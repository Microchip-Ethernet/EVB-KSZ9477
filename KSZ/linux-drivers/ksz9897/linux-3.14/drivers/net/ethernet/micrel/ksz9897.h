/**
 * Micrel KSZ9897 definition file
 *
 * Copyright (c) 2015 Microchip Technology Inc.
 *	Tristram Ha <Tristram.Ha@microchip.com>
 *
 * Copyright (c) 2013-2015 Micrel, Inc.
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

#ifndef __KSZ9897_H
#define __KSZ9897_H


#define KS_PRIO_M			0x7
#define KS_PRIO_S			4


/* 0 - Operation */
#define REG_CHIP_ID0__1			0x0000

#define REG_CHIP_ID1__1			0x0001

#define FAMILY_ID			0x95
#define FAMILY_ID_94			0x94
#define FAMILY_ID_95			0x95
#define FAMILY_ID_85			0x85
#define FAMILY_ID_98			0x98
#define FAMILY_ID_88			0x88

#define REG_CHIP_ID2__1			0x0002

#define CHIP_ID_63			0x63
#define CHIP_ID_66			0x66
#define CHIP_ID_67			0x67
#define CHIP_ID_77			0x77
#define CHIP_ID_93			0x93
#define CHIP_ID_96			0x96
#define CHIP_ID_97			0x97

#define REG_CHIP_ID3__1			0x0003

#define SWITCH_REVISION_M		0x0F
#define SWITCH_REVISION_S		4
#define SWITCH_RESET			0x01

#define REG_SW_PME_CTRL			0x0006

#define PME_ENABLE			(1 << 1)
#define PME_POLARITY			(1 << 0)

#define REG_GLOBAL_OPTIONS		0x000F

#define SW_GIGABIT_ABLE			(1 << 6)
#define SW_REDUNDANCY_ABLE		(1 << 5)
#define SW_AVB_ABLE			(1 << 4)

#define REG_SW_INT_STATUS__4		0x0010
#define REG_SW_INT_MASK__4		0x0014

#define LUE_INT				(1 << 31)
#define TRIG_TS_INT			(1 << 30)
#define APB_TIMEOUT_INT			(1 << 29)

#define SWITCH_INT_MASK			\
	(TRIG_TS_INT | APB_TIMEOUT_INT)

#define REG_SW_PORT_INT_STATUS__4	0x0018
#define REG_SW_PORT_INT_MASK__4		0x001C
#define REG_SW_PHY_INT_STATUS		0x0020
#define REG_SW_PHY_INT_ENABLE		0x0024

/* 1 - */
#define REG_SW_IBA__4			0x0104

#define SW_IBA_ENABLE			(1 << 31)
#define SW_IBA_DA_MATCH			(1 << 30)
#define SW_IBA_INIT			(1 << 29)
#define SW_IBA_QID_S			22
#define SW_IBA_QID_M			0xF
#define SW_IBA_PORT_S			16
#define SW_IBA_PORT_M			0x2F
#define SW_IBA_FRAME_TPID_M		0xFFFF

#define REG_SW_APB_TIMEOUT_ADDR__4	0x0108

#define APB_TIMEOUT_ACKNOWLEDGE		(1 << 31)

#define REG_SW_IBA_SYNC__1		0x010C

#define REG_SW_IO_STRENGTH__1		0x010D

#define REG_SW_IBA_STATUS__4		0x0110

#define SW_IBA_REQ			(1 << 31)
#define SW_IBA_RESP			(1 << 30)
#define SW_IBA_DA_MISMATCH		(1 << 14)
#define SW_IBA_FMT_MISMATCH		(1 << 13)
#define SW_IBA_CODE_ERROR		(1 << 12)
#define SW_IBA_CMD_ERROR		(1 << 11)
#define SW_IBA_CMD_LOC_M		((1 << 6) - 1)

#define REG_SW_IBA_STATES__4		0x0114

#define SW_IBA_BUF_STATE_S		30
#define SW_IBA_CMD_STATE_S		28
#define SW_IBA_RESP_STATE_S		26
#define SW_IBA_STATE_M			0x3
#define SW_IBA_PACKET_SIZE_S		16
#define SW_IBA_PACKET_SIZE_M		0x7F
#define SW_IBA_FMT_ID_M			0xFFFF

#define REG_SW_IBA_RESULT__4		0x0118

#define SW_IBA_SIZE_S			24

#define SW_IBA_RETRY_CNT_M		((1 << 5) - 1)


/* 2 - PHY */
#define REG_SW_POWER_MANAGEMENT_CTRL	0x0201

#define SW_PLL_POWER_DOWN		(1 << 5)
#define SW_POWER_DOWN_MODE		0x3
#define SW_ENERGY_DETECTION		1
#define SW_SOFT_POWER_DOWN		2
#define SW_POWER_SAVING			3

/* 3 - Operation Control */
#define REG_SW_OPERATION		0x0300

#define SW_DOUBLE_TAG			(1 << 7)
#define SW_RESET			(1 << 1)
#define SW_START			(1 << 0)

#define REG_SW_MAC_ADDR_0		0x0302
#define REG_SW_MAC_ADDR_1		0x0303
#define REG_SW_MAC_ADDR_2		0x0304
#define REG_SW_MAC_ADDR_3		0x0305
#define REG_SW_MAC_ADDR_4		0x0306
#define REG_SW_MAC_ADDR_5		0x0307

#define REG_SW_MTU__2			0x0308

#define REG_SW_ISP_TPID__2		0x030A

#define REG_SW_HSR_TPID__2		0x030C

#define REG_AVB_STRATEGY__2		0x030E

#define SW_SHAPING_CREDIT_ACCT		(1 << 1)
#define SW_POLICING_CREDIT_ACCT		(1 << 0)

#define REG_SW_LUE_CTRL_0		0x0310

#define SW_VLAN_ENABLE			(1 << 7)
#define SW_DROP_INVALID_VID		(1 << 6)
#define SW_AGE_CNT_M			0x7
#define SW_AGE_CNT_S			3
#define SW_RESV_MCAST_ENABLE		(1 << 2)
#define SW_HASH_OPTION_M		0x03
#define SW_HASH_OPTION_CRC		1
#define SW_HASH_OPTION_XOR		2
#define SW_HASH_OPTION_DIRECT		3

#define REG_SW_LUE_CTRL_1		0x0311

#define UNICAST_LEARN_DISABLE		(1 << 7)
#define SW_SRC_ADDR_FILTER		(1 << 6)
#define SW_FLUSH_STP_TABLE		(1 << 5)
#define SW_FLUSH_MSTP_TABLE		(1 << 4)
#define SW_FWD_MCAST_SRC_ADDR		(1 << 3)
#define SW_AGING_ENABLE			(1 << 2)
#define SW_FAST_AGING			(1 << 1)
#define SW_LINK_AUTO_AGING		(1 << 0)

#define REG_SW_LUE_CTRL_2		0x0312

#define SW_TRAP_DOUBLE_TAG		(1 << 6)
#define SW_EGRESS_VLAN_FILTER_DYN	(1 << 5)
#define SW_EGRESS_VLAN_FILTER_STA	(1 << 4)
#define SW_FLUSH_OPTION_M		0x3
#define SW_FLUSH_OPTION_S		2
#define SW_FLUSH_OPTION_DYN_MAC		1
#define SW_FLUSH_OPTION_STA_MAC		2
#define SW_FLUSH_OPTION_BOTH		3
#define SW_PRIO_M			0x3
#define SW_PRIO_DA			0
#define SW_PRIO_SA			1
#define SW_PRIO_HIGHEST_DA_SA		2
#define SW_PRIO_LOWEST_DA_SA		3

#define REG_SW_LUE_CTRL_3		0x0313

#define REG_SW_LUE_INT_STATUS		0x0314
#define REG_SW_LUE_INT_ENABLE		0x0315

#define LEARN_FAIL_INT			(1 << 2)
#define ALMOST_FULL_INT			(1 << 1)
#define WRITE_FAIL_INT			(1 << 0)

#define REG_SW_LUE_INDEX_0__2		0x0316

#define ENTRY_INDEX_M			0x0FFF

