/**
 * Microchip KSZ9897 SPI driver
 *
 * Copyright (c) 2015-2017 Microchip Technology Inc.
 * Copyright (c) 2013-2015 Micrel, Inc.
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

#if 0
#define NO_ATTACHED_DEV
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

#ifndef CONFIG_KSZ_IBA_ONLY
#include <linux/spi/spi.h>
#include <linux/debugfs.h>
#include <linux/seq_file.h>
#endif

#define MAX_REQUEST_SIZE		80

#include "ksz_cfg_9897.h"


#if 1
#define NO_EEE
#endif


#ifdef CONFIG_KSZ_DLR
/* Have ACL to handle beacon timeout. */
#define CONFIG_HAVE_ACL_HW

/* Have DLR to transmit beacons. */
#define CONFIG_HAVE_DLR_HW
#endif

#ifdef CONFIG_KSZ_HSR
#define CONFIG_HAVE_HSR_HW
#endif

#if 0
#define USE_MII_PHY
#endif
#if 0
#define USE_RGMII_PHY
#endif
#if 0
#define USE_MII_MODE
#endif
#if 0
#define USE_GMII_MODE
#endif
#if 0
#define USE_RMII_MODE
#endif
#if 0
#define USE_RGMII_MODE
#endif
#if 0
#define USE_GMII_100_MODE
#endif
#if 0
#define USE_10_MBIT_MODE
#ifndef USE_GMII_100_MODE
#define USE_GMII_100_MODE
#endif
#endif
#if 0
#define USE_HALF_DUPLEX
#endif


#define KS9897MLI_DEV0			"ksz9897"
#define KS9897MLI_DEV2			"ksz9897_2"

#define SW_DRV_RELDATE			"Jul 27, 2017"
#define SW_DRV_VERSION			"1.1.2"

/* -------------------------------------------------------------------------- */

#ifndef CONFIG_KSZ_IBA_ONLY
#define HW_R(ks, reg)		spi_rdreg8(ks, reg)
#define HW_W(ks, reg, val)	spi_wrreg8(ks, reg, val)
#define HW_R8(ks, reg)		spi_rdreg8(ks, reg)
#define HW_W8(ks, reg, val)	spi_wrreg8(ks, reg, val)
#define HW_R16(ks, reg)		spi_rdreg16(ks, reg)
#define HW_W16(ks, reg, val)	spi_wrreg16(ks, reg, val)
#define HW_R24(ks, reg)		spi_rdreg24(ks, reg)
#define HW_W24(ks, reg, val)	spi_wrreg24(ks, reg, val)
#define HW_R32(ks, reg)		spi_rdreg32(ks, reg)
#define HW_W32(ks, reg, val)	spi_wrreg32(ks, reg, val)
#else
#define HW_R(ks, reg)		0
#define HW_W(ks, reg, val)
#define HW_R8(ks, reg)		0
#define HW_W8(ks, reg, val)
#define HW_R16(ks, reg)		0
#define HW_W16(ks, reg, val)
#define HW_R24(ks, reg)		0
#define HW_W24(ks, reg, val)
#define HW_R32(ks, reg)		0
#define HW_W32(ks, reg, val)
#endif

#include "ksz_sw_phy.h"

#include "ksz_spi_net.h"

/* -------------------------------------------------------------------------- */

#define contain_reg(addr, len, reg)	\
	(addr <= (reg) && (reg) <= (addr + len - 1))

#ifndef CONFIG_KSZ_IBA_ONLY
static void spi_chk_regs(struct ksz_sw *sw, u32 addr, u8 *val, size_t txl)
{
	int i;
	u32 port_reg;

	port_reg = REG_PTP_MSG_CONF1 + 1;
	if contain_reg(addr, txl, port_reg) {
		i = port_reg - addr;
		if (val[i] & PTP_ENABLE)
			sw->overrides |= PTP_TAG;
		else
			sw->overrides &= ~PTP_TAG;

/* KSZ9567 S1 needs to have PTP tag all the time. */
#if 1
		if (!(sw->features & NEW_CAP) &&
		    sw->TAIL_TAG_LOOKUP >= 0x100)
			sw->overrides |= PTP_TAG;
#endif
	}
	port_reg = PORT_CTRL_ADDR(sw->HOST_PORT, REG_PORT_CTRL_0);
	if contain_reg(addr, txl, port_reg) {
		i = port_reg - addr;
		if (val[i] & PORT_TAIL_TAG_ENABLE)
			sw->overrides |= TAIL_TAGGING;
		else
			sw->overrides &= ~TAIL_TAGGING;
	}
}  /* spi_chk_regs */

