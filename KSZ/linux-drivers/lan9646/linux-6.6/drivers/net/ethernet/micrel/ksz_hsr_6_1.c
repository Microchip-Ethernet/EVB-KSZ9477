// SPDX-License-Identifier: GPL-2.0
/* Copyright 2011-2014 Autronica Fire and Security AS
 *
 * Author(s):
 *	2011-2014 Arvid Brodin, arvid.brodin@alten.se
 *
 * The HSR spec says never to forward the same frame twice on the same
 * interface. A frame is identified by its source MAC address and its HSR
 * sequence number. This code keeps track of senders and their sequence numbers
 * to allow filtering of duplicate frames, and to detect HSR ring errors.
 * Same code handles filtering of duplicates for PRP as well.
 */

#include <linux/if_ether.h>
#include <linux/etherdevice.h>
#include <linux/slab.h>
#include <linux/rculist.h>
#include "hsr_main.h"

#ifdef CONFIG_KSZ_SWITCH

struct hsr_cfg_work {
	struct work_struct work;
	struct ksz_sw *sw;
	u8 addr[ETH_ALEN];
	u16 member;
	u16 vlan;
};

static void proc_hsr_cfg_work(struct work_struct *work)
{
	struct hsr_cfg_work *cfg_work =
		container_of(work, struct hsr_cfg_work, work);
	struct ksz_sw *sw = cfg_work->sw;

	sw->ops->cfg_mac(sw, 0, cfg_work->addr, cfg_work->member,
		false, false, 0);
	if (cfg_work->vlan) {
		if (cfg_work->member)
			cfg_work->member = sw->HOST_MASK;
		sw->ops->cfg_mac(sw, 0, cfg_work->addr, cfg_work->member,
			false, true, cfg_work->vlan);
	}

	kfree(cfg_work);
}  /* proc_hsr_work */

static void proc_hsr_cfg(struct ksz_hsr_info *info, u8 *addr, u16 member)
{
	struct hsr_cfg_work *cfg_work;

	cfg_work = kzalloc(sizeof(struct hsr_cfg_work), GFP_ATOMIC);
	if (!cfg_work)
		return;
	INIT_WORK(&cfg_work->work, proc_hsr_cfg_work);
	cfg_work->sw = info->sw_dev;
	memcpy(cfg_work->addr, addr, ETH_ALEN);
	cfg_work->member = member;
	if (info->redbox)
		cfg_work->vlan = info->redbox_vlan;
	schedule_work(&cfg_work->work);
}  /* proc_hsr_cfg */

static void proc_hsr_tx(struct ksz_hsr_info *info, struct sk_buff *skb)
{
	skb_queue_tail(&info->txq, skb);
	schedule_work(&info->tx_proc);
}  /* proc_hsr_tx */
#endif

/* hsr_main */
#ifdef CONFIG_KSZ_SWITCH
static
#endif
struct hsr_port *hsr_port_get_hsr(struct hsr_priv *hsr, enum hsr_port_type pt)
{
	struct hsr_port *port;

	hsr_for_each_port(hsr, port)
		if (port->type == pt)
			return port;
	return NULL;
}
/* hsr_main */

/* hsr_framereg */
/* seq_nr_after(a, b) - return true if a is after (higher in sequence than) b,
 * false otherwise.
 */
static bool seq_nr_after(u16 a, u16 b)
{
	/* Remove inconsistency where
	 * seq_nr_after(a, b) == seq_nr_before(a, b)
	 */
	if ((int)b - a == 32768)
		return false;

	return (((s16)(b - a)) < 0);
}

#define seq_nr_before(a, b)		seq_nr_after((b), (a))
#define seq_nr_before_or_eq(a, b)	(!seq_nr_after((a), (b)))

#ifdef CONFIG_KSZ_SWITCH
static
#endif
bool hsr_addr_is_self(struct hsr_priv *hsr, unsigned char *addr)
{
	struct hsr_node *node;

	node = list_first_or_null_rcu(&hsr->self_node_db, struct hsr_node,
				      mac_list);
	if (!node) {
		WARN_ONCE(1, "HSR: No self node\n");
		return false;
	}

	if (ether_addr_equal(addr, node->macaddress_A))
		return true;
	if (ether_addr_equal(addr, node->macaddress_B))
		return true;

	return false;
}

/* Search for mac entry. Caller must hold rcu read lock.
 */
static struct hsr_node *find_node_by_addr_A(struct list_head *node_db,
					    const unsigned char addr[ETH_ALEN])
{
	struct hsr_node *node;

	list_for_each_entry_rcu(node, node_db, mac_list) {
		if (ether_addr_equal(node->macaddress_A, addr))
			return node;
	}

	return NULL;
}

/* Helper for device init; the self_node_db is used in hsr_rcv() to recognize
 * frames from self that's been looped over the HSR ring.
 */
#ifdef CONFIG_KSZ_SWITCH
static
#endif
int hsr_create_self_node(struct hsr_priv *hsr,
			 const unsigned char addr_a[ETH_ALEN],
			 const unsigned char addr_b[ETH_ALEN])
{
	struct list_head *self_node_db = &hsr->self_node_db;
	struct hsr_node *node, *oldnode;

	node = kmalloc(sizeof(*node), GFP_KERNEL);
	if (!node)
		return -ENOMEM;

	ether_addr_copy(node->macaddress_A, addr_a);
	ether_addr_copy(node->macaddress_B, addr_b);

	spin_lock_bh(&hsr->list_lock);
	oldnode = list_first_or_null_rcu(self_node_db,
					 struct hsr_node, mac_list);
	if (oldnode) {
		list_replace_rcu(&oldnode->mac_list, &node->mac_list);
		spin_unlock_bh(&hsr->list_lock);
		kfree_rcu(oldnode, rcu_head);
	} else {
		list_add_tail_rcu(&node->mac_list, self_node_db);
		spin_unlock_bh(&hsr->list_lock);
	}

	return 0;
}

#ifdef CONFIG_KSZ_SWITCH
static
#endif
void hsr_del_self_node(struct hsr_priv *hsr)
{
	struct list_head *self_node_db = &hsr->self_node_db;
	struct hsr_node *node;

	spin_lock_bh(&hsr->list_lock);
	node = list_first_or_null_rcu(self_node_db, struct hsr_node, mac_list);
	if (node) {
		list_del_rcu(&node->mac_list);
		kfree_rcu(node, rcu_head);
	}
	spin_unlock_bh(&hsr->list_lock);
}

#ifdef CONFIG_KSZ_SWITCH
static
#endif
void hsr_del_nodes(struct list_head *node_db)
{
	struct hsr_node *node;
	struct hsr_node *tmp;

	list_for_each_entry_safe(node, tmp, node_db, mac_list)
		kfree(node);
}

#ifdef CONFIG_KSZ_SWITCH
static
#endif
void prp_handle_san_frame(bool san, enum hsr_port_type port,
			  struct hsr_node *node)
{
	/* Mark if the SAN node is over LAN_A or LAN_B */
	if (port == HSR_PT_SLAVE_A) {
		node->san_a = true;
		return;
	}

	if (port == HSR_PT_SLAVE_B)
		node->san_b = true;
}

/* Allocate an hsr_node and add it to node_db. 'addr' is the node's address_A;
 * seq_out is used to initialize filtering of outgoing duplicate frames
 * originating from the newly added node.
 */
static struct hsr_node *hsr_add_node(struct hsr_priv *hsr,
				     struct list_head *node_db,
				     unsigned char addr[],
				     u16 seq_out, bool san,
#ifdef CONFIG_KSZ_SWITCH
				     bool hsr_dev,
#endif
				     enum hsr_port_type rx_port)
{
	struct hsr_node *new_node, *node;
	unsigned long now;
	int i;

	new_node = kzalloc(sizeof(*new_node), GFP_ATOMIC);
	if (!new_node)
		return NULL;

#ifdef CONFIG_KSZ_SWITCH
dbg_msg("%s %x %02x:%02x:%02x:%02x:%02x:%02x %04x %d\n", __func__, (int)new_node,
addr[0], addr[1], addr[2], addr[3], addr[4], addr[5], seq_out, hsr_dev);
#endif
	ether_addr_copy(new_node->macaddress_A, addr);
	spin_lock_init(&new_node->seq_out_lock);

	/* We are only interested in time diffs here, so use current jiffies
	 * as initialization. (0 could trigger an spurious ring error warning).
	 */
	now = jiffies;
	for (i = 0; i < HSR_PT_PORTS; i++) {
		new_node->time_in[i] = now;
		new_node->time_out[i] = now;
	}
	for (i = 0; i < HSR_PT_PORTS; i++)
		new_node->seq_out[i] = seq_out;

	if (san && hsr->proto_ops->handle_san_frame)
		hsr->proto_ops->handle_san_frame(san, rx_port, new_node);

	spin_lock_bh(&hsr->list_lock);
	list_for_each_entry_rcu(node, node_db, mac_list,
				lockdep_is_held(&hsr->list_lock)) {
		if (ether_addr_equal(node->macaddress_A, addr))
			goto out;
		if (ether_addr_equal(node->macaddress_B, addr))
			goto out;
	}
	list_add_tail_rcu(&new_node->mac_list, node_db);
	spin_unlock_bh(&hsr->list_lock);

#ifdef CONFIG_KSZ_SWITCH
	/* Assume the same address is used in both lanes. */
	new_node->is_same_addr = true;
	if (hsr_dev) {
		struct ksz_hsr_info *info = container_of(hsr,
			struct ksz_hsr_info, hsr);
		int not_self;

		not_self = memcmp(addr, info->src_addr, ETH_ALEN);
		if (not_self)
			proc_hsr_cfg(info, addr, info->member);
		info->part_cnt++;
	} else {
		new_node->slave = 1;
	}
#endif
	return new_node;
out:
	spin_unlock_bh(&hsr->list_lock);
	kfree(new_node);
	return node;
}

#ifdef CONFIG_KSZ_SWITCH
static
#endif
void prp_update_san_info(struct hsr_node *node, bool is_sup)
{
	if (!is_sup)
		return;

	node->san_a = false;
	node->san_b = false;
}

/* Get the hsr_node from which 'skb' was sent.
 */
#ifdef CONFIG_KSZ_SWITCH
static
#endif
struct hsr_node *hsr_get_node(struct hsr_port *port, struct list_head *node_db,
			      struct sk_buff *skb, bool is_sup,
			      enum hsr_port_type rx_port)
{
	struct hsr_priv *hsr = port->hsr;
	struct hsr_node *node;
	struct ethhdr *ethhdr;
	struct prp_rct *rct;
	bool san = false;
	u16 seq_out;

	if (!skb_mac_header_was_set(skb))
		return NULL;

	ethhdr = (struct ethhdr *)skb_mac_header(skb);

	list_for_each_entry_rcu(node, node_db, mac_list) {
		if (ether_addr_equal(node->macaddress_A, ethhdr->h_source)) {
			if (hsr->proto_ops->update_san_info)
				hsr->proto_ops->update_san_info(node, is_sup);
			return node;
		}
		if (ether_addr_equal(node->macaddress_B, ethhdr->h_source)) {
			if (hsr->proto_ops->update_san_info)
				hsr->proto_ops->update_san_info(node, is_sup);
			return node;
		}
	}

	/* Everyone may create a node entry, connected node to a HSR/PRP
	 * device.
	 */
	if (ethhdr->h_proto == htons(ETH_P_PRP) ||
	    ethhdr->h_proto == htons(ETH_P_HSR)) {
		/* Use the existing sequence_nr from the tag as starting point
		 * for filtering duplicate frames.
		 */
		seq_out = hsr_get_skb_sequence_nr(skb) - 1;
	} else {
		rct = skb_get_PRP_rct(skb);
		if (rct && prp_check_lsdu_size(skb, rct, is_sup)) {
			seq_out = prp_get_skb_sequence_nr(rct);
		} else {
			if (rx_port != HSR_PT_MASTER)
				san = true;
			seq_out = HSR_SEQNR_START;
		}
		seq_out--;
	}

	return hsr_add_node(hsr, node_db, ethhdr->h_source, seq_out,
#ifdef CONFIG_KSZ_SWITCH
			    san, true, rx_port);
#else
			    san, rx_port);
#endif
}

/* Use the Supervision frame's info about an eventual macaddress_B for merging
 * nodes that has previously had their macaddress_B registered as a separate
 * node.
 */
