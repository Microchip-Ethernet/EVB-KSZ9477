// SPDX-License-Identifier: GPL-2.0
/*
 * Microchip KSZ9477 series register access through I2C
 *
 * Copyright (C) 2018-2019 Microchip Technology Inc.
 */

#include <linux/i2c.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/regmap.h>

#include "ksz_common.h"

KSZ_REGMAP_TABLE(ksz9477, not_used, 16, 0, 0);

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

static int ksz9477_i2c_probe(struct i2c_client *i2c,
			     const struct i2c_device_id *i2c_id)
{
	struct regmap_config rc;
	struct ksz_device *dev;
	int i, ret;

	dev = ksz_switch_alloc(&i2c->dev, i2c);
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
		dev->regmap[i] = devm_regmap_init_i2c(i2c, &rc);
		if (IS_ERR(dev->regmap[i])) {
			ret = PTR_ERR(dev->regmap[i]);
			dev_err(&i2c->dev,
				"Failed to initialize regmap%i: %d\n",
				ksz9477_regmap_config[i].val_bits, ret);
			return ret;
		}
	}

	if (i2c->dev.platform_data)
		dev->pdata = i2c->dev.platform_data;

	ret = ksz9477_switch_register(dev);

	/* Main DSA driver may not be started yet. */
	if (ret)
		return ret;

	i2c_set_clientdata(i2c, dev);

	return 0;
}

static int ksz9477_i2c_remove(struct i2c_client *i2c)
{
	struct ksz_device *dev = i2c_get_clientdata(i2c);

	if (dev)
		ksz_switch_remove(dev);

	i2c_set_clientdata(i2c, NULL);

	return 0;
}

static void ksz9477_i2c_shutdown(struct i2c_client *i2c)
{
	struct ksz_device *dev = i2c_get_clientdata(i2c);

	if (!dev)
		return;

	if (dev->dev_ops->shutdown)
		dev->dev_ops->shutdown(dev);

	dsa_switch_shutdown(dev->ds);

	i2c_set_clientdata(i2c, NULL);
}

static const struct i2c_device_id ksz9477_i2c_id[] = {
	{ "ksz9477-switch", 0 },
	{},
};

MODULE_DEVICE_TABLE(i2c, ksz9477_i2c_id);

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

static struct i2c_driver ksz9477_i2c_driver = {
	.driver = {
		.name	= "ksz9477-switch",
		.of_match_table = of_match_ptr(ksz9477_dt_ids),
	},
	.probe	= ksz9477_i2c_probe,
	.remove	= ksz9477_i2c_remove,
	.shutdown = ksz9477_i2c_shutdown,
	.id_table = ksz9477_i2c_id,
};

module_i2c_driver(ksz9477_i2c_driver);

MODULE_AUTHOR("Tristram Ha <Tristram.Ha@microchip.com>");
MODULE_DESCRIPTION("Microchip KSZ9477 Series Switch I2C access Driver");
MODULE_LICENSE("GPL v2");
