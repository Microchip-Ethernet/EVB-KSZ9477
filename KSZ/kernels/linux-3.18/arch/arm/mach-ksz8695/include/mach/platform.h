/*
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
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#ifndef __address_h
#define __address_h                     1


#define KS8695_SDRAM_START	    0x00000000
#if defined(CONFIG_ARCH_KS8695P) || defined (CONFIG_ARCH_KS8695PM)
  #define KS8695_SDRAM_SIZE         0x02000000      /*32MB on board SDRAM, can be overwritten by kernel parameter */
#elif defined(CONFIG_ARCH_KS8695MB)
  #define KS8695_SDRAM_SIZE         0x03000000      /*48MB on board SDRAM, can be overwritten by kernel parameter */
#elif defined(CONFIG_ARCH_KS8695X) || defined(CONFIG_ARCH_KS8695)
  #define KS8695_SDRAM_SIZE         0x01000000      /*16MB on board SDRAM, can be overwritten by kernel parameter */
#elif defined(CONFIG_ARCH_KS8695V)
  #define KS8695_SDRAM_SIZE         0x01000000      /*16MB on board SDRAM, can be overwritten by kernel parameter */
#elif defined(CONFIG_ARCH_KS8695L)
  #define KS8695_SDRAM_SIZE         0x00800000      /*8MB on board SDRAM,and can be overwritten by kernel parameter */
#endif

#define KS8695_MEM_SIZE             KS8695_SDRAM_SIZE
#define KS8695_MEM_START            KS8695_SDRAM_START

#define KS8695_IO_BASE              0x03FF0000
#define KS8695_IO_SIZE              0x00010000

#define KS8695_VIO_BASE             0xF03FF000

#define KS8695_SYSTEN_CONFIG  	    0x00
#define KS8695_SYSTEN_BUS_CLOCK     0x04

#ifdef CONFIG_ARCH_KS8695MB
 #define KS8695_FLASH_START         0x03000000  /* flash starts from 0x03000000 */
 #define KS8695_FLASH_SIZE          0x00C00000  /* size */
 #define KS8695_EXTIO_BASE          0x03C00000  /* external io range, in this case, each bank can only be 1MB at max */
 #define KS8695_EXTIO_SIZE          0x00300000

#else
 #define KS8695_EXTIO_BASE          0x03200000 /* normal case is external io starts from 0x03200000 and each bank be 4MB */
 #define KS8695_EXTIO_SIZE          0x00C00000 /* total size */

#ifdef CONFIG_U_BOOT_LOADER
 #define KS8695_FLASH_START         0x02000000 /* flash starts from 0x02000000 */
#else
 #define KS8695_FLASH_START         0x02800000 /* flash starts from 0x02800000 */
#endif
#if defined( CONFIG_KS8695M )
#define KS8695_FLASH_SIZE           0x00800000

#elif defined( CONFIG_KS8695P )
#define KS8695_FLASH_SIZE           0x00400000

#else
#define KS8695_FLASH_SIZE           0x00400000
#endif
#endif

#ifdef CONFIG_ARCH_KS8695
 #define KS8695_PCMCIA_IO_BASE       0x03800000  /* for PCMCIA (KS8695 only) */
 #define KS8695_PCMCIA_IO_SIZE       0x00040000
#endif

/* PCI memory related defines */
#define KS8695P_PCIBG_MEM_BASE      0x10000000  /* memory base for bridge */
#define KS8695P_PCIBG_MEM_SIZE      0x04000000  /* 64M */
#define KS8695P_PCI_MEM_BASE        0x10000000  /* memory base in PCI space */
#define KS8695P_PCI_MEM_SIZE        0x08000000  /* 128M, can be extended to 512M */
#define KS8695P_PCI_MEM_MASK        0xF8000000  /* 128M */

/* PCI IO related defines */
#define KS8695P_PCIBG_IO_BASE       0x08000000  /* io base for bridge */
#define KS8695P_PCI_IO_BASE         0x08000000
#define KS8695P_PCI_IO_SIZE         0x00010000      /* 64K */
#define KS8695P_PCI_IO_MASK         0xFFFF0000      /* 64K range */

/* new registers specific to KS8695P */
/* PCI related */
#define	KS8695_CRCFID		0x2000
#define	KS8695_2000		0x2000
#define	KS8695_CRCFCS		0x2004
#define	KS8695_2004		0x2004
#define	KS8695_CRCFRV		0x2008
#define	KS8695_2008		0x2008
#define	KS8695_CRCFLT		0x200c
#define	KS8695_200C		0x200c
#define	KS8695_CRCBMA		0x2010
#define	KS8695_2010		0x2010
#define	KS8695_CRCBA0		0x2014
#define	KS8695_2014		0x2014

