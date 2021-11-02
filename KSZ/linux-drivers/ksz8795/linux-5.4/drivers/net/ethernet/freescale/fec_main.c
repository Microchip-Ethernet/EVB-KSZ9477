// SPDX-License-Identifier: GPL-2.0+
/*
 * Fast Ethernet Controller (FEC) driver for Motorola MPC8xx.
 * Copyright (c) 1997 Dan Malek (dmalek@jlc.net)
 *
 * Right now, I am very wasteful with the buffers.  I allocate memory
 * pages and then divide them into 2K frame buffers.  This way I know I
 * have buffers large enough to hold one frame within one buffer descriptor.
 * Once I get this working, I will use 64 or 128 byte CPM buffers, which
 * will be much more memory efficient and will easily handle lots of
 * small packets.
 *
 * Much better multiple PHY support by Magnus Damm.
 * Copyright (c) 2000 Ericsson Radio Systems AB.
 *
 * Support for FEC controller of ColdFire processors.
 * Copyright (c) 2001-2005 Greg Ungerer (gerg@snapgear.com)
 *
 * Bug fixes and cleanup by Philippe De Muyter (phdm@macqel.be)
 * Copyright (c) 2004-2006 Macq Electronique SA.
 *
 * Copyright (C) 2010-2011 Freescale Semiconductor, Inc.
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/pm_runtime.h>
#include <linux/ptrace.h>
#include <linux/errno.h>
#include <linux/ioport.h>
#include <linux/slab.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/skbuff.h>
#include <linux/in.h>
#include <linux/ip.h>
#include <net/ip.h>
#include <net/tso.h>
#include <linux/tcp.h>
#include <linux/udp.h>
#include <linux/icmp.h>
#include <linux/spinlock.h>
#include <linux/workqueue.h>
#include <linux/bitops.h>
#include <linux/io.h>
#include <linux/irq.h>
#include <linux/clk.h>
#include <linux/crc32.h>
#include <linux/platform_device.h>
#include <linux/mdio.h>
#include <linux/phy.h>
#include <linux/fec.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/of_gpio.h>
#include <linux/of_mdio.h>
#include <linux/of_net.h>
#include <linux/regulator/consumer.h>
#include <linux/if_vlan.h>
#include <linux/pinctrl/consumer.h>
#include <linux/prefetch.h>
#include <linux/mfd/syscon.h>
#include <linux/regmap.h>
#include <soc/imx/cpuidle.h>

#include <asm/cacheflush.h>

#include "fec.h"

#if defined(CONFIG_KSZ_SWITCH_EMBEDDED)
#include <linux/of_irq.h>
#include <linux/spi/spi.h>
#include <linux/ip.h>
#include <net/ip.h>
#include <net/ipv6.h>

/* Need to predefine get_sysfs_data. */

#ifndef get_sysfs_data
struct ksz_port;

static void get_sysfs_data_(struct net_device *dev,
	struct semaphore **proc_sem, struct ksz_port **port);

#define get_sysfs_data		get_sysfs_data_
#endif

static void copy_old_skb(struct sk_buff *old, struct sk_buff *skb);
#define DO_NOT_USE_COPY_SKB

#if defined(CONFIG_IBA_KSZ9897)
#include "../micrel/iba-ksz9897.c"
#elif defined(CONFIG_HAVE_KSZ9897)
#include "../micrel/spi-ksz9897.c"
#elif defined(CONFIG_HAVE_KSZ8795)
#include "../micrel/spi-ksz8795.c"
#elif defined(CONFIG_SMI_KSZ8895)
#include "../micrel/smi-ksz8895.c"
#elif defined(CONFIG_HAVE_KSZ8895)
#include "../micrel/spi-ksz8895.c"
#elif defined(CONFIG_SMI_KSZ8863)
#include "../micrel/smi-ksz8863.c"
#elif defined(CONFIG_HAVE_KSZ8863)
#include "../micrel/spi-ksz8863.c"
#elif defined(CONFIG_IBA_LAN937X)
#include "../microchip/iba-lan937x.c"
#elif defined(CONFIG_SMI_LAN937X)
#include "../microchip/smi-lan937x.c"
#elif defined(CONFIG_HAVE_LAN937X)
#include "../microchip/spi-lan937x.c"
#endif
#endif

#if defined(CONFIG_KSZ_SWITCH) && !defined(CONFIG_KSZ_SWITCH_EMBEDDED)
#ifdef CONFIG_HAVE_LAN937X
#include "../microchip/lan937x_dev.h"
#else
#include "../micrel/ksz_spi_net.h"
#endif
#endif

#ifdef CONFIG_KSZ_SWITCH

#if !defined(get_sysfs_data) || defined(CONFIG_KSZ_SWITCH_EMBEDDED)
static void get_sysfs_data_(struct net_device *dev,
	struct semaphore **proc_sem, struct ksz_port **port)
{
	struct fec_enet_private *priv = netdev_priv(dev);
	struct sw_priv *hw_priv;

	hw_priv = priv->parent;
	*port = &priv->port;
	*proc_sem = &hw_priv->proc_sem;
}  /* get_sysfs_data */
#endif

#ifndef get_sysfs_data
#define get_sysfs_data		get_sysfs_data_
#endif

#if !defined(CONFIG_KSZ_SWITCH_EMBEDDED)
#define USE_SPEED_LINK
#define USE_MIB

#if defined(CONFIG_HAVE_KSZ9897)
#include "../micrel/ksz_sw_sysfs_9897.c"
#elif defined(CONFIG_HAVE_KSZ8795)
#include "../micrel/ksz_sw_sysfs_8795.c"
#elif defined(CONFIG_HAVE_KSZ8895)
#include "../micrel/ksz_sw_sysfs_8895.c"
#elif defined(CONFIG_HAVE_KSZ8863)
#include "../micrel/ksz_sw_sysfs.c"
#elif defined(CONFIG_HAVE_KSZ8463)
#include "../micrel/ksz_sw_sysfs.c"
#elif defined(CONFIG_HAVE_LAN937X)
#include "../microchip/lan937x_sw_sysfs.c"
#endif

#ifdef CONFIG_1588_PTP
#if defined(CONFIG_HAVE_KSZ9897)
#include "../micrel/ksz_ptp_sysfs.c"
#elif defined(CONFIG_HAVE_LAN937X)
#include "../microchip/lan937x_ptp_sysfs.c"
#endif
#endif

#ifdef CONFIG_KSZ_DLR
#include "../micrel/ksz_dlr_sysfs.c"
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

static int fec_enet_add_vid(struct net_device *dev, __be16 proto, u16 vid)
{
	struct fec_enet_private *fep = netdev_priv(dev);
	struct ksz_sw *sw = fep->port.sw;

	if (sw_is_switch(sw))
		sw->net_ops->add_vid(sw, vid);
	return 0;
}

static int fec_enet_kill_vid(struct net_device *dev, __be16 proto, u16 vid)
{
	struct fec_enet_private *fep = netdev_priv(dev);
	struct ksz_sw *sw = fep->port.sw;

	if (sw_is_switch(sw))
		sw->net_ops->kill_vid(sw, vid);
	return 0;
}

static int sw_device_seen;

#if !defined(CONFIG_KSZ_IBA_ONLY)
static struct ksz_sw *check_avail_switch(struct net_device *netdev, int id)
{
	int phy_mode;
	char phy_id[MII_BUS_ID_SIZE];
	char bus_id[MII_BUS_ID_SIZE];
	struct ksz_sw *sw = NULL;
	struct phy_device *phydev = NULL;

	/* Check whether MII switch exists. */
	phy_mode = PHY_INTERFACE_MODE_MII;
	snprintf(bus_id, MII_BUS_ID_SIZE, "sw.%d", id);
	snprintf(phy_id, MII_BUS_ID_SIZE, PHY_ID_FMT, bus_id, 0);
	phydev = phy_attach(netdev, phy_id, phy_mode);
	if (!IS_ERR(phydev)) {
		struct phy_priv *phydata = phydev->priv;

		sw = phydata->port->sw;

		/*
		 * In case multiple devices mode is used and this phydev is not
		 * attached again.
		 */
		if (sw)
			phydev->interface = sw->interface;
		phy_detach(phydev);
	}
	return sw;
}  /* check_avail_switch */

static int fec_enet_sw_chk(struct fec_enet_private *fep)
{
	struct ksz_sw *sw;

	sw = fep->port.sw;
	if (!sw) {
		sw = check_avail_switch(fep->netdev, sw_device_seen);
		if (!sw_is_switch(sw))
			return -ENXIO;
	}
	fep->port.sw = sw;
	return 0;
}
#endif

#if defined(CONFIG_KSZ_IBA_ONLY) || defined(CONFIG_KSZ_SMI)
static int get_sw_irq(struct fec_enet_private *fep, struct device **ext_dev)
{
	struct device *dev;
	int spi_bus;
	int spi_select;
	char name[20];

	spi_select = 0;
	for (spi_bus = 0; spi_bus < 2; spi_bus++) {
		sprintf(name, "spi%d.%d\n", spi_bus, spi_select);
		dev = bus_find_device_by_name(&spi_bus_type, NULL, name);
		if (dev && dev->of_node) {
			int irq = of_irq_get(dev->of_node, 0);

			if (ext_dev)
				*ext_dev = dev;
			return irq;
		}
	}
	return -1;
}  /* get_sw_irq */
#endif

static void stop_dev_queues(struct ksz_sw *sw, struct net_device *hw_dev,
			    struct fec_enet_private *fep, u16 qid)
{
	if (sw_is_switch(sw)) {
		int dev_count = sw->dev_count + sw->dev_offset;
		struct netdev_queue *nq;
		struct net_device *dev;
		int p;

		for (p = 0; p < dev_count; p++) {
			dev = sw->netdev[p];
			if (!dev || dev == hw_dev)
				continue;
			if (netif_running(dev) || dev == fep->netdev) {
				nq = netdev_get_tx_queue(dev, qid);
				netif_tx_stop_queue(nq);
			}
		}
	}
}  /* stop_dev_queues */

static void wake_dev_queues(struct ksz_sw *sw, struct net_device *hw_dev,
			    u16 qid)
{
	if (sw_is_switch(sw)) {
		int dev_count = sw->dev_count + sw->dev_offset;
		struct netdev_queue *nq;
		struct net_device *dev;
		int p;

		for (p = 0; p < dev_count; p++) {
			dev = sw->netdev[p];
			if (!dev || dev == hw_dev)
				continue;
			if (netif_running(dev)) {
				nq = netdev_get_tx_queue(dev, qid);
				if (netif_tx_queue_stopped(nq))
					netif_tx_wake_queue(nq);
			}
		}
		wake_up_interruptible(&sw->queue);
	}
}  /* wake_dev_queues */

#if defined(CONFIG_HAVE_KSZ9897) || defined(CONFIG_HAVE_LAN937X)
static int priv_multi(void *ptr)
{
	struct fec_enet_private *priv = ptr;

	return (priv->multi & 1);
}  /* priv_multi */
#endif

static int priv_promisc(void *ptr)
{
	struct fec_enet_private *priv = ptr;

	return priv->promisc;
}  /* priv_promisc */

#if !defined(CONFIG_HAVE_KSZ9897) && !defined(CONFIG_HAVE_LAN937X)
static int priv_match_multi(void *ptr, u8 *data)
{
	struct netdev_hw_addr *ha;
	struct fec_enet_private *fep = ptr;
	int drop = true;

	netdev_for_each_mc_addr(ha, fep->netdev) {
		if (!memcmp(data, ha->addr, ETH_ALEN)) {
			drop = false;
			break;
		}
	}
	return drop;
}  /* priv_match_multi */
#endif

static struct net_device *sw_rx_proc(struct ksz_sw *sw, struct sk_buff *skb,
				     __u8 *data)
{
	struct net_device *dev;
	struct fec_enet_private *fep;
	int len = skb->len;
	int rx_port = 0;
#if defined(CONFIG_KSZ_SWITCH) || defined(CONFIG_1588_PTP)
	int forward = 0;
	int tag = 0;
	void *ptr = NULL;
	void (*rx_tstamp)(void *ptr, struct sk_buff *skb) = NULL;
#endif
#ifdef CONFIG_1588_PTP
	struct ptp_info *ptp = &sw->ptp_hw;
	int ptp_tag = 0;
#endif
	struct net_device *parent_dev = NULL;
	struct sk_buff *parent_skb = NULL;

	dev = sw->net_ops->rx_dev(sw, data, &len, &tag, &rx_port);
	if (!dev) {
		dev_kfree_skb_any(skb);
		return NULL;
	}

	/* vlan_get_tag requires network device in socket buffer. */
	skb->dev = dev;

	/* skb_put is already used. */
	if (len != skb->len) {
		int diff = skb->len - len;

		skb->len -= diff;
		skb->tail -= diff;
	}

	fep = netdev_priv(dev);

	/* Internal packets handled by the switch. */
	if (!sw->net_ops->drv_rx(sw, skb, rx_port)) {
		dev->stats.rx_packets++;
		dev->stats.rx_bytes += skb->len;
		return NULL;
	}

	if (!sw->net_ops->match_pkt(sw, &dev, (void **) &fep, priv_promisc,
#if defined(CONFIG_HAVE_KSZ9897) || defined(CONFIG_HAVE_LAN937X)
	    priv_multi,
#else
	    priv_match_multi,
#endif
	    skb, fep->hw_priv->hw_promisc)) {
		dev_kfree_skb_irq(skb);
		return NULL;
	}

#ifdef CONFIG_1588_PTP
	ptr = ptp;
	if (sw->features & PTP_HW) {
		if (ptp->ops->drop_pkt(ptp, skb, sw->vlan_id, &tag, &ptp_tag,
				       &forward)) {
			dev_kfree_skb_any(skb);
			return NULL;
		}
		if (ptp_tag)
			rx_tstamp = ptp->ops->get_rx_tstamp;
	}
#endif

#if defined(CONFIG_KSZ_SWITCH)
	/* Need to forward to VLAN devices for PAE messages. */
	if (!forward) {
		struct ethhdr *eth = (struct ethhdr *) data;

		if (eth->h_proto == htons(0x888E))
			forward = FWD_VLAN_DEV | FWD_STP_DEV;
	}

	/* No VLAN port forwarding; need to send to parent. */
	if ((forward & FWD_VLAN_DEV) && !tag)
		forward &= ~FWD_VLAN_DEV;
	dev = sw->net_ops->parent_rx(sw, dev, skb, &forward, &parent_dev,
		&parent_skb);

	/* dev may change. */
	if (dev != skb->dev) {
		skb->dev = dev;
	}

	sw->net_ops->port_vlan_rx(sw, dev, parent_dev, skb,
		forward, tag, ptr, rx_tstamp);
#endif
	return dev;
}  /* sw_rx_proc */
#endif

static void set_multicast_list(struct net_device *ndev);
static void fec_enet_itr_coal_init(struct net_device *ndev);

#define DRIVER_NAME	"fec"

#define FEC_ENET_GET_QUQUE(_x) ((_x == 0) ? 1 : ((_x == 1) ? 2 : 0))

/* Pause frame feild and FIFO threshold */
#define FEC_ENET_FCE	(1 << 5)
#define FEC_ENET_RSEM_V	0x84
#define FEC_ENET_RSFL_V	16
#define FEC_ENET_RAEM_V	0x8
#define FEC_ENET_RAFL_V	0x8
#define FEC_ENET_OPD_V	0xFFF0
#define FEC_MDIO_PM_TIMEOUT  100 /* ms */

struct fec_devinfo {
	u32 quirks;
	u8 stop_gpr_reg;
	u8 stop_gpr_bit;
};

static const struct fec_devinfo fec_imx25_info = {
	.quirks = FEC_QUIRK_USE_GASKET | FEC_QUIRK_MIB_CLEAR |
		  FEC_QUIRK_HAS_FRREG,
};

static const struct fec_devinfo fec_imx27_info = {
	.quirks = FEC_QUIRK_MIB_CLEAR | FEC_QUIRK_HAS_FRREG,
};

static const struct fec_devinfo fec_imx28_info = {
	.quirks = FEC_QUIRK_ENET_MAC | FEC_QUIRK_SWAP_FRAME |
		  FEC_QUIRK_SINGLE_MDIO | FEC_QUIRK_HAS_RACC |
		  FEC_QUIRK_HAS_FRREG,
};

static const struct fec_devinfo fec_imx6q_info = {
	.quirks = FEC_QUIRK_ENET_MAC | FEC_QUIRK_HAS_GBIT |
		  FEC_QUIRK_HAS_BUFDESC_EX | FEC_QUIRK_HAS_CSUM |
		  FEC_QUIRK_HAS_VLAN | FEC_QUIRK_ERR006358 |
		  FEC_QUIRK_HAS_RACC,
	.stop_gpr_reg = 0x34,
	.stop_gpr_bit = 27,
};

static const struct fec_devinfo fec_mvf600_info = {
	.quirks = FEC_QUIRK_ENET_MAC | FEC_QUIRK_HAS_RACC,
};

static const struct fec_devinfo fec_imx6x_info = {
	.quirks = FEC_QUIRK_ENET_MAC | FEC_QUIRK_HAS_GBIT |
		  FEC_QUIRK_HAS_BUFDESC_EX | FEC_QUIRK_HAS_CSUM |
		  FEC_QUIRK_HAS_VLAN | FEC_QUIRK_HAS_AVB |
		  FEC_QUIRK_ERR007885 | FEC_QUIRK_BUG_CAPTURE |
		  FEC_QUIRK_HAS_RACC | FEC_QUIRK_HAS_COALESCE,
};

static const struct fec_devinfo fec_imx6ul_info = {
	.quirks = FEC_QUIRK_ENET_MAC | FEC_QUIRK_HAS_GBIT |
		  FEC_QUIRK_HAS_BUFDESC_EX | FEC_QUIRK_HAS_CSUM |
		  FEC_QUIRK_HAS_VLAN | FEC_QUIRK_ERR007885 |
		  FEC_QUIRK_BUG_CAPTURE | FEC_QUIRK_HAS_RACC |
		  FEC_QUIRK_HAS_COALESCE,
};

static struct platform_device_id fec_devtype[] = {
	{
		/* keep it for coldfire */
		.name = DRIVER_NAME,
		.driver_data = 0,
	}, {
		.name = "imx25-fec",
		.driver_data = (kernel_ulong_t)&fec_imx25_info,
	}, {
		.name = "imx27-fec",
		.driver_data = (kernel_ulong_t)&fec_imx27_info,
	}, {
		.name = "imx28-fec",
		.driver_data = (kernel_ulong_t)&fec_imx28_info,
	}, {
		.name = "imx6q-fec",
		.driver_data = (kernel_ulong_t)&fec_imx6q_info,
	}, {
		.name = "mvf600-fec",
		.driver_data = (kernel_ulong_t)&fec_mvf600_info,
	}, {
		.name = "imx6sx-fec",
		.driver_data = (kernel_ulong_t)&fec_imx6x_info,
	}, {
		.name = "imx6ul-fec",
		.driver_data = (kernel_ulong_t)&fec_imx6ul_info,
	}, {
		/* sentinel */
	}
};
MODULE_DEVICE_TABLE(platform, fec_devtype);

enum imx_fec_type {
	IMX25_FEC = 1,	/* runs on i.mx25/50/53 */
	IMX27_FEC,	/* runs on i.mx27/35/51 */
	IMX28_FEC,
	IMX6Q_FEC,
	MVF600_FEC,
	IMX6SX_FEC,
	IMX6UL_FEC,
};

static const struct of_device_id fec_dt_ids[] = {
	{ .compatible = "fsl,imx25-fec", .data = &fec_devtype[IMX25_FEC], },
	{ .compatible = "fsl,imx27-fec", .data = &fec_devtype[IMX27_FEC], },
	{ .compatible = "fsl,imx28-fec", .data = &fec_devtype[IMX28_FEC], },
	{ .compatible = "fsl,imx6q-fec", .data = &fec_devtype[IMX6Q_FEC], },
	{ .compatible = "fsl,mvf600-fec", .data = &fec_devtype[MVF600_FEC], },
	{ .compatible = "fsl,imx6sx-fec", .data = &fec_devtype[IMX6SX_FEC], },
	{ .compatible = "fsl,imx6ul-fec", .data = &fec_devtype[IMX6UL_FEC], },
	{ /* sentinel */ }
};
MODULE_DEVICE_TABLE(of, fec_dt_ids);

static unsigned char macaddr[ETH_ALEN];
module_param_array(macaddr, byte, NULL, 0);
MODULE_PARM_DESC(macaddr, "FEC Ethernet MAC address");

#if defined(CONFIG_M5272)
/*
 * Some hardware gets it MAC address out of local flash memory.
 * if this is non-zero then assume it is the address to get MAC from.
 */
#if defined(CONFIG_NETtel)
#define	FEC_FLASHMAC	0xf0006006
#elif defined(CONFIG_GILBARCONAP) || defined(CONFIG_SCALES)
#define	FEC_FLASHMAC	0xf0006000
#elif defined(CONFIG_CANCam)
#define	FEC_FLASHMAC	0xf0020000
#elif defined (CONFIG_M5272C3)
#define	FEC_FLASHMAC	(0xffe04000 + 4)
#elif defined(CONFIG_MOD5272)
#define FEC_FLASHMAC	0xffc0406b
#else
#define	FEC_FLASHMAC	0
#endif
#endif /* CONFIG_M5272 */

/* The FEC stores dest/src/type/vlan, data, and checksum for receive packets.
 *
 * 2048 byte skbufs are allocated. However, alignment requirements
 * varies between FEC variants. Worst case is 64, so round down by 64.
 */
#define PKT_MAXBUF_SIZE		(round_down(2048 - 64, 64))
#define PKT_MINBUF_SIZE		64

/* FEC receive acceleration */
#define FEC_RACC_IPDIS		(1 << 1)
#define FEC_RACC_PRODIS		(1 << 2)
#define FEC_RACC_SHIFT16	BIT(7)
#define FEC_RACC_OPTIONS	(FEC_RACC_IPDIS | FEC_RACC_PRODIS)

/* MIB Control Register */
#define FEC_MIB_CTRLSTAT_DISABLE	BIT(31)

/*
 * The 5270/5271/5280/5282/532x RX control register also contains maximum frame
 * size bits. Other FEC hardware does not, so we need to take that into
 * account when setting it.
 */
#if defined(CONFIG_M523x) || defined(CONFIG_M527x) || defined(CONFIG_M528x) || \
    defined(CONFIG_M520x) || defined(CONFIG_M532x) || defined(CONFIG_ARM) || \
    defined(CONFIG_ARM64)
#define	OPT_FRAME_SIZE	(PKT_MAXBUF_SIZE << 16)
#else
#define	OPT_FRAME_SIZE	0
#endif

/* FEC MII MMFR bits definition */
#define FEC_MMFR_ST		(1 << 30)
#define FEC_MMFR_ST_C45		(0)
#define FEC_MMFR_OP_READ	(2 << 28)
#define FEC_MMFR_OP_READ_C45	(3 << 28)
#define FEC_MMFR_OP_WRITE	(1 << 28)
#define FEC_MMFR_OP_ADDR_WRITE	(0)
#define FEC_MMFR_PA(v)		((v & 0x1f) << 23)
#define FEC_MMFR_RA(v)		((v & 0x1f) << 18)
#define FEC_MMFR_TA		(2 << 16)
#define FEC_MMFR_DATA(v)	(v & 0xffff)
/* FEC ECR bits definition */
#define FEC_ECR_MAGICEN		(1 << 2)
#define FEC_ECR_SLEEP		(1 << 3)

#define FEC_MII_TIMEOUT		30000 /* us */

/* Transmitter timeout */
#define TX_TIMEOUT (2 * HZ)

