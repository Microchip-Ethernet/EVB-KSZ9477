/**
 * Microchip KSZ8795 switch common code
 *
 * Copyright (c) 2015-2018 Microchip Technology Inc.
 *	Tristram Ha <Tristram.Ha@microchip.com>
 *
 * Copyright (c) 2010-2015 Micrel, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */


#ifdef CONFIG_KSZ_DLR
/* Have ACL to handle beacon timeout. */
#define CONFIG_HAVE_ACL_HW
#endif

/* -------------------------------------------------------------------------- */

#define MAX_SYSFS_BUF_SIZE		(4080 - 80)

#if 1
#define USE_LOG_MASK
#endif

enum {
	PROC_SW_INFO,
	PROC_SW_VERSION,

	PROC_SET_SW_DUPLEX,
	PROC_SET_SW_SPEED,
	PROC_SET_SW_FORCE,
	PROC_SET_SW_FLOW_CTRL,

	PROC_SET_SW_FEATURES,
	PROC_SET_SW_OVERRIDES,
	PROC_SET_SW_MIB,

	PROC_SET_SW_REG,
	PROC_SET_SW_VID,

	PROC_DYNAMIC,
	PROC_STATIC,
	PROC_VLAN,

	PROC_SET_AGING,
	PROC_SET_FAST_AGING,
	PROC_SET_LINK_AGING,

	PROC_SET_BROADCAST_STORM,
	PROC_SET_MULTICAST_STORM,
	PROC_SET_TX_RATE_QUEUE_BASED,
	PROC_SET_DIFFSERV,
	PROC_SET_802_1P,

	PROC_ENABLE_VLAN,
	PROC_SET_REPLACE_NULL_VID,
	PROC_SET_MAC_ADDR,
	PROC_SET_MIRROR_MODE,
	PROC_SET_TAIL_TAG,

	PROC_SET_IGMP_SNOOP,
	PROC_SET_IPV6_MLD_SNOOP,
	PROC_SET_IPV6_MLD_OPTION,

	PROC_SET_AGGR_BACKOFF,
	PROC_SET_NO_EXC_DROP,

	PROC_SET_HUGE_PACKET,
	PROC_SET_LEGAL_PACKET,
	PROC_SET_LENGTH_CHECK,

	PROC_SET_BACK_PRESSURE_MODE,
	PROC_SET_SWITCH_FLOW_CTRL,
	PROC_SET_SWITCH_HALF_DUPLEX,
	PROC_SET_SWITCH_10_MBIT,

	PROC_SET_RX_FLOW_CTRL,
	PROC_SET_TX_FLOW_CTRL,
	PROC_SET_FAIR_FLOW_CTRL,
	PROC_SET_VLAN_BOUNDARY,

	PROC_SET_FORWARD_UNKNOWN_UNICAST,
	PROC_SET_FORWARD_UNKNOWN_UNICAST_PORTS,
	PROC_SET_FORWARD_UNKNOWN_MULTICAST,
	PROC_SET_FORWARD_UNKNOWN_MULTICAST_PORTS,
	PROC_SET_FORWARD_UNKNOWN_VID,
	PROC_SET_FORWARD_UNKNOWN_VID_PORTS,
	PROC_SET_FORWARD_UNKNOWN_IP_MULTICAST,
	PROC_SET_FORWARD_UNKNOWN_IP_MULTICAST_PORTS,
	PROC_SET_SELF_ADDR_FILTER,
	PROC_SET_INS_TAG,

	PROC_SET_PME,

	PROC_SET_PASS_PAUSE,
	PROC_SET_HI_PRIO_QUEUES,

	PROC_GET_PORTS,
	PROC_GET_DEV_START,
	PROC_GET_VLAN_START,
	PROC_GET_STP,

	PROC_SET_STATIC_FID,
	PROC_SET_STATIC_USE_FID,
	PROC_SET_STATIC_OVERRIDE,
	PROC_SET_STATIC_VALID,
	PROC_SET_STATIC_PORTS,
	PROC_SET_STATIC_MAC_ADDR,
	PROC_SET_STATIC_INDEX,
	PROC_GET_STATIC_INFO,

	PROC_SET_VLAN_VALID,
	PROC_SET_VLAN_MEMBER,
	PROC_SET_VLAN_FID,
	PROC_SET_VLAN_VID,
	PROC_GET_VLAN_INFO,

#ifdef CONFIG_KSZ_STP
	PROC_GET_STP_BR_INFO,
	PROC_SET_STP_BR_ON,
	PROC_SET_STP_BR_PRIO,
	PROC_SET_STP_BR_FWD_DELAY,
	PROC_SET_STP_BR_MAX_AGE,
	PROC_SET_STP_BR_HELLO_TIME,
	PROC_SET_STP_BR_TX_HOLD,
	PROC_SET_STP_VERSION,
#endif
};

enum {
	PROC_SET_PORT_MIB,

	PROC_SET_DEF_VID,
	PROC_SET_MEMBER,

	PROC_ENABLE_BROADCAST_STORM,
	PROC_ENABLE_DIFFSERV,
	PROC_ENABLE_802_1P,

	PROC_SET_PORT_BASED,

	PROC_SET_DIS_NON_VID,
	PROC_SET_INGRESS,
	PROC_SET_INSERT_TAG,
	PROC_SET_REMOVE_TAG,
	PROC_SET_DROP_TAG,
	PROC_SET_REPLACE_PRIO,

	PROC_SET_RX,
	PROC_SET_TX,
	PROC_SET_LEARN,

	PROC_SET_INS_TAG_0,
	PROC_SET_INS_TAG_1,
	PROC_SET_INS_TAG_2,
	PROC_SET_INS_TAG_3,
	PROC_SET_INS_TAG_4,

	PROC_SET_PASS_ALL,

	PROC_ENABLE_PRIO_QUEUE,
	PROC_SET_TX_Q0_CTRL,
	PROC_SET_TX_Q1_CTRL,
	PROC_SET_TX_Q2_CTRL,
	PROC_SET_TX_Q3_CTRL,
	PROC_SET_TX_Q0_RATIO,
	PROC_SET_TX_Q1_RATIO,
	PROC_SET_TX_Q2_RATIO,
	PROC_SET_TX_Q3_RATIO,

	PROC_ENABLE_RX_PRIO_RATE,
	PROC_ENABLE_TX_PRIO_RATE,
	PROC_SET_RX_LIMIT,
	PROC_SET_RX_LIMIT_PORT_BASED,
	PROC_SET_LIMIT_PACKET_BASED,
	PROC_SET_RX_LIMIT_FLOW_CTRL,
	PROC_SET_CNT_IFG,
	PROC_SET_CNT_PRE,
	PROC_SET_RX_P0_RATE,
	PROC_SET_RX_P1_RATE,
	PROC_SET_RX_P2_RATE,
	PROC_SET_RX_P3_RATE,
	PROC_SET_TX_Q0_RATE,
	PROC_SET_TX_Q1_RATE,
	PROC_SET_TX_Q2_RATE,
	PROC_SET_TX_Q3_RATE,

	PROC_SET_MIRROR_PORT,
	PROC_SET_MIRROR_RX,
	PROC_SET_MIRROR_TX,

	PROC_SET_BACK_PRESSURE,
	PROC_SET_FORCE_FLOW_CTRL,

	PROC_SET_UNKNOWN_UNICAST_PORT,
	PROC_SET_UNKNOWN_MULTICAST_PORT,
	PROC_SET_UNKNOWN_VID_PORT,
	PROC_SET_UNKNOWN_IP_MULTICAST_PORT,

	PROC_SET_PORT_PME_CTRL,
	PROC_SET_PORT_PME_STATUS,

	PROC_SET_AUTHEN_MODE,
	PROC_SET_ACL,
	PROC_SET_ACL_FIRST_RULE,
	PROC_SET_ACL_RULESET,
	PROC_SET_ACL_MODE,
	PROC_SET_ACL_ENABLE,
	PROC_SET_ACL_SRC,
	PROC_SET_ACL_EQUAL,
	PROC_SET_ACL_MAC_ADDR,
	PROC_SET_ACL_TYPE,
	PROC_SET_ACL_CNT,
	PROC_SET_ACL_MSEC,
	PROC_SET_ACL_INTR_MODE,
	PROC_SET_ACL_IP_ADDR,
	PROC_SET_ACL_IP_MASK,
	PROC_SET_ACL_PROTOCOL,
	PROC_SET_ACL_SEQNUM,
	PROC_SET_ACL_PORT_MODE,
	PROC_SET_ACL_MAX_PORT,
	PROC_SET_ACL_MIN_PORT,
	PROC_SET_ACL_TCP_FLAG_ENABLE,
	PROC_SET_ACL_TCP_FLAG,
	PROC_SET_ACL_TCP_FLAG_MASK,
	PROC_SET_ACL_PRIO_MODE,
	PROC_SET_ACL_PRIO,
	PROC_SET_ACL_VLAN_PRIO_REPLACE,
	PROC_SET_ACL_VLAN_PRIO,
	PROC_SET_ACL_MAP_MODE,
	PROC_SET_ACL_PORTS,
	PROC_SET_ACL_INDEX,
	PROC_SET_ACL_ACTION_INDEX,
	PROC_SET_ACL_ACTION,
	PROC_SET_ACL_RULE_INDEX,
	PROC_SET_ACL_INFO,
	PROC_GET_ACL_TABLE,

	PROC_SET_PORT_DUPLEX,
	PROC_SET_PORT_SPEED,
	PROC_SET_LINK_MD,

#ifdef CONFIG_KSZ_STP
	PROC_GET_STP_INFO,
	PROC_SET_STP_ON,
	PROC_SET_STP_PRIO,
	PROC_SET_STP_ADMIN_PATH_COST,
	PROC_SET_STP_PATH_COST,
	PROC_SET_STP_ADMIN_EDGE,
	PROC_SET_STP_AUTO_EDGE,
	PROC_SET_STP_MCHECK,
	PROC_SET_STP_ADMIN_P2P,
#endif

};

/* -------------------------------------------------------------------------- */

static uint get_phy_port(struct ksz_sw *sw, uint n)
{
if (n > sw->mib_port_cnt + 1)
dbg_msg("  !!! %s %d\n", __func__, n);
	if (n >= sw->mib_port_cnt + 1)
		n = 0;
	return sw->port_info[n].phy_p;
}

static uint get_log_port(struct ksz_sw *sw, uint p)
{
if (p >= sw->port_cnt)
dbg_msg("  !!! %s %d\n", __func__, p);
if (!sw->port_info[p].log_m)
dbg_msg("  ??? %s %d\n", __func__, p);
	return sw->port_info[p].log_p;
}

static uint get_log_port_zero(struct ksz_sw *sw, uint p)
{
	uint n;

	n = get_log_port(sw, p);
	if (n)
		n--;
	else
		n = sw->mib_port_cnt;
	return n;
}

#if 0
static u8 get_phy_mask(struct ksz_sw *sw, uint n)
{
if (n > sw->mib_port_cnt + 1)
dbg_msg("  !!! %s %d\n", __func__, n);
	if (n >= sw->mib_port_cnt + 1)
		n = 0;
	return sw->port_info[n].phy_m;
}
#endif

static uint get_phy_mask_from_log(struct ksz_sw *sw, uint log_m)
{
	struct ksz_port_info *info;
	uint n;
	uint p;
	uint phy_m = 0;

	for (n = 0; n <= sw->mib_port_cnt; n++) {
		info = &sw->port_info[n];
		p = info->phy_p;
		if (log_m & sw->port_info[p].log_m)
			phy_m |= info->phy_m;
	}
	return phy_m;
}

static uint get_log_mask_from_phy(struct ksz_sw *sw, uint phy_m)
{
	struct ksz_port_info *info;
	uint n;
	uint p;
	uint log_m = 0;

	for (n = 0; n <= sw->mib_port_cnt; n++) {
		info = &sw->port_info[n];
		p = info->phy_p;
		if (phy_m & info->phy_m)
			log_m |= sw->port_info[p].log_m;
	}
	return log_m;
}

static uint get_sysfs_port(struct ksz_sw *sw, uint n)
{
	uint p = n;

	if (!(sw->overrides & SYSFS_PHY_PORT)) {
		n++;
		if (n > sw->mib_port_cnt)
			n = 0;
		p = get_phy_port(sw, n);
	}
	return p;
}

static inline struct ksz_port_cfg *get_port_cfg(struct ksz_sw *sw, uint p)
{
	return &sw->info->port_cfg[p];
}

static inline struct ksz_port_info *get_port_info(struct ksz_sw *sw, uint p)
{
	return &sw->port_info[p];
}

static inline struct ksz_port_mib *get_port_mib(struct ksz_sw *sw, uint p)
{
	return &sw->port_mib[p];
}

static void sw_acquire(struct ksz_sw *sw)
{
	mutex_lock(&sw->lock);
	sw->reg->lock(sw);
	mutex_unlock(&sw->lock);
}  /* sw_acquire */

static void sw_release(struct ksz_sw *sw)
{
	sw->reg->unlock(sw);
}  /* sw_release */

/* -------------------------------------------------------------------------- */

/*
#define STATIC_MAC_TABLE_ADDR		00-0000FFFF-FFFFFFFF
#define STATIC_MAC_TABLE_FWD_PORTS	00-001F0000-00000000
#define STATIC_MAC_TABLE_VALID		00-00200000-00000000
#define STATIC_MAC_TABLE_OVERRIDE	00-00400000-00000000
#define STATIC_MAC_TABLE_USE_FID	00-00800000-00000000
#define STATIC_MAC_TABLE_FID		00-7F000000-00000000
*/

#define STATIC_MAC_TABLE_ADDR		0x0000FFFF
#define STATIC_MAC_TABLE_FWD_PORTS	0x001F0000
#define STATIC_MAC_TABLE_VALID		0x00200000
#define STATIC_MAC_TABLE_OVERRIDE	0x00400000
#define STATIC_MAC_TABLE_USE_FID	0x00800000
#define STATIC_MAC_TABLE_FID		0x7F000000

#define STATIC_MAC_FWD_PORTS_S		16
#define STATIC_MAC_FID_S		24

/*
#define VLAN_TABLE_FID			00-007F007F-007F007F
#define VLAN_TABLE_MEMBERSHIP		00-0F800F80-0F800F80
#define VLAN_TABLE_VALID		00-10001000-10001000
*/

#define VLAN_TABLE_FID			0x007F
#define VLAN_TABLE_MEMBERSHIP		0x0F80
#define VLAN_TABLE_VALID		0x1000

#define VLAN_TABLE_MEMBERSHIP_S		7
#define VLAN_TABLE_S			16

/*
#define DYNAMIC_MAC_TABLE_ADDR		00-0000FFFF-FFFFFFFF
#define DYNAMIC_MAC_TABLE_FID		00-007F0000-00000000
#define DYNAMIC_MAC_TABLE_NOT_READY	00-00800000-00000000
#define DYNAMIC_MAC_TABLE_SRC_PORT	00-07000000-00000000
#define DYNAMIC_MAC_TABLE_TIMESTAMP	00-18000000-00000000
#define DYNAMIC_MAC_TABLE_ENTRIES	7F-E0000000-00000000
#define DYNAMIC_MAC_TABLE_MAC_EMPTY	80-00000000-00000000
*/

#define DYNAMIC_MAC_TABLE_ADDR		0x0000FFFF
#define DYNAMIC_MAC_TABLE_FID		0x007F0000
#define DYNAMIC_MAC_TABLE_SRC_PORT	0x07000000
#define DYNAMIC_MAC_TABLE_TIMESTAMP	0x18000000
#define DYNAMIC_MAC_TABLE_ENTRIES	0xE0000000

#define DYNAMIC_MAC_TABLE_NOT_READY	0x80

#define DYNAMIC_MAC_TABLE_ENTRIES_H	0x7F
#define DYNAMIC_MAC_TABLE_MAC_EMPTY	0x80

#define DYNAMIC_MAC_FID_S		16
#define DYNAMIC_MAC_SRC_PORT_S		24
#define DYNAMIC_MAC_TIMESTAMP_S		27
#define DYNAMIC_MAC_ENTRIES_S		29
#define DYNAMIC_MAC_ENTRIES_H_S		3

/*
#define MIB_COUNTER_VALUE		00-00000000-3FFFFFFF
#define MIB_TOTAL_BYTES			00-0000000F-FFFFFFFF
#define MIB_PACKET_DROPPED		00-00000000-0000FFFF
#define MIB_COUNTER_VALID		00-00000020-00000000
#define MIB_COUNTER_OVERFLOW		00-00000040-00000000
*/

#ifndef MIB_COUNTER_OVERFLOW
#define MIB_COUNTER_OVERFLOW		(1 << 6)
#define MIB_COUNTER_VALID		(1 << 5)

#define MIB_COUNTER_VALUE		0x3FFFFFFF
#endif

#define KS_MIB_TOTAL_RX_0		0x100
#define KS_MIB_TOTAL_TX_0		0x101
#define KS_MIB_PACKET_DROPPED_RX_0	0x102
#define KS_MIB_PACKET_DROPPED_TX_0	0x103
#define KS_MIB_TOTAL_RX_1		0x104
#define KS_MIB_TOTAL_TX_1		0x105
#define KS_MIB_PACKET_DROPPED_TX_1	0x106
#define KS_MIB_PACKET_DROPPED_RX_1	0x107
#define KS_MIB_TOTAL_RX_2		0x108
#define KS_MIB_TOTAL_TX_2		0x109
#define KS_MIB_PACKET_DROPPED_TX_2	0x10A
#define KS_MIB_PACKET_DROPPED_RX_2	0x10B
#define KS_MIB_TOTAL_RX_3		0x10C
#define KS_MIB_TOTAL_TX_3		0x10D
#define KS_MIB_PACKET_DROPPED_TX_3	0x10E
#define KS_MIB_PACKET_DROPPED_RX_3	0x10F
#define KS_MIB_TOTAL_RX_4		0x110
#define KS_MIB_TOTAL_TX_4		0x111
#define KS_MIB_PACKET_DROPPED_TX_4	0x112
#define KS_MIB_PACKET_DROPPED_RX_4	0x113

#define MIB_PACKET_DROPPED		0x0000FFFF

#define MIB_TOTAL_BYTES_H		0x0000000F

/* -------------------------------------------------------------------------- */

/* Switch functions */

/**
 * sw_r_table_64 - read 64 bits of data from switch table
 * @sw:		The switch instance.
 * @table:	The table selector.
 * @addr:	The address of the table entry.
 * @data_hi:	Buffer to store the high part of read data (bit63 ~ bit32).
 * @data_lo:	Buffer to store the low part of read data (bit31 ~ bit0).
 *
 * This routine reads 64 bits of data from the table of the switch.
 * Hardware is locked to minimize corruption of read data.
 */
static void sw_r_table_64(struct ksz_sw *sw, int table, u16 addr, u32 *data_hi,
	u32 *data_lo)
{
	u64 buf;
	u16 ctrl_addr;

	ctrl_addr = IND_ACC_TABLE(table | TABLE_READ) | addr;

	sw->ops->acquire(sw);
	sw->reg->w16(sw, REG_IND_CTRL_0, ctrl_addr);
	sw->reg->r(sw, REG_IND_DATA_HI, &buf, sizeof(buf));
	sw->ops->release(sw);
	buf = be64_to_cpu(buf);
	*data_hi = (u32)(buf >> 32);
	*data_lo = (u32) buf;
}  /* sw_r_table_64 */

/**
 * sw_w_table_64 - write 64 bits of data to switch table
 * @sw:		The switch instance.
 * @table:	The table selector.
 * @addr:	The address of the table entry.
 * @data_hi:	The high part of data to be written (bit63 ~ bit32).
 * @data_lo:	The low part of data to be written (bit31 ~ bit0).
 *
 * This routine writes 64 bits of data to the table of the switch.
 * Hardware is locked to minimize corruption of written data.
 */
static void sw_w_table_64(struct ksz_sw *sw, int table, u16 addr, u32 data_hi,
	u32 data_lo)
{
	u64 buf;
	u16 ctrl_addr;

	ctrl_addr = IND_ACC_TABLE(table) | addr;
	buf = data_hi;
	buf <<= 32;
	buf |= data_lo;
	buf = cpu_to_be64(buf);

	sw->ops->acquire(sw);
	sw->reg->w(sw, REG_IND_DATA_HI, &buf, sizeof(buf));
	sw->reg->w16(sw, REG_IND_CTRL_0, ctrl_addr);
	sw->ops->release(sw);
}  /* sw_w_table_64 */

/**
 * sw_r_ext_table - read a byte of data from switch table
 * @sw:		The switch instance.
 * @table:	The table selector.
 * @addr:	The address of the table entry.
 * @offset:	The offset of the extended table.
 * @data:	Buffer to store the read data.
 *
 * This routine reads a byte of data from the extended table of the switch.
 * Hardware is locked to minimize corruption of read data.
 */
static void sw_r_ext_table(struct ksz_sw *sw, int table, u16 addr, u16 offset,
	u8 *data)
{
	u16 ctrl_addr;

	ctrl_addr = IND_ACC_TABLE(table | TABLE_READ | addr) | offset;

	sw->reg->w16(sw, REG_IND_CTRL_0, ctrl_addr);
	*data = sw->reg->r8(sw, REG_IND_DATA_PME_EEE_ACL);
}  /* sw_r_ext_table */

/**
 * sw_g_ext_table - read bytes of data from switch table
 * @sw:		The switch instance.
 * @table:	The table selector.
 * @addr:	The address of the table entry.
 * @offset:	The offset of the extended table.
 * @data:	Buffer to store the read data.
 * @cnt:	Numbe of bytes to read.
 *
 * This routine reads several bytes of data from the extended table of the
 * switch.
 * Hardware is locked to minimize corruption of read data.
 */
static void sw_g_ext_table(struct ksz_sw *sw, int table, u16 addr, u16 offset,
	u8 *data, int cnt)
{
	u16 ctrl_addr;
	int i;

	ctrl_addr = IND_ACC_TABLE(table | TABLE_READ | addr) | offset;

	sw->reg->w16(sw, REG_IND_CTRL_0, ctrl_addr);
	for (i = 0; i < cnt; i++)
		data[i] = sw->reg->r8(sw, REG_IND_DATA_PME_EEE_ACL);
}  /* sw_g_ext_table */

/**
 * sw_w_ext_table - write a byte of data to switch table
 * @sw:		The switch instance.
 * @table:	The table selector.
 * @addr:	The address of the table entry.
 * @offset:	The offset of the extended table.
 * @data:	Data to be written.
 *
 * This routine writes a byte of data to the extended table of the switch.
 * Hardware is locked to minimize corruption of written data.
 */
static void sw_w_ext_table(struct ksz_sw *sw, int table, u16 addr, u16 offset,
	u8 data)
{
	u16 ctrl_addr;

	ctrl_addr = IND_ACC_TABLE(table | addr) | offset;

	sw->reg->w16(sw, REG_IND_CTRL_0, ctrl_addr);
	sw->reg->w8(sw, REG_IND_DATA_PME_EEE_ACL, data);
}  /* sw_w_ext_table */

/**
 * sw_p_ext_table - write bytes of data to switch table
 * @sw:		The switch instance.
 * @table:	The table selector.
 * @addr:	The address of the table entry.
 * @offset:	The offset of the extended table.
 * @data:	Data to be written.
 * @cnt:	Numbe of bytes to write.
 *
 * This routine writes several bytes of data to the extended table of the
 * switch.
 * Hardware is locked to minimize corruption of written data.
 */
static void sw_p_ext_table(struct ksz_sw *sw, int table, u16 addr, u16 offset,
	u8 *data, int cnt)
{
	u16 ctrl_addr;
	int i;

	ctrl_addr = IND_ACC_TABLE(table | addr) | offset;

	sw->reg->w16(sw, REG_IND_CTRL_0, ctrl_addr);
	for (i = 0; i < cnt; i++)
		sw->reg->w8(sw, REG_IND_DATA_PME_EEE_ACL, data[i]);
}  /* sw_p_ext_table */

static inline int valid_dyn_entry(struct ksz_sw *sw, u8 *data)
{
	int timeout = 100;

	do {
		*data = sw->reg->r8(sw, REG_IND_DATA_CHECK);
		timeout--;
	} while ((*data & DYNAMIC_MAC_TABLE_NOT_READY) && timeout);

	/* Entry is not ready for accessing. */
	if (*data & DYNAMIC_MAC_TABLE_NOT_READY)
		return 1;

	/* Entry is ready for accessing. */
	else {
		*data = sw->reg->r8(sw, REG_IND_DATA_8);

		/* There is no valid entry in the table. */
		if (*data & DYNAMIC_MAC_TABLE_MAC_EMPTY)
			return 2;
	}
	return 0;
}  /* valid_dyn_entry */

/**
 * sw_r_dyn_mac_table - read from dynamic MAC table
 * @sw:		The switch instance.
 * @addr:	The address of the table entry.
 * @mac_addr:	Buffer to store the MAC address.
 * @fid:	Buffer to store the FID.
 * @src_port:	Buffer to store the source port number.
 * @timestamp:	Buffer to store the timestamp.
 * @entries:	Buffer to store the number of entries.  If this is zero, the
 *		table is empty and so this function should not be called again
 *		until later.
 *
 * This function reads an entry of the dynamic MAC table of the switch.
 * Hardware is locked to minimize corruption of read data.
 *
 * Return 0 if the entry is successfully read; otherwise -1.
 */
static int sw_r_dyn_mac_table(struct ksz_sw *sw, u16 addr, u8 *mac_addr,
	u8 *fid, u8 *src_port, u8 *timestamp, u16 *entries)
{
	u32 data_hi;
	u32 data_lo;
	u16 ctrl_addr;
	int rc;
	u8 data;

	ctrl_addr = IND_ACC_TABLE(TABLE_DYNAMIC_MAC | TABLE_READ) | addr;

	sw->ops->acquire(sw);
	sw->reg->w16(sw, REG_IND_CTRL_0, ctrl_addr);

	rc = valid_dyn_entry(sw, &data);
	if (1 == rc) {
		if (0 == addr)
			*entries = 0;
	} else if (2 == rc)
		*entries = 0;
	/* At least one valid entry in the table. */
	else {
		u64 buf;

		sw->reg->r(sw, REG_IND_DATA_HI, &buf, sizeof(buf));
		buf = be64_to_cpu(buf);
		data_hi = (u32)(buf >> 32);
		data_lo = (u32) buf;

		/* Check out how many valid entry in the table. */
		*entries = (u16)(((((u16)
			data & DYNAMIC_MAC_TABLE_ENTRIES_H) <<
			DYNAMIC_MAC_ENTRIES_H_S) |
			(((data_hi & DYNAMIC_MAC_TABLE_ENTRIES) >>
			DYNAMIC_MAC_ENTRIES_S))) + 1);

		*fid = (u8)((data_hi & DYNAMIC_MAC_TABLE_FID) >>
			DYNAMIC_MAC_FID_S);
		*src_port = (u8)((data_hi & DYNAMIC_MAC_TABLE_SRC_PORT) >>
			DYNAMIC_MAC_SRC_PORT_S);
		*timestamp = (u8)((
			data_hi & DYNAMIC_MAC_TABLE_TIMESTAMP) >>
			DYNAMIC_MAC_TIMESTAMP_S);

		mac_addr[5] = (u8) data_lo;
		mac_addr[4] = (u8)(data_lo >> 8);
		mac_addr[3] = (u8)(data_lo >> 16);
		mac_addr[2] = (u8)(data_lo >> 24);

		mac_addr[1] = (u8) data_hi;
		mac_addr[0] = (u8)(data_hi >> 8);
		rc = 0;
	}
	sw->ops->release(sw);

	return rc;
}  /* sw_r_dyn_mac_table */

/**
 * sw_d_dyn_mac_table - dump dynamic MAC table
 * @sw:		The switch instance.
 *
 * This routine dumps dynamic MAC table contents.
 */
static ssize_t sw_d_dyn_mac_table(struct ksz_sw *sw, char *buf, ssize_t len)
{
	u16 entries = 0;
	u16 i;
	u8 mac_addr[ETH_ALEN];
	u8 port = 0;
	u8 timestamp = 0;
	u8 fid = 0;
	int first_break = true;

	memset(mac_addr, 0, ETH_ALEN);
	i = 0;
	do {
		if (!sw_r_dyn_mac_table(sw, i, mac_addr, &fid, &port,
				&timestamp, &entries)) {
#ifdef USE_LOG_MASK
			port = get_log_port_zero(sw, port);
#endif
			if (len >= MAX_SYSFS_BUF_SIZE && first_break) {
				first_break = false;
				len += sprintf(buf + len, "...\n");
			}
			if (len < MAX_SYSFS_BUF_SIZE)
			len += sprintf(buf + len,
				"%02X:%02X:%02X:%02X:%02X:%02X  "
				"f:%02x  p:%x  t:%x\n",
				mac_addr[0], mac_addr[1], mac_addr[2],
				mac_addr[3], mac_addr[4], mac_addr[5],
				fid, port, timestamp);
			else
			printk(KERN_INFO
				"%02X:%02X:%02X:%02X:%02X:%02X  "
				"f:%02x  p:%x  t:%x\n",
				mac_addr[0], mac_addr[1], mac_addr[2],
				mac_addr[3], mac_addr[4], mac_addr[5],
				fid, port, timestamp);
		}
		i++;
	} while (i < entries);
	if (entries) {
		if (len < MAX_SYSFS_BUF_SIZE)
			sprintf(buf + len, "=%03x\n", entries);
		else
			printk(KERN_INFO "=%03x\n", entries);
	}
	return len;
}  /* sw_d_dyn_mac_table */

/**
 * sw_r_sta_mac_table - read from static MAC table
 * @sw:		The switch instance.
 * @addr:	The address of the table entry.
 * @mac:	Buffer to store the MAC table entry.
 *
 * This function reads an entry of the static MAC table of the switch.  It
 * calls sw_r_table_64() to get the data.
 *
 * Return 0 if the entry is valid; otherwise -1.
 */
static int sw_r_sta_mac_table(struct ksz_sw *sw, u16 addr,
	struct ksz_mac_table *mac)
{
	u32 data_hi;
	u32 data_lo;

	sw_r_table_64(sw, TABLE_STATIC_MAC, addr, &data_hi, &data_lo);
	if (data_hi & (STATIC_MAC_TABLE_VALID | STATIC_MAC_TABLE_OVERRIDE)) {
		mac->addr[5] = (u8) data_lo;
		mac->addr[4] = (u8)(data_lo >> 8);
		mac->addr[3] = (u8)(data_lo >> 16);
		mac->addr[2] = (u8)(data_lo >> 24);
		mac->addr[1] = (u8) data_hi;
		mac->addr[0] = (u8)(data_hi >> 8);
		mac->ports = (u8)((data_hi & STATIC_MAC_TABLE_FWD_PORTS) >>
			STATIC_MAC_FWD_PORTS_S);
		mac->override = (data_hi & STATIC_MAC_TABLE_OVERRIDE) ? 1 : 0;
		data_hi >>= 1;
		mac->use_fid = (data_hi & STATIC_MAC_TABLE_USE_FID) ? 1 : 0;
		mac->fid = (u8)((data_hi & STATIC_MAC_TABLE_FID) >>
			STATIC_MAC_FID_S);
		mac->dirty = 0;
		return 0;
	}
	return -1;
}  /* sw_r_sta_mac_table */

/**
 * sw_w_sta_mac_table - write to static MAC table
 * @sw:		The switch instance.
 * @addr:	The address of the table entry.
 * @mac:	The MAC table entry.
 *
 * This routine writes an entry of the static MAC table of the switch.  It
 * calls sw_w_table_64() to write the data.
 */
static void sw_w_sta_mac_table(struct ksz_sw *sw, u16 addr,
	struct ksz_mac_table *mac)
{
	u32 data_hi;
	u32 data_lo;

	data_lo = ((u32) mac->addr[2] << 24) |
		((u32) mac->addr[3] << 16) |
		((u32) mac->addr[4] << 8) | mac->addr[5];
	data_hi = ((u32) mac->addr[0] << 8) | mac->addr[1];
	data_hi |= (u32) mac->ports << STATIC_MAC_FWD_PORTS_S;

	if (mac->override)
		data_hi |= STATIC_MAC_TABLE_OVERRIDE;
	if (mac->use_fid) {
		data_hi |= STATIC_MAC_TABLE_USE_FID;
		data_hi |= (u32) mac->fid << STATIC_MAC_FID_S;
	}
	if (mac->valid)
		data_hi |= STATIC_MAC_TABLE_VALID;
	else
		data_hi &= ~STATIC_MAC_TABLE_OVERRIDE;

	sw_w_table_64(sw, TABLE_STATIC_MAC, addr, data_hi, data_lo);
	mac->dirty = 0;
}  /* sw_w_sta_mac_table */

/**
 * sw_d_sta_mac_table - dump static MAC table
 * @sw:		The switch instance.
 *
 * This routine dumps static MAC table contents.
 */
static ssize_t sw_d_sta_mac_table(struct ksz_sw *sw, char *buf, ssize_t len)
{
	u8 ports;
	u16 i;
	struct ksz_mac_table mac;

	i = 0;
	do {
		if (!sw_r_sta_mac_table(sw, i, &mac)) {
			ports = mac.ports;
#ifdef USE_LOG_MASK
			ports = get_log_mask_from_phy(sw, ports);
#endif
			len += sprintf(buf + len,
				"%2x: %02X:%02X:%02X:%02X:%02X:%02X  "
				"%02x  %u  %u:%02x\n",
				i, mac.addr[0], mac.addr[1], mac.addr[2],
				mac.addr[3], mac.addr[4], mac.addr[5],
				ports, mac.override, mac.use_fid, mac.fid);
		}
		i++;
	} while (i < STATIC_MAC_TABLE_ENTRIES);
	return len;
}  /* sw_d_sta_mac_table */

static ssize_t sw_d_mac_table(struct ksz_sw *sw, char *buf, ssize_t len)
{
#if 0
	struct ksz_mac_table *entry;
	int i;
	u8 ports;

	i = STATIC_MAC_TABLE_ENTRIES;
	do {
		entry = &sw->info->mac_table[i];
		if (entry->valid) {
			ports = entry->ports;
#ifdef USE_LOG_MASK
			ports = get_log_mask_from_phy(sw, ports);
#endif
			len += sprintf(buf + len,
				"%x: %02X:%02X:%02X:%02X:%02X:%02X  "
				"%x  %u  %u:%x\n",
				i, entry->mac_addr[0], entry->mac_addr[1],
				entry->mac_addr[2], entry->mac_addr[3],
				entry->mac_addr[4], entry->mac_addr[5],
				ports, entry->override, entry->use_fid,
				entry->fid);
		}
		i++;
		if (SWITCH_MAC_TABLE_ENTRIES == i)
			printk(KERN_INFO "\n");
	} while (i < MULTI_MAC_TABLE_ENTRIES);
#endif
	return len;
}  /* sw_d_mac_table */

/* -------------------------------------------------------------------------- */

/**
 * sw_r_vlan_entries - read many from VLAN table
 * @sw:		The switch instance.
 * @addr:	The address of the table entry.
 * @valid:	Buffer to store the valid bit.
 * @fid:	Buffer to store the VID.
 * @member:	Buffer to store the port membership.
 *
 * This function reads several entries of the VLAN table of the switch.  It
 * calls sw_r_table_64() to get the data.
 *
 * Return 0 if the entry is valid; otherwise -1.
 */
static int sw_r_vlan_entries(struct ksz_sw *sw, u16 addr, u8 *valid, u8 *fid,
	u8 *member)
{
	u64 buf;
	u32 *data_lo = (u32 *) &buf;
	u32 *data_hi = data_lo + 1;
	u16 data;
	int i;
	int ret = -1;

	sw_r_table_64(sw, TABLE_VLAN, addr, data_hi, data_lo);
	for (i = 0; i < 4; i++) {
		data = (u16) buf;
		*valid = 0;
		if (data & VLAN_TABLE_VALID) {
			*valid = 1;
			*fid = (u8)(data & VLAN_TABLE_FID);
			*member = (u8)((data & VLAN_TABLE_MEMBERSHIP) >>
				VLAN_TABLE_MEMBERSHIP_S);
			ret = 0;
		}
		++valid;
		++fid;
		++member;
		buf >>= VLAN_TABLE_S;
	}
	return ret;
}  /* sw_r_vlan_entries */

/**
 * sw_r_vlan_table - read from VLAN table
 * @sw:		The switch instance.
 * @vid:	The address of the table entry.
 * @vlan:	Buffer to store the VLAN table entry.
 *
 * This routine reads an entry of the VLAN table of the switch.  It calls
 * sw_r_table_64() to get the data.
 */
static void sw_r_vlan_table(struct ksz_sw *sw, u16 vid,
	struct ksz_vlan_table *vlan)
{
	u64 buf;
	u32 *data_lo = (u32 *) &buf;
	u32 *data_hi = data_lo + 1;
	u16 *data = (u16 *) &buf;
	u16 addr;
	int index;

	addr = vid / 4;
	index = vid & 3;
	sw_r_table_64(sw, TABLE_VLAN, addr, data_hi, data_lo);
	vlan->fid = (u8)(data[index] & VLAN_TABLE_FID);
	vlan->member = (u8)((data[index] & VLAN_TABLE_MEMBERSHIP) >>
		VLAN_TABLE_MEMBERSHIP_S);
	vlan->valid = !!(data[index] & VLAN_TABLE_VALID);
	vlan->dirty = 0;
}  /* sw_r_vlan_table */

/**
 * sw_w_vlan_table - write to VLAN table
 * @sw:		The switch instance.
 * @vid:	The address of the table entry.
 * @vlan:	The VLAN table entry.
 *
 * This routine writes an entry of the VLAN table of the switch.  It calls
 * sw_w_table_64() to write the data.
 */
static void sw_w_vlan_table(struct ksz_sw *sw, u16 vid,
	struct ksz_vlan_table *vlan)
{
	u64 buf;
	u32 *data_lo = (u32 *) &buf;
	u32 *data_hi = data_lo + 1;
	u16 *data = (u16 *) &buf;
	u16 addr;
	int index;

	addr = vid / 4;
	index = vid & 3;
	sw_r_table_64(sw, TABLE_VLAN, addr, data_hi, data_lo);
	data[index] = vlan->fid;
	data[index] |= (u16) vlan->member << VLAN_TABLE_MEMBERSHIP_S;
	if (vlan->valid)
		data[index] |= VLAN_TABLE_VALID;
	sw_w_table_64(sw, TABLE_VLAN, addr, *data_hi, *data_lo);
	vlan->dirty = 0;
}  /* sw_w_vlan_table */

/**
 * sw_d_vlan_table - dump VLAN table
 * @sw:		The switch instance.
 *
 * This routine dumps the VLAN table.
 */
static ssize_t sw_d_vlan_table(struct ksz_sw *sw, char *buf, ssize_t len)
{
	u16 i;
	u16 j;
	u16 vid;
	u8 ports;
	u8 fid[4];
	u8 member[4];
	u8 valid[4];
	int first_break = true;

	i = 0;
	do {
		if (!sw_r_vlan_entries(sw, i, valid, fid, member)) {
			vid = i * 4;
			for (j = 0; j < 4; j++, vid++) {
				if (!valid[j])
					continue;
				ports = member[j];
#ifdef USE_LOG_MASK
				ports = get_log_mask_from_phy(sw, member[j]);
#endif
				if (len >= MAX_SYSFS_BUF_SIZE && first_break) {
					first_break = false;
					len += sprintf(buf + len, "...\n");
				}
				if (len < MAX_SYSFS_BUF_SIZE)
					len += sprintf(buf + len,
						"0x%03x: %2x  %2x\n", vid,
						fid[j], ports);
				else
					printk(KERN_INFO
						"0x%03x: %2x  %2x\n", vid,
						fid[j], ports);
			}
		}
		if (len >= MAX_SYSFS_BUF_SIZE)
		yield();
		i++;
	} while (i < VLAN_TABLE_ENTRIES);
	return len;
}  /* sw_d_vlan_table */

/* -------------------------------------------------------------------------- */

/*
 * Some counters do not need to be read too often because they are less likely
 * to increase much.
 */
static u8 mib_read_max[TOTAL_SWITCH_COUNTER_NUM] = {
	1,
	4,
	4,
	4,
	4,
	4,
	4,
	4,
	4,
	1,
	1,
	1,
	1,
	2,
	2,
	2,
	2,
	2,
	2,
	2,
	2,

	1,
	4,
	1,
	1,
	1,
	1,
	4,
	4,
	4,
	4,
	4,

	1,
	1,
	2,
	2,
};

/**
 * port_r_mib_cnt - read MIB counter
 * @sw:		The switch instance.
 * @port:	The port index.
 * @addr:	The address of the counter.
 * @cnt:	Buffer to store the counter.
 *
 * This routine reads a MIB counter of the port.
 * Hardware is locked to minimize corruption of read data.
 */
static void port_r_mib_cnt(struct ksz_sw *sw, uint port, u16 addr, u64 *cnt)
{
	u32 data;
	u16 ctrl_addr;
	u8 check;
	int timeout;

	ctrl_addr = addr + SWITCH_COUNTER_NUM * port;

	sw->ops->acquire(sw);

	ctrl_addr |= IND_ACC_TABLE(TABLE_MIB | TABLE_READ);
	sw->reg->w16(sw, REG_IND_CTRL_0, ctrl_addr);

	for (timeout = 2; timeout > 0; timeout--) {
		check = sw->reg->r8(sw, REG_IND_MIB_CHECK);

		if (check & MIB_COUNTER_VALID) {
			data = sw->reg->r32(sw, REG_IND_DATA_LO);
			if (check & MIB_COUNTER_OVERFLOW)
				*cnt += MIB_COUNTER_VALUE + 1;
			*cnt += data & MIB_COUNTER_VALUE;
			break;
		}
	}

	sw->ops->release(sw);
}  /* port_r_mib_cnt */

/**
 * port_r_mib_pkt - read dropped packet counts
 * @sw:		The switch instance.
 * @port:	The port index.
 * @cnt:	Buffer to store the receive and transmit dropped packet counts.
 *
 * This routine reads the dropped packet counts of the port.
 * Hardware is locked to minimize corruption of read data.
 */
static void port_r_mib_pkt(struct ksz_sw *sw, uint port, u16 addr, u64 *cnt)
{
	u32 data;
	u16 ctrl_addr;
	u8 check;
	int timeout;

	addr -= SWITCH_COUNTER_NUM;
	ctrl_addr = (KS_MIB_TOTAL_RX_1 - KS_MIB_TOTAL_RX_0) * port;
	ctrl_addr += addr + KS_MIB_TOTAL_RX_0;

	sw->ops->acquire(sw);

	ctrl_addr |= IND_ACC_TABLE(TABLE_MIB | TABLE_READ);
	sw->reg->w16(sw, REG_IND_CTRL_0, ctrl_addr);

	for (timeout = 2; timeout > 0; timeout--) {
		check = sw->reg->r8(sw, REG_IND_MIB_CHECK);

		if (check & MIB_COUNTER_VALID) {
			data = sw->reg->r32(sw, REG_IND_DATA_LO);
			if (addr < 2) {
				u64 total;

				total = check & MIB_TOTAL_BYTES_H;
				total <<= 32;
				*cnt += total;
				*cnt += data;
				if (check & MIB_COUNTER_OVERFLOW) {
					total = MIB_TOTAL_BYTES_H + 1;
					total <<= 32;
					*cnt += total;
				}
			} else {
				if (check & MIB_COUNTER_OVERFLOW)
					*cnt += MIB_PACKET_DROPPED + 1;
				*cnt += data & MIB_PACKET_DROPPED;
			}
			break;
		}
	}

	sw->ops->release(sw);
}  /* port_r_mib_pkt */

static int exit_mib_read(struct ksz_sw *sw)
{
	if (sw->intr_using)
		return true;
	return false;
}  /* exit_mib_read */

/**
 * port_r_cnt - read MIB counters periodically
 * @sw:		The switch instance.
 * @port:	The port index.
 *
 * This routine is used to read the counters of the port periodically to avoid
 * counter overflow.  The hardware should be acquired first before calling this
 * routine.
 *
 * Return non-zero when not all counters not read.
 */
static int port_r_cnt(struct ksz_sw *sw, uint port)
{
	struct ksz_port_mib *mib = get_port_mib(sw, port);

	if (mib->mib_start < SWITCH_COUNTER_NUM)
		while (mib->cnt_ptr < SWITCH_COUNTER_NUM) {
			if (exit_mib_read(sw))
				return mib->cnt_ptr;
			++mib->read_cnt[mib->cnt_ptr];
			if (mib->read_cnt[mib->cnt_ptr] >=
					mib->read_max[mib->cnt_ptr]) {
				mib->read_cnt[mib->cnt_ptr] = 0;
				port_r_mib_cnt(sw, port, mib->cnt_ptr,
					&mib->counter[mib->cnt_ptr]);
			}
			++mib->cnt_ptr;
		}
	if (sw->mib_cnt > SWITCH_COUNTER_NUM)
		while (mib->cnt_ptr < TOTAL_SWITCH_COUNTER_NUM) {
			++mib->read_cnt[mib->cnt_ptr];
			if (mib->read_cnt[mib->cnt_ptr] >=
					mib->read_max[mib->cnt_ptr]) {
				mib->read_cnt[mib->cnt_ptr] = 0;
				port_r_mib_pkt(sw, port, mib->cnt_ptr,
					&mib->counter[mib->cnt_ptr]);
			}
			++mib->cnt_ptr;
		}
	mib->cnt_ptr = 0;
	return 0;
}  /* port_r_cnt */

/**
 * sw_cfg_mib_counter_ctrl - configure MIB counter control
 * @sw:		The switch instance.
 * @ctrl:	The control.
 * @port:	The port index.
 *
 * This routine configures the MIB counter control for flush or freeze.
 */
static void sw_cfg_mib_counter_ctrl(struct ksz_sw *sw, int ctrl, uint port)
{
	uint count;
	uint start;
	uint stop;
	u8 data;

	if (port < sw->port_cnt) {
		start = get_log_port(sw, port);
		stop = start + 1;
		data = (1 << port);
	} else {
		start = 0;
		stop = sw->mib_port_cnt + 1;
		data = sw->PORT_MASK;
	}
	if (ctrl & 4)
		data |= SW_MIB_COUNTER_FLUSH;
	if (ctrl & 2)
		data |= SW_MIB_COUNTER_FREEZE;
	SW_W(sw, REG_SW_CTRL_6, data);
	if (!(ctrl & 3))
		for (count = start; count < stop; count++) {
			struct ksz_port_mib *mib;

			port = get_phy_port(sw, count);
			mib = get_port_mib(sw, port);
			memset((void *) mib->counter, 0, sizeof(u64) *
				TOTAL_SWITCH_COUNTER_NUM);
			mib->rate[0].last = mib->rate[1].last = 0;
			mib->rate[0].last_cnt = mib->rate[1].last_cnt = 0;
			mib->rate[0].peak = mib->rate[1].peak = 0;
		}
}  /* sw_cfg_mib_counter_ctrl */

/**
 * port_init_cnt - initialize MIB counter values
 * @sw:		The switch instance.
 * @port:	The port index.
 *
 * This routine is used to initialize all counters to zero if the hardware
 * cannot do it after reset.
 */
static inline void port_init_cnt(struct ksz_sw *sw, uint port)
{
	struct ksz_port_mib *mib = get_port_mib(sw, port);

	mib->cnt_ptr = 0;
	if (mib->mib_start < SWITCH_COUNTER_NUM)
		do {
			mib->read_cnt[mib->cnt_ptr] = 0;
			mib->read_max[mib->cnt_ptr] =
				mib_read_max[mib->cnt_ptr];
			port_r_mib_cnt(sw, port, mib->cnt_ptr,
				&mib->counter[mib->cnt_ptr]);
			++mib->cnt_ptr;
		} while (mib->cnt_ptr < SWITCH_COUNTER_NUM);
	if (sw->mib_cnt > SWITCH_COUNTER_NUM)
		do {
			mib->read_cnt[mib->cnt_ptr] = 0;
			mib->read_max[mib->cnt_ptr] =
				mib_read_max[mib->cnt_ptr];
			port_r_mib_pkt(sw, port, mib->cnt_ptr,
				&mib->counter[mib->cnt_ptr]);
			++mib->cnt_ptr;
		} while (mib->cnt_ptr < TOTAL_SWITCH_COUNTER_NUM);
	memset((void *) mib->counter, 0, sizeof(u64) *
		TOTAL_SWITCH_COUNTER_NUM);
	mib->cnt_ptr = 0;
	mib->rate[0].last = mib->rate[1].last = 0;
	mib->rate[0].last_cnt = mib->rate[1].last_cnt = 0;
	mib->rate[0].peak = mib->rate[1].peak = 0;
}  /* port_init_cnt */

/* -------------------------------------------------------------------------- */

/*
 * Port functions
 */

/**
 * port_chk - check port register bits
 * @sw:		The switch instance.
 * @port:	The port index.
 * @offset:	The offset of the port register.
 * @bits:	The data bits to check.
 *
 * This function checks whether the specified bits of the port register are set
 * or not.
 *
 * Return 0 if the bits are not set.
 */
static int port_chk(struct ksz_sw *sw, uint port, int offset, SW_D bits)
{
	u32 addr;
	SW_D data;

	PORT_CTRL_ADDR(port, addr);
	addr += offset;
	data = SW_R(sw, addr);
	return (data & bits) == bits;
}  /* port_chk */

/**
 * port_cfg - set port register bits
 * @sw:		The switch instance.
 * @port:	The port index.
 * @offset:	The offset of the port register.
 * @bits:	The data bits to set.
 * @set:	The flag indicating whether the bits are to be set or not.
 *
 * This routine sets or resets the specified bits of the port register.
 */
static void port_cfg(struct ksz_sw *sw, uint port, int offset, SW_D bits,
	bool set)
{
	u32 addr;
	SW_D data;

	PORT_CTRL_ADDR(port, addr);
	addr += offset;
	data = SW_R(sw, addr);
	if (set)
		data |= bits;
	else
		data &= ~bits;
	SW_W(sw, addr, data);
}  /* port_cfg */

#if 0
/**
 * port_chk_shift - check port bit
 * @sw:		The switch instance.
 * @port:	The port index.
 * @offset:	The offset of the register.
 * @shift:	Number of bits to shift.
 *
 * This function checks whether the specified port is set in the register or
 * not.
 *
 * Return 0 if the port is not set.
 */
static int port_chk_shift(struct ksz_sw *sw, uint port, u32 addr, int shift)
{
	SW_D data;
	SW_D bit = 1 << port;

	data = SW_R(sw, addr);
	data >>= shift;
	return (data & bit) == bit;
}

/**
 * port_cfg_shift - set port bit
 * @sw:		The switch instance.
 * @port:	The port index.
 * @offset:	The offset of the register.
 * @shift:	Number of bits to shift.
 * @set:	The flag indicating whether the port is to be set or not.
 *
 * This routine sets or resets the specified port in the register.
 */
static void port_cfg_shift(struct ksz_sw *sw, uint port, u32 addr, int shift,
	bool set)
{
	SW_D data;
	SW_D bits = 1 << port;

	data = SW_R(sw, addr);
	bits <<= shift;
	if (set)
		data |= bits;
	else
		data &= ~bits;
	SW_W(sw, addr, data);
}
#endif

/**
 * port_r8 - read byte from port register
 * @sw:		The switch instance.
 * @port:	The port index.
 * @offset:	The offset of the port register.
 * @data:	Buffer to store the data.
 *
 * This routine reads a byte from the port register.
 */
static void port_r8(struct ksz_sw *sw, uint port, int offset, u8 *data)
{
	u32 addr;

	PORT_CTRL_ADDR(port, addr);
	addr += offset;
	*data = sw->reg->r8(sw, addr);
}  /* port_r8 */

/**
 * port_w8 - write byte to port register
 * @sw:		The switch instance.
 * @port:	The port index.
 * @offset:	The offset of the port register.
 * @data:	Data to write.
 *
 * This routine writes a byte to the port register.
 */
static void port_w8(struct ksz_sw *sw, uint port, int offset, u8 data)
{
	u32 addr;

	PORT_CTRL_ADDR(port, addr);
	addr += offset;
	sw->reg->w8(sw, addr, data);
}  /* port_w8 */

/**
 * port_r16 - read word from port register.
 * @sw:		The switch instance.
 * @port:	The port index.
 * @offset:	The offset of the port register.
 * @data:	Buffer to store the data.
 *
 * This routine reads a word from the port register.
 */
static void port_r16(struct ksz_sw *sw, uint port, int offset, u16 *data)
{
	u32 addr;

	PORT_CTRL_ADDR(port, addr);
	addr += offset;
	*data = sw->reg->r16(sw, addr);
}  /* port_r16 */

/**
 * port_w16 - write word to port register.
 * @sw:		The switch instance.
 * @port:	The port index.
 * @offset:	The offset of the port register.
 * @data:	Data to write.
 *
 * This routine writes a word to the port register.
 */
static void port_w16(struct ksz_sw *sw, uint port, int offset, u16 data)
{
	u32 addr;

	PORT_CTRL_ADDR(port, addr);
	addr += offset;
	sw->reg->w16(sw, addr, data);
}  /* port_w16 */

/**
 * port_r_s - read bits with shift from port register.
 * @sw:		The switch instance.
 * @p:		The port index.
 * @reg:	The port register.
 * @mask:	The mask to apply.
 * @shift:	The shift to use.
 *
 * This function reads bits from the port register.
 */
static u8 port_r_s(struct ksz_sw *sw, uint p, u32 reg, u8 mask, u8 shift)
{
	u8 data;

	port_r8(sw, p, reg, &data);
	data >>= shift;
	data &= mask;
	return data;
}  /* port_r_s */

/**
 * port_w_s - write bits with shift to port register.
 * @sw:		The switch instance.
 * @p:		The port index.
 * @reg:	The port register.
 * @mask:	The mask to apply.
 * @shift:	The shift to use.
 *
 * This routine writes bits to the port register.
 */
static void port_w_s(struct ksz_sw *sw, uint p, u32 reg, u8 mask, u8 shift,
	u8 val)
{
	u8 data;

	port_r8(sw, p, reg, &data);
	data &= ~(mask << shift);
	data |= (val & mask) << shift;
	port_w8(sw, p, reg, data);
}  /* port_w_s */

/**
 * sw_chk - check switch register bits
 * @sw:		The switch instance.
 * @addr:	The address of the switch register.
 * @bits:	The data bits to check.
 *
 * This function checks whether the specified bits of the switch register are
 * set or not.
 *
 * Return 0 if the bits are not set.
 */
static int sw_chk(struct ksz_sw *sw, u32 addr, SW_D bits)
{
	SW_D data;

	data = SW_R(sw, addr);
	return (data & bits) == bits;
}  /* sw_chk */

/**
 * sw_cfg - set switch register bits
 * @sw:		The switch instance.
 * @addr:	The address of the switch register.
 * @bits:	The data bits to set.
 * @set:	The flag indicating whether the bits are to be set or not.
 *
 * This function sets or resets the specified bits of the switch register.
 */
static void sw_cfg(struct ksz_sw *sw, u32 addr, SW_D bits, bool set)
{
	SW_D data;

	data = SW_R(sw, addr);
	if (set)
		data |= bits;
	else
		data &= ~bits;
	SW_W(sw, addr, data);
}  /* sw_cfg */

/* -------------------------------------------------------------------------- */

/* ACL */

static inline void port_cfg_acl(struct ksz_sw *sw, uint p, bool set)
{
	port_cfg(sw, p,
		REG_PORT_CTRL_5, PORT_ACL_ENABLE, set);
}

static inline int port_chk_acl(struct ksz_sw *sw, uint p)
{
	return port_chk(sw, p,
		REG_PORT_CTRL_5, PORT_ACL_ENABLE);
}

static inline u8 port_get_authen_mode(struct ksz_sw *sw, uint p)
{
	return port_r_s(sw, p,
		REG_PORT_CTRL_5, PORT_AUTHEN_MODE, 0);
}

static void port_set_authen_mode(struct ksz_sw *sw, uint p, u8 mode)
{
	port_w_s(sw, p,
		REG_PORT_CTRL_5, PORT_AUTHEN_MODE, 0, mode);
}

/**
 * get_acl_action_info - Get ACL action field information
 * @acl:	The ACL entry.
 * @data:	The ACL data.
 *
 * This helper routine gets ACL action field information.
 */
static void get_acl_action_info(struct ksz_acl_table *acl, u8 data[])
{
	acl->prio_mode = (data[10] >> ACL_PRIO_MODE_S) & ACL_PRIO_MODE_M;
	acl->prio = (data[10] >> ACL_PRIO_S) & ACL_PRIO_M;
	acl->vlan_prio_replace = !!(data[10] & ACL_VLAN_PRIO_REPLACE);
	acl->vlan_prio = data[11] >> ACL_VLAN_PRIO_S;
	acl->vlan_prio |= (data[10] & ACL_VLAN_PRIO_HI_M) << 1;
	acl->map_mode = (data[11] >> ACL_MAP_MODE_S) & ACL_MAP_MODE_M;
	acl->ports = data[11] & ACL_MAP_PORT_M;
}  /* get_acl_action_info */

/**
 * get_acl_table_info - Get ACL table information
 * @acl:	The ACL entry.
 * @data:	The ACL data.
 *
 * This helper routine gets ACL table information.
 */
static void get_acl_table_info(struct ksz_acl_table *acl, u8 data[])
{
	u16 *ptr_16;
	u32 *ptr_32;
	int i;
	int j;
	int cnt = 0;

	acl->first_rule = data[0] & ACL_FIRST_RULE_M;
	acl->mode = (data[1] >> ACL_MODE_S) & ACL_MODE_M;
	acl->enable = (data[1] >> ACL_ENABLE_S) & ACL_ENABLE_M;
	acl->src = !!(data[1] & ACL_SRC);
	acl->equal = !!(data[1] & ACL_EQUAL);
	switch (acl->mode) {
	case ACL_MODE_LAYER_2:
		for (i = 0; i < 6; i++)
			acl->mac[i] = data[2 + i];
		ptr_16 = (u16 *) &data[8];
		acl->eth_type = be16_to_cpu(*ptr_16);
		if (ACL_ENABLE_2_COUNT == acl->enable) {
			cnt = 1;
			ptr_16 = (u16 *) &data[10];
			acl->cnt = (be16_to_cpu(*ptr_16) >> ACL_CNT_S) &
				ACL_CNT_M;
			acl->msec =
				!!(data[ACL_INTR_CNT_START] & ACL_MSEC_UNIT);
			acl->intr_mode =
				!!(data[ACL_INTR_CNT_START] & ACL_INTR_MODE);
		}
		break;
	case ACL_MODE_LAYER_3:
		j = 2;
		for (i = 0; i < 4; i++, j++)
			acl->ip4_addr[i] = data[j];
		for (i = 0; i < 4; i++, j++)
			acl->ip4_mask[i] = data[j];
		break;
	case ACL_MODE_LAYER_4:
		switch (acl->enable) {
		case ACL_ENABLE_4_TCP_SEQN_COMP:
			ptr_32 = (u32 *) &data[2];
			acl->seqnum = be32_to_cpu(*ptr_32);
			break;
		default:
			ptr_16 = (u16 *) &data[2];
			acl->max_port = be16_to_cpu(*ptr_16);
			++ptr_16;
			acl->min_port = be16_to_cpu(*ptr_16);
			acl->port_mode = (data[6] >> ACL_PORT_MODE_S) &
				ACL_PORT_MODE_M;
		}
		acl->protocol = (data[6] & 1) << 7;
		acl->protocol |= (data[7] >> 1);
		acl->tcp_flag_enable = !!(data[7] & ACL_TCP_FLAG_ENABLE);
		acl->tcp_flag_mask = data[8];
		acl->tcp_flag = data[9];
		break;
	default:
		break;
	}
	if (!cnt)
		get_acl_action_info(acl, data);
	ptr_16 = (u16 *) &data[ACL_RULESET_START];
	acl->ruleset = be16_to_cpu(*ptr_16);
}  /* get_acl_table_info */

/**
 * set_acl_action_info - Set ACL action field information
 * @acl:	The ACL entry.
 * @data:	The ACL data.
 *
 * This helper routine sets ACL action field information.
 */
static void set_acl_action_info(struct ksz_acl_table *acl, u8 data[])
{
	if (acl->data[0] != 0xff)
		memcpy(data, acl->data, ACL_TABLE_LEN);
	data[10] = (acl->prio_mode & ACL_PRIO_MODE_M) << ACL_PRIO_MODE_S;
	data[10] |= (acl->prio & ACL_PRIO_M) << ACL_PRIO_S;
	if (acl->vlan_prio_replace)
		data[10] |= ACL_VLAN_PRIO_REPLACE;
	data[10] |= (acl->vlan_prio >> 1);
	data[11] = acl->vlan_prio << ACL_VLAN_PRIO_S;
	data[11] |= (acl->map_mode & ACL_MAP_MODE_M) << ACL_MAP_MODE_S;
	data[11] |= acl->ports & ACL_MAP_PORT_M;
}  /* set_acl_action_info */

/**
 * set_acl_ruleset_info - Set ACL ruleset field information
 * @acl:	The ACL entry.
 * @data:	The ACL data.
 *
 * This helper routine sets ACL ruleset field information.
 */
static void set_acl_ruleset_info(struct ksz_acl_table *acl, u8 data[])
{
	u16 *ptr_16;

	if (acl->data[0] != 0xff)
		memcpy(data, acl->data, ACL_TABLE_LEN);
	data[0] = acl->first_rule & ACL_FIRST_RULE_M;
	ptr_16 = (u16 *) &data[ACL_RULESET_START];
	*ptr_16 = cpu_to_be16(acl->ruleset);
}  /* set_acl_ruleset_info */

/**
 * set_acl_table_info - Set ACL table information
 * @acl:	The ACL entry.
 * @data:	The ACL data.
 *
 * This helper routine sets ACL table information.
 */
static void set_acl_table_info(struct ksz_acl_table *acl, u8 data[])
{
	u16 *ptr_16;
	u32 *ptr_32;
	int i;
	int j;

	if (acl->data[0] != 0xff)
		memcpy(data, acl->data, ACL_TABLE_LEN);
	data[1] = (acl->mode & ACL_MODE_M) << ACL_MODE_S;
	data[1] |= (acl->enable & ACL_ENABLE_M) << ACL_ENABLE_S;
	if (acl->src)
		data[1] |= ACL_SRC;
	if (acl->equal)
		data[1] |= ACL_EQUAL;
	switch (acl->mode) {
	case ACL_MODE_LAYER_2:
		for (i = 0; i < 6; i++)
			data[2 + i] = acl->mac[i];
		ptr_16 = (u16 *) &data[8];
		*ptr_16 = cpu_to_be16(acl->eth_type);
		if (ACL_ENABLE_2_COUNT == acl->enable) {
			data[ACL_INTR_CNT_START] = 0;
			ptr_16 = (u16 *) &data[10];
			*ptr_16 = cpu_to_be16((acl->cnt & ACL_CNT_M) <<
				ACL_CNT_S);
			if (acl->msec)
				data[ACL_INTR_CNT_START] |= ACL_MSEC_UNIT;
			if (acl->intr_mode)
				data[ACL_INTR_CNT_START] |= ACL_INTR_MODE;
		}
		break;
	case ACL_MODE_LAYER_3:
		j = 2;
		for (i = 0; i < 4; i++, j++)
			data[j] = acl->ip4_addr[i];
		for (i = 0; i < 4; i++, j++)
			data[j] = acl->ip4_mask[i];
		break;
	case ACL_MODE_LAYER_4:
		switch (acl->enable) {
		case ACL_ENABLE_4_TCP_SEQN_COMP:
			ptr_32 = (u32 *) &data[2];
			*ptr_32 = cpu_to_be32(acl->seqnum);
			data[6] = 0;
			break;
		default:
			ptr_16 = (u16 *) &data[2];
			*ptr_16 = cpu_to_be16(acl->max_port);
			++ptr_16;
			*ptr_16 = cpu_to_be16(acl->min_port);
			data[6] = (acl->port_mode & ACL_PORT_MODE_M) <<
				ACL_PORT_MODE_S;
		}
		data[6] |= (acl->protocol >> 7);
		data[7] = (acl->protocol << 1);
		if (acl->tcp_flag_enable)
			data[7] |= ACL_TCP_FLAG_ENABLE;
		data[8] = acl->tcp_flag_mask;
		data[9] = acl->tcp_flag;
		break;
	default:
		break;
	}
}  /* set_acl_table_info */

/**
 * wait_for_acl_table - Wait for ACL table
 * @sw:		The switch instance.
 * @port:	The port index.
 *
 * This helper routine waits for ACL table to be ready for access.
 */
static void wait_for_acl_table(struct ksz_sw *sw, uint port)
{
	u8 ctrl;

	do {
		sw_r_ext_table(sw, TABLE_ACL, port + 1, REG_PORT_ACL_CTRL_0,
			&ctrl);
	} while (!(ctrl & (PORT_ACL_WRITE_DONE | PORT_ACL_READ_DONE)));
}  /* wait_for_acl_table */

/**
 * sw_r_acl_hw - read from ACL table
 * @sw:		The switch instance.
 * @port:	The port index.
 * @addr:	The ACL index.
 * @data:	Buffer to hold the ACL data.
 *
 * This routine reads from ACL table of the port.
 */
static void sw_r_acl_hw(struct ksz_sw *sw, uint port, u16 addr, u8 data[])
{
	u8 ctrl = (addr & PORT_ACL_INDEX_M);

	port++;
	sw_w_ext_table(sw, TABLE_ACL, port, REG_PORT_ACL_CTRL_0, ctrl);
	do {
		sw_r_ext_table(sw, TABLE_ACL, port, REG_PORT_ACL_CTRL_0,
			&ctrl);
	} while (!(ctrl & PORT_ACL_READ_DONE));
	sw_g_ext_table(sw, TABLE_ACL, port, 0, data, ACL_TABLE_LEN);
}  /* sw_r_acl_hw */

/**
 * sw_r_acl_table - read from ACL table
 * @sw:		The switch instance.
 * @port:	The port index.
 * @addr:	The address of the table entry.
 * @acl:	Buffer to store the ACL entry.
 *
 * This function reads an entry of the ACL table of the port.
 *
 * Return 0 if the entry is valid; otherwise -1.
 */
static int sw_r_acl_table(struct ksz_sw *sw, uint port, u16 addr,
	struct ksz_acl_table *acl)
{
	u8 data[20];
	int rc = -1;

	sw->ops->acquire(sw);
	wait_for_acl_table(sw, port);
	sw_r_acl_hw(sw, port, addr, data);
	get_acl_table_info(acl, data);
	memcpy(acl->data, data, ACL_TABLE_LEN);
	sw->ops->release(sw);
	if (acl->mode)
		rc = 0;
	acl->changed = 0;
	return rc;
}  /* sw_r_acl_table */

/**
 * sw_a_acl_hw - write to ACL action field
 * @sw:		The switch instance.
 * @port:	The port index.
 * @addr:	The ACL index.
 * @data:	The ACL data to write.
 *
 * This routine writes to ACL action field of the port.
 */
static void sw_a_acl_hw(struct ksz_sw *sw, uint port, u16 addr, u8 data[])
{
	u8 ctrl = (addr & PORT_ACL_INDEX_M) | PORT_ACL_WRITE;

	if (sw->info->port_cfg[port].acl_byte_enable != ACL_ACTION_ENABLE)
		sw->info->port_cfg[port].acl_byte_enable = ACL_ACTION_ENABLE;
	data[REG_PORT_ACL_BYTE_EN_MSB] = 0;
	data[REG_PORT_ACL_BYTE_EN_LSB] = ACL_ACTION_ENABLE;
	data[REG_PORT_ACL_CTRL_0] = ctrl;
	port++;
	sw_p_ext_table(sw, TABLE_ACL, port, ACL_ACTION_START,
		       &data[ACL_ACTION_START], ACL_ACTION_LEN);
	sw_p_ext_table(sw, TABLE_ACL, port, REG_PORT_ACL_BYTE_EN_MSB,
		       &data[REG_PORT_ACL_BYTE_EN_MSB], 3);
	do {
		sw_r_ext_table(sw, TABLE_ACL, port, REG_PORT_ACL_CTRL_0,
			&ctrl);
	} while (!(ctrl & PORT_ACL_WRITE_DONE));
}  /* sw_a_acl_hw */

/**
 * sw_w_acl_hw - enable/disable ACL table
 * @sw:		The switch instance.
 * @port:	The port index.
 * @addr:	The ACL index.
 * @data:	The ACL data to write.
 *
 * This routine enables/disables ACL table of the port.
 */
static void sw_s_acl_hw(struct ksz_sw *sw, uint port, u16 addr, u8 data)
{
	u8 ctrl = (addr & PORT_ACL_INDEX_M) | PORT_ACL_WRITE;

	if (sw->info->port_cfg[port].acl_byte_enable != ACL_MODE_ENABLE) {
		u8 byte_enable[2] = { ACL_MODE_ENABLE >> 8, 0 };

		sw->info->port_cfg[port].acl_byte_enable = ACL_MODE_ENABLE;
		sw_p_ext_table(sw, TABLE_ACL, port + 1,
			       REG_PORT_ACL_BYTE_EN_MSB, byte_enable, 2);
	}
	port++;
	sw_w_ext_table(sw, TABLE_ACL, port, 1, data);
	sw_w_ext_table(sw, TABLE_ACL, port, REG_PORT_ACL_CTRL_0, ctrl);
	do {
		sw_r_ext_table(sw, TABLE_ACL, port, REG_PORT_ACL_CTRL_0,
			&ctrl);
	} while (!(ctrl & PORT_ACL_WRITE_DONE));
}  /* sw_s_acl_hw */

/**
 * sw_w_acl_hw - write to ACL table
 * @sw:		The switch instance.
 * @port:	The port index.
 * @addr:	The ACL index.
 * @data:	The ACL data to write.
 *
 * This routine writes to ACL table of the port.
 */
static void sw_w_acl_hw(struct ksz_sw *sw, uint port, u16 addr, u8 data[],
	u16 byte_enable)
{
	u8 ctrl = (addr & PORT_ACL_INDEX_M) | PORT_ACL_WRITE;

	if (sw->info->port_cfg[port].acl_byte_enable != byte_enable)
		sw->info->port_cfg[port].acl_byte_enable = byte_enable;
	data[0xe] = 0;
	data[0xf] = 0;
	data[REG_PORT_ACL_BYTE_EN_MSB] = (u8)(byte_enable >> 8);
	data[REG_PORT_ACL_BYTE_EN_LSB] = (u8)byte_enable;
	data[REG_PORT_ACL_CTRL_0] = ctrl;
	port++;
	sw_p_ext_table(sw, TABLE_ACL, port, 0, data, ACL_TABLE_LEN + 2 + 3);
	do {
		sw_r_ext_table(sw, TABLE_ACL, port, REG_PORT_ACL_CTRL_0,
			&ctrl);
	} while (!(ctrl & PORT_ACL_WRITE_DONE));
}  /* sw_w_acl_hw */

/**
 * sw_w_acl_action - write to ACL action field
 * @sw:		The switch instance.
 * @port:	The port index.
 * @addr:	The address of the table entry.
 * @acl:	The ACL entry.
 *
 * This routine writes to the action field of an entry of the ACL table.
 */
static void sw_w_acl_action(struct ksz_sw *sw, uint port, u16 addr,
	struct ksz_acl_table *acl)
{
	u8 data[20];

	sw->ops->acquire(sw);
	wait_for_acl_table(sw, port);
	set_acl_action_info(acl, data);
	sw_a_acl_hw(sw, port, addr, data);
	memcpy(&acl->data[ACL_ACTION_START], &data[ACL_ACTION_START],
		ACL_ACTION_LEN);
	sw->ops->release(sw);
	acl->action_changed = 0;
}  /* sw_w_acl_action */

/**
 * sw_w_acl_ruleset - write to ACL ruleset field
 * @sw:		The switch instance.
 * @port:	The port index.
 * @addr:	The address of the table entry.
 * @acl:	The ACL entry.
 *
 * This routine writes to the ruleset field of an entry of the ACL table.
 */
static void sw_w_acl_ruleset(struct ksz_sw *sw, uint port, u16 addr,
	struct ksz_acl_table *acl)
{
	u8 data[20];

	sw->ops->acquire(sw);
	wait_for_acl_table(sw, port);
	set_acl_ruleset_info(acl, data);
	sw_w_acl_hw(sw, port, addr, data, ACL_RULESET_ENABLE);

	/* First rule */
	acl->data[0] = data[0];
	memcpy(&acl->data[ACL_RULESET_START], &data[ACL_RULESET_START],
		ACL_RULESET_LEN);
	sw->ops->release(sw);
	acl->ruleset_changed = 0;
}  /* sw_w_acl_ruleset */

/**
 * sw_w_acl_rule - write to ACL matching and process fields
 * @sw:		The switch instance.
 * @port:	The port index.
 * @addr:	The address of the table entry.
 * @acl:	The ACL entry.
 *
 * This routine writes to the matching and process fields of an entry of the
 * ACL table of the port.
 */
static void sw_w_acl_rule(struct ksz_sw *sw, uint port, u16 addr,
	struct ksz_acl_table *acl)
{
	u8 data[20];
	u16 byte_enable = ACL_MATCH_ENABLE;

	if (ACL_MODE_LAYER_2 == acl->mode && ACL_ENABLE_2_COUNT == acl->enable)
		byte_enable = ACL_BYTE_ENABLE;
	sw->ops->acquire(sw);
	wait_for_acl_table(sw, port);
	set_acl_table_info(acl, data);
	if (data[0] == acl->data[0] && !memcmp(&data[2], &acl->data[2], 12))
		sw_s_acl_hw(sw, port, addr, data[1]);
	else
		sw_w_acl_hw(sw, port, addr, data, byte_enable);
	memcpy(acl->data, data, ACL_ACTION_START);
	sw->ops->release(sw);
	acl->changed = 0;
}  /* sw_w_acl_rule */

/**
 * sw_w_acl_table - write to ACL table
 * @sw:		The switch instance.
 * @port:	The port index.
 * @addr:	The address of the table entry.
 * @acl:	The ACL entry.
 *
 * This routine writes an entry of the ACL table of the port.
 */
static void sw_w_acl_table(struct ksz_sw *sw, uint port, u16 addr,
	struct ksz_acl_table *acl)
{
	u8 data[20];

	if (ACL_MODE_LAYER_2 == acl->mode && ACL_ENABLE_2_COUNT == acl->enable)
		return;
	acl->data[0] = 0xff;
	memset(data, 0, sizeof(data));
	sw->ops->acquire(sw);
	wait_for_acl_table(sw, port);
	set_acl_action_info(acl, data);
	set_acl_table_info(acl, data);
	set_acl_ruleset_info(acl, data);
	sw_w_acl_hw(sw, port, addr, data, ACL_BYTE_ENABLE);
	memcpy(acl->data, data, ACL_TABLE_LEN);
	sw->ops->release(sw);
}  /* sw_w_acl_table */

/**
 * acl_action_info - format ACL action field information
 * @acl:	The ACL entry.
 * @index;	The entry index.
 * @buf:	Buffer to store the strings.
 * @len:	Lenght of buffer.
 *
 * This helper routine formats the ACL action field information.
 */
static int acl_action_info(struct ksz_acl_table *acl, u16 index, char *buf,
	int len)
{
	char prio = 'p';
	char vlan = 'v';

	if (acl->prio_mode != ACL_PRIO_MODE_DISABLE)
		prio = 'P';
	if (acl->vlan_prio_replace)
		vlan = 'V';
	len += sprintf(buf + len,
		"%x: %c:%u=%u %c:%u=%u %u=%04x [%u]\n",
		index,
		prio, acl->prio_mode, acl->prio,
		vlan, acl->vlan_prio_replace, acl->vlan_prio,
		acl->map_mode, acl->ports,
		acl->action_changed ? 8 : 1);
	return len;
}  /* acl_action_info */

/**
 * acl_ruleset_info - format ACL ruleset field information
 * @acl:	The ACL entry.
 * @index;	The entry index.
 * @buf:	Buffer to store the strings.
 * @len:	Lenght of buffer.
 *
 * This helper routine formats the ACL ruleset field information.
 */
static int acl_ruleset_info(struct ksz_acl_table *acl, u16 index, char *buf,
	int len)
{
	len += sprintf(buf + len,
		"%x: %x:%04x [%u]\n",
		index,
		acl->first_rule, acl->ruleset,
		acl->ruleset_changed ? 8 : 1);
	return len;
}  /* acl_ruleset_info */

/**
 * acl_info - format ACL matching and process field information
 * @acl:	The ACL entry.
 * @index;	The entry index.
 * @buf:	Buffer to store the strings.
 * @len:	Lenght of buffer.
 *
 * This helper routine formats the ACL matching and process field information.
 */
static int acl_info(struct ksz_acl_table *acl, u16 index, char *buf, int len)
{
	char enable = 'e';
	char equal = 'q';
	char src = 's';
	char cnt = 'c';
	char protocol = 'x';
	char flag = 'f';
	char seqnum = 's';
	char msec[4];

	switch (acl->mode) {
	case ACL_MODE_LAYER_2:
		enable = 'E';
		*msec = 0;
		if (ACL_ENABLE_2_COUNT == acl->enable) {
			equal = 'Q';
			src = 'S';
			cnt = 'C';
			if (acl->intr_mode)
				*msec = 0;
			else if (acl->msec)
				strcpy(msec, "ms ");
			else
				strcpy(msec, "us ");
		} else {
			equal = 'Q';
			if (ACL_ENABLE_2_TYPE != acl->enable)
				src = 'S';
		}
		len += sprintf(buf + len,
			"%x: %02X:%02X:%02X:%02X:%02X:%02X-%04x "
			"%c:%u.%u %s"
			"%c:%u %c:%u %c:%u "
			"[%u]\n",
			index,
			acl->mac[0], acl->mac[1], acl->mac[2],
			acl->mac[3], acl->mac[4], acl->mac[5],
			acl->eth_type,
			cnt, acl->intr_mode, acl->cnt, msec,
			enable, acl->enable,
			src, acl->src, equal, acl->equal,
			acl->changed ? 8 : acl->mode);
		break;
	case ACL_MODE_LAYER_3:
		if (ACL_ENABLE_3_IP == acl->enable ||
		    ACL_ENABLE_3_SRC_DST_COMP == acl->enable)
			enable = 'E';
		if (ACL_ENABLE_3_IP == acl->enable) {
			equal = 'Q';
			src = 'S';
		}
		len += sprintf(buf + len,
			"%x: %u.%u.%u.%u:%u.%u.%u.%u "
			"%c:%u %c:%u %c:%u "
			"[%u]\n",
			index,
			acl->ip4_addr[0], acl->ip4_addr[1],
			acl->ip4_addr[2], acl->ip4_addr[3],
			acl->ip4_mask[0], acl->ip4_mask[1],
			acl->ip4_mask[2], acl->ip4_mask[3],
			enable, acl->enable,
			src, acl->src, equal, acl->equal,
			acl->changed ? 8 : acl->mode);
		break;
	case ACL_MODE_LAYER_4:
		enable = 'E';
		if (ACL_ENABLE_4_PROTOCOL == acl->enable) {
			protocol = 'X';
			equal = 'Q';
		} else if (ACL_ENABLE_4_TCP_SEQN_COMP == acl->enable) {
			seqnum = 'S';
			equal = 'Q';
			if (acl->tcp_flag_enable)
				flag = 'F';
		} else if (ACL_ENABLE_4_TCP_PORT_COMP == acl->enable) {
			src = 'S';
			if (acl->tcp_flag_enable)
				flag = 'F';
		} else
			src = 'S';
		len += sprintf(buf + len,
			"%x: %u=%4x-%4x 0%c%x %c:%08x %c:%u=%x:%x "
			"%c:%u %c:%u %c:%u "
			"[%u]\n",
			index,
			acl->port_mode, acl->min_port, acl->max_port,
			protocol, acl->protocol, seqnum, acl->seqnum,
			flag, acl->tcp_flag_enable,
			acl->tcp_flag, acl->tcp_flag_mask,
			enable, acl->enable,
			src, acl->src, equal, acl->equal,
			acl->changed ? 8 : acl->mode);
		break;
	default:
		len += sprintf(buf + len,
			"%x: "
			"%c:%u %c:%u %c:%u "
			"[%u]\n",
			index,
			enable, acl->enable,
			src, acl->src, equal, acl->equal,
			acl->changed ? 8 : acl->mode);
		break;
	}
	return len;
}  /* acl_info */

/**
 * sw_d_acl_table - dump ACL table
 * @sw:		The switch instance.
 * @port:	The port index.
 *
 * This routine dumps ACL table of the port.
 */
static ssize_t sw_d_acl_table(struct ksz_sw *sw, uint port, char *buf,
	ssize_t len)
{
	struct ksz_port_cfg *cfg = get_port_cfg(sw, port);
	struct ksz_acl_table *acl;
	int i;
	int acl_on;
	int min = 0;

	sw->ops->acquire(sw);
	acl_on = port_chk_acl(sw, port);
	if (!acl_on) {
		printk(KERN_INFO "ACL not on for port %d\n", port);
		port_cfg_acl(sw, port, true);
	}
	sw->ops->release(sw);
	for (i = 0; i < ACL_TABLE_ENTRIES; i++) {
		acl = &cfg->acl_info[i];
		acl->action_selected = false;
		sw_r_acl_table(sw, port, i, acl);
	}
	for (i = 0; i < ACL_TABLE_ENTRIES; i++) {
		acl = &cfg->acl_info[i];
		if (!acl->mode)
			continue;
		if (!min)
			len += sprintf(buf + len, "rules:\n");
		len = acl_info(acl, i, buf, len);
		min = 1;
	}
	if (min)
		len += sprintf(buf + len, "\n");
	min = 0;
	for (i = 0; i < ACL_TABLE_ENTRIES; i++) {
		acl = &cfg->acl_info[i];
		if (!acl->ruleset)
			continue;
		if (!min)
			len += sprintf(buf + len, "rulesets:\n");
		cfg->acl_info[acl->first_rule].action_selected = true;
		len = acl_ruleset_info(acl, i, buf, len);
		min = 1;
	}
	if (min)
		len += sprintf(buf + len, "\n");
	min = 0;
	for (i = 0; i < ACL_TABLE_ENTRIES; i++) {
		acl = &cfg->acl_info[i];
		if (ACL_PRIO_MODE_DISABLE == acl->prio_mode &&
		    ACL_MAP_MODE_DISABLE == acl->map_mode &&
		    !acl->ports &&
		    !acl->vlan_prio_replace && !acl->action_selected)
			continue;
		if (ACL_MODE_LAYER_2 == acl->mode &&
		    ACL_ENABLE_2_COUNT == acl->enable)
			continue;
		if (!min)
			len += sprintf(buf + len, "actions:\n");
		len = acl_action_info(acl, i, buf, len);
		min = 1;
	}
	if (!acl_on) {
		sw->ops->acquire(sw);
		port_cfg_acl(sw, port, false);
		sw->ops->release(sw);
	}
	return len;
}  /* sw_d_acl_table */

static void sw_reset_acl(struct ksz_sw *sw)
{
	struct ksz_port_cfg *cfg;
	uint n;
	uint port;

	for (n = 0; n <= sw->mib_port_cnt; n++) {
		port = get_phy_port(sw, n);
		cfg = get_port_cfg(sw, port);
		memset(cfg->acl_info, 0, sizeof(struct ksz_acl_table) *
			ACL_TABLE_ENTRIES);
		cfg->acl_index = cfg->acl_act_index = cfg->acl_rule_index = 0;
	}
}  /* sw_reset_acl */

static void sw_reset_acl_hw(struct ksz_sw *sw)
{
	struct ksz_port_cfg *cfg;
	struct ksz_acl_table *acl;
	int i;
	int acl_on;
	uint n;
	uint port;

	sw_reset_acl(sw);
	for (n = 0; n <= sw->mib_port_cnt; n++) {
		port = get_phy_port(sw, n);
		acl_on = port_chk_acl(sw, port);
		if (!acl_on)
			port_cfg_acl(sw, port, true);
		sw->ops->release(sw);
		cfg = get_port_cfg(sw, port);
		for (i = 0; i < ACL_TABLE_ENTRIES; i++) {
			acl = &cfg->acl_info[i];
			acl->mode = 0;
			acl->ruleset = 0;
			sw_w_acl_table(sw, port, i, acl);
		}
		sw->ops->acquire(sw);
		if (!acl_on)
			port_cfg_acl(sw, port, false);
	}
}  /* sw_reset_acl_hw */

static void sw_init_acl(struct ksz_sw *sw)
{
	struct ksz_port_cfg *cfg;
	struct ksz_acl_table *acl;
	int i;
	uint n;
	uint port;

	for (n = 0; n <= sw->mib_port_cnt; n++) {
		port = get_phy_port(sw, n);
		port_cfg_acl(sw, port, 1);
		cfg = get_port_cfg(sw, port);
		sw->ops->release(sw);
		for (i = 0; i < ACL_TABLE_ENTRIES; i++) {
			acl = &cfg->acl_info[i];
			sw_r_acl_table(sw, port, i, acl);
		}
		sw->ops->acquire(sw);
	}
}  /* sw_init_acl */

/* -------------------------------------------------------------------------- */

/* PME */

static u8 sw_get_pme(struct ksz_sw *sw)
{
	u8 data;

	sw_r_ext_table(sw, TABLE_PME, 0, 3, &data);
	return data;
}

static void sw_set_pme(struct ksz_sw *sw, u8 pme)
{
	sw_w_ext_table(sw, TABLE_PME, 0, 3, pme);
}

static u8 port_get_pme_ctrl(struct ksz_sw *sw, uint p)
{
	u8 data;

	sw_r_ext_table(sw, TABLE_PME, p + 1, 7, &data);
	return data;
}

static void port_set_pme_ctrl(struct ksz_sw *sw, uint p, u8 pme)
{
	sw_w_ext_table(sw, TABLE_PME, p + 1, 7, pme);
}

static u8 port_get_pme_status(struct ksz_sw *sw, uint p)
{
	u8 data;

	sw_r_ext_table(sw, TABLE_PME, p + 1, 3, &data);
	return data;
}

static void port_set_pme_status(struct ksz_sw *sw, uint p, u8 pme)
{
	sw_w_ext_table(sw, TABLE_PME, p + 1, 3, pme);
}

/* -------------------------------------------------------------------------- */

/* Bandwidth */

static inline void port_cfg_broad_storm(struct ksz_sw *sw, uint p, bool set)
{
	port_cfg(sw, p,
		P_BCAST_STORM_CTRL, PORT_BROADCAST_STORM, set);
}

static inline int port_chk_broad_storm(struct ksz_sw *sw, uint p)
{
	return port_chk(sw, p,
		P_BCAST_STORM_CTRL, PORT_BROADCAST_STORM);
}

/* Driver set switch broadcast storm protection at 10% rate. */
#define BROADCAST_STORM_PROTECTION_RATE	10

/* 148,800 frames * 67 ms / 100 */
#define BROADCAST_STORM_VALUE		9969

/**
 * sw_cfg_broad_storm - configure broadcast storm threshold
 * @sw:		The switch instance.
 * @percent:	Broadcast storm threshold in percent of transmit rate.
 *
 * This routine configures the broadcast storm threshold of the switch.
 */
static void sw_cfg_broad_storm(struct ksz_sw *sw, u8 percent)
{
	u16 data;
	u32 value = ((u32) BROADCAST_STORM_VALUE * (u32) percent / 100);

	if (value > BROADCAST_STORM_RATE)
		value = BROADCAST_STORM_RATE;

	data = sw->reg->r16(sw, S_REPLACE_VID_CTRL);
	data &= ~BROADCAST_STORM_RATE;
	data |= value;
	sw->reg->w16(sw, S_REPLACE_VID_CTRL, data);
}  /* sw_cfg_broad_storm */

/**
 * sw_get_board_storm - get broadcast storm threshold
 * @sw:		The switch instance.
 * @percent:	Buffer to store the broadcast storm threshold percentage.
 *
 * This routine retrieves the broadcast storm threshold of the switch.
 */
static void sw_get_broad_storm(struct ksz_sw *sw, u8 *percent)
{
	int num;
	u16 data;

	data = sw->reg->r16(sw, S_REPLACE_VID_CTRL);
	num = (data & BROADCAST_STORM_RATE);
	num = (num * 100 + BROADCAST_STORM_VALUE / 2) / BROADCAST_STORM_VALUE;
	*percent = (u8) num;
}  /* sw_get_broad_storm */

/**
 * sw_dis_broad_storm - disable broadcast storm protection
 * @sw:		The switch instance.
 * @port:	The port index.
 *
 * This routine disables the broadcast storm limit function of the switch.
 */
static void sw_dis_broad_storm(struct ksz_sw *sw, uint port)
{
	port_cfg_broad_storm(sw, port, 0);
}  /* sw_dis_broad_storm */

/**
 * sw_ena_broad_storm - enable broadcast storm protection
 * @sw:		The switch instance.
 * @port:	The port index.
 *
 * This routine enables the broadcast storm limit function of the switch.
 */
static void sw_ena_broad_storm(struct ksz_sw *sw, uint port)
{
	sw_cfg_broad_storm(sw, sw->info->broad_per);
	port_cfg_broad_storm(sw, port, 1);
}  /* sw_ena_broad_storm */

/**
 * sw_init_broad_storm - initialize broadcast storm
 * @sw:		The switch instance.
 *
 * This routine initializes the broadcast storm limit function of the switch.
 */
static void sw_init_broad_storm(struct ksz_sw *sw)
{
	u8 percent;

	sw_get_broad_storm(sw, &percent);
	sw->info->broad_per = percent;
}  /* sw_init_broad_storm */

/**
 * hw_cfg_broad_storm - configure broadcast storm
 * @sw:		The switch instance.
 * @percent:	Broadcast storm threshold in percent of transmit rate.
 *
 * This routine configures the broadcast storm threshold of the switch.
 * It is called by user functions.  The hardware should be acquired first.
 */
static void hw_cfg_broad_storm(struct ksz_sw *sw, u8 percent)
{
	if (percent > 100)
		percent = 100;

	sw_cfg_broad_storm(sw, percent);
	sw_init_broad_storm(sw);
}  /* hw_cfg_broad_storm */

/**
 * sw_setup_broad_storm - setup broadcast storm
 * @sw:		The switch instance.
 *
 * This routine setup the broadcast storm limit function of the switch.
 */
static void sw_setup_broad_storm(struct ksz_sw *sw)
{
	uint n;
	uint port;

	/* Enable switch broadcast storm protection at 10% percent rate. */
	hw_cfg_broad_storm(sw, BROADCAST_STORM_PROTECTION_RATE);
	for (n = 0; n <= sw->mib_port_cnt; n++) {
		port = get_phy_port(sw, n);
		sw_ena_broad_storm(sw, port);
	}
	sw_cfg(sw, REG_SW_CTRL_2, MULTICAST_STORM_DISABLE, 1);
}  /* sw_setup_broad_storm */

/* -------------------------------------------------------------------------- */

/* Rate Control */

/**
 * hw_cfg_rate_ctrl - configure port rate control
 * @sw:		The switch instance.
 * @port:	The port index.
 * @prio:	The priority index to configure.
 * @ctrl:	The flag indicating whether the rate control bit is set or not.
 *
 * This routine configures the priority rate control of the port.
 */
static void hw_cfg_rate_ctrl(struct ksz_sw *sw, uint port, int prio, int ctrl)
{
	int offset;
	u8 data;
	u8 saved;

	offset = REG_PORT_RATE_CTRL_0 - prio;
	port_r8(sw, port, offset, &data);
	saved = data;
	data &= ~RATE_CTRL_ENABLE;
	if (ctrl)
		data |= RATE_CTRL_ENABLE;
	if (data != saved)
		port_w8(sw, port, offset, data);
	sw->info->port_cfg[port].rate_ctrl[prio] = data;
}  /* hw_cfg_rate_ctrl */

/**
 * hw_cfg_rate_ratio - configure port rate ratio
 * @sw:		The switch instance.
 * @port:	The port index.
 * @prio:	The priority index to configure.
 * @ratio:	The rate ratio.
 *
 * This routine configures the priority rate ratio of the port.
 */
static void hw_cfg_rate_ratio(struct ksz_sw *sw, uint port, int prio, u8 ratio)
{
	int offset;
	u8 data;
	u8 saved;

	if (ratio >= RATE_CTRL_ENABLE)
		return;

	offset = REG_PORT_RATE_CTRL_0 - prio;
	port_r8(sw, port, offset, &data);
	saved = data;
	data &= RATE_CTRL_ENABLE;
	data |= ratio;
	if (data != saved)
		port_w8(sw, port, offset, data);
	sw->info->port_cfg[port].rate_ctrl[prio] = data;
}  /* hw_cfg_rate_ratio */

/**
 * hw_get_rate_ctrl - get port rate control
 * @sw:		The switch instance.
 * @port:	The port index.
 * @prio:	The priority index to retrieve.
 *
 * This routine retrieves the priority rate control of the port.
 */
static void hw_get_rate_ctrl(struct ksz_sw *sw, uint port, int prio)
{
	int offset;
	u8 data;

	offset = REG_PORT_RATE_CTRL_0 - prio;
	port_r8(sw, port, offset, &data);
	sw->info->port_cfg[port].rate_ctrl[prio] = data;
}  /* hw_get_rate_ctrl */

/* -------------------------------------------------------------------------- */

/* Rate Limit */

/**
 * hw_cfg_rate_limit - configure port rate limit modes
 * @sw:		The switch instance.
 * @port:	The port index.
 * @mask:	The mask value.
 * @shift:	The shift position.
 * @mode:	The rate limit mode.
 *
 * This helper routine configures the rate limit modes of the port.
 */
static void hw_cfg_rate_limit(struct ksz_sw *sw, uint port, u8 mask, u8 shift,
	u8 mode)
{
	u8 data;
	u8 saved;

	port_r8(sw, port, P_RATE_LIMIT_CTRL, &data);
	saved = data;
	data &= ~(mask << shift);
	data |= mode << shift;
	if (data != saved)
		port_w8(sw, port, P_RATE_LIMIT_CTRL, data);
	sw->info->port_cfg[port].rate_limit = data;
}  /* hw_cfg_rate_limit */

static void hw_cfg_in_port_based(struct ksz_sw *sw, uint port, bool set)
{
	hw_cfg_rate_limit(sw, port, 1, PORT_IN_PORT_BASED_S, set);
}

static void hw_cfg_in_flow_ctrl(struct ksz_sw *sw, uint port, bool set)
{
	hw_cfg_rate_limit(sw, port, 1, PORT_IN_FLOW_CTRL_S, set);
}

/**
 * hw_cfg_cnt_ifg - configure port rate limit count IFG control
 * @sw:		The switch instance.
 * @port:	The port index.
 * @set:	The flag indicating whether the count control is set or not.
 *
 * This routine configures the rate limit count IFG control of the port.
 */
static void hw_cfg_cnt_ifg(struct ksz_sw *sw, uint port, bool set)
{
	hw_cfg_rate_limit(sw, port, 1, PORT_COUNT_IFG_S, set);
}  /* hw_cfg_cnt_ifg */

/**
 * hw_cfg_cnt_pre - configure port rate limit count preamble control
 * @sw:		The switch instance.
 * @port:	The port index.
 * @set:	The flag indicating whether the count control is set or not.
 *
 * This routine configures the rate limit count preamble control of the port.
 */
static void hw_cfg_cnt_pre(struct ksz_sw *sw, uint port, bool set)
{
	hw_cfg_rate_limit(sw, port, 1, PORT_COUNT_PREAMBLE_S, set);
}  /* hw_cfg_cnt_pre */

/**
 * hw_cfg_rx_limit - configure port rate limit mode
 * @sw:		The switch instance.
 * @port:	The port index.
 * @mode:	The rate limit mode.
 *
 * This routine configures the rate limit mode of the port.
 */
static void hw_cfg_rx_limit(struct ksz_sw *sw, uint port, u8 mode)
{
	if (mode > PORT_IN_LIMIT_MODE_M)
		return;

	hw_cfg_rate_limit(sw, port, PORT_IN_LIMIT_MODE_M,
		PORT_IN_LIMIT_MODE_S, mode);
}  /* hw_cfg_rx_limit */

/**
 * hw_get_rate_limit - get port rate limit control
 * @sw:		The switch instance.
 * @port:	The port index.
 *
 * This routine retrieves the rate limit of the port.
 */
static void hw_get_rate_limit(struct ksz_sw *sw, uint port)
{
	u8 data;
	struct ksz_port_cfg *cfg = get_port_cfg(sw, port);

	port_r8(sw, port, P_RATE_LIMIT_CTRL, &data);
	cfg->rate_limit = data;
	cfg->packet_based = (data >> PORT_RATE_PACKET_BASED_S) & 1;
}  /* hw_get_rate_limit */

/* -------------------------------------------------------------------------- */

static uint get_rate_from_val(u8 val)
{
	uint i;

	if (0 == val)
		i = 0;
	else if (val <= 100)
		i = 1000 * val;
	else
		i = 64 * (val - 100);
	return i;
}

static int get_rate_to_val(uint rate)
{
	int i;

	if (rate >= 1000) {
		i = (rate + 500) / 1000;
		if (i > 100)
			i = 100;
	} else if (0 == rate)
		i = 0;
	else {
		i = (rate + 32) / 64;
		if (0 == i)
			i = 1;
		else if (i > 15)
			i = 15;
		i += 100;
	}
	return i;
}

static uint get_packet_from_val(u8 val)
{
	uint i;

	if (0 == val)
		i = 0;
	else if (val <= 100)
		i = 1920 * val;
	else if (101 == val)
		i = 64;
	else
		i = 128 * (val - 101);
	return i;
}

static int get_packet_to_val(uint rate)
{
	int i;

	if (rate >= 1920) {
		i = (rate + 960) / 1920;
		if (i > 100)
			i = 100;
	} else if (0 == rate)
		i = 0;
	else if (rate <= 64)
		i = 101;
	else {
		i = (rate + 64) / 128;
		if (0 == i)
			i = 1;
		else if (i > 14)
			i = 14;
		i += 101;
	}
	return i;
}

/**
 * port_cfg_rate - configure port priority rate
 * @sw:		The switch instance.
 * @port:	The port index.
 * @prio:	The priority index to configure.
 * @offset:	The receive or transmit rate offset.
 * @shift:	The shift position to set the value.
 * @rate:	The rate limit in number of Kbps (or Kpps).
 * @packet:	Packet indication.
 *
 * This helper routine configures the priority rate of the port.
 */
static void port_cfg_rate(struct ksz_sw *sw, uint port, int prio, int offset,
	uint rate, bool packet)
{
	u8 factor;

	if (packet)
		factor = (u8) get_packet_to_val(rate);
	else
		factor = (u8) get_rate_to_val(rate);

	port_w8(sw, port, offset + prio, factor);
}  /* port_cfg_rate */

/**
 * port_get_rate - get port priority rate
 * @sw:		The switch instance.
 * @port:	The port index.
 * @prio:	The priority index to configure.
 * @offset:	The receive or transmit rate offset.
 * @shift:	The shift position to get the value.
 * @rate:	Buffer to store the data rate in number of Kbps (or Kpps).
 * @packet:	Packet indication.
 *
 * This helper routine retrieves the priority rate of the port.
 */
static void port_get_rate(struct ksz_sw *sw, uint port, int prio, int offset,
	uint *rate, bool packet)
{
	u8 data;

	port_r8(sw, port, offset + prio, &data);
	if (packet)
		*rate = get_packet_from_val(data);
	else
		*rate = get_rate_from_val(data);
}  /* port_get_rate */

/**
 * hw_cfg_prio_rate - configure port priority
 * @sw:		The switch instance.
 * @port:	The port index.
 * @prio:	The priority index to configure.
 * @rate:	The rate limit in number of Kbps (or Kpps).
 * @offset:	The receive or transmit rate offset.
 * @result:	Buffer to store the data rate in number of Kbps (or Kpps).
 * @packet:	Packet indication.
 *
 * This helper routine configures the priority rate of the port and retrieves
 * the actual rate number.
 */
static void hw_cfg_prio_rate(struct ksz_sw *sw, uint port, int prio, uint rate,
	int offset, uint *result, bool packet)
{
	port_cfg_rate(sw, port, prio, offset, rate, packet);
	port_get_rate(sw, port, prio, offset, result, packet);
}  /* hw_cfg_prio_rate */

/*
 * THa  2016/02/24
 * The receive rate limit does not take effect until the last priority is also
 * written!  It can be turned off without writing the last priority.  Setting
 * it turns on rate limiting but the hardware seems to use the last value.
 */
static void hw_set_rx_prio(struct ksz_sw *sw, uint port)
{
	u8 data;

	port_r8(sw, port, REG_PORT_IN_RATE_0 + PRIO_QUEUES - 1, &data);
	port_w8(sw, port, REG_PORT_IN_RATE_0 + PRIO_QUEUES - 1, data);
}  /* hw_set_rx_prio */

/**
 * hw_cfg_rx_prio_rate - configure port receive priority
 * @sw:		The switch instance.
 * @port:	The port index.
 * @prio:	The priority index to configure.
 * @rate:	The rate limit in number of Kbps (or Kpps).
 *
 * This routine configures the receive priority rate of the port.
 * It is called by user functions.  The hardware should be acquired first.
 */
static void hw_cfg_rx_prio_rate(struct ksz_sw *sw, uint port, int prio,
	uint rate)
{
	uint *result;
	struct ksz_port_cfg *cfg = get_port_cfg(sw, port);

	if (cfg->packet_based)
		result = &cfg->rx_packet[prio];
	else
		result = &cfg->rx_rate[prio];
	hw_cfg_prio_rate(sw, port, prio, rate,
		REG_PORT_IN_RATE_0,
		result, cfg->packet_based);
}  /* hw_cfg_rx_prio_rate */

/**
 * hw_cfg_tx_prio_rate - configure port transmit priority
 * @sw:		The switch instance.
 * @port:	The port index.
 * @prio:	The priority index to configure.
 * @rate:	The rate limit in number of Kbps (or Kpps).
 *
 * This routine configures the transmit priority rate of the port.
 * It is called by user functions.  The hardware should be acquired first.
 */
static void hw_cfg_tx_prio_rate(struct ksz_sw *sw, uint port, int prio,
	uint rate)
{
	uint *result;
	struct ksz_port_cfg *cfg = get_port_cfg(sw, port);

	if (cfg->packet_based)
		result = &cfg->tx_packet[prio];
	else
		result = &cfg->tx_rate[prio];
	hw_cfg_prio_rate(sw, port, prio, rate,
		REG_PORT_OUT_RATE_0,
		result, cfg->packet_based);
}  /* hw_cfg_tx_prio_rate */

/**
 * sw_chk_rx_prio_rate - check switch rx priority rate
 * @sw:		The switch instance.
 * @port:	The port index.
 *
 * This function checks whether the rx priority rate function of the switch is
 * enabled.
 *
 * Return 0 if not enabled.
 */
static int sw_chk_rx_prio_rate(struct ksz_sw *sw, uint port)
{
	u32 rate_addr;
	u32 in_rate;

	PORT_CTRL_ADDR(port, rate_addr);
	rate_addr += REG_PORT_IN_RATE_0;
	in_rate = sw->reg->r32(sw, rate_addr);
	return in_rate != 0;
}  /* sw_chk_rx_prio_rate */

/**
 * sw_dis_rx_prio_rate - disable switch rx priority rate
 * @sw:		The switch instance.
 * @port:	The port index.
 *
 * This routine disables the rx priority rate function of the switch.
 */
static void sw_dis_rx_prio_rate(struct ksz_sw *sw, uint port)
{
	u32 rate_addr;

	PORT_CTRL_ADDR(port, rate_addr);
	rate_addr += REG_PORT_IN_RATE_0;
	sw->reg->w32(sw, rate_addr, 0);
}  /* sw_dis_rx_prio_rate */

/**
 * sw_ena_rx_prio_rate - enable switch rx priority rate
 * @sw:		The switch instance.
 * @port:	The port index.
 *
 * This routine enables the rx priority rate function of the switch.
 */
static void sw_ena_rx_prio_rate(struct ksz_sw *sw, uint port)
{
	int prio;
	u32 *rate;
	struct ksz_port_cfg *cfg = get_port_cfg(sw, port);

	if (cfg->packet_based)
		rate = cfg->rx_packet;
	else
		rate = cfg->rx_rate;
/*
 * THa  2016/02/24
 * The receive rate limit does not take effect until the last priority is also
 * written!  It can be turned off without writing the last priority.  Setting
 * it turns on rate limiting but the hardware seems to use the last value.
 */
	for (prio = 0; prio < PRIO_QUEUES; prio++, rate++)
		hw_cfg_rx_prio_rate(sw, port, prio, *rate);
}  /* sw_ena_rx_prio_rate */

/**
 * sw_chk_tx_prio_rate - check switch tx priority rate
 * @sw:		The switch instance.
 * @port:	The port index.
 *
 * This function checks whether the tx priority rate function of the switch is
 * enabled.
 *
 * Return 0 if not enabled.
 */
static int sw_chk_tx_prio_rate(struct ksz_sw *sw, uint port)
{
	u32 rate_addr;
	u32 out_rate;

	PORT_CTRL_ADDR(port, rate_addr);
	rate_addr += REG_PORT_OUT_RATE_0;
	if (sw_chk(sw, REG_SW_CTRL_19, SW_OUT_RATE_LIMIT_QUEUE_BASED))
		out_rate = sw->reg->r32(sw, rate_addr);

	/* Only need to check first priority as the others do not matter. */
	else
		out_rate = sw->reg->r8(sw, rate_addr);
	return out_rate != 0;
}  /* sw_chk_tx_prio_rate */

/**
 * sw_dis_tx_prio_rate - disable switch tx priority rate
 * @sw:		The switch instance.
 * @port:	The port index.
 *
 * This routine disables the tx priority rate function of the switch.
 */
static void sw_dis_tx_prio_rate(struct ksz_sw *sw, uint port)
{
	u32 rate_addr;

	PORT_CTRL_ADDR(port, rate_addr);
	rate_addr += REG_PORT_OUT_RATE_0;
	sw->reg->w32(sw, rate_addr, 0);
}  /* sw_dis_tx_prio_rate */

/**
 * sw_ena_tx_prio_rate - enable switch tx priority rate
 * @sw:		The switch instance.
 * @port:	The port index.
 *
 * This routine enables the tx priority rate function of the switch.
 */
static void sw_ena_tx_prio_rate(struct ksz_sw *sw, uint port)
{
	int prio;
	u32 *rate;
	struct ksz_port_cfg *cfg = get_port_cfg(sw, port);

	if (cfg->packet_based)
		rate = cfg->tx_packet;
	else
		rate = cfg->tx_rate;
	for (prio = 0; prio < PRIO_QUEUES; prio++, rate++)
		hw_cfg_tx_prio_rate(sw, port, prio, *rate);
}  /* sw_ena_tx_prio_rate */

static void hw_cfg_rate_packet_based(struct ksz_sw *sw, uint port, bool set)
{
	int prio;
	u32 *rx_rate;
	u32 *tx_rate;
	struct ksz_port_cfg *cfg = get_port_cfg(sw, port);

	cfg->packet_based = set;
	hw_cfg_rate_limit(sw, port, 1, PORT_RATE_PACKET_BASED_S, set);
	if (cfg->packet_based) {
		rx_rate = cfg->rx_packet;
		tx_rate = cfg->tx_packet;
	} else {
		rx_rate = cfg->rx_rate;
		tx_rate = cfg->tx_rate;
	}
	for (prio = 0; prio < PRIO_QUEUES; prio++, rx_rate++, tx_rate++) {

/* See issue above about configuring rx priority rates. */
#if 0
		/* Rate limiting is not enabled. */
		if (!cfg->rx_rate[prio] && !cfg->rx_packet[prio])
			continue;
#endif
		hw_cfg_rx_prio_rate(sw, port, prio, *rx_rate);

		/* Rate limiting is not enabled. */
		if (!cfg->tx_rate[prio] && !cfg->tx_packet[prio])
			continue;
		hw_cfg_tx_prio_rate(sw, port, prio, *tx_rate);
	}
}  /* hw_cfg_rate_packet_based */

/**
 * sw_init_prio_rate - initialize switch prioirty rate
 * @sw:		The switch instance.
 *
 * This routine initializes the priority rate function of the switch.
 */
static void sw_init_prio_rate(struct ksz_sw *sw)
{
	uint n;
	uint offset;
	uint port;
	uint prio;
	struct ksz_port_cfg *cfg;

	for (n = 0; n <= sw->mib_port_cnt; n++) {
		port = get_phy_port(sw, n);
		cfg = get_port_cfg(sw, port);
		hw_get_rate_limit(sw, port);
		for (prio = 0; prio < PRIO_QUEUES; prio++) {
			hw_get_rate_ctrl(sw, port, prio);
			offset = REG_PORT_IN_RATE_0;
			port_get_rate(sw, port, prio, offset,
				&cfg->rx_rate[prio], false);
			port_get_rate(sw, port, prio, offset,
				&cfg->rx_packet[prio], true);
			offset = REG_PORT_OUT_RATE_0;
			port_get_rate(sw, port, prio, offset,
				&cfg->tx_rate[prio], false);
			port_get_rate(sw, port, prio, offset,
				&cfg->tx_packet[prio], true);
		}
	}
}  /* sw_init_prio_rate */

/* -------------------------------------------------------------------------- */

/* Communication */

static inline void port_cfg_back_pressure(struct ksz_sw *sw, uint p, bool set)
{
	port_cfg(sw, p,
		P_STP_CTRL, PORT_BACK_PRESSURE, set);
}

static inline void port_cfg_force_flow_ctrl(struct ksz_sw *sw, uint p, bool set)
{
	port_cfg(sw, p,
		P_STP_CTRL, PORT_FORCE_FLOW_CTRL, set);
}

static inline int port_chk_back_pressure(struct ksz_sw *sw, uint p)
{
	return port_chk(sw, p,
		P_STP_CTRL, PORT_BACK_PRESSURE);
}

static inline int port_chk_force_flow_ctrl(struct ksz_sw *sw, uint p)
{
	return port_chk(sw, p,
		P_STP_CTRL, PORT_FORCE_FLOW_CTRL);
}

/* -------------------------------------------------------------------------- */

/* Spanning Tree */

static inline void port_cfg_dis_learn(struct ksz_sw *sw, uint p, bool set)
{
	port_cfg(sw, p,
		P_STP_CTRL, PORT_LEARN_DISABLE, set);
}

static inline void port_cfg_rx(struct ksz_sw *sw, uint p, bool set)
{
	port_cfg(sw, p,
		P_STP_CTRL, PORT_RX_ENABLE, set);
	if (set)
		sw->rx_ports |= (1 << p);
	else
		sw->rx_ports &= ~(1 << p);
}

static inline void port_cfg_tx(struct ksz_sw *sw, uint p, bool set)
{
	port_cfg(sw, p,
		P_STP_CTRL, PORT_TX_ENABLE, set);
	if (set)
		sw->tx_ports |= (1 << p);
	else
		sw->tx_ports &= ~(1 << p);
}

static inline int port_chk_dis_learn(struct ksz_sw *sw, uint p)
{
	return port_chk(sw, p,
		P_STP_CTRL, PORT_LEARN_DISABLE);
}

static inline int port_chk_rx(struct ksz_sw *sw, uint p)
{
	return port_chk(sw, p,
		P_STP_CTRL, PORT_RX_ENABLE);
}

static inline int port_chk_tx(struct ksz_sw *sw, uint p)
{
	return port_chk(sw, p,
		P_STP_CTRL, PORT_TX_ENABLE);
}

static inline void sw_cfg_fast_aging(struct ksz_sw *sw, bool set)
{
	sw_cfg(sw, REG_SW_CTRL_1, SW_FAST_AGING, set);
}

static void sw_flush_dyn_mac_table(struct ksz_sw *sw, uint port)
{
	uint cnt;
	uint first;
	uint index;
	int learn_disable[TOTAL_PORT_NUM];

	if (port < sw->port_cnt) {
		first = get_log_port(sw, port);
		cnt = first + 1;
	} else {
		first = 0;
		cnt = sw->mib_port_cnt + 1;
	}
	for (index = first; index < cnt; index++) {
		port = get_phy_port(sw, index);
		learn_disable[port] = port_chk_dis_learn(sw, port);
		if (!learn_disable[port])
			port_cfg_dis_learn(sw, port, 1);
	}
	sw_cfg(sw, S_FLUSH_TABLE_CTRL, SW_FLUSH_DYN_MAC_TABLE, 1);
	for (index = first; index < cnt; index++) {
		port = get_phy_port(sw, index);
		if (!learn_disable[port])
			port_cfg_dis_learn(sw, port, 0);
	}
}  /* sw_flush_dyn_mac_table */

/* -------------------------------------------------------------------------- */

/* VLAN */

static inline void port_cfg_ins_tag(struct ksz_sw *sw, uint p, bool insert)
{
	port_cfg(sw, p,
		P_TAG_CTRL, PORT_INSERT_TAG, insert);
}

static inline void port_cfg_rmv_tag(struct ksz_sw *sw, uint p, bool remove)
{
	port_cfg(sw, p,
		P_TAG_CTRL, PORT_REMOVE_TAG, remove);
}

static inline int port_chk_ins_tag(struct ksz_sw *sw, uint p)
{
	return port_chk(sw, p,
		P_TAG_CTRL, PORT_INSERT_TAG);
}

static inline int port_chk_rmv_tag(struct ksz_sw *sw, uint p)
{
	return port_chk(sw, p,
		P_TAG_CTRL, PORT_REMOVE_TAG);
}

static inline void port_cfg_dis_non_vid(struct ksz_sw *sw, uint p, bool set)
{
	port_cfg(sw, p,
		P_STP_CTRL, PORT_DISCARD_NON_VID, set);
}

static inline void port_cfg_drop_tag(struct ksz_sw *sw, uint p, bool set)
{
	port_cfg(sw, p,
		P_DROP_TAG_CTRL, PORT_DROP_TAG, set);
}

static inline void port_cfg_in_filter(struct ksz_sw *sw, uint p, bool set)
{
	port_cfg(sw, p,
		P_STP_CTRL, PORT_INGRESS_FILTER, set);
}

static inline int port_chk_dis_non_vid(struct ksz_sw *sw, uint p)
{
	return port_chk(sw, p,
		P_STP_CTRL, PORT_DISCARD_NON_VID);
}

static inline int port_chk_drop_tag(struct ksz_sw *sw, uint p)
{
	return port_chk(sw, p,
		P_DROP_TAG_CTRL, PORT_DROP_TAG);
}

static inline int port_chk_in_filter(struct ksz_sw *sw, uint p)
{
	return port_chk(sw, p,
		P_STP_CTRL, PORT_INGRESS_FILTER);
}

/* -------------------------------------------------------------------------- */

/* Mirroring */

static inline void port_cfg_mirror_sniffer(struct ksz_sw *sw, uint p, bool set)
{
	port_cfg(sw, p,
		P_MIRROR_CTRL, PORT_MIRROR_SNIFFER, set);
}

static inline void port_cfg_mirror_rx(struct ksz_sw *sw, uint p, bool set)
{
	port_cfg(sw, p,
		P_MIRROR_CTRL, PORT_MIRROR_RX, set);
}

static inline void port_cfg_mirror_tx(struct ksz_sw *sw, uint p, bool set)
{
	port_cfg(sw, p,
		P_MIRROR_CTRL, PORT_MIRROR_TX, set);
}

static inline void sw_cfg_mirror_rx_tx(struct ksz_sw *sw, bool set)
{
	sw_cfg(sw, S_MIRROR_CTRL, SW_MIRROR_RX_TX, set);
}

static inline int port_chk_mirror_sniffer(struct ksz_sw *sw, uint p)
{
	return port_chk(sw, p,
		P_MIRROR_CTRL, PORT_MIRROR_SNIFFER);
}

static inline int port_chk_mirror_rx(struct ksz_sw *sw, uint p)
{
	return port_chk(sw, p,
		P_MIRROR_CTRL, PORT_MIRROR_RX);
}

static inline int port_chk_mirror_tx(struct ksz_sw *sw, uint p)
{
	return port_chk(sw, p,
		P_MIRROR_CTRL, PORT_MIRROR_TX);
}

static inline int sw_chk_mirror_rx_tx(struct ksz_sw *sw)
{
	return sw_chk(sw, S_MIRROR_CTRL, SW_MIRROR_RX_TX);
}

static void sw_setup_mirror(struct ksz_sw *sw)
{
	uint n;
	uint port;

	/*
	 * The mirror sniffer port requires it to be in the port membership
	 * of the receive and transmit ports.
	 * For example, port 3 is the mirror port of traffic between ports 1
	 * and 2.  Port 3 needs only to turn sniffer on; its port membership
	 * can be 0.  Ordinarily the port membership of ports 1 and 2 is 3 for
	 * just commnunicating with eath other.  It has to be set to 7 to pass
	 * the frames to port 3.  Only one of the ports needs to turn on
	 * receive and transmit mirroring.
	 * The mirror receive and transmit mode requires at least two ports to
	 * turn on receive and transmit mirroring.
	 */
	for (n = 0; n <= sw->mib_port_cnt; n++) {
		port = get_phy_port(sw, n);
		port_cfg_mirror_sniffer(sw, port, 0);
		port_cfg_mirror_rx(sw, port, 0);
		port_cfg_mirror_tx(sw, port, 0);
	}
	sw_cfg_mirror_rx_tx(sw, 0);
}

/* -------------------------------------------------------------------------- */

static void sw_cfg_unk_dest(struct ksz_sw *sw, u8 offset, bool set)
{
	u8 data;

	data = sw->reg->r8(sw, offset);
	if (set)
		data |= SW_UNK_FWD_ENABLE;
	else
		data &= ~SW_UNK_FWD_ENABLE;
	sw->reg->w8(sw, offset, data);
}

static int sw_chk_unk_dest(struct ksz_sw *sw, u8 offset)
{
	u8 data;

	data = sw->reg->r8(sw, offset);
	return (data & SW_UNK_FWD_ENABLE) == SW_UNK_FWD_ENABLE;
}

static void sw_cfg_unk_def_port(struct ksz_sw *sw, u8 offset, u8 port, int set)
{
	u8 data;
	u8 bits = 1 << port;

	data = sw->reg->r8(sw, offset);
	if (2 == set) {
		data &= ~SW_UNK_FWD_MAP;
		bits = port & SW_UNK_FWD_MAP;
	}
	if (set)
		data |= bits;
	else
		data &= ~bits;
	sw->reg->w8(sw, offset, data);
}

static int sw_chk_unk_def_port(struct ksz_sw *sw, u8 offset, uint port)
{
	u8 data;
	u8 bit = 1 << port;

	data = sw->reg->r8(sw, offset);
	if (port >= sw->port_cnt)
		return data & SW_UNK_FWD_MAP;
	return (data & bit) == bit;
}

static inline int sw_chk_self_filter(struct ksz_sw *sw)
{
	return sw_chk(sw, REG_SW_UNK_IP_MCAST_CTRL,
		SW_SELF_ADDR_FILTER_ENABLE);
}

static inline void sw_cfg_self_filter(struct ksz_sw *sw, bool set)
{
	sw_cfg(sw, REG_SW_UNK_IP_MCAST_CTRL, SW_SELF_ADDR_FILTER_ENABLE, set);
}

static void sw_cfg_src_filter(struct ksz_sw *sw, bool set)
{
}  /* sw_cfg_src_filter */

static void sw_fwd_unk_vid(struct ksz_sw *sw)
{
	sw->reg->w8(sw, REG_SW_UNK_VID_CTRL, sw->HOST_MASK | SW_UNK_FWD_ENABLE);
}  /* sw_fwd_unk_vid */

/* -------------------------------------------------------------------------- */

/* Priority */

static inline void port_cfg_diffserv(struct ksz_sw *sw, uint p, bool set)
{
	port_cfg(sw, p,
		P_PRIO_CTRL, PORT_DIFFSERV_ENABLE, set);
}

static inline void port_cfg_802_1p(struct ksz_sw *sw, uint p, bool set)
{
	port_cfg(sw, p,
		P_PRIO_CTRL, PORT_802_1P_ENABLE, set);
}

static inline void port_cfg_replace_prio(struct ksz_sw *sw, uint p, bool set)
{
	port_cfg(sw, p,
		P_802_1P_CTRL, PORT_802_1P_REMAPPING, set);
}

static inline int port_chk_diffserv(struct ksz_sw *sw, uint p)
{
	return port_chk(sw, p,
		P_PRIO_CTRL, PORT_DIFFSERV_ENABLE);
}

static inline int port_chk_802_1p(struct ksz_sw *sw, uint p)
{
	return port_chk(sw, p,
		P_PRIO_CTRL, PORT_802_1P_ENABLE);
}

static inline int port_chk_replace_prio(struct ksz_sw *sw, uint p)
{
	return port_chk(sw, p,
		P_802_1P_CTRL, PORT_802_1P_REMAPPING);
}

/* -------------------------------------------------------------------------- */

/**
 * sw_set_tos_prio - program switch TOS priority
 * @sw:		The switch instance.
 * @tos:	ToS value from 6-bit (bit7 ~ bit2) of ToS field, ranging from 0
 *		to 63.
 * @prio:	Priority to be assigned.
 *
 * This routine programs the TOS priority into the switch registers.
 */
static void sw_set_tos_prio(struct ksz_sw *sw, u8 tos, SW_D prio)
{
	SW_W(sw, S_TOS_PRIO_CTRL + tos * SW_SIZE, prio);
}  /* sw_set_tos_prio */

/**
 * sw_dis_diffserv - disable switch DiffServ priority
 * @sw:		The switch instance.
 * @port:	The port index.
 *
 * This routine disables the DiffServ priority function of the switch.
 */
static void sw_dis_diffserv(struct ksz_sw *sw, uint port)
{
	port_cfg_diffserv(sw, port, 0);
}  /* sw_dis_diffserv */

/**
 * sw_ena_diffserv - enable switch DiffServ priority
 * @sw:		The switch instance.
 * @port:	The port index.
 *
 * This routine enables the DiffServ priority function of the switch.
 */
static void sw_ena_diffserv(struct ksz_sw *sw, uint port)
{
	port_cfg_diffserv(sw, port, 1);
}  /* sw_ena_diffserv */

/**
 * hw_cfg_tos_prio - configure TOS priority
 * @sw:		The switch instance.
 * @tos:	ToS value from 6-bit (bit7 ~ bit2) of ToS field, ranging from 0
 *		to 63.
 * @prio:	Priority to be assigned.
 *
 * This routine configures the TOS priority in the hardware.
 * DiffServ Value 0 ~ 63 is mapped to Priority Queue Number 0 ~ 3.
 * It is called by user functions.  The hardware should be acquired first.
 */
static void hw_cfg_tos_prio(struct ksz_sw *sw, u8 tos, SW_D prio)
{
	int shift;
	SW_D data = prio;
	SW_D mask = KS_PRIO_M;

	if (tos >= DIFFSERV_ENTRIES)
		return;

	if (prio >= 0x10)
		mask = 0xff;
	else if (prio > KS_PRIO_M)
		mask = 0xf;
	shift = (tos & (KS_PRIO_IN_REG - 1)) * KS_PRIO_S;
	prio = prio << shift;
	if (prio >> shift != data)
		return;
	mask <<= shift;
	tos /= KS_PRIO_IN_REG;

	sw->info->diffserv[tos] &= ~mask;
	sw->info->diffserv[tos] |= prio;

	sw_set_tos_prio(sw, tos, sw->info->diffserv[tos]);
}  /* hw_cfg_tos_prio */

/* -------------------------------------------------------------------------- */

/**
 * sw_set_802_1p_prio - program switch 802.1p priority
 * @sw:		The switch instance.
 * @prio:	Priority to be assigned.
 *
 * This routine programs the 802.1p priority into the switch register.
 */
static void sw_set_802_1p_prio(struct ksz_sw *sw, u8 tag, SW_D prio)
{
	SW_W(sw, S_802_1P_PRIO_CTRL + tag / SW_SIZE, prio);
}  /* sw_set_802_1p_prio */

/**
 * sw_dis_802_1p - disable switch 802.1p priority
 * @sw:		The switch instance.
 * @port:	The port index.
 *
 * This routine disables the 802.1p priority function of the switch.
 */
static void sw_dis_802_1p(struct ksz_sw *sw, uint port)
{
	port_cfg_802_1p(sw, port, 0);
}  /* sw_dis_802_1p */

/**
 * sw_ena_802_1p - enable switch 802.1p priority
 * @sw:		The switch instance.
 * @port:	The port index.
 *
 * This routine enables the 802.1p priority function of the switch.
 */
static void sw_ena_802_1p(struct ksz_sw *sw, uint port)
{
	port_cfg_802_1p(sw, port, 1);
}  /* sw_ena_802_1p */

/**
 * hw_cfg_802_1p_prio - configure 802.1p priority
 * @sw:		The switch instance.
 * @tag:	The 802.1p tag priority value, ranging from 0 to 7.
 * @prio:	Priority to be assigned.
 *
 * This routine configures the 802.1p priority in the hardware.
 * 802.1p Tag priority value 0 ~ 7 is mapped to Priority Queue Number 0 ~ 3.
 * It is called by user functions.  The hardware should be acquired first.
 */
static void hw_cfg_802_1p_prio(struct ksz_sw *sw, u8 tag, SW_D prio)
{
	int shift;
	SW_D data = prio;
	SW_D mask = KS_PRIO_M;

	if (tag >= PRIO_802_1P_ENTRIES)
		return;

	if (prio >= 0x10)
		mask = 0xff;
	else if (prio > KS_PRIO_M)
		mask = 0xf;
	shift = (tag & (KS_PRIO_IN_REG - 1)) * KS_PRIO_S;
	prio = prio << shift;
	if (prio >> shift != data)
		return;
	mask <<= shift;
	tag /= KS_PRIO_IN_REG;

	sw->info->p_802_1p[tag] &= ~mask;
	sw->info->p_802_1p[tag] |= prio;

	sw_set_802_1p_prio(sw, tag, sw->info->p_802_1p[tag]);
}  /* hw_cfg_802_1p_prio */

/**
 * sw_cfg_replace_null_vid - enable switch null VID replacement
 * @sw:		The switch instance.
 * @set:	The flag to disable or enable.
 *
 * This routine enables the VID to be replaced with port default VID if it is
 * empty.
 */
static void sw_cfg_replace_null_vid(struct ksz_sw *sw, bool set)
{
	sw_cfg(sw, S_REPLACE_VID_CTRL, SW_REPLACE_VID, set);
}  /* sw_cfg_replace_null_vid */

/**
 * sw_cfg_replace_prio - enable switch 802.1p priority re-mapping
 * @sw:		The switch instance.
 * @port:	The port index.
 * @set:	The flag to disable or enable.
 *
 * This routine enables the 802.1p priority re-mapping function of the switch.
 * That allows 802.1p priority field to be replaced with the port's default
 * tag's priority value if the ingress packet's 802.1p priority has a higher
 * priority than port's default tag's priority.
 */
static void sw_cfg_replace_prio(struct ksz_sw *sw, uint port, bool set)
{
	port_cfg_replace_prio(sw, port, set);
}  /* sw_cfg_replace_prio */

/* -------------------------------------------------------------------------- */

/**
 * sw_cfg_port_based - configure switch port based priority
 * @sw:		The switch instance.
 * @port:	The port index.
 * @prio:	The priority to set.
 *
 * This routine configures the port based priority of the switch.
 */
static void sw_cfg_port_based(struct ksz_sw *sw, uint port, u8 prio)
{
	SW_D data;

	if (prio > PORT_BASED_PRIO_M)
		prio = PORT_BASED_PRIO_M;

	port_r(sw, port, P_PRIO_CTRL, &data);
	data &= ~(PORT_BASED_PRIO_M << PORT_BASED_PRIO_S);
	data |= prio << PORT_BASED_PRIO_S;
	port_w(sw, port, P_PRIO_CTRL, data);

	sw->info->port_cfg[port].port_prio = prio;
}  /* sw_cfg_port_based */

/* -------------------------------------------------------------------------- */

static int sw_get_hi_prio_queues(struct ksz_sw *sw)
{
	u8 data;
	int queue;

	data = sw->reg->r8(sw, REG_SWITCH_CTRL_14);
	data >>= SW_PRIO_MAPPING_S;
	data &= SW_PRIO_MAPPING_M;
	switch (data) {
	case SW_PRIO_MAP_3_HI:
		queue = 3;
		break;
	case SW_PRIO_MAP_0_LO:
		queue = 1;
		break;
	case SW_PRIO_MAP_2_HI:
		queue = 2;
		break;
	default:
		queue = 0;
	}
	return queue;
}  /* sw_get_hi_prio_queues */

static void sw_set_hi_prio_queues(struct ksz_sw *sw, int queue)
{
	u8 data;

	data = sw->reg->r8(sw, REG_SWITCH_CTRL_14);
	data &= ~(SW_PRIO_MAPPING_M << SW_PRIO_MAPPING_S);
	switch (queue) {
	case 1:
		queue = SW_PRIO_MAP_0_LO;
		break;
	case 3:
		queue = SW_PRIO_MAP_3_HI;
		break;
	default:
		queue = SW_PRIO_MAP_2_HI;
	}
	queue <<= SW_PRIO_MAPPING_S;
	data |= (u8) queue;
	sw->reg->w8(sw, REG_SWITCH_CTRL_14, data);
}  /* sw_set_hi_prio_queues */

/**
 * port_get_prio_queue - check transmit multiple queues
 * @sw:		The switch instance.
 * @port:	The port index.
 *
 * This function checks number of transmit queues enabled in the port.
 */
static int port_get_prio_queue(struct ksz_sw *sw, uint port)
{
	int queue;
	u8 hi;
	u8 lo;

	port_r(sw, port, REG_PORT_CTRL_0, &lo);
	port_r(sw, port, P_DROP_TAG_CTRL, &hi);
	queue = !!(hi & PORT_QUEUE_SPLIT_H);
	queue <<= 1;
	queue |= !!(lo & PORT_QUEUE_SPLIT_L);
	return 1 << queue;
}  /* port_get_prio_queue */

/**
 * port_set_prio_queue - enable transmit multiple queues
 * @sw:		The switch instance.
 * @port:	The port index.
 * @queue:	Number of queues.
 *
 * This routine enables the transmit multiple queues selection of the switch
 * port.  The port transmit queue is split into two or four priority queues.
 */
static void port_set_prio_queue(struct ksz_sw *sw, uint port, int queue)
{
	u8 hi;
	u8 lo;

	switch (queue) {
	case 4:
	case 3:
		queue = PORT_QUEUE_SPLIT_4;
		break;
	case 2:
		queue = PORT_QUEUE_SPLIT_2;
		break;
	default:
		queue = PORT_QUEUE_SPLIT_1;
	}
	port_r(sw, port, REG_PORT_CTRL_0, &lo);
	port_r(sw, port, P_DROP_TAG_CTRL, &hi);
	lo &= ~PORT_QUEUE_SPLIT_L;
	if (queue & 1)
		lo |= PORT_QUEUE_SPLIT_L;
	hi &= ~PORT_QUEUE_SPLIT_H;
	if (queue & 2)
		hi |= PORT_QUEUE_SPLIT_H;
	port_w(sw, port, REG_PORT_CTRL_0, lo);
	port_w(sw, port, P_DROP_TAG_CTRL, hi);

	/* Default is port based for egress rate limit. */
	if (queue)
		sw_cfg(sw, REG_SW_CTRL_19, SW_OUT_RATE_LIMIT_QUEUE_BASED, 1);
}  /* port_set_prio_queue */

/**
 * sw_init_prio - initialize switch priority
 * @sw:		The switch instance.
 *
 * This routine initializes the switch QoS priority functions.
 */
static void sw_init_prio(struct ksz_sw *sw)
{
	uint n;
	uint port;
	SW_D data;

	sw->reg->r(sw, S_802_1P_PRIO_CTRL, sw->info->p_802_1p,
		PRIO_802_1P_ENTRIES / KS_PRIO_IN_REG);

	sw->reg->r(sw, S_TOS_PRIO_CTRL, sw->info->diffserv,
		DIFFSERV_ENTRIES / KS_PRIO_IN_REG);

	for (n = 0; n <= sw->mib_port_cnt; n++) {
		port = get_phy_port(sw, n);
		port_r(sw, port, P_PRIO_CTRL, &data);
		data &= PORT_BASED_PRIO_M;
		data >>= PORT_BASED_PRIO_S;
		sw->info->port_cfg[port].port_prio = data;
	}
}  /* sw_init_prio */

/**
 * sw_setup_prio - setup switch priority
 * @sw:		The switch instance.
 *
 * This routine setup the switch QoS priority functions.
 */
static void sw_setup_prio(struct ksz_sw *sw)
{
	uint n;
	uint port;

	/* All QoS functions disabled. */
	for (n = 0; n <= sw->mib_port_cnt; n++) {
		port = get_phy_port(sw, n);
		port_set_prio_queue(sw, port, 4);
		sw_dis_diffserv(sw, port);
		sw_cfg_replace_prio(sw, port, 0);
		sw_cfg_port_based(sw, port, sw->info->port_cfg[port].port_prio);

		sw_ena_802_1p(sw, port);
	}
	sw_cfg_replace_null_vid(sw, 0);
}  /* sw_setup_prio */

/* -------------------------------------------------------------------------- */

/**
 * port_cfg_def_vid - configure port default VID
 * @sw:		The switch instance.
 * @port:	The port index.
 * @vid:	The VID value.
 *
 * This routine configures the default VID of the port.
 */
static void port_cfg_def_vid(struct ksz_sw *sw, uint port, u16 vid)
{
	port_w16(sw, port, REG_PORT_CTRL_VID, vid);
}  /* port_cfg_def_vid */

/**
 * port_get_def_vid - get port default VID.
 * @sw:		The switch instance.
 * @port:	The port index.
 * @vid:	Buffer to store the VID.
 *
 * This routine retrieves the default VID of the port.
 */
static void port_get_def_vid(struct ksz_sw *sw, uint port, u16 *vid)
{
	port_r16(sw, port, REG_PORT_CTRL_VID, vid);
}  /* port_get_def_vid */

/**
 * sw_cfg_def_vid - configure switch port default VID
 * @sw:		The switch instance.
 * @port:	The port index.
 * @vid:	The VID value.
 *
 * This routine configures the default VID of the port.
 */
static void sw_cfg_def_vid(struct ksz_sw *sw, uint port, u16 vid)
{
	sw->info->port_cfg[port].vid = vid;
	port_cfg_def_vid(sw, port, vid);
}  /* sw_cfg_def_vid */

/**
 * sw_cfg_port_base_vlan - configure port-based VLAN membership
 * @sw:		The switch instance.
 * @port:	The port index.
 * @member:	The port-based VLAN membership.
 *
 * This routine configures the port-based VLAN membership of the port.
 */
static void sw_cfg_port_base_vlan(struct ksz_sw *sw, uint port, u8 member)
{
	SW_D data;

	port_r(sw, port, P_MIRROR_CTRL, &data);
	data &= ~PORT_VLAN_MEMBERSHIP;
	data |= (member & sw->PORT_MASK);
	port_w(sw, port, P_MIRROR_CTRL, data);

	sw->info->port_cfg[port].member = member;
}  /* sw_cfg_port_base_vlan */

/**
 * sw_vlan_cfg_dis_non_vid - configure discard non VID
 * @sw:		The switch instance.
 * @port:	The port index.
 * @set:	The flag to disable or enable.
 *
 * This routine configures Discard Non VID packets of the switch port.
 * If enabled, the device will discard packets whose VLAN id does not match
 * ingress port-based default VLAN id.
 */
static void sw_vlan_cfg_dis_non_vid(struct ksz_sw *sw, uint port, bool set)
{
	port_cfg_dis_non_vid(sw, port, set);
}  /* sw_vlan_cfg_dis_non_vid */

/**
 * sw_vlan_cfg_drop_tag - configure 802.1q tagged packet drop
 * @sw:		The switch instance.
 * @port:	The port index.
 * @set:	The flag to disable or enable.
 *
 */
static void sw_vlan_cfg_drop_tag(struct ksz_sw *sw, uint port, bool set)
{
	port_cfg_drop_tag(sw, port, set);
}  /* sw_vlan_cfg_drop_tag */

/**
 * sw_vlan_cfg_in_filter - configure ingress VLAN filtering
 * @sw:		The switch instance.
 * @port:	The port index.
 * @set:	The flag to disable or enable.
 *
 * This routine configures Ingress VLAN filtering of the switch port.
 * If enabled, the device will discard packets whose VLAN id membership	in the
 * VLAN table bits [18:16] does not include the ingress port that received this
 * packet.
 */
static void sw_vlan_cfg_in_filter(struct ksz_sw *sw, uint port, bool set)
{
	port_cfg_in_filter(sw, port, set);
}  /* sw_vlan_cfg_in_filter */

/**
 * sw_vlan_cfg_ins_tag - configure 802.1q tag insertion
 * @sw:		The switch instance.
 * @port:	The port index.
 * @set:	The flag to disable or enable.
 *
 * This routine configures 802.1q Tag insertion to the switch port.
 * If enabled, the device will insert 802.1q tag to the transmit packet on this
 * port if received packet is an untagged packet.  The device will not insert
 * 802.1q tag if received packet is tagged packet.
 */
static void sw_vlan_cfg_ins_tag(struct ksz_sw *sw, uint port, bool set)
{
	port_cfg_ins_tag(sw, port, set);
}  /* sw_vlan_cfg_ins_tag */

/**
 * sw_vlan_cfg_rmv_tag - configure 802.1q tag removal
 * @sw:		The switch instance.
 * @port:	The port index.
 * @set:	The flag to disable or enable.
 *
 * This routine configures 802.1q Tag removal to the switch port.
 * If enabled, the device will removed 802.1q tag to the transmit packet on
 * this port if received packet is a tagged packet.  The device will not remove
 * 802.1q tag if received packet is untagged packet.
 */
static void sw_vlan_cfg_rmv_tag(struct ksz_sw *sw, uint port, bool set)
{
	port_cfg_rmv_tag(sw, port, set);
}  /* sw_vlan_cfg_rmv_tag */

static inline int sw_chk_ins_tag(struct ksz_sw *sw)
{
	return sw_chk(sw, REG_SW_CTRL_19, SW_INS_TAG_ENABLE);
}

static inline void sw_cfg_ins_tag(struct ksz_sw *sw, bool set)
{
	sw_cfg(sw, REG_SW_CTRL_19, SW_INS_TAG_ENABLE, set);
}

static int get_ins_shift(int src_port, int dst_port)
{
	int shift;

	if (src_port == dst_port)
		return 0;
	shift = PORT_INS_TAG_FOR_PORT_5_S + dst_port - 3;
	if (src_port > shift)
		shift++;
	return shift;
}

static int sw_chk_ins(struct ksz_sw *sw, int src_port, int dst_port)
{
	int shift;

	shift = get_ins_shift(src_port, dst_port);
	if (!shift)
		return 0;
	--shift;
	return port_chk(sw, src_port, P_INS_SRC_PVID_CTRL, 1 << shift);
}

static void sw_cfg_ins(struct ksz_sw *sw, int src_port, int dst_port, bool set)
{
	int shift;

	shift = get_ins_shift(src_port, dst_port);
	if (!shift)
		return;
	--shift;
	port_cfg(sw, src_port, P_INS_SRC_PVID_CTRL, 1 << shift, set);
}

/**
 * sw_dis_vlan - disable switch VLAN
 * @sw:		The switch instance.
 *
 * This routine disables the VLAN function of the switch.
 */
static void sw_dis_vlan(struct ksz_sw *sw)
{
	sw_cfg(sw, S_MIRROR_CTRL, SW_VLAN_ENABLE, 0);
}  /* sw_dis_vlan */

/**
 * sw_ena_vlan - enable switch VLAN
 * @sw:		The switch instance.
 *
 * This routine enables the VLAN function of the switch.
 */
static void sw_ena_vlan(struct ksz_sw *sw)
{
	/* Enable 802.1q VLAN mode. */
	sw_cfg(sw, REG_SW_CTRL_2, UNICAST_VLAN_BOUNDARY, 1);
	sw_cfg(sw, S_MIRROR_CTRL, SW_VLAN_ENABLE, 1);
}  /* sw_ena_vlan */

/**
 * sw_init_vlan - initialize switch VLAN
 * @sw:		The switch instance.
 *
 * This routine initializes the VLAN function of the switch.
 */
static void sw_init_vlan(struct ksz_sw *sw)
{
	uint n;
	uint port;
	SW_D data;
	struct ksz_port_cfg *cfg;

	for (n = 0; n <= sw->mib_port_cnt; n++) {
		port = get_phy_port(sw, n);
		cfg = get_port_cfg(sw, port);
		port_get_def_vid(sw, port, &cfg->vid);
		port_r(sw, port, P_MIRROR_CTRL, &data);
		data &= PORT_VLAN_MEMBERSHIP;
		cfg->member = data;
		cfg->vid_member = data;

		port_cfg(sw, port, P_INS_SRC_PVID_CTRL,
			(PORT_INS_TAG_FOR_PORT_5 | PORT_INS_TAG_FOR_PORT_4 |
			PORT_INS_TAG_FOR_PORT_3 | PORT_INS_TAG_FOR_PORT_2),
			true);
	}
}  /* sw_init_vlan */

static void inc_mac_addr(u8 *dst, u8 *src, u8 inc)
{
	memcpy(dst, src, ETH_ALEN);
	dst[5] += inc;
	if (dst[5] < src[5])
		dst[4]++;
	if (dst[4] < src[4])
		dst[3]++;
}  /* inc_mac_addr */

/**
 * sw_get_addr - get the switch MAC address.
 * @sw:		The switch instance.
 * @mac_addr:	Buffer to store the MAC address.
 *
 * This function retrieves the MAC address of the switch.
 */
static inline void sw_get_addr(struct ksz_sw *sw, u8 *mac_addr)
{
	sw->reg->r(sw, REG_SW_MAC_ADDR_0, mac_addr, 6);
	memcpy(sw->info->mac_addr, mac_addr, 6);
}  /* sw_get_addr */

/**
 * sw_set_addr - configure switch MAC address
 * @sw:		The switch instance.
 * @mac_addr:	The MAC address.
 *
 * This function configures the MAC address of the switch.
 */
static void sw_set_addr(struct ksz_sw *sw, u8 *mac_addr)
{
	uint n;
	uint p;
	struct ksz_port_info *info;

	for (n = 0; n <= sw->mib_port_cnt; n++) {
		p = get_phy_port(sw, n);
		info = get_port_info(sw, p);
		inc_mac_addr(info->mac_addr, mac_addr, n);
	}
/**
 * THa  2015/07/17
 * Switch does not learn unicast address from port if the source address
 * matches the switch MAC address!  This mostly happens with the host MAC
 * address.
 */
#if 0
	sw->reg->w(sw, REG_SW_MAC_ADDR_0, mac_addr, 6);
#endif
	memcpy(sw->info->mac_addr, mac_addr, 6);
}  /* sw_set_addr */

#ifdef CONFIG_KSZ_MRP
#include "ksz_mrp.c"
#endif

#define STP_ENTRY			0
#define BROADCAST_ENTRY			1
#define BRIDGE_ADDR_ENTRY		2
#define IPV6_ADDR_ENTRY			3
#define DEV_0_ADDR_ENTRY		4
#define DEV_1_ADDR_ENTRY		5

/**
 * sw_set_global_ctrl - set switch global control
 * @sw:		The switch instance.
 *
 * This routine sets the global control of the switch function.
 */
static void sw_set_global_ctrl(struct ksz_sw *sw)
{
	SW_D data;
	struct phy_device *phydev = sw->phy[0];
	struct ksz_port_info *info = &sw->port_info[sw->HOST_PORT];

	data = SW_R(sw, REG_PORT_5_CTRL_6);

	/* Allow slower speed to be used for testing purpose. */
#ifdef USE_10_MBIT_MODE
	phydev->speed = SPEED_10;
	phydev->dev_flags |= 1;
#endif
#ifdef USE_HALF_DUPLEX
	phydev->duplex = DUPLEX_HALF;
	phydev->dev_flags |= 1;
#endif
#ifdef USE_GMII_100_MODE
	if (phydev->speed > SPEED_100)
		phydev->speed = SPEED_100;
	phydev->dev_flags |= 1;
#endif
	data &= ~PORT_INTERFACE_TYPE;
	data &= ~PORT_GMII_MAC_MODE;
	if (phydev->dev_flags & 2)
		data |= PORT_GMII_MAC_MODE;
	switch (phydev->interface) {
	case PHY_INTERFACE_MODE_MII:
		data &= ~PORT_GMII_1GPS_MODE;
		if (phydev->speed > SPEED_100)
			phydev->speed = SPEED_100;
		break;
	case PHY_INTERFACE_MODE_RMII:
		data &= ~PORT_GMII_1GPS_MODE;
		data |= PORT_INTERFACE_RMII;
		if (phydev->speed > SPEED_100)
			phydev->speed = SPEED_100;
		break;
	case PHY_INTERFACE_MODE_GMII:
		data |= PORT_GMII_1GPS_MODE;
		if (phydev->dev_flags & 1) {
			if (SPEED_1000 != phydev->speed)
				data &= ~PORT_GMII_1GPS_MODE;
		}
		if ((data & PORT_GMII_1GPS_MODE) &&
		    phydev->speed < SPEED_1000)
			phydev->speed = SPEED_1000;
		data |= PORT_INTERFACE_GMII;
		break;
	default:
		data &= ~PORT_RGMII_ID_IN_ENABLE;
		data &= ~PORT_RGMII_ID_OUT_ENABLE;
		if (PHY_INTERFACE_MODE_RGMII_ID == phydev->interface ||
		    PHY_INTERFACE_MODE_RGMII_RXID == phydev->interface)
			data |= PORT_RGMII_ID_IN_ENABLE;
		if (PHY_INTERFACE_MODE_RGMII_ID == phydev->interface ||
		    PHY_INTERFACE_MODE_RGMII_TXID == phydev->interface)
			data |= PORT_RGMII_ID_OUT_ENABLE;
		data |= PORT_GMII_1GPS_MODE;
		if (phydev->dev_flags & 1) {
			if (SPEED_1000 != phydev->speed)
				data &= ~PORT_GMII_1GPS_MODE;
		}
		if ((data & PORT_GMII_1GPS_MODE) &&
		    phydev->speed < SPEED_1000)
			phydev->speed = SPEED_1000;
		data |= PORT_INTERFACE_RGMII;
		break;
	}
	info->tx_rate = phydev->speed * TX_RATE_UNIT;
	info->duplex = phydev->duplex + 1;
	SW_W(sw, REG_PORT_5_CTRL_6, data);

	/* Enable switch MII flow control. */
	data = SW_R(sw, S_REPLACE_VID_CTRL);
	data |= SW_FLOW_CTRL;

	if (phydev->dev_flags & 1) {
		if (SPEED_10 == phydev->speed)
			data |= SW_10_MBIT;
		if (DUPLEX_HALF == phydev->duplex) {
			data |= SW_HALF_DUPLEX;
			data |= SW_HALF_DUPLEX_FLOW_CTRL;
		}
	}
	SW_W(sw, S_REPLACE_VID_CTRL, data);

	data = SW_R(sw, S_LINK_AGING_CTRL);
	data |= SW_LINK_AUTO_AGING;
	SW_W(sw, S_LINK_AGING_CTRL, data);

	data = SW_R(sw, REG_SW_CTRL_1);

	/* Enable aggressive back off algorithm in half duplex mode. */
	data |= SW_AGGR_BACKOFF;

	/* Enable automatic fast aging when link changed detected. */
	data |= SW_AGING_ENABLE;

	if (sw->overrides & FAST_AGING)
		data |= SW_FAST_AGING;
	else
		data &= ~SW_FAST_AGING;

	SW_W(sw, REG_SW_CTRL_1, data);

	data = SW_R(sw, REG_SW_CTRL_2);

	/* Make sure unicast VLAN boundary is set as default. */
	if (sw->dev_count > 1)
		data |= UNICAST_VLAN_BOUNDARY;

	/* Enable no excessive collision drop. */
	data |= NO_EXC_COLLISION_DROP;
	SW_W(sw, REG_SW_CTRL_2, data);
}  /* sw_set_global_ctrl */

/* -------------------------------------------------------------------------- */

/**
 * port_set_stp_state - configure port spanning tree state
 * @sw:		The switch instance.
 * @port:	The port index.
 * @state:	The spanning tree state.
 *
 * This routine configures the spanning tree state of the port.
 */
static void port_set_stp_state(struct ksz_sw *sw, uint port, int state)
{
	SW_D data;
	struct ksz_port_cfg *port_cfg;
	int member = -1;

	port_cfg = get_port_cfg(sw, port);
	port_r(sw, port, P_STP_CTRL, &data);
	switch (state) {
	case STP_STATE_DISABLED:
		data &= ~(PORT_TX_ENABLE | PORT_RX_ENABLE);
		data |= PORT_LEARN_DISABLE;
		if (port < SWITCH_PORT_NUM)
			member = 0;
		break;
	case STP_STATE_LISTENING:
/*
 * No need to turn on transmit because of port direct mode.
 * Turning on receive is required if static MAC table is not setup.
 */
		data &= ~PORT_TX_ENABLE;
		data |= PORT_RX_ENABLE;
		data |= PORT_LEARN_DISABLE;
		if (port < SWITCH_PORT_NUM &&
		    STP_STATE_DISABLED == port_cfg->stp_state)
			member = sw->HOST_MASK | port_cfg->vid_member;
		break;
	case STP_STATE_LEARNING:
		data &= ~PORT_TX_ENABLE;
		data |= PORT_RX_ENABLE;
		data &= ~PORT_LEARN_DISABLE;
		break;
	case STP_STATE_FORWARDING:
		data |= (PORT_TX_ENABLE | PORT_RX_ENABLE);
		data &= ~PORT_LEARN_DISABLE;

#ifdef CONFIG_KSZ_STP
		/* Actual port membership setting is done in another RSTP
		 * processing routine.
		 */
		if (sw->stp == 1 || (sw->stp && (sw->stp & (1 << port)))) {
			struct ksz_stp_info *info = &sw->info->rstp;

			if (info->br.bridgeEnabled)
				break;
		}
#endif
		if (((sw->features & (SW_VLAN_DEV | USE_FEWER_PORTS)) ||
		    sw->dev_offset) && port != sw->HOST_PORT)
			/* Set port-base vlan membership with host port. */
			member = sw->HOST_MASK | port_cfg->vid_member;
		break;
	case STP_STATE_BLOCKED:
/*
 * Need to setup static MAC table with override to keep receiving BPDU
 * messages.  See sw_setup_stp routine.
 */
		data &= ~(PORT_TX_ENABLE | PORT_RX_ENABLE);
		data |= PORT_LEARN_DISABLE;
		if (port < SWITCH_PORT_NUM &&
		    STP_STATE_DISABLED == port_cfg->stp_state)
			member = sw->HOST_MASK | port_cfg->vid_member;
		break;
	case STP_STATE_SIMPLE:
		data |= (PORT_TX_ENABLE | PORT_RX_ENABLE);
		data |= PORT_LEARN_DISABLE;
		if (port < SWITCH_PORT_NUM)
			/* Set port-base vlan membership with host port. */
			member = sw->HOST_MASK | port_cfg->vid_member;
		break;
	}
	port_w(sw, port, P_STP_CTRL, data);
	port_cfg->stp_state = state;
	if (data & PORT_RX_ENABLE)
		sw->rx_ports |= (1 << port);
	else
		sw->rx_ports &= ~(1 << port);
	if (data & PORT_TX_ENABLE)
		sw->tx_ports |= (1 << port);
	else
		sw->tx_ports &= ~(1 << port);

	/* Port membership may share register with STP state. */
	if (member >= 0)
		sw_cfg_port_base_vlan(sw, port, (u8) member);
}  /* port_set_stp_state */

/**
 * sw_clr_sta_mac_table - clear static MAC table
 * @sw:		The switch instance.
 *
 * This routine clears the static MAC table.
 */
static void sw_clr_sta_mac_table(struct ksz_sw *sw)
{
	struct ksz_mac_table entry;
	int i;

	memset(&entry, 0, sizeof(struct ksz_mac_table));
	sw->ops->release(sw);
	for (i = 0; i < STATIC_MAC_TABLE_ENTRIES; i++)
		sw_w_sta_mac_table(sw, i, &entry);
	sw->ops->acquire(sw);
}  /* sw_clr_sta_mac_table */

/**
 * sw_setup_stp - setup switch spanning tree support
 * @sw:		The switch instance.
 *
 * This routine initializes the spanning tree support of the switch.
 */
static void sw_setup_stp(struct ksz_sw *sw)
{
	struct ksz_mac_table entry;

	entry.addr[0] = 0x01;
	entry.addr[1] = 0x80;
	entry.addr[2] = 0xC2;
	entry.addr[3] = 0x00;
	entry.addr[4] = 0x00;
	entry.addr[5] = 0x00;
	entry.ports = sw->HOST_MASK;
	entry.use_fid = 0;
	entry.override = 1;
	entry.valid = 1;
	sw->ops->release(sw);
	sw_w_sta_mac_table(sw, STP_ENTRY, &entry);
	sw->ops->acquire(sw);
}  /* sw_setup_stp */

#ifdef CONFIG_KSZ_STP
static void bridge_change(struct ksz_sw *sw)
{
	uint n;
	uint port;
	u8 member;
	struct ksz_port_cfg *cfg;
	struct ksz_sw_info *info = sw->info;

	for (n = 1; n <= sw->mib_port_cnt; n++) {
		port = get_phy_port(sw, n);
		cfg = get_port_cfg(sw, port);
		if (STP_STATE_FORWARDING == cfg->stp_state)
			member = sw->HOST_MASK | info->member[0];
		else if (STP_STATE_DISABLED == cfg->stp_state)
			member = 0;
		else
			member = sw->HOST_MASK | (1 << port);
		if (member != cfg->member)
			sw_cfg_port_base_vlan(sw, port, member);
	}
}  /* bridge_change */
#endif

#define MAX_SW_LEN			1500

static void sw_setup_msg(struct sw_dev_info *info, void *data, int len,
	void (*func)(void *data, void *param), void *param)
{
	struct ksz_sw *sw = info->sw;
	int in_intr = in_interrupt();

	if (len > MAX_SW_LEN)
		len = MAX_SW_LEN;
	if (!in_intr)
		mutex_lock(&info->lock);
	memcpy(sw->msg_buf, data, len);
	if (func)
		func(sw->msg_buf, param);
	len += 2;
	if (info->read_len + len <= info->read_max) {
		u16 *msg_len = (u16 *) &info->read_buf[info->read_len];

		*msg_len = len;
		msg_len++;
		memcpy(msg_len, sw->msg_buf, len - 2);
		info->read_len += len;
	}
	if (!in_intr)
		mutex_unlock(&info->lock);
	wake_up_interruptible(&info->wait_msg);
}  /* sw_setup_msg */

#ifdef CONFIG_KSZ_STP
#include "ksz_stp.c"
#endif
#ifdef CONFIG_KSZ_DLR
#include "ksz_dlr.c"
#endif

/*
 * Link detection routines
 */

static inline void dbp_link(struct ksz_port *port, struct ksz_sw *sw,
	int change)
{
	struct ksz_port_info *info;
	uint i;
	uint n;
	uint p;

	for (i = 0, n = port->first_port; i < port->port_cnt; i++, n++) {
		p = get_phy_port(sw, n);
		info = get_port_info(sw, p);
		if (media_connected == info->state) {
			if (change & (1 << i)) {
				printk(KERN_INFO "link %d-%d: %d, %d\n",
					sw->id, i + port->first_port,
					info->tx_rate / TX_RATE_UNIT,
					info->duplex);
			}
		} else {
			if (change & (1 << i))
				printk(KERN_INFO "link %d-%d disconnected\n",
					sw->id, i + port->first_port);
		}
	}
}

static SW_D port_advertised_flow_ctrl(struct ksz_port *port, SW_D ctrl)
{
	ctrl &= ~PORT_AUTO_NEG_SYM_PAUSE;
	switch (port->flow_ctrl) {
	case PHY_FLOW_CTRL:
		ctrl |= PORT_AUTO_NEG_SYM_PAUSE;
		break;
	/* Not supported. */
	case PHY_TX_ONLY:
	case PHY_RX_ONLY:
	default:
		break;
	}
	return ctrl;
}  /* port_advertised_flow_ctrl */

static u8 sw_determine_flow_ctrl(struct ksz_sw *sw, struct ksz_port *port,
	u8 local, u8 remote)
{
	int rx;
	int tx;
	u8 flow = 0;

	if (sw->overrides & PAUSE_FLOW_CTRL)
		return flow;

	rx = tx = 0;
	if (port->force_link)
		rx = tx = 1;
	if (remote & PORT_REMOTE_SYM_PAUSE) {
		if (local & PORT_AUTO_NEG_SYM_PAUSE)
			rx = tx = 1;
	}
	if (rx)
		flow |= 0x01;
	if (tx)
		flow |= 0x02;
#ifdef DBG_LINK
	printk(KERN_INFO "pause: %d, %d; %02x %02x\n",
		rx, tx, local, remote);
#endif
	return flow;
}  /* sw_determine_flow_ctrl */

static int port_chk_force_link(struct ksz_sw *sw, uint p, SW_D local,
	SW_D remote, SW_D status)
{
#define PORT_REMOTE_STATUS				\
	(PORT_REMOTE_100BTX_FD | PORT_REMOTE_100BTX |	\
	PORT_REMOTE_10BT_FD | PORT_REMOTE_10BT)

	SW_D data;
	static SW_D saved_ctrl;
	static SW_D saved_status;
	static int test_stage;

	port_r(sw, p, P_FORCE_CTRL, &data);
	if (data & PORT_AUTO_NEG_DISABLE)
		return 0;
	if ((local & (PORT_REMOTE_100BTX_FD | PORT_REMOTE_100BTX)) !=
	    (PORT_REMOTE_100BTX_FD | PORT_REMOTE_100BTX) &&
	    (local & (PORT_REMOTE_10BT_FD | PORT_REMOTE_10BT)) !=
	    (PORT_REMOTE_10BT_FD | PORT_REMOTE_10BT))
		return 0;
	if (!(remote & PORT_REMOTE_SYM_PAUSE) &&
	    (remote & PORT_REMOTE_STATUS) != PORT_REMOTE_STATUS) {
		if (saved_ctrl) {
			if ((status & PORT_STAT_FULL_DUPLEX) !=
			    (saved_status & PORT_STAT_FULL_DUPLEX)) {
				printk(KERN_INFO
					"%d-%d: duplex is defaulted to %s\n",
					sw->id, p,
					(saved_ctrl & PORT_FORCE_FULL_DUPLEX) ?
					"full" : "half");
			}
			if (data != saved_ctrl) {
				port_w(sw, p, P_FORCE_CTRL, saved_ctrl);
				port_r(sw, p, P_NEG_RESTART_CTRL, &data);
				data |= PORT_AUTO_NEG_RESTART;
				port_w(sw, p, P_NEG_RESTART_CTRL, data);
				test_stage = 2;
			} else
				test_stage = 0;
			saved_ctrl = 0;
			if (test_stage)
				return 1;
		} else if (!test_stage) {
			saved_ctrl = data;
			saved_status = status;
			if (status & PORT_STAT_FULL_DUPLEX)
				data &= ~PORT_FORCE_FULL_DUPLEX;
			else
				data |= PORT_FORCE_FULL_DUPLEX;
			port_w(sw, p, P_FORCE_CTRL, data);
			port_r(sw, p, P_NEG_RESTART_CTRL, &data);
			data |= PORT_AUTO_NEG_RESTART;
			port_w(sw, p, P_NEG_RESTART_CTRL, data);
			test_stage = 1;
			return 1;
		}
		test_stage = 0;
	}
	return 0;
}  /* port_chk_force_link */

/**
 * port_get_link_speed - get current link status
 * @port:	The port instance.
 *
 * This routine reads PHY registers to determine the current link status of the
 * switch ports.
 */
static int port_get_link_speed(struct ksz_port *port)
{
	struct ksz_port_info *info;
	struct ksz_port_info *linked = NULL;
	struct ksz_port_state *state;
	struct ksz_sw *sw = port->sw;
	SW_D data;
	SW_D status;
	SW_D link;
	SW_D local;
	SW_D remote;
	uint i;
	uint n;
	uint p;
	int change = 0;

	/*
	 * Only check port which has interrupts triggered.
	 * If no interrupt poll all the ports with PHY.
	 */
	if (!sw->phy_intr)
		sw->phy_intr = sw->PORT_MASK;
	for (i = 0, n = port->first_port; i < port->port_cnt; i++, n++) {
		p = get_phy_port(sw, n);
		info = get_port_info(sw, p);
		if (!(sw->phy_intr & (1 << p))) {
			if (!linked && p != sw->HOST_PORT &&
			    info->state == media_connected)
				linked = info;
			continue;
		}
		sw->phy_intr &= ~(1 << p);

		state = &sw->port_state[p];
		port_r(sw, p, P_LOCAL_CTRL, &local);
		port_r(sw, p, P_REMOTE_STATUS, &remote);
		port_r(sw, p, P_SPEED_STATUS, &status);
		port_r(sw, p, P_LINK_STATUS, &data);

		/*
		 * The partner capability register is updated but the
		 * auto-negotiation is not completed yet.
		 */
		link = data & (PORT_AUTO_NEG_COMPLETE | PORT_STAT_LINK_GOOD);
		link |= status &
			(PORT_STAT_SPEED_100MBIT | PORT_STAT_FULL_DUPLEX);

		if (data & PORT_STAT_LINK_GOOD) {

			/* Remember the first linked port. */
			if (!linked)
				linked = info;
		}

		/* No change to status. */
		if (local == info->advertised && link == info->link)
			continue;

#ifdef DBG_LINK
		printk(KERN_INFO
			"%d=advertised: %02X-%02X; partner: %02X-%02X"
			"; link: %02X-%02X\n", p,
			local, info->advertised, remote, info->partner,
			link, info->link);
#endif
		if (data & PORT_STAT_LINK_GOOD) {
			if (port_chk_force_link(sw, p, local, remote, status)) {
				if (linked == info)
					linked = NULL;
				continue;
			}
			info->tx_rate = 10 * TX_RATE_UNIT;
			if (status & PORT_STAT_SPEED_100MBIT)
				info->tx_rate = 100 * TX_RATE_UNIT;

			info->duplex = 1;
			if (status & PORT_STAT_FULL_DUPLEX)
				info->duplex = 2;

#ifdef DBG_LINK
			printk(KERN_INFO "flow_ctrl: "SW_SIZE_STR"\n", status &
				(PORT_RX_FLOW_CTRL | PORT_TX_FLOW_CTRL));
#endif
			if (media_connected != info->state) {
				info->flow_ctrl = sw_determine_flow_ctrl(sw,
					port, local, remote);
				if (status & PORT_RX_FLOW_CTRL)
					info->flow_ctrl |= 0x10;
				if (status & PORT_TX_FLOW_CTRL)
					info->flow_ctrl |= 0x20;
				if (sw->info)
					port_cfg_back_pressure(sw, p,
						(1 == info->duplex));
				change |= 1 << i;
			} else if (link != info->link)
				change |= 1 << i;
			info->state = media_connected;
		} else {
			if (media_disconnected != info->state) {
				change |= 1 << i;

				/* Indicate the link just goes down. */
				state->link_down = 1;
			}
			info->state = media_disconnected;
		}
		info->report = true;
		info->advertised = local;
		info->partner = remote;
		info->link = link;
		state->state = info->state;
	}

	if (linked && media_disconnected == port->linked->state)
		port->linked = linked;

#ifdef DBG_LINK
	if (change)
		dbp_link(port, sw, change);
#endif
	if (change)
		schedule_work(&port->link_update);
	return change;
}  /* port_get_link_speed */

/**
 * port_set_link_speed - set port speed
 * @port:	The port instance.
 *
 * This routine sets the link speed of the switch ports.
 */
static void port_set_link_speed(struct ksz_port *port)
{
	struct ksz_sw *sw = port->sw;
	struct ksz_port_info *info;
	SW_D adv;
	SW_D cfg;
	SW_D data;
	SW_D local;
	SW_D status;
	uint i;
	uint n;
	uint p;

	for (i = 0, n = port->first_port; i < port->port_cnt; i++, n++) {
		p = get_phy_port(sw, n);
		info = get_port_info(sw, p);
		if (info->fiber)
			continue;

		info->own_flow_ctrl = port->flow_ctrl;
		info->own_duplex = port->duplex;
		info->own_speed = port->speed;

		port_r(sw, p, P_FORCE_CTRL, &data);
		port_r(sw, p, P_LOCAL_CTRL, &local);
		port_r(sw, p, P_LINK_STATUS, &status);

		adv = 0;
		cfg = 0;
		if (status & PORT_STAT_LINK_GOOD) {
			cfg = data;
			adv = local;
		}

		data &= ~PORT_AUTO_NEG_DISABLE;
		local = port_advertised_flow_ctrl(port, local);

		local |= PORT_AUTO_NEG_100BTX_FD | PORT_AUTO_NEG_100BTX |
			PORT_AUTO_NEG_10BT_FD | PORT_AUTO_NEG_10BT;

		/* Check if manual configuration is specified by the user. */
		if (port->speed || port->duplex) {
			if (10 == port->speed)
				local &= ~(PORT_AUTO_NEG_100BTX_FD |
					PORT_AUTO_NEG_100BTX);
			else if (100 == port->speed)
				local &= ~(PORT_AUTO_NEG_10BT_FD |
					PORT_AUTO_NEG_10BT);
			if (1 == port->duplex)
				local &= ~(PORT_AUTO_NEG_100BTX_FD |
					PORT_AUTO_NEG_10BT_FD);
			else if (2 == port->duplex)
				local &= ~(PORT_AUTO_NEG_100BTX |
					PORT_AUTO_NEG_10BT);
		}
		if (data != cfg || local != adv) {
			port_w(sw, p, P_FORCE_CTRL, data);
			port_w(sw, p, P_LOCAL_CTRL, local);
			port_r(sw, p, P_NEG_RESTART_CTRL, &data);
			data |= PORT_AUTO_NEG_RESTART;
			port_w(sw, p, P_NEG_RESTART_CTRL, data);

			/* Link is going down. */
			sw->port_state[p].state = media_disconnected;
		}
	}
}  /* port_set_link_speed */

/**
 * port_force_link_speed - force port speed
 * @port:	The port instance.
 *
 * This routine forces the link speed of the switch ports.
 */
static void port_force_link_speed(struct ksz_port *port)
{
	struct ksz_sw *sw = port->sw;
	struct ksz_port_info *info;
	SW_D data;
	uint i;
	uint n;
	uint p;

	for (i = 0, n = port->first_port; i < port->port_cnt; i++, n++) {
		p = get_phy_port(sw, n);
		info = get_port_info(sw, p);
		info->own_flow_ctrl = port->flow_ctrl;
		info->own_duplex = port->duplex;
		info->own_speed = port->speed;

		port_r(sw, p, P_FORCE_CTRL, &data);
		data |= PORT_AUTO_NEG_DISABLE;
		if (10 == port->speed)
			data &= ~PORT_FORCE_100_MBIT;
		else if (100 == port->speed)
			data |= PORT_FORCE_100_MBIT;
		if (1 == port->duplex)
			data &= ~PORT_FORCE_FULL_DUPLEX;
		else if (2 == port->duplex)
			data |= PORT_FORCE_FULL_DUPLEX;
		port_w(sw, p, P_FORCE_CTRL, data);
	}
}  /* port_force_link_speed */

/**
 * sw_enable - enable the switch
 * @sw:		The switch instance.
 *
 */
static void sw_enable(struct ksz_sw *sw)
{
	uint n;
	uint port;
	bool fewer;
	struct ksz_port_cfg *cfg;
	struct ksz_port_info *info;
	int state = STP_STATE_FORWARDING;

	if (sw->features & DSA_SUPPORT)
		state = STP_STATE_SIMPLE;

	/* Manually change default membership when not all ports are used. */
	fewer = false;
	for (port = 0; port < sw->port_cnt; port++) {
		info = get_port_info(sw, port);
		if (info->log_m) {
			cfg = get_port_cfg(sw, port);
			cfg->vid_member = sw->PORT_MASK;
		} else {
			fewer = true;
			port_set_stp_state(sw, port, STP_STATE_DISABLED);
		}
	}
dbg_msg(" fewer: %d %d\n", fewer, sw->eth_cnt);
	if (fewer)
		sw_cfg_port_base_vlan(sw, sw->HOST_PORT, sw->PORT_MASK);
	if ((sw->dev_count > 1 && !sw->dev_offset) ||
	    (sw->features & (STP_SUPPORT | DSA_SUPPORT))) {
		u8 member;

		for (n = 1; n <= sw->mib_port_cnt; n++) {
			port = get_phy_port(sw, n);
			member = (1 << port);
			if (sw->features & SW_VLAN_DEV) {
				struct ksz_dev_map *map;
				int q;

				for (q = 0; q < sw->eth_cnt; q++) {
					map = &sw->eth_maps[q];
					if (map->first <= n &&
					    n <= map->first + map->cnt - 1) {
						member = map->mask;
						break;
					}
				}
			}
			cfg = get_port_cfg(sw, port);
			cfg->vid_member = member;
		}
	} else if (1 == sw->eth_cnt) {
		u8 member;

		for (n = 1; n <= sw->mib_port_cnt; n++) {
			port = get_phy_port(sw, n);
			member = 0;
			if (sw->eth_maps[0].mask & (1 << port))
				member = sw->eth_maps[0].mask;
			cfg = get_port_cfg(sw, port);
			cfg->vid_member = member;
		}
	}
	for (n = 1; n <= sw->mib_port_cnt; n++) {
		port = get_phy_port(sw, n);
		if (sw->dev_count > 1 ||
		    (sw->eth_maps[0].mask &&
		    !(sw->eth_maps[0].mask & (1 << port))))
			port_set_stp_state(sw, port, STP_STATE_DISABLED);
		else if ((sw->eth_maps[0].mask & (1 << port)) &&
			 (sw->eth_maps[0].proto & HSR_HW))
			port_set_stp_state(sw, port, STP_STATE_SIMPLE);
		else
			port_set_stp_state(sw, port, state);
	}
	if (sw->dev_count > 1 && !sw->dev_offset && sw->eth_cnt < 2)
		port_set_stp_state(sw, sw->HOST_PORT, STP_STATE_SIMPLE);
	else
		port_set_stp_state(sw, sw->HOST_PORT, state);

	/*
	 * There may be some entries in the dynamic MAC table before the
	 * the learning is turned off.  Once the entries are in the table the
	 * switch may keep updating them even learning is off.
	 */
	if (sw->dev_count > 1)
		sw_flush_dyn_mac_table(sw, TOTAL_PORT_NUM);
}  /* sw_enable */

/**
 * sw_init - initialize the switch
 * @sw:		The switch instance.
 *
 * This routine initializes the hardware switch engine for default operation.
 */
static void sw_init(struct ksz_sw *sw)
{
	memset(sw->tx_pad, 0, 60);
	sw->tx_start = 0;
	sw_init_broad_storm(sw);

	sw_init_prio(sw);

	sw_init_prio_rate(sw);

	sw_init_vlan(sw);

	sw_init_acl(sw);

	if (sw_chk(sw, REG_SW_CTRL_1,
			SW_TX_FLOW_CTRL_DISABLE | SW_RX_FLOW_CTRL_DISABLE))
		sw->overrides |= PAUSE_FLOW_CTRL;
}  /* sw_init */

/**
 * sw_setup - setup the switch
 * @sw:		The switch instance.
 *
 * This routine setup the hardware switch engine for default operation.
 */
static void sw_setup(struct ksz_sw *sw)
{
	uint n;
	uint port;

	sw_set_global_ctrl(sw);
	for (n = 1; n <= sw->mib_port_cnt; n++) {
		SW_D data;

		port = get_phy_port(sw, n);
		port_cfg_back_pressure(sw, port, 1);

		/*
		 * Switch actually cannot do auto-negotiation with old 10Mbit
		 * hub.
		 */
		port_r(sw, port, P_FORCE_CTRL, &data);
		if (sw->port_info[port].fiber) {
			port_cfg_force_flow_ctrl(sw, port, 1);
			data |= PORT_AUTO_NEG_DISABLE;
			data |= PORT_FORCE_FULL_DUPLEX;
		} else {
			port_cfg_force_flow_ctrl(sw, port, 0);
			data &= ~PORT_FORCE_FULL_DUPLEX;
		}
		port_w(sw, port, P_FORCE_CTRL, data);
	}

	sw_setup_broad_storm(sw);

	sw_setup_prio(sw);

	sw_setup_mirror(sw);

	sw->info->multi_sys = MULTI_MAC_TABLE_ENTRIES;
	sw->info->multi_net = SWITCH_MAC_TABLE_ENTRIES;
	if (sw->features & STP_SUPPORT) {
		sw_setup_stp(sw);
	}
#ifdef CONFIG_KSZ_DLR
	if (sw->features & DLR_HW)
		sw_setup_dlr(sw);
#endif
}  /* sw_setup */

static void sw_reset_acl_all(struct ksz_sw *sw)
{
	uint i;
	uint n;

	for (n = 0; n <= sw->mib_port_cnt; n++) {
		i = get_phy_port(sw, n);
		sw->info->port_cfg[i].acl_byte_enable = ACL_BYTE_ENABLE;
		sw_w_ext_table(sw, TABLE_ACL, i + 1,
			REG_PORT_ACL_BYTE_EN_MSB, ACL_BYTE_EN_MSB_M);
		sw_w_ext_table(sw, TABLE_ACL, i + 1,
			REG_PORT_ACL_BYTE_EN_LSB, 0xFF);
	}
	sw_reset_acl_hw(sw);
}  /* sw_reset_acl_all */

static inline void sw_reset(struct ksz_sw *sw)
{
	sw->reg->w8(sw, REG_POWER_MANAGEMENT_1,
		SW_SOFTWARE_POWER_DOWN << SW_POWER_MANAGEMENT_MODE_S);
	sw->reg->w8(sw, REG_POWER_MANAGEMENT_1, 0);

	sw_reset_acl_all(sw);
}  /* sw_reset */

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

/* -------------------------------------------------------------------------- */

#ifdef KSZSW_REGS_SIZE
static struct ksz_sw *get_sw_data(struct device *d)
{
	struct sw_priv *hw_priv = dev_get_drvdata(d);

	return &hw_priv->sw;
}

static ssize_t kszsw_registers_read(struct file *filp, struct kobject *kobj,
	struct bin_attribute *bin_attr, char *buf, loff_t off, size_t count)
{
	size_t i;
	SW_D reg;
	struct device *dev;
	struct ksz_sw *sw;

	if (unlikely(off > KSZSW_REGS_SIZE))
		return 0;

	if ((off + count) > KSZSW_REGS_SIZE)
		count = KSZSW_REGS_SIZE - off;

	if (unlikely(!count))
		return count;

	dev = container_of(kobj, struct device, kobj);
	sw = get_sw_data(dev);

	reg = off;
	sw->ops->acquire(sw);
	i = sw->reg->get(sw, reg, count, buf);
	sw->ops->release(sw);
	return i;
}

static ssize_t kszsw_registers_write(struct file *filp, struct kobject *kobj,
	struct bin_attribute *bin_attr, char *buf, loff_t off, size_t count)
{
	size_t i;
	SW_D reg;
	struct device *dev;
	struct ksz_sw *sw;

	if (unlikely(off >= KSZSW_REGS_SIZE))
		return -EFBIG;

	if ((off + count) > KSZSW_REGS_SIZE)
		count = KSZSW_REGS_SIZE - off;

	if (unlikely(!count))
		return count;

	dev = container_of(kobj, struct device, kobj);
	sw = get_sw_data(dev);

	reg = off;
	sw->ops->acquire(sw);
	i = sw->reg->set(sw, reg, count, buf);
	sw->ops->release(sw);
	return i;
}

static struct bin_attribute kszsw_registers_attr = {
	.attr = {
		.name	= "registers",
		.mode	= S_IRUSR | S_IWUSR,
	},
	.size	= KSZSW_REGS_SIZE,
	.read	= kszsw_registers_read,
	.write	= kszsw_registers_write,
};
#endif

static int sw_reg_get(struct ksz_sw *sw, u32 reg, size_t count, char *buf)
{
	size_t i;
	SW_D *addr;

	addr = (SW_D *) buf;
	for (i = 0; i < count; i += SW_SIZE, reg += SW_SIZE, addr++) {
		*addr = 0;
		if (check_sw_reg_range(reg))
			*addr = SW_R(sw, reg);
	}
	return i;
}

static int sw_reg_set(struct ksz_sw *sw, u32 reg, size_t count, char *buf)
{
	size_t i;
	SW_D *addr;

	addr = (SW_D *) buf;
	for (i = 0; i < count; i += SW_SIZE, reg += SW_SIZE, addr++) {
		if (check_sw_reg_range(reg))
			SW_W(sw, reg, *addr);
	}
	return i;
}

#ifdef CONFIG_KSZ_MRP
static void sw_set_mrp(struct work_struct *work)
{
	struct delayed_work *dwork = to_delayed_work(work);
	struct ksz_sw *sw = container_of(dwork, struct ksz_sw, set_mrp);

	if (!netif_carrier_ok(sw->main_dev)) {
		schedule_delayed_work(&sw->set_mrp, msecs_to_jiffies(500));
		return;
	}

	mrp_start(&sw->mrp);
}  /* sw_set_mrp */
#endif

/* -------------------------------------------------------------------------- */

/*
 * Microchip LinkMD routines
 */

enum {
	CABLE_UNKNOWN,
	CABLE_GOOD,
	CABLE_CROSSED,
	CABLE_REVERSED,
	CABLE_CROSSED_REVERSED,
	CABLE_OPEN,
	CABLE_SHORT
};

#define STATUS_FULL_DUPLEX		0x01
#define STATUS_CROSSOVER		0x02
#define STATUS_REVERSED			0x04

#define LINK_10MBPS_FULL		0x00000001
#define LINK_10MBPS_HALF		0x00000002
#define LINK_100MBPS_FULL		0x00000004
#define LINK_100MBPS_HALF		0x00000008
#define LINK_1GBPS_FULL			0x00000010
#define LINK_1GBPS_HALF			0x00000020
#define LINK_10GBPS_FULL		0x00000040
#define LINK_10GBPS_HALF		0x00000080
#define LINK_SYM_PAUSE			0x00000100
#define LINK_ASYM_PAUSE			0x00000200

#define LINK_AUTO_MDIX			0x00010000
#define LINK_MDIX			0x00020000
#define LINK_AUTO_POLARITY		0x00040000

#define CABLE_LEN_MAXIMUM		15000
#define CABLE_LEN_MULTIPLIER		40

#define PHY_RESET_TIMEOUT		10

/**
 * sw_get_link_md - get LinkMD status
 * @sw:		The switch instance.
 * @port:	The port index.
 *
 * This routine is used to get the LinkMD status.
 */
static void sw_get_link_md(struct ksz_sw *sw, uint port)
{
	SW_D crossover;
	SW_D data;
	SW_D link;
	u16 len;
	int i;
	int timeout;
	struct ksz_port_info *port_info = get_port_info(sw, port);

	if (port_info->fiber)
		return;
	port_r(sw, port, P_SPEED_STATUS, &data);
	port_r(sw, port, P_LINK_STATUS, &link);
	port_info->status[0] = CABLE_UNKNOWN;
	if (link & PORT_STAT_LINK_GOOD) {
		int stat = 0;

		port_info->status[0] = CABLE_GOOD;
		port_info->length[0] = 1;
		port_info->status[1] = CABLE_GOOD;
		port_info->length[1] = 1;
		port_info->status[2] = CABLE_GOOD;
		port_info->length[2] = 1;

		if (link & PORT_MDIX_STATUS)
			stat |= STATUS_CROSSOVER;
		if (data & PORT_REVERSED_POLARITY)
			stat |= STATUS_REVERSED;
		if ((stat & (STATUS_CROSSOVER | STATUS_REVERSED)) ==
				(STATUS_CROSSOVER | STATUS_REVERSED))
			port_info->status[0] = CABLE_CROSSED_REVERSED;
		else if ((stat & STATUS_CROSSOVER) == STATUS_CROSSOVER)
			port_info->status[0] = CABLE_CROSSED;
		else if ((stat & STATUS_REVERSED) == STATUS_REVERSED)
			port_info->status[0] = CABLE_REVERSED;
		return;
	}

#if 0
	sw_w_ext_table(sw, TABLE_LINK_MD, 0, 0x4D, 0x80);
#endif

	port_r(sw, port, P_NEG_RESTART_CTRL, &data);
	crossover = data;

	for (i = 1; i <= 2; i++) {
		data = crossover;

		/* Disable auto MDIX. */
		data |= PORT_AUTO_MDIX_DISABLE;
		if (0 == i)
			data &= ~PORT_FORCE_MDIX;
		else
			data |= PORT_FORCE_MDIX;

		port_w(sw, port, P_NEG_RESTART_CTRL, data);

		/* Start cable diagnostic test. */
		port_r(sw, port, REG_PORT_LINK_MD_CTRL, &data);
		data |= PORT_START_CABLE_DIAG;
		port_w(sw, port, REG_PORT_LINK_MD_CTRL, data);
		timeout = PHY_RESET_TIMEOUT;
		do {
			if (!--timeout)
				break;
			delay_milli(10);
			port_r(sw, port, REG_PORT_LINK_MD_CTRL, &data);
		} while ((data & PORT_START_CABLE_DIAG));

		port_info->length[i] = 0;
		port_info->status[i] = CABLE_UNKNOWN;

		if (!(data & PORT_START_CABLE_DIAG)) {
			port_r8(sw, port, REG_PORT_LINK_MD_RESULT, &link);
			len = data & PORT_CABLE_FAULT_COUNTER_H;
			len <<= 16;
			len |= link;
			len *= CABLE_LEN_MULTIPLIER;
			len /= 100;
			port_info->length[i] = len;
			if (data & PORT_CABLE_10M_SHORT)
				port_info->length[i] = 1;
			data >>= PORT_CABLE_DIAG_RESULT_S;
			data &= PORT_CABLE_DIAG_RESULT_M;
			switch (data) {
			case PORT_CABLE_STAT_NORMAL:
				port_info->status[i] = CABLE_GOOD;
				port_info->length[i] = 1;
				break;
			case PORT_CABLE_STAT_OPEN:
				port_info->status[i] = CABLE_OPEN;
				break;
			case PORT_CABLE_STAT_SHORT:
				port_info->status[i] = CABLE_SHORT;
				break;
			}
		}
	}

	crossover |= PORT_AUTO_NEG_RESTART;
	port_w(sw, port, P_NEG_RESTART_CTRL, crossover);

	port_info->length[0] = port_info->length[1];
	port_info->status[0] = port_info->status[1];
	for (i = 2; i < 3; i++) {
		if (CABLE_GOOD == port_info->status[0]) {
			if (port_info->status[i] != CABLE_GOOD) {
				port_info->status[0] = port_info->status[i];
				port_info->length[0] = port_info->length[i];
				break;
			}
		}
	}
}  /* sw_get_link_md */

/* -------------------------------------------------------------------------- */

static void get_sw_mib_counters(struct ksz_sw *sw, int first, int cnt,
	u64 *counter)
{
	int i;
	int mib;
	uint n;
	uint p;
	struct ksz_port_mib *port_mib;

	memset(counter, 0, sizeof(u64) * TOTAL_SWITCH_COUNTER_NUM);
	for (i = 0, n = first; i < cnt; i++, n++) {
		p = get_phy_port(sw, n);
		port_mib = get_port_mib(sw, p);
		for (mib = port_mib->mib_start; mib < sw->mib_cnt; mib++)
			counter[mib] += port_mib->counter[mib];
	}
}

#define MIB_RX_HI_PRIO			0x00
#define MIB_RX_UNDERSIZE		0x01
#define MIB_RX_FRAGMENT			0x02
#define MIB_RX_OVERSIZE			0x03
#define MIB_RX_JABBER			0x04
#define MIB_RX_SYMBOL_ERR		0x05
#define MIB_RX_CRC_ERR			0x06
#define MIB_RX_ALIGNMENT_ERR		0x07
#define MIB_RX_CTRL_8808		0x08
#define MIB_RX_PAUSE			0x09
#define MIB_RX_BROADCAST		0x0A
#define MIB_RX_MULTICAST		0x0B
#define MIB_RX_UNICAST			0x0C
#define MIB_RX_OCTET_64			0x0D
#define MIB_RX_OCTET_65_127		0x0E
#define MIB_RX_OCTET_128_255		0x0F
#define MIB_RX_OCTET_256_511		0x10
#define MIB_RX_OCTET_512_1023		0x11
#define MIB_RX_OCTET_1024_1522		0x12
#define MIB_RX_OCTET_1523_2000		0x13
#define MIB_RX_OCTET_2001		0x14
#define MIB_TX_HI_PRIO			0x15
#define MIB_TX_LATE_COLLISION		0x16
#define MIB_TX_PAUSE			0x17
#define MIB_TX_BROADCAST		0x18
#define MIB_TX_MULTICAST		0x19
#define MIB_TX_UNICAST			0x1A
#define MIB_TX_DEFERRED			0x1B
#define MIB_TX_TOTAL_COLLISION		0x1C
#define MIB_TX_EXCESS_COLLISION		0x1D
#define MIB_TX_SINGLE_COLLISION		0x1E
#define MIB_TX_MULTI_COLLISION		0x1F

#define MIB_RX_TOTAL			0x20
#define MIB_TX_TOTAL			0x21
#define MIB_RX_DROPS			0x22
#define MIB_TX_DROPS			0x23

static struct {
	char string[20];
} mib_names[TOTAL_SWITCH_COUNTER_NUM] = {
	{ "rx_hi        " },
	{ "rx_undersize" },
	{ "rx_fragments" },
	{ "rx_oversize" },
	{ "rx_jabbers" },
	{ "rx_symbol_err" },
	{ "rx_crc_err" },
	{ "rx_align_err" },
	{ "rx_mac_ctrl" },
	{ "rx_pause" },
	{ "rx_bcast" },
	{ "rx_mcast" },
	{ "rx_ucast" },
	{ "rx_64_or_less" },
	{ "rx_65_127" },
	{ "rx_128_255" },
	{ "rx_256_511" },
	{ "rx_512_1023" },
	{ "rx_1024_1522" },
	{ "rx_1523_2000" },
	{ "rx_2001     " },

	{ "tx_hi        " },
	{ "tx_late_col" },
	{ "tx_pause" },
	{ "tx_bcast" },
	{ "tx_mcast" },
	{ "tx_ucast" },
	{ "tx_deferred" },
	{ "tx_total_col" },
	{ "tx_exc_col" },
	{ "tx_single_col" },
	{ "tx_mult_col" },

	{ "rx_total" },
	{ "tx_total" },
	{ "rx_discards" },
	{ "tx_discards" },
};

static struct {
	int rx;
	int tx;
} mib_display[TOTAL_SWITCH_COUNTER_NUM / 2] = {
	{ MIB_RX_TOTAL, MIB_TX_TOTAL },
	{ MIB_RX_HI_PRIO, MIB_TX_HI_PRIO },
	{ MIB_RX_PAUSE, MIB_TX_PAUSE },
	{ MIB_RX_BROADCAST, MIB_TX_BROADCAST },
	{ MIB_RX_MULTICAST, MIB_TX_MULTICAST },
	{ MIB_RX_UNICAST, MIB_TX_UNICAST },
	{ MIB_RX_DROPS, MIB_TX_DROPS },
	{ MIB_RX_OCTET_64, MIB_RX_OCTET_65_127 },
	{ MIB_RX_OCTET_128_255, MIB_RX_OCTET_256_511 },
	{ MIB_RX_OCTET_512_1023, MIB_RX_OCTET_1024_1522 },
	{ MIB_RX_OCTET_1523_2000, MIB_RX_OCTET_2001 },
	{ MIB_RX_UNDERSIZE, MIB_RX_OVERSIZE },
	{ MIB_RX_FRAGMENT, MIB_RX_JABBER },
	{ MIB_RX_SYMBOL_ERR, MIB_RX_CRC_ERR },
	{ MIB_RX_ALIGNMENT_ERR, MIB_RX_CTRL_8808 },
	{ MIB_TX_LATE_COLLISION, MIB_TX_DEFERRED },
	{ MIB_TX_TOTAL_COLLISION, MIB_TX_EXCESS_COLLISION },
	{ MIB_TX_SINGLE_COLLISION, MIB_TX_MULTI_COLLISION },
};

static int display_sw_mib_counters(struct ksz_sw *sw, int first, int cnt,
	char *buf)
{
	int mib;
	int n;
	int len = 0;
	u64 counter[TOTAL_SWITCH_COUNTER_NUM];

	get_sw_mib_counters(sw, first, cnt, counter);
	for (mib = 0; mib < TOTAL_SWITCH_COUNTER_NUM / 2; mib++) {
		int rx = mib_display[mib].rx;
		int tx = mib_display[mib].tx;
		if (buf)
			len += sprintf(buf + len,
				"%s\t= %-20llu\t%s\t= %-20llu\n",
				mib_names[rx].string,
				counter[rx],
				mib_names[tx].string,
				counter[tx]);
		else
			printk(KERN_INFO "%s\t= %-20llu\t%s\t= %-20llu\n",
				mib_names[rx].string,
				counter[rx],
				mib_names[tx].string,
				counter[tx]);
	}
	for (n = 0, mib = first; n < cnt; n++, mib++) {
		int j;
		uint p = get_phy_port(sw, mib);
		struct ksz_port_mib *port_mib = get_port_mib(sw, p);

		for (j = 0; j < 2; j++) {
			if (port_mib->rate[j].peak) {
				u32 num;
				u32 frac;

				num = port_mib->rate[j].peak / 10;
				frac = port_mib->rate[j].peak % 10;
				if (buf)
					len += sprintf(buf + len,
						"%d:%d=%u.%u\n", mib, j,
						num, frac);
				else
					printk(KERN_INFO
						"%d:%d=%u.%u\n", mib, j,
						num, frac);
				port_mib->rate[j].peak = 0;
			}
		}
	}
	return len;
}  /* display_sw_mib_counters */

/* -------------------------------------------------------------------------- */

static ssize_t display_sw_info(int cnt, char *buf, ssize_t len)
{
	len += sprintf(buf + len, "duplex:\t\t");
	len += sprintf(buf + len, "0 for auto; ");
	len += sprintf(buf + len,
		"set to 1 for half-duplex; 2, full-duplex\n");
	len += sprintf(buf + len, "speed:\t\t");
	len += sprintf(buf + len,
		"0 for auto; set to 10 or 100\n");
	len += sprintf(buf + len, "force:\t\t");
	len += sprintf(buf + len,
		"set to 1 to force link to specific speed setting\n");
	len += sprintf(buf + len, "flow_ctrl:\t");
	len += sprintf(buf + len,
		"set to 0 to disable flow control\n");
	len += sprintf(buf + len, "mib:\t\t");
	len += sprintf(buf + len,
		"display the MIB table\n");
	printk(KERN_INFO "%s", buf);
	len = 0;

	if (TOTAL_PORT_NUM != cnt)
		return len;

	len += sprintf(buf + len, "\ndynamic_table:\t");
	len += sprintf(buf + len,
		"display the switch's dynamic MAC table\n");
	len += sprintf(buf + len, "static_table:\t");
	len += sprintf(buf + len,
		"display the switch's static MAC table\n");
	len += sprintf(buf + len, "vlan_table:\t");
	len += sprintf(buf + len,
		"display the switch's VLAN table\n");

	len += sprintf(buf + len, "\naging:\t\t");
	len += sprintf(buf + len,
		"disable/enable aging\n");
	len += sprintf(buf + len, "fast_aging:\t");
	len += sprintf(buf + len,
		"disable/enable fast aging\n");
	len += sprintf(buf + len, "link_aging:\t");
	len += sprintf(buf + len,
		"disable/enable link change auto aging\n");

	len += sprintf(buf + len, "\nbcast_per:\t");
	len += sprintf(buf + len,
		"set broadcast storm percentage\n");
	len += sprintf(buf + len, "mcast_storm:\t");
	len += sprintf(buf + len,
		"disable multicast storm protection\n");
	len += sprintf(buf + len, "diffserv_map:\t");
	len += sprintf(buf + len,
		"set DiffServ value.  Use \"decimal=hexadecimal\" format\n");
	len += sprintf(buf + len, "p_802_1p_map:\t");
	len += sprintf(buf + len,
		"set 802.1p value.  Use \"decimal=hexadecimal\" format\n");
	printk(KERN_INFO "%s", buf);
	len = 0;

	len += sprintf(buf + len, "\nvlan:\t\t");
	len += sprintf(buf + len,
		"disable/enable 802.1Q VLAN\n");
	len += sprintf(buf + len, "null_vid:\t");
	len += sprintf(buf + len,
		"set to 1 to replace null vid\n");
	len += sprintf(buf + len, "macaddr:\t");
	len += sprintf(buf + len,
		"set switch MAC address\n");
	len += sprintf(buf + len, "mirror_mode:\t");
	len += sprintf(buf + len,
		"set to 1 to use mirror rx AND tx mode\n");
	len += sprintf(buf + len, "tail_tag:\t");
	len += sprintf(buf + len,
		"disable/enable tail tagging\n");

	len += sprintf(buf + len, "\nigmp_snoop:\t");
	len += sprintf(buf + len,
		"disable/enable IGMP snooping\n");
	len += sprintf(buf + len, "ipv6_mld_snoop:\t");
	len += sprintf(buf + len,
		"disable/enable IPv6 MLD snooping\n");
	len += sprintf(buf + len, "ipv6_mld_option:");
	len += sprintf(buf + len,
		"disable/enable IPv6 MLD option snooping\n");

	len += sprintf(buf + len, "\naggr_backoff:\t");
	len += sprintf(buf + len,
		"disable/enable aggressive backoff in half-duplex mode\n");
	len += sprintf(buf + len, "no_exc_drop:\t");
	len += sprintf(buf + len,
		"disable/enable no excessive collision drop\n");
	len += sprintf(buf + len, "buf_reserve:\t");
	len += sprintf(buf + len,
		"disable/enable buffer reserve\n");
	printk(KERN_INFO "%s", buf);
	len = 0;

	len += sprintf(buf + len, "\nhuge_packet:\t");
	len += sprintf(buf + len,
		"disable/enable huge packet support\n");
	len += sprintf(buf + len, "legal_packet:\t");
	len += sprintf(buf + len,
		"disable/enable legal packet\n");
	len += sprintf(buf + len, "length_check:\t");
	len += sprintf(buf + len,
		"disable/enable legal packet length check\n");

	len += sprintf(buf + len, "\nback_pressure:\t");
	len += sprintf(buf + len,
		"set back pressure mode\n");
	len += sprintf(buf + len, "sw_flow_ctrl:\t");
	len += sprintf(buf + len,
		"disable/enable switch host port flow control\n");
	len += sprintf(buf + len, "sw_half_duplex:\t");
	len += sprintf(buf + len,
		"disable/enable switch host port half-duplex mode\n");
#ifdef SW_10_MBIT
	len += sprintf(buf + len, "sw_10_mbit:\t");
	len += sprintf(buf + len,
		"disable/enable switch host port 10Mbit mode\n");
#endif
	len += sprintf(buf + len, "rx_flow_ctrl:\t");
	len += sprintf(buf + len,
		"disable/enable receive flow control\n");
	len += sprintf(buf + len, "tx_flow_ctrl:\t");
	len += sprintf(buf + len,
		"disable/enable transmit flow control\n");
	len += sprintf(buf + len, "fair_flow_ctrl:\t");
	len += sprintf(buf + len,
		"disable/enable fair flow control mode\n");
	printk(KERN_INFO "%s", buf);
	len = 0;

	len += sprintf(buf + len, "vlan_bound:\t");
	len += sprintf(buf + len,
		"disable/enable unicast VLAN boundary\n");
	len += sprintf(buf + len, "fw_unk_dest:\t");
	len += sprintf(buf + len,
		"disable/enable unknown destination address forwarding\n");

	len += sprintf(buf + len, "\nins_tag_0_1:\t");
	len += sprintf(buf + len,
		"set to 1 to insert tag from port 1 to 2\n");
	len += sprintf(buf + len, "ins_tag_0_2:\t");
	len += sprintf(buf + len,
		"set to 1 to insert tag from port 1 to 3\n");
	len += sprintf(buf + len, "ins_tag_1_0:\t");
	len += sprintf(buf + len,
		"set to 1 to insert tag from port 2 to 1\n");
	len += sprintf(buf + len, "ins_tag_1_2:\t");
	len += sprintf(buf + len,
		"set to 1 to insert tag from port 2 to 3\n");
	len += sprintf(buf + len, "ins_tag_2_0:\t");
	len += sprintf(buf + len,
		"set to 1 to insert tag from port 3 to 1\n");
	len += sprintf(buf + len, "ins_tag_2_1:\t");
	len += sprintf(buf + len,
		"set to 1 to insert tag from port 3 to 2\n");

	len += sprintf(buf + len, "\npass_all:\t");
	len += sprintf(buf + len,
		"set to 1 to pass all frames for debugging\n");
	len += sprintf(buf + len, "pass_pause:\t");
	len += sprintf(buf + len,
		"set to 1 to pass PAUSE frames for debugging\n");
	printk(KERN_INFO "%s", buf);
	len = 0;

	len += sprintf(buf + len, "\nswitch port settings:\n");
	len += sprintf(buf + len, "duplex:\t\t");
	len += sprintf(buf + len,
		"display the port's duplex setting\n");
	len += sprintf(buf + len, "speed:\t\t");
	len += sprintf(buf + len,
		"display the port's link speed\n");
	len += sprintf(buf + len, "linkmd:\t\t");
	len += sprintf(buf + len,
		"write to start LinkMD test.  read for result\n");
	len += sprintf(buf + len, "mib:\t\t");
	len += sprintf(buf + len,
		"display the port's MIB table\n");
	printk(KERN_INFO "%s", buf);
	len = 0;

	len += sprintf(buf + len, "vid:\t\t");
	len += sprintf(buf + len,
		"set default VID value\n");
	len += sprintf(buf + len, "member:\t\t");
	len += sprintf(buf + len,
		"set VLAN membership\n");

	len += sprintf(buf + len, "bcast_storm:\t");
	len += sprintf(buf + len,
		"disable/enable broadcast storm protection\n");
	len += sprintf(buf + len, "diffserv:\t");
	len += sprintf(buf + len,
		"disable/enable DiffServ priority\n");
	len += sprintf(buf + len, "p_802_1p:\t");
	len += sprintf(buf + len,
		"disable/enable 802.1p priority\n");

	len += sprintf(buf + len, "port_based:\t");
	len += sprintf(buf + len,
		"disable/enable port-based priority\n");
	printk(KERN_INFO "%s", buf);
	len = 0;

	len += sprintf(buf + len, "prio_queue:\t");
	len += sprintf(buf + len,
		"disable/enable priority queue\n");
	len += sprintf(buf + len, "tx_p0_ctrl:\t");
	len += sprintf(buf + len,
		"set priority queue 0 control\n");
	len += sprintf(buf + len, "tx_p1_ctrl:\t");
	len += sprintf(buf + len,
		"set priority queue 1 control\n");
	len += sprintf(buf + len, "tx_p2_ctrl:\t");
	len += sprintf(buf + len,
		"set priority queue 2 control\n");
	len += sprintf(buf + len, "tx_p3_ctrl:\t");
	len += sprintf(buf + len,
		"set priority queue 3 control\n");
	len += sprintf(buf + len, "tx_p0_ratio:\t");
	len += sprintf(buf + len,
		"set priority queue 0 ratio\n");
	len += sprintf(buf + len, "tx_p1_ratio:\t");
	len += sprintf(buf + len,
		"set priority queue 1 ratio\n");
	len += sprintf(buf + len, "tx_p2_ratio:\t");
	len += sprintf(buf + len,
		"set priority queue 2 ratio\n");
	len += sprintf(buf + len, "tx_p3_ratio:\t");
	len += sprintf(buf + len,
		"set priority queue 3 ratio\n");
	len += sprintf(buf + len, "prio_rate:\t");
	len += sprintf(buf + len,
		"disable/enable priority queue rate limiting\n");
	len += sprintf(buf + len, "rx_limit:\t");
	len += sprintf(buf + len,
		"set rx rate limiting mode\n");
	len += sprintf(buf + len, "cnt_ifg:\t");
	len += sprintf(buf + len,
		"set to 1 to count IPG\n");
	len += sprintf(buf + len, "cnt_pre:\t");
	len += sprintf(buf + len,
		"set to 1 to count preamble\n");
	len += sprintf(buf + len, "rx_p0_rate:\t");
	len += sprintf(buf + len,
		"set rx priority queue 0 rate in 64Kbps unit\n");
	len += sprintf(buf + len, "rx_p1_rate:\t");
	len += sprintf(buf + len,
		"set rx priority queue 1 rate in 64Kbps unit\n");
	len += sprintf(buf + len, "rx_p2_rate:\t");
	len += sprintf(buf + len,
		"set rx priority queue 2 rate in 64Kbps unit\n");
	len += sprintf(buf + len, "rx_p3_rate:\t");
	len += sprintf(buf + len,
		"set rx priority queue 3 rate in 64Kbps unit\n");
	len += sprintf(buf + len, "tx_p0_rate:\t");
	len += sprintf(buf + len,
		"set tx priority queue 0 rate in 64Kbps unit\n");
	len += sprintf(buf + len, "tx_p1_rate:\t");
	len += sprintf(buf + len,
		"set tx priority queue 1 rate in 64Kbps unit\n");
	len += sprintf(buf + len, "tx_p2_rate:\t");
	len += sprintf(buf + len,
		"set tx priority queue 2 rate in 64Kbps unit\n");
	len += sprintf(buf + len, "tx_p3_rate:\t");
	len += sprintf(buf + len,
		"set tx priority queue 3 rate in 64Kbps unit\n");
	printk(KERN_INFO "%s", buf);
	len = 0;

	len += sprintf(buf + len, "rx:\t\t");
	len += sprintf(buf + len,
		"disable/enable rx\n");
	len += sprintf(buf + len, "tx:\t\t");
	len += sprintf(buf + len,
		"disable/enable tx\n");
	len += sprintf(buf + len, "learn:\t\t");
	len += sprintf(buf + len,
		"disable/enable learning\n");

	len += sprintf(buf + len, "mirror_port:\t");
	len += sprintf(buf + len,
		"disable/enable mirror port\n");
	len += sprintf(buf + len, "mirror_rx:\t");
	len += sprintf(buf + len,
		"disable/enable mirror receive\n");
	len += sprintf(buf + len, "mirror_tx:\t");
	len += sprintf(buf + len,
		"disable/enable mirror transmit\n");
	printk(KERN_INFO "%s", buf);
	len = 0;

	len += sprintf(buf + len, "\nnon_vid:\t");
	len += sprintf(buf + len,
		"set to 1 to discard non-VID packets\n");
	len += sprintf(buf + len, "ingress:\t");
	len += sprintf(buf + len,
		"disable/enable ingress VLAN filtering\n");
	len += sprintf(buf + len, "ins_tag:\t");
	len += sprintf(buf + len,
		"disable/enable insert VLAN tag feature\n");
	len += sprintf(buf + len, "rmv_tag:\t");
	len += sprintf(buf + len,
		"disable/enable remove VLAN tag feature\n");
	len += sprintf(buf + len, "drop_tagged:\t");
	len += sprintf(buf + len,
		"disable/enable drop tagged packet feature\n");
	len += sprintf(buf + len, "replace_prio:\t");
	len += sprintf(buf + len,
		"disable/enable replace 802.1p priority feature\n");
	len += sprintf(buf + len, "back_pressure:\t");
	len += sprintf(buf + len,
		"disable/enable back pressure in half-duplex mode\n");
	len += sprintf(buf + len, "force_flow_ctrl:");
	len += sprintf(buf + len,
		"set to 1 to force flow control\n");
	len += sprintf(buf + len, "fw_unk_dest:\t");
	len += sprintf(buf + len,
		"set to 1 to forward unknown destination address packets\n");
	len += sprintf(buf + len, "fw_inv_vid:\t");
	len += sprintf(buf + len,
		"set to 1 to forward invalid VID packets\n");
	printk(KERN_INFO "%s", buf);
	len = 0;

	len += sprintf(buf + len, "\nstatic MAC table:\n");
	len += sprintf(buf + len, "addr:\t\t");
	len += sprintf(buf + len,
		"set MAC address\n");
	len += sprintf(buf + len, "ports:\t\t");
	len += sprintf(buf + len,
		"set destination ports\n");
	len += sprintf(buf + len, "override:\t");
	len += sprintf(buf + len,
		"set override bit\n");
	len += sprintf(buf + len, "use_fid:\t");
	len += sprintf(buf + len,
		"set use FID bit\n");
	len += sprintf(buf + len, "fid:\t\t");
	len += sprintf(buf + len,
		"set FID\n");
	len += sprintf(buf + len, "valid:\t\t");
	len += sprintf(buf + len,
		"set valid bit and write to table\n");
	len += sprintf(buf + len, "\nVLAN table:\n");
	len += sprintf(buf + len, "vid:\t\t");
	len += sprintf(buf + len,
		"set VID\n");
	len += sprintf(buf + len, "fid:\t\t");
	len += sprintf(buf + len,
		"set FID\n");
	len += sprintf(buf + len, "member:\t\t");
	len += sprintf(buf + len,
		"set membership\n");
	len += sprintf(buf + len, "valid:\t\t");
	len += sprintf(buf + len,
		"set valid bit and write to table\n");
	printk(KERN_INFO "%s", buf);
	len = 0;

	return len;
}  /* display_sw_info */

static ssize_t sysfs_sw_read(struct ksz_sw *sw, int proc_num,
	struct ksz_port *port, ssize_t len, char *buf)
{
	int i;
	int j;
	u16 map;
	struct ksz_sw_info *info = sw->info;

	switch (proc_num) {
	case PROC_SW_INFO:
		len = display_sw_info(TOTAL_PORT_NUM, buf, len);
		break;
	case PROC_SW_VERSION:
		len += sprintf(buf + len, "%s  %s\n",
			SW_DRV_VERSION, SW_DRV_RELDATE);
		break;
	case PROC_SET_SW_DUPLEX:
		if (!port)
			break;
		len += sprintf(buf + len, "%u; ", port->duplex);
		if (media_connected == port->linked->state) {
			if (1 == port->linked->duplex)
				len += sprintf(buf + len, "half-duplex\n");
			else if (2 == port->linked->duplex)
				len += sprintf(buf + len, "full-duplex\n");
		} else
			len += sprintf(buf + len, "unlinked\n");
		break;
	case PROC_SET_SW_SPEED:
		if (!port)
			break;
		len += sprintf(buf + len, "%u; ", port->speed);
		if (media_connected == port->linked->state)
			len += sprintf(buf + len, "%u\n",
				port->linked->tx_rate / TX_RATE_UNIT);
		else
			len += sprintf(buf + len, "unlinked\n");
		break;
	case PROC_SET_SW_FORCE:
		if (!port)
			break;
		len += sprintf(buf + len, "%u\n", port->force_link);
		break;
	case PROC_SET_SW_FLOW_CTRL:
		if (!port)
			break;
		len += sprintf(buf + len, "%u; ", port->flow_ctrl);
		switch (port->flow_ctrl) {
		case PHY_FLOW_CTRL:
			len += sprintf(buf + len, "flow control\n");
			break;
		case PHY_TX_ONLY:
			len += sprintf(buf + len, "tx only\n");
			break;
		case PHY_RX_ONLY:
			len += sprintf(buf + len, "rx only\n");
			break;
		default:
			len += sprintf(buf + len, "no flow control\n");
			break;
		}
		break;
	case PROC_SET_SW_MIB:
		if (!port)
			break;
		len += display_sw_mib_counters(sw, port->first_port,
			port->mib_port_cnt, buf + len);
		break;
	case PROC_SET_BROADCAST_STORM:
		len += sprintf(buf + len, "%u%%\n", info->broad_per);
		break;
	case PROC_SET_DIFFSERV:
		for (i = 0; i < DIFFSERV_ENTRIES / KS_PRIO_IN_REG; i++) {
			len += sprintf(buf + len, "%2u=",
				i * KS_PRIO_IN_REG);
			map = info->diffserv[i];
			for (j = 0; j < KS_PRIO_IN_REG; j++) {
				len += sprintf(buf + len, "%u ",
					map & KS_PRIO_M);
				map >>= KS_PRIO_S;
			}
			len += sprintf(buf + len, "\t"SW_SIZE_STR"\n",
				info->diffserv[i]);
		}
		break;
	case PROC_SET_802_1P:
		for (i = 0; i < PRIO_802_1P_ENTRIES / KS_PRIO_IN_REG; i++) {
			len += sprintf(buf + len, "%u=",
				i * KS_PRIO_IN_REG);
			map = info->p_802_1p[i];
			for (j = 0; j < KS_PRIO_IN_REG; j++) {
				len += sprintf(buf + len, "%u ",
					map & KS_PRIO_M);
				map >>= KS_PRIO_S;
			}
			len += sprintf(buf + len, "\t"SW_SIZE_STR"\n",
				info->p_802_1p[i]);
		}
		break;
	case PROC_SET_SW_VID:
		len += sprintf(buf + len, "0x%04x\n", sw->vid);
		break;
	case PROC_GET_PORTS:
	{
		uint ports = sw->mib_port_cnt;

		if (sw->eth_cnt)
			ports = sw->eth_maps[0].cnt;
		len += sprintf(buf + len, "%u\n", ports);
		break;
	}
	case PROC_GET_DEV_START:
	{
		int start = 0;

		if (sw->dev_offset)
			start = 100;
		len += sprintf(buf + len, "%u\n", start);
		break;
	}
	case PROC_GET_VLAN_START:
	{
		int start = 0;

		if (sw->features & VLAN_PORT)
			start = VLAN_PORT_START;
		len += sprintf(buf + len, "%u\n", start);
		break;
	}
	case PROC_GET_STP:
		len += sprintf(buf + len, "0\n");
		break;
	case PROC_SET_SW_FEATURES:
		len += sprintf(buf + len, "%08x:\n", sw->features);
		len += sprintf(buf + len, "\t%08x = STP support\n",
			STP_SUPPORT);
		len += sprintf(buf + len, "\t%08x = VLAN port forwarding\n",
			VLAN_PORT);
		len += sprintf(buf + len, "\t%08x = VLAN port remove tag\n",
			VLAN_PORT_REMOVE_TAG);
		len += sprintf(buf + len, "\t%08x = VLAN port tag tailing\n",
			VLAN_PORT_TAGGING);
#ifdef CONFIG_KSZ_DLR
		len += sprintf(buf + len, "\t%08x = DLR support\n",
			DLR_HW);
#endif
		len += sprintf(buf + len, "\t%08x = DSA support\n",
			DSA_SUPPORT);
		len += sprintf(buf + len, "\t%08x = different MAC addresses\n",
			DIFF_MAC_ADDR);
		break;
	case PROC_SET_SW_OVERRIDES:
		len += sprintf(buf + len, "%08x:\n", sw->overrides);
		len += sprintf(buf + len, "\t%08x = flow control\n",
			PAUSE_FLOW_CTRL);
		len += sprintf(buf + len, "\t%08x = fast aging\n",
			FAST_AGING);
		len += sprintf(buf + len, "\t%08x = ACL intr monitor\n",
			ACL_INTR_MONITOR);
		len += sprintf(buf + len, "\t%08x = tag is removed\n",
			TAG_REMOVE);
		len += sprintf(buf + len, "\t%08x = tail tagging\n",
			TAIL_TAGGING);
		break;
	case PROC_DYNAMIC:
		len = sw_d_dyn_mac_table(sw, buf, len);
		break;
	case PROC_STATIC:
		len = sw_d_sta_mac_table(sw, buf, len);
		len = sw_d_mac_table(sw, buf, len);
		break;
	case PROC_VLAN:
		len = sw_d_vlan_table(sw, buf, len);
		break;
	}
	return len;
}  /* sysfs_sw_read */

static ssize_t sysfs_sw_read_hw(struct ksz_sw *sw, int proc_num, ssize_t len,
	char *buf)
{
	u8 data[8];
	int chk = 0;
	int type = SHOW_HELP_ON_OFF;
	char note[40];

	note[0] = '\0';
	switch (proc_num) {
	case PROC_SET_AGING:
		chk = sw_chk(sw, REG_SW_CTRL_1, SW_AGING_ENABLE);
		break;
	case PROC_SET_FAST_AGING:
		chk = sw_chk(sw, REG_SW_CTRL_1, SW_FAST_AGING);
		break;
	case PROC_SET_LINK_AGING:
		chk = sw_chk(sw, S_LINK_AGING_CTRL, SW_LINK_AUTO_AGING);
		break;
	case PROC_SET_MULTICAST_STORM:
		chk = !sw_chk(sw, REG_SW_CTRL_2, MULTICAST_STORM_DISABLE);
		break;
	case PROC_SET_TX_RATE_QUEUE_BASED:
		chk = sw_chk(sw, REG_SW_CTRL_19,
			SW_OUT_RATE_LIMIT_QUEUE_BASED);
		break;
	case PROC_ENABLE_VLAN:
		chk = sw_chk(sw, S_MIRROR_CTRL, SW_VLAN_ENABLE);
		break;
	case PROC_SET_REPLACE_NULL_VID:
		chk = sw_chk(sw, S_REPLACE_VID_CTRL, SW_REPLACE_VID);
		break;
	case PROC_SET_MAC_ADDR:
		sw_get_addr(sw, data);
		len += sprintf(buf + len, "%02X:%02X:%02X:%02X:%02X:%02X\n",
			data[0], data[1], data[2], data[3], data[4], data[5]);
		type = SHOW_HELP_NONE;
		break;
	case PROC_SET_MIRROR_MODE:
		chk = sw_chk_mirror_rx_tx(sw);
		if (sw->verbose) {
			if (chk)
				strcpy(note, " (rx and tx)");
			else
				strcpy(note, " (rx or tx)");
		}
		type = SHOW_HELP_SPECIAL;
		break;
	case PROC_SET_IGMP_SNOOP:
		chk = sw_chk(sw, S_MIRROR_CTRL, SW_IGMP_SNOOP);
		break;
	case PROC_SET_IPV6_MLD_SNOOP:
		chk = sw_chk(sw, S_IPV6_MLD_CTRL, SW_IPV6_MLD_SNOOP);
		break;
	case PROC_SET_IPV6_MLD_OPTION:
		chk = sw_chk(sw, S_IPV6_MLD_CTRL, SW_IPV6_MLD_OPTION);
		break;
	case PROC_SET_TAIL_TAG:
		chk = sw_chk(sw, S_TAIL_TAG_CTRL, SW_TAIL_TAG_ENABLE);
		break;
	case PROC_SET_AGGR_BACKOFF:
		chk = sw_chk(sw, REG_SW_CTRL_1, SW_AGGR_BACKOFF);
		break;
	case PROC_SET_NO_EXC_DROP:
		chk = sw_chk(sw, REG_SW_CTRL_2, NO_EXC_COLLISION_DROP);
		break;
	case PROC_SET_VLAN_BOUNDARY:
		chk = sw_chk(sw, REG_SW_CTRL_2, UNICAST_VLAN_BOUNDARY);
		break;
	case PROC_SET_HUGE_PACKET:
		chk = sw_chk(sw, S_HUGE_PACKET_CTRL, SW_HUGE_PACKET);
		break;
	case PROC_SET_LEGAL_PACKET:
		chk = !sw_chk(sw, REG_SW_CTRL_2, SW_LEGAL_PACKET_DISABLE);
		break;
	case PROC_SET_LENGTH_CHECK:
		chk = sw_chk(sw, REG_SW_CTRL_1, SW_CHECK_LENGTH);
		break;
	case PROC_SET_BACK_PRESSURE_MODE:
		chk = sw_chk(sw, REG_SW_CTRL_2, SW_BACK_PRESSURE);
		break;
	case PROC_SET_SWITCH_FLOW_CTRL:
		chk = sw_chk(sw, S_REPLACE_VID_CTRL, SW_FLOW_CTRL);
		break;
	case PROC_SET_SWITCH_HALF_DUPLEX:
		chk = sw_chk(sw, S_REPLACE_VID_CTRL, SW_HALF_DUPLEX);
		break;
#ifdef SW_10_MBIT
	case PROC_SET_SWITCH_10_MBIT:
		chk = sw_chk(sw, S_REPLACE_VID_CTRL, SW_10_MBIT);
		break;
#endif
	case PROC_SET_RX_FLOW_CTRL:
		chk = !sw_chk(sw, REG_SW_CTRL_1, SW_RX_FLOW_CTRL_DISABLE);
		break;
	case PROC_SET_TX_FLOW_CTRL:
		chk = !sw_chk(sw, REG_SW_CTRL_1, SW_TX_FLOW_CTRL_DISABLE);
		break;
	case PROC_SET_FAIR_FLOW_CTRL:
		chk = sw_chk(sw, REG_SW_CTRL_2, FAIR_FLOW_CTRL);
		break;
	case PROC_SET_FORWARD_UNKNOWN_UNICAST:
		chk = sw_chk_unk_dest(sw, REG_SW_UNK_UCAST_CTRL);
		break;
	case PROC_SET_FORWARD_UNKNOWN_UNICAST_PORTS:
		chk = sw_chk_unk_def_port(sw, REG_SW_UNK_UCAST_CTRL,
			sw->port_cnt);
#ifdef USE_LOG_MASK
		chk = get_log_mask_from_phy(sw, chk);
#endif
		type = SHOW_HELP_HEX;
		break;
	case PROC_SET_FORWARD_UNKNOWN_MULTICAST:
		chk = sw_chk_unk_dest(sw, REG_SW_UNK_MCAST_CTRL);
		break;
	case PROC_SET_FORWARD_UNKNOWN_MULTICAST_PORTS:
		chk = sw_chk_unk_def_port(sw, REG_SW_UNK_MCAST_CTRL,
			sw->port_cnt);
#ifdef USE_LOG_MASK
		chk = get_log_mask_from_phy(sw, chk);
#endif
		type = SHOW_HELP_HEX;
		break;
	case PROC_SET_FORWARD_UNKNOWN_VID:
		chk = sw_chk_unk_dest(sw, REG_SW_UNK_VID_CTRL);
		break;
	case PROC_SET_FORWARD_UNKNOWN_VID_PORTS:
		chk = sw_chk_unk_def_port(sw, REG_SW_UNK_VID_CTRL,
			sw->port_cnt);
#ifdef USE_LOG_MASK
		chk = get_log_mask_from_phy(sw, chk);
#endif
		type = SHOW_HELP_HEX;
		break;
	case PROC_SET_FORWARD_UNKNOWN_IP_MULTICAST:
		chk = sw_chk_unk_dest(sw, REG_SW_UNK_IP_MCAST_CTRL);
		break;
	case PROC_SET_FORWARD_UNKNOWN_IP_MULTICAST_PORTS:
		chk = sw_chk_unk_def_port(sw, REG_SW_UNK_IP_MCAST_CTRL,
			sw->port_cnt);
#ifdef USE_LOG_MASK
		chk = get_log_mask_from_phy(sw, chk);
#endif
		type = SHOW_HELP_HEX;
		break;
	case PROC_SET_SELF_ADDR_FILTER:
		chk = sw_chk_self_filter(sw);
		break;
	case PROC_SET_INS_TAG:
		chk = sw_chk_ins_tag(sw);
		break;
	case PROC_SET_PME:
		data[0] = sw_get_pme(sw);
		len += sprintf(buf + len, "%02x:\n", data[0]);
		len += sprintf(buf + len, "\t%02x = PME enable\n",
			SW_PME_OUTPUT_ENABLE);
		len += sprintf(buf + len, "\t%02x = PME active high\n",
			SW_PME_ACTIVE_HIGH);
		type = SHOW_HELP_NONE;
		break;
	case PROC_SET_PASS_PAUSE:
		chk = sw_chk(sw, S_PASS_PAUSE_CTRL, SW_PASS_PAUSE);
		break;
	case PROC_SET_HI_PRIO_QUEUES:
		chk = sw_get_hi_prio_queues(sw);
		if (sw->verbose) {
			switch (chk) {
			case 3:
				strcpy(note, " (3 = H; 2, 1, 0 = L)");
				break;
			case 1:
				strcpy(note, " (3, 2, 1 = H; 0 = L)");
				break;
			default:
				strcpy(note, " (3, 2 = H; 1, 0 = L)");
			}
		}
		type = SHOW_HELP_SPECIAL;
		break;
	default:
		type = SHOW_HELP_NONE;
		break;
	}
	return sysfs_show(len, buf, type, chk, note, sw->verbose);
}  /* sysfs_sw_read_hw */

static int sysfs_sw_write(struct ksz_sw *sw, int proc_num,
	struct ksz_port *port, int num, const char *buf)
{
	int changes;
	int count;
	unsigned int val;
	u8 data[8];
	int processed = true;

	switch (proc_num) {
	case PROC_SW_INFO:
		sw_init(sw);
		sw->verbose = !!num;
		break;
	case PROC_SET_SW_DUPLEX:
		if (!port)
			break;
		if (num <= 2)
			port->duplex = (u8) num;
		break;
	case PROC_SET_SW_SPEED:
		if (!port)
			break;
		if (0 == num || 10 == num || 100 == num)
			port->speed = (u8) num;
		break;
	case PROC_SET_SW_FORCE:
		if (!port)
			break;
		port->force_link = (u8) num;
		if (port->force_link) {
			port_force_link_speed(port);
			sw->phy_intr = sw->PORT_MASK;
			port_get_link_speed(port);
			sw->phy_intr = 0;
		} else
			port_set_link_speed(port);
		break;
	case PROC_SET_SW_FLOW_CTRL:
		if (!port)
			break;
		if (num <= PHY_FLOW_CTRL)
			port->flow_ctrl = (u8) num;
		break;
	case PROC_SET_SW_MIB:
		sw_cfg_mib_counter_ctrl(sw, num, sw->port_cnt);
		break;
	case PROC_SET_SW_REG:
		count = sscanf(buf, "%x=%x", (unsigned int *) &num, &val);
		if (1 == count)
			printk(KERN_INFO SW_SIZE_STR"\n",
				SW_R(sw, num));
		else if (2 == count)
			SW_W(sw, num, val);
		break;
	case PROC_SET_SW_VID:
		sw->vid = num;
		break;
	case PROC_SET_SW_FEATURES:
		if ('0' != buf[0] || 'x' != buf[1])
			sscanf(buf, "%x", &num);
		changes = sw->features ^ num;
		sw->features = num;
		if (changes & VLAN_PORT_REMOVE_TAG) {
			uint n;
			uint p;
			bool enabled;

			if (num & VLAN_PORT_REMOVE_TAG) {
				enabled = true;
				sw->overrides |= TAG_REMOVE;
			} else {
				enabled = false;
				sw->overrides &= ~TAG_REMOVE;
			}
			for (n = 1; n <= sw->mib_port_cnt; n++) {
				p = get_phy_port(sw, n);
				port_cfg_rmv_tag(sw, p, enabled);
			}
		}
		break;
	case PROC_SET_SW_OVERRIDES:
		if ('0' != buf[0] || 'x' != buf[1])
			sscanf(buf, "%x", &num);
		sw->overrides = num;
		break;
	case PROC_DYNAMIC:
		sw_flush_dyn_mac_table(sw, TOTAL_PORT_NUM);
		break;
	case PROC_STATIC:
		sw_clr_sta_mac_table(sw);
		break;
	case PROC_SET_AGING:
		sw_cfg(sw, REG_SW_CTRL_1, SW_AGING_ENABLE, num);
		break;
	case PROC_SET_FAST_AGING:
		sw_cfg(sw, REG_SW_CTRL_1, SW_FAST_AGING, num);
		break;
	case PROC_SET_LINK_AGING:
		sw_cfg(sw, S_LINK_AGING_CTRL, SW_LINK_AUTO_AGING, num);
		break;
	case PROC_SET_BROADCAST_STORM:
		hw_cfg_broad_storm(sw, num);
		break;
	case PROC_SET_MULTICAST_STORM:
		sw_cfg(sw, REG_SW_CTRL_2, MULTICAST_STORM_DISABLE, !num);
		break;
	case PROC_SET_TX_RATE_QUEUE_BASED:
		sw_cfg(sw, REG_SW_CTRL_19, SW_OUT_RATE_LIMIT_QUEUE_BASED,
			num);
		break;
	case PROC_SET_DIFFSERV:
		count = sscanf(buf, "%d=%x", (unsigned int *) &num, &val);
		if (2 == count)
			hw_cfg_tos_prio(sw, (u8) num, (u16) val);
		break;
	case PROC_SET_802_1P:
		count = sscanf(buf, "%d=%x", (unsigned int *) &num, &val);
		if (2 == count)
			hw_cfg_802_1p_prio(sw, (u8) num, (u16) val);
		break;
	case PROC_ENABLE_VLAN:
		if (!num)
			sw_dis_vlan(sw);
		else
			sw_ena_vlan(sw);
		break;
	case PROC_SET_REPLACE_NULL_VID:
		sw_cfg_replace_null_vid(sw, num);
		break;
	case PROC_SET_MAC_ADDR:
	{
		int i;
		int n[6];

		i = sscanf(buf, "%x:%x:%x:%x:%x:%x",
			&n[0], &n[1], &n[2], &n[3], &n[4], &n[5]);
		if (6 == i) {
			for (i = 0; i < 6; i++)
				data[i] = (u8) n[i];
			sw_set_addr(sw, data);
		}
		break;
	}
	case PROC_SET_MIRROR_MODE:
		sw_cfg_mirror_rx_tx(sw, num);
		break;
	case PROC_SET_IGMP_SNOOP:
		sw_cfg(sw, S_MIRROR_CTRL, SW_IGMP_SNOOP, num);
		break;
	case PROC_SET_IPV6_MLD_SNOOP:
		sw_cfg(sw, S_IPV6_MLD_CTRL, SW_IPV6_MLD_SNOOP, num);
		break;
	case PROC_SET_IPV6_MLD_OPTION:
		sw_cfg(sw, S_IPV6_MLD_CTRL, SW_IPV6_MLD_OPTION, num);
		break;
	case PROC_SET_TAIL_TAG:
		sw_cfg(sw, S_TAIL_TAG_CTRL, SW_TAIL_TAG_ENABLE, num);
		if (num)
			sw->overrides |= TAIL_TAGGING;
		else
			sw->overrides &= ~TAIL_TAGGING;
		break;
	case PROC_SET_AGGR_BACKOFF:
		sw_cfg(sw, REG_SW_CTRL_1, SW_AGGR_BACKOFF, num);
		break;
	case PROC_SET_NO_EXC_DROP:
		sw_cfg(sw, REG_SW_CTRL_2, NO_EXC_COLLISION_DROP, num);
		break;
	case PROC_SET_VLAN_BOUNDARY:
		sw_cfg(sw, REG_SW_CTRL_2, UNICAST_VLAN_BOUNDARY, num);
		break;
	case PROC_SET_HUGE_PACKET:
		sw_cfg(sw, S_HUGE_PACKET_CTRL, SW_HUGE_PACKET, num);
		break;
	case PROC_SET_LEGAL_PACKET:
		sw_cfg(sw, REG_SW_CTRL_2, SW_LEGAL_PACKET_DISABLE, !num);
		break;
	case PROC_SET_LENGTH_CHECK:
		sw_cfg(sw, REG_SW_CTRL_1, SW_CHECK_LENGTH, num);
		break;
	case PROC_SET_BACK_PRESSURE_MODE:
		sw_cfg(sw, REG_SW_CTRL_2, SW_BACK_PRESSURE, num);
		break;
	case PROC_SET_SWITCH_FLOW_CTRL:
		sw_cfg(sw, S_REPLACE_VID_CTRL, SW_FLOW_CTRL, num);
		break;
	case PROC_SET_SWITCH_HALF_DUPLEX:
		sw_cfg(sw, S_REPLACE_VID_CTRL, SW_HALF_DUPLEX, num);
		break;
#ifdef SW_10_MBIT
	case PROC_SET_SWITCH_10_MBIT:
		sw_cfg(sw, S_REPLACE_VID_CTRL, SW_10_MBIT, num);
		break;
#endif
	case PROC_SET_RX_FLOW_CTRL:
		sw_cfg(sw, REG_SW_CTRL_1, SW_RX_FLOW_CTRL_DISABLE, !num);
		break;
	case PROC_SET_TX_FLOW_CTRL:
		sw_cfg(sw, REG_SW_CTRL_1, SW_TX_FLOW_CTRL_DISABLE, !num);
		break;
	case PROC_SET_FAIR_FLOW_CTRL:
		sw_cfg(sw, REG_SW_CTRL_2, FAIR_FLOW_CTRL, num);
		break;
	case PROC_SET_FORWARD_UNKNOWN_UNICAST:
		sw_cfg_unk_dest(sw, REG_SW_UNK_UCAST_CTRL, num);
		break;
	case PROC_SET_FORWARD_UNKNOWN_UNICAST_PORTS:
#ifdef USE_LOG_MASK
		num = get_phy_mask_from_log(sw, num);
#endif
		sw_cfg_unk_def_port(sw, REG_SW_UNK_UCAST_CTRL, num, 2);
		break;
	case PROC_SET_FORWARD_UNKNOWN_MULTICAST:
		sw_cfg_unk_dest(sw, REG_SW_UNK_MCAST_CTRL, num);
		break;
	case PROC_SET_FORWARD_UNKNOWN_MULTICAST_PORTS:
#ifdef USE_LOG_MASK
		num = get_phy_mask_from_log(sw, num);
#endif
		sw_cfg_unk_def_port(sw, REG_SW_UNK_MCAST_CTRL, num, 2);
		break;
	case PROC_SET_FORWARD_UNKNOWN_VID:
		sw_cfg_unk_dest(sw, REG_SW_UNK_VID_CTRL, num);
		break;
	case PROC_SET_FORWARD_UNKNOWN_VID_PORTS:
#ifdef USE_LOG_MASK
		num = get_phy_mask_from_log(sw, num);
#endif
		sw_cfg_unk_def_port(sw, REG_SW_UNK_VID_CTRL, num, 2);
		break;
	case PROC_SET_FORWARD_UNKNOWN_IP_MULTICAST:
		sw_cfg_unk_dest(sw, REG_SW_UNK_IP_MCAST_CTRL, num);
		break;
	case PROC_SET_FORWARD_UNKNOWN_IP_MULTICAST_PORTS:
#ifdef USE_LOG_MASK
		num = get_phy_mask_from_log(sw, num);
#endif
		sw_cfg_unk_def_port(sw, REG_SW_UNK_IP_MCAST_CTRL, num, 2);
		break;
	case PROC_SET_SELF_ADDR_FILTER:
		sw_cfg_self_filter(sw, num);
		break;
	case PROC_SET_INS_TAG:
		sw_cfg_ins_tag(sw, num);
		break;
	case PROC_SET_PME:
		sw_set_pme(sw, num);
		break;
	case PROC_SET_PASS_PAUSE:
		sw_cfg(sw, S_PASS_PAUSE_CTRL, SW_PASS_PAUSE, num);
		break;
	case PROC_SET_HI_PRIO_QUEUES:
		sw_set_hi_prio_queues(sw, num);
		break;
	default:
		processed = false;
		break;
	}
	return processed;
}  /* sysfs_sw_write */

static ssize_t sysfs_port_read(struct ksz_sw *sw, int proc_num, uint n,
	ssize_t len, char *buf)
{
	struct ksz_port_cfg *port_cfg;
	struct ksz_port_info *port_info;
	uint port;
	int chk = 0;
	int type = SHOW_HELP_NONE;
	char note[40];

	note[0] = '\0';
	port = get_sysfs_port(sw, n);
	port_cfg = get_port_cfg(sw, port);
	port_info = get_port_info(sw, port);
	switch (proc_num) {
	case PROC_SET_PORT_DUPLEX:
		if (media_connected == port_info->state) {
			if (1 == port_info->duplex)
				len += sprintf(buf + len, "half-duplex\n");
			else if (2 == port_info->duplex)
				len += sprintf(buf + len, "full-duplex\n");
		} else
			len += sprintf(buf + len, "unlinked\n");
		break;
	case PROC_SET_PORT_SPEED:
		if (media_connected == port_info->state)
			len += sprintf(buf + len, "%u\n",
				port_info->tx_rate / TX_RATE_UNIT);
		else
			len += sprintf(buf + len, "unlinked\n");
		break;
	case PROC_SET_PORT_MIB:
		port = get_log_port(sw, port);
		len += display_sw_mib_counters(sw, port, 1, buf + len);
		break;
	case PROC_SET_LINK_MD:
		len += sprintf(buf + len, "%u:%u %u:%u %u:%u\n",
			port_info->length[0], port_info->status[0],
			port_info->length[1], port_info->status[1],
			port_info->length[2], port_info->status[2]);
		if (sw->verbose)
			len += sprintf(buf + len,
				"(%d=unknown; %d=normal; %d=open; %d=short)\n",
				CABLE_UNKNOWN, CABLE_GOOD, CABLE_OPEN,
				CABLE_SHORT);
		break;
	case PROC_SET_PORT_BASED:
		chk = port_cfg->port_prio;
		type = SHOW_HELP_NUM;
		break;
	case PROC_SET_DEF_VID:
		chk = port_cfg->vid;
		type = SHOW_HELP_HEX_4;
		break;
	case PROC_SET_MEMBER:
		chk = port_cfg->member;
#ifdef USE_LOG_MASK
		chk = get_log_mask_from_phy(sw, chk);
#endif
		type = SHOW_HELP_HEX_2;
		break;
	case PROC_SET_TX_Q0_CTRL:
		chk = (port_cfg->rate_ctrl[0] & RATE_CTRL_ENABLE) != 0;
		type = SHOW_HELP_ON_OFF;
		break;
	case PROC_SET_TX_Q1_CTRL:
		chk = (port_cfg->rate_ctrl[1] & RATE_CTRL_ENABLE) != 0;
		type = SHOW_HELP_ON_OFF;
		break;
	case PROC_SET_TX_Q2_CTRL:
		chk = (port_cfg->rate_ctrl[2] & RATE_CTRL_ENABLE) != 0;
		type = SHOW_HELP_ON_OFF;
		break;
	case PROC_SET_TX_Q3_CTRL:
		chk = (port_cfg->rate_ctrl[3] & RATE_CTRL_ENABLE) != 0;
		type = SHOW_HELP_ON_OFF;
		break;
	case PROC_SET_TX_Q0_RATIO:
		chk = port_cfg->rate_ctrl[0] & RATE_RATIO_M;
		type = SHOW_HELP_NUM;
		break;
	case PROC_SET_TX_Q1_RATIO:
		chk = port_cfg->rate_ctrl[1] & RATE_RATIO_M;
		type = SHOW_HELP_NUM;
		break;
	case PROC_SET_TX_Q2_RATIO:
		chk = port_cfg->rate_ctrl[2] & RATE_RATIO_M;
		type = SHOW_HELP_NUM;
		break;
	case PROC_SET_TX_Q3_RATIO:
		chk = port_cfg->rate_ctrl[3] & RATE_RATIO_M;
		type = SHOW_HELP_NUM;
		break;
	case PROC_SET_RX_LIMIT:
		chk = ((port_cfg->rate_limit >> PORT_IN_LIMIT_MODE_S) &
			PORT_IN_LIMIT_MODE_M);
		if (sw->verbose) {
			switch (chk) {
			case 1:
				strcpy(note, " (flooded unicast)");
				break;
			case 2:
				strcpy(note, " (multicast)");
				break;
			case 3:
				strcpy(note, " (broadcast)");
				break;
			default:
				strcpy(note, " (all)");
			}
		}
		type = SHOW_HELP_SPECIAL;
		break;
	case PROC_SET_RX_LIMIT_PORT_BASED:
		chk = ((port_cfg->rate_limit >> PORT_IN_PORT_BASED_S) & 1);
		type = SHOW_HELP_ON_OFF;
		break;
	case PROC_SET_LIMIT_PACKET_BASED:
		chk = ((port_cfg->rate_limit >> PORT_RATE_PACKET_BASED_S) & 1);
		type = SHOW_HELP_ON_OFF;
		break;
	case PROC_SET_RX_LIMIT_FLOW_CTRL:
		chk = ((port_cfg->rate_limit >> PORT_IN_FLOW_CTRL_S) & 1);
		type = SHOW_HELP_ON_OFF;
		break;
	case PROC_SET_CNT_IFG:
		chk = ((port_cfg->rate_limit >> PORT_COUNT_IFG_S) & 1);
		type = SHOW_HELP_ON_OFF;
		break;
	case PROC_SET_CNT_PRE:
		chk = ((port_cfg->rate_limit >> PORT_COUNT_PREAMBLE_S) & 1);
		type = SHOW_HELP_ON_OFF;
		break;
	case PROC_SET_RX_P0_RATE:
		len += sprintf(buf + len, "%u %s\n", (int)
			port_cfg->packet_based ?
			port_cfg->rx_packet[0] : port_cfg->rx_rate[0],
			port_cfg->packet_based ? "pps" : "bps");
		break;
	case PROC_SET_RX_P1_RATE:
		len += sprintf(buf + len, "%u %s\n", (int)
			port_cfg->packet_based ?
			port_cfg->rx_packet[1] : port_cfg->rx_rate[1],
			port_cfg->packet_based ? "pps" : "bps");
		break;
	case PROC_SET_RX_P2_RATE:
		len += sprintf(buf + len, "%u %s\n", (int)
			port_cfg->packet_based ?
			port_cfg->rx_packet[2] : port_cfg->rx_rate[2],
			port_cfg->packet_based ? "pps" : "bps");
		break;
	case PROC_SET_RX_P3_RATE:
		len += sprintf(buf + len, "%u %s\n", (int)
			port_cfg->packet_based ?
			port_cfg->rx_packet[3] : port_cfg->rx_rate[3],
			port_cfg->packet_based ? "pps" : "bps");
		break;
	case PROC_SET_TX_Q0_RATE:
		len += sprintf(buf + len, "%u %s\n", (int)
			port_cfg->packet_based ?
			port_cfg->tx_packet[0] : port_cfg->tx_rate[0],
			port_cfg->packet_based ? "pps" : "bps");
		break;
	case PROC_SET_TX_Q1_RATE:
		len += sprintf(buf + len, "%u %s\n", (int)
			port_cfg->packet_based ?
			port_cfg->tx_packet[1] : port_cfg->tx_rate[1],
			port_cfg->packet_based ? "pps" : "bps");
		break;
	case PROC_SET_TX_Q2_RATE:
		len += sprintf(buf + len, "%u %s\n", (int)
			port_cfg->packet_based ?
			port_cfg->tx_packet[2] : port_cfg->tx_rate[2],
			port_cfg->packet_based ? "pps" : "bps");
		break;
	case PROC_SET_TX_Q3_RATE:
		len += sprintf(buf + len, "%u %s\n", (int)
			port_cfg->packet_based ?
			port_cfg->tx_packet[3] : port_cfg->tx_rate[3],
			port_cfg->packet_based ? "pps" : "bps");
		break;
	}
	return sysfs_show(len, buf, type, chk, note, sw->verbose);
}  /* sysfs_port_read */

static ssize_t sysfs_port_read_hw(struct ksz_sw *sw, int proc_num, uint n,
	ssize_t len, char *buf)
{
	u8 data[8];
	uint port;
	int chk = 0;
	int type = SHOW_HELP_ON_OFF;
	char note[40];

	note[0] = '\0';
	port = get_sysfs_port(sw, n);
	switch (proc_num) {
	case PROC_ENABLE_BROADCAST_STORM:
		chk = port_chk_broad_storm(sw, port);
		break;
	case PROC_ENABLE_DIFFSERV:
		chk = port_chk_diffserv(sw, port);
		break;
	case PROC_ENABLE_802_1P:
		chk = port_chk_802_1p(sw, port);
		break;
	case PROC_ENABLE_PRIO_QUEUE:
		chk = port_get_prio_queue(sw, port);
		type = SHOW_HELP_NUM;
		break;
	case PROC_SET_MIRROR_PORT:
		chk = port_chk_mirror_sniffer(sw, port);
		break;
	case PROC_SET_MIRROR_RX:
		chk = port_chk_mirror_rx(sw, port);
		break;
	case PROC_SET_MIRROR_TX:
		chk = port_chk_mirror_tx(sw, port);
		break;
	case PROC_SET_RX:
		chk = port_chk_rx(sw, port);
		break;
	case PROC_SET_TX:
		chk = port_chk_tx(sw, port);
		break;
	case PROC_SET_LEARN:
		chk = !port_chk_dis_learn(sw, port);
		break;
	case PROC_SET_INSERT_TAG:
		chk = port_chk_ins_tag(sw, port);
		break;
	case PROC_SET_REMOVE_TAG:
		chk = port_chk_rmv_tag(sw, port);
		break;
	case PROC_SET_DROP_TAG:
		chk = port_chk_drop_tag(sw, port);
		break;
	case PROC_SET_REPLACE_PRIO:
		chk = port_chk_replace_prio(sw, port);
		break;
	case PROC_ENABLE_RX_PRIO_RATE:
		chk = sw_chk_rx_prio_rate(sw, port);
		break;
	case PROC_ENABLE_TX_PRIO_RATE:
		chk = sw_chk_tx_prio_rate(sw, port);
		break;
	case PROC_SET_DIS_NON_VID:
		chk = port_chk_dis_non_vid(sw, port);
		break;
	case PROC_SET_INGRESS:
		chk = port_chk_in_filter(sw, port);
		break;
	case PROC_SET_BACK_PRESSURE:
		chk = port_chk_back_pressure(sw, port);
		break;
	case PROC_SET_FORCE_FLOW_CTRL:
		chk = port_chk_force_flow_ctrl(sw, port);
		break;
	case PROC_SET_INS_TAG_0:
		chk = sw_chk_ins(sw, port, 0);
		break;
	case PROC_SET_INS_TAG_1:
		chk = sw_chk_ins(sw, port, 1);
		break;
	case PROC_SET_INS_TAG_2:
		chk = sw_chk_ins(sw, port, 2);
		break;
	case PROC_SET_INS_TAG_3:
		chk = sw_chk_ins(sw, port, 3);
		break;
	case PROC_SET_INS_TAG_4:
		chk = sw_chk_ins(sw, port, 4);
		break;
	case PROC_SET_PASS_ALL:
		chk = port_chk(sw, port, P_PASS_ALL_CTRL, PORT_PASS_ALL);
		break;
	case PROC_SET_UNKNOWN_UNICAST_PORT:
		chk = sw_chk_unk_def_port(sw, REG_SW_UNK_UCAST_CTRL, port);
		break;
	case PROC_SET_UNKNOWN_MULTICAST_PORT:
		chk = sw_chk_unk_def_port(sw, REG_SW_UNK_MCAST_CTRL, port);
		break;
	case PROC_SET_UNKNOWN_VID_PORT:
		chk = sw_chk_unk_def_port(sw, REG_SW_UNK_VID_CTRL, port);
		break;
	case PROC_SET_UNKNOWN_IP_MULTICAST_PORT:
		chk = sw_chk_unk_def_port(sw, REG_SW_UNK_IP_MCAST_CTRL, port);
		break;
	case PROC_SET_PORT_PME_CTRL:
		data[0] = port_get_pme_ctrl(sw, port);
		len += sprintf(buf + len, "%02x:\n", data[0]);
		len += sprintf(buf + len, "\t%02x = Magic Packet detect\n",
			PORT_MAGIC_PACKET_DETECT);
		len += sprintf(buf + len, "\t%02x = link up detect\n",
			PORT_LINK_UP_DETECT);
		len += sprintf(buf + len, "\t%02x = energy detect\n",
			PORT_ENERGY_DETECT);
		type = SHOW_HELP_NONE;
		break;
	case PROC_SET_PORT_PME_STATUS:
		data[0] = port_get_pme_status(sw, port);
		len += sprintf(buf + len, "%02x:\n", data[0]);
		len += sprintf(buf + len, "\t%02x = Magic Packet detect\n",
			PORT_MAGIC_PACKET_DETECT);
		len += sprintf(buf + len, "\t%02x = link up detect\n",
			PORT_LINK_UP_DETECT);
		len += sprintf(buf + len, "\t%02x = energy detect\n",
			PORT_ENERGY_DETECT);
		type = SHOW_HELP_NONE;
		break;
	case PROC_SET_AUTHEN_MODE:
		len += sprintf(buf + len, "%u\n",
			port_get_authen_mode(sw, port));
		type = SHOW_HELP_NONE;
		break;
	case PROC_SET_ACL:
		chk = port_chk_acl(sw, port);
		break;
	default:
		type = SHOW_HELP_NONE;
		break;
	}
	return sysfs_show(len, buf, type, chk, note, sw->verbose);
}  /* sysfs_port_read_hw */

static int sysfs_port_write(struct ksz_sw *sw, int proc_num, uint n,
	int num, const char *buf)
{
	uint port;
	int processed = true;

	port = get_sysfs_port(sw, n);
	switch (proc_num) {
	case PROC_SET_PORT_DUPLEX:
	case PROC_SET_PORT_SPEED:
	{
		struct ksz_port phy_port;
		struct ksz_port_info *port_info = get_port_info(sw, port);

		if ((PROC_SET_PORT_DUPLEX == proc_num && num > 2) ||
		    (PROC_SET_PORT_SPEED == proc_num &&
		    num != 0 && num != 10 && num != 100))
			break;

		if (port == sw->HOST_PORT)
			break;
		phy_port.sw = sw;
		phy_port.port_cnt = 1;
		phy_port.first_port = get_log_port(sw, port);
		phy_port.flow_ctrl = port_info->own_flow_ctrl;
		phy_port.duplex = port_info->own_duplex;
		phy_port.speed = port_info->own_speed;
		if (PROC_SET_PORT_DUPLEX == proc_num)
			phy_port.duplex = (u8) num;
		else
			phy_port.speed = (u16) num;
		port_set_link_speed(&phy_port);
		break;
	}
	case PROC_SET_PORT_MIB:
		sw_cfg_mib_counter_ctrl(sw, num, port);
		break;
	case PROC_ENABLE_BROADCAST_STORM:
		if (!num)
			sw_dis_broad_storm(sw, port);
		else
			sw_ena_broad_storm(sw, port);
		break;
	case PROC_ENABLE_DIFFSERV:
		if (!num)
			sw_dis_diffserv(sw, port);
		else
			sw_ena_diffserv(sw, port);
		break;
	case PROC_ENABLE_802_1P:
		if (!num)
			sw_dis_802_1p(sw, port);
		else
			sw_ena_802_1p(sw, port);
		break;
	case PROC_SET_PORT_BASED:
		sw_cfg_port_based(sw, port, num);
		break;
	case PROC_SET_DEF_VID:
		sw_cfg_def_vid(sw, port, num);
		break;
	case PROC_SET_MEMBER:
#ifdef USE_LOG_MASK
		num = get_phy_mask_from_log(sw, num);
#endif
		sw_cfg_port_base_vlan(sw, port, (u8) num);
		break;
	case PROC_ENABLE_PRIO_QUEUE:
		if (0 <= num && num <= 4)
			port_set_prio_queue(sw, port, num);
		break;
	case PROC_SET_INS_TAG_0:
		sw_cfg_ins(sw, port, 0, num);
		break;
	case PROC_SET_INS_TAG_1:
		sw_cfg_ins(sw, port, 1, num);
		break;
	case PROC_SET_INS_TAG_2:
		sw_cfg_ins(sw, port, 2, num);
		break;
	case PROC_SET_INS_TAG_3:
		sw_cfg_ins(sw, port, 3, num);
		break;
	case PROC_SET_INS_TAG_4:
		sw_cfg_ins(sw, port, 4, num);
		break;
	case PROC_SET_PASS_ALL:
		port_cfg(sw, port, P_PASS_ALL_CTRL, PORT_PASS_ALL, num);
		break;
	case PROC_SET_TX_Q0_CTRL:
		hw_cfg_rate_ctrl(sw, port, 0, num);
		break;
	case PROC_SET_TX_Q1_CTRL:
		hw_cfg_rate_ctrl(sw, port, 1, num);
		break;
	case PROC_SET_TX_Q2_CTRL:
		hw_cfg_rate_ctrl(sw, port, 2, num);
		break;
	case PROC_SET_TX_Q3_CTRL:
		hw_cfg_rate_ctrl(sw, port, 3, num);
		break;
	case PROC_SET_TX_Q0_RATIO:
		hw_cfg_rate_ratio(sw, port, 0, (u8) num);
		break;
	case PROC_SET_TX_Q1_RATIO:
		hw_cfg_rate_ratio(sw, port, 1, (u8) num);
		break;
	case PROC_SET_TX_Q2_RATIO:
		hw_cfg_rate_ratio(sw, port, 2, (u8) num);
		break;
	case PROC_SET_TX_Q3_RATIO:
		hw_cfg_rate_ratio(sw, port, 3, (u8) num);
		break;
	case PROC_SET_RX_LIMIT:
		hw_cfg_rx_limit(sw, port, (u8) num);
		break;
	case PROC_SET_RX_LIMIT_PORT_BASED:
		hw_cfg_in_port_based(sw, port, num);
		break;
	case PROC_SET_LIMIT_PACKET_BASED:
		hw_cfg_rate_packet_based(sw, port, num);
		break;
	case PROC_SET_RX_LIMIT_FLOW_CTRL:
		hw_cfg_in_flow_ctrl(sw, port, num);
		break;
	case PROC_SET_CNT_IFG:
		hw_cfg_cnt_ifg(sw, port, num);
		break;
	case PROC_SET_CNT_PRE:
		hw_cfg_cnt_pre(sw, port, num);
		break;
	case PROC_SET_RX_P0_RATE:
		hw_cfg_rx_prio_rate(sw, port, 0, num);
		hw_set_rx_prio(sw, port);
		break;
	case PROC_SET_RX_P1_RATE:
		hw_cfg_rx_prio_rate(sw, port, 1, num);
		hw_set_rx_prio(sw, port);
		break;
	case PROC_SET_RX_P2_RATE:
		hw_cfg_rx_prio_rate(sw, port, 2, num);
		hw_set_rx_prio(sw, port);
		break;
	case PROC_SET_RX_P3_RATE:
		hw_cfg_rx_prio_rate(sw, port, 3, num);
		break;
	case PROC_SET_TX_Q0_RATE:
		hw_cfg_tx_prio_rate(sw, port, 0, num);
		break;
	case PROC_SET_TX_Q1_RATE:
		hw_cfg_tx_prio_rate(sw, port, 1, num);
		break;
	case PROC_SET_TX_Q2_RATE:
		hw_cfg_tx_prio_rate(sw, port, 2, num);
		break;
	case PROC_SET_TX_Q3_RATE:
		hw_cfg_tx_prio_rate(sw, port, 3, num);
		break;
	case PROC_SET_MIRROR_PORT:
		port_cfg_mirror_sniffer(sw, port, num);
		break;
	case PROC_SET_MIRROR_RX:
		port_cfg_mirror_rx(sw, port, num);
		break;
	case PROC_SET_MIRROR_TX:
		port_cfg_mirror_tx(sw, port, num);
		break;
	case PROC_SET_RX:
		port_cfg_rx(sw, port, num);
		break;
	case PROC_SET_TX:
		port_cfg_tx(sw, port, num);
		break;
	case PROC_SET_LEARN:
		port_cfg_dis_learn(sw, port, !num);
		if (!num)
			sw_cfg(sw, S_FLUSH_TABLE_CTRL,
				SW_FLUSH_DYN_MAC_TABLE, 1);
		break;
	case PROC_SET_INSERT_TAG:
		sw_vlan_cfg_ins_tag(sw, port, num);
		break;
	case PROC_SET_REMOVE_TAG:
		sw_vlan_cfg_rmv_tag(sw, port, num);
		break;
	case PROC_SET_DROP_TAG:
		sw_vlan_cfg_drop_tag(sw, port, num);
		break;
	case PROC_SET_REPLACE_PRIO:
		sw_cfg_replace_prio(sw, port, num);
		break;
	case PROC_ENABLE_RX_PRIO_RATE:
		if (!num)
			sw_dis_rx_prio_rate(sw, port);
		else
			sw_ena_rx_prio_rate(sw, port);
		break;
	case PROC_ENABLE_TX_PRIO_RATE:
		if (!num)
			sw_dis_tx_prio_rate(sw, port);
		else
			sw_ena_tx_prio_rate(sw, port);
		break;
	case PROC_SET_DIS_NON_VID:
		sw_vlan_cfg_dis_non_vid(sw, port, num);
		break;
	case PROC_SET_INGRESS:
		sw_vlan_cfg_in_filter(sw, port, num);
		break;
	case PROC_SET_BACK_PRESSURE:
		port_cfg_back_pressure(sw, port, num);
		break;
	case PROC_SET_FORCE_FLOW_CTRL:
		port_cfg_force_flow_ctrl(sw, port, num);
		break;
	case PROC_SET_UNKNOWN_UNICAST_PORT:
		sw_cfg_unk_def_port(sw, REG_SW_UNK_UCAST_CTRL, port, num);
		break;
	case PROC_SET_UNKNOWN_MULTICAST_PORT:
		sw_cfg_unk_def_port(sw, REG_SW_UNK_MCAST_CTRL, port, num);
		break;
	case PROC_SET_UNKNOWN_VID_PORT:
		sw_cfg_unk_def_port(sw, REG_SW_UNK_VID_CTRL, port, num);
		break;
	case PROC_SET_UNKNOWN_IP_MULTICAST_PORT:
		sw_cfg_unk_def_port(sw, REG_SW_UNK_IP_MCAST_CTRL, port, num);
		break;
	case PROC_SET_PORT_PME_CTRL:
		port_set_pme_ctrl(sw, port, num);
		break;
	case PROC_SET_PORT_PME_STATUS:
		port_set_pme_status(sw, port, num);
		break;
	case PROC_SET_AUTHEN_MODE:
		port_set_authen_mode(sw, port, num);
		break;
	case PROC_SET_ACL:
		port_cfg_acl(sw, port, num);
		break;
	case PROC_SET_LINK_MD:
		sw_get_link_md(sw, port);
		break;
	default:
		processed = false;
		break;
	}
	return processed;
}  /* sysfs_port_write */

static ssize_t sysfs_mac_read(struct ksz_sw *sw, int proc_num, ssize_t len,
	char *buf)
{
	struct ksz_mac_table *entry;
	u8 ports;

	entry = &sw->info->mac_entry;
	switch (proc_num) {
	case PROC_SET_STATIC_FID:
		len += sprintf(buf + len, "0x%02x\n", entry->fid);
		break;
	case PROC_SET_STATIC_USE_FID:
		len += sprintf(buf + len, "%u\n", entry->use_fid);
		break;
	case PROC_SET_STATIC_OVERRIDE:
		len += sprintf(buf + len, "%u\n", entry->override);
		break;
	case PROC_SET_STATIC_VALID:
		len += sprintf(buf + len, "%u\n", entry->valid);
		break;
	case PROC_SET_STATIC_PORTS:
		ports = entry->ports;
#ifdef USE_LOG_MASK
		ports = get_log_mask_from_phy(sw, entry->ports);
#endif
		len += sprintf(buf + len, "0x%02x\n", ports);
		break;
	case PROC_SET_STATIC_MAC_ADDR:
		len += sprintf(buf + len, "%02x:%02x:%02x:%02x:%02x:%02x\n",
			entry->addr[0], entry->addr[1],
			entry->addr[2], entry->addr[3],
			entry->addr[4], entry->addr[5]);
		break;
	case PROC_SET_STATIC_INDEX:
		len += sprintf(buf + len, "0x%02x\n", sw->mac_index);
		break;
	case PROC_GET_STATIC_INFO:
		if (sw->mac_dirty) {
			if (!entry->dirty)
				sw_r_sta_mac_table(sw, sw->mac_index, entry);
			sw->mac_dirty = 0;
		}
		ports = entry->ports;
#ifdef USE_LOG_MASK
		ports = get_log_mask_from_phy(sw, ports);
#endif
		len += sprintf(buf + len,
			"%2x: %02X:%02X:%02X:%02X:%02X:%02X "
			"%02x o:%u %u:%02x [%u]\n",
			sw->mac_index,
			entry->addr[0], entry->addr[1], entry->addr[2],
			entry->addr[3], entry->addr[4], entry->addr[5],
			ports, entry->override,
			entry->use_fid, entry->fid,
			entry->dirty ? 2 : entry->valid);
		break;
	}
	return len;
}  /* sysfs_mac_read */

static int sysfs_mac_write(struct ksz_sw *sw, int proc_num, int num,
	const char *buf)
{
	struct ksz_mac_table *entry;
	u8 ports;
	int processed = true;

	entry = &sw->info->mac_entry;
	switch (proc_num) {
	case PROC_SET_STATIC_FID:
		if (0 <= num && num < 128) {
			entry->fid = num;
			entry->dirty = 1;
		}
		break;
	case PROC_SET_STATIC_USE_FID:
		if (num)
			entry->use_fid = 1;
		else
			entry->use_fid = 0;
		entry->dirty = 1;
		break;
	case PROC_SET_STATIC_OVERRIDE:
		if (num)
			entry->override = 1;
		else
			entry->override = 0;
		entry->dirty = 1;
		break;
	case PROC_SET_STATIC_VALID:
		if (num)
			entry->valid = 1;
		else
			entry->valid = 0;
		sw_w_sta_mac_table(sw, sw->mac_index, entry);
		break;
	case PROC_SET_STATIC_PORTS:
		if (0 <= num && num <= sw->PORT_MASK) {
			ports = num;
#ifdef USE_LOG_MASK
			ports = get_phy_mask_from_log(sw, ports);
#endif
			entry->ports = ports;
			entry->dirty = 1;
		}
		break;
	case PROC_SET_STATIC_MAC_ADDR:
	{
		int i;
		int n[6];

		i = sscanf(buf, "%x:%x:%x:%x:%x:%x",
			&n[0], &n[1], &n[2], &n[3], &n[4], &n[5]);
		if (6 == i) {
			for (i = 0; i < 6; i++)
				entry->addr[i] = (u8) n[i];
			entry->dirty = 1;
		}
		break;
	}
	case PROC_SET_STATIC_INDEX:
		if (0 <= num && num < STATIC_MAC_TABLE_ENTRIES) {
			sw->mac_index = num;
			sw->mac_dirty = 1;
		}
		break;
	default:
		processed = false;
		break;
	}
	return processed;
}  /* sysfs_mac_write */

static ssize_t sysfs_vlan_read(struct ksz_sw *sw, int proc_num,	ssize_t len,
	char *buf)
{
	struct ksz_vlan_table *entry;

	entry = &sw->info->vlan_entry;
	switch (proc_num) {
	case PROC_SET_VLAN_VALID:
		len += sprintf(buf + len, "%u\n", entry->valid);
		break;
	case PROC_SET_VLAN_MEMBER:
		len += sprintf(buf + len, "0x%02x\n", entry->member);
		break;
	case PROC_SET_VLAN_FID:
		len += sprintf(buf + len, "0x%02x\n", entry->fid);
		break;
	case PROC_SET_VLAN_VID:
		len += sprintf(buf + len, "0x%03x\n", sw->vlan_index);
		break;
	case PROC_GET_VLAN_INFO:
		if (sw->vlan_dirty) {
			if (!entry->dirty) {
				sw_r_vlan_table(sw, sw->vlan_index, entry);
#ifdef USE_LOG_MASK
				entry->member =
					get_log_mask_from_phy(sw, entry->member);
#endif
			}
			sw->vlan_dirty = 0;
		}
		len += sprintf(buf + len,
			"%3x: 0x%02x %02x [%u]\n",
			sw->vlan_index, entry->fid, entry->member,
			entry->dirty ? 2 : entry->valid);
		break;
	}
	return len;
}  /* sysfs_vlan_read */

static int sysfs_vlan_write(struct ksz_sw *sw, int proc_num, int num)
{
	struct ksz_vlan_table *entry;
	u8 ports;
	int processed = true;

	entry = &sw->info->vlan_entry;
	switch (proc_num) {
	case PROC_SET_VLAN_VALID:
		if (num)
			entry->valid = 1;
		else
			entry->valid = 0;
		ports = entry->member;
#ifdef USE_LOG_MASK
		entry->member = get_phy_mask_from_log(sw, entry->member);
#endif
		sw_w_vlan_table(sw, sw->vlan_index, entry);
		entry->member = ports;
		sw->vlan_dirty = 0;
		break;
	case PROC_SET_VLAN_MEMBER:
		if (0 <= num && num <= sw->PORT_MASK) {
			entry->member = num;
			entry->dirty = 1;
		}
		break;
	case PROC_SET_VLAN_FID:
		if (0 <= num && num < 128) {
			entry->fid = num;
			entry->dirty = 1;
		}
		break;
	case PROC_SET_VLAN_VID:
		if (0 <= num && num < 0x1000) {
			sw->vlan_index = num;
			sw->vlan_dirty = 1;
		}
		break;
	default:
		processed = false;
		break;
	}
	return processed;
}  /* sysfs_vlan_write */

static ssize_t sysfs_acl_read(struct ksz_sw *sw, int proc_num, uint n,
	ssize_t len, char *buf)
{
	struct ksz_port_cfg *cfg;
	struct ksz_acl_table *acl;
	struct ksz_acl_table *action;
	struct ksz_acl_table *ruleset;
	uint port;
	int chk = 0;
	int type = SHOW_HELP_NONE;
	char note[40];

	note[0] = '\0';
	port = get_sysfs_port(sw, n);
	cfg = get_port_cfg(sw, port);
	acl = &cfg->acl_info[cfg->acl_index];
	action = &cfg->acl_info[cfg->acl_act_index];
	ruleset = &cfg->acl_info[cfg->acl_rule_index];
	switch (proc_num) {
	case PROC_SET_ACL_FIRST_RULE:
		chk = ruleset->first_rule;
		type = SHOW_HELP_HEX;
		break;
	case PROC_SET_ACL_RULESET:
		len += acl_ruleset_info(ruleset, cfg->acl_rule_index, buf, len);
		break;
	case PROC_SET_ACL_MODE:
		chk = acl->mode;
		if (sw->verbose) {
			switch (chk) {
			case 1:
				strcpy(note, " (layer 2)");
				break;
			case 2:
				strcpy(note, " (layer 3)");
				break;
			case 3:
				strcpy(note, " (layer 4)");
				break;
			default:
				strcpy(note, " (off)");
			}
		}
		type = SHOW_HELP_SPECIAL;
		break;
	case PROC_SET_ACL_ENABLE:
		chk = acl->enable;
		if (sw->verbose) {
			switch (chk) {
			case 1:
				strcpy(note, " (type; ip; tcp port)");
				break;
			case 2:
				strcpy(note, " (mac; src/dst; udp port)");
				break;
			case 3:
				strcpy(note, " (both; -; tcp seq)");
				break;
			default:
				strcpy(note, " (count; -; protocol)");
			}
		}
		type = SHOW_HELP_SPECIAL;
		break;
	case PROC_SET_ACL_SRC:
		chk = acl->src;
		type = SHOW_HELP_ON_OFF;
		break;
	case PROC_SET_ACL_EQUAL:
		chk = acl->equal;
		type = SHOW_HELP_ON_OFF;
		break;
	case PROC_SET_ACL_PRIO_MODE:
		chk = action->prio_mode;
		if (sw->verbose) {
			switch (chk) {
			case 1:
				strcpy(note, " (higher)");
				break;
			case 2:
				strcpy(note, " (lower)");
				break;
			case 3:
				strcpy(note, " (replace)");
				break;
			default:
				strcpy(note, " (disabled)");
			}
		}
		type = SHOW_HELP_SPECIAL;
		break;
	case PROC_SET_ACL_PRIO:
		chk = action->prio;
		type = SHOW_HELP_NUM;
		break;
	case PROC_SET_ACL_VLAN_PRIO_REPLACE:
		chk = action->vlan_prio_replace;
		type = SHOW_HELP_ON_OFF;
		break;
	case PROC_SET_ACL_VLAN_PRIO:
		chk = action->vlan_prio;
		type = SHOW_HELP_NUM;
		break;
	case PROC_SET_ACL_MAP_MODE:
		chk = action->map_mode;
		if (sw->verbose) {
			switch (chk) {
			case 1:
				strcpy(note, " (or)");
				break;
			case 2:
				strcpy(note, " (and)");
				break;
			case 3:
				strcpy(note, " (replace)");
				break;
			default:
				strcpy(note, " (disabled)");
			}
		}
		type = SHOW_HELP_SPECIAL;
		break;
	case PROC_SET_ACL_PORTS:
		chk = action->ports;
		type = SHOW_HELP_HEX_4;
		break;
	case PROC_SET_ACL_MAC_ADDR:
		len += sprintf(buf + len, "%02x:%02x:%02x:%02x:%02x:%02x\n",
			acl->mac[0], acl->mac[1], acl->mac[2],
			acl->mac[3], acl->mac[4], acl->mac[5]);
		break;
	case PROC_SET_ACL_TYPE:
		chk = acl->eth_type;
		type = SHOW_HELP_HEX_4;
		break;
	case PROC_SET_ACL_CNT:
		chk = acl->cnt;
		type = SHOW_HELP_NUM;
		break;
	case PROC_SET_ACL_MSEC:
		chk = acl->msec;
		type = SHOW_HELP_ON_OFF;
		break;
	case PROC_SET_ACL_INTR_MODE:
		chk = acl->intr_mode;
		type = SHOW_HELP_ON_OFF;
		break;
	case PROC_SET_ACL_IP_ADDR:
		len += sprintf(buf + len, "%u.%u.%u.%u\n",
			acl->ip4_addr[0], acl->ip4_addr[1],
			acl->ip4_addr[2], acl->ip4_addr[3]);
		break;
	case PROC_SET_ACL_IP_MASK:
		len += sprintf(buf + len, "%u.%u.%u.%u\n",
			acl->ip4_mask[0], acl->ip4_mask[1],
			acl->ip4_mask[2], acl->ip4_mask[3]);
		break;
	case PROC_SET_ACL_PROTOCOL:
		chk = acl->protocol;
		type = SHOW_HELP_NUM;
		break;
	case PROC_SET_ACL_PORT_MODE:
		chk = acl->port_mode;
		if (sw->verbose) {
			switch (chk) {
			case 1:
				strcpy(note, " (either)");
				break;
			case 2:
				strcpy(note, " (in range)");
				break;
			case 3:
				strcpy(note, " (out of range)");
				break;
			default:
				strcpy(note, " (disabled)");
			}
		}
		type = SHOW_HELP_SPECIAL;
		break;
	case PROC_SET_ACL_MAX_PORT:
		chk = acl->max_port;
		type = SHOW_HELP_NUM;
		break;
	case PROC_SET_ACL_MIN_PORT:
		chk = acl->min_port;
		type = SHOW_HELP_NUM;
		break;
	case PROC_SET_ACL_SEQNUM:
		chk = acl->seqnum;
		type = SHOW_HELP_NUM;
		break;
	case PROC_SET_ACL_TCP_FLAG_ENABLE:
		chk = acl->tcp_flag_enable;
		type = SHOW_HELP_ON_OFF;
		break;
	case PROC_SET_ACL_TCP_FLAG:
		chk = acl->tcp_flag;
		type = SHOW_HELP_HEX;
		break;
	case PROC_SET_ACL_TCP_FLAG_MASK:
		chk = acl->tcp_flag_mask;
		type = SHOW_HELP_HEX;
		break;
	case PROC_SET_ACL_INDEX:
		chk = cfg->acl_index;
		type = SHOW_HELP_HEX;
		break;
	case PROC_SET_ACL_ACTION_INDEX:
		chk = cfg->acl_act_index;
		type = SHOW_HELP_HEX;
		break;
	case PROC_SET_ACL_ACTION:
		len += acl_action_info(action, cfg->acl_act_index, buf, len);
		break;
	case PROC_SET_ACL_RULE_INDEX:
		chk = cfg->acl_rule_index;
		type = SHOW_HELP_HEX;
		break;
	case PROC_SET_ACL_INFO:
		len += acl_info(acl, cfg->acl_index, buf, len);
		break;
	case PROC_GET_ACL_TABLE:
		len = sw_d_acl_table(sw, port, buf, len);
		break;
	}
	return sysfs_show(len, buf, type, chk, note, sw->verbose);
}  /* sysfs_acl_read */

static int sysfs_acl_write(struct ksz_sw *sw, int proc_num, uint n, int num,
	const char *buf)
{
	struct ksz_port_cfg *cfg;
	struct ksz_acl_table *acl;
	struct ksz_acl_table *action;
	struct ksz_acl_table *ruleset;
	uint port;
	int acl_on = 0;
	int processed = true;

	port = get_sysfs_port(sw, n);
	cfg = get_port_cfg(sw, port);
	acl = &cfg->acl_info[cfg->acl_index];
	action = &cfg->acl_info[cfg->acl_act_index];
	ruleset = &cfg->acl_info[cfg->acl_rule_index];
	switch (proc_num) {
	case PROC_SET_ACL_RULESET:
	case PROC_SET_ACL_MODE:
	case PROC_SET_ACL_ACTION:
	case PROC_SET_ACL_INFO:
		sw->ops->acquire(sw);
		acl_on = port_chk_acl(sw, port);
		if (!acl_on)
			port_cfg_acl(sw, port, true);
		sw->ops->release(sw);
		break;
	}
	switch (proc_num) {
	case PROC_SET_ACL_FIRST_RULE:
		ruleset->first_rule = (u16) num;
		ruleset->ruleset_changed = 1;
		break;
	case PROC_SET_ACL_RULESET:
		sscanf(buf, "%x", &num);
		ruleset->ruleset = (u16) num;
		sw_w_acl_ruleset(sw, port, cfg->acl_rule_index, ruleset);
		break;
	case PROC_SET_ACL_MODE:
		if (0 <= num && num < 4) {
			acl->mode = num;
			sw_w_acl_rule(sw, port, cfg->acl_index, acl);
		}
		break;
	case PROC_SET_ACL_ENABLE:
		if (0 <= num && num < 4) {
			acl->enable = num;
			acl->changed = 1;
		}
		break;
	case PROC_SET_ACL_SRC:
		if (num)
			acl->src = 1;
		else
			acl->src = 0;
		acl->changed = 1;
		break;
	case PROC_SET_ACL_EQUAL:
		if (num)
			acl->equal = 1;
		else
			acl->equal = 0;
		acl->changed = 1;
		break;
	case PROC_SET_ACL_PRIO_MODE:
		if (0 <= num && num < 4) {
			action->prio_mode = num;
			action->action_changed = 1;
		}
		break;
	case PROC_SET_ACL_PRIO:
		if (0 <= num && num < 4) {
			action->prio = num;
			action->action_changed = 1;
		}
		break;
	case PROC_SET_ACL_VLAN_PRIO_REPLACE:
		if (num)
			action->vlan_prio_replace = 1;
		else
			action->vlan_prio_replace = 0;
		action->action_changed = 1;
		break;
	case PROC_SET_ACL_VLAN_PRIO:
		if (0 <= num && num < 4) {
			action->vlan_prio = num;
			action->action_changed = 1;
		}
		break;
	case PROC_SET_ACL_MAP_MODE:
		if (0 <= num && num < 4) {
			action->map_mode = num;
			action->action_changed = 1;
		}
		break;
	case PROC_SET_ACL_PORTS:
		sscanf(buf, "%x", &num);
		if (0 <= num && num <= sw->PORT_MASK) {
			action->ports = (u16) num;
			action->action_changed = 1;
		}
		break;
	case PROC_SET_ACL_MAC_ADDR:
	{
		int i;
		int n[6];

		i = sscanf(buf, "%x:%x:%x:%x:%x:%x",
			&n[0], &n[1], &n[2], &n[3], &n[4], &n[5]);
		if (6 == i) {
			for (i = 0; i < 6; i++)
				acl->mac[i] = (u8) n[i];
			acl->changed = 1;
		}
		break;
	}
	case PROC_SET_ACL_TYPE:
		sscanf(buf, "%x", &num);
		acl->eth_type = (u16) num;
		acl->changed = 1;
		break;
	case PROC_SET_ACL_CNT:
		if (0 <= num && num <= ACL_CNT_M) {
			acl->cnt = (u16) num;
			acl->changed = 1;
		}
		break;
	case PROC_SET_ACL_MSEC:
		if (num)
			acl->msec = 1;
		else
			acl->msec = 0;
		acl->changed = 1;
		break;
	case PROC_SET_ACL_INTR_MODE:
		if (num)
			acl->intr_mode = 1;
		else
			acl->intr_mode = 0;
		acl->changed = 1;
		break;
	case PROC_SET_ACL_IP_ADDR:
	{
		int i;
		int n[4];

		i = sscanf(buf, "%u.%u.%u.%u",
			&n[0], &n[1], &n[2], &n[3]);
		if (4 == i) {
			for (i = 0; i < 4; i++)
				acl->ip4_addr[i] = (u8) n[i];
			acl->changed = 1;
		}
		break;
	}
	case PROC_SET_ACL_IP_MASK:
	{
		int i;
		int n[4];

		i = sscanf(buf, "%u.%u.%u.%u",
			&n[0], &n[1], &n[2], &n[3]);
		if (4 == i) {
			for (i = 0; i < 4; i++)
				acl->ip4_mask[i] = (u8) n[i];
			acl->changed = 1;
		}
		break;
	}
	case PROC_SET_ACL_PROTOCOL:
		acl->protocol = (u8) num;
		acl->changed = 1;
		break;
	case PROC_SET_ACL_PORT_MODE:
		if (0 <= num && num < 4) {
			acl->port_mode = num;
			acl->changed = 1;
		}
		break;
	case PROC_SET_ACL_MAX_PORT:
		acl->max_port = (u16) num;
		acl->changed = 1;
		break;
	case PROC_SET_ACL_MIN_PORT:
		acl->min_port = (u16) num;
		acl->changed = 1;
		break;
	case PROC_SET_ACL_SEQNUM:
		acl->seqnum = num;
		acl->changed = 1;
		break;
	case PROC_SET_ACL_TCP_FLAG_ENABLE:
		if (num)
			acl->tcp_flag_enable = 1;
		else
			acl->tcp_flag_enable = 0;
		acl->changed = 1;
		break;
	case PROC_SET_ACL_TCP_FLAG:
		acl->tcp_flag = (u8) num;
		acl->changed = 1;
		break;
	case PROC_SET_ACL_TCP_FLAG_MASK:
		acl->tcp_flag_mask = (u8) num;
		acl->changed = 1;
		break;
	case PROC_SET_ACL_INDEX:
		if (0 <= num && num < ACL_TABLE_ENTRIES) {
			cfg->acl_index = num;
		}
		break;
	case PROC_SET_ACL_ACTION_INDEX:
		if (0 <= num && num < ACL_TABLE_ENTRIES) {
			cfg->acl_act_index = num;
		}
		break;
	case PROC_SET_ACL_ACTION:
		if (num)
			sw_w_acl_action(sw, port, cfg->acl_act_index, action);
		else
			sw_r_acl_table(sw, port, cfg->acl_act_index, action);
		break;
	case PROC_SET_ACL_RULE_INDEX:
		if (0 <= num && num < ACL_TABLE_ENTRIES) {
			cfg->acl_rule_index = num;
		}
		break;
	case PROC_SET_ACL_INFO:
		sw_r_acl_table(sw, port, cfg->acl_index, acl);
		break;
	default:
		processed = false;
		break;
	}
	switch (proc_num) {
	case PROC_SET_ACL_RULESET:
	case PROC_SET_ACL_MODE:
	case PROC_SET_ACL_ACTION:
	case PROC_SET_ACL_INFO:
		if (!acl_on) {
			sw->ops->acquire(sw);
			port_cfg_acl(sw, port, false);
			sw->ops->release(sw);
		}
		break;
	}
	return processed;
}  /* sysfs_acl_write */

static void sw_cfg_mac(struct ksz_sw *sw, u8 index, u8 *dest, u32 ports,
	int override, int use_fid, u16 fid)
{
	struct ksz_mac_table mac;

	if (index >= STATIC_MAC_TABLE_ENTRIES)
		return;
	memset(&mac, 0, sizeof(struct ksz_mac_table));
	memcpy(mac.addr, dest, ETH_ALEN);
	mac.ports = (u8) ports;
	mac.override = override;
	mac.use_fid = use_fid;
	mac.fid = (u8) fid;
	mac.valid = mac.ports != 0;
	if (!mac.valid && mac.override) {
		mac.override = 0;
		mac.valid = 1;
	}
	sw_w_sta_mac_table(sw, index, &mac);
}  /* sw_cfg_mac */

static void sw_cfg_vlan(struct ksz_sw *sw, u8 index, u16 vid, u16 fid,
	u32 ports)
{
	struct ksz_vlan_table vlan;

	if (0xffff == ports)
		ports = sw->PORT_MASK;
	memset(&vlan, 0, sizeof(struct ksz_vlan_table));
	vlan.vid = vid;
	vlan.fid = (u8) fid;
	vlan.member = (u8)(ports & sw->PORT_MASK);
	vlan.valid = ports != 0;
	sw_w_vlan_table(sw, vlan.vid, &vlan);
}  /* sw_cfg_vlan */

static u8 sw_alloc_mac(struct ksz_sw *sw)
{
	int i;

	for (i = 1; i < STATIC_MAC_TABLE_ENTRIES; i++) {
		if (!(sw->info->mac_table_used & (1 << i))) {
			sw->info->mac_table_used |= (1 << i);
			return i;
		}
	}

	/* Reject request. */
	return 0;
}  /* sw_alloc_mac */

static void sw_free_mac(struct ksz_sw *sw, u8 index)
{
	sw->info->mac_table_used &= ~(1 << index);
}  /* sw_free_mac */

static u8 sw_alloc_vlan(struct ksz_sw *sw)
{
	return 1;
}  /* sw_alloc_vlan */

static void sw_free_vlan(struct ksz_sw *sw, u8 index)
{
}  /* sw_free_vlan */

static u16 sw_alloc_fid(struct ksz_sw *sw, u16 vid)
{
	int x;
	int y;
	u16 fid;

	if (sw->info->fid_cnt + 2 == FID_ENTRIES)
		return 0;
	fid = vid & (FID_ENTRIES - 1);
	if (vid < 2)
		fid = 100;
	x = fid / FID_IN_DATA;
	y = fid % FID_IN_DATA;
	while (sw->info->fid[x] & (1 << y)) {
		++fid;
		++y;
		if (y >= FID_IN_DATA) {
			y = 0;
			++x;
		}
	}
	sw->info->fid[x] |= (1 << y);
	++sw->info->fid_cnt;
	return fid;
}  /* sw_alloc_fid */

static void sw_free_fid(struct ksz_sw *sw, u16 fid)
{
	int x;
	int y;

	x = fid / FID_IN_DATA;
	y = fid % FID_IN_DATA;
	if (sw->info->fid[x] & (1 << y)) {
		sw->info->fid[x] &= ~(1 << y);
		--sw->info->fid_cnt;
	}
}  /* sw_free_fid */

static const u8 *sw_get_br_id(struct ksz_sw *sw)
{
	u8 id[8];
	const u8* ret = id;

	memcpy(&id[2], sw->info->mac_addr, ETH_ALEN);
	id[0] = 0x80;
	id[1] = 0x00;

#ifdef CONFIG_KSZ_STP
	ret = stp_br_id(&sw->info->rstp);
#endif
	return ret;
}  /* sw_get_br_id */

static void sw_from_backup(struct ksz_sw *sw, uint p)
{
#ifdef CONFIG_KSZ_MRP
	if (sw->features & MRP_SUPPORT) {
		struct mrp_info *mrp = &sw->mrp;

		mrp->ops->from_backup(mrp, p);
	}
#endif
}  /* sw_from_backup */

static void sw_to_backup(struct ksz_sw *sw, uint p)
{
#ifdef CONFIG_KSZ_MRP
	if (sw->features & MRP_SUPPORT) {
		struct mrp_info *mrp = &sw->mrp;

		mrp->ops->to_backup(mrp, p);
	}
#endif
}  /* sw_to_backup */

static void sw_from_designated(struct ksz_sw *sw, uint p, bool alt)
{
#ifdef CONFIG_KSZ_MRP
	if (sw->features & MRP_SUPPORT) {
		struct mrp_info *mrp = &sw->mrp;

		mrp->ops->from_designated(mrp, p, alt);
	}
#endif
}  /* sw_from_designated */

static void sw_to_designated(struct ksz_sw *sw, uint p)
{
#ifdef CONFIG_KSZ_MRP
	if (sw->features & MRP_SUPPORT) {
		struct mrp_info *mrp = &sw->mrp;

		mrp->ops->to_designated(mrp, p);
	}
#endif
}  /* sw_to_designated */

static void sw_tc_detected(struct ksz_sw *sw, uint p)
{
#ifdef CONFIG_KSZ_MRP
	if (sw->features & MRP_SUPPORT) {
		struct mrp_info *mrp = &sw->mrp;

		mrp->ops->tc_detected(mrp, p);
	}
#endif
}  /* sw_tc_detected */

static int sw_get_tcDetected(struct ksz_sw *sw, uint p)
{
	int ret = false;

#ifdef CONFIG_KSZ_STP
	if (sw->features & STP_SUPPORT) {
		struct ksz_stp_info *info = &sw->info->rstp;

		ret = info->ops->get_tcDetected(info, p);
	}
#endif
	return ret;
}  /* sw_get_tcDetected */

static void sw_ena_intr(struct ksz_sw *sw)
{
	struct sw_priv *ks = container_of(sw, struct sw_priv, sw);

	sw->reg->w8(sw, REG_INT_ENABLE, ks->intr_mask);
	sw->reg->w8(sw, REG_ACL_INT_ENABLE, INT_PORT_ALL);
}  /* sw_ena_intr */

enum {
	KSZ8795_SW_CHIP,
	KSZ8794_SW_CHIP,
	KSZ8765_SW_CHIP,
};

static int sw_get_id(struct ksz_sw *sw, u8 *id1, u8 *id2, char *name)
{
	int id;
	int i;
	int j;

	id = sw->reg->r16(sw, REG_CHIP_ID0);
	i = id;
	j = i & SW_CHIP_ID_M;
	i >>= 8;
	*id1 = (u8) i;
	*id2 = (u8) j;
	if (sw->chip_id == KSZ8795_SW_CHIP)
		strcat(name, "8795");
	else if (sw->chip_id == KSZ8794_SW_CHIP)
		strcat(name, "8794");
	else if (sw->chip_id == KSZ8765_SW_CHIP)
		strcat(name, "8765");
	else
		strcat(name, "87xx");
	return id;
}  /* sw_get_id */

static void sw_cfg_tail_tag(struct ksz_sw *sw, bool enable)
{
	/* Switch marks the maximum frame with extra byte as oversize. */
	sw_cfg(sw, REG_SW_CTRL_2, SW_LEGAL_PACKET_DISABLE, enable);
	sw_cfg(sw, S_TAIL_TAG_CTRL, SW_TAIL_TAG_ENABLE, enable);
}

static void sw_cfg_each_port(struct ksz_sw *sw, uint p, bool cpu)
{
	if (cpu)
		p = sw->HOST_PORT;
	else {
		p = get_phy_port(sw, p + 1);
		sw->info->port_cfg[p].vid_member = (1 << p);
	}
	port_set_stp_state(sw, p, STP_STATE_SIMPLE);
}

static int sw_port_to_phy_addr(struct ksz_sw *sw, uint p)
{
	p = get_phy_port(sw, p + 1);
	if (p <= sw->mib_port_cnt)
		return p;
	return -1;
}

static void sw_set_port_addr(struct ksz_sw *sw, uint p, u8 *addr)
{
}

static void sw_set_multi(struct ksz_sw *sw, struct net_device *dev,
	struct ksz_port *priv)
{
	struct ksz_mac_table *entry;
	struct ksz_alu_table *alu;
	struct netdev_hw_addr *ha;
	int i;
	int found;
	int owner;
	int port = 0;
	struct ksz_sw_info *info = sw->info;

	/* This device is associated with a switch port. */
	if (1 == priv->port_cnt)
		port = priv->first_port;
	owner = 1 << port;

	/* Remove old multicast entries. */
	for (i = SWITCH_MAC_TABLE_ENTRIES; i < info->multi_net; i++) {
		entry = &info->mac_table[i];
		alu = &info->alu_table[i];
		if (alu->valid && (alu->owner & owner)) {
			/* Remove device ownership. */
			alu->owner &= ~owner;
			if (!port)
				alu->forward &= ~FWD_MAIN_DEV;
			else if (alu->owner <= 1)
				alu->forward &= ~FWD_STP_DEV;
			if (!alu->owner) {
				alu->valid = 0;
				entry->ports = 0;
				entry->valid = 0;
			}
		}
	}
	netdev_for_each_mc_addr(ha, dev) {
		if (!(*ha->addr & 1))
			continue;
		if (info->multi_net == info->multi_sys)
			break;
		found = 0;
		for (i = 0; i < MULTI_MAC_TABLE_ENTRIES; i++) {
			entry = &info->mac_table[i];
			alu = &info->alu_table[i];
			if (alu->valid &&
			    !memcmp(entry->addr, ha->addr, ETH_ALEN)) {
				found = i + 1;
				break;
			}
			if (!alu->valid && !found &&
			    i >= SWITCH_MAC_TABLE_ENTRIES &&
			    i < info->multi_net)
				found = i + 1;
		}
		if (!found) {
			info->multi_net++;
			found = info->multi_net;
		}
		found--;
		if (found >= SWITCH_MAC_TABLE_ENTRIES &&
		    found < info->multi_net) {
			entry = &info->mac_table[found];
			alu = &info->alu_table[found];
			if (port)
				alu->forward |= FWD_STP_DEV;
			else
				alu->forward |= FWD_MAIN_DEV;
			alu->owner |= owner;
			alu->valid = 1;
			memcpy(entry->addr, ha->addr, ETH_ALEN);
			entry->ports = sw->PORT_MASK;
			entry->valid = 1;
		}
	}
}  /* sw_set_multi */

static struct net_device *sw_rx_dev(struct ksz_sw *sw, u8 *data, u32 *len,
	int *tag, int *port)
{
	u16 proto;
	u16* proto_loc;
	struct net_device *dev;
	struct vlan_ethhdr *vlan = (struct vlan_ethhdr *) data;
	int index = -1;
	int vid = 0;

	proto_loc = &vlan->h_vlan_proto;
	proto = htons(*proto_loc);

	/* Get received port number. */
	if (sw->overrides & TAIL_TAGGING) {
		(*len)--;
		*tag = data[*len];

		/* In case tagging is not working right. */
		if (*tag >= SWITCH_PORT_NUM)
			*tag = 0;

		/* Save receiving port. */
		*port = *tag;
		index = sw->info->port_cfg[*tag].index;
	}

	/* Determine network device from VLAN id. */
	if (index < 0) {
		index = 0;
		if (vlan->h_vlan_proto == htons(ETH_P_8021Q)) {
			u16 vlan_tci = ntohs(vlan->h_vlan_TCI);

			vid = vlan_tci & VLAN_VID_MASK;
			proto_loc = &vlan->h_vlan_encapsulated_proto;
			proto = htons(*proto_loc);
		}
		if (vid && (sw->features & SW_VLAN_DEV)) {
			struct ksz_dev_map *map;
			int p;

			for (p = 0; p < sw->eth_cnt; p++) {
				map = &sw->eth_maps[p];
				if (vid == map->vlan) {
					*port = map->first;
					p = get_phy_port(sw, *port);
					*port = p;
					index = sw->info->port_cfg[p].index;
					break;
				}
			}
		}
	}
	if (index >= sw->dev_count + sw->dev_offset) {
		printk(KERN_INFO "  [%s] netdev not correct\n", __func__);
		BUG();
	}
	dev = sw->netdev[index];
#ifdef CONFIG_KSZ_DLR
	if (proto == DLR_TAG_TYPE)
		return dev;
#endif
	if (!(sw->features & VLAN_PORT_TAGGING) ||
	    !(sw->vlan_id & (1 << *tag))) {
		*tag = 0;
	}
	return dev;
}  /* sw_rx_dev */

static int pkt_matched(struct sk_buff *skb, struct net_device *dev, void *ptr,
	int (*match_multi)(void *ptr, u8 *addr), u8 h_promiscuous)
{
	int drop = false;
	u8 bcast_addr[] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };

	if (skb->data[0] & 0x01) {
		if (memcmp(skb->data, bcast_addr, ETH_ALEN))
			drop = match_multi(ptr, skb->data);
	} else if (h_promiscuous && memcmp(skb->data, dev->dev_addr, ETH_ALEN))
		drop = true;
	if (drop)
		return 0;
	return skb->len;
}  /* pkt_matched */

static int sw_match_pkt(struct ksz_sw *sw, struct net_device **dev,
	void **priv, int (*get_promiscuous)(void *ptr),
	int (*match_multi)(void *ptr, u8 *data), struct sk_buff *skb,
	u8 h_promiscuous)
{
	int s_promiscuous;

	if (sw->dev_count <= 1)
		return true;
	s_promiscuous = get_promiscuous(*priv);
	if (!s_promiscuous && !pkt_matched(skb, *dev, *priv, match_multi,
			h_promiscuous)) {
		int matched = false;

		/* There is a parent network device. */
		if (sw->dev_offset) {
			matched = true;
			*dev = sw->netdev[0];
			*priv = netdev_priv(*dev);
			s_promiscuous = get_promiscuous(*priv);
			if (!s_promiscuous && !pkt_matched(skb, *dev, *priv,
					match_multi, h_promiscuous))
				matched = false;
		}
		return matched;
	}
	return true;
}  /* sw_match_pkt */

static struct net_device *sw_parent_rx(struct ksz_sw *sw,
	struct net_device *dev, struct sk_buff *skb, int *forward,
	struct net_device **parent_dev, struct sk_buff **parent_skb)
{
	if (sw->dev_offset && dev != sw->netdev[0]) {
		*parent_dev = sw->netdev[0];
		if (!*forward)
			*forward = FWD_MAIN_DEV | FWD_STP_DEV;
		if ((*forward & (FWD_MAIN_DEV | FWD_STP_DEV)) ==
		    (FWD_MAIN_DEV | FWD_STP_DEV))
			*parent_skb = skb_clone(skb, GFP_ATOMIC);
		else if (!(*forward & FWD_STP_DEV))
			dev = *parent_dev;
		else
			*forward &= ~FWD_VLAN_DEV;
	}
	return dev;
}  /* sw_parent_rx */

static int sw_port_vlan_rx(struct ksz_sw *sw, struct net_device *dev,
	struct net_device *parent_dev, struct sk_buff *skb, int forward,
	int tag, void *ptr, void (*rx_tstamp)(void *ptr, struct sk_buff *skb))
{
	struct sk_buff *vlan_skb;
	struct net_device *vlan_dev = dev;

	/* Add VLAN tag manually. */
	if (!(forward & FWD_VLAN_DEV))
		return false;

	if (!tag || !(sw->features & VLAN_PORT))
		return false;
	tag += VLAN_PORT_START;

	/* Only forward to one network device. */
	if (!(forward & FWD_MAIN_DEV)) {
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), tag);
		return true;
	}
	vlan_skb = skb_clone(skb, GFP_ATOMIC);
	if (!vlan_skb)
		return false;
	skb_reset_mac_header(vlan_skb);
	__vlan_hwaccel_put_tag(vlan_skb, htons(ETH_P_8021Q), tag);
	if (parent_dev && dev != parent_dev) {
		vlan_dev = parent_dev;
		vlan_skb->dev = vlan_dev;
	}
	vlan_skb->protocol = eth_type_trans(vlan_skb, vlan_dev);
	netif_rx(vlan_skb);
	return true;
}  /* sw_port_vlan_rx */

static int sw_drv_rx(struct ksz_sw *sw, struct sk_buff *skb, uint port)
{
	int ret = 1;

#ifdef CONFIG_KSZ_STP
	if (sw->features & STP_SUPPORT) {
		ret = stp_rcv(&sw->info->rstp, skb, port);
		if (!ret)
			return ret;
	}
#endif
#ifdef PROC_MRP
	if (sw->features & MRP_SUPPORT) {
		ret = mrp_rcv(&sw->mrp, skb, port);
		if (!ret)
			return ret;
	}
#endif
#ifdef CONFIG_KSZ_DLR
	if (sw->features & DLR_HW) {
		ret = dlr_rcv(&sw->info->dlr, skb, port);
		if (!ret)
			return ret;
	}
#endif

	/* Need to remove VLAN tag if not using tail tag. */
	if (sw->dev_count > 1 && (sw->features & SW_VLAN_DEV) &&
	    !(sw->overrides & TAIL_TAGGING)) {
		struct vlan_ethhdr *vlan = (struct vlan_ethhdr *) skb->data;

		if (vlan->h_vlan_proto == htons(ETH_P_8021Q)) {
			int p;
			int vid;
			struct ethhdr *eth;
			u16 vlan_tci = ntohs(vlan->h_vlan_TCI);

			vid = vlan_tci & VLAN_VID_MASK;
			for (p = 0; p < sw->eth_cnt; p++) {
				if (vid == sw->eth_maps[p].vlan) {
					eth = (struct ethhdr *)
						skb_pull(skb, VLAN_HLEN);
					memmove(eth, vlan, 12);
					break;
				}
			}
		}
	}
	return ret;
}  /* sw_drv_rx */

static int sw_get_mtu(struct ksz_sw *sw)
{
	int need_tail_tag = false;
	int header = 0;
	int mtu = 0;

#ifdef CONFIG_KSZ_DLR
	if (sw->features & DLR_HW)
		need_tail_tag = true;
#endif
	if (sw->dev_count > 1 && !(sw->features & SW_VLAN_DEV))
		need_tail_tag = true;
	if (sw->features & VLAN_PORT_TAGGING)
		need_tail_tag = true;
	if (sw->features & (STP_SUPPORT | DSA_SUPPORT))
		need_tail_tag = true;
	if (need_tail_tag)
		mtu += 1;
	if (sw->features & SW_VLAN_DEV)
		if (header < VLAN_HLEN)
			header = VLAN_HLEN;
	mtu += header;
	return mtu;
}  /* sw_get_mtu */

static int sw_get_tx_len(struct ksz_sw *sw, struct sk_buff *skb, uint port,
	int *header)
{
	int len = skb->len;
	int hlen = 0;

	if (sw->features & SW_VLAN_DEV)
		hlen = VLAN_HLEN;
	*header += hlen;
	if (!(sw->overrides & TAIL_TAGGING))
		return len;
	if (len < 60)
		len = 60;
	len += 1;
	return len;
}  /* sw_get_tx_len */

static void sw_add_tail_tag(struct ksz_sw *sw, struct sk_buff *skb, uint ports)
{
	u8 *trailer;
	int len = 1;

	trailer = skb_put(skb, len);
	if (!ports)
		ports = TAIL_TAG_LOOKUP;
	else if (ports & TAIL_TAG_SET_OVERRIDE) {
		ports &= ~TAIL_TAG_SET_OVERRIDE;
		ports |= TAIL_TAG_OVERRIDE;
	}
	trailer[0] = (u8) ports;
}  /* sw_add_tail_tag */

static int sw_get_tail_tag(u8 *trailer, int *port)
{
	int len = 1;

	*port = *trailer;
	return len;
}  /* sw_get_tail_tag */

static void sw_add_vid(struct ksz_sw *sw, u16 vid)
{
	if ((sw->features & VLAN_PORT) && vid >= VLAN_PORT_START) {
		vid -= VLAN_PORT_START;
		if (vid <= SWITCH_PORT_NUM)
			sw->vlan_id |= (1 << vid);
	}
}  /* sw_add_vid */

static void sw_kill_vid(struct ksz_sw *sw, u16 vid)
{
	if ((sw->features & VLAN_PORT) && vid >= VLAN_PORT_START) {
		vid -= VLAN_PORT_START;
		if (vid <= SWITCH_PORT_NUM)
			sw->vlan_id &= ~(1 << vid);
	}
}  /* sw_kill_vid */

static int add_frag(void *from, char *to, int offset, int len, int odd,
	struct sk_buff *skb)
{
	memcpy(to + offset, from, len);
	return 0;
}

static struct sk_buff *sw_ins_vlan(struct ksz_sw *sw, uint port,
	struct sk_buff *skb)
{
	port = get_phy_port(sw, port);

	/* Need to insert VLAN tag. */
	if (sw->dev_count > 1 && (sw->features & SW_VLAN_DEV)) {
		u16 vid;
		struct vlan_ethhdr *vlan;
		struct ethhdr *eth = (struct ethhdr *) skb->data;

		vid = sw->info->port_cfg[port].vid;
		vlan = (struct vlan_ethhdr *) skb_push(skb, VLAN_HLEN);
		memmove(vlan, eth, 12);
		vlan->h_vlan_TCI = htons(vid);
		vlan->h_vlan_proto = htons(ETH_P_8021Q);
	}
	return skb;
}  /* sw_ins_vlan */

static struct sk_buff *sw_check_skb(struct ksz_sw *sw, struct sk_buff *skb,
	struct ksz_port *priv, void *ptr,
	int (*update_msg)(u8 *data, u32 port, u32 overrides))
{
	int len;
	uint port;
	u8 dest;
	struct sk_buff *org_skb;
	int update_dst = (sw->overrides & TAIL_TAGGING);

	if (!update_dst)
		return sw_ins_vlan(sw, priv->first_port, skb);

#ifdef CONFIG_KSZ_STP
	if (skb->protocol == htons(STP_TAG_TYPE))
		return skb;
#endif
#ifdef CONFIG_KSZ_DLR
	if (skb->protocol == htons(DLR_TAG_TYPE))
		return skb;
#endif

	org_skb = skb;
	port = 0;

	/* This device is associated with a switch port. */
	if (1 == priv->port_cnt)
		port = priv->first_port;

	do {
		u16 prio;
		u16 vid;
		uint i;
		uint p;
		u32 features = sw->features;

		p = get_phy_port(sw, priv->first_port);
		i = sw->info->port_cfg[p].index;
		if (sw->features & SW_VLAN_DEV)
			features = sw->eth_maps[i].proto;
		if (!(features & VLAN_PORT) || port || vlan_get_tag(skb, &vid))
			break;
		prio = vid & VLAN_PRIO_MASK;
		vid &= VLAN_VID_MASK;
		if (vid < VLAN_PORT_START)
			break;
		vid -= VLAN_PORT_START;
		if (!vid || vid > SWITCH_PORT_NUM)
			break;
		port = vid;

		if (sw->vid || prio) {
			struct vlan_ethhdr *vlan =
				(struct vlan_ethhdr *) skb->data;
			u16 vlan_tci = ntohs(vlan->h_vlan_TCI);

			vlan_tci &= ~VLAN_VID_MASK;
			vlan_tci |= sw->vid;
			vlan->h_vlan_TCI = htons(vlan_tci);

		/* Need to remove VLAN tag manually. */
		} else if (!(sw->overrides & TAG_REMOVE)) {
			u8 *data;

			len = VLAN_ETH_HLEN - 2;
			data = &skb->data[len];
			memmove(data - VLAN_HLEN, data, skb->len - len);
			skb->len -= VLAN_HLEN;
		}
	} while (0);

	dest = 0;
	if (port) {
		port = get_phy_port(sw, port);
		dest = 1 << port;
	}

	/* Socket buffer has no fragments. */
	if (!skb_shinfo(skb)->nr_frags) {
#ifdef NET_SKBUFF_DATA_USES_OFFSET
		len = skb_end_pointer(skb) - skb->data;
#else
		len = skb->end - skb->data;
#endif
		if (skb->len + 1 > len || len < 60 + 1) {
			len = (skb->len + 7) & ~3;
			if (len < 64)
				len = 64;
			skb = dev_alloc_skb(len);
			if (!skb)
				return NULL;
			memcpy(skb->data, org_skb->data, org_skb->len);
			skb->len = org_skb->len;
			copy_old_skb(org_skb, skb);
		}
		if (skb->len < 60) {
			memset(&skb->data[skb->len], 0, 60 - skb->len);
			skb->len = 60;
		}
		len = skb->len;
	}
	if (!dest) {
		dest = TAIL_TAG_LOOKUP;
	}
	if (dest == TAIL_TAG_LOOKUP) {
		/* Use VLAN for port forwarding if not specified directly. */
		skb = sw_ins_vlan(sw, priv->first_port, skb);
		if (len != skb->len)
			len = skb->len;
	}
	if (!skb_shinfo(skb)->nr_frags) {
		skb->data[len] = dest;
		skb_put(skb, 1);
	} else {
		struct sock dummy;
		struct sock *sk;

		sk = skb->sk;
		if (!sk) {
			sk = &dummy;
			sk->sk_allocation = GFP_KERNEL;
			atomic_set(&sk->sk_wmem_alloc, 1);
		}

		/* Clear last tag. */
		sw->tx_pad[sw->tx_start] = 0;
		sw->tx_start = 0;
		len = 1;
		if (skb->len < 60) {
			sw->tx_start = 60 - skb->len;
			len += sw->tx_start;
		}
		sw->tx_pad[sw->tx_start] = dest;
		skb_append_datato_frags(sk, skb, add_frag, sw->tx_pad, len);
	}
	return skb;
}  /* sw_check_skb */

static struct sk_buff *sw_check_tx(struct ksz_sw *sw, struct net_device *dev,
	struct sk_buff *skb, struct ksz_port *priv)
{
	void *ptr = NULL;
	int (*update_msg)(u8 *data, u32 port, u32 overrides) = NULL;

	return sw_check_skb(sw, skb, priv, ptr, update_msg);
}  /* sw_check_tx */

static struct sk_buff *sw_final_skb(struct ksz_sw *sw, struct sk_buff *skb,
	struct net_device *dev, struct ksz_port *port)
{
	skb = sw->net_ops->check_tx(sw, dev, skb, port);
	if (!skb)
		return NULL;
	return skb;
}  /* sw_final_skb */

static void sw_start(struct ksz_sw *sw, u8 *addr)
{
	int need_tail_tag = false;
	int need_vlan = false;

	sw->ops->acquire(sw);
	sw_setup(sw);
	sw_enable(sw);
	sw_set_addr(sw, addr);
#if 0
	if (1 == sw->dev_count)
		sw_cfg_self_filter(sw, true);
#endif
#ifdef CONFIG_KSZ_DLR
	if (sw->features & DLR_HW)
		need_tail_tag = true;
#endif
	if (sw->dev_count > 1 && !(sw->features & SW_VLAN_DEV))
		need_tail_tag = true;
	if (sw->features & VLAN_PORT) {
		if (sw->features & VLAN_PORT_REMOVE_TAG) {
			uint n;
			uint p;

			for (n = 1; n <= sw->mib_port_cnt; n++) {
				p = get_phy_port(sw, n);
				port_cfg_rmv_tag(sw, p, true);
			}
			sw->overrides |= TAG_REMOVE;
		}
		if (sw->features & VLAN_PORT_TAGGING)
			need_tail_tag = true;
	}
	if (sw->features & SW_VLAN_DEV) {
		struct ksz_vlan_table entry;
		struct ksz_dev_map *map;
		int i;
		int p;
		uint port;
		uint q;

		memset(&entry, 0, sizeof(struct ksz_vlan_table));
		for (p = 0; p < sw->eth_cnt; p++) {

			/* Not really using VLAN. */
			if (1 == sw->eth_maps[p].vlan)
				continue;
			sw->ops->release(sw);

			map = &sw->eth_maps[p];

			/*
			 * Setting FID allows same MAC address in different
			 * VLANs.
			 */
			entry.fid = map->vlan & (FID_ENTRIES - 1);
			entry.member = sw->HOST_MASK | map->mask;
			entry.valid = 1;
			sw_w_vlan_table(sw, map->vlan, &entry);
			sw->ops->acquire(sw);
			for (i = 0, q = map->first;
			     i < map->cnt; i++, q++) {
				port = get_phy_port(sw, q);
				sw_cfg_def_vid(sw, port, map->vlan);
#ifdef CONFIG_KSZ_DLR
				if ((sw->eth_maps[p].proto & DLR_HW))
					continue;
#endif
				port_cfg_rmv_tag(sw, port, true);
			}
		}

		/* Use VLAN tag to determine the network device. */
		if (!need_tail_tag)
			port_cfg_ins_tag(sw, sw->HOST_PORT, true);
		need_vlan = true;
	}
	if (sw->features & (STP_SUPPORT | DSA_SUPPORT))
		need_tail_tag = true;
	if (sw->features & (DLR_HW))
		need_vlan = true;
	if (need_tail_tag) {
		sw_cfg_tail_tag(sw, true);
		sw->overrides |= TAIL_TAGGING;
	}
	if (need_vlan) {
		struct ksz_vlan_table entry;

		/* Default VID 1 is not in VLAN table. */
		sw->ops->release(sw);
		entry.fid = 0;
		entry.member = sw->PORT_MASK;
		entry.valid = 1;
		sw_w_vlan_table(sw, 1, &entry);
		entry.fid = 0;
		entry.member = sw->PORT_MASK;
		entry.valid = 1;
		sw_w_vlan_table(sw, 0, &entry);
		sw->ops->acquire(sw);
		sw_ena_vlan(sw);
	}
	sw_ena_intr(sw);
	sw->ops->release(sw);

#ifdef CONFIG_KSZ_STP
	if (sw->features & STP_SUPPORT) {
		struct ksz_stp_info *stp = &sw->info->rstp;

		if (stp->br.bridgeEnabled)
			stp_start(stp);
	} else
		stp_set_addr(&sw->info->rstp, sw->info->mac_addr);
#endif
}  /* sw_start */

static int sw_stop(struct ksz_sw *sw, int complete)
{
	int reset = false;

#ifdef CONFIG_KSZ_STP
	if (sw->features & STP_SUPPORT) {
		struct ksz_stp_info *stp = &sw->info->rstp;

		if (stp->br.bridgeEnabled)
			stp_stop(stp, true);
	}
#endif

#ifdef CONFIG_KSZ_MRP
	if (sw->features & MRP_SUPPORT) {
		struct mrp_info *mrp = &sw->mrp;

		mrp_stop(mrp);
	}
#endif

	sw->ops->acquire(sw);
	if (!reset)
		sw_reset(sw);
	reset = true;
	sw_init(sw);

	/* Clean out static MAC table when the switch shutdown. */
	if (complete)
		sw_clr_sta_mac_table(sw);
	sw->ops->release(sw);
	return reset;
}  /* sw_stop */

static void sw_init_mib(struct ksz_sw *sw)
{
	unsigned long interval;
	uint n;
	uint p;

	interval = MIB_READ_INTERVAL * 2 / (sw->mib_port_cnt + 1);
	for (n = 0; n <= sw->mib_port_cnt; n++) {
		p = get_phy_port(sw, n);
		sw->port_mib[p].mib_start = 0;
		if (sw->next_jiffies < jiffies)
			sw->next_jiffies = jiffies + HZ * 2;
		else
			sw->next_jiffies += interval;
		sw->counter[p].time = sw->next_jiffies;
		sw->port_state[p].state = media_disconnected;
		port_init_cnt(sw, p);
	}
	sw->port_state[sw->HOST_PORT].state = media_connected;
}  /* sw_init_mib */

static int sw_open_dev(struct ksz_sw *sw, struct net_device *dev, u8 *addr)
{
	int mode = 0;

	sw_init_mib(sw);

	sw->main_dev = dev;
	sw->net_ops->start(sw, addr);
	if (sw->dev_count > 1)
		mode |= 1;
	if (sw->features & DIFF_MAC_ADDR)
		mode |= 2;
	return mode;
}  /* sw_open_dev */

static void sw_open_port(struct ksz_sw *sw, struct net_device *dev,
	struct ksz_port *port, u8 *state)
{
	uint i;
	uint n;
	uint p;
	struct ksz_port_info *info;

	/* Update in case it is changed. */
	if (dev->phydev)
		port->phydev = dev->phydev;
	for (i = 0, n = port->first_port; i < port->port_cnt; i++, n++) {
		p = get_phy_port(sw, n);
		info = get_port_info(sw, p);
		/*
		 * Initialize to invalid value so that link detection
		 * is done.
		 */
		info->link = 0xFF;
		info->state = media_unknown;
		info->report = true;
		if (port->port_cnt == 1) {
			if (sw->netdev[0]) {
				struct ksz_port *sw_port = sw->netport[0];

				port->speed = sw_port->speed;
				port->duplex = sw_port->duplex;
				port->flow_ctrl = sw_port->flow_ctrl;
			}
			if (info->own_speed != port->speed ||
			    info->own_duplex != port->duplex) {
				if (info->own_speed)
					port->speed = info->own_speed;
				if (info->own_duplex)
					port->duplex = info->own_duplex;
			}
		}
	}

	sw->ops->acquire(sw);

	/* Need to open the port in multiple device interfaces mode. */
	if (sw->dev_count > 1 && (!sw->dev_offset || dev != sw->netdev[0])) {
		*state = STP_STATE_SIMPLE;
		if (sw->dev_offset && !(sw->features & STP_SUPPORT)) {
			*state = STP_STATE_FORWARDING;
		}
		if (sw->features & SW_VLAN_DEV) {
			p = get_phy_port(sw, port->first_port);
			i = sw->info->port_cfg[p].index;
			if (!(sw->eth_maps[i].proto & HSR_HW))
				*state = STP_STATE_FORWARDING;
		}
		for (i = 0, n = port->first_port; i < port->port_cnt;
		     i++, n++) {
			p = get_phy_port(sw, n);
			sw->dev_ports |= (1 << p);
#ifdef CONFIG_KSZ_STP
			if (sw->features & STP_SUPPORT) {
				stp_enable_port(&sw->info->rstp, p, state);
			}
#endif
			port_set_stp_state(sw, p, *state);
		}
	} else if (sw->dev_count == 1) {
		sw->dev_ports = sw->PORT_MASK;
	}

	sw->phy_intr = sw->PORT_MASK;
	if (port->force_link)
		port_force_link_speed(port);
	else
		port_set_link_speed(port);
	port_get_link_speed(port);
	sw->phy_intr = 0;
	sw->ops->release(sw);
	for (i = 0; i < sw->eth_cnt; i++) {
		if (dev != sw->netdev[i])
			continue;
#ifdef CONFIG_KSZ_DLR
		if (sw->eth_maps[i].proto & DLR_HW) {
			struct ksz_dlr_info *info = &sw->info->dlr;

			p = get_phy_port(sw, port->first_port);
			if (info->ports[0] == p)
				prep_dlr(info, dev, dev->dev_addr);
		}
#endif
	}
}  /* sw_open_port */

static void sw_close_port(struct ksz_sw *sw, struct net_device *dev,
	struct ksz_port *port)
{
	int i;
	uint p;
#ifdef CONFIG_KSZ_MRP
	struct mrp_info *mrp = &sw->mrp;
#endif

	/* Need to shut the port manually in multiple device interfaces mode. */
	if (sw->dev_count > 1 && (!sw->dev_offset || dev != sw->netdev[0])) {
		uint n;

		sw->ops->acquire(sw);
		for (i = 0, n = port->first_port; i < port->port_cnt;
		     i++, n++) {
			p = get_phy_port(sw, n);
			if (p == sw->HOST_PORT)
				continue;
#ifdef CONFIG_KSZ_STP
			if (sw->features & STP_SUPPORT)
				stp_disable_port(&sw->info->rstp, p);
#endif
#ifdef CONFIG_KSZ_MRP
			if (sw->features & MRP_SUPPORT) {
				mrp_close_port(mrp, p);
			}
#endif
			sw->dev_ports &= ~(1 << p);
			port_set_stp_state(sw, p, STP_STATE_DISABLED);
		}
		sw->ops->release(sw);
	} else if (sw->dev_count == 1) {
#ifdef CONFIG_KSZ_MRP
		uint n;

		if (sw->features & MRP_SUPPORT) {
			for (n = 0; n <= sw->mib_port_cnt; n++) {
				p = get_phy_port(sw, n);
				mrp_close_port(mrp, p);
			}
		}
#endif
		sw->dev_ports = 0;
	}
	for (i = 0; i < sw->eth_cnt; i++) {
		if (dev != sw->netdev[i])
			continue;
	}
}  /* sw_close_port */

static void sw_open(struct ksz_sw *sw)
{
#ifdef CONFIG_KSZ_MRP
	if (sw->features & MRP_SUPPORT) {
		struct ksz_port_info *info = get_port_info(sw, sw->HOST_PORT);
		u32 speed = info->tx_rate / TX_RATE_UNIT;

		mrp_set_speed(&sw->mrp, sw->HOST_PORT, speed, true);
		mrp_open(&sw->mrp);
		schedule_delayed_work(&sw->set_mrp, msecs_to_jiffies(1000));
	}
#endif
	/* Timer may already be started by the SPI device. */
	if (!sw->monitor_timer_info->max)
		ksz_start_timer(sw->monitor_timer_info,
			sw->monitor_timer_info->period);
}  /* sw_open */

static void sw_close(struct ksz_sw *sw)
{
#ifdef CONFIG_KSZ_MRP
	if (sw->features & MRP_SUPPORT)
		mrp_close(&sw->mrp, true);
#endif
	ksz_stop_timer(sw->monitor_timer_info);
	cancel_delayed_work_sync(sw->link_read);
}  /* sw_close */

static u8 sw_set_mac_addr(struct ksz_sw *sw, struct net_device *dev,
	u8 promiscuous, uint port)
{
	int n;

	/* See if different MAC addresses are used. */
	if (sw->dev_count > 1) {
		int i;
		int dev_count = sw->dev_count + sw->dev_offset;

		for (i = 0; i < dev_count; i++) {
			if (dev == sw->netdev[i])
				continue;
			if (memcmp(sw->netdev[i]->dev_addr,
			    dev->dev_addr, ETH_ALEN))
				break;
		}
		if (sw->features & DIFF_MAC_ADDR) {
			struct ksz_port *priv;
			struct ksz_port_info *info;
			uint p;

			/* All addresses the same. */
			if (i == dev_count) {
				sw->features &= ~DIFF_MAC_ADDR;
				--promiscuous;
			} else if (sw->dev_offset && dev == sw->netdev[0]) {
				for (n = 1; n < dev_count; n++) {
					priv = sw->netport[n];
					p = get_phy_port(sw, priv->first_port);
					info = get_port_info(sw, p);
					inc_mac_addr(info->mac_addr,
						dev->dev_addr, n);
					inc_mac_addr(sw->netdev[n]->dev_addr,
						dev->dev_addr, n);
				}
			}
		} else {
			if (dev == sw->netdev[0] && i < dev_count) {

				/* Make MAC address the same in all devices. */
				for (i = 1; i < dev_count; i++) {
					memcpy(sw->netdev[i]->dev_addr,
						dev->dev_addr, ETH_ALEN);
				}
			} else {
				if (i < dev_count) {
					sw->features |= DIFF_MAC_ADDR;
					++promiscuous;
				}
			}
		}
	}
	if (dev == sw->netdev[0]) {
		sw->ops->acquire(sw);
		sw_set_addr(sw, dev->dev_addr);
		sw->ops->release(sw);
	}
	for (n = 0; n < sw->eth_cnt; n++) {
		if (sw->netdev[n] != dev)
			continue;
#ifdef CONFIG_KSZ_STP
		if (sw->features & STP_SUPPORT) {
			struct ksz_stp_info *stp = &sw->info->rstp;

			stp->ops->change_addr(stp, dev->dev_addr);
		}
#endif
#ifdef CONFIG_KSZ_DLR
		if (sw->eth_maps[n].proto & DLR_HW) {
			dlr_change_addr(&sw->info->dlr, dev->dev_addr);
		}
#endif
	}
	return promiscuous;
}  /* sw_set_mac_addr */

static struct ksz_sw *sw_priv;

static struct sw_dev_info *alloc_sw_dev_info(unsigned int minor)
{
	struct sw_dev_info *info;

	info = kzalloc(sizeof(struct sw_dev_info), GFP_KERNEL);
	if (info) {
		info->sw = sw_priv;
		sema_init(&info->sem, 1);
		mutex_init(&info->lock);
		init_waitqueue_head(&info->wait_msg);
		info->write_len = 1000;
		info->write_buf = kzalloc(info->write_len, GFP_KERNEL);
		info->read_max = 60000;
		info->read_buf = kzalloc(info->read_max, GFP_KERNEL);

		info->minor = minor;
		info->next = sw_priv->dev_list[minor];
		sw_priv->dev_list[minor] = info;
	}
	return info;
}  /* alloc_sw_dev_info */

static void free_sw_dev_info(struct sw_dev_info *info)
{
	if (info) {
		struct ksz_sw *sw = info->sw;
		unsigned int minor = info->minor;
		struct sw_dev_info *prev = sw->dev_list[minor];

		if (prev == info) {
			sw->dev_list[minor] = info->next;
		} else {
			while (prev && prev->next != info)
				prev = prev->next;
			if (prev)
				prev->next = info->next;
		}
		kfree(info->read_buf);
		kfree(info->write_buf);
		kfree(info);
	}
}  /* free_sw_dev_info */

static int sw_dev_open(struct inode *inode, struct file *filp)
{
	struct sw_dev_info *info = (struct sw_dev_info *)
		filp->private_data;
	unsigned int minor = MINOR(inode->i_rdev);

	if (minor > 1)
		return -ENODEV;
	if (!info) {
		info = alloc_sw_dev_info(minor);
		if (info)
			filp->private_data = info;
		else
			return -ENOMEM;
	}
	return 0;
}  /* sw_dev_open */

static int sw_dev_release(struct inode *inode, struct file *filp)
{
	struct sw_dev_info *info = (struct sw_dev_info *)
		filp->private_data;

	free_sw_dev_info(info);
	filp->private_data = NULL;
	return 0;
}  /* sw_dev_release */

static int sw_get_attrib(struct ksz_sw *sw, int subcmd, int size,
	int *req_size, size_t *len, u8 *data, int *output)
{
	struct ksz_info_opt *opt = (struct ksz_info_opt *) data;
	struct ksz_info_cfg *cfg = &opt->data.cfg;
	int i;
	int n;
	int p;

	*len = 0;
	*output = 0;
	switch (subcmd) {
	case DEV_SW_CFG:
		n = opt->num;
		p = opt->port;
		if (!n)
			n = 1;
		*len = 2 + n * sizeof(struct ksz_info_cfg);
		break;
	}
	if (!*len)
		return DEV_IOC_INVALID_CMD;
	if (size < *len) {
		*req_size = *len + SIZEOF_ksz_request;
		return DEV_IOC_INVALID_LEN;
	}
	switch (subcmd) {
	case DEV_SW_CFG:
		sw->ops->acquire(sw);
		for (i = 0; i < opt->num; i++, p++) {
			cfg->on_off = 0;
			if (cfg->set & SP_LEARN) {
				if (!port_chk_dis_learn(sw, p))
					cfg->on_off |= SP_LEARN;
			}
			if (cfg->set & SP_RX) {
				if (port_chk_rx(sw, p))
					cfg->on_off |= SP_RX;
			}
			if (cfg->set & SP_TX) {
				if (port_chk_tx(sw, p))
					cfg->on_off |= SP_TX;
			}
			if (p == sw->HOST_PORT)
				continue;
#if 0
			if (cfg->set & SP_PHY_POWER) {
				if (port_chk_power(sw, p))
					cfg->on_off |= SP_PHY_POWER;
			}
#endif
			cfg++;
		}
		sw->ops->release(sw);
		break;
	}
	return DEV_IOC_OK;
}  /* sw_get_attrib */

static int sw_set_attrib(struct ksz_sw *sw, int subcmd, int size,
	int *req_size, u8 *data, int *output)
{
	struct ksz_info_opt *opt = (struct ksz_info_opt *) data;
	struct ksz_info_cfg *cfg = &opt->data.cfg;
	int len;
	int i;
	int n;
	int p;

	*output = 0;
	switch (subcmd) {
	case DEV_SW_CFG:
		n = opt->num;
		p = opt->port;
		if (!n)
			n = 1;
		len = 2 + n * sizeof(struct ksz_info_cfg);
		if (size < len)
			goto not_enough;
		sw->ops->acquire(sw);
		for (i = 0; i < opt->num; i++, p++) {
			if (cfg->set & SP_LEARN)
				port_cfg_dis_learn(sw, p,
					!(cfg->on_off & SP_LEARN));
			if (cfg->set & SP_RX)
				port_cfg_rx(sw, p,
					!!(cfg->on_off & SP_RX));
			if (cfg->set & SP_TX)
				port_cfg_tx(sw, p,
					!!(cfg->on_off & SP_TX));
			if (p == sw->HOST_PORT)
				continue;
#if 0
			if (cfg->set & SP_PHY_POWER)
				port_cfg_power(sw, p,
					!!(cfg->on_off & SP_PHY_POWER));
#endif
			cfg++;
		}
		sw->ops->release(sw);
		break;
	default:
		return DEV_IOC_INVALID_CMD;
	}
	return DEV_IOC_OK;

not_enough:
	*req_size = len + SIZEOF_ksz_request;
	return DEV_IOC_INVALID_LEN;
}  /* sw_set_attrib */

static int base_dev_req(struct ksz_sw *sw, char *arg, void *info)
{
	struct ksz_request *req = (struct ksz_request *) arg;
	int len;
	int maincmd;
	int req_size;
	int subcmd;
	int output;
	size_t param_size;
	u8 data[PARAM_DATA_SIZE];
	struct ksz_resp_msg *msg = (struct ksz_resp_msg *) data;
	int err = 0;
	int result = 0;

	get_user_data(&req_size, &req->size, info);
	get_user_data(&maincmd, &req->cmd, info);
	get_user_data(&subcmd, &req->subcmd, info);
	get_user_data(&output, &req->output, info);
	len = req_size - SIZEOF_ksz_request;

	maincmd &= 0xffff;
	switch (maincmd) {
	case DEV_CMD_INFO:
		switch (subcmd) {
		case DEV_INFO_INIT:
			req_size = SIZEOF_ksz_request + 4;
			if (len >= 4) {
				data[0] = 'M';
				data[1] = 'i';
				data[2] = 'c';
				data[3] = 'r';
				data[4] = 0;
				err = write_user_data(data, req->param.data,
					6, info);
				if (err)
					goto dev_ioctl_done;
				sw->dev_info = info;
			} else
				result = DEV_IOC_INVALID_LEN;
			break;
		case DEV_INFO_EXIT:

		/* fall through */
		case DEV_INFO_QUIT:

			/* Not called through char device. */
			if (!info)
				break;
			msg->module = DEV_MOD_BASE;
			msg->cmd = DEV_INFO_QUIT;
			msg->resp.data[0] = 0;
			sw_setup_msg(info, msg, 8, NULL, NULL);
			sw->notifications = 0;
			sw->dev_info = NULL;
			break;
		case DEV_INFO_NOTIFY:
			if (len >= 4) {
				uint *notify = (uint *) data;

				_chk_ioctl_size(len, 4, 0, &req_size, &result,
					&req->param, data, info);
				sw->notifications = *notify;
			}
			break;
		default:
			result = DEV_IOC_INVALID_CMD;
			break;
		}
		break;
	case DEV_CMD_PUT:
		if (_chk_ioctl_size(len, len, 0, &req_size, &result,
		    &req->param, data, info))
			goto dev_ioctl_resp;
		result = sw_set_attrib(sw, subcmd, len, &req_size, data,
			&output);
		if (result)
			goto dev_ioctl_resp;
		put_user_data(&output, &req->output, info);
		break;
	case DEV_CMD_GET:
		if (_chk_ioctl_size(len, len, 0, &req_size, &result,
		    &req->param, data, info))
			goto dev_ioctl_resp;
		result = sw_get_attrib(sw, subcmd, len, &req_size,
			&param_size, data, &output);
		if (result)
			goto dev_ioctl_resp;
		err = write_user_data(data, req->param.data, param_size, info);
		if (err)
			goto dev_ioctl_done;
		req_size = param_size + SIZEOF_ksz_request;
		put_user_data(&output, &req->output, info);
		break;
	default:
		result = DEV_IOC_INVALID_CMD;
		break;
	}

dev_ioctl_resp:
	put_user_data(&req_size, &req->size, info);
	put_user_data(&result, &req->result, info);

	/* Return ERESTARTSYS so that the system call is called again. */
	if (result < 0)
		err = result;

dev_ioctl_done:
	return err;
}  /* base_dev_req */

static int sw_dev_req(struct ksz_sw *sw, int start, char *arg,
	struct sw_dev_info *info)
{
	struct ksz_request *req = (struct ksz_request *) arg;
	int maincmd;
	int req_size;
	int err = 0;
	int result = DEV_IOC_OK;

	/* Check request size. */
	get_user_data(&req_size, &req->size, info);
	if (chk_ioctl_size(req_size, SIZEOF_ksz_request, 0, &req_size,
	    &result, NULL, NULL))
		goto dev_ioctl_resp;

	result = -EOPNOTSUPP;
	get_user_data(&maincmd, &req->cmd, info);
	maincmd >>= 16;
	switch (maincmd) {
	case DEV_MOD_BASE:
		err = base_dev_req(sw, arg, info);
		result = 0;
		break;
#ifdef CONFIG_KSZ_DLR
	case DEV_MOD_DLR:
		if (sw->features & DLR_HW) {
			struct ksz_dlr_info *dlr = &sw->info->dlr;

			err = dlr->ops->dev_req(dlr, arg, info);
			result = 0;
		}
		break;
#endif
	default:
		break;
	}

	/* Processed by specific module. */
	if (!result)
		return err;
	if (result < 0)
		goto dev_ioctl_done;

dev_ioctl_resp:
	put_user_data(&req_size, &req->size, info);
	put_user_data(&result, &req->result, info);

dev_ioctl_done:

	/* Return ERESTARTSYS so that the system call is called again. */
	if (result < 0)
		err = result;

	return err;
}  /* sw_dev_req */

static ssize_t sw_dev_read(struct file *filp, char *buf, size_t count,
	loff_t *offp)
{
	struct sw_dev_info *info = (struct sw_dev_info *)
		filp->private_data;
	ssize_t result = 0;
	int rc;

	if (!info->read_len) {
		*offp = 0;
		rc = wait_event_interruptible(info->wait_msg,
			0 != info->read_len);

		/* Cannot continue if ERESTARTSYS. */
		if (rc < 0)
			return 0;
	}

	if (down_interruptible(&info->sem))
		return -ERESTARTSYS;

	mutex_lock(&info->lock);
	if (*offp >= info->read_len) {
		info->read_len = 0;
		count = 0;
		*offp = 0;
		goto dev_read_done;
	}

	if (*offp + count > info->read_len) {
		count = info->read_len - *offp;
		info->read_len = 0;
	}

	if (copy_to_user(buf, &info->read_buf[*offp], count)) {
		result = -EFAULT;
		goto dev_read_done;
	}
	if (info->read_len)
		*offp += count;
	else
		*offp = 0;
	result = count;

dev_read_done:
	mutex_unlock(&info->lock);
	up(&info->sem);
	return result;
}  /* sw_dev_read */

#ifdef HAVE_UNLOCKED_IOCTL
static long sw_dev_ioctl(struct file *filp, unsigned int cmd,
	unsigned long arg)
#else
static int sw_dev_ioctl(struct inode *inode, struct file *filp,
	unsigned int cmd, unsigned long arg)
#endif
{
	struct sw_dev_info *info = (struct sw_dev_info *)
		filp->private_data;
	struct ksz_sw *sw = info->sw;
	int err = 0;

	if (_IOC_TYPE(cmd) != DEV_IOC_MAGIC)
		return -ENOTTY;
	if (_IOC_NR(cmd) > DEV_IOC_MAX)
		return -ENOTTY;
	if (_IOC_DIR(cmd) & _IOC_READ)
		err = !access_ok(VERIFY_WRITE, (void *) arg, _IOC_SIZE(cmd));
	else if (_IOC_DIR(cmd) & _IOC_WRITE)
		err = !access_ok(VERIFY_READ, (void *) arg, _IOC_SIZE(cmd));
	if (err) {
		printk(KERN_ALERT "err fault\n");
		return -EFAULT;
	}
	if (down_interruptible(&info->sem))
		return -ERESTARTSYS;

	err = sw_dev_req(sw, 0, (char *) arg, info);
	up(&info->sem);
	return err;
}  /* sw_dev_ioctl */

static ssize_t sw_dev_write(struct file *filp, const char *buf, size_t count,
	loff_t *offp)
{
	struct sw_dev_info *info = (struct sw_dev_info *)
		filp->private_data;
	ssize_t result = 0;
	size_t size;
	int rc;

	if (!count)
		return result;

	if (down_interruptible(&info->sem))
		return -ERESTARTSYS;

	if (*offp >= info->write_len) {
		result = -ENOSPC;
		goto dev_write_done;
	}
	if (*offp + count > info->write_len)
		count = info->write_len - *offp;
	if (copy_from_user(info->write_buf, buf, count)) {
		result = -EFAULT;
		goto dev_write_done;
	}
	size = 0;
	result = size;
	rc = 0;
	if (rc)
		result = rc;

dev_write_done:
	up(&info->sem);
	return result;
}  /* sw_dev_write */

static const struct file_operations sw_dev_fops = {
	.read		= sw_dev_read,
	.write		= sw_dev_write,
#ifdef HAVE_UNLOCKED_IOCTL
	.unlocked_ioctl	= sw_dev_ioctl,
#else
	.ioctl		= sw_dev_ioctl,
#endif
	.open		= sw_dev_open,
	.release	= sw_dev_release,
};

static struct class *sw_class;

static int init_sw_dev(int dev_major, char *dev_name)
{
	int result;

	result = register_chrdev(dev_major, dev_name, &sw_dev_fops);
	if (result < 0) {
		printk(KERN_WARNING "%s: can't get major %d\n", dev_name,
			dev_major);
		return result;
	}
	if (0 == dev_major)
		dev_major = result;
	sw_class = class_create(THIS_MODULE, dev_name);
	if (IS_ERR(sw_class)) {
		unregister_chrdev(dev_major, dev_name);
		return -ENODEV;
	}
	device_create(sw_class, NULL, MKDEV(dev_major, 0), NULL, dev_name);
	return dev_major;
}  /* init_sw_dev */

static void exit_sw_dev(int dev_major, char *dev_name)
{
	device_destroy(sw_class, MKDEV(dev_major, 0));
	class_destroy(sw_class);
	unregister_chrdev(dev_major, dev_name);
}  /* exit_sw_dev */

static void sw_init_dev(struct ksz_sw *sw)
{
	sw_priv = sw;
	sprintf(sw->dev_name, "sw_dev");
	sw->dev_major = init_sw_dev(0, sw->dev_name);
	sw->msg_buf = kzalloc(MAX_SW_LEN, GFP_KERNEL);
}  /* sw_init_dev */

static void sw_exit_dev(struct ksz_sw *sw)
{
	kfree(sw->msg_buf);
	if (sw->dev_major >= 0)
		exit_sw_dev(sw->dev_major, sw->dev_name);
}  /* sw_exit_dev */

static void link_update_work(struct work_struct *work)
{
	struct ksz_port *port =
		container_of(work, struct ksz_port, link_update);
	struct ksz_sw *sw = port->sw;
	struct net_device *dev;
	struct phy_device *phydev;
	struct ksz_port_info *info;
	uint i;
	uint p;
	int link;

#ifdef CONFIG_KSZ_DLR
	if (sw->features & DLR_HW) {
		struct ksz_dlr_info *dlr = &sw->info->dlr;

		dlr->ops->link_change(dlr,
			sw->port_info[dlr->ports[0]].state == media_connected,
			sw->port_info[dlr->ports[1]].state == media_connected);
	}
#endif

	for (i = 1; i <= sw->mib_port_cnt; i++) {
		p = get_phy_port(sw, i);
		info = get_port_info(sw, p);

		if (!info->report)
			continue;
		info->report = false;
		phydev = sw->phy[i];
		phydev->link = (info->state == media_connected);
		phydev->speed = info->tx_rate / TX_RATE_UNIT;
		phydev->duplex = (info->duplex == 2);
	}

	info = port->linked;
	phydev = port->phydev;
	phydev->link = (info->state == media_connected);
	phydev->speed = info->tx_rate / TX_RATE_UNIT;
	phydev->duplex = (info->duplex == 2);
	dev = port->netdev;
	if (dev) {
		link = netif_carrier_ok(dev);
		if (link != phydev->link) {
			if (phydev->link)
				netif_carrier_on(dev);
			else
				netif_carrier_off(dev);
			if (netif_msg_link(sw))
				pr_info("%s link %s\n",
					dev->name,
					phydev->link ? "on" : "off");
		}
	}

#ifdef CONFIG_KSZ_STP
	if (sw->features & STP_SUPPORT) {
		struct ksz_stp_info *stp = &sw->info->rstp;

		stp->ops->link_change(stp, true);
	}
#endif

	/* The switch is always linked; speed and duplex are also fixed. */
	phydev = NULL;
	dev = sw->netdev[0];
	if (dev)
		phydev = dev->phydev;
	if (phydev) {
		int phy_link = 0;

		port = sw->netport[0];

		/* phydev settings may be changed by ethtool. */
		info = get_port_info(sw, sw->HOST_PORT);
		phydev->link = (info->state == media_connected);
		phydev->speed = info->tx_rate / TX_RATE_UNIT;
		phydev->duplex = (info->duplex == 2);
		phydev->pause = 1;
		if (phydev->link)
			phy_link = (port->linked->state == media_connected);
		link = netif_carrier_ok(dev);
		if (link != phy_link) {
			if (phy_link)
				netif_carrier_on(dev);
			else
				netif_carrier_off(dev);
			if (netif_msg_link(sw))
				pr_info("%s link %s\n",
					dev->name,
					phy_link ? "on" : "off");
		}
		if (phydev->adjust_link && phydev->attached_dev)
			phydev->adjust_link(phydev->attached_dev);
	}
}  /* link_update_work */

#if 0
#define USE_DLR
#endif

/*
 * This enables multiple network device mode for the switch, which contains at
 * least two physical ports.  Some users like to take control of the ports for
 * running Spanning Tree Protocol.  The driver will create an additional eth?
 * device for each port depending on the mode.
 *
 * Some limitations are the network devices cannot have different MTU and
 * multicast hash tables.
 */
static int multi_dev = -1;

/*
 * As most users select multiple network device mode to use Spanning Tree
 * Protocol, this enables a feature in which most unicast and multicast packets
 * are forwarded inside the switch and not passed to the host.  Only packets
 * that need the host's attention are passed to it.  This prevents the host
 * wasting CPU time to examine each and every incoming packets and do the
 * forwarding itself.
 *
 * As the hack requires the private bridge header, the driver cannot compile
 * with just the kernel headers.
 *
 * Enabling STP support also turns on multiple network device mode.
 */
static int stp = -1;

/*
 * This enables fast aging in the switch.  Not sure what situation requires
 * that.  However, fast aging is used to flush the dynamic MAC table when STP
 * support is enabled.
 */
static int fast_aging;

#if defined(USE_DLR)
static int eth1_ports = 0x3;
#else
static int eth1_ports;
#endif
static int eth2_ports;
static int eth3_ports;
static int eth4_ports;

static int eth1_vlan;
static int eth2_vlan;
static int eth3_vlan;
static int eth4_vlan;

#if defined(USE_DLR)
static char *eth1_proto = "dlr";
#endif
#if !defined(USE_DLR)
static char *eth1_proto = " ";
#endif
static char *eth2_proto = " ";
static char *eth3_proto = " ";
static char *eth4_proto = " ";

static int *eth_ports[] = {
	&eth1_ports,
	&eth2_ports,
	&eth3_ports,
	&eth4_ports,
	NULL
};

static int *eth_vlans[] = {
	&eth1_vlan,
	&eth2_vlan,
	&eth3_vlan,
	&eth4_vlan,
	NULL
};

static char **eth_proto[] = {
	&eth1_proto,
	&eth2_proto,
	&eth3_proto,
	&eth4_proto,
	NULL
};

struct ksz_port_mapping {
	u8 id;
	u8 cnt;
	u8 fiber;
	u8 map[8];
};

enum {
	KSZ8795_SKU,
	KSZ8794_SKU,
	KSZ8765_SKU,
};

static struct ksz_port_mapping port_mappings[] = {
	{ KSZ8795_SKU,   5, 0, { 1, 2, 3, 4, 5, 0, 0, 0 }},
	{ KSZ8794_SKU,   5, 0, { 1, 2, 3, 5, 0, 0, 0, 0 }},
	{ KSZ8765_SKU,   5, 1, { 1, 2, 3, 4, 5, 0, 0, 0 }},
};

static u8 port_map[8];

static void sw_setup_logical_ports(struct ksz_sw *sw, u8 id, uint ports)
{
	struct ksz_port_mapping *map;
	struct ksz_port_info *info;
	struct ksz_port_info *pinfo;
	uint i;
	uint l;
	uint n;
	uint p;
	uint cnt = 0;

	for (i = 0; i < ARRAY_SIZE(port_mappings); i++) {
		map = &port_mappings[i];
		if (id == map->id) {
			cnt = map->cnt;
			memset(port_map, 0, 8 * sizeof(u8));
			memcpy(port_map, map->map, cnt * sizeof(u8));
			for (n = 0; n < sw->port_cnt; n++) {
				if (n == sw->HOST_PORT)
					break;
				info = &sw->port_info[n];
				info->phy = 1;
				info->fiber = map->fiber;
			}
			break;
		}
	}
	if (!cnt)
		return;

	for (n = 0; n < cnt; n++) {
		p = map->map[n];
		if (!p)
			break;
		--p;
		info = &sw->port_info[p];
		if (p == sw->HOST_PORT) {
			l = 0;
		} else {
			l = p + 1;
			if (p > sw->HOST_PORT)
				--l;
		}
		info->log_p = l;
		info->log_m = 0;
		info->phy_id = l;
	}
	n = (1 << cnt) - 1;
	ports &= n;
	for (i = 0, n = 0; n <= sw->port_cnt; n++) {
		if (n > 0) {
			p = n - 1;
			if (!(ports & BIT(p)))
				continue;
			p = map->map[p] - 1;
			if (p == sw->HOST_PORT)
				continue;
			l = i;
			++i;
		} else {
			p = sw->HOST_PORT;
			l = 0;
		}
		info = &sw->port_info[i];
		info->phy_p = p;
		info->phy_m = BIT(p);
		info = &sw->port_info[p];
		info->log_p = i;
		info->log_m = BIT(l);
	}
	info = &sw->port_info[sw->HOST_PORT];
	info->log_m = BIT(i);

	ports = 0;
	for (n = 0; n <= i; n++) {
		info = &sw->port_info[n];
		ports |= info->phy_m;
	}
dbg_msg("ports: %d %x\n", i, ports);

	for (n = 0; n <= i; n++) {
		info = &sw->port_info[n];
		pinfo = &sw->port_info[info->phy_p];
dbg_msg("%d= %d:%02x %d:%02x %d:%02x %d\n", n,
info->phy_p, info->phy_m, info->log_p, info->log_m,
pinfo->log_p, pinfo->log_m, pinfo->fiber);
	}
#if 1
	if (i + 1 < sw->port_cnt) {
		for (n = 0; n < sw->port_cnt; n++) {
			info = &sw->port_info[n];
			if (!info->log_m)
dbg_msg(" %d= %d %d\n", n, info->log_p, info->fiber);
			if (!info->log_m)
				info->log_p = sw->port_cnt;
		}
	}
#endif
	sw->PORT_MASK = ports;
dbg_msg("mask: %x %x\n", sw->HOST_MASK, sw->PORT_MASK);
	sw->mib_port_cnt = i;
	if (sw->mib_port_cnt + 1 < sw->port_cnt)
		sw->features |= USE_FEWER_PORTS;
	for (i = 0; i < sw->eth_cnt; i++) {
dbg_msg(" eth_maps: %d=%x\n", i, sw->eth_maps[i].mask);
		sw->eth_maps[i].mask = 0;
		for (l = 0, n = sw->eth_maps[i].first;
		     l < sw->eth_maps[i].cnt; l++, n++) {
			p = get_phy_port(sw, n);
			sw->eth_maps[i].mask |= BIT(p);
		}
dbg_msg("   eth_maps: %d=%x\n", i, sw->eth_maps[i].mask);
	}
#ifdef CONFIG_KSZ_DLR
	if (sw->features & DLR_HW) {
		struct ksz_dlr_info *dlr = &sw->info->dlr;

		dlr->ports[0] = port_map[dlr->ports[0]] - 1;
		dlr->ports[1] = port_map[dlr->ports[1]] - 1;
		dlr->member = BIT(dlr->ports[0]) | BIT(dlr->ports[1]);
dbg_msg(" dlr member: %d:%d %x\n", dlr->ports[0], dlr->ports[1], dlr->member);
	}
#endif
}  /* sw_setup_logical_ports */

static uint sw_setup_zone(struct ksz_sw *sw, uint in_ports)
{
	int c;
	int f;
	int limit;
	int m;
	uint p;
	uint q;
	int w;
	int *v;
	char **s;
	uint features;
	struct ksz_dev_map *map;
	uint ports;
	uint used = 0;
	int last_log_port = 0;
	int last_phy_port = 0;
	int last_vlan = 0;
	uint left = (1 << sw->port_cnt) - 1;

	if (multi_dev > 2) {
		ports = in_ports;
		goto setup_next;
	}
	q = 0;
	ports = 0;
	for (p = 0; p < sw->port_cnt - 1; p++) {
		v = eth_ports[p];

		/* No more port setting. */
		if (!v || !*v)
			break;
		m = *v;
		if (!(m & left)) {
			left = 0;
			break;
		}

		/* Find out how the ports are to be used. */
		limit = 0;
		w = last_vlan;
		features = 0;
		s = eth_proto[p];
#ifdef CONFIG_KSZ_DLR
		if (!strcmp(*s, "dlr")) {
			features = DLR_HW;
			limit = 2;
			if (!w)
				w = 1;
		}
#endif
#ifdef CONFIG_KSZ_STP
		if (!strcmp(*s, "stp")) {
			features = STP_SUPPORT;
		}
#endif

		m &= ~((1 << last_phy_port) - 1);
		m &= left;

		/* No more legimate port. */
		if (!m)
			break;

		v = eth_vlans[p];
		if (!w && (!v || !*v))
			break;
		if (*v)
			w = *v;

		/* Check VLAN id is unused. */
		for (q = 0; q < p; q++) {
			if (w > 1 && w == sw->eth_maps[q].vlan)
				w = last_vlan + 1;
		}
		c = 0;
		f = -1;
		for (q = p; q < sw->port_cnt - 1; q++) {
			if (m & (1 << q)) {
				if (f < 0)
					f = last_log_port;
				++c;
				++last_log_port;

				/* Limit to certain ports. */
				if (limit && c >= limit) {
					if (!(used & features)) {
						used |= features;
						++q;
						last_phy_port = q;
						break;
					}
					features = 0;
				}
				last_phy_port = q + 1;
			} else if (f >= 0) {
				if (limit && c < limit)
					features = 0;
				break;
			}
		}
		if (!c)
			continue;
		m &= (1 << q) - 1;
		if (!p && c > 1)
			used |= (features & VLAN_PORT);
#ifdef CONFIG_KSZ_STP
		if ((features & STP_SUPPORT) && c > 1) {
			used |= (features & STP_SUPPORT);
			stp = m;
		}
#endif
		++f;
		map = &sw->eth_maps[p];
		map->cnt = c;
		map->mask = m;
		map->first = f;
		map->phy_id = f;
		map->vlan = w & (4096 - 1);
		map->proto = features;
		if (last_vlan < w)
			last_vlan = w;
		ports |= m;
#ifdef CONFIG_KSZ_DLR
		if (features & DLR_HW) {
			struct ksz_dlr_info *dlr = &sw->info->dlr;

			c = 0;
			f = 0;
			do {
				if (m & 1) {
					dlr->ports[c++] = f;
				}
				m >>= 1;
				++f;
			} while (m && c < map->cnt);
		}
#endif
	}

	/* No VLAN devices specified. */
	if (!p) {
		ports = in_ports;
		goto setup_next;
	}

	/* Not all ports are used. */
	left &= ~((1 << last_phy_port) - 1);
	if (multi_dev != 1)
		left = 0;
	features = 0;
	s = eth_proto[p];
#ifdef CONFIG_KSZ_STP
	if (s && !strcmp(*s, "stp"))
		features = STP_SUPPORT;
#endif
	if (left) {
		m = left;
		c = 0;
		f = -1;
		for (q = 0; q < sw->mib_port_cnt - 1; q++) {
			if (m & (1 << q)) {
				if (f < 0)
					f = last_log_port;
				++c;
			}
		}
		m &= (1 << q) - 1;
		if ((features & STP_SUPPORT) && c > 1) {
			used |= (features & STP_SUPPORT);
			stp = m;
		}
		++f;
		map = &sw->eth_maps[p];
		map->cnt = c;
		map->mask = m;
		map->first = f;
		map->phy_id = f;
		map->vlan = ++last_vlan & (4096 - 1);
		map->proto = features;
		ports |= m;
		p++;
	}
	if (p > 1)
		sw->features |= SW_VLAN_DEV;
	sw->eth_cnt = p;
	for (p = 0; p < sw->eth_cnt; p++) {
		map = &sw->eth_maps[p];
		dbg_msg("%d: %d:%d %04x %03x %08x\n",
			p, map->first, map->cnt,
			map->mask, map->vlan, map->proto);
	}

setup_next:
#ifdef CONFIG_KSZ_DLR
	if (!(used & DLR_HW))
		sw->features &= ~DLR_HW;
#endif
	if ((sw->features & (DLR_HW | HSR_HW)) || sw->eth_cnt > 1) {
		if (stp <= 1)
			stp = 0;
#if 0
		sw->overrides &= ~USE_802_1X_AUTH;
#endif
	}
#ifdef CONFIG_KSZ_STP
	if (stp > 0) {
		sw->features |= STP_SUPPORT;
	}
#endif

dbg_msg("features: %x m:%d s:%x\n", sw->features, multi_dev, stp);
	return ports;
}  /* sw_setup_zone */

static int phy_offset;

static void sw_setup_special(struct ksz_sw *sw, int *port_cnt,
	int *mib_port_cnt, int *dev_cnt)
{
	phy_offset = 0;
	sw->dev_offset = 0;
	sw->phy_offset = 0;

	/* Multiple network device interfaces are required. */
	if (1 == sw->multi_dev) {
		sw->dev_count = sw->mib_port_cnt;
		sw->phy_offset = 1;
	} else if (2 == sw->multi_dev)
		sw->features |= VLAN_PORT | VLAN_PORT_TAGGING;
	else if (3 == sw->multi_dev) {
		sw->dev_count = sw->mib_port_cnt;
		sw->dev_offset = 1;
	} else if (4 == sw->multi_dev)
		sw->features |= VLAN_PORT;
	else if (5 == sw->multi_dev) {
		sw->dev_count = sw->mib_port_cnt;
		sw->dev_offset = 1;
		sw->features |= VLAN_PORT | VLAN_PORT_TAGGING;
	}

	/* Single network device has multiple ports. */
	if (1 == sw->dev_count) {
		*port_cnt = sw->mib_port_cnt;
		*mib_port_cnt = sw->mib_port_cnt;
	}
	if (1 == sw->multi_dev && sw->eth_cnt)
		sw->dev_count = sw->eth_cnt;
	*dev_cnt = sw->dev_count;
	if (3 == sw->multi_dev || 5 == sw->multi_dev)
		(*dev_cnt)++;
}  /* sw_setup_special */

static void sw_leave_dev(struct ksz_sw *sw)
{
	int i;

#ifdef CONFIG_KSZ_STP
	if (sw->features & STP_SUPPORT)
		leave_stp(&sw->info->rstp);
#endif
#ifdef CONFIG_KSZ_MRP
	if (sw->features & MRP_SUPPORT)
		leave_mrp(&sw->mrp);
#endif
	for (i = 0; i < sw->dev_count; i++) {
		sw->netdev[i] = NULL;
		sw->netport[i] = NULL;
	}
	sw->eth_cnt = 0;
	sw->dev_count = 0;
	sw->dev_offset = 0;
	sw->phy_offset = 0;
}  /* sw_leave_dev */

static int sw_setup_dev(struct ksz_sw *sw, struct net_device *dev,
	char *dev_name, struct ksz_port *port, int i, int port_cnt,
	int mib_port_cnt)
{
	struct ksz_port_info *info;
	uint cnt;
	uint n;
	uint p;
	uint pi;
	int phy_id;
	u32 features;
	struct ksz_dev_map *map;

	if (!phy_offset)
		phy_offset = sw->phy_offset;

	/* dev_offset is ether 0 or 1. */
	p = i;
	if (p)
		p -= sw->dev_offset;

	if (sw->dev_offset) {
		/*
		 * First device associated with switch has been
		 * created.
		 */
		if (i) {
			snprintf(dev->name, IFNAMSIZ, "%s.10%%d", dev_name);
			pi = get_phy_port(sw, p + 1);
			memcpy(dev->dev_addr, sw->port_info[pi].mac_addr,
				ETH_ALEN);
		} else {
			port_cnt = sw->mib_port_cnt;
			mib_port_cnt = sw->mib_port_cnt;
			sw->ops->acquire(sw);
			sw_set_addr(sw, dev->dev_addr);
			sw->ops->release(sw);
		}
	}

	map = &sw->eth_maps[i];
	if (1 == sw->multi_dev && sw->eth_cnt) {
		port_cnt = map->cnt;
		p = map->first - 1;
		mib_port_cnt = port_cnt;
	}

	port->port_cnt = port_cnt;
	port->mib_port_cnt = mib_port_cnt;
	port->first_port = p + 1;
	port->flow_ctrl = PHY_FLOW_CTRL;

#ifdef CONFIG_KSZ_STP
	if (!i && (sw->features & STP_SUPPORT))
		prep_stp_mcast(dev);
#endif

#ifdef CONFIG_KSZ_DLR
	/* Cannot flow control because of beacon timeout. */
	if (sw->eth_cnt && (map->proto & DLR_HW)) {
		port->flow_ctrl = PHY_NO_FLOW_CTRL;
		prep_dlr_mcast(dev);
	}
#endif
#ifdef CONFIG_KSZ_MRP
	if (!i && (sw->features & MRP_SUPPORT))
		setup_mrp(&sw->mrp, dev);
#endif

	/* Point to port under netdev. */
	if (phy_offset)
		phy_id = port->first_port + phy_offset - 1;
	else
		phy_id = 0;

	/* Replace virtual port with one from network device. */
	do {
		struct phy_device *phydev;
		struct phy_priv *priv;
		struct sw_priv *hw_priv = container_of(sw, struct sw_priv, sw);

		if (hw_priv->bus)
			phydev = mdiobus_get_phy(hw_priv->bus, phy_id);
		else
			phydev = &sw->phy_map[phy_id];
		priv = phydev->priv;
		priv->port = port;
	} while (0);
	if (!phy_offset)
		phy_offset = 1;

	p = get_phy_port(sw, port->first_port);
	port->sw = sw;
	port->linked = get_port_info(sw, p);

	for (cnt = 0, n = port->first_port; cnt < port_cnt; cnt++, n++) {
		pi = get_phy_port(sw, n);
		info = get_port_info(sw, pi);
		info->state = media_disconnected;
		sw->info->port_cfg[pi].index = i;
	}
	sw->netdev[i] = dev;
	sw->netport[i] = port;
	port->netdev = dev;
	port->phydev = sw->phy[phy_id];
	if (sw->dev_count > 1 && i && !(sw->features & DIFF_MAC_ADDR)) {
		if (memcmp(dev->dev_addr, sw->netdev[0]->dev_addr, ETH_ALEN))
			sw->features |= DIFF_MAC_ADDR;
	}

	INIT_WORK(&port->link_update, link_update_work);
	features = sw->features;
	if (sw->features & SW_VLAN_DEV)
		features = map->proto;

	if (features & VLAN_PORT)
		dev->features |= NETIF_F_HW_VLAN_CTAG_FILTER;

	/* Needed for inserting VLAN tag. */
	if (sw->features & SW_VLAN_DEV)
		dev->hard_header_len += VLAN_HLEN;
dbg_msg("%s %d:%d phy:%d\n", __func__, port->first_port, port->port_cnt, phy_id);

	return phy_id;
}  /* sw_setup_dev */

static u8 sw_get_priv_state(struct net_device *dev)
{
	return STP_STATE_SIMPLE;
}

static void sw_set_priv_state(struct net_device *dev, u8 state)
{
}

static int netdev_chk_running(struct net_device *dev)
{
	return netif_running(dev);
}

static int netdev_chk_stopped(struct net_device *dev)
{
	return netif_running(dev) && netif_queue_stopped(dev);
}

static void netdev_start_queue(struct net_device *dev)
{
	netif_start_queue(dev);
}

static void netdev_stop_queue(struct net_device *dev)
{
	netif_stop_queue(dev);
}

static void netdev_wake_queue(struct net_device *dev)
{
	netif_wake_queue(dev);
}

static void sw_netdev_oper(struct ksz_sw *sw, struct net_device *dev,
	int (*netdev_chk)(struct net_device *dev),
	void (*netdev_oper)(struct net_device *dev))
{
	int port;
	int dev_count = 1;

	dev_count = sw->dev_count + sw->dev_offset;
	if (dev_count <= 1) {
		netdev_oper(dev);
		return;
	}
	for (port = 0; port < dev_count; port++) {
		dev = sw->netdev[port];
		if (!dev)
			continue;
		if (!netdev_chk || netdev_chk(dev))
			netdev_oper(dev);
	}
}  /* sw_netdev_oper */

static void sw_netdev_open_port(struct ksz_sw *sw, struct net_device *dev)
{
	struct ksz_port *port;
	u8 state;
	int p;
	int dev_count = 1;

	dev_count = sw->dev_count + sw->dev_offset;
	if (dev_count <= 1) {
		port = sw->net_ops->get_priv_port(dev);
		state = sw->net_ops->get_state(dev);
		sw->net_ops->open_port(sw, dev, port, &state);
		sw->net_ops->set_state(dev, state);
		return;
	}
	for (p = 0; p < dev_count; p++) {
		dev = sw->netdev[p];
		if (!dev)
			continue;
		port = sw->net_ops->get_priv_port(dev);
		state = sw->net_ops->get_state(dev);
		sw->net_ops->open_port(sw, dev, port, &state);
		sw->net_ops->set_state(dev, state);
	}
}  /* sw_netdev_open_port */

static void sw_netdev_start_queue(struct ksz_sw *sw, struct net_device *dev)
{
	sw_netdev_oper(sw, dev, netdev_chk_running, netdev_start_queue);
}

static void sw_netdev_stop_queue(struct ksz_sw *sw, struct net_device *dev)
{
	sw_netdev_oper(sw, dev, netdev_chk_running, netdev_stop_queue);
}

static void sw_netdev_wake_queue(struct ksz_sw *sw, struct net_device *dev)
{
	sw_netdev_oper(sw, dev, netdev_chk_stopped, netdev_wake_queue);
}

static struct ksz_sw_net_ops sw_net_ops = {
	.setup_special		= sw_setup_special,
	.setup_dev		= sw_setup_dev,
	.leave_dev		= sw_leave_dev,
	.get_state		= sw_get_priv_state,
	.set_state		= sw_set_priv_state,

	.start			= sw_start,
	.stop			= sw_stop,
	.open_dev		= sw_open_dev,
	.open_port		= sw_open_port,
	.close_port		= sw_close_port,
	.open			= sw_open,
	.close			= sw_close,

	.netdev_start_queue	= sw_netdev_start_queue,
	.netdev_stop_queue	= sw_netdev_stop_queue,
	.netdev_wake_queue	= sw_netdev_wake_queue,
	.netdev_open_port	= sw_netdev_open_port,

	.set_mac_addr		= sw_set_mac_addr,

	.get_mtu		= sw_get_mtu,
	.get_tx_len		= sw_get_tx_len,
	.add_tail_tag		= sw_add_tail_tag,
	.get_tail_tag		= sw_get_tail_tag,
	.add_vid		= sw_add_vid,
	.kill_vid		= sw_kill_vid,
	.check_tx		= sw_check_tx,
	.rx_dev			= sw_rx_dev,
	.match_pkt		= sw_match_pkt,
	.parent_rx		= sw_parent_rx,
	.port_vlan_rx		= sw_port_vlan_rx,
	.final_skb		= sw_final_skb,
	.drv_rx			= sw_drv_rx,
	.set_multi		= sw_set_multi,

};

static struct ksz_sw_ops sw_ops = {
	.init			= sw_init_dev,
	.exit			= sw_exit_dev,
	.dev_req		= sw_dev_req,

	.get_phy_port		= get_phy_port,
	.get_log_port		= get_log_port_zero,

	.acquire		= sw_acquire,
	.release		= sw_release,

	.chk			= sw_chk,
	.cfg			= sw_cfg,

	.port_get_link_speed	= port_get_link_speed,
	.port_set_link_speed	= port_set_link_speed,
	.port_force_link_speed	= port_force_link_speed,

	.port_r_cnt		= port_r_cnt,
	.get_mib_counters	= get_sw_mib_counters,

	.sysfs_read		= sysfs_sw_read,
	.sysfs_read_hw		= sysfs_sw_read_hw,
	.sysfs_write		= sysfs_sw_write,
	.sysfs_port_read	= sysfs_port_read,
	.sysfs_port_read_hw	= sysfs_port_read_hw,
	.sysfs_port_write	= sysfs_port_write,
	.sysfs_mac_read		= sysfs_mac_read,
	.sysfs_mac_write	= sysfs_mac_write,
	.sysfs_vlan_read	= sysfs_vlan_read,
	.sysfs_vlan_write	= sysfs_vlan_write,
	.sysfs_acl_read		= sysfs_acl_read,
	.sysfs_acl_write	= sysfs_acl_write,

#ifdef CONFIG_KSZ_STP
	.sysfs_stp_read		= sysfs_stp_read,
	.sysfs_stp_write	= sysfs_stp_write,
	.sysfs_stp_port_read	= sysfs_stp_port_read,
	.sysfs_stp_port_write	= sysfs_stp_port_write,
#endif

#ifdef CONFIG_KSZ_MRP
	.sysfs_mrp_read		= sysfs_mrp_read,
	.sysfs_mrp_write	= sysfs_mrp_write,
	.sysfs_mrp_port_read	= sysfs_mrp_port_read,
	.sysfs_mrp_port_write	= sysfs_mrp_port_write,
#endif

	.cfg_mac		= sw_cfg_mac,
	.cfg_vlan		= sw_cfg_vlan,
	.alloc_mac		= sw_alloc_mac,
	.free_mac		= sw_free_mac,
	.alloc_vlan		= sw_alloc_vlan,
	.free_vlan		= sw_free_vlan,
	.alloc_fid		= sw_alloc_fid,
	.free_fid		= sw_free_fid,

	.get_br_id		= sw_get_br_id,
	.from_backup		= sw_from_backup,
	.to_backup		= sw_to_backup,
	.from_designated	= sw_from_designated,
	.to_designated		= sw_to_designated,
	.tc_detected		= sw_tc_detected,
	.get_tcDetected		= sw_get_tcDetected,

	.get_id			= sw_get_id,
	.cfg_tail_tag		= sw_cfg_tail_tag,
	.cfg_each_port		= sw_cfg_each_port,
	.port_to_phy_addr	= sw_port_to_phy_addr,
	.set_port_addr		= sw_set_port_addr,

	.cfg_src_filter		= sw_cfg_src_filter,
	.flush_table		= sw_flush_dyn_mac_table,
	.fwd_unk_vid		= sw_fwd_unk_vid,

};

/* -------------------------------------------------------------------------- */

/* debugfs code */
static int state_show(struct seq_file *seq, void *v)
{
	int i;
	int j;
	SW_D data[16 / SW_SIZE];
	struct sw_priv *ks = seq->private;
	struct ksz_sw *sw = &ks->sw;

	for (i = 0; i < 0x100; i += 16) {
		seq_printf(seq, SW_SIZE_STR":\t", i);
		mutex_lock(&ks->lock);
		for (j = 0; j < 16 / SW_SIZE; j++)
			data[j] = sw->reg->r8(sw, i + j * SW_SIZE);
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
#include "ksz_sw_sysfs_8795.c"
#ifdef CONFIG_KSZ_DLR
#include "ksz_dlr_sysfs.c"
#endif

static irqreturn_t sw_interrupt(int irq, void *phy_dat)
{
	struct sw_priv *ks = phy_dat;

	ks->sw.intr_using += 1;
	ks->irq_work.func(&ks->irq_work);

	return IRQ_HANDLED;
}  /* sw_interrupt */

static void sw_change(struct work_struct *work)
{
	struct sw_priv *ks =
		container_of(work, struct sw_priv, irq_work);
	struct ksz_sw *sw = &ks->sw;
	SW_D status;

	mutex_lock(&ks->hwlock);
	mutex_lock(&ks->lock);
	sw->intr_using++;
	status = sw->reg->r8(sw, REG_ACL_INT_STATUS);
	if (status) {
		int p;

		sw->reg->w8(sw, REG_ACL_INT_ENABLE, INT_PORT_ALL & ~status);
		sw->reg->w8(sw, REG_ACL_INT_STATUS, status);
		sw->reg->w8(sw, REG_ACL_INT_ENABLE, INT_PORT_ALL);
		for (p = 0; p < sw->mib_port_cnt; p++) {
			if (!(status & (1 << p)))
				continue;
#ifdef CONFIG_KSZ_DLR
			if (sw->features & DLR_HW)
				dlr_timeout(&sw->info->dlr, p);
#endif
		}
		ks->intr_working |= 0x40000000;
	} else
		ks->intr_working &= ~0x40000000;
	status = sw->reg->r8(sw, REG_INT_STATUS);
	status &= ks->intr_mask;
	if (status & ks->intr_mask) {
		sw->phy_intr = status;
		sw->reg->w8(sw, REG_INT_STATUS, status);
		status &= ~ks->intr_mask;
		schedule_delayed_work(&ks->link_read, 0);
		if (ks->intr_working & 0x80000000)
			ks->intr_working |= 1;
		ks->intr_working |= 0x80000000;
	} else
		ks->intr_working &= ~0x80000000;
	if (!(ks->intr_working & 0xc0000000))
		ks->intr_working = 0;
	sw->intr_using--;
	mutex_unlock(&ks->lock);
	if (status) {
		mutex_lock(&ks->lock);
		sw->reg->w8(sw, REG_INT_STATUS, status);
		mutex_unlock(&ks->lock);
	}
	mutex_unlock(&ks->hwlock);
	sw->intr_using = 0;
}  /* sw_change */

static int sw_start_interrupt(struct sw_priv *ks, const char *name)
{
	int err = 0;

	INIT_WORK(&ks->irq_work, sw_change);

	err = request_threaded_irq(ks->irq, NULL, sw_interrupt,
		ks->intr_mode, name, ks);
	if (err < 0) {
		printk(KERN_WARNING "%s: Can't get IRQ %d (PHY)\n",
			name,
			ks->irq);
		ks->irq = 0;
	}

	return err;
}  /* sw_start_interrupt */

static void sw_stop_interrupt(struct sw_priv *ks)
{
	free_irq(ks->irq, ks);
	cancel_work_sync(&ks->irq_work);
}  /* sw_stop_interrupt */

/* -------------------------------------------------------------------------- */

#define KSZ8795_SW_ID		0x8795
#define PHY_ID_KSZ_SW		((KSZ8795_ID_HI << 16) | KSZ8795_SW_ID)

static char *kszsw_phy_driver_names[] = {
	"Microchip KSZ8795 Switch",
	"Microchip KSZ8794 Switch",
	"Microchip KSZ8765 Switch",
};

static int kszphy_config_init(struct phy_device *phydev)
{
	return 0;
}

static struct phy_driver kszsw_phy_driver = {
	.phy_id		= PHY_ID_KSZ_SW,
	.phy_id_mask	= 0x00ffffff,
	.name		= "Microchip KSZ8795 Switch",
	.features	= (PHY_BASIC_FEATURES | SUPPORTED_Pause),
	.flags		= PHY_HAS_INTERRUPT,
	.config_init	= kszphy_config_init,
	.config_aneg	= genphy_config_aneg,
	.read_status	= genphy_read_status,
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
		data = KSZ8795_ID_HI;
		break;
	case PHY_REG_ID_2:
		/* Use unique switch id to differentiate from regular PHY. */
		data = KSZ8795_SW_ID;
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

static int ksz_mii_read(struct mii_bus *bus, int phy_id, int regnum)
{
	struct sw_priv *ks = bus->priv;
	struct ksz_sw *sw = &ks->sw;
	int ret = 0xffff;

	if (phy_id > sw->mib_port_cnt + 1)
		return 0xffff;

	mutex_lock(&ks->lock);
	ret = 0;
	if (regnum < 6) {
		u16 data;
		struct ksz_port *port;

		port = &ks->ports[phy_id];

		/* Not initialized during registration. */
		if (sw->phy[phy_id]) {
			struct phy_priv *phydata;

			phydata = sw->phy[phy_id]->priv;
			port = phydata->port;
		}
		phy_id = port->linked->phy_id;
		sw_r_phy(&ks->sw, phy_id, regnum, &data);
		ret = data;
	}
	mutex_unlock(&ks->lock);
	return ret;
}  /* ksz_mii_read */

static int ksz_mii_write(struct mii_bus *bus, int phy_id, int regnum, u16 val)
{
	struct sw_priv *ks = bus->priv;
	struct ksz_sw *sw = &ks->sw;

	if (phy_id > sw->mib_port_cnt + 1)
		return -EINVAL;

	mutex_lock(&ks->lock);
	if (regnum < 6) {
		uint i;
		uint p;
		int first;
		int last;

		if (0 == phy_id) {
			first = 1;
			last = sw->mib_port_cnt;
		} else {
			int n;
			int f;
			int l;
			struct ksz_dev_map *map;

			first = phy_id;
			last = phy_id;
			for (n = 0; n < sw->eth_cnt; n++) {
				map = &sw->eth_maps[n];
				f = map->first;
				l = f + map->cnt - 1;
				if (f <= phy_id && phy_id < l) {
					first = map->first;
					last = first + map->cnt - 1;
					break;
				}
			}
dbg_msg(" %d f:%d l:%d\n", phy_id, first, last);
		}

		/* PHY device driver resets or powers down the PHY. */
		if (0 == regnum &&
		    (val & (PHY_RESET | PHY_POWER_DOWN)))
			goto done;
		for (i = first; i <= last; i++) {
			p = get_phy_port(sw, i) + 1;
			sw_w_phy(sw, p, regnum, val);
		}
		if (PHY_REG_CTRL == regnum &&
		    !(val & PHY_AUTO_NEG_ENABLE))
			schedule_delayed_work(&ks->link_read, 1);
	}
done:
	mutex_unlock(&ks->lock);
	return 0;
}  /* ksz_mii_write */

static void sw_init_phy_priv(struct sw_priv *ks)
{
	struct phy_priv *phydata;
	struct ksz_port *port;
	struct ksz_sw *sw = &ks->sw;
	uint n;
	uint p;

	for (n = 0; n <= sw->mib_port_cnt + 1; n++) {
		phydata = &sw->phydata[n];
		port = &ks->ports[n];
		phydata->port = port;
		port->sw = sw;
		port->phydev = &sw->phy_map[n];
		port->flow_ctrl = PHY_FLOW_CTRL;
		port->port_cnt = 1;
		port->mib_port_cnt = 1;
		p = n;
		if (!n) {
			port->port_cnt = sw->mib_port_cnt;
			port->mib_port_cnt = sw->mib_port_cnt;
			p = 1;
		}
		port->first_port = p;
		p = get_phy_port(sw, p);
		port->linked = get_port_info(sw, p);
dbg_msg(" %s %d=p:%d; f:%d c:%d i:%d\n", __func__, n, p,
port->first_port, port->port_cnt, port->linked->phy_id);
		INIT_WORK(&port->link_update, link_update_work);
		sw->phy_map[n].priv = phydata;
	}
}  /* sw_init_phy_priv */

static void sw_init_phydev(struct ksz_sw *sw, struct phy_device *phydev)
{
	struct ksz_port_info *info = get_port_info(sw, sw->HOST_PORT);

	phydev->interface = sw->interface;
	phydev->link = 1;
	phydev->speed = info->tx_rate / TX_RATE_UNIT;
	phydev->duplex = (info->duplex == 2);
	phydev->pause = 1;
}  /* sw_init_phydev */

static int driver_installed;

static int ksz_mii_init(struct sw_priv *ks)
{
	struct platform_device *pdev;
	struct mii_bus *bus;
	struct phy_device *phydev;
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
		kszsw_phy_driver.name =
			kszsw_phy_driver_names[ks->sw.chip_id];
		err = phy_driver_register(&kszsw_phy_driver, THIS_MODULE);
		if (err)
			goto mii_init_free_mii_bus;
		driver_installed = true;
	}

	bus->name = "Switch MII bus",
	bus->read = ksz_mii_read;
	bus->write = ksz_mii_write;
	snprintf(bus->id, MII_BUS_ID_SIZE, "sw.%d", ks->sw.id);
	bus->parent = &pdev->dev;
	bus->phy_mask = ~((1 << (ks->sw.mib_port_cnt + 2)) - 1);
	bus->priv = ks;

	for (i = 0; i < PHY_MAX_ADDR; i++)
		bus->irq[i] = ks->irq;

	err = mdiobus_register(bus);
	if (err < 0)
		goto mii_init_free_mii_bus;

	for (i = 0; i < PHY_MAX_ADDR; i++) {
		phydev = mdiobus_get_phy(bus, i);
		if (phydev) {
			struct phy_priv *priv = &ks->sw.phydata[i];

			priv->state = phydev->state;
			phydev->priv = priv;
		}
	}

	ks->bus = bus;
	ks->pdev = pdev;
	phydev = mdiobus_get_phy(bus, 0);
	ks->phydev = phydev;
	sw_init_phydev(&ks->sw, phydev);

	return 0;

mii_init_free_mii_bus:
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
	struct phy_device *phydev;
	struct platform_device *pdev = ks->pdev;
	struct mii_bus *bus = ks->bus;

	if (ks->irq > 0) {
		struct ksz_sw *sw = &ks->sw;

		mutex_lock(&ks->lock);
		sw->reg->w8(sw, REG_INT_ENABLE, 0);
		sw->reg->w8(sw, REG_ACL_INT_ENABLE, 0);
		mutex_unlock(&ks->lock);
		sw_stop_interrupt(ks);
	}
	for (i = 0; i < PHY_MAX_ADDR; i++) {
		phydev = mdiobus_get_phy(bus, i);
		if (phydev) {
			struct ksz_port *port;

			port = &ks->ports[i];
			flush_work(&port->link_update);
		}
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
			unsigned long diff = jiffies - mib->rate[j].last;
			u64 cnt = mib->counter[MIB_RX_TOTAL + j] -
				mib->rate[j].last_cnt;

			if (cnt > 1000000 && diff >= 100) {
				u32 rem;
				u64 rate = cnt;

				rate *= 8;
				diff *= 10 * 100;
				rate = div_u64_rem(rate, diff, &rem);
				mib->rate[j].last = jiffies;
				mib->rate[j].last_cnt =
					mib->counter[MIB_RX_TOTAL + j];
				if (mib->rate[j].peak < (u32) rate)
					mib->rate[j].peak = (u32) rate;
			}
		} else
			mib->rate[j].last = jiffies;
	}
}  /* determine_rate */

static void ksz8795_mib_read_work(struct work_struct *work)
{
	struct sw_priv *hw_priv =
		container_of(work, struct sw_priv, mib_read);
	struct ksz_sw *sw = &hw_priv->sw;
	struct ksz_port_mib *mib;
	unsigned long interval;
	uint n;
	uint p;
	int cnt = 0;

	/* Find out how many ports are connected. */
	for (n = 0; n <= sw->mib_port_cnt; n++) {
		p = get_phy_port(sw, n);
		if (media_connected == sw->port_state[p].state)
			++cnt;
	}
	if (!cnt)
		cnt++;
	interval = MIB_READ_INTERVAL * 2 / cnt;
	if (time_before(sw->next_jiffies, jiffies)) {
		sw->next_jiffies = jiffies;
		sw->next_jiffies += interval;
	}
	for (n = 0; n <= sw->mib_port_cnt; n++) {
		p = get_phy_port(sw, n);
		mib = get_port_mib(sw, p);

		/* Reading MIB counters or requested to read. */
		if (mib->cnt_ptr || 1 == hw_priv->counter[p].read) {

			/* Need to process interrupt. */
			if (port_r_cnt(sw, p))
				return;
			hw_priv->counter[p].read = 0;

			/* Finish reading counters. */
			if (0 == mib->cnt_ptr) {
				hw_priv->counter[p].read = 2;
				wake_up_interruptible(
					&hw_priv->counter[p].counter);
				if (p != sw->HOST_PORT)
					determine_rate(sw, mib);
			}
		} else if (time_after_eq(jiffies, hw_priv->counter[p].time)) {
			hw_priv->counter[p].time = sw->next_jiffies;
			/* Only read MIB counters when the port is connected. */
			if (media_connected == sw->port_state[p].state) {
				hw_priv->counter[p].read = 1;
				sw->next_jiffies += interval;
			}

		/* Port is just disconnected. */
		} else if (sw->port_state[p].link_down) {
			int j;

			for (j = 0; j < TOTAL_SWITCH_COUNTER_NUM; j++)
				mib->read_cnt[j] += mib->read_max[j];
			sw->port_state[p].link_down = 0;

			/* Read counters one last time after link is lost. */
			hw_priv->counter[p].read = 1;
		}
	}
}  /* ksz8795_mib_read_work */

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
	struct ksz_port *port = NULL;
	struct ksz_port *sw_port = NULL;
	int i;
	int changes = 0;
	int s = 1;
	int dev_cnt = sw->dev_count + sw->dev_offset;

	if (1 == sw->dev_count || 1 == sw->dev_offset)
		s = 0;

	/* Check main device when child devices are used. */
	if (sw->dev_offset)
		sw_port = sw->netport[0];
	sw->ops->acquire(sw);
	if (!sw->phy_intr) {
		sw->phy_intr = sw->reg->r8(sw, REG_INT_STATUS);
		sw->phy_intr &= ~INT_PME;
		if (sw->phy_intr)
			sw->reg->w8(sw, REG_INT_STATUS, sw->phy_intr);
	}
	for (i = sw->dev_offset; i < dev_cnt; i++) {
		struct phy_priv *phydata;
		int n = i + s;

		port = sw->netport[i];
		phydata = &sw->phydata[n];
		if (!port)
			port = phydata->port;
		changes |= port_get_link_speed(port);

		/* Copy all port information for user access. */
		if (port != phydata->port)
			copy_port_status(port, phydata->port);
	}

	sw->phy_intr = 0;
	sw->ops->release(sw);

	/* Change linked port for main device if it is not connected. */
	if (!sw_port || (media_connected == sw_port->linked->state))
		changes = 0;

	/* Not to read PHY registers unnecessarily if no link change. */
	if (!changes)
		return;

	for (i = sw->dev_offset; i < dev_cnt; i++) {
		struct phy_priv *phydata;

		port = sw->netport[i];
		if (!port) {
			phydata = &sw->phydata[i];
			port = phydata->port;
		}
		if (media_connected == port->linked->state) {
			sw_port->linked = port->linked;
			break;
		}
	}
}  /* link_read_work */

/*
 * Hardware monitoring
 */

static void ksz8795_mib_monitor(unsigned long ptr)
{
	struct sw_priv *hw_priv = (struct sw_priv *) ptr;

	schedule_work(&hw_priv->mib_read);

	ksz_update_timer(&hw_priv->mib_timer_info);
}  /* ksz8795_mib_monitor */

static void ksz8795_dev_monitor(unsigned long ptr)
{
	struct sw_priv *hw_priv = (struct sw_priv *) ptr;
	struct phy_device *phydev;
	struct phy_priv *priv;
	int i;

	/* For MAC driver that does not add code to device open function. */
	for (i = 0; i <= TOTAL_PORT_NUM; i++) {
		phydev = mdiobus_get_phy(hw_priv->bus, i);
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
}  /* ksz8795_dev_monitor */

static int intr_mode;
static int ports;

static int sw_device_present;

static int ksz_probe(struct sw_priv *ks)
{
	struct ksz_sw *sw = &ks->sw;
	struct ksz_port_info *info;
	u16 id;
	u8 id1;
	u8 id2;
	u8 sku;
	int i;
	uint p;
	uint mib_port_count;
	uint pi;
	uint port_count;
	int ret;

	ks->intr_mode = intr_mode ? IRQF_TRIGGER_FALLING :
		IRQF_TRIGGER_LOW;

	dev_set_drvdata(ks->dev, ks);

	mutex_init(&ks->hwlock);
	mutex_init(&ks->lock);

	sw = &ks->sw;
	mutex_init(&sw->lock);
	mutex_init(&sw->acllock);
	sw->hwlock = &ks->hwlock;
	sw->reglock = &ks->lock;
	sw->dev = ks;

	sw->net_ops = &sw_net_ops;
	sw->ops = &sw_ops;
	init_waitqueue_head(&sw->queue);

	/* simple check for a valid chip being connected to the bus */
	mutex_lock(&ks->lock);
	id = sw->reg->r16(sw, REG_CHIP_ID0);
	mutex_unlock(&ks->lock);
	id1 = id >> 8;
	id2 = id & SW_CHIP_ID_M;
	if (id1 != FAMILY_ID ||
	    (id2 != CHIP_ID_94 && id2 != CHIP_ID_95)) {
		dev_err(ks->dev, "failed to read device ID(0x%x)\n", id);
		ret = -ENODEV;
		goto err_sw;
	}
	dev_info(ks->dev, "chip id 0x%04x\n", id);

	sw->info = kzalloc(sizeof(struct ksz_sw_info), GFP_KERNEL);
	if (!sw->info) {
		ret = -ENOMEM;
		goto err_sw;
	}

	port_count = TOTAL_PORT_NUM;
	mib_port_count = TOTAL_PORT_NUM;

	sku = KSZ8795_SKU;
	sw->chip_id = KSZ8795_SW_CHIP;
	if (CHIP_ID_94 == id2) {
		sku = KSZ8794_SKU;
		sw->chip_id = KSZ8794_SW_CHIP;
		mib_port_count--;
	}
	mutex_lock(&ks->lock);
	for (p = 0; p < SWITCH_PORT_NUM; p++) {
		SW_D remote;

		port_r(sw, p, P_REMOTE_STATUS, &remote);
		if (remote & PORT_FIBER_MODE) {
			sku = KSZ8765_SKU;
			sw->chip_id = KSZ8765_SW_CHIP;
			break;
		}
	}
	mutex_unlock(&ks->lock);
	sw->PORT_INTR_MASK = (1 << port_count) - 1;
	sw->PORT_MASK = (1 << mib_port_count) - 1;

	sw->HOST_PORT = port_count - 1;
	sw->HOST_MASK = (1 << sw->HOST_PORT);

	sw->mib_cnt = TOTAL_SWITCH_COUNTER_NUM;
	sw->mib_port_cnt = mib_port_count;
	sw->port_cnt = port_count;

	sw->id = sw_device_present;

	sw->dev_count = 1;

#ifdef DEBUG
	sw->verbose = 1;
#endif
#if 0
	if (authen)
		sw->overrides |= USE_802_1X_AUTH;
#endif
	if (multi_dev < 0)
		multi_dev = 0;
	if (stp < 0)
		stp = 0;

	/* No specific ports are specified. */
	if (!ports)
		ports = sw->PORT_MASK;
dbg_msg("ports: %x\n", ports);

	ports = sw_setup_zone(sw, ports);

	sw_setup_logical_ports(sw, sku, ports);

	sw->PORT_MASK |= sw->HOST_MASK;
dbg_msg("mask: %x %x\n", sw->HOST_MASK, sw->PORT_MASK);

	dbg_msg("%s\n", kszsw_phy_driver_names[ks->sw.chip_id]);

	INIT_DELAYED_WORK(&ks->link_read, link_read_work);

	mutex_lock(&ks->lock);
	for (pi = 0; pi < SWITCH_PORT_NUM; pi++) {
		SW_D remote;

		/*
		 * Initialize to invalid value so that link detection
		 * is done.
		 */
		info = get_port_info(sw, pi);
		info->link = 0xFF;
		info->state = media_disconnected;
		info->report = true;
		port_r(sw, pi, P_REMOTE_STATUS, &remote);
		if (remote & PORT_FIBER_MODE)
			info->fiber = true;
	}
	mutex_unlock(&ks->lock);
	sw->interface = PHY_INTERFACE_MODE_MII;
	mutex_lock(&ks->lock);
	for (; pi < sw->port_cnt; pi++) {
		u8 ctrl;
		u8 data;
		int speed;
		phy_interface_t phy;

		info = get_port_info(sw, pi);
		ctrl = SW_R(sw, REG_SW_CTRL_4);
#ifdef USE_10_MBIT_MODE
		ctrl |= SW_10_MBIT;
#endif
#ifdef USE_HALF_DUPLEX
		ctrl |= SW_HALF_DUPLEX;
#endif

		data = sw_r8(sw, REG_PORT_5_CTRL_6);
#ifdef USE_GMII_100_MODE
		data &= ~PORT_GMII_1GPS_MODE;
#endif
#ifdef USE_MII_MODE
		data &= ~PORT_INTERFACE_TYPE;
#endif
#ifdef USE_GMII_MODE
		data &= ~PORT_INTERFACE_TYPE;
		data |= PORT_INTERFACE_GMII;
#endif
#ifdef USE_RMII_MODE
		data &= ~PORT_INTERFACE_TYPE;
		data |= PORT_INTERFACE_RMII;
#endif
		switch (data & PORT_INTERFACE_TYPE) {
		case PORT_INTERFACE_GMII:
			phy = PHY_INTERFACE_MODE_GMII;
			speed = 1000;
			if (data & PORT_GMII_1GPS_MODE)
				break;
		case PORT_INTERFACE_MII:
			phy = PHY_INTERFACE_MODE_MII;
			speed = 100;
			break;
		case PORT_INTERFACE_RMII:
			phy = PHY_INTERFACE_MODE_RMII;
			speed = 100;
			break;
		default:
			phy = PHY_INTERFACE_MODE_RGMII;
			if (data & PORT_RGMII_ID_IN_ENABLE)
				phy = PHY_INTERFACE_MODE_RGMII_RXID;
			if (data & PORT_RGMII_ID_IN_ENABLE) {
				if (PHY_INTERFACE_MODE_RGMII_RXID == phy)
					phy = PHY_INTERFACE_MODE_RGMII_ID;
				else
					phy = PHY_INTERFACE_MODE_RGMII_TXID;
			}
			speed = 100;
			if (data & PORT_GMII_1GPS_MODE)
				speed = 1000;
			break;
		}
		info->interface = phy;
		if (sw->HOST_PORT == pi)
			sw->interface = phy;
		if (info->phy)
			info->state = media_disconnected;
		else
			info->state = media_connected;
		if (ctrl & SW_10_MBIT)
			info->tx_rate = 10 * TX_RATE_UNIT;
		else
			info->tx_rate = speed * TX_RATE_UNIT;
		if (ctrl & SW_HALF_DUPLEX)
			info->duplex = 1;
		else
			info->duplex = 2;
		info->flow_ctrl = 0x33;
	}
	mutex_unlock(&ks->lock);

	sw_init_phy_priv(ks);

	ret = ksz_mii_init(ks);
	if (ret)
		goto err_mii;

	if (ks->bus) {
		for (i = 0; i <= sw->port_cnt; i++)
			sw->phy[i] = mdiobus_get_phy(ks->bus, i);
	} else {
		for (i = 0; i <= sw->port_cnt; i++)
			sw->phy[i] = &sw->phy_map[i];
	}

	sw->multi_dev |= multi_dev;
	sw->stp |= stp;
	sw->fast_aging |= fast_aging;
	if (sw->stp)
		sw->features |= STP_SUPPORT;
	if (sw->fast_aging)
		sw->overrides |= FAST_AGING;

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
#ifdef CONFIG_KSZ_DLR
	if (sw->features & DLR_HW)
		ksz_dlr_init(&sw->info->dlr, sw);
#endif
	sw->ops->acquire(sw);
	sw_reset(sw);
	sw_init(sw);
	sw_setup(sw);
	sw_enable(sw);
	sw->ops->release(sw);
	sw->ops->init(sw);

#if 0
	sw->overrides |= SYSFS_PHY_PORT;
#endif

#ifndef CONFIG_KSZ_SWITCH_EMBEDDED
	init_sw_sysfs(sw, &ks->sysfs, ks->dev);
#ifdef CONFIG_KSZ_DLR
	if (sw->features & DLR_HW)
		init_dlr_sysfs(ks->dev);
#endif
#endif
#ifdef KSZSW_REGS_SIZE
	ret = sysfs_create_bin_file(&ks->dev->kobj,
		&kszsw_registers_attr);
#endif
	sema_init(&ks->proc_sem, 1);

	INIT_WORK(&ks->mib_read, ksz8795_mib_read_work);

	/* 500 ms timeout */
	ksz_init_timer(&ks->mib_timer_info, 500 * HZ / 1000,
		ksz8795_mib_monitor, ks);
	ksz_init_timer(&ks->monitor_timer_info, 100 * HZ / 1000,
		ksz8795_dev_monitor, ks);

	ksz_start_timer(&ks->mib_timer_info, ks->mib_timer_info.period);
	if (!(sw->multi_dev & 1) && !sw->stp)
		ksz_start_timer(&ks->monitor_timer_info,
			ks->monitor_timer_info.period * 10);

	sw_device_present++;

#ifdef CONFIG_KSZ_MRP
	if (sw->features & MRP_SUPPORT) {
		struct mrp_info *mrp = &sw->mrp;

		INIT_DELAYED_WORK(&sw->set_mrp, sw_set_mrp);
		mrp->ops = &mrp_ops;
		mrp->ops->init(mrp);
	}
#endif

	if (ks->irq <= 0)
		return 0;
	ks->intr_mask = INT_PORT_1 | INT_PORT_2 |
		INT_PORT_3 | INT_PORT_4 | INT_PME;
	mutex_lock(&ks->lock);
	sw->reg->w8(sw, REG_INT_ENABLE, 0);
	sw->reg->w8(sw, REG_ACL_INT_ENABLE, 0);
	sw->reg->w8(sw, REG_INT_STATUS, ks->intr_mask);
	sw->reg->w8(sw, REG_ACL_INT_STATUS, INT_PORT_ALL);
	mutex_unlock(&ks->lock);
	ret = sw_start_interrupt(ks, dev_name(ks->dev));
	if (ret < 0)
		printk(KERN_WARNING "No switch interrupt\n");
	else {
		mutex_lock(&ks->lock);
		sw->reg->w8(sw, REG_INT_ENABLE, ks->intr_mask);
		sw->reg->w8(sw, REG_ACL_INT_ENABLE, INT_PORT_ALL);
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

static int ksz_remove(struct sw_priv *ks)
{
	struct ksz_sw *sw = &ks->sw;

	ksz_mii_exit(ks);
	ksz_stop_timer(&ks->monitor_timer_info);
	ksz_stop_timer(&ks->mib_timer_info);
	flush_work(&ks->mib_read);

#ifdef KSZSW_REGS_SIZE
	sysfs_remove_bin_file(&ks->dev->kobj, &kszsw_registers_attr);
#endif

#ifndef CONFIG_KSZ_SWITCH_EMBEDDED
#ifdef CONFIG_KSZ_DLR
	if (sw->features & DLR_HW)
		exit_dlr_sysfs(ks->dev);
#endif
	exit_sw_sysfs(sw, &ks->sysfs, ks->dev);
#endif
	sw->ops->exit(sw);
	cancel_delayed_work_sync(&ks->link_read);

	delete_debugfs(ks);

#ifdef CONFIG_KSZ_STP
	ksz_stp_exit(&sw->info->rstp);
#endif
#ifdef CONFIG_KSZ_DLR
	if (sw->features & DLR_HW)
		ksz_dlr_exit(&sw->info->dlr);
#endif
	kfree(sw->info);
	kfree(ks->hw_dev);
	kfree(ks);

	return 0;
}

module_param(intr_mode, int, 0);
MODULE_PARM_DESC(intr_mode,
	"Configure which interrupt mode to use(0=level low, 1=falling)");

module_param(fast_aging, int, 0);
module_param(multi_dev, int, 0);
module_param(stp, int, 0);
MODULE_PARM_DESC(fast_aging, "Fast aging");
MODULE_PARM_DESC(multi_dev, "Multiple device interfaces");
MODULE_PARM_DESC(stp, "STP support");

module_param(ports, int, 0);
MODULE_PARM_DESC(ports,
	"Configure number of ports");

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

