/**
 * Micrel gigabit switch common code
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

/* (288 - 24 - 4) / (8 * 3) */
#define MAX_IBA_MIB_ENTRIES		10

#define READ_MIB_ENTRY_SIZE		2

/* (288 - 24 - 4) / (8 * 6) */
#define MAX_IBA_MAC_ENTRIES		5

/* (288 - 24 - 4) / (8 * 6) */
#define MAX_IBA_VLAN_ENTRIES		5

#define READ_VLAN_ENTRY_SIZE		3
#define WRITE_VLAN_ENTRY_SIZE		4

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
	PROC_SET_DROP_INVALID_VID,
	PROC_SET_MAC_ADDR,
	PROC_SET_MIRROR_MODE,

	PROC_SET_IGMP_SNOOP,
	PROC_SET_IPV6_MLD_SNOOP,
	PROC_SET_IPV6_MLD_OPTION,

	PROC_SET_AGGR_BACKOFF,
	PROC_SET_NO_EXC_DROP,

	PROC_SET_JUMBO_PACKET,
	PROC_SET_LEGAL_PACKET,
	PROC_SET_LENGTH_CHECK,

	PROC_SET_BACK_PRESSURE_MODE,
	PROC_SET_SWITCH_FLOW_CTRL,
	PROC_SET_SWITCH_HALF_DUPLEX,
	PROC_SET_SWITCH_10_MBIT,

	PROC_SET_FAIR_FLOW_CTRL,
	PROC_SET_VLAN_BOUNDARY,
	PROC_SET_DOUBLE_TAG,
	PROC_SET_ISP_TAG,
	PROC_SET_HSR_TAG,
	PROC_SET_MTU,
	PROC_SET_FORWARD_UNKNOWN_UNICAST,
	PROC_SET_UNKNOWN_UNICAST_PORTS,
	PROC_SET_FORWARD_UNKNOWN_MULTICAST,
	PROC_SET_UNKNOWN_MULTICAST_PORTS,
	PROC_SET_FORWARD_UNKNOWN_VID,
	PROC_SET_UNKNOWN_VID_PORTS,

	PROC_SET_PASS_PAUSE,
	PROC_ENABLE_PME,
	PROC_ENABLE_PME_POLARITY,

	PROC_GET_HOST_PORT,
	PROC_GET_PORTS,
	PROC_GET_DEV_START,
	PROC_GET_VLAN_START,
	PROC_GET_STP,

	PROC_SET_STATIC_FID,
	PROC_SET_STATIC_USE_FID,
	PROC_SET_STATIC_OVERRIDE,
	PROC_SET_STATIC_VALID,
	PROC_SET_STATIC_MSTP,
	PROC_SET_STATIC_PRIO,
	PROC_SET_STATIC_SRC,
	PROC_SET_STATIC_DST,
	PROC_SET_STATIC_PORTS,
	PROC_SET_STATIC_MAC_ADDR,
	PROC_SET_STATIC_TYPE,
	PROC_SET_STATIC_INDEX,
	PROC_SET_STATIC_INFO,

	PROC_SET_VLAN_VALID,
	PROC_SET_VLAN_PORTS,
	PROC_SET_VLAN_UNTAG,
	PROC_SET_VLAN_FID,
	PROC_SET_VLAN_MSTP,
	PROC_SET_VLAN_PRIO,
	PROC_SET_VLAN_OPTION,
	PROC_SET_VLAN_VID,
	PROC_SET_VLAN_INFO,

	PROC_SET_NO_COLOR,
	PROC_SET_COLOR_RED,
	PROC_SET_COLOR_YELLOW,
	PROC_SET_COLOR_GREEN,

};

enum {
	PROC_SET_PORT_MIB,

	PROC_SET_DEF_VID,
	PROC_SET_MEMBER,

	PROC_ENABLE_BROADCAST_STORM,
	PROC_ENABLE_DIFFSERV,
	PROC_ENABLE_802_1P,
	PROC_ENABLE_VLAN_PRIO,
	PROC_ENABLE_MAC_PRIO,
	PROC_ENABLE_ACL_PRIO,
	PROC_SET_HIGHEST_PRIO,
	PROC_SET_OR_PRIO,

	PROC_SET_PORT_BASED,

	PROC_SET_DIS_NON_VID,
	PROC_SET_INGRESS,
	PROC_SET_DROP_NON_VLAN,
	PROC_SET_DROP_TAG,
	PROC_SET_REPLACE_VID,
	PROC_SET_REPLACE_PRIO,
	PROC_SET_SRC_ADDR_FILTER,
	PROC_SET_VLAN_LOOKUP_0,

	PROC_SET_MSTP,
	PROC_SET_RX,
	PROC_SET_TX,
	PROC_SET_LEARN,

	PROC_ENABLE_PRIO_QUEUE,

	PROC_ENABLE_PRIO_RATE,
	PROC_SET_LIMIT,
	PROC_SET_LIMIT_PORT_BASED,
	PROC_SET_LIMIT_PACKET_BASED,
	PROC_SET_LIMIT_FLOW_CTRL,
	PROC_SET_LIMIT_CNT_IFG,
	PROC_SET_LIMIT_CNT_PRE,
	PROC_SET_RX_P0_RATE,
	PROC_SET_RX_P1_RATE,
	PROC_SET_RX_P2_RATE,
	PROC_SET_RX_P3_RATE,
	PROC_SET_RX_P4_RATE,
	PROC_SET_RX_P5_RATE,
	PROC_SET_RX_P6_RATE,
	PROC_SET_RX_P7_RATE,
	PROC_SET_TX_Q0_RATE,
	PROC_SET_TX_Q1_RATE,
	PROC_SET_TX_Q2_RATE,
	PROC_SET_TX_Q3_RATE,

	PROC_SET_COLOR_MAP,
	PROC_SET_TC_MAP,

	PROC_SET_MIRROR_PORT,
	PROC_SET_MIRROR_RX,
	PROC_SET_MIRROR_TX,

	PROC_SET_BACK_PRESSURE,
	PROC_SET_FORCE_FLOW_CTRL,
	PROC_SET_PASS_ALL,
	PROC_SET_TAIL_TAG,

	PROC_SET_CUSTOM_VID,
	PROC_SET_SR_1_VID,
	PROC_SET_SR_2_VID,
	PROC_SET_SR_1_TYPE,
	PROC_SET_SR_2_TYPE,
	PROC_SET_PME_CTRL,
	PROC_SET_PME_STATUS,

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

	PROC_SET_P_INDEX,
	PROC_SET_Q_INDEX,

	PROC_SET_POLICE_PACKET_TYPE,
	PROC_SET_NON_DSCP_COLOR,
	PROC_ENABLE_POLICE_DROP_ALL,
	PROC_ENABLE_PORT_BASED_POLICING,
	PROC_ENABLE_COLOR_MARK,
	PROC_ENABLE_COLOR_REMAP,
	PROC_ENABLE_DROP_SRP,
	PROC_ENABLE_COLOR_AWARE,
	PROC_ENABLE_POLICE,

	PROC_SET_Q_CIR,
	PROC_SET_Q_PIR,
	PROC_SET_Q_CBS,
	PROC_SET_Q_PBS,

	PROC_SET_WRED_MAX_THRESHOLD,
	PROC_SET_WRED_MIN_THRESHOLD,
	PROC_SET_WRED_MULTIPLIER,
	PROC_GET_WRED_AVG_SIZE,

	PROC_SET_WRED_Q_MAX_THRESHOLD,
	PROC_SET_WRED_Q_MIN_THRESHOLD,
	PROC_SET_WRED_Q_MULTIPLIER,
	PROC_GET_WRED_Q_AVG_SIZE,

	PROC_SET_WRED_RANDOM_DROP,
	PROC_SET_WRED_DROP_GYR,
	PROC_SET_WRED_DROP_YR,
	PROC_SET_WRED_DROP_R,
	PROC_SET_WRED_DROP_ALL,
	PROC_GET_WRED_PMON,

	PROC_SET_SCHEDULE,
	PROC_SET_SHAPING,
#ifdef MTI_PREEMPT_ENABLE
	PROC_SET_PREEMPT,
#endif
	PROC_SET_TX_RATIO,
	PROC_SET_CREDIT_HI_WATER_MARK,
	PROC_SET_CREDIT_LO_WATER_MARK,
	PROC_SET_CREDIT_INCREMENT,
	PROC_SET_SRP,

	PROC_SET_QM_DROP,
	PROC_SET_QM_BURST_SIZE,
	PROC_SET_QM_RESV_SPACE,
	PROC_SET_QM_HI_WATER_MARK,
	PROC_SET_QM_LO_WATER_MARK,
	PROC_GET_QM_TX_USED,
	PROC_GET_QM_TX_AVAIL,
	PROC_GET_QM_TX_CALCULATED,

	PROC_SET_MMD_ID,
	PROC_SET_MMD_REG,
	PROC_SET_MMD_VAL,

	PROC_GET_RX_FLOW_CTRL,
	PROC_GET_TX_FLOW_CTRL,

	PROC_GET_PORT_DUPLEX,
	PROC_GET_PORT_SPEED,
	PROC_SET_LINK_MD,

};

/* -------------------------------------------------------------------------- */

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

/* Common routines used by both SPI and IBA accesses. */

/**
 * get_mac_table_info - Get MAC table information
 * @mac:	Buffer to store the MAC table entry.
 * @data:	Buffer holding MAC table information.
 *
 * This helper routine retrieves information from MAC table entry data.
 */
static void get_mac_table_info(struct ksz_mac_table *mac, u32 data[])
{
	mac->valid = !!(data[0] & ALU_V_STATIC_VALID);
	mac->src = !!(data[0] & ALU_V_SRC_FILTER);
	mac->dst = !!(data[0] & ALU_V_DST_FILTER);
	mac->prio = (data[0] >> ALU_V_PRIO_AGE_CNT_S) &
		ALU_V_PRIO_AGE_CNT_M;
	mac->mstp = data[0] & ALU_V_MSTP_M;
	mac->override = !!(data[1] & ALU_V_OVERRIDE);
	if (mac->ignore_use_fid)
		mac->use_fid = 1;
	else
		mac->use_fid = !!(data[1] & ALU_V_USE_FID);
	mac->ports = data[1] & ALU_V_PORT_MAP;
	mac->fid = data[2] >> ALU_V_FID_S;
	mac->addr[1] = (u8) data[2];
	mac->addr[0] = (u8)(data[2] >> 8);
	mac->addr[5] = (u8) data[3];
	mac->addr[4] = (u8)(data[3] >> 8);
	mac->addr[3] = (u8)(data[3] >> 16);
	mac->addr[2] = (u8)(data[3] >> 24);
}  /* get_mac_table_info */

/**
 * set_mac_table_info - Set MAC table information
 * @mac:	The MAC table entry.
 * @data:	Buffer to hold MAC table information.
 *
 * This helper routine puts information to MAC table entry.
 */
static void set_mac_table_info(struct ksz_mac_table *mac, u32 data[])
{
	data[0] = (u32)(mac->prio & ALU_V_PRIO_AGE_CNT_M) <<
		ALU_V_PRIO_AGE_CNT_S;
	data[0] |= mac->mstp & ALU_V_MSTP_M;
	if (mac->src)
		data[0] |= ALU_V_SRC_FILTER;
	if (mac->dst)
		data[0] |= ALU_V_DST_FILTER;
	if (mac->valid)
		data[0] |= ALU_V_STATIC_VALID;
	data[1] = mac->ports & ALU_V_PORT_MAP;
	if (mac->override)
		data[1] |= ALU_V_OVERRIDE;
	if (!mac->ignore_use_fid && mac->use_fid)
		data[1] |= ALU_V_USE_FID;
	data[2] = (u32) mac->fid << ALU_V_FID_S;
	data[2] |= ((u32) mac->addr[0] << 8) | mac->addr[1];
	data[3] = ((u32) mac->addr[2] << 24) |
		((u32) mac->addr[3] << 16) |
		((u32) mac->addr[4] << 8) | mac->addr[5];
}  /* set_mac_table_info */

/**
 * wait_for_dyn_mac_table - Wait for dynamic MAC table to be ready
 * @sw:		The switch instance.
 *
 * This helper routines waits for dynamic MAC table to be ready for access.
 */
static void wait_for_dyn_mac_table(struct ksz_sw *sw)
{
	u32 ctrl;

	do {
#if 0
		sw->ops->acquire(sw);
#endif
		ctrl = sw->reg->r32(sw, REG_SW_ALU_CTRL__4);
#if 0
		sw->ops->release(sw);
#endif
	} while ((ctrl & ALU_START) || ALU_SEARCH == (ctrl & ALU_ACTION));
}  /* wait_for_dyn_mac_table */

/**
 * wait_for_sta_mac_table - Wait for static MAC table to be ready
 * @sw:		The switch instance.
 *
 * This helper routines waits for static MAC table to be ready for access.
 */
static void wait_for_sta_mac_table(struct ksz_sw *sw)
{
	u32 ctrl;

	do {
#if 0
		sw->ops->acquire(sw);
#endif
		ctrl = sw->reg->r32(sw, REG_SW_ALU_STAT_CTRL__4);
#if 0
		sw->ops->release(sw);
#endif
	} while (ctrl & ALU_STAT_START);
}  /* wait_for_sta_mac_table */

/**
 * get_vlan_table_info - Get VLAN table information
 * @vlan:	Buffer to store the VLAN table entry.
 * @data:	Buffer holding VLAN table information.
 *
 * This helper routine retrieves information from VLAN table entry data.
 */
static void get_vlan_table_info(struct ksz_vlan_table *vlan, u32 data[])
{
	vlan->valid = !!(data[0] & VLAN_VALID);
	vlan->fid = (data[0] & VLAN_FID_M);
	vlan->mstp = (data[0] >> VLAN_MSTP_S) & VLAN_MSTP_M;
	vlan->prio = (data[0] >> VLAN_PRIO_S) & VLAN_PRIO_M;
	vlan->option = !!(data[0] & VLAN_FORWARD_OPTION);
	vlan->untag = data[1];
	vlan->ports = data[2];
}  /* get_vlan_table_info */

/**
 * set_vlan_table_info - set VLAN table information
 * @vlan:	The VLAN table entry.
 * @data:	Buffer to hold VLAN table information.
 *
 * This helper routine puts information to VLAN table entry.
 */
static void set_vlan_table_info(struct ksz_vlan_table *vlan, u32 data[])
{
	data[0] = vlan->fid & VLAN_FID_M;
	data[0] |= (u32)(vlan->mstp & VLAN_MSTP_M) << VLAN_MSTP_S;
	data[0] |= (u32)(vlan->prio & VLAN_PRIO_M) << VLAN_PRIO_S;
	if (vlan->option)
		data[0] |= VLAN_FORWARD_OPTION;
	if (vlan->valid)
		data[0] |= VLAN_VALID;
	data[1] = vlan->untag;
	data[2] = vlan->ports;
}  /* set_vlan_table_info */

/**
 * wait_for_vlan_table - Wait for VLAN table to be ready
 * @sw:		The switch instance.
 *
 * This helper routines waits for VLAN table to be ready for access.
 */
static void wait_for_vlan_table(struct ksz_sw *sw)
{
	u32 ctrl;

	do {
#if 0
		sw->ops->acquire(sw);
#endif
		ctrl = sw->reg->r8(sw, REG_SW_VLAN_CTRL);
#if 0
		sw->ops->release(sw);
#endif
	} while (ctrl & VLAN_START);
}  /* wait_for_vlan_table */

#ifdef CONFIG_1588_PTP
#include "ksz_ptp_9897.c"
#endif
#ifdef KSZ_IBA
static void sw_set_spi(struct ksz_sw *sw, struct ksz_iba_info *iba);

#include "ksz_iba.c"
#endif

/* -------------------------------------------------------------------------- */

/* Switch functions */

/**
 * sw_r_mac_table - read from MAC table
 * @sw:		The switch instance.
 * @mac:	Buffer to store the MAC table entry.
 *
 * This helper function reads an entry of the MAC table of the switch.
 */
static void sw_r_mac_table(struct ksz_sw *sw, struct ksz_mac_table *mac)
{
	u32 data[4];

	sw_r(sw, REG_SW_ALU_VAL_A, data, 4 * 4);
	data[0] = be32_to_cpu(data[0]);
	data[1] = be32_to_cpu(data[1]);
	data[2] = be32_to_cpu(data[2]);
	data[3] = be32_to_cpu(data[3]);
	get_mac_table_info(mac, data);
}  /* sw_r_mac_table */

/**
 * sw_w_mac_table - write to MAC table
 * @sw:		The switch instance.
 * @mac:	The MAC table entry.
 *
 * This helper function writes an entry of the MAC table of the switch.
 */
static void sw_w_mac_table(struct ksz_sw *sw, struct ksz_mac_table *mac)
{
	u32 data[4];

	set_mac_table_info(mac, data);
	data[0] = cpu_to_be32(data[0]);
	data[1] = cpu_to_be32(data[1]);
	data[2] = cpu_to_be32(data[2]);
	data[3] = cpu_to_be32(data[3]);
	sw_w(sw, REG_SW_ALU_VAL_A, data, 4 * 4);
}  /* sw_w_mac_table */

/**
 * sw_s_dyn_mac_table - prepare dynmaic MAC table for access
 * @sw:		The switch instance.
 * @addr:	The address of the table entry.
 * @src_addr:	The source address.
 * @src_fid:	The source FID.
 *
 * This helper function prepares dynmaic MAC table for access.
 */
static u32 sw_s_dyn_mac_table(struct ksz_sw *sw, u16 addr, u8 *src_addr,
	u16 src_fid)
{
	u32 ctrl;
	u32 data;

	ctrl = 0;
	if (addr) {
		data = (addr - 1) & ALU_DIRECT_INDEX_M;
		sw->reg->w32(sw, REG_SW_ALU_INDEX_1, data);
		ctrl |= ALU_DIRECT;
	} else {
		data = (u32) src_fid << ALU_FID_INDEX_S;
		data |= ((u32) src_addr[0] << 8) | src_addr[1];
		sw->reg->w32(sw, REG_SW_ALU_INDEX_0, data);
		data = ((u32) src_addr[2] << 24) |
			((u32) src_addr[3] << 16) |
			((u32) src_addr[4] << 8) | src_addr[5];
		sw->reg->w32(sw, REG_SW_ALU_INDEX_1, data);
	}
	return ctrl;
}  /* sw_s_dyn_mac_table */

/**
 * sw_r_dyn_mac_hw - read from dynamic MAC table using default access
 * @sw:		The switch instance.
 * @addr:	The address of the table entry.
 * @src_addr:	The source address.
 * @src_fid:	The source FID.
 * @mac:	Buffer to store the MAC table entry.
 * @entry:	Buffer to store the actual entry if available.
 *
 * This routine reads an entry of the dynamic MAC table using default access.
 */
static void sw_r_dyn_mac_hw(struct ksz_sw *sw, u16 addr, u8 *src_addr,
	u16 src_fid, struct ksz_mac_table *mac, u16 *entry)
{
	u32 ctrl;

	ctrl = sw_s_dyn_mac_table(sw, addr, src_addr, src_fid);
	ctrl |= ALU_READ;
	ctrl |= ALU_START;
	sw->reg->w32(sw, REG_SW_ALU_CTRL__4, ctrl);
	do {
		ctrl = sw->reg->r32(sw, REG_SW_ALU_CTRL__4);
	} while (ctrl & ALU_START);
if (!mac->ignore_use_fid)
dbg_msg("  !!! %s\n", __func__);
#if 0
	mac->ignore_use_fid = 1;
#endif
	sw_r_mac_table(sw, mac);

	/* Hash read. */
	if (!addr && entry)
		*entry = (sw->reg->r16(sw, REG_SW_LUE_INDEX_0__2) &
			ENTRY_INDEX_M) + 1;
}  /* sw_r_dyn_mac_hw */

/**
 * sw_r_dyn_mac_table - read from dynamic MAC table
 * @sw:		The switch instance.
 * @addr:	The address of the table entry.
 * @src_addr:	The source address.
 * @src_fid:	The source FID.
 * @mac:	Buffer to store the MAC table entry.
 * @entry:	Buffer to store the actual entry if available.
 *
 * This routine reads an entry of the dynamic MAC table of the switch.
 * ALU table is locked to prevent corruption of read data.
 */
static void sw_r_dyn_mac_table(struct ksz_sw *sw, u16 addr, u8 *src_addr,
	u16 src_fid, struct ksz_mac_table *mac, u16 *entry)
{
	if (entry)
		*entry = 0;
	mutex_lock(&sw->alulock);
	sw->ops->acquire(sw);
	wait_for_dyn_mac_table(sw);
	mac->ignore_use_fid = 1;
	sw->reg->r_dyn_mac_hw(sw, addr, src_addr, src_fid, mac, entry);
	sw->ops->release(sw);
	mutex_unlock(&sw->alulock);
	mac->dirty = 0;
}  /* sw_r_dyn_mac_table */

/**
 * sw_w_dyn_mac_hw - write to dynamic MAC table using default access
 * @sw:		The switch instance.
 * @addr:	The address of the table entry.
 * @src_addr:	The source address.
 * @src_fid:	The source FID.
 * @mac:	The MAC table entry.
 *
 * This routine writes an entry of the dynamic MAC table using default access.
 */
static void sw_w_dyn_mac_hw(struct ksz_sw *sw, u16 addr, u8 *src_addr,
	u16 src_fid, struct ksz_mac_table *mac)
{
	u32 ctrl;

	ctrl = sw_s_dyn_mac_table(sw, addr, src_addr, src_fid);
	ctrl |= ALU_WRITE;
	ctrl |= ALU_START;
#if 0
	mac->ignore_use_fid = 1;
#endif
if (!mac->ignore_use_fid)
dbg_msg("  !!! %s\n", __func__);
	sw_w_mac_table(sw, mac);
	sw->reg->w32(sw, REG_SW_ALU_CTRL__4, ctrl);
}  /* sw_w_dyn_mac_hw */

/**
 * sw_w_dyn_mac_table - write to dynamic MAC table
 * @sw:		The switch instance.
 * @addr:	The address of the table entry.
 * @src_addr:	The source address.
 * @src_fid:	The source FID.
 * @mac:	The MAC table entry.
 *
 * This routine writes an entry of the dynamic MAC table of the switch.
 * ALU table is locked to prevent corruption of read data.
 */
static void sw_w_dyn_mac_table(struct ksz_sw *sw, u16 addr, u8 *src_addr,
	u16 src_fid, struct ksz_mac_table *mac)
{
	mutex_lock(&sw->alulock);
	sw->ops->acquire(sw);
	wait_for_dyn_mac_table(sw);
	mac->ignore_use_fid = 1;
	sw->reg->w_dyn_mac_hw(sw, addr, src_addr, src_fid, mac);
	sw->ops->release(sw);
	mutex_unlock(&sw->alulock);
	mac->dirty = 0;
}  /* sw_w_dyn_mac_table */

/**
 * sw_start_dyn_mac_hw - start dynamic MAC table search using default access
 * @sw:		The switch instance.
 *
 * This routine starts dynamic MAC table search using default access.
 */
static void sw_start_dyn_mac_hw(struct ksz_sw *sw)
{
	u32 ctrl;

	ctrl = ALU_SEARCH;
	ctrl |= ALU_START;
	sw->reg->w32(sw, REG_SW_ALU_CTRL__4, ctrl);
}  /* sw_start_dyn_mac_hw */

/**
 * sw_start_dyn_mac_table - start dynamic MAC table search
 * @sw:		The switch instance.
 *
 * This routine starts dynamic MAC table search.
 * ALU table is locked to prevent corruption of read data.
 */
static void sw_start_dyn_mac_table(struct ksz_sw *sw)
{
	mutex_lock(&sw->alulock);
	sw->ops->acquire(sw);
	wait_for_dyn_mac_table(sw);
	sw->reg->start_dyn_mac_hw(sw);
	sw->ops->release(sw);
}  /* sw_start_dyn_mac_table */

/**
 * sw_g_dyn_mac_hw - retrieve dynamic MAC table result using default access
 * @sw:		The switch instance.
 * @mac:	Buffer to store the MAC table entry.
 *
 * This routine retrieves dynamic MAC table result using default access.
 */
static void sw_g_dyn_mac_hw(struct ksz_sw *sw, struct ksz_mac_table *mac)
{
#if 0
	mac->ignore_use_fid = 1;
#endif
if (!mac->ignore_use_fid)
dbg_msg("  !!! %s\n", __func__);
	sw_r_mac_table(sw, mac);
}  /* sw_g_dyn_mac_hw */

/**
 * sw_g_dyn_mac_table - retrieve dynamic MAC table result
 * @sw:		The switch instance.
 * @addr:	The address of the table entry.
 * @mac:	Buffer to store the MAC table entry.
 *
 * This function retrieves an entry of the dynamic MAC table search result.
 *
 * Return 0 if the entry is successfully read; otherwise -1.
 */
static int sw_g_dyn_mac_table(struct ksz_sw *sw, u16 *addr,
	struct ksz_mac_table *mac)
{
	u32 ctrl;
	int rc = 0;
int timeout = 10;
u32 data = 0;

	sw->ops->acquire(sw);
	do {
		ctrl = sw->reg->r32(sw, REG_SW_ALU_CTRL__4);
if (--timeout <= 0) {
printk(" %s to\n", __func__);
break;
}
/**
 * THa  2015/04/21
 * The long delay before the chip select is dropped causes the chip to think
 * the register is written twice, so the valid bit will not be set when read.
 */
#if 1
	if (!*addr && 1 == (ctrl >> ALU_VALID_CNT_S) && !(ctrl & ALU_VALID))
		ctrl |= ALU_VALID;
#endif
if ((ctrl & ALU_START) && !(ctrl & ALU_VALID))
data = ctrl;
	} while (!(ctrl & ALU_VALID) && (ctrl & ALU_START));
	if (ctrl & ALU_VALID) {
		ctrl >>= ALU_VALID_CNT_S;
		ctrl &= ALU_VALID_CNT_M;
		mac->ignore_use_fid = 1;
		sw->reg->g_dyn_mac_hw(sw, mac);
if (ctrl != *addr + 1)
printk(" ?get: %x %x\n", ctrl, *addr);
		if (ctrl != *addr + 1)
			*addr = ctrl - 1;
	} else
		rc = -1;
if (timeout < 9)
printk(" %s to: %d %x\n", __func__, timeout, data);
	sw->ops->release(sw);
	return rc;
}  /* sw_g_dyn_mac_table */

/**
 * sw_stop_dyn_mac_hw - stop dynamic MAC table search using default access
 * @sw:		The switch instance.
 *
 * This function stops dynamic MAC table search using default access.
 *
 * Return the last MAC table control.
 */
static u32 sw_stop_dyn_mac_hw(struct ksz_sw *sw)
{
	u32 ctrl;

	ctrl = 0;
	sw->reg->w32(sw, REG_SW_ALU_CTRL__4, ctrl);
	ctrl = sw->reg->r32(sw, REG_SW_ALU_CTRL__4);
	return ctrl;
}  /* sw_stop_dyn_mac_hw */

/**
 * sw_stop_dyn_mac_table - stop dynamic MAC table search
 * @sw:		The switch instance.
 * @addr:	The address of the last table entry.
 *
 * This routine stops dynamic MAC table search.
 */
static void sw_stop_dyn_mac_table(struct ksz_sw *sw, u16 addr)
{
	u32 ctrl;

	sw->ops->acquire(sw);
	ctrl = sw->reg->stop_dyn_mac_hw(sw);
	ctrl >>= ALU_VALID_CNT_S;
	ctrl &= ALU_VALID_CNT_M;
if (ctrl != addr)
dbg_msg(" ?stop: %x %x\n", ctrl, addr);
	sw->ops->release(sw);
	mutex_unlock(&sw->alulock);
}  /* sw_stop_dyn_mac_table */

/**
 * sw_d_dyn_mac_table - dump dynamic MAC table
 * @sw:		The switch instance.
 *
 * This routine dumps dynamic MAC table contents.
 */
static void sw_d_dyn_mac_table(struct ksz_sw *sw)
{
	u16 i;
	struct ksz_mac_table mac;

	sw_start_dyn_mac_table(sw);
	i = 0;
	do {
		if (sw_g_dyn_mac_table(sw, &i, &mac))
			break;
		printk(KERN_INFO
			"%4x: %02X:%02X:%02X:%02X:%02X:%02X "
			"%04x m:%u t:%u s:%u d:%u o:%u %u:%02x [%u]\n",
			i, mac.addr[0], mac.addr[1], mac.addr[2],
			mac.addr[3], mac.addr[4], mac.addr[5],
			mac.ports, mac.mstp, mac.prio, mac.src, mac.dst,
			mac.override, mac.use_fid, mac.fid, mac.valid);
		yield();
		i++;
	} while (1);
	sw_stop_dyn_mac_table(sw, i);
}  /* sw_d_dyn_mac_table */

static u8 mcast_reserved_map[RESERVED_MCAST_TABLE_ENTRIES] = {
	0, 1, 6, 2, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
	3, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
	4, 5, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
};

static u32 get_mac_table_ctrl(u16 addr, int mcast)
{
	u32 ctrl;

	ctrl = addr;
	if (mcast)
		ctrl &= ALU_RESV_MCAST_INDEX_M;
	else
		ctrl &= ALU_STAT_INDEX_M;
	ctrl <<= ALU_STAT_INDEX_S;
	if (mcast)
		ctrl |= ALU_RESV_MCAST_ADDR;
	ctrl |= ALU_STAT_START;
	return ctrl;
}  /* get_mac_table_ctrl */

/**
 * sw_r_sta_mac_hw - read from static MAC table using default access
 * @sw:		The switch instance.
 * @ctrl:	The control values for read operation.
 * @num:	Number of entries to read.
 * @mac:	Buffer to hold the MAC table entries.
 *
 * This routine reads from static MAC table using default access.
 */
static void sw_r_sta_mac_hw(struct ksz_sw *sw, u32 ctrl[], int num,
	struct ksz_mac_table *mac)
{
	u32 status;
	int cnt = 0;

	do {
		sw->reg->w32(sw, REG_SW_ALU_STAT_CTRL__4, *ctrl);
		do {
			status = sw->reg->r32(sw, REG_SW_ALU_STAT_CTRL__4);
		} while (status & ALU_STAT_START);
if (mac->ignore_use_fid)
dbg_msg("  !!! %s\n", __func__);
#if 0
		mac->ignore_use_fid = 0;
#endif
		sw_r_mac_table(sw, mac);
		++cnt;
		++ctrl;
		++mac;
	} while (cnt < num);
}  /* sw_r_sta_mac_hw */

/**
 * sw_r_sta_mac_table - read from static MAC table
 * @sw:		The switch instance.
 * @addr:	The address of the table entry.
 * @mcast:	Multicast reserved table indication.
 * @mac:	Buffer to store the MAC table entry.
 *
 * This routine reads an entry of the static MAC table of the switch.
 */
static void sw_r_sta_mac_table(struct ksz_sw *sw, u16 addr, int mcast,
	struct ksz_mac_table *mac)
{
	u32 ctrl;

	mutex_lock(&sw->alulock);
	sw->ops->acquire(sw);
	wait_for_sta_mac_table(sw);
	ctrl = get_mac_table_ctrl(addr, mcast);
	ctrl |= ALU_STAT_READ;
	mac->ignore_use_fid = 0;
	sw->reg->r_sta_mac_hw(sw, &ctrl, 1, mac);
	sw->ops->release(sw);
	mutex_unlock(&sw->alulock);
	if (mcast) {
		mac->addr[0] = 0x01;
		mac->addr[1] = 0x80;
		mac->addr[2] = 0xC2;
		mac->addr[3] = 0x00;
		mac->addr[4] = 0x00;
		mac->addr[5] = addr;
		mac->valid = 1;
	}
	mac->dirty = 0;
}  /* sw_r_sta_mac_table */

/**
 * sw_r_m_sta_mac_table - read many from static MAC table
 * @sw:		The switch instance.
 * @addr:	The addresses of the table entries.
 * @mcast:	Multicast reserved table indication.
 * @mac:	Buffer to store the MAC table entries.
 *
 * This routines reads several entries of the static MAC table of the switch.
 */
static void sw_r_m_sta_mac_table(struct ksz_sw *sw, u16 addr[], int mcast,
	int num, struct ksz_mac_table *mac)
{
	u32 ctrl[MAX_IBA_MAC_ENTRIES];
	u16 max_addr;
	int i;
	int j;
	int cnt = MAX_IBA_MAC_ENTRIES;

	if (mcast)
		max_addr = RESERVED_MCAST_TABLE_ENTRIES;
	else
		max_addr = STATIC_MAC_TABLE_ENTRIES;
	memset(mac, 0, sizeof(struct ksz_mac_table) * num);
	mutex_lock(&sw->alulock);
	sw->ops->acquire(sw);
	wait_for_sta_mac_table(sw);
	for (i = 0; i < num; i += MAX_IBA_MAC_ENTRIES) {
#if 1
		if (addr[i] >= max_addr)
			break;
#endif
		if (cnt > max_addr - addr[i])
			cnt = max_addr - addr[i];
		if (cnt > num - i)
			cnt = num - i;
		for (j = 0; j < cnt; j++) {
			ctrl[j] = get_mac_table_ctrl(addr[i + j], mcast);
			ctrl[j] |= ALU_STAT_READ;
			mac[j].ignore_use_fid = 0;
		}
		sw->reg->r_sta_mac_hw(sw, ctrl, cnt, mac);
		for (j = 0; j < cnt; j++) {
			if (mcast) {
				mac->addr[0] = 0x01;
				mac->addr[1] = 0x80;
				mac->addr[2] = 0xC2;
				mac->addr[3] = 0x00;
				mac->addr[4] = 0x00;
				mac->addr[5] = addr[i + j];
				mac->valid = 1;
			}
			++mac;
		}
	}
	sw->ops->release(sw);
	mutex_unlock(&sw->alulock);
}  /* sw_r_m_sta_mac_table */

/**
 * sw_w_sta_mac_hw - write to static MAC table using default access
 * @sw:		The switch instance.
 * @ctrl:	The control values for write operation.
 * @num:	Number of entries to write.
 * @mac:	MAC table entries.
 *
 * This routine writes to static MAC table using default access.
 */
static void sw_w_sta_mac_hw(struct ksz_sw *sw, u32 ctrl[], int num,
	struct ksz_mac_table *mac)
{
	u32 status;
	int cnt;

	for (cnt = 0; cnt < num; cnt++, ctrl++, mac++) {
if (mac->ignore_use_fid)
dbg_msg("  !!! %s\n", __func__);
#if 0
		mac->ignore_use_fid = 0;
#endif
		sw_w_mac_table(sw, mac);
		sw->reg->w32(sw, REG_SW_ALU_STAT_CTRL__4, *ctrl);
		do {
			status = sw->reg->r32(sw, REG_SW_ALU_STAT_CTRL__4);
		} while (status & ALU_STAT_START);
	}
}  /* sw_w_sta_mac_hw */

