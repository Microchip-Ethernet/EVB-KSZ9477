/*
 *	IEEE 802.1Q Multiple Registration Protocol (MRP)
 *
 *	Copyright (c) 2012 Massachusetts Institute of Technology
 *
 *	Adapted from code in net/802/garp.c
 *	Copyright (c) 2008 Patrick McHardy <kaber@trash.net>
 *
 *	This program is free software; you can redistribute it and/or
 *	modify it under the terms of the GNU General Public License
 *	version 2 as published by the Free Software Foundation.
 */
#include <linux/kernel.h>
#include <linux/timer.h>
#include <linux/skbuff.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/rtnetlink.h>
#include <linux/slab.h>
#include <linux/module.h>
#include "mrp.h"
#include <asm/unaligned.h>

#ifndef NETIF_F_HW_VLAN_CTAG_FILTER
#define prandom_u32()		prandom32(app->rnd)
#endif


static unsigned int mrp_join_time __read_mostly = 200;
module_param(mrp_join_time, uint, 0644);
MODULE_PARM_DESC(mrp_join_time, "Join time in ms (default 200ms)");

static unsigned int mrp_periodic_time __read_mostly = 1000;
module_param(mrp_periodic_time, uint, 0644);
MODULE_PARM_DESC(mrp_periodic_time, "Periodic time in ms (default 1s)");

static unsigned int mrp_leave_time __read_mostly = 1000;
static unsigned int mrp_lva_time __read_mostly = 10000;

MODULE_LICENSE("GPL");

