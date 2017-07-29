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

#include <mach/ks8692Reg.h>

/*
 *  System Memory Mapping
 */

#define KS8692_SDRAM_START          0x00000000
/* 32MB on board SDRAM, can be overwritten by kernel parameter */
#define KS8692_SDRAM_SIZE           0x02000000

#define KS8692_MEM_SIZE             KS8692_SDRAM_SIZE
#define KS8692_MEM_START            KS8692_SDRAM_START


/* normal case is external io starts from 0x03200000 and each bank be 4MB */
#define KS8692_EXTIO_BASE           0x03200000
#define KS8692_EXTIO_SIZE           0x00C00000   /* total size */

/* flash starts from 0x1C000000 */
#define KS8692_FLASH_START          0x1C000000
#define KS8692_FLASH_SIZE           0x00400000   /* 4MB */

/* NAND Flash Config Register base address */
#define KS8692_NAND_FLASH_BASE      0x1FFE0000
/* NAND Flash Register space size - 64KB */
#define KS8692_NAND_FLASH_SIZE      0x00010000

/* IPSEC Config Register base address */
#define KS8692_IPSEC_BASE           0x1FF80000
/* IPSEC Register space size - 256kB */
#define KS8692_IPSEC_SIZE           0x00040000

#define KS8692_PCMCIA_IO_BASE       0x03800000   /* for PCMCIA */
#define KS8692_PCMCIA_IO_SIZE       0x00040000

/* System Config Register base address */
#define KS8692_IO_BASE              0x1FFF0000
/* System Config Register space size - 64KB */
#define KS8692_IO_SIZE              0x00010000

/*
 *  Configure System Virtual Memory
 */

/*
 * Where in virtual memory the IO devices (timers, system controllers and so on)
 */

#define IO_BASE			0xF0000000		/* VA of IO */
#define IO_SIZE			KS8692_IO_SIZE		/* 0x0000 - 0xFFFF */
#define IO_START		KS8692_IO_BASE		/* PA of IO */

#define KS8692_VIO_BASE		0xF1FFF000

#define KS_IO_BASE		KS8692_IO_BASE

#define PCI_IO_VADDR		0xE0000000

/* Use SDRAM for memory  */
#define MEM_SIZE		KS8692_MEM_SIZE


/*
 * Macro to access KS8692 Registers by 32bit Data Width only
 */

#define IO_ADDRESS(x)		IOMEM(((x) >> 4) + IO_BASE)
#define KS8692_VA_IO_BASE	IO_ADDRESS(KS8692_IO_BASE)
#define KS_VIO_BASE		IO_ADDRESS(KS8692_IO_BASE)
#define VIO(reg)		(KS_VIO_BASE + (reg))

#define	KS8692_WRITE_REG(offset, v)	\
	__raw_writel((v), KS8692_VA_IO_BASE + (offset))
#define	KS8692_READ_REG(offset)		\
	__raw_readl(KS8692_VA_IO_BASE + (offset))

#define KS_R				KS8692_READ_REG
#define KS_W				KS8692_WRITE_REG

/* Watchdog timer macros. */
#define READ_TIMER_CTRL()		KS_R(KS8692_TIMER_CTRL)
#define DISABLE_TIMER(reg)		\
	KS_W(KS8692_TIMER_CTRL, (reg & ~(TIMER_TIME0_ENABLE)))
#define ENABLE_TIMER(reg)		\
	KS_W(KS8692_TIMER_CTRL, (reg | (TIMER_TIME0_ENABLE)))
#define WRITE_TIMER_VALUE(value, pcount)  \
	{ KS_W(KS8692_TIMER0, value);  KS_W(KS8692_TIMER0_PCOUNT, pcount); }


/*
 *  Configure System Interrupt
 */

#define MAXIRQNUM                              63
#define LOW_IRQS                               32

/*  definations for IRQ */

