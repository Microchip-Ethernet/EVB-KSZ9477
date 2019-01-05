/**
 * Microchip DLR code
 *
 * Copyright (c) 2015-2017 Microchip Technology Inc.
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


#if 0
#define DBG_DLR_STATE
#endif

#if 0
#define DBG_DLR_BEACON
#endif
#if 0
#define DBG_DLR_OPER
#endif
#if 0
#define DBG_DLR_HW_OPER
#endif
#if 0
#define DBG_DLR_SUPERVISOR
#endif
#if 0
#define DBG_DLR_ANN_SIGNON
#endif
#if 0
#define DBG_DLR_SIGNON
#endif


static u8 MAC_ADDR_BEACON[] = { 0x01, 0x21, 0x6C, 0x00, 0x00, 0x01 };
static u8 MAC_ADDR_SIGNON[] = { 0x01, 0x21, 0x6C, 0x00, 0x00, 0x02 };
static u8 MAC_ADDR_ANNOUNCE[] = { 0x01, 0x21, 0x6C, 0x00, 0x00, 0x03 };
static u8 MAC_ADDR_ADVERTISE[] = { 0x01, 0x21, 0x6C, 0x00, 0x00, 0x04 };
static u8 MAC_ADDR_LEARNING_UPDATE[] = { 0x01, 0x21, 0x6C, 0x00, 0x00, 0x05 };


#define BEACON_TICK			5
#define BEACON_INTERVAL			(BEACON_TICK * 10)

enum {
	DLR_ANNOUNCE_NODE,
	DLR_BEACON_NODE,
	DLR_SUPERVISOR,
	DLR_ACTIVE_SUPERVISOR,
};

enum {
	DLR_BEGIN,

	DLR_IDLE_STATE,
	DLR_FAULT_STATE,
	DLR_NORMAL_STATE,
	DLR_ACTIVE_STATE,
	DLR_ACTIVE_FAULT_STATE,
	DLR_ACTIVE_NORMAL_STATE,
	DLR_BACKUP_STATE,
	DLR_PREPARE_STATE,
	DLR_RESTART_STATE,
};

static int dbg_leak = 5;

#ifdef DBG_DLR_BEACON
static int dbg_bcn;
#endif

#ifdef DBG_DLR_ANN_SIGNON
static int dbg_ann;
#endif

#ifdef CONFIG_HAVE_ACL_HW

/* Lower action index has higher precedence. */
#define DLR_BEACON_DROP_ACL_ACTION	12
#define DLR_NO_ACL_ACTION		13
#define DLR_DROP_ACL_ACTION		15

#define DLR_BEACON_DROP_ACL_RULE	12
#define DLR_BEACON_ACL_RULE		13
#define DLR_DROP_SELF_ACL_RULE		15
#define DLR_BEACON_TIMEOUT_ACL_RULE	14

#define DLR_BEACON_DROP_ACL_ENTRY	12
#define DLR_BEACON_ACL_ENTRY		13
#define DLR_DROP_SELF_ACL_ENTRY		15
#define DLR_TIMEOUT_ACL_ENTRY		14

static void setup_acl_beacon(struct ksz_dlr_info *info, int port)
{
	struct ksz_sw *sw = info->sw_dev;
	struct ksz_port_cfg *cfg = &sw->info->port_cfg[port];
	struct ksz_acl_table *acl;
	int i = DLR_BEACON_DROP_ACL_RULE;
	int first_rule = i;
	int ruleset = (3 << i);

	acl = &cfg->acl_info[i];
	mutex_lock(&sw->acllock);
	if (!memcmp(acl->mac, info->attrib.active_super_addr.addr, ETH_ALEN) &&
	    acl->first_rule == first_rule)
		goto done;

	acl->first_rule = first_rule;
	acl->ruleset = ruleset;
	sw_w_acl_ruleset(sw, port, i, acl);

	acl->mode = ACL_MODE_LAYER_2;
	acl->enable = ACL_ENABLE_2_BOTH;
	acl->equal = 1;
	acl->src = 1;
	memcpy(acl->mac, info->attrib.active_super_addr.addr, ETH_ALEN);
	memcpy(info->beacon_addr, acl->mac, ETH_ALEN);
	acl->eth_type = DLR_TAG_TYPE;
	sw_w_acl_rule(sw, port, i, acl);

done:
	mutex_unlock(&sw->acllock);
}  /* setup_acl_beacon */

static void setup_acl_beacon_timeout(struct ksz_dlr_info *info, int port)
{
	struct ksz_sw *sw = info->sw_dev;
	struct ksz_port_cfg *cfg = &sw->info->port_cfg[port];
	struct ksz_acl_table *acl;
	int i;
	u8 *addr = MAC_ADDR_BEACON;

	i = DLR_TIMEOUT_ACL_ENTRY;
	mutex_lock(&sw->acllock);
	acl = &cfg->acl_info[i];
	acl->first_rule = DLR_NO_ACL_ACTION;
	acl->ruleset = (1 << i);
	acl->mode = ACL_MODE_LAYER_2;
	acl->enable = ACL_ENABLE_2_COUNT;
	acl->equal = 1;
	acl->src = 0;
	memcpy(acl->mac, addr, ETH_ALEN);
	acl->eth_type = DLR_TAG_TYPE;
	if (info->beacon_timeout > ACL_CNT_M) {
		int cnt = info->beacon_timeout + 500;

		cnt /= 1000;
		acl->cnt = cnt;
		acl->msec = 1;
	} else {
		acl->cnt = info->beacon_timeout;
		acl->msec = 0;
	}
	acl->intr_mode = 0;
	sw_w_acl_table(sw, port, i, acl);
	mutex_unlock(&sw->acllock);
}  /* setup_acl_beacon_timeout */

static void disable_acl_beacon_timeout(struct ksz_dlr_info *info, int port)
{
	struct ksz_sw *sw = info->sw_dev;
	struct ksz_port_cfg *cfg = &sw->info->port_cfg[port];
	struct ksz_acl_table *acl;
	int i = DLR_BEACON_TIMEOUT_ACL_RULE;

	mutex_lock(&sw->acllock);
	acl = &cfg->acl_info[i];
	acl->ruleset = 0;
	sw_w_acl_table(sw, port, i, acl);
	mutex_unlock(&sw->acllock);
}  /* disable_acl_beacon_timeout */

static void setup_acl_beacon_drop(struct ksz_dlr_info *info, int drop)
{
	struct ksz_sw *sw = info->sw_dev;
	struct ksz_port_cfg *cfg;
	struct ksz_acl_table *acl;
	int i = DLR_BEACON_DROP_ACL_ACTION;
	int p;

	for (p = 0; p < 2; p++)
		setup_acl_beacon(info, info->ports[p]);
	mutex_lock(&sw->acllock);
	for (p = 0; p < 2; p++) {
		cfg = &sw->info->port_cfg[info->ports[p]];

		acl = &cfg->acl_info[i];
		acl->map_mode = ACL_MAP_MODE_REPLACE;
		acl->ports = drop & info->member;
		if (!drop)
			acl->map_mode = ACL_MAP_MODE_DISABLE;
		sw_w_acl_action(sw, info->ports[p], i, acl);
	}
	mutex_unlock(&sw->acllock);

	if (drop)
		return;

	/* Ring state may be changed in the beacon. */
	memset(&info->beacon_info[0].last, 0, sizeof(struct ksz_dlr_beacon));
	memset(&info->beacon_info[1].last, 0, sizeof(struct ksz_dlr_beacon));
	info->beacon_info[0].timeout =
	info->beacon_info[1].timeout = 0;
}  /* setup_acl_beacon_drop */

static void setup_acl_self(struct ksz_dlr_info *info, int port)
{
	struct ksz_sw *sw = info->sw_dev;
	struct ksz_port_cfg *cfg = &sw->info->port_cfg[port];
	struct ksz_acl_table *acl;
	int i;

	/* Drop packets sent by self. */
	i = DLR_DROP_SELF_ACL_ENTRY;
	mutex_lock(&sw->acllock);
	acl = &cfg->acl_info[i];
	acl->data[0] = 0xff;
	acl->mode = ACL_MODE_LAYER_2;
	acl->enable = ACL_ENABLE_2_MAC;
	acl->equal = 1;
	acl->src = 1;
	memcpy(acl->mac, info->src_addr, ETH_ALEN);
	acl->eth_type = 0;
	acl->first_rule = DLR_DROP_ACL_ACTION;
	acl->ruleset = (1 << i);
	acl->map_mode = ACL_MAP_MODE_REPLACE;
	acl->ports = sw->HOST_MASK;
	acl->ports = 0;
	sw_w_acl_table(sw, port, i, acl);
	mutex_unlock(&sw->acllock);
}  /* setup_acl_self */

static void dlr_setup_acl(struct ksz_dlr_info *info, int port)
{
	struct ksz_sw *sw = info->sw_dev;
	struct ksz_port_cfg *cfg = &sw->info->port_cfg[port];
	struct ksz_acl_table *acl;
	int i;

	mutex_lock(&sw->acllock);

	/* Use MAC table for beacon forwarding. */
	i = DLR_BEACON_ACL_ENTRY;
	acl = &cfg->acl_info[i];
	acl->mode = ACL_MODE_LAYER_2;
	acl->enable = ACL_ENABLE_2_BOTH;
	acl->equal = 1;
	acl->src = 0;
	memcpy(acl->mac, MAC_ADDR_BEACON, ETH_ALEN);
	acl->eth_type = DLR_TAG_TYPE;
	sw_w_acl_rule(sw, port, i, acl);

	i = DLR_BEACON_ACL_RULE;
	acl = &cfg->acl_info[i];
	acl->first_rule = DLR_NO_ACL_ACTION;
	acl->ruleset = (1 << i);
	sw_w_acl_ruleset(sw, port, i, acl);

	i = DLR_NO_ACL_ACTION;
	acl = &cfg->acl_info[i];
	acl->map_mode = ACL_MAP_MODE_DISABLE;
	acl->ports = 0;
	sw_w_acl_action(sw, port, i, acl);
	mutex_unlock(&sw->acllock);
}  /* dlr_setup_acl */
#endif

static void setup_vlan_table(struct ksz_dlr_info *info, u16 vid, int set)
{
	struct ksz_sw *sw = info->sw_dev;
	u32 ports = 0;

#ifdef DBG_DLR_OPER
	dbg_msg(" %s %d %d\n", __func__, vid, set);
#endif

	/* Do not do anything for VID 0, which is priority tagged frame. */
	if (1 >= vid)
		return;
	if (set)
		ports = sw->HOST_MASK | info->member;
	sw->ops->cfg_vlan(sw, 0, vid, 0, ports);
}  /* setup_vlan_table */

#ifdef CONFIG_HAVE_DLR_HW
static void dlr_hw_set_state(struct ksz_sw *sw, u8 node, u8 ring)
{
	u8 data;

	if (!(sw->features & REDUNDANCY_SUPPORT))
		return;
	data = SW_R(sw, REG_DLR_STATE__1);
	data &= ~DLR_RING_STATE_NORMAL;
	data &= ~(DLR_NODE_STATE_M << DLR_NODE_STATE_S);
	node &= DLR_NODE_STATE_M;
	node <<= DLR_NODE_STATE_S;
	ring &= DLR_RING_STATE_NORMAL;
	data |= node | ring;
	SW_W(sw, REG_DLR_STATE__1, data);
}

static void dlr_hw_set_supervisor(struct ksz_sw *sw, u8 super)
{
	u8 data;
	u8 saved;

	if (!(sw->features & REDUNDANCY_SUPPORT))
		return;
	data = SW_R(sw, REG_DLR_CTRL__1);
	saved = data;
	data &= ~DLR_BEACON_TX_ENABLE;
	data &= ~DLR_BACKUP_AUTO_ON;
	if (DLR_ACTIVE_SUPERVISOR == super)
		data |= DLR_BEACON_TX_ENABLE;
#if 0
/*
 * THa  2016/12/30
 * Occassionally the ACL beacon timeout no longer is triggered after the
 * active supervisor is turned off.  The backup supervisor feature in the
 * switch starts sending beacons, but software has no way to become the
 * active supervisor.  Turning on/off supervisor does not recover from this
 * problem.
 */
	if (DLR_SUPERVISOR == super) {

		/* Turn off previous automatic start first. */
		if (saved & DLR_BACKUP_AUTO_ON) {
			SW_W(sw, REG_DLR_CTRL__1, data);
#ifdef DBG_DLR_HW_OPER
			dbg_msg("  reset backup: %x\n", saved);
#endif
		}
		data |= DLR_BACKUP_AUTO_ON;
	}
#endif
	data |= DLR_ASSIST_ENABLE;
	SW_W(sw, REG_DLR_CTRL__1, data);
#ifdef DBG_DLR_HW_OPER
	dbg_msg("  %s %x\n", __func__, data);
#endif
}

static void dlr_hw_set_dest_addr(struct ksz_sw *sw, u8 *addr)
{
	if (!(sw->features & REDUNDANCY_SUPPORT))
		return;
	sw->reg->w(sw, REG_DLR_DEST_ADDR_0, addr, ETH_ALEN);
}

static void dlr_hw_set_ip_addr(struct ksz_sw *sw, u32 ip_addr)
{
	if (!(sw->features & REDUNDANCY_SUPPORT))
		return;
	sw->reg->w32(sw, REG_DLR_IP_ADDR__4, ip_addr);
}

static void dlr_hw_reset_seq_id(struct ksz_sw *sw)
{
	u8 data;

	if (!(sw->features & REDUNDANCY_SUPPORT))
		return;
	data = SW_R(sw, REG_DLR_CTRL__1);
	SW_W(sw, REG_DLR_CTRL__1, data | DLR_RESET_SEQ_ID);
	SW_W(sw, REG_DLR_CTRL__1, data & ~DLR_RESET_SEQ_ID);
}

static void dlr_hw_set_port_map(struct ksz_sw *sw, u32 ports)
{
	if (!(sw->features & REDUNDANCY_SUPPORT))
		return;
	sw->reg->w32(sw, REG_DLR_PORT_MAP__4, ports);
}

static void dlr_hw_set_precedence(struct ksz_sw *sw, u8 precedence)
{
	if (!(sw->features & REDUNDANCY_SUPPORT))
		return;
	sw->reg->w8(sw, REG_DLR_PRECEDENCE__1, precedence);
}

static void dlr_hw_set_interval(struct ksz_sw *sw, u16 interval)
{
	if (!(sw->features & REDUNDANCY_SUPPORT))
		return;
	sw->reg->w32(sw, REG_DLR_BEACON_INTERVAL__4, interval);
}

static void dlr_hw_set_timeout(struct ksz_sw *sw, u32 timeout)
{
	if (!(sw->features & REDUNDANCY_SUPPORT))
		return;
	sw->reg->w32(sw, REG_DLR_BEACON_TIMEOUT__4, timeout);
}

static void dlr_hw_set_vlan_id(struct ksz_sw *sw, u16 vid)
{
	if (!(sw->features & REDUNDANCY_SUPPORT))
		return;
	sw->reg->w16(sw, REG_DLR_VLAN_ID__2, vid);
}
#endif


#define DLR_LEARNING_ENTRY		3
#define DLR_BEACON_ENTRY		4
#define DLR_ANNOUNCE_ENTRY		5
#define DLR_SIGNON_ENTRY		6
#define DLR_SUPERVISOR_ENTRY		7
#define DLR_SUPERVISOR_DEV_0_ENTRY	8

static void sw_setup_dlr(struct ksz_sw *sw)
{
	struct ksz_dlr_info *dlr = &sw->info->dlr;

	/* Enable 802.1p priority to give highest priority to beacon frame. */
	sw_ena_802_1p(sw, dlr->ports[0]);
	sw_ena_802_1p(sw, dlr->ports[1]);
	sw_ena_802_1p(sw, sw->HOST_PORT);

#ifdef CONFIG_HAVE_ACL_HW
	/* Need to receive beacon frame with changed VID. */
	sw->ops->fwd_unk_vid(sw);
#endif

#ifdef CONFIG_HAVE_DLR_HW
	dlr_hw_set_dest_addr(sw, MAC_ADDR_BEACON);
	dlr_hw_set_port_map(sw, dlr->member);
#endif
	sw->ops->release(sw);

	/* SignOn is not forwarded automatically. */
	sw->ops->cfg_mac(sw, DLR_SIGNON_ENTRY, MAC_ADDR_SIGNON, sw->HOST_MASK,
		false, false, 0);

	/* Not 3-port switch and other ports are used. */
	if (sw->overrides & HAVE_MORE_THAN_2_PORTS) {
		u32 member = dlr->member | sw->HOST_MASK;

		sw->ops->cfg_mac(sw, DLR_BEACON_ENTRY, MAC_ADDR_BEACON,
			member, false, false, 0);
		sw->ops->cfg_mac(sw, DLR_ANNOUNCE_ENTRY, MAC_ADDR_ANNOUNCE,
			member, false, false, 0);
		sw->ops->cfg_mac(sw, DLR_LEARNING_ENTRY,
			MAC_ADDR_LEARNING_UPDATE, member, false, false, 0);
		if (1 == sw->eth_cnt) {
			sw->ops->acquire(sw);
			sw_cfg_port_base_vlan(sw, dlr->ports[0], member);
			sw_cfg_port_base_vlan(sw, dlr->ports[1], member);
			sw_cfg_port_base_vlan(sw, sw->HOST_PORT, member);
			sw->ops->release(sw);
		}
	}
	dlr_setup_acl(dlr, dlr->ports[0]);
	dlr_setup_acl(dlr, dlr->ports[1]);

	/* Do not need to process beacons. */
	if (DLR_ANNOUNCE_NODE == sw->info->dlr.node)
		sw->ops->cfg_mac(sw, DLR_BEACON_ENTRY, MAC_ADDR_BEACON,
			dlr->member, false, false, 0);
	sw->ops->acquire(sw);
}  /* sw_setup_dlr */

enum {
	DEV_DLR_CHK_HW,
	DEV_DLR_CLR_SUPER,
	DEV_DLR_SETUP_DIR,
	DEV_DLR_SETUP_DROP,
	DEV_DLR_SETUP_TIMEOUT,
	DEV_DLR_SETUP_VID,
	DEV_DLR_FLUSH,
	DEV_DLR_BLOCK,
	DEV_DLR_STOP,
	DEV_DLR_UPDATE,
	DEV_DLR_RX,
	DEV_DLR_START_ANNOUNCE,
	DEV_DLR_TX_ANNOUNCE,
	DEV_DLR_TX_LOCATE,
	DEV_DLR_TX_SIGNON,
	DEV_DLR_TX_REQ,
	DEV_DLR_TX_RESP,
	DEV_DLR_TX_STATUS,
	DEV_DLR_TX_ADVERTISE,
	DEV_DLR_TX_FLUSH_TABLES,
	DEV_DLR_TX_LEARNING_UPDATE,
};

static void wait_for_timeout(u32 microsec)
{
	if (microsec >= 20000) {
		microsec /= 1000;
		delay_milli(microsec);
	} else
		delay_micro(microsec);
}  /* wait_for_timeout */

static void dlr_set_addr(struct ksz_dlr_active_node *node, u32 ip_addr,
	u8 *addr)
{
	node->ip_addr = ip_addr;
	memcpy(node->addr, addr, ETH_ALEN);
}  /* dlr_set_addr */

static int dlr_dev_xmit(struct ksz_dlr_info *info, u8 *data, int len,
	int ports, u16 vid)
{
	int rc;
	struct sk_buff *skb;
	const struct net_device_ops *ops = info->dev->netdev_ops;
	struct ksz_sw *sw = info->sw_dev;

	/* Add extra for tail tagging. */
	skb = dev_alloc_skb(len + VLAN_HLEN + 4 + 8);
	if (!skb)
		return -ENOMEM;

	/* Regular transmit from DLR node. */
	if (vid == info->vid)
		memcpy(skb->data, data, len);

	/* Need to replace source MAC address for self-address filtering. */
	if (ports & info->member)
		memcpy(&skb->data[6], info->src_addr, ETH_ALEN);

	skb_put(skb, len);
	sw->net_ops->add_tail_tag(sw, skb, ports);
	skb->protocol = htons(DLR_TAG_TYPE);
	skb->dev = info->dev;
	do {
		struct ksz_sw *sw = info->sw_dev;

		rc = ops->ndo_start_xmit(skb, skb->dev);
		if (NETDEV_TX_BUSY == rc) {
			rc = wait_event_interruptible_timeout(sw->queue,
				!netif_queue_stopped(info->dev),
				50 * HZ / 1000);

			rc = NETDEV_TX_BUSY;
		}
	} while (NETDEV_TX_BUSY == rc);
	return rc;
}  /* dlr_dev_xmit */

static int dlr_xmit(struct ksz_dlr_info *info, u16 ports)
{
	u8 *frame = info->tx_frame;
	int len = info->len;

	/* Do not send if network device is not ready. */
	if (!netif_running(info->dev) || !netif_carrier_ok(info->dev))
		return 0;

	/* Do not send to port if its link is lost. */
	if ((ports & (1 << info->ports[0])) && info->p1_down)
		ports &= ~(1 << info->ports[0]);
	if ((ports & (1 << info->ports[1])) && info->p2_down)
		ports &= ~(1 << info->ports[1]);

	if (len < 60) {
		memset(&frame[len], 0, 60 - len);
		len = 60;
	}

	return dlr_dev_xmit(info, info->tx_frame, len, ports, info->vid);
}  /* dlr_xmit */

static int prep_dlr_beacon(struct ksz_dlr_info *dlr)
{
	struct ksz_dlr_frame *frame = &dlr->frame.body;

	memcpy(dlr->frame.vlan.h_dest, MAC_ADDR_BEACON, ETH_ALEN);
	frame->hdr.frame_type = DLR_BEACON;
	frame->hdr.src_port = DLR_PORT_NONE;
	frame->hdr.seqid = htonl(dlr->seqid_beacon++);

	memset(frame->data.reserved, 0, 30);
	frame->data.beacon.ring_state = dlr->ring_state;
	frame->data.beacon.precedence = dlr->precedence;
	frame->data.beacon.interval = htonl(dlr->beacon_interval);
	frame->data.beacon.timeout = htonl(dlr->beacon_timeout);
	return sizeof(struct ksz_dlr_beacon);
}  /* prep_dlr_beacon */

static int prep_dlr_announce(struct ksz_dlr_info *dlr)
{
	struct ksz_dlr_frame *frame = &dlr->frame.body;

	memcpy(dlr->frame.vlan.h_dest, MAC_ADDR_ANNOUNCE, ETH_ALEN);
	frame->hdr.frame_type = DLR_ANNOUNCE;
	frame->hdr.src_port = DLR_PORT_NONE;
	frame->hdr.seqid = htonl(dlr->seqid++);

	memset(frame->data.reserved, 0, 30);
	frame->data.announce.ring_state = dlr->ring_state;
	return sizeof(struct ksz_dlr_announce);
}  /* prep_dlr_announce */

static int prep_dlr_link_status(struct ksz_dlr_info *dlr, int neigh)
{
	struct ksz_dlr_frame *frame = &dlr->frame.body;

	memcpy(dlr->frame.vlan.h_dest, dlr->attrib.active_super_addr.addr,
		ETH_ALEN);
	frame->hdr.frame_type = DLR_LINK_STATUS;
	frame->hdr.src_port = DLR_PORT_NONE;
	frame->hdr.seqid = htonl(dlr->seqid++);

	memset(frame->data.reserved, 0, 30);
	frame->data.status.port1_active = 1;
	frame->data.status.port2_active = 1;

	if (neigh) {
		frame->data.status.neighbor = 1;
		if (dlr->p1_lost)
			frame->data.status.port1_active = 0;
		if (dlr->p2_lost)
			frame->data.status.port2_active = 0;
	} else {
		frame->data.status.neighbor = 0;
		if (dlr->p1_down)
			frame->data.status.port1_active = 0;
		if (dlr->p2_down)
			frame->data.status.port2_active = 0;
	}
	return sizeof(struct ksz_dlr_status);
}  /* prep_dlr_link_status */

static int prep_dlr_locate_fault(struct ksz_dlr_info *dlr)
{
	struct ksz_dlr_frame *frame = &dlr->frame.body;

	memcpy(dlr->frame.vlan.h_dest, MAC_ADDR_ANNOUNCE, ETH_ALEN);
	frame->hdr.frame_type = DLR_LOCATE_FAULT;
	frame->hdr.src_port = DLR_PORT_NONE;
	frame->hdr.seqid = htonl(dlr->seqid++);

	memset(frame->data.reserved, 0, 30);
	return 0;
}  /* prep_dlr_locate_fault */

static int prep_dlr_neigh_chk_req(struct ksz_dlr_info *dlr, int port)
{
	struct ksz_dlr_frame *frame = &dlr->frame.body;

	memcpy(dlr->frame.vlan.h_dest, MAC_ADDR_SIGNON, ETH_ALEN);
	frame->hdr.frame_type = DLR_NEIGH_CHK_REQ;
	frame->hdr.src_port = port ? DLR_PORT_2 : DLR_PORT_1;
	dlr->seqid_chk[port] = dlr->seqid++;
	if (1 == dlr->port_chk[port])
		dlr->seqid_first[port] = dlr->seqid_chk[port];
	frame->hdr.seqid = htonl(dlr->seqid_chk[port]);

	memset(frame->data.reserved, 0, 30);
	return 0;
}  /* prep_dlr_neigh_chk_req */

static int prep_dlr_neigh_chk_resp(struct ksz_dlr_info *dlr, u32 seqid, u8 in,
	int out)
{
	struct ksz_dlr_frame *frame = &dlr->frame.body;

	memcpy(dlr->frame.vlan.h_dest, MAC_ADDR_SIGNON, ETH_ALEN);
	frame->hdr.frame_type = DLR_NEIGH_CHK_RESP;
	frame->hdr.src_port = out ? DLR_PORT_2 : DLR_PORT_1;
	frame->hdr.seqid = htonl(seqid);

	memset(frame->data.reserved, 0, 30);
	frame->data.neigh_chk_resp.src_port = in;
	return sizeof(struct ksz_dlr_neigh_chk_resp);
}  /* prep_dlr_neigh_chk_resp */

