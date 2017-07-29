/**
 * Micrel KSZ9897 I2C driver
 *
 * Copyright (c) 2015-2016 Microchip Technology Inc.
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

#ifndef CONFIG_MICREL_SWITCH_EMBEDDED
#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/interrupt.h>
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
#include <linux/i2c.h>
#include <linux/debugfs.h>
#include <linux/seq_file.h>
#include "ksz_cfg_9897.h"

#if 0
#define NO_ACL
#endif

#if 1
#define NO_EEE
#endif

#ifdef KSZ_DLR
/* Have ACL to handle beacon timeout. */
#define CONFIG_HAVE_ACL_HW

/* Have DLR to transmit beacons. */
#define CONFIG_HAVE_DLR_HW
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

/* -------------------------------------------------------------------------- */

#define HW_R(ks, reg)		i2c_rdreg8(ks, reg)
#define HW_W(ks, reg, val)	i2c_wrreg8(ks, reg, val)
#define HW_R8(ks, reg)		i2c_rdreg8(ks, reg)
#define HW_W8(ks, reg, val)	i2c_wrreg8(ks, reg, val)
#define HW_R16(ks, reg)		i2c_rdreg16(ks, reg)
#define HW_W16(ks, reg, val)	i2c_wrreg16(ks, reg, val)
#define HW_R24(ks, reg)		i2c_rdreg24(ks, reg)
#define HW_W24(ks, reg, val)	i2c_wrreg24(ks, reg, val)
#define HW_R32(ks, reg)		i2c_rdreg32(ks, reg)
#define HW_W32(ks, reg, val)	i2c_wrreg32(ks, reg, val)

#include "ksz_sw_phy.h"

#include "ksz_spi_net.h"

/* -------------------------------------------------------------------------- */

#define contain_reg(addr, len, reg)	\
	(addr <= (reg) && (reg) <= (addr + len - 1))

static void i2c_chk_regs(struct ksz_sw *sw, u32 addr, u8 *val, size_t txl)
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
}  /* i2c_chk_regs */

/*
 * I2C register read/write calls.
 *
 * All these calls issue I2C transactions to access the chip's registers. They
 * all require that the necessary lock is held to prevent accesses when the
 * chip is busy transfering packet data (RX/TX FIFO accesses).
 */

/**
 * i2c_wrreg - issue write register command
 * @ks:		The switch device structure.
 * @addr:	The register address.
 * @val:	The value to write.
 * @txl:	The length of data.
 *
 * This is the low level write call that issues the necessary i2c message(s)
 * to write data to the register specified in @addr.
 */
static void i2c_wrreg(struct sw_priv *ks, u32 addr, void *txb, size_t txl)
{
	struct i2c_hw_priv *hw_priv = ks->hw_dev;
	struct i2c_msg msg;
	struct i2c_client *i2c = hw_priv->i2cdev;
	struct i2c_adapter *adapter = i2c->adapter;

	if (!mutex_is_locked(&ks->lock))
		pr_alert("W not locked\n");

	hw_priv->txd[0] = (u8)(addr >> 8);
	hw_priv->txd[1] = (u8) addr;

	memcpy(&hw_priv->txd[2], txb, txl);

	msg.addr = i2c->addr;
	msg.flags = 0;
	msg.len = 2 + txl;
	msg.buf = hw_priv->txd;

	if (i2c_transfer(adapter, &msg, 1) != 1)
		pr_alert("i2c_transfer() failed\n");
	i2c_chk_regs(&ks->sw, addr, txb, txl);
}

/**
 * i2c_wrreg32 - write 32bit register value to chip
 * @ks:		The switch device structure.
 * @reg:	The register address.
 * @val:	The value to write.
 *
 * Issue a write to put the value @val into the register specified in @reg.
 */
static void i2c_wrreg32(struct sw_priv *ks, u32 reg, u32 val)
{
	u8 txb[4];
	int i = 0;
	size_t cnt = 4;

	do {
		txb[i++] = (u8)(val >> (8 * (cnt - 1)));
		cnt--;
	} while (cnt);
	i2c_wrreg(ks, reg, txb, 4);
}

/**
 * i2c_wrreg24 - write 24bit register value to chip
 * @ks:		The switch device structure.
 * @reg:	The register address.
 * @val:	The value to write.
 *
 * Issue a write to put the value @val into the register specified in @reg.
 */
static void i2c_wrreg24(struct sw_priv *ks, u32 reg, u32 val)
{
	u8 txb[4];
	int i = 0;
	size_t cnt = 3;

	do {
		txb[i++] = (u8)(val >> (8 * (cnt - 1)));
		cnt--;
	} while (cnt);
	i2c_wrreg(ks, reg, txb, 3);
}

/**
 * i2c_wrreg16 - write 16bit register value to chip
 * @ks:		The switch device structure.
 * @reg:	The register address.
 * @val:	The value to write.
 *
 * Issue a write to put the value @val into the register specified in @reg.
 */
static void i2c_wrreg16(struct sw_priv *ks, u32 reg, u32 val)
{
	u8 txb[4];
	int i = 0;
	size_t cnt = 2;

	do {
		txb[i++] = (u8)(val >> (8 * (cnt - 1)));
		cnt--;
	} while (cnt);
	i2c_wrreg(ks, reg, txb, 2);
}

/**
 * i2c_wrreg8 - write 8bit register value to chip
 * @ks:		The switch device structure.
 * @reg:	The register address.
 * @val:	The value to write.
 *
 * Issue a write to put the value @val into the register specified in @reg.
 */
static void i2c_wrreg8(struct sw_priv *ks, u32 reg, u32 val)
{
	u8 txb[4];
	int i = 0;
	size_t cnt = 1;

	do {
		txb[i++] = (u8)(val >> (8 * (cnt - 1)));
		cnt--;
	} while (cnt);
	i2c_wrreg(ks, reg, txb, 1);
}

