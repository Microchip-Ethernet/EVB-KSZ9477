/**
 * Micrel KSZ8863 I2C driver
 *
 * Copyright (c) 2015-2016 Microchip Technology Inc.
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
#endif

/* -------------------------------------------------------------------------- */

#include <linux/i2c.h>
#include <linux/debugfs.h>
#include <linux/seq_file.h>
#include "ksz_cfg_8863.h"
#ifndef PHY_RESET_NOT
#define PHY_RESET_NOT			PHY_RESET
#endif

/* -------------------------------------------------------------------------- */

#define HW_R(ks, reg)		i2c_rdreg8(ks, reg)
#define HW_W(ks, reg, val)	i2c_wrreg8(ks, reg, val)
#define HW_R8(ks, reg)		i2c_rdreg8(ks, reg)
#define HW_W8(ks, reg, val)	i2c_wrreg8(ks, reg, val)
#define HW_R16(ks, reg)		i2c_rdreg16(ks, reg)
#define HW_W16(ks, reg, val)	i2c_wrreg16(ks, reg, val)
#define HW_R32(ks, reg)		i2c_rdreg32(ks, reg)
#define HW_W32(ks, reg, val)	i2c_wrreg32(ks, reg, val)

#include "ksz_sw_phy.h"

#include "ksz_spi_net.h"

/* -------------------------------------------------------------------------- */

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
 * @reg:	The register address.
 * @buf:	The data buffer to write.
 * @txl:	The length of data.
 *
 * This is the low level write call that issues the necessary i2c message(s)
 * to write data to the register specified in @reg.
 */
static void i2c_wrreg(struct sw_priv *ks, u8 reg, void *buf, unsigned txl)
{
	struct i2c_hw_priv *hw_priv = ks->hw_dev;
	struct i2c_msg msg;
	u8 rxd[10];
	struct i2c_client *i2c = hw_priv->i2cdev;
	struct i2c_adapter *adapter = i2c->adapter;

	if (!mutex_is_locked(&ks->lock))
		pr_alert("W not locked\n");

	rxd[0] = reg;
	memcpy(&rxd[1], buf, txl);

	msg.addr = i2c->addr;
	msg.flags = 0;
	msg.len = SW_SIZE + txl;
	msg.buf = rxd;

	if (i2c_transfer(adapter, &msg, 1) != 1)
		pr_alert("i2c_transfer() failed\n");
}

/**
 * i2c_wrreg32 - write 32bit register value to chip
 * @ks:		The switch device structure.
 * @reg:	The register address.
 * @val:	The value to write.
 *
 * Issue a write to put the value @val into the register specified in @reg.
 */
static void i2c_wrreg32(struct sw_priv *ks, u8 reg, unsigned val)
{
	struct i2c_hw_priv *hw_priv = ks->hw_dev;
	int cnt = 4;
	int i = 0;
	u8 *txb = (u8 *) hw_priv->txd;

	while (cnt) {
		txb[i++] = (u8)(val >> (8 * (cnt - 1)));
		cnt--;
	}
	i2c_wrreg(ks, reg, txb, 4);
}

/**
 * i2c_wrreg16 - write 16bit register value to chip
 * @ks:		The switch device structure.
 * @reg:	The register address.
 * @val:	The value to write.
 *
 * Issue a write to put the value @val into the register specified in @reg.
 */
