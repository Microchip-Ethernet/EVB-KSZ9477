/**
 * Microchip HSR code
 *
 * Copyright (c) 2016-2017 Microchip Technology Inc.
 *	Tristram Ha <Tristram.Ha@microchip.com>
 *
 * Copyright 2011-2014 Autronica Fire and Security AS

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * Author(s):
 *	2011-2014 Arvid Brodin, arvid.brodin@alten.se
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */


static int dbg_hsr;

struct hsr_cfg_work {
	struct work_struct work;
	struct ksz_sw *sw;
	u8 addr[ETH_ALEN];
	u16 member;
};

static void proc_hsr_cfg_work(struct work_struct *work)
{
	struct hsr_cfg_work *cfg_work =
		container_of(work, struct hsr_cfg_work, work);
	struct ksz_sw *sw = cfg_work->sw;

	sw->ops->cfg_mac(sw, 0, cfg_work->addr, cfg_work->member,
		false, false, 0);

	kfree(cfg_work);
}  /* proc_hsr_work */

static void proc_hsr_cfg(struct ksz_hsr_info *info, u8 *addr, u16 member)
{
	struct hsr_cfg_work *cfg_work;

	cfg_work = kzalloc(sizeof(struct hsr_cfg_work), GFP_KERNEL);
	if (!cfg_work)
		return;
	INIT_WORK(&cfg_work->work, proc_hsr_cfg_work);
	cfg_work->sw = info->sw_dev;
	memcpy(cfg_work->addr, addr, ETH_ALEN);
	cfg_work->member = member;
	schedule_work(&cfg_work->work);
}  /* proc_hsr_cfg */

#if 0
static bool is_admin_up(struct net_device *dev)
{
	return dev && (dev->flags & IFF_UP);
}
#endif

static
struct hsr_port *hsr_port_get_hsr(struct hsr_priv *hsr, enum hsr_port_type pt)
{
	struct ksz_hsr_info *info = container_of(hsr,
		struct ksz_hsr_info, hsr);

	if (pt < HSR_PT_PORTS)
		return &info->hsr_ports[pt];
	return NULL;
}

struct hsr_node {
	struct list_head	mac_list;
	unsigned char		MacAddressA[ETH_ALEN];
	unsigned char		MacAddressB[ETH_ALEN];
	/* Local slave through which AddrB frames are received from this node */
	enum hsr_port_type	AddrB_port;
	unsigned long		time_in[HSR_PT_PORTS];
	bool			time_in_stale[HSR_PT_PORTS];
	u16			seq_out[HSR_PT_PORTS];
	unsigned long		time_out[HSR_PT_PORTS];
	struct rcu_head		rcu_head;
	int			slave;
};


/*	TODO: use hash lists for mac addresses (linux/jhash.h)?    */


/* seq_nr_after(a, b) - return true if a is after (higher in sequence than) b,
 * false otherwise.
 */
static bool seq_nr_after(u16 a, u16 b)
{
	/* Remove inconsistency where
	 * seq_nr_after(a, b) == seq_nr_before(a, b)
	 */
	if ((int) b - a == 32768)
		return false;

	return (((s16) (b - a)) < 0);
}
#define seq_nr_before(a, b)		seq_nr_after((b), (a))
#define seq_nr_after_or_eq(a, b)	(!seq_nr_before((a), (b)))
#define seq_nr_before_or_eq(a, b)	(!seq_nr_after((a), (b)))


static
bool hsr_addr_is_self(struct hsr_priv *hsr, unsigned char *addr)
{
	struct hsr_node *node;

	node = list_first_or_null_rcu(&hsr->self_node_db, struct hsr_node,
				      mac_list);
	if (!node) {
		WARN_ONCE(1, "HSR: No self node\n");
		return false;
	}

	if (ether_addr_equal(addr, node->MacAddressA))
		return true;
	if (ether_addr_equal(addr, node->MacAddressB))
		return true;

	return false;
}

/* Search for mac entry. Caller must hold rcu read lock.
 */
static struct hsr_node *find_node_by_AddrA(struct list_head *node_db,
					   const unsigned char addr[ETH_ALEN])
{
	struct hsr_node *node;

	list_for_each_entry_rcu(node, node_db, mac_list) {
		if (ether_addr_equal(node->MacAddressA, addr))
			return node;
	}

	return NULL;
}


/* Helper for device init; the self_node_db is used in hsr_rcv() to recognize
 * frames from self that's been looped over the HSR ring.
 */
static
int hsr_create_self_node(struct list_head *self_node_db,
			 unsigned char addr_a[ETH_ALEN],
			 unsigned char addr_b[ETH_ALEN])
{
	struct hsr_node *node, *oldnode;

	node = kmalloc(sizeof(*node), GFP_KERNEL);
	if (!node)
		return -ENOMEM;

	ether_addr_copy(node->MacAddressA, addr_a);
	ether_addr_copy(node->MacAddressB, addr_b);

	rcu_read_lock();
	oldnode = list_first_or_null_rcu(self_node_db,
						struct hsr_node, mac_list);
	if (oldnode) {
		list_replace_rcu(&oldnode->mac_list, &node->mac_list);
		rcu_read_unlock();
		synchronize_rcu();
		kfree(oldnode);
	} else {
		rcu_read_unlock();
		list_add_tail_rcu(&node->mac_list, self_node_db);
	}

	return 0;
}


/* Allocate an hsr_node and add it to node_db. 'addr' is the node's AddressA;
 * seq_out is used to initialize filtering of outgoing duplicate frames
 * originating from the newly added node.
 */
static
struct hsr_node *hsr_add_node_(struct list_head *node_db, unsigned char addr[],
			       u16 seq_out)
{
	struct hsr_node *node;
	unsigned long now;
	int i;

#if 1
dbg_msg("%s %02x:%02x:%02x:%02x:%02x:%02x %04x\n", __func__,
addr[0], addr[1], addr[2], addr[3], addr[4], addr[5], seq_out);
#endif
	node = kzalloc(sizeof(*node), GFP_ATOMIC);
	if (!node)
		return NULL;

	ether_addr_copy(node->MacAddressA, addr);

	/* We are only interested in time diffs here, so use current jiffies
	 * as initialization. (0 could trigger an spurious ring error warning).
	 */
	now = jiffies;
	for (i = 0; i < HSR_PT_PORTS; i++)
		node->time_in[i] = now;
	for (i = 0; i < HSR_PT_PORTS; i++)
		node->seq_out[i] = seq_out;
	for (i = 0; i < HSR_PT_PORTS; i++)
		node->time_out[i] = now;

	list_add_tail_rcu(&node->mac_list, node_db);

	return node;
}

static
struct hsr_node *hsr_add_node(struct list_head *node_db, unsigned char addr[],
			      u16 seq_out)
{
	struct hsr_node *node;

	node = hsr_add_node_(node_db, addr, seq_out);
	if (!node)
		return node;

	do {
		struct hsr_priv *hsr = container_of(node_db,
			struct hsr_priv, node_db);
		struct ksz_hsr_info *info = container_of(hsr,
			struct ksz_hsr_info, hsr);
		int not_self;

		not_self = memcmp(addr, info->src_addr, ETH_ALEN);
		if (not_self)
			proc_hsr_cfg(info, addr, info->member);
		info->part_cnt++;
	} while (0);

	return node;
}

static
struct hsr_node *hsr_add_slave(struct list_head *node_db,
	unsigned char addr[], u16 seq_out)
{
	struct hsr_node *node;

	node = hsr_add_node_(node_db, addr, seq_out);
	if (!node)
		return node;

	node->slave = 1;

	return node;
}

/* Get the hsr_node from which 'skb' was sent.
 */
static
struct hsr_node *hsr_get_node(struct list_head *node_db, struct sk_buff *skb,
			      bool is_sup)
{
	struct hsr_node *node;
	struct ethhdr *ethhdr;
	struct ethhdr *exthdr;
	u16 seq_out;

	if (!skb_mac_header_was_set(skb))
		return NULL;

	ethhdr = (struct ethhdr *) skb_mac_header(skb);

	list_for_each_entry_rcu(node, node_db, mac_list) {
		if (ether_addr_equal(node->MacAddressA, ethhdr->h_source))
			return node;
		if (ether_addr_equal(node->MacAddressB, ethhdr->h_source))
			return node;
	}

	if (!is_sup)
		return NULL; /* Only supervision frame may create node entry */

	exthdr = ethhdr;
	if (exthdr->h_proto == htons(ETH_P_8021Q))
		exthdr = (struct ethhdr *)((u8 *) exthdr + VLAN_HLEN);
	if (exthdr->h_proto == htons(ETH_P_HSR))
		exthdr = (struct ethhdr *)((u8 *) exthdr + HSR_HLEN);
	else {
		struct hsr_priv *hsr = container_of(node_db,
			struct hsr_priv, node_db);

		/* Supervision frame has its own sequence number. */
		seq_out = hsr->sequence_nr - 1;
		goto get_node_done;
	}
	if (exthdr->h_proto == htons(ETH_P_PRP)) {
		/* Use the existing sequence_nr from the tag as starting point
		 * for filtering duplicate frames.
		 */
		seq_out = hsr_get_skb_sequence_nr(skb) - 1;
	} else {
int i;
for (i = 0; i < 20; i++)
dbg_msg("%02x ", skb->data[i]);
dbg_msg("  %04x\n", ethhdr->h_proto);
		WARN_ONCE(1, "%s: Non-HSR frame\n", __func__);
		seq_out = 0;
	}

get_node_done:
	return hsr_add_node(node_db, ethhdr->h_source, seq_out);
}