/**
 * i2c_rdreg - issue read register command and return the data
 * @ks:		The switch device structure.
 * @reg:	The register address.
 * @rxb:	The RX buffer to return the result into.
 * @rxl:	The length of data expected.
 *
 * This is the low level read call that issues the necessary i2c message(s)
 * to read data from the register specified in @op.
 */
static void i2c_rdreg(struct sw_priv *ks, u32 addr, void *rxb, size_t rxl)
{
	struct i2c_hw_priv *hw_priv = ks->hw_dev;
	struct i2c_msg msg[2];
	struct i2c_client *i2c = hw_priv->i2cdev;
	struct i2c_adapter *adapter = i2c->adapter;

	if (!mutex_is_locked(&ks->lock))
		pr_alert("R not locked\n");

	hw_priv->txd[0] = (u8)(addr >> 8);
	hw_priv->txd[1] = (u8) addr;

	msg[0].addr = i2c->addr;
	msg[0].flags = 0;
	msg[0].len = 2;
	msg[0].buf = hw_priv->txd;

	msg[1].addr = i2c->addr;
	msg[1].flags = I2C_M_RD;
	msg[1].len = rxl;
	msg[1].buf = rxb;

	if (i2c_transfer(adapter, msg, 2) != 2)
		pr_alert("i2c_transfer() failed\n");
}

/**
 * i2c_rdreg8 - read 8 bit register from device
 * @ks:		The switch device structure.
 * @reg:	The register address.
 *
 * Read a 8bit register from the chip, returning the result.
 */
static u8 i2c_rdreg8(struct sw_priv *ks, u32 reg)
{
	u8 rxb[1];

	i2c_rdreg(ks, reg, rxb, 1);
	return rxb[0];
}

/**
 * i2c_rdreg16 - read 16 bit register from device
 * @ks:		The switch device structure.
 * @reg:	The register address.
 *
 * Read a 16bit register from the chip, returning the result.
 */
static u16 i2c_rdreg16(struct sw_priv *ks, u32 reg)
{
	__le16 rx = 0;

	i2c_rdreg(ks, reg, &rx, 2);
	return be16_to_cpu(rx);
}

/**
 * i2c_rdreg24 - read 24 bit register from device
 * @ks:		The switch device structure.
 * @reg:	The register address.
 *
 * Read a 24bit register from the chip.
 */
static u32 i2c_rdreg24(struct sw_priv *ks, u32 reg)
{
	__le32 rx = 0;

	i2c_rdreg(ks, reg, &rx, 3);
	return be32_to_cpu(rx);
}

/**
 * i2c_rdreg32 - read 32 bit register from device
 * @ks:		The switch device structure.
 * @reg:	The register address.
 *
 * Read a 32bit register from the chip.
 */
static u32 i2c_rdreg32(struct sw_priv *ks, u32 reg)
{
	__le32 rx = 0;

	i2c_rdreg(ks, reg, &rx, 4);
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

#include "ksz_common.c"

/* For ksz_request used by PTP or MRP driver. */
#include "ksz_req.c"

#ifndef CONFIG_MICREL_SWITCH_EMBEDDED
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
printk(KERN_ALERT "%s changed\n", __func__);
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
	i2c_rdreg(sw->dev, reg, buf, cnt);
}

