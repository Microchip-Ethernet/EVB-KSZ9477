

#ifndef KSZ_MAC_C
#define KSZ_MAC_C


static int sw_extra_mtu;

#if !defined(get_sysfs_data) || defined(CONFIG_KSZ_SWITCH_EMBEDDED)
static void get_sysfs_data_(struct net_device *dev,
	struct semaphore **proc_sem, struct ksz_port **port)
{
	struct ksz_mac *priv = get_netdev_priv(dev);
	struct sw_priv *hw_priv;

	hw_priv = priv->parent;
	*port = &priv->port;
	*proc_sem = &hw_priv->proc_sem;
}  /* get_sysfs_data */
#endif

#ifndef get_sysfs_data
#define get_sysfs_data		get_sysfs_data_
#endif

#ifndef CONFIG_KSZ_SWITCH_EMBEDDED

#if defined(CONFIG_HAVE_KSZ9897)
#include "ksz_sw_sysfs_9897.c"
#elif defined(CONFIG_HAVE_KSZ8795)
#include "ksz_sw_sysfs_8795.c"
#elif defined(CONFIG_HAVE_KSZ8895)
#include "ksz_sw_sysfs_8895.c"
#elif defined(CONFIG_HAVE_KSZ8863)
#include "ksz_sw_sysfs.c"
#elif defined(CONFIG_HAVE_KSZ8463)
#include "ksz_sw_sysfs.c"
#elif defined(CONFIG_HAVE_LAN937X)
#include "../microchip/lan937x_sw_sysfs.c"
#endif

#ifdef CONFIG_1588_PTP
#ifdef CONFIG_HAVE_LAN937X
#include "../microchip/lan937x_ptp_sysfs.c"
#else
#include "ksz_ptp_sysfs.c"
#endif
#endif

#ifdef CONFIG_KSZ_DLR
#include "ksz_dlr_sysfs.c"
#endif
#endif

static inline int sw_is_switch(struct ksz_sw *sw)
{
	return sw != NULL;
}

static void copy_old_skb(struct sk_buff *old, struct sk_buff *skb)
{
	if (old->ip_summed) {
		int offset = old->head - old->data;

		skb->head = skb->data + offset;
	}
	skb->dev = old->dev;
	skb->sk = old->sk;
	skb->protocol = old->protocol;
	skb->ip_summed = old->ip_summed;
	skb->csum = old->csum;
	skb_shinfo(skb)->tx_flags = skb_shinfo(old)->tx_flags;
	skb_set_network_header(skb, ETH_HLEN);

	dev_kfree_skb_any(old);
}  /* copy_old_skb */

#ifndef CONFIG_KSZ_IBA_ONLY
static int sw_device_seen;

static struct ksz_sw *check_avail_switch(struct net_device *netdev, int id)
{
	struct phy_device *phydev = NULL;
	char phy_id[MII_BUS_ID_SIZE];
	char bus_id[MII_BUS_ID_SIZE];
	phy_interface_t phy_mode;
	struct ksz_sw *sw = NULL;
	struct device *d;

	/* Check whether MII switch exists. */
	phy_mode = PHY_INTERFACE_MODE_MII;
	snprintf(bus_id, MII_BUS_ID_SIZE, "sw.%d", id);
	snprintf(phy_id, MII_BUS_ID_SIZE, PHY_ID_FMT, bus_id, 0);
	d = bus_find_device_by_name(&mdio_bus_type, NULL, phy_id);
	if (!d)
		return NULL;
	phydev = to_phy_device(d);
	if (!phydev->attached_dev) {
		struct phy_priv *phydata = phydev->priv;

		sw = phydata->port->sw;

		/*
		 * In case multiple devices mode is used and this phydev is not
		 * attached again.
		 */
		if (sw)
			phydev->interface = sw->interface;
	}
	put_device(d);
	return sw;
}  /* check_avail_switch */

static int sw_mac_chk(struct ksz_mac *priv)
{
	struct ksz_sw *sw;

	sw = priv->port.sw;
	if (!sw) {
		sw = check_avail_switch(priv->net, sw_device_seen);
		if (!sw_is_switch(sw))
			return -ENXIO;
	}
	priv->port.sw = sw;
	return 0;
}
#endif


static void dev_set_multicast(struct ksz_mac *priv, int multicast)
{
	if ((!multicast && priv->multi) || (multicast && !priv->multi)) {
		struct ksz_mac *hw_priv = priv->hw_priv;
		u8 hw_multi = hw_priv->hw_multi;

		if (multicast)
			++hw_priv->hw_multi;
		else
			--hw_priv->hw_multi;
		priv->multi = multicast;

		/* Turn on/off all multicast mode. */
		if (hw_priv->hw_multi <= 1 && hw_multi <= 1)
			hw_set_multicast(hw_priv->dev, hw_priv->hw_multi);
	}
}  /* dev_set_multicast */

