// SPDX-License-Identifier: GPL-2.0
/*
 * Microchip KSZ9477 switch driver main logic
 *
 * Copyright (C) 2017-2023 Microchip Technology Inc.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/iopoll.h>
#include <linux/platform_data/microchip-ksz.h>
#include <linux/phy.h>
#include <linux/if_bridge.h>
#include <net/dsa.h>
#include <net/switchdev.h>

#include "ksz_priv.h"
#include "ksz9477_reg.h"
#include "ksz_common.h"

/* features flags */
#define GBIT_SUPPORT			BIT(0)
#define NEW_XMII			BIT(1)
#define IS_9893				BIT(2)
#define PTP_HW				BIT(3)

/* overrides flags */
#define PTP_TAG				BIT(0)

static const struct {
	int index;
	char string[ETH_GSTRING_LEN];
} ksz9477_mib_names[TOTAL_SWITCH_COUNTER_NUM] = {
	{ 0x00, "rx_hi" },
	{ 0x01, "rx_undersize" },
	{ 0x02, "rx_fragments" },
	{ 0x03, "rx_oversize" },
	{ 0x04, "rx_jabbers" },
	{ 0x05, "rx_symbol_err" },
	{ 0x06, "rx_crc_err" },
	{ 0x07, "rx_align_err" },
	{ 0x08, "rx_mac_ctrl" },
	{ 0x09, "rx_pause" },
	{ 0x0A, "rx_bcast" },
	{ 0x0B, "rx_mcast" },
	{ 0x0C, "rx_ucast" },
	{ 0x0D, "rx_64_or_less" },
	{ 0x0E, "rx_65_127" },
	{ 0x0F, "rx_128_255" },
	{ 0x10, "rx_256_511" },
	{ 0x11, "rx_512_1023" },
	{ 0x12, "rx_1024_1522" },
	{ 0x13, "rx_1523_2000" },
	{ 0x14, "rx_2001" },
	{ 0x15, "tx_hi" },
	{ 0x16, "tx_late_col" },
	{ 0x17, "tx_pause" },
	{ 0x18, "tx_bcast" },
	{ 0x19, "tx_mcast" },
	{ 0x1A, "tx_ucast" },
	{ 0x1B, "tx_deferred" },
	{ 0x1C, "tx_total_col" },
	{ 0x1D, "tx_exc_col" },
	{ 0x1E, "tx_single_col" },
	{ 0x1F, "tx_mult_col" },
	{ 0x80, "rx_total" },
	{ 0x81, "tx_total" },
	{ 0x82, "rx_discards" },
	{ 0x83, "tx_discards" },
};

#ifdef SIMULATE_CASCADE_SWITCH
static bool ksz9477_skip_hw(struct ksz_device *dev, int port)
{
	if (dev->first) {
		struct dsa_switch *ds = dev->ds;
		struct dsa_switch_tree *dst = ds->dst;

		if (ds->index > 0) {
			ds = dst->ds[ds->index - 1];
			if (port == ds->rtable[ds->index + 1]) {
				return true;
			}
		}
	}
	return false;
}
#endif

static void ksz9477_cfg32(struct ksz_device *dev, u32 addr, u32 bits, bool set)
{
	regmap_update_bits(dev->regmap[2], addr, bits, set ? bits : 0);
}

static void ksz9477_port_cfg32(struct ksz_device *dev, int port, int offset,
			       u32 bits, bool set)
{
	regmap_update_bits(dev->regmap[2], PORT_CTRL_ADDR(port, offset), bits,
			   set ? bits : 0);
}

#define read8_op(addr)	\
({ \
	u8 data; \
	ksz_read8(dev, addr, &data); \
	data; \
})

#define read32_op(addr)	\
({ \
	u32 data; \
	ksz_read32(dev, addr, &data); \
	data; \
})

#define pread32_op(addr)	\
({ \
	u32 data; \
	ksz_pread32(dev, port, addr, &data); \
	data; \
})

static u16 ksz9477_get_fid(u16 vid)
{
	u16 fid;

	/* Need to find a way to map VID to FID. */
	if (vid <= 1) {
		fid = 0;
	} else {
		fid = vid & VLAN_FID_M;
		if (fid == 0)
			fid = VLAN_FID_M;
	}
	return fid;
}

static int ksz9477_get_vlan_table(struct ksz_device *dev, u16 vid,
				  u32 *vlan_table)
{
	int ret;
	u8 data;

	mutex_lock(&dev->vlan_mutex);

	ksz_write16(dev, REG_SW_VLAN_ENTRY_INDEX__2, vid & VLAN_INDEX_M);
	ksz_write8(dev, REG_SW_VLAN_CTRL, VLAN_READ | VLAN_START);

	/* wait to be cleared */
	ret = readx_poll_timeout(read8_op, REG_SW_VLAN_CTRL, data,
				 !(data & VLAN_START), 10, 1000);
	if (ret < 0) {
		dev_dbg(dev->dev, "Failed to read vlan table\n");
		goto exit;
	}

	ksz_read32(dev, REG_SW_VLAN_ENTRY__4, &vlan_table[0]);
	ksz_read32(dev, REG_SW_VLAN_ENTRY_UNTAG__4, &vlan_table[1]);
	ksz_read32(dev, REG_SW_VLAN_ENTRY_PORTS__4, &vlan_table[2]);

	ksz_write8(dev, REG_SW_VLAN_CTRL, 0);

exit:
	mutex_unlock(&dev->vlan_mutex);

	return ret;
}

static int ksz9477_set_vlan_table(struct ksz_device *dev, u16 vid,
				  u32 *vlan_table)
{
	int ret;
	u8 data;

	mutex_lock(&dev->vlan_mutex);

	ksz_write32(dev, REG_SW_VLAN_ENTRY__4, vlan_table[0]);
	ksz_write32(dev, REG_SW_VLAN_ENTRY_UNTAG__4, vlan_table[1]);
	ksz_write32(dev, REG_SW_VLAN_ENTRY_PORTS__4, vlan_table[2]);

	ksz_write16(dev, REG_SW_VLAN_ENTRY_INDEX__2, vid & VLAN_INDEX_M);
	ksz_write8(dev, REG_SW_VLAN_CTRL, VLAN_START | VLAN_WRITE);

	/* wait to be cleared */
	ret = readx_poll_timeout(read8_op, REG_SW_VLAN_CTRL, data,
				 !(data & VLAN_START), 10, 1000);
	if (ret < 0) {
		dev_dbg(dev->dev, "Failed to write vlan table\n");
		goto exit;
	}

	ksz_write8(dev, REG_SW_VLAN_CTRL, 0);

	/* update vlan cache table */
	dev->vlan_cache[vid].table[0] = vlan_table[0];
	dev->vlan_cache[vid].table[1] = vlan_table[1];
	dev->vlan_cache[vid].table[2] = vlan_table[2];

exit:
	mutex_unlock(&dev->vlan_mutex);

	return ret;
}

static void ksz9477_read_table(struct ksz_device *dev, u32 *table)
{
	ksz_read32(dev, REG_SW_ALU_VAL_A, &table[0]);
	ksz_read32(dev, REG_SW_ALU_VAL_B, &table[1]);
	ksz_read32(dev, REG_SW_ALU_VAL_C, &table[2]);
	ksz_read32(dev, REG_SW_ALU_VAL_D, &table[3]);
}

static void ksz9477_write_table(struct ksz_device *dev, u32 *table)
{
	ksz_write32(dev, REG_SW_ALU_VAL_A, table[0]);
	ksz_write32(dev, REG_SW_ALU_VAL_B, table[1]);
	ksz_write32(dev, REG_SW_ALU_VAL_C, table[2]);
	ksz_write32(dev, REG_SW_ALU_VAL_D, table[3]);
}

static int ksz9477_reset_switch(struct ksz_device *dev)
{
	u8 data8;
	u16 data16;
	u32 data32;

	/* reset switch */
	ksz_cfg(dev, REG_SW_OPERATION, SW_RESET, true);

	/* turn off SPI DO Edge select */
	ksz_read8(dev, REG_SW_GLOBAL_SERIAL_CTRL_0, &data8);
	data8 &= ~SPI_AUTO_EDGE_DETECTION;
	ksz_write8(dev, REG_SW_GLOBAL_SERIAL_CTRL_0, data8);

	/* default configuration */
	ksz_read8(dev, REG_SW_LUE_CTRL_1, &data8);
	data8 = SW_AGING_ENABLE | SW_LINK_AUTO_AGING |
	      SW_SRC_ADDR_FILTER | SW_FLUSH_STP_TABLE | SW_FLUSH_MSTP_TABLE;
	ksz_write8(dev, REG_SW_LUE_CTRL_1, data8);

	/* disable interrupts */
	ksz_write32(dev, REG_SW_INT_MASK__4, SWITCH_INT_MASK);
	ksz_write32(dev, REG_SW_PORT_INT_MASK__4, 0x7F);
	ksz_read32(dev, REG_SW_PORT_INT_STATUS__4, &data32);

	/* set broadcast storm protection 10% rate */
	ksz_read16(dev, REG_SW_MAC_CTRL_2, &data16);
	data16 &= ~BROADCAST_STORM_RATE;
	data16 |= (BROADCAST_STORM_VALUE * BROADCAST_STORM_PROT_RATE) / 100;
	ksz_write16(dev, REG_SW_MAC_CTRL_2, data16);

	ksz_write32(dev, REG_SW_PORT_INT_MASK__4, ~((1 << dev->port_cnt) - 1));
	return 0;
}

static void port_mmd_setup(struct ksz_device *dev, uint port, u16 devid,
			   u16 reg, u16 len)
{
	u16 ctrl = PORT_MMD_OP_DATA_NO_INCR;

	if (len > 1)
		ctrl = PORT_MMD_OP_DATA_INCR_RW;
	ksz_pwrite16(dev, port, REG_PORT_PHY_MMD_SETUP,
		     MMD_SETUP(PORT_MMD_OP_INDEX, devid));
	ksz_pwrite16(dev, port, REG_PORT_PHY_MMD_INDEX_DATA, reg);
	ksz_pwrite16(dev, port, REG_PORT_PHY_MMD_SETUP,
		     MMD_SETUP(ctrl, devid));
}

static void port_mmd_read(struct ksz_device *dev, uint port, u16 devid,
			  u16 reg, u16 *buf, u16 len)
{
	port_mmd_setup(dev, port, devid, reg, len);
	while (len) {
		ksz_pread16(dev, port, REG_PORT_PHY_MMD_INDEX_DATA, buf);
		buf++;
		len--;
	}
}

static void port_mmd_write(struct ksz_device *dev, uint port, u16 devid,
			   u16 reg, u16 *buf, u16 len)
{
	port_mmd_setup(dev, port, devid, reg, len);
	while (len) {
		ksz_pwrite16(dev, port, REG_PORT_PHY_MMD_INDEX_DATA, *buf);
		buf++;
		len--;
	}
}

#if 1
#define SETUP_PHY_OLD
#endif
#if 0
#define SETUP_PHY_NEW
#endif

struct ksz_phy_settings {
	u16 mmd;
	u16 reg;
	u16 val;
};

static struct ksz_phy_settings ksz9893_phy_settings[] = {
	{ MMD_DEVICE_ID_DSP, 0xa0, 0x3fff },
};

