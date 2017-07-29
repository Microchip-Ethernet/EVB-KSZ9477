/* Copyright 2011-2014 Autronica Fire and Security AS
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * Author(s):
 *	2011-2014 Arvid Brodin, arvid.brodin@alten.se
 */

#include "hsr_forward.h"
#include <linux/types.h>
#include <linux/skbuff.h>
#include <linux/etherdevice.h>
#include <linux/if_vlan.h>
#include "hsr_main.h"
#include "hsr_framereg.h"


struct hsr_node;

struct hsr_frame_info {
	struct sk_buff *skb_std;
	struct sk_buff *skb_hsr;
	struct hsr_port *port_rcv;
	struct hsr_node *node_src;
	u16 sequence_nr;
	bool is_supervision;
	bool is_vlan;
	bool is_local_dest;
	bool is_local_exclusive;
};


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

	WARN_ON_ONCE(!skb_mac_header_was_set(skb));
	hdr = (struct hsr_ethhdr_sp *) skb_mac_header(skb);

	if (!ether_addr_equal(hdr->ethhdr.h_dest,
			      hsr->sup_multicast_addr))
		return false;

#ifdef CONFIG_HSRv1
	/* Sent internally with VLAN tag. */
	if (hdr->ethhdr.h_proto == htons(ETH_P_8021Q))
		hdr = (struct hsr_ethhdr_sp *)((u8 *) hdr + VLAN_HLEN);

	/* Received from outside with HSR tag. */
	if (hdr->ethhdr.h_proto == htons(ETH_P_HSR))
		hdr = (struct hsr_ethhdr_sp *)((u8 *) hdr + HSR_HLEN);
#if 0
printk(" sup %p %p %d %x %x\n", hdr, &hdr->hsr_sup,
get_hsr_stag_HSR_ver(&hdr->hsr_sup),
hdr->sup_type.HSR_TLV_Type, hdr->sup_type.HSR_TLV_Length);
#endif
	if (get_hsr_stag_HSR_ver(&hdr->hsr_sup) < 1)
		return false;
	if (hdr->sup_type.HSR_TLV_Type != HSR_TLV_LIFE_CHECK)
		return false;
	if (hdr->sup_type.HSR_TLV_Length != 6)
		return false;
#else
	if (get_hsr_stag_path(&hdr->hsr_sup) != 0x0f)
		return false;
	if ((hdr->hsr_sup.HSR_TLV_Type != HSR_TLV_ANNOUNCE) &&
	    (hdr->hsr_sup.HSR_TLV_Type != HSR_TLV_LIFE_CHECK))
		return false;
	if (hdr->hsr_sup.HSR_TLV_Length != 12)
		return false;
#endif

	return true;
}


static struct sk_buff *create_stripped_skb(struct sk_buff *skb_in,
					   struct hsr_frame_info *frame)
{
	struct sk_buff *skb;
	int copylen;
	unsigned char *dst, *src;

#if 0
printk("%s\n", __func__);
#endif
	skb_pull(skb_in, HSR_HLEN);
	skb = __pskb_copy(skb_in, skb_headroom(skb_in) - HSR_HLEN, GFP_ATOMIC);
	skb_push(skb_in, HSR_HLEN);
	if (skb == NULL)
		return NULL;

	skb_reset_mac_header(skb);

	if (skb->ip_summed == CHECKSUM_PARTIAL)
		skb->csum_start -= HSR_HLEN;

	copylen = 2*ETH_ALEN;
	if (frame->is_vlan)
		copylen += VLAN_HLEN;
	src = skb_mac_header(skb_in);
	dst = skb_mac_header(skb);
	memcpy(dst, src, copylen);

	skb->protocol = eth_hdr(skb)->h_proto;
	return skb;
}

static struct sk_buff *frame_get_stripped_skb(struct hsr_frame_info *frame,
					      struct hsr_port *port)
{
	if (!frame->skb_std)
		frame->skb_std = create_stripped_skb(frame->skb_hsr, frame);
	return skb_clone(frame->skb_std, GFP_ATOMIC);
}


static void hsr_fill_tag(struct sk_buff *skb, struct hsr_frame_info *frame,
			 struct hsr_port *port)
{
	struct hsr_ethhdr *hsr_ethhdr;
	int lane_id;
	int lsdu_size;