#define	KS8695_CRCSID		0x202c
#define	KS8695_202C		0x202c

#define	KS8695_CRCFIT		0x203c
#define	KS8695_203C		0x203c

/* note that PCI configuration bits are defined in pci.h already */

/* bridge configuration related registers */
#define	KS8695_PBCA		0x2100
#define	KS8695_2100		0x2100
#define	KS8695_PBCD		0x2104
#define	KS8695_2104		0x2104

/* bridge mode related registers */
#define	KS8695_PBM		0x2200
#define	KS8695_2200		0x2200
#define	KS8695_PBCS		0x2204
#define	KS8695_2204		0x2204
#define	KS8695_PMBA		0x2208
#define	KS8695_2208		0x2208
#define	KS8695_PMBAC		0x220c
#define	KS8695_220C		0x220c
#define	KS8695_PMBAM		0x2210
#define	KS8695_2210		0x2210
#define	KS8695_PMBAT		0x2214
#define	KS8695_2214		0x2214
#define	KS8695_PIOBA		0x2218
#define	KS8695_2218		0x2218
#define	KS8695_PIOBAC		0x221c
#define	KS8695_221C		0x221c
#define	KS8695_PIOBAM		0x2220
#define	KS8695_2220		0x2220
#define	KS8695_PIOBAT		0x2224
#define	KS8695_2224		0x2224

/* bits for registers */
/* 0x2200 */
#define	PBM_BRIDGE_MODE		0x80000000

/* 0x2204 */
#define	PBCS_SW_RESET		0x80000000

/* 0x220c */
#define	PMBAC_TRANS_ENABLE	0x80000000

/*i/o control registers offset definitions*/
#define KS8695_IO_CTRL0             0x4000
#define KS8695_IO_CTRL1             0x4004
#define KS8695_IO_CTRL2             0x4008
#define KS8695_IO_CTRL3             0x400C

/*memory control registers offset definitions*/
#define KS8695_MEM_CTRL0            0x4010
#define KS8695_MEM_CTRL1            0x4014
#define KS8695_MEM_CTRL2            0x4018
#define KS8695_MEM_CTRL3            0x401C
#define KS8695_MEM_GENERAL          0x4020
#define KS8695_SDRAM_CTRL0          0x4030 
#define KS8695_SDRAM_CTRL1          0x4034
#define KS8695_SDRAM_GENERAL        0x4038
#define KS8695_SDRAM_BUFFER         0x403C
#define KS8695_SDRAM_REFRESH        0x4040    

/*WAN control registers offset definitions*/
#define KS8695_WAN_DMA_TX           0x6000
#define KS8695_WAN_DMA_RX           0x6004
#define KS8695_WAN_DMA_TX_START     0x6008    
#define KS8695_WAN_DMA_RX_START     0x600C    
#define KS8695_WAN_TX_LIST          0x6010
#define KS8695_WAN_RX_LIST          0x6014
#define KS8695_WAN_MAC_LOW          0x6018
#define KS8695_WAN_MAC_HIGH         0x601C
#define KS8695_WAN_MAC_ELOW         0x6080
#define KS8695_WAN_MAC_EHIGH        0x6084

/*LAN control registers offset definitions*/
#define KS8695_LAN_DMA_TX           0x8000
#define KS8695_LAN_DMA_RX           0x8004
#define KS8695_LAN_DMA_TX_START     0x8008    
#define KS8695_LAN_DMA_RX_START     0x800C    
#define KS8695_LAN_TX_LIST          0x8010
#define KS8695_LAN_RX_LIST          0x8014
#define KS8695_LAN_MAC_LOW          0x8018
#define KS8695_LAN_MAC_HIGH         0x801C
#define KS8695_LAN_MAC_ELOW         0X8080
#define KS8695_LAN_MAC_EHIGH        0X8084

/*HPNA control registers offset definitions*/
#ifdef CONFIG_ARCH_KS8695
 #define KS8695_HPNA_DMA_TX          0xA000
 #define KS8695_HPNA_DMA_RX          0xA004
 #define KS8695_HPNA_DMA_TX_START    0xA008    
 #define KS8695_HPNA_DMA_RX_START    0xA00C    
 #define KS8695_HPNA_TX_LIST         0xA010
 #define KS8695_HPNA_RX_LIST         0xA014
 #define KS8695_HPNA_MAC_LOW         0xA018
 #define KS8695_HPNA_MAC_HIGH        0xA01C
 #define KS8695_HPNA_MAC_ELOW        0xA080
 #define KS8695_HPNA_MAC_EHIGH       0xA084