static void port_setup_eee(struct ksz_device *dev, uint port)
{
	u16 val[0x20];

	ksz_pwrite16(dev, port, REG_PORT_PHY_CTRL, 0x2100);
#ifdef SETUP_PHY_OLD
	ksz_pwrite16(dev, port, REG_PORT_PHY_REMOTE_LB_LED, 0x00f0);
#endif

#ifdef SETUP_PHY_NEW
	val[0] = 0xDD0B;
	port_mmd_write(dev, port, MMD_DEVICE_ID_DSP, 0x6F, val, 1);
#else
	val[0] = 0x0100;
	port_mmd_write(dev, port, MMD_DEVICE_ID_DSP, 0xCE, val, 1);
	val[0] = 0x0ff0;
	port_mmd_write(dev, port, MMD_DEVICE_ID_DSP, 0xCC, val, 1);
	val[0] = 0x0141;
	port_mmd_write(dev, port, MMD_DEVICE_ID_DSP, 0xCA, val, 1);
	val[0] = 0x0fcf;
	port_mmd_write(dev, port, MMD_DEVICE_ID_DSP, 0xCB, val, 1);
	val[0] = 0x0010;
	port_mmd_write(dev, port, MMD_DEVICE_ID_DSP, 0xC8, val, 1);
	val[0] = 0x0100;
	port_mmd_write(dev, port, MMD_DEVICE_ID_DSP, 0xD9, val, 1);
	val[0] = 0x0280;
	port_mmd_write(dev, port, MMD_DEVICE_ID_DSP, 0xC9, val, 1);
#endif

#ifdef SETUP_PHY_OLD
	val[0x09] = 0x010A;
	val[0x0a] = 0x00ED;
	val[0x0b] = 0x00D3;
	val[0x0c] = 0x00BC;
	val[0x0d] = 0x00A8;
	val[0x0e] = 0x0096;
	val[0x0f] = 0x0085;
	val[0x10] = 0x0077;
	val[0x11] = 0x006A;
	val[0x12] = 0x005E;
	val[0x13] = 0x0054;
	val[0x14] = 0x004B;
	val[0x15] = 0x0043;
	val[0x16] = 0x003C;
	val[0x17] = 0x0035;
	val[0x18] = 0x002F;
	val[0x19] = 0x002A;
	val[0x1a] = 0x0026;
	port_mmd_write(dev, port, MMD_DEVICE_ID_DSP, 0x79, &val[0x09], 18);
#endif

	val[0] = 0x6032;
	port_mmd_write(dev, port, MMD_DEVICE_ID_DSP, 0x8F, val, 1);
	val[0] = 0x248C;
	port_mmd_write(dev, port, MMD_DEVICE_ID_DSP, 0x9D, val, 1);

	val[0] = 0x0060;
	port_mmd_write(dev, port, MMD_DEVICE_ID_DSP, 0x75, val, 1);
	val[0] = 0x7777;
	port_mmd_write(dev, port, MMD_DEVICE_ID_DSP, 0xD3, val, 1);

#ifdef SETUP_PHY_OLD
	val[0] = 0x9400;
	port_mmd_write(dev, port, MMD_DEVICE_ID_AFED, 0x0, val, 1);
#endif

#ifdef SETUP_PHY_NEW
	val[0] = 0x00d0;
	port_mmd_write(dev, port, MMD_DEVICE_ID_AFED, 0x4, val, 1);
	val[0] = 0x3008;
	port_mmd_write(dev, port, MMD_DEVICE_ID_AFED, 0x6, val, 1);
	val[0] = 0x2001;
	port_mmd_write(dev, port, MMD_DEVICE_ID_AFED, 0x8, val, 1);
#else
	/*
	 * Use value 0x00E2 for improved 100BTX PMD Output Amplitude.
	 */
	val[0] = 0x00e2;
	port_mmd_write(dev, port, MMD_DEVICE_ID_AFED, 0x4, val, 1);
	val[0] = 0x3100;
	port_mmd_write(dev, port, MMD_DEVICE_ID_AFED, 0x6, val, 1);
	val[0] = 0xe01c;
	port_mmd_write(dev, port, MMD_DEVICE_ID_AFED, 0x9, val, 1);
#endif

	val[0x13] = 0x6eff;
	val[0x14] = 0xe6ff;
	val[0x15] = 0x6eff;
	val[0x16] = 0xe6ff;
	val[0x17] = 0x00ff;
	val[0x18] = 0x43ff;
	val[0x19] = 0xc3ff;
	val[0x1a] = 0x6fff;
	val[0x1b] = 0x07ff;
	val[0x1c] = 0x0fff;
	val[0x1d] = 0xe7ff;
	val[0x1e] = 0xefff;
	port_mmd_write(dev, port, MMD_DEVICE_ID_AFED, 0x13, &val[0x13], 12);
#ifdef SETUP_PHY_NEW
	val[0] = 0xeeee;
	port_mmd_write(dev, port, MMD_DEVICE_ID_AFED, 0x20, val, 1);
#endif

	ksz_pwrite16(dev, port, REG_PORT_PHY_CTRL, 0x1140);
}

static void port_setup_9893(struct ksz_device *dev, uint port)
{
	struct ksz_phy_settings *set;
	u16 val[1];
	int i;

	for (i = 0; i < ARRAY_SIZE(ksz9893_phy_settings); i++) {
		set = &ksz9893_phy_settings[i];
		val[0] = set->val;
		port_mmd_write(dev, port, set->mmd, set->reg, val, 1);
	}
}

static void port_sgmii_s(struct ksz_device *dev, uint port, u16 devid, u16 reg,
			 u16 len)
{
	u32 data;

	data = devid & PORT_SGMII_DEVICE_ID_M;
	data <<= PORT_SGMII_DEVICE_ID_S;
	data |= reg;
	if (len > 1)
		data |= PORT_SGMII_AUTO_INCR;
	ksz_pwrite32(dev, port, REG_PORT_SGMII_ADDR__4, data);
}

static void port_sgmii_r(struct ksz_device *dev, uint port, u16 devid, u16 reg,
			 u16 *buf, u16 len)
{
	u32 data;

	port_sgmii_s(dev, port, devid, reg, len);
	while (len) {
		ksz_pread32(dev, port, REG_PORT_SGMII_DATA__4, &data);
		*buf++ = (u16) data;
		len--;
	}
}

static void port_sgmii_w(struct ksz_device *dev, uint port, u16 devid, u16 reg,
			 u16 *buf, u16 len)
{
	u32 data;

	port_sgmii_s(dev, port, devid, reg, len);
	while (len) {
		data = *buf++;
		ksz_pwrite32(dev, port, REG_PORT_SGMII_DATA__4, data);
		len--;
	}
}

static u16 port_sgmii_phy_r(struct ksz_device *dev, uint port, u16 reg)
{
	u16 buf;

	do {
		port_sgmii_r(dev, port, SR_MII, MMD_SR_MII_PHY_CTRL, &buf, 1);
	} while (buf & SR_MII_PHY_START_BUSY);
	buf = reg;
	port_sgmii_w(dev, port, SR_MII, MMD_SR_MII_PHY_ADDR, &buf, 1);
	buf = 0;
	port_sgmii_w(dev, port, SR_MII, MMD_SR_MII_PHY_CTRL, &buf, 1);
	buf |= SR_MII_PHY_START_BUSY;
	port_sgmii_w(dev, port, SR_MII, MMD_SR_MII_PHY_CTRL, &buf, 1);
	do {
		port_sgmii_r(dev, port, SR_MII, MMD_SR_MII_PHY_CTRL, &buf, 1);
	} while (buf & SR_MII_PHY_START_BUSY);
	port_sgmii_r(dev, port, SR_MII, MMD_SR_MII_PHY_DATA, &buf, 1);
	return buf;
}

static void port_sgmii_phy_w(struct ksz_device *dev, uint port, u16 reg, u16 val)
{
	u16 buf;

	do {
		port_sgmii_r(dev, port, SR_MII, MMD_SR_MII_PHY_CTRL, &buf, 1);
	} while (buf & SR_MII_PHY_START_BUSY);
	buf = reg;
	port_sgmii_w(dev, port, SR_MII, MMD_SR_MII_PHY_ADDR, &buf, 1);
	buf = val;
	port_sgmii_w(dev, port, SR_MII, MMD_SR_MII_PHY_DATA, &buf, 1);
	buf = SR_MII_PHY_WRITE;
	port_sgmii_w(dev, port, SR_MII, MMD_SR_MII_PHY_CTRL, &buf, 1);
	buf |= SR_MII_PHY_START_BUSY;
	port_sgmii_w(dev, port, SR_MII, MMD_SR_MII_PHY_CTRL, &buf, 1);
	do {
		port_sgmii_r(dev, port, SR_MII, MMD_SR_MII_PHY_CTRL, &buf, 1);
	} while (buf & SR_MII_PHY_START_BUSY);
}

static int port_sgmii_detect(struct ksz_device *dev, uint p)
{
	struct ksz_port *port = &dev->ports[p];
	int ret = 0;
	u16 buf[6];

	/* For debug purpose. */
	port_sgmii_phy_w(dev, p, SR_MII_PHY_JTAG_CHIP_ID_LO, 0x1234);
	buf[0] = port_sgmii_phy_r(dev, p, SR_MII_PHY_JTAG_CHIP_ID_LO);
	buf[1] = port_sgmii_phy_r(dev, p, SR_MII_PHY_JTAG_CHIP_ID_HI);
	port_sgmii_r(dev, p, SR_MII, 0x8000, buf, 3);

	port_sgmii_r(dev, p, SR_MII, 0, buf, 6);

	/* Cannot detect whether the SGMII PHY is plugged in reliably. */
	ret = 1;
	if (dev->sgmii_mode) {
		if (buf[5] & SR_MII_REMOTE_ACK) {
			if (buf[5] & (SR_MII_REMOTE_HALF_DUPLEX |
				      SR_MII_REMOTE_FULL_DUPLEX))
				port->fiber = 1;
			else if (dev->sgmii_mode == 1)
				dev->sgmii_mode = 2;
		} else if (dev->sgmii_mode == 1)
			port->fiber = 1;
	}
	return ret;
}

static void port_sgmii_setup(struct ksz_device *dev, uint p, bool pcs,
			     bool master, bool autoneg, int speed, int duplex)
{
	u16 ctrl;
	u16 cfg;
	u16 adv;

	/* SGMII registers are not changed by reset. */
	port_sgmii_r(dev, p, SR_MII, MMD_SR_MII_AUTO_NEG_CTRL, &cfg, 1);
	if (cfg & SR_MII_AUTO_NEG_COMPLETE_INTR)
		return;
	cfg = 0;
	if (pcs)
		cfg |= SR_MII_PCS_SGMII << SR_MII_PCS_MODE_S;
	if (master) {
		cfg |= SR_MII_TX_CFG_PHY_MASTER;
		cfg |= SR_MII_SGMII_LINK_UP;
	}
	cfg |= SR_MII_AUTO_NEG_COMPLETE_INTR;
	port_sgmii_w(dev, p, SR_MII, MMD_SR_MII_AUTO_NEG_CTRL, &cfg, 1);
	port_sgmii_r(dev, p, SR_MII, MMD_SR_MII_CTRL, &ctrl, 1);
	if (master || !autoneg) {
		switch (speed) {
		case 1:
			ctrl |= SR_MII_SPEED_100MBIT;
			break;
		case 2:
			ctrl |= SR_MII_SPEED_1000MBIT;
			break;
		}
	}
	if (!autoneg) {
		ctrl &= ~SR_MII_AUTO_NEG_ENABLE;
		port_sgmii_w(dev, p, SR_MII, MMD_SR_MII_CTRL, &ctrl, 1);
		return;
	} else if (!(ctrl & SR_MII_AUTO_NEG_ENABLE)) {
		ctrl |= SR_MII_AUTO_NEG_ENABLE;
		port_sgmii_w(dev, p, SR_MII, MMD_SR_MII_CTRL, &ctrl, 1);
	}

	/* Need to write to advertise register to send correct signal. */
	/* Default value is 0x0020. */
	port_sgmii_r(dev, p, SR_MII, MMD_SR_MII_AUTO_NEGOTIATION, &adv, 1);
	adv = SR_MII_AUTO_NEG_ASYM_PAUSE_RX << SR_MII_AUTO_NEG_PAUSE_S;
	if (duplex)
		adv |= SR_MII_AUTO_NEG_FULL_DUPLEX;
	else
		adv |= SR_MII_AUTO_NEG_HALF_DUPLEX;
	port_sgmii_w(dev, p, SR_MII, MMD_SR_MII_AUTO_NEGOTIATION, &adv, 1);
	if (master && autoneg) {
		ctrl |= SR_MII_AUTO_NEG_RESTART;
		port_sgmii_w(dev, p, SR_MII, MMD_SR_MII_CTRL, &ctrl, 1);
	}
}

