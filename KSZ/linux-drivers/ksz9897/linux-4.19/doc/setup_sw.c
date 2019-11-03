
#if defined(CONFIG_KSZ_SWITCH) || defined(CONFIG_KSZ_DSA)
#define HAVE_KSZ_SWITCH
#endif


#if defined(CONFIG_KSZ_SWITCH_EMBEDDED)
#include <linux/of.h>

/* Need to predefine get_sysfs_data. */

#ifndef get_sysfs_data
struct ksz_port;

static void get_sysfs_data_(struct net_device *dev,
	struct semaphore **proc_sem, struct ksz_port **port);

#define get_sysfs_data		get_sysfs_data_
#endif

#endif
#if defined(CONFIG_KSZ9897_EMBEDDED)
#include "spi-ksz9897.c"
#elif defined(CONFIG_HAVE_KSZ9897)
#include "ksz_cfg_9897.h"
#endif

#if defined(HAVE_KSZ_SWITCH) && !defined(CONFIG_KSZ_SWITCH_EMBEDDED)
#include <linux/spi/spi.h>

#include "ksz_sw_phy.h"
#ifndef HAVE_KSZ_SWITCH
#define SKIP_KSZ_SWITCH_SYSFS
#endif
#include "ksz_spi_net.h"
#endif


#ifdef HAVE_KSZ_SWITCH
static inline int sw_is_switch(struct ksz_sw *sw)
{
	return sw != NULL;
}
#endif


#if defined(CONFIG_KSZ_SWITCH)

#if !defined(get_sysfs_data) || defined(CONFIG_KSZ_SWITCH_EMBEDDED)
static void get_sysfs_data_(struct net_device *dev,
	struct semaphore **proc_sem, struct ksz_port **port)
{
	/* Use private structure from net_device. */
	struct dev_priv *priv = netdev_priv(dev);
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
#define USE_MIB
#include "ksz_sw_sysfs_9897.c"
#endif
#endif


static int sw_device_present;

static struct ksz_sw *ksz_sw_check(int id)
{
	/* Avoid compiler warning as net_device is very big. */
	static struct net_device netdev;
	int phy_mode;
	char phy_id[MII_BUS_ID_SIZE];
	char bus_id[MII_BUS_ID_SIZE];
	struct phy_device *phydev;
	struct ksz_sw *sw = NULL;

	/* Check whether MII switch exists. */
	phy_mode = PHY_INTERFACE_MODE_MII;
	snprintf(bus_id, MII_BUS_ID_SIZE, "sw.%d", id);
	snprintf(phy_id, MII_BUS_ID_SIZE, PHY_ID_FMT, bus_id, 0);
	phydev = phy_attach(&netdev, phy_id, phy_mode);
	if (!IS_ERR(phydev)) {
		struct phy_priv *phydata = phydev->priv;

		sw = phydata->port.sw;

		/*
		 * In case multiple devices mode is used and this phydev is not
		 * attached again.
		 */
		if (sw)
			phydev->interface = sw->interface;
		phy_detach(phydev);
	}
	return sw;
}

/* MAC driver may already implement this function. */
static void sw_adjust_link(struct net_device *netdev)
{
	struct phy_device *phydev = netdev->phydev;

	if (phydev->link) {
		if (phy->speed) {
		}
		if (phy->duplex) {
		}
		if (phy->pause) {
		}
	}
}

static struct phy_device *ksz_sw_attach(struct net_device *netdev)
{
	int phy_addr;
	int phy_mode;
	char phy_id[MII_BUS_ID_SIZE];
	char bus_id[MII_BUS_ID_SIZE];
	struct phy_device *phydev;