#endif

/*UART control registers offset definitions*/
#define KS_UART_RX_BUFFER           0xE000
#define KS_UART_TX_HOLDING          0xE004
#define KS_UART_FIFO_CTRL           0xE008
#define KS_UART_LINE_CTRL           0xE00C
#define KS_UART_MODEM_CTRL          0xE010
#define KS_UART_LINE_STATUS         0xE014
#define KS_UART_MODEM_STATUS        0xE018
#define KS_UART_DIVISOR             0xE01C
#define KS_UART_STATUS              0xE020

#define KS8695_UART_RX_BUFFER       0xE000
#define KS8695_UART_TX_HOLDING      0xE004

#define KS8695_UART_FIFO_CTRL       0xE008
#define KS8695_UART_FIFO_TRIG01     0x00
#define KS8695_UART_FIFO_TRIG04     0x80
#define KS8695_UART_FIFO_TXRST      0x04
#define KS8695_UART_FIFO_RXRST      0x02
#define KS8695_UART_FIFO_FEN        0x01

#define KS8695_UART_LINE_CTRL       0xE00C
#define KS8695_UART_LINEC_BRK       0x40
#define KS8695_UART_LINEC_EPS       0x10
#define KS8695_UART_LINEC_PEN       0x08
#define KS8695_UART_LINEC_STP2      0x04
#define KS8695_UART_LINEC_WLEN8     0x03
#define KS8695_UART_LINEC_WLEN7     0x02
#define KS8695_UART_LINEC_WLEN6     0x01
#define KS8695_UART_LINEC_WLEN5     0x00

#define KS8695_UART_MODEM_CTRL      0xE010
#define KS8695_UART_MODEMC_RTS      0x02
#define KS8695_UART_MODEMC_DTR      0x01

#define KS8695_UART_LINE_STATUS     0xE014
#define KS8695_UART_LINES_TXE       0x40
#define KS8695_UART_LINES_TXFE      0x20
#define KS8695_UART_LINES_BE        0x10
#define KS8695_UART_LINES_FE        0x08
#define KS8695_UART_LINES_PE        0x04
#define KS8695_UART_LINES_OE        0x02
#define KS8695_UART_LINES_RXFE      0x01
#define KS8695_UART_LINES_ANY	    (KS8695_UART_LINES_OE|KS8695_UART_LINES_BE|KS8695_UART_LINES_PE|KS8695_UART_LINES_FE)

#define KS8695_UART_MODEM_STATUS    0xE018
#define KS8695_UART_MODEM_DCD       0x80
#define KS8695_UART_MODEM_DSR       0x20
#define KS8695_UART_MODEM_CTS       0x10
#define KS8695_UART_MODEM_DDCD      0x08
#define KS8695_UART_MODEM_DDSR      0x02
#define KS8695_UART_MODEM_DCTS      0x01
#define UART8695_MODEM_ANY	    0xFF

#define KS8695_UART_DIVISOR         0xE01C
#define KS8695_UART_STATUS          0xE020

/*Interrupt controller registers offset definitions*/
#define KS8695_INT_CONTL            0xE200
#define KS8695_INT_ENABLE           0xE204
#define KS8695_INT_ENABLE_MODEM     0x0800
#define KS8695_INT_ENABLE_RX        0x0200
#define KS8695_INT_ENABLE_TX        0x0100

#define KS8695_INT_STATUS           0xE208
#define KS8695_INT_WAN_PRIORITY     0xE20C
#define KS8695_INT_HPNA_PRIORITY    0xE210
#define KS8695_INT_LAN_PRIORITY     0xE214
#define KS8695_INT_TIMER_PRIORITY   0xE218
#define KS8695_INT_UART_PRIORITY    0xE21C
#define KS8695_INT_EXT_PRIORITY     0xE220
#define KS8695_INT_CHAN_PRIORITY    0xE224
#define KS8695_INT_BUSERROR_PRO     0xE228
#define KS8695_INT_MASK_STATUS      0xE22C
#define KS8695_FIQ_PEND_PRIORITY    0xE230
#define KS8695_IRQ_PEND_PRIORITY    0xE234

