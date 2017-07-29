/*
 *	IEEE 802.1Q Multiple VLAN Registration Protocol (MVRP)
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


#ifndef ETH_P_MVRP
#define ETH_P_MVRP		0x88F5
#endif


#define MRP_MVRP_ADDRESS	{ 0x01, 0x80, 0xc2, 0x00, 0x00, 0x21 }

enum mvrp_attributes {
	MVRP_ATTR_INVALID,
	MVRP_ATTR_VID,
	__MVRP_ATTR_MAX
};
#define MVRP_ATTR_MAX	(__MVRP_ATTR_MAX - 1)

static struct mrp_application vlan_mrp_app __read_mostly = {
	.type		= MRP_APPLICATION_MVRP,
	.maxattr	= MVRP_ATTR_MAX,
	.pkttype.type	= htons(ETH_P_MVRP),
	.group_address	= MRP_MVRP_ADDRESS,
	.version	= 0,
};

static int mvrp_attr_chk(u8 attrtype, u8 attrlen)
{
	if (MVRP_ATTR_VID == attrtype && 2 == attrlen)
		return 0;
	return -1;
}

static int mvrp_rxpdu(struct mrp_applicant *app, u8 *data, int len)
{
	return mrp_rx(app, data, len);
}

static int mvrp_txpdu(struct mrp_applicant *app)
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
		MVRP_ATTR_VID, 2, MVRP_VID_OPT_MAX, MVRP_VID_MIN);

	/* LeaveAll for VLAN attribute type sent. */
	if (bytes) {
		msg_ptr += bytes;
		app->lva.tx &= ~(1 << (MVRP_ATTR_VID - 1));
	}

	return mrp_txpdu(app, msg_buf, msg_ptr, msg_eof, err);
}

static int mvrp_req_join(struct mrp_applicant *app, u16 vid)
{
	__be16 vlan_id = htons(vid);

	return mrp_req_new(app, &vlan_id, sizeof(vlan_id), MVRP_ATTR_VID,
		MRP_EVENT_JOIN);
}

static void mvrp_req_leave(struct mrp_applicant *app, u16 vid)
{
	__be16 vlan_id = htons(vid);

	mrp_req_leave(app, &vlan_id, sizeof(vlan_id), MVRP_ATTR_VID);
}

static void mvrp_init_application(struct mrp_applicant *app, void *mrp, u8 port,
	void (*acton)(struct mrp_applicant *app, struct mrp_attr *attr))
{
	app->parent = mrp;
	app->port = port;
	app->attrval_inc = mrp_attrvalue_inc;
	app->attr_chk = mvrp_attr_chk;
	app->attr_cmp = mrp_attr_cmp;
	app->attr_len = mrp_attr_len;
	app->attr_type = mrp_attr_type;
	app->rxpdu = mvrp_rxpdu;
	app->txpdu = mvrp_txpdu;
	app->acton = acton;
}

