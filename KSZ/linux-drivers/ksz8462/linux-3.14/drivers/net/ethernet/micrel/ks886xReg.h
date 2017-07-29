/**
 * Micrel KSZ8862 Register Definitions.
 *
 * Copyright (C) 2015 Microchip Technology Inc.
 * Copyright (C) 2010-2015 Micrel, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 *
  ----------------------------------------------------------------------------

  Author  Date      Version  Description
  PCD     04/08/10  0.0.1    Register definition for KS8861/2.
  ----------------------------------------------------------------------------
 */

#ifndef __KS886XREG_h
#define __KS886XREG_h


/*
 * QMU/BIC Registers
 * (Bank 0, Offset 0x100 - 0x200)
 */

#define REG_CHIP_CFG_STATUS        0x108       /* CCFG */
/* Bus in little endian mode */
#define   LITTLE_ENDIAN_BUS_MODE     (1 << 10)
/* External EEPROM is used */
#define   EEPROM_PRESENCE            (1 << 9)
/* In SPI bus mode */
#define   SPI_BUS_MODE               (1 << 8)
/* In 8-bit bus mode operation */
#define   DATA_BUS_8BIT              (1 << 7)
/* In 16-bit bus mode operation */
#define   DATA_BUS_16BIT             (1 << 6)
/* Data and address bus are shared */
#define   MULTIPLEX_MODE             (1 << 4)
/* 48-pin package */
#define   CHIP_PACKAGE_48PIN         (1 << 1)
/* 32-pin package for SPI host interface only */
#define   CHIP_PACKAGE_32PIN         (1 << 0)

#define REG_MAC_ADDR_0             0x110       /* MARL */
#define REG_MAC_ADDR_1             0x111       /* MARL */
#define REG_MAC_ADDR_2             0x112       /* MARM */
#define REG_MAC_ADDR_3             0x113       /* MARM */
#define REG_MAC_ADDR_4             0x114       /* MARH */
#define REG_MAC_ADDR_5             0x115       /* MARH */

#define REG_EEPROM_CTRL            0x122       /* EEPCR */
/* 0 set EDD pad tri-state during read and set to 1 during write. */
#define   EEPROM_DATA_WRITE          (1 << 5)
/* Enable software to access EEPROM through bit 3 to bit 0 */
#define   EEPROM_ACCESS_ENABLE       (1 << 4)
/* Data receive from EEPROM (EEDI pin) */
#define   EEPROM_DATA_IN             (1 << 3)
/* Data transmit to EEPROM (EEDO pin) */
#define   EEPROM_DATA_OUT            (1 << 2)
/* Serial clock (EESK pin) */
#define   EEPROM_SERIAL_CLOCK        (1 << 1)
/* EEPROM chip select (EECS pin) */
#define   EEPROM_CHIP_SELECT         (1 << 0)


#define REG_RESET_CTRL             0x126       /* GRR */
#define   PTP_SOFTWARE_RESET         (1 << 2)
/* QMU soft reset (clear TxQ, RxQ) */
#define   QMU_SOFTWARE_RESET         (1 << 1)
/* Global soft reset (PHY, MAC, QMU) */
#define   GLOBAL_SOFTWARE_RESET      (1 << 0)


/* Wake On Lan Control Registers */

#define REG_WOL_CTRL_ETH           0x12A       /* WFCR */
/* Enable the magic packet pattern detection */
#define   WOL_MAGIC_ENABLE_ETH       (1 << 7)
/* Enable the wake up frame 3 pattern detection */
#define   WOL_FRAME3_ENABLE_ETH      (1 << 3)
/* Enable the wake up frame 2 pattern detection */
#define   WOL_FRAME2_ENABLE_ETH      (1 << 2)
/* Enable the wake up frame 1 pattern detection */
#define   WOL_FRAME1_ENABLE_ETH      (1 << 1)
/* Enable the wake up frame 0 pattern detection */
#define   WOL_FRAME0_ENABLE_ETH      (1 << 0)

#define REG_WOL_FRAME0_CRC0        0x130       /* WF0CRC0 */
#define REG_WOL_FRAME0_CRC1        0x132       /* WF0CRC1 */
#define REG_WOL_FRAME0_BYTE_MASK0  0x134       /* WF0BM0 */
#define REG_WOL_FRAME0_BYTE_MASK1  0x136       /* WF0BM1 */
#define REG_WOL_FRAME0_BYTE_MASK2  0x138       /* WF0BM2 */
#define REG_WOL_FRAME0_BYTE_MASK3  0x13A       /* WF0BM3 */

#define REG_WOL_FRAME1_CRC0        0x140       /* WF1CRC0 */
#define REG_WOL_FRAME1_CRC1        0x142       /* WF1CRC1 */
#define REG_WOL_FRAME1_BYTE_MASK0  0x144       /* WF1BM0 */
#define REG_WOL_FRAME1_BYTE_MASK1  0x146       /* WF1BM1 */
#define REG_WOL_FRAME1_BYTE_MASK2  0x148       /* WF1BM2 */
#define REG_WOL_FRAME1_BYTE_MASK3  0x14A       /* WF1BM3 */

#define REG_WOL_FRAME2_CRC0        0x150       /* WF2CRC0 */
#define REG_WOL_FRAME2_CRC1        0x152       /* WF2CRC1 */
#define REG_WOL_FRAME2_BYTE_MASK0  0x154       /* WF2BM0 */
#define REG_WOL_FRAME2_BYTE_MASK1  0x156       /* WF2BM1 */
#define REG_WOL_FRAME2_BYTE_MASK2  0x158       /* WF2BM2 */
#define REG_WOL_FRAME2_BYTE_MASK3  0x15A       /* WF2BM3 */

#define REG_WOL_FRAME3_CRC0        0x160       /* WF3CRC0 */
#define REG_WOL_FRAME3_CRC1        0x162       /* WF3CRC1 */
#define REG_WOL_FRAME3_BYTE_MASK0  0x164       /* WF3BM0 */
#define REG_WOL_FRAME3_BYTE_MASK1  0x166       /* WF3BM1 */
#define REG_WOL_FRAME3_BYTE_MASK2  0x168       /* WF3BM2 */
#define REG_WOL_FRAME3_BYTE_MASK3  0x16A       /* WF3BM3 */


/* Transmit/Receive Control Registers */

/* Transmit Frame Header */
/* Dummy address to access QMU RxQ, TxQ */
#define REG_QDR_DUMMY              0x00
/* Transmit Interrupt on Completion */
#define   TX_CTRL_INTERRUPT_ON       (0x8000)

