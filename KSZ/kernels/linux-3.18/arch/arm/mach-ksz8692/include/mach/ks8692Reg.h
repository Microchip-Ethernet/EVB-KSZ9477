/*
 * include/asm-arm/arch-ks8692/ks8692Reg.h
 *
 * Micrel KSZ8692 Registers definitions.
 *
 * Copyright (C) 2006-2010 Micrel, Inc.
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
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *	Support and updates available at
 *	ftp://www.micrel.com/ethernet/ks8692/
  ---------------------------------------------------------------------------

  Author  Date      Version  Description
  PCD     02/15/06           Created file base on KS8692P datasheet rev.2.2. Jan 13, 2006.
  -----------------------------------------------------------------------------------------
 */
#ifndef __KS8692REG_h
#define __KS8692REG_h

/*
 * System Registers
 * (Offset 0x0000 - 0x1FFF)
 */

#define SYSCFG1_BASE                0x0000
#define KS8692_SYSTEM_CONFIG  	    0x0000     /* SYSCFG */

#define KS8692_SYSTEM_BUS_CLOCK     0x0004     /* CLKCON */
#define   IPSEC_CLOCK_200             0x00000600
#define   IPSEC_CLOCK_166             0x00000400
#define   IPSEC_CLOCK_125             0x00000200    /* Default IPSec clock at 125Mhz */
#define   IPSEC_CLOCK_50              0x00000000
#define   IPSEC_CLOCK_MASK            0x00000600

#define   PCI_BUS_CLOCK_66            0x00000080    /* PCI bus running at 66Mhz */
#define   PCI_BUS_CLOCK_33            0x00000000    /* PCI bus running at 33Mhz */

#define   CPU_CLOCK_250               0x00000040
#define   CPU_CLOCK_200               0x00000030
#define   CPU_CLOCK_166               0x00000020    /* Default ARM9 CPU clock at 166Mhz */
#define   CPU_CLOCK_125               0x00000010
#define   CPU_CLOCK_50                0x00000000
#define   CPU_CLOCK_MASK              0x00000070

#define   MEM_CLOCK_200               0x0000000C
#define   MEM_CLOCK_166               0x00000008
#define   MEM_CLOCK_125               0x00000004    /* Default DDR/SDR memory clock at 125Mhz */
#define   MEM_CLOCK_100               0x00000000
#define   MEM_CLOCK_MASK              0x0000000C

#define   SYSTEM_BUS_CLOCK_200        0x00000003
#define   SYSTEM_BUS_CLOCK_166        0x00000002
#define   SYSTEM_BUS_CLOCK_125        0x00000001    /* Default system clock at 125Mhz */
#define   SYSTEM_BUS_CLOCK_50         0x00000000
#define   SYSTEM_BUS_CLOCK_MASK       0x00000003

#define KS8692_NAND_FLASH_CFG      0x0008      /* NFLCFG */
#define   NAND_FLASH_WRITE_PROTECT   0x80000000    /* NAND Flash Memory write protect enable */
#define   NAND_FLASH_AUTO_PAGE       0x40000000    /* Enable NAND Flash Memory auto page open function */
#define   NAND_FLASH_BASE_MASK       0x1FFF0000    /* NAND Flash Config Register base address mask */

#define KS8692_IPSEC_CFG           0x000C      /* IPSECCFG */
#define   IPSEC_BASE_MASK            0x1FFC0000    /* IPSEC Config Register base address mask */
#define   IPSEC_ENABLE               0x00000001    /* Enable IPSEC */


#define KS8692_DDR_MEM_CFG         0x0014      /* DDLCP */
#define   SYS_BYPASS_PLL_EN          0x80000000    /* Enable bypass system PLL */
#define   SYS_X1_250MHZ              0x40000000    /* X1 is expected to 250MHz, if PLL is bypass */
#define   DDR_DDCLKO0                0x00080000    /* Enable DDR clock output 0 */
#define   DDR_DDCLKO1                0x00040000    /* Enable DDR clock output 1 */
#define   DDR_DDCLKO2                0x00020000    /* Enable DDR clock output 2 */
#define   DDR_DDCLKO3                0x00010000    /* Enable DDR clock output 3 */
#define   DESKEW_BYPASS_PLL_EN       0x00000800    /* Enable bypass deskew PLL */
#define   DESKEW_PLL_4DELAY          0x00000300    /* Bypass deskew PLL 4 delay line select */
#define   DESKEW_PLL_3DELAY          0x00000200    /* Bypass deskew PLL 3 delay line select */
#define   DESKEW_PLL_2DELAY          0x00000100    /* Bypass deskew PLL 2 delay line select */
#define   DESKEW_PLL_1DELAY          0x00000000    /* Bypass deskew PLL 1 delay line select */
#define   DDR_DELAY_17BUF            0x00000090    /* DDR Delay Line delay 17BUF */
#define   DDR_DELAY_16BUF            0x00000080    /* DDR Delay Line delay 16BUF */
#define   DDR_DELAY_15BUF            0x00000070    /* DDR Delay Line delay 15BUF */
#define   DDR_DELAY_14BUF            0x00000060    /* DDR Delay Line delay 14BUF */
#define   DDR_DELAY_13BUF            0x00000050    /* DDR Delay Line delay 13BUF */
#define   DDR_DELAY_12BUF            0x00000040    /* DDR Delay Line delay 12BUF */
#define   DDR_DELAY_11BUF            0x00000030    /* DDR Delay Line delay 11BUF */
#define   DDR_DELAY_10BUF            0x00000020    /* DDR Delay Line delay 10BUF */
#define   DDR_DELAY_8BUF             0x00000010    /* DDR Delay Line delay 8BUF */
#define   DDR_DELAY_6BUF             0x00000000    /* DDR Delay Line delay 6BUF */
#define   DDR_RX_PW_DOWN_EN          0x00000004    /* Enable DDR Receiver Power down */

#define KS8692_FEATURE_INTER_CFG   0x0018      /* FEC */
#define   LAN_PORT_SLEEP           0x00020000     /* LAN port sleep */
#define   WAN_PORT_SLEEP           0x00010000     /* WAN port sleep */
#define   TIMER_INTERFACE_DIS      0x00008000     /* Timer Interface Disable */
#define   SPI_INTERFACE_DIS        0x00004000     /* SPI(I2C) Interface Disable */
#define   I2S_INTERFACE_DIS        0x00002000     /* I2S Interface Disable */
#define   UART4_INTERFACE_DIS      0x00001000     /* UART4 Interface Disable */
#define   UART3_INTERFACE_DIS      0x00000800     /* UART3 Interface Disable */
#define   UART2_INTERFACE_DIS      0x00000400     /* UART2 Interface Disable */
#define   UART1_INTERFACE_DIS      0x00000200     /* UART1 Interface Disable */
#define   NOR_INTERFACE_DIS        0x00000100     /* NOR Flash Interface Disable */
#define   NAND_INTERFACE_DIS       0x00000080     /* NAND Flash Interface Disable */
#define   PCI_INTERFACE_DIS        0x00000040     /* PCI Interface Disable */
#define   IPSEC_INTERFACE_DIS      0x00000020     /* IPSEC Interface Disable */
#define   LAN_INTERFACE_DIS        0x00000010     /* LAN Port Interface Disable */
#define   WAN_INTERFACE_DIS        0x00000008     /* WAN Port Interface Disable */
#define   SDIO_INTERFACE_DIS       0x00000004     /* SDIO Interface Disable */
#define   USB_DEV_INTERFACE_DIS    0x00000002     /* USB Device Interface Disable */
#define   USB_HOST_INTERFACE_DIS   0x00000001     /* USB Host Interface Disable */

#define KS8692_IO_BASE_CFG         0x001C      /* NFEIOBA */
#define   IO_BASE_MASK               0xFC000000    /* System Config Register base address mask (0x1FFF0000) */


/*
 * PCI-AHB Bridge Configuration Registers
 * (Offset 0x2000 - 0x3FFF)
 */

/* Memory map base in PCI space */
#define KS8692_PCI_MEM_BASE        PCIBG_MEM_BASE
/* PCI memory size - 512M */
#define KS8692_PCI_MEM_SIZE        (PCIBG_MEM_SIZE << 1)
#define KS8692_PCI_IO_BASE         0x10000000  /* I/O map base in PCI space */
#define KS8692_PCI_IO_SIZE         0x00010000  /* PCI IO memory size - 64K */


/* PCI host device standard configuration registers are defined in pci.h already */

/* Access PCI host bridge configuration registers from CPU internal bus */

#define PCI_BASE    	           0x2000
#define	KS8692_CRCFID              0x2000      /* CRCFID */
#define	KS8692_2000                KS8692_CRCFID

#define	KS8692_CRCFCS              0x2004      /* CRCFCS */
#define	KS8692_2004                KS8692_CRCFCS
#define   PCI_STAT_MASK              0xFFF00000     /* status register bit mask */
#define   PCI_COMM_MASK              0x000FFFFF     /* command register bit mask */
#define   PCI_PARITY_ERROR           0x80000000     /* detected parity error */
#define   PCI_SYSTEM_ERROR           0x40000000     /* detected signal system error */
#define   PCI_RX_MASTER_ABORT        0x20000000     /* received master abort */
#define   PCI_RX_TARGET_ABORT        0x10000000     /* received target abort */
#define   PCI_GEN_TARGET_ABORT       0x08000000     /* generated target abort */
#define   PCI_DEVICE_TIMING_SLOW     0x04000000     /* device select slow timing */
#define   PCI_DEVICE_TIMING_MED      0x02000000     /* device select medium timing */
#define   PCI_DEVICE_TIMING_FAST     0x00000000     /* device select fast timing */
#define   PCI_DATA_PARITY_ERROR      0x01000000     /* data parity error */
#define   PCI_66MHZ                  0x00200000     /* PCI-AHB bridge is 66 MHzr */
#define   PCI_NEW_CAPABILITY         0x00100000     /* New capability */

#define   PCI_COMM_BACK_2_BACK       0x00000200     /* master fast back to back capability */
#define   PCI_COMM_SYSERREN          0x00000100     /* system error enable */
#define   PCI_COMM_ADSTEP            0x00000080     /* address/data stepping */
#define   PCI_COMM_PERRSP            0x00000040     /* parity error response */
#define   PCI_COMM_VGA               0x00000020     /* VGA palette access */
#define   PCI_COMM_MEMORY_WRITE      0x00000010     /* Enable genarate the memory write and invalidate command */
#define   PCI_COMM_MASTER            0x00000004     /* master operation enable */
#define   PCI_COMM_MEM               0x00000002     /* memory space access enable */
#define   PCI_COMM_IO                0x00000001     /* I/O space access enable */
#define   PCI_COMM_SETTING           (PCI_COMM_MEM | PCI_COMM_MASTER | PCI_COMM_PERRSP | PCI_COMM_SYSERREN)

#define	KS8692_CRCFRV              0x2008      /* CRCFRV */
#define	KS8692_2008                KS8692_CRCFRV

#define	KS8692_CRCFLT              0x200C      /* CRCFLT */
#define	KS8692_200C                KS8692_CRCFLT
#define   PCI_LATENCY_TIMER_MASK     0x0000FF00     /* latency timer, 1 byte */
#define   PCI_CACHE_LINESZ_MASK      0x000000FF     /* cache line size, 1 byte */
#define   PCI_LATENCY_TIMER_DEF      0x00000020     /* default latency timer  */
#define   PCI_CACHE_LINESZ           0x00000008     /* default cache line size - 8 (8-DWORD) */

#define	KS8692_CRCBMA              0x2010      /* CRCBMA */
#define	KS8692_2010                KS8692_CRCBMA
#define   PCI_MEMORY_BASE_MASK       0xF0000000     /* PCI base memory address mask */
#define   PCI_MEMORY_PREFETCHABLE    0x00000008     /* PCI memory space is prefetchable */
#define   PCI_MEMORY_MAPPING         0x00000001     /* register maps into memory space */

#define	KS8692_CRCSID              0x202C      /* CRCFID */
#define	KS8692_202C                KS8692_CRCSID
#define   PCI_CSID_SUBSYSID          0xFFFF0000     /* Subsystem ID, 2 bytes */
#define   PCI_CSID_SUBVENID          0x0000FFFF     /* Subsystem Vendor ID, 2 bytes*/

#define	KS8692_CRCCAP              0x2034      /* CRCCAP */
#define   PCI_PW_MANAG_OFFSET        0x00000050     /* Point to power management reg block */

#define	KS8692_CRCFIT              0x203C      /* CRCFID */
#define	KS8692_203C                KS8692_CRCFIT
#define   PCI_CFIT_MAX_L             0xFF000000     /* maximum latency, 1 byte */
#define   PCI_CFIT_MIN_G             0x00FF0000     /* minimum grant, 1 byte */
#define   PCI_CFIT_IPIN              0x0000FF00     /* interrupt pin, 1 byte */
#define   PCI_CFIT_ILINE             0x000000FF     /* interrupt line, 1 byte */
#define   PCI_MAX_LATENCY            0x28           /* default maximum latency - 0x28 */
#define   PCI_MIN_GRANT              0x14           /* default minimum grant - 0x14 */

#define	KS8692_CRCCID              0x2050      /* CRCCID */
#define   PME_STAT_PW_D3_COLD        0x80000000     /* Asserts PME in D3 (cold) state */
#define   PME_STAT_PW_D3_HOT         0x40000000     /* Asserts PME in D3 (hot) state */
#define   PME_STAT_PW_D2             0x20000000     /* Asserts PME in D2 state */
#define   PME_STAT_PW_D1             0x10000000     /* Asserts PME in D1 state */
#define   PME_STAT_PW_D0             0x08000000     /* Asserts PME in D0 state */
#define   PME_CAPT_PW_D2             0x04000000     /* Support D2 power state */
#define   PME_CAPT_PW_D1             0x02000000     /* Support D1 power state */
#define   REQ_SPECIFIC_INIT          0x00200000     /* Device request specific initialization */
#define   REQ_PME_CLOCK              0x00080000     /* PME genaration request PCI clock */
#define   PW_PCI_VERSION_MASK        0x00070000     /* Power management PCI version */
#define   CAPABILITY_ID_MASK         0x000000FF     /* Capabilities ID mask */

#define	KS8692_CRCPMC              0x2054      /* CRCPMC */
#define   PCI_PW_PME_STATUS          0x00008000     /* Status of PMEN pin is asserted */
#define   PCI_PW_PME_ENABLE          0x00000100     /* Enable PME (Power Manager) */
#define   PCI_STAT_NO_SOFTRESET      0x00000008     /* No soft reset when power from D3 to D0 */
#define   PCI_PW_STATE_D3            0x00000003     /* Current Power State is D3 (hot) */
#define   PCI_PW_STATE_D2            0x00000002     /* Current Power State is D2 */
#define   PCI_PW_STATE_D1            0x00000001     /* Current Power State is D1 */
#define   PCI_PW_STATE_D0            0x00000000     /* Current Power State is D0 */
#define   PCI_PW_STATE_MASK          0x00000003     /* Power State mask */

#define	KS8692_PBCA                0x2100      /* CRCFID */
#define	KS8692_2100                KS8692_PBCA
#define   PCI_BUS_NUM_MASK           0x00FF0000     /* PCI bus number mask */
#define   PCI_DEV_NUM_MASK           0x0000F100     /* PCI device number mask */
#define   PCI_FUN_NUM_MASK           0x00000700     /* PCI function number mask */
#define   PCI_REG_NUM_MASK           0x000000FC     /* PCI register number mask */
#define   PCI_TYPE1                  0x00000001     /* PCI TYPE 1 configuration */
#define   PCI_TYPE0                  0x00000000     /* PCI TYPE 0 configuration */

#define	KS8692_PBCD                0x2104      /* CRCFID */
#define	KS8692_2104                KS8692_PBCD

#define	KS8692_PBM                 0x2200      /* PBM */
#define	KS8692_2200                KS8692_PBM
#define   PCI_HOST_BRIDGE_MODE       0x80000000     /* Host Bridge mode */
#define   PCI_CARDBUS_MODE           0x40000000     /* Card bus mode */
#define   PCI_MINIPCI_MODE           0x20000000     /* Mini PCI mode */
#define   PCI_PCI_MODE               0x00000000     /* PCI mode */

#define	KS8692_PBCS                0x2204      /* PBCS */
#define	KS8692_2204                KS8692_PBCS
#define	  PCI_SW_RESET               0x80000000     /* Software reset */
#define	  PCI_PREFETCH_WORDS16       0x40000000     /* Prefetch limit equals 16 words */
#define	  PCI_PREFETCH_WORDS8        0x20000000     /* Prefetch limit equals 8 words */
#define	  PCI_PREFETCH_WORDS4        0x00000000     /* Prefetch limit equals 4 words */
#define	  PCI_EXT_ACCESS_DIS         0x10000000     /* Disable PCI configuration external access */

#define	KS8692_PMBA                0x2208      /* PMBA */
#define	KS8692_2208                KS8692_PMBA
#define   PCIBG_MEM_BASE             0x20000000     /* Memory base address for bridge */

#define	KS8692_PMBAC               0x220C      /* PMBAC */
#define	KS8692_220C                KS8692_PMBAC
#define	  PCI_TRANS_ENABLE           0x80000000     /* Enable Memory mapping Address Translation */

#define	KS8692_PMBAM               0x2210      /* PMBAM */
#define	KS8692_2210                KS8692_PMBAM
#define   PMBAM_MEM_MASK             0xE0000000     /* PCI Address masking for memory mapping - 512M */
#define   PCIBG_MEM_SIZE             0x10000000     /* bridge mem size - 256M */