static void dev_set_promisc(struct ksz_mac *priv, int promisc)
{
	if (promisc != priv->promisc) {
		struct ksz_mac *hw_priv = priv->hw_priv;
		u8 hw_promisc = hw_priv->hw_promisc;

		if (promisc)
			++hw_priv->hw_promisc;
		else
			--hw_priv->hw_promisc;
		priv->promisc = promisc;

		/* Turn on/off promiscuous mode. */
		if (hw_priv->hw_promisc <= 1 && hw_promisc <= 1)
			hw_set_promisc(hw_priv->dev, hw_priv->hw_promisc);
	}
}  /* dev_set_promisc */

static void promisc_reset_work(struct work_struct *work)
{
	struct delayed_work *dwork = to_delayed_work(work);
	struct ksz_mac *hw_priv = container_of(dwork, struct ksz_mac,
					       promisc_reset);

	hw_priv->hw_promisc = 0;
	hw_set_promisc(hw_priv->dev, hw_priv->promisc);
}  /* promisc_reset_work */

#ifndef KSZ_USE_SUBQUEUE
static void stop_dev_queues(struct ksz_sw *sw, struct net_device *hw_dev)
{
	if (sw_is_switch(sw)) {
		int dev_count = sw->dev_count + sw->dev_offset;
		struct net_device *net;
		int p;

		for (p = 0; p < dev_count; p++) {
			net = sw->netdev[p];
			if (!net || net == hw_dev)
				continue;
			if (netif_running(net) &&
			    !netif_queue_stopped(net)) {
				netif_stop_queue(net);
			}
		}
	}
}  /* stop_dev_queues */

static void wake_dev_queues(struct ksz_sw *sw, struct net_device *hw_dev)
{
	if (sw_is_switch(sw)) {
		int dev_count = sw->dev_count + sw->dev_offset;
		struct net_device *net;
		int p;

		for (p = 0; p < dev_count; p++) {
			net = sw->netdev[p];
			if (!net || net == hw_dev)
				continue;
			if (netif_running(net) &&
			    netif_queue_stopped(net)) {
				netif_wake_queue(net);

				/* Need to update trans_start. */
				netif_trans_update(net);
			}
		}
		wake_up_interruptible(&sw->queue);
	}
}  /* wake_dev_queues */
#else
static void stop_dev_subqueues(struct ksz_sw *sw, struct net_device *hw_dev,
			       int q)
{
	if (sw_is_switch(sw)) {
		int dev_count = sw->dev_count + sw->dev_offset;
		struct net_device *net;
		int p;

		for (p = 0; p < dev_count; p++) {
			net = sw->netdev[p];
			if (!net || net == hw_dev)
				continue;
			if (netif_running(net)) {
				if (q >= 0) {
					if (!__netif_subqueue_stopped(net, q))
						netif_stop_subqueue(net, q);
				} else {
					netif_tx_stop_all_queues(net);
				}
			}
		}
	}
}  /* stop_dev_subqueues */

static void wake_dev_subqueues(struct ksz_sw *sw, struct net_device *hw_dev,
			       int q)
{
	if (sw_is_switch(sw)) {
		int dev_count = sw->dev_count + sw->dev_offset;
		struct net_device *net;
		int p;

		for (p = 0; p < dev_count; p++) {
			net = sw->netdev[p];
			if (!net || net == hw_dev)
				continue;
			if (netif_running(net)) {
				if (q >= 0) {
					if (__netif_subqueue_stopped(net, q))
						netif_wake_subqueue(net, q);
				} else {
					netif_tx_wake_all_queues(net);
				}
			}
		}
		wake_up_interruptible(&sw->queue);
	}
}  /* wake_dev_subqueues */
#endif

static bool sw_set_rx_mode(struct net_device *dev)
{
	int multicast = ((dev->flags & IFF_ALLMULTI) == IFF_ALLMULTI);
	struct ksz_mac *priv = get_netdev_priv(dev);
	struct ksz_mac *hw_priv = priv->hw_priv;
	struct ksz_sw *sw = priv->port.sw;

	if (!sw_is_switch(sw))
		return false;

	/* set_rx_mode is always called at least wice.  First is to set
	 * multicast hash entries.  Second is to change promiscuous or all
	 * multicast mode.  For all multicast mode the second call does not
	 * indicate setting multicast hash.
	 */
	dev_set_promisc(priv, ((dev->flags & IFF_PROMISC) == IFF_PROMISC));

	/* Multicast is enabled but not all multicast. */
	if (!(dev->flags & IFF_ALLMULTI) &&
	    (dev->flags & IFF_MULTICAST)) {
		/* Used to handle unknown multicast forwarding if not using
		 * multiple network devices.
		 */
		sw->net_ops->set_multi(sw, dev, &priv->port);

		/* Need to turn on multicast for multiple network devices. */
		if (sw->dev_count > 1) {
			multicast |= 2;
		}
	}
	dev_set_multicast(priv, multicast);

	/* Promiscuous mode or all multicast mode is set. */
	if (hw_priv->hw_promisc || hw_priv->hw_multi)
		return true;
	return false;
}  /* sw_set_rx_mode */

