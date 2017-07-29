
#if defined(CONFIG_MICREL_SWITCH) || defined(CONFIG_NET_DSA_TAG_TAIL)
#define HAVE_MICREL_SWITCH
#endif


#if defined(CONFIG_MICREL_SWITCH_EMBEDDED)
#include <linux/of.h>
#endif
#if defined(CONFIG_MICREL_KSZ8795_EMBEDDED)
#include "spi-ksz8795.c"
#elif defined(CONFIG_HAVE_KSZ8795)
#include "ksz_cfg_8795.h"
#endif

#ifdef HAVE_MICREL_SWITCH
static inline int sw_is_switch(struct ksz_sw *sw)
{
	return sw != NULL;
}
#endif


#if defined(HAVE_MICREL_SWITCH) && !defined(CONFIG_MICREL_SWITCH_EMBEDDED)
#include <linux/spi/spi.h>

#include "ksz_sw_phy.h"
#ifndef HAVE_MICREL_SWITCH
#define SKIP_MICREL_SWITCH_SYSFS
#endif
#include "ksz_spi_net.h"
#endif


#if defined(CONFIG_MICREL_SWITCH) && !defined(CONFIG_MICREL_SWITCH_EMBEDDED)

#define USE_MIB
#include "ksz_sw_sysfs_8795.c"
#endif


static int sw_device_present;

static struct ksz_sw *micrel_sw_check(int id)
{
	int phy_mode;
	char phy_id[MII_BUS_ID_SIZE];
	char bus_id[MII_BUS_ID_SIZE];
	struct net_device netdev;
	struct phy_device *phydev;
	struct ksz_sw *sw = NULL;

	/* Check whether MII switch exists. */
	phy_mode = PHY_INTERFACE_MODE_MII;
	snprintf(bus_id, MII_BUS_ID_SIZE, "sw.%d", id);
	snprintf(phy_id, MII_BUS_ID_SIZE, PHY_ID_FMT, bus_id, 0);
	phydev = phy_attach(&netdev, phy_id, 0, phy_mode);
	if (!IS_ERR(phydev)) {
		struct phy_priv *phydata = phydev->priv;

		sw = phydata->port.sw;
		phy_detach(phydev);
	}
	return sw;
}

static void sw_adjust_link(struct net_device *netdev)
{
}

static struct phy_device *micrel_sw_attach(struct net_device *netdev)
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