#define	KS8692_PMBAT               0x2214      /* PMBAT */
#define	KS8692_2214                KS8692_PMBAT

#define	KS8692_PIOBA               0x2218      /* PIOBA */
#define	KS8692_2218                KS8692_PIOBA
#define   PCIBG_IO_BASE              0x10000000     /* IO base address for bridge */

#define	KS8692_PIOBAC              0x221C      /* PIOBAC */
#define	KS8692_221C                KS8692_PIOBAC
#define	  PCI_IO_TRANS_ENABLE        0x80000000     /* Enable I/O mapping Address Translation */

#define	KS8692_PIOBAM              0x2220      /* PIOBAM */
#define	KS8692_2220                KS8692_PIOBAM
#define   PIOBAM_IO_MASK             0xFFFF0000     /* PCI Address masking for IO mapping - 64K */
#define   PCI_IO_SIZE                0x00010000     /* PCI IO size - 64K */

#define	KS8692_PIOBAT              0x2224      /* PIOBAT */
#define	KS8692_2224                KS8692_PIOBAT


/*
 * Memory Controller Registers
 * (Offset 0x4000 - 0x4FFF)
 */

#define DDR_BASE                   0x4000
#define KS8692_DDR_CTL_00          0x4000      /* DDR_CTL_00 */
#define   DDR_BANK_SPLIT_EN          0x01000000    /* Enable bank spliting for cmd queue */
#define   DDR_ADDR_CMPT_EN           0x00010000    /* Enable address collision for cmd queue */
#define   DDR_CMD_AGE_CNT_MASK       0x00007000    /* Command age counters mask for cmd queue */
#define   DDR_AGE_CNT_MASK           0x00000007    /* Master aging-rate counters mask for cmd queue */

#define KS8692_DDR_CTL_01          0x4004      /* DDR_CTL_01 */
#define   DDR_FAST_WRITE             0x01000000    /* Sets when write cmds */
#define   DDR_RW_SAME_EN             0x00010000    /* Enable read/write grouping for cmd queue */
#define   DDR_PRIORITY_EN            0x00000100    /* Enable priority for cmd queue */
#define   DDR_PLACEMENT_EN           0x00000001    /* Enable placement for cmd queue */

#define KS8692_DDR_CTL_02          0x4008      /* DDR_CTL_02 */
#define   DDR_INT_STATUS_MASK        0x3F000000    /* Interrupt status mask */
#define   DDR_DLL_INCREMENT_MASK     0x003F0000    /* Number of elements to add to DLL_START_POINT */
#define   DDR_DLL_START_MASK         0x00003F00    /* Initial delay count mask */
#define   DDR_Q_FULLNESS_MASK        0x00000003    /* Quantity that determines cmd queue full */

#define KS8692_DDR_CTL_03          0x400C      /* DDR_CTL_03 */
#define   DDR_R_PRIORITY_P0_MASK     0x07000000    /* Priority of read cmds for port 0 */
#define   DDR_OUT_OF_RANGE_INT_MASK  0x00030000    /* cmd that cause Out-of-Range interrupt status */
#define   DDR_INT_MASK               0x00003F00    /* Interrupt mask */
#define   DDR_INT_ACK_MASK           0x0000001F    /* Clear Interrupt mask */

#define KS8692_DDR_CTL_04          0x4010      /* DDR_CTL_04 */
#define   DDR_CURRENT_BDW_P0_MASK    0x7F000000    /* Current bandwidth usage percentage for port0 mask */
#define   DDR_BDW_OVFLOW_P0          0x00010000    /* Port 0 bandwidth overflow */
#define   DDR_MAX_BDW_P0_MASK        0x0007F000    /* Port 0 max bandwidth mask */
#define   DDR_W_PRIORITY_P0_MASK     0x00000007    /* Priority of write cmds for port 0 */

#define KS8692_DDR_CTL_05          0x4014      /* DDR_CTL_05 */
#define   DDR_BDW_OVFLOW_P1          0x01000000    /* Port 1 bandwidth overflow */
#define   DDR_MAX_BDW_P1_MASK        0x007F0000    /* Port 1 max bandwidth mask */
#define   DDR_W_PRIORITY_P1_MASK     0x00000700    /* Priority of write cmds for port 1 */
#define   DDR_R_PRIORITY_P1_MASK     0x00000007    /* Priority of read cmds for port 1 */
#define   DDR_CURRENT_BDW_P1_MASK    0x0000007F    /* Current bandwidth usage percentage for port1 mask */

#define KS8692_DDR_CTL_06          0x4018      /* DDR_CTL_06 */
#define   DDR_MAX_BDW_P2_MASK        0x7F000000    /* Port 2 max bandwidth mask */
#define   DDR_W_PRIORITY_P2_MASK     0x00070000    /* Priority of write cmds for port 2 */
#define   DDR_R_PRIORITY_P2_MASK     0x00000700    /* Priority of read cmds for port 2 */
#define   DDR_CURRENT_BDW_P1_MASK    0x0000007F    /* Current bandwidth usage percentage for port1 mask */

#define KS8692_DDR_CTL_07          0x401C      /* DDR_CTL_07 */
#define   DDR_W_PRIORITY_P3_MASK     0x07000000    /* Priority of write cmds for port 3 */
#define   DDR_R_PRIORITY_P3_MASK     0x00070000    /* Priority of read cmds for port 3 */
#define   DDR_CURRENT_BDW_P2_MASK    0x00007F00    /* Current bandwidth usage percentage for port2 mask */
#define   DDR_BDW_OVFLOW_P2          0x00000001    /* Port 2 bandwidth overflow */

#define KS8692_DDR_CTL_08          0x4020      /* DDR_CTL_08 */
#define   DDR_R_PRIORITY_P4_MASK     0x07000000    /* Priority of write cmds for port 4 */
#define   DDR_CURRENT_BDW_P3_MASK    0x007F0000    /* Current bandwidth usage percentage for port3 mask */
#define   DDR_BDW_OVFLOW_P3          0x00000100    /* Port 3 bandwidth overflow */
#define   DDR_MAX_BDW_P3_MASK        0x0000007F    /* Port 3 max bandwidth mask */

#define KS8692_DDR_CTL_09          0x4024      /* DDR_CTL_09 */
#define   DDR_CURRENT_BDW_P4_MASK    0x7F000000    /* Current bandwidth usage percentage for port4 mask */
#define   DDR_BDW_OVFLOW_P4          0x00010000    /* Port 4 bandwidth overflow */
#define   DDR_MAX_BDW_P4_MASK        0x00007F00    /* Port 4 max bandwidth mask */
#define   DDR_W_PRIORITY_P4_MASK     0x00000007    /* Priority of write cmds for port 4 */

#define KS8692_DDR_CTL_10          0x4028      /* DDR_CTL_10 */
#define   DDR_BDW_OVFLOW_P5          0x01000000    /* Port 5 bandwidth overflow */
#define   DDR_MAX_BDW_P5_MASK        0x007F0000    /* Port 5 max bandwidth mask */
#define   DDR_W_PRIORITY_P5_MASK     0x00000700    /* Priority of write cmds for port 5 */
#define   DDR_R_PRIORITY_P5_MASK     0x00000007    /* Priority of write cmds for port 5 */

#define KS8692_DDR_CTL_11          0x402C      /* DDR_CTL_11 */
#define   DDR_MAX_BDW_P6_MASK        0x7F000000    /* Port 6 max bandwidth mask */
#define   DDR_W_PRIORITY_P6_MASK     0x00070000    /* Priority of write cmds for port 6 */
#define   DDR_R_PRIORITY_P6_MASK     0x00000700    /* Priority of read cmds for port 6 */
#define   DDR_CURRENT_BDW_P5_MASK    0x0000007F    /* Current bandwidth usage percentage for port5 mask */

#define KS8692_DDR_CTL_12          0x4030      /* DDR_CTL_12 */
#define   DDR_W_PRIORITY_P7_MASK     0x07000000    /* Priority of write cmds for port 7 */
#define   DDR_R_PRIORITY_P7_MASK     0x00070000    /* Priority of read cmds for port 7 */
#define   DDR_CURRENT_BDW_P6_MASK    0x00007F00    /* Current bandwidth usage percentage for port6 mask */
#define   DDR_BDW_OVFLOW_P6          0x00000001    /* Port 6 bandwidth overflow */

#define KS8692_DDR_CTL_13          0x4034      /* DDR_CTL_13 */
#define   DDR_CMD_Q_THRES_MASK       0x03000000    /* Overflow threshold for cmd queue */
#define   DDR_CURRENT_BDW_P7_MASK    0x007F0000    /* Current bandwidth usage percentage for port7 mask */
#define   DDR_BDW_OVFLOW_P7          0x00000100    /* Port 7 bandwidth overflow */
#define   DDR_MAX_BDW_P7_MASK        0x0000007F    /* Port 7 max bandwidth mask */

#define KS8692_DDR_CTL_14          0x4038      /* DDR_CTL_14 */
#define   DDR_MAX_CS_MASK            0x03000000    /* Max CS available mask */
#define   DDR_MAX_COL_MASK           0x000F0000    /* Max width column address mask in DRAMs */
#define   DDR_MAX_DW_MASK            0x00000F00    /* Max width of memory address bus mask */
#define   DDR_CMD_START              0x00000001    /* Start cmd processing */

#define KS8692_DDR_CTL_15          0x403C      /* DDR_CTL_15 */
#define   DDR_CASLAT_MASK            0x07000000    /* Encoded CAS latency sent to DRAMs during init.*/
#define   DDR_CASLAT_LIN_GATE_MASK   0x001F0000    /* Adjusts data captures gate open by half cycles */
#define   DDR_CASLAT_LIN_MASK        0x00001F00    /* Sets latency from read cmd mask */
#define   DDR_INITAREF_MASK          0x0000000F    /* Number of auto-refresh cmds to execute mask */

#define KS8692_DDR_CTL_16          0x4040      /* DDR_CTL_16 */
#define   DDR_TRC_MASK               0x1F000000    /* DRAM TRC parameters in cycles mask */
#define   DDR_TPDEX_MASK             0x00070000    /* DRAM TPDEX parameters in cycles mask  */
#define   DDR_TRRD_MASK              0x00000700    /* DRAM TRRD parameters in cycles mask  */
#define   DDR_BSTLEN_MASK            0x00000007    /* Encodeed burst length sent to DRAMs ask during init.*/

#define KS8692_DDR_CTL_17          0x4044      /* DDR_CTL_17 */
#define   DDR_TMRD_MASK              0x1F000000    /* DRAM TMRD parameters in cycles mask */
#define   DDR_TEMRS_MASK             0x00030000    /* DRAM TEMRS parameters in cycles mask  */
#define   DDR_TRP_MASK               0x00000F00    /* DRAM TRP parameters in cycles mask  */
#define   DDR_TRAS_MIN_MASK          0x000000FF    /* Encodeed TRAS_MIN prameters in cycles */

#define KS8692_DDR_CTL_18          0x4048      /* DDR_CTL_18 */
#define   DDR_WRITE_INTERP           0x01000000    /* Enable write burst interrupt with a read cmd */
#define   DDR_TWTR_MASK              0x00070000    /* DRAM TWTR parameters in cycles mask  */
#define   DDR_TRFC_MASK              0x000000FF    /* DRAM TRFC parameters in cycles mask  */

#define KS8692_DDR_CTL_19          0x404C      /* DDR_CTL_19 */
#define   DDR_WR_DQS_SHIFT_MASK      0x1F000000    /* Fraction of a cycle to delay the clk_wr signal */
#define   DDR_AREFRESH               0x00010000    /* Initiate auto-refresh when specified by AUTO_REFRESH_MODE  */
#define   DDR_AUTO_REFRESH_MODE      0x00000001    /* Sets if auto-refresh will be next or next cmd */

#define KS8692_DDR_CTL_20          0x4050      /* DDR_CTL_20 */
#define   DDR_WRITE_MODEREG          0x01000000    /* Write EMRS data to the DRAMs */
#define   DDR_CS_MAP_MASK            0x00030000    /* CS selects used in address decoding mask  */
#define   DDR_NO_CMD_INIT            0x00000100    /* Disable DRAM cmds until TDLL has expired during init */
#define   DDR_WR_DQS_SHIFT_BYPASS    0x0000007F    /* Fraction of a cycle to delay the clk_wr when bypassed mask */

#define KS8692_DDR_CTL_21          0x4054      /* DDR_CTL_21 */
#define   DDR_SREFRESH               0x01000000    /* Place DRAMs in self-refresh mode */
#define   DDR_POWER_DOWN             0x00000001    /* Set DRAMs in power-down state */

#define KS8692_DDR_CTL_22          0x4058      /* DDR_CTL_22 */
#define   DDR_CONCURRENTAP           0x01000000    /* Allow to issue cmds to other banks */
#define   DDR_AP_EN                  0x00010000    /* Enable auto pre-charge mode */
#define   DDR_DRIVE_DQ_DQS           0x00000100    /* Set DQ/DQS ouput enable behavior */
#define   DDR_TCKE_MASK              0x00000007    /* Minimum CKE pulse width mask */

#define KS8692_DDR_CTL_23          0x405C      /* DDR_CTL_23 */
#define   DDR_TRAS_LOCKOUT           0x01000000    /* Allow to execute auto pre-charge cmds before TRAS_MIN expires */
#define   DDR_INTRPTAPBURST          0x00010000    /* Allow to interrupt auto pre-charge cmds with another cmd */
#define   DDR_INTRPTWRITEA           0x00000100    /* Allow to interrupt a combined write cmd */
#define   DDR_INTRPTREADA            0x00000001    /* Allow to interrupt a combined read cmd */

#define KS8692_DDR_CTL_24          0x4060      /* DDR_CTL_24 */
#define   DDR_DLL_BYPASS_MODE        0x01000000    /* Enable the DLL bypass feature of the controller */
#define   DDR_TDAL_MASK              0x000F0000    /* DRAM TDAL parameter in cycles mask  */
#define   DDR_TWR_INT_MASK           0x00000700    /* DRAM TWR_INT parameter in cycles mask  */
#define   DDR_TRCD_INT_MASK          0x000000FF    /* DRAM TRCD_INT parameter in cycles mask  */

#define KS8692_DDR_CTL_25          0x4064      /* DDR_CTL_25 */
#define   DDR_DLL_LOCK_MASK          0x7F000000    /* Number of delay elements in master DLL lock mask */
#define   DDR_APREBIT_MASK           0x000F0000    /* Location of the auto pre-charge bit in the DRAM address */
#define   DDR_COLUMN_SIZE_MASK       0x00000700    /* Different between column pins available and used */
#define   DDR_ADDR_PINS_MASK         0x00000007    /* Different between address pins available and used */

#define KS8692_DDR_CTL_26          0x4068      /* DDR_CTL_26 */
#define   DDR_DLL_DQS_DELAY_3_MASK   0x7F000000    /* Delay dqs from DRAM for dll_rd_dqs_slice 3 mask */
#define   DDR_DLL_DQS_DELAY_2_MASK   0x007F0000    /* Delay dqs from DRAM for dll_rd_dqs_slice 2 mask */
#define   DDR_DLL_DQS_DELAY_1_MASK   0x00007F00    /* Delay dqs from DRAM for dll_rd_dqs_slice 1 mask */
#define   DDR_DLL_DQS_DELAY_0_MASK   0x0000007F    /* Delay dqs from DRAM for dll_rd_dqs_slice 0 mask */

#define KS8692_DDR_CTL_27          0x406C      /* DDR_CTL_27 */
#define   DDR_DLL_DQS_DELAY_BYPASS_3 0x7F000000    /* Delay dqs from DRAM for dll_rd_dqs_slice 3 mask when DLL is bypass */
#define   DDR_DLL_DQS_DELAY_BYPASS_2 0x007F0000    /* Delay dqs from DRAM for dll_rd_dqs_slice 2 mask when DLL is bypass */
#define   DDR_DLL_DQS_DELAY_BYPASS_1 0x00007F00    /* Delay dqs from DRAM for dll_rd_dqs_slice 1 mask when DLL is bypass */
#define   DDR_DLL_DQS_DELAY_BYPASS_0 0x0000007F    /* Delay dqs from DRAM for dll_rd_dqs_slice 0 mask when DLL is bypass */

#define KS8692_DDR_CTL_28          0x4070      /* DDR_CTL_28 */
#define   DDR_OUT_OF_RANGE_LEN_MASK  0x03FF0000    /* Length of cmd that cause Out-of-Range interrupt mask */
#define   DDR_DQS_OUT_SHIFT_BYPASS   0x00007F00    /* Delay the write dqs to DRAMs during writes when when DLL is bypass */
#define   DDR_DQS_OUT_SHIFT          0x0000007F    /* Delay the dqs to DRAMs during writes */

#define KS8692_DDR_CTL_29          0x4074      /* DDR_CTL_29 */
#define KS8692_DDR_CTL_30          0x4078      /* DDR_CTL_30 */
#define KS8692_DDR_CTL_31          0x407C      /* DDR_CTL_31 */
#define KS8692_DDR_CTL_32          0x4080      /* DDR_CTL_32 */
#define KS8692_DDR_CTL_33          0x4084      /* DDR_CTL_33 */
#define KS8692_DDR_CTL_34          0x4088      /* DDR_CTL_34 */
#define KS8692_DDR_CTL_35          0x408C      /* DDR_CTL_35 */
#define KS8692_DDR_CTL_36          0x4090      /* DDR_CTL_36 */
#define   DDR_AHB_RDCNT_MASK         0x07FF0000    /* Number of bytes for an INCR_READ cmd on port0 (port7) mask */
#define   DDR_AHB_WRCNT_MASK         0x000007FF    /* Number of bytes for an INCR_WRITE cmd on port0 (port7) mask */