#define REG_TX_CTRL                0x170       /* TXCR */
/* Enable ICMP frame checksum generation */
#define   TX_CTRL_ICMP_CHECKSUM      (1 << 8)
/* Enable UDP frame checksum generation */
#define   TX_CTRL_UDP_CHECKSUM       (1 << 7)
/* Enable TCP frame checksum generation */
#define   TX_CTRL_TCP_CHECKSUM       (1 << 6)
/* Enable IP frame checksum generation */
#define   TX_CTRL_IP_CHECKSUM        (1 << 5)
/* Clear transmit queue, reset tx frame pointer */
#define   TX_CTRL_FLUSH_QUEUE        (1 << 4)
/* Enable transmit flow control */
#define   TX_CTRL_FLOW_ENABLE        (1 << 3)
/* Eanble adding a padding to a packet shorter than 64 bytes */
#define   TX_CTRL_PAD_ENABLE         (1 << 2)
/* Enable adding a CRC to the end of transmit frame */
#define   TX_CTRL_CRC_ENABLE         (1 << 1)
/* Enable tranmsit */
#define   TX_CTRL_ENABLE             (1 << 0)
#if (0)
#define   DEFAULT_TX_CTRL	\
	(TX_CTRL_ICMP_CHECKSUM | TX_CTRL_UDP_CHECKSUM | \
	TX_CTRL_TCP_CHECKSUM | TX_CTRL_IP_CHECKSUM |  \
	TX_CTRL_FLOW_ENABLE | TX_CTRL_PAD_ENABLE |   \
	TX_CTRL_CRC_ENABLE)
#else
#define   DEFAULT_TX_CTRL	\
	(TX_CTRL_FLOW_ENABLE | TX_CTRL_PAD_ENABLE |   \
	TX_CTRL_CRC_ENABLE)
#endif

#define REG_TX_STATUS              0x172       /* TXSR */
/* Trnasmit late collision occurs */
#define   TX_STAT_LATE_COL           (1 << 13)
/* Tranmsit maximum collision is reached */
#define   TX_STAT_MAX_COL            (1 << 12)
/* Transmit frame ID mask */
#define   TX_FRAME_ID_MASK           (0x003F)
#define   TX_STAT_ERRORS             (TX_STAT_MAX_COL | TX_STAT_LATE_COL)

#define REG_RX_CTRL1               0x174       /* RXCR1 */
/* Clear receive queue, reset rx frame pointer */
#define   RX_CTRL_FLUSH_QUEUE        (1 << 15)
/* Enable UDP frame checksum verification */
#define   RX_CTRL_UDP_CHECKSUM       (1 << 14)
/* Enable TCP frame checksum verification */
#define   RX_CTRL_TCP_CHECKSUM       (1 << 13)
/* Enable IP frame checksum verification */
#define   RX_CTRL_IP_CHECKSUM        (1 << 12)
/* Receive with address that pass MAC address filtering */
#define   RX_CTRL_MAC_FILTER         (1 << 11)
/* Enable receive flow control */
#define   RX_CTRL_FLOW_ENABLE        (1 << 10)
/* Eanble receive CRC error frames */
#define   RX_CTRL_BAD_PACKET         (1 << 9)
/* Receive multicast frames that pass the CRC hash filtering */
#define   RX_CTRL_MULTICAST          (1 << 8)
/* Receive all the broadcast frames */
#define   RX_CTRL_BROADCAST          (1 << 7)
/* Receive all the multicast frames (including broadcast frames) */
#define   RX_CTRL_ALL_MULTICAST      (1 << 6)
/* Receive unicast frames that match the device MAC address */
#define   RX_CTRL_UNICAST            (1 << 5)
/* Receive all incoming frames, regardless of frame's DA */
#define   RX_CTRL_PROMISCUOUS        (1 << 4)
/* Receive with address check in inverse filtering mode */
#define   RX_CTRL_INVERSE_FILTER     (1 << 1)
/* Enable receive */
#define   RX_CTRL_ENABLE             (1 << 0)
#if (0) /* Promiscuous mode */
#define   DEFAULT_RX_CTRL1	\
	(RX_CTRL_UDP_CHECKSUM | RX_CTRL_TCP_CHECKSUM | \
	RX_CTRL_IP_CHECKSUM | RX_CTRL_PROMISCUOUS | \
	RX_CTRL_FLOW_ENABLE | RX_CTRL_BROADCAST | \
	RX_CTRL_ALL_MULTICAST | RX_CTRL_UNICAST)
#endif
#if (0)
#define   DEFAULT_RX_CTRL1	\
	(RX_CTRL_UDP_CHECKSUM | RX_CTRL_TCP_CHECKSUM | \
	RX_CTRL_IP_CHECKSUM | RX_CTRL_MAC_FILTER | \
	RX_CTRL_FLOW_ENABLE | RX_CTRL_BROADCAST | \
	RX_CTRL_ALL_MULTICAST | RX_CTRL_UNICAST)
#else
#define   DEFAULT_RX_CTRL1	\
	(RX_CTRL_MAC_FILTER | RX_CTRL_MULTICAST | RX_CTRL_PROMISCUOUS | \
	RX_CTRL_FLOW_ENABLE | RX_CTRL_BROADCAST | \
	RX_CTRL_ALL_MULTICAST | RX_CTRL_UNICAST)
#endif


#define REG_RX_CTRL2               0x176       /* RXCR2 */
/* SPI Receive data burst length - single frame */
#define   RX_SPI_BURST_FRAME         (0x0080)
/* SPI Receive data burst length - 32-byte */
#define   RX_SPI_BURST_32            (0x0060)
/* SPI Receive data burst length - 16-byte */
#define   RX_SPI_BURST_16            (0x0040)
/* SPI Receive data burst length - 8-byte */
#define   RX_SPI_BURST_8             (0x0020)
/* SPI Receive data burst length - 4-byte */
#define   RX_SPI_BURST_4             (0x0000)
/* Enable pause frame timer */
#define   RX_CTRL_PAUSE_TIMER        (1 << 8)
/* No checksum generation and verification if IPv6 UDP is fragment */
#define   RX_CTRL_IPV6_UDP_FRAG_PASS (1 << 4)
/* Receive pass IPv6 UDP frame with UDP checksum is zero */
#define   RX_CTRL_IPV6_UDP_ZERO_PASS (1 << 3)
/* Enable UDP Lite frame checksum generation and verification */
#define   RX_CTRL_UDP_LITE_CHECKSUM  (1 << 2)
/* Enable ICMP frame checksum verification */
#define   RX_CTRL_ICMP_CHECKSUM      (1 << 1)
/* Receive drop frame if the SA is same as device MAC address */
#define   RX_CTRL_BLOCK_MAC          (1 << 0)
#define   DEFAULT_RX_CTRL2	\
	(RX_CTRL_IPV6_UDP_FRAG_PASS | RX_CTRL_UDP_LITE_CHECKSUM | \
	RX_CTRL_ICMP_CHECKSUM | RX_CTRL_PAUSE_TIMER)


#define REG_TX_MEM_INFO            0x178       /* TXMIR */
/* The amount of memory available in TXQ */
#define   TX_MEM_AVAILABLE_MASK      (0x1FFF)