static void sw_w(struct ksz_sw *sw, unsigned reg, void *buf, size_t cnt)
{
	i2c_wrreg(sw->dev, reg, buf, cnt);
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

static void sw_port_r16(struct ksz_sw *sw, int port, int offset, u16 *data)
{
	u32 addr;

	addr = PORT_CTRL_ADDR(port, offset);
	*data = sw_r16(sw, addr);
}  /* sw_port_r16 */

static void sw_port_w16(struct ksz_sw *sw, int port, int offset, u16 data)
{
	u32 addr;

	addr = PORT_CTRL_ADDR(port, offset);
	sw_w16(sw, addr, data);
}  /* sw_port_w16 */

#ifdef CONFIG_KSZ_STP
static u8 get_port_state(struct net_device *dev, struct net_device **br_dev)
{
	struct net_bridge_port *p;
	u8 state;

	/* This state is not defined in kernel. */
	state = STP_STATE_SIMPLE;
	if (br_port_exists(dev)) {
		p = br_port_get_rcu(dev);
		state = p->state;

		/* Port is under bridge. */
		*br_dev = p->br->dev;
	}
	return state;
}  /* get_port_state */
#endif

static void link_update_work(struct work_struct *work)
{
	struct ksz_port *port =
		container_of(work, struct ksz_port, link_update);
	struct ksz_sw *sw = port->sw;
	struct phy_device *phydev;
	int i;
	int link;

#ifdef KSZ_DLR
	if (sw->features & DLR_HW) {
		struct ksz_dlr_info *dlr = &sw->info->dlr;

		dlr->ops->link_change(dlr,
			sw->port_info[dlr->ports[0]].state == media_connected,
			sw->port_info[dlr->ports[1]].state == media_connected);
	}
#endif

	/* This only matters when one phy device is used for the switch. */
	if (1 == sw->dev_count) {
		struct sw_priv *hw_priv = container_of(sw, struct sw_priv, sw);

		for (i = 0; i < sw->mib_port_cnt; i++) {
			if (i == sw->HOST_PORT)
				continue;
			if (port->linked == &sw->port_info[i]) {
				hw_priv->phy_id = i + 1;
				break;
			}
		}
	}
	for (i = 0; i < sw->phy_port_cnt; i++) {
		struct ksz_port_info *info = &sw->port_info[i];

		if (!info->report)
			continue;
		info->report = false;
		phydev = sw->phy[i + 1];
		if (i == sw->HOST_PORT)
			phydev = sw->phydev;
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
			if (phydev->adjust_link)
				phydev->adjust_link(phydev->attached_dev);
		}
	}

	/* The switch is always linked; speed and duplex are also fixed. */
	if (sw->HOST_PORT >= sw->phy_port_cnt) {
		struct ksz_port_info *info = &sw->port_info[sw->HOST_PORT];
		int phy_link;

		phydev = sw->phydev;
		phydev->link = (info->state == media_connected);
		phy_link = phydev->link;
		if (!sw->need_link_up &&
		    (1 == sw->dev_count || 1 == sw->dev_offset))
			phy_link = (port->linked->state == media_connected);
		phydev->speed = info->tx_rate / TX_RATE_UNIT;
		phydev->duplex = (info->duplex == 2);
		if (phydev->attached_dev) {
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
	}
}  /* link_update_work */

static void sw_dis_intr(struct ksz_sw *sw);
static void sw_ena_intr(struct ksz_sw *sw);

#define USE_DIFF_PORT_PRIORITY
#include "ksz_sw_9897.c"

static void sw_dis_intr(struct ksz_sw *sw)
{
	HW_W32(sw->dev, REG_SW_INT_MASK__4, SWITCH_INT_MASK);
	HW_W32(sw->dev, REG_SW_PORT_INT_MASK__4, sw->PORT_MASK);
}  /* sw_dis_intr */

static void sw_ena_intr(struct ksz_sw *sw)
{
	int i;

	HW_W32(sw->dev, REG_SW_INT_MASK__4,
		~sw->intr_mask & SWITCH_INT_MASK);
	HW_W32(sw->dev, REG_SW_PORT_INT_MASK__4,
		~sw->port_intr_mask & sw->PORT_MASK);
	for (i = 0; i < sw->mib_port_cnt; i++)
		port_w(sw, i, REG_PORT_INT_MASK,
			~sw->info->port_cfg[i].intr_mask & PORT_INT_MASK);
}  /* sw_ena_intr */

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

	snprintf(root_name, sizeof(root_name), "i2c_%s",
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
#include "ksz_sw_sysfs_9897.c"
#ifdef CONFIG_1588_PTP
#include "ksz_ptp_sysfs.c"
#endif
#ifdef KSZ_DLR
#include "ksz_dlr_sysfs.c"
#endif

static irqreturn_t sw_interrupt(int irq, void *phy_dat)
{
	struct phy_device *phydev = phy_dat;
	struct sw_priv *ks = phydev->bus->priv;

	if (IRQF_TRIGGER_LOW == ks->intr_mode)
		disable_irq_nosync(irq);
	atomic_inc(&phydev->irq_disable);
	ks->sw.intr_using = 1;
	schedule_work(&phydev->phy_queue);

	return IRQ_HANDLED;
}  /* sw_interrupt */

static void sw_change(struct work_struct *work)
{
	struct phy_device *phydev =
		container_of(work, struct phy_device, phy_queue);
	struct sw_priv *ks = phydev->bus->priv;
	struct ksz_sw *sw = &ks->sw;

	ks->intr_working |= 1;
	if (ks->sw.info->port_cfg[0].intr_mask & PORT_PHY_INT)
		ks->intr_working |= 2;
	mutex_lock(&sw->lock);
	mutex_lock(&ks->hwlock);
	mutex_lock(&ks->lock);
	sw->intr_using++;
	sw_proc_intr(&ks->sw);
	sw->intr_using--;
	mutex_unlock(&ks->lock);
	mutex_unlock(&ks->hwlock);
	mutex_unlock(&sw->lock);
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

#define KSZ9897_SW_ID		0x9897
#define PHY_ID_KSZ_SW		((KSZ9897_ID_HI << 16) | KSZ9897_SW_ID)

static int kszphy_config_init(struct phy_device *phydev)
{
	return 0;
}

static struct phy_driver kszsw_phy_driver = {
	.phy_id		= PHY_ID_KSZ_SW,
	.phy_id_mask	= 0x00ffffff,
	.name		= "Micrel KSZ9897 Switch",
	.features	= (PHY_GBIT_FEATURES |
				SUPPORTED_Pause | SUPPORTED_Asym_Pause),
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
static void sw_r_phy(struct ksz_sw *sw, u16 phy_id, u16 phy, u16 reg, u16 *val)
{
	u16 data;
	u16 ret;
	int id = phy;

	if (0 == phy || phy > sw->phy_port_cnt)
		phy = phy_id;
	sw_port_r16(sw, phy - 1, P_PHY_CTRL + reg * 2, &data);
	ret = data;

	/* Use unique switch id to differentiate from regular PHY. */
	if (3 == reg)
		ret = KSZ9897_SW_ID;
	if (0 == id || id > sw->phy_port_cnt) {
		switch (reg) {
		case 0:
			ret = 0x1140;
			break;
		case 1:
			ret = 0x796d;
			break;
		case 4:
			ret = 0x05e1;
			break;
		case 5:
			ret = 0xc5e1;
			break;
		case 9:
			ret = 0x0700;
			break;
		case 10:
			if (0 == id)
				id = sw->HOST_PORT;
			if (sw->port_info[id].tx_rate >= 1000 * TX_RATE_UNIT)
				ret = 0x7800;
			else
				ret = 0;
			break;
		}
	}
	if (1 == reg && !(ret & PORT_LINK_STATUS)) {
		sw_port_r16(sw, phy - 1, P_SPEED_STATUS, &data);
		if ((ret & PORT_AUTO_NEG_ACKNOWLEDGE) &&
		    (data & (PORT_STAT_SPEED_1000MBIT |
		    PORT_STAT_SPEED_100MBIT |
		    PORT_STAT_SPEED_10MBIT)))
			ret |= PORT_LINK_STATUS;
	}
	*val = ret;
}  /* sw_r_phy */

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
	int ret = 0xffff;

	if (phy_id > sw->mib_port_cnt)
		return 0xffff;

	addr = ksz_mii_addr(&regnum, &bank);

	mutex_lock(&ks->lock);

#ifdef KSZ_IBA
	/* Indicate okay to use SPI when IBA is enabled. */
	sw->info->iba.use_iba |= 0x40;
#endif
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
		if (regnum < 11) {
			u16 data;

			sw_r_phy(sw, ks->phy_id, phy_id, regnum, &data);
			ret = data;
		} else
			ret = 0;
	}
#ifdef KSZ_IBA
	sw->info->iba.use_iba &= ~0x40;
#endif
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

	if (phy_id > sw->mib_port_cnt)
		return -EINVAL;

	reg = regnum;
	addr = ksz_mii_addr(&regnum, &bank);

	mutex_lock(&ks->lock);

#ifdef KSZ_IBA
	/* Indicate okay to use SPI when IBA is enabled. */
	sw->info->iba.use_iba |= 0x40;
#endif
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
		 * the 32-bit write into two calls for I2C efficiency.
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
		if (regnum < 11) {
			int i;

			/* PHY device driver resets or powers down the PHY. */
			if (0 == regnum &&
			    (val & (PORT_PHY_RESET | PORT_POWER_DOWN)))
				break;
			for (i = 0; i < sw->phy_port_cnt; i++) {
				if (i + 1 == phy_id || 0 == phy_id)
					sw_port_w16(sw, i,
						P_PHY_CTRL + regnum * 2, val);
			}
		}
		break;
	}
#ifdef KSZ_IBA
	sw->info->iba.use_iba &= ~0x40;
#endif
	mutex_unlock(&ks->lock);
	return 0;
}  /* ksz_mii_write */

static int ksz_mii_init(struct sw_priv *ks)
{
	struct platform_device *pdev;
	struct mii_bus *bus;
	int err;
	int i;
	int driver_installed = false;

	pdev = platform_device_register_simple("Switch MII bus", ks->sw.id,
		NULL, 0);
	if (!pdev)
		return -ENOMEM;

	bus = mdiobus_alloc();
	if (bus == NULL) {
		err = -ENOMEM;
		goto mii_init_reg;
	}

	err = phy_driver_register(&kszsw_phy_driver);
	if (err)
		goto mii_init_free_mii_bus;
	driver_installed = true;

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

	ks->phy_id = 1;
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

			phydata = kzalloc(sizeof(struct phy_priv), GFP_KERNEL);
			if (!phydata) {
				err = -ENOMEM;
				goto mii_init_free_mii_bus;
			}
			phydata->port.sw = &ks->sw;
			INIT_WORK(&phydata->port.link_update, link_update_work);
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

		ks->phydev->speed = info->tx_rate / TX_RATE_UNIT;
		ks->phydev->duplex = (info->duplex == 2);
		ks->phydev->pause = 1;
	} while (0);

	return 0;

mii_init_free_mii_bus:
	for (i = 0; i < PHY_MAX_ADDR; i++)
		if (bus->phy_map[i])
			kfree(bus->phy_map[i]->priv);
	if (driver_installed)
		phy_driver_unregister(&kszsw_phy_driver);
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
#if 1
		HW_W32(ks, REG_SW_INT_MASK__4, 0xffffffff);
		HW_W32(ks, REG_SW_PORT_INT_MASK__4, 0xffffffff);
#endif
		mutex_unlock(&ks->lock);
		sw_stop_interrupt(ks);
	}
	for (i = 0; i < PHY_MAX_ADDR; i++)
		if (bus->phy_map[i])
			kfree(bus->phy_map[i]->priv);
	mdiobus_unregister(bus);
	phy_driver_unregister(&kszsw_phy_driver);
	mdiobus_free(bus);
	platform_device_unregister(pdev);
}  /* ksz_mii_exit */

