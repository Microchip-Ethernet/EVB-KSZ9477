/**
 * Microchip KSZ8695P/KS8695X Ethernet driver
 *
 * Copyright (c) 2015-2016 Microchip Technology Inc.
 *	Tristram Ha <Tristram.Ha@microchip.com>
 *
 * Copyright (c) 2009-2012 Micrel, Inc.
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

#if 0
#define DEBUG
#endif

#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/version.h>
#include <linux/ioport.h>
#include <linux/pci.h>
#include <linux/proc_fs.h>
#include <linux/mii.h>
#include <linux/platform_device.h>
#include <linux/ethtool.h>
#include <linux/etherdevice.h>
#include <linux/in.h>
#include <linux/ip.h>
#include <linux/if_vlan.h>
#include <linux/crc32.h>
#include <net/ip.h>
#include <net/ipv6.h>
#include <net/tcp.h>

/* Needed for STP support. */
#ifdef CONFIG_KSZ8695_STP
#include <../net/bridge/br_private.h>
#else
#define br_port_exists(dev)	(dev->priv_flags & IFF_BRIDGE_PORT)
#endif


/* DMA Registers */

#define KS_DMA_TX_CTRL			0x0000
#define DMA_TX_ENABLE			0x00000001
#define DMA_TX_CRC_ENABLE		0x00000002
#define DMA_TX_PAD_ENABLE		0x00000004
#define DMA_TX_LOOPBACK			0x00000100
#define DMA_TX_FLOW_ENABLE		0x00000200
#define DMA_TX_CSUM_IP			0x00010000
#define DMA_TX_CSUM_TCP			0x00020000
#define DMA_TX_CSUM_UDP			0x00040000
#define DMA_TX_BURST_SIZE		0x3F000000
#define DMA_TX_RESET			0x80000000

#define KS_DMA_RX_CTRL			0x0004
#define DMA_RX_ENABLE			0x00000001
#define DMA_RX_PROMISCUOUS		0x00000004
#define DMA_RX_ERROR			0x00000008
#define DMA_RX_UNICAST			0x00000010
#define DMA_RX_ALL_MULTICAST		0x00000020
#define DMA_RX_BROADCAST		0x00000040
#define DMA_RX_FLOW_ENABLE		0x00000200
#define DMA_RX_CSUM_IP			0x00010000
#define DMA_RX_CSUM_TCP			0x00020000
#define DMA_RX_CSUM_UDP			0x00040000
#define DMA_RX_IP_ALIGN			0x00080000
#define DMA_RX_HIGH_WATERMARK		0x00100000
#define DMA_RX_BURST_SIZE		0x3F000000

#define DMA_BURST_SHIFT			24
#define DMA_BURST_DEFAULT		8

#define KS_DMA_TX_START			0x0008
#define KS_DMA_RX_START			0x000C
#define DMA_START			0x00000001

#define KS_DMA_TX_ADDR			0x0010
#define KS_DMA_RX_ADDR			0x0014

#define DMA_ADDR_LIST_MASK		0xFFFFFFFC
#define DMA_ADDR_LIST_SHIFT		2

#define KS_DMA_MAC_ADDR_LO		0x0018
#define KS_DMA_MAC_ADDR_HI		0x001C

#define KS_INT_RX_MASK			\
	(KS_INT_RX | KS_INT_RX_OVERRUN)
#define KS_INT_TX_MASK			\
	(KS_INT_TX | KS_INT_TX_EMPTY)
#define KS_INT_MASK			(KS_INT_RX | KS_INT_TX)

/* MAC Additional Station Address */

/* MAAL0 */
#define KS_ADD_ADDR_0_LO		0x0080
/* MAAH0 */
#define KS_ADD_ADDR_0_HI		0x0084
/* MAAL1 */
#define KS_ADD_ADDR_1_LO		0x0088
/* MAAH1 */
#define KS_ADD_ADDR_1_HI		0x008C
/* MAAL2 */
#define KS_ADD_ADDR_2_LO		0x0090
/* MAAH2 */
#define KS_ADD_ADDR_2_HI		0x0094
/* MAAL3 */
#define KS_ADD_ADDR_3_LO		0x0098
/* MAAH3 */
#define KS_ADD_ADDR_3_HI		0x009C
/* MAAL4 */
#define KS_ADD_ADDR_4_LO		0x00A0
/* MAAH4 */
#define KS_ADD_ADDR_4_HI		0x00A4
/* MAAL5 */
#define KS_ADD_ADDR_5_LO		0x00A8
/* MAAH5 */
#define KS_ADD_ADDR_5_HI		0x00AC
/* MAAL6 */
#define KS_ADD_ADDR_6_LO		0x00B0
/* MAAH6 */
#define KS_ADD_ADDR_6_HI		0x00B4
/* MAAL7 */
#define KS_ADD_ADDR_7_LO		0x00B8
/* MAAH7 */
#define KS_ADD_ADDR_7_HI		0x00BC
/* MAAL8 */
#define KS_ADD_ADDR_8_LO		0x00C0
/* MAAH8 */
#define KS_ADD_ADDR_8_HI		0x00C4
/* MAAL9 */
#define KS_ADD_ADDR_9_LO		0x00C8
/* MAAH9 */
#define KS_ADD_ADDR_9_HI		0x00CC
/* MAAL10 */
#define KS_ADD_ADDR_A_LO		0x00D0
/* MAAH10 */
#define KS_ADD_ADDR_A_HI		0x00D4
/* MAAL11 */
#define KS_ADD_ADDR_B_LO		0x00D8
/* MAAH11 */
#define KS_ADD_ADDR_B_HI		0x00DC
/* MAAL12 */
#define KS_ADD_ADDR_C_LO		0x00E0
/* MAAH12 */
#define KS_ADD_ADDR_C_HI		0x00E4
/* MAAL13 */
#define KS_ADD_ADDR_D_LO		0x00E8
/* MAAH13 */
#define KS_ADD_ADDR_D_HI		0x00EC
/* MAAL14 */
#define KS_ADD_ADDR_E_LO		0x00F0
/* MAAH14 */
#define KS_ADD_ADDR_E_HI		0x00F4
/* MAAL15 */
#define KS_ADD_ADDR_F_LO		0x00F8
/* MAAH15 */
#define KS_ADD_ADDR_F_HI		0x00FC

#define ADD_ADDR_HI_MASK		0x0000FFFF
#define ADD_ADDR_ENABLE			0x80000000
#define ADD_ADDR_INCR			8

/* Interrupt Registers */

#define KS_INT_RX_STOPPED		0x00000001
#define KS_INT_TX_STOPPED		0x00000002
#define KS_INT_RX_OVERRUN		0x00000004
#define KS_INT_TX_EMPTY			0x00000008
#define KS_INT_RX			0x00000010
#define KS_INT_TX			0x00000020
#define KS_INT_PHY			0x00000040

#define KS_INT_CHECK			\
	(KS_INT_RX | KS_INT_TX |	\
	KS_INT_RX_OVERRUN |		\
	KS_INT_TX_EMPTY |		\
	KS_INT_RX_STOPPED |		\
	KS_INT_TX_STOPPED |		\
	KS_INT_PHY)

/* Miscellaneous Registers */

/* -------------------------------------------------------------------------- */

/* Mode Control Register */
#define PHY_REG_CTRL			0

#define PHY_RESET			0x8000
#define PHY_LOOPBACK			0x4000
#define PHY_SPEED_100MBIT		0x2000
#define PHY_AUTO_NEG_ENABLE		0x1000
#define PHY_POWER_DOWN			0x0800
#define PHY_MII_DISABLE			0x0400
#define PHY_AUTO_NEG_RESTART		0x0200
#define PHY_FULL_DUPLEX			0x0100
#define PHY_COLLISION_TEST		0x0080
#define PHY_HP_MDIX			0x0020
#define PHY_FORCE_MDIX			0x0010
#define PHY_AUTO_MDIX_DISABLE		0x0008
#define PHY_REMOTE_FAULT_DISABLE	0x0004
#define PHY_TRANSMIT_DISABLE		0x0002
#define PHY_LED_DISABLE			0x0001

/* Mode Status Register */
#define PHY_REG_STATUS			1

#define PHY_100BT4_CAPABLE		0x8000
#define PHY_100BTX_FD_CAPABLE		0x4000
#define PHY_100BTX_CAPABLE		0x2000
#define PHY_10BT_FD_CAPABLE		0x1000
#define PHY_10BT_CAPABLE		0x0800
#define PHY_MII_SUPPRESS_CAPABLE	0x0040
#define PHY_AUTO_NEG_ACKNOWLEDGE	0x0020
#define PHY_REMOTE_FAULT		0x0010
#define PHY_AUTO_NEG_CAPABLE		0x0008
#define PHY_LINK_STATUS			0x0004
#define PHY_JABBER_DETECT		0x0002
#define PHY_EXTENDED_CAPABILITY		0x0001

/* PHY Identifier Registers */
#define PHY_REG_ID_1			2
#define PHY_REG_ID_2			3

/* Auto-Negotiation Advertisement Register */
#define PHY_REG_AUTO_NEGOTIATION	4

#define PHY_AUTO_NEG_NEXT_PAGE		0x8000
#define PHY_ACKNOWLEDGE			0x4000
#define PHY_AUTO_NEG_REMOTE_FAULT	0x2000
/* Not supported. */
#define PHY_AUTO_NEG_ASYM_PAUSE		0x0800
#define PHY_AUTO_NEG_SYM_PAUSE		0x0400
#define PHY_AUTO_NEG_100BT4		0x0200
#define PHY_AUTO_NEG_100BTX_FD		0x0100
#define PHY_AUTO_NEG_100BTX		0x0080
#define PHY_AUTO_NEG_10BT_FD		0x0040
#define PHY_AUTO_NEG_10BT		0x0020
#define PHY_AUTO_NEG_SELECTOR		0x001F
#define PHY_AUTO_NEG_802_3		0x0001

#define PHY_LINK_SUPPORT		\
	(PHY_AUTO_NEG_SYM_PAUSE |	\
	PHY_AUTO_NEG_100BT4 |		\
	PHY_AUTO_NEG_100BTX_FD |	\
	PHY_AUTO_NEG_100BTX |		\
	PHY_AUTO_NEG_10BT_FD |		\
	PHY_AUTO_NEG_10BT)

#define PHY_AUTO_NEG_PAUSE		\
	(PHY_AUTO_NEG_SYM_PAUSE | PHY_AUTO_NEG_ASYM_PAUSE)

/* Auto-Negotiation Link Partner Ability Register */
#define PHY_REG_REMOTE_CAPABILITY	5

#define PHY_REMOTE_NEXT_PAGE		0x8000
#define PHY_REMOTE_ACKNOWLEDGE		0x4000
#define PHY_REMOTE_REMOTE_FAULT		0x2000
#define PHY_REMOTE_SYM_PAUSE		0x0400
#define PHY_REMOTE_100BTX_FD		0x0100
#define PHY_REMOTE_100BTX		0x0080
#define PHY_REMOTE_10BT_FD		0x0040
#define PHY_REMOTE_10BT			0x0020

/* Switch Engine registers */
/* SEC0 */
#define KS_SWITCH_CTRL_0_OFFSET		0xE800

#define SWITCH_NEW_BACKOFF		0x80000000
#define SWITCH_802_1P_MASK		0x70000000
#define SWITCH_802_1P_BASE		7
#define SWITCH_802_1P_SHIFT		28

#define LED_LAN_LED1_MODE_SHIFT		25
#define LED_LAN_LED0_MODE_SHIFT		22
#define LED_MODE_MASK			7
#define LED_SPEED			0
#define LED_LINK			1
#define LED_DUPLEX			2
#define LED_COLLISION			3
#define LED_ACTIVITIES			4
#define LED_DUPLEX_COLLISION		5
#define LED_LINK_ACTIVITIES		6

#define SWITCH_UNH_MODE			0x00200000
#define SWITCH_LINK_AUTO_AGING		0x00100000
#define SWITCH_PASS_ALL			0x00080000
#define SWITCH_FLOW_CTRL		0x00040000
#ifdef CONFIG_KS8695P
#define P_SWITCH_CHECK_LENGTH		0x00020000
#endif
#ifdef CONFIG_KS8695X
#define X_SWITCH_PORT_FLOW_CTRL		0x00020000
#endif
#define SWITCH_BUFFER_SHARE		0x00010000
#define SWITCH_AGING_ENABLE		0x00008000
#define SWITCH_FAST_AGING		0x00004000
#define SWITCH_AGGR_BACKOFF		0x00002000
#define UNICAST_VLAN_BOUNDARY		0x00001000
#define MULTICAST_STORM_DISABLE		0x00000800
#define SWITCH_BACK_PRESSURE_MODE	0x00000400
#define FAIR_FLOW_CTRL			0x00000200
#define NO_EXC_COLLISION_DROP		0x00000100
#define SWITCH_LEGAL_PACKET		0x00000080
#define SWITCH_BUF_RESERVE		0x00000040
#define SWITCH_BACK_PRESSURE		0x00000020
#ifdef CONFIG_KS8695P
#define P_SWITCH_HALF_DUPLEX		0x00000010
#endif
#define PRIORITY_SCHEME_SELECT		0x0000000C
#define PRIORITY_RATIO_HIGH		0x00000000
#define PRIORITY_RATIO_10		0x00000004
#define PRIORITY_RATIO_5		0x00000008
#define PRIORITY_RATIO_2		0x0000000C
#define TAG_MASK_ENABLE			0x00000002
#define SWITCH_ENABLE			0x00000001

/* SEC1 */
#define KS_SWITCH_CTRL_1_OFFSET		0xE804

#ifdef CONFIG_KS8695P
#define P_BROADCAST_STORM_RATE_MASK	0xFFE00000
#define P_BROADCAST_STORM_RATE_BASE	0x07FF
#define P_BROADCAST_STORM_RATE_SHIFT	21

#define P_SWITCH_IEEE_AUTO_NEG		0x00000800
#define P_SWITCH_TPID_MODE		0x00000400
#define P_SWITCH_PHY_MII_ENABLE		0x00000100
#define P_SWITCH_TX_FLOW_DISABLE	0x00000080
#define P_SWITCH_RX_FLOW_DISABLE	0x00000040
#define P_SWITCH_HUGE_PACKET		0x00000020
#define P_SWITCH_VLAN_ENABLE		0x00000010
#define P_SWITCH_TX_PORT_SPECIFY	0x00000008
#define P_SWITCH_RX_PORT_INDICATE	0x00000004
#define P_SWITCH_10_MBIT		0x00000002
#define P_SWITCH_REPLACE_NULL_VID	0x00000001

#define P_SWITCH_SEC1_RESERVED		0x001FF20C
#endif

#ifdef CONFIG_KS8695X
#define X_BROADCAST_STORM_RATE_MASK	0xFF000000
#define X_BROADCAST_STORM_RATE_BASE	0x00FF
#define X_BROADCAST_STORM_RATE_SHIFT	24

#define X_SWITCH_SEC1_RESERVED		0x00FFFFFF
#endif

#ifdef CONFIG_KS8695P
/* SEP1C1 */
#define KS_P_PORT_1_CTRL_1_OFFSET	0xE80C
/* SEP2C1 */
#define KS_P_PORT_2_CTRL_1_OFFSET	0xE818
/* SEP3C1 */
#define KS_P_PORT_3_CTRL_1_OFFSET	0xE824
/* SEP4C1 */
#define KS_P_PORT_4_CTRL_1_OFFSET	0xE830
/* SEP5C1 */
#define KS_P_PORT_5_CTRL_1_OFFSET	0xE83C
#endif

#ifdef CONFIG_KS8695X
/* SEP1C */
#define KS_X_PORT_1_CTRL_1_OFFSET	0xE808
/* SEP2C */
#define KS_X_PORT_2_CTRL_1_OFFSET	0xE80C
/* SEP3C */
#define KS_X_PORT_3_CTRL_1_OFFSET	0xE810
/* SEP4C */
#define KS_X_PORT_4_CTRL_1_OFFSET	0xE814
/* SEP5C */
#define KS_X_PORT_5_CTRL_1_OFFSET	0xE818
#endif

#define PORT_DEFAULT_VID		0xFFFF0000
#define PORT_DEFAULT_VID_SHIFT		16

#define PORT_AUTO_NEG_DISABLE		0x00008000
#define PORT_FORCE_100_MBIT		0x00004000
#define PORT_FORCE_FULL_DUPLEX		0x00002000

#ifdef CONFIG_KS8695X
#define X_SWITCH_TX_PORT_SPECIFY	0x00004000
#define X_SWITCH_RX_PORT_INDICATE	0x00002000
#endif

#define PORT_VLAN_MEMBERSHIP		0x00001F00
#define PORT_VLAN_MEMBERSHIP_SHIFT	8

#define PORT_TX_ENABLE			0x00000080
#define PORT_RX_ENABLE			0x00000040
#define PORT_LEARN_DISABLE		0x00000020
#define PORT_BROADCAST_STORM		0x00000010
#define PORT_BASED_PRIORITY_ENABLE	0x00000008
#define PORT_DIFFSERV_ENABLE		0x00000004
#define PORT_802_1P_ENABLE		0x00000002
#define PORT_PRIO_QUEUE_ENABLE		0x00000001

#define PORT_CTRL_ADDR(port, addr)			\
	(addr = KS_PORT_1_CTRL_1_OFFSET + (port) *	\
		(KS_PORT_2_CTRL_1_OFFSET - KS_PORT_1_CTRL_1_OFFSET))

#define KS_PORT_CTRL_1_OFFSET		0x00

#ifdef CONFIG_KS8695P
/* SEP1C2 */
#define KS_P_PORT_1_CTRL_2_OFFSET	0xE810
/* SEP2C2 */
#define KS_P_PORT_2_CTRL_2_OFFSET	0xE81C
/* SEP3C2 */
#define KS_P_PORT_3_CTRL_2_OFFSET	0xE828
/* SEP4C2 */
#define KS_P_PORT_4_CTRL_2_OFFSET	0xE834
/* SEP5C2 */
#define KS_P_PORT_5_CTRL_2_OFFSET	0xE840

#define PORT_INGRESS_VLAN_FILTER	0x10000000
#define PORT_DISCARD_NON_VID		0x08000000
#define PORT_FORCE_FLOW_CTRL		0x04000000
#define PORT_BACK_PRESSURE		0x02000000

#define PORT_TX_HI_RATE_SHIFT		12
#define PORT_TX_LO_RATE_SHIFT		0

#define PORT_PRIORITY_RATE		0xFFF
#define PORT_RATE_UNIT			32
#define PORT_RATE_SHIFT			12

#define KS_PORT_CTRL_2_OFFSET		0x04

/* SEP1C3 */
#define KS_P_PORT_1_CTRL_3_OFFSET	0xE814
/* SEP2C3 */
#define KS_P_PORT_2_CTRL_3_OFFSET	0xE820
/* SEP3C3 */
#define KS_P_PORT_3_CTRL_3_OFFSET	0xE82C
/* SEP4C3 */
#define KS_P_PORT_4_CTRL_3_OFFSET	0xE838
/* SEP5C3 */
#define KS_P_PORT_5_CTRL_3_OFFSET	0xE844

#define PORT_RX_HI_RATE_SHIFT		20
#define PORT_RX_LO_RATE_SHIFT		8
#define PORT_RX_RATE_DIFFERENTIAL	0x00000080
#define PORT_RX_LO_RATE_ENABLE		0x00000040
#define PORT_RX_HI_RATE_ENABLE		0x00000020
#define PORT_RX_LO_FLOW_CTRL		0x00000010
#define PORT_RX_HI_FLOW_CTRL		0x00000008
#define PORT_TX_RATE_DIFFERENTIAL	0x00000004
#define PORT_TX_LO_RATE_ENABLE		0x00000002
#define PORT_TX_HI_RATE_ENABLE		0x00000001

#define KS_PORT_CTRL_3_OFFSET		0x08

#define KS_P_PORT_2_AUTO_NEG_OFFSET	0xE848
#define KS_P_PORT_1_AUTO_NEG_OFFSET	0xE84A
#define KS_P_PORT_4_AUTO_NEG_OFFSET	0xE84C
#define KS_P_PORT_3_AUTO_NEG_OFFSET	0xE84E
#endif

#ifdef CONFIG_KS8695X
#define KS_X_PORT_2_AUTO_NEG_OFFSET	0xE81C
#define KS_X_PORT_1_AUTO_NEG_OFFSET	0xE81E
#define KS_X_PORT_4_AUTO_NEG_OFFSET	0xE820
#define KS_X_PORT_3_AUTO_NEG_OFFSET	0xE822
#endif

#define KS_PORT_0_AUTO_NEG_OFFSET	0xEA0E

#ifdef CONFIG_KS8695X
#define X_PORT_PHY_POWER_DOWN		0x8000
#endif
#define PORT_AUTO_NEG_COMPLETE		0x4000
#define PORT_AUTO_NEG_RESTART		0x2000
#define PORT_AUTO_NEG_SYM_PAUSE		0x1000
#define PORT_AUTO_NEG_100BTX_FD		0x0800
#define PORT_AUTO_NEG_100BTX		0x0400
#define PORT_AUTO_NEG_10BT_FD		0x0200
#define PORT_AUTO_NEG_10BT		0x0100
#define PORT_STATUS_LINK_GOOD		0x0080
#define PORT_STATUS_FULL_DUPLEX		0x0040
#define PORT_STATUS_SPEED_100MBIT	0x0020
#define PORT_REMOTE_SYM_PAUSE		0x0010
#define PORT_REMOTE_100BTX_FD		0x0008
#define PORT_REMOTE_100BTX		0x0004
#define PORT_REMOTE_10BT_FD		0x0002
#define PORT_REMOTE_10BT		0x0001

#ifdef CONFIG_KS8695P
/* SEIADL */
#define KS_P_SWITCH_ADVANCED_CTRL	0xE860
#endif

#ifdef CONFIG_KS8695X
/* SEAFC */
#define KS_X_SWITCH_ADVANCED_CTRL	0xE830
#endif

#define PORT_REMOVE_TAG_SHIFT		22
#define PORT_INSERT_TAG_SHIFT		17

#define SWITCH_MIRROR_RX_TX		0x00010000

#define PORT_MIRROR_SNIFFER_SHIFT	11
#define PORT_MIRROR_TX_SHIFT		6
#define PORT_MIRROR_RX_SHIFT		1

#define SWITCH_IGMP_SNOOP		0x00000001

#define ADVANCED_CTRL_RESERVED		0xF8000000

#ifdef CONFIG_KS8695P
/* SEDSCPH */
#define KS_P_TOS_PRIORITY_HI_OFFSET	0xE864
/* SEDSCPL */
#define KS_P_TOS_PRIORITY_LO_OFFSET	0xE868

/* SEMAH */
#define KS_P_SWITCH_MAC_ADDR_HI		0xE86C
/* SEMAL */
#define KS_P_SWITCH_MAC_ADDR_LO		0xE870
#endif

#ifdef CONFIG_KS8695X
/* SEDSCPH */
#define KS_X_TOS_PRIORITY_HI_OFFSET	0xE834
/* SEDSCPL */
#define KS_X_TOS_PRIORITY_LO_OFFSET	0xE838

/* SEMAH */
#define KS_X_SWITCH_MAC_ADDR_HI		0xE83C
/* SEMAL */
#define KS_X_SWITCH_MAC_ADDR_LO		0xE840

/* SEMCIA */
#define KS_X_SWITCH_MIB_ADDR		0xE844
/* SEMCD */
#define KS_X_SWITCH_MIB_DATA		0xE848
#endif

#ifdef CONFIG_KS8695P
#define KS_P_PORT_2_PHY_CTRL_OFFSET	0xE874
#define KS_P_PORT_1_PHY_CTRL_OFFSET	0xE876
#define KS_P_PORT_4_PHY_CTRL_OFFSET	0xE878
#define KS_P_PORT_3_PHY_CTRL_OFFSET	0xE87A
#endif

#ifdef CONFIG_KS8695X
#define KS_X_PORT_2_PHY_CTRL_OFFSET	0xE84C
#define KS_X_PORT_1_PHY_CTRL_OFFSET	0xE84E
#define KS_X_PORT_4_PHY_CTRL_OFFSET	0xE850
#define KS_X_PORT_3_PHY_CTRL_OFFSET	0xE854
#endif

#define KS_PORT_0_PHY_CTRL_OFFSET	0xEA10

#ifdef CONFIG_KS8695P
#define P_PORT_PHY_LOOPBACK		0x4000
#define P_PORT_REMOTE_LOOPBACK		0x2000
#define P_PORT_PHY_ISOLATE		0x1000
#define P_PORT_PHY_RESET		0x0800
#define P_PORT_FORCE_LINK		0x0400
#endif
#define PORT_MDIX_STATUS		0x0200
#define PORT_REMOTE_FAULT		0x0100
#ifdef CONFIG_KS8695X
#define X_PORT_IEEE_AUTO_MDIX		0x0080
#endif
#define PORT_TX_DISABLE			0x0040
#define PORT_REMOTE_FAULT_DISABLE	0x0020
#define PORT_POWER_DOWN			0x0010
#define PORT_AUTO_MDIX_DISABLE		0x0008
#define PORT_FORCE_MDIX			0x0004
#define PORT_MAC_LOOPBACK		0x0002

#ifdef CONFIG_KS8695P
#define P_PORT_PHY_CTRL_RESERVED	0x8081
#endif

#ifdef CONFIG_KS8695X
#define X_PORT_PHY_CTRL_RESERVED	0xFC01
#endif

#define KS_WAN_CONTROL			0xEA0C

#define LED_WAN_LED1_MODE_SHIFT		4
#define LED_WAN_LED0_MODE_SHIFT		0

#ifdef CONFIG_KS8695P
#define KS_P_IACR_OFFSET		0xE850

#define KS_P_ACC_DATA_0_OFFSET		0xE85C
#define KS_P_ACC_DATA_1_OFFSET		(KS_P_ACC_DATA_0_OFFSET + 1)
#define KS_P_ACC_DATA_2_OFFSET		(KS_P_ACC_DATA_0_OFFSET + 2)
#define KS_P_ACC_DATA_3_OFFSET		(KS_P_ACC_DATA_0_OFFSET + 3)
#define KS_P_ACC_DATA_4_OFFSET		0xE858
#define KS_P_ACC_DATA_5_OFFSET		(KS_P_ACC_DATA_4_OFFSET + 1)
#define KS_P_ACC_DATA_6_OFFSET		(KS_P_ACC_DATA_4_OFFSET + 2)
#define KS_P_ACC_DATA_7_OFFSET		(KS_P_ACC_DATA_4_OFFSET + 3)
#define KS_P_ACC_DATA_8_OFFSET		0xE854
#endif

#ifdef CONFIG_KS8695X
#define KS_X_IACR_OFFSET		0xE824

#define X_LUE_BUSY			0x00001000

#define KS_X_ACC_DATA_0_OFFSET		0xE82C
#define KS_X_ACC_DATA_1_OFFSET		(KS_X_ACC_DATA_0_OFFSET + 1)
#define KS_X_ACC_DATA_2_OFFSET		(KS_X_ACC_DATA_0_OFFSET + 2)
#define KS_X_ACC_DATA_3_OFFSET		(KS_X_ACC_DATA_0_OFFSET + 3)
#define KS_X_ACC_DATA_4_OFFSET		0xE828
#define KS_X_ACC_DATA_5_OFFSET		(KS_X_ACC_DATA_4_OFFSET + 1)
#define KS_X_ACC_DATA_6_OFFSET		(KS_X_ACC_DATA_4_OFFSET + 2)
#define KS_X_ACC_DATA_7_OFFSET		(KS_X_ACC_DATA_4_OFFSET + 3)
#endif

/* -------------------------------------------------------------------------- */

/*
#define STATIC_MAC_TABLE_ADDR		00-0000FFFF-FFFFFFFF
#define STATIC_MAC_TABLE_FWD_PORTS	00-001F0000-00000000
#define STATIC_MAC_TABLE_VALID		00-00200000-00000000
#define STATIC_MAC_TABLE_OVERRIDE	00-00400000-00000000
#define STATIC_MAC_TABLE_USE_FID	00-01000000-00000000
#define STATIC_MAC_TABLE_FID		00-1E000000-00000000
*/

#define STATIC_MAC_TABLE_ADDR		0x0000FFFF
#define STATIC_MAC_TABLE_FWD_PORTS	0x001F0000
#define STATIC_MAC_TABLE_VALID		0x00200000
#define STATIC_MAC_TABLE_OVERRIDE	0x00400000

#define STATIC_MAC_FWD_PORTS_SHIFT	16

#ifdef CONFIG_KS8695P
#define P_STATIC_MAC_TABLE_USE_FID	0x01000000
#define P_STATIC_MAC_TABLE_FID		0x1E000000

#define P_STATIC_MAC_FID_SHIFT		25
#define P_STATIC_MAC_WRITE_SHIFT	1
#endif

#ifdef CONFIG_KS8695P
/*
#define P_VLAN_TABLE_VID		00-00000000-00000FFF
#define P_VLAN_TABLE_FID		00-00000000-0000F000
#define P_VLAN_TABLE_MEMBERSHIP		00-00000000-001F0000
#define P_VLAN_TABLE_VALID		00-00000000-00200000
*/

#define P_VLAN_TABLE_VID		0x00000FFF
#define P_VLAN_TABLE_FID		0x0000F000
#define P_VLAN_TABLE_MEMBERSHIP		0x001F0000
#define P_VLAN_TABLE_VALID		0x00200000

#define P_VLAN_FID_SHIFT		12
#define P_VLAN_MEMBERSHIP_SHIFT		16

/*
#define P_DYN_MAC_TABLE_ADDR		00-0000FFFF-FFFFFFFF
#define P_DYN_MAC_TABLE_FID		00-000F0000-00000000
#define P_DYN_MAC_TABLE_SRC_PORT	00-00700000-00000000
#define P_DYN_MAC_TABLE_NOT_READY	00-00800000-00000000
#define P_DYN_MAC_TABLE_TIMESTAMP	00-03000000-00000000
#define P_DYN_MAC_TABLE_ENTRIES		0F-FC000000-00000000
#define P_DYN_MAC_TABLE_MAC_EMPTY	10-00000000-00000000
*/

#define P_DYN_MAC_TABLE_ADDR		0x0000FFFF
#define P_DYN_MAC_TABLE_FID		0x000F0000
#define P_DYN_MAC_TABLE_SRC_PORT	0x00700000
#define P_DYN_MAC_TABLE_NOT_READY	0x00800000
#define P_DYN_MAC_TABLE_TIMESTAMP	0x03000000
#define P_DYN_MAC_TABLE_ENTRIES		0xFC000000

#define P_DYN_MAC_TABLE_ENTRIES_H	0x0F
#define P_DYN_MAC_TABLE_MAC_EMPTY	0x10

#define P_DYN_MAC_FID_SHIFT		16
#define P_DYN_MAC_SRC_PORT_SHIFT	20
#define P_DYN_MAC_TIMESTAMP_SHIFT	24
#define P_DYN_MAC_ENTRIES_SHIFT		26
#define P_DYN_MAC_ENTRIES_H_SHIFT	6
#endif

#ifdef CONFIG_KS8695X
/*
#define X_DYN_MAC_TABLE_ADDR		0000FFFF-FFFFFFFF
#define X_DYN_MAC_TABLE_SRC_PORT	00070000-00000000
#define X_DYN_MAC_TABLE_TIMESTAMP	00180000-00000000
#define X_DYN_MAC_TABLE_ENTRIES		7FE00000-00000000
#define X_DYN_MAC_TABLE_MAC_EMPTY	80000000-00000000
*/

#define X_DYN_MAC_TABLE_ADDR		0x0000FFFF
#define X_DYN_MAC_TABLE_SRC_PORT	0x00070000
#define X_DYN_MAC_TABLE_TIMESTAMP	0x00180000
#define X_DYN_MAC_TABLE_ENTRIES		0x7FE00000
#define X_DYN_MAC_TABLE_MAC_EMPTY	0x80000000

#define X_DYN_MAC_SRC_PORT_SHIFT	16
#define X_DYN_MAC_TIMESTAMP_SHIFT	19
#define X_DYN_MAC_ENTRIES_SHIFT		21
#endif

/*
#define MIB_COUNTER_VALUE		00-00000000-3FFFFFFF
#define MIB_COUNTER_VALID		00-00000000-40000000
#define MIB_COUNTER_OVERFLOW		00-00000000-80000000
*/

#define MIB_COUNTER_VALUE		0x3FFFFFFF
#ifdef CONFIG_KS8695P
#define P_MIB_COUNTER_VALID		0x40000000
#define P_MIB_COUNTER_OVERFLOW		0x80000000
#endif
#ifdef CONFIG_KS8695X
#define X_MIB_COUNTER_VALID		0x80000000
#define X_MIB_COUNTER_OVERFLOW		0x40000000
#endif

#define MIB_PACKET_DROPPED		0x0000FFFF

#define KS_P_MIB_PACKET_DROPPED_TX_0	0x100
#define KS_P_MIB_PACKET_DROPPED_TX_1	0x101
#define KS_P_MIB_PACKET_DROPPED_TX_2	0x102
#define KS_P_MIB_PACKET_DROPPED_TX_3	0x103
#define KS_P_MIB_PACKET_DROPPED_TX	0x104
#define KS_P_MIB_PACKET_DROPPED_RX_0	0x105
#define KS_P_MIB_PACKET_DROPPED_RX_1	0x106
#define KS_P_MIB_PACKET_DROPPED_RX_2	0x107
#define KS_P_MIB_PACKET_DROPPED_RX_3	0x108
#define KS_P_MIB_PACKET_DROPPED_RX	0x109

#define KS_X_MIB_PACKET_DROPPED_TX_0	0x80
#define KS_X_MIB_PACKET_DROPPED_TX_1	0x81
#define KS_X_MIB_PACKET_DROPPED_TX_2	0x82
#define KS_X_MIB_PACKET_DROPPED_TX_3	0x83
#define KS_X_MIB_PACKET_DROPPED_TX	0x84
#define KS_X_MIB_PACKET_DROPPED_RX_0	0x85
#define KS_X_MIB_PACKET_DROPPED_RX_1	0x86
#define KS_X_MIB_PACKET_DROPPED_RX_2	0x87
#define KS_X_MIB_PACKET_DROPPED_RX_3	0x88
#define KS_X_MIB_PACKET_DROPPED_RX	0x89

#define KS_DEVICE_ID			0xEA00
#define KS_REVISION_ID			0xEA04

#define KS_PHY_POWER_SAVE		0xEA1C

#define PHY_POWER_SAVE_ENABLE		0x00000001


#ifdef CONFIG_KS8695P
#define KS_SWITCH_HOST_CTRL_OFFSET	KS_SWITCH_CTRL_1_OFFSET
#define SWITCH_TX_PORT_SPECIFY		P_SWITCH_TX_PORT_SPECIFY
#define SWITCH_RX_PORT_INDICATE		P_SWITCH_RX_PORT_INDICATE
#define BROADCAST_STORM_RATE_MASK	P_BROADCAST_STORM_RATE_MASK
#define BROADCAST_STORM_RATE_BASE	P_BROADCAST_STORM_RATE_BASE
#define BROADCAST_STORM_RATE_SHIFT	P_BROADCAST_STORM_RATE_SHIFT
#define KS_PORT_1_CTRL_1_OFFSET		KS_P_PORT_1_CTRL_1_OFFSET
#define KS_PORT_2_CTRL_1_OFFSET		KS_P_PORT_2_CTRL_1_OFFSET
#define KS_PORT_3_CTRL_1_OFFSET		KS_P_PORT_3_CTRL_1_OFFSET
#define KS_PORT_4_CTRL_1_OFFSET		KS_P_PORT_4_CTRL_1_OFFSET
#define KS_PORT_1_AUTO_NEG_OFFSET	KS_P_PORT_1_AUTO_NEG_OFFSET
#define KS_PORT_2_AUTO_NEG_OFFSET	KS_P_PORT_2_AUTO_NEG_OFFSET
#define KS_PORT_3_AUTO_NEG_OFFSET	KS_P_PORT_3_AUTO_NEG_OFFSET
#define KS_PORT_4_AUTO_NEG_OFFSET	KS_P_PORT_4_AUTO_NEG_OFFSET
#define KS_PORT_1_PHY_CTRL_OFFSET	KS_P_PORT_1_PHY_CTRL_OFFSET
#define KS_PORT_2_PHY_CTRL_OFFSET	KS_P_PORT_2_PHY_CTRL_OFFSET
#define KS_PORT_3_PHY_CTRL_OFFSET	KS_P_PORT_3_PHY_CTRL_OFFSET
#define KS_PORT_4_PHY_CTRL_OFFSET	KS_P_PORT_4_PHY_CTRL_OFFSET
#define KS_SWITCH_ADVANCED_CTRL		KS_P_SWITCH_ADVANCED_CTRL
#define KS_TOS_PRIORITY_HI_OFFSET	KS_P_TOS_PRIORITY_HI_OFFSET
#define KS_TOS_PRIORITY_LO_OFFSET	KS_P_TOS_PRIORITY_LO_OFFSET
#define KS_SWITCH_MAC_ADDR_HI		KS_P_SWITCH_MAC_ADDR_HI
#define KS_SWITCH_MAC_ADDR_LO		KS_P_SWITCH_MAC_ADDR_LO
#define KS_IACR_OFFSET			KS_P_IACR_OFFSET
#define KS_ACC_DATA_0_OFFSET		KS_P_ACC_DATA_0_OFFSET
#define KS_ACC_DATA_4_OFFSET		KS_P_ACC_DATA_4_OFFSET
#define KS_ACC_DATA_8_OFFSET		KS_P_ACC_DATA_8_OFFSET
#define DYN_MAC_TABLE_SRC_PORT		P_DYN_MAC_TABLE_SRC_PORT
#define DYN_MAC_TABLE_TIMESTAMP		P_DYN_MAC_TABLE_TIMESTAMP
#define DYN_MAC_SRC_PORT_SHIFT		P_DYN_MAC_SRC_PORT_SHIFT
#define DYN_MAC_TIMESTAMP_SHIFT		P_DYN_MAC_TIMESTAMP_SHIFT
#define KS_MIB_PACKET_DROPPED_TX_0	KS_P_MIB_PACKET_DROPPED_TX_0
#define KS_MIB_PACKET_DROPPED_TX	KS_P_MIB_PACKET_DROPPED_TX
#define KS_MIB_PACKET_DROPPED_RX_0	KS_P_MIB_PACKET_DROPPED_RX_0
#define MIB_COUNTER_VALID		P_MIB_COUNTER_VALID
#define MIB_COUNTER_OVERFLOW		P_MIB_COUNTER_OVERFLOW
#endif

#ifdef CONFIG_KS8695X
#define KS_SWITCH_HOST_CTRL_OFFSET	KS_X_PORT_5_CTRL_1_OFFSET
#define SWITCH_TX_PORT_SPECIFY		X_SWITCH_TX_PORT_SPECIFY
#define SWITCH_RX_PORT_INDICATE		X_SWITCH_RX_PORT_INDICATE
#define BROADCAST_STORM_RATE_MASK	X_BROADCAST_STORM_RATE_MASK
#define BROADCAST_STORM_RATE_BASE	X_BROADCAST_STORM_RATE_BASE
#define BROADCAST_STORM_RATE_SHIFT	X_BROADCAST_STORM_RATE_SHIFT
#define KS_PORT_1_CTRL_1_OFFSET		KS_X_PORT_1_CTRL_1_OFFSET
#define KS_PORT_2_CTRL_1_OFFSET		KS_X_PORT_2_CTRL_1_OFFSET
#define KS_PORT_3_CTRL_1_OFFSET		KS_X_PORT_3_CTRL_1_OFFSET
#define KS_PORT_4_CTRL_1_OFFSET		KS_X_PORT_4_CTRL_1_OFFSET
#define KS_PORT_1_AUTO_NEG_OFFSET	KS_X_PORT_1_AUTO_NEG_OFFSET
#define KS_PORT_2_AUTO_NEG_OFFSET	KS_X_PORT_2_AUTO_NEG_OFFSET
#define KS_PORT_3_AUTO_NEG_OFFSET	KS_X_PORT_3_AUTO_NEG_OFFSET
#define KS_PORT_4_AUTO_NEG_OFFSET	KS_X_PORT_4_AUTO_NEG_OFFSET
#define KS_PORT_1_PHY_CTRL_OFFSET	KS_X_PORT_1_PHY_CTRL_OFFSET
#define KS_PORT_2_PHY_CTRL_OFFSET	KS_X_PORT_2_PHY_CTRL_OFFSET
#define KS_PORT_3_PHY_CTRL_OFFSET	KS_X_PORT_3_PHY_CTRL_OFFSET
#define KS_PORT_4_PHY_CTRL_OFFSET	KS_X_PORT_4_PHY_CTRL_OFFSET
#define KS_SWITCH_ADVANCED_CTRL		KS_X_SWITCH_ADVANCED_CTRL
#define KS_TOS_PRIORITY_HI_OFFSET	KS_X_TOS_PRIORITY_HI_OFFSET
#define KS_TOS_PRIORITY_LO_OFFSET	KS_X_TOS_PRIORITY_LO_OFFSET
#define KS_SWITCH_MAC_ADDR_HI		KS_X_SWITCH_MAC_ADDR_HI
#define KS_SWITCH_MAC_ADDR_LO		KS_X_SWITCH_MAC_ADDR_LO
#define KS_IACR_OFFSET			KS_X_IACR_OFFSET
#define KS_ACC_DATA_0_OFFSET		KS_X_ACC_DATA_0_OFFSET
#define KS_ACC_DATA_4_OFFSET		KS_X_ACC_DATA_4_OFFSET
#define DYN_MAC_TABLE_SRC_PORT		X_DYN_MAC_TABLE_SRC_PORT
#define DYN_MAC_TABLE_TIMESTAMP		X_DYN_MAC_TABLE_TIMESTAMP
#define DYN_MAC_SRC_PORT_SHIFT		X_DYN_MAC_SRC_PORT_SHIFT
#define DYN_MAC_TIMESTAMP_SHIFT		X_DYN_MAC_TIMESTAMP_SHIFT
#define KS_MIB_PACKET_DROPPED_TX_0	KS_X_MIB_PACKET_DROPPED_TX_0
#define KS_MIB_PACKET_DROPPED_TX	KS_X_MIB_PACKET_DROPPED_TX
#define KS_MIB_PACKET_DROPPED_RX_0	KS_X_MIB_PACKET_DROPPED_RX_0
#define MIB_COUNTER_VALID		X_MIB_COUNTER_VALID
#define MIB_COUNTER_OVERFLOW		X_MIB_COUNTER_OVERFLOW
#endif

/* -------------------------------------------------------------------------- */

#define KS_IO_BASE			KS8695_IO_BASE
#ifndef KS_VIO_BASE
#define KS_VIO_BASE			IO_ADDRESS(KS_IO_BASE)
#endif

#define KS_WAN_DMA_TX			KS8695_WAN_DMA_TX
#define KS_LAN_DMA_TX			KS8695_LAN_DMA_TX
#define KS_INT_ENABLE			KS8695_INT_ENABLE
#define KS_INT_STATUS			KS8695_INT_STATUS

#ifndef KS_R
#define KS_R(x)				readl(KS_VIO_BASE + (x))
#define KS_W(x, d)			writel(d, KS_VIO_BASE + (x))
#endif

/* Make sure value is correct when read immediately. */
#define KS_WR(x, d)				\
	do {					\
		writel(d, KS_VIO_BASE + (x));	\
		readl(KS_VIO_BASE + (x));	\
	} while (0)

#define KS_R8(x)			readb(KS_VIO_BASE + (x))
#define KS_R16(x)			readw(KS_VIO_BASE + (x))


#ifdef DEBUG
#if 0
#define DEBUG_COUNTER
#endif
#if 0
#define DEBUG_INTERRUPT
#endif
#if 0
#define DEBUG_MSG
#if 0
#define DEBUG_VERIFY
#endif
#endif
#endif

#if 0
#define USE_MULTIPLE_RX_DESC
#endif

#if 0
#define VERIFY_NO_CSUM_FRAGMENT
#endif

#if 0
/* Verify multicast hash table filtering is working. */
#define VERIFY_MULTICAST
#endif

#if 0
#define TEST_RX_LOOPBACK
#endif

/* -------------------------------------------------------------------------- */

#define MAC_ADDR_LEN			6
#define MAC_ADDR_ORDER(i)		(MAC_ADDR_LEN - 1 - (i))

#define MAX_ETHERNET_BODY_SIZE		1500
#define ETHERNET_HEADER_SIZE		14

#define MAX_ETHERNET_PACKET_SIZE	\
	(MAX_ETHERNET_BODY_SIZE + ETHERNET_HEADER_SIZE)

#define REGULAR_RX_BUF_SIZE		(MAX_ETHERNET_PACKET_SIZE + 4)
#define MAX_RX_BUF_SIZE			(1912 + 4)

#define ADDITIONAL_ENTRIES		16
#define MAX_MULTICAST_LIST		ADDITIONAL_ENTRIES

#define BASE_IO_ADDR			KS_VIO_BASE
#define BASE_IO_RANGE			0x100

/* Most of the time the offset is just 2. */
#define MAX_ALIGN_OFFSET		3


/* Driver set switch broadcast storm protection at 10% rate. */
#define BROADCAST_STORM_PROTECTION_RATE	10

enum {
	media_connected,
	media_disconnected
};

enum {
	OID_COUNTER_UNKOWN,

	OID_COUNTER_FIRST,

	OID_COUNTER_XMIT_ERROR,

	OID_COUNTER_RCV_ERROR,
	OID_COUNTER_RCV_ERROR_CRC,
	OID_COUNTER_RCV_ERROR_PHY,
	OID_COUNTER_RCV_ERROR_TOOLONG,
	OID_COUNTER_RCV_ERROR_RUNT,
	OID_COUNTER_RCV_ERROR_IP,
	OID_COUNTER_RCV_ERROR_TCP,
	OID_COUNTER_RCV_ERROR_UDP,
	OID_COUNTER_RCV_NO_BUFFER,

	OID_COUNTER_LAST
};

enum {
	COUNT_BAD_FIRST,
	COUNT_BAD_ALLOC = COUNT_BAD_FIRST,
	COUNT_BAD_CMD,
	COUNT_BAD_CMD_BUSY,
	COUNT_BAD_CMD_INITIALIZE,
	COUNT_BAD_CMD_MEM_ALLOC,
	COUNT_BAD_CMD_RESET,
	COUNT_BAD_CMD_WRONG_CHIP,
	COUNT_BAD_COPY_DOWN,
	COUNT_BAD_RCV_FRAME,
	COUNT_BAD_RCV_PACKET,
	COUNT_BAD_SEND,
	COUNT_BAD_SEND_DIFF,
	COUNT_BAD_SEND_PACKET,
	COUNT_BAD_SEND_ZERO,
	COUNT_BAD_XFER_ZERO,
	COUNT_BAD_LAST
};

enum {
	COUNT_GOOD_FIRST,
	COUNT_GOOD_CMD_RESET = COUNT_GOOD_FIRST,
	COUNT_GOOD_CMD_RESET_MMU,
	COUNT_GOOD_COPY_DOWN_ODD,
	COUNT_GOOD_INT,
	COUNT_GOOD_INT_LOOP,
	COUNT_GOOD_INT_ALLOC,
	COUNT_GOOD_INT_RX,
	COUNT_GOOD_INT_RX_EARLY,
	COUNT_GOOD_INT_RX_OVERRUN,
	COUNT_GOOD_INT_TX,
	COUNT_GOOD_INT_TX_EMPTY,
	COUNT_GOOD_NEXT_PACKET,
	COUNT_GOOD_NO_NEXT_PACKET,
	COUNT_GOOD_RCV_COMPLETE,
	COUNT_GOOD_RCV_DISCARD,
	COUNT_GOOD_RCV_NOT_DISCARD,
	COUNT_GOOD_RCV_CNT_1,
	COUNT_GOOD_RCV_CNT_2,
	COUNT_GOOD_RCV_CNT_3,
	COUNT_GOOD_SEND_PACKET,
	COUNT_GOOD_SEND_QUEUE,
	COUNT_GOOD_SEND_ZERO,
	COUNT_GOOD_XFER_ZERO,
	COUNT_GOOD_LAST
};

/*
 * Hardware descriptor definitions
 */

#define DESC_ALIGNMENT			16
#define BUFFER_ALIGNMENT		8

#define NUM_OF_RX_DESC			64
#define NUM_OF_TX_DESC			64

#define KS_DESC_RX_FRAME_LEN		0x000007FF
#define KS_DESC_RX_FRAME_TYPE		0x00008000
#define KS_DESC_RX_ERROR_CRC		0x00010000
#define KS_DESC_RX_ERROR_RUNT		0x00020000
#define KS_DESC_RX_ERROR_TOO_LONG	0x00040000
#define KS_DESC_RX_ERROR_PHY		0x00080000
#define KS_DESC_RX_PORT_MASK		0x00F00000
#define KS_DESC_RX_MULTICAST		0x01000000
#define KS_DESC_RX_ERROR		0x02000000
#define KS_DESC_RX_ERROR_CSUM_UDP	0x04000000
#define KS_DESC_RX_ERROR_CSUM_TCP	0x08000000
#define KS_DESC_RX_ERROR_CSUM_IP	0x10000000
#define KS_DESC_RX_LAST			0x20000000
#define KS_DESC_RX_FIRST		0x40000000
#define KS_DESC_RX_ERROR_COND		\
	(KS_DESC_RX_ERROR_CRC |		\
	KS_DESC_RX_ERROR_RUNT |		\
	KS_DESC_RX_ERROR_PHY |		\
	KS_DESC_RX_ERROR_TOO_LONG)

#define KS_DESC_HW_OWNED		0x80000000

#define KS_DESC_BUF_SIZE		0x000007FF
#define KS_DESC_TX_PORT_MASK		0x00F00000
#define KS_DESC_END_OF_RING		0x02000000
#define KS_DESC_TX_CSUM_GEN_UDP		0x04000000
#define KS_DESC_TX_CSUM_GEN_TCP		0x08000000
#define KS_DESC_TX_CSUM_GEN_IP		0x10000000
#define KS_DESC_TX_LAST			0x20000000
#define KS_DESC_TX_FIRST		0x40000000
#define KS_DESC_TX_INTERRUPT		0x80000000

#define KS_DESC_PORT_SHIFT		20

#define KS_DESC_RX_MASK			(KS_DESC_BUF_SIZE)

#define KS_DESC_TX_MASK			\
	(KS_DESC_TX_INTERRUPT |		\
	KS_DESC_TX_FIRST |		\
	KS_DESC_TX_LAST |		\
	KS_DESC_TX_CSUM_GEN_IP |	\
	KS_DESC_TX_CSUM_GEN_TCP |	\
	KS_DESC_TX_CSUM_GEN_UDP |	\
	KS_DESC_BUF_SIZE)

struct ksz_desc_rx_stat {
#ifdef __BIG_ENDIAN_BITFIELD
	u32 hw_owned:1;
	u32 first_desc:1;
	u32 last_desc:1;
	u32 csum_err_ip:1;
	u32 csum_err_tcp:1;
	u32 csum_err_udp:1;
	u32 error:1;
	u32 multicast:1;
	u32 src_port:4;
	u32 err_phy:1;
	u32 err_too_long:1;
	u32 err_runt:1;
	u32 err_crc:1;
	u32 frame_type:1;
	u32 aligned:2;
	u32 reserved1:2;
	u32 frame_len:11;
#else
	u32 frame_len:11;
	u32 reserved1:2;
	u32 aligned:2;
	u32 frame_type:1;
	u32 err_crc:1;
	u32 err_runt:1;
	u32 err_too_long:1;
	u32 err_phy:1;
	u32 src_port:4;
	u32 multicast:1;
	u32 error:1;
	u32 csum_err_udp:1;
	u32 csum_err_tcp:1;
	u32 csum_err_ip:1;
	u32 last_desc:1;
	u32 first_desc:1;
	u32 hw_owned:1;
#endif
};

struct ksz_desc_tx_stat {
#ifdef __BIG_ENDIAN_BITFIELD
	u32 hw_owned:1;
	u32 reserved1:31;
#else
	u32 reserved1:31;
	u32 hw_owned:1;
#endif
};

struct ksz_desc_rx_buf {
#ifdef __BIG_ENDIAN_BITFIELD
	u32 reserved4:6;
	u32 end_of_ring:1;
	u32 reserved3:14;
	u32 buf_size:11;
#else
	u32 buf_size:11;
	u32 reserved3:14;
	u32 end_of_ring:1;
	u32 reserved4:6;
#endif
};

struct ksz_desc_tx_buf {
#ifdef __BIG_ENDIAN_BITFIELD
	u32 intr:1;
	u32 first_seg:1;
	u32 last_seg:1;
	u32 csum_gen_ip:1;
	u32 csum_gen_tcp:1;
	u32 csum_gen_udp:1;
	u32 end_of_ring:1;
	u32 reserved4:1;
	u32 dest_port:4;
	u32 reserved3:9;
	u32 buf_size:11;
#else
	u32 buf_size:11;
	u32 reserved3:9;
	u32 dest_port:4;
	u32 reserved4:1;
	u32 end_of_ring:1;
	u32 csum_gen_udp:1;
	u32 csum_gen_tcp:1;
	u32 csum_gen_ip:1;
	u32 last_seg:1;
	u32 first_seg:1;
	u32 intr:1;
#endif
};

union desc_stat {
	struct ksz_desc_rx_stat rx;
	struct ksz_desc_tx_stat tx;
	u32 data;
};

union desc_buf {
	struct ksz_desc_rx_buf rx;
	struct ksz_desc_tx_buf tx;
	u32 data;
};

/**
 * struct ksz_hw_desc - Hardware descriptor data structure
 * @ctrl:	Descriptor control value.
 * @buf:	Descriptor buffer value.
 * @addr:	Physical address of memory buffer.
 * @next:	Pointer to next hardware descriptor.
 */
struct ksz_hw_desc {
	union desc_stat ctrl;
	union desc_buf buf;
	u32 addr;
	u32 next;
};

/**
 * struct ksz_sw_desc - Software descriptor data structure
 * @ctrl:	Descriptor control value.
 * @buf:	Descriptor buffer value.
 * @buf_size:	Current buffers size value in hardware descriptor.
 */
struct ksz_sw_desc {
	union desc_stat ctrl;
	union desc_buf buf;
	u32 buf_size;
};

/**
 * struct ksz_dma_buf - OS dependent DMA buffer data structure
 * @skb:	Associated socket buffer.
 * @dma:	Associated physical DMA address.
 * len:		Actual len used.
 */
struct ksz_dma_buf {
	struct sk_buff *skb;
	dma_addr_t dma;
	int len;
};

/**
 * struct ksz_desc - Descriptor structure
 * @phw:	Hardware descriptor pointer to uncached physical memory.
 * @sw:		Cached memory to hold hardware descriptor values for
 *		manipulation.
 * @dma_buf:	Operating system dependent data structure to hold physical
 *		memory buffer allocation information.
 */
struct ksz_desc {
	struct ksz_hw_desc *phw;
	struct ksz_sw_desc sw;
	struct ksz_dma_buf dma_buf;
	struct ksz_hw_desc *check;
};

#define DMA_BUFFER(desc)  ((struct ksz_dma_buf *)(&(desc)->dma_buf))

/**
 * struct ksz_desc_info - Descriptor information data structure
 * @ring:	First descriptor in the ring.
 * @cur:	Current descriptor being manipulated.
 * @ring_virt:	First hardware descriptor in the ring.
 * @ring_phys:	The physical address of the first descriptor of the ring.
 * @size:	Size of hardware descriptor.
 * @alloc:	Number of descriptors allocated.
 * @avail:	Number of descriptors available for use.
 * @last:	Index for last descriptor released to hardware.
 * @next:	Index for next descriptor available for use.
 * @mask:	Mask for index wrapping.
 */
struct ksz_desc_info {
	struct ksz_desc *ring;
	struct ksz_desc *cur;
	struct ksz_hw_desc *ring_virt;
	u32 ring_phys;
	int size;
	int alloc;
	int avail;
	int last;
	int next;
	int mask;
};

/* -------------------------------------------------------------------------- */

/*
 * KSZ8695 switch definitions
 */

enum {
	TABLE_STATIC_MAC = 0,
	TABLE_VLAN,
	TABLE_DYNAMIC_MAC,
	TABLE_MIB
};

#define PRIO_QUEUES			2

#define KS_PRIORITY_IN_REG		32
#define KS_PRIORITY_MASK		1
#define KS_PRIORITY_SHIFT		1

#define SWITCH_PORT_NUM			4

#define PORT_COUNTER_NUM		0x20
#define SWITCH_COUNTER_NUM		PORT_COUNTER_NUM
#define TOTAL_SWITCH_COUNTER_NUM	(PORT_COUNTER_NUM + 2)

#define MIB_COUNTER_RX_LO_PRIORITY	0x00
#define MIB_COUNTER_RX_HI_PRIORITY	0x01
#define MIB_COUNTER_RX_UNDERSIZE	0x02
#define MIB_COUNTER_RX_FRAGMENT		0x03
#define MIB_COUNTER_RX_OVERSIZE		0x04
#define MIB_COUNTER_RX_JABBER		0x05
#define MIB_COUNTER_RX_SYMBOL_ERR	0x06
#define MIB_COUNTER_RX_CRC_ERR		0x07
#define MIB_COUNTER_RX_ALIGNMENT_ERR	0x08
#define MIB_COUNTER_RX_CTRL_8808	0x09
#define MIB_COUNTER_RX_PAUSE		0x0A
#define MIB_COUNTER_RX_BROADCAST	0x0B
#define MIB_COUNTER_RX_MULTICAST	0x0C
#define MIB_COUNTER_RX_UNICAST		0x0D
#define MIB_COUNTER_RX_OCTET_64		0x0E
#define MIB_COUNTER_RX_OCTET_65_127	0x0F
#define MIB_COUNTER_RX_OCTET_128_255	0x10
#define MIB_COUNTER_RX_OCTET_256_511	0x11
#define MIB_COUNTER_RX_OCTET_512_1023	0x12
#define MIB_COUNTER_RX_OCTET_1024_1522	0x13
#define MIB_COUNTER_TX_LO_PRIORITY	0x14
#define MIB_COUNTER_TX_HI_PRIORITY	0x15
#define MIB_COUNTER_TX_LATE_COLLISION	0x16
#define MIB_COUNTER_TX_PAUSE		0x17
#define MIB_COUNTER_TX_BROADCAST	0x18
#define MIB_COUNTER_TX_MULTICAST	0x19
#define MIB_COUNTER_TX_UNICAST		0x1A
#define MIB_COUNTER_TX_DEFERRED		0x1B
#define MIB_COUNTER_TX_TOTAL_COLLISION	0x1C
#define MIB_COUNTER_TX_EXCESS_COLLISION	0x1D
#define MIB_COUNTER_TX_SINGLE_COLLISION	0x1E
#define MIB_COUNTER_TX_MULTI_COLLISION	0x1F

#define MIB_COUNTER_RX_DROPPED_PACKET	0x20
#define MIB_COUNTER_TX_DROPPED_PACKET	0x21

#define LEARNED_MAC_TABLE_ENTRIES	1024
#define STATIC_MAC_TABLE_ENTRIES	8

/**
 * struct ksz_mac_table - Static MAC table data structure
 * @mac_addr:	MAC address to filter.
 * @vid:	VID value.
 * @fid:	FID value.
 * @ports:	Port membership.
 * @override:	Override setting.
 * @use_fid:	FID use setting.
 * @valid:	Valid setting indicating the entry is being used.
 */
struct ksz_mac_table {
	u8 mac_addr[MAC_ADDR_LEN];
	u16 vid;
	u8 fid;
	u8 ports;
	u8 override:1;
	u8 use_fid:1;
	u8 valid:1;
};

#define VLAN_TABLE_ENTRIES		16

/**
 * struct ksz_vlan_table - VLAN table data structure
 * @vid:	VID value.
 * @fid:	FID value.
 * @member:	Port membership.
 * @valid:	Valid setting indicating the entry is being used.
 */
struct ksz_vlan_table {
	u16 vid;
	u8 fid;
	u8 member;
	u8 valid:1;
};

#define DIFFSERV_ENTRIES		64

#define TOTAL_PORT_NUM			(SWITCH_PORT_NUM + 1)
#define HOST_MASK			(1 << SWITCH_PORT_NUM)
#define PORT_MASK			((1 << (SWITCH_PORT_NUM + 1)) - 1)

#define HOST_PORT			SWITCH_PORT_NUM

/**
 * struct ksz_port_mib - Port MIB data structure
 * @cnt_ptr:	Current pointer to MIB counter index.
 * @mib_start:	The starting counter index.  Some ports do not start at 0.
 * @counter:	64-bit MIB counter value.
 * @dropped:	Temporary buffer to remember last read packet dropped values.
 *
 * MIB counters needs to be read periodically so that counters do not get
 * overflowed and give incorrect values.  A right balance is needed to
 * satisfy this condition and not waste too much CPU time.
 */
struct ksz_port_mib {
	u8 cnt_ptr;
	u8 mib_start;
	u8 reserved[2];

	u64 counter[TOTAL_SWITCH_COUNTER_NUM];
	u32 dropped[2];
};

/**
 * struct ksz_port_cfg - Port configuration data structure
 * @vid:	VID value.
 * @member:	Port membership.
 * @port_prio:	Port priority.
 * @rx_rate:	Receive priority rate.
 * @tx_rate:	Transmit priority rate.
 * @stp_state:	Current Spanning Tree Protocol state.
 */
struct ksz_port_cfg {
	u16 vid;
	u8 member;
	u8 port_prio;
	u32 rx_rate[PRIO_QUEUES];
	u32 tx_rate[PRIO_QUEUES];
	int stp_state;
};

/**
 * struct ksz_sw_info - KSZ8695 switch information data structure
 * @mac_table:	MAC table entries information.
 * @vlan_table:	VLAN table entries information.
 * @port_cfg:	Port configuration information.
 * @port_mib:	Port MIB information.
 * @diffserv:	DiffServ priority settings.  Possible values from 6-bit of ToS
 *		(bit7 ~ bit2) field.
 * @br_addr:	Bridge address.  Used for STP.
 * @mac_addr:	Switch MAC address.
 * @broad_per:	Broadcast storm percentage.
 * @member:	Current port membership.  Used for STP.
 * @p_802_1p:	802.1P priority setting.  Possible values from 3-bit of 802.1p
 *		tag priority field.
 * @stp:	STP port membership.  Used for STP.
 */
struct ksz_sw_info {
	struct ksz_mac_table mac_table[STATIC_MAC_TABLE_ENTRIES];
	struct ksz_vlan_table vlan_table[VLAN_TABLE_ENTRIES];
	struct ksz_port_cfg port_cfg[TOTAL_PORT_NUM];
	struct ksz_port_mib port_mib[TOTAL_PORT_NUM];

	u32 diffserv[DIFFSERV_ENTRIES / KS_PRIORITY_IN_REG];

	u8 br_addr[MAC_ADDR_LEN];
	u8 mac_addr[MAC_ADDR_LEN];

	u8 broad_per;
	u8 member;
	u8 p_802_1p;
	u8 stp;
};

#define TX_RATE_UNIT			10000

/**
 * struct ksz_port_info - Port information data structure
 * @state:	Connection status of the port.
 * @tx_rate:	Transmit rate divided by 10000 to get Mbit.
 * @duplex:	Duplex mode.
 * @port_id:	Port index to access actual hardware register.
 * @link_down:	Indication the link has just gone down.
 * @force_reg:	Register to force the link.
 * @link_reg:	Register to determine link.
 * @phy_reg:	Register to access the PHY.
 * @pdev:	Pointer to OS dependent network device.
 *
 * It is pointless to read MIB counters when the port is disconnected.  The
 * @state provides the connection status so that MIB counters are read only
 * when the port is connected.  The @link_down indicates the port is just
 * disconnected so that all MIB counters are read one last time to update the
 * information.
 */
struct ksz_port_info {
	uint state;
	uint tx_rate;
	u8 duplex;
	u8 port_id;
	u8 link_down;
	u8 reserved[1];
	int force_reg;
	int link_reg;
	int phy_reg;
	void *pdev;
};

/* Switch features and bug fixes. */
#define STP_SUPPORT			(1 << 0)

/* Software overrides. */
#define PAUSE_FLOW_CTRL			(1 << 0)
#define FAST_AGING			(1 << 1)

/**
 * struct ksz_sw - Virtual switch data structure
 * @hwlock:		Pointer to hardware lock.
 * @lock		Software lock to switch structure.
 * @locked:		locked status.
 * @info:		Pointer to switch information structure.
 * @port_info:		Port information.
 * @mib_cnt:		Number of MIB counters this switch has.
 * @mib_port_cnt:	Number of ports with MIB counters.
 * @dev_count:		Number of network devices this switch supports.
 * @id:			Hardware ID.  Used for display only.
 * @features:		Switch features to enable.
 * @overrides:		Switch features to override.
 */
struct ksz_sw {
	struct mutex *hwlock;
	struct mutex lock;
	int locked;

	struct ksz_sw_info *info;
	struct ksz_port_info port_info[TOTAL_PORT_NUM];
	int mib_cnt;
	int mib_port_cnt;

	int dev_count;
	int id;

	uint features;
	uint overrides;
};

/**
 * struct ksz_port - Virtual port data structure
 * @duplex:		Duplex mode setting.  1 for half duplex, 2 for full
 *			duplex, and 0 for auto, which normally results in full
 *			duplex.
 * @speed:		Speed setting.  10 for 10 Mbit, 100 for 100 Mbit, and
 *			0 for auto, which normally results in 100 Mbit.
 * @force_link:		Force link setting.  0 for auto-negotiation, and 1 for
 *			force.
 * @flow_ctrl:		Flow control setting.  PHY_NO_FLOW_CTRL for no flow
 *			control, and PHY_FLOW_CTRL for flow control.
 *			PHY_TX_ONLY and PHY_RX_ONLY are not supported for 100
 *			Mbit PHY.
 * @first_port:		Index of first port this port supports.
 * @mib_port_cnt:	Number of ports with MIB counters.
 * @port_cnt:		Number of ports this port supports.
 * @counter:		Port statistics counter.
 * @hw:			Pointer to hardware structure.
 * @sw:			Pointer to virtual switch structure.
 * @linked:		Pointer to port information linked to this port.
 */
struct ksz_port {
	u8 duplex;
	u8 speed;
	u8 force_link;
	u8 flow_ctrl;

	int first_port;
	int mib_port_cnt;
	int port_cnt;
	u64 counter[OID_COUNTER_LAST];

	struct ksz_hw *hw;
	struct ksz_sw *sw;
	struct ksz_port_info *linked;
};

/* Adjust this number down if there is transmit problem in user space. */
#define MAX_TX_HELD_SIZE		51000

/* Hardware features and bug fixes. */
#define LINK_INT_WORKING		(1 << 0)
#define SMALL_PACKET_TX_BUG		(1 << 1)
#define HALF_DUPLEX_SIGNAL_BUG		(1 << 2)
#define IPV6_CSUM_GEN_HACK		(1 << 3)
#define RX_OVERRUN_BUG			(1 << 4)
#define RX_HUGE_FRAME			(1 << 16)
#define IP_HEADER_ALIGN			(1 << 17)

/* Software overrides. */
#define CHECK_RX_OVERRUN		(1 << 2)
#define RX_LOOPBACK			(1 << 3)
#define RX_ALL				(1 << 4)
#define DATA_HEADER			(1 << 5)

#ifdef DEBUG_VERIFY
#define RX_DBG				(1 << 8)
#define RX_DATA				(1 << 9)
#define TX_DBG				(1 << 10)
#define TX_DATA				(1 << 11)
#define CSUM_GEN			(1 << 16)
#define NO_CSUM_GEN			(1 << 17)
#define NO_IP_CSUM_GEN			(1 << 18)
/* Verify hardware transmit loopback is working. */
#define TX_LOOPBACK			(1 << 20)
#define TX_SHORT_FRAME			(1 << 21)
#define VERIFY_MIB			(1 << 22)
#endif

enum {
	PHY_NO_FLOW_CTRL,
	PHY_FLOW_CTRL,
	PHY_TX_ONLY,
	PHY_RX_ONLY
};

/**
 * struct ksz_hw - KSZ8695 hardware data structure
 * @io:			Virtual address assigned.
 * @dst_ports:		Destination ports in switch for transmission.
 * @tx_cfg:		Cached transmit control settings.
 * @rx_cfg:		Cached receive control settings.
 * @intr_check:		Interrupt check mask.
 * @intr_mask:		Current interrupt mask.
 * @intr_set:		Current interrup set.
 * @intr_blocked:	Interrupt blocked.
 * @rx_desc_info:	Receive descriptor information.
 * @tx_desc_info:	Transmit descriptor information.
 * @tx_int_cnt:		Transmit interrupt count.  Used for TX optimization.
 * @tx_int_mask:	Transmit interrupt mask.  Used for TX optimization.
 * @tx_size:		Transmit data size.  Used for TX optimization.
 *			The maximum is defined by MAX_TX_HELD_SIZE.
 * @perm_addr:		Permanent MAC address.
 * @override_addr:	Overrided MAC address.
 * @address:		Additional MAC address entries.
 * @addr_list_size:	Additional MAC address list size.
 * @mac_override:	Indication of MAC address overrided.
 * @promiscuous:	Counter to keep track of promiscuous mode set.
 * @all_multi:		Counter to keep track of all multicast mode set.
 * @multi_list:		Multicast address entries.
 * @multi_bits:		Cached multicast hash table settings.
 * @multi_list_size:	Multicast address list size.
 * @enabled:		Indication of hardware enabled.
 * @rx_stop:		Indication of receive process stop.
 * @features:		Hardware features to enable.
 * @overrides:		Hardware features to override.
 */
struct ksz_hw {
	void __iomem *io;

	int dst_ports;

	u32 tx_cfg;
	u32 rx_cfg;
	u32 intr_check;
	u32 intr_mask;
	u32 intr_set;
	uint intr_blocked;

	struct ksz_desc_info rx_desc_info;
	struct ksz_desc_info tx_desc_info;

	int tx_int_cnt;
	int tx_int_mask;
	int tx_size;

	u8 perm_addr[MAC_ADDR_LEN];
	u8 override_addr[MAC_ADDR_LEN];
	u8 address[ADDITIONAL_ENTRIES][MAC_ADDR_LEN];
	u8 addr_list_size;
	u8 mac_override;
	u8 promiscuous;
	u8 all_multi;
	u8 multi_list_size;

	u8 enabled;
	u8 rx_stop;
	u8 shift;

	uint features;
	uint overrides;

	uint bad[COUNT_BAD_LAST];
	uint good[COUNT_GOOD_LAST];
};

/* -------------------------------------------------------------------------- */

/**
 * struct ksz_timer_info - Timer information data structure
 * @timer:	Kernel timer.
 * @cnt:	Running timer counter.
 * @max:	Number of times to run timer; -1 for infinity.
 * @period:	Timer period in jiffies.
 */
struct ksz_timer_info {
	struct timer_list timer;
	int cnt;
	int max;
	int period;
};

/* -------------------------------------------------------------------------- */

/**
 * struct ksz_shared_mem - OS dependent shared memory data structure
 * @dma_addr:	Physical DMA address allocated.
 * @alloc_size:	Allocation size.
 * @phys:	Actual physical address used.
 * @alloc_virt:	Virtual address allocated.
 * @virt:	Actual virtual address used.
 */
struct ksz_shared_mem {
	dma_addr_t dma_addr;
	uint alloc_size;
	uint phys;
	u8 *alloc_virt;
	u8 *virt;
};

/* -------------------------------------------------------------------------- */

/**
 * struct ksz_counter_info - OS dependent counter information data structure
 * @counter:	Wait queue to wakeup after counters are read.
 * @time:	Next time in jiffies to read counter.
 * @read:	Indication of counters read in full or not.
 */
struct ksz_counter_info {
	wait_queue_head_t counter;
	unsigned long time;
	int read;
};

/* -------------------------------------------------------------------------- */

#define DEV_NAME_SIZE			20

struct ksz_dev_attr {
	struct device_attribute dev_attr;
	char dev_name[DEV_NAME_SIZE];
};

enum {
	PROC_SW_INFO,

	PROC_SET_SW_DUPLEX,
	PROC_SET_SW_SPEED,
	PROC_SET_SW_FORCE,
	PROC_SET_SW_FLOW_CTRL,

	PROC_SET_SW_FEATURES,
	PROC_SET_SW_OVERRIDES,
	PROC_GET_PORTS,
	PROC_SET_SW_MIB,

	PROC_SET_SW_REG,

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

	PROC_SET_IGMP_SNOOP,

	PROC_SET_AGGR_BACKOFF,
	PROC_SET_NO_EXC_DROP,
	PROC_SET_BUFFER_RESERVE,
	PROC_SET_BUFFER_SHARE,

	PROC_SET_HUGE_PACKET,
	PROC_SET_LEGAL_PACKET,
	PROC_SET_LENGTH_CHECK,

	PROC_SET_BACK_PRESSURE_MODE,
	PROC_SET_SWITCH_BACK_PRESSURE,
	PROC_SET_SWITCH_FLOW_CTRL,
	PROC_SET_SWITCH_10_MBIT,

	PROC_SET_RX_FLOW_CTRL,
	PROC_SET_TX_FLOW_CTRL,
	PROC_SET_FAIR_FLOW_CTRL,
	PROC_SET_VLAN_BOUNDARY,

	PROC_SET_PASS_ALL,
	PROC_SET_PRIORITY_SCHEME,

	PROC_SW_LAST
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

	PROC_SET_RX,
	PROC_SET_TX,
	PROC_SET_LEARN,

	PROC_ENABLE_PRIO_QUEUE,
	PROC_ENABLE_PRIO_RATE,
	PROC_SET_RX_P0_RATE,
	PROC_SET_RX_P1_RATE,
	PROC_SET_TX_P0_RATE,
	PROC_SET_TX_P1_RATE,

	PROC_SET_MIRROR_PORT,
	PROC_SET_MIRROR_RX,
	PROC_SET_MIRROR_TX,

	PROC_SET_BACK_PRESSURE,
	PROC_SET_FORCE_FLOW_CTRL,

	PROC_GET_PORT_DUPLEX,
	PROC_GET_PORT_SPEED,

	PROC_PORT_LAST
};

enum {
	PROC_SET_STATIC_FID,
	PROC_SET_STATIC_USE_FID,
	PROC_SET_STATIC_OVERRIDE,
	PROC_SET_STATIC_VALID,
	PROC_SET_STATIC_PORTS,
	PROC_SET_STATIC_MAC_ADDR,
};

#ifdef CONFIG_KS8695P
enum {
	PROC_SET_VLAN_VALID,
	PROC_SET_VLAN_MEMBER,
	PROC_SET_VLAN_FID,
	PROC_SET_VLAN_VID,
};
#endif

enum {
	PROC_INFO,

	PROC_SET_DUPLEX,
	PROC_SET_SPEED,
	PROC_SET_FORCE,
	PROC_SET_FLOW_CTRL,

	PROC_SET_FEATURES,
	PROC_SET_OVERRIDES,

	PROC_MAIN_LAST,

	PROC_LAST = PROC_MAIN_LAST +
		PROC_SW_LAST +
		PROC_PORT_LAST
};

/* -------------------------------------------------------------------------- */

/**
 * struct dev_info - Network device information data structure
 * @dev:		Pointer to network device.
 * @pdev:		Pointer to base device.
 * @hw:			Hardware structure.
 * @sw:			Virtual switch structure.
 * @desc_pool:		Physical memory used for descriptor pool.
 * @proc_sem:		Semaphore for proc accessing.
 * @hwlock:		Spinlock to prevent hardware from accessing.
 * @lock:		Mutex lock to prevent device from accessing.
 * @dev_rcv:		Receive process function used.
 * @last_skb:		Socket buffer allocated for descriptor rx fragments.
 * @skb_index:		Buffer index for receiving fragments.
 * @skb_len:		Buffer length for receiving fragments.
 * @mib_read:		Workqueue to read MIB counters.
 * @mib_timer_info:	Timer to read MIB counters.
 * @counter:		Used for MIB reading.
 * @mtu:		Current MTU used.  The default is REGULAR_RX_BUF_SIZE;
 *			the maximum is MAX_RX_BUF_SIZE.
 * @max_buf_size:	The maximum allowed receive buffer size.
 * @opened:		Counter to keep track of device open.
 * @rx_tasklet:		Receive processing tasklet.
 * @tx_tasklet:		Transmit processing tasklet.
 * @wol_enable:		Wake-on-LAN enable set by ethtool.
 * @wol_support:	Wake-on-LAN support used by ethtool.
 * @mem_start:		The starting memory address.
 * @irq_count:		Number of interrupts used.
 * @irq_name:		The interrupt names.
 */
struct dev_info {
	struct net_device *basedev;
	struct net_device *dev;
	struct device *pdev;

	struct ksz_hw hw;
	struct ksz_sw sw;
	struct ksz_shared_mem desc_pool;

	struct ksz_dev_attr *ksz_port_attrs[TOTAL_PORT_NUM];
	struct attribute **port_attrs[TOTAL_PORT_NUM];
	struct ksz_dev_attr *ksz_mac_attrs[STATIC_MAC_TABLE_ENTRIES];
	struct attribute **mac_attrs[STATIC_MAC_TABLE_ENTRIES];
#ifdef CONFIG_KS8695P
	struct ksz_dev_attr *ksz_vlan_attrs[VLAN_TABLE_ENTRIES];
	struct attribute **vlan_attrs[VLAN_TABLE_ENTRIES];
#endif
	struct semaphore proc_sem;

	spinlock_t hwlock;
	struct mutex lock;

	int (*dev_rcv)(struct dev_info *);

	struct sk_buff *last_skb;
	int skb_index;
	int skb_len;

	struct work_struct mib_read;
	struct ksz_timer_info mib_timer_info;
	struct ksz_counter_info counter[TOTAL_PORT_NUM];

	int mtu;
	int max_buf_size;
	int opened;

	struct tasklet_struct rx_tasklet;
	struct tasklet_struct tx_tasklet;

	int wol_enable;
	int wol_support;

	unsigned int mem_start;

	int irq_count;
	char irq_name[7][40];
};

/**
 * struct dev_priv - Network device private data structure
 * @adapter:		Adapter device information.
 * @port:		Port information.
 * @monitor_time_info:	Timer to monitor ports.
 * @stats:		Network statistics.
 * @proc_info:		Proc information.
 * @proc_main:		Main proc entry.
 * @proc_port_info:	Proc information for each port.
 * @proc_port:		Port proc entry.
 * @id:			Device ID.
 * @mii_if:		MII interface information.
 * @advertising:	Temporary variable to store advertised settings.
 * @msg_enable:		The message flags controlling driver output.
 * @media_state:	The connection status of the device.
 * @multicast:		The all multicast state of the device.
 * @promiscuous:	The promiscuous state of the device.
 * @state:		STP port state.  Used for STP.
 */
struct dev_priv {
	struct dev_info *adapter;
	struct ksz_port port;
	struct ksz_timer_info monitor_timer_info;
	struct net_device_stats stats;

	int id;

	struct mii_if_info mii_if;
	u32 advertising;

	u32 msg_enable;
	int media_state;
	int multicast;
	int promiscuous;
	u8 state;

#ifdef DEBUG_COUNTER
	unsigned long query_jiffies;
#endif
};

/* -------------------------------------------------------------------------- */

#define DRV_NAME			"centaur-net"
#define DEVICE_NAME			"Centaur"
#define DRV_VERSION			"1.0.0"
#define DRV_RELDATE			"Jun 1, 2012"

static char version[] =
	"Microchip " DEVICE_NAME " " DRV_VERSION " (" DRV_RELDATE ")";

#ifdef CONFIG_KS8695P
static u8 DEFAULT_MAC_ADDRESS[] = { 0x00, 0x10, 0xA1, 0x86, 0x10, 0x01 };
#endif
#ifdef CONFIG_KS8695X
static u8 DEFAULT_MAC_ADDRESS[] = { 0x00, 0x10, 0xA1, 0x86, 0x00, 0x01 };
#endif

#ifdef DEBUG
#define NET_MSG_ENABLE  (NETIF_MSG_DRV | NETIF_MSG_PROBE | NETIF_MSG_LINK)
#else
#define NET_MSG_ENABLE  0
#endif

#if 0
#define CONFIG_KSZ_NAPI
#endif

#if 0
#define HIGH_MEM_SUPPORT
#endif

#if 0
#define SET_MAC_ADDR
#endif

#define SKB_COPY_MAX			64

#ifdef CONFIG_KSZ_NAPI
#define ksz_rx_skb			netif_receive_skb
#define ksz_rx_quota(count, quota)	min(count, quota)
#else
#define ksz_rx_skb			netif_rx
#define ksz_rx_quota(count, quota)	count
#endif

/* -------------------------------------------------------------------------- */

/**
 * ksz_start_timer - start kernel timer
 * @info:	Kernel timer information.
 * @time:	The time tick.
 *
 * This routine starts the kernel timer after the specified time tick.
 */
static void ksz_start_timer(struct ksz_timer_info *info, int time)
{
	info->cnt = 0;
	info->timer.expires = jiffies + time;
	add_timer(&info->timer);

	/* infinity */
	info->max = -1;
}  /* ksz_start_timer */

/**
 * ksz_stop_timer - stop kernel timer
 * @info:	Kernel timer information.
 *
 * This routine stops the kernel timer.
 */
static void ksz_stop_timer(struct ksz_timer_info *info)
{
	if (info->max) {
		info->max = 0;
		del_timer_sync(&info->timer);
	}
}  /* ksz_stop_timer */

static void ksz_init_timer(struct ksz_timer_info *info, int period,
	void (*function)(unsigned long), void *data)
{
	info->max = 0;
	info->period = period;
	init_timer(&info->timer);
	info->timer.function = function;
	info->timer.data = (unsigned long) data;
}  /* ksz_init_timer */

static void ksz_update_timer(struct ksz_timer_info *info)
{
	++info->cnt;
	if (info->max > 0) {
		if (info->cnt < info->max) {
			info->timer.expires = jiffies + info->period;
			add_timer(&info->timer);
		} else
			info->max = 0;
	} else if (info->max < 0) {
		info->timer.expires = jiffies + info->period;
		add_timer(&info->timer);
	}
}  /* ksz_update_timer */

/* -------------------------------------------------------------------------- */

#define DBG_CH  '-'

#ifdef DEBUG_MSG

/* 2 lines buffer. */
#define DEBUG_MSG_BUF			(80 * 2)

#define PRINT_MSG_SIZE			(80 * 20)
#define PRINT_INT_SIZE			(80 * 10)

#define DEBUG_MSG_SIZE			(PRINT_MSG_SIZE + PRINT_INT_SIZE + \
	DEBUG_MSG_BUF * 2)

struct dbg_print {
	char *dbg_buf;
	char *int_buf;
	char *msg;
	char *int_msg;
	int msg_cnt;
	int int_cnt;
	int last_msg_line;
	int last_int_line;
	unsigned long lock;

	struct work_struct dbg_print;
	struct ksz_timer_info dbg_timer_info;
};

static struct dbg_print db;

static void print_buf(char *buf, char **msg, int *cnt, int *last)
{
	if (*last)
		printk(KERN_INFO "%c\n", DBG_CH);
	*last = 0;
	if ('\n' == buf[*cnt - 2] && DBG_CH == buf[*cnt - 1]) {
		buf[*cnt - 1] = '\0';
		*last = 1;
	}
	*msg = buf;
	*cnt = 0;
	printk(KERN_INFO "%s", buf);
}  /* print_buf */

static void dbg_print_work(struct work_struct *work)
{
	if (db.msg != db.dbg_buf)
		print_buf(db.dbg_buf, &db.msg, &db.msg_cnt,
			&db.last_msg_line);
	if (db.int_msg != db.int_buf) {
		printk(KERN_INFO "---\n");
		print_buf(db.int_buf, &db.int_msg, &db.int_cnt,
			&db.last_int_line);
	}
}  /* dbg_print_work */

static void dbg_monitor(unsigned long ptr)
{
	struct dbg_print *dbp = (struct dbg_print *) ptr;

	dbg_print_work(&dbp->dbg_print);
	ksz_update_timer(&dbp->dbg_timer_info);
}  /* dbg_monitor */

static int init_dbg(void)
{
	db.dbg_buf = kmalloc(DEBUG_MSG_SIZE, GFP_KERNEL);
	if (!db.dbg_buf)
		return -ENOMEM;

	db.msg = db.dbg_buf;
	*db.msg = '\0';
	db.int_buf = db.dbg_buf + PRINT_MSG_SIZE + DEBUG_MSG_BUF;
	db.int_msg = db.int_buf;
	*db.int_msg = '\0';
	db.msg_cnt = db.int_cnt = 0;
	db.last_msg_line = 1;
	db.last_int_line = 1;
	db.lock = 0;

	INIT_WORK(&db.dbg_print, dbg_print_work);

	/* 100 ms timeout */
	ksz_init_timer(&db.dbg_timer_info, 100 * HZ / 1000, dbg_monitor, &db);
	ksz_start_timer(&db.dbg_timer_info, db.dbg_timer_info.period);

	return 0;
}  /* init_dbg */

static void exit_dbg(void)
{
	if (db.dbg_buf) {
		ksz_stop_timer(&db.dbg_timer_info);
		flush_work(&db.dbg_print);

		if (db.msg != db.dbg_buf)
			printk(KERN_DEBUG "%s\n", db.dbg_buf);
		if (db.int_msg != db.int_buf)
			printk(KERN_DEBUG "%s\n", db.int_buf);
		kfree(db.dbg_buf);
		db.dbg_buf = NULL;
	}
}  /* exit_dbg */
#endif

static void dbg_msg(char *fmt, ...)
{
#ifdef DEBUG_MSG
	va_list args;
	char **msg;
	int *dbg_cnt;
	int left;
	int in_intr = in_interrupt();
	int n;

	dbg_cnt = &db.msg_cnt;
	msg = &db.msg;
	left = PRINT_MSG_SIZE - db.msg_cnt - 1;
	if (left <= 0) {
		db.last_msg_line = 1;
		return;
	}

	/* Called within interrupt routines. */
	if (in_intr) {
		/*
		 * If not able to get lock then put in the interrupt message
		 * buffer.
		 */
		if (test_bit(1, &db.lock)) {
			dbg_cnt = &db.int_cnt;
			msg = &db.int_msg;
			left = PRINT_INT_SIZE - db.int_cnt - 1;
			in_intr = 0;
		}
	} else
		set_bit(1, &db.lock);
	va_start(args, fmt);
	n = vsnprintf(*msg, left, fmt, args);
	va_end(args);
	if (n > 0) {
		if (left > n)
			left = n;
		*dbg_cnt += left;
		*msg += left;
	}
	if (!in_intr)
		clear_bit(1, &db.lock);
#endif
}  /* dbg_msg */

/* -------------------------------------------------------------------------- */

static inline void dbp_mac_addr(u8 *addr)
{
	dbg_msg("%02x:%02x:%02x:%02x:%02x:%02x",
		addr[0], addr[1], addr[2],
		addr[3], addr[4], addr[5]);
}  /* dbp_mac_addr */

static inline void dbp_pkt(struct sk_buff *skb, char first, char *msg, int hdr)
{
	int i;
	int len = skb->len;
	u8 *data = (u8 *) skb->data;

	if (!first || first != data[0]) {
		if (msg)
			dbg_msg(msg);
		if (hdr && len > 0x40)
			len = 0x40;
		for (i = 0; i < len; i++) {
			dbg_msg("%02x ", data[i]);
			if ((i % 16) == 15)
				dbg_msg("\n");
		}
		if ((i % 16))
			dbg_msg("\n");
	}
}  /* dbp_pkt */

/* -------------------------------------------------------------------------- */

/*
 * Interrupt processing primary routines
 */

static inline void hw_ack_intr(struct ksz_hw *hw, uint interrupt)
{
	KS_W(KS_INT_STATUS, interrupt << hw->shift);
}

static inline void hw_dis_intr(struct ksz_hw *hw)
{
	u32 data;

	data = KS_R(KS_INT_ENABLE);
	data &= ~(hw->intr_check << hw->shift);
	hw->intr_blocked = hw->intr_mask;
	KS_W(KS_INT_ENABLE, data);
	data = KS_R(KS_INT_ENABLE);
	hw->intr_set = (data >> hw->shift) & hw->intr_check;
}

static inline void hw_set_intr(struct ksz_hw *hw, uint interrupt)
{
	u32 data;

	data = KS_R(KS_INT_ENABLE);
	data &= ~(hw->intr_check << hw->shift);
	data |= interrupt << hw->shift;
	hw->intr_set = interrupt;
	KS_W(KS_INT_ENABLE, data);
}

static inline void hw_ena_intr(struct ksz_hw *hw)
{
	hw->intr_blocked = 0;
	hw_set_intr(hw, hw->intr_mask);
}

static inline void hw_dis_intr_bit(struct ksz_hw *hw, uint bit)
{
	hw->intr_mask &= ~(bit);
}

static inline void hw_turn_off_intr(struct ksz_hw *hw, uint interrupt)
{
	u32 read_intr;

	read_intr = KS_R(KS_INT_ENABLE);
	read_intr &= ~(interrupt << hw->shift);
	hw->intr_set = (read_intr >> hw->shift) & hw->intr_check;
	KS_W(KS_INT_ENABLE, read_intr);
	hw_dis_intr_bit(hw, interrupt);
}

/**
 * hw_turn_on_intr - turn on specified interrupts
 * @hw:		The hardware instance.
 * @bit:	The interrupt bits to be on.
 *
 * This routine turns on the specified interrupts in the interrupt mask so that
 * those interrupts will be enabled.
 */
static inline void hw_turn_on_intr(struct ksz_hw *hw, u32 bit)
{
	hw->intr_mask |= bit;

	if (!hw->intr_blocked)
		hw_set_intr(hw, hw->intr_mask);
}  /* hw_turn_on_intr */

static inline void hw_ena_intr_bit(struct ksz_hw *hw, uint interrupt)
{
	u32 read_intr;

	read_intr = KS_R(KS_INT_ENABLE);
	read_intr |= (interrupt << hw->shift);
	hw->intr_set = (read_intr >> hw->shift) & hw->intr_check;
	KS_W(KS_INT_ENABLE, read_intr);
}

static inline void hw_read_intr(struct ksz_hw *hw, uint *status)
{
	*status = (KS_R(KS_INT_STATUS) >> hw->shift) & hw->intr_check;
}

static inline void hw_restore_intr(struct ksz_hw *hw, uint interrupt)
{
	if (interrupt)
		hw_ena_intr(hw);
}

/**
 * hw_block_intr - block hardware interrupts
 *
 * This function blocks all interrupts of the hardware and returns the current
 * interrupt enable mask so that interrupts can be restored later.
 *
 * Return the current interrupt enable mask.
 */
static inline uint hw_block_intr(struct ksz_hw *hw)
{
	uint interrupt = 0;

	if (!hw->intr_blocked) {
		hw_dis_intr(hw);
		interrupt = hw->intr_blocked;
	}
	return interrupt;
}  /* hw_block_intr */

/* -------------------------------------------------------------------------- */

/*
 * Hardware descriptor routines
 */

static inline void reset_desc(struct ksz_desc *desc, union desc_stat status)
{
	status.rx.hw_owned = 0;
	desc->phw->ctrl.data = cpu_to_le32(status.data);
}

static inline void release_desc(struct ksz_desc *desc)
{
	desc->sw.ctrl.tx.hw_owned = 1;
	if (desc->sw.buf_size != desc->sw.buf.data) {
		desc->sw.buf_size = desc->sw.buf.data;
		desc->phw->buf.data = cpu_to_le32(desc->sw.buf.data);
	}
	desc->phw->ctrl.data = cpu_to_le32(desc->sw.ctrl.data);
}

static void get_rx_pkt(struct ksz_desc_info *info, struct ksz_desc **desc)
{
	*desc = &info->ring[info->last];
	info->last++;
	info->last &= info->mask;
	info->avail--;
	(*desc)->sw.buf.data &= ~KS_DESC_RX_MASK;
}

static inline void set_rx_buf(struct ksz_desc *desc, u32 addr)
{
	desc->phw->addr = cpu_to_le32(addr);
}

static inline void set_rx_len(struct ksz_desc *desc, u32 len)
{
	desc->sw.buf.rx.buf_size = len;
}

static inline void get_tx_pkt(struct ksz_desc_info *info,
	struct ksz_desc **desc)
{
	*desc = &info->ring[info->next];
	info->next++;
	info->next &= info->mask;
	info->avail--;
	(*desc)->sw.buf.data &= ~KS_DESC_TX_MASK;
}

static inline void set_tx_buf(struct ksz_desc *desc, u32 addr)
{
	desc->phw->addr = cpu_to_le32(addr);
}

static inline void set_tx_len(struct ksz_desc *desc, u32 len)
{
	desc->sw.buf.tx.buf_size = len;
}

/* -------------------------------------------------------------------------- */

static void KS_W16(int port_reg, u16 data)
{
	u32 reg_data;

	reg_data = KS_R(port_reg & ~3);
	if (port_reg & 3)
		reg_data = (reg_data & 0x0000FFFF) | ((u32) data << 16);
	else
		reg_data = (reg_data & 0xFFFF0000) | data;
	KS_WR(port_reg & ~3, reg_data);
}

/* -------------------------------------------------------------------------- */

static inline void sw_acquire(struct ksz_sw *sw, struct mutex *hwlock)
{
	mutex_lock(&sw->lock);
	if (hwlock) {
		mutex_lock(hwlock);
		sw->locked = true;
	}
}

static inline void sw_release(struct ksz_sw *sw, struct mutex *hwlock)
{
	if (hwlock) {
		sw->locked = false;
		mutex_unlock(hwlock);
	}
	mutex_unlock(&sw->lock);
}

/* Switch functions */

#ifdef CONFIG_KS8695P
#define TABLE_READ			0x10

static inline void chk_iacr_busy(void)
{
	KS_R(KS_IACR_OFFSET);
}

static inline u16 get_iacr_data_8(void)
{
	return (u16) KS_R(KS_ACC_DATA_8_OFFSET);
}
#endif
#ifdef CONFIG_KS8695X
#define TABLE_READ			0x08

static inline void chk_iacr_busy(void)
{
	u32 data;

	data = KS_R(KS_IACR_OFFSET);
	while (data & X_LUE_BUSY)
		data = KS_R(KS_IACR_OFFSET);
}

static inline u16 get_iacr_data_8(void)
{
	return 0;
}
#endif
#define TABLE_SEL_SHIFT			2

/* -------------------------------------------------------------------------- */

#ifdef CONFIG_KS8695P
static inline void mib_w(u32 ctrl_addr)
{
	ctrl_addr |= (((TABLE_MIB << TABLE_SEL_SHIFT) | TABLE_READ) << 8);
	KS_W(KS_P_IACR_OFFSET, ctrl_addr);
	KS_R(KS_P_IACR_OFFSET);
}

static inline u32 mib_r(void)
{
	return KS_R(KS_P_ACC_DATA_0_OFFSET);
}

static inline void mib_overflow(void) {}
#endif

#ifdef CONFIG_KS8695X
static inline void mib_w(u32 ctrl_addr)
{
	KS_W(KS_X_SWITCH_MIB_ADDR, ctrl_addr);
	KS_R(KS_X_SWITCH_MIB_ADDR);
}

static inline u32 mib_r(void)
{
	return KS_R(KS_X_SWITCH_MIB_DATA);
}

static inline void mib_overflow(void)
{
	KS_W(KS_X_SWITCH_MIB_ADDR, MIB_COUNTER_OVERFLOW);
}
#endif

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
	u32 ctrl_addr;
	int timeout;

	ctrl_addr = addr + SWITCH_COUNTER_NUM * port;

	mutex_lock(sw->hwlock);

	mib_w(ctrl_addr);

	for (timeout = 100; timeout > 0; timeout--) {
		data = mib_r();

		if (data & MIB_COUNTER_VALID) {
			if (data & MIB_COUNTER_OVERFLOW) {
				mib_overflow();
				*cnt += MIB_COUNTER_VALUE + 1;
			}
			*cnt += data & MIB_COUNTER_VALUE;
			break;
		}
	}

	mutex_unlock(sw->hwlock);
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
static void port_r_mib_pkt(struct ksz_sw *sw, int port, u32 *last, u64 *cnt)
{
	u32 cur;
	u32 data;
	u32 ctrl_addr;
	int index;
	int n;

	index = KS_MIB_PACKET_DROPPED_RX_0 + port;
	do {
		ctrl_addr = index;

		mutex_lock(sw->hwlock);

		mib_w(ctrl_addr);
		n = 0;
		do {
			data = mib_r();
		} while (!(data & MIB_COUNTER_VALID) && ++n < 5);

		mutex_unlock(sw->hwlock);

		data &= MIB_PACKET_DROPPED;
		cur = *last;
		if (data != cur) {
			*last = data;
			if (data < cur)
				data += MIB_PACKET_DROPPED + 1;
			data -= cur;
			*cnt += data;
		}
		++last;
		++cnt;
		index -= KS_MIB_PACKET_DROPPED_TX -
			KS_MIB_PACKET_DROPPED_TX_0 + 1;
	} while (index >= KS_MIB_PACKET_DROPPED_TX_0 + port);
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
	struct ksz_port_mib *mib = &sw->info->port_mib[port];

	if (mib->mib_start < SWITCH_COUNTER_NUM)
		while (mib->cnt_ptr < SWITCH_COUNTER_NUM) {
			port_r_mib_cnt(sw, port, mib->cnt_ptr,
				&mib->counter[mib->cnt_ptr]);
			++mib->cnt_ptr;
		}
	if (sw->mib_cnt > SWITCH_COUNTER_NUM)
		port_r_mib_pkt(sw, port, mib->dropped,
			&mib->counter[SWITCH_COUNTER_NUM]);
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
static void port_init_cnt(struct ksz_sw *sw, int port)
{
	struct ksz_port_mib *mib = &sw->info->port_mib[port];

	mib->cnt_ptr = 0;
	if (mib->mib_start < SWITCH_COUNTER_NUM)
		do {
			port_r_mib_cnt(sw, port, mib->cnt_ptr,
				&mib->counter[mib->cnt_ptr]);
			++mib->cnt_ptr;
		} while (mib->cnt_ptr < SWITCH_COUNTER_NUM);
	if (sw->mib_cnt > SWITCH_COUNTER_NUM)
		port_r_mib_pkt(sw, port, mib->dropped,
			&mib->counter[SWITCH_COUNTER_NUM]);
	memset((void *) mib->counter, 0, sizeof(u64) *
		TOTAL_SWITCH_COUNTER_NUM);
	mib->cnt_ptr = 0;
}  /* port_init_cnt */

/* -------------------------------------------------------------------------- */

#ifdef CONFIG_KS8695P
/**
 * sw_r_table - read 4 bytes of data from switch table
 * @sw:		The switch instance.
 * @table:	The table selector.
 * @addr:	The address of the table entry.
 * @data:	Buffer to store the read data.
 *
 * This routine reads 4 bytes of data from the table of the switch.
 * Hardware is locked to minimize corruption of read data.
 */
static void sw_r_table(struct ksz_sw *sw, int table, u16 addr, u32 *data)
{
	u32 ctrl_addr;

	ctrl_addr = (((table << TABLE_SEL_SHIFT) | TABLE_READ) << 8) | addr;

	if (!sw->locked)
		mutex_lock(sw->hwlock);
	KS_W(KS_IACR_OFFSET, ctrl_addr);
	chk_iacr_busy();

	/* Make sure data read is valid. */
	*data = KS_R(KS_ACC_DATA_0_OFFSET);
	*data = KS_R(KS_ACC_DATA_0_OFFSET);
	if (!sw->locked)
		mutex_unlock(sw->hwlock);
}  /* sw_r_table */

/**
 * sw_w_table - write 4 bytes of data to the switch table
 * @sw:		The switch instance.
 * @table:	The table selector.
 * @addr:	The address of the table entry.
 * @data:	Data to be written.
 *
 * This routine writes 4 bytes of data to the table of the switch.
 * Hardware is locked to minimize corruption of written data.
 */
static void sw_w_table(struct ksz_sw *sw, int table, u16 addr, u32 data)
{
	u32 ctrl_addr;

	ctrl_addr = ((table << TABLE_SEL_SHIFT) << 8) | addr;

	if (!sw->locked)
		mutex_lock(sw->hwlock);
	chk_iacr_busy();
	KS_W(KS_ACC_DATA_0_OFFSET, data);
	KS_R(KS_ACC_DATA_0_OFFSET);
	KS_W(KS_IACR_OFFSET, ctrl_addr);
	KS_R(KS_IACR_OFFSET);
	if (!sw->locked)
		mutex_unlock(sw->hwlock);
}  /* sw_w_table */
#endif

/**
 * sw_r_table_64 - read 8 bytes of data from the switch table
 * @sw:		The switch instance.
 * @table:	The table selector.
 * @addr:	The address of the table entry.
 * @data_hi:	Buffer to store the high part of read data (bit63 ~ bit32).
 * @data_lo:	Buffer to store the low part of read data (bit31 ~ bit0).
 *
 * This routine reads 8 bytes of data from the table of the switch.
 * Hardware is locked to minimize corruption of read data.
 */
static void sw_r_table_64(struct ksz_sw *sw, int table, u16 addr, u32 *data_hi,
	u32 *data_lo)
{
	u32 ctrl_addr;

	ctrl_addr = (((table << TABLE_SEL_SHIFT) | TABLE_READ) << 8) | addr;

	if (!sw->locked)
		mutex_lock(sw->hwlock);
	KS_W(KS_IACR_OFFSET, ctrl_addr);
	chk_iacr_busy();

	/* Make sure data read is valid. */
	*data_hi = KS_R(KS_ACC_DATA_4_OFFSET);
	*data_hi = KS_R(KS_ACC_DATA_4_OFFSET);
	*data_lo = KS_R(KS_ACC_DATA_0_OFFSET);
	if (!sw->locked)
		mutex_unlock(sw->hwlock);
}  /* sw_r_table_64 */

/**
 * sw_w_table_64 - write 8 bytes of data to the switch table
 * @sw:		The switch instance.
 * @table:	The table selector.
 * @addr:	The address of the table entry.
 * @data_hi:	The high part of data to be written (bit63 ~ bit32).
 * @data_lo:	The low part of data to be written (bit31 ~ bit0).
 *
 * This routine writes 8 bytes of data to the table of the switch.
 * Hardware is locked to minimize corruption of written data.
 */
static void sw_w_table_64(struct ksz_sw *sw, int table, u16 addr, u32 data_hi,
	u32 data_lo)
{
	u32 ctrl_addr;

	ctrl_addr = ((table << TABLE_SEL_SHIFT) << 8) | addr;

	if (!sw->locked)
		mutex_lock(sw->hwlock);
	chk_iacr_busy();
	KS_WR(KS_ACC_DATA_4_OFFSET, data_hi);
	KS_WR(KS_ACC_DATA_0_OFFSET, data_lo);
	udelay(1);

	KS_W(KS_IACR_OFFSET, ctrl_addr);
	KS_R(KS_IACR_OFFSET);
	if (!sw->locked)
		mutex_unlock(sw->hwlock);
}  /* sw_w_table_64 */

#if 0
/**
 * sw_r_table_all - read all 10 bytes of data from the switch table
 * @sw:		The switch instance.
 * @table:	The table selector.
 * @addr:	The address of the table entry.
 * @data:	Buffer to store the highest part of read data (bit79 ~ bit64).
 * @data_hi:	Buffer to store the high part of read data (bit63 ~ bit32).
 * @data_lo:	Buffer to store the low part of read data (bit31 ~ bit0).
 *
 * This routine reads 10 bytes of data from the table of the switch.
 * Hardware is locked to minimize corruption of read data.
 */
static void sw_r_table_all(struct ksz_sw *sw, int table, u16 addr, u16 *data,
	u32 *data_hi, u32 *data_lo)
{
	u32 ctrl_addr;

	ctrl_addr = (((table << TABLE_SEL_SHIFT) | TABLE_READ) << 8) | addr;

	if (!sw->locked)
		mutex_lock(sw->hwlock);
	KS_W(KS_IACR_OFFSET, ctrl_addr);
	chk_iacr_busy();

	/* Make sure data read is valid. */
	*data_hi = KS_R(KS_ACC_DATA_4_OFFSET);
	*data = get_iacr_data_8();
	*data_hi = KS_R(KS_ACC_DATA_4_OFFSET);
	*data_lo = KS_R(KS_ACC_DATA_0_OFFSET);
	if (!sw->locked)
		mutex_unlock(sw->hwlock);
}  /* sw_r_table_all */
#endif

/* -------------------------------------------------------------------------- */

#ifdef CONFIG_KS8695P
static inline int valid_dyn_entry(u32 *data_hi, u8 *data)
{
	int timeout = 100;

	*data_hi = KS_R(KS_ACC_DATA_4_OFFSET);
	do {
		*data_hi = KS_R(KS_ACC_DATA_4_OFFSET);
		timeout--;
	} while ((*data_hi & P_DYN_MAC_TABLE_NOT_READY) && timeout);

	/* Entry is not ready for accessing. */
	if (*data_hi & P_DYN_MAC_TABLE_NOT_READY)
		return 1;

	/* Entry is ready for accessing. */
	else {
		*data = (u8) KS_R(KS_ACC_DATA_8_OFFSET);

		/* There is no valid entry in the table. */
		if (*data & P_DYN_MAC_TABLE_MAC_EMPTY)
			return 2;
	}
	return 0;
}

static inline u16 get_dyn_entries(u32 data_hi, u16 data)
{
	return (u16)((((data & P_DYN_MAC_TABLE_ENTRIES_H) <<
		P_DYN_MAC_ENTRIES_H_SHIFT) |
		(((data_hi & P_DYN_MAC_TABLE_ENTRIES) >>
		P_DYN_MAC_ENTRIES_SHIFT))) + 1);
}

static inline u8 get_dyn_fid(u32 data_hi)
{
	return (u8)((data_hi & P_DYN_MAC_TABLE_FID) >>
		P_DYN_MAC_FID_SHIFT);
}
#endif

#ifdef CONFIG_KS8695X
static inline int valid_dyn_entry(u32 *data_hi, u8 *data)
{
	while (*data_hi & X_LUE_BUSY)
		*data_hi = KS_R(KS_IACR_OFFSET);
	*data_hi = KS_R(KS_ACC_DATA_4_OFFSET);
	*data_hi = KS_R(KS_ACC_DATA_4_OFFSET);
	if (*data_hi & X_DYN_MAC_TABLE_MAC_EMPTY)
		return 2;
	return 0;
}

static inline u16 get_dyn_entries(u32 data_hi, u16 data)
{
	return (u16)(((data_hi & X_DYN_MAC_TABLE_ENTRIES) >>
		X_DYN_MAC_ENTRIES_SHIFT) + 1);
}

static inline u8 get_dyn_fid(u32 data_hi)
{
	return 0;
}
#endif

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
	u32 ctrl_addr;
	int rc;
	u8 data;

	ctrl_addr = (((TABLE_DYNAMIC_MAC << TABLE_SEL_SHIFT) | TABLE_READ) <<
		8) | addr;

	if (!sw->locked)
		mutex_lock(sw->hwlock);
	KS_W(KS_IACR_OFFSET, ctrl_addr);
	data_hi = KS_R(KS_IACR_OFFSET);

	rc = valid_dyn_entry(&data_hi, &data);
	if (1 == rc) {
		if (0 == addr)
			*entries = 0;
	} else if (2 == rc)
		*entries = 0;
	/* At least one valid entry in the table. */
	else {
		/* Check out how many valid entry in the table. */
		*entries = get_dyn_entries(data_hi, data);
		*fid = get_dyn_fid(data_hi);
		*src_port = (u8)((data_hi & DYN_MAC_TABLE_SRC_PORT) >>
			DYN_MAC_SRC_PORT_SHIFT);
		*timestamp = (u8)((data_hi & DYN_MAC_TABLE_TIMESTAMP) >>
			DYN_MAC_TIMESTAMP_SHIFT);

		/* get the detail of dynamaic MAC table information */
		data_lo = KS_R(KS_ACC_DATA_0_OFFSET);

		mac_addr[5] = (u8) data_lo;
		mac_addr[4] = (u8)(data_lo >> 8);
		mac_addr[3] = (u8)(data_lo >> 16);
		mac_addr[2] = (u8)(data_lo >> 24);

		mac_addr[1] = (u8) data_hi;
		mac_addr[0] = (u8)(data_hi >> 8);
		rc = 0;
	}
	if (!sw->locked)
		mutex_unlock(sw->hwlock);

	return rc;
}  /* sw_r_dyn_mac_table */

static void sw_d_dyn_mac_table(struct ksz_sw *sw)
{
	u16 entries = 0;
	u16 i;
	u8 mac_addr[MAC_ADDR_LEN];
	u8 ports = 0;
	u8 timestamp = 0;
	u8 fid = 0;

	memset(mac_addr, 0, MAC_ADDR_LEN);
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
}  /* sw_d_dyn_mac_table */

/* -------------------------------------------------------------------------- */

#ifdef CONFIG_KS8695P
static inline int get_use_fid(u32 data_hi)
{
	return (data_hi & P_STATIC_MAC_TABLE_USE_FID) ? 1 : 0;
}

static inline u8 get_sta_fid(u32 data_hi)
{
	return (u8)((data_hi & P_STATIC_MAC_TABLE_FID) >>
		P_STATIC_MAC_FID_SHIFT);
}

static inline void set_fid(u32 *data_hi, u32 fid)
{
	*data_hi |= P_STATIC_MAC_TABLE_USE_FID >> P_STATIC_MAC_WRITE_SHIFT;
	*data_hi |= fid << (P_STATIC_MAC_FID_SHIFT - P_STATIC_MAC_WRITE_SHIFT);
}
#endif

#ifdef CONFIG_KS8695X
static inline int get_use_fid(u32 data_hi)
{
	return 0;
}

static inline u8 get_sta_fid(u32 data_hi)
{
	return 0;
}

static inline void set_fid(u32 *data_hi, u32 fid) {}
#endif

/**
 * sw_r_sta_mac_table - read from static MAC table
 * @sw:		The switch instance.
 * @addr:	The address of the table entry.
 * @mac_addr:	Buffer to store the MAC address.
 * @ports:	Buffer to store the port members.
 * @override:	Buffer to store the override flag.
 * @use_fid:	Buffer to store the use FID flag which indicates the FID is
 *		valid.
 * @fid:	Buffer to store the FID.
 *
 * This function reads an entry of the static MAC table of the switch.  It
 * calls sw_r_table_64() to get the data.
 *
 * Return 0 if the entry is valid; otherwise -1.
 */
static int sw_r_sta_mac_table(struct ksz_sw *sw, u16 addr, u8 *mac_addr,
	u8 *ports, int *override, int *use_fid, u8 *fid)
{
	u32 data_hi;
	u32 data_lo;

	sw_r_table_64(sw, TABLE_STATIC_MAC, addr, &data_hi, &data_lo);
	if (data_hi & (STATIC_MAC_TABLE_VALID | STATIC_MAC_TABLE_OVERRIDE)) {
		mac_addr[5] = (u8) data_lo;
		mac_addr[4] = (u8)(data_lo >> 8);
		mac_addr[3] = (u8)(data_lo >> 16);
		mac_addr[2] = (u8)(data_lo >> 24);
		mac_addr[1] = (u8) data_hi;
		mac_addr[0] = (u8)(data_hi >> 8);
		*ports = (u8)((data_hi & STATIC_MAC_TABLE_FWD_PORTS) >>
			STATIC_MAC_FWD_PORTS_SHIFT);
		*override = (data_hi & STATIC_MAC_TABLE_OVERRIDE) ? 1 : 0;
		*use_fid = get_use_fid(data_hi);
		*fid = get_sta_fid(data_hi);
		return 0;
	}
	return -1;
}  /* sw_r_sta_mac_table */

/**
 * sw_w_sta_mac_table - write to the static MAC table
 * @sw:		The switch instance.
 * @addr:	The address of the table entry.
 * @mac_addr:	The MAC address.
 * @ports:	The port members.
 * @override:	The flag to override the port receive/transmit settings.
 * @valid:	The flag to indicate entry is valid.
 * @use_fid:	The flag to indicate the FID is valid.
 * @fid:	The FID value.
 *
 * This routine writes an entry of the static MAC table of the switch.  It
 * calls sw_w_table_64() to write the data.
 */
static void sw_w_sta_mac_table(struct ksz_sw *sw, u16 addr, u8 *mac_addr,
	u8 ports, int override, int valid, int use_fid, u8 fid)
{
	u32 data_hi;
	u32 data_lo;

	data_lo = ((u32) mac_addr[2] << 24) |
		((u32) mac_addr[3] << 16) |
		((u32) mac_addr[4] << 8) | mac_addr[5];
	data_hi = ((u32) mac_addr[0] << 8) | mac_addr[1];
	data_hi |= (u32) ports << STATIC_MAC_FWD_PORTS_SHIFT;

	if (override)
		data_hi |= STATIC_MAC_TABLE_OVERRIDE;
	if (use_fid)
		set_fid(&data_hi, fid);
	if (valid)
		data_hi |= STATIC_MAC_TABLE_VALID;
	else
		data_hi &= ~STATIC_MAC_TABLE_OVERRIDE;

	sw_w_table_64(sw, TABLE_STATIC_MAC, addr, data_hi, data_lo);
}  /* sw_w_sta_mac_table */

static void sw_d_sta_mac_table(struct ksz_sw *sw)
{
	u16 i;
	u8 mac_addr[MAC_ADDR_LEN];
	u8 ports;
	int override;
	int use_fid;
	u8 fid;

	i = 0;
	do {
		if (!sw_r_sta_mac_table(sw, i, mac_addr, &ports, &override,
				&use_fid, &fid)) {
			printk(KERN_INFO
				"%d: %02X:%02X:%02X:%02X:%02X:%02X %02x %u %u:%x\n",
				i, mac_addr[0], mac_addr[1], mac_addr[2],
				mac_addr[3], mac_addr[4], mac_addr[5],
				ports, override, use_fid, fid);
		}
		i++;
	} while (i < STATIC_MAC_TABLE_ENTRIES);
}  /* sw_d_sta_mac_table */

/* -------------------------------------------------------------------------- */

#ifdef CONFIG_KS8695P
/**
 * sw_r_vlan_table - read from the VLAN table
 * @sw:		The switch instance.
 * @addr:	The address of the table entry.
 * @vid:	Buffer to store the VID.
 * @fid:	Buffer to store the VID.
 * @member:	Buffer to store the port membership.
 *
 * This function reads an entry of the VLAN table of the switch.  It calls
 * sw_r_table() to get the data.
 *
 * Return 0 if the entry is valid; otherwise -1.
 */
static int sw_r_vlan_table(struct ksz_sw *sw, u16 addr, u16 *vid, u8 *fid,
	u8 *member)
{
	u32 data;

	sw_r_table(sw, TABLE_VLAN, addr, &data);
	if (data & P_VLAN_TABLE_VALID) {
		*vid = (u16)(data & P_VLAN_TABLE_VID);
		*fid = (u8)((data & P_VLAN_TABLE_FID) >> P_VLAN_FID_SHIFT);
		*member = (u8)((data & P_VLAN_TABLE_MEMBERSHIP) >>
			P_VLAN_MEMBERSHIP_SHIFT);
		return 0;
	}
	return -1;
}  /* sw_r_vlan_table */

/**
 * sw_w_vlan_table - write to the VLAN table
 * @sw:		The switch instance.
 * @addr:	The address of the table entry.
 * @vid:	The VID value.
 * @fid:	The FID value.
 * @member:	The port membership.
 * @valid:	The flag to indicate entry is valid.
 *
 * This routine writes an entry of the VLAN table of the switch.  It calls
 * sw_w_table() to write the data.
 */
static void sw_w_vlan_table(struct ksz_sw *sw, u16 addr, u16 vid, u8 fid,
	u8 member, int valid)
{
	u32 data;
	int entry;
	struct ksz_sw_info *info = sw->info;

	data = vid;
	data |= (u32) fid << P_VLAN_FID_SHIFT;
	data |= (u32) member << P_VLAN_MEMBERSHIP_SHIFT;
	if (valid)
		data |= P_VLAN_TABLE_VALID;

	sw_w_table(sw, TABLE_VLAN, addr, data);

	entry = addr;
	if (entry >= VLAN_TABLE_ENTRIES)
		return;
	info->vlan_table[entry].vid = vid;
	info->vlan_table[entry].fid = fid;
	info->vlan_table[entry].member = member;
	info->vlan_table[entry].valid = valid;
}  /* sw_w_vlan_table */

static void sw_d_vlan_table(struct ksz_sw *sw)
{
	u16 i;
	u16 vid;
	u8 fid;
	u8 member;
	struct ksz_sw_info *info = sw->info;

	i = 0;
	do {
		if (!sw_r_vlan_table(sw, i, &vid, &fid, &member)) {
			info->vlan_table[i].vid = vid;
			info->vlan_table[i].fid = fid;
			info->vlan_table[i].member = member;
			info->vlan_table[i].valid = 1;
			printk(KERN_INFO
				"%x: 0x%03x %x %x\n", i, vid, fid, member);
		} else
			info->vlan_table[i].valid = 0;
		i++;
	} while (i < VLAN_TABLE_ENTRIES);
}
#endif

/* -------------------------------------------------------------------------- */

/*
 * Port functions
 */

/**
 * port_chk - check port register bits
 * @port:	The port index.
 * @offset:	The offset of the port register.
 * @bits:	The data bits to check.
 *
 * This function checks whether the specified bits of the port register are set
 * or not.
 *
 * Return 0 if the bits are not set.
 */
static int port_chk(int port, int offset, u32 bits)
{
	u32 addr;
	u32 data;

	PORT_CTRL_ADDR(port, addr);
	addr += offset;
	data = KS_R(addr);
	return (data & bits) == bits;
}  /* port_chk */

/**
 * port_cfg - set port register bits
 * @port:	The port index.
 * @offset:	The offset of the port register.
 * @bits:	The data bits to set.
 * @set:	The flag indicating whether the bits are to be set or not.
 *
 * This routine sets or resets the specified bits of the port register.
 */
static void port_cfg(int port, int offset, u32 bits, int set)
{
	u32 addr;
	u32 data;

	PORT_CTRL_ADDR(port, addr);
	addr += offset;
	data = KS_R(addr);
	if (set)
		data |= bits;
	else
		data &= ~bits;
	KS_WR(addr, data);
}  /* port_cfg */

/**
 * port_chk_shift - check port bit
 * @port:	The port index.
 * @offset:	The offset of the register.
 * @shift:	Number of bits to shift.
 *
 * This function checks whether the specified port is set in the register or
 * not.
 *
 * Return 0 if the port is not set.
 */
int port_chk_shift(int port, u32 addr, int shift)
{
	u32 data;
	u32 bits = 1 << port;

	data = KS_R(addr);
	data >>= shift;
	return (data & bits) == bits;
}  /* port_chk_shift */

/**
 * port_cfg_shift - set port bit
 * @port:	The port index.
 * @offset:	The offset of the register.
 * @shift:	Number of bits to shift.
 * @set:	The flag indicating whether the port is to be set or not.
 *
 * This routine sets or resets the specified port in the register.
 */
void port_cfg_shift(int port, u32 addr, int shift, int set)
{
	u32 data;
	u32 bits = 1 << port;

	data = KS_R(addr);
	bits <<= shift;
	if (set)
		data |= bits;
	else
		data &= ~bits;
	KS_WR(addr, data);
}  /* port_cfg_shift */

/**
 * port_r - read dword from port register.
 * @port:	The port index.
 * @offset:	The offset of the port register.
 * @data:	Buffer to store the data.
 *
 * This routine reads a word from the port register.
 */
static void port_r(int port, int offset, u32 *data)
{
	u32 addr;

	PORT_CTRL_ADDR(port, addr);
	addr += offset;
	*data = KS_R(addr);
}  /* port_r */

/**
 * port_w - write dword to port register.
 * @port:	The port index.
 * @offset:	The offset of the port register.
 * @data:	Data to write.
 *
 * This routine writes a word to the port register.
 */
static void port_w(int port, int offset, u32 data)
{
	u32 addr;

	PORT_CTRL_ADDR(port, addr);
	addr += offset;
	KS_WR(addr, data);
}  /* port_w */

/**
 * sw_chk - check switch register bits
 * @addr:	The address of the switch register.
 * @bits:	The data bits to check.
 *
 * This function checks whether the specified bits of the switch register are
 * set or not.
 *
 * Return 0 if the bits are not set.
 */
static int sw_chk(u32 addr, u32 bits)
{
	u32 data;

	data = KS_R(addr);
	return (data & bits) == bits;
}  /* sw_chk */

/**
 * sw_cfg - set switch register bits
 * @addr:	The address of the switch register.
 * @bits:	The data bits to set.
 * @set:	The flag indicating whether the bits are to be set or not.
 *
 * This function sets or resets the specified bits of the switch register.
 */
static void sw_cfg(u32 addr, u32 bits, int set)
{
	u32 data;

	data = KS_R(addr);
	if (set)
		data |= bits;
	else
		data &= ~bits;
	KS_WR(addr, data);
}  /* sw_cfg */

/* -------------------------------------------------------------------------- */

/* Bandwidth */

static inline void port_cfg_broad_storm(struct ksz_sw *sw, int p, int set)
{
	port_cfg(p, KS_PORT_CTRL_1_OFFSET, PORT_BROADCAST_STORM, set);
}

static inline int port_chk_broad_storm(struct ksz_sw *sw, int p)
{
	return port_chk(p, KS_PORT_CTRL_1_OFFSET, PORT_BROADCAST_STORM);
}

/* 0x04A = 1% for 50 ms */
#define BROADCAST_STORM_VALUE		7400

/**
 * sw_cfg_broad_storm - configure broadcast storm threshold
 * @sw:		The switch instance.
 * @percent:	Broadcast storm threshold in percent of transmit rate.
 *
 * This routine configures the broadcast storm threshold of the switch.
 */
static void sw_cfg_broad_storm(struct ksz_sw *sw, u8 percent)
{
	u32 data;
	u32 value = ((u32) BROADCAST_STORM_VALUE * (u32) percent / 100);

	if (value > BROADCAST_STORM_RATE_BASE)
		value = BROADCAST_STORM_RATE_BASE;

	data = KS_R(KS_SWITCH_CTRL_1_OFFSET);
	data &= ~BROADCAST_STORM_RATE_MASK;
	data |= value << BROADCAST_STORM_RATE_SHIFT;
	KS_WR(KS_SWITCH_CTRL_1_OFFSET, data);
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
	u32 data;

	data = KS_R(KS_SWITCH_CTRL_1_OFFSET);
	num = (data & BROADCAST_STORM_RATE_MASK) >> BROADCAST_STORM_RATE_SHIFT;
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

#ifdef DEBUG_MSG
	for (port = 0; port <= 100; port++) {
		hw_cfg_broad_storm(sw, port);
		if (port != sw->info->broad_per) {
			dbg_msg("max %d%%\n", port - 1);
			break;
		}
	}
#endif
	/* Enable switch broadcast storm protection at 10% percent rate. */
	hw_cfg_broad_storm(sw, BROADCAST_STORM_PROTECTION_RATE);
	for (port = 0; port < SWITCH_PORT_NUM; port++)
		sw_ena_broad_storm(sw, port);
	sw_cfg(KS_SWITCH_CTRL_0_OFFSET, MULTICAST_STORM_DISABLE, 1);
}

/* -------------------------------------------------------------------------- */

#ifdef CONFIG_KS8695P
/**
 * port_cfg_rate - configure port priority rate
 * @port:	The port index.
 * @offset:	The receive or transmit, high or low priority, rate offset.
 * @shift:	The shift position to set the value.
 * @rate:	The rate limit in number of Kbps.
 *
 * This helper routine configures the priority rate of the port.
 */
static void port_cfg_rate(int port, int offset, int shift, uint rate)
{
	u32 data;
	u32 factor;

	factor = rate / PORT_RATE_UNIT;
	if (factor > PORT_PRIORITY_RATE)
		factor = PORT_PRIORITY_RATE;

	port_r(port, offset, &data);
	data &= ~(PORT_PRIORITY_RATE << shift);
	data |= (factor << shift);
	port_w(port, offset, data);
}  /* port_cfg_rate */

/**
 * port_get_rate - get port priority rate
 * @port:	The port index.
 * @offset:	The receive or transmit, high or low priority, rate offset.
 * @shift:	The shift position to get the value.
 * @rate:	Buffer to store the data rate in number of Kbps.
 *
 * This helper routine retrieves the priority rate of the port.
 */
static void port_get_rate(int port, int offset, int shift, uint *rate)
{
	u32 data;

	port_r(port, offset, &data);
	data >>= shift;
	data &= PORT_PRIORITY_RATE;

	*rate = data * PORT_RATE_UNIT;
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
static void hw_cfg_prio_rate(int port, int prio, uint rate, int offset,
	int shift, uint *result)
{
	shift += PORT_RATE_SHIFT * prio;

	port_cfg_rate(port, offset, shift, rate);
	port_get_rate(port, offset, shift, result);
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
	hw_cfg_prio_rate(port, prio, rate,
		KS_PORT_CTRL_3_OFFSET, PORT_RX_LO_RATE_SHIFT,
		&sw->info->port_cfg[port].rx_rate[prio]);
}

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
	hw_cfg_prio_rate(port, prio, rate,
		KS_PORT_CTRL_2_OFFSET, PORT_TX_LO_RATE_SHIFT,
		&sw->info->port_cfg[port].tx_rate[prio]);
}

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
	u32 rx_prio;
	u32 tx_prio;

	port_r(port, KS_PORT_CTRL_3_OFFSET, &rx_prio);
	port_r(port, KS_PORT_CTRL_2_OFFSET, &tx_prio);
	return (rx_prio & (PORT_RX_LO_RATE_ENABLE | PORT_RX_HI_RATE_ENABLE)) |
		(tx_prio & (PORT_TX_LO_RATE_ENABLE | PORT_TX_HI_RATE_ENABLE));
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
	port_cfg(port, KS_PORT_CTRL_3_OFFSET,
		PORT_RX_LO_RATE_ENABLE | PORT_RX_HI_RATE_ENABLE, 0);
	port_cfg(port, KS_PORT_CTRL_2_OFFSET,
		PORT_TX_LO_RATE_ENABLE | PORT_TX_HI_RATE_ENABLE, 0);
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
	port_cfg(port, KS_PORT_CTRL_3_OFFSET,
		PORT_RX_LO_RATE_ENABLE | PORT_RX_HI_RATE_ENABLE, 1);
	port_cfg(port, KS_PORT_CTRL_2_OFFSET,
		PORT_TX_LO_RATE_ENABLE | PORT_TX_HI_RATE_ENABLE, 1);
}  /* sw_ena_prio_rate */

/**
 * sw_init_prio_rate - initialize switch prioirty rate
 * @sw:		The switch instance.
 *
 * This routine initializes the priority rate function of the switch.
 */
static void sw_init_prio_rate(struct ksz_sw *sw)
{
	int port;
	int prio;
	int rx_shift;
	int tx_shift;
	struct ksz_sw_info *info = sw->info;

	for (port = 0; port < TOTAL_PORT_NUM; port++) {
		rx_shift = PORT_RX_LO_RATE_SHIFT;
		tx_shift = PORT_TX_LO_RATE_SHIFT;
		for (prio = 0; prio < PRIO_QUEUES; prio++) {
			port_get_rate(port, KS_PORT_CTRL_3_OFFSET, rx_shift,
				&info->port_cfg[port].rx_rate[prio]);
			port_get_rate(port, KS_PORT_CTRL_2_OFFSET, tx_shift,
				&info->port_cfg[port].tx_rate[prio]);
			rx_shift += PORT_RATE_SHIFT;
			tx_shift += PORT_RATE_SHIFT;
		}
		port_cfg(port, KS_PORT_CTRL_3_OFFSET,
			PORT_RX_RATE_DIFFERENTIAL | PORT_TX_RATE_DIFFERENTIAL,
			1);
		sw_dis_prio_rate(sw, port);
	}
}  /* sw_init_prio_rate */
#endif

/* Communication */

#ifdef CONFIG_KS8695P
static inline void port_cfg_back_pressure(struct ksz_sw *sw, int p, int set)
{
	port_cfg(p, KS_PORT_CTRL_2_OFFSET, PORT_BACK_PRESSURE, set);
}

static inline void port_cfg_force_flow_ctrl(struct ksz_sw *sw, int p, int set)
{
	port_cfg(p, KS_PORT_CTRL_2_OFFSET, PORT_FORCE_FLOW_CTRL, set);
}

static inline int port_chk_back_pressure(struct ksz_sw *sw, int p)
{
	return port_chk(p, KS_PORT_CTRL_2_OFFSET, PORT_BACK_PRESSURE);
}

static inline int port_chk_force_flow_ctrl(struct ksz_sw *sw, int p)
{
	return port_chk(p, KS_PORT_CTRL_2_OFFSET, PORT_FORCE_FLOW_CTRL);
}
#endif

#ifdef CONFIG_KS8695X
static inline void port_cfg_back_pressure(struct ksz_sw *sw, int p, int set)
{}
static inline void port_cfg_force_flow_ctrl(struct ksz_sw *sw, int p, int set)
{}
#endif


/* Spanning Tree */

static inline void port_cfg_dis_learn(struct ksz_sw *sw, int p, int set)
{
	port_cfg(p, KS_PORT_CTRL_1_OFFSET, PORT_LEARN_DISABLE, set);
}

static inline void port_cfg_rx(struct ksz_sw *sw, int p, int set)
{
	port_cfg(p, KS_PORT_CTRL_1_OFFSET, PORT_RX_ENABLE, set);
}

static inline void port_cfg_tx(struct ksz_sw *sw, int p, int set)
{
	port_cfg(p, KS_PORT_CTRL_1_OFFSET, PORT_TX_ENABLE, set);
}

static inline int port_chk_dis_learn(struct ksz_sw *sw, int p)
{
	return port_chk(p, KS_PORT_CTRL_1_OFFSET, PORT_LEARN_DISABLE);
}

static inline int port_chk_rx(struct ksz_sw *sw, int p)
{
	return port_chk(p, KS_PORT_CTRL_1_OFFSET, PORT_RX_ENABLE);
}

static inline int port_chk_tx(struct ksz_sw *sw, int p)
{
	return port_chk(p, KS_PORT_CTRL_1_OFFSET, PORT_TX_ENABLE);
}

static inline void sw_cfg_fast_aging(struct ksz_sw *sw, int set)
{
	sw_cfg(KS_SWITCH_CTRL_0_OFFSET, SWITCH_FAST_AGING, set);
}

static inline void sw_flush_dyn_mac_table(struct ksz_sw *sw)
{
	if (!(sw->overrides & FAST_AGING)) {
		sw_cfg_fast_aging(sw, 1);
		udelay(800);
		sw_cfg_fast_aging(sw, 0);
	}
}

/* VLAN */

static inline void port_cfg_ins_tag(struct ksz_sw *sw, int p, int insert)
{
	port_cfg_shift(p,
		KS_SWITCH_ADVANCED_CTRL, PORT_INSERT_TAG_SHIFT, insert);
}

static inline void port_cfg_rmv_tag(struct ksz_sw *sw, int p, int remove)
{
	port_cfg_shift(p,
		KS_SWITCH_ADVANCED_CTRL, PORT_REMOVE_TAG_SHIFT, remove);
}

static inline int port_chk_ins_tag(struct ksz_sw *sw, int p)
{
	return port_chk_shift(p,
		KS_SWITCH_ADVANCED_CTRL, PORT_INSERT_TAG_SHIFT);
}

static inline int port_chk_rmv_tag(struct ksz_sw *sw, int p)
{
	return port_chk_shift(p,
		KS_SWITCH_ADVANCED_CTRL, PORT_REMOVE_TAG_SHIFT);
}

#ifdef CONFIG_KS8695P
static inline void port_cfg_dis_non_vid(struct ksz_sw *sw, int p, int set)
{
	port_cfg(p, KS_PORT_CTRL_2_OFFSET, PORT_DISCARD_NON_VID, set);
}

static inline void port_cfg_in_filter(struct ksz_sw *sw, int p, int set)
{
	port_cfg(p, KS_PORT_CTRL_2_OFFSET, PORT_INGRESS_VLAN_FILTER, set);
}

static inline int port_chk_dis_non_vid(struct ksz_sw *sw, int p)
{
	return port_chk(p, KS_PORT_CTRL_2_OFFSET, PORT_DISCARD_NON_VID);
}

static inline int port_chk_in_filter(struct ksz_sw *sw, int p)
{
	return port_chk(p, KS_PORT_CTRL_2_OFFSET, PORT_INGRESS_VLAN_FILTER);
}
#endif

/* Mirroring */

static inline void port_cfg_mirror_sniffer(struct ksz_sw *sw, int p, int set)
{
	port_cfg_shift(p,
		KS_SWITCH_ADVANCED_CTRL, PORT_MIRROR_SNIFFER_SHIFT, set);
}

static inline void port_cfg_mirror_rx(struct ksz_sw *sw, int p, int set)
{
	port_cfg_shift(p,
		KS_SWITCH_ADVANCED_CTRL, PORT_MIRROR_RX_SHIFT, set);
}

static inline void port_cfg_mirror_tx(struct ksz_sw *sw, int p, int set)
{
	port_cfg_shift(p,
		KS_SWITCH_ADVANCED_CTRL, PORT_MIRROR_TX_SHIFT, set);
}

static inline void sw_cfg_mirror_rx_tx(struct ksz_sw *sw, int set)
{
	sw_cfg(KS_SWITCH_ADVANCED_CTRL, SWITCH_MIRROR_RX_TX, set);
}

static inline int port_chk_mirror_sniffer(struct ksz_sw *sw, int p)
{
	return port_chk_shift(p,
		KS_SWITCH_ADVANCED_CTRL, PORT_MIRROR_SNIFFER_SHIFT);
}

static inline int port_chk_mirror_rx(struct ksz_sw *sw, int p)
{
	return port_chk_shift(p,
		KS_SWITCH_ADVANCED_CTRL, PORT_MIRROR_RX_SHIFT);
}

static inline int port_chk_mirror_tx(struct ksz_sw *sw, int p)
{
	return port_chk_shift(p,
		KS_SWITCH_ADVANCED_CTRL, PORT_MIRROR_TX_SHIFT);
}

static inline int sw_chk_mirror_rx_tx(struct ksz_sw *sw)
{
	return sw_chk(KS_SWITCH_ADVANCED_CTRL, SWITCH_MIRROR_RX_TX);
}

static void sw_setup_mirror(struct ksz_sw *sw)
{
	int port;

	for (port = 0; port < TOTAL_PORT_NUM; port++) {
		port_cfg_mirror_sniffer(sw, port, 0);
		port_cfg_mirror_rx(sw, port, 0);
		port_cfg_mirror_tx(sw, port, 0);
	}
	sw_cfg_mirror_rx_tx(sw, 0);
}  /* sw_setup_mirror */

/* Priority */

static inline void port_cfg_port_based(struct ksz_sw *sw, int p, int set)
{
	port_cfg(p, KS_PORT_CTRL_1_OFFSET, PORT_BASED_PRIORITY_ENABLE, set);
}

static inline void port_cfg_diffserv(struct ksz_sw *sw, int p, int set)
{
	port_cfg(p, KS_PORT_CTRL_1_OFFSET, PORT_DIFFSERV_ENABLE, set);
}

static inline void port_cfg_802_1p(struct ksz_sw *sw, int p, int set)
{
	port_cfg(p, KS_PORT_CTRL_1_OFFSET, PORT_802_1P_ENABLE, set);
}

static inline void port_cfg_prio(struct ksz_sw *sw, int p, int set)
{
	port_cfg(p, KS_PORT_CTRL_1_OFFSET, PORT_PRIO_QUEUE_ENABLE, set);
}

static inline int port_chk_port_based(struct ksz_sw *sw, int p)
{
	return port_chk(p, KS_PORT_CTRL_1_OFFSET, PORT_BASED_PRIORITY_ENABLE);
}

static inline int port_chk_diffserv(struct ksz_sw *sw, int p)
{
	return port_chk(p, KS_PORT_CTRL_1_OFFSET, PORT_DIFFSERV_ENABLE);
}

static inline int port_chk_802_1p(struct ksz_sw *sw, int p)
{
	return port_chk(p, KS_PORT_CTRL_1_OFFSET, PORT_802_1P_ENABLE);
}

static inline int port_chk_prio(struct ksz_sw *sw, int p)
{
	return port_chk(p, KS_PORT_CTRL_1_OFFSET, PORT_PRIO_QUEUE_ENABLE);
}

/* -------------------------------------------------------------------------- */

static void sw_set_lan_led(u32 led0, u32 led1)
{
	u32 reg;

	reg = KS_R(KS_SWITCH_CTRL_0_OFFSET);
	reg &= ~((LED_MODE_MASK << LED_LAN_LED1_MODE_SHIFT) |
		(LED_MODE_MASK << LED_LAN_LED0_MODE_SHIFT));
	reg |= (led1 << LED_LAN_LED1_MODE_SHIFT) |
		(led0 << LED_LAN_LED0_MODE_SHIFT);
	KS_W(KS_SWITCH_CTRL_0_OFFSET, reg);
}

static void sw_set_wan_led(u32 led0, u32 led1)
{
	u32 reg;

	reg = KS_R(KS_WAN_CONTROL);
	reg &= ~((LED_MODE_MASK << LED_WAN_LED1_MODE_SHIFT) |
		(LED_MODE_MASK << LED_WAN_LED0_MODE_SHIFT));
	reg |= (led1 << LED_WAN_LED1_MODE_SHIFT) |
		(led0 << LED_WAN_LED0_MODE_SHIFT);
	KS_W(KS_WAN_CONTROL, reg);
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
static void sw_set_tos_prio(u8 tos, u32 prio)
{
	int offset;

	if (tos < 1)
		offset = KS_TOS_PRIORITY_LO_OFFSET;
	else
		offset = KS_TOS_PRIORITY_HI_OFFSET;
	KS_WR(offset, prio);
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
 * DiffServ Value 0 ~ 63 is mapped to Priority Queue Number 0 ~ 1.
 * It is called by user functions.  The hardware should be acquired first.
 */
static void hw_cfg_tos_prio(struct ksz_sw *sw, u8 tos, u32 prio)
{
	int shift;
	u32 data = prio;
	u32 mask = KS_PRIORITY_MASK;

	if (tos >= DIFFSERV_ENTRIES)
		return;

	if (prio >= 0x10000)
		mask = 0xffffffff;
	else if (prio >= 0x100)
		mask = 0xffff;
	else if (prio >= 0x10)
		mask = 0xff;
	else if (prio > KS_PRIORITY_MASK)
		mask = 0xf;
	shift = (tos & (KS_PRIORITY_IN_REG - 1)) * KS_PRIORITY_SHIFT;
	prio = prio << shift;
	if (prio >> shift != data)
		return;
	mask <<= shift;
	tos /= KS_PRIORITY_IN_REG;

	sw->info->diffserv[tos] &= ~mask;
	sw->info->diffserv[tos] |= prio;

	sw_set_tos_prio(tos, sw->info->diffserv[tos]);
}  /* hw_cfg_tos_prio */

/* -------------------------------------------------------------------------- */

/**
 * sw_set_802_1p_prio - program switch 802.1p priority
 * @prio:	The 802.1p priority value, ranging from 0 to 7.
 *
 * This routine programs the 802.1p priority into the switch register.
 */
static void sw_set_802_1p_prio(u8 prio)
{
	u32 data;

	data = KS_R(KS_SWITCH_CTRL_0_OFFSET);
	data &= ~SWITCH_802_1P_MASK;
	data |= (u32) prio << SWITCH_802_1P_SHIFT;
	KS_WR(KS_SWITCH_CTRL_0_OFFSET, data);
}  /* sw_set_802_1p_prio */

/**
 * sw_init_802_1p - initialize 802.1p priority
 * @sw:		The switch instance.
 *
 * This helper routine initializes the 802.1p priority value from the switch.
 */
static void sw_init_802_1p(struct ksz_sw *sw)
{
	u32 data;

	data = KS_R(KS_SWITCH_CTRL_0_OFFSET);
	data &= ~SWITCH_802_1P_MASK;
	data >>= SWITCH_802_1P_SHIFT;

	sw->info->p_802_1p = (u8) data;
}  /* sw_init_802_1p */

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
 * @prio:	The 802.1p priority value, ranging from 0 to 7.
 *
 * This routine configures the 802.1p priority in the hardware.
 * 802.1p Tag priority value 0 ~ 7 is mapped to Priority Queue Number 0 ~ 1.
 * It is called by user functions.  The hardware should be acquired first.
 */
static void hw_cfg_802_1p_prio(struct ksz_sw *sw, u8 prio)
{
	if (prio > SWITCH_802_1P_BASE)
		return;

	sw->info->p_802_1p = prio;
	sw_set_802_1p_prio(prio);
}  /* hw_cfg_802_1p_prio */

#ifdef CONFIG_KS8695P
/**
 * sw_cfg_replace_null_vid -
 * @sw:		The switch instance.
 * @set:	The flag to disable or enable.
 *
 */
static void sw_cfg_replace_null_vid(struct ksz_sw *sw, int set)
{
	sw_cfg(KS_SWITCH_CTRL_1_OFFSET, P_SWITCH_REPLACE_NULL_VID, set);
}  /* sw_cfg_replace_null_vid */
#endif

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
	if (prio > KS_PRIORITY_MASK)
		prio = KS_PRIORITY_MASK;

	sw->info->port_cfg[port].port_prio = prio;
	port_cfg_port_based(sw, port, prio);
}  /* sw_cfg_port_based */

/* -------------------------------------------------------------------------- */

/**
 * sw_dis_multi_queue - disable transmit multiple queues
 * @sw:		The switch instance.
 * @port:	The port index.
 *
 * This routine disables the transmit multiple queues selection of the switch
 * port.  Only single transmit queue on the port.
 */
static void sw_dis_multi_queue(struct ksz_sw *sw, int port)
{
	port_cfg_prio(sw, port, 0);
}  /* sw_dis_multi_queue */

/**
 * sw_ena_multi_queue - enable transmit multiple queues
 * @sw:		The switch instance.
 * @port:	The port index.
 *
 * This routine enables the transmit multiple queues selection of the switch
 * port.  The port transmit queue is split into four priority queues.
 */
static void sw_ena_multi_queue(struct ksz_sw *sw, int port)
{
	port_cfg_prio(sw, port, 1);
}  /* sw_ena_multi_queue */

/* -------------------------------------------------------------------------- */

/**
 * sw_init_prio - initialize switch priority
 * @sw:		The switch instance.
 *
 * This routine initializes the switch QoS priority functions.
 */
static void sw_init_prio(struct ksz_sw *sw)
{
	int port;

	sw_init_802_1p(sw);

	sw->info->diffserv[0] = KS_R(KS_TOS_PRIORITY_LO_OFFSET);
	sw->info->diffserv[1] = KS_R(KS_TOS_PRIORITY_HI_OFFSET);

	for (port = 0; port < TOTAL_PORT_NUM; port++)
		sw->info->port_cfg[port].port_prio = port_chk(port,
			KS_PORT_CTRL_1_OFFSET, PORT_BASED_PRIORITY_ENABLE);
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
		sw_dis_multi_queue(sw, port);
		sw_dis_diffserv(sw, port);
		sw_dis_802_1p(sw, port);
		port_cfg_port_based(sw, port,
			sw->info->port_cfg[port].port_prio);
	}
#ifdef CONFIG_KS8695P
	sw_cfg_replace_null_vid(sw, 0);
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
static void port_cfg_def_vid(struct ksz_sw *sw, int port, u16 vid)
{
	u32 addr;
	u32 data;

	PORT_CTRL_ADDR(port, addr);
	addr += KS_PORT_CTRL_1_OFFSET;

	data = KS_R(addr);
	data &= ~PORT_DEFAULT_VID;
	data |= (u32) vid << PORT_DEFAULT_VID_SHIFT;
	KS_WR(addr, data);
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
	u32 addr;
	u32 data;

	PORT_CTRL_ADDR(port, addr);
	addr += KS_PORT_CTRL_1_OFFSET;

	data = KS_R(addr);

	*vid = (u16)(data >> PORT_DEFAULT_VID_SHIFT);
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
 * sw_init_port_base_vlan - initialize port-based VLAN membership
 * @sw:		The switch instance.
 * @port:	The port index.
 *
 * This routine initializes the port-based VLAN membership of the port.
 */
static void sw_init_port_base_vlan(struct ksz_sw *sw, int port)
{
	u32 addr;
	u32 data;

	PORT_CTRL_ADDR(port, addr);
	addr += KS_PORT_CTRL_1_OFFSET;

	data = KS_R(addr);
	data &= PORT_VLAN_MEMBERSHIP;
	data >>= PORT_VLAN_MEMBERSHIP_SHIFT;

	sw->info->port_cfg[port].member = (u8) data;
}  /* sw_init_port_base_vlan */

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
	u32 addr;
	u32 data;

	PORT_CTRL_ADDR(port, addr);
	addr += KS_PORT_CTRL_1_OFFSET;

	data = KS_R(addr);
	data &= ~PORT_VLAN_MEMBERSHIP;
	data |= (u32)(member & PORT_MASK) << PORT_VLAN_MEMBERSHIP_SHIFT;
	KS_WR(addr, data);

	sw->info->port_cfg[port].member = member;
}  /* sw_cfg_port_base_vlan */

#ifdef CONFIG_KS8695P
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
#endif

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

#ifdef CONFIG_KS8695P
/**
 * sw_dis_vlan - disable switch VLAN
 * @sw:		The switch instance.
 *
 * This routine disables the VLAN function of the switch.
 */
static void sw_dis_vlan(struct ksz_sw *sw)
{
	sw_cfg(KS_SWITCH_CTRL_1_OFFSET, P_SWITCH_VLAN_ENABLE, 0);
}  /* sw_dis_vlan */

/**
 * sw_ena_vlan - enable switch VLAN
 * @sw:		The switch instance.
 *
 * This routine enables the VLAN function of the switch.
 */
static void sw_ena_vlan(struct ksz_sw *sw)
{
	int entry;
	struct ksz_sw_info *info = sw->info;

	/* Create 16 VLAN entries in the VLAN table. */
	for (entry = 0; entry < VLAN_TABLE_ENTRIES; entry++) {
		sw_w_vlan_table(sw, entry,
			info->vlan_table[entry].vid,
			info->vlan_table[entry].fid,
			info->vlan_table[entry].member,
			info->vlan_table[entry].valid);
	}

	/* Enable 802.1q VLAN mode. */
	sw_cfg(KS_SWITCH_CTRL_0_OFFSET, UNICAST_VLAN_BOUNDARY, 1);
	sw_cfg(KS_SWITCH_CTRL_1_OFFSET, P_SWITCH_VLAN_ENABLE, 1);
}  /* sw_ena_vlan */
#endif

/**
 * sw_init_vlan - initialize switch VLAN
 * @sw:		The switch instance.
 *
 * This routine initializes the VLAN function of the switch.
 */
static void sw_init_vlan(struct ksz_sw *sw)
{
	int port;
	struct ksz_sw_info *info = sw->info;

#ifdef CONFIG_KS8695P
	int entry;

	/* Read 16 VLAN entries from device's VLAN table. */
	for (entry = 0; entry < VLAN_TABLE_ENTRIES; entry++) {
		if (!sw_r_vlan_table(sw, entry,
				&info->vlan_table[entry].vid,
				&info->vlan_table[entry].fid,
				&info->vlan_table[entry].member))
			info->vlan_table[entry].valid = 1;
		else
			info->vlan_table[entry].valid = 0;
	}
#endif

	for (port = 0; port < TOTAL_PORT_NUM; port++) {
		port_get_def_vid(sw, port, &info->port_cfg[port].vid);
		sw_init_port_base_vlan(sw, port);
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
	int i;

	for (i = 0; i < 4; i++)
		mac_addr[MAC_ADDR_ORDER(i)] = KS_R8(KS_SWITCH_MAC_ADDR_LO + i);
	for (i = 0; i < 2; i++)
		mac_addr[MAC_ADDR_ORDER(4 + i)] =
			KS_R8(KS_SWITCH_MAC_ADDR_HI + i);
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
	int i;
	u32 mac_addr_lo;
	u32 mac_addr_hi;

	mac_addr_hi = 0;
	for (i = 0; i < 2; i++) {
		mac_addr_hi <<= 8;
		mac_addr_hi |= mac_addr[i];
	}
	mac_addr_lo = 0;
	for (i = 2; i < 6; i++) {
		mac_addr_lo <<= 8;
		mac_addr_lo |= mac_addr[i];
	}

	KS_W(KS_SWITCH_MAC_ADDR_LO, mac_addr_lo);
	KS_W(KS_SWITCH_MAC_ADDR_HI, mac_addr_hi);
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
	u32 data;

	data = KS_R(KS_SWITCH_CTRL_0_OFFSET);

	/* Enable switch MII flow control. */
	data |= SWITCH_FLOW_CTRL;

	/* Enable aggressive back off algorithm in half duplex mode. */
	data |= SWITCH_AGGR_BACKOFF;

	/* Enable automatic fast aging when link changed detected. */
	data |= SWITCH_AGING_ENABLE;
	data |= SWITCH_LINK_AUTO_AGING;

	if (sw->overrides & FAST_AGING)
		data |= SWITCH_FAST_AGING;
	else
		data &= ~SWITCH_FAST_AGING;

	/* Make sure unicast VLAN boundary is set as default. */
	if (sw->dev_count > 1)
		data |= UNICAST_VLAN_BOUNDARY;

	/* Enable no excessive collision drop. */
	data |= NO_EXC_COLLISION_DROP;
	KS_WR(KS_SWITCH_CTRL_0_OFFSET, data);
}  /* sw_set_global_ctrl */

/* -------------------------------------------------------------------------- */

enum {
	STP_STATE_DISABLED = 0,
	STP_STATE_LISTENING,
	STP_STATE_LEARNING,
	STP_STATE_FORWARDING,
	STP_STATE_BLOCKED,
	STP_STATE_SIMPLE
};

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
	u32 data;

	port_r(port, KS_PORT_CTRL_1_OFFSET, &data);
	switch (state) {
	case STP_STATE_DISABLED:
		data &= ~(PORT_TX_ENABLE | PORT_RX_ENABLE);
		data |= PORT_LEARN_DISABLE;
		break;
	case STP_STATE_LISTENING:
/*
 * No need to turn on transmit because of port direct mode.
 * Turning on receive is required if static MAC table is not setup.
 */
		data &= ~PORT_TX_ENABLE;
		data |= PORT_RX_ENABLE;
		data |= PORT_LEARN_DISABLE;
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
		break;
	case STP_STATE_SIMPLE:
		data |= (PORT_TX_ENABLE | PORT_RX_ENABLE);
		data |= PORT_LEARN_DISABLE;
		break;
	}
	port_w(port, KS_PORT_CTRL_1_OFFSET, data);
	sw->info->port_cfg[port].stp_state = state;
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
	struct ksz_mac_table *entry;
	int i;

	for (i = 0; i < STATIC_MAC_TABLE_ENTRIES; i++) {
		entry = &sw->info->mac_table[i];
		sw_w_sta_mac_table(sw, i,
			entry->mac_addr, entry->ports,
			0, 0,
			entry->use_fid, entry->fid);
	}
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

	entry = &sw->info->mac_table[STP_ENTRY];
	entry->mac_addr[0] = 0x01;
	entry->mac_addr[1] = 0x80;
	entry->mac_addr[2] = 0xC2;
	entry->mac_addr[3] = 0x00;
	entry->mac_addr[4] = 0x00;
	entry->mac_addr[5] = 0x00;
	entry->ports = HOST_MASK;
	entry->override = 1;
	entry->valid = 1;
	sw_w_sta_mac_table(sw, STP_ENTRY,
		entry->mac_addr, entry->ports,
		entry->override, entry->valid,
		entry->use_fid, entry->fid);
}  /* sw_init_stp */

/**
 * sw_block_addr - block certain packets from the host port
 * @sw:		The switch instance.
 *
 * This routine blocks certain packets from reaching to the host port.
 */
static void sw_block_addr(struct ksz_sw *sw)
{
	struct ksz_mac_table *entry;
	int i;

	for (i = BROADCAST_ENTRY; i <= IPV6_ADDR_ENTRY; i++) {
		entry = &sw->info->mac_table[i];
		entry->valid = 0;
		sw_w_sta_mac_table(sw, i,
			entry->mac_addr, entry->ports,
			0, entry->valid,
			entry->use_fid, entry->fid);
	}
}  /* sw_block_addr */

#ifdef CONFIG_KSZ8695_STP
/**
 * sw_pass_addr - allow certain packets to the host port
 * @sw:		The switch instance.
 *
 * This routine allows certain packets to reach the host port.
 */
static void sw_pass_addr(struct ksz_sw *sw)
{
	struct ksz_mac_table *entry;
	int i;
	struct ksz_sw_info *info = sw->info;

	for (i = BROADCAST_ENTRY; i <= IPV6_ADDR_ENTRY; i++) {
		entry = &sw->info->mac_table[i];
		switch (i) {
		case BROADCAST_ENTRY:
			memset(entry->mac_addr, 0xFF, MAC_ADDR_LEN);
			break;
		case BRIDGE_ADDR_ENTRY:
			memcpy(entry->mac_addr, info->br_addr, MAC_ADDR_LEN);
			break;
		case IPV6_ADDR_ENTRY:
			memcpy(entry->mac_addr, info->br_addr, MAC_ADDR_LEN);
			entry->mac_addr[0] = 0x33;
			entry->mac_addr[1] = 0x33;
			entry->mac_addr[2] = 0xFF;
			break;
		}
		entry->ports = HOST_MASK;
		entry->override = 1;
		entry->valid = 1;
		sw_w_sta_mac_table(sw, i,
			entry->mac_addr, entry->ports,
			entry->override, entry->valid,
			entry->use_fid, entry->fid);
	}
}  /* sw_pass_addr */
#endif

/* -------------------------------------------------------------------------- */

/**
 * port_r_phy - read data from PHY register
 * @hw:		The hardware instance.
 * @port:	Port to read.
 * @reg:	PHY register to read.
 * @val:	Buffer to store the read data.
 *
 * This routine reads data from the PHY register.
 */
void port_r_phy(struct ksz_port *port, u16 reg, u16 *val)
{
	u32 force_data;
	u16 link_status;
	u16 phy_data;
	u16 data = 0;

	force_data = KS_R(port->linked->force_reg);
	link_status = KS_R16(port->linked->link_reg);
	phy_data = KS_R16(port->linked->phy_reg);
	if (phy_data & PORT_POWER_DOWN) {
		force_data |= PORT_AUTO_NEG_DISABLE;
		link_status &= ~PORT_STATUS_LINK_GOOD;
	}
	switch (reg) {
	case PHY_REG_CTRL:
		if (!(force_data & PORT_AUTO_NEG_DISABLE))
			data |= PHY_AUTO_NEG_ENABLE;
		if (force_data & PORT_FORCE_100_MBIT)
			data |= PHY_SPEED_100MBIT;
		if (force_data & PORT_FORCE_FULL_DUPLEX)
			data |= PHY_FULL_DUPLEX;
		break;
	case PHY_REG_STATUS:
		data = PHY_100BTX_FD_CAPABLE |
			PHY_100BTX_CAPABLE |
			PHY_10BT_FD_CAPABLE |
			PHY_10BT_CAPABLE |
			PHY_AUTO_NEG_CAPABLE;
		if (link_status & PORT_AUTO_NEG_COMPLETE)
			data |= PHY_AUTO_NEG_ACKNOWLEDGE;
		if (link_status & PORT_STATUS_LINK_GOOD)
			data |= PHY_LINK_STATUS;
		break;
	case PHY_REG_ID_1:
		break;
	case PHY_REG_ID_2:
		break;
	case PHY_REG_AUTO_NEGOTIATION:
		data = PHY_AUTO_NEG_802_3;
		if (link_status & PORT_AUTO_NEG_SYM_PAUSE)
			data |= PHY_AUTO_NEG_SYM_PAUSE;
		if (link_status & PORT_AUTO_NEG_100BTX_FD)
			data |= PHY_AUTO_NEG_100BTX_FD;
		if (link_status & PORT_AUTO_NEG_100BTX)
			data |= PHY_AUTO_NEG_100BTX;
		if (link_status & PORT_AUTO_NEG_10BT_FD)
			data |= PHY_AUTO_NEG_10BT_FD;
		if (link_status & PORT_AUTO_NEG_10BT)
			data |= PHY_AUTO_NEG_10BT;
		break;
	case PHY_REG_REMOTE_CAPABILITY:
		data = PHY_AUTO_NEG_802_3;
		if (link_status & PORT_REMOTE_SYM_PAUSE)
			data |= PHY_AUTO_NEG_SYM_PAUSE;
		if (link_status & PORT_REMOTE_100BTX_FD)
			data |= PHY_AUTO_NEG_100BTX_FD;
		if (link_status & PORT_REMOTE_100BTX)
			data |= PHY_AUTO_NEG_100BTX;
		if (link_status & PORT_REMOTE_10BT_FD)
			data |= PHY_AUTO_NEG_10BT_FD;
		if (link_status & PORT_REMOTE_10BT)
			data |= PHY_AUTO_NEG_10BT;
		break;
	default:
		break;
	}
	*val = data;
}  /* port_r_phy */

/**
 * port_w_phy - write data to PHY register
 * @hw:		The hardware instance.
 * @port:	Port to write.
 * @reg:	PHY register to write.
 * @val:	Word data to write.
 *
 * This routine writes data to the PHY register.
 */
void port_w_phy(struct ksz_port *port, u16 reg, u16 val)
{
	struct ksz_port_info *info;
	struct ksz_sw *sw = port->sw;
	u32 force_data;
	u16 data = 0;
	u16 phy_data;
	int i;
	int p;

	for (i = 0, p = port->first_port; i < port->port_cnt; i++, p++) {
		info = &sw->port_info[p];
		force_data = KS_R(info->force_reg);
		data = KS_R16(info->link_reg);
		phy_data = KS_R16(info->phy_reg);

		switch (reg) {
		case PHY_REG_CTRL:
			if (!(val & PHY_AUTO_NEG_ENABLE))
				force_data |= PORT_AUTO_NEG_DISABLE;
			else
				force_data &= ~PORT_AUTO_NEG_DISABLE;
			if (val & PHY_SPEED_100MBIT)
				force_data |= PORT_FORCE_100_MBIT;
			else
				force_data &= ~PORT_FORCE_100_MBIT;
			if (val & PHY_FULL_DUPLEX)
				force_data |= PORT_FORCE_FULL_DUPLEX;
			else
				force_data &= ~PORT_FORCE_FULL_DUPLEX;
			KS_W(info->force_reg, force_data);
			if (val & PHY_AUTO_NEG_RESTART)
				data |= PORT_AUTO_NEG_RESTART;
			else
				data &= ~(PORT_AUTO_NEG_RESTART);
			if (val & PHY_POWER_DOWN) {
				if (!(phy_data & PORT_POWER_DOWN)) {
					phy_data |= PORT_POWER_DOWN;
					KS_W16(info->phy_reg, phy_data);
				}
			} else {
				if (phy_data & PORT_POWER_DOWN) {
					phy_data &= ~PORT_POWER_DOWN;
					KS_W16(info->phy_reg, phy_data);
				}
			}
			break;
		case PHY_REG_AUTO_NEGOTIATION:
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
			break;
		case PHY_REG_REMOTE_CAPABILITY:
			data &= ~(PORT_REMOTE_SYM_PAUSE |
				PORT_REMOTE_100BTX_FD |
				PORT_REMOTE_100BTX |
				PORT_REMOTE_10BT_FD |
				PORT_REMOTE_10BT);
			if (val & PHY_AUTO_NEG_SYM_PAUSE)
				data |= PORT_REMOTE_SYM_PAUSE;
			if (val & PHY_AUTO_NEG_100BTX_FD)
				data |= PORT_REMOTE_100BTX_FD;
			if (val & PHY_AUTO_NEG_100BTX)
				data |= PORT_REMOTE_100BTX;
			if (val & PHY_AUTO_NEG_10BT_FD)
				data |= PORT_REMOTE_10BT_FD;
			if (val & PHY_AUTO_NEG_10BT)
				data |= PORT_REMOTE_10BT;
			break;
		default:
			data = 0;
			break;
		}
		if (data)
			KS_W16(info->link_reg, data);
	}
}  /* port_w_phy */

void port_set_led(int port, int set)
{
#ifdef CONFIG_KS8695P
	uint data;
	int  shift = 0;

	data = KS_R(KS8695_GPIO_DATA);
	if (set)
		data &= ~(1 << (port + 3 + shift));
	else
		data |= (1 << (port + 3 + shift));
	KS_W(KS8695_GPIO_DATA, data);
#endif
}  /* port_set_led */

static inline void setup_wan_port_regs(struct ksz_sw *sw)
{
	sw->port_info[0].force_reg = KS_WAN_CONTROL;
	sw->port_info[0].link_reg = KS_PORT_0_AUTO_NEG_OFFSET;
	sw->port_info[0].phy_reg = KS_PORT_0_PHY_CTRL_OFFSET;
}  /* setup_wan_port_regs */

static inline void setup_lan_port_regs(struct ksz_sw *sw)
{
	sw->port_info[0].force_reg = KS_PORT_1_CTRL_1_OFFSET;
	sw->port_info[1].force_reg = KS_PORT_2_CTRL_1_OFFSET;
	sw->port_info[2].force_reg = KS_PORT_3_CTRL_1_OFFSET;
	sw->port_info[3].force_reg = KS_PORT_4_CTRL_1_OFFSET;
	sw->port_info[0].link_reg = KS_PORT_1_AUTO_NEG_OFFSET;
	sw->port_info[1].link_reg = KS_PORT_2_AUTO_NEG_OFFSET;
	sw->port_info[2].link_reg = KS_PORT_3_AUTO_NEG_OFFSET;
	sw->port_info[3].link_reg = KS_PORT_4_AUTO_NEG_OFFSET;
	sw->port_info[0].phy_reg = KS_PORT_1_PHY_CTRL_OFFSET;
	sw->port_info[1].phy_reg = KS_PORT_2_PHY_CTRL_OFFSET;
	sw->port_info[2].phy_reg = KS_PORT_3_PHY_CTRL_OFFSET;
	sw->port_info[3].phy_reg = KS_PORT_4_PHY_CTRL_OFFSET;
}  /* setup_lan_port_regs */

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
}  /* dbp_link */

static u16 advertised_flow_ctrl(struct ksz_port *port, u16 ctrl)
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
}  /* advertise_flow_ctrl */

static void set_flow_ctrl(struct ksz_hw *hw, int rx, int tx)
{
	u32 rx_cfg;
	u32 tx_cfg;

	rx_cfg = hw->rx_cfg;
	tx_cfg = hw->tx_cfg;
	if (rx)
		hw->rx_cfg |= DMA_RX_FLOW_ENABLE;
	else
		hw->rx_cfg &= ~DMA_RX_FLOW_ENABLE;
	if (tx)
		hw->tx_cfg |= DMA_TX_FLOW_ENABLE;
	else
		hw->tx_cfg &= ~DMA_TX_FLOW_ENABLE;
	if (hw->enabled) {
		if (rx_cfg != hw->rx_cfg)
			writel(hw->rx_cfg, hw->io + KS_DMA_RX_CTRL);
		if (tx_cfg != hw->tx_cfg)
			writel(hw->tx_cfg, hw->io + KS_DMA_TX_CTRL);
	}
}  /* set_flow_ctrl */

static void determine_flow_ctrl(struct ksz_sw *sw, struct ksz_port *port,
	u16 status)
{
	int rx;
	int tx;

	if (sw->overrides & PAUSE_FLOW_CTRL)
		return;

	rx = tx = 0;
	if (port->force_link)
		rx = tx = 1;
	if (status & PORT_REMOTE_SYM_PAUSE) {
		if (status & PORT_AUTO_NEG_SYM_PAUSE)
			rx = tx = 1;
	}
	if (!sw->info)
		set_flow_ctrl(port->hw, rx, tx);
	dbg_msg("pause: %d, %d; %04x\n", rx, tx, status);
}  /* determine_flow_ctrl */

static inline void port_cfg_change(struct ksz_hw *hw, struct ksz_port *port,
	struct ksz_port_info *info, u16 link_status)
{
	if ((hw->features & HALF_DUPLEX_SIGNAL_BUG) &&
			!(port->sw->overrides & PAUSE_FLOW_CTRL)) {
		u32 cfg = hw->tx_cfg;

		/* Disable flow control in the half duplex mode. */
		if (1 == info->duplex)
			hw->tx_cfg &= ~DMA_TX_FLOW_ENABLE;
		if (hw->enabled && cfg != hw->tx_cfg)
			writel(hw->tx_cfg, hw->io + KS_DMA_TX_CTRL);
	}

	/* The auto-negotiation restart bit does not clear automatically. */
	if (link_status & PORT_AUTO_NEG_RESTART) {
		link_status &= ~PORT_AUTO_NEG_RESTART;
		KS_W16(info->link_reg, link_status);
	}
}  /* port_cfg_change */

/**
 * port_get_link_speed - get current link status
 * @port:	The port instance.
 *
 * This routine reads PHY registers to determine the current link status of the
 * switch ports.
 */
static void port_get_link_speed(struct ksz_port *port)
{
	struct ksz_port_info *info;
	struct ksz_port_info *linked = NULL;
	struct ksz_sw *sw = port->sw;
	u16 status;
	int i;
	int p;
	int change = 0;

	for (i = 0, p = port->first_port; i < port->port_cnt; i++, p++) {
		info = &sw->port_info[p];
		status = KS_R16(info->link_reg);
		if (status & PORT_STATUS_LINK_GOOD) {

			/* Remember the first linked port. */
			if (!linked)
				linked = info;

			info->tx_rate = 10 * TX_RATE_UNIT;
			if (status & PORT_STATUS_SPEED_100MBIT)
				info->tx_rate = 100 * TX_RATE_UNIT;

			info->duplex = 1;
			if (status & PORT_STATUS_FULL_DUPLEX)
				info->duplex = 2;

			if (media_connected != info->state) {
				determine_flow_ctrl(sw, port, status);
				if (sw->info)
					port_cfg_back_pressure(sw, p,
						(1 == info->duplex));
				change |= 1 << i;
				port_set_led(i + port->first_port + sw->id, 1);
				port_cfg_change(port->hw, port, info, status);
			}
			info->state = media_connected;
		} else {
			if (media_disconnected != info->state) {
				change |= 1 << i;
				port_set_led(i + port->first_port + sw->id, 0);

				/* Indicate the link just goes down. */
				info->link_down = 1;
			}
			info->state = media_disconnected;
		}
	}

	if (linked && media_disconnected == port->linked->state)
		port->linked = linked;

#ifdef DEBUG
	if (change)
		dbp_link(port, sw, change);
#endif
}  /* port_get_link_speed */

/**
 * port_set_link_speed - set port speed
 * @port:	The port instance.
 *
 * This routine sets the link speed of the switch ports.
 */
static void port_set_link_speed(struct ksz_port *port)
{
	struct ksz_port_info *info;
	struct ksz_sw *sw = port->sw;
	uint reg_data;
	u16 data;
	u16 cfg;
	int i;
	int p;
	int port_reg;

	for (i = 0, p = port->first_port; i < port->port_cnt; i++, p++) {
		info = &sw->port_info[p];
		reg_data = KS_R(info->force_reg);
		if (reg_data & PORT_AUTO_NEG_DISABLE) {
			reg_data &= ~PORT_AUTO_NEG_DISABLE;
			KS_W(info->force_reg, reg_data);
		}
		port_reg = info->link_reg;
		data = KS_R16(port_reg);

		cfg = 0;
		if (data & PORT_STATUS_LINK_GOOD)
			cfg = data;

		data = advertised_flow_ctrl(port, data);

		data |= PORT_AUTO_NEG_100BTX_FD | PORT_AUTO_NEG_100BTX |
			PORT_AUTO_NEG_10BT_FD | PORT_AUTO_NEG_10BT;

		/* Check if manual configuration is specified by the user. */
		if (port->speed || port->duplex) {
			if (10 == port->speed)
				data &= ~(PORT_AUTO_NEG_100BTX_FD |
					PORT_AUTO_NEG_100BTX);
			else if (100 == port->speed)
				data &= ~(PORT_AUTO_NEG_10BT_FD |
					PORT_AUTO_NEG_10BT);
			if (1 == port->duplex)
				data &= ~(PORT_AUTO_NEG_100BTX_FD |
					PORT_AUTO_NEG_10BT_FD);
			else if (2 == port->duplex)
				data &= ~(PORT_AUTO_NEG_100BTX |
					PORT_AUTO_NEG_10BT);
		}
		if (data != cfg) {
			data |= PORT_AUTO_NEG_RESTART;
			KS_W16(port_reg, data);
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
	struct ksz_port_info *info;
	struct ksz_sw *sw = port->sw;
	u32 data;
	int i;
	int p;

	for (i = 0, p = port->first_port; i < port->port_cnt; i++, p++) {
		info = &sw->port_info[p];
		data = KS_R(info->force_reg);

		data |= PORT_AUTO_NEG_DISABLE |
			PORT_FORCE_100_MBIT |
			PORT_FORCE_FULL_DUPLEX;
		if (10 == port->speed)
			data &= ~PORT_FORCE_100_MBIT;
		if (1 == port->duplex)
			data &= ~PORT_FORCE_FULL_DUPLEX;
		KS_W(info->force_reg, data);
	}
}  /* port_force_link_speed */

static void port_set_power_saving(struct ksz_port *port, int enable)
{
	int i;
	int p;
	u16 data;
	struct ksz_sw *sw = port->sw;

	for (i = 0, p = port->first_port; i < port->port_cnt; i++, p++) {
		data = KS_R16(sw->port_info[p].phy_reg);
		if (enable)
			data |= PORT_POWER_DOWN;
		else
			data &= ~PORT_POWER_DOWN;
		KS_W16(sw->port_info[p].phy_reg, data);
	}
}  /* port_set_power_saving */

/* -------------------------------------------------------------------------- */

/**
 * hw_init - check driver is correct for the hardware
 * @hw:		The hardware instance.
 *
 * This function checks the hardware is correct for this driver and sets the
 * hardware up for proper initialization.
 *
 * Return number of ports or 0 if not right.
 */
static int hw_init(struct ksz_hw *hw)
{
	u32 data;
	u32 id;
	int rev;
	int subid;
	struct dev_info *hw_priv = container_of(hw, struct dev_info, hw);
	struct ksz_sw *sw = &hw_priv->sw;

	id = KS_R(KS_DEVICE_ID);
	data = KS_R(KS_REVISION_ID);
	subid = (data & (0xF << 4)) >> 4;
	rev = data & 0xF;
	dbg_msg("%08X %02X %02X\n", id, subid, rev);

	/* Setup hardware features or bug workarounds. */
	if (rev <= 2) {
		hw->features |= SMALL_PACKET_TX_BUG;
		if (0 == sw->id)
			hw->features |= HALF_DUPLEX_SIGNAL_BUG;
		hw->features |= RX_OVERRUN_BUG;
	}
	hw->features |= IPV6_CSUM_GEN_HACK;
	hw->features |= IP_HEADER_ALIGN;

#ifdef DEBUG_VERIFY
	hw->overrides |= DATA_HEADER;
#endif

#ifdef CONFIG_KS8695P
	if (sw->info) {
		data = KS_R(KS8695_GPIO_MODE);
		data |= 0xf << 4;
		KS_W(KS8695_GPIO_MODE, data);
	} else {
		data = KS_R(KS8695_GPIO_MODE);
		data |= 0x1 << 3;
		KS_W(KS8695_GPIO_MODE, data);

		data = KS_R(KS_WAN_CONTROL);
		data &= ~(LED_MODE_MASK << LED_WAN_LED0_MODE_SHIFT);
		data |= LED_LINK_ACTIVITIES << LED_WAN_LED0_MODE_SHIFT;
		KS_W(KS_WAN_CONTROL, data);
	}
#endif

	return SWITCH_PORT_NUM;
}  /* hw_init */

static int empty_addr(u8 *addr)
{
	u32 *addr1 = (u32 *) addr;
	u16 *addr2 = (u16 *) &addr[4];

	return 0 == *addr1 && 0 == *addr2;
}  /* empty_addr */

static void hw_ena_add_addr(struct ksz_hw *hw, int index, u8 *mac_addr)
{
	int i;
	u32 mac_addr_lo;
	u32 mac_addr_hi;

	mac_addr_hi = 0;
	for (i = 0; i < 2; i++) {
		mac_addr_hi <<= 8;
		mac_addr_hi |= mac_addr[i];
	}
	mac_addr_hi |= ADD_ADDR_ENABLE;
	mac_addr_lo = 0;
	for (i = 2; i < 6; i++) {
		mac_addr_lo <<= 8;
		mac_addr_lo |= mac_addr[i];
	}
	index *= ADD_ADDR_INCR;

	writel(mac_addr_lo, hw->io + index + KS_ADD_ADDR_0_LO);
	writel(mac_addr_hi, hw->io + index + KS_ADD_ADDR_0_HI);
}  /* hw_ena_add_addr */

static void hw_set_add_addr(struct ksz_hw *hw)
{
	int i;

	for (i = 0; i < ADDITIONAL_ENTRIES; i++) {
		if (empty_addr(hw->address[i]))
			writel(0, hw->io + ADD_ADDR_INCR * i +
				KS_ADD_ADDR_0_HI);
		else
			hw_ena_add_addr(hw, i, hw->address[i]);
	}
}  /* hw_set_add_addr */

static int hw_add_addr(struct ksz_hw *hw, u8 *mac_addr)
{
	int i;
	int j = ADDITIONAL_ENTRIES;

	if (!memcmp(hw->override_addr, mac_addr, MAC_ADDR_LEN))
		return 0;
	for (i = 0; i < hw->addr_list_size; i++) {
		if (!memcmp(hw->address[i], mac_addr, MAC_ADDR_LEN))
			return 0;
		if (ADDITIONAL_ENTRIES == j && empty_addr(hw->address[i]))
			j = i;
	}
	if (j < ADDITIONAL_ENTRIES) {
		memcpy(hw->address[j], mac_addr, MAC_ADDR_LEN);
		hw_ena_add_addr(hw, j, hw->address[j]);
		return 0;
	}
	return -1;
}  /* hw_add_addr */

static int hw_del_addr(struct ksz_hw *hw, u8 *mac_addr)
{
	int i;

	for (i = 0; i < hw->addr_list_size; i++) {
		if (!memcmp(hw->address[i], mac_addr, MAC_ADDR_LEN)) {
			memset(hw->address[i], 0, MAC_ADDR_LEN);
			writel(0, hw->io + ADD_ADDR_INCR * i +
				KS_ADD_ADDR_0_HI);
			return 0;
		}
	}
	return -1;
}  /* hw_del_addr */

/**
 * hw_set_addr - set MAC address
 * @hw:		The hardware instance.
 *
 * This routine programs the MAC address of the hardware when the address is
 * overridden.
 */
static void hw_set_addr(struct ksz_hw *hw)
{
	int i;
	struct dev_info *hw_priv = container_of(hw, struct dev_info, hw);
	struct ksz_sw *sw = &hw_priv->sw;

	for (i = 0; i < MAC_ADDR_LEN; i++)
		writeb(hw->override_addr[MAC_ADDR_ORDER(i)],
			hw->io + KS_DMA_MAC_ADDR_LO + i);

	dbg_msg("set addr: ");
	dbp_mac_addr(hw->override_addr);
	dbg_msg("\n");

	if (sw->info)
		sw_set_addr(sw, hw->override_addr);
}  /* hw_set_addr */

/**
 * hw_read_addr - read MAC address
 * @hw:		The hardware instance.
 *
 * This routine retrieves the MAC address of the hardware.
 */
static void hw_read_addr(struct ksz_hw *hw)
{
	int i;

	for (i = 0; i < MAC_ADDR_LEN; i++)
		hw->perm_addr[MAC_ADDR_ORDER(i)] = readb(hw->io +
			KS_DMA_MAC_ADDR_LO + i);

	dbg_msg("get addr: ");
	dbp_mac_addr(hw->perm_addr);
	dbg_msg("\n");

	if (!hw->mac_override) {
		memcpy(hw->override_addr, hw->perm_addr, MAC_ADDR_LEN);
#ifdef SET_MAC_ADDR
		memset(hw->override_addr, 0, MAC_ADDR_LEN);
#endif
		if (empty_addr(hw->override_addr)) {
			struct dev_info *hw_priv =
				container_of(hw, struct dev_info, hw);

			memcpy(hw->perm_addr, DEFAULT_MAC_ADDRESS,
				MAC_ADDR_LEN);
			memcpy(hw->override_addr, DEFAULT_MAC_ADDRESS,
				MAC_ADDR_LEN);
			hw->override_addr[5] += hw_priv->sw.id;
			hw_set_addr(hw);
		}
	}
}  /* hw_read_addr */

/**
 * hw_reset - reset the hardware
 * @hw:		The hardware instance.
 *
 * This routine resets the hardware.
 */
static void hw_reset(struct ksz_hw *hw)
{
	writel(DMA_TX_RESET, hw->io + KS_DMA_TX_CTRL);

	/* MAC address always got erased after engine reset. */
	hw_set_addr(hw);
	hw_set_add_addr(hw);

#ifdef DEBUG_COUNTER
	hw->good[COUNT_GOOD_CMD_RESET]++;
#endif
}  /* hw_reset */

/**
 * hw_setup - setup the hardware
 * @hw:		The hardware instance.
 *
 * This routine setup the hardware for proper operation.
 */
static void hw_setup(struct ksz_hw *hw)
{
	/* Setup transmit control. */
	hw->tx_cfg = (DMA_TX_PAD_ENABLE | DMA_TX_CRC_ENABLE |
		(DMA_BURST_DEFAULT << DMA_BURST_SHIFT) | DMA_TX_ENABLE);
	hw->tx_cfg |= DMA_TX_FLOW_ENABLE;

#ifdef DEBUG_VERIFY
	if (hw->overrides & TX_LOOPBACK)
		hw->tx_cfg |= DMA_TX_LOOPBACK;

	if (hw->overrides & RX_LOOPBACK)
		hw->tx_cfg &= ~(DMA_TX_PAD_ENABLE | DMA_TX_CRC_ENABLE);
#endif

	/* Setup receive control. */
	hw->rx_cfg = (DMA_RX_BROADCAST | DMA_RX_UNICAST |
		(DMA_BURST_DEFAULT << DMA_BURST_SHIFT) | DMA_RX_ENABLE);
	hw->rx_cfg |= DMA_RX_FLOW_ENABLE;

	/* Hardware cannot handle UDP packet in IP fragments. */
	hw->rx_cfg |= (DMA_RX_CSUM_TCP | DMA_RX_CSUM_IP);

	/* Only work for IPv4 packets! */
	if (hw->features & IP_HEADER_ALIGN)
		hw->rx_cfg |= DMA_RX_IP_ALIGN;

	if (hw->features & RX_HUGE_FRAME)
		hw->rx_cfg |= DMA_RX_ERROR;

	if (hw->overrides & (RX_LOOPBACK | RX_ALL))
		hw->promiscuous++;

	if (hw->all_multi)
		hw->rx_cfg |= DMA_RX_ALL_MULTICAST;
	if (hw->promiscuous)
		hw->rx_cfg |= DMA_RX_PROMISCUOUS;

	dbg_msg("rx ctrl: %08x\n", hw->rx_cfg);
	dbg_msg("tx ctrl: %08x\n", hw->tx_cfg);
}  /* hw_setup */

/**
 * hw_setup_intr - setup interrupt mask
 * @hw:		The hardware instance.
 *
 * This routine setup the interrupt mask for proper operation.
 */
static void hw_setup_intr(struct ksz_hw *hw)
{
	struct dev_info *hw_priv = container_of(hw, struct dev_info, hw);

	hw->intr_mask = KS_INT_MASK | KS_INT_RX_OVERRUN;
	if (0 == hw_priv->sw.id)
		hw->intr_mask |= KS_INT_PHY;
}  /* hw_setup_intr */

/* -------------------------------------------------------------------------- */

static void ksz_check_desc_num(struct ksz_desc_info *info)
{
#define MIN_DESC_SHIFT  2

	int alloc = info->alloc;
	int shift;

	shift = 0;
	while (!(alloc & 1)) {
		shift++;
		alloc >>= 1;
	}
	if (alloc != 1 || shift < MIN_DESC_SHIFT) {
		pr_alert("Hardware descriptor numbers not right!\n");
		while (alloc) {
			shift++;
			alloc >>= 1;
		}
		if (shift < MIN_DESC_SHIFT)
			shift = MIN_DESC_SHIFT;
		alloc = 1 << shift;
		info->alloc = alloc;
	}
	info->mask = info->alloc - 1;
}  /* ksz_check_desc_num */

static void hw_init_desc(struct ksz_desc_info *desc_info, int transmit)
{
	int i;
	u32 phys = desc_info->ring_phys;
	struct ksz_hw_desc *desc = desc_info->ring_virt;
	struct ksz_desc *cur = desc_info->ring;
	struct ksz_desc *previous = NULL;
	int check = (desc_info->alloc * 15) / 16;

	for (i = 0; i < desc_info->alloc; i++) {
		cur->phw = desc++;
		phys += desc_info->size;
		previous = cur++;
		previous->phw->next = cpu_to_le32(phys);
		previous->check = &desc_info->ring_virt[((i + check) &
			desc_info->mask)];
	}
	previous->phw->next = cpu_to_le32(desc_info->ring_phys);
	previous->sw.buf.rx.end_of_ring = true;
	previous->phw->buf.data = cpu_to_le32(previous->sw.buf.data);

	desc_info->avail = desc_info->alloc;
	desc_info->last = desc_info->next = 0;

	desc_info->cur = desc_info->ring;
}  /* hw_init_desc */

/**
 * hw_set_desc_base - set descriptor base addresses
 * @hw:		The hardware instance.
 * @tx_addr:	The transmit descriptor base.
 * @rx_addr:	The receive descriptor base.
 *
 * This routine programs the descriptor base addresses after reset.
 */
static void hw_set_desc_base(struct ksz_hw *hw, u32 tx_addr, u32 rx_addr)
{
	/* Set base address of Tx/Rx descriptors. */
	writel(tx_addr, hw->io + KS_DMA_TX_ADDR);
	writel(rx_addr, hw->io + KS_DMA_RX_ADDR);
}  /* hw_set_desc_base */

static void hw_reset_pkts(struct ksz_desc_info *info)
{
	info->cur = info->ring;
	info->avail = info->alloc;
	info->last = info->next = 0;
}  /* hw_reset_pkts */

/* -------------------------------------------------------------------------- */

/*
 * Receive processing primary routines
 */

static inline void hw_resume_rx(struct ksz_hw *hw)
{
	writel(DMA_START, hw->io + KS_DMA_RX_START);
}

/**
 * hw_start_rx - start receiving
 * @hw:		The hardware instance.
 *
 * This routine starts the receive function of the hardware.
 */
static void hw_start_rx(struct ksz_hw *hw)
{
	writel(hw->rx_cfg, hw->io + KS_DMA_RX_CTRL);

	/* Notify when the receive stops. */
	hw->intr_mask |= KS_INT_RX_STOPPED;

	writel(DMA_START, hw->io + KS_DMA_RX_START);
	hw_ack_intr(hw, KS_INT_RX_STOPPED);
	hw->rx_stop++;

	/* Variable overflows. */
	if (0 == hw->rx_stop)
		hw->rx_stop = 2;
}  /* hw_start_rx */

/*
 * hw_stop_rx - stop receiving
 * @hw:		The hardware instance.
 *
 * This routine stops the receive function of the hardware.
 */
static void hw_stop_rx(struct ksz_hw *hw)
{
	hw->rx_stop = 0;
	hw_turn_off_intr(hw, KS_INT_RX_STOPPED);
	writel((hw->rx_cfg & ~DMA_RX_ENABLE), hw->io + KS_DMA_RX_CTRL);
}  /* hw_stop_rx */

/* -------------------------------------------------------------------------- */

/*
 * Transmit processing primary routines
 */

/**
 * hw_start_tx - start transmitting
 * @hw:		The hardware instance.
 *
 * This routine starts the transmit function of the hardware.
 */
static void hw_start_tx(struct ksz_hw *hw)
{
	writel(hw->tx_cfg, hw->io + KS_DMA_TX_CTRL);
}  /* hw_start_tx */

/**
 * hw_stop_tx - stop transmitting
 * @hw:		The hardware instance.
 *
 * This routine stops the transmit function of the hardware.
 */
static void hw_stop_tx(struct ksz_hw *hw)
{
	writel((hw->tx_cfg & ~DMA_TX_ENABLE), hw->io + KS_DMA_TX_CTRL);
}  /* hw_stop_tx */

/* -------------------------------------------------------------------------- */

/**
 * hw_disable - disable hardware
 * @hw:		The hardware instance.
 *
 * This routine disables the hardware.
 */
static void hw_disable(struct ksz_hw *hw)
{
	hw_stop_rx(hw);
	hw_stop_tx(hw);
	hw->enabled = 0;
}  /* hw_disable */

/**
 * hw_enable - enable hardware
 * @hw:		The hardware instance.
 *
 * This routine enables the hardware.
 */
static void hw_enable(struct ksz_hw *hw)
{
	hw_start_tx(hw);
	hw_start_rx(hw);
	hw->enabled = 1;
}  /* hw_enable */

/* -------------------------------------------------------------------------- */

/*
 * Transmit processing routines
 */

/**
 * hw_alloc_pkt - allocate enough descriptors for transmission
 * @hw:		The hardware instance.
 * @length:	The length of the packet.
 * @physical:	Number of descriptors required.
 *
 * This function allocates descriptors for transmission.
 *
 * Return 0 if not successful; 1 for buffer copy; or number of descriptors.
 */
static int hw_alloc_pkt(struct ksz_hw *hw, int length, int physical)
{
	/* Always leave one descriptor free. */
	if (hw->tx_desc_info.avail <= 1)
		return 0;

	/* Allocate a descriptor for transmission and mark it current. */
	get_tx_pkt(&hw->tx_desc_info, &hw->tx_desc_info.cur);
	hw->tx_desc_info.cur->sw.buf.tx.first_seg = true;

	/* Keep track of number of transmit descriptors used so far. */
	++hw->tx_int_cnt;
	hw->tx_size += length;

	/* Cannot hold on too much data. */
	if (hw->tx_size >= MAX_TX_HELD_SIZE)
		hw->tx_int_cnt = hw->tx_int_mask + 1;

	if (physical > hw->tx_desc_info.avail)
		return 1;

	return hw->tx_desc_info.avail;
}  /* hw_alloc_pkt */

/**
 * hw_send_pkt - mark packet for transmission
 * @hw:		The hardware instance.
 *
 * This routine marks the packet for transmission in PCI version.
 */
static void hw_send_pkt(struct ksz_hw *hw)
{
	struct ksz_desc *cur = hw->tx_desc_info.cur;

	cur->sw.buf.tx.last_seg = true;

	/* Interrupt only after specified number of descriptors used. */
	if (hw->tx_int_cnt > hw->tx_int_mask) {
		cur->sw.buf.tx.intr = true;
		hw->tx_int_cnt = 0;
		hw->tx_size = 0;
	}

	/* Switch supports port directed transmission. */
	cur->sw.buf.tx.dest_port = hw->dst_ports;

	release_desc(cur);

	writel(0, hw->io + KS_DMA_TX_START);
}  /* hw_send_pkt */

/* -------------------------------------------------------------------------- */

/**
 * hw_clr_multicast - clear multicast addresses
 * @hw:		The hardware instance.
 *
 * This routine removes all multicast addresses set in the hardware.
 */
static void hw_clr_multicast(struct ksz_hw *hw)
{
	int i;
	int j;

	j = ADDITIONAL_ENTRIES - 1;
	for (i = 0; i < hw->multi_list_size; i++, j--) {
		memset(hw->address[j], 0, MAC_ADDR_LEN);
		writel(0, hw->io + ADD_ADDR_INCR * j + KS_ADD_ADDR_0_HI);
	}
}  /* hw_clr_multicast */

/**
 * hw_set_grp_addr - set multicast addresses
 * @hw:		The hardware instance.
 *
 * This routine programs multicast addresses for the hardware to accept those
 * addresses.
 */
static void hw_set_grp_addr(struct ksz_hw *hw)
{
	int i;
	int j;

	j = ADDITIONAL_ENTRIES - 1;
	for (i = 0; i < hw->multi_list_size; i++, j--) {
		dbp_mac_addr(hw->address[j]);
		dbg_msg("\n");
		hw_ena_add_addr(hw, j, hw->address[j]);
	}
}  /* hw_set_grp_addr */

/**
 * hw_set_multicast - enable or disable all multicast receiving
 * @hw:		The hardware instance.
 * @multicast:	To turn on or off the all multicast feature.
 *
 * This routine enables/disables the hardware to accept all multicast packets.
 */
static void hw_set_multicast(struct ksz_hw *hw, u8 multicast)
{
	/* Stop receiving for reconfiguration. */
	hw_stop_rx(hw);

	if (multicast)
		hw->rx_cfg |= DMA_RX_ALL_MULTICAST;
	else
		hw->rx_cfg &= ~DMA_RX_ALL_MULTICAST;

	if (hw->enabled)
		hw_start_rx(hw);
}  /* hw_set_multicast */

/**
 * hw_set_promiscuous - enable or disable promiscuous receiving
 * @hw:		The hardware instance.
 * @prom:	To turn on or off the promiscuous feature.
 *
 * This routine enables/disables the hardware to accept all packets.
 */
static void hw_set_promiscuous(struct ksz_hw *hw, u8 prom)
{
	/* Stop receiving for reconfiguration. */
	hw_stop_rx(hw);

	if (prom)
		hw->rx_cfg |= DMA_RX_PROMISCUOUS;
	else
		hw->rx_cfg &= ~DMA_RX_PROMISCUOUS;

	if (hw->enabled)
		hw_start_rx(hw);
}  /* hw_set_promiscuous */

/* -------------------------------------------------------------------------- */

/**
 * sw_enable - enable the switch
 * @sw:		The switch instance.
 *
 * This routine is used to enable the switch in KSZ8695.
 */
static void sw_enable(struct ksz_sw *sw)
{
	int port;
	int enable;

	for (port = 0; port < SWITCH_PORT_NUM; port++) {
		if (sw->dev_count > 1) {
			/* Set port-base vlan membership with host port. */
			sw_cfg_port_base_vlan(sw, port,
				HOST_MASK | (1 << port));
			port_set_stp_state(sw, port, STP_STATE_DISABLED);
		} else {
			sw_cfg_port_base_vlan(sw, port, PORT_MASK);
			port_set_stp_state(sw, port, STP_STATE_FORWARDING);
		}
	}
	if (sw->dev_count > 1)
		port_set_stp_state(sw, SWITCH_PORT_NUM, STP_STATE_SIMPLE);
	else
		port_set_stp_state(sw, SWITCH_PORT_NUM, STP_STATE_FORWARDING);

	sw_cfg(KS_SWITCH_CTRL_0_OFFSET, SWITCH_ENABLE, true);
	if (sw->dev_count > 1)
		enable = 1;
	else
		enable = 0;
	sw_cfg(KS_SWITCH_HOST_CTRL_OFFSET,
		SWITCH_RX_PORT_INDICATE | SWITCH_TX_PORT_SPECIFY, enable);
}  /* sw_enable */

/**
 * sw_init - initialize the switch
 * @sw:		The switch instance.
 *
 * This routine initializes the hardware switch engine for default operation.
 */
static void sw_init(struct ksz_sw *sw)
{
	sw_init_broad_storm(sw);

	sw_init_prio(sw);

#ifdef CONFIG_KS8695P
	sw_init_prio_rate(sw);
#endif

	sw_init_vlan(sw);

#ifdef CONFIG_KS8695P
	if (sw_chk(KS_SWITCH_CTRL_1_OFFSET, P_SWITCH_TX_FLOW_DISABLE) ||
			sw_chk(KS_SWITCH_CTRL_1_OFFSET,
			P_SWITCH_RX_FLOW_DISABLE))
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
	sw_set_global_ctrl(sw);

	sw_setup_broad_storm(sw);

	sw_setup_prio(sw);

	sw_setup_mirror(sw);

	if (sw->features & STP_SUPPORT)
		sw_setup_stp(sw);
	sw_enable(sw);
}  /* sw_setup */

/* -------------------------------------------------------------------------- */

/**
 * ksz_alloc_soft_desc - allocate software descriptors
 * @desc_info:	Descriptor information structure.
 * @transmit:	Indication that descriptors are for transmit.
 *
 * This local function allocates software descriptors for manipulation in
 * memory.
 *
 * Return 0 if successful.
 */
static int ksz_alloc_soft_desc(struct ksz_desc_info *desc_info, int transmit)
{
	desc_info->ring = kzalloc(sizeof(struct ksz_desc) * desc_info->alloc,
		GFP_KERNEL);
	if (!desc_info->ring)
		return 1;
	hw_init_desc(desc_info, transmit);
	return 0;
}  /* ksz_alloc_soft_desc */

/**
 * ksz_alloc_desc - allocate hardware descriptors
 * @adapter:	Adapter information structure.
 *
 * This local function allocates hardware descriptors for receiving and
 * transmitting.
 *
 * Return 0 if successful.
 */
static int ksz_alloc_desc(struct dev_info *adapter)
{
	struct ksz_hw *hw = &adapter->hw;
	int offset;

	/* Allocate memory for RX & TX descriptors. */
	adapter->desc_pool.alloc_size =
		hw->rx_desc_info.size * hw->rx_desc_info.alloc +
		hw->tx_desc_info.size * hw->tx_desc_info.alloc +
		DESC_ALIGNMENT;

	adapter->desc_pool.alloc_virt =
		dma_alloc_coherent(
			adapter->pdev, adapter->desc_pool.alloc_size,
			&adapter->desc_pool.dma_addr, GFP_KERNEL);
	if (adapter->desc_pool.alloc_virt == NULL) {
		adapter->desc_pool.alloc_size = 0;
		return 1;
	}
	memset(adapter->desc_pool.alloc_virt, 0, adapter->desc_pool.alloc_size);

	/* Align to the next cache line boundary. */
	offset = (((ulong) adapter->desc_pool.alloc_virt % DESC_ALIGNMENT) ?
		(DESC_ALIGNMENT -
		((ulong) adapter->desc_pool.alloc_virt % DESC_ALIGNMENT)) : 0);
	adapter->desc_pool.virt = adapter->desc_pool.alloc_virt + offset;
	adapter->desc_pool.phys = adapter->desc_pool.dma_addr + offset;

	/* Allocate receive/transmit descriptors. */
	hw->rx_desc_info.ring_virt = (struct ksz_hw_desc *)
		adapter->desc_pool.virt;
	hw->rx_desc_info.ring_phys = adapter->desc_pool.phys;
	offset = hw->rx_desc_info.alloc * hw->rx_desc_info.size;
	hw->tx_desc_info.ring_virt = (struct ksz_hw_desc *)
		(adapter->desc_pool.virt + offset);
	hw->tx_desc_info.ring_phys = adapter->desc_pool.phys + offset;

	if (ksz_alloc_soft_desc(&hw->rx_desc_info, false))
		return 1;
	if (ksz_alloc_soft_desc(&hw->tx_desc_info, true))
		return 1;

	return 0;
}  /* ksz_alloc_desc */

/**
 * free_dma_buf - release DMA buffer resources
 * @adapter:	Adapter information structure.
 *
 * This routine is just a helper function to release the DMA buffer resources.
 */
static void free_dma_buf(struct dev_info *adapter, struct ksz_dma_buf *dma_buf,
	int direction)
{
#ifdef HIGH_MEM_SUPPORT
	dma_unmap_page(adapter->pdev, dma_buf->dma, dma_buf->len, direction);
#else
	dma_unmap_single(adapter->pdev, dma_buf->dma, dma_buf->len, direction);
#endif
	dev_kfree_skb(dma_buf->skb);
	dma_buf->skb = NULL;
	dma_buf->dma = 0;
}  /* free_dma_buf */

/**
 * ksz_init_rx_buffers - initialize receive descriptors
 * @adapter:	Adapter information structure.
 *
 * This routine initializes DMA buffers for receiving.
 */
static void ksz_init_rx_buffers(struct dev_info *adapter)
{
	int i;
	struct ksz_desc *desc;
	struct ksz_dma_buf *dma_buf;
	struct ksz_hw *hw = &adapter->hw;
	struct ksz_desc_info *info = &hw->rx_desc_info;

	for (i = 0; i < hw->rx_desc_info.alloc; i++) {
		get_rx_pkt(info, &desc);

		dma_buf = DMA_BUFFER(desc);
		if (dma_buf->skb && dma_buf->len != adapter->mtu)
			free_dma_buf(adapter, dma_buf, PCI_DMA_FROMDEVICE);
		dma_buf->len = adapter->mtu;
		if (!dma_buf->skb) {
			if (hw->features & IP_HEADER_ALIGN)
				/* skb->data != skb->head */
				dma_buf->skb = dev_alloc_skb(dma_buf->len);
			else
				/* skb->data == skb->head */
				dma_buf->skb = alloc_skb(dma_buf->len,
					GFP_ATOMIC);
		}
		if (dma_buf->skb && !dma_buf->dma) {
			dma_buf->skb->dev = adapter->dev;
#ifdef HIGH_MEM_SUPPORT
			dma_buf->dma = dma_map_page(
				adapter->pdev,
				virt_to_page(dma_buf->skb->tail),
				(unsigned long) dma_buf->skb->tail &
				~PAGE_MASK,
				dma_buf->len, DMA_FROM_DEVICE);
#else
			dma_buf->dma = dma_map_single(
				adapter->pdev, skb_tail_pointer(dma_buf->skb),
				dma_buf->len, DMA_FROM_DEVICE);
#endif
		}

		/* Set descriptor. */
		set_rx_buf(desc, dma_buf->dma);
		set_rx_len(desc, dma_buf->len);
		release_desc(desc);
	}
}  /* ksz_init_rx_buffers */

/**
 * ksz_alloc_mem - allocate memory for hardware descriptors
 * @adapter:	Adapter information structure.
 *
 * This function allocates memory for use by hardware descriptors for receiving
 * and transmitting.
 *
 * Return 0 if successful.
 */
static int ksz_alloc_mem(struct dev_info *adapter)
{
	struct ksz_hw *hw = &adapter->hw;

	/* Determine the number of receive and transmit descriptors. */
	hw->rx_desc_info.alloc = NUM_OF_RX_DESC;
	hw->tx_desc_info.alloc = NUM_OF_TX_DESC;

	/* Determine how many descriptors to skip transmit interrupt. */
	hw->tx_int_cnt = 0;
	hw->tx_int_mask = NUM_OF_TX_DESC / 4;
	if (hw->tx_int_mask > 8)
		hw->tx_int_mask = 8;
	while (hw->tx_int_mask) {
		hw->tx_int_cnt++;
		hw->tx_int_mask >>= 1;
	}
	if (hw->tx_int_cnt) {
		hw->tx_int_mask = (1 << (hw->tx_int_cnt - 1)) - 1;
		hw->tx_int_cnt = 0;
	}

	/* Determine the descriptor size. */
	hw->rx_desc_info.size =
		(((sizeof(struct ksz_hw_desc) + DESC_ALIGNMENT - 1) /
		DESC_ALIGNMENT) * DESC_ALIGNMENT);
	hw->tx_desc_info.size =
		(((sizeof(struct ksz_hw_desc) + DESC_ALIGNMENT - 1) /
		DESC_ALIGNMENT) * DESC_ALIGNMENT);
	if (hw->rx_desc_info.size != sizeof(struct ksz_hw_desc))
		pr_alert("Hardware descriptor size not right!\n");
	ksz_check_desc_num(&hw->rx_desc_info);
	ksz_check_desc_num(&hw->tx_desc_info);

	/* Allocate descriptors. */
	if (ksz_alloc_desc(adapter))
		return 1;

	return 0;
}  /* ksz_alloc_mem */

/**
 * ksz_free_desc - free software and hardware descriptors
 * @adapter:	Adapter information structure.
 *
 * This local routine frees the software and hardware descriptors allocated by
 * ksz_alloc_desc().
 */
static void ksz_free_desc(struct dev_info *adapter)
{
	struct ksz_hw *hw = &adapter->hw;

	/* Reset descriptor. */
	hw->rx_desc_info.ring_virt = NULL;
	hw->tx_desc_info.ring_virt = NULL;
	hw->rx_desc_info.ring_phys = 0;
	hw->tx_desc_info.ring_phys = 0;

	/* Free memory. */
	if (adapter->desc_pool.alloc_virt)
		dma_free_coherent(
			adapter->pdev,
			adapter->desc_pool.alloc_size,
			adapter->desc_pool.alloc_virt,
			adapter->desc_pool.dma_addr);

	/* Reset resource pool. */
	adapter->desc_pool.alloc_size = 0;
	adapter->desc_pool.alloc_virt = NULL;

	kfree(hw->rx_desc_info.ring);
	hw->rx_desc_info.ring = NULL;
	kfree(hw->tx_desc_info.ring);
	hw->tx_desc_info.ring = NULL;
}  /* ksz_free_desc */

/**
 * ksz_free_buffers - free buffers used in the descriptors
 * @adapter:	Adapter information structure.
 * @desc_info:	Descriptor information structure.
 *
 * This local routine frees buffers used in the DMA buffers.
 */
static void ksz_free_buffers(struct dev_info *adapter,
	struct ksz_desc_info *desc_info, int direction)
{
	int i;
	struct ksz_dma_buf *dma_buf;
	struct ksz_desc *desc = desc_info->ring;

	for (i = 0; i < desc_info->alloc; i++) {
		dma_buf = DMA_BUFFER(desc);
		if (dma_buf->skb)
			free_dma_buf(adapter, dma_buf, direction);
		desc++;
	}
}  /* ksz_free_buffers */

/**
 * ksz_free_mem - free all resources used by descriptors
 * @adapter:	Adapter information structure.
 *
 * This local routine frees all the resources allocated by ksz_alloc_mem().
 */
static void ksz_free_mem(struct dev_info *adapter)
{
	/* Free transmit buffers. */
	ksz_free_buffers(adapter, &adapter->hw.tx_desc_info,
		DMA_TO_DEVICE);

	/* Free receive buffers. */
	ksz_free_buffers(adapter, &adapter->hw.rx_desc_info,
		DMA_FROM_DEVICE);

	/* Free descriptors. */
	ksz_free_desc(adapter);
}  /* ksz_free_mem */

/* -------------------------------------------------------------------------- */

#ifdef CONFIG_KS8695P
#define MIB_RX				0x00
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

#define MIB_TX				0x14
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
#endif

#ifdef CONFIG_KS8695X
#define MIB_RX				0x00
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
#define MIB_RX_FRAME_LEN_ERR		0x13

#define MIB_TX				0x14
#define MIB_TX_CARRIER_SENSE		0x15
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
#endif

#define MIB_RX_DROPS			0x20
#define MIB_TX_DROPS			0x21

static struct {
	char string[20];
} mib_names[TOTAL_SWITCH_COUNTER_NUM] = {
	{ "rx           " },
#ifdef CONFIG_KS8695P
	{ "rx_hi        " },
#endif
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
#ifdef CONFIG_KS8695X
	{ "rx_frame_len" },
#endif

	{ "tx           " },
#ifdef CONFIG_KS8695P
	{ "tx_hi        " },
#endif
#ifdef CONFIG_KS8695X
	{ "tx_carrier" },
#endif
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
	{ MIB_RX, MIB_TX },
#ifdef CONFIG_KS8695P
	{ MIB_RX_HI_PRIO, MIB_TX_HI_PRIO },
#endif
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
#ifdef CONFIG_KS8695X
	{ MIG_RX_FRAME_LEN_ERR, MIB_TX_CARRIER_SENSE },
#endif
	{ MIB_TX_LATE_COLLISION, MIB_TX_DEFERRED },
	{ MIB_TX_TOTAL_COLLISION, MIB_TX_EXCESS_COLLISION },
	{ MIB_TX_SINGLE_COLLISION, MIB_TX_MULTI_COLLISION },
	{ MIB_RX_DROPS, MIB_TX_DROPS },
};

static void get_mib_counters(struct ksz_sw *sw, int first, int cnt,
	u64 *counter)
{
	int i;
	int mib;
	int port;
	struct ksz_port_mib *port_mib;

	memset(counter, 0, sizeof(u64) * TOTAL_SWITCH_COUNTER_NUM);
	for (i = 0, port = first; i < cnt; i++, port++) {
		port_mib = &sw->info->port_mib[port];
		for (mib = port_mib->mib_start; mib < sw->mib_cnt; mib++)
			counter[mib] += port_mib->counter[mib];
	}
}  /* get_mib_counters */

static int display_mib_counters(struct ksz_sw *sw, int first, int cnt,
	char *buf)
{
	int len = 0;
	u64 counter[TOTAL_SWITCH_COUNTER_NUM];

	get_mib_counters(sw, first, cnt, counter);
	for (cnt = 0; cnt < TOTAL_SWITCH_COUNTER_NUM / 2; cnt++) {
		int rx = mib_display[cnt].rx;
		int tx = mib_display[cnt].tx;

		if (rx < sw->info->port_mib[first].mib_start)
			continue;
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
}  /* display_mib_counter */

/* -------------------------------------------------------------------------- */

/**
 * send_packet - send packet
 * @skb:	Socket buffer.
 * @dev:	Network device.
 *
 * This routine is used to send a packet out to the network.
 */
static void send_packet(struct sk_buff *skb, struct net_device *dev)
{
	struct ksz_desc *desc;
	struct ksz_desc *first;
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_hw *hw = &hw_priv->hw;
	struct ksz_sw *sw = &hw_priv->sw;
	struct ksz_desc_info *info = &hw->tx_desc_info;
	struct ksz_dma_buf *dma_buf;
	int len;
	int last_frag = skb_shinfo(skb)->nr_frags;

	/*
	 * KSZ8695 with multiple device interfaces needs to be told which port
	 * to send.
	 */
	if (sw->dev_count > 1)
		hw->dst_ports = 1 << priv->port.first_port;

	/* Hardware will pad the length to 60. */
	len = skb->len;

	/* Remember the very first descriptor. */
	first = info->cur;
	desc = first;

	dma_buf = DMA_BUFFER(desc);
	if (last_frag) {
		int frag;
		skb_frag_t *this_frag;

		dma_buf->len = skb->len - skb->data_len;

#ifdef HIGH_MEM_SUPPORT
		dma_buf->dma = dma_map_page(
			hw_priv->pdev, virt_to_page(skb->data),
			((unsigned long) skb->data & ~PAGE_MASK), dma_buf->len,
			DMA_TO_DEVICE);
#else
		dma_buf->dma = dma_map_single(
			hw_priv->pdev, skb->data, dma_buf->len,
			DMA_TO_DEVICE);
#endif
		set_tx_buf(desc, dma_buf->dma);
		set_tx_len(desc, dma_buf->len);

		frag = 0;
		do {
			this_frag = &skb_shinfo(skb)->frags[frag];

			/* Get a new descriptor. */
			get_tx_pkt(info, &desc);

			/* Keep track of descriptors used so far. */
			++hw->tx_int_cnt;

			dma_buf = DMA_BUFFER(desc);
			dma_buf->len = this_frag->size;

#ifdef HIGH_MEM_SUPPORT
			dma_buf->dma = dma_map_page(
				hw_priv->pdev, this_frag->page,
				this_frag->page_offset, dma_buf->len,
				DMA_TO_DEVICE);
#else
			dma_buf->dma = dma_map_single(
				hw_priv->pdev,
				skb_frag_address(this_frag),
				dma_buf->len,
				DMA_TO_DEVICE);
#endif
			set_tx_buf(desc, dma_buf->dma);
			set_tx_len(desc, dma_buf->len);

			frag++;
			if (frag == last_frag)
				break;

			/* Do not release the last descriptor here. */
			release_desc(desc);
		} while (1);

		/* current points to the last descriptor. */
		info->cur = desc;

		/* Release the first descriptor. */
		release_desc(first);
	} else {
		dma_buf->len = len;

#ifdef HIGH_MEM_SUPPORT
		dma_buf->dma = dma_map_page(
			hw_priv->pdev, virt_to_page(skb->data),
			((unsigned long) skb->data & ~PAGE_MASK), dma_buf->len,
			DMA_TO_DEVICE);
#else
		dma_buf->dma = dma_map_single(
			hw_priv->pdev, skb->data, dma_buf->len,
			DMA_TO_DEVICE);
#endif
		set_tx_buf(desc, dma_buf->dma);
		set_tx_len(desc, dma_buf->len);
	}

	if (skb->ip_summed == CHECKSUM_PARTIAL) {
		struct iphdr *iph;

		iph = (struct iphdr *) skb_network_header(skb);
		if (iph->protocol == IPPROTO_TCP)
			(desc)->sw.buf.tx.csum_gen_tcp = true;
		else if (iph->protocol == IPPROTO_UDP)
			(desc)->sw.buf.tx.csum_gen_udp = true;
	}

	/*
	 * The last descriptor holds the packet so that it can be returned to
	 * network subsystem after all descriptors are transmitted.
	 */
	dma_buf->skb = skb;

#ifdef DEBUG_VERIFY
	if (hw->overrides & TX_DATA) {
		char msg[100];

		sprintf(msg, "S: %d\n", skb->len);
		if (hw->overrides & TX_LOOPBACK)
			dbp_pkt(skb, 0, msg, hw->overrides & DATA_HEADER);
		else
			dbp_pkt(skb, 0xFF, msg, hw->overrides & DATA_HEADER);
	}
#endif

	hw_send_pkt(hw);

	/* Update transmit statistics. */
	priv->stats.tx_packets++;
	priv->stats.tx_bytes += len;
}  /* send_packet */

/**
 * transmit_cleanup - clean up transmit descriptors
 * @hw_priv:	Hardware private structure.
 * @normal:	True for cleaning only transmitted descriptors.
 *
 * This routine is called to clean up the transmitted buffers.
 */
static void transmit_cleanup(struct dev_info *hw_priv, int normal)
{
	int last;
	union desc_stat status;
	struct ksz_hw *hw = &hw_priv->hw;
	struct ksz_desc_info *info = &hw->tx_desc_info;
	struct ksz_desc *desc;
	struct ksz_dma_buf *dma_buf;
	struct net_device *dev = NULL;

	spin_lock(&hw_priv->hwlock);
	last = info->last;

	while (info->avail < info->alloc) {
		/* Get next descriptor which is not hardware owned. */
		desc = &info->ring[last];
		status.data = le32_to_cpu(desc->phw->ctrl.data);
		if (status.tx.hw_owned) {
			if (normal)
				break;
			else
				reset_desc(desc, status);
		}

		dma_buf = DMA_BUFFER(desc);
#ifdef HIGH_MEM_SUPPORT
		dma_unmap_page(
			hw_priv->pdev, dma_buf->dma, dma_buf->len,
			DMA_TO_DEVICE);
#else
		dma_unmap_single(
			hw_priv->pdev, dma_buf->dma, dma_buf->len,
			DMA_TO_DEVICE);
#endif

		/* This descriptor contains the last buffer in the packet. */
		if (dma_buf->skb) {
			dev = dma_buf->skb->dev;

			/* Release the packet back to network subsystem. */
			dev_kfree_skb_irq(dma_buf->skb);
			dma_buf->skb = NULL;
		}

		/* Free the transmitted descriptor. */
		last++;
		last &= info->mask;
		info->avail++;
	}
	info->last = last;
	spin_unlock(&hw_priv->hwlock);

	/* Notify the network subsystem that the packet has been sent. */
	if (dev)
		dev->trans_start = jiffies;
}  /* transmit_cleanup */

/**
 * tx_done - transmit done processing
 * @hw_priv:	Hardware private structure.
 *
 * This routine is called when the transmit interrupt is triggered, indicating
 * either a packet is sent successfully or there are transmit errors.
 */
static void tx_done(struct dev_info *hw_priv)
{
	struct ksz_sw *sw = &hw_priv->sw;
	int port;

	transmit_cleanup(hw_priv, 1);

	for (port = 0; port < sw->dev_count; port++) {
		struct net_device *dev = sw->port_info[port].pdev;

		if (netif_running(dev) && netif_queue_stopped(dev))
			netif_wake_queue(dev);
	}
}  /* tx_done */

/* -------------------------------------------------------------------------- */

static inline void copy_old_skb(struct sk_buff *old, struct sk_buff *skb)
{
	skb->dev = old->dev;
	skb->protocol = old->protocol;
	skb->ip_summed = old->ip_summed;
	skb->csum = old->csum;
	skb_set_network_header(skb, ETH_HLEN);

	dev_kfree_skb(old);
}  /* copy_old_skb */

/**
 * netdev_tx - send out packet
 * @skb:	Socket buffer.
 * @dev:	Network device.
 *
 * This function is used by the upper network layer to send out a packet.
 *
 * Return 0 if successful; otherwise an error code indicating failure.
 */
static int netdev_tx(struct sk_buff *skb, struct net_device *dev)
{
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_hw *hw = &hw_priv->hw;
	int left;
	int num = 1;
	int rc = 0;

#ifdef DEBUG_VERIFY
	if ((hw->overrides & TX_DBG) && !(hw->overrides & TX_DATA))
		dbg_msg("S: %d\n", skb->len);

	if ((hw->overrides & TX_SHORT_FRAME) && skb->len >= 1600) {
		skb->len -= 1600;
		dbg_msg("min tx: %d\n", skb->len);
	}
#endif

	if (hw->features & SMALL_PACKET_TX_BUG) {
		struct sk_buff *org_skb = skb;

		if (skb->len <= 48) {
#ifdef NET_SKBUFF_DATA_USES_OFFSET
			if (skb_end_pointer(skb) - skb->data >= 50) {
#else
			if (skb->end - skb->data >= 50) {
#endif
				memset(&skb->data[skb->len], 0, 50 - skb->len);
				skb->len = 50;
			} else {
				skb = dev_alloc_skb(50);
				if (!skb)
					return NETDEV_TX_BUSY;
				memcpy(skb->data, org_skb->data, org_skb->len);
				memset(&skb->data[org_skb->len], 0,
					50 - org_skb->len);
				skb->len = 50;
				copy_old_skb(org_skb, skb);
			}
		}
	}

	spin_lock_irq(&hw_priv->hwlock);

	num = skb_shinfo(skb)->nr_frags + 1;
	left = hw_alloc_pkt(hw, skb->len, num);
	if (left) {
		if (left < num ||
				((hw->features & IPV6_CSUM_GEN_HACK) &&
				(CHECKSUM_PARTIAL == skb->ip_summed) &&
				(ETH_P_IPV6 == htons(skb->protocol)))) {
			struct sk_buff *org_skb = skb;

			skb = dev_alloc_skb(org_skb->len);
			if (!skb) {
				rc = NETDEV_TX_BUSY;
				goto netdev_tx_exit;
			}
			skb_copy_and_csum_dev(org_skb, skb->data);
			org_skb->ip_summed = 0;
			skb->len = org_skb->len;
			copy_old_skb(org_skb, skb);
		}
		send_packet(skb, dev);
		if (left <= num)
			netif_stop_queue(dev);
	} else {
		/* Stop the transmit queue until packet is allocated. */
		netif_stop_queue(dev);
		rc = NETDEV_TX_BUSY;
	}

netdev_tx_exit:
	spin_unlock_irq(&hw_priv->hwlock);

	return rc;
}  /* netdev_tx */

/**
 * netdev_tx_timeout - transmit timeout processing
 * @dev:	Network device.
 *
 * This routine is called when the transmit timer expires.  That indicates the
 * hardware is not running correctly because transmit interrupts are not
 * triggered to free up resources so that the transmit routine can continue
 * sending out packets.  The hardware is reset to correct the problem.
 */
static void netdev_tx_timeout(struct net_device *dev)
{
	static unsigned long last_reset;

	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_hw *hw = &hw_priv->hw;
	struct ksz_sw *sw = &hw_priv->sw;

	if (sw->dev_count > 1) {
		/*
		 * Only reset the hardware if time between calls is long
		 * enough.
		 */
		if (jiffies - last_reset <= dev->watchdog_timeo)
			hw_priv = NULL;
	}

	dbg_msg("tx timeout:%lu\n", jiffies);

	last_reset = jiffies;
	if (hw_priv) {
		hw_dis_intr(hw);
		hw_disable(hw);

		transmit_cleanup(hw_priv, 0);
		hw_reset_pkts(&hw->rx_desc_info);
		hw_reset_pkts(&hw->tx_desc_info);

		hw_reset(hw);

		hw_set_desc_base(hw,
			hw->tx_desc_info.ring_phys,
			hw->rx_desc_info.ring_phys);
		ksz_init_rx_buffers(hw_priv);

		if (hw->all_multi)
			hw_set_multicast(hw, hw->all_multi);
		else if (hw->multi_list_size)
			hw_set_grp_addr(hw);

		if (sw->dev_count > 1) {
			int port;

			hw_set_add_addr(hw);
			for (port = 0; port < SWITCH_PORT_NUM; port++) {
				struct net_device *port_dev;

				port_set_stp_state(sw, port,
					STP_STATE_DISABLED);

				port_dev = sw->port_info[port].pdev;
				if (netif_running(port_dev))
					port_set_stp_state(sw, port,
						STP_STATE_SIMPLE);
			}
		}

		hw_enable(hw);
		hw_ena_intr(hw);
	}

	dev->trans_start = jiffies;
	netif_wake_queue(dev);
}  /* netdev_tx_timeout */

/* -------------------------------------------------------------------------- */

static inline int get_aligned(struct sk_buff *skb, int aligned,
	struct ksz_hw *hw, union desc_stat status)
{
	unsigned short protocol;

	protocol = *((unsigned short *) &skb->data[aligned + 12]);
	if (protocol != htons(ETH_P_IP)) {
		int first = 0;

#ifdef DEBUG_VERIFY
		if (hw->overrides & RX_DBG) {
			char msg[100];

			sprintf(msg, "A: %d %08x\n", aligned, status.data);
			dbp_pkt(skb, 0, msg, 1);
		}
#endif
		for (first = 0; first < 4; first++) {
			if (skb->data[first] == hw->override_addr[0] ||
					(skb->data[first] & 1)) {
				protocol = *((unsigned short *)
					&skb->data[first + 12]);
				if (protocol == htons(ETH_P_IP)) {
					aligned = first;
					break;
				}
			}
		}
	}
	return aligned;
}  /* get_aligned */

static inline void csum_verified(struct sk_buff *skb)
{
	unsigned short protocol;
	struct iphdr *iph;

	protocol = skb->protocol;
	skb_reset_network_header(skb);
	iph = (struct iphdr *) skb_network_header(skb);
	if (protocol == htons(ETH_P_8021Q)) {
		protocol = iph->tot_len;
		skb_set_network_header(skb, VLAN_HLEN);
		iph = (struct iphdr *) skb_network_header(skb);
	}
	if (protocol == htons(ETH_P_IP)) {
		if (iph->protocol == IPPROTO_TCP)
			skb->ip_summed = CHECKSUM_UNNECESSARY;
	}
}  /* csum_verified */

static inline int rx_proc(struct net_device *dev, struct ksz_hw *hw,
	struct ksz_desc *desc, union desc_stat status)
{
	int packet_len;
	struct dev_priv *priv = netdev_priv(dev);
#ifdef USE_MULTIPLE_RX_DESC
	struct dev_info *hw_priv = priv->adapter;
#endif
	struct ksz_dma_buf *dma_buf;
	struct sk_buff *skb;
	int rx_status;
	int aligned = 0;

	/* Received length includes 4-byte CRC. */
#ifdef TEST_RX_LOOPBACK
	packet_len = status.rx.frame_len;
#else
	packet_len = status.rx.frame_len - 4;
#endif

#ifdef DEBUG_VERIFY
	if ((hw->overrides & RX_DBG) && !(hw->overrides & RX_DATA) &&
			(status.rx.error))
		dbg_msg("E: %08x, %d\n", status.data, packet_len);
#endif
	dma_buf = DMA_BUFFER(desc);
	dma_sync_single_for_cpu((struct device *) NULL, dma_buf->dma,
		packet_len + 4, DMA_FROM_DEVICE);

	if (hw->features & IP_HEADER_ALIGN) {
		aligned = status.rx.aligned;

		if (aligned) {
			dma_buf->skb->len = packet_len;
			aligned = get_aligned(dma_buf->skb, aligned, hw,
				status);
		}
	}

#ifdef USE_MULTIPLE_RX_DESC
	if (hw_priv->last_skb) {
		memcpy(&hw_priv->last_skb->data[hw_priv->skb_index],
			dma_buf->skb->data, hw_priv->skb_len);
		skb = hw_priv->last_skb;
		hw_priv->last_skb = NULL;
	} else
#endif
	if (aligned == 2 && packet_len > SKB_COPY_MAX) {
		skb = dma_buf->skb;

		/* skb->data != skb->head */
		dma_buf->skb = dev_alloc_skb(dma_buf->len);
		if (!dma_buf->skb) {
			dma_buf->skb = skb;
			priv->stats.rx_dropped++;
			return -ENOMEM;
		}

		dma_buf->dma = virt_to_dma(((struct device *) NULL),
			dma_buf->skb->data);

		/* Set descriptor. */
		set_rx_buf(desc, dma_buf->dma);

		if (aligned)
			skb_reserve(skb, aligned);
		skb_put(skb, packet_len);
		skb->truesize = packet_len + sizeof(struct sk_buff);
	} else {
		/* skb->data != skb->head */
		skb = dev_alloc_skb(packet_len + 2);
		if (!skb) {
			priv->stats.rx_dropped++;
			return -ENOMEM;
		}

		/*
		 * Align socket buffer in 4-byte boundary for better
		 * performance.
		 */
		skb_reserve(skb, 2);

		memcpy(skb_put(skb, packet_len),
			&dma_buf->skb->data[aligned], packet_len);
	}

#ifdef DEBUG_VERIFY
	if (hw->overrides & RX_DATA) {
		char msg[100];

		sprintf(msg, "R: %08x, %d\n", status.data, packet_len);
		if (hw->overrides & (RX_ALL | TX_LOOPBACK))
			dbp_pkt(skb, 0, msg, hw->overrides & DATA_HEADER);
		else
			dbp_pkt(skb, 0xFF, msg, hw->overrides & DATA_HEADER);
	}
#endif

	skb->dev = dev;

	/* Update receive statistics. */
	priv->stats.rx_packets++;
	priv->stats.rx_bytes += packet_len;

	/* Notify upper layer for received packet. */
	dev->last_rx = jiffies;

#ifdef DEBUG_COUNTER
	hw->good[COUNT_GOOD_RCV_COMPLETE]++;
#endif
#ifdef TEST_RX_LOOPBACK
	if (hw->overrides & RX_LOOPBACK) {
		skb_set_network_header(skb, ETH_HLEN);
		skb->ip_summed = CHECKSUM_UNNECESSARY;
		if (netif_queue_stopped(dev) || netdev_tx(skb, dev)) {
			dev_kfree_skb_irq(skb);
			priv->stats.tx_dropped++;
		}
		return 0;
	}
#endif
	skb->protocol = eth_type_trans(skb, dev);

	if (!status.rx.csum_err_tcp)
		csum_verified(skb);

	rx_status = netif_rx(skb);

	return 0;
}  /* rx_proc */

#ifdef USE_MULTIPLE_RX_DESC
static inline int copy_rx_seg(struct dev_info *hw_priv,
	struct ksz_dma_buf *dma_buf, int packet_len)
{
	dma_sync_single_for_cpu((struct device *) NULL, dma_buf->dma,
		dma_buf->len, DMA_FROM_DEVICE);

	if (!hw_priv->last_skb) {

		/* Allocate extra bytes for 32-bit transfer. */
		hw_priv->last_skb = dev_alloc_skb(packet_len + 2);
		if (!hw_priv->last_skb)
			return -ENOMEM;

		skb_reserve(hw_priv->last_skb, 2);
		skb_put(hw_priv->last_skb, packet_len - 4);
		hw_priv->skb_index = 0;
		hw_priv->skb_len = packet_len;
	}
	memcpy(&hw_priv->last_skb->data[hw_priv->skb_index],
		dma_buf->skb->data, dma_buf->len);
	hw_priv->skb_index += dma_buf->len;
	hw_priv->skb_len -= dma_buf->len;
	return 0;
}  /* copy_rx_seg */
#endif

static int dev_rcv_packets(struct dev_info *hw_priv)
{
	int next;
	union desc_stat status;
	struct ksz_hw *hw = &hw_priv->hw;
	struct ksz_sw *sw = &hw_priv->sw;
	struct net_device *dev = sw->port_info[0].pdev;
	struct ksz_desc_info *info = &hw->rx_desc_info;
#ifdef CONFIG_KSZ_NAPI
	int left = dev->quota;
#else
	int left = info->alloc;
#endif
	struct ksz_desc *desc;
	int received = 0;

	next = info->next;
	while (left--) {
		/* Get next descriptor which is not hardware owned. */
		desc = &info->ring[next];
		status.data = le32_to_cpu(desc->phw->ctrl.data);
		if (status.rx.hw_owned)
			break;

#ifdef DEBUG_COUNTER
		hw->good[COUNT_GOOD_NEXT_PACKET]++;
#endif

		/* Status valid only when last descriptor bit is set. */
		if (status.rx.last_desc && status.rx.first_desc) {
			if (rx_proc(dev, hw, desc, status))
				goto release_packet;
			received++;
		}
#ifdef DEBUG_VERIFY
		else if (hw->overrides & RX_DBG)
			dbg_msg(" ? %08x\n", status.data);
#endif

release_packet:
		release_desc(desc);
		next++;
		next &= info->mask;
	}
	info->next = next;

#ifdef DEBUG_COUNTER
	if (!received)
		hw->good[COUNT_GOOD_NO_NEXT_PACKET]++;
	else if (1 == received)
		hw->good[COUNT_GOOD_RCV_CNT_1]++;
	else if (2 == received)
		hw->good[COUNT_GOOD_RCV_CNT_2]++;
	else
		hw->good[COUNT_GOOD_RCV_CNT_3]++;
#endif
	return received;
}  /* dev_rcv_packets */

static int port_rcv_packets(struct dev_info *hw_priv)
{
	int next;
	union desc_stat status;
	struct ksz_hw *hw = &hw_priv->hw;
	struct ksz_sw *sw = &hw_priv->sw;
	struct net_device *dev = sw->port_info[0].pdev;
	struct ksz_desc_info *info = &hw->rx_desc_info;
#ifdef CONFIG_KSZ_NAPI
	int left = dev->quota;
#else
	int left = info->alloc;
#endif
	struct ksz_desc *desc;
	int received = 0;

	next = info->next;
	while (left--) {
		/* Get next descriptor which is not hardware owned. */
		desc = &info->ring[next];
		status.data = le32_to_cpu(desc->phw->ctrl.data);
		if (status.rx.hw_owned)
			break;

#ifdef DEBUG_COUNTER
		hw->good[COUNT_GOOD_NEXT_PACKET]++;
#endif
		if (sw->dev_count > 1) {
			/* Get received port number. */
			int p = status.rx.src_port;

			dev = sw->port_info[p].pdev;
			if (!netif_running(dev))
				goto release_packet;
		}

		/* Status valid only when last descriptor bit is set. */
		if (status.rx.last_desc && status.rx.first_desc) {
			if (rx_proc(dev, hw, desc, status))
				goto release_packet;
			received++;
		}
#ifdef DEBUG_VERIFY
		else if (hw->overrides & RX_DBG)
			dbg_msg(" ? %08x\n", status.data);
#endif

release_packet:
		release_desc(desc);
		next++;
		next &= info->mask;
	}
	info->next = next;

#ifdef DEBUG_COUNTER
	if (!received)
		hw->good[COUNT_GOOD_NO_NEXT_PACKET]++;
	else if (1 == received)
		hw->good[COUNT_GOOD_RCV_CNT_1]++;
	else if (2 == received)
		hw->good[COUNT_GOOD_RCV_CNT_2]++;
	else
		hw->good[COUNT_GOOD_RCV_CNT_3]++;
#endif
	return received;
}  /* port_rcv_packets */

static int dev_rcv_special(struct dev_info *hw_priv)
{
	int next;
	union desc_stat status;
	struct ksz_hw *hw = &hw_priv->hw;
	struct ksz_sw *sw = &hw_priv->sw;
	struct net_device *dev = sw->port_info[0].pdev;
	struct ksz_desc_info *info = &hw->rx_desc_info;
#ifdef CONFIG_KSZ_NAPI
	int left = dev->quota;
#else
	int left = info->alloc;
#endif
	struct ksz_desc *desc;
	int received = 0;

	next = info->next;
	while (left--) {
		/* Get next descriptor which is not hardware owned. */
		desc = &info->ring[next];
		status.data = le32_to_cpu(desc->phw->ctrl.data);
		if (status.rx.hw_owned)
			break;

#ifdef DEBUG_COUNTER
		hw->good[COUNT_GOOD_NEXT_PACKET]++;
#endif
		if ((hw->overrides & CHECK_RX_OVERRUN) &&
				!(desc->check->ctrl.data &
				cpu_to_le32(KS_DESC_HW_OWNED))) {
			release_desc(desc);
			next++;
			next &= info->mask;
			left = info->alloc;
			continue;
		}

		if (sw->dev_count > 1) {
			/* Get received port number. */
			int p = status.rx.src_port;

			dev = sw->port_info[p].pdev;
			if (!netif_running(dev))
				goto release_packet;
		}

		/* Status valid only when last descriptor bit is set. */
#ifndef USE_MULTIPLE_RX_DESC
		if (status.rx.last_desc && status.rx.first_desc) {
#else
		if (status.rx.last_desc) {
#endif
			struct dev_priv *priv = netdev_priv(dev);
			struct ksz_port *port = &priv->port;

			/*
			 * Receive without error.  With receive errors
			 * disabled, packets with receive errors will be
			 * dropped, so no need to check the error bit.
			 */
			if (!status.rx.error || (status.data &
					KS_DESC_RX_ERROR_COND) ==
					KS_DESC_RX_ERROR_TOO_LONG) {
				if (rx_proc(dev, hw, desc, status))
					goto release_packet;
				received++;
			} else {

#ifdef USE_MULTIPLE_RX_DESC
				if (hw_priv->last_skb) {
					dev_kfree_skb(hw_priv->last_skb);
					hw_priv->last_skb = NULL;
				}
#endif

				/* Update receive error statistics. */
				port->counter[OID_COUNTER_RCV_ERROR]++;

#ifdef DEBUG_VERIFY
				if (hw->overrides & RX_DBG)
					dbg_msg("  RX: %08X\n", status.data);
#endif
#ifdef DEBUG_COUNTER
				hw->bad[COUNT_BAD_RCV_FRAME]++;
#endif
			}

/* Hardware checksum errors are not associated with receive errors. */

#ifdef DEBUG
/* Hardware cannot handle UDP packet in IP fragments. */
			if (status.rx.csum_err_udp)
				port->counter[OID_COUNTER_RCV_ERROR_UDP]++;
			if (status.rx.csum_err_tcp)
				port->counter[OID_COUNTER_RCV_ERROR_TCP]++;
			if (status.rx.csum_err_ip)
				port->counter[OID_COUNTER_RCV_ERROR_IP]++;
#endif
		}

#ifdef USE_MULTIPLE_RX_DESC
		else if (!status.rx.last_desc) {
			if (copy_rx_seg(hw_priv, DMA_BUFFER(desc),
					status.rx.frame_len)) {
				priv->stats.rx_dropped++;
				goto release_packet;
			}
		}
#endif
#ifdef DEBUG_VERIFY
		else if (hw->overrides & RX_DBG)
			dbg_msg(" ? %08x\n", status.data);
#endif

release_packet:
		release_desc(desc);
		next++;
		next &= info->mask;
	}
	info->next = next;

#ifdef DEBUG_COUNTER
	if (!received)
		hw->good[COUNT_GOOD_NO_NEXT_PACKET]++;
	else if (1 == received)
		hw->good[COUNT_GOOD_RCV_CNT_1]++;
	else if (2 == received)
		hw->good[COUNT_GOOD_RCV_CNT_2]++;
	else
		hw->good[COUNT_GOOD_RCV_CNT_3]++;
#endif
	return received;
}  /* dev_rcv_special */

/* -------------------------------------------------------------------------- */

static void rx_proc_task(unsigned long data)
{
	struct dev_info *hw_priv = (struct dev_info *) data;
	struct ksz_hw *hw = &hw_priv->hw;

	if (!hw->enabled)
		return;
	if (unlikely(!hw_priv->dev_rcv(hw_priv))) {

		/* In case receive process is suspended because of overrun. */
		hw_resume_rx(hw);

		/* tasklets are interruptible. */
		spin_lock_irq(&hw_priv->hwlock);
		hw_turn_on_intr(hw, KS_INT_RX_MASK);
		spin_unlock_irq(&hw_priv->hwlock);
	} else {
		hw_ack_intr(hw, KS_INT_RX);
		tasklet_schedule(&hw_priv->rx_tasklet);
	}
#ifdef DEBUG_VERIFY
	if (hw->overrides & (RX_DBG | RX_DATA | TX_DBG | TX_DATA))
		schedule_work(&db.dbg_print);
#endif
}  /* rx_proc_task */

static void tx_proc_task(unsigned long data)
{
	struct dev_info *hw_priv = (struct dev_info *) data;
	struct ksz_hw *hw = &hw_priv->hw;

	hw_ack_intr(hw, KS_INT_TX_MASK);

	tx_done(hw_priv);

	/* tasklets are interruptible. */
	spin_lock_irq(&hw_priv->hwlock);
	hw_turn_on_intr(hw, KS_INT_TX);
	spin_unlock_irq(&hw_priv->hwlock);
#ifdef DEBUG_VERIFY
	if (hw->overrides & (RX_DBG | RX_DATA | TX_DBG | TX_DATA))
		schedule_work(&db.dbg_print);
#endif
}  /* tx_proc_task */

#ifdef CONFIG_KSZ_NAPI
/**
 * netdev_poll
 * @dev:	Network device.
 * @budget:	Remaining number of packets allowed to report to the stack.
 *
 * This function is used to poll the device for received buffers.
 *
 * Return 0 if all packets reported; one to indicate more.
 */
static int netdev_poll(struct net_device *dev, int *budget)
{
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_hw *hw = &hw_priv->hw;
	int received;
	int left = min(*budget, dev->quota);

	hw_ack_intr(hw, KS_INT_RX);

	received = hw_priv->dev_rcv(hw_priv);

	dev->quota -= received;
	*budget -= received;

	if (received < left) {
		netif_rx_complete(dev);

		/* tasklets are interruptible. */
		spin_lock_irq(&hw_priv->hwlock);
		hw_turn_on_intr(hw, KS_INT_RX_MASK);
		spin_unlock_irq(&hw_priv->hwlock);
	}

	return received >= left;
}  /* netdev_poll */
#endif

static inline void handle_rx_stop(struct ksz_hw *hw)
{
	/* Receive just has been stopped. */
	if (0 == hw->rx_stop)
		hw->intr_mask &= ~KS_INT_RX_STOPPED;
	else if (hw->rx_stop > 1) {
		if (hw->enabled && (hw->rx_cfg & DMA_RX_ENABLE)) {
			hw_start_rx(hw);
		} else {
			hw->intr_mask &= ~KS_INT_RX_STOPPED;
			hw->rx_stop = 0;
		}
	} else
		/* Receive just has been started. */
		hw->rx_stop++;
}  /* handle_rx_stop */

/**
 * netdev_intr - interrupt handling
 * @irq:	Interrupt number.
 * @dev_id:	Network device.
 *
 * This function is called by upper network layer to signal interrupt.
 *
 * Return IRQ_HANDLED if interrupt is handled.
 */
static irqreturn_t netdev_intr(int irq, void *dev_id)
{
	uint int_enable = 0;
	struct net_device *dev = (struct net_device *) dev_id;
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_hw *hw = &hw_priv->hw;

	hw_read_intr(hw, &int_enable);
#ifdef DEBUG_COUNTER
	hw->good[COUNT_GOOD_INT]++;
#endif
	do {
#ifdef DEBUG_COUNTER
		hw->good[COUNT_GOOD_INT_LOOP]++;
#endif
#ifdef DEBUG_INTERRUPT
		dbg_msg("I: %08X\n", int_enable);
#endif
		int_enable &= hw->intr_mask;
		hw_ack_intr(hw, int_enable);

		if (unlikely(int_enable & KS_INT_TX_MASK)) {
			hw_dis_intr_bit(hw, KS_INT_TX_MASK);
			tasklet_schedule(&hw_priv->tx_tasklet);
		}

		if (likely(int_enable & KS_INT_RX)) {
#ifdef DEBUG_COUNTER
			hw->good[COUNT_GOOD_INT_RX]++;
#endif

#ifdef CONFIG_KSZ_NAPI
			hw_dis_intr_bit(hw, KS_INT_RX_MASK);
			if (likely(netif_rx_schedule_prep(dev))) {

				/* tell system we have work to be done. */
				__netif_rx_schedule(dev);
			}

#else
			hw_dis_intr_bit(hw, KS_INT_RX);
			tasklet_schedule(&hw_priv->rx_tasklet);
#endif
		}

		if (unlikely(int_enable & KS_INT_RX_OVERRUN)) {
			priv->stats.rx_fifo_errors++;
			hw_resume_rx(hw);
		}

		if (unlikely(int_enable & KS_INT_PHY)) {
			struct ksz_port *port = &priv->port;

			hw->features |= LINK_INT_WORKING;
			port_get_link_speed(port);
		}

		if (unlikely(int_enable & KS_INT_RX_STOPPED)) {
			handle_rx_stop(hw);
			break;
		}

		if (unlikely(int_enable & KS_INT_TX_STOPPED)) {
			hw->intr_mask &= ~KS_INT_TX_STOPPED;
			break;
		}
	} while (0);

	hw_set_intr(hw, hw->intr_mask);

#ifdef HAVE_DELAY_SOFTIRQ
	delay_softirq = 1;
#endif

	return IRQ_HANDLED;
}  /* netdev_intr */

/* -------------------------------------------------------------------------- */

/*
 * Linux network device functions
 */

static unsigned long next_jiffies;

#ifdef CONFIG_NET_POLL_CONTROLLER
static void netdev_netpoll(struct net_device *dev)
{
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;

	hw_dis_intr(&hw_priv->hw);
	netdev_intr(dev->irq, dev);
}  /* netdev_netpoll */
#endif

static void bridge_change(struct ksz_sw *sw)
{
	int port;
	u8 member;
	struct ksz_sw_info *info = sw->info;

	/* No ports in forwarding state. */
	if (!info->member) {
		port_set_stp_state(sw, SWITCH_PORT_NUM, STP_STATE_SIMPLE);
		sw_block_addr(sw);
	}
	for (port = 0; port < SWITCH_PORT_NUM; port++) {
		if (STP_STATE_FORWARDING == info->port_cfg[port].stp_state)
			member = HOST_MASK | info->member;
		else
			member = HOST_MASK | (1 << port);
		if (member != info->port_cfg[port].member)
			sw_cfg_port_base_vlan(sw, port, member);
	}
}  /* bridge_change */

/**
 * netdev_close - close network device
 * @dev:	Network device.
 *
 * This function process the close operation of network device.  This is caused
 * by the user command "ifconfig ethX down."
 *
 * Return 0 if successful; otherwise an error code indicating failure.
 */
static int netdev_close(struct net_device *dev)
{
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_port *port = &priv->port;
	struct ksz_hw *hw = &hw_priv->hw;
	struct ksz_sw *sw = &hw_priv->sw;
	int irq;
	int i;
	int pi;

	netif_stop_queue(dev);

	ksz_stop_timer(&priv->monitor_timer_info);

	/* Need to shut the port manually in multiple device interfaces mode. */
	if (sw->dev_count > 1) {
		port_set_stp_state(sw, port->first_port, STP_STATE_DISABLED);

		/* Port is closed.  Need to change bridge setting. */
		if ((sw->features & STP_SUPPORT) &&
				br_port_exists(dev)) {
			pi = 1 << port->first_port;
			if (sw->info->member & pi) {
				sw->info->member &= ~pi;
				bridge_change(sw);
			}
		}
	}
	if (port->first_port > 0)
		hw_del_addr(hw, dev->dev_addr);

	/* Turn off LED to indicate device not running. */
	for (i = 0, pi = port->first_port; i < port->port_cnt; i++, pi++)
		port_set_led(pi + sw->id, 0);
	if (!hw_priv->wol_enable)
		port_set_power_saving(port, true);

	if (priv->multicast)
		--hw->all_multi;
	if (priv->promiscuous)
		--hw->promiscuous;

	hw_priv->opened--;
	if (hw_priv->opened)
		return 0;

	ksz_stop_timer(&hw_priv->mib_timer_info);
	flush_work(&hw_priv->mib_read);

	hw_dis_intr(hw);
	hw_disable(hw);
	hw_clr_multicast(hw);

	/* Delay for receive task to stop scheduling itself. */
	msleep(2000 / HZ);

	tasklet_disable(&hw_priv->rx_tasklet);
	tasklet_disable(&hw_priv->tx_tasklet);
	for (irq = 0; irq < hw_priv->irq_count; irq++)
		free_irq(dev->irq + irq, hw_priv->dev);

	transmit_cleanup(hw_priv, false);
	hw_reset_pkts(&hw->rx_desc_info);
	hw_reset_pkts(&hw->tx_desc_info);

	/* Clean out static MAC table when the switch is shutdown. */
	if (sw->features & STP_SUPPORT)
		sw_clr_sta_mac_table(sw);

	return 0;
}  /* netdev_close */

static void hw_cfg_huge_frame(struct dev_info *hw_priv, struct ksz_hw *hw)
{
	struct ksz_sw *sw = &hw_priv->sw;

#ifdef CONFIG_KS8695P
	if (sw->info) {
		u32 data;

		data = KS_R(KS_SWITCH_CTRL_1_OFFSET);
		if (hw->features & RX_HUGE_FRAME)
			data |= P_SWITCH_HUGE_PACKET;
		else
			data &= ~P_SWITCH_HUGE_PACKET;
		KS_WR(KS_SWITCH_CTRL_1_OFFSET, data);
	}
#endif
	if (hw->features & RX_HUGE_FRAME) {
		hw->rx_cfg |= DMA_RX_ERROR;
		hw_priv->dev_rcv = dev_rcv_special;
	} else {
		hw->rx_cfg &= ~DMA_RX_ERROR;
		if (sw->dev_count > 1)
			hw_priv->dev_rcv = port_rcv_packets;
		else
			hw_priv->dev_rcv = dev_rcv_packets;
		if (hw->overrides & CHECK_RX_OVERRUN)
			hw_priv->dev_rcv = dev_rcv_special;
	}
}  /* hw_cfg_huge_frame */

static int prepare_hardware(struct net_device *dev)
{
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_hw *hw = &hw_priv->hw;
	int irq;
	int rc = 0;

	/* Remember the network device that requests interrupts. */
	hw_priv->dev = dev;
	for (irq = 0; irq < hw_priv->irq_count; irq++) {
		switch (irq) {
		case 0:
			sprintf(hw_priv->irq_name[irq],
				"%s rx stopped", dev->name);
			break;
		case 1:
			sprintf(hw_priv->irq_name[irq],
				"%s tx stopped", dev->name);
			break;
		case 2:
			sprintf(hw_priv->irq_name[irq],
				"%s rx buffer empty", dev->name);
			break;
		case 3:
			sprintf(hw_priv->irq_name[irq],
				"%s tx buffer empty", dev->name);
			break;
		case 4:
			sprintf(hw_priv->irq_name[irq],
				"%s rx", dev->name);
			break;
		case 5:
			sprintf(hw_priv->irq_name[irq],
				"%s tx", dev->name);
			break;
		case 6:
			sprintf(hw_priv->irq_name[irq],
				"%s link", dev->name);
			break;
		default:
			break;
		}
		rc = request_irq(dev->irq + irq, netdev_intr, IRQF_DISABLED,
			hw_priv->irq_name[irq], dev);
		if (rc) {
			while (irq--)
				free_irq(dev->irq + irq, dev);
			return rc;
		}
	}
	tasklet_enable(&hw_priv->rx_tasklet);
	tasklet_enable(&hw_priv->tx_tasklet);

	hw->promiscuous = 0;
	hw->all_multi = 0;
	hw->multi_list_size = 0;

	hw_reset(hw);

	hw_set_desc_base(hw,
		hw->tx_desc_info.ring_phys, hw->rx_desc_info.ring_phys);
	hw_cfg_huge_frame(hw_priv, hw);
	ksz_init_rx_buffers(hw_priv);
	return 0;
}  /* prepare_hardware */

static void set_media_state(struct net_device *dev, int media_state)
{
	struct dev_priv *priv = netdev_priv(dev);

	if (media_state == priv->media_state)
		netif_carrier_on(dev);
	else
		netif_carrier_off(dev);
	if (netif_msg_link(priv))
		pr_info("%s link %s\n", dev->name,
			(media_state == priv->media_state ? "on" : "off"));
}

/**
 * netdev_open - open network device
 * @dev:	Network device.
 *
 * This function process the open operation of network device.  This is caused
 * by the user command "ifconfig ethX up."
 *
 * Return 0 if successful; otherwise an error code indicating failure.
 */
static int netdev_open(struct net_device *dev)
{
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_hw *hw = &hw_priv->hw;
	struct ksz_sw *sw = &hw_priv->sw;
	struct ksz_port *port = &priv->port;
	int i;
	int p;
	int rc = 0;

	priv->multicast = 0;
	priv->promiscuous = 0;

	/* Reset device statistics. */
	memset(&priv->stats, 0, sizeof(struct net_device_stats));
	memset((void *) port->counter, 0,
		(sizeof(u64) * OID_COUNTER_LAST));

	if (!(hw_priv->opened)) {
		rc = prepare_hardware(dev);
		if (rc)
			return rc;
		for (i = 0; i < sw->mib_port_cnt; i++) {
			if (next_jiffies < jiffies)
				next_jiffies = jiffies + HZ * 2;
			else
				next_jiffies += HZ * 1;
			hw_priv->counter[i].time = next_jiffies;
			sw->port_info[i].state = media_disconnected;
			port_init_cnt(sw, i);
		}
		sw->port_info[HOST_PORT].state = media_connected;
	}
	port_set_power_saving(port, false);

/*
 * THa  2012-05-30
 * Powering up the WAN port somehow triggers PHY interrupt in the new revison
 * chip.
 */
	if (hw->intr_check & KS_INT_PHY)
		hw_ack_intr(hw, KS_INT_PHY);

	for (i = 0, p = port->first_port; i < port->port_cnt; i++, p++)
		sw->port_info[p].state = media_disconnected;

	/* Need to open the port in multiple device interfaces mode. */
	if (sw->dev_count > 1) {
		if (!br_port_exists(dev))
			priv->state = STP_STATE_SIMPLE;
		port_set_stp_state(sw, port->first_port, priv->state);
		if (port->first_port > 0)
			hw_add_addr(hw, dev->dev_addr);
	}

	port_get_link_speed(port);
	if (port->force_link)
		port_force_link_speed(port);
	else
		port_set_link_speed(port);

	if (!(hw_priv->opened)) {
		hw_setup_intr(hw);
		hw_enable(hw);
		hw_ena_intr(hw);

		if (sw->mib_port_cnt)
			ksz_start_timer(&hw_priv->mib_timer_info,
				hw_priv->mib_timer_info.period);
	}

	hw_priv->opened++;

	ksz_start_timer(&priv->monitor_timer_info,
		priv->monitor_timer_info.period);

	priv->media_state = port->linked->state;

	set_media_state(dev, media_connected);
	netif_start_queue(dev);

	return 0;
}  /* netdev_open */

/* RX errors = rx_errors */
/* RX dropped = rx_dropped */
/* RX overruns = rx_fifo_errors */
/* RX frame = rx_crc_errors + rx_frame_errors + rx_length_errors */
/* TX errors = tx_errors */
/* TX dropped = tx_dropped */
/* TX overruns = tx_fifo_errors */
/* TX carrier = tx_aborted_errors + tx_carrier_errors + tx_window_errors */
/* collisions = collisions */

/**
 * netdev_query_statistics - query network device statistics
 * @dev:	Network device.
 *
 * This function returns the statistics of the network device.  The device
 * needs not be opened.
 *
 * Return network device statistics.
 */
static struct net_device_stats *netdev_query_statistics(struct net_device *dev)
{
	struct dev_priv *priv = netdev_priv(dev);
	struct ksz_port *port = &priv->port;
	struct ksz_sw *sw = &priv->adapter->sw;
	struct ksz_port_mib *mib;
	int i;
	int p;

	priv->stats.rx_errors = port->counter[OID_COUNTER_RCV_ERROR];
	priv->stats.tx_errors = port->counter[OID_COUNTER_XMIT_ERROR];

	/* Reset to zero to add count later. */
	priv->stats.multicast = 0;
	priv->stats.collisions = 0;
	priv->stats.rx_length_errors = 0;
	priv->stats.rx_crc_errors = 0;
	priv->stats.rx_frame_errors = 0;
	priv->stats.tx_window_errors = 0;

	for (i = 0, p = port->first_port; i < port->mib_port_cnt; i++, p++) {
		mib = &sw->info->port_mib[p];

		priv->stats.multicast += (unsigned long)
			mib->counter[MIB_COUNTER_RX_MULTICAST];

		priv->stats.collisions += (unsigned long)
			mib->counter[MIB_COUNTER_TX_TOTAL_COLLISION];

		priv->stats.rx_length_errors += (unsigned long)(
			mib->counter[MIB_COUNTER_RX_UNDERSIZE] +
			mib->counter[MIB_COUNTER_RX_FRAGMENT] +
			mib->counter[MIB_COUNTER_RX_OVERSIZE] +
			mib->counter[MIB_COUNTER_RX_JABBER]);
		priv->stats.rx_crc_errors += (unsigned long)
			mib->counter[MIB_COUNTER_RX_CRC_ERR];
		priv->stats.rx_frame_errors += (unsigned long)(
			mib->counter[MIB_COUNTER_RX_ALIGNMENT_ERR] +
			mib->counter[MIB_COUNTER_RX_SYMBOL_ERR]);

		priv->stats.tx_window_errors += (unsigned long)
			mib->counter[MIB_COUNTER_TX_LATE_COLLISION];
	}

#ifdef DEBUG_COUNTER
	if (jiffies - priv->query_jiffies >= 1000 * HZ / 1000) {
		if (hw->good[COUNT_GOOD_INT])
			display_mib_counters(sw, NULL);
		dbg_msg("%u %u %u; ",
			hw->good[COUNT_GOOD_RCV_CNT_1],
			hw->good[COUNT_GOOD_RCV_CNT_2],
			hw->good[COUNT_GOOD_RCV_CNT_3]);
		dbg_msg("I=%u L=%u R=%u; N=%u C=%u; Z=%u, T=%u\n",
			hw->good[COUNT_GOOD_INT],
			hw->good[COUNT_GOOD_INT_LOOP],
			hw->good[COUNT_GOOD_INT_RX],
			hw->good[COUNT_GOOD_NEXT_PACKET],
			hw->good[COUNT_GOOD_RCV_COMPLETE],
			hw->good[COUNT_GOOD_NO_NEXT_PACKET],
			hw->good[COUNT_GOOD_RCV_NOT_DISCARD]);
		hw->good[COUNT_GOOD_INT] =
		hw->good[COUNT_GOOD_INT_LOOP] =
		hw->good[COUNT_GOOD_INT_RX] =
		hw->good[COUNT_GOOD_NEXT_PACKET] =
		hw->good[COUNT_GOOD_RCV_COMPLETE] =
		hw->good[COUNT_GOOD_NO_NEXT_PACKET] =
		hw->good[COUNT_GOOD_RCV_NOT_DISCARD] =
		hw->good[COUNT_GOOD_RCV_CNT_1] =
		hw->good[COUNT_GOOD_RCV_CNT_2] =
		hw->good[COUNT_GOOD_RCV_CNT_3] =
			0;
	}
	priv->query_jiffies = jiffies;
#endif

	return &priv->stats;
}  /* netdev_query_statistics */

/**
 * netdev_set_mac_address - set network device MAC address
 * @dev:	Network device.
 * @addr:	Buffer of MAC address.
 *
 * This function is used to set the MAC address of the network device.
 *
 * Return 0 to indicate success.
 */
static int netdev_set_mac_address(struct net_device *dev, void *addr)
{
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_hw *hw = &hw_priv->hw;
	struct sockaddr *mac = addr;

	if (priv->port.first_port > 0)
		hw_del_addr(hw, dev->dev_addr);
	else {
		hw->mac_override = true;
		memcpy(hw->override_addr, mac->sa_data, MAC_ADDR_LEN);
	}

	memcpy(dev->dev_addr, mac->sa_data, MAC_ADDR_LEN);

	mutex_lock(&hw_priv->lock);
	if (priv->port.first_port > 0)
		hw_add_addr(hw, dev->dev_addr);
	else
		hw_set_addr(hw);
	mutex_unlock(&hw_priv->lock);

	return 0;
}  /* netdev_set_mac_address */

static void dev_set_promiscuous(struct net_device *dev, struct dev_priv *priv,
	struct ksz_hw *hw, int promiscuous)
{
	if (promiscuous != priv->promiscuous) {
		u8 prev_state = hw->promiscuous;

		if (promiscuous)
			++hw->promiscuous;
		else
			--hw->promiscuous;
		priv->promiscuous = promiscuous;

		/* Turn on/off promiscuous mode. */
		if (hw->promiscuous <= 1 && prev_state <= 1)
			hw_set_promiscuous(hw, hw->promiscuous);
	}
}  /* dev_set_promiscuous */

static void dev_set_multicast(struct dev_priv *priv, struct ksz_hw *hw,
	int multicast)
{
	if (multicast != priv->multicast) {
		u8 all_multi = hw->all_multi;

		if (multicast)
			++hw->all_multi;
		else
			--hw->all_multi;
		priv->multicast = multicast;

		/* Turn on/off all multicast mode. */
		if (hw->all_multi <= 1 && all_multi <= 1)
			hw_set_multicast(hw, hw->all_multi);
	}
}  /* dev_set_multicast */

/**
 * netdev_set_rx_mode
 * @dev:	Network device.
 *
 * This routine is used to set multicast addresses or put the network device
 * into promiscuous mode.
 */
static void netdev_set_rx_mode(struct net_device *dev)
{
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_hw *hw = &hw_priv->hw;
	int multicast = (dev->flags & IFF_ALLMULTI);

	dev_set_promiscuous(dev, priv, hw, (dev->flags & IFF_PROMISC));
	multicast |= (dev->flags & IFF_MULTICAST);
	dev_set_multicast(priv, hw, multicast);
}  /* netdev_set_rx_mode */

static int netdev_change_mtu(struct net_device *dev, int new_mtu)
{
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_hw *hw = &hw_priv->hw;
	struct ksz_sw *sw = &hw_priv->sw;
	int hw_mtu;

	if (netif_running(dev))
		return -EBUSY;

	/* Cannot use different MTU in multiple device interfaces mode. */
	if (sw->dev_count > 1)
		if (dev != hw_priv->dev)
			return 0;
	if (new_mtu < 60)
		return -ERANGE;

	if (dev->mtu != new_mtu) {
		hw_mtu = new_mtu + ETHERNET_HEADER_SIZE + 4;
		if (hw_mtu > hw_priv->max_buf_size)
			return -ERANGE;
		if (hw_mtu > REGULAR_RX_BUF_SIZE) {
			hw->features |= RX_HUGE_FRAME;
			if (!(hw->features & IP_HEADER_ALIGN))
				hw_mtu = hw_priv->max_buf_size;
		} else {
			hw->features &= ~RX_HUGE_FRAME;
			if (!(hw->features & IP_HEADER_ALIGN))
				hw_mtu = REGULAR_RX_BUF_SIZE;
		}
		if (hw->features & IP_HEADER_ALIGN)
			hw_mtu += MAX_ALIGN_OFFSET;
		hw_mtu = (hw_mtu + 3) & ~3;
		hw_priv->mtu = hw_mtu;
		dev->mtu = new_mtu;
	}
	return 0;
}  /* netdev_change_mtu */

/* -------------------------------------------------------------------------- */

/*
 * MII support
 */

/**
 * mdio_read - read PHY register
 * @dev:	Network device.
 * @phy_id:	The PHY id.
 * @reg_num:	The register number.
 *
 * This function returns the PHY register value.
 *
 * Return the register value.
 */
static int mdio_read(struct net_device *dev, int phy_id, int reg_num)
{
	struct dev_priv *priv = netdev_priv(dev);
	struct ksz_port *port = &priv->port;
	u16 val_out;

	port_r_phy(port, reg_num, &val_out);
	return val_out;
}  /* mdio_read */

/**
 * mdio_write - set PHY register
 * @dev:	Network device.
 * @phy_id:	The PHY id.
 * @reg_num:	The register number.
 * @val:	The register value.
 *
 * This procedure sets the PHY register value.
 */
static void mdio_write(struct net_device *dev, int phy_id, int reg_num, int val)
{
	struct dev_priv *priv = netdev_priv(dev);
	struct ksz_port *port = &priv->port;

	port_w_phy(port, reg_num, val);
}  /* mdio_write */

/* -------------------------------------------------------------------------- */

/*
 * ethtool support
 */

#define ADVERTISED_ALL			\
	(ADVERTISED_10baseT_Half |	\
	ADVERTISED_10baseT_Full |	\
	ADVERTISED_100baseT_Half |	\
	ADVERTISED_100baseT_Full)

/* These functions use the MII functions in mii.c. */

/**
 * netdev_get_settings - get network device settings
 * @dev:	Network device.
 * @cmd:	Ethtool command.
 *
 * This function queries the PHY and returns its state in the ethtool command.
 *
 * Return 0 if successful; otherwise an error code.
 */
static int netdev_get_settings(struct net_device *dev, struct ethtool_cmd *cmd)
{
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	int rc;

	mutex_lock(&hw_priv->lock);
	rc = mii_ethtool_gset(&priv->mii_if, cmd);
	cmd->advertising |= SUPPORTED_TP;
	cmd->port = PORT_TP;
	mutex_unlock(&hw_priv->lock);

	/* Save advertised settings for workaround in next function. */
	priv->advertising = cmd->advertising;
	return rc;
}  /* netdev_get_settings */

/**
 * netdev_set_settings - set network device settings
 * @dev:	Network device.
 * @cmd:	Ethtool command.
 *
 * This function sets the PHY according to the ethtool command.
 *
 * Return 0 if successful; otherwise an error code.
 */
static int netdev_set_settings(struct net_device *dev, struct ethtool_cmd *cmd)
{
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_port *port = &priv->port;
	int rc;

	/*
	 * ethtool utility does not change advertised setting if auto
	 * negotiation is not specified explicitly.
	 */
	if (cmd->autoneg && priv->advertising == cmd->advertising) {
		cmd->advertising |= ADVERTISED_ALL;
		if (10 == cmd->speed)
			cmd->advertising &=
				~(ADVERTISED_100baseT_Full |
				ADVERTISED_100baseT_Half);
		else if (100 == cmd->speed)
			cmd->advertising &=
				~(ADVERTISED_10baseT_Full |
				ADVERTISED_10baseT_Half);
		if (0 == cmd->duplex)
			cmd->advertising &=
				~(ADVERTISED_100baseT_Full |
				ADVERTISED_10baseT_Full);
		else if (1 == cmd->duplex)
			cmd->advertising &=
				~(ADVERTISED_100baseT_Half |
				ADVERTISED_10baseT_Half);
	}
	mutex_lock(&hw_priv->lock);
	if (cmd->autoneg && (cmd->advertising & ADVERTISED_ALL) ==
			ADVERTISED_ALL) {
		port->duplex = 0;
		port->speed = 0;
		port->force_link = 0;
	} else {
		port->duplex = cmd->duplex + 1;
		if (cmd->speed != 1000)
			port->speed = cmd->speed;
		if (cmd->autoneg)
			port->force_link = 0;
		else
			port->force_link = 1;
	}
	rc = mii_ethtool_sset(&priv->mii_if, cmd);
	mutex_unlock(&hw_priv->lock);
	return rc;
}  /* netdev_set_settings */

/**
 * netdev_nway_reset - restart auto-negotiation
 * @dev:	Network device.
 *
 * This function restarts the PHY for auto-negotiation.
 *
 * Return 0 if successful; otherwise an error code.
 */
static int netdev_nway_reset(struct net_device *dev)
{
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	int rc;

	mutex_lock(&hw_priv->lock);
	rc = mii_nway_restart(&priv->mii_if);
	mutex_unlock(&hw_priv->lock);
	return rc;
}  /* netdev_nway_reset */

/**
 * netdev_get_link - get network device link status
 * @dev:	Network device.
 *
 * This function gets the link status from the PHY.
 *
 * Return true if PHY is linked and false otherwise.
 */
static u32 netdev_get_link(struct net_device *dev)
{
	struct dev_priv *priv = netdev_priv(dev);
	int rc;

	rc = mii_link_ok(&priv->mii_if);
	return rc;
}  /* netdev_get_link */

/**
 * netdev_get_drvinfo - get network driver information
 * @dev:	Network device.
 * @info:	Ethtool driver info data structure.
 *
 * This procedure returns the driver information.
 */
static void netdev_get_drvinfo(struct net_device *dev,
	struct ethtool_drvinfo *info)
{
	strcpy(info->driver, DRV_NAME);
	strcpy(info->version, DRV_VERSION);
	strcpy(info->bus_info, "AMBA");
}  /* netdev_get_drvinfo */

static struct hw_regs {
	int start;
	int end;
} hw_regs_range[] = {
	{ 0x0, 0x2C },
	{ 0x200, 0x216 },
	{ 0x400, 0x412 },
	{ 0x470, 0x4AA },
	{ 0x4D0, 0x54A },
	{ 0x12000, 0x12224 },
	{ 0x14000, 0x14040 },
	{ 0x16000, 0x16084 },
	{ 0x18000, 0x18084 },
	{ 0x1E000, 0x1E020 },
	{ 0x1E200, 0x1E234 },
	{ 0x1E400, 0x1E410 },
	{ 0x1E600, 0x1E608 },
	{ 0x1E800, 0x1E880 },
	{ 0x1EA00, 0x1EA18 },
	{ 0, 0 }
};

/**
 * netdev_get_regs_len - get length of register dump
 * @dev:	Network device.
 *
 * This function returns the length of the register dump.
 *
 * Return length of the register dump.
 */
static int netdev_get_regs_len(struct net_device *dev)
{
	struct hw_regs *range = hw_regs_range;
	int len;
	int num;
	int regs_len;

	regs_len = 0;
	while (range->end > range->start) {
		num = (range->end - range->start + 3) / 4;
		num = (num + 3) / 4;
		len = (4 * 9 + 6) * num;
		regs_len += len;
		range++;
	}
	return regs_len;
}  /* netdev_get_regs_len */

/**
 * netdev_get_regs - get register dump
 * @dev:	Network device.
 * @regs:	Ethtool registers data structure.
 * @ptr:	Buffer to store the register values.
 *
 * This procedure dumps the register values in the provided buffer.
 */
static void netdev_get_regs(struct net_device *dev, struct ethtool_regs *regs,
	void *ptr)
{
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	char *buf = ptr;
	struct hw_regs *range = hw_regs_range;
	int base;
	int i;
	int len;
	int val;

	mutex_lock(&hw_priv->lock);
	regs->version = 0;
	while (range->end > range->start) {
		base = (int) hw_priv->hw.io - (int) BASE_IO_ADDR;
		len = range->start;
		if (len >= 0x10000)
			base = -0x10000;
		while (len < range->end) {
			buf += sprintf(buf, "%04x:", base + len);
			for (i = 0; i < 4; i++, len += 4) {
				if (base < 0)
					val = KS_R(base + len);
				else
					val = readl(hw_priv->hw.io + len);
				buf += sprintf(buf, " %08x", val);
			}
			buf += sprintf(buf, "\n");
		}
		range++;
	}
	mutex_unlock(&hw_priv->lock);
}  /* netdev_get_regs */

#define WOL_SUPPORT			0

/**
 * netdev_get_wol - get Wake-on-LAN support
 * @dev:	Network device.
 * @wol:	Ethtool Wake-on-LAN data structure.
 *
 * This procedure returns Wake-on-LAN support.
 */
static void netdev_get_wol(struct net_device *dev,
	struct ethtool_wolinfo *wol)
{
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;

	wol->supported = hw_priv->wol_support;
	wol->wolopts = hw_priv->wol_enable;
	memset(&wol->sopass, 0, sizeof(wol->sopass));
}  /* netdev_get_wol */

/**
 * netdev_set_wol - set Wake-on-LAN support
 * @dev:	Network device.
 * @wol:	Ethtool Wake-on-LAN data structure.
 *
 * This function sets Wake-on-LAN support.
 *
 * Return 0 if successful; otherwise an error code.
 */
static int netdev_set_wol(struct net_device *dev,
	struct ethtool_wolinfo *wol)
{
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;

	if (wol->wolopts & ~hw_priv->wol_support)
		return -EINVAL;

	hw_priv->wol_enable = wol->wolopts;

	/* Link wakeup cannot really be disabled. */
	if (wol->wolopts)
		hw_priv->wol_enable |= WAKE_PHY;
	return 0;
}  /* netdev_set_wol */

/**
 * netdev_get_msglevel - get debug message level
 * @dev:	Network device.
 *
 * This function returns current debug message level.
 *
 * Return current debug message flags.
 */
static u32 netdev_get_msglevel(struct net_device *dev)
{
	struct dev_priv *priv = netdev_priv(dev);

	return priv->msg_enable;
}  /* netdev_get_msglevel */

/**
 * netdev_set_msglevel - set debug message level
 * @dev:	Network device.
 * @value:	Debug message flags.
 *
 * This procedure sets debug message level.
 */
static void netdev_set_msglevel(struct net_device *dev, u32 value)
{
	struct dev_priv *priv = netdev_priv(dev);

	priv->msg_enable = value;
}  /* netdev_set_msglevel */

/**
 * netdev_get_pauseparam - get flow control parameters
 * @dev:	Network device.
 * @pause:	Ethtool PAUSE settings data structure.
 *
 * This procedure returns the PAUSE control flow settings.
 */
static void netdev_get_pauseparam(struct net_device *dev,
	struct ethtool_pauseparam *pause)
{
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_hw *hw = &hw_priv->hw;
	struct ksz_sw *sw = &hw_priv->sw;

	pause->autoneg = (sw->overrides & PAUSE_FLOW_CTRL) ? 0 : 1;
	if (!sw->info) {
		pause->rx_pause =
			(hw->rx_cfg & DMA_RX_FLOW_ENABLE) ? 1 : 0;
		pause->tx_pause =
			(hw->tx_cfg & DMA_TX_FLOW_ENABLE) ? 1 : 0;
	} else {
#ifdef CONFIG_KS8695P
		pause->rx_pause =
			(sw_chk(KS_SWITCH_CTRL_1_OFFSET,
				P_SWITCH_RX_FLOW_DISABLE)) ? 0 : 1;
		pause->tx_pause =
			(sw_chk(KS_SWITCH_CTRL_1_OFFSET,
				P_SWITCH_TX_FLOW_DISABLE)) ? 0 : 1;
#else
		pause->rx_pause = pause->tx_pause = 1;
#endif
	}
}  /* netdev_get_pauseparam */

/**
 * netdev_set_pauseparam - set flow control parameters
 * @dev:	Network device.
 * @pause:	Ethtool PAUSE settings data structure.
 *
 * This function sets the PAUSE control flow settings.
 * Not implemented yet.
 *
 * Return 0 if successful; otherwise an error code.
 */
static int netdev_set_pauseparam(struct net_device *dev,
	struct ethtool_pauseparam *pause)
{
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_hw *hw = &hw_priv->hw;
	struct ksz_sw *sw = &hw_priv->sw;
	struct ksz_port *port = &priv->port;

	mutex_lock(&hw_priv->lock);
	if (pause->autoneg) {
		if (!pause->rx_pause && !pause->tx_pause)
			port->flow_ctrl = PHY_NO_FLOW_CTRL;
		else
			port->flow_ctrl = PHY_FLOW_CTRL;
		sw->overrides &= ~PAUSE_FLOW_CTRL;
		port->force_link = 0;
#ifdef CONFIG_KS8695P
		if (sw->info) {
			sw_cfg(KS_SWITCH_CTRL_1_OFFSET,
				P_SWITCH_RX_FLOW_DISABLE, 0);
			sw_cfg(KS_SWITCH_CTRL_1_OFFSET,
				P_SWITCH_TX_FLOW_DISABLE, 0);
		}
#endif
		port_set_link_speed(port);
	} else {
		sw->overrides |= PAUSE_FLOW_CTRL;
		if (sw->info) {
#ifdef CONFIG_KS8695P
			sw_cfg(KS_SWITCH_CTRL_1_OFFSET,
				P_SWITCH_RX_FLOW_DISABLE, !pause->rx_pause);
			sw_cfg(KS_SWITCH_CTRL_1_OFFSET,
				P_SWITCH_TX_FLOW_DISABLE, !pause->tx_pause);
#endif
		} else
			set_flow_ctrl(hw, pause->rx_pause, pause->tx_pause);
	}
	mutex_unlock(&hw_priv->lock);

	return 0;
}  /* netdev_set_pauseparam */

/**
 * netdev_get_ringparam - get tx/rx ring parameters
 * @dev:	Network device.
 * @pause:	Ethtool RING settings data structure.
 *
 * This procedure returns the TX/RX ring settings.
 */
static void netdev_get_ringparam(struct net_device *dev,
	struct ethtool_ringparam *ring)
{
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_hw *hw = &hw_priv->hw;

	ring->tx_max_pending = (1 << 9);
	ring->tx_pending = hw->tx_desc_info.alloc;
	ring->rx_max_pending = (1 << 9);
	ring->rx_pending = hw->rx_desc_info.alloc;
}  /* netdev_get_ringparam */

#define STATS_LEN			(TOTAL_SWITCH_COUNTER_NUM)

static struct {
	char string[ETH_GSTRING_LEN];
} ethtool_stats_keys[STATS_LEN] = {
#ifdef CONFIG_KS8695P
	{ "rx_lo_priority_octets" },
	{ "rx_hi_priority_octets" },
#endif
#ifdef CONFIG_KS8695X
	{ "rx_octets" },
#endif
	{ "rx_undersize_packets" },
	{ "rx_fragments" },
	{ "rx_oversize_packets" },
	{ "rx_jabbers" },
	{ "rx_symbol_errors" },
	{ "rx_crc_errors" },
	{ "rx_align_errors" },
	{ "rx_mac_ctrl_packets" },
	{ "rx_pause_packets" },
	{ "rx_bcast_packets" },
	{ "rx_mcast_packets" },
	{ "rx_ucast_packets" },
	{ "rx_64_or_less_octet_packets" },
	{ "rx_65_to_127_octet_packets" },
	{ "rx_128_to_255_octet_packets" },
	{ "rx_256_to_511_octet_packets" },
	{ "rx_512_to_1023_octet_packets" },
	{ "rx_1024_to_1522_octet_packets" },

#ifdef CONFIG_KS8695P
	{ "tx_lo_priority_octets" },
	{ "tx_hi_priority_octets" },
#endif
#ifdef CONFIG_KS8695X
	{ "rx_frame_len_errors" },
	{ "tx_octets" },
	{ "tx_carrier_sense_errors" },
#endif
	{ "tx_late_collisions" },
	{ "tx_pause_packets" },
	{ "tx_bcast_packets" },
	{ "tx_mcast_packets" },
	{ "tx_ucast_packets" },
	{ "tx_deferred" },
	{ "tx_total_collisions" },
	{ "tx_excessive_collisions" },
	{ "tx_single_collisions" },
	{ "tx_mult_collisions" },

	{ "rx_discards" },
	{ "tx_discards" },
#if 0
	{ "1234567890123456789012345678901" }
#endif
};

/**
 * netdev_get_strings - get statistics identity strings
 * @dev:	Network device.
 * @stringset:	String set identifier.
 * @buf:	Buffer to store the strings.
 *
 * This procedure returns the strings used to identify the statistics.
 */
static void netdev_get_strings(struct net_device *dev, u32 stringset, u8 *buf)
{
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_sw *sw = &hw_priv->sw;

	if (ETH_SS_STATS == stringset)
		memcpy(buf, &ethtool_stats_keys,
			ETH_GSTRING_LEN * sw->mib_cnt);
}  /* netdev_get_strings */

/**
 * netdev_get_sset_count - get statistics size
 * @dev:	Network device.
 * @sset:	The statistics set number.
 *
 * This function returns the size of the statistics to be reported.
 *
 * Return size of the statistics to be reported.
 */
static int netdev_get_sset_count(struct net_device *dev, int sset)
{
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_sw *sw = &hw_priv->sw;

	switch (sset) {
	case ETH_SS_STATS:
		return sw->mib_cnt;
	default:
		return -EOPNOTSUPP;
	}
}

/**
 * netdev_get_ethtool_stats - get network device statistics
 * @dev:	Network device.
 * @stats:	Ethtool statistics data structure.
 * @data:	Buffer to store the statistics.
 *
 * This procedure returns the statistics.
 */
static void netdev_get_ethtool_stats(struct net_device *dev,
	struct ethtool_stats *stats, u64 *data)
{
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_sw *sw = &hw_priv->sw;
	struct ksz_port *port = &priv->port;
	int n_stats = stats->n_stats;
	int i;
	int n;
	int p;
	int rc;
	u64 counter[TOTAL_SWITCH_COUNTER_NUM];

	mutex_lock(&hw_priv->lock);
	n = SWITCH_PORT_NUM;
	for (i = 0, p = port->first_port; i < port->mib_port_cnt; i++, p++) {
		if (media_connected == sw->port_info[p].state) {
			hw_priv->counter[p].read = 1;

			/* Remember first port that requests read. */
			if (n == SWITCH_PORT_NUM)
				n = p;
		}
	}
	mutex_unlock(&hw_priv->lock);

	if (n < SWITCH_PORT_NUM)
		schedule_work(&hw_priv->mib_read);

	if (1 == port->mib_port_cnt && n < SWITCH_PORT_NUM) {
		p = n;
		rc = wait_event_interruptible_timeout(
			hw_priv->counter[p].counter,
			2 == hw_priv->counter[p].read,
			HZ * 1);
	} else
		for (i = 0, p = n; i < port->mib_port_cnt - n; i++, p++) {
			if (0 == i) {
				rc = wait_event_interruptible_timeout(
					hw_priv->counter[p].counter,
					2 == hw_priv->counter[p].read,
					HZ * 2);
			} else if (sw->info->port_mib[p].cnt_ptr) {
				rc = wait_event_interruptible_timeout(
					hw_priv->counter[p].counter,
					2 == hw_priv->counter[p].read,
					HZ * 1);
			}
		}

	get_mib_counters(sw, port->first_port, port->mib_port_cnt, counter);
	n = sw->mib_cnt;
	if (n > n_stats)
		n = n_stats;
	n_stats -= n;
	for (i = 0; i < n; i++)
		*data++ = counter[i];
}  /* netdev_get_ethtool_stats */

static struct ethtool_ops netdev_ethtool_ops = {
	.get_settings		= netdev_get_settings,
	.set_settings		= netdev_set_settings,
	.nway_reset		= netdev_nway_reset,
	.get_link		= netdev_get_link,
	.get_drvinfo		= netdev_get_drvinfo,
	.get_regs_len		= netdev_get_regs_len,
	.get_regs		= netdev_get_regs,
	.get_wol		= netdev_get_wol,
	.set_wol		= netdev_set_wol,
	.get_msglevel		= netdev_get_msglevel,
	.set_msglevel		= netdev_set_msglevel,
	.get_pauseparam		= netdev_get_pauseparam,
	.set_pauseparam		= netdev_set_pauseparam,
	.get_ringparam		= netdev_get_ringparam,
	.get_strings		= netdev_get_strings,
	.get_sset_count		= netdev_get_sset_count,
	.get_ethtool_stats	= netdev_get_ethtool_stats,
};

enum {
	DEV_IOC_OK,
	DEV_IOC_INVALID_SIZE,
	DEV_IOC_INVALID_CMD,
	DEV_IOC_INVALID_LEN
};

enum {
	DEV_CMD_INIT,
	DEV_CMD_EXIT,
	DEV_CMD_GET,
	DEV_CMD_PUT
};

enum {
	DEV_READ_REG,
	DEV_LINK_STATUS
};

enum {
	DEV_CAPABILITIES,
	DEV_CABLE_STATUS
};

#define MAX_DATA_SIZE  2000

struct ksz_request {
	int size;
	int cmd;
	int subcmd;
	int result;
	union {
		u8 data[0];
		int num[0];
	} param;
#if 0
	union {
		u8 data[MAX_DATA_SIZE];
		int num[MAX_DATA_SIZE / sizeof(int)];
	} param;
#endif
};

#define SIOCDEVDEBUG			(SIOCDEVPRIVATE + 10)

enum {
	REG_DMA_DUMP,
	REG_DMA_STATION_DUMP,
	REG_UART_DUMP,
	REG_INT_DUMP,
	REG_TIMER_DUMP,
	REG_GPIO_DUMP,
	REG_SWITCH_DUMP,
	REG_MISC_DUMP,
	REG_SNMP_DUMP,
	DRV_VERSION_INFO,
	DUMP_PCI_SPACE,
	DUMP_BRIDGE_REG,
	MEMORY_DUMP,
	MEMORY_SEARCH,
	REG_WRITE,
	DEBUG_DUMP_TX_PACKET,
	DEBUG_DUMP_RX_PACKET,
	DEBUG_RESET_DESC,
	DEBUG_STATISTICS,
	DEBUG_DESCRIPTORS,
	DEBUG_LINK_STATUS,
	CONFIG_LINK_TYPE,
	CONFIG_STATION_EX,
	CONFIG_SWITCH_GET,
	CONFIG_SWITCH_SET,
};

enum {
	CONFIG_SW_SUBID_ON,
	CONFIG_SW_SUBID_PORT_VLAN,
	CONFIG_SW_SUBID_PRIORITY,
	CONFIG_SW_SUBID_ADV_LINK_SELECTION,
	CONFIG_SW_SUBID_ADV_CTRL,
	CONFIG_SW_SUBID_ADV_MIRRORING,
	CONFIG_SW_SUBID_ADV_THRESHOLD,
	CONFIG_SW_SUBID_ADV_DSCP,
	CONFIG_SW_SUBID_INTERNAL_LED,
	CONFIG_SW_SUBID_INTERNAL_MISC,
	CONFIG_SW_SUBID_INTERNAL_SPANNINGTREE,
	CONFIG_SW_SUBID_PHY_IF,
	CONFIG_SW_SUBID_SEC1,
	CONFIG_SW_SUBID_GENERIC_DUMP,
	CONFIG_SW_SUBID_RATE_CTRL,
};

enum {
	GENERIC_DUMP_STATIC,
	GENERIC_DUMP_DYNAMIC,
	GENERIC_DUMP_VLAN,
	GENERIC_DUMP_SWITCH_REGS,
};

#define REG_DMA_MAX			8
#define REG_DMA_STATION_MAX		32
#define REG_UART_MAX			9
#define REG_INT_MAX			14
#define REG_TIMER_MAX			5
#define REG_GPIO_MAX			3
#define REG_SWITCH_MAX			21
#define REG_MISC_MAX			7
#define REG_SNMP_MAX			138

#define DUMP_BUFFER_MAX			1024

#define SW_PHY_AUTO		0   /* autosense */
#define SW_PHY_10BASE_T		1   /* 10Base-T */
#define SW_PHY_10BASE_T_FD	2   /* 10Base-T Full Duplex */
#define SW_PHY_100BASE_TX	3   /* 100Base-TX */
#define SW_PHY_100BASE_TX_FD	4   /* 100Base-TX Full Duplex */

struct ksz8695_ioctl {
	u8 id;
	u16 len;
	union {
		u32 data[0];
		u16 word[0];
		u8 byte[0];
	} u;
};

struct ksz8695_switch_ioctl {
	u8 id;
	u16 len;
	u8 subid;
	union {
		u32 data[0];
		u16 word[0];
		u8 byte[0];
	} u;
};

#define SIOC_KS8695_DEBUG		(SIOCDEVPRIVATE + 15)

static void fill_mib_counters(struct ksz_sw *sw, u32 *counter)
{
	int mib;
	int port;
	struct ksz_port_mib *port_mib;

	for (port = 0; port < SWITCH_PORT_NUM; port++) {
		port_mib = &sw->info->port_mib[port];
		for (mib = 0; mib < SWITCH_COUNTER_NUM; mib++, counter++)
			*counter = port_mib->counter[mib];
	}
	for (port = 0; port < TOTAL_PORT_NUM; port++) {
		port_mib = &sw->info->port_mib[port];
		*counter = (u32) port_mib->counter[
			MIB_COUNTER_RX_DROPPED_PACKET];
		counter++;
		*counter = (u32) port_mib->counter[
			MIB_COUNTER_TX_DROPPED_PACKET];
		counter++;
	}
}

/*
 * ks8695_ioctl_switch
 *	This function is used to configure CONFIG_SWITCH_SUBID related
 *	functions, for web page based configuration or for ks8695_debug tool.
 *
 * Argument(s)
 *	Adapter		pointer to ADAPTER_STRUCT structure.
 *	pIoCtrl		pointer to IOCTRL_SWITCH structure.
 *
 * Return(s)
 *	0				if success
 *	negative value	if failed
 */
static int ks8695_ioctl_switch(struct ksz_sw *sw, void *data)
{
	u32 reg;
	u32 uPort;
	struct net_device *port_dev;
	struct dev_priv *priv;
	struct ksz_port *port;
	struct ksz8695_switch_ioctl *ctrl = data;
	struct ksz_sw_info *info = sw->info;
	int result = -1;
	int i;

	switch (ctrl->subid) {
	case CONFIG_SW_SUBID_ON:
		/* 1 + 2 + 1 + 4 */
		if (ctrl->len != 8)
			break;
		if (CONFIG_SWITCH_SET == ctrl->id)
			sw_cfg(KS_SWITCH_CTRL_0_OFFSET, SWITCH_ENABLE,
				ctrl->u.data[0]);
		else
			/* return current switch status */
			ctrl->u.data[0] = sw_chk(KS_SWITCH_CTRL_0_OFFSET,
				SWITCH_ENABLE);
		result = 0;
		break;

	case CONFIG_SW_SUBID_PORT_VLAN:
		/* 1 + 2 + 1 + 4 * 4 */
		if (ctrl->len != 20)
			break;
		uPort = ctrl->u.data[0];
		if (uPort >= SWITCH_PORT_NUM) {
			pr_warning("%s> LAN port out of range (%d)",
				__func__, uPort);
			break;
		}
		if (CONFIG_SWITCH_SET == ctrl->id) {
			sw_cfg_def_vid(sw, uPort, (u16) ctrl->u.data[1]);
			port_cfg_ins_tag(sw, uPort, ctrl->u.data[2]);
			sw_cfg_port_base_vlan(sw, uPort, (u8) ctrl->u.data[3]);
		} else {
			ctrl->u.data[1] = info->port_cfg[uPort].vid;
			ctrl->u.data[2] = port_chk_ins_tag(sw, uPort);
			ctrl->u.data[3] = info->port_cfg[uPort].member;
		}
		result = 0;
		break;

	case CONFIG_SW_SUBID_PRIORITY:
		/* 1 + 2 + 1 + 4 * 7 */
		if (ctrl->len != 32)
			break;
		uPort = ctrl->u.data[0];
		if (uPort >= SWITCH_PORT_NUM) {
			pr_warning("%s> LAN port out of range (%d)",
				__func__, uPort);
			break;
		}
		if (CONFIG_SWITCH_SET == ctrl->id) {
			port_cfg_diffserv(sw, uPort, ctrl->u.data[1]);
			port_cfg_802_1p(sw, uPort, ctrl->u.data[2]);
			sw_cfg_port_based(sw, uPort, ctrl->u.data[3]);
			port_cfg_prio(sw, uPort, ctrl->u.data[4]);
			port_cfg_rmv_tag(sw, uPort, ctrl->u.data[5]);
			port_cfg_broad_storm(sw, uPort, ctrl->u.data[6]);
		} else {
			ctrl->u.data[1]	= port_chk_diffserv(sw, uPort);
			ctrl->u.data[2]	= port_chk_802_1p(sw, uPort);
			ctrl->u.data[3]	= port_chk_port_based(sw, uPort);
			ctrl->u.data[4]	= port_chk_prio(sw, uPort);
			ctrl->u.data[5] = port_chk_rmv_tag(sw, uPort);
			ctrl->u.data[6]	= port_chk_broad_storm(sw, uPort);
		}
		result = 0;
		break;

	case CONFIG_SW_SUBID_ADV_LINK_SELECTION:
		/* 1 + 2 + 1 + 4 * (3 | 4) */
		if (ctrl->len < 16)
			break;
		uPort = ctrl->u.data[0];
		if (uPort >= SWITCH_PORT_NUM) {
			pr_warning("%s> LAN port out of range (%d)",
				__func__, uPort);
			break;
		}
		if (!info)
			uPort = 0;
		port_dev = sw->port_info[uPort].pdev;
		priv = netdev_priv(port_dev);
		port = &priv->port;
		if (CONFIG_SWITCH_SET == ctrl->id) {
			u32 uDuplex;

			if (ctrl->len < 20)
				uDuplex = 0;
			else
				uDuplex = ctrl->u.data[3];

			/* auto nego or forced mode */
			port->force_link = ctrl->u.data[1];
			if (port->force_link) {
				port->speed = ctrl->u.data[2];
				if (port->speed)
					port->speed = 100;
				else
					port->speed = 10;
				port->duplex = uDuplex;
				if (port->duplex)
					port->duplex = 2;
				else
					port->duplex = 1;
				if (1 != port->force_link)
					port->force_link = 0;
			} else {
				port->speed = 0;
				port->duplex = 0;
			}
			if (port->force_link)
				port_force_link_speed(port);
			else
				port_set_link_speed(port);
		} else {
			u32 uType;

			if (0 == port->speed && 0 == port->duplex)
				uType = SW_PHY_AUTO;
			else if (10 == port->speed) {
				if (1 == port->duplex)
					uType = SW_PHY_10BASE_T;
				else
					uType = SW_PHY_10BASE_T_FD;
			} else {
				if (1 == port->duplex)
					uType = SW_PHY_100BASE_TX;
				else
					uType = SW_PHY_100BASE_TX_FD;
			}
			ctrl->u.data[1] = uType;
			ctrl->u.data[2] = port->force_link;
		}
		result = 0;
		break;

	case CONFIG_SW_SUBID_ADV_CTRL:
		/* 1 + 2 + 1 + 4 * 5 */
		if (ctrl->len != 24)
			break;
		reg = KS_R(KS_SWITCH_CTRL_0_OFFSET);
		if (CONFIG_SWITCH_SET == ctrl->id) {
			if (ctrl->u.data[0])
				reg |= FAIR_FLOW_CTRL;
			else
				reg &= ~FAIR_FLOW_CTRL;
#ifdef CONFIG_KS8695P
			if (ctrl->u.data[1])
				reg |= P_SWITCH_CHECK_LENGTH;
			else
				reg &= ~P_SWITCH_CHECK_LENGTH;
#endif
			if (ctrl->u.data[2])
				reg |= SWITCH_LINK_AUTO_AGING;
			else
				reg &= ~SWITCH_LINK_AUTO_AGING;
			if (ctrl->u.data[3])
				reg |= MULTICAST_STORM_DISABLE;
			else
				reg &= ~MULTICAST_STORM_DISABLE;
			/* clear priority scheme fields, 3:2 */
			reg &= ~PRIORITY_SCHEME_SELECT;
			reg |= (ctrl->u.data[4] & 0x3) << 2;
			KS_WR(KS_SWITCH_CTRL_0_OFFSET, reg);
		} else {
			ctrl->u.data[0] = (reg & FAIR_FLOW_CTRL) ? 1 : 0;
			ctrl->u.data[1] = 0;
#ifdef CONFIG_KS8695P
			ctrl->u.data[1] = (reg & P_SWITCH_CHECK_LENGTH)
				? 1 : 0;
#endif
			ctrl->u.data[2] = (reg & SWITCH_LINK_AUTO_AGING)
				? 1 : 0;
			ctrl->u.data[3] = (reg & MULTICAST_STORM_DISABLE)
				? 1 : 0;
			ctrl->u.data[4] = (reg & PRIORITY_SCHEME_SELECT) >> 2;
		}
		result = 0;
		break;

	case CONFIG_SW_SUBID_ADV_MIRRORING:
		/* 1 + 2 + 1 + 4 * 5 */
		if (ctrl->len != 24)
			break;
		reg = KS_R(KS_SWITCH_ADVANCED_CTRL);
		/*
		 * note that the port start from 1 - 5 instead of 0 - 5
		 * used internally in the driver
		 */
		if (CONFIG_SWITCH_SET == ctrl->id) {
			/* currently, WEB page allows only on sniffer */
			reg &= 0xfffe0000;
			/* sniffer port */
			if (0 < ctrl->u.data[0] && ctrl->u.data[0] <= 5)
				reg |= (1L << (ctrl->u.data[0] - 1)) <<
					PORT_MIRROR_SNIFFER_SHIFT;
			/* Tx mirror port */
			if (0 < ctrl->u.data[1] && ctrl->u.data[1] <= 5)
				reg |= (1L << (ctrl->u.data[1] - 1)) <<
					PORT_MIRROR_TX_SHIFT;
			/* Rx mirror port */
			if (0 < ctrl->u.data[2] && ctrl->u.data[2] <= 5)
				reg |= (1L << (ctrl->u.data[2] - 1)) <<
					PORT_MIRROR_RX_SHIFT;
			/* sniffer mode, 1 for AND 0 for OR */
			if (ctrl->u.data[3])
				reg |= SWITCH_MIRROR_RX_TX;
			/* IGMP trap enable */
			if (ctrl->u.data[4])
				reg |= SWITCH_IGMP_SNOOP;
			KS_WR(KS_SWITCH_ADVANCED_CTRL, reg);
		} else {
			ctrl->u.data[0] = (reg >> PORT_MIRROR_SNIFFER_SHIFT) &
				PORT_MASK;
			ctrl->u.data[1] = (reg >> PORT_MIRROR_TX_SHIFT) &
				PORT_MASK;
			ctrl->u.data[2] = (reg >> PORT_MIRROR_RX_SHIFT) &
				PORT_MASK;
			ctrl->u.data[3] = (reg & SWITCH_MIRROR_RX_TX) ?
				1 : 0;
			ctrl->u.data[4] = (reg & SWITCH_IGMP_SNOOP) ?
				1 : 0;
		}
		result = 0;
		break;

	case CONFIG_SW_SUBID_ADV_THRESHOLD:
		/* 1 + 2 + 1 + 4 * 2 */
		if (ctrl->len != 12)
			break;
		reg = KS_R(KS_SWITCH_CTRL_1_OFFSET);
		if (CONFIG_SWITCH_SET == ctrl->id) {
			reg &= ~BROADCAST_STORM_RATE_MASK;
			reg |= (ctrl->u.data[0] &
				BROADCAST_STORM_RATE_BASE) <<
				BROADCAST_STORM_RATE_SHIFT;
			KS_W(KS_SWITCH_CTRL_1_OFFSET, reg);

			reg = KS_R(KS_SWITCH_CTRL_0_OFFSET);
			reg &= ~SWITCH_802_1P_MASK;
			reg |= (ctrl->u.data[1] &
				SWITCH_802_1P_BASE) <<
				SWITCH_802_1P_SHIFT;
			KS_WR(KS_SWITCH_CTRL_0_OFFSET, reg);
			info->p_802_1p = ctrl->u.data[1] &
				SWITCH_802_1P_BASE;
		} else {
			ctrl->u.data[0] = reg >> BROADCAST_STORM_RATE_SHIFT;
			reg = KS_R(KS_SWITCH_CTRL_0_OFFSET);
			ctrl->u.data[1] = (reg & SWITCH_802_1P_MASK) >>
				SWITCH_802_1P_SHIFT;
		}
		result = 0;
		break;

	case CONFIG_SW_SUBID_ADV_DSCP:
		/* 1 + 2 + 1 + 4 * 2 */
		if (ctrl->len != 12)
			break;
		if (CONFIG_SWITCH_SET == ctrl->id) {
			int j;
			int tos;
			u32 prio;

			KS_W(KS_TOS_PRIORITY_HI_OFFSET,	ctrl->u.data[0]);
			KS_W(KS_TOS_PRIORITY_LO_OFFSET,	ctrl->u.data[1]);
			tos = 0;
			prio = ctrl->u.data[1];
			for (i = 0; i < 2; i++) {
				for (j = 0; j < 32; j++) {
					info->diffserv[tos] = prio & 1;
					prio >>= 1;
					tos++;
				}
				prio = ctrl->u.data[0];
			}
		} else {
			ctrl->u.data[0] = KS_R(KS_TOS_PRIORITY_HI_OFFSET);
			ctrl->u.data[1] = KS_R(KS_TOS_PRIORITY_LO_OFFSET);
		}
		result = 0;
		break;

	case CONFIG_SW_SUBID_INTERNAL_LED:
		/* 1 + 2 + 1 + 4 * 2 */
		if (ctrl->len != 12)
			break;
		if (CONFIG_SWITCH_SET == ctrl->id) {
			if (ctrl->u.data[0] <= LED_LINK_ACTIVITIES &&
					ctrl->u.data[1] <=
					LED_LINK_ACTIVITIES) {
				sw_set_lan_led(ctrl->u.data[0],
					ctrl->u.data[1]);
				sw_set_wan_led(ctrl->u.data[0],
					ctrl->u.data[1]);
			} else {
				/* out of range error */
				pr_info("%s> LED setting out of range",
					__func__);
				break;
			}
		} else {
			/*
			 * note that currently, all LED use same
			 * settings, so there is no need to define port
			 * in the IF
			 */
			/* LAN */
			reg = KS_R(KS_SWITCH_CTRL_0_OFFSET);
			ctrl->u.data[0] = (reg >> LED_LAN_LED0_MODE_SHIFT) &
				LED_MODE_MASK;
			ctrl->u.data[1] = (reg >> LED_LAN_LED1_MODE_SHIFT) &
				LED_MODE_MASK;
		}
		result = 0;
		break;

	case CONFIG_SW_SUBID_INTERNAL_MISC:
		/* 1 + 2 + 1 + 4 * 10 */
		if (ctrl->len != 44)
			break;
		reg = KS_R(KS_SWITCH_CTRL_0_OFFSET);
		if (CONFIG_SWITCH_SET == ctrl->id) {
			if (ctrl->u.data[0])
				reg |= SWITCH_PASS_ALL;
			else
				reg &= ~SWITCH_PASS_ALL;
			if (ctrl->u.data[1])
				reg |= SWITCH_BUFFER_SHARE;
			else
				reg &= ~SWITCH_BUFFER_SHARE;
			if (ctrl->u.data[2])
				reg |= SWITCH_AGING_ENABLE;
			else
				reg &= ~SWITCH_AGING_ENABLE;
			if (ctrl->u.data[3])
				reg |= SWITCH_FAST_AGING;
			else
				reg &= ~SWITCH_FAST_AGING;
			if (ctrl->u.data[4])
				reg |= SWITCH_AGGR_BACKOFF;
			else
				reg &= ~SWITCH_AGGR_BACKOFF;
			if (ctrl->u.data[5])
				reg |= SWITCH_BUF_RESERVE;
			else
				reg &= ~SWITCH_BUF_RESERVE;
			if (ctrl->u.data[6])
				reg |= UNICAST_VLAN_BOUNDARY;
			else
				reg &= ~UNICAST_VLAN_BOUNDARY;
			if (ctrl->u.data[7])
				reg |= NO_EXC_COLLISION_DROP;
			else
				reg &= ~NO_EXC_COLLISION_DROP;
			if (ctrl->u.data[8])
				reg |= SWITCH_BACK_PRESSURE;
			else
				reg &= ~SWITCH_BACK_PRESSURE;
			if (ctrl->u.data[9])
				reg |= SWITCH_BACK_PRESSURE_MODE;
			else
				reg &= ~SWITCH_BACK_PRESSURE_MODE;
			KS_WR(KS_SWITCH_CTRL_0_OFFSET, reg);
		} else {
			ctrl->u.data[0] = (reg & SWITCH_PASS_ALL)
				? 1 : 0;
			ctrl->u.data[1] = (reg & SWITCH_BUFFER_SHARE)
				? 1 : 0;
			ctrl->u.data[2] = (reg & SWITCH_AGING_ENABLE)
				? 1 : 0;
			ctrl->u.data[3] = (reg & SWITCH_FAST_AGING)
				? 1 : 0;
			ctrl->u.data[4] = (reg & SWITCH_AGGR_BACKOFF)
				? 1 : 0;
			ctrl->u.data[5] = (reg & SWITCH_BUF_RESERVE)
				? 1 : 0;
			ctrl->u.data[6] = (reg & UNICAST_VLAN_BOUNDARY)
				? 1 : 0;
			ctrl->u.data[7] = (reg & NO_EXC_COLLISION_DROP)
				? 1 : 0;
			ctrl->u.data[8] = (reg & SWITCH_BACK_PRESSURE)
				? 1 : 0;
			ctrl->u.data[9] = (reg & SWITCH_BACK_PRESSURE_MODE)
				? 1 : 0;
		}
		result = 0;
		break;

	case CONFIG_SW_SUBID_INTERNAL_SPANNINGTREE:
		/* 1 + 2 + 1 + 4 * 4 */
		if (ctrl->len != 20)
			break;
		uPort = ctrl->u.data[0];
		if (uPort > SWITCH_PORT_NUM) {
			pr_info("%s> LAN port out of range (%d)",
				__func__, uPort);
			break;
		}
		port_r(uPort, KS_PORT_CTRL_1_OFFSET, &reg);
		if (CONFIG_SWITCH_SET == ctrl->id) {
			if (ctrl->u.data[1])
				reg |= PORT_TX_ENABLE;
			else
				reg &= ~PORT_TX_ENABLE;
			if (ctrl->u.data[2])
				reg |= PORT_RX_ENABLE;
			else
				reg &= ~PORT_RX_ENABLE;
			if (ctrl->u.data[3])
				reg |= PORT_LEARN_DISABLE;
			else
				reg &= ~PORT_LEARN_DISABLE;
			port_w(uPort, KS_PORT_CTRL_1_OFFSET, reg);
		} else {
			ctrl->u.data[1] = (reg & PORT_TX_ENABLE)
				? 1 : 0;
			ctrl->u.data[2] = (reg & PORT_RX_ENABLE)
				? 1 : 0;
			ctrl->u.data[3] = (reg & PORT_LEARN_DISABLE)
				? 1 : 0;
		}
		result = 0;
		break;

#ifdef CONFIG_KS8695P
	case CONFIG_SW_SUBID_PHY_IF:
	{
		u32 off;
		u32 shift = 0;

		/* 1 + 2 + 1 + 4 + 4 * 4 */
		if (ctrl->len != 24)
			break;
		uPort = ctrl->u.data[0];
		if (!info) {
			uPort = 0;
			off = KS8695_WAN_POWERMAGR;
		} else {
			if (uPort >= SWITCH_PORT_NUM) {
				pr_warning("%s> LAN port out of range (%d)",
					__func__, uPort);
				break;
			}
			if (uPort < 2)
				off = KS8695_LPPM12;
			else
				off = KS8695_LPPM34;
			if (!(uPort % 2))
				shift = 1;
		}
		reg = KS_R(off);
		if (CONFIG_SWITCH_SET == ctrl->id) {
			if (ctrl->u.data[1])
				reg |= (KS8695_LPPM_PHY_LOOPBACK <<
					(shift * 16));
			else
				reg &= ~(KS8695_LPPM_PHY_LOOPBACK <<
					(shift * 16));
			if (ctrl->u.data[2])
				reg |= (KS8695_LPPM_RMT_LOOPBACK <<
					(shift * 16));
			else
				reg &= ~(KS8695_LPPM_RMT_LOOPBACK <<
					(shift * 16));
			if (ctrl->u.data[3])
				reg |= (KS8695_LPPM_PHY_ISOLATE <<
					(shift * 16));
			else
				reg &= ~(KS8695_LPPM_PHY_ISOLATE <<
					(shift * 16));
			if (ctrl->u.data[4])
				reg |= (KS8695_LPPM_FORCE_LINK <<
					(shift * 16));
			else
				reg &= ~(KS8695_LPPM_FORCE_LINK <<
					(shift * 16));
		} else {
			ctrl->u.data[1] = (reg & (KS8695_LPPM_PHY_LOOPBACK <<
				(shift * 16))) ? 1 : 0;
			ctrl->u.data[2] = (reg & (KS8695_LPPM_RMT_LOOPBACK <<
				(shift * 16))) ? 1 : 0;
			ctrl->u.data[3] = (reg & (KS8695_LPPM_PHY_ISOLATE <<
				(shift * 16))) ? 1 : 0;
			ctrl->u.data[4] = (reg & (KS8695_LPPM_FORCE_LINK <<
				(shift * 16))) ? 1 : 0;
		}
		result = 0;
		break;
	}

	case CONFIG_SW_SUBID_SEC1:
		/* 1 + 2 + 1 + 4 * 8 */
		if (ctrl->len != 36)
			break;
		reg = KS_R(KS_SWITCH_CTRL_1_OFFSET);
		if (CONFIG_SWITCH_SET == ctrl->id) {
			if (ctrl->u.data[0])
				reg |= P_SWITCH_IEEE_AUTO_NEG;
			else
				reg &= ~P_SWITCH_IEEE_AUTO_NEG;
			if (ctrl->u.data[1])
				reg |= P_SWITCH_TPID_MODE;
			else
				reg &= ~P_SWITCH_TPID_MODE;
			if (ctrl->u.data[2])
				reg |= P_SWITCH_TX_FLOW_DISABLE;
			else
				reg &= ~P_SWITCH_TX_FLOW_DISABLE;
			if (ctrl->u.data[3])
				reg |= P_SWITCH_RX_FLOW_DISABLE;
			else
				reg &= ~P_SWITCH_RX_FLOW_DISABLE;
			if (ctrl->u.data[4])
				reg |= P_SWITCH_HUGE_PACKET;
			else
				reg &= ~P_SWITCH_HUGE_PACKET;
			if (ctrl->u.data[5])
				reg |= P_SWITCH_VLAN_ENABLE;
			else
				reg &= ~P_SWITCH_VLAN_ENABLE;
			if (ctrl->u.data[6])
				reg |= P_SWITCH_10_MBIT;
			else
				reg &= ~P_SWITCH_10_MBIT;
			if (ctrl->u.data[7])
				reg |= P_SWITCH_REPLACE_NULL_VID;
			else
				reg &= ~P_SWITCH_REPLACE_NULL_VID;
			KS_WR(KS_SWITCH_CTRL_1_OFFSET, reg);
		} else {
			ctrl->u.data[0] = (reg & P_SWITCH_IEEE_AUTO_NEG)
				? 1 : 0;
			ctrl->u.data[1] = (reg & P_SWITCH_TPID_MODE)
				? 1 : 0;
			ctrl->u.data[2] = (reg & P_SWITCH_TX_FLOW_DISABLE)
				? 1 : 0;
			ctrl->u.data[3] = (reg & P_SWITCH_RX_FLOW_DISABLE)
				? 1 : 0;
			ctrl->u.data[4] = (reg & P_SWITCH_HUGE_PACKET)
				? 1 : 0;
			ctrl->u.data[5] = (reg & P_SWITCH_VLAN_ENABLE)
				? 1 : 0;
			ctrl->u.data[6] = (reg & P_SWITCH_10_MBIT)
				? 1 : 0;
			ctrl->u.data[7] = (reg & P_SWITCH_REPLACE_NULL_VID)
				? 1 : 0;
		}
		result = 0;
		break;

	case CONFIG_SW_SUBID_GENERIC_DUMP:
		/* 1 + 2 + 1 + 4 */
		if (ctrl->len != 8)
			break;

		switch (ctrl->u.data[0]) {
		case GENERIC_DUMP_DYNAMIC:
			sw_d_dyn_mac_table(sw);
			result = 0;
			break;

		case GENERIC_DUMP_SWITCH_REGS:
			printk(KERN_INFO "--Reg--   ---Value--\n");
			for (i = KS8695_SEC0; i <= KS8695_LPPM34; i += 4)
				printk(KERN_INFO " 0x%04x   0x%08x\n", i,
					KS_R(i));
			result = 0;
			break;

		case GENERIC_DUMP_STATIC:
			sw_d_sta_mac_table(sw);
			result = 0;
			break;

		default:
		case GENERIC_DUMP_VLAN:
			pr_info("%s> not implemented yet", __func__);
			break;
		}
		break;

	case CONFIG_SW_SUBID_RATE_CTRL:
	{
		u32 tx;
		u32 rx_prio;
		u32 tx_prio;

		/* 1 + 2 + 4 * 7 */
		if (ctrl->len != 32)
			break;
		if (!sw->info)
			break;
		uPort = ctrl->u.data[0];
		if (uPort > SWITCH_PORT_NUM) {
			pr_warning("%s> LAN port out of range (%d)",
				__func__, uPort);
			break;
		}
		tx = ctrl->u.data[1];
		port_r(uPort, KS_PORT_CTRL_3_OFFSET, &rx_prio);
		port_r(uPort, KS_PORT_CTRL_2_OFFSET, &tx_prio);
		if (CONFIG_SWITCH_SET == ctrl->id) {
			if (tx) {
				sw->info->port_cfg[uPort].tx_rate[0] =
					ctrl->u.data[2] * PORT_RATE_UNIT;
				sw->info->port_cfg[uPort].tx_rate[1] =
					ctrl->u.data[3] * PORT_RATE_UNIT;
				tx_prio &= ~((PORT_PRIORITY_RATE <<
					PORT_TX_LO_RATE_SHIFT) |
					(PORT_PRIORITY_RATE <<
					PORT_TX_HI_RATE_SHIFT));
				tx_prio |= (ctrl->u.data[2] <<
					PORT_TX_LO_RATE_SHIFT) |
					(ctrl->u.data[3] <<
					PORT_TX_HI_RATE_SHIFT);
				port_w(uPort, KS_PORT_CTRL_2_OFFSET, tx_prio);
				if (ctrl->u.data[4])
					rx_prio |= PORT_TX_RATE_DIFFERENTIAL;
				else
					rx_prio &= ~PORT_TX_RATE_DIFFERENTIAL;
				if (ctrl->u.data[5])
					rx_prio |= PORT_TX_LO_RATE_ENABLE;
				else
					rx_prio &= ~PORT_TX_LO_RATE_ENABLE;
				if (ctrl->u.data[6])
					rx_prio |= PORT_TX_HI_RATE_ENABLE;
				else
					rx_prio &= ~PORT_TX_HI_RATE_ENABLE;
			} else {
				sw->info->port_cfg[uPort].rx_rate[0] =
					ctrl->u.data[2] * PORT_RATE_UNIT;
				sw->info->port_cfg[uPort].rx_rate[1] =
					ctrl->u.data[3] * PORT_RATE_UNIT;
				rx_prio &= ~((PORT_PRIORITY_RATE <<
					PORT_RX_LO_RATE_SHIFT) |
					(PORT_PRIORITY_RATE <<
					PORT_RX_HI_RATE_SHIFT));
				rx_prio |= (ctrl->u.data[2] <<
					PORT_RX_LO_RATE_SHIFT) |
					(ctrl->u.data[3] <<
					PORT_RX_HI_RATE_SHIFT);
				if (ctrl->u.data[4])
					rx_prio |= PORT_RX_RATE_DIFFERENTIAL;
				else
					rx_prio &= ~PORT_RX_RATE_DIFFERENTIAL;
				if (ctrl->u.data[5])
					rx_prio |= PORT_RX_LO_RATE_ENABLE;
				else
					rx_prio &= ~PORT_RX_LO_RATE_ENABLE;
				if (ctrl->u.data[6])
					rx_prio |= PORT_RX_HI_RATE_ENABLE;
				else
					rx_prio &= ~PORT_RX_HI_RATE_ENABLE;
			}
			port_w(uPort, KS_PORT_CTRL_3_OFFSET, rx_prio);
		} else {
			if (tx) {
				ctrl->u.data[2] =
					(tx_prio >> PORT_TX_LO_RATE_SHIFT) &
					PORT_PRIORITY_RATE;
				ctrl->u.data[3] =
					(tx_prio >> PORT_TX_HI_RATE_SHIFT) &
					PORT_PRIORITY_RATE;
				ctrl->u.data[4] =
					(rx_prio & PORT_TX_RATE_DIFFERENTIAL)
					? 1 : 0;
				ctrl->u.data[5] =
					(rx_prio & PORT_TX_LO_RATE_ENABLE)
					? 1 : 0;
				ctrl->u.data[6] =
					(rx_prio & PORT_TX_HI_RATE_ENABLE)
					? 1 : 0;
			} else {
				ctrl->u.data[2] =
					(rx_prio >> PORT_RX_LO_RATE_SHIFT) &
					PORT_PRIORITY_RATE;
				ctrl->u.data[3] =
					(rx_prio >> PORT_RX_HI_RATE_SHIFT) &
					PORT_PRIORITY_RATE;
				ctrl->u.data[4] =
					(rx_prio & PORT_RX_RATE_DIFFERENTIAL)
					? 1 : 0;
				ctrl->u.data[5] =
					(rx_prio & PORT_RX_LO_RATE_ENABLE)
					? 1 : 0;
				ctrl->u.data[6] =
					(rx_prio & PORT_RX_HI_RATE_ENABLE)
					? 1 : 0;
			}
		}
		result = 0;
		break;
	}
#endif

	default:
		pr_info("%s> unsupported parameters: id=%d, len=%d",
			__func__, ctrl->id, ctrl->len);
		return -EOPNOTSUPP;
	}

	return result;
}  /* ks8695_ioctl_switch */

static void print_link(struct ksz_port *port, struct ksz_port_info *info,
	int index)
{
	char name[16];
	int linked = (media_connected == info->state);

	if (index)
		sprintf(name, "Port[%d] ", index);
	else if (linked)
		sprintf(name, "Link=Up,");
	else
		sprintf(name, "Link=Down,");
	if (linked)
		printk(KERN_INFO
			"%s Speed=%u, Duplex (read)=%s, Duplex (detected)=%s\n",
			name, info->tx_rate / TX_RATE_UNIT,
			1 != port->duplex ? "Full Duplex" : "Half Duplex",
			2 == info->duplex ? "Full Duplex" : "Half Duplex");
	else
		printk(KERN_INFO "%s Speed=Unknown, Duplex=Unknown\n", name);
}

static int ks8695_ioctl_debug(struct dev_priv *priv, void *data)
{
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_hw *hw = &hw_priv->hw;
	struct ksz_sw *sw = &hw_priv->sw;
	struct ksz8695_ioctl *ctrl = data;
	struct net_device *port_dev;
	struct ksz_port *port;
	struct ksz_port_info *port_info;
	int result = -1;
	int i;
	int len;
	u32 *val;
	u32 *pReg;
	u32 uPort;

	switch (ctrl->id) {
	case REG_DMA_DUMP:
		/* 1 + 2 + 4 + 8 * 4 */
		if (ctrl->len >= (4 * (1 + REG_DMA_MAX) + 3)) {
			val = ctrl->u.data;
			/* Tell debug application its offset. */
			*val++ = hw_priv->mem_start;
			for (i = KS_DMA_TX_CTRL; i <= KS_DMA_MAC_ADDR_HI;
					i += 4)
				*val++ = readl(hw->io + i);
			result = 0;
		}
		break;

	case REG_DMA_STATION_DUMP:
		/* 1 + 2 + 16 * 2 * 4 */
		if (ctrl->len >= (4 * REG_DMA_STATION_MAX + 3)) {
			val = ctrl->u.data;
			for (i = KS_ADD_ADDR_0_LO; i <= KS_ADD_ADDR_F_LO;
					i += 8) {
				*val++ = readl(hw->io + i);
				*val++ = readl(hw->io + i + 4);
			}
			result = 0;
		}
		break;

	case REG_UART_DUMP:
		/* 1 + 2 + 9 * 4 */
		if (ctrl->len >= (4 * REG_UART_MAX + 3)) {
			val = ctrl->u.data;
			for (i = KS8695_UART_RX_BUFFER;
					i <= KS8695_UART_STATUS; i += 4)
				*val++ = KS_R(i);
			result = 0;
		}
		break;

	case REG_INT_DUMP:
		/* 1 + 2 + 14 * 4 */
		if (ctrl->len >= (4 * REG_INT_MAX + 3)) {
			val = ctrl->u.data;
			for (i = KS8695_INT_CONTL;
					i <= KS8695_IRQ_PEND_PRIORITY; i += 4)
				*val++ = KS_R(i);
			result = 0;
		}
		break;

	/* Timer receive related */
	case REG_TIMER_DUMP:
		/* 1 + 2 + 5 * 4 */
		if (ctrl->len >= (4 * REG_TIMER_MAX + 3)) {
			val = ctrl->u.data;
			for (i = KS8695_TIMER_CTRL; i <= KS8695_TIMER0_PCOUNT;
					i += 4)
				*val++ = KS_R(i);
			result = 0;
		}
		break;

	/* GPIO receive related */
	case REG_GPIO_DUMP:
		/* 1 + 2 + 3 * 4 */
		if (ctrl->len >= (4 * REG_GPIO_MAX + 3)) {
			val = ctrl->u.data;
			for (i = KS8695_GPIO_MODE; i <= KS8695_GPIO_DATA;
					i += 4)
				*val++ = KS_R(i);
			result = 0;
		}
		break;

	case REG_SWITCH_DUMP:
		/* 1 + 2 + 21 * 4 */
		if (ctrl->len >= (4 * REG_SWITCH_MAX + 3)) {
			val = ctrl->u.data;
			for (i = KS8695_SWITCH_CTRL0;
					i <= KS8695_LAN34_POWERMAGR; i += 4)
				*val++ = KS_R(i);
			result = 0;
		}
		break;

	case REG_MISC_DUMP:
		/* 1 + 2 + 7 * 4 */
		if (ctrl->len >= (4 * REG_MISC_MAX + 3)) {
			val = ctrl->u.data;
			for (i = KS8695_DEVICE_ID; i <= KS8695_WAN_PHY_STATUS;
					i += 4)
				*val++ = KS_R(i);
			result = 0;
		}
		break;

	case REG_SNMP_DUMP:
		if (!sw->info)
			break;

		/* 138 * 4 */
		if (ctrl->len >= (4 * REG_SNMP_MAX)) {
			fill_mib_counters(sw, ctrl->u.data);
			result = 0;
		}
		break;

	case DRV_VERSION_INFO:
	{
		char name[40];

#ifdef CONFIG_KS8695P
		strcpy(name, "95P");
#else
		strcpy(name, "95X");
#endif

		/* 1 + 2 + 16 */
		if (ctrl->len >= 19) {
			sprintf(ctrl->u.byte, "%s, %s",
				DRV_VERSION, name);
			result = 0;
		}
		break;
	}

#ifdef CONFIG_KS8695P
	case DUMP_PCI_SPACE:
		/* 1 + 2 + 1 */
		if (ctrl->len < sizeof(struct ksz8695_ioctl))
			break;
		i = 0;
		printk(KERN_INFO "----- PCI conf Space -----\n");
		printk(KERN_INFO "0x%04x          0x%08x\n", i,
			KS_R(KS8695_2000));
		i += 4;
		printk(KERN_INFO "0x%04x          0x%08x\n", i,
			KS_R(KS8695_2004));
		i += 4;
		printk(KERN_INFO "0x%04x          0x%08x\n", i,
			KS_R(KS8695_2008));
		i += 4;
		printk(KERN_INFO "0x%04x          0x%08x\n", i,
			KS_R(KS8695_200C));
		i += 4;
		printk(KERN_INFO "0x%04x          0x%08x\n", i,
			KS_R(KS8695_2010));
		i += 4;
		printk(KERN_INFO "0x%04x          0x%08x\n", i,
			KS_R(KS8695_2014));
		i = 0x2c;
		printk(KERN_INFO "0x%04x          0x%08x\n", i,
			KS_R(KS8695_202C));
		i = 0x3c;
		printk(KERN_INFO "0x%04x          0x%08x\n", i,
			KS_R(KS8695_203C));
		result = 0;
		break;

	case DUMP_BRIDGE_REG:
		/* 1 + 2 + 1 + 1 (optional) */
		if (ctrl->len < sizeof(struct ksz8695_ioctl))
			break;
		printk(KERN_INFO "----- Bridge Conf Registers -----\n");
		i = KS8695_2100;
		printk(KERN_INFO "0x%04x          0x%08x\n", i, KS_R(i));
		i = KS8695_2104;
		printk(KERN_INFO "0x%04x          0x%08x\n", i, KS_R(i));
		i = KS8695_2200;
		printk(KERN_INFO "0x%04x          0x%08x\n", i, KS_R(i));
		i = KS8695_2204;
		printk(KERN_INFO "0x%04x          0x%08x\n", i, KS_R(i));
		i = KS8695_2208;
		printk(KERN_INFO "0x%04x          0x%08x\n", i, KS_R(i));
		i = KS8695_220C;
		printk(KERN_INFO "0x%04x          0x%08x\n", i, KS_R(i));
		i = KS8695_2210;
		printk(KERN_INFO "0x%04x          0x%08x\n", i, KS_R(i));
		i = KS8695_2214;
		printk(KERN_INFO "0x%04x          0x%08x\n", i, KS_R(i));
		i = KS8695_2218;
		printk(KERN_INFO "0x%04x          0x%08x\n", i, KS_R(i));
		i = KS8695_221C;
		printk(KERN_INFO "0x%04x          0x%08x\n", i, KS_R(i));
		i = KS8695_2220;
		printk(KERN_INFO "0x%04x          0x%08x\n", i, KS_R(i));
		i = KS8695_2224;
		printk(KERN_INFO "0x%04x          0x%08x\n", i, KS_R(i));
		result = 0;
		break;
#endif
	case MEMORY_DUMP:
		/* dump 32 dwords each time */
		/* 1 + 2 + 1 + 1 (optional) */
		if (ctrl->len >= (4 * 32 + 3)) {
			u32 *pReg1;

			pReg = ctrl->u.data;
			pReg1 = (u32 *)(*pReg);

			/* if no null pointer */
			if (pReg1 && (0xc0000000 ==
					((uint) pReg1 & 0xc0000000))) {
				for (i = 0; i <= 32; i++, pReg++, pReg1++)
					*pReg = *pReg1;
				result = 0;
			} else {
				pr_info("%s> invalid address: 0x%08x",
					__func__, *pReg1);
				result = -EINVAL;
			}
		}
		break;

	case MEMORY_SEARCH:
		/* dump 32 dwords each time */
		/* 1 + 2 + optional length */
		if (ctrl->len > 3 && ctrl->len < 128) {
			pr_info("%s> not implemented yet", __func__);
			result = 0;
		}
		break;

	case REG_WRITE:
		/* write control register */
		/* 1 + 2 + 1 * 4 */
		if (ctrl->len >= 7) {
			u32 reg;

			reg = ctrl->u.data[0];
			if (reg >= 0xffff)
				return -EINVAL;
			/*
			 * If no parameter is given, display register value
			 * instead.
			 */
			if (ctrl->len < 11)
				printk(KERN_INFO "Reg(0x%04x) = 0x%08x", reg,
					KS_R(reg));
			else
				KS_W(reg, ctrl->u.data[1]);
			result = 0;
		}
		break;

	case DEBUG_DUMP_TX_PACKET:
		/* set dump tx packet flag */
		/* 1 + 2 + 4 */
		if (ctrl->len >= 7) {
#ifndef	PACKET_DUMP
			pr_info("%s> DumpTxPkt was disabled", __func__);
#endif
			result = 0;
		}
		break;

	case DEBUG_DUMP_RX_PACKET:
		/* set dump rx packet flag */
		/* 1 + 2 + 4 */
		if (ctrl->len >= 7) {
#ifndef	PACKET_DUMP
			pr_info("%s> DumpRxPkt was disabled", __func__);
#endif
			result = 0;
		}
		break;

	case DEBUG_RESET_DESC:
		/* 1 + 2 */
		if (ctrl->len == 3)
			result = 0;
		break;

	case DEBUG_STATISTICS:
		/* printout statistical counters */
		/* 1 + 2 */
		if (ctrl->len != 3)
			break;

		printk(KERN_INFO "------- statistics TX -------\n");
		printk(KERN_INFO "tx_packets      = %12lu\n",
			priv->stats.tx_packets);
		printk(KERN_INFO "tx_bytes        = %12lu\n",
			priv->stats.tx_bytes);
		printk(KERN_INFO "tx_dropped      = %12lu\n",
			priv->stats.tx_dropped);
		printk(KERN_INFO "tx_errors       = %12lu\n",
			priv->stats.tx_errors);

		printk(KERN_INFO "------- statistics RX -------\n");
		printk(KERN_INFO "rx_packets      = %12lu\n",
			priv->stats.rx_packets);
		printk(KERN_INFO "rx_bytes        = %12lu\n",
			priv->stats.rx_bytes);
		printk(KERN_INFO "rx_dropped      = %12lu\n",
			priv->stats.rx_dropped);
		printk(KERN_INFO "rx_errors       = %12lu\n",
			priv->stats.rx_errors);
		printk(KERN_INFO "rx_length_errors= %12lu\n",
			priv->stats.rx_length_errors);
		printk(KERN_INFO "rx_crc_errors   = %12lu\n",
			priv->stats.rx_crc_errors);
		printk(KERN_INFO "collisions      = %12lu\n",
			priv->stats.collisions);
		printk(KERN_INFO "multicast       = %12lu\n",
			priv->stats.multicast);
		printk(KERN_INFO "rx_missed_errors= %12lu\n",
			priv->stats.rx_missed_errors);
		printk(KERN_INFO "rx_length_errors= %12lu\n",
			priv->stats.rx_length_errors);
		result = 0;
		break;

	case DEBUG_DESCRIPTORS:
		/* printout descriptors info */
		/* 1 + 2 */
		if (ctrl->len != 3)
			break;

		printk(KERN_INFO "------ TX Descriptors ------\n");
		printk(KERN_INFO "descriptor VA   = 0x%p\n",
			hw->tx_desc_info.ring_virt);
		printk(KERN_INFO "total           = %10d\n",
			hw->tx_desc_info.alloc);
		printk(KERN_INFO "available       = %10d\n",
			hw->tx_desc_info.avail);
		printk(KERN_INFO "next available  = %10d\n",
			hw->tx_desc_info.next);
		printk(KERN_INFO "------ RX Descriptors ------\n");
		printk(KERN_INFO "descriptor VA   = 0x%p\n",
			hw->rx_desc_info.ring_virt);
		printk(KERN_INFO "total           = %10d\n",
			hw->rx_desc_info.alloc);
		printk(KERN_INFO "next available  = %10d\n",
			hw->rx_desc_info.next);
		result = 0;
		break;

	case DEBUG_LINK_STATUS:
	{
		int linked;

		/* printout link status */
		/* 1 + 2 */
		if (ctrl->len < 3)
			break;

		if (!sw->info) {
			port_info = &sw->port_info[0];
			linked = (media_connected == port_info->state);

			/* 3 + 3 * 4 */
			if (ctrl->len == 15) {
				pReg = ctrl->u.data;

				/* link active */
				*pReg++ = linked;
				if (!linked) {
					/* speed */
					*pReg++ = 0;
					/* duplex */
					*pReg = 0;
				} else {
					*pReg++ = port_info->tx_rate;
					*pReg++ = (1 ==	port_info->duplex);
				}
			/* for back compatible with ks8695_debug utility */
			} else
				print_link(&priv->port, port_info, 0);
		} else {
			/* 3 + 3 * 4 * 4 = 51 */
			len = 3 + 3 * 4 * SWITCH_PORT_NUM;
			if (ctrl->len == len) {
				pReg = ctrl->u.data;
				for (i = 0; i < SWITCH_PORT_NUM; i++) {
					port_info = &sw->port_info[i];
					linked = (media_connected ==
						port_info->state);

					/* link active */
					*pReg++ = linked;
					if (!linked) {
						/* speed */
						*pReg++ = 0;
						/* duplex */
						*pReg++ = 0;
					} else {
						*pReg++ = port_info->tx_rate;
						*pReg++ = (1 ==
							port_info->duplex);
					}
				}
			} else {
				for (i = 0; i < SWITCH_PORT_NUM; i++) {
					port_info = &sw->port_info[i];
					port_dev = port_info->pdev;
					priv = netdev_priv(port_dev);
					print_link(&priv->port, port_info,
						i + 1);
				}
			}
		}
		result = 0;
		break;
	}

	case CONFIG_LINK_TYPE:
		/* configure link media type (forced mode without auto nego) */
		/* 1 + 2 + 4 * 4*/
		if (ctrl->len != 19)
			break;

			pReg = ctrl->u.data;

		pReg = ctrl->u.data;
		if (!sw->info) {
			port = &priv->port;
			uPort = 0;
			pReg++;
		} else {
			uPort = *pReg++;
			if (uPort >= SWITCH_PORT_NUM) {
				pr_warning("%s> LAN port out of range (%d)",
					__func__, uPort);
				break;
			}
			port_dev = sw->port_info[uPort].pdev;
			priv = netdev_priv(port_dev);
			port = &priv->port;
		}
		port->force_link = *pReg++;
		if (port->force_link) {
			port->speed = *pReg++;
			if (port->speed)
				port->speed = 100;
			else
				port->speed = 10;
			port->duplex = *pReg;
			if (port->duplex)
				port->duplex = 2;
			else
				port->duplex = 1;
			if (1 != port->force_link)
				port->force_link = 0;
		} else {
			port->speed = 0;
			port->duplex = 0;
		}
		if (port->force_link)
			port_force_link_speed(port);
		else
			port_set_link_speed(port);
		result = 0;
		break;

	case CONFIG_STATION_EX:
		/* 1 + 2 + 4 + 6 */
		if (ctrl->len == 13) {

			/* uData[0] = set, byData[4-9] = mac address */
			if (ctrl->u.data[0]) {
				if (!hw_add_addr(hw, &ctrl->u.byte[4]))
					result = 0;
			} else {
				hw_del_addr(hw, &ctrl->u.byte[4]);
				result = 0;
			}
		}
		break;

	case CONFIG_SWITCH_GET:
	case CONFIG_SWITCH_SET:
		/* for LAN driver only */
		if (sw->info || CONFIG_SW_SUBID_ADV_LINK_SELECTION ==
				((struct ksz8695_switch_ioctl *) data)->subid)
			return ks8695_ioctl_switch(sw, data);
		else
			/* filter out the IF supported for WAN */
			return -EPERM;
		break;

	default:
		pr_info("%s> unsupported parameters: id=%d, len=%d\n",
			__func__, ctrl->id, ctrl->len);
		return -EOPNOTSUPP;
	}
	return result;
}  /* ks8695_ioctl_debug */

/**
 * netdev_ioctl - I/O control processing
 * @dev:	Network device.
 * @ifr:	Interface request structure.
 * @cmd:	I/O control code.
 *
 * This function is used to process I/O control calls.
 *
 * Return 0 to indicate success.
 */
static int netdev_ioctl(struct net_device *dev, struct ifreq *ifr, int cmd)
{
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_port *port = &priv->port;
	struct ksz_request *req = ifr->ifr_data;
	int rc;
	int result = 0;
	struct mii_ioctl_data *data = if_mii(ifr);

	if (!ifr->ifr_data)
		return -EFAULT;

	if (down_interruptible(&hw_priv->proc_sem))
		return -ERESTARTSYS;

	/* assume success */
	rc = DEV_IOC_OK;
	switch (cmd) {
	/* Get address of MII PHY in use. */
	case SIOCGMIIPHY:
	/* for binary compat, remove in 2.5 */
	case SIOCDEVPRIVATE:
		data->phy_id = priv->id;

		/* Fallthrough... */

	/* Read MII PHY register. */
	case SIOCGMIIREG:
	/* for binary compat, remove in 2.5 */
	case SIOCDEVPRIVATE+1:
		if (data->phy_id != priv->id || data->reg_num >= 6)
			result = -EIO;
		else
			port_r_phy(port, data->reg_num, &data->val_out);
		break;

	/* Write MII PHY register. */
	case SIOCSMIIREG:
	/* for binary compat, remove in 2.5 */
	case SIOCDEVPRIVATE+2:
		if (!capable(CAP_NET_ADMIN))
			result = -EPERM;
		else if (data->phy_id != priv->id || data->reg_num >= 6)
			result = -EIO;
		else
			port_w_phy(port, data->reg_num, data->val_in);
		break;

	case SIOCDEVDEBUG:
		if (req) {
			switch (req->cmd) {
			case DEV_CMD_INIT:
				req->param.data[0] = 'M';
				req->param.data[1] = 'i';
				req->param.data[2] = 'c';
				req->param.data[3] = 'r';
				req->size = 8 + 4;
				break;
			case DEV_CMD_GET:
				switch (req->subcmd) {
				case DEV_READ_REG:
					break;
				}
				break;
			case DEV_CMD_PUT:
				break;
			default:
				rc = DEV_IOC_INVALID_CMD;
				break;
			}
		}
		if (req)
			req->result = rc;
		else if (!result)
			result = -EFAULT;
		break;
	case SIOC_KS8695_DEBUG:
		result = ks8695_ioctl_debug(priv, ifr->ifr_data);
		break;
	default:
		result = -EOPNOTSUPP;
	}

	up(&hw_priv->proc_sem);

	return result;
}  /* netdev_ioctl */

/* -------------------------------------------------------------------------- */

/*
 * Hardware monitoring
 */

static void update_link(struct net_device *dev, struct dev_priv *priv,
	struct ksz_port *port)
{
	if (priv->media_state != port->linked->state) {
		priv->media_state = port->linked->state;
		if (netif_running(dev))
			set_media_state(dev, media_connected);
	}
}  /* update_link */

#ifdef CONFIG_KSZ8695_STP
u8 get_port_state(struct net_device *dev, struct net_device **br_dev)
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

static void monitor_ports(struct ksz_sw *sw)
{
	int port;
	struct net_device *bridge_dev = NULL;
	struct ksz_sw_info *info = sw->info;
	u8 member = info->member;
	u8 stp = info->stp;
	u8 prev_stp = info->stp;
	u8 state;

	for (port = 0; port < SWITCH_PORT_NUM; port++) {
		struct net_device *dev = sw->port_info[port].pdev;
		struct dev_priv *priv = netdev_priv(dev);

		state = get_port_state(dev, &bridge_dev);
		if (state != STP_STATE_SIMPLE)
			stp |= (1 << port);
		else {
			stp &= ~(1 << port);
			state = priv->state;
		}
		if (stp != info->stp) {
			info->stp = stp;
			if (!(stp & (1 << port))) {
				if (netif_running(dev))
					state = STP_STATE_SIMPLE;
			}
		}
		priv->state = state;

		if (info->port_cfg[port].stp_state != state) {
			if (STP_STATE_FORWARDING ==
					info->port_cfg[port].stp_state)
				member &= ~(1 << port);
			if (STP_STATE_FORWARDING == state)
				member |= (1 << port);
			port_set_stp_state(sw, port, state);
			if (STP_STATE_LEARNING == state)
				sw_flush_dyn_mac_table(sw);
		}
	}
	if (prev_stp != info->stp && !info->stp)
		memset(info->br_addr, 0, MAC_ADDR_LEN);

	if (member != info->member) {

		/* Have first member. */
		if (!info->member) {
			port_set_stp_state(sw, SWITCH_PORT_NUM,
				STP_STATE_BLOCKED);

			/* Force to program bridge address. */
			info->br_addr[0] = 0xFF;
		}
		info->member = member;
		bridge_change(sw);
	}

	/* At least one port in forwarding state. */
	if (info->member && bridge_dev && memcmp(bridge_dev->dev_addr,
			info->br_addr, MAC_ADDR_LEN)) {
		memcpy(info->br_addr, bridge_dev->dev_addr, MAC_ADDR_LEN);
		sw_pass_addr(sw);
	}
}  /* monitor_ports */
#else
static inline void monitor_ports(struct ksz_sw *sw) {}
#endif

static void mib_read_work(struct work_struct *work)
{
	struct dev_info *hw_priv =
		container_of(work, struct dev_info, mib_read);
	struct ksz_sw *sw = &hw_priv->sw;
	struct ksz_port_mib *mib;
	int i;

	next_jiffies = jiffies;
	for (i = 0; i < sw->mib_port_cnt; i++) {
		mib = &sw->info->port_mib[i];

		/* Reading MIB counters or requested to read. */
		if (mib->cnt_ptr || 1 == hw_priv->counter[i].read) {

			/* Need to process receive interrupt. */
			if (port_r_cnt(sw, i))
				break;
			hw_priv->counter[i].read = 0;

			/* Finish reading counters. */
			if (0 == mib->cnt_ptr) {
				hw_priv->counter[i].read = 2;
				wake_up_interruptible(
					&hw_priv->counter[i].counter);
			}
		} else if (jiffies >= hw_priv->counter[i].time) {
			/* Only read MIB counters when the port is connected. */
			if (media_connected == sw->port_info[i].state)
				hw_priv->counter[i].read = 1;

			/* Read dropped counters. */
			else
				mib->cnt_ptr = SWITCH_COUNTER_NUM;
			next_jiffies += HZ * 1 * sw->mib_port_cnt;
			hw_priv->counter[i].time = next_jiffies;

		/* Port is just disconnected. */
		} else if (sw->port_info[i].link_down) {
			sw->port_info[i].link_down = 0;

			/* Read counters one last time after link is lost. */
			hw_priv->counter[i].read = 1;
		}
	}
}  /* mib_read_work */

static void mib_monitor(unsigned long ptr)
{
	struct dev_info *hw_priv = (struct dev_info *) ptr;

	schedule_work(&hw_priv->mib_read);

	ksz_update_timer(&hw_priv->mib_timer_info);
}  /* mib_monitor */

/**
 * dev_monitor - periodic monitoring
 * @ptr:	Network device pointer.
 *
 * This routine is run in a kernel timer to monitor the network device.
 */
static void dev_monitor(unsigned long ptr)
{
	struct net_device *dev = (struct net_device *) ptr;
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_hw *hw = &hw_priv->hw;
	struct ksz_sw *sw = &hw_priv->sw;
	struct ksz_port *port = &priv->port;

	if (!(hw->features & LINK_INT_WORKING))
		port_get_link_speed(port);
	update_link(dev, priv, port);

	/* Monitor the ports for user bridge changes. */
	if (sw->features & STP_SUPPORT)
		monitor_ports(sw);

	ksz_update_timer(&priv->monitor_timer_info);
}  /* dev_monitor */

/* -------------------------------------------------------------------------- */

#define KSZ8695_REGS_SIZE	0x10000

static int check_hw_reg_range(unsigned addr)
{
	struct hw_regs *range = hw_regs_range;

	addr += 0x10000;
	while (range->end > range->start) {
		if (range->start <= addr && addr <= range->end)
			return true;
		range++;
	}
	return false;
}

static ssize_t ksz8695_registers_read(struct file *filp, struct kobject *kobj,
	struct bin_attribute *bin_attr, char *buf, loff_t off, size_t count)
{
	size_t i;
	u32 *addr;
	u16 *addr_16;
	u8 *addr_8;
	u32 reg;
#if 0
	struct device *dev = container_of(kobj, struct device, kobj);
	struct net_device *ndev = container_of(dev, struct net_device, dev);
#endif

	if (unlikely(off > KSZ8695_REGS_SIZE))
		return 0;

	if ((off + count) > KSZ8695_REGS_SIZE)
		count = KSZ8695_REGS_SIZE - off;

	if (unlikely(!count))
		return count;

	reg = off;
	addr = (u32 *) buf;
	addr_16 = (u16 *) buf;
	addr_8 = (u8 *) buf;
	for (i = 0; i < count; i += 4, reg += 4, addr++) {
		*addr = 0;
		if (check_hw_reg_range(reg & ~3)) {
			int shift;
			u32 data = KS_R(reg & ~3);

			/* Return value in register with 32-bit boundary. */
			if (count == 4) {
				shift = reg & 3;
				if (shift == 2)
					count = 2;
				else if (shift)
					count = 1;
			}
			if (count >= 4)
				*addr = data;
			else if (count >= 2) {
				shift = reg & 2;
				shift *= 8;
				*addr_16 = (u16)(data >> shift);
			} else {
				shift = reg & 3;
				shift *= 8;
				*addr_8 = (u8)(data >> shift);
			}
		}
	}
	return i;
}

static ssize_t ksz8695_registers_write(struct file *filp, struct kobject *kobj,
	struct bin_attribute *bin_attr, char *buf, loff_t off, size_t count)
{
	size_t i;
	u32 *addr;
	u16 *addr_16;
	u8 *addr_8;
	u32 reg;
#if 0
	struct device *dev = container_of(kobj, struct device, kobj);
	struct net_device *ndev = container_of(dev, struct net_device, dev);
#endif

	if (unlikely(off >= KSZ8695_REGS_SIZE))
		return -EFBIG;

	if ((off + count) > KSZ8695_REGS_SIZE)
		count = KSZ8695_REGS_SIZE - off;

	if (unlikely(!count))
		return count;

	reg = off;
	addr = (u32 *) buf;
	addr_16 = (u16 *) buf;
	addr_8 = (u8 *) buf;
	for (i = 0; i < count; i += 4, reg += 4, addr++) {
		if (check_hw_reg_range(reg & ~3)) {
			int shift;

			if (count == 4) {
				shift = reg & 3;
				if (shift == 2)
					count = 2;
				else if (shift)
					count = 1;
			}
			if (count >= 4)
				KS_W(reg, *addr);
			else {
				u32 data = KS_R(reg & ~3);

				if (count >= 2) {
					shift = reg & 2;
					shift *= 8;
					data &= ~(0xffff << shift);
					data |= (*addr_16 << shift);
				} else {
					shift = reg & 3;
					shift *= 8;
					data &= ~(0xff << shift);
					data |= (*addr_8 << shift);
				}
				KS_W(reg & ~3, data);
			}
		}
	}
	return i;
}

static struct bin_attribute ksz8695_registers_attr = {
	.attr = {
		.name	= "registers",
		.mode	= S_IRUSR | S_IWUSR,
	},
	.size	= KSZ8695_REGS_SIZE,
	.read	= ksz8695_registers_read,
	.write	= ksz8695_registers_write,
};

/* -------------------------------------------------------------------------- */

enum {
	FOR_ALL,
	FOR_WAN,
	FOR_OUT,
	FOR_LAN = TOTAL_PORT_NUM
};

struct all_attributes {
	int info;
	int duplex;
	int speed;
	int force;
	int flow_ctrl;
	int features;
	int overrides;
};

struct lan_attributes {
	int info;
	int duplex;
	int speed;
	int force;
	int flow_ctrl;
	int features;
	int overrides;
	int ports;
	int mib;
	int reg;
	int dynamic_table;
	int static_table;
	int vlan_table;
	int aging;
	int fast_aging;
	int link_aging;
	int bcast_per;
	int mcast_storm;
	int v_diffserv;
	int v_802_1p;
	int vlan;
	int null_vid;
	int macaddr;
	int mirror_mode;
	int igmp_snoop;
	int aggr_backoff;
	int no_exc_drop;
	int buf_reserve;
	int buf_share;
	int huge_packet;
	int legal_packet;
	int length_check;
	int back_pressure;
	int sw_back_pressure;
	int sw_flow_ctrl;
	int sw_10_mbit;
	int rx_flow_ctrl;
	int tx_flow_ctrl;
	int fair_flow_ctrl;
	int vlan_bound;
	int pass_all;
	int priority_scheme;
};

struct sw_attributes {
	int mib;
	int vid;
	int member;
	int bcast_storm;
	int diffserv;
	int p_802_1p;
	int port_based;
	int non_vid;
	int ingress;
	int ins_tag;
	int rmv_tag;
	int rx;
	int tx;
	int learn;
	int prio_queue;
	int prio_rate;
	int rx_p0_rate;
	int rx_p1_rate;
	int tx_p0_rate;
	int tx_p1_rate;
	int mirror_port;
	int mirror_rx;
	int mirror_tx;
	int back_pressure;
	int force_flow_ctrl;
	int duplex;
	int speed;
};

struct static_mac_attributes {
	int fid;
	int use_fid;
	int override;
	int valid;
	int ports;
	int addr;
};

#ifdef CONFIG_KS8695P
struct vlan_attributes {
	int valid;
	int member;
	int fid;
	int vid;
};
#endif

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
	len += sprintf(buf + len, "v_diffserv:\t");
	len += sprintf(buf + len,
		"set DiffServ value.  Use \"decimal=hexadecimal\" format\n");
	len += sprintf(buf + len, "v_802_1p:\t");
	len += sprintf(buf + len,
		"set 802.1p value\n");
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
	len += sprintf(buf + len, "length_check:\t");
	len += sprintf(buf + len,
		"disable/enable legal packet length check\n");

	len += sprintf(buf + len, "\nback_pressure:\t");
	len += sprintf(buf + len,
		"set back pressure mode\n");
	len += sprintf(buf + len, "sw_flow_ctrl:\t");
	len += sprintf(buf + len,
		"disable/enable switch host port flow control\n");
	len += sprintf(buf + len, "sw_10_mbit:\t");
	len += sprintf(buf + len,
		"disable/enable switch host port 10Mbit mode\n");
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

	len += sprintf(buf + len, "\npass_all:\t");
	len += sprintf(buf + len,
		"set to 1 to pass all frames for debugging\n");
	printk(KERN_INFO "%s", buf);
	len = 0;

	len += sprintf(buf + len, "\nswitch port settings:\n");
	len += sprintf(buf + len, "duplex:\t\t");
	len += sprintf(buf + len,
		"display the port's duplex setting\n");
	len += sprintf(buf + len, "speed:\t\t");
	len += sprintf(buf + len,
		"display the port's link speed\n");
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
	len += sprintf(buf + len, "prio_rate:\t");
	len += sprintf(buf + len,
		"disable/enable priority queue rate limiting\n");
	len += sprintf(buf + len, "rx_p0_rate:\t");
	len += sprintf(buf + len,
		"set rx priority queue 0 rate in 64Kbps unit\n");
	len += sprintf(buf + len, "rx_p1_rate:\t");
	len += sprintf(buf + len,
		"set rx priority queue 1 rate in 64Kbps unit\n");
	len += sprintf(buf + len, "tx_p0_rate:\t");
	len += sprintf(buf + len,
		"set tx priority queue 0 rate in 64Kbps unit\n");
	len += sprintf(buf + len, "tx_p1_rate:\t");
	len += sprintf(buf + len,
		"set tx priority queue 1 rate in 64Kbps unit\n");
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
	len += sprintf(buf + len, "back_pressure:\t");
	len += sprintf(buf + len,
		"disable/enable back pressure in half-duplex mode\n");
	len += sprintf(buf + len, "force_flow_ctrl:");
	len += sprintf(buf + len,
		"set to 1 to force flow control\n");
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
}

static ssize_t sysfs_sw_read(struct ksz_sw *sw, int proc_num,
	struct ksz_port *port, ssize_t len, char *buf)
{
	int i;
	int j;
	u32 map;
	struct ksz_sw_info *info = sw->info;

	switch (proc_num) {
	case PROC_SW_INFO:
		len = display_sw_info(sw->mib_port_cnt, buf, len);
		break;
	case PROC_SET_SW_DUPLEX:
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
		len += sprintf(buf + len, "%u; ", port->speed);
		if (media_connected == port->linked->state)
			len += sprintf(buf + len, "%u\n",
				port->linked->tx_rate / TX_RATE_UNIT);
		else
			len += sprintf(buf + len, "unlinked\n");
		break;
	case PROC_SET_SW_FORCE:
		len += sprintf(buf + len, "%u\n", port->force_link);
		break;
	case PROC_SET_SW_FLOW_CTRL:
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
	case PROC_SET_BROADCAST_STORM:
		len += sprintf(buf + len, "%u%%\n", info->broad_per);
		break;
	case PROC_SET_DIFFSERV:
		for (i = 0; i < DIFFSERV_ENTRIES / KS_PRIORITY_IN_REG; i++) {
			len += sprintf(buf + len, "%2u=",
				i * KS_PRIORITY_IN_REG);
			map = info->diffserv[i];
			for (j = 0; j < KS_PRIORITY_IN_REG; j++) {
				len += sprintf(buf + len, "%u ",
					map & KS_PRIORITY_MASK);
				map >>= KS_PRIORITY_SHIFT;
			}
			len += sprintf(buf + len, "\t%08x\n",
				info->diffserv[i]);
		}
		break;
	case PROC_SET_802_1P:
		len += sprintf(buf + len, "%u\n", info->p_802_1p);
		break;
	case PROC_SET_SW_FEATURES:
		len += sprintf(buf + len, "%08x:\n", sw->features);
		len += sprintf(buf + len, "\t%08x = STP support\n",
			STP_SUPPORT);
		break;
	case PROC_SET_SW_OVERRIDES:
		len += sprintf(buf + len, "%08x:\n", sw->overrides);
		len += sprintf(buf + len, "\t%08x = flow control\n",
			PAUSE_FLOW_CTRL);
		len += sprintf(buf + len, "\t%08x = fast aging\n",
			FAST_AGING);
		break;
	case PROC_GET_PORTS:
		len += sprintf(buf + len, "%u\n", sw->mib_port_cnt - 1);
		break;
	}
	return len;
}

static ssize_t sysfs_sw_read_hw(struct ksz_sw *sw, int proc_num, ssize_t len,
	char *buf)
{
	u8 data[8];

	switch (proc_num) {
	case PROC_DYNAMIC:
		sw_d_dyn_mac_table(sw);
		break;
	case PROC_STATIC:
		sw_d_sta_mac_table(sw);
		break;
#ifdef CONFIG_KS8695P
	case PROC_SET_HUGE_PACKET:
		len += sprintf(buf + len, "%u\n",
			sw_chk(KS_SWITCH_CTRL_1_OFFSET,
				P_SWITCH_HUGE_PACKET));
		break;
	case PROC_SET_LENGTH_CHECK:
		len += sprintf(buf + len, "%u\n",
			sw_chk(KS_SWITCH_CTRL_0_OFFSET,
				P_SWITCH_CHECK_LENGTH));
		break;
	case PROC_SET_SWITCH_10_MBIT:
		len += sprintf(buf + len, "%u\n",
			sw_chk(KS_SWITCH_CTRL_1_OFFSET,
				P_SWITCH_10_MBIT));
		break;
	case PROC_SET_RX_FLOW_CTRL:
		len += sprintf(buf + len, "%u\n",
			!sw_chk(KS_SWITCH_CTRL_1_OFFSET,
				P_SWITCH_RX_FLOW_DISABLE));
		break;
	case PROC_SET_TX_FLOW_CTRL:
		len += sprintf(buf + len, "%u\n",
			!sw_chk(KS_SWITCH_CTRL_1_OFFSET,
				P_SWITCH_TX_FLOW_DISABLE));
		break;
	case PROC_VLAN:
		sw_d_vlan_table(sw);
		break;
	case PROC_ENABLE_VLAN:
		len += sprintf(buf + len, "%u\n",
			sw_chk(KS_SWITCH_CTRL_1_OFFSET,
				P_SWITCH_VLAN_ENABLE));
		break;
	case PROC_SET_REPLACE_NULL_VID:
		len += sprintf(buf + len, "%u\n",
			sw_chk(KS_SWITCH_CTRL_1_OFFSET,
			P_SWITCH_REPLACE_NULL_VID));
		break;
#endif
	case PROC_SET_AGING:
		len += sprintf(buf + len, "%u\n",
			sw_chk(KS_SWITCH_CTRL_0_OFFSET,
				SWITCH_AGING_ENABLE));
		break;
	case PROC_SET_FAST_AGING:
		len += sprintf(buf + len, "%u\n",
			sw_chk(KS_SWITCH_CTRL_0_OFFSET,
				SWITCH_FAST_AGING));
		break;
	case PROC_SET_LINK_AGING:
		len += sprintf(buf + len, "%u\n",
			sw_chk(KS_SWITCH_CTRL_0_OFFSET,
				SWITCH_LINK_AUTO_AGING));
		break;
	case PROC_SET_MULTICAST_STORM:
		len += sprintf(buf + len, "%u\n",
			!sw_chk(KS_SWITCH_CTRL_0_OFFSET,
				MULTICAST_STORM_DISABLE));
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
			sw_chk(KS_SWITCH_ADVANCED_CTRL,
				SWITCH_IGMP_SNOOP));
		break;
	case PROC_SET_AGGR_BACKOFF:
		len += sprintf(buf + len, "%u\n",
			sw_chk(KS_SWITCH_CTRL_0_OFFSET,
				SWITCH_AGGR_BACKOFF));
		break;
	case PROC_SET_NO_EXC_DROP:
		len += sprintf(buf + len, "%u\n",
			sw_chk(KS_SWITCH_CTRL_0_OFFSET,
				NO_EXC_COLLISION_DROP));
		break;
	case PROC_SET_BUFFER_RESERVE:
		len += sprintf(buf + len, "%u\n",
			sw_chk(KS_SWITCH_CTRL_0_OFFSET,
				SWITCH_BUF_RESERVE));
		break;
	case PROC_SET_BUFFER_SHARE:
		len += sprintf(buf + len, "%u\n",
			sw_chk(KS_SWITCH_CTRL_0_OFFSET,
				SWITCH_BUFFER_SHARE));
		break;
	case PROC_SET_VLAN_BOUNDARY:
		len += sprintf(buf + len, "%u\n",
			sw_chk(KS_SWITCH_CTRL_0_OFFSET,
				UNICAST_VLAN_BOUNDARY));
		break;
	case PROC_SET_LEGAL_PACKET:
		len += sprintf(buf + len, "%u\n",
			sw_chk(KS_SWITCH_CTRL_0_OFFSET,
				SWITCH_LEGAL_PACKET));
		break;
	case PROC_SET_BACK_PRESSURE_MODE:
		len += sprintf(buf + len, "%u\n",
			sw_chk(KS_SWITCH_CTRL_0_OFFSET,
				SWITCH_BACK_PRESSURE_MODE));
		break;
	case PROC_SET_SWITCH_BACK_PRESSURE:
		len += sprintf(buf + len, "%u\n",
			sw_chk(KS_SWITCH_CTRL_0_OFFSET,
				SWITCH_BACK_PRESSURE));
		break;
	case PROC_SET_SWITCH_FLOW_CTRL:
		len += sprintf(buf + len, "%u\n",
			sw_chk(KS_SWITCH_CTRL_0_OFFSET,
				SWITCH_FLOW_CTRL));
		break;
	case PROC_SET_FAIR_FLOW_CTRL:
		len += sprintf(buf + len, "%u\n",
			sw_chk(KS_SWITCH_CTRL_0_OFFSET,
				FAIR_FLOW_CTRL));
		break;
	case PROC_SET_PASS_ALL:
		len += sprintf(buf + len, "%u\n",
			sw_chk(KS_SWITCH_CTRL_0_OFFSET,
				SWITCH_PASS_ALL));
		break;
	case PROC_SET_PRIORITY_SCHEME:
	{
		u32 reg;

		reg = KS_R(KS_SWITCH_CTRL_0_OFFSET);
		len += sprintf(buf + len, "%u\n",
			(reg & PRIORITY_SCHEME_SELECT) >> 2);
		break;
	}
	}
	return len;
}

static int sysfs_sw_write(struct ksz_sw *sw, int proc_num,
	struct ksz_port *port, int num, const char *buf)
{
	int count;
	unsigned int val;
	u8 data[8];
	int processed = true;

	switch (proc_num) {
	case PROC_SW_INFO:
		sw_init(sw);
		break;
	case PROC_SET_SW_DUPLEX:
		if (num <= 2)
			port->duplex = (u8) num;
		break;
	case PROC_SET_SW_SPEED:
		if (0 == num || 10 == num || 100 == num)
			port->speed = (u8) num;
		break;
	case PROC_SET_SW_FORCE:
		port->force_link = (u8) num;
		break;
	case PROC_SET_SW_FLOW_CTRL:
		if (num <= PHY_FLOW_CTRL)
			port->flow_ctrl = (u8) num;
		break;
	case PROC_SET_SW_MIB:
		for (count = 0; count < sw->mib_port_cnt; count++) {
			struct ksz_port_mib *mib = &sw->info->port_mib[count];

			memset((void *) mib->counter, 0, sizeof(u64) *
				TOTAL_SWITCH_COUNTER_NUM);
		}
		break;
	case PROC_SET_SW_REG:
		count = sscanf(buf, "%x=%x", (unsigned int *) &num, &val);
		if (1 == count)
			printk(KERN_INFO "%04x\n",
				KS_R(num));
		else if (2 == count)
			KS_W(num, val);
		break;
	case PROC_SET_SW_FEATURES:
		if ('0' != buf[0] || 'x' != buf[1])
			sscanf(buf, "%x", &num);
		sw->features = num;
		break;
	case PROC_SET_SW_OVERRIDES:
		if ('0' != buf[0] || 'x' != buf[1])
			sscanf(buf, "%x", &num);
		sw->overrides = num;
		break;
	case PROC_DYNAMIC:
		sw_flush_dyn_mac_table(sw);
		break;
	case PROC_STATIC:
		sw_clr_sta_mac_table(sw);
		break;
	case PROC_SET_AGING:
		sw_cfg(KS_SWITCH_CTRL_0_OFFSET, SWITCH_AGING_ENABLE, num);
		break;
	case PROC_SET_FAST_AGING:
		sw_cfg(KS_SWITCH_CTRL_0_OFFSET, SWITCH_FAST_AGING, num);
		break;
	case PROC_SET_LINK_AGING:
		sw_cfg(KS_SWITCH_CTRL_0_OFFSET, SWITCH_LINK_AUTO_AGING, num);
		break;
	case PROC_SET_BROADCAST_STORM:
		hw_cfg_broad_storm(sw, num);
		break;
	case PROC_SET_MULTICAST_STORM:
		sw_cfg(KS_SWITCH_CTRL_0_OFFSET, MULTICAST_STORM_DISABLE, !num);
		break;
	case PROC_SET_DIFFSERV:
		count = sscanf(buf, "%d=%x", (unsigned int *) &num, &val);
		if (2 == count)
			hw_cfg_tos_prio(sw, (u8) num, val);
		break;
	case PROC_SET_802_1P:
		hw_cfg_802_1p_prio(sw, (u8) num);
		break;
#ifdef CONFIG_KS8695P
	case PROC_SET_HUGE_PACKET:
		sw_cfg(KS_SWITCH_CTRL_1_OFFSET,	P_SWITCH_HUGE_PACKET, num);
		break;
	case PROC_SET_LENGTH_CHECK:
		sw_cfg(KS_SWITCH_CTRL_0_OFFSET, P_SWITCH_CHECK_LENGTH, num);
		break;
	case PROC_SET_SWITCH_10_MBIT:
		sw_cfg(KS_SWITCH_CTRL_1_OFFSET,	P_SWITCH_10_MBIT, num);
		break;
	case PROC_SET_RX_FLOW_CTRL:
		sw_cfg(KS_SWITCH_CTRL_1_OFFSET,	P_SWITCH_RX_FLOW_DISABLE,
			!num);
		break;
	case PROC_SET_TX_FLOW_CTRL:
		sw_cfg(KS_SWITCH_CTRL_1_OFFSET,	P_SWITCH_TX_FLOW_DISABLE,
			!num);
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
#endif
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
		sw_cfg(KS_SWITCH_ADVANCED_CTRL, SWITCH_IGMP_SNOOP, num);
		break;
	case PROC_SET_AGGR_BACKOFF:
		sw_cfg(KS_SWITCH_CTRL_0_OFFSET, SWITCH_AGGR_BACKOFF, num);
		break;
	case PROC_SET_NO_EXC_DROP:
		sw_cfg(KS_SWITCH_CTRL_0_OFFSET, NO_EXC_COLLISION_DROP, num);
		break;
	case PROC_SET_BUFFER_RESERVE:
		sw_cfg(KS_SWITCH_CTRL_0_OFFSET,	SWITCH_BUF_RESERVE, num);
		break;
	case PROC_SET_BUFFER_SHARE:
		sw_cfg(KS_SWITCH_CTRL_0_OFFSET,	SWITCH_BUFFER_SHARE, num);
		break;
	case PROC_SET_VLAN_BOUNDARY:
		sw_cfg(KS_SWITCH_CTRL_0_OFFSET, UNICAST_VLAN_BOUNDARY, num);
		break;
	case PROC_SET_LEGAL_PACKET:
		sw_cfg(KS_SWITCH_CTRL_0_OFFSET,	SWITCH_LEGAL_PACKET, num);
		break;
	case PROC_SET_BACK_PRESSURE_MODE:
		sw_cfg(KS_SWITCH_CTRL_0_OFFSET, SWITCH_BACK_PRESSURE_MODE, num);
		break;
	case PROC_SET_SWITCH_BACK_PRESSURE:
		sw_cfg(KS_SWITCH_CTRL_0_OFFSET,	SWITCH_BACK_PRESSURE, num);
		break;
	case PROC_SET_SWITCH_FLOW_CTRL:
		sw_cfg(KS_SWITCH_CTRL_0_OFFSET, SWITCH_FLOW_CTRL, num);
		break;
	case PROC_SET_FAIR_FLOW_CTRL:
		sw_cfg(KS_SWITCH_CTRL_0_OFFSET,	FAIR_FLOW_CTRL, num);
		break;
	case PROC_SET_PASS_ALL:
		sw_cfg(KS_SWITCH_CTRL_0_OFFSET, SWITCH_PASS_ALL, num);
		break;
	case PROC_SET_PRIORITY_SCHEME:
	{
		u32 reg;

		reg = KS_R(KS_SWITCH_CTRL_0_OFFSET);
		reg &= ~PRIORITY_SCHEME_SELECT;
		reg |= (num & 3) << 2;
		KS_WR(KS_SWITCH_CTRL_0_OFFSET, reg);
		break;
	}
	default:
		processed = false;
		break;
	}
	return processed;
}

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
	case PROC_SET_PORT_BASED:
		len += sprintf(buf + len, "%u\n",
			port_cfg->port_prio);
		break;
	case PROC_SET_DEF_VID:
		len += sprintf(buf + len, "%04x\n",
			port_cfg->vid);
		break;
	case PROC_SET_MEMBER:
		len += sprintf(buf + len, "%02x\n",
			port_cfg->member);
		break;
	case PROC_SET_RX_P0_RATE:
		len += sprintf(buf + len, "%u\n", (int)
			port_cfg->rx_rate[0]);
		break;
	case PROC_SET_RX_P1_RATE:
		len += sprintf(buf + len, "%u\n", (int)
			port_cfg->rx_rate[1]);
		break;
	case PROC_SET_TX_P0_RATE:
		len += sprintf(buf + len, "%u\n", (int)
			port_cfg->tx_rate[0]);
		break;
	case PROC_SET_TX_P1_RATE:
		len += sprintf(buf + len, "%u\n", (int)
			port_cfg->tx_rate[1]);
		break;
	}
	return len;
}

static ssize_t sysfs_port_read_hw(struct ksz_sw *sw, int proc_num, int port,
	ssize_t len, char *buf)
{
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
			port_chk_prio(sw, port));
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
	case PROC_SET_LEARN:
		len += sprintf(buf + len, "%u\n",
			!port_chk_dis_learn(sw, port));
		break;
	case PROC_SET_RX:
		len += sprintf(buf + len, "%u\n",
			port_chk_rx(sw, port));
		break;
	case PROC_SET_TX:
		len += sprintf(buf + len, "%u\n",
			port_chk_tx(sw, port));
		break;
	case PROC_SET_INSERT_TAG:
		len += sprintf(buf + len, "%u\n",
			port_chk_ins_tag(sw, port));
		break;
	case PROC_SET_REMOVE_TAG:
		len += sprintf(buf + len, "%u\n",
			port_chk_rmv_tag(sw, port));
		break;
#ifdef CONFIG_KS8695P
	case PROC_ENABLE_PRIO_RATE:
		len += sprintf(buf + len, "%d\n",
			sw_chk_prio_rate(sw, port));
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
#endif
	}
	return len;
}

static int sysfs_port_write(struct ksz_sw *sw, int proc_num, int port,
	int num, const char *buf)
{
	int processed = true;

	switch (proc_num) {
	case PROC_SET_PORT_MIB:
	{
		struct ksz_port_mib *mib = &sw->info->port_mib[port];

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
		if (!num)
			sw_dis_multi_queue(sw, port);
		else
			sw_ena_multi_queue(sw, port);
		break;
#ifdef CONFIG_KS8695P
	case PROC_ENABLE_PRIO_RATE:
		if (!num)
			sw_dis_prio_rate(sw, port);
		else
			sw_ena_prio_rate(sw, port);
		break;
	case PROC_SET_RX_P0_RATE:
		hw_cfg_rx_prio_rate(sw, port, 0, num);
		break;
	case PROC_SET_RX_P1_RATE:
		hw_cfg_rx_prio_rate(sw, port, 1, num);
		break;
	case PROC_SET_TX_P0_RATE:
		hw_cfg_tx_prio_rate(sw, port, 0, num);
		break;
	case PROC_SET_TX_P1_RATE:
		hw_cfg_tx_prio_rate(sw, port, 1, num);
		break;
#endif
	case PROC_SET_MIRROR_PORT:
		port_cfg_mirror_sniffer(sw, port, num);
		break;
	case PROC_SET_MIRROR_RX:
		port_cfg_mirror_rx(sw, port, num);
		break;
	case PROC_SET_MIRROR_TX:
		port_cfg_mirror_tx(sw, port, num);
		break;
	case PROC_SET_LEARN:
		port_cfg_dis_learn(sw, port, !num);
		break;
	case PROC_SET_RX:
		port_cfg_rx(sw, port, num);
		break;
	case PROC_SET_TX:
		port_cfg_tx(sw, port, num);
		break;
	case PROC_SET_INSERT_TAG:
		sw_vlan_cfg_ins_tag(sw, port, num);
		break;
	case PROC_SET_REMOVE_TAG:
		sw_vlan_cfg_rmv_tag(sw, port, num);
		break;
#ifdef CONFIG_KS8695P
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
#endif
	default:
		processed = false;
		break;
	}
	return processed;
}

static ssize_t sysfs_mac_read(struct ksz_sw *sw, int proc_num, int index,
	ssize_t len, char *buf)
{
	struct ksz_mac_table *entry;

	entry = &sw->info->mac_table[index];
	switch (proc_num) {
	case PROC_SET_STATIC_FID:
		len += sprintf(buf + len, "%u\n", entry->fid);
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
		len += sprintf(buf + len, "%u\n", entry->ports);
		break;
	case PROC_SET_STATIC_MAC_ADDR:
		len += sprintf(buf + len, "%02x:%02x:%02x:%02x:%02x:%02x\n",
			entry->mac_addr[0], entry->mac_addr[1],
			entry->mac_addr[2], entry->mac_addr[3],
			entry->mac_addr[4], entry->mac_addr[5]);
		break;
	}
	return len;
}

static int sysfs_mac_write(struct ksz_sw *sw, int proc_num, int index,
	int num, const char *buf)
{
	struct ksz_mac_table *entry;
	int processed = true;

	entry = &sw->info->mac_table[index];
	switch (proc_num) {
	case PROC_SET_STATIC_FID:
		if (0 <= num && num < 16)
			entry->fid = num;
		break;
	case PROC_SET_STATIC_USE_FID:
		if (num)
			entry->use_fid = 1;
		else
			entry->use_fid = 0;
		break;
	case PROC_SET_STATIC_OVERRIDE:
		if (num)
			entry->override = 1;
		else
			entry->override = 0;
		break;
	case PROC_SET_STATIC_VALID:
		if (num)
			entry->valid = 1;
		else
			entry->valid = 0;
		sw_w_sta_mac_table(sw, index,
			entry->mac_addr, entry->ports,
			entry->override, entry->valid,
			entry->use_fid, entry->fid);
		break;
	case PROC_SET_STATIC_PORTS:
		if (0 <= num && num <= PORT_MASK)
			entry->ports = num;
		break;
	case PROC_SET_STATIC_MAC_ADDR:
	{
		int i;
		int n[6];

		i = sscanf(buf, "%x:%x:%x:%x:%x:%x",
			&n[0], &n[1], &n[2], &n[3], &n[4], &n[5]);
		if (6 == i) {
			for (i = 0; i < 6; i++)
				entry->mac_addr[i] = (u8) n[i];
		}
		break;
	}
	default:
		processed = false;
		break;
	}
	return processed;
}

#ifdef CONFIG_KS8695P
static ssize_t sysfs_vlan_read(struct ksz_sw *sw, int proc_num, int index,
	ssize_t len, char *buf)
{
	struct ksz_vlan_table *entry;

	entry = &sw->info->vlan_table[index];
	switch (proc_num) {
	case PROC_SET_VLAN_VALID:
		len += sprintf(buf + len, "%u\n", entry->valid);
		break;
	case PROC_SET_VLAN_MEMBER:
		len += sprintf(buf + len, "%u\n", entry->member);
		break;
	case PROC_SET_VLAN_FID:
		len += sprintf(buf + len, "%u\n", entry->fid);
		break;
	case PROC_SET_VLAN_VID:
		len += sprintf(buf + len, "0x%04x\n", entry->vid);
		break;
	}
	return len;
}

static int sysfs_vlan_write(struct ksz_sw *sw, int proc_num, int index,
	int num)
{
	struct ksz_vlan_table *entry;
	int processed = true;

	entry = &sw->info->vlan_table[index];
	switch (proc_num) {
	case PROC_SET_VLAN_VALID:
		if (num)
			entry->valid = 1;
		else
			entry->valid = 0;
		sw_w_vlan_table(sw, index, entry->vid, entry->fid,
			entry->member, entry->valid);
		break;
	case PROC_SET_VLAN_MEMBER:
		if (0 <= num && num <= PORT_MASK)
			entry->member = num;
		break;
	case PROC_SET_VLAN_FID:
		if (0 <= num && num < 16)
			entry->fid = num;
		break;
	case PROC_SET_VLAN_VID:
		if (0 <= num && num < 0x1000)
			entry->vid = num;
		break;
	default:
		processed = false;
		break;
	}
	return processed;
}
#endif

static ssize_t display_info(char *buf, ssize_t len)
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
	return len;
}

static ssize_t sysfs_gen_read(int proc_num, struct ksz_port *port, ssize_t len,
	char *buf)
{
	struct ksz_hw *hw = port->hw;

	switch (proc_num) {
	case PROC_INFO:
		len = display_info(buf, len);
		break;
	case PROC_SET_DUPLEX:
		len += sprintf(buf + len, "%u; ", port->duplex);
		if (media_connected == port->linked->state) {
			if (1 == port->linked->duplex)
				len += sprintf(buf + len, "half-duplex\n");
			else if (2 == port->linked->duplex)
				len += sprintf(buf + len, "full-duplex\n");
		} else
			len += sprintf(buf + len, "unlinked\n");
		break;
	case PROC_SET_SPEED:
		len += sprintf(buf + len, "%u; ", port->speed);
		if (media_connected == port->linked->state)
			len += sprintf(buf + len, "%u\n",
				port->linked->tx_rate / TX_RATE_UNIT);
		else
			len += sprintf(buf + len, "unlinked\n");
		break;
	case PROC_SET_FORCE:
		len += sprintf(buf + len, "%u\n", port->force_link);
		break;
	case PROC_SET_FLOW_CTRL:
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
	case PROC_SET_FEATURES:
		len += sprintf(buf + len, "%08x %08x; %08x:\n",
			hw->rx_cfg, hw->tx_cfg, hw->features);
		len += sprintf(buf + len, "\t%08x = has PHY interrupt\n",
			LINK_INT_WORKING);
		len += sprintf(buf + len, "\t%08x = small packet tx bug\n",
			SMALL_PACKET_TX_BUG);
		len += sprintf(buf + len, "\t%08x = half duplex signal bug\n",
			HALF_DUPLEX_SIGNAL_BUG);
		len += sprintf(buf + len, "\t%08x = IPV6 checksum hack\n",
			IPV6_CSUM_GEN_HACK);
		len += sprintf(buf + len, "\t%08x = rx overrun bug\n",
			RX_OVERRUN_BUG);
		len += sprintf(buf + len, "\t%08x = rx huge frame\n",
			RX_HUGE_FRAME);
		len += sprintf(buf + len, "\t%08x = IP header align\n",
			IP_HEADER_ALIGN);
		break;
	case PROC_SET_OVERRIDES:
		len += sprintf(buf + len, "%08x:\n", hw->overrides);
		len += sprintf(buf + len, "\t%08x = check rx overrun\n",
			CHECK_RX_OVERRUN);
		len += sprintf(buf + len, "\t%08x = rx loopback\n",
			RX_LOOPBACK);
		len += sprintf(buf + len, "\t%08x = rx all\n",
			RX_ALL);
		len += sprintf(buf + len, "\t%08x = data header only\n",
			DATA_HEADER);
#ifdef DEBUG_VERIFY
		len += sprintf(buf + len, "\t%08x = debug rx\n",
			RX_DBG);
		len += sprintf(buf + len, "\t%08x = print rx data\n",
			RX_DATA);
		len += sprintf(buf + len, "\t%08x = debug tx\n",
			TX_DBG);
		len += sprintf(buf + len, "\t%08x = print tx data\n",
			TX_DATA);
		len += sprintf(buf + len,
			"\t%08x = verify checksum generation\n",
			CSUM_GEN);
		len += sprintf(buf + len,
			"\t%08x = verify no checksum generation\n",
			NO_CSUM_GEN);
		len += sprintf(buf + len,
			"\t%08x = verify no IP checksum generation\n",
			NO_IP_CSUM_GEN);
		len += sprintf(buf + len, "\t%08x = tx loopback\n",
			TX_LOOPBACK);
		len += sprintf(buf + len, "\t%08x = tx short frame\n",
			TX_SHORT_FRAME);
		len += sprintf(buf + len, "\t%08x = verify mib\n",
			VERIFY_MIB);
#endif
		break;
	}
	return len;
}

static int sysfs_gen_write(struct dev_info *hw_priv, int proc_num,
	struct ksz_port *port, int num, const char *buf)
{
	struct ksz_hw *hw = port->hw;
	int changes;
	int processed = true;

	switch (proc_num) {
	case PROC_SET_DUPLEX:
		if (num <= 2)
			port->duplex = (u8) num;
		break;
	case PROC_SET_SPEED:
		if (0 == num || 10 == num || 100 == num)
			port->speed = (u8) num;
		break;
	case PROC_SET_FORCE:
		port->force_link = (u8) num;
		break;
	case PROC_SET_FLOW_CTRL:
		if (num <= PHY_FLOW_CTRL)
			port->flow_ctrl = (u8) num;
		break;
	case PROC_SET_FEATURES:
		if ('0' != buf[0] || 'x' != buf[1])
			sscanf(buf, "%x", &num);
		changes = hw->features ^ num;
		if ((changes & (RX_HUGE_FRAME |
				IP_HEADER_ALIGN)) &&
				netif_running(hw_priv->dev)) {
			printk(KERN_INFO "Stop device first\n");
			break;
		}
		hw->features = num;
		hw_setup(hw);
		break;
	case PROC_SET_OVERRIDES:
		if ('0' != buf[0] || 'x' != buf[1])
			sscanf(buf, "%x", &num);
		changes = hw->overrides ^ num;
		if (changes & (RX_LOOPBACK | RX_ALL)) {
			if (hw->overrides & (RX_LOOPBACK | RX_ALL))
				hw->promiscuous--;
		} else if (num & RX_ALL)
			num &= ~DATA_HEADER;
		hw->overrides = num;
		hw_setup(hw);
		if (hw->enabled)
			hw_enable(hw);
		break;
	default:
		processed = false;
		break;
	}
	return processed;
}

static int get_num_val(const char *buf)
{
	int num;

	if ('0' == buf[0] && 'x' == buf[1])
		sscanf(&buf[2], "%x", (unsigned int *) &num);
	else if ('0' == buf[0] && 'b' == buf[1]) {
		int i = 2;

		num = 0;
		while (buf[i]) {
			num <<= 1;
			num |= buf[i] - '0';
			i++;
		}
	} else if ('0' == buf[0] && 'd' == buf[1])
		sscanf(&buf[2], "%u", &num);
	else
		sscanf(buf, "%d", &num);
	return num;
}

static ssize_t net_show(struct device *d, struct device_attribute *attr,
	char *buf, unsigned long offset)
{
	struct net_device *dev = to_net_dev(d);
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_port *port = &priv->port;
	ssize_t len = -EINVAL;
	int proc_num;

	if (down_interruptible(&hw_priv->proc_sem))
		return -ERESTARTSYS;

	len = 0;
	proc_num = offset / sizeof(int);
	len = sysfs_gen_read(proc_num, port, len, buf);
	up(&hw_priv->proc_sem);
	return len;
}

static ssize_t net_store(struct device *d, struct device_attribute *attr,
	const char *buf, size_t count, unsigned long offset)
{
	struct net_device *dev = to_net_dev(d);
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_port *port = &priv->port;
	ssize_t ret = -EINVAL;
	int num;
	int proc_num;

	num = get_num_val(buf);
	if (down_interruptible(&hw_priv->proc_sem))
		return -ERESTARTSYS;

	proc_num = offset / sizeof(int);
	ret = count;
	mutex_lock(&hw_priv->lock);
	sysfs_gen_write(hw_priv, proc_num, port, num, buf);
	mutex_unlock(&hw_priv->lock);
	up(&hw_priv->proc_sem);
	return ret;
}

static ssize_t netlan_show(struct device *d, struct device_attribute *attr,
	char *buf, unsigned long offset)
{
	struct net_device *dev = to_net_dev(d);
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_port *port = &priv->port;
	struct ksz_sw *sw = port->sw;
	ssize_t len = -EINVAL;
	int proc_num;

	if (down_interruptible(&hw_priv->proc_sem))
		return -ERESTARTSYS;

	len = 0;
	proc_num = offset / sizeof(int);
	switch (proc_num) {
	case PROC_SET_SW_MIB:
		len += display_mib_counters(sw, port->first_port,
			port->mib_port_cnt, buf + len);
		break;
	default:
		len = sysfs_sw_read(sw, proc_num, port, len, buf);
	}
	if (len)
		goto netlan_show_done;

	/* Require hardware to be acquired first. */
	sw_acquire(sw, sw->hwlock);
	len = sysfs_sw_read_hw(sw, proc_num, len, buf);
	sw_release(sw, sw->hwlock);

netlan_show_done:
	up(&hw_priv->proc_sem);
	return len;
}

static ssize_t netlan_store(struct device *d, struct device_attribute *attr,
	const char *buf, size_t count, unsigned long offset)
{
	struct net_device *dev = to_net_dev(d);
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_port *port = &priv->port;
	struct ksz_sw *sw = port->sw;
	ssize_t ret = -EINVAL;
	int num;
	int proc_num;

	num = get_num_val(buf);
	if (down_interruptible(&hw_priv->proc_sem))
		return -ERESTARTSYS;

	proc_num = offset / sizeof(int);
	ret = count;
	sw_acquire(sw, sw->hwlock);
	sysfs_sw_write(sw, proc_num, port, num, buf);
	sw_release(sw, sw->hwlock);
	up(&hw_priv->proc_sem);
	return ret;
}

static ssize_t netsw_show(struct device *d, struct device_attribute *attr,
	char *buf, unsigned long offset)
{
	struct net_device *dev = to_net_dev(d);
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_sw *sw = &hw_priv->sw;
	ssize_t len = -EINVAL;
	int num;
	int port;

	if (attr->attr.name[1] != '_')
		return len;
	port = attr->attr.name[0] - '0';
	if (port >= TOTAL_PORT_NUM)
		return len;

	if (down_interruptible(&hw_priv->proc_sem))
		return -ERESTARTSYS;

	len = 0;
	num = offset / sizeof(int);
	switch (num) {
	case PROC_SET_PORT_MIB:
		len += display_mib_counters(sw, port, 1, buf + len);
		break;
	default:
		len = sysfs_port_read(sw, num, port, len, buf);
	}
	if (len)
		goto netsw_show_done;

	/* Require hardware to be acquired first. */
	sw_acquire(sw, sw->hwlock);
	len = sysfs_port_read_hw(sw, num, port, len, buf);
	sw_release(sw, sw->hwlock);

netsw_show_done:
	up(&hw_priv->proc_sem);
	return len;
}

static ssize_t netsw_store(struct device *d, struct device_attribute *attr,
	const char *buf, size_t count, unsigned long offset)
{
	struct net_device *dev = to_net_dev(d);
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_sw *sw = &hw_priv->sw;
	ssize_t ret = -EINVAL;
	int num;
	int port;
	int proc_num;

	if (attr->attr.name[1] != '_')
		return ret;
	port = attr->attr.name[0] - '0';
	if (port >= TOTAL_PORT_NUM)
		return ret;
	num = get_num_val(buf);
	if (down_interruptible(&hw_priv->proc_sem))
		return -ERESTARTSYS;

	proc_num = offset / sizeof(int);
	ret = count;
	sw_acquire(sw, sw->hwlock);
	sysfs_port_write(sw, proc_num, port, num, buf);
	sw_release(sw, sw->hwlock);
	up(&hw_priv->proc_sem);
	return ret;
}

static ssize_t netmac_show(struct device *d, struct device_attribute *attr,
	char *buf, unsigned long offset)
{
	struct net_device *dev = to_net_dev(d);
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_sw *sw = &hw_priv->sw;
	ssize_t len = -EINVAL;
	int num;
	int index;

	if (attr->attr.name[1] != '_')
		return len;
	index = attr->attr.name[0] - '0';
	if (index >= STATIC_MAC_TABLE_ENTRIES)
		return len;

	if (down_interruptible(&hw_priv->proc_sem))
		return -ERESTARTSYS;

	len = 0;
	num = offset / sizeof(int);
	len = sysfs_mac_read(sw, num, index, len, buf);
	up(&hw_priv->proc_sem);
	return len;
}

static ssize_t netmac_store(struct device *d, struct device_attribute *attr,
	const char *buf, size_t count, unsigned long offset)
{
	struct net_device *dev = to_net_dev(d);
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_sw *sw = &hw_priv->sw;
	ssize_t ret = -EINVAL;
	int num;
	int index;
	int proc_num;

	if (attr->attr.name[1] != '_')
		return ret;
	index = attr->attr.name[0] - '0';
	if (index >= STATIC_MAC_TABLE_ENTRIES)
		return ret;
	num = get_num_val(buf);
	if (down_interruptible(&hw_priv->proc_sem))
		return -ERESTARTSYS;

	proc_num = offset / sizeof(int);
	ret = count;
	sw_acquire(sw, sw->hwlock);
	sysfs_mac_write(sw, proc_num, index, num, buf);
	sw_release(sw, sw->hwlock);
	up(&hw_priv->proc_sem);
	return ret;
}

#ifdef CONFIG_KS8695P
static ssize_t netvlan_show(struct device *d, struct device_attribute *attr,
	char *buf, unsigned long offset)
{
	struct net_device *dev = to_net_dev(d);
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_sw *sw = &hw_priv->sw;
	ssize_t len = -EINVAL;
	int num;
	int index;

	if (attr->attr.name[1] != '_')
		return len;
	if ('a' <= attr->attr.name[0] && attr->attr.name[0] <= 'f')
		index = attr->attr.name[0] - 'a' + 10;
	else
		index = attr->attr.name[0] - '0';
	if (index >= VLAN_TABLE_ENTRIES)
		return len;

	if (down_interruptible(&hw_priv->proc_sem))
		return -ERESTARTSYS;

	len = 0;
	num = offset / sizeof(int);
	len = sysfs_vlan_read(sw, num, index, len, buf);
	up(&hw_priv->proc_sem);
	return len;
}

static ssize_t netvlan_store(struct device *d, struct device_attribute *attr,
	const char *buf, size_t count, unsigned long offset)
{
	struct net_device *dev = to_net_dev(d);
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_sw *sw = &hw_priv->sw;
	ssize_t ret = -EINVAL;
	int num;
	int index;
	int proc_num;

	if (attr->attr.name[1] != '_')
		return ret;
	if ('a' <= attr->attr.name[0] && attr->attr.name[0] <= 'f')
		index = attr->attr.name[0] - 'a' + 10;
	else
		index = attr->attr.name[0] - '0';
	if (index >= VLAN_TABLE_ENTRIES)
		return ret;
	num = get_num_val(buf);
	if (down_interruptible(&hw_priv->proc_sem))
		return -ERESTARTSYS;

	proc_num = offset / sizeof(int);
	ret = count;
	sw_acquire(sw, sw->hwlock);
	sysfs_vlan_write(sw, proc_num, index, num);
	sw_release(sw, sw->hwlock);
	up(&hw_priv->proc_sem);
	return ret;
}
#endif

/* generate a read-only attribute */
#define NET_RD_ENTRY(name)						\
static ssize_t show_##name(struct device *d,				\
	struct device_attribute *attr, char *buf)			\
{									\
	return net_show(d, attr, buf,					\
		offsetof(struct all_attributes, name));			\
}									\
static DEVICE_ATTR(name, S_IRUGO, show_##name, NULL)

/* generate a write-able attribute */
#define NET_WR_ENTRY(name)						\
static ssize_t show_##name(struct device *d,				\
	struct device_attribute *attr, char *buf)			\
{									\
	return net_show(d, attr, buf,					\
		offsetof(struct all_attributes, name));			\
}									\
static ssize_t store_##name(struct device *d,				\
	struct device_attribute *attr, const char *buf, size_t count)	\
{									\
	return net_store(d, attr, buf, count,				\
		offsetof(struct all_attributes, name));			\
}									\
static DEVICE_ATTR(name, S_IRUGO | S_IWUSR, show_##name, store_##name)

#define LAN_ATTR(_name, _mode, _show, _store) \
struct device_attribute lan_attr_##_name = \
	__ATTR(_name, _mode, _show, _store)

/* generate a read-only attribute */
#define NETLAN_RD_ENTRY(name)						\
static ssize_t show_lan_##name(struct device *d,			\
	struct device_attribute *attr, char *buf)			\
{									\
	return netlan_show(d, attr, buf,				\
		offsetof(struct lan_attributes, name));			\
}									\
static LAN_ATTR(name, S_IRUGO, show_lan_##name, NULL)

/* generate a write-able attribute */
#define NETLAN_WR_ENTRY(name)						\
static ssize_t show_lan_##name(struct device *d,			\
	struct device_attribute *attr, char *buf)			\
{									\
	return netlan_show(d, attr, buf,				\
		offsetof(struct lan_attributes, name));			\
}									\
static ssize_t store_lan_##name(struct device *d,			\
	struct device_attribute *attr, const char *buf, size_t count)	\
{									\
	return netlan_store(d, attr, buf, count,			\
		offsetof(struct lan_attributes, name));			\
}									\
static LAN_ATTR(name, S_IRUGO | S_IWUSR, show_lan_##name, store_lan_##name)

#define SW_ATTR(_name, _mode, _show, _store) \
struct device_attribute sw_attr_##_name = \
	__ATTR(0_##_name, _mode, _show, _store)

/* generate a read-only attribute */
#define NETSW_RD_ENTRY(name)						\
static ssize_t show_sw_##name(struct device *d,				\
	struct device_attribute *attr, char *buf)			\
{									\
	return netsw_show(d, attr, buf,					\
		offsetof(struct sw_attributes, name));			\
}									\
static SW_ATTR(name, S_IRUGO, show_sw_##name, NULL)

/* generate a write-able attribute */
#define NETSW_WR_ENTRY(name)						\
static ssize_t show_sw_##name(struct device *d,				\
	struct device_attribute *attr, char *buf)			\
{									\
	return netsw_show(d, attr, buf,					\
		offsetof(struct sw_attributes, name));			\
}									\
static ssize_t store_sw_##name(struct device *d,			\
	struct device_attribute *attr, const char *buf, size_t count)	\
{									\
	return netsw_store(d, attr, buf, count,				\
		offsetof(struct sw_attributes, name));			\
}									\
static SW_ATTR(name, S_IRUGO | S_IWUSR, show_sw_##name, store_sw_##name)

#define MAC_ATTR(_name, _mode, _show, _store) \
struct device_attribute mac_attr_##_name = \
	__ATTR(0_##_name, _mode, _show, _store)

/* generate a read-only attribute */
#define NETMAC_RD_ENTRY(name)						\
static ssize_t show_mac_##name(struct device *d,			\
	struct device_attribute *attr, char *buf)			\
{									\
	return netmac_show(d, attr, buf,				\
		offsetof(struct static_mac_attributes, name));		\
}									\
static MAC_ATTR(name, S_IRUGO, show_mac_##name, NULL)

/* generate a write-able attribute */
#define NETMAC_WR_ENTRY(name)						\
static ssize_t show_mac_##name(struct device *d,			\
	struct device_attribute *attr, char *buf)			\
{									\
	return netmac_show(d, attr, buf,				\
		offsetof(struct static_mac_attributes, name));		\
}									\
static ssize_t store_mac_##name(struct device *d,			\
	struct device_attribute *attr, const char *buf, size_t count)	\
{									\
	return netmac_store(d, attr, buf, count,			\
		offsetof(struct static_mac_attributes, name));		\
}									\
static MAC_ATTR(name, S_IRUGO | S_IWUSR, show_mac_##name, store_mac_##name)

#ifdef CONFIG_KS8695P
#define VLAN_ATTR(_name, _mode, _show, _store) \
struct device_attribute vlan_attr_##_name = \
	__ATTR(0_##_name, _mode, _show, _store)

/* generate a read-only attribute */
#define NETVLAN_RD_ENTRY(name)						\
static ssize_t show_vlan_##name(struct device *d,			\
	struct device_attribute *attr, char *buf)			\
{									\
	return netvlan_show(d, attr, buf,				\
		offsetof(struct vlan_attributes, name));		\
}									\
static VLAN_ATTR(name, S_IRUGO, show_vlan_##name, NULL)

/* generate a write-able attribute */
#define NETVLAN_WR_ENTRY(name)						\
static ssize_t show_vlan_##name(struct device *d,			\
	struct device_attribute *attr, char *buf)			\
{									\
	return netvlan_show(d, attr, buf,				\
		offsetof(struct vlan_attributes, name));		\
}									\
static ssize_t store_vlan_##name(struct device *d,			\
	struct device_attribute *attr, const char *buf, size_t count)	\
{									\
	return netvlan_store(d, attr, buf, count,			\
		offsetof(struct vlan_attributes, name));		\
}									\
static VLAN_ATTR(name, S_IRUGO | S_IWUSR, show_vlan_##name, store_vlan_##name)
#endif

NET_RD_ENTRY(info);
NET_WR_ENTRY(features);
NET_WR_ENTRY(overrides);

NETLAN_WR_ENTRY(info);
NETLAN_WR_ENTRY(duplex);
NETLAN_WR_ENTRY(speed);
NETLAN_WR_ENTRY(force);
NETLAN_WR_ENTRY(flow_ctrl);
NETLAN_RD_ENTRY(ports);
NETLAN_WR_ENTRY(mib);
NETLAN_WR_ENTRY(reg);
NETLAN_WR_ENTRY(features);
NETLAN_WR_ENTRY(overrides);

NETLAN_WR_ENTRY(dynamic_table);
NETLAN_WR_ENTRY(static_table);
#ifdef CONFIG_KS8695P
NETLAN_WR_ENTRY(huge_packet);
NETLAN_WR_ENTRY(length_check);
NETLAN_WR_ENTRY(sw_10_mbit);
NETLAN_WR_ENTRY(rx_flow_ctrl);
NETLAN_WR_ENTRY(tx_flow_ctrl);
NETLAN_RD_ENTRY(vlan_table);
NETLAN_WR_ENTRY(vlan);
NETLAN_WR_ENTRY(null_vid);
#endif
NETLAN_WR_ENTRY(aging);
NETLAN_WR_ENTRY(fast_aging);
NETLAN_WR_ENTRY(link_aging);
NETLAN_WR_ENTRY(bcast_per);
NETLAN_WR_ENTRY(mcast_storm);
NETLAN_WR_ENTRY(v_diffserv);
NETLAN_WR_ENTRY(v_802_1p);
NETLAN_WR_ENTRY(macaddr);
NETLAN_WR_ENTRY(mirror_mode);
NETLAN_WR_ENTRY(igmp_snoop);
NETLAN_WR_ENTRY(aggr_backoff);
NETLAN_WR_ENTRY(no_exc_drop);
NETLAN_WR_ENTRY(buf_reserve);
NETLAN_WR_ENTRY(buf_share);
NETLAN_WR_ENTRY(legal_packet);
NETLAN_WR_ENTRY(back_pressure);
NETLAN_WR_ENTRY(sw_back_pressure);
NETLAN_WR_ENTRY(sw_flow_ctrl);
NETLAN_WR_ENTRY(fair_flow_ctrl);
NETLAN_WR_ENTRY(vlan_bound);
NETLAN_WR_ENTRY(pass_all);
NETLAN_WR_ENTRY(priority_scheme);

NETSW_RD_ENTRY(mib);
NETSW_WR_ENTRY(vid);
NETSW_WR_ENTRY(member);
NETSW_WR_ENTRY(bcast_storm);
NETSW_WR_ENTRY(diffserv);
NETSW_WR_ENTRY(p_802_1p);
NETSW_WR_ENTRY(prio_queue);
NETSW_WR_ENTRY(port_based);
NETSW_WR_ENTRY(ins_tag);
NETSW_WR_ENTRY(rmv_tag);
NETSW_WR_ENTRY(rx);
NETSW_WR_ENTRY(tx);
NETSW_WR_ENTRY(learn);
NETSW_WR_ENTRY(mirror_port);
NETSW_WR_ENTRY(mirror_rx);
NETSW_WR_ENTRY(mirror_tx);
#ifdef CONFIG_KS8695P
NETSW_WR_ENTRY(non_vid);
NETSW_WR_ENTRY(ingress);
NETSW_WR_ENTRY(prio_rate);
NETSW_WR_ENTRY(rx_p0_rate);
NETSW_WR_ENTRY(rx_p1_rate);
NETSW_WR_ENTRY(tx_p0_rate);
NETSW_WR_ENTRY(tx_p1_rate);
NETSW_WR_ENTRY(back_pressure);
NETSW_WR_ENTRY(force_flow_ctrl);
#endif
NETSW_RD_ENTRY(duplex);
NETSW_RD_ENTRY(speed);

NETMAC_WR_ENTRY(fid);
NETMAC_WR_ENTRY(use_fid);
NETMAC_WR_ENTRY(override);
NETMAC_WR_ENTRY(valid);
NETMAC_WR_ENTRY(ports);
NETMAC_WR_ENTRY(addr);

#ifdef CONFIG_KS8695P
NETVLAN_WR_ENTRY(valid);
NETVLAN_WR_ENTRY(member);
NETVLAN_WR_ENTRY(fid);
NETVLAN_WR_ENTRY(vid);
#endif

static struct attribute *lan_attrs[] = {
	&lan_attr_info.attr,
	&lan_attr_reg.attr,
	&lan_attr_features.attr,
	&lan_attr_overrides.attr,

	&lan_attr_ports.attr,
	&lan_attr_mib.attr,
	&lan_attr_dynamic_table.attr,
	&lan_attr_static_table.attr,
	&lan_attr_aging.attr,
	&lan_attr_fast_aging.attr,
	&lan_attr_link_aging.attr,
	&lan_attr_bcast_per.attr,
	&lan_attr_mcast_storm.attr,
	&lan_attr_v_diffserv.attr,
	&lan_attr_v_802_1p.attr,
#ifdef CONFIG_KS8695P
	&lan_attr_huge_packet.attr,
	&lan_attr_length_check.attr,
	&lan_attr_sw_10_mbit.attr,
	&lan_attr_rx_flow_ctrl.attr,
	&lan_attr_tx_flow_ctrl.attr,
	&lan_attr_vlan_table.attr,
	&lan_attr_vlan.attr,
	&lan_attr_null_vid.attr,
#endif
	&lan_attr_macaddr.attr,
	&lan_attr_mirror_mode.attr,
	&lan_attr_igmp_snoop.attr,
	&lan_attr_aggr_backoff.attr,
	&lan_attr_no_exc_drop.attr,
	&lan_attr_buf_reserve.attr,
	&lan_attr_buf_share.attr,
	&lan_attr_legal_packet.attr,
	&lan_attr_back_pressure.attr,
	&lan_attr_sw_back_pressure.attr,
	&lan_attr_sw_flow_ctrl.attr,
	&lan_attr_fair_flow_ctrl.attr,
	&lan_attr_vlan_bound.attr,
	&lan_attr_pass_all.attr,
	&lan_attr_priority_scheme.attr,
	NULL
};

static struct attribute *wan_attrs[] = {
	&dev_attr_info.attr,
	&dev_attr_features.attr,
	&dev_attr_overrides.attr,
	&lan_attr_duplex.attr,
	&lan_attr_speed.attr,
	&lan_attr_force.attr,
	&lan_attr_flow_ctrl.attr,
	NULL
};

static struct attribute *sw_attrs[] = {
	&sw_attr_vid.attr,
	&sw_attr_member.attr,
	&sw_attr_bcast_storm.attr,
	&sw_attr_diffserv.attr,
	&sw_attr_p_802_1p.attr,
	&sw_attr_port_based.attr,
	&sw_attr_ins_tag.attr,
	&sw_attr_rmv_tag.attr,
	&sw_attr_rx.attr,
	&sw_attr_tx.attr,
	&sw_attr_learn.attr,
	&sw_attr_prio_queue.attr,
	&sw_attr_mirror_port.attr,
	&sw_attr_mirror_rx.attr,
	&sw_attr_mirror_tx.attr,
#ifdef CONFIG_KS8695P
	&sw_attr_prio_rate.attr,
	&sw_attr_rx_p0_rate.attr,
	&sw_attr_rx_p1_rate.attr,
	&sw_attr_tx_p0_rate.attr,
	&sw_attr_tx_p1_rate.attr,
	&sw_attr_non_vid.attr,
	&sw_attr_ingress.attr,
	&sw_attr_back_pressure.attr,
	&sw_attr_force_flow_ctrl.attr,
#endif
	&sw_attr_mib.attr,
	&sw_attr_duplex.attr,
	&sw_attr_speed.attr,
	NULL
};

static struct attribute *mac_attrs[] = {
	&mac_attr_fid.attr,
	&mac_attr_use_fid.attr,
	&mac_attr_override.attr,
	&mac_attr_valid.attr,
	&mac_attr_ports.attr,
	&mac_attr_addr.attr,
	NULL
};

#ifdef CONFIG_KS8695P
static struct attribute *vlan_attrs[] = {
	&vlan_attr_valid.attr,
	&vlan_attr_member.attr,
	&vlan_attr_fid.attr,
	&vlan_attr_vid.attr,
	NULL
};
#endif

static struct attribute_group all_group = {
	.name  = "general",
	.attrs  = wan_attrs,
};

static struct attribute_group lan_group = {
	.name  = "sw",
	.attrs  = lan_attrs,
};

static struct attribute_group sw_group = {
	.name  = "sw0",
	.attrs  = sw_attrs,
};

static struct attribute_group mac_group = {
	.name  = "mac0",
	.attrs  = mac_attrs,
};

#ifdef CONFIG_KS8695P
static struct attribute_group vlan_group = {
	.name  = "vlan0",
	.attrs  = vlan_attrs,
};
#endif

char *sw_name[TOTAL_PORT_NUM] = {
	"sw0",
	"sw1",
	"sw2",
	"sw3",
	"sw4",
};

static char *mac_name[STATIC_MAC_TABLE_ENTRIES] = {
	"mac0",
	"mac1",
	"mac2",
	"mac3",
	"mac4",
	"mac5",
	"mac6",
	"mac7",
};

#ifdef CONFIG_KS8695P
static char *vlan_name[VLAN_TABLE_ENTRIES] = {
	"vlan0",
	"vlan1",
	"vlan2",
	"vlan3",
	"vlan4",
	"vlan5",
	"vlan6",
	"vlan7",
	"vlan8",
	"vlan9",
	"vlana",
	"vlanb",
	"vlanc",
	"vland",
	"vlane",
	"vlanf",
};
#endif

static int alloc_dev_attr(struct attribute **attrs, size_t attr_size, int item,
	struct ksz_dev_attr **ksz_attrs, struct attribute ***item_attrs,
	char *item_name)
{
	struct attribute **attr_ptr;
	struct device_attribute *dev_attr;
	struct ksz_dev_attr *new_attr;

	*item_attrs = kmalloc(attr_size * sizeof(void *), GFP_KERNEL);
	if (!*item_attrs)
		return -ENOMEM;

	attr_size--;
	attr_size *= sizeof(struct ksz_dev_attr);
	*ksz_attrs = kmalloc(attr_size, GFP_KERNEL);
	if (!*ksz_attrs) {
		kfree(*item_attrs);
		*item_attrs = NULL;
		return -ENOMEM;
	}

	new_attr = *ksz_attrs;
	attr_ptr = *item_attrs;
	while (*attrs != NULL) {
		if (item_name && !strcmp((*attrs)->name, item_name))
			break;
		dev_attr = container_of(*attrs, struct device_attribute, attr);
		memcpy(new_attr, dev_attr, sizeof(struct device_attribute));
		strncpy(new_attr->dev_name, (*attrs)->name, DEV_NAME_SIZE);
		if (10 <= item && item <= 15)
			new_attr->dev_name[0] = item - 10 + 'a';
		else
			new_attr->dev_name[0] = item + '0';
		new_attr->dev_attr.attr.name = new_attr->dev_name;
		*attr_ptr = &new_attr->dev_attr.attr;
		new_attr++;
		attr_ptr++;
		attrs++;
	}
	*attr_ptr = NULL;
	return 0;
}

static void exit_sw_sysfs(struct dev_info *hw_priv)
{
	struct net_device *dev = hw_priv->basedev;
	int i;

#ifdef CONFIG_KS8695P
	for (i = 0; i < VLAN_TABLE_ENTRIES; i++) {
		vlan_group.name = vlan_name[i];
		vlan_group.attrs = hw_priv->vlan_attrs[i];
		sysfs_remove_group(&dev->dev.kobj, &vlan_group);
		kfree(hw_priv->vlan_attrs[i]);
		hw_priv->vlan_attrs[i] = NULL;
		kfree(hw_priv->ksz_vlan_attrs[i]);
		hw_priv->ksz_vlan_attrs[i] = NULL;
	}
#endif
	for (i = 0; i < STATIC_MAC_TABLE_ENTRIES; i++) {
		mac_group.name = mac_name[i];
		mac_group.attrs = hw_priv->mac_attrs[i];
		sysfs_remove_group(&dev->dev.kobj, &mac_group);
		kfree(hw_priv->mac_attrs[i]);
		hw_priv->mac_attrs[i] = NULL;
		kfree(hw_priv->ksz_mac_attrs[i]);
		hw_priv->ksz_mac_attrs[i] = NULL;
	}
	for (i = 0; i < SWITCH_PORT_NUM; i++) {
		sw_group.name = sw_name[i];
		sw_group.attrs = hw_priv->port_attrs[i];
		sysfs_remove_group(&dev->dev.kobj, &sw_group);
		kfree(hw_priv->port_attrs[i]);
		hw_priv->port_attrs[i] = NULL;
		kfree(hw_priv->ksz_port_attrs[i]);
		hw_priv->ksz_port_attrs[i] = NULL;
	}
	i = HOST_PORT;
	sw_group.name = sw_name[i];
	sw_group.attrs = hw_priv->port_attrs[i];
	sysfs_remove_group(&dev->dev.kobj, &sw_group);
	kfree(hw_priv->port_attrs[i]);
	hw_priv->port_attrs[i] = NULL;
	kfree(hw_priv->ksz_port_attrs[i]);
	hw_priv->ksz_port_attrs[i] = NULL;

	sysfs_remove_group(&dev->dev.kobj, &lan_group);
}

static int init_sw_sysfs(struct dev_info *hw_priv)
{
	struct net_device *dev = hw_priv->basedev;
	int err;
	int i;

	err = sysfs_create_group(&dev->dev.kobj, &lan_group);
	if (err)
		return err;
	for (i = 0; i < STATIC_MAC_TABLE_ENTRIES; i++) {
		err = alloc_dev_attr(mac_attrs,
			sizeof(mac_attrs) / sizeof(void *), i,
			&hw_priv->ksz_mac_attrs[i],
			&hw_priv->mac_attrs[i], NULL);
		if (err)
			return err;
		mac_group.name = mac_name[i];
		mac_group.attrs = hw_priv->mac_attrs[i];
		err = sysfs_create_group(&dev->dev.kobj, &mac_group);
		if (err)
			return err;
	}
#ifdef CONFIG_KS8695P
	for (i = 0; i < VLAN_TABLE_ENTRIES; i++) {
		err = alloc_dev_attr(vlan_attrs,
			sizeof(vlan_attrs) / sizeof(void *), i,
			&hw_priv->ksz_vlan_attrs[i],
			&hw_priv->vlan_attrs[i], NULL);
		if (err)
			return err;
		vlan_group.name = vlan_name[i];
		vlan_group.attrs = hw_priv->vlan_attrs[i];
		err = sysfs_create_group(&dev->dev.kobj, &vlan_group);
		if (err)
			return err;
	}
#endif
	for (i = 0; i < SWITCH_PORT_NUM; i++) {
		err = alloc_dev_attr(sw_attrs,
			sizeof(sw_attrs) / sizeof(void *), i,
			&hw_priv->ksz_port_attrs[i],
			&hw_priv->port_attrs[i], NULL);
		if (err)
			return err;
		sw_group.name = sw_name[i];
		sw_group.attrs = hw_priv->port_attrs[i];
		err = sysfs_create_group(&dev->dev.kobj, &sw_group);
		if (err)
			return err;
	}
	i = HOST_PORT;
	err = alloc_dev_attr(sw_attrs,
		sizeof(sw_attrs) / sizeof(void *), i,
		&hw_priv->ksz_port_attrs[i], &hw_priv->port_attrs[i],
		"0_duplex");
	if (err)
		return err;
	sw_group.name = sw_name[i];
	sw_group.attrs = hw_priv->port_attrs[i];
	err = sysfs_create_group(&dev->dev.kobj, &sw_group);
	if (err)
		return err;
	return err;
}

static void exit_sysfs(struct net_device *dev)
{
	sysfs_remove_group(&dev->dev.kobj, &all_group);
	sysfs_remove_bin_file(&dev->dev.kobj, &ksz8695_registers_attr);
}

static int init_sysfs(struct net_device *dev)
{
	int err;

	err = sysfs_create_bin_file(&dev->dev.kobj, &ksz8695_registers_attr);
	if (err)
		return err;
	err = sysfs_create_group(&dev->dev.kobj, &all_group);
	return err;
}

/* -------------------------------------------------------------------------- */

/*
 * Linux network device interface functions
 */

/* Driver exported variables */

static int msg_enable;

static char *lan_mac_addr = ":";
static char *wan_mac_addr = ":";

/*
 * This enables multiple network device mode for KSZ8695, which contains a
 * switch with two physical ports.  Some users like to take control of the
 * ports for running Spanning Tree Protocol.  The driver will create an
 * additional eth? device for the other port.
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
 * This enables fast aging in the KSZ8695 switch.  Not sure what situation
 * needs that.  However, fast aging is used to flush the dynamic MAC table when
 * STP suport is enabled.
 */
static int fast_aging;

/* -------------------------------------------------------------------------- */

/**
 * netdev_init - initalize network device.
 * @dev:	Network device.
 *
 * This function initializes the network device.
 *
 * Return 0 if successful; otherwise an error code indicating failure.
 */
static int netdev_init(struct net_device *dev)
{
	struct dev_priv *priv = netdev_priv(dev);

	/* 500 ms timeout */
	ksz_init_timer(&priv->monitor_timer_info, 500 * HZ / 1000,
		dev_monitor, dev);

	/* 500 ms timeout */
	dev->watchdog_timeo = HZ / 2;

	dev->hw_features |= NETIF_F_IP_CSUM;
	dev->hw_features |= NETIF_F_RXCSUM;

	/*
	 * Hardware does not really support IPv6 checksum generation, but
	 * driver actually runs faster with this on.  Refer IPV6_CSUM_GEN_HACK.
	 */
	dev->hw_features |= NETIF_F_IPV6_CSUM;
	dev->hw_features |= NETIF_F_SG;

	dev->features |= dev->hw_features;
#ifdef DEBUG
	pr_info("features: %llx\n", dev->features);
#endif

	priv->mii_if.phy_id_mask = 0x1;
	priv->mii_if.reg_num_mask = 0x7;
	priv->mii_if.dev = dev;
	priv->mii_if.mdio_read = mdio_read;
	priv->mii_if.mdio_write = mdio_write;
	priv->mii_if.phy_id = priv->id + 1;

	priv->msg_enable = netif_msg_init(msg_enable,
		(NETIF_MSG_DRV | NETIF_MSG_PROBE | NETIF_MSG_LINK));

	return 0;
}  /* netdev_init */

static const struct net_device_ops netdev_ops = {
	.ndo_init		= netdev_init,
	.ndo_open		= netdev_open,
	.ndo_stop		= netdev_close,
	.ndo_get_stats		= netdev_query_statistics,
	.ndo_start_xmit		= netdev_tx,
	.ndo_tx_timeout		= netdev_tx_timeout,
	.ndo_change_mtu		= netdev_change_mtu,
	.ndo_set_mac_address	= netdev_set_mac_address,
	.ndo_do_ioctl		= netdev_ioctl,
	.ndo_set_rx_mode	= netdev_set_rx_mode,
#ifdef CONFIG_NET_POLL_CONTROLLER
	.ndo_poll_controller	= netdev_netpoll,
#endif
};

static int netdev_create(struct net_device *dev)
{
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;

	dev->irq = hw_priv->hw.shift;
	dev->base_addr = 0;
	dev->mem_end = dev->mem_start + BASE_IO_RANGE - 1;
	memcpy(dev->dev_addr, hw_priv->hw.override_addr, MAC_ADDR_LEN);
	if (1 != hw_priv->sw.dev_count) {
		u8 addr = dev->dev_addr[5];

		dev->dev_addr[5] += priv->port.first_port;
		if (addr > dev->dev_addr[5]) {
			dev->dev_addr[4]++;
			if (0 == dev->dev_addr[4])
				dev->dev_addr[3]++;
		}
	}
	dev->netdev_ops = &netdev_ops;
	dev->ethtool_ops = &netdev_ethtool_ops;
	return register_netdev(dev);
}  /* netdev_create */

static void netdev_free(struct net_device *dev)
{
	exit_sysfs(dev);
	if (dev->watchdog_timeo)
		unregister_netdev(dev);

	free_netdev(dev);
}  /* netdev_free */

/* -------------------------------------------------------------------------- */

#define MAX_DEVICES			2

struct platform_info {
	struct dev_info dev_info;
	struct net_device *netdev[SWITCH_PORT_NUM];
};

static char PLATFORM_DRV_NAME[] = DEVICE_NAME;

static struct resource net_resources[MAX_DEVICES] = {
{
	.start		= KS_IO_BASE + KS_WAN_DMA_TX,
	.end		= KS_IO_BASE + KS_WAN_DMA_TX + BASE_IO_RANGE - 1,
	.flags		= IORESOURCE_MEM,
},
{
	.start		= KS_IO_BASE + KS_LAN_DMA_TX,
	.end		= KS_IO_BASE + KS_LAN_DMA_TX + BASE_IO_RANGE - 1,
	.flags		= IORESOURCE_MEM,
}
};

static int netdev_resume(struct platform_device *pdev)
{
	int i;
	struct platform_info *info = platform_get_drvdata(pdev);

	for (i = 0; i < info->dev_info.sw.dev_count; i++) {
		if (info->netdev[i]) {
			struct net_device *dev = info->netdev[i];

			if (netif_running(dev)) {
				netdev_open(dev);
				netif_device_attach(dev);
			}
		}
	}
	return 0;
}  /* netdev_resume */

static int netdev_suspend(struct platform_device *pdev, pm_message_t state)
{
	int i;
	struct platform_info *info = platform_get_drvdata(pdev);

	for (i = 0; i < info->dev_info.sw.dev_count; i++) {
		if (info->netdev[i]) {
			struct net_device *dev = info->netdev[i];

			if (netif_running(dev)) {
				netif_device_detach(dev);
				netdev_close(dev);
			}
		}
	}
	return 0;
}  /* netdev_suspend */

static void netdev_shutdown(struct platform_device *pdev)
{
	struct platform_info *info = platform_get_drvdata(pdev);
	int i;

	for (i = 0; i < info->dev_info.sw.dev_count; i++) {
		if (info->netdev[i]) {
			struct net_device *dev = info->netdev[i];

			if (netif_running(dev)) {
				netif_device_detach(dev);
				netdev_close(dev);
			}
		}
	}
}  /* netdev_shutdown */

static int net_device_present;

static void get_mac_addr(struct ksz_hw *hw, u8 *macaddr)
{
	int i;
	int n[6];

	i = sscanf(macaddr, "%x:%x:%x:%x:%x:%x",
		&n[0], &n[1], &n[2], &n[3], &n[4], &n[5]);
	if (MAC_ADDR_LEN == i) {
		for (i = 0; i < MAC_ADDR_LEN; i++)
			hw->override_addr[i] = (u8) n[i];
		hw->mac_override = true;
	}
}  /* get_mac_addr */

static int netdev_probe(struct platform_device *pdev)
{
	struct net_device *dev;
	struct dev_priv *priv;
	struct dev_info *hw_priv;
	struct ksz_hw *hw;
	struct ksz_sw *sw;
	struct platform_info *info;
	struct ksz_port *port;
	uint mem_start;
	int cnt;
	int i;
	int mib_port_count;
	int pi;
	int port_count;
	int err = -ENOMEM;

	info = kzalloc(sizeof(struct platform_info), GFP_KERNEL);
	if (!info)
		goto netdev_probe_devinfo_err;

	hw_priv = &info->dev_info;
	hw = &hw_priv->hw;
	sw = &hw_priv->sw;

	spin_lock_init(&hw_priv->hwlock);
	mutex_init(&hw_priv->lock);

	/* Assume device is WAN port. */
	sw->dev_count = 1;
	port_count = 1;
	mib_port_count = 1;
	hw->addr_list_size = 0;
	sw->mib_cnt = TOTAL_SWITCH_COUNTER_NUM;

	/* First device is WAN port. */
	if (0 == pdev->id) {
		mem_start = (uint) KS_VIO_BASE + KS_WAN_DMA_TX;

		/* WAN port does not have MIB counters. */
		mib_port_count = 0;
		sw->mib_port_cnt = mib_port_count;
		sw->mib_cnt = 0;

		hw_priv->mem_start = KS_IO_BASE + KS_WAN_DMA_TX;
		hw_priv->irq_count = 7;

		hw->intr_check = KS_INT_CHECK;
		hw->shift = 25;

		setup_wan_port_regs(sw);

		if (wan_mac_addr[0] != ':')
			get_mac_addr(hw, wan_mac_addr);

		sw->id = 0;

	/* LAN port is a switch with multiple ports. */
	} else {
		mem_start = (uint) KS_VIO_BASE + KS_LAN_DMA_TX;

		hw_priv->mem_start = KS_IO_BASE + KS_LAN_DMA_TX;
		hw_priv->irq_count = 6;

		hw->intr_check = KS_INT_CHECK & ~KS_INT_PHY;
		hw->shift = 12;

		setup_lan_port_regs(sw);

		if (lan_mac_addr[0] != ':')
			get_mac_addr(hw, lan_mac_addr);

#ifdef CONFIG_KSZ8695_STP
		if (stp) {
			fast_aging = 1;
			multi_dev = 1;
			sw->features |= STP_SUPPORT;
		}
#endif
		if (fast_aging)
			sw->overrides |= FAST_AGING;

		/* Multiple network device interfaces are required. */
		if (multi_dev) {
			sw->dev_count = SWITCH_PORT_NUM;
			hw->addr_list_size = SWITCH_PORT_NUM - 1;
		}

		/* Single network device has multiple ports. */
		if (1 == sw->dev_count) {
			port_count = SWITCH_PORT_NUM;
			mib_port_count = SWITCH_PORT_NUM;
		}
		sw->mib_port_cnt = TOTAL_PORT_NUM;
		sw->info = kzalloc(sizeof(struct ksz_sw_info), GFP_KERNEL);
		if (!sw->info)
			goto netdev_probe_netdev_err;

		sw->id = 1;
		for (i = 0; i < sw->mib_port_cnt; i++)
			sw->info->port_mib[i].mib_start = 0;
		sw->info->port_mib[HOST_PORT].mib_start = SWITCH_COUNTER_NUM;
	}
	mutex_init(&sw->lock);
	sw->hwlock = &hw_priv->lock;
	hw_priv->max_buf_size = MAX_RX_BUF_SIZE;

	hw_init(hw);

	/* Default MTU is 1500. */
	if (hw->features & IP_HEADER_ALIGN) {
		hw_priv->mtu = MAX_ETHERNET_PACKET_SIZE + 4;
		hw_priv->mtu += MAX_ALIGN_OFFSET;
	} else
		hw_priv->mtu = REGULAR_RX_BUF_SIZE;
	hw_priv->mtu = (hw_priv->mtu + 3) & ~3;

	if (ksz_alloc_mem(hw_priv))
		goto netdev_probe_mem_err;

	hw_priv->hw.io = (void __iomem *) mem_start;

	/* tasklet is enabled. */
	tasklet_init(&hw_priv->rx_tasklet, rx_proc_task,
		(unsigned long) hw_priv);
	tasklet_init(&hw_priv->tx_tasklet, tx_proc_task,
		(unsigned long) hw_priv);

	/* tasklet_enable will decrement the atomic counter. */
	tasklet_disable(&hw_priv->rx_tasklet);
	tasklet_disable(&hw_priv->tx_tasklet);

	for (i = 0; i < TOTAL_PORT_NUM; i++)
		init_waitqueue_head(&hw_priv->counter[i].counter);

	/* Read MAC address and initialize override address if not overrided. */
	hw_read_addr(hw);
	hw_setup(hw);
	if (sw->info) {
		sw_acquire(sw, sw->hwlock);
		sw_init(sw);
		sw_setup(sw);
		sw_release(sw, sw->hwlock);
	}
	hw_priv->wol_support = WOL_SUPPORT;
	hw_priv->wol_enable = 0;

	INIT_WORK(&hw_priv->mib_read, mib_read_work);

	/* 500 ms timeout */
	ksz_init_timer(&hw_priv->mib_timer_info, 500 * HZ / 1000,
		mib_monitor, hw_priv);

	for (i = 0; i < sw->dev_count; i++) {
		dev = alloc_etherdev(sizeof(struct dev_priv));
		if (!dev)
			goto netdev_probe_netdev_err;

		info->netdev[i] = dev;
		hw_priv->dev = dev;

		priv = netdev_priv(dev);
		priv->adapter = hw_priv;

		port = &priv->port;
		port->port_cnt = port_count;
		port->mib_port_cnt = mib_port_count;
		port->first_port = i;
		port->flow_ctrl = PHY_FLOW_CTRL;

		port->hw = hw;
		port->sw = sw;
		port->linked = &sw->port_info[port->first_port];

		for (cnt = 0, pi = i; cnt < port_count; cnt++, pi++) {
			sw->port_info[pi].port_id = pi;
			sw->port_info[pi].pdev = dev;
			sw->port_info[pi].state = media_disconnected;

			/* Turn off LED to indicate device not running. */
			port_set_led(pi + sw->id, 0);
		}

		priv->id = net_device_present;

		dev->mem_start = mem_start;
		err = netdev_create(dev);
		if (err)
			goto netdev_probe_netdev_err;

		err = init_sysfs(dev);
		if (err)
			goto netdev_probe_netdev_err;
		port_set_power_saving(port, true);
		net_device_present++;
	}
	hw_priv->basedev = info->netdev[0];
	sema_init(&hw_priv->proc_sem, 1);
	if (TOTAL_PORT_NUM == sw->mib_port_cnt) {
		err = init_sw_sysfs(hw_priv);
		if (err)
			goto netdev_probe_netdev_err;
	}
	request_mem_region(hw_priv->mem_start, BASE_IO_RANGE,
		info->netdev[0]->name);

	platform_set_drvdata(pdev, info);
	return 0;

netdev_probe_netdev_err:
	for (i = 0; i < sw->dev_count; i++) {
		if (info->netdev[i]) {
			netdev_free(info->netdev[i]);
			info->netdev[i] = NULL;
		}
	}

netdev_probe_mem_err:
	ksz_free_mem(hw_priv);
	kfree(sw->info);
	kfree(info);

netdev_probe_devinfo_err:
	return err;
}  /* netdev_probe */

static int netdev_remove(struct platform_device *pdev)
{
	int i;
	struct platform_info *info = platform_get_drvdata(pdev);
	struct dev_info *hw_priv = &info->dev_info;

	platform_set_drvdata(pdev, NULL);

	release_mem_region(hw_priv->mem_start, BASE_IO_RANGE);
	if (hw_priv->sw.info)
		exit_sw_sysfs(hw_priv);
	for (i = 0; i < hw_priv->sw.dev_count; i++) {
		if (info->netdev[i])
			netdev_free(info->netdev[i]);
	}
	ksz_free_mem(hw_priv);
	kfree(hw_priv->sw.info);
	kfree(info);
	return 0;
}  /* netdev_remove */

static void netdev_platform_release(struct device *device)
{
	struct platform_device *pdev;

	pdev = to_platform_device(device);
	kfree(pdev);
}  /* netdev_platform_release */

static struct platform_driver netdev_driver = {
	.probe		= netdev_probe,
	.remove		= netdev_remove,
	.suspend	= netdev_suspend,
	.resume		= netdev_resume,
	.shutdown	= netdev_shutdown,
	.driver		= {
		.name	= PLATFORM_DRV_NAME,
	},
};

static struct platform_device *ksz8695_platform[MAX_DEVICES];
static int device_present;

static void platform_free_devices(int num)
{
	struct platform_device *pdev;
	int i;

	for (i = 0; i < num; i++) {
		pdev = ksz8695_platform[i];
		if (pdev)
			platform_device_unregister(pdev);
	}
}  /* platform_free_devices */

static int __init platform_init(void)
{
	struct platform_device *pdev;
	int err;
	int i;

	memset(ksz8695_platform, 0, sizeof(ksz8695_platform));
	for (i = 0; i < MAX_DEVICES; i++) {
		pdev = kzalloc(sizeof(struct platform_device), GFP_KERNEL);
		if (!pdev) {
			err = -ENOMEM;
			goto device_reg_err;
		}

		pdev->name = PLATFORM_DRV_NAME;
		pdev->id = i;
		pdev->dev.release = netdev_platform_release;
		pdev->num_resources = 1;
		pdev->resource = &net_resources[i];

		if (platform_device_register(pdev)) {
			if (device_present)
				break;
			err = -ENODEV;
			goto device_reg_err;
		}

		ksz8695_platform[i] = pdev;
		++device_present;
	}

	err = platform_driver_register(&netdev_driver);
	if (err)
		goto device_reg_err;

	return 0;

device_reg_err:
	if (device_present)
		platform_free_devices(device_present);
	return err;
}  /* platform_init */

static void __exit platform_exit(void)
{
	platform_driver_unregister(&netdev_driver);
	platform_free_devices(device_present);
}  /* platform_exit */

static int __init ksz8695_init_module(void)
{
#ifdef DEBUG_MSG
	if (init_dbg())
		return -ENOMEM;
#endif

	printk(KERN_INFO "%s\n", version);

	return platform_init();
}

static void __exit ksz8695_cleanup_module(void)
{
	platform_exit();

#ifdef DEBUG_MSG
	exit_dbg();
#endif
}

module_init(ksz8695_init_module);
module_exit(ksz8695_cleanup_module);

MODULE_DESCRIPTION("KSZ8695 network driver");
MODULE_AUTHOR("Tristram Ha <Tristram.Ha@microchip.com>");
MODULE_LICENSE("GPL");

module_param_named(message, msg_enable, int, 0);
MODULE_PARM_DESC(message, "Message verbosity level (0=none, 31=all)");

module_param(lan_mac_addr, charp, 0);
module_param(wan_mac_addr, charp, 0);
module_param(fast_aging, int, 0);
module_param(multi_dev, int, 0);
module_param(stp, int, 0);
MODULE_PARM_DESC(lan_mac_addr, "LAN MAC address");
MODULE_PARM_DESC(wan_mac_addr, "WAN MAC address");
MODULE_PARM_DESC(fast_aging, "Fast aging");
MODULE_PARM_DESC(multi_dev, "Multiple device interfaces");
MODULE_PARM_DESC(stp, "STP support");
