/**
 * Microchip DLR driver API code
 *
 * Copyright (c) 2014-2017 Microchip Technology Inc.
 *	Tristram Ha <Tristram.Ha@microchip.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */


#include <stdint.h>
#include <net/if.h>
#include <sys/ioctl.h>

#include "ksz_dlr_api.h"

struct dlr_msg {
	struct ksz_net_hdr hdr;
	union dlr_data data;
} __packed;


/* Used to indicate which APIs are supported. */
static int dlr_version;

/* Used to indicate how many ports are in the switch. */
static int dlr_ports;

static u16 net_seqid;

static int set_net_req(void *ptr, u8 mod, u8 svc, u8 class, u8 id,
	void *data, size_t data_size)
{
	struct ksz_net_msg *msg = ptr;
	int len = sizeof(struct ksz_net_hdr);

	msg->hdr.mod = mod;
	msg->hdr.svc = svc;
	msg->hdr.class = class;
	msg->hdr.id = id;
	if (data) {
		memcpy(&msg->data, data, data_size);
		len += data_size;
	}
	msg->hdr.sequenceId = htons(net_seqid);
	net_seqid++;
	msg->hdr.messageLength = htons(len);
	return len;
}  /* set_net_req */

static int r_dlr_byte(void *fd,
	u8 *byte)
{
	struct ksz_net_info *net = fd;
	struct dlr_msg *msg = net->msg;

	if (net->len - sizeof(struct ksz_net_hdr) >= sizeof(u8)) {
		*byte = msg->data.byte;
		return 1;
	}
	return 0;
}  /* r_dlr_byte */

static void w_dlr_byte(void *fd,
	u8 *byte, u8 id)
{
	struct dlr_msg msg;
	int len;
	struct ksz_net_info *net = fd;

	len = set_net_req(&msg, DEV_MOD_DLR,
		0, 0, id,
		byte, sizeof(u8));
	net->send(&msg, net->family, len, net->addr, net->addrlen);
}  /* w_dlr_byte */

static int r_dlr_word(void *fd,
	u16 *word)
{
	struct ksz_net_info *net = fd;
	struct dlr_msg *msg = net->msg;

	if (net->len - sizeof(struct ksz_net_hdr) >= sizeof(u16)) {
		*word = msg->data.word;
		return 1;
	}
	return 0;
}  /* r_dlr_word */

static void w_dlr_word(void *fd,
	u16 *word, u8 id)
{
	struct dlr_msg msg;
	int len;
	struct ksz_net_info *net = fd;

	len = set_net_req(&msg, DEV_MOD_DLR,
		0, 0, id,
		word, sizeof(u16));
	net->send(&msg, net->family, len, net->addr, net->addrlen);
}  /* w_dlr_word */

static int r_dlr_dword(void *fd,
	u32 *dword)
{
	struct ksz_net_info *net = fd;
	struct dlr_msg *msg = net->msg;

	if (net->len - sizeof(struct ksz_net_hdr) >= sizeof(u32)) {
		*dword = msg->data.dword;
		return 1;
	}
	return 0;
}  /* r_dlr_dword */

static void w_dlr_dword(void *fd,
	u32 *dword, u8 id)
{
	struct dlr_msg msg;
	int len;
	struct ksz_net_info *net = fd;

	len = set_net_req(&msg, DEV_MOD_DLR,
		0, 0, id,
		dword, sizeof(u32));
	net->send(&msg, net->family, len, net->addr, net->addrlen);
}  /* w_dlr_dword */

static int r_dlr_node(void *fd,
	struct ksz_dlr_active_node *node)
{
	struct ksz_net_info *net = fd;
	struct dlr_msg *msg = net->msg;

	if (net->len - sizeof(struct ksz_net_hdr) >=
	    sizeof(struct ksz_dlr_active_node)) {
		memcpy(node, &msg->data, sizeof(struct ksz_dlr_active_node));
		return 1;
	}
	return 0;
}  /* r_dlr_node */

static void w_dlr_node(void *fd,
	struct ksz_dlr_active_node *node, u8 id)
{
	struct dlr_msg msg;
	int len;
	struct ksz_net_info *net = fd;

	len = set_net_req(&msg, DEV_MOD_DLR,
		0, 0, id,
		node, sizeof(struct ksz_dlr_active_node));
	net->send(&msg, net->family, len, net->addr, net->addrlen);
}  /* w_dlr_node */

static int r_dlr_revision(void *fd,
	u16 *rev)
{
	return r_dlr_word(fd, rev);
}  /* r_dlr_revision */

