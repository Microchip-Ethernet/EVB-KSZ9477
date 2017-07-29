/**
 * Micrel tail tagging switch DSA driver
 *
 * Copyright (c) 2015-2016 Microchip Technology Inc.
 * Copyright (c) 2012-2015 Micrel, Inc.
 * Copyright (c) 2008-2009 Marvell Semiconductor
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <linux/list.h>
#include <linux/module.h>
#include <linux/netdevice.h>
#include <linux/phy.h>
#include <net/dsa.h>

static int ksz_dsa_reg_read(struct dsa_switch *ds, int addr, int reg)
{
	++addr;
	return mdiobus_read(ds->master_mii_bus, ds->pd->sw_addr + addr, reg);
}

static int ksz_dsa_reg_write(struct dsa_switch *ds, int addr, int reg, u16 val)
{
	++addr;
	return mdiobus_write(ds->master_mii_bus, ds->pd->sw_addr + addr,
			     reg, val);
}

#define FAMILY_ID_87			0x87
#define CHIP_ID_8794			0x60
#define CHIP_ID_8795			0x90

#define FAMILY_ID_88			0x88
#define CHIP_ID_8863_MLI		0x30

#define FAMILY_ID_84			0x84
#define CHIP_ID_8463_MLI		0x40
#define CHIP_ID_8463_RLI		0x50

#define FAMILY_ID_85			0x85
#define FAMILY_ID_95			0x95
#define CHIP_ID_9567_RNX		0x67
#define CHIP_ID_9566_RNX		0x66

#define FAMILY_ID_88			0x88
#define FAMILY_ID_98			0x98
#define CHIP_ID_9893_RNX		0x93

static char *ksz_dsa_probe(struct mii_bus *bus, int sw_addr)
{
	struct phy_device *phydev = bus->phy_map[0];
	struct phy_priv *phydata = phydev->priv;
	struct ksz_sw *sw = phydata->port.sw;
	u8 id1;
	u8 id2;
	int id;
	static char switch_name[80];

	sw->ops->acquire(sw);
	id = sw->ops->get_id(sw, &id1, &id2);
	sw->ops->release(sw);
	strncpy(switch_name, "Micrel KSZ", sizeof(switch_name));
	switch (id1) {
	case FAMILY_ID_87:
		strcat(switch_name, "87");
		switch (id2) {
		case CHIP_ID_8794:
			strcat(switch_name, "94CNX");
			break;
		case CHIP_ID_8795:
			strcat(switch_name, "95CLX");
			break;
		}
		break;
	case FAMILY_ID_88:
		strcat(switch_name, "88");
		switch (id2) {
		case CHIP_ID_8863_MLI:
			strcat(switch_name, "63MLI");
			break;
#if 0
		case CHIP_ID_8873_MLI:
			strcat(switch_name, "73MLI");
			break;
#endif
		}
		break;
	case FAMILY_ID_84:
		strcat(switch_name, "84");
		switch (id2) {
		case CHIP_ID_8463_MLI:
			strcat(switch_name, "63MLI");
			break;
		case CHIP_ID_8463_RLI:
			strcat(switch_name, "63RLI");
			break;
		}
		break;
	case FAMILY_ID_95:
		strcat(switch_name, "95");
		switch (id2) {
		case CHIP_ID_9567_RNX:
			strcat(switch_name, "67RNX");
			break;
		case CHIP_ID_9566_RNX:
			strcat(switch_name, "66RNX");
			break;
		case CHIP_ID_9893_RNX:
			strcat(switch_name, "63RNX");
			break;
		}
		break;
	case FAMILY_ID_98:
	case 0x64:
		strcat(switch_name, "98");
		switch (id2) {
		case CHIP_ID_9567_RNX:
			strcat(switch_name, "97RNX");
			break;
		case CHIP_ID_9566_RNX:
			strcat(switch_name, "96RNX");
			break;
		case CHIP_ID_9893_RNX:
			strcat(switch_name, "93RNX");
			break;
		}
		break;
	}
	if (!switch_name[10])
		return NULL;
	return switch_name;
}

static int ksz_dsa_switch_reset(struct dsa_switch *ds)
{
	struct phy_device *phydev = ds->master_mii_bus->phy_map[0];
	struct phy_priv *phydata = phydev->priv;
	struct ksz_sw *sw = phydata->port.sw;

	sw->ops->acquire(sw);
	sw_reset(sw);
	sw_init(sw);
	sw_ena_intr(sw);
	sw->ops->release(sw);

	return 0;
}

static int ksz_dsa_setup_global(struct dsa_switch *ds)
{
	struct phy_device *phydev = ds->master_mii_bus->phy_map[0];
	struct phy_priv *phydata = phydev->priv;
	struct ksz_sw *sw = phydata->port.sw;

	sw->ops->acquire(sw);
	sw->features |= DSA_SUPPORT;
	if (!(sw->overrides & TAIL_TAGGING)) {
		sw->ops->cfg_tail_tag(sw, 1);
		sw->overrides |= TAIL_TAGGING;
	}
	sw->ops->release(sw);

	return 0;
}

static int ksz_dsa_setup_port(struct dsa_switch *ds, int p)
{
	struct phy_device *phydev = ds->master_mii_bus->phy_map[0];
	struct phy_priv *phydata = phydev->priv;
	struct ksz_sw *sw = phydata->port.sw;

	if (p == sw->port_cnt)
		return 0;
	sw->ops->acquire(sw);
	sw->ops->cfg_each_port(sw, p, dsa_is_cpu_port(ds, p));
	port_set_stp_state(sw, p, STP_STATE_SIMPLE);
	sw->ops->release(sw);

	return 0;
}

static int ksz_dsa_setup(struct dsa_switch *ds)
{
	int i;
	int ret;

	ret = ksz_dsa_switch_reset(ds);
	if (ret < 0)
		return ret;

	ret = ksz_dsa_setup_global(ds);
	if (ret < 0)
		return ret;

	for (i = 0; i < TOTAL_PORT_NUM; i++) {
		ret = ksz_dsa_setup_port(ds, i);
		if (ret < 0)
			return ret;
	}

	return 0;
}

static int ksz_dsa_set_addr(struct dsa_switch *ds, u8 *addr)
{
	struct phy_device *phydev = ds->master_mii_bus->phy_map[0];
	struct phy_priv *phydata = phydev->priv;
	struct ksz_sw *sw = phydata->port.sw;
	int port;

	sw->ops->acquire(sw);
	sw_set_addr(sw, addr);
	for (port = 0; port < SWITCH_PORT_NUM; port++) {
		if (port == sw->port_cnt)
			continue;
		sw->ops->set_port_addr(sw, port, addr);
	}
	sw->ops->release(sw);

	return 0;
}

static int ksz_dsa_phy_read(struct dsa_switch *ds, int port, int regnum)
{
	struct phy_device *phydev = ds->master_mii_bus->phy_map[0];
	struct phy_priv *phydata = phydev->priv;
	struct ksz_sw *sw = phydata->port.sw;
	int addr;

	addr = sw->ops->port_to_phy_addr(sw, port);
	if (addr == -1)
		return 0xffff;

	return ksz_dsa_reg_read(ds, addr, regnum);
}

static int
ksz_dsa_phy_write(struct dsa_switch *ds, int port, int regnum, u16 val)
{
	struct phy_device *phydev = ds->master_mii_bus->phy_map[0];
	struct phy_priv *phydata = phydev->priv;
	struct ksz_sw *sw = phydata->port.sw;
	int addr;

	addr = sw->ops->port_to_phy_addr(sw, port);
	if (addr == -1)
		return 0xffff;

	return ksz_dsa_reg_write(ds, addr, regnum, val);
}

static void ksz_dsa_poll_link(struct dsa_switch *ds)
{
	int i;
	struct phy_device *phydev = ds->master_mii_bus->phy_map[0];
	struct phy_priv *phydata = phydev->priv;
	struct ksz_sw *sw = phydata->port.sw;
	struct ksz_port_info *info;

	for (i = 0; i < SWITCH_PORT_NUM; i++) {
		struct net_device *dev;
		int link;
		int speed;
		int duplex;
		int fc;

		dev = ds->ports[i];
		if (dev == NULL)
			continue;

		info = &sw->port_info[i];
		link = 0;
		if (dev->flags & IFF_UP)
			link = (info->state == media_connected);

		if (!link) {
			if (netif_carrier_ok(dev)) {
				printk(KERN_INFO "%s: link down\n", dev->name);
				netif_carrier_off(dev);
			}
			continue;
		}

		speed = info->tx_rate / TX_RATE_UNIT;
		duplex = (info->duplex == 2);
		fc = (info->flow_ctrl & 3) == 3;

		if (!netif_carrier_ok(dev)) {
			printk(KERN_INFO "%s: link up, %d Mb/s, %s duplex, "
					 "flow control %sabled\n", dev->name,
					 speed, duplex ? "full" : "half",
					 fc ? "en" : "dis");
			netif_carrier_on(dev);
		}
	}
}

static struct dsa_switch_driver micrel_switch_driver = {
	.tag_protocol	= htons(ETH_P_TRAILER),
	.probe		= ksz_dsa_probe,
	.setup		= ksz_dsa_setup,
	.set_addr	= ksz_dsa_set_addr,
	.phy_read	= ksz_dsa_phy_read,
	.phy_write	= ksz_dsa_phy_write,
	.poll_link	= ksz_dsa_poll_link,
};

static int ksz_dsa_init(void)
{
	register_switch_driver(&micrel_switch_driver);
	return 0;
}

static void ksz_dsa_cleanup(void)
{
	unregister_switch_driver(&micrel_switch_driver);
}