#define FEC_PAUSE_FLAG_AUTONEG	0x1
#define FEC_PAUSE_FLAG_ENABLE	0x2
#define FEC_WOL_HAS_MAGIC_PACKET	(0x1 << 0)
#define FEC_WOL_FLAG_ENABLE		(0x1 << 1)
#define FEC_WOL_FLAG_SLEEP_ON		(0x1 << 2)

#define COPYBREAK_DEFAULT	256

/* Max number of allowed TCP segments for software TSO */
#define FEC_MAX_TSO_SEGS	100
#define FEC_MAX_SKB_DESCS	(FEC_MAX_TSO_SEGS * 2 + MAX_SKB_FRAGS)

#define IS_TSO_HEADER(txq, addr) \
	((addr >= txq->tso_hdrs_dma) && \
	(addr < txq->tso_hdrs_dma + txq->bd.ring_size * TSO_HEADER_SIZE))

static int mii_cnt;

static struct bufdesc *fec_enet_get_nextdesc(struct bufdesc *bdp,
					     struct bufdesc_prop *bd)
{
	return (bdp >= bd->last) ? bd->base
			: (struct bufdesc *)(((void *)bdp) + bd->dsize);
}

static struct bufdesc *fec_enet_get_prevdesc(struct bufdesc *bdp,
					     struct bufdesc_prop *bd)
{
	return (bdp <= bd->base) ? bd->last
			: (struct bufdesc *)(((void *)bdp) - bd->dsize);
}

static int fec_enet_get_bd_index(struct bufdesc *bdp,
				 struct bufdesc_prop *bd)
{
	return ((const char *)bdp - (const char *)bd->base) >> bd->dsize_log2;
}

static int fec_enet_get_free_txdesc_num(struct fec_enet_priv_tx_q *txq)
{
	int entries;

	entries = (((const char *)txq->dirty_tx -
			(const char *)txq->bd.cur) >> txq->bd.dsize_log2) - 1;

	return entries >= 0 ? entries : entries + txq->bd.ring_size;
}

static void swap_buffer(void *bufaddr, int len)
{
	int i;
	unsigned int *buf = bufaddr;

	for (i = 0; i < len; i += 4, buf++)
		swab32s(buf);
}

static void swap_buffer2(void *dst_buf, void *src_buf, int len)
{
	int i;
	unsigned int *src = src_buf;
	unsigned int *dst = dst_buf;

	for (i = 0; i < len; i += 4, src++, dst++)
		*dst = swab32p(src);
}

static void fec_dump(struct net_device *ndev)
{
	struct fec_enet_private *fep = netdev_priv(ndev);
	struct bufdesc *bdp;
	struct fec_enet_priv_tx_q *txq;
	int index = 0;

#ifdef CONFIG_KSZ_SWITCH
	fep = fep->hw_priv;
#endif
	netdev_info(ndev, "TX ring dump\n");
	pr_info("Nr     SC     addr       len  SKB\n");

	txq = fep->tx_queue[0];
	bdp = txq->bd.base;

	do {
		pr_info("%3u %c%c 0x%04x 0x%08x %4u %p\n",
			index,
			bdp == txq->bd.cur ? 'S' : ' ',
			bdp == txq->dirty_tx ? 'H' : ' ',
			fec16_to_cpu(bdp->cbd_sc),
			fec32_to_cpu(bdp->cbd_bufaddr),
			fec16_to_cpu(bdp->cbd_datlen),
			txq->tx_skbuff[index]);
		bdp = fec_enet_get_nextdesc(bdp, &txq->bd);
		index++;
	} while (bdp != txq->bd.base);
}

static inline bool is_ipv4_pkt(struct sk_buff *skb)
{
	return skb->protocol == htons(ETH_P_IP) && ip_hdr(skb)->version == 4;
}

static int
fec_enet_clear_csum(struct sk_buff *skb, struct net_device *ndev)
{
	/* Only run for packets requiring a checksum. */
	if (skb->ip_summed != CHECKSUM_PARTIAL)
		return 0;

	if (unlikely(skb_cow_head(skb, 0)))
		return -1;

	if (is_ipv4_pkt(skb))
		ip_hdr(skb)->check = 0;
	*(__sum16 *)(skb->head + skb->csum_start + skb->csum_offset) = 0;

	return 0;
}

static struct bufdesc *
fec_enet_txq_submit_frag_skb(struct fec_enet_priv_tx_q *txq,
			     struct sk_buff *skb,
			     struct net_device *ndev)
{
	struct fec_enet_private *fep = netdev_priv(ndev);
	struct bufdesc *bdp = txq->bd.cur;
	struct bufdesc_ex *ebdp;
	int nr_frags = skb_shinfo(skb)->nr_frags;
	int frag, frag_len;
	unsigned short status;
	unsigned int estatus = 0;
	skb_frag_t *this_frag;
	unsigned int index;
	void *bufaddr;
	dma_addr_t addr;
	int i;

#ifdef CONFIG_KSZ_SWITCH
	fep = fep->hw_priv;
#endif
	for (frag = 0; frag < nr_frags; frag++) {
		this_frag = &skb_shinfo(skb)->frags[frag];
		bdp = fec_enet_get_nextdesc(bdp, &txq->bd);
		ebdp = (struct bufdesc_ex *)bdp;

		status = fec16_to_cpu(bdp->cbd_sc);
		status &= ~BD_ENET_TX_STATS;
		status |= (BD_ENET_TX_TC | BD_ENET_TX_READY);
		frag_len = skb_frag_size(&skb_shinfo(skb)->frags[frag]);

		/* Handle the last BD specially */
		if (frag == nr_frags - 1) {
			status |= (BD_ENET_TX_INTR | BD_ENET_TX_LAST);
#ifndef CONFIG_1588_PTP
			if (fep->bufdesc_ex) {
				estatus |= BD_ENET_TX_INT;
				if (unlikely(skb_shinfo(skb)->tx_flags &
					SKBTX_HW_TSTAMP && fep->hwts_tx_en))
					estatus |= BD_ENET_TX_TS;
			}
#endif
		}

		if (fep->bufdesc_ex) {
			if (fep->quirks & FEC_QUIRK_HAS_AVB)
				estatus |= FEC_TX_BD_FTYPE(txq->bd.qid);
			if (skb->ip_summed == CHECKSUM_PARTIAL)
				estatus |= BD_ENET_TX_PINS | BD_ENET_TX_IINS;
			ebdp->cbd_bdu = 0;
			ebdp->cbd_esc = cpu_to_fec32(estatus);
		}

		bufaddr = skb_frag_address(this_frag);

		index = fec_enet_get_bd_index(bdp, &txq->bd);
		if (((unsigned long) bufaddr) & fep->tx_align ||
			fep->quirks & FEC_QUIRK_SWAP_FRAME) {
			memcpy(txq->tx_bounce[index], bufaddr, frag_len);
			bufaddr = txq->tx_bounce[index];

			if (fep->quirks & FEC_QUIRK_SWAP_FRAME)
				swap_buffer(bufaddr, frag_len);
		}

		addr = dma_map_single(&fep->pdev->dev, bufaddr, frag_len,
				      DMA_TO_DEVICE);
		if (dma_mapping_error(&fep->pdev->dev, addr)) {
			if (net_ratelimit())
				netdev_err(ndev, "Tx DMA memory map failed\n");
			goto dma_mapping_error;
		}

		bdp->cbd_bufaddr = cpu_to_fec32(addr);
		bdp->cbd_datlen = cpu_to_fec16(frag_len);
		/* Make sure the updates to rest of the descriptor are
		 * performed before transferring ownership.
		 */
		wmb();
		bdp->cbd_sc = cpu_to_fec16(status);
	}

	return bdp;
dma_mapping_error:
	bdp = txq->bd.cur;
	for (i = 0; i < frag; i++) {
		bdp = fec_enet_get_nextdesc(bdp, &txq->bd);
		dma_unmap_single(&fep->pdev->dev, fec32_to_cpu(bdp->cbd_bufaddr),
				 fec16_to_cpu(bdp->cbd_datlen), DMA_TO_DEVICE);
	}
	return ERR_PTR(-ENOMEM);
}

static int fec_enet_txq_submit_skb(struct fec_enet_priv_tx_q *txq,
				   struct sk_buff *skb, struct net_device *ndev)
{
	struct fec_enet_private *fep = netdev_priv(ndev);
	int nr_frags = skb_shinfo(skb)->nr_frags;
	struct bufdesc *bdp, *last_bdp;
	void *bufaddr;
	dma_addr_t addr;
	unsigned short status;
	unsigned short buflen;
	unsigned int estatus = 0;
	unsigned int index;
	int entries_free;

#ifdef CONFIG_KSZ_SWITCH
	struct ksz_sw *sw = fep->port.sw;
#endif

	entries_free = fec_enet_get_free_txdesc_num(txq);
	if (entries_free < MAX_SKB_FRAGS + 1) {
		dev_kfree_skb_any(skb);
		if (net_ratelimit())
			netdev_err(ndev, "NOT enough BD for SG!\n");
		return NETDEV_TX_OK;
	}

#ifdef CONFIG_KSZ_SWITCH
	if (sw_is_switch(sw)) {
		struct ksz_port *port = &fep->port;
		int len = skb->len;
		int header = 0;

		len = sw->net_ops->get_tx_len(sw, skb, port->first_port,
			&header);

		/* Hardware cannot generate checksum correctly for HSR frame. */
		if (skb->ip_summed && header > VLAN_HLEN) {
			struct sk_buff *nskb;

			nskb = dev_alloc_skb(len);
			if (nskb) {
				skb_copy_and_csum_dev(skb, nskb->data);
				skb->ip_summed = 0;
				nskb->len = skb->len;
				copy_old_skb(skb, nskb);
				skb = nskb;
				skb_set_tail_pointer(skb, skb->len);
			}
		}
	}
#endif

	/* Protocol checksum off-load for TCP and UDP. */
	if (fec_enet_clear_csum(skb, ndev)) {
		dev_kfree_skb_any(skb);
		return NETDEV_TX_OK;
	}

#ifdef CONFIG_KSZ_SWITCH
	if (sw_is_switch(sw)) {
		skb = sw->net_ops->final_skb(sw, skb, ndev, &fep->port);
		if (!skb)
			return NETDEV_TX_OK;
		nr_frags = skb_shinfo(skb)->nr_frags;
		fep = fep->hw_priv;
	}
#endif

	/* Fill in a Tx ring entry */
	bdp = txq->bd.cur;
	last_bdp = bdp;
	status = fec16_to_cpu(bdp->cbd_sc);
	status &= ~BD_ENET_TX_STATS;

	/* Set buffer length and buffer pointer */
	bufaddr = skb->data;
	buflen = skb_headlen(skb);

	index = fec_enet_get_bd_index(bdp, &txq->bd);
	if (((unsigned long) bufaddr) & fep->tx_align ||
		fep->quirks & FEC_QUIRK_SWAP_FRAME) {
		memcpy(txq->tx_bounce[index], skb->data, buflen);
		bufaddr = txq->tx_bounce[index];

		if (fep->quirks & FEC_QUIRK_SWAP_FRAME)
			swap_buffer(bufaddr, buflen);
	}

	/* Push the data cache so the CPM does not get stale memory data. */
	addr = dma_map_single(&fep->pdev->dev, bufaddr, buflen, DMA_TO_DEVICE);
	if (dma_mapping_error(&fep->pdev->dev, addr)) {
		dev_kfree_skb_any(skb);
		if (net_ratelimit())
			netdev_err(ndev, "Tx DMA memory map failed\n");
		return NETDEV_TX_OK;
	}

	if (nr_frags) {
		last_bdp = fec_enet_txq_submit_frag_skb(txq, skb, ndev);
		if (IS_ERR(last_bdp)) {
			dma_unmap_single(&fep->pdev->dev, addr,
					 buflen, DMA_TO_DEVICE);
			dev_kfree_skb_any(skb);
			return NETDEV_TX_OK;
		}
	} else {
		status |= (BD_ENET_TX_INTR | BD_ENET_TX_LAST);
#ifndef CONFIG_1588_PTP
		if (fep->bufdesc_ex) {
			estatus = BD_ENET_TX_INT;
			if (unlikely(skb_shinfo(skb)->tx_flags &
				SKBTX_HW_TSTAMP && fep->hwts_tx_en))
				estatus |= BD_ENET_TX_TS;
		}
#endif
	}
	bdp->cbd_bufaddr = cpu_to_fec32(addr);
	bdp->cbd_datlen = cpu_to_fec16(buflen);

	if (fep->bufdesc_ex) {

		struct bufdesc_ex *ebdp = (struct bufdesc_ex *)bdp;

#ifndef CONFIG_1588_PTP
		if (unlikely(skb_shinfo(skb)->tx_flags & SKBTX_HW_TSTAMP &&
			fep->hwts_tx_en))
			skb_shinfo(skb)->tx_flags |= SKBTX_IN_PROGRESS;
#endif

		if (fep->quirks & FEC_QUIRK_HAS_AVB)
			estatus |= FEC_TX_BD_FTYPE(txq->bd.qid);

		if (skb->ip_summed == CHECKSUM_PARTIAL)
			estatus |= BD_ENET_TX_PINS | BD_ENET_TX_IINS;

		ebdp->cbd_bdu = 0;
		ebdp->cbd_esc = cpu_to_fec32(estatus);
	}

	index = fec_enet_get_bd_index(last_bdp, &txq->bd);
	/* Save skb pointer */
	txq->tx_skbuff[index] = skb;

	/* Make sure the updates to rest of the descriptor are performed before
	 * transferring ownership.
	 */
	wmb();

	/* Send it on its way.  Tell FEC it's ready, interrupt when done,
	 * it's the last BD of the frame, and to put the CRC on the end.
	 */
	status |= (BD_ENET_TX_READY | BD_ENET_TX_TC);
	bdp->cbd_sc = cpu_to_fec16(status);

	/* If this was the last BD in the ring, start at the beginning again. */
	bdp = fec_enet_get_nextdesc(last_bdp, &txq->bd);

	skb_tx_timestamp(skb);

	/* Make sure the update to bdp and tx_skbuff are performed before
	 * txq->bd.cur.
	 */
	wmb();
	txq->bd.cur = bdp;

	/* Trigger transmission start */
	writel(0, txq->bd.reg_desc_active);

	return 0;
}

static int
fec_enet_txq_put_data_tso(struct fec_enet_priv_tx_q *txq, struct sk_buff *skb,
			  struct net_device *ndev,
			  struct bufdesc *bdp, int index, char *data,
			  int size, bool last_tcp, bool is_last)
{
	struct fec_enet_private *fep = netdev_priv(ndev);
	struct bufdesc_ex *ebdp = container_of(bdp, struct bufdesc_ex, desc);
	unsigned short status;
	unsigned int estatus = 0;
	dma_addr_t addr;

	status = fec16_to_cpu(bdp->cbd_sc);
	status &= ~BD_ENET_TX_STATS;

	status |= (BD_ENET_TX_TC | BD_ENET_TX_READY);

	if (((unsigned long) data) & fep->tx_align ||
		fep->quirks & FEC_QUIRK_SWAP_FRAME) {
		memcpy(txq->tx_bounce[index], data, size);
		data = txq->tx_bounce[index];

		if (fep->quirks & FEC_QUIRK_SWAP_FRAME)
			swap_buffer(data, size);
	}

	addr = dma_map_single(&fep->pdev->dev, data, size, DMA_TO_DEVICE);
	if (dma_mapping_error(&fep->pdev->dev, addr)) {
		dev_kfree_skb_any(skb);
		if (net_ratelimit())
			netdev_err(ndev, "Tx DMA memory map failed\n");
		return NETDEV_TX_BUSY;
	}

	bdp->cbd_datlen = cpu_to_fec16(size);
	bdp->cbd_bufaddr = cpu_to_fec32(addr);

	if (fep->bufdesc_ex) {
		if (fep->quirks & FEC_QUIRK_HAS_AVB)
			estatus |= FEC_TX_BD_FTYPE(txq->bd.qid);
		if (skb->ip_summed == CHECKSUM_PARTIAL)
			estatus |= BD_ENET_TX_PINS | BD_ENET_TX_IINS;
		ebdp->cbd_bdu = 0;
		ebdp->cbd_esc = cpu_to_fec32(estatus);
	}

	/* Handle the last BD specially */
	if (last_tcp)
		status |= (BD_ENET_TX_LAST | BD_ENET_TX_TC);
	if (is_last) {
		status |= BD_ENET_TX_INTR;
#ifndef CONFIG_1588_PTP
		if (fep->bufdesc_ex)
			ebdp->cbd_esc |= cpu_to_fec32(BD_ENET_TX_INT);
#endif
	}

	bdp->cbd_sc = cpu_to_fec16(status);

	return 0;
}

static int
fec_enet_txq_put_hdr_tso(struct fec_enet_priv_tx_q *txq,
			 struct sk_buff *skb, struct net_device *ndev,
			 struct bufdesc *bdp, int index)
{
	struct fec_enet_private *fep = netdev_priv(ndev);
	int hdr_len = skb_transport_offset(skb) + tcp_hdrlen(skb);
	struct bufdesc_ex *ebdp = container_of(bdp, struct bufdesc_ex, desc);
	void *bufaddr;
	unsigned long dmabuf;
	unsigned short status;
	unsigned int estatus = 0;

	status = fec16_to_cpu(bdp->cbd_sc);
	status &= ~BD_ENET_TX_STATS;
	status |= (BD_ENET_TX_TC | BD_ENET_TX_READY);

	bufaddr = txq->tso_hdrs + index * TSO_HEADER_SIZE;
	dmabuf = txq->tso_hdrs_dma + index * TSO_HEADER_SIZE;
	if (((unsigned long)bufaddr) & fep->tx_align ||
		fep->quirks & FEC_QUIRK_SWAP_FRAME) {
		memcpy(txq->tx_bounce[index], skb->data, hdr_len);
		bufaddr = txq->tx_bounce[index];

		if (fep->quirks & FEC_QUIRK_SWAP_FRAME)
			swap_buffer(bufaddr, hdr_len);

		dmabuf = dma_map_single(&fep->pdev->dev, bufaddr,
					hdr_len, DMA_TO_DEVICE);
		if (dma_mapping_error(&fep->pdev->dev, dmabuf)) {
			dev_kfree_skb_any(skb);
			if (net_ratelimit())
				netdev_err(ndev, "Tx DMA memory map failed\n");
			return NETDEV_TX_BUSY;
		}
	}

	bdp->cbd_bufaddr = cpu_to_fec32(dmabuf);
	bdp->cbd_datlen = cpu_to_fec16(hdr_len);

	if (fep->bufdesc_ex) {
		if (fep->quirks & FEC_QUIRK_HAS_AVB)
			estatus |= FEC_TX_BD_FTYPE(txq->bd.qid);
		if (skb->ip_summed == CHECKSUM_PARTIAL)
			estatus |= BD_ENET_TX_PINS | BD_ENET_TX_IINS;
		ebdp->cbd_bdu = 0;
		ebdp->cbd_esc = cpu_to_fec32(estatus);
	}

	bdp->cbd_sc = cpu_to_fec16(status);

	return 0;
}

static int fec_enet_txq_submit_tso(struct fec_enet_priv_tx_q *txq,
				   struct sk_buff *skb,
				   struct net_device *ndev)
{
	struct fec_enet_private *fep = netdev_priv(ndev);
	int hdr_len = skb_transport_offset(skb) + tcp_hdrlen(skb);
	int total_len, data_left;
	struct bufdesc *bdp = txq->bd.cur;
	struct tso_t tso;
	unsigned int index = 0;
	int ret;

	if (tso_count_descs(skb) >= fec_enet_get_free_txdesc_num(txq)) {
		dev_kfree_skb_any(skb);
		if (net_ratelimit())
			netdev_err(ndev, "NOT enough BD for TSO!\n");
		return NETDEV_TX_OK;
	}

	/* Protocol checksum off-load for TCP and UDP. */
	if (fec_enet_clear_csum(skb, ndev)) {
		dev_kfree_skb_any(skb);
		return NETDEV_TX_OK;
	}

	/* Initialize the TSO handler, and prepare the first payload */
	tso_start(skb, &tso);

	total_len = skb->len - hdr_len;
	while (total_len > 0) {
		char *hdr;

		index = fec_enet_get_bd_index(bdp, &txq->bd);
		data_left = min_t(int, skb_shinfo(skb)->gso_size, total_len);
		total_len -= data_left;

		/* prepare packet headers: MAC + IP + TCP */
		hdr = txq->tso_hdrs + index * TSO_HEADER_SIZE;
		tso_build_hdr(skb, hdr, &tso, data_left, total_len == 0);
		ret = fec_enet_txq_put_hdr_tso(txq, skb, ndev, bdp, index);
		if (ret)
			goto err_release;

		while (data_left > 0) {
			int size;

			size = min_t(int, tso.size, data_left);
			bdp = fec_enet_get_nextdesc(bdp, &txq->bd);
			index = fec_enet_get_bd_index(bdp, &txq->bd);
			ret = fec_enet_txq_put_data_tso(txq, skb, ndev,
							bdp, index,
							tso.data, size,
							size == data_left,
							total_len == 0);
			if (ret)
				goto err_release;

			data_left -= size;
			tso_build_data(skb, &tso, size);
		}

		bdp = fec_enet_get_nextdesc(bdp, &txq->bd);
	}

	/* Save skb pointer */
	txq->tx_skbuff[index] = skb;

	skb_tx_timestamp(skb);
	txq->bd.cur = bdp;

	/* Trigger transmission start */
	if (!(fep->quirks & FEC_QUIRK_ERR007885) ||
	    !readl(txq->bd.reg_desc_active) ||
	    !readl(txq->bd.reg_desc_active) ||
	    !readl(txq->bd.reg_desc_active) ||
	    !readl(txq->bd.reg_desc_active))
		writel(0, txq->bd.reg_desc_active);

	return 0;

err_release:
	/* TODO: Release all used data descriptors for TSO */
	return ret;
}

static netdev_tx_t
fec_enet_start_xmit(struct sk_buff *skb, struct net_device *ndev)
{
	struct fec_enet_private *fep = netdev_priv(ndev);
	int entries_free;
	unsigned short queue;
	struct fec_enet_priv_tx_q *txq;
	struct netdev_queue *nq;
	int ret;

#ifdef CONFIG_KSZ_SWITCH
	struct fec_enet_private *pfep = fep;
	unsigned long flags;

	fep = fep->hw_priv;
#endif

	queue = skb_get_queue_mapping(skb);
	txq = fep->tx_queue[queue];
	nq = netdev_get_tx_queue(ndev, queue);

#ifdef CONFIG_KSZ_SWITCH
	/* May be called from switch driver. */
	if (netif_tx_queue_stopped(nq))
		return NETDEV_TX_BUSY;

	spin_lock_irqsave(&fep->tx_lock, flags);
#endif

	if (skb_is_gso(skb))
		ret = fec_enet_txq_submit_tso(txq, skb, ndev);
	else
		ret = fec_enet_txq_submit_skb(txq, skb, ndev);

#ifdef CONFIG_KSZ_SWITCH
	if (ret)
		spin_unlock_irqrestore(&fep->tx_lock, flags);
#endif
	if (ret)
		return ret;

	entries_free = fec_enet_get_free_txdesc_num(txq);
	if (entries_free <= txq->tx_stop_threshold)
		netif_tx_stop_queue(nq);

#ifdef CONFIG_KSZ_SWITCH
	if (netif_tx_queue_stopped(nq))
		stop_dev_queues(pfep->port.sw, ndev, pfep, queue);
	spin_unlock_irqrestore(&fep->tx_lock, flags);
#endif

	return NETDEV_TX_OK;
}

/* Init RX & TX buffer descriptors
 */