static bool sw_mac_set_addr(struct net_device *dev, struct ksz_mac *priv)
{
	struct ksz_sw *sw = priv->port.sw;
	struct ksz_mac *hw_priv;
	u8 hw_promisc;
	u8 promisc;

	if (!sw_is_switch(sw))
		return false;
	hw_priv = priv->hw_priv;
	hw_promisc = hw_priv->hw_promisc;

	promisc = sw->net_ops->set_mac_addr(sw, dev, hw_promisc,
					    priv->port.first_port);
	if (promisc != hw_priv->hw_promisc) {

		/* A hack to accept changed KSZ9897 IBA response. */
		if (!hw_priv->hw_promisc && 2 == promisc) {
			promisc = 1;
			schedule_delayed_work(&hw_priv->promisc_reset, 10);
		}
		hw_priv->hw_promisc = promisc;

		/* Turn on/off promiscuous mode. */
		if (hw_priv->hw_promisc <= 1 && hw_promisc <= 1)
			hw_set_promisc(hw_priv->dev, hw_priv->hw_promisc);
	}
	if (priv->hw_priv && priv != priv->hw_priv)
		return true;
	return false;
}  /* sw_mac_set_addr */

#ifdef KSZ_USE_PRIVATE_IOCTL
static int sw_private_ioctl(struct net_device *dev, struct ifreq *ifr,
			    void __user *data, int cmd)
{
	struct ksz_mac *priv = get_netdev_priv(dev);
	struct ksz_sw *sw = priv->port.sw;
	int result = -EOPNOTSUPP;

	if (!sw_is_switch(sw))
		return result;
	switch (cmd) {
#ifdef CONFIG_1588_PTP
	case SIOCDEVPRIVATE + 15:
		if ((sw->features & PTP_HW)) {
			struct ptp_info *ptp = &sw->ptp_hw;

			result = ptp->ops->dev_req(ptp, ifr->ifr_data, NULL);
		}
		break;
#endif
#ifdef CONFIG_KSZ_MRP
	case SIOCDEVPRIVATE + 14:
		if ((sw->features & MRP_SUPPORT)) {
			struct mrp_info *mrp = &sw->mrp;

			result = mrp->ops->dev_req(mrp, ifr->ifr_data);
		}
		break;
#endif
	case SIOCDEVPRIVATE + 13:
		result = sw->ops->dev_req(sw, ifr->ifr_data, NULL);
		break;
	default:
		break;
	}
	return result;
}  /* sw_private_ioctl */
#endif

#ifdef KSZ_USE_IOCTL
static int sw_ioctl(struct net_device *dev, struct ifreq *rq, int cmd)
{
	int result = -EOPNOTSUPP;

#ifdef CONFIG_1588_PTP
	if (cmd == SIOCSHWTSTAMP) {
		struct ksz_mac *priv = get_netdev_priv(dev);
		struct ksz_sw *sw = priv->port.sw;

		if (sw_is_switch(sw) && (sw->features & PTP_HW)) {
			struct ptp_info *ptp;
			u16 ports;
			int i;
			int p;

			ports = 0;
			if (priv->port.port_cnt > 1) {
				p = priv->port.first_port +
				    priv->port.port_cnt - 1;
				ports = (1 << p);
			} else {
				for (i = 0, p = priv->port.first_port - 1;
				     i < priv->port.port_cnt; i++, p++)
					ports |= (1 << p);
			}
			ptp = &sw->ptp_hw;
			result = ptp->ops->hwtstamp_ioctl(ptp, rq, ports);
		}
	} else if (cmd == SIOCGHWTSTAMP) {
		struct ksz_mac *priv = get_netdev_priv(dev);
		struct ksz_sw *sw = priv->port.sw;

		if (sw_is_switch(sw) && (sw->features & PTP_HW)) {
			struct ptp_info *ptp = &sw->ptp_hw;

			result = ptp->ops->hwtstamp_ioctl_get(ptp, rq);
		}
	}
#endif
	return result;
}  /* sw_ioctl */
#endif