/* Use the Supervision frame's info about an eventual MacAddressB for merging
 * nodes that has previously had their MacAddressB registered as a separate
 * node.
 */
static
void hsr_handle_sup_frame(struct sk_buff *skb, struct hsr_node *node_curr,
			  struct hsr_port *port_rcv)
{
	struct hsr_node *node_real;
	struct hsr_sup_payload *hsr_sp;
	struct hsr_sup_type *hsr_stype;
	struct list_head *node_db;
	int i;

	skb_pull(skb, sizeof(struct hsr_ethhdr_sp));
	skb_pull(skb, sizeof(struct hsr_tag));
	hsr_sp = (struct hsr_sup_payload *) skb->data;

	if (ether_addr_equal(eth_hdr(skb)->h_source, hsr_sp->MacAddressA))
		/* Not sent from MacAddressB of a PICS_SUBS capable node */
		goto done;

	/* Check frame sent by RedBox. */
	hsr_stype = (struct hsr_sup_type *)(hsr_sp + 1);
	if (HSR_TLV_REDBOX == hsr_stype->HSR_TLV_Type) {
		hsr_sp = (struct hsr_sup_payload *)(hsr_stype + 1);
		if (ether_addr_equal(eth_hdr(skb)->h_source,
		    hsr_sp->MacAddressA))
			goto done;
	}

	/* Merge node_curr (registered on MacAddressB) into node_real */
	node_db = &port_rcv->hsr->node_db;
	node_real = find_node_by_AddrA(node_db, hsr_sp->MacAddressA);
	if (!node_real)
{
	u8 *data = (u8 *) eth_hdr(skb)->h_source;
dbg_msg("add new: %02x:%02x:%02x\n", data[3], data[4], data[5]);
}
	if (!node_real)
		/* No frame received from AddrA of this node yet */
		node_real = hsr_add_node(node_db, hsr_sp->MacAddressA,
					 HSR_SEQNR_START - 1);
	if (!node_real)
		goto done; /* No mem */
	if (node_real == node_curr)
		/* Node has already been merged */
		goto done;

	ether_addr_copy(node_real->MacAddressB, eth_hdr(skb)->h_source);
#if 1
do {
	u8 *data = (u8 *) eth_hdr(skb)->h_source;
dbg_msg("%s %02x:%02x:%02x:%02x:%02x:%02x\n", __func__,
data[0], data[1], data[2], data[3], data[4], data[5]);
} while (0);
#endif
	for (i = 0; i < HSR_PT_PORTS; i++) {
		if (!node_curr->time_in_stale[i] &&
		    time_after(node_curr->time_in[i], node_real->time_in[i])) {
			node_real->time_in[i] = node_curr->time_in[i];
			node_real->time_in_stale[i] = node_curr->time_in_stale[i];
		}
		if (seq_nr_after(node_curr->seq_out[i], node_real->seq_out[i]))
			node_real->seq_out[i] = node_curr->seq_out[i];
	}
	node_real->AddrB_port = port_rcv->type;

	list_del_rcu(&node_curr->mac_list);
	kfree_rcu(node_curr, rcu_head);

done:
	skb_push(skb, sizeof(struct hsr_tag));
	skb_push(skb, sizeof(struct hsr_ethhdr_sp));
}


/* 'skb' is a frame meant for this host, that is to be passed to upper layers.
 *
 * If the frame was sent by a node's B interface, replace the source
 * address with that node's "official" address (MacAddressA) so that upper
 * layers recognize where it came from.
 */
static
void hsr_addr_subst_source(struct hsr_node *node, struct sk_buff *skb)
{
#ifdef DEBUG
	if (!skb_mac_header_was_set(skb)) {
		WARN_ONCE(1, "%s: Mac header not set\n", __func__);
		return;
	}
#endif

	memcpy(&eth_hdr(skb)->h_source, node->MacAddressA, ETH_ALEN);
}

#if 0
/* 'skb' is a frame meant for another host.
 * 'port' is the outgoing interface
 *
 * Substitute the target (dest) MAC address if necessary, so the it matches the
 * recipient interface MAC address, regardless of whether that is the
 * recipient's A or B interface.
 * This is needed to keep the packets flowing through switches that learn on
 * which "side" the different interfaces are.
 */
static
void hsr_addr_subst_dest(struct hsr_node *node_src, struct sk_buff *skb,
			 struct hsr_port *port)
{
	struct hsr_node *node_dst;

#ifdef DEBUG
	if (!skb_mac_header_was_set(skb)) {
		WARN_ONCE(1, "%s: Mac header not set\n", __func__);
		return;
	}
#endif

	if (!is_unicast_ether_addr(eth_hdr(skb)->h_dest))
		return;

	node_dst = find_node_by_AddrA(&port->hsr->node_db, eth_hdr(skb)->h_dest);
	if (!node_dst) {
#if 1
u8 *addr = eth_hdr(skb)->h_dest;
dbg_msg("%s %02x:%02x:%02x:%02x:%02x:%02x\n", __func__,
addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);
#endif
		WARN_ONCE(1, "%s: Unknown node\n", __func__);
		return;
	}
	if (port->type != node_dst->AddrB_port)
		return;

	ether_addr_copy(eth_hdr(skb)->h_dest, node_dst->MacAddressB);
}
#endif


static
void hsr_register_frame_in(struct hsr_node *node, struct hsr_port *port,
			   u16 sequence_nr)
{
	/* Don't register incoming frames without a valid sequence number. This
	 * ensures entries of restarted nodes gets pruned so that they can
	 * re-register and resume communications.
	 */
	if (seq_nr_before(sequence_nr, node->seq_out[port->type]))
	{
		unsigned long diff = jiffies - node->time_in[port->type];
#if 0
dbg_msg("%s %d %04x %04x %lu\n", __func__, port->type,
sequence_nr, node->seq_out[port->type], diff);
#endif
		if (diff <= msecs_to_jiffies(HSR_ENTRY_FORGET_TIME))
			return;
	}

	node->time_in[port->type] = jiffies;
	node->time_in_stale[port->type] = false;
}

static
void hsr_update_frame_out(struct hsr_port *port, struct hsr_node *node,
	u16 sequence_nr)
{
	node->seq_out[port->type] = sequence_nr;
}

/* 'skb' is a HSR Ethernet frame (with a HSR tag inserted), with a valid
 * ethhdr->h_source address and skb->mac_header set.
 *
 * Return:
 *	 1 if frame can be shown to have been sent recently on this interface,
 *	 0 otherwise, or
 *	 negative error code on error
 */
static
int hsr_register_frame_out(struct hsr_port *port, struct hsr_node *node,
			   u16 sequence_nr)
{
	if (seq_nr_before_or_eq(sequence_nr, node->seq_out[port->type]))
	{
		unsigned long diff = jiffies - node->time_out[port->type];
#if 1
#if 0
if (port->type != HSR_PT_MASTER)
#endif
if (dbg_hsr < 10)
dbg_msg("%s %d %04x %04x %lu\n", __func__, port->type, sequence_nr,
node->seq_out[port->type], diff);
#endif
		if (diff <= msecs_to_jiffies(HSR_ENTRY_FORGET_TIME))
			return 1;
	}
	node->time_out[port->type] = jiffies;

	node->seq_out[port->type] = sequence_nr;
	return 0;
}


#if 0
static struct hsr_port *get_late_port(struct hsr_priv *hsr,
				      struct hsr_node *node)
{
	if (node->time_in_stale[HSR_PT_SLAVE_A])
		return hsr_port_get_hsr(hsr, HSR_PT_SLAVE_A);
	if (node->time_in_stale[HSR_PT_SLAVE_B])
		return hsr_port_get_hsr(hsr, HSR_PT_SLAVE_B);

	if (time_after(node->time_in[HSR_PT_SLAVE_B],
		       node->time_in[HSR_PT_SLAVE_A] +
					msecs_to_jiffies(MAX_SLAVE_DIFF)))
		return hsr_port_get_hsr(hsr, HSR_PT_SLAVE_A);
	if (time_after(node->time_in[HSR_PT_SLAVE_A],
		       node->time_in[HSR_PT_SLAVE_B] +
					msecs_to_jiffies(MAX_SLAVE_DIFF)))
		return hsr_port_get_hsr(hsr, HSR_PT_SLAVE_B);

	return NULL;
}
#endif