/*timer registers offset definitions*/
#define KS8695_TIMER_CTRL           0xE400
#define KS8695_TIMER1               0xE404
#define KS8695_TIMER0               0xE408
#define KS8695_TIMER1_PCOUNT        0xE40C
#define KS8695_TIMER0_PCOUNT        0xE410

/*GPIO registers offset definitions*/
#define KS8695_GPIO_MODE            0xE600
#define KS8695_GPIO_CTRL            0xE604
#define KS8695_GPIO_DATA            0xE608

/*SWITCH registers offset definitions*/
#define KS8695_SWITCH_CTRL0         0xE800
#define KS8695_SWITCH_CTRL1         0xE804
#define KS8695_SWITCH_PORT1         0xE808
#define KS8695_SWITCH_PORT2         0xE80C
#define KS8695_SWITCH_PORT3         0xE810
#define KS8695_SWITCH_PORT4         0xE814
#define KS8695_SWITCH_PORT5         0xE818
#define KS8695_SWITCH_AUTO0         0xE81C
#define KS8695_SWITCH_AUTO1         0xE820
#define KS8695_SWITCH_LUE_CTRL      0xE824
#define KS8695_SWITCH_LUE_HIGH      0xE828
#define KS8695_SWITCH_LUE_LOW       0xE82C
#define KS8695_SWITCH_ADVANCED      0xE830

/*host communication registers definitions*/
#define KS8695_DSCP_HIGH            0xE834
#define KS8695_DSCP_LOW             0xE838
#define KS8695_SWITCH_MAC_HIGH      0xE83C
#define KS8695_SWITCH_MAC_LOW       0xE840

/*miscellaneous registers definitions*/
#define KS8695_MANAGE_COUNTER       0xE844
#define KS8695_MANAGE_DATA          0xE848
#define KS8695_LAN12_POWERMAGR      0xE84C
#define KS8695_LAN34_POWERMAGR      0xE850

#define KS8695_DEVICE_ID            0xEA00
#define KS8695_REVISION_ID          0xEA04

#define KS8695_MISC_CONTROL         0xEA08
#define KS8695_WAN_CONTROL          0xEA0C
#define KS8695_WAN_POWERMAGR        0xEA10
#define KS8695_WAN_PHY_CONTROL      0xEA14
#define KS8695_WAN_PHY_STATUS       0xEA18

#ifdef CONFIG_KS8695P
/* most bit definition are same as KS8695, except few new bits */
#define KS8695_SEC0			0xE800
#define KS8695_E800			0xE800

/* new bits */
#define	KS8695_SEC0_BACKOFF_EN		0x80000000	/* new backoff enable for UNH, bit 31 */
#define	KS8695_SEC0_FRAME_LEN_CHECK	0x00020000	/* frame length field check, bit 17 */
#define	KS8695_SEC0_DMA_HALF_DUPLEX	0x00000010	/* LAN DMA port 5 half duplex mode bit 4 */

#define KS8695_SEC1			0xE804
#define KS8695_E804			0xE804

/* new bits */
#define	KS8695_SEC1_NO_IEEE_AN		0x00000800	/* non IEEE specific auto-nego bit 11 */
#define	KS8695_SEC1_TPID_MODE		0x00000400	/* Special TPID mode bit 10 */
#define	KS8695_SEC1_NO_TX_8021X_FLOW_CTRL	0x00000080	/* IEEE 802.1x transmit flow control disable bit 7 */
#define	KS8695_SEC1_NO_RX_8021X_FLOW_CTRL	0x00000040	/* IEEE 802.1x receive flow control disable bit 6 */
#define	KS8695_SEC1_HUGE_PACKET		0x00000020	/* huge packet support bit 5 */
#define	KS8695_SEC1_8021Q_VLAN_EN	0x00000010	/* IEEE 802.1q VLAN enable bit 4 */
#define	KS8695_SEC1_MII_10BT		0x00000002	/* Switch MII 10BT bit 1 */
#define	KS8695_SEC1_NULL_VID		0x00000001	/* null VID replacement bit 0 */

/* Port 1-4 and 5 Configuration Register Set 1 */
/* bit definition is same as KS8695 */
#define KS8695_SEP1C1			0xE80C
#define KS8695_E80C			0xE80C
#define KS8695_SEP2C1			0xE818
#define KS8695_E818			0xE818
#define KS8695_SEP3C1			0xE824
#define KS8695_E824			0xE824
#define KS8695_SEP4C1			0xE830
#define KS8695_E830			0xE830
#define KS8695_SEP5C1			0xE83C
#define KS8695_E83C			0xE83C

