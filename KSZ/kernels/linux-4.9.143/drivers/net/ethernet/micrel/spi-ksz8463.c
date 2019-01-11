/**
 * Microchip KSZ8463 SPI driver
 *
 * Copyright (c) 2015-2019 Microchip Technology Inc.
 * Copyright (c) 2010-2015 Micrel, Inc.
 *
 * Copyright 2009 Simtec Electronics
 *	http://www.simtec.co.uk/
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#if 0
#define DEBUG
#define DBG
#define DEBUG_MSG
#endif

#ifndef CONFIG_KSZ_SWITCH_EMBEDDED
#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/interrupt.h>
#include <linux/of.h>
#include <linux/phy.h>
#include <linux/platform_device.h>
#include <linux/sched.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/ethtool.h>
#include <linux/cache.h>
#include <linux/crc32.h>
#include <linux/if_vlan.h>
#include <linux/ip.h>
#include <net/ip.h>
#include <net/ipv6.h>
#endif

/* -------------------------------------------------------------------------- */

#include <linux/net_tstamp.h>
#include <linux/spi/spi.h>
#include <linux/debugfs.h>
#include <linux/seq_file.h>

#include "ksz_cfg_8463.h"


#define KS8463MLI_DEV0			"ksz8463"
#define KS8463MLI_DEV2			"ksz8463_2"

#define SW_DRV_RELDATE			"Jan 11, 2019"
#define SW_DRV_VERSION			"1.2.0"

/* -------------------------------------------------------------------------- */

#define HW_R(ks, reg)		spi_rdreg16(ks, reg)
#define HW_W(ks, reg, val)	spi_wrreg16(ks, reg, val)
#define HW_R8(ks, reg)		spi_rdreg8(ks, reg)
#define HW_W8(ks, reg, val)	spi_wrreg8(ks, reg, val)
#define HW_R16(ks, reg)		spi_rdreg16(ks, reg)
#define HW_W16(ks, reg, val)	spi_wrreg16(ks, reg, val)
#define HW_R32(ks, reg)		spi_rdreg32(ks, reg)
#define HW_W32(ks, reg, val)	spi_wrreg32(ks, reg, val)

#include "ksz_spi_net.h"

/* -------------------------------------------------------------------------- */

#define SPI_BYTE_ENABLE_S		4
#define SPI_ADDR_ENABLE_S		2
#define SPI_ADDR_S			11
#define SPI_ADDR_M			((1 << SPI_ADDR_S) - 1)
#define SPI_TURNAROUND_S		2

#define MK_BYTE(reg)			(1 << ((reg) & 3))
#define MK_WORD(reg)			(3 << ((reg) & 2))
#define MK_LONG(reg)			(0xf)

#define MK_OP(_byteen, _reg)		\
	((((_reg) >> SPI_ADDR_ENABLE_S) << SPI_BYTE_ENABLE_S) | _byteen)

#define KS_SPIOP_RD			0
#define KS_SPIOP_WR			\
	(1 << (SPI_ADDR_S - SPI_ADDR_ENABLE_S + SPI_BYTE_ENABLE_S))

/*
 * SPI register read/write calls.
 *
 * All these calls issue SPI transactions to access the chip's registers. They
 * all require that the necessary lock is held to prevent accesses when the
 * chip is busy transfering packet data (RX/TX FIFO accesses).
 */

/**
 * spi_wrreg - issue write register command
 * @ks:		The switch device structure.
 * @op:		The register address and byte enables in message format.
 * @val:	The value to write.
 * @rxl:	The length of data.
 *
 * This is the low level write call that issues the necessary spi message(s)
 * to write data to the register specified in @op.
 */