static int prep_dlr_signon(struct ksz_dlr_info *dlr, int len)
{
	int i;
	struct ksz_dlr_tx_frame *base = (struct ksz_dlr_tx_frame *)
		dlr->signon_frame;
	struct ksz_dlr_frame *frame = &base->body;
	u16 num = ntohs(frame->data.signon.num);
	struct ksz_dlr_node *node = frame->data.signon.node;
	int space = 1000;

	/* The very first signon frame. */
	if (!len) {
		memcpy(base->vlan.h_dest, dlr->signon_addr, ETH_ALEN);
		frame->hdr.frame_type = DLR_SIGN_ON;
		frame->hdr.src_port = dlr->tx_port;
		dlr->seqid_signon = dlr->seqid;
		frame->hdr.seqid = htonl(dlr->seqid++);
		num = 0;
		len = sizeof(struct vlan_ethhdr) +
			sizeof(struct ksz_dlr_hdr) +
			sizeof(struct ksz_dlr_signon) -
			sizeof(struct ksz_dlr_node);
		if ((dlr->overrides & DLR_TEST) && dlr->signon_space)
			space = dlr->signon_space + 1;
	}
	memcpy(base->vlan.h_source, dlr->src_addr, ETH_ALEN);
	if (len + sizeof(struct ksz_dlr_node) > 1500) {
		memcpy(base->vlan.h_dest, dlr->attrib.active_super_addr.addr,
			ETH_ALEN);
		frame->hdr.src_port = dlr->rx_port;
		dlr->signon_port = dlr->rx_port;
		return len;
	}
	for (i = 0; i < num; i++)
		node++;
	do {
		num++;
		memcpy(node->addr, dlr->src_addr, ETH_ALEN);
		node->ip_addr = dlr->ip_addr;
		len += sizeof(struct ksz_dlr_node);
		node++;
	} while (len + sizeof(struct ksz_dlr_node) * space <= 1500);
	frame->data.signon.num = htons(num);

	dlr->signon_port = dlr->tx_port;
	return len;
}  /* prep_dlr_signon */

static int prep_dlr_advertise(struct ksz_dlr_info *dlr)
{
	struct ksz_dlr_frame *frame = &dlr->frame.body;

	memcpy(dlr->frame.vlan.h_dest, MAC_ADDR_ADVERTISE, ETH_ALEN);
	frame->hdr.frame_type = DLR_ADVERTISE;
	frame->hdr.src_port = DLR_PORT_NONE;
	frame->hdr.seqid = htonl(dlr->seqid++);

	memset(frame->data.reserved, 0, 30);
	frame->data.advertise.state = DLR_GW_ACTIVE_LISTEN_STATE;
	frame->data.advertise.precedence = dlr->precedence;
	frame->data.advertise.interval = htonl(dlr->beacon_interval);
	frame->data.advertise.timeout = htonl(dlr->beacon_timeout);
	frame->data.advertise.learning_update_enable = 1;
	return sizeof(struct ksz_dlr_advertise);
}  /* prep_dlr_advertise */

static int prep_dlr_flush_tables(struct ksz_dlr_info *dlr)
{
	struct ksz_dlr_frame *frame = &dlr->frame.body;

	memcpy(dlr->frame.vlan.h_dest, MAC_ADDR_ANNOUNCE, ETH_ALEN);
	frame->hdr.frame_type = DLR_FLUSH_TABLES;
	frame->hdr.src_port = DLR_PORT_NONE;
	frame->hdr.seqid = htonl(dlr->seqid++);

	memset(frame->data.reserved, 0, 30);
	frame->data.flush.learning_update_enable = 1;
	return sizeof(struct ksz_dlr_flush_tables);
}  /* prep_dlr_flush_tables */

static int prep_dlr_learning_update(struct ksz_dlr_info *dlr)
{
	dlr->update_frame.hdr.seqid = htonl(dlr->seqid++);

	return sizeof(struct ksz_dlr_update_frame);
}  /* prep_dlr_learning_update */

static void dlr_tx_beacon(struct ksz_dlr_info *dlr)
{
	int rc;

	dlr->len = prep_dlr_beacon(dlr);
	dlr->len += sizeof(struct vlan_ethhdr) + sizeof(struct ksz_dlr_hdr);
	rc = dlr_xmit(dlr, dlr->member);
}  /* dlr_tx_beacon */

static void dlr_tx_announce(struct ksz_dlr_info *dlr)
{
	int rc;
	u16 ports = dlr->member;

#ifdef DBG_DLR_ANN_SIGNON
	if (dbg_ann > 0) {
		dbg_msg(" tx ann: S=%d R=%d %x %lx\n",
			dlr->state, dlr->ring_state,
			dlr->seqid, jiffies);
		dbg_ann--;
	}
#endif

	if (RING_NORMAL_STATE == dlr->ring_state) {
		if (dlr->ann_first)
			dlr->ann_jiffies = jiffies;
		else if (dlr->ann_jiffies == jiffies) {
			dlr->ann_jiffies = 0;
			return;
		}
	}

	if (RING_NORMAL_STATE == dlr->ring_state)
		ports = 1 << dlr->ports[dlr->port];

	dlr->len = prep_dlr_announce(dlr);
	dlr->len += sizeof(struct vlan_ethhdr) + sizeof(struct ksz_dlr_hdr);
	rc = dlr_xmit(dlr, ports);

	/* First delayed announce from initial fault state sent. */
	if (dlr->ann_first)
		dlr->ann_first = 0;
}  /* dlr_tx_announce */

static void dlr_tx_chk_req(struct ksz_dlr_info *dlr, int port)
{
	int rc;

	dlr->len = prep_dlr_neigh_chk_req(dlr, port);
	dlr->len += sizeof(struct vlan_ethhdr) + sizeof(struct ksz_dlr_hdr);
	rc = dlr_xmit(dlr, (1 << dlr->ports[port]));
}  /* dlr_tx_chk_req */

static void dlr_tx_chk_resp(struct ksz_dlr_info *dlr, int port)
{
	int rc;

	dlr->len = prep_dlr_neigh_chk_resp(dlr, dlr->seqid_rcv[port],
		dlr->port_rcv[port], port);
	dlr->len += sizeof(struct vlan_ethhdr) + sizeof(struct ksz_dlr_hdr);
	rc = dlr_xmit(dlr, (1 << dlr->ports[port]));
}  /* dlr_tx_chk_resp */

static void dlr_tx_status(struct ksz_dlr_info *dlr, int neigh)
{
	int rc;

	dlr->len = prep_dlr_link_status(dlr, neigh);
	dlr->len += sizeof(struct vlan_ethhdr) + sizeof(struct ksz_dlr_hdr);
	rc = dlr_xmit(dlr, 0);
}  /* dlr_tx_status */

static void dlr_tx_signon(struct ksz_dlr_info *dlr, int len)
{
	int rc;

	dlr->len = prep_dlr_signon(dlr, len);
	dlr->tx_frame = dlr->signon_frame;
	rc = dlr_xmit(dlr, (1 << dlr->ports[dlr->signon_port]));
	dlr->tx_frame = (u8 *) &dlr->frame;
}  /* dlr_tx_signon */

static void dlr_tx_locate_fault(struct ksz_dlr_info *dlr)
{
	int rc;

	dlr->len = prep_dlr_locate_fault(dlr);
	dlr->len += sizeof(struct vlan_ethhdr) + sizeof(struct ksz_dlr_hdr);
	rc = dlr_xmit(dlr, dlr->member);
}  /* dlr_tx_locate_fault */

static void dlr_tx_learning_update(struct ksz_dlr_info *dlr)
{
	int rc;
	u16 ports = dlr->member;

	dlr->len = prep_dlr_learning_update(dlr);
	dlr->tx_frame = (u8 *) &dlr->update_frame;

	/* Attempt to notify the other supervisor about incoming beacons. */
	if (dlr->rogue_super) {
		memcpy(dlr->update_frame.eth.h_dest,
			&dlr->rogue_super->prec_addr[1], ETH_ALEN);
		ports = (1 << dlr->ports[dlr->rogue_super->port]);
		ports |= 0x80000000;
	}
	rc = dlr_xmit(dlr, ports);

	/* Reset default Learning_Update address. */
	if (dlr->rogue_super) {
		memcpy(dlr->update_frame.eth.h_dest, MAC_ADDR_LEARNING_UPDATE,
			ETH_ALEN);
		dlr->rogue_super = NULL;
	}
	dlr->tx_frame = (u8 *) &dlr->frame;
}  /* dlr_tx_learning_update */

static void dlr_tx_advertise(struct ksz_dlr_info *dlr)
{
	int rc;

	dlr->len = prep_dlr_advertise(dlr);
	dlr->len += sizeof(struct vlan_ethhdr) + sizeof(struct ksz_dlr_hdr);
	rc = dlr_xmit(dlr, dlr->member);
}  /* dlr_tx_advertise */

static void dlr_tx_flush_tables(struct ksz_dlr_info *dlr)
{
	int rc;

	dlr->len = prep_dlr_flush_tables(dlr);
	dlr->len += sizeof(struct vlan_ethhdr) + sizeof(struct ksz_dlr_hdr);
	rc = dlr_xmit(dlr, dlr->member);
}  /* dlr_tx_flush_tables */

static void flushMacTable(struct ksz_dlr_info *info)
{
	struct ksz_sw *sw = info->sw_dev;

	sw->ops->acquire(sw);
	sw->ops->flush_table(sw, sw->mib_port_cnt);
	sw->ops->release(sw);
}

static void enableOnePort(struct ksz_dlr_info *info)
{
	struct ksz_sw *sw = info->sw_dev;
	int block_port = (info->port + 1) & 1;

	sw->ops->acquire(sw);
	port_set_stp_state(sw, info->ports[block_port], STP_STATE_BLOCKED);
	sw->ops->release(sw);
}

static void enableBothPorts(struct ksz_dlr_info *info)
{
	struct ksz_sw *sw = info->sw_dev;

	sw->ops->acquire(sw);
	port_set_stp_state(sw, info->ports[0], STP_STATE_FORWARDING);
	port_set_stp_state(sw, info->ports[1], STP_STATE_FORWARDING);
	sw->ops->release(sw);
}

static void disableLearn(struct ksz_dlr_info *info, int disable)
{
	struct ksz_sw *sw = info->sw_dev;

	if (disable != info->disable_learn) {
		sw->ops->acquire(sw);
		port_cfg_dis_learn(sw, info->ports[0], disable);
		port_cfg_dis_learn(sw, info->ports[1], disable);
		sw->ops->release(sw);
		info->disable_learn = disable;
	}
}

static void dlr_set_state(struct ksz_dlr_info *info)
{
#ifdef CONFIG_HAVE_DLR_HW
	u8 node;
	u8 ring;
	struct ksz_sw *sw = info->sw_dev;

	if (DLR_IDLE_STATE == info->state)
		node = DLR_NODE_STATE_IDLE;
	else if (DLR_NORMAL_STATE == info->state ||
		 DLR_ACTIVE_NORMAL_STATE == info->state)
		node = DLR_NODE_STATE_NORMAL;
	else
		node = DLR_NODE_STATE_FAULT;
	ring = RING_FAULT_STATE == info->ring_state ?
		DLR_RING_STATE_FAULT : DLR_RING_STATE_NORMAL;

	/* Backup supervisor needs to send ring fault with the first beacon. */
	if (DLR_ACTIVE_SUPERVISOR != info->node ||
	    DLR_RESTART_STATE == info->state)
		ring = DLR_RING_STATE_FAULT;
	sw->ops->acquire(sw);
	dlr_hw_set_state(sw, node, ring);
	sw->ops->release(sw);

	/* Make sure beacon is sent with new ring state. */
	if (DLR_ACTIVE_SUPERVISOR == info->node)
		wait_for_timeout(info->beacon_interval * 2);
#endif
}  /* dlr_set_state */

static void dlr_chk_supervisor(struct ksz_dlr_info *info)
{
#ifdef CONFIG_HAVE_DLR_HW
	u32 data;
	struct ksz_sw *sw = info->sw_dev;

	if (!(sw->features & REDUNDANCY_SUPPORT))
		return;
	sw->ops->acquire(sw);
	data = SW_R(sw, REG_DLR_CTRL__1);
	if (data & DLR_BEACON_TX_ENABLE) {
#ifdef DBG_DLR_HW_OPER
		dbg_msg("  %s %x\n", __func__, data);
#endif
		if (info->node != DLR_ACTIVE_SUPERVISOR) {
			data &= ~DLR_BEACON_TX_ENABLE;
			SW_W(sw, REG_DLR_CTRL__1, data);
#ifdef DBG_DLR_HW_OPER
			dbg_msg(" tx off\n");
#endif
		}
	} else if (DLR_ACTIVE_SUPERVISOR == info->node) {
		data |= DLR_BEACON_TX_ENABLE;
		SW_W(sw, REG_DLR_CTRL__1, data);
#ifdef DBG_DLR_HW_OPER
		dbg_msg(" tx on\n");
#endif
	}
	sw->ops->release(sw);
#endif
	info->chk_hw = 0;
}  /* dlr_chk_supervisor */

static void dlr_set_supervisor(struct ksz_dlr_info *info)
{
#ifdef CONFIG_HAVE_DLR_HW
	u8 node;
	struct ksz_sw *sw = info->sw_dev;

	if (info->node < DLR_SUPERVISOR)
		node = DLR_BEACON_NODE;
	else if (DLR_ACTIVE_SUPERVISOR == info->node)
		node = DLR_ACTIVE_SUPERVISOR;
	else
		node = DLR_SUPERVISOR;

	/* In case the backup supervisor starts sending beacons. */
	if (DLR_SUPERVISOR == node && 7 == info->beacon_timeout_ports)
		node = DLR_BEACON_NODE;
	sw->ops->acquire(sw);
	dlr_hw_set_supervisor(sw, node);
	sw->ops->release(sw);
#ifdef DBG_DLR_HW_OPER
	dbg_msg("  %s %d %d\n", __func__, node, info->node);
#endif
#endif
}  /* dlr_set_supervisor */

static void setupBeacons(struct ksz_dlr_info *info)
{
	int use_hw = false;

#ifdef CONFIG_HAVE_DLR_HW
	struct ksz_sw *sw = info->sw_dev;

	if (sw->features & REDUNDANCY_SUPPORT) {
		use_hw = true;
	}
#endif
	if (use_hw) {
		dlr_set_state(info);
	} else {
		info->interval = 0;
		dlr_tx_beacon(info);
	}
}  /* setupBeacons */

static void disableSupervisor(struct ksz_dlr_info *info)
{
	struct ksz_sw *sw = info->sw_dev;
	u32 member = 0;

#ifdef DBG_DLR_OPER
	dbg_msg("%s\n", __func__);
#endif
	if (sw->overrides & HAVE_MORE_THAN_2_PORTS)
		member = info->member | sw->HOST_MASK;
	dlr_set_supervisor(info);
	info->start = 0;

	/* Allow beacons to be forwarded. */
	sw->ops->cfg_mac(sw, DLR_BEACON_ENTRY, MAC_ADDR_BEACON, member, false,
		false, 0);
	sw->ops->cfg_mac(sw, DLR_ANNOUNCE_ENTRY, MAC_ADDR_ANNOUNCE, member,
		false, false, 0);
	sw->ops->cfg_mac(sw, DLR_SIGNON_ENTRY, MAC_ADDR_SIGNON, sw->HOST_MASK,
		false, false, 0);
	sw->ops->cfg_mac(sw, DLR_LEARNING_ENTRY, MAC_ADDR_LEARNING_UPDATE,
		member, false, false, 0);
#ifdef CONFIG_HAVE_DLR_HW
	sw->ops->acquire(sw);
	dlr_hw_reset_seq_id(sw);
	sw->ops->release(sw);
#endif
}  /* disableSupervisor */

static void enableSupervisor(struct ksz_dlr_info *info)
{
	struct ksz_sw *sw = info->sw_dev;

	/* Do not need to process Announce. */
	sw->ops->cfg_mac(sw, DLR_ANNOUNCE_ENTRY, MAC_ADDR_ANNOUNCE, 0, true,
		false, 0);

	/* Force to receive messages as port will be closed. */
	sw->ops->cfg_mac(sw, DLR_SIGNON_ENTRY, MAC_ADDR_SIGNON, sw->HOST_MASK,
		true, false, 0);
#if 0
/* For case where tag is removed and new tag is added. */
	sw->ops->cfg_mac(sw, DLR_SIGNON_ENTRY, MAC_ADDR_SIGNON, sw->HOST_MASK,
		true, true, 2);
#endif
	sw->ops->cfg_mac(sw, DLR_LEARNING_ENTRY, MAC_ADDR_LEARNING_UPDATE, 0,
		true, false, 0);
	sw->ops->acquire(sw);
#ifdef CONFIG_HAVE_DLR_HW
	dlr_hw_set_precedence(sw, info->precedence);
	dlr_hw_set_interval(sw, info->beacon_interval);
	dlr_hw_set_timeout(sw, info->beacon_timeout);
	dlr_hw_set_vlan_id(sw, info->vid);
	dlr_hw_set_ip_addr(sw, ntohl(info->ip_addr));
#endif
	sw->ops->release(sw);

	/* Beacons will only be forwarded to self. */
	sw->ops->cfg_mac(sw, DLR_BEACON_ENTRY, MAC_ADDR_BEACON, sw->HOST_MASK,
		false, false, 0);

	info->seqid_last[0] = info->seqid_last[1] = 0xdeadbeef;
	info->start = 1;
	dlr_set_supervisor(info);
}  /* enableSupervisor */

static void disableAnnounce(struct ksz_dlr_info *info)
{
#ifdef DBG_DLR_OPER
	dbg_msg("%s\n", __func__);
#endif
	cancel_delayed_work_sync(&info->announce_tx);
}

static void startAnnounce(struct ksz_dlr_info *info)
{
#ifdef DBG_DLR_OPER
	dbg_msg("%s\n", __func__);
#endif
	cancel_delayed_work_sync(&info->announce_tx);
	schedule_delayed_work(&info->announce_tx, 100);
	if (!info->ann_first)
		dlr_tx_announce(info);
	else
		info->tx_announce = true;
}  /* startAnnounce */

static void enableAnnounce(struct ksz_dlr_info *info, int delay)
{
#ifdef DBG_DLR_OPER
	dbg_msg("%s %d %d %lx\n", __func__, delay, info->ann_delay,
		jiffies);
#endif
	if (1 == delay) {

		/* Wait for 2 * beacon timeout before sending announce. */
		if (!info->ann_delay) {
			info->ann_jiffies = jiffies;
			info->ann_delay = 1;
			info->ann_first = 1;
			cancel_delayed_work_sync(&info->announce_tx);
			schedule_delayed_work(&info->announce_tx, 0);
		}

	/* Wait until first announce is sent. */
	} else if (!info->ann_delay)
		startAnnounce(info);
}

static void disableAnnounceTimeout(struct ksz_dlr_info *info)
{
#ifdef DBG_DLR_OPER
	dbg_msg("%s\n", __func__);
#endif
	ksz_stop_timer(&info->announce_timeout_timer_info);
}

static void disableNeighChkTimers(struct ksz_dlr_info *info)
{
	info->p1_lost = info->p2_lost = 0;
	info->port_chk[0] = info->port_chk[1] = 0;
	ksz_stop_timer(&info->neigh_chk_timer_info);
	info->neigh_chk = 0;
}

static void disableSignOnTimer(struct ksz_dlr_info *info)
{
	ksz_stop_timer(&info->signon_timer_info);
	info->signon_start = 0;
}  /* disableSignOnTimer */

static int updateValues(struct ksz_dlr_info *info)
{
	struct ksz_dlr_gateway_capable *attrib = &info->attrib;
	struct ksz_sw *sw = info->sw_dev;
	int can_change = false;
	int vid_change = false;
	int prepare = false;
	int cmp = memcmp(info->src_addr, attrib->active_super_addr.addr,
		ETH_ALEN);

#ifdef DBG_DLR_OPER
	dbg_msg("%s\n", __func__);
#endif
	sw->ops->acquire(sw);
	if (info->precedence != attrib->super_cfg.prec) {
		info->precedence = attrib->super_cfg.prec;
#ifdef CONFIG_HAVE_DLR_HW
		dlr_hw_set_precedence(sw, info->precedence);
#endif
	}
	sw->ops->release(sw);

	/*
	 * Changing precedence or MAC address can cause backup supervisor to
	 * become active.
	 */
	if (info->precedence > attrib->active_super_prec ||
	    (info->precedence == attrib->active_super_prec &&
	    cmp > 0)) {
		can_change = true;
		prepare = true;
	} else if (!cmp)
		can_change = true;
	if (can_change && info->vid != attrib->super_cfg.vid) {
		vid_change = true;
		setup_vlan_table(info, info->vid, false);
	}
	sw->ops->acquire(sw);
	if (can_change &&
	    info->beacon_interval != attrib->super_cfg.beacon_interval) {
#ifdef DBG_DLR_OPER
		dbg_msg("interval %u %u\n",
			info->beacon_interval,
			attrib->super_cfg.beacon_interval);
#endif
		info->beacon_interval = attrib->super_cfg.beacon_interval;
#ifdef CONFIG_HAVE_DLR_HW
		dlr_hw_set_interval(sw, info->beacon_interval);
#endif
	}
	if (can_change &&
	    info->beacon_timeout != attrib->super_cfg.beacon_timeout) {
#ifdef DBG_DLR_OPER
		dbg_msg("timeout %u %u\n",
			info->beacon_timeout,
			attrib->super_cfg.beacon_timeout);
#endif
		info->beacon_timeout = attrib->super_cfg.beacon_timeout;
#ifdef CONFIG_HAVE_DLR_HW
		dlr_hw_set_timeout(sw, info->beacon_timeout);
#endif
	}
	if (can_change && info->vid != attrib->super_cfg.vid) {
		info->vid = attrib->super_cfg.vid;
#ifdef CONFIG_HAVE_DLR_HW
		dlr_hw_set_vlan_id(sw, info->vid);
#endif
	}
	sw->ops->release(sw);
	if (vid_change)
		setup_vlan_table(info, info->vid, true);
	info->new_val = 0;
	info->frame.vlan.h_vlan_TCI = htons((7 << VLAN_PRIO_SHIFT) | info->vid);
	memcpy(info->signon_frame, &info->frame, sizeof(struct vlan_ethhdr));
	return prepare;
}  /* updateValues */

static void dlr_flush(struct ksz_dlr_info *info)
{
	flushMacTable(info);
}

static void setupDir(struct ksz_dlr_info *info, int port)
{
	struct ksz_sw *sw = info->sw_dev;
	struct ksz_dlr_active_node *active;
	int cmp;

	if (port >= 0) {
		active = &info->attrib.active_super_addr;
		memcpy(info->last_sup.addr, active->addr, ETH_ALEN);
		port = 1 << info->ports[port];
	} else {
		active = &info->last_sup;
		port = 0;
	}

	/* Do not change entry of own address. */
	cmp = memcmp(active->addr, info->src_addr, ETH_ALEN);
	if (!cmp)
		return;
	info->active_port = port;
	sw->ops->cfg_mac(sw, DLR_SUPERVISOR_ENTRY,
		active->addr, port, false, false, 0);
#if 0
	if (sw->eth_cnt > 1)
		sw->ops->cfg_mac(sw, DLR_SUPERVISOR_DEV_0_ENTRY, active->addr,
			port, false, true, sw->eth_maps[0].vlan);
#endif
#ifdef DBG_DLR_HW_OPER
	dbg_msg("%s x%x %02x:%02x:%02x\n", __func__, port,
		active->addr[3],
		active->addr[4],
		active->addr[5]);
#endif
}


#define announcedState		(info->ring_state)
#define fromRingState		(RING_FAULT_STATE == info->ring_state ?	\
	DLR_FAULT_STATE : DLR_NORMAL_STATE)
#define announceRcvd		(info->ann_rcvd)
#define announceTimeout		(info->ann_timeout)
#define oneBeaconRcvd		(info->one_rcvd)
#define twoBeaconsRcvd		(info->both_rcvd)
#define oneBeaconTimeout	(info->one_timeout)
#define twoBeaconsTimeout	(info->both_timeout)
#define newSupervisor		(info->new_supervisor)
#define newValue		(info->new_val)
#define backupSupervisor	(DLR_SUPERVISOR == info->node)
#define faultState		(RING_FAULT_STATE == info->ring_state)
#define linkDown		(info->both_down)
#define linkLoss		(info->one_down)
#define linkStatus		(info->p1_lost || info->p2_lost)


static void acceptBeacons(struct ksz_dlr_info *dlr)
{
#ifdef DBG_DLR_BEACON
	dbg_msg("%s\n", __func__);
#endif
#ifdef DBG_DLR_BEACON
	dbg_bcn += 4;
#endif
	dlr->skip_beacon = false;

	/* Indicate in process of accepting beacons. */
	dlr->drop_beacon++;
#ifdef CONFIG_HAVE_ACL_HW
	setup_acl_beacon_drop(dlr, 0);
#endif
	dlr->drop_beacon = false;
	memset(&dlr->last_beacon[0], 0, sizeof(struct ksz_dlr_tx_frame));
	memset(&dlr->last_beacon[1], 0, sizeof(struct ksz_dlr_tx_frame));
}  /* acceptBeacons */

static void dropBeacons(struct ksz_dlr_info *info)
{
	int drop = info->member;

#ifdef DBG_DLR_BEACON
	dbg_msg("%s\n", __func__);
#endif
	if (info->node == DLR_ACTIVE_SUPERVISOR)
		drop = 0x8000;
#ifdef CONFIG_HAVE_ACL_HW
	setup_acl_beacon_drop(info, drop);
#endif
	info->skip_beacon = !!drop;
}  /* dropBeacons */

static int seq_ahead(u32 start, u32 num)
{
	u32 ahead;
	u32 behind;

	ahead = num - start;
	behind = start - num;
	return ahead < behind;
}