#define REG_RX_FHR_STATUS          0x17C       /* RXFHSR */
/* Frame in the receive packet memory is valid */
#define   RX_VALID                   (1 << 15)
/* ICMP checksum field doesn't match */
#define   RX_ICMP_ERROR              (1 << 13)
/* IP checksum field doesn't match */
#define   RX_IP_ERROR                (1 << 12)
/* TCP checksum field doesn't match */
#define   RX_TCP_ERROR               (1 << 11)
/* UDP checksum field doesn't match */
#define   RX_UDP_ERROR               (1 << 10)
/* Received frame is a broadcast frame */
#define   RX_BROADCAST               (1 << 7)
/* Received frame is a multicast frame */
#define   RX_MULTICAST               (1 << 6)
/* Received frame is a unicast frame */
#define   RX_UNICAST                 (1 << 5)
/* Received frame has runt error */
#define   RX_PHY_ERROR               (1 << 4)
/* Received frame is an Ethernet-type frame */
#define   RX_FRAME_ETHER             (1 << 3)
/* Received frame length exceeds max size 0f 2048 bytes */
#define   RX_TOO_LONG                (1 << 2)
/* Received frame was demaged by a collision */
#define   RX_RUNT_ERROR              (1 << 1)
/* Received frame has a CRC error */
#define   RX_BAD_CRC                 (1 << 0)
#define   RX_ERRORS		\
	(RX_BAD_CRC | RX_TOO_LONG | RX_RUNT_ERROR | RX_PHY_ERROR | \
	RX_ICMP_ERROR | RX_IP_ERROR | RX_TCP_ERROR | RX_UDP_ERROR)

#define REG_RX_FHR_BYTE_CNT        0x17E       /* RXFHBCR */
/* Received frame byte size mask */
#define   RX_BYTE_CNT_MASK           (0x0FFF)

#define REG_TXQ_CMD                0x180       /* TXQCR */
/* Enable enqueue tx frames from tx buffer automatically */
#define   TXQ_AUTO_ENQUEUE           (1 << 2)
/* Enable generate interrupt when tx memory is available */
#define   TXQ_MEM_AVAILABLE_INT      (1 << 1)
/* Enable enqueue tx frames one frame at a time */
#define   TXQ_ENQUEUE                (1 << 0)

#define REG_RXQ_CMD                0x182       /* RXQCR */
/* RX interrupt is occured by timer duration */
#define   RXQ_STAT_TIME_INT          (1 << 12)
/* RX interrupt is occured by byte count threshold */
#define   RXQ_STAT_BYTE_CNT_INT      (1 << 11)
/* RX interrupt is occured by frame count threshold */
#define   RXQ_STAT_FRAME_CNT_INT     (1 << 10)
/* Enable adding 2-byte before frame header for IP aligned with DWORD */
#define   RXQ_TWOBYTE_OFFSET         (1 << 9)
/* Enable RX interrupt by timer duration */
#define   RXQ_TIME_INT               (1 << 7)
/* Enable RX interrupt by byte count threshold */
#define   RXQ_BYTE_CNT_INT           (1 << 6)
/* Enable RX interrupt by frame count threshold */
#define   RXQ_FRAME_CNT_INT          (1 << 5)
/* Enable release rx frames from rx buffer automatically */
#define   RXQ_AUTO_DEQUEUE           (1 << 4)
/* Start QMU transfer operation */
#define   RXQ_START                  (1 << 3)
/* Manual dequeue (release the current frame from RxQ) */
#define   RXQ_CMD_FREE_PACKET        (1 << 0)
#if (0)
#define   RXQ_CMD_CNTL		(RXQ_FRAME_CNT_INT|RXQ_AUTO_DEQUEUE)
#endif
#if (1)
#define   RXQ_CMD_CNTL		\
	(RXQ_FRAME_CNT_INT|RXQ_TWOBYTE_OFFSET|RXQ_AUTO_DEQUEUE)
#endif

#define REG_TX_ADDR_PTR            0x184       /* TXFDPR */
#define REG_RX_ADDR_PTR            0x186       /* RXFDPR */
/* Enable Frame data pointer increments automatically */
#define   ADDR_PTR_AUTO_INC          (1 << 14)
/* 1: WRN active to write data valid sample time is 4ns */
#define   WRN_WRITE_4NS              (1 << 12)
/* Set device in Big Endian mode */
#define   BIG_ENDIAN_MODE            (1 << 11)

#define REG_RX_TIME_THRES          0x18C       /* RXDTTR */
/* Set receive timer duration threshold */
#define   RX_TIME_THRESHOLD_MASK     (0xFFFF)

#define REG_RX_BYTE_CNT_THRES      0x18E       /* RXDBCTR */
/* Set receive byte count threshold */
#define   RX_BYTE_THRESHOLD_MASK     (0xFFFF)

#define REG_INT_MASK               0x190       /* IER */
/* Enable link change interrupt */
#define   INT_PHY                    (1 << 15)
/* Enable transmit done interrupt */
#define   INT_TX_ETH                 (1 << 14)
/* Enable receive interrupt */
#define   INT_RX_ETH                 (1 << 13)
/* Enable timestamp event detection interrupt */
#define   INT_TIMESTAMP              (1 << 12)
/* Enable receive overrun interrupt */
#define   INT_RX_OVERRUN_ETH         (1 << 11)
/* Enable trigger outout interrupt */
#define   INT_TRIG_OUTPUT            (1 << 10)
/* Enable transmit process stopped interrupt */
#define   INT_TX_STOPPED_ETH         (1 << 9)
/* Enable receive process stopped interrupt */
#define   INT_RX_STOPPED_ETH         (1 << 8)
/* Enable transmit space available interrupt */
#define   INT_TX_SPACE               (1 << 6)
/* Enable WOL on receive wake-up frame detect interrupt */
#define   INT_RX_WOL_FRAME           (1 << 5)
/* Enable WOL on receive magic packet detect interrupt */
#define   INT_RX_WOL_MAGIC           (1 << 4)
/* Enable WOL on link up detect interrupt */
#define   INT_RX_WOL_LINKUP          (1 << 3)
/* Enable WOL on energy detect interrupt */
#define   INT_RX_WOL_ENERGY          (1 << 2)
/* Enable receive SPI bus error interrupt */
#define   INT_RX_SPI_ERROR           (1 << 1)
/* Enable delay generate WOL on energy detect */
#define   RX_WOL_DELAY_ENERGY        (1 << 0)
#define   INT_MASK                    (INT_RX | INT_TX | INT_PHY)

#define REG_INT_STATUS             0x192       /* ISR */

#define REG_RX_FRAME_CNT_THRES     0x19C       /* RXFCTFC */
/* Set receive frame count threshold mask */
#define   RX_FRAME_THRESHOLD_MASK    (0x00FF)

#define REG_TX_TOTAL_FRAME_SIZE    0x19E       /* TXNTFSR */
/* Set next total tx frame size mask */
#define   TX_TOTAL_FRAME_SIZE_MASK   (0xFFFF)


/* QMU MAC Address Hash Table Control Registers */

#define REG_MAC_HASH_0             0x1A0       /* MAHTR0 */
#define REG_MAC_HASH_1             0x1A1

#define REG_MAC_HASH_2             0x1A2       /* MAHTR1 */
#define REG_MAC_HASH_3             0x1A3

#define REG_MAC_HASH_4             0x1A4       /* MAHTR2 */
#define REG_MAC_HASH_5             0x1A5

