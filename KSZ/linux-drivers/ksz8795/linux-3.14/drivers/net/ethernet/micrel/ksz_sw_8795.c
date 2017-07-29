/**
 * Micrel KSZ8795 switch common code
 *
 * Copyright (c) 2015-2016 Microchip Technology Inc.
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


/* -------------------------------------------------------------------------- */

enum {
	PROC_SW_INFO,

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
	PROC_SET_ACL_INFO,
	PROC_GET_ACL_TABLE,

	PROC_GET_PORT_DUPLEX,
	PROC_GET_PORT_SPEED,
	PROC_SET_LINK_MD,

};

/* -------------------------------------------------------------------------- */

static void sw_acquire(struct ksz_sw *sw)
{
	mutex_lock(&sw->lock);
	sw->reg->lock(sw);
}  /* sw_acquire */

static void sw_release(struct ksz_sw *sw)
{
	sw->reg->unlock(sw);
	mutex_unlock(&sw->lock);
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

	mutex_lock(sw->reglock);
	sw->reg->w16(sw, REG_IND_CTRL_0, ctrl_addr);
	sw_r(sw, REG_IND_DATA_HI, &buf, sizeof(buf));
	mutex_unlock(sw->reglock);
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

	mutex_lock(sw->reglock);
	sw_w(sw, REG_IND_DATA_HI, &buf, sizeof(buf));
	sw->reg->w16(sw, REG_IND_CTRL_0, ctrl_addr);
	mutex_unlock(sw->reglock);
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
	data[0] = sw->reg->r8(sw, REG_IND_DATA_PME_EEE_ACL);
	for (i = 1; i < cnt; i++) {
		++offset;
		sw->reg->w8(sw, REG_IND_CTRL_1, offset);
		data[i] = sw->reg->r8(sw, REG_IND_DATA_PME_EEE_ACL);
	}
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
	sw->reg->w8(sw, REG_IND_DATA_PME_EEE_ACL, data[0]);
	for (i = 1; i < cnt; i++) {
		++offset;
		sw->reg->w8(sw, REG_IND_CTRL_1, offset);
		sw->reg->w8(sw, REG_IND_DATA_PME_EEE_ACL, data[i]);
	}
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

	mutex_lock(sw->reglock);
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

		sw_r(sw, REG_IND_DATA_HI, &buf, sizeof(buf));
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
	mutex_unlock(sw->reglock);

	return rc;
}  /* sw_r_dyn_mac_table */

/**
 * sw_d_dyn_mac_table - dump dynamic MAC table
 * @sw:		The switch instance.
 *
 * This routine dumps dynamic MAC table contents.
 */
static void sw_d_dyn_mac_table(struct ksz_sw *sw)
{
	u16 entries = 0;
	u16 i;
	u8 mac_addr[ETH_ALEN];
	u8 ports = 0;
	u8 timestamp = 0;
	u8 fid = 0;
	int locked = mutex_is_locked(&sw->lock);

	if (locked)
		mutex_unlock(sw->reglock);
	memset(mac_addr, 0, ETH_ALEN);
	i = 0;
	do {
		if (!sw_r_dyn_mac_table(sw, i, mac_addr, &fid, &ports,
				&timestamp, &entries)) {
			printk(KERN_INFO
				"%02X:%02X:%02X:%02X:%02X:%02X %x %x %x %03x\n",
				mac_addr[0], mac_addr[1], mac_addr[2],
				mac_addr[3], mac_addr[4], mac_addr[5],
				fid, ports, timestamp, entries);
		}
		i++;
	} while (i < entries);
	if (locked)
		mutex_lock(sw->reglock);
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
	int locked = mutex_is_locked(&sw->lock);

	if (locked)
		mutex_unlock(sw->reglock);
	sw_r_table_64(sw, TABLE_STATIC_MAC, addr, &data_hi, &data_lo);
	if (locked)
		mutex_lock(sw->reglock);
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
	int locked = mutex_is_locked(&sw->lock);

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

	if (locked)
		mutex_unlock(sw->reglock);
	sw_w_table_64(sw, TABLE_STATIC_MAC, addr, data_hi, data_lo);
	if (locked)
		mutex_lock(sw->reglock);
	mac->dirty = 0;
}  /* sw_w_sta_mac_table */

/**
 * sw_d_sta_mac_table - dump static MAC table
 * @sw:		The switch instance.
 *
 * This routine dumps static MAC table contents.
 */
static void sw_d_sta_mac_table(struct ksz_sw *sw)
{
	u16 i;
	struct ksz_mac_table mac;

	i = 0;
	do {
		if (!sw_r_sta_mac_table(sw, i, &mac)) {
			printk(KERN_INFO
				"%2x: %02X:%02X:%02X:%02X:%02X:%02X "
				"%x %u %u:%x\n",
				i, mac.addr[0], mac.addr[1], mac.addr[2],
				mac.addr[3], mac.addr[4], mac.addr[5],
				mac.ports, mac.override, mac.use_fid, mac.fid);
		}
		i++;
	} while (i < STATIC_MAC_TABLE_ENTRIES);
}  /* sw_d_sta_mac_table */

static void sw_d_mac_table(struct ksz_sw *sw)
{
#if 0
	struct ksz_mac_table *entry;
	int i;

	i = STATIC_MAC_TABLE_ENTRIES;
	do {
		entry = &sw->info->mac_table[i];
		if (entry->valid) {
			printk(KERN_INFO
				"%x: %02X:%02X:%02X:%02X:%02X:%02X "
				"%x %u %u:%x\n",
				i, entry->mac_addr[0], entry->mac_addr[1],
				entry->mac_addr[2], entry->mac_addr[3],
				entry->mac_addr[4], entry->mac_addr[5],
				entry->ports, entry->override, entry->use_fid,
				entry->fid);
		}
		i++;
		if (SWITCH_MAC_TABLE_ENTRIES == i)
			printk(KERN_INFO "\n");
	} while (i < MULTI_MAC_TABLE_ENTRIES);
#endif
}

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
	int locked = mutex_is_locked(&sw->lock);
	int ret = -1;

	if (locked)
		mutex_unlock(sw->reglock);
	sw_r_table_64(sw, TABLE_VLAN, addr, data_hi, data_lo);
	if (locked)
		mutex_lock(sw->reglock);
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
	int locked = mutex_is_locked(&sw->lock);

	addr = vid / 4;
	index = vid & 3;
	if (locked)
		mutex_unlock(sw->reglock);
	sw_r_table_64(sw, TABLE_VLAN, addr, data_hi, data_lo);
	if (locked)
		mutex_lock(sw->reglock);
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
	int locked = mutex_is_locked(&sw->lock);

	addr = vid / 4;
	index = vid & 3;
	if (locked)
		mutex_unlock(sw->reglock);
	sw_r_table_64(sw, TABLE_VLAN, addr, data_hi, data_lo);
	data[index] = vlan->fid;
	data[index] |= (u16) vlan->member << VLAN_TABLE_MEMBERSHIP_S;
	if (vlan->valid)
		data[index] |= VLAN_TABLE_VALID;
	sw_w_table_64(sw, TABLE_VLAN, addr, *data_hi, *data_lo);
	if (locked)
		mutex_lock(sw->reglock);
	vlan->dirty = 0;
}  /* sw_w_vlan_table */

/**
 * sw_d_vlan_table - dump VLAN table
 * @sw:		The switch instance.
 *
 * This routine dumps the VLAN table.
 */