static int sgmii_port_get_speed(struct ksz_device *dev, uint p)
{
	struct ksz_port *info = &dev->ports[p];
	int ret = 0;
	u16 status;
	u16 speed;
	u16 data;
	u8 link;

	port_sgmii_r(dev, p, SR_MII, MMD_SR_MII_STATUS, &status, 1);
	port_sgmii_r(dev, p, SR_MII, MMD_SR_MII_STATUS, &status, 1);
	port_sgmii_r(dev, p, SR_MII, MMD_SR_MII_AUTO_NEG_STATUS, &data, 1);

	/* 10/100/1000: 1f0001 = 01ad  1f0005 = 4000  1f8002 = 0008
	 *              1f0001 = 01bd  1f0005 = d000  1f8002 = 001a
	 * 1000:        1f0001 = 018d  1f0005 = 0000  1f8002 = 0000
	 *              1f0001 = 01ad  1f0005 = 40a0  1f8002 = 0000
	 *              1f0001 = 01ad  1f0005 = 41a0  1f8002 = 0000
	 * fiber:       1f0001 = 0189  1f0005 = 0000  1f8002 = 0000
	 *              1f0001 = 01ad  1f0005 = 41a0  1f8002 = 0000
	 */

	/* Running in fiber mode. */
	if (info->fiber && !data &&
	    (status & (PORT_AUTO_NEG_ACKNOWLEDGE | PORT_LINK_STATUS)) ==
	    (PORT_AUTO_NEG_ACKNOWLEDGE | PORT_LINK_STATUS)) {
		data = SR_MII_STAT_LINK_UP |
		       (SR_MII_STAT_1000_MBPS << SR_MII_STAT_S) |
		       SR_MII_STAT_FULL_DUPLEX;
	}
	if (data & SR_MII_STAT_LINK_UP)
		ret = 1;

	link = (data & ~SR_MII_AUTO_NEG_COMPLETE_INTR);
	if (info->link_val == link)
		return ret;

	/* Need to update control register with same link setting. */
	if (data & SR_MII_STAT_LINK_UP) {
		u16 ctrl;

		ctrl = SR_MII_AUTO_NEG_ENABLE;
		speed = (data >> SR_MII_STAT_S) & SR_MII_STAT_M;
		if (SR_MII_STAT_1000_MBPS == speed)
			ctrl |= SR_MII_SPEED_1000MBIT;
		else if (SR_MII_STAT_100_MBPS == speed)
			ctrl |= SR_MII_SPEED_100MBIT;
		if (data & SR_MII_STAT_FULL_DUPLEX)
			ctrl |= SR_MII_FULL_DUPLEX;
		port_sgmii_w(dev, p, SR_MII, MMD_SR_MII_CTRL, &ctrl, 1);
	}
	if (data & SR_MII_STAT_LINK_UP) {
		speed = (data >> SR_MII_STAT_S) & SR_MII_STAT_M;
		info->phydev.speed = SPEED_10;
		if (SR_MII_STAT_1000_MBPS == speed)
			info->phydev.speed = SPEED_1000;
		else if (SR_MII_STAT_100_MBPS == speed)
			info->phydev.speed = SPEED_100;

		info->phydev.duplex = 0;
		if (data & SR_MII_STAT_FULL_DUPLEX)
			info->phydev.duplex = 1;
	}
	ret |= 2;
	info->link_val = link;
	info->phydev.link = (ret & 1);
	return ret;
}

static void sgmii_check_work(struct work_struct *work)
{
	struct ksz_device *dev =
		container_of(work, struct ksz_device, sgmii_check);
	struct ksz_port *p = &dev->ports[6];

	if (p->sgmii && p->phydev.link) {
		struct phy_device *phydev = p->actual_phydev;
		int ret = sgmii_port_get_speed(dev, 6);

		if ((ret & 2) && phydev)
			phy_trigger_machine(phydev, true);
	}
}

static void sgmii_monitor(unsigned long ptr)
{
	struct ksz_device *dev = (struct ksz_device *)ptr;

	mod_timer(&dev->sgmii_timer, jiffies + msecs_to_jiffies(1000));
	schedule_work(&dev->sgmii_check);
}

static void ksz9477_r_mib_cnt(struct ksz_device *dev, int port, u16 addr,
			      u64 *cnt)
{
	u32 data;
	int ret;
	struct ksz_port *p = &dev->ports[port];

	/* retain the flush/freeze bit */
	data = p->freeze ? MIB_COUNTER_FLUSH_FREEZE : 0;
	data |= MIB_COUNTER_READ;
	data |= (addr << MIB_COUNTER_INDEX_S);
	ksz_pwrite32(dev, port, REG_PORT_MIB_CTRL_STAT__4, data);

	/* failed to read MIB. get out of loop */
	ret = readx_poll_timeout(pread32_op, REG_PORT_MIB_CTRL_STAT__4, data,
				 !(data & MIB_COUNTER_READ), 10, 1000);
	if (ret < 0) {
		dev_dbg(dev->dev, "Failed to get MIB\n");
		return;
	}

	/* count resets upon read */
	ksz_pread32(dev, port, REG_PORT_MIB_DATA, &data);
	*cnt += data;
}

static void ksz9477_r_mib_pkt(struct ksz_device *dev, int port, u16 addr,
			      u64 *dropped, u64 *cnt)
{
	addr = ksz9477_mib_names[addr].index;
	ksz9477_r_mib_cnt(dev, port, addr, cnt);
}

static void ksz9477_freeze_mib(struct ksz_device *dev, int port, bool freeze)
{
	struct ksz_port *p = &dev->ports[port];
	u32 val = freeze ? MIB_COUNTER_FLUSH_FREEZE : 0;

	/* enable/disable the port for flush/freeze function */
	mutex_lock(&p->mib.cnt_mutex);
	ksz_pwrite32(dev, port, REG_PORT_MIB_CTRL_STAT__4, val);

	/* used by MIB counter reading code to know freeze is enabled */
	p->freeze = freeze;
	mutex_unlock(&p->mib.cnt_mutex);
}

static void ksz9477_port_init_cnt(struct ksz_device *dev, int port)
{
	struct ksz_port_mib *mib = &dev->ports[port].mib;

	/* flush all enabled port MIB counters */
	mutex_lock(&mib->cnt_mutex);
	ksz_pwrite32(dev, port, REG_PORT_MIB_CTRL_STAT__4,
		     MIB_COUNTER_FLUSH_FREEZE);
	ksz_write8(dev, REG_SW_MAC_CTRL_6, SW_MIB_COUNTER_FLUSH);
	ksz_pwrite32(dev, port, REG_PORT_MIB_CTRL_STAT__4, 0);
	mutex_unlock(&mib->cnt_mutex);

	mib->cnt_ptr = 0;
	memset(mib->counters, 0, dev->mib_cnt * sizeof(u64));
}

static enum dsa_tag_protocol ksz9477_get_tag_protocol(struct dsa_switch *ds)
{
	return DSA_TAG_PROTO_KSZ;
}

#define KSZ989X_SW_ID		0x9897
#define KSZ889X_SW_ID		0x8897
#define PHY_ID_KSZ989X_SW	((KSZ9477_ID_HI << 16) | KSZ989X_SW_ID)
#define PHY_ID_KSZ889X_SW	((KSZ9477_ID_HI << 16) | KSZ889X_SW_ID)

static int ksz9477_phy_read16(struct dsa_switch *ds, int addr, int reg)
{
	struct ksz_device *dev = ds->priv;
	u16 val = 0xffff;

	/* No real PHY after this. Simulate the PHY.
	 * A fixed PHY can be setup in the device tree, but this function is
	 * still called for that port during initialization.
	 * For RGMII PHY there is no way to access it so the fixed PHY should
	 * be used.
	 */
	if (addr >= dev->phy_port_cnt) {
		struct ksz_port *p = &dev->ports[addr];

		switch (reg) {
		case MII_BMCR:
			val = 0x1140;
			break;
		case MII_BMSR:
			if (p->phydev.link)
				val = 0x796d;
			else
				val = 0x7949;
			break;
		case MII_PHYSID1:
			val = KSZ9477_ID_HI;
			break;
		case MII_PHYSID2:
			val = 0x1631;
			break;
		case MII_ADVERTISE:
			val = 0x05e1;
			break;
		case MII_LPA:
			if (p->phydev.link) {
				if (p->phydev.speed == SPEED_1000) {
					val = 0xc5e1;
				} else if (p->phydev.speed == SPEED_100) {
					val = 0x4d81;
					if (!p->phydev.duplex)
						val = 0x4c81;
				} else {
					val = 0x4c61;
					if (!p->phydev.duplex)
						val = 0x4c21;
				}
			} else {
				val = 0x0000;
			}
			break;
		case MII_CTRL1000:
			val = 0x0700;
			break;
		case MII_STAT1000:
			if (p->phydev.link) {
				if (p->phydev.speed == SPEED_1000)
					val = 0x7c00;
				else
					val = 0x4000;
			} else {
				val = 0x0000;
			}
			break;
		}
	} else {
		ksz_pread16(dev, addr, 0x100 + (reg << 1), &val);
	}
	if (reg == MII_PHYSID2) {
		if (dev->features & GBIT_SUPPORT)
			val = KSZ989X_SW_ID;
		else
			val = KSZ889X_SW_ID;
	}

	return val;
}

static int ksz9477_phy_write16(struct dsa_switch *ds, int addr, int reg,
			       u16 val)
{
	struct ksz_device *dev = ds->priv;

	/* No real PHY after this. */
	if (addr >= dev->phy_port_cnt)
		return 0;

#ifdef SIMULATE_CASCADE_SWITCH
	if (ksz9477_skip_hw(dev, addr))
		return 0;
#endif

	/* No gigabit support.  Do not write to this register. */
	if (!(dev->features & GBIT_SUPPORT) && reg == MII_CTRL1000)
		return 0;
	ksz_pwrite16(dev, addr, 0x100 + (reg << 1), val);

	return 0;
}

static void ksz9477_get_strings(struct dsa_switch *ds, int port, uint8_t *buf)
{
	int i;

	for (i = 0; i < TOTAL_SWITCH_COUNTER_NUM; i++) {
		memcpy(buf + i * ETH_GSTRING_LEN, ksz9477_mib_names[i].string,
		       ETH_GSTRING_LEN);
	}
}

static void ksz9477_cfg_port_member(struct ksz_device *dev, int port,
				    u8 member)
{
	ksz_pwrite32(dev, port, REG_PORT_VLAN_MEMBERSHIP__4, member);
	dev->ports[port].member = member;
}