static const u8
mrp_applicant_state_table[MRP_APPLICANT_MAX + 1][MRP_EVENT_MAX + 1] = {
	[MRP_APPLICANT_VO] = {
		[MRP_EVENT_NEW]		= MRP_APPLICANT_VN,
		[MRP_EVENT_JOIN]	= MRP_APPLICANT_VP,
		[MRP_EVENT_LV]		= MRP_APPLICANT_VO,
		[MRP_EVENT_TX]		= MRP_APPLICANT_VO,
		[MRP_EVENT_TX_LA]	= MRP_APPLICANT_LO,
		[MRP_EVENT_TX_LAF]	= MRP_APPLICANT_LO,
		[MRP_EVENT_R_NEW]	= MRP_APPLICANT_VO,
		[MRP_EVENT_R_JOIN_IN]	= MRP_APPLICANT_AO,
		[MRP_EVENT_R_IN]	= MRP_APPLICANT_VO,
		[MRP_EVENT_R_JOIN_MT]	= MRP_APPLICANT_VO,
		[MRP_EVENT_R_MT]	= MRP_APPLICANT_VO,
		[MRP_EVENT_R_LV]	= MRP_APPLICANT_LO,
		[MRP_EVENT_R_LA]	= MRP_APPLICANT_LO,
		[MRP_EVENT_REDECLARE]	= MRP_APPLICANT_LO,
		[MRP_EVENT_PERIODIC]	= MRP_APPLICANT_VO,
		[MRP_EVENT_LV_TIMER]	= MRP_APPLICANT_VO,
		[MRP_EVENT_FLUSH]	= MRP_APPLICANT_VO,
	},
	[MRP_APPLICANT_VP] = {
		[MRP_EVENT_NEW]		= MRP_APPLICANT_VN,
		[MRP_EVENT_JOIN]	= MRP_APPLICANT_VP,
		[MRP_EVENT_LV]		= MRP_APPLICANT_VO,
		[MRP_EVENT_TX]		= MRP_APPLICANT_AA,
		[MRP_EVENT_TX_LA]	= MRP_APPLICANT_AA,
		[MRP_EVENT_TX_LAF]	= MRP_APPLICANT_VP,
		[MRP_EVENT_R_NEW]	= MRP_APPLICANT_VP,
		[MRP_EVENT_R_JOIN_IN]	= MRP_APPLICANT_AP,
		[MRP_EVENT_R_IN]	= MRP_APPLICANT_VP,
		[MRP_EVENT_R_JOIN_MT]	= MRP_APPLICANT_VP,
		[MRP_EVENT_R_MT]	= MRP_APPLICANT_VP,
		[MRP_EVENT_R_LV]	= MRP_APPLICANT_VP,
		[MRP_EVENT_R_LA]	= MRP_APPLICANT_VP,
		[MRP_EVENT_REDECLARE]	= MRP_APPLICANT_VP,
		[MRP_EVENT_PERIODIC]	= MRP_APPLICANT_VP,
		[MRP_EVENT_LV_TIMER]	= MRP_APPLICANT_VP,
		[MRP_EVENT_FLUSH]	= MRP_APPLICANT_VP,
	},
	[MRP_APPLICANT_VN] = {
		[MRP_EVENT_NEW]		= MRP_APPLICANT_VN,
		[MRP_EVENT_JOIN]	= MRP_APPLICANT_VN,
		[MRP_EVENT_LV]		= MRP_APPLICANT_LA,
		[MRP_EVENT_TX]		= MRP_APPLICANT_AN,
		[MRP_EVENT_TX_LA]	= MRP_APPLICANT_AN,
		[MRP_EVENT_TX_LAF]	= MRP_APPLICANT_VN,
		[MRP_EVENT_R_NEW]	= MRP_APPLICANT_VN,
		[MRP_EVENT_R_JOIN_IN]	= MRP_APPLICANT_VN,
		[MRP_EVENT_R_IN]	= MRP_APPLICANT_VN,
		[MRP_EVENT_R_JOIN_MT]	= MRP_APPLICANT_VN,
		[MRP_EVENT_R_MT]	= MRP_APPLICANT_VN,
		[MRP_EVENT_R_LV]	= MRP_APPLICANT_VN,
		[MRP_EVENT_R_LA]	= MRP_APPLICANT_VN,
		[MRP_EVENT_REDECLARE]	= MRP_APPLICANT_VN,
		[MRP_EVENT_PERIODIC]	= MRP_APPLICANT_VN,
		[MRP_EVENT_LV_TIMER]	= MRP_APPLICANT_VN,
		[MRP_EVENT_FLUSH]	= MRP_APPLICANT_VN,
	},
	[MRP_APPLICANT_AN] = {
		[MRP_EVENT_NEW]		= MRP_APPLICANT_AN,
		[MRP_EVENT_JOIN]	= MRP_APPLICANT_AN,
		[MRP_EVENT_LV]		= MRP_APPLICANT_LA,
		[MRP_EVENT_TX]		= MRP_APPLICANT_QA,
		[MRP_EVENT_TX_LA]	= MRP_APPLICANT_QA,
		[MRP_EVENT_TX_LAF]	= MRP_APPLICANT_VN,
		[MRP_EVENT_R_NEW]	= MRP_APPLICANT_AN,
		[MRP_EVENT_R_JOIN_IN]	= MRP_APPLICANT_AN,
		[MRP_EVENT_R_IN]	= MRP_APPLICANT_AN,
		[MRP_EVENT_R_JOIN_MT]	= MRP_APPLICANT_AN,
		[MRP_EVENT_R_MT]	= MRP_APPLICANT_AN,
		[MRP_EVENT_R_LV]	= MRP_APPLICANT_VN,
		[MRP_EVENT_R_LA]	= MRP_APPLICANT_VN,
		[MRP_EVENT_REDECLARE]	= MRP_APPLICANT_VN,
		[MRP_EVENT_PERIODIC]	= MRP_APPLICANT_AN,
		[MRP_EVENT_LV_TIMER]	= MRP_APPLICANT_AN,
		[MRP_EVENT_FLUSH]	= MRP_APPLICANT_AN,
	},
	[MRP_APPLICANT_AA] = {
		[MRP_EVENT_NEW]		= MRP_APPLICANT_VN,
		[MRP_EVENT_JOIN]	= MRP_APPLICANT_AA,
		[MRP_EVENT_LV]		= MRP_APPLICANT_LA,
		[MRP_EVENT_TX]		= MRP_APPLICANT_QA,
		[MRP_EVENT_TX_LA]	= MRP_APPLICANT_QA,
		[MRP_EVENT_TX_LAF]	= MRP_APPLICANT_VP,
		[MRP_EVENT_R_NEW]	= MRP_APPLICANT_AA,
		[MRP_EVENT_R_JOIN_IN]	= MRP_APPLICANT_QA,
		[MRP_EVENT_R_IN]	= MRP_APPLICANT_QA,
		[MRP_EVENT_R_JOIN_MT]	= MRP_APPLICANT_AA,
		[MRP_EVENT_R_MT]	= MRP_APPLICANT_AA,
		[MRP_EVENT_R_LV]	= MRP_APPLICANT_VP,
		[MRP_EVENT_R_LA]	= MRP_APPLICANT_VP,
		[MRP_EVENT_REDECLARE]	= MRP_APPLICANT_VP,
		[MRP_EVENT_PERIODIC]	= MRP_APPLICANT_AA,
		[MRP_EVENT_LV_TIMER]	= MRP_APPLICANT_AA,
		[MRP_EVENT_FLUSH]	= MRP_APPLICANT_AA,
	},
	[MRP_APPLICANT_QA] = {
		[MRP_EVENT_NEW]		= MRP_APPLICANT_VN,
		[MRP_EVENT_JOIN]	= MRP_APPLICANT_QA,
		[MRP_EVENT_LV]		= MRP_APPLICANT_LA,
		[MRP_EVENT_TX]		= MRP_APPLICANT_QA,
		[MRP_EVENT_TX_LA]	= MRP_APPLICANT_QA,
		[MRP_EVENT_TX_LAF]	= MRP_APPLICANT_VP,
		[MRP_EVENT_R_NEW]	= MRP_APPLICANT_QA,
		[MRP_EVENT_R_JOIN_IN]	= MRP_APPLICANT_QA,
		[MRP_EVENT_R_IN]	= MRP_APPLICANT_QA,
		[MRP_EVENT_R_JOIN_MT]	= MRP_APPLICANT_AA,
		[MRP_EVENT_R_MT]	= MRP_APPLICANT_AA,
		[MRP_EVENT_R_LV]	= MRP_APPLICANT_VP,
		[MRP_EVENT_R_LA]	= MRP_APPLICANT_VP,
		[MRP_EVENT_REDECLARE]	= MRP_APPLICANT_VP,
		[MRP_EVENT_PERIODIC]	= MRP_APPLICANT_AA,
		[MRP_EVENT_LV_TIMER]	= MRP_APPLICANT_QA,
		[MRP_EVENT_FLUSH]	= MRP_APPLICANT_QA,
	},
	[MRP_APPLICANT_LA] = {
		[MRP_EVENT_NEW]		= MRP_APPLICANT_VN,
		[MRP_EVENT_JOIN]	= MRP_APPLICANT_AA,
		[MRP_EVENT_LV]		= MRP_APPLICANT_LA,
		[MRP_EVENT_TX]		= MRP_APPLICANT_VO,
		[MRP_EVENT_TX_LA]	= MRP_APPLICANT_LO,
		[MRP_EVENT_TX_LAF]	= MRP_APPLICANT_LO,
		[MRP_EVENT_R_NEW]	= MRP_APPLICANT_LA,
		[MRP_EVENT_R_JOIN_IN]	= MRP_APPLICANT_LA,
		[MRP_EVENT_R_IN]	= MRP_APPLICANT_LA,
		[MRP_EVENT_R_JOIN_MT]	= MRP_APPLICANT_LA,
		[MRP_EVENT_R_MT]	= MRP_APPLICANT_LA,
		[MRP_EVENT_R_LV]	= MRP_APPLICANT_LA,
		[MRP_EVENT_R_LA]	= MRP_APPLICANT_LA,
		[MRP_EVENT_REDECLARE]	= MRP_APPLICANT_LA,
		[MRP_EVENT_PERIODIC]	= MRP_APPLICANT_LA,
		[MRP_EVENT_LV_TIMER]	= MRP_APPLICANT_LA,
		[MRP_EVENT_FLUSH]	= MRP_APPLICANT_LA,
	},
	[MRP_APPLICANT_AO] = {
		[MRP_EVENT_NEW]		= MRP_APPLICANT_VN,
		[MRP_EVENT_JOIN]	= MRP_APPLICANT_AP,
		[MRP_EVENT_LV]		= MRP_APPLICANT_AO,
		[MRP_EVENT_TX]		= MRP_APPLICANT_AO,
		[MRP_EVENT_TX_LA]	= MRP_APPLICANT_LO,
		[MRP_EVENT_TX_LAF]	= MRP_APPLICANT_LO,
		[MRP_EVENT_R_NEW]	= MRP_APPLICANT_AO,
		[MRP_EVENT_R_JOIN_IN]	= MRP_APPLICANT_QO,
		[MRP_EVENT_R_IN]	= MRP_APPLICANT_AO,
		[MRP_EVENT_R_JOIN_MT]	= MRP_APPLICANT_AO,
		[MRP_EVENT_R_MT]	= MRP_APPLICANT_AO,
		[MRP_EVENT_R_LV]	= MRP_APPLICANT_LO,
		[MRP_EVENT_R_LA]	= MRP_APPLICANT_LO,
		[MRP_EVENT_REDECLARE]	= MRP_APPLICANT_LO,
		[MRP_EVENT_PERIODIC]	= MRP_APPLICANT_AO,
		[MRP_EVENT_LV_TIMER]	= MRP_APPLICANT_AO,
		[MRP_EVENT_FLUSH]	= MRP_APPLICANT_AO,
	},
	[MRP_APPLICANT_QO] = {
		[MRP_EVENT_NEW]		= MRP_APPLICANT_VN,
		[MRP_EVENT_JOIN]	= MRP_APPLICANT_QP,
		[MRP_EVENT_LV]		= MRP_APPLICANT_QO,
		[MRP_EVENT_TX]		= MRP_APPLICANT_QO,
		[MRP_EVENT_TX_LA]	= MRP_APPLICANT_LO,
		[MRP_EVENT_TX_LAF]	= MRP_APPLICANT_LO,
		[MRP_EVENT_R_NEW]	= MRP_APPLICANT_QO,
		[MRP_EVENT_R_JOIN_IN]	= MRP_APPLICANT_QO,
		[MRP_EVENT_R_IN]	= MRP_APPLICANT_QO,
		[MRP_EVENT_R_JOIN_MT]	= MRP_APPLICANT_AO,
		[MRP_EVENT_R_MT]	= MRP_APPLICANT_AO,
		[MRP_EVENT_R_LV]	= MRP_APPLICANT_LO,
		[MRP_EVENT_R_LA]	= MRP_APPLICANT_LO,
		[MRP_EVENT_REDECLARE]	= MRP_APPLICANT_LO,
		[MRP_EVENT_PERIODIC]	= MRP_APPLICANT_QO,
		[MRP_EVENT_LV_TIMER]	= MRP_APPLICANT_QO,
		[MRP_EVENT_FLUSH]	= MRP_APPLICANT_QO,
	},
	[MRP_APPLICANT_AP] = {
		[MRP_EVENT_NEW]		= MRP_APPLICANT_VN,
		[MRP_EVENT_JOIN]	= MRP_APPLICANT_AP,
		[MRP_EVENT_LV]		= MRP_APPLICANT_AO,
		[MRP_EVENT_TX]		= MRP_APPLICANT_QA,
		[MRP_EVENT_TX_LA]	= MRP_APPLICANT_QA,
		[MRP_EVENT_TX_LAF]	= MRP_APPLICANT_VP,
		[MRP_EVENT_R_NEW]	= MRP_APPLICANT_AP,
		[MRP_EVENT_R_JOIN_IN]	= MRP_APPLICANT_QP,
		[MRP_EVENT_R_IN]	= MRP_APPLICANT_AP,
		[MRP_EVENT_R_JOIN_MT]	= MRP_APPLICANT_AP,
		[MRP_EVENT_R_MT]	= MRP_APPLICANT_AP,
		[MRP_EVENT_R_LV]	= MRP_APPLICANT_VP,
		[MRP_EVENT_R_LA]	= MRP_APPLICANT_VP,
		[MRP_EVENT_REDECLARE]	= MRP_APPLICANT_VP,
		[MRP_EVENT_PERIODIC]	= MRP_APPLICANT_AP,
		[MRP_EVENT_LV_TIMER]	= MRP_APPLICANT_AP,
		[MRP_EVENT_FLUSH]	= MRP_APPLICANT_AP,
	},
	[MRP_APPLICANT_QP] = {
		[MRP_EVENT_NEW]		= MRP_APPLICANT_VN,
		[MRP_EVENT_JOIN]	= MRP_APPLICANT_QP,
		[MRP_EVENT_LV]		= MRP_APPLICANT_QO,
		[MRP_EVENT_TX]		= MRP_APPLICANT_QP,
		[MRP_EVENT_TX_LA]	= MRP_APPLICANT_QA,
		[MRP_EVENT_TX_LAF]	= MRP_APPLICANT_VP,
		[MRP_EVENT_R_NEW]	= MRP_APPLICANT_QP,
		[MRP_EVENT_R_JOIN_IN]	= MRP_APPLICANT_QP,
		[MRP_EVENT_R_IN]	= MRP_APPLICANT_QP,
		[MRP_EVENT_R_JOIN_MT]	= MRP_APPLICANT_AP,
		[MRP_EVENT_R_MT]	= MRP_APPLICANT_AP,
		[MRP_EVENT_R_LV]	= MRP_APPLICANT_VP,
		[MRP_EVENT_R_LA]	= MRP_APPLICANT_VP,
		[MRP_EVENT_REDECLARE]	= MRP_APPLICANT_VP,
		[MRP_EVENT_PERIODIC]	= MRP_APPLICANT_AP,
		[MRP_EVENT_LV_TIMER]	= MRP_APPLICANT_VP,
		[MRP_EVENT_FLUSH]	= MRP_APPLICANT_VP,
	},
	[MRP_APPLICANT_LO] = {
		[MRP_EVENT_NEW]		= MRP_APPLICANT_VN,
		[MRP_EVENT_JOIN]	= MRP_APPLICANT_VP,
		[MRP_EVENT_LV]		= MRP_APPLICANT_LO,
		[MRP_EVENT_TX]		= MRP_APPLICANT_VO,
		[MRP_EVENT_TX_LA]	= MRP_APPLICANT_LO,
		[MRP_EVENT_TX_LAF]	= MRP_APPLICANT_LO,
		[MRP_EVENT_R_NEW]	= MRP_APPLICANT_LO,
		[MRP_EVENT_R_JOIN_IN]	= MRP_APPLICANT_LO,
		[MRP_EVENT_R_IN]	= MRP_APPLICANT_LO,
		[MRP_EVENT_R_JOIN_MT]	= MRP_APPLICANT_VO,
		[MRP_EVENT_R_MT]	= MRP_APPLICANT_VO,
		[MRP_EVENT_R_LV]	= MRP_APPLICANT_LO,
		[MRP_EVENT_R_LA]	= MRP_APPLICANT_LO,
		[MRP_EVENT_REDECLARE]	= MRP_APPLICANT_LO,
		[MRP_EVENT_PERIODIC]	= MRP_APPLICANT_LO,
		[MRP_EVENT_LV_TIMER]	= MRP_APPLICANT_LO,
		[MRP_EVENT_FLUSH]	= MRP_APPLICANT_LO,
	},
};