/**
 * sw_w_sta_mac_table - write to static MAC table
 * @sw:		The switch instance.
 * @addr:	The address of the table entry.
 * @mcast:	Multicast reserved table indication.
 * @mac:	The MAC table entry.
 *
 * This routine writes an entry of the static MAC table of the switch.
 */
static void sw_w_sta_mac_table(struct ksz_sw *sw, u16 addr, int mcast,
	struct ksz_mac_table *mac)
{
	u32 ctrl;

	mutex_lock(&sw->alulock);
	sw->ops->acquire(sw);
	wait_for_sta_mac_table(sw);
	ctrl = get_mac_table_ctrl(addr, mcast);
	mac->ignore_use_fid = 0;
	sw->reg->w_sta_mac_hw(sw, &ctrl, 1, mac);
	sw->ops->release(sw);
	mutex_unlock(&sw->alulock);
	mac->dirty = 0;
}  /* sw_w_sta_mac_table */

/**
 * sw_w_m_sta_mac_table - write many to static MAC table
 * @sw:		The switch instance.
 * @addr:	The addresses of the table entries.
 * @mcast:	Multicast reserved table indication.
 * num:		Numbe of entries.
 * @mac:	The MAC table entries.
 *
 * This routine writes several entries of the static MAC table of the switch.
 */
static void sw_w_m_sta_mac_table(struct ksz_sw *sw, u16 addr[], int mcast,
	int num, struct ksz_mac_table *mac)
{
	u32 ctrl[MAX_IBA_MAC_ENTRIES];
	int i;
	int j;
	int cnt = MAX_IBA_MAC_ENTRIES;

	mutex_lock(&sw->alulock);
	sw->ops->acquire(sw);
	wait_for_sta_mac_table(sw);
	for (i = 0; i < num; i += MAX_IBA_MAC_ENTRIES) {
		if (cnt > num - i)
			cnt = num - i;
		for (j = 0; j < cnt; j++) {
			ctrl[j] = get_mac_table_ctrl(addr[i + j], mcast);
			mac[j].ignore_use_fid = 0;
		}
		sw->reg->w_sta_mac_hw(sw, ctrl, cnt, mac);
		mac += MAX_IBA_MAC_ENTRIES;
	}
	sw->ops->release(sw);
	mutex_unlock(&sw->alulock);
}  /* sw_w_m_sta_mac_table */

/**
 * sw_d_sta_mac_table - dump static MAC table
 * @sw:		The switch instance.
 *
 * This routine dumps static MAC table contents.
 */
static void sw_d_sta_mac_table(struct ksz_sw *sw)
{
	int i;
	int j;
	u16 addr[8];
	struct ksz_mac_table *mac;
	struct ksz_mac_table table[8];
	int first_static = true;

	i = 0;
	do {
		for (j = 0; j < MAX_IBA_MAC_ENTRIES; j++)
			addr[j] = i + j;
		sw_r_m_sta_mac_table(sw, addr, 1, MAX_IBA_MAC_ENTRIES,
			table);
		for (j = 0; j < MAX_IBA_MAC_ENTRIES; j++) {
			mac = &table[j];
			if (!mac->valid)
				continue;
			printk(KERN_INFO
				"%2x: %02X:%02X:%02X:%02X:%02X:%02X "
				"%04x m:%u p:%u s:%u d:%u o:%u %u:%02x <%u>\n",
				i + j,
				mac->addr[0], mac->addr[1], mac->addr[2],
				mac->addr[3], mac->addr[4], mac->addr[5],
				mac->ports, mac->mstp, mac->prio,
				mac->src, mac->dst,
				mac->override, mac->use_fid, mac->fid,
				mcast_reserved_map[i + j]);
		}
		yield();
		i += MAX_IBA_MAC_ENTRIES;
	} while (i < RESERVED_MCAST_TABLE_ENTRIES);
	i = 0;
	do {
		for (j = 0; j < MAX_IBA_MAC_ENTRIES; j++)
			addr[j] = i + j;
		sw_r_m_sta_mac_table(sw, addr, 0, MAX_IBA_MAC_ENTRIES,
			table);
		for (j = 0; j < MAX_IBA_MAC_ENTRIES; j++) {
			mac = &table[j];
			if (!mac->valid)
				continue;
			if (first_static) {
				first_static = false;
				printk(KERN_INFO "\n");
			}
			printk(KERN_INFO
				"%2x: %02X:%02X:%02X:%02X:%02X:%02X "
				"%04x m:%u p:%u s:%u d:%u o:%u %u:%02x\n",
				i + j,
				mac->addr[0], mac->addr[1], mac->addr[2],
				mac->addr[3], mac->addr[4], mac->addr[5],
				mac->ports, mac->mstp, mac->prio,
				mac->src, mac->dst,
				mac->override, mac->use_fid, mac->fid);
		}
		yield();
		i += MAX_IBA_MAC_ENTRIES;
	} while (i < STATIC_MAC_TABLE_ENTRIES);
}  /* sw_d_sta_mac_table */

static int get_mcast_reserved_addr(u8 group)
{
	int i;

	for (i = 0; i < RESERVED_MCAST_TABLE_ENTRIES; i++)
		if (group == mcast_reserved_map[i])
			return i;
	return -1;
}  /* get_mcast_reserved_addr */

static void sw_d_mac_table(struct ksz_sw *sw)
{
	struct ksz_mac_table *mac;
	struct ksz_alu_table *alu;
	int i;
	int first_static = true;

	i = STATIC_MAC_TABLE_ENTRIES;
	do {
		mac = &sw->info->mac_table[i];
		if (mac->valid) {
			if (first_static) {
				first_static = false;
				printk(KERN_INFO "\n");
			}
			alu = &sw->info->alu_table[i];
			printk(KERN_INFO
				"%2x: %02X:%02X:%02X:%02X:%02X:%02X "
				"%04x m:%u p:%u s:%u d:%u o:%u %u:%02x  "
				"%02x:%02x\n",
				i,
				mac->addr[0], mac->addr[1], mac->addr[2],
				mac->addr[3], mac->addr[4], mac->addr[5],
				mac->ports, mac->mstp, mac->prio,
				mac->src, mac->dst,
				mac->override, mac->use_fid, mac->fid,
				alu->forward, alu->owner);
		}
		i++;
		if (SWITCH_MAC_TABLE_ENTRIES == i)
			first_static = true;
	} while (i < MULTI_MAC_TABLE_ENTRIES);
}

/* -------------------------------------------------------------------------- */

/**
 * sw_r_vlan_hw - read from VLAN table using default access
 * @sw:		The switch instance.
 * @data:	Buffer to hold the VLAN data.
 * @num:	Number of entries to read.
 *
 * This routine reads from VLAN table using default access.
 */
static void sw_r_vlan_hw(struct ksz_sw *sw, u32 data[], int num)
{
	u8 ctrl;
	int cnt = 0;
	u16 addr = data[READ_VLAN_ENTRY_SIZE];

	do {
		sw->reg->w16(sw, REG_SW_VLAN_ENTRY_INDEX__2, addr);
		ctrl = VLAN_READ;
		ctrl |= VLAN_START;
		sw->reg->w8(sw, REG_SW_VLAN_CTRL, ctrl);
		do {
			ctrl = sw->reg->r8(sw, REG_SW_VLAN_CTRL);
		} while (ctrl & VLAN_START);
		data[0] = sw->reg->r32(sw, REG_SW_VLAN_ENTRY__4);
		data[1] = 0;
		data[2] = 0;
		if (data[0] & VLAN_VALID) {
			sw_r(sw, REG_SW_VLAN_ENTRY_UNTAG__4, &data[1], 4 * 2);
			data[1] = be32_to_cpu(data[1]);
			data[2] = be32_to_cpu(data[2]);
		}
		++cnt;
		++addr;
		data += READ_VLAN_ENTRY_SIZE;
	} while (cnt < num);
}  /* sw_r_vlan_hw */

/**
 * sw_r_vlan_table - read from VLAN table
 * @sw:		The switch instance.
 * @addr:	The address of the table entry.
 * @vlan:	Buffer to store the VLAN table entry.
 *
 * This function reads an entry of the VLAN table of the switch.
 *
 * Return 0 if the entry is valid; otherwise -1.
 */
static int sw_r_vlan_table(struct ksz_sw *sw, u16 addr,
	struct ksz_vlan_table *vlan)
{
	u32 data[READ_VLAN_ENTRY_SIZE + 1];
	int rc = -1;

	mutex_lock(&sw->vlanlock);
	sw->ops->acquire(sw);
	wait_for_vlan_table(sw);
	data[READ_VLAN_ENTRY_SIZE] = addr;
	sw->reg->r_vlan_hw(sw, data, 1);
	get_vlan_table_info(vlan, data);
	sw->ops->release(sw);
	mutex_unlock(&sw->vlanlock);
	if (vlan->valid)
		rc = 0;
	vlan->vid = addr;
	vlan->dirty = 0;
	return rc;
}  /* sw_r_vlan_table */

/**
 * sw_r_m_vlan_table - read many from VLAN table
 * @sw:		The switch instance.
 * @addr:	The starting address of the table entries.
 * @num:	Number of entries.
 * @vlan:	Buffer to store the VLAN table entries.
 *
 * This routine reads several entries of the VLAN table of the switch.
 */
static void sw_r_m_vlan_table(struct ksz_sw *sw, u16 addr, int num,
	struct ksz_vlan_table *vlan)
{
	u32 data[READ_VLAN_ENTRY_SIZE * MAX_IBA_VLAN_ENTRIES + 1];
	int i;
	int j;
	int cnt = MAX_IBA_VLAN_ENTRIES;

	memset(vlan, 0, sizeof(struct ksz_vlan_table) * num);
	mutex_lock(&sw->vlanlock);
	sw->ops->acquire(sw);
	wait_for_vlan_table(sw);
	for (i = 0; i < num; i += MAX_IBA_VLAN_ENTRIES,
	     addr += MAX_IBA_VLAN_ENTRIES) {
		if (addr >= 4096)
			break;
		if (cnt > 4096 - addr)
			cnt = 4096 - addr;
		if (cnt > num - i)
			cnt = num - i;
		data[READ_VLAN_ENTRY_SIZE] = addr;
		sw->reg->r_vlan_hw(sw, data, cnt);
		for (j = 0; j < cnt; j++) {
			get_vlan_table_info(vlan, &data[j *
				READ_VLAN_ENTRY_SIZE]);
			vlan->vid = addr + j;
			vlan++;
		}
	}
	sw->ops->release(sw);
	mutex_unlock(&sw->vlanlock);
}  /* sw_r_m_vlan_table */

/**
 * sw_w_vlan_hw - write to VLAN table using default access
 * @sw:		The switch instance.
 * @data:	VLAN data to write.
 * @num:	Number of entries to write.
 *
 * This routine writes to VLAN table using default access.
 */
static void sw_w_vlan_hw(struct ksz_sw *sw, u32 data[], int num)
{
	u8 ctrl;
	int cnt;

	for (cnt = 0; cnt < num; cnt++) {
		data[0] = cpu_to_be32(data[0]);
		data[1] = cpu_to_be32(data[1]);
		data[2] = cpu_to_be32(data[2]);
		data[3] = cpu_to_be16(data[3]);
#if 0
		sw_w(sw, REG_SW_VLAN_ENTRY__4, data, 4 * 3 + 2);
#else
		sw_w(sw, REG_SW_VLAN_ENTRY__4, data, 4 * 3 + 4);
#endif
		ctrl = VLAN_WRITE;
		ctrl |= VLAN_START;
		sw->reg->w8(sw, REG_SW_VLAN_CTRL, ctrl);
		do {
			ctrl = sw->reg->r8(sw, REG_SW_VLAN_CTRL);
		} while (ctrl & VLAN_START);
		data += WRITE_VLAN_ENTRY_SIZE;
	}
}  /* sw_w_vlan_hw */

/**
 * sw_w_vlan_table - write to VLAN table
 * @sw:		The switch instance.
 * @addr:	The address of the table entry.
 * @vlan:	The VLAN table entry.
 *
 * This routine writes an entry of the VLAN table of the switch.
 */
static void sw_w_vlan_table(struct ksz_sw *sw, u16 addr,
	struct ksz_vlan_table *vlan)
{
	u32 data[4];

	mutex_lock(&sw->vlanlock);
	sw->ops->acquire(sw);
	wait_for_vlan_table(sw);
	set_vlan_table_info(vlan, data);
	data[3] = addr;
	sw->reg->w_vlan_hw(sw, data, 1);
	sw->ops->release(sw);
	mutex_unlock(&sw->vlanlock);
	vlan->dirty = 0;
}  /* sw_w_vlan_table */

/**
 * sw_d_vlan_table - dump VLAN table
 * @sw:		The switch instance.
 *
 * This routine dumps the VLAN table of the switch.
 */
static void sw_d_vlan_table(struct ksz_sw *sw)
{
	u16 i;
	int j;
	struct ksz_vlan_table *vlan;
	struct ksz_vlan_table table[8];

	i = 0;
	do {
		sw_r_m_vlan_table(sw, i, MAX_IBA_VLAN_ENTRIES, table);
		for (j = 0; j < MAX_IBA_VLAN_ENTRIES; j++) {
			vlan = &table[j];
			if (!vlan->valid)
				continue;
			printk(KERN_INFO
				"%3x: 0x%03x m:%x p:%x o:%u %04x %04x\n",
				vlan->vid,
				vlan->fid, vlan->mstp, vlan->prio,
				vlan->option, vlan->untag, vlan->ports);
		}
		yield();
		i += MAX_IBA_VLAN_ENTRIES;
	} while (i < 4096);
}  /* sw_d_vlan_table */

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

	addr = PORT_CTRL_ADDR(port, offset);
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

	addr = PORT_CTRL_ADDR(port, offset);
	data = SW_R(sw, addr);
	if (set)
		data |= bits;
	else
		data &= ~bits;
	SW_W(sw, addr, data);
}  /* port_cfg */

/**
 * port_chk32 - check port register bits
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
static int port_chk32(struct ksz_sw *sw, int port, int offset, u32 bits)
{
	u32 addr;
	u32 data;

	addr = PORT_CTRL_ADDR(port, offset);
	data = sw->reg->r32(sw, addr);
	return (data & bits) == bits;
}  /* port_chk32 */

/**
 * port_cfg32 - set port register bits
 * @sw:		The switch instance.
 * @port:	The port index.
 * @offset:	The offset of the port register.
 * @bits:	The data bits to set.
 * @set:	The flag indicating whether the bits are to be set or not.
 *
 * This routine sets or resets the specified bits of the port register.
 */
static void port_cfg32(struct ksz_sw *sw, int port, int offset, u32 bits,
	int set)
{
	u32 addr;
	u32 data;

	addr = PORT_CTRL_ADDR(port, offset);
	data = sw->reg->r32(sw, addr);
	if (set)
		data |= bits;
	else
		data &= ~bits;
	sw->reg->w32(sw, addr, data);
}  /* port_cfg32 */

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

	addr = PORT_CTRL_ADDR(port, offset);
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

	addr = PORT_CTRL_ADDR(port, offset);
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

	addr = PORT_CTRL_ADDR(port, offset);
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

	addr = PORT_CTRL_ADDR(port, offset);
	sw->reg->w16(sw, addr, data);
}  /* port_w16 */

/**
 * port_r32 - read dword from port register.
 * @sw:		The switch instance.
 * @port:	The port index.
 * @offset:	The offset of the port register.
 * @data:	Buffer to store the data.
 *
 * This routine reads a dword from the port register.
 */
static void port_r32(struct ksz_sw *sw, int port, int offset, u32 *data)
{
	u32 addr;

	addr = PORT_CTRL_ADDR(port, offset);
	*data = sw->reg->r32(sw, addr);
}  /* port_r32 */

/**
 * port_w32 - write dword to port register.
 * @sw:		The switch instance.
 * @port:	The port index.
 * @offset:	The offset of the port register.
 * @data:	Data to write.
 *
 * This routine writes a dword to the port register.
 */
static void port_w32(struct ksz_sw *sw, int port, int offset, u32 data)
{
	u32 addr;

	addr = PORT_CTRL_ADDR(port, offset);
	sw->reg->w32(sw, addr, data);
}  /* port_w32 */

static void port_get(struct ksz_sw *sw, int port, int offset, void *buf,
	size_t cnt)
{
	u32 addr;

	addr = PORT_CTRL_ADDR(port, offset);
	sw->reg->r(sw, addr, buf, cnt);
}

#if 0
static void port_set(struct ksz_sw *sw, int port, int offset, void *buf,
	size_t cnt)
{
	u32 addr;

	addr = PORT_CTRL_ADDR(port, offset);
	sw->reg->w(sw, addr, buf, cnt);
}
#endif

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

static u32 port_r_s_32(struct ksz_sw *sw, int p, u32 reg, u32 mask,
	u32 shift)
{
	u32 data;

	port_r32(sw, p, reg, &data);
	data >>= shift;
	data &= mask;
	return data;
}

static void port_w_s_32(struct ksz_sw *sw, int p, u32 reg, u32 mask,
	u32 shift, u32 val)
{
	u32 data;

	port_r32(sw, p, reg, &data);
	data &= ~(mask << shift);
	data |= (val & mask) << shift;
	port_w32(sw, p, reg, data);
}

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

static SW_D sw_r_shift(struct ksz_sw *sw, u32 addr, u32 mask,
	u32 shift)
{
	SW_D data;

	data = SW_R(sw, addr);
	data >>= shift;
	data &= mask;
	return data;
}

static void sw_w_shift(struct ksz_sw *sw, u32 addr, u32 mask, u32 shift,
	SW_D val)
{
	SW_D data;

	data = SW_R(sw, addr);
	data &= ~(mask << shift);
	data |= (val & mask) << shift;
	SW_W(sw, addr, data);
}

#ifdef PORT_OUT_RATE_ADDR
/**
 * port_out_rate_r8 - read byte from port register
 * @sw:		The switch instance.
 * @port:	The port index.
 * @offset:	The offset of the port register.
 * @data:	Buffer to store the data.
 *
 * This routine reads a byte from the port register.
 */
static void port_out_rate_r8(struct ksz_sw *sw, int port, int offset, u8 *data)
{
	u32 addr;

	PORT_OUT_RATE_ADDR(port, addr);
	addr += offset;
	*data = sw->reg->r8(sw, addr);
}

/**
 * port_out_rate_w8 - write byte to port register
 * @sw:		The switch instance.
 * @port:	The port index.
 * @offset:	The offset of the port register.
 * @data:	Data to write.
 *
 * This routine writes a byte to the port register.
 */
static void port_out_rate_w8(struct ksz_sw *sw, int port, int offset, u8 data)
{
	u32 addr;

	PORT_OUT_RATE_ADDR(port, addr);
	addr += offset;
	sw->reg->w8(sw, addr, data);
}
#endif

/* -------------------------------------------------------------------------- */

/* ACL */

static inline void port_cfg_acl(struct ksz_sw *sw, int p, int set)
{
	port_cfg(sw, p,
		REG_PORT_MRI_AUTHEN_CTRL, PORT_ACL_ENABLE, set);
}

static inline int port_chk_acl(struct ksz_sw *sw, int p)
{
	return port_chk(sw, p,
		REG_PORT_MRI_AUTHEN_CTRL, PORT_ACL_ENABLE);
}

static inline u8 port_get_authen_mode(struct ksz_sw *sw, int p)
{
	return port_r_s(sw, p,
		REG_PORT_MRI_AUTHEN_CTRL, PORT_AUTHEN_MODE, 0);
}

static void port_set_authen_mode(struct ksz_sw *sw, int p, u8 mode)
{
	port_w_s(sw, p,
		REG_PORT_MRI_AUTHEN_CTRL, PORT_AUTHEN_MODE, 0, mode);
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

	/* byte 12 is not used at all. */
	acl->ports = data[13];
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

	/* byte 12 is not used at all. */
	data[13] = acl->ports;
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
			data[12] = 0;
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
#ifndef NO_ACL
	u8 ctrl;
int timeout = 100;

	do {
		port_r(sw, port, REG_PORT_ACL_CTRL_0, &ctrl);
if (--timeout < 1) {
dbg_msg(" %s %d %x to\n", __func__, port, ctrl);
break;
}
	} while (!(ctrl & (PORT_ACL_WRITE_DONE | PORT_ACL_READ_DONE)));
#endif
}  /* wait_for_acl_table */

/**
 * sw_r_acl_hw - read from ACL table using default access
 * @sw:		The switch instance.
 * @port:	The port index.
 * @addr:	The ACL index.
 * @data:	Buffer to hold the ACL data.
 *
 * This routine reads from ACL table of the port using default access.
 */
static void sw_r_acl_hw(struct ksz_sw *sw, int port, u16 addr, u8 data[])
{
#ifndef NO_ACL
	u8 ctrl = (addr & PORT_ACL_INDEX_M);
int timeout = 100;

	port_w(sw, port, REG_PORT_ACL_CTRL_0, ctrl);
	do {
		port_r(sw, port, REG_PORT_ACL_CTRL_0, &ctrl);
if (--timeout < 1) {
dbg_msg(" %s %d %x to\n", __func__, port, addr);
break;
}
	} while (!(ctrl & PORT_ACL_READ_DONE));
	sw_r(sw, PORT_CTRL_ADDR(port, REG_PORT_ACL_0), data, ACL_TABLE_LEN);
#else
	memset(data, 0, 16);
#endif
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

	sw->ops->acquire(sw);
	wait_for_acl_table(sw, port);
	sw->reg->r_acl_hw(sw, port, addr, data);
	get_acl_table_info(acl, data);
	memcpy(acl->data, data, ACL_TABLE_LEN);
	sw->ops->release(sw);
	if (acl->mode)
		rc = 0;
	acl->changed = 0;
	return rc;
}  /* sw_r_acl_table */

/**
 * sw_w_acl_hw - write to ACL table using default access
 * @sw:		The switch instance.
 * @port:	The port index.
 * @addr:	The ACL index.
 * @data:	The ACL data to write.
 *
 * This routine writes to ACL table of the port using default access.
 */
static void sw_w_acl_hw(struct ksz_sw *sw, int port, u16 addr, u8 data[])
{
#ifndef NO_ACL
	u8 ctrl = (addr & PORT_ACL_INDEX_M) | PORT_ACL_WRITE;
#if 1
int timeout = 100;
#endif

	sw_w(sw, PORT_CTRL_ADDR(port, REG_PORT_ACL_0), data, ACL_TABLE_LEN);
	port_w(sw, port, REG_PORT_ACL_CTRL_0, ctrl);
	do {
		port_r(sw, port, REG_PORT_ACL_CTRL_0, &ctrl);
#if 1
if (--timeout < 1) {
dbg_msg(" %s %d %x to\n", __func__, port, addr);
break;
}
#endif
	} while (!(ctrl & PORT_ACL_WRITE_DONE));
#endif
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

	sw->ops->acquire(sw);
	wait_for_acl_table(sw, port);
	set_acl_action_info(acl, data);
	port_w16(sw, port, REG_PORT_ACL_BYTE_EN_MSB, ACL_ACTION_ENABLE);
	sw->reg->w_acl_hw(sw, port, addr, data);
	memcpy(&acl->data[ACL_ACTION_START], &data[ACL_ACTION_START],
		ACL_ACTION_LEN);
	sw->ops->release(sw);
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
	sw->ops->acquire(sw);
	wait_for_acl_table(sw, port);
	set_acl_table_info(acl, data);
	port_w16(sw, port, REG_PORT_ACL_BYTE_EN_MSB, byte_enable);
	sw->reg->w_acl_hw(sw, port, addr, data);
	memcpy(acl->data, data, ACL_ACTION_START);
	memcpy(&acl->data[ACL_RULESET_START], &data[ACL_RULESET_START], 2);
	sw->ops->release(sw);
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
		cfg = &sw->info->port_cfg[port];
		memset(cfg->acl_info, 0, sizeof(struct ksz_acl_table) *
			ACL_TABLE_ENTRIES);
		cfg->acl_index = cfg->acl_act_index = 0;
	}
}  /* sw_reset_acl */

static void sw_reset_acl_hw(struct ksz_sw *sw)
{
#ifndef NO_ACL
	struct ksz_port_cfg *cfg;
	struct ksz_acl_table *acl;
	int i;
	int port;

	sw_reset_acl(sw);
	sw->ops->release(sw);
	for (port = 0; port < sw->mib_port_cnt; port++) {
		cfg = &sw->info->port_cfg[port];
		for (i = 0; i < ACL_TABLE_ENTRIES; i++) {
			acl = &cfg->acl_info[i];
			acl->data[0] = 0xff;
			acl->mode = 0;
			sw_w_acl_action(sw, port, i, acl);
			sw_w_acl_table(sw, port, i, acl);
		}
	}
	sw->ops->acquire(sw);
#endif
}  /* sw_reset_acl_hw */

static void sw_init_acl(struct ksz_sw *sw)
{
#ifndef NO_ACL
	struct ksz_port_cfg *cfg;
	struct ksz_acl_table *acl;
	int i;
	int port;
#if 0
	u8 data[20];

	memset(data, 0, 20);
	data[11] = 0x60;
#endif
	for (port = 0; port < sw->mib_port_cnt; port++) {
		port_cfg_acl(sw, port, 1);
#if 0
		port_w16(sw, port, REG_PORT_ACL_BYTE_EN_MSB, 0xffff);
/*
 * THa  2015/11/29
 * The DLR beacon drop 2-entry rule occasionally leaks the beacon when running
 * in Gigabit and heavy traffic unless the port mapping action in first entry
 * is set in AND or REPLACE with empty ports.
 */
		wait_for_acl_table(sw, port);
		sw->reg->w_acl_hw(sw, port, 0, data);
#endif
		cfg = &sw->info->port_cfg[port];
		sw->ops->release(sw);
		for (i = 0; i < ACL_TABLE_ENTRIES; i++) {
			acl = &cfg->acl_info[i];
			sw_r_acl_table(sw, port, i, acl);
		}
		sw->ops->acquire(sw);
	}
#endif
}  /* sw_init_acl */

/* -------------------------------------------------------------------------- */

/* 36-bit counts. */
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

/* Actual locations. */
#define MIB_9897_RX_BYTE_CNT		0x80
#define MIB_9897_TX_BYTE_CNT		0x81

#define MIB_9897_RX_DROPPED_PACKET	0x82
#define MIB_9897_TX_DROPPED_PACKET	0x83

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

/*
 * Some counters do not need to be read too often because they are less likely
 * to increase much.
 */
static u8 mib_read_max[SWITCH_COUNTER_NUM] = {
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
};

static u8 mib_start[TOTAL_SWITCH_COUNTER_NUM];
static u8 mib_index[TOTAL_SWITCH_COUNTER_NUM];

static u8 sw_fill_mib_index(struct ksz_sw *sw, u8 index, u8 interval)
{
	int i;

	for (i = 0; i < SWITCH_COUNTER_NUM; i++) {
		if (interval == mib_read_max[i])
			mib_start[index++] = i;
	}
	return index;
}  /* sw_fill_mib_index */

static void sw_setup_mib(struct ksz_sw *sw)
{
	int i;
	int j;
	u8 index = 0;

	for (i = 0; i < 3; i++) {
		j = 2 - i;
		sw->mib_interval_start[j] = index;
		index = sw_fill_mib_index(sw, index, 1 << j);
	}
	memcpy(mib_index, mib_start, SWITCH_COUNTER_NUM);
	j = MIB_9897_RX_BYTE_CNT;
	for (i = 0; i < 4; i++, j++, index++) {
		mib_start[index] = SWITCH_COUNTER_NUM + i;
		mib_index[index] = j;
	}
}  /* sw_setup_mib */

static void get_mib_cnt_info(u64 *cnt, u32 data[])
{
	u64 num;

	if (data[0] & MIB_COUNTER_OVERFLOW) {
		num = 1;
		num <<= 32 + 4;
		*cnt += num;
	}
	num = (data[0] & MIB_COUNTER_DATA_HI_M);
	num <<= 32;
	num |= data[1];
	*cnt += num;
}  /* get_mib_cnt_info */

/**
 * sw_r_mib_cnt_hw - read MIB counters using default access
 * @sw:		The switch instance.
 * @port:	The port index.
 * @addr:	The addresses of the counters.
 * @num:	Number of entries to read.
 * @data:	Buffer to store the counters.
 *
 * This routine reads MIB counters of the port using default access.
 */
static void sw_r_mib_cnt_hw(struct ksz_sw *sw, int port, u32 addr[], int num,
	u32 data[])
{
	int i;
	u32 ctrl_addr;

	for (i = 0; i < num; i++) {
		ctrl_addr = (addr[i] & MIB_COUNTER_INDEX_M);
		ctrl_addr <<= MIB_COUNTER_INDEX_S;
		ctrl_addr |= MIB_COUNTER_READ;

#if 1
		/*
		 * First KSZ956X revision chip has a bug that writing 32-bit
		 * data to the register does not trigger the read operation.
		 */
		port_w16(sw, port, REG_PORT_MIB_CTRL_STAT__4, ctrl_addr >> 16);
#else
		port_w32(sw, port, REG_PORT_MIB_CTRL_STAT__4, ctrl_addr);
#endif
		/*
		 * Need to check the valid bit, but SPI access is slow enough
		 * to have that bit always set when reading.
		 */
		do {
			port_get(sw, port, REG_PORT_MIB_CTRL_STAT__4, data, 8);

			data[0] = be32_to_cpu(data[0]);
#ifndef NO_PHY_READ
			if (!(data[0] & MIB_COUNTER_VALID))
				dbg_msg(" !valid: %08x\n", data[0]);
#endif
			data[1] = be32_to_cpu(data[1]);
		} while (!(data[0] & MIB_COUNTER_VALID));
		data += READ_MIB_ENTRY_SIZE;
	}
}  /* sw_r_mib_cnt_hw */

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
	u32 index[MAX_IBA_MIB_ENTRIES];
	u32 data[MAX_IBA_MIB_ENTRIES * READ_MIB_ENTRY_SIZE];
	u8 start;
	int cnt;
	int i;

#if defined(NO_DIRECT_ACCESS)
if (!sw->info->iba.use_iba) {
printk("%s\n", __func__);
return 0;
}
#endif
	/* First read in this interval. */
	if (!mib->cnt_ptr) {
		u8 interval;

		++mib->interval;
		switch (mib->interval) {
		case 2:
			interval = 1;
			break;
		case 4:
			interval = 2;
			mib->interval = 0;
			break;
		default:
			interval = 0;
		}

		/* Determine the starting index in this interval. */
		mib->cnt_ptr = sw->mib_interval_start[interval];
	}
	while (mib->cnt_ptr < TOTAL_SWITCH_COUNTER_NUM) {
		cnt = MAX_IBA_MIB_ENTRIES;
		if (cnt > TOTAL_SWITCH_COUNTER_NUM - mib->cnt_ptr)
			cnt = TOTAL_SWITCH_COUNTER_NUM - mib->cnt_ptr;
		for (i = 0; i < cnt; i++)
			index[i] = mib_index[mib->cnt_ptr + i];
		sw->ops->acquire(sw);
		sw->reg->r_mib_cnt_hw(sw, port, index, cnt, data);
		sw->ops->release(sw);
		for (i = 0; i < cnt; i++, mib->cnt_ptr++) {
			start = mib_start[mib->cnt_ptr];
			get_mib_cnt_info(&mib->counter[start],
				&data[i * READ_MIB_ENTRY_SIZE]);
		}
		if (exit_mib_read(sw))
			return mib->cnt_ptr;
	}
	mib->cnt_ptr = 0;
	return 0;
}  /* port_r_cnt */

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
	u32 index[MAX_IBA_MIB_ENTRIES];
	u32 data[MAX_IBA_MIB_ENTRIES * READ_MIB_ENTRY_SIZE];
	int cnt;
	int i;

#if defined(NO_DIRECT_ACCESS)
if (!sw->info->iba.use_iba) {
printk("%s\n", __func__);
return;
}
#endif
	sw->ops->acquire(sw);
	mib->cnt_ptr = 0;
	mib->interval = 0;
	do {
		cnt = MAX_IBA_MIB_ENTRIES;
		if (cnt > TOTAL_SWITCH_COUNTER_NUM - mib->cnt_ptr)
			cnt = TOTAL_SWITCH_COUNTER_NUM - mib->cnt_ptr;
		for (i = 0; i < cnt; i++, mib->cnt_ptr++)
			index[i] = mib_index[mib->cnt_ptr];
		sw->reg->r_mib_cnt_hw(sw, port, index, cnt, data);
	} while (mib->cnt_ptr < TOTAL_SWITCH_COUNTER_NUM);
	memset((void *) mib->counter, 0, sizeof(u64) *
		TOTAL_SWITCH_COUNTER_NUM);
	mib->cnt_ptr = 0;
	sw->ops->release(sw);
}  /* port_init_cnt */

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
	for (port = 0; port < sw->mib_port_cnt; port++)
		sw_ena_broad_storm(sw, port);
	sw_cfg(sw, REG_SW_MAC_CTRL_1, MULTICAST_STORM_DISABLE, 1);
}  /* sw_setup_broad_storm */

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

static void hw_cfg_in_packet_based(struct ksz_sw *sw, int port, int set)
{
	sw->info->port_cfg[port].packet_based = set;
	hw_cfg_rate_limit(sw, port, 1, PORT_IN_PACKET_BASED_S, set != 0);
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
		PORT_IN_PACKET_BASED_S) & 1;
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
 * sw_chk_prio_rate - check switch priority rate
 * @sw:		The switch instance.
 * @port:	The port index.
 *
 * This function checks whether the priority rate function of the switch is
 * enabled.
 *
 * Return 0 if not enabled.
 */
static int sw_chk_prio_rate(struct ksz_sw *sw, int port)
{
	u32 addr;
	u32 rate_addr;
	u32 in_rate0;
	u32 in_rate1;
	u32 out_rate;

	addr = PORT_CTRL_ADDR(port, 0);
	rate_addr = addr + REG_PORT_IN_RATE_0;
	in_rate0 = sw->reg->r32(sw, rate_addr);
	in_rate1 = sw->reg->r32(sw, rate_addr + 4);
	rate_addr = addr + REG_PORT_OUT_RATE_0;
	out_rate = sw->reg->r32(sw, rate_addr);
	return (in_rate0 | in_rate1 | out_rate) != 0;
}  /* sw_chk_prio_rate */

/**
 * sw_dis_prio_rate - disable switch priority rate
 * @sw:		The switch instance.
 * @port:	The port index.
 *
 * This routine disables the priority rate function of the switch.
 */
static void sw_dis_prio_rate(struct ksz_sw *sw, int port)
{
	u32 addr;
	u32 rate_addr;

	addr = PORT_CTRL_ADDR(port, 0);
	rate_addr = addr + REG_PORT_IN_RATE_0;
	sw->reg->w32(sw, rate_addr, 0);
	sw->reg->w32(sw, rate_addr + 4, 0);
	rate_addr = addr + REG_PORT_OUT_RATE_0;
	sw->reg->w32(sw, rate_addr, 0);
}  /* sw_dis_prio_rate */