static void hsr_notify_link_lost(struct ksz_hsr_info *info)
{
dbg_msg(" hsr: %u %u:%u %u:%u\n", info->ring,
	info->p1_down, info->p2_down, info->p1_lost, info->p2_lost);
	if (info->dev_info) {
		u8 buf[sizeof(struct ksz_resp_msg) +
			sizeof(struct ksz_hsr_node)];
		struct ksz_resp_msg *msg = (struct ksz_resp_msg *) buf;
		struct ksz_hsr_node active;

		msg->module = DEV_MOD_HSR;
		msg->cmd = DEV_INFO_HSR_LINK;
		msg->resp.data[0] = 0;
		if (info->p1_down)
			msg->resp.data[0] |= 0x01;
		if (info->p2_down)
			msg->resp.data[0] |= 0x02;
		if (info->p1_lost)
			msg->resp.data[0] |= 0x04;
		if (info->p2_lost)
			msg->resp.data[0] |= 0x08;
		memcpy(active.addr, info->src_addr, ETH_ALEN);
		memcpy(&msg->resp.data[1], &active,
			sizeof(struct ksz_hsr_node));
		sw_setup_msg(info->dev_info, msg, sizeof(struct ksz_resp_msg) +
			sizeof(struct ksz_hsr_node), NULL, NULL);
	}
}  /* hsr_notify_link_lost */

#ifdef CONFIG_HAVE_HSR_HW
static void hsr_chk_ring(struct work_struct *work)
{
	struct hsr_node *node;
	struct delayed_work *dwork = to_delayed_work(work);
	struct ksz_hsr_info *info =
		container_of(dwork, struct ksz_hsr_info, chk_ring);
	struct hsr_priv *hsr = &info->hsr;
	int change = false;
	int no_drop_win = false;
	u16 start_seq[2];
	u16 exp_seq[2];

	memset(start_seq, 0, sizeof(start_seq));
	memset(exp_seq, 0, sizeof(exp_seq));

	rcu_read_lock();
	list_for_each_entry_rcu(node, &hsr->node_db, mac_list) {
		if (!memcmp(node->MacAddressA, info->src_addr, ETH_ALEN))
			continue;
		if (!node->slave) {
			struct ksz_hsr_table entry;
			struct ksz_sw *sw = info->sw_dev;

			memcpy(entry.src_mac, node->MacAddressA, ETH_ALEN);
			entry.path_id = 0;
			sw_r_hsr_table(sw, 0, &entry);
			if (entry.start_seq[0]) {
				u16 win[2];

				win[0] = entry.exp_seq[0] - entry.start_seq[0];
				win[1] = entry.exp_seq[1] - entry.start_seq[1];
				if (!win[0] && !win[1] &&
				    info->seq_num != entry.exp_seq[0]) {
					no_drop_win = true;
					info->center = node;
				}
				if (info->center == node) {
					exp_seq[0] = entry.exp_seq[0];
					exp_seq[1] = entry.exp_seq[1];
					start_seq[0] = entry.start_seq[0];
					start_seq[1] = entry.start_seq[1];
				}
			}
			if (no_drop_win)
				break;
		}
	}
	rcu_read_unlock();

	if (info->ring && !no_drop_win) {
		if (info->center) {
			int p;

dbg_msg("%04x:%04x %04x:%04x\n", start_seq[0], start_seq[1],
exp_seq[0], exp_seq[1]);
			if (start_seq[0] == exp_seq[0]) {
				info->p1_lost = 1;
				p = 1;
			} else {
				info->p2_lost = 1;
				p = 0;
			}
			info->seq_num = exp_seq[p];
		}
		info->ring = 0;
		change = 1;
	} else if (!info->ring && no_drop_win) {
		info->ring = 1;
		info->p1_down = info->p2_down =
		info->p1_lost = info->p2_lost = 0;
		change = 1;
	}
	if (change)
		hsr_notify_link_lost(info);
	info->check = 0;
}  /* hsr_chk_ring */
#endif


/* Remove stale sequence_nr records. Called by timer every
 * HSR_LIFE_CHECK_INTERVAL (two seconds or so).
 */
static
void hsr_prune_nodes(unsigned long data)
{
	struct hsr_priv *hsr;
	struct hsr_node *node;
#if 0
	struct hsr_port *port;
#endif
	unsigned long timestamp;
	unsigned long time_a, time_b;

	hsr = (struct hsr_priv *) data;

	rcu_read_lock();
	list_for_each_entry_rcu(node, &hsr->node_db, mac_list) {
		/* Shorthand */
		time_a = node->time_in[HSR_PT_SLAVE_A];
		time_b = node->time_in[HSR_PT_SLAVE_B];

		/* Check for timestamps old enough to risk wrap-around */
		if (time_after(jiffies, time_a + MAX_JIFFY_OFFSET/2))
			node->time_in_stale[HSR_PT_SLAVE_A] = true;
		if (time_after(jiffies, time_b + MAX_JIFFY_OFFSET/2))
			node->time_in_stale[HSR_PT_SLAVE_B] = true;

		/* Get age of newest frame from node.
		 * At least one time_in is OK here; nodes get pruned long
		 * before both time_ins can get stale
		 */
		timestamp = time_a;
		if (node->time_in_stale[HSR_PT_SLAVE_A] ||
		    (!node->time_in_stale[HSR_PT_SLAVE_B] &&
		    time_after(time_b, time_a)))
			timestamp = time_b;

#if 0
		/* Warn of ring error only as long as we get frames at all */
		if (time_is_after_jiffies(timestamp +
					msecs_to_jiffies(1.5*MAX_SLAVE_DIFF))) {
			rcu_read_lock();
			port = get_late_port(hsr, node);
			if (port != NULL)
				hsr_nl_ringerror(hsr, node->MacAddressA, port);
			rcu_read_unlock();
		}
#endif

		if (1 == node->slave && time_is_before_jiffies(timestamp +
			msecs_to_jiffies(HSR_NODE_FORGET_TIME / 4))) {
#if 1
dbg_msg("drop: %02x:%02x:%02x:%02x:%02x:%02x %ld\n",
node->MacAddressA[0],
node->MacAddressA[1],
node->MacAddressA[2],
node->MacAddressA[3],
node->MacAddressA[4],
node->MacAddressA[5],
jiffies - timestamp);
#endif
			node->slave = 2;
		}

		/* Prune old entries */
		if (time_is_before_jiffies(timestamp +
					msecs_to_jiffies(HSR_NODE_FORGET_TIME))) {
			struct ksz_hsr_info *info = container_of(hsr,
				struct ksz_hsr_info, hsr);
			if (!node->slave) {
				proc_hsr_cfg(info, node->MacAddressA, 0);
				info->part_cnt--;
			}

#if 1
dbg_msg("forget: %02x:%02x:%02x:%02x:%02x:%02x %lx %lx %lx; %ld\n",
node->MacAddressA[0],
node->MacAddressA[1],
node->MacAddressA[2],
node->MacAddressA[3],
node->MacAddressA[4],
node->MacAddressA[5],
time_a, time_b, timestamp, jiffies - timestamp);
#endif
			if (node == info->center) {
				info->center = NULL;
				info->seq_num = 0;
				info->ring = 0;
			}
#if 0
			hsr_nl_nodedown(hsr, node->MacAddressA);
#endif
			list_del_rcu(&node->mac_list);
			/* Note that we need to free this entry later: */
			kfree_rcu(node, rcu_head);
		}
	}
	rcu_read_unlock();

	hsr->prune_timer.expires = jiffies + msecs_to_jiffies(PRUNE_PERIOD);
	add_timer(&hsr->prune_timer);
}


#if 0
static
void *hsr_get_next_node(struct hsr_priv *hsr, void *_pos,
			unsigned char addr[ETH_ALEN])
{
	struct hsr_node *node;

	if (!_pos) {
		node = list_first_or_null_rcu(&hsr->node_db,
					      struct hsr_node, mac_list);
		if (node)
			ether_addr_copy(addr, node->MacAddressA);
		return node;
	}

	node = _pos;
	list_for_each_entry_continue_rcu(node, &hsr->node_db, mac_list) {
		ether_addr_copy(addr, node->MacAddressA);
		return node;
	}

	return NULL;
}