#ifdef KSZ_USE_MSGLEVEL
static void sw_set_msglevel(struct net_device *net, struct ksz_mac *priv,
			    u32 level)
{
	struct ksz_sw *sw = priv->port.sw;

	if (sw_is_switch(sw)) {
		struct net_device *sw_net;
		int i;

		/* All network devices share NETIF_MSG_LINK. */
		priv->msg_enable = level;
		for (i = 0; i < sw->dev_count + sw->dev_offset; i++) {
			sw_net = sw->netdev[i];
			if (!sw_net || sw_net == net)
				continue;
			priv = get_netdev_priv(sw_net);
			if (level & NETIF_MSG_LINK)
				priv->msg_enable |= NETIF_MSG_LINK;
			else
				priv->msg_enable &= ~NETIF_MSG_LINK;
		}
		if (level & NETIF_MSG_LINK)
			sw->msg_enable |= NETIF_MSG_LINK;
		else
			sw->msg_enable &= ~NETIF_MSG_LINK;
	}
}  /* sw_set_msglevel */
#endif

#if defined(CONFIG_HAVE_KSZ9897) || defined(CONFIG_HAVE_LAN937X)
static int priv_multi(void *ptr)
{
	struct ksz_mac *priv = get_ksz_mac(ptr);

	return (priv->multi & 1);
}  /* priv_multi */
#endif

static int priv_promisc(void *ptr)
{
	struct ksz_mac *priv = get_ksz_mac(ptr);

	return priv->promisc;
}  /* priv_promisc */

#if !defined(CONFIG_HAVE_KSZ9897) && !defined(CONFIG_HAVE_LAN937X)
static int priv_match_multi(void *ptr, u8 *data)
{
	struct ksz_mac *priv = get_ksz_mac(ptr);
	struct netdev_hw_addr *ha;
	int drop = true;

	netdev_for_each_mc_addr(ha, priv->net) {
		if (!memcmp(data, ha->addr, ETH_ALEN)) {
			drop = false;
			break;
		}
	}
	return drop;
}  /* priv_match_multi */
#endif

static void *sw_rx_proc(struct ksz_sw *sw, struct sk_buff *skb, int *rxlen)
{
	struct net_device *dev;
	struct ksz_mac *priv;
	int len = skb->len;
	int rx_port = 0;
	int forward = 0;
	void *mac_priv;
	int tag = 0;
#ifdef CONFIG_1588_PTP
	struct ptp_info *ptp = &sw->ptp_hw;
	int ptp_tag = 0;
#endif

	dev = sw->net_ops->rx_dev(sw, skb->data, &len, &tag, &rx_port);
	if (!dev) {
		dev_kfree_skb_any(skb);
		return NULL;
	}

	/* vlan_get_tag requires network device in socket buffer. */
	skb->dev = dev;

	/* __skb_set_length */
	if (len != skb->len) {
		skb->len = len;
		skb_set_tail_pointer(skb, skb->len);
	}

	mac_priv = netdev_priv(dev);
	priv = get_ksz_mac(mac_priv);

	/* Internal packets handled by the switch. */
	if (!sw->net_ops->drv_rx(sw, skb, rx_port)) {
		/* Tell MAC driver real packet was received. */
		*rxlen = skb->len;
		return NULL;
	}

	/* dev can change to the one specifying multicast hash. */
	if (!sw->net_ops->match_pkt(sw, &dev, (void **) &mac_priv, priv_promisc,
#if defined(CONFIG_HAVE_KSZ9897) || defined(CONFIG_HAVE_LAN937X)
	    priv_multi,
#else
	    priv_match_multi,
#endif
	    skb, priv->hw_priv->hw_promisc)) {
		dev_kfree_skb_irq(skb);
		return NULL;
	}

#ifdef CONFIG_1588_PTP
	if (sw->features & PTP_HW) {
		if (ptp->ops->drop_pkt(ptp, skb, sw->vlan_id, &tag, &ptp_tag,
				       &forward)) {
			dev_kfree_skb_any(skb);
			return NULL;
		}
	}
#endif

	/* Need to forward to VLAN devices for PAE messages. */
	if (!forward) {
		struct ethhdr *eth = (struct ethhdr *) skb->data;

		if (eth->h_proto == htons(0x888E) ||
		    eth->h_proto == htons(0x88F7))
			forward = FWD_VLAN_DEV | FWD_STP_DEV;
	}

	/* No VLAN port forwarding; need to send to parent. */
	if ((forward & FWD_VLAN_DEV) && !tag)
		forward &= ~FWD_VLAN_DEV;
	dev = sw->net_ops->parent_rx(sw, dev, &forward);

	/* dev may change. */
	if (dev != skb->dev) {
		skb->dev = dev;
		mac_priv = netdev_priv(dev);
	}

	sw->net_ops->port_vlan_rx(skb, forward, tag);

	return mac_priv;
}  /* sw_rx_proc */

