// SPDX-License-Identifier: GPL-2.0
/*
 * Microchip KSZ8895 series register access through SPI
 *
 * Copyright (C) 2017-2019 Microchip Technology Inc.
 *	Tristram Ha <Tristram.Ha@microchip.com>
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/spi/spi.h>

#include "ksz_priv.h"

/* SPI frame opcodes */
#define KS_SPIOP_RD			3
#define KS_SPIOP_WR			2

#define SPI_CMD_LEN			2
#define REG_SIZE			0x100

#define SPI_REGMAP_VAL			8
#define SPI_REGMAP_REG			(SPI_CMD_LEN * SPI_REGMAP_VAL)

#define KSZ_REGMAP_COMMON(n, width)					\
{									\
	.name			= n,					\
	.max_register		= REG_SIZE - (width),			\
	.reg_bits 		= SPI_REGMAP_REG,			\
	.val_bits		= SPI_REGMAP_VAL * (width),		\
	.reg_stride		= (width),				\
	.read_flag_mask		= KS_SPIOP_RD,				\
	.write_flag_mask	= KS_SPIOP_WR,				\
	.reg_format_endian	= REGMAP_ENDIAN_BIG,			\
	.val_format_endian	= REGMAP_ENDIAN_BIG,			\
}

static const struct regmap_config ksz8895_regmap_cfg[] = {
	KSZ_REGMAP_COMMON("8", 1),
	KSZ_REGMAP_COMMON("16", 2),
	KSZ_REGMAP_COMMON("32", 4),
};

static int ksz8895_spi_probe(struct spi_device *spi)
{
	struct ksz_device *dev;
	int i;
	int ret;

	dev = ksz_switch_alloc(&spi->dev);
	if (!dev)
		return -ENOMEM;

	for (i = 0; i < ARRAY_SIZE(ksz8895_regmap_cfg); i++) {
		dev->regmap[i] = devm_regmap_init_spi(spi,
						      &ksz8895_regmap_cfg[i]);
		if (IS_ERR(dev->regmap[i]))
			return PTR_ERR(dev->regmap[i]);
	}

	if (spi->dev.platform_data)
		dev->pdata = spi->dev.platform_data;

	ret = ksz8895_switch_register(dev);

	/* Main DSA driver may not be started yet. */
	if (ret)
		return ret;

	spi_set_drvdata(spi, dev);

	return 0;
}

static int ksz8895_spi_remove(struct spi_device *spi)
{
	struct ksz_device *dev = spi_get_drvdata(spi);

	if (dev)
		ksz_switch_remove(dev);

	return 0;
}

static void ksz8895_spi_shutdown(struct spi_device *spi)
{
	struct ksz_device *dev = spi_get_drvdata(spi);

	if (dev && dev->dev_ops->shutdown)
		dev->dev_ops->shutdown(dev);
}

static const struct of_device_id ksz8895_dt_ids[] = {
	{ .compatible = "microchip,ksz8895" },
	{ .compatible = "microchip,ksz8864" },
	{},
};
MODULE_DEVICE_TABLE(of, ksz8895_dt_ids);

static struct spi_driver ksz8895_spi_driver = {
	.driver = {
		.name	= "ksz8895-switch",
		.owner	= THIS_MODULE,
		.of_match_table = of_match_ptr(ksz8895_dt_ids),
	},
	.probe	= ksz8895_spi_probe,
	.remove	= ksz8895_spi_remove,
	.shutdown = ksz8895_spi_shutdown,
};

module_spi_driver(ksz8895_spi_driver);

MODULE_AUTHOR("Tristram Ha <Tristram.Ha@microchip.com>");
MODULE_DESCRIPTION("Microchip KSZ8895 Series Switch SPI Driver");
MODULE_LICENSE("GPL v2");
