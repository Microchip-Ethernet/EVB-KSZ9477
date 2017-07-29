/**
 * Microchip tail tagging switch DSA driver
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
	struct mii_bus *bus = dsa_host_dev_to_mii_bus(ds->master_dev);

	if (bus == NULL)
		return -EINVAL;

	++addr;
	return mdiobus_read(bus, ds->pd->sw_addr + addr, reg);
}

static int ksz_dsa_reg_write(struct dsa_switch *ds, int addr, int reg, u16 val)
{
	struct mii_bus *bus = dsa_host_dev_to_mii_bus(ds->master_dev);

	if (bus == NULL)
		return -EINVAL;

	++addr;
	return mdiobus_write(bus, ds->pd->sw_addr + addr, reg, val);
}

static struct ksz_sw *get_sw_ptr(struct device *host_dev)
{
	struct mii_bus *bus = dsa_host_dev_to_mii_bus(host_dev);
	struct ksz_sw *sw = NULL;

	if (bus) {
		struct phy_device *phydev;
		struct phy_priv *phydata;

		phydev = bus->phy_map[0];
		if (phydev) {
			phydata = phydev->priv;
			if (phydata)
				sw = phydata->port->sw;
		}
	}
	return sw;
}

static char *ksz_dsa_probe(struct device *host_dev, int sw_addr)
{
	u8 id1;
	u8 id2;
	int id;
	char dev_name[20];
	static char switch_name[80];
	struct ksz_sw *sw = get_sw_ptr(host_dev);

	dev_name[0] = '\0';
	switch_name[0] = '\0';
	if (!sw)
		return switch_name;

	sw->ops->acquire(sw);
	id = sw->ops->get_id(sw, &id1, &id2, dev_name);
	sw->ops->release(sw);
	strncpy(switch_name, "Microchip KSZ", sizeof(switch_name));
	strcat(switch_name, dev_name);
	if (!switch_name[13])
		return NULL;
	return switch_name;
}

static int ksz_dsa_switch_reset(struct dsa_switch *ds)
{
	struct ksz_sw *sw = get_sw_ptr(ds->master_dev);

	if (!sw)
		return -EINVAL;

	sw->ops->acquire(sw);
	sw_reset(sw);
	sw_init(sw);
	sw_setup(sw);
	sw_enable(sw);
	sw_ena_intr(sw);
	sw->ops->release(sw);

	return 0;
}

static int ksz_dsa_setup_global(struct dsa_switch *ds)
{
	struct ksz_sw *sw = get_sw_ptr(ds->master_dev);

	if (!sw)
		return -EINVAL;

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
	struct ksz_sw *sw = get_sw_ptr(ds->master_dev);

	if (!sw)
		return -EINVAL;

	sw->ops->acquire(sw);
	sw->ops->cfg_each_port(sw, p, dsa_is_cpu_port(ds, p));
	sw->ops->release(sw);

	return 0;
}

static int ksz_dsa_setup(struct dsa_switch *ds)
{
	int i;
	int ret;
	struct ksz_sw *sw = get_sw_ptr(ds->master_dev);

	if (!sw)
		return -EINVAL;

	ret = ksz_dsa_switch_reset(ds);
	if (ret < 0)
		return ret;

	ret = ksz_dsa_setup_global(ds);
	if (ret < 0)
		return ret;

	for (i = 0; i <= sw->dsa_port_cnt; i++) {
		ret = ksz_dsa_setup_port(ds, i);
		if (ret < 0)
			return ret;
	}

	return 0;
}

static int ksz_dsa_set_addr(struct dsa_switch *ds, u8 *addr)
{
	int port;
	struct ksz_sw *sw = get_sw_ptr(ds->master_dev);

	if (!sw)
		return -EINVAL;

	sw->ops->acquire(sw);
	sw_set_addr(sw, addr);
	for (port = 0; port < sw->dsa_port_cnt; port++) {
		sw->ops->set_port_addr(sw, port, addr);
	}
	sw->ops->release(sw);

	return 0;
}

static int ksz_dsa_phy_read(struct dsa_switch *ds, int port, int regnum)
{
	int addr;
	struct ksz_sw *sw = get_sw_ptr(ds->master_dev);

	if (!sw)
		return 0xffff;

	addr = sw->ops->port_to_phy_addr(sw, port);
	if (addr == -1)
		return 0xffff;

	return ksz_dsa_reg_read(ds, addr, regnum);
}

static int
ksz_dsa_phy_write(struct dsa_switch *ds, int port, int regnum, u16 val)
{
	int addr;
	struct ksz_sw *sw = get_sw_ptr(ds->master_dev);

	if (!sw)
		return 0xffff;

	addr = sw->ops->port_to_phy_addr(sw, port);
	if (addr == -1)
		return 0xffff;

	return ksz_dsa_reg_write(ds, addr, regnum, val);
}

static void ksz_dsa_poll_link(struct dsa_switch *ds)
{
	int i;
	struct ksz_port_info *info;
	struct ksz_sw *sw = get_sw_ptr(ds->master_dev);

	if (!sw)
		return;
	for (i = 0; i < sw->dsa_port_cnt; i++) {
		struct net_device *dev;
		int link;
		int speed;
		int duplex;
		int fc;
		int p = 0;

		dev = ds->ports[i];
		if (dev == NULL)
			continue;

		if (sw->ops->get_first_port)
			p = sw->ops->get_first_port(sw);
		info = &sw->port_info[i + p];
		link = 0;
		if (dev->flags & IFF_UP)
			link = (info->state == media_connected);

		if (!link) {
			if (netif_carrier_ok(dev)) {
				netdev_info(dev, "link down\n");
				netif_carrier_off(dev);
			}
			continue;
		}

		speed = info->tx_rate / TX_RATE_UNIT;
		duplex = (info->duplex == 2);
		fc = (info->flow_ctrl & 3) == 3;

		if (!netif_carrier_ok(dev)) {
			netdev_info(dev,
				    "link up, %d Mb/s, %s duplex, "
				    "flow control %sabled\n",
				    speed, duplex ? "full" : "half",
				    fc ? "en" : "dis");
			netif_carrier_on(dev);
		}
	}
}

static struct dsa_switch_driver micrel_switch_driver = {
	.tag_protocol	= DSA_TAG_PROTO_TRAILER,
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

