/**
 * Micrel DLR code
 *
 * Copyright (c) 2015-2016 Microchip Technology Inc.
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


#if 1
#define DROP_BEACON_1	1
#else
#define DROP_BEACON_1	0
#endif
#if 1
#define DROP_BEACON_0

#endif
#if 0
#define DLR_NO_ACL_TIMEOUT
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

#ifdef CONFIG_HAVE_ACL_HW

#define DLR_TIMEOUT_ACL_ENTRY		14

static void setup_acl_beacon(struct ksz_dlr_info *info, int port)
{
	struct ksz_sw *sw = info->sw_dev;
	struct ksz_port_cfg *cfg = &sw->info->port_cfg[port];
	struct ksz_acl_table *acl;
	int i = DLR_TIMEOUT_ACL_ENTRY - 2;
	int first_rule = i;
	int ruleset = (3 << i);

	if (info->overrides & DLR_BEACON_LEAK_HACK)
		first_rule = 0;
	acl = &cfg->acl_info[i];
	mutex_lock(&sw->acllock);
if (0 == info->attrib.active_super_addr.addr[5])
dbg_msg("  empty addr!\n");
	if (!memcmp(acl->mac, info->attrib.active_super_addr.addr, ETH_ALEN) &&
	    acl->first_rule == first_rule)
		goto done;
	acl->first_rule = first_rule;
	acl->ruleset = ruleset;
	acl->mode = ACL_MODE_LAYER_2;
	acl->enable = ACL_ENABLE_2_BOTH;
	acl->equal = 1;
	acl->src = 1;
	memcpy(acl->mac, info->attrib.active_super_addr.addr, ETH_ALEN);
	acl->eth_type = DLR_TAG_TYPE;
	sw_w_acl_table(sw, port, i, acl);
	i++;
	acl = &cfg->acl_info[i];
	if (!memcmp(acl->mac, MAC_ADDR_BEACON, ETH_ALEN) &&
	    acl->first_rule == first_rule)
		goto done;
	acl->first_rule = first_rule;
	acl->ruleset = ruleset;
	acl->mode = ACL_MODE_LAYER_2;
	acl->enable = ACL_ENABLE_2_BOTH;
	acl->equal = 1;
	acl->src = 0;
	memcpy(acl->mac, MAC_ADDR_BEACON, ETH_ALEN);
	acl->eth_type = DLR_TAG_TYPE;
	sw_w_acl_table(sw, port, i, acl);

done:
	mutex_unlock(&sw->acllock);
}  /* setup_acl_beacon */

static void setup_acl_beacon_timeout(struct ksz_dlr_info *info, int port)
{
	struct ksz_sw *sw = info->sw_dev;
	struct ksz_port_cfg *cfg = &sw->info->port_cfg[port];
	struct ksz_acl_table *acl;
	int i = DLR_TIMEOUT_ACL_ENTRY + 1;
	int ruleset;
	int first_rule = i;
	u8 *addr = MAC_ADDR_BEACON;

	i = DLR_TIMEOUT_ACL_ENTRY;
	ruleset = 1 << i;
	mutex_lock(&sw->acllock);
	acl = &cfg->acl_info[i];
	acl->first_rule = first_rule;
	acl->ruleset = ruleset;
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
	++i;
	acl = &cfg->acl_info[i];
	acl->map_mode = ACL_MAP_MODE_DISABLE;
	acl->ports = 0;
	sw_w_acl_action(sw, port, i, acl);
	mutex_unlock(&sw->acllock);
}  /* setup_acl_beacon_timeout */