static void spi_wrreg(struct spi_hw_priv *ks, unsigned op, unsigned val,
	unsigned txl)
{
	struct spi_transfer *xfer = &ks->spi_xfer1;
	struct spi_message *msg = &ks->spi_msg1;
	struct spi_device *spi = ks->spidev;
	__le16 txb[4];
	int ret;

	op |= KS_SPIOP_WR;
	op <<= SPI_TURNAROUND_S;
	txb[0] = cpu_to_be16(op);
	txb[1] = cpu_to_le16(val);
	txb[2] = cpu_to_le16(val >> 16);

	xfer->tx_buf = txb;
	xfer->rx_buf = NULL;
	xfer->len = txl + 2;

	ret = spi_sync(spi, msg);
	if (ret < 0)
		pr_alert("spi_sync() failed\n");
}

/**
 * spi_wrreg32 - write 32bit register value to chip
 * @ks:		The switch device structure.
 * @reg:	The register address.
 * @val:	The value to write.
 *
 * Issue a write to put the value @val into the register specified in @reg.
 */
static void spi_wrreg32(struct spi_hw_priv *ks, unsigned reg, unsigned val)
{
	spi_wrreg(ks, MK_OP(MK_LONG(reg), reg), val, 4);
}

/**
 * spi_wrreg16 - write 16bit register value to chip
 * @ks:		The switch device structure.
 * @reg:	The register address.
 * @val:	The value to write.
 *
 * Issue a write to put the value @val into the register specified in @reg.
 */
static void spi_wrreg16(struct spi_hw_priv *ks, unsigned reg, unsigned val)
{
	spi_wrreg(ks, MK_OP(MK_WORD(reg), reg), val, 2);
}

/**
 * spi_wrreg8 - write 8bit register value to chip
 * @ks:		The switch device structure.
 * @reg:	The register address.
 * @val:	The value to write.
 *
 * Issue a write to put the value @val into the register specified in @reg.
 */
static void spi_wrreg8(struct spi_hw_priv *ks, unsigned reg, unsigned val)
{
	spi_wrreg(ks, MK_OP(MK_BYTE(reg), reg), val, 1);
}

/**
 * ksz_rx_1msg - select whether to use one or two messages for spi read
 * @ks:		The device structure.
 *
 * Return whether to generate a single message with a tx and rx buffer
 * supplied to spi_sync(), or alternatively send the tx and rx buffers
 * as separate messages.
 *
 * Depending on the hardware in use, a single message may be more efficient
 * on interrupts or work done by the driver.
 *
 * This currently always returns false until we add some per-device data passed
 * from the platform code to specify which mode is better.
 */
static inline bool ksz_rx_1msg(struct spi_hw_priv *ks)
{
	return ks->rx_1msg;
}

/**
 * spi_rdreg - issue read register command and return the data
 * @ks:		The switch device structure.
 * @op:		The register address and byte enables in message format.
 * @rxb:	The RX buffer to return the result into.
 * @rxl:	The length of data expected.
 *
 * This is the low level read call that issues the necessary spi message(s)
 * to read data from the register specified in @op.
 */
static void spi_rdreg(struct spi_hw_priv *ks, unsigned op, u8 *rxb, unsigned rxl)
{
	struct spi_transfer *xfer;
	struct spi_message *msg;
	struct spi_device *spi = ks->spidev;
	__le16 *txb = (__le16 *) ks->txd;
	u8 *trx = ks->rxd;
	int ret;

	op |= KS_SPIOP_RD;
	op <<= SPI_TURNAROUND_S;
	txb[0] = cpu_to_be16(op);

	if (ksz_rx_1msg(ks)) {
#if defined(CONFIG_SPI_PEGASUS) || defined(CONFIG_SPI_PEGASUS_MODULE)
		/*
		 * A hack to tell KSZ8692 SPI host controller the read command.
		 */
		txb[1] = 0;
		memcpy(trx, txb, 2 + 2);
		txb[1] ^= 0xffff;
#endif
		msg = &ks->spi_msg1;
		xfer = &ks->spi_xfer1;

		xfer->tx_buf = txb;
		xfer->rx_buf = trx;
		xfer->len = rxl + 2;
	} else {
		msg = &ks->spi_msg2;
		xfer = ks->spi_xfer2;

		xfer->tx_buf = txb;
		xfer->rx_buf = NULL;
		xfer->len = 2;

		xfer++;
		xfer->tx_buf = NULL;
		xfer->rx_buf = trx;
		xfer->len = rxl;
	}

	ret = spi_sync(spi, msg);
	if (ret < 0)
		pr_alert("read: spi_sync() failed\n");
	else if (ksz_rx_1msg(ks))
		memcpy(rxb, trx + 2, rxl);
	else
		memcpy(rxb, trx, rxl);
}