static struct sk_buff *sw_mac_tx_pre(struct sk_buff *skb, struct ksz_mac *priv,
				     int chk_csum)
{
	struct ksz_port *port = &priv->port;
	struct ksz_sw *sw = port->sw;
	bool csum_not_ok = false;

	if (!sw_is_switch(sw))
		return skb;

	if (skb->ip_summed) {
		if (chk_csum & 1)
			csum_not_ok = using_tail_tag(sw);

#ifdef CONFIG_KSZ_HSR
		else if (chk_csum & 2)
			csum_not_ok = using_hsr(sw);
#endif
	}
	if (csum_not_ok) {
		struct sk_buff *nskb;
		int len = skb->len;

		len += sw_extra_mtu;
		nskb = dev_alloc_skb(len);
		if (nskb) {
			skb_copy_and_csum_dev(skb, nskb->data);
			skb->ip_summed = 0;
			nskb->len = skb->len;
			copy_old_skb(skb, nskb);
			skb = nskb;
		}
	}
	return skb;
}  /* sw_mac_tx_pre */

static struct sk_buff *sw_mac_tx(struct net_device *dev, struct sk_buff *skb,
				 struct ksz_mac *priv)
{
	struct ksz_port *port = &priv->port;
	struct ksz_sw *sw = port->sw;

	if (!sw_is_switch(sw))
		return skb;

	skb = sw->net_ops->final_skb(sw, skb, dev, port);
	if (!skb) {
		return NULL;
	}
	return skb;
}  /* sw_mac_tx */

static bool sw_mac_open_first(struct net_device *dev, struct ksz_mac *priv,
			      int *rx_mode)
{
	struct ksz_sw *sw = priv->port.sw;
	struct ksz_mac *hw_priv;

	if (!sw_is_switch(sw))
		return false;
	hw_priv = priv->hw_priv;
	priv->multi = false;
	priv->promisc = false;
	if (hw_priv->opened > 0) {
		netif_carrier_off(dev);
		return true;
	}
	if (0 == hw_priv->opened) {
		struct net_device *main_dev = hw_priv->net;

		/* Need to wait for adjust_link to start operation. */
		hw_priv->port.ready = false;
		hw_priv->hw_multi = 0;
		hw_priv->hw_promisc = 0;
		sw_reset_mac_mib(hw_priv);
		*rx_mode = sw->net_ops->open_dev(sw, main_dev, &hw_priv->port,
						 main_dev->dev_addr);
	}
	return false;
}  /* sw_mac_open_first */

static void sw_mac_open_next(struct ksz_sw *sw, struct ksz_mac *hw_priv,
			     int rx_mode)
{
	if (0 == hw_priv->opened) {
		if (rx_mode & 1) {
			hw_priv->hw_multi = 1;
			hw_set_multicast(hw_priv->dev, hw_priv->hw_multi);
		}
		if (rx_mode & 2) {
			hw_priv->hw_promisc = 1;
			hw_set_promisc(hw_priv->dev, hw_priv->hw_promisc);
		}
		sw->net_ops->open(sw);
	}
}  /* sw_mac_open_second */

static bool sw_mac_open_final(struct ksz_sw *sw, struct net_device *dev,
			      struct ksz_mac *hw_priv, struct ksz_mac *priv)
{
	sw->net_ops->open_port(sw, dev, &priv->port);
	hw_priv->opened++;
	return (hw_priv->opened > 1);
}  /* sw_mac_open_final */


#ifdef CONFIG_KSZ_IBA_ONLY
static bool sw_chk_iba(struct ksz_mac *priv, bool *do_exit)
{
	struct ksz_sw *sw = priv->port.sw;
	bool init = false;

	if (sw_is_switch(sw)) {

		/* Still under initialization in IBA-only mode. */
		if (IBA_USE_CODE_PREPARE == sw->info->iba.use_iba) {
			cancel_delayed_work_sync(&sw->set_ops);

			/* May not started yet. */
			if (IBA_USE_CODE_PREPARE == sw->info->iba.use_iba) {
				kfree(sw->dev);
				priv->port.sw = NULL;
				init = true;
			}
			if (do_exit)
				*do_exit = false;
		}
	}
	return init;
}
#endif