static void i2c_wrreg16(struct sw_priv *ks, u8 reg, unsigned val)
{
	struct i2c_hw_priv *hw_priv = ks->hw_dev;
	int cnt = 2;
	int i = 0;
	u8 *txb = (u8 *) hw_priv->txd;

	while (cnt) {
		txb[i++] = (u8)(val >> (8 * (cnt - 1)));
		cnt--;
	}
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
static void i2c_wrreg8(struct sw_priv *ks, u8 reg, unsigned val)
{
	struct i2c_hw_priv *hw_priv = ks->hw_dev;
	u8 *txb = (u8 *) hw_priv->txd;

	*txb = (u8) val;
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
 * to read data from the register specified in @reg.
 */
static void i2c_rdreg(struct sw_priv *ks, u8 reg, void *rxb, unsigned rxl)
{
	struct i2c_hw_priv *hw_priv = ks->hw_dev;
	struct i2c_msg msg[2];
	struct i2c_client *i2c = hw_priv->i2cdev;
	struct i2c_adapter *adapter = i2c->adapter;

	if (!mutex_is_locked(&ks->lock))
		pr_alert("R not locked\n");

	msg[0].addr = i2c->addr;
	msg[0].flags = 0;
	msg[0].len = SW_SIZE;
	msg[0].buf = &reg;

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
static u8 i2c_rdreg8(struct sw_priv *ks, u8 reg)
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
static u16 i2c_rdreg16(struct sw_priv *ks, u8 reg)
{
	__le16 rx = 0;

	i2c_rdreg(ks, reg, &rx, 2);
	return be16_to_cpu(rx);
}

/**
 * i2c_rdreg32 - read 32 bit register from device
 * @ks:		The switch device structure.
 * @reg:	The register address.
 *
 * Read a 32bit register from the chip.
 *
 * Note, this read requires the address be aligned to 4 bytes.
 */
static u32 i2c_rdreg32(struct sw_priv *ks, u8 reg)
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

	/* This only matters when one phy device is used for the switch. */
	if (1 == sw->dev_count) {
		struct sw_priv *hw_priv = container_of(sw, struct sw_priv, sw);

		for (i = 0; i < SWITCH_PORT_NUM; i++)
			if (port->linked == &sw->port_info[i]) {
				hw_priv->phy_id = i + 1;
				break;
			}
	}
	for (i = 0; i < SWITCH_PORT_NUM; i++) {
		struct ksz_port_info *info = &sw->port_info[i];

		phydev = sw->phy[i + 1];
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
	phydev = sw->phydev;
	if (phydev->attached_dev) {
		int phy_link = 1;

		if (1 == sw->dev_count || 1 == sw->dev_offset)
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
}  /* link_update_work */

#include "ksz_sw.c"

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
static void __devinit create_debugfs(struct sw_priv *ks)
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

static void __devexit delete_debugfs(struct sw_priv *ks)
{
	debugfs_remove(ks->debug_file);
	debugfs_remove(ks->debug_root);
}

/* -------------------------------------------------------------------------- */

#define USE_SPEED_LINK
#define USE_MIB
#include "ksz_sw_sysfs.c"

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
	SW_D status;

	ks->intr_working = true;
	mutex_lock(&ks->hwlock);
	mutex_lock(&ks->lock);
	sw->intr_using++;
	status = HW_R(ks, REG_INT_STATUS);
	status &= ks->intr_mask;
	if (status & ks->intr_mask) {
		HW_W(ks, REG_INT_STATUS, status);
		status &= ~ks->intr_mask;
		schedule_delayed_work(&ks->link_read, 0);
	}
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

#define KSZ8863_SW_ID		0x8863
#define PHY_ID_KSZ_SW		((KSZ8863_ID_HI << 16) | KSZ8863_SW_ID)

static int kszphy_config_init(struct phy_device *phydev)
{
	return 0;
}

static struct phy_driver kszsw_phy_driver = {
	.phy_id		= PHY_ID_KSZ_SW,
	.phy_id_mask	= 0x00ffffff,
	.name		= "Micrel KSZ8863/KSZ8873 Switch",
	.features	= (PHY_BASIC_FEATURES |	SUPPORTED_Pause),
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
	u8 p = phy - 1;
	u16 data = 0;

	switch (reg) {
	case PHY_REG_CTRL:
		port_r(sw, p, P_PHY_CTRL, &ctrl);
		port_r(sw, p, P_NEG_RESTART_CTRL, &restart);
		port_r(sw, p, P_SPEED_STATUS, &speed);
		if (restart & PORT_LOOPBACK)
			data |= PHY_LOOPBACK;
		if (ctrl & PORT_FORCE_100_MBIT)
			data |= PHY_SPEED_100MBIT;
		if (ctrl & PORT_AUTO_NEG_ENABLE)
			data |= PHY_AUTO_NEG_ENABLE;
		if (restart & PORT_POWER_DOWN)
			data |= PHY_POWER_DOWN;
		if (restart & PORT_AUTO_NEG_RESTART)
			data |= PHY_AUTO_NEG_RESTART;
		if (ctrl & PORT_FORCE_FULL_DUPLEX)
			data |= PHY_FULL_DUPLEX;
		if (speed & PORT_HP_MDIX)
			data |= PHY_HP_MDIX;
		if (restart & PORT_FORCE_MDIX)
			data |= PHY_FORCE_MDIX;
		if (restart & PORT_AUTO_MDIX_DISABLE)
			data |= PHY_AUTO_MDIX_DISABLE;
		if (restart & PORT_REMOTE_FAULT_DISABLE)
			data |= PHY_REMOTE_FAULT_DISABLE;
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
		if (link & PORT_STATUS_LINK_GOOD)
			data |= PHY_LINK_STATUS;
		if (speed & PORT_REMOTE_FAULT)
			data |= PHY_REMOTE_FAULT;
		break;
	case PHY_REG_ID_1:
		data = 0x0022;
		break;
	case PHY_REG_ID_2:
		/* Use unique switch id to differentiate from regular PHY. */
		data = KSZ8863_SW_ID;
		break;
	case PHY_REG_AUTO_NEGOTIATION:
		port_r(sw, p, P_PHY_CTRL, &ctrl);
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
		port_r(sw, p, P_LINK_STATUS, &link);
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
		port_r(sw, p, P_PHY_CTRL, &ctrl);
		data = ctrl;
		if (val & PHY_AUTO_NEG_ENABLE)
			data |= PORT_AUTO_NEG_ENABLE;
		else
			data &= ~PORT_AUTO_NEG_ENABLE;
		if (val & PHY_SPEED_100MBIT)
			data |= PORT_FORCE_100_MBIT;
		else
			data &= ~PORT_FORCE_100_MBIT;
		if (val & PHY_FULL_DUPLEX)
			data |= PORT_FORCE_FULL_DUPLEX;
		else
			data &= ~PORT_FORCE_FULL_DUPLEX;
		if (data != ctrl)
			port_w(sw, p, P_PHY_CTRL, data);
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
		if (val & PHY_REMOTE_FAULT_DISABLE)
			data |= PORT_REMOTE_FAULT_DISABLE;
		else
			data &= ~PORT_REMOTE_FAULT_DISABLE;
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
			data |= PORT_LOOPBACK;
		else
			data &= ~PORT_LOOPBACK;
		if (data != restart)
			port_w(sw, p, P_NEG_RESTART_CTRL, data);
		break;
	case PHY_REG_AUTO_NEGOTIATION:
		port_r(sw, p, P_PHY_CTRL, &ctrl);
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
			port_w(sw, p, P_PHY_CTRL, data);
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
	int addr;
	int bank;
	u16 data;
	int ret = 0xffff;

	if (phy_id > SWITCH_PORT_NUM)
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
			int id = phy_id;

			if (0 == phy_id)
				phy_id = ks->phy_id;
			sw_r_phy(&ks->sw, phy_id, regnum, &data);
			ret = data;
			if (0 == id) {
				switch (regnum) {
				case 0:
					ret = 0x3120;
					break;
				case 1:
					ret = 0x782c;
					break;
				case 4:
				case 5:
					ret = 0x05e1;
					break;
				}
			}
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
	int addr;
	int bank;
	int reg;

	if (phy_id > SWITCH_PORT_NUM)
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
		if (regnum < 6) {

			/* PHY device driver resets or powers down the PHY. */
			if (0 == regnum &&
			    (val & (PHY_RESET_NOT | PHY_POWER_DOWN)))
				break;
			if (2 == phy_id || 0 == phy_id)
				sw_w_phy(&ks->sw, 2, regnum, val);
			if (1 == phy_id || 0 == phy_id)
				sw_w_phy(&ks->sw, 1, regnum, val);
		}
		break;
	}
	mutex_unlock(&ks->lock);
	return 0;
}  /* ksz_mii_write */

static int __devinit ksz_mii_init(struct sw_priv *ks)
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
	ks->phydev->link = 1;
	ks->phydev->speed = SPEED_100;
	ks->phydev->duplex = 1;
	ks->phydev->pause = 1;

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

static void __devexit ksz_mii_exit(struct sw_priv *ks)
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
		if (bus->phy_map[i])
			kfree(bus->phy_map[i]->priv);
	mdiobus_unregister(bus);
	phy_driver_unregister(&kszsw_phy_driver);
	mdiobus_free(bus);
	platform_device_unregister(pdev);
}  /* ksz_mii_exit */

/* driver bus management functions */

static void ksz8863_mib_read_work(struct work_struct *work)
{
	struct sw_priv *hw_priv =
		container_of(work, struct sw_priv, mib_read);
	struct ksz_sw *sw = &hw_priv->sw;
	struct ksz_port_mib *mib;
	int i;

	next_jiffies = jiffies;
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
		} else if (jiffies >= hw_priv->counter[i].time) {
			/* Only read MIB counters when the port is connected. */
			if (media_connected == sw->port_state[i].state)
				hw_priv->counter[i].read = 1;

			/* Read dropped counters. */
			else
				mib->cnt_ptr = SWITCH_COUNTER_NUM;
			next_jiffies += MIB_READ_INTERVAL * sw->mib_port_cnt;
			hw_priv->counter[i].time = next_jiffies;

		/* Port is just disconnected. */
		} else if (sw->port_state[i].link_down) {
			sw->port_state[i].link_down = 0;

			/* Read counters one last time after link is lost. */
			hw_priv->counter[i].read = 1;
		}
	}
}  /* ksz8863_mib_read_work */

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

static void ksz8863_mib_monitor(unsigned long ptr)
{
	struct sw_priv *hw_priv = (struct sw_priv *) ptr;

	schedule_work(&hw_priv->mib_read);

	ksz_update_timer(&hw_priv->mib_timer_info);
}  /* ksz8863_mib_monitor */

static void ksz8863_dev_monitor(unsigned long ptr)
{
	struct sw_priv *hw_priv = (struct sw_priv *) ptr;

	if (hw_priv->intr_working && !(hw_priv->sw.features & STP_SUPPORT))
		return;
	if (!hw_priv->intr_working)
		schedule_delayed_work(&hw_priv->link_read, 0);
	if (hw_priv->sw.features & STP_SUPPORT)
		schedule_delayed_work(&hw_priv->stp_monitor, 0);

	ksz_update_timer(&hw_priv->monitor_timer_info);
}  /* ksz8863_dev_monitor */

#ifdef CONFIG_NET_DSA_TAG_TAIL
#include "ksz_dsa.c"
#endif

static int intr_mode;

#define MAX_I2C_DEVICES		1

static int sw_device_present;

static int __devinit ksz8863_probe(struct i2c_client *i2c,
	const struct i2c_device_id *i2c_id)
{
	struct i2c_hw_priv *hw_priv;
	struct sw_priv *ks;
	struct ksz_sw *sw;
	struct ksz_port *port;
	struct phy_device *phydev;
	struct phy_priv *priv;
	u16 id;
	int cnt;
	int i;
	int mib_port_count;
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
	id = HW_R16(ks, REG_CHIP_ID0);
	mutex_unlock(&ks->lock);
	if ((id & SWITCH_CHIP_ID_MASK) != CHIP_ID_63) {
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
	mib_port_count = SWITCH_PORT_NUM;

	sw->mib_cnt = TOTAL_SWITCH_COUNTER_NUM;
	sw->mib_port_cnt = TOTAL_PORT_NUM;
	sw->port_cnt = TOTAL_PORT_NUM;
	sw->PORT_MASK = (1 << sw->mib_port_cnt) - 1;
	sw->HOST_PORT = SWITCH_PORT_NUM;
	sw->HOST_MASK = (1 << sw->HOST_PORT);

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

	INIT_DELAYED_WORK(&ks->link_read, link_read_work);
	INIT_DELAYED_WORK(&ks->stp_monitor, stp_work);

	ret = ksz_mii_init(ks);
	if (ret)
		goto err_mii;

	sw->multi_dev |= multi_dev;
	sw->stp |= stp;
	sw->fast_aging |= fast_aging;

	sw->phydev = ks->phydev;
	sw->counter = ks->counter;
	sw->monitor_timer_info = &ks->monitor_timer_info;
	sw->link_read = &ks->link_read;
	sw->stp_monitor = &ks->stp_monitor;

	sw_init_mib(sw);

	for (i = 0; i < TOTAL_PORT_NUM; i++)
		init_waitqueue_head(&ks->counter[i].counter);

	create_debugfs(ks);

	sw->ops->acquire(sw);
	id = HW_R16(ks, REG_MODE_INDICATOR);
	if (MODE_FLL == (id & MODE_RLL))
		sw->port_info[0].fiber = true;
	sw_init(sw);
	sw_setup(sw);
	sw->ops->release(sw);

#ifndef CONFIG_MICREL_SWITCH_EMBEDDED
	init_sw_sysfs(sw, &ks->sysfs, ks->dev);
#endif
	ret = sysfs_create_bin_file(&ks->dev->kobj,
		&kszsw_registers_attr);
	sema_init(&ks->proc_sem, 1);

	for (cnt = 0, pi = 0; cnt < port_count; cnt++, pi++) {
		/*
		 * Initialize to invalid value so that link detection
		 * is done.
		 */
		sw->port_info[pi].partner = 0xFF;
		sw->port_info[pi].state = media_disconnected;
	}
	sw->interface = PHY_INTERFACE_MODE_MII;
	for (i = 0; i <= SWITCH_PORT_NUM; i++) {
		sw->phy[i] = ks->bus->phy_map[i];
		phydev = sw->phy[i];
		if (!phydev)
			continue;
		priv = phydev->priv;
		port = &priv->port;
		port->port_cnt = port_count;
		port->mib_port_cnt = mib_port_count;
		port->first_port = 0;
		port->flow_ctrl = PHY_FLOW_CTRL;

		port->linked = &sw->port_info[port->first_port];
	}

	INIT_WORK(&ks->mib_read, ksz8863_mib_read_work);

	/* 500 ms timeout */
	ksz_init_timer(&ks->mib_timer_info, 500 * HZ / 1000,
		ksz8863_mib_monitor, ks);
	ksz_init_timer(&ks->monitor_timer_info, 100 * HZ / 1000,
		ksz8863_dev_monitor, ks);

	ksz_start_timer(&ks->mib_timer_info, ks->mib_timer_info.period);
	if (!sw->multi_dev && !sw->stp)
		ksz_start_timer(&ks->monitor_timer_info,
			ks->monitor_timer_info.period);

	sw_device_present++;

#ifdef CONFIG_NET_DSA_TAG_TAIL
	ksz_dsa_init();
#endif

	if (ks->irq <= 0)
		return 0;
	ks->intr_mask = INT_PORT_1_LINK_CHANGE | INT_PORT_2_LINK_CHANGE |
		INT_PORT_3_LINK_CHANGE | INT_PORT_1_2_LINK_CHANGE;
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

static int __devexit ksz8863_remove(struct i2c_client *i2c)
{
	struct sw_priv *ks = dev_get_drvdata(&i2c->dev);
	struct ksz_sw *sw = &ks->sw;

#ifdef CONFIG_NET_DSA_TAG_TAIL
	ksz_dsa_cleanup();
#endif
	ksz_stop_timer(&ks->monitor_timer_info);
	ksz_stop_timer(&ks->mib_timer_info);
	flush_work(&ks->mib_read);

	sysfs_remove_bin_file(&ks->dev->kobj, &kszsw_registers_attr);
#ifndef CONFIG_MICREL_SWITCH_EMBEDDED
	exit_sw_sysfs(sw, &ks->sysfs, ks->dev);
#endif
	cancel_delayed_work_sync(&ks->link_read);
	cancel_delayed_work_sync(&ks->stp_monitor);
	delete_debugfs(ks);
	kfree(sw->info);
	ksz_mii_exit(ks);
	kfree(ks->hw_dev);
	kfree(ks);

	return 0;
}

#define I2C_SWITCH_NAME			"i2c-ksz8863"
#define I2C_SWITCH_ADDR			0x5F
#define I2C_SWITCH_INTR			-1

static int ksz8863_detect(struct i2c_client *i2c, struct i2c_board_info *info)
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

static struct i2c_driver ksz8863_driver = {
	.driver.name	= I2C_SWITCH_NAME,
	.probe		= ksz8863_probe,
	.remove		= ksz8863_remove,
	.id_table	= i2c_id,

	/* Big enough to be accepted in all cases. */
	.class		= 0xffff,
	.detect		= ksz8863_detect,
	.address_list	= i2c_address_list,
};

static int __init ksz8863_init(void)
{
	int ret;

	ret = i2c_add_driver(&ksz8863_driver);
	if (ret)
		return ret;

	/* Probe not called. */
	if (!sw_device_present) {
		struct i2c_adapter *adap;

		/* Assume I2C bus starts at 0. */
		adap = i2c_get_adapter(0);

		/* I2C master may not be created yet. */
		if (!adap) {
#if !defined(CONFIG_I2C_KSZ8863_MODULE)
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
	return ret;
}

static void __exit ksz8863_exit(void)
{
	i2c_del_driver(&ksz8863_driver);
}

#ifndef CONFIG_MICREL_KSZ8863_EMBEDDED
module_init(ksz8863_init);
module_exit(ksz8863_exit);

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

#ifndef CONFIG_MICREL_KSZ8863_EMBEDDED
MODULE_DESCRIPTION("KSZ8863 switch driver");
MODULE_AUTHOR("Tristram Ha <Tristram.Ha@microchip.com>");
MODULE_LICENSE("GPL");

MODULE_ALIAS("i2c:ksz8863");
#endif