static const u8
mrp_tx_action_table[MRP_APPLICANT_MAX + 1] = {
	[MRP_APPLICANT_VO] = MRP_TX_ACTION_S_IN_OPTIONAL,
	[MRP_APPLICANT_VP] = MRP_TX_ACTION_S_JOIN_IN,
	[MRP_APPLICANT_VN] = MRP_TX_ACTION_S_NEW,
	[MRP_APPLICANT_AN] = MRP_TX_ACTION_S_NEW,
	[MRP_APPLICANT_AA] = MRP_TX_ACTION_S_JOIN_IN,
	[MRP_APPLICANT_QA] = MRP_TX_ACTION_S_JOIN_IN_OPTIONAL,
	[MRP_APPLICANT_LA] = MRP_TX_ACTION_S_LV,
	[MRP_APPLICANT_AO] = MRP_TX_ACTION_S_IN_OPTIONAL,
	[MRP_APPLICANT_QO] = MRP_TX_ACTION_S_IN_OPTIONAL,
	[MRP_APPLICANT_AP] = MRP_TX_ACTION_S_JOIN_IN,
	[MRP_APPLICANT_QP] = MRP_TX_ACTION_S_IN_OPTIONAL,
	[MRP_APPLICANT_LO] = MRP_TX_ACTION_S_IN,
};

static const u8
mrp_tx_la_action_table[MRP_APPLICANT_MAX + 1] = {
	[MRP_APPLICANT_VO] = MRP_TX_ACTION_S_IN_OPTIONAL,
	[MRP_APPLICANT_VP] = MRP_TX_ACTION_S_IN,
	[MRP_APPLICANT_VN] = MRP_TX_ACTION_S_NEW,
	[MRP_APPLICANT_AN] = MRP_TX_ACTION_S_NEW,
	[MRP_APPLICANT_AA] = MRP_TX_ACTION_S_JOIN_IN,
	[MRP_APPLICANT_QA] = MRP_TX_ACTION_S_JOIN_IN,
	[MRP_APPLICANT_LA] = MRP_TX_ACTION_S_IN_OPTIONAL,
	[MRP_APPLICANT_AO] = MRP_TX_ACTION_S_IN_OPTIONAL,
	[MRP_APPLICANT_QO] = MRP_TX_ACTION_S_IN_OPTIONAL,
	[MRP_APPLICANT_AP] = MRP_TX_ACTION_S_JOIN_IN,
	[MRP_APPLICANT_QP] = MRP_TX_ACTION_S_JOIN_IN,
	[MRP_APPLICANT_LO] = MRP_TX_ACTION_S_IN_OPTIONAL,
};

#ifdef DBG_MRP
static char *format_event(char *str, enum mrp_event event)
{
	switch (event) {
	case MRP_EVENT_NEW:
		strcpy(str, "New!");
		break;
	case MRP_EVENT_JOIN:
		strcpy(str, "Join!");
		break;
	case MRP_EVENT_LV:
		strcpy(str, "Lv!");
		break;
	case MRP_EVENT_TX:
		strcpy(str, "tx!");
		break;
	case MRP_EVENT_TX_LA:
		strcpy(str, "txLA!");
		break;
	case MRP_EVENT_TX_LAF:
		strcpy(str, "txLAF!");
		break;
	case MRP_EVENT_R_NEW:
		strcpy(str, "rNew!");
		break;
	case MRP_EVENT_R_JOIN_IN:
		strcpy(str, "rJoinIn!");
		break;
	case MRP_EVENT_R_IN:
		strcpy(str, "rIn!");
		break;
	case MRP_EVENT_R_JOIN_MT:
		strcpy(str, "rJoinMt!");
		break;
	case MRP_EVENT_R_MT:
		strcpy(str, "rMt!");
		break;
	case MRP_EVENT_R_LV:
		strcpy(str, "rLv!");
		break;
	case MRP_EVENT_R_LA:
		strcpy(str, "rLA!");
		break;
	case MRP_EVENT_REDECLARE:
		strcpy(str, "Redec!");
		break;
	case MRP_EVENT_PERIODIC:
		strcpy(str, "periodic!");
		break;
	case MRP_EVENT_PERIODIC_DISABLE:
		strcpy(str, "peoridicDisable!");
		break;
	case MRP_EVENT_PERIODIC_ENABLE:
		strcpy(str, "periodicEnable!");
		break;
	case MRP_EVENT_LV_TIMER:
		strcpy(str, "lv!");
		break;
	case MRP_EVENT_LVA_TIMER:
		strcpy(str, "lva!");
		break;
	case MRP_EVENT_FLUSH:
		strcpy(str, "Flush!");
		break;
	default:
		strcpy(str, "?");
		break;
	}
	return str;
}  /* format_event */

static char *format_action(char *str, enum mrp_tx_action action)
{
	switch (action) {
	case MRP_TX_ACTION_NONE:
		strcpy(str, "-");
		break;
	case MRP_TX_ACTION_S_NEW:
		strcpy(str, "sN");
		break;
	case MRP_TX_ACTION_S_JOIN_IN:
		strcpy(str, "sJ");
		break;
	case MRP_TX_ACTION_S_JOIN_IN_OPTIONAL:
		strcpy(str, "[sJ]");
		break;
	case MRP_TX_ACTION_S_IN:
		strcpy(str, "s");
		break;
	case MRP_TX_ACTION_S_IN_OPTIONAL:
		strcpy(str, "[s]");
		break;
	case MRP_TX_ACTION_S_LV:
		strcpy(str, "sL");
		break;
	default:
		strcpy(str, "?");
		break;
	}
	return str;
}  /* format_action */

static char *format_app_state(char *str, enum mrp_applicant_state state)
{
	switch (state) {
	case MRP_APPLICANT_VO:
		strcpy(str, "VO");
		break;
	case MRP_APPLICANT_VP:
		strcpy(str, "VP");
		break;
	case MRP_APPLICANT_VN:
		strcpy(str, "VN");
		break;
	case MRP_APPLICANT_AN:
		strcpy(str, "AN");
		break;
	case MRP_APPLICANT_AA:
		strcpy(str, "AA");
		break;
	case MRP_APPLICANT_QA:
		strcpy(str, "QA");
		break;
	case MRP_APPLICANT_LA:
		strcpy(str, "LA");
		break;
	case MRP_APPLICANT_AO:
		strcpy(str, "AO");
		break;
	case MRP_APPLICANT_QO:
		strcpy(str, "QO");
		break;
	case MRP_APPLICANT_AP:
		strcpy(str, "AP");
		break;
	case MRP_APPLICANT_QP:
		strcpy(str, "QP");
		break;
	case MRP_APPLICANT_LO:
		strcpy(str, "LO");
		break;
	default:
		strcpy(str, "INV");
		break;
	}
	return str;
}  /* format_app_state */

static char *format_reg_state(char *str, enum mrp_registrar_state state)
{
	switch (state) {
	case MRP_REGISTRAR_MT:
		strcpy(str, "MT");
		break;
	case MRP_REGISTRAR_IN:
		strcpy(str, "IN");
		break;
	case MRP_REGISTRAR_LV:
		strcpy(str, "LV");
		break;
	default:
		strcpy(str, "INV");
		break;
	}
	return str;
}  /* format_reg_state */
#endif