static void fec_enet_bd_init(struct net_device *dev)
{
	struct fec_enet_private *fep = netdev_priv(dev);
	struct fec_enet_priv_tx_q *txq;
	struct fec_enet_priv_rx_q *rxq;
	struct bufdesc *bdp;
	unsigned int i;
	unsigned int q;

	for (q = 0; q < fep->num_rx_queues; q++) {
		/* Initialize the receive buffer descriptors. */
		rxq = fep->rx_queue[q];
		bdp = rxq->bd.base;

		for (i = 0; i < rxq->bd.ring_size; i++) {

			/* Initialize the BD for every fragment in the page. */
			if (bdp->cbd_bufaddr)
				bdp->cbd_sc = cpu_to_fec16(BD_ENET_RX_EMPTY);
			else
				bdp->cbd_sc = cpu_to_fec16(0);
			bdp = fec_enet_get_nextdesc(bdp, &rxq->bd);
		}

		/* Set the last buffer to wrap */
		bdp = fec_enet_get_prevdesc(bdp, &rxq->bd);
		bdp->cbd_sc |= cpu_to_fec16(BD_SC_WRAP);

		rxq->bd.cur = rxq->bd.base;
	}

	for (q = 0; q < fep->num_tx_queues; q++) {
		/* ...and the same for transmit */
		txq = fep->tx_queue[q];
		bdp = txq->bd.base;
		txq->bd.cur = bdp;

		for (i = 0; i < txq->bd.ring_size; i++) {
			/* Initialize the BD for every fragment in the page. */
			bdp->cbd_sc = cpu_to_fec16(0);
			if (bdp->cbd_bufaddr &&
			    !IS_TSO_HEADER(txq, fec32_to_cpu(bdp->cbd_bufaddr)))
				dma_unmap_single(&fep->pdev->dev,
						 fec32_to_cpu(bdp->cbd_bufaddr),
						 fec16_to_cpu(bdp->cbd_datlen),
						 DMA_TO_DEVICE);
			if (txq->tx_skbuff[i]) {
				dev_kfree_skb_any(txq->tx_skbuff[i]);
				txq->tx_skbuff[i] = NULL;
			}
			bdp->cbd_bufaddr = cpu_to_fec32(0);
			bdp = fec_enet_get_nextdesc(bdp, &txq->bd);
		}

		/* Set the last buffer to wrap */
		bdp = fec_enet_get_prevdesc(bdp, &txq->bd);
		bdp->cbd_sc |= cpu_to_fec16(BD_SC_WRAP);
		txq->dirty_tx = bdp;
	}
}

static void fec_enet_active_rxring(struct net_device *ndev)
{
	struct fec_enet_private *fep = netdev_priv(ndev);
	int i;

	for (i = 0; i < fep->num_rx_queues; i++)
		writel(0, fep->rx_queue[i]->bd.reg_desc_active);
}

static void fec_enet_enable_ring(struct net_device *ndev)
{
	struct fec_enet_private *fep = netdev_priv(ndev);
	struct fec_enet_priv_tx_q *txq;
	struct fec_enet_priv_rx_q *rxq;
	int i;

	for (i = 0; i < fep->num_rx_queues; i++) {
		rxq = fep->rx_queue[i];
		writel(rxq->bd.dma, fep->hwp + FEC_R_DES_START(i));
		writel(PKT_MAXBUF_SIZE, fep->hwp + FEC_R_BUFF_SIZE(i));

		/* enable DMA1/2 */
		if (i)
			writel(RCMR_MATCHEN | RCMR_CMP(i),
			       fep->hwp + FEC_RCMR(i));
	}

	for (i = 0; i < fep->num_tx_queues; i++) {
		txq = fep->tx_queue[i];
		writel(txq->bd.dma, fep->hwp + FEC_X_DES_START(i));

		/* enable DMA1/2 */
		if (i)
			writel(DMA_CLASS_EN | IDLE_SLOPE(i),
			       fep->hwp + FEC_DMA_CFG(i));
	}
}

static void fec_enet_reset_skb(struct net_device *ndev)
{
	struct fec_enet_private *fep = netdev_priv(ndev);
	struct fec_enet_priv_tx_q *txq;
	int i, j;

	for (i = 0; i < fep->num_tx_queues; i++) {
		txq = fep->tx_queue[i];

		for (j = 0; j < txq->bd.ring_size; j++) {
			if (txq->tx_skbuff[j]) {
				dev_kfree_skb_any(txq->tx_skbuff[j]);
				txq->tx_skbuff[j] = NULL;
			}
		}
	}
}

/*
 * This function is called to start or restart the FEC during a link
 * change, transmit timeout, or to reconfigure the FEC.  The network
 * packet processing for this device must be stopped before this call.
 */
static void
fec_restart(struct net_device *ndev)
{
	struct fec_enet_private *fep = netdev_priv(ndev);
	u32 val;
	u32 temp_mac[2];
	u32 rcntl = OPT_FRAME_SIZE | 0x04;
	u32 ecntl = 0x2; /* ETHEREN */

	/* Whack a reset.  We should wait for this.
	 * For i.MX6SX SOC, enet use AXI bus, we use disable MAC
	 * instead of reset MAC itself.
	 */
	if (fep->quirks & FEC_QUIRK_HAS_AVB) {
		writel(0, fep->hwp + FEC_ECNTRL);
	} else {
		writel(1, fep->hwp + FEC_ECNTRL);
		udelay(10);
	}

	/*
	 * enet-mac reset will reset mac address registers too,
	 * so need to reconfigure it.
	 */
	memcpy(&temp_mac, ndev->dev_addr, ETH_ALEN);
	writel((__force u32)cpu_to_be32(temp_mac[0]),
	       fep->hwp + FEC_ADDR_LOW);
	writel((__force u32)cpu_to_be32(temp_mac[1]),
	       fep->hwp + FEC_ADDR_HIGH);

	/* Clear any outstanding interrupt. */
	writel(0xffffffff, fep->hwp + FEC_IEVENT);

	fec_enet_bd_init(ndev);

	fec_enet_enable_ring(ndev);

	/* Reset tx SKB buffers. */
	fec_enet_reset_skb(ndev);

	/* Enable MII mode */
	if (fep->full_duplex == DUPLEX_FULL) {
		/* FD enable */
		writel(0x04, fep->hwp + FEC_X_CNTRL);
	} else {
		/* No Rcv on Xmit */
		rcntl |= 0x02;
		writel(0x0, fep->hwp + FEC_X_CNTRL);
	}

	/* Set MII speed */
	writel(fep->phy_speed, fep->hwp + FEC_MII_SPEED);

#if !defined(CONFIG_M5272)
	if (fep->quirks & FEC_QUIRK_HAS_RACC) {
		val = readl(fep->hwp + FEC_RACC);
		/* align IP header */
		val |= FEC_RACC_SHIFT16;
		if (fep->csum_flags & FLAG_RX_CSUM_ENABLED)
			/* set RX checksum */
			val |= FEC_RACC_OPTIONS;
		else
			val &= ~FEC_RACC_OPTIONS;
		writel(val, fep->hwp + FEC_RACC);
		writel(PKT_MAXBUF_SIZE, fep->hwp + FEC_FTRL);
	}
#endif

	/*
	 * The phy interface and speed need to get configured
	 * differently on enet-mac.
	 */
	if (fep->quirks & FEC_QUIRK_ENET_MAC) {
		/* Enable flow control and length check */
		rcntl |= 0x40000000 | 0x00000020;

		/* RGMII, RMII or MII */
		if (fep->phy_interface == PHY_INTERFACE_MODE_RGMII ||
		    fep->phy_interface == PHY_INTERFACE_MODE_RGMII_ID ||
		    fep->phy_interface == PHY_INTERFACE_MODE_RGMII_RXID ||
		    fep->phy_interface == PHY_INTERFACE_MODE_RGMII_TXID)
			rcntl |= (1 << 6);
		else if (fep->phy_interface == PHY_INTERFACE_MODE_RMII)
			rcntl |= (1 << 8);
		else
			rcntl &= ~(1 << 8);

		/* 1G, 100M or 10M */
		if (ndev->phydev) {
			if (ndev->phydev->speed == SPEED_1000)
				ecntl |= (1 << 5);
			else if (ndev->phydev->speed == SPEED_100)
				rcntl &= ~(1 << 9);
			else
				rcntl |= (1 << 9);
		}
	} else {
#ifdef FEC_MIIGSK_ENR
		if (fep->quirks & FEC_QUIRK_USE_GASKET) {
			u32 cfgr;
			/* disable the gasket and wait */
			writel(0, fep->hwp + FEC_MIIGSK_ENR);
			while (readl(fep->hwp + FEC_MIIGSK_ENR) & 4)
				udelay(1);

			/*
			 * configure the gasket:
			 *   RMII, 50 MHz, no loopback, no echo
			 *   MII, 25 MHz, no loopback, no echo
			 */
			cfgr = (fep->phy_interface == PHY_INTERFACE_MODE_RMII)
				? BM_MIIGSK_CFGR_RMII : BM_MIIGSK_CFGR_MII;
			if (ndev->phydev && ndev->phydev->speed == SPEED_10)
				cfgr |= BM_MIIGSK_CFGR_FRCONT_10M;
			writel(cfgr, fep->hwp + FEC_MIIGSK_CFGR);

			/* re-enable the gasket */
			writel(2, fep->hwp + FEC_MIIGSK_ENR);
		}
#endif
	}

#if !defined(CONFIG_M5272)
	/* enable pause frame*/
	if ((fep->pause_flag & FEC_PAUSE_FLAG_ENABLE) ||
	    ((fep->pause_flag & FEC_PAUSE_FLAG_AUTONEG) &&
	     ndev->phydev && ndev->phydev->pause)) {
		rcntl |= FEC_ENET_FCE;

		/* set FIFO threshold parameter to reduce overrun */
		writel(FEC_ENET_RSEM_V, fep->hwp + FEC_R_FIFO_RSEM);
		writel(FEC_ENET_RSFL_V, fep->hwp + FEC_R_FIFO_RSFL);
		writel(FEC_ENET_RAEM_V, fep->hwp + FEC_R_FIFO_RAEM);
		writel(FEC_ENET_RAFL_V, fep->hwp + FEC_R_FIFO_RAFL);

		/* OPD */
		writel(FEC_ENET_OPD_V, fep->hwp + FEC_OPD);
	} else {
		rcntl &= ~FEC_ENET_FCE;
	}
#endif /* !defined(CONFIG_M5272) */

	writel(rcntl, fep->hwp + FEC_R_CNTRL);

	/* Setup multicast filter. */
	set_multicast_list(ndev);
#ifndef CONFIG_M5272
	writel(0, fep->hwp + FEC_HASH_TABLE_HIGH);
	writel(0, fep->hwp + FEC_HASH_TABLE_LOW);
#endif

	if (fep->quirks & FEC_QUIRK_ENET_MAC) {
		/* enable ENET endian swap */
		ecntl |= (1 << 8);
		/* enable ENET store and forward mode */
		writel(1 << 8, fep->hwp + FEC_X_WMRK);
	}

	if (fep->bufdesc_ex)
		ecntl |= (1 << 4);

#ifndef CONFIG_M5272
	/* Enable the MIB statistic event counters */
	writel(0 << 31, fep->hwp + FEC_MIB_CTRLSTAT);
#endif

	/* And last, enable the transmit and receive processing */
	writel(ecntl, fep->hwp + FEC_ECNTRL);
	fec_enet_active_rxring(ndev);

#ifndef CONFIG_1588_PTP
	if (fep->bufdesc_ex)
		fec_ptp_start_cyclecounter(ndev);
#endif

	/* Enable interrupts we wish to service */
	if (fep->link)
		writel(FEC_DEFAULT_IMASK, fep->hwp + FEC_IMASK);
	else
		writel(FEC_ENET_MII, fep->hwp + FEC_IMASK);

	/* Init the interrupt coalescing */
	fec_enet_itr_coal_init(ndev);

}

static void fec_enet_stop_mode(struct fec_enet_private *fep, bool enabled)
{
	struct fec_platform_data *pdata = fep->pdev->dev.platform_data;
	struct fec_stop_mode_gpr *stop_gpr = &fep->stop_gpr;

	if (stop_gpr->gpr) {
		if (enabled)
			regmap_update_bits(stop_gpr->gpr, stop_gpr->reg,
					   BIT(stop_gpr->bit),
					   BIT(stop_gpr->bit));
		else
			regmap_update_bits(stop_gpr->gpr, stop_gpr->reg,
					   BIT(stop_gpr->bit), 0);
	} else if (pdata && pdata->sleep_mode_enable) {
		pdata->sleep_mode_enable(enabled);
	}
}

static void
fec_stop(struct net_device *ndev)
{
	struct fec_enet_private *fep = netdev_priv(ndev);
	u32 rmii_mode = readl(fep->hwp + FEC_R_CNTRL) & (1 << 8);
	u32 val;

	/* We cannot expect a graceful transmit stop without link !!! */
	if (fep->link) {
		writel(1, fep->hwp + FEC_X_CNTRL); /* Graceful transmit stop */
		udelay(10);
		if (!(readl(fep->hwp + FEC_IEVENT) & FEC_ENET_GRA))
			netdev_err(ndev, "Graceful transmit stop did not complete!\n");
	}

	/* Whack a reset.  We should wait for this.
	 * For i.MX6SX SOC, enet use AXI bus, we use disable MAC
	 * instead of reset MAC itself.
	 */
	if (!(fep->wol_flag & FEC_WOL_FLAG_SLEEP_ON)) {
		if (fep->quirks & FEC_QUIRK_HAS_AVB) {
			writel(0, fep->hwp + FEC_ECNTRL);
		} else {
			writel(1, fep->hwp + FEC_ECNTRL);
			udelay(10);
		}
		writel(FEC_DEFAULT_IMASK, fep->hwp + FEC_IMASK);
	} else {
		writel(FEC_DEFAULT_IMASK | FEC_ENET_WAKEUP, fep->hwp + FEC_IMASK);
		val = readl(fep->hwp + FEC_ECNTRL);
		val |= (FEC_ECR_MAGICEN | FEC_ECR_SLEEP);
		writel(val, fep->hwp + FEC_ECNTRL);
		fec_enet_stop_mode(fep, true);
	}
	writel(fep->phy_speed, fep->hwp + FEC_MII_SPEED);

	/* We have to keep ENET enabled to have MII interrupt stay working */
	if (fep->quirks & FEC_QUIRK_ENET_MAC &&
		!(fep->wol_flag & FEC_WOL_FLAG_SLEEP_ON)) {
		writel(2, fep->hwp + FEC_ECNTRL);
		writel(rmii_mode, fep->hwp + FEC_R_CNTRL);
	}
}


static void
fec_timeout(struct net_device *ndev)
{
	struct fec_enet_private *fep = netdev_priv(ndev);

#ifdef CONFIG_KSZ_SWITCH
	fep = fep->hw_priv;
#endif
	fec_dump(ndev);

	ndev->stats.tx_errors++;

	schedule_work(&fep->tx_timeout_work);
}

static void fec_enet_timeout_work(struct work_struct *work)
{
	struct fec_enet_private *fep =
		container_of(work, struct fec_enet_private, tx_timeout_work);
	struct net_device *ndev = fep->netdev;

	rtnl_lock();
	if (netif_device_present(ndev) || netif_running(ndev)) {
		napi_disable(&fep->napi);
		netif_tx_lock_bh(ndev);
		fec_restart(ndev);
		netif_tx_wake_all_queues(ndev);
#ifdef CONFIG_KSZ_SWITCH
		wake_dev_queues(fep->port.sw, fep->netdev, 0);
#endif
		netif_tx_unlock_bh(ndev);
		napi_enable(&fep->napi);
	}
	rtnl_unlock();
}

#ifndef CONFIG_1588_PTP
static void
fec_enet_hwtstamp(struct fec_enet_private *fep, unsigned ts,
	struct skb_shared_hwtstamps *hwtstamps)
{
	unsigned long flags;
	u64 ns;

	spin_lock_irqsave(&fep->tmreg_lock, flags);
	ns = timecounter_cyc2time(&fep->tc, ts);
	spin_unlock_irqrestore(&fep->tmreg_lock, flags);

	memset(hwtstamps, 0, sizeof(*hwtstamps));
	hwtstamps->hwtstamp = ns_to_ktime(ns);
}
#endif

static void
fec_enet_tx_queue(struct net_device *ndev, u16 queue_id)
{
	struct	fec_enet_private *fep;
	struct bufdesc *bdp;
	unsigned short status;
	struct	sk_buff	*skb;
	struct fec_enet_priv_tx_q *txq;
	struct netdev_queue *nq;
	int	index = 0;
	int	entries_free;

	fep = netdev_priv(ndev);

	queue_id = FEC_ENET_GET_QUQUE(queue_id);

	txq = fep->tx_queue[queue_id];
	/* get next bdp of dirty_tx */
	nq = netdev_get_tx_queue(ndev, queue_id);
	bdp = txq->dirty_tx;

	/* get next bdp of dirty_tx */
	bdp = fec_enet_get_nextdesc(bdp, &txq->bd);

	while (bdp != READ_ONCE(txq->bd.cur)) {
		/* Order the load of bd.cur and cbd_sc */
		rmb();
		status = fec16_to_cpu(READ_ONCE(bdp->cbd_sc));
		if (status & BD_ENET_TX_READY)
			break;

		index = fec_enet_get_bd_index(bdp, &txq->bd);

		skb = txq->tx_skbuff[index];
		txq->tx_skbuff[index] = NULL;
		if (!IS_TSO_HEADER(txq, fec32_to_cpu(bdp->cbd_bufaddr)))
			dma_unmap_single(&fep->pdev->dev,
					 fec32_to_cpu(bdp->cbd_bufaddr),
					 fec16_to_cpu(bdp->cbd_datlen),
					 DMA_TO_DEVICE);
		bdp->cbd_bufaddr = cpu_to_fec32(0);
		if (!skb)
			goto skb_done;

		/* Check for errors. */
		if (status & (BD_ENET_TX_HB | BD_ENET_TX_LC |
				   BD_ENET_TX_RL | BD_ENET_TX_UN |
				   BD_ENET_TX_CSL)) {
			ndev->stats.tx_errors++;
			if (status & BD_ENET_TX_HB)  /* No heartbeat */
				ndev->stats.tx_heartbeat_errors++;
			if (status & BD_ENET_TX_LC)  /* Late collision */
				ndev->stats.tx_window_errors++;
			if (status & BD_ENET_TX_RL)  /* Retrans limit */
				ndev->stats.tx_aborted_errors++;
			if (status & BD_ENET_TX_UN)  /* Underrun */
				ndev->stats.tx_fifo_errors++;
			if (status & BD_ENET_TX_CSL) /* Carrier lost */
				ndev->stats.tx_carrier_errors++;
		} else {
#ifdef CONFIG_KSZ_SWITCH
			skb->dev->stats.tx_packets++;
			skb->dev->stats.tx_bytes += skb->len;
#else
			ndev->stats.tx_packets++;
			ndev->stats.tx_bytes += skb->len;
#endif
		}

#ifndef CONFIG_1588_PTP
		if (unlikely(skb_shinfo(skb)->tx_flags & SKBTX_IN_PROGRESS) &&
			fep->bufdesc_ex) {
			struct skb_shared_hwtstamps shhwtstamps;
			struct bufdesc_ex *ebdp = (struct bufdesc_ex *)bdp;

			fec_enet_hwtstamp(fep, fec32_to_cpu(ebdp->ts), &shhwtstamps);
			skb_tstamp_tx(skb, &shhwtstamps);
		}
#endif

		/* Deferred means some collisions occurred during transmit,
		 * but we eventually sent the packet OK.
		 */
		if (status & BD_ENET_TX_DEF)
			ndev->stats.collisions++;

		/* Free the sk buffer associated with this last transmit */
		dev_kfree_skb_any(skb);
skb_done:
		/* Make sure the update to bdp and tx_skbuff are performed
		 * before dirty_tx
		 */
		wmb();
		txq->dirty_tx = bdp;

		/* Update pointer to next buffer descriptor to be transmitted */
		bdp = fec_enet_get_nextdesc(bdp, &txq->bd);

		/* Since we have freed up a buffer, the ring is no longer full
		 */
		if (netif_tx_queue_stopped(nq)) {
#ifdef CONFIG_KSZ_SWITCH
			unsigned long flags;

			/* Need to block transmit when manipulating the
			 * transmit queue of all network devices.
			 */
			spin_lock_irqsave(&fep->tx_lock, flags);
#endif
			entries_free = fec_enet_get_free_txdesc_num(txq);
			if (entries_free >= txq->tx_wake_threshold)
				netif_tx_wake_queue(nq);

#ifdef CONFIG_KSZ_SWITCH
			if (!netif_tx_queue_stopped(nq))
				wake_dev_queues(fep->port.sw, fep->netdev,
						queue_id);
			spin_unlock_irqrestore(&fep->tx_lock, flags);
#endif
		}
	}

	/* ERR006358: Keep the transmitter going */
	if (bdp != txq->bd.cur &&
	    readl(txq->bd.reg_desc_active) == 0)
		writel(0, txq->bd.reg_desc_active);
}

static void
fec_enet_tx(struct net_device *ndev)
{
	struct fec_enet_private *fep = netdev_priv(ndev);
	u16 queue_id;
	/* First process class A queue, then Class B and Best Effort queue */
	for_each_set_bit(queue_id, &fep->work_tx, FEC_ENET_MAX_TX_QS) {
		clear_bit(queue_id, &fep->work_tx);
		fec_enet_tx_queue(ndev, queue_id);
	}
	return;
}

static int
fec_enet_new_rxbdp(struct net_device *ndev, struct bufdesc *bdp, struct sk_buff *skb)
{
	struct  fec_enet_private *fep = netdev_priv(ndev);
	int off;

	off = ((unsigned long)skb->data) & fep->rx_align;
	if (off)
		skb_reserve(skb, fep->rx_align + 1 - off);

	bdp->cbd_bufaddr = cpu_to_fec32(dma_map_single(&fep->pdev->dev, skb->data, FEC_ENET_RX_FRSIZE - fep->rx_align, DMA_FROM_DEVICE));
	if (dma_mapping_error(&fep->pdev->dev, fec32_to_cpu(bdp->cbd_bufaddr))) {
		if (net_ratelimit())
			netdev_err(ndev, "Rx DMA memory map failed\n");
		return -ENOMEM;
	}

	return 0;
}

static bool fec_enet_copybreak(struct net_device *ndev, struct sk_buff **skb,
			       struct bufdesc *bdp, u32 length, bool swap)
{
	struct  fec_enet_private *fep = netdev_priv(ndev);
	struct sk_buff *new_skb;

	if (length > fep->rx_copybreak)
		return false;

	new_skb = netdev_alloc_skb(ndev, length);
	if (!new_skb)
		return false;

	dma_sync_single_for_cpu(&fep->pdev->dev,
				fec32_to_cpu(bdp->cbd_bufaddr),
				FEC_ENET_RX_FRSIZE - fep->rx_align,
				DMA_FROM_DEVICE);
	if (!swap)
		memcpy(new_skb->data, (*skb)->data, length);
	else
		swap_buffer2(new_skb->data, (*skb)->data, length);
	*skb = new_skb;

	return true;
}

/* During a receive, the bd_rx.cur points to the current incoming buffer.
 * When we update through the ring, if the next incoming buffer has
 * not been given to the system, we just set the empty indicator,
 * effectively tossing the packet.
 */