static void w_dlr_revision(void *fd,
	u16 *rev)
{
	struct dlr_msg msg;
	int len;
	struct ksz_net_info *net = fd;

	len = set_net_req(&msg, DEV_MOD_DLR,
		0, DLR_GET_REVISION, 0,
		rev, sizeof(u16));
	net->send(&msg, net->family, len, net->addr, net->addrlen);
}  /* w_dlr_revision */

static int r_dlr_all(void *fd,
	struct ksz_dlr_gateway_capable *capable)
{
	struct ksz_net_info *net = fd;
	struct dlr_msg *msg = net->msg;

	if (net->len - sizeof(struct ksz_net_hdr) >=
	    sizeof(struct ksz_dlr_gateway_capable)) {
		memcpy(capable, &msg->data.gateway,
			sizeof(struct ksz_dlr_gateway_capable));
		return 1;
	}
	return 0;
}  /* r_dlr_all */

static void w_dlr_all(void *fd,
	struct ksz_dlr_gateway_capable *capable)
{
	struct dlr_msg msg;
	int len;
	struct ksz_net_info *net = fd;

	len = set_net_req(&msg, DEV_MOD_DLR,
		0, 0, 0,
		capable, sizeof(struct ksz_dlr_gateway_capable));
	net->send(&msg, net->family, len, net->addr, net->addrlen);
}  /* w_dlr_all */

static int r_dlr_topology(void *fd,
	u8 *topology)
{
	return r_dlr_byte(fd, topology);
}  /* r_dlr_topology */

static void w_dlr_topology(void *fd,
	u8 *topology)
{
	w_dlr_byte(fd, topology, DLR_GET_NETWORK_TOPOLOGY);
}  /* w_dlr_topology */

static int r_dlr_network(void *fd,
	u8 *network)
{
	return r_dlr_byte(fd, network);
}  /* r_dlr_network */

static void w_dlr_network(void *fd,
	u8 *network)
{
	w_dlr_byte(fd, network, DLR_GET_NETWORK_STATUS);
}  /* w_dlr_network */

static int r_dlr_super_status(void *fd,
	u8 *status)
{
	return r_dlr_byte(fd, status);
}  /* r_dlr_super_status */

static void w_dlr_super_status(void *fd,
	u8 *status)
{
	w_dlr_byte(fd, status, DLR_GET_RING_SUPERVISOR_STATUS);
}  /* w_dlr_super_status */

static int r_dlr_super_cfg(void *fd,
	struct ksz_dlr_super_cfg *cfg)
{
	struct ksz_net_info *net = fd;
	struct dlr_msg *msg = net->msg;

	if (net->len - sizeof(struct ksz_net_hdr) >=
	    sizeof(struct ksz_dlr_super_cfg)) {
		memcpy(cfg, &msg->data, sizeof(struct ksz_dlr_super_cfg));
		return 1;
	}
	return 0;
}  /* r_dlr_super_cfg */

static void w_dlr_super_cfg(void *fd,
	struct ksz_dlr_super_cfg *cfg)
{
	struct dlr_msg msg;
	int len;
	struct ksz_net_info *net = fd;

	len = set_net_req(&msg, DEV_MOD_DLR,
		0, 0, DLR_SET_RING_SUPERVISOR_CONFIG,
		cfg, sizeof(struct ksz_dlr_super_cfg));
	net->send(&msg, net->family, len, net->addr, net->addrlen);
}  /* w_dlr_super_cfg */

static int r_dlr_ring_fault_cnt(void *fd,
	u16 *cnt)
{
	return r_dlr_word(fd, cnt);
}  /* r_dlr_ring_fault_cnt */

static void w_dlr_ring_fault_cnt(void *fd,
	u16 *cnt)
{
	w_dlr_word(fd, cnt, DLR_SET_RING_FAULT_COUNT);
}  /* w_dlr_ring_fault_cnt */

static int r_dlr_active_node(void *fd,
	struct ksz_dlr_active_node *node)
{
	struct ksz_net_info *net = fd;
	struct dlr_msg *msg = net->msg;

	if (net->len - sizeof(struct ksz_net_hdr) >=
	    sizeof(struct ksz_dlr_active_node) * 2) {
		memcpy(node, &msg->data, sizeof(struct ksz_dlr_active_node)
			* 2);
		return 1;
	}
	return 0;
}  /* r_dlr_active_node */

static void w_dlr_active_node(void *fd,
	struct ksz_dlr_active_node *node)
{
	struct dlr_msg msg;
	int len;
	struct ksz_net_info *net = fd;

	len = set_net_req(&msg, DEV_MOD_DLR,
		0, 0, DLR_GET_LAST_ACTIVE_NODE_ON_PORT_1,
		node, sizeof(struct ksz_dlr_active_node) * 2);
	net->send(&msg, net->family, len, net->addr, net->addrlen);
}  /* w_dlr_active_node */