#define KS8692_DDR_CTL_37          0x4094      /* DDR_CTL_37 */
#define   DDR_TREF_MASK              0x0FFF0000    /* DRAM TREF parameters in cycles mask */
#define   DDR_VERSION_MASK           0x0000FFFF    /* DRAM version number mask */

#define KS8692_DDR_CTL_38          0x4098      /* DDR_CTL_38 */
#define   DDR_TRAS_MAX_MASK          0x0000FFFF    /* DRAM TRAS_MAX parameter in cycles mask */

#define KS8692_DDR_CTL_39          0x409C      /* DDR_CTL_39 */
#define   DDR_EMRS_DATA_MASK         0x00003FFF    /* Extended mode register data written mask */

#define KS8692_DDR_CTL_40          0x40A0      /* DDR_CTL_40 */
#define   DDR_OUT_OF_RANGE_ADDR      0x7FFFFFFF    /* Address of cmd that caused Out-of-Range interrupt */

#define KS8692_DDR_CTL_41          0x40A4      /* DDR_CTL_41 */
#define   DDR_OUT_OF_RANGE_SRC_ID    0x07000000    /* Source ID of cmd that caused Out-of-Range interrupt */
#define   DDR_REG_DIMM_EN            0x00010000    /* Enable register DIMM operation */
#define   DDR_REDUC_EN               0x00000100    /* Enable half datapath feature */
#define   DDR_DLLLOCKREG_STATUS      0x00000001    /* Status of DLL lock coming out of master delay */

#define KS8692_DDR_CTL_42          0x40A8      /* DDR_CTL_42 */
#define   DDR_TDLL_MASK              0x00FFFF00    /* DRAM TDLL parameters in cycles mask */
#define   DDR_PORT_BUSY_MASK         0x00FFFF00    /* Per-port indicator that a cmd is in processing mask */

#define KS8692_DDR_CTL_43          0x40AC      /* DDR_CTL_43 */
#define   DDR_TXSR_MASK              0xFFFF0000    /* DRAM TXSR parameters in cycles mask */
#define   DDR_TXSNR_MASK             0x0000FFFF    /* DRAM TXSNR parameters in cycles mask */

#define KS8692_DDR_CTL_44          0x40B0      /* DDR_CTL_44 */
#define   DDR_TINIT_MASK             0x00FFFFFF    /* DRAM TINIT parameters in cycles mask */



/*
 * External I/O, Static Memory Controller Registers
 * (Offset 0x5000 - 0x5FFF)
 */

#define SDRAM_BASE                 0x5000
#define KS8692_IO_CTRL0            0x5000      /* EXTACON0 */
#define KS8692_IO_CTRL1            0x5004      /* EXTACON1 */
#define KS8692_IO_CTRL2            0x5008      /* EXTACON2 */
#define   EXT_IO_LAST_ADDR_MASK      0x3FC00000    /* External I/O last address mask */
#define   EXT_IO_BASE_ADDR_MASK      0x000FF000    /* External I/O base address mask */
#define   EXT_IO_WRITE_ACTIVE_MASK   0x00000E00    /* External I/O Write Active time mask */
#define   EXT_IO_CS_HOLD_MASK        0x000001C0    /* External I/O CS hold time mask */
#define   EXT_IO_ADDR_SETUP_MASK     0x00000038    /* External I/O Address setup time mask */
#define   EXT_IO_CS_SETUP_MASK       0x00000007    /* External I/O CS setup time mask */

#define   SYS_CLOCK_UNIT7            0x7           /* Time defined in unit of system clock */
#define   SYS_CLOCK_UNIT6            0x6
#define   SYS_CLOCK_UNIT5            0x5
#define   SYS_CLOCK_UNIT4            0x4
#define   SYS_CLOCK_UNIT3            0x3
#define   SYS_CLOCK_UNIT2            0x2
#define   SYS_CLOCK_UNIT1            0x1
#define   SYS_CLOCK_UNIT0            0x0


#define KS8692_MEM_CTRL0           0x5010      /* ROMCON0 */
#define KS8692_MEM_CTRL1           0x5014      /* ROMCON1 */
#define   ROM_LAST_ADDR_MASK         0xFFC00000    /* ROM/SRAM/FLASH last address mask */
#define   ROM_BASE_ADDR_MASK         0x003FF000    /* ROM/SRAM/FLASH base address mask */
#define   ROM_ACCESS_CYCLE_MASK      0x00000070    /* ROM/SRAM/FLASH Access Cycle time mask */
#define   ROM_PAGE_ACCESS_MASK       0x0000000C    /* ROM/SRAM/FLASH Page Address Access time mask */
#define   ROM_PAGE_MODE_MASK         0x00000003    /* ROM/SRAM/FLASH Page mode mask */
#define   ROM_PAGE16                 0x00000003    /* ROM/SRAM/FLASH access size is 16 word page */
#define   ROM_PAGE8                  0x00000002    /* ROM/SRAM/FLASH access size is 8 word page */
#define   ROM_PAGE4                  0x00000001    /* ROM/SRAM/FLASH access size is 4 word page */
#define   ROM_PAGE0                  0x00000000    /* ROM/SRAM/FLASH access size is normal ROM */


#define KS8692_MEM_GENERAL         0x5020      /* ERGCON */
#define   ROM_TIME_MULTIPLER_3       0x30000000    /* External I/O and ROM/SRAM/FLASH Time Multiplier */
#define   ROM_TIME_MULTIPLER_2       0x20000000
#define   ROM_TIME_MULTIPLER_1       0x10000000
#define   ROM_TIME_MULTIPLER_0       0x00000000
#define   EXT_IO2_DW32               0x00300000    /* External I/O bank 2 32-bit data width */
#define   EXT_IO2_DW16               0x00200000    /* External I/O bank 2 16-bit data width */
#define   EXT_IO2_DW8                0x00100000    /* External I/O bank 2 8-bit data width */
#define   EXT_IO2_DIS                0x00000000    /* Disable External I/O bank 2 */
#define   EXT_IO1_DW32               0x000C0000    /* External I/O bank 1 32-bit data width */
#define   EXT_IO1_DW16               0x00080000    /* External I/O bank 1 16-bit data width */
#define   EXT_IO1_DW8                0x00040000    /* External I/O bank 1 8-bit data width */
#define   EXT_IO1_DIS                0x00000000    /* Disable External I/O bank 1 */
#define   EXT_IO0_DW32               0x00030000    /* External I/O bank 0 32-bit data width */
#define   EXT_IO0_DW16               0x00020000    /* External I/O bank 0 16-bit data width */
#define   EXT_IO0_DW8                0x00010000    /* External I/O bank 0 8-bit data width */
#define   EXT_IO0_DIS                0x00000000    /* Disable External I/O bank 0 */
#define   ROM1_DW32                  0x0000000C    /* ROM/SRAM/FLASH bank 1 32-bit data width */
#define   ROM1_DW16                  0x00000008    /* ROM/SRAM/FLASH bank 1 16-bit data width */
#define   ROM1_DW8                   0x00000004    /* ROM/SRAM/FLASH bank 1 8-bit data width */
#define   ROM1_DIS                   0x00000000    /* Disable ROM/SRAM/FLASH bank 1 */
#define   ROM0_DW32                  0x00000003    /* ROM/SRAM/FLASH bank 0 32-bit data width */
#define   ROM0_DW16                  0x00000002    /* ROM/SRAM/FLASH bank 0 16-bit data width */
#define   ROM0_DW8                   0x00000001    /* ROM/SRAM/FLASH bank 0 8-bit data width */
#define   ROM0_DIS                   0x00000000    /* Disable ROM/SRAM/FLASH bank 0 */

#define KS8692_SDRAM_CTRL0         0x5030      /* SDCON0 */
#define KS8692_SDRAM_CTRL1         0x5034      /* SDCON1 */
#define   SDRAM_LAST_ADDR_MASK       0xFFC00000    /* ROM/SRAM/FLASH last address mask */
#define   SDRAM_BASE_ADDR_MASK       0x003FF000    /* ROM/SRAM/FLASH base address mask */
#define   SDRAM_COL_ADDR11	         0x00000300    /* SDRAM 11-bit Column address */
#define   SDRAM_COL_ADDR10	         0x00000200    /* SDRAM 10-bit Column address */
#define   SDRAM_COL_ADDR9	         0x00000100    /* SDRAM 9-bit Column address */
#define   SDRAM_COL_ADDR8 	         0x00000000    /* SDRAM 8-bit Column address */
#define   SDRAM_4_DEVICE             0x00000008    /* SDRAM 4-bank devices */
#define   SDRAM_2_DEVICE             0x00000000    /* SDRAM 2-bank devices */
#define   SDRAM_DBW32	             0x00000006    /* SDRAM 32-bit data width */
#define   SDRAM_DBW16	             0x00000004    /* SDRAM 16-bit data width */
#define   SDRAM_DBW8	             0x00000002    /* SDRAM 8-bit data width */
#define   SDRAM_DIS 	             0x00000000    /* Disable SDRAM */

#define KS8692_SDRAM_GENERAL       0x5038      /* SDGCON */
#define   SDRAM_RAS2CAS_LATENCY4     0x0000000C    /* SDRAM RAS to CAS 4-cycle latency */
#define   SDRAM_RAS2CAS_LATENCY3     0x00000008    /* SDRAM RAS to CAS 3-cycle latency */
#define   SDRAM_RAS2CAS_LATENCY2     0x00000004    /* SDRAM RAS to CAS 2-cycle latency */
#define   SDRAM_RAS2CAS_LATENCY1     0x00000000    /* SDRAM RAS to CAS 1-cycle latency */
#define   SDRAM_CAS_LATENCY4         0x00000003    /* SDRAM CAS 4-cycle latency */
#define   SDRAM_CAS_LATENCY3         0x00000002    /* SDRAM CAS 3-cycle latency */
#define   SDRAM_CAS_LATENCY2         0x00000001    /* SDRAM CAS 2-cycle latency */
#define   SDRAM_CAS_LATENCY1         0x00000000    /* SDRAM CAS 1-cycle latency */

#define KS8692_SDRAM_BUFFER        0x503C      /* SDBCON */
#define   SDRAM_STAT_BUSY            0x80000000    /* SDRAM engine is busy */
#define   SDRAM_BUF_BURST_EN         0x01000000    /* Enable SDRAM read buffer burst for the incremental burst */
#define   SDRAM_WRITE_FIFO_EN        0x00800000    /* Enable write FIFO */
#define   SDRAM_READ_FIFO_EN         0x00400000    /* Enable read FIFO */
#define   SDRAM_FLUSH_FIFO           0x00200000    /* Flush write FIFO to the SDRAM memory */
#define   SDRAM_INVALIDATE_FIFO      0x00100000    /* Invalidates read FIFO */
#define   SDRAM_CMD_NOP              0x00030000    /* Issure a NOP command to the SDRAM */
#define   SDRAM_CMD_MODE             0x00020000    /* Issure a Mode command to the SDRAM */
#define   SDRAM_CMD_PRECHARGE        0x00010000    /* Issure a Precharge command to the SDRAM */
#define   SDRAM_CMD_NORMAL           0x00000000    /* Issure a Normal command to the SDRAM */
#define   SDRAM_MODE_VALUE_MASK      0x00003FFF    /* SDRAM Mode register program value mask */

#define KS8692_SDRAM_REFRESH       0x5040      /* REFTIM */
#define   SDRAM_REFRESH_TIMER_MASK   0x0000FFFF    /* SDRAM Mode register program value mask */


/*
 * WAN DMA Registers
 * (Offset 0x6000 - 0x7FFF)
 */

#define WAN_BASE                   0x6000
#define KS8692_WAN_DMA_TX          0x6000      /* WMDTXC */
#define KS_WAN_DMA_TX              KS8692_WAN_DMA_TX
#define KS8692_WAN_DMA_RX          0x6004      /* WMDRXC */
#define KS8692_WAN_DMA_TX_START    0x6008      /* WMDTSC */
#define KS8692_WAN_DMA_RX_START    0x600C      /* WMDRSC */
#define KS8692_WAN_TX_LIST         0x6010      /* WTDLB */
#define KS8692_WAN_RX_LIST         0x6014      /* WRDLB */
#define KS8692_WAN_MAC_LOW         0x6018      /* WMAL */
#define KS8692_WAN_MAC_HIGH        0x601C      /* WMAH */
#define KS8692_WAN_MISC_CFG        0x6020      /* WEMC */

#define KS8692_WAN_RX_WATERMARK    0x6028      /* WMWTR */
#define	  WAN_HIGH_WATERMK_HP_MASK   0x07F00000	   /* High watermark mask of high priority (7KB) */
#define	  WAN_HIGH_WATERMK_LP_MASK   0x0001FC00	   /* High watermark mask of low priority (5KB) */
#define	  WAN_LOW_WATERMARK_MASK     0x0000007F	   /* Low watermark mask (2KB) */

#define KS8692_WAN_MULTICAST_LO    0x602C      /* WMTRL */
#define KS8692_WAN_MULTICAST_HI    0x6030      /* WMTRH */

#define KS8692_WAN_WOL_CTRL        0x6034      /* WWFCR */

#define KS8692_WAN_FRAME0_CRC      0x6038      /* WWF0CRC */
#define KS8692_WAN_FRAME0_MASK0    0x603C      /* WWF0MK0 */
#define KS8692_WAN_FRAME0_MASK1    0x6040      /* WWF0MK1 */

#define KS8692_WAN_FRAME1_CRC      0x6044      /* WWF1CRC */
#define KS8692_WAN_FRAME1_MASK0    0x6048      /* WWF1MK0 */
#define KS8692_WAN_FRAME1_MASK1    0x604C      /* WWF1MK1 */

#define KS8692_WAN_FRAME2_CRC      0x6050      /* WWF2CRC */
#define KS8692_WAN_FRAME2_MASK0    0x6054      /* WWF2MK0 */
#define KS8692_WAN_FRAME2_MASK1    0x6058      /* WWF2MK1 */

#define KS8692_WAN_FRAME3_CRC      0x605C      /* WWF3CRC */
#define KS8692_WAN_FRAME3_MASK0    0x6060      /* WWF3MK0 */
#define KS8692_WAN_FRAME3_MASK1    0x6064      /* WWF3MK1 */

#define KS8692_WAN_RX_IPG          0x6068      /* WMIPGL */

#define KS8692_WAN_BROADCAST_CNTL  0x60E4      /* WBTC */
#define KS8692_WAN_PKT_DROP        0x60E8      /* WPDC */
#define KS8692_WAN_CHECKSUM_DROP   0x60EC      /* WCEPDC */

#define KS8692_WAN_ACL_DATA1       0x6100      /* WACL1D */
#define KS8692_WAN_ACL_MASK1       0x6108      /* WACL1M */
#define KS8692_WAN_ACL_CONF1       0x6200      /* WACL1C */

#define KS8692_WAN_QOS_TOS0        0x6300      /* WDSPC0 */
#define KS8692_WAN_QOS_TOS1        (KS8692_WAN_QOS_TOS0+4)    /* WDSPC1 */
#define KS8692_WAN_QOS_TOS2        (KS8692_WAN_QOS_TOS1+4)    /* WDSPC2 */

#define KS8692_WAN_QOS_TAG         0x630C      /* WTPC */

/*
 * LAN DMA Registers
 * (Offset 0x8000 - 0x9FFF)
 */

#define LAN_BASE                   0x8000
#define KS8692_LAN_DMA_TX          0x8000      /* LMDTXC */
#define KS_LAN_DMA_TX              KS8692_LAN_DMA_TX
#define KS8692_LAN_DMA_RX          0x8004      /* LMDRXC */
#define KS8692_LAN_DMA_TX_START    0x8008      /* LMDTSC */
#define KS8692_LAN_DMA_RX_START    0x800C      /* LMDRSC */
#define KS8692_LAN_TX_LIST         0x8010      /* LTDLB */
#define KS8692_LAN_RX_LIST         0x8014      /* LRDLB */
#define KS8692_LAN_MAC_LOW         0x8018      /* LMAL */
#define KS8692_LAN_MAC_HIGH        0x801C      /* LMAH */

#define KS8692_LAN_MISC_CFG        0x8020      /* LEMC */
#define KS8692_LAN_RX_WATERMARK    0x8028      /* LMWTR */
#define	  LAN_HIGH_WATERMK_HP_MASK   0x1FF00000	   /* High watermark mask of high priority (22KB) */
#define	  LAN_HIGH_WATERMK_LP_MASK   0x0007FC00	   /* High watermark mask of low priority (19KB) */
#define	  LAN_LOW_WATERMARK_MASK     0x000001FF	   /* Low watermark mask (8KB) */

#define KS8692_LAN_MULTICAST_LO    0x802C      /* LMTRL */
#define KS8692_LAN_MULTICAST_HI    0x8030      /* LMTRH */

#define KS8692_LAN_WOL_CTRL        0x8034      /* LWFCR */

#define KS8692_LAN_FRAME0_CRC      0x8038      /* LWF0CRC */
#define KS8692_LAN_FRAME0_MASK0    0x803C      /* LWF0MK0 */
#define KS8692_LAN_FRAME0_MASK1    0x8040      /* LWF0MK1 */

#define KS8692_LAN_FRAME1_CRC      0x8044      /* LWF1CRC */
#define KS8692_LAN_FRAME1_MASK0    0x8048      /* LWF1MK0 */
#define KS8692_LAN_FRAME1_MASK1    0x804C      /* LWF1MK1 */