static int
fec_enet_rx_queue(struct net_device *ndev, int budget, u16 queue_id)
{
	struct fec_enet_private *fep = netdev_priv(ndev);
	struct fec_enet_priv_rx_q *rxq;
	struct bufdesc *bdp;
	unsigned short status;
	struct  sk_buff *skb_new = NULL;
	struct  sk_buff *skb;
	ushort	pkt_len;
	__u8 *data;
	int	pkt_received = 0;
	struct	bufdesc_ex *ebdp = NULL;
	bool	vlan_packet_rcvd = false;
	u16	vlan_tag;
	int	index = 0;
	bool	is_copybreak;
	bool	need_swap = fep->quirks & FEC_QUIRK_SWAP_FRAME;

#ifdef CONFIG_KSZ_SWITCH
	struct ksz_sw *sw = fep->port.sw;
	struct net_device *orig_dev = ndev;
#endif

#ifdef CONFIG_M532x
	flush_cache_all();
#endif
	queue_id = FEC_ENET_GET_QUQUE(queue_id);
	rxq = fep->rx_queue[queue_id];

	/* First, grab all of the stats for the incoming packet.
	 * These get messed up if we get called due to a busy condition.
	 */
	bdp = rxq->bd.cur;

	while (!((status = fec16_to_cpu(bdp->cbd_sc)) & BD_ENET_RX_EMPTY)) {

		if (pkt_received >= budget)
			break;
		pkt_received++;

		writel(FEC_ENET_RXF, fep->hwp + FEC_IEVENT);

		/* Check for errors. */
		status ^= BD_ENET_RX_LAST;
		if (status & (BD_ENET_RX_LG | BD_ENET_RX_SH | BD_ENET_RX_NO |
			   BD_ENET_RX_CR | BD_ENET_RX_OV | BD_ENET_RX_LAST |
			   BD_ENET_RX_CL)) {
			ndev->stats.rx_errors++;
			if (status & BD_ENET_RX_OV) {
				/* FIFO overrun */
				ndev->stats.rx_fifo_errors++;
				goto rx_processing_done;
			}
			if (status & (BD_ENET_RX_LG | BD_ENET_RX_SH
						| BD_ENET_RX_LAST)) {
				/* Frame too long or too short. */
				ndev->stats.rx_length_errors++;
				if (status & BD_ENET_RX_LAST)
					netdev_err(ndev, "rcv is not +last\n");
			}
			if (status & BD_ENET_RX_CR)	/* CRC Error */
				ndev->stats.rx_crc_errors++;
			/* Report late collisions as a frame error. */
			if (status & (BD_ENET_RX_NO | BD_ENET_RX_CL))
				ndev->stats.rx_frame_errors++;
			goto rx_processing_done;
		}

		/* Process the incoming frame. */
#ifndef CONFIG_KSZ_SWITCH
		ndev->stats.rx_packets++;
#endif
		pkt_len = fec16_to_cpu(bdp->cbd_datlen);
#ifndef CONFIG_KSZ_SWITCH
		ndev->stats.rx_bytes += pkt_len;
#endif

		index = fec_enet_get_bd_index(bdp, &rxq->bd);
		skb = rxq->rx_skbuff[index];

		/* The packet length includes FCS, but we don't want to
		 * include that when passing upstream as it messes up
		 * bridging applications.
		 */
		is_copybreak = fec_enet_copybreak(ndev, &skb, bdp, pkt_len - 4,
						  need_swap);
		if (!is_copybreak) {
			skb_new = netdev_alloc_skb(ndev, FEC_ENET_RX_FRSIZE);
			if (unlikely(!skb_new)) {
				ndev->stats.rx_dropped++;
				goto rx_processing_done;
			}
			dma_unmap_single(&fep->pdev->dev,
					 fec32_to_cpu(bdp->cbd_bufaddr),
					 FEC_ENET_RX_FRSIZE - fep->rx_align,
					 DMA_FROM_DEVICE);
		}

		prefetch(skb->data - NET_IP_ALIGN);
		skb_put(skb, pkt_len - 4);
		data = skb->data;

		if (!is_copybreak && need_swap)
			swap_buffer(data, pkt_len);

#if !defined(CONFIG_M5272)
		if (fep->quirks & FEC_QUIRK_HAS_RACC)
			data = skb_pull_inline(skb, 2);
#endif

#ifdef CONFIG_KSZ_SWITCH
		if (sw_is_switch(sw)) {
			struct net_device *dev;

			dev = sw_rx_proc(sw, skb, data);
			if (!dev)
				goto rx_done;
			ndev = dev;
		}
		ndev->stats.rx_packets++;
		ndev->stats.rx_bytes += pkt_len;
#endif

		/* Extract the enhanced buffer descriptor */
		ebdp = NULL;
		if (fep->bufdesc_ex)
			ebdp = (struct bufdesc_ex *)bdp;

		/* If this is a VLAN packet remove the VLAN Tag */
		vlan_packet_rcvd = false;
		if ((ndev->features & NETIF_F_HW_VLAN_CTAG_RX) &&
		    fep->bufdesc_ex &&
		    (ebdp->cbd_esc & cpu_to_fec32(BD_ENET_RX_VLAN))) {
			/* Push and remove the vlan tag */
			struct vlan_hdr *vlan_header =
					(struct vlan_hdr *) (data + ETH_HLEN);
			vlan_tag = ntohs(vlan_header->h_vlan_TCI);

			vlan_packet_rcvd = true;

			memmove(skb->data + VLAN_HLEN, data, ETH_ALEN * 2);
			skb_pull(skb, VLAN_HLEN);
		}

		skb->protocol = eth_type_trans(skb, ndev);

#ifndef CONFIG_1588_PTP
		/* Get receive timestamp from the skb */
		if (fep->hwts_rx_en && fep->bufdesc_ex)
			fec_enet_hwtstamp(fep, fec32_to_cpu(ebdp->ts),
					  skb_hwtstamps(skb));
#endif

		if (fep->bufdesc_ex &&
		    (fep->csum_flags & FLAG_RX_CSUM_ENABLED)) {
			if (!(ebdp->cbd_esc & cpu_to_fec32(FLAG_RX_CSUM_ERROR))) {
				/* don't check it */
				skb->ip_summed = CHECKSUM_UNNECESSARY;
			} else {
				skb_checksum_none_assert(skb);
			}
		}

		/* Handle received VLAN packets */
		if (vlan_packet_rcvd)
			__vlan_hwaccel_put_tag(skb,
					       htons(ETH_P_8021Q),
					       vlan_tag);

		napi_gro_receive(&fep->napi, skb);

#ifdef CONFIG_KSZ_SWITCH
rx_done:
		ndev = orig_dev;
#endif
		if (is_copybreak) {
			dma_sync_single_for_device(&fep->pdev->dev,
						   fec32_to_cpu(bdp->cbd_bufaddr),
						   FEC_ENET_RX_FRSIZE - fep->rx_align,
						   DMA_FROM_DEVICE);
		} else {
			rxq->rx_skbuff[index] = skb_new;
			fec_enet_new_rxbdp(ndev, bdp, skb_new);
		}

rx_processing_done:
		/* Clear the status flags for this buffer */
		status &= ~BD_ENET_RX_STATS;

		/* Mark the buffer empty */
		status |= BD_ENET_RX_EMPTY;

		if (fep->bufdesc_ex) {
			struct bufdesc_ex *ebdp = (struct bufdesc_ex *)bdp;

			ebdp->cbd_esc = cpu_to_fec32(BD_ENET_RX_INT);
			ebdp->cbd_prot = 0;
			ebdp->cbd_bdu = 0;
		}
		/* Make sure the updates to rest of the descriptor are
		 * performed before transferring ownership.
		 */
		wmb();
		bdp->cbd_sc = cpu_to_fec16(status);

		/* Update BD pointer to next entry */
		bdp = fec_enet_get_nextdesc(bdp, &rxq->bd);

		/* Doing this here will keep the FEC running while we process
		 * incoming frames.  On a heavily loaded network, we should be
		 * able to keep up at the expense of system resources.
		 */
		writel(0, rxq->bd.reg_desc_active);
	}
	rxq->bd.cur = bdp;
	return pkt_received;
}

static int
fec_enet_rx(struct net_device *ndev, int budget)
{
	int     pkt_received = 0;
	u16	queue_id;
	struct fec_enet_private *fep = netdev_priv(ndev);

	for_each_set_bit(queue_id, &fep->work_rx, FEC_ENET_MAX_RX_QS) {
		int ret;

		ret = fec_enet_rx_queue(ndev,
					budget - pkt_received, queue_id);

		if (ret < budget - pkt_received)
			clear_bit(queue_id, &fep->work_rx);

		pkt_received += ret;
	}
	return pkt_received;
}

static bool
fec_enet_collect_events(struct fec_enet_private *fep, uint int_events)
{
	if (int_events == 0)
		return false;

	if (int_events & FEC_ENET_RXF_0)
		fep->work_rx |= (1 << 2);
	if (int_events & FEC_ENET_RXF_1)
		fep->work_rx |= (1 << 0);
	if (int_events & FEC_ENET_RXF_2)
		fep->work_rx |= (1 << 1);

	if (int_events & FEC_ENET_TXF_0)
		fep->work_tx |= (1 << 2);
	if (int_events & FEC_ENET_TXF_1)
		fep->work_tx |= (1 << 0);
	if (int_events & FEC_ENET_TXF_2)
		fep->work_tx |= (1 << 1);

	return true;
}

static irqreturn_t
fec_enet_interrupt(int irq, void *dev_id)
{
	struct net_device *ndev = dev_id;
	struct fec_enet_private *fep = netdev_priv(ndev);
	uint int_events;
	irqreturn_t ret = IRQ_NONE;

	int_events = readl(fep->hwp + FEC_IEVENT);
	writel(int_events, fep->hwp + FEC_IEVENT);
	fec_enet_collect_events(fep, int_events);

	if ((fep->work_tx || fep->work_rx) && fep->link) {
		ret = IRQ_HANDLED;

		if (napi_schedule_prep(&fep->napi)) {
			/* Disable the NAPI interrupts */
			writel(FEC_NAPI_IMASK, fep->hwp + FEC_IMASK);
			__napi_schedule(&fep->napi);
		}
	}

	if (int_events & FEC_ENET_MII) {
		ret = IRQ_HANDLED;
		complete(&fep->mdio_done);
	}
	return ret;
}

static int fec_enet_rx_napi(struct napi_struct *napi, int budget)
{
	struct net_device *ndev = napi->dev;
	struct fec_enet_private *fep = netdev_priv(ndev);
	int pkts;

	pkts = fec_enet_rx(ndev, budget);

	fec_enet_tx(ndev);

	if (pkts < budget) {
		napi_complete_done(napi, pkts);
		writel(FEC_DEFAULT_IMASK, fep->hwp + FEC_IMASK);
	}
	return pkts;
}

/* ------------------------------------------------------------------------- */
static void fec_get_mac(struct net_device *ndev)
{
	struct fec_enet_private *fep = netdev_priv(ndev);
	struct fec_platform_data *pdata = dev_get_platdata(&fep->pdev->dev);
	unsigned char *iap, tmpaddr[ETH_ALEN];

	/*
	 * try to get mac address in following order:
	 *
	 * 1) module parameter via kernel command line in form
	 *    fec.macaddr=0x00,0x04,0x9f,0x01,0x30,0xe0
	 */
	iap = macaddr;

	/*
	 * 2) from device tree data
	 */
	if (!is_valid_ether_addr(iap)) {
		struct device_node *np = fep->pdev->dev.of_node;
		if (np) {
			const char *mac = of_get_mac_address(np);
			if (!IS_ERR(mac))
				iap = (unsigned char *) mac;
		}
	}

	/*
	 * 3) from flash or fuse (via platform data)
	 */
	if (!is_valid_ether_addr(iap)) {
#ifdef CONFIG_M5272
		if (FEC_FLASHMAC)
			iap = (unsigned char *)FEC_FLASHMAC;
#else
		if (pdata)
			iap = (unsigned char *)&pdata->mac;
#endif
	}

	/*
	 * 4) FEC mac registers set by bootloader
	 */
	if (!is_valid_ether_addr(iap)) {
		*((__be32 *) &tmpaddr[0]) =
			cpu_to_be32(readl(fep->hwp + FEC_ADDR_LOW));
		*((__be16 *) &tmpaddr[4]) =
			cpu_to_be16(readl(fep->hwp + FEC_ADDR_HIGH) >> 16);
		iap = &tmpaddr[0];
	}

	/*
	 * 5) random mac address
	 */
	if (!is_valid_ether_addr(iap)) {
		/* Report it and use a random ethernet address instead */
		dev_err(&fep->pdev->dev, "Invalid MAC address: %pM\n", iap);
		eth_hw_addr_random(ndev);
		dev_info(&fep->pdev->dev, "Using random MAC address: %pM\n",
			 ndev->dev_addr);
		return;
	}

	memcpy(ndev->dev_addr, iap, ETH_ALEN);

	/* Adjust MAC if using macaddr */
	if (iap == macaddr)
		 ndev->dev_addr[ETH_ALEN-1] = macaddr[ETH_ALEN-1] + fep->dev_id;
}

/* ------------------------------------------------------------------------- */

/*
 * Phy section
 */
static void fec_enet_adjust_link(struct net_device *ndev)
{
	struct fec_enet_private *fep = netdev_priv(ndev);
	struct phy_device *phy_dev = ndev->phydev;
	int status_change = 0;

	/*
	 * If the netdev is down, or is going down, we're not interested
	 * in link state events, so just mark our idea of the link as down
	 * and ignore the event.
	 */
	if (!netif_running(ndev) || !netif_device_present(ndev)) {
		fep->link = 0;
	} else if (phy_dev->link) {
		if (!fep->link) {
			fep->link = phy_dev->link;
			status_change = 1;
		}

		if (fep->full_duplex != phy_dev->duplex) {
			fep->full_duplex = phy_dev->duplex;
			status_change = 1;
		}

		if (phy_dev->speed != fep->speed) {
			fep->speed = phy_dev->speed;
			status_change = 1;
		}

		/* if any of the above changed restart the FEC */
		if (status_change) {
			napi_disable(&fep->napi);
			netif_tx_lock_bh(ndev);
			fec_restart(ndev);
			netif_tx_wake_all_queues(ndev);
			netif_tx_unlock_bh(ndev);
			napi_enable(&fep->napi);
		}
#ifdef CONFIG_KSZ_SWITCH
		fep->port.ready = netif_running(ndev);
#endif
	} else {
		if (fep->link) {
			napi_disable(&fep->napi);
			netif_tx_lock_bh(ndev);
			fec_stop(ndev);
			netif_tx_unlock_bh(ndev);
			napi_enable(&fep->napi);
			fep->link = phy_dev->link;
			status_change = 1;
		}
	}

	if (status_change)
		phy_print_status(phy_dev);
}

static int fec_enet_mdio_read(struct mii_bus *bus, int mii_id, int regnum)
{
	struct fec_enet_private *fep = bus->priv;
	struct device *dev = &fep->pdev->dev;
	unsigned long time_left;
	int ret = 0, frame_start, frame_addr, frame_op;
	bool is_c45 = !!(regnum & MII_ADDR_C45);

	ret = pm_runtime_get_sync(dev);
	if (ret < 0)
		return ret;

	reinit_completion(&fep->mdio_done);

	if (is_c45) {
		frame_start = FEC_MMFR_ST_C45;

		/* write address */
		frame_addr = (regnum >> 16);
		writel(frame_start | FEC_MMFR_OP_ADDR_WRITE |
		       FEC_MMFR_PA(mii_id) | FEC_MMFR_RA(frame_addr) |
		       FEC_MMFR_TA | (regnum & 0xFFFF),
		       fep->hwp + FEC_MII_DATA);

		/* wait for end of transfer */
		time_left = wait_for_completion_timeout(&fep->mdio_done,
				usecs_to_jiffies(FEC_MII_TIMEOUT));
		if (time_left == 0) {
			netdev_err(fep->netdev, "MDIO address write timeout\n");
			ret = -ETIMEDOUT;
			goto out;
		}

		frame_op = FEC_MMFR_OP_READ_C45;

	} else {
		/* C22 read */
		frame_op = FEC_MMFR_OP_READ;
		frame_start = FEC_MMFR_ST;
		frame_addr = regnum;
	}

	/* start a read op */
	writel(frame_start | frame_op |
		FEC_MMFR_PA(mii_id) | FEC_MMFR_RA(frame_addr) |
		FEC_MMFR_TA, fep->hwp + FEC_MII_DATA);

	/* wait for end of transfer */
	time_left = wait_for_completion_timeout(&fep->mdio_done,
			usecs_to_jiffies(FEC_MII_TIMEOUT));
	if (time_left == 0) {
		netdev_err(fep->netdev, "MDIO read timeout\n");
		ret = -ETIMEDOUT;
		goto out;
	}

	ret = FEC_MMFR_DATA(readl(fep->hwp + FEC_MII_DATA));

out:
	pm_runtime_mark_last_busy(dev);
	pm_runtime_put_autosuspend(dev);

	return ret;
}

static int fec_enet_mdio_write(struct mii_bus *bus, int mii_id, int regnum,
			   u16 value)
{
	struct fec_enet_private *fep = bus->priv;
	struct device *dev = &fep->pdev->dev;
	unsigned long time_left;
	int ret, frame_start, frame_addr;
	bool is_c45 = !!(regnum & MII_ADDR_C45);

	ret = pm_runtime_get_sync(dev);
	if (ret < 0)
		return ret;
	else
		ret = 0;

	reinit_completion(&fep->mdio_done);

	if (is_c45) {
		frame_start = FEC_MMFR_ST_C45;

		/* write address */
		frame_addr = (regnum >> 16);
		writel(frame_start | FEC_MMFR_OP_ADDR_WRITE |
		       FEC_MMFR_PA(mii_id) | FEC_MMFR_RA(frame_addr) |
		       FEC_MMFR_TA | (regnum & 0xFFFF),
		       fep->hwp + FEC_MII_DATA);

		/* wait for end of transfer */
		time_left = wait_for_completion_timeout(&fep->mdio_done,
			usecs_to_jiffies(FEC_MII_TIMEOUT));
		if (time_left == 0) {
			netdev_err(fep->netdev, "MDIO address write timeout\n");
			ret = -ETIMEDOUT;
			goto out;
		}
	} else {
		/* C22 write */
		frame_start = FEC_MMFR_ST;
		frame_addr = regnum;
	}

	/* start a write op */
	writel(frame_start | FEC_MMFR_OP_WRITE |
		FEC_MMFR_PA(mii_id) | FEC_MMFR_RA(frame_addr) |
		FEC_MMFR_TA | FEC_MMFR_DATA(value),
		fep->hwp + FEC_MII_DATA);

	/* wait for end of transfer */
	time_left = wait_for_completion_timeout(&fep->mdio_done,
			usecs_to_jiffies(FEC_MII_TIMEOUT));
	if (time_left == 0) {
		netdev_err(fep->netdev, "MDIO write timeout\n");
		ret  = -ETIMEDOUT;
	}

out:
	pm_runtime_mark_last_busy(dev);
	pm_runtime_put_autosuspend(dev);

	return ret;
}

static void fec_enet_phy_reset_after_clk_enable(struct net_device *ndev)
{
	struct fec_enet_private *fep = netdev_priv(ndev);
	struct phy_device *phy_dev = ndev->phydev;

	if (phy_dev) {
		phy_reset_after_clk_enable(phy_dev);
	} else if (fep->phy_node) {
		/*
		 * If the PHY still is not bound to the MAC, but there is
		 * OF PHY node and a matching PHY device instance already,
		 * use the OF PHY node to obtain the PHY device instance,
		 * and then use that PHY device instance when triggering
		 * the PHY reset.
		 */
		phy_dev = of_phy_find_device(fep->phy_node);
		phy_reset_after_clk_enable(phy_dev);
		put_device(&phy_dev->mdio.dev);
	}
}

static int fec_enet_clk_enable(struct net_device *ndev, bool enable)
{
	struct fec_enet_private *fep = netdev_priv(ndev);
	int ret;

	if (enable) {
		ret = clk_prepare_enable(fep->clk_enet_out);
		if (ret)
			return ret;

		if (fep->clk_ptp) {
			mutex_lock(&fep->ptp_clk_mutex);
			ret = clk_prepare_enable(fep->clk_ptp);
			if (ret) {
				mutex_unlock(&fep->ptp_clk_mutex);
				goto failed_clk_ptp;
			} else {
				fep->ptp_clk_on = true;
			}
			mutex_unlock(&fep->ptp_clk_mutex);
		}

		ret = clk_prepare_enable(fep->clk_ref);
		if (ret)
			goto failed_clk_ref;

		fec_enet_phy_reset_after_clk_enable(ndev);
	} else {
		clk_disable_unprepare(fep->clk_enet_out);
		if (fep->clk_ptp) {
			mutex_lock(&fep->ptp_clk_mutex);
			clk_disable_unprepare(fep->clk_ptp);
			fep->ptp_clk_on = false;
			mutex_unlock(&fep->ptp_clk_mutex);
		}
		clk_disable_unprepare(fep->clk_ref);
	}

	return 0;

failed_clk_ref:
	if (fep->clk_ref)
		clk_disable_unprepare(fep->clk_ref);
failed_clk_ptp:
	if (fep->clk_enet_out)
		clk_disable_unprepare(fep->clk_enet_out);

	return ret;
}

static int fec_enet_mii_probe(struct net_device *ndev)
{
	struct fec_enet_private *fep = netdev_priv(ndev);
	struct phy_device *phy_dev = NULL;
	char mdio_bus_id[MII_BUS_ID_SIZE];
	char phy_name[MII_BUS_ID_SIZE + 3];
	int phy_id;
	int dev_id = fep->dev_id;

#ifdef CONFIG_KSZ_SWITCH
	struct ksz_sw *sw = fep->port.sw;

	if (sw_is_switch(sw)) {
		phy_dev = ndev->phydev;
	} else
#endif
	if (fep->phy_node) {
		phy_dev = of_phy_connect(ndev, fep->phy_node,
					 &fec_enet_adjust_link, 0,
					 fep->phy_interface);
		if (!phy_dev) {
			netdev_err(ndev, "Unable to connect to phy\n");
			return -ENODEV;
		}
	} else {
		/* check for attached phy */
		for (phy_id = 0; (phy_id < PHY_MAX_ADDR); phy_id++) {
			if (!mdiobus_is_registered_device(fep->mii_bus, phy_id))
				continue;
			if (dev_id--)
				continue;
			strlcpy(mdio_bus_id, fep->mii_bus->id, MII_BUS_ID_SIZE);
			break;
		}

		if (phy_id >= PHY_MAX_ADDR) {
			netdev_info(ndev, "no PHY, assuming direct connection to switch\n");
			strlcpy(mdio_bus_id, "fixed-0", MII_BUS_ID_SIZE);
			phy_id = 0;
		}

		snprintf(phy_name, sizeof(phy_name),
			 PHY_ID_FMT, mdio_bus_id, phy_id);
		phy_dev = phy_connect(ndev, phy_name, &fec_enet_adjust_link,
				      fep->phy_interface);
	}

	if (IS_ERR(phy_dev)) {
		netdev_err(ndev, "could not attach to PHY\n");
		return PTR_ERR(phy_dev);
	}

	/* mask with MAC supported features */
	if (fep->quirks & FEC_QUIRK_HAS_GBIT) {
		phy_set_max_speed(phy_dev, 1000);
		phy_remove_link_mode(phy_dev,
				     ETHTOOL_LINK_MODE_1000baseT_Half_BIT);
#if !defined(CONFIG_M5272)
		phy_support_sym_pause(phy_dev);
#endif
	}
	else
		phy_set_max_speed(phy_dev, 100);

	fep->link = 0;
	fep->full_duplex = 0;

	phy_attached_info(phy_dev);

	return 0;
}