static int r_dlr_ring_part_cnt(void *fd,
	u16 *cnt)
{
	return r_dlr_word(fd, cnt);
}  /* r_dlr_ring_part_cnt */

static void w_dlr_ring_part_cnt(void *fd,
	u16 *cnt)
{
	w_dlr_word(fd, cnt, DLR_GET_RING_PARTICIPANTS_COUNT);
}  /* w_dlr_ring_part_cnt */

static int r_dlr_ring_part_list(void *fd,
	struct ksz_dlr_active_node *node, u16 size)
{
	struct ksz_net_info *net = fd;
	struct dlr_msg *msg = net->msg;

	if (net->len - sizeof(struct ksz_net_hdr) >= size) {
		memcpy(node, &msg->data, size);
		return 1;
	}
	return 0;
}  /* r_dlr_ring_part_list */

static void w_dlr_ring_part_list(void *fd,
	struct ksz_dlr_active_node *node, u16 size)
{
	struct dlr_msg msg;
	int len;
	struct ksz_net_info *net = fd;

	len = set_net_req(&msg, DEV_MOD_DLR,
		0, 0, DLR_GET_RING_PARTICIPANTS_LIST,
		node, size);
	net->send(&msg, net->family, len, net->addr, net->addrlen);
}  /* w_dlr_ring_part_list */

static int r_dlr_active_super_addr(void *fd,
	struct ksz_dlr_active_node *node)
{
	return r_dlr_node(fd, node);
}  /* r_dlr_active_super_addr */

static void w_dlr_active_super_addr(void *fd,
	struct ksz_dlr_active_node *node)
{
	w_dlr_node(fd, node, DLR_GET_ACTIVE_SUPERVISOR_ADDRESS);
}  /* w_dlr_active_super_addr */

static int r_dlr_active_super_prec(void *fd,
	u8 *prec)
{
	return r_dlr_byte(fd, prec);
}  /* r_dlr_active_super_prec */

static void w_dlr_active_super_prec(void *fd,
	u8 *prec)
{
	w_dlr_byte(fd, prec, DLR_GET_ACTIVE_SUPERVISOR_PRECEDENCE);
}  /* w_dlr_active_super_prec */

static int r_dlr_cap(void *fd,
	u32 *flags)
{
	return r_dlr_dword(fd, flags);
}  /* r_dlr_cap */

static void w_dlr_cap(void *fd,
	u32 *flags)
{
	w_dlr_dword(fd, flags, DLR_GET_CAPABILITY_FLAGS);
}  /* w_dlr_cap */

static int r_dlr_verify_fault(void *fd,
	u8 *err)
{
	return r_dlr_byte(fd, err);
}  /* r_dlr_verify_fault */

static void w_dlr_verify_fault(void *fd,
	u8 *err)
{
	struct dlr_msg msg;
	int len;
	struct ksz_net_info *net = fd;

	len = set_net_req(&msg, DEV_MOD_DLR,
		SVC_DLR_VERIFY_FAULT_LOCATION, 0, 0,
		err, sizeof(u8));
	net->send(&msg, net->family, len, net->addr, net->addrlen);
}  /* w_dlr_verify_fault */

static int r_dlr_clear_rapid_fault(void *fd,
	u8 *err)
{
	return r_dlr_byte(fd, err);
}  /* r_dlr_clear_rapid_fault */

static void w_dlr_clear_rapid_fault(void *fd,
	u8 *err)
{
	struct dlr_msg msg;
	int len;
	struct ksz_net_info *net = fd;

	len = set_net_req(&msg, DEV_MOD_DLR,
		SVC_DLR_CLEAR_RAPID_FAULTS, 0, 0,
		err, sizeof(u8));
	net->send(&msg, net->family, len, net->addr, net->addrlen);
}  /* w_dlr_clear_rapid_fault */

static int r_dlr_restart_sign_on(void *fd,
	u8 *err)
{
	return r_dlr_byte(fd, err);
}  /* r_dlr_restart_sign_on */

static void w_dlr_restart_sign_on(void *fd,
	u8 *err)
{
	struct dlr_msg msg;
	int len;
	struct ksz_net_info *net = fd;

	len = set_net_req(&msg, DEV_MOD_DLR,
		SVC_DLR_RESTART_SIGN_ON, 0, 0,
		err, sizeof(u8));
	net->send(&msg, net->family, len, net->addr, net->addrlen);
}  /* w_dlr_restart_sign_on */

static int r_dlr_clear_gateway_fault(void *fd,
	u8 *err)
{
	return r_dlr_byte(fd, err);
}  /* r_dlr_clear_gateway_fault */