static
int hsr_get_node_data(struct hsr_priv *hsr,
		      const unsigned char *addr,
		      unsigned char addr_b[ETH_ALEN],
		      unsigned int *addr_b_ifindex,
		      int *if1_age,
		      u16 *if1_seq,
		      int *if2_age,
		      u16 *if2_seq)
{
	struct hsr_node *node;
	struct hsr_port *port;
	unsigned long tdiff;


	rcu_read_lock();
	node = find_node_by_AddrA(&hsr->node_db, addr);
	if (!node) {
		rcu_read_unlock();
		return -ENOENT;	/* No such entry */
	}

	ether_addr_copy(addr_b, node->MacAddressB);

	tdiff = jiffies - node->time_in[HSR_PT_SLAVE_A];
	if (node->time_in_stale[HSR_PT_SLAVE_A])
		*if1_age = INT_MAX;
#if HZ <= MSEC_PER_SEC
	else if (tdiff > msecs_to_jiffies(INT_MAX))
		*if1_age = INT_MAX;
#endif
	else
		*if1_age = jiffies_to_msecs(tdiff);

	tdiff = jiffies - node->time_in[HSR_PT_SLAVE_B];
	if (node->time_in_stale[HSR_PT_SLAVE_B])
		*if2_age = INT_MAX;
#if HZ <= MSEC_PER_SEC
	else if (tdiff > msecs_to_jiffies(INT_MAX))
		*if2_age = INT_MAX;
#endif
	else
		*if2_age = jiffies_to_msecs(tdiff);

	/* Present sequence numbers as if they were incoming on interface */
	*if1_seq = node->seq_out[HSR_PT_SLAVE_B];
	*if2_seq = node->seq_out[HSR_PT_SLAVE_A];

	if (node->AddrB_port != HSR_PT_NONE) {
		port = hsr_port_get_hsr(hsr, node->AddrB_port);
		*addr_b_ifindex = port->dev->ifindex;
	} else {
		*addr_b_ifindex = -1;
	}

	rcu_read_unlock();

	return 0;
}
#endif

static int hsr_dev_xmit(struct ksz_hsr_info *info, struct net_device *dev,
	struct sk_buff *skb)
{
	int rc;
	const struct net_device_ops *ops = dev->netdev_ops;

	skb->dev = dev;
	rc = ops->ndo_start_xmit(skb, skb->dev);
	if (NETDEV_TX_BUSY == rc) {
		dev_kfree_skb_irq(skb);
	}
	return rc;
}  /* hsr_dev_xmit */

static int hsr_xmit(struct ksz_hsr_info *info)
{
	struct sk_buff *skb;
	u8 *frame = info->tx_frame;
	int len = info->len;

	/* Do not send if network device is not ready. */
	if (!netif_running(info->dev) || !netif_carrier_ok(info->dev))
		return 0;

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
	skb->protocol = htons(ETH_P_PRP);
	return hsr_dev_xmit(info, info->dev, skb);
}  /* hsr_xmit */

static void prep_hsr_supervision_frame(struct ksz_hsr_info *info)
{
	int len;
	int tlen;
	struct hsr_port *master;
	struct hsr_sup_tag *hsr_stag;
	struct hsr_sup_type *hsr_stype;
	struct hsr_sup_payload *hsr_sp;
	struct ethhdr *eth = (struct ethhdr *) info->master_sup_frame;

	master = hsr_port_get_hsr(&info->hsr, HSR_PT_MASTER);

	memcpy(eth->h_dest, master->hsr->sup_multicast_addr, ETH_ALEN);
	memcpy(eth->h_source, info->src_addr, ETH_ALEN);
	eth->h_proto = htons(ETH_P_PRP);
	len = sizeof(struct ethhdr);
	tlen = 60;

	/* Use VLAN. */
	if (info->vid) {
		struct vlan_ethhdr *vlan = (struct vlan_ethhdr *)
			info->master_sup_frame;

		vlan->h_vlan_encapsulated_proto = vlan->h_vlan_proto;
		vlan->h_vlan_TCI = htons(info->vid);
		vlan->h_vlan_proto = htons(ETH_P_8021Q);
		len += VLAN_HLEN;
		tlen += VLAN_HLEN;
	}

	hsr_stag = (struct hsr_sup_tag *) &info->master_sup_frame[len];

	/* Remember the supervision tag location. */
	info->master_hsr_stag = hsr_stag;

	/* HSR tag will be inserted by the standard hsr_fill_tag routine. */
	set_hsr_stag_path(hsr_stag, 0);
	set_hsr_stag_HSR_Ver(hsr_stag, 1);
	len += sizeof(struct hsr_sup_tag);

	hsr_stype = (struct hsr_sup_type *)(hsr_stag + 1);
	hsr_stype->HSR_TLV_Type = HSR_TLV_LIFE_CHECK;
	hsr_stype->HSR_TLV_Length = 6;
	len += sizeof(struct hsr_sup_type);

	/* Payload: MacAddressA */
	hsr_sp = (struct hsr_sup_payload *)(hsr_stype + 1);
	ether_addr_copy(hsr_sp->MacAddressA, info->src_addr);
	len += sizeof(struct hsr_sup_payload);

	/* Last TLV */
	hsr_stype = (struct hsr_sup_type *)(hsr_sp + 1);
	hsr_stype->HSR_TLV_Type = 0;
	hsr_stype->HSR_TLV_Length = 0;
	len += sizeof(struct hsr_sup_type);
	if (len < tlen) {
		memset(&info->master_sup_frame[len], 0, tlen - len);
		len = tlen;
	}
	info->master_len = len;
}  /* prep_hsr_supervision_frame */

static void prep_hsr_supervision_slave_frame(struct ksz_hsr_info *info)
{
	int len;
	int tlen;
	struct hsr_port *master;
	struct hsr_sup_tag *hsr_stag;
	struct hsr_sup_type *hsr_stype;
	struct hsr_sup_payload *hsr_sp;
	struct ethhdr *eth = (struct ethhdr *) info->slave_sup_frame;

	master = hsr_port_get_hsr(&info->hsr, HSR_PT_MASTER);

	memcpy(eth->h_dest, master->hsr->sup_multicast_addr, ETH_ALEN);
	memcpy(eth->h_source, info->src_addr, ETH_ALEN);
	eth->h_proto = htons(ETH_P_PRP);
	len = sizeof(struct ethhdr);
	tlen = 60;

	/* Use VLAN. */
	if (info->vid) {
		struct vlan_ethhdr *vlan = (struct vlan_ethhdr *)
			info->slave_sup_frame;

		vlan->h_vlan_encapsulated_proto = vlan->h_vlan_proto;
		vlan->h_vlan_TCI = htons(info->vid);
		vlan->h_vlan_proto = htons(ETH_P_8021Q);
		len += VLAN_HLEN;
		tlen += VLAN_HLEN;
	}

	hsr_stag = (struct hsr_sup_tag *) &info->slave_sup_frame[len];

	/* Remember the supervision tag location. */
	info->slave_hsr_stag = hsr_stag;

	/* HSR tag will be inserted by the standard hsr_fill_tag routine. */
	set_hsr_stag_path(hsr_stag, 0);
	set_hsr_stag_HSR_Ver(hsr_stag, 1);
	len += sizeof(struct hsr_sup_tag);

	hsr_stype = (struct hsr_sup_type *)(hsr_stag + 1);
	hsr_stype->HSR_TLV_Type = HSR_TLV_LIFE_CHECK;
	hsr_stype->HSR_TLV_Length = 6;
	len += sizeof(struct hsr_sup_type);

	/* Payload: MacAddressA */
	hsr_sp = (struct hsr_sup_payload *)(hsr_stype + 1);
	len += sizeof(struct hsr_sup_payload);

	/* Insert RedBox MAC address if available. */
	hsr_stype = (struct hsr_sup_type *)(hsr_sp + 1);
	hsr_stype->HSR_TLV_Type = HSR_TLV_REDBOX;
	hsr_stype->HSR_TLV_Length = 6;
	len += sizeof(struct hsr_sup_type);

	hsr_sp = (struct hsr_sup_payload *)(hsr_stype + 1);
	ether_addr_copy(hsr_sp->MacAddressA, info->redbox->dev_addr);

	/* Cannot have different source MAC address. */
	ether_addr_copy(hsr_sp->MacAddressA, info->src_addr);
	len += sizeof(struct hsr_sup_payload);

	/* Last TLV */
	hsr_stype = (struct hsr_sup_type *)(hsr_sp + 1);
	hsr_stype->HSR_TLV_Type = 0;
	hsr_stype->HSR_TLV_Length = 0;
	len += sizeof(struct hsr_sup_type);
	if (len < tlen) {
		memset(&info->slave_sup_frame[len], 0, tlen - len);
		len = tlen;
	}
	info->slave_len = len;
}  /* prep_hsr_supervision_slave_frame */

static void send_hsr_supervision_frame(struct hsr_port *master)
{
	struct ksz_hsr_info *info = container_of(master->hsr,
		struct ksz_hsr_info, hsr);
	struct hsr_sup_tag *hsr_stag = info->hsr_stag;

	hsr_stag->sequence_nr = htons(master->hsr->sup_sequence_nr);
	master->hsr->sup_sequence_nr++;

	hsr_xmit(info);
}

/* Announce (supervision frame) timer function
 */