static int fec_enet_mii_init(struct platform_device *pdev)
{
	static struct mii_bus *fec0_mii_bus;
	struct net_device *ndev = platform_get_drvdata(pdev);
	struct fec_enet_private *fep = netdev_priv(ndev);
	struct device_node *node;
	int err = -ENXIO;
	u32 mii_speed, holdtime;

	/*
	 * The i.MX28 dual fec interfaces are not equal.
	 * Here are the differences:
	 *
	 *  - fec0 supports MII & RMII modes while fec1 only supports RMII
	 *  - fec0 acts as the 1588 time master while fec1 is slave
	 *  - external phys can only be configured by fec0
	 *
	 * That is to say fec1 can not work independently. It only works
	 * when fec0 is working. The reason behind this design is that the
	 * second interface is added primarily for Switch mode.
	 *
	 * Because of the last point above, both phys are attached on fec0
	 * mdio interface in board design, and need to be configured by
	 * fec0 mii_bus.
	 */
	if ((fep->quirks & FEC_QUIRK_SINGLE_MDIO) && fep->dev_id > 0) {
		/* fec1 uses fec0 mii_bus */
		if (mii_cnt && fec0_mii_bus) {
			fep->mii_bus = fec0_mii_bus;
			mii_cnt++;
			return 0;
		}
		return -ENOENT;
	}

	/*
	 * Set MII speed to 2.5 MHz (= clk_get_rate() / 2 * phy_speed)
	 *
	 * The formula for FEC MDC is 'ref_freq / (MII_SPEED x 2)' while
	 * for ENET-MAC is 'ref_freq / ((MII_SPEED + 1) x 2)'.  The i.MX28
	 * Reference Manual has an error on this, and gets fixed on i.MX6Q
	 * document.
	 */
	mii_speed = DIV_ROUND_UP(clk_get_rate(fep->clk_ipg), 5000000);
	if (fep->quirks & FEC_QUIRK_ENET_MAC)
		mii_speed--;
	if (mii_speed > 63) {
		dev_err(&pdev->dev,
			"fec clock (%lu) too fast to get right mii speed\n",
			clk_get_rate(fep->clk_ipg));
		err = -EINVAL;
		goto err_out;
	}

	/*
	 * The i.MX28 and i.MX6 types have another filed in the MSCR (aka
	 * MII_SPEED) register that defines the MDIO output hold time. Earlier
	 * versions are RAZ there, so just ignore the difference and write the
	 * register always.
	 * The minimal hold time according to IEE802.3 (clause 22) is 10 ns.
	 * HOLDTIME + 1 is the number of clk cycles the fec is holding the
	 * output.
	 * The HOLDTIME bitfield takes values between 0 and 7 (inclusive).
	 * Given that ceil(clkrate / 5000000) <= 64, the calculation for
	 * holdtime cannot result in a value greater than 3.
	 */
	holdtime = DIV_ROUND_UP(clk_get_rate(fep->clk_ipg), 100000000) - 1;

	fep->phy_speed = mii_speed << 1 | holdtime << 8;

	writel(fep->phy_speed, fep->hwp + FEC_MII_SPEED);

	fep->mii_bus = mdiobus_alloc();
	if (fep->mii_bus == NULL) {
		err = -ENOMEM;
		goto err_out;
	}

	fep->mii_bus->name = "fec_enet_mii_bus";
	fep->mii_bus->read = fec_enet_mdio_read;
	fep->mii_bus->write = fec_enet_mdio_write;
	snprintf(fep->mii_bus->id, MII_BUS_ID_SIZE, "%s-%x",
		pdev->name, fep->dev_id + 1);
	fep->mii_bus->priv = fep;
	fep->mii_bus->parent = &pdev->dev;

	node = of_get_child_by_name(pdev->dev.of_node, "mdio");
	err = of_mdiobus_register(fep->mii_bus, node);
	of_node_put(node);
	if (err)
		goto err_out_free_mdiobus;

	mii_cnt++;

	/* save fec0 mii_bus */
	if (fep->quirks & FEC_QUIRK_SINGLE_MDIO)
		fec0_mii_bus = fep->mii_bus;

	return 0;

err_out_free_mdiobus:
	mdiobus_free(fep->mii_bus);
err_out:
	return err;
}

static void fec_enet_mii_remove(struct fec_enet_private *fep)
{
	if (--mii_cnt == 0) {
		mdiobus_unregister(fep->mii_bus);
		mdiobus_free(fep->mii_bus);
	}
}

static void fec_enet_get_drvinfo(struct net_device *ndev,
				 struct ethtool_drvinfo *info)
{
	struct fec_enet_private *fep = netdev_priv(ndev);

	strlcpy(info->driver, fep->pdev->dev.driver->name,
		sizeof(info->driver));
	strlcpy(info->version, "Revision: 1.0", sizeof(info->version));
	strlcpy(info->bus_info, dev_name(&ndev->dev), sizeof(info->bus_info));
}

static int fec_enet_get_regs_len(struct net_device *ndev)
{
	struct fec_enet_private *fep = netdev_priv(ndev);
	struct resource *r;
	int s = 0;

	r = platform_get_resource(fep->pdev, IORESOURCE_MEM, 0);
	if (r)
		s = resource_size(r);

	return s;
}

/* List of registers that can be safety be read to dump them with ethtool */
#if defined(CONFIG_M523x) || defined(CONFIG_M527x) || defined(CONFIG_M528x) || \
	defined(CONFIG_M520x) || defined(CONFIG_M532x) || defined(CONFIG_ARM) || \
	defined(CONFIG_ARM64) || defined(CONFIG_COMPILE_TEST)
static __u32 fec_enet_register_version = 2;
static u32 fec_enet_register_offset[] = {
	FEC_IEVENT, FEC_IMASK, FEC_R_DES_ACTIVE_0, FEC_X_DES_ACTIVE_0,
	FEC_ECNTRL, FEC_MII_DATA, FEC_MII_SPEED, FEC_MIB_CTRLSTAT, FEC_R_CNTRL,
	FEC_X_CNTRL, FEC_ADDR_LOW, FEC_ADDR_HIGH, FEC_OPD, FEC_TXIC0, FEC_TXIC1,
	FEC_TXIC2, FEC_RXIC0, FEC_RXIC1, FEC_RXIC2, FEC_HASH_TABLE_HIGH,
	FEC_HASH_TABLE_LOW, FEC_GRP_HASH_TABLE_HIGH, FEC_GRP_HASH_TABLE_LOW,
	FEC_X_WMRK, FEC_R_BOUND, FEC_R_FSTART, FEC_R_DES_START_1,
	FEC_X_DES_START_1, FEC_R_BUFF_SIZE_1, FEC_R_DES_START_2,
	FEC_X_DES_START_2, FEC_R_BUFF_SIZE_2, FEC_R_DES_START_0,
	FEC_X_DES_START_0, FEC_R_BUFF_SIZE_0, FEC_R_FIFO_RSFL, FEC_R_FIFO_RSEM,
	FEC_R_FIFO_RAEM, FEC_R_FIFO_RAFL, FEC_RACC, FEC_RCMR_1, FEC_RCMR_2,
	FEC_DMA_CFG_1, FEC_DMA_CFG_2, FEC_R_DES_ACTIVE_1, FEC_X_DES_ACTIVE_1,
	FEC_R_DES_ACTIVE_2, FEC_X_DES_ACTIVE_2, FEC_QOS_SCHEME,
	RMON_T_DROP, RMON_T_PACKETS, RMON_T_BC_PKT, RMON_T_MC_PKT,
	RMON_T_CRC_ALIGN, RMON_T_UNDERSIZE, RMON_T_OVERSIZE, RMON_T_FRAG,
	RMON_T_JAB, RMON_T_COL, RMON_T_P64, RMON_T_P65TO127, RMON_T_P128TO255,
	RMON_T_P256TO511, RMON_T_P512TO1023, RMON_T_P1024TO2047,
	RMON_T_P_GTE2048, RMON_T_OCTETS,
	IEEE_T_DROP, IEEE_T_FRAME_OK, IEEE_T_1COL, IEEE_T_MCOL, IEEE_T_DEF,
	IEEE_T_LCOL, IEEE_T_EXCOL, IEEE_T_MACERR, IEEE_T_CSERR, IEEE_T_SQE,
	IEEE_T_FDXFC, IEEE_T_OCTETS_OK,
	RMON_R_PACKETS, RMON_R_BC_PKT, RMON_R_MC_PKT, RMON_R_CRC_ALIGN,
	RMON_R_UNDERSIZE, RMON_R_OVERSIZE, RMON_R_FRAG, RMON_R_JAB,
	RMON_R_RESVD_O, RMON_R_P64, RMON_R_P65TO127, RMON_R_P128TO255,
	RMON_R_P256TO511, RMON_R_P512TO1023, RMON_R_P1024TO2047,
	RMON_R_P_GTE2048, RMON_R_OCTETS,
	IEEE_R_DROP, IEEE_R_FRAME_OK, IEEE_R_CRC, IEEE_R_ALIGN, IEEE_R_MACERR,
	IEEE_R_FDXFC, IEEE_R_OCTETS_OK
};
#else
static __u32 fec_enet_register_version = 1;
static u32 fec_enet_register_offset[] = {
	FEC_ECNTRL, FEC_IEVENT, FEC_IMASK, FEC_IVEC, FEC_R_DES_ACTIVE_0,
	FEC_R_DES_ACTIVE_1, FEC_R_DES_ACTIVE_2, FEC_X_DES_ACTIVE_0,
	FEC_X_DES_ACTIVE_1, FEC_X_DES_ACTIVE_2, FEC_MII_DATA, FEC_MII_SPEED,
	FEC_R_BOUND, FEC_R_FSTART, FEC_X_WMRK, FEC_X_FSTART, FEC_R_CNTRL,
	FEC_MAX_FRM_LEN, FEC_X_CNTRL, FEC_ADDR_LOW, FEC_ADDR_HIGH,
	FEC_GRP_HASH_TABLE_HIGH, FEC_GRP_HASH_TABLE_LOW, FEC_R_DES_START_0,
	FEC_R_DES_START_1, FEC_R_DES_START_2, FEC_X_DES_START_0,
	FEC_X_DES_START_1, FEC_X_DES_START_2, FEC_R_BUFF_SIZE_0,
	FEC_R_BUFF_SIZE_1, FEC_R_BUFF_SIZE_2
};
#endif

static void fec_enet_get_regs(struct net_device *ndev,
			      struct ethtool_regs *regs, void *regbuf)
{
	struct fec_enet_private *fep = netdev_priv(ndev);
	u32 __iomem *theregs = (u32 __iomem *)fep->hwp;
	struct device *dev = &fep->pdev->dev;
	u32 *buf = (u32 *)regbuf;
	u32 i, off;
	int ret;

	ret = pm_runtime_get_sync(dev);
	if (ret < 0)
		return;

#ifdef CONFIG_KSZ_SWITCH
	if (fep != fep->hw_priv)
		fep = fep->hw_priv;
#endif
	regs->version = fec_enet_register_version;

	memset(buf, 0, regs->len);

	for (i = 0; i < ARRAY_SIZE(fec_enet_register_offset); i++) {
		off = fec_enet_register_offset[i];

		if ((off == FEC_R_BOUND || off == FEC_R_FSTART) &&
		    !(fep->quirks & FEC_QUIRK_HAS_FRREG))
			continue;

		off >>= 2;
		buf[off] = readl(&theregs[off]);
	}

	pm_runtime_mark_last_busy(dev);
	pm_runtime_put_autosuspend(dev);
}

static int fec_enet_get_ts_info(struct net_device *ndev,
				struct ethtool_ts_info *info)
{
	struct fec_enet_private *fep = netdev_priv(ndev);

#ifdef CONFIG_1588_PTP
	struct ksz_sw *sw = fep->port.sw;

	if (sw_is_switch(sw) && (sw->features & PTP_HW)) {
		struct ptp_info *ptp = &sw->ptp_hw;

		return ptp->ops->get_ts_info(ptp, ndev, info);
	}
#endif
	if (fep->bufdesc_ex) {

		info->so_timestamping = SOF_TIMESTAMPING_TX_SOFTWARE |
					SOF_TIMESTAMPING_RX_SOFTWARE |
					SOF_TIMESTAMPING_SOFTWARE |
					SOF_TIMESTAMPING_TX_HARDWARE |
					SOF_TIMESTAMPING_RX_HARDWARE |
					SOF_TIMESTAMPING_RAW_HARDWARE;
		if (fep->ptp_clock)
			info->phc_index = ptp_clock_index(fep->ptp_clock);
		else
			info->phc_index = -1;

		info->tx_types = (1 << HWTSTAMP_TX_OFF) |
				 (1 << HWTSTAMP_TX_ON);

		info->rx_filters = (1 << HWTSTAMP_FILTER_NONE) |
				   (1 << HWTSTAMP_FILTER_ALL);
		return 0;
	} else {
		return ethtool_op_get_ts_info(ndev, info);
	}
}

#if !defined(CONFIG_M5272)

static void fec_enet_get_pauseparam(struct net_device *ndev,
				    struct ethtool_pauseparam *pause)
{
	struct fec_enet_private *fep = netdev_priv(ndev);

#ifdef CONFIG_KSZ_SWITCH
	if (fep != fep->hw_priv)
		fep = fep->hw_priv;
#endif
	pause->autoneg = (fep->pause_flag & FEC_PAUSE_FLAG_AUTONEG) != 0;
	pause->tx_pause = (fep->pause_flag & FEC_PAUSE_FLAG_ENABLE) != 0;
	pause->rx_pause = pause->tx_pause;
}

static int fec_enet_set_pauseparam(struct net_device *ndev,
				   struct ethtool_pauseparam *pause)
{
	struct fec_enet_private *fep = netdev_priv(ndev);

#ifdef CONFIG_KSZ_SWITCH
	if (fep != fep->hw_priv)
		fep = fep->hw_priv;
#endif
	if (!ndev->phydev)
		return -ENODEV;

	if (pause->tx_pause != pause->rx_pause) {
		netdev_info(ndev,
			"hardware only support enable/disable both tx and rx");
		return -EINVAL;
	}

	fep->pause_flag = 0;

	/* tx pause must be same as rx pause */
	fep->pause_flag |= pause->rx_pause ? FEC_PAUSE_FLAG_ENABLE : 0;
	fep->pause_flag |= pause->autoneg ? FEC_PAUSE_FLAG_AUTONEG : 0;

	phy_set_sym_pause(ndev->phydev, pause->rx_pause, pause->tx_pause,
			  pause->autoneg);

	if (pause->autoneg) {
		if (netif_running(ndev))
			fec_stop(ndev);
		phy_start_aneg(ndev->phydev);
	}
	if (netif_running(ndev)) {
		napi_disable(&fep->napi);
		netif_tx_lock_bh(ndev);
		fec_restart(ndev);
		netif_tx_wake_all_queues(ndev);
		netif_tx_unlock_bh(ndev);
		napi_enable(&fep->napi);
	}

	return 0;
}

static const struct fec_stat {
	char name[ETH_GSTRING_LEN];
	u16 offset;
} fec_stats[] = {
	/* RMON TX */
	{ "tx_dropped", RMON_T_DROP },
	{ "tx_packets", RMON_T_PACKETS },
	{ "tx_broadcast", RMON_T_BC_PKT },
	{ "tx_multicast", RMON_T_MC_PKT },
	{ "tx_crc_errors", RMON_T_CRC_ALIGN },
	{ "tx_undersize", RMON_T_UNDERSIZE },
	{ "tx_oversize", RMON_T_OVERSIZE },
	{ "tx_fragment", RMON_T_FRAG },
	{ "tx_jabber", RMON_T_JAB },
	{ "tx_collision", RMON_T_COL },
	{ "tx_64byte", RMON_T_P64 },
	{ "tx_65to127byte", RMON_T_P65TO127 },
	{ "tx_128to255byte", RMON_T_P128TO255 },
	{ "tx_256to511byte", RMON_T_P256TO511 },
	{ "tx_512to1023byte", RMON_T_P512TO1023 },
	{ "tx_1024to2047byte", RMON_T_P1024TO2047 },
	{ "tx_GTE2048byte", RMON_T_P_GTE2048 },
	{ "tx_octets", RMON_T_OCTETS },

	/* IEEE TX */
	{ "IEEE_tx_drop", IEEE_T_DROP },
	{ "IEEE_tx_frame_ok", IEEE_T_FRAME_OK },
	{ "IEEE_tx_1col", IEEE_T_1COL },
	{ "IEEE_tx_mcol", IEEE_T_MCOL },
	{ "IEEE_tx_def", IEEE_T_DEF },
	{ "IEEE_tx_lcol", IEEE_T_LCOL },
	{ "IEEE_tx_excol", IEEE_T_EXCOL },
	{ "IEEE_tx_macerr", IEEE_T_MACERR },
	{ "IEEE_tx_cserr", IEEE_T_CSERR },
	{ "IEEE_tx_sqe", IEEE_T_SQE },
	{ "IEEE_tx_fdxfc", IEEE_T_FDXFC },
	{ "IEEE_tx_octets_ok", IEEE_T_OCTETS_OK },

	/* RMON RX */
	{ "rx_packets", RMON_R_PACKETS },
	{ "rx_broadcast", RMON_R_BC_PKT },
	{ "rx_multicast", RMON_R_MC_PKT },
	{ "rx_crc_errors", RMON_R_CRC_ALIGN },
	{ "rx_undersize", RMON_R_UNDERSIZE },
	{ "rx_oversize", RMON_R_OVERSIZE },
	{ "rx_fragment", RMON_R_FRAG },
	{ "rx_jabber", RMON_R_JAB },
	{ "rx_64byte", RMON_R_P64 },
	{ "rx_65to127byte", RMON_R_P65TO127 },
	{ "rx_128to255byte", RMON_R_P128TO255 },
	{ "rx_256to511byte", RMON_R_P256TO511 },
	{ "rx_512to1023byte", RMON_R_P512TO1023 },
	{ "rx_1024to2047byte", RMON_R_P1024TO2047 },
	{ "rx_GTE2048byte", RMON_R_P_GTE2048 },
	{ "rx_octets", RMON_R_OCTETS },

	/* IEEE RX */
	{ "IEEE_rx_drop", IEEE_R_DROP },
	{ "IEEE_rx_frame_ok", IEEE_R_FRAME_OK },
	{ "IEEE_rx_crc", IEEE_R_CRC },
	{ "IEEE_rx_align", IEEE_R_ALIGN },
	{ "IEEE_rx_macerr", IEEE_R_MACERR },
	{ "IEEE_rx_fdxfc", IEEE_R_FDXFC },
	{ "IEEE_rx_octets_ok", IEEE_R_OCTETS_OK },
};

#define FEC_STATS_SIZE		(ARRAY_SIZE(fec_stats) * sizeof(u64))

static void fec_enet_update_ethtool_stats(struct net_device *dev)
{
	struct fec_enet_private *fep = netdev_priv(dev);
	int i;

#ifdef CONFIG_KSZ_SWITCH
	if (fep != fep->hw_priv)
		fep = fep->hw_priv;
#endif
	for (i = 0; i < ARRAY_SIZE(fec_stats); i++)
		fep->ethtool_stats[i] = readl(fep->hwp + fec_stats[i].offset);
}

static void fec_enet_get_ethtool_stats(struct net_device *dev,
				       struct ethtool_stats *stats, u64 *data)
{
	struct fec_enet_private *fep = netdev_priv(dev);

#ifdef CONFIG_KSZ_SWITCH
	if (fep != fep->hw_priv) {
		fep = fep->hw_priv;

		/* If current device is not running switch to the main device
		 * just to invoke fec_enet_update_ethtool_stats.
		 */
		if (!netif_running(dev))
			dev = fep->netdev;
	}
#endif
	if (netif_running(dev))
		fec_enet_update_ethtool_stats(dev);

	memcpy(data, fep->ethtool_stats, FEC_STATS_SIZE);
}

static void fec_enet_get_strings(struct net_device *netdev,
	u32 stringset, u8 *data)
{
	int i;
	switch (stringset) {
	case ETH_SS_STATS:
		for (i = 0; i < ARRAY_SIZE(fec_stats); i++)
			memcpy(data + i * ETH_GSTRING_LEN,
				fec_stats[i].name, ETH_GSTRING_LEN);
		break;
	}
}

static int fec_enet_get_sset_count(struct net_device *dev, int sset)
{
	switch (sset) {
	case ETH_SS_STATS:
		return ARRAY_SIZE(fec_stats);
	default:
		return -EOPNOTSUPP;
	}
}

static void fec_enet_clear_ethtool_stats(struct net_device *dev)
{
	struct fec_enet_private *fep = netdev_priv(dev);
	int i;

#ifdef CONFIG_KSZ_SWITCH
	if (fep != fep->hw_priv)
		fep = fep->hw_priv;
#endif
	/* Disable MIB statistics counters */
	writel(FEC_MIB_CTRLSTAT_DISABLE, fep->hwp + FEC_MIB_CTRLSTAT);

	for (i = 0; i < ARRAY_SIZE(fec_stats); i++)
		writel(0, fep->hwp + fec_stats[i].offset);

	/* Don't disable MIB statistics counters */
	writel(0, fep->hwp + FEC_MIB_CTRLSTAT);
}

#else	/* !defined(CONFIG_M5272) */
#define FEC_STATS_SIZE	0
static inline void fec_enet_update_ethtool_stats(struct net_device *dev)
{
}

static inline void fec_enet_clear_ethtool_stats(struct net_device *dev)
{
}
#endif /* !defined(CONFIG_M5272) */

/* ITR clock source is enet system clock (clk_ahb).
 * TCTT unit is cycle_ns * 64 cycle
 * So, the ICTT value = X us / (cycle_ns * 64)
 */
static int fec_enet_us_to_itr_clock(struct net_device *ndev, int us)
{
	struct fec_enet_private *fep = netdev_priv(ndev);

	return us * (fep->itr_clk_rate / 64000) / 1000;
}

/* Set threshold for interrupt coalescing */
static void fec_enet_itr_coal_set(struct net_device *ndev)
{
	struct fec_enet_private *fep = netdev_priv(ndev);
	int rx_itr, tx_itr;

	/* Must be greater than zero to avoid unpredictable behavior */
	if (!fep->rx_time_itr || !fep->rx_pkts_itr ||
	    !fep->tx_time_itr || !fep->tx_pkts_itr)
		return;

	/* Select enet system clock as Interrupt Coalescing
	 * timer Clock Source
	 */
	rx_itr = FEC_ITR_CLK_SEL;
	tx_itr = FEC_ITR_CLK_SEL;

	/* set ICFT and ICTT */
	rx_itr |= FEC_ITR_ICFT(fep->rx_pkts_itr);
	rx_itr |= FEC_ITR_ICTT(fec_enet_us_to_itr_clock(ndev, fep->rx_time_itr));
	tx_itr |= FEC_ITR_ICFT(fep->tx_pkts_itr);
	tx_itr |= FEC_ITR_ICTT(fec_enet_us_to_itr_clock(ndev, fep->tx_time_itr));

	rx_itr |= FEC_ITR_EN;
	tx_itr |= FEC_ITR_EN;

	writel(tx_itr, fep->hwp + FEC_TXIC0);
	writel(rx_itr, fep->hwp + FEC_RXIC0);
	if (fep->quirks & FEC_QUIRK_HAS_AVB) {
		writel(tx_itr, fep->hwp + FEC_TXIC1);
		writel(rx_itr, fep->hwp + FEC_RXIC1);
		writel(tx_itr, fep->hwp + FEC_TXIC2);
		writel(rx_itr, fep->hwp + FEC_RXIC2);
	}
}

