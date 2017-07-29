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

#include "hsr_slave.h"
#include <linux/etherdevice.h>
#include <linux/if_arp.h>
#include <linux/if_vlan.h>
#include "hsr_main.h"
#include "hsr_device.h"
#include "hsr_forward.h"
#include "hsr_framereg.h"


static rx_handler_result_t hsr_handle_frame(struct sk_buff **pskb)
{
	struct sk_buff *skb = *pskb;
	struct hsr_port *port;

	if (!skb_mac_header_was_set(skb)) {
		WARN_ONCE(1, "%s: skb invalid", __func__);
		return RX_HANDLER_PASS;
	}

	rcu_read_lock(); /* hsr->node_db, hsr->ports */
	port = hsr_port_get_rcu(skb->dev);

#ifdef CONFIG_HSRv1
	do {
		struct hsr_port *p;

		hsr_for_each_port(port->hsr, p) {
			if (p->type == HSR_PT_MASTER) {
				if (!(p->dev->flags & IFF_UP)) {
					kfree_skb(skb);
					goto finish_consume;
				}
				break;
			}
		}
	} while (0);
#endif

	if (hsr_addr_is_self(port->hsr, eth_hdr(skb)->h_source)) {
#if 0
struct vlan_ethhdr *vlan = vlan_eth_hdr(skb);
int i;
u8 *data;
if (vlan->h_vlan_proto == htons(ETH_P_8021Q) &&
vlan->h_vlan_encapsulated_proto == htons(ETH_P_HSR))
printk(" v hsr ");
else if (vlan_tx_tag_present(skb))
printk(" vtag %d %04x %04x\n", vlan_tx_tag_get_id(skb), skb->vlan_proto, skb->vlan_tci);
data = (u8 *) vlan;
#endif
#if 0
for (i = 0; i < 16; i++)
printk("%02x ", data[i]);
printk("\n");
printk("%s %p %p %p\n", __func__, eth_hdr(skb), vlan, skb->data);
#endif
		/* Directly kill frames sent by ourselves */
		kfree_skb(skb);
		goto finish_consume;
	}

#ifdef CONFIG_HSRv1
	if (eth_hdr(skb)->h_proto != htons(ETH_P_HSR))
#else
	if (eth_hdr(skb)->h_proto != htons(ETH_P_PRP))
#endif
		goto finish_pass;

	skb_push(skb, ETH_HLEN);
#if 0
do {
int i;
for (i = 0; i < 28; i++)
printk("%02x ", skb->data[i]);
printk("\n");
} while (0);
#endif

#if 0
do {
	u16 seq = hsr_get_skb_sequence_nr(skb);
printk("%s %02x:%02x:%02x %02x:%02x:%02x ", __func__,
skb->data[3], skb->data[4], skb->data[5],
skb->data[9], skb->data[10], skb->data[11]);
printk("%04x\n", seq);
} while (0);
#endif
	hsr_forward_skb(skb, port);

finish_consume:
	rcu_read_unlock(); /* hsr->node_db, hsr->ports */
	return RX_HANDLER_CONSUMED;

finish_pass:
	rcu_read_unlock(); /* hsr->node_db, hsr->ports */
	return RX_HANDLER_PASS;
}

bool hsr_port_exists(const struct net_device *dev)
{
	return rcu_access_pointer(dev->rx_handler) == hsr_handle_frame;
}


static int hsr_check_dev_ok(struct net_device *dev)
{
	/* Don't allow HSR on non-ethernet like devices */
	if ((dev->flags & IFF_LOOPBACK) || (dev->type != ARPHRD_ETHER) ||
	    (dev->addr_len != ETH_ALEN)) {
		netdev_info(dev, "Cannot use loopback or non-ethernet device as HSR slave.\n");
		return -EINVAL;
	}

	/* Don't allow enslaving hsr devices */
	if (is_hsr_master(dev)) {
		netdev_info(dev, "Cannot create trees of HSR devices.\n");
		return -EINVAL;
	}

	if (hsr_port_exists(dev)) {
		netdev_info(dev, "This device is already a HSR slave.\n");
		return -EINVAL;
	}

	if (dev->priv_flags & IFF_802_1Q_VLAN) {
		netdev_info(dev, "HSR on top of VLAN is not yet supported in this driver.\n");
		return -EINVAL;
	}

	if (dev->priv_flags & IFF_DONT_BRIDGE) {
		netdev_info(dev, "This device does not support bridging.\n");
		return -EOPNOTSUPP;
	}

	/* HSR over bonded devices has not been tested, but I'm not sure it
	 * won't work...
	 */

	return 0;
}


/* Setup device to be added to the HSR bridge. */
static int hsr_portdev_setup(struct net_device *dev, struct hsr_port *port)
{
	int res;

	dev_hold(dev);
	res = dev_set_promiscuity(dev, 1);
	if (res)
		goto fail_promiscuity;

	/* FIXME:
	 * What does net device "adjacency" mean? Should we do
	 * res = netdev_master_upper_dev_link(port->dev, port->hsr->dev); ?
	 */

	res = netdev_rx_handler_register(dev, hsr_handle_frame, port);
	if (res)
		goto fail_rx_handler;
	dev_disable_lro(dev);

	return 0;

fail_rx_handler:
	dev_set_promiscuity(dev, -1);
fail_promiscuity:
	dev_put(dev);

	return res;
}

int hsr_add_port(struct hsr_priv *hsr, struct net_device *dev,
		 enum hsr_port_type type)
{
	struct hsr_port *port, *master;
	int res;

	if (type != HSR_PT_MASTER) {
		res = hsr_check_dev_ok(dev);
		if (res)
			return res;
	}

	port = hsr_port_get_hsr(hsr, type);
	if (port != NULL)
		return -EBUSY;	/* This port already exists */

	port = kzalloc(sizeof(*port), GFP_KERNEL);
	if (port == NULL)
		return -ENOMEM;

	if (type != HSR_PT_MASTER) {
		res = hsr_portdev_setup(dev, port);
		if (res)
			goto fail_dev_setup;
	}

	port->hsr = hsr;
	port->dev = dev;
	port->type = type;

	list_add_tail_rcu(&port->port_list, &hsr->ports);
	synchronize_rcu();

	master = hsr_port_get_hsr(hsr, HSR_PT_MASTER);
	netdev_update_features(master->dev);
	dev_set_mtu(master->dev, hsr_get_max_mtu(hsr));

	return 0;

fail_dev_setup:
	kfree(port);
	return res;
}

void hsr_del_port(struct hsr_port *port)
{
	struct hsr_priv *hsr;
	struct hsr_port *master;

	hsr = port->hsr;
	master = hsr_port_get_hsr(hsr, HSR_PT_MASTER);
	list_del_rcu(&port->port_list);

	if (port != master) {
		netdev_update_features(master->dev);
		dev_set_mtu(master->dev, hsr_get_max_mtu(hsr));
		netdev_rx_handler_unregister(port->dev);
		dev_set_promiscuity(port->dev, -1);
	}

	/* FIXME?
	 * netdev_upper_dev_unlink(port->dev, port->hsr->dev);
	 */

	synchronize_rcu();
	dev_put(port->dev);
}