#ifdef CONFIG_KSZ_SWITCH
static
#endif
void hsr_handle_sup_frame(struct hsr_frame_info *frame)
{
	struct hsr_node *node_curr = frame->node_src;
	struct hsr_port *port_rcv = frame->port_rcv;
	struct hsr_priv *hsr = port_rcv->hsr;
	struct hsr_sup_payload *hsr_sp;
	struct hsr_sup_tlv *hsr_sup_tlv;
	struct hsr_node *node_real;
	struct sk_buff *skb = NULL;
	struct list_head *node_db;
	struct ethhdr *ethhdr;
	int i;
	unsigned int pull_size = 0;
	unsigned int total_pull_size = 0;

	/* Here either frame->skb_hsr or frame->skb_prp should be
	 * valid as supervision frame always will have protocol
	 * header info.
	 */
	if (frame->skb_hsr)
		skb = frame->skb_hsr;
	else if (frame->skb_prp)
		skb = frame->skb_prp;
	else if (frame->skb_std)
		skb = frame->skb_std;
	if (!skb)
		return;

	/* Leave the ethernet header. */
	pull_size = sizeof(struct ethhdr);
	skb_pull(skb, pull_size);
	total_pull_size += pull_size;

	ethhdr = (struct ethhdr *)skb_mac_header(skb);

	/* And leave the HSR tag. */
	if (ethhdr->h_proto == htons(ETH_P_HSR)) {
		pull_size = sizeof(struct hsr_tag);
		skb_pull(skb, pull_size);
		total_pull_size += pull_size;
	}

	/* And leave the HSR sup tag. */
	pull_size = sizeof(struct hsr_sup_tag);
	skb_pull(skb, pull_size);
	total_pull_size += pull_size;

	/* get HSR sup payload */
	hsr_sp = (struct hsr_sup_payload *)skb->data;

	/* Merge node_curr (registered on macaddress_B) into node_real */
	node_db = &port_rcv->hsr->node_db;
	node_real = find_node_by_addr_A(node_db, hsr_sp->macaddress_A);
#ifdef CONFIG_KSZ_SWITCH
	if (!node_real)
{
	u8 *data = (u8 *) eth_hdr(skb)->h_source;
	u8 *addr = (u8 *) hsr_sp->macaddress_A;
dbg_msg("add new: %02x:%02x:%02x; %02x:%02x:%02x\n",
data[3], data[4], data[5],
addr[3], addr[4], addr[5]);
}
#endif
	if (!node_real)
		/* No frame received from AddrA of this node yet */
		node_real = hsr_add_node(hsr, node_db, hsr_sp->macaddress_A,
					 HSR_SEQNR_START - 1, true,
#ifdef CONFIG_KSZ_SWITCH
					 true,
#endif
					 port_rcv->type);
	if (!node_real)
		goto done; /* No mem */
	if (node_real == node_curr)
		/* Node has already been merged */
		goto done;

	/* Leave the first HSR sup payload. */
	pull_size = sizeof(struct hsr_sup_payload);
	skb_pull(skb, pull_size);
	total_pull_size += pull_size;

	/* Get second supervision tlv */
	hsr_sup_tlv = (struct hsr_sup_tlv *)skb->data;
	/* And check if it is a redbox mac TLV */
	if (hsr_sup_tlv->HSR_TLV_type == PRP_TLV_REDBOX_MAC) {
		/* We could stop here after pushing hsr_sup_payload,
		 * or proceed and allow macaddress_B and for redboxes.
		 */
		/* Sanity check length */
		if (hsr_sup_tlv->HSR_TLV_length != 6)
			goto done;

		/* Leave the second HSR sup tlv. */
		pull_size = sizeof(struct hsr_sup_tlv);
		skb_pull(skb, pull_size);
		total_pull_size += pull_size;

		/* Get redbox mac address. */
		hsr_sp = (struct hsr_sup_payload *)skb->data;

		/* Check if redbox mac and node mac are equal. */
		if (!ether_addr_equal(node_real->macaddress_A, hsr_sp->macaddress_A)) {
			/* This is a redbox supervision frame for a VDAN! */
			goto done;
		}
	}

	ether_addr_copy(node_real->macaddress_B, ethhdr->h_source);
#ifdef CONFIG_KSZ_SWITCH
	if (memcmp(node_real->macaddress_A, node_real->macaddress_B, ETH_ALEN))
		node_real->is_same_addr = false;
#endif
	spin_lock_bh(&node_real->seq_out_lock);
	for (i = 0; i < HSR_PT_PORTS; i++) {
		if (!node_curr->time_in_stale[i] &&
		    time_after(node_curr->time_in[i], node_real->time_in[i])) {
			node_real->time_in[i] = node_curr->time_in[i];
			node_real->time_in_stale[i] =
						node_curr->time_in_stale[i];
		}
		if (seq_nr_after(node_curr->seq_out[i], node_real->seq_out[i]))
			node_real->seq_out[i] = node_curr->seq_out[i];
	}
	spin_unlock_bh(&node_real->seq_out_lock);
	node_real->addr_B_port = port_rcv->type;

	spin_lock_bh(&hsr->list_lock);
	if (!node_curr->removed) {
		list_del_rcu(&node_curr->mac_list);
		node_curr->removed = true;
		kfree_rcu(node_curr, rcu_head);
	}
	spin_unlock_bh(&hsr->list_lock);

done:
	/* Push back here */
	skb_push(skb, total_pull_size);
}

/* 'skb' is a frame meant for this host, that is to be passed to upper layers.
 *
 * If the frame was sent by a node's B interface, replace the source
 * address with that node's "official" address (macaddress_A) so that upper
 * layers recognize where it came from.
 */
#ifdef CONFIG_KSZ_SWITCH
static
#endif
void hsr_addr_subst_source(struct hsr_node *node, struct sk_buff *skb)
{
	if (!skb_mac_header_was_set(skb)) {
		WARN_ONCE(1, "%s: Mac header not set\n", __func__);
		return;
	}

	memcpy(&eth_hdr(skb)->h_source, node->macaddress_A, ETH_ALEN);
}

#ifndef CONFIG_KSZ_SWITCH
/* 'skb' is a frame meant for another host.
 * 'port' is the outgoing interface
 *
 * Substitute the target (dest) MAC address if necessary, so the it matches the
 * recipient interface MAC address, regardless of whether that is the
 * recipient's A or B interface.
 * This is needed to keep the packets flowing through switches that learn on
 * which "side" the different interfaces are.
 */
#ifdef CONFIG_KSZ_SWITCH
static
#endif
void hsr_addr_subst_dest(struct hsr_node *node_src, struct sk_buff *skb,
			 struct hsr_port *port)
{
	struct hsr_node *node_dst;

	if (!skb_mac_header_was_set(skb)) {
		WARN_ONCE(1, "%s: Mac header not set\n", __func__);
		return;
	}

	if (!is_unicast_ether_addr(eth_hdr(skb)->h_dest))
		return;

	node_dst = find_node_by_addr_A(&port->hsr->node_db,
				       eth_hdr(skb)->h_dest);
	if (!node_dst) {
		if (net_ratelimit())
			netdev_err(skb->dev, "%s: Unknown node\n", __func__);
		return;
	}
	if (port->type != node_dst->addr_B_port)
		return;

	if (is_valid_ether_addr(node_dst->macaddress_B))
		ether_addr_copy(eth_hdr(skb)->h_dest, node_dst->macaddress_B);
}
#endif

#ifdef CONFIG_KSZ_SWITCH
static struct hsr_node *hsr_addr_chk_dest(struct hsr_priv *hsr,
					  struct sk_buff *skb)
{
	struct hsr_node *node_dst;

	if (!skb_mac_header_was_set(skb)) {
		WARN_ONCE(1, "%s: Mac header not set\n", __func__);
		return NULL;
	}

	if (!is_unicast_ether_addr(eth_hdr(skb)->h_dest))
		return NULL;

	node_dst = find_node_by_addr_A(&hsr->node_db,
				       eth_hdr(skb)->h_dest);
	if (!node_dst) {
dbg_msg("%02x %02x %02x %02x %02x %02x\n",
	skb->data[0], skb->data[1], skb->data[2], skb->data[3], skb->data[4], skb->data[5]);
		if (net_ratelimit())
			netdev_err(skb->dev, "%s: Unknown node\n", __func__);
		return NULL;
	}

	return node_dst;
}
#endif

#ifdef CONFIG_KSZ_SWITCH
static
#endif
void hsr_register_frame_in(struct hsr_node *node, struct hsr_port *port,
			   u16 sequence_nr)
{
	/* Don't register incoming frames without a valid sequence number. This
	 * ensures entries of restarted nodes gets pruned so that they can
	 * re-register and resume communications.
	 */
	if (!(port->dev->features & NETIF_F_HW_HSR_TAG_RM) &&
	    seq_nr_before(sequence_nr, node->seq_out[port->type]))
		return;

	node->time_in[port->type] = jiffies;
	node->time_in_stale[port->type] = false;
}

#ifdef CONFIG_KSZ_SWITCH
static
#endif
void hsr_update_frame_out(struct hsr_port *port, struct hsr_node *node,
	u16 sequence_nr)
{
	spin_lock_bh(&node->seq_out_lock);
	node->seq_out[port->type] = sequence_nr;
	spin_unlock_bh(&node->seq_out_lock);
}

/* 'skb' is a HSR Ethernet frame (with a HSR tag inserted), with a valid
 * ethhdr->h_source address and skb->mac_header set.
 *
 * Return:
 *	 1 if frame can be shown to have been sent recently on this interface,
 *	 0 otherwise, or
 *	 negative error code on error
 */
#ifdef CONFIG_KSZ_SWITCH
static
#endif
int hsr_register_frame_out(struct hsr_port *port, struct hsr_node *node,
			   u16 sequence_nr)
{
	spin_lock_bh(&node->seq_out_lock);
	if (seq_nr_before_or_eq(sequence_nr, node->seq_out[port->type]) &&
	    time_is_after_jiffies(node->time_out[port->type] +
	    msecs_to_jiffies(HSR_ENTRY_FORGET_TIME))) {
		spin_unlock_bh(&node->seq_out_lock);
		return 1;
	}

	node->time_out[port->type] = jiffies;
	node->seq_out[port->type] = sequence_nr;
	spin_unlock_bh(&node->seq_out_lock);
	return 0;
}

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

/* Remove stale sequence_nr records. Called by timer every
 * HSR_LIFE_CHECK_INTERVAL (two seconds or so).
 */
#ifdef CONFIG_KSZ_SWITCH
static
#endif
void hsr_prune_nodes(struct timer_list *t)
{
	struct hsr_priv *hsr = from_timer(hsr, t, prune_timer);
	struct hsr_node *node;
	struct hsr_node *tmp;
	struct hsr_port *port;
	unsigned long timestamp;
	unsigned long time_a, time_b;

	spin_lock_bh(&hsr->list_lock);
	list_for_each_entry_safe(node, tmp, &hsr->node_db, mac_list) {
		/* Don't prune own node. Neither time_in[HSR_PT_SLAVE_A]
		 * nor time_in[HSR_PT_SLAVE_B], will ever be updated for
		 * the master port. Thus the master node will be repeatedly
		 * pruned leading to packet loss.
		 */
		if (hsr_addr_is_self(hsr, node->macaddress_A))
			continue;

		/* Shorthand */
		time_a = node->time_in[HSR_PT_SLAVE_A];
		time_b = node->time_in[HSR_PT_SLAVE_B];

		/* Check for timestamps old enough to risk wrap-around */
		if (time_after(jiffies, time_a + MAX_JIFFY_OFFSET / 2))
			node->time_in_stale[HSR_PT_SLAVE_A] = true;
		if (time_after(jiffies, time_b + MAX_JIFFY_OFFSET / 2))
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

		/* Warn of ring error only as long as we get frames at all */
		if (time_is_after_jiffies(timestamp +
				msecs_to_jiffies(1.5 * MAX_SLAVE_DIFF))) {
			rcu_read_lock();
			port = get_late_port(hsr, node);
#ifndef CONFIG_KSZ_SWITCH
			if (port)
				hsr_nl_ringerror(hsr, node->macaddress_A, port);
#endif
			rcu_read_unlock();
		}

#ifdef CONFIG_KSZ_SWITCH
		if (1 == node->slave && time_is_before_jiffies(timestamp +
			msecs_to_jiffies(HSR_NODE_FORGET_TIME / 4))) {

#if 1
dbg_msg("drop: %02x:%02x:%02x:%02x:%02x:%02x %ld\n",
node->macaddress_A[0],
node->macaddress_A[1],
node->macaddress_A[2],
node->macaddress_A[3],
node->macaddress_A[4],
node->macaddress_A[5],
jiffies - timestamp);
#endif
			node->slave = 2;
		}
#endif

		/* Prune old entries */
		if (time_is_before_jiffies(timestamp +
				msecs_to_jiffies(HSR_NODE_FORGET_TIME))) {
#ifdef CONFIG_KSZ_SWITCH
			struct ksz_hsr_info *info = container_of(hsr,
				struct ksz_hsr_info, hsr);

			if (!node->slave) {
				proc_hsr_cfg(info, node->macaddress_A, 0);
				info->part_cnt--;
			}

#if 1
dbg_msg("forget: %02x:%02x:%02x:%02x:%02x:%02x %lx %lx %lx; %ld\n",
node->macaddress_A[0],
node->macaddress_A[1],
node->macaddress_A[2],
node->macaddress_A[3],
node->macaddress_A[4],
node->macaddress_A[5],
time_a, time_b, timestamp, jiffies - timestamp);
#endif
			if (node == info->center) {
				info->center = NULL;
				info->seq_num = 0;
				info->ring = 0;
			}
#endif
#ifndef CONFIG_KSZ_SWITCH
			hsr_nl_nodedown(hsr, node->macaddress_A);
#endif
			if (!node->removed) {
				list_del_rcu(&node->mac_list);
				node->removed = true;
				/* Note that we need to free this entry later: */
				kfree_rcu(node, rcu_head);
			}
		}
	}
	spin_unlock_bh(&hsr->list_lock);

	/* Restart timer */
	mod_timer(&hsr->prune_timer,
		  jiffies + msecs_to_jiffies(PRUNE_PERIOD));
}

#ifndef CONFIG_KSZ_SWITCH
#ifdef CONFIG_KSZ_SWITCH
static
#endif
void *hsr_get_next_node(struct hsr_priv *hsr, void *_pos,
			unsigned char addr[ETH_ALEN])
{
	struct hsr_node *node;

	if (!_pos) {
		node = list_first_or_null_rcu(&hsr->node_db,
					      struct hsr_node, mac_list);
		if (node)
			ether_addr_copy(addr, node->macaddress_A);
		return node;
	}

	node = _pos;
	list_for_each_entry_continue_rcu(node, &hsr->node_db, mac_list) {
		ether_addr_copy(addr, node->macaddress_A);
		return node;
	}

	return NULL;
}

#ifdef CONFIG_KSZ_SWITCH
static
#endif
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

	node = find_node_by_addr_A(&hsr->node_db, addr);
	if (!node)
		return -ENOENT;

	ether_addr_copy(addr_b, node->macaddress_B);

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

	if (node->addr_B_port != HSR_PT_NONE) {
		port = hsr_port_get_hsr(hsr, node->addr_B_port);
		*addr_b_ifindex = port->dev->ifindex;
	} else {
		*addr_b_ifindex = -1;
	}

	return 0;
}
#endif
/* hsr_framereg */