static int
fec_enet_get_coalesce(struct net_device *ndev, struct ethtool_coalesce *ec)
{
	struct fec_enet_private *fep = netdev_priv(ndev);

#ifdef CONFIG_KSZ_SWITCH
	if (fep != fep->hw_priv)
		fep = fep->hw_priv;
#endif
	if (!(fep->quirks & FEC_QUIRK_HAS_COALESCE))
		return -EOPNOTSUPP;

	ec->rx_coalesce_usecs = fep->rx_time_itr;
	ec->rx_max_coalesced_frames = fep->rx_pkts_itr;

	ec->tx_coalesce_usecs = fep->tx_time_itr;
	ec->tx_max_coalesced_frames = fep->tx_pkts_itr;

	return 0;
}

static int
fec_enet_set_coalesce(struct net_device *ndev, struct ethtool_coalesce *ec)
{
	struct fec_enet_private *fep = netdev_priv(ndev);
	struct device *dev = &fep->pdev->dev;
	unsigned int cycle;

#ifdef CONFIG_KSZ_SWITCH
	if (fep != fep->hw_priv)
		fep = fep->hw_priv;
#endif
	if (!(fep->quirks & FEC_QUIRK_HAS_COALESCE))
		return -EOPNOTSUPP;

	if (ec->rx_max_coalesced_frames > 255) {
		dev_err(dev, "Rx coalesced frames exceed hardware limitation\n");
		return -EINVAL;
	}

	if (ec->tx_max_coalesced_frames > 255) {
		dev_err(dev, "Tx coalesced frame exceed hardware limitation\n");
		return -EINVAL;
	}

	cycle = fec_enet_us_to_itr_clock(ndev, ec->rx_coalesce_usecs);
	if (cycle > 0xFFFF) {
		dev_err(dev, "Rx coalesced usec exceed hardware limitation\n");
		return -EINVAL;
	}

	cycle = fec_enet_us_to_itr_clock(ndev, ec->tx_coalesce_usecs);
	if (cycle > 0xFFFF) {
		dev_err(dev, "Tx coalesced usec exceed hardware limitation\n");
		return -EINVAL;
	}

	fep->rx_time_itr = ec->rx_coalesce_usecs;
	fep->rx_pkts_itr = ec->rx_max_coalesced_frames;

	fep->tx_time_itr = ec->tx_coalesce_usecs;
	fep->tx_pkts_itr = ec->tx_max_coalesced_frames;

	fec_enet_itr_coal_set(ndev);

	return 0;
}

static void fec_enet_itr_coal_init(struct net_device *ndev)
{
	struct ethtool_coalesce ec;

	ec.rx_coalesce_usecs = FEC_ITR_ICTT_DEFAULT;
	ec.rx_max_coalesced_frames = FEC_ITR_ICFT_DEFAULT;

	ec.tx_coalesce_usecs = FEC_ITR_ICTT_DEFAULT;
	ec.tx_max_coalesced_frames = FEC_ITR_ICFT_DEFAULT;

	fec_enet_set_coalesce(ndev, &ec);
}