/* driver bus management functions */

static void ksz9897_mib_read_work(struct work_struct *work)
{
	struct sw_priv *hw_priv =
		container_of(work, struct sw_priv, mib_read);
	struct ksz_sw *sw = &hw_priv->sw;
	struct ksz_port_mib *mib;
	int i;
	int cnt = 0;

	/* Find out how many ports are connected. */
	for (i = 0; i < sw->mib_port_cnt; i++)
		if (media_connected == sw->port_state[i].state)
			++cnt;
	if (!cnt)
		cnt++;
	if (time_before(sw->next_jiffies, jiffies)) {
		sw->next_jiffies = jiffies;
		sw->next_jiffies += MIB_READ_INTERVAL * cnt;
	}
	for (i = 0; i < sw->mib_port_cnt; i++) {
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
			}
		} else if (time_after_eq(jiffies, hw_priv->counter[i].time)) {
			hw_priv->counter[i].time = sw->next_jiffies;
			/* Only read MIB counters when the port is connected. */
			if (media_connected == sw->port_state[i].state) {
				hw_priv->counter[i].read = 1;
				sw->next_jiffies += MIB_READ_INTERVAL;
			}

		/* Port is just disconnected. */
		} else if (sw->port_state[i].link_down) {
			sw->port_state[i].link_down = 0;

			/* Read counters one last time after link is lost. */
			hw_priv->counter[i].read = 1;
		}
	}
}  /* ksz9897_mib_read_work */

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
	int i;
	int changes = 0;
	int s = 1;

	if (1 == sw->dev_count || 1 == sw->dev_offset)
		s = 0;
	sw->ops->acquire(sw);
	for (i = 0; i < sw->dev_count + sw->dev_offset; i++) {
		struct phy_priv *phydata;
		struct net_device *dev = sw->netdev[i];

		phydev = sw->phy[i + s];
		phydata = phydev->priv;
		if (dev && sw->net_ops->get_priv_port)
			port = sw->net_ops->get_priv_port(dev);
		else
			port = &phydata->port;
		changes |= port_get_link_speed(port);

		/* Copy all port information for user access. */
		if (port != &phydata->port) {
			copy_port_status(port, &phydata->port);
			if (phydata != hw_priv->phydev->priv) {
				phydata = hw_priv->phydev->priv;
				copy_port_status(port, &phydata->port);
			}
		}
	}
	sw->ops->release(sw);

	/* Not to read PHY registers unnecessarily if no link change. */
	if (!changes)
		return;
}  /* link_read_work */

