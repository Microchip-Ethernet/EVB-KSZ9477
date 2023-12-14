// SPDX-License-Identifier: GPL-2.0
/*
 * Microchip KSZ9477 series register access through SPI
 *
 * Copyright (C) 2017-2019 Microchip Technology Inc.
 */

#include <asm/unaligned.h>

#include <linux/delay.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/regmap.h>
#include <linux/spi/spi.h>

#include "ksz_common.h"

#define SPI_ADDR_SHIFT			24
#define SPI_ADDR_ALIGN			3
#define SPI_TURNAROUND_SHIFT		5

KSZ_REGMAP_TABLE(ksz9477, 32, SPI_ADDR_SHIFT,
		 SPI_TURNAROUND_SHIFT, SPI_ADDR_ALIGN);

#ifndef CONFIG_OF

/* Choose one of switches. */
#if 1
#define CONFIG_KSZ_7_PORTS

/* Choose which port is host port. */
#if 1
#define CONFIG_KSZ_7_PORTS_HOST_6
#else
#define CONFIG_KSZ_7_PORTS_HOST_7
#endif
#endif
#if 0
#define CONFIG_KSZ_6_PORTS
#endif
#if 0
#define CONFIG_KSZ_3_PORTS
#endif

#if defined(CONFIG_KSZ_6_PORTS) || defined(CONFIG_KSZ_7_PORTS)
#if defined(CONFIG_KSZ_6_PORTS) || defined(CONFIG_KSZ_7_PORTS_HOST_6)
#define CONFIG_KSZ_HOST_PORT  5
#endif
#if defined(CONFIG_KSZ_7_PORTS) && defined(CONFIG_KSZ_7_PORTS_HOST_7)
#define CONFIG_KSZ_HOST_PORT  6
#endif

static struct dsa_chip_data ksz_dsa_chip_data = {
	.port_names[0]	= "lan1",
	.port_names[1]	= "lan2",
	.port_names[2]	= "lan3",
	.port_names[3]	= "lan4",
	.port_names[4]	= "lan5",
#if defined(CONFIG_KSZ_6_PORTS) || defined(CONFIG_KSZ_7_PORTS_HOST_6)
	.port_names[5]	= "cpu",
#endif
#if defined(CONFIG_KSZ_7_PORTS) && defined(CONFIG_KSZ_7_PORTS_HOST_6)
	.port_names[6]	= "lan6",
#endif
#if defined(CONFIG_KSZ_7_PORTS) && defined(CONFIG_KSZ_7_PORTS_HOST_7)
	.port_names[5]	= "lan6",
	.port_names[6]	= "cpu",
#endif
};
#endif
#ifdef CONFIG_KSZ_3_PORTS
#define CONFIG_KSZ_HOST_PORT  2
static struct dsa_chip_data ksz_dsa_chip_data = {
	.port_names[0]	= "lan1",
	.port_names[1]	= "lan2",
	.port_names[2]	= "cpu",
};
#endif
#endif

static int ksz9477_spi_probe(struct spi_device *spi)
{
	struct regmap_config rc;
	struct ksz_device *dev;
	int i, ret;

	dev = ksz_switch_alloc(&spi->dev, spi);
	if (!dev)
		return -ENOMEM;

#ifndef CONFIG_OF
	do {
		struct net_device *net;

		/* Network device needs to be exist. */
		net = dev_get_by_name(&init_net, "eth0");
		if (!net)
			return -EPROBE_DEFER;

		ksz_dsa_chip_data.netdev[CONFIG_KSZ_HOST_PORT] = &net->dev;
	} while (0);
	dev->ds->dev->platform_data = &ksz_dsa_chip_data;
#endif

	for (i = 0; i < ARRAY_SIZE(ksz9477_regmap_config); i++) {
		rc = ksz9477_regmap_config[i];
		rc.lock_arg = &dev->regmap_mutex;
		dev->regmap[i] = devm_regmap_init_spi(spi, &rc);
		if (IS_ERR(dev->regmap[i])) {
			ret = PTR_ERR(dev->regmap[i]);
			dev_err(&spi->dev,
				"Failed to initialize regmap%i: %d\n",
				ksz9477_regmap_config[i].val_bits, ret);
			return ret;
		}
	}

	if (spi->dev.platform_data)
		dev->pdata = spi->dev.platform_data;

	ret = ksz9477_switch_register(dev);

	/* Main DSA driver may not be started yet. */
	if (ret)
		return ret;

	spi_set_drvdata(spi, dev);

	return 0;
}

static int ksz9477_spi_remove(struct spi_device *spi)
{
	struct ksz_device *dev = spi_get_drvdata(spi);

	if (dev)
		ksz_switch_remove(dev);

	spi_set_drvdata(spi, NULL);

	return 0;
}

static void ksz9477_spi_shutdown(struct spi_device *spi)
{
	struct ksz_device *dev = spi_get_drvdata(spi);

	if (dev)
		dsa_switch_shutdown(dev->ds);

	spi_set_drvdata(spi, NULL);
}

static const struct of_device_id ksz9477_dt_ids[] = {
	{ .compatible = "microchip,ksz9477" },
	{ .compatible = "microchip,ksz9897" },
	{ .compatible = "microchip,ksz9893" },
	{ .compatible = "microchip,ksz9563" },
	{ .compatible = "microchip,ksz8563" },
	{ .compatible = "microchip,ksz9567" },
	{ .compatible = "microchip,ksz8567" },
	{ .compatible = "microchip,ksz8565" },
	{ .compatible = "microchip,ksz9656" },
	{},
};
MODULE_DEVICE_TABLE(of, ksz9477_dt_ids);

static const struct spi_device_id ksz9477_spi_ids[] = {
	{ "ksz9477" },
	{ "ksz9897" },
	{ "ksz9893" },
	{ "ksz9563" },
	{ "ksz8563" },
	{ "ksz9567" },
	{ "ksz8567" },
	{ "ksz8565" },
	{ "ksz9656" },
	{ },
};
MODULE_DEVICE_TABLE(spi, ksz9477_spi_ids);

static struct spi_driver ksz9477_spi_driver = {
	.driver = {
		.name	= "ksz9477-switch",
		.owner	= THIS_MODULE,
		.of_match_table = of_match_ptr(ksz9477_dt_ids),
	},
	.id_table = ksz9477_spi_ids,
	.probe	= ksz9477_spi_probe,
	.remove	= ksz9477_spi_remove,
	.shutdown = ksz9477_spi_shutdown,
};

module_spi_driver(ksz9477_spi_driver);

MODULE_ALIAS("spi:ksz9477");
MODULE_ALIAS("spi:ksz9897");
MODULE_ALIAS("spi:ksz9893");
MODULE_ALIAS("spi:ksz9563");
MODULE_ALIAS("spi:ksz8563");
MODULE_ALIAS("spi:ksz9567");
MODULE_ALIAS("spi:ksz8567");
MODULE_ALIAS("spi:ksz8565");
MODULE_ALIAS("spi:ksz9656");
MODULE_AUTHOR("Woojung Huh <Woojung.Huh@microchip.com>");
MODULE_DESCRIPTION("Microchip KSZ9477 Series Switch SPI access Driver");
MODULE_LICENSE("GPL");