static void mrp_attrvalue_inc(void *value, u8 len)
{
	u8 *v = (u8 *)value;

	/* Add 1 to the last byte. If it becomes zero,
	 * go to the previous byte and repeat.
	 */
	while (len > 0 && !++v[--len])
		;
}

static int mrp_attr_cmp(const struct mrp_attr *attr,
			 const void *value, u8 len, u8 type)
{
	if (attr->type != type)
		return attr->type - type;
	if (attr->len != len)
		return attr->len - len;
	return memcmp(attr->value, value, len);
}

static u8 mrp_attr_len(u8 attrtype, u8 attrlen)
{
	return attrlen;
}

static u8 mrp_attr_type(struct mrp_attr *attr)
{
	return attr->type;
}

#if 0
static int dbg_listener;
static int dbg_talker;
#endif

static struct mrp_attr *mrp_attr_lookup(const struct mrp_applicant *app,
					const void *value, u8 len, u8 type)
{
	struct rb_node *parent = app->mad.rb_node;
	struct mrp_attr *attr;
	int d;

	while (parent) {
		attr = rb_entry(parent, struct mrp_attr, node);
		d = app->attr_cmp(attr, value, len, type);
		if (d > 0)
			parent = parent->rb_left;
		else if (d < 0)
			parent = parent->rb_right;
		else
			return attr;
	}
#if 0
{
const u8 *data = value;

if ((len == 34 && !dbg_talker) || (len == 10 && !dbg_listener) ||
(len != 34 && len != 10)) {
dbg_msg("p:%d %d %d = ", app->port, app->app->type, type);
for (d = 0; d < len; d++)
dbg_msg("%02x ", data[d]);
dbg_msg("\n");

/* XMOS sends a talker with irrevant data. */
if (34 == len && 0x20 == data[17] && 0x01 == data[19])
++dbg_talker;
if (10 == len)
++dbg_listener;
}
}
#endif
	return NULL;
}

static struct mrp_attr *mrp_attr_create(struct mrp_applicant *app,
					const void *value, u8 len, u8 type)
{
	struct rb_node *parent = NULL, **p = &app->mad.rb_node;
	struct mrp_attr *attr;
	int d;

	while (*p) {
		parent = *p;
		attr = rb_entry(parent, struct mrp_attr, node);
		d = app->attr_cmp(attr, value, len, type);
		if (d > 0)
			p = &parent->rb_left;
		else if (d < 0)
			p = &parent->rb_right;
		else {
			/* The attribute already exists; re-use it. */
			return attr;
		}
	}
	attr = kmalloc(sizeof(*attr) + len, GFP_ATOMIC);
	if (!attr)
		return attr;
	attr->state = MRP_APPLICANT_VO;
	attr->type  = type;
	attr->len   = len;
	memcpy(attr->value, value, len);

	attr->new_state = MRP_APPLICANT_VO;
	attr->action = MRP_TX_ACTION_NONE;
	attr->reg_state = MRP_REGISTRAR_MT;
	attr->notify = MRP_NOTIFY_NONE;
	attr->aging = 0;

	rb_link_node(&attr->node, parent, p);
	rb_insert_color(&attr->node, &app->mad);
	return attr;
}

static void mrp_attr_destroy(struct mrp_applicant *app, struct mrp_attr *attr)
{
	u8 len = app->attr_len(attr->type, attr->len);
	u8 type = app->attr_type(attr);
dbg_msg("%s p:%d [%d=%d:%02x]\n", __func__, app->port, app->app->type,
type, attr->value[len - 1]);
	rb_erase(&attr->node, &app->mad);
	kfree(attr);
}

static int mrp_pdu_init(struct mrp_applicant *app)
{
	struct sk_buff *skb;
	struct mrp_pdu_hdr *ph;

	skb = alloc_skb(app->dev->mtu + LL_RESERVED_SPACE(app->dev) + 8,
			GFP_ATOMIC);
	if (!skb)
		return -ENOMEM;

	skb->dev = app->dev;
	skb->protocol = app->app->pkttype.type;
	skb_reserve(skb, LL_RESERVED_SPACE(app->dev));
	skb_reset_network_header(skb);
	skb_reset_transport_header(skb);

	ph = (struct mrp_pdu_hdr *)__skb_put(skb, sizeof(*ph));
	ph->version = app->app->version;

	app->pdu = skb;
	return 0;
}

static int mrp_applicant_chk(struct mrp_attr *attr)
{
	int ret = 0;
#if 0
	u8 len = attr->len;

if (25 == len || 34 == len || 10 == len)
	len = 8;
dbg_msg("aging [%02x] %d\n", attr->value[len - 1], attr->aging);
#endif
	if (attr->new_state != attr->state) {
		if (MRP_APPLICANT_VO == attr->new_state) {
			if (!attr->aging)
				attr->aging = 4;
		} else if (MRP_APPLICANT_LO != attr->new_state)
			attr->aging = 0;
		attr->state = attr->new_state;
	}
	if (MRP_REGISTRAR_MT != attr->reg_state)
		attr->aging = 0;
	if (attr->action != MRP_TX_ACTION_NONE) {
		if (attr->aging > 1)
			--attr->aging;
		attr->action = MRP_TX_ACTION_NONE;
	}
	if (1 == attr->aging)
		return 1;
	return ret;
}

#define MRP_OPT_MAX(attrlen)		\
	((((2 + (attrlen)) + 1) * 2 - (2 + (attrlen))) * 3)

#define MMRP_SVC_OPT_MAX		MRP_OPT_MAX(1)
#define MMRP_MAC_OPT_MAX		MRP_OPT_MAX(6)
#define MVRP_VID_OPT_MAX		MRP_OPT_MAX(2)

static void mrp_prepare_tx(struct mrp_applicant *app, u8 attrtype,
	int firstval_max)
{
	u8 firstval[20];
	int firstval_cnt = 0;
	int firstval_opt = 0;
	struct rb_node *node, *next;
	struct rb_node *opt = NULL;
	struct mrp_attr *attr;
	struct mrp_attr *first = NULL;
	struct mrp_attr dummy;
	struct mrp_attr *last = &dummy;
	enum mrp_tx_action last_action = MRP_TX_ACTION_NONE;

	memset(firstval, 0, sizeof(firstval));
	for (node = rb_first(&app->mad);
	     next = node ? rb_next(node) : NULL, node != NULL;
	     node = next) {
		attr = rb_entry(node, struct mrp_attr, node);
		if (attrtype != attr->type)
			continue;
		if (MRP_TX_ACTION_NONE == attr->action)
{
dbg_msg(" no send\n");
			continue;
}

		/* At least one attribute that is trying to send something. */
		if (last) {
			last = attr;
			last_action = attr->action;
		}
		if (firstval_cnt) {
			int firstval_next = 1;

			app->attrval_inc(firstval, attr->len);
			if (memcmp(firstval, attr->value, attr->len))
				firstval_next = 0;
			if (!firstval_next)
				first = NULL;
			else {
				++firstval_cnt;
				if (MRP_TX_ACTION_S_JOIN_IN_OPTIONAL ==
				    attr->action ||
				    MRP_TX_ACTION_S_IN_OPTIONAL ==
				    attr->action) {
					if (!opt) {
						opt = node;
						firstval_opt =
							firstval_cnt % 3;
						if (!firstval_opt)
							firstval_opt = 3;
					} else
						++firstval_opt;
					if (firstval_opt >= firstval_max)
						first = NULL;
				} else {
					opt = NULL;
					firstval_opt = 0;
				}
			}
		}
		if (!first) {
			while (firstval_opt) {
				first = rb_entry(opt, struct mrp_attr, node);
				first->action = MRP_TX_ACTION_NONE;
				opt = rb_next(opt);
				--firstval_opt;
			}
			opt = NULL;
			firstval_opt = 0;
			if (MRP_TX_ACTION_S_JOIN_IN_OPTIONAL == attr->action ||
			    MRP_TX_ACTION_S_IN_OPTIONAL == attr->action) {
				attr->action = MRP_TX_ACTION_NONE;
				continue;
			}
			first = attr;
			memcpy(firstval, attr->value, attr->len);
			firstval_cnt = 1;

			/* There is at least one attribute sending. */
			last = NULL;
		}
	}

	/* Need to send at least one for LeaveAll. */
	if ((app->lva.tx & (1 << (attrtype - 1))) && last &&
	    MRP_TX_ACTION_NONE == last->action)
		last->action = last_action;
}

static u8 mrp_3pack_encode(u8 vect[], int *i)
{
	u8 val;

	val = vect[0] * __MRP_VECATTR_EVENT_MAX * __MRP_VECATTR_EVENT_MAX;
	val += vect[1] * __MRP_VECATTR_EVENT_MAX;
	val += vect[2];
	memset(vect, 0, 3);
	*i = 0;
	return val;
}

#ifdef CONFIG_KSZ_MSRP
static u8 mrp_4pack_encode(u8 vect[])
{
	u8 val;

	val = vect[0] * 64;
	val += vect[1] * 16;
	val += vect[2] * 4;
	val += vect[3];
	return val;
}