static void stp_work(struct work_struct *work)
{
#ifdef CONFIG_KSZ_STP
	struct delayed_work *dwork = to_delayed_work(work);
	struct sw_priv *hw_priv =
		container_of(dwork, struct sw_priv, stp_monitor);
	struct ksz_sw *sw = &hw_priv->sw;

	sw->net_ops->monitor_ports(sw);
#endif
}  /* stp_work */

/*
 * Hardware monitoring
 */

static void ksz9897_mib_monitor(unsigned long ptr)
{
	struct sw_priv *hw_priv = (struct sw_priv *) ptr;

	schedule_work(&hw_priv->mib_read);

	ksz_update_timer(&hw_priv->mib_timer_info);
}  /* ksz9897_mib_monitor */

static void ksz9897_dev_monitor(unsigned long ptr)
{
	struct sw_priv *hw_priv = (struct sw_priv *) ptr;

#if 1
	if ((hw_priv->intr_working & 2) &&
	    !(hw_priv->sw.features & STP_SUPPORT))
		return;
	if (!(hw_priv->intr_working & 2))
#endif
		schedule_delayed_work(&hw_priv->link_read, 0);
	if (hw_priv->sw.features & STP_SUPPORT)
		schedule_delayed_work(&hw_priv->stp_monitor, 0);

	ksz_update_timer(&hw_priv->monitor_timer_info);
}  /* ksz9897_dev_monitor */

#ifdef CONFIG_NET_DSA_TAG_TAIL
#include "ksz_dsa.c"
#endif

static int intr_mode;
static int need_link_up;
static int sw_host_port;

#define MAX_I2C_DEVICES		1

static int sw_device_present;

