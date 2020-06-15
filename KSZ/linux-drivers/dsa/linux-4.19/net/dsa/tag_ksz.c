/*
 * net/dsa/tag_ksz.c - Microchip KSZ Switch tag format handling
 * Copyright (c) 2017-2020 Microchip Technology
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
	struct dsa_port *dp = dsa_slave_to_port(dev);
	struct ksz_device *sw = dp->ds->priv;
	struct sk_buff *nskb;
	int len;
	int padlen;

	len = KSZ_INGRESS_TAG_LEN;
	if (sw->tag_ops->get_len)
		len = sw->tag_ops->get_len(sw);

	padlen = (skb->len >= ETH_ZLEN) ? 0 : ETH_ZLEN - skb->len;

	if (skb_tailroom(skb) >= padlen + len) {
		/* Let dsa_slave_xmit() free skb */
		if (__skb_put_padto(skb, skb->len + padlen, false))
			return NULL;

		nskb = skb;
	} else {
		nskb = alloc_skb(NET_IP_ALIGN + skb->len +
				 padlen + len, GFP_ATOMIC);
		if (!nskb)
			return NULL;
		skb_reserve(nskb, NET_IP_ALIGN);

		skb_reset_mac_header(nskb);
		skb_set_network_header(nskb,
				       skb_network_header(skb) - skb->head);
		skb_set_transport_header(nskb,
					 skb_transport_header(skb) - skb->head);
		skb_copy_and_csum_dev(skb, skb_put(nskb, skb->len));

		/* Let skb_put_padto() free nskb, and let dsa_slave_xmit() free
		 * skb
		 */
		if (skb_put_padto(nskb, nskb->len + padlen))
			return NULL;

		consume_skb(skb);
	}

	sw->tag_ops->set_tag(sw, skb_put(nskb, len), skb_mac_header(nskb),
			     dp->index);

	return nskb;
}

static struct sk_buff *ksz_rcv(struct sk_buff *skb, struct net_device *dev,
			       struct packet_type *pt)
{
	struct dsa_port *cpu_dp = dev->dsa_ptr;
	struct dsa_switch_tree *dst = cpu_dp->dst;
	struct dsa_switch *ds;
	struct ksz_device *sw;
	u8 *tag;
	int len;
	int source_port;

	ds = dst->ds[0];
	if (!ds)
		return NULL;
	sw = ds->priv;

	tag = skb_tail_pointer(skb) - KSZ_EGRESS_TAG_LEN;

	len = KSZ_EGRESS_TAG_LEN;
	if (sw->tag_ops->get_tag)
		len = sw->tag_ops->get_tag(sw, tag, &source_port);
	else
		source_port = tag[0] & 7;

	skb->dev = dsa_master_find_slave(dev, 0, source_port);
	if (!skb->dev)
		return NULL;

	pskb_trim_rcsum(skb, skb->len - len);

#if 0
	skb->dev->stats.rx_packets++;
	skb->dev->stats.rx_bytes += skb->len;
#endif

	skb->offload_fwd_mark = true;

	return skb;
}

const struct dsa_device_ops ksz_netdev_ops = {
	.xmit	= ksz_xmit,
	.rcv	= ksz_rcv,
};