static void ksz9477_port_stp_state_set(struct dsa_switch *ds, int port,
				       u8 state)
{
	struct ksz_device *dev = ds->priv;
	struct ksz_port *p = &dev->ports[port];
	u8 data;
	int member = -1;
	int forward = dev->member;

#ifdef SIMULATE_CASCADE_SWITCH
	if (ksz9477_skip_hw(dev, port))
		return;
#endif

	ksz_pread8(dev, port, P_STP_CTRL, &data);
	data &= ~(PORT_TX_ENABLE | PORT_RX_ENABLE | PORT_LEARN_DISABLE);

	switch (state) {
	case BR_STATE_DISABLED:
		data |= PORT_LEARN_DISABLE;
		if (port != dev->cpu_port)
			member = 0;
		break;
	case BR_STATE_LISTENING:
		data |= (PORT_RX_ENABLE | PORT_LEARN_DISABLE);
		if (port != dev->cpu_port &&
		    p->stp_state == BR_STATE_DISABLED)
			member = dev->host_mask | p->vid_member;
		break;
	case BR_STATE_LEARNING:
		data |= PORT_RX_ENABLE;
		break;
	case BR_STATE_FORWARDING:
		data |= (PORT_TX_ENABLE | PORT_RX_ENABLE);

		/* This function is also used internally. */
		if (port == dev->cpu_port)
			break;

		member = dev->host_mask | p->vid_member;

		/* Port is a member of a bridge. */
		if (dev->br_member & (1 << port)) {
			dev->member |= (1 << port);
			member = dev->member;
		}
		break;
	case BR_STATE_BLOCKING:
		data |= PORT_LEARN_DISABLE;
		if (port != dev->cpu_port &&
		    p->stp_state == BR_STATE_DISABLED)
			member = dev->host_mask | p->vid_member;
		break;
	default:
		dev_err(ds->dev, "invalid STP state: %d\n", state);
		return;
	}

	ksz_pwrite8(dev, port, P_STP_CTRL, data);
	p->stp_state = state;
	if (data & PORT_RX_ENABLE)
		dev->rx_ports |= (1 << port);
	else
		dev->rx_ports &= ~(1 << port);
	if (data & PORT_TX_ENABLE)
		dev->tx_ports |= (1 << port);
	else
		dev->tx_ports &= ~(1 << port);

	/* Port membership may share register with STP state. */
	if (member >= 0 && member != p->member)
		ksz9477_cfg_port_member(dev, port, (u8)member);

	/* Check if forwarding needs to be updated. */
	if (state != BR_STATE_FORWARDING) {
		if (dev->br_member & (1 << port))
			dev->member &= ~(1 << port);
	}

	/* When topology has changed the function ksz_update_port_member
	 * should be called to modify port forwarding behavior.
	 */
	if (forward != dev->member)
		ksz_update_port_member(dev, port);
}

static void ksz9477_flush_dyn_mac_table(struct ksz_device *dev, int port)
{
	u8 data;

	ksz_read8(dev, REG_SW_LUE_CTRL_2, &data);
	data &= ~(SW_FLUSH_OPTION_M << SW_FLUSH_OPTION_S);
	data |= (SW_FLUSH_OPTION_DYN_MAC << SW_FLUSH_OPTION_S);
	ksz_write8(dev, REG_SW_LUE_CTRL_2, data);
	if (port < dev->mib_port_cnt) {
		/* flush individual port */
		ksz_pread8(dev, port, P_STP_CTRL, &data);
		if (!(data & PORT_LEARN_DISABLE))
			ksz_pwrite8(dev, port, P_STP_CTRL,
				    data | PORT_LEARN_DISABLE);
		ksz_cfg(dev, S_FLUSH_TABLE_CTRL, SW_FLUSH_DYN_MAC_TABLE, true);
		ksz_pwrite8(dev, port, P_STP_CTRL, data);
	} else {
		/* flush all */
		ksz_cfg(dev, S_FLUSH_TABLE_CTRL, SW_FLUSH_STP_TABLE, true);
	}
}

static int ksz9477_port_vlan_filtering(struct dsa_switch *ds, int port,
				       bool flag)
{
	struct ksz_device *dev = ds->priv;
	u16 vlan_ports = dev->vlan_ports;

	if (flag)
		dev->vlan_ports |= (1 << port);
	else
		dev->vlan_ports &= ~(1 << port);
	if ((flag && !vlan_ports) ||
	    (!flag && !dev->vlan_ports && dev->vlan_up)) {
		if (flag) {
			u32 vlan_table[3];

			vlan_table[0] = VLAN_VALID | 0;
			vlan_table[1] = 0;
			vlan_table[2] = dev->port_mask;
			if (ksz9477_set_vlan_table(dev, 0, vlan_table)) {
				dev_dbg(dev->dev, "Failed to set vlan table\n");
				return 0;
			}
			vlan_table[0] = VLAN_VALID | 0;
			vlan_table[1] = dev->port_mask;
			vlan_table[2] = dev->port_mask;
			if (ksz9477_set_vlan_table(dev, 1, vlan_table)) {
				dev_dbg(dev->dev, "Failed to set vlan table\n");
				return 0;
			}
		} else {
			int i;

			for (i = 0; i < dev->port_cnt; i++) {
				if (i == dev->cpu_port)
					continue;
				ksz_pwrite16(dev, i, REG_PORT_DEFAULT_VID, 1);
			}
			dev->vid_ports = 0;
		}
		ksz_cfg(dev, REG_SW_LUE_CTRL_0, SW_VLAN_ENABLE, flag);
		dev->vlan_up = flag;
	}
	if (vlan_ports != dev->vlan_ports) {
		ksz_port_cfg(dev, port, REG_PORT_LUE_CTRL,
			     (PORT_VLAN_LOOKUP_VID_0 | PORT_INGRESS_FILTER),
			     flag);
	}

	return 0;
}

static void ksz9477_port_vlan_add(struct dsa_switch *ds, int port,
				  const struct switchdev_obj_port_vlan *vlan,
				  struct switchdev_trans *trans)
{
	struct ksz_device *dev = ds->priv;
	u32 vlan_table[3];
	u16 fid;
	u16 vid;
	bool untagged = vlan->flags & BRIDGE_VLAN_INFO_UNTAGGED;
	bool pvid = vlan->flags & BRIDGE_VLAN_INFO_PVID;
	u16 new_pvid = 1;

	if (!dev->vlan_up)
		return;

	for (vid = vlan->vid_begin; vid <= vlan->vid_end; vid++) {
		if (ksz9477_get_vlan_table(dev, vid, vlan_table)) {
			dev_dbg(dev->dev, "Failed to get vlan table\n");
			return;
		}

		fid = ksz9477_get_fid(vid);
		vlan_table[0] = VLAN_VALID | fid;
		if (untagged)
			vlan_table[1] |= BIT(port);
		else
			vlan_table[1] &= ~BIT(port);

		/* Keep host port untagged when setting pvid. */
		if (untagged && vid == 1)
			vlan_table[1] |= BIT(dev->cpu_port);
		else
			vlan_table[1] &= ~(BIT(dev->cpu_port));

		vlan_table[2] |= BIT(port) | BIT(dev->cpu_port);

		if (ksz9477_set_vlan_table(dev, vid, vlan_table)) {
			dev_dbg(dev->dev, "Failed to set vlan table\n");
			return;
		}

		/* change PVID */
		if (pvid)
			new_pvid = vid;
	}

	ksz_pread16(dev, port, REG_PORT_DEFAULT_VID, &vid);
	if (new_pvid != (vid & 0xfff)) {
		vid &= ~0xfff;
		vid |= new_pvid;
		ksz_pwrite16(dev, port, REG_PORT_DEFAULT_VID, vid);

		/* Switch may use lookup to forward unicast frame. */
		dev->dev_ops->flush_dyn_mac_table(dev, port);
		dev->vid_ports |= (1 << port);
	}
}

static int ksz9477_port_vlan_del(struct dsa_switch *ds, int port,
				 const struct switchdev_obj_port_vlan *vlan)
{
	struct ksz_device *dev = ds->priv;
	u32 vlan_table[3];
	u16 vid;
	u16 pvid;
	u16 new_pvid = 0;

	if (!dev->vlan_up)
		return 0;

	ksz_pread16(dev, port, REG_PORT_DEFAULT_VID, &pvid);
	pvid = pvid & 0xFFF;

	for (vid = vlan->vid_begin; vid <= vlan->vid_end; vid++) {
		if (ksz9477_get_vlan_table(dev, vid, vlan_table)) {
			dev_dbg(dev->dev, "Failed to get vlan table\n");
			return -ETIMEDOUT;
		}

		vlan_table[2] &= ~BIT(port);

		/* Invalidate the entry if no more member. */
		if (!(vlan_table[2] & ~dev->host_mask))
			vlan_table[0] &= ~VLAN_VALID;

		vlan_table[1] &= ~BIT(port);

		if (pvid == vid)
			new_pvid = 1;

		if (ksz9477_set_vlan_table(dev, vid, vlan_table)) {
			dev_dbg(dev->dev, "Failed to set vlan table\n");
			return -ETIMEDOUT;
		}
	}

	if (new_pvid && new_pvid != pvid) {
		ksz_pwrite16(dev, port, REG_PORT_DEFAULT_VID, new_pvid);

		/* Switch may use lookup to forward unicast frame. */
		dev->dev_ops->flush_dyn_mac_table(dev, port);
		dev->vid_ports &= ~(1 << port);
	}

	return 0;
}

static void ksz9477_port_fdb_add(struct dsa_switch *ds, int port,
				 const struct switchdev_obj_port_fdb *fdb,
				 struct switchdev_trans *trans)
{
	struct ksz_device *dev = ds->priv;
	u32 alu_table[4];
	u32 data;
	int ret = 0;
	u16 vid = fdb->vid;
	const u8 *addr = fdb->addr;
	u16 fid = ksz9477_get_fid(vid);

	mutex_lock(&dev->alu_mutex);

	/* find any entry with mac & vid */
	data = fid << ALU_FID_INDEX_S;
	data |= ((addr[0] << 8) | addr[1]);
	ksz_write32(dev, REG_SW_ALU_INDEX_0, data);

	data = ((addr[2] << 24) | (addr[3] << 16));
	data |= ((addr[4] << 8) | addr[5]);
	ksz_write32(dev, REG_SW_ALU_INDEX_1, data);

	/* start read operation */
	ksz_write32(dev, REG_SW_ALU_CTRL__4, ALU_READ | ALU_START);

	/* wait to be finished */
	ret = readx_poll_timeout(read32_op, REG_SW_ALU_CTRL__4, data,
				 !(data & ALU_START), 10, 1000);
	if (ret < 0) {
		dev_dbg(dev->dev, "Failed to read ALU\n");
		goto exit;
	}

	/* read ALU entry */
	ksz9477_read_table(dev, alu_table);

	/* update ALU entry */
	alu_table[0] = ALU_V_STATIC_VALID;
	alu_table[1] |= BIT(port);
#if 1
	/* Host port can never be specified!? */
	alu_table[1] |= dev->host_mask;
#endif
	if (fid)
		alu_table[1] |= ALU_V_USE_FID;
	alu_table[2] = (fid << ALU_V_FID_S);
	alu_table[2] |= ((addr[0] << 8) | addr[1]);
	alu_table[3] = ((addr[2] << 24) | (addr[3] << 16));
	alu_table[3] |= ((addr[4] << 8) | addr[5]);

	ksz9477_write_table(dev, alu_table);

	ksz_write32(dev, REG_SW_ALU_CTRL__4, ALU_WRITE | ALU_START);

	/* wait to be finished */
	ret = readx_poll_timeout(read32_op, REG_SW_ALU_CTRL__4, data,
				 !(data & ALU_START), 10, 1000);
	if (ret < 0)
		dev_dbg(dev->dev, "Failed to write ALU\n");

exit:
	mutex_unlock(&dev->alu_mutex);
}

