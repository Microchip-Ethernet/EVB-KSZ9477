/*
 * net/dsa/tag_ksz.c - Microchip KSZ Switch tag format handling
 * Copyright (c) 2017-2018 Microchip Technology
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <linux/etherdevice.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/dsa/ksz_dsa.h>
#include <net/dsa.h>
#include "dsa_priv.h"

/* Usually only one byte is used for tail tag. */
#define KSZ_INGRESS_TAG_LEN		1
#define KSZ_EGRESS_TAG_LEN		1

static struct sk_buff *ksz_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct dsa_slave_priv *p = netdev_priv(dev);
	struct dsa_switch *ds = p->parent;
	struct ksz_device *sw = ds->priv;
	struct sk_buff *nskb;
	int len;
	int padlen;

	len = KSZ_INGRESS_TAG_LEN;
	if (sw->tag_ops->get_len)
		len = sw->tag_ops->get_len(sw);

	padlen = (skb->len >= ETH_ZLEN) ? 0 : ETH_ZLEN - skb->len;

	nskb = alloc_skb(NET_IP_ALIGN + skb->len +
			 padlen + len, GFP_ATOMIC);
	if (!nskb) {
		kfree_skb(skb);
		return NULL;
	}
	skb_reserve(nskb, NET_IP_ALIGN);

	skb_reset_mac_header(nskb);
	skb_set_network_header(nskb,
			       skb_network_header(skb) - skb->head);
	skb_set_transport_header(nskb,
				 skb_transport_header(skb) - skb->head);
	skb_copy_and_csum_dev(skb, skb_put(nskb, skb->len));
	kfree_skb(skb);

	if (padlen) {
		u8 *pad = skb_put(nskb, padlen);
		memset(pad, 0, padlen);
	}

	sw->tag_ops->set_tag(sw, skb_put(nskb, len), skb_mac_header(nskb),
			     p->port);

	return nskb;
}

static int ksz_rcv(struct sk_buff *skb, struct net_device *dev,
		   struct packet_type *pt, struct net_device *orig_dev)
{
	struct dsa_switch_tree *dst = dev->dsa_ptr;
	struct dsa_switch *ds;
	struct ksz_device *sw;
	u8 *tag;
	int len;
	int source_port;

	if (unlikely(dst == NULL))
		goto out_drop;
	ds = dst->ds[0];
	sw = ds->priv;

	skb = skb_unshare(skb, GFP_ATOMIC);
	if (skb == NULL)
		goto out;

	if (skb_linearize(skb))
		goto out_drop;

	tag = skb_tail_pointer(skb) - KSZ_EGRESS_TAG_LEN;

	len = KSZ_EGRESS_TAG_LEN;
	if (sw->tag_ops->get_tag)
		len = sw->tag_ops->get_tag(sw, tag, &source_port);
	else
		source_port = tag[0] & 7;

	if (source_port >= DSA_MAX_PORTS || !ds->ports[source_port].netdev)
		goto out_drop;

	pskb_trim_rcsum(skb, skb->len - len);

	skb->dev = ds->ports[source_port].netdev;
	skb_push(skb, ETH_HLEN);
	skb->pkt_type = PACKET_HOST;
	skb->protocol = eth_type_trans(skb, skb->dev);

	skb->dev->stats.rx_packets++;
	skb->dev->stats.rx_bytes += skb->len;

	skb->offload_fwd_mark = true;

	netif_receive_skb(skb);

	return 0;

out_drop:
	kfree_skb(skb);
out:
	return 0;
}

const struct dsa_device_ops ksz_netdev_ops = {
	.xmit	= ksz_xmit,
	.rcv	= ksz_rcv,
};