#define REG_MAC_HASH_6             0x1A6       /* MAHTR3 */
#define REG_MAC_HASH_7             0x1A7


/* QMU Receive Queue Watermark Control Registers */

#define REG_RX_LOW_WATERMARK       0x1B0       /* FCLWR */
/* Set QMU RxQ low watermark mask */
#define   RX_LOW_WATERMARK_MASK      (0x0FFF)

#define REG_RX_HIGH_WATERMARK      0x1B2       /* FCHWR */
/* Set QMU RxQ high watermark mask */
#define   RX_HIGH_WATERMARK_MASK     (0x0FFF)

#define REG_RX_OVERRUN_WATERMARK   0x1B4       /* FCOWR */
/* Set QMU RxQ overrun watermark mask */
#define   RX_OVERRUN_WATERMARK_MASK  (0x0FFF)


/*
 * Switch Registers
 * (Bank 0, Offset 0 - 0x0ff)
 */

/* Switch Global Control registers  */

#define REG_SWITCH_SIDER           0x00        /* SIDER */
/* Enable switch */
#define   SWITCH_START               (1 << 0)
#define	  CIDER_ID_8463			(0x8440)
#define	  CIDER_ID_8463_RLI		(0x8450)
#define   CIDER_ID_MASK			(~0xf)

#define REG_SWITCH_CTRL_1          0x02        /* SGCR1 */
/* pass all frames */
#define   SWITCH_PASS_ALL            (1 << 15)
/* IEEE 802.3x tx flow control enable */
#define   SWITCH_TX_FLOW_CTRL        (1 << 13)
/* IEEE 802.3x rx flow control enable */
#define   SWITCH_RX_FLOW_CTRL        (1 << 12)
/* check frame length field in the IEEE pkts */
#define   SWITCH_CHECK_LENGTH        (1 << 11)
/* enable Aging */
#define   SWITCH_AGING_ENABLE        (1 << 10)
/* enable fast aging */
#define   SWITCH_FAST_AGING          (1 << 9)
/* enable aggressive back off */
#define   SWITCH_AGGR_BACKOFF        (1 << 8)
/* pass flow control pkts */
#define   SWITCH_PASS_PAUSE          (1 << 3)
/* port 3 in turbo-mii mode */
#define   SWITCH_PORT3_TURBO_MII     (1 << 2)
/* fast aging when from link up to down */
#define   SWITCH_LINK_AUTO_AGING     (1 << 0)

#define REG_SWITCH_CTRL_2          0x04        /* SGCR2 */
/* enable 802.1Q */
#define   SWITCH_VLAN_ENABLE         (1 << 15)
/* enable IGMP */
#define   SWITCH_IGMP_SNOOP          (1 << 14)
/* enable ipv6 MLD */
#define   SWITCH_IPV6_MLD_SNOOP      (1 << 13)
/* enable ipv6 MLD option */
#define   SWITCH_IPV6_MLD_OPTION     (1 << 12)
#if 0
/* always tx higher priority first */
#define   PRIORITY_SCHEME_SELECT     (1 << 11)
#endif
/* select rx AND tx sniff mode */
#define   SWITCH_MIRROR_RX_TX        (1 << 8)
/* all pkts can't cross VLAN boundary */
#define   UNICAST_VLAN_BOUNDARY      (1 << 7)
/* broadcast storm protection not include multicast pkt */
#define   MULTICAST_STORM_DISABLE    (1 << 6)
/* select carrier sense based backpressure */
#define   SWITCH_BACK_PRESSURE       (1 << 5)
/* select fair mode */
#define   FAIR_FLOW_CTRL             (1 << 4)
/* switch not drop pkts when more than 16 collision happen */
#define   NO_EXC_COLLISION_DROP      (1 << 3)
/* accept huge pkts - upto 1916 bytes */
#define   SWITCH_HUGE_PACKET         (1 << 2)
/* accept legal max pkt - uptp 1536 bytes */
#define   SWITCH_LEGAL_PACKET        (1 << 1)
/* each ports pre-allocated 48 buffers */
#define   SWITCH_BUF_RESERVE         (1 << 0)

#define REG_SWITCH_CTRL_3          0x06        /* SGCR3 */
/* enable switch host port in half duplex */
#define   SWITCH_HALF_DUPLEX         (1 << 6)
/* enable switch host port flow control */
#define   SWITCH_FLOW_CTRL           (1 << 5)
/* replace NULL VID with port VID */
#define   SWITCH_REPLACE_VID         (1 << 3)
/* Broadcast storm protection rate bit[7:0] mask */
#define   BROADCAST_STORM_RATE_LO    (0xFF00)
/* Broadcast storm protection rate bit[10:8] mask */
#define   BROADCAST_STORM_RATE_HI    (0x0007)

#define BROADCAST_STORM_RATE		0x07FF

#define REG_SWITCH_CTRL_4          0x08        /* SGCR4 */

#define REG_SWITCH_CTRL_6          0x0C        /* SGCR6 */
#define   SWITCH_802_1P_MAP_MASK      3
#define   SWITCH_802_1P_MAP_SHIFT     2

#define REG_SWITCH_CTRL_7          0x0E        /* SGCR7 */
/* enable tx unknow DA pkts to specified port */
#define   SWITCH_UNKNOWN_DA_ENABLE   (1 << 7)
/* Set driver strength to 16mA */
#define   SWITCH_DRIVER_16MA         (1 << 6)
/* Invert port 3 txc */
#define   SWITCH_PORT3_INVERT_TXC    (1 << 4)
/* tx unknow DA pkts to port3 */
#define   SWITCH_UNKNOWN_DA_2_PORT3  (1 << 2)
/* tx unknow DA pkts to port3 */
#define   SWITCH_UNKNOWN_DA_2_PORT2  (1 << 1)
/* tx unknow DA pkts to port3 */
#define   SWITCH_UNKNOWN_DA_2_PORT1  (1 << 0)

#define REG_SWITCH_MAC_ADDR_0      0x10        /* MACAR1 */
#define REG_SWITCH_MAC_ADDR_1      0x11
#define REG_SWITCH_MAC_ADDR_2      0x12        /* MACAR2 */
#define REG_SWITCH_MAC_ADDR_3      0x13
#define REG_SWITCH_MAC_ADDR_4      0x14        /* MACAR3 */
#define REG_SWITCH_MAC_ADDR_5      0x15


#define REG_TOS_PRIORITY_CTRL_1    0x16       /* TOSR1 */
#define REG_TOS_PRIORITY_CTRL_2    0x18       /* TOSR2 */
#define REG_TOS_PRIORITY_CTRL_3    0x1A       /* TOSR3 */
#define REG_TOS_PRIORITY_CTRL_4    0x1C       /* TOSR4 */
#define REG_TOS_PRIORITY_CTRL_5    0x1E       /* TOSR5 */
#define REG_TOS_PRIORITY_CTRL_6    0x20       /* TOSR6 */
#define REG_TOS_PRIORITY_CTRL_7    0x22       /* TOSR7 */
#define REG_TOS_PRIORITY_CTRL_8    0x24       /* TOSR8 */