static int seq_in(u32 start, u32 end, u32 num)
{
	end -= start;
	num -= start;
	return 0 <= num && num <= end;
}

static struct ksz_dlr_node_info *find_dlr_node(struct ksz_dlr_info *info,
	u8 *addr)
{
	int i;

	for (i = 0; i < info->attrib.participants_cnt; i++)
		if (!memcmp(info->nodes[i].signon.addr, addr, ETH_ALEN))
			return &info->nodes[i];
	return NULL;
}  /* find_dlr_node */

static void dbg_dlr(struct ksz_dlr_info *info, char *msg)
{
	dbg_msg(" %s: S=%d R=%d L=%d ", msg, info->state, info->ring_state,
		info->LastBcnRcvPort);
	dbg_msg("d=%d:%d D=%d:%d l=%d:%d r=%d:%d R=%d:%d t=%d:%d T=%d:%d\n",
		info->p1_down, info->p2_down,
		info->one_down, info->both_down,
		info->p1_lost, info->p2_lost,
		info->p1_rcvd, info->p2_rcvd,
		info->one_rcvd, info->both_rcvd,
		info->p1_timeout, info->p2_timeout,
		info->one_timeout, info->both_timeout);
}

#ifdef DBG_DLR_STATE
static void dlr_print(struct ksz_dlr_info *info, char *msg)
{
	if (info->overrides & DLR_TEST)
		printk(KERN_INFO "%s\n", msg);
}
#endif

static int dlr_chk_beacon_timeout(struct ksz_dlr_info *info, int p,
	struct ksz_dlr_frame *beacon,
	struct ksz_dlr_super_info *active,
	struct ksz_dlr_super_info *super)
{
	u32 crc;
	int i;
	struct ksz_dlr_super_info *next;
	struct ksz_dlr_super_info *first = NULL;
	struct ksz_dlr_super_info *found = NULL;
	int accept = false;

	if (DLR_ACTIVE_SUPERVISOR != info->node)
		return accept;
	crc = ether_crc(ETH_ALEN + 1, super->prec_addr);
	for (i = 0; i < DLR_SUPERVISOR_NUM; i++) {
		next = &info->supers[i];
		if (!next->crc && !first)
			first = next;
		if (next->crc == crc) {
			found = next;
			break;
		}
	}
	if (!found)
		found = first;
	if (found) {
		u32 interval = ntohl(beacon->data.beacon.interval);

		found->cnt++;
		found->port = p;

		/* First time. */
		if (!found->crc) {
#ifdef DBG_DLR_SUPERVISOR
			dbg_msg("  A %x=%02x:%02x:%02x:%02x:%02x:%02x  "
				"S %x=%02x:%02x:%02x:%02x:%02x:%02x  ",
				active->prec_addr[0],
				active->prec_addr[1],
				active->prec_addr[2],
				active->prec_addr[3],
				active->prec_addr[4],
				active->prec_addr[5],
				active->prec_addr[6],
				super->prec_addr[0],
				super->prec_addr[1],
				super->prec_addr[2],
				super->prec_addr[3],
				super->prec_addr[4],
				super->prec_addr[5],
				super->prec_addr[6]);
			dbg_msg("cnt: %d %x\n", found->cnt, crc);
#endif
			found->crc = crc;
			memcpy(found->prec_addr, super->prec_addr,
				ETH_ALEN + 1);
		}
		found->timeout[p] += interval;
		if (found->timeout[p] > (10000 + 4 * interval) &&
		    !found->sent) {
dbg_msg("rogue: %u\n", found->timeout[p]);
			found->sent = 1;
			accept = true;
		}
	}
	return accept;
}  /* dlr_chk_beacon_timeout */

static void dbg_supervisor(struct ksz_dlr_info *info)
{
#ifdef DBG_DLR_SUPERVISOR
	struct ksz_dlr_super_info *next;
	int i;

	for (i = 0; i < DLR_SUPERVISOR_NUM; i++) {
		next = &info->supers[i];
		if (next->crc) {
			dbg_msg("  super %d %x=%02x:%02x:%02x\n",
				next->cnt,
				next->prec_addr[0],
				next->prec_addr[4],
				next->prec_addr[5],
				next->prec_addr[6]);
		}
	}
#endif
}  /* dbg_supervisor */

static void dlr_clr_supervisor(struct ksz_dlr_info *info)
{
	struct ksz_dlr_super_info *next;
	int i;

	for (i = 0; i < DLR_SUPERVISOR_NUM; i++) {
		next = &info->supers[i];
		if (next->crc) {
			if (next->last_cnt == next->cnt) {
#ifdef DBG_DLR_SUPERVISOR
				dbg_msg("  clr %d %u:%u %x=%02x:%02x:%02x\n",
					next->cnt,
					next->timeout[0], next->timeout[1],
					next->prec_addr[0],
					next->prec_addr[4],
					next->prec_addr[5],
					next->prec_addr[6]);
#endif
				memset(next, 0,
					sizeof(struct ksz_dlr_super_info));
			} else
				next->last_cnt = next->cnt;
		}
	}
}  /* dlr_clr_supervisor */

static void update_vlan(struct ksz_dlr_info *info, u16 vid)
{
	if (info->vid == vid)
		return;
	setup_vlan_table(info, info->vid, false);
	info->vid = vid;
	setup_vlan_table(info, info->vid, true);
	info->frame.vlan.h_vlan_TCI = htons((7 << VLAN_PRIO_SHIFT) | info->vid);
	memcpy(info->signon_frame, &info->frame, sizeof(struct vlan_ethhdr));
}  /* update_vlan */

static void setup_dir(struct ksz_dlr_info *info, int port)
{
	info->rx_port = port;
	info->tx_port = (port + 1) & 1;
	setupDir(info, port);
}  /* setup_dir */

static void dlr_notify_link_lost(struct ksz_dlr_info *dlr)
{
	if (dlr->dev_info) {
		u8 buf[sizeof(struct ksz_resp_msg) +
			sizeof(struct ksz_dlr_active_node) * 2];
		struct ksz_resp_msg *msg = (struct ksz_resp_msg *) buf;

		msg->module = DEV_MOD_DLR;
		msg->cmd = DEV_INFO_DLR_LINK;
		msg->resp.data[0] = 0;
		if (dlr->p1_down)
			msg->resp.data[0] |= 0x01;
		if (dlr->p2_down)
			msg->resp.data[0] |= 0x02;
		if (dlr->p1_lost)
			msg->resp.data[0] |= 0x04;
		if (dlr->p2_lost)
			msg->resp.data[0] |= 0x08;
		memcpy(&msg->resp.data[1], dlr->attrib.last_active,
			sizeof(struct ksz_dlr_active_node) * 2);
		sw_setup_msg(dlr->dev_info, msg, sizeof(struct ksz_resp_msg) +
			sizeof(struct ksz_dlr_active_node) * 2, NULL, NULL);
	}
}  /* dlr_notify_link_lost */

static void dlr_notify_cfg_change(struct ksz_dlr_info *dlr, int notify)
{
	if (dlr->dev_info) {
		struct ksz_resp_msg msg;

		msg.module = DEV_MOD_DLR;
		msg.cmd = DEV_INFO_DLR_CFG;
		msg.resp.data[0] = notify;
		sw_setup_msg(dlr->dev_info, &msg, sizeof(struct ksz_resp_msg),
			NULL, NULL);
	}
}  /* dlr_notify_cfg_change */

static int checkBeacon(struct ksz_dlr_info *info,
	struct ksz_dlr_rx_frame *frame, int port)
{
	struct ksz_dlr_super_info active;
	struct ksz_dlr_super_info super;
	u32 interval;
	u32 timeout;
	int cmp = 0;
	int accept = false;
	struct ksz_dlr_tx_frame beacon_frame;
	struct vlan_ethhdr *vlan = frame->vlan;
	struct ksz_dlr_frame *beacon = frame->body;
	u32 seqid = ntohl(beacon->hdr.seqid);
	struct ksz_dlr_gateway_capable *attrib = &info->attrib;
	struct ksz_dlr_beacon_info *beacon_info = &info->beacon_info[port];

	if (info->state && (info->overrides & DLR_TEST_SEQ) &&
	    (info->seqid_last[port] + 1 != seqid) && !info->seqid_cnt) {
		info->seqid_cnt = 1000;
		dbg_msg("bcn seq %d: %d %d\n", port,
			info->seqid_last[port], seqid);
	}
	if (info->seqid_cnt > 0)
		info->seqid_cnt--;
	info->seqid_last[port] = seqid;

	/* Announce node does not accept beacons. */
	if (DLR_ANNOUNCE_NODE == info->node)
		return accept;

#if 1
/*
 * THa  2015/11/03
 * Hardware generates wrong ring state.
 */
	if (0 == beacon->data.beacon.ring_state) {
		beacon->data.beacon.ring_state = 2;
		if (!(info->overrides & DLR_BEACON_STATE_HACK)) {
			info->overrides |= DLR_BEACON_STATE_HACK;
			printk(KERN_INFO "beacon fault state value wrong\n");
		}
	}
#endif

	/* Ignore own beacon if stopped. */
	/*
	 * Only active supervisor can receive its own beacons because of
	 * self-address filtering.
	 */
	if (!memcmp(info->src_addr, vlan->h_source, ETH_ALEN)) {
		if (info->skip_beacon && info->drop_beacon && dbg_leak)
			dbg_msg(" ^ ");
		if (!info->start)
			return accept;
	}

	/* Determine precedence level. */
	super.prec_addr[0] = beacon->data.beacon.precedence;
	memcpy(&super.prec_addr[1], vlan->h_source, ETH_ALEN);

	/* Compare own address first if supervisor capable. */
	if (info->node >= DLR_SUPERVISOR) {
		active.prec_addr[0] = attrib->super_cfg.prec;
		memcpy(&active.prec_addr[1], info->src_addr, ETH_ALEN);
		cmp = memcmp(&super, &active, ETH_ALEN + 1);
	}

	if (cmp >= 0) {
		active.prec_addr[0] = attrib->active_super_prec;
		memcpy(&active.prec_addr[1], attrib->active_super_addr.addr,
			ETH_ALEN);
		cmp = memcmp(&super, &active, ETH_ALEN + 1);
	}

	/* Ignore lower precedence beacon. */
	if (cmp < 0) {
		/* Simulate beacon timeout as hardware cannot catch that. */
		accept = dlr_chk_beacon_timeout(info, port, beacon, &active,
			&super);

		return accept;
	} else if (cmp > 0) {
#ifdef DBG_DLR_SUPERVISOR
		dbg_msg("new %d p:%d %08x A=%02x:%02x:%02x:%02x:%02x:%02x  "
			"S=%02x:%02x:%02x:%02x:%02x:%02x\n",
			cmp,
			beacon->data.beacon.precedence,
			beacon->hdr.ip_addr,
			attrib->active_super_addr.addr[0],
			attrib->active_super_addr.addr[1],
			attrib->active_super_addr.addr[2],
			attrib->active_super_addr.addr[3],
			attrib->active_super_addr.addr[4],
			attrib->active_super_addr.addr[5],
			vlan->h_source[0],
			vlan->h_source[1],
			vlan->h_source[2],
			vlan->h_source[3],
			vlan->h_source[4],
			vlan->h_source[5]);
		dbg_msg("  new prec: %d >= %d %d %d s:%d\n",
			beacon->data.beacon.precedence,
			attrib->active_super_prec, info->precedence,
			attrib->super_cfg.prec,
			beacon->data.beacon.ring_state);
#endif
		accept = true;
		dlr_set_addr(&attrib->active_super_addr,
			beacon->hdr.ip_addr, vlan->h_source);
		attrib->active_super_prec = beacon->data.beacon.precedence;
		info->new_supervisor = 1;
		info->p1_set = info->p2_set = 1;
		info->p1_rcvd = info->p2_rcvd =
		info->one_rcvd = info->both_rcvd = 0;
		info->p1_timeout = info->p2_timeout =
		info->one_timeout = info->both_timeout = 0;

		/* Set in following code. */
		info->LastBcnRcvPort = 0;

#ifdef DBG_DLR_STATE
		if (DLR_ACTIVE_SUPERVISOR == info->node) {
			dbg_dlr(info, "stop being active");
#ifdef DBG_DLR_BEACON
			dbg_bcn = 2;
#endif
		}
#endif
		memset(&info->last_beacon[0], 0,
			sizeof(struct ksz_dlr_tx_frame));
		memset(&info->last_beacon[1], 0,
			sizeof(struct ksz_dlr_tx_frame));
		memset(&info->beacon_info[0].last, 0,
			sizeof(struct ksz_dlr_beacon));
		memset(&info->beacon_info[1].last, 0,
			sizeof(struct ksz_dlr_beacon));
		info->beacon_info[0].timeout =
		info->beacon_info[1].timeout = 0;
	}

	/* Process accepted beacon. */
	info->LastBcnRcvPort |= port ? 2 : 1;

	interval = ntohl(beacon->data.beacon.interval);
	timeout = ntohl(beacon->data.beacon.timeout);

#ifdef CONFIG_HAVE_DLR_HW
	if (info->skip_beacon &&
	    !memcmp(vlan->h_source, info->beacon_addr, ETH_ALEN)) {
		if (dbg_leak > 0) {
			dbg_msg(" ??: p=%d %d n=%d %x "
				"%02x:%02x:%02x:%02x:%02x:%02x "
				"%02x:%02x:%02x:%02x:%02x:%02x\n",
				port, info->skip_beacon, info->node, seqid,
				vlan->h_dest[0],
				vlan->h_dest[1],
				vlan->h_dest[2],
				vlan->h_dest[3],
				vlan->h_dest[4],
				vlan->h_dest[5],
				vlan->h_source[0],
				vlan->h_source[1],
				vlan->h_source[2],
				vlan->h_source[3],
				vlan->h_source[4],
				vlan->h_source[5]);
			--dbg_leak;
		}
	}
#endif
	if (!accept && info->skip_beacon)
		return accept;
	else if (beacon_info->timeout && !info->drop_beacon) {
		beacon_info->timeout += interval;
		if (beacon_info->timeout > timeout) {
			info->drop_beacon = true;
			accept = true;
		}
	}

	/* Start the beacon drop process. */
	if (!beacon_info->timeout &&
	    !info->skip_beacon && !info->drop_beacon &&
	    !newSupervisor &&
	    RING_NORMAL_STATE == beacon->data.beacon.ring_state &&
	    RING_NORMAL_STATE == info->ring_state &&
	    (DLR_NORMAL_STATE == info->state ||
	    DLR_ACTIVE_NORMAL_STATE == info->state)) {
		beacon_info->timeout = 1;
#ifdef DBG_DLR_BEACON
		dbg_msg("  ready to drop: %d=r:%d\n",
			port, beacon->data.beacon.ring_state);
		dbg_bcn = 3;
#endif
	}

	/* Zero out the sequence id for comparison. */
	memcpy(&beacon_frame.vlan, frame->vlan, sizeof(struct vlan_ethhdr));
	memcpy(&beacon_frame.body, frame->body, sizeof(struct ksz_dlr_frame));
	beacon_frame.body.hdr.seqid = 0;
	if (!accept)
		accept = memcmp(&beacon_frame, &info->last_beacon[port],
			sizeof(struct ksz_dlr_tx_frame));
	if (accept)
		memcpy(&info->last_beacon[port], &beacon_frame,
			sizeof(struct ksz_dlr_tx_frame));

	/* Try to process as few beacons as possible. */
	if (memcmp(&beacon_info->last, &beacon->data.beacon,
	    sizeof(struct ksz_dlr_beacon))) {
		memcpy(&beacon_info->last, &beacon->data.beacon,
			sizeof(struct ksz_dlr_beacon));
		info->seqid_accept[port] = seqid;
	}

#ifdef DBG_DLR_BEACON
	if (accept || dbg_bcn > 0) {
		dbg_msg("b: %d=%d:%d %04x; %02x %02x:%02x:%02x %08lx; "
			"%d %d %lx %d\n",
			port,
			beacon->data.beacon.ring_state, info->ring_state,
			ntohs(vlan->h_vlan_TCI),
			beacon->data.beacon.precedence,
			vlan->h_source[3], vlan->h_source[4], vlan->h_source[5],
			seqid, info->new_supervisor,
			beacon_info->timeout,
			jiffies, dbg_bcn);
	}
	if (dbg_bcn)
		--dbg_bcn;
#endif
	return accept;
}  /* checkBeacon */

static int handleBeacon(struct ksz_dlr_info *info,
	struct ksz_dlr_rx_frame *frame, int port)
{
	u32 interval;
	u32 timeout;
	u16 vid;
	int cmp = 0;
	int update = false;
	struct vlan_ethhdr *vlan = frame->vlan;
	struct ksz_dlr_frame *beacon = frame->body;
	struct ksz_dlr_gateway_capable *attrib = &info->attrib;
	struct ksz_dlr_beacon_info *beacon_info = &info->beacon_info[port];
#ifdef CONFIG_HAVE_DLR_HW
	struct ksz_sw *sw = info->sw_dev;
#endif

	/* Only accepted beacon from active supervisor is processed. */
	cmp = memcmp(vlan->h_source, attrib->active_super_addr.addr,
		ETH_ALEN);
	if (cmp) {
#if 0
		struct ksz_dlr_super_info found;

		memcpy(&found.prec_addr[1], vlan->h_source, ETH_ALEN);
		found.port = port;
		info->rogue_super = &found;
		dlr_tx_learning_update(info);
#endif
		return false;
	}

	/* Process accepted beacon. */
	if (info->new_supervisor) {
		if (info->notifications & DLR_INFO_CFG_CHANGE)
			dlr_notify_cfg_change(info, 1);
		update = true;
	}

	interval = ntohl(beacon->data.beacon.interval);
	timeout = ntohl(beacon->data.beacon.timeout);

	/* Used to determine beacon timeout in software simulation. */
	beacon_info->rcv_once = 1;
	beacon_info->timeout_start = 0;

	if (!info->skip_beacon && info->drop_beacon) {
		dropBeacons(info);
		info->beacon_info[0].timeout =
		info->beacon_info[1].timeout = 0;
		return update;
	}
	if (update && info->skip_beacon)
		acceptBeacons(info);

	/* Not running as supervisor. */
	if ((DLR_ACTIVE_SUPERVISOR != info->node &&
	    info->ring_state != beacon->data.beacon.ring_state) ||
	    update) {
		if ((info->notifications & DLR_INFO_CFG_CHANGE) &&
		    info->ring_state != beacon->data.beacon.ring_state)
			dlr_notify_cfg_change(info, 2);
		info->ring_state = beacon->data.beacon.ring_state;

		/* Set in following code. */
		info->p1_rcvd = info->p2_rcvd =
		info->one_rcvd = info->both_rcvd = 0;
		beacon_info->timeout = 0;

#ifdef DBG_DLR_STATE
		if (RING_FAULT_STATE == info->ring_state) {
			dbg_dlr(info, "ring fault");
		}
#endif
		/* Get back into backup mode. */
		if (7 == info->beacon_timeout_ports)
			info->beacon_timeout_ports = 0;
	}
	if (1 == port) {
		info->p2_rcvd = 1;
		info->p2_timeout = 0;
		info->p2_down = 0;
	} else {
		info->p1_rcvd = 1;
		info->p1_timeout = 0;
		info->p1_down = 0;
	}
	if (!info->p1_timeout && !info->p2_timeout)
		info->one_timeout = 0;
	info->both_timeout = 0;

	/* Change down state as beacon can be received before link status. */
	if (!info->p1_down && !info->p2_down)
		info->one_down = 0;
	info->both_down = 0;

	if (info->p1_rcvd && info->p2_rcvd) {

		/* Running as supervisor. */
		if (DLR_ACTIVE_SUPERVISOR == info->node ||
		    RING_NORMAL_STATE == info->ring_state) {
			if (!info->both_rcvd)
				update = true;
			info->both_rcvd = 1;
			info->one_rcvd = 0;
		}
	} else {
		if (!info->one_rcvd)
			update = true;
		info->one_rcvd = 1;
		beacon_info->timeout = 0;
	}
	if (attrib->active_super_prec != beacon->data.beacon.precedence) {
		attrib->active_super_prec = beacon->data.beacon.precedence;
	}
	vid = info->vid;
	if (vlan->h_vlan_proto == htons(ETH_P_8021Q))
		vid = ntohs(vlan->h_vlan_TCI) & ((1 << VLAN_PRIO_SHIFT) - 1);
	if (info->vid != vid) {

		/* Use current VID. */
		update_vlan(info, vid);
		if (attrib->cap & DLR_CAP_SUPERVISOR_CAPABLE)
			attrib->super_cfg.vid = vid;
		if (attrib->super_cfg.enable) {
			attrib->super_cfg.vid = vid;
#ifdef CONFIG_HAVE_DLR_HW
			sw->ops->acquire(sw);
			dlr_hw_set_vlan_id(sw, info->vid);
			sw->ops->release(sw);
#endif
		}
	}
	if (info->beacon_interval != interval) {
#ifdef DBG_DLR_OPER
		dbg_msg("interval %u %u\n", info->beacon_interval, interval);
#endif

		/* Use current beacon interval. */
		info->beacon_interval = interval;
		if (attrib->cap & DLR_CAP_SUPERVISOR_CAPABLE)
			attrib->super_cfg.beacon_interval = interval;
		if (attrib->super_cfg.enable) {
			attrib->super_cfg.beacon_interval = interval;
#ifdef CONFIG_HAVE_DLR_HW
			sw->ops->acquire(sw);
			dlr_hw_set_interval(sw, info->beacon_interval);
			sw->ops->release(sw);
#endif
		}
	}
	if (info->beacon_timeout != timeout) {
#ifdef DBG_DLR_OPER
		dbg_msg("timeout %u %u\n", info->beacon_timeout, timeout);
#endif

		/* Use current beacon timeout. */
		info->beacon_timeout = timeout;
		if (attrib->cap & DLR_CAP_SUPERVISOR_CAPABLE)
			attrib->super_cfg.beacon_timeout = timeout;
		if (attrib->super_cfg.enable) {
			attrib->super_cfg.beacon_timeout = timeout;
#ifdef CONFIG_HAVE_DLR_HW
			sw->ops->acquire(sw);
			dlr_hw_set_timeout(sw, info->beacon_timeout);
			sw->ops->release(sw);
#endif
		}
		info->p1_set = info->p2_set = 1;
	}
#ifdef DBG_DLR_BEACON
	if (update || dbg_bcn > 0) {
		u32 seqid = ntohl(beacon->hdr.seqid);
		dbg_msg("B: %d=%d:%d; r=%d:%d R=%d:%d; %08lx %d %lx\n",
			port,
			beacon->data.beacon.ring_state, info->ring_state,
			info->p1_rcvd, info->p2_rcvd,
			info->one_rcvd, info->both_rcvd,
			seqid, info->new_supervisor,
			jiffies);
	}
#endif

	beacon_info->interval = 0;
	if (info->p1_rcvd && info->p1_set) {
		info->p1_set = 0;
#ifdef CONFIG_HAVE_ACL_HW
		setup_acl_beacon_timeout(info, info->ports[0]);
#endif
	}
	if (info->p2_rcvd && info->p2_set) {
		info->p2_set = 0;
#ifdef CONFIG_HAVE_ACL_HW
		setup_acl_beacon_timeout(info, info->ports[1]);
#endif
	}
	return update;
}  /* handleBeacon */

static int handleSignOn(struct ksz_dlr_info *info,
	struct ksz_dlr_rx_frame *frame, int port)
{
	int i;
	struct vlan_ethhdr *vlan = frame->vlan;
	struct ksz_dlr_frame *signon = frame->body;
	u16 num = ntohs(signon->data.signon.num);
	struct ksz_dlr_node *node = signon->data.signon.node;

	/* Ignore if not NORMAL_STATE. */
	if (info->state != DLR_ACTIVE_NORMAL_STATE &&
	    info->state != DLR_NORMAL_STATE &&
	    !(info->overrides & DLR_TEST)) {
#ifdef DBG_DLR_ANN_SIGNON
		dbg_dlr(info, " ?signon");
#endif
#ifdef DBG_DLR_BEACON
		dbg_bcn = 10;
#endif
		return false;
	}
#ifdef DBG_DLR_BEACON
	dbg_bcn = 2;
#endif
	if (DLR_ACTIVE_SUPERVISOR == info->node &&
	    !memcmp(node->addr, info->src_addr, ETH_ALEN)) {
		struct ksz_dlr_node_info *cur;

#ifdef DBG_DLR_SIGNON
		dbg_msg("signon: %d; %d; %02x\n", num, port, vlan->h_dest[0]);
		dbg_msg("%02x:%02x:%02x:%02x:%02x:%02x\n",
			node->addr[0],
			node->addr[1],
			node->addr[2],
			node->addr[3],
			node->addr[4],
			node->addr[5]);
#endif
		for (i = 0; i < num; i++, node++) {
			if (i && !memcmp(node->addr, info->src_addr, ETH_ALEN))
				continue;
#ifdef DBG_DLR_SIGNON
			dbg_msg("%d %02x:%02x:%02x:%02x:%02x:%02x\n", i,
				node->addr[0],
				node->addr[1],
				node->addr[2],
				node->addr[3],
				node->addr[4],
				node->addr[5]);
#endif
			cur = &info->nodes[info->attrib.participants_cnt];
			memcpy(&cur->signon, node,
				sizeof(struct ksz_dlr_node));
			cur->p1_down = cur->p2_down =
			cur->p1_lost = cur->p2_lost = 0;
			info->attrib.participants_cnt++;
		}

		/* Addressed to the supervisor instead of multicast address. */
		if (!memcmp(info->src_addr, vlan->h_dest, ETH_ALEN)) {
			memcpy(info->signon_addr, vlan->h_source,
				ETH_ALEN);
			dlr_tx_signon(info, 0);
		} else
			disableSignOnTimer(info);
	} else {
		int len;
		struct ksz_dlr_tx_frame *tx = (struct ksz_dlr_tx_frame *)
			info->signon_frame;

		if ((info->overrides & DLR_TEST) && info->ignore_req) {
			++info->req_cnt[0];
			if (info->req_cnt[0] <= info->ignore_req)
				printk(KERN_INFO
					"ignore SignOn: %d\n",
					info->req_cnt[0]);
			if (info->req_cnt[0] <= info->ignore_req)
				return false;
			info->req_cnt[0] = 0;
		}
		len = sizeof(struct ksz_dlr_hdr) +
			sizeof(struct ksz_dlr_signon) +
			(num - 1) * sizeof(struct ksz_dlr_node);
		memcpy(info->signon_frame, vlan, ETH_ALEN * 2);
		memcpy(&tx->body, signon, len);
		len += sizeof(struct vlan_ethhdr);
		info->rx_port = port;
		info->tx_port = (port + 1) & 1;
		dlr_tx_signon(info, len);
		if (info->active_port != (1 << info->ports[info->rx_port]))
			setupDir(info, port);
	}
	return false;
}  /* handleSignOn */