#define REG_SW_LUE_INDEX_1__2		0x0318

#define FAIL_INDEX_M			0x03FF

#define REG_SW_LUE_INDEX_2__2		0x031A

#define REG_SW_LUE_UNK_UCAST_CTRL__4	0x0320

#define SW_UNK_UNICAST_ENABLE		(1 << 31)

#define REG_SW_LUE_UNK_MCAST_CTRL__4	0x0324

#define SW_UNK_MULTICAST_ENABLE		(1 << 31)

#define REG_SW_LUE_UNK_VID_CTRL__4	0x0328

#define SW_UNK_VID_ENABLE		(1 << 31)

#define REG_SW_MAC_CTRL_0		0x0330

#define SW_NEW_BACKOFF			(1 << 7)
#define SW_CHECK_LENGTH			(1 << 3)
#define SW_AGGR_BACKOFF			(1 << 0)

#define REG_SW_MAC_CTRL_1		0x0331

#define MULTICAST_STORM_DISABLE		(1 << 6)
#define SW_BACK_PRESSURE		(1 << 5)
#define FAIR_FLOW_CTRL			(1 << 4)
#define NO_EXC_COLLISION_DROP		(1 << 3)
#define SW_JUMBO_PACKET			(1 << 2)
#define SW_LEGAL_PACKET_DISABLE		(1 << 1)
#define SW_PASS_SHORT_FRAME		(1 << 0)

#define REG_SW_MAC_CTRL_2		0x0332

#define SW_REPLACE_VID			(1 << 3)
#define BROADCAST_STORM_RATE_HI		0x07

#define REG_SW_MAC_CTRL_3		0x0333

#define BROADCAST_STORM_RATE_LO		0xFF
#define BROADCAST_STORM_RATE		0x07FF

#define REG_SW_MAC_CTRL_4		0x0334

#define SW_PASS_PAUSE			(1 << 3)

#define REG_SW_MAC_CTRL_5		0x0335

#define REG_SW_MAC_CTRL_6		0x0336

#define SW_MIB_COUNTER_FLUSH		(1 << 7)
#define SW_MIB_COUNTER_FREEZE		(1 << 6)
#if 0
#define SW_MIB_COUNTER_DONE		(1 << 0)
#endif

#define REG_SW_MAC_802_1P_MAP_0		0x0338
#define REG_SW_MAC_802_1P_MAP_1		0x0339
#define REG_SW_MAC_802_1P_MAP_2		0x033A
#define REG_SW_MAC_802_1P_MAP_3		0x033B

#define SW_802_1P_MAP_M			KS_PRIO_M
#define SW_802_1P_MAP_S			KS_PRIO_S

#define REG_SW_MAC_ISP_CTRL		0x033C

#define REG_SW_MAC_TOS_CTRL		0x033E

#define SW_TOS_DSCP_REMARK		(1 << 1)
#define SW_TOS_DSCP_REMAP		(1 << 0)

#define REG_SW_MAC_TOS_PRIO_0		0x0340
#define REG_SW_MAC_TOS_PRIO_1		0x0341
#define REG_SW_MAC_TOS_PRIO_2		0x0342
#define REG_SW_MAC_TOS_PRIO_3		0x0343
#define REG_SW_MAC_TOS_PRIO_4		0x0344
#define REG_SW_MAC_TOS_PRIO_5		0x0345
#define REG_SW_MAC_TOS_PRIO_6		0x0346
#define REG_SW_MAC_TOS_PRIO_7		0x0347
#define REG_SW_MAC_TOS_PRIO_8		0x0348
#define REG_SW_MAC_TOS_PRIO_9		0x0349
#define REG_SW_MAC_TOS_PRIO_10		0x034A
#define REG_SW_MAC_TOS_PRIO_11		0x034B
#define REG_SW_MAC_TOS_PRIO_12		0x034C
#define REG_SW_MAC_TOS_PRIO_13		0x034D
#define REG_SW_MAC_TOS_PRIO_14		0x034E
#define REG_SW_MAC_TOS_PRIO_15		0x034F
#define REG_SW_MAC_TOS_PRIO_16		0x0350
#define REG_SW_MAC_TOS_PRIO_17		0x0351
#define REG_SW_MAC_TOS_PRIO_18		0x0352
#define REG_SW_MAC_TOS_PRIO_19		0x0353
#define REG_SW_MAC_TOS_PRIO_20		0x0354
#define REG_SW_MAC_TOS_PRIO_21		0x0355
#define REG_SW_MAC_TOS_PRIO_22		0x0356
#define REG_SW_MAC_TOS_PRIO_23		0x0357
#define REG_SW_MAC_TOS_PRIO_24		0x0358
#define REG_SW_MAC_TOS_PRIO_25		0x0359
#define REG_SW_MAC_TOS_PRIO_26		0x035A
#define REG_SW_MAC_TOS_PRIO_27		0x035B
#define REG_SW_MAC_TOS_PRIO_28		0x035C
#define REG_SW_MAC_TOS_PRIO_29		0x035D
#define REG_SW_MAC_TOS_PRIO_30		0x035E
#define REG_SW_MAC_TOS_PRIO_31		0x035F

#define REG_SW_MRI_CTRL_0		0x0370

#define SW_IGMP_SNOOP			(1 << 6)
#define SW_IPV6_MLD_OPTION		(1 << 3)
#define SW_IPV6_MLD_SNOOP		(1 << 2)
#define SW_MIRROR_RX_TX			(1 << 0)

#define REG_SW_CLASS_D_IP_CTRL__4	0x0374

#define SW_CLASS_D_IP_ENABLE		(1 << 31)

#define REG_SW_MRI_CTRL_8		0x0378

#define SW_NO_COLOR_S			6
#define SW_RED_COLOR_S			4
#define SW_YELLOW_COLOR_S		2
#define SW_GREEN_COLOR_S		0
#define SW_COLOR_M			0x3

#define REG_SW_QM_CTRL			0x0390

#define PRIO_SCHEME_SELECT_M		0x3
#define PRIO_SCHEME_SELECT_S		2
#define UNICAST_VLAN_BOUNDARY		(1 << 1)

#define REG_SW_EEE_QM_CTRL__2		0x03C0

#define REG_SW_EEE_TXQ_WAIT_TIME__2	0x03C2

/* 4 - */
#define REG_SW_VLAN_ENTRY__4		0x0400

#define VLAN_VALID			(1 << 31)
#define VLAN_FORWARD_OPTION		(1 << 27)
#define VLAN_PRIO_S			24
#define VLAN_PRIO_M			0x3
#define VLAN_MSTP_S			12
#define VLAN_MSTP_M			0x3
#define VLAN_FID_M			0x7F

#define REG_SW_VLAN_ENTRY_UNTAG__4	0x0404
#define REG_SW_VLAN_ENTRY_PORTS__4	0x0408

#define REG_SW_VLAN_ENTRY_INDEX__2	0x040C

#define VLAN_INDEX_M			0x0FFF

#define REG_SW_VLAN_CTRL		0x040E

#define VLAN_START			(1 << 7)
#define VLAN_ACTION			0x3
#define VLAN_WRITE			1
#define VLAN_READ			2
#define VLAN_CLEAR			3

#define REG_SW_ALU_INDEX_0		0x0410

#define ALU_FID_INDEX_S			16
#define ALU_MAC_ADDR_HI			0xFFFF

#define REG_SW_ALU_INDEX_1		0x0414

#define ALU_DIRECT_INDEX_M		((1 << 12) - 1)

#define REG_SW_ALU_CTRL__4		0x0418

#define ALU_VALID_CNT_S			16
#define ALU_VALID_CNT_M			((1 << 14) - 1)
#define ALU_START			(1 << 7)
#define ALU_VALID			(1 << 6)
#define ALU_DIRECT			(1 << 2)
#define ALU_ACTION			0x3
#define ALU_WRITE			1
#define ALU_READ			2
#define ALU_SEARCH			3

#define REG_SW_ALU_STAT_CTRL__4		0x041C