static void setup_acl_beacon_drop(struct ksz_dlr_info *info, int drop)
{
	struct ksz_sw *sw = info->sw_dev;
	struct ksz_port_cfg *cfg;
	struct ksz_acl_table *acl;
	int i = DLR_TIMEOUT_ACL_ENTRY - 2;
	int p;

if (0 == info->attrib.active_super_addr.addr[5])
dbg_msg("  %s\n", __func__);
	for (p = 0; p < 2; p++)
		setup_acl_beacon(info, info->ports[p]);
	if (info->overrides & DLR_BEACON_LEAK_HACK)
		i = 0;
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

static void setup_vlan_table(struct ksz_dlr_info *info, u16 vid, int set)
{
	struct ksz_vlan_table vlan;
	struct ksz_sw *sw = info->sw_dev;

	memset(&vlan, 0, sizeof(struct ksz_vlan_table));
	vlan.vid = vid;
	if (set) {
		vlan.ports = sw->PORT_MASK;
		vlan.valid = true;
	}
	sw_w_vlan_table(sw, vlan.vid, &vlan);
}  /* setup_vlan_table */
#endif

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
	if (DLR_SUPERVISOR == super && (saved & DLR_BACKUP_AUTO_ON)) {

		/* Turn off previous automatic start first. */
		SW_W(sw, REG_DLR_CTRL__1, data);
dbg_msg("  reset backup: %x\n", saved);
		data |= DLR_BACKUP_AUTO_ON;
	}
	data |= DLR_ASSIST_ENABLE;
	SW_W(sw, REG_DLR_CTRL__1, data);
dbg_msg("%s %x\n", __func__, data);
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

static void sw_setup_dlr(struct ksz_sw *sw)
{
	int p;
	struct ksz_dlr_info *dlr = &sw->info->dlr;

	/* Enable 802.1p priority to give highest priority to beacon frame. */
	sw_ena_802_1p(sw, dlr->ports[0]);
	sw_ena_802_1p(sw, dlr->ports[1]);
	sw_ena_802_1p(sw, sw->HOST_PORT);

	/* DLR ports only communicate with host port. */
	sw_cfg_port_base_vlan(sw, dlr->ports[0], sw->HOST_MASK | dlr->member);
	sw_cfg_port_base_vlan(sw, dlr->ports[1], sw->HOST_MASK | dlr->member);
	for (p = 0; p < sw->mib_port_cnt; p++) {
		if (p == sw->HOST_PORT)
			continue;
		if (p == dlr->ports[0] || p == dlr->ports[1])
			continue;
		sw_cfg_port_base_vlan(sw, p, sw->PORT_MASK & ~dlr->member);
	}

	/* Need to create VLAN id 0 entry in the VLAN table. */
	port_cfg(sw, dlr->ports[0], REG_PORT_LUE_CTRL, PORT_VLAN_LOOKUP_VID_0,
		true);
	port_cfg(sw, dlr->ports[1], REG_PORT_LUE_CTRL, PORT_VLAN_LOOKUP_VID_0,
		true);

	/* Need to receive beacon frame with changed VID. */
	sw->reg->w32(sw, REG_SW_LUE_UNK_VID_CTRL__4,
		sw->HOST_MASK | SW_UNK_VID_ENABLE);

#ifdef CONFIG_HAVE_DLR_HW
	dlr_hw_set_dest_addr(sw, MAC_ADDR_BEACON);
	dlr_hw_set_port_map(sw, dlr->member);
#endif
	sw->ops->release(sw);
	sw->ops->cfg_mac(sw, DLR_SIGNON_ENTRY, MAC_ADDR_SIGNON, sw->HOST_MASK,
		false, false, 0);
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
#if 0
	microsec *= 1000;
#endif
#if 0
dbg_msg("%s %u %lx\n", __func__, microsec, jiffies);
#endif
	if (microsec >= 20000) {
		microsec /= 1000;
		delay_milli(microsec);
dbg_msg(" W %lx\n", jiffies);
	} else
		delay_micro(microsec);
}  /* wait_for_timeout */

static void dlr_set_addr(struct ksz_dlr_active_node *node, u32 ip_addr,
	u8 *addr)
{
	node->ip_addr = ip_addr;
	memcpy(node->addr, addr, ETH_ALEN);
}  /* dlr_set_addr */

static int dlr_xmit(struct ksz_dlr_info *info, u16 ports)
{
	int rc;
	struct sk_buff *skb;
	u8 *frame = info->tx_frame;
	int len = info->len;
	const struct net_device_ops *ops = info->dev->netdev_ops;
	struct ksz_sw *sw = info->sw_dev;

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

	/* Add extra for tail tagging. */
	skb = dev_alloc_skb(len + 4 + 8);
	if (!skb)
		return -ENOMEM;

	memcpy(skb->data, info->tx_frame, len);

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

static int prep_dlr_link_status(struct ksz_dlr_info *dlr)
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

	/* Link down has higher priority. */
	if (dlr->p1_down || dlr->p2_down) {
		frame->data.status.neighbor = 0;
		if (dlr->p1_down)
			frame->data.status.port1_active = 0;
		if (dlr->p2_down)
			frame->data.status.port2_active = 0;
	} else {
		frame->data.status.neighbor = 1;
		if (dlr->p1_lost)
			frame->data.status.port1_active = 0;
		if (dlr->p2_lost)
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
		node->ip_addr = htonl(dlr->ip_addr);
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

static int dbg_ann;
static void dlr_tx_announce(struct ksz_dlr_info *dlr)
{
	int rc;
	u16 ports = dlr->member;

	if (RING_NORMAL_STATE == dlr->ring_state && dlr->state != DLR_ACTIVE_NORMAL_STATE)
dbg_msg("  tx ann ?\n");
if (dbg_ann > 0) {
dbg_msg(" tx ann: %d %d %x %lx\n", dlr->state, dlr->ring_state, dlr->seqid,
jiffies);
dbg_ann--;
}
	if (RING_NORMAL_STATE == dlr->ring_state)
		ports = 1 << dlr->ports[dlr->port];

	dlr->len = prep_dlr_announce(dlr);
	dlr->len += sizeof(struct vlan_ethhdr) + sizeof(struct ksz_dlr_hdr);
	rc = dlr_xmit(dlr, ports);

	/* First delayed announce from initial fault state sent. */
	if (dlr->ann_delay)
		dlr->ann_delay = 0;
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

static void dlr_tx_status(struct ksz_dlr_info *dlr)
{
	int rc;

	dlr->len = prep_dlr_link_status(dlr);
	dlr->len += sizeof(struct vlan_ethhdr) + sizeof(struct ksz_dlr_hdr);
	rc = dlr_xmit(dlr, 0);
}  /* dlr_tx_status */

static void dlr_tx_signon(struct ksz_dlr_info *dlr, int len)
{
	int rc;

#if 0
dbg_msg("%s\n", __func__);
#endif
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

#if 0
dbg_msg("%s\n", __func__);
#endif
	sw->ops->acquire(sw);
	sw->ops->flush_table(sw, sw->mib_port_cnt);
	sw->ops->release(sw);
#if 0
dbg_msg(" %s.\n", __func__);
#endif
}

static void enableOnePort(struct ksz_dlr_info *info)
{
	struct ksz_sw *sw = info->sw_dev;
	int block_port = (info->port + 1) & 1;

#if 0
dbg_msg("%s %d\n", __func__, info->port);
#endif
	sw->ops->acquire(sw);
	port_set_stp_state(sw, info->ports[block_port], STP_STATE_BLOCKED);
	sw->ops->release(sw);
}

static void enableBothPorts(struct ksz_dlr_info *info)
{
	struct ksz_sw *sw = info->sw_dev;

#if 0
dbg_msg("%s\n", __func__);
#endif
	sw->ops->acquire(sw);
	port_set_stp_state(sw, info->ports[0], STP_STATE_FORWARDING);
	port_set_stp_state(sw, info->ports[1], STP_STATE_FORWARDING);
	sw->ops->release(sw);
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
#if 0
dbg_msg(" set state: s=%d r=%d; N=%d R=%d\n", info->state,
info->ring_state, node, ring);
#endif

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
dbg_msg("%s %x\n", __func__, data);
		if (info->node != DLR_ACTIVE_SUPERVISOR) {
			data &= ~DLR_BEACON_TX_ENABLE;
			SW_W(sw, REG_DLR_CTRL__1, data);
dbg_msg(" tx off\n");
		}
	} else if (DLR_ACTIVE_SUPERVISOR == info->node) {
			data |= DLR_BEACON_TX_ENABLE;
			SW_W(sw, REG_DLR_CTRL__1, data);
dbg_msg(" tx on\n");
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
	sw->ops->acquire(sw);
	dlr_hw_set_supervisor(sw, node);
dbg_msg("%s %d %d\n", __func__, node, info->node);
	sw->ops->release(sw);
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

dbg_msg("%s\n", __func__);
	sw->ops->acquire(sw);
	sw->ops->cfg_src_filter(sw, 1);
	sw->ops->release(sw);
	dlr_set_supervisor(info);
	info->start = 0;
	sw->ops->cfg_mac(sw, DLR_ANNOUNCE_ENTRY, MAC_ADDR_ANNOUNCE, 0, false,
		false, 0);
	sw->ops->cfg_mac(sw, DLR_BEACON_ENTRY, MAC_ADDR_BEACON, 0, false,
		false, 0);
	sw->ops->cfg_mac(sw, DLR_SIGNON_ENTRY, MAC_ADDR_SIGNON, sw->HOST_MASK,
		false, false, 0);
	sw->ops->cfg_mac(sw, DLR_LEARNING_ENTRY, MAC_ADDR_LEARNING_UPDATE, 0,
		false, false, 0);
}  /* disableSupervisor */

static void enableSupervisor(struct ksz_dlr_info *info)
{
	struct ksz_sw *sw = info->sw_dev;

#if 0
dbg_msg("%s\n", __func__);
#endif
	sw->ops->cfg_mac(sw, DLR_ANNOUNCE_ENTRY, MAC_ADDR_ANNOUNCE, 0, true,
		false, 0);
	sw->ops->cfg_mac(sw, DLR_BEACON_ENTRY, MAC_ADDR_BEACON, sw->HOST_MASK,
		!DROP_BEACON_1, false, 0);
	sw->ops->cfg_mac(sw, DLR_SIGNON_ENTRY, MAC_ADDR_SIGNON, sw->HOST_MASK,
		true, false, 0);
	sw->ops->cfg_mac(sw, DLR_LEARNING_ENTRY, MAC_ADDR_LEARNING_UPDATE, 0,
		true, false, 0);
	sw->ops->acquire(sw);
	sw->ops->cfg_src_filter(sw, 0);
#ifdef CONFIG_HAVE_DLR_HW
	dlr_hw_reset_seq_id(sw);
	dlr_hw_set_precedence(sw, info->precedence);
	dlr_hw_set_interval(sw, info->beacon_interval);
	dlr_hw_set_timeout(sw, info->beacon_timeout);
	dlr_hw_set_vlan_id(sw, info->vid);
	dlr_hw_set_ip_addr(sw, info->ip_addr);
#endif
	sw->ops->release(sw);
	info->start = 1;
	dlr_set_supervisor(info);
}  /* enableSupervisor */

static void disableAnnounce(struct ksz_dlr_info *info)
{
dbg_msg("%s\n", __func__);
	cancel_delayed_work_sync(&info->announce_tx);
}

static void startAnnounce(struct ksz_dlr_info *info)
{
dbg_msg("%s\n", __func__);
	cancel_delayed_work_sync(&info->announce_tx);
	schedule_delayed_work(&info->announce_tx, 100);
	dlr_tx_announce(info);
}  /* startAnnounce */

static void enableAnnounce(struct ksz_dlr_info *info, int delay)
{
#if 1
dbg_msg("%s %d %d %lx\n", __func__, delay, info->ann_delay,
jiffies);
#endif
	if (1 == delay) {

		/* Wait for 2 * beacon timeout before sending announce. */
		if (!info->ann_delay) {
			info->ann_delay = 1;
			cancel_delayed_work_sync(&info->announce_tx);
			schedule_delayed_work(&info->announce_tx, 0);
		}

	/* Wait until first announce is sent. */
	} else if (!info->ann_delay)
		startAnnounce(info);
}

static void disableAnnounceTimeout(struct ksz_dlr_info *info)
{
dbg_msg("%s\n", __func__);
	ksz_stop_timer(&info->announce_timeout_timer_info);
}

static void disableNeighChkTimers(struct ksz_dlr_info *info)
{
#if 0
dbg_msg("%s\n", __func__);
#endif
	info->p1_lost = info->p2_lost = 0;
	info->port_chk[0] = info->port_chk[1] = 0;
	ksz_stop_timer(&info->neigh_chk_timer_info);
	info->neigh_chk = 0;
}

static void disableSignOnTimer(struct ksz_dlr_info *info)
{
#if 0
dbg_msg("%s\n", __func__);
#endif
	ksz_stop_timer(&info->signon_timer_info);
	info->signon_start = 0;
}  /* disableSignOnTimer */

static void updateValues(struct ksz_dlr_info *info)
{
	struct ksz_dlr_gateway_capable *attrib = &info->attrib;
	struct ksz_sw *sw = info->sw_dev;
	int vid_change = false;

dbg_msg("%s\n", __func__);
	if (info->vid != attrib->super_cfg.vid) {
		vid_change = true;
		setup_vlan_table(info, info->vid, false);
	}
	sw->ops->acquire(sw);
	if (info->precedence != attrib->super_cfg.prec) {
		info->precedence = attrib->super_cfg.prec;
#ifdef CONFIG_HAVE_DLR_HW
		dlr_hw_set_precedence(sw, info->precedence);
#endif
	}
	if (info->beacon_interval != attrib->super_cfg.beacon_interval) {
dbg_msg("%s %u %u\n", __func__, info->beacon_interval, attrib->super_cfg.beacon_interval);
		info->beacon_interval = attrib->super_cfg.beacon_interval;
#ifdef CONFIG_HAVE_DLR_HW
		dlr_hw_set_interval(sw, info->beacon_interval);
#endif
	}
	if (info->beacon_timeout != attrib->super_cfg.beacon_timeout) {
		info->beacon_timeout = attrib->super_cfg.beacon_timeout;
#ifdef CONFIG_HAVE_DLR_HW
		dlr_hw_set_timeout(sw, info->beacon_timeout);
#endif
	}
	if (info->vid != attrib->super_cfg.vid) {
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
}  /* updateValues */

static void dlr_flush(struct ksz_dlr_info *info)
{
	flushMacTable(info);
}

static void setupDir(struct ksz_dlr_info *info, int port)
{
	struct ksz_sw *sw = info->sw_dev;
	int cmp;

	/* Do not change entry of own address. */
	cmp = memcmp(info->attrib.active_super_addr.addr, info->src_addr,
		ETH_ALEN);
	if (!cmp)
		return;
	if (port >= 0)
		port = 1 << info->ports[port];
	else
		port = 0;
	info->active_port = port;
	sw->ops->cfg_mac(sw, DLR_SUPERVISOR_ENTRY,
		info->attrib.active_super_addr.addr, port, false, false, 0);
dbg_msg("%s %x %02x:%02x:%02x\n", __func__, port,
info->attrib.active_super_addr.addr[3],
info->attrib.active_super_addr.addr[4],
info->attrib.active_super_addr.addr[5]);
}

static void proc_dlr_cmd(struct ksz_dlr_info *dlr, struct dlr_work *parent);

static int inside_state;
static int inside_cmd;
static int proc_dlr_hw_access(struct ksz_dlr_info *dlr, int cmd, int subcmd,
	int option, struct sk_buff *skb)
{
	struct dlr_work *work;
	int ret = 0;

if (inside_state) {
dbg_msg(" ? %d ", subcmd);
inside_cmd = subcmd;
}
	work = &dlr->work_info.works[dlr->work_info.tail];
	if (work->used) {
		pr_alert("work full\n");
		return -EFAULT;
	}
	work->skb = skb;
	work->cmd = cmd;
	work->subcmd = subcmd;
	work->option = option;
	work->used = true;
#if 0
if (work->prev->used && !in_interrupt())
dbg_msg(" used: %d %d %d %x %d; %p %p\n", dlr->work_info.tail, subcmd, work->prev->subcmd,
work->prev->index, dlr->work_info.ready, work, work->prev);
#endif
	dlr->work_info.tail++;
	dlr->work_info.tail &= DLR_WORK_LAST;
	if (!work->prev->used) {
dlr->work_info.ready = 1;
		schedule_work(&dlr->work_info.work);
}
	return ret;
}  /* proc_dlr_hw_access */

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


static int dbg_bcn;
static void acceptBeacons_(struct ksz_dlr_info *dlr)
{
dbg_msg("%s\n", __func__);
dbg_bcn += 4;
	dlr->skip_beacon = false;
#ifdef CONFIG_HAVE_ACL_HW
#if (0 == DROP_BEACON_1)
	if (dlr->node != DLR_ACTIVE_SUPERVISOR)
#endif
	setup_acl_beacon_drop(dlr, 0);
#endif
	dlr->drop_beacon = false;
}  /* acceptBeacons_ */

static void acceptBeacons(struct ksz_dlr_info *info)
{
dbg_msg("  %d %d; ", info->beacon_info[0].timeout, info->beacon_info[1].timeout);
dbg_msg("%s\n", __func__);
	info->skip_beacon = false;
	proc_dlr_hw_access(info, DEV_CMD_PUT, DEV_DLR_SETUP_DROP, 0,
		NULL);
	info->drop_beacon = false;
}  /* acceptBeacons */

#ifdef DROP_BEACON_0
static void dropBeacons(struct ksz_dlr_info *info)
{
	int drop = info->member;

	if (info->node == DLR_ACTIVE_SUPERVISOR)
		drop = 0x8000;
dbg_msg("%s\n", __func__);
	proc_dlr_hw_access(info, DEV_CMD_PUT, DEV_DLR_SETUP_DROP, drop,
		NULL);
	info->drop_beacon = true;
}  /* dropBeacons */
#endif

static void setupBeaconTimeout(struct ksz_dlr_info *info, int port)
{
#ifndef DLR_NO_ACL_TIMEOUT
dbg_msg("  setup timeout: %d\n", port);
	proc_dlr_hw_access(info, DEV_CMD_PUT, DEV_DLR_SETUP_TIMEOUT, port,
		NULL);
#endif
}  /* setupBeanconTimeout */

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
		if (!memcpy(info->nodes[i].signon.addr, addr, ETH_ALEN))
			return &info->nodes[i];
	return NULL;
}  /* find_dlr_node */

static int bcn_cnt;
static int dbg_leak = 5;

static void dbg_dlr(struct ksz_dlr_info *info, char *msg)
{
	dbg_msg(" %s: %d %d ", msg, info->state, info->ring_state);
	dbg_msg("d=%d:%d D=%d:%d l=%d:%d r=%d:%d R=%d:%d t=%d:%d T=%d:%d\n",
		info->p1_down, info->p2_down,
		info->one_down, info->both_down,
		info->p1_lost, info->p2_lost,
		info->p1_rcvd, info->p2_rcvd,
		info->one_rcvd, info->both_rcvd,
		info->p1_timeout, info->p2_timeout,
		info->one_timeout, info->both_timeout);
}

static void dlr_print(struct ksz_dlr_info *info, char *msg)
{
	if (info->overrides & DLR_TEST)
		printk(KERN_INFO "%s\n", msg);
}

static int dbg_active;
static void dlr_chk_beacon_timeout(struct ksz_dlr_info *info, int p,
	struct ksz_dlr_frame *beacon,
	struct ksz_dlr_super_info *active,
	struct ksz_dlr_super_info *super)
{
	u32 crc;
	int i;
	struct ksz_dlr_super_info *next;
	struct ksz_dlr_super_info *first = NULL;
	struct ksz_dlr_super_info *found = NULL;

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
		found->cnt++;
		found->port = p;

		/* First time. */
		if (!found->crc) {
dbg_msg("  %x=%02x:%02x:%02x:%02x:%02x:%02x  %x=%02x:%02x:%02x:%02x:%02x:%02x\n",
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
			found->crc = crc;
			memcpy(found->prec_addr, super->prec_addr,
				ETH_ALEN + 1);
		}
		found->timeout[p] += ntohl(beacon->data.beacon.interval);
		if (found->timeout[p] > info->beacon_timeout && !found->sent) {
			if (!info->rogue_super) {
				info->rogue_super = found;
				found->sent = 1;
				proc_dlr_hw_access(info, DEV_CMD_PUT,
					DEV_DLR_TX_LEARNING_UPDATE, 0, NULL);
			}
		}
	}
}  /* dlr_chk_beacon_timeout */

static void dbg_supervisor(struct ksz_dlr_info *info)
{
	struct ksz_dlr_super_info *next;
	int i;

	for (i = 0; i < DLR_SUPERVISOR_NUM; i++) {
		next = &info->supers[i];
		if (next->crc) {
dbg_msg(" super %d %x=%02x:%02x:%02x\n",
next->cnt,
next->prec_addr[0],
next->prec_addr[4],
next->prec_addr[5],
next->prec_addr[6]);
		}
	}
}  /* dbg_supervisor */

static void dlr_clr_supervisor(struct ksz_dlr_info *info)
{
	struct ksz_dlr_super_info *next;
	int i;

	for (i = 0; i < DLR_SUPERVISOR_NUM; i++) {
		next = &info->supers[i];
		if (next->crc) {
			if (next->last_cnt == next->cnt) {
dbg_msg(" clr %d %u:%u %x=%02x:%02x:%02x\n",
next->cnt, next->timeout[0], next->timeout[1],
next->prec_addr[0],
next->prec_addr[4],
next->prec_addr[5],
next->prec_addr[6]);
				memset(next, 0,
					sizeof(struct ksz_dlr_super_info));
			} else
				next->last_cnt = next->cnt;
		}
	}
}  /* dlr_clr_supervisor */

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
	u32 seqid = ntohl(beacon->hdr.seqid);
	struct ksz_dlr_gateway_capable *attrib = &info->attrib;
	struct ksz_dlr_beacon_info *beacon_info = &info->beacon_info[port];
struct ksz_dlr_super_info active;
struct ksz_dlr_super_info super;

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
		return update;

#if 1
/*
 * THa  2015/11/03
 * Hardware generates wrong ring state.
 */
	if (0 == beacon->data.beacon.ring_state)
		beacon->data.beacon.ring_state = 2;
#endif

	/* Ignore own beacon if stopped. */
	/*
	 * Only active supervisor can receive its own beacons because of
	 * self-address filtering.
	 */
	if (!memcmp(info->src_addr, vlan->h_source, ETH_ALEN)) {
#if 0
if (port == info->rx_port)
dbg_msg(" * ");
#endif
#if (1 == DROP_BEACON_1)
if (info->skip_beacon && info->drop_beacon && dbg_leak)
dbg_msg(" ^ ");
#endif
#if 0
		if (DLR_ACTIVE_SUPERVISOR != info->node && !info->start)
			info->chk_hw = 1;
#endif
		if (!info->start)
			return update;
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
		dlr_chk_beacon_timeout(info, port, beacon, &active, &super);

#if 0
/* Need to accept own beacons to check for timeout. */
if (info->skip_beacon) {
dbg_msg(" - ");
		acceptBeacons(info);
}
#endif
		return update;
	} else if (cmp > 0) {
dbg_msg("new %d %02x:%02x:%02x:%02x:%02x:%02x  %02x:%02x:%02x:%02x:%02x:%02x\n",
cmp,
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
if (info->new_supervisor)
dbg_msg("  prev super not proc\n");
		update = true;
		dlr_set_addr(&attrib->active_super_addr,
			ntohl(beacon->hdr.ip_addr), vlan->h_source);
		info->new_supervisor = 1;
		info->p1_set = info->p2_set = 1;
		info->p1_rcvd = info->p2_rcvd =
		info->one_rcvd = info->both_rcvd = 0;
		info->p1_timeout = info->p2_timeout =
		info->one_timeout = info->both_timeout = 0;
dbg_msg("  new sup 2: %d %d %d %d %d\n", beacon->data.beacon.precedence,
attrib->active_super_prec, info->precedence, attrib->super_cfg.prec,
beacon->data.beacon.ring_state);

		/* Set in following code. */
		info->LastBcnRcvPort = 0;
		if (DLR_ACTIVE_SUPERVISOR == info->node) {
dbg_active = 1;
			dbg_dlr(info, "stop being active");
dbg_bcn = 6;
		}
		memset(&info->beacon_info[0].last, 0,
			sizeof(struct ksz_dlr_beacon));
		memset(&info->beacon_info[1].last, 0,
			sizeof(struct ksz_dlr_beacon));
		info->beacon_info[0].timeout =
		info->beacon_info[1].timeout = 0;
	}

	/* Process accepted beacon. */

	interval = ntohl(beacon->data.beacon.interval);
	timeout = ntohl(beacon->data.beacon.timeout);

	/* Used to determine beacon timeout in software simulation. */
	beacon_info->rcv_once = 1;
	beacon_info->timeout_start = 0;

#ifdef DROP_BEACON_0
#ifdef CONFIG_HAVE_DLR_HW
	if (!update && info->skip_beacon /*&& info->node < DLR_ACTIVE_SUPERVISOR*/) {
if (dbg_leak > 0) {
dbg_msg(" ??: %d %d %d %x %02x:%02x:%02x:%02x:%02x:%02x %02x:%02x:%02x:%02x:%02x:%02x\n", port, info->skip_beacon, info->node, seqid,
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
vlan->h_source[5]
);
--dbg_leak;
}
}
#endif
	if (!update && info->skip_beacon)
{
if (dbg_active)
dbg_msg("  r3\n");
		return update;
}
	else if (beacon_info->timeout && !info->drop_beacon) {
		beacon_info->timeout += interval;
		if (beacon_info->timeout > timeout) {
if (RING_NORMAL_STATE != beacon->data.beacon.ring_state ||
    RING_NORMAL_STATE != info->ring_state)
dbg_msg(" drop: %d %d; %d %d\n", beacon->data.beacon.ring_state, info->ring_state,
info->beacon_info[0].timeout, info->beacon_info[1].timeout);
			info->beacon_info[0].timeout =
			info->beacon_info[1].timeout = 0;
			dropBeacons(info);
			return update;
		}
	}
	if (info->skip_beacon) {
dbg_msg(" update: %d\n", update);
		acceptBeacons(info);
	}
#endif

	/* Try to process as few beacons as possible. */
	if (memcmp(&beacon_info->last, &beacon->data.beacon,
	    sizeof(struct ksz_dlr_beacon))) {
		memcpy(&beacon_info->last, &beacon->data.beacon,
			sizeof(struct ksz_dlr_beacon));
		info->seqid_accept[port] = seqid;
	} else {
#if 0
if (dbg_active || dbg_bcn)
dbg_msg("  r4: %d %02x:%02x:%02x\n", port,
vlan->h_source[3],
vlan->h_source[4],
vlan->h_source[5]);
#endif
if (dbg_bcn)
--dbg_bcn;
if (update)
dbg_msg("  ??? update\n");
		if (beacon_info->timeout)
			return update;
	}

	/* Not running as supervisor. */
	if ((DLR_ACTIVE_SUPERVISOR != info->node &&
	    info->ring_state != beacon->data.beacon.ring_state) ||
	    update) {
int ring_state = info->ring_state;
		info->ring_state = beacon->data.beacon.ring_state;

		/* Set in following code. */
		info->LastBcnRcvPort = 0;
		info->p1_rcvd = info->p2_rcvd =
		info->one_rcvd = info->both_rcvd = 0;
		beacon_info->timeout = 0;

		if (RING_FAULT_STATE == info->ring_state) {
			dbg_dlr(info, "ring fault");
		}
dbg_msg(" R: %d %d %d %d\n", info->node, info->ring_state, ring_state, update);
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

	if (DLR_IDLE_STATE == info->state) {
#if 0
		int last = info->LastBcnRcvPort;
#endif

		if (1 == port) {
			info->LastBcnRcvPort = 2;
		} else {
			info->LastBcnRcvPort = 1;
		}
#if 0
		if (last != info->LastBcnRcvPort) {
dbg_msg("L: %d %d.\n", port, info->LastBcnRcvPort);
if (dbg_bcn > 2)
++dbg_bcn;
}
#endif
	} else if (info->state != DLR_NORMAL_STATE &&
		   info->state != DLR_ACTIVE_NORMAL_STATE) {
#if 0
		int last = info->LastBcnRcvPort;
#endif

		if (1 == port) {
			if (info->LastBcnRcvPort & 1) {
				info->LastBcnRcvPort = 3;
			} else
				info->LastBcnRcvPort = 2;
		} else {
			if (info->LastBcnRcvPort & 2) {
				info->LastBcnRcvPort = 3;
			} else
				info->LastBcnRcvPort = 1;
		}
#if 0
		if (last != info->LastBcnRcvPort && 3 == info->LastBcnRcvPort) {
dbg_msg("L: %d 3 %d.\n", port, info->ring_state);
if (dbg_bcn > 2)
++dbg_bcn;
}
#endif
	}
	if (info->p1_rcvd && info->p2_rcvd) {

		/* Running as supervisor. */
		if (DLR_ACTIVE_SUPERVISOR == info->node ||
		    RING_NORMAL_STATE == info->ring_state) {
			if (!info->both_rcvd)
				update = true;
			info->both_rcvd = 1;
			info->one_rcvd = 0;
		}

		/* Start the beacon drop process. */
		if (!beacon_info->timeout &&
		    !info->skip_beacon && !info->drop_beacon &&
		    RING_NORMAL_STATE == beacon->data.beacon.ring_state &&
		    RING_NORMAL_STATE == info->ring_state &&
		    (DLR_NORMAL_STATE == info->state ||
		    DLR_ACTIVE_NORMAL_STATE == info->state))
{
			beacon_info->timeout = 1;
dbg_msg("  ready to drop: %d\n", beacon->data.beacon.ring_state);
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
	if (vlan->h_vlan_proto == htons(ETH_P_8021Q)) {
		vid = ntohs(vlan->h_vlan_TCI) & ((1 << VLAN_PRIO_SHIFT) - 1);
		if (info->vid != vid) {
			proc_dlr_hw_access(info, DEV_CMD_PUT,
				DEV_DLR_SETUP_VID, info->vid, NULL);
			info->vid = vid;
			proc_dlr_hw_access(info, DEV_CMD_PUT,
				DEV_DLR_SETUP_VID,
				0x80000000 | info->vid, NULL);

			/* Use current VID . */
			if (attrib->super_cfg.enable)
				attrib->super_cfg.vid = vid;
			info->frame.vlan.h_vlan_TCI =
				htons((7 << VLAN_PRIO_SHIFT) | info->vid);
			memcpy(info->signon_frame, &info->frame,
				sizeof(struct vlan_ethhdr));
		}
	}
	if (info->beacon_interval != interval) {
dbg_msg("%s %u %u\n", __func__, info->beacon_interval, interval);
		info->beacon_interval = interval;

		/* Use current beacon interval. */
		if (attrib->super_cfg.enable)
			attrib->super_cfg.beacon_interval = interval;
	}
	if (info->beacon_timeout != timeout) {
		info->beacon_timeout = timeout;

		/* Use current beacon timeout. */
		if (attrib->super_cfg.enable)
			attrib->super_cfg.beacon_timeout = timeout;
		info->p1_set = info->p2_set = 1;
	}
#if 1
if (update || dbg_bcn > 0)
#endif
dbg_msg("b: %d=%d:%d %x %d; p=%d:%d r=%d:%d; %u %u %lx %d %lx %d\n", port,
beacon->data.beacon.ring_state, info->ring_state, ntohs(vlan->h_vlan_TCI), beacon_info->timeout,
info->p1_rcvd, info->p2_rcvd, info->one_rcvd, info->both_rcvd,
beacon_info->interval, bcn_cnt, seqid, info->new_supervisor,
jiffies, dbg_bcn);
if (dbg_bcn)
--dbg_bcn;
	beacon_info->interval = 0;
	if (info->p1_rcvd && info->p1_set) {
		info->p1_set = 0;
		setupBeaconTimeout(info, 0);
	}
	if (info->p2_rcvd && info->p2_set) {
		info->p2_set = 0;
		setupBeaconTimeout(info, 1);
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
	    !(info->overrides & DLR_TEST))
{
dbg_dlr(info, " ?signon");
dbg_bcn = 10;
		return false;
}
dbg_bcn = 2;
	if (DLR_ACTIVE_SUPERVISOR == info->node &&
	    !memcmp(node->addr, info->src_addr, ETH_ALEN)) {
		struct ksz_dlr_node_info *cur;
		u32 seqid = ntohl(signon->hdr.seqid);

		if (seqid != info->seqid_signon)
dbg_msg("!seqid: %08x %08x\n", seqid, info->seqid_signon);
dbg_msg("signon: %d; %d; %02x\n", num, port, vlan->h_dest[0]);
dbg_msg("%02x:%02x:%02x:%02x:%02x:%02x\n",
node->addr[0],
node->addr[1],
node->addr[2],
node->addr[3],
node->addr[4],
node->addr[5]);
		for (i = 0; i < num; i++, node++) {
			if (i && !memcmp(node->addr, info->src_addr, ETH_ALEN))
				continue;
dbg_msg("%d %02x:%02x:%02x:%02x:%02x:%02x\n", i,
node->addr[0],
node->addr[1],
node->addr[2],
node->addr[3],
node->addr[4],
node->addr[5]);
			cur = &info->nodes[info->attrib.participants_cnt];
			memcpy(&cur->signon, node,
				sizeof(struct ksz_dlr_node));
			cur->p1_down = cur->p2_down =
			cur->p1_lost = cur->p2_lost = 0;
			info->attrib.participants_cnt++;
		}

		/* Addressed to the supervisor instead of multicast address. */
		if (!memcmp(info->src_addr, vlan->h_dest, ETH_ALEN)) {
			if (info->overrides & DLR_TEST)
dbg_msg("send next\n");
			memcpy(info->signon_addr, vlan->h_source,
				ETH_ALEN);
			proc_dlr_hw_access(info, DEV_CMD_PUT,
				DEV_DLR_TX_SIGNON, 0, NULL);
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
		proc_dlr_hw_access(info, DEV_CMD_PUT, DEV_DLR_TX_SIGNON, len,
			NULL);
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
	    !(info->overrides & DLR_TEST))
{
dbg_msg("%s\n", __func__);
		return false;
}
	if (info->node != DLR_ACTIVE_SUPERVISOR &&
	    !memcmp(vlan->h_source, info->attrib.active_super_addr.addr,
	    ETH_ALEN)) {
		if (linkDown)
			proc_dlr_hw_access(info, DEV_CMD_PUT,
				DEV_DLR_TX_STATUS, 0, NULL);
		else if (!info->neigh_chk) {
			if (info->neigh_chk_timer_info.max) {
dbg_msg(" !! %s %d\n", __func__, info->neigh_chk_timer_info.max);
				return false;
			}
			info->neigh_chk = 1;
			ksz_start_timer(&info->neigh_chk_timer_info,
				info->neigh_chk_timer_info.period);
			info->neigh_chk_timer_info.max = 3;
			info->p1_lost = info->p2_lost = 0;
			info->port_chk[0] = info->port_chk[1] = 1;
			proc_dlr_hw_access(info, DEV_CMD_PUT, DEV_DLR_TX_REQ,
				0, NULL);
			proc_dlr_hw_access(info, DEV_CMD_PUT, DEV_DLR_TX_REQ,
				1, NULL);
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

	if (RING_NORMAL_STATE == announce->data.announce.ring_state &&
	    DLR_NORMAL_STATE == info->state &&
	    (!info->active_port || info->rx_port != port)) {
dbg_msg("%s %d %x dir %x %lx\n", __func__, port, info->active_port,
ntohl(announce->hdr.seqid), jiffies);
		proc_dlr_hw_access(info, DEV_CMD_PUT, DEV_DLR_SETUP_DIR, port,
			NULL);
	}
	if (announce->data.announce.ring_state != info->ring_state) {
dbg_msg(" ann: %d %d %d\n", port, info->ring_state, announce->data.announce.ring_state);
} else if (RING_NORMAL_STATE == info->ring_state && info->state != DLR_NORMAL_STATE)
dbg_msg(" ann ring normal: %d\n", port);
#if 1
	/* Rely on Announce frame to determine ring state. */
	if (info->skip_beacon) {
		if (!memcmp(vlan->h_source, attrib->active_super_addr.addr,
		    ETH_ALEN) && info->ring_state !=
		    announce->data.announce.ring_state) {
			info->ring_state = announce->data.announce.ring_state;
			acceptBeacons(info);
dbg_bcn += 4;
			return true;
		}
	}
#endif

	if (DLR_ACTIVE_SUPERVISOR == info->node) {
dbg_msg("%s ignored %d %d %d\n", __func__, port,
announce->data.announce.ring_state, info->skip_beacon);
		return false;
	}
	if (DLR_ANNOUNCE_NODE != info->node)
		return false;

info->rx_port = port;
info->tx_port = (port + 1) & 1;
	seqid = ntohl(announce->hdr.seqid);

	if (memcmp(vlan->h_source, attrib->active_super_addr.addr, ETH_ALEN) ||
	    info->ann_timeout) {
		dlr_set_addr(&attrib->active_super_addr,
			ntohl(announce->hdr.ip_addr), vlan->h_source);
		info->new_supervisor = 1;
		new = 1;
	} else {
		/* Check valid sequence number. */
		if (!seq_ahead(info->seqid_announce, seqid))
			return false;
	}
	info->seqid_announce = seqid;
	if (announce->data.announce.ring_state != info->ring_state) {
		info->ring_state = announce->data.announce.ring_state;
		info->ann_rcvd = 1;
		new = 1;
	}
	if (vlan->h_vlan_proto == htons(ETH_P_8021Q)) {
		vid = ntohs(vlan->h_vlan_TCI) & ((1 << VLAN_PRIO_SHIFT) - 1);
		if (vid != info->vid) {
			proc_dlr_hw_access(info, DEV_CMD_PUT,
				DEV_DLR_SETUP_VID, info->vid, NULL);
			info->vid = vid;
			proc_dlr_hw_access(info, DEV_CMD_PUT,
				DEV_DLR_SETUP_VID,
				0x80000000 | info->vid, NULL);
			info->frame.vlan.h_vlan_TCI =
				htons((7 << VLAN_PRIO_SHIFT) | info->vid);
			memcpy(info->signon_frame, &info->frame,
				sizeof(struct vlan_ethhdr) +
				sizeof(struct ksz_dlr_hdr));
			new = 1;
		}
	}
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

#if 0
dbg_msg("req: %08x %d %d\n",
ntohl(req->hdr.seqid), req->hdr.src_port, port);
#endif
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
	proc_dlr_hw_access(info, DEV_CMD_PUT, DEV_DLR_TX_RESP, port, NULL);
	return false;
}  /* handleNeighChkReq */

static int handleNeighChkResp(struct ksz_dlr_info *info,
	struct ksz_dlr_rx_frame *frame, int port)
{
	struct ksz_dlr_frame *resp = frame->body;
	int src_port = port ? DLR_PORT_2 : DLR_PORT_1;

#if 0
dbg_msg("resp: %08x %08x; %d %d\n",
ntohl(resp->hdr.seqid), info->seqid_chk[port],
resp->data.neigh_chk_resp.src_port, port);
#endif
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
	proc_dlr_hw_access(info, DEV_CMD_PUT, DEV_DLR_FLUSH, 0, NULL);
	if (flush->data.flush.learning_update_enable)
		proc_dlr_hw_access(info, DEV_CMD_PUT,
			DEV_DLR_TX_LEARNING_UPDATE, 0, NULL);

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
		struct ksz_dlr_node_info *prev;
		struct ksz_dlr_node_info *next;

dbg_msg("link: %02x:%02x:%02x:%02x:%02x:%02x %d:%d %d\n",
vlan->h_source[0],
vlan->h_source[1],
vlan->h_source[2],
vlan->h_source[3],
vlan->h_source[4],
vlan->h_source[5],
status->data.status.port1_active,
status->data.status.port2_active,
status->data.status.neighbor);
		prev = &info->nodes[0];
		for (i = 1; i < info->attrib.participants_cnt; i++) {
			node = &info->nodes[i];
			if (!memcmp(node->signon.addr, vlan->h_source,
			    ETH_ALEN)) {
				if (i + 1 < info->attrib.participants_cnt)
					next = node + 1;
				else
					next = &info->nodes[0];
				if (status->data.status.neighbor) {
					if (status->data.status.port1_active) {
						node->p1_down = 0;
						node->p1_lost = 0;
					} else {
						node->p1_lost = 1;
						prev->p2_lost = 1;
					}
					if (status->data.status.port2_active) {
						node->p2_down = 0;
						node->p2_lost = 0;
					} else {
						node->p2_lost = 1;
						next->p1_lost = 1;
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
			}
			prev = node;
		}
		if (!status->data.status.port1_active ||
		    !status->data.status.port2_active) {
			dlr_set_addr(&info->attrib.last_active[port],
				ntohl(status->hdr.ip_addr), vlan->h_source);
			if (1 == port)
				info->p2_lost = 1;
			else
				info->p1_lost = 1;
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
#if 0
	struct ksz_dlr_frame *update = frame->body;
#endif

dbg_msg("%s %d %d\n", __func__, info->node, port);
	if (!memcmp(info->src_addr, vlan->h_dest, ETH_ALEN)) {
dbg_msg(" to self!\n");
		proc_dlr_hw_access(info, DEV_CMD_PUT, DEV_DLR_CHK_HW, 0, NULL);
	}
	if (DLR_SUPERVISOR <= info->node) {
		if (!memcmp(info->src_addr, vlan->h_source, ETH_ALEN)) {
dbg_msg("%s %d\n", __func__, info->node);
		}
	}
	return false;
}  /* handleLearningUpdate */

static int handleBeaconTimeout(struct ksz_dlr_info *info, int port)
{
	struct ksz_dlr_beacon_info *beacon_info = &info->beacon_info[port];

	if (DLR_NORMAL_STATE == info->state ||
	    DLR_ACTIVE_NORMAL_STATE == info->state ||
	    info->state_change) {
		info->state_change = 0;
		if (1 == port)
			info->LastBcnRcvPort = 1;
		else
			info->LastBcnRcvPort = 2;
#if 0
dbg_msg("L1: %d %d\n", port, info->LastBcnRcvPort);
#endif
	} else if (info->state > DLR_IDLE_STATE) {
		int last = info->LastBcnRcvPort;

		if (1 == port) {
			if (2 == info->LastBcnRcvPort) {
				info->LastBcnRcvPort = 0;
			}
			if (DLR_SUPERVISOR <= info->node) {
				info->LastBcnRcvPort &= ~2;
				info->LastBcnRcvPort &= ~8;
			}
		} else {
			if (1 == info->LastBcnRcvPort) {
				info->LastBcnRcvPort = 0;
			}
			if (DLR_SUPERVISOR <= info->node) {
				info->LastBcnRcvPort &= ~1;
				info->LastBcnRcvPort &= ~4;
			}
		}
#if 0
dbg_msg("L2: %d %d\n", port, info->LastBcnRcvPort);
#endif
		if (last != info->LastBcnRcvPort &&
		    0 == info->LastBcnRcvPort) {
			if (DLR_SUPERVISOR == info->node)
dbg_msg("become active\n");
			else if (DLR_ACTIVE_SUPERVISOR != info->node)
dbg_msg("become idle\n");
		}
	}
	if (1 == port) {
		info->p2_rcvd = 0;
		info->p2_timeout = 1;
	} else {
		info->p1_rcvd = 0;
		info->p1_timeout = 1;
	}
	memset(&beacon_info->last, 0, sizeof(struct ksz_dlr_beacon));
	beacon_info->timeout = 0;
	if (info->p1_rcvd || info->p2_rcvd)
		info->one_rcvd = 1;
	else
		info->one_rcvd = 0;
	info->both_rcvd = 0;
	if ((info->p1_timeout && info->p2_timeout) /*|| !info->one_rcvd*/) {
		info->both_timeout = 1;
		info->one_timeout = 0;
		info->chk_hw = 1;
#if 0
if (DLR_ACTIVE_SUPERVISOR == info->node) {
dbg_msg(" chk hw\n");
		proc_dlr_hw_access(info, DEV_CMD_PUT, DEV_DLR_CHK_HW, 0, NULL);
}
#endif
	} else
		info->one_timeout = 1;
dbg_msg("timeout: r=%d:%d; t=%d:%d; R=%d:%d; T=%d:%d\n",
info->p1_rcvd, info->p2_rcvd, info->p1_timeout, info->p2_timeout,
info->one_rcvd, info->both_rcvd, info->one_timeout, info->both_timeout);
	if (info->both_timeout)
		info->p1_timeout = info->p2_timeout = 0;

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
	if ((!change[0] || link1) && (!change[1] || link2))
		going_up = true;
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
	if (info->p1_down) {
		info->p1_rcvd = 0;
		info->both_rcvd = 0;
	}
	if (info->p2_down) {
		info->p2_rcvd = 0;
		info->both_rcvd = 0;
	}
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

dbg_msg("Lo: %d:%d %d\n", down[0], down[1], info->LastBcnRcvPort);
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
			}
		}
	}
	return update;
}  /* handleLinkChange */

static void LocateFault(struct ksz_dlr_info *info)
{
	if (info->node != DLR_ACTIVE_SUPERVISOR)
		return;
#if 1
	dlr_tx_locate_fault(info);
#else
	proc_dlr_hw_access(info, DEV_CMD_PUT, DEV_DLR_TX_LOCATE, 0, NULL);
#endif
}  /* LocateFault */

static void NeighborCheck(struct ksz_dlr_info *info)
{
	struct ksz_dlr_gateway_capable *attrib = &info->attrib;

	if (!info->p1_down || !info->p2_down) {
		if (info->neigh_chk_timer_info.max) {
dbg_msg(" !! %s %d %d\n", __func__, info->neigh_chk_timer_info.max,
info->neigh_chk);
			return;
		}
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
#if 1
		dlr_tx_chk_req(info, 0);
#else
		proc_dlr_hw_access(info, DEV_CMD_PUT, DEV_DLR_TX_REQ, 0, NULL);
#endif
	}
	if (info->p2_down) {
		dlr_set_addr(&attrib->last_active[1],
			info->ip_addr, info->src_addr);
	} else {
		info->p2_lost = 0;
		info->port_chk[1] = 1;
#if 1
		dlr_tx_chk_req(info, 1);
#else
		proc_dlr_hw_access(info, DEV_CMD_PUT, DEV_DLR_TX_REQ, 1, NULL);
#endif
	}
}  /* NeighborCheck */

static void startSignOn(struct ksz_dlr_info *info, int now)
{
	if (info->signon_timer_info.max) {
dbg_msg(" !!! %s %d\n", __func__, info->signon_timer_info.max);
		return;
	}
	info->attrib.participants_cnt = 0;
	memcpy(info->signon_addr, MAC_ADDR_SIGNON, ETH_ALEN);
	ksz_start_timer(&info->signon_timer_info,
		info->signon_timer_info.period);
	if (!info->signon_delay || !info->ann_delay) {
		info->signon_delay = 0;
		if (now)
			dlr_tx_signon(info, 0);
		else
			proc_dlr_hw_access(info, DEV_CMD_PUT,
				DEV_DLR_TX_SIGNON, 0, NULL);
if (inside_cmd == DEV_DLR_TX_SIGNON)
dbg_msg(" %s\n", __func__);
	}
	else
dbg_msg("%s %d %d %lx\n", __func__, info->signon_delay, info->ann_delay,
jiffies);
}  /* startSignOn */

static void sendLinkStatus(struct ksz_dlr_info *info)
{
	/* Supervisor is known. */
	if (info->attrib.active_super_addr.addr[0] ||
	    info->attrib.active_super_addr.addr[1])
		dlr_tx_status(info);
}  /* sendLinkStatus */

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
	}
	memset(info->supers, 0, sizeof(struct ksz_dlr_super_info) *
		DLR_SUPERVISOR_NUM);
}  /* dlr_clear */

struct dlr_state {
	int change;
	int delay_ann;
	int new_state;
};

static void dlr_idle_init(struct ksz_dlr_info *info, struct dlr_state *state)
{
	struct ksz_dlr_gateway_capable *attrib = &info->attrib;

	dbg_dlr(info, "idle");
	dlr_print(info, "idle");
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
		acceptBeacons_(info);
	flushMacTable(info);
	dlr_set_state(info);
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

	dbg_dlr(info, "idle");
	dlr_print(info, "idle");
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

dbg_msg(" %d %d; %d %d;  ", info->seqid_accept[0], info->seqid_last[0],
info->seqid_accept[1], info->seqid_last[1]);
	dbg_dlr(info, "fault");
	dlr_print(info, "fault");
	newSupervisor = 0;
	announcedState = RING_FAULT_STATE;
dbg_msg("timeout %d %d; %d\n", info->beacon_info[0].timeout, info->beacon_info[1].timeout, info->drop_beacon);
if (info->drop_beacon) {
dbg_msg("  !!!\n");
	info->drop_beacon = false;
}

	attrib->net_topology = DLR_TOPOLOGY_RING;
	attrib->net_status = DLR_NET_RING_FAULT;
	if (DLR_BEACON_NODE >= info->node)
		attrib->super_status = DLR_STAT_RING_NODE;
	else
		attrib->super_status = DLR_STAT_BACKUP_SUPERVISOR;

	flushMacTable(info);
	dlr_set_state(info);
	if (linkLoss) {
		linkLoss = 0;
		sendLinkStatus(info);
	}
#if 0
	if (info->chk_hw) {
		info->chk_hw = 0;
		dlr_chk_supervisor(info);
	}
#endif
}  /* dlr_fault_init */

static void dlr_fault_next(struct ksz_dlr_info *info, struct dlr_state *state)
{
	if (twoBeaconsRcvd && !faultState) {
		newSupervisor = 0;
		disableNeighChkTimers(info);
		state->new_state = DLR_NORMAL_STATE;
	}
	if (twoBeaconsTimeout) {
#if 0
dbg_msg("to active\n");
#endif
		disableNeighChkTimers(info);
		if (DLR_BEACON_NODE >= info->node)
			state->new_state = DLR_IDLE_STATE;
		else
			state->new_state = DLR_PREPARE_STATE;
	}
	if (oneBeaconTimeout && !oneBeaconRcvd) {
		if (DLR_BEACON_NODE >= info->node)
			state->new_state = DLR_IDLE_STATE;
	}
	if (linkDown) {
dbg_msg(" s linkDown\n");
		disableNeighChkTimers(info);
		if (DLR_BEACON_NODE >= info->node)
			state->new_state = DLR_IDLE_STATE;
	}
	if (linkLoss) {
		linkLoss = 0;
dbg_msg(" s linkLoss\n");
		sendLinkStatus(info);
	}
	if (newSupervisor) {
dbg_msg("new super\n");
		newSupervisor = 0;
		flushMacTable(info);
	}

	/* Apply only to supervisor. */
	if (newValue) {
		updateValues(info);
	}
}  /* dlr_fault_next */

static void dlr_ann_fault_init(struct ksz_dlr_info *info,
	struct dlr_state *state)
{
	struct ksz_dlr_gateway_capable *attrib = &info->attrib;

	dbg_dlr(info, "fault");
	dlr_print(info, "fault");
	announceRcvd = 0;
	announcedState = RING_FAULT_STATE;

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

dbg_msg(" %d %d; %d %d;  ", info->seqid_accept[0], info->seqid_last[0],
info->seqid_accept[1], info->seqid_last[1]);
	dbg_dlr(info, "normal");
	dlr_print(info, "normal");
	newSupervisor = 0;

	attrib->net_topology = DLR_TOPOLOGY_RING;
	attrib->net_status = DLR_NET_NORMAL;
	if (DLR_BEACON_NODE >= info->node)
		attrib->super_status = DLR_STAT_RING_NODE;
	else
		attrib->super_status = DLR_STAT_BACKUP_SUPERVISOR;

	flushMacTable(info);
	dlr_set_state(info);
}  /* dlr_normal_init */

static void dlr_normal_next(struct ksz_dlr_info *info, struct dlr_state *state)
{
	if (twoBeaconsTimeout) {
		if (DLR_BEACON_NODE >= info->node)
			state->new_state = DLR_IDLE_STATE;
		else
			state->new_state = DLR_FAULT_STATE;
	}
	if (newSupervisor || faultState || oneBeaconTimeout) {

		/* Change from normal to fault. */
		if (faultState)
			info->state_change = 1;
		state->new_state = DLR_FAULT_STATE;
	}
	if (linkDown) {
dbg_msg(" s linkDown\n");
		disableNeighChkTimers(info);
		if (DLR_BEACON_NODE >= info->node)
			state->new_state = DLR_IDLE_STATE;
	}
	if (linkLoss) {
dbg_msg(" s linkLoss 2\n");
		state->new_state = DLR_FAULT_STATE;
	}

	/* Apply only to supervisor. */
	if (newValue) {
		updateValues(info);
	}
	if (state->new_state) {
		setupDir(info, -1);
		if (info->skip_beacon)
			acceptBeacons_(info);
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

	dbg_dlr(info, "normal");
	dlr_print(info, "normal");
	announceRcvd = 0;

	attrib->net_topology = DLR_TOPOLOGY_RING;
	attrib->net_status = DLR_NET_NORMAL;
	attrib->super_status = DLR_STAT_RING_NODE;

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

	dbg_dlr(info, "active");
	dlr_clear(info);
	info->beacon_info[0].timer =
	info->beacon_info[1].timer = 1;

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
	enableSupervisor(info);
	if (state->change > 0)
		state->change--;
}  /* dlr_active_init */

static void dlr_active_next(struct ksz_dlr_info *info, struct dlr_state *state)
{
	state->delay_ann = 1;
	state->new_state = DLR_ACTIVE_FAULT_STATE;
	if (newSupervisor)
		state->new_state = DLR_BACKUP_STATE;
dbg_bcn = 4;
}  /* dlr_active_next */

static void dlr_active_fault_init(struct ksz_dlr_info *info,
	struct dlr_state *state)
{
	struct ksz_dlr_gateway_capable *attrib = &info->attrib;

dbg_msg("  %d %d; ", info->beacon_info[0].timeout, info->beacon_info[1].timeout);
	dbg_dlr(info, "active fault");
	dlr_print(info, "active fault");
	dbg_supervisor(info);
	linkLoss = 0;
	newSupervisor = 0;
	announcedState = RING_FAULT_STATE;

	attrib->net_status = DLR_NET_RING_FAULT;
	memset(&attrib->last_active[0], 0,
		sizeof(struct ksz_dlr_active_node));
	memset(&attrib->last_active[1], 0,
		sizeof(struct ksz_dlr_active_node));

dbg_ann = 4;
	flushMacTable(info);
	enableBothPorts(info);
	setupBeacons(info);
	enableAnnounce(info, state->delay_ann);
	state->delay_ann = 0;
dbg_bcn = 3;
}  /* dlr_active_fault_init */

static void dlr_active_fault_next(struct ksz_dlr_info *info,
	struct dlr_state *state)
{
	if (oneBeaconTimeout || twoBeaconsTimeout) {
		oneBeaconTimeout = twoBeaconsTimeout = 0;
		if (!info->neigh_chk) {
			LocateFault(info);
			NeighborCheck(info);
		}
else
dbg_msg("chk in progress\n");
		if (info->start && info->chk_hw)
			dlr_chk_supervisor(info);
	}
	if (twoBeaconsRcvd) {
#if 0
		dbg_dlr(info, "to active normal");
#endif
		disableNeighChkTimers(info);
		state->new_state = DLR_ACTIVE_NORMAL_STATE;
	}
	if (newSupervisor) {
dbg_msg("to backup\n");
		disableNeighChkTimers(info);
		state->new_state = DLR_BACKUP_STATE;
	}
	if (newValue) {
		state->new_state = DLR_RESTART_STATE;
	}
#if 0
	if (info->chk_hw) {
		info->chk_hw = 0;
		dlr_chk_supervisor(info);
	}
#endif
}  /* dlr_active_fault_next */

static void dlr_active_normal_init(struct ksz_dlr_info *info,
	struct dlr_state *state)
{
	struct ksz_dlr_gateway_capable *attrib = &info->attrib;

	dbg_dlr(info, "active normal");
	dlr_print(info, "active normal");
	announcedState = RING_NORMAL_STATE;

	attrib->net_status = DLR_NET_NORMAL;

	/* Allow timeout notification. */
	info->beacon_timeout_ports = 0;
dbg_ann = 4;
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
dbg_bcn += 8;
}  /* dlr_active_normal_init */

static void dlr_active_normal_next(struct ksz_dlr_info *info,
	struct dlr_state *state)
{
	struct ksz_dlr_gateway_capable *attrib = &info->attrib;

	if (oneBeaconTimeout || twoBeaconsTimeout) {
		dbg_dlr(info, "active timeout");
		disableSignOnTimer(info);
		if (DLR_ACTIVE_SUPERVISOR == info->node) {
			if (twoBeaconsTimeout && info->start)
				dlr_chk_supervisor(info);
			state->new_state = DLR_ACTIVE_FAULT_STATE;
		} else
			state->new_state = DLR_FAULT_STATE;
	}
	if (linkDown) {
dbg_msg(" s linkDown\n");
		disableNeighChkTimers(info);
		state->new_state = DLR_ACTIVE_FAULT_STATE;
	}
	if (linkLoss || linkStatus) {
		dbg_dlr(info, "active loss");
		twoBeaconsRcvd = 0;
		disableSignOnTimer(info);
		if (DLR_ACTIVE_SUPERVISOR == info->node)
			state->new_state = DLR_ACTIVE_FAULT_STATE;
		else
			state->new_state = DLR_FAULT_STATE;
	}
	if (newSupervisor) {
dbg_msg("to backup\n");
		dbg_dlr(info, "to back");
dbg_active = 1;
		twoBeaconsRcvd = 0;
dbg_bcn += 4;
		disableSignOnTimer(info);
		state->new_state = DLR_BACKUP_STATE;
	}
	if (newValue) {
		state->new_state = DLR_RESTART_STATE;
	}
	if (DLR_ACTIVE_FAULT_STATE == state->new_state)
		attrib->fault_cnt++;
	if (state->new_state) {
		if (info->skip_beacon)
			acceptBeacons_(info);
		info->beacon_info[0].timeout =
		info->beacon_info[1].timeout = 0;
	}
}  /* dlr_active_normal_next */

static void dlr_backup_init(struct ksz_dlr_info *info, struct dlr_state *state)
{
	dbg_dlr(info, "backup");
	newSupervisor = 0;
	info->node = DLR_SUPERVISOR;
	disableSupervisor(info);
	enableBothPorts(info);
	state->new_state = DLR_FAULT_STATE;
}  /* dlr_backup_init */

static void dlr_backup_next(struct ksz_dlr_info *info, struct dlr_state *state)
{
}

static void dlr_prepare_init(struct ksz_dlr_info *info,
	struct dlr_state *state)
{
dbg_dlr(info, "prepare");
	wait_for_timeout(info->beacon_timeout);
	info->wait_done = 1;
}  /* dlr_prepare_init */

static void dlr_prepare_next(struct ksz_dlr_info *info,
	struct dlr_state *state)
{
	if (info->wait_done) {
dbg_dlr(info, "to active");
		info->wait_done = 0;
		state->new_state = DLR_ACTIVE_STATE;
	}
	if (newSupervisor)
		state->new_state = DLR_BACKUP_STATE;
}  /* dlr_prepare_init */

static void dlr_restart_init(struct ksz_dlr_info *info,
	struct dlr_state *state)
{
	dbg_dlr(info,"restart");

	/* Disable timeout notification. */
	info->beacon_timeout_ports = 3;
	info->wait_done = 0;
	info->node = DLR_SUPERVISOR;
	disableSupervisor(info);
	disableAnnounce(info);
	dlr_clear(info);
dbg_bcn += 5;

	/* Reset to ring fault state. */
	dlr_set_state(info);
	wait_for_timeout(info->beacon_timeout * 2);
	info->wait_done = 1;
}  /* dlr_restart_init */

static void dlr_restart_next(struct ksz_dlr_info *info,
	struct dlr_state *state)
{
	if (info->wait_done) {
	if (oneBeaconRcvd || twoBeaconsRcvd)
dbg_msg("  have beacon 0\n");
		info->wait_done = 0;
		updateValues(info);
		info->beacon_info[0].timer =
		info->beacon_info[1].timer = 1;
		state->new_state = DLR_ACTIVE_STATE;
	if (oneBeaconRcvd || twoBeaconsRcvd)
dbg_msg("  have beacon 1\n");
	}
	if (oneBeaconRcvd || twoBeaconsRcvd) {
		enableBothPorts(info);

		/* If not updated in previous code. */
		if (newValue) {
			updateValues(info);
			info->beacon_info[0].timer =
			info->beacon_info[1].timer = 1;
		}
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
#if 0
dbg_msg(" %s %d\n", __func__, info->state);
#endif
inside_state = 1;
dbg_leak = 5;
	do {
		state_info.change--;
		switch (info->state) {
		case DLR_BEGIN:
			dlr_clear(info);
			info->beacon_info[0].timer =
			info->beacon_info[1].timer = 1;
			info->LastBcnRcvPort = 0;
			memset(&attrib->last_active[0], 0,
				sizeof(struct ksz_dlr_active_node));
			memset(&attrib->last_active[1], 0,
				sizeof(struct ksz_dlr_active_node));
			attrib->participants_cnt = 0;
			if (info->skip_beacon)
				acceptBeacons_(info);
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
dbg_active = 0;
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
inside_state = 0;
#if 0
dbg_msg("  %s %d. \n", __func__, info->state);
#endif
}  /* RingSupervisor_state */

static void AnnounceRingNode_state(struct ksz_dlr_info *info)
{
	struct dlr_state state_info;
	struct ksz_dlr_gateway_capable *attrib = &info->attrib;

	state_info.change = 1;
	state_info.delay_ann = 0;
	state_info.new_state = 0;
inside_state = 1;
	do {
		state_info.change--;
		switch (info->state) {
		case DLR_BEGIN:
			dlr_clear(info);
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
				acceptBeacons_(info);
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
inside_state = 0;
}  /* AnnounceRingNode_state */

static void *check_dlr_frame(u8 *data)
{
	struct vlan_ethhdr *vlan = (struct vlan_ethhdr *) data;

	if (vlan->h_vlan_proto == htons(ETH_P_8021Q)) {
#if 0
		if (vlan->h_vlan_encapsulated_proto == htons(ETH_P_8021Q)) {
			unsigned char *ptr = (unsigned char *) vlan;

			ptr += VLAN_HLEN;
			vlan = (struct vlan_ethhdr *) ptr;
		}
#endif
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

static int dlr_rcv(struct ksz_dlr_info *info, struct sk_buff *skb, int port)
{
	struct ksz_dlr_rx_frame frame;
	struct ksz_dlr_frame *body;
	int update = false;
int inside = inside_state;

	/* Accept only from port 1 or 2. */
	if (port == info->ports[0])
		port = 0;
	else if (port == info->ports[1])
		port = 1;
	if (port > 1)
		return 1;
	body = check_dlr_frame(skb->data);
	if (body) {
inside_state = 0;
		frame.vlan = (struct vlan_ethhdr *) skb->data;
		frame.body = body;
		switch (body->hdr.frame_type) {
		case DLR_SIGN_ON:
		case DLR_NEIGH_CHK_REQ:
		case DLR_NEIGH_CHK_RESP:
		case DLR_LOCATE_FAULT:
		case DLR_FLUSH_TABLES:
			/* Need to process later after state is changed. */
			proc_dlr_hw_access(info, DEV_CMD_GET, DEV_DLR_RX,
				port, skb);
inside_state = inside;
			return 0;
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
		if (update) {
#if 0
dbg_msg("%s %d\n", __func__, body->hdr.frame_type);
#endif
			proc_dlr_hw_access(info, DEV_CMD_PUT, DEV_DLR_UPDATE,
				0, NULL);
		}
inside_state = inside;
		dev_kfree_skb_irq(skb);
		return 0;
	}
	return 1;
}  /* dlr_rcv */

static void dlr_link_change(struct ksz_dlr_info *info, int link1, int link2)
{
	if (handleLinkChange(info, link1, link2))
		proc_dlr_hw_access(info, DEV_CMD_PUT, DEV_DLR_UPDATE, 0, NULL);
}  /* dlr_link_change */

static void proc_beacon_timeout(struct work_struct *work)
{
	int p;
	struct ksz_dlr_info *dlr =
		container_of(work, struct ksz_dlr_info, beacon_rx_timeout);
int inside = inside_state;
inside_state = 0;

	for (p = 0; p < 2; p++) {
		if (dlr->beacon_timeout_ports & (1 << p)) {
			handleBeaconTimeout(dlr, p);
		}
	}
	if (dlr->beacon_timeout_ports) {
		proc_dlr_hw_access(dlr, DEV_CMD_PUT, DEV_DLR_UPDATE, 0, NULL);
		dlr->beacon_timeout_ports = 0;
	}
inside_state = inside;
}  /* proc_beacon_timeout */

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
		schedule_work(&info->beacon_rx_timeout);
	}
}  /* dlr_timeout */

static void dlr_stop(struct ksz_dlr_info *info)
{
	if (info->skip_beacon)
		acceptBeacons_(info);
	info->beacon_info[0].timeout =
	info->beacon_info[1].timeout = 0;
	info->node = DLR_BEACON_NODE;
	disableSupervisor(info);
	enableBothPorts(info);
	disableAnnounce(info);
	disableSignOnTimer(info);
}  /* dlr_stop */

static void dlr_update(struct ksz_dlr_info *info)
{
	switch (info->node) {
	case DLR_ANNOUNCE_NODE:
		AnnounceRingNode_state(info);
		break;
	default:
		RingSupervisor_state(info);
	}
}  /* dlr_update */

static void dlr_rx(struct ksz_dlr_info *info, int port, struct sk_buff *skb)
{
	struct ksz_dlr_rx_frame frame;
	int update = false;

	frame.vlan = (struct vlan_ethhdr *) skb->data;
	frame.body = check_dlr_frame(skb->data);
	switch (frame.body->hdr.frame_type) {
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
	default:
dbg_msg("%s %d\n", __func__, frame.body->hdr.frame_type);
	}
	if (update) {
dbg_msg("%s %d\n", __func__, frame.body->hdr.frame_type);
		proc_dlr_hw_access(info, DEV_CMD_PUT, DEV_DLR_UPDATE,
			0, NULL);
	}
	kfree_skb(skb);
}  /* dlr_rx */

static void setup_dir(struct ksz_dlr_info *info, int port)
{
dbg_msg("%s %d\n", __func__, port);
	info->rx_port = port;
	info->tx_port = (port + 1) & 1;
	setupDir(info, port);
}  /* setup_dir */

static void proc_dlr_cmd(struct ksz_dlr_info *dlr, struct dlr_work *parent)
{
#if 0
dbg_msg("%s %d\n", __func__, parent->index);
#endif
	switch (parent->cmd) {
	case DEV_CMD_PUT:
if (inside_cmd == parent->subcmd)
inside_cmd = 0;
		switch (parent->subcmd) {
		case DEV_DLR_CHK_HW:
			dlr_chk_supervisor(dlr);
			break;
		case DEV_DLR_CLR_SUPER:
			dlr_clr_supervisor(dlr);
			break;
		case DEV_DLR_SETUP_DIR:
			setup_dir(dlr, parent->option);
			break;
		case DEV_DLR_SETUP_DROP:
			if (!dlr->drop_beacon && parent->option)
dbg_msg(" ignore drop: %d %d\n", parent->option, dlr->skip_beacon);
			if (!dlr->drop_beacon && parent->option)
				break;
#ifdef CONFIG_HAVE_ACL_HW
#if (0 == DROP_BEACON_1)
			if (dlr->node != DLR_ACTIVE_SUPERVISOR)
#endif
			setup_acl_beacon_drop(dlr, parent->option);
#endif
			dlr->skip_beacon = !!parent->option;
			break;
		case DEV_DLR_SETUP_TIMEOUT:
#ifdef CONFIG_HAVE_ACL_HW
			setup_acl_beacon_timeout(dlr,
				dlr->ports[parent->option]);
#endif
			break;
		case DEV_DLR_SETUP_VID:
			setup_vlan_table(dlr, parent->option & ~0x80000000,
				!!(parent->option & 0x80000000));
			break;
		case DEV_DLR_FLUSH:
			dlr_flush(dlr);
			break;
			break;
		case DEV_DLR_STOP:
			dlr_stop(dlr);
			break;
		case DEV_DLR_UPDATE:
			if (parent->option) {
				dlr->reset = 1;
			}
			dlr_update(dlr);
			break;
		case DEV_DLR_START_ANNOUNCE:
			startAnnounce(dlr);
			break;
		case DEV_DLR_TX_ANNOUNCE:
			dlr_tx_announce(dlr);
			break;
		case DEV_DLR_TX_LOCATE:
			dlr_tx_locate_fault(dlr);
			break;
		case DEV_DLR_TX_SIGNON:
			dlr_tx_signon(dlr, parent->option);
			break;
		case DEV_DLR_TX_REQ:
			dlr_tx_chk_req(dlr, parent->option);
			break;
		case DEV_DLR_TX_RESP:
			dlr_tx_chk_resp(dlr, parent->option);
			break;
		case DEV_DLR_TX_STATUS:
			dlr_tx_status(dlr);
			break;
		case DEV_DLR_TX_ADVERTISE:
			dlr_tx_advertise(dlr);
			break;
		case DEV_DLR_TX_FLUSH_TABLES:
			dlr_tx_flush_tables(dlr);
			break;
		case DEV_DLR_TX_LEARNING_UPDATE:
			dlr_tx_learning_update(dlr);
			break;
		}
		break;
	case DEV_CMD_GET:
		switch (parent->subcmd) {
		case DEV_DLR_SETUP_TIMEOUT:
			break;
		case DEV_DLR_RX:
			dlr_rx(dlr, parent->option, parent->skb);
			parent->skb = NULL;
			break;
		}
		break;
	}
	parent->used = false;
#if 0
dbg_msg(" cmd:%d %p\n", parent->index, parent);
#endif
}  /* proc_dlr_cmd */

static void proc_dlr_work(struct work_struct *work)
{
	struct dlr_work_info *info =
		container_of(work, struct dlr_work_info, work);
	struct ksz_dlr_info *dlr =
		container_of(info, struct ksz_dlr_info, work_info);
	struct dlr_work *cmd;

	cmd = &info->works[info->head];
	while (cmd->used) {
		proc_dlr_cmd(dlr, cmd);
		info->head++;
		info->head &= DLR_WORK_LAST;
		cmd = &info->works[info->head];
	}
dlr->work_info.ready = 0;
}  /* proc_dlr_work */

static void init_dlr_work(struct ksz_dlr_info *dlr)
{
	struct dlr_work_info *info = &dlr->work_info;
	struct dlr_work *work;
	int i;

	for (i = 0; i < DLR_WORK_NUM; i++) {
		work = &info->works[i];
		work->index = i;
		work->prev = &info->works[(i - 1) & DLR_WORK_LAST];
	}
	info->head = info->tail = 0;
	INIT_WORK(&info->work, proc_dlr_work);
}  /* init_dlr_work */

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

dbg_msg("%s\n", __func__);
	/* Do not do anything if device is not ready. */
	if (!dlr->dev || !netif_running(dlr->dev))
		return;
	if (!memcmp(dlr->src_addr, addr, ETH_ALEN))
		return;
dbg_msg("%s.\n", __func__);
	sw->ops->cfg_mac(sw, 3, dlr->src_addr, 0, false, false, 0);
	prep_dlr_addr(dlr, addr);
	memcpy(dlr->signon_frame, &dlr->frame, sizeof(struct vlan_ethhdr) +
		sizeof(struct ksz_dlr_hdr));
	sw->ops->cfg_mac(sw, 3, dlr->src_addr, sw->HOST_MASK, false, false, 0);
	if (DLR_SUPERVISOR == dlr->node &&
	    dlr->attrib.super_cfg.prec == attrib->active_super_prec) {
		int cmp = memcmp(dlr->src_addr, attrib->active_super_addr.addr,
			ETH_ALEN);

		if (cmp > 0) {
			proc_dlr_hw_access(dlr, DEV_CMD_PUT, DEV_DLR_UPDATE, 0,
				NULL);
		}
	}
}  /* dlr_change_addr */

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
	proc_dlr_hw_access(dlr, DEV_CMD_PUT, DEV_DLR_UPDATE, 0, NULL);
	do {
		struct ksz_sw *sw = dlr->sw_dev;

		sw->ops->cfg_mac(sw, 3, dlr->src_addr, sw->HOST_MASK, false,
			false, 0);
	} while (0);
	setup_vlan_table(dlr, dlr->vid, true);
}  /* prep_dlr */

static unsigned long last_jiffies;

#ifndef CONFIG_HAVE_DLR_HW
static void chk_beacon_timeout(struct ksz_dlr_info *dlr)
{
	int p;

	for (p = 0; p < 2; p++) {
		struct ksz_dlr_beacon_info *info = &dlr->beacon_info[p];

		/* Beacon timeout timer enabled. */
		if (info->timer) {
printk("  !!!!\n");
			info->interval += BEACON_INTERVAL;
			if (info->rcv_once) {
				info->rcv_once = 0;
				info->timeout_start = 1;
				info->timeout_stop = 0;
				info->interval = 0;
			} else if (info->timeout_start)
				info->timeout_stop = 1;
			if (info->interval >= dlr->beacon_timeout &&
			    info->timeout_stop) {
#if 1
dbg_msg("  Timeout: %d %d %d %d %d %d %lx\n", p, info->rcv_once, info->timeout_start,
info->timeout_stop, info->interval, bcn_cnt, jiffies);
#endif
dbg_bcn = 3;
				info->timeout_start = info->timeout_stop = 0;
				dlr_timeout(dlr, dlr->ports[p]);
			}
		}
	}
}  /* chk_beacon_timeout */
#endif

static void beacon_monitor(struct work_struct *work)
{
	struct delayed_work *dwork = to_delayed_work(work);
	struct ksz_dlr_info *dlr =
		container_of(dwork, struct ksz_dlr_info, beacon_tx);

++bcn_cnt;
if (jiffies - last_jiffies > BEACON_TICK * 2)
dbg_msg("%lx %lx\n", last_jiffies, jiffies);
last_jiffies = jiffies;
	/* Simulate beacon interval. */
	dlr->interval += BEACON_INTERVAL;
	if (dlr->interval >= dlr->beacon_interval) {
		dlr->interval = 0;

		/* Send beacons for supervisor. */
		if (DLR_ACTIVE_SUPERVISOR == dlr->node) {
			dlr_tx_beacon(dlr);
		}
	}

#ifndef CONFIG_HAVE_DLR_HW
	chk_beacon_timeout(dlr);
#endif
	schedule_delayed_work(&dlr->beacon_tx, BEACON_TICK);
}  /* beacon_monitor */

static void announce_monitor(struct work_struct *work)
{
	struct delayed_work *dwork = to_delayed_work(work);
	struct ksz_dlr_info *dlr =
		container_of(dwork, struct ksz_dlr_info, announce_tx);
int inside = inside_state;

inside_state = 0;
	proc_dlr_hw_access(dlr, DEV_CMD_PUT, DEV_DLR_CLR_SUPER, 0, NULL);
#if 0
	if (dlr->chk_hw) {
		dlr->chk_hw = 0;
		proc_dlr_hw_access(dlr, DEV_CMD_PUT, DEV_DLR_CHK_HW, 0, NULL);
	}
#endif
inside_state = inside;
	if (DLR_ACTIVE_SUPERVISOR != dlr->node)
		return;

	if (dlr->ann_delay) {
		wait_for_timeout(dlr->beacon_timeout * 2);
	}
inside_state = 0;
if (dbg_ann)
dbg_msg(" sched ann: %d\n", dlr->signon_delay);
	proc_dlr_hw_access(dlr, DEV_CMD_PUT, DEV_DLR_TX_ANNOUNCE, 0, NULL);
	if (dlr->signon_delay) {
dbg_msg("delay signon: %lx\n", jiffies);
		proc_dlr_hw_access(dlr, DEV_CMD_PUT, DEV_DLR_TX_SIGNON, 0,
			NULL);
		dlr->signon_delay = 0;
	}
inside_state = inside;
	schedule_delayed_work(&dlr->announce_tx, 100);
}  /* announce_monitor */

static void announce_timeout_monitor(unsigned long ptr)
{
	struct ksz_dlr_info *info = (struct ksz_dlr_info *) ptr;
int inside = inside_state;
inside_state = 0;

	info->ann_timeout = 1;
	if (DLR_ANNOUNCE_NODE == info->node)
		proc_dlr_hw_access(info, DEV_CMD_PUT, DEV_DLR_UPDATE, 0, NULL);
inside_state = inside;
	ksz_update_timer(&info->announce_timeout_timer_info);
}  /* announce_timeout_monitor */

static void neigh_chk_monitor(unsigned long ptr)
{
	int p;
	struct ksz_dlr_info *dlr = (struct ksz_dlr_info *) ptr;
	int checking = 0;
	int lost = false;

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
				proc_dlr_hw_access(dlr, DEV_CMD_PUT,
					DEV_DLR_TX_REQ, p, NULL);
		}
	}
	if (lost) {
		if (DLR_ACTIVE_SUPERVISOR == dlr->node) {
			struct ksz_dlr_node_info *node;

			node = find_dlr_node(dlr, dlr->src_addr);
			if (node) {
				if (dlr->p1_lost)
					node->p1_lost = 1;
				if (dlr->p2_lost)
					node->p2_lost = 1;
			}
		} else
			proc_dlr_hw_access(dlr, DEV_CMD_PUT, DEV_DLR_TX_STATUS,
				0, NULL);
	}
	ksz_update_timer(&dlr->neigh_chk_timer_info);
	dlr->neigh_chk = !!dlr->neigh_chk_timer_info.max;
}  /* neigh_chk_monitor */

static void signon_monitor(unsigned long ptr)
{
	struct ksz_dlr_info *info = (struct ksz_dlr_info *) ptr;

dbg_msg("%s\n", __func__);
	if (DLR_ACTIVE_SUPERVISOR == info->node)
		proc_dlr_hw_access(info, DEV_CMD_PUT, DEV_DLR_TX_SIGNON, 0,
			NULL);
	else
		info->signon_timer_info.max = 1;
	ksz_update_timer(&info->signon_timer_info);
}  /* signon_monitor */

static void dlr_reset_attrib(struct ksz_dlr_info *dlr)
{
	memset(&dlr->attrib, 0, sizeof(struct ksz_dlr_gateway_capable));
#if 0
	dlr->attrib.super_status = 0xFF;
	dlr->attrib.participants_cnt = 0xFFFF;
#endif
	switch (dlr->node) {
	case DLR_ANNOUNCE_NODE:
		dlr->attrib.cap = DLR_CAP_ANNOUNCE_BASED;
		dlr->attrib.super_status = DLR_STAT_RING_NODE;
		break;
	case DLR_BEACON_NODE:
		dlr->attrib.cap = DLR_CAP_BEACON_BASED;
		dlr->attrib.cap |= DLR_CAP_SUPERVISOR_CAPABLE;
		dlr->attrib.super_status = DLR_STAT_RING_NODE;
		dlr->attrib.super_cfg.beacon_interval = 400;
		dlr->attrib.super_cfg.beacon_timeout = 1960;
		dlr->attrib.super_cfg.beacon_interval *= 2;
		dlr->attrib.super_cfg.beacon_timeout *= 1;
		break;
	default:
		dlr->attrib.cap = DLR_CAP_BEACON_BASED;
		dlr->attrib.cap |= DLR_CAP_SUPERVISOR_CAPABLE;
		dlr->attrib.super_status = DLR_STAT_ACTIVE_SUPERVISOR;
		dlr->attrib.super_cfg.enable = true;
		dlr->attrib.super_cfg.beacon_interval = 400;
		dlr->attrib.super_cfg.beacon_timeout = 1960;
		dlr->attrib.super_cfg.beacon_interval *= 2;
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
	dlr->beacon_interval *= 2;
	dlr->beacon_timeout *= 1;

	dlr->frame.vlan.h_vlan_proto = htons(ETH_P_8021Q);
	dlr->frame.vlan.h_vlan_encapsulated_proto = htons(DLR_TAG_TYPE);
	frame->hdr.ring_subtype = DLR_RING_SUBTYPE;
	frame->hdr.ring_protocol_version = 1;
	frame->hdr.ip_addr = htonl(dlr->ip_addr);
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
				if (attr->participants_cnt > 1) {
					*output = STATUS_REPLY_DATA_TOO_LARGE;
					break;
				}
				node = (struct ksz_dlr_active_node *) data;
				*len *= attr->participants_cnt;
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
int inside = inside_state;

	if (cfg->beacon_interval < 100 || cfg->beacon_interval > 100000 ||
	    cfg->beacon_timeout < 1000 || cfg->beacon_timeout > 2000000)
		return STATUS_INVALID_ATTRIB_VALUE;
inside_state = 0;
	if (cfg->enable != super->enable) {
		disableAnnounceTimeout(dlr);
		if (super->enable) {
			dlr->node = DLR_BEACON_NODE;
			proc_dlr_hw_access(dlr, DEV_CMD_PUT, DEV_DLR_STOP, 0,
				NULL);
		} else
			dlr->node = DLR_SUPERVISOR;
		super->enable = cfg->enable;
		proc_dlr_hw_access(dlr, DEV_CMD_PUT, DEV_DLR_UPDATE, 1, NULL);
	} else if (super->enable) {
		u8 prec = super->prec;

		if (cfg->prec != prec && DLR_SUPERVISOR == dlr->node) {
			int cmp = memcmp(dlr->src_addr,
				attrib->active_super_addr.addr, ETH_ALEN);

			if (cfg->prec < attrib->active_super_prec ||
			    (cfg->prec == attrib->active_super_prec &&
			    cmp < 0)) {
				prec = cfg->prec;
			}
		}
		if (cfg->prec != prec) {
			super->prec = cfg->prec;
			dlr->new_val = 1;
		}
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
		proc_dlr_hw_access(dlr, DEV_CMD_PUT, DEV_DLR_UPDATE, 0, NULL);
inside_state = inside;
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
			if (memcmp(&attr->gateway_cfg,&attrib->gateway_cfg,
			    len)) {
				memcpy(&attr->gateway_cfg, &attrib->gateway_cfg,
					len);
			}
			break;
		}
		break;
	case SVC_DLR_VERIFY_FAULT_LOCATION:
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
		proc_dlr_hw_access(dlr, DEV_CMD_PUT,
			DEV_DLR_TX_LOCATE, 0, NULL);
		break;
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

static int _dlr_dev_req(struct ksz_dlr_info *dlr, char *arg)
{
	struct ksz_request *req = (struct ksz_request *) arg;
	int len;
	int maincmd;
	int req_size;
	int subcmd;
	int output;
	u8 data[PARAM_DATA_SIZE];
	int err = 0;
	int result = 0;
	size_t param_size;

	/* Assume success. */
	result = DEV_IOC_OK;

	/* Check request size. */
	req_size = req->size;
	if (chk_ioctl_size(req_size, SIZEOF_ksz_request, 0, &req_size,
			&result, NULL, NULL))
		goto dev_ioctl_resp;

	err = 0;
	maincmd = req->cmd;
	subcmd = req->subcmd;
	output = req->output;
	len = req_size - SIZEOF_ksz_request;

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
#if 0
				data[4] = mrp->version;
				data[5] = mrp->ports;
#endif
				if (!access_ok(VERIFY_WRITE, req->param.data,
						6) ||
						copy_to_user(req->param.data,
						data, 6)) {
					err = -EFAULT;
					goto dev_ioctl_done;
				}
#if 0
				result = proc_mrp_hw_access(mrp,
					maincmd, subcmd, 0,
					data, 6, &output, true);
#endif
			} else
				result = DEV_IOC_INVALID_LEN;
			break;
		case DEV_INFO_EXIT:
#if 0
			result = proc_mrp_hw_access(mrp,
				maincmd, subcmd, 0,
				data, 0, &output, true);
#endif

		/* fall through */
		case DEV_INFO_QUIT:
			break;
		default:
			result = DEV_IOC_INVALID_CMD;
			break;
		}
		break;
	case DEV_CMD_PUT:
		memcpy(data, &req->param, len);
		result = dlr_set_attrib(dlr, subcmd, len, &req_size, data,
			&output);
		if (result)
			goto dev_ioctl_resp;
		req->output = output;
		break;
	case DEV_CMD_GET:
		result = dlr_get_attrib(dlr, subcmd, len, &req_size,
			&param_size, data, &output);
		if (result)
			goto dev_ioctl_resp;
		memcpy(req->param.data, data, param_size);
		req_size = param_size + SIZEOF_ksz_request;
		req->output = output;
		break;
	default:
		result = DEV_IOC_INVALID_CMD;
		break;
	}

dev_ioctl_resp:
	req->size = req_size;
	req->result = result;

	/* Return ERESTARTSYS so that the system call is called again. */
	if (result < 0)
		err = result;

dev_ioctl_done:
	return err;
}  /* _dlr_dev_req */

static int dlr_dev_req(struct ksz_dlr_info *dlr, char *arg)
{
	struct ksz_request *req = (struct ksz_request *) arg;
	int len;
	int maincmd;
	int req_size;
	int subcmd;
	int output;
	u8 data[PARAM_DATA_SIZE];
	int err = 0;
	int result = 0;
	size_t param_size;

	/* Assume success. */
	result = DEV_IOC_OK;

	/* Check request size. */
	__get_user(req_size, &req->size);
	if (chk_ioctl_size(req_size, SIZEOF_ksz_request, 0, &req_size,
			&result, NULL, NULL))
		goto dev_ioctl_resp;

#if 0
	if (!access_ok(VERIFY_READ, &req->param, 4) ||
	    copy_from_user(data, &req->param, 4)) {
		result = -EFAULT;
		goto dev_ioctl_resp;
	}
#endif

	err = 0;
	__get_user(maincmd, &req->cmd);
	__get_user(subcmd, &req->subcmd);
	__get_user(output, &req->output);
	len = req_size - SIZEOF_ksz_request;

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
#if 0
				data[4] = mrp->version;
				data[5] = mrp->ports;
#endif
				if (!access_ok(VERIFY_WRITE, req->param.data,
						6) ||
						copy_to_user(req->param.data,
						data, 6)) {
					err = -EFAULT;
					goto dev_ioctl_done;
				}
#if 0
				result = proc_mrp_hw_access(mrp,
					maincmd, subcmd, 0,
					data, 6, &output, true);
#endif
			} else
				result = DEV_IOC_INVALID_LEN;
			break;
		case DEV_INFO_EXIT:
#if 0
			result = proc_mrp_hw_access(mrp,
				maincmd, subcmd, 0,
				data, 0, &output, true);
#endif

		/* fall through */
		case DEV_INFO_QUIT:
			break;
		default:
			result = DEV_IOC_INVALID_CMD;
			break;
		}
		break;
	case DEV_CMD_PUT:
		if (chk_ioctl_size(len, len, 0, &req_size, &result,
		    &req->param, data))
			goto dev_ioctl_resp;
		result = dlr_set_attrib(dlr, subcmd, len, &req_size, data,
			&output);
		if (result)
			goto dev_ioctl_resp;
		__put_user(output, &req->output);
		break;
	case DEV_CMD_GET:
		result = dlr_get_attrib(dlr, subcmd, len, &req_size,
			&param_size, data, &output);
		if (result)
			goto dev_ioctl_resp;
		if (!access_ok(VERIFY_WRITE, req->param.data, param_size) ||
		    copy_to_user(req->param.data, data, param_size)) {
			err = -EFAULT;
			goto dev_ioctl_done;
		}
		req_size = param_size + SIZEOF_ksz_request;
		__put_user(output, &req->output);
		break;
	default:
		result = DEV_IOC_INVALID_CMD;
		break;
	}

dev_ioctl_resp:
	__put_user(req_size, &req->size);
	__put_user(result, &req->result);

	/* Return ERESTARTSYS so that the system call is called again. */
	if (result < 0)
		err = result;

dev_ioctl_done:
	return err;
}  /* dlr_dev_req */

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
	struct ksz_request_actual req;
	int rc;
	struct ksz_dlr_info *dlr = fd;

	set_dlr_req(&req, DEV_CMD_GET, SVC_GET_ATTRIBUTES_ALL,
		CLASS_DLR_OBJECT, CIP_INSTANCE_ATTRIBUTES, 0,
		NULL, sizeof(struct ksz_dlr_gateway_capable));
	rc = _dlr_dev_req(dlr, (char *) &req);
	if (!rc)
		rc = req.result;
	if (!rc) {
		memcpy(capable, &req.param, req.size - SIZEOF_ksz_request);
	}
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

enum {
	PROC_GET_DLR_INFO,
	PROC_SET_DLR_NODE,
	PROC_SET_DLR_PRECEDENCE,
	PROC_SET_DLR_INTERVAL,
	PROC_SET_DLR_TIMEOUT,
	PROC_SET_DLR_VID,
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

static void display_faults(struct ksz_dlr_info *dlr)
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
		dbg_msg("%02x:%02x:%02x:%02x:%02x:%02x %u.%u.%u.%u\n",
			signon->addr[0], signon->addr[1], signon->addr[2],
			signon->addr[3], signon->addr[4], signon->addr[5],
			(u8)(signon->ip_addr >> 24),
			(u8)(signon->ip_addr >> 16),
			(u8)(signon->ip_addr >> 8),
			(u8) signon->ip_addr);
		dbg_msg("%u:%u %u:%u\n",
			node->p1_down, node->p2_down,
			node->p1_lost, node->p2_lost);
	}
}  /* display_faults */

static void display_nodes(struct ksz_dlr_info *dlr)
{
	int i;
	struct ksz_dlr_node_info *node;
	struct ksz_dlr_node *signon;

	for (i = 0; i < dlr->attrib.participants_cnt; i++) {
		node = &dlr->nodes[i];
		signon = &node->signon;
		dbg_msg("%02x:%02x:%02x:%02x:%02x:%02x  %u.%u.%u.%u  ",
			signon->addr[0], signon->addr[1], signon->addr[2],
			signon->addr[3], signon->addr[4], signon->addr[5],
			(u8)(signon->ip_addr >> 24),
			(u8)(signon->ip_addr >> 16),
			(u8)(signon->ip_addr >> 8),
			(u8) signon->ip_addr);
		dbg_msg("%u:%u %u:%u\n",
			node->p1_down, node->p2_down,
			node->p1_lost, node->p2_lost);
	}
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
			"%u.%u.%u.%u  %02x:%02x:%02x:%02x:%02x:%02x\n",
			(u8)(node->ip_addr >> 24),
			(u8)(node->ip_addr >> 16),
			(u8)(node->ip_addr >> 8),
			(u8) node->ip_addr,
			node->addr[0],
			node->addr[1],
			node->addr[2],
			node->addr[3],
			node->addr[4],
			node->addr[5]);
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
	struct ksz_dlr_active_node nodes[10];
	struct ksz_dlr_super_cfg super;
	struct ksz_dlr_gateway_capable capable;
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
			display_faults(dlr);
		break;
	case PROC_SET_DLR_SIGN_ON:
		if (DLR_ACTIVE_SUPERVISOR == dlr->node)
			display_nodes(dlr);
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
		rc = get_dlr_all(dlr, &capable);
		if (!rc)
			len = show_dlr_attrib_all(len, buf, err, &capable);
		break;
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
		word = sizeof(nodes);
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
		break;
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

	switch (proc_num) {
	case PROC_SET_DLR_NODE:
		if (!(DLR_ANNOUNCE_NODE <= num &&
		    num <= DLR_ACTIVE_SUPERVISOR))
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
			acceptBeacons_(info);
		if (DLR_ANNOUNCE_NODE == info->node)
			sw->ops->cfg_mac(sw, DLR_BEACON_ENTRY,
				MAC_ADDR_BEACON, 0, false, false, 0);
		if (num == info->node)
			break;
		info->node = (u8) num;
		dlr_reset_attrib(info);
		info->attrib.super_cfg.beacon_interval = info->beacon_interval;
		info->attrib.super_cfg.beacon_timeout = info->beacon_timeout;
dbg_bcn = 4;
		do {
			struct ksz_sw *sw = info->sw_dev;

			if (DLR_ANNOUNCE_NODE == info->node)
				sw->ops->cfg_mac(sw, DLR_BEACON_ENTRY,
					MAC_ADDR_BEACON, info->member,
					false, false, 0);
			proc_dlr_hw_access(info, DEV_CMD_PUT, DEV_DLR_UPDATE,
				1, NULL);
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
		} else if (num >= ACL_CNT_M * 1000) {
			printk("too large\n");
			break;
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
		if (num & 4)
			info->overrides |= DLR_BEACON_LEAK_HACK;
		else
			info->overrides &= ~DLR_BEACON_LEAK_HACK;
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
			proc_dlr_hw_access(info, DEV_CMD_PUT, DEV_DLR_TX_REQ,
				0, NULL);
		}
		if (num & 2) {
			info->port_chk[1] = 1;
			proc_dlr_hw_access(info, DEV_CMD_PUT, DEV_DLR_TX_REQ,
				1, NULL);
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
			proc_dlr_hw_access(info, DEV_CMD_PUT,
				DEV_DLR_TX_STATUS, 0, NULL);
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
		if (netif_running(info->dev))
			printk(KERN_ALERT "stop %s first", info->dev->name);
		if (0 <= num && num < sw->phy_port_cnt &&
		    num != sw->HOST_PORT && num != info->ports[1])
			info->ports[0] = (u8) num;
		info->member = (1 << info->ports[0]) | (1 << info->ports[1]);
		break;
	case PROC_SET_DLR_PORT_2:
		if (netif_running(info->dev))
			printk(KERN_ALERT "stop %s first", info->dev->name);
		if (0 <= num && num < sw->phy_port_cnt &&
		    num != sw->HOST_PORT && num != info->ports[0])
			info->ports[1] = (u8) num;
		info->member = (1 << info->ports[0]) | (1 << info->ports[1]);
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
	cancel_delayed_work_sync(&dlr->announce_tx);
	cancel_delayed_work_sync(&dlr->beacon_tx);
}  /* ksz_dlr_exit */

static void ksz_dlr_init(struct ksz_dlr_info *dlr, struct ksz_sw *sw)
{
#if 0
	dlr->overrides = DLR_BEACON_LEAK_HACK;
#endif
	dlr->ports[0] = 0;
	dlr->ports[1] = 1;
	dlr->member = (1 << dlr->ports[0]) | (1 << dlr->ports[1]);
	dlr->sw_dev = sw;
	dlr->node = DLR_BEACON_NODE;
	setup_dlr(dlr);
	INIT_DELAYED_WORK(&dlr->announce_tx, announce_monitor);
	INIT_DELAYED_WORK(&dlr->beacon_tx, beacon_monitor);
	INIT_WORK(&dlr->beacon_rx_timeout, proc_beacon_timeout);
	init_dlr_work(dlr);
#ifdef CONFIG_HAVE_DLR_HW_
sw->overrides |= ACL_INTR_MONITOR;
#endif
	dlr->ops = &dlr_ops;
#ifdef CONFIG_HAVE_DLR_HW
	if (!(sw->features & REDUNDANCY_SUPPORT))
		schedule_delayed_work(&dlr->beacon_tx, BEACON_TICK);
#endif
}  /* ksz_dlr_init */

