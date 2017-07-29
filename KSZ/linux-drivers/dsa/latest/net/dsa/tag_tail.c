/*
 * net/dsa/tag_tail.c - Micrel tail tag format handling
 * Copyright (c) 2015 Micrel, Inc.
 * Copyright (c) 2008-2009 Marvell Semiconductor
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <linux/etherdevice.h>
#include <linux/list.h>
#include <linux/netdevice.h>
#include <linux/slab.h>
#include "dsa_priv.h"

/* These need to be defined in the supported switch drivers. */
void net_add_tail_tag(struct sk_buff *skb, struct net_device *dev, int port);
int net_get_tail_tag(struct sk_buff *skb, struct net_device *dev, int *port);

static netdev_tx_t trailer_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct dsa_slave_priv *p = netdev_priv(dev);
	struct sk_buff *nskb;
	int padlen;

	dev->stats.tx_packets++;
	dev->stats.tx_bytes += skb->len;

	/*
	 * We have to make sure that the trailer ends up as the very
	 * last 4 bytes of the packet.  This means that we have to pad
	 * the packet to the minimum ethernet frame size, if necessary,
	 * before adding the trailer.
	 */
	padlen = 0;
	if (skb->len < 60)
		padlen = 60 - skb->len;

	nskb = alloc_skb(NET_IP_ALIGN + skb->len + padlen + 8, GFP_ATOMIC);
	if (nskb == NULL) {
		kfree_skb(skb);
		return NETDEV_TX_OK;
	}
	skb_reserve(nskb, NET_IP_ALIGN);

	skb_reset_mac_header(nskb);
	skb_set_network_header(nskb, skb_network_header(skb) - skb->head);
	skb_set_transport_header(nskb, skb_transport_header(skb) - skb->head);
	skb_copy_and_csum_dev(skb, skb_put(nskb, skb->len));
	kfree_skb(skb);

	if (padlen) {
		u8 *pad = skb_put(nskb, padlen);
		memset(pad, 0, padlen);
	}

	nskb->dev = p->parent->dst->master_netdev;
	net_add_tail_tag(nskb, nskb->dev, p->port);

	nskb->protocol = htons(ETH_P_TRAILER);

	dev_queue_xmit(nskb);

	return NETDEV_TX_OK;
}

static int trailer_rcv(struct sk_buff *skb, struct net_device *dev,
		       struct packet_type *pt, struct net_device *orig_dev)
{
	struct dsa_switch_tree *dst = dev->dsa_ptr;
	struct dsa_switch *ds;
	int len;
	int source_port;

	if (unlikely(dst == NULL))
		goto out_drop;
	ds = dst->ds[0];

	skb = skb_unshare(skb, GFP_ATOMIC);
	if (skb == NULL)
		goto out;

	if (skb_linearize(skb))
		goto out_drop;

	len = net_get_tail_tag(skb, orig_dev, &source_port);
	if (source_port >= DSA_MAX_PORTS || ds->ports[source_port] == NULL)
		goto out_drop;

	pskb_trim_rcsum(skb, skb->len - len);

	skb->dev = ds->ports[source_port];
	skb_push(skb, ETH_HLEN);
	skb->pkt_type = PACKET_HOST;
	skb->protocol = eth_type_trans(skb, skb->dev);

	skb->dev->stats.rx_packets++;
	skb->dev->stats.rx_bytes += skb->len;

	netif_receive_skb(skb);

	return 0;

out_drop:
	kfree_skb(skb);
out:
	return 0;
}

const struct dsa_device_ops trailer_netdev_ops = {
	.xmit	= trailer_xmit,
	.rcv	= trailer_rcv,
};