static int ksz9477_port_fdb_del(struct dsa_switch *ds, int port,
				const struct switchdev_obj_port_fdb *fdb)
{
	struct ksz_device *dev = ds->priv;
	u32 alu_table[4];
	u32 data;
	u32 mask = 0;
	int ret = 0;
	u16 vid = fdb->vid;
	const u8 *addr = fdb->addr;
	u16 fid = ksz9477_get_fid(vid);

	mutex_lock(&dev->alu_mutex);

	/* read any entry with mac & vid */
	data = fid << ALU_FID_INDEX_S;
	data |= ((addr[0] << 8) | addr[1]);
	ksz_write32(dev, REG_SW_ALU_INDEX_0, data);

	data = ((addr[2] << 24) | (addr[3] << 16));
	data |= ((addr[4] << 8) | addr[5]);
	ksz_write32(dev, REG_SW_ALU_INDEX_1, data);

	/* start read operation */
	ksz_write32(dev, REG_SW_ALU_CTRL__4, ALU_READ | ALU_START);

	/* wait to be finished */
	ret = readx_poll_timeout(read32_op, REG_SW_ALU_CTRL__4, data,
				 !(data & ALU_START), 10, 1000);
	if (ret < 0) {
		dev_dbg(dev->dev, "Failed to read ALU\n");
		goto exit;
	}

	ksz_read32(dev, REG_SW_ALU_VAL_A, &alu_table[0]);
	if (alu_table[0] & ALU_V_STATIC_VALID) {
		ksz_read32(dev, REG_SW_ALU_VAL_B, &alu_table[1]);
		ksz_read32(dev, REG_SW_ALU_VAL_C, &alu_table[2]);
		ksz_read32(dev, REG_SW_ALU_VAL_D, &alu_table[3]);

		/* clear forwarding port */
		alu_table[1] &= ~BIT(port);

#if 1
		/* Host port may never get called to remove the entry. */
		mask = dev->host_mask;
#endif

		/* if there is no port to forward, clear table */
		if (!((alu_table[1] & ALU_V_PORT_MAP) & ~mask)) {
			alu_table[0] = 0;
			alu_table[1] = 0;
			alu_table[2] = 0;
			alu_table[3] = 0;
		}
	} else {
		alu_table[0] = 0;
		alu_table[1] = 0;
		alu_table[2] = 0;
		alu_table[3] = 0;
	}

	ksz9477_write_table(dev, alu_table);

	ksz_write32(dev, REG_SW_ALU_CTRL__4, ALU_WRITE | ALU_START);

	/* wait to be finished */
	ret = readx_poll_timeout(read32_op, REG_SW_ALU_CTRL__4, data,
				 !(data & ALU_START), 10, 1000);
	if (ret < 0)
		dev_dbg(dev->dev, "Failed to write ALU\n");

exit:
	mutex_unlock(&dev->alu_mutex);

	return ret;
}

static void ksz9477_convert_alu(struct alu_struct *alu, u32 *alu_table)
{
	alu->is_static = !!(alu_table[0] & ALU_V_STATIC_VALID);
	alu->is_src_filter = !!(alu_table[0] & ALU_V_SRC_FILTER);
	alu->is_dst_filter = !!(alu_table[0] & ALU_V_DST_FILTER);
	alu->prio_age = (alu_table[0] >> ALU_V_PRIO_AGE_CNT_S) &
			ALU_V_PRIO_AGE_CNT_M;
	alu->mstp = alu_table[0] & ALU_V_MSTP_M;

	alu->is_override = !!(alu_table[1] & ALU_V_OVERRIDE);
	alu->is_use_fid = !!(alu_table[1] & ALU_V_USE_FID);
	alu->port_forward = alu_table[1] & ALU_V_PORT_MAP;

	alu->fid = (alu_table[2] >> ALU_V_FID_S) & ALU_V_FID_M;

	alu->mac[0] = (alu_table[2] >> 8) & 0xFF;
	alu->mac[1] = alu_table[2] & 0xFF;
	alu->mac[2] = (alu_table[3] >> 24) & 0xFF;
	alu->mac[3] = (alu_table[3] >> 16) & 0xFF;
	alu->mac[4] = (alu_table[3] >> 8) & 0xFF;
	alu->mac[5] = alu_table[3] & 0xFF;
}

static int ksz9477_port_fdb_dump(struct dsa_switch *ds, int port,
				 struct switchdev_obj_port_fdb *fdb,
				 int (*cb)(struct switchdev_obj *obj))
{
	struct ksz_device *dev = ds->priv;
	int ret = 0;
	u32 index;
	u32 ksz_data;
	u32 alu_table[4];
	struct alu_struct alu;
	int timeout;
	u32 cnt = 0;

	mutex_lock(&dev->alu_mutex);

	/* start ALU search */
	ksz_write32(dev, REG_SW_ALU_CTRL__4, ALU_START | ALU_SEARCH);

	do {
		timeout = 1000;
		do {
			ksz_read32(dev, REG_SW_ALU_CTRL__4, &ksz_data);
			if ((ksz_data & ALU_VALID) || !(ksz_data & ALU_START))
				break;
			usleep_range(1, 10);
		} while (timeout-- > 0);

		if (!timeout) {
			dev_dbg(dev->dev, "Failed to search ALU\n");
			ret = -ETIMEDOUT;
			goto exit;
		}

		if (!(ksz_data & ALU_VALID))
			goto exit;
		++cnt;
		index = ksz_data;
		index >>= ALU_VALID_CNT_S;
		index &= ALU_VALID_CNT_M;
		if (index != cnt) {
			dev_dbg(dev->dev, "index not matched: %d %d\n",
				index, cnt);
			cnt = index;
		}

		/* read ALU table */
		ksz9477_read_table(dev, alu_table);

		ksz9477_convert_alu(&alu, alu_table);

		if (alu.port_forward & BIT(port)) {
			fdb->vid = alu.fid;
			if (alu.is_static)
				fdb->ndm_state = NUD_NOARP;
			else
				fdb->ndm_state = NUD_REACHABLE;
			ether_addr_copy(fdb->addr, alu.mac);

			ret = cb(&fdb->obj);
			if (ret)
				goto exit;
		}
	} while (ksz_data & ALU_START);

exit:

	/* stop ALU search */
	ksz_write32(dev, REG_SW_ALU_CTRL__4, 0);
	ksz_data >>= ALU_VALID_CNT_S;
	ksz_data &= ALU_VALID_CNT_M;
	if (ksz_data != cnt)
		dev_dbg(dev->dev, "count not matched: %d %d\n",
			ksz_data, cnt);

	mutex_unlock(&dev->alu_mutex);

	return ret;
}

static void ksz9477_port_mdb_add(struct dsa_switch *ds, int port,
				 const struct switchdev_obj_port_mdb *mdb,
				 struct switchdev_trans *trans)
{
#if 1
	struct switchdev_obj_port_fdb fdb;

	ether_addr_copy(fdb.addr, mdb->addr);
	fdb.vid = mdb->vid;
	memcpy(fdb.addr, mdb->addr, ETH_ALEN);
	ksz9477_port_fdb_add(ds, port, &fdb, trans);
#else
	struct ksz_device *dev = ds->priv;
	u32 static_table[4];
	u32 data;
	int index;
	int ret;
	u32 mac_hi, mac_lo;
	u16 fid;

	fid = ksz9477_get_fid(mdb->vid);
	mac_hi = ((mdb->addr[0] << 8) | mdb->addr[1]);
	mac_lo = ((mdb->addr[2] << 24) | (mdb->addr[3] << 16));
	mac_lo |= ((mdb->addr[4] << 8) | mdb->addr[5]);

	mutex_lock(&dev->alu_mutex);

	for (index = 0; index < dev->num_statics; index++) {
		/* find empty slot first */
		data = (index << ALU_STAT_INDEX_S) |
			ALU_STAT_READ | ALU_STAT_START;
		ksz_write32(dev, REG_SW_ALU_STAT_CTRL__4, data);

		/* wait to be finished */
		ret = readx_poll_timeout(read32_op, REG_SW_ALU_STAT_CTRL__4,
					 data, !(data & ALU_STAT_START),
					 10, 1000);
		if (ret < 0) {
			dev_dbg(dev->dev, "Failed to read ALU STATIC\n");
			goto exit;
		}

		/* read ALU static table */
		ksz9477_read_table(dev, static_table);

		if (static_table[0] & ALU_V_STATIC_VALID) {
			/* check this has same vid & mac address */
			if (((static_table[2] >> ALU_V_FID_S) == fid) &&
			    ((static_table[2] & ALU_V_MAC_ADDR_HI) == mac_hi) &&
			    static_table[3] == mac_lo) {
				/* found matching one */
				break;
			}
		} else {
			/* found empty one */
			break;
		}
	}

	/* no available entry */
	if (index == dev->num_statics)
		goto exit;

	/* add entry */
	static_table[0] = ALU_V_STATIC_VALID;
	static_table[1] |= BIT(port);
#if 1
	/* Host port can never be specified!? */
	static_table[1] |= dev->host_mask;
#endif
	if (fid)
		static_table[1] |= ALU_V_USE_FID;
	static_table[2] = (fid << ALU_V_FID_S);
	static_table[2] |= mac_hi;
	static_table[3] = mac_lo;

	ksz9477_write_table(dev, static_table);

	data = (index << ALU_STAT_INDEX_S) | ALU_STAT_START;
	ksz_write32(dev, REG_SW_ALU_STAT_CTRL__4, data);

	/* wait to be finished */
	ret = readx_poll_timeout(read32_op, REG_SW_ALU_STAT_CTRL__4, data,
				 !(data & ALU_STAT_START), 10, 1000);
	if (ret < 0)
		dev_dbg(dev->dev, "Failed to read ALU STATIC\n");

exit:
	mutex_unlock(&dev->alu_mutex);
#endif
}

static int ksz9477_port_mdb_del(struct dsa_switch *ds, int port,
				const struct switchdev_obj_port_mdb *mdb)
{
#if 1
	struct switchdev_obj_port_fdb fdb;

	ether_addr_copy(fdb.addr, mdb->addr);
	fdb.vid = mdb->vid;
	memcpy(fdb.addr, mdb->addr, ETH_ALEN);
	return ksz9477_port_fdb_del(ds, port, &fdb);
#else
	struct ksz_device *dev = ds->priv;
	u32 static_table[4];
	u32 data;
	int index;
	int ret = 0;
	u32 mac_hi, mac_lo;
	u16 fid;

	fid = ksz9477_get_fid(mdb->vid);
	mac_hi = ((mdb->addr[0] << 8) | mdb->addr[1]);
	mac_lo = ((mdb->addr[2] << 24) | (mdb->addr[3] << 16));
	mac_lo |= ((mdb->addr[4] << 8) | mdb->addr[5]);

	mutex_lock(&dev->alu_mutex);

	for (index = 0; index < dev->num_statics; index++) {
		/* find empty slot first */
		data = (index << ALU_STAT_INDEX_S) |
			ALU_STAT_READ | ALU_STAT_START;
		ksz_write32(dev, REG_SW_ALU_STAT_CTRL__4, data);

		/* wait to be finished */
		ret = readx_poll_timeout(read32_op, REG_SW_ALU_STAT_CTRL__4,
					 data, !(data & ALU_STAT_START),
					 10, 1000);
		if (ret < 0) {
			dev_dbg(dev->dev, "Failed to read ALU STATIC\n");
			goto exit;
		}

		/* read ALU static table */
		ksz9477_read_table(dev, static_table);

		if (static_table[0] & ALU_V_STATIC_VALID) {
			/* check this has same vid & mac address */

			if (((static_table[2] >> ALU_V_FID_S) == fid) &&
			    ((static_table[2] & ALU_V_MAC_ADDR_HI) == mac_hi) &&
			    static_table[3] == mac_lo) {
				/* found matching one */
				break;
			}
		}
	}

	/* no available entry */
	if (index == dev->num_statics)
		goto exit;

	/* clear port */
	static_table[1] &= ~BIT(port);

	if (((static_table[1] & ALU_V_PORT_MAP) & ~dev->host_mask) == 0) {
		/* delete entry */
		static_table[0] = 0;
		static_table[1] = 0;
		static_table[2] = 0;
		static_table[3] = 0;
	}

	ksz9477_write_table(dev, static_table);

	data = (index << ALU_STAT_INDEX_S) | ALU_STAT_START;
	ksz_write32(dev, REG_SW_ALU_STAT_CTRL__4, data);

	/* wait to be finished */
	ret = readx_poll_timeout(read32_op, REG_SW_ALU_STAT_CTRL__4, data,
				 !(data & ALU_STAT_START), 10, 1000);
	if (ret < 0)
		dev_dbg(dev->dev, "Failed to read ALU STATIC\n");

exit:
	mutex_unlock(&dev->alu_mutex);

	return ret;
#endif
}

