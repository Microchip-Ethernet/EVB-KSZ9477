// SPDX-License-Identifier: GPL-2.0
/*
 * Microchip KSZ8463 series register access through SPI
 *
 * Copyright (C) 2019 Microchip Technology Inc.
 *	Tristram Ha <Tristram.Ha@microchip.com>
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/spi/spi.h>

#include "ksz_priv.h"

/* SPI frame opcodes */
#define KS_SPIOP_RD			0
#define KS_SPIOP_WR			1

#define SPI_ADDR_S			13
#define SPI_ADDR_M			(BIT(SPI_ADDR_S) - 1)
#define SPI_TURNAROUND_S		2

#define SPI_CMD_LEN			2
#define REG_SIZE			0x800

#define SPI_REGMAP_PAD			SPI_TURNAROUND_S
#define SPI_REGMAP_VAL			8
#define SPI_REGMAP_REG			\
	(SPI_CMD_LEN * SPI_REGMAP_VAL - SPI_TURNAROUND_S)
#define SPI_REGMAP_MASK_S		\
	(SPI_ADDR_S + SPI_TURNAROUND_S - \
	(SPI_CMD_LEN * SPI_REGMAP_VAL - 8))

#define KSZ_REGMAP_COMMON(n, width)					\
{									\
	.name			= n,					\
	.max_register		= REG_SIZE - (width),			\
	.reg_bits 		= SPI_REGMAP_REG,			\
	.val_bits		= SPI_REGMAP_VAL * (width),		\
	.pad_bits		= SPI_REGMAP_PAD,			\
	.reg_stride		= (width),				\
	.read_flag_mask		= KS_SPIOP_RD << SPI_REGMAP_MASK_S,	\
	.write_flag_mask	= KS_SPIOP_WR << SPI_REGMAP_MASK_S,	\
	.reg_format_endian	= REGMAP_ENDIAN_BIG,			\
	.val_format_endian	= REGMAP_ENDIAN_BIG,			\
}

static const struct regmap_config ksz8463_regmap_cfg[] = {
	KSZ_REGMAP_COMMON("8", 1),
	KSZ_REGMAP_COMMON("16", 2),
	KSZ_REGMAP_COMMON("32", 4),
};

static int ksz8463_spi_probe(struct spi_device *spi)
{
	struct ksz_device *dev;
	int i;
	int ret;

	dev = ksz_switch_alloc(&spi->dev);
	if (!dev)
		return -ENOMEM;

	for (i = 0; i < ARRAY_SIZE(ksz8463_regmap_cfg); i++) {
		dev->regmap[i] = devm_regmap_init_spi(spi,
						      &ksz8463_regmap_cfg[i]);
		if (IS_ERR(dev->regmap[i]))
			return PTR_ERR(dev->regmap[i]);
	}

	if (spi->dev.platform_data)
		dev->pdata = spi->dev.platform_data;

	ret = ksz8463_switch_register(dev);

	/* Main DSA driver may not be started yet. */
	if (ret)
		return ret;

	spi_set_drvdata(spi, dev);

	return 0;
}

static int ksz8463_spi_remove(struct spi_device *spi)
{
	struct ksz_device *dev = spi_get_drvdata(spi);

	if (dev)
		ksz_switch_remove(dev);

	return 0;
}

static void ksz8463_spi_shutdown(struct spi_device *spi)
{
	struct ksz_device *dev = spi_get_drvdata(spi);

	if (dev && dev->dev_ops->shutdown)
		dev->dev_ops->shutdown(dev);
}

static const struct of_device_id ksz8463_dt_ids[] = {
	{ .compatible = "microchip,ksz8463" },
	{},
};
MODULE_DEVICE_TABLE(of, ksz8463_dt_ids);

static struct spi_driver ksz8463_spi_driver = {
	.driver = {
		.name	= "ksz8463-switch",
		.owner	= THIS_MODULE,
		.of_match_table = of_match_ptr(ksz8463_dt_ids),
	},
	.probe	= ksz8463_spi_probe,
	.remove	= ksz8463_spi_remove,
	.shutdown = ksz8463_spi_shutdown,
};

module_spi_driver(ksz8463_spi_driver);

MODULE_AUTHOR("Tristram Ha <Tristram.Ha@microchip.com>");
MODULE_DESCRIPTION("Microchip KSZ8463 Series Switch SPI Driver");
MODULE_LICENSE("GPL v2");