static void hsr_announce(unsigned long data)
{
	struct hsr_priv *hsr;
	struct hsr_port *master;
	struct ksz_hsr_info *info;
	struct hsr_node *node;

	hsr = (struct hsr_priv *) data;
	info = container_of(hsr, struct ksz_hsr_info, hsr);

	master = hsr_port_get_hsr(hsr, HSR_PT_MASTER);

	info->tx_frame = info->master_sup_frame;
	info->len = info->master_len;
	info->hsr_stag = info->master_hsr_stag;
	send_hsr_supervision_frame(master);

	info->tx_frame = info->slave_sup_frame;
	info->len = info->slave_len;
	info->hsr_stag = info->slave_hsr_stag;
	list_for_each_entry_rcu(node, &hsr->node_db, mac_list) {
		struct hsr_sup_type *hsr_stype;
		struct hsr_sup_payload *hsr_sp;
		struct hsr_sup_tag *hsr_stag = info->slave_hsr_stag;
		struct vlan_ethhdr *vlan = (struct vlan_ethhdr *)
			info->slave_sup_frame;

		if (1 != node->slave)
			continue;

		/*
		 * Cannot use different source MAC address because
		 * self-address filtering is used to drop frames sent by self.
		 */
		memcpy(vlan->h_source, node->MacAddressA, ETH_ALEN);
		memcpy(vlan->h_source, info->src_addr, ETH_ALEN);

		hsr_stype = (struct hsr_sup_type *)(hsr_stag + 1);
		hsr_sp = (struct hsr_sup_payload *)(hsr_stype + 1);
		ether_addr_copy(hsr_sp->MacAddressA, node->MacAddressA);
		send_hsr_supervision_frame(master);
	}

	hsr->announce_timer.expires = jiffies +
		msecs_to_jiffies(HSR_LIFE_CHECK_INTERVAL);

	if (netif_running(master->dev) && netif_carrier_ok(master->dev))
		add_timer(&hsr->announce_timer);
}


/* The uses I can see for these HSR supervision frames are:
 * 1) Use the frames that are sent after node initialization ("HSR_TLV.Type =
 *    22") to reset any sequence_nr counters belonging to that node. Useful if
 *    the other node's counter has been reset for some reason.
 *    --
 *    Or not - resetting the counter and bridging the frame would create a
 *    loop, unfortunately.
 *
 * 2) Use the LifeCheck frames to detect ring breaks. I.e. if no LifeCheck
 *    frame is received from a particular node, we know something is wrong.
 *    We just register these (as with normal frames) and throw them away.
 *
 * 3) Allow different MAC addresses for the two slave interfaces, using the
 *    MacAddressA field.
 */
static bool is_supervision_frame(struct hsr_priv *hsr, struct sk_buff *skb)
{
	struct hsr_ethhdr_sp *hdr;

	hdr = (struct hsr_ethhdr_sp *) skb_mac_header(skb);

	if (!ether_addr_equal(hdr->ethhdr.h_dest,
			      hsr->sup_multicast_addr))
		return false;

	/* Sent internally with VLAN tag. */
	if (hdr->ethhdr.h_proto == htons(ETH_P_8021Q))
		hdr = (struct hsr_ethhdr_sp *)((u8 *) hdr + VLAN_HLEN);

	/* Received from outside with HSR tag. */
	if (hdr->ethhdr.h_proto == htons(ETH_P_HSR))
		hdr = (struct hsr_ethhdr_sp *)((u8 *) hdr + HSR_HLEN);
	if (get_hsr_stag_HSR_ver(&hdr->hsr_sup) < 1)
		return false;
	if (hdr->sup_type.HSR_TLV_Type != HSR_TLV_LIFE_CHECK)
		return false;
	if (hdr->sup_type.HSR_TLV_Length != 6)
		return false;

	return true;
}

static struct sk_buff *create_stripped_skb(struct sk_buff *skb,
					   struct hsr_frame_info *frame)
{
	int copylen;
	unsigned char *dst, *src;

	copylen = 2 * ETH_ALEN;
	if (frame->is_vlan)
		copylen += VLAN_HLEN;

	src = skb->data;
	dst = skb_pull(skb, HSR_HLEN);
	memmove(dst, src, copylen);
	skb_reset_mac_header(skb);

	/* Move HSR frame to non-HSR frame. */
	frame->skb_std = skb;
	frame->skb_hsr = NULL;

	return skb;
}

static struct sk_buff *frame_get_stripped_skb(struct hsr_frame_info *frame,
					      struct hsr_port *port)
{
	if (!frame->skb_std)
		frame->skb_std = create_stripped_skb(frame->skb_hsr, frame);
	return frame->skb_std;
}

static void hsr_fill_tag(struct sk_buff *skb, struct hsr_frame_info *frame,
			 struct hsr_port *port)
{
	int lane_id;
	int lsdu_size;

	if (hsr_addr_is_self(port->hsr, &skb->data[6]))
		lane_id = port->hsr->net_id;
	else
		lane_id = port->hsr->redbox_id;
	lane_id <<= 1;

	lsdu_size = skb->len - 14;

	if (lsdu_size < 60 - 14)
		lsdu_size = 60 - 14;
	if (frame->is_vlan)
		lsdu_size -= 4;

	set_hsr_tag_path(frame->hsr_tag, lane_id);
	set_hsr_tag_LSDU_size(frame->hsr_tag, lsdu_size);
	frame->hsr_tag->sequence_nr = htons(frame->sequence_nr);
	*frame->proto = htons(ETH_P_HSR);
}

static struct sk_buff *create_tagged_skb(struct sk_buff *skb,
					 struct hsr_frame_info *frame,
					 struct hsr_port *port)
{
	int movelen;
	unsigned char *dst, *src;

	movelen = 2 * ETH_ALEN;
	if (frame->is_vlan)
		movelen += VLAN_HLEN;

	src = skb_mac_header(skb);
	dst = skb_push(skb, HSR_HLEN);
	memmove(dst, src, movelen);
	skb_reset_mac_header(skb);

	hsr_fill_tag(skb, frame, port);

	/* Move non-HSR frame to HSR frame. */
	frame->skb_hsr = skb;
	frame->skb_std = NULL;

	return skb;
}

/* If the original frame was an HSR tagged frame, just clone it to be sent
 * unchanged. Otherwise, create a private frame especially tagged for 'port'.
 */
static struct sk_buff *frame_get_tagged_skb(struct hsr_frame_info *frame,
					    struct hsr_port *port)
{
	if (frame->skb_hsr)
		return frame->skb_hsr;

	return create_tagged_skb(frame->skb_std, frame, port);
}

/* Forward the frame through all devices except:
 * - Back through the receiving device
 * - If it's a HSR frame: through a device where it has passed before
 * - To the local HSR master only if the frame is directly addressed to it, or
 *   a non-supervision multicast or broadcast frame.
 *
 * HSR slave devices should insert a HSR tag into the frame, or forward the
 * frame unchanged if it's already tagged. Interlink devices should strip HSR
 * tags if they're of the non-HSR type (but only after duplicate discard). The
 * master device always strips HSR tags.
 */
static void hsr_forward_do(struct hsr_frame_info *frame)
{
	struct hsr_port *from;
	struct hsr_port *other;
	struct hsr_port *port;
	struct sk_buff *skb;
	struct ksz_hsr_info *info;

	from = frame->port_rcv;

	/* Coming from host. */
	if (from->type == HSR_PT_MASTER) {
		port = hsr_port_get_hsr(from->hsr, HSR_PT_SLAVE_A);
		other = hsr_port_get_hsr(from->hsr, HSR_PT_SLAVE_B);

#if 0
		/* Deliver frames directly addressed to us to master only */
		if (frame->is_local_exclusive)
{
#if 1
dbg_msg("local only: %d\n", port->type);
#endif
			goto tx_drop;
}
#endif

		/* Don't send frame over port where it has been sent before */
		if (hsr_register_frame_out(port, frame->node_src,
					   frame->sequence_nr))
		{
#if 1
dbg_msg("saw before: %d %04x %d\n", port->type, frame->sequence_nr,
frame->is_supervision);
#endif

			goto tx_drop;
		}
		hsr_update_frame_out(other, frame->node_src,
			frame->sequence_nr);

		/* Simulate incoming frame so that node is not removed. */
		if (frame->is_supervision && !frame->node_src->slave) {
			hsr_register_frame_in(frame->node_src, port,
				frame->sequence_nr);
		}

		skb = frame_get_tagged_skb(frame, port);
		skb->protocol = htons(ETH_P_HSR);
		return;
	} else {
		int forward;
		u16 path_id;

		port = hsr_port_get_hsr(from->hsr, HSR_PT_MASTER);
		if (from->type == HSR_PT_SLAVE_A)
			other = hsr_port_get_hsr(from->hsr, HSR_PT_SLAVE_B);
		else
			other = hsr_port_get_hsr(from->hsr, HSR_PT_SLAVE_A);

		if (hsr_addr_is_self(port->hsr,
		    eth_hdr(frame->skb_hsr)->h_source)) {
if (dbg_hsr < 10)
dbg_msg(" S ");
++dbg_hsr;
			goto rx_drop;
		}

		/* Don't deliver locally unless we should */
		if (!frame->is_local_dest)
{
dbg_msg("not local: %d\n", port->type);
			goto rx_drop;
}

		/* Don't send frame over port where it has been sent before */
		if (hsr_register_frame_out(port, frame->node_src,
					   frame->sequence_nr))
		{
#if 1
if (dbg_hsr < 10) {
	if (hsr_addr_is_self(port->hsr, eth_hdr(frame->skb_hsr)->h_source))
dbg_msg(" self ");
dbg_msg("saw before: %d %d %04x %d\n", from->type, port->type, frame->sequence_nr,
frame->is_supervision);
}
++dbg_hsr;
#endif

			goto rx_drop;
		}
if (hsr_addr_is_self(port->hsr, eth_hdr(frame->skb_hsr)->h_source)) {
if (dbg_hsr < 10)
dbg_msg(" S ");
}
		info = container_of(from->hsr, struct ksz_hsr_info, hsr);

		hsr_update_frame_out(other, frame->node_src,
			frame->sequence_nr);
		if (frame->is_supervision) {
			hsr_handle_sup_frame(frame->skb_hsr,
					     frame->node_src,
					     frame->port_rcv);

#ifdef CONFIG_HAVE_HSR_HW
			if (!info->check) {
				info->check = 1;
				schedule_delayed_work(&info->chk_ring, 5);
			}
#endif
			goto rx_drop;
		}

		/* Get the path id before the HSR tag is removed. */
		path_id = get_hsr_tag_path(frame->hsr_tag);

		skb = frame_get_stripped_skb(frame, port);
		hsr_addr_subst_source(frame->node_src, skb);

		if (!info->redbox)
			return;
		do {
			struct ksz_sw *sw = info->sw_dev;

			if (sw->info->forward & FWD_UCAST)
				forward = 1;
			else if (sw->info->forward & FWD_MCAST)
				forward = 2;
			else
				forward = 0;
		} while (0);
#if 0
#if 1
		if (forward && (path_id >> 1) == info->hsr.redbox_id)
			forward = 0;
#endif
#ifdef CONFIG_1588_PTP_
		/* Do not forward PTP messages. */
		if (forward) {
			struct ksz_sw *sw = info->sw_dev;

			if (sw->tag.ports & 0x80)
				forward = 0;
		}
#endif
		if (forward) {
			struct sk_buff *new_skb;

			if (1 == forward) {
				new_skb = skb;
				frame->skb_std = NULL;
				frame->skb_hsr = NULL;
			} else {
				new_skb = skb_copy(skb, GFP_ATOMIC);
			}
			if (new_skb)
				hsr_dev_xmit(info, info->redbox, new_skb);
		}
#endif
		return;

	}
tx_drop:
	if (frame->skb_std) {
		kfree_skb(frame->skb_std);
		frame->skb_std = NULL;
	}

rx_drop:
	if (frame->skb_hsr) {
		kfree_skb(frame->skb_hsr);
		frame->skb_hsr = NULL;
	}
}

