/**
 * Microchip KSZ8895 SPI driver
 *
 * Copyright (c) 2015-2017 Microchip Technology Inc.
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
#endif

/* -------------------------------------------------------------------------- */

#include <linux/spi/spi.h>
#include <linux/debugfs.h>
#include <linux/seq_file.h>
#include "ksz_cfg_8895.h"


#define KS8895_DEV			"ksz8895"

#define SW_DRV_RELDATE			"Feb 8, 2017"
#define SW_DRV_VERSION			"1.1.0"

/* -------------------------------------------------------------------------- */

#define HW_R(ks, reg)		spi_rdreg8(ks, reg)
#define HW_W(ks, reg, val)	spi_wrreg8(ks, reg, val)
#define HW_R8(ks, reg)		spi_rdreg8(ks, reg)
#define HW_W8(ks, reg, val)	spi_wrreg8(ks, reg, val)
#define HW_R16(ks, reg)		spi_rdreg16(ks, reg)
#define HW_W16(ks, reg, val)	spi_wrreg16(ks, reg, val)
#define HW_R32(ks, reg)		spi_rdreg32(ks, reg)
#define HW_W32(ks, reg, val)	spi_wrreg32(ks, reg, val)

#include "ksz_sw_phy.h"

#include "ksz_spi_net.h"

/* -------------------------------------------------------------------------- */

/* SPI frame opcodes */
#define SPI_ADDR_S			12
#define SPI_ADDR_M			((1 << SPI_ADDR_S) - 1)
#define SPI_TURNAROUND_S		1

#define KS_SPIOP_RD			3
#define KS_SPIOP_WR			2

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
 * @reg:	The register address.
 * @buf:	The data buffer to write.
 * @rxl:	The length of data.
 *
 * This is the low level write call that issues the necessary spi message(s)
 * to write data to the register specified in @reg.
 */