static void mrp_4pack_decode(u8 val, u8 vect[], int *i)
{
	vect[3] = val & 3;
	val >>= 2;
	vect[2] = val & 3;
	val >>= 2;
	vect[1] = val & 3;
	val >>= 2;
	vect[0] = val & 3;
	*i = 0;
}
#endif

/* mrp_vecattr_hdr + attrlen + vaevents + 4 endmarks */
#define MRP_MIN			(2 + 1 + 4)

#define MVRP_VID_MIN		(2 + MRP_MIN)
#define MMRP_SVC_MIN		(1 + MRP_MIN)
#define MMRP_MAC_MIN		(6 + MRP_MIN)

static int mrp_tx(struct mrp_applicant *app, u8 *msg_buf, u8 *msg_eof,
	int *bytes, u8 attrtype, u8 attrlen, u8 attrmax, u8 msg_min)
{
	struct rb_node *node, *next;
	struct mrp_attr *attr;
	struct mrp_msg_hdr *mh;
	struct mrp_vecattr_hdr *vah;
	u8 firstval[20];
	u8 vectevt[3];
	int i = 0;
	int len = 0;
	int num_break = false;
	int node_break = false;
	u8 *msg_ptr = msg_buf;

	*bytes = 0;

	/* mrp_msg_hdr + mrp_vecattr_hdr + attrlen + vaevents + 4 endmarks */
	if (msg_ptr > (msg_eof - (sizeof(struct mrp_msg_hdr) + msg_min)))
		return -1;
	memset(vectevt, 0, 3);

	mrp_prepare_tx(app, attrtype, attrmax);

	mh = (struct mrp_msg_hdr *) msg_ptr;
	mh->attrtype = attrtype;
	mh->attrlen = attrlen;
	msg_ptr += sizeof(struct mrp_msg_hdr);

	vah = (struct mrp_vecattr_hdr *) msg_ptr;
	msg_ptr += sizeof(struct mrp_vecattr_hdr);

	node = app->last_node;
	if (node) {
dbg_msg("%s 3\n", __func__);
		attr = rb_entry(node, struct mrp_attr, node);
		if (attrtype != attr->type)
			return 0;
	} else
		node = rb_first(&app->mad);
	for (;
	     next = node ? rb_next(node) : NULL, node != NULL;
	     node = next) {

		/* Check if there is enough space for all required data. */
		if (!len && msg_ptr > (msg_eof - msg_min))
{
dbg_msg(" no space\n");
			break;
}

		attr = rb_entry(node, struct mrp_attr, node);
		if (attrtype != attr->type)
			continue;

		if (MRP_TX_ACTION_NONE == attr->action) {
			if (mrp_applicant_chk(attr))
				mrp_attr_destroy(app, attr);

			/* In case there are events waiting. */
			i += 2;
			goto val_end;
		}
		if (len) {
			app->attrval_inc(firstval, attr->len);
			if (memcmp(firstval, attr->value, attr->len)) {
				/* Process with current node. */
				next = node;
				num_break = true;
				i = 3;
				goto val_end;
			}
		}
		if (!len) {
			memcpy(firstval, attr->value, attr->len);
			memcpy(vah->firstattrvalue, firstval, attr->len);
			msg_ptr += attr->len;
		}
		switch (attr->action) {
		case MRP_TX_ACTION_S_JOIN_IN:
		case MRP_TX_ACTION_S_JOIN_IN_OPTIONAL:
			vectevt[i] = MRP_REGISTRAR_IN == attr->reg_state ?
				MRP_VECATTR_EVENT_JOIN_IN :
				MRP_VECATTR_EVENT_JOIN_MT;
			break;
		case MRP_TX_ACTION_S_IN:
		case MRP_TX_ACTION_S_IN_OPTIONAL:
			vectevt[i] = MRP_REGISTRAR_IN == attr->reg_state ?
				MRP_VECATTR_EVENT_IN :
				MRP_VECATTR_EVENT_MT;
			break;
		case MRP_TX_ACTION_S_NEW:
			vectevt[i] = MRP_VECATTR_EVENT_NEW;
			break;
		case MRP_TX_ACTION_S_LV:
			vectevt[i] = MRP_VECATTR_EVENT_LV;
			break;
		default:
			break;
		}
		if (mrp_applicant_chk(attr))
			mrp_attr_destroy(app, attr);

		++i;
		++len;

val_end:
		if (i >= 3) {
			*msg_ptr++ = mrp_3pack_encode(vectevt, &i);
			if (msg_ptr > msg_eof - (1 + 4)) {
				num_break = true;
				node_break = true;
			}
		}
		if (num_break) {
			put_unaligned(cpu_to_be16(len), &vah->lenflags);
			if (app->lva.tx & (1 << (attrtype - 1)))
				vah->lenflags |= MRP_VECATTR_HDR_FLAG_LA;
			len = 0;
			num_break = false;

			vah = (struct mrp_vecattr_hdr *) msg_ptr;
			msg_ptr += sizeof(struct mrp_vecattr_hdr);
		}
		if (node_break)
			break;
	}
	if (len) {
		if (i)
			*msg_ptr++ = mrp_3pack_encode(vectevt, &i);
		put_unaligned(cpu_to_be16(len), &vah->lenflags);
		if (app->lva.tx & (1 << (attrtype - 1)))
			vah->lenflags |= MRP_VECATTR_HDR_FLAG_LA;
	}
	app->last_node = node;

	if (msg_ptr == msg_buf +
	    sizeof(struct mrp_msg_hdr) +
	    sizeof(struct mrp_vecattr_hdr)) {
		return 0;
	}
	*msg_ptr++ = MRP_END_MARK;
	*msg_ptr++ = MRP_END_MARK;

	*bytes = msg_ptr - msg_buf;

	/* Not all attributes sent. */
	if (node)
		return -1;
	return 0;
}

static void mrp_leave_timer_arm(struct mrp_applicant *app)
{
	/* Extend the timer in case one is already scheduled. */
#if 0
	if (app->timer_arm.leave)
		return;
#endif
	mod_timer(&app->leave_timer,
		  jiffies + msecs_to_jiffies(mrp_leave_time));
	app->timer_arm.leave = 1;
}

static int mrp_registrar_event(struct mrp_applicant *app, struct mrp_attr *attr,
	enum mrp_event event)
{
	enum mrp_registrar_state state = attr->reg_state;
	enum mrp_notification notify = MRP_NOTIFY_NONE;
#ifdef DBG_MRP
	char last_reg_str[10];
	char reg_str[10];
#endif

	switch (event) {
	case MRP_EVENT_R_LV:
	case MRP_EVENT_R_LA:
	case MRP_EVENT_REDECLARE:
		if (MRP_REGISTRAR_IN == attr->reg_state) {
			mrp_leave_timer_arm(app);
			state = MRP_REGISTRAR_LV;
		}
		break;
	case MRP_EVENT_R_NEW:
		state = MRP_REGISTRAR_IN;
		notify = MRP_NOTIFY_NEW;
		break;
	case MRP_EVENT_R_JOIN_IN:
	case MRP_EVENT_R_JOIN_MT:
		if (MRP_REGISTRAR_MT == attr->reg_state) {
			state = MRP_REGISTRAR_IN;
			notify = MRP_NOTIFY_JOIN;
		} else if (MRP_REGISTRAR_LV == attr->reg_state)
			state = MRP_REGISTRAR_IN;
		break;
	case MRP_EVENT_LV_TIMER:
		if (MRP_REGISTRAR_LV == attr->reg_state) {
			state = MRP_REGISTRAR_MT;
			notify = MRP_NOTIFY_LV;
		}
		break;
	case MRP_EVENT_FLUSH:
		if (MRP_REGISTRAR_LV == attr->reg_state)
			notify = MRP_NOTIFY_LV;
		state = MRP_REGISTRAR_MT;
		break;
	case MRP_EVENT_R_MT:
		break;
	default:
		break;
	}
#ifdef DBG_MRP
	if (state != attr->reg_state || (notify && notify != attr->notify)) {
		u8 len = app->attr_len(attr->type, attr->len);
		u8 type = app->attr_type(attr);

		format_reg_state(reg_str, state);
		format_reg_state(last_reg_str, attr->reg_state);
		if (notify != attr->notify && notify)
dbg_msg(" ==>");
dbg_msg(" reg_event p:%d [%d=%d:%02x] %s:%s %d\n", app->port, app->app->type,
type, attr->value[len - 1],
	last_reg_str, reg_str, notify);
	}
#endif
	attr->reg_state = state;
	attr->notify = notify;
	return notify != MRP_NOTIFY_NONE;
}