#define REG_IND_DATA_1             0x26        /* IADR1 */
/* read is still in progress */
#define   TABLE_READ_NOT_COMPLETE    (1 << 7)

#define REG_IND_DATA_2             0x28        /* IADR2 */
#define REG_IND_DATA_3             0x2A        /* IADR3 */
#define REG_IND_DATA_4             0x2C        /* IADR4 */
#define REG_IND_DATA_5             0x2E        /* IADR5 */
/* MIB count overflow */
#define   MIB_COUNTER_OVERFLOW       (1 << 31)
/* MIB count value is valid */
#define   MIB_COUNTER_VALID          (1 << 30)
/* MIB count value mask */
#define   MIB_COUNTER_VALUE          (0x3FFFFFFF)
#ifndef MIB_COUNTER_PACKET_DROPPED
/* for pkt drop overflow */
#define   MIB_COUNTER_PACKET_DROPPED (0xFFFF)
#endif

/* Port 1 TX drop pkt MIB count address */
#define   MIB_COUNTER_PACKET_DROPPED_TX_0  0x100
/* Port 1 RX drop pkt MIB count address */
#define   MIB_COUNTER_PACKET_DROPPED_RX_0  0x103

#define REG_IND_IACR               0x30        /* IACR */
/* read operation */
#define   TABLE_READ                 (1 << 12)
/* access static MAC address table */
#define   TABLE_STATIC_MAC           (0 << 10)
/* access VLAN table */
#define   TABLE_VLAN                 (1 << 10)
/* access dynamic MAC address table */
#define   TABLE_DYNAMIC_MAC          (2 << 10)
/* access MIB count table */
#define   TABLE_MIB                  (3 << 10)
#define   TABLE_ENTRY_MASK           (0x03ff)


/* PHY 1 registers  */

#define PHY1_REG_CTRL               0x4C        /* P1MBCR */
#define PHY1_REG_STATUS             0x4E        /* P1MBSR */
#define PHY1_REG_ID_1               0x50        /* PHY1ILR */
#define PHY1_REG_ID_2               0x52        /* PHY1IHR */
#define PHY1_REG_AUTO_NEGOTIATION   0x54        /* P1ANAR */
#define PHY1_REG_REMOTE_CAPABILITY  0x56        /* P1ANLPR */

#ifndef PHY_REG_CTRL
#define PHY_REG_CTRL               0x4C        /* P1MBCR */
/* PHY soft reset */
#define   PHY_RESET                  (1 << 15)
/* phy loopback */
#define   PHY_LOOPBACK               (1 << 14)
/* force link speed to 100bt */
#define   PHY_SPEED_100MBIT          (1 << 13)
/* enable auto-nego */
#define   PHY_AUTO_NEG_ENABLE        (1 << 12)
/* phy power down */
#define   PHY_POWER_DOWN             (1 << 11)
/* isolate phy */
#define   PHY_MII_DISABLE            (1 << 10)
/* restart auto-nego */
#define   PHY_AUTO_NEG_RESTART       (1 << 9)
/* force link in full duplex mode */
#define   PHY_FULL_DUPLEX            (1 << 8)
/* test collision */
#define   PHY_COLLISION_TEST         (1 << 7)
/* enable HP auto MDIX mode */
#define   PHY_HP_MDIX                (1 << 5)
/* force MDIX mode */
#define   PHY_FORCE_MDIX             (1 << 4)
/* disable auto MDIX mode */
#define   PHY_AUTO_MDIX_DISABLE      (1 << 3)
/* disable far end fail detection */
#define   PHY_REMOTE_FAULT_DISABLE   (1 << 2)
/* disable tx */
#define   PHY_TRANSMIT_DISABLE       (1 << 1)
/* disable LED */
#define   PHY_LED_DISABLE            (1 << 0)

#define PHY_REG_STATUS             0x4E        /* P1MBSR */
/* T4 capable */
#define   PHY_100BT4_CAPABLE         (1 << 15)
/* 100BT full duplex capable */
#define   PHY_100BTX_FD_CAPABLE      (1 << 14)
/* 100BT half duplex capable */
#define   PHY_100BTX_CAPABLE         (1 << 13)
/* 10BT full duplex capable */
#define   PHY_10BT_FD_CAPABLE        (1 << 12)
/* 10BT half duplex capable */
#define   PHY_10BT_CAPABLE           (1 << 11)
/* preamble suppressed */
#define   PHY_MII_SUPPRESS_CAPABLE   (1 << 6)
/* auto-nego complete */
#define   PHY_AUTO_NEG_ACKNOWLEDGE   (1 << 5)
/* far end fault detected */
#define   PHY_REMOTE_FAULT           (1 << 4)
/* auto-nego capable */
#define   PHY_AUTO_NEG_CAPABLE       (1 << 3)
/* link is up */
#define   PHY_LINK_STATUS            (1 << 2)
/* Jabber test */
#define   PHY_JABBER_DETECT          (1 << 1)
/* extended capable */
#define   PHY_EXTENDED_CAPABILITY    (1 << 0)

#define PHY_REG_ID_1               0x50        /* PHY1ILR */
#define PHY_REG_ID_2               0x52        /* PHY1IHR */

#define PHY_REG_AUTO_NEGOTIATION   0x54        /* P1ANAR */
/* next page */
#define   PHY_AUTO_NEG_NEXT_PAGE     (1 << 15)
/* remote fault */
#define   PHY_AUTO_NEG_REMOTE_FAULT  (1 << 13)
/* advertise pause ability */
#define   PHY_AUTO_NEG_SYM_PAUSE     (1 << 10)
/* advertise 100 full */
#define   PHY_AUTO_NEG_100BTX_FD     (1 << 8)
/* advertise 100 half */
#define   PHY_AUTO_NEG_100BTX        (1 << 7)
/* advertise 10 full */
#define   PHY_AUTO_NEG_10BT_FD       (1 << 6)
/* advertise 10 half */
#define   PHY_AUTO_NEG_10BT          (1 << 5)
#define   PHY_AUTO_NEG_SELECTOR      (0x001F)
#define   PHY_AUTO_NEG_802_3         (0x0001)

#define PHY_REG_REMOTE_CAPABILITY  0x56        /* P1ANLPR */
/* remote next page */
#define   PHY_REMOTE_NEXT_PAGE       (1 << 15)
/* link partner pause capability */
#define   PHY_REMOTE_SYM_PAUSE       (1 << 10)
/* link partner 100 full capability */
#define   PHY_REMOTE_100BTX_FD       (1 << 8)
/* link partner 100 half capability */
#define   PHY_REMOTE_100BTX          (1 << 7)
/* link partner 10 full capability */
#define   PHY_REMOTE_10BT_FD         (1 << 6)
/* link partner 10 hal capability */
#define   PHY_REMOTE_10BT            (1 << 5)
#endif

/* PHY 2 registers  */