#define KS8692_LAN_FRAME2_CRC      0x8050      /* LWF2CRC */
#define KS8692_LAN_FRAME2_MASK0    0x8054      /* LWF2MK0 */
#define KS8692_LAN_FRAME2_MASK1    0x8058      /* LWF2MK1 */

#define KS8692_LAN_FRAME3_CRC      0x805C      /* LWF3CRC */
#define KS8692_LAN_FRAME3_MASK0    0x8060      /* LWF3MK0 */
#define KS8692_LAN_FRAME3_MASK1    0x8064      /* LWF3MK1 */

#define KS8692_LAN_RX_IPG          0x8068      /* LMIPGL */

#define KS8692_LAN_BROADCAST_CNTL  0x80E4      /* LBTC */
#define KS8692_LAN_PKT_DROP        0x80E8      /* LPDC */
#define KS8692_LAN_CHECKSUM_DROP   0x80EC      /* LCEPDC */

#define KS8692_LAN_ACL_DATA1       0x8100      /* LACL1D */
#define KS8692_LAN_ACL_MASK1       0x8108      /* LACL1M */
#define KS8692_LAN_ACL_CONF1       0x8200      /* LACL1C */

#define KS8692_LAN_QOS_TOS0        0x8300      /* LDSPC0 */
#define KS8692_LAN_QOS_TOS1        (KS8692_LAN_QOS_TOS0+4)    /* LDSPC1 */
#define KS8692_LAN_QOS_TOS2        (KS8692_LAN_QOS_TOS1+4)    /* LDSPC2 */

#define KS8692_LAN_QOS_TAG         0x830C      /* LTPC */

/*
 * WAN\LAN DMA Registers Offset
 *   WAN and LAN DMA register offset are the same,
 *   only the base address is different.
 *   We define the offset here to make easier for the driver.
 */

#if !defined( KS_PCI_BUS ) && !defined( KS_ISA_BUS )
#define	REG_DMA_TX_CTRL            0x0000
#define	  DMA_TX_CTRL_RESET          0x80000000		/* Enable DMA soft reset */
#define	  DMA_TX_CTRL_BURST_SIZE     0x3f000000		/* DMA Transmit Burst Size bit mask  */
#define   DMA_PBL_DEFAULT	         8	            /* DMA default burst size */	
#define	  DMA_TX_CTRL_CSUM_ICMP      0x00080000		/* Enable DMA ICMP Checksum generation */
#define	  DMA_TX_CTRL_CSUM_UDP       0x00040000		/* Enable DMA UDP Checksum generation */
#define	  DMA_TX_CTRL_CSUM_TCP       0x00020000		/* Enable DMA TCP Checksum generation */
#define	  DMA_TX_CTRL_CSUM_IP        0x00010000		/* Enable DMA_IP Checksum  generation */
#define	  DMA_TX_CTRL_FLOW_ENABLE    0x00000200		/* Enable DMA Transmit Flow Control */
#define	  DMA_TX_CTRL_LOOPBACK       0x00000100		/* Enable DMA Transmit loopback mode */
#define	  DMA_TX_CTRL_PAD_ENABLE     0x00000004		/* Enable DMA Transmit Padding */
#define	  DMA_TX_CTRL_CRC_ENABLE     0x00000002		/* Enable DMA Transmit Add CRC */
#define	  DMA_TX_CTRL_ENABLE         0x00000001		/* Enable DMA Transmit engine */

#define	REG_DMA_RX_CTRL            0x0004
#define   DMA_RX_CTRL_BURST_SIZE     0x3F000000     /* DMA Receive Burst Size bit mask  */
#define	  DMA_RX_CTRL_IP_ALIGN       0x00080000		/* Align DMA Receive IP header at DWORD boundary */
#define	  DMA_RX_CTRL_CSUM_UDP       0x00040000		/* Enable DMA UDP Checksum verification */
#define	  DMA_RX_CTRL_CSUM_TCP       0x00020000		/* Enable DMA TCP Checksum verification */
#define	  DMA_RX_CTRL_CSUM_IP        0x00010000		/* Enable DMA_IP Checksum  verification */
#define	  DMA_RX_CTRL_CSUM_ICMP      0x00008000		/* Enable DMA ICMP Checksum verification */
#define	  DMA_RX_CTRL_DROP_LO_PRI    0x00000400		/* Enable DMA Drop low priority packet during congestion */
#define   DMA_RX_CTRL_FLOW_ENABLE    0x00000200     /* Enable DMA Receive Flow Control */
#define	  DMA_RX_CTRL_BROADCAST      0x00000040		/* Enable DMA Receive Broadcast frames */
#define	  DMA_RX_CTRL_ALL_MULTICAST  0x00000020		/* Enable DMA Receive Multicast frames */
#define	  DMA_RX_CTRL_UNICAST        0x00000010		/* Enable DMA Receive Unicast frames */
#define	  DMA_RX_CTRL_ERROR          0x00000008		/* Enable DMA Receive Error frames */
#define	  DMA_RX_CTRL_PROMISCUOUS    0x00000004		/* Enable DMA Receive All frames, regatdless of its DA */
#define   DMA_RX_CTRL_MULTICAST      0x00000002     /* Enable DMA Receive multicast hash filtering */
#define   DMA_RX_CTRL_ENABLE         0x00000001     /* Enable DMA Receive engine */

#define	REG_DMA_TX_START           0x0008
#define	REG_DMA_RX_START           0x000c
#define	  DMA_START                  0x00000001		/* Start DMA Command */

#define	REG_DMA_TX_ADDR            0x0010
#define	REG_DMA_RX_ADDR            0x0014

#define	REG_DMA_MAC_ADDR_LO        0x0018
#define	REG_DMA_MAC_ADDR_HI        0x001c

#define REG_DMA_MISC_CFG           0x0020
#define	  MISC_RGMII_TX_DELAY        0x00008000	    /* Enable another 1.5ns delay to P0_TXC */
#define	  MISC_RGMII_RX_DELAY        0x00004000     /* Enable another 1.5ns delay to P0_RXC */
#define	  DMA_BLOCK_PACKET           0x00002000     /* Block all packets except packets match the configured data */
#define	  DMA_PHY_MII                0x00001000     /* Select PHY MII mode */
#define	  MISC_RGMII_SELECT          0x00000800		/* Select RGMII mode */
#define	  DMA_JUMBO_FRAME_SUPPORT    0x00000400		/* Enable support Jumbo frame (LAN port upto 9KB, WAN port upto 2000byte) */
#define	  DMA_FRAME_LEN_CHECK        0x00000200		/* Enable check frame length */
#define	  MISC_EXC_DEFER_ENABLE      0x00000100		/* Enable excessive defer */
#define	  MISC_RECEIVE_ENABLE        0x00000080		/* Enable PHY receive */
#define	  DMA_SHORTCUT_EN            0x00000040		/* Enable Shortcut slot time counter */
#define	  DMA_TX_HALFDUPLEX_CTRL2    0x00000020		/* Enable Tranmit half duplex flow control mode 2 */
#define	  DMA_NO_EXC_COLLISION       0x00000010		/* Enable No excessive collision */
#define	  DMA_TX_COLLISION_LIMIT4    0x00000008		/* Enable Tranmit collision limit 4 */
#define	  MISC_PORT_1000M            0x00000004		/* MAC speed 1000Mbps */
#define	  MISC_PORT_100M             0x00000002		/* MAC speed 100Mbps */
#define	  MISC_PORT_10M              0x00000000		/* MAC speed 10Mbps */
#define	  MISC_PORT_FD               0x00000001		/* MAC full duplex */
#define	  MISC_PORT_HD               0x00000000		/* MAC half duplex */
#define   DMA_LINK_MASK              0x00000007     /* Link (speed/duplex) mask */

#define REG_DMA_RX_WATERMARK       0x0028
#define   DMA_WATERMARK_BASE_BYTE    64

#define   WAN_HI_WATERMARK_HI_MASK   0x03F00000
#define   WAN_HI_WATERMARK_HI_SHIFT  20
#define   WAN_HI_WATERMARK_LO_MASK   0x0001FE00
#define   WAN_HI_WATERMARK_LO_SHIFT  10
#define   WAN_LO_WATERMARK_MASK      0x0000007F

#define   LAN_HI_WATERMARK_HI_MASK   0x0FF00000
#define   LAN_HI_WATERMARK_HI_SHIFT  20
#define   LAN_HI_WATERMARK_LO_MASK   0x0007FE00
#define   LAN_HI_WATERMARK_LO_SHIFT  10
#define   LAN_LO_WATERMARK_MASK      0x000001FF

#define REG_MULTICAST_0_OFFSET     0x002C
#define REG_MULTICAST_1_OFFSET     0x002D
#define REG_MULTICAST_2_OFFSET     0x002E
#define REG_MULTICAST_3_OFFSET     0x002F

#define REG_MULTICAST_4_OFFSET     0x0030
#define REG_MULTICAST_5_OFFSET     0x0031
#define REG_MULTICAST_6_OFFSET     0x0032
#define REG_MULTICAST_7_OFFSET     0x0033
#endif

#define REG_WOL_CTRL               0x0034
#define   WOL_MAGIC_ENABLE           0x00000080     /* Enable Receive Magic Packet detection */
#define   WOL_FRAME3_ENABLE          0x00000008     /* Enable Receive WOL Frame 3 pattern detection */
#define   WOL_FRAME2_ENABLE          0x00000004     /* Enable Receive WOL Frame 2 pattern detection */
#define   WOL_FRAME1_ENABLE          0x00000002     /* Enable Receive WOL Frame 1 pattern detection */
#define   WOL_FRAME0_ENABLE          0x00000001     /* Enable Receive WOL Frame 0 pattern detection */

#define REG_FRAME0_CRC             0x0038
#define REG_FRAME0_MASK0           0x003C
#define REG_FRAME0_MASK1           0x0040

#define REG_FRAME1_CRC             0x0044
#define REG_FRAME1_MASK0           0x0048
#define REG_FRAME1_MASK1           0x004C

#define REG_FRAME2_CRC             0x0050
#define REG_FRAME2_MASK0           0x0054
#define REG_FRAME2_MASK1           0x0058

#define REG_FRAME3_CRC             0x005C
#define REG_FRAME3_MASK0           0x0060
#define REG_FRAME3_MASK1           0x0064

#define REG_RX_IPG                 0x0068
#define	  DMA_GIGABIT_IPG_MASK       0x0000FF00	/* Gigabit ethernet rx IPG limit mask */
#define	  DMA_FAST_IPG_MASK          0x000000FF	/* Fast ethernet rx IPG limit mask */

#define REG_BROADCAST_CNTL         0x00E4
#define   DMA_BROADCAST_CNTL_EN      0x80000000     /* Enable WAN\LAN Broadcast Traffic Control */
#define   DMA_BROADCAST_RATE_MASK    0x000000FF     /* WAN\LAN Broadcast Traffic Control Preload mask */

#define REG_PKT_DROP               0x00E8
#define REG_CHECKSUM_DROP          0x00EC

#define REG_ACL_DATA1              0x0100
#define REG_ACL_MASK1              0x0108
#define REG_ACL_CONF1              0x0200
#define	  ACL_ENABLE                 0x80000000		/* Enable ACL */
#define	  ACL_IPV6                   0x40000000		/* ACL is on IPv6 */
#define	  ACL_MAC_SA                 0x20000000		/* ACL is for MAC SA address */
#define	  ACL_FILTER_EN              0x00080000		/* Enable ACL filter */
#define	  ACL_HI_PRIO                0x00010000		/* Hi priority packet if it match ACL pattern */
#define	  ACL_OFFSET_SCHEME          0x00008000		/* Offset address scheme is used for data match */
#define	  ACL_IPV6_SA                0x00004000		/* ACL for IPv6 128-bit source IP addr */
#define	  ACL_IPV6_DA                0x00002000		/* ACL for IPv6 128-bit destination IP addr */
#define	  ACL_PROTOCOL               0x00001000     /* ACL for 8-bit protocol field */
#define	  ACL_PORT_SA                0x00000800     /* ACL for 16-bit source port number */
#define	  ACL_PORT_DA                0x00000400     /* ACL for 16-bit destination port number */
#define	  ACL_IPV4_SA                0x00000200		/* ACL for IPv4 32-bit source IP addr */
#define	  ACL_IPV4_DA                0x00000100		/* ACL for IPv4 32-bit destination IP addr */
#define	  ACL_DATA_OFFSET_MASK       0x0000003F		/* Data offset address begin to match ACL pattern */

#define REG_QOS_TOS0               0x0300
#define REG_QOS_TOS1               (REG_QOS_TOS0+4)
#define REG_QOS_TOS2               (REG_QOS_TOS1+4)
#define	  QOS_TOS_ENABLE             0x00000001		/* Enable QoS IP Diff-Serv priority */

#define REG_QOS_TAG                0x030C
#define	  QOS_802_1P_ENABLE          0x00008000		/* Enable QoS 802.1p */

/*
 * WAN/LAN DMA Interrupts Bit definitions
 */

#if !defined( KS_PCI_BUS ) && !defined( KS_ISA_BUS )
#define   INT_RX_STOPPED             0x00000001
#define   INT_TX_STOPPED             0x00000002
#define   INT_RX_OVERRUN             0x00000004
#define   INT_TX_EMPTY               0x00000008
#define   INT_RX                     0x00000010
#define   INT_TX                     0x00000020

#define INT_CHECK                   ( INT_RX | INT_TX | INT_RX_OVERRUN | INT_TX_EMPTY | INT_RX_STOPPED | INT_TX_STOPPED )

/*
 * Receive Descriptors Registers
 *   RDES0\RDES1\RDES2\RDES3 Bit definitions
 */

/* RDES0 */
#define   DESC_HW_OWNED              0x80000000		/* shared with Tx descriptor */
#define   DESC_RX_FIRST              0x40000000		/* First Descriptor of the received frame */
#define   DESC_RX_LAST               0x20000000		/* Last Descriptor of the received frame */

#ifdef CONFIG_KSZ8692VA              /* for A1 chip */
#define   DESC_RX_MULTICAST          0x01000000		/* Multicast Frame */
#define   DESC_RX_ERROR              0x02000000		/* Error Summary */
#define   DESC_RX_ERROR_CSUM_UDP     0x04000000		/* UDP checksum error */
#define   DESC_RX_ERROR_CSUM_TCP     0x08000000		/* TCP checksum error */
#define   DESC_RX_ERROR_CSUM_IP      0x10000000		/* IP checksum error */

#else                                /* for A2 chip */
#define   DESC_RX_ERROR              0x10000000		/* Error Summary */
#define   DESC_RX_ERROR_CSUM_ICMP    0x08000000		/* ICMP checksum error */
#define   DESC_RX_ERROR_CSUM_UDP     0x06000000		/* UDP checksum error */
#define   DESC_RX_ERROR_CSUM_TCP     0x04000000		/* TCP checksum error */
#define   DESC_RX_ERROR_CSUM_IP      0x02000000		/* IP checksum error */
#define   DESC_RX_CSUM_NOT_DONE      0x01000000     /* IP/TCP/UDP/ICMP checksum not completed */
#define   DESC_RX_CSUM_CAUSE         0x00C00000     /* Checksum not completed cause by */
#endif /* #ifdef CONFIG_KSZ8692VA */

#define   DESC_RX_IP_ALIGN_3         0x00300000		/* Rx buffer shift data by 3-byte */
#define   DESC_RX_IP_ALIGN_2         0x00200000		/* Rx buffer shift data by 2-byte */
#define   DESC_RX_ERROR_PHY          0x00080000		/* Report on MII/GMII error */
#define   DESC_RX_ERROR_TOO_LONG     0x00040000		/* Frame Too Long */
#define   DESC_RX_ERROR_RUNT         0x00020000		/* Runt Frame */
#define   DESC_RX_ERROR_CRC          0x00010000		/* CRC error */
#define   DESC_RX_FRAME_TYPE         0x00008000		/* Frame Type */
#define   DESC_RX_HI_PRIORITY        0x00004000     /* Receive high priority packet */
#define   DESC_RX_FRAME_LEN          0x00003FFF     /* Frame Length bit mask, 0:13 */

#define   DESC_BUF_SIZE              0x00003FFF		
#define   DESC_RX_MASK               ( DESC_BUF_SIZE )


/* RDES1 */
#define   RFC_RER                    0x02000000		/* Receive End of Ring */
#define   RFC_RBS_MASK               0x00003FFF		/* Receive buffer Size bit mask, 0:13 */

/*
 * Transmit Descriptors Registers
 *   TDES0\TDES1\TDES2\TDES3 Bit definitions
 */

/* TDES1 */
#define   DESC_TX_INTERRUPT          0x80000000		/* Interrupt on completion */
#define   DESC_TX_FIRST              0x40000000		/* first segment */
#define   DESC_TX_LAST               0x20000000		/* last segment */
#define   DESC_TX_CSUM_GEN_IP        0x10000000		/* IP checksum generation */
#define   DESC_TX_CSUM_GEN_TCP       0x08000000		/* TCP checksum generation */
#define   DESC_TX_CSUM_GEN_UDP       0x04000000		/* UDP checksum generation */
#define   DESC_END_OF_RING           0x02000000		/* Transmit End of Ring */
#define   DESC_TX_CSUM_GEN_ICMP      0x01000000     /* ICMP checksum generation */