#if 0
static int ksz9477_port_mirror_add(struct dsa_switch *ds, int port,
				   struct dsa_mall_mirror_tc_entry *mirror,
				   bool ingress)
{
	struct ksz_device *dev = ds->priv;

	if (ingress)
		ksz_port_cfg(dev, port, P_MIRROR_CTRL, PORT_MIRROR_RX, true);
	else
		ksz_port_cfg(dev, port, P_MIRROR_CTRL, PORT_MIRROR_TX, true);

	ksz_port_cfg(dev, port, P_MIRROR_CTRL, PORT_MIRROR_SNIFFER, false);

	/* configure mirror port */
	ksz_port_cfg(dev, mirror->to_local_port, P_MIRROR_CTRL,
		     PORT_MIRROR_SNIFFER, true);

	ksz_cfg(dev, S_MIRROR_CTRL, SW_MIRROR_RX_TX, false);

	return 0;
}

static void ksz9477_port_mirror_del(struct dsa_switch *ds, int port,
				    struct dsa_mall_mirror_tc_entry *mirror)
{
	struct ksz_device *dev = ds->priv;
	u8 data;

	if (mirror->ingress)
		ksz_port_cfg(dev, port, P_MIRROR_CTRL, PORT_MIRROR_RX, false);
	else
		ksz_port_cfg(dev, port, P_MIRROR_CTRL, PORT_MIRROR_TX, false);

	ksz_pread8(dev, port, P_MIRROR_CTRL, &data);

	if (!(data & (PORT_MIRROR_RX | PORT_MIRROR_TX)))
		ksz_port_cfg(dev, mirror->to_local_port, P_MIRROR_CTRL,
			     PORT_MIRROR_SNIFFER, false);
}
#endif

static void ksz9477_phy_setup(struct ksz_device *dev, int port,
			      struct phy_device *phy)
{
	if (port < dev->phy_port_cnt) {
		/* SUPPORTED_Asym_Pause and SUPPORTED_Pause can be removed to
		 * disable flow control when rate limiting is used.
		 */
		phy->supported |= SUPPORTED_Pause;
		phy->advertising = phy->supported;
	}
}

static bool ksz9477_get_gbit(struct ksz_device *dev, u8 data)
{
	bool gbit;

	if (dev->features & NEW_XMII)
		gbit = !(data & PORT_MII_NOT_1GBIT);
	else
		gbit = !!(data & PORT_MII_1000MBIT_S1);
	return gbit;
}

static void ksz9477_set_gbit(struct ksz_device *dev, bool gbit, u8 *data)
{
	if (dev->features & NEW_XMII) {
		if (gbit)
			*data &= ~PORT_MII_NOT_1GBIT;
		else
			*data |= PORT_MII_NOT_1GBIT;
	} else {
		if (gbit)
			*data |= PORT_MII_1000MBIT_S1;
		else
			*data &= ~PORT_MII_1000MBIT_S1;
	}
}

static int ksz9477_get_xmii(struct ksz_device *dev, u8 data)
{
	int mode;

	if (dev->features & NEW_XMII) {
		switch (data & PORT_MII_SEL_M) {
		case PORT_MII_SEL:
			mode = 0;
			break;
		case PORT_RMII_SEL:
			mode = 1;
			break;
		case PORT_GMII_SEL:
			mode = 2;
			break;
		default:
			mode = 3;
		}
	} else {
		switch (data & PORT_MII_SEL_M) {
		case PORT_MII_SEL_S1:
			mode = 0;
			break;
		case PORT_RMII_SEL_S1:
			mode = 1;
			break;
		case PORT_GMII_SEL_S1:
			mode = 2;
			break;
		default:
			mode = 3;
		}
	}
	return mode;
}

static void ksz9477_set_xmii(struct ksz_device *dev, int mode, u8 *data)
{
	u8 xmii;

	if (dev->features & NEW_XMII) {
		switch (mode) {
		case 0:
			xmii = PORT_MII_SEL;
			break;
		case 1:
			xmii = PORT_RMII_SEL;
			break;
		case 2:
			xmii = PORT_GMII_SEL;
			break;
		default:
			xmii = PORT_RGMII_SEL;
			break;
		}
	} else {
		switch (mode) {
		case 0:
			xmii = PORT_MII_SEL_S1;
			break;
		case 1:
			xmii = PORT_RMII_SEL_S1;
			break;
		case 2:
			xmii = PORT_GMII_SEL_S1;
			break;
		default:
			xmii = PORT_RGMII_SEL_S1;
			break;
		}
	}
	*data &= ~PORT_MII_SEL_M;
	*data |= xmii;
}

static phy_interface_t ksz9477_get_interface(struct ksz_device *dev, int port)
{
	bool gbit;
	int mode;
	u8 data8;
	phy_interface_t interface;

	if (port < dev->phy_port_cnt)
		return PHY_INTERFACE_MODE_NA;
	ksz_pread8(dev, port, REG_PORT_XMII_CTRL_1, &data8);
	gbit = ksz9477_get_gbit(dev, data8);
	mode = ksz9477_get_xmii(dev, data8);
	switch (mode) {
	case 2:
		interface = PHY_INTERFACE_MODE_GMII;
		if (gbit)
			break;
	case 0:
		interface = PHY_INTERFACE_MODE_MII;
		break;
	case 1:
		interface = PHY_INTERFACE_MODE_RMII;
		break;
	default:
		interface = PHY_INTERFACE_MODE_RGMII;
		if (data8 & PORT_RGMII_ID_EG_ENABLE)
			interface = PHY_INTERFACE_MODE_RGMII_TXID;
		if (data8 & PORT_RGMII_ID_IG_ENABLE) {
			interface = PHY_INTERFACE_MODE_RGMII_RXID;
			if (data8 & PORT_RGMII_ID_EG_ENABLE)
				interface = PHY_INTERFACE_MODE_RGMII_ID;
		}
		break;
	}
	return interface;
}

static void ksz9477_port_setup(struct ksz_device *dev, int port, bool cpu_port)
{
	u8 data8;
	u8 member;
	u16 data16;
	struct ksz_port *p = &dev->ports[port];

#ifdef SIMULATE_CASCADE_SWITCH
	if (ksz9477_skip_hw(dev, port))
		return;
#endif

	/* enable tag tail for host port */
	if (cpu_port)
		ksz_port_cfg(dev, port, REG_PORT_CTRL_0, PORT_TAIL_TAG_ENABLE,
			     true);

	ksz_port_cfg(dev, port, REG_PORT_CTRL_0, PORT_MAC_LOOPBACK, false);

	/* set back pressure */
	ksz_port_cfg(dev, port, REG_PORT_MAC_CTRL_1, PORT_BACK_PRESSURE, true);

	/* enable broadcast storm limit */
	ksz_port_cfg(dev, port, P_BCAST_STORM_CTRL, PORT_BROADCAST_STORM, true);

	/* disable DiffServ priority */
	ksz_port_cfg(dev, port, P_PRIO_CTRL, PORT_DIFFSERV_PRIO_ENABLE, false);

	/* replace priority */
	ksz_port_cfg(dev, port, REG_PORT_MRI_MAC_CTRL, PORT_USER_PRIO_CEILING,
		     false);
	ksz9477_port_cfg32(dev, port, REG_PORT_MTI_QUEUE_CTRL_0__4,
			   MTI_PVID_REPLACE, false);

	/* enable 802.1p priority */
	ksz_port_cfg(dev, port, P_PRIO_CTRL, PORT_802_1P_PRIO_ENABLE, true);

	if (port < dev->phy_port_cnt) {
		/* do not force flow control */
		ksz_port_cfg(dev, port, REG_PORT_CTRL_0,
			     PORT_FORCE_TX_FLOW_CTRL | PORT_FORCE_RX_FLOW_CTRL,
			     false);

	} else {
		/* force flow control */
		ksz_port_cfg(dev, port, REG_PORT_CTRL_0,
			     PORT_FORCE_TX_FLOW_CTRL | PORT_FORCE_RX_FLOW_CTRL,
			     true);

		/* configure MAC to 1G & RGMII mode */
		ksz_pread8(dev, port, REG_PORT_XMII_CTRL_1, &data8);
		switch (dev->interface) {
		case PHY_INTERFACE_MODE_MII:
			ksz9477_set_xmii(dev, 0, &data8);
			ksz9477_set_gbit(dev, false, &data8);
			p->phydev.speed = SPEED_100;
			break;
		case PHY_INTERFACE_MODE_RMII:
			ksz9477_set_xmii(dev, 1, &data8);
			ksz9477_set_gbit(dev, false, &data8);
			p->phydev.speed = SPEED_100;
			break;
		case PHY_INTERFACE_MODE_GMII:
			ksz9477_set_xmii(dev, 2, &data8);
			ksz9477_set_gbit(dev, true, &data8);
			p->phydev.speed = SPEED_1000;
			break;
		default:
			ksz9477_set_xmii(dev, 3, &data8);
			ksz9477_set_gbit(dev, true, &data8);
			data8 &= ~PORT_RGMII_ID_IG_ENABLE;
			data8 &= ~PORT_RGMII_ID_EG_ENABLE;
			if (dev->interface == PHY_INTERFACE_MODE_RGMII_ID ||
			    dev->interface == PHY_INTERFACE_MODE_RGMII_RXID)
				data8 |= PORT_RGMII_ID_IG_ENABLE;
			if (dev->interface == PHY_INTERFACE_MODE_RGMII_ID ||
			    dev->interface == PHY_INTERFACE_MODE_RGMII_TXID)
				data8 |= PORT_RGMII_ID_EG_ENABLE;
			p->phydev.speed = SPEED_1000;
			break;
		}
		ksz_pwrite8(dev, port, REG_PORT_XMII_CTRL_1, data8);
		p->phydev.duplex = 1;
		if (!p->sgmii)
			p->phydev.link = 1;
	}
	if (cpu_port) {
		member = dev->port_mask;
		dev->on_ports = dev->host_mask;
		dev->live_ports = dev->host_mask;
	} else {
		member = dev->host_mask | p->vid_member;
		dev->on_ports |= (1 << port);

		/* Link was detected before port is enabled. */
		if (p->phydev.link)
			dev->live_ports |= (1 << port);
	}
	ksz9477_cfg_port_member(dev, port, member);

	/* clear pending interrupts */
	if (port < dev->phy_port_cnt)
		ksz_pread16(dev, port, REG_PORT_PHY_INT_ENABLE, &data16);
	if (port < dev->phy_port_cnt) {
		u32 data;
		u16 val;

		if ((dev->features & IS_9893))
			port_setup_9893(dev, port);
		else
			port_setup_eee(dev, port);

		/* Disable EEE for 1588 PTP. */
		if (dev->features & PTP_HW) {
			port_mmd_read(dev, port, MMD_DEVICE_ID_EEE_ADV,
				      MMD_EEE_ADV, &val, 1);
			val &= ~(EEE_ADV_100MBIT | EEE_ADV_1GBIT);
			port_mmd_write(dev, port, MMD_DEVICE_ID_EEE_ADV,
				       MMD_EEE_ADV, &val, 1);
		}

		p->intr_mask = PORT_PHY_INT;
		val = LINK_DOWN_INT | LINK_UP_INT;

		ksz_pread32(dev, port, REG_PORT_PHY_INT_ENABLE & ~3, &data);
		data &= 0xffff00ff;
		data |= (u32)val << 8;
		ksz_pwrite32(dev, port, REG_PORT_PHY_INT_ENABLE & ~3, data);
	}
	if (p->sgmii) {
		bool pcs = true;
		bool master = false;
		bool autoneg = true;

		if (dev->sgmii_mode == 0) {
			master = true;
			autoneg = false;
		} else if (dev->sgmii_mode == 1) {
			pcs = false;
			master = true;
		}
		port_sgmii_setup(dev, port, pcs, master, autoneg, 2, 1);
		p->intr_mask = PORT_SGMII_INT;

		/* Make invalid so the correct value is set. */
		p->link_val = 0xff;
		sgmii_port_get_speed(dev, port);
	}
	ksz_pwrite8(dev, port, REG_PORT_INT_MASK,
		    ~p->intr_mask & PORT_INT_MASK);
}