static int handleLocateFault(struct ksz_dlr_info *info,
	struct ksz_dlr_rx_frame *frame, int port)
{
	struct vlan_ethhdr *vlan = frame->vlan;

	/* Ignore if not FAULT_STATE. */
	if (info->state != DLR_FAULT_STATE &&
	    !(info->overrides & DLR_TEST)) {
		dbg_msg(" ?%s %d\n", __func__, port);
		return false;
	}
	if (info->node != DLR_ACTIVE_SUPERVISOR &&
	    !memcmp(vlan->h_source, info->attrib.active_super_addr.addr,
	    ETH_ALEN)) {
		info->fault_jiffies = jiffies;
		if (info->p1_down || info->p2_down)
			dlr_tx_status(info, 0);
		else if (!info->neigh_chk) {
			info->neigh_chk = 1;
			ksz_start_timer(&info->neigh_chk_timer_info,
				info->neigh_chk_timer_info.period);
			info->neigh_chk_timer_info.max = 3;
			info->p1_lost = info->p2_lost = 0;
			info->port_chk[0] = info->port_chk[1] = 1;
			dlr_tx_chk_req(info, 0);
			dlr_tx_chk_req(info, 1);
		}
	} else {
		dbg_msg("%s ignored\n", __func__);
	}
	return false;
}  /* handleLocateFault */

static int handleAnnounce(struct ksz_dlr_info *info,
	struct ksz_dlr_rx_frame *frame, int port)
{
	u32 seqid;
	u16 vid;
	struct vlan_ethhdr *vlan = frame->vlan;
	struct ksz_dlr_frame *announce = frame->body;
	int new = 0;
	struct ksz_dlr_gateway_capable *attrib = &info->attrib;

	/* Supervisor direction is not set yet. */
	if (RING_NORMAL_STATE == announce->data.announce.ring_state &&
	    DLR_NORMAL_STATE == info->state &&
	    (!info->active_port || info->rx_port != port)) {
#ifdef DBG_DLR_OPER
		dbg_msg("%s p=%d r=%d x%x\n", __func__, port, info->rx_port,
			info->active_port);
#endif
		setup_dir(info, port);
	}

#ifdef DBG_DLR_STATE
	if (DLR_ANNOUNCE_NODE != info->node) {
		if (announce->data.announce.ring_state != info->ring_state)
			dbg_msg("  ann: p=%d r=%d != %d\n",
				port, info->ring_state,
				announce->data.announce.ring_state);
		else if (RING_NORMAL_STATE == info->ring_state &&
			 info->state != DLR_NORMAL_STATE)
			dbg_msg("  ann ring normal: p=%d s=%d\n",
				port, info->state);
	}
#endif

	/* Rely on Announce frame to determine ring state. */
	if (info->skip_beacon) {
		if (memcmp(vlan->h_source, attrib->active_super_addr.addr,
		    ETH_ALEN)) {
dbg_msg(" diff super\n");
			dlr_set_addr(&attrib->active_super_addr,
				announce->hdr.ip_addr, vlan->h_source);
		}
		if (!memcmp(vlan->h_source, attrib->active_super_addr.addr,
		    ETH_ALEN) && info->ring_state !=
		    announce->data.announce.ring_state) {
			if ((info->notifications & DLR_INFO_CFG_CHANGE) &&
			    info->ring_state !=
			    announce->data.announce.ring_state)
				dlr_notify_cfg_change(info, 2);
			info->ring_state = announce->data.announce.ring_state;
			acceptBeacons(info);
#ifdef DBG_DLR_BEACON
			dbg_bcn += 4;
#endif
			return true;
		}
	}

	if (DLR_ACTIVE_SUPERVISOR == info->node) {
#if 0
		dbg_msg("%s ignored %d %d %d\n", __func__, port,
			announce->data.announce.ring_state, info->skip_beacon);
		if (vlan)
			dbg_msg("src: %02x:%02x:%02x:%02x:%02x:%02x\n",
				vlan->h_source[0], vlan->h_source[1],
				vlan->h_source[2], vlan->h_source[3],
				vlan->h_source[4], vlan->h_source[5]);
#endif
		return false;
	}
	if (DLR_SUPERVISOR == info->node)
		goto done;
	if (DLR_ANNOUNCE_NODE != info->node)
		return false;

	info->rx_port = port;
	info->tx_port = (port + 1) & 1;
	seqid = ntohl(announce->hdr.seqid);

	if (memcmp(vlan->h_source, attrib->active_super_addr.addr, ETH_ALEN) ||
	    info->ann_timeout) {
		memcpy(info->last_sup.addr, attrib->active_super_addr.addr,
			ETH_ALEN);
		dlr_set_addr(&attrib->active_super_addr,
			announce->hdr.ip_addr, vlan->h_source);
		info->new_supervisor = 1;
		new = 1;
		if (info->notifications & DLR_INFO_CFG_CHANGE)
			dlr_notify_cfg_change(info, 1);
	} else {
		/* Check valid sequence number. */
		if (!seq_ahead(info->seqid_announce, seqid))
			return false;
	}
	info->seqid_announce = seqid;
	if (announce->data.announce.ring_state != info->ring_state || new) {
		if ((info->notifications & DLR_INFO_CFG_CHANGE) &&
		    info->ring_state != announce->data.announce.ring_state)
			dlr_notify_cfg_change(info, 2);
		info->ring_state = announce->data.announce.ring_state;
		info->ann_rcvd = 1;
		new = 1;
	}
	if (vlan->h_vlan_proto == htons(ETH_P_8021Q)) {
		vid = ntohs(vlan->h_vlan_TCI) & ((1 << VLAN_PRIO_SHIFT) - 1);
		if (vid != info->vid) {
			update_vlan(info, vid);
			new = 1;
		}
	}

done:
	info->ann_timeout = 0;

	ksz_stop_timer(&info->announce_timeout_timer_info);
	ksz_start_timer(&info->announce_timeout_timer_info,
		info->announce_timeout_timer_info.period);
	info->announce_timeout_timer_info.max = 1;
	return new;
}  /* handleAnnounce */

static int handleNeighChkReq(struct ksz_dlr_info *info,
	struct ksz_dlr_rx_frame *frame, int port)
{
	struct ksz_dlr_frame *req = frame->body;

	/* Ignore if not FAULT_STATE. */
	if (info->state != DLR_FAULT_STATE &&
	    info->state != DLR_ACTIVE_FAULT_STATE &&
	    !(info->overrides & DLR_TEST))
		return false;
	if (info->overrides & DLR_TEST) {
		printk(KERN_INFO "req: p=%d s=%08x %d; %lx\n",
			port, ntohl(req->hdr.seqid), req->hdr.src_port,
			jiffies);
	}
	if ((info->overrides & DLR_TEST) && info->ignore_req) {
		++info->req_cnt[port];
		if (info->req_cnt[port] <= info->ignore_req)
			return false;
		info->req_cnt[port] = 0;
	}
	info->port_rcv[port] = req->hdr.src_port;
	info->seqid_rcv[port] = ntohl(req->hdr.seqid);
	dlr_tx_chk_resp(info, port);
	return false;
}  /* handleNeighChkReq */

static int handleNeighChkResp(struct ksz_dlr_info *info,
	struct ksz_dlr_rx_frame *frame, int port)
{
	struct ksz_dlr_frame *resp = frame->body;
	int src_port = port ? DLR_PORT_2 : DLR_PORT_1;

	/* Ignore if not FAULT_STATE. */
	if (info->state != DLR_FAULT_STATE &&
	    info->state != DLR_ACTIVE_FAULT_STATE &&
	    !(info->overrides & DLR_TEST))
		return false;
	if (info->overrides & DLR_TEST) {
		printk(KERN_INFO "resp: p=%d s=%08x %d; %08x - %08x; %lx\n",
			port, ntohl(resp->hdr.seqid),
			resp->data.neigh_chk_resp.src_port,
			info->seqid_first[port],
			info->seqid_chk[port], jiffies);
	}
	if (src_port == resp->data.neigh_chk_resp.src_port) {
		u32 seqid = ntohl(resp->hdr.seqid);

		if (seq_in(info->seqid_first[port], info->seqid_chk[port],
		    seqid)) {
			if (port)
				info->p2_down = info->p2_lost = 0;
			else
				info->p1_down = info->p1_lost = 0;
			info->port_chk[port] = 0;
			if (!info->port_chk[(port + 1) & 1]) {
				ksz_stop_timer(&info->neigh_chk_timer_info);
				info->neigh_chk = 0;
			}
		}
	}
	return false;
}  /* handleNeighChkResp */

static int handleFlushTables(struct ksz_dlr_info *info,
	struct ksz_dlr_rx_frame *frame, int port)
{
	struct ksz_dlr_frame *flush = frame->body;

	/* Ignore if not in NORMAL_STATE or FAULT_STATE. */
	if (info->state <= DLR_IDLE_STATE &&
	    !(info->overrides & DLR_TEST))
		return false;
	dlr_flush(info);
	if (flush->data.flush.learning_update_enable)
		dlr_tx_learning_update(info);

	return false;
}  /* handleFlushTables */

static int handleLinkStatus(struct ksz_dlr_info *info,
	struct ksz_dlr_rx_frame *frame, int port)
{
	struct vlan_ethhdr *vlan = frame->vlan;
	struct ksz_dlr_frame *status = frame->body;

	if (info->overrides & DLR_TEST) {
		printk(KERN_INFO
			"link: %02x:%02x:%02x:%02x:%02x:%02x %d:%d %d\n",
			vlan->h_source[0], vlan->h_source[1], vlan->h_source[2],
			vlan->h_source[3], vlan->h_source[4], vlan->h_source[5],
			status->data.status.port1_active,
			status->data.status.port2_active,
			status->data.status.neighbor);
	}
	if (DLR_ACTIVE_SUPERVISOR == info->node) {
		int i;
		struct ksz_dlr_node_info *node;

#ifdef DBG_DLR_STATE
		dbg_msg("link: %02x:%02x:%02x:%02x:%02x:%02x %x %d:%d %d\n",
			vlan->h_source[0],
			vlan->h_source[1],
			vlan->h_source[2],
			vlan->h_source[3],
			vlan->h_source[4],
			vlan->h_source[5],
			ntohl(status->hdr.seqid),
			status->data.status.port1_active,
			status->data.status.port2_active,
			status->data.status.neighbor);
#endif
		for (i = 1; i < info->attrib.participants_cnt; i++) {
			node = &info->nodes[i];
			if (!memcmp(node->signon.addr, vlan->h_source,
			    ETH_ALEN)) {
				if (status->data.status.neighbor) {
					if (status->data.status.port1_active) {
						node->p1_down = 0;
						node->p1_lost = 0;
					} else {
						node->p1_lost = 1;
					}
					if (status->data.status.port2_active) {
						node->p2_down = 0;
						node->p2_lost = 0;
					} else {
						node->p2_lost = 1;
					}
				} else {
					if (status->data.status.port1_active) {
						node->p1_down = 0;
					} else {
						node->p1_down = 1;
					}
					if (status->data.status.port2_active) {
						node->p2_down = 0;
					} else {
						node->p2_down = 1;
					}
				}
				break;
			}
		}
		if (!status->data.status.port1_active ||
		    !status->data.status.port2_active) {
			dlr_set_addr(&info->attrib.last_active[port],
				status->hdr.ip_addr, vlan->h_source);
			if (info->notifications & DLR_INFO_LINK_LOST)
				dlr_notify_link_lost(info);
			return true;
		}
	} else {
		dbg_msg("%s ignored\n", __func__);
	}
	return false;
}  /* handleLinkStatus */

static int handleLearningUpdate(struct ksz_dlr_info *info,
	struct ksz_dlr_rx_frame *frame, int port)
{
	struct vlan_ethhdr *vlan = frame->vlan;

#ifdef DBG_DLR_SUPERVISOR
	dbg_msg("%s %d %d\n", __func__, info->node, port);
#endif
	if (!memcmp(info->src_addr, vlan->h_dest, ETH_ALEN)) {
		if (!newSupervisor) {
dbg_msg(" %d %d %d  ", info->state, info->node, info->precedence);
dbg_msg(" to self!\n");
			dlr_chk_supervisor(info);
		}
	}
	if (DLR_SUPERVISOR <= info->node) {
		if (!memcmp(info->src_addr, vlan->h_source, ETH_ALEN)) {
dbg_msg("%s %d\n", __func__, info->node);
		}
	}
	return false;
}  /* handleLearningUpdate */

static void dlr_clr_last_beacon(struct ksz_dlr_info *info, int missed)
{
	int last = info->LastBcnRcvPort;

	info->LastBcnRcvPort &= ~missed;
	if (last != info->LastBcnRcvPort &&
	    0 == info->LastBcnRcvPort) {
#ifdef DBG_DLR_STATE
		if (DLR_SUPERVISOR == info->node)
			dbg_msg("become active\n");
		else if (DLR_ACTIVE_SUPERVISOR != info->node)
			dbg_msg("become idle\n");
#endif
	}
}  /* dlr_clr_last_beacon */

static int handleBeaconTimeout(struct ksz_dlr_info *info, int port)
{
	struct ksz_dlr_beacon_info *beacon_info = &info->beacon_info[port];

	if (1 == port) {
		info->p2_rcvd = 0;
		info->p2_timeout = 1;
	} else {
		info->p1_rcvd = 0;
		info->p1_timeout = 1;
	}
	memset(&beacon_info->last, 0, sizeof(struct ksz_dlr_beacon));
	beacon_info->timeout = 0;
	memset(&info->last_beacon[port], 0, sizeof(struct ksz_dlr_tx_frame));
	if (info->p1_rcvd || info->p2_rcvd)
		info->one_rcvd = 1;
	else
		info->one_rcvd = 0;
	info->both_rcvd = 0;
	if ((info->p1_timeout && info->p2_timeout)) {
		info->both_timeout = 1;
		info->one_timeout = 0;
		info->chk_hw = 1;
	} else
		info->one_timeout = 1;

#ifdef DBG_DLR_STATE
	dbg_dlr(info, "timeout");
#endif
	if (info->both_timeout)
		info->p1_timeout = info->p2_timeout = 0;
	dlr_clr_last_beacon(info, port ? 2 : 1);

	/* Automatic backup supervisor will start. */
	if (info->both_timeout && DLR_SUPERVISOR == info->node)
		info->start = 1;
	return true;
}  /* handleBeaconTimeout */

static int handleLinkChange(struct ksz_dlr_info *info, int link1, int link2)
{
	int change[2];
	int down[2];
	int update = false;
	int going_up = false;
	int missed = 0;

	/* State machine not ready yet. */
	if (!info->state)
		return update;
	down[0] = down[1] = 0;
	change[0] = !link1 ^ info->p1_down;
	change[1] = !link2 ^ info->p2_down;
	if (link1)
		info->p1_down = 0;
	else
		info->p1_down = 1;
	if (link2)
		info->p2_down = 0;
	else
		info->p2_down = 1;
	if (DLR_ACTIVE_SUPERVISOR == info->node) {
		struct ksz_dlr_node_info *node;

		node = find_dlr_node(info, info->src_addr);
		if (node) {
			node->p1_down = info->p1_down;
			node->p2_down = info->p2_down;
		}
	}
	if ((!change[0] || link1) && (!change[1] || link2)) {
		going_up = true;
		info->fault_jiffies = 0;
		return update;
	}
	if (info->p1_down && info->p2_down) {
		if (!info->both_down)
			update = true;
		info->both_down = 1;
		info->one_down = 0;
		info->one_rcvd = 0;
	} else if (info->p1_down || info->p2_down) {
		if (!info->one_down)
			update = true;
		info->both_down = 0;
		info->one_down = 1;
		if (info->both_rcvd)
			info->one_rcvd = 1;
	} else {
		info->one_down = 0;
		info->both_down = 0;
	}

	/* Reset beacon timeout if the link also goes down. */
	if (info->one_timeout) {
		if ((info->p1_timeout && info->p1_down) ||
		    (info->p2_timeout && info->p2_down)) {
			info->one_timeout = 0;
			info->p1_timeout = info->p2_timeout = 0;
		}
	}
	if (info->p1_down) {
		info->p1_rcvd = 0;
		info->both_rcvd = 0;
		missed |= 1;

		/* Stop neighbor check if link is down (unlikely). */
		if (info->port_chk[0] && info->port_chk[0] < 3)
			info->port_chk[0] = 3;
	}
	if (info->p2_down) {
		info->p2_rcvd = 0;
		info->both_rcvd = 0;
		missed |= 2;

		/* Stop neighbor check if link is down (unlikely). */
		if (info->port_chk[1] && info->port_chk[1] < 3)
			info->port_chk[1] = 3;
	}
	dlr_clr_last_beacon(info, missed);
	down[0] = info->p1_down;
	down[1] = info->p2_down;
	if (info->node != DLR_ANNOUNCE_NODE) {
		info->beacon_info[0].timer = !down[0];
		info->beacon_info[1].timer = !down[1];
	}
	if (going_up)
		update = false;
	if ((info->p1_down || info->p2_down) && !going_up) {
		int p;

#ifdef DBG_DLR_STATE
		dbg_msg("Lo: %d:%d %x\n", down[0], down[1],
			info->LastBcnRcvPort);
#endif
		if (info->fault_jiffies)
			dbg_msg("time from fault: %lu\n",
				jiffies - info->fault_jiffies);
		if (DLR_ACTIVE_SUPERVISOR == info->node) {
			struct ksz_dlr_gateway_capable *attrib = &info->attrib;

			for (p = 0; p < 2; p++) {
				if (down[p]) {
					dlr_set_addr(&attrib->last_active[p],
						info->ip_addr, info->src_addr);
				}
			}
		}

		/* Reset last beacon in case timeout is not processed. */
		for (p = 0; p < 2; p++) {
			if (down[p]) {
				memset(&info->beacon_info[p].last, 0,
					sizeof(struct ksz_dlr_beacon));
				info->beacon_info[p].timeout = 0;
				memset(&info->last_beacon[p], 0,
					sizeof(struct ksz_dlr_tx_frame));
			}
		}
	}
	return update;
}  /* handleLinkChange */

static void LocateFault(struct ksz_dlr_info *info)
{
	if (info->node != DLR_ACTIVE_SUPERVISOR)
		return;
	dlr_tx_locate_fault(info);
}  /* LocateFault */

static void NeighborCheck(struct ksz_dlr_info *info)
{
	struct ksz_dlr_gateway_capable *attrib = &info->attrib;

	if (!info->p1_down || !info->p2_down) {
		info->neigh_chk = 1;
		ksz_start_timer(&info->neigh_chk_timer_info,
			info->neigh_chk_timer_info.period);
		info->neigh_chk_timer_info.max = 3;
	}
	if (info->p1_down) {
		dlr_set_addr(&attrib->last_active[0],
			info->ip_addr, info->src_addr);
	} else {
		info->p1_lost = 0;
		info->port_chk[0] = 1;
		dlr_tx_chk_req(info, 0);
	}
	if (info->p2_down) {
		dlr_set_addr(&attrib->last_active[1],
			info->ip_addr, info->src_addr);
	} else {
		info->p2_lost = 0;
		info->port_chk[1] = 1;
		dlr_tx_chk_req(info, 1);
	}
}  /* NeighborCheck */

static void startSignOn(struct ksz_dlr_info *info, int now)
{
	info->attrib.participants_cnt = 0;
	memcpy(info->signon_addr, MAC_ADDR_SIGNON, ETH_ALEN);
	ksz_start_timer(&info->signon_timer_info,
		info->signon_timer_info.period);
	if (!info->signon_delay || !info->ann_delay) {
		info->signon_delay = 0;
		if (now && !info->ann_first)
			dlr_tx_signon(info, 0);
		else
			info->tx_signon = true;
	}
#ifdef DBG_DLR_OPER
	else
		dbg_msg("%s %d %d %lx\n", __func__,
			info->signon_delay, info->ann_delay,
			jiffies);
#endif
}  /* startSignOn */

static void sendLinkStatus(struct ksz_dlr_info *info)
{
	/* Supervisor is known. */
	if (info->attrib.active_super_addr.addr[0] ||
	    info->attrib.active_super_addr.addr[1])
		dlr_tx_status(info, false);
}  /* sendLinkStatus */

#if 1
static int getting_last_active;
#endif

static void dlr_clear(struct ksz_dlr_info *info)
{
	struct ksz_dlr_beacon_info *beacon_info;
	int p;

	info->p1_rcvd = info->p2_rcvd =
	info->one_rcvd = info->both_rcvd =
	info->p1_timeout = info->p2_timeout =
	info->one_timeout = info->both_timeout = 0;
	for (p = 0; p < 2; p++ ) {
		beacon_info = &info->beacon_info[p];
		beacon_info->timer =
		beacon_info->rcv_once =
		beacon_info->timeout_start =
		beacon_info->timeout_stop = 0;
		beacon_info->timeout = 0;
		memset(&beacon_info->last, 0, sizeof(struct ksz_dlr_beacon));
		memset(&info->last_beacon[p], 0,
			sizeof(struct ksz_dlr_tx_frame));
	}
	memset(info->supers, 0, sizeof(struct ksz_dlr_super_info) *
		DLR_SUPERVISOR_NUM);
#if 1
	getting_last_active = 0;
#endif
}  /* dlr_clear */

struct dlr_state {
	int change;
	int delay_ann;
	int new_state;
};

static void dlr_idle_init(struct ksz_dlr_info *info, struct dlr_state *state)
{
	struct ksz_dlr_gateway_capable *attrib = &info->attrib;

#ifdef DBG_DLR_STATE
	dbg_dlr(info, "idle");
	dlr_print(info, "idle");
#endif

	oneBeaconRcvd = twoBeaconsRcvd = 0;
	oneBeaconTimeout = twoBeaconsTimeout = 0;
	announcedState = RING_FAULT_STATE;

	attrib->net_topology = DLR_TOPOLOGY_LINEAR;
	attrib->net_status = DLR_NET_NORMAL;
	attrib->super_status = DLR_STAT_NO_SUPERVISOR;
	memset(&attrib->active_super_addr, 0,
		sizeof(struct ksz_dlr_active_node));
	attrib->active_super_prec = 0;

	if (info->skip_beacon)
		acceptBeacons(info);
	disableLearn(info, 1);
	flushMacTable(info);
	dlr_set_state(info);
	if (info->notifications & DLR_INFO_CFG_CHANGE)
		dlr_notify_cfg_change(info, 2);
}  /* dlr_idle_init */

static void dlr_idle_next(struct ksz_dlr_info *info, struct dlr_state *state)
{
	if (twoBeaconsRcvd && !faultState) {
		state->new_state = DLR_NORMAL_STATE;
	}
	if (oneBeaconRcvd || (twoBeaconsRcvd && faultState)) {
		state->new_state = DLR_FAULT_STATE;
	}
}  /* dlr_idle_next */

static void dlr_ann_idle_init(struct ksz_dlr_info *info,
	struct dlr_state *state)
{
	struct ksz_dlr_gateway_capable *attrib = &info->attrib;

#ifdef DBG_DLR_STATE
	dbg_dlr(info, "ann idle");
	dlr_print(info, "idle");
#endif

	announceRcvd = 0;
	announcedState = 0;

	attrib->net_topology = DLR_TOPOLOGY_LINEAR;
	attrib->net_status = DLR_NET_NORMAL;
	attrib->super_status = DLR_STAT_NO_SUPERVISOR;
	memset(&attrib->active_super_addr, 0,
		sizeof(struct ksz_dlr_active_node));
	attrib->active_super_prec = 0;
}  /* dlr_ann_idle_init */

static void dlr_ann_idle_next(struct ksz_dlr_info *info,
	struct dlr_state *state)
{
	if (announceRcvd) {
		state->new_state = fromRingState;
	}
}  /* dlr_ann_idle_next */

static void dlr_fault_init(struct ksz_dlr_info *info, struct dlr_state *state)
{
	struct ksz_dlr_gateway_capable *attrib = &info->attrib;

#ifdef DBG_DLR_BEACON
	dbg_msg("  %08x - %08x; %08x - %08x;\n",
		info->seqid_accept[0], info->seqid_last[0],
		info->seqid_accept[1], info->seqid_last[1]);
#endif
#ifdef DBG_DLR_STATE
	dbg_dlr(info, "fault");
	dlr_print(info, "fault");
#endif

	newSupervisor = 0;
	if (DLR_ACTIVE_SUPERVISOR == info->node)
		announcedState = RING_FAULT_STATE;

	attrib->net_topology = DLR_TOPOLOGY_RING;
	attrib->net_status = DLR_NET_RING_FAULT;
	if (DLR_BEACON_NODE >= info->node)
		attrib->super_status = DLR_STAT_RING_NODE;
	else
		attrib->super_status = DLR_STAT_BACKUP_SUPERVISOR;

#if 1
	disableLearn(info, 1);
#endif
	flushMacTable(info);
#if 0
	disableLearn(info, 0);
#endif
	dlr_set_state(info);
	if (linkLoss) {
		linkLoss = 0;
		sendLinkStatus(info);
	}
}  /* dlr_fault_init */