#define DESC_TX_MASK  ( DESC_TX_INTERRUPT | DESC_TX_FIRST | DESC_TX_LAST | \
                        DESC_TX_CSUM_GEN_IP  | DESC_TX_CSUM_GEN_TCP | \
                        DESC_TX_CSUM_GEN_ICMP | \
                        DESC_TX_CSUM_GEN_UDP | DESC_BUF_SIZE )
#endif


/*
 * SDIO Registers
 * (Offset 0xA000 - 0xAFFF)
 */

#define SDI_BASE                   0xA000
#define SDIO_HOST_BASE             0xA000		/* SDIO host controller base */

#if !defined( __KERNEL__ ) || defined( TEXT_BASE )
#define SDHCI_DMA_ADDRESS          0x00
#define SDHCI_BLOCK_SIZE           0x04
#define  SDHCI_MAKE_BLKSZ(dma, blksz) (((dma & 0x7) << 12) | (blksz & 0xFFF))

#define SDHCI_BLOCK_COUNT          0x06
#define SDHCI_ARGUMENT             0x08
#define SDHCI_TRANSFER_MODE        0x0C
#define  SDHCI_TRNS_DMA              0x01
#define  SDHCI_TRNS_BLK_CNT_EN       0x02
#define  SDHCI_TRNS_ACMD12           0x04
#define  SDHCI_TRNS_READ             0x10
#define  SDHCI_TRNS_MULTI            0x20

#define SDHCI_COMMAND              0x0E
#define  SDHCI_CMD_RESP_MASK         0x03
#define  SDHCI_CMD_CRC               0x08
#define  SDHCI_CMD_INDEX             0x10
#define  SDHCI_CMD_DATA              0x20
#define  SDHCI_CMD_SUSPEND           0x40
#define  SDHCI_CMD_RESUME            0x80
#define  SDHCI_CMD_ABORT             0xC0

#define  SDHCI_CMD_RESP_NONE         0x00
#define  SDHCI_CMD_RESP_LONG         0x01
#define  SDHCI_CMD_RESP_SHORT        0x02
#define  SDHCI_CMD_RESP_SHORT_BUSY   0x03

#define  SDHCI_MAKE_CMD(c, f) (((c & 0xff) << 8) | (f & 0xff))

#define SDHCI_RESPONSE             0x10
#define SDHCI_BUFFER               0x20
#define SDHCI_PRESENT_STATE        0x24
#define  SDHCI_CMD_INHIBIT           0x00000001
#define  SDHCI_DATA_INHIBIT          0x00000002
#define  SDHCI_DOING_WRITE           0x00000100
#define  SDHCI_DOING_READ            0x00000200
#define  SDHCI_SPACE_AVAILABLE       0x00000400
#define  SDHCI_DATA_AVAILABLE        0x00000800
#define  SDHCI_CARD_PRESENT          0x00010000
#define  SDHCI_WRITE_PROTECT         0x00080000

#define SDHCI_HOST_CONTROL         0x28
#define  SDHCI_CTRL_LED              0x01
#define  SDHCI_CTRL_4BITBUS          0x02
#define  SDHCI_CTRL_HISPD            0x04

#define SDHCI_POWER_CONTROL        0x29
#define  SDHCI_POWER_ON              0x01
#define  SDHCI_POWER_180             0x0A
#define  SDHCI_POWER_300             0x0C
#define  SDHCI_POWER_330             0x0E

#define SDHCI_BLOCK_GAP_CONTROL    0x2A

#define SDHCI_WALK_UP_CONTROL      0x2B

#define SDHCI_CLOCK_CONTROL        0x2C
#define  SDHCI_DIVIDER_SHIFT         8
#define  SDHCI_CLOCK_CARD_EN         0x0004
#define  SDHCI_CLOCK_INT_STABLE      0x0002
#define  SDHCI_CLOCK_INT_EN          0x0001

#define SDHCI_TIMEOUT_CONTROL      0x2E

#define SDHCI_SOFTWARE_RESET       0x2F
#define  SDHCI_RESET_ALL             0x01
#define  SDHCI_RESET_CMD             0x02
#define  SDHCI_RESET_DATA            0x04

#define SDHCI_INT_STATUS           0x30
#define SDHCI_INT_ENABLE           0x34
#define SDHCI_SIGNAL_ENABLE        0x38
#define  SDHCI_INT_RESPONSE          0x00000001
#define  SDHCI_INT_DATA_END          0x00000002
#define  SDHCI_INT_DMA_END           0x00000008
#define  SDHCI_INT_SPACE_AVAIL       0x00000010
#define  SDHCI_INT_DATA_AVAIL        0x00000020
#define  SDHCI_INT_CARD_INSERT       0x00000040
#define  SDHCI_INT_CARD_REMOVE       0x00000080
#define  SDHCI_INT_CARD_INT          0x00000100
#define  SDHCI_INT_TIMEOUT           0x00010000
#define  SDHCI_INT_CRC               0x00020000
#define  SDHCI_INT_END_BIT           0x00040000
#define  SDHCI_INT_INDEX             0x00080000
#define  SDHCI_INT_DATA_TIMEOUT      0x00100000
#define  SDHCI_INT_DATA_CRC          0x00200000
#define  SDHCI_INT_DATA_END_BIT      0x00400000
#define  SDHCI_INT_BUS_POWER         0x00800000
#define  SDHCI_INT_ACMD12ERR         0x01000000

#define  SDHCI_INT_BUF_EMPTY         SDHCI_INT_SPACE_AVAIL
#define  SDHCI_INT_BUF_FULL          SDHCI_INT_DATA_AVAIL


#define  SDHCI_INT_NORMAL_MASK       0x00007FFF
#define  SDHCI_INT_ERROR_MASK        0xFFFF8000

#define  SDHCI_INT_CMD_MASK	(SDHCI_INT_RESPONSE | SDHCI_INT_TIMEOUT | \
                             SDHCI_INT_CRC | SDHCI_INT_END_BIT | SDHCI_INT_INDEX)
#define  SDHCI_INT_DATA_MASK (SDHCI_INT_DATA_END | SDHCI_INT_DMA_END | \
                              SDHCI_INT_SPACE_AVAIL | SDHCI_INT_DATA_AVAIL | \
                              SDHCI_INT_DATA_TIMEOUT | SDHCI_INT_DATA_CRC | \
                              SDHCI_INT_DATA_END_BIT)

#define SDHCI_ACMD12_ERR           0x3C

/* 3E-3F reserved */

#define SDHCI_CAPABILITIES         0x40
#define  SDHCI_TIMEOUT_CLK_MASK      0x0000003F
#define  SDHCI_TIMEOUT_CLK_SHIFT     0
#define  SDHCI_TIMEOUT_CLK_UNIT      0x00000080
#define  SDHCI_TIMEOUT_CLK_SHIFT     0
#define  SDHCI_CLOCK_BASE_MASK       0x00003F00
#define  SDHCI_CLOCK_BASE_SHIFT      8
#define  SDHCI_MAX_BLOCK_MASK        0x00030000
#define  SDHCI_MAX_BLOCK_SHIFT       16
#define  SDHCI_CAN_DO_HISPD	         0x00200000
#define  SDHCI_CAN_DO_DMA            0x00400000
#define  SDHCI_CAN_VDD_330           0x01000000
#define  SDHCI_CAN_VDD_300	         0x02000000
#define  SDHCI_CAN_VDD_180	         0x04000000

/* 44-47 reserved for more caps */

#define SDHCI_MAX_CURRENT          0x48

/* 4C-4F reserved for more max current */

/* 50-FB reserved */
#define SDHCI_SLOT_INT_STATUS      0xFC
#define SDHCI_HOST_VERSION         0xFE
#define  SDHCI_VENDOR_VER_MASK       0xFF00
#define  SDHCI_VENDOR_VER_SHIFT      8
#define  SDHCI_SPEC_VER_MASK         0x00FF
#define  SDHCI_SPEC_VER_SHIFT        0
#endif

/*
 * USB Device Registers
 * (Offset 0xB000 - 0xBFFF)
 */

#define USB_DEVICE_BASE            0xB000
#define USB_DEV_REG_BASE           0x00000000       /* Base address of registers */

/*-----------------------------------------------*/
/* Defining base addresses for type of registers */
/*-----------------------------------------------*/

#define USB_DEV_AHB_EP_IN_BASE          USB_DEV_REG_BASE            /* Base Address for IN EP Registers */
#define USB_DEV_AHB_EP_OUT_BASE         (USB_DEV_REG_BASE + 0x0200) /* Base Address for OUT EP Registers */
#define USB_DEV_AHB_REG_BASE            (USB_DEV_REG_BASE + 0x0400) /* Base Address for AHB Subsys Registers */
#define USB_DEV_UDC_REG_BASE            (USB_DEV_REG_BASE + 0x0500) /* Base Address for UDC Registers */
#define USB_DEV_UDC_EP_BASE             (USB_DEV_REG_BASE + 0x0504) /* Base Address for EP Registers */

/*-----------------------------------*/
/* UDC-AHB Registers */
/*-----------------------------------*/

/* In Endpoint Registers */
/* EP IN Control Reg */
#define USB_DEV_EPIN_CTRL_REG(n)        ((int *)(USB_DEV_AHB_EP_IN_BASE + 0x00 + 0x20 * (n)))
/* EP IN Status Reg */
#define USB_DEV_EPIN_STS_REG(n)         ((int *)(USB_DEV_AHB_EP_IN_BASE + 0x04 + 0x20 * (n)))
/* EP IN BufferSize Reg*/
#define USB_DEV_EPIN_BUFFSIZE_REG(n)    ((int *)(USB_DEV_AHB_EP_IN_BASE + 0x08 + 0x20 * (n)))
/* EP IN Maxpkt Size Reg */
#define USB_DEV_EPIN_MAXSIZE_REG(n)     ((int *)(USB_DEV_AHB_EP_IN_BASE + 0x0C + 0x20 * (n)))
/* EP IN Data Desc Ptr Reg */
#define USB_DEV_EPIN_DATPTR_REG(n)      ((int *)(USB_DEV_AHB_EP_IN_BASE + 0x14 + 0x20 * (n)))

/* Out Endpoint Registers */
/* EP OUT Control Reg */
#define USB_DEV_EPOUT_CTRL_REG(n)       ((int *)(USB_DEV_AHB_EP_OUT_BASE + 0x00 + 0x20 * (n)))
/* EP OUT Status Reg */
#define USB_DEV_EPOUT_STS_REG(n)        ((int *)(USB_DEV_AHB_EP_OUT_BASE + 0x04 + 0x20 * (n)))
/* EP OUT Pkt Frame Num Reg */
#define USB_DEV_EPOUT_FRAME_REG(n)      ((int *)(USB_DEV_AHB_EP_OUT_BASE + 0x08 + 0x20 * (n)))
/* EP OUT Max Pkt Size Reg */
#define USB_DEV_EPOUT_MAXSIZE_REG(n)    ((int *)(USB_DEV_AHB_EP_OUT_BASE + 0x0C + 0x20 * (n)))
/* EP OUT Setup Buff Ptr Reg */
#define USB_DEV_EPOUT_SETUP_REG(n)      ((int *)(USB_DEV_AHB_EP_OUT_BASE + 0x10 + 0x20 * (n)))
/* EP OUT Data Desc Ptr Reg */
#define USB_DEV_EPOUT_DATPTR_REG(n)     ((int *)(USB_DEV_AHB_EP_OUT_BASE + 0x14 + 0x20 * (n)))
/* EP Out Bulk Out Pkt Len Register */
#define USB_DEV_EPOUT_BOPKT_LEN_REG(n)  ((int *)(USB_DEV_AHB_EP_OUT_BASE + 0x18 + 0x20 * (n)))

/* Different fields in the Enpoint Registers */
/* EP Control Register Fields */
#define USB_DEV_STALL                   0x00000001    /* EP Stall Bit */
#define USB_DEV_FLUSH                   0x00000002    /* EP In data fifo Flush */
#define USB_DEV_SNOOP                   0x00000004    /* EP Out Snoop Mode */
#define USB_DEV_PD                      0x00000008    /* EP Poll Demand */
#define USB_DEV_NAK                     0x00000040    /* EP NAK Status */
#define USB_DEV_SNAK                    0x00000080    /* EP Set NAK Bit */
#define USB_DEV_CNAK                    0x00000100    /* EP Clr NAK Bit */

/* USB EP Control Register */
#define USB_DEV_UDC_CTRL                0x00000000    /* EP Control */
#define USB_DEV_UDC_ISO                 0x00000020    /* EP Isoch */
#define USB_DEV_UDC_BULK                0x00000040    /* EP Bulk */
#define USB_DEV_UDC_INTR                0x00000060    /* EP Interrupt */

/* EP Status Register */
#define USB_DEV_IN                      0x00000040    /* EP In */
#define USB_DEV_BNA                     0x00000080    /* EP Buffer Not Available */
#define USB_DEV_HERR                    0x00000200    /* EP Host Error Response */
#define USB_DEV_TDC                     0x00000400    /* EP Transmit DMA Complete */
#define USB_DEV_OUT                     0x00000030    /* EP Receive Status */
#define USB_DEV_OUT_DATA                0x00000010    /* EP Receive Status */
#define USB_DEV_OUT_SETUP               0x00000020    /* EP Receive Status */
/* EP Bulk Out Pkt Len Reg */
#define USB_DEV_BO_PKTLEN_EN            0x80000000    /* Bulk Out Length Compare En */
#define USB_DEV_BO_PKTLEN               0x0000FFFF    /* Bulk Out Length */

/* Device Configuration Register */
#define USB_DEV_CFG_REG                 (int *)(USB_DEV_AHB_REG_BASE + 0x00)
#define USB_DEV_HS                      0x00000000    /* High Speed */
#define USB_DEV_FS                      0x00000001    /* Full Speed */
#define USB_DEV_LS                      0x00000002    /* Low Speed */
#define USB_DEV_8BIT_PI                 0x00000020    /* 8-bit Phy Interface */
#define USB_DEV_16BIT_PI                0x00000000    /* 16-bit Phy Interface */

#define USB_DEV_RWKP                    0x00000004
#define USB_DEV_SP                      0x00000008
#define USB_DEV_DIR                     0x00000040    /* Direction(1:bi-dir */
#define USB_DEV_SP                      0x00000008
#define USB_DEV_CSR_PRG                 0x00020000
#define USB_DEV_SET_DESC                0x00040000
#define USB_DEV_DDR                     0x00080000

/* Device Control Register */
#define USB_DEV_CTRL_REG                (int *)(USB_DEV_AHB_REG_BASE + 0x04)
#define USB_DEV_RDE                     0x00000004    /* Rx DMA Enable */
#define USB_DEV_TDE                     0x00000008    /* Tx DMA Enable */
#define USB_DEV_DU                      0x00000010    /* Desc. Update at the EOP */
#define USB_DEV_BF                      0x00000040    /* Buffer Fill Mode */
#define USB_DEV_THE                     0x00000080    /* Threshold Enable */
#define USB_DEV_BREN                    0x00000100    /* Burst Enable */
#define USB_DEV_DMODE                   0x00000200    /* DMA Mode */
#define USB_DEV_BRLEN                   0x00040000    /* Burst Length */
#define USB_DEV_THLEN                   0x08000000    /* Burst Length */

#define USB_DEV_RES                     0x00000001    /* Resuming signal */
#define USB_DEV_BE                      0x00000020    /* Big Endian mode */
#define USB_DEV_SD                      0x00000400    /* Soft disconnect */
#define USB_DEV_SCALE                   0x00000800    /* Scale down */

/* Device Status Register */
#define USB_DEV_STS_REG                 (int *)(USB_DEV_AHB_REG_BASE + 0x08)
#define USB_DEV_CFG                     0x0000000F    /* Config Field */
#define USB_DEV_INTF                    0x000000F0    /* Interface Field */
#define USB_DEV_ALT                     0x00000F00    /* Alternate Setting Field */
#define USB_DEV_SUSP                    0x00001000    /* Suspend Status Field */
#define USB_DEV_ENUM_SPD                0x00006000    /* Enumerated Speed */
#define USB_DEV_RXF_EMPTY               0x00008000    /* Rx FIFO Empty */
#define USB_DEV_TS                      0xFFFC0000    /* Frame Num of the rcvd SOF */
#define USB_DEV_ENUM_DONE               0x00020000    /* Enum Done Software driven/
							 not present in hardware */

#define USB_DEV_ENUM_SPD_HS             0x00000000    /* Enumerated High Speed */
#define USB_DEV_ENUM_SPD_FS             0x00002000    /* Enumerated Full Speed */
#define USB_DEV_ENUM_SPD_LS             0x00004000    /* Enumerated Low Speed */

/* Device Intr Register */
#define USB_DEV_INTR_REG                (int *)(USB_DEV_AHB_REG_BASE + 0x0C)

/* Device Intr Mask Register */
#define USB_DEV_INTR_MASK_REG           (int *)(USB_DEV_AHB_REG_BASE + 0x10)

/* Rcvd Set Configuration Command */
#define USB_DEV_SC                      0x00000001	  /* Rcvd Set Interface Command */
#define USB_DEV_SI                      0x00000002    /* IDLE > 3ms Detected */
#define USB_DEV_ES                      0x00000004    /* Rcvd SOF */
#define USB_DEV_UR                      0x00000008	  /* Rcvd USB Reset */
#define USB_DEV_US                      0x00000010	  /* Rcvd Suspend Detected */
#define USB_DEV_SOF                     0x00000020	  /* Rcvd SOF */
#define USB_DEV_ENUM                    0x00000040	  /* Speed enumeration is complete */
/* Enable all the intrs */
#define USB_DEV_INTR_MASK               ( USB_DEV_UR | USB_DEV_SI | USB_DEV_SC | USB_DEV_ENUM | USB_DEV_US )