static void ksz9477_config_cpu_port(struct dsa_switch *ds)
{
	struct ksz_device *dev = ds->priv;
	struct ksz_port *p;
	int i;

	/* Setup the upstream port first. */
	i = dsa_upstream_port(ds);
	if (i >= 0 && (dev->cpu_ports & (1 << i))) {
		phy_interface_t interface;

		dev->cpu_port = i;
		dev->host_mask = (1 << i);
		dev->port_mask |= dev->host_mask;

		if (i >= dev->phy_port_cnt) {
			interface = ksz9477_get_interface(dev, i);
			if (!dev->interface && interface)
				dev->interface = interface;
			if (interface && interface != dev->interface)
				dev_info(dev->dev,
					 "use %s instead of %s\n",
					  phy_modes(dev->interface),
					  phy_modes(interface));
		}

		/* enable upstream port */
		ksz9477_port_setup(dev, i, true);
		p = &dev->ports[i];
		p->vid_member = dev->port_mask;
		p->on = 1;
	}

	dev->member = dev->host_mask;

	for (i = 0; i < dev->mib_port_cnt; i++) {
		if (i == dsa_upstream_port(ds))
			continue;
		p = &dev->ports[i];

		/* Initialize to non-zero so that ksz_cfg_port_member() will
		 * be called.
		 */
		p->vid_member = (1 << i);
		p->member = dev->port_mask;
		p->on = 1;

#ifdef SIMULATE_CASCADE_SWITCH
		if (dev->first) {
			struct dsa_switch *mds = dev->first->ds;

			if (dev->first->host_mask & (1 << i))
				continue;
			if (dsa_is_dsa_port(mds, i))
				continue;
		}
#endif
		if (dsa_is_dsa_port(ds, i)) {
			ksz9477_port_setup(dev, i, false);
		} else {
			ksz9477_port_stp_state_set(ds, i, BR_STATE_DISABLED);
		}
		if (i < dev->phy_port_cnt)
			p->phy = 1;
		if (dev->chip_id == 0x00947700 && i == 6) {
			p->sgmii = 1;
			p->phy = port_sgmii_detect(dev, i);
		}
	}

	/* Need a timer to check link down if using fiber SFP. */
	if (dev->sgmii_mode != 1)
		return;

	INIT_WORK(&dev->sgmii_check, sgmii_check_work);
	setup_timer(&dev->sgmii_timer, sgmii_monitor, (unsigned long)dev);
	dev->sgmii_timer.expires = jiffies + msecs_to_jiffies(2000);
	add_timer(&dev->sgmii_timer);
}

static int ksz9477_setup(struct dsa_switch *ds)
{
	struct ksz_device *dev = ds->priv;
	int ret = 0;

	dev->vlan_cache = devm_kcalloc(dev->dev, sizeof(struct vlan_table),
				       dev->num_vlans, GFP_KERNEL);
	if (!dev->vlan_cache)
		return -ENOMEM;

#ifdef SIMULATE_CASCADE_SWITCH
	if (dev->first) {
		ksz9477_config_cpu_port(ds);
		return 0;
	}
#endif
	ret = ksz9477_reset_switch(dev);
	if (ret) {
		dev_err(ds->dev, "failed to reset switch\n");
		return ret;
	}

	/* Do not work correctly with tail tagging. */
	ksz_cfg(dev, REG_SW_MAC_CTRL_0, SW_CHECK_LENGTH, false);

	/* accept packet up to 2000bytes */
	ksz_cfg(dev, REG_SW_MAC_CTRL_1, SW_LEGAL_PACKET_DISABLE, true);

	ksz9477_config_cpu_port(ds);

	ksz_cfg(dev, REG_SW_MAC_CTRL_1, MULTICAST_STORM_DISABLE, true);

	/* Required for port partitioning. */
	ksz9477_cfg32(dev, REG_SW_QM_CTRL__4, UNICAST_VLAN_BOUNDARY,
		      true);

	/* queue based egress rate limit */
	ksz_cfg(dev, REG_SW_MAC_CTRL_5, SW_OUT_RATE_LIMIT_QUEUE_BASED, true);

	/* enable global MIB counter freeze function */
	ksz_cfg(dev, REG_SW_MAC_CTRL_6, SW_MIB_COUNTER_FREEZE, true);

	/* start switch */
	ksz_cfg(dev, REG_SW_OPERATION, SW_START, true);

	ksz_init_mib_timer(dev);

	return 0;
}

static irqreturn_t ksz9477_switch_irq_thread(int ireq, void *dev_id)
{
	struct ksz_device *dev = dev_id;
	irqreturn_t result = IRQ_NONE;
	u32 data;
	int port;
	int ret;

	ret = ksz_read32(dev, REG_SW_INT_STATUS__4, &data);
	if (ret)
		return result;

	ret = ksz_read32(dev, REG_SW_PORT_INT_STATUS__4, &data);
	if (ret)
		return result;

	for (port = 0; port < dev->port_cnt; port++) {
		if (data & BIT(port)) {
			struct phy_device *phydev =
				dev->ports[port].actual_phydev;
			u8 data8;

			ksz_pread8(dev, port, REG_PORT_INT_STATUS, &data8);

			result = IRQ_HANDLED;
			if (data8 & PORT_PHY_INT) {
				u8 val;

				/* The status is cleared after read. */
				ksz_pread8(dev, port, REG_PORT_PHY_INT_STATUS,
					   &val);
				if ((val & (LINK_DOWN_INT | LINK_UP_INT)) &&
				    phydev) {
					phy_trigger_machine(phydev, true);
				}
			}
			if (data8 & PORT_SGMII_INT) {
				u16 data16 = 0;

				port_sgmii_w(dev, port, SR_MII,
					     MMD_SR_MII_AUTO_NEG_STATUS,
					     &data16, 1);
				ret = sgmii_port_get_speed(dev, port);
				if ((ret & 2) && phydev)
					phy_trigger_machine(phydev, true);
			}
		}
	}

	return result;
}

static struct dsa_switch_ops ksz9477_switch_ops = {
	.get_tag_protocol	= ksz9477_get_tag_protocol,
	.setup			= ksz9477_setup,
	.phy_read		= ksz9477_phy_read16,
	.phy_write		= ksz9477_phy_write16,
	.adjust_link		= ksz_adjust_link,
	.port_enable		= ksz_enable_port,
	.port_disable		= ksz_disable_port,
	.get_strings		= ksz9477_get_strings,
	.get_ethtool_stats	= ksz_get_ethtool_stats,
	.get_sset_count		= ksz_sset_count,
	.port_bridge_join	= ksz_port_bridge_join,
	.port_bridge_leave	= ksz_port_bridge_leave,
	.port_stp_state_set	= ksz9477_port_stp_state_set,
	.port_fast_age		= ksz_port_fast_age,
	.port_vlan_filtering	= ksz9477_port_vlan_filtering,
	.port_vlan_prepare	= ksz_port_vlan_prepare,
	.port_vlan_add		= ksz9477_port_vlan_add,
	.port_vlan_del		= ksz9477_port_vlan_del,
	.port_fdb_dump		= ksz9477_port_fdb_dump,
	.port_fdb_add		= ksz9477_port_fdb_add,
	.port_fdb_del		= ksz9477_port_fdb_del,
	.port_mdb_prepare       = ksz_port_mdb_prepare,
	.port_mdb_add           = ksz9477_port_mdb_add,
	.port_mdb_del           = ksz9477_port_mdb_del,
#if 0
	.port_mirror_add	= ksz9477_port_mirror_add,
	.port_mirror_del	= ksz9477_port_mirror_del,
#endif
};

#define KSZ9477_REGS_SIZE		0x8000

static struct bin_attribute ksz9477_registers_attr = {
	.attr = {
		.name	= "registers",
		.mode	= 00600,
	},
	.size	= KSZ9477_REGS_SIZE,
	.read	= ksz_registers_read,
	.write	= ksz_registers_write,
};

#define KSZ_CHIP_NAME_SIZE		18

static const char *ksz9477_chip_names[KSZ_CHIP_NAME_SIZE] = {
	"Microchip KSZ9897",
	"Microchip KSZ9896",
	"Microchip KSZ9567",
	"Microchip KSZ8567",
	"Microchip KSZ8565",
	"Microchip KSZ9477",
	"Microchip KSZ9893",
	"Microchip KSZ9563",
	"Microchip KSZ8563",
};

enum {
	KSZ9897_SW_CHIP,
	KSZ9896_SW_CHIP,
	KSZ9567_SW_CHIP,
	KSZ8567_SW_CHIP,
	KSZ8565_SW_CHIP,
	KSZ9477_SW_CHIP,
	KSZ9893_SW_CHIP,
	KSZ9563_SW_CHIP,
	KSZ8563_SW_CHIP,
};

static int kszphy_config_init(struct phy_device *phydev)
{
	return 0;
}

static struct phy_driver ksz9477_phy_driver[] = {
{
	.phy_id		= PHY_ID_KSZ989X_SW,
	.phy_id_mask	= 0x00ffffff,
	.name		= "Microchip KSZ989X",
	.features	= PHY_GBIT_FEATURES,
	.flags		= PHY_HAS_INTERRUPT,
	.config_init	= kszphy_config_init,
	.config_aneg	= genphy_config_aneg,
	.read_status	= genphy_read_status,
	.config_aneg	= genphy_config_aneg,
	.suspend	= genphy_suspend,
	.resume		= genphy_resume,
}, {
	.phy_id		= PHY_ID_KSZ889X_SW,
	.phy_id_mask	= 0x00ffffff,
	.name		= "Microchip KSZ889X",
	.features	= PHY_BASIC_FEATURES,
	.flags		= PHY_HAS_INTERRUPT,
	.config_init	= kszphy_config_init,
	.config_aneg	= genphy_config_aneg,
	.read_status	= genphy_read_status,
	.suspend	= genphy_suspend,
	.resume		= genphy_resume,
},
};

