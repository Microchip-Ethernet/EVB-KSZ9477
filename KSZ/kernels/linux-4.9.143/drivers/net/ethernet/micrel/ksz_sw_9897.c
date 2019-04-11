/**
 * Microchip gigabit switch common code
 *
 * Copyright (c) 2015-2019 Microchip Technology Inc.
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
	PROC_HSR,

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
	PROC_SET_HSR_REDBOX_ID,
	PROC_SET_HSR_NET_ID,
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
	PROC_GET_AVB,
	PROC_GET_STP,
	PROC_GET_TWO_DEV,
	PROC_SET_AUTHEN,

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
	PROC_SET_VID_2_FID,
	PROC_SET_FID_2_MSTID,

#ifdef CONFIG_KSZ_STP
	PROC_GET_STP_BR_INFO,
	PROC_SET_STP_BR_ON,
	PROC_SET_STP_BR_PRIO,
	PROC_SET_STP_BR_FWD_DELAY,
	PROC_SET_STP_BR_MAX_AGE,
	PROC_SET_STP_BR_HELLO_TIME,
	PROC_SET_STP_BR_TX_HOLD,
	PROC_SET_STP_VERSION,
#ifdef CONFIG_KSZ_MSTP
	PROC_SET_STP_BR_MAX_HOPS,
	PROC_SET_STP_MSTI,
	PROC_SET_STP_MSTI_VID,
	PROC_SET_STP_MSTP_CFG,
	PROC_SET_STP_MSTP_NAME,
#endif
#endif

#ifdef CONFIG_KSZ_MRP
#ifdef CONFIG_KSZ_MSRP
	PROC_GET_MSRP_INFO,
	PROC_SET_MSRP_ENABLED,
	PROC_SET_MSRP_SR_A,
#endif
#endif

#ifdef CONFIG_KSZ_HSR
	PROC_SET_HSR_VALID,
	PROC_SET_HSR_AGE_CNT,
	PROC_SET_HSR_PATH_ID,
	PROC_SET_HSR_SRC_MAC_ADDR,
	PROC_SET_HSR_INDEX,
	PROC_SET_HSR_INFO,
	PROC_GET_HSR_STATE,
#endif

	PROC_SET_NO_COLOR,
	PROC_SET_COLOR_RED,
	PROC_SET_COLOR_YELLOW,
	PROC_SET_COLOR_GREEN,

	PROC_SET_VLAN_FILTERING_DYNAMIC,
	PROC_SET_VLAN_FILTERING_STATIC,
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
	PROC_SET_MAC_BASED_802_1X,
	PROC_SET_SRC_ADDR_FILTER,
	PROC_SET_VLAN_LOOKUP_0,

	PROC_SET_MSTP,
	PROC_SET_RX,
	PROC_SET_TX,
	PROC_SET_LEARN,
	PROC_SET_POWER,

	PROC_ENABLE_PRIO_QUEUE,

	PROC_ENABLE_RX_PRIO_RATE,
	PROC_ENABLE_TX_PRIO_RATE,
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
	PROC_SET_ACL_RULE_INDEX,
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

	PROC_SET_QUEUE_SCHEDULING,
	PROC_SET_QUEUE_SHAPING,
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

	PROC_SET_PORT_DUPLEX,
	PROC_SET_PORT_SPEED,

	PROC_SET_MAC_OPERATIONAL,
	PROC_SET_VLAN_RESTRICTED,
	PROC_SET_VLAN_UNTAGGED,

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
	PROC_SET_STP_AUTO_ISOLATE,
#endif

#ifdef CONFIG_KSZ_MRP
	PROC_SET_PORT_MMRP_ENABLED,
	PROC_SET_PORT_MMRP_MAC,
	PROC_SET_PORT_MMRP_SVC,
	PROC_SET_PORT_MMRP_REG,
	PROC_SET_PORT_MVRP_ENABLED,
	PROC_SET_PORT_MVRP_VID,
	PROC_SET_PORT_MVRP_REG,

#ifdef CONFIG_KSZ_MSRP
	PROC_SET_PORT_ASCAPABLE,
	PROC_SET_PORT_MSRP_ENABLED,
	PROC_SET_TC_DELTA_BANDWIDTH,
	PROC_SET_TC_ADMIN_IDLE_MBPS,
	PROC_SET_TC_ADMIN_IDLE_SLOPE,
	PROC_GET_TC_OPER_IDLE_SLOPE,
	PROC_SET_TC_ALGORITHM,
	PROC_GET_SR_0_RX_PRIO,
	PROC_SET_SR_0_TX_PRIO,
	PROC_GET_SR_0_SRP_DOMAIN_BOUNDARY,
	PROC_SET_SR_0_LATENCY,
	PROC_GET_SR_1_RX_PRIO,
	PROC_SET_SR_1_TX_PRIO,
	PROC_GET_SR_1_SRP_DOMAIN_BOUNDARY,
	PROC_SET_SR_1_LATENCY,
#endif
#endif

	PROC_SET_LINK_MD,
	PROC_SET_SQI,
	PROC_SET_MAC_LOOPBACK,
	PROC_SET_PHY_LOOPBACK,
	PROC_SET_REMOTE_LOOPBACK,

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

static u16 get_phy_mask(struct ksz_sw *sw, uint n)
{
if (n > sw->mib_port_cnt + 1)
dbg_msg("  !!! %s %d\n", __func__, n);
	if (n >= sw->mib_port_cnt + 1)
		n = 0;
	return sw->port_info[n].phy_m;
}

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
	if (mac->use_fid)
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
 * This helper function waits for dynamic MAC table to be ready for access.
 */
static int wait_for_dyn_mac_table(struct ksz_sw *sw)
{
	u32 ctrl;
	int timeout = 100;

	do {
		--timeout;
		if (!timeout)
			return 1;
		ctrl = sw->reg->r32(sw, REG_SW_ALU_CTRL__4);
	} while ((ctrl & ALU_START) || ALU_SEARCH == (ctrl & ALU_ACTION));
	return 0;
}  /* wait_for_dyn_mac_table */

/**
 * wait_for_sta_mac_table - Wait for static MAC table to be ready
 * @sw:		The switch instance.
 *
 * This helper function waits for static MAC table to be ready for access.
 */
static int wait_for_sta_mac_table(struct ksz_sw *sw)
{
	u32 ctrl;
	int timeout = 100;

	do {
		--timeout;
		if (!timeout)
			return 1;
		ctrl = sw->reg->r32(sw, REG_SW_ALU_STAT_CTRL__4);
	} while (ctrl & ALU_STAT_START);
	return 0;
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
 * This helper function waits for VLAN table to be ready for access.
 */
static int wait_for_vlan_table(struct ksz_sw *sw)
{
	u32 ctrl;
	int timeout = 100;

	do {
		--timeout;
		if (!timeout)
			return 1;
		ctrl = sw->reg->r8(sw, REG_SW_VLAN_CTRL);
	} while (ctrl & VLAN_START);
	return 0;
}  /* wait_for_vlan_table */

#ifdef CONFIG_KSZ_HSR
/**
 * get_hsr_table_info - Get HSR table information
 * @hsr:	Buffer to store the HSR table entry.
 * @data:	Buffer holding HSR table information.
 *
 * This helper routine retrieves information from HSR table entry data.
 */
static void get_hsr_table_info(struct ksz_hsr_table *hsr, u32 data[])
{
	u8 *byte;
	u16 *word;

	hsr->valid = !!(data[0] & HSR_V_STATIC_VALID);
	hsr->age_cnt = (data[0] >> HSR_V_AGE_CNT_S) & HSR_V_AGE_CNT_M;
	hsr->path_id = (data[0] & HSR_V_PATH_ID_M);
	data[1] = htonl(data[1]);
	memcpy(hsr->dst_mac, &data[1], 4);
	byte = (u8 *) &data[2];
	data[2] = htonl(data[2]);
	memcpy(&hsr->dst_mac[4], &byte[0], 2);
	memcpy(&hsr->src_mac[0], &byte[2], 2);
	data[3] = htonl(data[3]);
	memcpy(&hsr->src_mac[2], &data[3], 4);
	word = (u16 *) &data[4];
	memcpy(&hsr->start_seq[1], word, 2);
	word++;
	memcpy(&hsr->start_seq[0], word, 2);
	word++;
	memcpy(&hsr->exp_seq[1], word, 2);
	word++;
	memcpy(&hsr->exp_seq[0], word, 2);
	word++;
	memcpy(&hsr->seq_cnt[1], word, 2);
	word++;
	memcpy(&hsr->seq_cnt[0], word, 2);
	word++;
}  /* get_hsr_table_info */

/**
 * set_hsr_table_info - Set HSR table information
 * @hsr:	The HSR table entry.
 * @data:	Buffer to hold HSR table information.
 *
 * This helper routine puts information to HSR table entry.
 */
static void set_hsr_table_info(struct ksz_hsr_table *hsr, u32 data[])
{
	u8 *byte;
	u16 *word;

	data[0] = (u32)(hsr->age_cnt & HSR_V_AGE_CNT_M) << HSR_V_AGE_CNT_S;
	data[0] |= hsr->path_id & HSR_V_PATH_ID_M;
	if (hsr->valid)
		data[0] |= HSR_V_STATIC_VALID;
	memcpy(&data[1], hsr->dst_mac, 4);
	data[1] = htonl(data[1]);
	byte = (u8 *) &data[2];
	memcpy(&byte[0], &hsr->dst_mac[4], 2);
	memcpy(&byte[2], &hsr->src_mac[0], 2);
	data[2] = htonl(data[2]);
	memcpy(&data[3], &hsr->src_mac[2], 4);
	data[3] = htonl(data[3]);
	word = (u16 *) &data[4];
	memcpy(word, &hsr->start_seq[1], 2);
	word++;
	memcpy(word, &hsr->start_seq[0], 2);
	word++;
	memcpy(word, &hsr->exp_seq[1], 2);
	word++;
	memcpy(word, &hsr->exp_seq[0], 2);
	word++;
	memcpy(word, &hsr->seq_cnt[1], 2);
	word++;
	memcpy(word, &hsr->seq_cnt[0], 2);
	word++;
}  /* set_hsr_table_info */

/**
 * wait_for_hsr_table - Wait for HSR table to be ready
 * @sw:		The switch instance.
 *
 * This helper function waits for HSR table to be ready for access.
 */
static int wait_for_hsr_table(struct ksz_sw *sw)
{
	u32 ctrl;
	int timeout = 100;

	do {
		--timeout;
		if (!timeout)
			return 1;
		ctrl = sw->reg->r32(sw, REG_HSR_ALU_CTRL__4);
	} while ((ctrl & HSR_START) || HSR_SEARCH == (ctrl & HSR_ACTION));
	return 0;
}  /* wait_for_hsr_table */
#endif

/* -------------------------------------------------------------------------- */

#define contain_reg(addr, len, reg)	\
	(addr <= (reg) && (reg) <= (addr + len - 1))

#ifdef CONFIG_1588_PTP
#include "ksz_ptp_9897.c"
#endif
#ifdef CONFIG_KSZ_IBA
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
	ctrl |= ALU_START;
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
 * This function reads an entry of the dynamic MAC table using default access.
 */
static int sw_r_dyn_mac_hw(struct ksz_sw *sw, u16 addr, u8 *src_addr,
	u16 src_fid, struct ksz_mac_table *mac, u16 *entry)
{
	u32 ctrl;

	ctrl = sw_s_dyn_mac_table(sw, addr, src_addr, src_fid);
	ctrl |= ALU_READ;

	/* Dynamic MAC table does not use USE_FID bit and does not clear it. */
	sw->reg->w32(sw, REG_SW_ALU_VAL_B, 0);
	sw->reg->w32(sw, REG_SW_ALU_CTRL__4, ctrl);
	do {
		ctrl = sw->reg->r32(sw, REG_SW_ALU_CTRL__4);
	} while (ctrl & ALU_START);
	sw_r_mac_table(sw, mac);

	/* Hash read. */
	if (!addr && entry)
		*entry = (sw->reg->r16(sw, REG_SW_LUE_INDEX_0__2) &
			ENTRY_INDEX_M) + 1;
	return 1;
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
	if (wait_for_dyn_mac_table(sw))
		goto r_dyn_exit;
	sw->reg->r_dyn_mac_hw(sw, addr, src_addr, src_fid, mac, entry);

r_dyn_exit:
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
 * This function writes an entry of the dynamic MAC table using default access.
 */
static int sw_w_dyn_mac_hw(struct ksz_sw *sw, u16 addr, u8 *src_addr,
	u16 src_fid, struct ksz_mac_table *mac)
{
	u32 ctrl;

	ctrl = sw_s_dyn_mac_table(sw, addr, src_addr, src_fid);
	ctrl |= ALU_WRITE;
	sw_w_mac_table(sw, mac);
	sw->reg->w32(sw, REG_SW_ALU_CTRL__4, ctrl);
	return 1;
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
	if (wait_for_dyn_mac_table(sw))
		goto w_dyn_exit;

	/* Dynamic MAC table does not use USE_FID bit. */
	mac->use_fid = 0;
	sw->reg->w_dyn_mac_hw(sw, addr, src_addr, src_fid, mac);

w_dyn_exit:
	sw->ops->release(sw);
	mutex_unlock(&sw->alulock);
	mac->dirty = 0;
}  /* sw_w_dyn_mac_table */

/**
 * sw_start_dyn_mac_hw - start dynamic MAC table search using default access
 * @sw:		The switch instance.
 *
 * This function starts dynamic MAC table search using default access.
 */
static int sw_start_dyn_mac_hw(struct ksz_sw *sw)
{
	u32 ctrl;

	ctrl = ALU_SEARCH;
	ctrl |= ALU_START;

	/* Dynamic MAC table does not use USE_FID bit and does not clear it. */
	sw->reg->w32(sw, REG_SW_ALU_VAL_B, 0);
	sw->reg->w32(sw, REG_SW_ALU_CTRL__4, ctrl);
	return 1;
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
	if (wait_for_dyn_mac_table(sw))
		goto s_dyn_exit;
	sw->reg->start_dyn_mac_hw(sw);

s_dyn_exit:
	sw->ops->release(sw);
}  /* sw_start_dyn_mac_table */

/**
 * sw_g_dyn_mac_hw - retrieve dynamic MAC table result using default access
 * @sw:		The switch instance.
 * @mac:	Buffer to store the MAC table entry.
 *
 * This function retrieves dynamic MAC table result using default access.
 */
static int sw_g_dyn_mac_hw(struct ksz_sw *sw, struct ksz_mac_table *mac)
{
	sw_r_mac_table(sw, mac);
	return 1;
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

	sw->ops->acquire(sw);
	do {
		ctrl = sw->reg->r32(sw, REG_SW_ALU_CTRL__4);
	} while (!(ctrl & ALU_VALID) && (ctrl & ALU_START));
	if (ctrl & ALU_VALID) {
		ctrl >>= ALU_VALID_CNT_S;
		ctrl &= ALU_VALID_CNT_M;
		rc = !sw->reg->g_dyn_mac_hw(sw, mac);
		if (ctrl != *addr + 1)
			*addr = ctrl - 1;
	} else
		rc = -1;
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
static ssize_t sw_d_dyn_mac_table(struct ksz_sw *sw, char *buf, ssize_t len)
{
	u16 i;
	u32 ports;
	struct ksz_mac_table mac;
	int first_break = true;

	sw_start_dyn_mac_table(sw);
	i = 0;
	do {
		if (sw_g_dyn_mac_table(sw, &i, &mac))
			break;
		ports = mac.ports;
#ifdef USE_LOG_MASK
		ports = get_log_mask_from_phy(sw, ports);
#endif
		if (len >= MAX_SYSFS_BUF_SIZE && first_break) {
			first_break = false;
			len += sprintf(buf + len, "...\n");
		}
		if (len < MAX_SYSFS_BUF_SIZE)
		len += sprintf(buf + len,
			"%4x: %02X:%02X:%02X:%02X:%02X:%02X  "
			"%04x  m:%u  t:%u  s:%u  d:%u  o:%u  %02x  [%u]\n",
			i, mac.addr[0], mac.addr[1], mac.addr[2],
			mac.addr[3], mac.addr[4], mac.addr[5],
			ports, mac.mstp, mac.prio, mac.src, mac.dst,
			mac.override, mac.fid, mac.valid);
		else {
		printk(KERN_INFO
			"%4x: %02X:%02X:%02X:%02X:%02X:%02X  "
			"%04x  m:%u  t:%u  s:%u  d:%u  o:%u  %02x  [%u]\n",
			i, mac.addr[0], mac.addr[1], mac.addr[2],
			mac.addr[3], mac.addr[4], mac.addr[5],
			ports, mac.mstp, mac.prio, mac.src, mac.dst,
			mac.override, mac.fid, mac.valid);
		yield();
		}
		i++;
	} while (1);
	sw_stop_dyn_mac_table(sw, i);
	return len;
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
 * This function reads from static MAC table using default access.
 */
static int sw_r_sta_mac_hw(struct ksz_sw *sw, u32 ctrl[], int num,
	struct ksz_mac_table *mac)
{
	u32 status;
	int cnt = 0;

	do {
		sw->reg->w32(sw, REG_SW_ALU_STAT_CTRL__4, *ctrl);
		do {
			status = sw->reg->r32(sw, REG_SW_ALU_STAT_CTRL__4);
		} while (status & ALU_STAT_START);
		sw_r_mac_table(sw, mac);
		++cnt;
		++ctrl;
		++mac;
	} while (cnt < num);
	return 1;
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
	if (wait_for_sta_mac_table(sw))
		goto r_sta_exit;
	ctrl = get_mac_table_ctrl(addr, mcast);
	ctrl |= ALU_STAT_READ;
	sw->reg->r_sta_mac_hw(sw, &ctrl, 1, mac);

r_sta_exit:
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
 * This routine reads several entries of the static MAC table of the switch.
 */
static void sw_r_m_sta_mac_table(struct ksz_sw *sw, u16 addr[], int mcast,
	int num, struct ksz_mac_table *mac)
{
	u32 ctrl[MAX_IBA_MAC_ENTRIES];
	u16 max_addr;
	int i;
	int j;
	int rc;
	int cnt = MAX_IBA_MAC_ENTRIES;

	if (mcast)
		max_addr = RESERVED_MCAST_TABLE_ENTRIES;
	else
		max_addr = STATIC_MAC_TABLE_ENTRIES;
	memset(mac, 0, sizeof(struct ksz_mac_table) * num);
	mutex_lock(&sw->alulock);
	sw->ops->acquire(sw);
	if (wait_for_sta_mac_table(sw))
		goto r_m_sta_exit;
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
		}
		rc = sw->reg->r_sta_mac_hw(sw, ctrl, cnt, mac);
		if (!rc)
			break;
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

r_m_sta_exit:
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
 * This function writes to static MAC table using default access.
 */
static int sw_w_sta_mac_hw(struct ksz_sw *sw, u32 ctrl[], int num,
	struct ksz_mac_table *mac)
{
	u32 status;
	int cnt;

	for (cnt = 0; cnt < num; cnt++, ctrl++, mac++) {
		sw_w_mac_table(sw, mac);
		sw->reg->w32(sw, REG_SW_ALU_STAT_CTRL__4, *ctrl);
		do {
			status = sw->reg->r32(sw, REG_SW_ALU_STAT_CTRL__4);
		} while (status & ALU_STAT_START);
	}
	return 1;
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
	if (wait_for_sta_mac_table(sw))
		goto w_sta_exit;
	ctrl = get_mac_table_ctrl(addr, mcast);
	sw->reg->w_sta_mac_hw(sw, &ctrl, 1, mac);

w_sta_exit:
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
	int rc;
	int cnt = MAX_IBA_MAC_ENTRIES;

	mutex_lock(&sw->alulock);
	sw->ops->acquire(sw);
	if (wait_for_sta_mac_table(sw))
		goto w_m_sta_exit;
	for (i = 0; i < num; i += MAX_IBA_MAC_ENTRIES) {
		if (cnt > num - i)
			cnt = num - i;
		for (j = 0; j < cnt; j++) {
			ctrl[j] = get_mac_table_ctrl(addr[i + j], mcast);
		}
		rc = sw->reg->w_sta_mac_hw(sw, ctrl, cnt, mac);
		if (!rc)
			break;
		mac += MAX_IBA_MAC_ENTRIES;
	}

w_m_sta_exit:
	sw->ops->release(sw);
	mutex_unlock(&sw->alulock);
}  /* sw_w_m_sta_mac_table */

static int get_mcast_reserved_addr(u8 group)
{
	int i;

	for (i = 0; i < RESERVED_MCAST_TABLE_ENTRIES; i++)
		if (group == mcast_reserved_map[i])
			return i;
	return -1;
}  /* get_mcast_reserved_addr */

/**
 * sw_d_sta_mac_table - dump static MAC table
 * @sw:		The switch instance.
 *
 * This routine dumps static MAC table contents.
 */
static ssize_t sw_d_sta_mac_table(struct ksz_sw *sw, char *sbuf, ssize_t slen)
{
	int i;
	int j;
	int seen;
	int len;
	char buf[120];
	u16 addr[8];
	u16 ports;
	struct ksz_mac_table *mac;
	struct ksz_mac_table table[8];
	int first_static = true;

	for (j = 0; j < 8; j++)
		addr[j] = get_mcast_reserved_addr(j);
	sw_r_m_sta_mac_table(sw, addr, 1, 8, table);
	for (j = 0; j < 8; j++) {
		mac = &table[j];
		if (!mac->valid)
			continue;
		ports = mac->ports;
#ifdef USE_LOG_MASK
		ports = get_log_mask_from_phy(sw, ports);
#endif
		len = 0;
		len += sprintf(buf + len,
			"%2x: %02X:%02X:%02X:%02X:%02X:%02X  "
			"%04x  m:%u  p:%u  s:%u  d:%u  o:%u  %u:%02x  <",
			j,
			mac->addr[0], mac->addr[1], mac->addr[2],
			mac->addr[3], mac->addr[4], mac->addr[5],
			ports, mac->mstp, mac->prio,
			mac->src, mac->dst,
			mac->override, mac->use_fid, mac->fid);

		seen = 0;
		for (i = 0; i < RESERVED_MCAST_TABLE_ENTRIES; i++) {
			if (j == mcast_reserved_map[i]) {
				if (!seen) {
					if (i != mac->addr[5])
						len += sprintf(buf + len, " ");
					len += sprintf(buf + len,
						"%02X", i);
					seen = i + 1;
				}
			} else if (seen) {
				if (i != seen)
					len += sprintf(buf + len,
						"..%02X", i - 1);
				seen = 0;
			}
		}
		if (seen && i != seen)
			len += sprintf(buf + len, "..%02X", i - 1);
		len += sprintf(buf + len, ">");
		slen += sprintf(sbuf + slen, "%s\n", buf);
	}
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
			ports = mac->ports;
#ifdef USE_LOG_MASK
			ports = get_log_mask_from_phy(sw, ports);
#endif
			if (first_static) {
				first_static = false;
				slen += sprintf(sbuf + slen, "\n");
			}
			slen += sprintf(sbuf + slen,
				"%2x: %02X:%02X:%02X:%02X:%02X:%02X  "
				"%04x  m:%u  p:%u  s:%u  d:%u  o:%u  %u:%02x\n",
				i + j,
				mac->addr[0], mac->addr[1], mac->addr[2],
				mac->addr[3], mac->addr[4], mac->addr[5],
				ports, mac->mstp, mac->prio,
				mac->src, mac->dst,
				mac->override, mac->use_fid, mac->fid);
		}
		i += MAX_IBA_MAC_ENTRIES;
	} while (i < STATIC_MAC_TABLE_ENTRIES);
	return slen;
}  /* sw_d_sta_mac_table */

static ssize_t sw_d_mac_table(struct ksz_sw *sw, char *buf, ssize_t len)
{
	struct ksz_mac_table *mac;
	struct ksz_alu_table *alu;
	u16 ports;
	int i;
	int first_static = true;
	int first_break = true;

	i = STATIC_MAC_TABLE_ENTRIES;
	do {
		alu = &sw->info->alu_table[i];
		if (alu->valid) {
			if (len >= MAX_SYSFS_BUF_SIZE && first_break) {
				first_break = false;
				len += sprintf(buf + len, "...\n");
			}
			if (first_static) {
				first_static = false;
				if (len < MAX_SYSFS_BUF_SIZE)
					len += sprintf(buf + len, "\n");
				else
					printk(KERN_INFO "\n");
			}
			mac = &sw->info->mac_table[i];
			ports = mac->ports;
#ifdef USE_LOG_MASK
			ports = get_log_mask_from_phy(sw, ports);
#endif
			if (len < MAX_SYSFS_BUF_SIZE)
			len += sprintf(buf + len,
				"%2x: %02X:%02X:%02X:%02X:%02X:%02X  "
				"%04x  m:%u  p:%u  s:%u  d:%u  o:%u  %u:%02x  "
				"%02x:%02x\n",
				i,
				mac->addr[0], mac->addr[1], mac->addr[2],
				mac->addr[3], mac->addr[4], mac->addr[5],
				ports, mac->mstp, mac->prio,
				mac->src, mac->dst,
				mac->override, mac->use_fid, mac->fid,
				alu->forward, alu->owner);
			else
			printk(KERN_INFO
				"%2x: %02X:%02X:%02X:%02X:%02X:%02X  "
				"%04x  m:%u  p:%u  s:%u  d:%u  o:%u  %u:%02x  "
				"%02x:%02x\n",
				i,
				mac->addr[0], mac->addr[1], mac->addr[2],
				mac->addr[3], mac->addr[4], mac->addr[5],
				ports, mac->mstp, mac->prio,
				mac->src, mac->dst,
				mac->override, mac->use_fid, mac->fid,
				alu->forward, alu->owner);
		}
		i++;
		if (SWITCH_MAC_TABLE_ENTRIES == i)
			first_static = true;
	} while (i < MULTI_MAC_TABLE_ENTRIES);
	return len;
}  /* sw_d_mac_table */

/* -------------------------------------------------------------------------- */

/**
 * sw_r_vlan_hw - read from VLAN table using default access
 * @sw:		The switch instance.
 * @data:	Buffer to hold the VLAN data.
 * @num:	Number of entries to read.
 *
 * This function reads from VLAN table using default access.
 */
static int sw_r_vlan_hw(struct ksz_sw *sw, u32 data[], int num)
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
	return 1;
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
	if (wait_for_vlan_table(sw))
		goto r_vlan_exit;
	data[READ_VLAN_ENTRY_SIZE] = addr;
	sw->reg->r_vlan_hw(sw, data, 1);
	get_vlan_table_info(vlan, data);

r_vlan_exit:
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
	int rc;
	int cnt = MAX_IBA_VLAN_ENTRIES;

	memset(vlan, 0, sizeof(struct ksz_vlan_table) * num);
	mutex_lock(&sw->vlanlock);
	sw->ops->acquire(sw);
	if (wait_for_vlan_table(sw))
		goto r_m_vlan_exit;
	for (i = 0; i < num; i += MAX_IBA_VLAN_ENTRIES,
	     addr += MAX_IBA_VLAN_ENTRIES) {
		if (addr >= 4096)
			break;
		if (cnt > 4096 - addr)
			cnt = 4096 - addr;
		if (cnt > num - i)
			cnt = num - i;
		data[READ_VLAN_ENTRY_SIZE] = addr;
		rc = sw->reg->r_vlan_hw(sw, data, cnt);
		if (!rc)
			break;
		for (j = 0; j < cnt; j++) {
			get_vlan_table_info(vlan, &data[j *
				READ_VLAN_ENTRY_SIZE]);
			vlan->vid = addr + j;
			vlan++;
		}
	}

r_m_vlan_exit:
	sw->ops->release(sw);
	mutex_unlock(&sw->vlanlock);
}  /* sw_r_m_vlan_table */

/**
 * sw_w_vlan_hw - write to VLAN table using default access
 * @sw:		The switch instance.
 * @data:	VLAN data to write.
 * @num:	Number of entries to write.
 *
 * This function writes to VLAN table using default access.
 */
static int sw_w_vlan_hw(struct ksz_sw *sw, u32 data[], int num)
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
	return 1;
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
	int bit;
	int index;

	mutex_lock(&sw->vlanlock);
	sw->ops->acquire(sw);
	if (wait_for_vlan_table(sw))
		goto w_vlan_exit;
	set_vlan_table_info(vlan, data);
	data[3] = addr;
	sw->reg->w_vlan_hw(sw, data, 1);
	index = addr / VID_IN_DATA;
	bit = addr % VID_IN_DATA;
	if (vlan->valid) {
		uint m;
		uint n;
		uint p;
		struct ksz_port_cfg *cfg;

		for (n = 1; n <= sw->mib_port_cnt; n++) {
			p = get_phy_port(sw, n);
			cfg = get_port_cfg(sw, p);
			m = BIT(p);
			if (vlan->untag & m)
				cfg->untagged[index] |= (1 << bit);
			else
				cfg->untagged[index] &= ~(1 << bit);
		}
		sw->info->vid[index] |= (1 << bit);
	} else {
		sw->info->vid[index] &= ~(1 << bit);
	}

w_vlan_exit:
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
static ssize_t sw_d_vlan_table(struct ksz_sw *sw, char *buf, ssize_t len)
{
	u16 i;
	int j;
	u16 ports;
	u16 untag;
	struct ksz_vlan_table *vlan;
	struct ksz_vlan_table table[8];
	int first_break = true;

	i = 0;
	do {
		sw_r_m_vlan_table(sw, i, MAX_IBA_VLAN_ENTRIES, table);
		for (j = 0; j < MAX_IBA_VLAN_ENTRIES; j++) {
			vlan = &table[j];
			if (!vlan->valid)
				continue;
			ports = vlan->ports;
			untag = vlan->untag;
#ifdef USE_LOG_MASK
			ports = get_log_mask_from_phy(sw, ports);
			untag = get_log_mask_from_phy(sw, untag);
#endif
			if (len >= MAX_SYSFS_BUF_SIZE && first_break) {
				first_break = false;
				len += sprintf(buf + len, "...\n");
			}
			if (len < MAX_SYSFS_BUF_SIZE)
			len += sprintf(buf + len,
				"%3x: 0x%03x  m:%x  p:%x  o:%u  %04x  %04x\n",
				vlan->vid,
				vlan->fid, vlan->mstp, vlan->prio,
				vlan->option, untag, ports);
			else
			printk(KERN_INFO
				"%3x: 0x%03x  m:%x  p:%x  o:%u  %04x  %04x\n",
				vlan->vid,
				vlan->fid, vlan->mstp, vlan->prio,
				vlan->option, untag, ports);
		}
		if (len >= MAX_SYSFS_BUF_SIZE)
		yield();
		i += MAX_IBA_VLAN_ENTRIES;
	} while (i < VLAN_TABLE_ENTRIES);
	return len;
}  /* sw_d_vlan_table */

/* -------------------------------------------------------------------------- */

#ifdef CONFIG_KSZ_HSR
/**
 * sw_s_hsr_table - prepare HSR table for access
 * @sw:		The switch instance.
 * @addr:	The address of the table entry.
 * @src_addr:	The source address.
 * @path_id:	The path ID.
 *
 * This helper function prepares HSR table for access.
 */
static u32 sw_s_hsr_table(struct ksz_sw *sw, u16 addr, u8 *src_addr,
	u8 path_id)
{
	u32 ctrl;
	u32 data;
	u16 *word;

	ctrl = 0;
	if (addr) {
		data = (addr - 1) & HSR_DIRECT_INDEX_M;
		sw->reg->w32(sw, REG_HSR_ALU_INDEX_2, data);
		ctrl |= HSR_DIRECT;
	} else {
		data = 0;
		sw->reg->w32(sw, REG_HSR_ALU_INDEX_0, data);
		word = (u16 *) &data;
		word++;
		memcpy(word, &src_addr[0], 2);
		data = htonl(data);
		sw->reg->w32(sw, REG_HSR_ALU_INDEX_1, data);
		memcpy(&data, &src_addr[2], 4);
		data = htonl(data);
		sw->reg->w32(sw, REG_HSR_ALU_INDEX_2, data);
		data = path_id & HSR_PATH_INDEX_M;
		sw->reg->w32(sw, REG_HSR_ALU_INDEX_3, data);
	}
	ctrl |= HSR_START;
	return ctrl;
}  /* sw_s_hsr_table */

static void sw_get_hsr_table(struct ksz_sw *sw, struct ksz_hsr_table *hsr)
{
	int i;
	u32 data[7];

	sw_r(sw, REG_HSR_ALU_VAL_A, data, 7 * 4);
	for (i = 0; i < 7; i++)
		data[i] = be32_to_cpu(data[i]);
	get_hsr_table_info(hsr, data);
}  /* sw_get_hsr_table */

/**
 * sw_r_hsr_hw - read from HSR table using default access
 * @sw:		The switch instance.
 * @addr:	The address of the table entry.
 * @hsr:	Buffer to store the HSR table entry.
 *
 * This function reads an entry of the HSR table using default access.
 */
static int sw_r_hsr_hw(struct ksz_sw *sw, u16 addr,
	struct ksz_hsr_table *hsr)
{
	u32 ctrl;

	ctrl = sw_s_hsr_table(sw, addr, hsr->src_mac, hsr->path_id);
	ctrl |= HSR_READ;
	sw->reg->w32(sw, REG_HSR_ALU_CTRL__4, ctrl);
	do {
		ctrl = sw->reg->r32(sw, REG_HSR_ALU_CTRL__4);
	} while (ctrl & HSR_START);
	sw_get_hsr_table(sw, hsr);
	return 1;
}  /* sw_r_hsr_hw */

/**
 * sw_r_hsr_table - read from HSR table
 * @sw:		The switch instance.
 * @addr:	The address of the table entry.
 * @hsr:	Buffer to store the HSR table entry.
 *
 * This routine reads an entry of the HSR table of the switch.
 * HSR table is locked to prevent corruption of read data.
 */
static void sw_r_hsr_table(struct ksz_sw *sw, u16 addr,
	struct ksz_hsr_table *hsr)
{
	mutex_lock(&sw->hsrlock);
	sw->ops->acquire(sw);
	if (wait_for_hsr_table(sw))
		goto r_hsr_exit;
	sw->reg->r_hsr_hw(sw, addr, hsr);

r_hsr_exit:
	sw->ops->release(sw);
	mutex_unlock(&sw->hsrlock);
	hsr->dirty = 0;
}  /* sw_r_hsr_table */

/**
 * sw_w_hsr_hw - write to HSR table using default access
 * @sw:		The switch instance.
 * @addr:	The address of the table entry.
 * @hsr:	The HSR table entry.
 *
 * This function writes an entry of the HSR table using default access.
 */
static int sw_w_hsr_hw(struct ksz_sw *sw, u16 addr,
	struct ksz_hsr_table *hsr)
{
	u32 ctrl;
	u32 data[7];
	int i;

	ctrl = sw_s_hsr_table(sw, addr, hsr->src_mac, hsr->path_id);
	ctrl |= HSR_WRITE;
	set_hsr_table_info(hsr, data);
	for (i = 0; i < 7; i++)
		data[i] = cpu_to_be32(data[i]);
	sw_w(sw, REG_HSR_ALU_VAL_A, data, 7 * 4);
	sw->reg->w32(sw, REG_HSR_ALU_CTRL__4, ctrl);
	return 1;
}  /* sw_w_hsr_hw */

/**
 * sw_w_hsr_table - write to HSR table
 * @sw:		The switch instance.
 * @addr:	The address of the table entry.
 * @hsr:	The HSR table entry.
 *
 * This routine writes an entry of the HSR table of the switch.
 * HSR table is locked to prevent corruption of read data.
 */
static void sw_w_hsr_table(struct ksz_sw *sw, u16 addr,
	struct ksz_hsr_table *hsr)
{
	mutex_lock(&sw->hsrlock);
	sw->ops->acquire(sw);
	if (wait_for_hsr_table(sw))
		goto w_hsr_exit;
	sw->reg->w_hsr_hw(sw, addr, hsr);

w_hsr_exit:
	sw->ops->release(sw);
	mutex_unlock(&sw->hsrlock);
	hsr->dirty = 0;
}  /* sw_w_hsr_table */

/**
 * sw_start_hsr_hw - start HSR table search using default access
 * @sw:		The switch instance.
 *
 * This function starts HSR table search using default access.
 */
static int sw_start_hsr_hw(struct ksz_sw *sw)
{
	u32 ctrl;

	ctrl = HSR_SEARCH;
	ctrl |= HSR_START;
	sw->reg->w32(sw, REG_HSR_ALU_CTRL__4, ctrl);
	return 1;
}  /* sw_start_hsr_hw */

/**
 * sw_start_hsr_table - start HSR table search
 * @sw:		The switch instance.
 *
 * This routine starts HSR table search.
 * HSR table is locked to prevent corruption of read data.
 */
static void sw_start_hsr_table(struct ksz_sw *sw)
{
	mutex_lock(&sw->hsrlock);
	sw->ops->acquire(sw);
	if (wait_for_hsr_table(sw))
		goto s_hsr_exit;
	sw->reg->start_hsr_hw(sw);

s_hsr_exit:
	sw->ops->release(sw);
}  /* sw_start_hsr_table */

/**
 * sw_g_hsr_hw - retrieve HSR table result using default access
 * @sw:		The switch instance.
 * @hsr:	Buffer to store the HSR table entry.
 *
 * This function retrieves HSR table result using default access.
 */
static int sw_g_hsr_hw(struct ksz_sw *sw, struct ksz_hsr_table *hsr)
{
	sw_get_hsr_table(sw, hsr);
	return 1;
}  /* sw_g_hsr_hw */

/**
 * sw_g_hsr_table - retrieve HSR table result
 * @sw:		The switch instance.
 * @addr:	The address of the table entry.
 * @hsr:	Buffer to store the HSR table entry.
 *
 * This function retrieves an entry of the HSR table search result.
 *
 * Return 0 if the entry is successfully read; otherwise -1.
 */
static int sw_g_hsr_table(struct ksz_sw *sw, u16 *addr,
	struct ksz_hsr_table *hsr)
{
	u32 ctrl;
	int rc = 0;

	sw->ops->acquire(sw);
	do {
		ctrl = sw->reg->r32(sw, REG_HSR_ALU_CTRL__4);
	} while (!(ctrl & HSR_VALID) && (ctrl & HSR_START));
	if (ctrl & HSR_VALID) {
		ctrl >>= HSR_VALID_CNT_S;
		ctrl &= HSR_VALID_CNT_M;
		rc = !sw->reg->g_hsr_hw(sw, hsr);
		if (ctrl != *addr + 1)
			*addr = ctrl - 1;
	} else
		rc = -1;
	sw->ops->release(sw);
	return rc;
}  /* sw_g_hsr_table */

/**
 * sw_stop_hsr_hw - stop HSR table search using default access
 * @sw:		The switch instance.
 *
 * This function stops HSR table search using default access.
 *
 * Return the last HSR table control.
 */
static u32 sw_stop_hsr_hw(struct ksz_sw *sw)
{
	u32 ctrl;

	ctrl = 0;
	sw->reg->w32(sw, REG_HSR_ALU_CTRL__4, ctrl);
	ctrl = sw->reg->r32(sw, REG_HSR_ALU_CTRL__4);
	return ctrl;
}  /* sw_stop_hsr_hw */

/**
 * sw_stop_hsr_table - stop HSR table search
 * @sw:		The switch instance.
 * @addr:	The address of the last table entry.
 *
 * This routine stops HSR table search.
 */
static void sw_stop_hsr_table(struct ksz_sw *sw, u16 addr)
{
	u32 ctrl;

	sw->ops->acquire(sw);
	ctrl = sw->reg->stop_hsr_hw(sw);
	ctrl >>= HSR_VALID_CNT_S;
	ctrl &= HSR_VALID_CNT_M;
if (ctrl != addr)
dbg_msg(" ?stop: %x %x\n", ctrl, addr);
	sw->ops->release(sw);
	mutex_unlock(&sw->hsrlock);
}  /* sw_stop_hsr_table */

/**
 * sw_d_hsr_table - dump HSR table
 * @sw:		The switch instance.
 *
 * This routine dumps HSR table contents.
 */
static ssize_t sw_d_hsr_table(struct ksz_sw *sw, char *buf, ssize_t len)
{
	u16 i;
	struct ksz_hsr_table hsr;
	int first_break = true;

	sw_start_hsr_table(sw);
	i = 0;
	do {
		if (sw_g_hsr_table(sw, &i, &hsr))
			break;
		if (len >= MAX_SYSFS_BUF_SIZE && first_break) {
			first_break = false;
			len += sprintf(buf + len, "...\n");
		}
		if (len < MAX_SYSFS_BUF_SIZE)
		len += sprintf(buf + len,
			"%3x: %02X:%02X:%02X:%02X:%02X:%02X - %x "
			" c=%x  %04x:%04x  %04x:%04x  %04x:%04x  [%u]\n",
			i, hsr.src_mac[0], hsr.src_mac[1], hsr.src_mac[2],
			hsr.src_mac[3], hsr.src_mac[4], hsr.src_mac[5],
			hsr.path_id >> 1, hsr.age_cnt,
			hsr.start_seq[0], hsr.start_seq[1],
			hsr.exp_seq[0], hsr.exp_seq[1],
			hsr.seq_cnt[0], hsr.seq_cnt[1], hsr.valid);
		else {
		printk(KERN_INFO
			"%3x: %02X:%02X:%02X:%02X:%02X:%02X - %x "
			" c=%x  %04x:%04x  %04x:%04x  %04x:%04x  [%u]\n",
			i, hsr.src_mac[0], hsr.src_mac[1], hsr.src_mac[2],
			hsr.src_mac[3], hsr.src_mac[4], hsr.src_mac[5],
			hsr.path_id >> 1, hsr.age_cnt,
			hsr.start_seq[0], hsr.start_seq[1],
			hsr.exp_seq[0], hsr.exp_seq[1],
			hsr.seq_cnt[0], hsr.seq_cnt[1], hsr.valid);
		yield();
		}
		i++;
	} while (1);
	sw_stop_hsr_table(sw, i);
#if 1
	if (len < MAX_SYSFS_BUF_SIZE)
		len += sprintf(buf + len, "\n");
	else
		printk(KERN_INFO "\n");
	for (i = 0; i < HSR_INDEX_MAX; i++) {
		sw_r_hsr_table(sw, i + 1, &hsr);
		if (!hsr.valid && !hsr.age_cnt)
			continue;
		if (len >= MAX_SYSFS_BUF_SIZE && first_break) {
			first_break = false;
			len += sprintf(buf + len, "...\n");
		}
		if (len < MAX_SYSFS_BUF_SIZE)
		len += sprintf(buf + len,
			"%3x: %02X:%02X:%02X:%02X:%02X:%02X - %x "
			" c=%x  %04x:%04x  %04x:%04x  %04x:%04x  [%u]\n",
			i, hsr.src_mac[0], hsr.src_mac[1], hsr.src_mac[2],
			hsr.src_mac[3], hsr.src_mac[4], hsr.src_mac[5],
			hsr.path_id >> 1, hsr.age_cnt,
			hsr.start_seq[0], hsr.start_seq[1],
			hsr.exp_seq[0], hsr.exp_seq[1],
			hsr.seq_cnt[0], hsr.seq_cnt[1], hsr.valid);
		else {
		printk(KERN_INFO
			"%3x: %02X:%02X:%02X:%02X:%02X:%02X - %x "
			" c=%x  %04x:%04x  %04x:%04x  %04x:%04x  [%u]\n",
			i, hsr.src_mac[0], hsr.src_mac[1], hsr.src_mac[2],
			hsr.src_mac[3], hsr.src_mac[4], hsr.src_mac[5],
			hsr.path_id >> 1, hsr.age_cnt,
			hsr.start_seq[0], hsr.start_seq[1],
			hsr.exp_seq[0], hsr.exp_seq[1],
			hsr.seq_cnt[0], hsr.seq_cnt[1], hsr.valid);
		yield();
		}
	}
#endif
	return len;
}  /* sw_d_hsr_table */

/* -------------------------------------------------------------------------- */
#endif

/*
 * Port functions
 */

static void port_phy_w(struct ksz_sw *sw, u32 addr, u16 val)
{
	int shift;
	u32 data;

	shift = addr & 3;
	shift *= 8;
	shift = 16 - shift;
	addr &= ~3;
	data = sw->reg->r32(sw, addr);
	data &= ~(0xffff << shift);
	data |= (val << shift);
	sw->reg->w32(sw, addr, data);
}  /* port_phy_w */

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
static int port_chk(struct ksz_sw *sw, uint port, uint offset, SW_D bits)
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
static void port_cfg(struct ksz_sw *sw, uint port, uint offset, SW_D bits,
	bool set)
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
 * port_chk16 - check port register bits
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
static int port_chk16(struct ksz_sw *sw, uint port, uint offset, u16 bits)
{
	u32 addr;
	u16 data;

	addr = PORT_CTRL_ADDR(port, offset);
	data = sw->reg->r16(sw, addr);
	return (data & bits) == bits;
}  /* port_chk32 */

/**
 * port_cfg16 - set port register bits
 * @sw:		The switch instance.
 * @port:	The port index.
 * @offset:	The offset of the port register.
 * @bits:	The data bits to set.
 * @set:	The flag indicating whether the bits are to be set or not.
 *
 * This routine sets or resets the specified bits of the port register.
 */
static void port_cfg16(struct ksz_sw *sw, uint port, uint offset, u16 bits,
	bool set)
{
	u32 addr;
	u16 data;

	addr = PORT_CTRL_ADDR(port, offset);
	data = sw->reg->r16(sw, addr);
	if (set)
		data |= bits;
	else
		data &= ~bits;
	if (0x120 <= offset && offset <= 0x13F)
		port_phy_w(sw, addr, data);
	else
		sw->reg->w16(sw, addr, data);
}  /* port_cfg16 */

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
static int port_chk32(struct ksz_sw *sw, uint port, uint offset, u32 bits)
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
static void port_cfg32(struct ksz_sw *sw, uint port, uint offset, u32 bits,
	bool set)
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
static void port_r8(struct ksz_sw *sw, uint port, uint offset, u8 *data)
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
static void port_w8(struct ksz_sw *sw, uint port, uint offset, u8 data)
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
static void port_r16(struct ksz_sw *sw, uint port, uint offset, u16 *data)
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
static void port_w16(struct ksz_sw *sw, uint port, uint offset, u16 data)
{
	u32 addr;

	addr = PORT_CTRL_ADDR(port, offset);
	if (0x120 <= offset && offset <= 0x13F)
		port_phy_w(sw, addr, data);
	else
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
static void port_r32(struct ksz_sw *sw, uint port, uint offset, u32 *data)
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
static void port_w32(struct ksz_sw *sw, uint port, uint offset, u32 data)
{
	u32 addr;

	addr = PORT_CTRL_ADDR(port, offset);
	sw->reg->w32(sw, addr, data);
}  /* port_w32 */

static void port_get(struct ksz_sw *sw, uint port, uint offset, void *buf,
	size_t cnt)
{
	u32 addr;

	addr = PORT_CTRL_ADDR(port, offset);
	sw->reg->r(sw, addr, buf, cnt);
}

#if 0
static void port_set(struct ksz_sw *sw, uint port, uint offset, void *buf,
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

static u32 port_r_s_32(struct ksz_sw *sw, uint p, u32 reg, u32 mask,
	u32 shift)
{
	u32 data;

	port_r32(sw, p, reg, &data);
	data >>= shift;
	data &= mask;
	return data;
}

static void port_w_s_32(struct ksz_sw *sw, uint p, u32 reg, u32 mask,
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
static void port_out_rate_r8(struct ksz_sw *sw, uint port, uint offset, u8 *data)
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
static void port_out_rate_w8(struct ksz_sw *sw, uint port, uint offset, u8 data)
{
	u32 addr;

	PORT_OUT_RATE_ADDR(port, addr);
	addr += offset;
	sw->reg->w8(sw, addr, data);
}
#endif

/* -------------------------------------------------------------------------- */

/* ACL */

static inline void port_cfg_acl(struct ksz_sw *sw, uint p, bool set)
{
	port_cfg(sw, p,
		REG_PORT_MRI_AUTHEN_CTRL, PORT_ACL_ENABLE, set);
}

static inline int port_chk_acl(struct ksz_sw *sw, uint p)
{
	return port_chk(sw, p,
		REG_PORT_MRI_AUTHEN_CTRL, PORT_ACL_ENABLE);
}

static inline u8 port_get_authen_mode(struct ksz_sw *sw, uint p)
{
	return port_r_s(sw, p,
		REG_PORT_MRI_AUTHEN_CTRL, PORT_AUTHEN_MODE, 0);
}

static void port_set_authen_mode(struct ksz_sw *sw, uint p, u8 mode)
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
	if (acl->data[0] != 0xff)
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
			data[12] = 0;
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
 * This helper function waits for ACL table to be ready for access.
 */
static int wait_for_acl_table(struct ksz_sw *sw, uint port)
{
	u8 ctrl;
	int timeout = 100;

	if (!port_chk_acl(sw, port))
		dbg_msg("acl not on: %d\n", port);
	do {
		--timeout;
		if (!timeout)
			return 1;
		port_r(sw, port, REG_PORT_ACL_CTRL_0, &ctrl);
	} while (!(ctrl & (PORT_ACL_WRITE_DONE | PORT_ACL_READ_DONE)));
	return 0;
}  /* wait_for_acl_table */

/**
 * sw_r_acl_hw - read from ACL table using default access
 * @sw:		The switch instance.
 * @port:	The port index.
 * @addr:	The ACL index.
 * @data:	Buffer to hold the ACL data.
 *
 * This function reads from ACL table of the port using default access.
 */
static int sw_r_acl_hw(struct ksz_sw *sw, uint port, u16 addr, u8 data[])
{
	u8 ctrl = (addr & PORT_ACL_INDEX_M);

	port_w(sw, port, REG_PORT_ACL_CTRL_0, ctrl);
	do {
		port_r(sw, port, REG_PORT_ACL_CTRL_0, &ctrl);
	} while (!(ctrl & PORT_ACL_READ_DONE));
	sw_r(sw, PORT_CTRL_ADDR(port, REG_PORT_ACL_0), data, ACL_TABLE_LEN);
	return 1;
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
	if (wait_for_acl_table(sw, port))
		goto r_acl_exit;
	sw->reg->r_acl_hw(sw, port, addr, data);
	get_acl_table_info(acl, data);
	memcpy(acl->data, data, ACL_TABLE_LEN);

r_acl_exit:
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
 * This function writes to ACL table of the port using default access.
 */
static int sw_w_acl_hw(struct ksz_sw *sw, uint port, u16 addr, u8 data[])
{
	u8 ctrl = (addr & PORT_ACL_INDEX_M) | PORT_ACL_WRITE;

	sw_w(sw, PORT_CTRL_ADDR(port, REG_PORT_ACL_0), data, ACL_TABLE_LEN);
	port_w(sw, port, REG_PORT_ACL_CTRL_0, ctrl);
	do {
		port_r(sw, port, REG_PORT_ACL_CTRL_0, &ctrl);
	} while (!(ctrl & PORT_ACL_WRITE_DONE));
	return 1;
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
	if (wait_for_acl_table(sw, port))
		goto w_acl_act_exit;
	set_acl_action_info(acl, data);
	port_w16(sw, port, REG_PORT_ACL_BYTE_EN_MSB, ACL_ACTION_ENABLE);
	sw->reg->w_acl_hw(sw, port, addr, data);
	memcpy(&acl->data[ACL_ACTION_START], &data[ACL_ACTION_START],
		ACL_ACTION_LEN);

w_acl_act_exit:
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
	if (wait_for_acl_table(sw, port))
		goto w_acl_ruleset_exit;
	set_acl_ruleset_info(acl, data);
	port_w16(sw, port, REG_PORT_ACL_BYTE_EN_MSB, ACL_RULESET_ENABLE);
	sw->reg->w_acl_hw(sw, port, addr, data);

	/* First rule */
	acl->data[0] = data[0];
	memcpy(&acl->data[ACL_RULESET_START], &data[ACL_RULESET_START],
		ACL_RULESET_LEN);

w_acl_ruleset_exit:
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
	int len = ACL_ACTION_START;

	if (ACL_MODE_LAYER_2 == acl->mode &&
	    ACL_ENABLE_2_COUNT == acl->enable) {
		byte_enable |= ACL_ACTION_ENABLE;
		len += ACL_ACTION_LEN;
	}
	sw->ops->acquire(sw);
	if (wait_for_acl_table(sw, port))
		goto w_acl_rule_exit;
	set_acl_table_info(acl, data);
	port_w16(sw, port, REG_PORT_ACL_BYTE_EN_MSB, byte_enable);
	sw->reg->w_acl_hw(sw, port, addr, data);
	memcpy(acl->data, data, len);

w_acl_rule_exit:
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

	acl->data[0] = 0xff;
	memset(data, 0, sizeof(data));
	sw->ops->acquire(sw);
	if (wait_for_acl_table(sw, port))
		goto w_acl_exit;
	if (!(ACL_MODE_LAYER_2 == acl->mode &&
	    ACL_ENABLE_2_COUNT == acl->enable))
		set_acl_action_info(acl, data);
	set_acl_table_info(acl, data);
	set_acl_ruleset_info(acl, data);
	port_w16(sw, port, REG_PORT_ACL_BYTE_EN_MSB, ACL_BYTE_ENABLE);
	sw->reg->w_acl_hw(sw, port, addr, data);
	memcpy(acl->data, data, ACL_TABLE_LEN);

w_acl_exit:
	sw->ops->release(sw);
}  /* sw_w_acl_table */

/**
 * acl_action_info - format ACL action field information
 * @sw:		The switch instance.
 * @acl:	The ACL entry.
 * @index;	The entry index.
 * @buf:	Buffer to store the strings.
 * @len:	Lenght of buffer.
 *
 * This helper routine formats the ACL action field information.
 */
static int acl_action_info(struct ksz_sw *sw, struct ksz_acl_table *acl,
			   u16 index, char *buf, int len)
{
	char prio = 'p';
	char vlan = 'v';
	uint ports = acl->ports;

#ifdef USE_LOG_MASK
	ports = get_log_mask_from_phy(sw, ports);
#endif
	if (acl->prio_mode != ACL_PRIO_MODE_DISABLE)
		prio = 'P';
	if (acl->vlan_prio_replace)
		vlan = 'V';
	len += sprintf(buf + len,
		"%x: %c:%u=%u %c:%u=%u %u=%04x [%u]\n",
		index,
		prio, acl->prio_mode, acl->prio,
		vlan, acl->vlan_prio_replace, acl->vlan_prio,
		acl->map_mode, ports,
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
		len = acl_action_info(sw, acl, i, buf, len);
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

static int dbg_mib;

/**
 * sw_r_mib_cnt_hw - read MIB counters using default access
 * @sw:		The switch instance.
 * @port:	The port index.
 * @addr:	The addresses of the counters.
 * @num:	Number of entries to read.
 * @data:	Buffer to store the counters.
 *
 * This function reads MIB counters of the port using default access.
 */
static int sw_r_mib_cnt_hw(struct ksz_sw *sw, uint port, u32 addr[], int num,
			   u32 data[])
{
	int i;
	u32 ctrl_addr;
	struct ksz_port_cfg *cfg = get_port_cfg(sw, port);
	u32 freeze = cfg->freeze ? MIB_COUNTER_FLUSH_FREEZE : 0;

	for (i = 0; i < num; i++) {
		ctrl_addr = (addr[i] & MIB_COUNTER_INDEX_M);
		ctrl_addr <<= MIB_COUNTER_INDEX_S;
		ctrl_addr |= MIB_COUNTER_READ;
		ctrl_addr |= freeze;

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
			if (!(data[0] & MIB_COUNTER_VALID) && dbg_mib++ < 5)
				dbg_msg(" !valid: %08x\n", data[0]);
			data[1] = be32_to_cpu(data[1]);
		} while (!(data[0] & MIB_COUNTER_VALID));
		data += READ_MIB_ENTRY_SIZE;
	}
	return 1;
}  /* sw_r_mib_cnt_hw */

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
	u32 index[MAX_IBA_MIB_ENTRIES];
	u32 data[MAX_IBA_MIB_ENTRIES * READ_MIB_ENTRY_SIZE];
	u8 start;
	int cnt;
	int i;
	int rc;

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
		rc = sw->reg->r_mib_cnt_hw(sw, port, index, cnt, data);
		sw->ops->release(sw);
		if (!rc)
			return mib->cnt_ptr;
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

static void port_freeze_mib(struct ksz_sw *sw, uint port, bool freeze)
{
	u32 ctrl = freeze ? MIB_COUNTER_FLUSH_FREEZE : 0;
	struct ksz_port_cfg *cfg = get_port_cfg(sw, port);

	cfg->freeze = !!freeze;
	port_w32(sw, port, REG_PORT_MIB_CTRL_STAT__4, ctrl);
}  /* port_freeze_mib */

static void sw_freeze_mib(struct ksz_sw *sw, bool freeze)
{
	sw_cfg(sw, REG_SW_MAC_CTRL_6, SW_MIB_COUNTER_FREEZE, freeze);
}  /* sw_freeze_mib */

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
	u32 index[MAX_IBA_MIB_ENTRIES];
	u32 data[MAX_IBA_MIB_ENTRIES * READ_MIB_ENTRY_SIZE];
	int cnt;
	int i;
	int rc;

	sw->ops->acquire(sw);
	mib->cnt_ptr = 0;
	mib->interval = 0;
	do {
		cnt = MAX_IBA_MIB_ENTRIES;
		if (cnt > TOTAL_SWITCH_COUNTER_NUM - mib->cnt_ptr)
			cnt = TOTAL_SWITCH_COUNTER_NUM - mib->cnt_ptr;
		for (i = 0; i < cnt; i++, mib->cnt_ptr++)
			index[i] = mib_index[mib->cnt_ptr];
		rc = sw->reg->r_mib_cnt_hw(sw, port, index, cnt, data);
		if (!rc)
			break;
	} while (mib->cnt_ptr < TOTAL_SWITCH_COUNTER_NUM);
	memset((void *) mib->counter, 0, sizeof(u64) *
		TOTAL_SWITCH_COUNTER_NUM);
	mib->cnt_ptr = 0;
	mib->rate[0].last = mib->rate[1].last = 0;
	mib->rate[0].last_cnt = mib->rate[1].last_cnt = 0;
	mib->rate[0].peak = mib->rate[1].peak = 0;
	sw->ops->release(sw);
}  /* port_init_cnt */

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
static void hw_cfg_rate_limit(struct ksz_sw *sw, uint port, u8 mask, u8 shift,
			      u8 mode)
{
	u8 data;
	u8 saved;
	struct ksz_port_cfg *cfg = get_port_cfg(sw, port);

	port_r8(sw, port, P_RATE_LIMIT_CTRL, &data);
	saved = data;
	data &= ~(mask << shift);
	data |= mode << shift;
	if (data != saved)
		port_w8(sw, port, P_RATE_LIMIT_CTRL, data);
	cfg->rate_limit = data;
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
static void port_cfg_rate(struct ksz_sw *sw, uint port, uint prio, uint offset,
			  uint rate, bool packet)
{
	u8 factor;
	struct ksz_port_info *info = get_port_info(sw, port);

	if (info->tx_rate / TX_RATE_UNIT == 1000)
		rate /= 10;
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
static void port_get_rate(struct ksz_sw *sw, uint port, uint prio, uint offset,
			  uint *rate, bool packet)
{
	u8 data;
	struct ksz_port_info *info = get_port_info(sw, port);

	port_r8(sw, port, offset + prio, &data);
	if (packet)
		*rate = get_packet_from_val(data);
	else
		*rate = get_rate_from_val(data);
	if (info->tx_rate / TX_RATE_UNIT == 1000)
		*rate *= 10;
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
static void hw_cfg_prio_rate(struct ksz_sw *sw, uint port, uint prio,
			     uint rate, uint offset, uint *result, bool packet)
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

	port_r8(sw, port, REG_PORT_IN_RATE_0 + RX_PRIO_QUEUES - 1, &data);
	port_w8(sw, port, REG_PORT_IN_RATE_0 + RX_PRIO_QUEUES - 1, data);
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
static void hw_cfg_rx_prio_rate(struct ksz_sw *sw, uint port, uint prio,
				uint rate)
{
	uint *result;
	struct ksz_port_cfg *cfg = get_port_cfg(sw, port);

	if (cfg->packet_based)
		result = &cfg->rx_packet[prio];
	else
		result = &cfg->rx_rate[prio];
	hw_cfg_prio_rate(sw, port, prio, rate, REG_PORT_IN_RATE_0, result,
			 cfg->packet_based);
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
static void hw_cfg_tx_prio_rate(struct ksz_sw *sw, uint port, uint prio,
				uint rate)
{
	uint *result;
	struct ksz_port_cfg *cfg = get_port_cfg(sw, port);

	if (cfg->packet_based)
		result = &cfg->tx_packet[prio];
	else
		result = &cfg->tx_rate[prio];
	hw_cfg_prio_rate(sw, port, prio, rate, REG_PORT_OUT_RATE_0, result,
			 cfg->packet_based);
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
	u32 in_rate0;
	u32 in_rate1;

	rate_addr = PORT_CTRL_ADDR(port, REG_PORT_IN_RATE_0);
	in_rate0 = sw->reg->r32(sw, rate_addr);
	in_rate1 = sw->reg->r32(sw, rate_addr + 4);
	return (in_rate0 | in_rate1) != 0;
}  /* sw_chk_rx_prio_rate */

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

	rate_addr = PORT_CTRL_ADDR(port, REG_PORT_OUT_RATE_0);
	if (sw_chk(sw, REG_SW_MAC_CTRL_5, SW_OUT_RATE_LIMIT_QUEUE_BASED))
		out_rate = sw->reg->r32(sw, rate_addr);

	/* Only need to check first priority as the others do not matter. */
	else
		out_rate = sw->reg->r8(sw, rate_addr);
	return (out_rate) != 0;
}  /* sw_chk_tx_prio_rate */

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

	rate_addr = PORT_CTRL_ADDR(port, REG_PORT_IN_RATE_0);
	sw->reg->w32(sw, rate_addr, 0);
	sw->reg->w32(sw, rate_addr + 4, 0);
}  /* sw_dis_rx_prio_rate */

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

	rate_addr = PORT_CTRL_ADDR(port, REG_PORT_OUT_RATE_0);
	sw->reg->w32(sw, rate_addr, 0);
}  /* sw_dis_tx_prio_rate */

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
	for (prio = 0; prio < RX_PRIO_QUEUES; prio++, rate++)
		hw_cfg_rx_prio_rate(sw, port, prio, *rate);
}  /* sw_ena_rx_prio_rate */

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

		/* Rate limiting is not enabled. */
		if (!cfg->rx_rate[prio] && !cfg->rx_packet[prio])
			continue;
		hw_cfg_rx_prio_rate(sw, port, prio, *rx_rate);

		/* Rate limiting is not enabled. */
		if (!cfg->tx_rate[prio] && !cfg->tx_packet[prio])
			continue;
		hw_cfg_tx_prio_rate(sw, port, prio, *tx_rate);
	}
	for (; prio < RX_PRIO_QUEUES; prio++, rx_rate++) {

/* See issue above about configuring rx priority rates. */
#if 0
		/* Rate limiting is not enabled. */
		if (!cfg->rx_rate[prio] && !cfg->rx_packet[prio])
			continue;
#endif
		hw_cfg_rx_prio_rate(sw, port, prio, *rx_rate);
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
		for (prio = 0; prio < RX_PRIO_QUEUES; prio++) {
			offset = REG_PORT_IN_RATE_0;
			port_get_rate(sw, port, prio, offset,
				      &cfg->rx_rate[prio], false);
			port_get_rate(sw, port, prio, offset,
				      &cfg->rx_packet[prio], true);
		}
		for (prio = 0; prio < PRIO_QUEUES; prio++) {
			offset = REG_PORT_OUT_RATE_0;
			port_get_rate(sw, port, prio, offset,
				      &cfg->tx_rate[prio], false);
			port_get_rate(sw, port, prio, offset,
				      &cfg->tx_rate[prio], true);
		}
	}
}  /* sw_init_prio_rate */

/* -------------------------------------------------------------------------- */

/* Communication */

static inline void port_cfg_back_pressure(struct ksz_sw *sw, uint p, bool set)
{
	port_cfg(sw, p,
		REG_PORT_MAC_CTRL_1, PORT_BACK_PRESSURE, set);
}

static inline void port_cfg_force_flow_ctrl(struct ksz_sw *sw, uint p, bool set)
{
	port_cfg(sw, p,
		REG_PORT_CTRL_0,
		PORT_FORCE_TX_FLOW_CTRL | PORT_FORCE_RX_FLOW_CTRL, set);
}

static inline void port_cfg_mac_loopback(struct ksz_sw *sw, uint p, bool set)
{
	port_cfg(sw, p,
		REG_PORT_CTRL_0, PORT_MAC_LOOPBACK, set);
}

static void port_cfg_phy_loopback(struct ksz_sw *sw, uint p, bool set)
{
	u16 data;
	struct ksz_port_cfg *cfg = get_port_cfg(sw, p);

	port_r16(sw, p, REG_PORT_PHY_CTRL, &data);
	if (set) {
		if (!(data & PORT_PHY_LOOPBACK)) {
			cfg->phy_ctrl = data;
			data &= ~PORT_AUTO_NEG_ENABLE;
			data |= PORT_PHY_LOOPBACK;
		}
	} else {
		if (data & PORT_PHY_LOOPBACK)
			data = cfg->phy_ctrl;
	}
	port_w16(sw, p, REG_PORT_PHY_CTRL, data);
}

static inline void port_cfg_remote_loopback(struct ksz_sw *sw, uint p, bool set)
{
	port_cfg16(sw, p,
		REG_PORT_PHY_REMOTE_LB_LED, PORT_REMOTE_LOOPBACK, set);
}

static inline void port_cfg_tail_tag(struct ksz_sw *sw, uint p, bool set)
{
	port_cfg(sw, p,
		REG_PORT_CTRL_0, PORT_TAIL_TAG_ENABLE, set);
}

static inline int port_chk_back_pressure(struct ksz_sw *sw, uint p)
{
	return port_chk(sw, p,
		REG_PORT_MAC_CTRL_1, PORT_BACK_PRESSURE);
}

static inline int port_chk_force_flow_ctrl(struct ksz_sw *sw, uint p)
{
	return port_chk(sw, p,
		REG_PORT_CTRL_0,
		PORT_FORCE_TX_FLOW_CTRL | PORT_FORCE_RX_FLOW_CTRL);
}

static inline int port_chk_mac_loopback(struct ksz_sw *sw, uint p)
{
	return port_chk(sw, p,
		REG_PORT_CTRL_0, PORT_MAC_LOOPBACK);
}

static inline int port_chk_phy_loopback(struct ksz_sw *sw, uint p)
{
	return port_chk16(sw, p,
		REG_PORT_PHY_CTRL, PORT_PHY_LOOPBACK);
}

static inline int port_chk_remote_loopback(struct ksz_sw *sw, uint p)
{
	return port_chk16(sw, p,
		REG_PORT_PHY_REMOTE_LB_LED, PORT_REMOTE_LOOPBACK);
}

static inline int port_chk_tail_tag(struct ksz_sw *sw, uint p)
{
	return port_chk(sw, p,
		REG_PORT_CTRL_0, PORT_TAIL_TAG_ENABLE);
}

/* -------------------------------------------------------------------------- */

/* Spanning Tree */

static inline void port_cfg_mstp(struct ksz_sw *sw, uint p, u8 mstp)
{
	struct ksz_port_cfg *cfg = get_port_cfg(sw, p);

	if (cfg->mstp != mstp) {
		port_w(sw, p, REG_PORT_LUE_MSTP_INDEX, mstp);
		cfg->mstp = mstp;
	}
}

static inline void port_cfg_dis_learn(struct ksz_sw *sw, uint p, bool set)
{
	port_cfg(sw, p,
		P_STP_CTRL, PORT_LEARN_DISABLE, set);
}

static inline void port_cfg_rx(struct ksz_sw *sw, uint p, bool set)
{
	struct ksz_port_cfg *cfg = get_port_cfg(sw, p);
	uint m = BIT(p);

	port_cfg(sw, p,
		 P_STP_CTRL, PORT_RX_ENABLE, set);
	if (set)
		sw->rx_ports[cfg->mstp] |= m;
	else
		sw->rx_ports[cfg->mstp] &= ~m;
}

static inline void port_cfg_tx(struct ksz_sw *sw, uint p, bool set)
{
	struct ksz_port_cfg *cfg = get_port_cfg(sw, p);
	uint m = BIT(p);

	port_cfg(sw, p,
		 P_STP_CTRL, PORT_TX_ENABLE, set);
	if (set)
		sw->tx_ports[cfg->mstp] |= m;
	else
		sw->tx_ports[cfg->mstp] &= ~m;
}

static inline u8 port_chk_mstp(struct ksz_sw *sw, uint p)
{
	SW_D mstp;

	port_r(sw, p, REG_PORT_LUE_MSTP_INDEX, &mstp);
	return mstp;
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

static void port_cfg_rx_special(struct ksz_sw *sw, uint p, bool set)
{
	int hsr = false;

#ifdef CONFIG_KSZ_HSR
	if (sw->features & HSR_HW)
		hsr = true;
#endif
	if (!hsr)
		port_cfg_rx(sw, p, set);
#ifdef CONFIG_KSZ_HSR
	else {
		if (set)
			port_cfg_rx(sw, p, set);
		do {
			int n;
			u16 mask = 0;

			for (n = 0; n < sw->eth_cnt; n++) {
				if (sw->eth_maps[n].proto & HSR_HW) {
					mask = sw->eth_maps[n].mask;
					break;
				}
			}
			if (mask & (1 << p)) {
				u32 val;

				val = sw->reg->r32(sw, REG_HSR_PORT_MAP__4);
				if (set)
					val |= mask & ~(1 << p);
				else
					val &= (1 << p);
				sw->reg->w32(sw, REG_HSR_PORT_MAP__4, val);
			}
		} while (0);
		if (!set)
			port_cfg_rx(sw, p, set);
	}
#endif
}  /* port_cfg_rx_special */

static void port_cfg_power(struct ksz_sw *sw, uint p, bool set)
{
	u16 ctrl;
	u8 intr;
	struct ksz_port_cfg *cfg = get_port_cfg(sw, p);

	if (set) {
		u32 data;

		port_r16(sw, p, REG_PORT_PHY_CTRL, &ctrl);
		if (!(ctrl & PORT_POWER_DOWN))
			return;
		ctrl = cfg->phy_ctrl;
		port_w16(sw, p, REG_PORT_PHY_CTRL, cfg->phy_ctrl);
		port_r16(sw, p, REG_PORT_PHY_CTRL, &ctrl);
		port_r16(sw, p, REG_PORT_PHY_AUTO_NEGOTIATION, &ctrl);
		if (ctrl != cfg->phy_adv)
			port_w16(sw, p, REG_PORT_PHY_AUTO_NEGOTIATION,
				cfg->phy_adv);
		if (sw->features & GIGABIT_SUPPORT) {
			port_r16(sw, p, REG_PORT_PHY_1000_CTRL, &ctrl);
			if (ctrl != cfg->phy_adv_g)
				port_w16(sw, p, REG_PORT_PHY_1000_CTRL,
					cfg->phy_adv_g);
		}
		port_r32(sw, p, REG_PORT_PHY_INT_ENABLE & ~3, &data);
		data &= 0xffff00ff;
		data |= cfg->phy_intr << 8;
		port_w32(sw, p, REG_PORT_PHY_INT_ENABLE & ~3, data);
		ctrl = cfg->phy_ctrl;
		if (ctrl & PORT_AUTO_NEG_ENABLE)
			ctrl |= PORT_AUTO_NEG_RESTART;
		port_w16(sw, p, REG_PORT_PHY_CTRL, ctrl);
	} else {
		port_r8(sw, p, REG_PORT_PHY_INT_ENABLE, &intr);
		cfg->phy_intr = intr;
		port_r16(sw, p, REG_PORT_PHY_AUTO_NEGOTIATION, &ctrl);
		cfg->phy_adv = ctrl;
		if (sw->features & GIGABIT_SUPPORT) {
			port_r16(sw, p, REG_PORT_PHY_1000_CTRL, &ctrl);
			cfg->phy_adv_g = ctrl;
		}
		port_r16(sw, p, REG_PORT_PHY_CTRL, &ctrl);
		ctrl &= ~PORT_POWER_DOWN;
		cfg->phy_ctrl = ctrl;
		port_w16(sw, p, REG_PORT_PHY_CTRL, ctrl | PORT_POWER_DOWN);
	}
}  /* port_cfg_power */

static int port_chk_power(struct ksz_sw *sw, uint p)
{
	u16 ctrl;

	port_r16(sw, p, REG_PORT_PHY_CTRL, &ctrl);
	return !(ctrl & PORT_POWER_DOWN);
}  /* port_chk_power */

static inline void sw_cfg_fast_aging(struct ksz_sw *sw, bool set)
{
	sw_cfg(sw, REG_SW_LUE_CTRL_1, SW_FAST_AGING, set);
}

static void sw_flush_dyn_mac_table(struct ksz_sw *sw, uint port)
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
	if (port < sw->port_cnt) {
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
		sw_cfg(sw, S_FLUSH_TABLE_CTRL, SW_FLUSH_STP_TABLE, 1);
	}
}  /* sw_flush_dyn_mac_table */

/* -------------------------------------------------------------------------- */

/* VLAN */

static inline void port_cfg_drop_non_vlan(struct ksz_sw *sw, uint p, bool set)
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
static inline void port_cfg_drop_tag(struct ksz_sw *sw, uint p, bool set)
{
	port_cfg(sw, p,
		REG_PORT_MRI_MAC_CTRL, PORT_DROP_TAG, set);
}

static inline int port_chk_drop_non_vlan(struct ksz_sw *sw, uint p)
{
	return port_chk(sw, p,
		REG_PORT_MRI_MAC_CTRL, PORT_DROP_NON_VLAN);
}

static inline int port_chk_drop_tag(struct ksz_sw *sw, uint p)
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
static inline void port_cfg_dis_non_vid(struct ksz_sw *sw, uint p, bool set)
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
static inline void port_cfg_in_filter(struct ksz_sw *sw, uint p, bool set)
{
	port_cfg(sw, p,
		REG_PORT_LUE_CTRL, PORT_INGRESS_FILTER, set);
}  /* port_cfg_in_filter */

static inline int port_chk_dis_non_vid(struct ksz_sw *sw, uint p)
{
	return port_chk(sw, p,
		REG_PORT_LUE_CTRL, PORT_DISCARD_NON_VID);
}

static inline int port_chk_in_filter(struct ksz_sw *sw, uint p)
{
	return port_chk(sw, p,
		REG_PORT_LUE_CTRL, PORT_INGRESS_FILTER);
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

/* Priority */

static inline void port_cfg_diffserv(struct ksz_sw *sw, uint p, bool set)
{
	port_cfg(sw, p,
		P_PRIO_CTRL, PORT_DIFFSERV_PRIO_ENABLE, set);
}

static inline void port_cfg_802_1p(struct ksz_sw *sw, uint p, bool set)
{
	port_cfg(sw, p,
		P_PRIO_CTRL, PORT_802_1P_PRIO_ENABLE, set);
}

static inline void port_cfg_vlan_prio(struct ksz_sw *sw, uint p, bool set)
{
	port_cfg(sw, p,
		P_PRIO_CTRL, PORT_VLAN_PRIO_ENABLE, set);
}

static inline void port_cfg_mac_prio(struct ksz_sw *sw, uint p, bool set)
{
	port_cfg(sw, p,
		P_PRIO_CTRL, PORT_MAC_PRIO_ENABLE, set);
}

static inline void port_cfg_acl_prio(struct ksz_sw *sw, uint p, bool set)
{
	port_cfg(sw, p,
		P_PRIO_CTRL, PORT_ACL_PRIO_ENABLE, set);
}

static inline void port_cfg_highest_prio(struct ksz_sw *sw, uint p, bool set)
{
	port_cfg(sw, p,
		P_PRIO_CTRL, PORT_HIGHEST_PRIO, set);
}

static inline void port_cfg_or_prio(struct ksz_sw *sw, uint p, bool set)
{
	port_cfg(sw, p,
		P_PRIO_CTRL, PORT_OR_PRIO, set);
}

static inline void port_cfg_replace_prio(struct ksz_sw *sw, uint p, bool set)
{
	port_cfg(sw, p,
		REG_PORT_MRI_MAC_CTRL, PORT_USER_PRIO_CEILING, set);
}

static inline void port_set_prio_queue(struct ksz_sw *sw, uint p, uint queue)
{
	port_w_s(sw, p,
		REG_PORT_CTRL_0, PORT_QUEUE_SPLIT_ENABLE, 0, queue);
}

static inline int port_chk_diffserv(struct ksz_sw *sw, uint p)
{
	return port_chk(sw, p,
		P_PRIO_CTRL, PORT_DIFFSERV_PRIO_ENABLE);
}

static inline int port_chk_802_1p(struct ksz_sw *sw, uint p)
{
	return port_chk(sw, p,
		P_PRIO_CTRL, PORT_802_1P_PRIO_ENABLE);
}

static inline int port_chk_vlan_prio(struct ksz_sw *sw, uint p)
{
	return port_chk(sw, p,
		P_PRIO_CTRL, PORT_VLAN_PRIO_ENABLE);
}

static inline int port_chk_mac_prio(struct ksz_sw *sw, uint p)
{
	return port_chk(sw, p,
		P_PRIO_CTRL, PORT_MAC_PRIO_ENABLE);
}

static inline int port_chk_acl_prio(struct ksz_sw *sw, uint p)
{
	return port_chk(sw, p,
		P_PRIO_CTRL, PORT_ACL_PRIO_ENABLE);
}

static inline int port_chk_highest_prio(struct ksz_sw *sw, uint p)
{
	return port_chk(sw, p,
		P_PRIO_CTRL, PORT_HIGHEST_PRIO);
}

static inline int port_chk_or_prio(struct ksz_sw *sw, uint p)
{
	return port_chk(sw, p,
		P_PRIO_CTRL, PORT_OR_PRIO);
}

static inline int port_chk_replace_prio(struct ksz_sw *sw, uint p)
{
	return port_chk(sw, p,
		REG_PORT_MRI_MAC_CTRL, PORT_USER_PRIO_CEILING);
}

static inline int port_get_prio_queue(struct ksz_sw *sw, uint p)
{
	return port_r_s(sw, p,
		REG_PORT_CTRL_0, PORT_QUEUE_SPLIT_ENABLE, 0);
}

/* -------------------------------------------------------------------------- */

/* Policing */

static void port_cfg_index(struct ksz_sw *sw, uint port, uint p, uint q)
{
	u32 data;

	data = (p & MRI_INDEX_P_M) << MRI_INDEX_P_S;
	data |= (q & MRI_INDEX_Q_M) << MRI_INDEX_Q_S;
	port_w32(sw, port, REG_PORT_MRI_INDEX__4, data);
}

static inline void port_cfg_police(struct ksz_sw *sw, uint p, bool set)
{
	port_cfg32(sw, p,
		REG_PORT_MRI_POLICE_CTRL__4, POLICE_ENABLE, set);
}

static inline void port_cfg_color_aware(struct ksz_sw *sw, uint p, bool set)
{
	port_cfg32(sw, p,
		REG_PORT_MRI_POLICE_CTRL__4, POLICE_COLOR_NOT_AWARE, !set);
}

static inline void port_cfg_drop_srp(struct ksz_sw *sw, uint p, bool set)
{
	port_cfg32(sw, p,
		REG_PORT_MRI_POLICE_CTRL__4, POLICE_DROP_SRP, set);
}

static inline void port_cfg_color_mark(struct ksz_sw *sw, uint p, bool set)
{
	port_cfg32(sw, p,
		REG_PORT_MRI_POLICE_CTRL__4, COLOR_MARK_ENABLE, set);
}

static inline void port_cfg_color_remap(struct ksz_sw *sw, uint p, bool set)
{
	port_cfg32(sw, p,
		REG_PORT_MRI_POLICE_CTRL__4, COLOR_REMAP_ENABLE, set);
}

static inline void port_cfg_port_based_policing(struct ksz_sw *sw, uint p,
	bool set)
{
	port_cfg32(sw, p,
		REG_PORT_MRI_POLICE_CTRL__4, PORT_BASED_POLICING, set);
}

static inline void port_cfg_police_drop_all(struct ksz_sw *sw, uint p, bool set)
{
	port_cfg32(sw, p,
		REG_PORT_MRI_POLICE_CTRL__4, POLICE_DROP_ALL, set);
}

static inline void port_set_police_packet_type(struct ksz_sw *sw, uint p,
	u32 type)
{
	port_w_s_32(sw, p,
		REG_PORT_MRI_POLICE_CTRL__4, POLICE_PACKET_TYPE_M,
			POLICE_PACKET_TYPE_S, type);
}

static inline void port_set_non_dscp_color(struct ksz_sw *sw, uint p, u32 color)
{
	port_w_s_32(sw, p,
		REG_PORT_MRI_POLICE_CTRL__4, SW_COLOR_M,
			NON_DSCP_COLOR_S, color);
}

static inline int port_chk_police(struct ksz_sw *sw, uint p)
{
	return port_chk32(sw, p,
		REG_PORT_MRI_POLICE_CTRL__4, POLICE_ENABLE);
}

static inline int port_chk_color_aware(struct ksz_sw *sw, uint p)
{
	return !port_chk32(sw, p,
		REG_PORT_MRI_POLICE_CTRL__4, POLICE_COLOR_NOT_AWARE);
}

static inline int port_chk_drop_srp(struct ksz_sw *sw, uint p)
{
	return port_chk32(sw, p,
		REG_PORT_MRI_POLICE_CTRL__4, POLICE_DROP_SRP);
}

static inline int port_chk_color_mark(struct ksz_sw *sw, uint p)
{
	return port_chk32(sw, p,
		REG_PORT_MRI_POLICE_CTRL__4, COLOR_MARK_ENABLE);
}

static inline int port_chk_color_remap(struct ksz_sw *sw, uint p)
{
	return port_chk32(sw, p,
		REG_PORT_MRI_POLICE_CTRL__4, COLOR_REMAP_ENABLE);
}

static inline int port_chk_port_based_policing(struct ksz_sw *sw, uint p)
{
	return port_chk32(sw, p,
		REG_PORT_MRI_POLICE_CTRL__4, PORT_BASED_POLICING);
}

static inline int port_chk_police_drop_all(struct ksz_sw *sw, uint p)
{
	return port_chk32(sw, p,
		REG_PORT_MRI_POLICE_CTRL__4, POLICE_DROP_ALL);
}

static inline u32 port_get_police_packet_type(struct ksz_sw *sw, uint p)
{
	return port_r_s_32(sw, p,
		REG_PORT_MRI_POLICE_CTRL__4, POLICE_PACKET_TYPE_M,
			POLICE_PACKET_TYPE_S);
}

static inline u32 port_get_non_dscp_color(struct ksz_sw *sw, uint p)
{
	return port_r_s_32(sw, p,
		REG_PORT_MRI_POLICE_CTRL__4, SW_COLOR_M,
			NON_DSCP_COLOR_S);
}

static inline u16 port_get_cir(struct ksz_sw *sw, uint p)
{
	return port_r_s_32(sw, p,
		REG_PORT_POLICE_RATE__4, 0xffff, POLICE_CIR_S);
}

static inline u16 port_get_pir(struct ksz_sw *sw, uint p)
{
	return port_r_s_32(sw, p,
		REG_PORT_POLICE_RATE__4, 0xffff, POLICE_PIR_S);
}

static inline void port_set_cir(struct ksz_sw *sw, uint p, u16 rate)
{
	port_w_s_32(sw, p,
		REG_PORT_POLICE_RATE__4, 0xffff, POLICE_CIR_S, rate);
}

static inline void port_set_pir(struct ksz_sw *sw, uint p, u16 rate)
{
	port_w_s_32(sw, p,
		REG_PORT_POLICE_RATE__4, 0xffff, POLICE_PIR_S, rate);
}

static inline u16 port_get_cbs(struct ksz_sw *sw, uint p)
{
	return port_r_s_32(sw, p,
		REG_PORT_POLICE_BURST_SIZE__4, POLICE_BURST_SIZE_M,
			POLICE_CBS_S);
}

static inline u16 port_get_pbs(struct ksz_sw *sw, uint p)
{
	return port_r_s_32(sw, p,
		REG_PORT_POLICE_BURST_SIZE__4, POLICE_BURST_SIZE_M,
			POLICE_PBS_S);
}

static inline void port_set_cbs(struct ksz_sw *sw, uint p, u16 size)
{
	port_w_s_32(sw, p,
		REG_PORT_POLICE_BURST_SIZE__4, POLICE_BURST_SIZE_M,
			POLICE_CBS_S, size);
}

static inline void port_set_pbs(struct ksz_sw *sw, uint p, u16 size)
{
	port_w_s_32(sw, p,
		REG_PORT_POLICE_BURST_SIZE__4, POLICE_BURST_SIZE_M,
			POLICE_PBS_S, size);
}

static inline u16 port_get_wred_max(struct ksz_sw *sw, uint p)
{
	return port_r_s_32(sw, p,
		REG_PORT_WRED_PM_CTRL_0__4, WRED_PM_CTRL_M,
			WRED_PM_MAX_THRESHOLD_S);
}

static inline u16 port_get_wred_min(struct ksz_sw *sw, uint p)
{
	return port_r_s_32(sw, p,
		REG_PORT_WRED_PM_CTRL_0__4, WRED_PM_CTRL_M,
			WRED_PM_MIN_THRESHOLD_S);
}

static inline u16 port_get_wred_multiplier(struct ksz_sw *sw, uint p)
{
	return port_r_s_32(sw, p,
		REG_PORT_WRED_PM_CTRL_1__4, WRED_PM_CTRL_M,
			WRED_PM_MULTIPLIER_S);
}

static inline u16 port_get_wred_avg_size(struct ksz_sw *sw, uint p)
{
	return port_r_s_32(sw, p,
		REG_PORT_WRED_PM_CTRL_1__4, WRED_PM_CTRL_M,
			WRED_PM_AVG_QUEUE_SIZE_S);
}

static inline void port_set_wred_max(struct ksz_sw *sw, uint p, u16 threshold)
{
	port_w_s_32(sw, p,
		REG_PORT_WRED_PM_CTRL_0__4, WRED_PM_CTRL_M,
			WRED_PM_MAX_THRESHOLD_S, threshold);
}

static inline void port_set_wred_min(struct ksz_sw *sw, uint p, u16 threshold)
{
	port_w_s_32(sw, p,
		REG_PORT_WRED_PM_CTRL_0__4, WRED_PM_CTRL_M,
			WRED_PM_MIN_THRESHOLD_S, threshold);
}

static inline void port_set_wred_multiplier(struct ksz_sw *sw, uint p, u16 val)
{
	port_w_s_32(sw, p,
		REG_PORT_WRED_PM_CTRL_1__4, WRED_PM_CTRL_M,
			WRED_PM_MULTIPLIER_S, val);
}

static inline u16 port_get_wred_q_max(struct ksz_sw *sw, uint p)
{
	return port_r_s_32(sw, p,
		REG_PORT_WRED_QUEUE_CTRL_0__4, WRED_PM_CTRL_M,
			WRED_PM_MAX_THRESHOLD_S);
}

static inline u16 port_get_wred_q_min(struct ksz_sw *sw, uint p)
{
	return port_r_s_32(sw, p,
		REG_PORT_WRED_QUEUE_CTRL_0__4, WRED_PM_CTRL_M,
			WRED_PM_MIN_THRESHOLD_S);
}

static inline u16 port_get_wred_q_multiplier(struct ksz_sw *sw, uint p)
{
	return port_r_s_32(sw, p,
		REG_PORT_WRED_QUEUE_CTRL_1__4, WRED_PM_CTRL_M,
			WRED_PM_MULTIPLIER_S);
}

static inline u16 port_get_wred_q_avg_size(struct ksz_sw *sw, uint p)
{
	return port_r_s_32(sw, p,
		REG_PORT_WRED_QUEUE_CTRL_1__4, WRED_PM_CTRL_M,
			WRED_PM_AVG_QUEUE_SIZE_S);
}

static inline void port_set_wred_q_max(struct ksz_sw *sw, uint p, u16 threshold)
{
	port_w_s_32(sw, p,
		REG_PORT_WRED_QUEUE_CTRL_0__4, WRED_PM_CTRL_M,
			WRED_PM_MAX_THRESHOLD_S, threshold);
}

static inline void port_set_wred_q_min(struct ksz_sw *sw, uint p, u16 threshold)
{
	port_w_s_32(sw, p,
		REG_PORT_WRED_QUEUE_CTRL_0__4, WRED_PM_CTRL_M,
			WRED_PM_MIN_THRESHOLD_S, threshold);
}

static inline void port_set_wred_q_multiplier(struct ksz_sw *sw, uint p, u16 val)
{
	port_w_s_32(sw, p,
		REG_PORT_WRED_QUEUE_CTRL_1__4, WRED_PM_CTRL_M,
			WRED_PM_MULTIPLIER_S, val);
}

static inline void port_cfg_wred_random_drop(struct ksz_sw *sw, uint p, bool set)
{
	port_cfg32(sw, p,
		REG_PORT_WRED_QUEUE_PMON__4, WRED_RANDOM_DROP_ENABLE, set);
}

static inline void port_cfg_wred_drop_gyr(struct ksz_sw *sw, uint p, bool set)
{
	port_cfg32(sw, p,
		REG_PORT_WRED_QUEUE_PMON__4, WRED_DROP_GYR_DISABLE, !set);
}

static inline void port_cfg_wred_drop_yr(struct ksz_sw *sw, uint p, bool set)
{
	port_cfg32(sw, p,
		REG_PORT_WRED_QUEUE_PMON__4, WRED_DROP_YR_DISABLE, !set);
}

static inline void port_cfg_wred_drop_r(struct ksz_sw *sw, uint p, bool set)
{
	port_cfg32(sw, p,
		REG_PORT_WRED_QUEUE_PMON__4, WRED_DROP_R_DISABLE, !set);
}

static inline void port_cfg_wred_drop_all(struct ksz_sw *sw, uint p, bool set)
{
	port_cfg32(sw, p,
		REG_PORT_WRED_QUEUE_PMON__4, WRED_DROP_ALL, set);
}

static inline int port_chk_wred_random_drop(struct ksz_sw *sw, uint p)
{
	return port_chk32(sw, p,
		REG_PORT_WRED_QUEUE_PMON__4, WRED_RANDOM_DROP_ENABLE);
}

static inline int port_chk_wred_drop_gyr(struct ksz_sw *sw, uint p)
{
	return !port_chk32(sw, p,
		REG_PORT_WRED_QUEUE_PMON__4, WRED_DROP_GYR_DISABLE);
}

static inline int port_chk_wred_drop_yr(struct ksz_sw *sw, uint p)
{
	return !port_chk32(sw, p,
		REG_PORT_WRED_QUEUE_PMON__4, WRED_DROP_YR_DISABLE);
}

static inline int port_chk_wred_drop_r(struct ksz_sw *sw, uint p)
{
	return !port_chk32(sw, p,
		REG_PORT_WRED_QUEUE_PMON__4, WRED_DROP_R_DISABLE);
}

static inline int port_chk_wred_drop_all(struct ksz_sw *sw, uint p)
{
	return port_chk32(sw, p,
		REG_PORT_WRED_QUEUE_PMON__4, WRED_DROP_ALL);
}

static u32 port_get_wred_pmon(struct ksz_sw *sw, uint p)
{
	return port_r_s_32(sw, p,
		REG_PORT_WRED_QUEUE_PMON__4, WRED_PMON_M, 0);
}

/* -------------------------------------------------------------------------- */

/* Rate Control */

#ifdef MTI_PREEMPT_ENABLE
static inline void port_cfg_preempt(struct ksz_sw *sw, uint p, uint q, bool set)
{
	port_w32(sw, p, REG_PORT_MTI_QUEUE_INDEX__4, q);
	port_cfg(sw, p,
		REG_PORT_MTI_QUEUE_CTRL_0, MTI_PREEMPT_ENABLE, set);
}

static inline int port_chk_preempt(struct ksz_sw *sw, uint p, uint q)
{
	port_w32(sw, p, REG_PORT_MTI_QUEUE_INDEX__4, q);
	return port_chk(sw, p,
		REG_PORT_MTI_QUEUE_CTRL_0, MTI_PREEMPT_ENABLE);
}
#endif

static inline u8 port_get_schedule_mode(struct ksz_sw *sw, uint p, uint q)
{
	port_w32(sw, p, REG_PORT_MTI_QUEUE_INDEX__4, q);
	return port_r_s(sw, p,
		REG_PORT_MTI_QUEUE_CTRL_0, MTI_SCHEDULE_MODE_M,
			MTI_SCHEDULE_MODE_S);
}

static inline u8 port_get_shaping(struct ksz_sw *sw, uint p, uint q)
{
	port_w32(sw, p, REG_PORT_MTI_QUEUE_INDEX__4, q);
	return port_r_s(sw, p,
		REG_PORT_MTI_QUEUE_CTRL_0, MTI_SHAPING_M,
			MTI_SHAPING_S);
}

static inline u8 port_get_tx_ratio(struct ksz_sw *sw, uint p, uint q)
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
static inline void port_set_schedule_mode(struct ksz_sw *sw, uint p, uint q,
	u8 mode)
{
	port_w32(sw, p, REG_PORT_MTI_QUEUE_INDEX__4, q);
	port_w_s(sw, p,
		REG_PORT_MTI_QUEUE_CTRL_0, MTI_SCHEDULE_MODE_M,
			MTI_SCHEDULE_MODE_S, mode);
}  /* port_set_schedule_mode */

static inline void port_set_shaping(struct ksz_sw *sw, uint p, uint q,
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
static inline void port_set_tx_ratio(struct ksz_sw *sw, uint p, uint q, u8 ratio)
{
	port_w32(sw, p, REG_PORT_MTI_QUEUE_INDEX__4, q);
	port_w(sw, p, REG_PORT_MTI_QUEUE_CTRL_1, ratio & MTI_TX_RATIO_M);
}  /* port_set_tx_ratio */

static u16 port_get_hi_water_mark(struct ksz_sw *sw, uint p, uint q)
{
	u16 data;

	port_w32(sw, p, REG_PORT_MTI_QUEUE_INDEX__4, q);
	port_r16(sw, p, REG_PORT_MTI_QUEUE_CTRL_2__2, &data);
	return data;
}  /* port_get_hi_water_mark */

static u16 port_get_lo_water_mark(struct ksz_sw *sw, uint p, uint q)
{
	u16 data;

	port_w32(sw, p, REG_PORT_MTI_QUEUE_INDEX__4, q);
	port_r16(sw, p, REG_PORT_MTI_QUEUE_CTRL_3__2, &data);
	return data;
}  /* port_get_lo_water_mark */

static u16 port_get_increment(struct ksz_sw *sw, uint p, uint q)
{
	u16 data;

	port_w32(sw, p, REG_PORT_MTI_QUEUE_INDEX__4, q);
	port_r16(sw, p, REG_PORT_MTI_QUEUE_CTRL_4__2, &data);
	return data;
}  /* port_get_increment */

static u8 port_get_srp(struct ksz_sw *sw, uint p)
{
	u8 data;

	port_r(sw, p, REG_PORT_CTRL_1, &data);
	return data & PORT_SRP_ENABLE;
}  /* port_get_srp */

static void port_set_hi_water_mark(struct ksz_sw *sw, uint p, uint q, u16 val)
{
	port_w32(sw, p, REG_PORT_MTI_QUEUE_INDEX__4, q);
	port_w16(sw, p, REG_PORT_MTI_QUEUE_CTRL_2__2, val);
}  /* port_set_hi_water_mark */

static void port_set_lo_water_mark(struct ksz_sw *sw, uint p, uint q, u16 val)
{
	port_w32(sw, p, REG_PORT_MTI_QUEUE_INDEX__4, q);
	port_w16(sw, p, REG_PORT_MTI_QUEUE_CTRL_3__2, val);
}  /* port_set_lo_water_mark */

static void port_set_increment(struct ksz_sw *sw, uint p, uint q, u16 val)
{
	port_w32(sw, p, REG_PORT_MTI_QUEUE_INDEX__4, q);
	port_w16(sw, p, REG_PORT_MTI_QUEUE_CTRL_4__2, val);
}  /* port_set_increment */

static void port_set_srp(struct ksz_sw *sw, uint p, u8 srp)
{
	port_w(sw, p, REG_PORT_CTRL_1, srp & PORT_SRP_ENABLE);
}  /* port_set_srp */

/* -------------------------------------------------------------------------- */

/* Queue Management */

static inline u8 port_get_qm_drop(struct ksz_sw *sw, uint p)
{
	return (u8) port_r_s_32(sw, p, REG_PORT_QM_CTRL__4,
		PORT_QM_DROP_PRIO_M, 0);
}

static u8 port_get_qm_burst_size(struct ksz_sw *sw, uint p)
{
	return (u8) port_r_s_32(sw, p, REG_PORT_QM_QUEUE_INDEX__4,
		3, PORT_QM_BURST_SIZE_S);
}

static u16 port_get_qm_resv_space(struct ksz_sw *sw, uint p)
{
	return (u16) port_r_s_32(sw, p, REG_PORT_QM_QUEUE_INDEX__4,
		PORT_QM_MIN_RESV_SPACE_M, 0);
}

static u16 port_get_qm_hi_water_mark(struct ksz_sw *sw, uint p, uint q)
{
	port_w_s_32(sw, p, REG_PORT_QM_QUEUE_INDEX__4,
		PRIO_QUEUES_M, PORT_QM_QUEUE_INDEX_S, q);
	return (u16) port_r_s_32(sw, p, REG_PORT_QM_WATER_MARK__4,
		PORT_QM_WATER_MARK_M, PORT_QM_HI_WATER_MARK_S);
}

static u16 port_get_qm_lo_water_mark(struct ksz_sw *sw, uint p, uint q)
{
	port_w_s_32(sw, p, REG_PORT_QM_QUEUE_INDEX__4,
		PRIO_QUEUES_M, PORT_QM_QUEUE_INDEX_S, q);
	return (u16) port_r_s_32(sw, p, REG_PORT_QM_WATER_MARK__4,
		PORT_QM_WATER_MARK_M, PORT_QM_LO_WATER_MARK_S);
}

static u16 port_get_qm_tx_used(struct ksz_sw *sw, uint p, uint q)
{
	port_w_s_32(sw, p, REG_PORT_QM_QUEUE_INDEX__4,
		PRIO_QUEUES_M, PORT_QM_QUEUE_INDEX_S, q);
	return (u16) port_r_s_32(sw, p, REG_PORT_QM_TX_CNT_0__4,
		PORT_QM_TX_CNT_M, PORT_QM_TX_CNT_USED_S);
}

static u16 port_get_qm_tx_avail(struct ksz_sw *sw, uint p, uint q)
{
	port_w_s_32(sw, p, REG_PORT_QM_QUEUE_INDEX__4,
		PRIO_QUEUES_M, PORT_QM_QUEUE_INDEX_S, q);
	return (u16) port_r_s_32(sw, p, REG_PORT_QM_TX_CNT_1__4,
		PORT_QM_TX_CNT_M, PORT_QM_TX_CNT_AVAIL_S);
}

static u16 port_get_qm_tx_calculated(struct ksz_sw *sw, uint p, uint q)
{
	port_w_s_32(sw, p, REG_PORT_QM_QUEUE_INDEX__4,
		PRIO_QUEUES_M, PORT_QM_QUEUE_INDEX_S, q);
	return (u16) port_r_s_32(sw, p, REG_PORT_QM_TX_CNT_1__4,
		PORT_QM_TX_CNT_M, PORT_QM_TX_CNT_CALCULATED_S);
}

static inline void port_set_qm_drop(struct ksz_sw *sw, uint p, u8 drop)
{
	port_w_s_32(sw, p, REG_PORT_QM_CTRL__4,
		PORT_QM_DROP_PRIO_M, 0, drop);
}

static inline void port_set_qm_burst_size(struct ksz_sw *sw, uint p, u8 burst)
{
	port_w_s_32(sw, p, REG_PORT_QM_QUEUE_INDEX__4,
		3, PORT_QM_BURST_SIZE_S, burst);
}

static inline void port_set_qm_resv_space(struct ksz_sw *sw, uint p, u16 space)
{
	port_w_s_32(sw, p, REG_PORT_QM_QUEUE_INDEX__4,
		PORT_QM_MIN_RESV_SPACE_M, 0, space);
}

static void port_set_qm_hi_water_mark(struct ksz_sw *sw, uint p, uint q, u16 val)
{
	port_w_s_32(sw, p, REG_PORT_QM_QUEUE_INDEX__4,
		PRIO_QUEUES_M, PORT_QM_QUEUE_INDEX_S, q);
	port_w_s_32(sw, p, REG_PORT_QM_WATER_MARK__4,
		PORT_QM_WATER_MARK_M, PORT_QM_HI_WATER_MARK_S, val);
}

static void port_set_qm_lo_water_mark(struct ksz_sw *sw, uint p, uint q, u16 val)
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
 * DiffServ Value 0 ~ 63 is mapped to Priority Queue Number 0 ~ 7.
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
 * 802.1p Tag priority value 0 ~ 7 is mapped to Priority Queue Number 0 ~ 7.
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
 * @p:		The port index.
 * @set:	The flag to disable or enable.
 *
 * This routine enables the VID to be replaced with port default VID if it is
 * empty.
 */
static void sw_cfg_replace_null_vid(struct ksz_sw *sw, uint p, bool set)
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
	struct ksz_port_cfg *cfg = get_port_cfg(sw, port);

	if (prio > PORT_BASED_PRIO_M)
		prio = PORT_BASED_PRIO_M;

	port_r(sw, port, REG_PORT_MRI_MAC_CTRL, &data);
	data &= ~(PORT_BASED_PRIO_M << PORT_BASED_PRIO_S);
	data |= prio << PORT_BASED_PRIO_S;
	port_w(sw, port, REG_PORT_MRI_MAC_CTRL, data);

	cfg->port_prio = prio;
}  /* sw_cfg_port_based */

/* -------------------------------------------------------------------------- */

/**
 * sw_set_multi_queue - enable transmit multiple queues
 * @sw:		The switch instance.
 * @port:	The port index.
 * @queue:	The queue register setting.
 *
 * This routine enables the transmit multiple queues selection of the switch
 * port.  The port transmit queue is split into two or four priority queues.
 */
static void sw_set_multi_queue(struct ksz_sw *sw, uint port, uint queue)
{
	port_set_prio_queue(sw, port, queue);

	/* Default is port based for egress rate limit. */
	if (queue)
		sw_cfg(sw, REG_SW_MAC_CTRL_5, SW_OUT_RATE_LIMIT_QUEUE_BASED,
			1);
}  /* sw_set_multi_queue */

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
	int tos;
	SW_D data;
	struct ksz_port_cfg *port_cfg;

	for (tos = 0; tos < PRIO_802_1P_ENTRIES / KS_PRIO_IN_REG; tos++)
		sw->info->p_802_1p[tos] =
			SW_R(sw, S_802_1P_PRIO_CTRL + tos * SW_SIZE);

	for (tos = 0; tos < DIFFSERV_ENTRIES / KS_PRIO_IN_REG; tos++)
		sw->info->diffserv[tos] =
			SW_R(sw, S_TOS_PRIO_CTRL + tos * SW_SIZE);

	for (n = 0; n <= sw->mib_port_cnt; n++) {
		port = get_phy_port(sw, n);
		port_cfg = get_port_cfg(sw, port);
		port_r(sw, port, REG_PORT_MRI_MAC_CTRL, &data);
		data &= PORT_BASED_PRIO_M;
		port_cfg->port_prio = data;
		for (tos = 0; tos < PRIO_802_1P_ENTRIES / 8; tos++)
			port_r32(sw, port, REG_PORT_MRI_TC_MAP__4 - tos * 4,
				&port_cfg->tc_map[tos]);

		for (tos = 0; tos < DIFFSERV_ENTRIES / 16; tos++)
			port_r32(sw, port, REG_PORT_POLICE_COLOR_3__4 -
				tos * 4, &port_cfg->color_map[tos]);
	}
}  /* sw_init_prio */

static void port_set_color_map(struct ksz_sw *sw, uint port, u8 tos, u32 prio)
{
	port_w32(sw, port, REG_PORT_POLICE_COLOR_3__4 - tos * 4, prio);
}  /* port_set_color_map */

static void port_set_tc_map(struct ksz_sw *sw, uint port, u8 tos, u32 prio)
{
	port_w32(sw, port, REG_PORT_MRI_TC_MAP__4 + tos * 4, prio);
}  /* port_set_color_map */

/**
 * port_cfg_color_map - configure port police color map
 * @sw:		The switch instance.
 * @tos:	ToS value.
 * @prio:	Priority to be assigned.
 *
 * This routine configures the color map in the hardware.
 */
static void port_cfg_color_map(struct ksz_sw *sw, uint port, u8 tos, u32 prio)
{
	int shift;
	u32 data = prio;
	u32 mask = POLICE_COLOR_MAP_M;
	struct ksz_port_cfg *port_cfg = get_port_cfg(sw, port);

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
 * @tc:		Traffic class.
 * @prio:	Priority to be assigned.
 *
 * This routine configures the traffic class mapping in the hardware.
 */
static void port_cfg_tc_map(struct ksz_sw *sw, uint port, u8 tc, u32 prio)
{
	int shift;
	u32 data = prio;
	u32 mask = PORT_TC_MAP_M;
	u32 regmask = PORT_TC_MAP_M;
	struct ksz_port_cfg *port_cfg = get_port_cfg(sw, port);

	if (tc >= PRIO_802_1P_ENTRIES)
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
	shift = (tc & (8 - 1)) * PORT_TC_MAP_S;
	prio = prio << shift;
	if (prio >> shift != data)
		return;
	mask <<= shift;
	regmask <<= shift;
	prio &= regmask;
	tc /= 8;

	port_cfg->tc_map[tc] &= ~mask;
	port_cfg->tc_map[tc] |= prio;

	port_set_tc_map(sw, port, tc, port_cfg->tc_map[tc]);
}  /* port_cfg_tc_map */

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
	uint q;
	struct ksz_port_cfg *cfg;

	/* All QoS functions disabled. */
	for (n = 0; n <= sw->mib_port_cnt; n++) {
		port = get_phy_port(sw, n);
		cfg = get_port_cfg(sw, port);

		sw_set_multi_queue(sw, port, 2);
		sw_dis_diffserv(sw, port);
		sw_cfg_replace_prio(sw, port, 0);
		sw_cfg_replace_null_vid(sw, port, 0);
		sw_cfg_port_based(sw, port, cfg->port_prio);

		sw_ena_802_1p(sw, port);
		for (q = 0; q < PRIO_QUEUES; q++)
			port_set_tx_ratio(sw, port, q, 1 << q);
		if (sw->features & AVB_SUPPORT) {
			cfg->tc_map[0] = 0x11113200;
			port_set_tc_map(sw, port, 0, cfg->tc_map[0]);
			cfg->port_prio = 4;
			sw_cfg_port_based(sw, port, cfg->port_prio);
		}
		sw->reg->w8(sw, REG_PTP_EVENT_PRIO_CTRL, PTP_PRIO_ENABLE | 7);
		sw->reg->w8(sw, REG_PTP_GENERAL_PRIO_CTRL, PTP_PRIO_ENABLE | 7);
	}
	sw->ctrl_queue = (1 << 2) - 1;
	if (sw->features & AVB_SUPPORT)
		sw->ctrl_queue = 1;
#ifdef CONFIG_MACB_
	/* Atmel MAC has problem receiving larger traffic. */
	for (q = 0; q < PRIO_QUEUES; q++)
		hw_cfg_tx_prio_rate(sw, sw->HOST_PORT, q, 380000);
#endif
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
static void port_get_def_vid(struct ksz_sw *sw, uint port, u16 *vid)
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
static void sw_cfg_def_vid(struct ksz_sw *sw, uint port, u16 vid)
{
	struct ksz_port_cfg *cfg = get_port_cfg(sw, port);

	cfg->vid = vid;
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
static void sw_cfg_port_base_vlan(struct ksz_sw *sw, uint port, u16 member)
{
	struct ksz_port_cfg *cfg = get_port_cfg(sw, port);

	cfg->member = member;
	port_w32(sw, port, REG_PORT_VLAN_MEMBERSHIP__4, member);
}  /* sw_cfg_port_base_vlan */

static void sw_cfg_default_vlan(struct ksz_sw *sw, int reset)
{
	struct ksz_vlan_table vlan;

	if (sw->overrides & VLAN_SET)
		return;
	sw->ops->release(sw);
	vlan.vid = 1;
	sw_r_vlan_table(sw, vlan.vid, &vlan);
	vlan.ports = sw->PORT_MASK;
	if (reset)
		vlan.untag = 0;
	else
		vlan.untag = vlan.ports;
	vlan.valid = vlan.ports != 0;
	sw_w_vlan_table(sw, vlan.vid, &vlan);
	if (!reset) {
		vlan.vid = 0;
		vlan.ports = sw->PORT_MASK;
		vlan.untag = 0;
		vlan.valid = 1;
		sw_w_vlan_table(sw, vlan.vid, &vlan);
	}
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
	uint n;
	uint p;
	u32 val;

	/* Hardware may remove priority tag with VID 0. */
	for (n = 0; n <= sw->mib_port_cnt; n++) {
		p = get_phy_port(sw, n);
		port_cfg(sw, p, REG_PORT_LUE_CTRL, PORT_VLAN_LOOKUP_VID_0,
			true);
	}
	sw_cfg_default_vlan(sw, false);

	/* Enable 802.1q VLAN mode. */
	val = sw->reg->r32(sw, REG_SW_QM_CTRL__4);
	val |= UNICAST_VLAN_BOUNDARY;
	sw->reg->w32(sw, REG_SW_QM_CTRL__4, val);
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
	uint n;
	uint port;
	u32 data;
	struct ksz_port_cfg *cfg;

	for (n = 0; n <= sw->mib_port_cnt; n++) {
		port = get_phy_port(sw, n);
		cfg = get_port_cfg(sw, port);
		port_get_def_vid(sw, port, &cfg->vid);
		port_r32(sw, port, REG_PORT_VLAN_MEMBERSHIP__4, &data);
		cfg->member = (u16) data;
		cfg->vid_member = (u16) data;
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
	uint i;
	uint n;
	struct ksz_port_info *info;

	for (n = 0; n <= sw->mib_port_cnt; n++) {
		i = get_phy_port(sw, n);
		info = get_port_info(sw, i);
		inc_mac_addr(info->mac_addr, mac_addr, n);
	}
	sw->reg->w(sw, REG_SW_MAC_ADDR_0, mac_addr, 6);
	memcpy(sw->info->mac_addr, mac_addr, 6);
#ifdef CONFIG_KSZ_IBA
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
	bool update;

	memset(table, 0, sizeof(struct ksz_mac_table) * 8);
	for (i = 0; i < 8; i++)
		addr[i] = get_mcast_reserved_addr(i);

	sw_r_m_sta_mac_table(sw, addr, 1, 8, table);
	update = table[6].ports != sw->HOST_MASK ||
		 sw->PORT_MASK != (1 << sw->port_cnt) - 1 ||
		 (sw->features & MRP_SUPPORT);
	if (update) {
		for (i = 0; i < 8; i++)
			ctrl[i] = get_mac_table_ctrl(addr[i], true);
#if 0
		table[0].override = true;
		table[0].ports = sw->HOST_MASK;
#endif
		table[1].ports = 0;
		table[2].override = true;
		table[2].ports = sw->HOST_MASK;
		table[3].ports = sw->PORT_MASK;
		if (sw->features & MRP_SUPPORT) {
#ifdef MRP_PASSTHRU
			table[4].ports = sw->PORT_MASK;
			table[5].ports = sw->PORT_MASK;
#else
			table[4].override = true;
			table[4].ports = sw->HOST_MASK;
			table[5].override = true;
			table[5].ports = sw->HOST_MASK;
#endif
		} else {
			table[4].ports = sw->PORT_MASK;
			table[5].ports = sw->PORT_MASK;
		}
#ifdef MRP_PASSTHRU
		table[6].ports = sw->PORT_MASK;
#else
		table[6].override = true;
		table[6].ports = sw->HOST_MASK;
#endif
		table[7].ports = sw->PORT_MASK & ~sw->HOST_MASK;
		sw_w_m_sta_mac_table(sw, addr, true, 8, table);
	}
}  /* sw_setup_reserved_multicast */

static int sw_get_gbit(struct ksz_sw *sw, u8 data)
{
	int gbit;

	if (sw->features & NEW_XMII)
		gbit = !(data & PORT_MII_NOT_1GBIT);
	else
		gbit = data & PORT_MII_1000MBIT_S1;
	return gbit;
}  /* sw_get_gbit */

static void sw_set_gbit(struct ksz_sw *sw, int gbit, u8 *data)
{
	if (sw->features & NEW_XMII) {
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

	if (sw->features & NEW_XMII) {
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

	if (sw->features & NEW_XMII) {
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

#ifdef CONFIG_KSZ_MRP
#include "ksz_mrp.c"
#endif

#define STP_ENTRY			(MULTI_MAC_TABLE_ENTRIES - 2)
#define DEV_0_ADDR_ENTRY		0
#define DEV_1_ADDR_ENTRY		1
#define BRIDGE_ADDR_ENTRY		2

/**
 * sw_set_global_ctrl - set switch global control
 * @sw:		The switch instance.
 *
 * This routine sets the global control of the switch function.
 */
static void sw_set_global_ctrl(struct ksz_sw *sw)
{
	SW_D data;
	int setup_xmii = sw->HOST_PORT >= sw->phy_port_cnt;

#ifdef CONFIG_KSZ_IBA
	if (2 <= sw->info->iba.use_iba)
		setup_xmii = 0;
#endif
	if (setup_xmii) {
		struct phy_device *phydev = sw->phy[0];
		struct ksz_port_info *info = get_port_info(sw, sw->HOST_PORT);
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
		if (sw->netdev[0]) {
			struct ksz_port *sw_port = sw->netport[0];

			if (sw_port->flow_ctrl == PHY_NO_FLOW_CTRL) {
				if (sw->features & IS_9893) {
					port_cfg_force_flow_ctrl(sw,
						sw->HOST_PORT, 0);
				} else {
					port_r(sw, sw->HOST_PORT,
						REG_PORT_XMII_CTRL_0, &data);
					data &= ~(PORT_MII_TX_FLOW_CTRL |
						  PORT_MII_RX_FLOW_CTRL);
					port_w(sw, sw->HOST_PORT,
						REG_PORT_XMII_CTRL_0, data);
				}
			} else {
				if (sw->features & IS_9893) {
					port_cfg_force_flow_ctrl(sw,
						sw->HOST_PORT, 1);
				} else {
					port_r(sw, sw->HOST_PORT,
						REG_PORT_XMII_CTRL_0, &data);
					data |= (PORT_MII_TX_FLOW_CTRL |
						 PORT_MII_RX_FLOW_CTRL);
					port_w(sw, sw->HOST_PORT,
						REG_PORT_XMII_CTRL_0, data);
				}
			}
		}
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
			if (phydev->speed > SPEED_100)
				phydev->speed = SPEED_100;
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
		sw->cached.xmii[sw->HOST_PORT - sw->phy_port_cnt] &= ~0xff;
		sw->cached.xmii[sw->HOST_PORT - sw->phy_port_cnt] |= data;
dbg_msg(" cached: %02x\n", sw->cached.xmii[sw->HOST_PORT - sw->phy_port_cnt]);
	}

	data = SW_R(sw, REG_SW_MAC_CTRL_0);

	/* Enable aggressive back off algorithm in half duplex mode. */
	data |= SW_AGGR_BACKOFF;

/*
 * THa  2016/10/17
 * If no excessive collision drop is enabled the default backoff algorithm
 * may cause both linked device to stop passing traffic completely.
 */
	data |= SW_NEW_BACKOFF;

/*
 * THa  2016/10/17
 * Recommended to turn on this mode to pass UNH tests.
 */
	data |= SW_PAUSE_UNH_MODE;
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

#ifdef IMX6_KSZ9567
	/* SPI access becomes more stable. */
	data = SW_R(sw, REG_SW_GLOBAL_OUTPUT_CTRL__1);
	data |= SW_REFCLKO_IS_125MHZ;
	SW_W(sw, REG_SW_GLOBAL_OUTPUT_CTRL__1, data);

	data = SW_R(sw, REG_SW_IO_STRENGTH__1);
	data &= ~(SW_DRIVE_STRENGTH_M << SW_HI_SPEED_DRIVE_STRENGTH_S);
	data |= SW_DRIVE_STRENGTH_16MA << SW_HI_SPEED_DRIVE_STRENGTH_S;
	SW_W(sw, REG_SW_IO_STRENGTH__1, data);
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
static void port_set_stp_state(struct ksz_sw *sw, uint port, int state)
{
	SW_D data;
	struct ksz_port_cfg *cfg = get_port_cfg(sw, port);
	uint m = BIT(port);
	int member = -1;

#if 0
dbg_msg("%s %d %d\n", __func__, port, state);
#endif
	port_r(sw, port, P_STP_CTRL, &data);
	switch (state) {
	case STP_STATE_DISABLED:
		data &= ~(PORT_TX_ENABLE | PORT_RX_ENABLE);
		data |= PORT_LEARN_DISABLE;
		if (port != sw->HOST_PORT)
			member = 0;
		break;
	case STP_STATE_LISTENING:
/* No need to turn on transmit because of port direct mode.
 * Turning on receive is required if static MAC table is not setup.
 */
		data &= ~PORT_TX_ENABLE;
		data |= PORT_RX_ENABLE;
		data |= PORT_LEARN_DISABLE;
		if (port != sw->HOST_PORT &&
		    STP_STATE_DISABLED == cfg->stp_state[cfg->mstp])
			member = sw->HOST_MASK | cfg->vid_member;
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
			member = sw->HOST_MASK | cfg->vid_member;
		break;
	case STP_STATE_BLOCKED:
/*
 * Need to setup static MAC table with override to keep receiving BPDU
 * messages.  See sw_setup_stp routine.
 */
		data &= ~(PORT_TX_ENABLE | PORT_RX_ENABLE);
		data |= PORT_LEARN_DISABLE;
		if (port != sw->HOST_PORT &&
		    STP_STATE_DISABLED == cfg->stp_state[cfg->mstp])
			member = sw->HOST_MASK | cfg->vid_member;
		break;
	case STP_STATE_SIMPLE:
		data |= (PORT_TX_ENABLE | PORT_RX_ENABLE);
		data |= PORT_LEARN_DISABLE;
		if (port != sw->HOST_PORT)
			/* Set port-base vlan membership with host port. */
			member = sw->HOST_MASK | cfg->vid_member;
		break;
	}
	port_w(sw, port, P_STP_CTRL, data);
	cfg->stp_state[cfg->mstp] = state;
	if (data & PORT_RX_ENABLE)
		sw->rx_ports[cfg->mstp] |= m;
	else
		sw->rx_ports[cfg->mstp] &= ~m;
	if (data & PORT_TX_ENABLE)
		sw->tx_ports[cfg->mstp] |= m;
	else
		sw->tx_ports[cfg->mstp] &= ~m;

	/* Port membership may share register with STP state. */
	if (member >= 0)
		sw_cfg_port_base_vlan(sw, port, (u8) member);
}  /* port_set_stp_state */

static void port_open(struct ksz_sw *sw, uint p, bool open)
{
	int acl_on;
	uint n;
	uint q;
	u8 acl_rule;
	u8 map_mode;
	u8 member;
	u16 ruleset;
	struct ksz_acl_table *acl;

dbg_msg("%s %d %d\n", __func__, p, open);
	acl_rule = 1;
	if (open) {
		sw->on_ports |= (1 << p);
		map_mode = 0;
		ruleset = 0;
	} else {
		sw->on_ports &= ~(1 << p);
		map_mode = ACL_MAP_MODE_REPLACE;
		ruleset = (1 << acl_rule);
	}
	acl_on = port_chk_acl(sw, p);
	if (!acl_on)
		port_cfg_acl(sw, p, true);
	sw->ops->release(sw);
	acl = &sw->info->port_cfg[p].acl_info[acl_rule];
	acl->map_mode = map_mode;
	acl->ruleset = ruleset;
	sw_w_acl_table(sw, p, acl_rule, acl);
	++acl_rule;
	acl = &sw->info->port_cfg[p].acl_info[acl_rule];
	if (ruleset)
		ruleset = (1 << acl_rule);
	acl->ruleset = ruleset;
	sw_w_acl_table(sw, p, acl_rule, acl);
	sw->ops->acquire(sw);
	if (!acl_on)
		port_cfg_acl(sw, p, false);
	for (n = 1; n <= sw->mib_port_cnt; n++) {
		q = get_phy_port(sw, n);
		if (sw->on_ports & (1 << q))
			member = (u8)(sw->HOST_MASK | sw->on_ports);
		else
			member = sw->HOST_MASK;
		if (sw->info->port_cfg[q].member != member)
			sw_cfg_port_base_vlan(sw, q, member);
	}
}  /* port_open */

static void sw_setup_acl(struct ksz_sw *sw)
{
	struct ksz_acl_table *acl;
	int acl_on;
	uint n;
	uint port;
	u8 first_rule;
	u8 acl_rule;

	if (!(sw->overrides & USE_802_1X_AUTH))
		return;
	for (n = 1; n <= sw->mib_port_cnt; n++) {
		port = get_phy_port(sw, n);
		port_set_authen_mode(sw, port, PORT_AUTHEN_BLOCK);
		sw_cfg_port_base_vlan(sw, port, sw->HOST_MASK);

		acl_on = port_chk_acl(sw, port);
		if (!acl_on)
			port_cfg_acl(sw, port, true);

		first_rule = 0;
		acl_rule = 0;
		acl = &sw->info->port_cfg[port].acl_info[acl_rule];
		acl->mac[0] = 0x01;
		acl->mac[1] = 0x80;
		acl->mac[2] = 0xC2;
		acl->mac[3] = 0x00;
		acl->mac[4] = 0x00;
		acl->mac[5] = 0x03;
		acl->eth_type = ETH_P_PAE;
		acl->src = 0;
		acl->equal = 1;
		acl->enable = ACL_ENABLE_2_BOTH;
		acl->mode = ACL_MODE_LAYER_2;
		acl->ruleset = (1 << acl_rule);
		acl->first_rule = first_rule;
		acl->map_mode = 0;
		acl->ports = 0;
		sw->ops->release(sw);
		sw_w_acl_table(sw, port, acl_rule, acl);
		sw->ops->acquire(sw);

		first_rule = 1;
		acl_rule++;
		acl++;
		acl->src = 0;
		acl->min_port = 1645;
		acl->max_port = 1812;
		acl->port_mode = ACL_PORT_MODE_EITHER;
		acl->enable = ACL_ENABLE_4_UDP_PORT_COMP;
		acl->mode = ACL_MODE_LAYER_4;
		acl->ruleset = (1 << acl_rule);
		acl->first_rule = first_rule;
		acl->map_mode = ACL_MAP_MODE_REPLACE;
		acl->ports = sw->HOST_MASK;
		sw->ops->release(sw);
		sw_w_acl_table(sw, port, acl_rule, acl);
		sw->ops->acquire(sw);
		acl_rule++;
		acl++;
		acl->eth_type = ETH_P_ARP;
		acl->equal = 1;
		acl->enable = ACL_ENABLE_2_TYPE;
		acl->mode = ACL_MODE_LAYER_2;
		acl->ruleset = (1 << acl_rule);
		acl->first_rule = first_rule;
		sw->ops->release(sw);
		sw_w_acl_table(sw, port, acl_rule, acl);
		sw->ops->acquire(sw);
		if (!acl_on)
			port_cfg_acl(sw, port, false);
	}
}  /* sw_setup_acl */

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

#ifdef CONFIG_KSZ_STP
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
	if (sw->stp) {
		entry->ports = sw->HOST_MASK;
		entry->override = 1;
	} else {
		entry->ports = sw->PORT_MASK & ~sw->HOST_MASK;
	}
	entry->valid = 1;
	alu = &info->alu_table[STP_ENTRY];
	alu->index = 0;
	alu->type = 1;
	alu->owner = 1;
	alu->valid = 1;
	if (sw->stp)
		alu->forward = FWD_STP_DEV | FWD_HOST | FWD_HOST_OVERRIDE;
	sw->ops->release(sw);
	sw_w_sta_mac_table(sw, alu->index, alu->type, entry);
	sw->ops->acquire(sw);
}  /* sw_setup_stp */
#endif

static void sw_set_mcast_table(struct ksz_sw *sw, int i, const u8 *addr)
{
	struct ksz_mac_table *entry;
	struct ksz_alu_table *alu;

	entry = &sw->info->mac_table[i];
	alu = &sw->info->alu_table[i];
	memcpy(entry->addr, addr, ETH_ALEN);
	entry->fid = 0;
	entry->ports = sw->PORT_MASK;
	entry->valid = 1;
	alu = &sw->info->alu_table[i];
	alu->forward = FWD_MAIN_DEV | FWD_MCAST | FWD_KNOWN;
	alu->owner = 1;
	alu->valid = 1;
	alu->index = 0;
	alu->type = 2;
	sw_w_dyn_mac_table(sw, 0, entry->addr, entry->fid, entry);
}  /* sw_set_mcast_table */

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

#if 1
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
#endif
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

static const u8 ipv6_neigh_mcast[] = {
	0x33, 0x33, 0xFF,
};

static const u8 known_mcast_addr[][ETH_ALEN] = {
	/* IGMP V2 */
	{ 0x01, 0x00, 0x5E, 0x00, 0x00, 0x01 },
	{ 0x33, 0x33, 0x00, 0x00, 0x00, 0x01 },
	{ 0x01, 0x00, 0x5E, 0x00, 0x00, 0x02 },

	/* ICMPv6 */
	{ 0x33, 0x33, 0x00, 0x00, 0x00, 0x02 },

	/* IGMP V3 */
	{ 0x01, 0x00, 0x5E, 0x00, 0x00, 0x16 },
	{ 0x33, 0x33, 0x00, 0x00, 0x00, 0x16 },

	{ 0x01, 0x00, 0x5E, 0x00, 0x00, 0xFB },
	{ 0x33, 0x33, 0x00, 0x00, 0x00, 0xFB },

	/* Link-Local Multicast Name Resolution */
	{ 0x01, 0x00, 0x5E, 0x00, 0x00, 0xFC },
	{ 0x33, 0x33, 0x00, 0x01, 0x00, 0x03 },

	/* Simple Service Discovery Protocol */
	{ 0x01, 0x00, 0x5E, 0x7F, 0xFF, 0xFA },
	{ 0x33, 0x33, 0x00, 0x00, 0x00, 0x0C },

	{ 0x33, 0x33, 0x00, 0x01, 0x00, 0x02 },
};

static void sw_setup_multi(struct ksz_sw *sw)
{
	struct ksz_mac_table *entry;
	struct ksz_alu_table *alu;
	int i;
	int n;
	u8 forward;
	u8 addr[ETH_ALEN];
	struct ksz_sw_info *info = sw->info;

	sw->ops->release(sw);
	i = info->multi_sys;
	forward = FWD_HOST;

	addr[0] = 0x01;
	addr[1] = 0x80;
	addr[2] = 0xC2;
	addr[3] = 0x00;
	addr[4] = 0x00;
	addr[5] = 0x00;

	entry = &info->mac_table[--i];
	memset(entry->addr, 0xFF, ETH_ALEN);
	entry->ports = sw->PORT_MASK;
	entry->fid = 0;
	alu = &info->alu_table[i];
	alu->forward = FWD_MAIN_DEV | FWD_MCAST | FWD_KNOWN;
	alu->owner = sw->PORT_MASK;
	alu->valid = 1;
	alu->index = 0;
	alu->type = 2;
#if 0
	if (sw->features & DLR_HW) {
		entry->ports = sw->HOST_MASK;
		alu->forward |= FWD_HOST;
	}
#endif

	i = STP_ENTRY;

#if 1
	entry = &info->mac_table[--i];
	memcpy(entry->addr, addr, ETH_ALEN);
	entry->addr[5] = 0x01;
	entry->ports = sw->HOST_MASK;
	alu = &info->alu_table[i];
	alu->forward = forward;
	alu->owner = 1;
	alu->valid = 1;
	alu->index = 0;
	alu->type = 1;
#endif

	entry = &info->mac_table[--i];
	memcpy(entry->addr, addr, ETH_ALEN);
	entry->addr[5] = 0x02;
	entry->ports = sw->HOST_MASK;
	alu = &info->alu_table[i];
	alu->forward = forward;
	alu->owner = 1;
	alu->valid = 1;
	alu->index = 0;
	alu->type = 1;

	entry = &info->mac_table[--i];
	memcpy(entry->addr, addr, ETH_ALEN);
	entry->addr[5] = 0x03;
	entry->ports = sw->HOST_MASK;
	alu = &info->alu_table[i];
	alu->forward = forward;
	alu->owner = 1;
	alu->valid = 1;
	alu->index = 0;
	alu->type = 1;

	entry = &info->mac_table[--i];
	memcpy(entry->addr, addr, ETH_ALEN);
	entry->addr[5] = 0x04;
	entry->ports = sw->HOST_MASK;
	alu = &info->alu_table[i];
	alu->forward = forward;
	alu->owner = 1;
	alu->valid = 1;
	alu->index = 0;
	alu->type = 1;

	entry = &info->mac_table[--i];
	memcpy(entry->addr, addr, ETH_ALEN);
	entry->addr[5] = 0x05;
	entry->ports = sw->HOST_MASK;
	alu = &info->alu_table[i];
	alu->forward = forward;
	alu->owner = 1;
	alu->valid = 1;
	alu->index = 0;
	alu->type = 1;

	entry = &info->mac_table[--i];
	memcpy(entry->addr, addr, ETH_ALEN);
	entry->addr[5] = 0x06;
	entry->ports = sw->HOST_MASK;
	alu = &info->alu_table[i];
	alu->forward = forward;
	alu->owner = 1;
	alu->valid = 1;
	alu->index = 0;
	alu->type = 1;

	entry = &info->mac_table[--i];
	memcpy(entry->addr, addr, ETH_ALEN);
	entry->addr[5] = 0x07;
	entry->ports = sw->HOST_MASK;
	alu = &info->alu_table[i];
	alu->forward = forward;
	alu->owner = 1;
	alu->valid = 1;
	alu->index = 0;
	alu->type = 1;

	entry = &info->mac_table[--i];
	memcpy(entry->addr, addr, ETH_ALEN);
	entry->addr[5] = 0x08;
	entry->ports = sw->HOST_MASK;
	alu = &info->alu_table[i];
	alu->forward = forward;
	alu->owner = 1;
	alu->valid = 1;
	alu->index = 0;
	alu->type = 1;

	entry = &info->mac_table[--i];
	memcpy(entry->addr, addr, ETH_ALEN);
	entry->addr[5] = 0x09;
	entry->ports = sw->HOST_MASK;
	alu = &info->alu_table[i];
	alu->forward = forward;
	alu->owner = 1;
	alu->valid = 1;
	alu->index = 0;
	alu->type = 1;

	entry = &info->mac_table[--i];
	memcpy(entry->addr, addr, ETH_ALEN);
	entry->addr[5] = 0x0A;
	entry->ports = sw->HOST_MASK;
	alu = &info->alu_table[i];
	alu->forward = forward;
	alu->owner = 1;
	alu->valid = 1;
	alu->index = 0;
	alu->type = 1;

	entry = &info->mac_table[--i];
	memcpy(entry->addr, addr, ETH_ALEN);
	entry->addr[5] = 0x0B;
	entry->ports = sw->HOST_MASK;
	alu = &info->alu_table[i];
	alu->forward = forward;
	alu->owner = 1;
	alu->valid = 1;
	alu->index = 0;
	alu->type = 1;

	entry = &info->mac_table[--i];
	memcpy(entry->addr, addr, ETH_ALEN);
	entry->addr[5] = 0x0C;
	entry->ports = sw->HOST_MASK;
	alu = &info->alu_table[i];
	alu->forward = forward;
	alu->owner = 1;
	alu->valid = 1;
	alu->index = 0;
	alu->type = 1;

	entry = &info->mac_table[--i];
	memcpy(entry->addr, addr, ETH_ALEN);
	entry->addr[5] = 0x0D;
	entry->ports = sw->HOST_MASK;
	alu = &info->alu_table[i];
	alu->forward = forward;
	alu->owner = 1;
	alu->valid = 1;
	alu->index = 0;
	alu->type = 1;

	entry = &info->mac_table[--i];
	memcpy(entry->addr, addr, ETH_ALEN);
	entry->addr[5] = 0x0E;
	entry->ports = sw->HOST_MASK;
#ifdef CONFIG_1588_PTP
	entry->override = 1;
	alu = &info->alu_table[i];
	alu->forward = forward | FWD_HOST_OVERRIDE;
#else
	alu = &info->alu_table[i];
	alu->forward = forward;
#endif
	alu->owner = 1;
	alu->valid = 1;
	alu->index = 0;
	alu->type = 1;

	entry = &info->mac_table[--i];
	memcpy(entry->addr, addr, ETH_ALEN);
	entry->addr[5] = 0x0F;
	entry->ports = sw->HOST_MASK;
	alu = &info->alu_table[i];
	alu->forward = forward;
	alu->owner = 1;
	alu->valid = 1;
	alu->index = 0;
	alu->type = 1;

	entry = &info->mac_table[--i];
	memcpy(entry->addr, addr, ETH_ALEN);
	entry->addr[5] = 0x20;
	entry->ports = sw->HOST_MASK;
	alu = &info->alu_table[i];
	alu->forward = forward;
	alu->owner = 1;
	alu->valid = 1;
	alu->index = 0;
	alu->type = 1;

	entry = &info->mac_table[--i];
	memcpy(entry->addr, addr, ETH_ALEN);
	entry->addr[5] = 0x21;
	entry->ports = sw->HOST_MASK;
	alu = &info->alu_table[i];
	alu->forward = forward;
	alu->owner = 1;
	alu->valid = 1;
	alu->index = 0;
	alu->type = 1;

	forward = FWD_MAIN_DEV;
	forward |= FWD_MCAST | FWD_KNOWN;

	entry = &info->mac_table[--i];
	memcpy(entry->addr, addr, ETH_ALEN);
	entry->addr[5] = 0x10;
	entry->ports = sw->PORT_MASK;
	alu = &info->alu_table[i];
	alu->forward = forward;
	alu->owner = 1;
	alu->valid = 1;
	alu->index = 0;
	alu->type = 1;

	for (n = 0; n < 13; n++) {
		--i;
		sw_set_mcast_table(sw, i, known_mcast_addr[n]);
	}

	sw->ops->acquire(sw);
	info->multi_sys = i;
}  /* sw_setup_multi */

#ifdef CONFIG_KSZ_STP
static void bridge_change(struct ksz_sw *sw)
{
	int i;
	uint n;
	uint port;
	u8 m;
	u8 member;
	struct ksz_port_cfg *cfg;

	for (n = 1; n <= sw->mib_port_cnt; n++) {
		port = get_phy_port(sw, n);
		cfg = get_port_cfg(sw, port);
		member = 0;
		for (i = 0; i < NUM_OF_MSTI; i++) {
			if (STP_STATE_FORWARDING == cfg->stp_state[i])
				m = sw->HOST_MASK | sw->info->member[i];
			else if (STP_STATE_DISABLED == cfg->stp_state[i])
				m = 0;
			else
				m = sw->HOST_MASK | (1 << port);
			member |= m;
		}
		if (member != cfg->member)
			sw_cfg_port_base_vlan(sw, port, member);
	}
}  /* bridge_change */
#endif

static int sw_match_multi(struct ksz_sw *sw, struct ksz_port *priv, u8 *addr)
{
	struct ksz_mac_table *entry;
	struct ksz_alu_table *alu;
	int i;
	int owner;
	uint port = 0;
	struct ksz_sw_info *info = sw->info;

	if (priv->port_cnt != sw->mib_port_cnt)
		port = priv->first_port;
#if 0
dbg_msg("%s %d %d\n", __func__, priv->port_cnt, port);
#endif
	owner = 1 << port;

	for (i = SWITCH_MAC_TABLE_ENTRIES; i < info->multi_net; i++) {
		entry = &info->mac_table[i];
		alu = &info->alu_table[i];
		if (alu->valid && (alu->owner & owner) &&
		    !memcmp(addr, entry->addr, ETH_ALEN))
			return false;
	}
	for (i = info->multi_sys; i < MULTI_MAC_TABLE_ENTRIES; i++) {
		entry = &info->mac_table[i];
		alu = &info->alu_table[i];
		if (alu->valid && !memcmp(addr, entry->addr, ETH_ALEN))
			return false;
	}
	return true;
}  /* sw_match_multi */

static void sw_set_multi(struct ksz_sw *sw, struct net_device *dev,
	struct ksz_port *priv)
{
	struct ksz_mac_table *entry;
	struct ksz_alu_table *alu;
	struct netdev_hw_addr *ha;
	int i;
	int found;
	int owner;
	uint port = 0;
	struct ksz_sw_info *info = sw->info;

	if (priv->port_cnt != sw->mib_port_cnt)
		port = priv->first_port;
#if 0
dbg_msg("%s %d %d\n", __func__, priv->port_cnt, port);
#endif
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

static void sw_reset_multi(struct ksz_sw *sw, struct ksz_port *priv)
{
	struct ksz_mac_table *entry;
	struct ksz_alu_table *alu;
	int i;
	int owner;
	uint port = 0;
	struct ksz_sw_info *info = sw->info;

	if (priv->port_cnt != sw->mib_port_cnt)
		port = priv->first_port;
	owner = 1 << port;

	for (i = SWITCH_MAC_TABLE_ENTRIES; i < info->multi_net; i++) {
		entry = &info->mac_table[i];
		alu = &info->alu_table[i];
		if (alu->valid && (alu->owner & owner)) {
			alu->owner &= ~owner;
			if (!alu->owner) {
				alu->valid = 0;
				entry->valid = 0;
			}
		}
	}
}  /* sw_reset_multi */

static void sw_reset_setup(struct ksz_sw *sw)
{
	struct ksz_mac_table *entry;
	struct ksz_alu_table *alu;
	int i;
	struct ksz_sw_info *info = sw->info;

	for (i = 0; i < MULTI_MAC_TABLE_ENTRIES; i++) {
		entry = &info->mac_table[i];
		alu = &info->alu_table[i];
		if (alu->valid) {
			alu->owner = 0;
			alu->valid = 0;
			entry->valid = 0;
		}
	}
	for (i = 0; i < sw->port_cnt; i++)
		sw->info->port_cfg[i].mstp = 0;
}  /* sw_reset_setup */

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

#ifdef CONFIG_KSZ_MSTP
#include "ksz_mstp.c"
#elif defined(CONFIG_KSZ_STP)
#define HAVE_VID2FID
#include "ksz_stp.c"
#endif
#ifdef CONFIG_KSZ_DLR
#include "ksz_dlr.c"
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
	uint i;
	uint n;
	uint p;

	for (i = 0, n = port->first_port; i < port->port_cnt; i++, n++) {
		p = get_phy_port(sw, n);
		info = get_port_info(sw, p);

		/* Port does not have PHY. */
		if (!info->phy)
			continue;

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

static u16 port_advertised_flow_ctrl(int flow_ctrl, u16 ctrl)
{
	ctrl &= ~PORT_AUTO_NEG_PAUSE;
	switch (flow_ctrl) {
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

static u8 sw_determine_flow_ctrl(struct ksz_sw *sw, bool force_link,
	u16 local, u16 remote)
{
	int rx;
	int tx;
	u8 flow = 0;

	if (sw->overrides & PAUSE_FLOW_CTRL)
		return flow;

	rx = tx = 0;
	if (force_link)
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
#ifdef DBG_LINK
	printk(KERN_INFO "pause: %d, %d; %04x %04x\n",
		rx, tx, local, remote);
#endif
	return flow;
}  /* sw_determine_flow_ctrl */

static void port_sgmii_r(struct ksz_sw *sw, uint port, u16 devid, u16 reg,
	u16 *buf, u16 len)
{
	u32 data;

	data = devid & PORT_SGMII_DEVICE_ID_M;
	data <<= PORT_SGMII_DEVICE_ID_S;
	data |= reg;
	if (len > 1)
		data |= PORT_SGMII_AUTO_INCR;
	port_w32(sw, port, REG_PORT_SGMII_ADDR__4, data);
	while (len) {
		port_r32(sw, port, REG_PORT_SGMII_DATA__4, &data);
		*buf++ = (u16) data;
		len--;
	}
}  /* port_sgmii_r */

static void port_sgmii_w(struct ksz_sw *sw, uint port, u16 devid, u16 reg,
	u16 *buf, u16 len)
{
	u32 data;

	data = devid & PORT_SGMII_DEVICE_ID_M;
	data <<= PORT_SGMII_DEVICE_ID_S;
	data |= reg;
	if (len > 1)
		data |= PORT_SGMII_AUTO_INCR;
	port_w32(sw, port, REG_PORT_SGMII_ADDR__4, data);
	while (len) {
		data = *buf++;
		port_w32(sw, port, REG_PORT_SGMII_DATA__4, data);
		len--;
	}
}  /* port_sgmii_w */

static u16 port_sgmii_phy_r(struct ksz_sw *sw, uint port, u16 reg)
{
	u16 buf;

	do {
		port_sgmii_r(sw, port, SR_MII, MMD_SR_MII_PHY_CTRL, &buf, 1);
	} while (buf & SR_MII_PHY_START_BUSY);
	buf = reg;
	port_sgmii_w(sw, port, SR_MII, MMD_SR_MII_PHY_ADDR, &buf, 1);
	buf = 0;
	port_sgmii_w(sw, port, SR_MII, MMD_SR_MII_PHY_CTRL, &buf, 1);
	buf |= SR_MII_PHY_START_BUSY;
	port_sgmii_w(sw, port, SR_MII, MMD_SR_MII_PHY_CTRL, &buf, 1);
	do {
		port_sgmii_r(sw, port, SR_MII, MMD_SR_MII_PHY_CTRL, &buf, 1);
	} while (buf & SR_MII_PHY_START_BUSY);
	port_sgmii_r(sw, port, SR_MII, MMD_SR_MII_PHY_DATA, &buf, 1);
	return buf;
}  /* port_sgmii_phy_r */

static void port_sgmii_phy_w(struct ksz_sw *sw, uint port, u16 reg, u16 val)
{
	u16 buf;

	do {
		port_sgmii_r(sw, port, SR_MII, MMD_SR_MII_PHY_CTRL, &buf, 1);
	} while (buf & SR_MII_PHY_START_BUSY);
	buf = reg;
	port_sgmii_w(sw, port, SR_MII, MMD_SR_MII_PHY_ADDR, &buf, 1);
	buf = val;
	port_sgmii_w(sw, port, SR_MII, MMD_SR_MII_PHY_DATA, &buf, 1);
	buf = SR_MII_PHY_WRITE;
	port_sgmii_w(sw, port, SR_MII, MMD_SR_MII_PHY_CTRL, &buf, 1);
	buf |= SR_MII_PHY_START_BUSY;
	port_sgmii_w(sw, port, SR_MII, MMD_SR_MII_PHY_CTRL, &buf, 1);
	do {
		port_sgmii_r(sw, port, SR_MII, MMD_SR_MII_PHY_CTRL, &buf, 1);
	} while (buf & SR_MII_PHY_START_BUSY);
}  /* port_sgmii_phy_w */

static int port_sgmii_detect(struct ksz_sw *sw, uint p)
{
	u16 buf[6];
	int ret = 0;

	port_sgmii_phy_w(sw, p, SR_MII_PHY_JTAG_CHIP_ID_LO, 0x1234);
	buf[0] = port_sgmii_phy_r(sw, p, SR_MII_PHY_JTAG_CHIP_ID_LO);
	buf[1] = port_sgmii_phy_r(sw, p, SR_MII_PHY_JTAG_CHIP_ID_HI);
dbg_msg("jtag: %04x %04x\n", buf[1], buf[0]);
	port_sgmii_r(sw, p, SR_MII, 0, buf, 6);
dbg_msg("%04x %04x %04x %04x %04x %04x\n",
buf[0], buf[1], buf[2], buf[3], buf[4], buf[5]);

	/* Cannot detect whether the SGMII PHY is plugged in reliably. */
	if (sw->sgmii_mode) {
		ret = 1;
		if (buf[5] & SR_MII_REMOTE_ACK) {
			if (buf[5] & (SR_MII_REMOTE_HALF_DUPLEX |
				      SR_MII_REMOTE_FULL_DUPLEX))
				sw->port_info[p].fiber = 1;
			else if (sw->sgmii_mode == 1)
				sw->sgmii_mode = 2;
		} else if (sw->sgmii_mode == 1)
			sw->port_info[p].fiber = 1;
	}
	return ret;
}  /* port_sgmii_detect */

static void port_sgmii_setup(struct ksz_sw *sw, uint p, bool pcs, bool master,
	bool autoneg, int speed, int duplex)
{
	u16 cfg;
	u16 ctrl;
	u16 adv;

	/* SGMII registers are not changed by reset. */
	port_sgmii_r(sw, p, SR_MII, MMD_SR_MII_AUTO_NEG_CTRL, &cfg, 1);
dbg_msg("  cfg: %04x\n", cfg);
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
dbg_msg("CFG: %04x\n", cfg);
	port_sgmii_w(sw, p, SR_MII, MMD_SR_MII_AUTO_NEG_CTRL, &cfg, 1);
	port_sgmii_r(sw, p, SR_MII, MMD_SR_MII_CTRL, &ctrl, 1);
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
dbg_msg("CTRL: %04x\n", ctrl);
		port_sgmii_w(sw, p, SR_MII, MMD_SR_MII_CTRL, &ctrl, 1);
		return;
	} else if (!(ctrl & SR_MII_AUTO_NEG_ENABLE)) {
		ctrl |= SR_MII_AUTO_NEG_ENABLE;
dbg_msg("CTRL: %04x\n", ctrl);
		port_sgmii_w(sw, p, SR_MII, MMD_SR_MII_CTRL, &ctrl, 1);
	}

	/* Need to write to advertise register to send correct signal. */
	/* Default value is 0x0020. */
	port_sgmii_r(sw, p, SR_MII, MMD_SR_MII_AUTO_NEGOTIATION, &adv, 1);
dbg_msg("  adv: %04x\n", adv);
	adv = SR_MII_AUTO_NEG_ASYM_PAUSE_RX << SR_MII_AUTO_NEG_PAUSE_S;
	if (duplex)
		adv |= SR_MII_AUTO_NEG_FULL_DUPLEX;
	else
		adv |= SR_MII_AUTO_NEG_HALF_DUPLEX;
dbg_msg("ADV: %04x\n", adv);
	port_sgmii_w(sw, p, SR_MII, MMD_SR_MII_AUTO_NEGOTIATION, &adv, 1);
	if (master && autoneg) {
		ctrl |= SR_MII_AUTO_NEG_RESTART;
dbg_msg("AUTO_NEG: %04x\n", ctrl);
		port_sgmii_w(sw, p, SR_MII, MMD_SR_MII_CTRL, &ctrl, 1);
	}
}  /* port_sgmii_setup */

static int sgmii_port_get_speed(struct ksz_sw *sw, uint p, bool force_link)
{
	u16 data;
	u16 speed;
	u16 status;
	u8 link;
	int ret = 0;
	struct ksz_port_info *info = get_port_info(sw, p);

	port_sgmii_r(sw, p, SR_MII, MMD_SR_MII_STATUS, &status, 1);
	port_sgmii_r(sw, p, SR_MII, MMD_SR_MII_STATUS, &status, 1);
	port_sgmii_r(sw, p, SR_MII, MMD_SR_MII_AUTO_NEG_STATUS, &data, 1);

	/* Running in fiber mode. */
	if (info->fiber && (status & PORT_LINK_STATUS) && !data) {
		data = SR_MII_STAT_LINK_UP |
		       (SR_MII_STAT_1000_MBPS << SR_MII_STAT_S) |
		       SR_MII_STAT_FULL_DUPLEX;
	}
	if (data & SR_MII_STAT_LINK_UP)
		ret = 1;

	link = data & ~SR_MII_AUTO_NEG_COMPLETE_INTR;
	if (info->link == link)
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
		port_sgmii_w(sw, p, SR_MII, MMD_SR_MII_CTRL, &ctrl, 1);
	}
	if (data & SR_MII_STAT_LINK_UP) {
		speed = (data >> SR_MII_STAT_S) & SR_MII_STAT_M;
		info->tx_rate = 10 * TX_RATE_UNIT;
		if (SR_MII_STAT_1000_MBPS == speed)
			info->tx_rate = 1000 * TX_RATE_UNIT;
		else if (SR_MII_STAT_100_MBPS == speed)
			info->tx_rate = 100 * TX_RATE_UNIT;

		info->duplex = 1;
		if (data & SR_MII_STAT_FULL_DUPLEX)
			info->duplex = 2;

		if (info->link != link) {
			SW_D flow_ctrl;

			port_r(sw, p, REG_PORT_STATUS_0, &flow_ctrl);
#ifdef DBG_LINK
			printk(KERN_INFO "flow_ctrl: "SW_SIZE_STR"\n",
				flow_ctrl & (PORT_RX_FLOW_CTRL |
				PORT_TX_FLOW_CTRL));
#endif
			info->flow_ctrl = 3;
			if (flow_ctrl & PORT_RX_FLOW_CTRL)
				info->flow_ctrl |= 0x10;
			if (flow_ctrl & PORT_TX_FLOW_CTRL)
				info->flow_ctrl |= 0x20;
			ret |= 2;
		}
	} else {
		ret = 2;
	}
	info->link = link;
	return ret;
}  /* sgmii_port_get_speed */

static void sgmii_port_set_speed(struct ksz_sw *sw, uint p, int speed,
				 int duplex, int flow_ctrl)
{
	u16 ctrl;
	u16 cfg;
	u16 adv;

	port_sgmii_r(sw, p, SR_MII, MMD_SR_MII_AUTO_NEGOTIATION, &adv, 1);
	cfg = adv;
	switch (flow_ctrl) {
	case PHY_FLOW_CTRL:
		adv = SR_MII_AUTO_NEG_SYM_PAUSE;
		break;
	case PHY_TX_ONLY:
		adv = SR_MII_AUTO_NEG_ASYM_PAUSE_TX;
		break;
	case PHY_RX_ONLY:
		adv = SR_MII_AUTO_NEG_ASYM_PAUSE_RX;
		break;
	default:
		adv = 0;
	}
	adv <<= SR_MII_AUTO_NEG_PAUSE_S;
	adv |= SR_MII_AUTO_NEG_FULL_DUPLEX;
	adv |= SR_MII_AUTO_NEG_HALF_DUPLEX;
	if (duplex) {
		if (1 == duplex)
			adv &= ~SR_MII_AUTO_NEG_FULL_DUPLEX;
		else if (2 == duplex)
			adv &= ~SR_MII_AUTO_NEG_HALF_DUPLEX;
	}
	if (adv != cfg) {
dbg_msg("ADV: %04x\n", adv);
		port_sgmii_w(sw, p, SR_MII, MMD_SR_MII_AUTO_NEGOTIATION,
			&adv, 1);
		port_sgmii_r(sw, p, SR_MII, MMD_SR_MII_CTRL, &ctrl, 1);
		ctrl |= SR_MII_AUTO_NEG_RESTART;
		port_sgmii_w(sw, p, SR_MII, MMD_SR_MII_CTRL, &ctrl, 1);
	}
}  /* sgmii_port_set_speed */

static int phy_port_get_speed(struct ksz_sw *sw, uint p, bool force_link)
{
	u16 data;
	u16 link;
	u16 dbg_link;
	u16 status;
	u32 local;
	u32 remote;
	int ret = 0;
	struct ksz_port_info *info = get_port_info(sw, p);

#ifdef NO_PHY_READ
	if (sw) {
		link = PORT_LINK_STATUS;
		dbg_link = link;
		status = PORT_STAT_SPEED_100MBIT |
			 PORT_STAT_FULL_DUPLEX;
		local = 0x10001000;
		remote = 0x10001000;
		goto get_cont1;
	}
#endif

	if (sw->features & GIGABIT_SUPPORT)
		port_r16(sw, p, REG_PORT_PHY_1000_CTRL, &data);
	else
		data = 0;
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

#ifdef NO_PHY_READ
get_cont1:
#endif
	/* The partner capability register is updated but the
	 * auto-negotiation is not completed yet.
	 */
	link &= (PORT_AUTO_NEG_ACKNOWLEDGE | PORT_LINK_STATUS);
	status &= (PORT_STAT_SPEED_1000MBIT |
		  PORT_STAT_SPEED_100MBIT |
		  PORT_STAT_SPEED_10MBIT |
		  PORT_STAT_FULL_DUPLEX);
	link |= (status << 8);

	if (link & PORT_LINK_STATUS)
		ret = 1;

	/* No change to status. */
	if (local == info->advertised && link == info->link)
		return ret;

	if (!(dbg_link & PORT_LINK_STATUS) &&
	    dbg_link & PORT_AUTO_NEG_ACKNOWLEDGE)
dbg_msg(" link? %d=%04x\n", p, dbg_link);
#ifdef DBG_LINK
	printk(KERN_INFO
		"%d=advertised: %08X-%08X; partner: %08X-%08X"
		"; link: %04X-%04X\n", p,
		local, info->advertised, remote, info->partner,
		link, info->link);
#endif
	if (link & PORT_LINK_STATUS) {
		info->tx_rate = 10 * TX_RATE_UNIT;
		if (status & PORT_STAT_SPEED_100MBIT)
			info->tx_rate = 100 * TX_RATE_UNIT;
		else if (status & PORT_STAT_SPEED_1000MBIT)
			info->tx_rate = 1000 * TX_RATE_UNIT;

		info->duplex = 1;
		if (status & PORT_STAT_FULL_DUPLEX)
			info->duplex = 2;

		if (link != info->link) {
			SW_D flow_ctrl;

			port_r(sw, p, REG_PORT_STATUS_0, &flow_ctrl);
#ifdef DBG_LINK
			printk(KERN_INFO "flow_ctrl: "SW_SIZE_STR"\n",
				flow_ctrl & (PORT_RX_FLOW_CTRL |
				PORT_TX_FLOW_CTRL));
#endif
			info->flow_ctrl = sw_determine_flow_ctrl(sw,
				force_link, local, remote);
			if (flow_ctrl & PORT_RX_FLOW_CTRL)
				info->flow_ctrl |= 0x10;
			if (flow_ctrl & PORT_TX_FLOW_CTRL)
				info->flow_ctrl |= 0x20;
			if (sw->info)
				port_cfg_back_pressure(sw, p,
					(1 == info->duplex));
			ret |= 2;
		}
	} else {
		ret = 2;
	}
	info->advertised = local;
	info->partner = remote;
	info->link = link;
	return ret;
}  /* phy_port_get_speed */

static void phy_port_set_speed(struct ksz_sw *sw, uint p, int speed,
			       int duplex, int flow_ctrl)
{
	struct ksz_port_cfg *port_cfg;
	u16 data;
	u16 ctrl;
	u16 local;
	u16 status;
	u32 adv;
	u32 cfg;

	if (sw->features & GIGABIT_SUPPORT)
		port_r16(sw, p, REG_PORT_PHY_1000_CTRL, &ctrl);
	else
		ctrl = 0;
	port_r16(sw, p, REG_PORT_PHY_AUTO_NEGOTIATION, &local);
	if (!(local & PORT_AUTO_NEG_SYM_PAUSE) &&
	    (PHY_FLOW_CTRL == flow_ctrl ||
	    PHY_RX_ONLY == flow_ctrl))
		dbg_msg(" no sym pause: %d %04x\n", p, local);
	if ((local & PORT_AUTO_NEG_ASYM_PAUSE) &&
	    (PHY_TX_ONLY != flow_ctrl &&
	    PHY_RX_ONLY != flow_ctrl))
		dbg_msg(" has asym pause: %d %04x\n", p, local);
	adv = ctrl;
	adv <<= 16;
	adv |= local;
	port_r16(sw, p, P_SPEED_STATUS, &status);
	port_r16(sw, p, P_NEG_RESTART_CTRL, &data);

	cfg = 0;

	/* Do not need to restart auto-negotiation if desired settings
	 * are same.
	 */
	if ((data & PORT_AUTO_NEG_ENABLE) &&
	    (status &
	    (PORT_STAT_SPEED_1000MBIT |
	     PORT_STAT_SPEED_100MBIT |
	     PORT_STAT_SPEED_10MBIT)))
		cfg = adv;

	/* Need auto-negotiation restart. */
	port_cfg = get_port_cfg(sw, p);
	if (port_cfg->setup_time) {
		cfg = 0;
		port_cfg->setup_time = 0;
	}

	local = port_advertised_flow_ctrl(flow_ctrl, local);

	if (sw->features & GIGABIT_SUPPORT)
		ctrl |= PORT_AUTO_NEG_1000BT_FD | PORT_AUTO_NEG_1000BT;
	local |= PORT_AUTO_NEG_100BTX_FD | PORT_AUTO_NEG_100BTX |
		PORT_AUTO_NEG_10BT_FD | PORT_AUTO_NEG_10BT;

	/* Check if manual configuration is specified by the user. */
	if (speed || duplex) {
		if (speed && speed != 1000)
			ctrl &= ~(PORT_AUTO_NEG_1000BT_FD |
				PORT_AUTO_NEG_1000BT);
		if (10 == speed)
			local &= ~(PORT_AUTO_NEG_100BTX_FD |
				PORT_AUTO_NEG_100BTX);
		else if (100 == speed)
			local &= ~(PORT_AUTO_NEG_10BT_FD |
				PORT_AUTO_NEG_10BT);
		else if (1000 == speed)
			local &= ~(PORT_AUTO_NEG_100BTX_FD |
				PORT_AUTO_NEG_100BTX |
				PORT_AUTO_NEG_10BT_FD |
				PORT_AUTO_NEG_10BT);
		if (1 == duplex) {
			ctrl &= ~PORT_AUTO_NEG_1000BT_FD;
			local &= ~(PORT_AUTO_NEG_100BTX_FD |
				PORT_AUTO_NEG_10BT_FD);
		} else if (2 == duplex) {
			ctrl &= ~PORT_AUTO_NEG_1000BT;
			local &= ~(PORT_AUTO_NEG_100BTX |
				PORT_AUTO_NEG_10BT);
		}
	}
	adv = ctrl;
	adv <<= 16;
	adv |= local;
	if (adv != cfg) {
		if (sw->features & GIGABIT_SUPPORT)
			port_w16(sw, p, REG_PORT_PHY_1000_CTRL, ctrl);
		port_w16(sw, p, REG_PORT_PHY_AUTO_NEGOTIATION, local);
		port_r16(sw, p, P_NEG_RESTART_CTRL, &data);
		data |= PORT_AUTO_NEG_ENABLE;
		port_cfg->phy_ctrl = data;
		data |= PORT_AUTO_NEG_RESTART;
		port_w16(sw, p, P_NEG_RESTART_CTRL, data);

		/* Link is going down. */
		sw->port_state[p].state = media_disconnected;
	}
}  /* phy_port_set_speed */

static void phy_port_force_speed(struct ksz_sw *sw, uint p, int speed,
			         int duplex, int flow_ctrl)
{
	struct ksz_port_cfg *cfg;
	u16 data;

	port_r16(sw, p, P_PHY_CTRL, &data);
	data &= ~(PORT_AUTO_NEG_ENABLE |
		PORT_SPEED_100MBIT | PORT_SPEED_1000MBIT);
	if (100 == speed)
		data |= PORT_SPEED_100MBIT;
	else if (1000 == speed)
		data |= PORT_SPEED_1000MBIT;
	if (1 == duplex)
		data &= ~PORT_FULL_DUPLEX;
	else if (2 == duplex)
		data |= PORT_FULL_DUPLEX;
	port_w16(sw, p, P_PHY_CTRL, data);
	cfg = get_port_cfg(sw, p);
	cfg->phy_ctrl = data;
}  /* phy_port_force_speed */

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
	int link;
	uint i;
	uint n;
	uint p;
	int change = 0;

	for (i = 0, n = port->first_port; i < port->port_cnt; i++, n++) {
		p = get_phy_port(sw, n);
		info = get_port_info(sw, p);

		/* Port does not have PHY. */
		if (!info->phy) {

			/* By itself. */
			if (1 == port->port_cnt &&
			    (sw->phy_intr & (1 << p)))
				change |= 1 << p;
			continue;
		}

		if (!(sw->phy_intr & (1 << p))) {
			if (!linked && p != sw->HOST_PORT &&
			    info->state == media_connected)
				linked = info;
			continue;
		}
		sw->phy_intr &= ~(1 << p);

		state = &sw->port_state[p];

		if (!info->get_link_speed)
			continue;
		link = info->get_link_speed(sw, p, port->force_link);
		if (link & 1) {

			/* Remember the first linked port. */
			if (!linked && p != sw->HOST_PORT)
				linked = info;
		}

		/* No change to status. */
		if (!(link & 2))
			continue;

		if (link & 1) {
			if (media_connected != info->state) {
				change |= 1 << p;
			}
			if (link & 2)
				change |= 1 << p;
			info->state = media_connected;
			state->tx_rate = info->tx_rate;
		} else {
			if (media_disconnected != info->state) {
				change |= 1 << p;

				/* Indicate the link just goes down. */
				state->link_down = 1;

				/* For 802.1X Authentication. */
				if ((sw->overrides & USE_802_1X_AUTH) &&
				    (sw->on_ports & (1 << p)))
					port_open(sw, p, false);
			}
			info->state = media_disconnected;
		}
		info->report = true;
		if (media_disconnected == info->state) {
			sw->live_ports &= ~(1 << p);
			port->live_ports &= ~(1 << p);
		} else {
			sw->live_ports |= (1 << p);
			port->live_ports |= (1 << p);
		}
		state->state = info->state;
	}

	if (linked && media_disconnected == port->linked->state)
		port->linked = linked;

#ifdef DBG_LINK
	if (change)
		dbp_link(port, sw, change);
#endif
	if (change) {
		port->link_ports |= change;
		schedule_work(&port->link_update);
	}
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
	uint i;
	uint n;
	uint p;

	for (i = 0, n = port->first_port; i < port->port_cnt; i++, n++) {
		p = get_phy_port(sw, n);
		info = get_port_info(sw, p);
		if (!info->set_link_speed)
			continue;

		info->own_flow_ctrl = port->flow_ctrl;
		info->own_duplex = port->duplex;
		info->own_speed = port->speed;

		info->set_link_speed(sw, p, port->speed, port->duplex,
				     port->flow_ctrl);
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
	uint i;
	uint n;
	uint p;

	for (i = 0, n = port->first_port; i < port->port_cnt; i++, n++) {
		p = get_phy_port(sw, n);
		info = get_port_info(sw, p);
		if (!info->force_link_speed)
			continue;

		info->own_flow_ctrl = port->flow_ctrl;
		info->own_duplex = port->duplex;
		info->own_speed = port->speed;

		info->force_link_speed(sw, p, port->speed, port->duplex,
				       port->flow_ctrl);
	}
}  /* port_force_link_speed */

static void port_mmd_read(struct ksz_sw *sw, uint port, u16 devid, u16 reg,
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

static void port_mmd_write(struct ksz_sw *sw, uint port, u16 devid, u16 reg,
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

static void port_chk_sqi(struct ksz_sw *sw, uint port)
{
	u16 sqi[4];
	int val;
	int val2;
	int i;
	int n;
	int cnt = 10;
	int num = 4;
	struct ksz_port_info *info = get_port_info(sw, port);

	if (info->state == media_disconnected)
		return;
	if (info->tx_rate / TX_RATE_UNIT != 1000)
		num = 1;
	val = 0;
	for (n = 0; n < cnt; n++) {
		port_mmd_read(sw, port, MMD_DEVICE_ID_DSP, MMD_DSP_SQI_CHAN_A,
			sqi, num);
		val2 = 0;
		for (i = 0; i < num; i++) {
			if (sqi[i] & DSP_SQI_ERR_DETECTED)
dbg_msg(" ?? %s %d %04x\n", __func__, i, sqi[i]);
			if (sqi[i] & DSP_SQI_ERR_DETECTED)
				break;
			val2 += sqi[i] & DSP_SQI_AVG_ERR;
		}
		val2 /= num;
		val += val2;
	}
	val /= cnt;
	val >>= 8;
	if (val > 15)
		val = 15;
	val = 15 - val;
	info->sqi = val;
}  /* port_chk_sqi */

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

static void port_setup_eee(struct ksz_sw *sw, uint port)
{
	u16 val[0x20];

	if (sw->features & NEW_CAP) {
#ifdef DEBUG_PHY
dbg_msg("%s %d\n", __func__, port);
if (0 == port) {
int i;
		port_r16(sw, port, REG_PORT_PHY_CTRL, val);
dbg_msg("%04x=%04x\n", REG_PORT_PHY_CTRL, val[0]);
		port_r16(sw, port, REG_PORT_PHY_REMOTE_LB_LED, val);
dbg_msg("%04x=%04x\n", REG_PORT_PHY_REMOTE_LB_LED, val[0]);

dbg_msg(" %x\n", MMD_DEVICE_ID_DSP);
		port_mmd_read(sw, port, MMD_DEVICE_ID_DSP, 0x6F, val, 1);
dbg_msg(" %04x=%04x\n", 0x6F, val[0]);
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
		port_mmd_read(sw, port, 0x1C, 0x8, val, 1);
dbg_msg(" %04x=%04x\n", 0x8, val[0]);
		port_mmd_read(sw, port, 0x1C, 0x9, val, 1);
dbg_msg(" %04x=%04x\n", 0x9, val[0]);

		port_mmd_read(sw, port, 0x1C, 0x13, &val[0x13], 12);
for (i = 0; i < 12; i++)
dbg_msg("%04x ", val[0x13 + i]);
dbg_msg("\n");
		port_mmd_read(sw, port, 0x1C, 0x20, val, 1);
dbg_msg(" %04x=%04x\n", 0x20, val[0]);
}
#endif

		port_w16(sw, port, REG_PORT_PHY_CTRL, 0x2100);
#ifdef SETUP_PHY_OLD
		port_w16(sw, port, REG_PORT_PHY_REMOTE_LB_LED, 0x00f0);
#endif

#ifdef SETUP_PHY_NEW
		val[0] = 0xDD0B;
		port_mmd_write(sw, port, MMD_DEVICE_ID_DSP, 0x6F, val, 1);
#else
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
		port_mmd_write(sw, port, MMD_DEVICE_ID_DSP, 0x79, &val[0x09],
			18);
#endif

		val[0] = 0x6032;
		port_mmd_write(sw, port, MMD_DEVICE_ID_DSP, 0x8F, val, 1);
		val[0] = 0x248C;
		port_mmd_write(sw, port, MMD_DEVICE_ID_DSP, 0x9D, val, 1);

		val[0] = 0x0060;
		port_mmd_write(sw, port, MMD_DEVICE_ID_DSP, 0x75, val, 1);
		val[0] = 0x7777;
		port_mmd_write(sw, port, MMD_DEVICE_ID_DSP, 0xD3, val, 1);

#ifdef SETUP_PHY_OLD
		val[0] = 0x9400;
		port_mmd_write(sw, port, MMD_DEVICE_ID_AFED, 0x0, val, 1);
#endif

#ifdef SETUP_PHY_NEW
		val[0] = 0x00d0;
		port_mmd_write(sw, port, MMD_DEVICE_ID_AFED, 0x4, val, 1);
		val[0] = 0x3008;
		port_mmd_write(sw, port, MMD_DEVICE_ID_AFED, 0x6, val, 1);
		val[0] = 0x2001;
		port_mmd_write(sw, port, MMD_DEVICE_ID_AFED, 0x8, val, 1);
#else
/*
 * THa  2016/10/20
 * Use value 0x00E2 for improved 100BTX PMD Output Amplitude.
 */
		val[0] = 0x00e2;
		port_mmd_write(sw, port, MMD_DEVICE_ID_AFED, 0x4, val, 1);
		val[0] = 0x3100;
		port_mmd_write(sw, port, MMD_DEVICE_ID_AFED, 0x6, val, 1);
		val[0] = 0xe01c;
		port_mmd_write(sw, port, MMD_DEVICE_ID_AFED, 0x9, val, 1);
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
		port_mmd_write(sw, port, MMD_DEVICE_ID_AFED, 0x13, &val[0x13],
			12);
#ifdef SETUP_PHY_NEW
		val[0] = 0xeeee;
		port_mmd_write(sw, port, MMD_DEVICE_ID_AFED, 0x20, val, 1);
#endif

		if (port == sw->HOST_PORT)
			port_w16(sw, port, REG_PORT_PHY_CTRL, 0x1140);
		else {
			/* Avoid empty interrupt at beginning. */
			port_w16(sw, port, REG_PORT_PHY_CTRL, 0x0140);
			sw->info->port_cfg[port].setup_time = 4000;
		}
	} else {
		memset(val, 0, sizeof(val));
		port_mmd_write(sw, port, 0x1C, 0x10, val, 0x11);
	}
}  /* port_setup_eee */

static void port_setup_9893(struct ksz_sw *sw, uint port)
{
	u16 val[1];
	int i;
	struct ksz_phy_settings *set;

	for (i = 0; i < sizeof(ksz9893_phy_settings) /
	     sizeof(struct ksz_phy_settings); i++) {
		set = &ksz9893_phy_settings[i];
		val[0] = set->val;
		port_mmd_write(sw, port, set->mmd, set->reg, val, 1);
	}
}  /* port_setup_9893 */

static void sw_dis_intr(struct ksz_sw *sw)
{
	sw->reg->w32(sw, REG_SW_INT_MASK__4, SWITCH_INT_MASK);
	sw->reg->w32(sw, REG_SW_PORT_INT_MASK__4, sw->PORT_INTR_MASK);
}  /* sw_dis_intr */

static void sw_ena_intr(struct ksz_sw *sw)
{
	uint n;
	uint p;

	sw->reg->w32(sw, REG_SW_INT_MASK__4,
		~sw->intr_mask & SWITCH_INT_MASK);
	sw->reg->w32(sw, REG_SW_PORT_INT_MASK__4,
		~sw->port_intr_mask & sw->PORT_INTR_MASK);
	for (n = 0; n <= sw->mib_port_cnt; n++) {
		p = get_phy_port(sw, n);
		port_w(sw, p, REG_PORT_INT_MASK,
			~sw->info->port_cfg[p].intr_mask & PORT_INT_MASK);
	}
}  /* sw_ena_intr */

/**
 * sw_enable - enable the switch
 * @sw:		The switch instance.
 *
 * This routine enables the switch with a specific configuration.
 */
static void sw_enable(struct ksz_sw *sw)
{
	uint n;
	uint port;
	bool fewer;
	struct ksz_port_cfg *cfg;
	struct ksz_port_info *info;
	int state = STP_STATE_FORWARDING;

	if (sw->features & (DSA_SUPPORT))
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
			if (port < sw->phy_port_cnt)
				port_cfg_power(sw, port, false);
		}
	}
dbg_msg(" fewer: %d %d\n", fewer, sw->eth_cnt);
	if (fewer)
		sw_cfg_port_base_vlan(sw, sw->HOST_PORT, sw->PORT_MASK);
	if ((sw->dev_count > 1 && !sw->dev_offset) ||
	    (sw->features & (STP_SUPPORT | DSA_SUPPORT))) {
		u16 member;

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
		u16 member;

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
	 * the learning is turned off.  Once the entries in the table the
	 * switch may keep updating them even learning is off.
	 */
	if (sw->dev_count > 1)
		sw_flush_dyn_mac_table(sw, sw->port_cnt);
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
	sw_init_cached_regs(sw);
	sw->open_ports = sw->PORT_MASK & ~sw->HOST_MASK;
	sw->mtu = sw->reg->r16(sw, REG_SW_MTU__2);

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
	uint n;
	uint port;
	struct ksz_port_cfg *cfg;

	/* Starting from stopped state will flush the ACL table. */
	sw_cfg(sw, REG_SW_OPERATION, SW_START, 1);

	sw->port_intr_mask = sw->PORT_INTR_MASK;
	sw->intr_mask = TRIG_TS_INT | APB_TIMEOUT_INT;
	sw_set_global_ctrl(sw);
	sw_cfg(sw, REG_SW_LUE_CTRL_0, SW_RESV_MCAST_ENABLE, 1);
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
	if (sw->features & IS_9893) {
		sw_cfg(sw, REG_SW_MAC_CTRL_0, SW_CHECK_LENGTH, 0);
		sw->reg->w16(sw, REG_AVB_STRATEGY__2,
			SW_SHAPING_CREDIT_ACCT |
			SW_POLICING_CREDIT_ACCT);
	}

	for (n = 0; n <= sw->mib_port_cnt; n++) {
		port = get_phy_port(sw, n);
		cfg = get_port_cfg(sw, port);
		cfg->intr_mask = 0;
		port_cfg_back_pressure(sw, port, 1);
		if (port < sw->phy_port_cnt)
			port_cfg_force_flow_ctrl(sw, port, 0);
		cfg->intr_mask |= PORT_ACL_INT;
		if (port == sw->HOST_PORT)
			continue;

#ifdef CONFIG_1588_PTP
		cfg->intr_mask |= PORT_PTP_INT;
#endif
	}
/*
 * THa  2015/10/01
 * Increasing wait time in this register avoids the PTP transmit problem.
 */
	dbg_msg("eee txq wait: %04x\n",
		sw->reg->r16(sw, REG_SW_EEE_TXQ_WAIT_TIME__2));
	sw->reg->w16(sw, REG_SW_EEE_TXQ_WAIT_TIME__2, 0x0040);

	for (n = 0; n <= sw->mib_port_cnt; n++) {
		u16 val = 0;

		port = get_phy_port(sw, n);
		if (port >= sw->phy_port_cnt)
			continue;
		if (sw->features & IS_9893)
			port_setup_9893(sw, port);
		else
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
 * 100Mbit link to be unstable, with blinking LED that can only transmit.
 * Enabling EEE will recover this error condition.
 */
		/* Enable port PHY interrupt. */
		sw->info->port_cfg[port].intr_mask |= PORT_PHY_INT;

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
		do {
			u32 data;

			port_r32(sw, port, REG_PORT_PHY_INT_ENABLE & ~3, &data);
			data &= 0xffff00ff;
			data |= val << 8;
			port_w32(sw, port, REG_PORT_PHY_INT_ENABLE & ~3, data);
		} while (0);
	}
#if 0
	for (port = 0; port < sw->phy_port_cnt; port++) {
#ifdef CONFIG_KSZ_IBA
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
	port = 6;
	if (PHY_INTERFACE_MODE_SGMII == sw->port_info[port].interface) {
		bool pcs = true;
		bool master = false;
		bool autoneg = true;

		/* Possibly connect directly. */
		if (sw->sgmii_mode == 0) {
			master = true;
			autoneg = false;

		/* Using fiber. */
		} else if (sw->sgmii_mode == 1) {
			pcs = false;
			master = true;
		}
		port_sgmii_setup(sw, port, pcs, master, autoneg, 2, 1);
		sw->info->port_cfg[port].intr_mask |= PORT_SGMII_INT;
	}

	sw_setup_broad_storm(sw);

	sw_setup_prio(sw);

	sw_setup_mirror(sw);

	sw->info->multi_sys = MULTI_MAC_TABLE_ENTRIES;
	sw->info->multi_net = SWITCH_MAC_TABLE_ENTRIES;

	/* Unknown multicast forwarding will not be used. */
	if (sw->features & AVB_SUPPORT)
		sw_setup_multi(sw);
#ifdef CONFIG_KSZ_STP
	sw_setup_stp(sw);
#endif
#ifdef CONFIG_1588_PTP
	sw_setup_ptp(sw);
#endif
#ifdef CONFIG_KSZ_IBA
	if (!sw->info->iba.use_iba)
		sw_setup_iba(sw);
#endif
#ifdef CONFIG_KSZ_DLR
	if (sw->features & DLR_HW)
		sw_setup_dlr(sw);
#endif
#ifdef CONFIG_KSZ_HSR
	if (sw->features & HSR_HW)
		sw_setup_hsr(sw);
#endif
	sw_setup_acl(sw);
}  /* sw_setup */

static void sw_reset(struct ksz_sw *sw)
{
	uint p;
	u8 byte_before;
	u8 byte_after;

	sw->overrides &= ~VLAN_SET;
	sw_reset_setup(sw);

	sw_cfg(sw, REG_SW_OPERATION, SW_RESET, 1);
	delay_micro(1);

	/* Turn off SPI auto edge detection. */
	sw->reg->w8(sw, REG_SW_GLOBAL_SERIAL_CTRL_0, 0);

#if 1
	if (sw->overrides & USE_802_1X_AUTH)
		sw_cfg(sw, REG_SW_OPERATION, SW_START, 0);
#endif

/*
 * THa  2016/10/03
 * SGMII registers are not reset by hardware reset.
 */
	p = 6;
	if (PHY_INTERFACE_MODE_SGMII == sw->port_info[p].interface) {
		u16 ctrl;

		port_sgmii_r(sw, p, SR_MII, MMD_SR_MII_CTRL, &ctrl, 1);
		ctrl |= SR_MII_RESET;
		port_sgmii_w(sw, p, SR_MII, MMD_SR_MII_CTRL, &ctrl, 1);
		ctrl &= ~SR_MII_RESET;
		port_sgmii_w(sw, p, SR_MII, MMD_SR_MII_CTRL, &ctrl, 1);
	}
	for (p = sw->phy_port_cnt; p < sw->port_cnt; p++) {
		port_r(sw, p, REG_PORT_XMII_CTRL_1, &byte_before);
		byte_after = byte_before ^(PORT_MII_NOT_1GBIT |
			PORT_MII_MAC_MODE | PORT_MII_SEL_M);
		port_w(sw, p, REG_PORT_XMII_CTRL_1, byte_after);
		port_w(sw, p, REG_PORT_XMII_CTRL_1, byte_before);
		port_w16(sw, p, REG_PORT_XMII_CTRL_0,
			sw->cached.xmii[p - sw->phy_port_cnt]);
	}
	sw_reset_acl(sw);
	sw->overrides &= ~TAIL_TAGGING;
	sw->overrides &= ~PTP_TAG;
	sw->overrides &= ~TAG_REMOVE;
	sw_dis_intr(sw);
}  /* sw_reset */

static void sw_chk_regs(struct ksz_sw *sw, u32 addr, u8 *val, size_t txl)
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
}  /* sw_chk_regs */

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
	unsigned phy_reg;
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
	phy_reg = reg & 0x1FF;
	sw->ops->acquire(sw);
	if ((reg & 0xF000) && (0x120 <= phy_reg && phy_reg <= 0x13F) &&
	    ((reg & 3) || (count & 3))) {
		char *tmp;
		size_t cnt = (count + 3) & ~3;
		int start = phy_reg & 3;

#ifdef CONFIG_KSZ_IBA
		if (sw->info->iba.use_iba)
			start = 4 - ((phy_reg + count) & 3);
#endif
		tmp = kzalloc(cnt, GFP_KERNEL);
		if (!tmp) {
			i = 0;
			goto write_done;
		}
		reg &= ~3;
		i = sw->reg->get(sw, reg, cnt, tmp);
		memcpy(&tmp[start], buf, count);
		i = sw->reg->set(sw, reg, cnt, tmp);
		kfree(tmp);
	} else
		i = sw->reg->set(sw, reg, count, buf);
write_done:
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

#ifdef CONFIG_KSZ_IBA
/**
 * sw_set_spi - use SPI for access
 * @sw:		The switch instance.
 * @iba:	The IBA instance.
 *
 * This routine uses default hardware access like SPI for register access.
 */
static void sw_set_spi(struct ksz_sw *sw, struct ksz_iba_info *iba)
{
	sw->reg = sw->org_reg;
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

	/* Catch bug if triggered. */
	if (!iba->dev) {
		dbg_msg("No IBA dev\n");
		return;
	}
	if (sw->net_ops->get_ready && !sw->net_ops->get_ready(iba->dev)) {
		schedule_delayed_work(&sw->set_ops, 1);
		return;
	}
	if (sw->HOST_PORT < sw->phy_port_cnt &&
	    sw->port_info[sw->HOST_PORT].state != media_connected) {
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
	if (iba->use_iba) {
		u32 id;

		sw->intr_using += 3;
		iba->use_iba |= 0x80;
		id = sw->reg->r32(sw, REG_CHIP_ID0__1);
		iba->use_iba &= ~0x80;
dbg_msg("id = %08x\n", id);
#if 1
/*
 * THa  2016/01/03
 * KSZ9563 S1 does not respond the very first time when using RGMII.
 */
		if (id == 0xdeadbeaf && !(sw->features & NEW_CAP)) {
			id = sw->reg->r32(sw, REG_CHIP_ID0__1);
dbg_msg("id = %08x\n", id);
		}
#endif
		sw->intr_using -= 3;
		if (id == 0xdeadbeaf)
			sw_set_spi(sw, iba);
	}
	mutex_unlock(sw->reglock);
	mutex_unlock(sw->hwlock);
	mutex_unlock(&sw->lock);

	if (!iba->use_iba)
		return;
printk(KERN_INFO "Using IBA\n");
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
		uint port;
		u8 val = LINK_DOWN_INT | LINK_UP_INT;

		sw->ops->acquire(sw);
		for (port = 0; port < sw->phy_port_cnt; port++) {
			port_w8(sw, port, REG_PORT_PHY_INT_ENABLE, val);
		}
		sw->ops->release(sw);
	}
#endif
}  /* sw_set_ops */

/**
 * sw_set_dev - try to use SPI for access
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
	int delay_tick = msecs_to_jiffies(20);

	if (!iba->use_iba && sw->HOST_PORT < sw->phy_port_cnt)
		delay_tick = msecs_to_jiffies(100);
	if (!dev) {
		if (sw->reg != sw->org_reg) {
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

#ifdef CONFIG_KSZ_MRP
static void sw_set_mrp(struct work_struct *work)
{
	struct delayed_work *dwork = to_delayed_work(work);
	struct ksz_sw *sw = container_of(dwork, struct ksz_sw, set_mrp);

	if (sw->HOST_PORT < sw->phy_port_cnt &&
	    !netif_carrier_ok(sw->main_dev)) {
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
#define CABLE_LEN_MULTIPLIER		8

#define PHY_RESET_TIMEOUT		10

/**
 * sw_get_link_md -
 * @sw:		The switch instance.
 * @port:	The port index.
 *
 * This routine is used to get the LinkMD status.
 */
static void sw_get_link_md(struct ksz_sw *sw, uint port)
{
	u16 ctrl;
	u16 data;
	u16 giga;
	u16 link;
	u16 len;
	int i;
	int timeout;
	struct ksz_port_info *port_info = get_port_info(sw, port);

	port_r16(sw, port, P_LINK_STATUS, &link);

	/* Read second time in case the status is not latched. */
	if (!(link & PORT_LINK_STATUS))
		port_r16(sw, port, P_LINK_STATUS, &link);
	port_r16(sw, port, REG_PORT_PHY_DIGITAL_STATUS, &data);
	port_info->status[0] = CABLE_UNKNOWN;
	if (link & PORT_LINK_STATUS) {
		int stat = 0;

		port_info->status[0] = CABLE_GOOD;
		port_info->length[0] = 1;
		port_info->status[1] = CABLE_GOOD;
		port_info->length[1] = 1;
		port_info->status[2] = CABLE_GOOD;
		port_info->length[2] = 1;
		port_info->status[3] = CABLE_GOOD;
		port_info->length[3] = 1;
		port_info->status[4] = CABLE_GOOD;
		port_info->length[4] = 1;

		if (!(data & PORT_PHY_STAT_MDI))
			stat |= STATUS_CROSSOVER;
#if 0
		if (data & PORT_REVERSED_POLARITY)
			stat |= STATUS_REVERSED;
#endif
		if ((stat & (STATUS_CROSSOVER | STATUS_REVERSED)) ==
				(STATUS_CROSSOVER | STATUS_REVERSED))
			port_info->status[0] = CABLE_CROSSED_REVERSED;
		else if ((stat & STATUS_CROSSOVER) == STATUS_CROSSOVER)
			port_info->status[0] = CABLE_CROSSED;
		else if ((stat & STATUS_REVERSED) == STATUS_REVERSED)
			port_info->status[0] = CABLE_REVERSED;
		return;
	}

	/* Put in 1000 Mbps mode. */
	port_r16(sw, port, P_PHY_CTRL, &ctrl);
	data = PORT_FULL_DUPLEX | PORT_SPEED_1000MBIT;
	port_w16(sw, port, P_PHY_CTRL, data);
	port_r16(sw, port, REG_PORT_PHY_1000_CTRL, &giga);
	data = PORT_AUTO_NEG_MANUAL;
	port_w16(sw, port, REG_PORT_PHY_1000_CTRL, data);

	port_r16(sw, port, REG_PORT_PHY_LINK_MD, &data);

	/* Disable transmitter. */
	data |= PORT_TX_DISABLE;
	port_w16(sw, port, REG_PORT_PHY_LINK_MD, data);

	/* Wait at most 1 second.*/
	delay_milli(100);

	/* Enable transmitter. */
	data &= ~PORT_TX_DISABLE;
	port_w16(sw, port, REG_PORT_PHY_LINK_MD, data);

	for (i = 1; i <= 4; i++) {

		/* Start cable diagnostic test. */
		data |= PORT_START_CABLE_DIAG;
		data |= (i - 1) << PORT_CABLE_DIAG_PAIR_S;
		port_w16(sw, port, REG_PORT_PHY_LINK_MD, data);
		timeout = PHY_RESET_TIMEOUT;
		do {
			if (!--timeout)
				break;
			delay_milli(10);
			port_r16(sw, port, REG_PORT_PHY_LINK_MD, &data);
		} while ((data & PORT_START_CABLE_DIAG));

		port_info->length[i] = 0;
		port_info->status[i] = CABLE_UNKNOWN;

		if (!(data & PORT_START_CABLE_DIAG)) {
			len = data & PORT_CABLE_FAULT_COUNTER;
			if (len >= 22)
				len -= 22;
			else
				len = 0;
			len *= CABLE_LEN_MULTIPLIER;
			len += 5;
			len /= 10;
			port_info->length[i] = len;
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

	port_w16(sw, port, REG_PORT_PHY_1000_CTRL, giga);
	port_w16(sw, port, P_PHY_CTRL, ctrl);
	if (ctrl & PORT_AUTO_NEG_ENABLE) {
		ctrl |= PORT_AUTO_NEG_RESTART;
		port_w16(sw, port, P_NEG_RESTART_CTRL, ctrl);
	}

	port_info->length[0] = port_info->length[1];
	port_info->status[0] = port_info->status[1];
	for (i = 2; i < 5; i++) {
		if (CABLE_GOOD == port_info->status[0]) {
			if (port_info->status[i] != CABLE_GOOD) {
				port_info->status[0] = port_info->status[i];
				port_info->length[0] = port_info->length[i];
				break;
			}
		}
	}
}

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
	case PROC_GET_HOST_PORT:
		len += sprintf(buf + len, "%u\n", sw->HOST_PORT + 1);
		break;
	case PROC_GET_PORTS:
	{
		uint ports = sw->mib_port_cnt + 1;

		if (sw->eth_cnt)
			ports = sw->eth_maps[0].cnt + 1;
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
	case PROC_GET_AVB:
		len += sprintf(buf + len, "%u\n",
			!!(sw->features & AVB_SUPPORT));
		break;
	case PROC_GET_STP:
		len += sprintf(buf + len, "0\n");
		break;
	case PROC_GET_TWO_DEV:
		i = 0;
		if (2 == sw->dev_count && (sw->features & SW_VLAN_DEV))
			i = 1;
#ifdef CONFIG_KSZ_HSR
		if (sw->features & HSR_REDBOX)
			i = 2;
#endif
		len += sprintf(buf + len, "%d\n", i);
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
		len += sprintf(buf + len, "\t%08x = VLAN dev forwarding\n",
			SW_VLAN_DEV);
		len += sprintf(buf + len, "\t%08x = MRP support\n",
			MRP_SUPPORT);
		len += sprintf(buf + len, "\t%08x = Gigabit support\n",
			GIGABIT_SUPPORT);
		len += sprintf(buf + len, "\t%08x = IBA support\n",
			IBA_SUPPORT);
		len += sprintf(buf + len, "\t%08x = new capabilities\n",
			NEW_CAP);
		len += sprintf(buf + len, "\t%08x = AVB support\n",
			AVB_SUPPORT);
		len += sprintf(buf + len, "\t%08x = Redundancy support\n",
			REDUNDANCY_SUPPORT);
#ifdef CONFIG_KSZ_DLR
		len += sprintf(buf + len, "\t%08x = DLR support\n",
			DLR_HW);
#endif
#ifdef CONFIG_KSZ_HSR
		len += sprintf(buf + len, "\t%08x = HSR support\n",
			HSR_HW);
		len += sprintf(buf + len, "\t%08x = HSR RedBox support\n",
			HSR_REDBOX);
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
		len += sprintf(buf + len, "\t%08x = have >2 ports\n",
			HAVE_MORE_THAN_2_PORTS);
		len += sprintf(buf + len, "\t%08x = unknown mcast blocked\n",
			UNK_MCAST_BLOCK);
#ifdef CONFIG_KSZ_IBA
		len += sprintf(buf + len, "\t%08x = IBA test\n",
			IBA_TEST);
#endif
		len += sprintf(buf + len, "\t%08x = ACL intr monitor\n",
			ACL_INTR_MONITOR);
		len += sprintf(buf + len, "\t%08x = 802.1X Authentication\n",
			USE_802_1X_AUTH);
		len += sprintf(buf + len, "\t%08x = ptp tag\n",
			PTP_TAG);
		len += sprintf(buf + len, "\t%08x = tag is removed\n",
			TAG_REMOVE);
		len += sprintf(buf + len, "\t%08x = tail tagging\n",
			TAIL_TAGGING);
		break;
	case PROC_SET_AUTHEN:
		len += sprintf(buf + len, "%u\n",
			!!(sw->overrides & USE_802_1X_AUTH));
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
	case PROC_HSR:
#ifdef CONFIG_KSZ_HSR
		if (sw->features & HSR_HW)
			len = sw_d_hsr_table(sw, buf, len);
#endif
		break;
	}
	return len;
}  /* sysfs_sw_read */

static ssize_t sysfs_sw_read_hw(struct ksz_sw *sw, int proc_num, ssize_t len,
	char *buf)
{
	u8 data[8];
	u32 val;
	int chk = 0;
	int type = SHOW_HELP_ON_OFF;
	char note[40];

	note[0] = '\0';
	switch (proc_num) {
	case PROC_SET_AGING:
		chk = sw_chk(sw, REG_SW_LUE_CTRL_1, SW_AGING_ENABLE);
		break;
	case PROC_SET_FAST_AGING:
		chk = sw_chk(sw, REG_SW_LUE_CTRL_1, SW_FAST_AGING);
		break;
	case PROC_SET_LINK_AGING:
		chk = sw_chk(sw, S_LINK_AGING_CTRL, SW_LINK_AUTO_AGING);
		break;
	case PROC_SET_MULTICAST_STORM:
		chk = !sw_chk(sw, REG_SW_MAC_CTRL_1, MULTICAST_STORM_DISABLE);
		break;
	case PROC_SET_TX_RATE_QUEUE_BASED:
		chk = sw_chk(sw, REG_SW_MAC_CTRL_5,
			SW_OUT_RATE_LIMIT_QUEUE_BASED);
		break;
	case PROC_ENABLE_VLAN:
		chk = sw_chk(sw, REG_SW_LUE_CTRL_0, SW_VLAN_ENABLE);
		break;
	case PROC_SET_REPLACE_NULL_VID:
		chk = sw_chk(sw, S_REPLACE_VID_CTRL, SW_REPLACE_VID);
		break;
	case PROC_SET_DROP_INVALID_VID:
		chk = sw_chk(sw, REG_SW_LUE_CTRL_0, SW_DROP_INVALID_VID);
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
#ifdef SW_IPV6_MLD_SNOOP
	case PROC_SET_IPV6_MLD_SNOOP:
		chk = sw_chk(sw, S_MIRROR_CTRL, SW_IPV6_MLD_SNOOP);
		break;
	case PROC_SET_IPV6_MLD_OPTION:
		chk = sw_chk(sw, S_MIRROR_CTRL, SW_IPV6_MLD_OPTION);
		break;
#endif
	case PROC_SET_AGGR_BACKOFF:
		chk = sw_chk(sw, REG_SW_MAC_CTRL_0, SW_AGGR_BACKOFF);
		break;
	case PROC_SET_NO_EXC_DROP:
		chk = sw_chk(sw, REG_SW_MAC_CTRL_1, NO_EXC_COLLISION_DROP);
		break;
	case PROC_SET_VLAN_BOUNDARY:
		val = sw->reg->r32(sw, REG_SW_QM_CTRL__4);
		chk = !!(val & UNICAST_VLAN_BOUNDARY);
		break;
	case PROC_SET_DOUBLE_TAG:
		chk = sw_chk(sw, REG_SW_OPERATION, SW_DOUBLE_TAG);
		break;
	case PROC_SET_ISP_TAG:
		chk = sw->reg->r16(sw, REG_SW_ISP_TPID__2);
		type = SHOW_HELP_HEX_4;
		break;
	case PROC_SET_HSR_TAG:
		chk = sw->reg->r16(sw, REG_SW_HSR_TPID__2);
		type = SHOW_HELP_HEX_4;
		break;
	case PROC_SET_HSR_REDBOX_ID:
#ifdef CONFIG_KSZ_HSR
		if (sw->features & HSR_HW) {
			struct ksz_hsr_info *hsr = &sw->info->hsr;

			chk = hsr->ops->get_redbox_id(hsr);
		}
#endif
		type = SHOW_HELP_NUM;
		break;
	case PROC_SET_HSR_NET_ID:
#ifdef CONFIG_KSZ_HSR
		if (sw->features & HSR_HW) {
			struct ksz_hsr_info *hsr = &sw->info->hsr;

			chk = hsr->ops->get_net_id(hsr);
		}
#endif
		type = SHOW_HELP_NUM;
		break;
	case PROC_SET_MTU:
		chk = sw->reg->r16(sw, REG_SW_MTU__2);
		sw->mtu = chk;
		type = SHOW_HELP_NUM;
		break;
	case PROC_SET_FORWARD_UNKNOWN_UNICAST:
		val = sw->reg->r32(sw, REG_SW_LUE_UNK_UCAST_CTRL__4);
		chk = !!(val & SW_UNK_UCAST_ENABLE);
		break;
	case PROC_SET_UNKNOWN_UNICAST_PORTS:
		val = sw->reg->r32(sw, REG_SW_LUE_UNK_UCAST_CTRL__4);
		val &= ~SW_UNK_UCAST_ENABLE;
#ifdef USE_LOG_MASK
		val = get_log_mask_from_phy(sw, val);
#endif
		chk = val;
		type = SHOW_HELP_HEX;
		break;
	case PROC_SET_FORWARD_UNKNOWN_MULTICAST:
		val = sw->reg->r32(sw, REG_SW_LUE_UNK_MCAST_CTRL__4);
		chk = !!(val & SW_UNK_MCAST_ENABLE);
		break;
	case PROC_SET_UNKNOWN_MULTICAST_PORTS:
		val = sw->reg->r32(sw, REG_SW_LUE_UNK_MCAST_CTRL__4);
		val &= ~SW_UNK_MCAST_ENABLE;
#ifdef USE_LOG_MASK
		val = get_log_mask_from_phy(sw, val);
#endif
		chk = val;
		type = SHOW_HELP_HEX;
		break;
	case PROC_SET_FORWARD_UNKNOWN_VID:
		val = sw->reg->r32(sw, REG_SW_LUE_UNK_VID_CTRL__4);
		chk = !!(val & SW_UNK_VID_ENABLE);
		break;
	case PROC_SET_UNKNOWN_VID_PORTS:
		val = sw->reg->r32(sw, REG_SW_LUE_UNK_VID_CTRL__4);
		val &= ~SW_UNK_VID_ENABLE;
#ifdef USE_LOG_MASK
		val = get_log_mask_from_phy(sw, val);
#endif
		chk = val;
		type = SHOW_HELP_HEX;
		break;
	case PROC_SET_JUMBO_PACKET:
		chk = sw_chk(sw, REG_SW_MAC_CTRL_1, SW_JUMBO_PACKET);
		break;
	case PROC_SET_LEGAL_PACKET:
		chk = !sw_chk(sw, REG_SW_MAC_CTRL_1, SW_LEGAL_PACKET_DISABLE);
		break;
	case PROC_SET_LENGTH_CHECK:
		chk = sw_chk(sw, REG_SW_MAC_CTRL_0, SW_CHECK_LENGTH);
		break;
	case PROC_SET_BACK_PRESSURE_MODE:
		chk = sw_chk(sw, REG_SW_MAC_CTRL_1, SW_BACK_PRESSURE);
		break;
	case PROC_SET_FAIR_FLOW_CTRL:
		chk = sw_chk(sw, REG_SW_MAC_CTRL_1, FAIR_FLOW_CTRL);
		break;
	case PROC_SET_PASS_PAUSE:
		chk = sw_chk(sw, REG_SW_MAC_CTRL_4, SW_PASS_PAUSE);
		break;
	case PROC_ENABLE_PME:
		chk = sw_chk(sw, REG_SW_PME_CTRL, PME_ENABLE);
		break;
	case PROC_ENABLE_PME_POLARITY:
		chk = sw_chk(sw, REG_SW_PME_CTRL, PME_POLARITY);
		break;
	case PROC_SET_NO_COLOR:
		chk = sw_r_shift(sw, REG_SW_MRI_CTRL_8, SW_COLOR_M,
			SW_NO_COLOR_S);
		break;
	case PROC_SET_COLOR_RED:
		chk = sw_r_shift(sw, REG_SW_MRI_CTRL_8, SW_COLOR_M,
			SW_RED_COLOR_S);
		break;
	case PROC_SET_COLOR_YELLOW:
		chk = sw_r_shift(sw, REG_SW_MRI_CTRL_8, SW_COLOR_M,
			SW_YELLOW_COLOR_S);
		break;
	case PROC_SET_COLOR_GREEN:
		chk = sw_r_shift(sw, REG_SW_MRI_CTRL_8, SW_COLOR_M,
			SW_GREEN_COLOR_S);
		break;
	case PROC_SET_VLAN_FILTERING_DYNAMIC:
		chk = sw_chk(sw, REG_SW_LUE_CTRL_2, SW_EGRESS_VLAN_FILTER_DYN);
		break;
	case PROC_SET_VLAN_FILTERING_STATIC:
		chk = sw_chk(sw, REG_SW_LUE_CTRL_2, SW_EGRESS_VLAN_FILTER_STA);
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
		if (!(sw->features & GIGABIT_SUPPORT) && num == 1000)
			break;
		if (0 == num || 10 == num || 100 == num || 1000 == num)
			port->speed = (u16) num;
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
		if (num <= PHY_RX_ONLY)
			port->flow_ctrl = (u8) num;
		break;
	case PROC_SET_SW_MIB:
		if (num >= 1 && num <= 2) {
			sw_freeze_mib(sw, num - 1);
			break;
		}
		for (count = 0; count <= sw->mib_port_cnt; count++) {
			uint p = get_phy_port(sw, count);
			struct ksz_port_mib *mib = get_port_mib(sw, p);

			memset((void *) mib->counter, 0, sizeof(u64) *
				TOTAL_SWITCH_COUNTER_NUM);
			mib->rate[0].last = mib->rate[1].last = 0;
			mib->rate[0].last_cnt = mib->rate[1].last_cnt = 0;
			mib->rate[0].peak = mib->rate[1].peak = 0;
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
	case PROC_SET_AUTHEN:
		if (num)
			sw->overrides |= USE_802_1X_AUTH;
		else if (sw->overrides & USE_802_1X_AUTH) {
			struct ksz_acl_table *acl;
			int acl_on;
			int acl_rule;
			uint n;
			uint port;

			for (n = 1; n <= sw->mib_port_cnt; n++) {
				port = get_phy_port(sw, n);
				port_set_authen_mode(sw, port,
					PORT_AUTHEN_PASS);
				sw_cfg_port_base_vlan(sw, port, sw->PORT_MASK);

				acl_on = port_chk_acl(sw, port);
				if (!acl_on)
					port_cfg_acl(sw, port, true);
				acl_rule = 0;
				acl = &sw->info->port_cfg[port].
					acl_info[acl_rule];
				acl->ruleset = 0;
				sw->ops->release(sw);
				sw_w_acl_ruleset(sw, port, acl_rule, acl);
				sw->ops->acquire(sw);
				acl_rule++;
				acl++;
				acl->ruleset = 0;
				sw->ops->release(sw);
				sw_w_acl_ruleset(sw, port, acl_rule, acl);
				sw->ops->acquire(sw);
				acl_rule++;
				acl++;
				acl->ruleset = 0;
				sw->ops->release(sw);
				sw_w_acl_ruleset(sw, port, acl_rule, acl);
				sw->ops->acquire(sw);
				if (!acl_on)
					port_cfg_acl(sw, port, false);
			}
			sw->overrides &= ~USE_802_1X_AUTH;
		}
		break;
	case PROC_DYNAMIC:
		sw_flush_dyn_mac_table(sw, sw->port_cnt);
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
	case PROC_SET_TX_RATE_QUEUE_BASED:
		sw_cfg(sw, REG_SW_MAC_CTRL_5, SW_OUT_RATE_LIMIT_QUEUE_BASED,
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
		val = sw->reg->r32(sw, REG_SW_QM_CTRL__4);
		if (num)
			val |= UNICAST_VLAN_BOUNDARY;
		else
			val &= ~UNICAST_VLAN_BOUNDARY;
		sw->reg->w32(sw, REG_SW_QM_CTRL__4, val);
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
	case PROC_SET_HSR_REDBOX_ID:
#ifdef CONFIG_KSZ_HSR
		if (sw->features & HSR_HW) {
			struct ksz_hsr_info *hsr = &sw->info->hsr;

			if (0 <= num && num <= 7)
				hsr->ops->set_redbox_id(hsr, (u8) num);
		}
#endif
		break;
	case PROC_SET_HSR_NET_ID:
#ifdef CONFIG_KSZ_HSR
		if (sw->features & HSR_HW) {
			struct ksz_hsr_info *hsr = &sw->info->hsr;

			if (0 <= num && num <= 7)
				hsr->ops->set_net_id(hsr, (u8) num);
		}
#endif
		break;
	case PROC_SET_MTU:
		if (2000 <= num && num <= 9000) {
			sw->reg->w16(sw, REG_SW_MTU__2, (u16) num);
			sw->mtu = num;
		}
		break;
	case PROC_SET_FORWARD_UNKNOWN_UNICAST:
		sw_cfg(sw, REG_SW_LUE_UNK_UCAST_CTRL__4,
			SW_UNK_UCAST_ENABLE >> 24, num);
		break;
	case PROC_SET_UNKNOWN_UNICAST_PORTS:
		num &= ~SW_UNK_UCAST_ENABLE;
		val = sw->reg->r32(sw, REG_SW_LUE_UNK_UCAST_CTRL__4);
		val &= SW_UNK_UCAST_ENABLE;
#ifdef USE_LOG_MASK
		num = get_phy_mask_from_log(sw, num);
#endif
		val |= num;
		sw->reg->w32(sw, REG_SW_LUE_UNK_UCAST_CTRL__4, val);
		break;
	case PROC_SET_FORWARD_UNKNOWN_MULTICAST:
		sw_cfg(sw, REG_SW_LUE_UNK_MCAST_CTRL__4,
			SW_UNK_MCAST_ENABLE >> 24, num);
		if (num) {
			val = sw->reg->r32(sw, REG_SW_LUE_UNK_MCAST_CTRL__4);
			val &= ~SW_UNK_MCAST_ENABLE;
			if (val == sw->HOST_MASK)
				sw->overrides |= UNK_MCAST_BLOCK;
		} else {
			sw->overrides &= ~UNK_MCAST_BLOCK;
		}
		break;
	case PROC_SET_UNKNOWN_MULTICAST_PORTS:
		num &= ~SW_UNK_MCAST_ENABLE;
		val = sw->reg->r32(sw, REG_SW_LUE_UNK_MCAST_CTRL__4);
		val &= SW_UNK_MCAST_ENABLE;
#ifdef USE_LOG_MASK
		num = get_phy_mask_from_log(sw, num);
#endif
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
#ifdef USE_LOG_MASK
		num = get_phy_mask_from_log(sw, num);
#endif
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
	case PROC_SET_VLAN_FILTERING_DYNAMIC:
		sw_cfg(sw, REG_SW_LUE_CTRL_2, SW_EGRESS_VLAN_FILTER_DYN, num);
		break;
	case PROC_SET_VLAN_FILTERING_STATIC:
		sw_cfg(sw, REG_SW_LUE_CTRL_2, SW_EGRESS_VLAN_FILTER_STA, num);
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
	int i;
	int j;
	uint port;
	u32 map;
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
	case PROC_SET_MAC_OPERATIONAL:
		chk = !!(sw->dev_ports & (1 << port));
		type = SHOW_HELP_ON_OFF;
		break;
	case PROC_SET_VLAN_RESTRICTED:
		chk = port_cfg->restricted;
		if (sw->verbose)
			strcpy(note, " (0 = normal, 1 = restricted)");
		type = SHOW_HELP_SPECIAL;
		break;
	case PROC_SET_VLAN_UNTAGGED:
	{
		int index;
		int bit;

		index = sw->vlan_index / VID_IN_DATA;
		bit = sw->vlan_index % VID_IN_DATA;
		chk = !!(port_cfg->untagged[index] & (1 << bit));
		if (sw->verbose)
			strcpy(note, " (0 = tagged, 1 = untagged)");
		type = SHOW_HELP_SPECIAL;
		break;
	}
	case PROC_SET_PORT_MIB:
		port = get_log_port(sw, port);
		len += display_sw_mib_counters(sw, port, 1, buf + len);
		break;
	case PROC_SET_LINK_MD:
		len += sprintf(buf + len, "%u:%u %u:%u %u:%u %u:%u %u:%u\n",
			port_info->length[0], port_info->status[0],
			port_info->length[1], port_info->status[1],
			port_info->length[2], port_info->status[2],
			port_info->length[3], port_info->status[3],
			port_info->length[4], port_info->status[4]);
		if (sw->verbose)
			len += sprintf(buf + len,
				"(%d=unknown; %d=normal; %d=open; %d=short)\n",
				CABLE_UNKNOWN, CABLE_GOOD, CABLE_OPEN,
				CABLE_SHORT);
		break;
	case PROC_SET_SQI:
		chk = port_info->sqi;
		if (sw->verbose)
			strcpy(note, " (0 = worst, 15 = best)");
		type = SHOW_HELP_SPECIAL;
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
	case PROC_SET_LIMIT:
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
	case PROC_SET_LIMIT_PORT_BASED:
		chk = ((port_cfg->rate_limit >> PORT_IN_PORT_BASED_S) & 1);
		type = SHOW_HELP_ON_OFF;
		break;
	case PROC_SET_LIMIT_PACKET_BASED:
		chk = ((port_cfg->rate_limit >> PORT_RATE_PACKET_BASED_S) & 1);
		type = SHOW_HELP_ON_OFF;
		break;
	case PROC_SET_LIMIT_FLOW_CTRL:
		chk = ((port_cfg->rate_limit >> PORT_IN_FLOW_CTRL_S) & 1);
		type = SHOW_HELP_ON_OFF;
		break;
	case PROC_SET_LIMIT_CNT_IFG:
		chk = ((port_cfg->rate_limit >> PORT_COUNT_IFG_S) & 1);
		type = SHOW_HELP_ON_OFF;
		break;
	case PROC_SET_LIMIT_CNT_PRE:
		chk = ((port_cfg->rate_limit >> PORT_COUNT_PREAMBLE_S) & 1);
		type = SHOW_HELP_ON_OFF;
		break;
	case PROC_SET_RX_P0_RATE:
		len += sprintf(buf + len, "%u %s\n", (int)
			port_cfg->packet_based ?
			port_cfg->rx_packet[0] : port_cfg->rx_rate[0],
			port_cfg->packet_based ? "Kpps" : "Kbps");
		break;
	case PROC_SET_RX_P1_RATE:
		len += sprintf(buf + len, "%u %s\n", (int)
			port_cfg->packet_based ?
			port_cfg->rx_packet[1] : port_cfg->rx_rate[1],
			port_cfg->packet_based ? "Kpps" : "Kbps");
		break;
	case PROC_SET_RX_P2_RATE:
		len += sprintf(buf + len, "%u %s\n", (int)
			port_cfg->packet_based ?
			port_cfg->rx_packet[2] : port_cfg->rx_rate[2],
			port_cfg->packet_based ? "Kpps" : "Kbps");
		break;
	case PROC_SET_RX_P3_RATE:
		len += sprintf(buf + len, "%u %s\n", (int)
			port_cfg->packet_based ?
			port_cfg->rx_packet[3] : port_cfg->rx_rate[3],
			port_cfg->packet_based ? "Kpps" : "Kbps");
		break;
	case PROC_SET_RX_P4_RATE:
		len += sprintf(buf + len, "%u %s\n", (int)
			port_cfg->packet_based ?
			port_cfg->rx_packet[4] : port_cfg->rx_rate[4],
			port_cfg->packet_based ? "Kpps" : "Kbps");
		break;
	case PROC_SET_RX_P5_RATE:
		len += sprintf(buf + len, "%u %s\n", (int)
			port_cfg->packet_based ?
			port_cfg->rx_packet[5] : port_cfg->rx_rate[5],
			port_cfg->packet_based ? "Kpps" : "Kbps");
		break;
	case PROC_SET_RX_P6_RATE:
		len += sprintf(buf + len, "%u %s\n", (int)
			port_cfg->packet_based ?
			port_cfg->rx_packet[6] : port_cfg->rx_rate[6],
			port_cfg->packet_based ? "Kpps" : "Kbps");
		break;
	case PROC_SET_RX_P7_RATE:
		len += sprintf(buf + len, "%u %s\n", (int)
			port_cfg->packet_based ?
			port_cfg->rx_packet[7] : port_cfg->rx_rate[7],
			port_cfg->packet_based ? "Kpps" : "Kbps");
		break;
	case PROC_SET_TX_Q0_RATE:
		len += sprintf(buf + len, "%u %s\n", (int)
			port_cfg->packet_based ?
			port_cfg->tx_packet[0] : port_cfg->tx_rate[0],
			port_cfg->packet_based ? "Kpps" : "Kbps");
		break;
	case PROC_SET_TX_Q1_RATE:
		len += sprintf(buf + len, "%u %s\n", (int)
			port_cfg->packet_based ?
			port_cfg->tx_packet[1] : port_cfg->tx_rate[1],
			port_cfg->packet_based ? "Kpps" : "Kbps");
		break;
	case PROC_SET_TX_Q2_RATE:
		len += sprintf(buf + len, "%u %s\n", (int)
			port_cfg->packet_based ?
			port_cfg->tx_packet[2] : port_cfg->tx_rate[2],
			port_cfg->packet_based ? "Kpps" : "Kbps");
		break;
	case PROC_SET_TX_Q3_RATE:
		len += sprintf(buf + len, "%u %s\n", (int)
			port_cfg->packet_based ?
			port_cfg->tx_packet[3] : port_cfg->tx_rate[3],
			port_cfg->packet_based ? "Kpps" : "Kbps");
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
		chk = port_cfg->mmd_id;
		type = SHOW_HELP_HEX;
		break;
	case PROC_SET_MMD_REG:
		chk = port_cfg->mmd_reg;
		type = SHOW_HELP_HEX;
		break;
	}
	return sysfs_show(len, buf, type, chk, note, sw->verbose);
}  /* sysfs_port_read */

static ssize_t sysfs_port_read_hw(struct ksz_sw *sw, int proc_num, uint n,
	ssize_t len, char *buf)
{
	u16 val;
	uint port;
	struct ksz_port_cfg *cfg;
	int chk = 0;
	int type = SHOW_HELP_ON_OFF;
	char note[40];

	note[0] = '\0';
	port = get_sysfs_port(sw, n);
	cfg = get_port_cfg(sw, port);
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
	case PROC_ENABLE_VLAN_PRIO:
		chk = port_chk_vlan_prio(sw, port);
		break;
	case PROC_ENABLE_MAC_PRIO:
		chk = port_chk_mac_prio(sw, port);
		break;
	case PROC_ENABLE_ACL_PRIO:
		chk = port_chk_acl_prio(sw, port);
		break;
	case PROC_SET_HIGHEST_PRIO:
		chk = port_chk_highest_prio(sw, port);
		break;
	case PROC_SET_OR_PRIO:
		chk = port_chk_or_prio(sw, port);
		break;
	case PROC_ENABLE_PRIO_QUEUE:
		chk = port_get_prio_queue(sw, port);
		if (sw->verbose) {
			if (chk < 3)
				sprintf(note, " (%u)", (1 << chk));
			else
				strcpy(note, " (invalid)");
		}
		type = SHOW_HELP_SPECIAL;
		break;
	case PROC_SET_REPLACE_VID:
		chk = port_chk32(sw, port, REG_PORT_MTI_QUEUE_CTRL_0__4,
			MTI_PVID_REPLACE);
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
	case PROC_SET_DROP_NON_VLAN:
		chk = port_chk_drop_non_vlan(sw, port);
		break;
	case PROC_SET_DROP_TAG:
		chk = port_chk_drop_tag(sw, port);
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
	case PROC_SET_DIS_NON_VID:
		chk = port_chk_dis_non_vid(sw, port);
		break;
	case PROC_SET_INGRESS:
		chk = port_chk_in_filter(sw, port);
		break;
	case PROC_SET_MAC_BASED_802_1X:
		chk = port_chk(sw, port, REG_PORT_LUE_CTRL,
			PORT_MAC_BASED_802_1X);
		break;
	case PROC_SET_SRC_ADDR_FILTER:
		chk = port_chk(sw, port, REG_PORT_LUE_CTRL,
			PORT_SRC_ADDR_FILTER);
		break;
	case PROC_SET_VLAN_LOOKUP_0:
		chk = port_chk(sw, port, REG_PORT_LUE_CTRL,
			PORT_VLAN_LOOKUP_VID_0);
		break;
	case PROC_SET_MSTP:
		chk = port_chk_mstp(sw, port);
		type = SHOW_HELP_NUM;
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
	case PROC_SET_POWER:
		chk = port_chk_power(sw, port);
		break;
	case PROC_SET_BACK_PRESSURE:
		chk = port_chk_back_pressure(sw, port);
		break;
	case PROC_SET_FORCE_FLOW_CTRL:
		chk = port_chk_force_flow_ctrl(sw, port);
		break;
	case PROC_SET_PASS_ALL:
		chk = port_chk(sw, port, REG_PORT_MAC_CTRL_1, PORT_PASS_ALL);
		break;
	case PROC_SET_TAIL_TAG:
		chk = port_chk_tail_tag(sw, port);
		break;
	case PROC_SET_CUSTOM_VID:
	{
		u16 data;

		port_r16(sw, port, REG_PORT_CUSTOM_VID, &data);
		chk = data;
		type = SHOW_HELP_HEX_4;
		break;
	}
	case PROC_SET_SR_1_VID:
	{
		u16 data;

		port_r16(sw, port, REG_PORT_AVB_SR_1_VID, &data);
		chk = data;
		type = SHOW_HELP_HEX_4;
		break;
	}
	case PROC_SET_SR_2_VID:
	{
		u16 data;

		port_r16(sw, port, REG_PORT_AVB_SR_2_VID, &data);
		chk = data;
		type = SHOW_HELP_HEX_4;
		break;
	}
	case PROC_SET_SR_1_TYPE:
	{
		u16 data;

		port_r16(sw, port, REG_PORT_AVB_SR_1_TYPE, &data);
		chk = data;
		type = SHOW_HELP_HEX_4;
		break;
	}
	case PROC_SET_SR_2_TYPE:
	{
		u16 data;

		port_r16(sw, port, REG_PORT_AVB_SR_2_TYPE, &data);
		chk = data;
		type = SHOW_HELP_HEX_4;
		break;
	}
	case PROC_SET_PME_CTRL:
		chk = port_r_s(sw, port, REG_PORT_PME_CTRL, 7, 0);
		len += sprintf(buf + len, "%02x:\n", chk);
		len += sprintf(buf + len, "\t%02x = Magic Packet detect\n",
			PME_WOL_MAGICPKT);
		len += sprintf(buf + len, "\t%02x = link up detect\n",
			PME_WOL_LINKUP);
		len += sprintf(buf + len, "\t%02x = energy detect\n",
			PME_WOL_ENERGY);
		type = SHOW_HELP_NONE;
		break;
	case PROC_SET_PME_STATUS:
		chk = port_r_s(sw, port, REG_PORT_PME_STATUS, 7, 0);
		len += sprintf(buf + len, "%02x:\n", chk);
		len += sprintf(buf + len, "\t%02x = Magic Packet detect\n",
			PME_WOL_MAGICPKT);
		len += sprintf(buf + len, "\t%02x = link up detect\n",
			PME_WOL_LINKUP);
		len += sprintf(buf + len, "\t%02x = energy detect\n",
			PME_WOL_ENERGY);
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
	case PROC_SET_P_INDEX:
		chk = get_log_port(sw, cfg->p_index);
		if (chk > 0)
			chk--;
		else
			chk = sw->mib_port_cnt;
		type = SHOW_HELP_NUM;
		break;
	case PROC_SET_Q_INDEX:
		chk = cfg->q_index;
		type = SHOW_HELP_NUM;
		break;
	case PROC_SET_POLICE_PACKET_TYPE:
		len += sprintf(buf + len, "%u\n",
			port_get_police_packet_type(sw, port));
		type = SHOW_HELP_NONE;
		break;
	case PROC_SET_NON_DSCP_COLOR:
		len += sprintf(buf + len, "%u\n",
			port_get_non_dscp_color(sw, port));
		type = SHOW_HELP_NONE;
		break;
	case PROC_ENABLE_PORT_BASED_POLICING:
		len += sprintf(buf + len, "%u\n",
			port_chk_port_based_policing(sw, port));
		type = SHOW_HELP_NONE;
		break;
	case PROC_ENABLE_POLICE_DROP_ALL:
		chk = port_chk_police_drop_all(sw, port);
		break;
	case PROC_ENABLE_COLOR_MARK:
		chk = port_chk_color_mark(sw, port);
		break;
	case PROC_ENABLE_COLOR_REMAP:
		chk = port_chk_color_remap(sw, port);
		break;
	case PROC_ENABLE_DROP_SRP:
		chk = port_chk_drop_srp(sw, port);
		break;
	case PROC_ENABLE_COLOR_AWARE:
		chk = port_chk_color_aware(sw, port);
		break;
	case PROC_ENABLE_POLICE:
		chk = port_chk_police(sw, port);
		break;
	case PROC_SET_Q_CIR:
		port_cfg_index(sw, port, cfg->p_index, cfg->q_index);
		len += sprintf(buf + len, "%u\n",
			port_get_cir(sw, port));
		type = SHOW_HELP_NONE;
		break;
	case PROC_SET_Q_PIR:
		port_cfg_index(sw, port, cfg->p_index, cfg->q_index);
		len += sprintf(buf + len, "%u\n",
			port_get_pir(sw, port));
		type = SHOW_HELP_NONE;
		break;
	case PROC_SET_Q_CBS:
		port_cfg_index(sw, port, cfg->p_index, cfg->q_index);
		len += sprintf(buf + len, "%u\n",
			port_get_cbs(sw, port));
		type = SHOW_HELP_NONE;
		break;
	case PROC_SET_Q_PBS:
		port_cfg_index(sw, port, cfg->p_index, cfg->q_index);
		len += sprintf(buf + len, "%u\n",
			port_get_pbs(sw, port));
		type = SHOW_HELP_NONE;
		break;
	case PROC_SET_WRED_MAX_THRESHOLD:
		len += sprintf(buf + len, "%u\n",
			port_get_wred_max(sw, port));
		type = SHOW_HELP_NONE;
		break;
	case PROC_SET_WRED_MIN_THRESHOLD:
		len += sprintf(buf + len, "%u\n",
			port_get_wred_min(sw, port));
		type = SHOW_HELP_NONE;
		break;
	case PROC_SET_WRED_MULTIPLIER:
		len += sprintf(buf + len, "%u\n",
			port_get_wred_multiplier(sw, port));
		type = SHOW_HELP_NONE;
		break;
	case PROC_GET_WRED_AVG_SIZE:
		len += sprintf(buf + len, "%u\n",
			port_get_wred_avg_size(sw, port));
		type = SHOW_HELP_NONE;
		break;
	case PROC_SET_WRED_Q_MAX_THRESHOLD:
		port_cfg_index(sw, port, cfg->p_index, cfg->q_index);
		len += sprintf(buf + len, "%u\n",
			port_get_wred_q_max(sw, port));
		type = SHOW_HELP_NONE;
		break;
	case PROC_SET_WRED_Q_MIN_THRESHOLD:
		port_cfg_index(sw, port, cfg->p_index, cfg->q_index);
		len += sprintf(buf + len, "%u\n",
			port_get_wred_q_min(sw, port));
		type = SHOW_HELP_NONE;
		break;
	case PROC_SET_WRED_Q_MULTIPLIER:
		port_cfg_index(sw, port, cfg->p_index, cfg->q_index);
		len += sprintf(buf + len, "%u\n",
			port_get_wred_q_multiplier(sw, port));
		type = SHOW_HELP_NONE;
		break;
	case PROC_GET_WRED_Q_AVG_SIZE:
		port_cfg_index(sw, port, cfg->p_index, cfg->q_index);
		len += sprintf(buf + len, "%u\n",
			port_get_wred_q_avg_size(sw, port));
		type = SHOW_HELP_NONE;
		break;
	case PROC_SET_WRED_RANDOM_DROP:
		len += sprintf(buf + len, "%u\n",
			port_chk_wred_random_drop(sw, port));
		type = SHOW_HELP_NONE;
		break;
	case PROC_SET_WRED_DROP_GYR:
		len += sprintf(buf + len, "%u\n",
			port_chk_wred_drop_gyr(sw, port));
		type = SHOW_HELP_NONE;
		break;
	case PROC_SET_WRED_DROP_YR:
		len += sprintf(buf + len, "%u\n",
			port_chk_wred_drop_yr(sw, port));
		type = SHOW_HELP_NONE;
		break;
	case PROC_SET_WRED_DROP_R:
		len += sprintf(buf + len, "%u\n",
			port_chk_wred_drop_r(sw, port));
		type = SHOW_HELP_NONE;
		break;
	case PROC_SET_WRED_DROP_ALL:
		len += sprintf(buf + len, "%u\n",
			port_chk_wred_drop_all(sw, port));
		type = SHOW_HELP_NONE;
		break;
	case PROC_GET_WRED_PMON:
		port_cfg_index(sw, port, cfg->p_index, cfg->q_index);
		len += sprintf(buf + len, "%u\n",
			port_get_wred_pmon(sw, port));
		type = SHOW_HELP_NONE;
		break;
	case PROC_SET_QUEUE_SCHEDULING:
		chk = port_get_schedule_mode(sw, port, cfg->q_index);
		if (sw->verbose) {
			switch (chk) {
			case 0:
				strcpy(note, " (strict priority)");
				break;
			case 2:
				strcpy(note, " (WRR)");
				break;
			default:
				strcpy(note, " (invalid)");
			}
		}
		type = SHOW_HELP_SPECIAL;
		break;
	case PROC_SET_QUEUE_SHAPING:
		chk = port_get_shaping(sw, port, cfg->q_index);
		if (sw->verbose) {
			switch (chk) {
			case 0:
				strcpy(note, " (off)");
				break;
			case 1:
				strcpy(note, " (on)");
				break;
			case 2:
				strcpy(note, " (time aware)");
				break;
			default:
				strcpy(note, " (invalid)");
			}
		}
		type = SHOW_HELP_SPECIAL;
		break;
#ifdef MTI_PREEMPT_ENABLE
	case PROC_SET_PREEMPT:
		len += sprintf(buf + len, "%u\n",
			port_chk_preempt(sw, port, cfg->q_index));
		type = SHOW_HELP_NONE;
		break;
#endif
	case PROC_SET_TX_RATIO:
		chk = port_get_tx_ratio(sw, port, cfg->q_index);
		type = SHOW_HELP_NUM;
		break;
	case PROC_SET_CREDIT_HI_WATER_MARK:
		chk = port_get_hi_water_mark(sw, port, cfg->q_index);
		type = SHOW_HELP_NUM;
		break;
	case PROC_SET_CREDIT_LO_WATER_MARK:
		chk = port_get_lo_water_mark(sw, port, cfg->q_index);
		type = SHOW_HELP_NUM;
		break;
	case PROC_SET_CREDIT_INCREMENT:
		chk = port_get_increment(sw, port, cfg->q_index);
		type = SHOW_HELP_NUM;
		break;
	case PROC_SET_SRP:
		chk = port_get_srp(sw, port);
		if (sw->verbose) {
			switch (chk) {
			case 0:
				strcpy(note, " (off)");
				break;
			case 1:
				strcpy(note, " (insert SR_1 tag)");
				break;
			case 2:
				strcpy(note, " (insert SR_2 tag)");
				break;
			default:
				strcpy(note, " (invalid)");
			}
		}
		type = SHOW_HELP_SPECIAL;
		break;
	case PROC_SET_QM_DROP:
		len += sprintf(buf + len, "%u\n",
			port_get_qm_drop(sw, port));
		type = SHOW_HELP_NONE;
		break;
	case PROC_SET_QM_BURST_SIZE:
		len += sprintf(buf + len, "%u\n",
			port_get_qm_burst_size(sw, port));
		type = SHOW_HELP_NONE;
		break;
	case PROC_SET_QM_RESV_SPACE:
		len += sprintf(buf + len, "%u\n",
			port_get_qm_resv_space(sw, port));
		type = SHOW_HELP_NONE;
		break;
	case PROC_SET_QM_HI_WATER_MARK:
		len += sprintf(buf + len, "%u\n",
			port_get_qm_hi_water_mark(sw, port, cfg->q_index));
		type = SHOW_HELP_NONE;
		break;
	case PROC_SET_QM_LO_WATER_MARK:
		len += sprintf(buf + len, "%u\n",
			port_get_qm_lo_water_mark(sw, port, cfg->q_index));
		type = SHOW_HELP_NONE;
		break;
	case PROC_GET_QM_TX_USED:
		len += sprintf(buf + len, "%u\n",
			port_get_qm_tx_used(sw, port, cfg->q_index));
		type = SHOW_HELP_NONE;
		break;
	case PROC_GET_QM_TX_AVAIL:
		len += sprintf(buf + len, "%u\n",
			port_get_qm_tx_avail(sw, port, cfg->q_index));
		type = SHOW_HELP_NONE;
		break;
	case PROC_GET_QM_TX_CALCULATED:
		len += sprintf(buf + len, "%u\n",
			port_get_qm_tx_calculated(sw, port, cfg->q_index));
		type = SHOW_HELP_NONE;
		break;
	case PROC_GET_RX_FLOW_CTRL:
		chk = port_chk(sw, port, REG_PORT_STATUS_0,
			PORT_RX_FLOW_CTRL);
		break;
	case PROC_GET_TX_FLOW_CTRL:
		chk = port_chk(sw, port, REG_PORT_STATUS_0,
			PORT_TX_FLOW_CTRL);
		break;
	case PROC_SET_MMD_VAL:
		if (PHY_INTERFACE_MODE_SGMII == sw->port_info[port].interface)
			port_sgmii_r(sw, port, cfg->mmd_id, cfg->mmd_reg,
				&val, 1);
		else
			port_mmd_read(sw, port, cfg->mmd_id, cfg->mmd_reg,
				&val, 1);
		chk = val;
		type = SHOW_HELP_HEX_4;
		break;
	case PROC_SET_MAC_LOOPBACK:
		chk = port_chk_mac_loopback(sw, port);
		break;
	case PROC_SET_PHY_LOOPBACK:
		chk = port_chk_phy_loopback(sw, port);
		break;
	case PROC_SET_REMOTE_LOOPBACK:
		chk = port_chk_remote_loopback(sw, port);
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
	int count;
	uint m;
	uint port;
	unsigned int val;
	u16 mmd_val;
	int processed = true;
	struct ksz_port_cfg *cfg;
	struct ksz_port_info *port_info;

	port = get_sysfs_port(sw, n);
	port_info = get_port_info(sw, port);
	cfg = get_port_cfg(sw, port);
	switch (proc_num) {
	case PROC_SET_PORT_DUPLEX:
	case PROC_SET_PORT_SPEED:
		if (sw->HOST_PORT == port)
			break;
		if ((PROC_SET_PORT_DUPLEX == proc_num && num > 2) ||
		    (PROC_SET_PORT_SPEED == proc_num &&
		    num != 0 && num != 10 && num != 100 && num != 1000))
			break;
		if (!(sw->features & GIGABIT_SUPPORT) && num == 1000)
			break;

		if (!port_info->set_link_speed)
			break;
		if (PROC_SET_PORT_DUPLEX == proc_num)
			port_info->own_duplex = (u8) num;
		else
			port_info->own_speed = (u16) num;
		port_info->set_link_speed(sw, port, port_info->own_speed,
					  port_info->own_duplex,
					  port_info->own_flow_ctrl);
		break;
	case PROC_SET_MAC_OPERATIONAL:
#if 0
		if (sw->overrides & USE_802_1X_AUTH)
			break;
#endif
		m = BIT(port);
		count = sw->dev_ports & m;
		if (count && !num) {
			sw->dev_ports &= ~m;
			num = 1;
		} else if (!count && num) {
			if (sw->dev_count > 1)
				break;
			sw->dev_ports |= m;
			num = 2;
		} else
			num = 0;

#ifdef CONFIG_KSZ_MRP
		if (sw->features & MRP_SUPPORT) {
			struct mrp_info *mrp = &sw->mrp;

			if (2 == num) {
				mrp->rx_ports |= m;
				mrp->tx_ports |= m;
			} else if (1 == num) {
				mrp->rx_ports &= ~m;
				mrp->tx_ports &= ~m;
			}
		}
#endif
		break;
	case PROC_SET_VLAN_RESTRICTED:
		cfg->restricted = !!num;
		break;
	case PROC_SET_VLAN_UNTAGGED:
	{
		int bit;
		int index;

		index = sw->vlan_index / VID_IN_DATA;
		bit = sw->vlan_index % VID_IN_DATA;
		count = !!(cfg->untagged[index] & (1 << bit));
		if (count != !!num) {
			struct ksz_vlan_table vlan;

			if (num)
				cfg->untagged[index] |= (1 << bit);
			else
				cfg->untagged[index] &= ~(1 << bit);
			sw->ops->release(sw);
			if (!sw_r_vlan_table(sw, sw->vlan_index, &vlan)) {
				if (num)
					vlan.untag |= (1 << port);
				else
					vlan.untag &= ~(1 << port);
				sw_w_vlan_table(sw, sw->vlan_index, &vlan);
			}
			sw->ops->acquire(sw);
		}
		break;
	}
	case PROC_SET_PORT_MIB:
	{
		struct ksz_port_mib *mib = get_port_mib(sw, port);

		if (num >= 1 && num <= 2) {
			port_freeze_mib(sw, port, num - 1);
			break;
		}
		memset((void *) mib->counter, 0, sizeof(u64) *
			TOTAL_SWITCH_COUNTER_NUM);
		mib->rate[0].last = mib->rate[1].last = 0;
		mib->rate[0].last_cnt = mib->rate[1].last_cnt = 0;
		mib->rate[0].peak = mib->rate[1].peak = 0;
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
#ifdef USE_LOG_MASK
		num = get_phy_mask_from_log(sw, num);
#endif
		sw_cfg_port_base_vlan(sw, port, (u16) num);
		break;
	case PROC_ENABLE_PRIO_QUEUE:
		if (0 <= num && num <= 2)
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
		hw_cfg_rate_packet_based(sw, port, num);
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
		hw_set_rx_prio(sw, port);
		break;
	case PROC_SET_RX_P4_RATE:
		hw_cfg_rx_prio_rate(sw, port, 4, num);
		hw_set_rx_prio(sw, port);
		break;
	case PROC_SET_RX_P5_RATE:
		hw_cfg_rx_prio_rate(sw, port, 5, num);
		hw_set_rx_prio(sw, port);
		break;
	case PROC_SET_RX_P6_RATE:
		hw_cfg_rx_prio_rate(sw, port, 6, num);
		hw_set_rx_prio(sw, port);
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
	case PROC_SET_LINK_MD:
		sw_get_link_md(sw, port);
		break;
	case PROC_SET_SQI:
		port_chk_sqi(sw, port);
		break;
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
	case PROC_SET_MAC_BASED_802_1X:
		port_cfg(sw, port, REG_PORT_LUE_CTRL, PORT_MAC_BASED_802_1X,
			num);
		break;
	case PROC_SET_SRC_ADDR_FILTER:
		if (!num)
			sw->open_ports |= (1 << port);
		port_cfg(sw, port, REG_PORT_LUE_CTRL, PORT_SRC_ADDR_FILTER,
			num);
		if (num)
			sw->open_ports &= ~(1 << port);
		break;
	case PROC_SET_VLAN_LOOKUP_0:
		port_cfg(sw, port, REG_PORT_LUE_CTRL, PORT_VLAN_LOOKUP_VID_0,
			num);
		break;
	case PROC_SET_MSTP:
		port_cfg_mstp(sw, port, num);
		break;
	case PROC_SET_RX:
		port_cfg_rx_special(sw, port, num);
		break;
	case PROC_SET_TX:
		port_cfg_tx(sw, port, num);
		break;
	case PROC_SET_LEARN:
		port_cfg_dis_learn(sw, port, !num);
		if (!num)
			sw_flush_dyn_mac_table(sw, port);
		break;
	case PROC_SET_POWER:
		port_cfg_power(sw, port, num);
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
		if (num > PORT_AUTHEN_TRAP)
			break;
		if (num == PORT_AUTHEN_NORMAL)
			num = PORT_AUTHEN_PASS;
		port_set_authen_mode(sw, port, num);
		if (sw->overrides & USE_802_1X_AUTH)
			port_open(sw, port, PORT_AUTHEN_PASS == num);
		break;
	case PROC_SET_ACL:
		port_cfg_acl(sw, port, num);
		break;
	case PROC_SET_P_INDEX:
		if (0 <= num && num <= sw->mib_port_cnt)
			cfg->p_index = (u8) get_phy_port(sw, num + 1);
		break;
	case PROC_SET_Q_INDEX:
		if (0 <= num && num < PRIO_QUEUES)
			cfg->q_index = (u8) num;
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
		port_cfg_index(sw, port, cfg->p_index, cfg->q_index);
		port_set_cir(sw, port, num);
		break;
	case PROC_SET_Q_PIR:
		port_cfg_index(sw, port, cfg->p_index, cfg->q_index);
		port_set_pir(sw, port, num);
		break;
	case PROC_SET_Q_CBS:
		port_cfg_index(sw, port, cfg->p_index, cfg->q_index);
		port_set_cbs(sw, port, num);
		break;
	case PROC_SET_Q_PBS:
		port_cfg_index(sw, port, cfg->p_index, cfg->q_index);
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
		port_cfg_index(sw, port, cfg->p_index, cfg->q_index);
		port_set_wred_q_max(sw, port, num);
		break;
	case PROC_SET_WRED_Q_MIN_THRESHOLD:
		port_cfg_index(sw, port, cfg->p_index, cfg->q_index);
		port_set_wred_q_min(sw, port, num);
		break;
	case PROC_SET_WRED_Q_MULTIPLIER:
		port_cfg_index(sw, port, cfg->p_index, cfg->q_index);
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
	case PROC_SET_QUEUE_SCHEDULING:
		port_set_schedule_mode(sw, port, cfg->q_index, (u8) num);
		break;
	case PROC_SET_QUEUE_SHAPING:
		port_set_shaping(sw, port, cfg->q_index, (u8) num);
		break;
#ifdef MTI_PREEMPT_ENABLE
	case PROC_SET_PREEMPT:
		port_cfg_preempt(sw, port, cfg->q_index, num);
		break;
#endif
	case PROC_SET_TX_RATIO:
		port_set_tx_ratio(sw, port, cfg->q_index, (u8) num);
		break;
	case PROC_SET_CREDIT_HI_WATER_MARK:
		port_set_hi_water_mark(sw, port, cfg->q_index, (u16) num);
		break;
	case PROC_SET_CREDIT_LO_WATER_MARK:
		port_set_lo_water_mark(sw, port, cfg->q_index, (u16) num);
		break;
	case PROC_SET_CREDIT_INCREMENT:
		port_set_increment(sw, port, cfg->q_index, (u16) num);
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
		port_set_qm_hi_water_mark(sw, port, cfg->q_index, (u16) num);
		break;
	case PROC_SET_QM_LO_WATER_MARK:
		port_set_qm_lo_water_mark(sw, port, cfg->q_index, (u16) num);
		break;
	case PROC_SET_MMD_ID:
		cfg->mmd_id = (u16) num;
		break;
	case PROC_SET_MMD_REG:
		cfg->mmd_reg = (u16) num;
		break;
	case PROC_SET_MMD_VAL:
		mmd_val = (u16) num;
		if (PHY_INTERFACE_MODE_SGMII == sw->port_info[port].interface)
			port_sgmii_w(sw, port, cfg->mmd_id, cfg->mmd_reg,
				&mmd_val, 1);
		else
			port_mmd_write(sw, port, cfg->mmd_id, cfg->mmd_reg,
				&mmd_val, 1);
		break;
	case PROC_SET_MAC_LOOPBACK:
		port_cfg_mac_loopback(sw, port, num);
		break;
	case PROC_SET_PHY_LOOPBACK:
		port_cfg_phy_loopback(sw, port, num);
		break;
	case PROC_SET_REMOTE_LOOPBACK:
		port_cfg_remote_loopback(sw, port, num);
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
	u16 ports;

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
		ports = entry->ports;
#ifdef USE_LOG_MASK
		ports = get_log_mask_from_phy(sw, entry->ports);
#endif
		len += sprintf(buf + len, "0x%04x\n", ports);
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
		ports = entry->ports;
#ifdef USE_LOG_MASK
		ports = get_log_mask_from_phy(sw, ports);
#endif
		len += sprintf(buf + len,
			"%3x.%u: %02X:%02X:%02X:%02X:%02X:%02X  "
			"%04x  m:%u  ",
			sw->alu_index, sw->alu_type,
			entry->addr[0], entry->addr[1], entry->addr[2],
			entry->addr[3], entry->addr[4], entry->addr[5],
			ports, entry->mstp);
		if (2 == sw->alu_type)
			len += sprintf(buf + len,
				"t:%u  s:%u  d:%u  o:%u  %02x  [%u]\n",
				entry->prio, entry->src, entry->dst,
				entry->override, entry->fid,
				entry->dirty ? 2 : entry->valid);
		else
			len += sprintf(buf + len,
				"p:%u  s:%u  d:%u  o:%u  %u:%02x  [%u]\n",
				entry->prio, entry->src, entry->dst,
				entry->override, entry->use_fid, entry->fid,
				entry->dirty ? 2 : entry->valid);
		break;
	}
	return len;
}  /* sysfs_mac_read */

static int sysfs_mac_write(struct ksz_sw *sw, int proc_num, int num,
	const char *buf)
{
	struct ksz_mac_table *entry;
	u16 ports;
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
	int i;

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
			if (!entry->dirty) {
				sw_r_vlan_table(sw, sw->vlan_index, entry);
#ifdef USE_LOG_MASK
				entry->ports =
					get_log_mask_from_phy(sw, entry->ports);
#endif
			}
			sw->vlan_dirty = 0;
		}
		len += sprintf(buf + len,
			"%3x: 0x%03x  m:%x  p:%x  o:%u  %04x  %04x  [%u]\n",
			sw->vlan_index, entry->fid, entry->mstp, entry->prio,
			entry->option, entry->untag, entry->ports,
			entry->dirty ? 2 : entry->valid);
		break;
	case PROC_SET_VID_2_FID:
		len += sprintf(buf + len,
			"%03x=%02x\n", sw->vlan_index,
				sw->info->vid2fid[sw->vlan_index]);
		break;
	case PROC_SET_FID_2_MSTID:
		if (entry->fid) {
			len += sprintf(buf + len,
				"%02x=%u\n", entry->fid,
					sw->info->fid2mstid[entry->fid]);
			break;
		}
		for (i = 0; i < FID_ENTRIES; i++) {
			if ((i % 32) == 0)
				len += sprintf(buf + len,
					"%02x: ", i);
			len += sprintf(buf + len,
				"%u ", sw->info->fid2mstid[i]);
			if ((i % 32) == 31)
				len += sprintf(buf + len,
					"\n");
		}
		break;
	}
	return len;
}  /* sysfs_vlan_read */

static int sysfs_vlan_write(struct ksz_sw *sw, int proc_num, int num)
{
	struct ksz_vlan_table *entry;
	u16 ports;
	u16 untag;
	int processed = true;

	entry = &sw->info->vlan_entry;
	switch (proc_num) {
	case PROC_SET_VLAN_VALID:
		if (num)
			entry->valid = 1;
		else
			entry->valid = 0;
		ports = entry->ports;
		untag = entry->untag;
#ifdef USE_LOG_MASK
		entry->ports = get_phy_mask_from_log(sw, entry->ports);
		entry->untag = get_phy_mask_from_log(sw, entry->untag);
#endif
#ifdef CONFIG_KSZ_MRP
		if (sw->features & MRP_SUPPORT) {
			struct mrp_info *mrp = &sw->mrp;

			mrp->ops->setup_vlan(mrp, sw->vlan_index, entry);
		}
#endif
		sw_w_vlan_table(sw, sw->vlan_index, entry);
		entry->ports = ports;
		entry->untag = untag;
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
		if (0 <= num && num < FID_ENTRIES) {
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
	case PROC_SET_VID_2_FID:
		if (0 <= num && num < FID_ENTRIES) {
			sw->info->vid2fid[sw->vlan_index] = num;
			sw->info->fid_updated = 1;
		}
		break;
	case PROC_SET_FID_2_MSTID:
		if (0 <= num && num < NUM_OF_MSTI) {
			sw->info->fid2mstid[entry->fid] = num;
			sw->info->fid_updated = 1;
		}
		break;
	default:
		processed = false;
		break;
	}
	return processed;
}  /* sysfs_vlan_write */

#ifdef CONFIG_KSZ_HSR
static ssize_t sysfs_hsr_read(struct ksz_sw *sw, int proc_num, ssize_t len,
	char *buf)
{
	struct ksz_hsr_table *entry;
	u8 mac_addr[ETH_ALEN];
	u8 path_id;
	struct ksz_hsr_info *info = &sw->info->hsr;

	entry = &sw->info->hsr_entry;
	switch (proc_num) {
	case PROC_SET_HSR_VALID:
		len += sprintf(buf + len, "%u\n", entry->valid);
		break;
	case PROC_SET_HSR_AGE_CNT:
		len += sprintf(buf + len, "%u\n", entry->age_cnt);
		break;
	case PROC_SET_HSR_PATH_ID:
		len += sprintf(buf + len, "%x\n", entry->path_id >> 1);
		break;
	case PROC_SET_HSR_SRC_MAC_ADDR:
		len += sprintf(buf + len, "%02x:%02x:%02x:%02x:%02x:%02x\n",
			entry->src_mac[0], entry->src_mac[1],
			entry->src_mac[2], entry->src_mac[3],
			entry->src_mac[4], entry->src_mac[5]);
		break;
	case PROC_SET_HSR_INDEX:
		len += sprintf(buf + len, "0x%03x\n", sw->hsr_index);
		break;
	case PROC_SET_HSR_INFO:

		/* MAC address and path ID will be wiped out if emtpy entry. */
		memcpy(mac_addr, entry->src_mac, ETH_ALEN);
		path_id = entry->path_id;
		if (sw->hsr_dirty) {
			sw_r_hsr_table(sw, sw->hsr_index, entry);
			sw->hsr_dirty = 0;
		}
		len += sprintf(buf + len,
			"%3x: %02X:%02X:%02X:%02X:%02X:%02X - %x "
			" c:%u %04x:%04x %04x:%04x %04x:%04x [%u]\n",
			sw->hsr_index,
			entry->src_mac[0], entry->src_mac[1], entry->src_mac[2],
			entry->src_mac[3], entry->src_mac[4], entry->src_mac[5],
			entry->path_id >> 1, entry->age_cnt,
			entry->start_seq[0], entry->start_seq[1],
			entry->exp_seq[0], entry->exp_seq[1],
			entry->seq_cnt[0], entry->seq_cnt[1],
			entry->dirty ? 2 : entry->valid);

		memcpy(entry->src_mac, mac_addr, ETH_ALEN);
		entry->path_id = path_id;
		break;
	case PROC_GET_HSR_STATE:
		len += sprintf(buf + len,
			"%u %u:%u %u:%u\n", info->ring,
			info->p1_down, info->p2_down,
			info->p1_lost, info->p2_lost);
		break;
	}
	return len;
}  /* sysfs_hsr_read */

static int sysfs_hsr_write(struct ksz_sw *sw, int proc_num, int num,
	const char *buf)
{
	struct ksz_hsr_table *entry;
	int processed = true;

	entry = &sw->info->hsr_entry;
	switch (proc_num) {
	case PROC_SET_HSR_PATH_ID:
		if (0 <= num && num <= 7) {
			entry->path_id = num << 1;
			if (!sw->hsr_index)
				sw->hsr_dirty = 1;
		}
		break;
	case PROC_SET_HSR_AGE_CNT:
		if (0 <= num && num <= 3) {
			entry->age_cnt = num;
			entry->dirty = 1;
		}
		break;
	case PROC_SET_HSR_VALID:
		if (num)
			entry->valid = 1;
		else
			entry->valid = 0;
		sw_w_hsr_table(sw, sw->hsr_index, entry);
		break;
	case PROC_SET_HSR_SRC_MAC_ADDR:
	{
		int i;
		int n[6];

		i = sscanf(buf, "%x:%x:%x:%x:%x:%x",
			&n[0], &n[1], &n[2], &n[3], &n[4], &n[5]);
		if (6 == i) {
			for (i = 0; i < 6; i++)
				entry->src_mac[i] = (u8) n[i];
			if (!sw->hsr_index)
				sw->hsr_dirty = 1;
		}
		break;
	}
	case PROC_SET_HSR_INDEX:
		if (0 <= num && num < 0x200) {
			sw->hsr_index = num;
			sw->hsr_dirty = 1;
		}
		break;
	case PROC_SET_HSR_INFO:
		sw->hsr_dirty = 1;
		entry->dirty = 0;
		break;
	default:
		processed = false;
		break;
	}
	return processed;
}  /* sysfs_hsr_write */
#endif

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
#ifdef USE_LOG_MASK
		chk = get_log_mask_from_phy(sw, chk);
#endif
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
		len += acl_action_info(sw, action, cfg->acl_act_index, buf,
				       len);
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
		if (0 <= num && num <= KS_PRIO_M) {
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
		if (0 <= num && num <= KS_PRIO_M) {
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
#ifdef USE_LOG_MASK
			num = get_phy_mask_from_log(sw, num);
#endif
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

static void sw_cfg_mac(struct ksz_sw *sw, u8 index, const u8 *dest, u32 ports,
	int override, int use_fid, u16 fid)
{
	struct ksz_mac_table mac;

	memset(&mac, 0, sizeof(struct ksz_mac_table));
	memcpy(mac.addr, dest, ETH_ALEN);
	mac.ports = ports & sw->PORT_MASK;
	mac.override = override;
	mac.use_fid = use_fid;
	mac.fid = fid;
	mac.valid = ports != 0;
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
	if (sw_r_vlan_table(sw, vid, &vlan)) {
		memset(&vlan, 0, sizeof(struct ksz_vlan_table));
		vlan.vid = vid;
		vlan.fid = fid;
	}
	vlan.ports = ports & sw->PORT_MASK;
	vlan.valid = ports != 0;
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

static u16 sw_alloc_fid(struct ksz_sw *sw, u16 vid)
{
#if 0
	int x;
	int y;
	u16 fid;

	if (sw->info->fid_cnt + 2 == FID_ENTRIES)
		return 0;
	fid = vid & (FID_ENTRIES - 1);
	if (vid < 2)
		fid = 1000;
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
#else
	return sw->info->vid2fid[vid];
#endif
}  /* sw_alloc_fid */

static void sw_free_fid(struct ksz_sw *sw, u16 fid)
{
#if 0
	int x;
	int y;

	x = fid / FID_IN_DATA;
	y = fid % FID_IN_DATA;
	if (sw->info->fid[x] & (1 << y)) {
		sw->info->fid[x] &= ~(1 << y);
		--sw->info->fid_cnt;
	}
#endif
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

enum {
	KSZ9897_SW_CHIP,
	KSZ9567_SW_CHIP,
	KSZ9477_SW_CHIP,
	KSZ9896_SW_CHIP,
	KSZ9566_SW_CHIP,
	KSZ8567_SW_CHIP,
	KSZ8565_SW_CHIP,
	KSZ9893_SW_CHIP,
	KSZ9563_SW_CHIP,
	KSZ8563_SW_CHIP,
};

static int sw_get_id(struct ksz_sw *sw, u8 *id1, u8 *id2, char *name)
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
	if (sw->chip_id == KSZ9897_SW_CHIP)
		strcat(name, "9897");
	else if (sw->chip_id == KSZ9567_SW_CHIP)
		strcat(name, "9567");
	else if (sw->chip_id == KSZ9477_SW_CHIP)
		strcat(name, "9477");
	else if (sw->chip_id == KSZ9896_SW_CHIP)
		strcat(name, "9896");
	else if (sw->chip_id == KSZ9566_SW_CHIP)
		strcat(name, "9566");
	else if (sw->chip_id == KSZ8567_SW_CHIP)
		strcat(name, "8567");
	else if (sw->chip_id == KSZ8565_SW_CHIP)
		strcat(name, "8565");
	else if (sw->chip_id == KSZ9893_SW_CHIP)
		strcat(name, "9893");
	else if (sw->chip_id == KSZ9563_SW_CHIP)
		strcat(name, "9563");
	else if (sw->chip_id == KSZ8563_SW_CHIP)
		strcat(name, "8563");
	else
		strcat(name, "98xx");
	return id;
}  /* sw_get_id */

static void sw_cfg_tail_tag(struct ksz_sw *sw, bool enable)
{
	port_cfg_tail_tag(sw, sw->HOST_PORT, enable);
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

static void sw_cfg_src_filter(struct ksz_sw *sw, bool set)
{
	uint m;
	uint n;
	uint p;

	if (!(sw->features & NEW_CAP))
		return;
	for (n = 1; n <= sw->mib_port_cnt; n++) {
		p = get_phy_port(sw, n);
		m = get_phy_mask(sw, n);
		if (!set)
			sw->open_ports |= m;
		port_cfg(sw, p, REG_PORT_LUE_CTRL, PORT_SRC_ADDR_FILTER, set);
		if (set)
			sw->open_ports &= ~m;
	}
}  /* sw_cfg_src_filter */

static void sw_fwd_unk_mcast(struct ksz_sw *sw, bool set)
{
	if (set) {
		sw->reg->w32(sw, REG_SW_LUE_UNK_MCAST_CTRL__4,
			sw->HOST_MASK | SW_UNK_MCAST_ENABLE);
		sw->overrides |= UNK_MCAST_BLOCK;
	} else {
		sw_cfg(sw, REG_SW_LUE_UNK_MCAST_CTRL__4,
			SW_UNK_MCAST_ENABLE >> 24, false);
		sw->overrides &= ~UNK_MCAST_BLOCK;
	}
}  /* sw_fwd_unk_mcast */

static void sw_fwd_unk_ucast(struct ksz_sw *sw)
{
	sw->reg->w32(sw, REG_SW_LUE_UNK_UCAST_CTRL__4,
		sw->HOST_MASK | SW_UNK_UCAST_ENABLE);
}  /* sw_fwd_unk_ucast */

static void sw_fwd_unk_vid(struct ksz_sw *sw)
{
	sw->reg->w32(sw, REG_SW_LUE_UNK_VID_CTRL__4,
		sw->HOST_MASK | SW_UNK_VID_ENABLE);
}  /* sw_fwd_unk_vid */

static int sw_need_dest(struct ksz_sw *sw, u8 *addr)
{
	int need = 0;

	if (addr[0] & 0x01) {
		int i;
		struct ksz_mac_table *entry;
		struct ksz_alu_table *alu;

		for (i = MULTI_MAC_TABLE_ENTRIES - 1; i >= 0; i--) {
			alu = &sw->info->alu_table[i];
			entry = &sw->info->mac_table[i];
			if (alu->valid &&
			    !memcmp(addr, entry->addr, ETH_ALEN)) {
				if (alu->forward & FWD_HOST)
					need = 1;
				if (alu->forward & FWD_HOST_OVERRIDE)
					need = 2;
				break;
			}
		}
		if (i < 0 && (sw->overrides & UNK_MCAST_BLOCK))
			need = 1;
	} else if (!memcmp(addr, sw->info->mac_addr, ETH_ALEN))
		need = 1;
	return need;
}  /* sw_need_dest */

static void sw_forward(struct ksz_sw *sw, u8 *addr, u8 *self, u16 proto,
	int tag)
{
	int forward = 0;

	/* Already set for PTP message. */
	if (sw->info->forward)
		return;

	/* Check for multicast addresses that are not forwarding. */
	if (addr[0] & 0x01) {
		int i;
		struct ksz_mac_table *entry;
		struct ksz_alu_table *alu;

		for (i = MULTI_MAC_TABLE_ENTRIES - 1; i >= 0; i--) {
			alu = &sw->info->alu_table[i];
			entry = &sw->info->mac_table[i];
			if (alu->valid &&
			    !memcmp(addr, entry->addr, ETH_ALEN)) {
				forward = alu->forward;
				if (!(forward & FWD_VLAN_DEV)) {
					if (proto == 0x888E)
						forward = FWD_STP_DEV |
							  FWD_VLAN_DEV;
				}
				break;
			}
		}
		if (!forward)
			forward = FWD_MAIN_DEV | FWD_MCAST;

	/* Check unicast address to host. */
	} else if (!memcmp(addr, self, ETH_ALEN))
		forward = FWD_HOST;
	else
		forward = FWD_MAIN_DEV | FWD_UCAST;
	if (!tag)
		forward &= ~FWD_VLAN_DEV;
	sw->info->forward = forward;
}  /* sw_forward */

static void sw_tx_fwd(struct work_struct *work)
{
	int rc;
	bool last;
	struct sk_buff *skb;
	struct ksz_sw *sw = container_of(work, struct ksz_sw, tx_fwd);
	const struct net_device_ops *ops = sw->main_dev->netdev_ops;

	last = skb_queue_empty(&sw->txq);
	while (!last) {
		skb = skb_dequeue(&sw->txq);
		last = skb_queue_empty(&sw->txq);
		if (!skb)
			continue;
		do {
			rc = ops->ndo_start_xmit(skb, skb->dev);
			if (NETDEV_TX_BUSY == rc) {
				rc = wait_event_interruptible_timeout(sw->queue,
					!netif_queue_stopped(sw->main_dev),
					50 * HZ / 1000);

				rc = NETDEV_TX_BUSY;
			}
		} while (NETDEV_TX_BUSY == rc);
	}
}  /* sw_tx_fwd */

#if 1
static u8 last_addr[6];
#endif

static struct net_device *sw_rx_dev(struct ksz_sw *sw, u8 *data, u32 *len,
	int *tag, int *port)
{
	u16 proto;
	u16* proto_loc;
	struct net_device *dev;
	struct ethhdr *eth = (struct ethhdr *) data;
	struct vlan_ethhdr *vlan = (struct vlan_ethhdr *) data;
	int index = -1;
	int vid = 0;
	u16 prio = 0;
#ifdef CONFIG_KSZ_DSA
	u32 org_len = *len;
#endif

	proto_loc = &vlan->h_vlan_proto;
	proto = htons(*proto_loc);
	if (eth->h_proto == htons(ETH_P_8021Q)) {
		u16 vlan_tci = ntohs(vlan->h_vlan_TCI);

		vid = vlan_tci & VLAN_VID_MASK;
		prio = vlan_tci & VLAN_PRIO_MASK;
		prio >>= VLAN_PRIO_SHIFT;
		proto_loc = &vlan->h_vlan_encapsulated_proto;
		proto = htons(*proto_loc);
#if 0
dbg_msg(" 1 vid: %x %d %04x\n", vlan_tci, vid, proto);
#endif
		if (vlan->h_vlan_encapsulated_proto == htons(ETH_P_8021Q)) {
			unsigned char *ptr = (unsigned char *) vlan;
			u16 vlan_tci = ntohs(vlan->h_vlan_TCI);

			ptr += VLAN_HLEN;
dbg_msg(" 2 vid: %x\n", vlan_tci);
		}
	}
#ifdef CONFIG_KSZ_HSR
	if (proto == ETH_P_HSR) {
		proto_loc += HSR_HLEN / 2;
		proto = htons(*proto_loc);
	}
#endif

#if 1
/*
 * THa  2016/02/03
 * A company switch is sending frames that causes the dropped count to
 * increase.
 */
	if (proto == 0x8874 &&
	    0x01 == vlan->h_source[0] &&
	    0x80 == vlan->h_source[1] &&
	    0xc2 == vlan->h_source[2] &&
	    0xff == vlan->h_dest[0]) {
		return NULL;
	}
#endif
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
	sw->info->forward = 0;

	/* Get received port number. */
	if (sw->overrides & TAIL_TAGGING) {
		(*len)--;
		*tag = data[*len];
		sw->tag.timestamp = 0;
		sw->tag.ports = *tag;
		if (*tag & 0x80) {
			u32 rx_ts;

			memcpy(&rx_ts, &data[*len - 4], 4);
			rx_ts = ntohl(rx_ts);
			sw->tag.timestamp = rx_ts;
			(*len) -= 4;

#ifdef CONFIG_1588_PTP
			/* PTP message cannot be forwarded normally. */
			if (sw->features & PTP_HW) {
				struct ptp_info *ptp = &sw->ptp_hw;

				sw->info->forward = ptp->forward;
			} else
#endif
			if (sw->features & SW_VLAN_DEV)
				sw->info->forward = FWD_VLAN_DEV;
			else
				sw->info->forward = FWD_MAIN_DEV;
		}
		*tag &= ~0x80;

		/* In case tagging is not working right. */
		if (*tag >= sw->port_cnt)
			*tag = 0;
		index = sw->info->port_cfg[*tag].index;

#ifdef CONFIG_KSZ_HSR
		/* Always use HSR device for communication. */
		if (sw->features & HSR_REDBOX) {
			struct ksz_hsr_info *info = &sw->info->hsr;

			index = info->hsr_index;
		}
#endif

		/* Save receiving port. */
		*port = *tag;
	}
#ifdef CONFIG_KSZ_IBA
	if (proto == IBA_TAG_TYPE)
		return sw->netdev[0];
#endif

#ifdef CONFIG_KSZ_DSA
	/* DSA has its function to read the tail tag. */
	if (sw->features & DSA_SUPPORT) {
		*len = org_len;
		return sw->netdev[0];
	}
#endif

	/* Determine network device from VLAN id. */
	if (index < 0) {
		index = 0;
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
	*tag = get_log_port(sw, *tag);
	if (!(sw->features & VLAN_PORT_TAGGING) ||
	    !(sw->vlan_id & (1 << *tag))) {
		*tag = 0;
	}
	sw_forward(sw, data, dev->dev_addr, proto, *tag);
#ifdef CONFIG_KSZ_MRP
	if (proto == 0x22F0)
		mrp_proc_proto(&sw->mrp, data, *port);
#endif
	if ((sw->overrides & UNK_MCAST_BLOCK) &&
	    (sw->info->forward & (FWD_MCAST | FWD_KNOWN)) == FWD_MCAST) {
		struct sk_buff *skb;
		u16 ports = sw->PORT_MASK & ~(1 << *port) & ~sw->HOST_MASK;

		ports &= sw->live_ports;
		if (!ports)
			return dev;
		if (memcmp(data, ipv6_neigh_mcast, 3)) {
			if (memcmp(data, last_addr, 6)) {
dbg_msg("%02x:%02x:%02x:%02x:%02x:%02x  %d=%d %x\n",
data[0], data[1], data[2], data[3], data[4], data[5], *port, *len, ports);
				memcpy(last_addr, data, 6);
			}
		}
#ifdef CONFIG_KSZ_MRP
		/* Do not forward IPv6 packets as the test tool confuses them
		 * for AVB traffic.
		 */
		else if ((sw->features & MRP_SUPPORT) && fqtss_hack)
			return dev;
		if (memcmp(data, ipv6_neigh_mcast, 3) &&
		    (sw->features & MRP_SUPPORT)) {
			int rc;

			rc = mrp_chk_mcast(&sw->mrp, vlan->h_dest, vid, prio,
					   proto, *port);
			if (rc != 1)
				return dev;
		}
#endif
		skb = alloc_skb(*len + 8, GFP_ATOMIC);
		if (!skb)
			return dev;
		skb->dev = sw->main_dev;
		skb_reset_network_header(skb);
		skb_reset_transport_header(skb);
		memcpy(skb->data, data, *len);
		skb_put(skb, *len);
		sw->net_ops->add_tail_tag(sw, skb, ports);
		skb->protocol = htons(ETH_P_TRAILER);

		skb_queue_tail(&sw->txq, skb);
		schedule_work(&sw->tx_fwd);
	}
	return dev;
}  /* sw_rx_dev */

static int pkt_matched(struct ksz_sw *sw, struct sk_buff *skb,
	struct net_device *dev, void *ptr, int (*get_multi)(void *ptr),
	u8 h_promiscuous)
{
	int drop = false;
	u8 bcast_addr[] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };

	if (skb->data[0] & 0x01) {
		if (memcmp(skb->data, bcast_addr, ETH_ALEN) && !get_multi(ptr))
			drop = sw_match_multi(sw,
				sw->net_ops->get_priv_port(dev), skb->data);
	} else if (h_promiscuous && memcmp(skb->data, dev->dev_addr, ETH_ALEN))
		drop = true;
	if (drop)
		return 0;
	return skb->len;
}  /* pkt_matched */

static int sw_match_pkt(struct ksz_sw *sw, struct net_device **dev,
	void **priv, int (*get_promiscuous)(void *ptr),
	int (*get_multi)(void *ptr), struct sk_buff *skb,
	u8 h_promiscuous)
{
	int s_promiscuous;

	/* This function will return the child device if matched, and the
	 * parent device if it is matched.
	 */
	if (sw->dev_count <= 1)
		return true;
	s_promiscuous = get_promiscuous(*priv);
	if (!s_promiscuous && !pkt_matched(sw, skb, *dev, *priv, get_multi,
	    h_promiscuous)) {
		int matched = false;

		/* There is a parent network device. */
		if (sw->dev_offset) {
			matched = true;
			*dev = sw->netdev[0];
			*priv = netdev_priv(*dev);
			s_promiscuous = get_promiscuous(*priv);
			if (!s_promiscuous && !pkt_matched(sw, skb, *dev,
			    *priv, get_multi, h_promiscuous))
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
			*forward = FWD_MAIN_DEV;
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

#if 0
	/* tag never equals sw->HOST_PORT + 1. */
if (tag == sw->HOST_PORT + 1)
BUG();
	if (tag > sw->HOST_PORT)
		--tag;
#endif
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

static int sw_drv_rx(struct ksz_sw *sw, struct sk_buff *skb, uint port)
{
	int ret = 1;

#ifdef CONFIG_KSZ_IBA
	if (sw->features & IBA_SUPPORT) {
		ret = iba_rcv(&sw->info->iba, skb);
		if (!ret)
			return ret;

#ifdef CONFIG_KSZ_IBA_ONLY
		if (2 == sw->info->iba.use_iba) {
			dev_kfree_skb_irq(skb);
			return 0;
		}
#endif
	}
#endif
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
#ifdef CONFIG_KSZ_HSR
	if (sw->features & HSR_HW) {
		ret = hsr_rcv(&sw->info->hsr, skb, port);

		/* It is an HSR frame or consumed. */
		if (ret < 2)
			return ret;
		if (sw->features & HSR_REDBOX) {
			ret = hsr_chk(&sw->info->hsr, skb, port);
			if (ret < 2)
				return ret;
		}
	}
#endif

	/* Need to remove VLAN tag if not using tail tag. */
	if (sw->dev_count > 1 && (sw->features & SW_VLAN_DEV) &&
	    !(sw->overrides & TAIL_TAGGING)) {
		struct vlan_ethhdr *vlan = (struct vlan_ethhdr *) skb->data;

		if (vlan->h_vlan_proto == htons(ETH_P_8021Q)) {
			int i;
			int vid;
			struct ethhdr *eth;
			u16 vlan_tci = ntohs(vlan->h_vlan_TCI);

			vid = vlan_tci & VLAN_VID_MASK;
			for (i = 0; i < sw->eth_cnt; i++) {
				if (vid == sw->eth_maps[i].vlan) {
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

	if (sw->features & (PTP_HW | DLR_HW | HSR_HW))
		need_tail_tag = true;
	if (sw->dev_count > 1 && !(sw->features & SW_VLAN_DEV))
		need_tail_tag = true;
	if (sw->features & VLAN_PORT_TAGGING)
		need_tail_tag = true;
	if (sw->features & (STP_SUPPORT | DSA_SUPPORT))
		need_tail_tag = true;
	if (need_tail_tag) {
		mtu += 2;
		if (sw->TAIL_TAG_SHIFT != 7)
			mtu -= 1;
		if (sw->features & PTP_HW)
			mtu += 4;
	}
#ifdef CONFIG_KSZ_HSR
	if (sw->features & HSR_HW)
		header = HSR_HLEN;
#endif
	if (sw->features & SW_VLAN_DEV)
		if (header < VLAN_HLEN)
			header = VLAN_HLEN;
	mtu += header;
dbg_msg("mtu: %d\n", mtu);
	return mtu;
}  /* sw_get_mtu */

static int sw_get_tx_len(struct ksz_sw *sw, struct sk_buff *skb, uint port,
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
	len += 2;
	if (sw->overrides & PTP_TAG)
		len += 4;
	return len;
}  /* sw_get_tx_len */

static void sw_add_tail_tag(struct ksz_sw *sw, struct sk_buff *skb, uint ports)
{
	struct ksz_sw_tx_tag tx_tag;
	u8 *trailer;
	u8 *tag;
	int len = 2;
	int ptp_len = 0;
	bool override = !!(ports & TAIL_TAG_SET_OVERRIDE);
	bool queue = !!(ports & TAIL_TAG_SET_QUEUE);

	/* PTP is enabled and so requires extra 4 bytes. */
	if (sw->overrides & PTP_TAG)
		ptp_len = 4;
	len += ptp_len;
	if (sw->TAIL_TAG_SHIFT != 7)
		len--;
	trailer = skb_put(skb, len);
	memset(&tx_tag, 0, sizeof(struct ksz_sw_tx_tag));
	tx_tag.ports = ports & sw->PORT_MASK;
	if (!tx_tag.ports)
		tx_tag.ports = sw->TAIL_TAG_LOOKUP;
	else if (override)
		tx_tag.ports |= sw->TAIL_TAG_OVERRIDE;
	if (queue)
		tx_tag.ports |= sw->ctrl_queue << sw->TAIL_TAG_SHIFT;
	tx_tag.ports = htons(tx_tag.ports);
	tag = (u8 *) &tx_tag;
	memcpy(trailer, &tag[4 - ptp_len], ptp_len + 2);
	if (sw->TAIL_TAG_SHIFT != 7)
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

static void sw_add_vid(struct ksz_sw *sw, u16 vid)
{
	if ((sw->features & VLAN_PORT) && vid >= VLAN_PORT_START) {
		vid -= VLAN_PORT_START;
		if (vid <= SWITCH_PORT_NUM) {
			sw->vlan_id |= (1 << vid);
		}
	}
}  /* sw_add_vid */

static void sw_kill_vid(struct ksz_sw *sw, u16 vid)
{
	if ((sw->features & VLAN_PORT) && vid >= VLAN_PORT_START) {
		vid -= VLAN_PORT_START;
		if (vid <= SWITCH_PORT_NUM) {
			sw->vlan_id &= ~(1 << vid);
		}
	}
}  /* sw_kill_vid */

static int append_tag(u16 shift, u8 *pad, u8 *tag, int len, int ptp_len,
	int addlen)
{
	memcpy(&pad[len], &tag[4 - ptp_len], ptp_len + 2);

	/* Only one byte for the tag. */
	if (shift != 7) {
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

static struct sk_buff *sw_ins_vlan(struct ksz_sw *sw, uint port,
	struct sk_buff *skb)
{
#ifdef CONFIG_KSZ_IBA
	if (skb->protocol == htons(ETH_P_IBA))
		return skb;
#endif
#if 0
	port = get_phy_port(sw, port);
#endif
	port = sw->priv_port;

	/* Need to insert VLAN tag. */
	if (sw->dev_count > 1 && (sw->features & SW_VLAN_DEV)) {
		u16 vid;
		struct vlan_ethhdr *vlan;
		struct ethhdr *eth;
		struct sk_buff *nskb = NULL;
#if 0
		int i = sw->info->port_cfg[port].index;
#endif

		/*
		 * Bridge uses clones of socket buffer to send to both
		 * devices!
		 */
#ifdef CONFIG_KSZ_HSR
		if (sw->features & HSR_REDBOX)
			nskb = skb;
#endif
		if (!nskb) {
			nskb = skb_copy(skb, GFP_ATOMIC);
			if (!nskb)
				return skb;
			dev_kfree_skb_irq(skb);
			skb = nskb;
		}
		eth = (struct ethhdr *) skb->data;
#if 0
		if (sw->eth_cnt && (sw->eth_maps[i].proto & (DLR_HW)))
			memcpy(eth->h_source, sw->info->mac_addr, ETH_ALEN);
#endif

		vid = sw->info->port_cfg[port].vid;
		vlan = (struct vlan_ethhdr *) skb_push(skb, VLAN_HLEN);
		memmove(vlan, eth, 12);
		vlan->h_vlan_TCI = htons(vid);
		vlan->h_vlan_proto = htons(ETH_P_8021Q);
	}
	return skb;
}  /* sw_ins_vlan */

#ifdef CONFIG_KSZ_HSR
static struct sk_buff *sw_ins_hsr(struct ksz_sw *sw, uint n,
	struct sk_buff *skb, u16 *ports)
{
	int i;
	uint p;
	struct ksz_hsr_info *info = &sw->info->hsr;

#if 0
	p = get_phy_port(sw, n);
#endif
	p = sw->priv_port;
	i = sw->info->port_cfg[p].index;
	if (info->redbox_up) {
		struct net_device **dev = (struct net_device **)skb->cb;

		/* Destination is Redbox. */
		if (info->redbox && *dev == info->redbox)
			return skb;
		if (skb->dev == info->redbox) {
			dev_kfree_skb_irq(skb);
			return NULL;
		}
		if (*dev != info->dev) {
			int forward = hsr_fwd(info, skb);

			if (forward == 2) {
				struct ksz_port *sw_port =
					sw->netport[info->redbox_index];
				uint m = sw_port->first_port;

				sw->priv_port = get_phy_port(sw, m);
				return skb;
			}
		}
	}
	if (sw->eth_cnt && (sw->eth_maps[i].proto & HSR_HW)) {
		struct hsr_port *from =
			hsr_port_get_hsr(&info->hsr, HSR_PT_MASTER);
#ifdef CONFIG_1588_PTP
		struct ptp_msg *msg;
		struct ptp_info *ptp = &sw->ptp_hw;

		if (ptp->tx_msg_parsed)
			msg = ptp->tx_msg;
		else {
			msg = check_ptp_msg(skb->data, NULL);
			ptp->tx_msg_parsed = true;
			ptp->tx_msg = msg;
		}
		if (msg) {
			if (msg->hdr.messageType != SYNC_MSG &&
			    msg->hdr.messageType != MANAGEMENT_MSG &&
			    msg->hdr.messageType != SIGNALING_MSG &&
			    msg->hdr.messageType != ANNOUNCE_MSG)
				return skb;
			if (!(*ports & sw->TAIL_TAG_LOOKUP)) {
				if (!(*ports & (1 << info->ports[0]))) {
					dev_kfree_skb_irq(skb);
					return NULL;
				}
			}
		}
#endif
		if (!hsr_forward_skb(skb, from))
			return NULL;
#if 0
		memcpy(&skb->data[6], info->src_addr, ETH_ALEN);
#endif
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
	uint port;
	struct sk_buff *org_skb;
	struct ksz_sw_tx_tag tx_tag;
	u8 *tag;
	int update_dst = (sw->overrides & TAIL_TAGGING);
	int ptp_len = 0;

#ifdef CONFIG_1588_PTP
	struct ptp_info *ptp = ptr;
#endif

	if (!update_dst)
		return sw_ins_vlan(sw, priv->first_port, skb);

	if (skb->protocol == htons(ETH_P_TRAILER))
		return skb;
#ifdef CONFIG_KSZ_STP
	if (skb->protocol == htons(STP_TAG_TYPE))
		return skb;
#endif
#ifdef CONFIG_KSZ_DLR
	if (skb->protocol == htons(DLR_TAG_TYPE))
		return skb;
#endif
#ifdef PROC_MRP
	if (skb->protocol == htons(ETH_P_MSRP) ||
	    skb->protocol == htons(ETH_P_MVRP) ||
	    skb->protocol == htons(ETH_P_MMRP)) {

		/* MRP frame from application has 2 end marks. */
		if (skb->data[skb->len - 1] || skb->data[skb->len - 2])
			return skb;

		mrp_rcv(&sw->mrp, skb, sw->HOST_PORT);
		return NULL;
	}
#endif

	/* PTP is enabled and so requires extra 4 bytes. */
	if (sw->overrides & PTP_TAG)
		ptp_len = 4;

	tx_tag.ports = 0;
	tx_tag.timestamp = 0;

#ifdef CONFIG_KSZ_IBA
	if (skb->protocol == htons(ETH_P_IBA)) {
		tx_tag.ports = sw->TAIL_TAG_LOOKUP;
		len = skb->len;
		goto add_tag;
	}
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

	if (port) {
		port = get_phy_port(sw, port);
		tx_tag.ports = 1 << port;
	}

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
	}

	/* Remember original tag information as PTP may change the tag. */
	port = tx_tag.ports;

#ifdef CONFIG_1588_PTP
	if (ptp)
		ptp_set_tx_info(ptp, skb->data, &tx_tag);
#endif
	if (!port) {
		sw->priv_port = get_phy_port(sw, priv->first_port);
		if (!tx_tag.ports)
			tx_tag.ports = sw->TAIL_TAG_LOOKUP;

#ifdef CONFIG_KSZ_HSR
		skb = sw_ins_hsr(sw, priv->first_port, skb, &tx_tag.ports);
		if (!skb)
			return NULL;
		len = skb->len;
#endif
	}
	if (sw->TAIL_TAG_LOOKUP == tx_tag.ports) {
		/* Use VLAN for port forwarding if not specified directly. */
		skb = sw_ins_vlan(sw, priv->first_port, skb);
		if (len != skb->len)
			len = skb->len;
	}
	do {
		int dest;
#if 1
		struct vlan_ethhdr *vlan = (struct vlan_ethhdr *)skb->data;
#endif

		/* The MAC table was programmed to forward only to host.
		 * Need destination ports to send out.
		 * The port may be blocked.  Need override to send out.
		 */
		dest = sw_need_dest(sw, skb->data);
		if (dest > 0 && sw->TAIL_TAG_LOOKUP == tx_tag.ports) {
			struct ksz_dev_map *map;
			u16 ports;
			int i;

			ports = priv->live_ports & sw->tx_ports[0];
			ports &= ~sw->HOST_MASK;
			if (!ports) {
				dev_kfree_skb_irq(skb);
				return NULL;
			}
			for (i = 0; i < sw->eth_cnt; i++) {
				map = &sw->eth_maps[i];
				if (map->first == priv->first_port &&
				    (map->proto & (DLR_HW | HSR_HW))) {
					dev_kfree_skb_irq(skb);
					return NULL;
				}
			}
			tx_tag.ports = ports;
		}

#if 1
		/* Honor the VLAN priority to put in different queue. */
		if (vlan->h_vlan_proto == htons(ETH_P_8021Q)) {
			u16 prio;
			u16 vlan_tci = ntohs(vlan->h_vlan_TCI);
			struct ksz_port_cfg *cfg =
				&sw->info->port_cfg[sw->HOST_PORT];
			u32 queue = cfg->tc_map[0];

			prio = vlan_tci & VLAN_PRIO_MASK;
			prio >>= VLAN_PRIO_SHIFT;
			queue >>= prio * PORT_TC_MAP_S;
			queue &= PORT_TC_MAP_M;
			tx_tag.ports &= ~(7 << sw->TAIL_TAG_SHIFT);
			tx_tag.ports |= (queue << sw->TAIL_TAG_SHIFT);
		}
#endif
		if (tx_tag.ports && 2 == dest)
			tx_tag.ports |= sw->TAIL_TAG_OVERRIDE;
	} while (0);

#ifdef CONFIG_KSZ_IBA
add_tag:
#endif
	tx_tag.ports = htons(tx_tag.ports);
	tx_tag.timestamp = htonl(tx_tag.timestamp);
	tag = (u8 *) &tx_tag;

	/* Socket buffer has no fragments. */
	if (!skb_shinfo(skb)->nr_frags) {
		len = append_tag(sw->TAIL_TAG_SHIFT, skb->data, tag, len,
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
		len = append_tag(sw->TAIL_TAG_SHIFT, sw->tx_pad, tag,
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
	}
#endif

	return sw_check_skb(sw, skb, priv, ptr, update_msg);
}  /* sw_check_tx */

#ifdef CONFIG_KSZ_DSA
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
#ifdef CONFIG_KSZ_DSA
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
	int setup = true;

#ifdef CONFIG_KSZ_IBA
	if (2 <= sw->info->iba.use_iba)
		setup = false;
#endif
	sw->ops->acquire(sw);
	if (setup)
		sw_setup(sw);
	sw_enable(sw);

	sw_set_addr(sw, addr);

	/* STP has its own mechanism to handle looping. */
	if (!(sw->features & STP_SUPPORT))
		sw_cfg_src_filter(sw, true);
	if (sw->features & (PTP_HW | DLR_HW | HSR_HW))
		need_tail_tag = true;
	if (sw->dev_count > 1 && !(sw->features & SW_VLAN_DEV))
		need_tail_tag = true;
	if (sw->features & VLAN_PORT) {
		if (sw->features & VLAN_PORT_REMOVE_TAG) {
			struct ksz_vlan_table entry;
			uint n;
			uint p;

			memset(&entry, 0, sizeof(struct ksz_vlan_table));
			sw->ops->release(sw);
			entry.fid = VLAN_PORT_START;
			entry.untag = sw->PORT_MASK;
			entry.ports = sw->PORT_MASK;
			entry.valid = 1;
			sw_w_vlan_table(sw, VLAN_PORT_START, &entry);
			for (n = 1; n <= sw->mib_port_cnt; n++) {
				p = get_phy_port(sw, n);
				entry.fid = VLAN_PORT_START + p + 1;
				entry.untag = (1 << p);
				entry.ports = (1 << p) | (1 << sw->HOST_PORT);
				entry.valid = 1;
				sw_w_vlan_table(sw, VLAN_PORT_START + p + 1,
					&entry);
			}
			sw->ops->acquire(sw);
			for (n = 1; n <= sw->mib_port_cnt; n++) {
				p = get_phy_port(sw, n);
				sw_cfg_def_vid(sw, p, VLAN_PORT_START);
			}
			need_vlan = true;
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
			entry.untag = map->mask;

			/* Use tail tag to determine the network device. */
			if (need_tail_tag)
				entry.untag |= sw->HOST_MASK;
			entry.ports = sw->HOST_MASK | map->mask;
			entry.valid = 1;
			sw_w_vlan_table(sw, map->vlan, &entry);
			sw->ops->acquire(sw);
			need_vlan = true;
#ifdef CONFIG_KSZ_HSR
			if (map->proto & HSR_HW)
				continue;
#endif
			for (i = 0, q = map->first;
			     i < map->cnt; i++, q++) {
				port = get_phy_port(sw, q);
				sw_cfg_def_vid(sw, port, map->vlan);
			}
		}
	}
	if (sw->features & (STP_SUPPORT | DSA_SUPPORT))
		need_tail_tag = true;
	if (sw->features & (DLR_HW | MRP_SUPPORT))
		need_vlan = true;

#ifdef CONFIG_KSZ_MSTP
	if (sw->features & STP_SUPPORT)
		need_vlan = true;
#endif
	if (need_vlan)
		sw_ena_vlan(sw);
	if (need_tail_tag) {
		port_cfg_tail_tag(sw, sw->HOST_PORT, 1);
if (!(sw->overrides & TAIL_TAGGING))
dbg_msg(" ! tail tag not set\n");
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

#if defined(CONFIG_KSZ_IBA) || defined(CONFIG_1588_PTP)
	int hw_access = true;
#endif

#ifdef CONFIG_KSZ_IBA
	if (2 <= sw->info->iba.use_iba) {
		hw_access = false;
	}
#endif

#ifdef CONFIG_KSZ_STP
	if (sw->features & STP_SUPPORT) {
		struct ksz_stp_info *stp = &sw->info->rstp;

		if (stp->br.bridgeEnabled)
			stp_stop(stp, hw_access);
	}
#endif

#ifdef CONFIG_KSZ_MRP
	if (sw->features & MRP_SUPPORT) {
		struct mrp_info *mrp = &sw->mrp;

		mrp_stop(mrp);
	}
#endif

#ifdef CONFIG_1588_PTP
	if (sw->features & PTP_HW) {
		struct ptp_info *ptp = &sw->ptp_hw;

		reset = ptp->ops->stop(ptp, hw_access);
	}
#endif

#ifdef CONFIG_KSZ_IBA
	if (2 <= sw->info->iba.use_iba) {
		if (sw->info->iba.use_iba < 4) {
			sw->ops->acquire(sw);
			sw_cfg(sw, REG_SW_OPERATION, SW_RESET, 1);
			sw->ops->release(sw);

			/* Indicate no more hardware access. */
			sw->info->iba.use_iba = 4;
		}
		return reset;
	}
#endif

	sw->ops->acquire(sw);
	if (!reset)
		sw_reset(sw);
	reset = true;
	if (sw->mtu > 2000) {
		sw->reg->w16(sw, REG_SW_MTU__2, (u16) sw->mtu);
		sw_cfg(sw, REG_SW_MAC_CTRL_1, SW_JUMBO_PACKET, true);
	}
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
	for (n = 0; n <= sw->mib_port_cnt; n++) {
		p = get_phy_port(sw, n);
		if (sw->port_info[p].phy)
			continue;
		sw->port_state[p].state = media_connected;
	}
	sw->port_state[sw->HOST_PORT].state = media_connected;
}  /* sw_init_mib */

static int sw_open_dev(struct ksz_sw *sw, struct net_device *dev, u8 *addr)
{
	int mode = 0;

	sw_init_mib(sw);

	sw->main_dev = dev;
	sw->net_ops->start(sw, addr);
	if (sw->features & AVB_SUPPORT)
		mode |= 1;
	if (sw->dev_count > 1)
		mode |= 1;
	if (sw->features & DIFF_MAC_ADDR)
		mode |= 2;
#ifdef CONFIG_KSZ_HSR
	if (sw->features & HSR_REDBOX)
		mode |= 2;
#endif
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
		if (!info->phy)
			continue;

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
			if (p == sw->HOST_PORT)
				continue;
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
#ifdef CONFIG_KSZ_HSR
		if (sw->eth_maps[i].proto & HSR_HW) {
			struct ksz_hsr_info *info = &sw->info->hsr;

			p = get_phy_port(sw, port->first_port);
			if (info->ports[0] == p)
				prep_hsr(info, dev, dev->dev_addr);
		}
		if (sw->eth_maps[i].proto & HSR_REDBOX) {
			struct ksz_hsr_info *info = &sw->info->hsr;

			start_hsr_redbox(info, dev);
		}
#endif
	}
dbg_msg("%s r:%x t:%x d:%x l:%x\n", __func__,
sw->rx_ports[0], sw->tx_ports[0], sw->dev_ports, sw->live_ports);
}  /* sw_open_port */

static void sw_close_port(struct ksz_sw *sw, struct net_device *dev,
	struct ksz_port *port)
{
	int i;
	uint p;
#ifdef CONFIG_KSZ_MRP
	struct mrp_info *mrp = &sw->mrp;
#endif

#ifdef CONFIG_KSZ_IBA
	if (2 <= sw->info->iba.use_iba && dev == sw->main_dev)
		return;
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
#ifdef CONFIG_KSZ_HSR
		if (sw->eth_maps[i].proto & HSR_HW) {
			struct ksz_hsr_info *info = &sw->info->hsr;

			p = get_phy_port(sw, port->first_port);
			if (info->ports[0] == p)
				stop_hsr(info);
		}
		if (sw->eth_maps[i].proto & HSR_REDBOX) {
			struct ksz_hsr_info *info = &sw->info->hsr;

			stop_hsr_redbox(info, dev);
		}
#endif
	}
	sw_reset_multi(sw, port);
}  /* sw_close_port */

static void sw_open(struct ksz_sw *sw)
{
	sw->running = true;
#ifdef CONFIG_KSZ_IBA
	if (!sw->info->iba.use_iba)
		sw_set_dev(sw, sw->main_dev, sw->main_dev->dev_addr);
#endif
	sw_setup_reserved_multicast(sw);
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
	int hw_access = true;

#ifdef CONFIG_KSZ_IBA
	if (2 <= sw->info->iba.use_iba) {
		hw_access = false;
	}
#endif
	sw->running = false;
	flush_work(&sw->set_addr);
	if (hw_access) {
#ifdef CONFIG_KSZ_IBA
		sw_set_dev(sw, NULL, sw->main_dev->dev_addr);
#endif
	}
#ifdef CONFIG_KSZ_MRP
	if (sw->features & MRP_SUPPORT)
		mrp_close(&sw->mrp, hw_access);
#endif
	if (!hw_access) {
		struct sw_priv *hw_priv = sw->dev;

		ksz_stop_timer(&hw_priv->mib_timer_info);
	}
	ksz_stop_timer(sw->monitor_timer_info);
	cancel_delayed_work_sync(sw->link_read);
}  /* sw_close */

static void sw_delayed_set_addr(struct work_struct *work)
{
	struct ksz_sw *sw = container_of(work, struct ksz_sw, set_addr);

	sw->ops->acquire(sw);
	sw_set_addr(sw, sw->netdev[0]->dev_addr);
	sw->ops->release(sw);
}  /* sw_delayed_set_addr */

static u8 sw_set_mac_addr(struct ksz_sw *sw, struct net_device *dev,
	u8 promiscuous, uint port)
{
	int n;
#ifdef CONFIG_KSZ_IBA
	u8 promisc = promiscuous;
#endif

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

			/* All addresses are the same. */
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
	if (dev == sw->netdev[0])
		schedule_work(&sw->set_addr);
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
#ifdef CONFIG_KSZ_HSR
		if (sw->eth_maps[n].proto & (HSR_HW | HSR_REDBOX)) {
			struct ksz_hsr_info *hsr = &sw->info->hsr;

			hsr->ops->change_addr(hsr, dev);
		}
#endif
	}
	if (dev != sw->netdev[0])
		return promiscuous;

#ifdef CONFIG_1588_PTP
	if (sw->features & PTP_HW) {
		struct ptp_info *ptp = &sw->ptp_hw;

		ptp->ops->set_identity(ptp, dev->dev_addr);
	}
#endif

#ifdef CONFIG_KSZ_IBA
	if (netif_running(dev)) {
		sw_set_dev(sw, dev, dev->dev_addr);

		/* A hack to accept IBA response. */
		if (!promisc)
			promiscuous = 2;
	}
#endif
#ifdef CAPTURE_IBA
promiscuous = 1;
#endif
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
		if (sw->dev_info == info) {
			sw->dev_info = NULL;
			sw->notifications = 0;
		}
#ifdef CONFIG_KSZ_MRP_
		do {
			struct mrp_info *mrp = &sw->mrp;

			if (mrp->dev_info == info) {
				mrp->dev_info = NULL;
				mrp->notifications = 0;
			}
		} while (0);
#endif
#ifdef CONFIG_KSZ_DLR
		do {
			struct ksz_dlr_info *dlr = &sw->info->dlr;

			if (dlr->dev_info == info) {
				dlr->dev_info = NULL;
				dlr->notifications = 0;
			}
		} while (0);
#endif
#ifdef CONFIG_KSZ_HSR
		do {
			struct ksz_hsr_info *hsr = &sw->info->hsr;

			if (hsr->dev_info == info) {
				hsr->dev_info = NULL;
				hsr->notifications = 0;
			}
		} while (0);
#endif
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
			if (cfg->set & SP_PHY_POWER) {
				if (port_chk_power(sw, p))
					cfg->on_off |= SP_PHY_POWER;
			}
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
				port_cfg_rx_special(sw, p,
					!!(cfg->on_off & SP_RX));
			if (cfg->set & SP_TX)
				port_cfg_tx(sw, p,
					!!(cfg->on_off & SP_TX));
			if (p == sw->HOST_PORT)
				continue;
			if (cfg->set & SP_PHY_POWER)
				port_cfg_power(sw, p,
					!!(cfg->on_off & SP_PHY_POWER));
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
#ifdef CONFIG_1588_PTP
	case DEV_MOD_PTP:
		if (sw->features & PTP_HW) {
			struct ptp_info *ptp = &sw->ptp_hw;

			err = ptp->ops->dev_req(ptp, start, arg,
				(struct ptp_dev_info *) info);
			result = 0;
		}
		break;
#endif
#ifdef CONFIG_KSZ_MRP
	case DEV_MOD_MRP:
		if (sw->features & MRP_SUPPORT) {
			struct mrp_info *mrp = &sw->mrp;

			err = mrp->ops->dev_req(mrp, start, arg);
			result = 0;
		}
		break;
#endif
#ifdef CONFIG_KSZ_DLR
	case DEV_MOD_DLR:
		if (sw->features & DLR_HW) {
			struct ksz_dlr_info *dlr = &sw->info->dlr;

			err = dlr->ops->dev_req(dlr, arg, info);
			result = 0;
		}
		break;
#endif
#ifdef CONFIG_KSZ_HSR
	case DEV_MOD_HSR:
		if (sw->features & HSR_HW) {
			struct ksz_hsr_info *hsr = &sw->info->hsr;

			err = hsr->ops->dev_req(hsr, arg, info);
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

/* -------------------------------------------------------------------------- */

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
	u32 speed;
	bool duplex;

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
#ifdef CONFIG_KSZ_HSR
	if (sw->features & HSR_HW) {
		struct ksz_hsr_info *hsr = &sw->info->hsr;

		dev = port->netdev;
		if (dev && dev == hsr->redbox_dev) {
			int up = hsr->redbox_up;

			hsr->redbox_up = netif_carrier_ok(dev);
			if (up != hsr->redbox_up && up)
				hsr_rmv_slaves(hsr);
		}
	}
#endif

	for (i = 1; i <= sw->mib_port_cnt; i++) {
		p = get_phy_port(sw, i);
		if (!(port->link_ports & (1 << p)))
			continue;
		info = get_port_info(sw, p);
		speed = (media_connected == info->state) ?
			info->tx_rate / TX_RATE_UNIT : 0;
		duplex = (info->duplex == 2);
#ifdef CONFIG_1588_PTP
		if (sw->features & PTP_HW) {
			struct ptp_info *ptp = &sw->ptp_hw;

			ptp->link_ports = port->link_ports;
		}
#endif
#ifdef CONFIG_KSZ_MSRP
		if (sw->features & MRP_SUPPORT) {
			struct mrp_info *mrp = &sw->mrp;

			mrp_set_speed(mrp, p, speed, duplex);
		}
#endif
	}
	if (port->link_ports) {

#ifdef CONFIG_1588_PTP
		if (sw->features & PTP_HW) {
			struct ptp_info *ptp = &sw->ptp_hw;

			if (ptp->started)
				set_latency(&ptp->set_latency);
		}
#endif
	}
	port->link_ports = 0;

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
			if (netif_msg_link(sw))
				pr_info("%s link %s\n",
					dev->name,
					phy_link ? "on" : "off");
		}
		if (phydev->adjust_link && phydev->attached_dev)
			phydev->adjust_link(phydev->attached_dev);
		link = netif_carrier_ok(dev);
		if (link != phy_link) {
			if (phy_link)
				netif_carrier_on(dev);
			else
				netif_carrier_off(dev);
		}
	}

#ifdef CONFIG_KSZ_HSR
	if (sw->features & HSR_HW) {
		struct ksz_hsr_info *hsr = &sw->info->hsr;

		p = get_phy_port(sw, port->first_port);
		if (hsr->ports[0] == p) {
			hsr->ops->link_change(hsr,
				sw->port_info[hsr->ports[0]].state ==
				media_connected,
				sw->port_info[hsr->ports[1]].state ==
				media_connected);
			hsr->ops->check_announce(hsr);
		}
	}
#endif
}  /* link_update_work */


#if defined(CONFIG_KSZ_DLR) && !defined(CONFIG_KSZ_MSRP) && !defined(CONFIG_KSZ_HSR)
#define USE_DLR
#endif

#if defined(CONFIG_KSZ_HSR) && !defined(CONFIG_KSZ_MSRP) && !defined(CONFIG_KSZ_DLR)
#define USE_HSR
#define USE_HSR_REDBOX
#endif

#if 0
#define USE_DLR
#if 0
#define USE_DLR_FORWARD
#endif
#endif
#if 0
#define USE_HSR
#if 0
#define USE_HSR_REDBOX
#endif
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
#if defined(USE_HSR_REDBOX) || defined(USE_DLR_FORWARD)
static int multi_dev = 1;
#else
static int multi_dev = -1;
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
static int stp = -1;

/*
 * This enables fast aging in the switch.  Not sure what situation requires
 * that.  However, fast aging is used to flush the dynamic MAC table when STP
 * support is enabled.
 */
static int fast_aging;

static int sgmii = -1;

static int authen;

#if defined(USE_DLR) || defined(USE_HSR)
static int avb;
#else
static int avb = -1;
#endif
static int mrp;

#if defined(USE_DLR) || defined(USE_HSR)
static int eth1_ports = 0x3;
#else
static int eth1_ports;
#endif
static int eth2_ports;
static int eth3_ports;
static int eth4_ports;
static int eth5_ports;
static int eth6_ports;

#if defined(USE_HSR_REDBOX) || defined(USE_DLR_FORWARD)
static int eth1_vlan = FID_ENTRIES - 2;
#else
static int eth1_vlan;
#endif
static int eth2_vlan;
static int eth3_vlan;
static int eth4_vlan;
static int eth5_vlan;
static int eth6_vlan;

#if defined(USE_DLR)
static char *eth1_proto = "dlr";
#endif
#if defined(USE_HSR)
static char *eth1_proto = "hsr";
#endif
#if !defined(USE_DLR) && !defined(USE_HSR)
static char *eth1_proto = " ";
#endif
#if defined(USE_HSR_REDBOX)
static char *eth2_proto = "redbox";
#else
static char *eth2_proto = " ";
#endif
static char *eth3_proto = " ";
static char *eth4_proto = " ";
static char *eth5_proto = " ";
static char *eth6_proto = " ";

static int *eth_ports[] = {
	&eth1_ports,
	&eth2_ports,
	&eth3_ports,
	&eth4_ports,
	&eth5_ports,
	&eth6_ports,
	NULL
};

static int *eth_vlans[] = {
	&eth1_vlan,
	&eth2_vlan,
	&eth3_vlan,
	&eth4_vlan,
	&eth5_vlan,
	&eth6_vlan,
	NULL
};

static char **eth_proto[] = {
	&eth1_proto,
	&eth2_proto,
	&eth3_proto,
	&eth4_proto,
	&eth5_proto,
	&eth6_proto,
	NULL
};

#ifdef CONFIG_KSZ_IBA
static int iba = 1;
#endif

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
#ifdef CONFIG_1588_PTP
			if (sw->features & PTP_HW) {
				features |= VLAN_PORT;
				sw->features |= VLAN_PORT | VLAN_PORT_TAGGING;
			}
#endif
			limit = 2;
			if (!w)
				w = 1;
		}
#endif
#ifdef CONFIG_KSZ_HSR
		if (!strcmp(*s, "hsr")) {
			features = HSR_HW;
#ifdef CONFIG_1588_PTP
			if (sw->features & PTP_HW) {
				features |= VLAN_PORT;
				sw->features |= VLAN_PORT | VLAN_PORT_TAGGING;
			}
#endif
			limit = 2;
			if (!w)
				w = 1;
		} else if (!strcmp(*s, "redbox")) {
			features = HSR_REDBOX;
			if (!w)
				w = 1;
		}
#endif
#ifdef CONFIG_KSZ_STP
		if (!strcmp(*s, "stp")) {
			features = STP_SUPPORT;
		}
#endif
#ifdef CONFIG_1588_PTP
		if (!features && !p) {
			if (sw->features & PTP_HW) {
				features |= VLAN_PORT;
				sw->features |= VLAN_PORT | VLAN_PORT_TAGGING;
			}
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
#ifdef CONFIG_KSZ_DLR
		if ((features & DLR_HW) && !(used & DLR_HW))
			features = 0;
		if (!(sw->features & DLR_HW) && (features & DLR_HW))
			features = 0;
#endif
#ifdef CONFIG_KSZ_HSR
		if ((features & HSR_HW) && !(used & HSR_HW))
			features = 0;
		if (!(sw->features & HSR_HW) &&
		    (features & (HSR_HW | HSR_REDBOX)))
			features = 0;
		if (features == HSR_REDBOX)
			used |= features;
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
#ifdef CONFIG_KSZ_HSR
		if (features & HSR_HW) {
			struct ksz_hsr_info *hsr = &sw->info->hsr;

			c = 0;
			f = 0;
			do {
				if (m & 1) {
					hsr->ports[c++] = f;
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
#ifdef CONFIG_KSZ_HSR
	if (left && (sw->features & HSR_HW)) {

		/* Redbox is explicitly specified. */
		if (used & HSR_REDBOX)
			left = 0;
		if ((used & HSR_HW) && !(used & HSR_REDBOX)) {
			s = eth_proto[1];
			if (!strcmp(*s, "redbox")) {
				features = HSR_REDBOX;
				used |= HSR_REDBOX;
			}
		}
		if (used & HSR_REDBOX)
			sw->features |= HSR_REDBOX;
		else if (used & HSR_HW)
			left = 0;
	}
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
		dbg_msg("%d: %d:%d:%d m=%04x v=%03x %08x\n",
			p, map->first, map->cnt, map->phy_id,
			map->mask, map->vlan, map->proto);
	}

setup_next:
#ifdef CONFIG_KSZ_DLR
	if (!(used & DLR_HW))
		sw->features &= ~DLR_HW;
#endif
#ifdef CONFIG_KSZ_HSR
	if (!(used & HSR_HW))
		sw->features &= ~HSR_HW;
#endif
	if ((sw->features & (DLR_HW | HSR_HW)) || sw->eth_cnt > 1) {
		if (stp <= 1)
			stp = 0;
		avb = 0;
		sw->overrides &= ~USE_802_1X_AUTH;
	}
#ifdef CONFIG_KSZ_STP
	if (stp > 0) {
		sw->features |= STP_SUPPORT;
	}
#endif
#ifdef CONFIG_1588_PTP
	if (!(used & VLAN_PORT))
		sw->features &= ~(VLAN_PORT | VLAN_PORT_TAGGING);
	if (!avb)
		sw->features &= ~AVB_SUPPORT;
#endif
dbg_msg("features: %x m:%d a:%d s:%x\n", sw->features, multi_dev, avb, stp);
	return ports;
}  /* sw_setup_zone */

static int phy_offset;

static void sw_setup_special(struct ksz_sw *sw, int *port_cnt,
	int *mib_port_cnt, int *dev_cnt)
{
	phy_offset = 0;
	sw->dev_offset = 0;
	sw->phy_offset = 0;
	dbg_msg("%s s:%x m:%d f:%d\n", __func__,
		sw->stp, sw->multi_dev, sw->fast_aging);
#ifdef CONFIG_KSZ_IBA
	if (iba)
		sw->features |= IBA_SUPPORT;
#endif

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
#ifdef CONFIG_1588_PTP
#ifdef CONFIG_PTP_1588_CLOCK
/* THa  05/30/2018
 * I2C driver is invoked before PPS and PTP, so the call to register the PTP
 * clock needs to be called later.
 */
	if (sw->features & PTP_HW) {
		struct ptp_info *ptp = &sw->ptp_hw;

		micrel_ptp_probe(ptp);
	}
#endif
	if (sw->features & VLAN_PORT) {
		struct ptp_info *ptp = &sw->ptp_hw;

		ptp->overrides |= PTP_PORT_FORWARD;
	}
#endif
dbg_msg("%s d:%d c:%d\n", __func__, *dev_cnt, sw->eth_cnt);
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
	char *dev_name, struct ksz_port *port, int i, uint port_cnt,
	uint mib_port_cnt)
{
	struct ksz_port_info *info;
	uint cnt;
	uint n;
	uint p;
	uint pi;
	int phy_id;
	u32 features;
	struct ksz_dev_map *map;
	int header = 0;

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

	/* S1 chips do not work well with asymmetric PAUSE. */
	if ((sw->features & NEW_CAP) && (sw->features & GIGABIT_SUPPORT))
		port->flow_ctrl = PHY_RX_ONLY;

#ifdef CONFIG_KSZ_STP
	if (!i && (sw->features & STP_SUPPORT))
		prep_stp_mcast(dev);
#endif

#ifdef CONFIG_KSZ_DLR
	/* Cannot flow control because of beacon timeout. */
	if (sw->eth_cnt && (map->proto & DLR_HW)) {
		if ((sw->features & NEW_CAP) &&
		    (sw->features & GIGABIT_SUPPORT))
			port->flow_ctrl = PHY_TX_ONLY;
		prep_dlr_mcast(dev);
	}
#endif
#ifdef CONFIG_KSZ_HSR
	if (sw->eth_cnt && (map->proto & HSR_HW)) {
#if 0
		port->flow_ctrl = PHY_TX_ONLY;
#endif
		setup_hsr(&sw->info->hsr, dev, i);
		if (header < HSR_HLEN)
			header = HSR_HLEN;
	}
	if (sw->eth_cnt && (map->proto & HSR_REDBOX)) {
		setup_hsr_redbox(&sw->info->hsr, dev, i);
	}
#endif
#ifdef CONFIG_KSZ_MRP
	if (!i && (sw->features & MRP_SUPPORT))
		setup_mrp(&sw->mrp, dev);
#endif
	if (sw->features & AVB_SUPPORT)
		port->flow_ctrl = PHY_NO_FLOW_CTRL;

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
		if (info->phy)
			info->state = media_disconnected;
		else if (info->intf == INTF_RGMII)
			port->live_ports |= (1 << pi);
		if (pi == sw->HOST_PORT)
			continue;
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

#ifndef CONFIG_KSZ_DSA
	if (features & VLAN_PORT)
		dev->features |= NETIF_F_HW_VLAN_CTAG_FILTER;
#endif

	/* Needed for inserting VLAN tag. */
	if (sw->features & SW_VLAN_DEV)
		if (header < VLAN_HLEN)
			header = VLAN_HLEN;
	dev->hard_header_len += header;
dbg_msg("%s %d:%d phy:%d l:%x\n", __func__, port->first_port, port->port_cnt, phy_id,
port->live_ports);

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
	uint port;
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
		port = sw->netport[0];
		state = sw->net_ops->get_state(dev);
		sw->net_ops->open_port(sw, dev, port, &state);
		sw->net_ops->set_state(dev, state);
		return;
	}
	for (p = 0; p < dev_count; p++) {
		dev = sw->netdev[p];
		if (!dev)
			continue;
		port = sw->netport[p];
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
	.drop_icmp		= sw_drop_icmp,
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

	.chk_regs		= sw_chk_regs,

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

#ifdef CONFIG_KSZ_MRP
	.sysfs_mrp_read		= sysfs_mrp_read,
	.sysfs_mrp_write	= sysfs_mrp_write,
	.sysfs_mrp_port_read	= sysfs_mrp_port_read,
	.sysfs_mrp_port_write	= sysfs_mrp_port_write,
#endif

#ifdef CONFIG_KSZ_HSR
	.sysfs_hsr_read		= sysfs_hsr_read,
	.sysfs_hsr_write	= sysfs_hsr_write,
#endif

	.sysfs_acl_read		= sysfs_acl_read,
	.sysfs_acl_write	= sysfs_acl_write,

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
	.fwd_unk_mcast		= sw_fwd_unk_mcast,
	.fwd_unk_ucast		= sw_fwd_unk_ucast,
	.fwd_unk_vid		= sw_fwd_unk_vid,

	.port_freeze_mib	= port_freeze_mib,
	.freeze_mib		= sw_freeze_mib,
};

static int sw_proc_intr(struct ksz_sw *sw)
{
	u32 intr_mask;
	u32 status;
	u16 port_intr_mask;
	u8 port_status;
	uint port;
#ifdef CONFIG_1588_PTP
	struct ptp_info *ptp = &sw->ptp_hw;
#endif
	u32 intr_status[2];
	int cnt = 0;
	static int dbg_intr_status = 5;
	static int dbg_intr_cnt = 0;

	intr_mask = sw->intr_mask;
	status = sw->reg->r32(sw, REG_SW_INT_STATUS__4);
	if (status)
		cnt++;
	intr_status[0] = status;
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
	if (status)
		cnt++;
	intr_status[1] = status;
#if 0
dbg_msg("port irq: %08x; %08x\n", status, sw->port_intr_mask);
#endif
	status &= sw->port_intr_mask;
	for (port = 0; port < sw->port_cnt; port++) {
		if (status & 1) {
			struct ksz_port_cfg *cfg = get_port_cfg(sw, port);
			int stop_phy_irq = false;

			if (!(sw->features & NEW_CAP))
				stop_phy_irq = true;
			port_intr_mask = cfg->intr_mask;
			port_r(sw, port, REG_PORT_INT_STATUS, &port_status);
			port_status &= cfg->intr_mask;
			if (port_status & PORT_SGMII_INT) {
				u16 data = 0;

				port_sgmii_w(sw, port, SR_MII,
					MMD_SR_MII_AUTO_NEG_STATUS, &data, 1);
				sw->phy_intr |= (1 << port);
			}
			if (port_status & PORT_PHY_INT) {
				u8 val;

				/* The status is cleared after read. */
				port_r8(sw, port, REG_PORT_PHY_INT_STATUS,
					&val);
				if (val & (LINK_DOWN_INT | LINK_UP_INT))
					sw->phy_intr |= (1 << port);
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
				if (sw->features & NEW_CAP)
					port_w(sw, port, REG_PORT_INT_STATUS,
						PORT_ACL_INT);
				else {
					port_w(sw, port, REG_PORT_INT_MASK,
						(~cfg->intr_mask &
						PORT_INT_MASK) |
						PORT_ACL_INT);
					port_w(sw, port, REG_PORT_INT_MASK,
						~cfg->intr_mask &
						PORT_INT_MASK);
				}
#ifdef CONFIG_KSZ_DLR
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
	if (sw->intr_cnt && cnt) {
		dbg_intr_cnt = cnt;
#if 0
		dbg_msg("intr: %08x %08x\n", intr_status[0], intr_status[1]);
#endif
	}
	if (!sw->intr_cnt && cnt)
		dbg_intr_cnt = 0;
	sw->intr_cnt += cnt;
	if (!sw->intr_cnt && !dbg_intr_cnt && dbg_intr_status) {
		dbg_msg("no intr status\n");
		dbg_intr_status--;
	}
	return cnt;
}  /* sw_proc_intr */

/* -------------------------------------------------------------------------- */

#ifndef CONFIG_KSZ_IBA_ONLY
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
#endif

/* -------------------------------------------------------------------------- */

#define USE_SPEED_LINK
#define USE_MIB
#include "ksz_sw_sysfs_9897.c"
#ifdef CONFIG_1588_PTP
#include "ksz_ptp_sysfs.c"
#endif
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
	int intr;

	/* Fake interrupt can be triggered once. */
	if (ks->intr_working & 0x80000000) {
		ks->intr_working |= 1;
		if (ks->sw.info->port_cfg[0].intr_mask & PORT_PHY_INT)
			ks->intr_working |= 2;
	}
	ks->intr_working |= 0x80000000;
	mutex_lock(&sw->lock);
	mutex_lock(&ks->hwlock);
	mutex_lock(&ks->lock);
	sw->intr_using++;
	sw->intr_cnt = 0;
	do {
		intr = sw_proc_intr(sw);
	} while (intr);
	sw->intr_using--;
	mutex_unlock(&ks->lock);
	mutex_unlock(&ks->hwlock);
	mutex_unlock(&sw->lock);
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

#ifndef CONFIG_KSZ_NO_MDIO_BUS
#define KSZ989X_SW_ID		0x9897
#define KSZ889X_SW_ID		0x8897
#define PHY_ID_KSZ989X_SW	((KSZ9897_ID_HI << 16) | KSZ989X_SW_ID)
#define PHY_ID_KSZ889X_SW	((KSZ9897_ID_HI << 16) | KSZ889X_SW_ID)

static char *kszsw_phy_driver_names[] = {
	"Microchip KSZ9897 Switch",
	"Microchip KSZ9567 Switch",
	"Microchip KSZ9477 Switch",
	"Microchip KSZ9896 Switch",
	"Microchip KSZ9566 Switch",
	"Microchip KSZ8567 Switch",
	"Microchip KSZ8565 Switch",
	"Microchip KSZ9893 Switch",
	"Microchip KSZ9563 Switch",
	"Microchip KSZ8563 Switch",
};

static int kszphy_config_init(struct phy_device *phydev)
{
	return 0;
}

static struct phy_driver kszsw_phy_driver[] = {
{
	.phy_id		= PHY_ID_KSZ989X_SW,
	.phy_id_mask	= 0x00ffffff,
	.name		= "Microchip KSZ989X Switch",
	.features	= (PHY_GBIT_FEATURES |
				SUPPORTED_Pause | SUPPORTED_Asym_Pause),
	.flags		= PHY_HAS_INTERRUPT,
	.config_init	= kszphy_config_init,
	.config_aneg	= genphy_config_aneg,
	.read_status	= genphy_read_status,
}, {
	.phy_id		= PHY_ID_KSZ889X_SW,
	.phy_id_mask	= 0x00ffffff,
	.name		= "Microchip KSZ889X Switch",
	.features	= (PHY_BASIC_FEATURES | SUPPORTED_Pause),
	.flags		= PHY_HAS_INTERRUPT,
	.config_init	= kszphy_config_init,
	.config_aneg	= genphy_config_aneg,
	.read_status	= genphy_read_status,
}
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
	u16 ret = 0;
	uint p;

	p = get_phy_port(sw, phy);
	if (p < sw->phy_port_cnt) {
		u16 data;

		port_r16(sw, p, P_PHY_CTRL + reg * 2, &data);
		ret = data;
		if (1 == reg && !(ret & PORT_LINK_STATUS)) {
			port_r16(sw, p, P_SPEED_STATUS, &data);
			if ((ret & PORT_AUTO_NEG_ACKNOWLEDGE) &&
			    (data & (PORT_STAT_SPEED_1000MBIT |
			    PORT_STAT_SPEED_100MBIT |
			    PORT_STAT_SPEED_10MBIT)))
				ret |= PORT_LINK_STATUS;
		}
	} else {
		switch (reg) {
		case MII_BMCR:
			ret = 0x1140;
			break;
		case MII_BMSR:
			ret = 0x796d;
			break;
		case MII_ADVERTISE:
			ret = 0x05e1;
			break;
		case MII_LPA:
			ret = 0xc5e1;
			break;
		case MII_CTRL1000:
			ret = 0x0700;
			break;
		case MII_STAT1000:
			if (sw->port_info[p].tx_rate >= 1000 * TX_RATE_UNIT)
				ret = 0x7800;
			else
				ret = 0;
			break;
		}
	}

	/* Use unique switch id to differentiate from regular PHY. */
	if (MII_PHYSID2 == reg) {
		if (sw->features & GIGABIT_SUPPORT)
			ret = KSZ989X_SW_ID;
		else
			ret = KSZ889X_SW_ID;
	} else if (MII_PHYSID1 == reg) {
		ret = KSZ9897_ID_LO;
	}
	*val = ret;
}  /* sw_r_phy */

static int ksz_mii_read(struct mii_bus *bus, int phy_id, int regnum)
{
	struct sw_priv *ks = bus->priv;
	struct ksz_sw *sw = &ks->sw;
	int ret = 0xffff;

	if (phy_id > sw->mib_port_cnt + 1)
		return 0xffff;

	sw->ops->acquire(sw);
	ret = 0;
	if (regnum < 11) {
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
		sw_r_phy(sw, phy_id, regnum, &data);
		ret = data;
	}
	sw->ops->release(sw);
	return ret;
}  /* ksz_mii_read */

static int ksz_mii_write(struct mii_bus *bus, int phy_id, int regnum, u16 val)
{
	struct sw_priv *ks = bus->priv;
	struct ksz_sw *sw = &ks->sw;

	if (phy_id > sw->mib_port_cnt + 1)
		return -EINVAL;

	sw->ops->acquire(sw);
	if (regnum < 11) {
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
				if (f <= phy_id && phy_id <= l) {
					first = map->first;
					last = first + map->cnt - 1;
					break;
				}
			}
dbg_msg(" %d f:%d l:%d\n", phy_id, first, last);
		}

		/* PHY device driver resets or powers down the PHY. */
		if (0 == regnum &&
		    (val & (PORT_PHY_RESET | PORT_POWER_DOWN)))
			goto done;
		for (i = first; i <= last; i++) {
			p = get_phy_port(sw, i);
			if (p >= sw->phy_port_cnt)
				break;
			if (p == sw->HOST_PORT)
				continue;
			port_w16(sw, p, P_PHY_CTRL + regnum * 2, val);
		}
		if (0 == regnum &&
		    !(val & PORT_AUTO_NEG_ENABLE))
			schedule_delayed_work(&ks->link_read, 1);
	}
done:
	sw->ops->release(sw);
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
		if (ks->sw.features & GIGABIT_SUPPORT)
			kszsw_phy_driver[0].name =
				kszsw_phy_driver_names[ks->sw.chip_id];
		else
			kszsw_phy_driver[1].name =
				kszsw_phy_driver_names[ks->sw.chip_id];
		err = phy_drivers_register(kszsw_phy_driver,
			ARRAY_SIZE(kszsw_phy_driver), THIS_MODULE);
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
		phy_drivers_unregister(kszsw_phy_driver,
			ARRAY_SIZE(kszsw_phy_driver));
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
		phy_drivers_unregister(kszsw_phy_driver,
			ARRAY_SIZE(kszsw_phy_driver));
		driver_installed = false;
	}
	mdiobus_free(bus);
	platform_device_unregister(pdev);
}  /* ksz_mii_exit */
#endif

/* driver bus management functions */

static void determine_rate(struct ksz_sw *sw, struct ksz_port_mib *mib)
{
	int j;

	for (j = 0; j < 2; j++) {
		if (mib->rate[j].last) {
			unsigned long diff = jiffies - mib->rate[j].last;
			u64 cnt = mib->counter[MIB_RX_TOTAL + j] -
				mib->rate[j].last_cnt;

			if (cnt > 1000000 && diff >= HZ) {
				u32 rem;
				u64 rate = cnt;

				rate *= 8;
				diff *= 1000 * 100 / HZ;
				rate = div_u64_rem(rate, diff, &rem);
				mib->rate[j].last = jiffies;
				mib->rate[j].last_cnt =
					mib->counter[MIB_RX_TOTAL + j];
				if (mib->rate[j].peak < (u32) rate)
					mib->rate[j].peak = (u32) rate;
			}
			diff = jiffies - mib->rate[j].check;
			cnt = mib->counter[MIB_RX_TOTAL + j] -
				mib->rate[j].prev_cnt;
			mib->rate[j].prev_cnt =
				mib->counter[MIB_RX_TOTAL + j];
			if (cnt) {
				mib->rate[j].check = jiffies;
				mib->rate[j].no_change = false;
			} else if (diff >= HZ / 2) {
				mib->rate[j].no_change = true;
			}
		} else {
			mib->rate[j].last = jiffies;
			mib->rate[j].check = jiffies;
			mib->rate[j].no_change = false;
		}
	}
}  /* determine_rate */

static void ksz9897_mib_read_work(struct work_struct *work)
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

	/* Restart auto-negotiation for those ports used in port_setup_eee. */
	do {
		struct ksz_port_cfg *cfg;
		u32 period = hw_priv->mib_timer_info.period * 1000 / HZ;

		for (n = 0; n <= sw->mib_port_cnt; n++) {
			p = get_phy_port(sw, n);
			cfg = get_port_cfg(sw, p);
			if (cfg->setup_time) {
				if (cfg->setup_time > period)
					cfg->setup_time -= period;
				else {
					sw->ops->acquire(sw);
					port_w16(sw, p, REG_PORT_PHY_CTRL,
						0x1140);
					sw->ops->release(sw);
					cfg->setup_time = 0;
				}
			}
		}
	} while (0);
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
				struct ksz_port_info *info;

				hw_priv->counter[p].read = 2;
				wake_up_interruptible(
					&hw_priv->counter[p].counter);
				if (p != sw->HOST_PORT)
					determine_rate(sw, mib);
				info = get_port_info(sw, p);
				if (info->fiber &&
				    info->state == media_connected &&
				    mib->rate[0].no_change &&
				    mib->rate[1].no_change) {
					sw->phy_intr |= (1 << p);
					schedule_delayed_work(&hw_priv->link_read, 0);
				}
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
			sw->port_state[p].link_down = 0;
			mib->rate[0].no_change = false;

			/* Read counters one last time after link is lost. */
			hw_priv->counter[p].read = 1;
		}
	}
#ifdef CONFIG_KSZ_MRP
	if (sw->features & MRP_SUPPORT)
		mrp_chk_blocked_addr(&sw->mrp);
#endif
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
	struct ksz_port *port = NULL;
	struct ksz_port *sw_port = NULL;
	int i;
	int changes = 0;
	int s = 1;
	int dev_cnt = sw->dev_count + sw->dev_offset;

	if (1 == sw->dev_count || 1 == sw->dev_offset)
		s = 0;
	/* Check main device when child devices are used. */
	if (sw->dev_offset) {
		sw_port = sw->netport[0];
		sw_port->live_ports = 0;
	}

	/*
	 * Only check port which has interrupts triggered.
	 * If no interrupt poll all the ports with PHY.
	 */
	if (!sw->phy_intr) {
		sw->phy_intr = (1 << sw->phy_port_cnt) - 1;
		for (i = sw->phy_port_cnt; i <= sw->mib_port_cnt; i++)
			if (sw->port_info[i].phy)
				sw->phy_intr |= (1 << i);
	}
	sw->ops->acquire(sw);
	for (i = sw->dev_offset; i < dev_cnt; i++) {
		struct phy_priv *phydata;
		int n = i + s;

		port = sw->netport[i];
		phydata = &sw->phydata[n];
		if (!port)
			port = phydata->port;
		changes |= port_get_link_speed(port);
		if (sw_port)
			sw_port->live_ports |= port->live_ports;

		/* Copy all port information for user access. */
		if (port != phydata->port)
			copy_port_status(port, phydata->port);
	}
	if (sw->phy_intr && sw->port_info[sw->HOST_PORT].phy) {
		port = sw->phydata[sw->mib_port_cnt + 1].port;
		port_get_link_speed(port);
	}
	sw->phy_intr = 0;
	sw->ops->release(sw);

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
		if (media_connected == port->linked->state &&
		    port->linked->phy) {
			sw_port->linked = port->linked;
			break;
		}
	}
}  /* link_read_work */

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

#ifndef CONFIG_KSZ_NO_MDIO_BUS
	struct phy_device *phydev;
	struct phy_priv *priv;
	int i;

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
#endif
	if (!(hw_priv->intr_working & 2))
		schedule_delayed_work(&hw_priv->link_read, 0);

	ksz_update_timer(&hw_priv->monitor_timer_info);
}  /* ksz9897_dev_monitor */

#ifdef CONFIG_KSZ_DSA
#include "ksz_dsa.c"
#endif

static int intr_mode;
static int sw_host_port;
static int ports;


static int sw_device_present;

static int ksz_probe_prep(struct sw_priv *ks, void *dev)
{
	struct ksz_sw *sw;

#if defined(CONFIG_SPI_PEGASUS) || defined(CONFIG_SPI_PEGASUS_MODULE)
	intr_mode = 1;
#endif

	if (1 == intr_mode)
		ks->intr_mode = IRQF_TRIGGER_LOW | IRQF_ONESHOT;
	else if (2 == intr_mode)
		ks->intr_mode = IRQF_TRIGGER_FALLING;
	ks->intr_mode |= IRQF_ONESHOT;

	dev_set_drvdata(ks->dev, ks);

	mutex_init(&ks->hwlock);
	mutex_init(&ks->lock);

	sw = &ks->sw;
	mutex_init(&sw->lock);
	mutex_init(&sw->acllock);
	mutex_init(&sw->alulock);
	mutex_init(&sw->vlanlock);
	mutex_init(&sw->hsrlock);
	sw->hwlock = &ks->hwlock;
	sw->reglock = &ks->lock;
	sw->dev = ks;

	sw->info = kzalloc(sizeof(struct ksz_sw_info), GFP_KERNEL);
	if (!sw->info)
		return -ENOMEM;

	/* Save original register access. */
	sw->org_reg = sw->reg;
	sw->net_ops = &sw_net_ops;
	sw->ops = &sw_ops;
	init_waitqueue_head(&sw->queue);

#ifdef CONFIG_KSZ_IBA_ONLY
	if (dev) {
		sw->netdev[0] = dev;
		sw->features |= IBA_SUPPORT;
		sw->info->iba.use_iba = 2;
	}
#endif

#ifdef CONFIG_KSZ_IBA
	ksz_iba_init(&sw->info->iba, sw);
	INIT_DELAYED_WORK(&sw->set_ops, sw_set_ops);
#endif

	return 0;
}  /* ksz_probe_prep */

struct ksz_port_mapping {
	u8 id;
	u8 cnt;
	u8 p7_intf;
	u8 map[8];
};

enum {
	KSZ9897_SKU,
	KSZ9477_SKU,
	KSZ9896_SKU,
	KSZ9893_SKU,
	KSZ8565_SKU,

	KSZ9477_5_SKU,
	KSZ9477_3_SKU,
	KSZ9897_T_SKU,
	KSZ9897_U_SKU,
};

static struct ksz_port_mapping port_mappings[] = {
	{ KSZ9897_SKU,   7, INTF_RGMII, { 1, 2, 3, 4, 5, 6, 7, 0 }},
	{ KSZ9477_SKU,   7, INTF_SGMII, { 1, 2, 3, 4, 5, 7, 6, 0 }},
	{ KSZ9896_SKU,   6, INTF_RGMII, { 1, 2, 3, 4, 5, 6, 0, 0 }},
	{ KSZ9893_SKU,   3, INTF_RGMII, { 1, 2, 3, 0, 0, 0, 0, 0 }},
	{ KSZ8565_SKU,   5, INTF_RGMII, { 1, 2, 3, 4, 7, 0, 0, 0 }},

	{ KSZ9477_5_SKU, 5, INTF_SGMII, { 1, 2, 3, 4, 6, 0, 0, 0 }},
	{ KSZ9477_3_SKU, 3, INTF_SGMII, { 1, 2, 6, 0, 0, 0, 0, 0 }},
	{ KSZ9897_T_SKU, 6, INTF_RGMII, { 4, 3, 2, 1, 5, 6, 0, 0 }},
	{ KSZ9897_U_SKU, 6, INTF_RGMII, { 6, 4, 3, 2, 1, 5, 0, 0 }},
};

static u8 port_map[8];

static void ksz_setup_logical_ports(struct ksz_sw *sw, u8 id, uint ports)
{
	struct ksz_port_mapping *map;
	struct ksz_port_info *info;
	struct ksz_port_info *pinfo;
	uint i;
	uint l;
	uint n;
	uint p;
	int cnt = 0;

	for (i = 0; i < ARRAY_SIZE(port_mappings); i++) {
		map = &port_mappings[i];
		if (id == map->id) {
			cnt = map->cnt;
			memset(port_map, 0, 8 * sizeof(u8));
			memcpy(port_map, map->map, cnt * sizeof(u8));
			for (n = 0; n < sw->phy_port_cnt; n++) {
				info = &sw->port_info[n];
				info->intf = INTF_TX_PHY;
			}
			for (; n < cnt; n++) {
				info = &sw->port_info[n];
				info->intf = INTF_RGMII;
				if (n > 5)
					info->intf = map->p7_intf;
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
			if (!(ports & BIT(n - 1)))
				continue;
			p = n - 1;
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
dbg_msg("ports: %x\n", ports);

	for (n = 0; n <= i; n++) {
		info = &sw->port_info[n];
		pinfo = &sw->port_info[info->phy_p];
dbg_msg("%d= %d:%02x %d:%02x %d:%02x %d\n", n,
info->phy_p, info->phy_m, info->log_p, info->log_m,
pinfo->log_p, pinfo->log_m, pinfo->intf);
	}
#if 1
	if (i + 1 < sw->port_cnt) {
		for (n = 0; n < sw->port_cnt; n++) {
			info = &sw->port_info[n];
			if (!info->log_m)
dbg_msg(" %d= %d %d\n", n, info->log_p, info->intf);
			if (!info->log_m)
				info->log_p = sw->port_cnt;
		}
	}
#endif
	sw->PORT_MASK = ports;
dbg_msg("mask: %x %x %x\n", ports, sw->HOST_MASK, sw->PORT_MASK);
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
#ifdef CONFIG_KSZ_HSR
	if (sw->features & HSR_HW) {
		struct ksz_hsr_info *hsr = &sw->info->hsr;

dbg_msg("port_map %d %d %d %d %d %d %d:%d\n",
port_map[0], port_map[1], port_map[2], port_map[3], port_map[4], port_map[5],
hsr->ports[0], hsr->ports[1]);
		hsr->ports[0] = port_map[hsr->ports[0]] - 1;
		hsr->ports[1] = port_map[hsr->ports[1]] - 1;
		hsr->member = BIT(hsr->ports[0]) | BIT(hsr->ports[1]);
dbg_msg(" hsr member: %d:%d %x\n", hsr->ports[0], hsr->ports[1], hsr->member);
	}
#endif
}  /* ksz_setup_logical_ports */

static void xmii_hack(struct ksz_sw *sw, int pi, u16 *data, u16 orig,
	u8 *data_hi)
{
	*data_hi ^= (PORT_MII_NOT_1GBIT | PORT_MII_MAC_MODE | PORT_MII_SEL_M);
	port_w8(sw, pi, REG_PORT_XMII_CTRL_1, *data_hi);
	*data = orig;
	port_w8(sw, pi, REG_PORT_XMII_CTRL_1, *data_hi);
}  /* xmii_hack */

static int ksz_probe_next(struct sw_priv *ks)
{
	struct ksz_sw *sw = &ks->sw;
	struct ksz_port_info *info;
	u32 id;
	u32 id1;
	u32 id2;
	u8 sku;
	int i;
	uint p;
	uint mib_port_count;
	uint phy_port_count;
	uint pi;
	uint port_count;
	int reset = true;
	int ret = -ENODEV;

#ifdef CONFIG_KSZ_IBA
	if (sw->info->iba.use_iba)
		reset = false;
#endif

	sw->ops->acquire(sw);

#ifndef CONFIG_KSZ_IBA_ONLY
	/* Turn off SPI auto edge detection. */
	sw->reg->w8(sw, REG_SW_GLOBAL_SERIAL_CTRL_0, 0);
#endif

	/* simple check for a valid chip being connected to the bus */
	id = sw->reg->r32(sw, REG_CHIP_ID0__1);
	sw->ops->release(sw);
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
		goto err_mii;
	}
	dev_info(ks->dev, "chip id 0x%08x\n", id);

	port_count = 1;
	mib_port_count = 1;
	phy_port_count = 1;
#ifdef CONFIG_1588_PTP
	if ((FAMILY_ID_95 & 0x0f) == (id1 & 0x0f)) {
		sw->features |= PTP_HW;
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
	sku = KSZ9897_SKU;
	if ((CHIP_ID_67 & 0x0f) == (id2 & 0x0f)) {
		port_count = 7;
		mib_port_count = 7;
		phy_port_count = 5;
		sw->TAIL_TAG_SHIFT = 7;
		sw->TAIL_TAG_LOOKUP = (1 << (7 + 3));
		sw->TAIL_TAG_OVERRIDE = (1 << (7 + 2));
		sku = KSZ9897_SKU;
	} else if ((CHIP_ID_66 & 0x0f) == (id2 & 0x0f)) {
		port_count = 6;
		mib_port_count = 6;
		phy_port_count = 5;
		sw->TAIL_TAG_SHIFT = 7;
		sw->TAIL_TAG_LOOKUP = (1 << (7 + 3));
		sw->TAIL_TAG_OVERRIDE = (1 << (7 + 2));
		sku = KSZ9896_SKU;
	} else if ((CHIP_ID_63 & 0x0f) == (id2 & 0x0f)) {
		port_count = 3;
		mib_port_count = 3;
		phy_port_count = 2;
		sw->TAIL_TAG_SHIFT = 3;
		sw->TAIL_TAG_LOOKUP = (1 << (3 + 3));
		sw->TAIL_TAG_OVERRIDE = (1 << (3 + 2));
		sw->features |= IS_9893;
		sku = KSZ9893_SKU;
	}
	sw->PORT_INTR_MASK = (1 << port_count) - 1;
	sw->PORT_MASK = (1 << port_count) - 1;

	sw->id = sw_device_present;

	/* Check for S2 revision. */
	sw->ops->acquire(sw);
	id = sw->reg->r8(sw, REG_GLOBAL_OPTIONS);
	sw->ops->release(sw);
	if (id) {
		u16 val;

		sw->revision = 1;

		sw->ops->acquire(sw);
		port_r16(sw, 0, REG_PORT_INT_STATUS & ~1, &val);
		sw->ops->release(sw);
		if (!(val & PORT_PHY_INT)) {
			sw->revision = 2;
		}

		sw->features &= ~SETUP_PHY;
		sw->features |= NEW_CAP;

		/* Only new KSZ9897 changes XMII definitions. */
		if ((CHIP_ID_63 & 0x0f) != (id2 & 0x0f)) {
			sw->features |= NEW_XMII;
			if (id & SW_REDUNDANCY_ABLE) {
				sw->features |= REDUNDANCY_SUPPORT;
#ifdef CONFIG_KSZ_HSR
				sw->features |= HSR_HW;
#endif
			}
		} else {
			if (id & SW_QW_ABLE)
				sw->features |= QW_HW;
			else
				sw->features |= GIGABIT_SUPPORT;
		}
		if (id & SW_AVB_ABLE) {
			sw->features |= AVB_SUPPORT;
#ifdef CONFIG_1588_PTP
			sw->features |= PTP_HW;
#endif
		}

		/* DLR can be used if supervisor is not needed. */
#ifdef CONFIG_KSZ_DLR
		sw->features |= DLR_HW;
#endif

		switch (id & 0x0f) {
		case SW_9477_SL_5_2:
			/* Last port is SGMII. */
			if (!sw_host_port)
				sw_host_port = 6;
			sku = KSZ9477_SKU;
			break;
		}
		if (id & SW_GIGABIT_ABLE)
			sw->features |= GIGABIT_SUPPORT;

		if (sw->features & IS_9893)
dbg_msg("avb=%d  qw=%d  giga=%d\n",
!!(id & SW_AVB_ABLE), !!(id & SW_QW_ABLE), !!(id & SW_GIGABIT_ABLE));
		else
dbg_msg("avb=%d  rr=%d  giga=%d\n",
!!(id & SW_AVB_ABLE), !!(id & SW_REDUNDANCY_ABLE), !!(id & SW_GIGABIT_ABLE));
	} else if ((FAMILY_ID_95 & 0x0f) == (id1 & 0x0f))
		sw->features |= AVB_SUPPORT;
	if ((sw->features & (HSR_HW | DLR_HW)) && port_count > 3)
		sw->overrides |= HAVE_MORE_THAN_2_PORTS;
	if (sw->features & IS_9893) {
		sw->chip_id = KSZ9893_SW_CHIP;
		if (sw->features & AVB_SUPPORT) {
			if (sw->features & GIGABIT_SUPPORT)
				sw->chip_id = KSZ9563_SW_CHIP;
			else
				sw->chip_id = KSZ8563_SW_CHIP;
		}
	} else {
		sw->chip_id = KSZ9897_SW_CHIP;
		if (port_count == 6)
			sw->chip_id = KSZ9896_SW_CHIP;
		if (sw->features & REDUNDANCY_SUPPORT)
			sw->chip_id = KSZ9477_SW_CHIP;
		else if (sw->features & AVB_SUPPORT) {
			if (sw->features & GIGABIT_SUPPORT) {
				sw->chip_id = KSZ9567_SW_CHIP;
				if (port_count == 6)
					sw->chip_id = KSZ9566_SW_CHIP;
			} else {
				sw->chip_id = KSZ8567_SW_CHIP;
			}
		}
	}
	if (ks->dev->of_node) {
		int score;
		char name[80];

		if (!of_modalias_node(ks->dev->of_node, name, sizeof(name)))
			dbg_msg(" compatible: %s\n", name);
		score = of_device_is_compatible(ks->dev->of_node,
						"microchip,ksz8565");
		if (score > 0 && sw->chip_id == KSZ8567_SW_CHIP) {
			sku = KSZ8565_SKU;
			sw->chip_id = KSZ8565_SW_CHIP;
		}
	}

	if (sw_host_port < 0 || sw_host_port > port_count)
		sw_host_port = 0;

#ifdef CONFIG_KSZ_IBA_ONLY
	if (!sw_host_port)
		sw_host_port = port_count;
#endif

	/* Select the host port. */
	if (sw_host_port > 0 && sw_host_port <= port_count) {
		sw->HOST_PORT = sw_host_port - 1;
	} else {
		sw->HOST_PORT = port_count - 1;
		sw_host_port = 0;
	}
	sw->HOST_MASK = (1 << sw->HOST_PORT);

	sw->dev_count = 1;

	sw->mib_cnt = TOTAL_SWITCH_COUNTER_NUM;
	sw->mib_port_cnt = mib_port_count;
	sw->phy_port_cnt = phy_port_count;
	sw->port_cnt = port_count;

#ifdef DEBUG
	sw->verbose = 1;
#endif
	if (authen)
		sw->overrides |= USE_802_1X_AUTH;
	if (!(sw->features & AVB_SUPPORT) || !(sw->features & PTP_HW)) {
		avb = 0;
	} else if (avb < 0) {
		avb = 0;
		if (!(sw->features & IS_9893))
			avb = 1;
	}

#ifndef CONFIG_KSZ_DSA
	if (multi_dev < 0 && (avb || sw->features & (PTP_HW) ||
	    sw->overrides & (USE_802_1X_AUTH))) {
		multi_dev = 3;
		if (!(sw->overrides & (USE_802_1X_AUTH)) && stp < 0)
			stp = 1;
	}
	if (multi_dev < 0)
		multi_dev = 0;
	if (stp < 0)
		stp = 0;
#endif
#ifdef CONFIG_KSZ_DSA
	avb = 0;
	authen = 0;
	multi_dev = 1;
	stp = 0;
#endif

	/* No specific ports are specified. */
	if (!ports)
		ports = sw->PORT_MASK;
dbg_msg("ports: %x\n", ports);

	ports = sw_setup_zone(sw, ports);

	ksz_setup_logical_ports(sw, sku, ports);

	sw->PORT_MASK |= sw->HOST_MASK;
dbg_msg("mask: %x %x; %x %x\n", sw->HOST_MASK, sw->PORT_MASK,
sw->TAIL_TAG_LOOKUP, sw->TAIL_TAG_OVERRIDE);
dbg_msg("port: %x %x %x\n", sw->port_cnt, sw->mib_port_cnt, sw->phy_port_cnt);

	INIT_DELAYED_WORK(&ks->link_read, link_read_work);

	/* No SGMII setting. */
	if (sgmii < 0) {

		/* Direct connect. */
		if (sw->HOST_PORT == 6)
			sgmii = 0;
		else
			sgmii = 1;
	}
	sw->sgmii_mode = sgmii;

	for (pi = 0; pi < phy_port_count; pi++) {
		/*
		 * Initialize to invalid value so that link detection
		 * is done.
		 */
		info = get_port_info(sw, pi);
		info->link = 0xFF;
		info->state = media_disconnected;
		info->get_link_speed = phy_port_get_speed;
		info->set_link_speed = phy_port_set_speed;
		info->force_link_speed = phy_port_force_speed;
		info->phy = true;
		info->report = true;
	}
	sw->interface = PHY_INTERFACE_MODE_RGMII;
	sw->ops->acquire(sw);
	for (; pi < sw->port_cnt; pi++) {
		u16 data;
		u16 orig;
		u8 *data_lo;
		u8 *data_hi;
		int speed;
		phy_interface_t phy;
		int gbit;
		int mode;

		if (sw->TAIL_TAG_SHIFT != 7)
			mode = 2;
		else
			mode = 5;
		info = get_port_info(sw, pi);
		if (pi < mode) {
#ifdef CONFIG_KSZ_IBA_ONLY
			if (pi == sw->HOST_PORT) {
				info->state = media_connected;
				sw->live_ports |= (1 << pi);
				info->tx_rate = 1000 * TX_RATE_UNIT;
				info->duplex = 2;
			}
#endif
			break;
		}
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
			if (reset)
				xmii_hack(sw, pi, &data, orig, data_hi);
		} else
			*data_hi &= ~(PORT_RGMII_ID_IG_ENABLE |
				PORT_RGMII_ID_EG_ENABLE);
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
#ifdef USE_MII_MODE
		sw_set_gbit(sw, false, data_hi);
		sw_set_xmii(sw, 0, data_hi);
#endif
#ifdef USE_GMII_MODE
		sw_set_gbit(sw, true, data_hi);
		sw_set_xmii(sw, 2, data_hi);
#endif
#ifdef USE_GMII_100_MODE
		sw_set_gbit(sw, false, data_hi);
#endif
#ifdef USE_RMII_MODE
		sw_set_gbit(sw, false, data_hi);
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
			speed = 1000;
			if (gbit)
				break;
		case 0:
			phy = PHY_INTERFACE_MODE_MII;
			speed = 100;
			break;
		case 1:
			phy = PHY_INTERFACE_MODE_RMII;
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
			speed = 100;
			if (gbit)
				speed = 1000;
			break;
		}
		if (*data_lo & PORT_SGMII_SEL) {
			phy = PHY_INTERFACE_MODE_SGMII;
			info->link = 0xFF;
			info->state = media_disconnected;
			info->get_link_speed = sgmii_port_get_speed;
			info->set_link_speed = sgmii_port_set_speed;
			info->phy = port_sgmii_detect(sw, pi);
			if (info->phy)
				info->report = true;
		}
		info->interface = phy;
		if (sw->HOST_PORT == pi)
			sw->interface = phy;
		if (sw->HOST_PORT == pi)
dbg_msg("host: %d %d\n", sw->HOST_PORT, sw->interface);
		if (info->phy)
			info->state = media_disconnected;
		else if (info->intf == INTF_RGMII) {
			info->state = media_connected;
			sw->live_ports |= (1 << pi);
		}
		if (!(*data_lo & PORT_MII_100MBIT))
			info->tx_rate = 10 * TX_RATE_UNIT;
		else
			info->tx_rate = speed * TX_RATE_UNIT;
		if (*data_lo & PORT_MII_FULL_DUPLEX)
			info->duplex = 2;
		else
			info->duplex = 1;
		info->flow_ctrl = 0x33;
		sw->cached.xmii[pi - sw->phy_port_cnt] = (*data_lo << 8) |
			*data_hi;
dbg_msg("xmii: %04x %02x %02x; %u %u\n", orig, *data_lo, *data_hi,
info->tx_rate / TX_RATE_UNIT, info->duplex);
	}
	sw->ops->release(sw);

	sw_init_phy_priv(ks);

#ifndef CONFIG_KSZ_NO_MDIO_BUS
	ret = ksz_mii_init(ks);
	if (ret)
		goto err_mii;

#else
	phydev = &sw->phy_map[0];
	sw_init_phydev(sw, phydev);
#endif

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

#ifdef CONFIG_KSZ_MRP
	if (sw->features & AVB_SUPPORT) {
		sw->features |= MRP_SUPPORT;
	}
#endif

	sw->counter = ks->counter;
	sw->monitor_timer_info = &ks->monitor_timer_info;
	sw->link_read = &ks->link_read;

	sw_setup_mib(sw);
	sw_init_mib(sw);

	for (i = 0; i < TOTAL_PORT_NUM; i++)
		init_waitqueue_head(&ks->counter[i].counter);

#ifndef CONFIG_KSZ_IBA_ONLY
	create_debugfs(ks);
#endif

#ifdef CONFIG_KSZ_STP
	ksz_stp_init(&sw->info->rstp, sw);
#endif
#ifdef CONFIG_KSZ_DLR
	if (sw->features & DLR_HW)
		ksz_dlr_init(&sw->info->dlr, sw);
#endif
#ifdef CONFIG_KSZ_HSR
	if (sw->features & HSR_HW)
		ksz_hsr_init(&sw->info->hsr, sw);
#endif
	sw->ops->acquire(sw);

	/* Turn off PTP in case the feature is not enabled. */
	if (reset)
		sw->reg->w16(sw, REG_PTP_MSG_CONF1, 0);

	if (reset)
		sw_reset(sw);
	sw_init(sw);
	sw_setup(sw);
	sw_enable(sw);
	sw->ops->release(sw);
	sw->ops->init(sw);

#if 0
	sw->overrides |= SYSFS_PHY_PORT;
#endif

#if !defined(CONFIG_KSZ9897_EMBEDDED)
	init_sw_sysfs(sw, &ks->sysfs, ks->dev);
#ifdef CONFIG_KSZ_DLR
	if (sw->features & DLR_HW)
		init_dlr_sysfs(ks->dev);
#endif
#endif
#ifdef KSZSW_REGS_SIZE
	ret = sysfs_create_bin_file(&ks->dev->kobj,
		&kszsw_registers_attr);
	if (ret < 0)
		goto err_drv;
#endif
	sema_init(&ks->proc_sem, 1);

#ifdef NO_ATTACHED_DEV
	sw->ops->acquire(sw);
	phydev = sw->phydev;
	priv = phydev->priv;
	port = priv->port;
	port_set_link_speed(port);
	sw->ops->release(sw);
#endif

	INIT_WORK(&sw->set_addr, sw_delayed_set_addr);
	INIT_WORK(&sw->tx_fwd, sw_tx_fwd);
	skb_queue_head_init(&sw->txq);

	INIT_WORK(&ks->mib_read, ksz9897_mib_read_work);

	/* 500 ms timeout */
	ksz_init_timer(&ks->mib_timer_info, 500 * HZ / 1000,
		ksz9897_mib_monitor, ks);
	ksz_init_timer(&ks->monitor_timer_info, 100 * HZ / 1000,
		ksz9897_dev_monitor, ks);

	ksz_start_timer(&ks->mib_timer_info, ks->mib_timer_info.period);
	if (!(sw->multi_dev & 1) && !sw->stp)
		ksz_start_timer(&ks->monitor_timer_info,
			ks->monitor_timer_info.period * 10);

	sw_device_present++;

#ifdef CONFIG_1588_PTP
	if (sw->features & PTP_HW) {
		struct ptp_info *ptp = &sw->ptp_hw;

		ptp->ports = sw->mib_port_cnt;
#if 1
		if (1 == sw->multi_dev && (sw->features & SW_VLAN_DEV))
			ptp->ports = sw->eth_maps[0].cnt + 1;
#endif
		ptp->reg = &ptp_reg_ops;
		ptp->ops = &ptp_ops;
		ptp->parent = ks->dev;
		ptp->ops->init(ptp, sw->info->mac_addr);
#ifdef NO_ATTACHED_DEV
		ptp->reg->start(ptp, true);
#endif
		init_ptp_sysfs(&ks->ptp_sysfs, ks->dev);
	}
#endif
#ifdef CONFIG_KSZ_MRP
	if (sw->features & MRP_SUPPORT) {
		struct mrp_info *mrp = &sw->mrp;

		INIT_DELAYED_WORK(&sw->set_mrp, sw_set_mrp);
		mrp->ops = &mrp_ops;
		mrp->ops->init(mrp);
	}
#endif

#ifdef CONFIG_KSZ_DSA
	ksz_dsa_init();
#endif

	if (ks->irq <= 0)
		return 0;
	sw->ops->acquire(sw);
	if (!reset)
		sw_dis_intr(sw);
	sw->reg->w32(sw, REG_PTP_INT_STATUS__4, 0xffffffff);
	for (p = 0; p < sw->port_cnt; p++) {
		port_w(sw, p, REG_PORT_INT_MASK, 0xff);
		port_w16(sw, p, REG_PTP_PORT_TX_INT_STATUS__2, 0xffff);
	}
	sw->ops->release(sw);
	ret = sw_start_interrupt(ks, dev_name(ks->dev));
	if (ret < 0)
		printk(KERN_WARNING "No switch interrupt\n");
	else {
		sw->ops->acquire(sw);
		sw_ena_intr(sw);
		sw->ops->release(sw);
	}

	return 0;

err_drv:
#ifndef CONFIG_KSZ_NO_MDIO_BUS
	ksz_mii_exit(ks);
#endif

err_mii:

#ifdef CONFIG_KSZ_IBA
	ksz_iba_exit(&sw->info->iba);
#endif
	kfree(sw->info);

#ifndef CONFIG_KSZ_IBA_ONLY
	kfree(ks->hw_dev);
#endif
	kfree(ks);

	return ret;
}  /* ksz_probe_next */

#ifndef CONFIG_KSZ_IBA_ONLY
static int ksz_probe(struct sw_priv *ks)
{
	int ret = -ENODEV;

	ret = ksz_probe_prep(ks, NULL);
	if (ret)
		return ret;

	return ksz_probe_next(ks);
}
#endif

static int ksz_remove(struct sw_priv *ks)
{
	struct ksz_sw *sw = &ks->sw;

#ifdef CONFIG_KSZ_DSA
	ksz_dsa_cleanup();
#endif
#ifdef CONFIG_KSZ_MRP
	if (sw->features & MRP_SUPPORT) {
		struct mrp_info *mrp = &sw->mrp;

		cancel_delayed_work_sync(&sw->set_mrp);
		mrp->ops->exit(mrp);
	}
#endif
#ifdef CONFIG_1588_PTP
	if (sw->features & PTP_HW) {
		struct ptp_info *ptp = &sw->ptp_hw;

		exit_ptp_sysfs(&ks->ptp_sysfs, ks->dev);
#ifdef NO_ATTACHED_DEV
		ptp->ops->stop(ptp);
#endif
		ptp->ops->exit(ptp);
	}
#endif

	if (ks->irq > 0) {
#ifndef CONFIG_KSZ_IBA_ONLY
		sw->ops->acquire(sw);
		sw->reg->w32(sw, REG_SW_INT_MASK__4, 0xffffffff);
		sw->reg->w32(sw, REG_SW_PORT_INT_MASK__4, 0xffffffff);
		sw->ops->release(sw);
#endif
		sw_stop_interrupt(ks);
	}

#ifndef CONFIG_KSZ_NO_MDIO_BUS
	ksz_mii_exit(ks);
#endif
	ksz_stop_timer(&ks->monitor_timer_info);
	ksz_stop_timer(&ks->mib_timer_info);
	flush_work(&ks->mib_read);

	sysfs_remove_bin_file(&ks->dev->kobj, &kszsw_registers_attr);

#if !defined(CONFIG_KSZ9897_EMBEDDED)
#ifdef CONFIG_KSZ_DLR
	if (sw->features & DLR_HW)
		exit_dlr_sysfs(ks->dev);
#endif
	exit_sw_sysfs(sw, &ks->sysfs, ks->dev);
#endif
	sw->ops->exit(sw);
	cancel_delayed_work_sync(&ks->link_read);

#ifndef CONFIG_KSZ_IBA_ONLY
	delete_debugfs(ks);
#endif

#ifdef CONFIG_KSZ_STP
	ksz_stp_exit(&sw->info->rstp);
#endif
#ifdef CONFIG_KSZ_DLR
	if (sw->features & DLR_HW)
		ksz_dlr_exit(&sw->info->dlr);
#endif
#ifdef CONFIG_KSZ_HSR
	if (sw->features & HSR_HW)
		ksz_hsr_exit(&sw->info->hsr);
#endif
#ifdef CONFIG_KSZ_IBA
	ksz_iba_exit(&sw->info->iba);
#endif
	kfree(sw->info);
#ifndef CONFIG_KSZ_IBA_ONLY
	kfree(ks->hw_dev);
#endif
	kfree(ks);

	return 0;
}  /* ksz_remove */

module_param(fast_aging, int, 0);
module_param(multi_dev, int, 0);
module_param(stp, int, 0);
module_param(avb, int, 0);
module_param(mrp, int, 0);
module_param(authen, int, 0);
module_param(sgmii, int, 0);
MODULE_PARM_DESC(fast_aging, "Fast aging");
MODULE_PARM_DESC(multi_dev, "Multiple device interfaces");
MODULE_PARM_DESC(stp, "STP support");
MODULE_PARM_DESC(avb, "AVB support");
MODULE_PARM_DESC(mrp, "MRP support");
MODULE_PARM_DESC(authen, "802.1X Authentication");
MODULE_PARM_DESC(sgmii, "SGMII mode");

#ifdef CONFIG_1588_PTP
module_param(pps_gpo, int, 0);
module_param(mhz_gpo, int, 0);
MODULE_PARM_DESC(pps_gpo, "PPS GPIO");
MODULE_PARM_DESC(mhz_gpo, "10MHz GPIO");
#endif

#ifdef CONFIG_KSZ_IBA
module_param(iba, int, 0);
MODULE_PARM_DESC(iba, "IBA support");
#endif

module_param(intr_mode, int, 0);
MODULE_PARM_DESC(intr_mode,
	"Configure which interrupt mode to use(1=level low, 2=falling)");

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