static void dlr_fault_next(struct ksz_dlr_info *info, struct dlr_state *state)
{
	if (twoBeaconsRcvd && !faultState) {
		newSupervisor = 0;
		disableNeighChkTimers(info);
		state->new_state = DLR_NORMAL_STATE;
	}
	if ((twoBeaconsTimeout || (oneBeaconTimeout && !oneBeaconRcvd)) &&
	    info->LastBcnRcvPort)
		dbg_dlr(info, "  ! last beacon");
	if (!info->LastBcnRcvPort) {
		if (linkDown)
dbg_msg(" f linkDown\n");
		disableNeighChkTimers(info);
		if (DLR_BEACON_NODE >= info->node)
			state->new_state = DLR_IDLE_STATE;
		else
			state->new_state = DLR_PREPARE_STATE;
	}
	if (linkLoss) {
		linkLoss = 0;
		sendLinkStatus(info);
	}
	if (newSupervisor) {
		newSupervisor = 0;
		flushMacTable(info);
	}

	/* Apply only to supervisor. */
	if (newValue) {
		if (updateValues(info))
			state->new_state = DLR_PREPARE_STATE;
	}
	if (announceTimeout) {
		announceTimeout = false;
		dbg_msg("  ??? announce timeout\n");
		disableAnnounceTimeout(info);
		if (DLR_SUPERVISOR == info->node)
			state->new_state = DLR_PREPARE_STATE;
	}
}  /* dlr_fault_next */

static void dlr_ann_fault_init(struct ksz_dlr_info *info,
	struct dlr_state *state)
{
	struct ksz_dlr_gateway_capable *attrib = &info->attrib;

#ifdef DBG_DLR_STATE
	dbg_dlr(info, "fault");
	dlr_print(info, "fault");
#endif

	announceRcvd = 0;

	attrib->net_topology = DLR_TOPOLOGY_RING;
	attrib->net_status = DLR_NET_RING_FAULT;
	attrib->super_status = DLR_STAT_RING_NODE;

	flushMacTable(info);
	if (linkLoss) {
		linkLoss = 0;
		sendLinkStatus(info);
	}
}  /* dlr_ann_fault_init */

static void dlr_ann_fault_next(struct ksz_dlr_info *info,
	struct dlr_state *state)
{
	if (announceTimeout) {
		disableNeighChkTimers(info);
		state->new_state = DLR_IDLE_STATE;
	}
	if (linkDown) {
		disableAnnounceTimeout(info);
		disableNeighChkTimers(info);
		state->new_state = DLR_IDLE_STATE;
	}
	if (linkLoss) {
		linkLoss = 0;
		sendLinkStatus(info);
	}
	if (announceRcvd) {
		state->new_state = fromRingState;
	}
	if (newSupervisor) {
		newSupervisor = 0;
		disableNeighChkTimers(info);
	}
}  /* dlr_ann_fault_next */

static void dlr_normal_init(struct ksz_dlr_info *info, struct dlr_state *state)
{
	struct ksz_dlr_gateway_capable *attrib = &info->attrib;

#ifdef DBG_DLR_BEACON
	dbg_msg("  %08x - %08x; %08x - %08x;\n",
		info->seqid_accept[0], info->seqid_last[0],
		info->seqid_accept[1], info->seqid_last[1]);
#endif
#ifdef DBG_DLR_STATE
	dbg_dlr(info, "normal");
	dlr_print(info, "normal");
#endif

	newSupervisor = 0;

	attrib->net_topology = DLR_TOPOLOGY_RING;
	attrib->net_status = DLR_NET_NORMAL;
	if (DLR_BEACON_NODE >= info->node)
		attrib->super_status = DLR_STAT_RING_NODE;
	else
		attrib->super_status = DLR_STAT_BACKUP_SUPERVISOR;
	info->ok_ports = info->member;

	flushMacTable(info);
	disableLearn(info, 0);
	dlr_set_state(info);
}  /* dlr_normal_init */

static void dlr_normal_next(struct ksz_dlr_info *info, struct dlr_state *state)
{
	if (twoBeaconsTimeout || linkDown) {
		if (linkDown)
dbg_msg(" n linkDown\n");
		disableNeighChkTimers(info);
		if (DLR_BEACON_NODE >= info->node)
			state->new_state = DLR_IDLE_STATE;
		else
			state->new_state = DLR_FAULT_STATE;
	}
	if (newSupervisor || faultState || oneBeaconTimeout) {
		state->new_state = DLR_FAULT_STATE;
	}
	if (linkLoss) {
		state->new_state = DLR_FAULT_STATE;
	}
	if (announceTimeout) {
		announceTimeout = false;
		dbg_msg("  ??? announce timeout\n");
		disableAnnounceTimeout(info);
		if (DLR_SUPERVISOR == info->node)
			state->new_state = DLR_PREPARE_STATE;
	}

	/* Apply only to supervisor. */
	if (newValue) {
		if (updateValues(info))
			state->new_state = DLR_PREPARE_STATE;
	}
	if (state->new_state) {
		setupDir(info, -1);
		if (info->skip_beacon)
			acceptBeacons(info);
		info->beacon_info[0].timeout =
		info->beacon_info[1].timeout = 0;
	}
	if (DLR_FAULT_STATE == state->new_state) {
		struct ksz_dlr_gateway_capable *attrib = &info->attrib;

		attrib->fault_cnt++;
	}
}  /* dlr_normal_next */

static void dlr_ann_normal_init(struct ksz_dlr_info *info,
	struct dlr_state *state)
{
	struct ksz_dlr_gateway_capable *attrib = &info->attrib;

#ifdef DBG_DLR_STATE
	dbg_dlr(info, "normal");
	dlr_print(info, "normal");
#endif

	announceRcvd = 0;

	attrib->net_topology = DLR_TOPOLOGY_RING;
	attrib->net_status = DLR_NET_NORMAL;
	attrib->super_status = DLR_STAT_RING_NODE;
	info->ok_ports = info->member;

	flushMacTable(info);
	disableNeighChkTimers(info);
}  /* dlr_ann_normal_init */

static void dlr_ann_normal_next(struct ksz_dlr_info *info,
	struct dlr_state *state)
{
	if (announceTimeout) {
		state->new_state = DLR_IDLE_STATE;
	}
	if (announceRcvd) {
		state->new_state = fromRingState;
	}
	if (linkLoss) {
		state->new_state = DLR_FAULT_STATE;
	}
	if (state->new_state)
		setupDir(info, -1);
	if (DLR_FAULT_STATE == state->new_state) {
		struct ksz_dlr_gateway_capable *attrib = &info->attrib;

		attrib->fault_cnt++;
	}
}  /* dlr_ann_normal_next */

static void dlr_active_init(struct ksz_dlr_info *info, struct dlr_state *state)
{
	struct ksz_dlr_gateway_capable *attrib = &info->attrib;

#ifdef DBG_DLR_STATE
	dbg_dlr(info, "active");
#endif
	dlr_clear(info);
	info->beacon_info[0].timer =
	info->beacon_info[1].timer = 1;
#if 1
	getting_last_active = 0;
#endif

	/* Reset incoming and outgoing ports. */
	info->tx_port = info->port;
	info->rx_port = (info->tx_port + 1) & 1;
	info->LastBcnRcvPort = 0;
	info->node = DLR_ACTIVE_SUPERVISOR;
	info->interval = info->beacon_interval;

	attrib->net_topology = DLR_TOPOLOGY_RING;
	attrib->super_status = DLR_STAT_ACTIVE_SUPERVISOR;
	dlr_set_addr(&attrib->active_super_addr,
		info->ip_addr, info->src_addr);
	attrib->active_super_prec = attrib->super_cfg.prec;

	/* Supervisor source address may change. */
	info->p1_set = info->p2_set = 1;

	if (!newSupervisor) {
		enableSupervisor(info);
		disableAnnounceTimeout(info);
	}
	if (state->change > 0)
		state->change--;
}  /* dlr_active_init */

static void dlr_active_next(struct ksz_dlr_info *info, struct dlr_state *state)
{
	state->delay_ann = 1;
	state->new_state = DLR_ACTIVE_FAULT_STATE;
	if (newSupervisor)
		state->new_state = DLR_BACKUP_STATE;
	else if (info->notifications & DLR_INFO_CFG_CHANGE)
		dlr_notify_cfg_change(info, 1);
#ifdef DBG_DLR_BEACON_
	if (!dbg_bcn)
		dbg_bcn = 4;
#endif
}  /* dlr_active_next */

static void dlr_active_fault_init(struct ksz_dlr_info *info,
	struct dlr_state *state)
{
	struct ksz_dlr_gateway_capable *attrib = &info->attrib;

#ifdef DBG_DLR_SUPERVISOR
	dbg_msg("  %d %d;\n",
		info->beacon_info[0].timeout, info->beacon_info[1].timeout);
#endif
#ifdef DBG_DLR_STATE
	dbg_dlr(info, "active fault");
	dlr_print(info, "active fault");
#endif
	dbg_supervisor(info);
#ifdef DBG_DLR_BEACON
	dbg_bcn = 3;
#endif

	linkLoss = 0;
	if (!memcmp(info->attrib.active_super_addr.addr, info->src_addr,
	    ETH_ALEN))
		newSupervisor = 0;
	announcedState = RING_FAULT_STATE;

	attrib->net_status = DLR_NET_RING_FAULT;

	/* Reset timeout notification. */
	info->beacon_timeout_ports = 0;

#ifdef DBG_DLR_ANN_SIGNON
	dbg_ann = 3;
#endif
	flushMacTable(info);
	enableBothPorts(info);
	setupBeacons(info);
	enableAnnounce(info, state->delay_ann);

	/* Coming here from active normal state. */
	if (!state->delay_ann && !linkDown) {
#if 1
		getting_last_active = 1;
#endif
		LocateFault(info);
		NeighborCheck(info);
	}
	state->delay_ann = 0;
#if 0
	if (info->notifications & DLR_INFO_CFG_CHANGE)
		dlr_notify_cfg_change(info, 2);
#endif
}  /* dlr_active_fault_init */

static void dlr_active_fault_next(struct ksz_dlr_info *info,
	struct dlr_state *state)
{
	if (oneBeaconTimeout || twoBeaconsTimeout) {
		oneBeaconTimeout = twoBeaconsTimeout = 0;
		if (info->start && info->chk_hw)
			dlr_chk_supervisor(info);
	}
	if (twoBeaconsRcvd) {
		disableNeighChkTimers(info);
		state->new_state = DLR_ACTIVE_NORMAL_STATE;
	}
	if (newSupervisor) {
		disableNeighChkTimers(info);
		state->new_state = DLR_BACKUP_STATE;
	}
	if (!newSupervisor && newValue) {
		state->new_state = DLR_RESTART_STATE;
	}

	if (!state->new_state && DLR_ACTIVE_SUPERVISOR == info->node &&
	    memcmp(info->attrib.active_super_addr.addr, info->src_addr,
	    ETH_ALEN)) {
		printk(KERN_INFO "still active fault\n");
dbg_msg("prec: %02x %d\n", info->attrib.active_super_addr.addr[5],
info->precedence);
		state->new_state = DLR_BACKUP_STATE;
	}
}  /* dlr_active_fault_next */

static void dlr_active_normal_init(struct ksz_dlr_info *info,
	struct dlr_state *state)
{
	struct ksz_dlr_gateway_capable *attrib = &info->attrib;

#ifdef DBG_DLR_STATE
	dbg_dlr(info, "active normal");
	dlr_print(info, "active normal");
#endif
#ifdef DBG_DLR_BEACON
	dbg_bcn += 4;
#endif

	announcedState = RING_NORMAL_STATE;

	attrib->net_status = DLR_NET_NORMAL;
	memset(&attrib->last_active[0], 0,
		sizeof(struct ksz_dlr_active_node));
	memset(&attrib->last_active[1], 0,
		sizeof(struct ksz_dlr_active_node));
#if 1
	getting_last_active = 0;
#endif

	/* Allow timeout notification. */
	info->beacon_timeout_ports = 0;
	info->ok_ports = info->member;

#ifdef DBG_DLR_ANN_SIGNON
	dbg_ann = 3;
#endif
	enableOnePort(info);
	flushMacTable(info);
	setupBeacons(info);
	enableAnnounce(info, 0);

	/*
	 * Need to wait until the normal beacons are
	 * sent.
	 */
	info->signon_delay = 1;
	if (!info->signon_start) {
		info->signon_start = 1;
		startSignOn(info, true);
	}
	if (info->notifications & DLR_INFO_CFG_CHANGE)
		dlr_notify_cfg_change(info, 2);
}  /* dlr_active_normal_init */

static void dlr_active_normal_next(struct ksz_dlr_info *info,
	struct dlr_state *state)
{
	struct ksz_dlr_gateway_capable *attrib = &info->attrib;

	if ((oneBeaconTimeout || twoBeaconsTimeout) && !linkLoss) {
#ifdef DBG_DLR_STATE
		dbg_dlr(info, "active timeout");
#endif
		disableSignOnTimer(info);
		if (DLR_ACTIVE_SUPERVISOR == info->node) {
			if (twoBeaconsTimeout && info->start)
				dlr_chk_supervisor(info);
			state->new_state = DLR_ACTIVE_FAULT_STATE;
		} else
			state->new_state = DLR_FAULT_STATE;
	}
	if (linkDown) {
		disableNeighChkTimers(info);
		state->new_state = DLR_ACTIVE_FAULT_STATE;
	}
	if (linkLoss || linkStatus) {
#ifdef DBG_DLR_STATE
		dbg_dlr(info, "active loss");
#endif
		twoBeaconsRcvd = 0;
		disableSignOnTimer(info);
		if (DLR_ACTIVE_SUPERVISOR == info->node)
			state->new_state = DLR_ACTIVE_FAULT_STATE;
		else
			state->new_state = DLR_FAULT_STATE;
	}
	if (newSupervisor) {
		twoBeaconsRcvd = 0;
#ifdef DBG_DLR_BEACON
		dbg_bcn += 4;
#endif
		disableSignOnTimer(info);
		state->new_state = DLR_BACKUP_STATE;
	}
	if (!newSupervisor && newValue) {
		state->new_state = DLR_RESTART_STATE;

		/* Ignore own beacons until they are changed. */
		info->start = 0;
	}
	if (DLR_ACTIVE_FAULT_STATE == state->new_state)
		attrib->fault_cnt++;
	if (state->new_state) {
		if (info->skip_beacon)
			acceptBeacons(info);
		info->beacon_info[0].timeout =
		info->beacon_info[1].timeout = 0;
	}

	if (!state->new_state && DLR_ACTIVE_SUPERVISOR == info->node &&
	    memcmp(info->attrib.active_super_addr.addr, info->src_addr,
	    ETH_ALEN)) {
		printk(KERN_INFO "still active normal\n");
		state->new_state = DLR_BACKUP_STATE;
	}
}  /* dlr_active_normal_next */

static void dlr_backup_init(struct ksz_dlr_info *info, struct dlr_state *state)
{
#ifdef DBG_DLR_STATE
	dbg_dlr(info, "backup");
#endif

	info->node = DLR_SUPERVISOR;
	info->attrib.participants_cnt = 0;

	disableSupervisor(info);
	enableBothPorts(info);
	state->new_state = DLR_FAULT_STATE;

	/* Delay resetting so that node knows it is becoming backup. */
	newSupervisor = 0;
}  /* dlr_backup_init */

static void dlr_backup_next(struct ksz_dlr_info *info, struct dlr_state *state)
{
}

static void dlr_prepare_init(struct ksz_dlr_info *info,
	struct dlr_state *state)
{
#ifdef DBG_DLR_STATE
	dbg_dlr(info, "prepare");
#endif
	wait_for_timeout(info->beacon_timeout);
	info->wait_done = 1;
}  /* dlr_prepare_init */

static void dlr_prepare_next(struct ksz_dlr_info *info,
	struct dlr_state *state)
{
	if (info->wait_done) {
		info->wait_done = 0;
		state->new_state = DLR_ACTIVE_STATE;
	}
	if (newSupervisor)
		state->new_state = DLR_BACKUP_STATE;
}  /* dlr_prepare_init */

static void dlr_restart_init(struct ksz_dlr_info *info,
	struct dlr_state *state)
{
#ifdef DBG_DLR_STATE
	dbg_dlr(info,"restart");
#endif
#ifdef DBG_DLR_BEACON
	dbg_bcn += 5;
#endif

	/* Disable timeout notification. */
	info->beacon_timeout_ports = 7;
	info->wait_done = 0;
	info->node = DLR_SUPERVISOR;

	disableSupervisor(info);
	disableAnnounce(info);
	dlr_clear(info);

	/* Reset to ring fault state. */
	dlr_set_state(info);
	wait_for_timeout(info->beacon_timeout * 2);
	info->wait_done = 1;
}  /* dlr_restart_init */

static void dlr_restart_next(struct ksz_dlr_info *info,
	struct dlr_state *state)
{
	if (info->wait_done) {
		info->wait_done = 0;
		updateValues(info);
		info->beacon_info[0].timer =
		info->beacon_info[1].timer = 1;
		state->new_state = DLR_ACTIVE_STATE;
	}
	if (oneBeaconRcvd || twoBeaconsRcvd) {
		dbg_msg("may never get here\n");
		enableBothPorts(info);

		/* Reset timeout notification. */
		info->beacon_timeout_ports = 0;
		state->new_state = DLR_FAULT_STATE;
	}
}  /* dlr_restart_next */

static int dlr_proc_state(struct ksz_dlr_info *info, struct dlr_state *state,
	void (*state_init)(struct ksz_dlr_info *info, struct dlr_state *state),
	void (*state_next)(struct ksz_dlr_info *info, struct dlr_state *state))
{
	if (state->new_state) {
		state->new_state = 0;
		state_init(info, state);
		if (1 == state->change)
			return 1;
	}
	state_next(info, state);
	return 0;
}  /* dlr_proc_state */

static void RingSupervisor_state(struct ksz_dlr_info *info)
{
	struct dlr_state state_info;
	struct ksz_dlr_gateway_capable *attrib = &info->attrib;

	state_info.change = 1;
	state_info.delay_ann = 0;
	state_info.new_state = 0;
	dbg_leak = 5;
	do {
		state_info.change--;
		switch (info->state) {
		case DLR_BEGIN:
			dlr_clear(info);
			info->ok_ports = info->member;
			info->beacon_info[0].timer =
			info->beacon_info[1].timer = 1;
			info->LastBcnRcvPort = 0;
			memset(&attrib->last_active[0], 0,
				sizeof(struct ksz_dlr_active_node));
			memset(&attrib->last_active[1], 0,
				sizeof(struct ksz_dlr_active_node));
			attrib->participants_cnt = 0;
			if (info->skip_beacon)
				acceptBeacons(info);
			if (DLR_BEACON_NODE >= info->node)
				state_info.new_state = DLR_IDLE_STATE;
			else
				state_info.new_state = DLR_ACTIVE_STATE;
			state_info.change = 1;
			break;
		case DLR_IDLE_STATE:
			if (dlr_proc_state(info, &state_info,
			    dlr_idle_init, dlr_idle_next))
				goto done;
			break;
		case DLR_FAULT_STATE:
			if (dlr_proc_state(info, &state_info,
			    dlr_fault_init, dlr_fault_next))
				goto done;
			break;
		case DLR_NORMAL_STATE:
			if (dlr_proc_state(info, &state_info,
			    dlr_normal_init, dlr_normal_next))
				goto done;
			break;
		case DLR_ACTIVE_STATE:
			if (dlr_proc_state(info, &state_info,
			    dlr_active_init, dlr_active_next))
				goto done;
			break;
		case DLR_ACTIVE_FAULT_STATE:
			if (dlr_proc_state(info, &state_info,
			    dlr_active_fault_init, dlr_active_fault_next))
				goto done;
			break;
		case DLR_ACTIVE_NORMAL_STATE:
			if (dlr_proc_state(info, &state_info,
			    dlr_active_normal_init, dlr_active_normal_next))
				goto done;
			break;
		case DLR_BACKUP_STATE:
			if (dlr_proc_state(info, &state_info,
			    dlr_backup_init, dlr_backup_next))
				goto done;
			break;
		case DLR_PREPARE_STATE:
			if (dlr_proc_state(info, &state_info,
			    dlr_prepare_init, dlr_prepare_next))
				goto done;
			break;
		case DLR_RESTART_STATE:
			if (dlr_proc_state(info, &state_info,
			    dlr_restart_init, dlr_restart_next))
				goto done;
			break;
		}
		if (info->reset) {
			info->reset = 0;
			if (DLR_NORMAL_STATE == info->state)
				setupDir(info, -1);
			state_info.new_state = 0;
			info->state = DLR_BEGIN;
			state_info.change++;
		}

		/* There is a new state. */
		if (state_info.new_state) {
			info->state = state_info.new_state;
			state_info.change++;
		}
	} while (state_info.change);

done:
	return;
}  /* RingSupervisor_state */

static void AnnounceRingNode_state(struct ksz_dlr_info *info)
{
	struct dlr_state state_info;
	struct ksz_dlr_gateway_capable *attrib = &info->attrib;

	state_info.change = 1;
	state_info.delay_ann = 0;
	state_info.new_state = 0;
	do {
		state_info.change--;
		switch (info->state) {
		case DLR_BEGIN:
			dlr_clear(info);
			info->ok_ports = info->member;
			info->beacon_info[0].timer =
			info->beacon_info[1].timer = 0;
			announceRcvd = 0;
			announcedState = 0;
			memset(&attrib->last_active[0], 0,
				sizeof(struct ksz_dlr_active_node));
			memset(&attrib->last_active[1], 0,
				sizeof(struct ksz_dlr_active_node));
			attrib->participants_cnt = 0;
			if (info->skip_beacon)
				acceptBeacons(info);
			state_info.new_state = DLR_IDLE_STATE;
			state_info.change = 1;
			break;
		case DLR_IDLE_STATE:
			if (dlr_proc_state(info, &state_info,
			    dlr_ann_idle_init, dlr_ann_idle_next))
				goto done;
			break;
		case DLR_FAULT_STATE:
			if (dlr_proc_state(info, &state_info,
			    dlr_ann_fault_init, dlr_ann_fault_next))
				goto done;
			break;
		case DLR_NORMAL_STATE:
			if (dlr_proc_state(info, &state_info,
			    dlr_ann_normal_init, dlr_ann_normal_next))
				goto done;
			break;
		}
		if (info->reset) {
			info->reset = 0;
			if (DLR_NORMAL_STATE == info->state)
				setupDir(info, -1);
			state_info.new_state = 0;
			info->state = DLR_BEGIN;
			state_info.change++;
		}

		/* There is a new state. */
		if (state_info.new_state) {
			info->state = state_info.new_state;
			state_info.change++;
		}
	} while (state_info.change);

done:
	return;
}  /* AnnounceRingNode_state */

static void *check_dlr_frame(u8 *data)
{
	struct vlan_ethhdr *vlan = (struct vlan_ethhdr *) data;

	if (vlan->h_vlan_proto == htons(ETH_P_8021Q)) {
		if (vlan->h_vlan_encapsulated_proto == htons(DLR_TAG_TYPE))
			return vlan + 1;
	}

	/* VLAN tag can be removed by the switch. */
	if (vlan->h_vlan_proto == htons(DLR_TAG_TYPE)) {
		struct ethhdr *eth = (struct ethhdr *) data;

		return eth + 1;
	}
	return NULL;
}  /* check_dlr_frame */

static void dlr_proc_rx(struct ksz_dlr_info *info, struct sk_buff *skb,
	int port)
{
	struct ksz_dlr_rx_frame frame;
	struct ksz_dlr_frame *body;
	int update = false;

	body = check_dlr_frame(skb->data);
	frame.vlan = (struct vlan_ethhdr *) skb->data;
	frame.body = body;
	switch (body->hdr.frame_type) {
	case DLR_SIGN_ON:
		update = handleSignOn(info, &frame, port);
		break;
	case DLR_NEIGH_CHK_REQ:
		update = handleNeighChkReq(info, &frame, port);
		break;
	case DLR_NEIGH_CHK_RESP:
		update = handleNeighChkResp(info, &frame, port);
		break;
	case DLR_LOCATE_FAULT:
		update = handleLocateFault(info, &frame, port);
		break;
	case DLR_FLUSH_TABLES:
		update = handleFlushTables(info, &frame, port);
		break;
	case DLR_BEACON:
		update = handleBeacon(info, &frame, port);
		break;
	case DLR_ANNOUNCE:
		update = handleAnnounce(info, &frame, port);
		break;
	case DLR_LINK_STATUS:
		update = handleLinkStatus(info, &frame, port);
		break;
	case DLR_LEARNING_UPDATE:
		update = handleLearningUpdate(info, &frame, port);
		break;
	}
	if (update)
		info->state_machine(info);
}  /* dlr_proc_rx */

static void dlr_stop(struct ksz_dlr_info *info)
{
	if (DLR_SUPERVISOR == info->node)
		disableAnnounceTimeout(info);

	/* Avoid trying to drop the beacons again. */
	info->beacon_info[0].timeout =
	info->beacon_info[1].timeout = 1;
	info->node = DLR_BEACON_NODE;

	disableSupervisor(info);
	enableBothPorts(info);
	disableAnnounce(info);
	disableSignOnTimer(info);
	info->beacon_info[0].timeout =
	info->beacon_info[1].timeout = 0;
}  /* dlr_stop */