#define KS8692_INT_DDR_SDR_ERR                  4
#define KS8692_INT_IPSEC                        6
#define KS8692_INT_SDIO                         7
#define KS8692_INT_USB_HOST_EHCI                8
#define KS8692_INT_USB_HOST_OHCI                9
#define KS8692_INT_USB_DEVICE                  10
#define KS8692_INT_LAN_STOP_RX                 12
#define KS8692_INT_LAN_STOP_TX                 13
#define KS8692_INT_LAN_BUF_RX_STATUS           14
#define KS8692_INT_LAN_BUF_TX_STATUS           15
#define KS8692_INT_LAN_RX_STATUS               16
#define KS8692_INT_LAN_TX_STATUS               17
#define KS8692_INT_LAN_WOL                     18
#define KS8692_INT_WAN_WOL                     19
#define KS8692_INT_BUS_ERROR                   24
#define KS8692_INT_WAN_STOP_RX                 25
#define KS8692_INT_WAN_STOP_TX                 26
#define KS8692_INT_WAN_BUF_RX_STATUS           27
#define KS8692_INT_WAN_BUF_TX_STATUS           28
#define KS8692_INT_WAN_RX_STATUS               29
#define KS8692_INT_WAN_TX_STATUS               30


#define KS8692_INT_EXT_INT0                     2
#define KS8692_INT_EXT_INT1                     3
#define KS8692_INT_EXT_INT2                     4
#define KS8692_INT_EXT_INT3                     5
#define KS8692_INT_TIMERINT0                    6
#define KS8692_INT_TIMERINT1                    7
#define KS8692_INT_I2C                          8
#define KS8692_INT_I2S_RX                       9
#define KS8692_INT_I2S_TX                      10
#define KS8692_INT_SPI                         11
#define KS8692_INT_MDIO                        12
#define KS8692_INT_UART1_TX                    13
#define KS8692_INT_UART1_RX                    14
#define KS8692_INT_UART1_LINE_ERR              15
#define KS8692_INT_UART1_MODEMS                16
#define KS8692_INT_UART2_TX                    17
#define KS8692_INT_UART2_RX                    18
#define KS8692_INT_UART2_LINE_ERR              19
#define KS8692_INT_UART3_TX                    20
#define KS8692_INT_UART3_RX                    21
#define KS8692_INT_UART3_LINE_ERR              22
#define KS8692_INT_UART4_TX                    23
#define KS8692_INT_UART4_RX                    24
#define KS8692_INT_UART4_LINE_ERR              25


/*  Interrupt bit positions */

#define KS8692_INTMASK_DDR_SDR_ERR          (1 << KS8692_INT_DDR_SDR_ERR)
#define KS8692_INTMASK_IPSEC                (1 << KS8692_INT_IPSEC)
#define KS8692_INTMASK_SDIO                 (1 << KS8692_INT_SDIO)
#define KS8692_INTMASK_USB_HOST_EHCI        (1 << KS8692_INT_USB_HOST_EHCI)
#define KS8692_INTMASK_USB_HOST_OHCI        (1 << KS8692_INT_USB_HOST_OHCI)
#define KS8692_INTMASK_USB_DEVICE           (1 << KS8692_INT_USB_DEVICE)
#define KS8692_INTMASK_LAN_STOP_RX          (1 << KS8692_INT_LAN_STOP_RX)
#define KS8692_INTMASK_LAN_STOP_TX          (1 << KS8692_INT_LAN_STOP_TX)
#define KS8692_INTMASK_LAN_BUF_RX_STATUS    (1 << KS8692_INT_LAN_BUF_RX_STATUS)
#define KS8692_INTMASK_LAN_BUF_TX_STATUS    (1 << KS8692_INT_LAN_BUF_TX_STATUS)
#define KS8692_INTMASK_LAN_RX_STATUS        (1 << KS8692_INT_LAN_RX_STATUS)
#define KS8692_INTMASK_LAN_TX_STATUS        (1 << KS8692_INT_LAN_TX_STATUS)
#define KS8692_INTMASK_LAN_WOL              (1 << KS8692_INT_LAN_WOL)
#define KS8692_INTMASK_WAN_WOL              (1 << KS8692_INT_WAN_WOL)
#define KS8692_INTMASK_BUS_ERROR            (1 << KS8692_INT_BUS_ERROR)
#define KS8692_INTMASK_WAN_STOP_RX          (1 << KS8692_INT_WAN_STOP_RX)
#define KS8692_INTMASK_WAN_STOP_TX          (1 << KS8692_INT_WAN_STOP_TX)
#define KS8692_INTMASK_WAN_BUF_RX_STATUS    (1 << KS8692_INT_WAN_BUF_RX_STATUS)
#define KS8692_INTMASK_WAN_BUF_TX_STATUS    (1 << KS8692_INT_WAN_BUF_TX_STATUS)
#define KS8692_INTMASK_WAN_RX_STATUS        (1 << KS8692_INT_WAN_RX_STATUS)
#define KS8692_INTMASK_WAN_TX_STATUS        (1 << KS8692_INT_WAN_TX_STATUS)