/* SPI frame opcodes */
#define KS_SPIOP_RD			3
#define KS_SPIOP_WR			2

#define SPI_ADDR_SHIFT			24
#define SPI_ADDR_MASK			((1 << SPI_ADDR_SHIFT) - 1)
#define SPI_TURNAROUND_SHIFT		5

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
 * @addr:	The register address.
 * @val:	The value to write.
 * @txl:	The length of data.
 *
 * This is the low level write call that issues the necessary spi message(s)
 * to write data to the register specified in @addr.
 */
static void spi_wrreg(struct sw_priv *ks, u32 addr, void *txb, size_t txl)
{
	struct spi_hw_priv *hw_priv = ks->hw_dev;
	struct spi_transfer *xfer = &hw_priv->spi_xfer1;
	struct spi_message *msg = &hw_priv->spi_msg1;
	struct spi_device *spi = hw_priv->spidev;
	u32 *txc = (u32 *) hw_priv->txd;
	int ret;
	struct ksz_sw *sw = &ks->sw;

	if (!(sw->features & NEW_CAP)) {
		u32 len = (addr & 3) + txl;

		if (len >= 4 && (len & 3))
			pr_alert("W may not be correct: %x %x\n", addr, txl);
	}
	if (!mutex_is_locked(&ks->lock))
		pr_alert("W not locked: %x\n", addr);
	*txc = addr & SPI_ADDR_MASK;
	*txc |= KS_SPIOP_WR << SPI_ADDR_SHIFT;
	*txc <<= SPI_TURNAROUND_SHIFT;
	*txc = cpu_to_be32(*txc);
	++txc;
	memcpy(txc, txb, txl);

	xfer->tx_buf = hw_priv->txd;
	xfer->rx_buf = NULL;
	xfer->len = txl + 4;

	ret = spi_sync(spi, msg);
	if (ret < 0)
		pr_alert("spi_sync() failed: %x %u\n", addr, txl);
	spi_chk_regs(sw, addr, txb, txl);
}

/**
 * spi_wrreg32 - write 32bit register value to chip
 * @ks:		The switch device structure.
 * @reg:	The register address.
 * @val:	The value to write.
 *
 * Issue a write to put the value @val into the register specified in @reg.
 */
static void spi_wrreg32(struct sw_priv *ks, u32 reg, u32 val)
{
	u8 txb[4];
	int i = 0;
	size_t cnt = 4;

	do {
		txb[i++] = (u8)(val >> (8 * (cnt - 1)));
		cnt--;
	} while (cnt);
	spi_wrreg(ks, reg, txb, 4);
}

/**
 * spi_wrreg24 - write 24bit register value to chip
 * @ks:		The switch device structure.
 * @reg:	The register address.
 * @val:	The value to write.
 *
 * Issue a write to put the value @val into the register specified in @reg.
 */
static void spi_wrreg24(struct sw_priv *ks, u32 reg, u32 val)
{
	u8 txb[4];
	int i = 0;
	size_t cnt = 3;

	do {
		txb[i++] = (u8)(val >> (8 * (cnt - 1)));
		cnt--;
	} while (cnt);
	spi_wrreg(ks, reg, txb, 3);
}

/**
 * spi_wrreg16 - write 16bit register value to chip
 * @ks:		The switch device structure.
 * @reg:	The register address.
 * @val:	The value to write.
 *
 * Issue a write to put the value @val into the register specified in @reg.
 */