/* EndPoint Intr Register */
#define USB_DEV_EP_INTR_REG             (int *)(USB_DEV_AHB_REG_BASE + 0x14)

/* Endpoint Intr Mask Register */
#define USB_DEV_EP_INTR_MASK_REG        (int *)(USB_DEV_AHB_REG_BASE + 0x18)

#if 0
#define USB_DEV_CNTL_IN_INTR            0x00000001    /* Ctrl In Intr */
#define USB_DEV_CNTL_OUT_INTR           0x00010000    /* Ctrl Out Intr */
#define USB_DEV_BULK_IN_INTR            0x00000002    /* Bulk In Intr */
#define USB_DEV_BULK_OUT_INTR           0x00040000    /* Bulk Out Intr */
#define USB_DEV_INTR_IN_INTR            0x00000008    /* Intr In Intr */
#define USB_DEV_IN_EP_INTR              ( USB_DEV_CNTL_IN_INTR | USB_DEV_BULK_IN_INTR |  USB_DEV_INTR_IN_INTR )
#define USB_DEV_OUT_EP_INTR             ( USB_DEV_CNTL_OUT_INTR | USB_DEV_BULK_OUT_INTR )
#endif

/* Device Descriptor/Setup Command address register */
#define USB_DEV_UDC_SETUP_CMD           USB_DEV_UDC_REG_BASE

/* EndPoint Information registers */
#define USB_DEV_UDC_EP_INFO(n)          ((int *)(USB_DEV_UDC_EP_BASE + 0x04 * (n)))
#define USB_DEV_EPNUM_0                 0x00000000    /* Endpoint Number Field = 0 */
#define USB_DEV_EPNUM_1                 0x00000001    /* Endpoint Number Field = 1 */
#define USB_DEV_EPNUM_2                 0x00000002    /* Endpoint Number Field = 2 */
#define USB_DEV_EPNUM_3                 0x00000003    /* Endpoint Number Field = 3 */
#define USB_DEV_EPIN                    0x00000010    /* Endpoint In Direction */
#define USB_DEV_EPOUT                   0x00000000    /* Endpoint Out Direction */
#define USB_DEV_AHB_INTR                0x00000030    /* Interrupt Endpoint */
#define USB_DEV_AHB_BULK                0x00000020    /* Bulk Endpoint */
#define USB_DEV_AHB_ISO                 0x00000010    /* Isochronous Endpoint */
#define USB_DEV_AHB_CTRL                0x00000000    /* Control Endpoint */
#define USB_DEV_CONFNUM_0               0x00000000    /* Configuration Number of the EP = 0 */
#define USB_DEV_CONFNUM_1               0x00000080    /* Configuration Number of the EP = 1 */
#define USB_DEV_INTFNUM_0               0x00000000    /* Interface Number of the EP */
#define USB_DEV_ALTNUM_0                0x00000000    /* Alt. setting of the EP */
#define USB_DEV_MAXPKTSIZE_SHIFT        28            /* Max Pkt Size of the EP */
#define MAX_PKT_SIZE_UDC_REG            0x02000000    /* Max Pkt size field to be programmed into
							 the UDC registers */

/* Setup Status */
#define USB_DEV_CONFG_STS               0x0FFF0000    /* Current Configuration Status */
#define USB_DEV_CONF_NUM                0x0F000000    /* Configuration Number Received */
#define USB_DEV_INTF_NUM                0x00F00000    /* Interface Number Received */
#define USB_DEV_ALT_NUM                 0x000F0000    /* Alternate Setting Number Received */

/* DMA Related Definitions */

/* Description of the status quadlets */
#define USB_DEV_BUFF_STS                0xC0000000    /* Buffer Status */
#define USB_DEV_BS_HST_RDY              0x00000000    /* 2'b00 : Host Ready */
#define USB_DEV_BS_DMA_BSY              0x40000000    /* 2'b01 : DMA Busy */
#define USB_DEV_BS_DMA_DONE             0x80000000    /* 2'b10 : DMA Done */
#define USB_DEV_BS_HST_BSY              0xC0000000    /* 2'b11 : Host Busy */

#define USB_DEV_RXTX_STS                0x30000000    /* Receive or Transmit Status */
#define USB_DEV_RTS_SUCC                0x00000000    /* 2'b00 : Success */
#define USB_DEV_RTS_DESERR              0x10000000    /* 2'b01 : Descriptor Error */
#define USB_DEV_RTS_BUFERR              0x30000000    /* 2'b11 : Buffer Error */

/* Transmit Receive DMA Descriptor Status */
#define USB_DEV_LAST                    0x08000000    /* Last Descriptor Indication */
#define USB_DEV_RXTX_BYTES              0x0000FFFF    /* Number of Bytes either xmited or rcvd */


/*
 * USB EHCI Registers
 * (Offset 0xC000 - 0xCFFF)
 */

#define USB_EHCI_BASE              0xC000

/*
 * USB OHCI Registers
 * (Offset 0xD000 - 0xDFFF)
 */

#define USB_OHCI_BASE              0xD000

/*
 * Nand Flash Control Registers
 *  base address : NFLCFG[28:16]
 * (Offset 0x0000 - 0x7FFF)
 */

#define KS8692_NAND_DATA           0x0000      /* NFLD */
#define KS8692_NAND_COMMAND        0x8000      /* NFLC */

#if !defined( __KERNEL__ ) || defined( TEXT_BASE )
#define   NAND_CMD_READ              0x00000000    /* Read command */
#define   NAND_CMD_RESET             0x000000FF    /* Reset command */
#define   NAND_CMD_READ_ID           0x00000090    /* Read ID command */
#define   NAND_CMD_PAGE              0x00000080    /* Page program command */
#define   NAND_CMD_PAGE_CONFIRM      0x00000010    /* Page program confirm command */
#define   NAND_CMD_READ_STATUS       0x00000070    /* Read status command */
#define   NAND_CMD_ERASE             0x00000060    /* Block erase command */
#define   NAND_CMD_ERASE_CONFIRM     0x000000D0    /* Block erase confirm command */
#endif
#define   NAND_CMD_CE_OFF            0x000000EE    /* Turn of CE single to the flash after read */
#define   NAND_CMD_BANK_0            0x00000000
#define   NAND_CMD_BANK_1            0x00000100
#define   NAND_CMD_BANK_2            0x00000200
#define   NAND_CMD_BANK_3            0x00000300
#define   NAND_CMD_BANK_SHIFT        8

#define KS8692_NAND_INDEX          0x8004      /* NFLI */
#define   NAND_INDEX_MASK            0x000000FF    /* Nand flash index register mask */

#define KS8692_NAND_STATUS         0x8008      /* NFLS */
#define   NAND_STAT_CHIP3_MASK       0xFF000000    /* Nand flash chip3 status mask */
#define   NAND_STAT_CHIP2_MASK       0x00FF0000    /* Nand flash chip2 status mask */
#define   NAND_STAT_CHIP1_MASK       0x0000FF00    /* Nand flash chip1 status mask */
#define   NAND_STAT_CHIP0_MASK       0x000000FF    /* Nand flash chip0 status mask */

#define KS8692_NAND_ID0            0x8010      /* NFLID0 */
#define   NAND_MAKER_CODE3_MASK      0xFF000000    /* Nand flash chip3 ID (maker code) mask */
#define   NAND_MAKER_CODE2_MASK      0x00FF0000    /* Nand flash chip2 ID (maker code) mask */
#define   NAND_MAKER_CODE1_MASK      0x0000FF00    /* Nand flash chip1 ID (maker code) mask */
#define   NAND_MAKER_CODE0_MASK      0x000000FF    /* Nand flash chip0 ID (maker code) mask */

#define KS8692_NAND_ID1            0x8018      /* NFLID1 */
#define   NAND_DEVICE_CODE3_MASK     0xFF000000    /* Nand flash chip3 (device code) mask */
#define   NAND_DEVICE_CODE2_MASK     0x00FF0000    /* Nand flash chip2 (device code) mask */
#define   NAND_DEVICE_CODE1_MASK     0x0000FF00    /* Nand flash chip1 (device code) mask */
#define   NAND_DEVICE_CODE0_MASK     0x000000FF    /* Nand flash chip0 (device code) mask */

#define KS8692_NAND_ID2            0x8020      /* NFLID2 */
#define   NAND_ID_CHIP3_MASK         0xFF000000    /* Nand flash 3rd byte ID of chip3 mask */
#define   NAND_ID_CHIP2_MASK         0x00FF0000    /* Nand flash 3rd byte ID of chip2 mask */
#define   NAND_ID_CHIP1_MASK         0x0000FF00    /* Nand flash 3rd byte ID of chip1 mask */
#define   NAND_ID_CHIP0_MASK         0x000000FF    /* Nand flash 3rd byte ID of chip0 mask */

#define KS8692_NAND_ID3            0x8028      /* NFLID2 */
#define   NAND_PLANE_CODE3_MASK      0xFF000000    /* Nand flash chip3 (Multi plane code ID) mask */
#define   NAND_PLANE_CODE2_MASK      0x00FF0000    /* Nand flash chip2 (Multi plane code ID) mask */
#define   NAND_PLANE_CODE1_MASK      0x0000FF00    /* Nand flash chip1 (Multi plane code ID) mask */
#define   NAND_PLANE_CODE0_MASK      0x000000FF    /* Nand flash chip0 (Multi plane code ID) mask */

#define KS8692_NAND_EXT_INDEX      0x8048      /* NFLEI */
#define   NAND_EXT_INDEX_MASK        0x000000FF    /* Nand flash extended index register mask */

#define KS8692_NAND_TIMING_CNTL0   0x804C      /* NFLTC0 */
#define   NAND_HOLD_TIME_MASK        0xFF000000    /* Nand flash CLE/CE#/ALE hold time after WE# mask */
#define   NAND_READ_PULSE_MASK       0x00FF0000    /* Nand flash RE# pulse width mask */
#define   NAND_WRITE_PULSE_MASK      0x0000FF00    /* Nand flash WE# pulse width mask */
#define   NAND_SETUP_TIME_MASK       0x000000FF    /* Nand flash CLE/CE#/ALE setup time to WE#/RE# mask */

#define KS8692_NAND_TIMING_CNTL1   0x8050      /* NFLTC1 */
#define   NAND_WRITE_RAISING_MASK    0xFF000000    /* Nand flash WE# raising edge to RY/BY# falling edge mask */
#define   NAND_BUSY_RAISING_MASK     0x00FF0000    /* Nand flash RY/BY# raising edge to RE# pluse falling edge mask */
#define   NAND_READ_PULSE_HI_MASK    0x0000FF00    /* Nand flash RE# pluse high time mask */
#define   NAND_WRITE_PULSE_HI_MASK   0x000000FF    /* Nand flash WE# pluse high time mask */

#define KS8692_NAND_CONF           0x8054      /* NFLC */
#define   NAND_LARGE_BLOCK           0x00000100    /* Nand flash is in large block */
#define   NAND_4_BANK                0x00000080    /* 4 active Nand flash banks in cascade */
#define   NAND_2_BANK                0x00000040    /* 2 active Nand flash banks in cascade */
#define   NAND_1_BANK                0x00000000    /* 1 active Nand flash banks in cascade */
#define   NAND_4_FLASH               0x00000020    /* 4 NAND flash in parallel for combined */
#define   NAND_2_FLASH               0x00000010    /* 2 NAND flash in parallel for combined */
#define   NAND_1_FLASH               0x00000000    /* 1 NAND flash in parallel for combined */
#define   NAND_WIDTH_16BIT           0x00000008    /* NAND flash data width is 16-bit */
#define   NAND_WIDTH_8BIT            0x00000000    /* NAND flash data width is 8-bit */
#define   NAND_SIZE_8GBIT            0x00000007    /* NAND flash size is 8Gbit */
#define   NAND_SIZE_4GBIT            0x00000006    /* NAND flash size is 4Gbit */
#define   NAND_SIZE_2GBIT            0x00000005    /* NAND flash size is 2Gbit */
#define   NAND_SIZE_1GBIT            0x00000004    /* NAND flash size is 1Gbit */
#define   NAND_SIZE_512MBIT          0x00000003    /* NAND flash size is 512MGbit */
#define   NAND_SIZE_256MBIT          0x00000002    /* NAND flash size is 256MGbit */
#define   NAND_SIZE_128MBIT          0x00000001    /* NAND flash size is 128MGbit */
#define   NAND_SIZE_64MBIT           0x00000000    /* NAND flash size is 64MGbit */


/*
 * UART Registers
 * (Offset 0xE000 - 0xE1FF)
 */

#define SYSCFG2_BASE                0xE000

#define KS_UART_RX_BUFFER           0x00
#define KS_UART_TX_HOLDING          0x04
#define KS_UART_FIFO_CTRL           0x08
#define KS_UART_LINE_CTRL           0x0C
#define KS_UART_MODEM_CTRL          0x10
#define KS_UART_LINE_STATUS         0x14
#define KS_UART_MODEM_STATUS        0x18
#define KS_UART_DIVISOR             0x1C
#define KS_UART_STATUS              0x20

#define KS8692_UART1_RX_BUFFER     0xE000      /* UR1RB */
#define   UART_RX_DATA_MASK          0x000000FF    /* 1-Byte data mask */

#define KS8692_UART1_TX_HOLDING    0xE004      /* UR1TH */

#define KS8692_UART1_FIFO_CTRL     0xE008      /* UR1FC */
#define   UART_FIFO_TRIG_24BYTE      0x0000000C    /* 24-Byte trigger level */
#define   UART_FIFO_TRIG_16BYTE      0x00000008    /* 16-Byte trigger level */
#define   UART_FIFO_TRIG_8BYTE       0x00000004    /* 8-Byte trigger level */
#define   UART_FIFO_TRIG_1BYTE       0x00000000    /* 1-Byte trigger level */
#define   UART_FIFO_TX_RESET         0x00000004    /* Reset UART Transmit FIFO */
#define   UART_FIFO_RX_RESET         0x00000002    /* Reset UART Receive FIFO */
#define   UART_FIFO_ENABLE           0x00000001    /* Enable UART FIFO */

#define KS8692_UART1_LINE_CTRL     0xE00C      /* UR1LC */
#define   UART_LINEC_TX_FLOWCTRL     0x00000200    /* Enable tx flow control */
#define   UART_LINEC_RX_FLOWCTRL     0x00000100    /* Enable rx flow control */
#define   UART_LINEC_BREAK           0x00000040    /* Set Break Condition on UTXD */
#define   UART_LINEC_STICK_PARITY    0x00000020    /* Enable Stick parity */
#define   UART_LINEC_EVEN_PARITY     0x00000010    /* Enable Even parity */
#define   UART_LINEC_ODD_PARITY      0x00000000    /* Enable Odd parity */
#define   UART_LINEC_PARITY_EN       0x00000008    /* Enable parity check */
#define   UART_LINEC_2STOP_BIT       0x00000004    /* 2 Stop bit */
#define   UART_LINEC_1STOP_BIT       0x00000000    /* 1 Stop bit */
#define   UART_LINEC_8DATA_BIT       0x00000003    /* 8 Data bit */
#define   UART_LINEC_7DATA_BIT       0x00000002    /* 7 Data bit */
#define   UART_LINEC_6DATA_BIT       0x00000001    /* 6 Data bit */
#define   UART_LINEC_5DATA_BIT       0x00000000    /* 5 Data bit */
#define   UART_LINEC_BAUD_RATE_MASK  0x00000003    /* Baud rate mask */

#define KS8692_UART1_MODEM_CTRL    0xE010      /* UR1MC */
#define   UART_ENABLE                0x00000080    /* Enable UART */
#define   UART_CLOCK_166MHZ          0x00000060    /* Select UART clock as 166MHz */
#define   UART_CLOCK_125MHZ          0x00000040    /* Select UART clock as 125MHz */
#define   UART_CLOCK_62_5MHZ         0x00000020    /* Select UART clock as 62.5MHz */
#define   UART_CLOCK_25MHZ           0x00000000    /* Select UART clock as 25MHz  */
#define   UART_LOOPBACK              0x00000010    /* SeT UART in loopback mode  */
#define   UART_OUT2_ASSERT_LOW       0x00000008    /* SeT UART OUT2 signal is asserted to 0 */
#define   UART_OUT1_ASSERT_LOW       0x00000004    /* SeT UART OUT1 signal is asserted to 0 */

#define KS8692_UART1_LINE_STATUS   0xE014      /* UR1LS */
#define   UART_LINES_RX_FIFO_MASK    0x00003F00    /* UART Receive FIFO available data mask */
#define   UART_LINES_RX_FIFO_ERR     0x00000080    /* UART Receive FIFO Error */
#define   UART_LINES_TX_EMPTY        0x00000040    /* UART Transmit Empty */
#define   UART_LINES_TX_HOLD_EMPTY   0x00000020    /* UART Transmit Holding Register Empty */
#define   UART_LINES_RX_BREAK_ERR    0x00000010    /* UART Break Condition occurs on the URXD pin */
#define   UART_LINES_RX_FRAME_ERR    0x00000008    /* UART Receive Frame Error */
#define   UART_LINES_RX_PARITY_ERR   0x00000004    /* UART Receive Parity Error */
#define   UART_LINES_RX_OVERRUN_ERR  0x00000002    /* UART Receive Overrun Error */
#define   UART_LINES_RX_READY        0x00000001    /* UART Receive Data Ready */
#define   UART_RX_ERRORS             (UART_LINES_RX_BREAK_ERR|UART_LINES_RX_FRAME_ERR|UART_LINES_RX_PARITY_ERR|UART_LINES_RX_OVERRUN_ERR)