static void w_dlr_clear_gateway_fault(void *fd,
	u8 *err)
{
	struct dlr_msg msg;
	int len;
	struct ksz_net_info *net = fd;

	len = set_net_req(&msg, DEV_MOD_DLR,
		SVC_DLR_CLEAR_GATEWAY_PARTIAL_FAULT, 0, 0,
		err, sizeof(u8));
	net->send(&msg, net->family, len, net->addr, net->addrlen);
}  /* w_dlr_clear_gateway_fault */

static int r_dlr_ip_addr(void *fd,
	struct ksz_dlr_active_node *node)
{
	return r_dlr_node(fd, node);
}  /* r_dlr_ip_addr */

static void w_dlr_ip_addr(void *fd,
	struct ksz_dlr_active_node *node)
{
	w_dlr_node(fd, node, DLR_SET_IP_ADDRESS);
}  /* w_dlr_ip_addr */

struct dlr_info {
	u8 network;
	u8 prec;
	u8 super_status;
	u8 topology;
	u8 err;
	u16 fault_cnt;
	u16 node_cnt;
	u16 rev;
	u32 flags;
	struct ksz_dlr_gateway_capable capable;
	struct ksz_dlr_super_cfg super_cfg;
	struct ksz_dlr_active_node last_active[2];
	struct ksz_dlr_active_node super_addr;

	struct ksz_dlr_active_node node;

	struct ksz_dlr_active_node *nodes;
	u16 max_cnt;
};

int proc_dlr_msg(void *fd, struct dlr_info *info)
{
	struct ksz_net_info *net = fd;
	struct dlr_msg *msg = net->msg;
	int proc;
	int rc = -1;

	proc = 1;
	switch (msg->hdr.class) {
	case DLR_GET_REVISION:
		rc = r_dlr_revision(fd, &info->rev);
		break;
	default:
		proc = 0;
		break;
	}
	if (proc)
		return rc;
	proc = 1;
	switch (msg->hdr.svc) {
	case SVC_DLR_VERIFY_FAULT_LOCATION:
		rc = r_dlr_verify_fault(fd, &info->err);
		break;
	case SVC_DLR_CLEAR_RAPID_FAULTS:
		rc = r_dlr_clear_rapid_fault(fd, &info->err);
		break;
	case SVC_DLR_RESTART_SIGN_ON:
		rc = r_dlr_restart_sign_on(fd, &info->err);
		break;
	case SVC_DLR_CLEAR_GATEWAY_PARTIAL_FAULT:
		rc = r_dlr_clear_gateway_fault(fd, &info->err);
		break;
	default:
		proc = 0;
		break;
	}
	if (proc)
		return rc;
	switch (msg->hdr.id) {
	case 0:
		rc = r_dlr_all(fd, &info->capable);
		break;
	case DLR_GET_NETWORK_TOPOLOGY:
		rc = r_dlr_topology(fd, &info->topology);
		break;
	case DLR_GET_NETWORK_STATUS:
		rc = r_dlr_network(fd, &info->network);
		break;
	case DLR_GET_RING_SUPERVISOR_STATUS:
		rc = r_dlr_super_status(fd, &info->super_status);
		break;
	case DLR_SET_RING_SUPERVISOR_CONFIG:
		rc = r_dlr_super_cfg(fd, &info->super_cfg);
		break;
	case DLR_SET_RING_FAULT_COUNT:
		rc = r_dlr_ring_fault_cnt(fd, &info->fault_cnt);
		break;
	case DLR_GET_LAST_ACTIVE_NODE_ON_PORT_1:
		rc = r_dlr_active_node(fd, info->last_active);
		break;
	case DLR_GET_RING_PARTICIPANTS_COUNT:
		rc = r_dlr_ring_part_cnt(fd, &info->node_cnt);
		break;
	case DLR_GET_RING_PARTICIPANTS_LIST:
		rc = r_dlr_ring_part_list(fd, info->nodes,
			sizeof(struct ksz_dlr_active_node) * info->node_cnt);
		break;
	case DLR_GET_ACTIVE_SUPERVISOR_ADDRESS:
		rc = r_dlr_active_super_addr(fd, &info->super_addr);
		break;
	case DLR_GET_ACTIVE_SUPERVISOR_PRECEDENCE:
		rc = r_dlr_active_super_prec(fd, &info->prec);
		break;
	case DLR_GET_CAPABILITY_FLAGS:
		rc = r_dlr_cap(fd, &info->flags);
		break;
	case DLR_SET_IP_ADDRESS:
		rc = r_dlr_ip_addr(fd, &info->node);
		break;
	default:
		proc = 0;
		break;
	}
	return rc;
}  /* proc_dlr_msg */