static void dlr_delay_proc(struct work_struct *work)
{
	struct ksz_dlr_info *dlr =
		container_of(work, struct ksz_dlr_info, delay_proc);
	bool empty;
	bool last;
	struct sk_buff *skb;
	bool notify_link_lost = false;

	if (dlr->stop) {
		dlr->stop = false;
		dlr_stop(dlr);
	}
	if (dlr->timeout_beacon) {
		dlr->timeout_beacon = false;
		if (dlr->beacon_timeout_ports) {
			int p;

			for (p = 0; p < 2; p++) {
				if (dlr->beacon_timeout_ports & (1 << p))
					handleBeaconTimeout(dlr, p);
			}
			dlr->beacon_timeout_ports = 0;
		}
	}
	if (dlr->link_change) {
		dlr->link_change = false;
		if (dlr->notifications & DLR_INFO_LINK_LOST)
			notify_link_lost = true;
	}

	last = skb_queue_empty(&dlr->rxq);
	empty = last;
	while (!last) {
		skb = skb_dequeue(&dlr->rxq);
		last = skb_queue_empty(&dlr->rxq);
		if (skb) {
			int port;

			port = skb->cb[0];
			dlr_proc_rx(dlr, skb, port);
			dev_kfree_skb_irq(skb);
		}
	}
	dlr->state_machine(dlr);
	if (dlr->tx_announce) {
		dlr->tx_announce = false;
		dlr_tx_announce(dlr);
	}
	if (dlr->tx_signon) {
		dlr->tx_signon = false;
		dlr_tx_signon(dlr, 0);
	}
	if (dlr->tx_advertise) {
		dlr->tx_advertise = false;
		dlr_tx_advertise(dlr);
	}
	if (dlr->tx_flush_tables) {
		dlr->tx_flush_tables = false;
		dlr_tx_flush_tables(dlr);
	}
	if (dlr->clr_supervisor) {
		dlr->clr_supervisor = false;
		dlr_clr_supervisor(dlr);
	}
	if (notify_link_lost)
		dlr_notify_link_lost(dlr);
}  /* dlr_delay_proc */

static int dlr_rcv(struct ksz_dlr_info *info, struct sk_buff *skb, int port)
{
	struct ksz_dlr_frame *body;
	int dlr_port = port;

	/* Accept only from port 1 or 2. */
	if (port == info->ports[0])
		dlr_port = 0;
	else if (port == info->ports[1])
		dlr_port = 1;
	body = check_dlr_frame(skb->data);
	if (body) {
		struct ksz_dlr_rx_frame frame;
		int accept = true;

		if (dlr_port < 2) {
			frame.vlan = (struct vlan_ethhdr *) skb->data;
			frame.body = body;
			if (DLR_BEACON == body->hdr.frame_type)
				accept = checkBeacon(info, &frame, dlr_port);
		} else
			accept = false;
		if (accept) {

			/* Use control buffer to save port information. */
			skb->cb[0] = (char) dlr_port;
			skb_queue_tail(&info->rxq, skb);
			schedule_work(&info->delay_proc);
		} else
			dev_kfree_skb_irq(skb);
		return 0;
	}
	return 1;
}  /* dlr_rcv */

static void dlr_link_change(struct ksz_dlr_info *info, int link1, int link2)
{
	if (handleLinkChange(info, link1, link2)) {
		info->link_change = true;
		schedule_work(&info->delay_proc);
	}
}  /* dlr_link_change */

static void dlr_timeout(struct ksz_dlr_info *info, int port)
{
	/* Accept only from port 1 or 2. */
	if (port == info->ports[0])
		port = 0;
	else if (port == info->ports[1])
		port = 1;
	if (port > 1)
		return;
	if (!(info->beacon_timeout_ports & (1 << port))) {
		info->beacon_timeout_ports |= (1 << port);
		info->timeout_beacon = true;
		schedule_work(&info->delay_proc);
	}
}  /* dlr_timeout */

static void prep_dlr_addr(struct ksz_dlr_info *dlr, u8 *src)
{
	memcpy(dlr->src_addr, src, ETH_ALEN);
	memcpy(dlr->frame.vlan.h_source, src, ETH_ALEN);
	memcpy(dlr->update_frame.eth.h_source, src, ETH_ALEN);
	if (DLR_ACTIVE_SUPERVISOR == dlr->node)
		memcpy(dlr->attrib.active_super_addr.addr, src, ETH_ALEN);
}  /* prep_dlr_addr */

static void dlr_change_addr(struct ksz_dlr_info *dlr, u8 *addr)
{
	struct ksz_dlr_gateway_capable *attrib = &dlr->attrib;
	struct ksz_sw *sw = dlr->sw_dev;

	/* Do not do anything if device is not ready. */
	if (!dlr->dev || !netif_running(dlr->dev))
		return;
	if (!memcmp(dlr->src_addr, addr, ETH_ALEN))
		return;

	sw->ops->cfg_mac(sw, BRIDGE_ADDR_ENTRY, dlr->src_addr, 0,
		false, false, 0);
	if (sw->eth_cnt > 1) {
		sw->ops->cfg_mac(sw, DEV_0_ADDR_ENTRY, dlr->src_addr, 0,
			false, true, sw->eth_maps[0].vlan);
		sw->ops->cfg_mac(sw, DEV_1_ADDR_ENTRY, dlr->src_addr, 0,
			false, true, sw->eth_maps[1].vlan);
	}
	prep_dlr_addr(dlr, addr);
	memcpy(dlr->signon_frame, &dlr->frame, sizeof(struct vlan_ethhdr) +
		sizeof(struct ksz_dlr_hdr));
	sw->ops->cfg_mac(sw, BRIDGE_ADDR_ENTRY, dlr->src_addr, sw->HOST_MASK,
		false, false, 0);
	if (sw->eth_cnt > 1) {
		sw->ops->cfg_mac(sw, DEV_0_ADDR_ENTRY, dlr->src_addr,
			sw->HOST_MASK, false, true, sw->eth_maps[0].vlan);
		sw->ops->cfg_mac(sw, DEV_1_ADDR_ENTRY, dlr->src_addr,
			sw->HOST_MASK, false, true, sw->eth_maps[1].vlan);
	}
#ifdef CONFIG_HAVE_ACL_HW
	setup_acl_self(dlr, dlr->ports[0]);
	setup_acl_self(dlr, dlr->ports[1]);
#endif
	if (DLR_SUPERVISOR == dlr->node &&
	    dlr->attrib.super_cfg.prec == attrib->active_super_prec) {
		int cmp = memcmp(dlr->src_addr, attrib->active_super_addr.addr,
			ETH_ALEN);

		if (cmp > 0) {
			dlr->new_val = 1;
			schedule_work(&dlr->delay_proc);
		}
	} else if (DLR_ACTIVE_SUPERVISOR == dlr->node) {
		if (dlr->skip_beacon)
			acceptBeacons(dlr);
		dlr->new_val = 1;
		schedule_work(&dlr->delay_proc);
	}
}  /* dlr_change_addr */

static void prep_dlr_mcast(struct net_device *dev)
{
	char addr[MAX_ADDR_LEN];

	memcpy(addr, MAC_ADDR_BEACON, ETH_ALEN);
	dev_mc_add(dev, addr);
	memcpy(addr, MAC_ADDR_SIGNON, ETH_ALEN);
	dev_mc_add(dev, addr);
	memcpy(addr, MAC_ADDR_ANNOUNCE, ETH_ALEN);
	dev_mc_add(dev, addr);
	memcpy(addr, MAC_ADDR_ADVERTISE, ETH_ALEN);
	dev_mc_add(dev, addr);
	memcpy(addr, MAC_ADDR_LEARNING_UPDATE, ETH_ALEN);
	dev_mc_add(dev, addr);
}  /* prep_dlr_mcast */

static void prep_dlr(struct ksz_dlr_info *dlr, struct net_device *dev, u8 *src)
{
	dlr->dev = dev;
	prep_dlr_addr(dlr, src);
	dlr->frame.vlan.h_vlan_TCI = htons((7 << VLAN_PRIO_SHIFT) | dlr->vid);
	memcpy(dlr->signon_frame, &dlr->frame, sizeof(struct vlan_ethhdr) +
		sizeof(struct ksz_dlr_hdr));

	dlr->active_port = 0;
	dlr->seqid = 0;
#if 1
	dlr->seqid = 0xffffffe0;
#endif
	dlr->seqid_beacon = 0;
	dlr->state = DLR_BEGIN;
	do {
		struct ksz_sw *sw = dlr->sw_dev;

		sw->ops->cfg_mac(sw, BRIDGE_ADDR_ENTRY, dlr->src_addr,
			sw->HOST_MASK, false, false, 0);
		if (sw->eth_cnt > 1) {
			sw->ops->cfg_mac(sw, DEV_0_ADDR_ENTRY, dlr->src_addr,
				sw->HOST_MASK, false, true,
				sw->eth_maps[0].vlan);
			sw->ops->cfg_mac(sw, DEV_1_ADDR_ENTRY, dlr->src_addr,
				sw->HOST_MASK, false, true,
				sw->eth_maps[1].vlan);
		}
		dlr->p1_down = sw->port_info[dlr->ports[0]].state !=
			media_connected;
		dlr->p2_down = sw->port_info[dlr->ports[1]].state !=
			media_connected;
		if (DLR_ACTIVE_SUPERVISOR == dlr->node) {
			if (dlr->p1_down)
				dlr_set_addr(&dlr->attrib.last_active[0],
					dlr->ip_addr, dlr->src_addr);
			if (dlr->p2_down)
				dlr_set_addr(&dlr->attrib.last_active[1],
					dlr->ip_addr, dlr->src_addr);
		}
		sw->ops->acquire(sw);
		port_cfg(sw, dlr->ports[0], REG_PORT_LUE_CTRL,
			PORT_SRC_ADDR_FILTER, false);
		port_cfg(sw, dlr->ports[1], REG_PORT_LUE_CTRL,
			PORT_SRC_ADDR_FILTER, false);
		sw->ops->release(sw);
	} while (0);
#ifdef CONFIG_HAVE_ACL_HW
	setup_acl_self(dlr, dlr->ports[0]);
	setup_acl_self(dlr, dlr->ports[1]);
#endif
	setup_vlan_table(dlr, dlr->vid, true);
	schedule_work(&dlr->delay_proc);
}  /* prep_dlr */

static void announce_monitor(struct work_struct *work)
{
	struct delayed_work *dwork = to_delayed_work(work);
	struct ksz_dlr_info *dlr =
		container_of(dwork, struct ksz_dlr_info, announce_tx);

	dlr->clr_supervisor = true;

	/* No longer being active supervisor after this scheduling. */
	if (DLR_ACTIVE_SUPERVISOR != dlr->node) {
#if 0
if (dlr->ann_delay)
dbg_msg(" ! %s %d %d\n", __func__, dlr->ann_delay, dlr->signon_delay);
#endif
		dlr->ann_delay = 0;
		dlr->signon_delay = 0;
		goto done;
	}

	if (dlr->ann_delay) {
		u32 microsec;
		unsigned long diff = jiffies - dlr->ann_jiffies;

		microsec = dlr->beacon_timeout * 2;
		if (diff >= 2)
			diff = diff * 1000 * (1000 / HZ);
		else
			diff = 0;
		if (diff < microsec) {
			microsec -= diff;
			wait_for_timeout(microsec);
		}
		dlr->ann_delay = 0;
		dlr->ann_jiffies = 0;
	}

	/* No longer being active supervisor after the wait. */
	if (DLR_ACTIVE_SUPERVISOR != dlr->node) {
		dlr->signon_delay = 0;
		goto done;
	}

	dlr->tx_announce = true;
	if (dlr->signon_delay) {
#ifdef DBG_DLR_ANN_SIGNON
		dbg_msg("delay signon: %lx\n", jiffies);
#endif
		dlr->tx_signon = true;
		dlr->signon_delay = 0;
	}
	schedule_delayed_work(&dlr->announce_tx, 100);

done:
	schedule_work(&dlr->delay_proc);
}  /* announce_monitor */

static void announce_timeout_monitor(unsigned long ptr)
{
	struct ksz_dlr_info *info = (struct ksz_dlr_info *) ptr;

dbg_msg("ann timeout\n");
	info->ann_timeout = 1;
	if (DLR_ANNOUNCE_NODE == info->node ||
	    DLR_SUPERVISOR == info->node)
		schedule_work(&info->delay_proc);
	ksz_update_timer(&info->announce_timeout_timer_info);
}  /* announce_timeout_monitor */

static void neigh_chk_proc(struct work_struct *work)
{
	int p;
	int checking = 0;
	int lost = false;
	struct ksz_dlr_info *dlr =
		container_of(work, struct ksz_dlr_info, neigh_chk_proc);

	/* Neighbor_Check_Request timeout. */
	for (p = 0; p < 2; p++) {

		/* This port has sent a Neighbor_Check_Request frame. */
		if (dlr->port_chk[p]) {
			++checking;
			++dlr->port_chk[p];
			if (dlr->port_chk[p] > 3) {
				if (p)
					dlr->p2_lost = 1;
				else
					dlr->p1_lost = 1;
				lost = true;
				--checking;
			} else
				dlr_tx_chk_req(dlr, p);
		}
	}
	if (lost) {
		if (DLR_ACTIVE_SUPERVISOR == dlr->node) {
			struct ksz_dlr_node_info *node;

			if (dlr->p1_lost)
				dlr->ok_ports &= ~(1 << dlr->ports[0]);
			if (dlr->p2_lost)
				dlr->ok_ports &= ~(1 << dlr->ports[1]);
			node = find_dlr_node(dlr, dlr->src_addr);
			if (node) {
				if (dlr->p1_down)
					node->p1_down = 1;
				if (dlr->p2_down)
					node->p2_down = 1;
				if (dlr->p1_lost)
					node->p1_lost = 1;
				if (dlr->p2_lost)
					node->p2_lost = 1;
			}
			if (dlr->p1_lost)
				dlr_set_addr(&dlr->attrib.last_active[0],
					dlr->ip_addr, dlr->src_addr);
			if (dlr->p2_lost)
				dlr_set_addr(&dlr->attrib.last_active[1],
					dlr->ip_addr, dlr->src_addr);
#if 1
			if (dlr->notifications & DLR_INFO_CFG_CHANGE)
				dlr_notify_cfg_change(dlr, 2);
#endif
			dlr_notify_link_lost(dlr);
		} else
			dlr_tx_status(dlr, 1);
	}
}  /* neigh_chk_proc */

static void neigh_chk_monitor(unsigned long ptr)
{
	struct ksz_dlr_info *dlr = (struct ksz_dlr_info *) ptr;

	schedule_work(&dlr->neigh_chk_proc);
	ksz_update_timer(&dlr->neigh_chk_timer_info);
	dlr->neigh_chk = !!dlr->neigh_chk_timer_info.max;
}  /* neigh_chk_monitor */

static void signon_monitor(unsigned long ptr)
{
	struct ksz_dlr_info *info = (struct ksz_dlr_info *) ptr;

#ifdef DBG_DLR_ANN_SIGNON
	dbg_msg("%s\n", __func__);
#endif
	if (DLR_ACTIVE_SUPERVISOR == info->node) {
		info->tx_signon = true;
		schedule_work(&info->delay_proc);
	} else
		info->signon_timer_info.max = 1;
	ksz_update_timer(&info->signon_timer_info);
}  /* signon_monitor */

static void dlr_reset_attrib(struct ksz_dlr_info *dlr)
{
#ifdef CONFIG_HAVE_DLR_HW
	struct ksz_sw *sw = dlr->sw_dev;
#endif

	memset(&dlr->attrib, 0, sizeof(struct ksz_dlr_gateway_capable));
	switch (dlr->node) {
	case DLR_ANNOUNCE_NODE:
		dlr->attrib.cap = DLR_CAP_ANNOUNCE_BASED;
		dlr->attrib.super_status = DLR_STAT_RING_NODE;
		break;
	case DLR_BEACON_NODE:
		dlr->attrib.cap = DLR_CAP_BEACON_BASED;

#ifdef CONFIG_HAVE_DLR_HW
		if (sw->features & REDUNDANCY_SUPPORT)
			dlr->attrib.cap |= DLR_CAP_SUPERVISOR_CAPABLE;
#endif
		dlr->attrib.super_status = DLR_STAT_RING_NODE;
		dlr->attrib.super_cfg.beacon_interval = 400;
		dlr->attrib.super_cfg.beacon_timeout = 1960;
		dlr->attrib.super_cfg.beacon_interval *= 1;
		dlr->attrib.super_cfg.beacon_timeout *= 1;
		break;
	default:

#ifdef CONFIG_HAVE_DLR_HW
		if (!(sw->features & REDUNDANCY_SUPPORT))
			break;
#endif
		dlr->attrib.cap = DLR_CAP_BEACON_BASED;
		dlr->attrib.cap |= DLR_CAP_SUPERVISOR_CAPABLE;
		dlr->attrib.super_status = DLR_STAT_ACTIVE_SUPERVISOR;
		dlr->attrib.super_cfg.enable = true;
		dlr->attrib.super_cfg.beacon_interval = 400;
		dlr->attrib.super_cfg.beacon_timeout = 1960;
		dlr->attrib.super_cfg.beacon_interval *= 1;
		dlr->attrib.super_cfg.beacon_timeout *= 1;
	}
}  /* dlr_reset_attrib */

static void setup_dlr(struct ksz_dlr_info *dlr)
{
	struct ksz_dlr_frame *frame = &dlr->frame.body;

	dlr_reset_attrib(dlr);

	dlr->ip_addr = 0;
	dlr->vid = 0;
	dlr->precedence = 0;
	dlr->beacon_interval = 400;
	dlr->beacon_timeout = 1960;
	dlr->beacon_interval *= 1;
	dlr->beacon_timeout *= 1;

	dlr->frame.vlan.h_vlan_proto = htons(ETH_P_8021Q);
	dlr->frame.vlan.h_vlan_encapsulated_proto = htons(DLR_TAG_TYPE);
	frame->hdr.ring_subtype = DLR_RING_SUBTYPE;
	frame->hdr.ring_protocol_version = 1;
	frame->hdr.ip_addr = dlr->ip_addr;
	dlr->tx_frame = (u8 *) &dlr->frame;

	memcpy(dlr->update_frame.eth.h_dest, MAC_ADDR_LEARNING_UPDATE,
		ETH_ALEN);
	dlr->update_frame.eth.h_proto = htons(DLR_TAG_TYPE);
	dlr->update_frame.hdr.ring_subtype = DLR_RING_SUBTYPE;
	dlr->update_frame.hdr.ring_protocol_version = 1;
	dlr->update_frame.hdr.frame_type = DLR_LEARNING_UPDATE;
	dlr->update_frame.hdr.src_port = DLR_PORT_NONE;
	memset(dlr->update_frame.reserved, 0, 34);

	dlr->p1_set = dlr->p2_set = 1;

	dlr->port = 0;
	dlr->tx_port = dlr->port;
	dlr->rx_port = (dlr->tx_port + 1) & 1;

	ksz_init_timer(&dlr->announce_timeout_timer_info, 1200 * HZ / 1000,
		announce_timeout_monitor, dlr);
	ksz_init_timer(&dlr->neigh_chk_timer_info, 100 * HZ / 1000,
		neigh_chk_monitor, dlr);
	ksz_init_timer(&dlr->signon_timer_info, 60000 * HZ / 1000,
		signon_monitor, dlr);

}  /* setup_dlr */

static int dlr_get_attrib(struct ksz_dlr_info *dlr, int subcmd, int size,
	int *req_size, size_t *len, u8 *data, int *output)
{
	struct ksz_dlr_node_info *cur;
	struct ksz_dlr_active_node *node;
	int i;
	struct ksz_dlr_gateway_capable *attr = &dlr->attrib;
	u8 svc = (u8)(subcmd >> CIP_SVC_S);
	u8 class = (u8)(subcmd >> CIP_CLASS_S);
	u8 code = (u8)(subcmd >> CIP_ATTR_S);
	u8 id = (u8) subcmd;

	*len = 0;
	*output = 0;
	if (class != CLASS_DLR_OBJECT)
		return DEV_IOC_INVALID_CMD;
	if (svc != SVC_GET_ATTRIBUTES_ALL &&
	    svc != SVC_GET_ATTRIBUTE_SINGLE &&
	    svc != SVC_GET_MEMBER)
		return DEV_IOC_INVALID_CMD;
	if (CIP_INSTANCE_ATTRIBUTES == code) {
		if (SVC_GET_ATTRIBUTES_ALL == svc) {
			*len = sizeof(struct ksz_dlr_super_capable_2);
			if (attr->cap & DLR_CAP_GATEWAY_CAPABLE)
				*len = sizeof(struct ksz_dlr_gateway_capable);
			memcpy(data, attr, *len);
		} else if (SVC_GET_ATTRIBUTE_SINGLE == svc) {
			union dlr_data *attrib = (union dlr_data *) data;

			switch (id) {
			case DLR_GET_NETWORK_TOPOLOGY:
				*len = 1;
				attrib->byte = attr->net_topology;
				break;
			case DLR_GET_NETWORK_STATUS:
				*len = 1;
				attrib->byte = attr->net_status;
#if 1
if (attrib->byte == DLR_NET_RING_FAULT && getting_last_active &&
((!attr->last_active[0].addr[4] && !attr->last_active[0].addr[5]) ||
(!attr->last_active[1].addr[4] && !attr->last_active[1].addr[5])))
attrib->byte = DLR_NET_NORMAL;
#endif
				break;
			case DLR_GET_RING_SUPERVISOR_STATUS:
				*len = 1;
				attrib->byte = attr->super_status;
				break;
			case DLR_SET_RING_SUPERVISOR_CONFIG:
				*len = sizeof(struct ksz_dlr_super_cfg);
				memcpy(&attrib->super_cfg, &attr->super_cfg,
					*len);
				break;
			case DLR_SET_RING_FAULT_COUNT:
				*len = 2;
				attrib->word = attr->fault_cnt;
				break;
			case DLR_GET_LAST_ACTIVE_NODE_ON_PORT_1:
dbg_msg("+");
				*len = sizeof(struct ksz_dlr_active_node);
				memcpy(&attrib->active,	&attr->last_active[0],
					*len);
				break;
			case DLR_GET_LAST_ACTIVE_NODE_ON_PORT_2:
				*len = sizeof(struct ksz_dlr_active_node);
				memcpy(&attrib->active,	&attr->last_active[1],
					*len);
				break;
			case DLR_GET_RING_PARTICIPANTS_COUNT:
				*len = 2;
				attrib->word = attr->participants_cnt;
				break;
			case DLR_GET_ACTIVE_SUPERVISOR_ADDRESS:
				*len = sizeof(struct ksz_dlr_active_node);
				memcpy(&attrib->active,
					&attr->active_super_addr, *len);
				break;
			case DLR_GET_ACTIVE_SUPERVISOR_PRECEDENCE:
				*len = 1;
				attrib->byte = attr->active_super_prec;
				break;
			case DLR_GET_CAPABILITY_FLAGS:
				*len = 4;
				attrib->dword = attr->cap;
				break;
			case DLR_SET_REDUNDANT_GATEWAY_CONFIG:
				if (!(attr->cap & DLR_CAP_GATEWAY_CAPABLE))
					break;
				*len = sizeof(struct ksz_dlr_gateway_cfg);
				memcpy(&attrib->gateway_cfg, &attr->gateway_cfg,
					*len);
				break;
			case DLR_GET_REDUNDANT_GATEWAY_STATUS:
				if (!(attr->cap & DLR_CAP_GATEWAY_CAPABLE))
					break;
				*len = 1;
				attrib->byte = attr->gateway_status;
				break;
			case DLR_GET_ACTIVE_GATEWAY_ADDRESS:
				if (!(attr->cap & DLR_CAP_GATEWAY_CAPABLE))
					break;
				*len = sizeof(struct ksz_dlr_active_node);
				memcpy(&attrib->active,
					&attr->active_gateway_addr, *len);
				break;
			case DLR_GET_ACTIVE_GATEWAY_PRECEDENCE:
				if (!(attr->cap & DLR_CAP_GATEWAY_CAPABLE))
					break;
				*len = 1;
				attrib->byte = attr->active_gateway_prec;
				break;
			case DLR_GET_RING_PARTICIPANTS_LIST:
				*len = sizeof(struct ksz_dlr_active_node);
				if (attr->super_status !=
				    DLR_STAT_ACTIVE_SUPERVISOR) {
					*output = STATUS_OBJECT_STATE_CONFLICT;
					break;
				}
				*len *= attr->participants_cnt;
				if (size < *len) {
					*output = STATUS_REPLY_DATA_TOO_LARGE;
					break;
				}
				node = (struct ksz_dlr_active_node *) data;
				for (i = 0; i < attr->participants_cnt; i++) {
					cur = &dlr->nodes[i];
					node->ip_addr = cur->signon.ip_addr;
					memcpy(&node->addr, cur->signon.addr,
						ETH_ALEN);
					node++;
				}
				break;
			}
		} else if (SVC_GET_MEMBER == svc) {
			switch (id) {
			case DLR_GET_RING_PARTICIPANTS_LIST:
				*len = sizeof(struct ksz_dlr_active_node);
				if (attr->super_status !=
				    DLR_STAT_ACTIVE_SUPERVISOR) {
					*output = STATUS_OBJECT_STATE_CONFLICT;
					break;
				}
				node = (struct ksz_dlr_active_node *) data;
				i = 0;
				cur = &dlr->nodes[i];
				node->ip_addr = cur->signon.ip_addr;
				memcpy(&node->addr, cur->signon.addr,
					ETH_ALEN);
				break;
			}
		}
	} else if (CIP_CLASS_ATTRIBUTES == code) {
		union dlr_data *attrib = (union dlr_data *) data;

		if (DLR_GET_REVISION == id) {
			*len = 2;
			attrib->word = DLR_REVISION;
		}
	}
	if (!*len)
		return DEV_IOC_INVALID_CMD;
	if (size < *len) {
		*req_size = *len + SIZEOF_ksz_request;
		return DEV_IOC_INVALID_LEN;
	}
	return DEV_IOC_OK;
}  /* dlr_get_attrib */

static int dlr_change_cfg(struct ksz_dlr_info *dlr,
	struct ksz_dlr_super_cfg *cfg)
{
	struct ksz_dlr_gateway_capable *attrib = &dlr->attrib;
	struct ksz_dlr_super_cfg *super = &attrib->super_cfg;