#define KS8692_UART1_MODEM_STATUS  0xE018      /* UR1MS */
#define   UART_MODEM_DCD             0x00000080    /* UART Data Carrier Detect */
#define   UART_MODEM_RI              0x00000040    /* UART Ring Indicator */
#define   UART_MODEM_DSR             0x00000020    /* UART Data Set Ready */
#define   UART_MODEM_CTS             0x00000010    /* UART Clear To Send */
#define   UART_MODEM_DDCD            0x00000008    /* UART Delta Data Carrier Detect */
#define   UART_MODEM_TERI            0x00000004    /* UART Trailing Edge ring Indicator */
#define   UART_MODEM_DDSR            0x00000002    /* UART Delta Data Set Ready */
#define   UART_MODEM_DCTS            0x00000001    /* UART Delta Clear To Send */
#define   UART_MODEM_STATUS_CHANGE   (UART_MODEM_DDCD|UART_MODEM_DDSR|UART_MODEM_DCTS) /* UART Modem Status Change mask */

#define KS8692_UART1_DIVISOR       0xE01C     /* UR1BD */
#define   UART_DIVISOR_MASK          0x07FFFFFF    /* UART baud rate divisor count mask */

#define KS8692_UART1_STATUS        0xE020     /* US1R  */
#define   UART_INT_TIMEOUT          0x00000001    /* UART interrupt from timeout */

#define KS8692_UART2_RX_BUFFER     (KS8692_UART1_RX_BUFFER+0x80)     /* UR2RB */
#define KS8692_UART2_TX_HOLDING    (KS8692_UART1_TX_HOLDING+0x80)    /* UR2TH */
#define KS8692_UART2_FIFO_CTRL     (KS8692_UART1_FIFO_CTRL+0x80)     /* UR2FC */
#define KS8692_UART2_LINE_CTRL     (KS8692_UART1_LINE_CTRL+0x80)     /* UR2LC */
#define KS8692_UART2_MODEM_CTRL    (KS8692_UART1_MODEM_CTRL+0x80)    /* UR2MC */
#define KS8692_UART2_LINE_STATUS   (KS8692_UART1_LINE_STATUS+0x80)   /* UR2LS */
#define KS8692_UART2_MODEM_STATUS  (KS8692_UART1_MODEM_STATUS+0x80)  /* UR2MS */
#define KS8692_UART2_DIVISOR       (KS8692_UART1_DIVISOR+0x80)       /* UR2BD */
#define KS8692_UART2_STATUS        (KS8692_UART1_STATUS+0x80)        /* US2R  */

#define KS8692_UART3_RX_BUFFER     (KS8692_UART2_RX_BUFFER+0x80)     /* UR3RB */
#define KS8692_UART3_TX_HOLDING    (KS8692_UART2_TX_HOLDING+0x80)    /* UR3TH */
#define KS8692_UART3_FIFO_CTRL     (KS8692_UART2_FIFO_CTRL+0x80)     /* UR3FC */
#define KS8692_UART3_LINE_CTRL     (KS8692_UART2_LINE_CTRL+0x80)     /* UR3LC */
#define KS8692_UART3_MODEM_CTRL    (KS8692_UART2_MODEM_CTRL+0x80)    /* UR3MC */
#define KS8692_UART3_LINE_STATUS   (KS8692_UART2_LINE_STATUS+0x80)   /* UR3LS */
#define KS8692_UART3_MODEM_STATUS  (KS8692_UART2_MODEM_STATUS+0x80)  /* UR3MS */
#define KS8692_UART3_DIVISOR       (KS8692_UART2_DIVISOR+0x80)       /* UR3BD */
#define KS8692_UART3_STATUS        (KS8692_UART2_STATUS+0x80)        /* US3R  */

#define KS8692_UART4_RX_BUFFER     (KS8692_UART3_RX_BUFFER+0x80)     /* UR4RB */
#define KS8692_UART4_TX_HOLDING    (KS8692_UART3_TX_HOLDING+0x80)    /* UR4TH */
#define KS8692_UART4_FIFO_CTRL     (KS8692_UART3_FIFO_CTRL+0x80)     /* UR4FC */
#define KS8692_UART4_LINE_CTRL     (KS8692_UART3_LINE_CTRL+0x80)     /* UR4LC */
#define KS8692_UART4_MODEM_CTRL    (KS8692_UART3_MODEM_CTRL+0x80)    /* UR4MC */
#define KS8692_UART4_LINE_STATUS   (KS8692_UART3_LINE_STATUS+0x80)   /* UR4LS */
#define KS8692_UART4_MODEM_STATUS  (KS8692_UART3_MODEM_STATUS+0x80)  /* UR4MS */
#define KS8692_UART4_DIVISOR       (KS8692_UART3_DIVISOR+0x80)       /* UR4BD */
#define KS8692_UART4_STATUS        (KS8692_UART3_STATUS+0x80)        /* US4R  */

/*
 * Interrupt Controller Registers
 * (Offset 0xE200 - 0xE3FF)
 */

#define KS8692_INT_CONTL1           0xE200     /* INTMC  */
#define KS8692_INT_CONTL2           0xE204     /* INTMC2 */

#define KS8692_INT_ENABLE1          0xE208     /* INTEN  */
#define KS_INT_ENABLE               KS8692_INT_ENABLE1
#define	  INT_WAN_TX                  0x40000000	/* WAN Tx complete interrupt */
#define	  INT_WAN_RX                  0x20000000	/* WAN Rx complete interrupt */
#define	  INT_WAN_TX_UNAVIAL          0x10000000	/* WAN Tx desc unavailable interrupt */
#define	  INT_WAN_RX_UNAVIAL          0x08000000	/* WAN Rx desc unavailable interrupt */
#define	  INT_WAN_TX_STOPPED          0x04000000	/* WAN Tx stopped interrupt */
#define	  INT_WAN_RX_STOPPED          0x02000000	/* WAN Rx stopped interrupt */
#define	  INT_AMBA_BUS_ERROR          0x01000000	/* AMBA bus error interrupt */
#define	  INT_WAN_WOL                 0x00080000	/* WAN Wake-up interrupt */
#define	  INT_LAN_WOL                 0x00040000	/* LAN Wake-up interrupt */
#define	  INT_LAN_TX                  0x00020000	/* LAN Tx complete interrupt */
#define	  INT_LAN_RX                  0x00010000	/* LAN Rx complete interrupt */
#define	  INT_LAN_TX_UNAVAIL          0x00008000	/* LAN Tx desc unavailable interrupt */
#define	  INT_LAN_RX_UNAVAIL          0x00004000	/* LAN Rx desc unavailable interrupt */
#define	  INT_LAN_TX_STOPPED          0x00002000	/* LAN Tx stopped interrupt */
#define	  INT_LAN_RX_STOPPED          0x00001000	/* LAN Rx stopped interrupt */
#define	  INT_USB_DEVICE              0x00000400	/* USB Device interrupt */
#define	  INT_USB_HOST_OHCI           0x00000200	/* USB Host OHCI interrupt */
#define	  INT_USB_HOST_EHCI           0x00000100	/* USB Host EHCI interrupt */
#define	  INT_SDIO                    0x00000080	/* SDIO interrupt */
#define	  INT_IPSEC                   0x00000040	/* IPSec interrupt */
#define	  INT_DDR_SDR_ERR             0x00000020	/* DDR or SDR memory interrupt */
#define	  INT_WAN_MASK                0x68000000	/* WAN Interrupt mask bit */
#define	  INT_LAN_MASK                0x00034000    /* LAN Interrupt mask bit */
#define	  INT_DMA_MASK                (INT_WAN_MASK | INT_LAN_MASK) /* interrupt bit mask for DMA (WAN, LAN) */

#define KS8692_INT_ENABLE2          0xE20C     /* INTEN2 */
#define   INT_UART4_LINE              0x02000000    /* UART4 Line Status interrupt */
#define   INT_UART4_RX                0x01000000    /* UART4 Receiver trigger level interrupt */
#define   INT_UART4_TX                0x00800000    /* UART4 Transmitter empty interrupt */
#define   INT_UART3_LINE              0x00400000    /* UART3 Line Status interrupt */
#define   INT_UART3_RX                0x00200000    /* UART3 Receiver trigger level interrupt */
#define   INT_UART3_TX                0x00100000    /* UART3 Transmitter empty interrupt */
#define   INT_UART2_LINE              0x00080000    /* UART2 Line Status interrupt */
#define   INT_UART2_RX                0x00040000    /* UART2 Receiver trigger level interrupt */
#define   INT_UART2_TX                0x00020000    /* UART2 Transmitter empty interrupt */
#define   INT_UART1_MODEM             0x00010000    /* UART1 Modem interrupt */
#define   INT_UART1_LINE              0x00008000    /* UART1 Line Status interrupt */
#define   INT_UART1_RX                0x00004000    /* UART1 Receiver trigger level interrupt */
#define   INT_UART1_TX                0x00002000    /* UART1 Transmitter empty interrupt */
#define   INT_MDIO                    0x00001000    /* MDIO interrupt */
#define   INT_SPI                     0x00000800    /* SPI interrupt */
#define   INT_I2S_TX                  0x00000400    /* I2S Transmit interrupt */
#define   INT_I2S_RX                  0x00000200    /* I2S Receive interrupt */
#define   INT_I2C                     0x00000100    /* I2C interrupt */
#define   INT_TIMER1                  0x00000080    /* Timer1 interrupt */
#define   INT_TIMER0                  0x00000040    /* Timer2 interrupt */
#define   INT_EXTERNAL3               0x00000020    /* External interrupt 3 */
#define   INT_EXTERNAL2               0x00000010    /* External interrupt 2 */
#define   INT_EXTERNAL1               0x00000008    /* External interrupt 1 */
#define   INT_EXTERNAL0               0x00000004    /* External interrupt 0 */
#define   INT_CHANNEL_TX              0x00000002    /* Communications Transmit interrupt */
#define   INT_CHANNEL_RX              0x00000001    /* Communications Receive interrupt */
#define   INT_UART4_MASK              0x03800000    /* UART4 Interrupt mask */
#define   INT_UART3_MASK              0x00700000    /* UART3 Interrupt mask */
#define   INT_UART2_MASK              0x000E0000    /* UART2 Interrupt mask */
#define   INT_UART1_MASK              0x0001E000    /* UART1 Interrupt mask */


#define KS8692_INT_STATUS1          0xE210     /* INTST  */
#define KS_INT_STATUS               KS8692_INT_STATUS1
#define KS8692_INT_STATUS2          0xE214     /* INTST2 */

#define KS8692_INT_WAN_PRIORITY     0xE218     /* INTPW  */

#define KS8692_INT_BUSERROR_PRO     0xE21C     /* INTPBE */

#define KS8692_INT_LAN_PRIORITY     0xE220     /* INTPL  */

#define KS8692_INT_USB_PRIORITY     0xE224     /* INTPUSB */

#define KS8692_INT_SDIO_PRIORITY    0xE228     /* INTPSDIO */

#define KS8692_INT_IPSEC_PRIORITY   0xE22C     /* INTPIPSEC */

#define KS8692_INT_DDR_PRIORITY     0xE230     /* INTPDDR */

#define KS8692_INT_UART1_PRIORITY   0xE234     /* INTPU  */
#define KS8692_INT_UART2_PRIORITY   0xE238     /* INTPU2 */

#define KS8692_INT_MDIO_PRIORITY    0xE23C     /* INTPMDIO */

#define KS8692_INT_SPI_PRIORITY     0xE240     /* INTPSPI */

#define KS8692_INT_I2S_PRIORITY     0xE244     /* INTPI2S */

#define KS8692_INT_I2C_PRIORITY     0xE248     /* INTPI2C */

#define KS8692_INT_TIMER_PRIORITY   0xE24C     /* INTPT */

#define KS8692_INT_EXT_PRIORITY     0xE250     /* INTPE */

#define KS8692_INT_CHAN_PRIORITY    0xE254     /* INTPC */

#define KS8692_INT_MASK1_STATUS     0xE258     /* INTPMS  */
#define KS8692_INT_MASK2_STATUS     0xE25C     /* INTPMS2 */

#define KS8692_FIQ1_PEND_PRIORITY   0xE260     /* INTHPF  */
#define KS8692_FIQ2_PEND_PRIORITY   0xE264     /* INTHPF2 */

#define KS8692_IRQ1_PEND_PRIORITY   0xE268     /* INTHPI  */
#define KS8692_IRQ2_PEND_PRIORITY   0xE26C     /* INTHPI2 */


/*
 * Timer Registers
 * (Offset 0xE400 - 0xE5FF)
 */

#define KS8692_TIMER_CTRL           0xE400     /* TMCON */
#define   TIMER_TIME1_ENABLE          0x00000002    /* Enable Timer 1 */
#define   TIMER_TIME0_ENABLE          0x00000001    /* Enable Timer 0 */

#define KS8692_TIMER1               0xE404     /* T1TC */
#define KS8692_TIMER0               0xE408     /* T0TC */
#define KS8692_TIMER1_PCOUNT        0xE40C     /* T1PD */
#define KS8692_TIMER0_PCOUNT        0xE410     /* T0PD */

#define KS8692_TIMER1_COUNTER       0xE424


/*
 * GPIO Registers
 * (Offset 0xE600 - 0xE7FF)
 */

#define KS8692_GPIO_MODE            0xE600     /* IOPM */
#define   GPIO_PIN3_OUTPUT            0x00000008    /* Set GPIO Pin 3 as an output pin */

#define KS8692_GPIO_CTRL            0xE604     /* IOPC */
#define   GPIO_UART4_RTS              0x00800000    /* Set GPIO as UART4 RTS_N */
#define   GPIO_UART3_RTS              0x00400000    /* Set GPIO as UART3 RTS_N */
#define   GPIO_UART2_RTS              0x00200000    /* Set GPIO as UART2 RTS_N */
#define   GPIO_USB_SIGNAL             0x00100000    /* Set GPIO as observe USB signals */
#define   GPIO_SDIO_LED               0x00080000    /* Set GPIO as SDIO LED */
#define   GPIO_INTERNAL_INT           0x00040000    /* Set GPIO as Internal interrupt monitor */
#define   GPIO_TIMER1                 0x00020000    /* Set GPIO as Timer 1 */
#define   GPIO_TIMER0                 0x00010000    /* Set GPIO as Timer 0 */
#define   GPIO_EXT3_INT               0x00008000    /* Set EXT3 as external interrupt */
#define   GPIO_EXT2_INT               0x00000800    /* Set EXT2 as external interrupt */
#define   GPIO_EXT1_INT               0x00000080    /* Set EXT1 as external interrupt */
#define   GPIO_EXT0_INT               0x00000008    /* Set EXT0 as external interrupt */

#define   GPIO_INT_BOTH_EDGE          0x00000006    /* Set ext interrupt trigger mode as "both edge" */
#define   GPIO_INT_FALL_EDGE          0x00000004    /* Set ext interrupt trigger mode as "falling edge" */
#define   GPIO_INT_RISE_EDGE          0x00000002    /* Set ext interrupt trigger mode as "rising edge" */
#define   GPIO_INT_HIGH               0x00000001    /* Set ext interrupt trigger mode as "active high level" */
#define   GPIO_INT_LOW                0x00000000    /* Set ext interrupt trigger mode as "active low level" */

#define KS8692_GPIO_DATA            0xE608     /* IOPD */


/*
 * I2C Registers
 * (Offset 0xE800 - 0xE8FF)
 */

#define I2C_BASE                    0xE800
#define KS8692_I2C_BASE             0xE800	   /* I2C controller base */
#define KS8692_I2C_CTRL             0x00       /* I2C_GCR */
#define   I2C_TIMEOUT_MASK            0x00FF0000    /* I2C Timeout mask */
#define   I2C_STOP_BIT                0x00008000    /* I2C issure Stop bit */
#define   I2C_BIT_PERIOD_MASK         0x000003FE    /* I2C Bit Period mask */
#define   I2C_ENABLE                  0x00000001    /* Enable I2C */

#define KS8692_I2C_ADDR             0x04       /* I2C_AR */
#define   I2C_BYTE_TO_WRITE_MASK      0x00F00000    /* I2C Number of byte to write mask */
#define   I2C_BYTE_TO_READ_MASK       0x000F0000    /* I2C Number of byte to read mask */
#define   I2C_ADDR_10BIT              0x00000800    /* I2C 10-bit Address for transaction */
#define   I2C_ADDR_MASK               0x000007FE    /* I2C 10-bit Address mask */
#define   I2C_READ                    0x00000001    /* I2C Read transaction */
#define   I2C_WRITE                   0x00000000    /* I2C Write transaction */

#define KS8692_I2C_COMMAND          0x08       /* I2C_SCR */
#define   I2C_START                   0x00000001    /* I2C Start command */
#define   I2C_DONE                    0x00000000    /* I2C Done command */