/* Port 1-4 and 5 Configuration Register Set 2 */
#define KS8695_SEP1C2			0xE810
#define KS8695_E810			0xE810
#define KS8695_SEP2C2			0xE81C
#define KS8695_E81C			0xE81C
#define KS8695_SEP3C2			0xE828
#define KS8695_E828			0xE828
#define KS8695_SEP4C2			0xE834
#define KS8695_E834			0xE834
#define KS8695_SEP5C2			0xE840
#define KS8695_E840			0xE840

#define	KS8695_SEPC2_VLAN_FILTER	0x10000000	/* Ingress VLAN filtering bit 28 */
#define	KS8695_SEPC2_DISCARD_NON_PVID	0x08000000	/* discard non PVID packets, bit 27 */
#define	KS8695_SEPC2_FORCE_FLOW_CTRL	0x04000000	/* force flow control, bit 26 */
#define	KS8695_SEPC2_BACK_PRESSURE_EN	0x02000000	/* back pressure enable, bit 25 */

#define	KS8695_SEPC2_TX_H_RATECTRL_MASK	0x00FFF000	/* Tx high priority rate control bit 23:12 */
#define	KS8695_SEPC2_TX_L_RATECTRL_MASK	0x00000FFF	/* Tx low priority rate control bit 11:0 */

/* Port 1-4 and 5 Configuration Register Set 3 */
#define KS8695_SEP1C3			0xE814
#define KS8695_E814			0xE814
#define KS8695_SEP2C3			0xE820
#define KS8695_E820			0xE820
#define KS8695_SEP3C3			0xE82C
#define KS8695_E82C			0xE82C
#define KS8695_SEP4C3			0xE838
#define KS8695_E838			0xE838
#define KS8695_SEP5C3			0xE844
#define KS8695_E844			0xE844

#define	KS8695_SEPC3_RX_H_RATECTRL_MASK	0xFFF00000	/* Rx high priority rate control bit 31:20 */
#define	KS8695_SEPC3_RX_L_RATECTRL_MASK	0x000FFF00	/* Rx low priority rate control bit 19:8 */
#define	KS8695_SEPC3_RX_DIF_RATECTRL_EN	0x00000080	/* Rx differential priority rate control enable bit 7 */
#define	KS8695_SEPC3_RX_L_RATECTRL_EN	0x00000040	/* Rx low priority rate control enable bit 6 */
#define	KS8695_SEPC3_RX_H_RATECTRL_EN	0x00000020	/* Rx high priority rate control enable bit 5 */
#define	KS8695_SEPC3_RX_L_RATEFLOW_EN	0x00000010	/* Rx low priority rate flow control enable bit 4 */
#define	KS8695_SEPC3_RX_H_RATEFLOW_EN	0x00000008	/* Rx high priority rate flow control enable bit 3 */
#define	KS8695_SEPC3_TX_DIF_RATECTRL_EN	0x00000004	/* Tx low priority rate control enable bit 2 */
#define	KS8695_SEPC3_TX_L_RATECTRL_EN	0x00000002	/* Tx low priority rate control enable bit 1 */
#define	KS8695_SEPC3_TX_H_RATECTRL_EN	0x00000001	/* Tx high priority rate control enable bit 0 */

/* Port auto negotiation related registers */
/* bit definition is same as KS8695 */
#define KS8695_SEP12AN			0xE848
#define KS8695_E848			0xE848
#define KS8695_SEP34AN			0xE84C
#define KS8695_E84C			0xE84C

/* backward compatible */
#undef KS8695_SWITCH_AUTO0
#undef KS8695_SWITCH_AUTO1
#define KS8695_SWITCH_AUTO0		0xE848
#define KS8695_SWITCH_AUTO1		0xE84C

/* Indirect Access Control register */
#define KS8695_SEIAC			0xE850
#define KS8695_E850			0xE850
#define KS8695_SEIADH2			0xE854
#define KS8695_E854			0xE854
#define KS8695_SEIADH1			0xE858
#define KS8695_E858			0xE858
#define KS8695_SEIADL			0xE85C
#define KS8695_E85C			0xE85C

#define	KS8695_SEIAC_READ		0x00001000	/* bit 12 */
#define	KS8695_SEIAC_WRITE		0x00000000	/* bit 12 not set*/
/* table select bit 11:10 */
#define	KS8695_SEIAC_TAB_STATIC		0x00000000
#define	KS8695_SEIAC_TAB_VLAN		0x00000400
#define	KS8695_SEIAC_TAB_DYNAMIC	0x00000800
#define	KS8695_SEIAC_TAB_MIB		0x00000C00
#define	KS8695_SEIAC_INDEX_MASK		0x000003FF	/* bit 9:0 */