static int mrp_attr_event(struct mrp_applicant *app,
			   struct mrp_attr *attr, enum mrp_event event)
{
	enum mrp_applicant_state state;
	int tx = false;
	int tx_req = false;
#ifdef DBG_MRP
	char ev_str[10];
	char last_app_str[10];
	char last_new_str[10];
	char app_str[10];
	char new_str[10];
	char act_str[10];
	enum mrp_applicant_state last_state = attr->state;
	enum mrp_tx_action last_action = attr->action;

	format_event(ev_str, event);
	format_app_state(last_new_str, attr->new_state);
	format_app_state(last_app_str, attr->state);
#endif

	/* Do not change state if already sent. */
	if (MRP_EVENT_TX_LAF == event && MRP_TX_ACTION_NONE == attr->action)
		return tx_req;

	/* Note #4. */
	if (MRP_EVENT_R_JOIN_IN == event) {
		if ((MRP_APPLICANT_VO == attr->state ||
		    MRP_APPLICANT_VP == attr->state) && app->p2p_mac)
			return tx_req;

	/* Note #5. */
	} else if (MRP_EVENT_R_IN == event) {
		if (MRP_APPLICANT_AA == attr->state && !app->p2p_mac)
			return tx_req;
	}

	state = mrp_applicant_state_table[attr->state][event];
	if (state == MRP_APPLICANT_INVALID) {
		WARN_ON(1);
		return tx_req;
	}
	/* Note #8. */
	if (MRP_APPLICANT_AN == attr->state && MRP_EVENT_TX == event &&
	    MRP_REGISTRAR_IN != attr->reg_state)
		state = MRP_APPLICANT_AA;

	if (event == MRP_EVENT_TX) {
		attr->action = mrp_tx_action_table[attr->state];
		tx = true;
	}
	if (event == MRP_EVENT_TX_LA) {
		attr->action = mrp_tx_la_action_table[attr->state];
		tx = true;
	}
#ifdef MRP_BASIC
	if (MRP_TX_ACTION_S_JOIN_IN_OPTIONAL == attr->action)
		attr->action = MRP_TX_ACTION_S_JOIN_IN;
	else if (MRP_TX_ACTION_S_IN_OPTIONAL == attr->action)
		attr->action = MRP_TX_ACTION_S_IN;
#endif
	if (state != attr->state) {
		switch (state) {
		case MRP_APPLICANT_VN:
		case MRP_APPLICANT_AN:
		case MRP_APPLICANT_AA:
		case MRP_APPLICANT_LA:
		case MRP_APPLICANT_VP:
		case MRP_APPLICANT_AP:
		case MRP_APPLICANT_LO:

			/* Note #6. */
			tx_req = true;
			break;
		case MRP_APPLICANT_VO:

			/* Attribute is not being sent. */
			if (!tx) {
				if (!attr->aging)
					attr->aging = 3;
			}
			break;
		default:
			break;
		}
	}
	if (tx && !tx_req &&
	    (MRP_TX_ACTION_S_JOIN_IN_OPTIONAL == attr->action ||
	    MRP_TX_ACTION_S_IN_OPTIONAL == attr->action))
		tx = false;

	/* Update state after attribute is sent. */
	attr->new_state = state;
	if (!tx)
		attr->state = state;
#ifdef DBG_MRP
	if (last_state != state || last_action != attr->action) {
		u8 len = app->attr_len(attr->type, attr->len);
		u8 type = app->attr_type(attr);

		format_app_state(new_str, attr->new_state);
		format_app_state(app_str, attr->state);
		format_action(act_str, attr->action);
if (MRP_EVENT_R_LV == event)
dbg_msg(" --> ");
else if (app->rx)
dbg_msg(" -> ");
dbg_msg("attr_event p:%d [%d=%d:%02x] %s:%s %s ", app->port, app->app->type,
type, attr->value[len - 1],
last_app_str, last_new_str, ev_str);
dbg_msg(" %s:%s %s %d\n", app_str, new_str, act_str, tx_req);
	}
#endif

	switch (event) {
	case MRP_EVENT_R_NEW:
	case MRP_EVENT_R_JOIN_IN:
	case MRP_EVENT_R_IN:
	case MRP_EVENT_R_JOIN_MT:
	case MRP_EVENT_R_MT:
	case MRP_EVENT_R_LV:
	case MRP_EVENT_R_LA:
	case MRP_EVENT_REDECLARE:
	case MRP_EVENT_LV_TIMER:
	case MRP_EVENT_LVA_TIMER:
	case MRP_EVENT_FLUSH:
		if (mrp_registrar_event(app, attr, event))
			app->acton(app, attr);
		break;
	default:
		break;
	}

	return tx_req;
}

static void mrp_lva_timer_arm(struct mrp_applicant *app)
{
	unsigned long delay;
	unsigned long fixed;
	unsigned long random;

	/* Ignore if one is already scheduled. */
	if (app->timer_arm.lva)
		return;
	app->timer_arm.lva = 1;
	random = mrp_lva_time / 4;
	fixed = msecs_to_jiffies(random * 3);
	random += random / 4;
	delay = (u64)msecs_to_jiffies(random) * prandom_u32() >> 32;
	delay += fixed;
	mod_timer(&app->lva_timer, jiffies + delay);
}

static int mrp_lva_timer_event(struct mrp_applicant *app, enum mrp_event event)
{
	enum mrp_timer_state state = app->lva.state;
	int tx_lva = 0;
	int tx_req = false;

	switch (event) {
	case MRP_EVENT_TX:
		if (MRP_TIMER_ACTIVE == state) {
			tx_lva = 0xf;
			state = MRP_TIMER_PASSIVE;
		}
		break;
	case MRP_EVENT_R_LA:
		state = MRP_TIMER_PASSIVE;
		mrp_lva_timer_arm(app);
		break;
	case MRP_EVENT_LVA_TIMER:
		state = MRP_TIMER_ACTIVE;
		mrp_lva_timer_arm(app);
		break;
	default:
		return tx_req;
	}
	if (state != app->lva.state && MRP_TIMER_ACTIVE == state)
		tx_req = true;
	app->lva.state = state;
	app->lva.tx = tx_lva;
	return tx_req;
}

static void mrp_periodic_timer_arm(struct mrp_applicant *app)
{
	/* Ignore if one is already scheduled. */
	if (app->timer_arm.periodic)
		return;
	mod_timer(&app->periodic_timer,
		  jiffies + msecs_to_jiffies(mrp_periodic_time));
	app->timer_arm.periodic = 1;
}

static void mrp_periodic_event(struct mrp_applicant *app, enum mrp_event event)
{
	enum mrp_timer_state state = app->periodic.state;

	switch (event) {
	case MRP_EVENT_PERIODIC:
		if (MRP_TIMER_ACTIVE == state)
			mrp_periodic_timer_arm(app);
		break;
	case MRP_EVENT_PERIODIC_DISABLE:
		state = MRP_TIMER_PASSIVE;
		break;
	case MRP_EVENT_PERIODIC_ENABLE:
		if (MRP_TIMER_PASSIVE == state) {
			state = MRP_TIMER_ACTIVE;
			mrp_periodic_timer_arm(app);
		}
	default:
		break;
	}
	app->periodic.state = state;
}

static void mrp_join_timer_arm(struct mrp_applicant *app)
{
	unsigned long delay;
	unsigned long fixed;
	unsigned long random;

	/* Ignore if one is already scheduled. */
	if (app->timer_arm.join)
		return;
	app->timer_arm.join = 1;
	random = mrp_join_time / 4;
	fixed = msecs_to_jiffies(random * 3);
	random += random / 8;
	delay = (u64)msecs_to_jiffies(random) * prandom_u32() >> 32;
	delay += fixed;
	mod_timer(&app->join_timer, jiffies + delay);
}