static int fec_enet_get_tunable(struct net_device *netdev,
				const struct ethtool_tunable *tuna,
				void *data)
{
	struct fec_enet_private *fep = netdev_priv(netdev);
	int ret = 0;

#ifdef CONFIG_KSZ_SWITCH
	if (fep != fep->hw_priv)
		fep = fep->hw_priv;
#endif
	switch (tuna->id) {
	case ETHTOOL_RX_COPYBREAK:
		*(u32 *)data = fep->rx_copybreak;
		break;
	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}

static int fec_enet_set_tunable(struct net_device *netdev,
				const struct ethtool_tunable *tuna,
				const void *data)
{
	struct fec_enet_private *fep = netdev_priv(netdev);
	int ret = 0;

#ifdef CONFIG_KSZ_SWITCH
	if (fep != fep->hw_priv)
		fep = fep->hw_priv;
#endif
	switch (tuna->id) {
	case ETHTOOL_RX_COPYBREAK:
		fep->rx_copybreak = *(u32 *)data;
		break;
	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}

static void
fec_enet_get_wol(struct net_device *ndev, struct ethtool_wolinfo *wol)
{
	struct fec_enet_private *fep = netdev_priv(ndev);

#ifdef CONFIG_KSZ_SWITCH
	if (fep != fep->hw_priv)
		fep = fep->hw_priv;
#endif
	if (fep->wol_flag & FEC_WOL_HAS_MAGIC_PACKET) {
		wol->supported = WAKE_MAGIC;
		wol->wolopts = fep->wol_flag & FEC_WOL_FLAG_ENABLE ? WAKE_MAGIC : 0;
	} else {
		wol->supported = wol->wolopts = 0;
	}
}

static int
fec_enet_set_wol(struct net_device *ndev, struct ethtool_wolinfo *wol)
{
	struct fec_enet_private *fep = netdev_priv(ndev);

#ifdef CONFIG_KSZ_SWITCH
	if (fep != fep->hw_priv)
		fep = fep->hw_priv;
#endif
	if (!(fep->wol_flag & FEC_WOL_HAS_MAGIC_PACKET))
		return -EINVAL;

	if (wol->wolopts & ~WAKE_MAGIC)
		return -EINVAL;

	device_set_wakeup_enable(&ndev->dev, wol->wolopts & WAKE_MAGIC);
	if (device_may_wakeup(&ndev->dev)) {
		fep->wol_flag |= FEC_WOL_FLAG_ENABLE;
		if (fep->irq[0] > 0)
			enable_irq_wake(fep->irq[0]);
	} else {
		fep->wol_flag &= (~FEC_WOL_FLAG_ENABLE);
		if (fep->irq[0] > 0)
			disable_irq_wake(fep->irq[0]);
	}

	return 0;
}

static const struct ethtool_ops fec_enet_ethtool_ops = {
	.get_drvinfo		= fec_enet_get_drvinfo,
	.get_regs_len		= fec_enet_get_regs_len,
	.get_regs		= fec_enet_get_regs,
	.nway_reset		= phy_ethtool_nway_reset,
	.get_link		= ethtool_op_get_link,
	.get_coalesce		= fec_enet_get_coalesce,
	.set_coalesce		= fec_enet_set_coalesce,
#ifndef CONFIG_M5272
	.get_pauseparam		= fec_enet_get_pauseparam,
	.set_pauseparam		= fec_enet_set_pauseparam,
	.get_strings		= fec_enet_get_strings,
	.get_ethtool_stats	= fec_enet_get_ethtool_stats,
	.get_sset_count		= fec_enet_get_sset_count,
#endif
	.get_ts_info		= fec_enet_get_ts_info,
	.get_tunable		= fec_enet_get_tunable,
	.set_tunable		= fec_enet_set_tunable,
	.get_wol		= fec_enet_get_wol,
	.set_wol		= fec_enet_set_wol,
	.get_link_ksettings	= phy_ethtool_get_link_ksettings,
	.set_link_ksettings	= phy_ethtool_set_link_ksettings,
};

#ifdef CONFIG_KSZ_SWITCH
#define SIOCDEVDEBUG			(SIOCDEVPRIVATE + 10)
#endif

static int fec_enet_ioctl(struct net_device *ndev, struct ifreq *rq, int cmd)
{
	struct fec_enet_private *fep = netdev_priv(ndev);
	struct phy_device *phydev = ndev->phydev;

#ifdef CONFIG_KSZ_SWITCH
	int result;
	struct ksz_sw *sw = fep->port.sw;
#ifdef CONFIG_1588_PTP
	struct ptp_info *ptp;
#endif

	result = -EOPNOTSUPP;
	switch (cmd) {
#ifdef CONFIG_1588_PTP
	case SIOCSHWTSTAMP:
		if (sw_is_switch(sw) && (sw->features & PTP_HW)) {
			int i;
			int p;
			u16 ports;

			ports = 0;
			for (i = 0, p = fep->port.first_port;
			     i < fep->port.port_cnt; i++, p++)
				ports |= (1 << p);
			ptp = &sw->ptp_hw;
			result = ptp->ops->hwtstamp_ioctl(ptp, rq, ports);
		}
		break;
	case SIOCDEVPRIVATE + 15:
		if (sw_is_switch(sw) && (sw->features & PTP_HW)) {
			ptp = &sw->ptp_hw;
			result = ptp->ops->dev_req(ptp, rq->ifr_data, NULL);
		}
		break;
#endif
#ifdef CONFIG_KSZ_MRP
	case SIOCDEVPRIVATE + 14:
		if (sw_is_switch(sw) && (sw->features & MRP_SUPPORT)) {
			struct mrp_info *mrp = &sw->mrp;

			result = mrp->ops->dev_req(mrp, rq->ifr_data);
		}
		break;
#endif
	case SIOCDEVPRIVATE + 13:
		if (sw_is_switch(sw)) {
			result = sw->ops->dev_req(sw, rq->ifr_data, NULL);
		}
		break;
	default:
		result = -EOPNOTSUPP;
	}
	if (result != -EOPNOTSUPP)
		return result;
#endif

	if (!netif_running(ndev))
		return -EINVAL;

	if (!phydev)
		return -ENODEV;

	if (fep->bufdesc_ex) {
		if (cmd == SIOCSHWTSTAMP)
			return fec_ptp_set(ndev, rq);
		if (cmd == SIOCGHWTSTAMP)
			return fec_ptp_get(ndev, rq);
	}

	return phy_mii_ioctl(phydev, rq, cmd);
}

static void fec_enet_free_buffers(struct net_device *ndev)
{
	struct fec_enet_private *fep = netdev_priv(ndev);
	unsigned int i;
	struct sk_buff *skb;
	struct bufdesc	*bdp;
	struct fec_enet_priv_tx_q *txq;
	struct fec_enet_priv_rx_q *rxq;
	unsigned int q;

	for (q = 0; q < fep->num_rx_queues; q++) {
		rxq = fep->rx_queue[q];
		bdp = rxq->bd.base;
		for (i = 0; i < rxq->bd.ring_size; i++) {
			skb = rxq->rx_skbuff[i];
			rxq->rx_skbuff[i] = NULL;
			if (skb) {
				dma_unmap_single(&fep->pdev->dev,
						 fec32_to_cpu(bdp->cbd_bufaddr),
						 FEC_ENET_RX_FRSIZE - fep->rx_align,
						 DMA_FROM_DEVICE);
				dev_kfree_skb(skb);
			}
			bdp = fec_enet_get_nextdesc(bdp, &rxq->bd);
		}
	}

	for (q = 0; q < fep->num_tx_queues; q++) {
		txq = fep->tx_queue[q];
		bdp = txq->bd.base;
		for (i = 0; i < txq->bd.ring_size; i++) {
			kfree(txq->tx_bounce[i]);
			txq->tx_bounce[i] = NULL;
			skb = txq->tx_skbuff[i];
			txq->tx_skbuff[i] = NULL;
			dev_kfree_skb(skb);
		}
	}
}

static void fec_enet_free_queue(struct net_device *ndev)
{
	struct fec_enet_private *fep = netdev_priv(ndev);
	int i;
	struct fec_enet_priv_tx_q *txq;

	for (i = 0; i < fep->num_tx_queues; i++)
		if (fep->tx_queue[i] && fep->tx_queue[i]->tso_hdrs) {
			txq = fep->tx_queue[i];
			dma_free_coherent(&fep->pdev->dev,
					  txq->bd.ring_size * TSO_HEADER_SIZE,
					  txq->tso_hdrs,
					  txq->tso_hdrs_dma);
		}

	for (i = 0; i < fep->num_rx_queues; i++)
		kfree(fep->rx_queue[i]);
	for (i = 0; i < fep->num_tx_queues; i++)
		kfree(fep->tx_queue[i]);
}

static int fec_enet_alloc_queue(struct net_device *ndev)
{
	struct fec_enet_private *fep = netdev_priv(ndev);
	int i;
	int ret = 0;
	struct fec_enet_priv_tx_q *txq;

	for (i = 0; i < fep->num_tx_queues; i++) {
		txq = kzalloc(sizeof(*txq), GFP_KERNEL);
		if (!txq) {
			ret = -ENOMEM;
			goto alloc_failed;
		}

		fep->tx_queue[i] = txq;
		txq->bd.ring_size = TX_RING_SIZE;
		fep->total_tx_ring_size += fep->tx_queue[i]->bd.ring_size;

		txq->tx_stop_threshold = FEC_MAX_SKB_DESCS;
		txq->tx_wake_threshold =
			(txq->bd.ring_size - txq->tx_stop_threshold) / 2;

		txq->tso_hdrs = dma_alloc_coherent(&fep->pdev->dev,
					txq->bd.ring_size * TSO_HEADER_SIZE,
					&txq->tso_hdrs_dma,
					GFP_KERNEL);
		if (!txq->tso_hdrs) {
			ret = -ENOMEM;
			goto alloc_failed;
		}
	}

	for (i = 0; i < fep->num_rx_queues; i++) {
		fep->rx_queue[i] = kzalloc(sizeof(*fep->rx_queue[i]),
					   GFP_KERNEL);
		if (!fep->rx_queue[i]) {
			ret = -ENOMEM;
			goto alloc_failed;
		}

		fep->rx_queue[i]->bd.ring_size = RX_RING_SIZE;
		fep->total_rx_ring_size += fep->rx_queue[i]->bd.ring_size;
	}
	return ret;

alloc_failed:
	fec_enet_free_queue(ndev);
	return ret;
}

static int
fec_enet_alloc_rxq_buffers(struct net_device *ndev, unsigned int queue)
{
	struct fec_enet_private *fep = netdev_priv(ndev);
	unsigned int i;
	struct sk_buff *skb;
	struct bufdesc	*bdp;
	struct fec_enet_priv_rx_q *rxq;

	rxq = fep->rx_queue[queue];
	bdp = rxq->bd.base;
	for (i = 0; i < rxq->bd.ring_size; i++) {
		skb = netdev_alloc_skb(ndev, FEC_ENET_RX_FRSIZE);
		if (!skb)
			goto err_alloc;

		if (fec_enet_new_rxbdp(ndev, bdp, skb)) {
			dev_kfree_skb(skb);
			goto err_alloc;
		}

		rxq->rx_skbuff[i] = skb;
		bdp->cbd_sc = cpu_to_fec16(BD_ENET_RX_EMPTY);

		if (fep->bufdesc_ex) {
			struct bufdesc_ex *ebdp = (struct bufdesc_ex *)bdp;
			ebdp->cbd_esc = cpu_to_fec32(BD_ENET_RX_INT);
		}

		bdp = fec_enet_get_nextdesc(bdp, &rxq->bd);
	}

	/* Set the last buffer to wrap. */
	bdp = fec_enet_get_prevdesc(bdp, &rxq->bd);
	bdp->cbd_sc |= cpu_to_fec16(BD_SC_WRAP);
	return 0;

 err_alloc:
	fec_enet_free_buffers(ndev);
	return -ENOMEM;
}

static int
fec_enet_alloc_txq_buffers(struct net_device *ndev, unsigned int queue)
{
	struct fec_enet_private *fep = netdev_priv(ndev);
	unsigned int i;
	struct bufdesc  *bdp;
	struct fec_enet_priv_tx_q *txq;

	txq = fep->tx_queue[queue];
	bdp = txq->bd.base;
	for (i = 0; i < txq->bd.ring_size; i++) {
		txq->tx_bounce[i] = kmalloc(FEC_ENET_TX_FRSIZE, GFP_KERNEL);
		if (!txq->tx_bounce[i])
			goto err_alloc;

		bdp->cbd_sc = cpu_to_fec16(0);
		bdp->cbd_bufaddr = cpu_to_fec32(0);

#ifndef CONFIG_1588_PTP
		if (fep->bufdesc_ex) {
			struct bufdesc_ex *ebdp = (struct bufdesc_ex *)bdp;
			ebdp->cbd_esc = cpu_to_fec32(BD_ENET_TX_INT);
		}
#endif

		bdp = fec_enet_get_nextdesc(bdp, &txq->bd);
	}

	/* Set the last buffer to wrap. */
	bdp = fec_enet_get_prevdesc(bdp, &txq->bd);
	bdp->cbd_sc |= cpu_to_fec16(BD_SC_WRAP);

	return 0;

 err_alloc:
	fec_enet_free_buffers(ndev);
	return -ENOMEM;
}

static int fec_enet_alloc_buffers(struct net_device *ndev)
{
	struct fec_enet_private *fep = netdev_priv(ndev);
	unsigned int i;

	for (i = 0; i < fep->num_rx_queues; i++)
		if (fec_enet_alloc_rxq_buffers(ndev, i))
			return -ENOMEM;

	for (i = 0; i < fep->num_tx_queues; i++)
		if (fec_enet_alloc_txq_buffers(ndev, i))
			return -ENOMEM;
	return 0;
}

#ifdef CONFIG_KSZ_SWITCH
static void priv_adjust_link(struct net_device *dev)
{}

#if defined(CONFIG_HAVE_KSZ9897) || defined(CONFIG_HAVE_LAN937X)
static int get_net_ready(struct net_device *dev)
{
	struct fec_enet_private *priv = netdev_priv(dev);

	return priv->hw_priv->port.ready;
}  /* get_net_ready */
#endif

static void hw_set_multicast(struct fec_enet_private *fep, int multicast)
{
	unsigned int tmp;

	tmp = readl(fep->hwp + FEC_R_CNTRL);
	tmp &= ~0x8;
	writel(tmp, fep->hwp + FEC_R_CNTRL);

	if (multicast) {
		/* Catch all multicast addresses, so set the
		 * filter to all 1's
		 */
		writel(0xffffffff, fep->hwp + FEC_GRP_HASH_TABLE_HIGH);
		writel(0xffffffff, fep->hwp + FEC_GRP_HASH_TABLE_LOW);
	} else {
		writel(0, fep->hwp + FEC_GRP_HASH_TABLE_HIGH);
		writel(0, fep->hwp + FEC_GRP_HASH_TABLE_LOW);
	}
}  /* hw_set_multicast */

static void hw_set_promisc(struct fec_enet_private *fep, int promisc)
{
	unsigned int tmp;

	tmp = readl(fep->hwp + FEC_R_CNTRL);
	if (promisc)
		tmp |= 0x8;
	else
		tmp &= ~0x8;
	writel(tmp, fep->hwp + FEC_R_CNTRL);
}  /* hw_set_promisc */

static void dev_set_multicast(struct fec_enet_private *fep, int multicast)
{
	if (multicast != fep->multi) {
		struct fec_enet_private *hfep = fep->hw_priv;
		u8 hw_multi = hfep->hw_multi;

		if (multicast)
			++hfep->hw_multi;
		else
			--hfep->hw_multi;
		fep->multi = multicast;

		/* Turn on/off all multicast mode. */
		if (hfep->hw_multi <= 1 && hw_multi <= 1)
			hw_set_multicast(hfep, hfep->hw_multi);
	}
}  /* dev_set_multicast */

static void dev_set_promisc(struct fec_enet_private *fep, int promisc)
{
	if (promisc != fep->promisc) {
		struct fec_enet_private *hfep = fep->hw_priv;
		u8 hw_promisc = hfep->hw_promisc;

		if (promisc)
			++hfep->hw_promisc;
		else
			--hfep->hw_promisc;
		fep->promisc = promisc;

		/* Turn on/off promiscuous mode. */
		if (hfep->hw_promisc <= 1 && hw_promisc <= 1)
			hw_set_promisc(hfep, hfep->hw_promisc);
	}
}  /* dev_set_promisc */

static void promisc_reset_work(struct work_struct *work)
{
	struct delayed_work *dwork = to_delayed_work(work);
	struct fec_enet_private *hfep = container_of(dwork,
		struct fec_enet_private, promisc_reset);

	hfep->hw_promisc = 0;
	hw_set_promisc(hfep, hfep->promisc);
}  /* promisc_reset_work */

static void fec_enet_set_mac_addr(struct net_device *dev)
{
	struct fec_enet_private *fep = netdev_priv(dev);
	struct fec_enet_private *hfep = fep->hw_priv;
	struct ksz_sw *sw = fep->port.sw;
	u8 hw_promisc = hfep->hw_promisc;
	u8 promisc;

	promisc = sw->net_ops->set_mac_addr(sw, dev, hw_promisc,
		fep->port.first_port);
	if (promisc != hfep->hw_promisc) {

		/* A hack to accept changed KSZ9897 IBA response. */
		if (!hfep->hw_promisc && 2 == promisc) {
			promisc = 1;
			schedule_delayed_work(&hfep->promisc_reset, 10);
		}
		hfep->hw_promisc = promisc;

		/* Turn on/off promiscuous mode. */
		if (hfep->hw_promisc <= 1 && hw_promisc <= 1)
			hw_set_promisc(hfep, hfep->hw_promisc);
	}
}  /* fec_enet_set_mac_addr */

static void prep_sw_first(struct ksz_sw *sw, int *port_count,
	int *mib_port_count, int *dev_count, char *dev_name)
{
	*port_count = 1;
	*mib_port_count = 1;
	*dev_count = 1;
	dev_name[0] = '\0';
#if defined(CONFIG_HAVE_KSZ9897) || defined(CONFIG_HAVE_LAN937X)
	sw->net_ops->get_ready = get_net_ready;
#endif
	sw->net_ops->setup_special(sw, port_count, mib_port_count, dev_count,
				   NULL);
	sw_update_csum(sw);
}  /* prep_sw_first */

static void prep_sw_dev(struct ksz_sw *sw, struct fec_enet_private *fep, int i,
	int port_count, int mib_port_count, char *dev_name)
{
	int phy_mode;
	char phy_id[MII_BUS_ID_SIZE];
	char bus_id[MII_BUS_ID_SIZE];

	fep->phy_addr = sw->net_ops->setup_dev(sw, fep->netdev, dev_name,
		&fep->port, i, port_count, mib_port_count);

	phy_mode = fep->phy_interface;
	snprintf(bus_id, MII_BUS_ID_SIZE, "sw.%d", sw->id);
	snprintf(phy_id, MII_BUS_ID_SIZE, PHY_ID_FMT, bus_id, fep->phy_addr);
	if (!fep->netdev->phydev)
		phy_attach(fep->netdev, phy_id, phy_mode);
}  /* prep_sw_dev */

static int fec_enet_sw_init(struct fec_enet_private *fep)
{
	struct ksz_sw *sw;
	int err;
	int i;
	int port_count;
	int dev_count;
	int mib_port_count;
	char dev_label[IFNAMSIZ];
	struct fec_enet_private *hw_priv;
	struct net_device *dev;
	struct net_device *main_dev;
	struct platform_device *pdev;
	netdev_features_t features;

	sw = fep->port.sw;

	/* This is the main private structure holding hardware information. */
	hw_priv = fep;
	hw_priv->parent = sw->dev;
	main_dev = fep->netdev;
	pdev = fep->pdev;
	features = main_dev->features;

	prep_sw_first(sw, &port_count, &mib_port_count, &dev_count, dev_label);

	/* The main switch phydev will not be attached. */
	if (dev_count > 1) {
		struct phy_device *phydev = sw->phy[0];

		phydev->interface = fep->phy_interface;
	}

	/* Save the base device name. */
	strlcpy(dev_label, hw_priv->netdev->name, IFNAMSIZ);

#ifndef CONFIG_KSZ_SMI
	if (sw->net_ops->setup_mdiobus)
		sw->net_ops->setup_mdiobus(sw, fep->mii_bus);
#endif
	prep_sw_dev(sw, fep, 0, port_count, mib_port_count, dev_label);

	/* Only the main one needs to set adjust_link for configuration. */
	if (fep->netdev->phydev->mdio.bus &&
	    !fep->netdev->phydev->adjust_link) {
		fep->netdev->phydev->adjust_link = fec_enet_adjust_link;

		fep->link = 0;
		fep->speed = 0;
		fep->full_duplex = 0;
	}

	INIT_DELAYED_WORK(&hw_priv->promisc_reset, promisc_reset_work);

	for (i = 1; i < dev_count; i++) {
		dev = alloc_etherdev_mqs(sizeof(struct fec_enet_private) +
					 FEC_STATS_SIZE,
					 hw_priv->num_tx_queues,
					 hw_priv->num_rx_queues);
		if (!dev)
			break;

		fep = netdev_priv(dev);
		fep->pdev = pdev;
		fep->netdev = dev;
		fep->num_rx_queues = hw_priv->num_rx_queues;
		fep->num_tx_queues = hw_priv->num_tx_queues;
		fep->hwp = hw_priv->hwp;

		fep->hw_priv = hw_priv;
		fep->phy_interface = hw_priv->phy_interface;

		spin_lock_init(&fep->tx_lock);

		dev->watchdog_timeo = TX_TIMEOUT;
		dev->netdev_ops = main_dev->netdev_ops;
		dev->ethtool_ops = main_dev->ethtool_ops;

		dev->base_addr = main_dev->base_addr;
		memcpy(dev->dev_addr, main_dev->dev_addr, ETH_ALEN);

		dev->hw_features = main_dev->hw_features;
		dev->features = features;

		SET_NETDEV_DEV(dev, &pdev->dev);

		prep_sw_dev(sw, fep, i, port_count, mib_port_count, dev_label);
		if (fep->netdev->phydev->mdio.bus)
			fep->netdev->phydev->adjust_link = priv_adjust_link;

		err = register_netdev(dev);
		if (err) {
			free_netdev(dev);
			break;
		}

		netif_carrier_off(dev);
	}

#if !defined(CONFIG_KSZ_IBA_ONLY)
	/*
	 * Adding sysfs support is optional for network device.  It is more
	 * convenient to locate eth0 more or less than spi<bus>.<select>,
	 * especially when the bus number is auto assigned which results in a
	 * very big number.
	 */
	err = init_sw_sysfs(sw, &hw_priv->sysfs, &main_dev->dev);

#ifdef CONFIG_1588_PTP
	if (sw->features & PTP_HW)
		err = init_ptp_sysfs(&hw_priv->ptp_sysfs, &main_dev->dev);
#endif
#ifdef CONFIG_KSZ_DLR
	if (sw->features & DLR_HW)
		err = init_dlr_sysfs(&main_dev->dev);
#endif
#endif

	sw_device_seen++;

	return 0;
}

#if defined(CONFIG_KSZ_IBA_ONLY)
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
	struct fec_enet_private *fep;
	int rx_mode;

	if (2 != iba->use_iba)
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

	fep = netdev_priv(dev);

	sw->reg = &sw_iba_ops;
	iba->cnt = 0;
	if (ksz_probe_next(sw->dev)) {
		fep->parent = NULL;
		fep->port.sw = NULL;
		return;
	}

#ifdef CONFIG_1588_PTP
	sw->ptp_hw.reg = &ptp_iba_ops;
#endif

	fec_enet_sw_init(fep);

	fep->multi = false;
	fep->promisc = false;

	fep->hw_multi = 0;
	fep->hw_promisc = 0;

#if 1
	/* Clear MIB counters for debugging. */
	memset(&fep->ethtool_stats, 0, FEC_STATS_SIZE);
#endif
	rx_mode = sw->net_ops->open_dev(sw, dev, &fep->port, dev->dev_addr);
	if (rx_mode & 1) {
		fep->hw_multi = 1;
		hw_set_multicast(fep, fep->hw_multi);
	}
	if (rx_mode & 2) {
		fep->hw_promisc = 1;
		hw_set_promisc(fep, fep->hw_promisc);
	}
	sw->net_ops->open(sw);

	sw->net_ops->open_port(sw, dev, &fep->port);
	fep->opened++;

	/* Signal IBA initialization is complete. */
	if (2 == sw->info->iba.use_iba)
		sw->info->iba.use_iba = 3;
}  /* netdev_start_iba */

static int create_sw_dev(struct net_device *dev, struct fec_enet_private *fep)
{
	struct sw_priv *ks;
	struct ksz_sw *sw;

	/*
	 * Stop normal traffic from going out until the switch is
	 * configured to block looping frames.
	 */
	netif_carrier_off(dev);

	ks = kzalloc(sizeof(struct sw_priv), GFP_KERNEL);
	if (!ks)
		return -ENOMEM;
	ks->hw_dev = dev;
	ks->dev = &dev->dev;

	ks->irq = get_sw_irq(fep, &ks->of_dev);
	if (ks->irq == fep->netdev->phydev->irq)
		ks->irq = 0;

	intr_mode = 1;
	sw_device_present = 0;
	sw = &ks->sw;
	ksz_probe_prep(ks, dev);

	sw->net_ops->get_ready = get_net_ready;
	sw->netdev[0] = dev;
	sw->netport[0] = &fep->port;
	sw->main_dev = dev;
	sw->main_port = &fep->port;
	sw->dev_count = 1;

	INIT_DELAYED_WORK(&sw->set_ops, netdev_start_iba);

	sw_set_dev(sw, dev, dev->dev_addr);

	fep->parent = sw->dev;
	fep->port.sw = sw;

	sw->main_port->iba_ready = true;

#ifdef DEBUG_MSG
	init_dbg();
#endif
	return 0;
}  /* create_sw_dev */
#endif

static void fec_enet_sw_exit(struct fec_enet_private *fep)
{
	struct net_device *dev = fep->netdev;
	struct ksz_sw *sw = fep->port.sw;
	int i;

#if !defined(CONFIG_KSZ_IBA_ONLY)
#ifdef CONFIG_KSZ_DLR
	if (sw->features & DLR_HW)
		exit_dlr_sysfs(&dev->dev);
#endif
#ifdef CONFIG_1588_PTP
	if (sw->features & PTP_HW)
		exit_ptp_sysfs(&fep->ptp_sysfs, &dev->dev);
#endif
	exit_sw_sysfs(sw, &fep->sysfs, &dev->dev);
#endif
	for (i = 1; i < sw->dev_count + sw->dev_offset; i++) {
		dev = sw->netdev[i];
		if (!dev)
			continue;
		fep = netdev_priv(dev);
		flush_work(&fep->port.link_update);
		unregister_netdev(dev);
		if (dev->phydev->mdio.bus)
			phy_detach(dev->phydev);
		free_netdev(dev);
	}
}
#endif

#ifdef CONFIG_KSZ_SMI
/* These SMI access functions may require non-standard MDIO signal and so the
 * standard phy_read and phy_write functions cannot be used.
 */
static int smi_read(struct mii_bus *bus, int phy_id, int regnum)
{
	return fec_enet_mdio_read(bus, phy_id, regnum);
}

static int smi_write(struct mii_bus *bus, int phy_id, int regnum, u16 val)
{
	return fec_enet_mdio_write(bus, phy_id, regnum, val);
}
#endif

static int
fec_enet_open(struct net_device *ndev)
{
	struct fec_enet_private *fep = netdev_priv(ndev);
	int ret;
	bool reset_again;

#ifdef CONFIG_KSZ_SWITCH
	struct net_device *pndev = ndev;
	struct fec_enet_private *pfep = fep;
	struct ksz_sw *sw = fep->port.sw;

	if (sw_is_switch(sw)) {

		/* This is the true private data. */
		fep = pfep->hw_priv;
		pfep->multi = false;
		pfep->promisc = false;
		if (fep->opened > 0) {
			netif_carrier_off(ndev);
			goto skip_hw;
		}

		/* Use first net device for accessing hardware. */
		ndev = fep->netdev;
	}
#endif

	ret = pm_runtime_get_sync(&fep->pdev->dev);
	if (ret < 0)
		return ret;

	pinctrl_pm_select_default_state(&fep->pdev->dev);
	ret = fec_enet_clk_enable(ndev, true);
	if (ret)
		goto clk_enable;

	/* During the first fec_enet_open call the PHY isn't probed at this
	 * point. Therefore the phy_reset_after_clk_enable() call within
	 * fec_enet_clk_enable() fails. As we need this reset in order to be
	 * sure the PHY is working correctly we check if we need to reset again
	 * later when the PHY is probed
	 */
	if (ndev->phydev && ndev->phydev->drv)
		reset_again = false;
	else
		reset_again = true;

	/* I should reset the ring buffers here, but I don't yet know
	 * a simple way to do that.
	 */

	ret = fec_enet_alloc_buffers(ndev);
	if (ret)
		goto err_enet_alloc;

	/* Init MAC prior to mii bus probe */
	fec_restart(ndev);

	/* Call phy_reset_after_clk_enable() again if it failed during
	 * phy_reset_after_clk_enable() before because the PHY wasn't probed.
	 */
	if (reset_again)
		fec_enet_phy_reset_after_clk_enable(ndev);

	/* Probe and connect to PHY when open the interface */
	ret = fec_enet_mii_probe(ndev);
	if (ret)
		goto err_enet_mii_probe;

	if (fep->quirks & FEC_QUIRK_ERR006687)
		imx6q_cpuidle_fec_irqs_used();

	napi_enable(&fep->napi);

#ifdef CONFIG_KSZ_SWITCH
	if (sw_is_switch(sw)) {
		if (0 == fep->opened) {
			int rx_mode = 0;

			/* Need to wait for adjust_link to start operation. */
			fep->port.ready = false;
			fep->hw_multi = 0;
			fep->hw_promisc = 0;

#if 1
			/* Clear MIB counters for debugging. */
			memset(&fep->ethtool_stats, 0, FEC_STATS_SIZE);
#endif
			rx_mode = sw->net_ops->open_dev(sw, ndev, &pfep->port,
				ndev->dev_addr);
			if (rx_mode & 1) {
				fep->hw_multi = 1;
				hw_set_multicast(fep, fep->hw_multi);
			}
			if (rx_mode & 2) {
				fep->hw_promisc = 1;
				hw_set_promisc(fep, fep->hw_promisc);
			}
			sw->net_ops->open(sw);
		}

skip_hw:
		sw->net_ops->open_port(sw, pndev, &pfep->port);
		fep->opened++;
	}
	if (!sw_is_switch(sw))
#endif
	phy_start(ndev->phydev);
	netif_tx_start_all_queues(ndev);

	device_set_wakeup_enable(&ndev->dev, fep->wol_flag &
				 FEC_WOL_FLAG_ENABLE);

#if defined(CONFIG_KSZ_IBA_ONLY)
	if (!sw_is_switch(sw))
		create_sw_dev(ndev, fep);
#endif

	return 0;

err_enet_mii_probe:
	fec_enet_free_buffers(ndev);
err_enet_alloc:
	fec_enet_clk_enable(ndev, false);
clk_enable:
	pm_runtime_mark_last_busy(&fep->pdev->dev);
	pm_runtime_put_autosuspend(&fep->pdev->dev);
	pinctrl_pm_select_sleep_state(&fep->pdev->dev);
	return ret;
}

static int
fec_enet_close(struct net_device *ndev)
{
	struct fec_enet_private *fep = netdev_priv(ndev);

#ifdef CONFIG_KSZ_SWITCH
	struct net_device *pndev = ndev;
	struct fec_enet_private *pfep = fep;
	struct ksz_sw *sw = fep->port.sw;

#if defined(CONFIG_KSZ_IBA_ONLY)
	if (sw_is_switch(sw)) {

		/* Still under initialization in IBA-only mode. */
		if (2 == sw->info->iba.use_iba) {
			cancel_delayed_work_sync(&sw->set_ops);

			/* May not started yet. */
			if (2 == sw->info->iba.use_iba) {
				kfree(sw->dev);
				fep->port.sw = NULL;
				sw = NULL;
			}
		}
	}
#endif
	if (sw_is_switch(sw)) {
		fep = pfep->hw_priv;
		dev_set_multicast(pfep, false);
		dev_set_promisc(pfep, false);
		sw->net_ops->close_port(sw, pndev, &pfep->port);
		fep->opened--;
		if (fep->opened > 0) {
			if (netif_device_present(ndev))
				netif_tx_disable(ndev);
			netif_carrier_off(ndev);
			return 0;
		}

		/* Use first net device for accessing hardware. */
		ndev = fep->netdev;
		if (!fep->opened) {
			sw->net_ops->close(sw);
			sw->net_ops->stop(sw, true);
		}

#if defined(CONFIG_KSZ_IBA_ONLY)
		sw->net_ops->leave_dev(sw);
		ksz_remove(sw->dev);
		fep->port.sw = NULL;
		sw = NULL;
#endif
	}

	/* Reset ready indication. */
	fep->port.ready = false;

	if (!sw_is_switch(sw))
#endif
	phy_stop(ndev->phydev);

	if (netif_device_present(ndev)) {
		napi_disable(&fep->napi);
		netif_tx_disable(ndev);
		fec_stop(ndev);
	}

#ifdef CONFIG_KSZ_SWITCH
	if (!sw_is_switch(sw))
#endif
	phy_disconnect(ndev->phydev);

	if (fep->quirks & FEC_QUIRK_ERR006687)
		imx6q_cpuidle_fec_irqs_unused();

	fec_enet_update_ethtool_stats(ndev);

	fec_enet_clk_enable(ndev, false);
	pinctrl_pm_select_sleep_state(&fep->pdev->dev);
	pm_runtime_mark_last_busy(&fep->pdev->dev);
	pm_runtime_put_autosuspend(&fep->pdev->dev);

	fec_enet_free_buffers(ndev);

	return 0;
}

/* Set or clear the multicast filter for this adaptor.
 * Skeleton taken from sunlance driver.
 * The CPM Ethernet implementation allows Multicast as well as individual
 * MAC address filtering.  Some of the drivers check to make sure it is
 * a group multicast address, and discard those that are not.  I guess I
 * will do the same for now, but just remove the test if you want
 * individual filtering as well (do the upper net layers want or support
 * this kind of feature?).
 */

#define FEC_HASH_BITS	6		/* #bits in hash */

static void set_multicast_list(struct net_device *ndev)
{
	struct fec_enet_private *fep = netdev_priv(ndev);
	struct netdev_hw_addr *ha;
	unsigned int crc, tmp;
	unsigned char hash;
	unsigned int hash_high = 0, hash_low = 0;

#ifdef CONFIG_KSZ_SWITCH
	struct ksz_sw *sw = fep->port.sw;
	int multicast = ((ndev->flags & IFF_ALLMULTI) == IFF_ALLMULTI);
	bool do_hash = false;

	if (sw_is_switch(sw)) {
		dev_set_promisc(fep,
			((ndev->flags & IFF_PROMISC) == IFF_PROMISC));
		if (!(ndev->flags & IFF_ALLMULTI)) {
			struct fec_enet_private *hfep = fep->hw_priv;

			if (sw->dev_count > 1) {
				if ((ndev->flags & IFF_MULTICAST) &&
				    !netdev_mc_empty(ndev))
					sw->net_ops->set_multi(sw, ndev,
						&fep->port);
				multicast |= ((ndev->flags & IFF_MULTICAST) ==
					IFF_MULTICAST) << 1;
			} else if (!hfep->hw_multi && !netdev_mc_empty(ndev)) {
				do_hash = true;
			}
		}
		dev_set_multicast(fep, multicast);
		if (do_hash)
			goto multicast_hash;
		return;
	}
#endif

	if (ndev->flags & IFF_PROMISC) {
		tmp = readl(fep->hwp + FEC_R_CNTRL);
		tmp |= 0x8;
		writel(tmp, fep->hwp + FEC_R_CNTRL);
		return;
	}

	tmp = readl(fep->hwp + FEC_R_CNTRL);
	tmp &= ~0x8;
	writel(tmp, fep->hwp + FEC_R_CNTRL);

	if (ndev->flags & IFF_ALLMULTI) {
		/* Catch all multicast addresses, so set the
		 * filter to all 1's
		 */
		writel(0xffffffff, fep->hwp + FEC_GRP_HASH_TABLE_HIGH);
		writel(0xffffffff, fep->hwp + FEC_GRP_HASH_TABLE_LOW);

		return;
	}

#ifdef CONFIG_KSZ_SWITCH
multicast_hash:
#endif

	/* Add the addresses in hash register */
	netdev_for_each_mc_addr(ha, ndev) {
		/* calculate crc32 value of mac address */
		crc = ether_crc_le(ndev->addr_len, ha->addr);

		/* only upper 6 bits (FEC_HASH_BITS) are used
		 * which point to specific bit in the hash registers
		 */
		hash = (crc >> (32 - FEC_HASH_BITS)) & 0x3f;

		if (hash > 31)
			hash_high |= 1 << (hash - 32);
		else
			hash_low |= 1 << hash;
	}

	writel(hash_high, fep->hwp + FEC_GRP_HASH_TABLE_HIGH);
	writel(hash_low, fep->hwp + FEC_GRP_HASH_TABLE_LOW);
}

/* Set a MAC change in hardware. */
static int
fec_set_mac_address(struct net_device *ndev, void *p)
{
	struct fec_enet_private *fep = netdev_priv(ndev);
	struct sockaddr *addr = p;

	if (addr) {
		if (!is_valid_ether_addr(addr->sa_data))
			return -EADDRNOTAVAIL;
		memcpy(ndev->dev_addr, addr->sa_data, ndev->addr_len);

#ifdef CONFIG_KSZ_SWITCH
		if (sw_is_switch(fep->port.sw))
			fec_enet_set_mac_addr(ndev);
#endif
	}

	/* Add netif status check here to avoid system hang in below case:
	 * ifconfig ethx down; ifconfig ethx hw ether xx:xx:xx:xx:xx:xx;
	 * After ethx down, fec all clocks are gated off and then register
	 * access causes system hang.
	 */
	if (!netif_running(ndev))
		return 0;

	writel(ndev->dev_addr[3] | (ndev->dev_addr[2] << 8) |
		(ndev->dev_addr[1] << 16) | (ndev->dev_addr[0] << 24),
		fep->hwp + FEC_ADDR_LOW);
	writel((ndev->dev_addr[5] << 16) | (ndev->dev_addr[4] << 24),
		fep->hwp + FEC_ADDR_HIGH);
	return 0;
}

#ifdef CONFIG_NET_POLL_CONTROLLER
/**
 * fec_poll_controller - FEC Poll controller function
 * @dev: The FEC network adapter
 *
 * Polled functionality used by netconsole and others in non interrupt mode
 *
 */
static void fec_poll_controller(struct net_device *dev)
{
	int i;
	struct fec_enet_private *fep = netdev_priv(dev);

	for (i = 0; i < FEC_IRQ_NUM; i++) {
		if (fep->irq[i] > 0) {
			disable_irq(fep->irq[i]);
			fec_enet_interrupt(fep->irq[i], dev);
			enable_irq(fep->irq[i]);
		}
	}
}
#endif

static inline void fec_enet_set_netdev_features(struct net_device *netdev,
	netdev_features_t features)
{
	struct fec_enet_private *fep = netdev_priv(netdev);
	netdev_features_t changed = features ^ netdev->features;

	netdev->features = features;

	/* Receive checksum has been changed */
	if (changed & NETIF_F_RXCSUM) {
		if (features & NETIF_F_RXCSUM)
			fep->csum_flags |= FLAG_RX_CSUM_ENABLED;
		else
			fep->csum_flags &= ~FLAG_RX_CSUM_ENABLED;
	}
}

static int fec_set_features(struct net_device *netdev,
	netdev_features_t features)
{
	struct fec_enet_private *fep = netdev_priv(netdev);
	netdev_features_t changed = features ^ netdev->features;

	if (netif_running(netdev) && changed & NETIF_F_RXCSUM) {
		napi_disable(&fep->napi);
		netif_tx_lock_bh(netdev);
		fec_stop(netdev);
		fec_enet_set_netdev_features(netdev, features);
		fec_restart(netdev);
		netif_tx_wake_all_queues(netdev);
		netif_tx_unlock_bh(netdev);
		napi_enable(&fep->napi);
	} else {
		fec_enet_set_netdev_features(netdev, features);
	}

	return 0;
}

static const struct net_device_ops fec_netdev_ops = {
	.ndo_open		= fec_enet_open,
	.ndo_stop		= fec_enet_close,
	.ndo_start_xmit		= fec_enet_start_xmit,
	.ndo_set_rx_mode	= set_multicast_list,
	.ndo_validate_addr	= eth_validate_addr,
	.ndo_tx_timeout		= fec_timeout,
	.ndo_set_mac_address	= fec_set_mac_address,
	.ndo_do_ioctl		= fec_enet_ioctl,
#ifdef CONFIG_NET_POLL_CONTROLLER
	.ndo_poll_controller	= fec_poll_controller,
#endif
	.ndo_set_features	= fec_set_features,
#ifdef CONFIG_KSZ_SWITCH
	.ndo_vlan_rx_add_vid	= fec_enet_add_vid,
	.ndo_vlan_rx_kill_vid	= fec_enet_kill_vid,
#endif
};

static const unsigned short offset_des_active_rxq[] = {
	FEC_R_DES_ACTIVE_0, FEC_R_DES_ACTIVE_1, FEC_R_DES_ACTIVE_2
};

static const unsigned short offset_des_active_txq[] = {
	FEC_X_DES_ACTIVE_0, FEC_X_DES_ACTIVE_1, FEC_X_DES_ACTIVE_2
};

 /*
  * XXX:  We need to clean up on failure exits here.
  *
  */
static int fec_enet_init(struct net_device *ndev)
{
	struct fec_enet_private *fep = netdev_priv(ndev);
	struct bufdesc *cbd_base;
	dma_addr_t bd_dma;
	int bd_size;
	unsigned int i;
	unsigned dsize = fep->bufdesc_ex ? sizeof(struct bufdesc_ex) :
			sizeof(struct bufdesc);
	unsigned dsize_log2 = __fls(dsize);
	int ret;

	WARN_ON(dsize != (1 << dsize_log2));
#if defined(CONFIG_ARM) || defined(CONFIG_ARM64)
	fep->rx_align = 0xf;
	fep->tx_align = 0xf;
#else
	fep->rx_align = 0x3;
	fep->tx_align = 0x3;
#endif

	/* Check mask of the streaming and coherent API */
	ret = dma_set_mask_and_coherent(&fep->pdev->dev, DMA_BIT_MASK(32));
	if (ret < 0) {
		dev_warn(&fep->pdev->dev, "No suitable DMA available\n");
		return ret;
	}

	ret = fec_enet_alloc_queue(ndev);
	if (ret)
		return ret;

	bd_size = (fep->total_tx_ring_size + fep->total_rx_ring_size) * dsize;

	/* Allocate memory for buffer descriptors. */
	cbd_base = dmam_alloc_coherent(&fep->pdev->dev, bd_size, &bd_dma,
				       GFP_KERNEL);
	if (!cbd_base) {
		ret = -ENOMEM;
		goto free_queue_mem;
	}

	/* Get the Ethernet address */
	fec_get_mac(ndev);
	/* make sure MAC we just acquired is programmed into the hw */
	fec_set_mac_address(ndev, NULL);

	/* Set receive and transmit descriptor base. */
	for (i = 0; i < fep->num_rx_queues; i++) {
		struct fec_enet_priv_rx_q *rxq = fep->rx_queue[i];
		unsigned size = dsize * rxq->bd.ring_size;

		rxq->bd.qid = i;
		rxq->bd.base = cbd_base;
		rxq->bd.cur = cbd_base;
		rxq->bd.dma = bd_dma;
		rxq->bd.dsize = dsize;
		rxq->bd.dsize_log2 = dsize_log2;
		rxq->bd.reg_desc_active = fep->hwp + offset_des_active_rxq[i];
		bd_dma += size;
		cbd_base = (struct bufdesc *)(((void *)cbd_base) + size);
		rxq->bd.last = (struct bufdesc *)(((void *)cbd_base) - dsize);
	}

	for (i = 0; i < fep->num_tx_queues; i++) {
		struct fec_enet_priv_tx_q *txq = fep->tx_queue[i];
		unsigned size = dsize * txq->bd.ring_size;

		txq->bd.qid = i;
		txq->bd.base = cbd_base;
		txq->bd.cur = cbd_base;
		txq->bd.dma = bd_dma;
		txq->bd.dsize = dsize;
		txq->bd.dsize_log2 = dsize_log2;
		txq->bd.reg_desc_active = fep->hwp + offset_des_active_txq[i];
		bd_dma += size;
		cbd_base = (struct bufdesc *)(((void *)cbd_base) + size);
		txq->bd.last = (struct bufdesc *)(((void *)cbd_base) - dsize);
	}


	/* The FEC Ethernet specific entries in the device structure */
	ndev->watchdog_timeo = TX_TIMEOUT;
	ndev->netdev_ops = &fec_netdev_ops;
	ndev->ethtool_ops = &fec_enet_ethtool_ops;

	writel(FEC_RX_DISABLED_IMASK, fep->hwp + FEC_IMASK);
	netif_napi_add(ndev, &fep->napi, fec_enet_rx_napi, NAPI_POLL_WEIGHT);

	if (fep->quirks & FEC_QUIRK_HAS_VLAN)
		/* enable hw VLAN support */
		ndev->features |= NETIF_F_HW_VLAN_CTAG_RX;

	if (fep->quirks & FEC_QUIRK_HAS_CSUM) {
		ndev->gso_max_segs = FEC_MAX_TSO_SEGS;

		/* enable hw accelerator */
		ndev->features |= (NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM
				| NETIF_F_RXCSUM | NETIF_F_SG | NETIF_F_TSO);
		fep->csum_flags |= FLAG_RX_CSUM_ENABLED;
	}

	if (fep->quirks & FEC_QUIRK_HAS_AVB) {
		fep->tx_align = 0;
		fep->rx_align = 0x3f;
	}

#ifdef CONFIG_KSZ_SWITCH

	/* Point to real private structure holding hardware information. */
	fep->hw_priv = fep;

	spin_lock_init(&fep->tx_lock);

#if defined(CONFIG_KSZ_IBA_ONLY)
	ndev->features &= ~NETIF_F_TSO;
#endif
#endif

	ndev->hw_features = ndev->features;

	fec_restart(ndev);

	if (fep->quirks & FEC_QUIRK_MIB_CLEAR)
		fec_enet_clear_ethtool_stats(ndev);
	else
		fec_enet_update_ethtool_stats(ndev);

	return 0;

free_queue_mem:
	fec_enet_free_queue(ndev);
	return ret;
}

#ifdef CONFIG_OF
static int fec_reset_phy(struct platform_device *pdev)
{
	int err, phy_reset;
	bool active_high = false;
	int msec = 1, phy_post_delay = 0;
	struct device_node *np = pdev->dev.of_node;

	if (!np)
		return 0;

	err = of_property_read_u32(np, "phy-reset-duration", &msec);
	/* A sane reset duration should not be longer than 1s */
	if (!err && msec > 1000)
		msec = 1;

	phy_reset = of_get_named_gpio(np, "phy-reset-gpios", 0);
	if (phy_reset == -EPROBE_DEFER)
		return phy_reset;
	else if (!gpio_is_valid(phy_reset))
		return 0;

	err = of_property_read_u32(np, "phy-reset-post-delay", &phy_post_delay);
	/* valid reset duration should be less than 1s */
	if (!err && phy_post_delay > 1000)
		return -EINVAL;

	active_high = of_property_read_bool(np, "phy-reset-active-high");

	err = devm_gpio_request_one(&pdev->dev, phy_reset,
			active_high ? GPIOF_OUT_INIT_HIGH : GPIOF_OUT_INIT_LOW,
			"phy-reset");
	if (err) {
		dev_err(&pdev->dev, "failed to get phy-reset-gpios: %d\n", err);
		return err;
	}

	if (msec > 20)
		msleep(msec);
	else
		usleep_range(msec * 1000, msec * 1000 + 1000);

	gpio_set_value_cansleep(phy_reset, !active_high);

	if (!phy_post_delay)
		return 0;

	if (phy_post_delay > 20)
		msleep(phy_post_delay);
	else
		usleep_range(phy_post_delay * 1000,
			     phy_post_delay * 1000 + 1000);

	return 0;
}
#else /* CONFIG_OF */
static int fec_reset_phy(struct platform_device *pdev)
{
	/*
	 * In case of platform probe, the reset has been done
	 * by machine code.
	 */
	return 0;
}
#endif /* CONFIG_OF */

static void
fec_enet_get_queue_num(struct platform_device *pdev, int *num_tx, int *num_rx)
{
	struct device_node *np = pdev->dev.of_node;

	*num_tx = *num_rx = 1;

	if (!np || !of_device_is_available(np))
		return;

	/* parse the num of tx and rx queues */
	of_property_read_u32(np, "fsl,num-tx-queues", num_tx);

	of_property_read_u32(np, "fsl,num-rx-queues", num_rx);

	if (*num_tx < 1 || *num_tx > FEC_ENET_MAX_TX_QS) {
		dev_warn(&pdev->dev, "Invalid num_tx(=%d), fall back to 1\n",
			 *num_tx);
		*num_tx = 1;
		return;
	}

	if (*num_rx < 1 || *num_rx > FEC_ENET_MAX_RX_QS) {
		dev_warn(&pdev->dev, "Invalid num_rx(=%d), fall back to 1\n",
			 *num_rx);
		*num_rx = 1;
		return;
	}

}

static int fec_enet_get_irq_cnt(struct platform_device *pdev)
{
	int irq_cnt = platform_irq_count(pdev);

	if (irq_cnt > FEC_IRQ_NUM)
		irq_cnt = FEC_IRQ_NUM;	/* last for pps */
	else if (irq_cnt == 2)
		irq_cnt = 1;	/* last for pps */
	else if (irq_cnt <= 0)
		irq_cnt = 1;	/* At least 1 irq is needed */
	return irq_cnt;
}

static int fec_enet_init_stop_mode(struct fec_enet_private *fep,
				   struct fec_devinfo *dev_info,
				   struct device_node *np)
{
	struct device_node *gpr_np;
	int ret = 0;

	if (!dev_info)
		return 0;

	gpr_np = of_parse_phandle(np, "gpr", 0);
	if (!gpr_np)
		return 0;

	fep->stop_gpr.gpr = syscon_node_to_regmap(gpr_np);
	if (IS_ERR(fep->stop_gpr.gpr)) {
		dev_err(&fep->pdev->dev, "could not find gpr regmap\n");
		ret = PTR_ERR(fep->stop_gpr.gpr);
		fep->stop_gpr.gpr = NULL;
		goto out;
	}

	fep->stop_gpr.reg = dev_info->stop_gpr_reg;
	fep->stop_gpr.bit = dev_info->stop_gpr_bit;

out:
	of_node_put(gpr_np);

	return ret;
}

static int
fec_probe(struct platform_device *pdev)
{
	struct fec_enet_private *fep;
	struct fec_platform_data *pdata;
	struct net_device *ndev;
	int i, irq, ret = 0;
	const struct of_device_id *of_id;
	static int dev_id;
	struct device_node *np = pdev->dev.of_node, *phy_node;
	int num_tx_qs;
	int num_rx_qs;
	char irq_name[8];
	int irq_cnt;
	struct fec_devinfo *dev_info;

	fec_enet_get_queue_num(pdev, &num_tx_qs, &num_rx_qs);

	/* Init network device */
	ndev = alloc_etherdev_mqs(sizeof(struct fec_enet_private) +
				  FEC_STATS_SIZE, num_tx_qs, num_rx_qs);
	if (!ndev)
		return -ENOMEM;

	SET_NETDEV_DEV(ndev, &pdev->dev);

	/* setup board info structure */
	fep = netdev_priv(ndev);

	of_id = of_match_device(fec_dt_ids, &pdev->dev);
	if (of_id)
		pdev->id_entry = of_id->data;
	dev_info = (struct fec_devinfo *)pdev->id_entry->driver_data;
	if (dev_info)
		fep->quirks = dev_info->quirks;

	fep->netdev = ndev;
	fep->num_rx_queues = num_rx_qs;
	fep->num_tx_queues = num_tx_qs;

#if !defined(CONFIG_M5272)
	/* default enable pause frame auto negotiation */
	if (fep->quirks & FEC_QUIRK_HAS_GBIT)
		fep->pause_flag |= FEC_PAUSE_FLAG_AUTONEG;
#endif

	/* Select default pin state */
	pinctrl_pm_select_default_state(&pdev->dev);

	fep->hwp = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(fep->hwp)) {
		ret = PTR_ERR(fep->hwp);
		goto failed_ioremap;
	}

	fep->pdev = pdev;
	fep->dev_id = dev_id++;

	platform_set_drvdata(pdev, ndev);

	if ((of_machine_is_compatible("fsl,imx6q") ||
	     of_machine_is_compatible("fsl,imx6dl")) &&
	    !of_property_read_bool(np, "fsl,err006687-workaround-present"))
		fep->quirks |= FEC_QUIRK_ERR006687;

	if (of_get_property(np, "fsl,magic-packet", NULL))
		fep->wol_flag |= FEC_WOL_HAS_MAGIC_PACKET;

	ret = fec_enet_init_stop_mode(fep, dev_info, np);
	if (ret)
		goto failed_stop_mode;

	phy_node = of_parse_phandle(np, "phy-handle", 0);
	if (!phy_node && of_phy_is_fixed_link(np)) {
		ret = of_phy_register_fixed_link(np);
		if (ret < 0) {
			dev_err(&pdev->dev,
				"broken fixed-link specification\n");
			goto failed_phy;
		}
		phy_node = of_node_get(np);
	}
	fep->phy_node = phy_node;

	ret = of_get_phy_mode(pdev->dev.of_node);
	if (ret < 0) {
		pdata = dev_get_platdata(&pdev->dev);
		if (pdata)
			fep->phy_interface = pdata->phy;
		else
			fep->phy_interface = PHY_INTERFACE_MODE_MII;
	} else {
		fep->phy_interface = ret;
	}

	fep->clk_ipg = devm_clk_get(&pdev->dev, "ipg");
	if (IS_ERR(fep->clk_ipg)) {
		ret = PTR_ERR(fep->clk_ipg);
		goto failed_clk;
	}

	fep->clk_ahb = devm_clk_get(&pdev->dev, "ahb");
	if (IS_ERR(fep->clk_ahb)) {
		ret = PTR_ERR(fep->clk_ahb);
		goto failed_clk;
	}

	fep->itr_clk_rate = clk_get_rate(fep->clk_ahb);

	/* enet_out is optional, depends on board */
	fep->clk_enet_out = devm_clk_get(&pdev->dev, "enet_out");
	if (IS_ERR(fep->clk_enet_out))
		fep->clk_enet_out = NULL;

	fep->ptp_clk_on = false;
	mutex_init(&fep->ptp_clk_mutex);

	/* clk_ref is optional, depends on board */
	fep->clk_ref = devm_clk_get(&pdev->dev, "enet_clk_ref");
	if (IS_ERR(fep->clk_ref))
		fep->clk_ref = NULL;

	fep->bufdesc_ex = fep->quirks & FEC_QUIRK_HAS_BUFDESC_EX;
	fep->clk_ptp = devm_clk_get(&pdev->dev, "ptp");
	if (IS_ERR(fep->clk_ptp)) {
		fep->clk_ptp = NULL;
		fep->bufdesc_ex = false;
	}

	ret = fec_enet_clk_enable(ndev, true);
	if (ret)
		goto failed_clk;

	ret = clk_prepare_enable(fep->clk_ipg);
	if (ret)
		goto failed_clk_ipg;
	ret = clk_prepare_enable(fep->clk_ahb);
	if (ret)
		goto failed_clk_ahb;

	fep->reg_phy = devm_regulator_get_optional(&pdev->dev, "phy");
	if (!IS_ERR(fep->reg_phy)) {
		ret = regulator_enable(fep->reg_phy);
		if (ret) {
			dev_err(&pdev->dev,
				"Failed to enable phy regulator: %d\n", ret);
			goto failed_regulator;
		}
	} else {
		if (PTR_ERR(fep->reg_phy) == -EPROBE_DEFER) {
			ret = -EPROBE_DEFER;
			goto failed_regulator;
		}
		fep->reg_phy = NULL;
	}

	pm_runtime_set_autosuspend_delay(&pdev->dev, FEC_MDIO_PM_TIMEOUT);
	pm_runtime_use_autosuspend(&pdev->dev);
	pm_runtime_get_noresume(&pdev->dev);
	pm_runtime_set_active(&pdev->dev);
	pm_runtime_enable(&pdev->dev);

	ret = fec_reset_phy(pdev);
	if (ret)
		goto failed_reset;

	irq_cnt = fec_enet_get_irq_cnt(pdev);
#ifndef CONFIG_1588_PTP
	if (fep->bufdesc_ex)
		fec_ptp_init(pdev, irq_cnt);
#endif

	ret = fec_enet_init(ndev);
	if (ret)
		goto failed_init;

	for (i = 0; i < irq_cnt; i++) {
		snprintf(irq_name, sizeof(irq_name), "int%d", i);
		irq = platform_get_irq_byname_optional(pdev, irq_name);
		if (irq < 0)
			irq = platform_get_irq(pdev, i);
		if (irq < 0) {
			ret = irq;
			goto failed_irq;
		}
		ret = devm_request_irq(&pdev->dev, irq, fec_enet_interrupt,
				       0, pdev->name, ndev);
		if (ret)
			goto failed_irq;

		fep->irq[i] = irq;
	}

	init_completion(&fep->mdio_done);
	ret = fec_enet_mii_init(pdev);
	if (ret)
		goto failed_mii_init;

#ifdef CONFIG_KSZ_SMI
	if (!ret) {
		int irq = get_sw_irq(fep, NULL);

		ret = smi_probe(&fep->sw_pdev, fep->mii_bus, irq,
				smi_read, smi_write);
		if (ret)
			goto failed_register;
	}
#endif

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

#ifdef CONFIG_KSZ_SWITCH
#if !defined(CONFIG_KSZ_IBA_ONLY)
	ret = fec_enet_sw_chk(fep);
	if (!ret) {
		ndev->features &= ~NETIF_F_TSO;
		ndev->hw_features = ndev->features;
	}
#endif
#endif

	/* Carrier starts down, phylib will bring it up */
	netif_carrier_off(ndev);
	fec_enet_clk_enable(ndev, false);
	pinctrl_pm_select_sleep_state(&pdev->dev);

	ret = register_netdev(ndev);
	if (ret)
		goto failed_register;

	device_init_wakeup(&ndev->dev, fep->wol_flag &
			   FEC_WOL_HAS_MAGIC_PACKET);

#ifndef CONFIG_1588_PTP
	if (fep->bufdesc_ex && fep->ptp_clock)
		netdev_info(ndev, "registered PHC device %d\n", fep->dev_id);
#endif

	fep->rx_copybreak = COPYBREAK_DEFAULT;
	INIT_WORK(&fep->tx_timeout_work, fec_enet_timeout_work);

#ifdef CONFIG_KSZ_SWITCH
#if !defined(CONFIG_KSZ_IBA_ONLY)
	if (fep->port.sw)
		ret = fec_enet_sw_init(fep);
#endif
#endif

	pm_runtime_mark_last_busy(&pdev->dev);
	pm_runtime_put_autosuspend(&pdev->dev);

	return 0;

failed_register:
	fec_enet_mii_remove(fep);
failed_mii_init:
failed_irq:
failed_init:
	fec_ptp_stop(pdev);
failed_reset:
	pm_runtime_put_noidle(&pdev->dev);
	pm_runtime_disable(&pdev->dev);
	if (fep->reg_phy)
		regulator_disable(fep->reg_phy);
failed_regulator:
	clk_disable_unprepare(fep->clk_ahb);
failed_clk_ahb:
	clk_disable_unprepare(fep->clk_ipg);
failed_clk_ipg:
	fec_enet_clk_enable(ndev, false);
failed_clk:
	if (of_phy_is_fixed_link(np))
		of_phy_deregister_fixed_link(np);
	of_node_put(phy_node);
failed_stop_mode:
failed_phy:
	dev_id--;
failed_ioremap:
	free_netdev(ndev);

	return ret;
}

