/**
 * Microchip KSZ8895 switch common code
 *
 * Copyright (c) 2015-2017 Microchip Technology Inc.
 *	Tristram Ha <Tristram.Ha@microchip.com>
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

#define MAX_SYSFS_BUF_SIZE		(4080 - 80)

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

	PROC_SET_PASS_ALL,

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

static int get_first_port(struct ksz_sw *sw)
{
	int p = 0;

#ifdef SKIP_FIRST_PORT
	p = sw->first_port;
#endif
	return p;
}  /* get_first_port */

static int chk_last_port(struct ksz_sw *sw, int p)
{
#ifdef USE_FEWER_PORTS
	if (sw->last_port && p == sw->last_port)
		p = sw->HOST_PORT;
#endif
	return p;
}  /* chk_last_port */

static void sw_acquire(struct ksz_sw *sw)
{
	mutex_lock(&sw->lock);
	mutex_lock(sw->reglock);
}  /* sw_acquire */

static void sw_release(struct ksz_sw *sw)
{
	mutex_unlock(sw->reglock);
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
#define VLAN_TABLE_FID			00-00003F81-FC0FE07F
#define VLAN_TABLE_MEMBERSHIP		00-0007C03E-01F00F80
#define VLAN_TABLE_VALID		00-00080040-02001000
*/

#define VLAN_TABLE_FID			0x007F
#define VLAN_TABLE_MEMBERSHIP		0x0F80
#define VLAN_TABLE_VALID		0x1000

#define VLAN_TABLE_MEMBERSHIP_S		7
#define VLAN_TABLE_S			13

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
#define MIB_PACKET_DROPPED		00-00000000-0000FFFF
#define MIB_COUNTER_VALID		00-00000000-40000000
#define MIB_COUNTER_OVERFLOW		00-00000000-80000000
*/

#ifndef MIB_COUNTER_OVERFLOW
#define MIB_COUNTER_OVERFLOW		(1 << 7)
#define MIB_COUNTER_VALID		(1 << 6)

#define MIB_COUNTER_VALUE		0x3FFFFFFF
#endif

#define KS_MIB_PACKET_DROPPED_TX_0	0x100
#define KS_MIB_PACKET_DROPPED_TX_1	0x101
#define KS_MIB_PACKET_DROPPED_TX_2	0x102
#define KS_MIB_PACKET_DROPPED_TX_3	0x103
#define KS_MIB_PACKET_DROPPED_TX_4	0x104
#define KS_MIB_PACKET_DROPPED_RX_0	0x105
#define KS_MIB_PACKET_DROPPED_RX_1	0x106
#define KS_MIB_PACKET_DROPPED_RX_2	0x107
#define KS_MIB_PACKET_DROPPED_RX_3	0x108
#define KS_MIB_PACKET_DROPPED_RX_4	0x109

#define MIB_PACKET_DROPPED		0x0000FFFF

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
	sw_r(sw, REG_IND_DATA_HI, &buf, sizeof(buf));
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
	sw_w(sw, REG_IND_DATA_HI, &buf, sizeof(buf));
	sw->reg->w16(sw, REG_IND_CTRL_0, ctrl_addr);
	sw->ops->release(sw);
}  /* sw_w_table_64 */

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
	u8 ports = 0;
	u8 timestamp = 0;
	u8 fid = 0;
	int first_break = true;

	memset(mac_addr, 0, ETH_ALEN);
	i = 0;
	do {
		if (!sw_r_dyn_mac_table(sw, i, mac_addr, &fid, &ports,
				&timestamp, &entries)) {
			if (len >= MAX_SYSFS_BUF_SIZE && first_break) {
				first_break = false;
				len += sprintf(buf + len, "...\n");
			}
			if (len < MAX_SYSFS_BUF_SIZE)
			len += sprintf(buf + len,
				"%02X:%02X:%02X:%02X:%02X:%02X  "
				"f:%2x  p:%x  t:%x\n",
				mac_addr[0], mac_addr[1], mac_addr[2],
				mac_addr[3], mac_addr[4], mac_addr[5],
				fid, ports, timestamp);
			else
			printk(KERN_INFO
				"%02X:%02X:%02X:%02X:%02X:%02X  "
				"f:%2x  p:%x  t:%x\n",
				mac_addr[0], mac_addr[1], mac_addr[2],
				mac_addr[3], mac_addr[4], mac_addr[5],
				fid, ports, timestamp);
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
	u16 i;
	struct ksz_mac_table mac;

	i = 0;
	do {
		if (!sw_r_sta_mac_table(sw, i, &mac)) {
			len += sprintf(buf + len,
				"%2x: %02X:%02X:%02X:%02X:%02X:%02X  "
				"%02x  %u  %u:%x\n",
				i, mac.addr[0], mac.addr[1], mac.addr[2],
				mac.addr[3], mac.addr[4], mac.addr[5],
				mac.ports, mac.override, mac.use_fid, mac.fid);
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

	i = STATIC_MAC_TABLE_ENTRIES;
	do {
		entry = &sw->info->mac_table[i];
		if (entry->valid) {
			len += sprintf(buf + len,
				"%x: %02X:%02X:%02X:%02X:%02X:%02X  "
				"%x  %u  %u:%x\n",
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
	u16 addr;
	int index;

	addr = vid / 4;
	index = vid & 3;
	sw_r_table_64(sw, TABLE_VLAN, addr, data_hi, data_lo);
	buf >>= VLAN_TABLE_S * index;
	buf &= (1 << VLAN_TABLE_S) - 1;
	vlan->fid = (u8)(buf & VLAN_TABLE_FID);
	vlan->member = (u8)((buf & VLAN_TABLE_MEMBERSHIP) >>
		VLAN_TABLE_MEMBERSHIP_S);
	vlan->valid = !!(buf & VLAN_TABLE_VALID);
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
	u64 mask;
	u64 val;
	u32 *data_lo = (u32 *) &buf;
	u32 *data_hi = data_lo + 1;
	u16 addr;
	int index;

	addr = vid / 4;
	index = vid & 3;
	sw_r_table_64(sw, TABLE_VLAN, addr, data_hi, data_lo);
	mask = (1 << VLAN_TABLE_S) - 1;
	mask <<= VLAN_TABLE_S * index;
	val = vlan->fid;
	val |= (u16) vlan->member << VLAN_TABLE_MEMBERSHIP_S;
	if (vlan->valid)
		val |= VLAN_TABLE_VALID;
	val <<= VLAN_TABLE_S * index;
	buf &= ~mask;
	buf |= val;
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
					continue;
				if (len >= MAX_SYSFS_BUF_SIZE && first_break) {
					first_break = false;
					len += sprintf(buf + len, "...\n");
				}
				if (len < MAX_SYSFS_BUF_SIZE)
					len += sprintf(buf + len,
						"0x%03x: %2x  %2x\n", vid,
						fid[j], member[j]);
				else
					printk(KERN_INFO
						"0x%03x: %2x  %2x\n", vid,
						fid[j], member[j]);
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

	1,
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

	sw->ops->acquire(sw);

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
static void port_r_mib_pkt(struct ksz_sw *sw, int port, u16 addr, u32 *last,
	u64 *cnt)
{
	u32 cur;
	u32 data;
	u16 ctrl_addr;

	addr -= SWITCH_COUNTER_NUM;
	ctrl_addr = addr ? KS_MIB_PACKET_DROPPED_TX_0 :
		KS_MIB_PACKET_DROPPED_RX_0;
	ctrl_addr += port;

	sw->ops->acquire(sw);

	ctrl_addr |= IND_ACC_TABLE(TABLE_MIB | TABLE_READ);
	sw->reg->w16(sw, REG_IND_CTRL_0, ctrl_addr);

	data = sw->reg->r32(sw, REG_IND_DATA_LO);
	sw->ops->release(sw);
	data &= MIB_PACKET_DROPPED;
	cur = last[addr];
	if (data != cur) {
		last[addr] = data;
		if (data < cur)
			data += MIB_PACKET_DROPPED + 1;
		data -= cur;
		*cnt += data;
	}
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
					mib->dropped,
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

	if (port < sw->mib_port_cnt) {
		start = port;
		stop = port + 1;
	} else {
		start = get_first_port(sw);
		stop = sw->mib_port_cnt;
	}
	if (ctrl & 1)
		for (count = start; count < stop; count++) {
			struct ksz_port_mib *mib;

			count = chk_last_port(sw, count);
			mib = &sw->port_mib[count];
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
static inline void port_init_cnt(struct ksz_sw *sw, int port)
{
	struct ksz_port_mib *mib = &sw->port_mib[port];

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
			port_r_mib_pkt(sw, port, mib->cnt_ptr, mib->dropped,
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

#if 0
static u8 port_r_s(struct ksz_sw *sw, int p, u32 reg, u8 mask,
	u8 shift)
{
	u8 data;

	port_r8(sw, p, reg, &data);
	data >>= shift;
	data &= mask;
	return data;
}

static void port_w_s(struct ksz_sw *sw, int p, u32 reg, u8 mask,
	u8 shift, u8 val)
{
	u8 data;

	port_r8(sw, p, reg, &data);
	data &= ~(mask << shift);
	data |= (val & mask) << shift;
	port_w8(sw, p, reg, data);
}
#endif

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
	int p = get_first_port(sw);

	/* Enable switch broadcast storm protection at 10% percent rate. */
	hw_cfg_broad_storm(sw, BROADCAST_STORM_PROTECTION_RATE);
	for (port = p; port < sw->mib_port_cnt; port++) {
		port = chk_last_port(sw, port);
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

/**
 * port_cfg_rate - configure port priority rate
 * @sw:		The switch instance.
 * @port:	The port index.
 * @prio:	The priority index to configure.
 * @offset:	The receive or transmit rate offset.
 * @shift:	The shift position to set the value.
 * @rate:	The rate limit in number of Kbps.
 *
 * This helper routine configures the priority rate of the port.
 */
static void port_cfg_rate(struct ksz_sw *sw, int port, int prio, int offset,
	uint rate)
{
	u8 factor;

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
 *
 * This helper routine retrieves the priority rate of the port.
 */
static void port_get_rate(struct ksz_sw *sw, int port, int prio, int offset,
	uint *rate)
{
	u8 data;

	port_r8(sw, port, offset + prio, &data);
	*rate = get_rate_from_val(data);
}  /* port_get_rate */

/**
 * hw_cfg_prio_rate - configure port priority
 * @sw:		The switch instance.
 * @port:	The port index.
 * @prio:	The priority index to configure.
 * @rate:	The rate limit in number of Kbps.
 * @offset:	The receive or transmit rate offset.
 * @result:	Buffer to store the data rate in number of Kbps.
 *
 * This helper routine configures the priority rate of the port and retrieves
 * the actual rate number.
 */
static void hw_cfg_prio_rate(struct ksz_sw *sw, int port, int prio, uint rate,
	int offset, uint *result)
{
	port_cfg_rate(sw, port, prio, offset, rate);
	port_get_rate(sw, port, prio, offset, result);
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
		REG_PORT_IN_RATE_0,
		&sw->info->port_cfg[port].rx_rate[prio]);
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
		REG_PORT_OUT_RATE_0,
		&sw->info->port_cfg[port].tx_rate[prio]);
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
static int sw_chk_rx_prio_rate(struct ksz_sw *sw, int port)
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
static void sw_dis_rx_prio_rate(struct ksz_sw *sw, int port)
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
static void sw_ena_rx_prio_rate(struct ksz_sw *sw, int port)
{
	int prio;

	for (prio = 0; prio < PRIO_QUEUES; prio++) {
		hw_cfg_rx_prio_rate(sw, port, prio,
			sw->info->port_cfg[port].rx_rate[prio]);
	}
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
static int sw_chk_tx_prio_rate(struct ksz_sw *sw, int port)
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
static void sw_dis_tx_prio_rate(struct ksz_sw *sw, int port)
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
static void sw_ena_tx_prio_rate(struct ksz_sw *sw, int port)
{
	int prio;

	for (prio = 0; prio < PRIO_QUEUES; prio++) {
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
	int p = get_first_port(sw);

	for (port = p; port < sw->mib_port_cnt; port++) {
		port = chk_last_port(sw, port);
		hw_get_rate_limit(sw, port);
		for (prio = 0; prio < PRIO_QUEUES; prio++) {
			hw_get_rate_ctrl(sw, port, prio);
			offset = REG_PORT_IN_RATE_0;
			port_get_rate(sw, port, prio, offset,
				&sw->info->port_cfg[port].rx_rate[prio]);
			offset = REG_PORT_OUT_RATE_0;
			port_get_rate(sw, port, prio, offset,
				&sw->info->port_cfg[port].tx_rate[prio]);
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
		first = get_first_port(sw);
		cnt = sw->mib_port_cnt;
	}
	for (index = first; index < cnt; index++) {
		index = chk_last_port(sw, index);
		learn_disable[index] = port_chk_dis_learn(sw, index);
		if (!learn_disable[index])
			port_cfg_dis_learn(sw, index, 1);
	}
	sw_cfg(sw, S_FLUSH_TABLE_CTRL, SW_FLUSH_DYN_MAC_TABLE, 1);
	for (index = first; index < cnt; index++) {
		index = chk_last_port(sw, index);
		if (!learn_disable[index])
			port_cfg_dis_learn(sw, index, 0);
	}
}  /* sw_flush_dyn_mac_table */

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
	int p = get_first_port(sw);

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
	for (port = p; port < sw->mib_port_cnt; port++) {
		port = chk_last_port(sw, port);
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
	return sw_chk(sw, REG_SW_CTRL_18,
		SW_SELF_ADDR_FILTER_ENABLE);
}

static inline void sw_cfg_self_filter(struct ksz_sw *sw, int set)
{
	sw_cfg(sw, REG_SW_CTRL_18, SW_SELF_ADDR_FILTER_ENABLE, set);
}

static void sw_cfg_src_filter(struct ksz_sw *sw, int set)
{
}  /* sw_cfg_src_filter */

static void sw_fwd_unk_vid(struct ksz_sw *sw)
{
	sw_w8(sw, REG_SW_UNK_VID_CTRL, sw->HOST_MASK | SW_UNK_FWD_ENABLE);
}  /* sw_fwd_unk_vid */

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
 * port.  The port transmit queue is split into two or four priority queues.
 */
static void port_set_prio_queue(struct ksz_sw *sw, int port, int queue)
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
	int port;
	SW_D data;
	int p = get_first_port(sw);

	sw->reg->r(sw, S_802_1P_PRIO_CTRL, sw->info->p_802_1p,
		PRIO_802_1P_ENTRIES / KS_PRIO_IN_REG);

	sw->reg->r(sw, S_TOS_PRIO_CTRL, sw->info->diffserv,
		DIFFSERV_ENTRIES / KS_PRIO_IN_REG);

	for (port = p; port < sw->mib_port_cnt; port++) {
		port = chk_last_port(sw, port);
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
	int p = get_first_port(sw);

	/* All QoS functions disabled. */
	for (port = p; port < sw->mib_port_cnt; port++) {
		port = chk_last_port(sw, port);
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
	int p = get_first_port(sw);

	for (port = p; port < sw->mib_port_cnt; port++) {
		port = chk_last_port(sw, port);
		port_get_def_vid(sw, port, &info->port_cfg[port].vid);
		port_r(sw, port, P_MIRROR_CTRL, &data);
		data &= PORT_VLAN_MEMBERSHIP;
		info->port_cfg[port].member = data;
		info->port_cfg[port].vid_member = data;

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
	int p;
	struct ksz_port_info *info;

	for (p = 0; p < sw->mib_port_cnt; p++) {
		info = &sw->port_info[p];
#if 0
		inc_mac_addr(info->mac_addr, mac_addr, p + 1);
#else
		inc_mac_addr(info->mac_addr, mac_addr, 0);
#endif
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

#define STP_ENTRY			0
#define BROADCAST_ENTRY			1
#define BRIDGE_ADDR_ENTRY		2
#define IPV6_ADDR_ENTRY			3

/**
 * sw_set_global_ctrl - set switch global control
 * @sw:		The switch instance.
 *
 * This routine sets the global control of the switch function.
 */
static void sw_set_global_ctrl(struct ksz_sw *sw)
{
	SW_D data;

	/* Enable switch MII flow control. */
	data = SW_R(sw, S_REPLACE_VID_CTRL);
	data |= SW_FLOW_CTRL;

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

#ifdef CONFIG_KSZ_HSR
	if (sw->features & HSR_HW) {
		int n;

		for (n = 0; n < sw->eth_cnt; n++) {
			if (sw->eth_maps[n].proto & HSR_HW) {
				if (sw->netdev[n]) {
					sw->ops->release(sw);
					sw->ops->cfg_mac(sw, BRIDGE_ADDR_ENTRY,
						sw->netdev[n]->dev_addr,
						sw->HOST_MASK, false, false, 0);
					sw->ops->acquire(sw);
				}
				break;
			}
		}
	}
#endif
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
		if (sw->features & STP_SUPPORT)
			break;
		if ((sw->features & (SW_VLAN_DEV | SKIP_FIRST_PORT)) &&
		    port != sw->HOST_PORT)
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
	int c;
	int port;
	u8 member;
	struct ksz_sw_info *info = sw->info;
	int p = get_first_port(sw);

	for (c = 0, port = p; c < sw->port_cnt; c++, port++) {
		if (STP_STATE_FORWARDING == info->port_cfg[port].stp_state)
			member = sw->HOST_MASK | info->member[0];
		else if (STP_STATE_DISABLED == info->port_cfg[port].stp_state)
			member = 0;
		else
			member = sw->HOST_MASK | (1 << port);
		if (member != info->port_cfg[port].member)
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
#ifdef CONFIG_KSZ_HSR
#include "ksz_hsr.c"
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
#ifdef DBG_LINK
	printk(KERN_INFO "pause: %d, %d; %02x %02x\n",
		rx, tx, local, remote);
#endif
	return flow;
}  /* sw_determine_flow_ctrl */

static int port_chk_force_link(struct ksz_sw *sw, int p, SW_D local,
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
		info = &sw->port_info[p];
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
		data = remote;

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

#if 1
		/* Bit 7 fluctuates in port 0. */
		if (0 == p)
			local &= ~PORT_AUTO_NEG_DISABLE;
#endif

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
	if (change && port->first_port < SWITCH_PORT_NUM)
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
	SW_D data;
	SW_D local;
	SW_D status;
	int i;
	int p;

	for (i = 0, p = port->first_port; i < port->port_cnt; i++, p++) {
		info = &sw->port_info[p];
		info->own_flow_ctrl = port->flow_ctrl;
		info->own_duplex = port->duplex;
		info->own_speed = port->speed;

		port_r(sw, p, P_LOCAL_CTRL, &local);
		port_r(sw, p, P_LINK_STATUS, &status);

		adv = 0;
		if (status & PORT_STAT_LINK_GOOD) {
			adv = local;
		}

		local &= ~PORT_AUTO_NEG_DISABLE;
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
		if (local != adv) {
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
	int i;
	int p;

	for (i = 0, p = port->first_port; i < port->port_cnt; i++, p++) {
		info = &sw->port_info[p];
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
	int c;
	int port;
	int state = STP_STATE_FORWARDING;
	int p = get_first_port(sw);

	if (sw->features & DSA_SUPPORT)
		state = STP_STATE_SIMPLE;

	/* Manually change default membership when not all ports are used. */
	if (sw->features & SKIP_FIRST_PORT) {
		for (port = p; port < sw->mib_port_cnt; port++) {
			port = chk_last_port(sw, port);
			sw->info->port_cfg[port].vid_member = sw->PORT_MASK;
		}
		port_set_stp_state(sw, 0, STP_STATE_DISABLED);
		sw_cfg_port_base_vlan(sw, sw->HOST_PORT, sw->PORT_MASK);
	}
	if (sw->dev_count > 1 || (sw->features & DSA_SUPPORT)) {
		u8 member;

		for (c = 0, port = p; c < sw->port_cnt; c++, port++) {
			member = (1 << port);
			if (sw->features & SW_VLAN_DEV) {
				int q;

				for (q = 0; q < sw->eth_cnt; q++)
					if (sw->eth_maps[q].port <= port &&
					    port < sw->eth_maps[q].port +
					    sw->eth_maps[q].cnt) {
						member = sw->eth_maps[q].mask;
						break;
					}
			}
			sw->info->port_cfg[port].vid_member = member;
		}
	}
	for (c = 0, port = p; c < sw->port_cnt; c++, port++) {
		if (sw->dev_count > 1)
			port_set_stp_state(sw, port, STP_STATE_DISABLED);
		else
			port_set_stp_state(sw, port, state);
	}
	if (sw->dev_count > 1)
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
	sw_w8(sw, REG_CHIP_ID1, SW_START);
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
	int c;
	int port;
	int p = get_first_port(sw);

	sw_set_global_ctrl(sw);
	for (c = 0, port = p; c < sw->port_cnt; c++, port++) {
		SW_D data;

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

	sw->info->multi_sys = MULTI_MAC_TABLE_ENTRIES;
	sw->info->multi_net = SWITCH_MAC_TABLE_ENTRIES;
	if (sw->features & STP_SUPPORT) {
		sw_setup_stp(sw);
	}
}  /* sw_setup */

static inline void sw_reset(struct ksz_sw *sw)
{
	sw->reg->w8(sw, REG_POWER_MANAGEMENT_1,
		SW_SOFTWARE_POWER_DOWN << SW_POWER_MANAGEMENT_MODE_S);
	sw->reg->w8(sw, REG_POWER_MANAGEMENT_1, 0);
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

#define MIB_RX_LO_PRIO			0x00
#define MIB_RX_HI_PRIO			0x01
#define MIB_RX_UNDERSIZE		0x02
#define MIB_RX_FRAGMENT			0x03
#define MIB_RX_OVERSIZE			0x04
#define MIB_RX_JABBER			0x05
#define MIB_RX_SYMBOL_ERR		0x06
#define MIB_RX_CRC_ERR			0x07
#define MIB_RX_ALIGNMENT_ERR		0x08
#define MIB_RX_CTRL_8808		0x09
#define MIB_RX_PAUSE			0x0A
#define MIB_RX_BROADCAST		0x0B
#define MIB_RX_MULTICAST		0x0C
#define MIB_RX_UNICAST			0x0D
#define MIB_RX_OCTET_64			0x0E
#define MIB_RX_OCTET_65_127		0x0F
#define MIB_RX_OCTET_128_255		0x10
#define MIB_RX_OCTET_256_511		0x11
#define MIB_RX_OCTET_512_1023		0x12
#define MIB_RX_OCTET_1024_1522		0x13
#define MIB_TX_LO_PRIO			0x14
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

#define MIB_RX_DROPS			0x20
#define MIB_TX_DROPS			0x21

static struct {
	char string[20];
} mib_names[TOTAL_SWITCH_COUNTER_NUM] = {
	{ "rx           " },
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

	{ "tx           " },
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

	{ "rx_discards" },
	{ "tx_discards" },
};

static struct {
	int rx;
	int tx;
} mib_display[TOTAL_SWITCH_COUNTER_NUM / 2] = {
	{ MIB_RX_LO_PRIO, MIB_TX_LO_PRIO },
	{ MIB_RX_HI_PRIO, MIB_TX_HI_PRIO },
	{ MIB_RX_PAUSE, MIB_TX_PAUSE },
	{ MIB_RX_BROADCAST, MIB_TX_BROADCAST },
	{ MIB_RX_MULTICAST, MIB_TX_MULTICAST },
	{ MIB_RX_UNICAST, MIB_TX_UNICAST },
	{ MIB_RX_OCTET_64, MIB_RX_OCTET_65_127 },
	{ MIB_RX_OCTET_128_255, MIB_RX_OCTET_256_511 },
	{ MIB_RX_OCTET_512_1023, MIB_RX_OCTET_1024_1522 },
	{ MIB_RX_UNDERSIZE, MIB_RX_OVERSIZE },
	{ MIB_RX_FRAGMENT, MIB_RX_JABBER },
	{ MIB_RX_SYMBOL_ERR, MIB_RX_CRC_ERR },
	{ MIB_RX_ALIGNMENT_ERR, MIB_RX_CTRL_8808 },
	{ MIB_TX_LATE_COLLISION, MIB_TX_DEFERRED },
	{ MIB_TX_TOTAL_COLLISION, MIB_TX_EXCESS_COLLISION },
	{ MIB_TX_SINGLE_COLLISION, MIB_TX_MULTI_COLLISION },
	{ MIB_RX_DROPS, MIB_TX_DROPS },
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

		for (j = 0; j < 2; j++) {
			if (sw->port_mib[mib].rate[j].peak) {
				u32 num;
				u32 frac;

				num = sw->port_mib[mib].rate[j].peak / 10;
				frac = sw->port_mib[mib].rate[j].peak % 10;
				if (buf)
					len += sprintf(buf + len,
						"%d:%d=%u.%u\n", mib, j,
						num, frac);
				else
					printk(KERN_INFO
						"%d:%d=%u.%u\n", mib, j,
						num, frac);
				sw->port_mib[mib].rate[j].peak = 0;
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
		len = display_sw_info(sw->mib_port_cnt, buf, len);
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
		int ports = sw->port_cnt;

		if (sw->eth_cnt > 1)
			ports = sw->eth_maps[0].cnt + 0;
		else if (sw->port_cnt == sw->mib_port_cnt)
			ports = sw->mib_port_cnt - 1;
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
#if 0
		len += sprintf(buf + len, "%u\n",
			!!(sw->features & STP_SUPPORT));
#else
		len += sprintf(buf + len, "0\n");
#endif
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
#ifdef CONFIG_KSZ_HSR
		len += sprintf(buf + len, "\t%08x = HSR support\n",
			HSR_HW);
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
		chk = sw_chk(sw, REG_SW_CTRL_2, SW_LEGAL_PACKET);
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
			sw->mib_port_cnt);
		type = SHOW_HELP_HEX;
		break;
	case PROC_SET_FORWARD_UNKNOWN_MULTICAST:
		chk = sw_chk_unk_dest(sw, REG_SW_UNK_MCAST_CTRL);
		break;
	case PROC_SET_FORWARD_UNKNOWN_MULTICAST_PORTS:
		chk = sw_chk_unk_def_port(sw, REG_SW_UNK_MCAST_CTRL,
			sw->mib_port_cnt);
		type = SHOW_HELP_HEX;
		break;
	case PROC_SET_FORWARD_UNKNOWN_VID:
		chk = sw_chk_unk_dest(sw, REG_SW_UNK_VID_CTRL);
		break;
	case PROC_SET_FORWARD_UNKNOWN_VID_PORTS:
		chk = sw_chk_unk_def_port(sw, REG_SW_UNK_VID_CTRL,
			sw->mib_port_cnt);
		type = SHOW_HELP_HEX;
		break;
	case PROC_SET_FORWARD_UNKNOWN_IP_MULTICAST:
		chk = sw_chk_unk_dest(sw, REG_SW_UNK_IP_MCAST_CTRL);
		break;
	case PROC_SET_FORWARD_UNKNOWN_IP_MULTICAST_PORTS:
		chk = sw_chk_unk_def_port(sw, REG_SW_UNK_IP_MCAST_CTRL,
			sw->mib_port_cnt);
		type = SHOW_HELP_HEX;
		break;
	case PROC_SET_SELF_ADDR_FILTER:
		chk = sw_chk_self_filter(sw);
		break;
	case PROC_SET_INS_TAG:
		chk = sw_chk_ins_tag(sw);
		break;
	case PROC_SET_PASS_ALL:
		chk = sw_chk(sw, REG_SW_CTRL_1, SW_PASS_ALL);
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
			int c;
			int i;
			int enabled;
			int p = get_first_port(sw);

			if (num & VLAN_PORT_REMOVE_TAG) {
				enabled = true;
				sw->overrides |= TAG_REMOVE;
			} else {
				enabled = false;
				sw->overrides &= ~TAG_REMOVE;
			}
			for (c = 0, i = p; c < sw->port_cnt; c++, i++) {
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
		sw_cfg(sw, REG_SW_CTRL_2, SW_LEGAL_PACKET, num);
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
	case PROC_SET_PASS_ALL:
		sw_cfg(sw, REG_SW_CTRL_1, SW_PASS_ALL, num);
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
	int chk = 0;
	int type = SHOW_HELP_NONE;
	char note[40];

	note[0] = '\0';
	port += sw->ops->get_first_port(sw);
	port_cfg = &sw->info->port_cfg[port];
	port_info = &sw->port_info[port];
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
		chk = port_cfg->rx_rate[0];
		if (sw->verbose)
			strcpy(note, " (bps)");
		type = SHOW_HELP_SPECIAL;
		break;
	case PROC_SET_RX_P1_RATE:
		chk = port_cfg->rx_rate[1];
		if (sw->verbose)
			strcpy(note, " (bps)");
		type = SHOW_HELP_SPECIAL;
		break;
	case PROC_SET_RX_P2_RATE:
		chk = port_cfg->rx_rate[2];
		if (sw->verbose)
			strcpy(note, " (bps)");
		type = SHOW_HELP_SPECIAL;
		break;
	case PROC_SET_RX_P3_RATE:
		chk = port_cfg->rx_rate[3];
		if (sw->verbose)
			strcpy(note, " (bps)");
		type = SHOW_HELP_SPECIAL;
		break;
	case PROC_SET_TX_Q0_RATE:
		chk = port_cfg->tx_rate[0];
		if (sw->verbose)
			strcpy(note, " (bps)");
		type = SHOW_HELP_SPECIAL;
		break;
	case PROC_SET_TX_Q1_RATE:
		chk = port_cfg->tx_rate[1];
		if (sw->verbose)
			strcpy(note, " (bps)");
		type = SHOW_HELP_SPECIAL;
		break;
	case PROC_SET_TX_Q2_RATE:
		chk = port_cfg->tx_rate[2];
		if (sw->verbose)
			strcpy(note, " (bps)");
		type = SHOW_HELP_SPECIAL;
		break;
	case PROC_SET_TX_Q3_RATE:
		chk = port_cfg->tx_rate[3];
		if (sw->verbose)
			strcpy(note, " (bps)");
		type = SHOW_HELP_SPECIAL;
		break;
	}
	return sysfs_show(len, buf, type, chk, note, sw->verbose);
}  /* sysfs_port_read */

static ssize_t sysfs_port_read_hw(struct ksz_sw *sw, int proc_num, int port,
	ssize_t len, char *buf)
{
	int chk = 0;
	int type = SHOW_HELP_ON_OFF;
	char note[40];

	note[0] = '\0';
	port += sw->ops->get_first_port(sw);
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
	}
	return sysfs_show(len, buf, type, chk, note, sw->verbose);
}  /* sysfs_port_read_hw */

static int sysfs_port_write(struct ksz_sw *sw, int proc_num, int port,
	int num, const char *buf)
{
	int processed = true;

	port += sw->ops->get_first_port(sw);
	switch (proc_num) {
	case PROC_SET_PORT_DUPLEX:
	case PROC_SET_PORT_SPEED:
	{
		struct ksz_port phy_port;
		struct ksz_port_info *port_info = &sw->port_info[port];

		if ((PROC_SET_PORT_DUPLEX == proc_num && num > 2) ||
		    (PROC_SET_PORT_SPEED == proc_num &&
		    num != 0 && num != 10 && num != 100))
			break;

		phy_port.sw = sw;
		phy_port.port_cnt = 1;
		phy_port.first_port = port;
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

static void sw_from_designated(struct ksz_sw *sw, int p)
{
#ifdef CONFIG_KSZ_MRP
	if (sw->features & MRP_SUPPORT) {
		struct mrp_info *mrp = &sw->mrp;

		mrp->ops->from_designated(mrp, p);
	}
#endif
}  /* sw_from_designated */

static void sw_to_designated(struct ksz_sw *sw, int p)
{
#ifdef CONFIG_KSZ_MRP
	if (sw->features & MRP_SUPPORT) {
		struct mrp_info *mrp = &sw->mrp;

		mrp->ops->to_designated(mrp, p);
	}
#endif
}  /* sw_to_designated */

static void sw_tc_detected(struct ksz_sw *sw, int p)
{
#ifdef CONFIG_KSZ_MRP
	if (sw->features & MRP_SUPPORT) {
		struct mrp_info *mrp = &sw->mrp;

		mrp->ops->tc_detected(mrp, p);
	}
#endif
}  /* sw_tc_detected */

static int sw_get_tcDetected(struct ksz_sw *sw, int p)
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

#define FAMILY_ID_88			0x95
#define CHIP_ID_8895			0x40
#define CHIP_ID_8895R			0x60
#define CHIP_ID_8864			0x90

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
	switch (i) {
	case FAMILY_ID_88:
		strcat(name, "88");
		switch (j) {
		case CHIP_ID_8895:
		case CHIP_ID_8895R:
			strcat(name, "95");
			break;
		case CHIP_ID_8864:
			strcat(name, "64");
			break;
		}
		break;
	}
	if (name[0] && !name[2])
		strcat(name, "xx");
	return id;
}  /* sw_get_id */

static void sw_cfg_tail_tag(struct ksz_sw *sw, int enable)
{
	sw_cfg(sw, S_TAIL_TAG_CTRL, SW_TAIL_TAG_ENABLE, enable);
}

static int sw_port_to_phy_addr(struct ksz_sw *sw, int p)
{
	p += sw->ops->get_first_port(sw);
	if (0 <= p && p <= sw->mib_port_cnt)
		return p;
	return -1;
}

static void sw_cfg_each_port(struct ksz_sw *sw, int p, int cpu)
{
	if (cpu)
		p = sw->HOST_PORT;
	else {
		p += sw->ops->get_first_port(sw);
		if (p > sw->mib_port_cnt)
			return;
		sw->info->port_cfg[p].vid_member = sw->HOST_MASK | (1 << p);
	}
	port_set_stp_state(sw, p, STP_STATE_SIMPLE);
}

static void sw_set_port_addr(struct ksz_sw *sw, int p, u8 *addr)
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
	struct net_device *dev;
	int index = -1;
	int vid = 0;
#ifdef CONFIG_NET_DSA_TAG_TAIL
	u32 org_len = *len;
#endif

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

#ifdef CONFIG_NET_DSA_TAG_TAIL
	/* DSA has its function to read the tail tag. */
	if (sw->features & DSA_SUPPORT) {
		*len = org_len;
		return sw->netdev[0];
	}
#endif

	/* Determine network device from VLAN id. */
	if (index < 0) {
		struct vlan_ethhdr *vlan = (struct vlan_ethhdr *) data;

		index = 0;
		if (vlan->h_vlan_proto == htons(ETH_P_8021Q)) {
			u16 vlan_tci = ntohs(vlan->h_vlan_TCI);

			vid = vlan_tci & VLAN_VID_MASK;
		}
		if (vid && (sw->features & SW_VLAN_DEV)) {
			int p;

			for (p = 0; p < sw->eth_cnt; p++) {
				if (vid == sw->eth_maps[p].vlan) {
					*port = sw->eth_maps[p].port;
					index = sw->info->port_cfg[*port].index;
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

#ifdef CONFIG_KSZ_STP
	if (sw->features & STP_SUPPORT) {
		ret = stp_rcv(&sw->info->rstp, skb, port);
		if (!ret)
			return ret;
	}
#endif
#ifdef CONFIG_KSZ_HSR
	if (sw->features & HSR_HW) {
		ret = hsr_rcv(&sw->info->hsr, skb, port);

		/* It is an HSR frame or consumed. */
		if (ret < 2)
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

#ifdef CONFIG_KSZ_HSR
	if (sw->features & HSR_HW)
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
#ifdef CONFIG_KSZ_HSR
	if (sw->features & HSR_HW)
		header = HSR_HLEN;
#endif
	if (sw->features & SW_VLAN_DEV)
		if (header < VLAN_HLEN)
			header = VLAN_HLEN;
	mtu += header;
	return mtu;
}  /* sw_get_mtu */

static int sw_get_tx_len(struct ksz_sw *sw, struct sk_buff *skb, int port,
	int *header)
{
	int len = skb->len;
	int hlen = 0;

	if (sw->features & SW_VLAN_DEV)
		hlen = VLAN_HLEN;
#ifdef CONFIG_KSZ_HSR
	do {
		int i;

		i = sw->info->port_cfg[port].index;
		if (sw->eth_cnt && (sw->eth_maps[i].proto & HSR_HW))
			hlen = HSR_HLEN;
	} while (0);
#endif
	*header += hlen;
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
	else if (ports & 0x80000000) {
		ports &= ~0x80000000;
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

static int sw_get_phys_port(struct ksz_sw *sw, int port)
{
	int p = sw->ops->get_first_port(sw);

	port += p;
	return port;
}  /* sw_get_phy_port */

static int sw_get_virt_port(struct ksz_sw *sw, int port)
{
	int p = sw->ops->get_first_port(sw);

	port -= p;
	return port;
}  /* sw_get_virt_port */

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

static struct sk_buff *sw_ins_vlan(struct ksz_sw *sw, int port,
	struct sk_buff *skb)
{
#ifdef CONFIG_KSZ_HSR
	do {
		int i = sw->info->port_cfg[port].index;

		if (sw->eth_cnt && (sw->eth_maps[i].proto & HSR_HW))
			return skb;
	} while (0);
#endif

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

#ifdef CONFIG_KSZ_HSR
static struct sk_buff *sw_ins_hsr(struct ksz_sw *sw, int port,
	struct sk_buff *skb, u8 *ports)
{
	int i = sw->info->port_cfg[port].index;

	if (sw->eth_cnt && (sw->eth_maps[i].proto & HSR_HW)) {
		struct ksz_hsr_info *info = &sw->info->hsr;
		struct hsr_port *from =
			hsr_port_get_hsr(&info->hsr, HSR_PT_MASTER);

		if (!hsr_forward_skb(skb, from))
			return NULL;
		*ports = info->member;
	}
	return skb;
}  /* sw_ins_hsr */
#endif

static struct sk_buff *sw_check_skb(struct ksz_sw *sw, struct sk_buff *skb,
	struct ksz_port *priv, void *ptr,
	int (*update_msg)(u8 *data, u32 port, u32 overrides))
{
	int len;
	int port;
	u8 dest;
	struct sk_buff *org_skb;
	int update_dst = (sw->overrides & TAIL_TAGGING);

	if (!update_dst)
		return sw_ins_vlan(sw, priv->first_port, skb);

#ifdef CONFIG_NET_DSA_TAG_TAIL
	if (skb->protocol == htons(ETH_P_TRAILER))
		return skb;
#endif
#ifdef CONFIG_KSZ_STP
	if (skb->protocol == htons(STP_TAG_TYPE))
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
		int i = sw->info->port_cfg[priv->first_port].index;
		u32 features = sw->features;

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
	if (port)
		dest = 1 << (port - 1);
#ifdef CONFIG_KSZ_HSR
	skb = sw_ins_hsr(sw, priv->first_port, skb, &dest);
	if (!skb)
		return NULL;
#endif

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
		skb->data[len] = dest;
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
		sw->tx_pad[sw->tx_start] = dest;
		if (!sw->tx_pad[sw->tx_start])
			sw->tx_pad[sw->tx_start] = TAIL_TAG_LOOKUP;
		skb_append_datato_frags(sk, skb, add_frag, sw->tx_pad, len);
	}
	skb = sw_ins_vlan(sw, priv->first_port, skb);
	return skb;
}  /* sw_check_skb */

static struct sk_buff *sw_check_tx(struct ksz_sw *sw, struct net_device *dev,
	struct sk_buff *skb, struct ksz_port *priv)
{
	void *ptr = NULL;
	int (*update_msg)(u8 *data, u32 port, u32 overrides) = NULL;

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
	int need_vlan = false;

	sw->ops->acquire(sw);
	sw_setup(sw);
	sw_enable(sw);
	sw_set_addr(sw, addr);
#if 0
	if (1 == sw->dev_count)
		sw_cfg_self_filter(sw, true);
#endif
#ifdef CONFIG_KSZ_HSR
	if (sw->features & HSR_HW)
		need_tail_tag = true;
#endif
	if (sw->dev_count > 1 && !(sw->features & SW_VLAN_DEV))
		need_tail_tag = true;
	if (sw->features & VLAN_PORT) {
		if (sw->features & VLAN_PORT_REMOVE_TAG) {
			int c;
			int i;
			int p = get_first_port(sw);

			for (c = 0, i = p; c < sw->port_cnt; c++, i++) {
				port_cfg_rmv_tag(sw, i, true);
			}
			sw->overrides |= TAG_REMOVE;
		}
		if (sw->features & VLAN_PORT_TAGGING)
			need_tail_tag = true;
	}
	if (sw->features & SW_VLAN_DEV) {
		struct ksz_vlan_table entry;
		int i;
		int p;
		int q;

		memset(&entry, 0, sizeof(struct ksz_vlan_table));
		for (p = 0; p < sw->eth_cnt; p++) {

			/* Not really using VLAN. */
			if (1 == sw->eth_maps[p].vlan)
				continue;
			sw->ops->release(sw);

			/*
			 * Setting FID allows same MAC address in different
			 * VLANs.
			 */
			entry.fid = sw->eth_maps[p].vlan & (FID_ENTRIES - 1);
			entry.member = sw->HOST_MASK | sw->eth_maps[p].mask;
			entry.valid = 1;
			sw_w_vlan_table(sw, sw->eth_maps[p].vlan, &entry);
			sw->ops->acquire(sw);
			for (i = 0, q = sw->eth_maps[p].port;
			     i < sw->eth_maps[p].cnt; i++, q++) {
				sw_cfg_def_vid(sw, q, sw->eth_maps[p].vlan);
				port_cfg_rmv_tag(sw, q, true);
			}
		}

		/* Use VLAN tag to determine the network device. */
		if (!need_tail_tag)
			port_cfg_ins_tag(sw, sw->HOST_PORT, true);
		need_vlan = true;
	}
	if (sw->features & (STP_SUPPORT | DSA_SUPPORT))
		need_tail_tag = true;
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
	int i;
	int p = get_first_port(sw);

	for (i = p; i < sw->mib_port_cnt; i++) {
		i = chk_last_port(sw, i);
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
	int i;
	int p;
	struct ksz_port_info *info;

	for (i = 0, p = port->first_port; i < port->port_cnt; i++, p++) {
		info = &sw->port_info[p];
		/*
		 * Initialize to invalid value so that link detection
		 * is done.
		 */
		info->link = 0xFF;
		info->state = media_unknown;
		info->report = true;
	}

	sw->ops->acquire(sw);

	/* Need to open the port in multiple device interfaces mode. */
	if (sw->dev_count > 1 && (!sw->dev_offset || dev != sw->netdev[0])) {
		*state = STP_STATE_SIMPLE;
		if (sw->features & SW_VLAN_DEV) {
			i = sw->info->port_cfg[port->first_port].index;
			if (!(sw->eth_maps[i].proto & HSR_HW))
				*state = STP_STATE_FORWARDING;
		}
		for (i = 0, p = port->first_port; i < port->port_cnt;
		     i++, p++) {
			port_set_stp_state(sw, p, *state);
		}
	}

	sw->phy_intr = sw->PORT_MASK;
	if (port->force_link)
		port_force_link_speed(port);
	else
		port_set_link_speed(port);
	port_get_link_speed(port);
	sw->phy_intr = 0;
	sw->ops->release(sw);
	if (sw->dev_offset && dev == sw->netdev[0]) {
		struct ksz_port *sw_port = NULL;
		struct sw_priv *hw_priv = container_of(sw, struct sw_priv, sw);

		if (sw->net_ops->get_priv_port)
			sw_port = sw->net_ops->get_priv_port(dev);
		if (sw_port)
			hw_priv->phy_id = sw_port->linked->phy_id;
	}
	for (i = 0; i < sw->eth_cnt; i++) {
		if (dev != sw->netdev[i])
			continue;
#ifdef CONFIG_KSZ_HSR
		if (sw->eth_maps[i].proto & HSR_HW) {
			struct ksz_hsr_info *info = &sw->info->hsr;

			if (info->ports[0] == port->first_port)
				prep_hsr(info, dev, dev->dev_addr);
		}
#endif
	}
}  /* sw_open_port */

static void sw_close_port(struct ksz_sw *sw, struct net_device *dev,
	struct ksz_port *port)
{
	int i;

	/* Need to shut the port manually in multiple device interfaces mode. */
	if (sw->dev_count > 1 && (!sw->dev_offset || dev != sw->netdev[0])) {
		int p;

		sw->ops->acquire(sw);
		for (i = 0, p = port->first_port; i < port->port_cnt;
		     i++, p++) {
			if (p == sw->HOST_PORT)
				continue;
			port_set_stp_state(sw, p, STP_STATE_DISABLED);
		}
		sw->ops->release(sw);
	}
	for (i = 0; i < sw->eth_cnt; i++) {
		if (dev != sw->netdev[i])
			continue;
#ifdef CONFIG_KSZ_HSR
		if (sw->eth_maps[i].proto & HSR_HW) {
			struct ksz_hsr_info *info = &sw->info->hsr;

			if (info->ports[0] == port->first_port)
				stop_hsr(info);
		}
#endif
	}
}  /* sw_close_port */

static void sw_open(struct ksz_sw *sw)
{
	/* Timer may already be started by the SPI device. */
	if (!sw->monitor_timer_info->max)
		ksz_start_timer(sw->monitor_timer_info,
			sw->monitor_timer_info->period);
}  /* sw_open */

static void sw_close(struct ksz_sw *sw)
{
	ksz_stop_timer(sw->monitor_timer_info);
	cancel_delayed_work_sync(sw->link_read);
}  /* sw_close */

static u8 sw_set_mac_addr(struct ksz_sw *sw, struct net_device *dev,
	u8 promiscuous, int port)
{

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

			/* All addresses the same. */
			if (i == dev_count) {
				sw->features &= ~DIFF_MAC_ADDR;
				--promiscuous;
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

#if 0
#define USE_HSR
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
#if defined(USE_HSR)
static int multi_dev = 1;
#else
static int multi_dev;
#endif

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

#if defined(USE_HSR)
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

#if defined(USE_HSR)
static char *eth1_proto = "hsr";
#endif
#if !defined(USE_HSR)
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

static void sw_setup_zone(struct ksz_sw *sw)
{
	int c;
	int f;
	int limit;
	int m;
	int n;
	int p;
	int q;
	int w;
	int *v;
	char **s;
	uint features;
	uint used = 0;
	int last_vlan = 0;
	int ports = sw->PORT_MASK;
	int b = get_first_port(sw);

#ifdef DEBUG
	sw->verbose = 1;
#endif
	if (sw->multi_dev > 2)
		goto setup_next;
	for (p = 0; p < SWITCH_PORT_NUM - 1; p++) {
		v = eth_ports[p];

		/* No more port setting. */
		if (!v || !*v)
			break;
		m = *v;
		m <<= b;

		/* Find out how the ports are to be used. */
		limit = 0;
		w = last_vlan;
		features = 0;
		s = eth_proto[p];
		if (!strcmp(*s, "hsr")) {
#ifdef CONFIG_KSZ_HSR
			features = HSR_HW;
			features |= VLAN_PORT;
			sw->features |= VLAN_PORT | VLAN_PORT_TAGGING;
#endif
			limit = 2;
			w = 1;
		}

		v = eth_vlans[p];
		if (!w && (!v || !*v))
			break;
		if (*v)
			w = *v;

		for (q = 0; q < p; q++) {
			m &= ~sw->eth_maps[q].mask;
			if (w > 1 && w == sw->eth_maps[q].vlan)
				w = last_vlan + 1;
		}
		c = 0;
		f = -1;
		for (n = 0, q = b; n < sw->port_cnt; n++, q++) {
			if (m & (1 << q)) {
				if (f < 0)
					f = q;
				++c;

				/* Limit to certain ports. */
				if (limit && c >= limit) {
					if (!(used & features)) {
						used |= features;
						++q;
						break;
					}
					features = 0;
				}
			} else if (f >= 0)
				break;
		}
		if (!c)
			continue;
		m &= (1 << q) - 1;
		sw->eth_maps[p].cnt = c;
		sw->eth_maps[p].mask = m;
		sw->eth_maps[p].port = f;
		sw->eth_maps[p].phy_id = f + 1;
		sw->eth_maps[p].vlan = w & (4096 - 1);
		sw->eth_maps[p].proto = features;
#ifdef CONFIG_KSZ_HSR
		if (features & HSR_HW) {
			struct ksz_hsr_info *hsr = &sw->info->hsr;

			hsr->ports[0] = f++;
			if (f == sw->HOST_PORT)
				f++;
			hsr->ports[1] = f;
			hsr->member = (1 << hsr->ports[0]) |
				(1 << hsr->ports[1]);
		}
#endif
		if (last_vlan < w)
			last_vlan = w;
		ports &= ~m;
	}

	/* No VLAN devices specified. */
	if (!p)
		goto setup_next;

	/* Not all ports are used. */
	ports &= ~sw->HOST_MASK;
	if (sw->multi_dev != 1)
		ports = 0;
	features = 0;
	while (ports) {
		m = ports;
		c = 0;
		f = -1;
		for (n = 0, q = b; n < sw->port_cnt; n++, q++) {
			if (m & (1 << q)) {
				if (f < 0)
					f = q;
				++c;
			} else if (f >= 0)
				break;
		}
		m &= (1 << q) - 1;
		sw->eth_maps[p].cnt = c;
		sw->eth_maps[p].mask = m;
		sw->eth_maps[p].port = f;
		sw->eth_maps[p].phy_id = f + 1;
		sw->eth_maps[p].vlan = ++last_vlan & (4096 - 1);
		sw->eth_maps[p].proto = features;
		ports &= ~m;
		p++;
	}
	if (p > 1)
		sw->features |= SW_VLAN_DEV;
	sw->eth_cnt = p;
#ifdef CONFIG_KSZ_HSR
	if (used & HSR_HW)
		sw->features |= HSR_HW;
#endif
	for (p = 0; p < sw->eth_cnt; p++) {
		dbg_msg("%d: %d:%d %02x %03x %08x\n",
			p, sw->eth_maps[p].port, sw->eth_maps[p].cnt,
			sw->eth_maps[p].mask, sw->eth_maps[p].vlan,
			sw->eth_maps[p].proto);
	}

setup_next:
	return;
}  /* sw_setup_zone */

static int phy_offset;

static void sw_setup_special(struct ksz_sw *sw, int *port_cnt,
	int *mib_port_cnt, int *dev_cnt)
{
	phy_offset = 0;
	sw->dev_offset = 0;
	sw->phy_offset = 0;
	if (sw->stp) {
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
		if (sw->first_port) {
			(*port_cnt)--;
			(*mib_port_cnt)--;
		}
	} else if (sw->first_port)
		sw->dev_count--;
	if (1 == sw->multi_dev && (sw->features & SW_VLAN_DEV))
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
	for (i = 0; i < sw->dev_count; i++)
		sw->netdev[i] = NULL;
	sw->eth_cnt = 0;
	sw->dev_count = 0;
	sw->dev_offset = 0;
	sw->phy_offset = 0;
}  /* sw_leave_dev */

static int sw_setup_dev(struct ksz_sw *sw, struct net_device *dev,
	char *dev_name, struct ksz_port *port, int i, int port_cnt,
	int mib_port_cnt)
{
	int cnt;
	int p;
	int pi;
	int phy_id;
	u32 features;

	if (!phy_offset)
		phy_offset = sw->phy_offset;

	p = i;
	if (p)
		p -= sw->dev_offset;
	p += sw->first_port;

	if (sw->dev_offset) {
		/*
		 * First device associated with switch has been
		 * created.
		 */
		if (i)
			snprintf(dev->name, IFNAMSIZ, "%s.10%%d", dev_name);
		else {
			port_cnt = SWITCH_PORT_NUM;
			mib_port_cnt = SWITCH_PORT_NUM;
			if (sw->first_port) {
				port_cnt--;
				mib_port_cnt--;
			}
		}
	}

	if (1 == sw->multi_dev && (sw->features & SW_VLAN_DEV)) {
		port_cnt = sw->eth_maps[i].cnt;
		p = sw->eth_maps[i].port;
		mib_port_cnt = port_cnt;
	}
#ifdef CONFIG_KSZ_HSR
	if (sw->eth_cnt && (sw->eth_maps[i].proto & HSR_HW)) {
		port_cnt = sw->eth_maps[i].cnt;
		p = sw->eth_maps[i].port;
		mib_port_cnt = port_cnt;
		setup_hsr(&sw->info->hsr, dev);
		dev->hard_header_len += HSR_HLEN;
	}
#endif

	port->port_cnt = port_cnt;
	port->mib_port_cnt = mib_port_cnt;
	port->first_port = p;
	port->flow_ctrl = PHY_FLOW_CTRL;

#ifdef CONFIG_KSZ_STP
	if (sw->features & STP_SUPPORT)
		prep_stp_mcast(dev);
#endif

	/* Point to port under netdev. */
	if (phy_offset)
		phy_id = port->first_port + phy_offset;
	else
		phy_id = 0;

	/* Replace virtual port with one from network device. */
	do {
		struct phy_device *phydev;
		struct phy_priv *priv;
		struct sw_priv *hw_priv = container_of(sw, struct sw_priv, sw);

		phydev = hw_priv->bus->phy_map[phy_id];
		priv = phydev->priv;
		priv->port = port;
	} while (0);
	if (!phy_offset)
		phy_offset = 1;

	port->sw = sw;
	port->linked = &sw->port_info[port->first_port];

	for (cnt = 0, pi = p; cnt < port_cnt; cnt++, pi++) {
		sw->port_info[pi].state = media_disconnected;
		sw->info->port_cfg[pi].index = i;
	}
	sw->netdev[i] = dev;
	if (sw->dev_count > 1 && i && !(sw->features & DIFF_MAC_ADDR)) {
		if (memcmp(dev->dev_addr, sw->netdev[0]->dev_addr, ETH_ALEN))
			sw->features |= DIFF_MAC_ADDR;
	}

	INIT_WORK(&port->link_update, link_update_work);
	features = sw->features;
	if (sw->features & SW_VLAN_DEV)
		features = sw->eth_maps[i].proto;

#ifndef CONFIG_NET_DSA_TAG_TAIL
	if (features & VLAN_PORT)
		dev->features |= NETIF_F_HW_VLAN_CTAG_FILTER;
#endif

	/* Needed for inserting VLAN tag. */
	if (sw->features & SW_VLAN_DEV)
		dev->hard_header_len += VLAN_HLEN;

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
	.get_phys_port		= sw_get_phys_port,
	.get_virt_port		= sw_get_virt_port,
	.add_vid		= sw_add_vid,
	.kill_vid		= sw_kill_vid,
	.check_tx		= sw_check_tx,
	.rx_dev			= sw_rx_dev,
	.match_pkt		= sw_match_pkt,
	.parent_rx		= sw_parent_rx,
	.port_vlan_rx		= sw_port_vlan_rx,
	.drop_icmp		= sw_drop_icmp,
	.final_skb		= sw_final_skb,
	.drv_rx			= sw_drv_rx,
	.set_multi		= sw_set_multi,

};

static struct ksz_sw_ops sw_ops = {
	.init			= sw_init_dev,
	.exit			= sw_exit_dev,
	.dev_req		= sw_dev_req,

	.get_first_port		= get_first_port,
	.chk_last_port		= chk_last_port,

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

#ifdef CONFIG_KSZ_STP
	.sysfs_stp_read		= sysfs_stp_read,
	.sysfs_stp_write	= sysfs_stp_write,
	.sysfs_stp_port_read	= sysfs_stp_port_read,
	.sysfs_stp_port_write	= sysfs_stp_port_write,
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