	if (cfg->beacon_interval < 100 || cfg->beacon_interval > 100000 ||
	    cfg->beacon_timeout < 1000 || cfg->beacon_timeout > 2000000)
		return STATUS_INVALID_ATTRIB_VALUE;
	if (cfg->enable && !(dlr->attrib.cap & DLR_CAP_SUPERVISOR_CAPABLE))
		return STATUS_INVALID_ATTRIB_VALUE;
	if (cfg->enable != super->enable) {
		if (super->enable) {
			dlr->stop = true;
		} else
			dlr->node = DLR_SUPERVISOR;
		super->enable = cfg->enable;
		if (super->enable) {
			super->prec = cfg->prec;
			super->beacon_interval = cfg->beacon_interval;
			super->beacon_timeout = cfg->beacon_timeout;
			super->vid = cfg->vid;
			dlr->precedence = super->prec;
			dlr->beacon_interval = super->beacon_interval;
			dlr->beacon_timeout = super->beacon_timeout;
			dlr->vid = super->vid;
		}
		dlr->reset = true;
		schedule_work(&dlr->delay_proc);
	} else if (super->enable) {
		if (cfg->prec != super->prec) {
			super->prec = cfg->prec;
			dlr->new_val = 1;
		}
		if (DLR_ACTIVE_SUPERVISOR == dlr->node || dlr->new_val) {
			if (cfg->beacon_interval != super->beacon_interval) {
				super->beacon_interval = cfg->beacon_interval;
				dlr->new_val = 1;
			}
			if (cfg->beacon_timeout != super->beacon_timeout) {
				super->beacon_timeout = cfg->beacon_timeout;
				dlr->new_val = 1;
			}
			if (cfg->vid != super->vid) {
				super->vid = cfg->vid;
				dlr->new_val = 1;
			}
		}
		if (dlr->new_val)
			schedule_work(&dlr->delay_proc);
	}
	return 0;
}  /* dlr_change_cfg */

static int dlr_set_attrib(struct ksz_dlr_info *dlr, int subcmd, int size,
	int *req_size, u8 *data, int *output)
{
	struct ksz_dlr_gateway_capable *attr = &dlr->attrib;
	int len = 0;
	u8 svc = (u8)(subcmd >> CIP_SVC_S);
	u8 class = (u8)(subcmd >> CIP_CLASS_S);
	u8 code = (u8)(subcmd >> CIP_ATTR_S);
	u8 id = (u8) subcmd;
	union dlr_data *attrib = (union dlr_data *) data;

	*output = 0;
	if (class != CLASS_DLR_OBJECT)
		return DEV_IOC_INVALID_CMD;
	switch (svc) {
	case SVC_SET_ATTRIBUTE_SINGLE:
		if (CIP_INSTANCE_ATTRIBUTES != code)
			return DEV_IOC_INVALID_CMD;
		switch (id) {
		case DLR_SET_RING_SUPERVISOR_CONFIG:
			len = sizeof(struct ksz_dlr_super_cfg);
			break;
		case DLR_SET_RING_FAULT_COUNT:
			len = 2;
			break;
		case DLR_SET_REDUNDANT_GATEWAY_CONFIG:
			if (!(attr->cap & DLR_CAP_GATEWAY_CAPABLE))
				break;
			len = sizeof(struct ksz_dlr_gateway_cfg);
			break;
		case DLR_SET_IP_ADDRESS:
			len = sizeof(struct ksz_dlr_active_node);
			break;
		}
		if (!len)
			return DEV_IOC_INVALID_CMD;
		if (size < len) {
			*req_size = len + SIZEOF_ksz_request;
			return DEV_IOC_INVALID_LEN;
		}
		switch (id) {
		case DLR_SET_RING_SUPERVISOR_CONFIG:
			*output = dlr_change_cfg(dlr, &attrib->super_cfg);
			break;
		case DLR_SET_RING_FAULT_COUNT:
			if (attrib->word) {
				*output = STATUS_INVALID_ATTRIB_VALUE;
				break;
			}
			attr->fault_cnt = attrib->word;
			break;
		case DLR_SET_REDUNDANT_GATEWAY_CONFIG:
			if (memcmp(&attr->gateway_cfg, &attrib->gateway_cfg,
			    len)) {
				memcpy(&attr->gateway_cfg, &attrib->gateway_cfg,
					len);
			}
			break;
		case DLR_SET_IP_ADDRESS:
		{
			struct ksz_dlr_frame *frame = &dlr->frame.body;

			dlr->ip_addr = attrib->active.ip_addr;
			frame->hdr.ip_addr = dlr->ip_addr;
			break;
		}
		}
		break;
	case SVC_DLR_VERIFY_FAULT_LOCATION:
	{
		struct ksz_dlr_node_info *node;
		int i;

		if (attr->super_status !=
		    DLR_STAT_ACTIVE_SUPERVISOR ||
		    dlr->state != DLR_ACTIVE_FAULT_STATE) {
			*output = STATUS_OBJECT_STATE_CONFLICT;
			memset(&attr->last_active[0], 0,
				sizeof(struct ksz_dlr_active_node));
			memset(&attr->last_active[1], 0,
				sizeof(struct ksz_dlr_active_node));
			break;
		}
		for (i = 1; i < attr->participants_cnt; i++) {
			node = &dlr->nodes[i];
			node->p1_down = 0;
			node->p1_lost = 0;
			node->p2_down = 0;
			node->p2_lost = 0;
		}
		dlr_tx_locate_fault(dlr);
		break;
	}
	case SVC_DLR_CLEAR_RAPID_FAULTS:
		break;
	case SVC_DLR_RESTART_SIGN_ON:
		if (attr->super_status !=
		    DLR_STAT_ACTIVE_SUPERVISOR ||
		    dlr->state != DLR_ACTIVE_NORMAL_STATE) {
			*output = STATUS_OBJECT_STATE_CONFLICT;
			break;
		}

		/* SignOn timer not started. */
		if (!dlr->signon_start) {
			dlr->signon_start = 1;
			startSignOn(dlr, false);
		}
		break;
	case SVC_DLR_CLEAR_GATEWAY_PARTIAL_FAULT:
		break;
	default:
		return DEV_IOC_INVALID_CMD;
	}
	return DEV_IOC_OK;
}  /* dlr_set_attrib */

static int dlr_dev_req(struct ksz_dlr_info *dlr, char *arg, void *info)
{
	struct ksz_request *req = (struct ksz_request *) arg;
	int len;
	int maincmd;
	int req_size;
	int subcmd;
	int output;
	size_t param_size;
	u8 data[PARAM_DATA_SIZE];
	struct ksz_resp_msg *msg = (struct ksz_resp_msg *) data;
	int err = 0;
	int result = 0;

	get_user_data(&req_size, &req->size, info);
	get_user_data(&maincmd, &req->cmd, info);
	get_user_data(&subcmd, &req->subcmd, info);
	get_user_data(&output, &req->output, info);
	len = req_size - SIZEOF_ksz_request;

	maincmd &= 0xffff;
	switch (maincmd) {
	case DEV_CMD_INFO:
		switch (subcmd) {
		case DEV_INFO_INIT:
			req_size = SIZEOF_ksz_request + 4;
			if (len >= 4) {
				data[0] = 'M';
				data[1] = 'i';
				data[2] = 'c';
				data[3] = 'r';
				data[4] = 0;
				data[5] = dlr->member;
				err = write_user_data(data, req->param.data,
					6, info);
				if (err)
					goto dev_ioctl_done;
				dlr->dev_info = info;
			} else
				result = DEV_IOC_INVALID_LEN;
			break;
		case DEV_INFO_EXIT:

		/* fall through */
		case DEV_INFO_QUIT:

			/* Not called through char device. */
			if (!info)
				break;
			msg->module = DEV_MOD_DLR;
			msg->cmd = DEV_INFO_QUIT;
			msg->resp.data[0] = 0;
			sw_setup_msg(info, msg, 8, NULL, NULL);
			dlr->notifications = 0;
			dlr->dev_info = NULL;
			break;
		case DEV_INFO_NOTIFY:
			if (len >= 4) {
				uint *notify = (uint *) data;

				_chk_ioctl_size(len, 4, 0, &req_size, &result,
					&req->param, data, info);
				dlr->notifications = *notify;
			}
			break;
		default:
			result = DEV_IOC_INVALID_CMD;
			break;
		}
		break;
	case DEV_CMD_PUT:
		if (_chk_ioctl_size(len, len, 0, &req_size, &result,
		    &req->param, data, info))
			goto dev_ioctl_resp;
		result = dlr_set_attrib(dlr, subcmd, len, &req_size, data,
			&output);
		if (result)
			goto dev_ioctl_resp;
		put_user_data(&output, &req->output, info);
		break;
	case DEV_CMD_GET:
		result = dlr_get_attrib(dlr, subcmd, len, &req_size,
			&param_size, data, &output);
		if (result)
			goto dev_ioctl_resp;
		err = write_user_data(data, req->param.data, param_size, info);
		if (err)
			goto dev_ioctl_done;
		req_size = param_size + SIZEOF_ksz_request;
		put_user_data(&output, &req->output, info);
		break;
	default:
		result = DEV_IOC_INVALID_CMD;
		break;
	}

dev_ioctl_resp:
	put_user_data(&req_size, &req->size, info);
	put_user_data(&result, &req->result, info);

	/* Return ERESTARTSYS so that the system call is called again. */
	if (result < 0)
		err = result;

dev_ioctl_done:
	return err;
}  /* dlr_dev_req */

#define _dlr_dev_req(a, b)		dlr_dev_req(a, b, NULL)

static void set_dlr_req(void *ptr, int cmd,
	u8 svc, u8 class, u8 code, u8 id, void *dlr, size_t dlr_size)
{
	struct ksz_request *req = ptr;

	req->size = SIZEOF_ksz_request;
	req->size += dlr_size;
	req->cmd = cmd;
	req->subcmd = (svc << CIP_SVC_S) | (class << CIP_CLASS_S) |
		(code << CIP_ATTR_S) | id;
	req->output = 0;
	if (dlr)
		memcpy(&req->param, dlr, dlr_size);
}  /* set_dlr_req */

static int get_dlr_revision(void *fd,
	u16 *rev)
{
	struct ksz_request_actual req;
	int rc;
	struct ksz_dlr_info *dlr = fd;

	set_dlr_req(&req, DEV_CMD_GET, SVC_GET_ATTRIBUTE_SINGLE,
		CLASS_DLR_OBJECT, CIP_CLASS_ATTRIBUTES, DLR_GET_REVISION,
		NULL, sizeof(u16));
	rc = _dlr_dev_req(dlr, (char *) &req);
	if (!rc)
		rc = req.result;
	if (!rc) {
		union dlr_data *data = (union dlr_data *) &req.param;

		*rev = data->word;
	}
	return rc;
}  /* get_dlr_revision */

static int get_dlr_all(void *fd,
	struct ksz_dlr_gateway_capable *capable)
{
	struct ksz_request_actual *req;
	int rc;
	struct ksz_dlr_info *dlr = fd;

	req = kzalloc(sizeof(struct ksz_request_actual), GFP_KERNEL);
	if (!req)
		return -1;
	set_dlr_req(req, DEV_CMD_GET, SVC_GET_ATTRIBUTES_ALL,
		CLASS_DLR_OBJECT, CIP_INSTANCE_ATTRIBUTES, 0,
		NULL, sizeof(struct ksz_dlr_gateway_capable));
	rc = _dlr_dev_req(dlr, (char *) req);
	if (!rc)
		rc = req->result;
	if (!rc) {
		memcpy(capable, &req->param, req->size - SIZEOF_ksz_request);
	}
	kfree(req);
	return rc;
}  /* get_dlr_all */

static int get_dlr_topology(void *fd,
	u8 *topology)
{
	struct ksz_request_actual req;
	int rc;
	struct ksz_dlr_info *dlr = fd;

	set_dlr_req(&req, DEV_CMD_GET, SVC_GET_ATTRIBUTE_SINGLE,
		CLASS_DLR_OBJECT, CIP_INSTANCE_ATTRIBUTES,
		DLR_GET_NETWORK_TOPOLOGY,
		NULL, sizeof(u8));
	rc = _dlr_dev_req(dlr, (char *) &req);
	if (!rc)
		rc = req.result;
	if (!rc) {
		union dlr_data *data = (union dlr_data *) &req.param;

		*topology = data->byte;
	}
	return rc;
}  /* get_dlr_topology */

static int get_dlr_network(void *fd,
	u8 *network)
{
	struct ksz_request_actual req;
	int rc;
	struct ksz_dlr_info *dlr = fd;

	set_dlr_req(&req, DEV_CMD_GET, SVC_GET_ATTRIBUTE_SINGLE,
		CLASS_DLR_OBJECT, CIP_INSTANCE_ATTRIBUTES,
		DLR_GET_NETWORK_STATUS,
		NULL, sizeof(u8));
	rc = _dlr_dev_req(dlr, (char *) &req);
	if (!rc)
		rc = req.result;
	if (!rc) {
		union dlr_data *data = (union dlr_data *) &req.param;

		*network = data->byte;
	}
	return rc;
}  /* get_dlr_network */

static int get_dlr_super_status(void *fd,
	u8 *status)
{
	struct ksz_request_actual req;
	int rc;
	struct ksz_dlr_info *dlr = fd;

	set_dlr_req(&req, DEV_CMD_GET, SVC_GET_ATTRIBUTE_SINGLE,
		CLASS_DLR_OBJECT, CIP_INSTANCE_ATTRIBUTES,
		DLR_GET_RING_SUPERVISOR_STATUS,
		NULL, sizeof(u8));
	rc = _dlr_dev_req(dlr, (char *) &req);
	if (!rc)
		rc = req.result;
	if (!rc) {
		union dlr_data *data = (union dlr_data *) &req.param;

		*status = data->byte;
	}
	return rc;
}  /* get_dlr_super_status */

static int get_dlr_super_cfg(void *fd,
	struct ksz_dlr_super_cfg *cfg)
{
	struct ksz_request_actual req;
	int rc;
	struct ksz_dlr_info *dlr = fd;

	set_dlr_req(&req, DEV_CMD_GET, SVC_GET_ATTRIBUTE_SINGLE,
		CLASS_DLR_OBJECT, CIP_INSTANCE_ATTRIBUTES,
		DLR_SET_RING_SUPERVISOR_CONFIG,
		NULL, sizeof(struct ksz_dlr_super_cfg));
	rc = _dlr_dev_req(dlr, (char *) &req);
	if (!rc)
		rc = req.result;
	if (!rc) {
		memcpy(cfg, &req.param, req.size - SIZEOF_ksz_request);
	}
	return rc;
}  /* get_dlr_super_cfg */

static int set_dlr_super_cfg(void *fd,
	struct ksz_dlr_super_cfg *cfg, u8 *err)
{
	struct ksz_request_actual req;
	int rc;
	struct ksz_dlr_info *dlr = fd;

	set_dlr_req(&req, DEV_CMD_PUT, SVC_SET_ATTRIBUTE_SINGLE,
		CLASS_DLR_OBJECT, CIP_INSTANCE_ATTRIBUTES,
		DLR_SET_RING_SUPERVISOR_CONFIG,
		cfg, sizeof(struct ksz_dlr_super_cfg));
	rc = _dlr_dev_req(dlr, (char *) &req);
	if (!rc)
		rc = req.result;
	if (!rc) {
		*err = (u8) req.output;
	}
	return rc;
}  /* set_dlr_super_cfg */

static int get_dlr_ring_fault_cnt(void *fd,
	u16 *cnt)
{
	struct ksz_request_actual req;
	int rc;
	struct ksz_dlr_info *dlr = fd;

	set_dlr_req(&req, DEV_CMD_GET, SVC_GET_ATTRIBUTE_SINGLE,
		CLASS_DLR_OBJECT, CIP_INSTANCE_ATTRIBUTES,
		DLR_SET_RING_FAULT_COUNT,
		NULL, sizeof(u16));
	rc = _dlr_dev_req(dlr, (char *) &req);
	if (!rc)
		rc = req.result;
	if (!rc) {
		union dlr_data *data = (union dlr_data *) &req.param;

		*cnt = data->word;
	}
	return rc;
}  /* get_dlr_ring_fault_cnt */

static int set_dlr_ring_fault_cnt(void *fd,
	u16 cnt, u8 *err)
{
	struct ksz_request_actual req;
	int rc;
	struct ksz_dlr_info *dlr = fd;

	set_dlr_req(&req, DEV_CMD_PUT, SVC_SET_ATTRIBUTE_SINGLE,
		CLASS_DLR_OBJECT, CIP_INSTANCE_ATTRIBUTES,
		DLR_SET_RING_FAULT_COUNT,
		&cnt, sizeof(u16));
	rc = _dlr_dev_req(dlr, (char *) &req);
	if (!rc)
		rc = req.result;
	if (!rc) {
		*err = (u8) req.output;
	}
	return rc;
}  /* set_dlr_ring_fault_cnt */

static int get_dlr_active_node(void *fd,
	u8 port, struct ksz_dlr_active_node *node)
{
	struct ksz_request_actual req;
	int rc;
	struct ksz_dlr_info *dlr = fd;
	u8 id;

	if (1 == port)
		id = DLR_GET_LAST_ACTIVE_NODE_ON_PORT_2;
	else
		id = DLR_GET_LAST_ACTIVE_NODE_ON_PORT_1;
	set_dlr_req(&req, DEV_CMD_GET, SVC_GET_ATTRIBUTE_SINGLE,
		CLASS_DLR_OBJECT, CIP_INSTANCE_ATTRIBUTES,
		id,
		NULL, sizeof(struct ksz_dlr_active_node));
	rc = _dlr_dev_req(dlr, (char *) &req);
	if (!rc)
		rc = req.result;
	if (!rc) {
		memcpy(node, &req.param, req.size - SIZEOF_ksz_request);
	}
	return rc;
}  /* get_dlr_active_node */

static int get_dlr_ring_part_cnt(void *fd,
	u16 *cnt)
{
	struct ksz_request_actual req;
	int rc;
	struct ksz_dlr_info *dlr = fd;

	set_dlr_req(&req, DEV_CMD_GET, SVC_GET_ATTRIBUTE_SINGLE,
		CLASS_DLR_OBJECT, CIP_INSTANCE_ATTRIBUTES,
		DLR_GET_RING_PARTICIPANTS_COUNT,
		NULL, sizeof(u16));
	rc = _dlr_dev_req(dlr, (char *) &req);
	if (!rc)
		rc = req.result;
	if (!rc) {
		union dlr_data *data = (union dlr_data *) &req.param;

		*cnt = data->word;
	}
	return rc;
}  /* get_dlr_ring_part_cnt */

static int get_dlr_ring_part_list(void *fd,
	struct ksz_dlr_active_node *node, u16 *size, u8 *err)
{
	struct ksz_request_actual req;
	int rc;
	struct ksz_dlr_info *dlr = fd;

	set_dlr_req(&req, DEV_CMD_GET, SVC_GET_ATTRIBUTE_SINGLE,
		CLASS_DLR_OBJECT, CIP_INSTANCE_ATTRIBUTES,
		DLR_GET_RING_PARTICIPANTS_LIST,
		NULL, *size);
	rc = _dlr_dev_req(dlr, (char *) &req);
	if (!rc)
		rc = req.result;
	if (!rc) {
		*err = (u8) req.output;
		*size = req.size - SIZEOF_ksz_request;
		memcpy(node, &req.param, *size);
	}
	return rc;
}  /* get_dlr_ring_part_list */

static int get_dlr_active_super_addr(void *fd,
	struct ksz_dlr_active_node *node)
{
	struct ksz_request_actual req;
	int rc;
	struct ksz_dlr_info *dlr = fd;

	set_dlr_req(&req, DEV_CMD_GET, SVC_GET_ATTRIBUTE_SINGLE,
		CLASS_DLR_OBJECT, CIP_INSTANCE_ATTRIBUTES,
		DLR_GET_ACTIVE_SUPERVISOR_ADDRESS,
		NULL, sizeof(struct ksz_dlr_active_node));
	rc = _dlr_dev_req(dlr, (char *) &req);
	if (!rc)
		rc = req.result;
	if (!rc) {
		memcpy(node, &req.param, req.size - SIZEOF_ksz_request);
	}
	return rc;
}  /* get_dlr_active_super_addr */

static int get_dlr_active_super_prec(void *fd,
	u8 *prec)
{
	struct ksz_request_actual req;
	int rc;
	struct ksz_dlr_info *dlr = fd;

	set_dlr_req(&req, DEV_CMD_GET, SVC_GET_ATTRIBUTE_SINGLE,
		CLASS_DLR_OBJECT, CIP_INSTANCE_ATTRIBUTES,
		DLR_GET_ACTIVE_SUPERVISOR_PRECEDENCE,
		NULL, sizeof(u8));
	rc = _dlr_dev_req(dlr, (char *) &req);
	if (!rc)
		rc = req.result;
	if (!rc) {
		union dlr_data *data = (union dlr_data *) &req.param;

		*prec = data->byte;
	}
	return rc;
}  /* get_dlr_active_super_prec */

static int get_dlr_cap(void *fd,
	u32 *flags)
{
	struct ksz_request_actual req;
	int rc;
	struct ksz_dlr_info *dlr = fd;

	set_dlr_req(&req, DEV_CMD_GET, SVC_GET_ATTRIBUTE_SINGLE,
		CLASS_DLR_OBJECT, CIP_INSTANCE_ATTRIBUTES,
		DLR_GET_CAPABILITY_FLAGS,
		NULL, sizeof(u32));
	rc = _dlr_dev_req(dlr, (char *) &req);
	if (!rc)
		rc = req.result;
	if (!rc) {
		union dlr_data *data = (union dlr_data *) &req.param;

		*flags = data->dword;
	}
	return rc;
}  /* get_dlr_cap */

static int set_dlr_verify_fault(void *fd,
	u8 *err)
{
	struct ksz_request_actual req;
	int rc;
	struct ksz_dlr_info *dlr = fd;

	set_dlr_req(&req, DEV_CMD_PUT, SVC_DLR_VERIFY_FAULT_LOCATION,
		CLASS_DLR_OBJECT, 0, 0,
		NULL, 0);
	rc = _dlr_dev_req(dlr, (char *) &req);
	if (!rc)
		rc = req.result;
	if (!rc) {
		*err = (u8) req.output;
	}
	return rc;
}  /* set_dlr_verify_fault */

static int set_dlr_clear_rapid_fault(void *fd,
	u8 *err)
{
	struct ksz_request_actual req;
	int rc;
	struct ksz_dlr_info *dlr = fd;

	set_dlr_req(&req, DEV_CMD_PUT, SVC_DLR_CLEAR_RAPID_FAULTS,
		CLASS_DLR_OBJECT, 0, 0,
		NULL, 0);
	rc = _dlr_dev_req(dlr, (char *) &req);
	if (!rc)
		rc = req.result;
	if (!rc) {
		*err = (u8) req.output;
	}
	return rc;
}  /* set_dlr_clear_rapid_fault */

static int set_dlr_restart_sign_on(void *fd,
	u8 *err)
{
	struct ksz_request_actual req;
	int rc;
	struct ksz_dlr_info *dlr = fd;

	set_dlr_req(&req, DEV_CMD_PUT, SVC_DLR_RESTART_SIGN_ON,
		CLASS_DLR_OBJECT, 0, 0,
		NULL, 0);
	rc = _dlr_dev_req(dlr, (char *) &req);
	if (!rc)
		rc = req.result;
	if (!rc) {
		*err = (u8) req.output;
	}
	return rc;
}  /* set_dlr_restart_sign_on */

static int set_dlr_clear_gateway_fault(void *fd,
	u8 *err)
{
	struct ksz_request_actual req;
	int rc;
	struct ksz_dlr_info *dlr = fd;

	set_dlr_req(&req, DEV_CMD_PUT, SVC_DLR_CLEAR_GATEWAY_PARTIAL_FAULT,
		CLASS_DLR_OBJECT, 0, 0,
		NULL, 0);
	rc = _dlr_dev_req(dlr, (char *) &req);
	if (!rc)
		rc = req.result;
	if (!rc) {
		*err = (u8) req.output;
	}
	return rc;
}  /* set_dlr_clear_gateway_fault */

static void test_monitor(unsigned long ptr)
{
	struct ksz_dlr_info *info = (struct ksz_dlr_info *) ptr;

	if (DLR_SUPERVISOR <= info->node) {
		u8 prec;

		if (1 == info->precedence)
			prec = 9;
		else if (9 == info->precedence)
			prec = 1;
		else
			prec = 0;
		if (prec) {
			int rc;
			u8 err;
			struct ksz_dlr_super_cfg super;

			memcpy(&super, &info->attrib.super_cfg, sizeof(super));
			super.prec = prec;
			rc = set_dlr_super_cfg(info, &super, &err);
		}
	}
	ksz_update_timer(&info->test_timer_info);
}  /* test_monitor */

enum {
	PROC_GET_DLR_INFO,
	PROC_SET_DLR_NODE,
	PROC_SET_DLR_PRECEDENCE,
	PROC_SET_DLR_INTERVAL,
	PROC_SET_DLR_TIMEOUT,
	PROC_SET_DLR_VID,
	PROC_SET_DLR_CFG,
	PROC_SET_DLR_STATE,
	PROC_SET_DLR_PORT,
	PROC_SET_DLR_TEST,
	PROC_SET_DLR_NEIGH_CHK_REQ,
	PROC_SET_DLR_NEIGH_CHK_RESP,
	PROC_SET_DLR_LINK_BREAK,
	PROC_SET_DLR_LEARNING_UPDATE,
	PROC_SET_DLR_LOCATE_FAULT,
	PROC_SET_DLR_SIGN_ON,
	PROC_SET_DLR_CLEAR_FAULT,
	PROC_SET_DLR_CLEAR_GATEWAY_FAULT,