#define ALU_STAT_INDEX_S		16
#define ALU_STAT_INDEX_M		((1 << 4) - 1)
#define ALU_RESV_MCAST_INDEX_M		((1 << 6) - 1)
#define ALU_STAT_START			(1 << 7)
#define ALU_RESV_MCAST_ADDR		(1 << 1)
#define ALU_STAT_READ			(1 << 0)

#define REG_SW_ALU_VAL_A		0x0420

#define ALU_V_STATIC_VALID		(1 << 31)
#define ALU_V_SRC_FILTER		(1 << 30)
#define ALU_V_DST_FILTER		(1 << 29)
#define ALU_V_PRIO_AGE_CNT_S		26
#define ALU_V_PRIO_AGE_CNT_M		((1 << 3) - 1)
#define ALU_V_MSTP_M			0x7

#define REG_SW_ALU_VAL_B		0x0424

#define ALU_V_OVERRIDE			(1 << 31)
#define ALU_V_USE_FID			(1 << 30)
#define ALU_V_PORT_MAP			((1 << 24) - 1)

#define REG_SW_ALU_VAL_C		0x0428

#define ALU_V_FID_S			16
#define ALU_V_FID_M			((1 << 16) - 1)
#define ALU_V_MAC_ADDR_HI		0xFFFF

#define REG_SW_ALU_VAL_D		0x042C

/* 5 - PTP Clock */
#define REG_PTP_CLK_CTRL		0x0500

#define PTP_STEP_ADJ			(1 << 6)
#define PTP_STEP_DIR			(1 << 5)
#define PTP_READ_TIME			(1 << 4)
#define PTP_LOAD_TIME			(1 << 3)
#define PTP_CLK_ADJ_ENABLE		(1 << 2)
#define PTP_CLK_ENABLE			(1 << 1)
#define PTP_CLK_RESET			(1 << 0)

#define REG_PTP_RTC_SUB_NANOSEC__2	0x0502

#define PTP_RTC_SUB_NANOSEC_M		0x0007

#define REG_PTP_RTC_NANOSEC		0x0504
#define REG_PTP_RTC_NANOSEC_H		0x0504
#define REG_PTP_RTC_NANOSEC_L		0x0506

#define REG_PTP_RTC_SEC			0x0508
#define REG_PTP_RTC_SEC_H		0x0508
#define REG_PTP_RTC_SEC_L		0x050A

#define REG_PTP_SUBNANOSEC_RATE		0x050C
#define REG_PTP_SUBNANOSEC_RATE_H	0x050C

#define PTP_RATE_DIR			(1 << 31)
#define PTP_TMP_RATE_ENABLE		(1 << 30)

#define REG_PTP_SUBNANOSEC_RATE_L	0x050E

#define REG_PTP_RATE_DURATION		0x0510
#define REG_PTP_RATE_DURATION_H		0x0510
#define REG_PTP_RATE_DURATION_L		0x0512

#define REG_PTP_MSG_CONF1		0x0514

#define PTP_802_1AS			(1 << 7)
#define PTP_ENABLE			(1 << 6)
#define PTP_ETH_ENABLE			(1 << 5)
#define PTP_IPV4_UDP_ENABLE		(1 << 4)
#define PTP_IPV6_UDP_ENABLE		(1 << 3)
#define PTP_TC_P2P			(1 << 2)
#define PTP_MASTER			(1 << 1)
#define PTP_1STEP			(1 << 0)

#define REG_PTP_MSG_CONF2		0x0516

#define PTP_UNICAST_ENABLE		(1 << 12)
#define PTP_ALTERNATE_MASTER		(1 << 11)
#define PTP_ALL_HIGH_PRIO		(1 << 10)
#define PTP_SYNC_CHECK			(1 << 9)
#define PTP_DELAY_CHECK			(1 << 8)
#define PTP_PDELAY_CHECK		(1 << 7)
#define PTP_DROP_SYNC_DELAY_REQ		(1 << 5)
#define PTP_DOMAIN_CHECK		(1 << 4)
#define PTP_UDP_CHECKSUM		(1 << 2)

#define REG_PTP_DOMAIN_VERSION		0x0518
#define PTP_VERSION_M			0xFF00
#define PTP_DOMAIN_M			0x00FF

#define REG_PTP_UNIT_INDEX__4		0x0520

#define PTP_UNIT_M			0xF

/* 2013-09-10 */
#define PTP_GPIO_INDEX_S		16
#define PTP_TSI_INDEX_S			8
#define PTP_TOU_INDEX_S			0

#define REG_PTP_TRIG_STATUS__4		0x0524

#define TRIG_ERROR_S			16
#define TRIG_DONE_S			0

#define REG_PTP_INT_STATUS__4		0x0528

#define TRIG_INT_S			16
#define TS_INT_S			0

#define TRIG_UNIT_M			0x7
#define TS_UNIT_M			0x3

#define REG_PTP_CTRL_STAT__4		0x052C

#define GPIO_IN				(1 << 7)
#define GPIO_OUT			(1 << 6)
#define TS_INT_ENABLE			(1 << 5)
#define TRIG_ACTIVE			(1 << 4)
#define TRIG_ENABLE			(1 << 3)
#define TRIG_RESET			(1 << 2)
#define TS_ENABLE			(1 << 1)
#define TS_RESET			(1 << 0)

#define GPIO_CTRL_M			\
	(GPIO_IN | GPIO_OUT)

#define TRIG_CTRL_M			\
	(TRIG_ACTIVE | TRIG_ENABLE | TRIG_RESET)

#define TS_CTRL_M			\
	(TS_INT_ENABLE | TS_ENABLE | TS_RESET)

#define REG_TRIG_TARGET_NANOSEC		0x0530
#define REG_TRIG_TARGET_SEC		0x0534

#define REG_TRIG_CTRL__4		0x0538

#define TRIG_CASCADE_ENABLE		(1 << 31)
#define TRIG_CASCADE_TAIL		(1 << 30)
#define TRIG_CASCADE_UPS_S		26
#define TRIG_CASCADE_UPS_M		0xF
#define TRIG_NOW			(1 << 25)
#define TRIG_NOTIFY			(1 << 24)
#define TRIG_EDGE			(1 << 23)
#define TRIG_PATTERN_S			20
#define TRIG_PATTERN_M			0x7
#define TRIG_NEG_EDGE			0
#define TRIG_POS_EDGE			1
#define TRIG_NEG_PULSE			2
#define TRIG_POS_PULSE			3
#define TRIG_NEG_PERIOD			4
#define TRIG_POS_PERIOD			5
#define TRIG_REG_OUTPUT			6
#define TRIG_GPO_S			16
#define TRIG_GPO_M			0xF
#define TRIG_CASCADE_ITERATE_CNT_M	0xFFFF

#define REG_TRIG_CYCLE_WIDTH		0x053C

#define REG_TRIG_CYCLE_CNT		0x0540

#define TRIG_CYCLE_CNT_S		16
#define TRIG_CYCLE_CNT_M		0xFFFF
#define TRIG_BIT_PATTERN_M		0xFFFF

#define REG_TRIG_ITERATE_TIME		0x0544

#define REG_TRIG_PULSE_WIDTH__4		0x0548

#define TRIG_PULSE_WIDTH_M		0x00FFFFFF

#define REG_TS_CTRL_STAT__4		0x0550

#define TS_EVENT_DETECT_S		17
#define TS_EVENT_DETECT_M		0xF
#define TS_EVENT_OVERFLOW		(1 << 16)
#define TS_GPI_S			8
#define TS_GPI_M			0xF
#define TS_DETECT_RISE			(1 << 7)
#define TS_DETECT_FALL			(1 << 6)
#define TS_DETECT_S			6
#define TS_CASCADE_TAIL			(1 << 5)
#define TS_CASCADE_UPS_S		1
#define TS_CASCADE_UPS_M		0xF
#define TS_CASCADE_ENABLE		(1 << 0)

#define DETECT_RISE			(TS_DETECT_RISE >> TS_DETECT_S)
#define DETECT_FALL			(TS_DETECT_FALL >> TS_DETECT_S)

#define REG_TS_EVENT_0_NANOSEC		0x0554
#define REG_TS_EVENT_0_SEC		0x0558
#define REG_TS_EVENT_0_SUB_NANOSEC	0x055C