static void sw_d_vlan_table(struct ksz_sw *sw)
{
	u16 i;
	u16 j;
	u16 vid;
	u8 fid[4];
	u8 member[4];
	u8 valid[4];

	i = 0;
	do {
		if (!sw_r_vlan_entries(sw, i, valid, fid, member)) {
			vid = i * 4;
			for (j = 0; j < 4; j++, vid++) {
				if (valid[j])
					printk(KERN_INFO
					"0x%03x: %2x %2x\n", vid,
					fid[j], member[j]);
			}
		}
		yield();
		i++;
	} while (i < VLAN_TABLE_ENTRIES);
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
static void port_r_mib_cnt(struct ksz_sw *sw, int port, u16 addr, u64 *cnt)
{
	u32 data;
	u16 ctrl_addr;
	u8 check;
	int timeout;

	ctrl_addr = addr + SWITCH_COUNTER_NUM * port;

	mutex_lock(sw->reglock);

	ctrl_addr |= IND_ACC_TABLE(TABLE_MIB | TABLE_READ);
	sw->reg->w16(sw, REG_IND_CTRL_0, ctrl_addr);

	for (timeout = 1; timeout > 0; timeout--) {
		check = sw->reg->r8(sw, REG_IND_MIB_CHECK);

		if (check & MIB_COUNTER_VALID) {
			data = sw->reg->r32(sw, REG_IND_DATA_LO);
			if (check & MIB_COUNTER_OVERFLOW)
				*cnt += MIB_COUNTER_VALUE + 1;
			*cnt += data & MIB_COUNTER_VALUE;
			break;
		}
	}

	mutex_unlock(sw->reglock);
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
static void port_r_mib_pkt(struct ksz_sw *sw, int port, u16 addr, u64 *cnt)
{
	u32 data;
	u16 ctrl_addr;
	u8 check;
	int timeout;

	addr -= SWITCH_COUNTER_NUM;
	ctrl_addr = (KS_MIB_TOTAL_RX_1 - KS_MIB_TOTAL_RX_0) * port;
	ctrl_addr += addr + KS_MIB_TOTAL_RX_0;

	mutex_lock(sw->reglock);

	ctrl_addr |= IND_ACC_TABLE(TABLE_MIB | TABLE_READ);
	sw->reg->w16(sw, REG_IND_CTRL_0, ctrl_addr);

	for (timeout = 1; timeout > 0; timeout--) {
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

	mutex_unlock(sw->reglock);
}  /* port_r_mib_pkt */

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
static int port_r_cnt(struct ksz_sw *sw, int port)
{
	struct ksz_port_mib *mib = &sw->port_mib[port];

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
static void sw_cfg_mib_counter_ctrl(struct ksz_sw *sw, int ctrl, int port)
{
	int count;
	int start;
	int stop;
	u8 data;

	if (port < sw->mib_port_cnt) {
		start = port;
		stop = port + 1;
		data = (1 << port);
	} else {
		start = 0;
		stop = sw->mib_port_cnt;
		data = KS_PORT_M;
	}
	if (ctrl & 1)
		data |= SW_MIB_COUNTER_FLUSH;
	if (ctrl & 2)
		data |= SW_MIB_COUNTER_FREEZE;
	SW_W(sw, REG_SW_CTRL_6, data);
	if (ctrl & 1)
		for (count = start; count < stop; count++) {
			struct ksz_port_mib *mib = &sw->port_mib[count];

			memset((void *) mib->counter, 0, sizeof(u64) *
				TOTAL_SWITCH_COUNTER_NUM);
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
static inline void port_init_cnt(struct ksz_sw *sw, int port)
{
	struct ksz_port_mib *mib = &sw->port_mib[port];

	mutex_lock(&sw->lock);
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
	mutex_unlock(&sw->lock);
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
static int port_chk(struct ksz_sw *sw, int port, int offset, SW_D bits)
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
static void port_cfg(struct ksz_sw *sw, int port, int offset, SW_D bits,
	int set)
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
static int port_chk_shift(struct ksz_sw *sw, int port, u32 addr, int shift)
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
static void port_cfg_shift(struct ksz_sw *sw, int port, u32 addr, int shift,
	int set)
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
static void port_r8(struct ksz_sw *sw, int port, int offset, u8 *data)
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
static void port_w8(struct ksz_sw *sw, int port, int offset, u8 data)
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
static void port_r16(struct ksz_sw *sw, int port, int offset, u16 *data)
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
static void port_w16(struct ksz_sw *sw, int port, int offset, u16 data)
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
static u8 port_r_s(struct ksz_sw *sw, int p, u32 reg, u8 mask, u8 shift)
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
static void port_w_s(struct ksz_sw *sw, int p, u32 reg, u8 mask, u8 shift,
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
static void sw_cfg(struct ksz_sw *sw, u32 addr, SW_D bits, int set)
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

static inline void port_cfg_acl(struct ksz_sw *sw, int p, int set)
{
	port_cfg(sw, p,
		REG_PORT_CTRL_5, PORT_ACL_ENABLE, set);
}

static inline int port_chk_acl(struct ksz_sw *sw, int p)
{
	return port_chk(sw, p,
		REG_PORT_CTRL_5, PORT_ACL_ENABLE);
}

static inline u8 port_get_authen_mode(struct ksz_sw *sw, int p)
{
	return port_r_s(sw, p,
		REG_PORT_CTRL_5, PORT_AUTHEN_MODE, 0);
}

static void port_set_authen_mode(struct ksz_sw *sw, int p, u8 mode)
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

	memcpy(data, acl->data, ACL_TABLE_LEN);
	data[0] = acl->first_rule & ACL_FIRST_RULE_M;
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
			ptr_16 = (u16 *) &data[10];
			*ptr_16 = cpu_to_be16((acl->cnt & ACL_CNT_M) <<
				ACL_CNT_S);
			data[ACL_INTR_CNT_START] = 0;
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
	ptr_16 = (u16 *) &data[ACL_RULESET_START];
	*ptr_16 = cpu_to_be16(acl->ruleset);
}  /* set_acl_table_info */

/**
 * wait_for_acl_table - Wait for ACL table
 * @sw:		The switch instance.
 * @port:	The port index.
 *
 * This helper routine waits for ACL table to be ready for access.
 */
static void wait_for_acl_table(struct ksz_sw *sw, int port)
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
static void sw_r_acl_hw(struct ksz_sw *sw, int port, u16 addr, u8 data[])
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
static int sw_r_acl_table(struct ksz_sw *sw, int port, u16 addr,
	struct ksz_acl_table *acl)
{
	u8 data[20];
	int rc = -1;

	mutex_lock(sw->reglock);
	wait_for_acl_table(sw, port);
	sw_r_acl_hw(sw, port, addr, data);
	get_acl_table_info(acl, data);
	memcpy(acl->data, data, ACL_TABLE_LEN);
	mutex_unlock(sw->reglock);
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
static void sw_a_acl_hw(struct ksz_sw *sw, int port, u16 addr, u8 data[])
{
	u8 ctrl = (addr & PORT_ACL_INDEX_M) | PORT_ACL_WRITE;

	if (sw->info->port_cfg[port].acl_byte_enable != ACL_ACTION_ENABLE) {
		sw->info->port_cfg[port].acl_byte_enable = ACL_ACTION_ENABLE;
		sw_w_ext_table(sw, TABLE_ACL, port + 1,
			REG_PORT_ACL_BYTE_EN_MSB, 0);
		sw_w_ext_table(sw, TABLE_ACL, port + 1,
			REG_PORT_ACL_BYTE_EN_LSB, ACL_ACTION_ENABLE);
	}
	port++;
	sw_p_ext_table(sw, TABLE_ACL, port, 0, data, ACL_TABLE_LEN);
	sw_w_ext_table(sw, TABLE_ACL, port, REG_PORT_ACL_CTRL_0, ctrl);
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
static void sw_s_acl_hw(struct ksz_sw *sw, int port, u16 addr, u8 data)
{
	u8 ctrl = (addr & PORT_ACL_INDEX_M) | PORT_ACL_WRITE;

	if (sw->info->port_cfg[port].acl_byte_enable != ACL_MODE_ENABLE) {
		sw->info->port_cfg[port].acl_byte_enable = ACL_MODE_ENABLE;
		sw_w_ext_table(sw, TABLE_ACL, port + 1,
			REG_PORT_ACL_BYTE_EN_MSB, ACL_MODE_ENABLE >> 8);
		sw_w_ext_table(sw, TABLE_ACL, port + 1,
			REG_PORT_ACL_BYTE_EN_LSB, 0);
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
static void sw_w_acl_hw(struct ksz_sw *sw, int port, u16 addr, u8 data[],
	u16 byte_enable)
{
	u8 ctrl = (addr & PORT_ACL_INDEX_M) | PORT_ACL_WRITE;

	if (sw->info->port_cfg[port].acl_byte_enable != byte_enable) {
		sw->info->port_cfg[port].acl_byte_enable = byte_enable;
		sw_w_ext_table(sw, TABLE_ACL, port + 1,
			REG_PORT_ACL_BYTE_EN_MSB, byte_enable >> 8);
		sw_w_ext_table(sw, TABLE_ACL, port + 1,
			REG_PORT_ACL_BYTE_EN_LSB, (u8) byte_enable);
	}
	port++;
	sw_p_ext_table(sw, TABLE_ACL, port, 0, data, ACL_TABLE_LEN);
	sw_w_ext_table(sw, TABLE_ACL, port, REG_PORT_ACL_CTRL_0, ctrl);
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
static void sw_w_acl_action(struct ksz_sw *sw, int port, u16 addr,
	struct ksz_acl_table *acl)
{
	u8 data[20];

	mutex_lock(sw->reglock);
	wait_for_acl_table(sw, port);
	set_acl_action_info(acl, data);
	sw_a_acl_hw(sw, port, addr, data);
	memcpy(&acl->data[ACL_ACTION_START], &data[ACL_ACTION_START],
		ACL_ACTION_LEN);
	mutex_unlock(sw->reglock);
	acl->action_changed = 0;
}  /* sw_w_acl_action */

/**
 * sw_w_acl_table - write to ACL matching and process fields
 * @sw:		The switch instance.
 * @port:	The port index.
 * @addr:	The address of the table entry.
 * @acl:	The ACL entry.
 *
 * This routine writes to the matching and process fields of an entry of the
 * ACL table of the port.
 */
static void sw_w_acl_table(struct ksz_sw *sw, int port, u16 addr,
	struct ksz_acl_table *acl)
{
	u8 data[20];
	u16 byte_enable = ACL_MATCH_ENABLE;

	if (ACL_MODE_LAYER_2 == acl->mode && ACL_ENABLE_2_COUNT == acl->enable)
		byte_enable = ACL_BYTE_ENABLE;
	mutex_lock(sw->reglock);
	wait_for_acl_table(sw, port);
	set_acl_table_info(acl, data);
	if (data[0] == acl->data[0] && !memcmp(&data[2], &acl->data[2], 12))
		sw_s_acl_hw(sw, port, addr, data[1]);
	else
		sw_w_acl_hw(sw, port, addr, data, byte_enable);
	memcpy(acl->data, data, ACL_ACTION_START);
	memcpy(&acl->data[ACL_RULESET_START], &data[ACL_RULESET_START], 2);
	mutex_unlock(sw->reglock);
	acl->changed = 0;
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
			"%x:%04x [%u]\n",
			index,
			acl->mac[0], acl->mac[1], acl->mac[2],
			acl->mac[3], acl->mac[4], acl->mac[5],
			acl->eth_type,
			cnt, acl->intr_mode, acl->cnt, msec,
			enable, acl->enable,
			src, acl->src, equal, acl->equal,
			acl->first_rule, acl->ruleset,
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
			"%x:%04x [%u]\n",
			index,
			acl->ip4_addr[0], acl->ip4_addr[1],
			acl->ip4_addr[2], acl->ip4_addr[3],
			acl->ip4_mask[0], acl->ip4_mask[1],
			acl->ip4_mask[2], acl->ip4_mask[3],
			enable, acl->enable,
			src, acl->src, equal, acl->equal,
			acl->first_rule, acl->ruleset,
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
			"%x:%04x [%u]\n",
			index,
			acl->port_mode, acl->min_port, acl->max_port,
			protocol, acl->protocol, seqnum, acl->seqnum,
			flag, acl->tcp_flag_enable,
			acl->tcp_flag, acl->tcp_flag_mask,
			enable, acl->enable,
			src, acl->src, equal, acl->equal,
			acl->first_rule, acl->ruleset,
			acl->changed ? 8 : acl->mode);
		break;
	default:
		len += sprintf(buf + len,
			"%x: "
			"%c:%u %c:%u %c:%u "
			"%x:%04x [%u]\n",
			index,
			enable, acl->enable,
			src, acl->src, equal, acl->equal,
			acl->first_rule, acl->ruleset,
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
static void sw_d_acl_table(struct ksz_sw *sw, int port)
{
	struct ksz_port_cfg *cfg = &sw->info->port_cfg[port];
	struct ksz_acl_table *acl;
	int i;
	char buf[100];
	int len;
	int min = 0;

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
			printk(KERN_INFO "rules:\n");
		cfg->acl_info[acl->first_rule].action_selected = true;
		len = acl_info(acl, i, buf, 0);
		printk(KERN_INFO "%s", buf);
		min = 1;
	}
	if (min)
		printk(KERN_INFO "\n");
	min = 0;
	for (i = 0; i < ACL_TABLE_ENTRIES; i++) {
		acl = &cfg->acl_info[i];
		if (ACL_PRIO_MODE_DISABLE == acl->prio_mode &&
		    ACL_MAP_MODE_DISABLE == acl->map_mode &&
		    !acl->vlan_prio_replace && !acl->action_selected)
			continue;
		if (ACL_MODE_LAYER_2 == acl->mode &&
		    ACL_ENABLE_2_COUNT == acl->enable)
			continue;
		if (!min)
			printk(KERN_INFO "actions:\n");
		len = acl_action_info(acl, i, buf, 0);
		printk(KERN_INFO "%s", buf);
		min = 1;
	}
}  /* sw_d_acl_table */

static void sw_reset_acl(struct ksz_sw *sw)
{
	struct ksz_port_cfg *cfg;
	int port;

	for (port = 0; port < sw->mib_port_cnt; port++) {
		if (port == sw->port_cnt)
			continue;
		cfg = &sw->info->port_cfg[port];
		memset(cfg->acl_info, 0, sizeof(struct ksz_acl_table) *
			ACL_TABLE_ENTRIES);
		cfg->acl_index = cfg->acl_act_index = 0;
	}
}  /* sw_reset_acl */

static void sw_reset_acl_hw(struct ksz_sw *sw)
{
	struct ksz_port_cfg *cfg;
	struct ksz_acl_table *acl;
	int i;
	int port;

	sw_reset_acl(sw);
	for (port = 0; port < sw->mib_port_cnt; port++) {
		if (port == sw->port_cnt)
			continue;
		cfg = &sw->info->port_cfg[port];
		for (i = 0; i < ACL_TABLE_ENTRIES; i++) {
			acl = &cfg->acl_info[i];
			acl->data[0] = 0xff;
			acl->mode = 0;
			mutex_unlock(sw->reglock);
			sw_w_acl_action(sw, port, i, acl);
			sw_w_acl_table(sw, port, i, acl);
			mutex_lock(sw->reglock);
		}
	}
}  /* sw_reset_acl_hw */

static void sw_init_acl(struct ksz_sw *sw)
{
	struct ksz_port_cfg *cfg;
	struct ksz_acl_table *acl;
	int i;
	int port;

	for (port = 0; port < sw->mib_port_cnt; port++) {
		if (port == sw->port_cnt)
			continue;
		port_cfg_acl(sw, port, 1);
		cfg = &sw->info->port_cfg[port];
		for (i = 0; i < ACL_TABLE_ENTRIES; i++) {
			acl = &cfg->acl_info[i];
			mutex_unlock(sw->reglock);
			sw_r_acl_table(sw, port, i, acl);
			mutex_lock(sw->reglock);
		}
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

static u8 port_get_pme_ctrl(struct ksz_sw *sw, int p)
{
	u8 data;

	sw_r_ext_table(sw, TABLE_PME, p + 1, 7, &data);
	return data;
}

static void port_set_pme_ctrl(struct ksz_sw *sw, int p, u8 pme)
{
	sw_w_ext_table(sw, TABLE_PME, p + 1, 7, pme);
}

static u8 port_get_pme_status(struct ksz_sw *sw, int p)
{
	u8 data;

	sw_r_ext_table(sw, TABLE_PME, p + 1, 3, &data);
	return data;
}

static void port_set_pme_status(struct ksz_sw *sw, int p, u8 pme)
{
	sw_w_ext_table(sw, TABLE_PME, p + 1, 3, pme);
}

/* -------------------------------------------------------------------------- */

/* Bandwidth */

static inline void port_cfg_broad_storm(struct ksz_sw *sw, int p, int set)
{
	port_cfg(sw, p,
		P_BCAST_STORM_CTRL, PORT_BROADCAST_STORM, set);
}

static inline int port_chk_broad_storm(struct ksz_sw *sw, int p)
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
static void sw_dis_broad_storm(struct ksz_sw *sw, int port)
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
static void sw_ena_broad_storm(struct ksz_sw *sw, int port)
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
	int port;

	/* Enable switch broadcast storm protection at 10% percent rate. */
	hw_cfg_broad_storm(sw, BROADCAST_STORM_PROTECTION_RATE);
	for (port = 0; port < sw->mib_port_cnt; port++) {
		if (port == sw->port_cnt)
			continue;
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
static void hw_cfg_rate_ctrl(struct ksz_sw *sw, int port, int prio, int ctrl)
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
static void hw_cfg_rate_ratio(struct ksz_sw *sw, int port, int prio, u8 ratio)
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
static void hw_get_rate_ctrl(struct ksz_sw *sw, int port, int prio)
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
static void hw_cfg_rate_limit(struct ksz_sw *sw, int port, u8 mask, u8 shift,
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

static void hw_cfg_in_port_based(struct ksz_sw *sw, int port, int set)
{
	hw_cfg_rate_limit(sw, port, 1, PORT_IN_PORT_BASED_S, set != 0);
}

static void hw_cfg_rate_packet_based(struct ksz_sw *sw, int port, int set)
{
	sw->info->port_cfg[port].packet_based = set;
	hw_cfg_rate_limit(sw, port, 1, PORT_RATE_PACKET_BASED_S, set != 0);
}

static void hw_cfg_in_flow_ctrl(struct ksz_sw *sw, int port, int set)
{
	hw_cfg_rate_limit(sw, port, 1, PORT_IN_FLOW_CTRL_S, set != 0);
}

/**
 * hw_cfg_cnt_ifg - configure port rate limit count IFG control
 * @sw:		The switch instance.
 * @port:	The port index.
 * @set:	The flag indicating whether the count control is set or not.
 *
 * This routine configures the rate limit count IFG control of the port.
 */
static void hw_cfg_cnt_ifg(struct ksz_sw *sw, int port, int set)
{
	hw_cfg_rate_limit(sw, port, 1, PORT_COUNT_IFG_S, set != 0);
}  /* hw_cfg_cnt_ifg */

/**
 * hw_cfg_cnt_pre - configure port rate limit count preamble control
 * @sw:		The switch instance.
 * @port:	The port index.
 * @set:	The flag indicating whether the count control is set or not.
 *
 * This routine configures the rate limit count preamble control of the port.
 */
static void hw_cfg_cnt_pre(struct ksz_sw *sw, int port, int set)
{
	hw_cfg_rate_limit(sw, port, 1, PORT_COUNT_PREAMBLE_S, set != 0);
}  /* hw_cfg_cnt_pre */

/**
 * hw_cfg_rx_limit - configure port rate limit mode
 * @sw:		The switch instance.
 * @port:	The port index.
 * @mode:	The rate limit mode.
 *
 * This routine configures the rate limit mode of the port.
 */
static void hw_cfg_rx_limit(struct ksz_sw *sw, int port, u8 mode)
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
static void hw_get_rate_limit(struct ksz_sw *sw, int port)
{
	u8 data;

	port_r8(sw, port, P_RATE_LIMIT_CTRL, &data);
	sw->info->port_cfg[port].rate_limit = data;
	sw->info->port_cfg[port].packet_based = (data >>
		PORT_RATE_PACKET_BASED_S) & 1;
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
 * @rate:	The rate limit in number of Kbps.
 * @packet:	Packet indication.
 *
 * This helper routine configures the priority rate of the port.
 */
static void port_cfg_rate(struct ksz_sw *sw, int port, int prio, int offset,
	uint rate, int packet)
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
 * @rate:	Buffer to store the data rate in number of Kbps.
 * @packet:	Buffer to store the data rate in number of packets.
 *
 * This helper routine retrieves the priority rate of the port.
 */
static void port_get_rate(struct ksz_sw *sw, int port, int prio, int offset,
	uint *rate, uint *packet)
{
	u8 data;

	port_r8(sw, port, offset + prio, &data);
	*rate = get_rate_from_val(data);
	*packet = get_packet_from_val(data);
}  /* port_get_rate */

/**
 * hw_cfg_prio_rate - configure port priority
 * @sw:		The switch instance.
 * @port:	The port index.
 * @prio:	The priority index to configure.
 * @rate:	The rate limit in number of Kbps.
 * @offset:	The receive or transmit rate offset.
 * @result:	Buffer to store the data rate in number of Kbps.
 * @r_packet:	Buffer to store the data rate in number of packets.
 *
 * This helper routine configures the priority rate of the port and retrieves
 * the actual rate number.
 */
static void hw_cfg_prio_rate(struct ksz_sw *sw, int port, int prio, uint rate,
	int packet, int offset, uint *result_rate, uint *r_packet)
{
	port_cfg_rate(sw, port, prio, offset, rate, packet);
	port_get_rate(sw, port, prio, offset, result_rate, r_packet);
}  /* hw_cfg_prio_rate */

/**
 * hw_cfg_rx_prio_rate - configure port receive priority
 * @sw:		The switch instance.
 * @port:	The port index.
 * @prio:	The priority index to configure.
 * @rate:	The rate limit in number of Kbps.
 *
 * This routine configures the receive priority rate of the port.
 * It is called by user functions.  The hardware should be acquired first.
 */
static void hw_cfg_rx_prio_rate(struct ksz_sw *sw, int port, int prio,
	uint rate)
{
	hw_cfg_prio_rate(sw, port, prio, rate,
		sw->info->port_cfg[port].packet_based,
		REG_PORT_IN_RATE_0,
		&sw->info->port_cfg[port].rx_rate[prio],
		&sw->info->port_cfg[port].rx_packet[prio]);
}  /* hw_cfg_rx_prio_rate */

/**
 * hw_cfg_tx_prio_rate - configure port transmit priority
 * @sw:		The switch instance.
 * @port:	The port index.
 * @prio:	The priority index to configure.
 * @rate:	The rate limit in number of Kbps.
 *
 * This routine configures the transmit priority rate of the port.
 * It is called by user functions.  The hardware should be acquired first.
 */
static void hw_cfg_tx_prio_rate(struct ksz_sw *sw, int port, int prio,
	uint rate)
{
	hw_cfg_prio_rate(sw, port, prio, rate,
		sw->info->port_cfg[port].packet_based,
		REG_PORT_OUT_RATE_0,
		&sw->info->port_cfg[port].tx_rate[prio],
		&sw->info->port_cfg[port].tx_packet[prio]);
}  /* hw_cfg_tx_prio_rate */

/**
 * sw_chk_rx_prio_rate - check switch receive priority rate
 * @sw:		The switch instance.
 * @port:	The port index.
 *
 * This function checks whether the priority rate function of the switch is
 * enabled.
 *
 * Return 0 if not enabled.
 */
static int sw_chk_rx_prio_rate(struct ksz_sw *sw, int port)
{
	u8 data;

	port_r8(sw, port, REG_PORT_IN_RATE_3, &data);
	return data & PORT_IN_RATE_ENABLE;
}  /* sw_chk_rx_prio_rate */

/**
 * sw_dis_rx_prio_rate - disable switch priority rate
 * @sw:		The switch instance.
 * @port:	The port index.
 *
 * This routine disables the priority rate function of the switch.
 */
static void sw_dis_rx_prio_rate(struct ksz_sw *sw, int port)
{
	u8 data;

	port_r8(sw, port, REG_PORT_IN_RATE_3, &data);
	data &= ~PORT_IN_RATE_ENABLE;
	port_w8(sw, port, REG_PORT_IN_RATE_3, data);
}  /* sw_dis_rx_prio_rate */

/**
 * sw_ena_prio_rate - enable switch priority rate
 * @sw:		The switch instance.
 * @port:	The port index.
 *
 * This routine enables the priority rate function of the switch.
 */
static void sw_ena_rx_prio_rate(struct ksz_sw *sw, int port)
{
	int prio;
	u8 data;

	for (prio = 0; prio < PRIO_QUEUES; prio++) {
		if (sw->info->port_cfg[port].packet_based)
			hw_cfg_rx_prio_rate(sw, port, prio,
				sw->info->port_cfg[port].rx_packet[prio]);
		else
			hw_cfg_rx_prio_rate(sw, port, prio,
				sw->info->port_cfg[port].rx_rate[prio]);
	}
	port_r8(sw, port, REG_PORT_IN_RATE_3, &data);
	data |= PORT_IN_RATE_ENABLE;
	port_w8(sw, port, REG_PORT_IN_RATE_3, data);
}  /* sw_ena_rx_prio_rate */

/**
 * sw_chk_tx_prio_rate - check switch priority rate
 * @sw:		The switch instance.
 * @port:	The port index.
 *
 * This function checks whether the priority rate function of the switch is
 * enabled.
 *
 * Return 0 if not enabled.
 */
static int sw_chk_tx_prio_rate(struct ksz_sw *sw, int port)
{
	u32 addr;
	u32 rate_addr;
	u32 out_rate;

	PORT_CTRL_ADDR(port, addr);
	rate_addr = addr + REG_PORT_OUT_RATE_0;
	out_rate = sw->reg->r32(sw, rate_addr);
	return out_rate != 0;
}  /* sw_chk_tx_prio_rate */

/**
 * sw_dis_tx_prio_rate - disable switch priority rate
 * @sw:		The switch instance.
 * @port:	The port index.
 *
 * This routine disables the priority rate function of the switch.
 */
static void sw_dis_tx_prio_rate(struct ksz_sw *sw, int port)
{
	u32 addr;
	u32 rate_addr;

	PORT_CTRL_ADDR(port, addr);
	rate_addr = addr + REG_PORT_OUT_RATE_0;
	sw->reg->w32(sw, rate_addr, 0);
}  /* sw_dis_tx_prio_rate */

/**
 * sw_ena_tx_prio_rate - enable switch priority rate
 * @sw:		The switch instance.
 * @port:	The port index.
 *
 * This routine enables the priority rate function of the switch.
 */
static void sw_ena_tx_prio_rate(struct ksz_sw *sw, int port)
{
	int prio;

	for (prio = 0; prio < PRIO_QUEUES; prio++) {
		if (sw->info->port_cfg[port].packet_based)
			hw_cfg_tx_prio_rate(sw, port, prio,
				sw->info->port_cfg[port].tx_packet[prio]);
		else
			hw_cfg_tx_prio_rate(sw, port, prio,
				sw->info->port_cfg[port].tx_rate[prio]);
	}
}  /* sw_ena_tx_prio_rate */

/**
 * sw_init_prio_rate - initialize switch prioirty rate
 * @sw:		The switch instance.
 *
 * This routine initializes the priority rate function of the switch.
 */
static void sw_init_prio_rate(struct ksz_sw *sw)
{
	int offset;
	int port;
	int prio;

	for (port = 0; port < TOTAL_PORT_NUM; port++) {
		if (port == sw->port_cnt)
			continue;
		hw_get_rate_limit(sw, port);
		for (prio = 0; prio < PRIO_QUEUES; prio++) {
			hw_get_rate_ctrl(sw, port, prio);
			offset = REG_PORT_IN_RATE_0;
			port_get_rate(sw, port, prio, offset,
				&sw->info->port_cfg[port].rx_rate[prio],
				&sw->info->port_cfg[port].rx_packet[prio]);
			offset = REG_PORT_OUT_RATE_0;
			port_get_rate(sw, port, prio, offset,
				&sw->info->port_cfg[port].tx_rate[prio],
				&sw->info->port_cfg[port].tx_packet[prio]);
		}
	}
}  /* sw_init_prio_rate */

/* -------------------------------------------------------------------------- */

/* Communication */

static inline void port_cfg_back_pressure(struct ksz_sw *sw, int p, int set)
{
	port_cfg(sw, p,
		P_STP_CTRL, PORT_BACK_PRESSURE, set);
}

static inline void port_cfg_force_flow_ctrl(struct ksz_sw *sw, int p, int set)
{
	port_cfg(sw, p,
		P_STP_CTRL, PORT_FORCE_FLOW_CTRL, set);
}

static inline int port_chk_back_pressure(struct ksz_sw *sw, int p)
{
	return port_chk(sw, p,
		P_STP_CTRL, PORT_BACK_PRESSURE);
}

static inline int port_chk_force_flow_ctrl(struct ksz_sw *sw, int p)
{
	return port_chk(sw, p,
		P_STP_CTRL, PORT_FORCE_FLOW_CTRL);
}

/* -------------------------------------------------------------------------- */

/* Spanning Tree */

static inline void port_cfg_dis_learn(struct ksz_sw *sw, int p, int set)
{
	port_cfg(sw, p,
		P_STP_CTRL, PORT_LEARN_DISABLE, set);
}

static inline void port_cfg_rx(struct ksz_sw *sw, int p, int set)
{
	port_cfg(sw, p,
		P_STP_CTRL, PORT_RX_ENABLE, set);
	if (set)
		sw->rx_ports |= (1 << p);
	else
		sw->rx_ports &= ~(1 << p);
}

static inline void port_cfg_tx(struct ksz_sw *sw, int p, int set)
{
	port_cfg(sw, p,
		P_STP_CTRL, PORT_TX_ENABLE, set);
	if (set)
		sw->tx_ports |= (1 << p);
	else
		sw->tx_ports &= ~(1 << p);
}

static inline int port_chk_dis_learn(struct ksz_sw *sw, int p)
{
	return port_chk(sw, p,
		P_STP_CTRL, PORT_LEARN_DISABLE);
}

static inline int port_chk_rx(struct ksz_sw *sw, int p)
{
	return port_chk(sw, p,
		P_STP_CTRL, PORT_RX_ENABLE);
}

static inline int port_chk_tx(struct ksz_sw *sw, int p)
{
	return port_chk(sw, p,
		P_STP_CTRL, PORT_TX_ENABLE);
}

static inline void sw_cfg_fast_aging(struct ksz_sw *sw, int set)
{
	sw_cfg(sw, REG_SW_CTRL_1, SW_FAST_AGING, set);
}

static void sw_flush_dyn_mac_table(struct ksz_sw *sw, int port)
{
	int cnt;
	int first;
	int index;
	int learn_disable[TOTAL_PORT_NUM];

	if ((uint) port < TOTAL_PORT_NUM) {
		first = port;
		cnt = port + 1;
	} else {
		first = 0;
		cnt = TOTAL_PORT_NUM;
	}
	for (index = first; index < cnt; index++) {
		if (index == sw->port_cnt)
			continue;
		learn_disable[index] = port_chk_dis_learn(sw, index);
		if (!learn_disable[index])
			port_cfg_dis_learn(sw, index, 1);
	}
	sw_cfg(sw, S_FLUSH_TABLE_CTRL, SW_FLUSH_DYN_MAC_TABLE, 1);
	for (index = first; index < cnt; index++) {
		if (index == sw->port_cnt)
			continue;
		if (!learn_disable[index])
			port_cfg_dis_learn(sw, index, 0);
	}
}

/* -------------------------------------------------------------------------- */

/* VLAN */

static inline void port_cfg_ins_tag(struct ksz_sw *sw, int p, int insert)
{
	port_cfg(sw, p,
		P_TAG_CTRL, PORT_INSERT_TAG, insert);
}

static inline void port_cfg_rmv_tag(struct ksz_sw *sw, int p, int remove)
{
	port_cfg(sw, p,
		P_TAG_CTRL, PORT_REMOVE_TAG, remove);
}

static inline int port_chk_ins_tag(struct ksz_sw *sw, int p)
{
	return port_chk(sw, p,
		P_TAG_CTRL, PORT_INSERT_TAG);
}

static inline int port_chk_rmv_tag(struct ksz_sw *sw, int p)
{
	return port_chk(sw, p,
		P_TAG_CTRL, PORT_REMOVE_TAG);
}

static inline void port_cfg_dis_non_vid(struct ksz_sw *sw, int p, int set)
{
	port_cfg(sw, p,
		P_STP_CTRL, PORT_DISCARD_NON_VID, set);
}

static inline void port_cfg_drop_tag(struct ksz_sw *sw, int p, int set)
{
	port_cfg(sw, p,
		P_DROP_TAG_CTRL, PORT_DROP_TAG, set);
}

static inline void port_cfg_in_filter(struct ksz_sw *sw, int p, int set)
{
	port_cfg(sw, p,
		P_STP_CTRL, PORT_INGRESS_FILTER, set);
}

static inline int port_chk_dis_non_vid(struct ksz_sw *sw, int p)
{
	return port_chk(sw, p,
		P_STP_CTRL, PORT_DISCARD_NON_VID);
}

static inline int port_chk_drop_tag(struct ksz_sw *sw, int p)
{
	return port_chk(sw, p,
		P_DROP_TAG_CTRL, PORT_DROP_TAG);
}

static inline int port_chk_in_filter(struct ksz_sw *sw, int p)
{
	return port_chk(sw, p,
		P_STP_CTRL, PORT_INGRESS_FILTER);
}

/* -------------------------------------------------------------------------- */

/* Mirroring */

static inline void port_cfg_mirror_sniffer(struct ksz_sw *sw, int p, int set)
{
	port_cfg(sw, p,
		P_MIRROR_CTRL, PORT_MIRROR_SNIFFER, set);
}

static inline void port_cfg_mirror_rx(struct ksz_sw *sw, int p, int set)
{
	port_cfg(sw, p,
		P_MIRROR_CTRL, PORT_MIRROR_RX, set);
}

static inline void port_cfg_mirror_tx(struct ksz_sw *sw, int p, int set)
{
	port_cfg(sw, p,
		P_MIRROR_CTRL, PORT_MIRROR_TX, set);
}

static inline void sw_cfg_mirror_rx_tx(struct ksz_sw *sw, int set)
{
	sw_cfg(sw, S_MIRROR_CTRL, SW_MIRROR_RX_TX, set);
}

static inline int port_chk_mirror_sniffer(struct ksz_sw *sw, int p)
{
	return port_chk(sw, p,
		P_MIRROR_CTRL, PORT_MIRROR_SNIFFER);
}

static inline int port_chk_mirror_rx(struct ksz_sw *sw, int p)
{
	return port_chk(sw, p,
		P_MIRROR_CTRL, PORT_MIRROR_RX);
}

static inline int port_chk_mirror_tx(struct ksz_sw *sw, int p)
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
	int port;

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
	for (port = 0; port < TOTAL_PORT_NUM; port++) {
		if (port == sw->port_cnt)
			continue;
		port_cfg_mirror_sniffer(sw, port, 0);
		port_cfg_mirror_rx(sw, port, 0);
		port_cfg_mirror_tx(sw, port, 0);
	}
	sw_cfg_mirror_rx_tx(sw, 0);
}

/* -------------------------------------------------------------------------- */

static void sw_cfg_unk_dest(struct ksz_sw *sw, u8 offset, int set)
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

static int sw_chk_unk_def_port(struct ksz_sw *sw, u8 offset, int port)
{
	u8 data;
	u8 bit = 1 << port;

	data = sw->reg->r8(sw, offset);
	if (port >= sw->mib_port_cnt)
		return data & SW_UNK_FWD_MAP;
	return (data & bit) == bit;
}

static inline int sw_chk_self_filter(struct ksz_sw *sw)
{
	return sw_chk(sw, REG_SW_UNK_IP_MCAST_CTRL,
		SW_SELF_ADDR_FILTER_ENABLE);
}

static inline void sw_cfg_self_filter(struct ksz_sw *sw, int set)
{
	sw_cfg(sw, REG_SW_UNK_IP_MCAST_CTRL, SW_SELF_ADDR_FILTER_ENABLE, set);
}

static void sw_cfg_src_filter(struct ksz_sw *sw, int set)
{
}  /* sw_cfg_src_filter */

/* -------------------------------------------------------------------------- */

/* Priority */

static inline void port_cfg_diffserv(struct ksz_sw *sw, int p, int set)
{
	port_cfg(sw, p,
		P_PRIO_CTRL, PORT_DIFFSERV_ENABLE, set);
}

static inline void port_cfg_802_1p(struct ksz_sw *sw, int p, int set)
{
	port_cfg(sw, p,
		P_PRIO_CTRL, PORT_802_1P_ENABLE, set);
}

static inline void port_cfg_replace_prio(struct ksz_sw *sw, int p, int set)
{
	port_cfg(sw, p,
		P_802_1P_CTRL, PORT_802_1P_REMAPPING, set);
}

static inline int port_chk_diffserv(struct ksz_sw *sw, int p)
{
	return port_chk(sw, p,
		P_PRIO_CTRL, PORT_DIFFSERV_ENABLE);
}

static inline int port_chk_802_1p(struct ksz_sw *sw, int p)
{
	return port_chk(sw, p,
		P_PRIO_CTRL, PORT_802_1P_ENABLE);
}

static inline int port_chk_replace_prio(struct ksz_sw *sw, int p)
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
static void sw_dis_diffserv(struct ksz_sw *sw, int port)
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
static void sw_ena_diffserv(struct ksz_sw *sw, int port)
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
static void sw_dis_802_1p(struct ksz_sw *sw, int port)
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
static void sw_ena_802_1p(struct ksz_sw *sw, int port)
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
static void sw_cfg_replace_null_vid(struct ksz_sw *sw, int set)
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
static void sw_cfg_replace_prio(struct ksz_sw *sw, int port, int set)
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
static void sw_cfg_port_based(struct ksz_sw *sw, int port, u8 prio)
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
}

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
}

/**
 * port_get_prio_queue - check transmit multiple queues
 * @sw:		The switch instance.
 * @port:	The port index.
 *
 * This function checks number of transmit queues enabled in the port.
 */
static int port_get_prio_queue(struct ksz_sw *sw, int port)
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
 * port.  The port transmit queue is split into four priority queues.
 */
static void port_set_prio_queue(struct ksz_sw *sw, int port, int queue)
{
	u8 hi;
	u8 lo;

	switch (queue) {
	case 4:
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
}  /* port_set_prio_queue */

/**
 * sw_init_prio - initialize switch priority
 * @sw:		The switch instance.
 *
 * This routine initializes the switch QoS priority functions.
 */
static void sw_init_prio(struct ksz_sw *sw)
{
	int port;
	SW_D data;

	sw->reg->r(sw, S_802_1P_PRIO_CTRL, sw->info->p_802_1p,
		PRIO_802_1P_ENTRIES / KS_PRIO_IN_REG);

	sw->reg->r(sw, S_TOS_PRIO_CTRL, sw->info->diffserv,
		DIFFSERV_ENTRIES / KS_PRIO_IN_REG);

	for (port = 0; port < TOTAL_PORT_NUM; port++) {
		if (port == sw->port_cnt)
			continue;
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
	int port;

	/* All QoS functions disabled. */
	for (port = 0; port < TOTAL_PORT_NUM; port++) {
		if (port == sw->port_cnt)
			continue;
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
static void port_cfg_def_vid(struct ksz_sw *sw, int port, u16 vid)
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
static void port_get_def_vid(struct ksz_sw *sw, int port, u16 *vid)
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
static void sw_cfg_def_vid(struct ksz_sw *sw, int port, u16 vid)
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
static void sw_cfg_port_base_vlan(struct ksz_sw *sw, int port, u8 member)
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
static void sw_vlan_cfg_dis_non_vid(struct ksz_sw *sw, int port, int set)
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
static void sw_vlan_cfg_drop_tag(struct ksz_sw *sw, int port, int set)
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
static void sw_vlan_cfg_in_filter(struct ksz_sw *sw, int port, int set)
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
static void sw_vlan_cfg_ins_tag(struct ksz_sw *sw, int port, int set)
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
static void sw_vlan_cfg_rmv_tag(struct ksz_sw *sw, int port, int set)
{
	port_cfg_rmv_tag(sw, port, set);
}  /* sw_vlan_cfg_rmv_tag */

static inline int sw_chk_ins_tag(struct ksz_sw *sw)
{
	return sw_chk(sw, REG_SW_CTRL_19, SW_INS_TAG_ENABLE);
}

static inline void sw_cfg_ins_tag(struct ksz_sw *sw, int set)
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

static void sw_cfg_ins(struct ksz_sw *sw, int src_port, int dst_port, int set)
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
	int port;
	SW_D data;
	struct ksz_sw_info *info = sw->info;

	for (port = 0; port < TOTAL_PORT_NUM; port++) {
		if (port == sw->port_cnt)
			continue;
		port_get_def_vid(sw, port, &info->port_cfg[port].vid);
		port_r(sw, port, P_MIRROR_CTRL, &data);
		data &= PORT_VLAN_MEMBERSHIP;
		info->port_cfg[port].member = data;

		port_cfg(sw, port, P_INS_SRC_PVID_CTRL,
			(PORT_INS_TAG_FOR_PORT_5 | PORT_INS_TAG_FOR_PORT_4 |
			PORT_INS_TAG_FOR_PORT_3 | PORT_INS_TAG_FOR_PORT_2),
			true);
	}
}  /* sw_init_vlan */

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

/**
 * sw_set_global_ctrl - set switch global control
 * @sw:		The switch instance.
 *
 * This routine sets the global control of the switch function.
 */
static void sw_set_global_ctrl(struct ksz_sw *sw)
{
	SW_D data;
	struct phy_device *phydev = sw->phydev;
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
static void port_set_stp_state(struct ksz_sw *sw, int port, int state)
{
	SW_D data;
	struct ksz_port_cfg *port_cfg;
	int member = -1;

	port_cfg = &sw->info->port_cfg[port];
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
			member = sw->HOST_MASK | (1 << port);
		break;
	case STP_STATE_LEARNING:
		data &= ~PORT_TX_ENABLE;
		data |= PORT_RX_ENABLE;
		data &= ~PORT_LEARN_DISABLE;
		break;
	case STP_STATE_FORWARDING:
		data |= (PORT_TX_ENABLE | PORT_RX_ENABLE);
		data &= ~PORT_LEARN_DISABLE;
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
			member = sw->HOST_MASK | (1 << port);
		break;
	case STP_STATE_SIMPLE:
		data |= (PORT_TX_ENABLE | PORT_RX_ENABLE);
		data |= PORT_LEARN_DISABLE;
		if (port < SWITCH_PORT_NUM)
			/* Set port-base vlan membership with host port. */
			member = sw->HOST_MASK | (1 << port);
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

#define STP_ENTRY			0
#define BROADCAST_ENTRY			1
#define BRIDGE_ADDR_ENTRY		2
#define IPV6_ADDR_ENTRY			3

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
	for (i = 0; i < STATIC_MAC_TABLE_ENTRIES; i++)
		sw_w_sta_mac_table(sw, i, &entry);
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
	sw_w_sta_mac_table(sw, STP_ENTRY, &entry);
}  /* sw_setup_stp */

#ifdef CONFIG_KSZ_STP
/**
 * sw_block_addr - block certain packets from the host port
 * @sw:		The switch instance.
 *
 * This routine blocks certain packets from reaching to the host port.
 */
static void sw_block_addr(struct ksz_sw *sw)
{
	struct ksz_mac_table entry;
	int i;

	for (i = BROADCAST_ENTRY; i <= IPV6_ADDR_ENTRY; i++) {
		entry.override = 0;
		entry.valid = 0;
		sw_w_sta_mac_table(sw, i, &entry);
	}
}  /* sw_block_addr */

static void sw_block_multi(struct ksz_sw *sw)
{
	struct ksz_mac_table *entry;
	int i;

	for (i = STATIC_MAC_TABLE_ENTRIES; i < MULTI_MAC_TABLE_ENTRIES; i++) {
		entry = &sw->info->mac_table[i];
		if (entry->ports)
			entry->valid = 0;
	}
}  /* sw_block_multi */

static void sw_setup_multi(struct ksz_sw *sw)
{
	struct ksz_mac_table *entry;
	struct ksz_alu_table *alu;
	int i;
	u8 forward;
	struct ksz_sw_info *info = sw->info;

	i = MULTI_MAC_TABLE_ENTRIES;
	forward = FWD_STP_DEV;
	forward |= FWD_MAIN_DEV;

	/* Used for V2 IGMP messages. */
	entry = &info->mac_table[--i];
	entry->mac_addr[0] = 0x01;
	entry->mac_addr[1] = 0x00;
	entry->mac_addr[2] = 0x5E;
	entry->mac_addr[3] = 0x00;
	entry->mac_addr[4] = 0x00;
	entry->mac_addr[5] = 0x01;
	entry->ports = sw->HOST_MASK;
	alu = &info->alu_table[i];
	alu->forward = forward;
	alu->owner = sw->PORT_MASK;
	alu->valid = 1;
	entry = &info->mac_table[--i];
	entry->mac_addr[0] = 0x33;
	entry->mac_addr[1] = 0x33;
	entry->mac_addr[2] = 0x00;
	entry->mac_addr[3] = 0x00;
	entry->mac_addr[4] = 0x00;
	entry->mac_addr[5] = 0x01;
	entry->ports = sw->HOST_MASK;
	alu = &info->alu_table[i];
	alu->forward = forward;
	alu->owner = sw->PORT_MASK;
	alu->valid = 1;

	entry = &info->mac_table[--i];
	entry->mac_addr[0] = 0x01;
	entry->mac_addr[1] = 0x00;
	entry->mac_addr[2] = 0x5E;
	entry->mac_addr[3] = 0x00;
	entry->mac_addr[4] = 0x00;
	entry->mac_addr[5] = 0x02;
	entry->ports = sw->HOST_MASK;
	alu = &info->alu_table[i];
	alu->forward = forward;
	alu->owner = sw->PORT_MASK;
	alu->valid = 1;
	entry = &info->mac_table[--i];
	entry->mac_addr[0] = 0x33;
	entry->mac_addr[1] = 0x33;
	entry->mac_addr[2] = 0x00;
	entry->mac_addr[3] = 0x00;
	entry->mac_addr[4] = 0x00;
	entry->mac_addr[5] = 0x02;
	entry->ports = sw->HOST_MASK;
	alu = &info->alu_table[i];
	alu->forward = forward;
	alu->owner = sw->PORT_MASK;
	alu->valid = 1;

	/* Used for V3 IGMP messages. */
	entry = &info->mac_table[--i];
	entry->mac_addr[0] = 0x01;
	entry->mac_addr[1] = 0x00;
	entry->mac_addr[2] = 0x5E;
	entry->mac_addr[3] = 0x00;
	entry->mac_addr[4] = 0x00;
	entry->mac_addr[5] = 0x16;
	entry->ports = sw->HOST_MASK;
	alu = &info->alu_table[i];
	alu->forward = forward;
	alu->owner = sw->PORT_MASK;
	alu->valid = 1;
	entry = &info->mac_table[--i];
	entry->mac_addr[0] = 0x33;
	entry->mac_addr[1] = 0x33;
	entry->mac_addr[2] = 0x00;
	entry->mac_addr[3] = 0x00;
	entry->mac_addr[4] = 0x00;
	entry->mac_addr[5] = 0x16;
	entry->ports = sw->HOST_MASK;
	alu = &info->alu_table[i];
	alu->forward = forward;
	alu->owner = sw->PORT_MASK;
	alu->valid = 1;

	info->multi_sys = i;
}  /* sw_setup_multi */

static void bridge_change(struct ksz_sw *sw)
{
	int port;
	u8 member;
	struct ksz_sw_info *info = sw->info;

	for (port = 0; port < SWITCH_PORT_NUM; port++) {
		if (port == sw->port_cnt)
			continue;
		if (STP_STATE_FORWARDING == info->port_cfg[port].stp_state)
			member = sw->HOST_MASK | info->member;
		else if (STP_STATE_DISABLED == info->port_cfg[port].stp_state)
			member = 0;
		else
			member = sw->HOST_MASK | (1 << port);
		if (member != info->port_cfg[port].member)
			sw_cfg_port_base_vlan(sw, port, member);
	}
}  /* bridge_change */

/**
 * sw_pass_addr - allow certain packets to the host port
 * @sw:		The switch instance.
 *
 * This routine allows certain packets to reach the host port.
 */
static void sw_pass_addr(struct ksz_sw *sw)
{
	struct ksz_mac_table entry;
	int i;
	struct ksz_sw_info *info = sw->info;

	for (i = BROADCAST_ENTRY; i <= IPV6_ADDR_ENTRY; i++) {
		switch (i) {
		case BROADCAST_ENTRY:
			memset(entry.addr, 0xFF, ETH_ALEN);
			break;
		case BRIDGE_ADDR_ENTRY:
			memcpy(entry.addr, info->br_addr, ETH_ALEN);
			break;
		case IPV6_ADDR_ENTRY:
			memcpy(entry.addr, info->br_addr, ETH_ALEN);
			entry.addr[0] = 0x33;
			entry.addr[1] = 0x33;
			entry.addr[2] = 0xFF;
			break;
		}
		entry.ports = sw->HOST_MASK;
		entry.use_fid = 0;
		entry.override = 0;
		entry.valid = 1;
		sw_w_sta_mac_table(sw, i, &entry);
	}
}  /* sw_pass_addr */

static void sw_pass_multi(struct ksz_sw *sw)
{
	struct ksz_mac_table *entry;
	int i;

	for (i = STATIC_MAC_TABLE_ENTRIES; i < MULTI_MAC_TABLE_ENTRIES; i++) {
		entry = &sw->info->mac_table[i];
		if (entry->ports)
			entry->valid = 1;
	}
}  /* sw_pass_multi */

static void monitor_ports(struct ksz_sw *sw)
{
	int port;
	struct net_device *bridge_dev = NULL;
	struct ksz_sw_info *info = sw->info;
	u8 member = info->member;
	u8 stp = info->stp;
	u8 prev_stp = info->stp;
	u8 stp_down = 0;
	u8 state;
	u8 forwarding[SWITCH_PORT_NUM];

	memset(forwarding, 0, SWITCH_PORT_NUM);
	sw->ops->acquire(sw);
	for (port = 0; port < SWITCH_PORT_NUM; port++) {
		struct net_device *dev = sw->netdev[port + sw->dev_offset];

		if (port == sw->port_cnt)
			continue;
		state = sw->net_ops->get_port_state(dev, &bridge_dev);
		if (state != STP_STATE_SIMPLE) {
			stp |= (1 << port);
			if (STP_STATE_DISABLED == state)
				stp_down |= (1 << port);
		} else {
			stp &= ~(1 << port);
			state = sw->net_ops->get_state(dev);
		}
		if (stp != info->stp) {
			info->stp = stp;

			/* Device just removed from bridge. */
			if (!(stp & (1 << port))) {
				if (netif_running(dev))
					state = STP_STATE_SIMPLE;
			}
		}
		sw->net_ops->set_state(dev, state);

		if (info->port_cfg[port].stp_state != state) {
			if (STP_STATE_FORWARDING ==
					info->port_cfg[port].stp_state)
				member &= ~(1 << port);
			if (STP_STATE_FORWARDING == state)
				member |= (1 << port);

			/* Try to set forwarding after the other states. */
			if (STP_STATE_FORWARDING == state)
				forwarding[port] = true;
			else
				port_set_stp_state(sw, port, state);
			if (STP_STATE_LEARNING == state ||
			    STP_STATE_BLOCKED == state)
				sw_flush_dyn_mac_table(sw, port);
		}
	}
	for (port = 0; port < SWITCH_PORT_NUM; port++) {
		if (forwarding[port])
			port_set_stp_state(sw, port, STP_STATE_FORWARDING);
	}
	sw->ops->release(sw);
	if (prev_stp != info->stp && !info->stp)
		memset(info->br_addr, 0, ETH_ALEN);
	if (stp_down != info->stp_down || prev_stp != info->stp) {
		struct ksz_mac_table entry;

		sw_r_sta_mac_table(sw, 0, &entry);
		if (stp_down == info->stp) {

			/* Turn off STP only when it is already setup. */
			if (prev_stp == info->stp) {
				entry.override = 0;
				entry.valid = 0;
				sw_w_sta_mac_table(sw, 0, &entry);

				/* No ports in forwarding state. */
				sw->ops->acquire(sw);
				port_set_stp_state(sw, SWITCH_PORT_NUM,
					STP_STATE_SIMPLE);
				sw->ops->release(sw);
				sw_block_addr(sw);
				sw_block_multi(sw);
			}
		} else if (info->stp_down == info->stp ||
				(!prev_stp && info->stp)) {
			entry.override = 1;
			entry.valid = 1;
			sw_w_sta_mac_table(sw, 0, &entry);
		}

		/* Update disabled ports when STP is settled down. */
		if (prev_stp == info->stp)
			info->stp_down = stp_down;
	}

	if (member != info->member) {
		int cnt = 0;

		for (port = 0; port < SWITCH_PORT_NUM; port++)
			if (member & (1 << port))
				cnt++;
		info->fwd_ports = cnt;

		/* Have first member. */
		if (!info->member) {

			/* Force to program bridge address. */
			info->br_addr[0] = 0xFF;
		}
		info->member = member;
		sw->ops->acquire(sw);
		bridge_change(sw);
		sw->ops->release(sw);
	}

	/* At least one port in forwarding state. */
	if (info->member && bridge_dev && memcmp(bridge_dev->dev_addr,
			info->br_addr, ETH_ALEN)) {
		memcpy(info->br_addr, bridge_dev->dev_addr, ETH_ALEN);
		sw_pass_addr(sw);
		sw_pass_multi(sw);
	}
}  /* monitor_ports */
#endif

#ifdef KSZ_DLR
#include "ksz_dlr.c"
#endif

/*
 * Link detection routines
 */

static inline void dbp_link(struct ksz_port *port, struct ksz_sw *sw,
	int change)
{
	struct ksz_port_info *info;
	int i;
	int p;

	for (i = 0, p = port->first_port; i < port->port_cnt; i++, p++) {
		info = &sw->port_info[p];
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
#ifdef DEBUG
	printk(KERN_INFO "pause: %d, %d; %02x %02x\n",
		rx, tx, local, remote);
#endif
	return flow;
}  /* sw_determine_flow_ctrl */

static int port_chk_force_link(struct ksz_sw *sw, int p, SW_D remote,
	SW_D status)
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
	int i;
	int p;
	int change = 0;

	/*
	 * Only check port which has interrupts triggered.
	 * If no interrupt poll all the ports with PHY.
	 */
	if (!sw->phy_intr)
		sw->phy_intr = sw->PORT_MASK;
	for (i = 0, p = port->first_port; i < port->port_cnt; i++, p++) {
		if (!(sw->phy_intr & (1 << p)))
			continue;

		info = &sw->port_info[p];
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

		if (data & PORT_STAT_LINK_GOOD) {

			/* Remember the first linked port. */
			if (!linked)
				linked = info;
		}

		/* No change to status. */
		if (local == info->advertised && link == info->link)
			continue;

#ifdef DEBUG
		printk(KERN_INFO "advertised: %02X-%02X; partner: %02X-%02X\n",
			local, info->advertised, remote, info->partner);
#endif
		if (data & PORT_STAT_LINK_GOOD) {
			if (port_chk_force_link(sw, p, remote, status)) {
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

#ifdef DEBUG
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
			}
			info->state = media_connected;
		} else {
			if (media_disconnected != info->state) {
				change |= 1 << i;

				/* Indicate the link just goes down. */
				state->link_down = 1;
			}
			info->state = media_disconnected;
		}
		state->state = info->state;
		info->report = true;
		info->advertised = local;
		info->partner = remote;
		info->link = link;
	}
	sw->phy_intr = 0;

	if (linked && media_disconnected == port->linked->state)
		port->linked = linked;

#ifdef DEBUG
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
	SW_D adv;
	SW_D cfg;
	SW_D data;
	SW_D local;
	SW_D status;
	int i;
	int p;

	for (i = 0, p = port->first_port; i < port->port_cnt; i++, p++) {
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
	SW_D data;
	int i;
	int p;

	for (i = 0, p = port->first_port; i < port->port_cnt; i++, p++) {
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
	int port;

	for (port = 0; port < SWITCH_PORT_NUM; port++) {
		if (port == sw->port_cnt)
			continue;
		if (sw->dev_count > 1)
			port_set_stp_state(sw, port, STP_STATE_DISABLED);
		else
			port_set_stp_state(sw, port, STP_STATE_FORWARDING);
	}
	if (sw->dev_count > 1)
		port_set_stp_state(sw, SWITCH_PORT_NUM, STP_STATE_SIMPLE);
	else
		port_set_stp_state(sw, SWITCH_PORT_NUM, STP_STATE_FORWARDING);

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
	int port;

	sw_set_global_ctrl(sw);
	for (port = 0; port < SWITCH_PORT_NUM; port++) {
		SW_D data;

		if (port == sw->port_cnt)
			continue;
		port_cfg_back_pressure(sw, port, 1);
		port_cfg_force_flow_ctrl(sw, port, 0);

		/*
		 * Switch actually cannot do auto-negotiation with old 10Mbit
		 * hub.
		 */
		port_r(sw, port, P_FORCE_CTRL, &data);
		data &= ~PORT_FORCE_FULL_DUPLEX;
		port_w(sw, port, P_FORCE_CTRL, data);
	}

	sw_setup_broad_storm(sw);

	sw_setup_prio(sw);

	sw_setup_mirror(sw);

	sw->info->multi_net = SWITCH_MAC_TABLE_ENTRIES;
	if (sw->features & STP_SUPPORT) {
		sw_setup_stp(sw);
#ifdef CONFIG_KSZ_STP
		sw_setup_multi(sw);
#endif
	}
#ifdef KSZ_DLR
	if (sw->features & DLR_HW)
		sw_setup_dlr(sw);
#endif
	sw_enable(sw);
}  /* sw_setup */

static inline void sw_reset(struct ksz_sw *sw)
{
	int i;

	sw->reg->w8(sw, REG_POWER_MANAGEMENT_1,
		SW_SOFTWARE_POWER_DOWN << SW_POWER_MANAGEMENT_MODE_S);
	sw->reg->w8(sw, REG_POWER_MANAGEMENT_1, 0);

	for (i = 0; i < sw->mib_port_cnt; i++) {
		if (i == sw->port_cnt)
			continue;
		sw->info->port_cfg[i].acl_byte_enable = ACL_BYTE_ENABLE;
		sw_w_ext_table(sw, TABLE_ACL, i + 1,
			REG_PORT_ACL_BYTE_EN_MSB, ACL_BYTE_EN_MSB_M);
		sw_w_ext_table(sw, TABLE_ACL, i + 1,
			REG_PORT_ACL_BYTE_EN_LSB, 0xFF);
	}
	sw_reset_acl_hw(sw);
}  /* sw_reset */

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

static struct ksz_sw_reg_ops sw_reg_ops = {
	.lock			= sw_lock,
	.unlock			= sw_unlock,

	.r8			= sw_r8,
	.r16			= sw_r16,
	.r32			= sw_r32,
	.w8			= sw_w8,
	.w16			= sw_w16,
	.w32			= sw_w32,

	.r			= sw_r,
	.w			= sw_w,

	.get			= sw_reg_get,
	.set			= sw_reg_set,
};

/* -------------------------------------------------------------------------- */

/*
 * Micrel LinkMD routines
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
#define CABLE_LEN_MULTIPLIER		41

#define PHY_RESET_TIMEOUT		10

/**
 * hw_get_link_md -
 * @sw:		The switch instance.
 * @port:	The port index.
 *
 * This routine is used to get the LinkMD status.
 */
static void hw_get_link_md(struct ksz_sw *sw, int port)
{
	SW_D crossover;
	SW_D ctrl;
	SW_D data;
	SW_D link;
	u16 len;
	int i;
	int timeout;
	struct ksz_port_info *port_info = &sw->port_info[port];

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

	/* Put in 10 Mbps mode. */
	port_r(sw, port, P_FORCE_CTRL, &ctrl);
	data = ctrl;
	data &= ~(PORT_FORCE_100_MBIT |	PORT_FORCE_FULL_DUPLEX);
	data |= PORT_AUTO_NEG_DISABLE;
	port_w(sw, port, P_FORCE_CTRL, data);

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

		/* Disable transmitter. */
		data |= PORT_TX_DISABLE;
		port_w(sw, port, P_NEG_RESTART_CTRL, data);

		/* Wait at most 1 second.*/
		delay_milli(100);

		/* Enable transmitter. */
		data &= ~PORT_TX_DISABLE;
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
			port_info->length[i] = len *
				CABLE_LEN_MULTIPLIER;
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

	port_w(sw, port, P_FORCE_CTRL, ctrl);
	if (!(ctrl & PORT_AUTO_NEG_DISABLE)) {
		crossover |= PORT_AUTO_NEG_RESTART;
		port_w(sw, port, P_NEG_RESTART_CTRL, crossover);
	}

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
}  /* hw_get_link_md */

/* -------------------------------------------------------------------------- */

static void get_sw_mib_counters(struct ksz_sw *sw, int first, int cnt,
	u64 *counter)
{
	int i;
	int mib;
	int port;
	struct ksz_port_mib *port_mib;

	memset(counter, 0, sizeof(u64) * TOTAL_SWITCH_COUNTER_NUM);
	for (i = 0, port = first; i < cnt; i++, port++) {
		port_mib = &sw->port_mib[port];
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
		len = display_sw_info(sw->mib_port_cnt, buf, len);
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
		if (sw->port_cnt == sw->mib_port_cnt)
			len += sprintf(buf + len, "%u\n", sw->mib_port_cnt - 1);
		else
			len += sprintf(buf + len, "%u\n", sw->port_cnt);
		break;
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
		len += sprintf(buf + len, "%u\n",
			!!(sw->features & STP_SUPPORT));
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
		len += sprintf(buf + len, "\t%08x = different MAC addresses\n",
			DIFF_MAC_ADDR);
		break;
	case PROC_SET_SW_OVERRIDES:
		len += sprintf(buf + len, "%08x:\n", sw->overrides);
		len += sprintf(buf + len, "\t%08x = flow control\n",
			PAUSE_FLOW_CTRL);
		len += sprintf(buf + len, "\t%08x = fast aging\n",
			FAST_AGING);
		len += sprintf(buf + len, "\t%08x = tag is removed\n",
			TAG_REMOVE);
		len += sprintf(buf + len, "\t%08x = tail tagging\n",
			TAIL_TAGGING);
		break;
	}
	return len;
}  /* sysfs_sw_read */

static ssize_t sysfs_sw_read_hw(struct ksz_sw *sw, int proc_num, ssize_t len,
	char *buf)
{
	u8 data[8];

	switch (proc_num) {
	case PROC_SET_AGING:
		len += sprintf(buf + len, "%u\n",
			sw_chk(sw, REG_SW_CTRL_1,
				SW_AGING_ENABLE));
		break;
	case PROC_SET_FAST_AGING:
		len += sprintf(buf + len, "%u\n",
			sw_chk(sw, REG_SW_CTRL_1,
				SW_FAST_AGING));
		break;
	case PROC_SET_LINK_AGING:
		len += sprintf(buf + len, "%u\n",
			sw_chk(sw, S_LINK_AGING_CTRL,
				SW_LINK_AUTO_AGING));
		break;
	case PROC_SET_MULTICAST_STORM:
		len += sprintf(buf + len, "%u\n",
			!sw_chk(sw, REG_SW_CTRL_2,
				MULTICAST_STORM_DISABLE));
		break;
	case PROC_ENABLE_VLAN:
		len += sprintf(buf + len, "%u\n",
			sw_chk(sw, S_MIRROR_CTRL,
				SW_VLAN_ENABLE));
		break;
	case PROC_SET_REPLACE_NULL_VID:
		len += sprintf(buf + len, "%u\n",
			sw_chk(sw, S_REPLACE_VID_CTRL,
				SW_REPLACE_VID));
		break;
	case PROC_SET_MAC_ADDR:
		sw_get_addr(sw, data);
		len += sprintf(buf + len, "%02X:%02X:%02X:%02X:%02X:%02X\n",
			data[0], data[1], data[2], data[3], data[4], data[5]);
		break;
	case PROC_SET_MIRROR_MODE:
		len += sprintf(buf + len, "%u\n",
			sw_chk_mirror_rx_tx(sw));
		break;
	case PROC_SET_IGMP_SNOOP:
		len += sprintf(buf + len, "%u\n",
			sw_chk(sw, S_MIRROR_CTRL,
				SW_IGMP_SNOOP));
		break;
	case PROC_SET_IPV6_MLD_SNOOP:
		len += sprintf(buf + len, "%u\n",
			sw_chk(sw, S_IPV6_MLD_CTRL,
				SW_IPV6_MLD_SNOOP));
		break;
	case PROC_SET_IPV6_MLD_OPTION:
		len += sprintf(buf + len, "%u\n",
			sw_chk(sw, S_IPV6_MLD_CTRL,
				SW_IPV6_MLD_OPTION));
		break;
	case PROC_SET_TAIL_TAG:
		len += sprintf(buf + len, "%u\n",
			sw_chk(sw, S_TAIL_TAG_CTRL,
				SW_TAIL_TAG_ENABLE));
		break;
	case PROC_SET_AGGR_BACKOFF:
		len += sprintf(buf + len, "%u\n",
			sw_chk(sw, REG_SW_CTRL_1,
				SW_AGGR_BACKOFF));
		break;
	case PROC_SET_NO_EXC_DROP:
		len += sprintf(buf + len, "%u\n",
			sw_chk(sw, REG_SW_CTRL_2,
				NO_EXC_COLLISION_DROP));
		break;
	case PROC_SET_VLAN_BOUNDARY:
		len += sprintf(buf + len, "%u\n",
			sw_chk(sw, REG_SW_CTRL_2,
				UNICAST_VLAN_BOUNDARY));
		break;
	case PROC_SET_HUGE_PACKET:
		len += sprintf(buf + len, "%u\n",
			sw_chk(sw, S_HUGE_PACKET_CTRL,
				SW_HUGE_PACKET));
		break;
	case PROC_SET_LEGAL_PACKET:
		len += sprintf(buf + len, "%u\n",
			!sw_chk(sw, REG_SW_CTRL_2,
				SW_LEGAL_PACKET_DISABLE));
		break;
	case PROC_SET_LENGTH_CHECK:
		len += sprintf(buf + len, "%u\n",
			sw_chk(sw, REG_SW_CTRL_1,
				SW_CHECK_LENGTH));
		break;
	case PROC_SET_BACK_PRESSURE_MODE:
		len += sprintf(buf + len, "%u\n",
			sw_chk(sw, REG_SW_CTRL_2,
				SW_BACK_PRESSURE));
		break;
	case PROC_SET_SWITCH_FLOW_CTRL:
		len += sprintf(buf + len, "%u\n",
			sw_chk(sw, S_REPLACE_VID_CTRL,
				SW_FLOW_CTRL));
		break;
	case PROC_SET_SWITCH_HALF_DUPLEX:
		len += sprintf(buf + len, "%u\n",
			sw_chk(sw, S_REPLACE_VID_CTRL,
				SW_HALF_DUPLEX));
		break;
#ifdef SW_10_MBIT
	case PROC_SET_SWITCH_10_MBIT:
		len += sprintf(buf + len, "%u\n",
			sw_chk(sw, S_REPLACE_VID_CTRL,
				SW_10_MBIT));
		break;
#endif
	case PROC_SET_RX_FLOW_CTRL:
		len += sprintf(buf + len, "%u\n",
			!sw_chk(sw, REG_SW_CTRL_1,
				SW_RX_FLOW_CTRL_DISABLE));
		break;
	case PROC_SET_TX_FLOW_CTRL:
		len += sprintf(buf + len, "%u\n",
			!sw_chk(sw, REG_SW_CTRL_1,
				SW_TX_FLOW_CTRL_DISABLE));
		break;
	case PROC_SET_FAIR_FLOW_CTRL:
		len += sprintf(buf + len, "%u\n",
			sw_chk(sw, REG_SW_CTRL_2,
				FAIR_FLOW_CTRL));
		break;
	case PROC_SET_FORWARD_UNKNOWN_UNICAST:
		len += sprintf(buf + len, "%u\n",
			sw_chk_unk_dest(sw, REG_SW_UNK_UCAST_CTRL));
		break;
	case PROC_SET_FORWARD_UNKNOWN_UNICAST_PORTS:
		len += sprintf(buf + len, "0x%x\n",
			sw_chk_unk_def_port(sw, REG_SW_UNK_UCAST_CTRL,
				sw->mib_port_cnt));
		break;
	case PROC_SET_FORWARD_UNKNOWN_MULTICAST:
		len += sprintf(buf + len, "%u\n",
			sw_chk_unk_dest(sw, REG_SW_UNK_MCAST_CTRL));
		break;
	case PROC_SET_FORWARD_UNKNOWN_MULTICAST_PORTS:
		len += sprintf(buf + len, "0x%x\n",
			sw_chk_unk_def_port(sw, REG_SW_UNK_MCAST_CTRL,
				sw->mib_port_cnt));
		break;
	case PROC_SET_FORWARD_UNKNOWN_VID:
		len += sprintf(buf + len, "%u\n",
			sw_chk_unk_dest(sw, REG_SW_UNK_VID_CTRL));
		break;
	case PROC_SET_FORWARD_UNKNOWN_VID_PORTS:
		len += sprintf(buf + len, "0x%x\n",
			sw_chk_unk_def_port(sw, REG_SW_UNK_VID_CTRL,
				sw->mib_port_cnt));
		break;
	case PROC_SET_FORWARD_UNKNOWN_IP_MULTICAST:
		len += sprintf(buf + len, "%u\n",
			sw_chk_unk_dest(sw, REG_SW_UNK_IP_MCAST_CTRL));
		break;
	case PROC_SET_FORWARD_UNKNOWN_IP_MULTICAST_PORTS:
		len += sprintf(buf + len, "0x%x\n",
			sw_chk_unk_def_port(sw, REG_SW_UNK_IP_MCAST_CTRL,
				sw->mib_port_cnt));
		break;
	case PROC_SET_SELF_ADDR_FILTER:
		len += sprintf(buf + len, "%d\n",
			sw_chk_self_filter(sw));
		break;
	case PROC_SET_INS_TAG:
		len += sprintf(buf + len, "%d\n",
			sw_chk_ins_tag(sw));
		break;
	case PROC_SET_PME:
		data[0] = sw_get_pme(sw);
		len += sprintf(buf + len, "%02x:\n", data[0]);
		len += sprintf(buf + len, "\t%02x = PME enable\n",
			SW_PME_OUTPUT_ENABLE);
		len += sprintf(buf + len, "\t%02x = PME active high\n",
			SW_PME_ACTIVE_HIGH);
		break;
	case PROC_SET_PASS_PAUSE:
		len += sprintf(buf + len, "%u\n",
			sw_chk(sw, S_PASS_PAUSE_CTRL,
				SW_PASS_PAUSE));
		break;
	case PROC_SET_HI_PRIO_QUEUES:
		len += sprintf(buf + len, "%u\n",
			sw_get_hi_prio_queues(sw));
		break;
	case PROC_DYNAMIC:
		sw_d_dyn_mac_table(sw);
		break;
	case PROC_STATIC:
		sw_d_sta_mac_table(sw);
		sw_d_mac_table(sw);
		break;
	case PROC_VLAN:
		sw_d_vlan_table(sw);
		break;
	}
	return len;
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
		if (port->force_link)
			port_force_link_speed(port);
		else
			port_set_link_speed(port);
		break;
	case PROC_SET_SW_FLOW_CTRL:
		if (!port)
			break;
		if (num <= PHY_FLOW_CTRL)
			port->flow_ctrl = (u8) num;
		break;
	case PROC_SET_SW_MIB:
		sw_cfg_mib_counter_ctrl(sw, num, sw->mib_port_cnt);
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
			int i;
			int enabled;

			if (num & VLAN_PORT_REMOVE_TAG) {
				enabled = true;
				sw->overrides |= TAG_REMOVE;
			} else {
				enabled = false;
				sw->overrides &= ~TAG_REMOVE;
			}
			for (i = 0; i < SWITCH_PORT_NUM; i++) {
				if (i == sw->port_cnt)
					continue;
				port_cfg_rmv_tag(sw, i, enabled);
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
		sw_cfg_unk_def_port(sw, REG_SW_UNK_UCAST_CTRL, num, 2);
		break;
	case PROC_SET_FORWARD_UNKNOWN_MULTICAST:
		sw_cfg_unk_dest(sw, REG_SW_UNK_MCAST_CTRL, num);
		break;
	case PROC_SET_FORWARD_UNKNOWN_MULTICAST_PORTS:
		sw_cfg_unk_def_port(sw, REG_SW_UNK_MCAST_CTRL, num, 2);
		break;
	case PROC_SET_FORWARD_UNKNOWN_VID:
		sw_cfg_unk_dest(sw, REG_SW_UNK_VID_CTRL, num);
		break;
	case PROC_SET_FORWARD_UNKNOWN_VID_PORTS:
		sw_cfg_unk_def_port(sw, REG_SW_UNK_VID_CTRL, num, 2);
		break;
	case PROC_SET_FORWARD_UNKNOWN_IP_MULTICAST:
		sw_cfg_unk_dest(sw, REG_SW_UNK_IP_MCAST_CTRL, num);
		break;
	case PROC_SET_FORWARD_UNKNOWN_IP_MULTICAST_PORTS:
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

static ssize_t sysfs_port_read(struct ksz_sw *sw, int proc_num, int port,
	ssize_t len, char *buf)
{
	struct ksz_port_cfg *port_cfg;
	struct ksz_port_info *port_info;

	port_cfg = &sw->info->port_cfg[port];
	port_info = &sw->port_info[port];
	switch (proc_num) {
	case PROC_GET_PORT_DUPLEX:
		if (media_connected == port_info->state) {
			if (1 == port_info->duplex)
				len += sprintf(buf + len, "half-duplex\n");
			else if (2 == port_info->duplex)
				len += sprintf(buf + len, "full-duplex\n");
		} else
			len += sprintf(buf + len, "unlinked\n");
		break;
	case PROC_GET_PORT_SPEED:
		if (media_connected == port_info->state)
			len += sprintf(buf + len, "%u\n",
				port_info->tx_rate / TX_RATE_UNIT);
		else
			len += sprintf(buf + len, "unlinked\n");
		break;
	case PROC_SET_PORT_MIB:
		len += display_sw_mib_counters(sw, port, 1, buf + len);
		break;
	case PROC_SET_LINK_MD:
		len += sprintf(buf + len, "%u:%u %u:%u %u:%u\n",
			port_info->length[0], port_info->status[0],
			port_info->length[1], port_info->status[1],
			port_info->length[2], port_info->status[2]);
		break;
	case PROC_SET_PORT_BASED:
		len += sprintf(buf + len, "%u\n",
			port_cfg->port_prio);
		break;
	case PROC_SET_DEF_VID:
		len += sprintf(buf + len, "0x%04x\n",
			port_cfg->vid);
		break;
	case PROC_SET_MEMBER:
		len += sprintf(buf + len, "0x%02x\n",
			port_cfg->member);
		break;
	case PROC_SET_TX_Q0_CTRL:
		len += sprintf(buf + len, "%u\n", (int)
			(port_cfg->rate_ctrl[0] & RATE_CTRL_ENABLE) != 0);
		break;
	case PROC_SET_TX_Q1_CTRL:
		len += sprintf(buf + len, "%u\n", (int)
			(port_cfg->rate_ctrl[1] & RATE_CTRL_ENABLE) != 0);
		break;
	case PROC_SET_TX_Q2_CTRL:
		len += sprintf(buf + len, "%u\n", (int)
			(port_cfg->rate_ctrl[2] & RATE_CTRL_ENABLE) != 0);
		break;
	case PROC_SET_TX_Q3_CTRL:
		len += sprintf(buf + len, "%u\n", (int)
			(port_cfg->rate_ctrl[3] & RATE_CTRL_ENABLE) != 0);
		break;
	case PROC_SET_TX_Q0_RATIO:
		len += sprintf(buf + len, "%u\n", (int)
			port_cfg->rate_ctrl[0] & RATE_RATIO_M);
		break;
	case PROC_SET_TX_Q1_RATIO:
		len += sprintf(buf + len, "%u\n", (int)
			port_cfg->rate_ctrl[1] & RATE_RATIO_M);
		break;
	case PROC_SET_TX_Q2_RATIO:
		len += sprintf(buf + len, "%u\n", (int)
			port_cfg->rate_ctrl[2] & RATE_RATIO_M);
		break;
	case PROC_SET_TX_Q3_RATIO:
		len += sprintf(buf + len, "%u\n", (int)
			port_cfg->rate_ctrl[3] & RATE_RATIO_M);
		break;
	case PROC_SET_RX_LIMIT:
		len += sprintf(buf + len, "%u\n",
			((port_cfg->rate_limit >> PORT_IN_LIMIT_MODE_S) &
			PORT_IN_LIMIT_MODE_M));
		break;
	case PROC_SET_RX_LIMIT_PORT_BASED:
		len += sprintf(buf + len, "%u\n",
			((port_cfg->rate_limit >> PORT_IN_PORT_BASED_S)
			& 1));
		break;
	case PROC_SET_LIMIT_PACKET_BASED:
		len += sprintf(buf + len, "%u\n",
			((port_cfg->rate_limit >> PORT_RATE_PACKET_BASED_S)
			& 1));
		break;
	case PROC_SET_RX_LIMIT_FLOW_CTRL:
		len += sprintf(buf + len, "%u\n",
			((port_cfg->rate_limit >> PORT_IN_FLOW_CTRL_S)
			& 1));
		break;
	case PROC_SET_CNT_IFG:
		len += sprintf(buf + len, "%u\n",
			((port_cfg->rate_limit >> PORT_COUNT_IFG_S)
			& 1));
		break;
	case PROC_SET_CNT_PRE:
		len += sprintf(buf + len, "%u\n",
			((port_cfg->rate_limit >> PORT_COUNT_PREAMBLE_S)
			& 1));
		break;
	case PROC_SET_RX_P0_RATE:
		len += sprintf(buf + len, "%u %s\n", (int)
			port_cfg->packet_based ?
			port_cfg->rx_packet[0] : port_cfg->rx_rate[0],
			port_cfg->packet_based ? "pbs" : "bbs");
		break;
	case PROC_SET_RX_P1_RATE:
		len += sprintf(buf + len, "%u %s\n", (int)
			port_cfg->packet_based ?
			port_cfg->rx_packet[1] : port_cfg->rx_rate[1],
			port_cfg->packet_based ? "pbs" : "bbs");
		break;
	case PROC_SET_RX_P2_RATE:
		len += sprintf(buf + len, "%u %s\n", (int)
			port_cfg->packet_based ?
			port_cfg->rx_packet[2] : port_cfg->rx_rate[2],
			port_cfg->packet_based ? "pbs" : "bbs");
		break;
	case PROC_SET_RX_P3_RATE:
		len += sprintf(buf + len, "%u %s\n", (int)
			port_cfg->packet_based ?
			port_cfg->rx_packet[3] : port_cfg->rx_rate[3],
			port_cfg->packet_based ? "pbs" : "bbs");
		break;
	case PROC_SET_TX_Q0_RATE:
		len += sprintf(buf + len, "%u %s\n", (int)
			port_cfg->packet_based ?
			port_cfg->tx_packet[0] : port_cfg->tx_rate[0],
			port_cfg->packet_based ? "pbs" : "bbs");
		break;
	case PROC_SET_TX_Q1_RATE:
		len += sprintf(buf + len, "%u %s\n", (int)
			port_cfg->packet_based ?
			port_cfg->tx_packet[1] : port_cfg->tx_rate[1],
			port_cfg->packet_based ? "pbs" : "bbs");
		break;
	case PROC_SET_TX_Q2_RATE:
		len += sprintf(buf + len, "%u %s\n", (int)
			port_cfg->packet_based ?
			port_cfg->tx_packet[2] : port_cfg->tx_rate[2],
			port_cfg->packet_based ? "pbs" : "bbs");
		break;
	case PROC_SET_TX_Q3_RATE:
		len += sprintf(buf + len, "%u %s\n", (int)
			port_cfg->packet_based ?
			port_cfg->tx_packet[3] : port_cfg->tx_rate[3],
			port_cfg->packet_based ? "pbs" : "bbs");
		break;
	}
	return len;
}  /* sysfs_port_read */

static ssize_t sysfs_port_read_hw(struct ksz_sw *sw, int proc_num, int port,
	ssize_t len, char *buf)
{
	u8 data[8];

	switch (proc_num) {
	case PROC_ENABLE_BROADCAST_STORM:
		len += sprintf(buf + len, "%d\n",
			port_chk_broad_storm(sw, port));
		break;
	case PROC_ENABLE_DIFFSERV:
		len += sprintf(buf + len, "%d\n",
			port_chk_diffserv(sw, port));
		break;
	case PROC_ENABLE_802_1P:
		len += sprintf(buf + len, "%d\n",
			port_chk_802_1p(sw, port));
		break;
	case PROC_ENABLE_PRIO_QUEUE:
		len += sprintf(buf + len, "%d\n",
			port_get_prio_queue(sw, port));
		break;
	case PROC_SET_MIRROR_PORT:
		len += sprintf(buf + len, "%u\n",
			port_chk_mirror_sniffer(sw, port));
		break;
	case PROC_SET_MIRROR_RX:
		len += sprintf(buf + len, "%u\n",
			port_chk_mirror_rx(sw, port));
		break;
	case PROC_SET_MIRROR_TX:
		len += sprintf(buf + len, "%u\n",
			port_chk_mirror_tx(sw, port));
		break;
	case PROC_SET_RX:
		len += sprintf(buf + len, "%u\n",
			port_chk_rx(sw, port));
		break;
	case PROC_SET_TX:
		len += sprintf(buf + len, "%u\n",
			port_chk_tx(sw, port));
		break;
	case PROC_SET_LEARN:
		len += sprintf(buf + len, "%u\n",
			!port_chk_dis_learn(sw, port));
		break;
	case PROC_SET_INSERT_TAG:
		len += sprintf(buf + len, "%u\n",
			port_chk_ins_tag(sw, port));
		break;
	case PROC_SET_REMOVE_TAG:
		len += sprintf(buf + len, "%u\n",
			port_chk_rmv_tag(sw, port));
		break;
	case PROC_SET_DROP_TAG:
		len += sprintf(buf + len, "%u\n",
			port_chk_drop_tag(sw, port));
		break;
	case PROC_SET_REPLACE_PRIO:
		len += sprintf(buf + len, "%u\n",
			port_chk_replace_prio(sw, port));
		break;
	case PROC_ENABLE_RX_PRIO_RATE:
		len += sprintf(buf + len, "%d\n",
			sw_chk_rx_prio_rate(sw, port));
		break;
	case PROC_ENABLE_TX_PRIO_RATE:
		len += sprintf(buf + len, "%d\n",
			sw_chk_tx_prio_rate(sw, port));
		break;
	case PROC_SET_DIS_NON_VID:
		len += sprintf(buf + len, "%u\n",
			port_chk_dis_non_vid(sw, port));
		break;
	case PROC_SET_INGRESS:
		len += sprintf(buf + len, "%u\n",
			port_chk_in_filter(sw, port));
		break;
	case PROC_SET_BACK_PRESSURE:
		len += sprintf(buf + len, "%u\n",
			port_chk_back_pressure(sw, port));
		break;
	case PROC_SET_FORCE_FLOW_CTRL:
		len += sprintf(buf + len, "%u\n",
			port_chk_force_flow_ctrl(sw, port));
		break;
	case PROC_SET_INS_TAG_0:
		len += sprintf(buf + len, "%u\n",
			sw_chk_ins(sw, port, 0));
		break;
	case PROC_SET_INS_TAG_1:
		len += sprintf(buf + len, "%u\n",
			sw_chk_ins(sw, port, 1));
		break;
	case PROC_SET_INS_TAG_2:
		len += sprintf(buf + len, "%u\n",
			sw_chk_ins(sw, port, 2));
		break;
	case PROC_SET_INS_TAG_3:
		len += sprintf(buf + len, "%u\n",
			sw_chk_ins(sw, port, 3));
		break;
	case PROC_SET_INS_TAG_4:
		len += sprintf(buf + len, "%u\n",
			sw_chk_ins(sw, port, 4));
		break;
	case PROC_SET_PASS_ALL:
		len += sprintf(buf + len, "%u\n",
			port_chk(sw, port, P_PASS_ALL_CTRL,
				PORT_PASS_ALL));
		break;
	case PROC_SET_UNKNOWN_UNICAST_PORT:
		len += sprintf(buf + len, "%u\n",
			sw_chk_unk_def_port(sw, REG_SW_UNK_UCAST_CTRL, port));
		break;
	case PROC_SET_UNKNOWN_MULTICAST_PORT:
		len += sprintf(buf + len, "%u\n",
			sw_chk_unk_def_port(sw, REG_SW_UNK_MCAST_CTRL, port));
		break;
	case PROC_SET_UNKNOWN_VID_PORT:
		len += sprintf(buf + len, "%u\n",
			sw_chk_unk_def_port(sw, REG_SW_UNK_VID_CTRL, port));
		break;
	case PROC_SET_UNKNOWN_IP_MULTICAST_PORT:
		len += sprintf(buf + len, "%u\n",
			sw_chk_unk_def_port(sw, REG_SW_UNK_IP_MCAST_CTRL,
				port));
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
		break;
	case PROC_SET_AUTHEN_MODE:
		len += sprintf(buf + len, "%u\n",
			port_get_authen_mode(sw, port));
		break;
	case PROC_SET_ACL:
		len += sprintf(buf + len, "%u\n",
			port_chk_acl(sw, port));
		break;
	}
	return len;
}  /* sysfs_port_read_hw */

static int sysfs_port_write(struct ksz_sw *sw, int proc_num, int port,
	int num, const char *buf)
{
	int processed = true;

	switch (proc_num) {
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
		sw_cfg_port_base_vlan(sw, port, (u8) num);
		break;
	case PROC_ENABLE_PRIO_QUEUE:
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
		break;
	case PROC_SET_RX_P1_RATE:
		hw_cfg_rx_prio_rate(sw, port, 1, num);
		break;
	case PROC_SET_RX_P2_RATE:
		hw_cfg_rx_prio_rate(sw, port, 2, num);
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
		hw_get_link_md(sw, port);
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
		len += sprintf(buf + len, "0x%02x\n", entry->ports);
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
		len += sprintf(buf + len,
			"%2x: %02X:%02X:%02X:%02X:%02X:%02X "
			"%02x o:%u %u:%02x [%u]\n",
			sw->mac_index,
			entry->addr[0], entry->addr[1], entry->addr[2],
			entry->addr[3], entry->addr[4], entry->addr[5],
			entry->ports, entry->override,
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
			entry->ports = num;
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
			if (!entry->dirty)
				sw_r_vlan_table(sw, sw->vlan_index, entry);
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
	int processed = true;

	entry = &sw->info->vlan_entry;
	switch (proc_num) {
	case PROC_SET_VLAN_VALID:
		if (num)
			entry->valid = 1;
		else
			entry->valid = 0;
		sw_w_vlan_table(sw, sw->vlan_index, entry);
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

static ssize_t sysfs_acl_read(struct ksz_sw *sw, int proc_num, int port,
	ssize_t len, char *buf)
{
	struct ksz_port_cfg *cfg = &sw->info->port_cfg[port];
	struct ksz_acl_table *acl;
	struct ksz_acl_table *action;

	acl = &cfg->acl_info[cfg->acl_index];
	action = &cfg->acl_info[cfg->acl_act_index];
	switch (proc_num) {
	case PROC_SET_ACL_FIRST_RULE:
		len += sprintf(buf + len, "0x%x\n", acl->first_rule);
		break;
	case PROC_SET_ACL_RULESET:
		len += sprintf(buf + len, "0x%04x\n", acl->ruleset);
		break;
	case PROC_SET_ACL_MODE:
		len += sprintf(buf + len, "%u\n", acl->mode);
		break;
	case PROC_SET_ACL_ENABLE:
		len += sprintf(buf + len, "%u\n", acl->enable);
		break;
	case PROC_SET_ACL_SRC:
		len += sprintf(buf + len, "%u\n", acl->src);
		break;
	case PROC_SET_ACL_EQUAL:
		len += sprintf(buf + len, "%u\n", acl->equal);
		break;
	case PROC_SET_ACL_PRIO_MODE:
		len += sprintf(buf + len, "%u\n", action->prio_mode);
		break;
	case PROC_SET_ACL_PRIO:
		len += sprintf(buf + len, "%u\n", action->prio);
		break;
	case PROC_SET_ACL_VLAN_PRIO_REPLACE:
		len += sprintf(buf + len, "%u\n", action->vlan_prio_replace);
		break;
	case PROC_SET_ACL_VLAN_PRIO:
		len += sprintf(buf + len, "%u\n", action->vlan_prio);
		break;
	case PROC_SET_ACL_MAP_MODE:
		len += sprintf(buf + len, "%u\n", action->map_mode);
		break;
	case PROC_SET_ACL_PORTS:
		len += sprintf(buf + len, "0x%04x\n", action->ports);
		break;
	case PROC_SET_ACL_MAC_ADDR:
		len += sprintf(buf + len, "%02x:%02x:%02x:%02x:%02x:%02x\n",
			acl->mac[0], acl->mac[1], acl->mac[2],
			acl->mac[3], acl->mac[4], acl->mac[5]);
		break;
	case PROC_SET_ACL_TYPE:
		len += sprintf(buf + len, "0x%04x\n", acl->eth_type);
		break;
	case PROC_SET_ACL_CNT:
		len += sprintf(buf + len, "%u\n", acl->cnt);
		break;
	case PROC_SET_ACL_MSEC:
		len += sprintf(buf + len, "%u\n", acl->msec);
		break;
	case PROC_SET_ACL_INTR_MODE:
		len += sprintf(buf + len, "%u\n", acl->intr_mode);
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
		len += sprintf(buf + len, "%u\n", acl->protocol);
		break;
	case PROC_SET_ACL_PORT_MODE:
		len += sprintf(buf + len, "%u\n", acl->port_mode);
		break;
	case PROC_SET_ACL_MAX_PORT:
		len += sprintf(buf + len, "%u\n", acl->max_port);
		break;
	case PROC_SET_ACL_MIN_PORT:
		len += sprintf(buf + len, "%u\n", acl->min_port);
		break;
	case PROC_SET_ACL_SEQNUM:
		len += sprintf(buf + len, "%u\n", acl->seqnum);
		break;
	case PROC_SET_ACL_TCP_FLAG_ENABLE:
		len += sprintf(buf + len, "%u\n", acl->tcp_flag_enable);
		break;
	case PROC_SET_ACL_TCP_FLAG:
		len += sprintf(buf + len, "0x%x\n", acl->tcp_flag);
		break;
	case PROC_SET_ACL_TCP_FLAG_MASK:
		len += sprintf(buf + len, "0x%x\n", acl->tcp_flag_mask);
		break;
	case PROC_SET_ACL_INDEX:
		len += sprintf(buf + len, "0x%x\n", cfg->acl_index);
		break;
	case PROC_SET_ACL_ACTION_INDEX:
		len += sprintf(buf + len, "0x%x\n", cfg->acl_act_index);
		break;
	case PROC_SET_ACL_ACTION:
		len += acl_action_info(action, cfg->acl_act_index, buf, len);
		break;
	case PROC_SET_ACL_INFO:
		len += acl_info(acl, cfg->acl_index, buf, len);
		break;
	case PROC_GET_ACL_TABLE:
		sw_d_acl_table(sw, port);
		break;
	}
	return len;
}  /* sysfs_acl_read */

static int sysfs_acl_write(struct ksz_sw *sw, int proc_num, int port, int num,
	const char *buf)
{
	struct ksz_port_cfg *cfg = &sw->info->port_cfg[port];
	struct ksz_acl_table *acl;
	struct ksz_acl_table *action;
	int processed = true;

	acl = &cfg->acl_info[cfg->acl_index];
	action = &cfg->acl_info[cfg->acl_act_index];
	switch (proc_num) {
	case PROC_SET_ACL_FIRST_RULE:
		acl->first_rule = (u16) num;
		acl->changed = 1;
		break;
	case PROC_SET_ACL_RULESET:
		sscanf(buf, "%x", &num);
		acl->ruleset = (u16) num;
		acl->changed = 1;
		break;
	case PROC_SET_ACL_MODE:
		if (0 <= num && num < 4) {
			acl->mode = num;
			sw_w_acl_table(sw, port, cfg->acl_index, acl);
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
	case PROC_SET_ACL_INFO:
		sw_r_acl_table(sw, port, cfg->acl_index, acl);
		break;
	default:
		processed = false;
		break;
	}
	return processed;
}  /* sysfs_acl_write */

/* -------------------------------------------------------------------------- */

#ifdef KSZSW_REGS_SIZE
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
	vlan.member = (u8) ports;
	vlan.valid = vlan.member != 0;
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

static int sw_get_id(struct ksz_sw *sw, u8 *id1, u8 *id2)
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
	return id;
}

static void sw_cfg_tail_tag(struct ksz_sw *sw, int enable)
{
	/* Switch marks the maximum frame with extra byte as oversize. */
	sw_cfg(sw, REG_SW_CTRL_2, SW_LEGAL_PACKET_DISABLE, enable);
	sw_cfg(sw, S_TAIL_TAG_CTRL, SW_TAIL_TAG_ENABLE, enable);
}

static int sw_port_to_phy_addr(struct ksz_sw *sw, int p)
{
	if (0 <= p && p <= sw->mib_port_cnt)
		return p;
	return -1;
}

static void sw_cfg_each_port(struct ksz_sw *sw, int p, int cpu)
{
	if (!cpu)
		sw_cfg_port_base_vlan(sw, p, sw->HOST_MASK | (1 << p));
	else
		sw_cfg_port_base_vlan(sw, p, sw->PORT_MASK);
}

static void sw_set_port_addr(struct ksz_sw *sw, int p, u8 *addr)
{
}

#ifdef CONFIG_KSZ_STP
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
		port = priv->first_port + 1;
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
			    !memcmp(entry->mac_addr, ha->addr, ETH_ALEN)) {
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
			memcpy(entry->mac_addr, ha->addr, ETH_ALEN);
			entry->ports = sw->PORT_MASK;
			entry->valid = 1;
		}
	}
}  /* sw_set_multi */

static void sw_add_frame(struct ksz_sw *sw, u32 crc, unsigned long now,
	unsigned long expired, int num, int port, int max,
	struct ksz_frame_table *table, int *cnt)
{
	struct ksz_frame_table *entry;
	int i;

	/* Table full. */
	if (max == *cnt) {
		for (i = 0; i < max; i++) {
			entry = &table[i];
			if (entry->expired &&
					time_after(now, entry->expired)) {
				entry->expired = 0;
				--(*cnt);
			}
		}
	}
	for (i = 0; i < max; i++) {
		entry = &table[i];
		if (!entry->expired) {
			entry->crc = crc;
			entry->cnt = num;
			entry->port = port;
			if (0 == expired)
				expired = 1;
			entry->expired = expired;
			++(*cnt);
			break;
		}
	}
}  /* sw_add_frame */

static int sw_del_frame(struct ksz_sw *sw, u32 crc, unsigned long now,
	int port, int max, struct ksz_frame_table *table, int *cnt)
{
	struct ksz_frame_table *entry;
	int i;
	int num = 0;

	for (i = 0; i < max; i++) {
		entry = &table[i];
		if (!entry->expired)
			continue;
		if (crc == entry->crc && port != entry->port) {
			if (time_after(now, entry->expired)) {
				entry->expired = 0;
				--(*cnt);
				break;
			}
			--entry->cnt;

			/* No need to retain the entry. */
			if (!entry->cnt) {
				entry->expired = 0;
				--(*cnt);
			}
			return i + 1;
		}
		++num;
		if (num == *cnt)
			break;
	}
	return 0;
}  /* sw_del_frame */

static void sw_add_rx(struct ksz_sw *sw, u32 crc, unsigned long now,
	unsigned long expired, int num, int port)
{
	struct ksz_rx_table *info = &sw->info->rx_table;

	sw_add_frame(sw, crc, now, expired, num, port,
		RX_TABLE_ENTRIES, info->table, &info->cnt);
}  /* sw_add_rx */

static int sw_del_rx(struct ksz_sw *sw, u32 crc, unsigned long now, int port)
{
	struct ksz_rx_table *info = &sw->info->rx_table;

	return sw_del_frame(sw, crc, now, port, RX_TABLE_ENTRIES, info->table,
		&info->cnt);
}  /* sw_del_rx */

static void sw_add_tx(struct ksz_sw *sw, u32 crc, unsigned long now,
	unsigned long expired, int num, int port)
{
	struct ksz_tx_table *info = &sw->info->tx_table;

	sw_add_frame(sw, crc, now, expired, num, port,
		TX_TABLE_ENTRIES, info->table, &info->cnt);
}  /* sw_add_tx */

static int sw_del_tx(struct ksz_sw *sw, u32 crc, unsigned long now, int port)
{
	struct ksz_tx_table *info = &sw->info->tx_table;

	return sw_del_frame(sw, crc, now, port, TX_TABLE_ENTRIES, info->table,
		&info->cnt);
}  /* sw_del_tx */

static int sw_blocked_rx(struct ksz_sw *sw, u8 *data)
{
	int i;

	for (i = 0; i < sw->info->blocked_rx_cnt; i++)
		if (!memcmp(data, sw->info->blocked_rx[i], ETH_ALEN))
			return true;
	if (BLOCKED_RX_ENTRIES == i)
		sw->info->blocked_rx_cnt = 0;
	memcpy(sw->info->blocked_rx[sw->info->blocked_rx_cnt++], data,
		ETH_ALEN);
	return false;
}  /* sw_blocked_rx */

static int sw_block_rx(struct ksz_sw *sw, u8 *data, int len, int port)
{
	struct ksz_mac_table *entry;
	struct ksz_alu_table *alu;
	u32 crc;
	int i;
	int forward = 0;

	for (i = 0; i < MULTI_MAC_TABLE_ENTRIES; i++) {

		/*
		 * Special case of checking the frame is forwarded to the host.
		 * All entries before STATIC_MAC_TABLE_ENTRIES should have
		 * FWD_HOST.
		 */
		if (!len && STATIC_MAC_TABLE_ENTRIES == i)
			break;

		entry = &sw->info->mac_table[i];
		if (!entry->valid ||
		    memcmp(data, entry->addr, ETH_ALEN))
			continue;

		/* Block if received port is closed. */
		if (len && !entry->override && !(sw->rx_ports & (1 << port)))
			break;

		alu = &sw->info->alu_table[i];
		forward = alu->forward;

		/* Allow to reach host as the frame is not forwarded. */
		if (alu->forward & FWD_HOST)
			break;

		/* Remember the frame when forwarding to STP device. */
		if ((alu->forward & FWD_STP_DEV) && sw->info->fwd_ports > 1) {
			unsigned long now;

			/* Port is zero-based. */
			port++;
			crc = ether_crc(len, data);
			now = jiffies;
			sw_add_rx(sw, crc, now, now + 1000 / HZ,
				sw->info->fwd_ports - 1, port);
		}
		break;
	}

	/*
	 * Check port state in case it is changed after processing arrived
	 * BPDU.
	 */
	if (forward && len && !i)
		schedule_delayed_work(sw->stp_monitor, 1);
	return forward;
}  /* sw_block_rx */

static int sw_block_tx(struct ksz_sw *sw, u8 *data, int len, int port)
{
	struct ksz_mac_table *entry;
	struct ksz_alu_table *alu;
	int i;
	u32 crc = 0;
	unsigned long now = 0;
	int block = false;
	int forward = 0;

	for (i = 0; i < MULTI_MAC_TABLE_ENTRIES; i++) {
		entry = &sw->info->mac_table[i];
		if (!entry->valid ||
		    memcmp(data, entry->addr, ETH_ALEN))
			continue;

		alu = &sw->info->alu_table[i];
		forward = alu->forward;

		/* No need to block. */
		if (alu->forward & FWD_HOST)
			break;

		/* Check frame is not forwarded by software. */
		if (port && (alu->forward & FWD_STP_DEV) &&
		    sw->info->fwd_ports > 1) {
			crc = ether_crc(len, data);
			now = jiffies;
			if (sw_del_rx(sw, crc, now, port)) {
				if ((1 << (port - 1)) & sw->info->member) {
					block = true;
					forward = 0;
				}
			}
		}
		break;
	}

	/* Check duplicate frames sent by main and STP devices. */
	if ((forward & (FWD_MAIN_DEV | FWD_STP_DEV)) ==
	    (FWD_MAIN_DEV | FWD_STP_DEV)) {

		/* Re-use CRC if already calculated. */
		if (!now) {
			crc = ether_crc(len, data);
			now = jiffies;
		}
		if (sw_del_tx(sw, crc, now, !!port))
			block = true;
		else
			sw_add_tx(sw, crc, now, now + 100 / HZ, 1, !!port);
	}
	return block;
}  /* sw_block_tx */

static int sw_stp_rx(struct ksz_sw *sw, struct net_device *dev,
	struct sk_buff *skb, int port, int *forward)
{
	if ((sw->features & STP_SUPPORT) && br_port_exists(dev)) {
		*forward = sw_block_rx(sw, skb->data, skb->len, port);
		if (!*forward && sw->dev_offset && dev != sw->netdev[0]) {
			dev = sw->netdev[0];
			if ((dev->flags & IFF_PROMISC) ||
			    ((dev->flags & IFF_ALLMULTI) &&
			    (skb->data[0] & 1)))
				*forward = FWD_MAIN_DEV;
		}
		return true;
	}
	return false;
}  /* sw_stp_rx */
#endif

static struct net_device *sw_rx_dev(struct ksz_sw *sw, u8 *data, u32 *len,
	int *tag, int *port)
{
	struct net_device *dev;
#ifdef KSZ_DLR
	struct vlan_ethhdr *vlan = (struct vlan_ethhdr *) data;
#endif

	/* Get received port number. */
	if (sw->overrides & TAIL_TAGGING) {
		(*len)--;
		*tag = data[*len - 4];

		/* In case tagging is not working right. */
		if (*tag >= SWITCH_PORT_NUM)
			*tag = 0;

		/* Save receiving port. */
		*port = *tag;
	}
	dev = sw->netdev[*tag + sw->dev_offset];
#ifdef KSZ_DLR
	if (vlan->h_vlan_proto == htons(ETH_P_8021Q)) {
		if (vlan->h_vlan_encapsulated_proto == htons(DLR_TAG_TYPE))
			return dev;
	}
#endif
	if (sw->dev_count > 1) {
		u8 stp;

		stp = sw->info->stp & sw->info->stp_down;
		if (stp & (1 << *tag))
			return NULL;
		if (!netif_running(dev))
			return NULL;
	}
	if (sw->features & VLAN_PORT_TAGGING) {
		(*tag)++;
		if (!(sw->vlan_id & (1 << *tag)))
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
	struct net_device *dev, struct sk_buff *skb, int forward,
	struct net_device **parent_dev, struct sk_buff **parent_skb)
{
	if (sw->dev_offset && dev != sw->netdev[0]) {
		*parent_dev = sw->netdev[0];
		if (!forward)
			forward = FWD_MAIN_DEV | FWD_STP_DEV;
		if ((forward & (FWD_MAIN_DEV | FWD_STP_DEV)) ==
		    (FWD_MAIN_DEV | FWD_STP_DEV))
			*parent_skb = skb_copy(skb, GFP_ATOMIC);
		else if (!(forward & FWD_STP_DEV))
			dev = *parent_dev;
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
	vlan_skb = skb_copy(skb, GFP_ATOMIC);
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

static int sw_drop_icmp(struct sk_buff *skb, int extra_skb)
{
	int drop = 0;

	if (skb && extra_skb &&	skb->protocol == htons(ETH_P_IP)) {
		struct iphdr *iph = (struct iphdr *) skb->data;

		drop = (iph->protocol == IPPROTO_ICMP);
	}
	return drop;
}  /* sw_drop_icmp */

static int sw_drv_rx(struct ksz_sw *sw, struct sk_buff *skb, int port)
{
	int ret = 1;

#ifdef KSZ_DLR
	if (sw->features & DLR_HW)
		ret = dlr_rcv(&sw->info->dlr, skb, port);
#endif
	return ret;
}  /* sw_drv_rx */

static int sw_get_tx_len(struct ksz_sw *sw, struct sk_buff *skb)
{
	int len = skb->len;

	if (!(sw->overrides & TAIL_TAGGING))
		return len;
	if (len < 60)
		len = 60;
	len += 1;
	return len;
}  /* sw_get_tx_len */

static void sw_add_tail_tag(struct ksz_sw *sw, struct sk_buff *skb, int ports)
{
	u8 *trailer;
	int len = 1;

	trailer = skb_put(skb, len);
	if (!ports)
		ports = TAIL_TAG_LOOKUP;
	trailer[0] = (u8) ports;
}  /* sw_add_tail_tag */

static int sw_get_tail_tag(u8 *trailer, int *port)
{
	int len = 1;

	*port = *trailer;
	return len;
}  /* sw_get_tail_tag */

static int add_frag(void *from, char *to, int offset, int len, int odd,
	struct sk_buff *skb)
{
	memcpy(to + offset, from, len);
	return 0;
}

static struct sk_buff *sw_check_skb(struct ksz_sw *sw, struct sk_buff *skb,
	struct ksz_port *priv, void *ptr,
	int (*update_msg)(u8 *data, u32 port, u32 overrides))
{
	int len;
	int port;
	struct sk_buff *org_skb;
	int update_dst = (sw->overrides & TAIL_TAGGING);

	if (!update_dst)
		return skb;

#ifdef CONFIG_NET_DSA_TAG_TAIL
	if (skb->protocol == htons(ETH_P_TRAILER))
		return skb;
#endif
#ifdef KSZ_DLR
	if (skb->protocol == htons(DLR_TAG_TYPE))
		return skb;
#endif

	org_skb = skb;
	port = 0;

	/* This device is associated with a switch port. */
	if (1 == priv->port_cnt)
		port = priv->first_port + 1;

	do {
		u16 prio;
		u16 vid;

		if (!(sw->features & VLAN_PORT) || port ||
				vlan_get_tag(skb, &vid))
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
	if (!(sw->overrides & TAIL_TAGGING))
		return skb;

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
		skb->data[len] = 0;
		if (port)
			skb->data[len] = 1 << (port - 1);
#ifdef CONFIG_KSZ_STP
		if (sw->features & STP_SUPPORT) {
			int forward = sw_block_rx(sw, skb->data, 0, 0);

			/*
			 * Need destination port if lookup is set to forward
			 * to host.
			 */
			if (forward & FWD_HOST) {
				if (!port)
					port = sw->tx_ports & ~sw->HOST_MASK;
				if (port && (forward & FWD_HOST_OVERRIDE))
					port |= TAIL_TAG_OVERRIDE;
				skb->data[len] = (u8) port;
			}
		}
#endif
		if (!skb->data[len])
			skb->data[len] = TAIL_TAG_LOOKUP;
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
		sw->tx_pad[sw->tx_start] = 0;
		if (port)
			sw->tx_pad[sw->tx_start] = 1 << (port - 1);
		if (!sw->tx_pad[sw->tx_start])
			sw->tx_pad[sw->tx_start] = TAIL_TAG_LOOKUP;
		skb_append_datato_frags(sk, skb, add_frag, sw->tx_pad, len);
	}
	return skb;
}  /* sw_check_skb */

static struct sk_buff *sw_check_tx(struct ksz_sw *sw, struct net_device *dev,
	struct sk_buff *skb, struct ksz_port *priv)
{
	void *ptr = NULL;
	int (*update_msg)(u8 *data, u32 port, u32 overrides) = NULL;

#ifdef CONFIG_KSZ_STP
	if (sw->features & STP_SUPPORT) {
		int port = 0;

		/* This device is associated with a switch port. */
		if (1 == priv->port_cnt)
			port = priv->first_port + 1;
		if ((br_port_exists(dev) || !port) &&
		    sw_block_tx(sw, skb->data, skb->len, port)) {
			dev_kfree_skb_irq(skb);
			return NULL;
		}
	}
#endif
	return sw_check_skb(sw, skb, priv, ptr, update_msg);
}  /* sw_check_tx */

#ifdef CONFIG_NET_DSA_TAG_TAIL
static struct sk_buff *tail_xmit(struct sk_buff *skb, struct net_device *dev,
	struct ksz_sw *sw)
{
	struct sk_buff *nskb;
	int padlen;
	int addlen = 8;

	if (skb->protocol == htons(ETH_P_TRAILER))
		return skb;

	/*
	 * We have to make sure that the trailer ends up as the very
	 * last 4 bytes of the packet.  This means that we have to pad
	 * the packet to the minimum ethernet frame size, if necessary,
	 * before adding the trailer.
	 */
	padlen = 0;
	if (skb->len < 60)
		padlen = 60 - skb->len;

	nskb = alloc_skb(NET_IP_ALIGN + skb->len + padlen + addlen, GFP_ATOMIC);
	if (nskb == NULL) {
		dev_kfree_skb_irq(skb);
		return NULL;
	}
	skb_reserve(nskb, NET_IP_ALIGN);

	skb_reset_mac_header(nskb);
	skb_set_network_header(nskb, skb_network_header(skb) - skb->head);
	skb_set_transport_header(nskb, skb_transport_header(skb) - skb->head);
	skb_copy_and_csum_dev(skb, skb_put(nskb, skb->len));
	nskb->dev = skb->dev;
	dev_kfree_skb_irq(skb);

	if (padlen) {
		u8 *pad = skb_put(nskb, padlen);
		memset(pad, 0, padlen);
	}

	sw->net_ops->add_tail_tag(sw, nskb, 0);

	nskb->protocol = htons(ETH_P_TRAILER);

	return nskb;
}
#endif

static struct sk_buff *sw_final_skb(struct ksz_sw *sw, struct sk_buff *skb,
	struct net_device *dev, struct ksz_port *port)
{
#ifdef CONFIG_NET_DSA_TAG_TAIL
	skb = tail_xmit(skb, dev, sw);
	if (!skb)
		return NULL;
#endif

	skb = sw->net_ops->check_tx(sw, dev, skb, port);
	if (!skb)
		return NULL;
	return skb;
}  /* sw_final_skb */

static void sw_start(struct ksz_sw *sw, u8 *addr)
{
	int need_tail_tag = false;

	sw->ops->acquire(sw);
	sw_setup(sw);
	sw_set_addr(sw, addr);
#if 0
	if (1 == sw->dev_count)
		sw_cfg_self_filter(sw, true);
#endif
#ifdef KSZ_DLR
	if (sw->features & DLR_HW)
		need_tail_tag = true;
#endif
	if (sw->dev_count > 1)
		need_tail_tag = true;
	if (sw->features & VLAN_PORT) {
		if (sw->features & VLAN_PORT_REMOVE_TAG) {
			int i;

			for (i = 0; i < SWITCH_PORT_NUM; i++) {
				if (i == sw->port_cnt)
					continue;
				port_cfg_rmv_tag(sw, i, true);
			}
			sw->overrides |= TAG_REMOVE;
		}
		if (sw->features & VLAN_PORT_TAGGING)
			need_tail_tag = true;
	}
	if (sw->features & DSA_SUPPORT) {
		int p;

		need_tail_tag = true;
		for (p = 0; p < sw->mib_port_cnt - 1; p++) {
			sw_cfg_each_port(sw, p, false);
			port_set_stp_state(sw, p, STP_STATE_SIMPLE);
		}
		sw_cfg_each_port(sw, p, true);
		port_set_stp_state(sw, p, STP_STATE_SIMPLE);
	}
	if (need_tail_tag) {
		sw_cfg_tail_tag(sw, true);
		sw->overrides |= TAIL_TAGGING;
	}
	sw_ena_intr(sw);
	sw->ops->release(sw);
}  /* sw_start */

static int sw_stop(struct ksz_sw *sw, int complete)
{
	int reset = false;

	sw->ops->acquire(sw);
	if (!reset)
		sw_reset(sw);
	reset = true;
	sw_init(sw);

	/* Clean out static MAC table when the switch shutdown. */
	if ((sw->features & STP_SUPPORT) && complete)
		sw_clr_sta_mac_table(sw);
	sw->ops->release(sw);
	return reset;
}  /* sw_stop */

static void sw_init_mib(struct ksz_sw *sw)
{
	int i;

	for (i = 0; i < sw->mib_port_cnt; i++) {
		if (i == sw->port_cnt)
			continue;
		sw->port_mib[i].mib_start = 0;
		if (next_jiffies < jiffies)
			next_jiffies = jiffies + HZ * 2;
		else
			next_jiffies += MIB_READ_INTERVAL;
		sw->counter[i].time = next_jiffies;
		sw->port_state[i].state = media_disconnected;
		port_init_cnt(sw, i);
	}
	sw->port_state[sw->HOST_PORT].state = media_connected;
}  /* sw_init_mib */

static void sw_open_dev(struct ksz_sw *sw, struct net_device *dev, u8 *addr)
{
	sw_init_mib(sw);

	sw->net_ops->start(sw, addr);
	sw->main_dev = dev;
}  /* sw_open_dev */

static void sw_open_port(struct ksz_sw *sw, struct net_device *dev,
	struct ksz_port *port, u8 *state)
{
	int i;
	int p;

	for (i = 0, p = port->first_port; i < port->port_cnt; i++, p++) {
		/*
		 * Initialize to invalid value so that link detection
		 * is done.
		 */
		sw->port_info[p].link = 0xFF;
		sw->port_info[p].state = media_unknown;
		sw->port_info[p].report = true;
	}

	sw->ops->acquire(sw);

	/* Need to open the port in multiple device interfaces mode. */
	if (sw->dev_count > 1 && (!sw->dev_offset || dev != sw->netdev[0])) {
#ifdef CONFIG_KSZ_STP
		if (!br_port_exists(dev))
#endif
			*state = STP_STATE_SIMPLE;
		port_set_stp_state(sw, port->first_port, *state);
	}

	sw->phy_intr = sw->PORT_MASK;
	if (port->force_link)
		port_force_link_speed(port);
	else
		port_set_link_speed(port);
	port_get_link_speed(port);
	sw->ops->release(sw);
}  /* sw_open_port */

static void sw_close_port(struct ksz_sw *sw, struct net_device *dev,
	struct ksz_port *port)
{
	/* Need to shut the port manually in multiple device interfaces mode. */
	if (sw->dev_count > 1 && (!sw->dev_offset || dev != sw->netdev[0])) {
		sw->ops->acquire(sw);
		port_set_stp_state(sw, port->first_port, STP_STATE_DISABLED);

#ifdef CONFIG_KSZ_STP
		/* Port is closed.  Need to change bridge setting. */
		if ((sw->features & STP_SUPPORT) && br_port_exists(dev)) {
			int pi;

			pi = 1 << port->first_port;
			if (sw->info->member & pi) {
				sw->info->member &= ~pi;

				/* No ports in forwarding state. */
				if (!sw->info->member) {
					port_set_stp_state(sw, SWITCH_PORT_NUM,
						STP_STATE_SIMPLE);
					sw->ops->release(sw);
					sw_block_addr(sw);
					sw_block_multi(sw);
					sw->ops->acquire(sw);
				}
				bridge_change(sw);
			}
		}
#endif
		sw->ops->release(sw);
	}
}  /* sw_close_port */

static void sw_open(struct ksz_sw *sw)
{
#ifdef KSZ_DLR
	if (sw->features & DLR_HW)
		prep_dlr(&sw->info->dlr, sw->main_dev, sw->main_dev->dev_addr);
#endif
	/* Timer may already be started by the SPI device. */
	if (!sw->monitor_timer_info->max)
		ksz_start_timer(sw->monitor_timer_info,
			sw->monitor_timer_info->period);
}  /* sw_open */

static void sw_close(struct ksz_sw *sw)
{
	ksz_stop_timer(sw->monitor_timer_info);
	cancel_delayed_work_sync(sw->link_read);
	cancel_delayed_work_sync(sw->stp_monitor);
}  /* sw_close */

static u8 sw_set_mac_addr(struct ksz_sw *sw, struct net_device *dev,
	u8 promiscuous, int port)
{
	sw->ops->acquire(sw);
	if (sw->dev_count > 1 && (!sw->dev_offset || dev != sw->netdev[0])) {
		if (sw->features & DIFF_MAC_ADDR) {
			sw->features &= ~DIFF_MAC_ADDR;
			--promiscuous;
		}
		for (port = 0; port < SWITCH_PORT_NUM; port++) {
			if (port == sw->port_cnt)
				continue;
			if (memcmp(sw->port_info[port].mac_addr,
					dev->dev_addr, ETH_ALEN)) {
				sw->features |= DIFF_MAC_ADDR;
				++promiscuous;
				break;
			}
		}
	} else {
		int i;

		/* Make MAC address the same in all the ports. */
		if (sw->dev_count > 1) {
			for (i = 0; i < SWITCH_PORT_NUM; i++) {
				if (i == sw->port_cnt)
					continue;
				memcpy(sw->netdev[i + 1]->dev_addr,
					dev->dev_addr, ETH_ALEN);
			}
			if (sw->features & DIFF_MAC_ADDR) {
				sw->features &= ~DIFF_MAC_ADDR;
				--promiscuous;
			}
		}
		if (dev == sw->netdev[0])
			sw_set_addr(sw, dev->dev_addr);
	}
	sw->ops->release(sw);
#ifdef KSZ_DLR
	if (sw->features & DLR_HW)
		dlr_change_addr(&sw->info->dlr, dev->dev_addr);
#endif
	return promiscuous;
}  /* sw_set_mac_addr */

/*
 * This enables multiple network device mode for the switch, which contains at
 * least two physical ports.  Some users like to take control of the ports for
 * running Spanning Tree Protocol.  The driver will create an additional eth?
 * device for each port depending on the mode.
 *
 * Some limitations are the network devices cannot have different MTU and
 * multicast hash tables.
 */
static int multi_dev;

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
static int stp;

/*
 * This enables fast aging in the switch.  Not sure what situation requires
 * that.  However, fast aging is used to flush the dynamic MAC table when STP
 * support is enabled.
 */
static int fast_aging;

static void sw_setup_special(struct ksz_sw *sw, int *port_cnt,
	int *mib_port_cnt, int *dev_cnt)
{
	sw->dev_offset = 0;
	sw->phy_offset = 0;
	if (sw->stp) {
		sw->fast_aging = 1;
		sw->multi_dev = 1;
		sw->features |= STP_SUPPORT;
	}
	if (sw->fast_aging)
		sw->overrides |= FAST_AGING;

	/* Multiple network device interfaces are required. */
	if (1 == sw->multi_dev) {
		sw->dev_count = SWITCH_PORT_NUM;
		sw->phy_offset = 1;
	} else if (2 == sw->multi_dev)
		sw->features |= VLAN_PORT | VLAN_PORT_TAGGING;
	else if (3 == sw->multi_dev) {
		sw->dev_count = SWITCH_PORT_NUM;
		sw->dev_offset = 1;
	} else if (4 == sw->multi_dev)
		sw->features |= VLAN_PORT;
	else if (5 == sw->multi_dev) {
		sw->dev_count = SWITCH_PORT_NUM;
		sw->dev_offset = 1;
		sw->features |= VLAN_PORT | VLAN_PORT_TAGGING;
	}

	/* Single network device has multiple ports. */
	if (1 == sw->dev_count) {
		*port_cnt = SWITCH_PORT_NUM;
		*mib_port_cnt = SWITCH_PORT_NUM;
		if (sw->port_cnt < sw->mib_port_cnt) {
			(*port_cnt)--;
			(*mib_port_cnt)--;
		}
	} else if (sw->port_cnt < sw->mib_port_cnt)
		sw->dev_count--;
	*dev_cnt = sw->dev_count;
	if (3 == sw->multi_dev || 5 == sw->multi_dev)
		(*dev_cnt)++;
}

static void sw_setup_dev(struct ksz_sw *sw, struct net_device *dev,
	char *dev_name, struct ksz_port *port, int i, int port_cnt,
	int mib_port_cnt)
{
	int cnt;
	int p;
	int pi;

	p = i;
	if (p)
		p -= sw->dev_offset;
	port->port_cnt = port_cnt;
	port->mib_port_cnt = mib_port_cnt;
	port->first_port = p;
	port->flow_ctrl = PHY_FLOW_CTRL;

	port->sw = sw;
	port->linked = &sw->port_info[port->first_port];

	for (cnt = 0, pi = p; cnt < port_cnt; cnt++, pi++) {
		sw->port_info[pi].state = media_disconnected;
		sw->netdev[pi + sw->dev_offset] = dev;
	}
	if (sw->dev_offset) {
		/*
		 * First device associated with switch has been
		 * created.
		 */
		if (i)
			snprintf(dev->name, IFNAMSIZ, "%s.10%%d", dev_name);
		else {
			port->port_cnt = SWITCH_PORT_NUM;
			port->mib_port_cnt = SWITCH_PORT_NUM;
			if (sw->port_cnt < sw->mib_port_cnt) {
				port->port_cnt--;
				port->mib_port_cnt--;
			}
			sw->netdev[i] = dev;
		}
	}
	INIT_WORK(&port->link_update, link_update_work);
	if (sw->features & VLAN_PORT)
		dev->features |= NETIF_F_HW_VLAN_CTAG_FILTER;
}

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
	dev->trans_start = jiffies;
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
	.setup_dev		= sw_setup_dev,
	.setup_special		= sw_setup_special,
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

	.get_tx_len		= sw_get_tx_len,
	.add_tail_tag		= sw_add_tail_tag,
	.get_tail_tag		= sw_get_tail_tag,
	.check_tx		= sw_check_tx,
	.rx_dev			= sw_rx_dev,
	.match_pkt		= sw_match_pkt,
	.parent_rx		= sw_parent_rx,
	.port_vlan_rx		= sw_port_vlan_rx,
	.drop_icmp		= sw_drop_icmp,
	.final_skb		= sw_final_skb,
	.drv_rx			= sw_drv_rx,

#ifdef CONFIG_KSZ_STP
	.get_port_state		= get_port_state,

	.set_multi		= sw_set_multi,
	.stp_rx			= sw_stp_rx,
	.blocked_rx		= sw_blocked_rx,
	.monitor_ports		= monitor_ports,
#endif
};

static struct ksz_sw_ops sw_ops = {
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

	.cfg_mac		= sw_cfg_mac,
	.cfg_vlan		= sw_cfg_vlan,
	.alloc_mac		= sw_alloc_mac,
	.free_mac		= sw_free_mac,
	.alloc_vlan		= sw_alloc_vlan,
	.free_vlan		= sw_free_vlan,

	.get_id			= sw_get_id,
	.cfg_tail_tag		= sw_cfg_tail_tag,
	.cfg_each_port		= sw_cfg_each_port,
	.port_to_phy_addr	= sw_port_to_phy_addr,
	.set_port_addr		= sw_set_port_addr,

	.cfg_src_filter		= sw_cfg_src_filter,
	.flush_table		= sw_flush_dyn_mac_table,

};