/* Advanced Feature Control register */
/* bit definition is same as KS8695 */
#define KS8695_SEAFC			0xE860
#define KS8695_SEDSCPH			0xE864
#define KS8695_SEDSCPL			0xE868
#define KS8695_SEMAH			0xE86C
#define KS8695_SEMAL			0xE870

/* backward compatible */
#undef	KS8695_SWITCH_ADVANCED
#undef	KS8695_DSCP_HIGH
#undef	KS8695_DSCP_LOW
#undef	KS8695_SWITCH_MAC_HIGH
#undef	KS8695_SWITCH_MAC_LOW

#define KS8695_SWITCH_ADVANCED		0xE860
#define KS8695_DSCP_HIGH		0xE864
#define KS8695_DSCP_LOW			0xE868
#define KS8695_SWITCH_MAC_HIGH		0xE86C
#define KS8695_SWITCH_MAC_LOW		0xE870

/* LAN PHY power management related registers */
/* bit definition is same as KS8695, except new bits 30:26 */
#define KS8695_LPPM12			0xE874
#define KS8695_LPPM34			0xE878

/* new bits */
#define	KS8695_LPPM_PHY_LOOPBACK	0x4000	/* phy loopback bit 14 */
#define	KS8695_LPPM_RMT_LOOPBACK	0x2000	/* remote loopback bit 13 */
#define	KS8695_LPPM_PHY_ISOLATE		0x1000	/* phy isolate bit 12 */
#define	KS8695_LPPM_SOFT_RESET		0x0800	/* phy isolate bit 11 */
#define	KS8695_LPPM_FORCE_LINK		0x0400	/* force link isolationi bit 10 */
/* shift bit defined already */

/* backward compatible */
#undef	KS8695_LAN12_POWERMAGR
#undef	KS8695_LAN34_POWERMAGR
#define KS8695_LAN12_POWERMAGR		0xE874
#define KS8695_LAN34_POWERMAGR		0xE878

/* new bits */
#define	KS8695_LPPM_PHY_LOOPBACK	0x4000	/* phy loopback bit 14 */
#define	KS8695_LPPM_RMT_LOOPBACK	0x2000	/* remote loopback bit 13 */
#define	KS8695_LPPM_PHY_ISOLATE		0x1000	/* phy isolate bit 12 */
#define	KS8695_LPPM_SOFT_RESET		0x0800	/* phy isolate bit 11 */
#define	KS8695_LPPM_FORCE_LINK		0x0400	/* force link isolationi bit 10 */
/* shift bit defined already */

/* backward compatible */
#undef	KS8695_LAN12_POWERMAGR
#undef	KS8695_LAN34_POWERMAGR
#define KS8695_LAN12_POWERMAGR		0xE874
#define KS8695_LAN34_POWERMAGR		0xE878

/* Digital Testing Status and Control Registers */
#define KS8695_SEDTS			0xE87C		/* Digital Testing status & control register */
#define KS8695_SEATCS			0xE880		/* Analog Testing status and control register */

/* new bits for WAN PHY Power mangement register */
#define	KS8695_WPPM_PHY_LOOPBACK	0x00004000	/* phy loopback bit 14 */
#define	KS8695_WPPM_RMT_LOOPBACK	0x00002000	/* remote loopback bit 13 */
#define	KS8695_WPPM_PHY_ISOLATION	0x00001000	/* phy isolationi bit 12 */
#define	KS8695_WPPM_FORCE_LINK		0x00000400	/* force link isolationi bit 10 */

#endif	/* CONFIG_KS8695P */

/* bus clock definitions*/
#define KS8695_BUS_CLOCK_125MHZ     0x0
#define KS8695_BUS_CLOCK_100MHZ     0x1
#define KS8695_BUS_CLOCK_62MHZ      0x2
#define KS8695_BUS_CLOCK_50MHZ      0x3
#define KS8695_BUS_CLOCK_41MHZ      0x4
#define KS8695_BUS_CLOCK_33MHZ      0x5
#define KS8695_BUS_CLOCK_31MHZ      0x6
#define KS8695_BUS_CLOCK_25MHZ      0x7

/* -------------------------------------------------------------------------------
 *  definations for IRQ
 * -------------------------------------------------------------------------------*/