#ifdef CONFIG_KSZ_SWITCH
static void hsr_notify_link_lost(struct ksz_hsr_info *info)
{
	static u8 lost_buf[sizeof(struct ksz_resp_msg) +
		sizeof(struct ksz_hsr_node)];

dbg_msg(" hsr: %u %u:%u %u:%u\n", info->ring,
	info->p1_down, info->p2_down, info->p1_lost, info->p2_lost);
	if ((info->notifications & HSR_INFO_LINK_LOST)) {
		struct ksz_resp_msg *msg = (struct ksz_resp_msg *) lost_buf;
		struct ksz_hsr_node active;
		struct ksz_sw *sw = info->sw_dev;
		struct file_dev_info *dev_info;
		size_t n = sizeof(struct ksz_resp_msg) +
			sizeof(struct ksz_hsr_node);

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
		dev_info = sw->dev_list[0];
		while (dev_info) {
			if ((dev_info->notifications[DEV_MOD_HSR] &
			    HSR_INFO_LINK_LOST))
				file_dev_setup_msg(dev_info, msg, n, NULL,
						   NULL);
			dev_info = dev_info->next;
		}
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

	list_for_each_entry_rcu(node, &hsr->node_db, mac_list) {
		if (!memcmp(node->macaddress_A, info->src_addr, ETH_ALEN))
			continue;
		if (!node->slave) {
			struct ksz_hsr_table entry;
			struct ksz_sw *sw = info->sw_dev;

			memcpy(entry.src_mac, node->macaddress_A, ETH_ALEN);
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
#endif

#ifdef CONFIG_KSZ_SWITCH
static
void hsr_rmv_slaves(struct ksz_hsr_info *info)
{
	struct hsr_priv *hsr = &info->hsr;
	struct hsr_node *node;
	struct hsr_node *tmp;

	spin_lock_bh(&hsr->list_lock);
	list_for_each_entry_safe(node, tmp, &hsr->node_db, mac_list) {

		/* Prune slave entries */
		if (node->slave && !node->removed) {
			node->removed = true;
			list_del_rcu(&node->mac_list);
			/* Note that we need to free this entry later: */
			kfree_rcu(node, rcu_head);
		}
	}
	spin_unlock_bh(&hsr->list_lock);
}
#endif

/* hsr_slave */
#ifdef CONFIG_KSZ_SWITCH
static
#endif
bool hsr_port_exists(const struct net_device *dev)
{
#ifdef CONFIG_KSZ_SWITCH
	return true;
#else
	return rcu_access_pointer(dev->rx_handler) == hsr_handle_frame;
#endif
}

static inline struct hsr_port *hsr_port_get_rtnl(const struct net_device *dev)
{
	ASSERT_RTNL();
	return hsr_port_exists(dev) ?
				rtnl_dereference(dev->rx_handler_data) : NULL;
}

static inline struct hsr_port *hsr_port_get_rcu(const struct net_device *dev)
{
	return hsr_port_exists(dev) ?
				rcu_dereference(dev->rx_handler_data) : NULL;
}

#ifdef CONFIG_KSZ_SWITCH
static
#endif
bool hsr_invalid_dan_ingress_frame(__be16 protocol)
{
	return (protocol != htons(ETH_P_PRP) && protocol != htons(ETH_P_HSR));
}

#ifndef CONFIG_KSZ_SWITCH
static rx_handler_result_t hsr_handle_frame(struct sk_buff **pskb)
{
	struct sk_buff *skb = *pskb;
	struct hsr_port *port;
	struct hsr_priv *hsr;
	__be16 protocol;

	/* Packets from dev_loopback_xmit() do not have L2 header, bail out */
	if (unlikely(skb->pkt_type == PACKET_LOOPBACK))
		return RX_HANDLER_PASS;

	if (!skb_mac_header_was_set(skb)) {
		WARN_ONCE(1, "%s: skb invalid", __func__);
		return RX_HANDLER_PASS;
	}

	port = hsr_port_get_rcu(skb->dev);
	if (!port)
		goto finish_pass;
	hsr = port->hsr;

	if (hsr_addr_is_self(port->hsr, eth_hdr(skb)->h_source)) {
		/* Directly kill frames sent by ourselves */
		kfree_skb(skb);
		goto finish_consume;
	}

	/* For HSR, only tagged frames are expected (unless the device offloads
	 * HSR tag removal), but for PRP there could be non tagged frames as
	 * well from Single attached nodes (SANs).
	 */
	protocol = eth_hdr(skb)->h_proto;

	if (!(port->dev->features & NETIF_F_HW_HSR_TAG_RM) &&
	    hsr->proto_ops->invalid_dan_ingress_frame &&
	    hsr->proto_ops->invalid_dan_ingress_frame(protocol))
		goto finish_pass;

	skb_push(skb, ETH_HLEN);
	skb_reset_mac_header(skb);
	if ((!hsr->prot_version && protocol == htons(ETH_P_PRP)) ||
	    protocol == htons(ETH_P_HSR))
		skb_set_network_header(skb, ETH_HLEN + HSR_HLEN);
	skb_reset_mac_len(skb);

	hsr_forward_skb(skb, port);

finish_consume:
	return RX_HANDLER_CONSUMED;

finish_pass:
	return RX_HANDLER_PASS;
}
#endif

#ifndef CONFIG_KSZ_SWITCH
static int hsr_check_dev_ok(struct net_device *dev,
			    struct netlink_ext_ack *extack)
{
	/* Don't allow HSR on non-ethernet like devices */
	if ((dev->flags & IFF_LOOPBACK) || dev->type != ARPHRD_ETHER ||
	    dev->addr_len != ETH_ALEN) {
		NL_SET_ERR_MSG_MOD(extack, "Cannot use loopback or non-ethernet device as HSR slave.");
		return -EINVAL;
	}

#ifndef CONFIG_KSZ_SWITCH
	/* Don't allow enslaving hsr devices */
	if (is_hsr_master(dev)) {
		NL_SET_ERR_MSG_MOD(extack,
				   "Cannot create trees of HSR devices.");
		return -EINVAL;
	}
#endif

	if (hsr_port_exists(dev)) {
		NL_SET_ERR_MSG_MOD(extack,
				   "This device is already a HSR slave.");
		return -EINVAL;
	}

	if (is_vlan_dev(dev)) {
		NL_SET_ERR_MSG_MOD(extack, "HSR on top of VLAN is not yet supported in this driver.");
		return -EINVAL;
	}

	if (dev->priv_flags & IFF_DONT_BRIDGE) {
		NL_SET_ERR_MSG_MOD(extack,
				   "This device does not support bridging.");
		return -EOPNOTSUPP;
	}

	/* HSR over bonded devices has not been tested, but I'm not sure it
	 * won't work...
	 */

	return 0;
}
#endif

#ifndef CONFIG_KSZ_SWITCH
/* Setup device to be added to the HSR bridge. */
static int hsr_portdev_setup(struct hsr_priv *hsr, struct net_device *dev,
			     struct hsr_port *port,
			     struct netlink_ext_ack *extack)

{
	struct net_device *hsr_dev;
	struct hsr_port *master;
	int res;

	res = dev_set_promiscuity(dev, 1);
	if (res)
		return res;

	master = hsr_port_get_hsr(hsr, HSR_PT_MASTER);
	hsr_dev = master->dev;

	res = netdev_upper_dev_link(dev, hsr_dev, extack);
	if (res)
		goto fail_upper_dev_link;

	res = netdev_rx_handler_register(dev, hsr_handle_frame, port);
	if (res)
		goto fail_rx_handler;
	dev_disable_lro(dev);

	return 0;

fail_rx_handler:
	netdev_upper_dev_unlink(dev, hsr_dev);
fail_upper_dev_link:
	dev_set_promiscuity(dev, -1);
	return res;
}
#endif

#ifdef CONFIG_KSZ_SWITCH
static
#endif
int hsr_add_port(struct hsr_priv *hsr, struct net_device *dev,
		 enum hsr_port_type type, struct netlink_ext_ack *extack)
{
#ifdef CONFIG_KSZ_SWITCH
	struct hsr_port *port;
#else
	struct hsr_port *port, *master;
	int res;

	if (type != HSR_PT_MASTER) {
		res = hsr_check_dev_ok(dev, extack);
		if (res)
			return res;
	}
#endif

	port = hsr_port_get_hsr(hsr, type);
	if (port)
		return -EBUSY;	/* This port already exists */

	port = kzalloc(sizeof(*port), GFP_KERNEL);
	if (!port)
		return -ENOMEM;

	port->hsr = hsr;
	port->dev = dev;
	port->type = type;

#ifndef CONFIG_KSZ_SWITCH
	if (type != HSR_PT_MASTER) {
		res = hsr_portdev_setup(hsr, dev, port, extack);
		if (res)
			goto fail_dev_setup;
	}
#endif

	list_add_tail_rcu(&port->port_list, &hsr->ports);
	synchronize_rcu();

#ifndef CONFIG_KSZ_SWITCH
	master = hsr_port_get_hsr(hsr, HSR_PT_MASTER);
	netdev_update_features(master->dev);
	dev_set_mtu(master->dev, hsr_get_max_mtu(hsr));
#endif

	return 0;

#ifndef CONFIG_KSZ_SWITCH
fail_dev_setup:
	kfree(port);
	return res;
#endif
}

#ifdef CONFIG_KSZ_SWITCH
static
#endif
void hsr_del_port(struct hsr_port *port)
{
	struct hsr_priv *hsr;
	struct hsr_port *master;

	hsr = port->hsr;
	master = hsr_port_get_hsr(hsr, HSR_PT_MASTER);
	list_del_rcu(&port->port_list);

	if (port != master) {
		netdev_update_features(master->dev);
#ifndef CONFIG_KSZ_SWITCH
		dev_set_mtu(master->dev, hsr_get_max_mtu(hsr));
		netdev_rx_handler_unregister(port->dev);
		dev_set_promiscuity(port->dev, -1);
		netdev_upper_dev_unlink(port->dev, master->dev);
#endif
	}

	synchronize_rcu();

	kfree(port);
}
/* hsr_slave */

/* hsr_forward */
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
	struct ethhdr *eth_hdr;
	struct hsr_sup_tag *hsr_sup_tag;
	struct hsrv1_ethhdr_sp *hsr_V1_hdr;
	struct hsr_sup_tlv *hsr_sup_tlv;
	u16 total_length = 0;

	WARN_ON_ONCE(!skb_mac_header_was_set(skb));
	eth_hdr = (struct ethhdr *)skb_mac_header(skb);

	/* Correct addr? */
	if (!ether_addr_equal(eth_hdr->h_dest,
			      hsr->sup_multicast_addr))
		return false;

	/* Correct ether type?. */
	if (!(eth_hdr->h_proto == htons(ETH_P_PRP) ||
	      eth_hdr->h_proto == htons(ETH_P_HSR)))
		return false;

	/* Get the supervision header from correct location. */
	if (eth_hdr->h_proto == htons(ETH_P_HSR)) { /* Okay HSRv1. */
		total_length = sizeof(struct hsrv1_ethhdr_sp);
		if (!pskb_may_pull(skb, total_length))
			return false;

		hsr_V1_hdr = (struct hsrv1_ethhdr_sp *)skb_mac_header(skb);
		if (hsr_V1_hdr->hsr.encap_proto != htons(ETH_P_PRP))
			return false;

		hsr_sup_tag = &hsr_V1_hdr->hsr_sup;
	} else {
		total_length = sizeof(struct hsrv0_ethhdr_sp);
		if (!pskb_may_pull(skb, total_length))
			return false;

		hsr_sup_tag =
		     &((struct hsrv0_ethhdr_sp *)skb_mac_header(skb))->hsr_sup;
	}

	if (hsr_sup_tag->tlv.HSR_TLV_type != HSR_TLV_ANNOUNCE &&
	    hsr_sup_tag->tlv.HSR_TLV_type != HSR_TLV_LIFE_CHECK &&
	    hsr_sup_tag->tlv.HSR_TLV_type != PRP_TLV_LIFE_CHECK_DD &&
	    hsr_sup_tag->tlv.HSR_TLV_type != PRP_TLV_LIFE_CHECK_DA)
		return false;
	if (hsr_sup_tag->tlv.HSR_TLV_length != 12 &&
	    hsr_sup_tag->tlv.HSR_TLV_length != sizeof(struct hsr_sup_payload))
		return false;

	/* Get next tlv */
	total_length += sizeof(struct hsr_sup_tlv) + hsr_sup_tag->tlv.HSR_TLV_length;
	if (!pskb_may_pull(skb, total_length))
		return false;
	skb_pull(skb, total_length);
	hsr_sup_tlv = (struct hsr_sup_tlv *)skb->data;
	skb_push(skb, total_length);

	/* if this is a redbox supervision frame we need to verify
	 * that more data is available
	 */
	if (hsr_sup_tlv->HSR_TLV_type == PRP_TLV_REDBOX_MAC) {
		/* tlv length must be a length of a mac address */
		if (hsr_sup_tlv->HSR_TLV_length != sizeof(struct hsr_sup_payload))
			return false;

		/* make sure another tlv follows */
		total_length += sizeof(struct hsr_sup_tlv) + hsr_sup_tlv->HSR_TLV_length;
		if (!pskb_may_pull(skb, total_length))
			return false;

		/* get next tlv */
		skb_pull(skb, total_length);
		hsr_sup_tlv = (struct hsr_sup_tlv *)skb->data;
		skb_push(skb, total_length);
	}

	/* end of tlvs must follow at the end */
	if (hsr_sup_tlv->HSR_TLV_type == HSR_TLV_EOT &&
	    hsr_sup_tlv->HSR_TLV_length != 0)
		return false;

	return true;
}

static struct sk_buff *create_stripped_skb_hsr(struct sk_buff *skb_in,
					       struct hsr_frame_info *frame)
{
	struct sk_buff *skb;
	int copylen;
	unsigned char *dst, *src;

#ifdef CONFIG_KSZ_SWITCH
	if (!frame->skb_out) {
		/* frame->skb_out will be assinged frame->skb_std. */
		frame->skb_hsr = NULL;

#if 0
		/* Retain a copy of original HSR frame. */
		if (frame->fwd_hsr)
			frame->skb_hsr = skb_copy(skb_in, GFP_ATOMIC);
#endif
		copylen = 2 * ETH_ALEN;
		if (frame->is_vlan)
			copylen += VLAN_HLEN;
		src = skb_mac_header(skb_in);
		skb = skb_in;
		dst = skb_pull(skb, HSR_HLEN);
		memmove(dst, src, copylen);
		if (skb->ip_summed == CHECKSUM_PARTIAL)
			skb->csum_start -= HSR_HLEN;
		goto create_stripped_next;
	}
#endif

	skb_pull(skb_in, HSR_HLEN);
	skb = __pskb_copy(skb_in, skb_headroom(skb_in) - HSR_HLEN, GFP_ATOMIC);
	skb_push(skb_in, HSR_HLEN);
	if (!skb)
		return NULL;

	skb_reset_mac_header(skb);

	if (skb->ip_summed == CHECKSUM_PARTIAL)
		skb->csum_start -= HSR_HLEN;

	copylen = 2 * ETH_ALEN;
	if (frame->is_vlan)
		copylen += VLAN_HLEN;
	src = skb_mac_header(skb_in);
	dst = skb_mac_header(skb);
	memcpy(dst, src, copylen);

#ifdef CONFIG_KSZ_SWITCH
create_stripped_next:
#endif
	skb->protocol = eth_hdr(skb)->h_proto;
	return skb;
}

#ifdef CONFIG_KSZ_SWITCH
static
#endif
struct sk_buff *hsr_get_untagged_frame(struct hsr_frame_info *frame,
				       struct hsr_port *port)
{
	if (!frame->skb_std) {
		if (frame->skb_hsr)
			frame->skb_std =
				create_stripped_skb_hsr(frame->skb_hsr, frame);
		else
			netdev_warn_once(port->dev,
					 "Unexpected frame received in hsr_get_untagged_frame()\n");

		if (!frame->skb_std)
			return NULL;
	}

#ifdef CONFIG_KSZ_SWITCH
	if (!frame->skb_out) {
		frame->skb_out = frame->skb_std;
		return frame->skb_std;
	} else {
		return skb_copy(frame->skb_std, GFP_ATOMIC);
	}
#endif
	return skb_clone(frame->skb_std, GFP_ATOMIC);
}

#ifdef CONFIG_KSZ_SWITCH
static
#endif
struct sk_buff *prp_get_untagged_frame(struct hsr_frame_info *frame,
				       struct hsr_port *port)
{
	if (!frame->skb_std) {
		if (frame->skb_prp) {
			/* trim the skb by len - HSR_HLEN to exclude RCT */
			skb_trim(frame->skb_prp,
				 frame->skb_prp->len - HSR_HLEN);
			frame->skb_std =
				__pskb_copy(frame->skb_prp,
					    skb_headroom(frame->skb_prp),
					    GFP_ATOMIC);
		} else {
			/* Unexpected */
			WARN_ONCE(1, "%s:%d: Unexpected frame received (port_src %s)\n",
				  __FILE__, __LINE__, port->dev->name);
			return NULL;
		}
	}

	return skb_clone(frame->skb_std, GFP_ATOMIC);
}

static void prp_set_lan_id(struct prp_rct *trailer,
			   struct hsr_port *port)
{
	int lane_id;

	if (port->type == HSR_PT_SLAVE_A)
		lane_id = 0;
	else
		lane_id = 1;

	/* Add net_id in the upper 3 bits of lane_id */
	lane_id |= port->hsr->net_id;
	set_prp_lan_id(trailer, lane_id);
}

/* Tailroom for PRP rct should have been created before calling this */
static struct sk_buff *prp_fill_rct(struct sk_buff *skb,
				    struct hsr_frame_info *frame,
				    struct hsr_port *port)
{
	struct prp_rct *trailer;
	int min_size = ETH_ZLEN;
	int lsdu_size;

	if (!skb)
		return skb;

	if (frame->is_vlan)
		min_size = VLAN_ETH_ZLEN;

	if (skb_put_padto(skb, min_size))
		return NULL;

	trailer = (struct prp_rct *)skb_put(skb, HSR_HLEN);
	lsdu_size = skb->len - 14;
	if (frame->is_vlan)
		lsdu_size -= 4;
	prp_set_lan_id(trailer, port);
	set_prp_LSDU_size(trailer, lsdu_size);
	trailer->sequence_nr = htons(frame->sequence_nr);
	trailer->PRP_suffix = htons(ETH_P_PRP);
	skb->protocol = eth_hdr(skb)->h_proto;

	return skb;
}

static void hsr_set_path_id(struct hsr_ethhdr *hsr_ethhdr,
			    struct hsr_port *port)
{
	int path_id;

	if (port->type == HSR_PT_SLAVE_A)
		path_id = 0;
	else
		path_id = 1;

	set_hsr_tag_path(&hsr_ethhdr->hsr_tag, path_id);
}

static struct sk_buff *hsr_fill_tag(struct sk_buff *skb,
				    struct hsr_frame_info *frame,
				    struct hsr_port *port, u8 proto_version)
{
	struct hsr_ethhdr *hsr_ethhdr;
	int lsdu_size;
#ifdef CONFIG_KSZ_SWITCH
	int vlan_size = 0;
#endif

	/* pad to minimum packet size which is 60 + 6 (HSR tag) */
	if (skb_put_padto(skb, ETH_ZLEN + HSR_HLEN))
		return NULL;

	lsdu_size = skb->len - 14;
	if (frame->is_vlan)
		lsdu_size -= 4;

#ifdef CONFIG_KSZ_SWITCH
	if (frame->is_vlan)
		vlan_size += 4;
	hsr_ethhdr = (struct hsr_ethhdr *)(skb_mac_header(skb) + vlan_size);
#else
	hsr_ethhdr = (struct hsr_ethhdr *)skb_mac_header(skb);
#endif

	hsr_set_path_id(hsr_ethhdr, port);
	set_hsr_tag_LSDU_size(&hsr_ethhdr->hsr_tag, lsdu_size);
	hsr_ethhdr->hsr_tag.sequence_nr = htons(frame->sequence_nr);
	hsr_ethhdr->hsr_tag.encap_proto = hsr_ethhdr->ethhdr.h_proto;
	hsr_ethhdr->ethhdr.h_proto = htons(proto_version ?
			ETH_P_HSR : ETH_P_PRP);
	skb->protocol = hsr_ethhdr->ethhdr.h_proto;

	return skb;
}

/* If the original frame was an HSR tagged frame, just clone it to be sent
 * unchanged. Otherwise, create a private frame especially tagged for 'port'.
 */
#ifdef CONFIG_KSZ_SWITCH
static
#endif
struct sk_buff *hsr_create_tagged_frame(struct hsr_frame_info *frame,
					struct hsr_port *port)
{
	unsigned char *dst, *src;
	struct sk_buff *skb;
	int movelen;

	if (frame->skb_hsr) {
		struct hsr_ethhdr *hsr_ethhdr =
			(struct hsr_ethhdr *)skb_mac_header(frame->skb_hsr);

		/* set the lane id properly */
		hsr_set_path_id(hsr_ethhdr, port);
		return skb_clone(frame->skb_hsr, GFP_ATOMIC);
	} else if (port->dev->features & NETIF_F_HW_HSR_TAG_INS) {
		return skb_clone(frame->skb_std, GFP_ATOMIC);
	}

#ifdef CONFIG_KSZ_SWITCH
	/* Re-use the socket buffer if not already used. */
	if (!frame->skb_out) {
		frame->skb_out = frame->skb_std;
		skb = frame->skb_std;
		goto create_tagged_next;
	}
#endif

	/* Create the new skb with enough headroom to fit the HSR tag */
	skb = __pskb_copy(frame->skb_std,
			  skb_headroom(frame->skb_std) + HSR_HLEN, GFP_ATOMIC);
	if (!skb)
		return NULL;
	skb_reset_mac_header(skb);

#ifdef CONFIG_KSZ_SWITCH
create_tagged_next:
#endif

	if (skb->ip_summed == CHECKSUM_PARTIAL)
		skb->csum_start += HSR_HLEN;

	movelen = ETH_HLEN;
	if (frame->is_vlan)
		movelen += VLAN_HLEN;

	src = skb_mac_header(skb);
	dst = skb_push(skb, HSR_HLEN);
	memmove(dst, src, movelen);
	skb_reset_mac_header(skb);

	/* skb_put_padto free skb on error and hsr_fill_tag returns NULL in
	 * that case
	 */
	return hsr_fill_tag(skb, frame, port, port->hsr->prot_version);
}

#ifdef CONFIG_KSZ_SWITCH
static
#endif
struct sk_buff *prp_create_tagged_frame(struct hsr_frame_info *frame,
					struct hsr_port *port)
{
	struct sk_buff *skb;

	if (frame->skb_prp) {
		struct prp_rct *trailer = skb_get_PRP_rct(frame->skb_prp);

		if (trailer) {
			prp_set_lan_id(trailer, port);
		} else {
			WARN_ONCE(!trailer, "errored PRP skb");
			return NULL;
		}
		return skb_clone(frame->skb_prp, GFP_ATOMIC);
	} else if (port->dev->features & NETIF_F_HW_HSR_TAG_INS) {
		return skb_clone(frame->skb_std, GFP_ATOMIC);
	}

	skb = skb_copy_expand(frame->skb_std, 0,
			      skb_tailroom(frame->skb_std) + HSR_HLEN,
			      GFP_ATOMIC);
	prp_fill_rct(skb, frame, port);

	return skb;
}

#ifndef CONFIG_KSZ_SWITCH
static void hsr_deliver_master(struct sk_buff *skb, struct net_device *dev,
			       struct hsr_node *node_src)
{
	bool was_multicast_frame;
	int res, recv_len;

	was_multicast_frame = (skb->pkt_type == PACKET_MULTICAST);
	hsr_addr_subst_source(node_src, skb);
	skb_pull(skb, ETH_HLEN);
	recv_len = skb->len;
	res = netif_rx(skb);
	if (res == NET_RX_DROP) {
		dev->stats.rx_dropped++;
	} else {
		dev->stats.rx_packets++;
		dev->stats.rx_bytes += recv_len;
		if (was_multicast_frame)
			dev->stats.multicast++;
	}
}

static int hsr_xmit(struct sk_buff *skb, struct hsr_port *port,
		    struct hsr_frame_info *frame)
{
	if (frame->port_rcv->type == HSR_PT_MASTER) {
		hsr_addr_subst_dest(frame->node_src, skb, port);

		/* Address substitution (IEC62439-3 pp 26, 50): replace mac
		 * address of outgoing frame with that of the outgoing slave's.
		 */
		ether_addr_copy(eth_hdr(skb)->h_source, port->dev->dev_addr);
	}
	return dev_queue_xmit(skb);
}
#endif

#ifdef CONFIG_KSZ_SWITCH
static
#endif
bool prp_drop_frame(struct hsr_frame_info *frame, struct hsr_port *port)
{
	return ((frame->port_rcv->type == HSR_PT_SLAVE_A &&
		 port->type ==  HSR_PT_SLAVE_B) ||
		(frame->port_rcv->type == HSR_PT_SLAVE_B &&
		 port->type ==  HSR_PT_SLAVE_A));
}

#ifdef CONFIG_KSZ_SWITCH
static
#endif
bool hsr_drop_frame(struct hsr_frame_info *frame, struct hsr_port *port)
{
#ifdef CONFIG_KSZ_SWITCH
	struct ksz_hsr_info *info =
		container_of(port->hsr, struct ksz_hsr_info, hsr);

	if (!info->fwd_lane_b)
		return prp_drop_frame(frame, port);
#endif
	if (port->dev->features & NETIF_F_HW_HSR_FWD)
		return prp_drop_frame(frame, port);

	return false;
}

#ifdef CONFIG_KSZ_SWITCH
static void hsr_fwd_host(struct ksz_hsr_info *info,
			 struct hsr_frame_info *frame,
			 struct hsr_port *port)
{
	struct hsr_priv *hsr = port->hsr;
	struct sk_buff *skb;

	/* Don't send frame over port where it has been sent before.
	 * Also fro SAN, this shouldn't be done.
	 */
	if (!frame->is_from_san &&
	    hsr_register_frame_out(port, frame->node_src,
				   frame->sequence_nr))
		return;

	if (frame->is_supervision) {
		hsr_handle_sup_frame(frame);
#ifdef CONFIG_KSZ_SWITCH
		frame->out = 0;
#ifdef CONFIG_HAVE_HSR_HW
		if (!info->check) {
			struct ksz_sw *sw = info->sw_dev;

			/* No HSR hardware. */
			if (!(sw->features & REDUNDANCY_SUPPORT))
				return;
			info->check = 1;
			schedule_delayed_work(&info->chk_ring,
					      msecs_to_jiffies(50));
		}
#endif
#endif
		return;
	}

	skb = hsr->proto_ops->get_untagged_frame(frame, port);
	if (!skb) {
		frame->port_rcv->dev->stats.rx_dropped++;
		return;
	}
	skb->dev = port->dev;

	/* Always use the first address of the node. */
	if (!frame->node_src->is_same_addr)
		hsr_addr_subst_source(frame->node_src, skb);
}

static void hsr_fwd_interlink(struct ksz_hsr_info *info,
			      struct hsr_frame_info *frame,
			      struct hsr_port *port)
{
	struct hsr_priv *hsr = port->hsr;
	struct sk_buff *skb;

	skb = hsr->proto_ops->get_untagged_frame(frame, port);
	if (!skb) {
		return;
	}
	if (frame->port_rcv->type == HSR_PT_MASTER) {
if (skb != frame->skb_out)
dbg_msg(" not out\n");
	}

	/* Forward to Redbox. */
	if (frame->port_rcv->type != HSR_PT_MASTER ||
	    skb != frame->skb_out) {
		struct net_device **dev = (struct net_device **)skb->cb;

		*dev = info->redbox;
		skb->dev = port->dev;
		proc_hsr_tx(info, skb);
	} else {
		frame->out = 4;
	}
}

static void hsr_fwd_port(struct ksz_hsr_info *info,
			 struct hsr_frame_info *frame,
			 struct hsr_port *port)
{
	struct hsr_priv *hsr = port->hsr;
	struct sk_buff *skb;

	/* Don't send frame over port where it has been sent before.
	 * Also fro SAN, this shouldn't be done.
	 */
	if (!frame->is_from_san &&
	    hsr_register_frame_out(port, frame->node_src,
				   frame->sequence_nr))
		return;

	skb = hsr->proto_ops->create_tagged_frame(frame, port);
	if (!skb) {
		return;
	}

	skb->dev = port->dev;
	if (port->type == HSR_PT_SLAVE_A) {
		if (frame->port_rcv->type == HSR_PT_MASTER) {
			char forward;

			/* Default is to send to both ports. */
			forward = 3;
			if (info->use_lane_b)
				forward = 1;

			if (!frame->node_dst ||
			    frame->node_dst->is_same_addr) {
				/* No need to send to lane B. */
				if (!info->use_lane_b)
					info->fwd_lane_a = true;
			} else {
				forward = 1;
			}
			frame->out = forward;
			if (skb != frame->skb_out) {
				skb->vlan_tci = forward;
				proc_hsr_tx(info, skb);
			}


		} else {
			skb->vlan_tci = 1;
			proc_hsr_tx(info, skb);
		}
	} else if (port->type == HSR_PT_SLAVE_B) {
		if (frame->port_rcv->type == HSR_PT_MASTER &&
		    frame->node_dst) {
			ether_addr_copy(eth_hdr(skb)->h_dest,
					frame->node_dst->macaddress_B);
		}
		skb->vlan_tci = 2;
		proc_hsr_tx(info, skb);
	}
}
#endif

/* Forward the frame through all devices except:
 * - Back through the receiving device
 * - If it's a HSR frame: through a device where it has passed before
 * - if it's a PRP frame: through another PRP slave device (no bridge)
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
#ifndef CONFIG_KSZ_SWITCH
	struct hsr_port *port;
	struct sk_buff *skb;
	bool sent = false;
#endif
#ifdef CONFIG_KSZ_SWITCH
	struct hsr_port *host, *interlink, *portA, *portB;
	struct hsr_port *from = frame->port_rcv;
	struct ksz_hsr_info *info;

	info = container_of(from->hsr, struct ksz_hsr_info, hsr);

	interlink = info->hsr_ports[HSR_PT_INTERLINK];
	portA = info->hsr_ports[HSR_PT_SLAVE_A];
	portB = info->hsr_ports[HSR_PT_SLAVE_B];
	host = info->hsr_ports[HSR_PT_MASTER];

	info->fwd_lane_a = false;

	/* Coming from host. */
	if (from->type == HSR_PT_MASTER) {
		/* Process Redbox first to re-use skb_std. */
		if (frame->is_redbox_dest)
			hsr_fwd_interlink(info, frame, interlink);

		/* Only master port can send to HSR device because of
		 * sequence_nr lock.
		 */
		if (frame->is_hsr_dest) {
			hsr_fwd_port(info, frame, portA);
			if (info->use_lane_b)
				hsr_fwd_port(info, frame, portB);
		}
	} else if (from->type == HSR_PT_INTERLINK) {
		/* Don't deliver locally unless we should */
		if (frame->is_local_dest)
			hsr_fwd_host(info, frame, host);
		if (frame->is_hsr_dest && info->redbox_fwd) {
			struct net_device **dev;
			struct sk_buff *skb;

			if (!frame->skb_out) {
				frame->skb_out = frame->skb_std;
				skb = frame->skb_std;
			} else {
dbg_msg(" new in\n");
				skb = __pskb_copy(frame->skb_std,
						  skb_headroom(frame->skb_std) +
						  HSR_HLEN, GFP_ATOMIC);
				if (!skb)
					goto fwd_exit;
				skb_reset_mac_header(skb);
			}

			/* Replace source MAC address. */
			ether_addr_copy(eth_hdr(skb)->h_source,
					info->src_addr);

			/* Cannot send to HSR device here because the sequence
			 * number cannot be be guaranteed to be sequential in
			 * the send order.
			 */
			dev = (struct net_device **)skb->cb;
			*dev = info->dev;
			proc_hsr_tx(info, skb);
		}
	} else {
		/* Don't deliver locally unless we should */
		if (frame->is_local_dest)
			hsr_fwd_host(info, frame, host);
		if (frame->is_redbox_dest)
			hsr_fwd_interlink(info, frame, interlink);
#if 0
		if (frame->is_hsr_dest) {
			struct hsr_priv *hsr = from->hsr;
			struct hsr_port *port;

			if (from->type == HSR_PT_SLAVE_A)
				port = portB;
			else
				port = portA;
#if 1
			/* Check if frame is to be dropped. Eg. for PRP no
			 * forward between ports.
			 */
			if (hsr->proto_ops->drop_frame &&
			    hsr->proto_ops->drop_frame(frame, port))
				goto fwd_exit;

			hsr_fwd_port(info, frame, port);
#endif
		}
#endif
	}

fwd_exit:
	if (frame->skb_out) {
		frame->skb_std = NULL;
	}
#else
	hsr_for_each_port(frame->port_rcv->hsr, port) {
		struct hsr_priv *hsr = port->hsr;
		/* Don't send frame back the way it came */
		if (port == frame->port_rcv)
			continue;

		/* Don't deliver locally unless we should */
		if (port->type == HSR_PT_MASTER && !frame->is_local_dest)
			continue;

		/* Deliver frames directly addressed to us to master only */
		if (port->type != HSR_PT_MASTER && frame->is_local_exclusive)
			continue;

		/* If hardware duplicate generation is enabled, only send out
		 * one port.
		 */
		if ((port->dev->features & NETIF_F_HW_HSR_DUP) && sent)
			continue;

		/* Don't send frame over port where it has been sent before.
		 * Also fro SAN, this shouldn't be done.
		 */
		if (!frame->is_from_san &&
		    hsr_register_frame_out(port, frame->node_src,
					   frame->sequence_nr))
			continue;

		if (frame->is_supervision && port->type == HSR_PT_MASTER) {
			hsr_handle_sup_frame(frame);
			continue;
		}

		/* Check if frame is to be dropped. Eg. for PRP no forward
		 * between ports.
		 */
		if (hsr->proto_ops->drop_frame &&
		    hsr->proto_ops->drop_frame(frame, port))
			continue;

		if (port->type != HSR_PT_MASTER)
			skb = hsr->proto_ops->create_tagged_frame(frame, port);
		else
			skb = hsr->proto_ops->get_untagged_frame(frame, port);

		if (!skb) {
			frame->port_rcv->dev->stats.rx_dropped++;
			continue;
		}

		skb->dev = port->dev;
		if (port->type == HSR_PT_MASTER) {
			hsr_deliver_master(skb, port->dev, frame->node_src);
		} else {
			if (!hsr_xmit(skb, port, frame))
				sent = true;
		}
	}
#endif
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

	if (skb->pkt_type == PACKET_HOST ||
	    skb->pkt_type == PACKET_MULTICAST ||
	    skb->pkt_type == PACKET_BROADCAST) {
		frame->is_local_dest = true;
	} else {
		frame->is_local_dest = false;
	}
}

static void handle_std_frame(struct sk_buff *skb,
			     struct hsr_frame_info *frame)
{
	struct hsr_port *port = frame->port_rcv;
	struct hsr_priv *hsr = port->hsr;

	frame->skb_hsr = NULL;
	frame->skb_prp = NULL;
	frame->skb_std = skb;

	if (port->type != HSR_PT_MASTER) {
		frame->is_from_san = true;
	} else {
		/* Sequence nr for the master node */
		lockdep_assert_held(&hsr->seqnr_lock);
		frame->sequence_nr = hsr->sequence_nr;
		hsr->sequence_nr++;
	}
}

#ifdef CONFIG_KSZ_SWITCH
static
#endif
int hsr_fill_frame_info(__be16 proto, struct sk_buff *skb,
			struct hsr_frame_info *frame)
{
	struct hsr_port *port = frame->port_rcv;
	struct hsr_priv *hsr = port->hsr;

	/* HSRv0 supervisory frames double as a tag so treat them as tagged. */
	if ((!hsr->prot_version && proto == htons(ETH_P_PRP)) ||
	    proto == htons(ETH_P_HSR)) {
#ifndef CONFIG_KSZ_SWITCH
		/* Check if skb contains hsr_ethhdr */
		if (skb->mac_len < sizeof(struct hsr_ethhdr))
			return -EINVAL;
#endif

		/* HSR tagged frame :- Data or Supervision */
		frame->skb_std = NULL;
		frame->skb_prp = NULL;
		frame->skb_hsr = skb;
		frame->sequence_nr = hsr_get_skb_sequence_nr(skb);
		return 0;
	}

	/* Standard frame or PRP from master port */
	handle_std_frame(skb, frame);

	return 0;
}

#ifdef CONFIG_KSZ_SWITCH
static
#endif
int prp_fill_frame_info(__be16 proto, struct sk_buff *skb,
			struct hsr_frame_info *frame)
{
	/* Supervision frame */
	struct prp_rct *rct = skb_get_PRP_rct(skb);

	if (rct &&
	    prp_check_lsdu_size(skb, rct, frame->is_supervision)) {
		frame->skb_hsr = NULL;
		frame->skb_std = NULL;
		frame->skb_prp = skb;
		frame->sequence_nr = prp_get_skb_sequence_nr(rct);
		return 0;
	}
	handle_std_frame(skb, frame);

	return 0;
}

static int fill_frame_info(struct hsr_frame_info *frame,
			   struct sk_buff *skb, struct hsr_port *port)
{
	struct hsr_priv *hsr = port->hsr;
	struct hsr_vlan_ethhdr *vlan_hdr;
	struct ethhdr *ethhdr;
	__be16 proto;
	int ret;
#ifdef CONFIG_KSZ_SWITCH
	struct ksz_hsr_info *info = container_of(hsr,
		struct ksz_hsr_info, hsr);
	struct net_device **dev = (struct net_device **)skb->cb;
#endif

#ifndef CONFIG_KSZ_SWITCH
	/* Check if skb contains ethhdr */
	if (skb->mac_len < sizeof(struct ethhdr))
		return -EINVAL;
#endif

	memset(frame, 0, sizeof(*frame));
	frame->is_supervision = is_supervision_frame(port->hsr, skb);
	frame->node_src = hsr_get_node(port, &hsr->node_db, skb,
				       frame->is_supervision,
				       port->type);
	if (!frame->node_src)
		return -1; /* Unknown node and !is_supervision, or no mem */

	ethhdr = (struct ethhdr *)skb_mac_header(skb);
	frame->is_vlan = false;
	proto = ethhdr->h_proto;

	if (proto == htons(ETH_P_8021Q))
		frame->is_vlan = true;

	if (frame->is_vlan) {
		vlan_hdr = (struct hsr_vlan_ethhdr *)ethhdr;
		proto = vlan_hdr->vlanhdr.h_vlan_encapsulated_proto;
		/* FIXME: */
		netdev_warn_once(skb->dev, "VLAN not yet supported");
	}

	frame->is_from_san = false;
	frame->port_rcv = port;
	ret = hsr->proto_ops->fill_frame_info(proto, skb, frame);
	if (ret)
		return ret;

	check_local_dest(port->hsr, skb, frame);

#ifdef CONFIG_KSZ_SWITCH
	frame->out = 0;
	frame->skb_out = NULL;
	frame->node_dst = NULL;
	frame->is_hsr_dest = false;
	frame->is_hsr_exclusive = false;
	frame->is_redbox_dest = false;
	frame->is_redbox_exclusive = false;
	frame->fwd_hsr = false;
	if (info->use_lane_b || info->fwd_lane_b)
		frame->fwd_hsr = true;

	/* Frame is sent to HSR device directly. */
	if (*dev == info->dev) {
		frame->is_hsr_dest = true;
		frame->is_hsr_exclusive = true;
		return 0;
	}

	/* Not unicast frame addressed to host. */
	if (!frame->is_local_exclusive) {

		/* May need to change address for lane B. */
		frame->node_dst = hsr_addr_chk_dest(port->hsr, skb);

		/* Need to forward to HSR device. */
		if (info->hsr_up &&
		    (!frame->node_dst || !frame->node_dst->slave)) {
			if (port->type == HSR_PT_MASTER ||
			    port->type == HSR_PT_INTERLINK) {
				frame->is_hsr_dest = true;
				if (frame->node_dst &&
				    !frame->node_dst->slave)
					frame->is_hsr_exclusive = true;
			} else if (info->fwd_lane_b) {
				frame->is_hsr_dest = true;
			}

			/* Do not forward to host. */
			if (frame->is_hsr_exclusive)
				frame->is_local_dest = false;

			/* Do not forward to Redbox for code below. */
			if (frame->is_supervision)
				frame->is_hsr_exclusive = true;
		}

		/* Forward to Redbox if supported. */
		if (port->type != HSR_PT_INTERLINK &&
		    info->redbox_fwd && info->redbox_up &&
		    !frame->is_hsr_exclusive) {
			frame->is_redbox_dest = true;
			if ((frame->node_dst && frame->node_dst->slave))
				frame->is_redbox_exclusive = true;
			else if (!frame->is_hsr_dest)
				frame->is_redbox_exclusive = true;

			/* Do not forward to host. */
			if (frame->is_redbox_exclusive)
				frame->is_local_dest = false;
		}
	}

	/* Host is processing received frame. */
	if (frame->is_local_dest)
		frame->out = 1;
#endif

	return 0;
}

/* Must be called holding rcu read lock (because of the port parameter) */
#ifdef CONFIG_KSZ_SWITCH
static
int hsr_forward_skb(struct sk_buff *skb, struct hsr_port *port)
#else
void hsr_forward_skb(struct sk_buff *skb, struct hsr_port *port)
#endif
{
	struct hsr_frame_info frame;

	rcu_read_lock();
	if (fill_frame_info(&frame, skb, port) < 0)
		goto out_drop;

	hsr_register_frame_in(frame.node_src, port, frame.sequence_nr);
	hsr_forward_do(&frame);
	rcu_read_unlock();
#ifndef CONFIG_KSZ_SWITCH
	/* Gets called for ingress frames as well as egress from master port.
	 * So check and increment stats for master port only here.
	 */
	if (port->type == HSR_PT_MASTER) {
		port->dev->stats.tx_packets++;
		port->dev->stats.tx_bytes += skb->len;
	}
#endif

	kfree_skb(frame.skb_hsr);
	kfree_skb(frame.skb_prp);
	kfree_skb(frame.skb_std);
#ifdef CONFIG_KSZ_SWITCH
	/* No outcome to process. */
	if (!frame.skb_out)
		return 0;
	return frame.out;
#else
	return;
#endif

out_drop:
dbg_msg("drop\n");
	rcu_read_unlock();
	port->dev->stats.tx_dropped++;
	kfree_skb(skb);
#ifdef CONFIG_KSZ_SWITCH
	return 0;
#endif
}
/* hsr_forward */

/* hsr_debugfs */
#if IS_ENABLED(CONFIG_DEBUG_FS)

static struct dentry *hsr_debugfs_root_dir;

/* hsr_node_table_show - Formats and prints node_table entries */
static int
hsr_node_table_show(struct seq_file *sfp, void *data)
{
	struct hsr_priv *priv = (struct hsr_priv *)sfp->private;
	struct hsr_node *node;

	seq_printf(sfp, "Node Table entries for (%s) device\n",
		   (priv->prot_version == PRP_V1 ? "PRP" : "HSR"));
	seq_puts(sfp, "MAC-Address-A,    MAC-Address-B,    time_in[A], ");
	seq_puts(sfp, "time_in[B], Address-B port, ");
	if (priv->prot_version == PRP_V1)
		seq_puts(sfp, "SAN-A, SAN-B, DAN-P\n");
	else
		seq_puts(sfp, "DAN-H\n");

	rcu_read_lock();
	list_for_each_entry_rcu(node, &priv->node_db, mac_list) {
		/* skip self node */
		if (hsr_addr_is_self(priv, node->macaddress_A))
			continue;
		seq_printf(sfp, "%pM ", &node->macaddress_A[0]);
		seq_printf(sfp, "%pM ", &node->macaddress_B[0]);
		seq_printf(sfp, "%10lx, ", node->time_in[HSR_PT_SLAVE_A]);
		seq_printf(sfp, "%10lx, ", node->time_in[HSR_PT_SLAVE_B]);
		seq_printf(sfp, "%14x, ", node->addr_B_port);

		if (priv->prot_version == PRP_V1)
			seq_printf(sfp, "%5x, %5x, %5x\n",
				   node->san_a, node->san_b,
				   (node->san_a == 0 && node->san_b == 0));
		else
			seq_printf(sfp, "%5x\n", 1);
	}
	rcu_read_unlock();
	return 0;
}

DEFINE_SHOW_ATTRIBUTE(hsr_node_table);

#ifndef CONFIG_KSZ_SWITCH
void hsr_debugfs_rename(struct net_device *dev)
{
	struct hsr_priv *priv = netdev_priv(dev);
	struct dentry *d;

	d = debugfs_rename(hsr_debugfs_root_dir, priv->node_tbl_root,
			   hsr_debugfs_root_dir, dev->name);
	if (IS_ERR(d))
		netdev_warn(dev, "failed to rename\n");
	else
		priv->node_tbl_root = d;
}
#endif

/* hsr_debugfs_init - create hsr node_table file for dumping
 * the node table
 *
 * Description:
 * When debugfs is configured this routine sets up the node_table file per
 * hsr device for dumping the node_table entries
 */
#ifdef CONFIG_KSZ_SWITCH
static
#endif
void hsr_debugfs_init(struct hsr_priv *priv, struct net_device *hsr_dev)
{
	struct dentry *de = NULL;

	de = debugfs_create_dir(hsr_dev->name, hsr_debugfs_root_dir);
	if (IS_ERR(de)) {
		pr_err("Cannot create hsr debugfs directory\n");
		return;
	}

	priv->node_tbl_root = de;

	de = debugfs_create_file("node_table", S_IFREG | 0444,
				 priv->node_tbl_root, priv,
				 &hsr_node_table_fops);
	if (IS_ERR(de)) {
		pr_err("Cannot create hsr node_table file\n");
		debugfs_remove(priv->node_tbl_root);
		priv->node_tbl_root = NULL;
		return;
	}
}

/* hsr_debugfs_term - Tear down debugfs intrastructure
 *
 * Description:
 * When Debugfs is configured this routine removes debugfs file system
 * elements that are specific to hsr
 */
#ifdef CONFIG_KSZ_SWITCH
static
#endif
void
hsr_debugfs_term(struct hsr_priv *priv)
{
	debugfs_remove_recursive(priv->node_tbl_root);
	priv->node_tbl_root = NULL;
}

#ifdef CONFIG_KSZ_SWITCH
static
#endif
void hsr_debugfs_create_root(void)
{
	hsr_debugfs_root_dir = debugfs_create_dir("hsr", NULL);
	if (IS_ERR(hsr_debugfs_root_dir)) {
		pr_err("Cannot create hsr debugfs root directory\n");
		hsr_debugfs_root_dir = NULL;
	}
}

#ifdef CONFIG_KSZ_SWITCH
static
#endif
void hsr_debugfs_remove_root(void)
{
	/* debugfs_remove() internally checks NULL and ERROR */
	debugfs_remove(hsr_debugfs_root_dir);
}
#endif

/* hsr_device */
static bool is_admin_up(struct net_device *dev)
{
	return dev && (dev->flags & IFF_UP);
}

#ifndef CONFIG_KSZ_SWITCH
static bool is_slave_up(struct net_device *dev)
{
	return dev && is_admin_up(dev) && netif_oper_up(dev);
}

static void __hsr_set_operstate(struct net_device *dev, int transition)
{
	write_lock(&dev_base_lock);
	if (dev->operstate != transition) {
		dev->operstate = transition;
		write_unlock(&dev_base_lock);
		netdev_state_change(dev);
	} else {
		write_unlock(&dev_base_lock);
	}
}

static void hsr_set_operstate(struct hsr_port *master, bool has_carrier)
{
	if (!is_admin_up(master->dev)) {
		__hsr_set_operstate(master->dev, IF_OPER_DOWN);
		return;
	}

	if (has_carrier)
		__hsr_set_operstate(master->dev, IF_OPER_UP);
	else
		__hsr_set_operstate(master->dev, IF_OPER_LOWERLAYERDOWN);
}

static bool hsr_check_carrier(struct hsr_port *master)
{
	struct hsr_port *port;

	ASSERT_RTNL();

	hsr_for_each_port(master->hsr, port) {
		if (port->type != HSR_PT_MASTER && is_slave_up(port->dev)) {
			netif_carrier_on(master->dev);
			return true;
		}
	}

	netif_carrier_off(master->dev);

	return false;
}
#endif

#ifdef CONFIG_KSZ_SWITCH
static void hsr_check_announce(struct ksz_hsr_info *info)
{
	struct hsr_priv *hsr = &info->hsr;
	int state;

	if (info->state < 0)
		return;
	state = netif_running(info->dev) && info->hsr_up;
	if (state != info->state) {
dbg_msg("%s %d %d\n", __func__, info->state, state);
		if (state)
			mod_timer(&hsr->announce_timer,
				  jiffies + msecs_to_jiffies(1));
		else
			del_timer(&hsr->announce_timer);
		info->state = state;
	}
}
#else
static void hsr_check_announce(struct net_device *hsr_dev,
			       unsigned char old_operstate)
{
	struct hsr_priv *hsr;

	hsr = netdev_priv(hsr_dev);

	if (hsr_dev->operstate == IF_OPER_UP && old_operstate != IF_OPER_UP) {
		/* Went up */
		hsr->announce_count = 0;
		mod_timer(&hsr->announce_timer,
			  jiffies + msecs_to_jiffies(HSR_ANNOUNCE_INTERVAL));
	}

	if (hsr_dev->operstate != IF_OPER_UP && old_operstate == IF_OPER_UP)
		/* Went down */
		del_timer(&hsr->announce_timer);
}
#endif

#ifndef CONFIG_KSZ_SWITCH
void hsr_check_carrier_and_operstate(struct hsr_priv *hsr)
{
	struct hsr_port *master;
	unsigned char old_operstate;
	bool has_carrier;

	master = hsr_port_get_hsr(hsr, HSR_PT_MASTER);
	/* netif_stacked_transfer_operstate() cannot be used here since
	 * it doesn't set IF_OPER_LOWERLAYERDOWN (?)
	 */
	old_operstate = master->dev->operstate;
	has_carrier = hsr_check_carrier(master);
	hsr_set_operstate(master, has_carrier);
	hsr_check_announce(master->dev, old_operstate);
}

int hsr_get_max_mtu(struct hsr_priv *hsr)
{
	unsigned int mtu_max;
	struct hsr_port *port;

	mtu_max = ETH_DATA_LEN;
	hsr_for_each_port(hsr, port)
		if (port->type != HSR_PT_MASTER)
			mtu_max = min(port->dev->mtu, mtu_max);

	if (mtu_max < HSR_HLEN)
		return 0;
	return mtu_max - HSR_HLEN;
}

static int hsr_dev_change_mtu(struct net_device *dev, int new_mtu)
{
	struct hsr_priv *hsr;

	hsr = netdev_priv(dev);

	if (new_mtu > hsr_get_max_mtu(hsr)) {
		netdev_info(dev, "A HSR master's MTU cannot be greater than the smallest MTU of its slaves minus the HSR Tag length (%d octets).\n",
			    HSR_HLEN);
		return -EINVAL;
	}

	dev->mtu = new_mtu;

	return 0;
}

static int hsr_dev_open(struct net_device *dev)
{
	struct hsr_priv *hsr;
	struct hsr_port *port;
	char designation;

	hsr = netdev_priv(dev);
	designation = '\0';

	hsr_for_each_port(hsr, port) {
		if (port->type == HSR_PT_MASTER)
			continue;
		switch (port->type) {
		case HSR_PT_SLAVE_A:
			designation = 'A';
			break;
		case HSR_PT_SLAVE_B:
			designation = 'B';
			break;
		default:
			designation = '?';
		}
		if (!is_slave_up(port->dev))
			netdev_warn(dev, "Slave %c (%s) is not up; please bring it up to get a fully working HSR network\n",
				    designation, port->dev->name);
	}

	if (designation == '\0')
		netdev_warn(dev, "No slave devices configured\n");

	return 0;
}

static int hsr_dev_close(struct net_device *dev)
{
	/* Nothing to do here. */
	return 0;
}

static netdev_features_t hsr_features_recompute(struct hsr_priv *hsr,
						netdev_features_t features)
{
	netdev_features_t mask;
	struct hsr_port *port;

	mask = features;

	/* Mask out all features that, if supported by one device, should be
	 * enabled for all devices (see NETIF_F_ONE_FOR_ALL).
	 *
	 * Anything that's off in mask will not be enabled - so only things
	 * that were in features originally, and also is in NETIF_F_ONE_FOR_ALL,
	 * may become enabled.
	 */
	features &= ~NETIF_F_ONE_FOR_ALL;
	hsr_for_each_port(hsr, port)
		features = netdev_increment_features(features,
						     port->dev->features,
						     mask);

	return features;
}

static netdev_features_t hsr_fix_features(struct net_device *dev,
					  netdev_features_t features)
{
	struct hsr_priv *hsr = netdev_priv(dev);

	return hsr_features_recompute(hsr, features);
}
#endif

#ifdef CONFIG_KSZ_SWITCH
static netdev_tx_t hsr_dev_xmit(struct sk_buff *skb, struct net_device *dev)
{
	const struct net_device_ops *ops = dev->netdev_ops;
	netdev_tx_t rc;

	rc = ops->ndo_start_xmit(skb, skb->dev);
	if (NETDEV_TX_BUSY == rc) {
		dev_kfree_skb_any(skb);
	}
	return rc;
}

static int hsr_xmit(struct ksz_hsr_info *info)
{
	struct net_device **dev;
	struct sk_buff *skb;
	int len = info->len;

	/* Do not send if network device is not ready. */
	if (!netif_running(info->dev) || !info->hsr_up)
		return 0;

	/* Add extra for tail tagging. */
	skb = dev_alloc_skb(len + 4 + 8);
	if (!skb)
		return -ENOMEM;

	memcpy(skb->data, info->tx_frame, len);
	skb_reset_mac_header(skb);
	skb_set_network_header(skb, ETH_HLEN);

	skb_put(skb, len);
	skb->protocol = htons(ETH_P_PRP);
	skb->dev = info->dev;
	dev = (struct net_device **)skb->cb;
	*dev = info->dev;
	return hsr_dev_xmit(skb, skb->dev);
}  /* hsr_xmit */
#else
static netdev_tx_t hsr_dev_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct hsr_priv *hsr = netdev_priv(dev);
	struct hsr_port *master;

	master = hsr_port_get_hsr(hsr, HSR_PT_MASTER);
	if (master) {
		skb->dev = master->dev;
		skb_reset_mac_header(skb);
		skb_reset_mac_len(skb);
		spin_lock_bh(&hsr->seqnr_lock);
		hsr_forward_skb(skb, master);
		spin_unlock_bh(&hsr->seqnr_lock);
	} else {
		dev_core_stats_tx_dropped_inc(dev);
		dev_kfree_skb_any(skb);
	}
	return NETDEV_TX_OK;
}
#endif

static const struct header_ops hsr_header_ops = {
	.create	 = eth_header,
	.parse	 = eth_header_parse,
};

static struct sk_buff *hsr_init_skb(struct hsr_port *master)
{
	struct hsr_priv *hsr = master->hsr;
	struct sk_buff *skb;
	int hlen, tlen;

	hlen = LL_RESERVED_SPACE(master->dev);
	tlen = master->dev->needed_tailroom;
	/* skb size is same for PRP/HSR frames, only difference
	 * being, for PRP it is a trailer and for HSR it is a
	 * header
	 */
	skb = dev_alloc_skb(sizeof(struct hsr_sup_tag) +
			    sizeof(struct hsr_sup_payload) + hlen + tlen);

	if (!skb)
		return skb;

	skb_reserve(skb, hlen);
	skb->dev = master->dev;
	skb->priority = TC_PRIO_CONTROL;

	if (dev_hard_header(skb, skb->dev, ETH_P_PRP,
			    hsr->sup_multicast_addr,
			    skb->dev->dev_addr, skb->len) <= 0)
		goto out;

	skb_reset_mac_header(skb);
	skb_reset_mac_len(skb);
	skb_reset_network_header(skb);
	skb_reset_transport_header(skb);

	return skb;
out:
	kfree_skb(skb);

	return NULL;
}

#ifdef CONFIG_KSZ_SWITCH
static void prep_hsr_supervision_frame(struct ksz_hsr_info *info)
{
	int len;
	int tlen;
	struct hsr_port *master;
	struct hsr_priv *hsr;
	struct hsr_sup_tag *hsr_stag;
	struct hsr_sup_tlv *hsr_stype;
	struct hsr_sup_payload *hsr_sp;
	struct ethhdr *eth = (struct ethhdr *) info->master_sup_frame;

	master = hsr_port_get_hsr(&info->hsr, HSR_PT_MASTER);
	hsr = master->hsr;

	memcpy(eth->h_dest, hsr->sup_multicast_addr, ETH_ALEN);
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
	set_hsr_stag_path(hsr_stag, (hsr->prot_version ? 0x0 : 0xf));
	set_hsr_stag_HSR_ver(hsr_stag, hsr->prot_version);
	len += sizeof(struct hsr_sup_tag);

	hsr_stype = &hsr_stag->tlv;
	hsr_stype->HSR_TLV_type = HSR_TLV_LIFE_CHECK;
	hsr_stype->HSR_TLV_length = 6;
	len += sizeof(struct hsr_sup_tlv);

	/* Payload: MacAddressA */
	hsr_sp = (struct hsr_sup_payload *)(hsr_stype + 1);
	ether_addr_copy(hsr_sp->macaddress_A, info->src_addr);
	len += sizeof(struct hsr_sup_payload);

	/* Last TLV */
	hsr_stype = (struct hsr_sup_tlv *)(hsr_sp + 1);
	hsr_stype->HSR_TLV_type = 0;
	hsr_stype->HSR_TLV_length = 0;
	len += sizeof(struct hsr_sup_tlv);
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
	struct hsr_priv *hsr;
	struct hsr_sup_tag *hsr_stag;
	struct hsr_sup_tlv *hsr_stype;
	struct hsr_sup_payload *hsr_sp;
	struct ethhdr *eth = (struct ethhdr *) info->slave_sup_frame;

	master = hsr_port_get_hsr(&info->hsr, HSR_PT_MASTER);
	hsr = master->hsr;

	memcpy(eth->h_dest, hsr->sup_multicast_addr, ETH_ALEN);
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
	set_hsr_stag_path(hsr_stag, (hsr->prot_version ? 0x0 : 0xf));
	set_hsr_stag_HSR_ver(hsr_stag, hsr->prot_version);
	len += sizeof(struct hsr_sup_tag);

	hsr_stype = &hsr_stag->tlv;
	hsr_stype->HSR_TLV_type = HSR_TLV_LIFE_CHECK;
	hsr_stype->HSR_TLV_length = 6;
	len += sizeof(struct hsr_sup_tlv);

	/* Payload: MacAddressA */
	hsr_sp = (struct hsr_sup_payload *)(hsr_stype + 1);
	len += sizeof(struct hsr_sup_payload);

	/* Insert RedBox MAC address if available. */
	hsr_stype = (struct hsr_sup_tlv *)(hsr_sp + 1);
	hsr_stype->HSR_TLV_type = PRP_TLV_REDBOX_MAC;
	hsr_stype->HSR_TLV_length = 6;
	len += sizeof(struct hsr_sup_tlv);

	hsr_sp = (struct hsr_sup_payload *)(hsr_stype + 1);
	ether_addr_copy(hsr_sp->macaddress_A, info->redbox->dev_addr);

	/* Cannot have different source MAC address. */
	ether_addr_copy(hsr_sp->macaddress_A, info->src_addr);
	len += sizeof(struct hsr_sup_payload);

	/* Last TLV */
	hsr_stype = (struct hsr_sup_tlv *)(hsr_sp + 1);
	hsr_stype->HSR_TLV_type = 0;
	hsr_stype->HSR_TLV_length = 0;
	len += sizeof(struct hsr_sup_tlv);
	if (len < tlen) {
		memset(&info->slave_sup_frame[len], 0, tlen - len);
		len = tlen;
	}
	info->slave_len = len;
}  /* prep_hsr_supervision_slave_frame */
#endif

#ifdef CONFIG_KSZ_SWITCH
static void send_hsr_supervision_frame(struct hsr_port *master,
				       unsigned long *interval)
{
	struct hsr_priv *hsr = master->hsr;
	struct ksz_hsr_info *info = container_of(hsr,
		struct ksz_hsr_info, hsr);
	struct hsr_sup_tag *hsr_stag = info->hsr_stag;
	__u8 type = HSR_TLV_LIFE_CHECK;

	if (interval) {
		*interval = msecs_to_jiffies(HSR_LIFE_CHECK_INTERVAL);
		if (hsr->announce_count < 3 && hsr->prot_version == 0) {
			type = HSR_TLV_ANNOUNCE;
			*interval = msecs_to_jiffies(HSR_ANNOUNCE_INTERVAL);
			hsr->announce_count++;
		}
	}

	spin_lock_bh(&hsr->seqnr_lock);
	if (hsr->prot_version > 0) {
		hsr_stag->sequence_nr = htons(hsr->sup_sequence_nr);
		hsr->sup_sequence_nr++;
	} else {
		hsr_stag->sequence_nr = htons(hsr->sequence_nr);
		hsr->sequence_nr++;
	}
	hsr_xmit(info);
	spin_unlock_bh(&hsr->seqnr_lock);
}
#else
static void send_hsr_supervision_frame(struct hsr_port *master,
				       unsigned long *interval)
{
	struct hsr_priv *hsr = master->hsr;
	__u8 type = HSR_TLV_LIFE_CHECK;
	struct hsr_sup_payload *hsr_sp;
	struct hsr_sup_tag *hsr_stag;
	struct sk_buff *skb;

	*interval = msecs_to_jiffies(HSR_LIFE_CHECK_INTERVAL);
	if (hsr->announce_count < 3 && hsr->prot_version == 0) {
		type = HSR_TLV_ANNOUNCE;
		*interval = msecs_to_jiffies(HSR_ANNOUNCE_INTERVAL);
		hsr->announce_count++;
	}

	skb = hsr_init_skb(master);
	if (!skb) {
		WARN_ONCE(1, "HSR: Could not send supervision frame\n");
		return;
	}

	hsr_stag = skb_put(skb, sizeof(struct hsr_sup_tag));
	set_hsr_stag_path(hsr_stag, (hsr->prot_version ? 0x0 : 0xf));
	set_hsr_stag_HSR_ver(hsr_stag, hsr->prot_version);

	/* From HSRv1 on we have separate supervision sequence numbers. */
	spin_lock_bh(&hsr->seqnr_lock);
	if (hsr->prot_version > 0) {
		hsr_stag->sequence_nr = htons(hsr->sup_sequence_nr);
		hsr->sup_sequence_nr++;
	} else {
		hsr_stag->sequence_nr = htons(hsr->sequence_nr);
		hsr->sequence_nr++;
	}

	hsr_stag->tlv.HSR_TLV_type = type;
	/* TODO: Why 12 in HSRv0? */
	hsr_stag->tlv.HSR_TLV_length = hsr->prot_version ?
				sizeof(struct hsr_sup_payload) : 12;

	/* Payload: MacAddressA */
	hsr_sp = skb_put(skb, sizeof(struct hsr_sup_payload));
	ether_addr_copy(hsr_sp->macaddress_A, master->dev->dev_addr);

	if (skb_put_padto(skb, ETH_ZLEN)) {
		spin_unlock_bh(&hsr->seqnr_lock);
		return;
	}

	hsr_forward_skb(skb, master);
	spin_unlock_bh(&hsr->seqnr_lock);
	return;
}
#endif

static void send_prp_supervision_frame(struct hsr_port *master,
				       unsigned long *interval)
{
	struct hsr_priv *hsr = master->hsr;
	struct hsr_sup_payload *hsr_sp;
	struct hsr_sup_tag *hsr_stag;
	struct sk_buff *skb;

	skb = hsr_init_skb(master);
	if (!skb) {
		WARN_ONCE(1, "PRP: Could not send supervision frame\n");
		return;
	}

	*interval = msecs_to_jiffies(HSR_LIFE_CHECK_INTERVAL);
	hsr_stag = skb_put(skb, sizeof(struct hsr_sup_tag));
	set_hsr_stag_path(hsr_stag, (hsr->prot_version ? 0x0 : 0xf));
	set_hsr_stag_HSR_ver(hsr_stag, (hsr->prot_version ? 1 : 0));

	/* From HSRv1 on we have separate supervision sequence numbers. */
	spin_lock_bh(&hsr->seqnr_lock);
	hsr_stag->sequence_nr = htons(hsr->sup_sequence_nr);
	hsr->sup_sequence_nr++;
	hsr_stag->tlv.HSR_TLV_type = PRP_TLV_LIFE_CHECK_DD;
	hsr_stag->tlv.HSR_TLV_length = sizeof(struct hsr_sup_payload);

	/* Payload: MacAddressA */
	hsr_sp = skb_put(skb, sizeof(struct hsr_sup_payload));
	ether_addr_copy(hsr_sp->macaddress_A, master->dev->dev_addr);

	if (skb_put_padto(skb, ETH_ZLEN)) {
		spin_unlock_bh(&hsr->seqnr_lock);
		return;
	}

	hsr_forward_skb(skb, master);
	spin_unlock_bh(&hsr->seqnr_lock);
}

/* Announce (supervision frame) timer function
 */
static void hsr_announce(struct timer_list *t)
{
	struct hsr_priv *hsr;
	struct hsr_port *master;
	unsigned long interval;
#ifdef CONFIG_KSZ_SWITCH
	struct ksz_hsr_info *info;
	struct hsr_node *node;
#endif

	hsr = from_timer(hsr, t, announce_timer);
#ifdef CONFIG_KSZ_SWITCH
	info = container_of(hsr, struct ksz_hsr_info, hsr);
	info->tx_frame = info->master_sup_frame;
	info->len = info->master_len;
	info->hsr_stag = info->master_hsr_stag;
#endif

	rcu_read_lock();
	master = hsr_port_get_hsr(hsr, HSR_PT_MASTER);
	hsr->proto_ops->send_sv_frame(master, &interval);
#ifdef CONFIG_KSZ_SWITCH
	info->tx_frame = info->slave_sup_frame;
	info->len = info->slave_len;
	info->hsr_stag = info->slave_hsr_stag;
	list_for_each_entry_rcu(node, &hsr->node_db, mac_list) {
		struct hsr_sup_tag *hsr_stag = info->slave_hsr_stag;
		struct hsr_sup_payload *hsr_sp;
		struct hsr_sup_tlv *hsr_stype;
		struct hsr_port *port;

		if (1 != node->slave)
			continue;

		hsr_stype = &hsr_stag->tlv;
		hsr_sp = (struct hsr_sup_payload *)(hsr_stype + 1);
		ether_addr_copy(hsr_sp->macaddress_A, node->macaddress_A);
#ifndef REDBOX_NOT_SEND_SUPERVISION
		/* Update so that sequence number may not be too far apart. */
		port = hsr_port_get_hsr(hsr, HSR_PT_SLAVE_A);
		hsr_update_frame_out(port, node, hsr->sequence_nr - 1);
		hsr->proto_ops->send_sv_frame(master, NULL);
#endif
	}
#endif

	if (is_admin_up(master->dev))
		mod_timer(&hsr->announce_timer, jiffies + interval);

	rcu_read_unlock();
}

#ifdef CONFIG_KSZ_SWITCH
static
#endif
void hsr_del_ports(struct hsr_priv *hsr)
{
	struct hsr_port *port;
#ifdef CONFIG_KSZ_SWITCH
	struct ksz_hsr_info *info = container_of(hsr, struct ksz_hsr_info, hsr);
	int i;

	for (i = HSR_PT_SLAVE_A; i < HSR_PT_PORTS; i++)
		info->hsr_ports[i] = NULL;
#endif

	port = hsr_port_get_hsr(hsr, HSR_PT_SLAVE_A);
	if (port)
		hsr_del_port(port);

	port = hsr_port_get_hsr(hsr, HSR_PT_SLAVE_B);
	if (port)
		hsr_del_port(port);

	port = hsr_port_get_hsr(hsr, HSR_PT_MASTER);
	if (port)
		hsr_del_port(port);
}

#ifndef CONFIG_KSZ_SWITCH
static const struct net_device_ops hsr_device_ops = {
	.ndo_change_mtu = hsr_dev_change_mtu,
	.ndo_open = hsr_dev_open,
	.ndo_stop = hsr_dev_close,
	.ndo_start_xmit = hsr_dev_xmit,
	.ndo_fix_features = hsr_fix_features,
};

static struct device_type hsr_type = {
	.name = "hsr",
};
#endif

static struct hsr_proto_ops hsr_ops = {
	.send_sv_frame = send_hsr_supervision_frame,
	.create_tagged_frame = hsr_create_tagged_frame,
	.get_untagged_frame = hsr_get_untagged_frame,
	.drop_frame = hsr_drop_frame,
	.fill_frame_info = hsr_fill_frame_info,
	.invalid_dan_ingress_frame = hsr_invalid_dan_ingress_frame,
};

static struct hsr_proto_ops prp_ops = {
	.send_sv_frame = send_prp_supervision_frame,
	.create_tagged_frame = prp_create_tagged_frame,
	.get_untagged_frame = prp_get_untagged_frame,
	.drop_frame = prp_drop_frame,
	.fill_frame_info = prp_fill_frame_info,
	.handle_san_frame = prp_handle_san_frame,
	.update_san_info = prp_update_san_info,
};

#ifndef CONFIG_KSZ_SWITCH
void hsr_dev_setup(struct net_device *dev)
{
	eth_hw_addr_random(dev);

	ether_setup(dev);
	dev->min_mtu = 0;
	dev->header_ops = &hsr_header_ops;
	dev->netdev_ops = &hsr_device_ops;
	SET_NETDEV_DEVTYPE(dev, &hsr_type);
	dev->priv_flags |= IFF_NO_QUEUE | IFF_DISABLE_NETPOLL;

	dev->needs_free_netdev = true;

	dev->hw_features = NETIF_F_SG | NETIF_F_FRAGLIST | NETIF_F_HIGHDMA |
			   NETIF_F_GSO_MASK | NETIF_F_HW_CSUM |
			   NETIF_F_HW_VLAN_CTAG_TX;

	dev->features = dev->hw_features;

	/* Prevent recursive tx locking */
	dev->features |= NETIF_F_LLTX;
	/* VLAN on top of HSR needs testing and probably some work on
	 * hsr_header_create() etc.
	 */
	dev->features |= NETIF_F_VLAN_CHALLENGED;
	/* Not sure about this. Taken from bridge code. netdev_features.h says
	 * it means "Does not change network namespaces".
	 */
	dev->features |= NETIF_F_NETNS_LOCAL;
}
#endif

#ifndef CONFIG_KSZ_SWITCH
/* Return true if dev is a HSR master; return false otherwise.
 */
bool is_hsr_master(struct net_device *dev)
{
	return (dev->netdev_ops->ndo_start_xmit == hsr_dev_xmit);
}
EXPORT_SYMBOL(is_hsr_master);
#endif

/* Default multicast address for HSR Supervision frames */
static const unsigned char def_multicast_addr[ETH_ALEN] __aligned(2) = {
	0x01, 0x15, 0x4e, 0x00, 0x01, 0x00
};

#ifdef CONFIG_KSZ_SWITCH
static
#endif
#ifdef CONFIG_KSZ_SWITCH
int hsr_dev_finalize(struct net_device *hsr_dev, struct ksz_hsr_info *info,
#else
int hsr_dev_finalize(struct net_device *hsr_dev, struct net_device *slave[2],
#endif
		     unsigned char multicast_spec, u8 protocol_version,
		     struct netlink_ext_ack *extack)
{
#ifndef CONFIG_KSZ_SWITCH
	bool unregister = false;
#endif
	struct hsr_priv *hsr;
	int res;

#ifdef CONFIG_KSZ_SWITCH
	struct net_device *slave[2];

	hsr = &info->hsr;
	slave[0] = hsr_dev;
	slave[1] = hsr_dev;
#else
	hsr = netdev_priv(hsr_dev);
#endif
	INIT_LIST_HEAD(&hsr->ports);
	INIT_LIST_HEAD(&hsr->node_db);
	INIT_LIST_HEAD(&hsr->self_node_db);
	spin_lock_init(&hsr->list_lock);

#ifndef CONFIG_KSZ_SWITCH
	eth_hw_addr_set(hsr_dev, slave[0]->dev_addr);
#endif

	/* initialize protocol specific functions */
	if (protocol_version == PRP_V1) {
		/* For PRP, lan_id has most significant 3 bits holding
		 * the net_id of PRP_LAN_ID
		 */
		hsr->net_id = PRP_LAN_ID << 1;
		hsr->proto_ops = &prp_ops;
	} else {
		hsr->proto_ops = &hsr_ops;
	}

	/* Make sure we recognize frames from ourselves in hsr_rcv() */
	res = hsr_create_self_node(hsr, hsr_dev->dev_addr,
#ifdef CONFIG_KSZ_SWITCH
				   hsr_dev->dev_addr);
#else
				   slave[1]->dev_addr);
#endif
	if (res < 0)
		return res;

	spin_lock_init(&hsr->seqnr_lock);
	/* Overflow soon to find bugs easier: */
	hsr->sequence_nr = HSR_SEQNR_START;
	hsr->sup_sequence_nr = HSR_SUP_SEQNR_START;

	timer_setup(&hsr->announce_timer, hsr_announce, 0);
	timer_setup(&hsr->prune_timer, hsr_prune_nodes, 0);

	ether_addr_copy(hsr->sup_multicast_addr, def_multicast_addr);
	hsr->sup_multicast_addr[ETH_ALEN - 1] = multicast_spec;

	hsr->prot_version = protocol_version;

#ifndef CONFIG_KSZ_SWITCH
	/* Make sure the 1st call to netif_carrier_on() gets through */
	netif_carrier_off(hsr_dev);
#endif

	res = hsr_add_port(hsr, hsr_dev, HSR_PT_MASTER, extack);
	if (res)
		goto err_add_master;

#ifndef CONFIG_KSZ_SWITCH
	res = register_netdevice(hsr_dev);
	if (res)
		goto err_unregister;

	unregister = true;
#endif

	res = hsr_add_port(hsr, slave[0], HSR_PT_SLAVE_A, extack);
	if (res)
		goto err_unregister;

	res = hsr_add_port(hsr, slave[1], HSR_PT_SLAVE_B, extack);
	if (res)
		goto err_unregister;

#ifdef CONFIG_KSZ_SWITCH
	if (info->redbox) {
		res = hsr_add_port(hsr, info->redbox, HSR_PT_MASTER, extack);
		if (res)
			goto err_add_master;
	}

	for (res = HSR_PT_SLAVE_A; res < HSR_PT_PORTS; res++)
		info->hsr_ports[res] = hsr_port_get_hsr(hsr, res);
	hsr_debugfs_create_root();
#endif
	hsr_debugfs_init(hsr, hsr_dev);
	mod_timer(&hsr->prune_timer, jiffies + msecs_to_jiffies(PRUNE_PERIOD));

	return 0;

err_unregister:
	hsr_del_ports(hsr);
err_add_master:
	hsr_del_self_node(hsr);

#ifndef CONFIG_KSZ_SWITCH
	if (unregister)
		unregister_netdevice(hsr_dev);
#endif
	return res;
}
/* hsr_device */

#ifdef CONFIG_KSZ_SWITCH
#if 0
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
#endif

static bool hsr_chk(struct ksz_hsr_info *info, struct sk_buff *skb)
{
	struct vlan_ethhdr *vlan = (struct vlan_ethhdr *) skb->data;
	struct hsr_priv *hsr = &info->hsr;
	struct ksz_sw *sw = info->sw_dev;
	struct list_head *node_db;
	struct hsr_node *node;
	int forward;
	bool ret = false;

	if (!info->redbox_up)
		return ret;

	if (sw->info->forward & FWD_UCAST)
		forward = 1;
	else if (sw->info->forward & FWD_MCAST)
		forward = 2;
	else
		forward = 0;

	/* HSR device is not up. */
	if (!info->hsr_up)
		forward = 0;

	node_db = &hsr->node_db;
	node = find_node_by_addr_A(node_db, vlan->h_source);
	if (!node) {
		struct hsr_port *master = hsr_port_get_hsr(&info->hsr,
			HSR_PT_MASTER);
		struct hsr_sup_tag *hsr_stag = info->slave_hsr_stag;
		struct hsr_sup_payload *hsr_sp;
		struct hsr_sup_tlv *hsr_stype;

		node = hsr_add_node(hsr, node_db, vlan->h_source,
				    info->hsr.sequence_nr - 1, false,
				    false, master->type);
		if (!node)
			return ret;

		info->tx_frame = info->slave_sup_frame;
		info->len = info->slave_len;
		info->hsr_stag = info->slave_hsr_stag;

		vlan = (struct vlan_ethhdr *) info->slave_sup_frame;

		hsr_stype = &hsr_stag->tlv;
		hsr_sp = (struct hsr_sup_payload *)(hsr_stype + 1);
		ether_addr_copy(hsr_sp->macaddress_A, node->macaddress_A);
#ifndef REDBOX_NOT_SEND_SUPERVISION
		hsr->proto_ops->send_sv_frame(master, NULL);
#endif
	} else {
		struct hsr_port *port;

		/* Remove the fixed entries in MAC table. */
		if (!node->slave)
			proc_hsr_cfg(info, node->macaddress_A, 0);
		node->slave = 1;
		node->time_in[HSR_PT_SLAVE_A] = jiffies;
		node->time_in_stale[HSR_PT_SLAVE_A] = false;

		/* Update so that sequence number may not be too far apart. */
		port = hsr_port_get_hsr(&info->hsr, HSR_PT_SLAVE_A);
		hsr_update_frame_out(port, node, info->hsr.sequence_nr - 1);
	}

	/* Do not forward internally. Need software bridge. */
	if (!info->redbox_fwd)
		return ret;
	if (!forward)
		return ret;

	return true;
}  /* hsr_chk */

static void hsr_tx_proc(struct work_struct *work)
{
	struct ksz_hsr_info *info = container_of(work, struct ksz_hsr_info,
						 tx_proc);
	struct sk_buff *skb;
	bool last;

	last = skb_queue_empty(&info->txq);
	while (!last) {
		skb = skb_dequeue(&info->txq);
		last = skb_queue_empty(&info->txq);
		if (!skb)
			continue;
		hsr_dev_xmit(skb, skb->dev);
	}
}  /* hsr_tx_proc */

static int hsr_rcv(struct ksz_hsr_info *info, struct sk_buff *skb, int port)
{
	enum hsr_port_type pt = HSR_PT_PORTS;
	int hlen = ETH_HLEN + HSR_HLEN;
	struct hsr_port *from;

	if (port == info->ports[0])
		pt = HSR_PT_SLAVE_A;
	else if (port == info->ports[1])
		pt = HSR_PT_SLAVE_B;
	else if (info->redbox)
		pt = HSR_PT_INTERLINK;
	if (pt == HSR_PT_PORTS) {
		dev_kfree_skb_irq(skb);
		return 0;
	}
	if (pt == HSR_PT_INTERLINK) {
		/* Just pass the frame up. */
		if (!hsr_chk(info, skb))
			return 2;
		hlen = ETH_HLEN;
	}
	from = hsr_port_get_hsr(&info->hsr, pt);
	skb_reset_mac_header(skb);
	skb_set_network_header(skb, hlen);
	skb_reset_mac_len(skb);
	return hsr_forward_skb(skb, from);
}  /* hsr_rcv */
#endif

/* hsr_netlink */
static void hsr_dev_destroy(struct ksz_hsr_info *info)
{
	struct hsr_priv *hsr = &info->hsr;

	del_timer_sync(&hsr->prune_timer);
	del_timer_sync(&hsr->announce_timer);

	hsr_debugfs_term(hsr);
	hsr_del_ports(hsr);

	hsr_del_self_node(hsr);
	hsr_del_nodes(&hsr->node_db);

	hsr_debugfs_remove_root();
	info->state = -1;
}

static void prep_hsr_addr(struct ksz_hsr_info *info, const u8 *src)
{
	struct vlan_ethhdr *vlan = (struct vlan_ethhdr *)
		info->master_sup_frame;
	struct hsr_sup_tlv *hsr_stype;
	struct hsr_sup_payload *hsr_sp;

	memcpy(info->src_addr, src, ETH_ALEN);

	memcpy(vlan->h_source, src, ETH_ALEN);
	hsr_stype = &info->master_hsr_stag->tlv;
	hsr_sp = (struct hsr_sup_payload *)(hsr_stype + 1);
	ether_addr_copy(hsr_sp->macaddress_A, info->src_addr);
}  /* prep_hsr_addr */

static void prep_hsr_redbox_addr(struct ksz_hsr_info *info)
{
	struct vlan_ethhdr *vlan = (struct vlan_ethhdr *)
		info->slave_sup_frame;
	struct hsr_sup_tlv *hsr_stype;
	struct hsr_sup_payload *hsr_sp;

	if (!info->redbox)
		return;
	memcpy(vlan->h_source, info->src_addr, ETH_ALEN);
	hsr_stype = &info->slave_hsr_stag->tlv;
	hsr_sp = (struct hsr_sup_payload *)(hsr_stype + 1);
	hsr_stype = (struct hsr_sup_tlv *)(hsr_sp + 1);
	hsr_sp = (struct hsr_sup_payload *)(hsr_stype + 1);
	ether_addr_copy(hsr_sp->macaddress_A, info->redbox->dev_addr);
	ether_addr_copy(hsr_sp->macaddress_A, info->src_addr);
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
		if (info->redbox_vlan)
			sw->ops->cfg_mac(sw, DEV_1_ADDR_ENTRY, info->src_addr,
					 0, false, false, 0);
		prep_hsr_addr(info, dev->dev_addr);
		sw->ops->cfg_mac(sw, BRIDGE_ADDR_ENTRY, info->src_addr,
			sw->HOST_MASK, false, false, 0);
		if (info->redbox_vlan)
			sw->ops->cfg_mac(sw, DEV_1_ADDR_ENTRY, info->src_addr,
					 sw->HOST_MASK, false, true,
					 info->redbox_vlan);
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

static void setup_hsr(struct ksz_hsr_info *info, struct net_device *dev, int i)
{
	enum hsr_version proto_version = HSR_V1;
	unsigned char multicast_spec = 0;

	info->dev = dev;
	info->hsr_index = i;
	info->vid = 0;
	info->state = -1;
#if 0
	/* Simulate software forwarding. */
	info->fwd_lane_b = true;
#endif
#if 0
	/* Send HSR frames individually. */
	info->use_lane_b = true;
#endif

	hsr_dev_finalize(dev, info, multicast_spec, proto_version, NULL);
	prep_hsr_supervision_frame(info);
	info->tx_frame = info->master_sup_frame;
	info->len = info->master_len;
	info->hsr_stag = info->master_hsr_stag;
	prep_hsr_mcast(dev);

	/* Redbox is setup first. */
	if (info->redbox)
		prep_hsr_supervision_slave_frame(info);
	skb_queue_head_init(&info->txq);
	INIT_WORK(&info->tx_proc, hsr_tx_proc);
}  /* setup_hsr */

static void setup_hsr_redbox(struct ksz_hsr_info *info, struct net_device *dev,
			     int i, bool fwd)
{
	info->redbox = dev;
	info->redbox_index = i;
	info->redbox_fwd = fwd;

	/* Main HSR device is setup. */
	if (info->dev)
		prep_hsr_supervision_slave_frame(info);
	if (info->dev) {
		int res;

		res = hsr_add_port(&info->hsr, dev, HSR_PT_INTERLINK, NULL);
		res = HSR_PT_INTERLINK;
		info->hsr_ports[res] = hsr_port_get_hsr(&info->hsr, res);
	}
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
				memcpy(&active->addr, node->macaddress_A,
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
	struct ksz_sw *sw = hsr->sw_dev;

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
			} else
				result = DEV_IOC_INVALID_LEN;
			break;
		case DEV_INFO_EXIT:

		/* fall through */
		case DEV_INFO_QUIT:

			/* Not called through char device. */
			if (!info)
				break;
			file_dev_clear_notify(sw->dev_list[0], info,
					      DEV_MOD_HSR,
					      &hsr->notifications);
			msg->module = DEV_MOD_HSR;
			msg->cmd = DEV_INFO_QUIT;
			msg->resp.data[0] = 0;
			file_dev_setup_msg(info, msg, 8, NULL, NULL);
			break;
		case DEV_INFO_NOTIFY:
			if (len >= 4) {
				struct file_dev_info *dev_info = info;
				uint *notify = (uint *) data;

				_chk_ioctl_size(len, 4, 0, &req_size, &result,
					&req->param, data, info);
				dev_info->notifications[DEV_MOD_HSR] =
					*notify;
				hsr->notifications |= *notify;
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

static struct hsr_ops hsr_dev_ops = {
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
	const u8 *src)
{
	struct ksz_sw *sw = info->sw_dev;

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
	if (info->redbox) {
		int i;

		for (i = 0; i < sw->eth_cnt; i++) {
			if (sw->eth_maps[i].proto & HSR_REDBOX) {
				info->redbox_vlan = sw->eth_maps[i].vlan;
				break;
			}
		}
	}
	sw->ops->cfg_mac(sw, BRIDGE_ADDR_ENTRY, info->src_addr, sw->HOST_MASK,
			 false, false, 0);
	if (info->redbox_vlan)
		sw->ops->cfg_mac(sw, DEV_1_ADDR_ENTRY, info->src_addr,
				 sw->HOST_MASK, false, true,
				 info->redbox_vlan);

	/* Ready for announcement. */
	info->state = 0;
	hsr_check_announce(info);
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

	/* Have HSR hardware. */
	if (sw->features & REDUNDANCY_SUPPORT) {
		sw->reg->w32(sw, REG_HSR_PORT_MAP__4, mask);
		data = SW_R(sw, REG_HSR_ALU_CTRL_0__1);
		data &= ~HSR_NODE_UNICAST;
		SW_W(sw, REG_HSR_ALU_CTRL_0__1, data);
	}
	if ((sw->overrides & HAVE_MORE_THAN_2_PORTS) && 1 == sw->eth_cnt)
		sw_cfg_port_base_vlan(sw, sw->HOST_PORT, mask | sw->HOST_MASK);
}  /* sw_setup_hsr */

static void stop_hsr(struct ksz_hsr_info *info)
{
	info->hsr_up = false;
#ifdef CONFIG_HAVE_HSR_HW
	cancel_delayed_work_sync(&info->chk_ring);
#endif
	hsr_dev_destroy(info);
}

static void start_hsr_redbox(struct ksz_hsr_info *info, struct net_device *dev)
{
	info->redbox_up = netif_carrier_ok(dev);
}

static void stop_hsr_redbox(struct ksz_hsr_info *info, struct net_device *dev)
{
	info->redbox_up = false;
}

static void ksz_hsr_exit(struct ksz_hsr_info *info)
{
}  /* ksz_hsr_exit */

static void ksz_hsr_init(struct ksz_hsr_info *info, struct ksz_sw *sw)
{
	info->state = -1;
#ifdef CONFIG_HAVE_HSR_HW
	info->cap = HSR_CAP_DUPLICATE_DISCARD;
	info->cap |= HSR_CAP_REDBOX_CAPABLE;
#endif
	info->sw_dev = sw;
	info->ops = &hsr_dev_ops;

#ifdef CONFIG_HAVE_HSR_HW
	INIT_DELAYED_WORK(&info->chk_ring, hsr_chk_ring);
#endif
}  /* ksz_hsr_init */