static void mrp_mad_event(struct mrp_applicant *app, enum mrp_event event)
{
	struct rb_node *node, *next;
	struct mrp_attr *attr;
	int tx_req = 0;

	/* Do this first so that tx! becomes txLA! if LeaveAll is indicated. */
	if (MRP_EVENT_TX == event || MRP_EVENT_R_LA == event ||
	    MRP_EVENT_LVA_TIMER == event)
		tx_req |= mrp_lva_timer_event(app, event);
	if (MRP_EVENT_TX == event && app->lva.tx)
		event = MRP_EVENT_TX_LA;
#if 1
/*
 * Do this first or after txLAF! ?
 * If first the registrar values will always be empty, prompting the other to
 * send back the values.  On the other hand, the receiving side can flush the
 * registrar value and get the current one immediately without waiting for
 * another transmit.
 */

	if (MRP_EVENT_TX_LA == event) {
		for (node = rb_first(&app->mad);
		     next = node ? rb_next(node) : NULL, node != NULL;
		     node = next) {
			attr = rb_entry(node, struct mrp_attr, node);
			tx_req |= mrp_attr_event(app, attr, MRP_EVENT_R_LA);
		}
	}
#endif
	for (node = rb_first(&app->mad);
	     next = node ? rb_next(node) : NULL, node != NULL;
	     node = next) {
		attr = rb_entry(node, struct mrp_attr, node);

		/* Act on specific attribute type. */
		if (app->lva_type) {
			u8 attrtype = app->attr_type(attr);

			if (attrtype != app->lva_type)
				continue;
		}
		tx_req |= mrp_attr_event(app, attr, event);
	}
	if (MRP_EVENT_PERIODIC == event)
		mrp_periodic_event(app, MRP_EVENT_PERIODIC);
	if (MRP_EVENT_TX == event || MRP_EVENT_TX_LA == event) {
		int rc;

		event = 0;
#if 0
		app->lva.rx = app->lva.tx;
#endif
		rc = app->txpdu(app);

		/* Not all attributes sent. */
		if (rc) {
			if (app->lva.tx)
				event = MRP_EVENT_TX_LAF;
			else
				tx_req |= 2;
		} else if (app->lva.rx) {
#if 0
			event = MRP_EVENT_R_LA;
			tx_req |= mrp_lva_timer_event(app, event);
#endif
		}
		if (event) {
			for (node = rb_first(&app->mad);
			     next = node ? rb_next(node) : NULL, node != NULL;
			     node = next) {
				attr = rb_entry(node, struct mrp_attr, node);
				tx_req |= mrp_attr_event(app, attr, event);
			}
		}
	}
	if (tx_req) {
		mrp_join_timer_arm(app);

		/* Not continuing previous tx!. */
		if (!(tx_req & 2))
			app->last_node = NULL;
	}
}

static void mrp_join_timer_exec(struct mrp_applicant *app)
{
	spin_lock(&app->lock);
	app->timer_arm.join = 0;
	mrp_mad_event(app, MRP_EVENT_TX);
	spin_unlock(&app->lock);
}

static void mrp_join_timer_work(struct work_struct *work)
{
	struct mrp_applicant *app =
		container_of(work, struct mrp_applicant, join_work);

	mrp_join_timer_exec(app);
}

static void mrp_join_timer(unsigned long data)
{
	struct mrp_applicant *app = (struct mrp_applicant *)data;

	/* Timer is running in interrupt context. */
	schedule_work(&app->join_work);
}

static void mrp_periodic_timer_exec(struct mrp_applicant *app)
{
	spin_lock(&app->lock);
	app->timer_arm.periodic = 0;
	mrp_mad_event(app, MRP_EVENT_PERIODIC);
	spin_unlock(&app->lock);
}

static void mrp_periodic_timer_work(struct work_struct *work)
{
	struct mrp_applicant *app =
		container_of(work, struct mrp_applicant, periodic_work);

	mrp_periodic_timer_exec(app);
}

static void mrp_periodic_timer(unsigned long data)
{
	struct mrp_applicant *app = (struct mrp_applicant *)data;

	/* Periodic timer is disabled. */
	if (MRP_TIMER_PASSIVE == app->periodic.state) {
		app->timer_arm.periodic = 0;
		return;
	}

	/* Timer is running in interrupt context.  Not necessary. */
	schedule_work(&app->periodic_work);
}

static void mrp_leave_timer_exec(struct mrp_applicant *app)
{
	spin_lock(&app->lock);
	app->timer_arm.leave = 0;
	mrp_mad_event(app, MRP_EVENT_LV_TIMER);
	spin_unlock(&app->lock);
}

static void mrp_leave_timer_work(struct work_struct *work)
{
	struct mrp_applicant *app =
		container_of(work, struct mrp_applicant, leave_work);

	mrp_leave_timer_exec(app);
}

static void mrp_leave_timer(unsigned long data)
{
	struct mrp_applicant *app = (struct mrp_applicant *)data;

	/* Timer is running in interrupt context.. */
	schedule_work(&app->leave_work);
}

static void mrp_lva_timer_exec(struct mrp_applicant *app)
{
	int tx_req;

	spin_lock(&app->lock);
	app->timer_arm.lva = 0;
	tx_req = mrp_lva_timer_event(app, MRP_EVENT_LVA_TIMER);
	if (tx_req)
		mrp_join_timer_arm(app);
	spin_unlock(&app->lock);
}

static void mrp_lva_timer_work(struct work_struct *work)
{
	struct mrp_applicant *app =
		container_of(work, struct mrp_applicant, lva_work);

	mrp_lva_timer_exec(app);
}

static void mrp_lva_timer(unsigned long data)
{
	struct mrp_applicant *app = (struct mrp_applicant *)data;

	/* Timer is running in interrupt context.  Not necessary. */
	schedule_work(&app->lva_work);
}

static void mrp_update_attr(struct mrp_applicant *app, u8 *attrvalue,
	u8 attrlen, u8 attrtype, u8 vaevent)
{
	enum mrp_event event;
	struct mrp_attr *attr;

	switch (vaevent) {
	case MRP_VECATTR_EVENT_NEW:
		event = MRP_EVENT_R_NEW;
		break;
	case MRP_VECATTR_EVENT_JOIN_IN:
		event = MRP_EVENT_R_JOIN_IN;
		break;
	case MRP_VECATTR_EVENT_IN:
		event = MRP_EVENT_R_IN;
		break;
	case MRP_VECATTR_EVENT_JOIN_MT:
		event = MRP_EVENT_R_JOIN_MT;
		break;
	case MRP_VECATTR_EVENT_MT:
		event = MRP_EVENT_R_MT;
		break;
	case MRP_VECATTR_EVENT_LV:
		event = MRP_EVENT_R_LV;
		break;
	default:
		return;
	}
#ifdef DBG_MRP_
{
	char ev_str[10];
	u8 len = app->attr_len(attrtype, attrlen);

	format_event(ev_str, event);
dbg_msg("> ");
#if 1
dbg_msg("%s p:%d [%d=%d:%02x] %s\n", __func__, app->port, app->app->type,
attrtype, attrvalue[len - 1], ev_str);
#endif
}
#endif
	attr = mrp_attr_lookup(app, attrvalue, attrlen, attrtype);
	if (attr == NULL) {

		/* No need to create an attribute. */
		if (MRP_VECATTR_EVENT_MT == vaevent ||
		    MRP_VECATTR_EVENT_LV == vaevent)
{
#if 1
if (MRP_VECATTR_EVENT_LV == vaevent)
dbg_msg(" not create\n");
#endif
			return;
}
		attr = mrp_attr_create(app, attrvalue, attrlen, attrtype);
		if (!attr)
			return;
	}

	app->rx = 1;
	if (mrp_attr_event(app, attr, event))
		mrp_join_timer_arm(app);
	app->rx = 0;
}

static int mrp_parse_end_mark(u8 **msg_ptr, u8 *msg_eof)
{
	u8 *data = *msg_ptr;

	if (*msg_ptr > (msg_eof - 2))
{
dbg_msg(" e1 %02x %02x; %p %p\n", data[0], data[1], *msg_ptr, msg_eof);
		return -1;
}

	/* End mark can terminte list. */
	if (MRP_END_MARK == data[0] && MRP_END_MARK == data[1]) {
		*msg_ptr += 2;
		return 0;
	}

	/* Keep parsing. */
	return 1;
}

static int mrp_parse_events(struct mrp_applicant *app,
	u8 **msg_ptr, u8 *msg_eof, u8 attrlen, u8 attrtype)
{
	struct mrp_vecattr_hdr *vah;
	u16 valen;
	u16 LA;
	u8 firstval[20];
	u8 vaevent;
	u8 vaevents;

	vah = (struct mrp_vecattr_hdr *) *msg_ptr;
	valen = get_unaligned(&vah->lenflags);
	LA = valen & MRP_VECATTR_HDR_FLAG_LA;
	valen = be16_to_cpu(valen & MRP_VECATTR_HDR_LEN_MASK);
	if (!valen)
		return -1;
	if (*msg_ptr + (valen + 2) / 3 >= msg_eof)
		return -1;

	*msg_ptr += sizeof(struct mrp_vecattr_hdr);

	/* Do it once for each attribute type. */
	if (LA && !(app->lva.rx & (1 << attrtype))) {
		app->lva_type = attrtype;
		mrp_mad_event(app, MRP_EVENT_R_LA);
		app->lva_type = 0;
		app->lva.rx |= (1 << attrtype);
	}

	memcpy(firstval, vah->firstattrvalue, attrlen);
	*msg_ptr += attrlen;

	/* In a VectorAttribute, the Vector contains events which are packed
	 * three to a byte. We process one byte of the Vector at a time.
	 */
	while (valen > 0) {
		vaevents = **msg_ptr;
		*msg_ptr += sizeof(vaevents);

		/* Extract and process the first event. */
		vaevent = vaevents / (__MRP_VECATTR_EVENT_MAX *
				      __MRP_VECATTR_EVENT_MAX);
		if (vaevent >= __MRP_VECATTR_EVENT_MAX) {
			/* The byte is malformed; stop processing. */
			return -1;
		}
		mrp_update_attr(app, firstval, attrlen, attrtype, vaevent);

		/* If present, extract and process the second event. */
		if (!--valen)
			break;
		vaevents %= (__MRP_VECATTR_EVENT_MAX *
			     __MRP_VECATTR_EVENT_MAX);
		vaevent = vaevents / __MRP_VECATTR_EVENT_MAX;
		app->attrval_inc(firstval, attrlen);
		mrp_update_attr(app, firstval, attrlen, attrtype, vaevent);

		/* If present, extract and process the third event. */
		if (!--valen)
			break;
		vaevents %= __MRP_VECATTR_EVENT_MAX;
		vaevent = vaevents;
		app->attrval_inc(firstval, attrlen);
		mrp_update_attr(app, firstval, attrlen, attrtype, vaevent);
		app->attrval_inc(firstval, attrlen);
		--valen;
	}
	return 0;
}