#define KS8695_INT_EXT_INT0                    2
#define KS8695_INT_EXT_INT1                    3
#define KS8695_INT_EXT_INT2                    4
#define KS8695_INT_EXT_INT3                    5
#define KS8695_INT_TIMERINT0                   6
#define KS8695_INT_TIMERINT1                   7 
#define KS8695_INT_UART_TX                     8
#define KS8695_INT_UART_RX                     9
#define KS8695_INT_UART_LINE_ERR               10
#define KS8695_INT_UART_MODEMS                 11
#define KS8695_INT_LAN_STOP_RX                 12
#define KS8695_INT_LAN_STOP_TX                 13
#define KS8695_INT_LAN_BUF_RX_STATUS           14
#define KS8695_INT_LAN_BUF_TX_STATUS           15
#define KS8695_INT_LAN_RX_STATUS               16
#define KS8695_INT_LAN_TX_STATUS               17
#define KS8695_INT_HPAN_STOP_RX                18
#define KS8695_INT_HPNA_STOP_TX                19
#define KS8695_INT_HPNA_BUF_RX_STATUS          20
#define KS8695_INT_HPNA_BUF_TX_STATUS          21
#define KS8695_INT_HPNA_RX_STATUS              22
#define KS8695_INT_HPNA_TX_STATUS              23
#define KS8695_INT_BUS_ERROR                   24
#define KS8695_INT_WAN_STOP_RX                 25
#define KS8695_INT_WAN_STOP_TX                 26
#define KS8695_INT_WAN_BUF_RX_STATUS           27
#define KS8695_INT_WAN_BUF_TX_STATUS           28
#define KS8695_INT_WAN_RX_STATUS               29
#define KS8695_INT_WAN_TX_STATUS               30
#define KS8695_INT_WAN_PHY_STATUS              31

#define KS8695_INT_UART                        KS8695_INT_UART_TX

/* -------------------------------------------------------------------------------
 *  Interrupt bit positions
 * 
 * -------------------------------------------------------------------------------
 */

#define KS8695_INTMASK_EXT_INT0                ( 1 << KS8695_INT_EXT_INT0 )
#define KS8695_INTMASK_EXT_INT1                ( 1 << KS8695_INT_EXT_INT1 )
#define KS8695_INTMASK_EXT_INT2                ( 1 << KS8695_INT_EXT_INT2 )
#define KS8695_INTMASK_EXT_INT3                ( 1 << KS8695_INT_EXT_INT3 )
#define KS8695_INTMASK_TIMERINT0               ( 1 << KS8695_INT_TIMERINT0 )
#define KS8695_INTMASK_TIMERINT1               ( 1 << KS8695_INT_TIMERINT1 )
#define KS8695_INTMASK_UART_TX                 ( 1 << KS8695_INT_UART_TX  )
#define KS8695_INTMASK_UART_RX                 ( 1 << KS8695_INT_UART_RX  )
#define KS8695_INTMASK_UART_LINE_ERR           ( 1 << KS8695_INT_UART_LINE_ERR )
#define KS8695_INTMASK_UART_MODEMS             ( 1 << KS8695_INT_UART_MODEMS )
#define KS8695_INTMASK_LAN_STOP_RX             ( 1 << KS8695_INT_LAN_STOP_RX )
#define KS8695_INTMASK_LAN_STOP_TX             ( 1 << KS8695_INT_LAN_STOP_TX )
#define KS8695_INTMASK_LAN_BUF_RX_STATUS       ( 1 << KS8695_INT_LAN_BUF_RX_STATUS )
#define KS8695_INTMASK_LAN_BUF_TX_STATUS       ( 1 << KS8695_INT_LAN_BUF_TX_STATUS )
#define KS8695_INTMASK_LAN_RX_STATUS           ( 1 << KS8695_INT_LAN_RX_STATUS )
#define KS8695_INTMASK_LAN_TX_STATUS           ( 1 << KS8695_INT_LAN_RX_STATUS )
#define KS8695_INTMASK_HPAN_STOP_RX            ( 1 << KS8695_INT_HPAN_STOP_RX )
#define KS8695_INTMASK_HPNA_STOP_TX            ( 1 << KS8695_INT_HPNA_STOP_TX )
#define KS8695_INTMASK_HPNA_BUF_RX_STATUS      ( 1 << KS8695_INT_HPNA_BUF_RX_STATUS )
#define KS8695_INTMAKS_HPNA_BUF_TX_STATUS      ( 1 << KS8695_INT_HPNA_BUF_TX_STATUS
#define KS8695_INTMASK_HPNA_RX_STATUS          ( 1 << KS8695_INT_HPNA_RX_STATUS )
#define KS8695_INTMASK_HPNA_TX_STATUS          ( 1 << KS8695_INT_HPNA_TX_STATUS )
#define KS8695_INTMASK_BUS_ERROR               ( 1 << KS8695_INT_BUS_ERROR )
#define KS8695_INTMASK_WAN_STOP_RX             ( 1 << KS8695_INT_WAN_STOP_RX )
#define KS8695_INTMASK_WAN_STOP_TX             ( 1 << KS8695_INT_WAN_STOP_TX )
#define KS8695_INTMASK_WAN_BUF_RX_STATUS       ( 1 << KS8695_INT_WAN_BUF_RX_STATUS )
#define KS8695_INTMASK_WAN_BUF_TX_STATUS       ( 1 << KS8695_INT_WAN_BUF_TX_STATUS )
#define KS8695_INTMASK_WAN_RX_STATUS           ( 1 << KS8695_INT_WAN_RX_STATUS )
#define KS8695_INTMASK_WAN_TX_STATUS           ( 1 << KS8695_INT_WAN_TX_STATUS )