	phy_addr = 0;
	phy_mode = PHY_INTERFACE_MODE_MII;
	snprintf(bus_id, MII_BUS_ID_SIZE, "sw.%d", sw_device_present);
	snprintf(phy_id, MII_BUS_ID_SIZE, PHY_ID_FMT, bus_id, phy_addr);
	phydev = phy_attach(netdev, phy_id, 0, phy_mode);
	if (!IS_ERR(phydev)) {
		phydev->adjust_link = sw_adjust_link;
		return phydev;
	}
	return NULL;
}

static int ksz_sw_init(struct dev_priv *priv)
{
	int i;
	int port_count;
	int dev_count;
	int mib_port_count;
	char dev_label[IFNAMSIZ];
	int phy_mode;
	char phy_id[MII_BUS_ID_SIZE];
	char bus_id[MII_BUS_ID_SIZE];
	struct ksz_sw *sw = NULL;

	sw = ksz_sw_check(0);
	if (!sw_is_switch(sw))
		return -ENIXO;

	priv->parent = sw->dev;

	port_count = 1;
	mib_port_count = 1;
	dev_count = 1;
	dev_label[0] = '\0';

	/* Call at the very beginning to setup the switch function. */
	sw->net_ops->get_state = get_priv_state;
	sw->net_ops->set_state = set_priv_state;
	sw->net_ops->get_priv_port = get_priv_port;
	sw->net_ops->get_ready = get_net_ready;
	sw->net_ops->setup_special(sw, &port_count, &mib_port_count,
		&dev_count);

	/* Save the base device name. */
	strlcpy(dev_label, priv->dev->name, IFNAMSIZ);

	/* Call for every created network device. */
	priv->phy_addr = sw->net_ops->setup_dev(sw, priv->dev,
		dev_label, &priv->port, i, port_count, mib_port_count);

	phy_mode = priv->phy_interface;
	snprintf(bus_id, MII_BUS_ID_SIZE, "sw.%d", sw_device_present);
	snprintf(phy_id, MII_BUS_ID_SIZE, PHY_ID_FMT, bus_id,
		priv->phy_addr);
	priv->phydev = phy_attach(priv->dev, phy_id, phy_mode);

	/* Only the main one needs to set adjust_link for configuration. */
	priv->phydev->adjust_link = sw_adjust_link;

	for (i = 1; i < dev_count; i++) {

		/* Create network device. */
		...

		priv = netdev_priv(dev);
		priv->dev = dev;

		/* Call for every created network device. */
		priv->phy_addr = sw->net_ops->setup_dev(sw, priv->dev,
			dev_label, &priv->port, i, port_count, mib_port_count);

		phy_mode = priv->phy_interface;
		snprintf(bus_id, MII_BUS_ID_SIZE, "sw.%d", sw_device_present);
		snprintf(phy_id, MII_BUS_ID_SIZE, PHY_ID_FMT, bus_id,
			priv->phy_addr);
		priv->phydev = phy_attach(priv->dev, phy_id, phy_mode);

		/* Register network device. */
		...
	}

	return 0;
}

int netdev_open(struct net_device *dev)
{
	struct dev_priv *priv = netdev_priv(dev);
	struct ksz_sw *sw = priv->port.sw;
	int rx_mode = 0;

	/* Call only once for the first and main device. */
	main_dev = priv->dev;
	rx_mode = sw->net_ops->open_dev(sw, main_dev, main_dev->dev_addr);
	sw->net_ops->open(sw);

	/* Call for every network device. */
	sw->net_ops->open_port(sw, &priv->port, &priv->state);
}

int netdev_close(struct net_device *dev);
{
	struct dev_priv *priv = netdev_priv(dev);
	struct ksz_sw *sw = priv->port.sw;

	/* Call for every network device. */
	sw->net_ops->close_port(sw, &priv->port);

	/* Call only once for the last and main device. */
	sw->net_ops->close(sw);
	sw->net_ops->stp(sw, true);
}


static int init_sysfs(struct net_device *netdev, struct ksz_sw_sysfs *sysfs,
	struct ksz_sw *sw)
{
	return init_sw_sysfs(sw, sysfs, &netdev->dev);
}

static void exit_sysfs(struct net_device *netdev, struct ksz_sw_sysfs *sysfs,
	struct ksz_sw *sw)
{
	exit_sw_sysfs(sw, sysfs, &netdev->dev);
}