static void check_local_dest(struct hsr_priv *hsr, struct sk_buff *skb,
			     struct hsr_frame_info *frame)
{
	if (hsr_addr_is_self(hsr, eth_hdr(skb)->h_dest)) {
		frame->is_local_exclusive = true;
		skb->pkt_type = PACKET_HOST;
	} else {
		frame->is_local_exclusive = false;
	}

	if ((skb->pkt_type == PACKET_HOST) ||
	    (skb->data[0] & 0x01)) {
		frame->is_local_dest = true;
	} else {
dbg_msg("not local_dest\n");
		frame->is_local_dest = false;
	}
}

static int hsr_fill_frame_info(struct hsr_frame_info *frame,
			       struct sk_buff *skb, struct hsr_port *port)
{
	unsigned long irqflags;

	frame->is_supervision = is_supervision_frame(port->hsr, skb);
	frame->node_src = hsr_get_node(&port->hsr->node_db, skb,
				       frame->is_supervision);
	if (frame->node_src == NULL)
		return -1; /* Unknown node and !is_supervision, or no mem */

	/* Most likely this is a received frame. */
	if (*frame->proto == htons(ETH_P_HSR)) {
		frame->skb_std = NULL;
		frame->skb_hsr = skb;
		frame->sequence_nr = hsr_get_skb_sequence_nr(skb);

	/* Received frame without HSR tag will not come here. */
	} else {
		frame->skb_std = skb;
		frame->skb_hsr = NULL;
		/* Sequence nr for the master node */
		spin_lock_irqsave(&port->hsr->seqnr_lock, irqflags);
		frame->sequence_nr = port->hsr->sequence_nr;
		port->hsr->sequence_nr++;
		spin_unlock_irqrestore(&port->hsr->seqnr_lock, irqflags);
	}

	frame->port_rcv = port;
#if 1
	if (port->type != HSR_PT_MASTER)
		check_local_dest(port->hsr, skb, frame);
#endif

	return 0;
}

static
int hsr_forward_skb(struct sk_buff *skb, struct hsr_port *port)
{
	struct hsr_frame_info _frame;
	struct hsr_frame_info *frame = &_frame;

	skb_reset_mac_header(skb);

	/* Coming from host. */
	if (port->type == HSR_PT_MASTER) {
		struct vlan_ethhdr *vlan = (struct vlan_ethhdr *) skb->data;
		u8 *proto;
		u8 *hsr_tag;

		memset(frame, 0, sizeof(struct hsr_frame_info));
		proto = (u8 *) &vlan->h_vlan_proto;
		hsr_tag = (u8 *) &vlan->h_vlan_TCI;
		if (vlan->h_vlan_proto == htons(ETH_P_8021Q)) {
			frame->is_vlan = true;
			proto = (u8 *) &vlan->h_vlan_encapsulated_proto;
			hsr_tag = (u8 *)(vlan + 1);
		}
		proto -= HSR_HLEN;
		hsr_tag -= HSR_HLEN;
		frame->proto = (u16 *) proto;
		frame->hsr_tag = (struct hsr_tag *) hsr_tag;
	} else {
		struct ksz_hsr_info *info = container_of(port->hsr,
			struct ksz_hsr_info, hsr);

		frame = &info->frame;
	}
	if (hsr_fill_frame_info(frame, skb, port) < 0)
		goto out_drop;
	hsr_register_frame_in(frame->node_src, port, frame->sequence_nr);
	hsr_forward_do(frame);

	/* Frame is supervision or was dropped. */
	if (!frame->skb_hsr && !frame->skb_std)
{
#if 0
if (!frame->is_supervision)
dbg_msg(" d ");
#endif
		return 0;
}

	/* Pass to upper layer or down. */
	return 1;

out_drop:
dbg_msg("fwd drop: %02x:%02x:%02x:%02x:%02x:%02x  %02x:%02x:%02x:%02x:%02x:%02x\n",
skb->data[0],
skb->data[1],
skb->data[2],
skb->data[3],
skb->data[4],
skb->data[5],
skb->data[6],
skb->data[7],
skb->data[8],
skb->data[9],
skb->data[10],
skb->data[11]);
#if 0
	port->dev->stats.tx_dropped++;
#endif
	kfree_skb(skb);
	return 0;
}

static void *check_hsr_frame(u8 *data, struct hsr_frame_info *frame)
{
	struct vlan_ethhdr *vlan = (struct vlan_ethhdr *) data;

	frame->is_vlan = false;
	if (vlan->h_vlan_proto == htons(ETH_P_8021Q)) {
		frame->is_vlan = true;
		frame->proto = &vlan->h_vlan_encapsulated_proto;
		frame->hsr_tag = (struct hsr_tag *)(vlan + 1);
		if (vlan->h_vlan_encapsulated_proto == htons(ETH_P_HSR))
			return vlan + 1;
	}

	/* VLAN tag can be removed by the switch. */
	if (vlan->h_vlan_proto == htons(ETH_P_HSR)) {
		struct ethhdr *eth = (struct ethhdr *) data;

		frame->proto = &vlan->h_vlan_proto;
		frame->hsr_tag = (struct hsr_tag *)(eth + 1);
		return eth + 1;
	}
	return NULL;
}  /* check_hsr_frame */