	if (port->type == HSR_PT_SLAVE_A)
		lane_id = 0;
	else
		lane_id = 1;
	lane_id |= (port->hsr->net_id << 1);

	lsdu_size = skb->len - 14;
#ifdef CONFIG_HSRv1
	if (lsdu_size < 60 - 14)
		lsdu_size = 60 - 14;
#endif
	if (frame->is_vlan)
		lsdu_size -= 4;

	hsr_ethhdr = (struct hsr_ethhdr *) skb_mac_header(skb);

	/* HSR tag is after VLAN tag. */
	if (frame->is_vlan) {
		hsr_ethhdr = (struct hsr_ethhdr *)((u8 *) hsr_ethhdr + 4);
	}

	set_hsr_tag_path(&hsr_ethhdr->hsr_tag, lane_id);
	set_hsr_tag_LSDU_size(&hsr_ethhdr->hsr_tag, lsdu_size);
	hsr_ethhdr->hsr_tag.sequence_nr = htons(frame->sequence_nr);
	hsr_ethhdr->hsr_tag.encap_proto = hsr_ethhdr->ethhdr.h_proto;
#ifdef CONFIG_HSRv1
	hsr_ethhdr->ethhdr.h_proto = htons(ETH_P_HSR);
#else
	hsr_ethhdr->ethhdr.h_proto = htons(ETH_P_PRP);
#endif
}

static struct sk_buff *create_tagged_skb(struct sk_buff *skb_o,
					 struct hsr_frame_info *frame,
					 struct hsr_port *port)
{
	int movelen;
	unsigned char *dst, *src;
	struct sk_buff *skb;

if (vlan_tx_tag_present(skb_o))
printk("%s %d\n", __func__, vlan_tx_tag_get_id(skb_o));
	/* Create the new skb with enough headroom to fit the HSR tag */
	skb = __pskb_copy(skb_o, skb_headroom(skb_o) + HSR_HLEN, GFP_ATOMIC);
	if (skb == NULL)
		return NULL;
	skb_reset_mac_header(skb);

	if (skb->ip_summed == CHECKSUM_PARTIAL)
		skb->csum_start += HSR_HLEN;

	movelen = ETH_HLEN;
	if (frame->is_vlan)
		movelen += VLAN_HLEN;
#if 0
printk("%s %d %d\n", __func__, frame->is_vlan, movelen);
#endif

	src = skb_mac_header(skb);
	dst = skb_push(skb, HSR_HLEN);
	memmove(dst, src, movelen);
	skb_reset_mac_header(skb);
#if 0
{
int i;
for (i = 0; i < 16; i++)
printk("%02x ", skb->data[i]);
printk("\n");
}
#endif

	hsr_fill_tag(skb, frame, port);

	return skb;
}

/* If the original frame was an HSR tagged frame, just clone it to be sent
 * unchanged. Otherwise, create a private frame especially tagged for 'port'.
 */
static struct sk_buff *frame_get_tagged_skb(struct hsr_frame_info *frame,
					    struct hsr_port *port)
{
	if (frame->skb_hsr)
		return skb_clone(frame->skb_hsr, GFP_ATOMIC);

	if ((port->type != HSR_PT_SLAVE_A) && (port->type != HSR_PT_SLAVE_B)) {
		WARN_ONCE(1, "HSR: Bug: trying to create a tagged frame for a non-ring port");
		return NULL;
	}

	return create_tagged_skb(frame->skb_std, frame, port);
}


static void hsr_deliver_master(struct sk_buff *skb, struct net_device *dev,
			       struct hsr_node *node_src)
{
	bool was_multicast_frame;
	int res;

#if 0
printk("%s\n", __func__);
#endif
	was_multicast_frame = (skb->pkt_type == PACKET_MULTICAST);
	hsr_addr_subst_source(node_src, skb);
	skb_pull(skb, ETH_HLEN);
#if 0
do {
int i;
for (i = 0; i < 24; i++)
printk("%02x ", skb->data[i]);
printk("  %d\n", skb->len);
} while (0);
#endif
	res = netif_rx(skb);
	if (res == NET_RX_DROP) {
printk("rx drop\n");
		dev->stats.rx_dropped++;
	} else {
		dev->stats.rx_packets++;
		dev->stats.rx_bytes += skb->len;
		if (was_multicast_frame)
			dev->stats.multicast++;
	}
}