#define REG_TS_EVENT_1_NANOSEC		0x0560
#define REG_TS_EVENT_1_SEC		0x0564
#define REG_TS_EVENT_1_SUB_NANOSEC	0x0568

#define REG_TS_EVENT_2_NANOSEC		0x056C
#define REG_TS_EVENT_2_SEC		0x0570
#define REG_TS_EVENT_2_SUB_NANOSEC	0x0574

#define REG_TS_EVENT_3_NANOSEC		0x0578
#define REG_TS_EVENT_3_SEC		0x057C
#define REG_TS_EVENT_3_SUB_NANOSEC	0x0580

#define REG_TS_EVENT_4_NANOSEC		0x0584
#define REG_TS_EVENT_4_SEC		0x0588
#define REG_TS_EVENT_4_SUB_NANOSEC	0x058C

#define REG_TS_EVENT_5_NANOSEC		0x0590
#define REG_TS_EVENT_5_SEC		0x0594
#define REG_TS_EVENT_5_SUB_NANOSEC	0x0598

#define REG_TS_EVENT_6_NANOSEC		0x059C
#define REG_TS_EVENT_6_SEC		0x05A0
#define REG_TS_EVENT_6_SUB_NANOSEC	0x05A4

#define REG_TS_EVENT_7_NANOSEC		0x05A8
#define REG_TS_EVENT_7_SEC		0x05AC
#define REG_TS_EVENT_7_SUB_NANOSEC	0x05B0

#define TS_EVENT_EDGE_S			30
#define TS_EVENT_EDGE_M			0x1
#define TS_EVENT_NANOSEC_M		((1 << 30) - 1)

#define TS_EVENT_SUB_NANOSEC_M		0x7

#define TS_EVENT_SAMPLE			\
	(REG_TS_EVENT_1_NANOSEC - REG_TS_EVENT_0_NANOSEC)


#define PORT_CTRL_ADDR(port, addr)	((addr) | (((port) + 1) << 12))

#define REG_GLOBAL_RR_INDEX__1		0x0600

/* DLR */
#define REG_DLR_SRC_PORT__4		0x0604

#define DLR_SRC_PORT_UNICAST		(1 << 31)
#define DLR_SRC_PORT_M			0x3
#define DLR_SRC_PORT_BOTH		0
#define DLR_SRC_PORT_EACH		1

#define REG_DLR_IP_ADDR__4		0x0608

#define REG_DLR_CTRL__1			0x0610

#define DLR_RESET_SEQ_ID		(1 << 3)
#define DLR_BACKUP_AUTO_ON		(1 << 2)
#define DLR_BEACON_TX_ENABLE		(1 << 1)
#define DLR_ASSIST_ENABLE		(1 << 0)

#define REG_DLR_STATE__1		0x0611

#define DLR_NODE_STATE_M		0x3
#define DLR_NODE_STATE_S		1
#define DLR_NODE_STATE_IDLE		0
#define DLR_NODE_STATE_FAULT		1
#define DLR_NODE_STATE_NORMAL		2
#define DLR_RING_STATE_FAULT		0
#define DLR_RING_STATE_NORMAL		1

#define REG_DLR_PRECEDENCE__1		0x0612

#define REG_DLR_BEACON_INTERVAL__4	0x0614

#define REG_DLR_BEACON_TIMEOUT__4	0x0618

#define REG_DLR_TIMEOUT_WINDOW__4	0x061C

#define DLR_TIMEOUT_WINDOW_M		((1 << 22) - 1)

#define REG_DLR_VLAN_ID__2		0x0620

#define DLR_VLAN_ID_M			((1 << 12) - 1)

#define REG_DLR_DEST_ADDR_0		0x0622
#define REG_DLR_DEST_ADDR_1		0x0623
#define REG_DLR_DEST_ADDR_2		0x0624
#define REG_DLR_DEST_ADDR_3		0x0625
#define REG_DLR_DEST_ADDR_4		0x0626
#define REG_DLR_DEST_ADDR_5		0x0627

#define REG_DLR_PORT_MAP__4		0x0628

#define REG_DLR_CLASS__1		0x062C

#define DLR_FRAME_QID_M			0x3

/* HSR */
#define REG_HSR_PORT_MAP__4		0x0640

#define REG_HSR_ALU_CTRL_0__1		0x0644

#define HSR_DUPLICATE_DISCARD		(1 << 7)
#define HSR_NODE_UNICAST		(1 << 6)
#define HSR_AGE_CNT_DEFAULT_M		0x7
#define HSR_AGE_CNT_DEFAULT_S		3
#define HSR_LEARN_MCAST_DISABLE		(1 << 2)
#define HSR_HASH_OPTION_M		0x3
#define HSR_HASH_DISABLE		0
#define HSR_HASH_UPPER_BITS		1
#define HSR_HASH_LOWER_BITS		2
#define HSR_HASH_XOR_BOTH_BITS		3

#define REG_HSR_ALU_CTRL_1__1		0x0645

#define HSR_LEARN_UCAST_DISABLE		(1 << 7)
#define HSR_FLUSH_TABLE			(1 << 5)
#define HSR_PROC_MCAST_SRC		(1 << 3)
#define HSR_AGING_ENABLE		(1 << 2)

#define REG_HSR_ALU_CTRL_2__2		0x0646

#define REG_HSR_ALU_AGE_PERIOD__4	0x0648

#define REG_HSR_ALU_INT_STATUS__1	0x064C
#define REG_HSR_ALU_INT_MASK__1		0x064D

#define HSR_WINDOW_OVERFLOW_INT		(1 << 3)
#define HSR_LEARN_FAIL_INT		(1 << 2)
#define HSR_ALMOST_FULL_INT		(1 << 1)
#define HSR_WRITE_FAIL_INT		(1 << 0)

#define REG_HSR_ALU_ENTRY_0__2		0x0650

#define HSR_ENTRY_INDEX_M		((1 << 10) - 1)
#define HSR_FAIL_INDEX_M		((1 << 8) - 1)

#define REG_HSR_ALU_ENTRY_1__2		0x0652

#define HSR_FAIL_LEARN_INDEX_M		((1 << 8) - 1)

#define REG_HSR_ALU_ENTRY_3__2		0x0654

#define HSR_CPU_ACCESS_ENTRY_INDEX_M	((1 << 8) - 1)


/* 0 - Operation */
#define REG_PORT_DEFAULT_VID		0x0000

#define REG_PORT_CUSTOM_VID		0x0002
#define REG_PORT_AVB_SR_1_VID		0x0004
#define REG_PORT_AVB_SR_2_VID		0x0006

#define REG_PORT_AVB_SR_1_TYPE		0x0008
#define REG_PORT_AVB_SR_2_TYPE		0x000A

#define REG_PORT_PME_STATUS		0x0013
#define REG_PORT_PME_CTRL		0x0017

#define PME_WOL_MAGICPKT		(1 << 2)
#define PME_WOL_LINKUP			(1 << 1)
#define PME_WOL_ENERGY			(1 << 0)

#define REG_PORT_INT_STATUS		0x001B
#define REG_PORT_INT_MASK		0x001F

#define PORT_PTP_INT			(1 << 2)
#define PORT_PHY_INT			(1 << 1)
#define PORT_ACL_INT			(1 << 0)

#define PORT_INT_MASK			\
	(PORT_PTP_INT | PORT_PHY_INT | PORT_ACL_INT)

#define REG_PORT_CTRL_0			0x0020

#define PORT_MAC_LOOPBACK		(1 << 7)
#define PORT_FORCE_TX_FLOW_CTRL		(1 << 4)
#define PORT_FORCE_RX_FLOW_CTRL		(1 << 3)
#define PORT_TAIL_TAG_ENABLE		(1 << 2)
#define PORT_QUEUE_SPLIT_ENABLE		0x3

#define REG_PORT_CTRL_1			0x0021

#define PORT_SRP_ENABLE			0x3

#define REG_PORT_STATUS_0		0x0030

#define PORT_INTF_SPEED_M		0x3
#define PORT_INTF_SPEED_S		3
#define PORT_INTF_FULL_DUPLEX		(1 << 2)
#define PORT_TX_FLOW_CTRL		(1 << 1)
#define PORT_RX_FLOW_CTRL		(1 << 0)