static bool sw_mac_close(struct net_device *dev, struct ksz_mac *priv, int iba)
{
	struct ksz_mac *hw_priv;
	struct ksz_sw *sw;

#ifdef CONFIG_KSZ_IBA_ONLY
	sw_chk_iba(priv, NULL);
#endif
	sw = priv->port.sw;
	if (!sw_is_switch(sw))
		return false;
	hw_priv = priv->hw_priv;
	dev_set_multicast(priv, false);
	dev_set_promisc(priv, false);
	sw->net_ops->close_port(sw, dev, &priv->port);
	hw_priv->opened--;
	if (!hw_priv->opened) {
		bool ok_to_close = true;

		/* Not invoked during closing down the MAC. */
#ifdef CONFIG_KSZ_IBA
		ok_to_close = (sw->info->iba.use_iba != IBA_USE_CODE_LOST);
#endif
		if (ok_to_close) {
			sw->net_ops->close(sw);

#ifdef CONFIG_KSZ_IBA
			/* Do not reset switch at the end. */
			if (sw->info->iba.use_iba >= IBA_USE_CODE_ONLY)
				sw->info->iba.use_iba = iba;
#endif
			sw->net_ops->stop(sw, true);

#ifdef CONFIG_KSZ_IBA_ONLY
			schedule_work(&hw_priv->rmv_dev);
#endif
		}
	} else {
		netif_carrier_off(dev);
		return true;
	}

	/* Reset ready indication. */
	hw_priv->port.ready = false;

	/* Last network device to turn off is not the first. */
	if (dev != sw->netdev[0]) {
		if (hw_priv->saved_phy)
			phy_stop(hw_priv->saved_phy);

		/* Do not want to call phy_stop for this phydev. */
		if (dev->phydev && dev->phydev->mdio.bus)
			phy_detach(dev->phydev);
		dev->phydev = NULL;
	}
	return false;
}

#ifndef KSZ_USE_PHYLINK
static void sw_adjust_link(struct net_device *dev)
{}
#endif

#if defined(CONFIG_HAVE_KSZ9897) || defined(CONFIG_HAVE_LAN937X)
static int get_net_ready(struct net_device *dev)
{
	struct ksz_mac *priv = get_netdev_priv(dev);

	return priv->hw_priv->port.ready;
}  /* get_net_ready */
#endif

static void prep_sw_first(struct ksz_sw *sw, int *port_count,
			  int *mib_port_count, int *dev_count, char *dev_name,
			  const void *phylink_ops)
{
	*port_count = 1;
	*mib_port_count = 1;
	*dev_count = 1;
	dev_name[0] = '\0';
#if defined(CONFIG_HAVE_KSZ9897) || defined(CONFIG_HAVE_LAN937X)
	sw->net_ops->get_ready = get_net_ready;
#endif
	sw->net_ops->setup_special(sw, port_count, mib_port_count, dev_count,
				   phylink_ops);
}  /* prep_sw_first */

static void prep_sw_dev(struct ksz_sw *sw, struct ksz_mac *priv, int i,
			int port_count, int mib_port_count, char *dev_name,
			phy_interface_t phy_mode)
{
	priv->phy_addr = sw->net_ops->setup_dev(sw, priv->net, dev_name,
						&priv->port, i, port_count,
						mib_port_count);

#if defined(CONFIG_PHYLINK) || defined(CONFIG_PHYLINK_MODULE)
	/* MAC driver uses phylink. */
	if (sw->phylink_ops) {
		/* Use the phylink created by the switch driver. */
		if (!priv->phylink)
			priv->phylink = priv->port.pl;
		return;
	}
#endif
	if (!priv->net->phydev) {
		char phy_id[MII_BUS_ID_SIZE];
		char bus_id[MII_BUS_ID_SIZE];

		snprintf(bus_id, MII_BUS_ID_SIZE, "sw.%d", sw->id);
		snprintf(phy_id, MII_BUS_ID_SIZE, PHY_ID_FMT, bus_id,
			 priv->phy_addr);
		phy_attach(priv->net, phy_id, phy_mode);
	}
}  /* prep_sw_dev */

#ifdef CONFIG_OF
#if defined(CONFIG_KSZ_IBA_ONLY) || defined(CONFIG_KSZ_SMI)
#ifdef KSZ_USE_SPI_DEV
static int get_sw_irq(struct device **ext_dev)
{
	int spi_bus, spi_select;
	struct device *dev;
	char name[20];

	for (spi_bus = 0; spi_bus < 2; spi_bus++) {
		for (spi_select = 0; spi_select < 4; spi_select++) {
			sprintf(name, "spi%d.%d\n", spi_bus, spi_select);
			dev = bus_find_device_by_name(&spi_bus_type, NULL,
						      name);
			if (dev && dev->of_node) {
				int irq = of_irq_get(dev->of_node, 0);

				if (ext_dev)
					*ext_dev = dev;
				return irq;
			}
		}
	}
	return -1;
}  /* get_sw_irq */
#endif
#endif
#endif