#define KS8692_INTMASK_EXT_INT0             (1 << KS8692_INT_EXT_INT0)
#define KS8692_INTMASK_EXT_INT1             (1 << KS8692_INT_EXT_INT1)
#define KS8692_INTMASK_EXT_INT2             (1 << KS8692_INT_EXT_INT2)
#define KS8692_INTMASK_EXT_INT3             (1 << KS8692_INT_EXT_INT3)
#define KS8692_INTMASK_TIMERINT0            (1 << KS8692_INT_TIMERINT0)
#define KS8692_INTMASK_TIMERINT1            (1 << KS8692_INT_TIMERINT1)
#define KS8692_INTMASK_I2C                  (1 << KS8692_INT_I2C)
#define KS8692_INTMASK_I2S_RX               (1 << KS8692_INT_I2S_RX)
#define KS8692_INTMASK_I2S_TX               (1 << KS8692_INT_I2S_TX)
#define KS8692_INTMASK_SPI                  (1 << KS8692_INT_SPI)
#define KS8692_INTMASK_MDIO                 (1 << KS8692_INT_MDIO)
#define KS8692_INTMASK_UART1_TX             (1 << KS8692_INT_UART1_TX)
#define KS8692_INTMASK_UART1_RX             (1 << KS8692_INT_UART1_RX)
#define KS8692_INTMASK_UART1_LINE_ERR       (1 << KS8692_INT_UART1_LINE_ERR)
#define KS8692_INTMASK_UART1_MODEMS         (1 << KS8692_INT_UART1_MODEMS)
#define KS8692_INTMASK_UART2_TX             (1 << KS8692_INT_UART2_TX)
#define KS8692_INTMASK_UART2_RX             (1 << KS8692_INT_UART2_RX)
#define KS8692_INTMASK_UART2_LINE_ERR       (1 << KS8692_INT_UART2_LINE_ERR)
#define KS8692_INTMASK_UART3_TX             (1 << KS8692_INT_UART3_TX)
#define KS8692_INTMASK_UART3_RX             (1 << KS8692_INT_UART3_RX)
#define KS8692_INTMASK_UART3_LINE_ERR       (1 << KS8692_INT_UART3_LINE_ERR)
#define KS8692_INTMASK_UART4_TX             (1 << KS8692_INT_UART4_TX)
#define KS8692_INTMASK_UART4_RX             (1 << KS8692_INT_UART4_RX)
#define KS8692_INTMASK_UART4_LINE_ERR       (1 << KS8692_INT_UART4_LINE_ERR)

#define KS_INT_UART_TX(base_tx_irq)         (1 << ((base_tx_irq) + 0))
#define KS_INT_UART_RX(base_tx_irq)         (1 << ((base_tx_irq) + 1))
#define KS_INT_UART_LINE(base_tx_irq)       (1 << ((base_tx_irq) + 2))
#define KS_INT_UART_MODEM(base_tx_irq)      (1 << ((base_tx_irq) + 3))
#define KS_INT_UART_MASK(base_tx_irq)  \
	(((KS8692_INT_UART1_TX == (base_tx_irq)) ? 0xF : 0x7) << (base_tx_irq))

/*
 *  System Devices Interfaces Definitions
 */

#define	MAX_ETHERNET_PORTS	2		/* Max Ethernet ports */
#define MAX_UART_PORTS		4		/* Max UART ports */


#ifndef __ASSEMBLY__
extern void pegasus_init_late_call(void);
extern void pegasus_register_late_call(void *);
#endif

/*============================================================================*/
#endif

/* END */