static int ksz9477_switch_detect(struct ksz_device *dev)
{
	u8 data8;
	u8 id_hi;
	u8 id_lo;
	u32 id32;
	int ret;
	int chip = -1;

	/* turn off SPI DO Edge select */
	ret = ksz_read8(dev, REG_SW_GLOBAL_SERIAL_CTRL_0, &data8);
	if (ret)
		return ret;
	if (data8 == 0xff)
		return -ENODEV;

	data8 &= ~SPI_AUTO_EDGE_DETECTION;
	ret = ksz_write8(dev, REG_SW_GLOBAL_SERIAL_CTRL_0, data8);
	if (ret)
		return ret;

	/* read chip id */
	ret = ksz_read32(dev, REG_CHIP_ID0__1, &id32);
	if (ret)
		return ret;
	ret = ksz_read8(dev, REG_GLOBAL_OPTIONS, &data8);
	if (ret)
		return ret;

	/* Number of ports can be reduced depending on chip. */
	dev->mib_port_cnt = TOTAL_PORT_NUM;
	dev->phy_port_cnt = 5;
	dev->features = GBIT_SUPPORT;

	id_hi = (u8)(id32 >> 16);
	id_lo = (u8)(id32 >> 8);
	if ((id_lo & 0xf) == 3) {
		dev->features |= IS_9893;
		if (data8 & SW_QW_ABLE)
			dev->features &= ~GBIT_SUPPORT;
		dev->mib_port_cnt = 3;
		dev->phy_port_cnt = 2;
		if (!(data8 & SW_AVB_ABLE))
			chip = KSZ9893_SW_CHIP;
		else if (data8 & SW_QW_ABLE)
			chip = KSZ8563_SW_CHIP;
		else
			chip = KSZ9563_SW_CHIP;
		if (!(data8 & SW_AVB_ABLE))
			dev->features |= PTP_HW;
	} else {
		dev->features |= NEW_XMII;
		if (!(data8 & SW_GIGABIT_ABLE))
			dev->features &= ~GBIT_SUPPORT;
		if ((id_lo & 0xf) == 6)
			dev->mib_port_cnt = 6;
		if (id_hi == FAMILY_ID_94)
			chip = KSZ9477_SW_CHIP;
		else if (id_hi == FAMILY_ID_98 && id_lo == CHIP_ID_97)
			chip = KSZ9897_SW_CHIP;
		else if (id_hi == FAMILY_ID_98 && id_lo == CHIP_ID_96)
			chip = KSZ9896_SW_CHIP;
		else if (id_hi == FAMILY_ID_95 && id_lo == CHIP_ID_67)
			chip = KSZ9567_SW_CHIP;
		else if (id_hi == FAMILY_ID_85 && id_lo == CHIP_ID_67)
			chip = KSZ8567_SW_CHIP;
		if (id_lo == CHIP_ID_67) {
			id_hi = FAMILY_ID_98;
			id_lo = CHIP_ID_97;
		} else if (id_lo == CHIP_ID_66) {
			id_hi = FAMILY_ID_98;
			id_lo = CHIP_ID_96;
		}
		if (id_hi == FAMILY_ID_94 ||
		    id_lo == CHIP_ID_67 ||
		    id_lo == CHIP_ID_66)
			dev->features |= PTP_HW;
	}
	if (dev->dev->of_node) {
		char name[80];

		if (!of_modalias_node(dev->dev->of_node, name, sizeof(name))) {
			if (!strcmp(name, "ksz8565")) {
				chip = KSZ8565_SW_CHIP;
				id_hi = FAMILY_ID_98;
				id_lo = 0x95;
			}
		}
	}
	id32 = (id_hi << 16) | (id_lo << 8);
 
 	dev->chip_id = id32;
	if (chip >= 0) {
		int id;

		dev->name = ksz9477_chip_names[chip];
		if (dev->features & GBIT_SUPPORT)
			id = 0;
		else
			id = 1;
		strlcpy(ksz9477_phy_driver[id].name, ksz9477_chip_names[chip],
			KSZ_CHIP_NAME_SIZE);
	}
	if (dev->dev->of_node) {
		struct device_node *ports, *port;

		ports = of_get_child_by_name(dev->dev->of_node, "ports");
		if (ports) {
			u32 mode, reg;
			int err;

			for_each_available_child_of_node(ports, port) {
				err = of_property_read_u32(port, "reg", &reg);
				if (err)
					break;
				err = of_property_read_u32(port, "mode", &mode);
				if (err)
					continue;
				if (dev->chip_id == 0x00947700 && reg == 6) {
					dev->sgmii_mode = (u8) mode;
				}
			}
		}
	}

	return 0;
}

struct ksz_chip_data {
	u32 chip_id;
	const char *dev_name;
	int num_vlans;
	int num_alus;
	int num_statics;
	int cpu_ports;
	int port_cnt;
};

static const struct ksz_chip_data ksz9477_switch_chips[] = {
	{
		.chip_id = 0x00947700,
		.dev_name = "KSZ9477",
		.num_vlans = 4096,
		.num_alus = 4096,
		.num_statics = 16,
		.cpu_ports = 0x7F,	/* can be configured as cpu port */
		.port_cnt = 7,		/* total physical port count */
	},
	{
		.chip_id = 0x00989700,
		.dev_name = "KSZ9897",
		.num_vlans = 4096,
		.num_alus = 4096,
		.num_statics = 16,
		.cpu_ports = 0x7F,	/* can be configured as cpu port */
		.port_cnt = 7,		/* total physical port count */
	},
	{
		.chip_id = 0x00989600,
		.dev_name = "KSZ9896",
		.num_vlans = 4096,
		.num_alus = 4096,
		.num_statics = 16,
		.cpu_ports = 0x3F,	/* can be configured as cpu port */
		.port_cnt = 6,		/* total port count */
	},
	{
		.chip_id = 0x00989300,
		.dev_name = "KSZ9893",
		.num_vlans = 4096,
		.num_alus = 4096,
		.num_statics = 16,
		.cpu_ports = 0x07,	/* can be configured as cpu port */
		.port_cnt = 3,		/* total port count */
	},
	{
		.chip_id = 0x00989500,
		.dev_name = "KSZ8565",
		.num_vlans = 4096,
		.num_alus = 4096,
		.num_statics = 16,
		.cpu_ports = 0x4F,	/* can be configured as cpu port */
		.port_cnt = 7,		/* total port count */
	},
};

static int ksz9477_switch_init(struct ksz_device *dev)
{
	int i;

	dev->ds->ops = &ksz9477_switch_ops;

	for (i = 0; i < ARRAY_SIZE(ksz9477_switch_chips); i++) {
		const struct ksz_chip_data *chip = &ksz9477_switch_chips[i];

		if (dev->chip_id == chip->chip_id) {
			if (!dev->name)
				dev->name = chip->dev_name;
			dev->num_vlans = chip->num_vlans;
			dev->num_alus = chip->num_alus;
			dev->num_statics = chip->num_statics;
			dev->port_cnt = chip->port_cnt;
			dev->cpu_ports = chip->cpu_ports;

			break;
		}
	}

	/* no switch found */
	if (!dev->port_cnt)
		return -ENODEV;

	dev->port_mask = (1 << dev->port_cnt) - 1;
	dev->port_mask &= dev->cpu_ports;

	dev->reg_mib_cnt = SWITCH_COUNTER_NUM;
	dev->mib_cnt = TOTAL_SWITCH_COUNTER_NUM;

	i = dev->mib_port_cnt;
	dev->ports = devm_kzalloc(dev->dev, sizeof(struct ksz_port) * i,
				  GFP_KERNEL);
	if (!dev->ports)
		return -ENOMEM;
	for (i = 0; i < dev->mib_port_cnt; i++) {
		mutex_init(&dev->ports[i].mib.cnt_mutex);
		dev->ports[i].mib.counters =
			devm_kzalloc(dev->dev,
				     sizeof(u64) *
				     (TOTAL_SWITCH_COUNTER_NUM + 1),
				     GFP_KERNEL);
		if (!dev->ports[i].mib.counters)
			return -ENOMEM;
	}
	if (dev->irq > 0) {
		unsigned long irqflags = IRQF_TRIGGER_LOW;
		int ret;

		irqflags |= IRQF_ONESHOT;
		ret = devm_request_threaded_irq(dev->dev, dev->irq, NULL,
						ksz9477_switch_irq_thread,
						irqflags,
						dev_name(dev->dev),
						dev);
		if (ret) {
			dev_err(dev->dev, "failed to request IRQ.\n");
			return ret;
		}
	}

#ifdef SIMULATE_CASCADE_SWITCH
	if (!dev->first)
#endif
	i = phy_drivers_register(ksz9477_phy_driver,
				 ARRAY_SIZE(ksz9477_phy_driver), THIS_MODULE);
	if (i < 0)
		return -ENODEV;

	dev->regs_size = KSZ9477_REGS_SIZE;
	i = sysfs_create_bin_file(&dev->dev->kobj,
				  &ksz9477_registers_attr);

	return 0;
}

static void ksz9477_switch_exit(struct ksz_device *dev)
{
	if (dev->sgmii_timer.expires) {
		del_timer_sync(&dev->sgmii_timer);
		flush_work(&dev->sgmii_check);
	}
	sysfs_remove_bin_file(&dev->dev->kobj, &ksz9477_registers_attr);
#ifdef SIMULATE_CASCADE_SWITCH
	if (!dev->first)
#endif
	phy_drivers_unregister(ksz9477_phy_driver,
			       ARRAY_SIZE(ksz9477_phy_driver));
	if (dev->irq > 0)
		devm_free_irq(dev->dev, dev->irq, dev);
	ksz9477_reset_switch(dev);
}

static const struct ksz_dev_ops ksz9477_dev_ops = {
	.cfg_port_member = ksz9477_cfg_port_member,
	.flush_dyn_mac_table = ksz9477_flush_dyn_mac_table,
	.phy_setup = ksz9477_phy_setup,
	.port_setup = ksz9477_port_setup,
	.r_mib_cnt = ksz9477_r_mib_cnt,
	.r_mib_pkt = ksz9477_r_mib_pkt,
	.freeze_mib = ksz9477_freeze_mib,
	.port_init_cnt = ksz9477_port_init_cnt,
	.shutdown = ksz9477_reset_switch,
	.detect = ksz9477_switch_detect,
	.init = ksz9477_switch_init,
	.exit = ksz9477_switch_exit,
};

/* For Ingress (Host -> KSZ), 2 bytes are added before FCS.
 * ---------------------------------------------------------------------------
 * DA(6bytes)|SA(6bytes)|....|Data(nbytes)|tag0(1byte)|tag1(1byte)|FCS(4bytes)
 * ---------------------------------------------------------------------------
 * tag0 : Prioritization (not used now)
 * tag1 : each bit represents port (eg, 0x01=port1, 0x02=port2, 0x10=port5)
 *
 * For switch with 3 ports only one byte is needed.
 * When PTP function is enabled additional 4 bytes are needed.
 *
 * For Egress (KSZ -> Host), 1 byte is added before FCS.
 * ---------------------------------------------------------------------------
 * DA(6bytes)|SA(6bytes)|....|Data(nbytes)|tag0(1byte)|FCS(4bytes)
 * ---------------------------------------------------------------------------
 * tag0 : zero-based value represents port
 *	  (eg, 0x00=port1, 0x02=port3, 0x06=port7)
 *
 * When PTP function is enabled BIT 7 indicates the received frame is a PTP
 * message and so there are 4 additional bytes for the receive timestamp.
 */

static int ksz9477_get_len(struct ksz_device *dev)
{
	int len = 1;

	if (!(dev->features & IS_9893))
		len += 1;
	if (dev->overrides & PTP_TAG)
		len += 4;
	return len;
}

static int ksz9477_get_tag(struct ksz_device *dev, u8 *tag, int *port)
{
	int len = 1;

	if (tag[0] & BIT(7))
		len += 4;
	*port = tag[0] & 7;
	return len;
}

static void ksz9477_set_tag(struct ksz_device *dev, void *ptr, u8 *addr, int p)
{
	if (dev->overrides & PTP_TAG) {
		u32 *timestamp = (u32 *)ptr;

		*timestamp = 0;
		ptr = timestamp + 1;
	}
	if (dev->features & IS_9893) {
		u8 *tag = (u8 *)ptr;

		*tag = 1 << p;
	} else {
		u16 *tag = (u16 *)ptr;

		*tag = 1 << p;
		*tag = cpu_to_be16(*tag);
	}
}

static const struct ksz_tag_ops ksz9477_tag_ops = {
	.get_len = ksz9477_get_len,
	.get_tag = ksz9477_get_tag,
	.set_tag = ksz9477_set_tag,
};

int ksz9477_switch_register(struct ksz_device *dev)
{
	return ksz_switch_register(dev, &ksz9477_dev_ops, &ksz9477_tag_ops);
}
EXPORT_SYMBOL(ksz9477_switch_register);

MODULE_AUTHOR("Woojung Huh <Woojung.Huh@microchip.com>");
MODULE_DESCRIPTION("Microchip KSZ9477 Series Switch DSA Driver");
MODULE_LICENSE("GPL v2");