#ifdef CONFIG_KSZ_IBA_ONLY
/**
 * netdev_start_iba - Start using IBA for register access
 *
 * This routine starts using IBA for register access.
 */
static void netdev_start_iba(struct work_struct *work)
{
	struct delayed_work *dwork = to_delayed_work(work);
	struct ksz_sw *sw = container_of(dwork, struct ksz_sw, set_ops);
	struct ksz_iba_info *iba = &sw->info->iba;
	struct net_device *dev = sw->main_dev;
	struct ksz_port *port = sw->main_port;
	struct ksz_mac *priv;
	int rx_mode;

	if (IBA_USE_CODE_PREPARE != iba->use_iba)
		return;

	/* Communication is not ready if a cable connection is used. */
	if (!port->ready) {
		port->iba_ready = false;
		schedule_delayed_work(&sw->set_ops, 1);
		return;
	}

	/* Need some time after link is established. */
	if (!port->iba_ready) {
		port->iba_ready = true;
		schedule_delayed_work(&sw->set_ops, 10);
		return;
	}

	priv = get_netdev_priv(dev);

	sw->reg = &sw_iba_ops;
	iba->cnt = 0;
	if (ksz_probe_next(sw->dev)) {
		priv->parent = NULL;
		priv->port.sw = NULL;

		/* Turn on link for regular network operation. */
		netif_carrier_on(dev);
		return;
	}

#ifdef CONFIG_1588_PTP
	sw->ptp_hw.reg = &ptp_iba_ops;
#endif

	sw_mac_init(dev, priv);

	priv->multi = false;
	priv->promisc = false;

	priv->hw_multi = 0;
	priv->hw_promisc = 0;
	sw_reset_mac_mib(priv);
	rx_mode = sw->net_ops->open_dev(sw, dev, &priv->port, dev->dev_addr);
	if (rx_mode & 1) {
		priv->hw_multi = 1;
		hw_set_multicast(priv->dev, priv->hw_multi);
	}
	if (rx_mode & 2) {
		priv->hw_promisc = 1;
		hw_set_promisc(priv->dev, priv->hw_promisc);
	}
	sw->net_ops->open(sw);

	sw->net_ops->open_port(sw, dev, &priv->port);
	priv->opened++;

	/* set_rx_mode is called before open. */
	sw_set_rx_mode(priv->net);

	/* Signal IBA initialization is complete. */
	if (IBA_USE_CODE_PREPARE == sw->info->iba.use_iba)
		sw->info->iba.use_iba = IBA_USE_CODE_ONLY;
}  /* netdev_start_iba */

static int create_sw_dev(struct net_device *dev, struct ksz_mac *priv)
{
	struct sw_priv *ks;
	struct ksz_sw *sw;
	int ret;

	/*
	 * Stop normal traffic from going out until the switch is
	 * configured to block looping frames.
	 */
	netif_carrier_off(dev);

	ks = kzalloc(sizeof(struct sw_priv), GFP_KERNEL);
	ks->hw_dev = dev;
	ks->dev = &dev->dev;

#ifdef CONFIG_OF
#ifdef KSZ_USE_SPI_DEV
	ks->irq = get_sw_irq(&ks->of_dev);
#endif
#endif

	sw = &ks->sw;
	ret = ksz_probe_prep(ks, dev);
	if (ret)
		return ret;

	sw->net_ops->get_ready = get_net_ready;
	sw->netdev[0] = dev;
	sw->netport[0] = &priv->port;
	sw->main_dev = dev;
	sw->main_port = &priv->port;
	sw->dev_count = 1;

	INIT_DELAYED_WORK(&sw->set_ops, netdev_start_iba);

	sw_set_dev(sw, dev, dev->dev_addr);

	priv->parent = sw->dev;
	priv->port.sw = sw;

	sw->main_port->iba_ready = true;

#ifdef DEBUG_MSG
	init_dbg();
#endif
	return 0;
}  /* create_sw_dev */
#endif

static void sw_mac_init_pre(void)
{
	/* Accommodate tail tag. */
	sw_extra_mtu = 1;
#ifdef CONFIG_1588_PTP
	/* Accommodate PTP. */
	sw_extra_mtu += 4;
#endif
#ifdef CONFIG_KSZ_HSR
	/* Accommodate HSR. */
	sw_extra_mtu += 6;
#endif

	/* Make it even. */
	sw_extra_mtu += 1;
	sw_extra_mtu &= ~1;

#ifdef CONFIG_KSZ8795_EMBEDDED
	ksz8795_init();
#endif
#ifdef CONFIG_KSZ8895_EMBEDDED
	ksz8895_init();
#endif
#ifdef CONFIG_KSZ9897_EMBEDDED
	ksz9897_init();
#endif
#ifdef CONFIG_LAN937X_EMBEDDED
	lan937x_init();
#endif
}