static int mrp_parse_msg(struct mrp_applicant *app, u8 **msg_ptr, u8 *msg_eof)
{
	struct mrp_msg_hdr *mh;
	int rc;

	/*
	 * End mark terminates the message.  Happen when there are filler
	 * bytes in the frame.
	 */
	mh = (struct mrp_msg_hdr *) *msg_ptr;
	if (MRP_END_MARK == mh->attrtype &&
	    MRP_END_MARK == mh->attrlen) {
		return -1;
	}

	/* Check whether the attribute type is understood. */
	rc = app->attr_chk(mh->attrtype, mh->attrlen);
	if (rc < 0)
		return -1;

	*msg_ptr += sizeof(struct mrp_msg_hdr);
	while (*msg_ptr < (msg_eof - 3)) {
		rc = mrp_parse_events(app, msg_ptr, msg_eof,
			mh->attrlen, mh->attrtype);
		if (rc < 0)
			return rc;

		/* End mark terminates the vector list. */
		rc = mrp_parse_end_mark(msg_ptr, msg_eof);
		if (rc <= 0)
			return rc;
	}
	return 0;
}

static int mrp_rx(struct mrp_applicant *app, u8 *data, int len)
{
	struct mrp_pdu_hdr *ph;
	u8 *msg_ptr;
	u8 *msg_eof;
	int rc;

	ph = (struct mrp_pdu_hdr *) data;
	if (ph->version != app->app->version)
		return -1;

	msg_ptr = (u8 *)(ph + 1);
	msg_eof = msg_ptr + len - sizeof(struct mrp_pdu_hdr);

	while (msg_ptr < (msg_eof - 2)) {

		/* rLA! applies to the attribute type declared. */
		app->lva.rx = 0;

		rc = mrp_parse_msg(app, &msg_ptr, msg_eof);
		if (rc < 0)
			return rc;

		/* End mark terminates the frame. */
		rc = mrp_parse_end_mark(&msg_ptr, msg_eof);
		if (rc <= 0)
			return rc;
	}
	return 0;
}

static int mrp_txpdu(struct mrp_applicant *app, u8 *msg_buf, u8 *msg_ptr,
	u8 *msg_eof, int err)
{
	/* Have something to send. */
	if (msg_ptr != msg_buf) {
#ifndef DBG_MRP_RX
		struct mrp_info *mrp = app->parent;
#endif

		/* Reset txLA flags if not txLAF. */
		if (!err)
			app->lva.tx = 0;
		if (msg_ptr <= (msg_eof - 2)) {
			*msg_ptr++ = MRP_END_MARK;
			*msg_ptr++ = MRP_END_MARK;
		}
		skb_put(app->pdu, msg_ptr - msg_buf);
		dev_hard_header(app->pdu, app->dev,
			ntohs(app->app->pkttype.type),
			app->app->group_address, app->dev->dev_addr,
			app->pdu->len);
#if 1
		if (app->app->type == 2 && 1 == app->port && app->rla_jiffies) {
if (jiffies - app->rla_jiffies > 20)
dbg_msg("p:%d %d %lu: \n", app->port, app->app->type, jiffies - app->rla_jiffies);
app->rla_jiffies = 0;
#endif
		}
#ifdef DBG_MRP_TX
		for (err = 0; err < app->pdu->len; err++) {
			dbg_msg("%02x ", app->pdu->data[err]);
			if ((err % 16) == 15)
				dbg_msg("\n");
		}
		if ((err % 16))
			dbg_msg("\n");
#endif
#ifdef DBG_MRP_RX
		app->rxpdu(app, &app->pdu->data[14], app->pdu->len - 14);
		kfree_skb(app->pdu);
#else
#ifdef MRP_PASSTHRU
		kfree_skb(app->pdu);
#else
		err = proc_mrp_xmit(mrp, app->port, app->pdu);
#endif
#endif
		app->pdu = NULL;
	} else {
		kfree_skb(app->pdu);
		app->pdu = NULL;
	}
	return 0;
}

static int mrp_req_new(struct mrp_applicant *app,
	const void *value, u8 len, u8 type, u8 event)
{
	struct mrp_attr *attr;

	spin_lock_bh(&app->lock);
	attr = mrp_attr_create(app, value, len, type);
	if (!attr) {
		spin_unlock_bh(&app->lock);
		return -ENOMEM;
	}

	/* Not newly created attribute does not update the rest of data. */
	if (MRP_EVENT_NEW == event && app->attr_upd)
		app->attr_upd(value, attr);
	if (mrp_attr_event(app, attr, event))
		mrp_join_timer_arm(app);
	spin_unlock_bh(&app->lock);
	return 0;
}

static void mrp_req_leave(struct mrp_applicant *app,
	const void *value, u8 len, u8 type)
{
	struct mrp_attr *attr;

	spin_lock_bh(&app->lock);
	attr = mrp_attr_lookup(app, value, len, type);
	if (!attr) {
		spin_unlock_bh(&app->lock);
		return;
	}
	if (mrp_attr_event(app, attr, MRP_EVENT_LV))
		mrp_join_timer_arm(app);
	spin_unlock_bh(&app->lock);
}

#ifndef NETIF_F_HW_VLAN_CTAG_FILTER
static struct rnd_state rnd;
#endif

static int mrp_init_applicant(struct mrp_port *port, struct net_device *dev,
	struct mrp_application *appl)
{
	struct mrp_applicant *app;
	int err;

	err = -ENOMEM;
	app = kzalloc(sizeof(*app), GFP_KERNEL);
	if (!app)
		goto err2;

	err = dev_mc_add(dev, appl->group_address);
	if (err < 0)
		goto err3;

#ifndef NETIF_F_HW_VLAN_CTAG_FILTER
	app->rnd = &rnd;
#endif
	app->dev = dev;
	app->app = appl;
	app->mad = RB_ROOT;
	app->p2p_mac = 1;
	spin_lock_init(&app->lock);
	skb_queue_head_init(&app->queue);
	rcu_assign_pointer(port->applicants[appl->type], app);
	INIT_WORK(&app->join_work, mrp_join_timer_work);
	setup_timer(&app->join_timer, mrp_join_timer, (unsigned long)app);
#if 0
	mrp_join_timer_arm(app);
#endif

	INIT_WORK(&app->periodic_work, mrp_periodic_timer_work);
	setup_timer(&app->periodic_timer, mrp_periodic_timer,
		    (unsigned long)app);
	app->periodic.state = MRP_TIMER_ACTIVE;
#if 0
	mrp_periodic_timer_arm(app);
#endif
#if 0
	mrp_periodic_event(app, MRP_EVENT_PERIODIC_DISABLE);
#endif

	INIT_WORK(&app->leave_work, mrp_leave_timer_work);
	setup_timer(&app->leave_timer, mrp_leave_timer, (unsigned long)app);

	INIT_WORK(&app->lva_work, mrp_lva_timer_work);
	setup_timer(&app->lva_timer, mrp_lva_timer, (unsigned long)app);
	app->lva.state = MRP_TIMER_PASSIVE;
	mrp_lva_timer_arm(app);
	return 0;

err3:
	kfree(app);
err2:
	return err;
}

static void mrp_uninit_applicant(struct mrp_port *port,
	struct mrp_application *appl)
{
	struct mrp_applicant *app = rtnl_dereference(
		port->applicants[appl->type]);

	RCU_INIT_POINTER(port->applicants[appl->type], NULL);

	/* Delete timer and generate a final TX event to flush out
	 * all pending messages before the applicant is gone.
	 */

	/* TX event actually may arm several timers. */
	spin_lock_bh(&app->lock);
	mrp_mad_event(app, MRP_EVENT_TX);
	spin_unlock_bh(&app->lock);

	del_timer_sync(&app->join_timer);
	del_timer_sync(&app->periodic_timer);
	del_timer_sync(&app->leave_timer);
	del_timer_sync(&app->lva_timer);
	flush_work(&app->join_work);
	flush_work(&app->periodic_work);
	flush_work(&app->leave_work);
	flush_work(&app->lva_work);

	dev_mc_del(app->dev, appl->group_address);
	kfree_rcu(app, rcu);
}