/**
 * sw_ena_prio_rate - enable switch priority rate
 * @sw:		The switch instance.
 * @port:	The port index.
 *
 * This routine enables the priority rate function of the switch.
 */
static void sw_ena_prio_rate(struct ksz_sw *sw, int port)
{
	int prio;

	for (prio = 0; prio < PRIO_QUEUES; prio++) {
		hw_cfg_rx_prio_rate(sw, port, prio,
			sw->info->port_cfg[port].rx_rate[prio]);
		hw_cfg_tx_prio_rate(sw, port, prio,
			sw->info->port_cfg[port].tx_rate[prio]);
	}
	for (; prio < RX_PRIO_QUEUES; prio++)
		hw_cfg_rx_prio_rate(sw, port, prio,
			sw->info->port_cfg[port].rx_rate[prio]);
}  /* sw_ena_prio_rate */

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

	for (port = 0; port < sw->mib_port_cnt; port++) {
		hw_get_rate_limit(sw, port);
		for (prio = 0; prio < RX_PRIO_QUEUES; prio++) {
			offset = REG_PORT_IN_RATE_0;
			port_get_rate(sw, port, prio, offset,
				&sw->info->port_cfg[port].rx_rate[prio],
				&sw->info->port_cfg[port].rx_packet[prio]);
		}
		for (prio = 0; prio < PRIO_QUEUES; prio++) {
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
		REG_PORT_MAC_CTRL_1, PORT_BACK_PRESSURE, set);
}

static inline void port_cfg_force_flow_ctrl(struct ksz_sw *sw, int p, int set)
{
	port_cfg(sw, p,
		REG_PORT_CTRL_0,
		PORT_FORCE_TX_FLOW_CTRL | PORT_FORCE_RX_FLOW_CTRL, set);
}

static inline void port_cfg_tail_tag(struct ksz_sw *sw, int p, int set)
{
	port_cfg(sw, p,
		REG_PORT_CTRL_0, PORT_TAIL_TAG_ENABLE, set);
}

static inline int port_chk_back_pressure(struct ksz_sw *sw, int p)
{
	return port_chk(sw, p,
		REG_PORT_MAC_CTRL_1, PORT_BACK_PRESSURE);
}

static inline int port_chk_force_flow_ctrl(struct ksz_sw *sw, int p)
{
	return port_chk(sw, p,
		REG_PORT_CTRL_0,
		PORT_FORCE_TX_FLOW_CTRL | PORT_FORCE_RX_FLOW_CTRL);
}

static inline int port_chk_tail_tag(struct ksz_sw *sw, int p)
{
	return port_chk(sw, p,
		REG_PORT_CTRL_0, PORT_TAIL_TAG_ENABLE);
}

/* -------------------------------------------------------------------------- */

/* Spanning Tree */

static inline void port_cfg_mstp(struct ksz_sw *sw, int p, u8 mstp)
{
	port_w(sw, p, REG_PORT_LUE_MSTP_INDEX, mstp);
}

static inline void port_cfg_dis_learn(struct ksz_sw *sw, int p, int set)
{
	port_cfg(sw, p,
		P_STP_CTRL, PORT_LEARN_DISABLE, set);
}

static inline void port_cfg_rx(struct ksz_sw *sw, int p, int set)
{
	SW_D mstp;

	port_r(sw, p, REG_PORT_LUE_MSTP_INDEX, &mstp);
	port_cfg(sw, p,
		P_STP_CTRL, PORT_RX_ENABLE, set);
	if (mstp)
		return;
	if (set)
		sw->rx_ports |= (1 << p);
	else
		sw->rx_ports &= ~(1 << p);
}

static inline void port_cfg_tx(struct ksz_sw *sw, int p, int set)
{
	SW_D mstp;

	port_r(sw, p, REG_PORT_LUE_MSTP_INDEX, &mstp);
	port_cfg(sw, p,
		P_STP_CTRL, PORT_TX_ENABLE, set);
	if (mstp)
		return;
	if (set)
		sw->tx_ports |= (1 << p);
	else
		sw->tx_ports &= ~(1 << p);
}

static inline u8 port_chk_mstp(struct ksz_sw *sw, int p)
{
	SW_D mstp;

	port_r(sw, p, REG_PORT_LUE_MSTP_INDEX, &mstp);
	return mstp;
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
	sw_cfg(sw, REG_SW_LUE_CTRL_1, SW_FAST_AGING, set);
}

static void sw_flush_dyn_mac_table(struct ksz_sw *sw, int port)
{
	int cnt;
	int first;
	int index;
	int learn_disable[TOTAL_PORT_NUM];
	SW_D data;

	data = SW_R(sw, REG_SW_LUE_CTRL_2);
	data &= ~(SW_FLUSH_OPTION_M << SW_FLUSH_OPTION_S);
	data |= (SW_FLUSH_OPTION_DYN_MAC << SW_FLUSH_OPTION_S);
	SW_W(sw, REG_SW_LUE_CTRL_2, data);
	if (port < sw->mib_port_cnt) {
		first = port;
		cnt = port + 1;
		for (index = first; index < cnt; index++) {
			learn_disable[index] = port_chk_dis_learn(sw, index);
			if (!learn_disable[index])
				port_cfg_dis_learn(sw, index, 1);
		}
		sw_cfg(sw, S_FLUSH_TABLE_CTRL, SW_FLUSH_DYN_MAC_TABLE, 1);
		for (index = first; index < cnt; index++) {
			if (!learn_disable[index])
				port_cfg_dis_learn(sw, index, 0);
		}
	} else {
		first = 0;
		cnt = sw->mib_port_cnt;
		sw_cfg(sw, S_FLUSH_TABLE_CTRL, SW_FLUSH_STP_TABLE, 1);
	}
}

/* -------------------------------------------------------------------------- */

/* VLAN */

static inline void port_cfg_drop_non_vlan(struct ksz_sw *sw, int p, int set)
{
	port_cfg(sw, p,
		REG_PORT_MRI_MAC_CTRL, PORT_DROP_NON_VLAN, set);
}

/**
 * port_cfg_drop_tag - configure 802.1q tagged packet drop
 * @sw:		The switch instance.
 * @port:	The port index.
 * @set:	The flag to disable or enable.
 *
 */
static inline void port_cfg_drop_tag(struct ksz_sw *sw, int p, int set)
{
	port_cfg(sw, p,
		REG_PORT_MRI_MAC_CTRL, PORT_DROP_TAG, set);
}

static inline int port_chk_drop_non_vlan(struct ksz_sw *sw, int p)
{
	return port_chk(sw, p,
		REG_PORT_MRI_MAC_CTRL, PORT_DROP_NON_VLAN);
}

static inline int port_chk_drop_tag(struct ksz_sw *sw, int p)
{
	return port_chk(sw, p,
		REG_PORT_MRI_MAC_CTRL, PORT_DROP_TAG);
}

/**
 * port_cfg_dis_non_vid - configure discard non VID
 * @sw:		The switch instance.
 * @port:	The port index.
 * @set:	The flag to disable or enable.
 *
 * This routine configures Discard Non VID packets of the switch port.
 * If enabled, the device will discard packets whose VLAN id does not match
 * ingress port-based default VLAN id.
 */
static inline void port_cfg_dis_non_vid(struct ksz_sw *sw, int p, int set)
{
	port_cfg(sw, p,
		REG_PORT_LUE_CTRL, PORT_DISCARD_NON_VID, set);
}  /* port_cfg_dis_non_vid */

/**
 * port_cfg_in_filter - configure ingress VLAN filtering
 * @sw:		The switch instance.
 * @port:	The port index.
 * @set:	The flag to disable or enable.
 *
 * This routine configures Ingress VLAN filtering of the switch port.
 * If enabled, the device will discard packets whose VLAN id membership	in the
 * VLAN table receive ports does not include the ingress port that received
 * this packet.
 */
static inline void port_cfg_in_filter(struct ksz_sw *sw, int p, int set)
{
	port_cfg(sw, p,
		REG_PORT_LUE_CTRL, PORT_INGRESS_FILTER, set);
}  /* port_cfg_in_filter */

static inline int port_chk_dis_non_vid(struct ksz_sw *sw, int p)
{
	return port_chk(sw, p,
		REG_PORT_LUE_CTRL, PORT_DISCARD_NON_VID);
}

static inline int port_chk_in_filter(struct ksz_sw *sw, int p)
{
	return port_chk(sw, p,
		REG_PORT_LUE_CTRL, PORT_INGRESS_FILTER);
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
	for (port = 0; port < sw->mib_port_cnt; port++) {
		port_cfg_mirror_sniffer(sw, port, 0);
		port_cfg_mirror_rx(sw, port, 0);
		port_cfg_mirror_tx(sw, port, 0);
	}
	sw_cfg_mirror_rx_tx(sw, 0);
}

/* -------------------------------------------------------------------------- */

/* Priority */

static inline void port_cfg_diffserv(struct ksz_sw *sw, int p, int set)
{
	port_cfg(sw, p,
		P_PRIO_CTRL, PORT_DIFFSERV_PRIO_ENABLE, set);
}

static inline void port_cfg_802_1p(struct ksz_sw *sw, int p, int set)
{
	port_cfg(sw, p,
		P_PRIO_CTRL, PORT_802_1P_PRIO_ENABLE, set);
}

static inline void port_cfg_vlan_prio(struct ksz_sw *sw, int p, int set)
{
	port_cfg(sw, p,
		P_PRIO_CTRL, PORT_VLAN_PRIO_ENABLE, set);
}

static inline void port_cfg_mac_prio(struct ksz_sw *sw, int p, int set)
{
	port_cfg(sw, p,
		P_PRIO_CTRL, PORT_MAC_PRIO_ENABLE, set);
}

static inline void port_cfg_acl_prio(struct ksz_sw *sw, int p, int set)
{
	port_cfg(sw, p,
		P_PRIO_CTRL, PORT_ACL_PRIO_ENABLE, set);
}

static inline void port_cfg_highest_prio(struct ksz_sw *sw, int p, int set)
{
	port_cfg(sw, p,
		P_PRIO_CTRL, PORT_HIGHEST_PRIO, set);
}

static inline void port_cfg_or_prio(struct ksz_sw *sw, int p, int set)
{
	port_cfg(sw, p,
		P_PRIO_CTRL, PORT_OR_PRIO, set);
}

static inline void port_cfg_replace_prio(struct ksz_sw *sw, int p, int set)
{
	port_cfg(sw, p,
		REG_PORT_MRI_MAC_CTRL, PORT_USER_PRIO_CEILING, set);
}

static inline void port_cfg_prio(struct ksz_sw *sw, int p, int set)
{
	port_w_s(sw, p,
		REG_PORT_CTRL_0, PORT_QUEUE_SPLIT_ENABLE, 0, set);
}

static inline int port_chk_diffserv(struct ksz_sw *sw, int p)
{
	return port_chk(sw, p,
		P_PRIO_CTRL, PORT_DIFFSERV_PRIO_ENABLE);
}

static inline int port_chk_802_1p(struct ksz_sw *sw, int p)
{
	return port_chk(sw, p,
		P_PRIO_CTRL, PORT_802_1P_PRIO_ENABLE);
}

static inline int port_chk_vlan_prio(struct ksz_sw *sw, int p)
{
	return port_chk(sw, p,
		P_PRIO_CTRL, PORT_VLAN_PRIO_ENABLE);
}

static inline int port_chk_mac_prio(struct ksz_sw *sw, int p)
{
	return port_chk(sw, p,
		P_PRIO_CTRL, PORT_MAC_PRIO_ENABLE);
}

static inline int port_chk_acl_prio(struct ksz_sw *sw, int p)
{
	return port_chk(sw, p,
		P_PRIO_CTRL, PORT_ACL_PRIO_ENABLE);
}

static inline int port_chk_highest_prio(struct ksz_sw *sw, int p)
{
	return port_chk(sw, p,
		P_PRIO_CTRL, PORT_HIGHEST_PRIO);
}

static inline int port_chk_or_prio(struct ksz_sw *sw, int p)
{
	return port_chk(sw, p,
		P_PRIO_CTRL, PORT_OR_PRIO);
}

static inline int port_chk_replace_prio(struct ksz_sw *sw, int p)
{
	return port_chk(sw, p,
		REG_PORT_MRI_MAC_CTRL, PORT_USER_PRIO_CEILING);
}

static inline int port_chk_prio(struct ksz_sw *sw, int p)
{
	return port_r_s(sw, p,
		REG_PORT_CTRL_0, PORT_QUEUE_SPLIT_ENABLE, 0);
}

/* -------------------------------------------------------------------------- */

/* Policing */

static void port_cfg_index(struct ksz_sw *sw, int port, int p, int q)
{
	u32 data;

	data = (p & MRI_INDEX_P_M) << MRI_INDEX_P_S;
	data |= (q & MRI_INDEX_Q_M) << MRI_INDEX_Q_S;
	port_w32(sw, port, REG_PORT_MRI_INDEX__4, data);
}

static inline void port_cfg_police(struct ksz_sw *sw, int p, int set)
{
	port_cfg32(sw, p,
		REG_PORT_MRI_POLICE_CTRL__4, POLICE_ENABLE, set);
}

static inline void port_cfg_color_aware(struct ksz_sw *sw, int p, int set)
{
	port_cfg32(sw, p,
		REG_PORT_MRI_POLICE_CTRL__4, POLICE_COLOR_NOT_AWARE, !set);
}

static inline void port_cfg_drop_srp(struct ksz_sw *sw, int p, int set)
{
	port_cfg32(sw, p,
		REG_PORT_MRI_POLICE_CTRL__4, POLICE_DROP_SRP, set);
}

static inline void port_cfg_color_mark(struct ksz_sw *sw, int p, int set)
{
	port_cfg32(sw, p,
		REG_PORT_MRI_POLICE_CTRL__4, COLOR_MARK_ENABLE, set);
}

static inline void port_cfg_color_remap(struct ksz_sw *sw, int p, int set)
{
	port_cfg32(sw, p,
		REG_PORT_MRI_POLICE_CTRL__4, COLOR_REMAP_ENABLE, set);
}

static inline void port_cfg_port_based_policing(struct ksz_sw *sw, int p,
	int set)
{
	port_cfg32(sw, p,
		REG_PORT_MRI_POLICE_CTRL__4, PORT_BASED_POLICING, set);
}

static inline void port_cfg_police_drop_all(struct ksz_sw *sw, int p, int set)
{
	port_cfg32(sw, p,
		REG_PORT_MRI_POLICE_CTRL__4, POLICE_DROP_ALL, set);
}

static inline void port_set_police_packet_type(struct ksz_sw *sw, int p,
	u32 type)
{
	port_w_s_32(sw, p,
		REG_PORT_MRI_POLICE_CTRL__4, POLICE_PACKET_TYPE_M,
			POLICE_PACKET_TYPE_S, type);
}

static inline void port_set_non_dscp_color(struct ksz_sw *sw, int p, u32 color)
{
	port_w_s_32(sw, p,
		REG_PORT_MRI_POLICE_CTRL__4, SW_COLOR_M,
			NON_DSCP_COLOR_S, color);
}

static inline int port_chk_police(struct ksz_sw *sw, int p)
{
	return port_chk32(sw, p,
		REG_PORT_MRI_POLICE_CTRL__4, POLICE_ENABLE);
}

static inline int port_chk_color_aware(struct ksz_sw *sw, int p)
{
	return !port_chk32(sw, p,
		REG_PORT_MRI_POLICE_CTRL__4, POLICE_COLOR_NOT_AWARE);
}

static inline int port_chk_drop_srp(struct ksz_sw *sw, int p)
{
	return port_chk32(sw, p,
		REG_PORT_MRI_POLICE_CTRL__4, POLICE_DROP_SRP);
}

static inline int port_chk_color_mark(struct ksz_sw *sw, int p)
{
	return port_chk32(sw, p,
		REG_PORT_MRI_POLICE_CTRL__4, COLOR_MARK_ENABLE);
}

static inline int port_chk_color_remap(struct ksz_sw *sw, int p)
{
	return port_chk32(sw, p,
		REG_PORT_MRI_POLICE_CTRL__4, COLOR_REMAP_ENABLE);
}

static inline int port_chk_port_based_policing(struct ksz_sw *sw, int p)
{
	return port_chk32(sw, p,
		REG_PORT_MRI_POLICE_CTRL__4, PORT_BASED_POLICING);
}

static inline int port_chk_police_drop_all(struct ksz_sw *sw, int p)
{
	return port_chk32(sw, p,
		REG_PORT_MRI_POLICE_CTRL__4, POLICE_DROP_ALL);
}

static inline u32 port_get_police_packet_type(struct ksz_sw *sw, int p)
{
	return port_r_s_32(sw, p,
		REG_PORT_MRI_POLICE_CTRL__4, POLICE_PACKET_TYPE_M,
			POLICE_PACKET_TYPE_S);
}

static inline u32 port_get_non_dscp_color(struct ksz_sw *sw, int p)
{
	return port_r_s_32(sw, p,
		REG_PORT_MRI_POLICE_CTRL__4, SW_COLOR_M,
			NON_DSCP_COLOR_S);
}

static inline u16 port_get_cir(struct ksz_sw *sw, int p)
{
	return port_r_s_32(sw, p,
		REG_PORT_POLICE_RATE__4, 0xffff, POLICE_CIR_S);
}

static inline u16 port_get_pir(struct ksz_sw *sw, int p)
{
	return port_r_s_32(sw, p,
		REG_PORT_POLICE_RATE__4, 0xffff, POLICE_PIR_S);
}

static inline void port_set_cir(struct ksz_sw *sw, int p, u16 rate)
{
	port_w_s_32(sw, p,
		REG_PORT_POLICE_RATE__4, 0xffff, POLICE_CIR_S, rate);
}

static inline void port_set_pir(struct ksz_sw *sw, int p, u16 rate)
{
	port_w_s_32(sw, p,
		REG_PORT_POLICE_RATE__4, 0xffff, POLICE_PIR_S, rate);
}

static inline u16 port_get_cbs(struct ksz_sw *sw, int p)
{
	return port_r_s_32(sw, p,
		REG_PORT_POLICE_BURST_SIZE__4, POLICE_BURST_SIZE_M,
			POLICE_CBS_S);
}

static inline u16 port_get_pbs(struct ksz_sw *sw, int p)
{
	return port_r_s_32(sw, p,
		REG_PORT_POLICE_BURST_SIZE__4, POLICE_BURST_SIZE_M,
			POLICE_PBS_S);
}

static inline void port_set_cbs(struct ksz_sw *sw, int p, u16 size)
{
	port_w_s_32(sw, p,
		REG_PORT_POLICE_BURST_SIZE__4, POLICE_BURST_SIZE_M,
			POLICE_CBS_S, size);
}

static inline void port_set_pbs(struct ksz_sw *sw, int p, u16 size)
{
	port_w_s_32(sw, p,
		REG_PORT_POLICE_BURST_SIZE__4, POLICE_BURST_SIZE_M,
			POLICE_PBS_S, size);
}

static inline u16 port_get_wred_max(struct ksz_sw *sw, int p)
{
	return port_r_s_32(sw, p,
		REG_PORT_WRED_PM_CTRL_0__4, WRED_PM_CTRL_M,
			WRED_PM_MAX_THRESHOLD_S);
}

static inline u16 port_get_wred_min(struct ksz_sw *sw, int p)
{
	return port_r_s_32(sw, p,
		REG_PORT_WRED_PM_CTRL_0__4, WRED_PM_CTRL_M,
			WRED_PM_MIN_THRESHOLD_S);
}

static inline u16 port_get_wred_multiplier(struct ksz_sw *sw, int p)
{
	return port_r_s_32(sw, p,
		REG_PORT_WRED_PM_CTRL_1__4, WRED_PM_CTRL_M,
			WRED_PM_MULTIPLIER_S);
}

static inline u16 port_get_wred_avg_size(struct ksz_sw *sw, int p)
{
	return port_r_s_32(sw, p,
		REG_PORT_WRED_PM_CTRL_1__4, WRED_PM_CTRL_M,
			WRED_PM_AVG_QUEUE_SIZE_S);
}

static inline void port_set_wred_max(struct ksz_sw *sw, int p, u16 threshold)
{
	port_w_s_32(sw, p,
		REG_PORT_WRED_PM_CTRL_0__4, WRED_PM_CTRL_M,
			WRED_PM_MAX_THRESHOLD_S, threshold);
}

static inline void port_set_wred_min(struct ksz_sw *sw, int p, u16 threshold)
{
	port_w_s_32(sw, p,
		REG_PORT_WRED_PM_CTRL_0__4, WRED_PM_CTRL_M,
			WRED_PM_MIN_THRESHOLD_S, threshold);
}

static inline void port_set_wred_multiplier(struct ksz_sw *sw, int p, u16 val)
{
	port_w_s_32(sw, p,
		REG_PORT_WRED_PM_CTRL_1__4, WRED_PM_CTRL_M,
			WRED_PM_MULTIPLIER_S, val);
}

static inline u16 port_get_wred_q_max(struct ksz_sw *sw, int p)
{
	return port_r_s_32(sw, p,
		REG_PORT_WRED_QUEUE_CTRL_0__4, WRED_PM_CTRL_M,
			WRED_PM_MAX_THRESHOLD_S);
}

static inline u16 port_get_wred_q_min(struct ksz_sw *sw, int p)
{
	return port_r_s_32(sw, p,
		REG_PORT_WRED_QUEUE_CTRL_0__4, WRED_PM_CTRL_M,
			WRED_PM_MIN_THRESHOLD_S);
}

static inline u16 port_get_wred_q_multiplier(struct ksz_sw *sw, int p)
{
	return port_r_s_32(sw, p,
		REG_PORT_WRED_QUEUE_CTRL_1__4, WRED_PM_CTRL_M,
			WRED_PM_MULTIPLIER_S);
}

static inline u16 port_get_wred_q_avg_size(struct ksz_sw *sw, int p)
{
	return port_r_s_32(sw, p,
		REG_PORT_WRED_QUEUE_CTRL_1__4, WRED_PM_CTRL_M,
			WRED_PM_AVG_QUEUE_SIZE_S);
}

static inline void port_set_wred_q_max(struct ksz_sw *sw, int p, u16 threshold)
{
	port_w_s_32(sw, p,
		REG_PORT_WRED_QUEUE_CTRL_0__4, WRED_PM_CTRL_M,
			WRED_PM_MAX_THRESHOLD_S, threshold);
}

static inline void port_set_wred_q_min(struct ksz_sw *sw, int p, u16 threshold)
{
	port_w_s_32(sw, p,
		REG_PORT_WRED_QUEUE_CTRL_0__4, WRED_PM_CTRL_M,
			WRED_PM_MIN_THRESHOLD_S, threshold);
}

static inline void port_set_wred_q_multiplier(struct ksz_sw *sw, int p, u16 val)
{
	port_w_s_32(sw, p,
		REG_PORT_WRED_QUEUE_CTRL_1__4, WRED_PM_CTRL_M,
			WRED_PM_MULTIPLIER_S, val);
}

static inline void port_cfg_wred_random_drop(struct ksz_sw *sw, int p, int set)
{
	port_cfg32(sw, p,
		REG_PORT_WRED_QUEUE_PMON__4, WRED_RANDOM_DROP_ENABLE, set);
}

static inline void port_cfg_wred_drop_gyr(struct ksz_sw *sw, int p, int set)
{
	port_cfg32(sw, p,
		REG_PORT_WRED_QUEUE_PMON__4, WRED_DROP_GYR_DISABLE, !set);
}

static inline void port_cfg_wred_drop_yr(struct ksz_sw *sw, int p, int set)
{
	port_cfg32(sw, p,
		REG_PORT_WRED_QUEUE_PMON__4, WRED_DROP_YR_DISABLE, !set);
}

static inline void port_cfg_wred_drop_r(struct ksz_sw *sw, int p, int set)
{
	port_cfg32(sw, p,
		REG_PORT_WRED_QUEUE_PMON__4, WRED_DROP_R_DISABLE, !set);
}

static inline void port_cfg_wred_drop_all(struct ksz_sw *sw, int p, int set)
{
	port_cfg32(sw, p,
		REG_PORT_WRED_QUEUE_PMON__4, WRED_DROP_ALL, set);
}

static inline int port_chk_wred_random_drop(struct ksz_sw *sw, int p)
{
	return port_chk32(sw, p,
		REG_PORT_WRED_QUEUE_PMON__4, WRED_RANDOM_DROP_ENABLE);
}

static inline int port_chk_wred_drop_gyr(struct ksz_sw *sw, int p)
{
	return !port_chk32(sw, p,
		REG_PORT_WRED_QUEUE_PMON__4, WRED_DROP_GYR_DISABLE);
}

static inline int port_chk_wred_drop_yr(struct ksz_sw *sw, int p)
{
	return !port_chk32(sw, p,
		REG_PORT_WRED_QUEUE_PMON__4, WRED_DROP_YR_DISABLE);
}

static inline int port_chk_wred_drop_r(struct ksz_sw *sw, int p)
{
	return !port_chk32(sw, p,
		REG_PORT_WRED_QUEUE_PMON__4, WRED_DROP_R_DISABLE);
}

static inline int port_chk_wred_drop_all(struct ksz_sw *sw, int p)
{
	return port_chk32(sw, p,
		REG_PORT_WRED_QUEUE_PMON__4, WRED_DROP_ALL);
}

static u32 port_get_wred_pmon(struct ksz_sw *sw, int p)
{
	return port_r_s_32(sw, p,
		REG_PORT_WRED_QUEUE_PMON__4, WRED_PMON_M, 0);
}

/* -------------------------------------------------------------------------- */

/* Rate Control */

#ifdef MTI_PREEMPT_ENABLE
static inline void port_cfg_preempt(struct ksz_sw *sw, int p, int q, int set)
{
	port_w32(sw, p, REG_PORT_MTI_QUEUE_INDEX__4, q);
	port_cfg(sw, p,
		REG_PORT_MTI_QUEUE_CTRL_0, MTI_PREEMPT_ENABLE, set);
}

static inline int port_chk_preempt(struct ksz_sw *sw, int p, int q)
{
	port_w32(sw, p, REG_PORT_MTI_QUEUE_INDEX__4, q);
	return port_chk(sw, p,
		REG_PORT_MTI_QUEUE_CTRL_0, MTI_PREEMPT_ENABLE);
}
#endif

static inline u8 port_get_schedule_mode(struct ksz_sw *sw, int p, int q)
{
	port_w32(sw, p, REG_PORT_MTI_QUEUE_INDEX__4, q);
	return port_r_s(sw, p,
		REG_PORT_MTI_QUEUE_CTRL_0, MTI_SCHEDULE_MODE_M,
			MTI_SCHEDULE_MODE_S);
}

static inline u8 port_get_shaping(struct ksz_sw *sw, int p, int q)
{
	port_w32(sw, p, REG_PORT_MTI_QUEUE_INDEX__4, q);
	return port_r_s(sw, p,
		REG_PORT_MTI_QUEUE_CTRL_0, MTI_SHAPING_M,
			MTI_SHAPING_S);
}

static inline u8 port_get_tx_ratio(struct ksz_sw *sw, int p, int q)
{
	u8 data;

	port_w32(sw, p, REG_PORT_MTI_QUEUE_INDEX__4, q);
	port_r(sw, p, REG_PORT_MTI_QUEUE_CTRL_1, &data);
	return data;
}

/**
 * port_set_schedule_mode - configure port rate control
 * @sw:		The switch instance.
 * @p:		The port index.
 * @q:		The priority queue.
 * @mode:	The schedule mode to specify strict priority or WRR.
 *
 * This routine configures the priority queue rate control of the port.
 */
static inline void port_set_schedule_mode(struct ksz_sw *sw, int p, int q,
	u8 mode)
{
	port_w32(sw, p, REG_PORT_MTI_QUEUE_INDEX__4, q);
	port_w_s(sw, p,
		REG_PORT_MTI_QUEUE_CTRL_0, MTI_SCHEDULE_MODE_M,
			MTI_SCHEDULE_MODE_S, mode);
}  /* port_set_schedule_mode */

static inline void port_set_shaping(struct ksz_sw *sw, int p, int q,
	u8 shaping)
{
	port_w32(sw, p, REG_PORT_MTI_QUEUE_INDEX__4, q);
	port_w_s(sw, p,
		REG_PORT_MTI_QUEUE_CTRL_0, MTI_SHAPING_M,
			MTI_SHAPING_S, shaping);
}

/**
 * port_set_tx_ratio - configure port rate ratio
 * @sw:		The switch instance.
 * @p:		The port index.
 * @q:		The priority queue.
 * @ratio:	The rate ratio.
 *
 * This routine configures the priority queue rate ratio of the port.
 */
static inline void port_set_tx_ratio(struct ksz_sw *sw, int p, int q, u8 ratio)
{
	port_w32(sw, p, REG_PORT_MTI_QUEUE_INDEX__4, q);
	port_w(sw, p, REG_PORT_MTI_QUEUE_CTRL_1, ratio & MTI_TX_RATIO_M);
}  /* port_set_tx_ratio */

static u16 port_get_hi_water_mark(struct ksz_sw *sw, int p, int q)
{
	u16 data;

	port_w32(sw, p, REG_PORT_MTI_QUEUE_INDEX__4, q);
	port_r16(sw, p, REG_PORT_MTI_QUEUE_CTRL_2__2, &data);
	return data;
}

static u16 port_get_lo_water_mark(struct ksz_sw *sw, int p, int q)
{
	u16 data;

	port_w32(sw, p, REG_PORT_MTI_QUEUE_INDEX__4, q);
	port_r16(sw, p, REG_PORT_MTI_QUEUE_CTRL_3__2, &data);
	return data;
}

static u16 port_get_increment(struct ksz_sw *sw, int p, int q)
{
	u16 data;

	port_w32(sw, p, REG_PORT_MTI_QUEUE_INDEX__4, q);
	port_r16(sw, p, REG_PORT_MTI_QUEUE_CTRL_4__2, &data);
	return data;
}

static u8 port_get_srp(struct ksz_sw *sw, int p)
{
	u8 data;

	port_r(sw, p, REG_PORT_CTRL_1, &data);
	return data & PORT_SRP_ENABLE;
}

static void port_set_hi_water_mark(struct ksz_sw *sw, int p, int q, u16 val)
{
	port_w32(sw, p, REG_PORT_MTI_QUEUE_INDEX__4, q);
	port_w16(sw, p, REG_PORT_MTI_QUEUE_CTRL_2__2, val);
}

static void port_set_lo_water_mark(struct ksz_sw *sw, int p, int q, u16 val)
{
	port_w32(sw, p, REG_PORT_MTI_QUEUE_INDEX__4, q);
	port_w16(sw, p, REG_PORT_MTI_QUEUE_CTRL_3__2, val);
}

static void port_set_increment(struct ksz_sw *sw, int p, int q, u16 val)
{
	port_w32(sw, p, REG_PORT_MTI_QUEUE_INDEX__4, q);
	port_w16(sw, p, REG_PORT_MTI_QUEUE_CTRL_4__2, val);
}

static void port_set_srp(struct ksz_sw *sw, int p, u8 srp)
{
	port_w(sw, p, REG_PORT_CTRL_1, srp & PORT_SRP_ENABLE);
}

#ifdef KSZ_MRP
#include "ksz_mrp.c"
#endif

/* -------------------------------------------------------------------------- */

/* Queue Management */

static inline u8 port_get_qm_drop(struct ksz_sw *sw, int p)
{
	return (u8) port_r_s_32(sw, p, REG_PORT_QM_CTRL__4,
		PORT_QM_DROP_PRIO_M, 0);
}

static u8 port_get_qm_burst_size(struct ksz_sw *sw, int p)
{
	return (u8) port_r_s_32(sw, p, REG_PORT_QM_QUEUE_INDEX__4,
		3, PORT_QM_BURST_SIZE_S);
}

static u16 port_get_qm_resv_space(struct ksz_sw *sw, int p)
{
	return (u16) port_r_s_32(sw, p, REG_PORT_QM_QUEUE_INDEX__4,
		PORT_QM_MIN_RESV_SPACE_M, 0);
}

static u16 port_get_qm_hi_water_mark(struct ksz_sw *sw, int p, int q)
{
	port_w_s_32(sw, p, REG_PORT_QM_QUEUE_INDEX__4,
		PRIO_QUEUES_M, PORT_QM_QUEUE_INDEX_S, q);
	return (u16) port_r_s_32(sw, p, REG_PORT_QM_WATER_MARK__4,
		PORT_QM_WATER_MARK_M, PORT_QM_HI_WATER_MARK_S);
}

static u16 port_get_qm_lo_water_mark(struct ksz_sw *sw, int p, int q)
{
	port_w_s_32(sw, p, REG_PORT_QM_QUEUE_INDEX__4,
		PRIO_QUEUES_M, PORT_QM_QUEUE_INDEX_S, q);
	return (u16) port_r_s_32(sw, p, REG_PORT_QM_WATER_MARK__4,
		PORT_QM_WATER_MARK_M, PORT_QM_LO_WATER_MARK_S);
}

static u16 port_get_qm_tx_used(struct ksz_sw *sw, int p, int q)
{
	port_w_s_32(sw, p, REG_PORT_QM_QUEUE_INDEX__4,
		PRIO_QUEUES_M, PORT_QM_QUEUE_INDEX_S, q);
	return (u16) port_r_s_32(sw, p, REG_PORT_QM_TX_CNT_0__4,
		PORT_QM_TX_CNT_M, PORT_QM_TX_CNT_USED_S);
}

static u16 port_get_qm_tx_avail(struct ksz_sw *sw, int p, int q)
{
	port_w_s_32(sw, p, REG_PORT_QM_QUEUE_INDEX__4,
		PRIO_QUEUES_M, PORT_QM_QUEUE_INDEX_S, q);
	return (u16) port_r_s_32(sw, p, REG_PORT_QM_TX_CNT_1__4,
		PORT_QM_TX_CNT_M, PORT_QM_TX_CNT_AVAIL_S);
}

static u16 port_get_qm_tx_calculated(struct ksz_sw *sw, int p, int q)
{
	port_w_s_32(sw, p, REG_PORT_QM_QUEUE_INDEX__4,
		PRIO_QUEUES_M, PORT_QM_QUEUE_INDEX_S, q);
	return (u16) port_r_s_32(sw, p, REG_PORT_QM_TX_CNT_1__4,
		PORT_QM_TX_CNT_M, PORT_QM_TX_CNT_CALCULATED_S);
}

static inline void port_set_qm_drop(struct ksz_sw *sw, int p, u8 drop)
{
	port_w_s_32(sw, p, REG_PORT_QM_CTRL__4,
		PORT_QM_DROP_PRIO_M, 0, drop);
}

static inline void port_set_qm_burst_size(struct ksz_sw *sw, int p, u8 burst)
{
	port_w_s_32(sw, p, REG_PORT_QM_QUEUE_INDEX__4,
		3, PORT_QM_BURST_SIZE_S, burst);
}