static void sw_mac_exit(struct ksz_mac *priv)
{
	struct net_device *dev = priv->net;
	struct ksz_sw *sw = priv->port.sw;
	int i;

#ifndef CONFIG_KSZ_IBA_ONLY
#ifdef CONFIG_KSZ_DLR
	if (sw->features & DLR_HW)
		exit_dlr_sysfs(&dev->dev);
#endif
#ifdef CONFIG_1588_PTP
	if (sw->features & PTP_HW)
		exit_ptp_sysfs(&priv->ptp_sysfs, &dev->dev);
#endif
	exit_sw_sysfs(sw, &priv->sysfs, &dev->dev);
#endif
#if defined(CONFIG_PHYLINK) || defined(CONFIG_PHYLINK_MODULE)
	if (priv->port.pl == priv->phylink)
		priv->port.pl = NULL;
#endif
	for (i = 1; i < sw->dev_count + sw->dev_offset; i++) {
		dev = sw->netdev[i];
		if (!dev)
			continue;
		priv = get_netdev_priv(dev);
		cancel_delayed_work_sync(&priv->port.link_update);
#if defined(CONFIG_PHYLINK) || defined(CONFIG_PHYLINK_MODULE)
		if (priv->phylink) {
			if (priv->port.pl == priv->phylink)
				priv->port.pl = NULL;
			phylink_destroy(priv->phylink);
			priv->phylink = NULL;
		}
#endif
		unregister_netdev(dev);
		if (dev->phydev && dev->phydev->mdio.bus)
			phy_detach(dev->phydev);
		free_netdev(dev);
	}
}  /* sw_mac_exit */

#ifdef CONFIG_KSZ_IBA_ONLY
static void rmv_dev_work(struct work_struct *work)
{
	struct ksz_mac *priv = container_of(work, struct ksz_mac, rmv_dev);
	struct ksz_sw *sw = priv->port.sw;

	sw_mac_exit(priv);
	sw->net_ops->leave_dev(sw);
	ksz_remove(sw->dev);
	priv->port.sw = NULL;
}  /* rmv_dev_work */
#endif

static void sw_mac_remove(struct net_device *dev, struct ksz_mac *priv)
{
	struct ksz_sw *sw = priv->port.sw;
	bool do_exit = true;

	if (!sw_is_switch(sw))
		return;

#ifdef CONFIG_KSZ_IBA_ONLY
	if (sw_chk_iba(priv, &do_exit))
		return;
#endif
	if (do_exit) {

#ifdef CONFIG_KSZ_IBA
		/* Indicate no more network communication. */
		if (sw->info->iba.use_iba >= IBA_USE_CODE_ONLY)
			sw->info->iba.use_iba = IBA_USE_CODE_LOST;
		else if (sw->info->iba.use_iba == IBA_USE_CODE_ON)
			sw->net_ops->close_port(sw, sw->main_dev,
						sw->main_port);
#endif

		/* Remove all other network devices. */
		sw_mac_exit(priv);

		/* Indicate MAC is being turned off. */
		if (netif_running(sw->netdev[0]))
			priv->opened = 0;

		cancel_delayed_work_sync(&priv->port.link_update);
		sw->net_ops->stop(sw, true);

		/* Restore phy device if it was replaced. */
		if (dev->phydev && dev->phydev != priv->saved_phy) {
			if (dev->phydev->mdio.bus) {
				/* Need to clear the pointer. */
				dev->phydev->adjust_link = NULL;
				phy_detach(dev->phydev);
			}
			dev->phydev = priv->saved_phy;
		}
	}

#ifdef CONFIG_KSZ_SMI
	if (priv->sw_pdev)
		smi_remove(priv->sw_pdev);
#endif
	sw->net_ops->leave_dev(sw);
#ifdef CONFIG_KSZ_IBA_ONLY
	ksz_remove(sw->dev);
#endif
	priv->port.sw = NULL;
#if defined(CONFIG_KSZ_IBA_ONLY) && defined(DEBUG_MSG)
	exit_dbg();
#endif
#ifdef CONFIG_KSZ8795_EMBEDDED
	ksz8795_exit();
#endif
#ifdef CONFIG_KSZ8895_EMBEDDED
	ksz8895_exit();
#endif
#ifdef CONFIG_KSZ9897_EMBEDDED
	ksz9897_exit();
#endif
#ifdef CONFIG_LAN937X_EMBEDDED
	lan937x_exit();
#endif
}  /* sw_mac_remove */

#endif

