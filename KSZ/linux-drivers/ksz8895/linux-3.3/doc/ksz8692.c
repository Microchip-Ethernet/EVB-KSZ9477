/**
 * Micrel KSZ8692 Ethernet driver
 *
 * Copyright (c) 2015-2016 Microchip Technology Inc.
 *	Tristram Ha <Tristram.Ha@microchip.com>
 *
 * Copyright (c) 2009-2015 Micrel, Inc.
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

#ifdef DEBUG
#if 1
#define DEBUG_MSG
#endif
#endif

#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/version.h>
#include <linux/ioport.h>
#include <linux/pci.h>
#include <linux/phy.h>
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

#if defined(CONFIG_MICREL_SWITCH) || defined(CONFIG_NET_DSA_TAG_TAIL)
#define HAVE_MICREL_SWITCH
#endif

#ifdef CONFIG_NET_PEGASUS_PASSTHRU
#define CONFIG_PASSTHRU
#endif

#if defined(CONFIG_SPI_FTDI) && defined(CONFIG_NET_PEGASUS)
#define INIT
#define DEVINIT
#define DEVINITDATA
#else
#define INIT __init
#define DEVINIT __devinit
#define DEVINITDATA __devinitdata
#endif

/* -------------------------------------------------------------------------- */

#define DESC_RX_ERROR_COND		\
	(DESC_RX_ERROR_CRC |		\
	DESC_RX_ERROR_RUNT |		\
	DESC_RX_ERROR_TOO_LONG |	\
	DESC_RX_ERROR_PHY)

#define DMA_BURST_SHIFT			24
#define DMA_BURST_DEFAULT		8

#define INT_RX_MASK			(INT_RX | INT_RX_OVERRUN)
#define INT_TX_MASK			(INT_TX | INT_TX_EMPTY)

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
/* Auto-Negotiation Link Partner Ability Register */
#define PHY_REG_REMOTE_CAPABILITY	5

#define PHY_AUTO_NEG_NEXT_PAGE		0x8000
#define PHY_ACKNOWLEDGE			0x4000
#define PHY_AUTO_NEG_REMOTE_FAULT	0x2000
#define PHY_AUTO_NEG_ASYM_PAUSE		0x0800
#define PHY_AUTO_NEG_SYM_PAUSE		0x0400
#define PHY_AUTO_NEG_100BT4		0x0200
#define PHY_AUTO_NEG_100BTX_FD		0x0100
#define PHY_AUTO_NEG_100BTX		0x0080
#define PHY_AUTO_NEG_10BT_FD		0x0040
#define PHY_AUTO_NEG_10BT		0x0020
#define PHY_AUTO_NEG_SELECTOR		0x001F
#define PHY_AUTO_NEG_802_3		0x0001

#define AUTO_NEGOTIATION_RESERVED	0x5000
#define REMOTE_CAPABILITY_RESERVED	0x1000

#define PHY_LINK_SUPPORT		\
	(PHY_AUTO_NEG_SYM_PAUSE |	\
	PHY_AUTO_NEG_ASYM_PAUSE |	\
	PHY_AUTO_NEG_100BT4 |		\
	PHY_AUTO_NEG_100BTX_FD |	\
	PHY_AUTO_NEG_100BTX |		\
	PHY_AUTO_NEG_10BT_FD |		\
	PHY_AUTO_NEG_10BT)

#define PHY_AUTO_NEG_PAUSE		\
	(PHY_AUTO_NEG_SYM_PAUSE | PHY_AUTO_NEG_ASYM_PAUSE)

/* Auto-Negotiation Expansion Register */
#define PHY_REG_AUTO_NEG_EXPANSION	6

#define PHY_PARALLEL_DETECT_FAULT	0x0010
#define PHY_REMOTE_NEXT_PAGE_ABLE	0x0008
#define PHY_LOCAL_NEXT_PAGE_ABLE	0x0004
#define PHY_PAGE_RECEIVED		0x0002
#define PHY_REMOTE_AUTO_NEG_ABLE	0x0001

#define AUTO_NEG_EXP_RESERVED		0xFFE0

/* Auto-Negotiation Next-Page Transmit Register */
#define PHY_REG_AUTO_NEG_NEXT_PAGE	7
/* Auto-Negotiation Link Partner Next-Page Receive Register */
#define PHY_REG_REMOTE_NEXT_PAGE	8

#define PHY_NEXT_PAGE			0x8000
#define PHY_ACKNOWLEDGE			0x4000
#define PHY_MESSAGE_PAGE		0x2000
#define PHY_ACKNOWLEDGE_2		0x1000
#define PHY_TOGGLE			0x0800
#define PHY_MESSAGE_FIELD		0x07FF

#define AUTO_NEG_NEXT_PAGE_RESERVED	0x4000

#define RX_MIB_COUNTER_NUM		20

#ifdef CONFIG_KSZ8692VA
#define WAN_RX_MIB_COUNTER_NUM		22
#define LAN_RX_MIB_COUNTER_NUM		20

#define PORT_COUNTER_NUM		\
	(WAN_RX_MIB_COUNTER_NUM + TX_MIB_COUNTER_NUM)
#else
#define WAN_RX_MIB_COUNTER_NUM		21
#define LAN_RX_MIB_COUNTER_NUM		22

#define PORT_COUNTER_NUM		\
	(LAN_RX_MIB_COUNTER_NUM + TX_MIB_COUNTER_NUM)
#endif
#define TX_MIB_COUNTER_NUM		11

#define WAN_PORT_COUNTER_NUM		\
	(WAN_RX_MIB_COUNTER_NUM + TX_MIB_COUNTER_NUM)
#define LAN_PORT_COUNTER_NUM		\
	(LAN_RX_MIB_COUNTER_NUM + TX_MIB_COUNTER_NUM)

#define TOTAL_PORT_COUNTER_NUM		(PORT_COUNTER_NUM + 2)

#define MIB_COUNTER_RX			0x00
#define MIB_COUNTER_RX_UNDERSIZE	0x01
#define MIB_COUNTER_RX_FRAGMENT		0x02
#define MIB_COUNTER_RX_OVERSIZE		0x03
#define MIB_COUNTER_RX_JABBER		0x04
#define MIB_COUNTER_RX_SYMBOL_ERR	0x05
#define MIB_COUNTER_RX_CRC_ERR		0x06
#define MIB_COUNTER_RX_ALIGNMENT_ERR	0x07
#define MIB_COUNTER_RX_CTRL_8808	0x08
#define MIB_COUNTER_RX_PAUSE		0x09
#define MIB_COUNTER_RX_BROADCAST	0x0A
#define MIB_COUNTER_RX_MULTICAST	0x0B
#define MIB_COUNTER_RX_UNICAST		0x0C
#define MIB_COUNTER_RX_OCTET_64		0x0D
#define MIB_COUNTER_RX_OCTET_65_127	0x0E
#define MIB_COUNTER_RX_OCTET_128_255	0x0F
#define MIB_COUNTER_RX_OCTET_256_511	0x10
#define MIB_COUNTER_RX_OCTET_512_1023	0x11
#define MIB_COUNTER_RX_OCTET_1024_1521	0x12
#define MIB_COUNTER_RX_OCTET_1522_2000	0x13

#define MIB_COUNTER_RX_OCTET_2001_2047	0x14

#define MIB_COUNTER_RX_OCTET_2001_9216	0x14
#define MIB_COUNTER_RX_OCTET_9217_9500	0x15

#define MIB_COUNTER_TX			(mib->tx_start)

#define MIB_COUNTER_TX_LATE_COLLISION	(MIB_COUNTER_TX + 1)
#define MIB_COUNTER_TX_PAUSE		(MIB_COUNTER_TX + 2)
#define MIB_COUNTER_TX_BROADCAST	(MIB_COUNTER_TX + 3)
#define MIB_COUNTER_TX_MULTICAST	(MIB_COUNTER_TX + 4)
#define MIB_COUNTER_TX_UNICAST		(MIB_COUNTER_TX + 5)
#define MIB_COUNTER_TX_DEFERRED		(MIB_COUNTER_TX + 6)
#define MIB_COUNTER_TX_TOTAL_COLLISION	(MIB_COUNTER_TX + 7)
#define MIB_COUNTER_TX_EXCESS_COLLISION	(MIB_COUNTER_TX + 8)
#define MIB_COUNTER_TX_SINGLE_COLLISION	(MIB_COUNTER_TX + 9)
#define MIB_COUNTER_TX_MULTI_COLLISION	(MIB_COUNTER_TX + 10)

#define MIB_COUNTER_PACKET_DROPPED	(mib->cnt_end)

#define MIB_COUNTER_CHECKSUM_DROPPED	(MIB_COUNTER_PACKET_DROPPED + 1)

/* -------------------------------------------------------------------------- */

#define KS_R				KS8692_READ_REG
#define KS_W				KS8692_WRITE_REG

/* -------------------------------------------------------------------------- */

#define MAC_ADDR_ORDER(i)		(ETH_ALEN - 1 - (i))

#define MAX_ETHERNET_BODY_SIZE		1500
#define ETHERNET_HEADER_SIZE		14

#define MAX_ETHERNET_PACKET_SIZE	\
	(MAX_ETHERNET_BODY_SIZE + ETHERNET_HEADER_SIZE)

#define REGULAR_RX_BUF_SIZE		2000
#define WAN_MAX_RX_BUF_SIZE		2047
#define LAN_MAX_TX_BUF_SIZE		2600
#define LAN_MAX_RX_BUF_SIZE		LAN_MAX_TX_BUF_SIZE
#define JUMBO_RX_BUF_SIZE		9216
#define JUMBO_MAX_TX_BUF_SIZE		9500
#define JUMBO_MAX_RX_BUF_SIZE		JUMBO_MAX_TX_BUF_SIZE

#ifdef CONFIG_KSZ8692VA
#define WAN_MAX_BUF_SIZE		JUMBO_MAX_RX_BUF_SIZE

/* RX descriptor length is masked at 0x400. */
#define LAN_MAX_BUF_SIZE		2044

#define WAN_RX_BUF_SIZE			LAN_MAX_RX_BUF_SIZE
#define LAN_RX_BUF_SIZE			REGULAR_RX_BUF_SIZE
#define WAN_TX_BUF_SIZE			(JUMBO_MAX_TX_BUF_SIZE - 4)
#define LAN_TX_BUF_SIZE			(WAN_MAX_RX_BUF_SIZE - 4)

#else
#define WAN_MAX_BUF_SIZE		WAN_MAX_RX_BUF_SIZE
#define LAN_MAX_BUF_SIZE		JUMBO_MAX_RX_BUF_SIZE

/* WAN port cannot handle receiving more than 2047-byte frames. */
#define WAN_RX_BUF_SIZE			REGULAR_RX_BUF_SIZE
#define LAN_RX_BUF_SIZE			LAN_MAX_RX_BUF_SIZE
#define WAN_TX_BUF_SIZE			(WAN_MAX_RX_BUF_SIZE - 4)
#define LAN_TX_BUF_SIZE			(JUMBO_MAX_TX_BUF_SIZE - 4)
#endif

#define MAX_MULTICAST_LIST		32

#define HW_MULTICAST_SIZE		8

#define BASE_IO_ADDR			KS_VIO_BASE
#define BASE_IO_RANGE			0x100

/* Most of the time the offset is just 2. */
#define MAX_ALIGN_OFFSET		3

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
#if defined(HAVE_MICREL_SWITCH)
#define NUM_OF_TX_DESC			64 * 2
#else
#define NUM_OF_TX_DESC			64
#endif

struct ksz_desc_rx_stat {
	u32 frame_len:14;
#ifdef CONFIG_KSZ8692VA
	u32 reserved1:1;
#else
	u32 high_prio:1;
#endif
	u32 frame_type:1;
	u32 err_crc:1;
	u32 err_runt:1;
	u32 err_too_long:1;
	u32 err_phy:1;
	u32 aligned:2;
#ifdef CONFIG_KSZ8692VA
	u32 high_prio:1;
	u32 reserved2:1;
	u32 multicast:1;
	u32 error:1;
	u32 csum_err_udp:1;
	u32 csum_err_tcp:1;
	u32 csum_err_ip:1;
#else
	u32 csum_cause:2;
	u32 csum_not_done:1;
	u32 csum_error:3;
	u32 error:1;
#endif
	u32 last_desc:1;
	u32 first_desc:1;
	u32 hw_owned:1;
};

struct ksz_desc_tx_stat {
	u32 reserved1:31;
	u32 hw_owned:1;
};

struct ksz_desc_rx_buf {
	u32 buf_size:14;
	u32 reserved3:11;
	u32 end_of_ring:1;
	u32 reserved4:6;
};

struct ksz_desc_tx_buf {
	u32 buf_size:14;
	u32 reserved3:6;
#ifdef CONFIG_KSZ8692VA
	u32 reserved4:5;
#else
	u32 reserved4:4;
	u32 csum_gen_icmp:1;
#endif
	u32 end_of_ring:1;
	u32 csum_gen_udp:1;
	u32 csum_gen_tcp:1;
	u32 csum_gen_ip:1;
	u32 last_seg:1;
	u32 first_seg:1;
	u32 intr:1;
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

#ifndef CONFIG_KSZ8692VA
#define TOTAL_ACL_NUM			32

struct ksz_acl_info {
	u32 data;
	u32 mask;
	u8 mac[ETH_ALEN];
	u8 offset;
	u8 protocol;
	u16 port;
	u16 reserved;
	u8 ip4_addr[4];
	u8 ip4_mask[4];
	u8 ip6_addr[16];
	u8 ip6_mask[16];
	u32 acl:8;
	u32 mode:8;
	u32 enable:1;
	u32 filter:1;
	u32 prio:1;
	u32 changed:1;
};
#endif

/**
 * struct ksz_hw_mib - KSZ8692 MIB data structure
 * @cnt_ptr:	Current pointer to MIB counter index.
 * @link_down:	Indication the link has just gone down.
 * @state:	Connection status of the port.
 * @mib_start:	The starting counter index.  Some ports do not start at 0.
 * @counter:	64-bit MIB counter value.
 * @dropped:	Temporary buffer to remember last read packet dropped values.
 *
 * MIB counters needs to be read periodically so that counters do not get
 * overflowed and give incorrect values.  A right balance is needed to
 * satisfy this condition and not waste too much CPU time.
 *
 * It is pointless to read MIB counters when the port is disconnected.  The
 * @state provides the connection status so that MIB counters are read only
 * when the port is connected.  The @link_down indicates the port is just
 * disconnected so that all MIB counters are read one last time to update the
 * information.
 */
struct ksz_hw_mib {
	int cnt_end;
	int tx_start;
	u8 cnt_ptr;
	u8 link_down;
	u8 state;
	u8 mib_start;

	u64 counter[TOTAL_PORT_COUNTER_NUM];
};

/* Adjust this number down if there is transmit problem in user space. */
#define MAX_TX_HELD_SIZE		51000

/* Hardware features and bug fixes. */
#define RESET_HANG_BUG			(1 << 0)
#define GIGABIT_RATE_CHANGE_BUG		(1 << 1)
#define MAX_RX_BUG			(1 << 2)
#define ICMP_CSUM_GEN_BUG		(1 << 3)
#define RX_HUGE_FRAME			(1 << 16)
#define IP_HEADER_ALIGN			(1 << 17)
#define RX_JUMBO_FRAME			(1 << 18)
#define ICMP_CSUM_GEN			(1 << 19)
#define RGMII_PHY			(1 << 20)
#define MII_PHY				(1 << 21)
#ifdef CONFIG_NET_PEGASUS_PASSTHRU
#define PASSTHRU			(1 << 24)
#endif
#if defined(HAVE_MICREL_SWITCH)
#define MII_SWITCH			(1 << 27)
#endif

/* Software overrides. */
#define PAUSE_FLOW_CTRL			(1 << 0)
#define MAX_RX_CRC_ERR			(1 << 2)
#define RX_LOOPBACK			(1 << 3)
#define RX_ALL				(1 << 4)
#define DATA_HEADER			(1 << 5)

/**
 * struct ksz_hw - KSZ8692 hardware data structure
 * @io:			Virtual address assigned.
 * @port_info:		Port information.
 * @port_mib:		Port MIB information.
 * @dev_count:		Number of network devices this hardware supports.
 * @dst_ports:		Destination ports in switch for transmission.
 * @id:			Hardware ID.  Used for display only.
 * @mib_cnt:		Number of MIB counters this hardware has.
 * @mib_port_cnt:	Number of ports with MIB counters.
 * @tx_cfg:		Cached transmit control settings.
 * @rx_cfg:		Cached receive control settings.
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

	struct ksz_hw_mib port_mib;

	u32 tx_cfg;
	u32 rx_cfg;
	u32 intr_mask;
	u32 intr_set;
	uint intr_blocked;

	struct ksz_desc_info rx_desc_info;
	struct ksz_desc_info tx_desc_info;

	int tx_int_cnt;
	int tx_int_mask;
	int tx_size;

	u32 reg_mib_cnt;

	u8 perm_addr[ETH_ALEN];
	u8 override_addr[ETH_ALEN];
	u8 *mac_addr;
	u8 mac_override;
	u8 promiscuous;
	u8 all_multi;
	u8 multi_list_size;
	u8 multi_list[MAX_MULTICAST_LIST][ETH_ALEN];
	u8 multi_bits[HW_MULTICAST_SIZE];

	u8 enabled;
	u8 rx_stop;
	u8 shift;
	u8 phy_shift;
	u8 phy_addr;

	u8 duplex;
	u16 speed;
	u8 force_link;
	u8 flow_ctrl;
	u8 reserved2[2];

#ifndef CONFIG_KSZ8692VA
	struct ksz_acl_info acl_info[TOTAL_ACL_NUM];

	u8 broadcast_cnt;
	u8 map_802_1p;
	u8 flag_block:1;
	u8 flag_broadcast:1;
	u8 flag_diffserv:1;
	u8 flag_802_1p:1;
	u8 reserved3;
	u32 diffserv0;
	u32 diffserv1;
#endif

	uint features;
	uint overrides;

	uint bad[COUNT_BAD_LAST];
	uint good[COUNT_GOOD_LAST];

	u64 counter[OID_COUNTER_LAST];
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

enum {
	/* Read-only entries. */
	PROC_INFO,

	/* Read-write entries. */
	PROC_SET_DUPLEX,
	PROC_SET_SPEED,
	PROC_SET_FORCE,
	PROC_SET_FLOW_CTRL,
	PROC_SET_MIB,
	PROC_SET_FEATURES,
	PROC_SET_OVERRIDES,

#ifndef CONFIG_KSZ8692VA
	PROC_SET_BROADCAST_ENABLE,
	PROC_SET_BROADCAST_COUNTER,

	PROC_SET_DIFFSERV_ENABLE,
	PROC_SET_DIFFSERV_MAPPING0,
	PROC_SET_DIFFSERV_MAPPING1,
	PROC_SET_DIFFSERV_SET,
	PROC_SET_DIFFSERV_UNSET,

	PROC_SET_802_1P_ENABLE,
	PROC_SET_802_1P_MAPPING,
	PROC_SET_802_1P_SET,
	PROC_SET_802_1P_UNSET,

	PROC_SET_ACL_BLOCK_UNMATCHED,
#endif
};

#ifndef CONFIG_KSZ8692VA
enum {
	/* ACL specific read-write entries. */
	PROC_8692_SET_ACL_ENABLE,
	PROC_8692_SET_ACL_RX_HI_PRIORITY,
	PROC_8692_SET_ACL_FILTER_MATCHED,
	PROC_8692_SET_ACL_MODE,

	PROC_8692_SET_ACL_DATA,
	PROC_8692_SET_ACL_MASK,
	PROC_8692_SET_ACL_MAC,
	PROC_8692_SET_ACL_OFFSET,
	PROC_8692_SET_ACL_PROTOCOL,
	PROC_8692_SET_ACL_PORT,
	PROC_8692_SET_ACL_IPV4_ADDR,
	PROC_8692_SET_ACL_IPV4_MASK,
	PROC_8692_SET_ACL_IPV6_ADDR,
	PROC_8692_SET_ACL_IPV6_MASK,
};
#endif

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

#if defined(CONFIG_MICREL_SWITCH_EMBEDDED)
#include <linux/of.h>
#endif
#if defined(CONFIG_MICREL_KSZ8863_EMBEDDED)
#include "spi-ksz8863.c"
#elif defined(CONFIG_MICREL_KSZ8463_EMBEDDED)
#include "spi-ksz8463.c"
#elif defined(CONFIG_MICREL_KSZ8795_EMBEDDED)
#include "spi-ksz8795.c"
#elif defined(CONFIG_MICREL_KSZ8895_EMBEDDED)
#include "spi-ksz8895.c"
#elif defined(CONFIG_MICREL_KSZ9897_EMBEDDED)
#include "spi-ksz9897.c"
#elif defined(CONFIG_HAVE_KSZ8863)
#include "ksz_cfg_8863.h"
#elif defined(CONFIG_HAVE_KSZ8463)
#include "ksz_cfg_8463.h"
#elif defined(CONFIG_HAVE_KSZ9897)
#include "ksz_cfg_9897.h"
#elif defined(CONFIG_HAVE_KSZ8795)
#include "ksz_cfg_8795.h"
#elif defined(CONFIG_HAVE_KSZ8895)
#include "ksz_cfg_8895.h"
#endif

#ifdef HAVE_MICREL_SWITCH
static inline int sw_is_switch(struct ksz_sw *sw)
{
	return sw != NULL;
}
#else
#include "ksz_common.h"

#include "ksz_req.h"
#endif

#if !defined(CONFIG_MICREL_SWITCH_EMBEDDED)
#include "ksz_common.c"
#endif

/* -------------------------------------------------------------------------- */

#ifdef CONFIG_NET_DSA_TAG_TAIL
#include "setup_dsa.c"
#endif

/* -------------------------------------------------------------------------- */

#if defined(HAVE_MICREL_SWITCH) && !defined(CONFIG_MICREL_SWITCH_EMBEDDED)
#include "ksz_sw_phy.h"
#ifndef HAVE_MICREL_SWITCH
#define SKIP_MICREL_SWITCH_SYSFS
#endif
#include "ksz_spi_net.h"
#endif

/**
 * struct dev_info - Network device information data structure
 * @dev:		Pointer to network device.
 * @main_dev:		Pointer to main network device.
 * @pdev:		Pointer to base device.
 * @hw:			Hardware structure.
 * @desc_pool:		Physical memory used for descriptor pool.
 * @hwlock:		Spinlock to prevent hardware from accessing.
 * @lock:		Mutex lock to prevent device from accessing.
 * @dev_rcv:		Receive process function used.
 * @last_skb:		Socket buffer allocated for descriptor rx fragments.
 * @skb_index:		Buffer index for receiving fragments.
 * @skb_len:		Buffer length for receiving fragments.
 * @mib_read:		Workqueue to read MIB counters.
 * @mib_timer_info:	Timer to read MIB counters.
 * @counter:		Used for MIB reading.
 * @mtu:		Current MTU used.
 * @max_buf_size:	The maximum allowed receive buffer size.
 * @rx_buf_size:	The maximum normal receive buffer size.
 * @tx_buf_size:	The maximum allowed transmit buffer size.
 * @rx_tasklet:		Receive processing tasklet.
 * @tx_tasklet:		Transmit processing tasklet.
 * @link_reset:		Workqueue to reset hardware after link change.
 * @tx_reset:		Workqueue to access PHY device after tx timeout.
 * @promisc_reset:	Workqueue to reset promiscuous mode.
 * @gigabit_rate:	Used for link reset.
 * @link_reset_timeout: Used for link reset.
 * @wol_enable:		Wake-on-LAN enable set by ethtool.
 * @wol_support:	Wake-on-LAN support used by ethtool.
 * @mem_start:		The starting memory address.
 * @irq_name:		The interrupt names.
 */
struct dev_info {
	struct net_device *dev;
	struct net_device *main_dev;
	struct device *pdev;
#ifdef CONFIG_NET_PEGASUS_PASSTHRU
	struct net_device *otherdev;
	struct sk_buff_head tx_queue;
	int otherdev_running;
#endif

	struct ksz_hw hw;
	struct ksz_shared_mem desc_pool;

	spinlock_t hwlock;
	struct mutex lock;

#if defined(HAVE_MICREL_SWITCH)
	struct ksz_sw *sw;
	struct phy_device *phydev;
#endif
#ifdef HAVE_MICREL_SWITCH
	struct ksz_sw_sysfs sysfs;
#ifdef CONFIG_1588_PTP
	struct ksz_ptp_sysfs ptp_sysfs;
#endif
#endif
	struct ksz_dev_attr *ksz_attrs[TOTAL_ACL_NUM];
	struct attribute **acl_attrs[TOTAL_ACL_NUM];
	struct semaphore proc_sem;

	int (*dev_rcv)(struct dev_info *);

	struct sk_buff *last_skb;
	struct sk_buff *new_skb;
	int skb_index;
	int skb_len;

	struct work_struct mib_read;
	struct ksz_timer_info mib_timer_info;
	struct ksz_counter_info counter;

	int mtu;
	int max_buf_size;
	int rx_buf_size;
	int tx_buf_size;
	int opened;

	struct tasklet_struct rx_tasklet;
	struct tasklet_struct tx_tasklet;

	struct work_struct link_reset;
	struct work_struct tx_reset;
	struct delayed_work promisc_reset;
	int gigabit_rate;
	int link_reset_timeout;

	int wol_enable;
	int wol_support;

	unsigned int mem_start;

	char irq_name[6][40];
};

#if !defined(HAVE_MICREL_SWITCH)
/**
 * struct dev_priv - Network device private data structure
 * @adapter:		Adapter device information.
 * @stats:		Network statistics.
 * @phydev:		The PHY device associated with the device.
 * @phy_pause:		Workqueue to pause the PHY state machine.
 * @proc_info:		Proc information.
 * @proc_main:		Main proc entry.
 * @proc_acl_info:	Proc information for each ACL.
 * @proc_acldir:	ACL directory proc entry.
 * @proc_acl:		ACL proc entry.
 * @proc_sem:		Semaphore for proc accessing.
 * @id:			Device ID.
 * @mii_if:		MII interface information.
 * @advertising:	Temporary variable to store advertised settings.
 * @msg_enable:		The message flags controlling driver output.
 * @media_state:	The connection status of the device.
 * @multicast:		The all multicast state of the device.
 * @promiscuous:	The promiscuous state of the device.
 */
struct dev_priv {
	struct dev_info *adapter;
	struct net_device_stats stats;

	struct phy_device *phydev;
	struct work_struct phy_pause;

	int id;

	struct mii_if_info mii_if;
	u32 advertising;

	u32 msg_enable;
	int media_state;
	int multicast;
	int promiscuous;
	u8 phy_addr;
};
#endif

/* -------------------------------------------------------------------------- */

#define DRV_NAME			"pegasus-net"
#define DEVICE_NAME			"Pegasus"
#define DRV_VERSION			"1.0.11"
#define DRV_RELDATE			"Dec 25, 2015"

static char version[] DEVINITDATA =
	"Micrel " DEVICE_NAME " " DRV_VERSION " (" DRV_RELDATE ")";

#ifdef CONFIG_KSZ8692VA
static u8 DEFAULT_MAC_ADDRESS[] = { 0x00, 0x10, 0xA1, 0x86, 0x92, 0x01 };
#else
static u8 DEFAULT_MAC_ADDRESS[] = { 0x00, 0x10, 0xA1, 0x96, 0x92, 0x01 };
#endif

#ifdef DEBUG
#define NET_MSG_ENABLE  (NETIF_MSG_DRV | NETIF_MSG_PROBE | NETIF_MSG_LINK)
#else
#define NET_MSG_ENABLE  0
#endif

#if 0
#define HIGH_MEM_SUPPORT
#endif

#define SKB_COPY_MAX			64

#ifdef CONFIG_KSZ_NAPI
#define ksz_rx_skb			netif_receive_skb
#define ksz_rx_quota(count, quota)	min(count, quota)
#else
#define ksz_rx_skb			netif_rx
#define ksz_rx_quota(count, quota)	count
#endif

/*
 * THa  2007/07/10
 * Multicast hash table function does not work correctly in KSZ8692!
 */
#ifdef CONFIG_KSZ8692VA
#define MULTICAST_LEN  5
#else
#define MULTICAST_LEN  6
#endif

/* -------------------------------------------------------------------------- */

#if defined(HAVE_MICREL_SWITCH)
#ifdef CONFIG_1588_PTP

extern unsigned int ksz_system_bus_clock;

static u32 get_clk_cnt(void)
{
	return KS_R(KS8692_TIMER1_COUNTER);
}
#endif

static u8 get_priv_state(struct net_device *dev)
{
	struct dev_priv *priv = netdev_priv(dev);

	return priv->state;
}  /* get_priv_state */

static void set_priv_state(struct net_device *dev, u8 state)
{
	struct dev_priv *priv = netdev_priv(dev);

	priv->state = state;
}  /* set_priv_state */

static struct ksz_port *get_priv_port(struct net_device *dev)
{
	struct dev_priv *priv = netdev_priv(dev);

	return &priv->port;
}  /* get_priv_port */
#endif

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
	data &= ~(INT_CHECK << hw->shift);
	hw->intr_blocked = hw->intr_mask;
	KS_W(KS_INT_ENABLE, data);
	data = KS_R(KS_INT_ENABLE);
	hw->intr_set = (data >> hw->shift) & INT_CHECK;
}

static inline void hw_set_intr(struct ksz_hw *hw, uint interrupt)
{
	u32 data;

	data = KS_R(KS_INT_ENABLE);
	data &= ~(INT_CHECK << hw->shift);
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
	hw->intr_set = (read_intr >> hw->shift) & INT_CHECK;
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
	hw->intr_set = (read_intr >> hw->shift) & INT_CHECK;
	KS_W(KS_INT_ENABLE, read_intr);
}