/**
 * spi_rdreg8 - read 8 bit register from device
 * @ks:		The switch device structure.
 * @reg:	The register address.
 *
 * Read a 8bit register from the chip, returning the result.
 */
static u8 spi_rdreg8(struct spi_hw_priv *ks, unsigned reg)
{
	u8 rxb[1];

	spi_rdreg(ks, MK_OP(MK_BYTE(reg), reg), rxb, 1);
	return rxb[0];
}

/**
 * spi_rdreg16 - read 16 bit register from device
 * @ks:		The switch device structure.
 * @reg:	The register address.
 *
 * Read a 16bit register from the chip, returning the result.
 */
static u16 spi_rdreg16(struct spi_hw_priv *ks, unsigned reg)
{
	__le16 rx = 0;

	spi_rdreg(ks, MK_OP(MK_WORD(reg), reg), (u8 *) &rx, 2);
	return le16_to_cpu(rx);
}

/**
 * spi_rdreg32 - read 32 bit register from device
 * @ks:		The switch device structure.
 * @reg:	The register address.
 *
 * Read a 32bit register from the chip.
 *
 * Note, this read requires the address be aligned to 4 bytes.
 */
static u32 spi_rdreg32(struct spi_hw_priv *ks, unsigned reg)
{
	__le32 rx = 0;

	WARN_ON(reg & 3);

	spi_rdreg(ks, MK_OP(MK_LONG(reg), reg), (u8 *) &rx, 4);
	return le32_to_cpu(rx);
}

/* -------------------------------------------------------------------------- */

#define USE_SHOW_HELP
#include "ksz_common.c"

/* For ksz_request used by PTP or MRP driver. */
#include "ksz_req.c"

/* -------------------------------------------------------------------------- */

#define MIB_READ_INTERVAL		(HZ / 2)

static u8 sw_r8(struct ksz_sw *sw, unsigned reg)
{
	return HW_R8(sw->dev, reg);
}

static u16 sw_r16(struct ksz_sw *sw, unsigned reg)
{
	return HW_R16(sw->dev, reg);
}

static u32 sw_r32(struct ksz_sw *sw, unsigned reg)
{
	return HW_R32(sw->dev, reg);
}

static void sw_w8(struct ksz_sw *sw, unsigned reg, unsigned val)
{
	HW_W8(sw->dev, reg, val);
}

static void sw_w16(struct ksz_sw *sw, unsigned reg, unsigned val)
{
	HW_W16(sw->dev, reg, val);
}

static void sw_w32(struct ksz_sw *sw, unsigned reg, unsigned val)
{
	HW_W32(sw->dev, reg, val);
}

#define USE_DIFF_PORT_PRIORITY
#include "ksz_sw.c"

static struct ksz_sw_reg_ops sw_reg_ops = {
	.r8			= sw_r8,
	.r16			= sw_r16,
	.r32			= sw_r32,
	.w8			= sw_w8,
	.w16			= sw_w16,
	.w32			= sw_w32,

	.r			= sw_r16,
	.w			= sw_w16,

	.get			= sw_reg_get,
	.set			= sw_reg_set,
};

/* -------------------------------------------------------------------------- */

static int rx_1msg;
static int spi_bus;

#define MAX_SPI_DEVICES		2

