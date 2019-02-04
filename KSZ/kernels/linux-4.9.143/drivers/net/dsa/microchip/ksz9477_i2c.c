// SPDX-License-Identifier: GPL-2.0
/*
 * Microchip KSZ9477 series register access through I2C
 *
 * Copyright (C) 2018-2019 Microchip Technology Inc.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/i2c.h>

#include "ksz_priv.h"

#define REG_SIZE			0x8000

#define I2C_REGMAP_VAL			8
#define I2C_REGMAP_REG			16

#define KSZ_REGMAP_COMMON(n, width)					\
{									\
	.name			= n,					\
	.max_register		= REG_SIZE - (width),			\
	.reg_bits 		= I2C_REGMAP_REG,			\
	.val_bits		= I2C_REGMAP_VAL * (width),		\
	.reg_stride		= (width),				\
	.reg_format_endian	= REGMAP_ENDIAN_BIG,			\
	.val_format_endian	= REGMAP_ENDIAN_BIG,			\
}

static const struct regmap_config ksz9477_regmap_cfg[] = {
	KSZ_REGMAP_COMMON("8", 1),
	KSZ_REGMAP_COMMON("16", 2),
	KSZ_REGMAP_COMMON("32", 4),
};

static int ksz9477_i2c_probe(struct i2c_client *i2c,
			     const struct i2c_device_id *i2c_id)
{
	struct ksz_device *dev;
	int i;
	int ret;

	dev = ksz_switch_alloc(&i2c->dev);
	if (!dev)
		return -ENOMEM;

	for (i = 0; i < ARRAY_SIZE(ksz9477_regmap_cfg); i++) {
		dev->regmap[i] = devm_regmap_init_i2c(i2c,
						      &ksz9477_regmap_cfg[i]);
		if (IS_ERR(dev->regmap[i]))
			return PTR_ERR(dev->regmap[i]);
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

	return 0;
}

static void ksz9477_i2c_shutdown(struct i2c_client *i2c)
{
	struct ksz_device *dev = i2c_get_clientdata(i2c);

	if (dev && dev->dev_ops->shutdown)
		dev->dev_ops->shutdown(dev);
}

static const struct i2c_device_id ksz9477_i2c_id[] = {
	{ "ksz9477-switch", 0 },
	{},
};

MODULE_DEVICE_TABLE(i2c, ksz9477_i2c_id);

static const struct of_device_id ksz9477_dt_ids[] = {
	{ .compatible = "microchip,ksz9477" },
	{ .compatible = "microchip,ksz9897" },
	{ .compatible = "microchip,ksz9896" },
	{ .compatible = "microchip,ksz9567" },
	{ .compatible = "microchip,ksz8565" },
	{ .compatible = "microchip,ksz9893" },
	{ .compatible = "microchip,ksz9563" },
	{},
};
MODULE_DEVICE_TABLE(of, ksz9477_dt_ids);

static struct i2c_driver ksz9477_i2c_driver = {
	.driver = {
		.name	= "ksz9477-switch",
		.owner	= THIS_MODULE,
		.of_match_table = of_match_ptr(ksz9477_dt_ids),
	},
	.probe	= ksz9477_i2c_probe,
	.remove	= ksz9477_i2c_remove,
	.shutdown = ksz9477_i2c_shutdown,
	.id_table = ksz9477_i2c_id,
};

module_i2c_driver(ksz9477_i2c_driver);

MODULE_AUTHOR("Tristram Ha <Tristram.Ha@microchip.com>");
MODULE_DESCRIPTION("Microchip KSZ9477 Series Switch I2C Driver");
MODULE_LICENSE("GPL v2");