static inline void port_set_qm_resv_space(struct ksz_sw *sw, int p, u16 space)
{
	port_w_s_32(sw, p, REG_PORT_QM_QUEUE_INDEX__4,
		PORT_QM_MIN_RESV_SPACE_M, 0, space);
}

static void port_set_qm_hi_water_mark(struct ksz_sw *sw, int p, int q, u16 val)
{
	port_w_s_32(sw, p, REG_PORT_QM_QUEUE_INDEX__4,
		PRIO_QUEUES_M, PORT_QM_QUEUE_INDEX_S, q);
	port_w_s_32(sw, p, REG_PORT_QM_WATER_MARK__4,
		PORT_QM_WATER_MARK_M, PORT_QM_HI_WATER_MARK_S, val);
}

static void port_set_qm_lo_water_mark(struct ksz_sw *sw, int p, int q, u16 val)
{
	port_w_s_32(sw, p, REG_PORT_QM_QUEUE_INDEX__4,
		PRIO_QUEUES_M, PORT_QM_QUEUE_INDEX_S, q);
	port_w_s_32(sw, p, REG_PORT_QM_WATER_MARK__4,
		PORT_QM_WATER_MARK_M, PORT_QM_LO_WATER_MARK_S, val);
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
	SW_D regmask = KS_PRIO_M;

	if (tos >= DIFFSERV_ENTRIES)
		return;

	if (prio >= 0x10)
		mask = 0xff;
	else if (prio > KS_PRIO_M)
		mask = 0xf;
	if (prio >= 0x10)
		regmask = (KS_PRIO_M << KS_PRIO_S) | KS_PRIO_M;
	shift = (tos & (KS_PRIO_IN_REG - 1)) * KS_PRIO_S;
	prio = prio << shift;
	if (prio >> shift != data)
		return;
	mask <<= shift;
	regmask <<= shift;
	prio &= regmask;
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
	SW_D regmask = KS_PRIO_M;

	if (tag >= PRIO_802_1P_ENTRIES)
		return;

	if (prio >= 0x10)
		mask = 0xff;
	else if (prio > KS_PRIO_M)
		mask = 0xf;
	if (prio >= 0x10)
		regmask = (KS_PRIO_M << KS_PRIO_S) | KS_PRIO_M;
	shift = (tag & (KS_PRIO_IN_REG - 1)) * KS_PRIO_S;
	prio = prio << shift;
	if (prio >> shift != data)
		return;
	mask <<= shift;
	regmask <<= shift;
	prio &= regmask;
	tag /= KS_PRIO_IN_REG;

	sw->info->p_802_1p[tag] &= ~mask;
	sw->info->p_802_1p[tag] |= prio;

	sw_set_802_1p_prio(sw, tag, sw->info->p_802_1p[tag]);
}  /* hw_cfg_802_1p_prio */

/**
 * sw_cfg_replace_null_vid - enable switch null VID replacement
 * @sw:		The switch instance.
 * @port:	The port index.
 * @set:	The flag to disable or enable.
 *
 * This routine enables the VID to be replaced with port default VID if it is
 * empty.
 */
static void sw_cfg_replace_null_vid(struct ksz_sw *sw, int p, int set)
{
	port_cfg32(sw, p, REG_PORT_MTI_QUEUE_CTRL_0__4, MTI_PVID_REPLACE, set);
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

	port_r(sw, port, REG_PORT_MRI_MAC_CTRL, &data);
	data &= ~(PORT_BASED_PRIO_M << PORT_BASED_PRIO_S);
	data |= prio << PORT_BASED_PRIO_S;
	port_w(sw, port, REG_PORT_MRI_MAC_CTRL, data);

	sw->info->port_cfg[port].port_prio = prio;
}  /* sw_cfg_port_based */

/* -------------------------------------------------------------------------- */

/**
 * sw_set_multi_queue - enable transmit multiple queues
 * @sw:		The switch instance.
 * @port:	The port index.
 *
 * This routine enables the transmit multiple queues selection of the switch
 * port.  The port transmit queue is split into two or four priority queues.
 */
static void sw_set_multi_queue(struct ksz_sw *sw, int port, int queue)
{
	port_cfg_prio(sw, port, queue);
}  /* sw_set_multi_queue */

/**
 * sw_init_prio - initialize switch priority
 * @sw:		The switch instance.
 *
 * This routine initializes the switch QoS priority functions.
 */
static void sw_init_prio(struct ksz_sw *sw)
{
	int port;
	int tos;
	SW_D data;
	struct ksz_port_cfg *port_cfg;

	for (tos = 0; tos < PRIO_802_1P_ENTRIES / KS_PRIO_IN_REG; tos++)
		sw->info->p_802_1p[tos] =
			SW_R(sw, S_802_1P_PRIO_CTRL + tos * SW_SIZE);

	for (tos = 0; tos < DIFFSERV_ENTRIES / KS_PRIO_IN_REG; tos++)
		sw->info->diffserv[tos] =
			SW_R(sw, S_TOS_PRIO_CTRL + tos * SW_SIZE);

	for (port = 0; port < sw->mib_port_cnt; port++) {
		port_r(sw, port, REG_PORT_MRI_MAC_CTRL, &data);
		data &= PORT_BASED_PRIO_M;
		sw->info->port_cfg[port].port_prio = data;
		port_cfg = &sw->info->port_cfg[port];
		for (tos = 0; tos < PRIO_802_1P_ENTRIES / 8; tos++)
			port_r32(sw, port, REG_PORT_MRI_TC_MAP__4 - tos * 4,
				&port_cfg->tc_map[tos]);

		for (tos = 0; tos < DIFFSERV_ENTRIES / 16; tos++)
			port_r32(sw, port, REG_PORT_POLICE_COLOR_3__4 -
				tos * 4, &port_cfg->color_map[tos]);
	}

#if 0
#ifdef USE_DIFF_PORT_PRIORITY
/*
 * THa  2012/02/01
 * Port 3 sometimes cannot send frames out through the port where 100%
 * wire-rate 64 bytes traffic also goes through.  Solution is to assign
 * different port priorities.  It does not matter port 3 has higher priority,
 * just different from the port where heavy traffic comes in.
 */
	for (port = 0; port < TOTAL_PORT_NUM; port++)
		sw->info->port_cfg[port].port_prio = port;
#endif
#ifdef USE_DIFF_PORT_PRIORITY
	for (port = 0; port < SWITCH_PORT_NUM; port++) {
		int prio;

		for (prio = 0; prio < PRIO_QUEUES; prio++) {
			sw->info->port_cfg[port].rx_rate[prio] = 95000;
			sw->info->port_cfg[port].tx_rate[prio] = 0;
		}
		sw_ena_prio_rate(sw, port);
	}
#endif
#endif
}  /* sw_init_prio */

static void port_set_color_map(struct ksz_sw *sw, int port, u8 tos, u32 prio)
{
	port_w32(sw, port, REG_PORT_POLICE_COLOR_3__4 - tos * 4, prio);
}  /* port_set_color_map */

static void port_set_tc_map(struct ksz_sw *sw, int port, u8 tos, u32 prio)
{
	port_w32(sw, port, REG_PORT_MRI_TC_MAP__4 + tos * 4, prio);
}  /* port_set_color_map */

/**
 * port_cfg_color_map - configure port police color map
 * @sw:		The switch instance.
 * @tos:	ToS value from 6-bit (bit7 ~ bit2) of ToS field, ranging from 0
 *		to 63.
 * @prio:	Priority to be assigned.
 *
 * This routine configures the TOS priority in the hardware.
 * DiffServ Value 0 ~ 63 is mapped to Priority Queue Number 0 ~ 3.
 * It is called by user functions.  The hardware should be acquired first.
 */
static void port_cfg_color_map(struct ksz_sw *sw, int port, u8 tos, u32 prio)
{
	int shift;
	u32 data = prio;
	u32 mask = POLICE_COLOR_MAP_M;
	struct ksz_port_cfg *port_cfg = &sw->info->port_cfg[port];

	if (tos >= DIFFSERV_ENTRIES)
		return;

	if (prio >= 0x10000)
		mask = 0xffffffff;
	else if (prio >= 0x100)
		mask = 0xffff;
	else if (prio >= 0x10)
		mask = 0xff;
	else if (prio > POLICE_COLOR_MAP_M)
		mask = 0xf;
	shift = (tos & (16 - 1)) * POLICE_COLOR_MAP_S;
	prio = prio << shift;
	if (prio >> shift != data)
		return;
	mask <<= shift;
	tos /= 16;

	port_cfg->color_map[tos] &= ~mask;
	port_cfg->color_map[tos] |= prio;

	port_set_color_map(sw, port, tos, port_cfg->color_map[tos]);
}  /* port_cfg_color_map */

/**
 * port_cfg_tc_map - configure port traffic class map
 * @sw:		The switch instance.
 * @tos:	ToS value from 6-bit (bit7 ~ bit2) of ToS field, ranging from 0
 *		to 63.
 * @prio:	Priority to be assigned.
 *
 * This routine configures the TOS priority in the hardware.
 * DiffServ Value 0 ~ 63 is mapped to Priority Queue Number 0 ~ 3.
 * It is called by user functions.  The hardware should be acquired first.
 */
static void port_cfg_tc_map(struct ksz_sw *sw, int port, u8 tos, u32 prio)
{
	int shift;
	u32 data = prio;
	u32 mask = PORT_TC_MAP_M;
	u32 regmask = PORT_TC_MAP_M;
	struct ksz_port_cfg *port_cfg = &sw->info->port_cfg[port];

	if (tos >= PRIO_802_1P_ENTRIES)
		return;

	if (prio >= 0x10000)
		mask = 0xffffffff;
	else if (prio >= 0x100)
		mask = 0xffff;
	else if (prio >= 0x10)
		mask = 0xff;
	else if (prio > PORT_TC_MAP_M)
		mask = 0xf;
	if (prio >= 0x10000)
		regmask = 0x33333333;
	else if (prio >= 0x100)
		regmask = 0x3333;
	else if (prio >= 0x10)
		regmask = 0x33;
	shift = (tos & (8 - 1)) * PORT_TC_MAP_S;
	prio = prio << shift;
	if (prio >> shift != data)
		return;
	mask <<= shift;
	regmask <<= shift;
	prio &= regmask;
	tos /= 8;

	port_cfg->tc_map[tos] &= ~mask;
	port_cfg->tc_map[tos] |= prio;

	port_set_tc_map(sw, port, tos, port_cfg->tc_map[tos]);
}  /* port_cfg_tc_map */

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
	for (port = 0; port < sw->mib_port_cnt; port++) {
		sw_set_multi_queue(sw, port, 2);
		sw_dis_diffserv(sw, port);
		sw_cfg_replace_prio(sw, port, 0);
		sw_cfg_replace_null_vid(sw, port, 0);
		sw_cfg_port_based(sw, port, sw->info->port_cfg[port].port_prio);

		sw_ena_802_1p(sw, port);
	}
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
	port_w16(sw, port, REG_PORT_DEFAULT_VID, vid);
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
	port_r16(sw, port, REG_PORT_DEFAULT_VID, vid);
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
static void sw_cfg_port_base_vlan(struct ksz_sw *sw, int port, u16 member)
{
#if 0
/*
 * THa  2014/10/08
 * There are problems in using the VLAN table method for PTP.
 */
	struct ksz_vlan_table entry;
	int p;

	memset(&entry, 0, sizeof(struct ksz_vlan_table));
	p = 100 + port;
	sw->reg->unlock(sw);
	entry.fid = 0;
	entry.untag = sw->PORT_MASK;
	entry.ports = member;
	entry.valid = 1;
	sw_w_vlan_table(sw, p, &entry);
	sw->reg->lock(sw);

	sw_cfg_def_vid(sw, port, p);
#else
/*
 * THa  2014/10/08
 * In KSZ9566 the bit for the last host port is 0x40 instead of 0x20.
 */
	if (6 == sw->mib_port_cnt && (member & 0x20))
		member |= 0x40;
	port_w32(sw, port, REG_PORT_VLAN_MEMBERSHIP__4, member);
#endif

	sw->info->port_cfg[port].member = member;
}  /* sw_cfg_port_base_vlan */

static void sw_cfg_default_vlan(struct ksz_sw *sw, int reset)
{
	struct ksz_vlan_table vlan;

	if (sw->overrides & VLAN_SET)
		return;
	sw->ops->release(sw);
	vlan.vid = 1;
	sw_r_vlan_table(sw, vlan.vid, &vlan);
	if (reset)
		vlan.untag = 0;
	else
		vlan.untag = vlan.ports;
	vlan.valid = vlan.ports != 0;
	sw_w_vlan_table(sw, vlan.vid, &vlan);
	sw->ops->acquire(sw);
}  /* sw_cfg_default_vlan */

/**
 * sw_dis_vlan - disable switch VLAN
 * @sw:		The switch instance.
 *
 * This routine disables the VLAN function of the switch.
 */
static void sw_dis_vlan(struct ksz_sw *sw)
{
	sw_cfg(sw, REG_SW_LUE_CTRL_0, SW_VLAN_ENABLE, 0);
	sw_cfg_default_vlan(sw, true);
}  /* sw_dis_vlan */

/**
 * sw_ena_vlan - enable switch VLAN
 * @sw:		The switch instance.
 *
 * This routine enables the VLAN function of the switch.
 */
