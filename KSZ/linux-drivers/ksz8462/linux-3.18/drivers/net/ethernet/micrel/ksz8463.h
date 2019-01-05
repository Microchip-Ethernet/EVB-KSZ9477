/**
 * Microchip KSZ8463 definition file
 *
 * Copyright (c) 2015-2016 Microchp Technology Inc.
 *	Tristram Ha <Tristram.Ha@microchip.com>
 *
 * Copyright (c) 2012-2013 Micrel, Inc.
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

#ifndef __KSZ8463_H
#define __KSZ8463_H


/* Default values are used in ksz_sw.h if these are not defined. */
#define PRIO_QUEUES			4

#define KS_PRIO_IN_REG			8

#define TOTAL_PORT_NUM			3

#define KSZ8463_COUNTER_NUM		0x20
#define TOTAL_KSZ8463_COUNTER_NUM	(KSZ8463_COUNTER_NUM + 2)

#define SWITCH_COUNTER_NUM		KSZ8463_COUNTER_NUM
#define TOTAL_SWITCH_COUNTER_NUM	TOTAL_KSZ8463_COUNTER_NUM

/* Required for common switch control in ksz_sw.c */
#define SW_D				u16
#define SW_R(sw, addr)			(sw)->reg->r16(sw, addr)
#define SW_W(sw, addr, val)		(sw)->reg->w16(sw, addr, val)
#define SW_SIZE				(2)
#define SW_SIZE_STR			"%04x"
#define port_r				port_r16
#define port_w				port_w16

#define P_BCAST_STORM_CTRL		REG_PORT_CTRL1
#define P_PRIO_CTRL			REG_PORT_CTRL1
#define P_TAG_CTRL			REG_PORT_CTRL1
#define P_MIRROR_CTRL			REG_PORT_CTRL2
#define P_STP_CTRL			REG_PORT_CTRL2
#define P_PHY_CTRL			REG_PORT_CTRL4
#define P_FORCE_CTRL			REG_PORT_CTRL4
#define P_NEG_RESTART_CTRL		REG_PORT_CTRL4
#define P_LINK_STATUS			REG_PORT_STATUS
#define P_SPEED_STATUS			REG_PORT_STATUS
#define P_RATE_LIMIT_CTRL		REG_PORT_CTRL3
#define P_SA_MAC_CTRL			REG_PORT_CTRL1
#define P_2_QUEUE_CTRL			REG_PORT_CTRL1
#define P_4_QUEUE_CTRL			REG_PORT_CTRL1

#define S_LINK_AGING_CTRL		REG_SWITCH_CTRL_1
#define S_MIRROR_CTRL			REG_SWITCH_CTRL_2
#define S_REPLACE_VID_CTRL		REG_SWITCH_CTRL_3
#define S_802_1P_PRIO_CTRL		REG_SWITCH_CTRL_6
#define S_UNKNOWN_DA_CTRL		REG_SWITCH_CTRL_7
#define S_TOS_PRIO_CTRL			REG_TOS_PRIORITY_CTRL_1
#define S_FLUSH_TABLE_CTRL		REG_SWITCH_CTRL_8
#define S_TAIL_TAG_CTRL			REG_SWITCH_CTRL_8
#define S_FORWARD_INVALID_VID_CTRL	REG_SWITCH_CTRL_9
#define S_INS_SRC_PVID_CTRL		REG_SWITCH_CTRL_9

#define IND_ACC_TABLE(table)		((table))

#define REG_IND_CTRL_0			REG_IND_IACR
#define REG_IND_DATA_CHECK		REG_IND_DATA_1
#define REG_IND_DATA_HI			REG_IND_DATA_2
#define REG_IND_DATA_LO			REG_IND_DATA_4

#define REG_SWITCH_RESET		REG_RESET_CTRL

#define PORT_DROP_TAG			PORT_DROP_TAG_PKT

#define REG_PORT_0_MAC_ADDR_0		REG_SA_FILTER_MAC1_H
#define REG_PORT_1_MAC_ADDR_0		REG_SA_FILTER_MAC2_H

#define REG_PORT_IN_RATE_0		REG_PORT_IN_RATE0
#define REG_PORT_OUT_RATE_0		REG_PORT_OUT_RATE0
#define REG_PORT_1_IN_RATE_0		REG_PORT_IN_RATE0
#define REG_PORT_1_OUT_RATE_0		REG_PORT_OUT_RATE0

#define SWITCH_FLUSH_DYN_MAC_TABLE	SWITCH_FLUSH_DYNA_MAC
#define SWITCH_INS_TAG_1_PORT_2		SWITCH_INS_TAG_0_1
#define SWITCH_INS_TAG_1_PORT_3		SWITCH_INS_TAG_0_2
#define SWITCH_INS_TAG_2_PORT_1		SWITCH_INS_TAG_1_0
#define SWITCH_INS_TAG_2_PORT_3		SWITCH_INS_TAG_1_2
#define SWITCH_INS_TAG_3_PORT_1		SWITCH_INS_TAG_2_0
#define SWITCH_INS_TAG_3_PORT_2		SWITCH_INS_TAG_2_1

#define FORWARD_INVALID_PORT_SHIFT	8


#endif