#define REG_PORT_STATUS_1		0x0034

/* 1 - PHY */
#define REG_PORT_PHY_CTRL		0x0100

#define PORT_PHY_RESET			(1 << 15)
#define PORT_PHY_LOOPBACK		(1 << 14)
#define PORT_SPEED_100MBIT		(1 << 13)
#define PORT_AUTO_NEG_ENABLE		(1 << 12)
#define PORT_POWER_DOWN			(1 << 11)
#define PORT_ISOLATE			(1 << 10)
#define PORT_AUTO_NEG_RESTART		(1 << 9)
#define PORT_FULL_DUPLEX		(1 << 8)
#define PORT_COLLISION_TEST		(1 << 7)
#define PORT_SPEED_1000MBIT		(1 << 6)
#if 0
#define PHY_HP_MDIX			(1 << 5)
#define PHY_FORCE_MDIX			(1 << 4)
#define PHY_AUTO_MDIX_DISABLE		(1 << 3)
#define PHY_REMOTE_FAULT_DISABLE	(1 << 2)
#define PHY_TRANSMIT_DISABLE		(1 << 1)
#define PHY_LED_DISABLE			(1 << 0)
#endif

#define REG_PORT_PHY_STATUS		0x0102

#define PORT_100BT4_CAPABLE		(1 << 15)
#define PORT_100BTX_FD_CAPABLE		(1 << 14)
#define PORT_100BTX_CAPABLE		(1 << 13)
#define PORT_10BT_FD_CAPABLE		(1 << 12)
#define PORT_10BT_CAPABLE		(1 << 11)
#define PORT_EXTENDED_STATUS		(1 << 8)
#define PORT_MII_SUPPRESS_CAPABLE	(1 << 6)
#define PORT_AUTO_NEG_ACKNOWLEDGE	(1 << 5)
#define PORT_REMOTE_FAULT		(1 << 4)
#define PORT_AUTO_NEG_CAPABLE		(1 << 3)
#define PORT_LINK_STATUS		(1 << 2)
#define PORT_JABBER_DETECT		(1 << 1)
#define PORT_EXTENDED_CAPABILITY	(1 << 0)

#define REG_PORT_PHY_ID_HI		0x0104
#define REG_PORT_PHY_ID_LO		0x0106

#define KSZ9897_ID_HI			0x0022
#define KSZ9897_ID_LO			0x1622

#define REG_PORT_PHY_AUTO_NEGOTIATION	0x0108

#define PORT_AUTO_NEG_NEXT_PAGE		(1 << 15)
#define PORT_AUTO_NEG_REMOTE_FAULT	(1 << 13)
#define PORT_AUTO_NEG_ASYM_PAUSE	(1 << 11)
#define PORT_AUTO_NEG_SYM_PAUSE		(1 << 10)
#define PORT_AUTO_NEG_100BT4		(1 << 9)
#define PORT_AUTO_NEG_100BTX_FD		(1 << 8)
#define PORT_AUTO_NEG_100BTX		(1 << 7)
#define PORT_AUTO_NEG_10BT_FD		(1 << 6)
#define PORT_AUTO_NEG_10BT		(1 << 5)
#define PORT_AUTO_NEG_SELECTOR		0x001F
#define PORT_AUTO_NEG_802_3		0x0001

#define PORT_AUTO_NEG_PAUSE		\
	(PORT_AUTO_NEG_ASYM_PAUSE | PORT_AUTO_NEG_SYM_PAUSE)

#define REG_PORT_PHY_REMOTE_CAPABILITY	0x010A

#define PORT_REMOTE_NEXT_PAGE		(1 << 15)
#define PORT_REMOTE_ACKNOWLEDGE		(1 << 14)
#define PORT_REMOTE_REMOTE_FAULT	(1 << 13)
#define PORT_REMOTE_ASYM_PAUSE		(1 << 11)
#define PORT_REMOTE_SYM_PAUSE		(1 << 10)
#define PORT_REMOTE_100BTX_FD		(1 << 8)
#define PORT_REMOTE_100BTX		(1 << 7)
#define PORT_REMOTE_10BT_FD		(1 << 6)
#define PORT_REMOTE_10BT		(1 << 5)

#define REG_PORT_PHY_1000_CTRL		0x0112

#define PORT_AUTO_NEG_MANUAL		(1 << 12)
#define PORT_AUTO_NEG_MASTER		(1 << 11)
#define PORT_AUTO_NEG_MASTER_PREFERRED	(1 << 10)
#define PORT_AUTO_NEG_1000BT_FD		(1 << 9)
#define PORT_AUTO_NEG_1000BT		(1 << 8)

#define REG_PORT_PHY_1000_STATUS	0x0114

#define PORT_MASTER_FAULT		(1 << 15)
#define PORT_LOCAL_MASTER		(1 << 14)
#define PORT_LOCAL_RX_OK		(1 << 13)
#define PORT_REMOTE_RX_OK		(1 << 12)
#define PORT_REMOTE_1000BT_FD		(1 << 11)
#define PORT_REMOTE_1000BT		(1 << 10)
#define PORT_REMOTE_IDLE_CNT_M		0x0F

#define PORT_PHY_1000_STATIC_STATUS	\
	(PORT_LOCAL_RX_OK |		\
	PORT_REMOTE_RX_OK |		\
	PORT_REMOTE_1000BT_FD |		\
	PORT_REMOTE_1000BT)

#define REG_PORT_PHY_MMD_SETUP		0x011A

#define PORT_MMD_OP_MODE_S		14
#define PORT_MMD_OP_MODE_M		0x3
#define PORT_MMD_OP_INDEX		0
#define PORT_MMD_OP_DATA_NO_INCR	1
#define PORT_MMD_OP_DATA_INCR_RW	2
#define PORT_MMD_OP_DATA_INCR_W		3
#define PORT_MMD_DEVICE_ID_M		0x1F

#define MMD_SETUP(mode, dev)		\
	(((u16) mode << PORT_MMD_OP_MODE_S) | dev)

#define REG_PORT_PHY_MMD_INDEX_DATA	0x011C

#define MMD_DEVICE_ID_DSP		1
#define MMD_DEVICE_ID_COMMON		2

#define MMD_DEVICE_ID_EEE_ADV		7

#define MMD_EEE_ADV			0x3C
#define EEE_ADV_100MBIT			(1 << 1)
#define EEE_ADV_1GBIT			(1 << 2)

#define MMD_EEE_LP_ADV			0x3D
#define MMD_EEE_MSG_CODE		0x3F

#define MMD_DEVICE_ID_AFED		0x1C

#define REG_PORT_PHY_EXTENDED_STATUS	0x011E

#define PORT_100BTX_FD_ABLE		(1 << 15)
#define PORT_100BTX_ABLE		(1 << 14)
#define PORT_10BT_FD_ABLE		(1 << 13)
#define PORT_10BT_ABLE			(1 << 12)

#define REG_PORT_PHY_REMOTE_LB_LED	0x0122

#define PORT_REMOTE_LOOPBACK		(1 << 8)
#define PORT_LED_SELECT			(3 << 6)
#define PORT_LED_CTRL			(3 << 4)
#define PORT_LED_CTRL_TEST		(1 << 3)
#define PORT_10BT_PREAMBLE		(1 << 2)
#define PORT_LINK_MD_10BT_ENABLE	(1 << 1)
#define PORT_LINK_MD_PASS		(1 << 0)

#define REG_PORT_PHY_LINK_MD		0x0124

#define PORT_START_CABLE_DIAG		(1 << 15)
#define PORT_TX_DISABLE			(1 << 14)
#define PORT_CABLE_DIAG_PAIR_S		12
#define PORT_CABLE_DIAG_PAIR_M		0x3
#define PORT_CABLE_DIAG_SELECT_S	10
#define PORT_CABLE_DIAG_SELECT_M	0x3
#define PORT_CABLE_DIAG_RESULT_S	8
#define PORT_CABLE_DIAG_RESULT_M	0x3
#define PORT_CABLE_STAT_NORMAL		0
#define PORT_CABLE_STAT_OPEN		1
#define PORT_CABLE_STAT_SHORT		2
#define PORT_CABLE_STAT_FAILED		3
#define PORT_CABLE_10M_SHORT		(1 << 12)
#define PORT_CABLE_FAULT_COUNTER	0x00FF