#define PHY2_REG_CTRL              (PHY1_REG_CTRL+0x0C)    /* P2MBCR */
#define PHY2_REG_STATUS            (PHY1_REG_STATUS+0x0C)  /* P2MBSR */
#define PHY2_REG_ID_1              (PHY1_REG_ID_1+0x0C)    /* PHY2ILR */
#define PHY2_REG_ID_2              (PHY1_REG_ID_2+0x0C)    /* PHY2IHR */
/* P2ANAR */
#define PHY2_REG_AUTO_NEGOTIATION  (PHY1_REG_AUTO_NEGOTIATION+0x0C)
/* P2ANLPR */
#define PHY2_REG_REMOTE_CAPABILITY (PHY1_REG_REMOTE_CAPABILITY+0x0C)

/* PHY 1 LinkMD registers  */

#define PHY_REG_LINK_MD            0x64        /* P1VCT */
/* start cable diag test */
#define   PHY_START_CABLE_DIAG       (1 << 15)
/* cable test result mask */
#define   PHY_CABLE_DIAG_RESULT      (0x6000)
/* cable is normal */
#define   PHY_CABLE_STAT_NORMAL      (0x0000)
/* cable is open */
#define   PHY_CABLE_STAT_OPEN        (0x2000)
/* cable is short */
#define   PHY_CABLE_STAT_SHORT       (0x4000)
/* cable test fail */
#define   PHY_CABLE_STAT_FAILED      (0x6000)
/* cable is less than 10 meter */
#define   PHY_CABLE_10M_SHORT        (1 << 12)
/* cable fail in distance count mask */
#define   PHY_CABLE_FAULT_COUNTER    (0x01FF)

#define PHY_REG_PHY_CTRL           0x66        /* P1PHYCTRL */
/* phy polarity reverse */
#define   PHY_STAT_REVERSED_POLARITY (1 << 5)
/* phy is in MDI mode */
#define   PHY_STAT_MDIX              (1 << 4)
/* force link pass */
#define   PHY_FORCE_LINK             (1 << 3)
/* enable phy power saving */
#define   PHY_POWER_SAVING_DISABLE   (1 << 2)
/* enable pyh remote loopback */
#define   PHY_REMOTE_LOOPBACK        (1 << 1)

/* PHY 2 LinkMD registers  */

#define PHY2_REG_LINK_MD           (PHY_REG_LINK_MD+0x04)    /* P2VCT */
#define PHY2_REG_PHY_CTRL          (PHY_REG_PHY_CTRL+0x04)   /* P2PHYCTRL */


/* Port 1 registers  */

#define REG_PORT1_CTRL1            0x6C        /* P1CR1 */
/* enable SA MAC2 */
#define   PORT_SA_MAC2               (1 << 11)
/* enable SA MAC1 */
#define   PORT_SA_MAC1               (1 << 10)
/* enable drop tagged ingress pkts */
#define   PORT_DROP_TAG_PKT          (1 << 9)
/* enable split port tx queue to two queues */
#define   PORT_SPLIT_2QUEUE          (1 << 8)
/* enable broadcast storm protection */
#define   PORT_BROADCAST_STORM       (1 << 7)
/* enable Diffserv QoS */
#define   PORT_DIFFSERV_ENABLE       (1 << 6)
/* enable 802.1p QoS */
#define   PORT_802_1P_ENABLE         (1 << 5)
/* port-base QoS mask */
#define   PORT_BASED_PRIORITY_MASK   (0x0018)
#define   PORT_BASED_PRIORITY_BASE   (0x03)
#define   PORT_BASED_PRIORITY_SHIFT  3
/* port-base priority queue 0 QoS */
#define   PORT_PORT_PRIORITY_0       (0x0000)
/* port-base priority queue 1 QoS */
#define   PORT_PORT_PRIORITY_1       (0x0008)
/* port-base priority queue 2 QoS */
#define   PORT_PORT_PRIORITY_2       (0x0010)
/* port-base priority queue 3 QoS */
#define   PORT_PORT_PRIORITY_3       (0x0018)
/* enable vlan tag insertion */
#define   PORT_INSERT_TAG            (1 << 2)
/* enable vlan tag removal */
#define   PORT_REMOVE_TAG            (1 << 1)
/* enable split port tx queue to four queues */
#define   PORT_PRIORITY_ENABLE       (1 << 0)

#define REG_PORT1_CTRL2            0x6E        /* P1CR2 */
/* remote loopback */
#define   PORT_REMOTE_LOOPBACK       (1 << 15)
/* VLAN ingress filtering */
#define   PORT_INGRESS_FILTER        (1 << 14)
/* discard pkts whose VID not match port default VID */
#define   PORT_DISCARD_NON_VID       (1 << 13)
/* force flow control */
#define   PORT_FORCE_FLOW_CTRL       (1 << 12)
/* enable back pressure */
#define   PORT_BACK_PRESSURE         (1 << 11)
/* enable tx */
#define   PORT_TX_ENABLE             (1 << 10)
/* enable rx */
#define   PORT_RX_ENABLE             (1 << 9)
/* disable learning */
#define   PORT_LEARN_DISABLE         (1 << 8)
/* select this port as sniffer port */
#define   PORT_MIRROR_SNIFFER        (1 << 7)
/* select this port as monitored rx pkts */
#define   PORT_MIRROR_RX             (1 << 6)
/* select this port as monitored tx pkts */
#define   PORT_MIRROR_TX             (1 << 5)
/* enable replace 802.1p priority field */
#define   PORT_802_1P_REMAPPING      (1 << 3)
/* Port VLAN membership mask */
#define   PORT_VLAN_MEMBERSHIP       (0x07)

#define REG_PORT_1_CTRL_VID        0x70        /* P1VIDCR */

#define REG_PORT1_CTRL3            0x72        /* P1CR3 */
/* Ingress rate limit mode mask */
#define   PORT_INGRESS_LIMIT_MODE    (0x0C)
/*  - limit all frames */
#define   PORT_INGRESS_ALL           (0x00)
/*  - limit broadcast, multicast, flooded unicast pkts */
#define   PORT_INGRESS_UNICAST       (0x04)
/*  - limit broadcast, multicast pkts only */
#define   PORT_INGRESS_MULTICAST     (0x08)
/*  - limit broadcast pkts only */
#define   PORT_INGRESS_BROADCAST     (0x0C)
/* rate limiting include IFG bytes */
#define   PORT_COUNT_IFG             (1 << 1)
/* rate limiting include preamble bytes */
#define   PORT_COUNT_PREAMBLE        (1 << 0)

#define REG_PORT_1_IN_RATE0        0x74        /* P1IRCR0 */
#define REG_PORT_1_IN_RATE1        0x76        /* P1IRCR1 */

#define REG_PORT_1_OUT_RATE0       0x78        /* P1ERCR0 */
/* enable port egress rate limit flow control */
#define   PORT_EGRESS_LIMIT_FLOW_EN  (1 << 7)

#define REG_PORT_1_OUT_RATE1       0x7A        /* P1ERCR1 */