#define KS8692_I2C_STATUS           0x0C       /* I2C_SR */
#define   I2C_SCL                     0x80000000    /* I2C current SCL status */
#define   I2C_SDA                     0x40000000    /* I2C current SDA status */
#define   I2C_DATA_DONE               0x00010000    /* I2C Burst Data transfer completed */
#define   I2C_BYTE_WRITE_MASK         0x0000F000    /* I2C Number of byte writtten mask */
#define   I2C_BYTE_READ_MASK          0x00000F00    /* I2C Number of byte read mask */
#define   I2C_DATA_ERR                0x00000040    /* I2C Data error */
#define   I2C_START_TIMEOUT_ERR       0x00000020    /* I2C Start bit timeout error */
#define   I2C_STOP_TIMEOUT_ERR        0x00000010    /* I2C Stop bit timeout error */
#define   I2C_DATA_TIMEOUT_ERR        0x00000008    /* I2C Data timeout error */
#define   I2C_ADDR_TIMEOUT_ERR        0x00000004    /* I2C Address timeout error */
#define   I2C_DATA_ACK_ERR            0x00000002    /* I2C No Data ACK error */
#define   I2C_ADDR_ACK_ERR            0x00000001    /* I2C No Address ACK error */
#define   I2C_ERROR_MASK              0x0000007F    /* I2C transaction error mask */
#define   I2C_STATUS_MASK             0x000001FF    /* I2C status check mask */
#define   I2C_MAX_DATA_LEN            8             /* I2C max transaction data length */

#define KS8692_I2C_READ_DATA0       0x10       /* I2C_RDR0 */
#define KS8692_I2C_READ_DATA1       0x14       /* I2C_RDR1 */
#define KS8692_I2C_WRITE_DATA0      0x18       /* I2C_WDR0 */
#define KS8692_I2C_WRITE_DATA1      0x1C       /* I2C_WDR1 */
#define KS8692_I2C_DEBUG            0x20       /* I2C_DEBUG */


/*
 * SPI Registers
 * (Offset 0xE900 - 0xE9FF)
 */

#define SPI_BASE                    0xE900
#define KS8692_SPI_BASE             0xE900	   /* SPI controller base */
#define KS8692_SPI_CTRL             0x00       /* SPI_CTR */
#define   SPI_RESET                   0x80000000    /* SPI Software Reset */
#define   SPI_ENABLE                  0x40000000    /* Enable SPI */
#define   SPI_RX_CHECK_RDY            0x00000002    /* SPI Enable check RDY before read frame length */
#define   SPI_TX_CHECK_RDY            0x00000001    /* SPI Enable check RDY before write frame length */

#define KS8692_SPI_RX_DATA          0x04       /* SPI_RDR */
#define   SPI_RX_PDATA_MASK           0xFFFF0000    /* SPI Receive data pointer in receive buffer */
#define   SPI_CS_VALUE                0x00008000    /* SPI CS Status on the CS pin */
#define   SPI_RX_DATA_MASK            0x0000FFFF    /* SPI Receive data mask */

#define KS8692_SPI_TX_DATA          0x08       /* SPI_TDR */
#define   SPI_TX_DATA_MASK            0xFFFF0000    /* SPI Transmit data window to transmit buffer */
#define   SPI_TX_CS_END               0x00008000    /* SPI De-assert the CS after transmission command */
#define   SPI_TX_HIZ_ENABLE           0x00004000    /* SPI Set high in MOSI pin when process 1st character in transmit buffer */
#define   SPI_TX_HIZEXT_ENABLE        0x00002000    /* SPI Set high in MOSI pin when SPI goes to Character Externd State */
#define   SPI_MICREL_MODE             0x00001000    /* SPI Change SPI mode to Micrel mode (32bit transfer) */
#define   SPI_TX_16_BITS              0x00000800    /* SPI Set 16 Bits per transfer */
#define   SPI_TX_BITS_MASK            0x00000F00    /* SPI Bits per transfer mask */
#define   SPI_TX_CEXT_MASK            0x000000FF    /* SPI Character Extend mask */

#define KS8692_SPI_MICREL_TX_DATA   0x0C       /* SPI_MCR */

#define KS8692_SPI_BUF_STATUS       0x10       /* SPI_BFR */
#define   SPI_MICREL_RX_LEN_MASK      0xFF000000    /* SPI Receive Data Length mask at Micrel mode */
#define   SPI_RX_ERROR                0x00200000    /* SPI Receive a underrun error */
#define   SPI_RX_LEN_MASK             0x001F0000    /* SPI received data length in receive buffer */
#define   SPI_TX_ERROR                0x00000020    /* SPI Transmit overrun error */
#define   SPI_UNTX_LEN_MASK           0x0000001F    /* SPI UnTransmit data length in transmit buffer */

#define KS8692_SPI_INT_STATUS       0x14       /* SPI_ISR */
#define KS8692_SPI_INT_ENABLE       0x18       /* SPI_IER */
#define   SPI_INT_RDBU                0x80000000    /* SPI Receive Data Buffer Full Interrupt */
#define   SPI_INT_RDRDY               0x40000000    /* SPI Receive Data Ready Interrupt */
#define   SPI_INT_XRDY                0x20000000    /* SPI External RDY Interrupt */
#define   SPI_INT_TDBU                0x10000000    /* SPI Transmit Data Buffer Full Interrupt */
#define   SPI_INT_TDTH                0x08000000    /* SPI Transmit Buffer is Lower than Threshold Interrupt */
#define   SPI_INT_MASK                ( SPI_INT_RDBU | SPI_INT_RDRDY | SPI_INT_TDBU | SPI_INT_TDTH )

#define KS8692_SPI_CS               0x1C       /* SPI_CSR */
#define   SPI_SPCK_INACTIVE_HIGH      0x80000000    /* SPI SPCK is high inactive (CPOL=1)*/
#define   SPI_SPCK_INACTIVE_LOW       0x00000000    /* SPI SPCK is low inactive (CPPL=0)*/
#define   SPI_DATA_LEADING_EDGE       0x40000000    /* SPI Data captured at leading edge of SPCK clock (CPHA=1)*/
#define   SPI_DATA_FOLLOWING_EDGE     0x00000000    /* SPI Data captured at following edge of SPCK clock (CPHA=0) */
#define   SPI_SYSCLK_BY65536          0x38000000    /* SPI Clock divided SYSCLK by 65536 */
#define   SPI_SYSCLK_BY8192           0x30000000    /* SPI Clock divided SYSCLK by 8192 */
#define   SPI_SYSCLK_BY1024           0x28000000    /* SPI Clock divided SYSCLK by 1024 */
#define   SPI_SYSCLK_BY256            0x20000000    /* SPI Clock divided SYSCLK by 256 */
#define   SPI_SYSCLK_BY128            0x18000000    /* SPI Clock divided SYSCLK by 128 */
#define   SPI_SYSCLK_BY64             0x10000000    /* SPI Clock divided SYSCLK by 64 */
#define   SPI_SYSCLK_BY32             0x08000000    /* SPI Clock divided SYSCLK by 32 */
#define   SPI_SYSCLK_BY16             0x00000000    /* SPI Clock divided SYSCLK by 16 */
#define   SPI_SYSCLK_MASK             0x38000000    /* SPI Clock divided mask */
#define   SPI_CS_ACTIVE_HIGH          0x04000000    /* SPI CS is high active */
#define   SPI_CS_ACTIVE_LOW           0x00000000    /* SPI CS is low active */
#define   SPI_TX_THRESHOLD_MASK       0x00F00000    /* SPI Transmit Buffer Threshold mask */
#define   SPI_RX_THRESHOLD_MASK       0x000F0000    /* SPI Receive Buffer Threshold mask */
#define   SPI_CS_SETUP_TIME_EN        0x00001000    /* SPI CS valid to SPCK is 1 clock periord */
#define   SPI_DATA_DELAY_1            0x00000100    /* SPI delay 1 clock between consecutive transfers */
#define   SPI_CS_DELAY_1              0x00000001    /* SPI delay 1 clock between CS */
#define   SPI_DATA_DELAY_MASK         0x00000F00    /* SPI delay mask between data transfers */
#define   SPI_CS_DELAY_MASK           0x000000FF    /* SPI delay mask between chip selects */

/*
 * Miscellaneous Registers
 * (Offset 0xEA00 - 0xEAFF)
 */

#define KS8692_DEVICE_ID            0xEA00     /* DID */

#define KS8692_REVISION_ID          0xEA04     /* RID */

#define KS8692_DDR_CTRL_DIAG        0xEA10     /* DDRDIAG */
#define   DDR_CMD_REFRESH             0x80000000    /* DDR self-refresh command */
#define   DDR_STAT_REFRESH            0x00000008    /* DDR status of refresh command in process */
#define   DDR_STAT_DLL_LOCK           0x00000004    /* DDR status of DLL lock */
#define   DDR_STAT_Q_FULL             0x00000002    /* DDR status of queue has reached the q_fullness */
#define   DDR_STAT_BUSY               0x00000001    /* DDR status of controller busy */

#define KS8692_USB_PHY_CTRL         0xEA20     /* UPC */
#define   USB_OVER_CURRENT            0x00000800    /* USB positive sense over current */
#define   USB_POWER_DOWN              0x00000400    /* USB power shut down in USB ananlog partion */
#define   USB_TEST_PIN_ENABLE         0x00000200    /* Enable USB Test pin output */
#define   USB_ENABLE                  0x00000001    /* Enable USB device */

#define KS8692_USB_TEST_CTRL        0xEA24     /* UPT */
#define KS8692_USB_TEST_STATUS      0xEA28     /* UPS */
#define KS8692_PLL_CTRL_DIAG        0xEA2C     /* PDC */

#define KS8692_NAND_BUSY_STATUS     0xEA40     /* NFLBS */
#define   NAND_BANK2_BUSY             0x00000002    /* NAND flash bank2 is busy */
#define   NAND_BANK1_BUSY             0x00000001    /* NAND flash bank1 is busy */

#define KS8692_SPARE_REG            0xEA50     /* SR  */
#define   IPV6_UDP_FRAG_PASS          0x00000002    /* No checksum generation/verification if IPv6 UDP is fragment */
#define   IPV6_UDP_ZERO_PASS          0x00000001    /* Receive pass IPv6 UDP frame with UDP checksum is zero */


/*
 * I2S Registers
 * (Offset 0xEB00 - 0xEBFF)
 */

#define I2S_BASE                    0xEB00
#define KS8692_I2S_BASE             0xEB00	   /* I2S controller base */
#define KS8692_I2S_CTRL             0x0        /* I2S_CR */
#define   I2S_LEFT_JUSTIFIED          0x00400000    /* I2S Left justified timing  */
#define   I2S_DATA_24BIT              0x00300000    /* I2S 24 bit wide audio data */
#define   I2S_DATA_20BIT              0x00200000    /* I2S 20 bit wide audio data */
#define   I2S_DATA_18BIT              0x00100000    /* I2S 18 bit wide audio data */
#define   I2S_DATA_16BIT              0x00000000    /* I2S 16 bit wide audio data */
#define   I2S_DATA_FMT_MASK           0x00300000    /* I2S data format mask */
#define   I2S_BCLK_DIVISOR_MASK       0x000F0000    /* I2S BCLK divisior value mask */
#define   I2S_RX_ENABLE               0x00001000    /* Enable I2S Receive */
#define   I2S_RX_INT_THRESHOLD2       0x00000200    /* I2S generate interrupt when receive hit 3/4 tx buffer */
#define   I2S_RX_INT_THRESHOLD1       0x00000100    /* I2S generate interrupt when receive hit 1/4 tx buffer */
#define   I2S_RX_INT_THRESHOLD0       0x00000000    /* I2S generate interrupt when receive hit 1/2 tx buffer */
#define   I2S_TX_ENABLE               0x00000010    /* Enable I2S Transmit */
#define   I2S_TX_INT_THRESHOLD2       0x00000002    /* I2S generate interrupt when transmit hit 3/4 tx buffer */
#define   I2S_TX_INT_THRESHOLD1       0x00000001    /* I2S generate interrupt when transmit hit 1/4 tx buffer */
#define   I2S_TX_INT_THRESHOLD0       0x00000000    /* I2S generate interrupt when transmit hit 1/2 tx buffer */

#define KS8692_I2S_TX_STATUS        0x0004     /* I2S_TSR */
#define   I2S_TX_THRESHOLD_HIT        0x00000400    /* I2S Transmit threshold is hit */
#define   I2S_TX_OVERRUN              0x00000200    /* I2S Transmit overrun */
#define   I2S_TX_UNDERRUN             0x00000100    /* I2S Transmit underrun */
#define   I2S_TX_VALID_MASK           0x0000003F    /* I2S Transmit buffer valid counter */

#define KS8692_I2S_RX_STATUS        0x0008     /* I2S_RSR */
#define   I2S_RX_THRESHOLD_HIT        0x00000400    /* I2S Receive threshold is hit */
#define   I2S_RX_OVERRUN              0x00000200    /* I2S Receive overrun */
#define   I2S_RX_UNDERRUN             0x00000100    /* I2S Receive underrun */
#define   I2S_RX_VALID_MASK           0x0000003F    /* I2S Receive buffer valid counter */

#define KS8692_I2S_DATA             0x000C     /* I2S_DR */

/*
 * STA Registers
 * (Offset 0xEC00 - 0xECFF)
 */

#define KS8692_STA_CONF             0xEC00     /* STA_CFG */
#define   STA_AUTO_POLL               0x80000000    /* STA auto poll */
#define   STA_MDC_SHUT_DOWN           0x00020000    /* STA Shut down MDC */
#define   STA_PREAMBLE                0x00010000    /* STA Set preamble suppression */
#define   STA_CLK_DIVIDEND_MASK       0x000001FE    /* STA Clock dividend value mask */
#define   STA_MDIO_ENABLE             0x00000001    /* STA Enable MDIO */

#define KS8692_STA_PHY              0xEC04     /* STA_INSTALLED_PHY */
#define   STA_PHY1_VALID              0x00008000    /* STA PHY 1 Valid */
#define   STA_PHY1_ADD_MASK           0x00001F00    /* STA PHY 1 Address Mask */
#define   STA_PHY0_VALID              0x00000080    /* STA PHY 0 Valid */
#define   STA_PHY0_ADD_MASK           0x0000001F    /* STA PHY 0 Address Mask */

#define KS8692_STA_INT_CTRL         0xEC08     /* STA_INT_ENABLE */
#define   PHY_AERR_ENABLE             0x00000040    /* STA PHY Address Error */
#define   PROC_TERR_ENABLE            0x00000020    /* STA Procedure TransactionError */
#define   PHY1_DN_ENABLE              0x00000010    /* STA PHY1 link down */
#define   PHY1_UP_ENABLE              0x00000008    /* STA PHY1 link up */
#define   PHY0_DN_ENABLE              0x00000004    /* STA PHY0 link down */
#define   PHY0_UP_ENABLE              0x00000002    /* STA PHY0 link up */
#define   CPU_CMPLT_ENABLE            0x00000001    /* STA transaction is done */

#define KS8692_STA_INT_STATUS         0xEC0C     /* STA_INT_EVENT */
#define   PHY_AERR                    0x00000040    /* STA PHY Address Error */
#define   PROC_TERRE                  0x00000020    /* STA Procedure TransactionError */
#define   PHY1_DN                     0x00000010    /* STA PHY1 link down */
#define   PHY1_UP                     0x00000008    /* STA PHY1 link up */
#define   PHY0_DN                     0x00000004    /* STA PHY0 link down */
#define   PHY0_UP                     0x00000002    /* STA PHY0 link up */
#define   CPU_CMPLT                   0x00000001    /* STA transaction is done */

#define KS8692_STA_COMM             0xEC10     /* STA_COMMAND */
#define   STA_BURST_SIZE4             0x00030000    /* STA Burst 4 transactions */
#define   STA_BURST_SIZE3             0x00020000    /* STA Burst 3 transactions */
#define   STA_BURST_SIZE2             0x00010000    /* STA Burst 2 transactions */
#define   STA_BURST_SIZE1             0x00000000    /* STA Burst 1 transactions */
#define   STA_PHY_REG_ADDR_MASK       0x000007C0    /* STA PHY register address */
#define   STA_PHY_ADDR_MASK           0x0000003E    /* STA PHY address */
#define   STA_READ                    0x00000001    /* STA Read operation */
#define   STA_WRITE                   0x00000000    /* STA Write operation */

#define KS8692_STA_CTRL             0xEC14     /* STA_CONTROL */
#define   STA_START                   0x00000001    /* STA Start command to start STA management transaction */

#define KS8692_STA_STATUS           0xEC18     /* STA_STATUS */
#define   STA_BURST_STATUS_MASK       0x0000000C    /* STA Burst size of last completed transaction */
#define   STA_READ_DONE               0x00000003    /* STA Read transaction has done */
#define   STA_WRITE_DONE              0x00000002    /* STA Write transaction has done */
#define   STA_BUSY                    0x00000001    /* STA Transaction is in BUSY */
#define   STA_IDLE                    0x00000000    /* STA Transaction is in IDLE */
#define   STA_STATUS_MASK             0x00000003    /* STA Transaction status mask */

#define KS8692_STA_DATA0            0xEC1C     /* STA_DATA0 */

#define KS8692_STA_DATA1            0xEC20     /* STA_DATA1 */

/*
 * MIB Counters Registers
 * (Offset 0xED00 - 0xEDFF)
 */

#define KS8692_MIB_PORT0_COUNTER    0xED00
#define KS8692_MIB_PORT1_COUNTER    0xED80

/*
 * IPSec Registers
 * (Offset 0x80000 - 0xAFFFF)
 */


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

  #define CFI_DEVICETYPE                       CFI_DEVICETYPE_X8
  #define CFI_INTERLEAVE                       1
  #define cfi_buswidth_is_1()                  (1)
  #define cfi_buswidth_is_2()                  (0)
  #define cfi_buswidth_is_4()                  (0)
  #define cfi_interleave_is_1()                (1)
  #define cfi_interleave_is_2()                (0)
  #define cfi_interleave_is_4()                (0)
#endif

#endif

/* 	END */