	PROC_GET_DLR_ALL,
	PROC_GET_DLR_REVISION,
	PROC_GET_DLR_NETWORK_TOPOLOGY,
	PROC_GET_DLR_NETWORK_STATUS,
	PROC_GET_DLR_RING_SUPERVISOR_STATUS,
	PROC_SET_DLR_RING_SUPERVISOR_CONFIG,
	PROC_SET_DLR_RING_FAULT_COUNT,
	PROC_GET_DLR_LAST_ACTIVE_NODE_1,
	PROC_GET_DLR_LAST_ACTIVE_NODE_2,
	PROC_GET_DLR_RING_PARTICIPANTS_COUNT,
	PROC_GET_DLR_RING_PARTICIPANTS_LIST,
	PROC_GET_DLR_ACTIVE_SUPERVISOR_ADDRESS,
	PROC_GET_DLR_ACTIVE_SUPERVISOR_PRECEDENCE,
	PROC_GET_DLR_CAPABILITIES,
	PROC_SET_DLR_PORT_1,
	PROC_SET_DLR_PORT_2,
};

static ssize_t display_faults(struct ksz_dlr_info *dlr, char *buf, ssize_t len)
{
	int i;
	struct ksz_dlr_node_info *node;
	struct ksz_dlr_node *signon;

	for (i = 0; i < dlr->attrib.participants_cnt; i++) {
		node = &dlr->nodes[i];
		signon = &node->signon;
		if (!node->p1_down && !node->p2_down &&
		    !node->p1_lost && !node->p2_lost)
			continue;
		len += sprintf(buf + len, 
			"%02x:%02x:%02x:%02x:%02x:%02x  %3u.%3u.%3u.%3u  ",
			signon->addr[0], signon->addr[1], signon->addr[2],
			signon->addr[3], signon->addr[4], signon->addr[5],
			(u8) signon->ip_addr,
			(u8)(signon->ip_addr >> 8),
			(u8)(signon->ip_addr >> 24),
			(u8)(signon->ip_addr >> 16));
		len += sprintf(buf + len, "%u:%u %u:%u\n",
			node->p1_down, node->p2_down,
			node->p1_lost, node->p2_lost);
		if (len >= 2048 - 80) {
			len += sprintf(buf + len, "...\n");
			break;
		}
	}
	return len;
}  /* display_faults */

static ssize_t display_nodes(struct ksz_dlr_info *dlr, char *buf, ssize_t len)
{
	int i;
	struct ksz_dlr_node_info *node;
	struct ksz_dlr_node *signon;

	for (i = 0; i < dlr->attrib.participants_cnt; i++) {
		node = &dlr->nodes[i];
		signon = &node->signon;
		len += sprintf(buf + len,
			"%02x:%02x:%02x:%02x:%02x:%02x  %3u.%3u.%3u.%3u  ",
			signon->addr[0], signon->addr[1], signon->addr[2],
			signon->addr[3], signon->addr[4], signon->addr[5],
			(u8) signon->ip_addr,
			(u8)(signon->ip_addr >> 8),
			(u8)(signon->ip_addr >> 16),
			(u8)(signon->ip_addr >> 24));
		len += sprintf(buf + len, "%u:%u %u:%u\n",
			node->p1_down, node->p2_down,
			node->p1_lost, node->p2_lost);
		if (len >= 2048 - 80) {
			len += sprintf(buf + len, "...\n");
			break;
		}
	}
	return len;
}  /* display_nodes */

static ssize_t show_dlr_err(ssize_t len, char *buf, u8 err)
{
	if (buf)
		len += sprintf(buf + len, "!0x%02x\n", err);
	else
		printk(KERN_INFO "!0x%02x\n", err);
	return len;
}  /* show_dlr_err */

static ssize_t show_dlr_attrib(ssize_t len, char *buf, u8 err, char *format,
	u32 data)
{
	if (err)
		len = show_dlr_err(len, buf, err);
	else
		len += sprintf(buf + len, format, data);
	return len;
}  /* show_dlr_attrib */

static ssize_t show_dlr_attrib_super(ssize_t len, char *buf, u8 err,
	struct ksz_dlr_super_cfg *cfg)
{
	if (err)
		len = show_dlr_err(len, buf, err);
	else
		len += sprintf(buf + len, "E:%u  P:%u  I:%u  T:%u  V:%u\n",
			cfg->enable,
			cfg->prec,
			cfg->beacon_interval,
			cfg->beacon_timeout,
			cfg->vid);
	return len;
}  /* show_dlr_attrib_super */

static ssize_t show_dlr_attrib_node(ssize_t len, char *buf, u8 err,
	struct ksz_dlr_active_node *node)
{
	if (err)
		len = show_dlr_err(len, buf, err);
	else
		len += sprintf(buf + len,
			"%02x:%02x:%02x:%02x:%02x:%02x  %3u.%3u.%3u.%3u\n",
			node->addr[0],
			node->addr[1],
			node->addr[2],
			node->addr[3],
			node->addr[4],
			node->addr[5],
			(u8) node->ip_addr,
			(u8)(node->ip_addr >> 8),
			(u8)(node->ip_addr >> 16),
			(u8)(node->ip_addr >> 24));
	return len;
}  /* show_dlr_attrib_node */

static ssize_t show_dlr_attrib_all(ssize_t len, char *buf, u8 err,
	struct ksz_dlr_gateway_capable *capable)
{
	if (err)
		len = show_dlr_err(len, buf, err);
	else {
		len = show_dlr_attrib(len, buf, 0,
			"top:%u  ", capable->net_topology);
		len = show_dlr_attrib(len, buf, 0,
			"net:%u  ", capable->net_status);
		len = show_dlr_attrib(len, buf, 0,
			"sup:%u  ", capable->super_status);
		len = show_dlr_attrib(len, buf, 0,
			"fault:%u\n", capable->fault_cnt);
		len = show_dlr_attrib_super(len, buf, 0,
			&capable->super_cfg);
		len = show_dlr_attrib_node(len, buf, 0,
			&capable->last_active[0]);
		len = show_dlr_attrib_node(len, buf, 0,
			&capable->last_active[1]);
		len = show_dlr_attrib_node(len, buf, 0,
			&capable->active_super_addr);
		len = show_dlr_attrib(len, buf, 0,
			"cnt:%u  ", capable->participants_cnt);
		len = show_dlr_attrib(len, buf, 0,
			"prec:%u  ", capable->active_super_prec);
		len = show_dlr_attrib(len, buf, 0,
			"cap:%08x\n", capable->cap);
	}
	return len;
}  /* show_dlr_attrib_all */

static ssize_t sysfs_dlr_read(struct ksz_dlr_info *dlr, int proc_num,
	ssize_t len, char *buf)
{
	struct ksz_dlr_active_node node;
	struct ksz_dlr_super_cfg super;
	int rc;
	u32 dword;
	u16 word;
	u8 byte;
	u8 err = 0;

	switch (proc_num) {
	case PROC_GET_DLR_INFO:
		break;
	case PROC_SET_DLR_NODE:
		len += sprintf(buf + len, "%u\n", dlr->node);
		break;
	case PROC_SET_DLR_PRECEDENCE:
		len += sprintf(buf + len, "%u\n", dlr->precedence);
		break;
	case PROC_SET_DLR_INTERVAL:
		len += sprintf(buf + len, "%u\n", dlr->beacon_interval);
		break;
	case PROC_SET_DLR_TIMEOUT:
		len += sprintf(buf + len, "%u\n", dlr->beacon_timeout);
		break;
	case PROC_SET_DLR_VID:
		len += sprintf(buf + len, "0x%03x\n", dlr->vid);
		break;
	case PROC_SET_DLR_STATE:
		len += sprintf(buf + len, "%u\n", dlr->ring_state);
		break;
	case PROC_SET_DLR_PORT:
		len += sprintf(buf + len, "%u\n", dlr->port);
		break;
	case PROC_SET_DLR_TEST:
		len += sprintf(buf + len, "%u\n",
			(dlr->overrides & DLR_TEST) ? 1 : 0);
		break;
	case PROC_SET_DLR_LOCATE_FAULT:
		if (DLR_ACTIVE_SUPERVISOR == dlr->node)
			len = display_faults(dlr, buf, len);
		break;
	case PROC_SET_DLR_SIGN_ON:
		if (DLR_ACTIVE_SUPERVISOR == dlr->node)
			len = display_nodes(dlr, buf, len);
		else
			len += sprintf(buf + len, "%u\n", dlr->ignore_req);
		break;
	case PROC_SET_DLR_NEIGH_CHK_REQ:
		break;
	case PROC_SET_DLR_NEIGH_CHK_RESP:
		len += sprintf(buf + len, "%u\n", dlr->ignore_req);
		break;
	case PROC_SET_DLR_LINK_BREAK:
		len += sprintf(buf + len, "0x%x\n", dlr->link_break);
		break;
	case PROC_GET_DLR_REVISION:
		rc = get_dlr_revision(dlr, &word);
		if (!rc)
			len = show_dlr_attrib(len, buf, err, "%u\n", word);
		break;
	case PROC_GET_DLR_ALL:
	{
		struct ksz_dlr_gateway_capable *capable;

		capable = kzalloc(sizeof(struct ksz_dlr_gateway_capable),
			GFP_KERNEL);
		if (!capable)
			break;
		rc = get_dlr_all(dlr, capable);
		if (!rc)
			len = show_dlr_attrib_all(len, buf, err, capable);
		kfree(capable);
		break;
	}
	case PROC_GET_DLR_NETWORK_TOPOLOGY:
		rc = get_dlr_topology(dlr, &byte);
		if (!rc)
			len = show_dlr_attrib(len, buf, err, "%u\n", byte);
		break;
	case PROC_GET_DLR_NETWORK_STATUS:
		rc = get_dlr_network(dlr, &byte);
		if (!rc)
			len = show_dlr_attrib(len, buf, err, "%u\n", byte);
		break;
	case PROC_GET_DLR_RING_SUPERVISOR_STATUS:
		rc = get_dlr_super_status(dlr, &byte);
		if (!rc)
			len = show_dlr_attrib(len, buf, err, "%u\n", byte);
		break;
	case PROC_SET_DLR_RING_SUPERVISOR_CONFIG:
		rc = get_dlr_super_cfg(dlr, &super);
		if (!rc)
			len = show_dlr_attrib_super(len, buf, err, &super);
		break;
	case PROC_SET_DLR_RING_FAULT_COUNT:
		rc = get_dlr_ring_fault_cnt(dlr, &word);
		if (!rc)
			len = show_dlr_attrib(len, buf, err, "%u\n", word);
		break;
	case PROC_GET_DLR_LAST_ACTIVE_NODE_1:
		rc = get_dlr_active_node(dlr, 0, &node);
		if (!rc)
			len = show_dlr_attrib_node(len, buf, err, &node);
		break;
	case PROC_GET_DLR_LAST_ACTIVE_NODE_2:
		rc = get_dlr_active_node(dlr, 1, &node);
		if (!rc)
			len = show_dlr_attrib_node(len, buf, err, &node);
		break;
	case PROC_GET_DLR_RING_PARTICIPANTS_COUNT:
		rc = get_dlr_ring_part_cnt(dlr, &word);
		if (!rc)
			len = show_dlr_attrib(len, buf, err, "%u\n", word);
		break;
	case PROC_GET_DLR_RING_PARTICIPANTS_LIST:
	{
		struct ksz_dlr_active_node *nodes;

		rc = get_dlr_ring_part_cnt(dlr, &word);
		if (rc || !word)
			break;

		word *= sizeof(struct ksz_dlr_active_node);
		nodes = kzalloc(word, GFP_KERNEL);
		if (!nodes)
			break;

		rc = get_dlr_ring_part_list(dlr, nodes, &word, &err);
		if (!rc) {
			int i;

			if (err) {
				len = show_dlr_err(len, buf, err);
				break;
			}
			word /= sizeof(struct ksz_dlr_active_node);
			for (i = 0; i < word; i++)
				len = show_dlr_attrib_node(len, buf, 0,
					&nodes[i]);
		}
		kfree(nodes);
		break;
	}
	case PROC_GET_DLR_ACTIVE_SUPERVISOR_ADDRESS:
		rc = get_dlr_active_super_addr(dlr, &node);
		if (!rc)
			len = show_dlr_attrib_node(len, buf, err, &node);
		break;
	case PROC_GET_DLR_ACTIVE_SUPERVISOR_PRECEDENCE:
		rc = get_dlr_active_super_prec(dlr, &byte);
		if (!rc)
			len = show_dlr_attrib(len, buf, err, "%u\n", byte);
		break;
	case PROC_GET_DLR_CAPABILITIES:
		rc = get_dlr_cap(dlr, &dword);
		if (!rc)
			len = show_dlr_attrib(len, buf, err, "%08x\n", dword);
		break;
	case PROC_SET_DLR_PORT_1:
		len += sprintf(buf + len, "%u\n", dlr->ports[0]);
		break;
	case PROC_SET_DLR_PORT_2:
		len += sprintf(buf + len, "%u\n", dlr->ports[1]);
		break;
	}
	return len;
}  /* sysfs_dlr_read */

static void sysfs_dlr_write(struct ksz_dlr_info *info, int proc_num, int num,
	const char *buf)
{
	int rc;
	u8 err;
	struct ksz_dlr_super_cfg super;
	struct ksz_dlr_gateway_capable *attrib = &info->attrib;
	struct ksz_sw *sw = info->sw_dev;
	int node = DLR_ACTIVE_SUPERVISOR;
	u32 member = 0;

	if (sw->overrides & HAVE_MORE_THAN_2_PORTS)
		member = info->member | sw->HOST_MASK;
	switch (proc_num) {
	case PROC_SET_DLR_NODE:
#ifdef CONFIG_HAVE_DLR_HW
		/* Cannot be a supervisor without beacon generation. */
		if (!(sw->features & REDUNDANCY_SUPPORT))
			node = DLR_BEACON_NODE;
#endif
		if (!(DLR_ANNOUNCE_NODE <= num && num <= node))
			break;
		if (num == info->node)
			break;
		disableAnnounceTimeout(info);
		if (DLR_SUPERVISOR <= info->node) {
			int prev_node = info->node;

			info->node = DLR_BEACON_NODE;
			disableSupervisor(info);
			if (DLR_ACTIVE_SUPERVISOR == prev_node) {
				enableBothPorts(info);
				disableAnnounce(info);
				disableSignOnTimer(info);
			}
		} else if (DLR_NORMAL_STATE == info->state) {
			setupDir(info, -1);
		}
		if (info->skip_beacon)
			acceptBeacons(info);
		if (DLR_ANNOUNCE_NODE == info->node)
			sw->ops->cfg_mac(sw, DLR_BEACON_ENTRY,
				MAC_ADDR_BEACON, member, false, false, 0);
		if (num == info->node)
			break;
		info->node = (u8) num;
		dlr_reset_attrib(info);
		info->attrib.super_cfg.beacon_interval = info->beacon_interval;
		info->attrib.super_cfg.beacon_timeout = info->beacon_timeout;
#ifdef DBG_DLR_BEACON
		dbg_bcn = 4;
#endif
		do {
			struct ksz_sw *sw = info->sw_dev;

			if (DLR_ANNOUNCE_NODE == info->node) {
#ifdef CONFIG_HAVE_ACL_HW
				disable_acl_beacon_timeout(info,
					info->ports[0]);
				disable_acl_beacon_timeout(info,
					info->ports[1]);
#endif
				sw->ops->cfg_mac(sw, DLR_BEACON_ENTRY,
					MAC_ADDR_BEACON, info->member,
					false, false, 0);
				info->state_machine = AnnounceRingNode_state;
			} else
				info->state_machine = RingSupervisor_state;
			info->reset = true;
			schedule_work(&info->delay_proc);
		} while (0);
		break;
	case PROC_SET_DLR_PRECEDENCE:
		/* Value can only be set through supervisor. */
		if (info->node < DLR_SUPERVISOR)
			break;
		memcpy(&super, &info->attrib.super_cfg, sizeof(super));
		super.prec = (u8) num;
		rc = set_dlr_super_cfg(info, &super, &err);
		if (!rc && err)
			show_dlr_err(0, NULL, err);
		break;
	case PROC_SET_DLR_INTERVAL:
		/* Value can only be set through active supervisor. */
		if (DLR_ACTIVE_SUPERVISOR != info->node)
			break;
		if (num < 200) {
			printk("too small\n");
			break;
		} else if (num * 4 > info->beacon_timeout) {
			printk("too large\n");
			break;
		}
		memcpy(&super, &info->attrib.super_cfg, sizeof(super));
		super.beacon_interval = num;
		rc = set_dlr_super_cfg(info, &super, &err);
		if (!rc && err)
			show_dlr_err(0, NULL, err);
		break;
	case PROC_SET_DLR_TIMEOUT:
		/* Value can only be set through active supervisor. */
		if (DLR_ACTIVE_SUPERVISOR != info->node)
			break;
		if (num < info->beacon_interval * 4) {
			printk("too small\n");
			break;

#ifdef CONFIG_HAVE_ACL_HW
		} else if (num >= ACL_CNT_M * 1000) {
			printk("too large\n");
			break;
#endif
		}
		memcpy(&super, &info->attrib.super_cfg, sizeof(super));
		super.beacon_timeout = num;
		rc = set_dlr_super_cfg(info, &super, &err);
		if (!rc && err)
			show_dlr_err(0, NULL, err);
		break;
	case PROC_SET_DLR_VID:
		/* Value can only be set through active supervisor. */
		if (DLR_ACTIVE_SUPERVISOR != info->node)
			break;
		if (num >= 0x400)
			break;
		memcpy(&super, &info->attrib.super_cfg, sizeof(super));
		super.vid = (u16) num;
		rc = set_dlr_super_cfg(info, &super, &err);
		if (!rc && err)
			show_dlr_err(0, NULL, err);
		break;
	case PROC_SET_DLR_CFG:
	{
		int enable;
		int prec;
		int interval;
		int timeout;
		int vid;

		sscanf(buf, "%u %u %u %u %u",
			&enable, &prec, &interval, &timeout, &vid);
		if (interval < 200) {
			printk("too small\n");
			break;
		} else if (interval * 4 > timeout) {
			printk("too large\n");
			break;
		}
		if (timeout < interval * 4) {
			printk("too small\n");
			break;

#ifdef CONFIG_HAVE_ACL_HW
		} else if (timeout >= ACL_CNT_M * 1000) {
			printk("too large\n");
			break;
#endif
		}
		super.enable = (u8) enable;
		super.prec = (u8) prec;
		super.beacon_interval = interval;
		super.beacon_timeout = timeout;
		super.vid = (u16) vid;
		rc = set_dlr_super_cfg(info, &super, &err);
		if (!rc && err)
			show_dlr_err(0, NULL, err);
		break;
	}
	case PROC_SET_DLR_STATE:
		if (1 <= num && num <= 2) {
			info->ring_state = (u8) num;
			dlr_set_state(info);
		}
		break;
	case PROC_SET_DLR_PORT:
		if (0 <= num && num <= 1) {
			info->port = (u8) num;
			info->tx_port = (u8) num;
			info->rx_port = (info->tx_port + 1) & 1;
		}
		break;
	case PROC_SET_DLR_TEST:
		if (num & 1)
			info->overrides |= DLR_TEST;
		else
			info->overrides &= ~DLR_TEST;
		if (num & 2)
			info->overrides |= DLR_TEST_SEQ;
		else
			info->overrides &= ~DLR_TEST_SEQ;
		if (num & 0x80)
			ksz_start_timer(&info->test_timer_info,
				info->test_timer_info.period);
		else
			ksz_stop_timer(&info->test_timer_info);
		break;
	case PROC_SET_DLR_LEARNING_UPDATE:
		dlr_tx_learning_update(info);
		break;
	case PROC_SET_DLR_LOCATE_FAULT:
		rc = set_dlr_verify_fault(info, &err);
		if (!rc && err)
			show_dlr_err(0, NULL, err);
		break;
	case PROC_SET_DLR_SIGN_ON:
		if (DLR_ACTIVE_SUPERVISOR == info->node) {
			info->signon_space = num;
		} else {
			info->ignore_req = (u8) num;
			info->req_cnt[0] = info->req_cnt[1] = 0;
			if (info->overrides & DLR_TEST)
				break;
		}
		rc = set_dlr_restart_sign_on(info, &err);
		if (!rc && err)
			show_dlr_err(0, NULL, err);
		break;
	case PROC_SET_DLR_NEIGH_CHK_REQ:
		if (num & 3) {
			if (!info->neigh_chk) {
				info->neigh_chk = 1;
				ksz_start_timer(&info->neigh_chk_timer_info,
					info->neigh_chk_timer_info.period);
			}
			info->neigh_chk_timer_info.max = 3;
		}
		if (num & 1) {
			info->port_chk[0] = 1;
			dlr_tx_chk_req(info, 0);
		}
		if (num & 2) {
			info->port_chk[1] = 1;
			dlr_tx_chk_req(info, 1);
		}
		break;
	case PROC_SET_DLR_NEIGH_CHK_RESP:
		info->ignore_req = (u8) num;
		info->req_cnt[0] = info->req_cnt[1] = 0;
		break;
	case PROC_SET_DLR_LINK_BREAK:
		info->link_break = num;
		if (info->link_break & 1)
			info->p1_down = 1;
		else
			info->p1_down = 0;
		if (info->link_break & 2)
			info->p2_down = 1;
		else
			info->p2_down = 0;
		if (info->link_break & 4)
			info->p1_lost = 1;
		else
			info->p1_lost = 0;
		if (info->link_break & 8)
			info->p2_lost = 1;
		else
			info->p2_lost = 0;
		if (info->node != DLR_ACTIVE_SUPERVISOR)
			dlr_tx_status(info, 0);
		else if (attrib->participants_cnt > 0) {
			struct ksz_dlr_node_info *node;

			node = &info->nodes[0];
			if (attrib->participants_cnt > 1) {
				struct ksz_dlr_node_info *prev;
				struct ksz_dlr_node_info *next;

				prev = &info->nodes[attrib->participants_cnt -
					1];
				next = &info->nodes[1];
				if (info->p1_lost)
					prev->p2_lost = 1;
				if (info->p2_lost)
					next->p1_lost = 1;
			}
			node->p1_down = info->p1_down;
			node->p2_down = info->p2_down;
			node->p1_lost = info->p1_lost;
			node->p2_lost = info->p2_lost;
		}
		break;
	case PROC_SET_DLR_RING_SUPERVISOR_CONFIG:
	{
		struct ksz_dlr_super_cfg super;

		/* Value can only be set through supervisor. */
		if (!(info->attrib.cap & DLR_CAP_SUPERVISOR_CAPABLE))
			break;
		memcpy(&super, &info->attrib.super_cfg, sizeof(super));
		if (num) {
			super.enable = true;
			if (!super.beacon_interval)
				super.beacon_interval = 400;
			if (!super.beacon_timeout)
				super.beacon_timeout = 1960;
		} else
			super.enable = false;
		rc = set_dlr_super_cfg(info, &super, &err);
		if (!rc && err)
			show_dlr_err(0, NULL, err);
		break;
	}
	case PROC_SET_DLR_RING_FAULT_COUNT:
		rc = set_dlr_ring_fault_cnt(info, num, &err);
		if (!rc && err)
			show_dlr_err(0, NULL, err);
		break;
	case PROC_SET_DLR_CLEAR_FAULT:
		rc = set_dlr_clear_rapid_fault(info, &err);
		if (!rc && err)
			show_dlr_err(0, NULL, err);
		break;
	case PROC_SET_DLR_CLEAR_GATEWAY_FAULT:
		rc = set_dlr_clear_gateway_fault(info, &err);
		if (!rc && err)
			show_dlr_err(0, NULL, err);
		break;
	case PROC_SET_DLR_PORT_1:
#ifdef CONFIG_HAVE_DLR_HW
		if (netif_running(info->dev))
			printk(KERN_ALERT "stop %s first", info->dev->name);
		if (0 <= num && num < sw->port_cnt &&
		    num != sw->HOST_PORT && num != info->ports[1])
			info->ports[0] = (u8) num;
		info->member = (1 << info->ports[0]) | (1 << info->ports[1]);
#endif
		break;
	case PROC_SET_DLR_PORT_2:
#ifdef CONFIG_HAVE_DLR_HW
		if (netif_running(info->dev))
			printk(KERN_ALERT "stop %s first", info->dev->name);
		if (0 <= num && num < sw->port_cnt &&
		    num != sw->HOST_PORT && num != info->ports[0])
			info->ports[1] = (u8) num;
		info->member = (1 << info->ports[0]) | (1 << info->ports[1]);
#endif
		break;
	}
}  /* sysfs_dlr_write */

static struct dlr_ops dlr_ops = {
	.change_addr		= dlr_change_addr,
	.link_change		= dlr_link_change,
	.timeout		= dlr_timeout,

	.dev_req		= dlr_dev_req,

	.sysfs_read		= sysfs_dlr_read,
	.sysfs_write		= sysfs_dlr_write,
};

static void ksz_dlr_exit(struct ksz_dlr_info *dlr)
{
	ksz_stop_timer(&dlr->announce_timeout_timer_info);
	ksz_stop_timer(&dlr->neigh_chk_timer_info);
	ksz_stop_timer(&dlr->signon_timer_info);
	ksz_stop_timer(&dlr->test_timer_info);
	cancel_delayed_work_sync(&dlr->announce_tx);
}  /* ksz_dlr_exit */

static void ksz_dlr_init(struct ksz_dlr_info *dlr, struct ksz_sw *sw)
{
	dlr->ports[0] = 0;
	dlr->ports[1] = 1;
	dlr->member = (1 << dlr->ports[0]) | (1 << dlr->ports[1]);
	dlr->ok_ports = dlr->member;
	dlr->sw_dev = sw;
	dlr->node = DLR_BEACON_NODE;
	dlr->state_machine = RingSupervisor_state;
	setup_dlr(dlr);
	INIT_DELAYED_WORK(&dlr->announce_tx, announce_monitor);
	INIT_WORK(&dlr->delay_proc, dlr_delay_proc);
	INIT_WORK(&dlr->neigh_chk_proc, neigh_chk_proc);
	skb_queue_head_init(&dlr->rxq);
	dlr->ops = &dlr_ops;
	ksz_init_timer(&dlr->test_timer_info, 1000 * HZ / 1000,
		test_monitor, dlr);
}  /* ksz_dlr_init */