#define REG_PORT_1_LINK_MD_CTRL    0x7C        /* P1SCSLMD */
/* cable less than 10 meter short */
#define   PORT_CABLE_10M_SHORT       (1 << 15)
/* cable test result mask */
#define   PORT_CABLE_DIAG_RESULT     (0x6000)
/* cable is normal */
#define   PORT_CABLE_STAT_NORMAL     (0x0000)
/* cable is open */
#define   PORT_CABLE_STAT_OPEN       (0x2000)
/* cable is short */
#define   PORT_CABLE_STAT_SHORT      (0x4000)
/* cable test fail */
#define   PORT_CABLE_STAT_FAILED     (0x6000)
/* enable cable diag test */
#define   PORT_START_CABLE_DIAG      (1 << 12)
/* force link pass */
#define   PORT_FORCE_LINK            (1 << 11)
/* enable phy power saving */
#define   PORT_POWER_SAVING          (1 << 10)
/* phy remote loopback */
#define   PORT_PHY_REMOTE_LOOPBACK   (1 << 9)
/* cable fail in distance count mask */
#define   PORT_CABLE_FAULT_COUNTER   (0x01FF)

#define REG_PORT_1_CTRL_4          0x7E        /* P1CR4 */
/* turn off all port's LEDs */
#define   PORT_LED_OFF               (1 << 15)
/* disable tx */
#define   PORT_TX_DISABLE            (1 << 14)
/* restart auto-nego */
#define   PORT_AUTO_NEG_RESTART      (1 << 13)
/* disable far end fail detection */
#define   PORT_REMOTE_FAULT_DISABLE  (1 << 12)
/* phy power down */
#define   PORT_POWER_DOWN            (1 << 11)
/* disable auto MDIX mode */
#define   PORT_AUTO_MDIX_DISABLE     (1 << 10)
/* force MDIX mode */
#define   PORT_FORCE_MDIX            (1 << 9)
/* phy loopback */
#define   PORT_LOOPBACK              (1 << 8)
/* enable auto-nego */
#define   PORT_AUTO_NEG_ENABLE       (1 << 7)
/* force link speed to 100bt */
#define   PORT_FORCE_100_MBIT        (1 << 6)
/* force link in full duplex mode */
#define   PORT_FORCE_FULL_DUPLEX     (1 << 5)
/* advertise pause ability */
#define   PORT_AUTO_NEG_SYM_PAUSE    (1 << 4)
/* advertise 100 full */
#define   PORT_AUTO_NEG_100BTX_FD    (1 << 3)
/* advertise 100 half */
#define   PORT_AUTO_NEG_100BTX       (1 << 2)
/* advertise 10 full */
#define   PORT_AUTO_NEG_10BT_FD      (1 << 1)
/* advertise 10 half */
#define   PORT_AUTO_NEG_10BT         (1 << 0)

#define REG_PORT_1_STATUS          0x80        /* P1SR */
/* enable HP auto MDIX mode */
#define   PORT_HP_MDIX               (1 << 15)
/* phy polarity reverse */
#define   PORT_REVERSED_POLARITY     (1 << 13)
/* tx flow control is active */
#define   PORT_RX_FLOW_CTRL          (1 << 12)
/* rx flow control is active */
#define   PORT_TX_FLOW_CTRL          (1 << 11)
/* link speed is in 100BT */
#define   PORT_STAT_SPEED_100MBIT    (1 << 10)
/* Link is in full duplex */
#define   PORT_STAT_FULL_DUPLEX      (1 << 9)
/* far end fault detected */
#define   PORT_REMOTE_FAULT          (1 << 8)
/* phy is in MDI mode */
#define   PORT_MDIX_STATUS           (1 << 7)
/* auto-nego complete */
#define   PORT_AUTO_NEG_COMPLETE     (1 << 6)
/* link is up */
#define   PORT_STATUS_LINK_GOOD      (1 << 5)
/* link partner pause capability */
#define   PORT_REMOTE_SYM_PAUSE      (1 << 4)
/* link partner 100 full capability */
#define   PORT_REMOTE_100BTX_FD      (1 << 3)
/* link partner 100 half capability */
#define   PORT_REMOTE_100BTX         (1 << 2)
/* link partner 10 full capability */
#define   PORT_REMOTE_10BT_FD        (1 << 1)
/* link partner 10 hal capability */
#define   PORT_REMOTE_10BT           (1 << 0)

/* Port 2 registers  */

#define REG_PORT2_CTRL1            (REG_PORT1_CTRL1 + 0x18)   /* P2CR1 */
#define REG_PORT2_CTRL2            (REG_PORT1_CTRL2 + 0x18)   /* P2CR2 */
#define REG_PORT_2_CTRL_VID        (REG_PORT_1_CTRL_VID+0x18) /* P2VIDCR */
#define REG_PORT2_CTRL3            (REG_PORT1_CTRL3 + 0x18)   /* P2CR3 */
#define REG_PORT_2_IN_RATE0        (REG_PORT_1_IN_RATE0+0x18) /* P2IRCR0 */
#define REG_PORT_2_IN_RATE1        (REG_PORT_1_IN_RATE1+0x18) /* P2IRCR1 */
#define REG_PORT_2_OUT_RATE0       (REG_PORT_1_OUT_RATE0+0x18)/* P2ERCR0 */
#define REG_PORT_2_OUT_RATE1       (REG_PORT_1_OUT_RATE1+0x18)/* P2ERCR1 */
#define REG_PORT_2_LINK_MD_CTRL    (REG_PORT_1_LINK_MD_CTRL+0x18) /* P2SCSLMD */
#define REG_PORT_2_CTRL_4          (REG_PORT_1_CTRL_4 + 0x18) /* P2CR4 */
#define REG_PORT_2_STATUS          (REG_PORT_1_STATUS + 0x18) /* P2SR */

/* Port 3 registers  */

#define REG_PORT3_CTRL1            (REG_PORT2_CTRL1 + 0x18)  /* P3CR1 */
#define REG_PORT3_CTRL2            (REG_PORT2_CTRL2 + 0x18)  /* P3CR2 */
#define REG_PORT3_CTRL3            (REG_PORT2_CTRL3 + 0x18)  /* P3CR3 */
#define REG_PORT_3_CTRL_VID        (REG_PORT_2_CTRL_VID+0x18) /* P3VIDCR */
#define REG_PORT3_CTRL3            (REG_PORT2_CTRL3 + 0x18)   /* P3CR3 */
#define REG_PORT_3_IN_RATE0        (REG_PORT_2_IN_RATE0+0x18) /* P3IRCR0 */
#define REG_PORT_3_IN_RATE1        (REG_PORT_2_IN_RATE1+0x18) /* P3IRCR1 */
#define REG_PORT_3_OUT_RATE0       (REG_PORT_2_OUT_RATE0+0x18)/* P3ERCR0 */
#define REG_PORT_3_OUT_RATE1       (REG_PORT_2_OUT_RATE1+0x18)/* P3ERCR1 */

#define REG_PORT_CTRL1			0x00
#define REG_PORT_CTRL2			0x02
#define REG_PORT_CTRL_VID		0x04
#define REG_PORT_CTRL3			0x06
#define REG_PORT_IN_RATE0		0x08
#define REG_PORT_IN_RATE1		0x0A
#define REG_PORT_OUT_RATE0		0x0C
#define REG_PORT_OUT_RATE1		0x0E
#define REG_PORT_LINK_MD_CTRL		0x10
#define REG_PORT_CTRL4			0x12
#define REG_PORT_STATUS			0x14

