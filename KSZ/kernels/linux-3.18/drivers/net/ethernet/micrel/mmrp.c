/*
 *	IEEE 802.1Q Multiple MAC Registration Protocol (MMRP)
 *
 *	Copyright (c) 2016 Microchip Technology Inc.
 *
 *	Copyright (c) 2012 Massachusetts Institute of Technology
 *
 *	Adapted from code in net/8021q/vlan_gvrp.c
 *	Copyright (c) 2008 Patrick McHardy <kaber@trash.net>
 *
 *	This program is free software; you can redistribute it and/or
 *	modify it under the terms of the GNU General Public License
 *	version 2 as published by the Free Software Foundation.
 */


#ifndef ETH_P_MMRP
#define ETH_P_MMRP		0x88F6
#endif

#define MRP_MMRP_ADDRESS	{ 0x01, 0x80, 0xc2, 0x00, 0x00, 0x20 }

enum mmrp_attributes {
	MMRP_ATTR_INVALID,
	MMRP_ATTR_SVC,
	MMRP_ATTR_MAC,
	__MMRP_ATTR_MAX
};
#define MMRP_ATTR_MAX	(__MMRP_ATTR_MAX - 1)

static struct mrp_application mac_mrp_app __read_mostly = {
	.type		= MRP_APPLICATION_MMRP,
	.maxattr	= MMRP_ATTR_MAX,
	.pkttype.type	= htons(ETH_P_MMRP),
	.group_address	= MRP_MMRP_ADDRESS,
	.version	= 0,
};

static int mmrp_attr_chk(u8 attrtype, u8 attrlen)
{
	if (MMRP_ATTR_MAC == attrtype && ETH_ALEN == attrlen)
		return 0;
	else if (MMRP_ATTR_SVC == attrtype && 1 == attrlen)
		return 0;
	return -1;
}

static int mmrp_rxpdu(struct mrp_applicant *app, u8 *data, int len)
{
	return mrp_rx(app, data, len);
}

static int mmrp_txpdu(struct mrp_applicant *app)
{
	int bytes;
	int err;
	u8 *msg_buf;
	u8 *msg_eof;
	u8 *msg_ptr;

	err = mrp_pdu_init(app);
	if (err < 0)
		return err;

	msg_buf = app->pdu->data;
	msg_eof = msg_buf + app->dev->mtu;
	msg_buf++;
	msg_ptr = msg_buf;

	err = mrp_tx(app, msg_ptr, msg_eof, &bytes,
		MMRP_ATTR_MAC, ETH_ALEN, MMRP_MAC_OPT_MAX, MMRP_MAC_MIN);

	/* LeaveAll for MAC attribute type sent. */
	if (bytes) {
		msg_ptr += bytes;
		app->lva.tx &= ~(1 << (MMRP_ATTR_MAC - 1));

		/* No more space. */
		if (-1 == err)
			goto send;
	}

	err = mrp_tx(app, msg_ptr, msg_eof, &bytes,
		MMRP_ATTR_SVC, 1, MMRP_SVC_OPT_MAX, MMRP_SVC_MIN);

	/* LeaveAll for SVC attribute type sent. */
	if (bytes) {
		msg_ptr += bytes;
		app->lva.tx &= ~(1 << (MMRP_ATTR_SVC - 1));

		/* No more space. */
		if (-1 == err)
			goto send;
	}

send:
	return mrp_txpdu(app, msg_buf, msg_ptr, msg_eof, err);
}

static int mmrp_req_join_mac(struct mrp_applicant *app, u8 *addr)
{
	return mrp_req_new(app, addr, ETH_ALEN, MMRP_ATTR_MAC,
		MRP_EVENT_JOIN);
}

#if 0
static int mmrp_req_join_svc(struct mrp_applicant *app, u8 svc)
{
	return mrp_req_new(app, &svc, 1, MMRP_ATTR_SVC,
		MRP_EVENT_JOIN);
}
#endif

static void mmrp_req_leave_mac(struct mrp_applicant *app, u8 *addr)
{
	mrp_req_leave(app, addr, ETH_ALEN, MMRP_ATTR_MAC);
}

#if 0
static void mmrp_req_leave_svc(struct mrp_applicant *app, u8 svc)
{
	mrp_req_leave(app, &svc, 1, MMRP_ATTR_SVC);
}
#endif

static void mmrp_init_application(struct mrp_applicant *app, void *mrp, u8 port,
	void (*acton)(struct mrp_applicant *app, struct mrp_attr *attr))
{
	app->parent = mrp;
	app->port = port;
	app->attrval_inc = mrp_attrvalue_inc;
	app->attr_chk = mmrp_attr_chk;
	app->attr_cmp = mrp_attr_cmp;
	app->attr_len = mrp_attr_len;
	app->attr_type = mrp_attr_type;
	app->rxpdu = mmrp_rxpdu;
	app->txpdu = mmrp_txpdu;
	app->acton = acton;
}