static void spi_wrreg(struct sw_priv *ks, u8 reg, void *buf, unsigned txl)
{
	struct spi_hw_priv *hw_priv = ks->hw_dev;
	struct spi_transfer *xfer = hw_priv->spi_xfer2;
	struct spi_message *msg = &hw_priv->spi_msg2;
	struct spi_device *spi = hw_priv->spidev;
	u8 *txb = (u8 *) hw_priv->rxd;
	int ret;

#ifdef DEBUG
	if (!mutex_is_locked(&ks->lock))
		pr_alert("W not locked\n");
#endif
	txb[0] = KS_SPIOP_WR;
	txb[1] = reg;

	xfer->tx_buf = txb;
	xfer->rx_buf = NULL;
	xfer->len = 2;

	xfer++;
	xfer->tx_buf = buf;
	xfer->rx_buf = NULL;
	xfer->len = txl;

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
static void spi_wrreg32(struct sw_priv *ks, u8 reg, unsigned val)
{
	struct spi_hw_priv *hw_priv = ks->hw_dev;
	int cnt = 4;
	int i = 0;
	u8 *txb = hw_priv->txd;

	while (cnt) {
		txb[i++] = (u8)(val >> (8 * (cnt - 1)));
		cnt--;
	}
	spi_wrreg(ks, reg, txb, 4);
}

/**
 * spi_wrreg16 - write 16bit register value to chip
 * @ks:		The switch device structure.
 * @reg:	The register address.
 * @val:	The value to write.
 *
 * Issue a write to put the value @val into the register specified in @reg.
 */
static void spi_wrreg16(struct sw_priv *ks, u8 reg, unsigned val)
{
	struct spi_hw_priv *hw_priv = ks->hw_dev;
	int cnt = 2;
	int i = 0;
	u8 *txb = hw_priv->txd;

	while (cnt) {
		txb[i++] = (u8)(val >> (8 * (cnt - 1)));
		cnt--;
	}
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
static void spi_wrreg8(struct sw_priv *ks, u8 reg, unsigned val)
{
	struct spi_hw_priv *hw_priv = ks->hw_dev;
	u8 *txb = hw_priv->txd;

	*txb = (u8) val;
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
 * @ks:		The switch device structure.
 * @reg:	The register address.
 * @rxb:	The RX buffer to return the result into.
 * @rxl:	The length of data expected.
 *
 * This is the low level read call that issues the necessary spi message(s)
 * to read data from the register specified in @op.
 */
static void spi_rdreg(struct sw_priv *ks, u8 reg, void *rxb, unsigned rxl)
{
	struct spi_hw_priv *hw_priv = ks->hw_dev;
	struct spi_transfer *xfer;
	struct spi_message *msg;
	struct spi_device *spi = hw_priv->spidev;
	u8 *txb = (u8 *) hw_priv->txd;
	int ret;

#ifdef DEBUG
	if (!mutex_is_locked(&ks->lock))
		pr_alert("R not locked: %02X\n", reg);
#endif
	txb[0] = KS_SPIOP_RD;
	txb[1] = reg;

	if (ksz_rx_1msg(hw_priv)) {
		msg = &hw_priv->spi_msg1;
		xfer = &hw_priv->spi_xfer1;

		xfer->tx_buf = txb;
		xfer->rx_buf = hw_priv->rxd;
		xfer->len = rxl + 2;
	} else {
		msg = &hw_priv->spi_msg2;
		xfer = hw_priv->spi_xfer2;

		xfer->tx_buf = txb;
		xfer->rx_buf = NULL;
		xfer->len = 2;

		xfer++;
		xfer->tx_buf = NULL;
		xfer->rx_buf = rxb;
		xfer->len = rxl;
	}

	ret = spi_sync(spi, msg);
	if (ret < 0)
		pr_alert("read: spi_sync() failed\n");
	else if (ksz_rx_1msg(hw_priv))
		memcpy(rxb, hw_priv->rxd + 2, rxl);
}

/**
 * spi_rdreg8 - read 8 bit register from device
 * @ks:		The switch device structure.
 * @reg:	The register address.
 *
 * Read a 8bit register from the chip, returning the result.
 */
static u8 spi_rdreg8(struct sw_priv *ks, u8 reg)
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
static u16 spi_rdreg16(struct sw_priv *ks, u8 reg)
{
	u16 rx = 0;

	spi_rdreg(ks, reg, &rx, 2);
	return be16_to_cpu(rx);
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
static u32 spi_rdreg32(struct sw_priv *ks, u8 reg)
{
	u32 rx = 0;

	spi_rdreg(ks, reg, &rx, 4);
	return be32_to_cpu(rx);
}

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

#include "ksz_req.c"

#ifndef CONFIG_KSZ_SWITCH_EMBEDDED
static inline void copy_old_skb(struct sk_buff *old, struct sk_buff *skb)
{
	skb->dev = old->dev;
	skb->protocol = old->protocol;
	skb->ip_summed = old->ip_summed;
	skb->csum = old->csum;
	skb_set_network_header(skb, ETH_HLEN);

	dev_kfree_skb(old);
}  /* copy_old_skb */
#endif

/* -------------------------------------------------------------------------- */

#define KSZSW_REGS_SIZE			0x100

static struct sw_regs {
	int start;
	int end;
} sw_regs_range[] = {
	{ 0x000, 0x100 },
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

static unsigned long next_jiffies;

static int exit_mib_read(struct ksz_sw *sw)
{
	if (sw->intr_using)
		return true;
	return false;
}  /* exit_mib_read */

static void sw_ena_intr(struct ksz_sw *sw)
{
	struct sw_priv *hw_priv = container_of(sw, struct sw_priv, sw);

	HW_W(sw->dev, REG_INT_ENABLE, hw_priv->intr_mask);
}  /* sw_ena_intr */

static int sw_r(struct ksz_sw *sw, u32 reg, void *buf, unsigned len)
{
	spi_rdreg(sw->dev, reg, buf, len);
	return 0;
}

static int sw_w(struct ksz_sw *sw, u32 reg, void *buf, unsigned len)
{
	spi_wrreg(sw->dev, reg, buf, len);
	return 0;
}

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

static void link_update_work(struct work_struct *work)
{
	struct ksz_port *port =
		container_of(work, struct ksz_port, link_update);
	struct ksz_sw *sw = port->sw;
	struct phy_device *phydev;
	struct ksz_port_info *info;
	int c;
	int i;
	int link;
	int p = sw->ops->get_first_port(sw);

	/* This only matters when one phy device is used for the switch. */
	if (1 == sw->dev_count) {
		struct sw_priv *hw_priv = container_of(sw, struct sw_priv, sw);

		if (hw_priv->phy_id != port->linked->phy_id)
			hw_priv->phy_id = port->linked->phy_id;
	}
	for (c = 0, i = p; c < sw->port_cnt; c++, i++) {
		info = &sw->port_info[i];

		if (!info->report)
			continue;
		info->report = false;
		phydev = sw->phy[i + 1];
		if (!phydev)
			continue;
		phydev->link = (info->state == media_connected);
		phydev->speed = info->tx_rate / TX_RATE_UNIT;
		phydev->duplex = (info->duplex == 2);
	}

	for (i = 0; i < sw->eth_cnt; i++) {
		if (sw->eth_maps[i].port == port->first_port) {
			if (sw->eth_maps[i].phy_id != port->linked->phy_id)
				sw->eth_maps[i].phy_id = port->linked->phy_id;
			break;
		}
	}

	info = port->linked;
	phydev = sw->phy[port->first_port + 1];
	phydev->link = (info->state == media_connected);
	phydev->speed = info->tx_rate / TX_RATE_UNIT;
	phydev->duplex = (info->duplex == 2);
	if (phydev->attached_dev) {
		link = netif_carrier_ok(phydev->attached_dev);
		if (link != phydev->link) {
			if (phydev->link)
				netif_carrier_on(phydev->attached_dev);
			else
				netif_carrier_off(phydev->attached_dev);
			if (netif_msg_link(sw))
				pr_info("%s link %s\n",
					phydev->attached_dev->name,
					phydev->link ? "on" : "off");
		}
	}

	/* The switch is always linked; speed and duplex are also fixed. */
	if (sw->netdev[0]) {
		phydev = sw->netdev[0]->phydev;
		if (!phydev)
			phydev = sw->phydev;
		if (sw->net_ops->get_priv_port)
			port = sw->net_ops->get_priv_port(sw->netdev[0]);
	} else
		phydev = sw->phydev;
	if (phydev->attached_dev) {
		int phy_link;

		/* phydev settings may be changed by ethtool. */
		info = &sw->port_info[sw->HOST_PORT];
		phydev->link = 1;
#if 0
		/* Need a way to know the PHY port is actually used. */
		phydev->speed = info->tx_rate / TX_RATE_UNIT;
		phydev->duplex = (info->duplex == 2);
#else
		phydev->speed = 100;
		phydev->duplex = 1;
#endif
		phydev->pause = 1;
		phy_link = (port->linked->state == media_connected);
		link = netif_carrier_ok(phydev->attached_dev);
		if (link != phy_link) {
			if (phy_link)
				netif_carrier_on(phydev->attached_dev);
			else
				netif_carrier_off(phydev->attached_dev);
			if (netif_msg_link(sw))
				pr_info("%s link %s\n",
					phydev->attached_dev->name,
					phy_link ? "on" : "off");
		}
		if (phydev->adjust_link)
			phydev->adjust_link(phydev->attached_dev);
	}

#ifdef CONFIG_KSZ_STP
	if (sw->features & STP_SUPPORT) {
		struct ksz_stp_info *stp = &sw->info->rstp;

		stp->ops->link_change(stp, true);
	}
#endif

#ifdef CONFIG_KSZ_HSR
	if (sw->features & HSR_HW) {
		struct ksz_hsr_info *hsr = &sw->info->hsr;

		if (hsr->ports[0] <= port->first_port &&
		    port->first_port <= hsr->ports[1])
			hsr->ops->check_announce(hsr);
	}
#endif
}  /* link_update_work */

#include "ksz_sw_8895.c"

/* -------------------------------------------------------------------------- */

/* debugfs code */
static int state_show(struct seq_file *seq, void *v)
{
	int i;
	int j;
	SW_D data[16 / SW_SIZE];
	struct sw_priv *ks = seq->private;

	for (i = 0; i < 0x100; i += 16) {
		seq_printf(seq, SW_SIZE_STR":\t", i);
		mutex_lock(&ks->lock);
		for (j = 0; j < 16 / SW_SIZE; j++)
			data[j] = HW_R(ks, i + j * SW_SIZE);
		mutex_unlock(&ks->lock);
		for (j = 0; j < 16 / SW_SIZE; j++)
			seq_printf(seq, SW_SIZE_STR" ", data[j]);
		seq_printf(seq, "\n");
	}
	return 0;
}

static int state_open(struct inode *inode, struct file *file)
{
	return single_open(file, state_show, inode->i_private);
}

static const struct file_operations state_fops = {
	.owner	= THIS_MODULE,
	.open	= state_open,
	.read	= seq_read,
	.llseek	= seq_lseek,
	.release = single_release,
};

/**
 * create_debugfs - create debugfs directory and files
 * @ks:		The switch device structure.
 *
 * Create the debugfs entries for the specific device.
 */
static void create_debugfs(struct sw_priv *ks)
{
	struct dentry *root;
	char root_name[32];

	snprintf(root_name, sizeof(root_name), "%s",
		 dev_name(ks->dev));

	root = debugfs_create_dir(root_name, NULL);
	if (IS_ERR(root)) {
		pr_err("cannot create debugfs root\n");
		return;
	}

	ks->debug_root = root;
	ks->debug_file = debugfs_create_file("state", 0444, root,
		ks, &state_fops);
	if (IS_ERR(ks->debug_file))
		pr_err("cannot create debugfs state file\n");
}

static void delete_debugfs(struct sw_priv *ks)
{
	debugfs_remove(ks->debug_file);
	debugfs_remove(ks->debug_root);
}

/* -------------------------------------------------------------------------- */

#define USE_SPEED_LINK
#define USE_MIB
#include "ksz_sw_sysfs_8895.c"

static irqreturn_t sw_interrupt(int irq, void *phy_dat)
{
	struct phy_device *phydev = phy_dat;
	struct sw_priv *ks = phydev->bus->priv;

	if (IRQF_TRIGGER_LOW == ks->intr_mode)
		disable_irq_nosync(irq);
	atomic_inc(&phydev->irq_disable);
	ks->sw.intr_using += 1;
	schedule_work(&phydev->phy_queue);

	return IRQ_HANDLED;
}  /* sw_interrupt */

static void sw_change(struct work_struct *work)
{
	struct phy_device *phydev =
		container_of(work, struct phy_device, phy_queue);
	struct sw_priv *ks = phydev->bus->priv;
	struct ksz_sw *sw = &ks->sw;
	SW_D status;

	mutex_lock(&ks->hwlock);
	mutex_lock(&ks->lock);
	sw->intr_using++;
	status = HW_R(ks, REG_INT_STATUS);
	status &= ks->intr_mask;
	if (status & ks->intr_mask) {
		sw->phy_intr = status;
		HW_W(ks, REG_INT_STATUS, status);
		status &= ~ks->intr_mask;
		schedule_delayed_work(&ks->link_read, 0);
		if (ks->intr_working & 0x80000000)
			ks->intr_working |= 1;
		ks->intr_working |= 0x80000000;
	} else
		ks->intr_working &= ~0x80000000;
	if (!(ks->intr_working & 0x80000000))
		ks->intr_working = 0;
	sw->intr_using--;
	mutex_unlock(&ks->lock);
	if (status) {
		mutex_lock(&ks->lock);
		HW_W(ks, REG_INT_STATUS, status);
		mutex_unlock(&ks->lock);
	}
	mutex_unlock(&ks->hwlock);
	sw->intr_using = 0;

	atomic_dec(&phydev->irq_disable);
	if (IRQF_TRIGGER_LOW == ks->intr_mode)
		enable_irq(ks->irq);
}  /* sw_change */

static int sw_start_interrupt(struct sw_priv *ks, const char *name)
{
	struct phy_device *phydev = ks->phydev;
	int err = 0;

	INIT_WORK(&phydev->phy_queue, sw_change);

	atomic_set(&phydev->irq_disable, 0);
	if (request_irq(ks->irq, sw_interrupt, ks->intr_mode, name,
			phydev) < 0) {
		printk(KERN_WARNING "%s: Can't get IRQ %d (PHY)\n",
			phydev->bus->name,
			ks->irq);
		phydev->irq = PHY_POLL;
		return 0;
	}

	return err;
}  /* sw_start_interrupt */

static void sw_stop_interrupt(struct sw_priv *ks)
{
	struct phy_device *phydev = ks->phydev;

	free_irq(ks->irq, phydev);
	cancel_work_sync(&phydev->phy_queue);
	while (atomic_dec_return(&phydev->irq_disable) >= 0)
		enable_irq(ks->irq);
}  /* sw_stop_interrupt */

/* -------------------------------------------------------------------------- */

#define KSZ8895_SW_ID		0x8895
#define PHY_ID_KSZ_SW		((KSZ8895_ID_HI << 16) | KSZ8895_SW_ID)

static int kszphy_config_init(struct phy_device *phydev)
{
	return 0;
}

static struct phy_driver kszsw_phy_driver = {
	.phy_id		= PHY_ID_KSZ_SW,
	.phy_id_mask	= 0x00ffffff,
	.name		= "Microchip KSZ8895 Switch",
	.features	= (PHY_BASIC_FEATURES | SUPPORTED_Pause),
	.flags		= PHY_HAS_MAGICANEG | PHY_HAS_INTERRUPT,
	.config_init	= kszphy_config_init,
	.config_aneg	= genphy_config_aneg,
	.read_status	= genphy_read_status,
	.driver		= { .owner = THIS_MODULE, },
};

/**
 * sw_r_phy - read data from PHY register
 * @sw:		The switch instance.
 * @phy:	PHY address to read.
 * @reg:	PHY register to read.
 * @val:	Buffer to store the read data.
 *
 * This routine reads data from the PHY register.
 */
static void sw_r_phy(struct ksz_sw *sw, u16 phy, u16 reg, u16 *val)
{
	u8 ctrl;
	u8 restart;
	u8 link;
	u8 speed;
	u8 force;
	u8 p = phy - 1;
	u16 data = 0;

	switch (reg) {
	case PHY_REG_CTRL:
		port_r(sw, p, P_LOCAL_CTRL, &ctrl);
		port_r(sw, p, P_NEG_RESTART_CTRL, &restart);
		port_r(sw, p, P_SPEED_STATUS, &speed);
		port_r(sw, p, P_FORCE_CTRL, &force);
		if (restart & PORT_PHY_LOOPBACK)
			data |= PHY_LOOPBACK;
		if (force & PORT_FORCE_100_MBIT)
			data |= PHY_SPEED_100MBIT;
		if (!(force & PORT_AUTO_NEG_DISABLE))
			data |= PHY_AUTO_NEG_ENABLE;
		if (restart & PORT_POWER_DOWN)
			data |= PHY_POWER_DOWN;
		if (restart & PORT_AUTO_NEG_RESTART)
			data |= PHY_AUTO_NEG_RESTART;
		if (force & PORT_FORCE_FULL_DUPLEX)
			data |= PHY_FULL_DUPLEX;
		if (speed & PORT_HP_MDIX)
			data |= PHY_HP_MDIX;
		if (restart & PORT_FORCE_MDIX)
			data |= PHY_FORCE_MDIX;
		if (restart & PORT_AUTO_MDIX_DISABLE)
			data |= PHY_AUTO_MDIX_DISABLE;
		if (restart & PORT_TX_DISABLE)
			data |= PHY_TRANSMIT_DISABLE;
		if (restart & PORT_LED_OFF)
			data |= PHY_LED_DISABLE;
		break;
	case PHY_REG_STATUS:
		port_r(sw, p, P_LINK_STATUS, &link);
		port_r(sw, p, P_SPEED_STATUS, &speed);
		data = PHY_100BTX_FD_CAPABLE |
			PHY_100BTX_CAPABLE |
			PHY_10BT_FD_CAPABLE |
			PHY_10BT_CAPABLE |
			PHY_AUTO_NEG_CAPABLE;
		if (link & PORT_AUTO_NEG_COMPLETE)
			data |= PHY_AUTO_NEG_ACKNOWLEDGE;
		if (link & PORT_STAT_LINK_GOOD)
			data |= PHY_LINK_STATUS;
		break;
	case PHY_REG_ID_1:
		data = KSZ8895_ID_HI;
		break;
	case PHY_REG_ID_2:
		/* Use unique switch id to differentiate from regular PHY. */
		data = KSZ8895_SW_ID;
		break;
	case PHY_REG_AUTO_NEGOTIATION:
		port_r(sw, p, P_LOCAL_CTRL, &ctrl);
		data = PHY_AUTO_NEG_802_3;
		if (ctrl & PORT_AUTO_NEG_SYM_PAUSE)
			data |= PHY_AUTO_NEG_SYM_PAUSE;
		if (ctrl & PORT_AUTO_NEG_100BTX_FD)
			data |= PHY_AUTO_NEG_100BTX_FD;
		if (ctrl & PORT_AUTO_NEG_100BTX)
			data |= PHY_AUTO_NEG_100BTX;
		if (ctrl & PORT_AUTO_NEG_10BT_FD)
			data |= PHY_AUTO_NEG_10BT_FD;
		if (ctrl & PORT_AUTO_NEG_10BT)
			data |= PHY_AUTO_NEG_10BT;
		break;
	case PHY_REG_REMOTE_CAPABILITY:
		port_r(sw, p, P_REMOTE_STATUS, &link);
		data = PHY_AUTO_NEG_802_3;
		if (link & PORT_REMOTE_SYM_PAUSE)
			data |= PHY_AUTO_NEG_SYM_PAUSE;
		if (link & PORT_REMOTE_100BTX_FD)
			data |= PHY_AUTO_NEG_100BTX_FD;
		if (link & PORT_REMOTE_100BTX)
			data |= PHY_AUTO_NEG_100BTX;
		if (link & PORT_REMOTE_10BT_FD)
			data |= PHY_AUTO_NEG_10BT_FD;
		if (link & PORT_REMOTE_10BT)
			data |= PHY_AUTO_NEG_10BT;
		break;
	default:
		break;
	}
	*val = data;
}  /* sw_r_phy */

/**
 * sw_w_phy - write data to PHY register
 * @hw:		The switch instance.
 * @phy:	PHY address to write.
 * @reg:	PHY register to write.
 * @val:	Word data to write.
 *
 * This routine writes data to the PHY register.
 */
static void sw_w_phy(struct ksz_sw *sw, u16 phy, u16 reg, u16 val)
{
	u8 ctrl;
	u8 restart;
	u8 speed;
	u8 data;
	u8 p = phy - 1;

	switch (reg) {
	case PHY_REG_CTRL:
		port_r(sw, p, P_SPEED_STATUS, &speed);
		data = speed;
		if (val & PHY_HP_MDIX)
			data |= PORT_HP_MDIX;
		else
			data &= ~PORT_HP_MDIX;
		if (data != speed)
			port_w(sw, p, P_SPEED_STATUS, data);
		port_r(sw, p, P_FORCE_CTRL, &ctrl);
		data = ctrl;
		if (!(val & PHY_AUTO_NEG_ENABLE))
			data |= PORT_AUTO_NEG_DISABLE;
		else
			data &= ~PORT_AUTO_NEG_DISABLE;
		if (val & PHY_SPEED_100MBIT)
			data |= PORT_FORCE_100_MBIT;
		else
			data &= ~PORT_FORCE_100_MBIT;
		if (val & PHY_FULL_DUPLEX)
			data |= PORT_FORCE_FULL_DUPLEX;
		else
			data &= ~PORT_FORCE_FULL_DUPLEX;
		if (data != ctrl)
			port_w(sw, p, P_FORCE_CTRL, data);
		port_r(sw, p, P_NEG_RESTART_CTRL, &restart);
		data = restart;
		if (val & PHY_LED_DISABLE)
			data |= PORT_LED_OFF;
		else
			data &= ~PORT_LED_OFF;
		if (val & PHY_TRANSMIT_DISABLE)
			data |= PORT_TX_DISABLE;
		else
			data &= ~PORT_TX_DISABLE;
		if (val & PHY_AUTO_NEG_RESTART)
			data |= PORT_AUTO_NEG_RESTART;
		else
			data &= ~(PORT_AUTO_NEG_RESTART);
		if (val & PHY_POWER_DOWN)
			data |= PORT_POWER_DOWN;
		else
			data &= ~PORT_POWER_DOWN;
		if (val & PHY_AUTO_MDIX_DISABLE)
			data |= PORT_AUTO_MDIX_DISABLE;
		else
			data &= ~PORT_AUTO_MDIX_DISABLE;
		if (val & PHY_FORCE_MDIX)
			data |= PORT_FORCE_MDIX;
		else
			data &= ~PORT_FORCE_MDIX;
		if (val & PHY_LOOPBACK)
			data |= PORT_PHY_LOOPBACK;
		else
			data &= ~PORT_PHY_LOOPBACK;
		if (data != restart)
			port_w(sw, p, P_NEG_RESTART_CTRL, data);
		break;
	case PHY_REG_AUTO_NEGOTIATION:
		port_r(sw, p, P_LOCAL_CTRL, &ctrl);
		data = ctrl;
		data &= ~(PORT_AUTO_NEG_SYM_PAUSE |
			PORT_AUTO_NEG_100BTX_FD |
			PORT_AUTO_NEG_100BTX |
			PORT_AUTO_NEG_10BT_FD |
			PORT_AUTO_NEG_10BT);
		if (val & PHY_AUTO_NEG_SYM_PAUSE)
			data |= PORT_AUTO_NEG_SYM_PAUSE;
		if (val & PHY_AUTO_NEG_100BTX_FD)
			data |= PORT_AUTO_NEG_100BTX_FD;
		if (val & PHY_AUTO_NEG_100BTX)
			data |= PORT_AUTO_NEG_100BTX;
		if (val & PHY_AUTO_NEG_10BT_FD)
			data |= PORT_AUTO_NEG_10BT_FD;
		if (val & PHY_AUTO_NEG_10BT)
			data |= PORT_AUTO_NEG_10BT;
		if (data != ctrl)
			port_w(sw, p, P_LOCAL_CTRL, data);
		break;
	default:
		break;
	}
}  /* sw_w_phy */

static int ksz_mii_addr(int *reg, int *bank)
{
	int ret;

	ret = (*reg & 0xC000) >> ADDR_SHIFT;
	*bank = (*reg & 0x3000) >> BANK_SHIFT;
	*reg &= 0x0FFF;
	return ret;
}

static int ksz_mii_read(struct mii_bus *bus, int phy_id, int regnum)
{
	struct sw_priv *ks = bus->priv;
	struct ksz_sw *sw = &ks->sw;
	int addr;
	int bank;
	u16 data;
	int ret = 0xffff;

	/* Last port can be a PHY. */
	if (phy_id > SWITCH_PORT_NUM + 1)
		return 0xffff;
	if (sw->first_port && 1 == phy_id)
		return 0xffff;

	addr = ksz_mii_addr(&regnum, &bank);

	mutex_lock(&ks->lock);
	switch (addr) {
	case ADDR_8:
		ret = HW_R8(ks, regnum);
		break;
	case ADDR_16:
		ret = HW_R16(ks, regnum);
		break;
	case ADDR_32:
		ret = HW_R32(ks, regnum);
		break;
	default:
		if (regnum < 6) {
			if (0 == phy_id)
				phy_id = ks->phy_id;
			else {
				int n;

				/*
				 * Get the represented PHY id when using
				 * multiple ports.
				 */
				for (n = 0; n < sw->eth_cnt; n++) {
					if (sw->eth_maps[n].port + 1 ==
					    phy_id) {
						phy_id = sw->eth_maps[n].phy_id;
						break;
					}
				}
			}

			sw_r_phy(&ks->sw, phy_id, regnum, &data);
			ret = data;
		} else
			ret = 0;
	}
	mutex_unlock(&ks->lock);
	return ret;
}  /* ksz_mii_read */

static int ksz_mii_write(struct mii_bus *bus, int phy_id, int regnum, u16 val)
{
	static int last_reg;
	static int last_val;
	struct sw_priv *ks = bus->priv;
	struct ksz_sw *sw = &ks->sw;
	int addr;
	int bank;
	int reg;

	/* Last port can be a PHY. */
	if (phy_id > SWITCH_PORT_NUM + 1)
		return -EINVAL;
	if (sw->first_port && 1 == phy_id)
		return -EINVAL;

	reg = regnum;
	addr = ksz_mii_addr(&regnum, &bank);

	mutex_lock(&ks->lock);
	switch (addr) {
	case ADDR_8:
		HW_W8(ks, regnum, val);
		break;
	case ADDR_16:
		HW_W16(ks, regnum, val);
		break;
	case ADDR_32:
		/*
		 * The phy_write interface allows only 16-bit value.  Break
		 * the 32-bit write into two calls for SPI efficiency.
		 */

		/* Previous write to high word. */
		if (last_reg == reg + 2) {
			last_val <<= 16;
			last_val |= val;
			HW_W32(ks, regnum, last_val);
			last_reg = 0;
		} else {
			/* Somebody has written to different address! */
			if (last_reg) {
				int last_bank;

				addr = ksz_mii_addr(&last_reg, &last_bank);
				HW_W16(ks, last_reg, last_val);
				last_reg = 0;
			}

			/* Cache the 16-bit write to high word. */
			if (reg & 3) {
				last_reg = reg;
				last_val = val;

			/* Did not find the previous write to high word.*/
			} else
				HW_W16(ks, regnum, val);
		}
		break;
	default:
		if (regnum < 6) {
			int i;
			int first;
			int last;

			if (0 == phy_id) {
				first = sw->ops->get_first_port(sw);
				last = first + sw->port_cnt;
			} else {
				int n;
				int f;
				int l;

				first = phy_id - 1;
				last = phy_id;
				for (n = 0; n < sw->eth_cnt; n++) {
					f = sw->eth_maps[n].port + 1;
					l = f + sw->eth_maps[n].cnt;
					if (f <= phy_id && phy_id < l) {
						first = sw->eth_maps[n].port;
						last = first +
							sw->eth_maps[n].cnt;
						break;
					}
				}
			}

			/* PHY device driver resets or powers down the PHY. */
			if (0 == regnum &&
			    (val & (PHY_RESET | PHY_POWER_DOWN)))
				break;
			for (i = first; i < last; i++) {
				sw_w_phy(sw, i + 1, regnum, val);
			}
			if (PHY_REG_CTRL == regnum &&
			    !(val & PHY_AUTO_NEG_ENABLE))
				schedule_delayed_work(&ks->link_read, 1);
		}
		break;
	}
	mutex_unlock(&ks->lock);
	return 0;
}  /* ksz_mii_write */

static int driver_installed;

static int ksz_mii_init(struct sw_priv *ks)
{
	struct platform_device *pdev;
	struct mii_bus *bus;
	int err;
	int i;

	pdev = platform_device_register_simple("Switch MII bus", ks->sw.id,
		NULL, 0);
	if (!pdev)
		return -ENOMEM;

	bus = mdiobus_alloc();
	if (bus == NULL) {
		err = -ENOMEM;
		goto mii_init_reg;
	}

	if (!driver_installed) {
		err = phy_driver_register(&kszsw_phy_driver);
		if (err)
			goto mii_init_free_mii_bus;
		driver_installed = true;
	}

	bus->name = "Switch MII bus",
	bus->read = ksz_mii_read;
	bus->write = ksz_mii_write;
	snprintf(bus->id, MII_BUS_ID_SIZE, "sw.%d", ks->sw.id);
	bus->parent = &pdev->dev;
	bus->phy_mask = ~((1 << (ks->sw.mib_port_cnt + 1)) - 1);
	bus->priv = ks;
	bus->irq = ks->bus_irqs;

	for (i = 0; i < PHY_MAX_ADDR; i++)
		bus->irq[i] = ks->irq;

	ks->phy_id = ks->sw.first_port + 1;
	err = mdiobus_register(bus);
	if (err < 0)
		goto mii_init_free_mii_bus;

	if (!bus->phy_map[0]) {
		printk(KERN_WARNING "No PHY detected\n");
		mdiobus_unregister(bus);
		err = -ENODEV;
		goto mii_init_free_mii_bus;
	}

	for (i = 0; i < PHY_MAX_ADDR; i++)
		if (bus->phy_map[i]) {
			struct phy_priv *phydata;
			struct ksz_port *port;
			int p = i;

			if (!p)
				p = 1;

			phydata = kzalloc(sizeof(struct phy_priv), GFP_KERNEL);
			if (!phydata) {
				err = -ENOMEM;
				goto mii_init_free_mii_bus;
			}
			port = &ks->ports[i];
			phydata->port = port;
			port->sw = &ks->sw;
			port->first_port = p - 1;
			port->port_cnt = 1;
			port->mib_port_cnt = 1;
			port->flow_ctrl = PHY_FLOW_CTRL;
			port->linked = &ks->sw.port_info[port->first_port];
			INIT_WORK(&port->link_update, link_update_work);
			phydata->state = bus->phy_map[i]->state;
			bus->phy_map[i]->priv = phydata;
		}

	ks->bus = bus;
	ks->pdev = pdev;
	ks->phydev = bus->phy_map[0];
	ks->phydev->interface = ks->sw.interface;

	/* The switch is always linked; speed and duplex are also fixed. */
	do {
		struct ksz_port_info *info =
			&ks->sw.port_info[ks->sw.HOST_PORT];

		ks->phydev->link = 1;
		ks->phydev->speed = info->tx_rate / TX_RATE_UNIT;
		ks->phydev->duplex = (info->duplex == 2);
		ks->phydev->pause = 1;
	} while (0);

	return 0;

mii_init_free_mii_bus:
	for (i = 0; i < PHY_MAX_ADDR; i++)
		if (bus->phy_map[i])
			kfree(bus->phy_map[i]->priv);
	if (driver_installed) {
		phy_driver_unregister(&kszsw_phy_driver);
		driver_installed = false;
	}
	mdiobus_free(bus);

mii_init_reg:
	platform_device_unregister(pdev);

	return err;
}  /* ksz_mii_init */

static void ksz_mii_exit(struct sw_priv *ks)
{
	int i;
	struct platform_device *pdev = ks->pdev;
	struct mii_bus *bus = ks->bus;

	if (ks->irq > 0) {
		mutex_lock(&ks->lock);
		HW_W(ks, REG_INT_ENABLE, 0);
		mutex_unlock(&ks->lock);
		sw_stop_interrupt(ks);
	}
	for (i = 0; i < PHY_MAX_ADDR; i++)
		if (bus->phy_map[i]) {
			struct ksz_port *port;

			port = & ks->ports[i];
			flush_work(&port->link_update);
			kfree(bus->phy_map[i]->priv);
		}
	mdiobus_unregister(bus);
	if (driver_installed) {
		phy_driver_unregister(&kszsw_phy_driver);
		driver_installed = false;
	}
	mdiobus_free(bus);
	platform_device_unregister(pdev);
}  /* ksz_mii_exit */

/* driver bus management functions */

static void determine_rate(struct ksz_sw *sw, struct ksz_port_mib *mib)
{
	int j;

	for (j = 0; j < 2; j++) {
		if (mib->rate[j].last) {
			int offset;
			u64 cnt;
			u64 last_cnt;
			unsigned long diff = jiffies - mib->rate[j].last;

			if (0 == j)
				offset = MIB_RX_LO_PRIO;
			else
				offset = MIB_TX_LO_PRIO;
			cnt = mib->counter[offset] + mib->counter[offset + 1];
			last_cnt = cnt;
			cnt -= mib->rate[j].last_cnt;
			if (cnt > 1000000 && diff >= 100) {
				u32 rem;
				u64 rate = cnt;

				rate *= 8;
				diff *= 10 * 100;
				rate = div_u64_rem(rate, diff, &rem);
				mib->rate[j].last = jiffies;
				mib->rate[j].last_cnt = last_cnt;
				if (mib->rate[j].peak < (u32) rate)
					mib->rate[j].peak = (u32) rate;
			}
		} else
			mib->rate[j].last = jiffies;
	}
}  /* determine_rate */

static void ksz8895_mib_read_work(struct work_struct *work)
{
	struct sw_priv *hw_priv =
		container_of(work, struct sw_priv, mib_read);
	struct ksz_sw *sw = &hw_priv->sw;
	struct ksz_port_mib *mib;
	int i;
	int p = sw->ops->get_first_port(sw);

	next_jiffies = jiffies;
	for (i = p; i < sw->mib_port_cnt; i++) {
		i = chk_last_port(sw, i);
		mib = &sw->port_mib[i];

		/* Reading MIB counters or requested to read. */
		if (mib->cnt_ptr || 1 == hw_priv->counter[i].read) {

			/* Need to process interrupt. */
			if (port_r_cnt(sw, i))
				return;
			hw_priv->counter[i].read = 0;

			/* Finish reading counters. */
			if (0 == mib->cnt_ptr) {
				hw_priv->counter[i].read = 2;
				wake_up_interruptible(
					&hw_priv->counter[i].counter);
				if (i != sw->HOST_PORT)
					determine_rate(sw, mib);
			}
		} else if (jiffies >= hw_priv->counter[i].time) {
			/* Only read MIB counters when the port is connected. */
			if (media_connected == sw->port_state[i].state ||
			    i == sw->HOST_PORT)
				hw_priv->counter[i].read = 1;

			/* Read the dropped counters. */
			else
				mib->cnt_ptr = SWITCH_COUNTER_NUM;
			next_jiffies += MIB_READ_INTERVAL * sw->mib_port_cnt;
			if (sw->port_cnt < sw->mib_port_cnt)
				next_jiffies -= MIB_READ_INTERVAL;
			hw_priv->counter[i].time = next_jiffies;

		/* Port is just disconnected. */
		} else if (sw->port_state[i].link_down) {
			int j;

			for (j = 0; j < TOTAL_SWITCH_COUNTER_NUM; j++)
				mib->read_cnt[j] += mib->read_max[j];
			sw->port_state[i].link_down = 0;

			/* Read counters one last time after link is lost. */
			hw_priv->counter[i].read = 1;
		}
	}
}  /* ksz8895_mib_read_work */

static void copy_port_status(struct ksz_port *src, struct ksz_port *dst)
{
	dst->duplex = src->duplex;
	dst->speed = src->speed;
	dst->force_link = src->force_link;
	dst->linked = src->linked;
}

static void link_read_work(struct work_struct *work)
{
	struct delayed_work *dwork = to_delayed_work(work);
	struct sw_priv *hw_priv =
		container_of(dwork, struct sw_priv, link_read);
	struct ksz_sw *sw = &hw_priv->sw;
	struct phy_device *phydev;
	struct ksz_port *port = NULL;
	struct ksz_port *sw_port = NULL;
	int i;
	int changes = 0;
	int p = sw->ops->get_first_port(sw);
	int s = 1;

	if (1 == sw->dev_count || 1 == sw->dev_offset)
		s = 0;
	if (sw->dev_offset) {
		struct phy_priv *phydata;
		struct net_device *dev = sw->netdev[0];

		phydev = sw->phydev;
		phydata = phydev->priv;
		if (dev && sw->net_ops->get_priv_port)
			sw_port = sw->net_ops->get_priv_port(dev);
		else
			sw_port = phydata->port;
	}
	sw->ops->acquire(sw);
	if (!sw->phy_intr) {
		sw->phy_intr = HW_R(hw_priv, REG_INT_STATUS);
		if (sw->phy_intr)
			HW_W(hw_priv, REG_INT_STATUS, sw->phy_intr);
	}
	for (i = sw->dev_offset; i < sw->dev_count + sw->dev_offset; i++) {
		int n;
		struct phy_priv *phydata;
		struct net_device *dev = sw->netdev[i];

		n = i + s;
		if (n >= p)
			n += p;
		phydev = sw->phy[n];
		if (sw->features & SW_VLAN_DEV)
			phydev = sw->phy[sw->eth_maps[i].port + 1];
		phydata = phydev->priv;
		if (dev && sw->net_ops->get_priv_port)
			port = sw->net_ops->get_priv_port(dev);
		else
			port = phydata->port;
		changes |= port_get_link_speed(port);

		/* Copy all port information for user access. */
		if (port != phydata->port) {
			copy_port_status(port, phydata->port);
			if (phydata != hw_priv->phydev->priv) {
				phydata = hw_priv->phydev->priv;
				copy_port_status(port, phydata->port);
			}
		}
	}
	do {
		struct phy_priv *phydata;

		phydev = sw->phy[SWITCH_PORT_NUM + 1];
		phydata = phydev->priv;
		port = phydata->port;
		port_get_link_speed(port);
	} while (0);
	sw->phy_intr = 0;
	sw->ops->release(sw);

	if (!sw->dev_offset || (media_connected == sw_port->linked->state))
		changes = 0;

	/* Not to read PHY registers unnecessarily if no link change. */
	if (!changes)
		return;

	for (i = sw->dev_offset; i < sw->dev_count + sw->dev_offset; i++) {
		int n;
		struct phy_priv *phydata;
		struct net_device *dev = sw->netdev[i];

		n = i + s;
		if (n >= p)
			n += p;
		phydev = sw->phy[n];
		if (sw->features & SW_VLAN_DEV)
			phydev = sw->phy[sw->eth_maps[i].port + 1];
		phydata = phydev->priv;
		if (dev && sw->net_ops->get_priv_port)
			port = sw->net_ops->get_priv_port(dev);
		else
			port = phydata->port;
		if (media_connected == port->linked->state) {
			sw_port->linked = port->linked;
			hw_priv->phy_id = port->linked->phy_id;
			break;
		}
	}
}  /* link_read_work */

/*
 * Hardware monitoring
 */

static void ksz8895_mib_monitor(unsigned long ptr)
{
	struct sw_priv *hw_priv = (struct sw_priv *) ptr;

	schedule_work(&hw_priv->mib_read);

	ksz_update_timer(&hw_priv->mib_timer_info);
}  /* ksz8895_mib_monitor */

static void ksz8895_dev_monitor(unsigned long ptr)
{
	struct sw_priv *hw_priv = (struct sw_priv *) ptr;
	struct phy_device *phydev;
	struct phy_priv *priv;
	int i;

	/* For MAC driver that does not add code to device open function. */
	for (i = 0; i <= TOTAL_PORT_NUM; i++) {
		phydev = hw_priv->bus->phy_map[i];
		if (!phydev)
			continue;
		priv = phydev->priv;
		if (priv->state != phydev->state) {
			priv->state = phydev->state;
			if (PHY_UP == phydev->state ||
			    PHY_RESUMING == phydev->state)
				schedule_work(&priv->port->link_update);
		}
	}
	if (!(hw_priv->intr_working & 1))
		schedule_delayed_work(&hw_priv->link_read, 0);

	ksz_update_timer(&hw_priv->monitor_timer_info);
}  /* ksz8895_dev_monitor */

#ifdef CONFIG_NET_DSA_TAG_TAIL
#include "ksz_dsa.c"
#endif

static int intr_mode;
static int rx_1msg;
static int spi_bus;

#define MAX_SPI_DEVICES		2

static int sw_device_present;

static int ksz8895_probe(struct spi_device *spi)
{
	struct spi_hw_priv *hw_priv;
	struct sw_priv *ks;
	struct ksz_sw *sw;
	struct ksz_port *port;
	struct phy_device *phydev;
	struct phy_priv *priv;
	u16 id;
	u8 id1;
	u8 id2;
	int i;
	int mib_port_count;
	int pi;
	int port_count;
	int ret;

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

	/* initialise pre-made spi transfer messages */

	spi_message_init(&hw_priv->spi_msg1);
	spi_message_add_tail(&hw_priv->spi_xfer1, &hw_priv->spi_msg1);

	spi_message_init(&hw_priv->spi_msg2);
	spi_message_add_tail(&hw_priv->spi_xfer2[0], &hw_priv->spi_msg2);
	spi_message_add_tail(&hw_priv->spi_xfer2[1], &hw_priv->spi_msg2);

	ks->intr_mode = intr_mode ? IRQF_TRIGGER_FALLING :
		IRQF_TRIGGER_LOW;
	ks->irq = spi->irq;
	ks->dev = &spi->dev;

	dev_set_drvdata(ks->dev, ks);

	mutex_init(&ks->hwlock);
	mutex_init(&ks->lock);

	/* simple check for a valid chip being connected to the bus */
	mutex_lock(&ks->lock);
	id = HW_R16(ks, REG_CHIP_ID0);
	mutex_unlock(&ks->lock);
	id1 = id >> 8;
	id2 = id & SW_CHIP_ID_M;
	if (id1 != FAMILY_ID ||
	    (id2 != CHIP_ID_95 && id2 != CHIP_ID_95R)) {
		dev_err(ks->dev, "failed to read device ID(0x%x)\n", id);
		ret = -ENODEV;
		goto err_sw;
	}
	dev_info(ks->dev, "chip id 0x%x\n", id);

	sw = &ks->sw;
	mutex_init(&sw->lock);
	sw->hwlock = &ks->hwlock;
	sw->reglock = &ks->lock;

	sw->dev_count = 1;

	port_count = SWITCH_PORT_NUM;
	mib_port_count = TOTAL_PORT_NUM;
	sw->HOST_PORT = mib_port_count - 1;
	sw->HOST_MASK = (1 << sw->HOST_PORT);

	mutex_lock(&ks->lock);
	id2 = HW_R(ks, REG_KSZ8864_CHIP_ID);
	mutex_unlock(&ks->lock);
	if (id2 & SW_KSZ8864) {
		port_count--;
		sw->first_port = 1;
		sw->features |= SKIP_FIRST_PORT;
	}
	sw->port_cnt = port_count;
	sw->mib_port_cnt = mib_port_count;
	sw->PORT_MASK = (1 << port_count) - 1;
	sw->PORT_MASK <<= sw->first_port;
	sw->PORT_MASK |= sw->HOST_MASK;

	sw->mib_cnt = TOTAL_SWITCH_COUNTER_NUM;

	sw->dev = ks;
	sw->id = sw_device_present;

	sw->info = kzalloc(sizeof(struct ksz_sw_info), GFP_KERNEL);
	if (!sw->info) {
		ret = -ENOMEM;
		goto err_sw;
	}

	sw->reg = &sw_reg_ops;
	sw->net_ops = &sw_net_ops;
	sw->ops = &sw_ops;

	init_waitqueue_head(&sw->queue);
	INIT_DELAYED_WORK(&ks->link_read, link_read_work);

	for (pi = 0; pi < SWITCH_PORT_NUM; pi++) {
		/*
		 * Initialize to invalid value so that link detection
		 * is done.
		 */
		sw->port_info[pi].link = 0xFF;
		sw->port_info[pi].state = media_disconnected;
		sw->port_info[pi].report = true;
		sw->port_info[pi].phy_id = pi + 1;
	}
	sw->interface = PHY_INTERFACE_MODE_MII;
	pi = sw->HOST_PORT;
	sw->port_info[pi].phy_id = pi + 1;
	sw->port_info[pi].tx_rate = 100 * TX_RATE_UNIT;
	sw->port_info[pi].duplex = 2;
	sw->port_info[pi].flow_ctrl = 0x33;

	ret = ksz_mii_init(ks);
	if (ret)
		goto err_mii;

	sw->multi_dev |= multi_dev;
	sw->stp |= stp;
	sw->fast_aging |= fast_aging;
	sw_setup_zone(sw);

	sw->phydev = ks->phydev;
	sw->counter = ks->counter;
	sw->monitor_timer_info = &ks->monitor_timer_info;
	sw->link_read = &ks->link_read;

	sw_init_mib(sw);

	for (i = 0; i < TOTAL_PORT_NUM; i++)
		init_waitqueue_head(&ks->counter[i].counter);

	create_debugfs(ks);

#ifdef CONFIG_KSZ_STP
	ksz_stp_init(&sw->info->rstp, sw);
#endif
#ifdef CONFIG_KSZ_HSR
	if (sw->features & HSR_HW)
		ksz_hsr_init(&sw->info->hsr, sw);
#endif
	sw->ops->acquire(sw);
	sw_reset(sw);
	sw_init(sw);
	sw_setup(sw);
	sw_enable(sw);
	sw->ops->release(sw);
	sw->ops->init(sw);

#ifndef CONFIG_KSZ8895_EMBEDDED
	init_sw_sysfs(sw, &ks->sysfs, ks->dev);
#endif
	ret = sysfs_create_bin_file(&ks->dev->kobj,
		&kszsw_registers_attr);
	sema_init(&ks->proc_sem, 1);

	for (i = 0; i <= SWITCH_PORT_NUM + 1; i++) {
		sw->phy[i] = ks->bus->phy_map[i];
	}

	/* User ports does not include host port. */
	mib_port_count = port_count;
	phydev = sw->phy[0];
	priv = phydev->priv;
	port = priv->port;
	port->port_cnt = port_count;
	port->mib_port_cnt = mib_port_count;
	port->flow_ctrl = PHY_FLOW_CTRL;

	INIT_WORK(&ks->mib_read, ksz8895_mib_read_work);

	/* 500 ms timeout */
	ksz_init_timer(&ks->mib_timer_info, 500 * HZ / 1000,
		ksz8895_mib_monitor, ks);
	ksz_init_timer(&ks->monitor_timer_info, 100 * HZ / 1000,
		ksz8895_dev_monitor, ks);

	ksz_start_timer(&ks->mib_timer_info, ks->mib_timer_info.period);
	if (sw->multi_dev < 3 && !sw->stp)
		ksz_start_timer(&ks->monitor_timer_info,
			ks->monitor_timer_info.period * 10);

	sw_device_present++;

#ifdef CONFIG_NET_DSA_TAG_TAIL
	ksz_dsa_init();
#endif

	if (ks->irq <= 0)
		return 0;
	ks->intr_mask = INT_PORT_1 | INT_PORT_2 |
		INT_PORT_3 | INT_PORT_4 | INT_PORT_5;
	mutex_lock(&ks->lock);
	HW_W(ks, REG_INT_ENABLE, 0);
	HW_W(ks, REG_INT_STATUS, ks->intr_mask);
	mutex_unlock(&ks->lock);
	ret = sw_start_interrupt(ks, dev_name(ks->dev));
	if (ret < 0)
		printk(KERN_WARNING "No switch interrupt\n");
	else {
		mutex_lock(&ks->lock);
		HW_W(ks, REG_INT_ENABLE, ks->intr_mask);
		mutex_unlock(&ks->lock);
	}

	return 0;

err_mii:
	kfree(sw->info);

err_sw:
	kfree(ks->hw_dev);
	kfree(ks);

	return ret;
}

static int ksz8895_remove(struct spi_device *spi)
{
	struct sw_priv *ks = dev_get_drvdata(&spi->dev);
	struct ksz_sw *sw = &ks->sw;

#ifdef CONFIG_NET_DSA_TAG_TAIL
	ksz_dsa_cleanup();
#endif
	ksz_mii_exit(ks);
	ksz_stop_timer(&ks->monitor_timer_info);
	ksz_stop_timer(&ks->mib_timer_info);
	flush_work(&ks->mib_read);

	sysfs_remove_bin_file(&ks->dev->kobj, &kszsw_registers_attr);

#ifndef CONFIG_KSZ8895_EMBEDDED
	exit_sw_sysfs(sw, &ks->sysfs, ks->dev);
#endif
	sw->ops->exit(sw);
	cancel_delayed_work_sync(&ks->link_read);

	delete_debugfs(ks);

#ifdef CONFIG_KSZ_STP
	ksz_stp_exit(&sw->info->rstp);
#endif
	kfree(sw->info);
	kfree(ks->hw_dev);
	kfree(ks);

	return 0;
}

static const struct of_device_id ksz8895_dt_ids[] = {
	{ .compatible = "microchip,ksz8895" },
	{},
};
MODULE_DEVICE_TABLE(of, ksz8895_dt_ids);

static struct spi_driver ksz8895_driver = {
	.driver = {
		.name = KS8895_DEV,
		.owner = THIS_MODULE,
		.of_match_table = of_match_ptr(ksz8895_dt_ids),
	},
	.probe = ksz8895_probe,
	.remove = ksz8895_remove,
};

static int __init ksz8895_init(void)
{
	return spi_register_driver(&ksz8895_driver);
}

static void __exit ksz8895_exit(void)
{
	spi_unregister_driver(&ksz8895_driver);
}

#ifndef CONFIG_KSZ8895_EMBEDDED
subsys_initcall(ksz8895_init);
module_exit(ksz8895_exit);

module_param(fast_aging, int, 0);
module_param(multi_dev, int, 0);
module_param(stp, int, 0);
MODULE_PARM_DESC(fast_aging, "Fast aging");
MODULE_PARM_DESC(multi_dev, "Multiple device interfaces");
MODULE_PARM_DESC(stp, "STP support");
#endif

module_param(intr_mode, int, 0);
MODULE_PARM_DESC(intr_mode,
	"Configure which interrupt mode to use(0=level low, 1=falling)");

module_param(rx_1msg, int, 0);
MODULE_PARM_DESC(rx_1msg,
	"Configure whether receive one message is used");

module_param(spi_bus, int, 0);
MODULE_PARM_DESC(spi_bus,
	"Configure which spi master to use(0=KSZ8692, 2=FTDI)");

module_param(eth1_ports, int, 0);
module_param(eth2_ports, int, 0);
module_param(eth3_ports, int, 0);
module_param(eth4_ports, int, 0);
MODULE_PARM_DESC(eth1_ports, "Ports to use on device 1.");
MODULE_PARM_DESC(eth2_ports, "Ports to use on device 2.");
MODULE_PARM_DESC(eth3_ports, "Ports to use on device 3.");
MODULE_PARM_DESC(eth4_ports, "Ports to use on device 4.");

module_param(eth1_vlan, int, 0);
module_param(eth2_vlan, int, 0);
module_param(eth3_vlan, int, 0);
module_param(eth4_vlan, int, 0);
MODULE_PARM_DESC(eth1_vlan, "VLAN to use on device 1.");
MODULE_PARM_DESC(eth2_vlan, "VLAN to use on device 2.");
MODULE_PARM_DESC(eth3_vlan, "VLAN to use on device 3.");
MODULE_PARM_DESC(eth4_vlan, "VLAN to use on device 4.");

module_param(eth1_proto, charp, 0);
module_param(eth2_proto, charp, 0);
module_param(eth3_proto, charp, 0);
module_param(eth4_proto, charp, 0);
MODULE_PARM_DESC(eth1_proto, "Protocol to use on device 1.");
MODULE_PARM_DESC(eth2_proto, "Protocol to use on device 2.");
MODULE_PARM_DESC(eth3_proto, "Protocol to use on device 3.");
MODULE_PARM_DESC(eth4_proto, "Protocol to use on device 4.");

#ifndef CONFIG_KSZ8895_EMBEDDED
MODULE_DESCRIPTION("KSZ8895 switch driver");
MODULE_AUTHOR("Tristram Ha <Tristram.Ha@microchip.com>");
MODULE_LICENSE("GPL");

MODULE_ALIAS("spi:ksz8895");
#endif