#define REG_PORT_PHY_PMA_STATUS		0x0126

#define PORT_1000_LINK_GOOD		(1 << 1)
#define PORT_100_LINK_GOOD		(1 << 0)

#define REG_PORT_PHY_DIGITAL_STATUS	0x0128

#define PORT_LINK_DETECT		(1 << 14)

#define REG_PORT_PHY__CTRL		30

#define PHY_STAT_REVERSED_POLARITY	(1 << 5)
#define PHY_STAT_MDIX			(1 << 4)
#define PHY_FORCE_LINK			(1 << 3)
#define PHY_POWER_SAVING_DISABLE	(1 << 2)
#define PHY_REMOTE_LOOPBACK		(1 << 1)

#define REG_PORT_PHY_RXER_COUNTER	0x012A

#define REG_PORT_PHY_INT_ENABLE		0x0136
#define REG_PORT_PHY_INT_STATUS		0x0137

#define JABBER_INT			(1 << 7)
#define RX_ERR_INT			(1 << 6)
#define PAGE_RX_INT			(1 << 5)
#define PARALLEL_DETECT_FAULT_INT	(1 << 4)
#define LINK_PARTNER_ACK_INT		(1 << 3)
#define LINK_DOWN_INT			(1 << 2)
#define REMOTE_FAULT_INT		(1 << 1)
#define LINK_UP_INT			(1 << 0)

#define REG_PORT_PHY_DIGITAL_DEBUG_1	0x0138

#define PORT_REG_CLK_SPEED_25_MHZ	(1 << 14)

#define REG_PORT_PHY_DIGITAL_DEBUG_2	0x013A

#define REG_PORT_PHY_DIGITAL_DEBUG_3	0x013C

#define PORT_100BT_FIXED_LATENCY	(1 << 15)

#define REG_PORT_PHY_PHY_CTRL		0x013E

#define PORT_INT_PIN_HIGH		(1 << 14)
#define PORT_ENABLE_JABBER		(1 << 9)
#define PORT_STAT_SPEED_1000MBIT	(1 << 6)
#define PORT_STAT_SPEED_100MBIT		(1 << 5)
#define PORT_STAT_SPEED_10MBIT		(1 << 4)
#define PORT_STAT_FULL_DUPLEX		(1 << 3)
#define PORT_STAT_MASTER		(1 << 2)
#define PORT_RESET			(1 << 1)
#define PORT_LINK_STATUS_FAIL		(1 << 0)

/* 3 - xMII */
#define REG_PORT_XMII_CTRL_0		0x0300

#define PORT_SGMII_SEL			(1 << 7)
#define PORT_MII_FULL_DUPLEX		(1 << 6)
#define PORT_MII_100MBIT		(1 << 4)
#define PORT_GRXC_ENABLE		(1 << 0)

#define REG_PORT_XMII_CTRL_1		0x0301

#define PORT_RMII_CLK_SEL		(1 << 7)
/* S1 */
#define PORT_MII_1000MBIT_S1		(1 << 6)
/* S2 */
#define PORT_MII_NOT_1GBIT		(1 << 6)
#define PORT_MII_SEL_EDGE		(1 << 5)
#define PORT_RGMII_ID_IG_ENABLE		(1 << 4)
#define PORT_RGMII_ID_EG_ENABLE		(1 << 3)
#define PORT_MII_MAC_MODE		(1 << 2)
#define PORT_MII_SEL_M			0x3
/* S1 */
#define PORT_MII_SEL_S1			0x0
#define PORT_RMII_SEL_S1		0x1
#define PORT_GMII_SEL_S1		0x2
#define PORT_RGMII_SEL_S1		0x3
/* S2 */
#define PORT_RGMII_SEL			0x0
#define PORT_RMII_SEL			0x1
#define PORT_GMII_SEL			0x2
#define PORT_MII_SEL			0x3

/* 4 - MAC */
#define REG_PORT_MAC_CTRL_0		0x0400

#define PORT_BROADCAST_STORM		(1 << 1)
#define PORT_JUMBO_FRAME		(1 << 0)

#define REG_PORT_MAC_CTRL_1		0x0401

#define PORT_BACK_PRESSURE		(1 << 3)
#define PORT_PASS_ALL			(1 << 0)

#define REG_PORT_MAC_CTRL_2		0x0402

#define PORT_100BT_EEE_DISABLE		(1 << 7)
#define PORT_1000BT_EEE_DISABLE		(1 << 6)

#define REG_PORT_MAC_IN_RATE_LIMIT	0x0403

#define PORT_IN_PORT_BASED_S		6
#define PORT_IN_PACKET_BASED_S		5
#define PORT_IN_FLOW_CTRL_S		4
#define PORT_COUNT_IFG_S		1
#define PORT_COUNT_PREAMBLE_S		0
#define PORT_IN_PORT_BASED		(1 << 6)
#define PORT_IN_PACKET_BASED		(1 << 5)
#define PORT_IN_FLOW_CTRL		(1 << 4)
#define PORT_IN_LIMIT_MODE_M		0x3
#define PORT_IN_LIMIT_MODE_S		2
#define PORT_IN_ALL			0
#define PORT_IN_UNICAST			1
#define PORT_IN_MULTICAST		2
#define PORT_IN_BROADCAST		3
#define PORT_COUNT_IFG			(1 << 1)
#define PORT_COUNT_PREAMBLE		(1 << 0)

#define REG_PORT_IN_RATE_0		0x0410
#define REG_PORT_IN_RATE_1		0x0411
#define REG_PORT_IN_RATE_2		0x0412
#define REG_PORT_IN_RATE_3		0x0413
#define REG_PORT_IN_RATE_4		0x0414
#define REG_PORT_IN_RATE_5		0x0415
#define REG_PORT_IN_RATE_6		0x0416
#define REG_PORT_IN_RATE_7		0x0417

#define REG_PORT_OUT_RATE_0		0x0420
#define REG_PORT_OUT_RATE_1		0x0421
#define REG_PORT_OUT_RATE_2		0x0422
#define REG_PORT_OUT_RATE_3		0x0423

#define PORT_RATE_LIMIT_M		((1 << 7) - 1)

/* 5 - MIB Counters */
#define REG_PORT_MIB_CTRL_STAT__4	0x0500

#define MIB_COUNTER_OVERFLOW		(1 << 31)
#define MIB_COUNTER_VALID		(1 << 30)
#define MIB_COUNTER_READ		(1 << 25)
#define MIB_COUNTER_FLUSH_FREEZE	(1 << 24)
#define MIB_COUNTER_INDEX_M		((1 << 8) - 1)
#define MIB_COUNTER_INDEX_S		16
#define MIB_COUNTER_DATA_HI_M		0xF

#define REG_PORT_MIB_DATA		0x0504

/* 6 - ACL */
#define REG_PORT_ACL_0			0x0600

#define ACL_FIRST_RULE_M		0xF

#define REG_PORT_ACL_1			0x0601

#define ACL_MODE_M			0x3
#define ACL_MODE_S			4
#define ACL_MODE_DISABLE		0
#define ACL_MODE_LAYER_2		1
#define ACL_MODE_LAYER_3		2
#define ACL_MODE_LAYER_4		3
#define ACL_ENABLE_M			0x3
#define ACL_ENABLE_S			2
#define ACL_ENABLE_2_COUNT		0
#define ACL_ENABLE_2_TYPE		1
#define ACL_ENABLE_2_MAC		2
#define ACL_ENABLE_2_BOTH		3
#define ACL_ENABLE_3_IP			1
#define ACL_ENABLE_3_SRC_DST_COMP	2
#define ACL_ENABLE_4_PROTOCOL		0
#define ACL_ENABLE_4_TCP_PORT_COMP	1
#define ACL_ENABLE_4_UDP_PORT_COMP	2
#define ACL_ENABLE_4_TCP_SEQN_COMP	3
#define ACL_SRC				(1 << 1)
#define ACL_EQUAL			(1 << 0)