static int ksz8463_probe(struct spi_device *spi)
{
	struct spi_hw_priv *hw_priv;
	struct sw_priv *ks;

	spi->bits_per_word = 8;

	ks = kzalloc(sizeof(struct sw_priv), GFP_KERNEL);
	if (!ks)
		return -ENOMEM;

	ks->hw_priv = kzalloc(sizeof(struct spi_hw_priv), GFP_KERNEL);
	if (!ks->hw_priv) {
		kfree(ks);
		return -ENOMEM;
	}
	hw_priv = ks->hw_priv;

	hw_priv->rx_1msg = rx_1msg;
	hw_priv->spidev = spi;

	ks->dev = &spi->dev;
	ks->hw_dev = hw_priv;

	ks->sw.reg = &sw_reg_ops;

	/* initialise pre-made spi transfer messages */

	spi_message_init(&hw_priv->spi_msg1);
	spi_message_add_tail(&hw_priv->spi_xfer1, &hw_priv->spi_msg1);

	spi_message_init(&hw_priv->spi_msg2);
	spi_message_add_tail(&hw_priv->spi_xfer2[0], &hw_priv->spi_msg2);
	spi_message_add_tail(&hw_priv->spi_xfer2[1], &hw_priv->spi_msg2);

	ks->irq = spi->irq;

	return ksz_probe(ks);
}

static int ksz8463_remove(struct spi_device *spi)
{
	struct sw_priv *ks = dev_get_drvdata(&spi->dev);

	return ksz_remove(ks);
}

static const struct of_device_id ksz8463_dt_ids[] = {
	{ .compatible = "microchip,ksz8463" },
	{},
};
MODULE_DEVICE_TABLE(of, ksz8463_dt_ids);

static struct spi_driver ksz8463_driver = {
	.driver = {
		.name = KS8463MLI_DEV0,
		.owner = THIS_MODULE,
		.of_match_table = of_match_ptr(ksz8463_dt_ids),
	},
	.probe = ksz8463_probe,
	.remove = ksz8463_remove,
};

#if defined(CONFIG_SPI_FTDI) && defined(CONFIG_ARCH_MICREL_PEGASUS)
static void ksz8463_late_init(void)
{
	spi_register_driver(&ksz8463_driver);
}
#endif

static int __init ksz8463_init(void)
{
	if (spi_bus == 0)
		sprintf((char *) ksz8463_driver.driver.name, KS8463MLI_DEV0);
	else
		sprintf((char *) ksz8463_driver.driver.name, KS8463MLI_DEV2);
#ifdef DEBUG_MSG
	if (init_dbg())
		return -ENOMEM;
#endif

#if defined(CONFIG_SPI_FTDI) && defined(CONFIG_ARCH_MICREL_PEGASUS)
	pegasus_register_late_call(ksz8463_late_init);
	return 0;
#else
	return spi_register_driver(&ksz8463_driver);
#endif
}

static void __exit ksz8463_exit(void)
{
	spi_unregister_driver(&ksz8463_driver);
#ifdef DEBUG_MSG
	exit_dbg();
#endif
}

#ifndef CONFIG_KSZ8463_EMBEDDED
subsys_initcall(ksz8463_init);
module_exit(ksz8463_exit);
#endif

module_param(rx_1msg, int, 0);
MODULE_PARM_DESC(rx_1msg,
	"Configure whether receive one message is used");

module_param(spi_bus, int, 0);
MODULE_PARM_DESC(spi_bus,
	"Configure which spi master to use(0=KSZ8692, 2=FTDI)");

#ifndef CONFIG_KSZ8463_EMBEDDED
MODULE_DESCRIPTION("Microchip KSZ8463 MLI Switch Driver");
MODULE_AUTHOR("Tristram Ha <Tristram.Ha@microchip.com>");
MODULE_LICENSE("GPL");

MODULE_ALIAS("spi:ksz8463");
#endif