static int hsr_xmit(struct sk_buff *skb, struct hsr_port *port,
		    struct hsr_frame_info *frame)
{
#if 1
{
struct ethhdr *ethhdr = (struct ethhdr *) skb->data;
if (ethhdr->h_proto != htons(ETH_P_HSR))
printk(" ? %s %d %04x\n", __func__, port->type, ethhdr->h_proto);
}
#endif
	if (frame->port_rcv->type == HSR_PT_MASTER) {
		hsr_addr_subst_dest(frame->node_src, skb, port);

#ifndef CONFIG_HSRv1
		/* Address substitution (IEC62439-3 pp 26, 50): replace mac
		 * address of outgoing frame with that of the outgoing slave's.
		 */
		ether_addr_copy(eth_hdr(skb)->h_source, port->dev->dev_addr);
#endif
	}

#ifdef CONFIG_HSRv1
	skb->protocol = htons(ETH_P_HSR);
#endif
	return dev_queue_xmit(skb);
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
	struct hsr_port *port;
	struct sk_buff *skb;
#ifdef CONFIG_HSRv1
	int seq_nr = -1;
	int tx = frame->port_rcv->hsr->tx;
	int tx_once = 0;
#endif

	hsr_for_each_port(frame->port_rcv->hsr, port) {
		/* Don't send frame back the way it came */
		if (port == frame->port_rcv)
{
#if 0
if ((port->type == HSR_PT_MASTER) && frame->is_supervision) {
hsr_register_frame_out(port, frame->node_src, frame->sequence_nr);
	hsr_register_frame_in(frame->node_src, 
		hsr_port_get_hsr(frame->port_rcv->hsr, HSR_PT_SLAVE_A),
frame->sequence_nr);
	hsr_register_frame_in(frame->node_src,
		hsr_port_get_hsr(frame->port_rcv->hsr, HSR_PT_SLAVE_B),
frame->sequence_nr);
}
#endif
			continue;
}

		/* Don't deliver locally unless we should */
		if ((port->type == HSR_PT_MASTER) && !frame->is_local_dest)
{
printk("not local: %d\n", port->type);
			continue;
}

		/* Deliver frames directly addressed to us to master only */
		if ((port->type != HSR_PT_MASTER) && frame->is_local_exclusive)
{
#if 0
printk("local only: %d\n", port->type);
#endif
			continue;
}

#ifdef CONFIG_HSRv1
		/* Do not forward the duplicate that is not passed to host. */
		if ((port->type != HSR_PT_MASTER) &&
		    frame->sequence_nr == seq_nr) {
#if 0
printk("dup: %d %04x\n", port->type, seq_nr);
#endif
			hsr_update_frame_out(port, frame->node_src, seq_nr);
			continue;
		}
#endif

		/* Don't send frame over port where it has been sent before */
		if (hsr_register_frame_out(port, frame->node_src,
					   frame->sequence_nr))
		{
#if 1
if (port->type != HSR_PT_MASTER)
printk("saw before: %d %04x %d\n", port->type, frame->sequence_nr,
frame->is_supervision);
#endif

#ifdef CONFIG_HSRv1
			/* Mark frame as duplicate so no need to forward. */
			if (HSR_PT_MASTER == port->type)
				seq_nr = frame->sequence_nr;
#endif
			continue;
		}

		if (frame->is_supervision && (port->type == HSR_PT_MASTER)) {
			hsr_handle_sup_frame(frame->skb_hsr,
					     frame->node_src,
					     frame->port_rcv);
#if 0
printk("is sup\n");
#endif
			continue;
		}

#ifdef CONFIG_HSRv1
		/* Not delivering to master. */
		if (tx && port->type != HSR_PT_MASTER) {

			/* Do not need to forward or send to other port. */
			if (frame->port_rcv->type != HSR_PT_MASTER || tx_once)
				continue;
			if (netif_carrier_ok(port->dev))
				tx_once = 1;
			else
				continue;
		}
#endif

		if (port->type != HSR_PT_MASTER)
			skb = frame_get_tagged_skb(frame, port);
		else
			skb = frame_get_stripped_skb(frame, port);
		if (skb == NULL) {
			/* FIXME: Record the dropped frame? */
printk("f 5\n");
			continue;
		}

		skb->dev = port->dev;
		if (port->type == HSR_PT_MASTER)
			hsr_deliver_master(skb, port->dev, frame->node_src);
		else
			hsr_xmit(skb, port, frame);
	}
}