#ifdef CONFIG_KSZ_SWITCH
static void
fec_drv_shutdown(struct platform_device *pdev)
{
	struct net_device *dev = platform_get_drvdata(pdev);
	struct fec_enet_private *fep = netdev_priv(dev);
	struct ksz_sw *sw = fep->port.sw;
	int i;
	int dev_count = 1;

	if (sw_is_switch(sw))
		dev_count = sw->dev_count + sw->dev_offset;

	/* Reverse order as the first network device may be needed. */
	for (i = dev_count - 1; i >= 0; i--) {
		if (sw_is_switch(sw)) {
			dev = sw->netdev[i];
			if (!dev)
				continue;
		}
		if (netif_running(dev)) {
			dev->netdev_ops->ndo_stop(dev);

			/* This call turns off the transmit queue. */
			netif_device_detach(dev);
		}
	}
}

static void
fec_drv_sw_remove(struct net_device *ndev, struct fec_enet_private *fep)
{
	struct ksz_sw *sw = fep->port.sw;
	bool do_exit = true;

	if (!sw_is_switch(sw))
		return;

#if defined(CONFIG_KSZ_IBA_ONLY)

	/* Still under initialization in IBA-only mode. */
	if (2 == sw->info->iba.use_iba) {
		cancel_delayed_work_sync(&sw->set_ops);

		/* May not started yet. */
		if (2 == sw->info->iba.use_iba) {
			kfree(sw->dev);
			fep->port.sw = NULL;
			return;
		}
		do_exit = false;
	}
#endif
	if (do_exit) {
		flush_work(&fep->port.link_update);
		fec_enet_sw_exit(fep);
	}
#ifdef CONFIG_KSZ_SMI
	if (fep->sw_pdev)
		smi_remove(fep->sw_pdev);
#endif
	sw->net_ops->leave_dev(sw);
	if (ndev->phydev) {
		if (ndev->phydev->mdio.bus)
			phy_detach(ndev->phydev);
		ndev->phydev = NULL;
	}
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
}
#endif

static int
fec_drv_remove(struct platform_device *pdev)
{
	struct net_device *ndev = platform_get_drvdata(pdev);
	struct fec_enet_private *fep = netdev_priv(ndev);
	struct device_node *np = pdev->dev.of_node;
	int ret;

	ret = pm_runtime_get_sync(&pdev->dev);
	if (ret < 0)
		return ret;

#ifdef CONFIG_KSZ_SWITCH
	fec_drv_sw_remove(ndev, fep);
#endif

	cancel_work_sync(&fep->tx_timeout_work);
	fec_ptp_stop(pdev);
	unregister_netdev(ndev);
	fec_enet_mii_remove(fep);
	if (fep->reg_phy)
		regulator_disable(fep->reg_phy);

	if (of_phy_is_fixed_link(np))
		of_phy_deregister_fixed_link(np);
	of_node_put(fep->phy_node);
	free_netdev(ndev);

	clk_disable_unprepare(fep->clk_ahb);
	clk_disable_unprepare(fep->clk_ipg);
	pm_runtime_put_noidle(&pdev->dev);
	pm_runtime_disable(&pdev->dev);

	return 0;
}

static int __maybe_unused fec_suspend(struct device *dev)
{
	struct net_device *ndev = dev_get_drvdata(dev);
	struct fec_enet_private *fep = netdev_priv(ndev);

	rtnl_lock();
	if (netif_running(ndev)) {
		if (fep->wol_flag & FEC_WOL_FLAG_ENABLE)
			fep->wol_flag |= FEC_WOL_FLAG_SLEEP_ON;
		phy_stop(ndev->phydev);
		napi_disable(&fep->napi);
		netif_tx_lock_bh(ndev);
		netif_device_detach(ndev);
		netif_tx_unlock_bh(ndev);
		fec_stop(ndev);
		fec_enet_clk_enable(ndev, false);
		if (!(fep->wol_flag & FEC_WOL_FLAG_ENABLE))
			pinctrl_pm_select_sleep_state(&fep->pdev->dev);
	}
	rtnl_unlock();

	if (fep->reg_phy && !(fep->wol_flag & FEC_WOL_FLAG_ENABLE))
		regulator_disable(fep->reg_phy);

	/* SOC supply clock to phy, when clock is disabled, phy link down
	 * SOC control phy regulator, when regulator is disabled, phy link down
	 */
	if (fep->clk_enet_out || fep->reg_phy)
		fep->link = 0;

	return 0;
}

static int __maybe_unused fec_resume(struct device *dev)
{
	struct net_device *ndev = dev_get_drvdata(dev);
	struct fec_enet_private *fep = netdev_priv(ndev);
	int ret;
	int val;

	if (fep->reg_phy && !(fep->wol_flag & FEC_WOL_FLAG_ENABLE)) {
		ret = regulator_enable(fep->reg_phy);
		if (ret)
			return ret;
	}

	rtnl_lock();
	if (netif_running(ndev)) {
		ret = fec_enet_clk_enable(ndev, true);
		if (ret) {
			rtnl_unlock();
			goto failed_clk;
		}
		if (fep->wol_flag & FEC_WOL_FLAG_ENABLE) {
			fec_enet_stop_mode(fep, false);

			val = readl(fep->hwp + FEC_ECNTRL);
			val &= ~(FEC_ECR_MAGICEN | FEC_ECR_SLEEP);
			writel(val, fep->hwp + FEC_ECNTRL);
			fep->wol_flag &= ~FEC_WOL_FLAG_SLEEP_ON;
		} else {
			pinctrl_pm_select_default_state(&fep->pdev->dev);
		}
		fec_restart(ndev);
		netif_tx_lock_bh(ndev);
		netif_device_attach(ndev);
		netif_tx_unlock_bh(ndev);
		napi_enable(&fep->napi);
		phy_start(ndev->phydev);
	}
	rtnl_unlock();

	return 0;

failed_clk:
	if (fep->reg_phy)
		regulator_disable(fep->reg_phy);
	return ret;
}

static int __maybe_unused fec_runtime_suspend(struct device *dev)
{
	struct net_device *ndev = dev_get_drvdata(dev);
	struct fec_enet_private *fep = netdev_priv(ndev);

	clk_disable_unprepare(fep->clk_ahb);
	clk_disable_unprepare(fep->clk_ipg);

	return 0;
}

static int __maybe_unused fec_runtime_resume(struct device *dev)
{
	struct net_device *ndev = dev_get_drvdata(dev);
	struct fec_enet_private *fep = netdev_priv(ndev);
	int ret;

	ret = clk_prepare_enable(fep->clk_ahb);
	if (ret)
		return ret;
	ret = clk_prepare_enable(fep->clk_ipg);
	if (ret)
		goto failed_clk_ipg;

	return 0;

failed_clk_ipg:
	clk_disable_unprepare(fep->clk_ahb);
	return ret;
}

static const struct dev_pm_ops fec_pm_ops = {
	SET_SYSTEM_SLEEP_PM_OPS(fec_suspend, fec_resume)
	SET_RUNTIME_PM_OPS(fec_runtime_suspend, fec_runtime_resume, NULL)
};

static struct platform_driver fec_driver = {
	.driver	= {
		.name	= DRIVER_NAME,
		.pm	= &fec_pm_ops,
		.of_match_table = fec_dt_ids,
	},
	.id_table = fec_devtype,
	.probe	= fec_probe,
	.remove	= fec_drv_remove,
#ifdef CONFIG_KSZ_SWITCH
	.shutdown	= fec_drv_shutdown,
#endif
};

module_platform_driver(fec_driver);

MODULE_ALIAS("platform:"DRIVER_NAME);
MODULE_LICENSE("GPL");