static void spi_wrreg16(struct sw_priv *ks, u32 reg, u32 val)
{
	u8 txb[4];
	int i = 0;
	size_t cnt = 2;

	do {
		txb[i++] = (u8)(val >> (8 * (cnt - 1)));
		cnt--;
	} while (cnt);
	spi_wrreg(ks, reg, txb, 2);
}

/**
 * spi_wrreg8 - write 8bit register value to chip
 * @ks:		The switch device structure.
 * @reg:	The register address.
 * @val:	The value to write.
 *
 * Issue a write to put the value @val into the register specified in @reg.
 */
static void spi_wrreg8(struct sw_priv *ks, u32 reg, u32 val)
{
	u8 txb[4];
	int i = 0;
	size_t cnt = 1;

	do {
		txb[i++] = (u8)(val >> (8 * (cnt - 1)));
		cnt--;
	} while (cnt);
	spi_wrreg(ks, reg, txb, 1);
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
 * @ks:		The device structure.
 * @reg:	The register address.
 * @rxb:	The RX buffer to return the result into.
 * @rxl:	The length of data expected.
 *
 * This is the low level read call that issues the necessary spi message(s)
 * to read data from the register specified in @op.
 */
static void spi_rdreg(struct sw_priv *ks, u32 addr, void *rxb, size_t rxl)
{
	struct spi_hw_priv *hw_priv = ks->hw_dev;
	struct spi_transfer *xfer;
	struct spi_message *msg;
	struct spi_device *spi = hw_priv->spidev;
	u32 *txc = (u32 *) hw_priv->txd;
	u8 *trx = hw_priv->rxd;
	int ret;

	if (!mutex_is_locked(&ks->lock))
		pr_alert("R not locked: %x\n", addr);
	*txc = addr & SPI_ADDR_MASK;
	*txc |= KS_SPIOP_RD << SPI_ADDR_SHIFT;
	*txc <<= SPI_TURNAROUND_SHIFT;
	*txc = cpu_to_be32(*txc);

	if (ksz_rx_1msg(hw_priv)) {
		msg = &hw_priv->spi_msg1;
		xfer = &hw_priv->spi_xfer1;
		xfer->tx_buf = hw_priv->txd;
		xfer->rx_buf = hw_priv->rxd;
		xfer->len = rxl + 4;
		++txc;
		memset(txc, 0, rxl);
#if defined(CONFIG_SPI_PEGASUS) || defined(CONFIG_SPI_PEGASUS_MODULE)
		/*
		 * A hack to tell KSZ8692 SPI host controller the read command.
		 */
		memcpy(hw_priv->rxd, hw_priv->txd, 4 + 1);
		hw_priv->rxd[4] ^= 0xff;
#endif
	} else {
		msg = &hw_priv->spi_msg2;
		xfer = hw_priv->spi_xfer2;

		xfer->tx_buf = hw_priv->txd;
		xfer->rx_buf = NULL;
		xfer->len = 4;

		xfer++;
		xfer->tx_buf = NULL;
		xfer->rx_buf = hw_priv->rxd;
		xfer->len = rxl;
	}

	ret = spi_sync(spi, msg);
	if (ret < 0)
		pr_alert("read: spi_sync() failed: %x %u\n", addr, rxl);
	else if (ksz_rx_1msg(hw_priv))
		memcpy(rxb, trx + 4, rxl);
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
static u8 spi_rdreg8(struct sw_priv *ks, u32 reg)
{
	u8 rxb[1];

	spi_rdreg(ks, reg, rxb, 1);
	return rxb[0];
}

/**
 * spi_rdreg16 - read 16 bit register from device
 * @ks:		The switch device structure.
 * @reg:	The register address.
 *
 * Read a 16bit register from the chip, returning the result.
 */
static u16 spi_rdreg16(struct sw_priv *ks, u32 reg)
{
	__le16 rx = 0;

	spi_rdreg(ks, reg, &rx, 2);
	return be16_to_cpu(rx);
}

/**
 * spi_rdreg24 - read 24 bit register from device
 * @ks:		The switch device structure.
 * @reg:	The register address.
 *
 * Read a 24bit register from the chip.
 */
static u32 spi_rdreg24(struct sw_priv *ks, u32 reg)
{
	__le32 rx = 0;

	spi_rdreg(ks, reg, &rx, 3);
	return be32_to_cpu(rx);
}

/**
 * spi_rdreg32 - read 32 bit register from device
 * @ks:		The switch device structure.
 * @reg:	The register address.
 *
 * Read a 32bit register from the chip.
 */
static u32 spi_rdreg32(struct sw_priv *ks, u32 reg)
{
	__le32 rx = 0;

	spi_rdreg(ks, reg, &rx, 4);
	return be32_to_cpu(rx);
}
#endif

/* -------------------------------------------------------------------------- */

/**
 * delay_micro - delay in microsecond
 * @microsec:	Number of microseconds to delay.
 *
 * This routine delays in microseconds.
 */
static inline void delay_micro(uint microsec)
{
	uint millisec = microsec / 1000;

	microsec %= 1000;
	if (millisec)
		mdelay(millisec);
	if (microsec)
		udelay(microsec);
}

/**
 * delay_milli - delay in millisecond
 * @millisec:	Number of milliseconds to delay.
 *
 * This routine delays in milliseconds.
 */
static void delay_milli(uint millisec)
{
	unsigned long ticks = millisec * HZ / 1000;

	if (!ticks || in_interrupt())
		mdelay(millisec);
	else {
		set_current_state(TASK_INTERRUPTIBLE);
		schedule_timeout(ticks);
	}
}

#define USE_SHOW_HELP
#include "ksz_common.c"

/* For ksz_request used by PTP or MRP driver. */
#include "ksz_req.c"

#ifndef CONFIG_KSZ_SWITCH_EMBEDDED
static inline void copy_old_skb(struct sk_buff *old, struct sk_buff *skb)
{
	skb->dev = old->dev;
	skb->sk = old->sk;
	skb->protocol = old->protocol;
	skb->ip_summed = old->ip_summed;
	skb->csum = old->csum;
	skb_shinfo(skb)->tx_flags = skb_shinfo(old)->tx_flags;
	skb_set_network_header(skb, ETH_HLEN);

	dev_kfree_skb(old);
}  /* copy_old_skb */
#endif

/* -------------------------------------------------------------------------- */

#define KSZSW_REGS_SIZE			0x8000

static struct sw_regs {
	int start;
	int end;
} sw_regs_range[] = {
	{ 0x0000, 0x7FFF },
	{ 0, 0 }
};

static int check_sw_reg_range(unsigned addr)
{
	struct sw_regs *range = sw_regs_range;

	while (range->end > range->start) {
		if (range->start <= addr && addr < range->end)
			return true;
		range++;
	}
	return false;
}

static struct ksz_sw *get_sw_data(struct device *d)
{
	struct sw_priv *hw_priv = dev_get_drvdata(d);

	return &hw_priv->sw;
}

/* -------------------------------------------------------------------------- */

#define MIB_READ_INTERVAL		(HZ / 2)

static void sw_lock(struct ksz_sw *sw)
{
	const struct ksz_sw_reg_ops *reg_ops = sw->reg;

	mutex_lock(sw->reglock);
	if (sw->reg != reg_ops) {
		mutex_unlock(sw->reglock);
		sw->reg->lock(sw);
	}
}  /* sw_lock */

static void sw_unlock(struct ksz_sw *sw)
{
	mutex_unlock(sw->reglock);
}  /* sw_unlock */

static int exit_mib_read(struct ksz_sw *sw)
{
	if (sw->intr_using)
		return true;
	return false;
}  /* exit_mib_read */

static u8 sw_r8(struct ksz_sw *sw, unsigned reg)
{
	return HW_R8(sw->dev, reg);
}

static u16 sw_r16(struct ksz_sw *sw, unsigned reg)
{
	return HW_R16(sw->dev, reg);
}

static u32 sw_r24(struct ksz_sw *sw, unsigned reg)
{
	return HW_R24(sw->dev, reg);
}

static u32 sw_r32(struct ksz_sw *sw, unsigned reg)
{
	return HW_R32(sw->dev, reg);
}

static void sw_r(struct ksz_sw *sw, unsigned reg, void *buf, size_t cnt)
{
#ifndef CONFIG_KSZ_IBA_ONLY
	spi_rdreg(sw->dev, reg, buf, cnt);
#else
	/* Avoid compiler complaint. */
	memset(buf, 0, cnt);
#endif
}

static void sw_w(struct ksz_sw *sw, unsigned reg, void *buf, size_t cnt)
{
#ifndef CONFIG_KSZ_IBA_ONLY
	spi_wrreg(sw->dev, reg, buf, cnt);
#endif
}

static void sw_w8(struct ksz_sw *sw, unsigned reg, unsigned val)
{
	HW_W8(sw->dev, reg, val);
}

static void sw_w16(struct ksz_sw *sw, unsigned reg, unsigned val)
{
	HW_W16(sw->dev, reg, val);
}

static void sw_w24(struct ksz_sw *sw, unsigned reg, unsigned val)
{
	HW_W24(sw->dev, reg, val);
}

static void sw_w32(struct ksz_sw *sw, unsigned reg, unsigned val)
{
	HW_W32(sw->dev, reg, val);
}


static void link_update_work(struct work_struct *work);

static void sw_dis_intr(struct ksz_sw *sw);
static void sw_ena_intr(struct ksz_sw *sw);

#define USE_DIFF_PORT_PRIORITY
#include "ksz_sw_9897.c"

static int rx_1msg = 1;
static int spi_bus;


#define MAX_SPI_DEVICES		2

#if !defined(CONFIG_KSZ_IBA_ONLY)
static int ksz9897_probe(struct spi_device *spi)
{
	struct spi_hw_priv *hw_priv;
	struct sw_priv *ks;

	spi->bits_per_word = 8;

	ks = kzalloc(sizeof(struct sw_priv), GFP_KERNEL);
	if (!ks)
		return -ENOMEM;

	ks->hw_dev = kzalloc(sizeof(struct spi_hw_priv), GFP_KERNEL);
	if (!ks->hw_dev) {
		kfree(ks);
		return -ENOMEM;
	}
	hw_priv = ks->hw_dev;

	hw_priv->rx_1msg = rx_1msg;
	hw_priv->spidev = spi;

	ks->dev = &spi->dev;

	/* initialise pre-made spi transfer messages */

	spi_message_init(&hw_priv->spi_msg1);
	spi_message_add_tail(&hw_priv->spi_xfer1, &hw_priv->spi_msg1);

	spi_message_init(&hw_priv->spi_msg2);
	spi_message_add_tail(&hw_priv->spi_xfer2[0], &hw_priv->spi_msg2);
	spi_message_add_tail(&hw_priv->spi_xfer2[1], &hw_priv->spi_msg2);

	ks->irq = spi->irq;

	return ksz_probe(ks);
}

static int ksz9897_remove(struct spi_device *spi)
{
	struct sw_priv *ks = dev_get_drvdata(&spi->dev);

	return ksz_remove(ks);
}

static const struct of_device_id ksz9897_dt_ids[] = {
	{ .compatible = "microchip,ksz9567" },
	{ .compatible = "microchip,ksz9477" },
	{ .compatible = "microchip,ksz9893" },
	{},
};
MODULE_DEVICE_TABLE(of, ksz9897_dt_ids);

static struct spi_driver ksz9897_driver = {
	.driver = {
		.name = KS9897MLI_DEV0,
		.owner = THIS_MODULE,
		.of_match_table = of_match_ptr(ksz9897_dt_ids),
	},
	.probe = ksz9897_probe,
	.remove = ksz9897_remove,
};

static int __init ksz9897_init(void)
{
#ifdef DEBUG_MSG
	if (init_dbg())
		return -ENOMEM;
#endif

	return spi_register_driver(&ksz9897_driver);
}

static void __exit ksz9897_exit(void)
{
	spi_unregister_driver(&ksz9897_driver);
#ifdef DEBUG_MSG
	exit_dbg();
#endif
}
#endif

#if !defined(CONFIG_KSZ_SWITCH_EMBEDDED)
subsys_initcall(ksz9897_init);
module_exit(ksz9897_exit);
#endif

module_param(fast_aging, int, 0);
module_param(multi_dev, int, 0);
module_param(stp, int, 0);
module_param(avb, int, 0);
module_param(authen, int, 0);
MODULE_PARM_DESC(fast_aging, "Fast aging");
MODULE_PARM_DESC(multi_dev, "Multiple device interfaces");
MODULE_PARM_DESC(stp, "STP support");
MODULE_PARM_DESC(avb, "AVB support");
MODULE_PARM_DESC(authen, "802.1X Authentication");

#ifdef CONFIG_KSZ_IBA
module_param(iba, int, 0);
MODULE_PARM_DESC(iba, "IBA support");
#endif

module_param(intr_mode, int, 0);
MODULE_PARM_DESC(intr_mode,
	"Configure which interrupt mode to use(1=level low, 2=falling)");

module_param(rx_1msg, int, 0);
MODULE_PARM_DESC(rx_1msg,
	"Configure whether receive one message is used");

module_param(spi_bus, int, 0);
MODULE_PARM_DESC(spi_bus,
	"Configure which spi master to use(0=KSZ8692, 2=FTDI)");

module_param(sw_host_port, int, 0);
MODULE_PARM_DESC(sw_host_port,
	"Configure switch host port");

module_param(ports, int, 0);
MODULE_PARM_DESC(ports,
	"Configure number of ports");

module_param(eth1_ports, int, 0);
module_param(eth2_ports, int, 0);
module_param(eth3_ports, int, 0);
module_param(eth4_ports, int, 0);
module_param(eth5_ports, int, 0);
module_param(eth6_ports, int, 0);
MODULE_PARM_DESC(eth1_ports, "Ports to use on device 1.");
MODULE_PARM_DESC(eth2_ports, "Ports to use on device 2.");
MODULE_PARM_DESC(eth3_ports, "Ports to use on device 3.");
MODULE_PARM_DESC(eth4_ports, "Ports to use on device 4.");
MODULE_PARM_DESC(eth5_ports, "Ports to use on device 5.");
MODULE_PARM_DESC(eth6_ports, "Ports to use on device 6.");

module_param(eth1_vlan, int, 0);
module_param(eth2_vlan, int, 0);
module_param(eth3_vlan, int, 0);
module_param(eth4_vlan, int, 0);
module_param(eth5_vlan, int, 0);
module_param(eth6_vlan, int, 0);
MODULE_PARM_DESC(eth1_vlan, "VLAN to use on device 1.");
MODULE_PARM_DESC(eth2_vlan, "VLAN to use on device 2.");
MODULE_PARM_DESC(eth3_vlan, "VLAN to use on device 3.");
MODULE_PARM_DESC(eth4_vlan, "VLAN to use on device 4.");
MODULE_PARM_DESC(eth5_vlan, "VLAN to use on device 5.");
MODULE_PARM_DESC(eth6_vlan, "VLAN to use on device 6.");

module_param(eth1_proto, charp, 0);
module_param(eth2_proto, charp, 0);
module_param(eth3_proto, charp, 0);
module_param(eth4_proto, charp, 0);
module_param(eth5_proto, charp, 0);
module_param(eth6_proto, charp, 0);
MODULE_PARM_DESC(eth1_proto, "Protocol to use on device 1.");
MODULE_PARM_DESC(eth2_proto, "Protocol to use on device 2.");
MODULE_PARM_DESC(eth3_proto, "Protocol to use on device 3.");
MODULE_PARM_DESC(eth4_proto, "Protocol to use on device 4.");
MODULE_PARM_DESC(eth5_proto, "Protocol to use on device 5.");
MODULE_PARM_DESC(eth6_proto, "Protocol to use on device 6.");

#ifndef CONFIG_KSZ_SWITCH_EMBEDDED
MODULE_DESCRIPTION("Microchip KSZ9897 SPI Switch Driver");
MODULE_AUTHOR("Tristram Ha <Tristram.Ha@microchip.com>");
MODULE_LICENSE("GPL");

MODULE_ALIAS("spi:ksz9897");
#endif