#define KS8695_SC_VALID_INT                    0xFFFFFFFF
#define MAXIRQNUM                              31
#define LOW_IRQS                               0

/* 
 *  Timer definitions
 * 
 *  Use timer 1 & 2
 *  (both run at 25MHz).
 *
 */
#define TICKS_PER_uSEC                  25
#define mSEC_1                          1000
#define mSEC_10                         (mSEC_1 * 10)

#ifndef CONFIG_MTD_CFI
/*definitions for flash device*/
#define CFI_DEVICETYPE_X8  (8 / 8)
#define CFI_DEVICETYPE_X16 (16 / 8)
#define CFI_DEVICETYPE_X32 (32 / 8)

#if defined(CONFIG_ARCH_KS8695PM) || defined(CONFIG_ARCH_KS8695MB)
  #define CFI_DEVICETYPE                       CFI_DEVICETYPE_X16
  #define CFI_INTERLEAVE                       2 
  #define cfi_buswidth_is_1()                  (0)
  #define cfi_buswidth_is_2()                  (0)
  #define cfi_buswidth_is_4()                  (1)
  #define cfi_interleave_is_1()                (0)
  #define cfi_interleave_is_2()                (1)
  #define cfi_interleave_is_4()                (0)
#elif defined(CONFIG_ARCH_KS8695P) || defined(CONFIG_ARCH_KS8695) || defined(CONFIG_ARCH_KS8695X)
  #define CFI_DEVICETYPE                       CFI_DEVICETYPE_X8
  #define CFI_INTERLEAVE                       1
  #define cfi_buswidth_is_1()                  (1)
  #define cfi_buswidth_is_2()                  (0)
  #define cfi_buswidth_is_4()                  (0)
  #define cfi_interleave_is_1()                (1)
  #define cfi_interleave_is_2()                (0)
  #define cfi_interleave_is_4()                (0)
#elif defined(CONFIG_ARCH_KS8695L) || defined(CONFIG_ARCH_KS8695V)
  #define CFI_DEVICETYPE                       CFI_DEVICETYPE_X16
  #define CFI_INTERLEAVE                       1
  #define cfi_buswidth_is_1()                  (0)
  #define cfi_buswidth_is_2()                  (1)
  #define cfi_buswidth_is_4()                  (0)
  #define cfi_interleave_is_1()                (1)
  #define cfi_interleave_is_2()                (0)
  #define cfi_interleave_is_4()                (0)
#endif
#endif


#define KS_R(x)				__raw_readl(KS_VIO_BASE + (x))
#define KS_W(x, d)			__raw_writel(d, KS_VIO_BASE + (x))

/* Watchdog timer macros.*/
#define TIMER_TIME0_ENABLE  1
#define TIMER_TIME1_ENABLE  2

#define READ_TIMER_CTRL()		KS_R(KS8695_TIMER_CTRL)
#define DISABLE_TIMER(reg)		\
	KS_W(KS8695_TIMER_CTRL, (reg & ~( TIMER_TIME0_ENABLE)))
#define ENABLE_TIMER(reg)		\
	KS_W( KS8695_TIMER_CTRL, (reg | ( TIMER_TIME0_ENABLE)))
#define WRITE_TIMER_VALUE(value, pcount)  \
	{ KS_W(KS8695_TIMER0, value); KS_W(KS8695_TIMER0_PCOUNT, pcount ); }

#endif

/* 	END */