static inline void hw_read_intr(struct ksz_hw *hw, uint *status)
{
	*status = (KS_R(KS_INT_STATUS) >> hw->shift) & INT_CHECK;
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
	(*desc)->sw.buf.data &= ~DESC_RX_MASK;
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
	(*desc)->sw.buf.data &= ~DESC_TX_MASK;
}

static inline void put_tx_pkt(struct ksz_desc_info *info)
{
	info->next--;
	info->next &= info->mask;
	info->avail++;
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

#ifndef CONFIG_PEGASUS_NO_MDIO
#define STA_TIMEOUT			15

static void hw_init_phy_ctrl(void)
{
#ifdef CONFIG_KSZ8692VA
/* 5.00 MHz * 2 */
#define F_MDC	1000
#elif defined(CONFIG_KSZ8692VB)
/* 4.00 MHz * 2 */
#define F_MDC	800
#else
/* 6.25 MHz * 2 */
#define F_MDC	1250
#endif

	u32 data;
	uint clk_dividend;
	uint apb;

	/* Get APB system clock in Hz. */
	data = KS_R(KS8692_SYSTEM_BUS_CLOCK);
	apb = data & SYSTEM_BUS_CLOCK_MASK;

	switch (apb) {
	case SYSTEM_BUS_CLOCK_200:
		apb = 20000;
		break;
	case SYSTEM_BUS_CLOCK_166:
		apb = 16600;
		break;
	case SYSTEM_BUS_CLOCK_125:
		apb = 12500;
		break;
	case SYSTEM_BUS_CLOCK_50:
	default:
		apb = 5000;
		break;
	}

	/* Calculate CLK_DIVIDEND value -- F_mdc = F_apb / (CLK_DIVIDEND * 2) */
	clk_dividend = apb / F_MDC;

	data = KS_R(KS8692_STA_CONF);
	if ((data & STA_CLK_DIVIDEND_MASK) != (clk_dividend << 1)) {
		int status;
		int timeout = STA_TIMEOUT;

		/* Disable STA first. */
		data &= ~STA_MDIO_ENABLE;
		do {
			udelay(2);
			status = KS_R(KS8692_STA_STATUS) & STA_STATUS_MASK;
		} while (status != STA_IDLE && --timeout);
		KS_W(KS8692_STA_CONF, data);

		/* Set CLK_DIVIDEND value to STA Configuration Register. */
		data &= ~STA_CLK_DIVIDEND_MASK;
		data |= (clk_dividend << 1);
	}
	data |= STA_MDIO_ENABLE;
	data |= STA_AUTO_POLL;
	KS_W(KS8692_STA_CONF, data);

	KS_W(KS8692_STA_INT_CTRL, KS_R(KS8692_STA_INT_CTRL) |
		PHY1_DN_ENABLE | PHY1_UP_ENABLE |
		PHY0_DN_ENABLE | PHY0_UP_ENABLE);
}  /* hw_init_phy_ctrl */
#endif

/* -------------------------------------------------------------------------- */

#ifndef CONFIG_KSZ8692VA
enum {
	ACL_MODE_MAC,

	/* Need to be in this order. */
	ACL_MODE_OFFSET,
	ACL_MODE_PROTOCOL,

	ACL_MODE_PORT_DST,
	ACL_MODE_PORT_SRC,
	ACL_MODE_PORT_BOTH,

	ACL_MODE_IPV4_DST,
	ACL_MODE_IPV4_SRC,
	ACL_MODE_IPV4_BOTH,

	ACL_MODE_IPV6_DST,
	ACL_MODE_IPV6_SRC,
	ACL_MODE_IPV6_BOTH,

	ACL_MODE_LAST
};

/**
 * hw_cfg_acl_block - configure the ACL block feature
 * @hw:		The hardware instance.
 * @enable:	The flag to enable the feature or not.
 *
 * This routine turns on or off the ACL block feature.
 */
static void hw_cfg_acl_block(struct ksz_hw *hw, int enable)
{
	u32 data;

	data = readl(hw->io + REG_DMA_MISC_CFG);
	if (enable)
		data |= DMA_BLOCK_PACKET;
	else
		data &= ~DMA_BLOCK_PACKET;
	writel(data, hw->io + REG_DMA_MISC_CFG);
}  /* hw_cfg_acl_block */

static u32 acl_data(u8 *addr)
{
	u32 data;

	data = ((u32) addr[0] << 24) | ((u32) addr[1] << 16) |
		((u32) addr[2] << 8) | addr[3];
	return data;
}

/**
 * acl_reg - return correct AL register
 * @acl:	The ACL index.
 * @reg:	The ACL offset register.
 *
 * This helper function returns the correct ACL register to access.
 */
static inline u32 acl_reg(int acl, u32 reg)
{
	int offset = 0;

	if (acl >= 0x10) {
		acl -= 0x10;
		offset = 4;
	}
	acl *= 0x10;
	return reg + acl + offset;
}  /* acl_reg */

/**
 * hw_cfg_acl - program ACL configuration register
 * @hw:		The hardware instance.
 * @enable:	The flag to enable the bit or not.
 * @mask:	The mask bit to change in the register.
 *
 * This routine programs the ACL configuration register.
 */
static void hw_cfg_acl(struct ksz_hw *hw, int acl, int enable, uint mask)
{
	u32 data;
	u32 reg = acl_reg(acl, REG_ACL_CONF1);

	data = readl(hw->io + reg);
	if (enable)
		data |= mask;
	else
		data &= ~mask;
	writel(data, hw->io + reg);
	dbg_msg(" cfg %04X = %08x\n", reg, data);
}  /* hw_cfg_acl */

static inline void hw_cfg_acl_enable(struct ksz_hw *hw, int acl, int enable)
{
	hw_cfg_acl(hw, acl, enable, ACL_ENABLE);
}

static inline void hw_cfg_acl_filter(struct ksz_hw *hw, int acl, int filter)
{
	hw_cfg_acl(hw, acl, filter, ACL_FILTER_EN);
}

static inline void hw_cfg_acl_prio(struct ksz_hw *hw, int acl, int prio)
{
	hw_cfg_acl(hw, acl, prio, ACL_HI_PRIO);
}

static inline void hw_cfg_acl_ipv6(struct ksz_hw *hw, int acl, int enable)
{
	hw_cfg_acl(hw, acl, enable, ACL_IPV6);
}

/**
 * hw_set_acl_cfg - program the ACL registers.
 * @hw:		The hardware instance.
 * @acl:	The ACL index.
 * @filter:	The filter enable bit.
 * @prio:	The receive high priority bit.
 * @data:	The ACL data value.
 * @mask:	The ACL mask value.
 * @cfg:	The ACL configuration value.
 *
 * This helper routine programs the ACL registers.
 *
 * The comparison logic is (pattern | mask == data | mask).
 */
static void hw_set_acl_cfg(struct ksz_hw *hw, int acl, int filter, int prio,
	u32 data, u32 mask, u32 cfg)
{
	u32 reg;

	reg = acl_reg(acl, REG_ACL_DATA1);
	writel(data, hw->io + reg);
	dbg_msg(" data %04X = %08x, ", reg, data);
	reg = acl_reg(acl, REG_ACL_MASK1);
	writel(mask, hw->io + reg);
	dbg_msg("mask %04X = %08x, ", reg, mask);
	reg = acl_reg(acl, REG_ACL_CONF1);

	/* These bits are not set in @cfg before calling this routine. */
	if (filter)
		cfg |= ACL_FILTER_EN;
	if (prio)
		cfg |= ACL_HI_PRIO;
	writel(cfg, hw->io + reg);
	dbg_msg("cfg %04X = %08x\n", reg, cfg);
}  /* hw_set_acl_cfg */

/**
 * hw_set_acl_mac - filter MAC address
 * @hw:		The hardware instance.
 * @acl:	The ACL index.
 * @filter:	The filter enable bit.
 * @prio:	The receive high priority bit.
 * @addr:	The MAC address.
 *
 * This routine programs the ACL entry to filter MAC address.
 */
static void hw_set_acl_mac(struct ksz_hw *hw, int acl, int filter, int prio,
	u8 *addr)
{
	u32 cfg;
	u32 data;
	u32 mask;

	data = acl_data(&addr[2]);
	mask = ((u32) addr[0] << 8) | addr[1];
	cfg = ACL_ENABLE | ACL_MAC_SA;
	hw_set_acl_cfg(hw, acl, filter, prio, data, mask, cfg);
}  /* hw_set_acl_mac */

/**
 * hw_set_acl_offset - filter data pattern
 * @hw:		The hardware instance.
 * @acl:	The ACL index.
 * @filter:	The filter enable bit.
 * @prio:	The receive high priority bit.
 * @offset:	The offset value
 * @data:	The pattern data value.
 * @mask:	The pattern mask.
 *
 * This routine programs the ACL entry to filter data pattern.
 */
static void hw_set_acl_offset(struct ksz_hw *hw, int acl, int filter, int prio,
	int offset, u32 data, u32 mask)
{
	u32 cfg;

	WARN_ON(offset <= ACL_DATA_OFFSET_MASK);

	cfg = ACL_ENABLE | ACL_OFFSET_SCHEME | offset;
	hw_set_acl_cfg(hw, acl, filter, prio, data, mask, cfg);
}  /* hw_set_acl_offset */

/**
 * hw_set_acl_protocol - filter packet protocol
 * @hw:		The hardware instance.
 * @acl:	The ACL index.
 * @filter:	The filter enable bit.
 * @prio:	The receive high priority bit.
 * @data:	The protocol number.
 * @mask:	The protocol mask.
 *
 * This routine programs the ACL entry to filter packet protocol.
 */
static void hw_set_acl_protocol(struct ksz_hw *hw, int acl, int filter,
	int prio, u8 data, u8 mask)
{
	u32 cfg;

	cfg = ACL_ENABLE | ACL_PROTOCOL;
	hw_set_acl_cfg(hw, acl, filter, prio, data, mask, cfg);
}  /* hw_set_acl_protocol */

/**
 * hw_set_acl_port - filter port number.
 * @hw:		The hardware instance.
 * @acl:	The ACL index.
 * @filter:	The filter enable bit.
 * @prio:	The receive high priority bit.
 * @mode:	The filter mode.
 * @data:	The port number.
 * @mask:	The port mask.
 *
 * This routine programs the ACL entry to filter port number.
 */
static void hw_set_acl_port(struct ksz_hw *hw, int acl, int filter, int prio,
	int mode, u16 data, u16 mask)
{
	u32 cfg;

	WARN_ON(1 <= mode && mode <= 3);

	cfg = ACL_ENABLE;
	if (mode & 1)
		cfg |= ACL_PORT_DA;
	if (mode & 2)
		cfg |= ACL_PORT_SA;
	hw_set_acl_cfg(hw, acl, filter, prio, data, mask, cfg);
}  /* hw_set_acl_port */

/**
 * hw_set_acl_ipv4 - filter IPv4 address
 * @hw:		The hardware instance.
 * @acl:	The ACL index.
 * @filter:	The filter enable bit.
 * @prio:	The receive high priority bit.
 * @mode:	The filter mode.
 * @addr:	The IPv4 address.
 * @ip_mask:	The IPv4 mask.
 *
 * This routine programs the ACL entry to filter IPv4 address.
 */
static void hw_set_acl_ipv4(struct ksz_hw *hw, int acl, int filter, int prio,
	int mode, u8 *addr, u8 *ip_mask)
{
	u32 cfg;
	u32 data;
	u32 mask;

	WARN_ON(1 <= mode && mode <= 3);

	data = acl_data(addr);
	mask = acl_data(ip_mask);
	cfg = ACL_ENABLE;
	if (mode & 1)
		cfg |= ACL_IPV4_DA;
	if (mode & 2)
		cfg |= ACL_IPV4_SA;
	hw_set_acl_cfg(hw, acl, filter, prio, data, mask, cfg);
}  /* hw_set_acl_ipv4 */

/**
 * hw_set_acl_ipv6 - filter IPv6 address
 * @hw:		The hardware instance.
 * @acl:	The ACL index.
 * @filter:	The filter enable bit.
 * @prio:	The receive high priority bit.
 * @mode:	The filter mode.
 * @addr:	The IPv6 address.
 * @ip_mask:	The IPv6 mask.
 *
 * This routine programs the ACL entry to filter IPv6 address.
 */
static void hw_set_acl_ipv6(struct ksz_hw *hw, int acl, int filter, int prio,
	int mode, u8 *addr, u8 *ip_mask)
{
	u32 cfg;
	u32 reg;
	u32 data;
	int i;

	WARN_ON(!(acl % 4));
	WARN_ON(1 <= mode && mode <= 3);

	reg = acl_reg(acl, REG_ACL_DATA1);
	reg += 0x30;
	for (i = 0; i < 4; i++) {
		data = acl_data(addr);
		writel(data, hw->io + reg);
		dbg_msg(" %04X = %08x,", reg, data);
		reg -= 0x10;
		addr += 4;
	}
	dbg_msg("\n");
	reg = acl_reg(acl, REG_ACL_MASK1);
	reg += 0x30;
	for (i = 0; i < 4; i++) {
		data = acl_data(ip_mask);
		writel(data, hw->io + reg);
		dbg_msg(" %04X = %08x,", reg, data);
		reg -= 0x10;
		ip_mask += 4;
	}
	dbg_msg("\n");
	reg = acl_reg(acl, REG_ACL_CONF1);
	cfg = ACL_ENABLE | ACL_IPV6;
	if (mode & 1)
		cfg |= ACL_IPV6_DA;
	if (mode & 2)
		cfg |= ACL_IPV6_SA;
	if (filter)
		cfg |= ACL_FILTER_EN;
	if (prio)
		cfg |= ACL_HI_PRIO;
	writel(cfg, hw->io + reg);
	dbg_msg(" %04X = %08x\n", reg, cfg);
}  /* hw_set_acl_ipv6 */

/**
 * hw_setup_acl - setup ACL when its information is changed
 * @hw:		The hardware instance.
 * @acl:	The ACL information.
 * @first:	The first in the range of modes to be compared.
 * @last:	The last in the range of modes to be compared.
 *
 * This routine setups the ACL after the information is changed.
 */
static void hw_setup_acl(struct ksz_hw *hw, struct ksz_acl_info *acl,
	int first, int last)
{
	/* This routine is called only after ACL information was changed. */
	acl->changed = 1;

	/* Program ACL only when enabled and the right mode is being used. */
	if (acl->enable && first <= acl->mode && acl->mode <= last) {

		/* The change is written to hardware. */
		acl->changed = 0;
		switch (acl->mode) {
		case ACL_MODE_MAC:
			hw_set_acl_mac(hw, acl->acl, acl->filter, acl->prio,
				acl->mac);
			break;
		case ACL_MODE_OFFSET:
			hw_set_acl_offset(hw, acl->acl, acl->filter, acl->prio,
				acl->offset, acl->data, acl->mask);
			break;
		case ACL_MODE_PROTOCOL:
			hw_set_acl_protocol(hw, acl->acl, acl->filter,
				acl->prio, acl->protocol, acl->mask);
			break;
		case ACL_MODE_PORT_DST:
		case ACL_MODE_PORT_SRC:
		case ACL_MODE_PORT_BOTH:
			hw_set_acl_port(hw, acl->acl, acl->filter, acl->prio,
				acl->mode - (ACL_MODE_PORT_DST - 1),
				acl->port, acl->mask);
			break;
		case ACL_MODE_IPV4_DST:
		case ACL_MODE_IPV4_SRC:
		case ACL_MODE_IPV4_BOTH:
			hw_set_acl_ipv4(hw, acl->acl, acl->filter, acl->prio,
				acl->mode - (ACL_MODE_IPV4_DST - 1),
				acl->ip4_addr, acl->ip4_mask);
			break;
		case ACL_MODE_IPV6_DST:
		case ACL_MODE_IPV6_SRC:
		case ACL_MODE_IPV6_BOTH:
		{
			int i;

			hw_set_acl_ipv6(hw, acl->acl, acl->filter, acl->prio,
				acl->mode - (ACL_MODE_IPV6_DST - 1),
				acl->ip6_addr, acl->ip6_mask);

			/* IPv6 ACL uses all next 3 entries. */
			for (i = 0; i < 3; i++) {
				acl++;
				if (acl->enable) {
					acl->enable = 0;
					acl->changed = 1;
					hw_cfg_acl_enable(hw, acl->acl, 0);
				}
			}
			break;
		}
		default:
			break;
		}
	}
}  /* hw_setup_acl */

/* -------------------------------------------------------------------------- */

/**
 * hw_set_broadcast_traffic - program broadcast traffic control value
 * @hw:		The hardware instance.
 * @enable:	The flag to enable broadcast control or not.
 * @val:	The preload value.
 *
 * This routine programs the broadcast traffic control preload value into the
 * hardware register.
 */
static void hw_set_broadcast_traffic(struct ksz_hw *hw, u8 enable, u8 val)
{
	u32 data = 0;

	if (enable)
		data = val | DMA_BROADCAST_CNTL_EN;
	writel(data, hw->io + REG_BROADCAST_CNTL);
}  /* hw_set_broadcast_traffic */

/* -------------------------------------------------------------------------- */

/**
 * hw_set_diffserv_prio - program DiffServ priority
 * @hw:		The hardware instance.
 * @enable:	The flag to enable DiffServ or not.
 * @map0:	The low part of 64-bit DiffServ priority mapping.
 * @map1:	The high part of 64-bit DiffServ priority mapping.
 *
 * This routine programs the DiffServ priority into the hardware registers.
 */
static void hw_set_diffserv_prio(struct ksz_hw *hw, u8 enable, u32 map0,
	u32 map1)
{
	if (enable) {
		writel(map0, hw->io + REG_QOS_TOS0);
		writel(map1, hw->io + REG_QOS_TOS1);
		writel(QOS_TOS_ENABLE, hw->io + REG_QOS_TOS2);
	} else
		writel(0, hw->io + REG_QOS_TOS2);
}  /* hw_set_diffserv_prio */

/**
 * hw_set_802_1p_prio - program 802.1p priority
 * @hw:		The hardware instance.
 * @enable:	The flag to enable 802.1p or not.
 * @mapping:	The 802.1p priority mapping.
 *
 * This routine programs the 802.1p priority into the hardware register.
 */
static void hw_set_802_1p_prio(struct ksz_hw *hw, u8 enable, u8 mapping)
{
	u32 data = 0;

	if (enable)
		data = mapping | QOS_802_1P_ENABLE;
	writel(data, hw->io + REG_QOS_TAG);
}  /* hw_set_802_1p_prio */
#endif

/* -------------------------------------------------------------------------- */

/**
 * hw_cfg_wol - configure Wake-on-LAN features
 * @hw:		The hardware instance.
 * @frame:	The pattern frame bit.
 * @set:	The flag indicating whether to enable or disable.
 *
 * This routine is used to enable or disable certain Wake-on-LAN features.
 */
static void hw_cfg_wol(struct ksz_hw *hw, u16 frame, int set)
{
	u32 data;

	data = readl(hw->io + REG_WOL_CTRL);
	if (set)
		data |= frame;
	else
		data &= ~frame;
	writel(data, hw->io + REG_WOL_CTRL);
}  /* hw_cfg_wol */

/**
 * hw_set_wol_frame - program Wake-on-LAN pattern
 * @hw:		The hardware instance.
 * @i:		The frame index.
 * @mask_size:	The size of the mask.
 * @mask:	Mask to ignore certain bytes in the pattern.
 * @frame_size:	The size of the frame.
 * @pattern:	The frame data.
 *
 * This routine is used to program Wake-on-LAN pattern.
 */
static void hw_set_wol_frame(struct ksz_hw *hw, int i, uint mask_size,
	u8 *mask, uint frame_size, u8 *pattern)
{
	int bits;
	int from;
	int len;
	int to;
	u32 crc;
	u8 data[64];
	u8 val = 0;

	if (frame_size > mask_size * 8)
		frame_size = mask_size * 8;
	if (frame_size > 64)
		frame_size = 64;

	i *= REG_FRAME1_CRC - REG_FRAME0_CRC;
	bits = len = from = to = 0;
	do {
		if (bits) {
			if ((val & 1))
				data[to++] = pattern[from];
			val >>= 1;
			++from;
			--bits;
		} else {
			val = mask[len];
			writeb(val, hw->io + REG_FRAME0_MASK0 + i + len);
			++len;
			if (val)
				bits = 8;
			else
				from += 8;
		}
	} while (from < (int) frame_size);
	if (val) {
		bits = mask[len - 1];
		val <<= (from % 8);
		bits &= ~val;
		writeb(bits, hw->io + REG_FRAME0_MASK0 + i + len - 1);
	}
	crc = ether_crc(to, data);
	writel(crc, hw->io + REG_FRAME0_CRC + i);
}  /* hw_set_wol_frame */

/**
 * hw_add_wol_arp - add ARP pattern
 * @hw:		The hardware instance.
 * @ip_addr:	The IPv4 address assigned to the device.
 *
 * This routine is used to add ARP pattern for waking up the host.
 */
static void hw_add_wol_arp(struct ksz_hw *hw, u8 *ip_addr)
{
	u8 mask[6] = { 0x3F, 0xF0, 0x3F, 0x00, 0xC0, 0x03 };
	u8 pattern[42] = {
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x08, 0x06,
		0x00, 0x01, 0x08, 0x00, 0x06, 0x04, 0x00, 0x01,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00 };

	memcpy(&pattern[38], ip_addr, 4);
	hw_set_wol_frame(hw, 3, 6, mask, 42, pattern);
}  /* hw_add_wol_arp */

/**
 * hw_add_wol_bcast - add broadcast pattern
 * @hw:		The hardware instance.
 *
 * This routine is used to add broadcast pattern for waking up the host.
 */
static void hw_add_wol_bcast(struct ksz_hw *hw)
{
	u8 mask[] = { 0x3F };
	u8 pattern[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

	hw_set_wol_frame(hw, 2, 1, mask, ETH_ALEN, pattern);
}  /* hw_add_wol_bcast */

/**
 * hw_add_wol_mcast - add multicast pattern
 * @hw:		The hardware instance.
 *
 * This routine is used to add multicast pattern for waking up the host.
 *
 * It is assumed the multicast packet is the ICMPv6 neighbor solicitation used
 * by IPv6 ping command.  Note that multicast packets are filtred through the
 * multicast hash table, so not all multicast packets can wake up the host.
 */
static void hw_add_wol_mcast(struct ksz_hw *hw)
{
	u8 mask[] = { 0x3F };
	u8 pattern[] = { 0x33, 0x33, 0xFF, 0x00, 0x00, 0x00 };

	memcpy(&pattern[3], &hw->override_addr[3], 3);
	hw_set_wol_frame(hw, 1, 1, mask, 6, pattern);
}  /* hw_add_wol_mcast */

/**
 * hw_add_wol_ucast - add unicast pattern
 * @hw:		The hardware instance.
 *
 * This routine is used to add unicast pattern to wakeup the host.
 *
 * It is assumed the unicast packet is directed to the device, as the hardware
 * can only receive them in normal case.
 */
static void hw_add_wol_ucast(struct ksz_hw *hw)
{
	u8 mask[] = { 0x3F };

	hw_set_wol_frame(hw, 0, 1, mask, ETH_ALEN, hw->override_addr);
}  /* hw_add_wol_ucast */

/**
 * hw_enable_wol - enable Wake-on-LAN
 * @hw:		The hardware instance.
 * @wol_enable:	The Wake-on-LAN settings.
 * @net_addr:	The IPv4 address assigned to the device.
 *
 * This routine is used to enable Wake-on-LAN depending on driver settings.
 */
static void hw_enable_wol(struct ksz_hw *hw, u32 wol_enable, u8 *net_addr)
{
	hw_cfg_wol(hw, WOL_MAGIC_ENABLE, (wol_enable & WAKE_MAGIC));
	hw_cfg_wol(hw, WOL_FRAME0_ENABLE, (wol_enable & WAKE_UCAST));
	hw_add_wol_ucast(hw);
	hw_cfg_wol(hw, WOL_FRAME1_ENABLE, (wol_enable & WAKE_MCAST));
	hw_add_wol_mcast(hw);
	hw_cfg_wol(hw, WOL_FRAME2_ENABLE, (wol_enable & WAKE_BCAST));
	hw_cfg_wol(hw, WOL_FRAME3_ENABLE, (wol_enable & WAKE_ARP));
	hw_add_wol_arp(hw, net_addr);
}  /* hw_enable_wol */

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
	uint data;

	data = KS_R(KS8692_STA_PHY);
	data >>= hw->phy_shift;
	hw->phy_addr = PHY_MAX_ADDR;
	if (data & STA_PHY0_VALID)
		hw->phy_addr = data & STA_PHY0_ADD_MASK;

	hw->flow_ctrl = PHY_FLOW_CTRL;

	/* Setup hardware features or bug workarounds. */
#ifndef CONFIG_KSZ8692_MII
	hw->features |= RGMII_PHY;
#endif

#ifdef CONFIG_NET_PEGASUS_PASSTHRU
	hw->features |= PASSTHRU;
#else
	hw->features |= IP_HEADER_ALIGN;
#endif

	hw->features |= ICMP_CSUM_GEN;

/*
 * THa  2008/10/07
 * Enable ICMP checksum generation by itself does not work.
 */
	hw->features |= ICMP_CSUM_GEN_BUG;

/*
 * THa  2008/10/31
 * KSZ8692 has a hardware bug that resetting the DMA engine hangs the whole
 * system.  The position of the hardware reset code influences whether system
 * hangs or not.  As this problem happens only with 166 MHz system bus clock
 * and above, one workaround is to set the clock to 125 MHz before resetting
 * and then set the clock back to original value.
 */
	hw->features |= RESET_HANG_BUG;

/*
 * THa  2008/07/24
 * Enable to avoid transmit failure when switching from Gigabit to 100 Mbit.
 */
	hw->features |= GIGABIT_RATE_CHANGE_BUG;

	hw->features |= MAX_RX_BUG;
	hw->overrides |= MAX_RX_CRC_ERR;

#ifndef CONFIG_KSZ8692VA
	data = KS_R(KS8692_SPARE_REG);
	data |= IPV6_UDP_FRAG_PASS;
	KS_W(KS8692_SPARE_REG, data);
#endif
	return 1;
}  /* hw_init */

static int empty_addr(u8 *addr)
{
	u16 *addr1 = (u16 *) addr;
	u16 *addr2 = (u16 *) &addr[2];
	u16 *addr3 = (u16 *) &addr[4];

	return 0 == *addr1 && 0 == *addr2 && 0 == *addr3;
}  /* empty_addr */

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

	for (i = 0; i < ETH_ALEN; i++)
		writeb(hw->override_addr[MAC_ADDR_ORDER(i)],
			hw->io + REG_DMA_MAC_ADDR_LO + i);

	dbg_msg("set addr: ");
	dbp_mac_addr(hw->override_addr);
	dbg_msg("\n");
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

	for (i = 0; i < ETH_ALEN; i++)
		hw->perm_addr[MAC_ADDR_ORDER(i)] = readb(hw->io +
			REG_DMA_MAC_ADDR_LO + i);

	dbg_msg("get addr: ");
	dbp_mac_addr(hw->perm_addr);
	dbg_msg("\n");

	if (!hw->mac_override) {
		memcpy(hw->override_addr, hw->perm_addr, ETH_ALEN);
		if (empty_addr(hw->override_addr)) {
			memcpy(hw->perm_addr, DEFAULT_MAC_ADDRESS, ETH_ALEN);
			memcpy(hw->override_addr, DEFAULT_MAC_ADDRESS,
				ETH_ALEN);
			hw->override_addr[5] = hw->phy_addr;
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
#ifndef CONFIG_KSZ8692VA
	int entry;
#endif
	uint uninitialized_var(data);

	if (hw->features & RESET_HANG_BUG) {
		data = KS_R(KS8692_SYSTEM_BUS_CLOCK);
		KS_W(KS8692_SYSTEM_BUS_CLOCK,
			(data & ~SYSTEM_BUS_CLOCK_MASK) |
			SYSTEM_BUS_CLOCK_50);
	}
	writel(DMA_TX_CTRL_RESET, hw->io + REG_DMA_TX_CTRL);
	if (hw->features & RESET_HANG_BUG)
		KS_W(KS8692_SYSTEM_BUS_CLOCK, data);

	/* MAC address always got erased after engine reset. */
	hw_set_addr(hw);

#ifndef CONFIG_KSZ8692VA
	if (hw->flag_broadcast)
		hw_set_broadcast_traffic(hw, true, hw->broadcast_cnt);
	if (hw->flag_diffserv)
		hw_set_diffserv_prio(hw, true,
			hw->diffserv0, hw->diffserv1);
	if (hw->flag_802_1p)
		hw_set_802_1p_prio(hw, true, hw->map_802_1p);
	if (hw->flag_block)
		hw_cfg_acl_block(hw, true);
	for (entry = 0; entry < TOTAL_ACL_NUM; entry++) {
		struct ksz_acl_info *acl = &hw->acl_info[entry];

		acl->changed = 1;
		if (acl->enable)
			hw_setup_acl(hw, acl, acl->mode, acl->mode);
	}
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
	hw->tx_cfg = (DMA_TX_CTRL_PAD_ENABLE | DMA_TX_CTRL_CRC_ENABLE |
		(DMA_BURST_DEFAULT << DMA_BURST_SHIFT) | DMA_TX_CTRL_ENABLE);

	/* Setup receive control. */
	hw->rx_cfg = (DMA_RX_CTRL_BROADCAST | DMA_RX_CTRL_UNICAST |
		(DMA_BURST_DEFAULT << DMA_BURST_SHIFT) | DMA_RX_CTRL_ENABLE);
	hw->rx_cfg |= DMA_RX_CTRL_MULTICAST;

#ifndef CONFIG_KSZ8692VA
	hw->rx_cfg |= DMA_RX_CTRL_CSUM_TCP;
#endif
#ifdef HAVE_MICREL_SWITCH
	if (hw->features & MII_SWITCH) {
		hw->rx_cfg |= DMA_RX_CTRL_FLOW_ENABLE;
		hw->tx_cfg |= DMA_TX_CTRL_FLOW_ENABLE;
	}
#endif

	/* Only work for IP packets! */
	if (hw->features & IP_HEADER_ALIGN)
		hw->rx_cfg |= DMA_RX_CTRL_IP_ALIGN;

	if (hw->features & RX_HUGE_FRAME)
		hw->rx_cfg |= DMA_RX_CTRL_ERROR;

	if (hw->overrides & RX_LOOPBACK)
		hw->promiscuous++;
#ifdef CONFIG_NET_PEGASUS_PASSTHRU
	if (hw->features & PASSTHRU)
		hw->promiscuous++;
#endif

	if (hw->all_multi)
		hw->rx_cfg |= DMA_RX_CTRL_ALL_MULTICAST;
	if (hw->promiscuous)
		hw->rx_cfg |= DMA_RX_CTRL_PROMISCUOUS;

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
	hw->intr_mask = INT_RX | INT_TX | INT_RX_OVERRUN;
}  /* hw_setup_intr */

/* -------------------------------------------------------------------------- */

static void ksz_check_desc_num(struct ksz_desc_info *info)
{
#define MIN_DESC_SHIFT  1

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

static inline void dump_desc(struct ksz_desc_info *desc_info)
{
	int i;
	struct ksz_hw_desc *desc = desc_info->ring_virt;

	for (i = 0; i < desc_info->alloc; i++, desc++)
		printk(KERN_DEBUG "%p %08x %08x %08x %08x\n", desc,
			desc->ctrl.data, desc->buf.data,
			desc->addr, desc->next);
}

static void hw_init_desc(struct ksz_desc_info *desc_info, int transmit)
{
	int i;
	u32 phys = desc_info->ring_phys;
	struct ksz_hw_desc *desc = desc_info->ring_virt;
	struct ksz_desc *cur = desc_info->ring;
	struct ksz_desc *previous = NULL;

	for (i = 0; i < desc_info->alloc; i++) {
		cur->phw = desc++;
		phys += desc_info->size;
		previous = cur++;
		previous->phw->next = cpu_to_le32(phys);
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
	writel(tx_addr, hw->io + REG_DMA_TX_ADDR);
	writel(rx_addr, hw->io + REG_DMA_RX_ADDR);
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
	writel(DMA_START, hw->io + REG_DMA_RX_START);
}

/**
 * hw_start_rx - start receiving
 * @hw:		The hardware instance.
 *
 * This routine starts the receive function of the hardware.
 */
static void hw_start_rx(struct ksz_hw *hw)
{
	writel(hw->rx_cfg, hw->io + REG_DMA_RX_CTRL);

#if 0
	/* Notify when the receive stops. */
	hw->intr_mask |= INT_RX_STOPPED;
#endif
	writel(DMA_START, hw->io + REG_DMA_RX_START);
	hw_ack_intr(hw, INT_RX_STOPPED);
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
#if 0
	hw_turn_off_intr(hw, INT_RX_STOPPED);
#endif
	writel((hw->rx_cfg & ~DMA_RX_CTRL_ENABLE), hw->io + REG_DMA_RX_CTRL);
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
	writel(hw->tx_cfg, hw->io + REG_DMA_TX_CTRL);
}  /* hw_start_tx */

/**
 * hw_stop_tx - stop transmitting
 * @hw:		The hardware instance.
 *
 * This routine stops the transmit function of the hardware.
 */
static void hw_stop_tx(struct ksz_hw *hw)
{
	writel((hw->tx_cfg & ~DMA_TX_CTRL_ENABLE), hw->io + REG_DMA_TX_CTRL);
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

#define MIN_TX_DESC			5

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
	int extra = 0;

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

#if defined(HAVE_MICREL_SWITCH)
	/* May add another descriptor for tail tag. */
	extra = 1;
#endif

	/* This will not happen if MIN_TX_DESC is big enough. */
	if (physical + extra > hw->tx_desc_info.avail)
		return 1;

	/* Allow to use tx fragments but signal queue stop. */
	if (hw->tx_desc_info.avail <= 1 + MIN_TX_DESC)
		return physical;

	return hw->tx_desc_info.avail;
}  /* hw_alloc_pkt */

static void hw_free_pkt(struct ksz_hw *hw, int length)
{
	/* Put back the allocated descriptor. */
	put_tx_pkt(&hw->tx_desc_info);

	/* Keep track of number of transmit descriptors used so far. */
	--hw->tx_int_cnt;
	if (hw->tx_int_cnt < 0)
		hw->tx_int_cnt = 0;
	hw->tx_size -= length;
	if (hw->tx_size < 0)
		hw->tx_size = 0;
}  /* hw_free_pkt */

/**
 * hw_send_pkt - mark packet for transmission
 * @hw:		The hardware instance.
 *
 * This routine marks the packet for transmission in PCI version.
 */
static void hw_send_pkt(struct ksz_hw *hw, struct ksz_desc *first)
{
	struct ksz_desc *cur = hw->tx_desc_info.cur;

	cur->sw.buf.tx.last_seg = true;

	/* Interrupt only after specified number of descriptors used. */
	if (hw->tx_int_cnt > hw->tx_int_mask) {
		cur->sw.buf.tx.intr = true;
		hw->tx_int_cnt = 0;
		hw->tx_size = 0;
	}

	release_desc(cur);
	if (first != cur)
		release_desc(first);

	writel(0, hw->io + REG_DMA_TX_START);
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

	for (i = 0; i < HW_MULTICAST_SIZE; i++) {
		hw->multi_bits[i] = 0;
		writeb(0, hw->io + REG_MULTICAST_0_OFFSET + i);
	}
}  /* hw_clr_multicast */

static void set_multi_hash(u8 *addr, u8 *bits)
{
	int position;
	int index;
	int value;

	position = (ether_crc(MULTICAST_LEN, addr) >> 26) & 0x3f;
	index = position >> 3;
	value = 1 << (position & 7);
	bits[index] |= (u8) value;
}  /* set_multi_hash */

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

	memset(hw->multi_bits, 0, sizeof(u8) * HW_MULTICAST_SIZE);

	for (i = 0; i < hw->multi_list_size; i++)
		set_multi_hash(hw->multi_list[i], hw->multi_bits);

	for (i = 0; i < HW_MULTICAST_SIZE; i++)
		writeb(hw->multi_bits[i], hw->io + REG_MULTICAST_0_OFFSET + i);
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
		hw->rx_cfg |= DMA_RX_CTRL_ALL_MULTICAST;
	else
		hw->rx_cfg &= ~DMA_RX_CTRL_ALL_MULTICAST;

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
		hw->rx_cfg |= DMA_RX_CTRL_PROMISCUOUS;
	else
		hw->rx_cfg &= ~DMA_RX_CTRL_PROMISCUOUS;

	if (hw->enabled)
		hw_start_rx(hw);
}  /* hw_set_promiscuous */

/* -------------------------------------------------------------------------- */

/**
 * hw_r_mib_cnt - read MIB counter
 * @hw:		The hardware instance.
 * @addr:	The address of the counter.
 * @cnt:	Buffer to store the counter.
 *
 * This routine reads a MIB counter of the hardware port.
 */
static void hw_r_mib_cnt(struct ksz_hw *hw, int addr, u64 *cnt)
{
	u32 data;

	data = KS_R(hw->reg_mib_cnt + addr * 4);
	*cnt += data;
}  /* hw_r_mib_cnt */

/**
 * hw_r_cnt - read MIB counters periodically
 * @hw:		The hardware instance.
 *
 * This routine is used to read the counters of the port periodically to avoid
 * counter overflow.  The hardware should be acquired first before calling this
 * routine.
 *
 * Return non-zero when not all counters not read.
 */
static int hw_r_cnt(struct ksz_hw *hw)
{
	u32 data;
	struct ksz_hw_mib *mib = &hw->port_mib;

	while (mib->cnt_ptr < mib->cnt_end) {
		hw_r_mib_cnt(hw, mib->cnt_ptr, &mib->counter[mib->cnt_ptr]);
		++mib->cnt_ptr;
	}
	data = readl(hw->io + REG_PKT_DROP);
	mib->counter[mib->cnt_ptr++] += data;
	data = readl(hw->io + REG_CHECKSUM_DROP);
	mib->counter[mib->cnt_ptr++] += data;
	mib->cnt_ptr = 0;
	return 0;
}  /* hw_r_cnt */

/**
 * hw_init_cnt - initialize MIB counter values
 * @hw:		The hardware instance.
 *
 * This routine is used to initialize all counters to zero if the hardware
 * cannot do it after reset.
 */
static void hw_init_cnt(struct ksz_hw *hw)
{
	u32 data;
	struct ksz_hw_mib *mib = &hw->port_mib;

	mib->cnt_ptr = 0;
	do {
		hw_r_mib_cnt(hw, mib->cnt_ptr, &mib->counter[mib->cnt_ptr]);
		++mib->cnt_ptr;
	} while (mib->cnt_ptr < mib->cnt_end);
	data = readl(hw->io + REG_PKT_DROP);
	data = readl(hw->io + REG_CHECKSUM_DROP);
	memset((void *) mib->counter, 0, sizeof(u64) * TOTAL_PORT_COUNTER_NUM);
	mib->cnt_ptr = 0;
}  /* hw_init_cnt */

/* -------------------------------------------------------------------------- */

#ifdef CONFIG_NET_PEGASUS_PASSTHRU
static struct sk_buff_head skb_pool;
static struct dev_info *first_dev;

static int alloc_skb_pool(struct dev_info *adapter)
{
	int i;
	struct sk_buff *skb;

	skb_queue_head_init(&skb_pool);
	for (i = 0; i < NUM_OF_RX_DESC * 8; i++) {
		skb = alloc_skb(adapter->mtu, GFP_KERNEL);
		if (!skb)
			return -ENOMEM;

		/*
		 * Use to indicate socket buffer is from socket buffer pool as
		 * ip_summed is never set to CHECKSUM_UNNECESSARY when
		 * transmitting.
		 */
		skb->ip_summed = CHECKSUM_UNNECESSARY;
		skb_queue_tail(&skb_pool, skb);
	}
	return 0;
}  /* alloc_skb_pool */

static void free_skb_pool(void)
{
	struct sk_buff *skb, *tmp;

	skb_queue_walk_safe(&skb_pool, skb, tmp) {
		skb_unlink(skb, &skb_pool);
		kfree_skb(skb);
	}
}  /* free_skb_pool */

/**
 * send_frame - send frame directly after receiving
 * @skb:	Socket buffer.
 * @dev:	Network device.
 *
 * This routine is used to send a frame out after receiving.
 */
static int send_frame(struct sk_buff *skb, dma_addr_t dma)
{
	struct ksz_desc *desc;
	struct dev_priv *priv = netdev_priv(skb->dev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_hw *hw = &hw_priv->hw;
	struct ksz_desc_info *info = &hw->tx_desc_info;
	struct ksz_dma_buf *dma_buf;
	int left;

	left = hw_alloc_pkt(hw, skb->len, 1);
	if (!left) {
		netif_stop_queue(skb->dev);
		if (dma)
			skb_queue_tail(&hw_priv->tx_queue, skb);
		return NETDEV_TX_BUSY;
	}

	desc = info->cur;

	dma_buf = DMA_BUFFER(desc);
	dma_buf->len = skb->len;
	dma_buf->dma = dma;

	if (!dma)
		dma_buf->dma = dma_map_single(
			hw_priv->pdev, skb->data, dma_buf->len,
			DMA_TO_DEVICE);
	set_tx_buf(desc, dma_buf->dma);
	set_tx_len(desc, dma_buf->len);

	dma_buf->skb = skb;

	hw_send_pkt(hw, desc);
	return 0;
}  /* send_frame */

static void send_stored_frames(struct net_device *dev)
{
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	struct sk_buff *skb;

	while (hw_priv->tx_queue.qlen) {
		skb = skb_dequeue(&hw_priv->tx_queue);
		if (send_frame(skb, 0)) {
			skb_queue_head(&hw_priv->tx_queue, skb);
			break;
		}
	}
}  /* send_stored_frames */

static inline int filter_packet(u8 *addr, struct sk_buff *skb, void *ptr)
{
	if (skb->data[0] & 1) {
		if (0xFF == skb->data[0])
			return PACKET_BROADCAST;

#ifdef CONFIG_1588_PTP
		do {
			struct ptp_info *ptr = ptr;

			/* Do not pass PTP messages. */
			if (ptp && ptp->ops->check_msg(skb->data, NULL))
				return PACKET_HOST;
		} while (0);
#endif
		return PACKET_MULTICAST;
	} else {
		if (!memcmp(skb->data, addr, ETH_ALEN))
			return PACKET_HOST;
	}
	return PACKET_OTHERHOST;
}  /* filter_packet */
#endif

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
#ifdef CONFIG_NET_PEGASUS_PASSTHRU
			if (adapter->otherdev)
				dma_buf->skb = skb_dequeue(&skb_pool);
			else
#endif
			if (hw->features & IP_HEADER_ALIGN)
				/* skb->data != skb->head */
				dma_buf->skb = dev_alloc_skb(dma_buf->len);
			else
				/* skb->data == skb->head */
				dma_buf->skb = alloc_skb(dma_buf->len,
					GFP_ATOMIC);
		}
		if (dma_buf->skb && !dma_buf->dma) {
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

#define MIB_8692_RX			0x00
#define MIB_8692_RX_UNDERSIZE		0x01
#define MIB_8692_RX_FRAGMENT		0x02
#define MIB_8692_RX_OVERSIZE		0x03
#define MIB_8692_RX_JABBER		0x04
#define MIB_8692_RX_SYMBOL_ERR		0x05
#define MIB_8692_RX_CRC_ERR		0x06
#define MIB_8692_RX_ALIGNMENT_ERR	0x07
#define MIB_8692_RX_CTRL_8808		0x08
#define MIB_8692_RX_PAUSE		0x09
#define MIB_8692_RX_BROADCAST		0x0A
#define MIB_8692_RX_MULTICAST		0x0B
#define MIB_8692_RX_UNICAST		0x0C
#define MIB_8692_RX_OCTET_64		0x0D
#define MIB_8692_RX_OCTET_65_127	0x0E
#define MIB_8692_RX_OCTET_128_255	0x0F
#define MIB_8692_RX_OCTET_256_511	0x10
#define MIB_8692_RX_OCTET_512_1023	0x11
#define MIB_8692_RX_OCTET_1024_1521	0x12
#define MIB_8692_RX_OCTET_1522_2000	0x13
#define MIB_8692_RX_OCTET_2001_9216	0x14
#define MIB_8692_RX_OCTET_9217_9500	0x15

#define MIB_8692_TX			0x16

#define MIB_8692_TX_LATE_COLLISION	(MIB_8692_TX + 1)
#define MIB_8692_TX_PAUSE		(MIB_8692_TX + 2)
#define MIB_8692_TX_BROADCAST		(MIB_8692_TX + 3)
#define MIB_8692_TX_MULTICAST		(MIB_8692_TX + 4)
#define MIB_8692_TX_UNICAST		(MIB_8692_TX + 5)
#define MIB_8692_TX_DEFERRED		(MIB_8692_TX + 6)
#define MIB_8692_TX_TOTAL_COLLISION	(MIB_8692_TX + 7)
#define MIB_8692_TX_EXCESS_COLLISION	(MIB_8692_TX + 8)
#define MIB_8692_TX_SINGLE_COLLISION	(MIB_8692_TX + 9)
#define MIB_8692_TX_MULTI_COLLISION	(MIB_8692_TX + 10)

#define MIB_8692_PACKET_DROPPED		(MIB_8692_TX + 11)

#define MIB_8692_CHECKSUM_DROPPED	(MIB_8692_PACKET_DROPPED + 1)

static struct {
	char string[20];
} ksz8692_mib_names[TOTAL_PORT_COUNTER_NUM] = {
	{ "rx           " },
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
	{ "rx_9217     " },

	{ "tx           " },
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

	{ "pkt_drop" },
	{ "csum_err_drop" },
};

static struct {
	int rx;
	int tx;
} ksz8692_mib_display[(TOTAL_PORT_COUNTER_NUM + 1) / 2] = {
	{ MIB_8692_RX, MIB_8692_TX },
	{ MIB_8692_RX_PAUSE, MIB_8692_TX_PAUSE },
	{ MIB_8692_RX_BROADCAST, MIB_8692_TX_BROADCAST },
	{ MIB_8692_RX_MULTICAST, MIB_8692_TX_MULTICAST },
	{ MIB_8692_RX_UNICAST, MIB_8692_TX_UNICAST },
	{ MIB_8692_RX_OCTET_64, MIB_8692_RX_OCTET_65_127 },
	{ MIB_8692_RX_OCTET_128_255, MIB_8692_RX_OCTET_256_511 },
	{ MIB_8692_RX_OCTET_512_1023, MIB_8692_RX_OCTET_1024_1521 },
	{ MIB_8692_RX_OCTET_1522_2000, MIB_8692_RX_OCTET_2001_9216 },
	{ MIB_8692_RX_OCTET_9217_9500, -1 },
	{ MIB_8692_RX_UNDERSIZE, MIB_8692_RX_OVERSIZE },
	{ MIB_8692_RX_FRAGMENT, MIB_8692_RX_JABBER },
	{ MIB_8692_RX_SYMBOL_ERR, MIB_8692_RX_CRC_ERR },
	{ MIB_8692_RX_ALIGNMENT_ERR, MIB_8692_RX_CTRL_8808 },
	{ MIB_8692_TX_LATE_COLLISION, MIB_8692_TX_DEFERRED },
	{ MIB_8692_TX_TOTAL_COLLISION, MIB_8692_TX_EXCESS_COLLISION },
	{ MIB_8692_TX_SINGLE_COLLISION, MIB_8692_TX_MULTI_COLLISION },
	{ MIB_8692_PACKET_DROPPED, MIB_8692_CHECKSUM_DROPPED },
};

static int display_mib_counters(struct ksz_hw *hw, char *buf)
{
	int cnt;
	int len = 0;
	int num = hw->port_mib.cnt_end;
	int tx_start = 1;
	struct ksz_hw_mib *mib = &hw->port_mib;

#ifndef CONFIG_KSZ8692VA
	num += 2;
#endif
	if (MIB_8692_TX == mib->tx_start)
		--tx_start;
	num += tx_start;
	for (cnt = 0; cnt < (num + 1) / 2; cnt++) {
		int rx = ksz8692_mib_display[cnt].rx;
		int tx = ksz8692_mib_display[cnt].tx;
		int rx_i = rx;
		int tx_i = tx;

		if (tx < 0) {
			/* No rx entry. */
			if (rx == mib->tx_start)
				continue;
			if (buf)
				len += sprintf(buf + len,
					"%s\t= %-20llu\n",
					ksz8692_mib_names[rx].string,
					mib->counter[rx]);
			else
				printk(KERN_INFO "%s\t= %-20llu\n",
					ksz8692_mib_names[rx].string,
					mib->counter[rx]);
			continue;
		}
		if (rx_i >= mib->tx_start)
			rx_i -= tx_start;
		if (tx_i >= mib->tx_start)
			tx_i -= tx_start;
		if (buf)
			len += sprintf(buf + len,
				"%s\t= %-20llu\t%s\t= %-20llu\n",
				ksz8692_mib_names[rx].string,
				mib->counter[rx_i],
				ksz8692_mib_names[tx].string,
				mib->counter[tx_i]);
		else
			printk(KERN_INFO "%s\t= %-20llu\t%s\t= %-20llu\n",
				ksz8692_mib_names[rx].string,
				mib->counter[rx_i],
				ksz8692_mib_names[tx].string,
				mib->counter[tx_i]);
	}
	return len;
}  /* display_mib_counter */

/* -------------------------------------------------------------------------- */

static void set_flow_ctrl(struct ksz_hw *hw, int rx, int tx)
{
	u32 rx_cfg;
	u32 tx_cfg;

	rx_cfg = hw->rx_cfg;
	tx_cfg = hw->tx_cfg;
	if (rx)
		hw->rx_cfg |= DMA_RX_CTRL_FLOW_ENABLE;
	else
		hw->rx_cfg &= ~DMA_RX_CTRL_FLOW_ENABLE;
	if (tx)
		hw->tx_cfg |= DMA_TX_CTRL_FLOW_ENABLE;
	else
		hw->tx_cfg &= ~DMA_TX_CTRL_FLOW_ENABLE;
	if (hw->enabled) {
		if (rx_cfg != hw->rx_cfg)
			writel(hw->rx_cfg, hw->io + REG_DMA_RX_CTRL);
		if (tx_cfg != hw->tx_cfg)
			writel(hw->tx_cfg, hw->io + REG_DMA_TX_CTRL);
	}
}  /* set_flow_ctrl */

static void determine_flow_ctrl(struct ksz_hw *hw, int local, int remote)
{
	int rx;
	int tx;

	if (hw->overrides & PAUSE_FLOW_CTRL)
		return;

	rx = tx = 0;
	if (hw->force_link)
		rx = tx = 1;
	if (remote & PHY_AUTO_NEG_SYM_PAUSE) {
		if (local & PHY_AUTO_NEG_SYM_PAUSE)
			rx = tx = 1;
		else if ((remote & PHY_AUTO_NEG_ASYM_PAUSE) &&
				(local & PHY_AUTO_NEG_PAUSE) ==
				PHY_AUTO_NEG_ASYM_PAUSE)
			tx = 1;
	} else if (remote & PHY_AUTO_NEG_ASYM_PAUSE) {
		if ((local & PHY_AUTO_NEG_PAUSE) == PHY_AUTO_NEG_PAUSE)
			rx = 1;
	}
	set_flow_ctrl(hw, rx, tx);
}  /* determine_flow_ctrl */

static u32 determine_connect_cfg(struct ksz_hw *hw, int speed, int duplex)
{
	u32 data;

	data = readl(hw->io + REG_DMA_MISC_CFG);
	data &= ~(MISC_PORT_1000M | MISC_PORT_100M | MISC_PORT_FD);
	data &= ~MISC_RGMII_SELECT;
	data &= ~(MISC_RGMII_TX_DELAY | MISC_RGMII_RX_DELAY);
	data &= ~DMA_JUMBO_FRAME_SUPPORT;
	if (1000 == speed)
		data |= MISC_PORT_1000M;
	else if (100 == speed)
		data |= MISC_PORT_100M;
	if (1 == duplex)
		data |= MISC_PORT_FD;
	data |= (MISC_EXC_DEFER_ENABLE | MISC_RECEIVE_ENABLE);

	return data;
}  /* determine_connect_cfg */

static void hw_cfg_link_speed(struct ksz_hw *hw, struct phy_device *phydev)
{
	u32 data;
	int local;
	int remote;
	int link = phydev->link;
	int speed = phydev->speed;
	int duplex = phydev->duplex;
	struct mii_bus *bus = phydev->bus;

#ifdef HAVE_MICREL_SWITCH
	if (hw->features & MII_SWITCH) {
		struct dev_info *hw_priv =
			container_of(hw, struct dev_info, hw);
		phydev = hw_priv->phydev;
		link = phydev->link;
		speed = phydev->speed;
		duplex = phydev->duplex;
		bus = NULL;
	}
#endif
	if (link && speed) {
		data = determine_connect_cfg(hw, speed, duplex);
		if (hw->features & RGMII_PHY) {
			data |= MISC_RGMII_SELECT;
			if (PHY_INTERFACE_MODE_RGMII_RXID ==
			    phydev->interface ||
			    PHY_INTERFACE_MODE_RGMII == phydev->interface)
				data |= MISC_RGMII_RX_DELAY;
			if (PHY_INTERFACE_MODE_RGMII_TXID ==
			    phydev->interface ||
			    PHY_INTERFACE_MODE_RGMII == phydev->interface)
				data |= MISC_RGMII_TX_DELAY;
		} else if (hw->features & MII_PHY)
			data |= DMA_PHY_MII;
		if (hw->features & RX_JUMBO_FRAME)
			data |= DMA_JUMBO_FRAME_SUPPORT;
		writel(data, hw->io + REG_DMA_MISC_CFG);

		/* It is not a pseudo placeholder phy device. */
		if (bus) {
			local = phy_read(phydev, PHY_REG_AUTO_NEGOTIATION);
			remote = phy_read(phydev, PHY_REG_REMOTE_CAPABILITY);
			determine_flow_ctrl(hw, local, remote);
		}
	} else if (hw->port_mib.state)
		hw->port_mib.link_down = 1;
	hw->port_mib.state = link;
}  /* hw_cfg_link_speed */

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
	struct ksz_desc_info *info = &hw->tx_desc_info;
	struct ksz_dma_buf *dma_buf;
	int len;
	int last_frag = skb_shinfo(skb)->nr_frags;

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
		(desc)->sw.buf.tx.csum_gen_tcp = true;
		(desc)->sw.buf.tx.csum_gen_udp = true;
	}

	/*
	 * The last descriptor holds the packet so that it can be returned to
	 * network subsystem after all descriptors are transmitted.
	 */
	dma_buf->skb = skb;

	hw_send_pkt(hw, first);

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
	int in_intr = in_interrupt();

	if (!hw_priv->link_reset_timeout) {
		if (in_intr)
			spin_lock(&hw_priv->hwlock);
		else
			spin_lock_irq(&hw_priv->hwlock);
	}
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
			if (dev != dma_buf->skb->dev) {
				dev = dma_buf->skb->dev;
				dev->trans_start = jiffies;
			}

#ifdef CONFIG_NET_PEGASUS_PASSTHRU
			if (CHECKSUM_UNNECESSARY == dma_buf->skb->ip_summed)
				skb_queue_tail(&skb_pool, dma_buf->skb);
			else
#endif
#ifdef CONFIG_1588_PTP
			/* Still waiting for tx timestamp. */
			if (skb_shinfo(dma_buf->skb)->tx_flags &
					SKBTX_IN_PROGRESS)
				skb_shinfo(dma_buf->skb)->tx_flags &=
					~SKBTX_HW_TSTAMP;
			else
#endif

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
#ifdef CONFIG_NET_PEGASUS_PASSTHRU
	if (!normal) {
		struct sk_buff *skb, *tmp;

		skb_queue_walk_safe(&hw_priv->tx_queue, skb, tmp) {
			__skb_unlink(skb, &hw_priv->tx_queue);
			skb_queue_tail(&skb_pool, skb);
		}
	}
#endif
	if (!hw_priv->link_reset_timeout) {
		if (in_intr)
			spin_unlock(&hw_priv->hwlock);
		else
			spin_unlock_irq(&hw_priv->hwlock);
	}

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
	int port;
	int dev_count = 1;
	struct net_device *dev = hw_priv->dev;
#ifdef CONFIG_MICREL_SWITCH
	struct ksz_sw *sw = hw_priv->sw;
#endif

	transmit_cleanup(hw_priv, 1);

#ifdef CONFIG_MICREL_SWITCH
	if (sw_is_switch(sw))
		dev_count = sw->dev_count + sw->dev_offset;
#endif
	for (port = 0; port < dev_count; port++) {
#ifdef CONFIG_MICREL_SWITCH
		if (sw_is_switch(sw)) {
			dev = sw->netdev[port];
			if (!dev)
				continue;
		}
#endif
		if (netif_running(dev) && netif_queue_stopped(dev)) {
			struct ksz_hw *hw = &hw_priv->hw;

			/* Do not restart tx if descriptors are not enough. */
			if (hw->tx_desc_info.avail > 1 + MIN_TX_DESC)
				netif_wake_queue(dev);
#if defined(CONFIG_MICREL_SWITCH) && defined(CONFIG_HAVE_KSZ9897)
			if (sw_is_switch(sw))
				wake_up_interruptible(&sw->queue);
#endif
#ifdef CONFIG_NET_PEGASUS_PASSTHRU
			send_stored_frames(dev);
#endif
		}
	}
}  /* tx_done */

/* -------------------------------------------------------------------------- */

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
	int len = skb->len;
	int num = 1;
	int rc = 0;

	num = skb_shinfo(skb)->nr_frags + 1;

#if defined(HAVE_MICREL_SWITCH)
	if (hw->features & MII_SWITCH) {
		struct ksz_sw *sw = hw_priv->sw;

		len = sw->net_ops->get_tx_len(sw, skb);
		if (len != skb->len && num > 1)
			++num;
	}
#endif

	spin_lock_irq(&hw_priv->hwlock);

	left = hw_alloc_pkt(hw, len, num);
	if (left) {
		if (left < num) {
			struct sk_buff *org_skb = skb;
			int new_len = org_skb->len;

			if (new_len < 70)
				new_len = 70;
			skb = dev_alloc_skb(new_len);
			if (!skb) {
				hw_free_pkt(hw, len);
				rc = NETDEV_TX_BUSY;
				goto netdev_tx_exit;
			}
			skb_copy_and_csum_dev(org_skb, skb->data);
			org_skb->ip_summed = 0;
			skb->len = org_skb->len;
			copy_old_skb(org_skb, skb);
		}
#if defined(HAVE_MICREL_SWITCH)
		if (hw->features & MII_SWITCH) {
			struct ksz_sw *sw = hw_priv->sw;

			skb = sw->net_ops->final_skb(sw, skb, dev, &priv->port);
			if (!skb) {
				hw_free_pkt(hw, len);
				goto netdev_tx_exit;
			}
		}
#endif
		send_packet(skb, dev);
		if (left <= num)
			netif_stop_queue(dev);
#ifdef CONFIG_HAVE_KSZ9897
		if (hw->features & MII_SWITCH) {
			struct ksz_sw *sw = hw_priv->sw;

			if ((sw->features & IBA_SUPPORT) && !hw_priv->new_skb)
				hw_priv->new_skb = dev_alloc_skb(hw_priv->mtu);
		}
#endif
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

	dbg_msg("tx timeout:%lx\n", jiffies);
	printk(KERN_DEBUG "tx timeout:%lx\n", jiffies);

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

		hw_enable(hw);
		hw_ena_intr(hw);
	}

	dev->trans_start = jiffies;
	netif_wake_queue(dev);
	schedule_work(&hw_priv->tx_reset);
}  /* netdev_tx_timeout */

/* -------------------------------------------------------------------------- */

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

#ifdef CONFIG_MICREL_SWITCH
static int priv_promiscuous(void *ptr)
{
	struct dev_priv *priv = ptr;

	return priv->promiscuous;
}  /* priv_promiscuous */

static int priv_match_multi(void *ptr, u8 *data)
{
	int i;
	struct dev_priv *priv = ptr;
	int drop = false;

	if (priv->multi_list_size)
		drop = true;
	for (i = 0; i < priv->multi_list_size; i++)
		if (!memcmp(data, priv->multi_list[i], ETH_ALEN)) {
			drop = false;
			break;
		}
	return drop;
}  /* priv_match_multi */
#endif

#ifdef CONFIG_NET_DSA_TAG_TAIL
void net_add_tail_tag(struct sk_buff *skb, struct net_device *dev, int port)
{
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_sw *sw = hw_priv->sw;

	sw->net_ops->add_tail_tag(sw, skb, 1 << port);
}  /* net_add_tail_tag */

int net_get_tail_tag(struct sk_buff *skb, struct net_device *dev, int *port)
{
	u8 *trailer;
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_sw *sw = hw_priv->sw;

	trailer = skb_tail_pointer(skb) - 1;
	return sw->net_ops->get_tail_tag(trailer, port);
}  /* net_get_tail_tag */
#endif

static inline int rx_proc(struct dev_info *hw_priv, struct ksz_hw *hw,
	struct ksz_desc *desc, union desc_stat status)
{
	int packet_len;
	struct net_device *dev = hw_priv->dev;
	struct dev_priv *priv;
	struct ksz_dma_buf *dma_buf;
	struct sk_buff *skb = NULL;
	int rx_status;
	int aligned = status.rx.aligned;
	u32 frame_len = status.rx.frame_len;
#ifdef CONFIG_NET_PEGASUS_PASSTHRU
	int filter_flag;
#endif
#ifdef HAVE_MICREL_SWITCH
#if defined(CONFIG_MICREL_SWITCH) || defined(CONFIG_1588_PTP)
	struct ksz_sw *sw = hw_priv->sw;
	int forward = 0;
	int tag = 0;
	void *ptr = NULL;
	void (*rx_tstamp)(void *ptr, struct sk_buff *skb) = NULL;
#endif
#ifdef CONFIG_MICREL_SWITCH
	struct net_device *parent_dev = NULL;
	struct sk_buff *parent_skb = NULL;
	int extra_skb;
	int rx_port = 0;
#endif
#ifdef CONFIG_1588_PTP
	struct ptp_info *ptp = &sw->ptp_hw;
	int ptp_tag = 0;
#endif
#endif

	dma_buf = DMA_BUFFER(desc);
	dma_sync_single_for_cpu((struct device *) NULL, dma_buf->dma,
		status.rx.frame_len, DMA_FROM_DEVICE);

#ifdef CONFIG_MICREL_SWITCH
	if (sw_is_switch(sw)) {
		dev = sw->net_ops->rx_dev(sw, &dma_buf->skb->data[aligned],
			&frame_len, &tag, &rx_port);
		if (!dev)
			return -ENODEV;
	}
#endif
	priv = netdev_priv(dev);

	/* Received length includes 4-byte CRC. */
	packet_len = frame_len - 4;

#ifdef CONFIG_NET_PEGASUS_PASSTHRU
	filter_flag = filter_packet(hw->override_addr, dma_buf->skb);

	/* Promiscuous mode is set by user. */
	if (PACKET_OTHERHOST == filter_flag && hw->promiscuous > 1)
		filter_flag = PACKET_BROADCAST;
#endif

	if (aligned > 0 && packet_len > SKB_COPY_MAX) {
		skb = dma_buf->skb;
		dma_buf->skb = NULL;

		/* skb->data != skb->head */
#ifdef CONFIG_MICREL_SWITCH
#ifdef CONFIG_HAVE_KSZ9897
		if (sw->features & IBA_SUPPORT) {
			spin_lock(&hw_priv->hwlock);
			dma_buf->skb = hw_priv->new_skb;
			hw_priv->new_skb = NULL;
			spin_unlock(&hw_priv->hwlock);
		}
#endif
#endif
		if (!dma_buf->skb)
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
#ifdef CONFIG_NET_PEGASUS_PASSTHRU
	} else if (PACKET_OTHERHOST != filter_flag) {
#else
	} else {
#endif
#ifdef CONFIG_MICREL_SWITCH
#ifdef CONFIG_HAVE_KSZ9897
		if (sw->features & IBA_SUPPORT) {
			spin_lock(&hw_priv->hwlock);
			skb = hw_priv->new_skb;
			hw_priv->new_skb = NULL;
			spin_unlock(&hw_priv->hwlock);
		}
#endif
#endif
		/* skb->data != skb->head */
		if (!skb)
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

#ifdef CONFIG_NET_PEGASUS_PASSTHRU
	if (PACKET_HOST != filter_flag &&
			hw_priv->otherdev_running &&
			netif_carrier_ok(hw_priv->otherdev)) {
		struct dev_priv *other_priv = netdev_priv(hw_priv->otherdev);
		struct sk_buff *tx_skb = dma_buf->skb;

		dma_buf->skb = skb_dequeue(&skb_pool);
		if (!dma_buf->skb) {
			dma_buf->skb = tx_skb;
			other_priv->stats.tx_dropped++;
		} else {
			skb_reset_tail_pointer(tx_skb);
			tx_skb->len = 0;
			skb_put(tx_skb, packet_len);
			tx_skb->dev = hw_priv->otherdev;
			if (netif_queue_stopped(tx_skb->dev)) {
				struct dev_info *other = other_priv->adapter;
				struct sk_buff_head *tx_queue =
					&other->tx_queue;

				skb_queue_tail(tx_queue, tx_skb);
			} else
				send_frame(tx_skb, dma_buf->dma);

			dma_buf->dma = virt_to_dma(((struct device *) NULL),
				dma_buf->skb->data);

			/* Set descriptor. */
			set_rx_buf(desc, dma_buf->dma);
		}
	}

	/* PACKET_OTHERHOST == filter_flag */
	if (!skb)
		return 0;
#endif

#ifdef CONFIG_MICREL_SWITCH
	if (sw_is_switch(sw) && !sw->net_ops->match_pkt(sw, &dev,
			(void **) &priv, priv_promiscuous, priv_match_multi,
			skb, hw->promiscuous)) {
		dev_kfree_skb_irq(skb);
		return 0;
	}
	if (sw_is_switch(sw)) {

		/* Internal packets handled by the switch. */
		if (!sw->net_ops->drv_rx(sw, skb, rx_port))
			goto done;
	}
#endif

#ifndef CONFIG_KSZ8692VA
	if (0 == status.rx.csum_error && 0 == status.rx.csum_not_done)
		skb->ip_summed = CHECKSUM_UNNECESSARY;
#endif

	/* vlan_get_tag requires network device in socket buffer. */
	skb->dev = dev;

#ifdef CONFIG_1588_PTP
	ptr = ptp;
	if (sw->features & PTP_HW) {
		if (ptp->ops->drop_pkt(ptp, skb, sw->vlan_id, &tag, &ptp_tag)) {
			dev_kfree_skb_irq(skb);
			return 0;
		}
		if (ptp_tag) {
			rx_tstamp = ptp->ops->get_rx_tstamp;
			if (!forward)
				forward = FWD_VLAN_DEV | FWD_MAIN_DEV;
		}
	}
#endif
#ifdef CONFIG_KSZ_STP
	if (sw_is_switch(sw) && sw->net_ops->stp_rx(sw, dev, skb, rx_port,
			&forward)) {
		if (!forward) {
			if (!sw->net_ops->blocked_rx(sw, skb->data))
				dbg_msg(
					"rxd%d=%02x:%02x:%02x:%02x:%02x:%02x\n",
					rx_port,
					skb->data[0], skb->data[1],
					skb->data[2], skb->data[3],
					skb->data[4], skb->data[5]);
			dev_kfree_skb_irq(skb);
			return 0;
		}
	}
#endif
#if defined(CONFIG_MICREL_SWITCH)
	if (sw_is_switch(sw)) {

		/* Need to forward to VLAN devices for MRP messages. */
		if (!forward) {
			struct ethhdr *eth = (struct ethhdr *) skb->data;

			if (eth->h_proto == htons(0x88F5) ||
			    eth->h_proto == htons(0x88F6) ||
			    eth->h_proto == htons(0x22EA))
				forward = FWD_VLAN_DEV;
		}

		/* No VLAN port forwarding; need to send to parent. */
		if ((forward & FWD_VLAN_DEV) && !tag)
			forward &= ~FWD_VLAN_DEV;
		dev = sw->net_ops->parent_rx(sw, dev, skb, forward,
			&parent_dev, &parent_skb);

		/* dev may change. */
		skb->dev = dev;
	}
	extra_skb = (parent_skb != NULL);
#endif

#if defined(CONFIG_MICREL_SWITCH)
	if (sw_is_switch(sw))
		extra_skb |= sw->net_ops->port_vlan_rx(sw, dev, parent_dev,
			skb, forward, tag, ptr, rx_tstamp);
#endif
	skb->protocol = eth_type_trans(skb, dev);

#ifdef CONFIG_KSZ8692VA
	if (!status.rx.csum_err_tcp)
		csum_verified(skb);
#endif
	if (skb)
		rx_status = netif_rx(skb);

#if defined(CONFIG_MICREL_SWITCH)
	if (parent_skb) {
		struct dev_priv *parent_priv = netdev_priv(parent_dev);

		/* Update receive statistics. */
		parent_priv->stats.rx_packets++;
		parent_priv->stats.rx_bytes += packet_len;

		/* Notify upper layer for received packet. */
		parent_dev->last_rx = jiffies;

#ifdef CONFIG_1588_PTP
		if (ptp_tag && (ptp->rx_en & 1))
			ptp->ops->get_rx_tstamp(ptp, parent_skb);
#endif
		parent_skb->protocol = eth_type_trans(parent_skb, parent_dev);
		rx_status = netif_rx(parent_skb);
	}

done:
#endif
	/* Update receive statistics. */
	priv = netdev_priv(dev);
	priv->stats.rx_packets++;
	priv->stats.rx_bytes += packet_len;

	/* Notify upper layer for received packet. */
	dev->last_rx = jiffies;

	return 0;
}  /* rx_proc */

static int dev_rcv_packets(struct dev_info *hw_priv)
{
	int next;
	union desc_stat status;
	struct ksz_hw *hw = &hw_priv->hw;
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

		/* Status valid only when last descriptor bit is set. */
		if (status.rx.last_desc && status.rx.first_desc) {
			if (rx_proc(hw_priv, hw, desc, status))
				goto release_packet;
			received++;
		}

release_packet:
		release_desc(desc);
		next++;
		next &= info->mask;
	}
	info->next = next;

	return received;
}  /* dev_rcv_packets */

static int dev_rcv_special(struct dev_info *hw_priv)
{
	int next;
	union desc_stat status;
	struct ksz_hw *hw = &hw_priv->hw;
	struct ksz_desc_info *info = &hw->rx_desc_info;
	int left = info->alloc;
	struct ksz_desc *desc;
	int received = 0;

	next = info->next;
	while (left--) {
		/* Get next descriptor which is not hardware owned. */
		desc = &info->ring[next];
		status.data = le32_to_cpu(desc->phw->ctrl.data);
		if (status.rx.hw_owned)
			break;

		/* Status valid only when last descriptor bit is set. */
		if (status.rx.last_desc && status.rx.first_desc) {
			/*
			 * Receive without error.  With receive errors
			 * disabled, packets with receive errors will be
			 * dropped, so no need to check the error bit.
			 */
			if (!status.rx.error || (status.data &
					DESC_RX_ERROR_COND) ==
					DESC_RX_ERROR_TOO_LONG) {
				if (rx_proc(hw_priv, hw, desc, status))
					goto release_packet;
				received++;
			} else if ((hw->overrides & MAX_RX_CRC_ERR) &&
						status.rx.err_crc &&
						((JUMBO_MAX_TX_BUF_SIZE ==
						status.rx.frame_len) ||
						(LAN_MAX_TX_BUF_SIZE ==
						status.rx.frame_len))) {
				if (rx_proc(hw_priv, hw, desc, status))
					goto release_packet;
				received++;
			} else {

				/* Update receive error statistics. */
				hw->counter[OID_COUNTER_RCV_ERROR]++;
			}
		}

release_packet:
		release_desc(desc);
		next++;
		next &= info->mask;
	}
	info->next = next;

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
		hw_turn_on_intr(hw, INT_RX_MASK);
		spin_unlock_irq(&hw_priv->hwlock);
	} else {
		hw_ack_intr(hw, INT_RX);
		tasklet_schedule(&hw_priv->rx_tasklet);
	}
}  /* rx_proc_task */