#define REG_PORT_ACL_2			0x0602
#define REG_PORT_ACL_3			0x0603

#define ACL_MAX_PORT			0xFFFF

#define REG_PORT_ACL_4			0x0604
#define REG_PORT_ACL_5			0x0605

#define ACL_MIN_PORT			0xFFFF
#define ACL_IP_ADDR			0xFFFFFFFF
#define ACL_TCP_SEQNUM			0xFFFFFFFF

#define REG_PORT_ACL_6			0x0606

#define ACL_RESERVED			0xF8
#define ACL_PORT_MODE_M			0x3
#define ACL_PORT_MODE_S			1
#define ACL_PORT_MODE_DISABLE		0
#define ACL_PORT_MODE_EITHER		1
#define ACL_PORT_MODE_IN_RANGE		2
#define ACL_PORT_MODE_OUT_OF_RANGE	3

#define REG_PORT_ACL_7			0x0607

#define ACL_TCP_FLAG_ENABLE		(1 << 0)

#define REG_PORT_ACL_8			0x0608

#define ACL_TCP_FLAG_M			0xFF

#define REG_PORT_ACL_9			0x0609

#define ACL_TCP_FLAG			0xFF
#define ACL_ETH_TYPE			0xFFFF
#define ACL_IP_M			0xFFFFFFFF

#define REG_PORT_ACL_A			0x060A

#define ACL_PRIO_MODE_M			0x3
#define ACL_PRIO_MODE_S			6
#define ACL_PRIO_MODE_DISABLE		0
#define ACL_PRIO_MODE_HIGHER		1
#define ACL_PRIO_MODE_LOWER		2
#define ACL_PRIO_MODE_REPLACE		3
#define ACL_PRIO_M			KS_PRIO_M
#define ACL_PRIO_S			3
#define ACL_VLAN_PRIO_REPLACE		(1 << 2)
#define ACL_VLAN_PRIO_M			KS_PRIO_M
#define ACL_VLAN_PRIO_HI_M		0x3

#define REG_PORT_ACL_B			0x060B

#define ACL_VLAN_PRIO_LO_M		0x8
#define ACL_VLAN_PRIO_S			7
#define ACL_MAP_MODE_M			0x3
#define ACL_MAP_MODE_S			5
#define ACL_MAP_MODE_DISABLE		0
#define ACL_MAP_MODE_OR			1
#define ACL_MAP_MODE_AND		2
#define ACL_MAP_MODE_REPLACE		3

#define ACL_CNT_M			((1 << 11) - 1)
#define ACL_CNT_S			5

#define REG_PORT_ACL_C			0x060C

#define REG_PORT_ACL_D			0x060D
#define ACL_MSEC_UNIT			(1 << 6)
#define ACL_INTR_MODE			(1 << 5)
#define ACL_PORT_MAP			0x7F

#define REG_PORT_ACL_E			0x060E
#define REG_PORT_ACL_F			0x060F

#define REG_PORT_ACL_BYTE_EN_MSB	0x0610
#define REG_PORT_ACL_BYTE_EN_LSB	0x0611

#define ACL_ACTION_START		0xA
#define ACL_ACTION_LEN			4
#define ACL_INTR_CNT_START		0xD
#define ACL_RULESET_START		0xE
#define ACL_TABLE_LEN			16

#define ACL_ACTION_ENABLE		0x003C
#define ACL_MATCH_ENABLE		0xFFC3
#define ACL_BYTE_ENABLE			0xFFFF

#define REG_PORT_ACL_CTRL_0		0x0612

#define PORT_ACL_WRITE_DONE		(1 << 6)
#define PORT_ACL_READ_DONE		(1 << 5)
#define PORT_ACL_WRITE			(1 << 4)
#define PORT_ACL_INDEX_M		0xF

#define REG_PORT_ACL_CTRL_1		0x0613

/* 8 - Classification and Policing */
#define REG_PORT_MRI_MIRROR_CTRL	0x0800

#define PORT_MIRROR_RX			(1 << 6)
#define PORT_MIRROR_TX			(1 << 5)
#define PORT_MIRROR_SNIFFER		(1 << 1)

#define REG_PORT_MRI_PRIO_CTRL		0x0801

#define PORT_HIGHEST_PRIO		(1 << 7)
#define PORT_OR_PRIO			(1 << 6)
#define PORT_MAC_PRIO_ENABLE		(1 << 4)
#define PORT_VLAN_PRIO_ENABLE		(1 << 3)
#define PORT_802_1P_PRIO_ENABLE		(1 << 2)
#define PORT_DIFFSERV_PRIO_ENABLE	(1 << 1)
#define PORT_ACL_PRIO_ENABLE		(1 << 0)

#define REG_PORT_MRI_MAC_CTRL		0x0802

#define PORT_USER_PRIO_CEILING		(1 << 7)
#define PORT_DROP_NON_VLAN		(1 << 4)
#define PORT_DROP_TAG			(1 << 3)
#define PORT_BASED_PRIO_M		KS_PRIO_M
#define PORT_BASED_PRIO_S		0

#define REG_PORT_MRI_AUTHEN_CTRL	0x0803

#define PORT_ACL_ENABLE			(1 << 2)
#define PORT_AUTHEN_MODE		0x3
#define PORT_AUTHEN_PASS		0
#define PORT_AUTHEN_BLOCK		1
#define PORT_AUTHEN_TRAP		2

#define REG_PORT_MRI_INDEX__4		0x0804

#define MRI_INDEX_P_M			0x7
#define MRI_INDEX_P_S			16
#define MRI_INDEX_Q_M			0x3
#define MRI_INDEX_Q_S			0

#define REG_PORT_MRI_TC_MAP__4		0x0808

#define PORT_TC_MAP_M			0xf
#define PORT_TC_MAP_S			4

#define REG_PORT_MRI_POLICE_CTRL__4	0x080C

#define POLICE_DROP_ALL			(1 << 10)
#define POLICE_PACKET_TYPE_M		0x3
#define POLICE_PACKET_TYPE_S		8
#define POLICE_PACKET_DROPPED		0
#define POLICE_PACKET_GREEN		1
#define POLICE_PACKET_YELLOW		2
#define POLICE_PACKET_RED		3
#define PORT_BASED_POLICING		(1 << 7)
#define NON_DSCP_COLOR_M		0x3
#define NON_DSCP_COLOR_S		5
#define COLOR_MARK_ENABLE		(1 << 4)
#define COLOR_REMAP_ENABLE		(1 << 3)
#define POLICE_DROP_SRP			(1 << 2)
#define POLICE_COLOR_NOT_AWARE		(1 << 1)
#define POLICE_ENABLE			(1 << 0)

#define REG_PORT_POLICE_COLOR_0__4	0x0810
#define REG_PORT_POLICE_COLOR_1__4	0x0814
#define REG_PORT_POLICE_COLOR_2__4	0x0818
#define REG_PORT_POLICE_COLOR_3__4	0x081C

#define POLICE_COLOR_MAP_S		2
#define POLICE_COLOR_MAP_M		((1 << POLICE_COLOR_MAP_S) - 1)

#define REG_PORT_POLICE_RATE__4		0x0820

#define POLICE_CIR_S			16
#define POLICE_PIR_S			0

#define REG_PORT_POLICE_BURST_SIZE__4	0x0824

#define POLICE_BURST_SIZE_M		0x3FFF
#define POLICE_CBS_S			16
#define POLICE_PBS_S			0

#define REG_PORT_WRED_PM_CTRL_0__4	0x0830

#define WRED_PM_CTRL_M			((1 << 11) - 1)

#define WRED_PM_MAX_THRESHOLD_S		16
#define WRED_PM_MIN_THRESHOLD_S		0

#define REG_PORT_WRED_PM_CTRL_1__4	0x0834

#define WRED_PM_MULTIPLIER_S		16
#define WRED_PM_AVG_QUEUE_SIZE_S	0

#define REG_PORT_WRED_QUEUE_CTRL_0__4	0x0840
#define REG_PORT_WRED_QUEUE_CTRL_1__4	0x0844

#define REG_PORT_WRED_QUEUE_PMON__4	0x0848