#define PORT_CTRL_ADDR(port, addr)		\
	(addr = REG_PORT1_CTRL1 + (port) *	\
		(REG_PORT2_CTRL1 - REG_PORT1_CTRL1))

/* More Switch Global Control registers  */

#define REG_SWITCH_CTRL_8          0xAC        /* SGCR8 */
#define   SWITCH_PRIORITY_MAP_MASK   3
#define   SWITCH_PRIORITY_MAP_SHIFT  14
#define   SWITCH_PRIORITY_3_HI       (0 << SWITCH_PRIORITY_MAP_SHIFT)
#define   SWITCH_PRIORITY_0_LO       (1 << SWITCH_PRIORITY_MAP_SHIFT)
#define   SWITCH_PRIORITY_SPLIT      (2 << SWITCH_PRIORITY_MAP_SHIFT)
/* Flush dynamic mac table */
#define   SWITCH_FLUSH_DYNA_MAC      (1 << 10)
/* Flush static mac table */
#define   SWITCH_FLUSH_STATIC_MAC    (1 << 9)
/* enable port 3 tail tag mode */
#define   SWITCH_TAIL_TAG_ENABLE     (1 << 8)

#define REG_SWITCH_CTRL_9          0xAE        /* SGCR9 */
/* forwarding invalid VID frames to port 3 */
#define   SWITCH_INVALID_VID_2_PORT3 (1 << 10)
/* forwarding invalid VID frames to port 2 */
#define   SWITCH_INVALID_VID_2_PORT2 (1 << 9)
/* forwarding invalid VID frames to port 1 */
#define   SWITCH_INVALID_VID_2_PORT1 (1 << 8)
/* enable insert vlan tag when untagged pkts from port 3 to port 2 */
#define   SWITCH_INS_TAG_2_1         (1 << 5)
/* enable insert vlan tag when untagged pkts from port 3 to port 1 */
#define   SWITCH_INS_TAG_2_0         (1 << 4)
/* enable insert vlan tag when untagged pkts from port 2 to port 3 */
#define   SWITCH_INS_TAG_1_2         (1 << 3)
/* enable insert vlan tag when untagged pkts from port 2 to port 1 */
#define   SWITCH_INS_TAG_1_0         (1 << 2)
/* enable insert vlan tag when untagged pkts from port 2 to port 3 */
#define   SWITCH_INS_TAG_0_2         (1 << 1)
/* enable insert vlan tag when untagged pkts from port 1 to port 2 */
#define   SWITCH_INS_TAG_0_1         (1 << 0)


#define REG_SA_FILTER_MAC1_L       0xB0        /* SAFMACA1L */
#define REG_SA_FILTER_MAC1_M       0xB2        /* SAFMACA1M */
#define REG_SA_FILTER_MAC1_H       0xB4        /* SAFMACA1H */

#define REG_SA_FILTER_MAC2_L       0xB6        /* SAFMACA2L */
#define REG_SA_FILTER_MAC2_M       0xB8        /* SAFMACA2M */
#define REG_SA_FILTER_MAC2_H       0xBA        /* SAFMACA2H */


/* more Ports registers  */

#define REG_PORT1_TXQ_RATE_CTRL1   0xC8        /* P1TXQRCR1 */
/* tx highest priority before lower priority pkts for TX queue 2 */
#define   PORT_TXQ2_HIGH_PRIORITY    (1 << 15)
/* tx highest priority before lower priority pkts for TX queue 1 */
#define   PORT_TXQ1_HIGH_PRIORITY    (1 << 7)

#define REG_PORT1_TXQ_RATE_CTRL2   0xCA        /* P1TXQRCR2 */
/* tx highest priority before lower priority pkts for TX queue 4 */
#define   PORT_TXQ4_HIGH_PRIORITY    (1 << 15)
/* tx highest priority before lower priority pkts for TX queue 3 */
#define   PORT_TXQ3_HIGH_PRIORITY    (1 << 7)

/* P2TXQRCR1 */
#define REG_PORT2_TXQ_RATE_CTRL1   (REG_PORT1_TXQ_RATE_CTRL1 + 0x04)
/* P2TXQRCR2 */
#define REG_PORT2_TXQ_RATE_CTRL2   (REG_PORT1_TXQ_RATE_CTRL2 + 0x04)

/* P3TXQRCR1 */
#define REG_PORT3_TXQ_RATE_CTRL1   (REG_PORT2_TXQ_RATE_CTRL1 + 0x04)
/* P3TXQRCR2 */
#define REG_PORT3_TXQ_RATE_CTRL2   (REG_PORT2_TXQ_RATE_CTRL2 + 0x04)

#define RATE_CTRL_ENABLE	(1 << 7)
#define RATE_RATIO_MASK		0x7f


#define REG_IO_MUX_CTRL            0xD6        /* IOMXSEL */
/* 1 as P2LED1; 0 as GPIO9 for KS8463MLL/KS8441HLL */
#define   IO_SEL_P2LED1             (1 << 10)
/* 1 as P2LED0; 0 as GPIO10 for KS8463MLL */
#define   IO_SEL_P2LED0             (1 << 9)
/* 1 as P1LED1; 0 as GPIO7  for KS8463MLL */
#define   IO_SEL_P1LED1             (1 << 8)
/* 1 as EESK; 0 as GPIO5 for KS8462SNL */
#define   IO_SEL_EESK_SNL_2PORT     (1 << 7)
/* 1 as EESK; 0 as GPIO0 for KS8441SNL */
#define   IO_SEL_EESK_SNL_1PORT     (1 << 6)
/* 1 as EESK; 0 as GPIO3 for KS8462HLL/KS8441HLL */
#define   IO_SEL_EESK_HLL           (1 << 5)
/* 1 as EEDIO; 0 as GPIO6 for KS8462SNL */
#define   IO_SEL_EEDIO_SNL_2PORT    (1 << 4)
/* 1 as EEDIO; 0 as GPIO1 for KS8441SNL */
#define   IO_SEL_EEDIO_SNL_1PORT    (1 << 3)
/* 1 as EEDIO; 0 as GPIO4 for KS8462HLL/KS8441HLL */
#define   IO_SEL_EEDIO_HLL          (1 << 2)
/* 1 as EECS; 0 as GPIO5 for KS8462HLL/KS8441HLL */
#define   IO_SEL_EECS_HLL           (1 << 1)
/* 1 as EECS; 0 as GPIO4 for KS8462SNL/KS8441SNL */
#define   IO_SEL_EECS_SNL           (1 << 0)

#define REG_CFG_CTRL			0xD8
#define PORT_2_COPPER_MODE		(1 << 7)
#define PORT_1_COPPER_MODE		(1 << 6)
#define PORT_COPPER_MODE_S		6

#define REG_PCS_EEE_CTRL		0xF3
#define PORT_2_NEXT_PAGE_ENABLE		(1 << 1)
#define PORT_1_NEXT_PAGE_ENABLE		(1 << 0)

#endif

/* END */