static void tx_proc_task(unsigned long data)
{
	struct dev_info *hw_priv = (struct dev_info *) data;
	struct ksz_hw *hw = &hw_priv->hw;

	hw_ack_intr(hw, INT_TX_MASK);

	tx_done(hw_priv);

	/* tasklets are interruptible. */
	spin_lock_irq(&hw_priv->hwlock);
	hw_turn_on_intr(hw, INT_TX);
	spin_unlock_irq(&hw_priv->hwlock);
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

	hw_ack_intr(hw, INT_RX);

	received = dev_rcv_packets(dev);

	dev->quota -= received;
	*budget -= received;

	if (received < left) {
		netif_rx_complete(dev);

		/* tasklets are interruptible. */
		spin_lock_irq(&hw_priv->hwlock);
		hw_turn_on_intr(hw, INT_RX_MASK);
		spin_unlock_irq(&hw_priv->hwlock);
	}

	return received >= left;
}  /* netdev_poll */
#endif

static inline void handle_rx_stop(struct ksz_hw *hw)
{
	/* Receive just has been stopped. */
	if (0 == hw->rx_stop)
		hw->intr_mask &= ~INT_RX_STOPPED;
	else if (hw->rx_stop > 1) {
		if (hw->enabled && (hw->rx_cfg & DMA_RX_CTRL_ENABLE)) {
			hw_start_rx(hw);
		} else {
			hw->intr_mask &= ~INT_RX_STOPPED;
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
	do {
		int_enable &= hw->intr_mask;
		hw_ack_intr(hw, int_enable);

		if (unlikely(int_enable & INT_TX_MASK)) {
			hw_dis_intr_bit(hw, INT_TX_MASK);
			tasklet_schedule(&hw_priv->tx_tasklet);
		}

		if (likely(int_enable & INT_RX)) {

#ifdef CONFIG_KSZ_NAPI
			hw_dis_intr_bit(hw, INT_RX_MASK);
			if (likely(netif_rx_schedule_prep(dev))) {

				/* tell system we have work to be done. */
				__netif_rx_schedule(dev);
			}

#else
			hw_dis_intr_bit(hw, INT_RX);
			tasklet_schedule(&hw_priv->rx_tasklet);
#endif
		}

		if (unlikely(int_enable & INT_RX_OVERRUN)) {
			hw->counter[OID_COUNTER_RCV_NO_BUFFER]++;
			priv->stats.rx_fifo_errors++;
			hw_resume_rx(hw);
		}

		if (unlikely(int_enable & INT_RX_STOPPED)) {
			handle_rx_stop(hw);
			break;
		}

		if (unlikely(int_enable & INT_TX_STOPPED)) {
			hw->intr_mask &= ~INT_TX_STOPPED;
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
	struct ksz_hw *hw = &hw_priv->hw;
#ifdef HAVE_MICREL_SWITCH
	struct ksz_sw *sw = hw_priv->sw;
#endif
	int irq;

#ifdef CONFIG_NET_PEGASUS_PASSTHRU
	if (hw_priv->otherdev) {
		struct dev_priv *other_priv = netdev_priv(hw_priv->otherdev);
		struct dev_info *other_hw_priv = other_priv->adapter;

		other_hw_priv->otherdev_running = false;
	}
#endif
	netif_stop_queue(dev);

#ifdef HAVE_MICREL_SWITCH
	if (sw_is_switch(sw))
		sw->net_ops->close_port(sw, dev, &priv->port);
#endif

	if (priv->multicast)
		--hw->all_multi;
	if (priv->promiscuous)
		--hw->promiscuous;

	hw_priv->opened--;
	if (hw_priv->opened)
		return 0;

	ksz_stop_timer(&hw_priv->mib_timer_info);
	flush_work(&hw_priv->mib_read);
#ifdef HAVE_MICREL_SWITCH
	if (hw->features & MII_SWITCH) {
		sw->net_ops->close(sw);
		sw->net_ops->stop(sw, true);
	}
#endif

	hw_dis_intr(hw);
	hw_disable(hw);
	hw_clr_multicast(hw);

	/* Delay for receive task to stop scheduling itself. */
	msleep(2000 / HZ);

	if (hw->features & GIGABIT_RATE_CHANGE_BUG)
		flush_work(&hw_priv->link_reset);

	tasklet_disable(&hw_priv->rx_tasklet);
	tasklet_disable(&hw_priv->tx_tasklet);
	for (irq = 0; irq < 6; irq++)
		free_irq(dev->irq + irq, hw_priv->dev);

	transmit_cleanup(hw_priv, false);
	hw_reset_pkts(&hw->rx_desc_info);
	hw_reset_pkts(&hw->tx_desc_info);

#ifdef DEBUG_MSG
	dbg_print_work(&db.dbg_print);
#endif

	return 0;
}  /* netdev_close */

#define SUPPORTED_Pauses		\
	(SUPPORTED_Pause | SUPPORTED_Asym_Pause)

static u32 advertised_flow_ctrl(struct ksz_hw *hw, u32 advertising)
{
	advertising &= ~SUPPORTED_Pauses;
	switch (hw->flow_ctrl) {
	case PHY_FLOW_CTRL:
		advertising |= SUPPORTED_Pause;
		break;
	case PHY_TX_ONLY:
		advertising |= SUPPORTED_Asym_Pause;
		break;
	case PHY_RX_ONLY:
		advertising |= SUPPORTED_Pauses;
		break;
	default:
		break;
	}
	return advertising;
}  /* advertise_flow_ctrl */

static void phy_resume_machine(struct phy_device *phydev)
{
	schedule_delayed_work(&phydev->state_queue, 0);
}  /* phy_resume_machine */

static void hw_set_link_speed(struct ksz_hw *hw, struct phy_device *phydev)
{
	u32 advertising = phydev->advertising;

	/* It is a pseudo placeholder phy device. */
	if (!phydev->bus)
		return;
	if (hw->force_link) {
		if (!hw->speed)
			hw->speed = 10;
		phydev->speed = hw->speed;
		if (2 == hw->duplex)
			phydev->duplex = DUPLEX_FULL;
		else
			phydev->duplex = DUPLEX_HALF;
		phydev->autoneg = AUTONEG_DISABLE;
		advertising &= ~ADVERTISED_Autoneg;
	} else {
		phydev->autoneg = AUTONEG_ENABLE;
		advertising |= ADVERTISED_Autoneg;
		advertising |= (ADVERTISED_10baseT_Half |
			ADVERTISED_10baseT_Full |
			ADVERTISED_100baseT_Half |
			ADVERTISED_100baseT_Full);
		if ((phydev->drv->features & PHY_GBIT_FEATURES) ==
				PHY_GBIT_FEATURES)
			advertising |= (ADVERTISED_1000baseT_Half |
				ADVERTISED_1000baseT_Full);
		if (hw->speed || hw->duplex) {
			if (10 == hw->speed) {
				advertising &= ~(ADVERTISED_100baseT_Half |
					ADVERTISED_100baseT_Full |
					ADVERTISED_1000baseT_Half |
					ADVERTISED_1000baseT_Full);
			} else if (100 == hw->speed) {
				advertising &= ~(ADVERTISED_10baseT_Half |
					ADVERTISED_10baseT_Full |
					ADVERTISED_1000baseT_Half |
					ADVERTISED_1000baseT_Full);
			} else if (1000 == hw->speed) {
				advertising &= ~(ADVERTISED_10baseT_Half |
					ADVERTISED_10baseT_Full |
					ADVERTISED_100baseT_Half |
					ADVERTISED_100baseT_Full);
			}
			if (1 == hw->duplex) {
				advertising &= ~(ADVERTISED_10baseT_Full |
					ADVERTISED_100baseT_Full |
					ADVERTISED_1000baseT_Full);
			} else if (2 == hw->duplex) {
				advertising &= ~(ADVERTISED_10baseT_Half |
					ADVERTISED_100baseT_Half |
					ADVERTISED_1000baseT_Half);
			}
		}
		advertising = advertised_flow_ctrl(hw, advertising);
	}
	if (hw->force_link || advertising != phydev->advertising) {
		phydev->advertising = advertising;
#ifdef HAVE_MICREL_SWITCH
		if (hw->features & MII_SWITCH)
			return;
#endif
		phy_start_aneg(phydev);
		phy_resume_machine(phydev);
	}
}  /* hw_set_link_speed */

static void hw_cfg_huge_frame(struct dev_info *hw_priv, struct ksz_hw *hw)
{
#ifdef CONFIG_MICREL_SWITCH
	struct ksz_sw *sw = hw_priv->sw;

	if (sw && sw->info) {
		int set;

		if (hw->features & RX_HUGE_FRAME)
			set = true;
		else
			set = false;
		sw->ops->acquire(sw);
#if defined(REG_SWITCH_CTRL_2) && defined(SWITCH_HUGE_PACKET)
		sw->ops->cfg(sw, REG_SWITCH_CTRL_2, SWITCH_HUGE_PACKET, set);
#endif
		sw->ops->release(sw);
	}
#endif
	if (hw->features & RX_HUGE_FRAME) {
		hw->rx_cfg |= DMA_RX_CTRL_ERROR;
		hw_priv->dev_rcv = dev_rcv_special;
	} else {
		hw->rx_cfg &= ~DMA_RX_CTRL_ERROR;
		hw_priv->dev_rcv = dev_rcv_packets;
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
	for (irq = 0; irq < 6; irq++) {
		switch (irq) {
		case 0:
			snprintf(hw_priv->irq_name[irq], 40,
				"%s rx stopped", dev->name);
			break;
		case 1:
			snprintf(hw_priv->irq_name[irq], 40,
				"%s tx stopped", dev->name);
			break;
		case 2:
			snprintf(hw_priv->irq_name[irq], 40,
				"%s rx buffer empty", dev->name);
			break;
		case 3:
			snprintf(hw_priv->irq_name[irq], 40,
				"%s tx buffer empty", dev->name);
			break;
		case 4:
			snprintf(hw_priv->irq_name[irq], 40,
				"%s rx", dev->name);
			break;
		case 5:
			snprintf(hw_priv->irq_name[irq], 40,
				"%s tx", dev->name);
			break;
		default:
			break;
		}
		rc = request_irq(dev->irq + irq, netdev_intr,
			IRQF_DISABLED,
			hw_priv->irq_name[irq], dev);
		if (rc) {
			while (irq--)
				free_irq(dev->irq + irq, dev);
			return rc;
		}
	}
	tasklet_enable(&hw_priv->rx_tasklet);
	tasklet_enable(&hw_priv->tx_tasklet);

	hw->all_multi = 0;
#ifdef KSZ_DLR
	hw->all_multi = 1;
#endif
	hw->multi_list_size = 0;

	hw_setup(hw);
	hw_reset(hw);

	hw_set_desc_base(hw,
		hw->tx_desc_info.ring_phys, hw->rx_desc_info.ring_phys);

	/* Need to program misc. configuration register. */
	hw_cfg_link_speed(hw, priv->phydev);
	hw_cfg_huge_frame(hw_priv, hw);
	ksz_init_rx_buffers(hw_priv);
	return 0;
}  /* prepare_hardware */

static int netdev_open_before(struct net_device *dev, struct dev_priv *priv,
	struct dev_info *hw_priv, struct ksz_hw *hw)
{
	int rc;

#ifdef HAVE_MICREL_SWITCH
	do {
		struct ksz_sw *sw = hw_priv->sw;

		if (sw_is_switch(sw))
			sw->net_ops->open_dev(sw, dev, hw->override_addr);
	} while (0);
#endif

	rc = prepare_hardware(dev);
	if (rc)
		return rc;

	if (next_jiffies < jiffies)
		next_jiffies = jiffies + HZ * 2;
	else
		next_jiffies += HZ * 1;
	hw_priv->counter.time = next_jiffies;
	hw_init_cnt(hw);
	hw_add_wol_bcast(hw);

	if (hw->features & GIGABIT_RATE_CHANGE_BUG) {
		hw_priv->gigabit_rate = false;
		if (1000 == priv->phydev->speed)
			hw_priv->gigabit_rate = true;
	}
	return 0;
}  /* netdev_open_before */

static void netdev_open_after(struct dev_info *hw_priv, struct ksz_hw *hw)
{
	hw_setup_intr(hw);
	hw_enable(hw);
	hw_ena_intr(hw);

	ksz_start_timer(&hw_priv->mib_timer_info,
		hw_priv->mib_timer_info.period);

#ifdef HAVE_MICREL_SWITCH
	do {
		struct ksz_sw *sw = hw_priv->sw;

		if (sw_is_switch(sw))
			sw->net_ops->open(sw);
	} while (0);
#endif
}  /* netdev_open_after */

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
	int rc;
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_hw *hw = &hw_priv->hw;

	priv->multicast = 0;
	priv->promiscuous = 0;

	/* Reset device statistics. */
	memset(&priv->stats, 0, sizeof(struct net_device_stats));
	memset((void *) hw->counter, 0,
		(sizeof(u64) * OID_COUNTER_LAST));

	if (!(hw_priv->opened)) {
		rc = netdev_open_before(dev, priv, hw_priv, hw);
		if (rc)
			return rc;
	}

#ifdef HAVE_MICREL_SWITCH
	do {
		struct ksz_sw *sw = hw_priv->sw;

		if (sw_is_switch(sw))
			sw->net_ops->open_port(sw, dev, &priv->port,
				&priv->state);
	} while (0);
#endif

	/*
	 * Delay reporting link up until device is started.
	 * Faked PHY device cannot start.
	 */
	if (priv->phydev->bus)
		phy_start(priv->phydev);
	hw_set_link_speed(hw, priv->phydev);

	if (!(hw_priv->opened))
		netdev_open_after(hw_priv, hw);

	hw_priv->opened++;

	netif_start_queue(dev);
#ifdef CONFIG_NET_PEGASUS_PASSTHRU
	if ((hw->features & PASSTHRU) && hw_priv->otherdev) {
		struct dev_priv *other_priv = netdev_priv(hw_priv->otherdev);
		struct dev_info *other_hw_priv = other_priv->adapter;

		other_hw_priv->otherdev_running = true;
	}
#endif

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
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_hw *hw = &hw_priv->hw;
	struct ksz_hw_mib *mib = &hw->port_mib;

	priv->stats.rx_errors = hw->counter[OID_COUNTER_RCV_ERROR];
	priv->stats.tx_errors = hw->counter[OID_COUNTER_XMIT_ERROR];

	priv->stats.multicast = (unsigned long)
		mib->counter[MIB_COUNTER_RX_MULTICAST];

	priv->stats.collisions = (unsigned long)
		mib->counter[MIB_COUNTER_TX_TOTAL_COLLISION];

	priv->stats.rx_length_errors = (unsigned long)(
		mib->counter[MIB_COUNTER_RX_UNDERSIZE] +
		mib->counter[MIB_COUNTER_RX_FRAGMENT] +
		mib->counter[MIB_COUNTER_RX_OVERSIZE] +
		mib->counter[MIB_COUNTER_RX_JABBER]);
	priv->stats.rx_crc_errors = (unsigned long)
		mib->counter[MIB_COUNTER_RX_CRC_ERR];
	priv->stats.rx_frame_errors = (unsigned long)(
		mib->counter[MIB_COUNTER_RX_ALIGNMENT_ERR] +
		mib->counter[MIB_COUNTER_RX_SYMBOL_ERR]);

	priv->stats.tx_window_errors = (unsigned long)
		mib->counter[MIB_COUNTER_TX_LATE_COLLISION];

#ifndef CONFIG_KSZ8692VA
	priv->stats.rx_dropped = (unsigned long)
		mib->counter[MIB_COUNTER_PACKET_DROPPED];
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

	memcpy(dev->dev_addr, mac->sa_data, ETH_ALEN);

	hw->mac_override = true;
	memcpy(hw->override_addr, mac->sa_data, ETH_ALEN);

#ifdef CONFIG_MICREL_SWITCH
	if (hw->features & MII_SWITCH) {
		struct ksz_sw *sw = hw_priv->sw;
		u8 promiscuous = hw->promiscuous;

		promiscuous = sw->net_ops->set_mac_addr(sw, dev, promiscuous,
			priv->port.first_port);
		if (promiscuous != hw->promiscuous) {

			/* A hack to accept changed KSZ9897 IBA response. */
			if (!hw->promiscuous && 2 == promiscuous) {
				promiscuous = 1;
				schedule_delayed_work(&hw_priv->promisc_reset,
					 10);
			}
			hw->promiscuous = promiscuous;
			if (hw->promiscuous <= 1 && promiscuous <= 1)
				hw_set_promiscuous(hw, hw->promiscuous);
		}
	}
#endif
	mutex_lock(&hw_priv->lock);
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
	struct netdev_hw_addr *ha;
	int flags = dev->flags;
	int multicast = ((dev->flags & IFF_ALLMULTI) == IFF_ALLMULTI);

	dev_set_promiscuous(dev, priv, hw,
		((dev->flags & IFF_PROMISC) == IFF_PROMISC));

#ifdef CONFIG_MICREL_SWITCH
	if (hw_priv->sw && hw_priv->sw->dev_count > 1) {
#ifdef CONFIG_KSZ_STP
		if ((flags & IFF_MULTICAST) && !netdev_mc_empty(dev))
			hw_priv->sw->net_ops->set_multi(hw_priv->sw, dev,
				&priv->port);
#endif
		priv->multi_list_size = 0;

		/* Do not update multi_list_size. */
		if (flags & IFF_ALLMULTI)
			flags &= ~IFF_MULTICAST;

		/* Turn on all multicast. */
		multicast |= ((dev->flags & IFF_MULTICAST) == IFF_MULTICAST);
	}
#endif
	dev_set_multicast(priv, hw, multicast);

	if ((flags & IFF_MULTICAST) && !netdev_mc_empty(dev)) {
		int i = 0;

		/* List too big to support so turn on all multicast mode. */
		if (netdev_mc_count(dev) > MAX_MULTICAST_LIST) {
			if (MAX_MULTICAST_LIST != hw->multi_list_size) {
				hw->multi_list_size = MAX_MULTICAST_LIST;
				++hw->all_multi;
				hw_set_multicast(hw, hw->all_multi);
			}
#ifdef CONFIG_MICREL_SWITCH
			priv->multi_list_size = 0;
#endif
			return;
		}

		netdev_for_each_mc_addr(ha, dev) {
			if (!(*ha->addr & 1))
				continue;
			if (i >= MAX_MULTICAST_LIST)
				break;
#ifdef CONFIG_MICREL_SWITCH
			memcpy(priv->multi_list[i], ha->addr, ETH_ALEN);
#endif
			memcpy(hw->multi_list[i++], ha->addr, ETH_ALEN);
		}
#ifdef CONFIG_MICREL_SWITCH
		priv->multi_list_size = (u8) i;
#endif
		hw->multi_list_size = (u8) i;
		hw_set_grp_addr(hw);
	} else {
		if (MAX_MULTICAST_LIST == hw->multi_list_size) {
			--hw->all_multi;
			hw_set_multicast(hw, hw->all_multi);
		}
#ifdef CONFIG_MICREL_SWITCH
		priv->multi_list_size = 0;
#endif
		hw->multi_list_size = 0;
		hw_clr_multicast(hw);
	}
}  /* netdev_set_rx_mode */

static int netdev_change_mtu(struct net_device *dev, int new_mtu)
{
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_hw *hw = &hw_priv->hw;
	int hw_mtu;

	if (netif_running(dev))
		return -EBUSY;

#ifdef CONFIG_NET_PEGASUS_PASSTHRU
	if (hw->features & PASSTHRU)
		return -EBUSY;
#endif
#ifdef HAVE_MICREL_SWITCH_
	if (hw->features & MII_SWITCH)
		return -EBUSY;
#endif

	if (new_mtu < 60)
		return -ERANGE;

	if (dev->mtu != new_mtu) {
		hw_mtu = new_mtu + ETHERNET_HEADER_SIZE + 4;
#if defined(CONFIG_MICREL_KSZ9897_PTP)
		do {
			struct ksz_sw *sw = hw_priv->sw;

			if (sw_is_switch(sw))
				hw_mtu += 5;
		} while (0);
#endif
		if (hw_mtu > hw_priv->max_buf_size)
			return -ERANGE;
		if (hw_mtu > JUMBO_RX_BUF_SIZE) {
			if (JUMBO_MAX_TX_BUF_SIZE == hw_mtu &&
					(hw->features & MAX_RX_BUG) &&
					!(hw->overrides & MAX_RX_CRC_ERR))
				return -ERANGE;
			hw->features |= RX_JUMBO_FRAME;
			hw->features |= RX_HUGE_FRAME;
			if (!(hw->features & IP_HEADER_ALIGN))
				hw_mtu = JUMBO_MAX_RX_BUF_SIZE;
		} else if (hw_mtu > hw_priv->rx_buf_size) {
			hw->features |= RX_JUMBO_FRAME;
			hw->features &= ~RX_HUGE_FRAME;
			if (!(hw->features & IP_HEADER_ALIGN))
				hw_mtu = JUMBO_RX_BUF_SIZE;
		} else if (hw_mtu > REGULAR_RX_BUF_SIZE) {
			if (LAN_MAX_TX_BUF_SIZE == hw_mtu &&
					(hw->features & MAX_RX_BUG) &&
					!(hw->overrides & MAX_RX_CRC_ERR))
				return -ERANGE;
			hw->features &= ~RX_JUMBO_FRAME;
			hw->features |= RX_HUGE_FRAME;
			if (!(hw->features & IP_HEADER_ALIGN))
				hw_mtu = hw_priv->rx_buf_size;
		} else {
			hw->features &= ~RX_JUMBO_FRAME;
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

#ifdef CONFIG_MICREL_SWITCH
static int netdev_add_vid(struct net_device *dev, unsigned short vid)
{
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_sw *sw = hw_priv->sw;

	if (!sw)
		return 0;
	if ((sw->features & VLAN_PORT) && vid >= VLAN_PORT_START) {
		vid -= VLAN_PORT_START;
		if (vid <= SWITCH_PORT_NUM)
			sw->vlan_id |= (1 << vid);
	}
	return 0;
}

static int netdev_kill_vid(struct net_device *dev, unsigned short vid)
{
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_sw *sw = hw_priv->sw;

	if (!sw)
		return 0;
	if ((sw->features & VLAN_PORT) && vid >= VLAN_PORT_START) {
		vid -= VLAN_PORT_START;
		if (vid <= SWITCH_PORT_NUM)
			sw->vlan_id &= ~(1 << vid);
	}
	return 0;
}
#endif

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
	struct mii_bus *bus = priv->phydev->bus;
	int err;
	int val_out = 0xffff;

	/* It is a pseudo placeholder phy device. */
	if (!bus)
		return val_out;
	mutex_lock(&bus->mdio_lock);
	err = bus->read(bus, phy_id, reg_num);
	mutex_unlock(&bus->mdio_lock);
	if (err >= 0)
		val_out = err;

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
	struct mii_bus *bus = priv->phydev->bus;

	/* It is a pseudo placeholder phy device. */
	if (!bus)
		return;
	mutex_lock(&bus->mdio_lock);
	bus->write(bus, phy_id, reg_num, (u16) val);
	mutex_unlock(&bus->mdio_lock);
}  /* mdio_write */

/* -------------------------------------------------------------------------- */

/*
 * ethtool support
 */

#define ADVERTISED_ALL			\
	(ADVERTISED_10baseT_Half |	\
	ADVERTISED_10baseT_Full |	\
	ADVERTISED_1000baseT_Half |	\
	ADVERTISED_1000baseT_Full |	\
	ADVERTISED_100baseT_Half |	\
	ADVERTISED_100baseT_Full)

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

	/* It is a pseudo placeholder phy device. */
	if (!priv->phydev->bus)
		return -1;
	mutex_lock(&hw_priv->lock);
#ifdef HAVE_MICREL_SWITCH
	rc = mii_ethtool_gset(&priv->mii_if, cmd);
	cmd->advertising |= SUPPORTED_TP;
	cmd->port = PORT_TP;
#else
	rc = phy_ethtool_gset(priv->phydev, cmd);
#endif
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
	struct ksz_hw *hw = &hw_priv->hw;
	int rc;

	/* It is a pseudo placeholder phy device. */
	if (!priv->phydev->bus)
		return -1;
	/*
	 * ethtool utility does not change advertised setting if auto
	 * negotiation is not specified explicitly.
	 */
	if (cmd->autoneg && priv->advertising == cmd->advertising) {
		cmd->advertising |= ADVERTISED_ALL;
		if (10 == cmd->speed)
			cmd->advertising &=
				~(ADVERTISED_100baseT_Full |
				ADVERTISED_100baseT_Half |
				ADVERTISED_1000baseT_Full |
				ADVERTISED_1000baseT_Half);
		else if (100 == cmd->speed)
			cmd->advertising &=
				~(ADVERTISED_10baseT_Full |
				ADVERTISED_10baseT_Half |
				ADVERTISED_1000baseT_Full |
				ADVERTISED_1000baseT_Half);
		else if (1000 == cmd->speed)
			cmd->advertising &=
				~(ADVERTISED_10baseT_Full |
				ADVERTISED_10baseT_Half |
				ADVERTISED_100baseT_Full |
				ADVERTISED_100baseT_Half);
		if (0 == cmd->duplex)
			cmd->advertising &=
				~(ADVERTISED_100baseT_Full |
				ADVERTISED_10baseT_Full |
				ADVERTISED_1000baseT_Full);
		else if (1 == cmd->duplex)
			cmd->advertising &=
				~(ADVERTISED_100baseT_Half |
				ADVERTISED_10baseT_Half |
				ADVERTISED_1000baseT_Half);
	}
	mutex_lock(&hw_priv->lock);
	if (cmd->autoneg && (cmd->advertising & ADVERTISED_ALL) ==
			ADVERTISED_ALL) {
		hw->duplex = 0;
		hw->speed = 0;
		hw->force_link = 0;
	} else {
		hw->duplex = cmd->duplex + 1;
		hw->speed = cmd->speed;
		if (cmd->autoneg)
			hw->force_link = 0;
		else
			hw->force_link = 1;
	}
#ifdef HAVE_MICREL_SWITCH
	if (hw->features & MII_SWITCH) {
		struct ksz_port *port = &priv->port;

		port->duplex = hw->duplex;
		if (hw->speed != 1000)
			port->speed = hw->speed;
		port->force_link = hw->force_link;
	}
	rc = mii_ethtool_sset(&priv->mii_if, cmd);
#else
	rc = phy_ethtool_sset(priv->phydev, cmd);
#endif
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
	{ 0x0, 0x68 },
	{ 0xE0, 0xEC },
	{ 0x100, 0x10C },
	{ 0x200, 0x204 },
	{ 0x300, 0x310 },
	{ 0xF00, 0xF10 },
	{ 0x10000, 0x10058 },
	{ 0x12000, 0x12058 },
#if !defined(CONFIG_PEGASUS_NO_PCI)
	{ 0x12100, 0x12228 },
#endif
	{ 0x14000, 0x14044 },
	{ 0x15000, 0x15044 },
	{ 0x16000, 0x16040 },
	{ 0x18000, 0x18040 },
	{ 0x1E000, 0x1E024 },
	{ 0x1E080, 0x1E0A4 },
	{ 0x1E100, 0x1E124 },
	{ 0x1E180, 0x1E1A4 },
	{ 0x1E200, 0x1E270 },
	{ 0x1E400, 0x1E410 },
	{ 0x1E600, 0x1E610 },
	{ 0x1E800, 0x1E824 },
	{ 0x1E900, 0x1E920 },
	{ 0x1EA00, 0x1EA60 },
	{ 0x1EB00, 0x1EB10 },
	{ 0x1EC00, 0x1EC24 },
	{ 0x1ED00, 0x1ED04 },
	{ 0x1ED80, 0x1ED84 },
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
		base = (uint) hw_priv->hw.io - (uint) BASE_IO_ADDR;
		len = range->start;
		if (len >= 0x10000)
			base = -0x10000;
		while (len < range->end) {
			buf += sprintf(buf, "%04x:", base + len);
			for (i = 0; i < 4; i++, len += 4) {
				if (base < 0)
					val = KS_R(base + len);
				else if (len < 0xF00)
					val = readl(hw_priv->hw.io + len);
				else {
					int phy_reg = (len - 0xF00) / 2;
					int phy_val;

					if (priv->phydev->bus)
						phy_val = phy_read(priv->phydev,
							phy_reg + 1);
					else
						phy_val = 0xffff;
					val = phy_val << 16;
					if (priv->phydev->bus)
						phy_val = phy_read(priv->phydev,
							phy_reg);
					else
						phy_val = 0xffff;
					val |= phy_val;
				}
				buf += sprintf(buf, " %08x", val);
			}
			buf += sprintf(buf, "\n");
		}
		range++;
	}
	mutex_unlock(&hw_priv->lock);
}  /* netdev_get_regs */

#define WOL_SUPPORT			\
	(WAKE_PHY | WAKE_MAGIC |	\
	WAKE_UCAST | WAKE_MCAST |	\
	WAKE_BCAST | WAKE_ARP)

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

	/* Need to find a way to retrieve the device IP address. */
	u8 net_addr[] = { 192, 168, 1, 1 };

	if (wol->wolopts & ~hw_priv->wol_support)
		return -EINVAL;

	hw_priv->wol_enable = wol->wolopts;

	/* Link wakeup cannot really be disabled. */
	if (wol->wolopts)
		hw_priv->wol_enable |= WAKE_PHY;
	hw_enable_wol(&hw_priv->hw, hw_priv->wol_enable, net_addr);
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
#ifdef HAVE_MICREL_SWITCH
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_sw *sw = hw_priv->sw;

	sw->msg_enable = value;
#endif
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
#ifdef HAVE_MICREL_SWITCH
	struct ksz_sw *sw = hw_priv->sw;

	pause->autoneg = (sw->overrides & PAUSE_FLOW_CTRL) ? 0 : 1;
#else
	pause->autoneg = (hw->overrides & PAUSE_FLOW_CTRL) ? 0 : 1;
#endif
	pause->rx_pause = (hw->rx_cfg & DMA_RX_CTRL_FLOW_ENABLE) ? 1 : 0;
	pause->tx_pause = (hw->tx_cfg & DMA_TX_CTRL_FLOW_ENABLE) ? 1 : 0;
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
#ifdef HAVE_MICREL_SWITCH
	struct ksz_sw *sw = hw_priv->sw;
	struct ksz_port *port = &priv->port;
#endif

	mutex_lock(&hw_priv->lock);
	if (pause->autoneg) {
		if (!pause->rx_pause && !pause->tx_pause)
			hw->flow_ctrl = PHY_NO_FLOW_CTRL;
		else if (!pause->tx_pause)
			hw->flow_ctrl = PHY_RX_ONLY;
		else if (!pause->rx_pause)
			hw->flow_ctrl = PHY_TX_ONLY;
		else
			hw->flow_ctrl = PHY_FLOW_CTRL;
		hw->overrides &= ~PAUSE_FLOW_CTRL;
		hw->force_link = 0;
#ifdef HAVE_MICREL_SWITCH
		if (sw_is_switch(sw)) {
			port->flow_ctrl = hw->flow_ctrl;
			sw->overrides &= ~PAUSE_FLOW_CTRL;
			port->force_link = hw->force_link;
			sw->ops->port_set_link_speed(port);
		} else
#endif
		hw_set_link_speed(hw, priv->phydev);
	} else {
#ifdef HAVE_MICREL_SWITCH
		if (sw_is_switch(sw))
			sw->overrides |= PAUSE_FLOW_CTRL;
#endif
		hw->overrides |= PAUSE_FLOW_CTRL;
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

static struct {
	char string[ETH_GSTRING_LEN];
} ethtool_stats_rx_keys[RX_MIB_COUNTER_NUM] = {
	{ "rx_octets" },
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
	{ "rx_1024_to_1521_octet_packets" },
	{ "rx_1522_to_2000_octet_packets" },
#if 0
	{ "1234567890123456789012345678901" }
#endif
};

static struct {
	char string[ETH_GSTRING_LEN];
} ethtool_stats_lan_rx_keys[1] = {
	{ "rx_2001_or_more_octet_packets" },
};

static struct {
	char string[ETH_GSTRING_LEN];
} ethtool_stats_wan_rx_keys[2] = {
	{ "rx_2001_to_9216_octet_packets" },
	{ "rx_9217_or_more_octet_packets" },
};

static struct {
	char string[ETH_GSTRING_LEN];
} ethtool_stats_tx_keys[TX_MIB_COUNTER_NUM] = {
	{ "tx_octets" },
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
};

#ifndef CONFIG_KSZ8692VA
static struct {
	char string[ETH_GSTRING_LEN];
} ethtool_stats_drop_keys[2] = {
	{ "packets_dropped" },
	{ "checksum_errors_dropped" },
};
#endif

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
	struct ksz_hw *hw = &hw_priv->hw;
	size_t len = 0;
	int rx_num = hw->port_mib.cnt_end -
		RX_MIB_COUNTER_NUM - TX_MIB_COUNTER_NUM;

	if (ETH_SS_STATS == stringset) {
		memcpy(buf, &ethtool_stats_rx_keys,
			sizeof(ethtool_stats_rx_keys));
		len += sizeof(ethtool_stats_rx_keys);
		if (2 == rx_num) {
			memcpy(&buf[len], &ethtool_stats_wan_rx_keys,
				sizeof(ethtool_stats_wan_rx_keys));
			len += sizeof(ethtool_stats_wan_rx_keys);
		} else if (1 == rx_num) {
			memcpy(&buf[len], &ethtool_stats_lan_rx_keys,
				sizeof(ethtool_stats_lan_rx_keys));
			len += sizeof(ethtool_stats_lan_rx_keys);
		}
		memcpy(&buf[len], &ethtool_stats_tx_keys,
			sizeof(ethtool_stats_tx_keys));

#ifndef CONFIG_KSZ8692VA
		len += sizeof(ethtool_stats_tx_keys);
		memcpy(&buf[len], &ethtool_stats_drop_keys,
			sizeof(ethtool_stats_drop_keys));
#endif
	}
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
	struct ksz_hw *hw = &hw_priv->hw;

	switch (sset) {
	case ETH_SS_STATS:
	{
		int count = hw->port_mib.cnt_end;

#ifndef CONFIG_KSZ8692VA
		count += 2;
#endif
		return count;
	}
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
	struct ksz_hw *hw = &hw_priv->hw;
	int n_stats = stats->n_stats;
	int i;
	int n;
	int rc;

	if (hw->port_mib.state) {
		hw_priv->counter.read = 1;
		schedule_work(&hw_priv->mib_read);
		rc = wait_event_interruptible_timeout(
			hw_priv->counter.counter,
			2 == hw_priv->counter.read,
			HZ * 1);
	}
	n = TOTAL_PORT_COUNTER_NUM;
	if (n > n_stats)
		n = n_stats;
	n_stats -= n;
	for (i = 0; i < n; i++)
		*data++ = hw->port_mib.counter[i];
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

#define SIOCDEVDEBUG			(SIOCDEVPRIVATE + 10)

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
#ifdef CONFIG_1588_PTP
	struct ksz_sw *sw = hw_priv->sw;
	struct ptp_info *ptp = &sw->ptp_hw;
#endif
	int result = 0;
	struct mii_ioctl_data *data = if_mii(ifr);

	if (down_interruptible(&hw_priv->proc_sem))
		return -ERESTARTSYS;

	switch (cmd) {
	/* Get address of MII PHY in use. */
	case SIOCGMIIPHY:
		data->phy_id = priv->phy_addr;

		/* Fallthrough... */

	/* Read MII PHY register. */
	case SIOCGMIIREG:
		if (data->phy_id >= 32 || data->reg_num >= 32)
			result = -EIO;
		else
			data->val_out = mdio_read(dev, data->phy_id,
				data->reg_num);
		break;

	/* Write MII PHY register. */
	case SIOCSMIIREG:
		if (!capable(CAP_NET_ADMIN))
			result = -EPERM;
		else if (data->phy_id >= 32 || data->reg_num >= 32)
			result = -EIO;
		else
			mdio_write(dev, data->phy_id, data->reg_num,
				data->val_in);
		break;

#ifdef CONFIG_1588_PTP
	case SIOCSHWTSTAMP:
		result = -EOPNOTSUPP;
		if (sw->features & PTP_HW)
			result = ptp->ops->hwtstamp_ioctl(ptp, ifr);
		break;
	case SIOCDEVPRIVATE + 15:
		result = -EOPNOTSUPP;
		if (sw->features & PTP_HW)
			result = ptp->ops->dev_req(ptp, ifr->ifr_data, NULL);
		break;
#endif
#ifdef KSZ_MRP
	case SIOCDEVPRIVATE + 14:
	{
		struct mrp_info *mrp = &sw->mrp;

		result = -EOPNOTSUPP;
		if (sw->features & MRP_SUPPORT)
			result = mrp->ops->dev_req(mrp, ifr->ifr_data);
		break;
	}
#endif
	default:
		result = -EOPNOTSUPP;
#ifdef CONFIG_1588_PTP
		if (sw->features & PTP_HW)
			result = ptp->ops->ixxat_ioctl(ptp, cmd, ifr);
#endif
	}

	up(&hw_priv->proc_sem);

	return result;
}  /* netdev_ioctl */

static void mib_read_work(struct work_struct *work)
{
	struct dev_info *hw_priv =
		container_of(work, struct dev_info, mib_read);
	struct ksz_hw *hw = &hw_priv->hw;
	struct ksz_hw_mib *mib;

	next_jiffies = jiffies;
	mib = &hw->port_mib;

	/* Reading MIB counters or requested to read. */
	if (mib->cnt_ptr || 1 == hw_priv->counter.read) {

		/* Need to process receive interrupt. */
		if (hw_r_cnt(hw))
			return;
		hw_priv->counter.read = 0;

		/* Finish reading counters. */
		if (0 == mib->cnt_ptr) {
			hw_priv->counter.read = 2;
			wake_up_interruptible(
				&hw_priv->counter.counter);
		}
	} else if (jiffies >= hw_priv->counter.time) {
		/* Only read MIB counters when the port is connected. */
		if (mib->state)
			hw_priv->counter.read = 1;
		next_jiffies += HZ * 1 * 2;
		hw_priv->counter.time = next_jiffies;

	/* Port is just disconnected. */
	} else if (mib->link_down) {
		mib->link_down = 0;

		/* Read counters one last time after link is lost. */
		hw_priv->counter.read = 1;
	}
}  /* mib_read_work */

/*
 * Hardware monitoring
 */

static void mib_monitor(unsigned long ptr)
{
	struct dev_info *hw_priv = (struct dev_info *) ptr;

	schedule_work(&hw_priv->mib_read);

	ksz_update_timer(&hw_priv->mib_timer_info);
}  /* mib_monitor */

static int device_present;

/* -------------------------------------------------------------------------- */

#define KSZ8692_REGS_SIZE	0x10000

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

static ssize_t ksz8692_registers_read(struct file *filp, struct kobject *kobj,
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

	if (unlikely(off > KSZ8692_REGS_SIZE))
		return 0;

	if ((off + count) > KSZ8692_REGS_SIZE)
		count = KSZ8692_REGS_SIZE - off;

	if (unlikely(!count))
		return count;

	reg = off;
	addr = (u32 *) buf;
	addr_16 = (u16 *) buf;
	addr_8 = (u8 *) buf;
	for (i = 0; i < count; i += 4, reg += 4, addr++) {
		*addr = 0;
		if (check_hw_reg_range(reg)) {
			u32 data = KS_R(reg);

			if (count >= 4)
				*addr = data;
			else if (count >= 2)
				*addr_16 = (u16) data;
			else
				*addr_8 = (u8) data;
		}
	}
	return i;
}

static ssize_t ksz8692_registers_write(struct file *filp, struct kobject *kobj,
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

	if (unlikely(off >= KSZ8692_REGS_SIZE))
		return -EFBIG;

	if ((off + count) > KSZ8692_REGS_SIZE)
		count = KSZ8692_REGS_SIZE - off;

	if (unlikely(!count))
		return count;

	reg = off;
	addr = (u32 *) buf;
	addr_16 = (u16 *) buf;
	addr_8 = (u8 *) buf;
	for (i = 0; i < count; i += 4, reg += 4, addr++) {
		if (check_hw_reg_range(reg)) {
			if (count >= 4)
				KS_W(reg, *addr);
			else {
				u32 data = KS_R(reg);

				if (count >= 2) {
					data &= ~0xffff;
					data |= *addr_16;
				} else {
					data &= ~0xff;
					data |= *addr_8;
				}
				KS_W(reg, data);
			}
		}
	}
	return i;
}

static struct bin_attribute ksz8692_registers_attr = {
	.attr = {
		.name	= "registers",
		.mode	= S_IRUSR | S_IWUSR,
	},
	.size	= KSZ8692_REGS_SIZE,
	.read	= ksz8692_registers_read,
	.write	= ksz8692_registers_write,
};

/* -------------------------------------------------------------------------- */

#ifndef CONFIG_KSZ8692VA
#define IN6ADDRSZ	16
#define INADDRSZ	4
#define INT16SZ		2

/* int
 * inet_ntop4(src, dst, size)
 *  format an IPv4 address, more or less like inet_ntoa()
 * return:
 *  `dst' (as a const)
 * notes:
 *  (1) uses no statics
 *  (2) takes a u_char* not an in_addr as input
 * author:
 *  Paul Vixie, 1996.
 */
static int inet_ntop4(const uint8_t *src, char *dst, size_t size)
{
	static const char fmt[] = "%u.%u.%u.%u";

	int len;
	char tmp[sizeof "255.255.255.255"];

	snprintf(tmp, sizeof(tmp), fmt, src[0], src[1], src[2], src[3]);
	len = strlen(tmp);
	if (len + 1 > size)
		return 0;
	strcpy(dst, tmp);
	return len;
}  /* inet_ntop4 */

/* int
 * inet_ntop6(src, dst, size)
 *  convert IPv6 binary address into presentation (printable) format
 * author:
 *  Paul Vixie, 1996.
 */
static int inet_ntop6(const uint8_t *src, char *dst, size_t size)
{
	/*
	 * Note that int32_t and int16_t need only be "at least" large enough
	 * to contain a value of the specified size.  On some systems, like
	 * Crays, there is no such thing as an integer variable with 16 bits.
	 * Keep this in mind if you think this function should have been coded
	 * to use pointer overlays.  All the world's not a VAX.
	 */
	char tmp[sizeof "ffff:ffff:ffff:ffff:ffff:ffff:255.255.255.255"];
	char *tp;
	uint32_t words[IN6ADDRSZ / INT16SZ];
	int i;
	int len;
	struct { int base, len; } best, cur;

	/*
	 * Preprocess:
	 *  Copy the input (bytewise) array into a wordwise array.
	 *  Find the longest run of 0x00's in src[] for :: shorthanding.
	 */
	memset(words, 0, sizeof words);
	for (i = 0; i < IN6ADDRSZ; i++)
		words[i / 2] |= (src[i] << ((1 - (i % 2)) << 3));
	best.len = 0;
	cur.len = 0;
	best.base = -1;
	cur.base = -1;
	for (i = 0; i < (IN6ADDRSZ / INT16SZ); i++) {
		if (words[i] == 0) {
			if (cur.base == -1)
				cur.base = i, cur.len = 1;
			else
				cur.len++;
		} else {
			if (cur.base != -1) {
				if (best.base == -1 || cur.len > best.len)
					best = cur;
				cur.base = -1;
			}
		}
	}
	if (cur.base != -1) {
		if (best.base == -1 || cur.len > best.len)
			best = cur;
	}
	if (best.base != -1 && best.len < 2)
		best.base = -1;

	/*
	 * Format the result.
	 */
	tp = tmp;
	for (i = 0; i < (IN6ADDRSZ / INT16SZ); i++) {

		/* Are we inside the best run of 0x00's? */
		if (best.base != -1 && i >= best.base &&
				i < (best.base + best.len)) {
			if (i == best.base)
				*tp++ = ':';
			continue;
		}

		/* Are we following an initial run of 0x00s or any real hex? */
		if (i != 0)
			*tp++ = ':';

		/* Is this address an encapsulated IPv4? */
		if (i == 6 && best.base == 0 &&
				(best.len == 6 || (best.len == 5 &&
				words[5] == 0xffff))) {
			if (!inet_ntop4(src + 12, tp, sizeof tmp - (tp - tmp)))
				return 0;
			tp += strlen(tp);
			break;
		}
		snprintf(tp, sizeof(tmp), "%x", words[i]);
		tp += strlen(tp);
	}

	/* Was it a trailing run of 0x00's? */
	if (best.base != -1 && (best.base + best.len) == (IN6ADDRSZ / INT16SZ))
		*tp++ = ':';
	*tp++ = '\0';

	/*
	 * Check for overflow, copy, and we're done.
	 */
	len = tp - tmp;
	if ((size_t) len > size)
		return 0;
	strcpy(dst, tmp);
	return len - 1;
}  /* inet_ntop6 */

/* int
 * inet_pton4(src, dst)
 *  like inet_aton() but without all the hexadecimal and shorthand.
 * return:
 *  1 if `src' is a valid dotted quad, else 0.
 * notice:
 *  does not touch `dst' unless it's returning 1.
 * author:
 *  Paul Vixie, 1996.
 */
static int inet_pton4(const char *src, uint8_t *dst)
{
	static const char digits[] = "0123456789";

	int saw_digit;
	int octets;
	int ch;
	uint8_t tmp[INADDRSZ];
	uint8_t *tp;

	saw_digit = 0;
	octets = 0;
	*(tp = tmp) = 0;
	while ((ch = *src++) != '\0') {
		const char *pch;

		pch = strchr(digits, ch);
		if (pch != NULL) {
			uint32_t new_word = *tp * 10 + (pch - digits);

			if (new_word > 255)
				return 0;
			*tp = (uint8_t) new_word;
			if (!saw_digit) {
				if (++octets > 4)
					return 0;
				saw_digit = 1;
			}
		} else if (ch == '.' && saw_digit) {
			if (octets == 4)
				return 0;
			*++tp = 0;
			saw_digit = 0;
		} else
			return 0;
	}
	if (octets < 4)
		return 0;
	memcpy(dst, tmp, INADDRSZ);
	return 1;
}  /* inet_pton4 */

/* int
 * inet_pton6(src, dst)
 *  convert presentation level address to network order binary form.
 * return:
 *  1 if `src' is a valid [RFC1884 2.2] address, else 0.
 * notice:
 *  (1) does not touch `dst' unless it's returning 1.
 *  (2) :: in a full address is silently ignored.
 * credit:
 *  inspired by Mark Andrews.
 * author:
 *  Paul Vixie, 1996.
 */
static int inet_pton6(const char *src, uint8_t *dst)
{
	static const char xdigits_l[] = "0123456789abcdef",
			  xdigits_u[] = "0123456789ABCDEF";

	uint8_t tmp[IN6ADDRSZ];
	uint8_t *tp;
	uint8_t *endp;
	uint8_t *colonp;
	const char *xdigits;
	const char *curtok;
	int ch;
	int saw_xdigit;
	uint32_t val;

	memset((tp = tmp), 0, IN6ADDRSZ);
	endp = tp + IN6ADDRSZ;
	colonp = NULL;

	/* Leading :: requires some special handling. */
	if (*src == ':')
		if (*++src != ':')
			return 0;
	curtok = src;
	saw_xdigit = 0;
	val = 0;
	while ((ch = *src++) != '\0') {
		const char *pch;

		pch = strchr((xdigits = xdigits_l), ch);
		if (pch == NULL)
			pch = strchr((xdigits = xdigits_u), ch);
		if (pch != NULL) {
			val <<= 4;
			val |= (pch - xdigits);
			if (val > 0xffff)
				return 0;
			saw_xdigit = 1;
			continue;
		}
		if (ch == ':') {
			curtok = src;
			if (!saw_xdigit) {
				if (colonp)
					return 0;
				colonp = tp;
				continue;
			}
			if (tp + INT16SZ > endp)
				return 0;
			*tp++ = (uint8_t)(val >> 8);
			*tp++ = (uint8_t) val;
			saw_xdigit = 0;
			val = 0;
			continue;
		}
		if (ch == '.' && ((tp + INADDRSZ) <= endp)  &&
				inet_pton4(curtok, tp) > 0) {
			tp += INADDRSZ;
			saw_xdigit = 0;

			/* '\0' was seen by inet_pton4(). */
			break;
		}
		return 0;
	}
	if (saw_xdigit) {
		if (tp + INT16SZ > endp)
			return 0;
		*tp++ = (uint8_t)(val >> 8);
		*tp++ = (uint8_t) val;
	}
	if (colonp != NULL) {
		/*
		 * Since some memmove()'s erroneously fail to handle
		 * overlapping regions, we'll do the shift by hand.
		 */
		const int n = tp - colonp;
		int i;

		for (i = 1; i <= n; i++) {
			endp[-i] = colonp[n - i];
			colonp[n - i] = 0;
		}
		tp = endp;
	}
	if (tp != endp)
		return 0;
	memcpy(dst, tmp, IN6ADDRSZ);
	return 1;
}  /* inet_pton6 */
#endif

/* -------------------------------------------------------------------------- */

static void hw_cfg_802_1p(struct ksz_hw *hw, int num, int set)
{
	if (set)
		hw->map_802_1p |= 1 << num;
	else
		hw->map_802_1p &= ~(1 << num);
	if (hw->flag_802_1p)
		hw_set_802_1p_prio(hw, hw->flag_802_1p, hw->map_802_1p);
}  /* hw_cfg_802_1p */

static void hw_cfg_diffserv(struct ksz_hw *hw, int num, int set)
{
	u32 *diffserv;

	if (num < 32)
		diffserv = &hw->diffserv0;
	else {
		diffserv = &hw->diffserv1;
		num -= 32;
	}
	if (set)
		*diffserv |= 1 << num;
	else
		*diffserv &= ~(1 << num);
	if (hw->flag_diffserv)
		hw_set_diffserv_prio(hw, hw->flag_diffserv,
			hw->diffserv0, hw->diffserv1);
}  /* hw_cfg_diffserv */

static void hw_set_diffserv(struct ksz_hw *hw, const char *str, int num,
	u32 *diffserv)
{
	if ('0' != str[0] || 'x' != str[1])
		sscanf(str, "%x", &num);
	*diffserv = num;
	if (hw->flag_diffserv)
		hw_set_diffserv_prio(hw, hw->flag_diffserv,
			hw->diffserv0, hw->diffserv1);
}  /* hw_set_diffserv */

#if defined(HAVE_MICREL_SWITCH) && !defined(CONFIG_MICREL_SWITCH_EMBEDDED)

#define USE_MIB
#if defined(CONFIG_HAVE_KSZ9897)
#include "ksz_sw_sysfs_9897.c"
#elif defined(CONFIG_HAVE_KSZ8795)
#include "ksz_sw_sysfs_8795.c"
#elif defined(CONFIG_HAVE_KSZ8895)
#include "ksz_sw_sysfs_8895.c"
#else
#include "ksz_sw_sysfs.c"
#endif

#ifdef CONFIG_1588_PTP
#include "ksz_ptp_sysfs.c"
#endif
#ifdef KSZ_DLR
#include "ksz_dlr_sysfs.c"
#endif
#endif

struct all_attributes {
	int info;
	int duplex;
	int speed;
	int force;
	int flow_ctrl;
	int mib;
	int features;
	int overrides;

	int bcast_storm;
	int bcast_cnt;
	int diffserv;
	int diffserv_map0;
	int diffserv_map1;
	int diffserv_set;
	int diffserv_unset;
	int p_802_1p;
	int p_802_1p_map;
	int p_802_1p_set;
	int p_802_1p_unset;
	int acl_block;
};

struct acl_attributes {
	int enable;
	int hi_priority;
	int filter;
	int mode;
	int data;
	int mask;
	int mac;
	int offset;
	int protocol;
	int port;
	int ipv4_addr;
	int ipv4_mask;
	int ipv6_addr;
	int ipv6_mask;
};

static ssize_t display_info(char *buf, ssize_t len)
{
	len += sprintf(buf + len, "duplex:\t\t");
	len += sprintf(buf + len, "0 for auto; ");
	len += sprintf(buf + len,
		"set to 1 for half-duplex; 2, full-duplex\n");
	len += sprintf(buf + len, "speed:\t\t");
	len += sprintf(buf + len,
		"0 for auto; set to 10, 100, or 1000\n");
	len += sprintf(buf + len, "force:\t\t");
	len += sprintf(buf + len,
		"set to 1 to force link to specific speed setting\n");
	len += sprintf(buf + len, "flow_ctrl:\t");
	len += sprintf(buf + len,
		"set to 0 to disable flow control\n");
	len += sprintf(buf + len, "\n");
	len += sprintf(buf + len, "mib:\t\t");
	len += sprintf(buf + len,
		"display the MIB table\n");
	len += sprintf(buf + len, "bcast_storm:\t");
	len += sprintf(buf + len,
		"disable/enable broadcast storm protection\n");
	len += sprintf(buf + len, "bcast_cnt:\t");
	len += sprintf(buf + len,
		"set broadcast storm percentage\n");
	len += sprintf(buf + len, "diffserv:\t");
	len += sprintf(buf + len,
		"disable/enable DiffServ priority\n");
	len += sprintf(buf + len, "diffserv_map:\t");
	len += sprintf(buf + len,
		"DiffServ mapping value\n");
	len += sprintf(buf + len, "diffserv_set:\t");
	len += sprintf(buf + len,
		"change DiffServ mapping by setting bits\n");
	len += sprintf(buf + len, "diffserv_unset:\t");
	len += sprintf(buf + len,
		"change DiffServ mapping by unsetting bits\n");
	len += sprintf(buf + len, "p_802_1p:\t");
	len += sprintf(buf + len,
		"disable/enable 802.1p priority\n");
	len += sprintf(buf + len, "p_802_1p_map:\t");
	len += sprintf(buf + len,
		"802.1p mapping value\n");
	len += sprintf(buf + len, "p_802_1p_set:\t");
	len += sprintf(buf + len,
		"change 802.1p mapping by setting bits\n");
	len += sprintf(buf + len, "p_802_1p_unset:\t");
	len += sprintf(buf + len,
		"change 802.1p mapping by unsetting bits\n");
	len += sprintf(buf + len, "acl_block:\t");
	len += sprintf(buf + len,
		"set to 1 to block ACL unmatched pattern\n");
	len += sprintf(buf + len, "\nAccess Control List (ACL)\n\n");
	len += sprintf(buf + len, "enable:\t\t");
	len += sprintf(buf + len,
		"disable/enable ACL\n");
	len += sprintf(buf + len, "hi_priority:\t");
	len += sprintf(buf + len,
		"receive ACL in high priority\n");
	len += sprintf(buf + len, "filter:\t\t");
	len += sprintf(buf + len,
		"filter ACL\n");
	len += sprintf(buf + len, "mode:\t\t");
	len += sprintf(buf + len,
		"set ACL mode\n");
	len += sprintf(buf + len, "\t\t0 = MAC address\n");
	len += sprintf(buf + len, "\t\t1 = offset\n");
	len += sprintf(buf + len, "\t\t2 = protocol\n");
	len += sprintf(buf + len, "\t\t3 = destination port\n");
	len += sprintf(buf + len, "\t\t4 = source port\n");
	len += sprintf(buf + len, "\t\t5 = both ports\n");
	len += sprintf(buf + len, "\t\t6 = destination IPv4 address\n");
	len += sprintf(buf + len, "\t\t7 = source IPv4 address\n");
	len += sprintf(buf + len, "\t\t8 = both IPv4 addresses\n");
	len += sprintf(buf + len, "\t\t9 = destination IPv6 address\n");
	len += sprintf(buf + len, "\t\ta = source IPv6 address\n");
	len += sprintf(buf + len, "\t\tb = both IPv6 addresses\n");
	len += sprintf(buf + len, "data:\t\t");
	len += sprintf(buf + len,
		"set ACL data\n");
	len += sprintf(buf + len, "mask:\t\t");
	len += sprintf(buf + len,
		"set ACL mask\n");
	len += sprintf(buf + len, "mac:\t\t");
	len += sprintf(buf + len,
		"set ACL MAC address\n");
	len += sprintf(buf + len, "offset:\t\t");
	len += sprintf(buf + len,
		"set ACL offset\n");
	len += sprintf(buf + len, "protocol:\t");
	len += sprintf(buf + len,
		"set ACL protocol\n");
	len += sprintf(buf + len, "port:\t\t");
	len += sprintf(buf + len,
		"set ACL port\n");
	len += sprintf(buf + len, "ipv4_addr:\t");
	len += sprintf(buf + len,
		"set ACL IPv4 address\n");
	len += sprintf(buf + len, "ipv4_mask:\t");
	len += sprintf(buf + len,
		"set ACL IPv4 mask\n");
	len += sprintf(buf + len, "ipv6_addr:\t");
	len += sprintf(buf + len,
		"set ACL IPv6 address\n");
	len += sprintf(buf + len, "ipv6_mask:\t");
	len += sprintf(buf + len,
		"set ACL IPv6 mask\n");
	return len;
}

static ssize_t net_show(const struct device *d,
	struct device_attribute *attr, char *buf, unsigned long offset)
{
	struct net_device *dev = to_net_dev(d);
	struct dev_priv *priv = netdev_priv(dev);
	struct phy_device *phydev = priv->phydev;
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_hw *hw = &hw_priv->hw;
	ssize_t len = -EINVAL;
	int rc;
	int proc_num;

	if (down_interruptible(&hw_priv->proc_sem))
		return -ERESTARTSYS;

	len = 0;
	proc_num = offset / sizeof(int);
	switch (proc_num) {
	case PROC_INFO:
		len = display_info(buf, len);
		break;
	case PROC_SET_DUPLEX:
		len += sprintf(buf + len, "%u; ", hw->duplex);
		if (phydev->link && phydev->duplex >= 0) {
			if (phydev->duplex)
				len += sprintf(buf + len, "full-duplex\n");
			else
				len += sprintf(buf + len, "half-duplex\n");
		} else
			len += sprintf(buf + len, "unlinked\n");
		break;
	case PROC_SET_SPEED:
		len += sprintf(buf + len, "%u; ", hw->speed);
		if (phydev->link && phydev->speed)
			len += sprintf(buf + len, "%u\n", phydev->speed);
		else
			len += sprintf(buf + len, "unlinked\n");
		break;
	case PROC_SET_FORCE:
		len += sprintf(buf + len, "%u\n", hw->force_link);
		break;
	case PROC_SET_FLOW_CTRL:
		len += sprintf(buf + len, "%u; ", hw->flow_ctrl);
		switch (hw->flow_ctrl) {
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
	case PROC_SET_MIB:
		hw_priv->counter.read = 1;
		schedule_work(&hw_priv->mib_read);
		rc = wait_event_interruptible_timeout(
			hw_priv->counter.counter,
			2 == hw_priv->counter.read,
			HZ * 1);
		len += display_mib_counters(hw, buf + len);
		break;
	case PROC_SET_FEATURES:
		len += sprintf(buf + len, "%08x %08x; %08x:\n",
			hw->rx_cfg, hw->tx_cfg, hw->features);
		len += sprintf(buf + len, "\t%08x = reset hang bug\n",
			RESET_HANG_BUG);
		len += sprintf(buf + len, "\t%08x = gigabit rate change bug\n",
			GIGABIT_RATE_CHANGE_BUG);
		len += sprintf(buf + len, "\t%08x = max rx bug\n",
			MAX_RX_BUG);
		len += sprintf(buf + len,
			"\t%08x = ICMP checksum generation bug\n",
			ICMP_CSUM_GEN_BUG);
		len += sprintf(buf + len, "\t%08x = rx huge frame\n",
			RX_HUGE_FRAME);
		len += sprintf(buf + len, "\t%08x = IP header align\n",
			IP_HEADER_ALIGN);
		len += sprintf(buf + len, "\t%08x = rx jumbo frame\n",
			RX_JUMBO_FRAME);
		len += sprintf(buf + len, "\t%08x = ICMP checksum generation\n",
			ICMP_CSUM_GEN);
		len += sprintf(buf + len, "\t%08x = RGMII\n",
			RGMII_PHY);
		len += sprintf(buf + len, "\t%08x = MII\n",
			MII_PHY);
#ifdef CONFIG_NET_PEGASUS_PASSTHRU
		len += sprintf(buf + len, "\t%08x = passthru\n",
			PASSTHRU);
#endif
#ifdef HAVE_MICREL_SWITCH
		len += sprintf(buf + len, "\t%08x = MII switch\n",
			MII_SWITCH);
#endif
		break;
	case PROC_SET_OVERRIDES:
		len += sprintf(buf + len, "%08x:\n", hw->overrides);
		len += sprintf(buf + len, "\t%08x = flow control\n",
			PAUSE_FLOW_CTRL);
		len += sprintf(buf + len,
			"\t%08x = ignore max rx crc error\n",
			MAX_RX_CRC_ERR);
		len += sprintf(buf + len, "\t%08x = rx loopback\n",
			RX_LOOPBACK);
		len += sprintf(buf + len, "\t%08x = rx all\n",
			RX_ALL);
		len += sprintf(buf + len, "\t%08x = data header only\n",
			DATA_HEADER);
		break;
	case PROC_SET_BROADCAST_ENABLE:
		len += sprintf(buf + len, "%u; ", hw->flag_broadcast);
		if (hw->flag_broadcast)
			len += sprintf(buf + len, "enabled\n");
		else
			len += sprintf(buf + len, "disabled\n");
		break;
	case PROC_SET_BROADCAST_COUNTER:
		len += sprintf(buf + len, "%u\n", hw->broadcast_cnt);
		break;
	case PROC_SET_DIFFSERV_ENABLE:
		len += sprintf(buf + len, "%u; ", hw->flag_diffserv);
		if (hw->flag_diffserv)
			len += sprintf(buf + len, "enabled\n");
		else
			len += sprintf(buf + len, "disabled\n");
		break;
	case PROC_SET_DIFFSERV_MAPPING0:
		len += sprintf(buf + len, "0x%08x\n", hw->diffserv0);
		break;
	case PROC_SET_DIFFSERV_MAPPING1:
		len += sprintf(buf + len, "0x%08x\n", hw->diffserv1);
		break;
	case PROC_SET_DIFFSERV_SET:
	case PROC_SET_DIFFSERV_UNSET:
		break;
	case PROC_SET_802_1P_ENABLE:
		len += sprintf(buf + len, "%u; ", hw->flag_802_1p);
		if (hw->flag_802_1p)
			len += sprintf(buf + len, "enabled\n");
		else
			len += sprintf(buf + len, "disabled\n");
		break;
	case PROC_SET_802_1P_MAPPING:
		len += sprintf(buf + len, "0x%02x\n", hw->map_802_1p);
		break;
	case PROC_SET_802_1P_SET:
	case PROC_SET_802_1P_UNSET:
		break;
	case PROC_SET_ACL_BLOCK_UNMATCHED:
		len += sprintf(buf + len, "%u\n", hw->flag_block);
		break;
	}
	up(&hw_priv->proc_sem);
	return len;
}

static ssize_t net_store(const struct device *d,
	struct device_attribute *attr, const char *buf, size_t count,
	unsigned long offset)
{
	struct net_device *dev = to_net_dev(d);
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_hw *hw = &hw_priv->hw;
	ssize_t ret = -EINVAL;
	int changes;
	int num;
	int proc_num;

	num = get_num_val(buf);
	if (down_interruptible(&hw_priv->proc_sem))
		return -ERESTARTSYS;

	proc_num = offset / sizeof(int);
	ret = count;
	mutex_lock(&hw_priv->lock);
	switch (proc_num) {
	case PROC_SET_DUPLEX:
		if (num <= 2)
			hw->duplex = (u8) num;
		break;
	case PROC_SET_SPEED:
		if (0 == num || 10 == num || 100 == num || 1000 == num)
			hw->speed = (u16) num;
		break;
	case PROC_SET_FORCE:
		hw->force_link = (u8) num;
		break;
	case PROC_SET_FLOW_CTRL:
		if (num <= PHY_RX_ONLY)
			hw->flow_ctrl = (u8) num;
		break;
	case PROC_SET_MIB:
		break;
	case PROC_SET_FEATURES:
		if ('0' != buf[0] || 'x' != buf[1])
			sscanf(buf, "%x", &num);
		changes = hw->features ^ num;
		if ((changes & (RX_HUGE_FRAME |
				RX_JUMBO_FRAME |
				IP_HEADER_ALIGN)) &&
				hw_priv->opened) {
			printk(KERN_INFO "Stop device first\n");
			break;
		}
#ifdef CONFIG_NET_PEGASUS_PASSTHRU
		hw_priv->otherdev_running = false;
		if ((hw->features & PASSTHRU)) {
			if (hw->promiscuous)
				hw->promiscuous--;
			if (hw_priv->otherdev &&
					netif_running(hw_priv->otherdev))
				hw_priv->otherdev_running = true;
		}
#endif
		hw->features = num;
		hw_setup(hw);
		break;
	case PROC_SET_OVERRIDES:
		if ('0' != buf[0] || 'x' != buf[1])
			sscanf(buf, "%x", &num);
		changes = hw->overrides ^ num;
		if ((hw->overrides & RX_LOOPBACK) && hw->promiscuous)
			hw->promiscuous--;
		hw->overrides = num;
		hw_setup(hw);
		if (hw->enabled)
			hw_enable(hw);
		break;
	case PROC_SET_BROADCAST_ENABLE:
		if (0 == num)
			hw->flag_broadcast = 0;
		else
			hw->flag_broadcast = 1;
		hw_set_broadcast_traffic(hw, hw->flag_broadcast,
			hw->broadcast_cnt);
		break;
	case PROC_SET_BROADCAST_COUNTER:
		if (num < 0x100) {
			hw->broadcast_cnt = (u8) num;
			if (hw->flag_broadcast)
				hw_set_broadcast_traffic(hw,
					hw->flag_broadcast,
					hw->broadcast_cnt);
		}
		break;
	case PROC_SET_DIFFSERV_ENABLE:
		if (0 == num)
			hw->flag_diffserv = 0;
		else
			hw->flag_diffserv = 1;
		hw_set_diffserv_prio(hw, hw->flag_diffserv,
			hw->diffserv0, hw->diffserv1);
		break;
	case PROC_SET_DIFFSERV_MAPPING0:
		hw_set_diffserv(hw, buf, num, &hw->diffserv0);
		break;
	case PROC_SET_DIFFSERV_MAPPING1:
		hw_set_diffserv(hw, buf, num, &hw->diffserv1);
		break;
	case PROC_SET_DIFFSERV_SET:
		if (num < 64)
			hw_cfg_diffserv(hw, num, true);
		break;
	case PROC_SET_DIFFSERV_UNSET:
		if (num < 64)
			hw_cfg_diffserv(hw, num, false);
		break;
	case PROC_SET_802_1P_ENABLE:
		if (0 == num)
			hw->flag_802_1p = 0;
		else
			hw->flag_802_1p = 1;
		hw_set_802_1p_prio(hw, hw->flag_802_1p,
			hw->map_802_1p);
		break;
	case PROC_SET_802_1P_MAPPING:
		if ('0' != buf[0] || 'x' != buf[1])
			sscanf(buf, "%x", &num);
		if (num < 0x100) {
			hw->map_802_1p = (u8) num;
			if (hw->flag_802_1p)
				hw_set_802_1p_prio(hw,
					hw->flag_802_1p, hw->map_802_1p);
		}
		break;
	case PROC_SET_802_1P_SET:
		if (num < 8)
			hw_cfg_802_1p(hw, num, true);
		break;
	case PROC_SET_802_1P_UNSET:
		if (num < 8)
			hw_cfg_802_1p(hw, num, false);
		break;
	case PROC_SET_ACL_BLOCK_UNMATCHED:
		if (0 == num)
			hw->flag_block = 0;
		else
			hw->flag_block = 1;
		hw_cfg_acl_block(hw, hw->flag_block);
		break;
	default:
		pr_alert("write_proc:%d\n", proc_num);
	}
	mutex_unlock(&hw_priv->lock);
	up(&hw_priv->proc_sem);
	return ret;
}

static ssize_t netacl_show(const struct device *d,
	struct device_attribute *attr, char *buf, unsigned long offset)
{
	struct net_device *dev = to_net_dev(d);
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_hw *hw = &hw_priv->hw;
	ssize_t len = -EINVAL;
	int count = 80;
	int num;
	int port;
	struct ksz_acl_info *acl;

	if (attr->attr.name[2] != '_')
		return len;
	sscanf(attr->attr.name, "%02d", (unsigned int *) &port);
	if (port >= TOTAL_ACL_NUM)
		return len;

	if (down_interruptible(&hw_priv->proc_sem))
		return -ERESTARTSYS;

	acl = &hw->acl_info[port];
	len = 0;
	num = offset / sizeof(int);
	switch (num) {
	case PROC_8692_SET_ACL_ENABLE:
		len += sprintf(buf + len, "%u\n", acl->enable);
		break;
	case PROC_8692_SET_ACL_RX_HI_PRIORITY:
		len += sprintf(buf + len, "%u\n", acl->prio);
		break;
	case PROC_8692_SET_ACL_FILTER_MATCHED:
		len += sprintf(buf + len, "%u\n", acl->filter);
		break;
	case PROC_8692_SET_ACL_MODE:
		len += sprintf(buf + len, "%u;\n", acl->mode);
		len += sprintf(buf + len, "\t0 = mac\n");
		len += sprintf(buf + len, "\t1 = offset\n");
		len += sprintf(buf + len, "\t2 = protocol\n");
		len += sprintf(buf + len, "\t3 = destination port\n");
		len += sprintf(buf + len, "\t4 = source port\n");
		len += sprintf(buf + len, "\t5 = both ports\n");
		len += sprintf(buf + len, "\t6 = destination IPv4 address\n");
		len += sprintf(buf + len, "\t7 = source IPv4 address\n");
		len += sprintf(buf + len, "\t8 = both IPv4 addresses\n");
		if (acl->acl % 4)
			break;
		len += sprintf(buf + len, "\t9 = destination IPv6 address\n");
		len += sprintf(buf + len, "\ta = source IPv6 address\n");
		len += sprintf(buf + len, "\tb = both IPv6 addresses\n");
		break;
	case PROC_8692_SET_ACL_DATA:
		len += sprintf(buf + len, "0x%08x\n", acl->data);
		break;
	case PROC_8692_SET_ACL_MASK:
		len += sprintf(buf + len, "0x%08x\n", acl->mask);
		break;
	case PROC_8692_SET_ACL_MAC:
		len += sprintf(buf + len,
			"%02x:%02x:%02x:%02x:%02x:%02x\n",
			acl->mac[0], acl->mac[1], acl->mac[2],
			acl->mac[3], acl->mac[4], acl->mac[5]);
		break;
	case PROC_8692_SET_ACL_OFFSET:
		len += sprintf(buf + len, "%x\n", acl->offset);
		break;
	case PROC_8692_SET_ACL_PROTOCOL:
		len += sprintf(buf + len, "%x\n", acl->protocol);
		break;
	case PROC_8692_SET_ACL_PORT:
		len += sprintf(buf + len, "%x\n", acl->port);
		break;
	case PROC_8692_SET_ACL_IPV4_ADDR:
		len += inet_ntop4(acl->ip4_addr, buf + len, count - len);
		len += sprintf(buf + len, "\n");
		break;
	case PROC_8692_SET_ACL_IPV4_MASK:
		len += inet_ntop4(acl->ip4_mask, buf + len, count - len);
		len += sprintf(buf + len, "\n");
		break;
	case PROC_8692_SET_ACL_IPV6_ADDR:
		len += inet_ntop6(acl->ip6_addr, buf + len, count - len);
		len += sprintf(buf + len, "\n");
		break;
	case PROC_8692_SET_ACL_IPV6_MASK:
		len += inet_ntop6(acl->ip6_mask, buf + len, count - len);
		len += sprintf(buf + len, "\n");
		break;
	}
	up(&hw_priv->proc_sem);
	return len;
}

static ssize_t netacl_store(const struct device *d,
	struct device_attribute *attr, const char *buf, size_t count,
	unsigned long offset)
{
	struct net_device *dev = to_net_dev(d);
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_hw *hw = &hw_priv->hw;
	ssize_t ret = -EINVAL;
	int num;
	int port;
	int proc_num;
	struct ksz_acl_info *acl;
	u8 addr[16];

	if (attr->attr.name[2] != '_')
		return ret;
	sscanf(attr->attr.name, "%02d", (unsigned int *) &port);
	if (port >= TOTAL_ACL_NUM)
		return ret;
	num = get_num_val(buf);
	if (down_interruptible(&hw_priv->proc_sem))
		return -ERESTARTSYS;

	acl = &hw->acl_info[port];
	proc_num = offset / sizeof(int);
	proc_num += PROC_8692_SET_ACL_ENABLE;
	ret = count;
	mutex_lock(&hw_priv->lock);
	switch (proc_num) {
	case PROC_8692_SET_ACL_ENABLE:
	{
		int ip6_acl = acl->acl & ~3;

		/* This ACL cannot be used for IPv6. */
		if (ip6_acl != acl->acl) {
			struct ksz_acl_info *ip6 = &hw->acl_info[ip6_acl];

			/* The IPv6 ACL may be used for IPv6. */
			if (ACL_MODE_IPV6_DST <= ip6->mode &&
					ip6->mode <= ACL_MODE_IPV6_BOTH) {
				/* Currently used for IPv6. */
				if (ip6->enable)
					break;
				/*
				 * If this ACL is enabled later, the hardware
				 * needs to be updated.
				 */
				if (0 != num)
					ip6->changed = 1;
			}
		}
		if (0 == num)
			acl->enable = 0;
		else
			acl->enable = 1;

		/* Setup ACL immediately if information was changed. */
		if (acl->enable && acl->changed)
			hw_setup_acl(hw, acl, acl->mode, acl->mode);
		else {
			hw_cfg_acl_enable(hw, acl->acl, acl->enable);
#if 0
/* ? */
			if (!(acl->acl % 4))
				hw_cfg_acl_ipv6(hw, acl->acl, acl->enable);
#endif
		}
		break;
	}
	case PROC_8692_SET_ACL_FILTER_MATCHED:
		if (0 == num)
			acl->filter = 0;
		else
			acl->filter = 1;
		if (acl->enable)
			hw_cfg_acl_filter(hw, acl->acl, acl->filter);
		break;
	case PROC_8692_SET_ACL_RX_HI_PRIORITY:
		if (0 == num)
			acl->prio = 0;
		else
			acl->prio = 1;
		if (acl->enable)
			hw_cfg_acl_prio(hw, acl->acl, acl->prio);
		break;
	case PROC_8692_SET_ACL_MODE:
	{
		int last_mode = acl->mode;

		if ('0' != buf[0] || 'x' != buf[1])
			sscanf(buf, "%x", &num);
		if (ACL_MODE_MAC <= num && num <= ACL_MODE_IPV4_BOTH)
			acl->mode = num;
		else if (num <= ACL_MODE_IPV6_BOTH && !(acl->acl % 4))
			acl->mode = num;
		if (last_mode != acl->mode)
			hw_setup_acl(hw, acl, acl->mode, acl->mode);
		break;
	}
	case PROC_8692_SET_ACL_DATA:
		if ('0' != buf[0] || 'x' != buf[1])
			sscanf(buf, "%x", &num);
		acl->data = num;
		hw_setup_acl(hw, acl, ACL_MODE_OFFSET, ACL_MODE_OFFSET);
		break;
	case PROC_8692_SET_ACL_MASK:
		if ('0' != buf[0] || 'x' != buf[1])
			sscanf(buf, "%x", &num);
		acl->mask = num;
		hw_setup_acl(hw, acl, ACL_MODE_OFFSET, ACL_MODE_PORT_BOTH);
		break;
	case PROC_8692_SET_ACL_MAC:
	{
		int i;
		int n[6];

		i = sscanf(buf, "%x:%x:%x:%x:%x:%x",
			&n[0], &n[1], &n[2], &n[3], &n[4], &n[5]);
		if (6 == i) {
			for (i = 0; i < 6; i++)
				addr[i] = (u8) n[i];
			memcpy(acl->mac, addr, 6);
			hw_setup_acl(hw, acl, ACL_MODE_MAC, ACL_MODE_MAC);
		}
		break;
	}
	case PROC_8692_SET_ACL_OFFSET:
		if ('0' != buf[0] || 'x' != buf[1])
			sscanf(buf, "%x", &num);
		if (0 <= num && num <= ACL_DATA_OFFSET_MASK) {
			acl->offset = num;
			hw_setup_acl(hw, acl, ACL_MODE_OFFSET,
				ACL_MODE_OFFSET);
		}
		break;
	case PROC_8692_SET_ACL_PROTOCOL:
		if ('0' != buf[0] || 'x' != buf[1])
			sscanf(buf, "%x", &num);
		if (0 <= num && num < 0x100) {
			acl->protocol = num;
			hw_setup_acl(hw, acl, ACL_MODE_PROTOCOL,
				ACL_MODE_PROTOCOL);
		}
		break;
	case PROC_8692_SET_ACL_PORT:
		if ('0' != buf[0] || 'x' != buf[1])
			sscanf(buf, "%x", &num);
		if (0 <= num && num < 0x10000) {
			acl->port = num;
			hw_setup_acl(hw, acl, ACL_MODE_PORT_DST,
				ACL_MODE_PORT_BOTH);
		}
		break;
	case PROC_8692_SET_ACL_IPV4_ADDR:
		if (inet_pton4(buf, addr)) {
			memcpy(acl->ip4_addr, addr, 4);
			hw_setup_acl(hw, acl, ACL_MODE_IPV4_DST,
				ACL_MODE_IPV4_BOTH);
		}
		break;
	case PROC_8692_SET_ACL_IPV4_MASK:
		if (inet_pton4(buf, addr)) {
			memcpy(acl->ip4_mask, addr, 4);
			hw_setup_acl(hw, acl, ACL_MODE_IPV4_DST,
				ACL_MODE_IPV4_BOTH);
		}
		break;
	case PROC_8692_SET_ACL_IPV6_ADDR:
		if (inet_pton6(buf, addr)) {
			memcpy(acl->ip6_addr, addr, 16);
			hw_setup_acl(hw, acl, ACL_MODE_IPV6_DST,
				ACL_MODE_IPV6_BOTH);
		}
		break;
	case PROC_8692_SET_ACL_IPV6_MASK:
		if (inet_pton6(buf, addr)) {
			memcpy(acl->ip6_mask, addr, 16);
			hw_setup_acl(hw, acl, ACL_MODE_IPV6_DST,
				ACL_MODE_IPV6_BOTH);
		}
		break;
	default:
		pr_alert("write_proc:%d\n", proc_num);
	}
	mutex_unlock(&hw_priv->lock);
	up(&hw_priv->proc_sem);
	return ret;
}

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

#define ACL_ATTR(_name, _mode, _show, _store) \
struct device_attribute acl_attr_##_name = \
	__ATTR(00_##_name, _mode, _show, _store)

/* generate a read-only attribute */
#define NETACL_RD_ENTRY(name)						\
static ssize_t show_acl_##name(struct device *d,			\
	struct device_attribute *attr, char *buf)			\
{									\
	return netacl_show(d, attr, buf,				\
		offsetof(struct acl_attributes, name));			\
}									\
static ACL_ATTR(name, S_IRUGO, show_acl_##name, NULL)

/* generate a write-able attribute */
#define NETACL_WR_ENTRY(name)						\
static ssize_t show_acl_##name(struct device *d,			\
	struct device_attribute *attr, char *buf)			\
{									\
	return netacl_show(d, attr, buf,				\
		offsetof(struct acl_attributes, name));			\
}									\
static ssize_t store_acl_##name(struct device *d,			\
	struct device_attribute *attr, const char *buf, size_t count)	\
{									\
	return netacl_store(d, attr, buf, count,			\
		offsetof(struct acl_attributes, name));			\
}									\
static ACL_ATTR(name, S_IRUGO | S_IWUSR, show_acl_##name, store_acl_##name)

NET_WR_ENTRY(duplex);
NET_WR_ENTRY(speed);
NET_WR_ENTRY(force);
NET_WR_ENTRY(flow_ctrl);
NET_WR_ENTRY(mib);
NET_RD_ENTRY(info);
NET_WR_ENTRY(features);
NET_WR_ENTRY(overrides);

NET_WR_ENTRY(bcast_storm);
NET_WR_ENTRY(bcast_cnt);
NET_WR_ENTRY(diffserv);
NET_WR_ENTRY(diffserv_map0);
NET_WR_ENTRY(diffserv_map1);
NET_WR_ENTRY(diffserv_set);
NET_WR_ENTRY(diffserv_unset);
NET_WR_ENTRY(p_802_1p);
NET_WR_ENTRY(p_802_1p_map);
NET_WR_ENTRY(p_802_1p_set);
NET_WR_ENTRY(p_802_1p_unset);
NET_WR_ENTRY(acl_block);

NETACL_WR_ENTRY(enable);
NETACL_WR_ENTRY(hi_priority);
NETACL_WR_ENTRY(filter);
NETACL_WR_ENTRY(mode);
NETACL_WR_ENTRY(data);
NETACL_WR_ENTRY(mask);
NETACL_WR_ENTRY(mac);
NETACL_WR_ENTRY(offset);
NETACL_WR_ENTRY(protocol);
NETACL_WR_ENTRY(port);
NETACL_WR_ENTRY(ipv4_addr);
NETACL_WR_ENTRY(ipv4_mask);
NETACL_WR_ENTRY(ipv6_addr);
NETACL_WR_ENTRY(ipv6_mask);

static struct attribute *all_attrs[] = {
	&dev_attr_info.attr,
	&dev_attr_mib.attr,
	&dev_attr_features.attr,
	&dev_attr_overrides.attr,

	&dev_attr_bcast_storm.attr,
	&dev_attr_bcast_cnt.attr,
	&dev_attr_diffserv.attr,
	&dev_attr_diffserv_map0.attr,
	&dev_attr_diffserv_map1.attr,
	&dev_attr_diffserv_set.attr,
	&dev_attr_diffserv_unset.attr,
	&dev_attr_p_802_1p.attr,
	&dev_attr_p_802_1p_map.attr,
	&dev_attr_p_802_1p_set.attr,
	&dev_attr_p_802_1p_unset.attr,

	&dev_attr_acl_block.attr,
	NULL
};

static struct attribute *net_attrs[] = {
	&dev_attr_duplex.attr,
	&dev_attr_speed.attr,
	&dev_attr_force.attr,
	&dev_attr_flow_ctrl.attr,
	NULL
};

#ifdef HAVE_MICREL_SWITCH
static struct attribute *netlan_attrs[] = {
	&lan_attr_duplex.attr,
	&lan_attr_speed.attr,
	&lan_attr_force.attr,
	&lan_attr_flow_ctrl.attr,
	NULL
};
#endif

static struct attribute *acl_ipv4_attrs[] = {
	&acl_attr_enable.attr,
	&acl_attr_hi_priority.attr,
	&acl_attr_filter.attr,
	&acl_attr_mode.attr,
	&acl_attr_data.attr,
	&acl_attr_mask.attr,
	&acl_attr_mac.attr,
	&acl_attr_offset.attr,
	&acl_attr_protocol.attr,
	&acl_attr_port.attr,
	&acl_attr_ipv4_addr.attr,
	&acl_attr_ipv4_mask.attr,
	NULL
};

static struct attribute *acl_ipv6_attrs[] = {
	&acl_attr_enable.attr,
	&acl_attr_hi_priority.attr,
	&acl_attr_filter.attr,
	&acl_attr_mode.attr,
	&acl_attr_data.attr,
	&acl_attr_mask.attr,
	&acl_attr_mac.attr,
	&acl_attr_offset.attr,
	&acl_attr_protocol.attr,
	&acl_attr_port.attr,
	&acl_attr_ipv4_addr.attr,
	&acl_attr_ipv4_mask.attr,
	&acl_attr_ipv6_addr.attr,
	&acl_attr_ipv6_mask.attr,
	NULL
};

static struct attribute_group all_group = {
	.name  = "general",
	.attrs  = all_attrs,
};

static struct attribute_group net_group = {
	.name  = "net_port",
	.attrs  = net_attrs,
};

static struct attribute_group acl_group = {
	.name  = "acl00",
	.attrs  = acl_ipv6_attrs,
};

char *acl_name[TOTAL_ACL_NUM] = {
	"acl00",
	"acl01",
	"acl02",
	"acl03",
	"acl04",
	"acl05",
	"acl06",
	"acl07",
	"acl08",
	"acl09",
	"acl10",
	"acl11",
	"acl12",
	"acl13",
	"acl14",
	"acl15",
	"acl16",
	"acl17",
	"acl18",
	"acl19",
	"acl20",
	"acl21",
	"acl22",
	"acl23",
	"acl24",
	"acl25",
	"acl26",
	"acl27",
	"acl28",
	"acl29",
	"acl30",
	"acl31",
};

/* Kernel checking requires the attributes are in data segment. */
#define ACL_ATTRS_SIZE		(sizeof(acl_ipv6_attrs) / sizeof(void *) - 1)

static struct ksz_dev_attr ksz_dev_attrs[ACL_ATTRS_SIZE * TOTAL_ACL_NUM * 2];
static struct ksz_dev_attr *ksz_dev_attrs_ptr = ksz_dev_attrs;

static int alloc_acl_attr(struct dev_info *priv, struct attribute **attrs,
	size_t attr_size, int acl, struct ksz_dev_attr **attrs_ptr)
{
	struct attribute **attr_ptr;
	struct device_attribute *dev_attr;
	struct ksz_dev_attr *new_attr;
	char name[4];

	priv->acl_attrs[acl] = kmalloc(attr_size * sizeof(void *),
		GFP_KERNEL);
	if (!priv->acl_attrs[acl])
		return -ENOMEM;

	attr_size--;
	attr_size *= sizeof(struct ksz_dev_attr);
	priv->ksz_attrs[acl] = *attrs_ptr;
	*attrs_ptr += attr_size / sizeof(struct ksz_dev_attr);

	new_attr = priv->ksz_attrs[acl];
	attr_ptr = priv->acl_attrs[acl];
	while (*attrs != NULL) {
		dev_attr = container_of(*attrs, struct device_attribute, attr);
		memcpy(new_attr, dev_attr, sizeof(struct device_attribute));
		strncpy(new_attr->dev_name, (*attrs)->name, DEV_NAME_SIZE);
		sprintf(name, "%02d", acl);
		new_attr->dev_name[0] = name[0];
		new_attr->dev_name[1] = name[1];
		new_attr->dev_attr.attr.name = new_attr->dev_name;
		*attr_ptr = &new_attr->dev_attr.attr;
		new_attr++;
		attr_ptr++;
		attrs++;
	}
	*attr_ptr = NULL;
	return 0;
}

/* -------------------------------------------------------------------------- */

static void exit_netdev_sysfs(struct net_device *dev)
{
#ifdef HAVE_MICREL_SWITCH
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
#endif

	net_group.attrs = net_attrs;
#ifdef HAVE_MICREL_SWITCH
	if (hw_priv->hw.features & MII_SWITCH)
		net_group.attrs = netlan_attrs;
#endif
	sysfs_remove_group(&dev->dev.kobj, &net_group);
}

static int init_netdev_sysfs(struct net_device *dev)
{
#ifdef HAVE_MICREL_SWITCH
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
#endif

	net_group.attrs = net_attrs;
#ifdef HAVE_MICREL_SWITCH
	if (hw_priv->hw.features & MII_SWITCH)
		net_group.attrs = netlan_attrs;
#endif
	return sysfs_create_group(&dev->dev.kobj, &net_group);
}

static void exit_sysfs(struct net_device *dev)
{
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	int i;

	for (i = 0; i < TOTAL_ACL_NUM; i++) {
		if (!hw_priv->acl_attrs[i])
			break;
		acl_group.name = acl_name[i];
		acl_group.attrs = hw_priv->acl_attrs[i];
		sysfs_remove_group(&dev->dev.kobj, &acl_group);
		kfree(hw_priv->acl_attrs[i]);
		hw_priv->acl_attrs[i] = NULL;
		hw_priv->ksz_attrs[i] = NULL;
	}
	sysfs_remove_group(&dev->dev.kobj, &all_group);
	sysfs_remove_bin_file(&dev->dev.kobj, &ksz8692_registers_attr);
}

static int init_sysfs(struct net_device *dev)
{
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	struct attribute **acl_attrs;
	size_t acl_size;
	int err;
	int i;

	err = sysfs_create_bin_file(&dev->dev.kobj, &ksz8692_registers_attr);
	if (err)
		return err;
	err = sysfs_create_group(&dev->dev.kobj, &all_group);
	if (err)
		return err;
	for (i = 0; i < TOTAL_ACL_NUM; i++) {
		if (!(i % 4)) {
			acl_attrs = acl_ipv6_attrs;
			acl_size = sizeof(acl_ipv6_attrs);
		} else {
			acl_attrs = acl_ipv4_attrs;
			acl_size = sizeof(acl_ipv4_attrs);
		}
		err = alloc_acl_attr(hw_priv, acl_attrs,
			acl_size / sizeof(void *), i, &ksz_dev_attrs_ptr);
		if (err)
			break;
		acl_group.name = acl_name[i];
		acl_group.attrs = hw_priv->acl_attrs[i];
		err = sysfs_create_group(&dev->dev.kobj, &acl_group);
		if (err)
			break;
	}
	if (err)
		exit_sysfs(dev);
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
 * These are used to specify irregular PHY configurations.  A value of -1
 * indicates no PHY is connected.  This usually applies to WAN port, so LAN
 * port becomes eth0.  A value of 32 indicates a switch is connected but no
 * PHY address is assigned.  A dummy PHY device will be used.  Other values
 * below 32 indicates the PHY address.  Normally the PHY address of LAN port
 * is less than that of WAN port.  This allows using the exception.
 */
static int lan_phy;
static int wan_phy;

#ifdef CONFIG_MICREL_SWITCH
static int lan_multi_dev;
static int wan_multi_dev;
static int initial_multi_dev;
#endif
#ifdef HAVE_MICREL_SWITCH
static int lan_mii;
static int wan_mii;
#endif

/* -------------------------------------------------------------------------- */

static void link_reset_work(struct work_struct *work)
{
	struct dev_info *hw_priv =
		container_of(work, struct dev_info, link_reset);
	struct net_device *dev = hw_priv->dev;

	spin_lock_irq(&hw_priv->hwlock);
	if (netif_running(dev)) {
		/* To indicate no spinlock in transmit_cleanup(). */
		hw_priv->link_reset_timeout = true;
		netdev_tx_timeout(dev);
		hw_priv->link_reset_timeout = false;
	}
	spin_unlock_irq(&hw_priv->hwlock);
}  /* link_reset_work */

static void tx_reset_work(struct work_struct *work)
{
	struct dev_info *hw_priv =
		container_of(work, struct dev_info, tx_reset);
	struct net_device *dev = hw_priv->dev;
	struct dev_priv *priv = netdev_priv(dev);
#ifdef HAVE_MICREL_SWITCH
	struct ksz_hw *hw = &hw_priv->hw;
	struct ksz_sw *sw = hw_priv->sw;

	if (sw_is_switch(sw)) {
		sw->net_ops->stop(sw, false);
		sw->net_ops->start(sw, hw->override_addr);
	}
#endif

	/* Need to program misc. configuration register. */
	hw_cfg_link_speed(&hw_priv->hw, priv->phydev);
}  /* tx_reset_work */

static void promisc_reset_work(struct work_struct *work)
{
	struct delayed_work *dwork = to_delayed_work(work);
	struct dev_info *hw_priv =
		container_of(dwork, struct dev_info, promisc_reset);
	struct ksz_hw *hw = &hw_priv->hw;

	hw->promiscuous = 0;
	hw_set_promiscuous(hw, hw->promiscuous);
}  /* promisc_reset_work */

/**
 * netdev_init - initalize network device.
 * @dev:	Network device.
 *
 * This function initializes the network device.
 *
 * Return 0 if successful; otherwise an error code indicating failure.
 */
static int DEVINIT netdev_init(struct net_device *dev)
{
	struct dev_priv *priv = netdev_priv(dev);
#ifdef CONFIG_MICREL_SWITCH
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_sw *sw = hw_priv->sw;
#endif

	/* 500 ms timeout */
	dev->watchdog_timeo = HZ / 2;

	dev->hw_features |= NETIF_F_IP_CSUM;
	dev->hw_features |= NETIF_F_RXCSUM;

	dev->hw_features |= NETIF_F_IPV6_CSUM;
	dev->hw_features |= NETIF_F_SG;

	dev->features |= dev->hw_features;

	priv->mii_if.phy_id_mask = 0x1f;
	priv->mii_if.reg_num_mask = 0x1f;
	priv->mii_if.dev = dev;
	priv->mii_if.mdio_read = mdio_read;
	priv->mii_if.mdio_write = mdio_write;
	if (priv->phydev && priv->phydev->bus) {
		priv->mii_if.phy_id = priv->phy_addr;
		if ((priv->phydev->drv->features & PHY_GBIT_FEATURES) ==
				PHY_GBIT_FEATURES)
			priv->mii_if.supports_gmii = 1;
	} else
		priv->mii_if.phy_id = 0;

	priv->msg_enable = netif_msg_init(msg_enable,
		(NETIF_MSG_DRV | NETIF_MSG_PROBE | NETIF_MSG_LINK));
#ifdef CONFIG_MICREL_SWITCH
	if (sw)
		sw->msg_enable = priv->msg_enable;
#endif

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
#ifdef CONFIG_MICREL_SWITCH
	.ndo_vlan_rx_add_vid	= netdev_add_vid,
	.ndo_vlan_rx_kill_vid	= netdev_kill_vid,
#endif
};

static int DEVINIT netdev_create(struct net_device *dev)
{
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;

	dev->irq = hw_priv->hw.shift;
	dev->base_addr = 0;
	dev->mem_end = dev->mem_start + BASE_IO_RANGE - 1;
	memcpy(dev->dev_addr, hw_priv->hw.override_addr, ETH_ALEN);
	dev->netdev_ops = &netdev_ops;
	SET_ETHTOOL_OPS(dev, &netdev_ethtool_ops);
	return register_netdev(dev);
}  /* netdev_create */

static void netdev_free(struct net_device *dev)
{
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;

	/* Just free net device if not created yet. */
	if (IS_ERR(priv->phydev)) {
		free_netdev(dev);
		return;
	}
#ifdef HAVE_MICREL_SWITCH
	if (priv->phydev) {
#ifdef CONFIG_1588_PTP
		struct ksz_sw *sw = hw_priv->sw;

		if (sw->features & PTP_HW) {
			struct ptp_info *ptp = &sw->ptp_hw;

			ptp->ops->exit(ptp);
		}
#endif
		if (hw_priv->hw.features & MII_SWITCH) {
			phy_detach(priv->phydev);
			priv->phydev = NULL;
		}
	}
#endif
	/* It is a pseudo placeholder phy device. */
	if (priv->phydev && !priv->phydev->bus) {
		kfree(priv->phydev);
		priv->phydev = NULL;
	}
	if (priv->phydev) {
		phy_stop(priv->phydev);
		phy_disconnect(priv->phydev);
	}

	exit_netdev_sysfs(dev);
	if (dev == hw_priv->main_dev)
		exit_sysfs(dev);
	if (dev->watchdog_timeo)
		unregister_netdev(dev);

	free_netdev(dev);
}  /* netdev_free */

/* -------------------------------------------------------------------------- */

#define MAX_DEVICES			2

struct platform_info {
	struct dev_info dev_info;
	struct net_device *netdev;
};

static char PLATFORM_DRV_NAME[] DEVINITDATA = DRV_NAME;

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
	struct net_device *dev = info->netdev;
	int dev_count = 1;
#ifdef CONFIG_MICREL_SWITCH
	struct dev_info *hw_priv = &info->dev_info;
	struct ksz_sw *sw = hw_priv->sw;

	if (sw_is_switch(sw))
		dev_count = sw->dev_count + sw->dev_offset;
#endif
	for (i = 0; i < dev_count; i++) {
#ifdef CONFIG_MICREL_SWITCH
		if (sw_is_switch(sw)) {
			dev = sw->netdev[i];
			if (!dev)
				continue;
		}
#endif
		if (netif_running(dev)) {
			netdev_open(dev);
			netif_device_attach(dev);
		}
	}
	return 0;
}  /* netdev_resume */

static int netdev_suspend(struct platform_device *pdev, pm_message_t state)
{
	int i;
	struct platform_info *info = platform_get_drvdata(pdev);
	struct net_device *dev = info->netdev;
	int dev_count = 1;
#ifdef CONFIG_MICREL_SWITCH
	struct dev_info *hw_priv = &info->dev_info;
	struct ksz_sw *sw = hw_priv->sw;

	if (sw_is_switch(sw))
		dev_count = sw->dev_count + sw->dev_offset;
#endif
	for (i = 0; i < dev_count; i++) {
#ifdef CONFIG_MICREL_SWITCH
		if (sw_is_switch(sw)) {
			dev = sw->netdev[i];
			if (!dev)
				continue;
		}
#endif
		if (netif_running(dev)) {
			netif_device_detach(dev);
			netdev_close(dev);
		}
	}
	return 0;
}  /* netdev_suspend */

static void netdev_shutdown(struct platform_device *pdev)
{
	int i;
	struct platform_info *info = platform_get_drvdata(pdev);
	struct net_device *dev = info->netdev;
	int dev_count = 1;
#ifdef CONFIG_MICREL_SWITCH
	struct dev_info *hw_priv = &info->dev_info;
	struct ksz_sw *sw = hw_priv->sw;

	if (sw_is_switch(sw))
		dev_count = sw->dev_count + sw->dev_offset;
#endif
	for (i = 0; i < dev_count; i++) {
#ifdef CONFIG_MICREL_SWITCH
		if (sw_is_switch(sw)) {
			dev = sw->netdev[i];
			if (!dev)
				continue;
		}
#endif
		if (netif_running(dev)) {
			netif_device_detach(dev);
			netdev_close(dev);
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
	if (ETH_ALEN == i) {
		for (i = 0; i < ETH_ALEN; i++)
			hw->override_addr[i] = (u8) n[i];
		hw->mac_override = true;
	}
}  /* get_mac_addr */

/* -------------------------------------------------------------------------- */

#ifndef CONFIG_PEGASUS_NO_MDIO
static void phy_pause_machine(struct work_struct *work)
{
	struct dev_priv *priv = container_of(work, struct dev_priv, phy_pause);
	struct phy_device *phydev = priv->phydev;

	cancel_delayed_work_sync(&phydev->state_queue);
}  /* phy_pause_machine */

static void phy_init_pause(struct net_device *dev)
{
	struct dev_priv *priv = netdev_priv(dev);

	INIT_WORK(&priv->phy_pause, phy_pause_machine);
}  /* phy_init_pause */

static void phy_adjust_link(struct net_device *dev)
{
	struct dev_priv *priv = netdev_priv(dev);
	struct phy_device *phydev = priv->phydev;
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_hw *hw = &hw_priv->hw;

	hw_cfg_link_speed(hw, phydev);
	if (hw->features & GIGABIT_RATE_CHANGE_BUG) {
		if (phydev->link) {
			if (1000 == phydev->speed)
				hw_priv->gigabit_rate = true;
			else if (hw_priv->gigabit_rate) {
				hw_priv->gigabit_rate = false;
				schedule_work(&hw_priv->link_reset);
			}
		}
	}
	if (netif_msg_link(priv))
		pr_info("%s link %s\n", dev->name,
			(phydev->link ? "on" : "off"));

	if ((PHY_RUNNING == phydev->state) ||
			(PHY_NOLINK == phydev->state))
		schedule_work(&priv->phy_pause);
}  /* phy_adjust_link */
#endif

#if defined(HAVE_MICREL_SWITCH)
static void sw_adjust_link(struct net_device *dev)
{
	struct dev_priv *priv = netdev_priv(dev);
	struct phy_device *phydev = priv->phydev;
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_hw *hw = &hw_priv->hw;

	if (hw_priv->phydev != priv->phydev)
		return;
	hw_cfg_link_speed(hw, phydev);
	if (hw->features & GIGABIT_RATE_CHANGE_BUG) {
		if (phydev->link) {
			if (1000 == phydev->speed)
				hw_priv->gigabit_rate = true;
			else if (hw_priv->gigabit_rate) {
				hw_priv->gigabit_rate = false;
				schedule_work(&hw_priv->link_reset);
			}
		}
	}
}  /* sw_adjust_link */

static int sw_device_seen;
#endif

#if defined(HAVE_MICREL_SWITCH) && !defined(CONFIG_MICREL_SWITCH_EMBEDDED)
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
#endif

#if defined(HAVE_MICREL_SWITCH)
static struct ksz_sw *avail_sw;

struct ksz_sw *check_avail_switch(int id)
{
	int phy_mode;
	char phy_id[MII_BUS_ID_SIZE];
	char bus_id[MII_BUS_ID_SIZE];
	struct net_device netdev;
	struct ksz_sw *sw = NULL;
	struct phy_device *phydev = NULL;

	/* Check whether MII switch exists. */
	phy_mode = PHY_INTERFACE_MODE_MII;
	snprintf(bus_id, MII_BUS_ID_SIZE, "sw.%d", id);
	snprintf(phy_id, MII_BUS_ID_SIZE, PHY_ID_FMT, bus_id, 0);
	phydev = phy_attach(&netdev, phy_id, 0, phy_mode);
	if (!IS_ERR(phydev)) {
		struct phy_priv *phydata = phydev->priv;

		sw = phydata->port.sw;

		/*
		 * In case multiple devices mode is used and this phydev is not
		 * attached again.
		 */
		if (sw)
			phydev->interface = sw->interface;
		phy_detach(phydev);
	}
	return sw;
}
#endif

static int DEVINIT netdev_probe(struct platform_device *pdev)
{
	struct net_device *dev;
	struct dev_priv *priv;
	struct dev_info *hw_priv;
	struct ksz_hw *hw;
	struct platform_info *info;
	uint mem_start;
	struct phy_device *phydev = NULL;
	int err = -ENOMEM;
	int i;
	int dev_count;
	int port_phy;
#if !defined(CONFIG_PEGASUS_NO_MDIO) || defined(HAVE_MICREL_SWITCH)
	int phy_mode;
	char phy_id[MII_BUS_ID_SIZE];
#endif
#ifdef HAVE_MICREL_SWITCH
	char bus_id[MII_BUS_ID_SIZE];
	struct ksz_sw *sw = NULL;
	char dev_name[IFNAMSIZ];
	int port_count;
	int mib_port_count;
	int port_mii = 0;
#endif

	info = kzalloc(sizeof(struct platform_info), GFP_KERNEL);
	if (!info)
		goto netdev_probe_devinfo_err;

	hw_priv = &info->dev_info;
	hw = &hw_priv->hw;

#if defined(HAVE_MICREL_SWITCH)
	if (avail_sw) {
		sw = avail_sw;
		if (sw_device_seen > 0)
			sw = check_avail_switch(sw_device_seen);
	}
	hw_priv->sw = sw;
#endif

	/* First device is WAN port. */
	if (0 == pdev->id) {
		mem_start = (uint) KS_VIO_BASE + KS_WAN_DMA_TX;

		hw_priv->mem_start = KS_IO_BASE + KS_WAN_DMA_TX;

		hw->shift = 25;
		hw->phy_shift = 0;
		hw->reg_mib_cnt = 0xED00;
		hw->port_mib.cnt_end = WAN_PORT_COUNTER_NUM;
		hw->port_mib.tx_start = WAN_RX_MIB_COUNTER_NUM;

		hw_priv->max_buf_size = WAN_MAX_BUF_SIZE;
		hw_priv->rx_buf_size = WAN_RX_BUF_SIZE;
		hw_priv->tx_buf_size = WAN_TX_BUF_SIZE;

		if (wan_mac_addr[0] != ':')
			get_mac_addr(hw, wan_mac_addr);
		port_phy = wan_phy;

#ifdef CONFIG_MICREL_SWITCH
		if (!initial_multi_dev || wan_multi_dev)
			multi_dev = wan_multi_dev;
#endif
#ifdef HAVE_MICREL_SWITCH
		port_mii = wan_mii;
#endif
	} else {
		mem_start = (uint) KS_VIO_BASE + KS_LAN_DMA_TX;

		hw_priv->mem_start = KS_IO_BASE + KS_LAN_DMA_TX;

		hw->shift = 12;
		hw->phy_shift = 8;
		hw->reg_mib_cnt = 0xEDC0;
		hw->port_mib.cnt_end = LAN_PORT_COUNTER_NUM;
		hw->port_mib.tx_start = LAN_RX_MIB_COUNTER_NUM;

		hw_priv->max_buf_size = LAN_MAX_BUF_SIZE;
		hw_priv->rx_buf_size = LAN_RX_BUF_SIZE;
		hw_priv->tx_buf_size = LAN_TX_BUF_SIZE;

		if (lan_mac_addr[0] != ':')
			get_mac_addr(hw, lan_mac_addr);
		port_phy = lan_phy;

#ifdef CONFIG_MICREL_SWITCH
		if (!initial_multi_dev || lan_multi_dev)
			multi_dev = lan_multi_dev;
#endif
#ifdef HAVE_MICREL_SWITCH
		port_mii = lan_mii;
#endif
	}
	dev_count = 1;
	dev = NULL;

#ifdef HAVE_MICREL_SWITCH
	dev_name[0] = '\0';
	port_count = 1;
	mib_port_count = 1;
	if (sw_is_switch(sw)) {
		sw->multi_dev |= multi_dev;
		sw->stp |= stp;
		sw->fast_aging |= fast_aging;
		sw->net_ops->get_state = get_priv_state;
		sw->net_ops->set_state = set_priv_state;
		sw->net_ops->get_priv_port = get_priv_port;
		sw->net_ops->setup_special(sw, &port_count, &mib_port_count,
			&dev_count);
	}
#endif

	hw_init(hw);

	/* Default MTU is 1500. */
	if (hw->features & IP_HEADER_ALIGN) {
		hw_priv->mtu = MAX_ETHERNET_PACKET_SIZE + 4;
#if defined(CONFIG_MICREL_KSZ9897_PTP)
		if (sw_is_switch(sw))
			hw_priv->mtu += 5;
#endif
		hw_priv->mtu += MAX_ALIGN_OFFSET;
	} else
		hw_priv->mtu = REGULAR_RX_BUF_SIZE;
	hw_priv->mtu = (hw_priv->mtu + 3) & ~3;

	if (ksz_alloc_mem(hw_priv))
		goto netdev_probe_mem_err;

	hw_priv->hw.io = (void __iomem *) mem_start;

	spin_lock_init(&hw_priv->hwlock);
	mutex_init(&hw_priv->lock);

	/* Read MAC address and initialize override address if not overrided. */
	hw->mac_addr = hw->override_addr;
	hw_read_addr(hw);
	hw_setup(hw);
	hw_priv->wol_support = WOL_SUPPORT;
	hw_priv->wol_enable = 0;

	if (hw->features & GIGABIT_RATE_CHANGE_BUG)
		INIT_WORK(&hw_priv->link_reset, link_reset_work);
	INIT_WORK(&hw_priv->tx_reset, tx_reset_work);
	INIT_DELAYED_WORK(&hw_priv->promisc_reset, promisc_reset_work);

	init_waitqueue_head(&hw_priv->counter.counter);

	INIT_WORK(&hw_priv->mib_read, mib_read_work);

	/* 500 ms timeout */
	ksz_init_timer(&hw_priv->mib_timer_info, 500 * HZ / 1000,
		mib_monitor, hw_priv);

	for (i = 0; i < dev_count; i++) {
		dev = alloc_etherdev(sizeof(struct dev_priv));
		if (!dev)
			goto netdev_probe_mem_err;

		info->netdev = dev;
		hw_priv->dev = dev;

		priv = netdev_priv(dev);
		priv->adapter = hw_priv;

		priv->phy_addr = hw->phy_addr;
		priv->phydev = ERR_PTR(-ENODEV);
		if (PHY_MAX_ADDR == port_phy)
			priv->phydev = NULL;
#ifndef CONFIG_MICREL_SWITCH
		priv->phydev = NULL;
#endif
#ifndef CONFIG_PEGASUS_NO_MDIO
		phy_init_pause(dev);
		snprintf(phy_id, MII_BUS_ID_SIZE, PHY_ID_FMT, "mdio",
			hw->phy_addr);
		if (hw->features & RGMII_PHY)
			phy_mode = PHY_INTERFACE_MODE_RGMII;
		else
			phy_mode = PHY_INTERFACE_MODE_MII;
		if (hw->phy_addr < PHY_MAX_ADDR)
			priv->phydev =
				phy_connect(dev, phy_id, phy_adjust_link, 0,
					phy_mode);
#endif
#if defined(HAVE_MICREL_SWITCH)
		if (sw && (IS_ERR(priv->phydev) || !priv->phydev)) {
			int flags = 0;

			if (0 == port_mii)
				phy_mode = sw->interface;
			else if (1 == port_mii)
				phy_mode = PHY_INTERFACE_MODE_MII;
			else if (2 == port_mii)
				phy_mode = PHY_INTERFACE_MODE_RGMII;
			else if (3 == port_mii)
				phy_mode = PHY_INTERFACE_MODE_RGMII_ID;
			else if (4 == port_mii)
				phy_mode = PHY_INTERFACE_MODE_RGMII_RXID;
			else
				phy_mode = PHY_INTERFACE_MODE_RGMII_TXID;
			if (PHY_INTERFACE_MODE_MII == phy_mode)
				hw->features &= ~RGMII_PHY;
			hw->features &= ~MII_PHY;
			hw->features |= MII_SWITCH;
			priv->phy_addr = i + sw->phy_offset;
			snprintf(bus_id, MII_BUS_ID_SIZE, "sw.%d",
				sw_device_seen);
			snprintf(phy_id, MII_BUS_ID_SIZE, PHY_ID_FMT,
				bus_id, priv->phy_addr);
			priv->phydev = phy_attach(dev, phy_id, flags, phy_mode);
		}
#endif
		if (IS_ERR(priv->phydev)) {
			err = -ENODEV;
			goto netdev_probe_reg_err;
		}
#ifdef HAVE_MICREL_SWITCH
		/* This network hardware is not connected to a switch. */
		if (sw && !(hw->features & MII_SWITCH)) {
			sw = NULL;
			hw_priv->sw = NULL;
		}
		if (sw_is_switch(sw)) {
			priv->phydev->adjust_link = sw_adjust_link;
			priv->parent = sw->dev;
			priv->dev = dev;

			sw->net_ops->setup_dev(sw, dev, dev_name, &priv->port,
				i, port_count, mib_port_count);
		}
#endif

		priv->id = net_device_present;

		dev->mem_start = mem_start;
		err = netdev_create(dev);
		if (err)
			goto netdev_probe_reg_err;

		if (priv->phydev) {
#ifdef HAVE_MICREL_SWITCH
			if (!sw_is_switch(sw))
#endif
			if ((priv->phydev->drv->features & PHY_GBIT_FEATURES) !=
					PHY_GBIT_FEATURES)
				hw->features &= ~RGMII_PHY;

			phydev = priv->phydev;
			phydev->advertising =
				advertised_flow_ctrl(hw, phydev->advertising);

			/*
			 * Link default is on.  Delay reporting until device
			 * is started.
			 */
			netif_carrier_off(dev);
		} else {
			priv->phydev = kzalloc(sizeof(struct phy_device),
				GFP_KERNEL);
			priv->phydev->link = 1;
			priv->phydev->speed = 100;
			priv->phydev->duplex = 1;
			hw->features &= ~RGMII_PHY;
		}
		if (!i) {
			hw_priv->main_dev = dev;
			err = init_sysfs(dev);
			if (err)
				goto netdev_probe_reg_err;
		}
		err = init_netdev_sysfs(dev);
		if (err)
			goto netdev_probe_reg_err;
		net_device_present++;

#ifdef CONFIG_MICREL_SWITCH
		/* Save the base device name. */
		if (!dev_name[0])
			strlcpy(dev_name, dev->name, IFNAMSIZ);
#endif
	}
#ifdef HAVE_MICREL_SWITCH
	if (sw_is_switch(sw)) {
		dev = sw->netdev[0];

		hw_priv->phydev = sw->phydev;

		err = init_sw_sysfs(sw, &hw_priv->sysfs, &dev->dev);
		if (err)
			goto netdev_probe_reg_err;

#ifdef CONFIG_1588_PTP
		if (sw->features & PTP_HW) {
			struct ptp_info *ptp = &sw->ptp_hw;

#ifdef CONFIG_MICREL_FPGA_BOARD
			ptp->ops->acquire(sw);
			ptp->reg->write(ptp, ADDR_16, REG_RESET_CTRL,
				GLOBAL_SOFTWARE_RESET);
			ptp->reg->write(ptp, ADDR_16, REG_RESET_CTRL, 0);
			ptp->ops->release(sw);
#endif

			ptp->get_clk_cnt = get_clk_cnt;
			ptp->clk_divider = ksz_system_bus_clock;
			ptp->ops->init(ptp, hw->mac_addr);
			if (ptp->version < 1)
				sw->features &= ~VLAN_PORT_REMOVE_TAG;

			err = init_ptp_sysfs(&hw_priv->ptp_sysfs, &dev->dev);
			if (err)
				goto netdev_probe_reg_err;
		}
#endif
#ifdef KSZ_DLR
		if (sw->features & DLR_HW) {
			err = init_dlr_sysfs(&dev->dev);
			if (err)
				goto netdev_probe_reg_err;
		}
#endif
		++sw_device_seen;
	}
#endif
	sema_init(&hw_priv->proc_sem, 1);
	request_mem_region(hw_priv->mem_start, BASE_IO_RANGE,
		info->netdev->name);

	hw_init_cnt(hw);

	/* tasklet is enabled. */
	tasklet_init(&hw_priv->rx_tasklet, rx_proc_task,
		(unsigned long) hw_priv);
	tasklet_init(&hw_priv->tx_tasklet, tx_proc_task,
		(unsigned long) hw_priv);

	/* tasklet_enable will decrement the atomic counter. */
	tasklet_disable(&hw_priv->rx_tasklet);
	tasklet_disable(&hw_priv->tx_tasklet);

	platform_set_drvdata(pdev, info);

#ifdef CONFIG_NET_PEGASUS_PASSTHRU
	skb_queue_head_init(&hw_priv->tx_queue);
	if (0 == pdev->id)
		first_dev = hw_priv;
	else {
		if (first_dev) {
			if (alloc_skb_pool(hw_priv)) {
				free_skb_pool();
				goto netdev_probe_reg_err;
			}
			first_dev->otherdev = hw_priv->dev;
			hw_priv->otherdev = first_dev->dev;
		}
	}
#endif
	return 0;

netdev_probe_reg_err:
#ifdef CONFIG_MICREL_SWITCH
	if (sw_is_switch(sw)) {
		int dev_count = sw->dev_count + sw->dev_offset;

		for (i = 0; i < dev_count; i++) {
			dev = sw->netdev[i];
			if (dev) {
				netdev_free(dev);
				sw->netdev[i] = NULL;
			}
		}
	} else
#endif
	free_netdev(dev);

netdev_probe_mem_err:
	ksz_free_mem(hw_priv);
	kfree(info);

netdev_probe_devinfo_err:
	return err;
}  /* netdev_probe */

static int netdev_remove(struct platform_device *pdev)
{
	struct platform_info *info = platform_get_drvdata(pdev);
	struct net_device *dev = info->netdev;
	struct dev_info *hw_priv = &info->dev_info;
#ifdef HAVE_MICREL_SWITCH
	struct ksz_sw *sw = hw_priv->sw;
#endif

	platform_set_drvdata(pdev, NULL);

#ifdef CONFIG_NET_PEGASUS_PASSTHRU
	if (0 == pdev->id && hw_priv->otherdev)
		free_skb_pool();
#endif
	release_mem_region(hw_priv->mem_start, BASE_IO_RANGE);
#ifdef HAVE_MICREL_SWITCH
	if (sw_is_switch(sw)) {
		int i;
		int dev_count = sw->dev_count + sw->dev_offset;

		dev = sw->netdev[0];
		if (dev) {
#ifdef KSZ_DLR
			if (sw->features & DLR_HW)
				exit_dlr_sysfs(&dev->dev);
#endif
#ifdef CONFIG_1588_PTP
			if (sw->features & PTP_HW)
				exit_ptp_sysfs(&hw_priv->ptp_sysfs, &dev->dev);
#endif
			exit_sw_sysfs(sw, &hw_priv->sysfs, &dev->dev);
		}
		for (i = 0; i < dev_count; i++) {
			dev = sw->netdev[i];
			if (dev)
				netdev_free(dev);
		}
	} else
#endif
	netdev_free(dev);
	ksz_free_mem(hw_priv);
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

#ifndef CONFIG_PEGASUS_NO_MDIO
static struct mdio_priv {
	struct resource *io;
	int irqnum;
	int irq[PHY_MAX_ADDR];
	char name[40];
	u32 phy_installed;
	int phy_id[2];
	struct phy_device *phydev[2];
} mdio_data;

static u32 ksz_mdio_access(struct mdio_priv *priv, int phy_id)
{
	u32 installed = priv->phy_installed;

	if (phy_id != priv->phy_id[0] && phy_id != priv->phy_id[1]) {
		installed &= ~(STA_PHY0_VALID | STA_PHY0_ADD_MASK);
		installed |= (STA_PHY0_VALID | phy_id);
		KS_W(KS8692_STA_PHY, installed);
	}
	return installed;
}  /* ksz_mdio_access */

static int ksz_mdio_read(struct mii_bus *bus, int phy_id, int regnum)
{
	int phy;
	int status;
	int timeout = STA_TIMEOUT;
	int ret = -1;
	u32 installed;
	struct mdio_priv *priv = bus->priv;

	installed = ksz_mdio_access(priv, phy_id);
	phy = (regnum << 6) | (phy_id << 1) | STA_READ;
	KS_W(KS8692_STA_COMM, phy);
	KS_W(KS8692_STA_CTRL, STA_START);
	do {
		udelay(2);
		status = KS_R(KS8692_STA_STATUS) & STA_STATUS_MASK;
	} while (status != STA_READ_DONE && --timeout);
	if (STA_READ_DONE == status)
		ret = (u16) KS_R(KS8692_STA_DATA0);
	if (installed != priv->phy_installed && priv->phy_installed)
		KS_W(KS8692_STA_PHY, priv->phy_installed);
	return ret;
}  /* ksz_mdio_read */

static int ksz_mdio_write(struct mii_bus *bus, int phy_id, int regnum, u16 val)
{
	int phy;
	int status;
	int timeout = STA_TIMEOUT;
	u32 installed;
	struct mdio_priv *priv = bus->priv;

	installed = ksz_mdio_access(priv, phy_id);
	phy = (regnum << 6) | (phy_id << 1) | STA_WRITE;
	KS_W(KS8692_STA_DATA0, val);
	KS_W(KS8692_STA_COMM, phy);
	KS_W(KS8692_STA_CTRL, STA_START);
	do {
		udelay(2);
		status = KS_R(KS8692_STA_STATUS) & STA_STATUS_MASK;
	} while (status != STA_WRITE_DONE && --timeout);
	if (installed != priv->phy_installed && priv->phy_installed)
		KS_W(KS8692_STA_PHY, priv->phy_installed);
	if (STA_WRITE_DONE == status)
		return 0;
	return -EBUSY;
}  /* ksz_mdio_write */

static int ksz_mdio_reset(struct mii_bus *bus)
{
	return 0;
}

static irqreturn_t ksz_mdio_interrupt(int irq, void *dev_id)
{
	u32 status;
	int i;
	struct phy_device *phydev;
	struct mdio_priv *priv = dev_id;

	status = KS_R(KS8692_STA_INT_STATUS);

	for (i = 0; i < 2; i++) {
		phydev = priv->phydev[i];
		if (phydev && (status & (PHY0_UP | PHY0_DN))) {
			if ((PHY_RUNNING == phydev->state) ||
					(PHY_NOLINK == phydev->state))
				phydev->state = PHY_CHANGELINK;
			schedule_delayed_work(&phydev->state_queue, 0);
		}
		status >>= 2;
	}

	return IRQ_HANDLED;
}  /* ksz_mdio_interrupt */

static int ksz_mdio_setup(struct mii_bus *bus)
{
	u32 data;
	u32 installed = 0;
	int i;
	int id1;
	int id2;
	int val;
	int zero1 = 0;
	int zero2 = 0;
	int first = PHY_MAX_ADDR;
	int second = PHY_MAX_ADDR;
	int last = PHY_MAX_ADDR;
	int mask = 0xffffffff;
	int num = 0;
	struct mdio_priv *priv = bus->priv;

	/* Need to setup the PHY valid register to access the PHY. */
	data = KS_R(KS8692_STA_PHY);
	data &= ~(STA_PHY1_VALID | STA_PHY1_ADD_MASK |
		STA_PHY0_VALID | STA_PHY0_ADD_MASK);
#if !defined(CONFIG_PEGASUS_LAN_SPECIAL)
	for (i = 0; i < PHY_MAX_ADDR; i++) {
#else
	for (i = 1; i < PHY_MAX_ADDR; i++) {
#endif
		id1 = bus->read(bus, i, MII_PHYSID1);
		if (id1 < 0)
			continue;
		id2 = bus->read(bus, i, MII_PHYSID2);
		if (id2 < 0 || (0xfff == (id1 & 0xfff) && 0xffff == id2))
			continue;
		if (0 == i) {
			zero1 = id1;
			zero2 = id2;
		}
#ifdef CONFIG_PEGASUS_LAN_SPECIAL
		if (i < 4)
			continue;
#endif
		if (PHY_MAX_ADDR == first)
			first = i;
		else if (PHY_MAX_ADDR == second)
			second = i;
		last = i;
		mask &= ~(1 << i);
		num++;
	}

	/* PHY may respond to zero address. */
	if (!(mask & 1)) {
		for (i = 1; i < PHY_MAX_ADDR; i++) {
			if (mask & (1 << i))
				continue;
			id1 = bus->read(bus, i, MII_PHYSID1);
			id2 = bus->read(bus, i, MII_PHYSID2);
			if (id1 == zero1 && id2 == zero2) {
				id1 = bus->read(bus, i, MII_BMCR);
				val = id1;
				id1 |= BMCR_SPEED100;
				bus->write(bus, i, MII_BMCR, id1);
				id2 = bus->read(bus, 0, MII_BMCR);
				bus->write(bus, i, MII_BMCR, val);
				if (id1 == id2) {
					mask |= 1;
					if (0 == first)
						first = second;
					break;
				}
			}
		}
	}

	/* Found at least one PHY. */
	if (first != PHY_MAX_ADDR) {

		/* Only one PHY found. */
		if (first == last) {

			/* No PHY connected to WAN port. */
			if (PHY_MAX_ADDR == wan_phy)
				last = PHY_MAX_ADDR;
		} else {
			if (0 < wan_phy && wan_phy < PHY_MAX_ADDR &&
					wan_phy == first) {
				first = last;
				if (0 < lan_phy && lan_phy < PHY_MAX_ADDR &&
						first != lan_phy) {
					printk(KERN_ALERT
						"Use PHY %d instead of %d\n",
						lan_phy, first);
					first = lan_phy;
				}
				last = wan_phy;
			} else if (0 < lan_phy && lan_phy < PHY_MAX_ADDR &&
					lan_phy == last) {
				last = first;
				if (0 < wan_phy && wan_phy < PHY_MAX_ADDR &&
						last != wan_phy) {
					printk(KERN_ALERT
						"Use PHY %d instead of %d\n",
						wan_phy, last);
					last = wan_phy;
				}
				first = lan_phy;
			}
		}

		/* Nothing connected to WAN port. */
		if (wan_phy == -1)
			last = PHY_MAX_ADDR;

		/* Nothing connected to LAN port. */
		if (lan_phy == -1)
			first = PHY_MAX_ADDR;
	}
	if (first != PHY_MAX_ADDR && first != last) {
		installed = first | STA_PHY0_VALID;
		installed <<= 8;
	}
	if (last != PHY_MAX_ADDR)
		installed |= last | STA_PHY0_VALID;
	data |= installed;
	KS_W(KS8692_STA_PHY, data);
	priv->phy_installed = installed;
	if (installed & STA_PHY0_VALID)
		priv->phy_id[0] = installed & STA_PHY0_ADD_MASK;
	installed >>= 8;
	if (installed & STA_PHY0_VALID)
		priv->phy_id[1] = installed & STA_PHY0_ADD_MASK;
	return mask;
}  /* ksz_mdio_setup */

static int ksz_mdio_probe(struct platform_device *pdev)
{
	struct mii_bus *bus;
	struct resource *io;
	int err;
	int i;

	bus = mdiobus_alloc();
	if (bus == NULL)
		return -ENOMEM;

	sprintf(mdio_data.name, "mdio_bus");

	io = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!request_mem_region(io->start, resource_size(io), mdio_data.name)) {
		err = -ENODEV;
		goto mdio_probe_free_mii_bus;
	}
	mdio_data.io = io;
	mdio_data.irqnum = platform_get_irq(pdev, 0);
	mdio_data.phy_installed = 0;
	mdio_data.phy_id[0] = PHY_MAX_ADDR;
	mdio_data.phy_id[1] = PHY_MAX_ADDR;

	hw_init_phy_ctrl();

	bus->name = "Pegasus MII bus",
	bus->read = ksz_mdio_read;
	bus->write = ksz_mdio_write;
	bus->reset = ksz_mdio_reset;
	snprintf(bus->id, MII_BUS_ID_SIZE, "mdio");
	bus->parent = &pdev->dev;
	bus->phy_mask = 0x00000000;
	bus->priv = &mdio_data;
	bus->irq = mdio_data.irq;

	for (i = 0; i < PHY_MAX_ADDR; i++)
		bus->irq[i] = PHY_POLL;

	bus->phy_mask = ksz_mdio_setup(bus);

	err = mdiobus_register(bus);
	if (err < 0)
		goto mdio_probe_free_region;

	if (mdio_data.phy_id[0] != PHY_MAX_ADDR)
		mdio_data.phydev[0] = bus->phy_map[mdio_data.phy_id[0]];
	if (mdio_data.phy_id[1] != PHY_MAX_ADDR)
		mdio_data.phydev[1] = bus->phy_map[mdio_data.phy_id[1]];

	KS_R(KS8692_STA_INT_STATUS);
	err = request_irq(mdio_data.irqnum, ksz_mdio_interrupt, 0,
		mdio_data.name, &mdio_data);
	if (err)
		goto mdio_probe_unreg_bus;

	platform_set_drvdata(pdev, bus);

	return 0;

mdio_probe_unreg_bus:
	mdiobus_unregister(bus);

mdio_probe_free_region:
	release_mem_region(io->start, resource_size(io));

mdio_probe_free_mii_bus:
	mdiobus_free(bus);

	return err;
}  /* ksz_mdio_probe */

static int ksz_mdio_remove(struct platform_device *pdev)
{
	struct mii_bus *bus = platform_get_drvdata(pdev);
	struct mdio_priv *priv = bus->priv;
	struct resource *io = priv->io;

	mdiobus_unregister(bus);
	free_irq(priv->irqnum, priv);
	release_mem_region(io->start, resource_size(io));
	mdiobus_free(bus);
	platform_set_drvdata(pdev, NULL);

	return 0;
}  /* ksz_mdio_remove */

static struct platform_driver ksz_mdio_driver = {
	.driver		= {
		.name	= "pegasus-mdio",
	},
	.probe		= ksz_mdio_probe,
	.remove		= ksz_mdio_remove,
};

#define IO_MDIO		(KS_IO_BASE + KS8692_STA_CONF)
#define IRQ_MDIO	(KS8692_INT_MDIO + LOW_IRQS)

static struct resource pegasus_mdio_resource[] = {
	[0] = {
		.start	= IO_MDIO,
		.end	= IO_MDIO + 0x40 - 1,
		.flags	= IORESOURCE_MEM,
	},
	[1] = {
		.start	= IRQ_MDIO,
		.end	= IRQ_MDIO,
		.flags	= IORESOURCE_IRQ,
	}
};

static void platform_release(struct device *device)
{
	struct platform_device *pdev;

	pdev = to_platform_device(device);
}

struct platform_device pegasus_mdio = {
	.name		= "pegasus-mdio",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(pegasus_mdio_resource),
	.resource	= pegasus_mdio_resource,
	.dev		= {
		.release = platform_release
	}
};

static int __init ksz_mdio_init(void)
{
	int ret;

	ret = platform_device_register(&pegasus_mdio);
	if (ret)
		return ret;
	return platform_driver_register(&ksz_mdio_driver);
}

static void __exit ksz_mdio_exit(void)
{
	platform_driver_unregister(&ksz_mdio_driver);
	platform_device_unregister(&pegasus_mdio);
}
#endif

#ifdef CONFIG_NET_DSA_TAG_TAIL
static void setup_micrel_switch(struct platform_device *pdev,
	struct ksz_sw *sw)
{
	struct platform_info *info = platform_get_drvdata(pdev);
	struct net_device *dev = info->netdev;
	struct dev_priv *priv = netdev_priv(dev);

	if (!priv->phydev->bus || !sw)
		return;
	micrel_switch_init(&micrel_switch_plat_data, NO_IRQ,
		&dev->dev, &priv->phydev->bus->dev, sw);
}
#endif

static struct platform_device *ksz8692_platform[MAX_DEVICES];
static int device_present;

static void platform_free_devices(int num)
{
	struct platform_device *pdev;
	int i;

	for (i = 0; i < num; i++) {
		pdev = ksz8692_platform[i];
		if (pdev)
			platform_device_unregister(pdev);
	}
}  /* platform_free_devices */

static int INIT platform_init(void)
{
	struct platform_device *pdev;
	int err;
	int i;
	int j;
	int max = MAX_DEVICES;
	int first = 0;

#if defined(HAVE_MICREL_SWITCH)
	struct ksz_sw *sw = NULL;

	sw = check_avail_switch(0);
	avail_sw = sw;
#endif

#ifndef CONFIG_PEGASUS_NO_MDIO
	err = ksz_mdio_init();
	if (err)
		goto device_reg_err;
#endif

#ifdef CONFIG_MICREL_SWITCH
	initial_multi_dev = multi_dev;
#endif
#ifdef CONFIG_PEGASUS_WAN_ONLY
	max = 1;
#endif
#if defined(HAVE_MICREL_SWITCH) && defined(CONFIG_MICREL_CTRL_BOARD)
	if (sw) {
		/*
		 * Default U-Boot setting in Micrel Control Board is that the
		 * LAN port uses MII interface.
		 */
		if (!wan_mii && PHY_INTERFACE_MODE_MII == sw->interface)
			first = 1;
	}
#endif
	if (lan_phy == -1 || wan_phy == -1)
		max = 1;
	if (wan_phy == -1)
		first = 1;
	memset(ksz8692_platform, 0, sizeof(ksz8692_platform));
	for (i = 0; i < max; i++) {
		pdev = kzalloc(sizeof(struct platform_device), GFP_KERNEL);
		if (!pdev) {
			err = -ENOMEM;
			goto device_reg_err;
		}

		j = (i + first) & 1;
		pdev->name = PLATFORM_DRV_NAME;
		pdev->id = j;
		pdev->dev.release = netdev_platform_release;
		pdev->num_resources = 1;
		pdev->resource = &net_resources[j];

		if (platform_device_register(pdev)) {
			if (device_present)
				break;
			err = -ENODEV;
			goto device_reg_err;
		}

		ksz8692_platform[i] = pdev;
		++device_present;
	}

	err = platform_driver_register(&netdev_driver);
	if (err)
		goto device_reg_err;

#ifdef CONFIG_NET_DSA_TAG_TAIL
	setup_micrel_switch(ksz8692_platform[0], sw);
#endif

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
#ifndef CONFIG_PEGASUS_NO_MDIO
	ksz_mdio_exit();
#endif
#ifdef CONFIG_MICREL_KSZ8463_EMBEDDED
	ksz8463_exit();
#endif
#ifdef CONFIG_MICREL_KSZ8863_EMBEDDED
	ksz8863_exit();
#endif
#ifdef CONFIG_MICREL_KSZ8795_EMBEDDED
	ksz8795_exit();
#endif
#ifdef CONFIG_MICREL_KSZ8895_EMBEDDED
	ksz8895_exit();
#endif
#ifdef CONFIG_MICREL_KSZ9897_EMBEDDED
	ksz9897_exit();
#endif
}  /* platform_exit */

#if defined(CONFIG_SPI_FTDI) && defined(CONFIG_NET_PEGASUS)
static void late_init(void)
{
	platform_init();
}
#endif

static int __init ksz8692_init_module(void)
{
#ifdef DEBUG_MSG
	if (init_dbg())
		return -ENOMEM;
#endif

	printk(KERN_INFO "%s\n", version);

#ifdef CONFIG_MICREL_KSZ8463_EMBEDDED
	ksz8463_init();
#endif
#ifdef CONFIG_MICREL_KSZ8863_EMBEDDED
	ksz8863_init();
#endif
#ifdef CONFIG_MICREL_KSZ8795_EMBEDDED
	ksz8795_init();
#endif
#ifdef CONFIG_MICREL_KSZ8895_EMBEDDED
	ksz8895_init();
#endif
#ifdef CONFIG_MICREL_KSZ9897_EMBEDDED
	ksz9897_init();
#endif
#if defined(CONFIG_SPI_FTDI) && defined(CONFIG_NET_PEGASUS)
	pegasus_register_late_call(late_init);
	return 0;
#else
	return platform_init();
#endif
}

static void __exit ksz8692_cleanup_module(void)
{
	platform_exit();

#ifdef DEBUG_MSG
	exit_dbg();
#endif
}

module_init(ksz8692_init_module);
module_exit(ksz8692_cleanup_module);

MODULE_DESCRIPTION("KSZ8692 network driver");
MODULE_AUTHOR("Tristram Ha <Tristram.Ha@microchip.com>");
MODULE_LICENSE("GPL");

module_param_named(message, msg_enable, int, 0);
MODULE_PARM_DESC(message, "Message verbosity level (0=none, 31=all)");

module_param(lan_mac_addr, charp, 0);
module_param(wan_mac_addr, charp, 0);
MODULE_PARM_DESC(lan_mac_addr, "LAN MAC address");
MODULE_PARM_DESC(wan_mac_addr, "WAN MAC address");

module_param(lan_phy, int, 0);
module_param(wan_phy, int, 0);
MODULE_PARM_DESC(lan_phy, "LAN PHY address");
MODULE_PARM_DESC(wan_phy, "WAN PHY address");

#ifdef CONFIG_MICREL_SWITCH
module_param(fast_aging, int, 0);
module_param(multi_dev, int, 0);
module_param(stp, int, 0);
module_param(lan_multi_dev, int, 0);
module_param(wan_multi_dev, int, 0);
MODULE_PARM_DESC(fast_aging, "Fast aging");
MODULE_PARM_DESC(multi_dev, "Multiple device interfaces");
MODULE_PARM_DESC(stp, "STP support");
MODULE_PARM_DESC(lan_multi_dev, "Multiple device interfaces in LAN port");
MODULE_PARM_DESC(wan_multi_dev, "Multiple device interfaces in WAN port");
#endif
#ifdef HAVE_MICREL_SWITCH
module_param(lan_mii, int, 0);
module_param(wan_mii, int, 0);
MODULE_PARM_DESC(wan_mii, "MII interface for WAN port");
MODULE_PARM_DESC(lan_mii, "MII interface for LAN port");
#endif