#define WRED_RANDOM_DROP_ENABLE		(1 << 31)
#define WRED_PMON_FLUSH			(1 << 30)
#define WRED_DROP_GYR_DISABLE		(1 << 29)
#define WRED_DROP_YR_DISABLE		(1 << 28)
#define WRED_DROP_R_DISABLE		(1 << 27)
#define WRED_DROP_ALL			(1 << 26)
#define WRED_PMON_M			((1 << 24) - 1)

/* 9 - Shaping */

#define REG_PORT_MTI_QUEUE_INDEX__4	0x0900

#define REG_PORT_MTI_QUEUE_CTRL_0__4	0x0904

#define MTI_PVID_REPLACE		(1 << 0)

#define REG_PORT_MTI_QUEUE_CTRL_0	0x0914

#define MTI_SCHEDULE_MODE_M		0x3
#define MTI_SCHEDULE_MODE_S		6
#define MTI_SCHEDULE_STRICT_PRIO	0
#define MTI_SCHEDULE_WRR		2
#define MTI_SHAPING_M			0x3
#define MTI_SHAPING_S			4
#define MTI_SHAPING_OFF			0
#define MTI_SHAPING_SRP			1
#define MTI_SHAPING_TIME_AWARE		2
#if 0
#define MTI_PREEMPT_ENABLE		(1 << 3)
#endif

#define REG_PORT_MTI_QUEUE_CTRL_1	0x0915

#define MTI_TX_RATIO_M			((1 << 7) - 1)

#define REG_PORT_MTI_QUEUE_CTRL_2__2	0x0916
#define REG_PORT_MTI_HI_WATER_MARK	0x0916
#define REG_PORT_MTI_QUEUE_CTRL_3__2	0x0918
#define REG_PORT_MTI_LO_WATER_MARK	0x0918
#define REG_PORT_MTI_QUEUE_CTRL_4__2	0x091A
#define REG_PORT_MTI_CREDIT_INCREMENT	0x091A

/* A - QM */

#define REG_PORT_QM_CTRL__4		0x0A00

#define PORT_QM_DROP_PRIO_M		0x3

#define REG_PORT_VLAN_MEMBERSHIP__4	0x0A04

#define REG_PORT_QM_QUEUE_INDEX__4	0x0A08

#define PORT_QM_QUEUE_INDEX_S		24
#define PORT_QM_BURST_SIZE_S		16
#define PORT_QM_MIN_RESV_SPACE_M	((1 << 11) - 1)

#define REG_PORT_QM_WATER_MARK__4	0x0A0C

#define PORT_QM_HI_WATER_MARK_S		16
#define PORT_QM_LO_WATER_MARK_S		0
#define PORT_QM_WATER_MARK_M		((1 << 11) - 1)

#define REG_PORT_QM_TX_CNT_0__4		0x0A10

#define PORT_QM_TX_CNT_USED_S		0
#define PORT_QM_TX_CNT_M		((1 << 11) - 1)

#define REG_PORT_QM_TX_CNT_1__4		0x0A14

#define PORT_QM_TX_CNT_CALCULATED_S	16
#define PORT_QM_TX_CNT_AVAIL_S		0

/* B - LUE */
#define REG_PORT_LUE_CTRL		0x0B00

#define PORT_VLAN_LOOKUP_VID_0		(1 << 7)
#define PORT_INGRESS_FILTER		(1 << 6)
#define PORT_DISCARD_NON_VID		(1 << 5)
#define PORT_MAC_BASED_802_1X		(1 << 4)
#define PORT_SRC_ADDR_FILTER		(1 << 3)

#define REG_PORT_LUE_MSTP_INDEX		0x0B01

#define REG_PORT_LUE_MSTP_STATE		0x0B04

#define PORT_TX_ENABLE			(1 << 2)
#define PORT_RX_ENABLE			(1 << 1)
#define PORT_LEARN_DISABLE		(1 << 0)

/* C - PTP */

#define REG_PTP_PORT_RX_DELAY__2	0x0C00
#define REG_PTP_PORT_TX_DELAY__2	0x0C02
#define REG_PTP_PORT_ASYM_DELAY__2	0x0C04

#define REG_PTP_PORT_XDELAY_TS		0x0C08
#define REG_PTP_PORT_XDELAY_TS_H	0x0C08
#define REG_PTP_PORT_XDELAY_TS_L	0x0C0A

#define REG_PTP_PORT_SYNC_TS		0x0C0C
#define REG_PTP_PORT_SYNC_TS_H		0x0C0C
#define REG_PTP_PORT_SYNC_TS_L		0x0C0E

#define REG_PTP_PORT_PDRESP_TS		0x0C10
#define REG_PTP_PORT_PDRESP_TS_H	0x0C10
#define REG_PTP_PORT_PDRESP_TS_L	0x0C12

#define REG_PTP_PORT_TX_INT_STATUS__2	0x0C14
#define REG_PTP_PORT_TX_INT_ENABLE__2	0x0C16

#define PTP_PORT_SYNC_INT		(1 << 15)
#define PTP_PORT_XDELAY_REQ_INT		(1 << 14)
#define PTP_PORT_PDELAY_RESP_INT	(1 << 13)

#define REG_PTP_PORT_LINK_DELAY__4	0x0C18


/* Default values are used in ksz_sw_9897.h if these are not defined. */
#define PRIO_QUEUES			4
#define RX_PRIO_QUEUES			8

#define KS_PRIO_IN_REG			2

#define SWITCH_PORT_NUM			6

#define KSZ9897_COUNTER_NUM		0x20
#define TOTAL_KSZ9897_COUNTER_NUM	(KSZ9897_COUNTER_NUM + 2 + 2)

#define SWITCH_COUNTER_NUM		KSZ9897_COUNTER_NUM
#define TOTAL_SWITCH_COUNTER_NUM	TOTAL_KSZ9897_COUNTER_NUM

/* Required for common switch control in ksz_sw_9897.c */
#define SW_D				u8
#define SW_R(sw, addr)			(sw)->reg->r8(sw, addr)
#define SW_W(sw, addr, val)		(sw)->reg->w8(sw, addr, val)
#define SW_SIZE				(1)
#define SW_SIZE_STR			"%02x"
#define port_r				port_r8
#define port_w				port_w8

#define P_BCAST_STORM_CTRL		REG_PORT_MAC_CTRL_0
#define P_PRIO_CTRL			REG_PORT_MRI_PRIO_CTRL
#define P_MIRROR_CTRL			REG_PORT_MRI_MIRROR_CTRL
#define P_STP_CTRL			REG_PORT_LUE_MSTP_STATE
#define P_PHY_CTRL			REG_PORT_PHY_CTRL
#define P_NEG_RESTART_CTRL		REG_PORT_PHY_CTRL
#define P_LINK_STATUS			REG_PORT_PHY_STATUS
#define P_SPEED_STATUS			REG_PORT_PHY_PHY_CTRL
#define P_RATE_LIMIT_CTRL		REG_PORT_MAC_IN_RATE_LIMIT

#define S_LINK_AGING_CTRL		REG_SW_LUE_CTRL_1
#define S_MIRROR_CTRL			REG_SW_MRI_CTRL_0
#define S_REPLACE_VID_CTRL		REG_SW_MAC_CTRL_2
#define S_802_1P_PRIO_CTRL		REG_SW_MAC_802_1P_MAP_0
#define S_TOS_PRIO_CTRL			REG_SW_MAC_TOS_PRIO_0
#define S_FLUSH_TABLE_CTRL		REG_SW_LUE_CTRL_1

#define REG_SWITCH_RESET		REG_RESET_CTRL

#define SW_FLUSH_DYN_MAC_TABLE		SW_FLUSH_MSTP_TABLE


#define MAX_TIMESTAMP_UNIT		2
#define MAX_TRIG_UNIT			3
#define MAX_TIMESTAMP_EVENT_UNIT	8
#define MAX_GPIO			4

#define PTP_TRIG_UNIT_M			((1 << MAX_TRIG_UNIT) - 1)
#define PTP_TS_UNIT_M			((1 << MAX_TIMESTAMP_UNIT) - 1)

#endif