static int ksz9897_probe(struct i2c_client *i2c,
	const struct i2c_device_id *i2c_id)
{
	struct i2c_hw_priv *hw_priv;
	struct sw_priv *ks;
	struct ksz_sw *sw;
	struct ksz_port *port;
	struct phy_device *phydev;
	struct phy_priv *priv;
	u32 id;
	u32 id1;
	u32 id2;
	int cnt;
	int i;
	int mib_port_count;
	int phy_port_count;
	int pi;
	int port_count;
	int ret;

	ks = kzalloc(sizeof(struct sw_priv), GFP_KERNEL);
	if (!ks)
		return -ENOMEM;

	ks->hw_dev = kzalloc(sizeof(struct i2c_hw_priv), GFP_KERNEL);
	if (!ks->hw_dev) {
		kfree(ks);
		return -ENOMEM;
	}
	hw_priv = ks->hw_dev;

	hw_priv->i2cdev = i2c;

	ks->intr_mode = intr_mode ? IRQF_TRIGGER_FALLING :
		IRQF_TRIGGER_LOW;
	ks->irq = i2c->irq;
	ks->dev = &i2c->dev;

	dev_set_drvdata(ks->dev, ks);

	mutex_init(&ks->hwlock);
	mutex_init(&ks->lock);

	/* simple check for a valid chip being connected to the bus */
	mutex_lock(&ks->lock);
	id = HW_R32(ks, REG_CHIP_ID0__1);
	mutex_unlock(&ks->lock);
	id1 = id;
	id1 >>= 8;
	id1 &= 0xffff;
	id2 = id1 & 0xff;
	id1 >>= 8;
dbg_msg("%02x %02x\n", id1, id2);
	if (id1 != FAMILY_ID_95 && id1 != FAMILY_ID_98 &&
	    id1 != FAMILY_ID_94 && id1 != FAMILY_ID_85 && id1 != 0x64) {
		dev_err(ks->dev, "failed to read device ID(0x%x)\n", id);
		ret = -ENODEV;
		goto err_sw;
	}
	dev_info(ks->dev, "chip id 0x%08x\n", id);
	sw = &ks->sw;
	mutex_init(&sw->lock);
	mutex_init(&sw->acllock);
	mutex_init(&sw->alulock);
	mutex_init(&sw->vlanlock);
	sw->hwlock = &ks->hwlock;
	sw->reglock = &ks->lock;

	port_count = 1;
	mib_port_count = 1;
	phy_port_count = 1;
#ifdef CONFIG_1588_PTP
	if ((FAMILY_ID_95 & 0x0f) == (id1 & 0x0f)) {
		sw->features |= PTP_HW;
		sw->features |= ACL_CORRUPT_BUG;
	}
	if (0x64 == id1) {
		sw->features |= PTP_HW;
#if 1
		sw->features |= SETUP_PHY;
#endif
	}
#endif
	if ((FAMILY_ID_85 & 0xf0) == (id1 & 0xf0))
		sw->features |= QW_HW;
	sw->features |= NO_GLOBAL_RESET;

	/* Check for S2 revision. */
	mutex_lock(&ks->lock);
	id = HW_R(ks, REG_GLOBAL_OPTIONS);
	mutex_unlock(&ks->lock);
	if (id) {
		sw->features &= ~ACL_CORRUPT_BUG;
		sw->features &= ~SETUP_PHY;
		sw->features &= ~NO_GLOBAL_RESET;
		sw->features |= NEW_CAP;
		if (id & SW_AVB_ABLE) {
			sw->features |= AVB_SUPPORT;
			sw->features |= PTP_HW;
		}
		if (id & SW_REDUNDANCY_ABLE) {
			sw->features |= REDUNDANCY_SUPPORT;
#ifdef KSZ_DLR
			sw->features |= DLR_HW;
#endif
			sw->features |= HSR_HW;
		}
dbg_msg("avb=%d  rr=%d  giga=%d\n",
!!(id & SW_AVB_ABLE), !!(id & SW_REDUNDANCY_ABLE), !!(id & SW_GIGABIT_ABLE));
	}
	if ((CHIP_ID_67 & 0x0f) == (id2 & 0x0f)) {
		port_count = 7;
		mib_port_count = 7;
		phy_port_count = 5;
		sw->TAIL_TAG_LOOKUP = (1 << (7 + 3));
		sw->TAIL_TAG_OVERRIDE = (1 << (7 + 2));
	} else if ((CHIP_ID_66 & 0x0f) == (id2 & 0x0f)) {
		port_count = 6;
		mib_port_count = 6;
		phy_port_count = 5;
		sw->TAIL_TAG_LOOKUP = (1 << (7 + 3));
		sw->TAIL_TAG_OVERRIDE = (1 << (7 + 2));
	} else if ((CHIP_ID_63 & 0x0f) == (id2 & 0x0f)) {
		port_count = 3;
		mib_port_count = 3;
		phy_port_count = 2;
		sw->TAIL_TAG_LOOKUP = (1 << (3 + 3));
		sw->TAIL_TAG_OVERRIDE = (1 << (3 + 2));
	}
dbg_msg("port: %x %x %x\n", port_count, mib_port_count, phy_port_count);

	sw->dev_count = 1;

	sw->PORT_MASK = (1 << (mib_port_count + 0)) - 1;
	sw->mib_cnt = TOTAL_SWITCH_COUNTER_NUM;
	sw->mib_port_cnt = mib_port_count;
	sw->phy_port_cnt = phy_port_count;
	sw->port_cnt = mib_port_count;
	if (sw_host_port && sw_host_port <= port_count)
		sw->HOST_PORT = sw_host_port - 1;
	else
		sw->HOST_PORT = port_count - 1;
	sw->HOST_MASK = (1 << sw->HOST_PORT);
dbg_msg("mask: %x %x; %x %x\n", sw->HOST_MASK, sw->PORT_MASK,
sw->TAIL_TAG_LOOKUP, sw->TAIL_TAG_OVERRIDE);

	/* Last port is the host port. */
	if (sw->HOST_PORT == port_count - 1 || !sw->HOST_PORT) {
		port_count = port_count - 1;
		mib_port_count = mib_port_count - 1;
	}

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
	INIT_DELAYED_WORK(&ks->stp_monitor, stp_work);

	for (cnt = 0, pi = 0; cnt < phy_port_count; cnt++, pi++) {
		/*
		 * Initialize to invalid value so that link detection
		 * is done.
		 */
		sw->port_info[pi].link = 0xFF;
		sw->port_info[pi].state = media_disconnected;
		sw->port_info[pi].report = true;
	}
	sw->interface = PHY_INTERFACE_MODE_MII;
	mutex_lock(&ks->lock);
	for (; cnt < sw->mib_port_cnt; cnt++, pi++) {
		u16 data;
		u16 orig;
		u8 *data_lo;
		u8 *data_hi;
		int speed;
		phy_interface_t phy;
		struct ksz_port_info *info = &sw->port_info[pi];
		int gbit;
		int mode;

		port_r16(sw, pi, REG_PORT_XMII_CTRL_0, &data);
		orig = data;
		data_hi = (u8 *) &data;
		data_lo = data_hi + 1;

/**
 * THa  2015/08/27
 * Port 6 or 7 may never start transmiting and cause flow control problem in
 * the receive port.
 * Not guaranteed to work all the time.
 */
		if (sw->features & NEW_CAP) {
			*data_hi ^= (PORT_MII_NOT_1GBIT | PORT_MII_MAC_MODE |
				PORT_MII_SEL_M);
			port_w8(sw, pi, REG_PORT_XMII_CTRL_1, *data_hi);
			data = orig;
			port_w8(sw, pi, REG_PORT_XMII_CTRL_1, *data_hi);
		}
#ifdef USE_10_MBIT_MODE
		*data_lo &= ~PORT_MII_100MBIT;
#endif
#ifdef USE_HALF_DUPLEX
		*data_lo &= ~PORT_MII_FULL_DUPLEX;
#endif
#ifdef USE_RGMII_MODE
		sw_set_gbit(sw, true, data_hi);
		sw_set_xmii(sw, 3, data_hi);
#endif
#ifdef USE_GMII_100_MODE
		sw_set_gbit(sw, false, data_hi);
#endif
#ifdef USE_MII_MODE
		sw_set_xmii(sw, 0, data_hi);
#endif
#ifdef USE_GMII_MODE
		sw_set_xmii(sw, 2, data_hi);
#endif
#ifdef USE_RMII_MODE
		sw_set_xmii(sw, 1, data_hi);
#endif
/* Strap options may not valid after reset. */
#if 1
if (PORT_RMII_SEL == (*data_hi & PORT_MII_SEL_M)) {
dbg_msg("?%02x\n", *data_hi);
		sw_set_gbit(sw, true, data_hi);
		sw_set_xmii(sw, 3, data_hi);
}
#endif
		gbit = sw_get_gbit(sw, *data_hi);
		mode = sw_get_xmii(sw, *data_hi);
		switch (mode) {
		case 2:
			phy = PHY_INTERFACE_MODE_GMII;
			if (sw->HOST_PORT == pi)
				sw->interface = phy;
			info->interface = phy;
			speed = 1000;
			if (gbit)
				break;
		case 0:
			phy = PHY_INTERFACE_MODE_MII;
			if (sw->HOST_PORT == pi)
				sw->interface = phy;
			info->interface = phy;
			speed = 100;
			break;
		case 1:
			phy = PHY_INTERFACE_MODE_RMII;
			if (sw->HOST_PORT == pi)
				sw->interface = phy;
			info->interface = phy;
			speed = 100;
			break;
		default:
			phy = PHY_INTERFACE_MODE_RGMII;
			if (*data_hi & PORT_RGMII_ID_IG_ENABLE)
				phy = PHY_INTERFACE_MODE_RGMII_RXID;
			if (*data_hi & PORT_RGMII_ID_EG_ENABLE) {
				if (PHY_INTERFACE_MODE_RGMII_RXID == phy)
					phy = PHY_INTERFACE_MODE_RGMII_ID;
				else
					phy = PHY_INTERFACE_MODE_RGMII_TXID;
			}
			if (sw->HOST_PORT == pi)
				sw->interface = phy;
			info->interface = phy;
			speed = 100;
			if (gbit)
				speed = 1000;
			break;
		}
		if (sw->HOST_PORT == pi)
dbg_msg("host: %d %d\n", sw->HOST_PORT, sw->interface);
		info->state = media_connected;
		if (!(*data_lo & PORT_MII_100MBIT))
			info->tx_rate = 10 * TX_RATE_UNIT;
		else
			info->tx_rate = speed * TX_RATE_UNIT;
		if (*data_lo & PORT_MII_FULL_DUPLEX)
			info->duplex = 2;
		else
			info->duplex = 1;
		info->flow_ctrl = 0x33;
dbg_msg("xmii: %04x %02x %02x; %u %u\n", orig, *data_lo, *data_hi,
info->tx_rate / TX_RATE_UNIT, info->duplex);
	}
	mutex_unlock(&ks->lock);

	ret = ksz_mii_init(ks);
	if (ret)
		goto err_mii;

#ifdef KSZ_IBA
	sw->need_link_up = need_link_up;
#endif
	sw->multi_dev |= multi_dev;
	sw->stp |= stp;
	sw->fast_aging |= fast_aging;

	sw->phydev = ks->phydev;
	sw->counter = ks->counter;
	sw->monitor_timer_info = &ks->monitor_timer_info;
	sw->link_read = &ks->link_read;
	sw->stp_monitor = &ks->stp_monitor;

	sw_setup_mib(sw);
	sw_init_mib(sw);

	for (i = 0; i < TOTAL_PORT_NUM; i++)
		init_waitqueue_head(&ks->counter[i].counter);

	create_debugfs(ks);

#ifdef KSZ_DLR
	if (sw->features & DLR_HW)
		ksz_dlr_init(&sw->info->dlr, sw);
#endif
	sw->ops->acquire(sw);

	/* Turn off PTP in case the feature is not enabled. */
	sw_w16(sw, REG_PTP_MSG_CONF1, 0);

#if 1
	/* Turn off IBA first for KSZ9893. */
	if (sw->features & SETUP_PHY)
		sw_w8(sw, REG_SW_IBA__4, 0);
#endif
	sw_reset(sw);
	sw_init(sw);
	sw_setup(sw);
	sw->ops->release(sw);

#ifndef CONFIG_MICREL_SWITCH_EMBEDDED
	init_sw_sysfs(sw, &ks->sysfs, ks->dev);
#ifdef KSZ_DLR
	if (sw->features & DLR_HW)
		init_dlr_sysfs(ks->dev);
#endif
#endif
	ret = sysfs_create_bin_file(&ks->dev->kobj,
		&kszsw_registers_attr);
	sema_init(&ks->proc_sem, 1);

	for (i = 0; i <= sw->mib_port_cnt; i++) {
		sw->phy[i] = ks->bus->phy_map[i];
		phydev = sw->phy[i];
		if (!phydev)
			continue;
		priv = phydev->priv;
		port = &priv->port;
		port->port_cnt = port_count;
		port->mib_port_cnt = mib_port_count;
		port->first_port = 0;
		port->flow_ctrl = PHY_TX_ONLY;

		port->linked = &sw->port_info[port->first_port];
	}
#ifdef NO_ATTACHED_DEV
	sw->ops->acquire(sw);
	phydev = sw->phydev;
	priv = phydev->priv;
	port = &priv->port;
	port_set_link_speed(port);
	sw->ops->release(sw);
#endif

	INIT_WORK(&sw->set_addr, sw_delayed_set_addr);

#ifdef KSZ_IBA
	ksz_iba_init(&sw->info->iba, sw);
	INIT_DELAYED_WORK(&sw->set_ops, sw_set_ops);
#endif

	INIT_WORK(&ks->mib_read, ksz9897_mib_read_work);

	/* 500 ms timeout */
	ksz_init_timer(&ks->mib_timer_info, 500 * HZ / 1000,
		ksz9897_mib_monitor, ks);
	ksz_init_timer(&ks->monitor_timer_info, 100 * HZ / 1000,
		ksz9897_dev_monitor, ks);

	ksz_start_timer(&ks->mib_timer_info, ks->mib_timer_info.period);
	if (!sw->multi_dev && !sw->stp)
		ksz_start_timer(&ks->monitor_timer_info,
			ks->monitor_timer_info.period);

	sw_device_present++;

#ifdef CONFIG_1588_PTP
	if (sw->features & PTP_HW) {
		struct ptp_info *ptp = &sw->ptp_hw;

		ptp->ports = sw->mib_port_cnt - 0;
		ptp->reg = &ptp_reg_ops;
		ptp->ops = &ptp_ops;
		ptp->parent = ks->dev;
#ifdef NO_ATTACHED_DEV
		ptp->ops->init(ptp, sw->info->mac_addr);
		ptp->reg->start(ptp, true);
#endif
		init_ptp_sysfs(&ks->ptp_sysfs, ks->dev);
	}
#endif
#ifdef KSZ_MRP
	sw->features |= MRP_SUPPORT;
	if (sw->features & MRP_SUPPORT) {
		struct mrp_info *mrp = &sw->mrp;

		mrp->ops = &mrp_ops;
		mrp->ops->init(mrp);
	}
#endif

#ifdef CONFIG_NET_DSA_TAG_TAIL
	ksz_dsa_init();
#endif

	if (ks->irq <= 0)
		return 0;
	mutex_lock(&ks->lock);
	HW_W32(ks, REG_SW_INT_MASK__4, SWITCH_INT_MASK);
	HW_W32(ks, REG_SW_PORT_INT_MASK__4, sw->PORT_MASK);
	sw_w32(sw, REG_PTP_INT_STATUS__4, 0xffffffff);
	for (i = 0; i < sw->phy_port_cnt; i++)
		port_w8(sw, i, REG_PORT_PHY_INT_ENABLE, 0);
	for (i = 0; i < sw->mib_port_cnt; i++) {
		port_w(sw, i, REG_PORT_INT_MASK, 0xff);
		port_w16(sw, i, REG_PTP_PORT_TX_INT_STATUS__2, 0xffff);
	}
	mutex_unlock(&ks->lock);
	ret = sw_start_interrupt(ks, dev_name(ks->dev));
	if (ret < 0)
		printk(KERN_WARNING "No switch interrupt\n");
	else {
		mutex_lock(&ks->lock);
		sw_ena_intr(sw);
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

static int ksz9897_remove(struct i2c_client *i2c)
{
	struct sw_priv *ks = dev_get_drvdata(&i2c->dev);
	struct ksz_sw *sw = &ks->sw;

#ifdef CONFIG_NET_DSA_TAG_TAIL
	ksz_dsa_cleanup();
#endif
#ifdef NO_ATTACHED_DEV
#ifdef CONFIG_1588_PTP
	if (sw->features & PTP_HW) {
		struct ptp_info *ptp = &sw->ptp_hw;

		ptp->ops->stop(ptp);
		ptp->ops->exit(ptp);
	}
#endif
#endif
	ksz_stop_timer(&ks->monitor_timer_info);
	ksz_stop_timer(&ks->mib_timer_info);
	flush_work(&ks->mib_read);

	sysfs_remove_bin_file(&ks->dev->kobj, &kszsw_registers_attr);
#ifndef CONFIG_MICREL_SWITCH_EMBEDDED
#ifdef KSZ_DLR
	if (sw->features & DLR_HW)
		exit_dlr_sysfs(ks->dev);
#endif
#ifdef CONFIG_1588_PTP
	if (sw->features & PTP_HW)
		exit_ptp_sysfs(&ks->ptp_sysfs, ks->dev);
#endif
	exit_sw_sysfs(sw, &ks->sysfs, ks->dev);
#endif
	cancel_delayed_work_sync(&ks->link_read);
	cancel_delayed_work_sync(&ks->stp_monitor);
	delete_debugfs(ks);
#ifdef KSZ_DLR
	if (sw->features & DLR_HW)
		ksz_dlr_exit(&sw->info->dlr);
#endif
#ifdef KSZ_IBA
	ksz_iba_exit(&sw->info->iba);
#endif
	kfree(sw->info);
	ksz_mii_exit(ks);
	kfree(ks->hw_dev);
	kfree(ks);

	return 0;
}

#define I2C_SWITCH_NAME			"i2c-ksz9897"

/* Please change the I2C address if necessary. */
#define I2C_SWITCH_ADDR			0x5F

/* Please provide a system interrupt number here. */
#define I2C_SWITCH_INTR			-1

static int ksz9897_detect(struct i2c_client *i2c, struct i2c_board_info *info)
{
	strncpy(info->type, I2C_SWITCH_NAME, I2C_NAME_SIZE);
	info->irq = I2C_SWITCH_INTR;
	return 0;
}

static unsigned short i2c_address_list[] = {
	I2C_SWITCH_ADDR,

	I2C_CLIENT_END
};

static const struct i2c_device_id i2c_id[] = {
	{ I2C_SWITCH_NAME, 0 },
	{ },
};

static struct i2c_driver ksz9897_driver = {
	.driver.name	= I2C_SWITCH_NAME,
	.probe		= ksz9897_probe,
	.remove		= ksz9897_remove,
	.id_table	= i2c_id,

	/* Big enough to be accepted in all cases. */
	.class		= 0xffff,
	.detect		= ksz9897_detect,
	.address_list	= i2c_address_list,
};

static int __init ksz9897_init(void)
{
	int ret;

	ret = i2c_add_driver(&ksz9897_driver);
	if (ret)
		return ret;

	/* Probe not called. */
	if (!sw_device_present) {
		struct i2c_adapter *adap;

		/* Assume I2C bus starts at 0. */
		adap = i2c_get_adapter(0);

		/* I2C master may not be created yet. */
		if (!adap) {
#if !defined(CONFIG_I2C_KSZ9897_MODULE)
			struct i2c_board_info info = {
				.type	= I2C_SWITCH_NAME,
				.addr	= I2C_SWITCH_ADDR,
				.irq	= I2C_SWITCH_INTR,
			};

			ret = i2c_register_board_info(0, &info, 1);
#else
			return -ENODEV;
#endif
		} else
			i2c_put_adapter(adap);
	}
#ifdef DEBUG_MSG
	if (init_dbg())
		return -ENOMEM;
#endif
	return ret;
}

static void __exit ksz9897_exit(void)
{
	i2c_del_driver(&ksz9897_driver);
#ifdef DEBUG_MSG
	exit_dbg();
#endif
}

#ifndef CONFIG_MICREL_KSZ9897_EMBEDDED
module_init(ksz9897_init);
module_exit(ksz9897_exit);

module_param(fast_aging, int, 0);
module_param(multi_dev, int, 0);
module_param(stp, int, 0);
MODULE_PARM_DESC(fast_aging, "Fast aging");
MODULE_PARM_DESC(multi_dev, "Multiple device interfaces");
MODULE_PARM_DESC(stp, "STP support");

#ifdef KSZ_IBA
module_param(iba, int, 0);
MODULE_PARM_DESC(iba, "IBA support");
#endif
#endif

module_param(intr_mode, int, 0);
MODULE_PARM_DESC(intr_mode,
	"Configure which interrupt mode to use(0=level low, 1=falling)");

module_param(need_link_up, int, 0);
MODULE_PARM_DESC(need_link_up,
	"Configure whether to always indicate link is up");

module_param(sw_host_port, int, 0);
MODULE_PARM_DESC(sw_host_port,
	"Configure switch host port");

#ifndef CONFIG_MICREL_KSZ9897_EMBEDDED
MODULE_DESCRIPTION("Micrel KSZ9897 I2C Switch Driver");
MODULE_AUTHOR("Tristram Ha <Tristram.Ha@microchip.com>");
MODULE_LICENSE("GPL");

MODULE_ALIAS("i2c:ksz9897");
#endif