static int hsr_chk(struct ksz_hsr_info *info, struct sk_buff *skb, int port)
{
#if 0 
	struct sk_buff *new_skb;
#endif
	struct hsr_node *node;
	struct list_head *node_db;
	int forward;
	struct vlan_ethhdr *vlan = (struct vlan_ethhdr *) skb->data;
	int ret = 2;
	struct ksz_sw *sw = info->sw_dev;

	if (!info->redbox)
		return ret;

	/* Stop processing if coming from HSR ports. */
	if (port == info->ports[0] || port == info->ports[1])
		return ret;

	if (sw->info->forward & FWD_UCAST)
		forward = 1;
	else if (sw->info->forward & FWD_MCAST)
		forward = 2;
	else
		forward = 0;
	if (!forward)
		return ret;

	node_db = &info->hsr.node_db;
	node = find_node_by_AddrA(node_db, vlan->h_source);
	if (!node) {
		struct hsr_sup_type *hsr_stype;
		struct hsr_sup_payload *hsr_sp;
		struct hsr_sup_tag *hsr_stag = info->slave_hsr_stag;
		struct hsr_port *master = hsr_port_get_hsr(&info->hsr,
			HSR_PT_MASTER);

		node = hsr_add_slave(node_db, vlan->h_source,
			info->hsr.sequence_nr - 1);
		if (!node)
			return ret;

		info->tx_frame = info->slave_sup_frame;
		info->len = info->slave_len;
		info->hsr_stag = info->slave_hsr_stag;

		vlan = (struct vlan_ethhdr *) info->slave_sup_frame;

		/*
		 * Cannot use different source MAC address because
		 * self-address filtering is used to drop frames sent by self.
		 */
		memcpy(vlan->h_source, node->MacAddressA, ETH_ALEN);
		memcpy(vlan->h_source, info->src_addr, ETH_ALEN);

		hsr_stype = (struct hsr_sup_type *)(hsr_stag + 1);
		hsr_sp = (struct hsr_sup_payload *)(hsr_stype + 1);
		ether_addr_copy(hsr_sp->MacAddressA, node->MacAddressA);
		send_hsr_supervision_frame(master);
	} else {
		node->slave = 1;
		node->time_in[HSR_PT_SLAVE_A] = jiffies;
		node->time_in_stale[HSR_PT_SLAVE_A] = false;
	}
#if 0
	if (1 == forward) {
		new_skb = skb;
		ret = 0;
	} else {
		new_skb = skb_copy(skb, GFP_ATOMIC);
		if (!new_skb)
			return ret;
	}

	/* Replace source MAC address. */
	memcpy(&new_skb->data[6], info->src_addr, ETH_ALEN);

	/* Send frame to HSR device. */
	hsr_dev_xmit(info, info->dev, new_skb);
#endif
	return ret;
}  /* hsr_chk */

static int hsr_rcv(struct ksz_hsr_info *info, struct sk_buff *skb, int port)
{
	/* Accept only from port 1 or 2. */
	if (port == info->ports[0])
		port = 0;
	else if (port == info->ports[1])
		port = 1;
	if (port > 1)
		return 2;
	if(check_hsr_frame(skb->data, &info->frame)) {
		enum hsr_port_type pt;
		struct hsr_port *from;

		if (1 == port)
			pt = HSR_PT_SLAVE_B;
		else
			pt = HSR_PT_SLAVE_A;
		from = hsr_port_get_hsr(&info->hsr, pt);
		return hsr_forward_skb(skb, from);
	}
	return 2;
}  /* hsr_rcv */

static
void hsr_add_port(struct hsr_priv *hsr, struct net_device *dev,
	enum hsr_port_type type)
{
	struct hsr_port *port;

	port = hsr_port_get_hsr(hsr, type);

	port->hsr = hsr;
	port->dev = dev;
	port->type = type;
}

/* Default multicast address for HSR Supervision frames */
static const unsigned char def_multicast_addr[ETH_ALEN] __aligned(2) = {
	0x01, 0x15, 0x4e, 0x00, 0x01, 0x00
};

static void prep_hsr_addr(struct ksz_hsr_info *info, u8 *src)
{
	struct hsr_sup_type *hsr_stype;
	struct hsr_sup_payload *hsr_sp;
	struct vlan_ethhdr *vlan = (struct vlan_ethhdr *)
		info->master_sup_frame;

	memcpy(info->src_addr, src, ETH_ALEN);

	memcpy(vlan->h_source, src, ETH_ALEN);
	hsr_stype = (struct hsr_sup_type *)(info->master_hsr_stag + 1);
	hsr_sp = (struct hsr_sup_payload *)(hsr_stype + 1);
	ether_addr_copy(hsr_sp->MacAddressA, info->src_addr);
}  /* prep_hsr_addr */

static void prep_hsr_redbox_addr(struct ksz_hsr_info *info)
{
	struct hsr_sup_type *hsr_stype;
	struct hsr_sup_payload *hsr_sp;

	if (!info->redbox)
		return;
	hsr_stype = (struct hsr_sup_type *)(info->slave_hsr_stag + 1);
	hsr_sp = (struct hsr_sup_payload *)(hsr_stype + 1);
	hsr_stype = (struct hsr_sup_type *)(hsr_sp + 1);
	hsr_sp = (struct hsr_sup_payload *)(hsr_stype + 1);
	ether_addr_copy(hsr_sp->MacAddressA, info->redbox->dev_addr);
	ether_addr_copy(hsr_sp->MacAddressA, info->src_addr);
}  /* prep_hsr_redbox_addr */

static void hsr_change_addr(struct ksz_hsr_info *info, struct net_device *dev)
{
	struct ksz_sw *sw = info->sw_dev;

	/* Do not do anything if device is not ready. */
	if (!info->dev || !netif_running(dev))
		return;
	if (info->dev == dev) {
		if (!memcmp(info->src_addr, dev->dev_addr, ETH_ALEN))
			return;
		sw->ops->cfg_mac(sw, BRIDGE_ADDR_ENTRY, info->src_addr, 0,
			false, false, 0);
		if (sw->eth_cnt > 1) {
			sw->ops->cfg_mac(sw, DEV_0_ADDR_ENTRY, info->src_addr,
				0, false, false, sw->eth_maps[0].vlan);
			sw->ops->cfg_mac(sw, DEV_1_ADDR_ENTRY, info->src_addr,
				0, false, false, sw->eth_maps[1].vlan);
		}
		prep_hsr_addr(info, dev->dev_addr);
		sw->ops->cfg_mac(sw, BRIDGE_ADDR_ENTRY, info->src_addr,
			sw->HOST_MASK, false, false, 0);
		if (sw->eth_cnt > 1) {
			sw->ops->cfg_mac(sw, DEV_0_ADDR_ENTRY, info->src_addr,
				sw->HOST_MASK, false, false,
				sw->eth_maps[0].vlan);
			sw->ops->cfg_mac(sw, DEV_1_ADDR_ENTRY, info->src_addr,
				sw->HOST_MASK, false, false,
				sw->eth_maps[1].vlan);
		}
	} else {
		prep_hsr_redbox_addr(info);
	}
}  /* hsr_change_addr */

static void hsr_link_change(struct ksz_hsr_info *info, int link1, int link2)
{
	info->p1_down = !link1;
	info->p2_down = !link2;
	if (info->ring && (info->p1_down || info->p2_down)) {
		info->ring = 0;
		hsr_notify_link_lost(info);
	}
}  /* hsr_link_change */

static u8 hsr_get_redbox_id(struct ksz_hsr_info *info)
{
	return info->hsr.redbox_id;
}  /* hsr_get_redbox_id */

static void hsr_set_redbox_id(struct ksz_hsr_info *info, u8 id)
{
	info->hsr.redbox_id = id;
}  /* hsr_set_redbox_id */

static u8 hsr_get_net_id(struct ksz_hsr_info *info)
{
	return info->hsr.net_id;
}  /* hsr_get_net_id */

static void hsr_set_net_id(struct ksz_hsr_info *info, u8 id)
{
	info->hsr.net_id = id;
}  /* hsr_set_net_id */

static void prep_hsr_mcast(struct net_device *dev)
{
	char addr[MAX_ADDR_LEN];

	memcpy(addr, def_multicast_addr, ETH_ALEN);
	dev_mc_add(dev, addr);
}  /* prep_hsr_mcast */

static void hsr_check_announce(struct ksz_hsr_info *info)
{
	int state;
	struct hsr_priv *hsr = &info->hsr;

	if (info->state < 0)
		return;
	state = netif_running(info->dev) && netif_carrier_ok(info->dev);
	if (state != info->state) {
dbg_msg("%s %d %d\n", __func__, info->state, state);
		if (state) {
			hsr->announce_timer.expires = jiffies +
				msecs_to_jiffies(1);
			add_timer(&hsr->announce_timer);
		} else
			del_timer(&hsr->announce_timer);
		info->state = state;
	}
}

static void hsr_dev_init(struct ksz_hsr_info *info)
{
	struct hsr_priv *hsr = &info->hsr;

	INIT_LIST_HEAD(&hsr->node_db);
	INIT_LIST_HEAD(&hsr->self_node_db);

	spin_lock_init(&hsr->seqnr_lock);

	init_timer(&hsr->announce_timer);
	hsr->announce_timer.function = hsr_announce;
	hsr->announce_timer.data = (unsigned long) hsr;

	init_timer(&hsr->prune_timer);
	hsr->prune_timer.function = hsr_prune_nodes;
	hsr->prune_timer.data = (unsigned long) hsr;

	ether_addr_copy(hsr->sup_multicast_addr, def_multicast_addr);
	hsr->sup_multicast_addr[ETH_ALEN - 1] = 0;

	hsr_add_port(hsr, info->dev, HSR_PT_MASTER);

	hsr_add_port(hsr, info->dev, HSR_PT_SLAVE_A);
	hsr_add_port(hsr, info->dev, HSR_PT_SLAVE_B);

	info->state = -1;
}