static void check_local_dest(struct hsr_priv *hsr, struct sk_buff *skb,
			     struct hsr_frame_info *frame)
{
	struct net_device *master_dev;

	master_dev = hsr_port_get_hsr(hsr, HSR_PT_MASTER)->dev;

#if 0
do {
#if 0
	u8 *data = eth_hdr(skb)->h_dest;
#else
	u8 *data = eth_hdr(skb)->h_source;
#endif
printk("%s %02x:%02x:%02x:%02x:%02x:%02x\n", __func__,
data[0], data[1], data[2], data[3], data[4], data[5]);
} while (0);
#endif
	if (hsr_addr_is_self(hsr, eth_hdr(skb)->h_dest)) {
		frame->is_local_exclusive = true;
		skb->pkt_type = PACKET_HOST;
	} else {
		frame->is_local_exclusive = false;
	}

	if ((skb->pkt_type == PACKET_HOST) ||
	    (skb->pkt_type == PACKET_MULTICAST) ||
	    (skb->pkt_type == PACKET_BROADCAST)) {
		frame->is_local_dest = true;
	} else {
printk("not local_dest\n");
		frame->is_local_dest = false;
	}
}


static int hsr_fill_frame_info(struct hsr_frame_info *frame,
			       struct sk_buff *skb, struct hsr_port *port)
{
	struct ethhdr *ethhdr;
	unsigned long irqflags;

	frame->is_supervision = is_supervision_frame(port->hsr, skb);
#if 0
if (!frame->is_supervision) {
int i;
for (i = 0; i < 30; i++)
printk("%02x ", skb->data[i]);
printk("  chk sup\n");
}
#endif
	frame->node_src = hsr_get_node(&port->hsr->node_db, skb,
				       frame->is_supervision);
#if 0
printk("%s %d %p\n", __func__, frame->is_supervision, frame->node_src);
#endif
	if (frame->node_src == NULL)
		return -1; /* Unknown node and !is_supervision, or no mem */

	ethhdr = (struct ethhdr *) skb_mac_header(skb);
	frame->is_vlan = false;
	if (ethhdr->h_proto == htons(ETH_P_8021Q)) {
#if 0
		struct vlan_ethhdr *vlan = (struct vlan_ethhdr *) ethhdr;

printk("vlan: %04x\n", ntohs(vlan->h_vlan_TCI));
#endif

		frame->is_vlan = true;
#if 0
		/* FIXME: */
		WARN_ONCE(1, "HSR: VLAN not yet supported");
#endif
	}

	/* This is for HSR frame generated internally.  Right now not used. */
#ifdef CONFIG_HSRv1
	if (ethhdr->h_proto == htons(ETH_P_HSR)) {
#else
	if (ethhdr->h_proto == htons(ETH_P_PRP)) {
#endif
		frame->skb_std = NULL;
		frame->skb_hsr = skb;
		frame->sequence_nr = hsr_get_skb_sequence_nr(skb);
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
	check_local_dest(port->hsr, skb, frame);

	return 0;
}

/* Must be called holding rcu read lock (because of the port parameter) */
void hsr_forward_skb(struct sk_buff *skb, struct hsr_port *port)
{
	struct hsr_frame_info frame;

	if (skb_mac_header(skb) != skb->data) {
		WARN_ONCE(1, "%s:%d: Malformed frame (port_src %s)\n",
			  __FILE__, __LINE__, port->dev->name);
		goto out_drop;
	}

	if (hsr_fill_frame_info(&frame, skb, port) < 0)
		goto out_drop;
	hsr_register_frame_in(frame.node_src, port, frame.sequence_nr);
	hsr_forward_do(&frame);

	if (frame.skb_hsr != NULL)
		kfree_skb(frame.skb_hsr);
	if (frame.skb_std != NULL)
		kfree_skb(frame.skb_std);
	return;

out_drop:
printk("fwd drop\n");
	port->dev->stats.tx_dropped++;
	kfree_skb(skb);
}