static void sw_ena_vlan(struct ksz_sw *sw)
{
	sw_cfg_default_vlan(sw, false);

	/* Enable 802.1q VLAN mode. */
	sw_cfg(sw, REG_SW_QM_CTRL, UNICAST_VLAN_BOUNDARY, 1);
	sw_cfg(sw, REG_SW_LUE_CTRL_0, SW_VLAN_ENABLE, 1);
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
	u32 data;
	struct ksz_sw_info *info = sw->info;

	for (port = 0; port < sw->mib_port_cnt; port++) {
		port_get_def_vid(sw, port, &info->port_cfg[port].vid);
		port_r32(sw, port, REG_PORT_VLAN_MEMBERSHIP__4, &data);
		info->port_cfg[port].member = (u16) data;
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
	sw->reg->w(sw, REG_SW_MAC_ADDR_0, mac_addr, 6);
	memcpy(sw->info->mac_addr, mac_addr, 6);
#ifdef KSZ_IBA
	prepare_iba(&sw->info->iba, mac_addr, sw->info->iba.src);
#endif
}  /* sw_set_addr */

#ifdef SWITCH_PORT_PHY_ADDR_MASK
/**
 * sw_init_phy_addr - initialize switch PHY address
 * @sw:		The switch instance.
 *
 * This function initializes the PHY address of the switch.
 */
static void sw_init_phy_addr(struct ksz_sw *sw)
{
	u8 addr;

	addr = sw->reg->r8(sw, REG_SWITCH_CTRL_13);
	addr >>= SWITCH_PORT_PHY_ADDR_SHIFT;
	addr &= SWITCH_PORT_PHY_ADDR_MASK;
	sw->info->phy_addr = addr;
}

/**
 * sw_set_phy_addr - configure switch PHY address
 * @sw:		The switch instance.
 * @addr:	The PHY address.
 *
 * This function configures the PHY address of the switch.
 */
static void sw_set_phy_addr(struct ksz_sw *sw, u8 addr)
{
	sw->info->phy_addr = addr;
	addr &= SWITCH_PORT_PHY_ADDR_MASK;
	addr <<= SWITCH_PORT_PHY_ADDR_SHIFT;
	sw->reg->w8(sw, REG_SWITCH_CTRL_13, addr);
}
#endif

static void sw_setup_reserved_multicast(struct ksz_sw *sw)
{
	struct ksz_mac_table table[8];
	u16 addr[8];
	u32 ctrl[8];
	int i;

	memset(table, 0, sizeof(struct ksz_mac_table) * 8);
	for (i = 0; i < 8; i++)
		addr[i] = get_mcast_reserved_addr(i);

	/* Register access is locked before this call. */
	sw->ops->release(sw);
	sw_r_m_sta_mac_table(sw, addr, 1, 8, table);
	if (table[0].ports != sw->HOST_MASK) {
		for (i = 0; i < 8; i++)
			ctrl[i] = get_mac_table_ctrl(addr[i], true);
		table[0].ports = sw->HOST_MASK;
		table[1].ports = 0;
		table[2].ports = sw->HOST_MASK;
		table[3].ports = sw->PORT_MASK;
		table[4].ports = sw->PORT_MASK & ~sw->HOST_MASK;
		table[5].ports = sw->PORT_MASK & ~sw->HOST_MASK;
		table[6].ports = sw->HOST_MASK;
		table[7].ports = sw->PORT_MASK & ~sw->HOST_MASK;
		sw_w_m_sta_mac_table(sw, addr, true, 8, table);
	}
	sw->ops->acquire(sw);
	sw_cfg(sw, REG_SW_LUE_CTRL_0, SW_RESV_MCAST_ENABLE, 1);
}  /* sw_setup_reserved_multicast */

static int sw_get_gbit(struct ksz_sw *sw, u8 data)
{
	int gbit;

	if (sw->features & NEW_CAP)
		gbit = !(data & PORT_MII_NOT_1GBIT);
	else
		gbit = data & PORT_MII_1000MBIT_S1;
	return gbit;
}  /* sw_get_gbit */

static void sw_set_gbit(struct ksz_sw *sw, int gbit, u8 *data)
{
	if (sw->features & NEW_CAP) {
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
}  /* sw_set_gbit */

static int sw_get_xmii(struct ksz_sw *sw, u8 data)
{
	int mode;

	if (sw->features & NEW_CAP) {
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
}  /* sw_get_xmii */

static void sw_set_xmii(struct ksz_sw *sw, int mode, u8 *data)
{
	u8 xmii;

	if (sw->features & NEW_CAP) {
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
		}
	}
	*data &= ~PORT_MII_SEL_M;
	*data |= xmii;
}  /* sw_set_xmii */

/**
 * sw_set_global_ctrl - set switch global control
 * @sw:		The switch instance.
 *
 * This routine sets the global control of the switch function.
 */
static void sw_set_global_ctrl(struct ksz_sw *sw)
{
	SW_D data;

	if (sw->HOST_PORT >= sw->phy_port_cnt) {
		struct phy_device *phydev = sw->phydev;
		struct ksz_port_info *info = &sw->port_info[sw->HOST_PORT];
		int gbit;
		int mode;

		/* Allow slower speed to be used for testing purpose. */
#ifdef USE_10_MBIT_MODE
		phydev->speed = SPEED_10;
		phydev->dev_flags |= 1;
#endif
#ifdef USE_HALF_DUPLEX
		phydev->duplex = DUPLEX_HALF;
		phydev->dev_flags |= 1;
#endif
#if defined(USE_MII_PHY) || defined(USE_RGMII_PHY)
		phydev->dev_flags |= 2;
#endif
		if ((sw->features & NO_GLOBAL_RESET) ||
		    (phydev->dev_flags & 1)) {
			port_r(sw, sw->HOST_PORT, REG_PORT_XMII_CTRL_0, &data);
			data |= PORT_MII_100MBIT;
			data |= PORT_MII_FULL_DUPLEX;
			if (phydev->dev_flags & 1) {
				if (SPEED_10 == phydev->speed)
					data &= ~PORT_MII_100MBIT;
				if (DUPLEX_HALF == phydev->duplex)
					data &= ~PORT_MII_FULL_DUPLEX;
			}
			if ((data & PORT_MII_100MBIT) &&
			    phydev->speed < SPEED_100)
				phydev->speed = SPEED_100;
			if ((data & PORT_MII_FULL_DUPLEX) &&
			    phydev->duplex < DUPLEX_FULL)
				phydev->duplex = DUPLEX_FULL;
			port_w(sw, sw->HOST_PORT, REG_PORT_XMII_CTRL_0, data);
		}

		port_r(sw, sw->HOST_PORT, REG_PORT_XMII_CTRL_1, &data);
		data &= ~PORT_MII_MAC_MODE;
		if (phydev->dev_flags & 2)
			data |= PORT_MII_MAC_MODE;
		switch (phydev->interface) {
		case PHY_INTERFACE_MODE_MII:
			sw_set_gbit(sw, false, &data);
			mode = 0;
			if (phydev->speed > SPEED_100)
				phydev->speed = SPEED_100;
			break;
		case PHY_INTERFACE_MODE_RMII:
			sw_set_gbit(sw, false, &data);
			mode = 1;
			break;
		case PHY_INTERFACE_MODE_GMII:
			sw_set_gbit(sw, true, &data);
			mode = 2;
			if (phydev->dev_flags & 1) {
				if (SPEED_1000 != phydev->speed)
					sw_set_gbit(sw, false, &data);
			}
			gbit = sw_get_gbit(sw, data);
			if (gbit && phydev->speed < SPEED_1000)
				phydev->speed = SPEED_1000;
			break;
		case PHY_INTERFACE_MODE_SGMII:
			mode = 3;
			break;
		default:
			data &= ~PORT_RGMII_ID_IG_ENABLE;
			data &= ~PORT_RGMII_ID_EG_ENABLE;
			if (PHY_INTERFACE_MODE_RGMII_ID == phydev->interface ||
			    PHY_INTERFACE_MODE_RGMII_RXID == phydev->interface)
				data |= PORT_RGMII_ID_IG_ENABLE;
			if (PHY_INTERFACE_MODE_RGMII_ID == phydev->interface ||
			    PHY_INTERFACE_MODE_RGMII_TXID == phydev->interface)
				data |= PORT_RGMII_ID_EG_ENABLE;
			sw_set_gbit(sw, true, &data);
			mode = 3;
			if (phydev->dev_flags & 1) {
				if (SPEED_1000 != phydev->speed)
					sw_set_gbit(sw, false, &data);
			}
			gbit = sw_get_gbit(sw, data);
			if (gbit && phydev->speed < SPEED_1000)
				phydev->speed = SPEED_1000;
			break;
		}
		info->tx_rate = phydev->speed * TX_RATE_UNIT;
		info->duplex = phydev->duplex + 1;
#ifdef USE_RGMII_PHY
		data |= PORT_RGMII_ID_EG_ENABLE;
		mode = 3;
#endif
		sw_set_xmii(sw, mode, &data);
		port_w(sw, sw->HOST_PORT, REG_PORT_XMII_CTRL_1, data);
	}

	data = SW_R(sw, REG_SW_MAC_CTRL_0);

	/* Enable aggressive back off algorithm in half duplex mode. */
	data |= SW_AGGR_BACKOFF;
	SW_W(sw, REG_SW_MAC_CTRL_0, data);

	data = SW_R(sw, REG_SW_MAC_CTRL_1);

	/* Enable no excessive collision drop. */
	data |= NO_EXC_COLLISION_DROP;
	SW_W(sw, REG_SW_MAC_CTRL_1, data);

	data = SW_R(sw, S_LINK_AGING_CTRL);

	data |= SW_AGING_ENABLE;
	if (sw->overrides & FAST_AGING)
		data |= SW_FAST_AGING;
	else
		data &= ~SW_FAST_AGING;

	/* Enable automatic fast aging when link changed detected. */
	data |= SW_LINK_AUTO_AGING;

#if 1
/*
 * THa  2014/10/08
 * The host port also gets filtered if lookup is used!
 */
	if (sw->features & NEW_CAP)
		data |= SW_SRC_ADDR_FILTER;
#endif
	SW_W(sw, S_LINK_AGING_CTRL, data);

	data = SW_R(sw, REG_SW_QM_CTRL);

	/* Make sure unicast VLAN boundary is set as default. */
	if (sw->dev_count > 1)
		data |= UNICAST_VLAN_BOUNDARY;
	SW_W(sw, REG_SW_QM_CTRL, data);

#if 1
/*
 * THa  2015/12/06
 * The HSR register 0x640 needs to be set, even though the value read is 3.
 * The NODE_UNICAST bit in register 0x644 needs to be turned off for multicast
 * address to work.
 * If HSR_LEARN_UCAST_DISABLE bit in register 0x645 is turned on, multicast
 * address also does not work, even though HSR_LEARN_MCAST_DISABLE bit in
 * register 0x644 can be used to control that.
 */
	if (sw->features & HSR_HW) {
		sw->reg->w32(sw, REG_HSR_PORT_MAP__4, 3);
		data = SW_R(sw, REG_HSR_ALU_CTRL_0__1);
		data &= ~HSR_NODE_UNICAST;
		SW_W(sw, REG_HSR_ALU_CTRL_0__1, data);
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
		if (port != sw->HOST_PORT)
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
		if (port != sw->HOST_PORT &&
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
		if (port != sw->HOST_PORT &&
		    STP_STATE_DISABLED == port_cfg->stp_state)
			member = sw->HOST_MASK | (1 << port);
		break;
	case STP_STATE_SIMPLE:
		data |= (PORT_TX_ENABLE | PORT_RX_ENABLE);
		data |= PORT_LEARN_DISABLE;
		if (port != sw->HOST_PORT)
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
	SW_D data;

	data = SW_R(sw, REG_SW_LUE_CTRL_2);
	data &= ~(SW_FLUSH_OPTION_M << SW_FLUSH_OPTION_S);
	data |= (SW_FLUSH_OPTION_STA_MAC << SW_FLUSH_OPTION_S);
	SW_W(sw, REG_SW_LUE_CTRL_2, data);
	sw_cfg(sw, S_FLUSH_TABLE_CTRL, SW_FLUSH_STP_TABLE, 1);
}  /* sw_clr_sta_mac_table */

/**
 * sw_setup_stp - setup switch spanning tree support
 * @sw:		The switch instance.
 *
 * This routine initializes the spanning tree support of the switch.
 */
static void sw_setup_stp(struct ksz_sw *sw)
{
	struct ksz_mac_table *entry;
	struct ksz_alu_table *alu;
	struct ksz_sw_info *info = sw->info;

	entry = &info->mac_table[STP_ENTRY];
	entry->addr[0] = 0x01;
	entry->addr[1] = 0x80;
	entry->addr[2] = 0xC2;
	entry->addr[3] = 0x00;
	entry->addr[4] = 0x00;
	entry->addr[5] = 0x00;
	entry->ports = sw->HOST_MASK;
	entry->override = 1;
	entry->valid = 1;
	alu = &info->alu_table[STP_ENTRY];
	alu->forward = FWD_STP_DEV | FWD_HOST | FWD_HOST_OVERRIDE;
	alu->owner = sw->PORT_MASK;
	alu->valid = 1;
	alu->index = 0;
	alu->type = 1;
	sw->ops->release(sw);
	sw_w_sta_mac_table(sw, alu->index, alu->type, entry);
	sw->ops->acquire(sw);

	entry = &info->mac_table[BROADCAST_ENTRY];
	memset(entry->addr, 0xFF, ETH_ALEN);
	entry->ports = sw->HOST_MASK;
	entry->override = 0;
	entry->valid = 1;
	alu = &sw->info->alu_table[BROADCAST_ENTRY];
	alu->forward = FWD_MAIN_DEV | FWD_STP_DEV | FWD_HOST;
	alu->owner = sw->PORT_MASK;
	alu->valid = 1;
	alu->index = BROADCAST_ENTRY - 1;
	alu->type = 0;

	entry = &info->mac_table[BRIDGE_ADDR_ENTRY];
	memcpy(entry->addr, info->mac_addr, ETH_ALEN);
	entry->ports = sw->HOST_MASK;
	entry->override = 0;
	entry->valid = 1;
	alu = &sw->info->alu_table[BRIDGE_ADDR_ENTRY];
	alu->forward = FWD_MAIN_DEV | FWD_HOST;
	alu->owner = sw->PORT_MASK;
	alu->valid = 1;
	alu->index = BRIDGE_ADDR_ENTRY - 1;
	alu->type = 0;

	entry = &info->mac_table[IPV6_ADDR_ENTRY];
	memcpy(entry->addr, info->mac_addr, ETH_ALEN);
	entry->addr[0] = 0x33;
	entry->addr[1] = 0x33;
	entry->addr[2] = 0xFF;
	entry->ports = sw->HOST_MASK;
	entry->override = 0;
	entry->valid = 1;
	alu = &sw->info->alu_table[IPV6_ADDR_ENTRY];
	alu->forward = FWD_MAIN_DEV | FWD_STP_DEV | FWD_HOST;
	alu->owner = sw->PORT_MASK;
	alu->valid = 1;
	alu->index = IPV6_ADDR_ENTRY - 1;
	alu->type = 0;
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
	struct ksz_mac_table *entry;
	struct ksz_alu_table *alu;
	int i;
	struct ksz_sw_info *info = sw->info;

	for (i = BROADCAST_ENTRY; i <= IPV6_ADDR_ENTRY; i++) {
		entry = &info->mac_table[i];
		entry->valid = 0;
		alu = &info->alu_table[i];
		sw_w_sta_mac_table(sw, alu->index, alu->type, entry);
	}
}  /* sw_block_addr */

static void sw_block_multi(struct ksz_sw *sw)
{
	struct ksz_mac_table *entry;
	struct ksz_alu_table *alu;
	int i;
	struct ksz_sw_info *info = sw->info;

	for (i = STATIC_MAC_TABLE_ENTRIES; i < MULTI_MAC_TABLE_ENTRIES; i++) {
		entry = &info->mac_table[i];
		if (entry->ports) {
			entry->valid = 0;
			alu = &info->alu_table[i];
			if (2 == alu->type)
				sw_w_dyn_mac_table(sw, alu->index,
					entry->addr, entry->fid, entry);
			else if (alu->type < 2)
				sw_w_sta_mac_table(sw, alu->index, alu->type,
					entry);
		}
	}
}  /* sw_block_multi */

#ifdef CONFIG_1588_PTP
static void sw_setup_ptp(struct ksz_sw *sw)
{
	struct ksz_mac_table *entry;
	struct ksz_alu_table *alu;
	int i;
	u8 forward;
	struct ksz_sw_info *info = sw->info;

	i = info->multi_sys;
	forward = FWD_MAIN_DEV;
	forward |= FWD_VLAN_DEV;

	entry = &info->mac_table[--i];
	entry->addr[0] = 0x01;
	entry->addr[1] = 0x00;
	entry->addr[2] = 0x5E;
	entry->addr[3] = 0x00;
	entry->addr[4] = 0x01;
	entry->addr[5] = 0x81;
	entry->ports = sw->PORT_MASK;
	alu = &info->alu_table[i];
	alu->forward = forward;
	alu->owner = 1;
	alu->valid = 1;
	alu->index = 0;
	alu->type = 3;
	entry = &info->mac_table[--i];
	entry->addr[0] = 0x01;
	entry->addr[1] = 0x00;
	entry->addr[2] = 0x5E;
	entry->addr[3] = 0x00;
	entry->addr[4] = 0x00;
	entry->addr[5] = 0x6B;
	entry->ports = sw->PORT_MASK;
	entry->override = 1;
	alu = &info->alu_table[i];
	alu->forward = forward | FWD_HOST_OVERRIDE;
	alu->owner = 1;
	alu->valid = 1;
	alu->index = 0;
	alu->type = 3;
	entry = &info->mac_table[--i];
	entry->addr[0] = 0x33;
	entry->addr[1] = 0x33;
	entry->addr[2] = 0x00;
	entry->addr[3] = 0x00;
	entry->addr[4] = 0x01;
	entry->addr[5] = 0x81;
	entry->ports = sw->PORT_MASK;
	alu = &info->alu_table[i];
	alu->forward = forward;
	alu->owner = 1;
	alu->valid = 1;
	alu->index = 0;
	alu->type = 3;
	entry = &info->mac_table[--i];
	entry->addr[0] = 0x33;
	entry->addr[1] = 0x33;
	entry->addr[2] = 0x00;
	entry->addr[3] = 0x00;
	entry->addr[4] = 0x00;
	entry->addr[5] = 0x6B;
	entry->ports = sw->PORT_MASK;
	entry->override = 1;
	alu = &info->alu_table[i];
	alu->forward = forward | FWD_HOST_OVERRIDE;
	alu->owner = 1;
	alu->valid = 1;
	alu->index = 0;
	alu->type = 3;
	entry = &info->mac_table[--i];
	entry->addr[0] = 0x01;
	entry->addr[1] = 0x1B;
	entry->addr[2] = 0x19;
	entry->addr[3] = 0x00;
	entry->addr[4] = 0x00;
	entry->addr[5] = 0x00;
	entry->ports = sw->PORT_MASK;
	alu = &info->alu_table[i];
	alu->forward = forward;
	alu->owner = 1;
	alu->valid = 1;
	alu->index = 0;
	alu->type = 3;
	entry = &info->mac_table[--i];
	entry->addr[0] = 0x01;
	entry->addr[1] = 0x80;
	entry->addr[2] = 0xC2;
	entry->addr[3] = 0x00;
	entry->addr[4] = 0x00;
	entry->addr[5] = 0x0E;
	entry->ports = sw->HOST_MASK;
	entry->override = 1;
	alu = &info->alu_table[i];
	alu->forward = forward | FWD_HOST_OVERRIDE;
	alu->owner = 1;
	alu->valid = 1;
	alu->index = 0xE;
	alu->type = 1;

	info->multi_sys = i;
}
#endif

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
	entry->addr[0] = 0x01;
	entry->addr[1] = 0x00;
	entry->addr[2] = 0x5E;
	entry->addr[3] = 0x00;
	entry->addr[4] = 0x00;
	entry->addr[5] = 0x01;
	entry->ports = sw->HOST_MASK;
	alu = &info->alu_table[i];
	alu->forward = forward;
	alu->owner = sw->PORT_MASK;
	alu->valid = 1;
	alu->index = 0;
	alu->type = 2;
	entry = &info->mac_table[--i];
	entry->addr[0] = 0x33;
	entry->addr[1] = 0x33;
	entry->addr[2] = 0x00;
	entry->addr[3] = 0x00;
	entry->addr[4] = 0x00;
	entry->addr[5] = 0x01;
	entry->ports = sw->HOST_MASK;
	alu = &info->alu_table[i];
	alu->forward = forward;
	alu->owner = sw->PORT_MASK;
	alu->valid = 1;
	alu->index = 0;
	alu->type = 2;

	entry = &info->mac_table[--i];
	entry->addr[0] = 0x01;
	entry->addr[1] = 0x00;
	entry->addr[2] = 0x5E;
	entry->addr[3] = 0x00;
	entry->addr[4] = 0x00;
	entry->addr[5] = 0x02;
	entry->ports = sw->HOST_MASK;
	alu = &info->alu_table[i];
	alu->forward = forward;
	alu->owner = sw->PORT_MASK;
	alu->valid = 1;
	alu->index = 0;
	alu->type = 2;
	entry = &info->mac_table[--i];
	entry->addr[0] = 0x33;
	entry->addr[1] = 0x33;
	entry->addr[2] = 0x00;
	entry->addr[3] = 0x00;
	entry->addr[4] = 0x00;
	entry->addr[5] = 0x02;
	entry->ports = sw->HOST_MASK;
	alu = &info->alu_table[i];
	alu->forward = forward;
	alu->owner = sw->PORT_MASK;
	alu->valid = 1;
	alu->index = 0;
	alu->type = 2;

	/* Used for V3 IGMP messages. */
	entry = &info->mac_table[--i];
	entry->addr[0] = 0x01;
	entry->addr[1] = 0x00;
	entry->addr[2] = 0x5E;
	entry->addr[3] = 0x00;
	entry->addr[4] = 0x00;
	entry->addr[5] = 0x16;
	entry->ports = sw->HOST_MASK;
	alu = &info->alu_table[i];
	alu->forward = forward;
	alu->owner = sw->PORT_MASK;
	alu->valid = 1;
	alu->index = 0;
	alu->type = 2;
	entry = &info->mac_table[--i];
	entry->addr[0] = 0x33;
	entry->addr[1] = 0x33;
	entry->addr[2] = 0x00;
	entry->addr[3] = 0x00;
	entry->addr[4] = 0x00;
	entry->addr[5] = 0x16;
	entry->ports = sw->HOST_MASK;
	alu = &info->alu_table[i];
	alu->forward = forward;
	alu->owner = sw->PORT_MASK;
	alu->valid = 1;
	alu->index = 0;
	alu->type = 2;

	info->multi_sys = i;
}

static void bridge_change(struct ksz_sw *sw)
{
	int port;
	u8 member;
	struct ksz_sw_info *info = sw->info;

	for (port = 0; port < sw->mib_port_cnt; port++) {
		if (port == sw->HOST_PORT)
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
	struct ksz_mac_table *entry;
	struct ksz_alu_table *alu;
	int i;
	struct ksz_sw_info *info = sw->info;

	for (i = BROADCAST_ENTRY; i <= IPV6_ADDR_ENTRY; i++) {
		entry = &info->mac_table[i];
		switch (i) {
		case BROADCAST_ENTRY:
			memset(entry->addr, 0xFF, ETH_ALEN);
			break;
		case BRIDGE_ADDR_ENTRY:
			memcpy(entry->addr, info->br_addr, ETH_ALEN);
			break;
		case IPV6_ADDR_ENTRY:
			memcpy(entry->addr, info->br_addr, ETH_ALEN);
			entry->addr[0] = 0x33;
			entry->addr[1] = 0x33;
			entry->addr[2] = 0xFF;
			break;
		}
		entry->ports = sw->HOST_MASK;
		entry->valid = 1;
		alu = &info->alu_table[i];
		sw_w_sta_mac_table(sw, alu->index, alu->type, entry);
	}
}  /* sw_pass_addr */

static void sw_pass_multi(struct ksz_sw *sw)
{
	struct ksz_mac_table *entry;
	struct ksz_alu_table *alu;
	int i;
	struct ksz_sw_info *info = sw->info;

	for (i = STATIC_MAC_TABLE_ENTRIES; i < MULTI_MAC_TABLE_ENTRIES; i++) {
		entry = &info->mac_table[i];
		if (entry->ports) {
			entry->valid = 1;
			alu = &info->alu_table[i];
			if (2 == alu->type)
				sw_w_dyn_mac_table(sw, alu->index,
					entry->addr, entry->fid, entry);
			else if (alu->type < 2)
				sw_w_sta_mac_table(sw, alu->index, alu->type,
					entry);
		}
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
	for (port = 0; port < sw->mib_port_cnt; port++) {
		int index = port;
		struct net_device *dev;

		if (port == sw->HOST_PORT)
			continue;
		if (port > sw->HOST_PORT)
			--index;
		dev = sw->netdev[index + sw->dev_offset];
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
	for (port = 0; port < sw->mib_port_cnt; port++) {
		if (port == sw->HOST_PORT)
			continue;
		if (forwarding[port])
			port_set_stp_state(sw, port, STP_STATE_FORWARDING);
	}
	sw->ops->release(sw);
	if (prev_stp != info->stp && !info->stp)
		memset(info->br_addr, 0, ETH_ALEN);
	if (stp_down != info->stp_down || prev_stp != info->stp) {
		struct ksz_mac_table *entry = &sw->info->mac_table[0];
		struct ksz_alu_table *alu = &sw->info->alu_table[0];
		int valid = entry->valid;

		if (stp_down == info->stp) {

			/* Turn off STP only when it is already setup. */
			if (prev_stp == info->stp)
				entry->valid = 0;
		} else if (info->stp_down == info->stp ||
				(!prev_stp && info->stp))
			entry->valid = 1;
		if (valid != entry->valid) {

			/* Cannot really disable the entry. */
			if (entry->valid)
				entry->override = 1;
			else
				entry->override = 0;
			sw_w_sta_mac_table(sw, alu->index, alu->type, entry);

			/* No ports in forwarding state. */
			if (!entry->valid) {
				sw->ops->acquire(sw);
				port_set_stp_state(sw, SWITCH_PORT_NUM,
					STP_STATE_SIMPLE);
				sw->ops->release(sw);
				sw_block_addr(sw);
				sw_block_multi(sw);
			}
		}

		/* Update disabled ports when STP is settled down. */
		if (prev_stp == info->stp)
			info->stp_down = stp_down;
	}

	if (member != info->member) {
		int cnt = 0;

		for (port = 0; port < sw->mib_port_cnt; port++) {
			if (port == sw->HOST_PORT)
				continue;
			if (member & (1 << port))
				cnt++;
		}
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

		/* Port does not have PHY. */
		if (p >= sw->phy_port_cnt) {
			break;
		}

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

static u16 port_advertised_flow_ctrl(struct ksz_port *port, u16 ctrl)
{
	ctrl &= ~PORT_AUTO_NEG_PAUSE;
	switch (port->flow_ctrl) {
	case PHY_FLOW_CTRL:
		ctrl |= PORT_AUTO_NEG_SYM_PAUSE;
		break;
	case PHY_TX_ONLY:
		ctrl |= PORT_AUTO_NEG_ASYM_PAUSE;
		break;
	case PHY_RX_ONLY:
		ctrl |= PORT_AUTO_NEG_PAUSE;
		break;
	default:
		break;
	}
	return ctrl;
}  /* port_advertised_flow_ctrl */

static u8 sw_determine_flow_ctrl(struct ksz_sw *sw, struct ksz_port *port,
	u16 local, u16 remote)
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
		else if ((remote & PORT_AUTO_NEG_ASYM_PAUSE) &&
			 (local & PORT_AUTO_NEG_PAUSE) ==
			 PORT_AUTO_NEG_ASYM_PAUSE)
			tx = 1;
	} else if (remote & PORT_AUTO_NEG_ASYM_PAUSE) {
		if ((local & PORT_AUTO_NEG_PAUSE) == PORT_AUTO_NEG_PAUSE)
			rx = 1;
	}
	if (rx)
		flow |= 0x01;
	if (tx)
		flow |= 0x02;
#ifdef DEBUG
	printk(KERN_INFO "pause: %d, %d; %04x %04x\n",
		rx, tx, local, remote);
#endif
	return flow;
}  /* sw_determine_flow_ctrl */

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
	u16 data;
	u16 link;
	u16 dbg_link;
	u16 status;
	u32 local;
	u32 remote;
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

		/* Port does not have PHY. */
		if (p >= sw->phy_port_cnt)
			break;

		if (!(sw->phy_intr & (1 << p)))
			continue;

		info = &sw->port_info[p];
		state = &sw->port_state[p];

#ifndef NO_PHY_READ
		port_r16(sw, p, REG_PORT_PHY_1000_CTRL, &data);
		local = data;
		local <<= 16;
		port_r16(sw, p, REG_PORT_PHY_AUTO_NEGOTIATION, &data);
		local |= data;
		port_r16(sw, p, REG_PORT_PHY_1000_STATUS, &data);
		remote = data;
		remote &= PORT_PHY_1000_STATIC_STATUS;
		remote <<= 16;
		port_r16(sw, p, REG_PORT_PHY_REMOTE_CAPABILITY, &data);
		remote |= data;
		port_r16(sw, p, P_LINK_STATUS, &link);

		/* Read second time in case the status is not latched. */
		if (!(link & PORT_LINK_STATUS))
			port_r16(sw, p, P_LINK_STATUS, &link);

		/* SPI has problem reading the link status from the PHY. */
		dbg_link = link;
		port_r16(sw, p, P_SPEED_STATUS, &status);
		if (!(sw->features & NEW_CAP) &&
		    ((link & PORT_AUTO_NEG_ACKNOWLEDGE) && (status &
		    (PORT_STAT_SPEED_1000MBIT |
		     PORT_STAT_SPEED_100MBIT |
		     PORT_STAT_SPEED_10MBIT))))
			link |= PORT_LINK_STATUS;
#else
		link = PORT_LINK_STATUS;
		dbg_link = link;
		local = 0x10001000;
		remote = 0x10001000;
#endif
		/*
		 * The partner capability register is updated but the
		 * auto-negotiation is not completed yet.
		 */
		link &= (PORT_AUTO_NEG_ACKNOWLEDGE | PORT_LINK_STATUS);

		if (link & PORT_LINK_STATUS) {

			/* Remember the first linked port. */
#if 1
			if (!linked && p != sw->HOST_PORT)
#else
			if (!linked)
#endif
				linked = info;
		}

		/* No change to status. */
		if (local == info->advertised && (u8) link == info->link)
			continue;

		if (!(dbg_link & PORT_LINK_STATUS) &&
		    dbg_link & PORT_AUTO_NEG_ACKNOWLEDGE)
dbg_msg(" link? %d=%04x\n", p, dbg_link);
#ifdef DEBUG
		printk(KERN_INFO
			"%d=advertised: %08X-%08X; partner: %08X-%08X\n", p,
			local, info->advertised, remote, info->partner);
#endif
		info->report = true;
		info->advertised = local;
		info->partner = remote;
		info->link = (u8) link;
		if (link & PORT_LINK_STATUS) {
#ifdef NO_PHY_READ
			status = PORT_STAT_SPEED_100MBIT |
				PORT_STAT_FULL_DUPLEX;
#endif
			info->tx_rate = 10 * TX_RATE_UNIT;
			if (status & PORT_STAT_SPEED_100MBIT)
				info->tx_rate = 100 * TX_RATE_UNIT;
			else if (status & PORT_STAT_SPEED_1000MBIT)
				info->tx_rate = 1000 * TX_RATE_UNIT;

			info->duplex = 1;
			if (status & PORT_STAT_FULL_DUPLEX)
				info->duplex = 2;

			if (media_connected != info->state) {
#ifndef NO_PHY_READ
				SW_D flow_ctrl;

				port_r(sw, p, REG_PORT_STATUS_0, &flow_ctrl);
#ifdef DEBUG
				printk(KERN_INFO "flow_ctrl: "SW_SIZE_STR"\n",
					flow_ctrl & (PORT_RX_FLOW_CTRL |
					PORT_TX_FLOW_CTRL));
#endif
				info->flow_ctrl = sw_determine_flow_ctrl(sw,
					port, local, remote);
				if (flow_ctrl & PORT_RX_FLOW_CTRL)
					info->flow_ctrl |= 0x10;
				if (flow_ctrl & PORT_TX_FLOW_CTRL)
					info->flow_ctrl |= 0x20;
				if (sw->info)
					port_cfg_back_pressure(sw, p,
						(1 == info->duplex));
#endif
				change |= 1 << i;
			}
			info->state = media_connected;
			state->tx_rate = info->tx_rate;
		} else {
			if (media_disconnected != info->state) {
				change |= 1 << i;

				/* Indicate the link just goes down. */
				state->link_down = 1;
			}
			info->state = media_disconnected;
		}
#ifdef CONFIG_1588_PTP
		if (sw->features & PTP_HW) {
			struct ptp_info *ptp = &sw->ptp_hw;

			if (media_disconnected == info->state)
				ptp->linked[p] = 0;
			else {
				ptp->linked[p] = info->tx_rate / TX_RATE_UNIT;
				ptp->linked[p] |= 0x80000000;
			}
		}
#endif
#ifdef KSZ_MRP
		if (sw->features & MRP_SUPPORT) {
			u32 speed;
			struct mrp_info *mrp = &sw->mrp;

			if (media_disconnected == info->state)
				speed = 0;
			else
				speed = info->tx_rate / TX_RATE_UNIT;
			mrp_set_speed(mrp, p, speed);
		}
#endif
		state->state = info->state;
	}
	sw->phy_intr = 0;

	if (linked && media_disconnected == port->linked->state)
		port->linked = linked;

#ifdef CONFIG_1588_PTP
	if ((sw->features & PTP_HW) && change) {
		struct ptp_info *ptp = &sw->ptp_hw;

		for (i = sw->phy_port_cnt; i < ptp->ports; i++) {
			if (media_disconnected == port->linked->state)
				ptp->linked[i] = 0;
			else
				ptp->linked[i] = 1000;
		}
		if (ptp->started)
			schedule_work(&ptp->set_latency);
	}
#endif
#ifdef DEBUG
	if (change)
		dbp_link(port, sw, change);
#endif
#ifdef KSZ_IBA
	change |= sw->link_change;
	sw->link_change = 0;
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
	u16 data;
	u16 ctrl;
	u16 local;
	u16 status;
	u32 adv;
	u32 cfg;
	int i;
	int p;

#ifdef NO_PHY_READ
if (port)
	return;
#endif
	for (i = 0, p = port->first_port; i < port->port_cnt; i++, p++) {

		/* Port does not have PHY. */
		if (p >= sw->phy_port_cnt)
			break;

		/* Host port is not at either end. */
		if (p == sw->HOST_PORT)
			continue;

		port_r16(sw, p, REG_PORT_PHY_1000_CTRL, &ctrl);
		port_r16(sw, p, REG_PORT_PHY_AUTO_NEGOTIATION, &local);
		if (!(local & PORT_AUTO_NEG_SYM_PAUSE))
			dbg_msg(" no sym pause: %d %04x\n", p, local);
		if (local & PORT_AUTO_NEG_ASYM_PAUSE)
			dbg_msg(" has asym pause: %d %04x\n", p, local);
		adv = ctrl;
		adv <<= 16;
		adv |= local;
		port_r16(sw, p, P_SPEED_STATUS, &status);
		port_r16(sw, p, P_NEG_RESTART_CTRL, &data);

		cfg = 0;

		/*
		 * Do not need to restart auto-negotiation if desired settings
		 * are same.
		 */
		if ((data & PORT_AUTO_NEG_ENABLE) &&
		    (status &
		    (PORT_STAT_SPEED_1000MBIT |
		     PORT_STAT_SPEED_100MBIT |
		     PORT_STAT_SPEED_10MBIT)))
			cfg = adv;

		local = port_advertised_flow_ctrl(port, local);

		ctrl |= PORT_AUTO_NEG_1000BT_FD | PORT_AUTO_NEG_1000BT;
		local |= PORT_AUTO_NEG_100BTX_FD | PORT_AUTO_NEG_100BTX |
			PORT_AUTO_NEG_10BT_FD | PORT_AUTO_NEG_10BT;

		/* Check if manual configuration is specified by the user. */
		if (port->speed || port->duplex) {
			if (port->speed && port->speed != 1000)
				ctrl &= ~(PORT_AUTO_NEG_1000BT_FD |
					PORT_AUTO_NEG_1000BT);
			if (10 == port->speed)
				local &= ~(PORT_AUTO_NEG_100BTX_FD |
					PORT_AUTO_NEG_100BTX);
			else if (100 == port->speed)
				local &= ~(PORT_AUTO_NEG_10BT_FD |
					PORT_AUTO_NEG_10BT);
			else if (1000 == port->speed)
				local &= ~(PORT_AUTO_NEG_100BTX_FD |
					PORT_AUTO_NEG_100BTX |
					PORT_AUTO_NEG_10BT_FD |
					PORT_AUTO_NEG_10BT);
			if (1 == port->duplex) {
				ctrl &= ~PORT_AUTO_NEG_1000BT_FD;
				local &= ~(PORT_AUTO_NEG_100BTX_FD |
					PORT_AUTO_NEG_10BT_FD);
			} else if (2 == port->duplex) {
				ctrl &= ~PORT_AUTO_NEG_1000BT;
				local &= ~(PORT_AUTO_NEG_100BTX |
					PORT_AUTO_NEG_10BT);
			}
		}
		adv = ctrl;
		adv <<= 16;
		adv |= local;
		if (adv != cfg) {
			port_w16(sw, p, REG_PORT_PHY_1000_CTRL, ctrl);
			port_w16(sw, p, REG_PORT_PHY_AUTO_NEGOTIATION, local);
			port_r16(sw, p, P_NEG_RESTART_CTRL, &data);
			data |= PORT_AUTO_NEG_ENABLE;
			data |= PORT_AUTO_NEG_RESTART;
			port_w16(sw, p, P_NEG_RESTART_CTRL, data);

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
	u16 data;
	int i;
	int p;

#ifdef NO_PHY_READ
if (port)
	return;
#endif
	for (i = 0, p = port->first_port; i < port->port_cnt; i++, p++) {

		/* Port does not have PHY. */
		if (p >= sw->phy_port_cnt) {
			break;
		}

		/* Host port is not at either end. */
		if (p == sw->HOST_PORT)
			continue;

		port_r16(sw, p, P_PHY_CTRL, &data);
		data &= ~(PORT_AUTO_NEG_ENABLE |
			PORT_SPEED_100MBIT | PORT_SPEED_1000MBIT);
		if (100 == port->speed)
			data |= PORT_SPEED_100MBIT;
		else if (1000 == port->speed)
			data |= PORT_SPEED_1000MBIT;
		if (1 == port->duplex)
			data &= ~PORT_FULL_DUPLEX;
		else if (2 == port->duplex)
			data |= PORT_FULL_DUPLEX;
		port_w16(sw, p, P_PHY_CTRL, data);
	}
}  /* port_force_link_speed */

static void port_mmd_read(struct ksz_sw *sw, int port, u16 devid, u16 reg,
	u16 *buf, u16 len)
{
	port_w16(sw, port, REG_PORT_PHY_MMD_SETUP,
		MMD_SETUP(PORT_MMD_OP_INDEX, devid));
	port_w16(sw, port, REG_PORT_PHY_MMD_INDEX_DATA, reg);
	if (len > 1)
		port_w16(sw, port, REG_PORT_PHY_MMD_SETUP,
			MMD_SETUP(PORT_MMD_OP_DATA_INCR_RW, devid));
	else
		port_w16(sw, port, REG_PORT_PHY_MMD_SETUP,
			MMD_SETUP(PORT_MMD_OP_DATA_NO_INCR, devid));
	while (len) {
		port_r16(sw, port, REG_PORT_PHY_MMD_INDEX_DATA, buf);
		buf++;
		len--;
	}
}  /* port_mmd_read */

static void port_mmd_write(struct ksz_sw *sw, int port, u16 devid, u16 reg,
	u16 *buf, u16 len)
{
	port_w16(sw, port, REG_PORT_PHY_MMD_SETUP,
		MMD_SETUP(PORT_MMD_OP_INDEX, devid));
	port_w16(sw, port, REG_PORT_PHY_MMD_INDEX_DATA, reg);
	if (len > 1)
		port_w16(sw, port, REG_PORT_PHY_MMD_SETUP,
			MMD_SETUP(PORT_MMD_OP_DATA_INCR_W, devid));
	else
		port_w16(sw, port, REG_PORT_PHY_MMD_SETUP,
			MMD_SETUP(PORT_MMD_OP_DATA_NO_INCR, devid));
	while (len) {
		port_w16(sw, port, REG_PORT_PHY_MMD_INDEX_DATA, *buf);
		buf++;
		len--;
	}
}  /* port_mmd_write */

static void port_setup_eee(struct ksz_sw *sw, int port)
{
	u16 val[0x20];

dbg_msg("%s %d\n", __func__, port);
	if (sw->features & NEW_CAP) {
#if 1
if (0 == port) {
int i;
		port_r16(sw, port, REG_PORT_PHY_CTRL, val);
dbg_msg("%04x=%04x\n", REG_PORT_PHY_CTRL, val[0]);
		port_r16(sw, port, REG_PORT_PHY_REMOTE_LB_LED, val);
dbg_msg("%04x=%04x\n", REG_PORT_PHY_REMOTE_LB_LED, val[0]);

dbg_msg(" %x\n", MMD_DEVICE_ID_DSP);
		port_mmd_read(sw, port, MMD_DEVICE_ID_DSP, 0xCE, val, 1);
dbg_msg(" %04x=%04x\n", 0xCE, val[0]);
		port_mmd_read(sw, port, MMD_DEVICE_ID_DSP, 0xCC, val, 1);
dbg_msg(" %04x=%04x\n", 0xCC, val[0]);
		port_mmd_read(sw, port, MMD_DEVICE_ID_DSP, 0xCA, val, 1);
dbg_msg(" %04x=%04x\n", 0xCA, val[0]);
		port_mmd_read(sw, port, MMD_DEVICE_ID_DSP, 0xCB, val, 1);
dbg_msg(" %04x=%04x\n", 0xCB, val[0]);
		port_mmd_read(sw, port, MMD_DEVICE_ID_DSP, 0xC8, val, 1);
dbg_msg(" %04x=%04x\n", 0xC8, val[0]);
		port_mmd_read(sw, port, MMD_DEVICE_ID_DSP, 0xD9, val, 1);
dbg_msg(" %04x=%04x\n", 0xD9, val[0]);
		port_mmd_read(sw, port, MMD_DEVICE_ID_DSP, 0xC9, val, 1);
dbg_msg(" %04x=%04x\n", 0xC9, val[0]);

		port_mmd_read(sw, port, MMD_DEVICE_ID_DSP, 0x79, &val[0x09],
			18);
for (i = 0; i < 18; i++)
dbg_msg("%04x ", val[0x09 + i]);
dbg_msg("\n");

		port_mmd_read(sw, port, MMD_DEVICE_ID_DSP, 0x8F, val, 1);
dbg_msg(" %04x=%04x\n", 0x8F, val[0]);
		port_mmd_read(sw, port, MMD_DEVICE_ID_DSP, 0x9D, val, 1);
dbg_msg(" %04x=%04x\n", 0x9D, val[0]);

		port_mmd_read(sw, port, MMD_DEVICE_ID_DSP, 0x75, val, 1);
dbg_msg(" %04x=%04x\n", 0x75, val[0]);
		port_mmd_read(sw, port, MMD_DEVICE_ID_DSP, 0xD3, val, 1);
dbg_msg(" %04x=%04x\n", 0xD3, val[0]);

dbg_msg(" %x\n", MMD_DEVICE_ID_AFED);
		port_mmd_read(sw, port, 0x1C, 0x0, val, 1);
dbg_msg(" %04x=%04x\n", 0x0, val[0]);
		port_mmd_read(sw, port, 0x1C, 0x4, val, 1);
dbg_msg(" %04x=%04x\n", 0x4, val[0]);
		port_mmd_read(sw, port, 0x1C, 0x6, val, 1);
dbg_msg(" %04x=%04x\n", 0x6, val[0]);
		port_mmd_read(sw, port, 0x1C, 0x9, val, 1);
dbg_msg(" %04x=%04x\n", 0x9, val[0]);

		port_mmd_read(sw, port, 0x1C, 0x13, &val[0x13], 12);
for (i = 0; i < 12; i++)
dbg_msg("%04x ", val[0x13 + i]);
dbg_msg("\n");
}
#endif

		port_w16(sw, port, REG_PORT_PHY_CTRL, 0x2100);
		port_w16(sw, port, REG_PORT_PHY_REMOTE_LB_LED, 0x00f0);

		val[0] = 0x0100;
		port_mmd_write(sw, port, MMD_DEVICE_ID_DSP, 0xCE, val, 1);
		val[0] = 0x0ff0;
		port_mmd_write(sw, port, MMD_DEVICE_ID_DSP, 0xCC, val, 1);
		val[0] = 0x0141;
		port_mmd_write(sw, port, MMD_DEVICE_ID_DSP, 0xCA, val, 1);
		val[0] = 0x0fcf;
		port_mmd_write(sw, port, MMD_DEVICE_ID_DSP, 0xCB, val, 1);
		val[0] = 0x0010;
		port_mmd_write(sw, port, MMD_DEVICE_ID_DSP, 0xC8, val, 1);
		val[0] = 0x0100;
		port_mmd_write(sw, port, MMD_DEVICE_ID_DSP, 0xD9, val, 1);
		val[0] = 0x0280;
		port_mmd_write(sw, port, MMD_DEVICE_ID_DSP, 0xC9, val, 1);

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
		port_mmd_write(sw, port, MMD_DEVICE_ID_DSP, 0x79, &val[0x09],
			18);

		val[0] = 0x6032;
		port_mmd_write(sw, port, MMD_DEVICE_ID_DSP, 0x8F, val, 1);
		val[0] = 0x248C;
		port_mmd_write(sw, port, MMD_DEVICE_ID_DSP, 0x9D, val, 1);

		val[0] = 0x0060;
		port_mmd_write(sw, port, MMD_DEVICE_ID_DSP, 0x75, val, 1);
		val[0] = 0x7777;
		port_mmd_write(sw, port, MMD_DEVICE_ID_DSP, 0xD3, val, 1);

		val[0] = 0x9400;
		port_mmd_write(sw, port, MMD_DEVICE_ID_AFED, 0x0, val, 1);
		val[0] = 0x0000;
		port_mmd_write(sw, port, MMD_DEVICE_ID_AFED, 0x4, val, 1);
		val[0] = 0x3100;
		port_mmd_write(sw, port, MMD_DEVICE_ID_AFED, 0x6, val, 1);
		val[0] = 0xe01c;
		port_mmd_write(sw, port, MMD_DEVICE_ID_AFED, 0x9, val, 1);

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
		port_mmd_write(sw, port, MMD_DEVICE_ID_AFED, 0x13, &val[0x13],
			12);

		if (port == sw->HOST_PORT)
			port_w16(sw, port, REG_PORT_PHY_CTRL, 0x1140);
	} else {
		memset(val, 0, sizeof(val));
		port_mmd_write(sw, port, 0x1C, 0x10, val, 0x11);
	}
}  /* port_setup_eee */

static void port_setup_9893(struct ksz_sw *sw, int port)
{
	u16 val[0x40];
	int i;

dbg_msg("%s %d\n", __func__, port);
	memset(val, 0, sizeof(val));
	port_mmd_read(sw, port, 0x1C, 0x0, val, 0x35);
	if (0x0008 == val[6])
		return;
	for (i = 0; i < 0x35; i++) {
dbg_msg("%04x ", val[i]);
		if ((i % 0x10) == 0xf)
dbg_msg("\n");
	}
dbg_msg("\n");

#if 0
	port_w16(sw, port, REG_PORT_PHY_CTRL, 0);
#else
	port_w16(sw, port, REG_PORT_PHY_CTRL, 0x2100);
#endif

	val[0] = 0x0240;
	port_mmd_write(sw, port, 0x1C, 0x0, val, 1);

	val[0x11] = 0x7777;
	port_mmd_write(sw, port, 0x1C, 0x11, &val[0x11], 1);

	val[0x13] = 0x0077;
	val[0x14] = 0x0077;
	val[0x15] = 0x7777;
	val[0x16] = 0x7777;
	val[0x17] = 0x0077;
	val[0x18] = 0x4377;
	val[0x19] = 0x4377;
	val[0x1a] = 0x6777;
	val[0x1b] = 0x0777;
	val[0x1c] = 0x0777;
	val[0x1d] = 0x6777;
	val[0x1e] = 0x6777;
	port_mmd_write(sw, port, 0x1C, 0x13, &val[0x13], 12);

	val[0x20] = 0x0;
	port_mmd_write(sw, port, 0x1C, 0x20, &val[0x20], 1);

	val[0x6] = 0x0008;
	port_mmd_write(sw, port, 0x1C, 0x6, &val[0x6], 1);

	val[0x25] = 0x0;
	val[0x26] = 0x1f10;
	val[0x27] = 0x1f1f;
	val[0x28] = 0x0f00;
	val[0x29] = 0x0;
	val[0x2a] = 0x0;
	val[0x2b] = 0x0;
	val[0x2c] = 0x0;
	val[0x2d] = 0x0;
	val[0x2e] = 0x0;
	val[0x2f] = 0x0;
	val[0x30] = 0x0;
	val[0x31] = 0x0;
	val[0x32] = 0x0;
	val[0x33] = 0x0;
	val[0x34] = 0x0;
	port_mmd_write(sw, port, 0x1C, 0x25, &val[0x25], 16);

	val[0] = 0x80e6;
	port_mmd_write(sw, port, 0x1, 0xd8, val, 1);
	val[0] = 0x02ff;
	port_mmd_write(sw, port, 0x1, 0xc9, val, 1);

#if 0
	port_w16(sw, port, REG_PORT_PHY_CTRL, 0x1340);
#else
	port_w16(sw, port, REG_PORT_PHY_CTRL, 0x1140);
#endif
}  /* port_setup_9893 */

/**
 * sw_enable - enable the switch
 * @sw:		The switch instance.
 *
 * This routine enables the switch with a specific configuration.
 */
static void sw_enable(struct ksz_sw *sw)
{
	int port;

	for (port = 0; port < sw->mib_port_cnt; port++) {
		if (port == sw->HOST_PORT)
			continue;
		if (sw->dev_count > 1)
			port_set_stp_state(sw, port, STP_STATE_DISABLED);
		else
			port_set_stp_state(sw, port, STP_STATE_FORWARDING);
	}
	if (sw->dev_count > 1)
		port_set_stp_state(sw, sw->HOST_PORT, STP_STATE_SIMPLE);
	else
		port_set_stp_state(sw, sw->HOST_PORT, STP_STATE_FORWARDING);

	/*
	 * There may be some entries in the dynamic MAC table before the
	 * the learning is turned off.  Once the entries in the table the
	 * switch may keep updating them even learning is off.
	 */
	if (sw->dev_count > 1)
		sw_flush_dyn_mac_table(sw, sw->mib_port_cnt);
}  /* sw_enable */

static void sw_init_cached_regs(struct ksz_sw *sw)
{
	sw->cached.ptp_clk_ctrl = sw->reg->r16(sw, REG_PTP_CLK_CTRL);
	sw->cached.ptp_unit_index = sw->reg->r32(sw, REG_PTP_UNIT_INDEX__4);
}

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
#if defined(NO_DIRECT_ACCESS)
if (!sw->info->iba.use_iba) {
printk("%s\n", __func__);
return;
}
#endif
	sw_init_cached_regs(sw);
#ifdef SWITCH_PORT_PHY_ADDR_MASK
	sw_init_phy_addr(sw);
#endif

	sw_init_broad_storm(sw);

	sw_init_prio(sw);

	sw_init_prio_rate(sw);

	sw_init_vlan(sw);

	sw_init_acl(sw);
#if 0
	if (!sw_chk(sw, REG_SWITCH_CTRL_1,
			SWITCH_TX_FLOW_CTRL | SWITCH_RX_FLOW_CTRL))
		sw->overrides |= PAUSE_FLOW_CTRL;
#endif
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

	sw->port_intr_mask = sw->PORT_MASK;
	sw->intr_mask = TRIG_TS_INT | APB_TIMEOUT_INT;
#if defined(NO_DIRECT_ACCESS)
if (!sw->info->iba.use_iba) {
printk("%s\n", __func__);
return;
}
#endif
	sw_set_global_ctrl(sw);
	sw_setup_reserved_multicast(sw);
#if 0
	sw->reg->w16(sw, REG_SW_ISP_TPID__2, 0x88A8);
#endif
/*
 * THa  2015/12/03
 * The new chip does not require legal packet check to be disabled for the tail
 * tagging to work, but it still counts packets as oversized.
 */
#if 0
	if (!(sw->features & NEW_CAP))
#endif
		sw_cfg(sw, REG_SW_MAC_CTRL_1, SW_LEGAL_PACKET_DISABLE, 1);

	for (port = 0; port < sw->mib_port_cnt; port++) {
		sw->info->port_cfg[port].intr_mask = 0;
		port_cfg_back_pressure(sw, port, 1);
		if (port < sw->phy_port_cnt)
			port_cfg_force_flow_ctrl(sw, port, 0);
		else
			port_cfg_force_flow_ctrl(sw, port, 1);
#ifndef KSZ_DLR
		if (!(sw->features & ACL_CORRUPT_BUG))
#endif
			sw->info->port_cfg[port].intr_mask |= PORT_ACL_INT;
		if (port == sw->HOST_PORT)
			continue;

#ifdef CONFIG_1588_PTP
		sw->info->port_cfg[port].intr_mask |= PORT_PTP_INT;
#endif
	}
/*
 * THa  2015/10/01
 * Increasing wait time in this register avoids the PTP transmit problem.
 */
	dbg_msg("eee txq wait: %04x\n",
		sw->reg->r16(sw, REG_SW_EEE_TXQ_WAIT_TIME__2));
	sw->reg->w16(sw, REG_SW_EEE_TXQ_WAIT_TIME__2, 0x0040);

#ifndef KSZ9897_FPGA
	for (port = 0; port < sw->phy_port_cnt; port++) {
		u16 val = 0;

#if 0
		port_r16(sw, port, REG_PORT_PHY_DIGITAL_DEBUG_1, &val);
		val |= PORT_REG_CLK_SPEED_25_MHZ;
		port_w16(sw, port, REG_PORT_PHY_DIGITAL_DEBUG_1, val);
		delay_milli(1);
#endif

		if (sw->features & SETUP_PHY)
			port_setup_9893(sw, port);
		port_setup_eee(sw, port);
#ifdef NO_EEE
		/* Disable EEE for now. */
		port_mmd_read(sw, port, MMD_DEVICE_ID_EEE_ADV, MMD_EEE_ADV,
			&val, 1);
/*
 * THa  2015/09/30
 * EEE in gigabit causes PTP messages not to be sent immediately.
 * Just advertise EEE in 100 causes link not to be established.
 * EEE in 100 has too much PTP jitter.
 */
		val = 0;
		port_mmd_write(sw, port, MMD_DEVICE_ID_EEE_ADV, MMD_EEE_ADV,
			&val, 1);
#endif

		/*
		 * Switch actually cannot do auto-negotiation with old 10Mbit
		 * hub.
		 */
		port_r16(sw, port, P_PHY_CTRL, &val);
		val &= ~PORT_FULL_DUPLEX;
		port_w16(sw, port, P_PHY_CTRL, val);

/*
 * THa  2015/10/07
 * The S2 chip has a bug that writing to the 0xN13E register will cause the
 * 100Mbit link to be unstable.
 * One way to workaround is to use 25 MHz clock speed for register access.
 */
#if 0
		/* Enable port PHY interrupt. */
		sw->info->port_cfg[port].intr_mask |= PORT_PHY_INT;

		port_r16(sw, port, REG_PORT_PHY_PHY_CTRL, &val);

		/* Normally it should be low? */
		val |= PORT_INT_PIN_HIGH;
		port_w16(sw, port, REG_PORT_PHY_PHY_CTRL, val);
		val = LINK_DOWN_INT | LINK_UP_INT;

#if 1
/*
 * THa  2014/06/25
 * SPI cannot just read PHY interrupt status register to clear interrupts.
 * No way to clear the interrupts so cannot enable them here.
 */
		if (!(sw->features & NEW_CAP))
			val = 0;
#endif
		port_w8(sw, port, REG_PORT_PHY_INT_ENABLE, val);

/*
 * THa  2015/09/17
 * The S2 chip has a strange bug that if PHY register 0x0136 is accessed last,
 * either read or write, the global port interrupt status 0x0018 and individual
 * port status register 0x001B do not indicate PHY interrupt even though the
 * actual interrupt is triggered by plugging in or out the cable.
 */
		port_r16(sw, port, REG_PORT_PHY_PHY_CTRL, &val);

/*
 * THa  2014/11/18
 * The new KSZ9893 chip has a bug related to IBA.  When writing PHY related
 * registers with SPI while IBA is enabled APB interrupt can be triggered.
 * Somehow the hardware expects those writes be 32-bit.  By itself this bug is
 * just an annoyance, but port 2 has additional problem.
 * After IBA are run the next initialization triggers a more serioud bug.
 * Instead of generating APB interrupt the PHY_PHY_CTRL register 0x213E is
 * reset to 0 by the hardware.  Writing to the PHY_INT_ENABLE register, even
 * with a zero value, will generate the PHY interrupt with no actual PHY
 * status.  As the interrupt pin is no longer high, the interrupt will keep
 * coming until it is masked out or the interrupt pin is set to high again.
 */
#endif
	}
#endif
#if 0
	for (port = 0; port < sw->phy_port_cnt; port++) {
#ifdef KSZ_IBA
		if (port == sw->HOST_PORT) {
			port_w8(sw, port, REG_PORT_MAC_CTRL_2, 0);
			continue;
		}
#endif
		port_w8(sw, port, REG_PORT_MAC_CTRL_2,
#if 1
			PORT_100BT_EEE_DISABLE |
#endif
			PORT_1000BT_EEE_DISABLE);
	}
#endif
#ifdef KSZ9897_FPGA
printk("setup PHY ports\n");
if (3 == sw->phy_port_cnt)
	do {
		int i;
		struct ksz_port_info *info;

		for (i = 0; i < sw->phy_port_cnt; i++) {
			port_w8(sw, i, 0x111, 1);
			port_w8(sw, i, 0x110, 3);
			info = &sw->port_info[i];
			info->state = media_connected;
			info->tx_rate = 100 * TX_RATE_UNIT;
			info->duplex = 2;
		}
	} while (0);
#endif

	sw_setup_broad_storm(sw);

	sw_setup_prio(sw);

	sw_setup_mirror(sw);

	sw->info->multi_net = SWITCH_MAC_TABLE_ENTRIES;
	if (sw->features & STP_SUPPORT) {
		sw_setup_stp(sw);
#ifdef CONFIG_KSZ_STP
		sw_setup_multi(sw);
#ifdef CONFIG_1588_PTP
		sw_setup_ptp(sw);
#endif
#endif
	}
#ifdef KSZ_IBA
	sw_setup_iba(sw);
#endif
#ifdef KSZ_DLR
	if (sw->features & DLR_HW)
		sw_setup_dlr(sw);
#endif
	sw_enable(sw);
}  /* sw_setup */

static void sw_reset(struct ksz_sw *sw)
{
#if defined(NO_DIRECT_ACCESS)
if (!sw->info->iba.use_iba) {
printk("%s\n", __func__);
return;
}
#endif
	sw->overrides &= ~VLAN_SET;
	if (sw->features & NEW_CAP) {
		int p;
		u8 byte_before;
		u8 byte_after;

		sw_cfg(sw, REG_SW_OPERATION, SW_RESET, 1);
		delay_micro(1);

/*
 * THa  2015/10/07
 * The S2 chip has a bug that writing to the 0xN13E register will cause the
 * 100Mbit link to be unstable.
 * One way to workaround is to use 25 MHz clock speed for register access.
 */
#if 0
		/* PHY interrupt level is not in normal position. */
		for (p = 0; p < sw->phy_port_cnt; p++) {
			u16 val;

			port_r16(sw, p, REG_PORT_PHY_DIGITAL_DEBUG_1, &val);
			val |= PORT_REG_CLK_SPEED_25_MHZ;
			port_w16(sw, p, REG_PORT_PHY_DIGITAL_DEBUG_1, val);
			delay_milli(1);

			port_r16(sw, p, REG_PORT_PHY_PHY_CTRL, &val);

			val |= PORT_INT_PIN_HIGH;
/*
 * THa  2015/09/17
 * The S2 chip has a strange bug that if PHY register 0x0136 is accessed last,
 * either read or write, the global port interrupt status 0x0018 and individual
 * port status register 0x001B do not indicate PHY interrupt even though the
 * actual interrupt is triggered by plugging in or out the cable.
 */
			port_w16(sw, p, REG_PORT_PHY_PHY_CTRL, val);
		}
#endif
		for (p = sw->phy_port_cnt; p < sw->mib_port_cnt; p++) {
			port_r(sw, p, REG_PORT_XMII_CTRL_1, &byte_before);
			byte_after = byte_before ^(PORT_MII_NOT_1GBIT |
				PORT_MII_MAC_MODE | PORT_MII_SEL_M);
			port_w(sw, p, REG_PORT_XMII_CTRL_1, byte_after);
			port_w(sw, p, REG_PORT_XMII_CTRL_1, byte_before);
		}
		sw_reset_acl(sw);
		sw->overrides &= ~TAIL_TAGGING;
		sw->overrides &= ~PTP_TAG;
		sw->overrides &= ~TAG_REMOVE;
		sw_dis_intr(sw);
		return;
	}

	/* There is no global reset function yet. */
	sw_dis_vlan(sw);
	do {
		int p;

		/* Need to turn on ACL to write to ACL table. */
		for (p = 0; p < sw->mib_port_cnt; p++) {
			port_cfg_acl(sw, p, 1);
			port_w16(sw, p, REG_PORT_ACL_BYTE_EN_MSB, 0xffff);
		}
		sw_reset_acl_hw(sw);
		for (p = 0; p < sw->mib_port_cnt; p++) {
			if (p == sw->HOST_PORT)
				continue;
			if (sw->dev_count > 1)
				sw_cfg_port_base_vlan(sw, p, sw->PORT_MASK);
			port_set_stp_state(sw, p, STP_STATE_FORWARDING);
		}
		for (p = 0; p < sw->mib_port_cnt; p++) {
			sw_cfg_def_vid(sw, p, 1);
			port_cfg_tail_tag(sw, p, 0);
			port_set_authen_mode(sw, p, 0);
#ifndef NO_ACL
/*
 * THa  2014/06/18
 * Cannot read ACL in next bootup if there are lots of traffic going through
 * the port.
 */
			if (sw->features & ACL_CORRUPT_BUG)
				port_cfg_acl(sw, p, 1);
			else
				port_cfg_acl(sw, p, 0);
#endif
		}
	} while (0);
	sw->overrides &= ~TAIL_TAGGING;
	sw->overrides &= ~PTP_TAG;
	sw->overrides &= ~TAG_REMOVE;
}  /* sw_reset */

static int sw_chk_reg(struct ksz_sw *sw, u32 reg, size_t count)
{
	size_t i;

	for (i = 0; i < count; i += SW_SIZE, reg += SW_SIZE) {
		if (!check_sw_reg_range(reg))
			return false;
	}
	return true;
}

static int sw_reg_get(struct ksz_sw *sw, u32 reg, size_t count, char *buf)
{
	size_t i;
	SW_D *addr;

	addr = (SW_D *) buf;
	if (sw_chk_reg(sw, reg, count)) {
		sw_r(sw, reg, buf, count);
		return count;
	}
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
	if (sw_chk_reg(sw, reg, count)) {
		sw_w(sw, reg, buf, count);
		return count;
	}
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
	.r24			= sw_r24,
	.r32			= sw_r32,
	.w8			= sw_w8,
	.w16			= sw_w16,
	.w24			= sw_w24,
	.w32			= sw_w32,

	.r			= sw_r,
	.w			= sw_w,

	.get			= sw_reg_get,
	.set			= sw_reg_set,

	.r_dyn_mac_hw		= sw_r_dyn_mac_hw,
	.w_dyn_mac_hw		= sw_w_dyn_mac_hw,
	.start_dyn_mac_hw	= sw_start_dyn_mac_hw,
	.g_dyn_mac_hw		= sw_g_dyn_mac_hw,
	.stop_dyn_mac_hw	= sw_stop_dyn_mac_hw,
	.r_sta_mac_hw		= sw_r_sta_mac_hw,
	.w_sta_mac_hw		= sw_w_sta_mac_hw,
	.r_vlan_hw		= sw_r_vlan_hw,
	.w_vlan_hw		= sw_w_vlan_hw,
	.r_mib_cnt_hw		= sw_r_mib_cnt_hw,
	.r_acl_hw		= sw_r_acl_hw,
	.w_acl_hw		= sw_w_acl_hw,
};

#ifdef KSZ_IBA
/**
 * sw_set_spi - use SPI for access
 * @sw:		The switch instance.
 * @iba:	The IBA instance.
 *
 * This routine uses default hardware access like SPI for register access.
 */
static void sw_set_spi(struct ksz_sw *sw, struct ksz_iba_info *iba)
{
	sw->reg = &sw_reg_ops;
#ifdef CONFIG_1588_PTP
	if (sw->features & PTP_HW) {
		struct ptp_info *ptp = &sw->ptp_hw;

		ptp->reg = &ptp_reg_ops;
	}
#endif
	iba->use_iba = 0;
}  /* sw_set_spi */

/**
 * sw_set_ops - try to use SPI for access
 * @sw:		The switch instance.
 * @iba:	The IBA instance.
 *
 * This routine tries to use IBA for register access.
 */
static void sw_set_ops(struct work_struct *work)
{
	struct delayed_work *dwork = to_delayed_work(work);
	struct ksz_sw *sw = container_of(dwork, struct ksz_sw, set_ops);
	struct ksz_iba_info *iba = &sw->info->iba;
#ifdef CONFIG_1588_PTP
	struct ptp_info *ptp = NULL;
#endif

	if (sw->reg == &sw_iba_ops)
		return;

	if (sw->HOST_PORT < sw->phy_port_cnt && !netif_carrier_ok(iba->dev)) {
		schedule_delayed_work(&sw->set_ops, 1);
		return;
	}

#ifdef CONFIG_1588_PTP
	if (sw->features & PTP_HW)
		ptp = &sw->ptp_hw;
#endif
	mutex_lock(&sw->lock);
	mutex_lock(sw->hwlock);
	mutex_lock(sw->reglock);
	if (netif_running(iba->dev)) {
#ifdef CONFIG_1588_PTP
		if (ptp)
			ptp->reg = &ptp_iba_ops;
#endif
		sw->reg = &sw_iba_ops;
		iba->cnt = 0;
		iba->use_iba = 1;
	}
dbg_msg("changed: %p\n", sw->reg);
if (sw->reg == &sw_iba_ops)
dbg_msg("iba set\n");
	if (iba->use_iba) {
		u32 id;

		sw->intr_using = 2;
		iba->use_iba |= 0x80;
		id = sw->reg->r32(sw, REG_CHIP_ID0__1);
		iba->use_iba &= ~0x80;
dbg_msg("id = %08x\n", id);
#if 1
/*
 * THa  2016/01/03
 * KSZ9563 S1 does not respond the very first time when using RGMII.
 */
		if (id == 0xdeadbeaf && (sw->features & SETUP_PHY)) {
			id = sw->reg->r32(sw, REG_CHIP_ID0__1);
dbg_msg("id = %08x\n", id);
		}
#endif
		sw->intr_using = 0;
		if (id == 0xdeadbeaf)
			sw_set_spi(sw, iba);
	}
	mutex_unlock(sw->reglock);
	mutex_unlock(sw->hwlock);
	mutex_unlock(&sw->lock);

	if (!iba->use_iba)
		return;
#if 1
/*
 * THa  2014/06/25
 * SPI cannot just read PHY interrupt status register to clear interrupts.
 *
 * THa  2015/09/17
 * The S2 chip has a strange bug that if PHY register 0x0136 is accessed last,
 * either read or write, the global port interrupt status 0x0018 and individual
 * port status register 0x001B do not indicate PHY interrupt even though the
 * actual interrupt is triggered by plugging in or out the cable.
 */
	if (!(sw->features & NEW_CAP)) {
		int port;
		u8 val = LINK_DOWN_INT | LINK_UP_INT;

		sw->ops->acquire(sw);
		for (port = 0; port < sw->phy_port_cnt; port++) {
			port_w8(sw, port, REG_PORT_PHY_INT_ENABLE, val);
		}
		sw->ops->release(sw);
	}
#endif
#ifdef TEST_IBA
	if (iba->use_iba) {
u32 id;
		sw->ops->acquire(sw);
id = sw->reg->r32(sw, REG_CHIP_ID0__1);
		sw_init(sw);
		sw->ops->release(sw);
	}
#endif
}  /* sw_set_ops */

/**
 * sw_set_ops - try to use SPI for access
 * @sw:		The switch instance.
 * @dev:	The network device.
 * @mac_addr:	The MAC address used.
 *
 * This routine setup the IBA with the network device and its MAC address if
 * the device exists.  Otherwise it uses the default access like SPI.
 */
static void sw_set_dev(struct ksz_sw *sw, struct net_device *dev, u8 *mac_addr)
{
	struct ksz_iba_info *iba = &sw->info->iba;
	int delay_tick = 2;

	if (sw->HOST_PORT < sw->phy_port_cnt)
		delay_tick = 10;
	if (!dev) {
		if (sw->reg != &sw_reg_ops) {
#ifdef CONFIG_1588_PTP
			struct ptp_info *ptp = NULL;

			if (sw->features & PTP_HW)
				ptp = &sw->ptp_hw;
#endif
			mutex_lock(&sw->lock);
			mutex_lock(sw->hwlock);
			mutex_lock(sw->reglock);
			sw_set_spi(sw, iba);
			mutex_unlock(sw->reglock);
			mutex_unlock(sw->hwlock);
			mutex_unlock(&sw->lock);
		}
	} else if (sw->features & IBA_SUPPORT)
		schedule_delayed_work(&sw->set_ops, delay_tick);
	mutex_lock(sw->hwlock);
	iba->dev = dev;
	prepare_iba(iba, iba->dst, mac_addr);
	mutex_unlock(sw->hwlock);
}  /* sw_set_dev */
#endif

/* -------------------------------------------------------------------------- */

/*
 * Micrel LinkMD routines
 */

#if 0
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
	if (link & (PORT_1000_LINK_GOOD | PORT_100_LINK_GOOD)) {
		int stat = 0;

		port_info->status[0] = CABLE_GOOD;
		port_info->length[0] = 1;
		port_info->status[1] = CABLE_GOOD;
		port_info->length[1] = 1;
		port_info->status[2] = CABLE_GOOD;
		port_info->length[2] = 1;

#if 0
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
#endif
		return;
	}

	/* Put in 10 Mbps mode. */
	port_r(sw, port, P_PHY_CTRL, &ctrl);
	data = ctrl;
	data &= ~(PORT_AUTO_NEG_ENABLE | PORT_FULL_DUPLEX |
		PORT_SPEED_1000MBIT | PORT_SPEED_100MBIT);
	port_w(sw, port, P_PHY_CTRL, data);

	port_r(sw, port, P_NEG_RESTART_CTRL, &data);
	crossover = data;

#if 0
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
#if (SW_SIZE == (1))
			port_r8(sw, port, REG_PORT_LINK_MD_RESULT, &link);
			len = data & PORT_CABLE_FAULT_COUNTER_H;
			len <<= 16;
			len |= link;
#else
			len = data & PORT_CABLE_FAULT_COUNTER;
#endif
			port_info->length[i] = len *
				CABLE_LEN_MULTIPLIER;
			if (data & PORT_CABLE_10M_SHORT)
				port_info->length[i] = 1;
			data &= PORT_CABLE_DIAG_RESULT;
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
#endif

	port_w(sw, port, P_PHY_CTRL, ctrl);
	if (ctrl & PORT_AUTO_NEG_ENABLE) {
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
}
#endif

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
		if (cnt > 1 && port == sw->HOST_PORT)
			continue;
		port_mib = &sw->port_mib[port];
		for (mib = port_mib->mib_start; mib < sw->mib_cnt; mib++)
			counter[mib] += port_mib->counter[mib];
	}
}

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
#ifdef SWITCH_10_MBIT
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

	len += sprintf(buf + len, "\npass_all:\t");
	len += sprintf(buf + len,
		"set to 1 to pass all frames for debugging\n");
	len += sprintf(buf + len, "tail_tag:\t");
	len += sprintf(buf + len,
		"disable/enable tail tagging\n");
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
	len += sprintf(buf + len, "\nmacaddr:\t");
	len += sprintf(buf + len,
		"set port MAC address\n");
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
	case PROC_GET_HOST_PORT:
		len += sprintf(buf + len, "%u\n", sw->HOST_PORT + 1);
		break;
	case PROC_GET_PORTS:
		len += sprintf(buf + len, "%u\n", sw->mib_port_cnt);
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
		len += sprintf(buf + len, "\t%08x = MRP support\n",
			MRP_SUPPORT);
		len += sprintf(buf + len, "\t%08x = IBA support\n",
			IBA_SUPPORT);
		len += sprintf(buf + len, "\t%08x = new capabilities\n",
			NEW_CAP);
		len += sprintf(buf + len, "\t%08x = AVB support\n",
			AVB_SUPPORT);
		len += sprintf(buf + len, "\t%08x = Redundancy support\n",
			REDUNDANCY_SUPPORT);
#ifdef KSZ_DLR
		len += sprintf(buf + len, "\t%08x = DLR\n",
			DLR_HW);
#endif
#ifdef KSZ_HSR
		len += sprintf(buf + len, "\t%08x = HSR\n",
			HSR_HW);
#endif
		len += sprintf(buf + len, "\t%08x = DSA support\n",
			DSA_SUPPORT);
		len += sprintf(buf + len, "\t%08x = different MAC addresses\n",
			DIFF_MAC_ADDR);
		len += sprintf(buf + len, "\t%08x = QuietWire\n",
			QW_HW);
#ifdef CONFIG_1588_PTP
		len += sprintf(buf + len, "\t%08x = 1588 PTP\n",
			PTP_HW);
#endif
		break;
	case PROC_SET_SW_OVERRIDES:
		len += sprintf(buf + len, "%08x:\n", sw->overrides);
		len += sprintf(buf + len, "\t%08x = flow control\n",
			PAUSE_FLOW_CTRL);
		len += sprintf(buf + len, "\t%08x = fast aging\n",
			FAST_AGING);
#ifdef KSZ_IBA
		len += sprintf(buf + len, "\t%08x = IBA test\n",
			IBA_TEST);
#endif
		len += sprintf(buf + len, "\t%08x = ACL intr monitor\n",
			ACL_INTR_MONITOR);
		len += sprintf(buf + len, "\t%08x = ptp tag\n",
			PTP_TAG);
		len += sprintf(buf + len, "\t%08x = tag is removed\n",
			TAG_REMOVE);
		len += sprintf(buf + len, "\t%08x = tail tagging\n",
			TAIL_TAGGING);
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
}  /* sysfs_sw_read */

static ssize_t sysfs_sw_read_hw(struct ksz_sw *sw, int proc_num, ssize_t len,
	char *buf)
{
	u8 data[8];
	u32 val;

	switch (proc_num) {
	case PROC_SET_AGING:
		len += sprintf(buf + len, "%u\n",
			sw_chk(sw, REG_SW_LUE_CTRL_1,
				SW_AGING_ENABLE));
		break;
	case PROC_SET_FAST_AGING:
		len += sprintf(buf + len, "%u\n",
			sw_chk(sw, REG_SW_LUE_CTRL_1,
				SW_FAST_AGING));
		break;
	case PROC_SET_LINK_AGING:
		len += sprintf(buf + len, "%u\n",
			sw_chk(sw, S_LINK_AGING_CTRL,
				SW_LINK_AUTO_AGING));
		break;
	case PROC_SET_MULTICAST_STORM:
		len += sprintf(buf + len, "%u\n",
			!sw_chk(sw, REG_SW_MAC_CTRL_1,
				MULTICAST_STORM_DISABLE));
		break;
	case PROC_ENABLE_VLAN:
		len += sprintf(buf + len, "%u\n",
			sw_chk(sw, REG_SW_LUE_CTRL_0,
				SW_VLAN_ENABLE));
		break;
	case PROC_SET_REPLACE_NULL_VID:
		len += sprintf(buf + len, "%u\n",
			sw_chk(sw, S_REPLACE_VID_CTRL,
				SW_REPLACE_VID));
		break;
	case PROC_SET_DROP_INVALID_VID:
		len += sprintf(buf + len, "%u\n",
			sw_chk(sw, REG_SW_LUE_CTRL_0,
				SW_DROP_INVALID_VID));
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
#ifdef SW_IPV6_MLD_SNOOP
	case PROC_SET_IPV6_MLD_SNOOP:
		len += sprintf(buf + len, "%u\n",
			sw_chk(sw, S_MIRROR_CTRL,
				SW_IPV6_MLD_SNOOP));
		break;
	case PROC_SET_IPV6_MLD_OPTION:
		len += sprintf(buf + len, "%u\n",
			sw_chk(sw, S_MIRROR_CTRL,
				SW_IPV6_MLD_OPTION));
		break;
#endif
	case PROC_SET_AGGR_BACKOFF:
		len += sprintf(buf + len, "%u\n",
			sw_chk(sw, REG_SW_MAC_CTRL_0,
				SW_AGGR_BACKOFF));
		break;
	case PROC_SET_NO_EXC_DROP:
		len += sprintf(buf + len, "%u\n",
			sw_chk(sw, REG_SW_MAC_CTRL_1,
				NO_EXC_COLLISION_DROP));
		break;
	case PROC_SET_VLAN_BOUNDARY:
		len += sprintf(buf + len, "%u\n",
			sw_chk(sw, REG_SW_QM_CTRL,
				UNICAST_VLAN_BOUNDARY));
		break;
	case PROC_SET_DOUBLE_TAG:
		len += sprintf(buf + len, "%u\n",
			sw_chk(sw, REG_SW_OPERATION,
				SW_DOUBLE_TAG));
		break;
	case PROC_SET_ISP_TAG:
		len += sprintf(buf + len, "0x%04x\n",
			sw->reg->r16(sw, REG_SW_ISP_TPID__2));
		break;
	case PROC_SET_HSR_TAG:
		len += sprintf(buf + len, "0x%04x\n",
			sw->reg->r16(sw, REG_SW_HSR_TPID__2));
		break;
	case PROC_SET_MTU:
		len += sprintf(buf + len, "%u\n",
			sw->reg->r16(sw, REG_SW_MTU__2));
		break;
	case PROC_SET_FORWARD_UNKNOWN_UNICAST:
		val = sw->reg->r32(sw, REG_SW_LUE_UNK_UCAST_CTRL__4);
		val = !!(val & SW_UNK_UNICAST_ENABLE);
		len += sprintf(buf + len, "%u\n", val);
		break;
	case PROC_SET_UNKNOWN_UNICAST_PORTS:
		val = sw->reg->r32(sw, REG_SW_LUE_UNK_UCAST_CTRL__4);
		val &= ~SW_UNK_UNICAST_ENABLE;
		len += sprintf(buf + len, "0x%x\n", val);
		break;
	case PROC_SET_FORWARD_UNKNOWN_MULTICAST:
		val = sw->reg->r32(sw, REG_SW_LUE_UNK_MCAST_CTRL__4);
		val = !!(val & SW_UNK_MULTICAST_ENABLE);
		len += sprintf(buf + len, "%u\n", val);
		break;
	case PROC_SET_UNKNOWN_MULTICAST_PORTS:
		val = sw->reg->r32(sw, REG_SW_LUE_UNK_MCAST_CTRL__4);
		val &= ~SW_UNK_MULTICAST_ENABLE;
		len += sprintf(buf + len, "0x%x\n", val);
		break;
	case PROC_SET_FORWARD_UNKNOWN_VID:
		val = sw->reg->r32(sw, REG_SW_LUE_UNK_VID_CTRL__4);
		val = !!(val & SW_UNK_VID_ENABLE);
		len += sprintf(buf + len, "%u\n", val);
		break;
	case PROC_SET_UNKNOWN_VID_PORTS:
		val = sw->reg->r32(sw, REG_SW_LUE_UNK_VID_CTRL__4);
		val &= ~SW_UNK_VID_ENABLE;
		len += sprintf(buf + len, "0x%x\n", val);
		break;
	case PROC_SET_JUMBO_PACKET:
		len += sprintf(buf + len, "%u\n",
			sw_chk(sw, REG_SW_MAC_CTRL_1,
				SW_JUMBO_PACKET));
		break;
	case PROC_SET_LEGAL_PACKET:
		len += sprintf(buf + len, "%u\n",
			!sw_chk(sw, REG_SW_MAC_CTRL_1,
				SW_LEGAL_PACKET_DISABLE));
		break;
	case PROC_SET_LENGTH_CHECK:
		len += sprintf(buf + len, "%u\n",
			sw_chk(sw, REG_SW_MAC_CTRL_0,
				SW_CHECK_LENGTH));
		break;
	case PROC_SET_BACK_PRESSURE_MODE:
		len += sprintf(buf + len, "%u\n",
			sw_chk(sw, REG_SW_MAC_CTRL_1,
				SW_BACK_PRESSURE));
		break;
	case PROC_SET_FAIR_FLOW_CTRL:
		len += sprintf(buf + len, "%u\n",
			sw_chk(sw, REG_SW_MAC_CTRL_1,
				FAIR_FLOW_CTRL));
		break;
	case PROC_SET_PASS_PAUSE:
		len += sprintf(buf + len, "%u\n",
			sw_chk(sw, REG_SW_MAC_CTRL_4,
				SW_PASS_PAUSE));
		break;
	case PROC_ENABLE_PME:
		len += sprintf(buf + len, "%u\n",
			sw_chk(sw, REG_SW_PME_CTRL,
				PME_ENABLE));
		break;
	case PROC_ENABLE_PME_POLARITY:
		len += sprintf(buf + len, "%u\n",
			sw_chk(sw, REG_SW_PME_CTRL,
				PME_POLARITY));
		break;
	case PROC_SET_NO_COLOR:
		len += sprintf(buf + len, "%u\n",
			sw_r_shift(sw, REG_SW_MRI_CTRL_8,
				SW_COLOR_M, SW_NO_COLOR_S));
		break;
	case PROC_SET_COLOR_RED:
		len += sprintf(buf + len, "%u\n",
			sw_r_shift(sw, REG_SW_MRI_CTRL_8,
				SW_COLOR_M, SW_RED_COLOR_S));
		break;
	case PROC_SET_COLOR_YELLOW:
		len += sprintf(buf + len, "%u\n",
			sw_r_shift(sw, REG_SW_MRI_CTRL_8,
				SW_COLOR_M, SW_YELLOW_COLOR_S));
		break;
	case PROC_SET_COLOR_GREEN:
		len += sprintf(buf + len, "%u\n",
			sw_r_shift(sw, REG_SW_MRI_CTRL_8,
				SW_COLOR_M, SW_GREEN_COLOR_S));
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
		if (0 == num || 10 == num || 100 == num || 1000 == num)
			port->speed = (u16) num;
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
		if (num <= PHY_RX_ONLY)
			port->flow_ctrl = (u8) num;
		break;
	case PROC_SET_SW_MIB:
		for (count = 0; count < sw->mib_port_cnt; count++) {
			struct ksz_port_mib *mib = &sw->port_mib[count];

			memset((void *) mib->counter, 0, sizeof(u64) *
				TOTAL_SWITCH_COUNTER_NUM);
		}
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
		break;
	case PROC_SET_SW_OVERRIDES:
		if ('0' != buf[0] || 'x' != buf[1])
			sscanf(buf, "%x", &num);
		sw->overrides = num;
		break;
	case PROC_DYNAMIC:
		sw_flush_dyn_mac_table(sw, sw->mib_port_cnt);
		break;
	case PROC_STATIC:
		sw_clr_sta_mac_table(sw);
		break;
	case PROC_SET_AGING:
		sw_cfg(sw, REG_SW_LUE_CTRL_1, SW_AGING_ENABLE, num);
		break;
	case PROC_SET_FAST_AGING:
		sw_cfg(sw, REG_SW_LUE_CTRL_1, SW_FAST_AGING, num);
		break;
	case PROC_SET_LINK_AGING:
		sw_cfg(sw, S_LINK_AGING_CTRL, SW_LINK_AUTO_AGING, num);
		break;
	case PROC_SET_BROADCAST_STORM:
		hw_cfg_broad_storm(sw, num);
		break;
	case PROC_SET_MULTICAST_STORM:
		sw_cfg(sw, REG_SW_MAC_CTRL_1, MULTICAST_STORM_DISABLE,
			!num);
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
		sw_cfg(sw, S_REPLACE_VID_CTRL, SW_REPLACE_VID, num);
		break;
	case PROC_SET_DROP_INVALID_VID:
		sw_cfg(sw, REG_SW_LUE_CTRL_0, SW_DROP_INVALID_VID, num);
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
#ifdef SW_IPV6_MLD_SNOOP
	case PROC_SET_IPV6_MLD_SNOOP:
		sw_cfg(sw, S_MIRROR_CTRL, SW_IPV6_MLD_SNOOP, num);
		break;
	case PROC_SET_IPV6_MLD_OPTION:
		sw_cfg(sw, S_MIRROR_CTRL, SW_IPV6_MLD_OPTION, num);
		break;
#endif
	case PROC_SET_AGGR_BACKOFF:
		sw_cfg(sw, REG_SW_MAC_CTRL_0, SW_AGGR_BACKOFF, num);
		break;
	case PROC_SET_NO_EXC_DROP:
		sw_cfg(sw, REG_SW_MAC_CTRL_1, NO_EXC_COLLISION_DROP, num);
		break;
	case PROC_SET_VLAN_BOUNDARY:
		sw_cfg(sw, REG_SW_QM_CTRL, UNICAST_VLAN_BOUNDARY, num);
		break;
	case PROC_SET_DOUBLE_TAG:
		sw_cfg(sw, REG_SW_OPERATION, SW_DOUBLE_TAG, num);
		break;
	case PROC_SET_ISP_TAG:
		sw->reg->w16(sw, REG_SW_ISP_TPID__2, (u16) num);
		break;
	case PROC_SET_HSR_TAG:
		sw->reg->w16(sw, REG_SW_HSR_TPID__2, (u16) num);
		break;
	case PROC_SET_MTU:
		if (2000 <= num && num <= 9000)
			sw->reg->w16(sw, REG_SW_MTU__2, (u16) num);
		break;
	case PROC_SET_FORWARD_UNKNOWN_UNICAST:
		sw_cfg(sw, REG_SW_LUE_UNK_UCAST_CTRL__4,
			SW_UNK_UNICAST_ENABLE >> 24, num);
		break;
	case PROC_SET_UNKNOWN_UNICAST_PORTS:
		num &= ~SW_UNK_UNICAST_ENABLE;
		val = sw->reg->r32(sw, REG_SW_LUE_UNK_UCAST_CTRL__4);
		val &= SW_UNK_UNICAST_ENABLE;
		val |= num;
		sw->reg->w32(sw, REG_SW_LUE_UNK_UCAST_CTRL__4, val);
		break;
	case PROC_SET_FORWARD_UNKNOWN_MULTICAST:
		sw_cfg(sw, REG_SW_LUE_UNK_MCAST_CTRL__4,
			SW_UNK_MULTICAST_ENABLE >> 24, num);
		break;
	case PROC_SET_UNKNOWN_MULTICAST_PORTS:
		num &= ~SW_UNK_MULTICAST_ENABLE;
		val = sw->reg->r32(sw, REG_SW_LUE_UNK_MCAST_CTRL__4);
		val &= SW_UNK_MULTICAST_ENABLE;
		val |= num;
		sw->reg->w32(sw, REG_SW_LUE_UNK_MCAST_CTRL__4, val);
		break;
	case PROC_SET_FORWARD_UNKNOWN_VID:
		sw_cfg(sw, REG_SW_LUE_UNK_VID_CTRL__4,
			SW_UNK_VID_ENABLE >> 24, num);
		break;
	case PROC_SET_UNKNOWN_VID_PORTS:
		num &= ~SW_UNK_VID_ENABLE;
		val = sw->reg->r32(sw, REG_SW_LUE_UNK_VID_CTRL__4);
		val &= SW_UNK_VID_ENABLE;
		val |= num;
		sw->reg->w32(sw, REG_SW_LUE_UNK_VID_CTRL__4, val);
		break;
	case PROC_SET_JUMBO_PACKET:
		sw_cfg(sw, REG_SW_MAC_CTRL_1, SW_JUMBO_PACKET, num);
		break;
	case PROC_SET_LEGAL_PACKET:
		sw_cfg(sw, REG_SW_MAC_CTRL_1, SW_LEGAL_PACKET_DISABLE,
			!num);
		break;
	case PROC_SET_LENGTH_CHECK:
		sw_cfg(sw, REG_SW_MAC_CTRL_0, SW_CHECK_LENGTH, num);
		break;
	case PROC_SET_BACK_PRESSURE_MODE:
		sw_cfg(sw, REG_SW_MAC_CTRL_1, SW_BACK_PRESSURE, num);
		break;
	case PROC_SET_FAIR_FLOW_CTRL:
		sw_cfg(sw, REG_SW_MAC_CTRL_1, FAIR_FLOW_CTRL, num);
		break;
	case PROC_SET_PASS_PAUSE:
		sw_cfg(sw, REG_SW_MAC_CTRL_4, SW_PASS_PAUSE, num);
		break;
	case PROC_ENABLE_PME:
		sw_cfg(sw, REG_SW_PME_CTRL, PME_ENABLE, num);
		break;
	case PROC_ENABLE_PME_POLARITY:
		sw_cfg(sw, REG_SW_PME_CTRL, PME_POLARITY, num);
		break;
	case PROC_SET_NO_COLOR:
		sw_w_shift(sw, REG_SW_MRI_CTRL_8,
			SW_COLOR_M, SW_NO_COLOR_S, num);
		break;
	case PROC_SET_COLOR_RED:
		sw_w_shift(sw, REG_SW_MRI_CTRL_8,
			SW_COLOR_M, SW_RED_COLOR_S, num);
		break;
	case PROC_SET_COLOR_YELLOW:
		sw_w_shift(sw, REG_SW_MRI_CTRL_8,
			SW_COLOR_M, SW_YELLOW_COLOR_S, num);
		break;
	case PROC_SET_COLOR_GREEN:
		sw_w_shift(sw, REG_SW_MRI_CTRL_8,
			SW_COLOR_M, SW_GREEN_COLOR_S, num);
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
	int i;
	int j;
	u32 map;

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
	case PROC_SET_LIMIT:
		len += sprintf(buf + len, "%u\n",
			((port_cfg->rate_limit >> PORT_IN_LIMIT_MODE_S) &
			PORT_IN_LIMIT_MODE_M));
		break;
	case PROC_SET_LIMIT_PORT_BASED:
		len += sprintf(buf + len, "%u\n",
			((port_cfg->rate_limit >> PORT_IN_PORT_BASED_S)
			& 1));
		break;
	case PROC_SET_LIMIT_PACKET_BASED:
		len += sprintf(buf + len, "%u\n",
			((port_cfg->rate_limit >> PORT_IN_PACKET_BASED_S)
			& 1));
		break;
	case PROC_SET_LIMIT_FLOW_CTRL:
		len += sprintf(buf + len, "%u\n",
			((port_cfg->rate_limit >> PORT_IN_FLOW_CTRL_S)
			& 1));
		break;
	case PROC_SET_LIMIT_CNT_IFG:
		len += sprintf(buf + len, "%u\n",
			((port_cfg->rate_limit >> PORT_COUNT_IFG_S)
			& 1));
		break;
	case PROC_SET_LIMIT_CNT_PRE:
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
	case PROC_SET_RX_P4_RATE:
		len += sprintf(buf + len, "%u %s\n", (int)
			port_cfg->packet_based ?
			port_cfg->rx_packet[4] : port_cfg->rx_rate[4],
			port_cfg->packet_based ? "pbs" : "bbs");
		break;
	case PROC_SET_RX_P5_RATE:
		len += sprintf(buf + len, "%u %s\n", (int)
			port_cfg->packet_based ?
			port_cfg->rx_packet[5] : port_cfg->rx_rate[5],
			port_cfg->packet_based ? "pbs" : "bbs");
		break;
	case PROC_SET_RX_P6_RATE:
		len += sprintf(buf + len, "%u %s\n", (int)
			port_cfg->packet_based ?
			port_cfg->rx_packet[6] : port_cfg->rx_rate[6],
			port_cfg->packet_based ? "pbs" : "bbs");
		break;
	case PROC_SET_RX_P7_RATE:
		len += sprintf(buf + len, "%u %s\n", (int)
			port_cfg->packet_based ?
			port_cfg->rx_packet[7] : port_cfg->rx_rate[7],
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
	case PROC_SET_COLOR_MAP:
		for (i = 0; i < DIFFSERV_ENTRIES / 16; i++) {
			len += sprintf(buf + len, "%2u=",
				i * 16);
			map = port_cfg->color_map[i];
			for (j = 0; j < 16; j++) {
				len += sprintf(buf + len, "%u ",
					map & POLICE_COLOR_MAP_M);
				map >>= POLICE_COLOR_MAP_S;
			}
			len += sprintf(buf + len, "\t%08x\n",
				port_cfg->color_map[i]);
		}
		break;
	case PROC_SET_TC_MAP:
		for (i = 0; i < PRIO_802_1P_ENTRIES / 8; i++) {
			len += sprintf(buf + len, "%u=",
				i * 8);
			map = port_cfg->tc_map[i];
			for (j = 0; j < 8; j++) {
				len += sprintf(buf + len, "%u ",
					map & PORT_TC_MAP_M);
				map >>= PORT_TC_MAP_S;
			}
			len += sprintf(buf + len, "\t%08x\n",
				port_cfg->tc_map[i]);
		}
		break;
	case PROC_SET_MMD_ID:
		len += sprintf(buf + len, "0x%x\n", port_cfg->mmd_id);
		break;
	case PROC_SET_MMD_REG:
		len += sprintf(buf + len, "0x%x\n", port_cfg->mmd_reg);
		break;
	}
	return len;
}  /* sysfs_port_read */

static ssize_t sysfs_port_read_hw(struct ksz_sw *sw, int proc_num, int port,
	ssize_t len, char *buf)
{
	u16 val;
	struct ksz_port_cfg *cfg = &sw->info->port_cfg[port];

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
	case PROC_ENABLE_VLAN_PRIO:
		len += sprintf(buf + len, "%d\n",
			port_chk_vlan_prio(sw, port));
		break;
	case PROC_ENABLE_MAC_PRIO:
		len += sprintf(buf + len, "%d\n",
			port_chk_mac_prio(sw, port));
		break;
	case PROC_ENABLE_ACL_PRIO:
		len += sprintf(buf + len, "%d\n",
			port_chk_acl_prio(sw, port));
		break;
	case PROC_SET_HIGHEST_PRIO:
		len += sprintf(buf + len, "%d\n",
			port_chk_highest_prio(sw, port));
		break;
	case PROC_SET_OR_PRIO:
		len += sprintf(buf + len, "%d\n",
			port_chk_or_prio(sw, port));
		break;
	case PROC_ENABLE_PRIO_QUEUE:
		len += sprintf(buf + len, "%d\n",
			port_chk_prio(sw, port));
		break;
	case PROC_SET_REPLACE_VID:
		len += sprintf(buf + len, "%u\n",
			port_chk32(sw, port, REG_PORT_MTI_QUEUE_CTRL_0__4,
				MTI_PVID_REPLACE));
		break;
	case PROC_SET_REPLACE_PRIO:
		len += sprintf(buf + len, "%u\n",
			port_chk_replace_prio(sw, port));
		break;
	case PROC_ENABLE_PRIO_RATE:
		len += sprintf(buf + len, "%d\n",
			sw_chk_prio_rate(sw, port));
		break;
	case PROC_SET_DROP_NON_VLAN:
		len += sprintf(buf + len, "%u\n",
			port_chk_drop_non_vlan(sw, port));
		break;
	case PROC_SET_DROP_TAG:
		len += sprintf(buf + len, "%u\n",
			port_chk_drop_tag(sw, port));
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
	case PROC_SET_DIS_NON_VID:
		len += sprintf(buf + len, "%u\n",
			port_chk_dis_non_vid(sw, port));
		break;
	case PROC_SET_INGRESS:
		len += sprintf(buf + len, "%u\n",
			port_chk_in_filter(sw, port));
		break;
	case PROC_SET_SRC_ADDR_FILTER:
		len += sprintf(buf + len, "%u\n",
			port_chk(sw, port, REG_PORT_LUE_CTRL,
				PORT_SRC_ADDR_FILTER));
		break;
	case PROC_SET_VLAN_LOOKUP_0:
		len += sprintf(buf + len, "%u\n",
			port_chk(sw, port, REG_PORT_LUE_CTRL,
				PORT_VLAN_LOOKUP_VID_0));
		break;
	case PROC_SET_MSTP:
		len += sprintf(buf + len, "%u\n",
			port_chk_mstp(sw, port));
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
	case PROC_SET_BACK_PRESSURE:
		len += sprintf(buf + len, "%u\n",
			port_chk_back_pressure(sw, port));
		break;
	case PROC_SET_FORCE_FLOW_CTRL:
		len += sprintf(buf + len, "%u\n",
			port_chk_force_flow_ctrl(sw, port));
		break;
	case PROC_SET_PASS_ALL:
		len += sprintf(buf + len, "%u\n",
			port_chk(sw, port, REG_PORT_MAC_CTRL_1,
				PORT_PASS_ALL));
		break;
	case PROC_SET_TAIL_TAG:
		len += sprintf(buf + len, "%u\n",
			port_chk_tail_tag(sw, port));
		break;
	case PROC_SET_CUSTOM_VID:
	{
		u16 data;

		port_r16(sw, port, REG_PORT_CUSTOM_VID, &data);
		len += sprintf(buf + len, "%04x\n", data);
		break;
	}
	case PROC_SET_SR_1_VID:
	{
		u16 data;

		port_r16(sw, port, REG_PORT_AVB_SR_1_VID, &data);
		len += sprintf(buf + len, "%04x\n", data);
		break;
	}
	case PROC_SET_SR_2_VID:
	{
		u16 data;

		port_r16(sw, port, REG_PORT_AVB_SR_2_VID, &data);
		len += sprintf(buf + len, "%04x\n", data);
		break;
	}
	case PROC_SET_SR_1_TYPE:
	{
		u16 data;

		port_r16(sw, port, REG_PORT_AVB_SR_1_TYPE, &data);
		len += sprintf(buf + len, "%04x\n", data);
		break;
	}
	case PROC_SET_SR_2_TYPE:
	{
		u16 data;

		port_r16(sw, port, REG_PORT_AVB_SR_2_TYPE, &data);
		len += sprintf(buf + len, "%04x\n", data);
		break;
	}
	case PROC_SET_PME_CTRL:
		len += sprintf(buf + len, "%u\n",
			port_r_s(sw, port, REG_PORT_PME_CTRL, 7, 0));
		break;
	case PROC_SET_PME_STATUS:
		len += sprintf(buf + len, "%u\n",
			port_r_s(sw, port, REG_PORT_PME_STATUS, 7, 0));
		break;
	case PROC_SET_AUTHEN_MODE:
		len += sprintf(buf + len, "%u\n",
			port_get_authen_mode(sw, port));
		break;
	case PROC_SET_ACL:
		len += sprintf(buf + len, "%u\n",
			port_chk_acl(sw, port));
		break;
	case PROC_SET_P_INDEX:
		len += sprintf(buf + len, "%u\n",
			sw->info->port_cfg[port].p_index);
		break;
	case PROC_SET_Q_INDEX:
		len += sprintf(buf + len, "%u\n",
			sw->info->port_cfg[port].q_index);
		break;
	case PROC_SET_POLICE_PACKET_TYPE:
		len += sprintf(buf + len, "%u\n",
			port_get_police_packet_type(sw, port));
		break;
	case PROC_SET_NON_DSCP_COLOR:
		len += sprintf(buf + len, "%u\n",
			port_get_non_dscp_color(sw, port));
		break;
	case PROC_ENABLE_PORT_BASED_POLICING:
		len += sprintf(buf + len, "%u\n",
			port_chk_port_based_policing(sw, port));
		break;
	case PROC_ENABLE_POLICE_DROP_ALL:
		len += sprintf(buf + len, "%u\n",
			port_chk_police_drop_all(sw, port));
		break;
	case PROC_ENABLE_COLOR_MARK:
		len += sprintf(buf + len, "%u\n",
			port_chk_color_mark(sw, port));
		break;
	case PROC_ENABLE_COLOR_REMAP:
		len += sprintf(buf + len, "%u\n",
			port_chk_color_remap(sw, port));
		break;
	case PROC_ENABLE_DROP_SRP:
		len += sprintf(buf + len, "%u\n",
			port_chk_drop_srp(sw, port));
		break;
	case PROC_ENABLE_COLOR_AWARE:
		len += sprintf(buf + len, "%u\n",
			port_chk_color_aware(sw, port));
		break;
	case PROC_ENABLE_POLICE:
		len += sprintf(buf + len, "%u\n",
			port_chk_police(sw, port));
		break;
	case PROC_SET_Q_CIR:
		port_cfg_index(sw, port,
			sw->info->port_cfg[port].p_index,
			sw->info->port_cfg[port].q_index);
		len += sprintf(buf + len, "%u\n",
			port_get_cir(sw, port));
		break;
	case PROC_SET_Q_PIR:
		port_cfg_index(sw, port,
			sw->info->port_cfg[port].p_index,
			sw->info->port_cfg[port].q_index);
		len += sprintf(buf + len, "%u\n",
			port_get_pir(sw, port));
		break;
	case PROC_SET_Q_CBS:
		port_cfg_index(sw, port,
			sw->info->port_cfg[port].p_index,
			sw->info->port_cfg[port].q_index);
		len += sprintf(buf + len, "%u\n",
			port_get_cbs(sw, port));
		break;
	case PROC_SET_Q_PBS:
		port_cfg_index(sw, port,
			sw->info->port_cfg[port].p_index,
			sw->info->port_cfg[port].q_index);
		len += sprintf(buf + len, "%u\n",
			port_get_pbs(sw, port));
		break;
	case PROC_SET_WRED_MAX_THRESHOLD:
		len += sprintf(buf + len, "%u\n",
			port_get_wred_max(sw, port));
		break;
	case PROC_SET_WRED_MIN_THRESHOLD:
		len += sprintf(buf + len, "%u\n",
			port_get_wred_min(sw, port));
		break;
	case PROC_SET_WRED_MULTIPLIER:
		len += sprintf(buf + len, "%u\n",
			port_get_wred_multiplier(sw, port));
		break;
	case PROC_GET_WRED_AVG_SIZE:
		len += sprintf(buf + len, "%u\n",
			port_get_wred_avg_size(sw, port));
		break;
	case PROC_SET_WRED_Q_MAX_THRESHOLD:
		port_cfg_index(sw, port,
			sw->info->port_cfg[port].p_index,
			sw->info->port_cfg[port].q_index);
		len += sprintf(buf + len, "%u\n",
			port_get_wred_q_max(sw, port));
		break;
	case PROC_SET_WRED_Q_MIN_THRESHOLD:
		port_cfg_index(sw, port,
			sw->info->port_cfg[port].p_index,
			sw->info->port_cfg[port].q_index);
		len += sprintf(buf + len, "%u\n",
			port_get_wred_q_min(sw, port));
		break;
	case PROC_SET_WRED_Q_MULTIPLIER:
		port_cfg_index(sw, port,
			sw->info->port_cfg[port].p_index,
			sw->info->port_cfg[port].q_index);
		len += sprintf(buf + len, "%u\n",
			port_get_wred_q_multiplier(sw, port));
		break;
	case PROC_GET_WRED_Q_AVG_SIZE:
		port_cfg_index(sw, port,
			sw->info->port_cfg[port].p_index,
			sw->info->port_cfg[port].q_index);
		len += sprintf(buf + len, "%u\n",
			port_get_wred_q_avg_size(sw, port));
		break;
	case PROC_SET_WRED_RANDOM_DROP:
		len += sprintf(buf + len, "%u\n",
			port_chk_wred_random_drop(sw, port));
		break;
	case PROC_SET_WRED_DROP_GYR:
		len += sprintf(buf + len, "%u\n",
			port_chk_wred_drop_gyr(sw, port));
		break;
	case PROC_SET_WRED_DROP_YR:
		len += sprintf(buf + len, "%u\n",
			port_chk_wred_drop_yr(sw, port));
		break;
	case PROC_SET_WRED_DROP_R:
		len += sprintf(buf + len, "%u\n",
			port_chk_wred_drop_r(sw, port));
		break;
	case PROC_SET_WRED_DROP_ALL:
		len += sprintf(buf + len, "%u\n",
			port_chk_wred_drop_all(sw, port));
		break;
	case PROC_GET_WRED_PMON:
		port_cfg_index(sw, port,
			sw->info->port_cfg[port].p_index,
			sw->info->port_cfg[port].q_index);
		len += sprintf(buf + len, "%u\n",
			port_get_wred_pmon(sw, port));
		break;
	case PROC_SET_SCHEDULE:
		len += sprintf(buf + len, "%u\n",
			port_get_schedule_mode(sw, port,
				sw->info->port_cfg[port].q_index));
		break;
	case PROC_SET_SHAPING:
		len += sprintf(buf + len, "%u\n",
			port_get_shaping(sw, port,
				sw->info->port_cfg[port].q_index));
		break;
#ifdef MTI_PREEMPT_ENABLE
	case PROC_SET_PREEMPT:
		len += sprintf(buf + len, "%u\n",
			port_chk_preempt(sw, port,
				sw->info->port_cfg[port].q_index));
		break;
#endif
	case PROC_SET_TX_RATIO:
		len += sprintf(buf + len, "%u\n",
			port_get_tx_ratio(sw, port,
				sw->info->port_cfg[port].q_index));
		break;
	case PROC_SET_CREDIT_HI_WATER_MARK:
		len += sprintf(buf + len, "%u\n",
			port_get_hi_water_mark(sw, port,
				sw->info->port_cfg[port].q_index));
		break;
	case PROC_SET_CREDIT_LO_WATER_MARK:
		len += sprintf(buf + len, "%u\n",
			port_get_lo_water_mark(sw, port,
				sw->info->port_cfg[port].q_index));
		break;
	case PROC_SET_CREDIT_INCREMENT:
		len += sprintf(buf + len, "%u\n",
			port_get_increment(sw, port,
				sw->info->port_cfg[port].q_index));
		break;
	case PROC_SET_SRP:
		len += sprintf(buf + len, "%u\n",
			port_get_srp(sw, port));
		break;
	case PROC_SET_QM_DROP:
		len += sprintf(buf + len, "%u\n",
			port_get_qm_drop(sw, port));
		break;
	case PROC_SET_QM_BURST_SIZE:
		len += sprintf(buf + len, "%u\n",
			port_get_qm_burst_size(sw, port));
		break;
	case PROC_SET_QM_RESV_SPACE:
		len += sprintf(buf + len, "%u\n",
			port_get_qm_resv_space(sw, port));
		break;
	case PROC_SET_QM_HI_WATER_MARK:
		len += sprintf(buf + len, "%u\n",
			port_get_qm_hi_water_mark(sw, port,
				sw->info->port_cfg[port].q_index));
		break;
	case PROC_SET_QM_LO_WATER_MARK:
		len += sprintf(buf + len, "%u\n",
			port_get_qm_lo_water_mark(sw, port,
				sw->info->port_cfg[port].q_index));
		break;
	case PROC_GET_QM_TX_USED:
		len += sprintf(buf + len, "%u\n",
			port_get_qm_tx_used(sw, port,
				sw->info->port_cfg[port].q_index));
		break;
	case PROC_GET_QM_TX_AVAIL:
		len += sprintf(buf + len, "%u\n",
			port_get_qm_tx_avail(sw, port,
				sw->info->port_cfg[port].q_index));
		break;
	case PROC_GET_QM_TX_CALCULATED:
		len += sprintf(buf + len, "%u\n",
			port_get_qm_tx_calculated(sw, port,
				sw->info->port_cfg[port].q_index));
		break;
	case PROC_GET_RX_FLOW_CTRL:
		len += sprintf(buf + len, "%u\n",
			port_chk(sw, port, REG_PORT_STATUS_0,
				PORT_RX_FLOW_CTRL));
		break;
	case PROC_GET_TX_FLOW_CTRL:
		len += sprintf(buf + len, "%u\n",
			port_chk(sw, port, REG_PORT_STATUS_0,
				PORT_TX_FLOW_CTRL));
		break;
	case PROC_SET_MMD_VAL:
		port_mmd_read(sw, port, cfg->mmd_id, cfg->mmd_reg, &val, 1);
		len += sprintf(buf + len, "0x%04x\n", val);
		break;
	}
	return len;
}  /* sysfs_port_read_hw */

static int sysfs_port_write(struct ksz_sw *sw, int proc_num, int port,
	int num, const char *buf)
{
	int count;
	unsigned int val;
	u16 mmd_val;
	int processed = true;
	struct ksz_port_cfg *cfg = &sw->info->port_cfg[port];

	switch (proc_num) {
	case PROC_SET_PORT_MIB:
	{
		struct ksz_port_mib *mib = &sw->port_mib[port];

		memset((void *) mib->counter, 0, sizeof(u64) *
			TOTAL_SWITCH_COUNTER_NUM);
		break;
	}
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
	case PROC_ENABLE_VLAN_PRIO:
		port_cfg_vlan_prio(sw, port, num);
		break;
	case PROC_ENABLE_MAC_PRIO:
		port_cfg_mac_prio(sw, port, num);
		break;
	case PROC_ENABLE_ACL_PRIO:
		port_cfg_acl_prio(sw, port, num);
		break;
	case PROC_SET_HIGHEST_PRIO:
		port_cfg_highest_prio(sw, port, num);
		break;
	case PROC_SET_OR_PRIO:
		port_cfg_or_prio(sw, port, num);
		break;
	case PROC_SET_PORT_BASED:
		sw_cfg_port_based(sw, port, num);
		break;
	case PROC_SET_DEF_VID:
		sw_cfg_def_vid(sw, port, num);
		break;
	case PROC_SET_MEMBER:
		sw_cfg_port_base_vlan(sw, port, (u16) num);
		break;
	case PROC_ENABLE_PRIO_QUEUE:
		if (0 <= num && num < 2)
			sw_set_multi_queue(sw, port, num);
		break;
	case PROC_SET_REPLACE_VID:
		sw_cfg_replace_null_vid(sw, port, num);
		break;
	case PROC_SET_LIMIT:
		hw_cfg_rx_limit(sw, port, (u8) num);
		break;
	case PROC_SET_LIMIT_PORT_BASED:
		hw_cfg_in_port_based(sw, port, num);
		break;
	case PROC_SET_LIMIT_PACKET_BASED:
		hw_cfg_in_packet_based(sw, port, num);
		break;
	case PROC_SET_LIMIT_FLOW_CTRL:
		hw_cfg_in_flow_ctrl(sw, port, num);
		break;
	case PROC_SET_LIMIT_CNT_IFG:
		hw_cfg_cnt_ifg(sw, port, num);
		break;
	case PROC_SET_LIMIT_CNT_PRE:
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
	case PROC_SET_RX_P4_RATE:
		hw_cfg_rx_prio_rate(sw, port, 4, num);
		break;
	case PROC_SET_RX_P5_RATE:
		hw_cfg_rx_prio_rate(sw, port, 5, num);
		break;
	case PROC_SET_RX_P6_RATE:
		hw_cfg_rx_prio_rate(sw, port, 6, num);
		break;
	case PROC_SET_RX_P7_RATE:
		hw_cfg_rx_prio_rate(sw, port, 7, num);
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
	case PROC_SET_REPLACE_PRIO:
		sw_cfg_replace_prio(sw, port, num);
		break;
	case PROC_ENABLE_PRIO_RATE:
		if (!num)
			sw_dis_prio_rate(sw, port);
		else
			sw_ena_prio_rate(sw, port);
		break;
#if 0
	case PROC_SET_LINK_MD:
		hw_get_link_md(sw, port);
		break;
#endif
	case PROC_SET_COLOR_MAP:
		count = sscanf(buf, "%d=%x", (unsigned int *) &num, &val);
		if (2 == count)
			port_cfg_color_map(sw, port, (u8) num, (u32) val);
		break;
	case PROC_SET_TC_MAP:
		count = sscanf(buf, "%d=%x", (unsigned int *) &num, &val);
		if (2 == count)
			port_cfg_tc_map(sw, port, (u8) num, (u32) val);
		break;
	case PROC_SET_DROP_NON_VLAN:
		port_cfg_drop_non_vlan(sw, port, num);
		break;
	case PROC_SET_DROP_TAG:
		port_cfg_drop_tag(sw, port, num);
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
	case PROC_SET_DIS_NON_VID:
		port_cfg_dis_non_vid(sw, port, num);
		break;
	case PROC_SET_INGRESS:
		port_cfg_in_filter(sw, port, num);
		break;
	case PROC_SET_SRC_ADDR_FILTER:
		port_cfg(sw, port, REG_PORT_LUE_CTRL, PORT_SRC_ADDR_FILTER,
			num);
		break;
	case PROC_SET_VLAN_LOOKUP_0:
		port_cfg(sw, port, REG_PORT_LUE_CTRL, PORT_VLAN_LOOKUP_VID_0,
			num);
		break;
	case PROC_SET_MSTP:
		port_cfg_mstp(sw, port, num);
		break;
	case PROC_SET_RX:
		port_cfg_rx(sw, port, num);
		break;
	case PROC_SET_TX:
		port_cfg_tx(sw, port, num);
		break;
	case PROC_SET_LEARN:
		port_cfg_dis_learn(sw, port, !num);
#if 1
		if (!num)
			sw_flush_dyn_mac_table(sw, port);
#endif
		break;
	case PROC_SET_BACK_PRESSURE:
		port_cfg_back_pressure(sw, port, num);
		break;
	case PROC_SET_FORCE_FLOW_CTRL:
		port_cfg_force_flow_ctrl(sw, port, num);
		break;
	case PROC_SET_PASS_ALL:
		port_cfg(sw, port, REG_PORT_MAC_CTRL_1, PORT_PASS_ALL, num);
		break;
	case PROC_SET_TAIL_TAG:
		port_cfg_tail_tag(sw, port, num);
		break;
	case PROC_SET_CUSTOM_VID:
		port_w16(sw, port, REG_PORT_CUSTOM_VID, (u16) num);
		break;
	case PROC_SET_SR_1_VID:
		port_w16(sw, port, REG_PORT_AVB_SR_1_VID, (u16) num);
		break;
	case PROC_SET_SR_2_VID:
		port_w16(sw, port, REG_PORT_AVB_SR_2_VID, (u16) num);
		break;
	case PROC_SET_SR_1_TYPE:
		port_w16(sw, port, REG_PORT_AVB_SR_1_TYPE, (u16) num);
		break;
	case PROC_SET_SR_2_TYPE:
		port_w16(sw, port, REG_PORT_AVB_SR_2_TYPE, (u16) num);
		break;
	case PROC_SET_PME_CTRL:
		port_w_s(sw, port, REG_PORT_PME_CTRL, 7, 0, (u8) num);
		break;
	case PROC_SET_PME_STATUS:
		port_w_s(sw, port, REG_PORT_PME_STATUS, 7, 0, (u8) num);
		break;
	case PROC_SET_AUTHEN_MODE:
		port_set_authen_mode(sw, port, num);
		break;
	case PROC_SET_ACL:
		port_cfg_acl(sw, port, num);
		break;
	case PROC_SET_P_INDEX:
		if (0 <= num && num < sw->mib_port_cnt)
			sw->info->port_cfg[port].p_index = (u8) num;
		break;
	case PROC_SET_Q_INDEX:
		if (0 <= num && num < 4)
			sw->info->port_cfg[port].q_index = (u8) num;
		break;
	case PROC_SET_POLICE_PACKET_TYPE:
		port_set_police_packet_type(sw, port, num);
		break;
	case PROC_SET_NON_DSCP_COLOR:
		port_set_non_dscp_color(sw, port, num);
		break;
	case PROC_ENABLE_PORT_BASED_POLICING:
		port_cfg_port_based_policing(sw, port, num);
		break;
	case PROC_ENABLE_POLICE_DROP_ALL:
		port_cfg_police_drop_all(sw, port, num);
		break;
	case PROC_ENABLE_COLOR_MARK:
		port_cfg_color_mark(sw, port, num);
		break;
	case PROC_ENABLE_COLOR_REMAP:
		port_cfg_color_remap(sw, port, num);
		break;
	case PROC_ENABLE_DROP_SRP:
		port_cfg_drop_srp(sw, port, num);
		break;
	case PROC_ENABLE_COLOR_AWARE:
		port_cfg_color_aware(sw, port, num);
		break;
	case PROC_ENABLE_POLICE:
		port_cfg_police(sw, port, num);
		break;
	case PROC_SET_Q_CIR:
		port_cfg_index(sw, port,
			sw->info->port_cfg[port].p_index,
			sw->info->port_cfg[port].q_index);
		port_set_cir(sw, port, num);
		break;
	case PROC_SET_Q_PIR:
		port_cfg_index(sw, port,
			sw->info->port_cfg[port].p_index,
			sw->info->port_cfg[port].q_index);
		port_set_pir(sw, port, num);
		break;
	case PROC_SET_Q_CBS:
		port_cfg_index(sw, port,
			sw->info->port_cfg[port].p_index,
			sw->info->port_cfg[port].q_index);
		port_set_cbs(sw, port, num);
		break;
	case PROC_SET_Q_PBS:
		port_cfg_index(sw, port,
			sw->info->port_cfg[port].p_index,
			sw->info->port_cfg[port].q_index);
		port_set_pbs(sw, port, num);
		break;
	case PROC_SET_WRED_MAX_THRESHOLD:
		port_set_wred_max(sw, port, num);
		break;
	case PROC_SET_WRED_MIN_THRESHOLD:
		port_set_wred_min(sw, port, num);
		break;
	case PROC_SET_WRED_MULTIPLIER:
		port_set_wred_multiplier(sw, port, num);
		break;
	case PROC_SET_WRED_Q_MAX_THRESHOLD:
		port_cfg_index(sw, port,
			sw->info->port_cfg[port].p_index,
			sw->info->port_cfg[port].q_index);
		port_set_wred_q_max(sw, port, num);
		break;
	case PROC_SET_WRED_Q_MIN_THRESHOLD:
		port_cfg_index(sw, port,
			sw->info->port_cfg[port].p_index,
			sw->info->port_cfg[port].q_index);
		port_set_wred_q_min(sw, port, num);
		break;
	case PROC_SET_WRED_Q_MULTIPLIER:
		port_cfg_index(sw, port,
			sw->info->port_cfg[port].p_index,
			sw->info->port_cfg[port].q_index);
		port_set_wred_q_multiplier(sw, port, num);
		break;
	case PROC_SET_WRED_RANDOM_DROP:
		port_cfg_wred_random_drop(sw, port, num);
		break;
	case PROC_SET_WRED_DROP_GYR:
		port_cfg_wred_drop_gyr(sw, port, num);
		break;
	case PROC_SET_WRED_DROP_YR:
		port_cfg_wred_drop_yr(sw, port, num);
		break;
	case PROC_SET_WRED_DROP_R:
		port_cfg_wred_drop_r(sw, port, num);
		break;
	case PROC_SET_WRED_DROP_ALL:
		port_cfg_wred_drop_all(sw, port, num);
		break;
	case PROC_SET_SCHEDULE:
		port_set_schedule_mode(sw, port,
			sw->info->port_cfg[port].q_index, (u8) num);
		break;
	case PROC_SET_SHAPING:
		port_set_shaping(sw, port,
			sw->info->port_cfg[port].q_index, (u8) num);
		break;
#ifdef MTI_PREEMPT_ENABLE
	case PROC_SET_PREEMPT:
		port_cfg_preempt(sw, port,
			sw->info->port_cfg[port].q_index, num);
		break;
#endif
	case PROC_SET_TX_RATIO:
		port_set_tx_ratio(sw, port,
			sw->info->port_cfg[port].q_index, (u8) num);
		break;
	case PROC_SET_CREDIT_HI_WATER_MARK:
		port_set_hi_water_mark(sw, port,
			sw->info->port_cfg[port].q_index, (u16) num);
		break;
	case PROC_SET_CREDIT_LO_WATER_MARK:
		port_set_lo_water_mark(sw, port,
			sw->info->port_cfg[port].q_index, (u16) num);
		break;
	case PROC_SET_CREDIT_INCREMENT:
		port_set_increment(sw, port,
			sw->info->port_cfg[port].q_index, (u16) num);
		break;
	case PROC_SET_SRP:
		port_set_srp(sw, port, (u8) num);
		break;
	case PROC_SET_QM_DROP:
		port_set_qm_drop(sw, port, num);
		break;
	case PROC_SET_QM_BURST_SIZE:
		port_set_qm_burst_size(sw, port, (u8) num);
		break;
	case PROC_SET_QM_RESV_SPACE:
		port_set_qm_resv_space(sw, port, (u16) num);
		break;
	case PROC_SET_QM_HI_WATER_MARK:
		port_set_qm_hi_water_mark(sw, port,
			sw->info->port_cfg[port].q_index, (u16) num);
		break;
	case PROC_SET_QM_LO_WATER_MARK:
		port_set_qm_lo_water_mark(sw, port,
			sw->info->port_cfg[port].q_index, (u16) num);
		break;
	case PROC_SET_MMD_ID:
		cfg->mmd_id = (u16) num;
		break;
	case PROC_SET_MMD_REG:
		cfg->mmd_reg = (u16) num;
		break;
	case PROC_SET_MMD_VAL:
		mmd_val = (u16) num;
		port_mmd_write(sw, port, cfg->mmd_id, cfg->mmd_reg,
			&mmd_val, 1);
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
		len += sprintf(buf + len, "0x%03x\n", entry->fid);
		break;
	case PROC_SET_STATIC_USE_FID:
		len += sprintf(buf + len, "%u\n", entry->use_fid);
		break;
	case PROC_SET_STATIC_MSTP:
		len += sprintf(buf + len, "%u\n", entry->mstp);
		break;
	case PROC_SET_STATIC_PRIO:
		len += sprintf(buf + len, "%u\n", entry->prio);
		break;
	case PROC_SET_STATIC_SRC:
		len += sprintf(buf + len, "%u\n", entry->src);
		break;
	case PROC_SET_STATIC_DST:
		len += sprintf(buf + len, "%u\n", entry->dst);
		break;
	case PROC_SET_STATIC_OVERRIDE:
		len += sprintf(buf + len, "%u\n", entry->override);
		break;
	case PROC_SET_STATIC_VALID:
		len += sprintf(buf + len, "%u\n", entry->valid);
		break;
	case PROC_SET_STATIC_PORTS:
		len += sprintf(buf + len, "0x%04x\n", entry->ports);
		break;
	case PROC_SET_STATIC_MAC_ADDR:
		len += sprintf(buf + len, "%02x:%02x:%02x:%02x:%02x:%02x\n",
			entry->addr[0], entry->addr[1],
			entry->addr[2], entry->addr[3],
			entry->addr[4], entry->addr[5]);
		break;
	case PROC_SET_STATIC_TYPE:
		len += sprintf(buf + len, "%u\n", sw->alu_type);
		break;
	case PROC_SET_STATIC_INDEX:
		len += sprintf(buf + len, "0x%03x\n", sw->alu_index);
		break;
	case PROC_SET_STATIC_INFO:
		if (sw->alu_dirty) {
			if (2 == sw->alu_type) {
				u8 mac_addr[ETH_ALEN];
				u16 fid;
				u16 mac_index;

				memcpy(mac_addr, entry->addr, ETH_ALEN);
				fid = entry->fid;
				sw_r_dyn_mac_table(sw, sw->alu_index,
					mac_addr, fid, entry, &mac_index);
				if (!sw->alu_index && mac_index)
					sw->alu_index = mac_index;
			} else if (!entry->dirty)
				sw_r_sta_mac_table(sw, sw->alu_index,
					sw->alu_type, entry);
			sw->alu_dirty = 0;
		}
		len += sprintf(buf + len,
			"%3x.%u: %02X:%02X:%02X:%02X:%02X:%02X "
			"%04x m:%u p:%u s:%u d:%u o:%u %u:%02x [%u]\n",
			sw->alu_index, sw->alu_type,
			entry->addr[0], entry->addr[1], entry->addr[2],
			entry->addr[3], entry->addr[4], entry->addr[5],
			entry->ports, entry->mstp, entry->prio,
			entry->src, entry->dst, entry->override,
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
		if (0 <= num && num <= ALU_V_FID_M) {
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
	case PROC_SET_STATIC_MSTP:
		if (0 <= num && num <= ALU_V_MSTP_M) {
			entry->mstp = num;
			entry->dirty = 1;
		}
		break;
	case PROC_SET_STATIC_PRIO:
		if (0 <= num && num <= ALU_V_PRIO_AGE_CNT_M) {
			entry->prio = num;
			entry->dirty = 1;
		}
		break;
	case PROC_SET_STATIC_SRC:
		if (num)
			entry->src = 1;
		else
			entry->src = 0;
		entry->dirty = 1;
		break;
	case PROC_SET_STATIC_DST:
		if (num)
			entry->dst = 1;
		else
			entry->dst = 0;
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
		if (2 == sw->alu_type)
			sw_w_dyn_mac_table(sw, sw->alu_index,
				entry->addr, entry->fid, entry);
		else
			sw_w_sta_mac_table(sw, sw->alu_index,
				sw->alu_type, entry);
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
	case PROC_SET_STATIC_TYPE:
		if (0 <= num && num < 3) {
			sw->alu_type = num;
			sw->alu_dirty = 1;
		}
		break;
	case PROC_SET_STATIC_INDEX:
		if (0 <= num && num < 0x1000) {
			sw->alu_index = num;
			sw->alu_dirty = 1;
		}
		break;
	case PROC_SET_STATIC_INFO:
		sw->alu_dirty = 1;
		entry->dirty = 0;
		break;
	default:
		processed = false;
		break;
	}
	return processed;
}  /* sysfs_mac_write */

static ssize_t sysfs_vlan_read(struct ksz_sw *sw, int proc_num, ssize_t len,
	char *buf)
{
	struct ksz_vlan_table *entry;

	entry = &sw->info->vlan_entry;
	switch (proc_num) {
	case PROC_SET_VLAN_VALID:
		len += sprintf(buf + len, "%u\n", entry->valid);
		break;
	case PROC_SET_VLAN_PORTS:
		len += sprintf(buf + len, "0x%04x\n", entry->ports);
		break;
	case PROC_SET_VLAN_UNTAG:
		len += sprintf(buf + len, "0x%04x\n", entry->untag);
		break;
	case PROC_SET_VLAN_FID:
		len += sprintf(buf + len, "0x%03x\n", entry->fid);
		break;
	case PROC_SET_VLAN_MSTP:
		len += sprintf(buf + len, "0x%x\n", entry->mstp);
		break;
	case PROC_SET_VLAN_PRIO:
		len += sprintf(buf + len, "0x%x\n", entry->prio);
		break;
	case PROC_SET_VLAN_OPTION:
		len += sprintf(buf + len, "%u\n", entry->option);
		break;
	case PROC_SET_VLAN_VID:
		len += sprintf(buf + len, "0x%03x\n", sw->vlan_index);
		break;
	case PROC_SET_VLAN_INFO:
		if (sw->vlan_dirty) {
			if (!entry->dirty)
				sw_r_vlan_table(sw, sw->vlan_index, entry);
			sw->vlan_dirty = 0;
		}
		len += sprintf(buf + len,
			"%3x: 0x%03x m:%x p:%x o:%u %04x %04x [%u]\n",
			sw->vlan_index, entry->fid, entry->mstp, entry->prio,
			entry->option, entry->untag, entry->ports,
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
		sw->overrides |= VLAN_SET;
		break;
	case PROC_SET_VLAN_PORTS:
		if (0 <= num && num <= sw->PORT_MASK) {
			entry->ports = num;
			entry->dirty = 1;
		}
		break;
	case PROC_SET_VLAN_UNTAG:
		if (0 <= num && num <= sw->PORT_MASK) {
			entry->untag = num;
			entry->dirty = 1;
		}
		break;
	case PROC_SET_VLAN_FID:
		if (0 <= num && num < 0x1000) {
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
	case PROC_SET_VLAN_MSTP:
		if (0 <= num && num <= VLAN_MSTP_M) {
			entry->mstp = num;
			entry->dirty = 1;
		}
		break;
	case PROC_SET_VLAN_PRIO:
		if (0 <= num && num <= VLAN_PRIO_M) {
			entry->prio = num;
			entry->dirty = 1;
		}
		break;
	case PROC_SET_VLAN_OPTION:
		if (num)
			entry->option = 1;
		else
			entry->option = 0;
		entry->dirty = 1;
		break;
	case PROC_SET_VLAN_INFO:
		sw->vlan_dirty = 1;
		entry->dirty = 0;
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
	unsigned reg;
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
	unsigned reg;
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

	memset(&mac, 0, sizeof(struct ksz_mac_table));
	memcpy(mac.addr, dest, ETH_ALEN);
	mac.ports = ports;
	mac.override = override;
	mac.use_fid = use_fid;
	mac.fid = fid;
	mac.valid = mac.ports != 0;
	if (!mac.valid && mac.override) {
		mac.override = 0;
		mac.valid = 1;
	}
	sw_w_dyn_mac_table(sw, 0, mac.addr, mac.fid, &mac);
}  /* sw_cfg_mac */

static void sw_cfg_vlan(struct ksz_sw *sw, u8 index, u16 vid, u16 fid,
	u32 ports)
{
	struct ksz_vlan_table vlan;

	if (0xffff == ports)
		ports = sw->PORT_MASK;
	memset(&vlan, 0, sizeof(struct ksz_vlan_table));
	vlan.vid = vid;
	vlan.fid = fid;
	vlan.ports = ports;
	vlan.valid = vlan.ports != 0;
	sw_w_vlan_table(sw, vlan.vid, &vlan);
}  /* sw_cfg_vlan */

static u8 sw_alloc_mac(struct ksz_sw *sw)
{
	return 1;
}  /* sw_alloc_mac */

static void sw_free_mac(struct ksz_sw *sw, u8 index)
{
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

	id = sw->reg->r32(sw, REG_CHIP_ID0__1);
	i = id;
	i >>= 8;
	i &= 0xffff;
	j = i & 0xff;
	i >>= 8;
	*id1 = (u8) i;
	*id2 = (u8) j;
	return id;
}

static void sw_cfg_tail_tag(struct ksz_sw *sw, int enable)
{
	port_cfg_tail_tag(sw, sw->HOST_PORT, enable);
}

static void sw_cfg_each_port(struct ksz_sw *sw, int p, int cpu)
{
	if (cpu)
		p = sw->HOST_PORT;
	else if (p >= sw->HOST_PORT)
		p++;
	if (!cpu)
		sw_cfg_port_base_vlan(sw, p, sw->HOST_MASK | (1 << p));
	else
		sw_cfg_port_base_vlan(sw, p, sw->PORT_MASK);
}

static int sw_port_to_phy_addr(struct ksz_sw *sw, int p)
{
	if (p >= sw->HOST_PORT)
		p++;
	if (0 <= p && p <= sw->mib_port_cnt)
		return p;
	return -1;
}

static void sw_set_port_addr(struct ksz_sw *sw, int p, u8 *addr)
{
}

static void sw_cfg_src_filter(struct ksz_sw *sw, int set)
{
	int p;

	if (!(sw->features & NEW_CAP))
		return;
	for (p = 0; p < sw->mib_port_cnt; p++) {
		if (p == sw->HOST_PORT)
			continue;
		port_cfg(sw, p, REG_PORT_LUE_CTRL, PORT_SRC_ADDR_FILTER, set);
	}
}  /* sw_cfg_src_filter */

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
#if 0
		if (!len && STATIC_MAC_TABLE_ENTRIES == i)
			break;
#endif

		entry = &sw->info->mac_table[i];
		if (!entry->valid ||
		    memcmp(data, entry->addr, ETH_ALEN))
			continue;

#if 0
		/* Block if received port is closed. */
		if (!entry->override && !(sw->rx_ports & (1 << port)))
			break;
#endif

		alu = &sw->info->alu_table[i];
		forward = alu->forward;

		/* Allow to reach host as the frame is not forwarded. */
		if (alu->forward & FWD_HOST)
			break;
		if (!len)
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
	int index;
	struct net_device *dev;
	struct ethhdr *eth = (struct ethhdr *) data;
	struct vlan_ethhdr *vlan = (struct vlan_ethhdr *) data;

	/* Get received port number. */
	if (eth->h_proto == htons(ETH_P_8021Q)) {
#if 0
		u16 vlan_tci = ntohs(vlan->h_vlan_TCI);

dbg_msg(" 1 vid: %x\n", vlan_tci);
#endif
		if (vlan->h_vlan_encapsulated_proto == htons(ETH_P_8021Q)) {
			unsigned char *ptr = (unsigned char *) vlan;
			u16 vlan_tci = ntohs(vlan->h_vlan_TCI);

			ptr += VLAN_HLEN;
dbg_msg(" 2 vid: %x\n", vlan_tci);
		}
	}
	if (eth->h_proto == htons(0x9100)) {
		u16 vlan_tci = ntohs(vlan->h_vlan_TCI);

dbg_msg(" 1 isp: %x\n", vlan_tci);
		if (vlan->h_vlan_encapsulated_proto == htons(ETH_P_8021Q)) {
			unsigned char *ptr = (unsigned char *) vlan;
			u16 vlan_tci = ntohs(vlan->h_vlan_TCI);

			ptr += VLAN_HLEN;
			vlan_tci = ntohs(vlan->h_vlan_TCI);
dbg_msg(" 2 vid: %x\n", vlan_tci);
		}
	}
	if (sw->overrides & TAIL_TAGGING) {
		(*len)--;
		*tag = data[*len - 4];
		sw->tag.timestamp = 0;
		sw->tag.ports = *tag;
		if (*tag & 0x80) {
			u32 rx_ts;

			memcpy(&rx_ts, &data[*len - 8], 4);
			rx_ts = ntohl(rx_ts);
			sw->tag.timestamp = rx_ts;
			(*len) -= 4;
		}
		*tag &= ~0x80;

		/* In case tagging is not working right. */
		if (*tag >= sw->mib_port_cnt)
			*tag = 0;

		/* Save receiving port. */
		*port = *tag;
	}
	index = *tag;
	if (index > sw->HOST_PORT)
		--index;
	dev = sw->netdev[index + sw->dev_offset];
#ifdef KSZ_DLR
	if (vlan->h_vlan_proto == htons(ETH_P_8021Q)) {
		if (vlan->h_vlan_encapsulated_proto == htons(DLR_TAG_TYPE))
			return dev;
	}
#endif
#ifdef KSZ_IBA
	if (vlan->h_vlan_proto == htons(IBA_TAG_TYPE))
		return sw->netdev[0];
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
	if (tag > sw->HOST_PORT)
		--tag;
	tag += VLAN_PORT_START;
	vlan_skb = skb_copy(skb, GFP_ATOMIC);
	if (!vlan_skb)
		return false;
	skb_reset_mac_header(vlan_skb);
	__vlan_hwaccel_put_tag(vlan_skb, htons(ETH_P_8021Q), tag);
#ifdef CONFIG_1588_PTP
	do {
		struct ptp_info *ptp = ptr;

		if (rx_tstamp && (ptp->rx_en & 1))
			rx_tstamp(ptp, vlan_skb);
	} while (0);
#endif
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

#ifdef KSZ_IBA
	if (sw->features & IBA_SUPPORT) {
		ret = iba_rcv(&sw->info->iba, skb);
		if (!ret)
			return ret;
	}
#endif
#ifdef KSZ_DLR
	if (sw->features & DLR_HW) {
		ret = dlr_rcv(&sw->info->dlr, skb, port);
		if (!ret)
			return ret;
	}
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
	len += 2;
	if (sw->overrides & PTP_TAG)
		len += 4;
	return len;
}  /* sw_get_tx_len */

static void sw_add_tail_tag(struct ksz_sw *sw, struct sk_buff *skb, int ports)
{
	struct ksz_sw_tx_tag tx_tag;
	u8 *trailer;
	u8 *tag;
	int len = 2;
	int ptp_len = 0;

	/* PTP is enabled and so requires extra 4 bytes. */
	if (sw->overrides & PTP_TAG)
		ptp_len = 4;
	len += ptp_len;
	if (sw->TAIL_TAG_LOOKUP < 0x100)
		len--;
	trailer = skb_put(skb, len);
	memset(&tx_tag, 0, sizeof(struct ksz_sw_tx_tag));
	tx_tag.ports = ports;
	if (!tx_tag.ports)
		tx_tag.ports = sw->TAIL_TAG_LOOKUP;
	else
		tx_tag.ports |= sw->TAIL_TAG_OVERRIDE;
	tx_tag.ports = htons(tx_tag.ports);
	tag = (u8 *) &tx_tag;
	memcpy(trailer, &tag[4 - ptp_len], ptp_len + 2);
	if (sw->TAIL_TAG_LOOKUP < 0x100)
		trailer[ptp_len] = trailer[ptp_len + 1];
}  /* sw_add_tail_tag */

static int sw_get_tail_tag(u8 *trailer, int *port)
{
	int len = 1;

	if (*trailer & 0x80)
		len += 4;
	*trailer &= ~0x80;
	*port = *trailer;
	return len;
}  /* sw_get_tail_tag */

static int append_tag(u16 lookup, u8 *pad, u8 *tag, int len, int ptp_len,
	int addlen)
{
	memcpy(&pad[len], &tag[4 - ptp_len], ptp_len + 2);

	/* Only one byte for the tag. */
	if (lookup < 0x100) {
		pad[len + ptp_len] = pad[len + ptp_len + 1];
		addlen--;
	}
	return addlen;
}

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
	struct ksz_sw_tx_tag tx_tag;
	u8 *tag;
	int update_dst = (sw->overrides & TAIL_TAGGING);
	int ptp_len = 0;

#ifdef CONFIG_1588_PTP
	struct ptp_info *ptp = ptr;
#endif

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
		if (vid > sw->HOST_PORT)
			vid++;
		if (!vid || vid > sw->mib_port_cnt)
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

	/* PTP is enabled and so requires extra 4 bytes. */
	if (sw->overrides & PTP_TAG)
		ptp_len = 4;

	tx_tag.ports = 0;
	if (port)
		tx_tag.ports = 1 << (port - 1);

	/* Socket buffer has no fragments. */
	if (!skb_shinfo(skb)->nr_frags) {
#ifdef NET_SKBUFF_DATA_USES_OFFSET
		len = skb_end_pointer(skb) - skb->data;
#else
		len = skb->end - skb->data;
#endif
		if (skb->len + ptp_len + 2 > len || len < 60 + ptp_len + 2) {
			len = (skb->len + ptp_len + 5) & ~3;
			if (len < 68)
				len = 68;
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

#ifdef CONFIG_KSZ_STP
		if ((sw->features & STP_SUPPORT) &&
		    skb->protocol != htons(ETH_P_IBA)) {
			int forward = sw_block_rx(sw, skb->data, 0, 0);

			/*
			 * The static MAC table was programmed to forward only
			 * to host.
			 * Need destination ports to send out.
			 */
			if (forward & FWD_HOST) {
				if (!port)
					port = sw->tx_ports & ~sw->HOST_MASK;
				if (port && (forward & FWD_HOST_OVERRIDE))
					port |= sw->TAIL_TAG_OVERRIDE;
				tx_tag.ports = port;
			}
		}
#endif
	}
	if (!tx_tag.ports)
		tx_tag.ports = sw->TAIL_TAG_LOOKUP;
	tx_tag.timestamp = 0;

#ifdef CONFIG_1588_PTP
	if (ptp)
		ptp_set_tx_info(ptp, skb->data, &tx_tag);
#endif
#if 0
tx_tag.ports |= sw->TAIL_TAG_OVERRIDE;
#endif
#if 0
if (port == sw->HOST_PORT + 1)
printk(" tag: %x\n", tx_tag.ports);
#endif

	tx_tag.ports = htons(tx_tag.ports);
	tx_tag.timestamp = htonl(tx_tag.timestamp);
	tag = (u8 *) &tx_tag;

	/* Socket buffer has no fragments. */
	if (!skb_shinfo(skb)->nr_frags) {
		len = append_tag(sw->TAIL_TAG_LOOKUP, skb->data, tag, len,
			ptp_len, ptp_len + 2);
		skb_put(skb, len);
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
		memset(&sw->tx_pad[sw->tx_start], 0, sizeof(tx_tag));
		sw->tx_start = 0;
		len = ptp_len + 2;
		if (skb->len < 60) {
			sw->tx_start = 60 - skb->len;
			len += sw->tx_start;
		}
		len = append_tag(sw->TAIL_TAG_LOOKUP, sw->tx_pad, tag,
			sw->tx_start, ptp_len, len);
		skb_append_datato_frags(sk, skb, add_frag, sw->tx_pad, len);
	}
	return skb;
}  /* sw_check_skb */

static struct sk_buff *sw_check_tx(struct ksz_sw *sw, struct net_device *dev,
	struct sk_buff *skb, struct ksz_port *priv)
{
	void *ptr = NULL;
	int (*update_msg)(u8 *data, u32 port, u32 overrides) = NULL;

#ifdef CONFIG_1588_PTP
	if (sw->features & PTP_HW) {
		struct ptp_info *ptp = &sw->ptp_hw;

		ptr = ptp;
#if 0
		update_msg = ptp->ops->update_msg;
#endif
	}
#endif

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

#ifdef CONFIG_1588_PTP
	if (sw->features & PTP_HW) {
		struct ptp_info *ptp = &sw->ptp_hw;

		if (skb_shinfo(skb)->tx_flags & SKBTX_HW_TSTAMP)
			ptp->ops->get_tx_tstamp(ptp, skb);
	}
#endif
	return skb;
}  /* sw_final_skb */

static void sw_start(struct ksz_sw *sw, u8 *addr)
{
	int need_tail_tag = false;
	int need_vlan = false;

	sw->ops->acquire(sw);
	sw_setup(sw);
#if defined(NO_DIRECT_ACCESS)
if (!sw->info->iba.use_iba) {
printk("%s\n", __func__);
	sw->ops->release(sw);
return;
}
#endif
	sw_set_addr(sw, addr);
	if (1 == sw->dev_count)
		sw_cfg_src_filter(sw, true);
#if defined(CONFIG_1588_PTP) || defined(KSZ_DLR)
	if (sw->features & (PTP_HW | DLR_HW | HSR_HW))
		need_tail_tag = true;
#endif
	if (sw->dev_count > 1)
		need_tail_tag = true;
	if (sw->features & VLAN_PORT) {
		if (sw->features & VLAN_PORT_REMOVE_TAG) {
			struct ksz_vlan_table entry;
			int p;

			memset(&entry, 0, sizeof(struct ksz_vlan_table));
			sw->ops->release(sw);
			entry.fid = VLAN_PORT_START;
			entry.untag = sw->PORT_MASK;
			entry.ports = sw->PORT_MASK;
			entry.valid = 1;
			sw_w_vlan_table(sw, VLAN_PORT_START, &entry);
			for (p = 0; p < sw->mib_port_cnt - 1; p++) {
				entry.fid = VLAN_PORT_START + p + 1;
				entry.untag = (1 << p);
				entry.ports = (1 << p) | (1 << sw->HOST_PORT);
				entry.valid = 1;
				sw_w_vlan_table(sw, VLAN_PORT_START + p + 1,
					&entry);
			}
			sw->ops->acquire(sw);
			for (p = 0; p < sw->mib_port_cnt; p++) {
				sw_cfg_def_vid(sw, p, VLAN_PORT_START);
			}
			need_vlan = true;
			sw->overrides |= TAG_REMOVE;
		}
		if (sw->features & VLAN_PORT_TAGGING)
			need_tail_tag = true;
	}
	if (sw->features & DSA_SUPPORT) {
		int p;
		int q;

		need_tail_tag = true;
		for (p = 0; p < sw->mib_port_cnt; p++) {
			q = p;
			if (q > sw->HOST_PORT)
				q--;
			sw_cfg_each_port(sw, q, p == sw->HOST_PORT);
			port_set_stp_state(sw, p, STP_STATE_SIMPLE);
		}
	}
	if (sw->features & MRP_SUPPORT)
		need_vlan = true;
	if (need_vlan)
		sw_ena_vlan(sw);
	if (need_tail_tag) {
		port_cfg_tail_tag(sw, sw->HOST_PORT, 1);
if (!(sw->overrides & TAIL_TAGGING))
dbg_msg(" ! tail tag not set\n");
	}
#ifdef KSZ9897_FPGA
#ifndef NO_SEC_TIMESTAMP
sw_cfg(sw, 0x12B, 0xC, 0);
#else
sw_cfg(sw, 0x12B, 0xC, 1);
#endif
#endif
	sw_ena_intr(sw);
	sw->ops->release(sw);
#ifdef CONFIG_1588_PTP
	if (sw->features & PTP_HW) {
		struct ptp_info *ptp = &sw->ptp_hw;

		ptp->reg->start(ptp, true);
if (!(sw->overrides & PTP_TAG))
dbg_msg(" ! ptp tag not set\n");
	}
#endif
}  /* sw_start */

static int sw_stop(struct ksz_sw *sw, int complete)
{
	int reset = false;

#ifdef CONFIG_1588_PTP
	if (sw->features & PTP_HW) {
		struct ptp_info *ptp = &sw->ptp_hw;

		reset = ptp->ops->stop(ptp);
	}
#endif
	sw->ops->acquire(sw);
	if (!reset)
		sw_reset(sw);
	reset = true;
	sw_init(sw);

	/* PHY may not work after reset. */
	if (sw->features & SETUP_PHY) {
		int port;
		u16 data;

		for (port = 0; port < sw->phy_port_cnt; port++)
			port_setup_9893(sw, port);
		port_r16(sw, port, REG_PORT_XMII_CTRL_0, &data);
dbg_msg("xmii: %04x\n", data);
		data = 0x5008;
		port_w16(sw, port, REG_PORT_XMII_CTRL_0, data);
	}

#if !defined(TEST_IBA)
	/* Clean out static MAC table when the switch shutdown. */
	if ((sw->features & STP_SUPPORT) && complete)
		sw_clr_sta_mac_table(sw);
	if (complete)
		sw_clr_sta_mac_table(sw);
#endif
	sw->ops->release(sw);
	return reset;
}  /* sw_stop */

static void sw_init_mib(struct ksz_sw *sw)
{
	int i;

	for (i = 0; i < sw->mib_port_cnt; i++) {
		sw->port_mib[i].mib_start = 0;
		if (sw->next_jiffies < jiffies)
			sw->next_jiffies = jiffies + HZ * 2;
		else
			sw->next_jiffies += MIB_READ_INTERVAL;
		sw->counter[i].time = sw->next_jiffies;
		sw->port_state[i].state = media_disconnected;
		port_init_cnt(sw, i);
	}
	for (i = sw->phy_port_cnt; i < sw->mib_port_cnt; i++)
		sw->port_state[i].state = media_connected;
	sw->port_state[sw->HOST_PORT].state = media_connected;
}  /* sw_init_mib */

static void sw_open_dev(struct ksz_sw *sw, struct net_device *dev, u8 *addr)
{
	sw_init_mib(sw);

	sw->net_ops->start(sw, addr);
#ifdef KSZ_IBA
	if (sw->need_link_up && sw->HOST_PORT >= sw->phy_port_cnt)
		sw->link_change = 0x80000000;
#endif
	sw->main_dev = dev;
}  /* sw_open_dev */

static void sw_open_port(struct ksz_sw *sw, struct net_device *dev,
	struct ksz_port *port, u8 *state)
{
	int i;
	int p;

	for (i = 0, p = port->first_port; i < port->port_cnt; i++, p++) {
		if (p >= sw->phy_port_cnt)
			break;

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
					port_set_stp_state(sw, sw->HOST_PORT,
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
#ifdef KSZ_IBA
	sw_set_dev(sw, sw->main_dev, sw->main_dev->dev_addr);
#endif
	/* Timer may already be started by the SPI device. */
	if (!sw->monitor_timer_info->max)
		ksz_start_timer(sw->monitor_timer_info,
			sw->monitor_timer_info->period);
}  /* sw_open */

static void sw_close(struct ksz_sw *sw)
{
	flush_work(&sw->set_addr);
#ifdef KSZ_IBA
	sw_set_dev(sw, NULL, sw->main_dev->dev_addr);
#endif
	ksz_stop_timer(sw->monitor_timer_info);
	cancel_delayed_work_sync(sw->link_read);
	cancel_delayed_work_sync(sw->stp_monitor);
}  /* sw_close */

static void sw_delayed_set_addr(struct work_struct *work)
{
	struct ksz_sw *sw = container_of(work, struct ksz_sw, set_addr);

	sw->ops->acquire(sw);
	sw_set_addr(sw, sw->netdev[0]->dev_addr);
	sw->ops->release(sw);
}  /* sw_delayed_set_addr */

static u8 sw_set_mac_addr(struct ksz_sw *sw, struct net_device *dev,
	u8 promiscuous, int port)
{
	if (sw->dev_count > 1 && (!sw->dev_offset || dev != sw->netdev[0])) {
		if (sw->features & DIFF_MAC_ADDR) {
			sw->features &= ~DIFF_MAC_ADDR;
			--promiscuous;
		}
		for (port = 0; port < sw->mib_port_cnt; port++) {
			if (port == sw->HOST_PORT)
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
			int dev_count = sw->dev_count + sw->dev_offset;

			for (i = 0; i < dev_count; i++) {
				if (dev == sw->netdev[i])
					continue;
				memcpy(sw->netdev[i]->dev_addr,
					dev->dev_addr, ETH_ALEN);
			}
			if (sw->features & DIFF_MAC_ADDR) {
				sw->features &= ~DIFF_MAC_ADDR;
				--promiscuous;
			}
		}
		if (dev == sw->netdev[0])
			schedule_work(&sw->set_addr);
	}
	if (dev != sw->netdev[0])
		return promiscuous;

#ifdef CONFIG_1588_PTP
	if (sw->features & PTP_HW) {
		struct ptp_info *ptp = &sw->ptp_hw;

		ptp->ops->set_identity(ptp, dev->dev_addr);
	}
#endif
#ifdef KSZ_DLR
	if (sw->features & DLR_HW)
		dlr_change_addr(&sw->info->dlr, dev->dev_addr);
#endif

#ifdef KSZ_IBA
	if (netif_running(dev)) {
		sw_set_dev(sw, dev, dev->dev_addr);

		/* A hack to accept IBA response. */
		if (!promiscuous)
			promiscuous = 2;
	}
#endif
#ifdef CAPTURE_IBA
promiscuous = 1;
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

#ifdef KSZ_IBA
static int iba = 1;
#endif

static void sw_setup_special(struct ksz_sw *sw, int *port_cnt,
	int *mib_port_cnt, int *dev_cnt)
{
	sw->dev_offset = 0;
	sw->phy_offset = 0;
	if (sw->stp) {
		sw->fast_aging = 1;
		sw->multi_dev = 1;
#ifdef CONFIG_1588_PTP
		sw->multi_dev = 5;
#endif
		sw->features |= STP_SUPPORT;
	}
	dbg_msg("%s %d %d %d\n", __func__,
		sw->stp, sw->multi_dev, sw->fast_aging);
	if (sw->fast_aging)
		sw->overrides |= FAST_AGING;
#ifdef KSZ_IBA
	if (iba)
		sw->features |= IBA_SUPPORT;
#endif

	/* Multiple network device interfaces are required. */
	if (1 == sw->multi_dev) {
		sw->dev_count = sw->mib_port_cnt - 1;
		sw->phy_offset = 1;
	} else if (2 == sw->multi_dev)
		sw->features |= VLAN_PORT | VLAN_PORT_TAGGING;
	else if (3 == sw->multi_dev) {
		sw->dev_count = sw->mib_port_cnt - 1;
		sw->dev_offset = 1;
	} else if (4 == sw->multi_dev)
		sw->features |= VLAN_PORT;
	else if (5 == sw->multi_dev) {
		sw->dev_count = sw->mib_port_cnt - 1;
		sw->dev_offset = 1;
		sw->features |= VLAN_PORT | VLAN_PORT_TAGGING;
	}

	/* Single network device has multiple ports. */
	if (1 == sw->dev_count) {
		*port_cnt = sw->mib_port_cnt - 1;
		*mib_port_cnt = sw->mib_port_cnt - 1;
		if (0 < sw->HOST_PORT && sw->HOST_PORT < sw->mib_port_cnt - 1) {
			(*port_cnt)++;
			(*mib_port_cnt)++;
		}
	}
	*dev_cnt = sw->dev_count;
	if (3 == sw->multi_dev || 5 == sw->multi_dev)
		(*dev_cnt)++;
#ifdef CONFIG_1588_PTP
	if (sw->features & VLAN_PORT) {
		struct ptp_info *ptp = &sw->ptp_hw;

		ptp->overrides |= PTP_PORT_FORWARD;
	}
#endif
}  /* sw_setup_special */

static void sw_setup_dev(struct ksz_sw *sw, struct net_device *dev,
	char *dev_name, struct ksz_port *port, int i, int port_cnt,
	int mib_port_cnt)
{
	int cnt;
	int p;
	int pi;

	/* dev_offset is ether 0 or 1. */
	p = i;
	if (p)
		p -= sw->dev_offset;
	if (p >= sw->HOST_PORT)
		p++;

	if (sw->dev_offset) {
		/*
		 * First device associated with switch has been
		 * created.
		 */
		if (i)
			snprintf(dev->name, IFNAMSIZ, "%s.10%%d", dev_name);
		else {
			port_cnt = sw->mib_port_cnt - 1;
			mib_port_cnt = sw->mib_port_cnt - 1;
			if (0 < sw->HOST_PORT &&
			    sw->HOST_PORT < sw->mib_port_cnt - 1) {
				port_cnt++;
				mib_port_cnt++;
			}
			sw->netdev[i] = dev;
		}
	}

	port->port_cnt = port_cnt;
	port->mib_port_cnt = mib_port_cnt;
	port->first_port = p;
	port->flow_ctrl = PHY_TX_ONLY;

	port->sw = sw;
	port->linked = &sw->port_info[port->first_port];

	for (cnt = 0, pi = p; cnt < port_cnt; cnt++, pi++) {
		if (pi < sw->phy_port_cnt)
			sw->port_info[pi].state = media_disconnected;
		if (pi == sw->HOST_PORT)
			continue;
		sw->netdev[i++] = dev;
	}

	INIT_WORK(&port->link_update, link_update_work);
	if (sw->features & VLAN_PORT)
		dev->features |= NETIF_F_HW_VLAN_CTAG_FILTER;
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

static void sw_proc_intr(struct ksz_sw *sw)
{
	u32 intr_mask;
	u32 status;
	u16 port_intr_mask;
	u8 port_status;
	int port;
#ifdef CONFIG_1588_PTP
	struct ptp_info *ptp = &sw->ptp_hw;
#endif
	int no_intr_status = 0;

	intr_mask = sw->intr_mask;
	status = sw->reg->r32(sw, REG_SW_INT_STATUS__4);
	if (!status)
		++no_intr_status;
	status &= sw->intr_mask;
#ifdef CONFIG_1588_PTP
	if (status & TRIG_TS_INT) {
		if (ptp->started)
			ptp->ops->proc_intr(ptp);
		else
			sw->intr_mask &= ~TRIG_TS_INT;
	}
#endif
	if (status & APB_TIMEOUT_INT) {
dbg_msg(" apb: %08x\n", sw->reg->r32(sw, REG_SW_APB_TIMEOUT_ADDR__4));
		sw->reg->w32(sw, REG_SW_APB_TIMEOUT_ADDR__4,
			APB_TIMEOUT_ACKNOWLEDGE);
		status = sw->reg->r32(sw, REG_SW_INT_STATUS__4);
		if (status & APB_TIMEOUT_INT)
			sw->intr_mask &= ~APB_TIMEOUT_INT;
	}
	if (intr_mask != sw->intr_mask)
		sw->reg->w32(sw, REG_SW_INT_MASK__4,
			~sw->intr_mask & SWITCH_INT_MASK);

	intr_mask = sw->port_intr_mask;
	status = sw->reg->r32(sw, REG_SW_PORT_INT_STATUS__4);
	if (!status)
		++no_intr_status;
#if 0
dbg_msg("port irq: %08x\n", status);
#endif
#if 0
	if (!status)
		status |= 1;
#endif
	status &= sw->port_intr_mask;
	for (port = 0; port < sw->mib_port_cnt; port++) {
		if (status & 1) {
			struct ksz_port_cfg *cfg = &sw->info->port_cfg[port];
			int stop_phy_irq = false;

			if (!(sw->features & NEW_CAP))
				stop_phy_irq = true;
			port_intr_mask = cfg->intr_mask;
			port_r(sw, port, REG_PORT_INT_STATUS, &port_status);
#if 1
			port_status &= cfg->intr_mask;
#endif
#if 0
if (2 == no_intr_status && !port_status)
port_status |= PORT_PHY_INT;
#endif
			if (port_status & PORT_PHY_INT) {
				u8 val;

				/* The status is cleared after read. */
				port_r8(sw, port, REG_PORT_PHY_INT_STATUS,
					&val);
				if (val & (LINK_DOWN_INT | LINK_UP_INT))
					sw->phy_intr |= (1 << port);
dbg_msg(" phy: %d %x\n", port, val);

/*
 * THa  2014/11/18
 * KSZ9893 IBA/SPI register reset bug.
 */
if (!val) {
	u16 data;

	port_r8(sw, port, REG_PORT_PHY_INT_ENABLE, &val);
dbg_msg("!! %x %x %x %x\n", status, port_status, cfg->intr_mask, val);
	port_r16(sw, port, REG_PORT_PHY_PHY_CTRL, &data);
dbg_msg(" p1: %x\n", data);
	if (!(data & PORT_INT_PIN_HIGH)) {
		port_w16(sw, port, REG_PORT_PHY_PHY_CTRL, 0x4300);
		port_r16(sw, port, REG_PORT_PHY_PHY_CTRL, &data);
dbg_msg(" p2: %x\n", data);
stop_phy_irq = true;
	}
}
#ifndef KSZ_IBA
				if (stop_phy_irq) {
				port_w(sw, port, REG_PORT_INT_MASK,
					(~cfg->intr_mask & PORT_INT_MASK) |
					PORT_PHY_INT);
				cfg->intr_mask &= ~PORT_PHY_INT;
				}
#endif
			}
#ifdef CONFIG_1588_PTP
			if (port_status & PORT_PTP_INT) {
				if (ptp->started)
					proc_ptp_tx_intr(ptp, port);
				else
					cfg->intr_mask &= ~PORT_PTP_INT;
			}
#endif
			if (port_status & PORT_ACL_INT) {
#if 0
				port_w(sw, port, REG_PORT_INT_STATUS,
					PORT_ACL_INT);
#else
				port_w(sw, port, REG_PORT_INT_MASK,
					(~cfg->intr_mask & PORT_INT_MASK) |
					PORT_ACL_INT);
				port_w(sw, port, REG_PORT_INT_MASK,
					~cfg->intr_mask & PORT_INT_MASK);
#endif
#ifdef KSZ_DLR
				if (sw->features & DLR_HW)
					dlr_timeout(&sw->info->dlr, port);
#endif
				if (sw->overrides & ACL_INTR_MONITOR)
					printk(KERN_INFO "  acl: %d %lx\n",
						port, jiffies);
			}
			if (port_intr_mask != cfg->intr_mask)
				port_w(sw, port, REG_PORT_INT_MASK,
					~cfg->intr_mask & PORT_INT_MASK);
		}
		status >>= 1;
	}
	if (sw->phy_intr)
		schedule_delayed_work(sw->link_read, 0);
	if (intr_mask != sw->port_intr_mask)
		sw->reg->w32(sw, REG_SW_PORT_INT_MASK__4,
			~sw->port_intr_mask & sw->PORT_MASK);
	if (2 == no_intr_status)
		printk(KERN_INFO "no intr status\n");
}  /* sw_proc_intr */