static int hsr_dev_finalize(struct ksz_hsr_info *info)
{
	struct hsr_priv *hsr = &info->hsr;
	int res;

	res = hsr_create_self_node(&hsr->self_node_db, info->dev->dev_addr,
				   info->dev->dev_addr);
	if (res < 0)
		return res;

	/* Overflow soon to find bugs easier: */
	hsr->sequence_nr = HSR_SEQNR_START;
	hsr->sup_sequence_nr = HSR_SEQNR_START;
	hsr->redbox_id = 7;
	hsr->net_id = 0;

#if 1
	msleep(HSR_NODE_REBOOT_INTERVAL);
#endif
	/* Ready for announcement. */
	info->state = 0;
	hsr_check_announce(info);

	hsr->prune_timer.expires = jiffies + msecs_to_jiffies(PRUNE_PERIOD);
	add_timer(&hsr->prune_timer);

	return 0;
}

static void hsr_dev_destroy(struct ksz_hsr_info *info)
{
	struct hsr_priv *hsr = &info->hsr;
	struct hsr_node *node;

	node = list_first_or_null_rcu(&hsr->self_node_db, struct hsr_node,
				      mac_list);
	if (node) {
		list_del_rcu(&node->mac_list);
		kfree_rcu(node, rcu_head);
	}
	list_for_each_entry_rcu(node, &hsr->node_db, mac_list) {
		list_del_rcu(&node->mac_list);
		kfree_rcu(node, rcu_head);
	}
	del_timer_sync(&hsr->prune_timer);
	del_timer_sync(&hsr->announce_timer);
	info->state = -1;
}

static void setup_hsr(struct ksz_hsr_info *info, struct net_device *dev)
{
	info->dev = dev;
	info->vid = 0;

	hsr_dev_init(info);
	prep_hsr_supervision_frame(info);
	info->tx_frame = info->master_sup_frame;
	info->len = info->master_len;
	info->hsr_stag = info->master_hsr_stag;
	prep_hsr_mcast(dev);
}  /* setup_hsr */

static void setup_hsr_redbox(struct ksz_hsr_info *info, struct net_device *dev)
{
	info->redbox = dev;
	prep_hsr_supervision_slave_frame(info);
}  /* setup_hsr_redbox */

static int hsr_get_attrib(struct ksz_hsr_info *info, int subcmd, int size,
	int *req_size, size_t *len, u8 *data, int *output)
{
	struct hsr_node *node;
	struct ksz_hsr_node *active;
	struct hsr_priv *hsr = &info->hsr;
	union hsr_data *attrib = (union hsr_data *) data;

	*len = 0;
	*output = 0;
	switch (subcmd) {
	case HSR_GET_NETWORK_STATUS:
		*len = 1;
		attrib->byte = info->ring;
		break;
	case HSR_GET_CAPABILITY_FLAGS:
		*len = 4;
		attrib->dword = info->cap;
		break;
	case HSR_GET_RING_PARTICIPANTS_COUNT:
		*len = 2;
		attrib->word = info->part_cnt;
		break;
	case HSR_GET_RING_PARTICIPANTS_LIST:
		*len = sizeof(struct ksz_hsr_node);
		*len *= info->part_cnt;
		if (size < *len) {
			break;
		}
		active = (struct ksz_hsr_node *) data;
		rcu_read_lock();
		list_for_each_entry_rcu(node, &hsr->node_db, mac_list) {
			if (!node->slave) {
				memcpy(&active->addr, node->MacAddressA,
					ETH_ALEN);
				active++;
			}
		}
		rcu_read_unlock();
		break;
	}
	if (!*len)
		return DEV_IOC_INVALID_CMD;
	if (size < *len) {
		*req_size = *len + SIZEOF_ksz_request;
		return DEV_IOC_INVALID_LEN;
	}
	return DEV_IOC_OK;
}  /* hsr_get_attrib */

static int hsr_dev_req(struct ksz_hsr_info *hsr, char *arg, void *info)
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
				data[5] = hsr->member;
				err = write_user_data(data, req->param.data,
					6, info);
				if (err)
					goto dev_ioctl_done;
				hsr->dev_info = info;
			} else
				result = DEV_IOC_INVALID_LEN;
			break;
		case DEV_INFO_EXIT:

		/* fall through */
		case DEV_INFO_QUIT:

			/* Not called through char device. */
			if (!info)
				break;
			msg->module = DEV_MOD_HSR;
			msg->cmd = DEV_INFO_QUIT;
			msg->resp.data[0] = 0;
			sw_setup_msg(info, msg, 8, NULL, NULL);
			hsr->notifications = 0;
			hsr->dev_info = NULL;
			break;
		case DEV_INFO_NOTIFY:
			if (len >= 4) {
				uint *notify = (uint *) data;

				_chk_ioctl_size(len, 4, 0, &req_size, &result,
					&req->param, data, info);
				hsr->notifications = *notify;
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
#if 0
		result = hsr_set_attrib(hsr, subcmd, len, &req_size, data,
			&output);
		if (result)
			goto dev_ioctl_resp;
#endif
		put_user_data(&output, &req->output, info);
		break;
	case DEV_CMD_GET:
		result = hsr_get_attrib(hsr, subcmd, len, &req_size,
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
}  /* hsr_dev_req */

static struct hsr_ops hsr_ops = {
	.change_addr		= hsr_change_addr,
	.link_change		= hsr_link_change,
	.check_announce		= hsr_check_announce,
	.get_redbox_id		= hsr_get_redbox_id,
	.set_redbox_id		= hsr_set_redbox_id,
	.get_net_id		= hsr_get_net_id,
	.set_net_id		= hsr_set_net_id,

	.dev_req		= hsr_dev_req,
};

static void prep_hsr(struct ksz_hsr_info *info, struct net_device *dev,
	u8 *src)
{
	info->dev = dev;
	info->center = NULL;
	info->seq_num = 0;
	info->ring = 0;
	prep_hsr_addr(info, src);
	prep_hsr_redbox_addr(info);
	if (info->vid) {
		struct vlan_ethhdr *vlan = (struct vlan_ethhdr *)
			info->master_sup_frame;

		vlan->h_vlan_TCI = htons(info->vid);
		vlan = (struct vlan_ethhdr *) info->slave_sup_frame;
		vlan->h_vlan_TCI = htons(info->vid);
	}
	do {
		struct ksz_sw *sw = info->sw_dev;

		sw->ops->cfg_mac(sw, BRIDGE_ADDR_ENTRY, info->src_addr,
			sw->HOST_MASK, false, false, 0);
		if (sw->eth_cnt > 1) {
			sw->ops->cfg_mac(sw, DEV_0_ADDR_ENTRY, info->src_addr,
				sw->HOST_MASK, false, false,
				sw->eth_maps[0].vlan);
			sw->ops->cfg_mac(sw, DEV_1_ADDR_ENTRY, info->src_addr,
				sw->HOST_MASK, false, false,
				sw->eth_maps[1].vlan);
		}
	} while (0);
	hsr_dev_finalize(info);
}  /* prep_hsr */

static void sw_setup_hsr(struct ksz_sw *sw)
{
/*
 * THa  2015/12/06
 * The HSR register 0x640 needs to be set, even though the value read is 3.
 * The NODE_UNICAST bit in register 0x644 needs to be turned off for multicast
 * address to work.
 * If HSR_LEARN_UCAST_DISABLE bit in register 0x645 is turned on, multicast
 * address also does not work, even though HSR_LEARN_MCAST_DISABLE bit in
 * register 0x644 can be used to control that.
 */
	SW_D data;
	int n;
	u16 mask = 0;

	for (n = 0; n < sw->eth_cnt; n++) {
		if (sw->eth_maps[n].proto & HSR_HW) {
			mask = sw->eth_maps[n].mask;
			break;
		}
	}
	sw->reg->w32(sw, REG_HSR_PORT_MAP__4, mask);
	data = SW_R(sw, REG_HSR_ALU_CTRL_0__1);
	data &= ~HSR_NODE_UNICAST;
	SW_W(sw, REG_HSR_ALU_CTRL_0__1, data);
	if ((sw->overrides & HAVE_MORE_THAN_2_PORTS) && 1 == sw->eth_cnt)
		sw_cfg_port_base_vlan(sw, sw->HOST_PORT, mask | sw->HOST_MASK);
}  /* sw_setup_hsr */

static void stop_hsr(struct ksz_hsr_info *info)
{
	hsr_dev_destroy(info);
}

static void ksz_hsr_exit(struct ksz_hsr_info *info)
{
#ifdef CONFIG_HAVE_HSR_HW
	cancel_delayed_work_sync(&info->chk_ring);
#endif
}  /* ksz_hsr_exit */

static void ksz_hsr_init(struct ksz_hsr_info *info, struct ksz_sw *sw)
{
	info->state = -1;
	info->ports[0] = 0;
	info->ports[1] = 1;
	info->member = (1 << info->ports[0]) | (1 << info->ports[1]);
#ifdef CONFIG_HAVE_HSR_HW
	info->cap = HSR_CAP_DUPLICATE_DISCARD;
	info->cap |= HSR_CAP_REDBOX_CAPABLE;
#endif
	info->sw_dev = sw;
	info->ops = &hsr_ops;

#ifdef CONFIG_HAVE_HSR_HW
	INIT_DELAYED_WORK(&info->chk_ring, hsr_chk_ring);
#endif
}  /* ksz_hsr_init */

