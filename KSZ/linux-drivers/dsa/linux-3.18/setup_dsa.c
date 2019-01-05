/**
 * Microchip tail tagging switch DSA setup code
 *
 * Copyright (c) 2015-2016 Microchip Technology Inc.
 * Copyright (c) 2012-2015 Micrel, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <net/dsa.h>


static struct dsa_chip_data ksz_switch_chip_data = {
	.port_names[0]	= "lan1",
	.port_names[1]	= "lan2",
	.port_names[2]	= "lan3",
	.port_names[3]	= "lan4",
	.port_names[4]	= "lan5",
	.port_names[5]	= "lan6",
	.port_names[6]	= "cpu",
};

static struct dsa_platform_data ksz_switch_plat_data = {
	.nr_chips	= 1,
	.chip		= &ksz_switch_chip_data,
};

static struct resource ksz_switch_resources[] = {
	{
		.start	= 0,
		.end	= 0,
		.flags	= IORESOURCE_IRQ,
	},
};

static struct platform_device ksz_switch_device = {
	.name		= "dsa",
	.id		= 0,
	.num_resources	= 0,
	.resource	= ksz_switch_resources,
};

void ksz_switch_init(struct dsa_platform_data *d, int irq,
	struct device *netdev, struct device *mii_bus_dev,
	struct ksz_sw *sw)
{
	int i;

	if (irq != NO_IRQ) {
		ksz_switch_resources[0].start = irq;
		ksz_switch_resources[0].end = irq;
		ksz_switch_device.num_resources = 1;
	}

	d->netdev = netdev;
	for (i = 0; i < d->nr_chips; i++)
		d->chip[i].host_dev = mii_bus_dev;
	ksz_switch_device.dev.platform_data = d;

	if (sw->port_cnt == sw->mib_port_cnt)
		i = sw->mib_port_cnt - 1;
	else
		i = sw->port_cnt;
	if (i > 6)
		i = 6;
	sw->dsa_port_cnt = i;
	strcpy(ksz_switch_chip_data.port_names[i], "cpu");
	while (i < 6)
		ksz_switch_chip_data.port_names[++i] = NULL;

	platform_device_register(&ksz_switch_device);
}

