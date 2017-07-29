/* arch/arm/mach-ksz8692/devs.c
 *
 * Copyright (c) 2009-2015 Micrel, Inc.
 *
 * Copyright (c) 2004 Simtec Electronics
 * Ben Dooks <ben@simtec.co.uk>
 *
 * Base S3C2410 platform device definitions
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * Modifications:
 *     15-Jan-2006 LCVR Using S3C24XX_PA_##x macro for common S3C24XX devices
 *     10-Mar-2005 LCVR Changed S3C2410_{VA,SZ} to S3C24XX_{VA,SZ}
 *     10-Feb-2005 BJD  Added camera from guillaume.gourat@nexvision.tv
 *     29-Aug-2004 BJD  Added timers 0 through 3
 *     29-Aug-2004 BJD  Changed index of devices we only have one of to -1
 *     21-Aug-2004 BJD  Added IRQ_TICK to RTC resources
 *     18-Aug-2004 BJD  Created initial version
*/

#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/interrupt.h>
#include <linux/list.h>
#include <linux/timer.h>
#include <linux/init.h>
#include <linux/platform_device.h>

#include "devs.h"

#define KS8692_PA_SYSCFG1 (KS8692_IO_BASE+SYSCFG1_BASE)
#define KS8692_SZ_SYSCFG1 SZ_8K

#define KS8692_PA_SYSCFG2 (KS8692_IO_BASE+SYSCFG2_BASE)
#define KS8692_SZ_SYSCFG2 SZ_8K

#define KS8692_PA_PCI (KS8692_IO_BASE+PCI_BASE)
#define KS8692_SZ_PCI SZ_8K

#define KS8692_PA_DDR (KS8692_IO_BASE+DDR_BASE)
#define KS8692_SZ_DDR SZ_4K

#define KS8692_PA_SDRAM (KS8692_IO_BASE+SDRAM_BASE)
#define KS8692_SZ_SDRAM SZ_4K

#define KS8692_PA_WAN (KS8692_IO_BASE+WAN_BASE)
#define KS8692_SZ_WAN SZ_8K

#define KS8692_PA_LAN (KS8692_IO_BASE+LAN_BASE)
#define KS8692_SZ_LAN SZ_8K

#define KS8692_PA_SDI (KS8692_IO_BASE+SDI_BASE)
#define KS8692_SZ_SDI SZ_4K

#define KS8692_PA_OHCI (KS8692_IO_BASE+USB_OHCI_BASE)
#define KS8692_SZ_OHCI SZ_4K

#define KS8692_PA_EHCI (KS8692_IO_BASE+USB_EHCI_BASE)
#define KS8692_SZ_EHCI SZ_4K

#define KS8692_PA_USBDEVICE (KS8692_IO_BASE+USB_DEVICE_BASE)
#define KS8692_SZ_USBDEVICE SZ_4K

#define KS8692_PA_I2C (KS8692_IO_BASE+I2C_BASE)
#define KS8692_SZ_I2C 0x100

#define KS8692_PA_SPI (KS8692_IO_BASE+SPI_BASE)
#define KS8692_SZ_SPI 0x100

#define KS8692_PA_I2S (KS8692_IO_BASE+I2S_BASE)
#define KS8692_SZ_I2S 0x100


#define	IRQ_SDIO	7
#define	IRQ_EHCI	8
#define	IRQ_OHCI	9
#define	IRQ_USBDEVICE	10
#define	IRQ_SPI         LOW_IRQS+KS8692_INT_SPI
#define	IRQ_I2S_TX      LOW_IRQS+KS8692_INT_I2S_TX
#define	IRQ_I2S_RX      LOW_IRQS+KS8692_INT_I2S_RX
#define	IRQ_I2C         LOW_IRQS+KS8692_INT_I2C


#define SYSCFG1_BASE    0x0000
#define PCI_BASE    	0x2000
#define DDR_BASE        0x4000
#define SDRAM_BASE      0x5000
#define WAN_BASE        0x6000
#define LAN_BASE        0x8000
#define SDI_BASE        0xA000

#define USB_DEVICE_BASE 0xB000
#define USB_EHCI_BASE   0xC000
#define USB_OHCI_BASE   0xD000
#define SYSCFG2_BASE    0xE000

static struct resource ks8692_syscfg1_resource[] = {
	[0] = {
		.start = KS8692_PA_SYSCFG1,
		.end   = KS8692_PA_SYSCFG1 + KS8692_SZ_SYSCFG1 - 1,
		.flags = IORESOURCE_MEM,
	},
};

static u64 ks8692_device_syscfg1_dmamask = 0xffffffffUL;

struct platform_device ks8692_device_syscfg1 = {
	.name		  = "ks8692-syscfg1",
	.id		  = -1,
	.num_resources	  = ARRAY_SIZE(ks8692_syscfg1_resource),
	.resource	  = ks8692_syscfg1_resource,
	.dev              = {
		.dma_mask = &ks8692_device_syscfg1_dmamask,
		.coherent_dma_mask = 0xffffffffUL
	}
};

EXPORT_SYMBOL(ks8692_device_syscfg1);

static struct resource ks8692_syscfg2_resource[] = {
	[0] = {
		.start = KS8692_PA_SYSCFG2,
		.end   = KS8692_PA_SYSCFG2 + KS8692_SZ_SYSCFG2 - 1,
		.flags = IORESOURCE_MEM,
	},
};

static u64 ks8692_syscfg2_dmamask = 0xffffffffUL;

struct platform_device ks8692_device_syscfg2 = {
	.name		  = "ks8692-syscfg2",
	.id		  = -1,
	.num_resources	  = ARRAY_SIZE(ks8692_syscfg2_resource),
	.resource	  = ks8692_syscfg2_resource,
	.dev              = {
		.dma_mask = &ks8692_syscfg2_dmamask,
		.coherent_dma_mask = 0xffffffffUL
	}
};

EXPORT_SYMBOL(ks8692_device_syscfg2);


/* PCI BRIDGE Controller */
static struct resource ks8692_pci_resource[] = {
	[0] = {
		.start = KS8692_PA_PCI,
		.end   = KS8692_PA_PCI + KS8692_SZ_PCI - 1,
		.flags = IORESOURCE_MEM,
	},
};

static u64 ks8692_device_pci_dmamask = 0xffffffffUL;

struct platform_device ks8692_device_pci = {
	.name		  = "ks8692-pci",
	.id		  = -1,
	.num_resources	  = ARRAY_SIZE(ks8692_pci_resource),
	.resource	  = ks8692_pci_resource,
	.dev              = {
		.dma_mask = &ks8692_device_pci_dmamask,
		.coherent_dma_mask = 0xffffffffUL
	}
};

EXPORT_SYMBOL(ks8692_device_pci);

/* DDR Controller */
static struct resource ks8692_ddr_resource[] = {
	[0] = {
		.start = KS8692_PA_DDR,
		.end   = KS8692_PA_DDR + KS8692_SZ_DDR - 1,
		.flags = IORESOURCE_MEM,
	},
};

static u64 ks8692_device_ddr_dmamask = 0xffffffffUL;

struct platform_device ks8692_device_ddr = {
	.name		  = "ks8692-ddr",
	.id		  = -1,
	.num_resources	  = ARRAY_SIZE(ks8692_ddr_resource),
	.resource	  = ks8692_ddr_resource,
	.dev              = {
		.dma_mask = &ks8692_device_ddr_dmamask,
		.coherent_dma_mask = 0xffffffffUL
	}
};

EXPORT_SYMBOL(ks8692_device_ddr);

/* SDRAM Controller */
static struct resource ks8692_sdram_resource[] = {
	[0] = {
		.start = KS8692_PA_SDRAM,
		.end   = KS8692_PA_SDRAM + KS8692_SZ_SDRAM - 1,
		.flags = IORESOURCE_MEM,
	},
};

static u64 ks8692_device_sdram_dmamask = 0xffffffffUL;

struct platform_device ks8692_device_sdram = {
	.name		  = "ks8692-sdram",
	.id		  = -1,
	.num_resources	  = ARRAY_SIZE(ks8692_sdram_resource),
	.resource	  = ks8692_sdram_resource,
	.dev              = {
		.dma_mask = &ks8692_device_sdram_dmamask,
		.coherent_dma_mask = 0xffffffffUL
	}
};

EXPORT_SYMBOL(ks8692_device_sdram);

/* WAN ETH Controller */
static struct resource ks8692_wan_resource[] = {
	[0] = {
		.start = KS8692_PA_WAN,
		.end   = KS8692_PA_WAN + KS8692_SZ_WAN - 1,
		.flags = IORESOURCE_MEM,
	},
};

static u64 ks8692_device_wan_dmamask = 0xffffffffUL;

struct platform_device ks8692_device_wan = {
	.name		  = "ks8692-wan",
	.id		  = -1,
	.num_resources	  = ARRAY_SIZE(ks8692_wan_resource),
	.resource	  = ks8692_wan_resource,
	.dev              = {
		.dma_mask = &ks8692_device_wan_dmamask,
		.coherent_dma_mask = 0xffffffffUL
	}
};

EXPORT_SYMBOL(ks8692_device_wan);

/* LAN ETH Controller */
static struct resource ks8692_lan_resource[] = {
	[0] = {
		.start = KS8692_PA_LAN,
		.end   = KS8692_PA_LAN + KS8692_SZ_LAN - 1,
		.flags = IORESOURCE_MEM,
	},
};

static u64 ks8692_device_lan_dmamask = 0xffffffffUL;

struct platform_device ks8692_device_lan = {
	.name		  = "ks8692-lan",
	.id		  = -1,
	.num_resources	  = ARRAY_SIZE(ks8692_lan_resource),
	.resource	  = ks8692_lan_resource,
	.dev              = {
		.dma_mask = &ks8692_device_lan_dmamask,
		.coherent_dma_mask = 0xffffffffUL
	}
};

EXPORT_SYMBOL(ks8692_device_lan);

/* SDI Controller */
static struct resource ks8692_sdi_resource[] = {
	[0] = {
		.start = KS8692_PA_SDI,
		.end   = KS8692_PA_SDI + KS8692_SZ_SDI - 1,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start = IRQ_SDIO,
		.end   = IRQ_SDIO,
		.flags = IORESOURCE_IRQ,
	}
};

static u64 ks8692_device_sdi_dmamask = 0xffffffffUL;

struct platform_device ks8692_device_sdi = {
	.name		  = "pegasus-sdhci",
	.id		  = -1,
	.num_resources	  = ARRAY_SIZE(ks8692_sdi_resource),
	.resource	  = ks8692_sdi_resource,
	.dev              = {
		.dma_mask = &ks8692_device_sdi_dmamask,
		.coherent_dma_mask = 0xffffffffUL
	}
};

EXPORT_SYMBOL(ks8692_device_sdi);


/* USB OHCI Controller */
static struct resource ks8692_ohci_resource[] = {
	[0] = {
		.start = KS8692_PA_OHCI,
		.end   = KS8692_PA_OHCI + KS8692_SZ_OHCI - 1,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start = IRQ_OHCI,
		.end   = IRQ_OHCI,
		.flags = IORESOURCE_IRQ,
	}
};

static u64 ks8692_device_ohci_dmamask = 0xffffffffUL;

struct platform_device ks8692_device_ohci = {
	.name		  = "pegasus-ohci",
	.id		  = -1,
	.num_resources	  = ARRAY_SIZE(ks8692_ohci_resource),
	.resource	  = ks8692_ohci_resource,
	.dev              = {
		.dma_mask = &ks8692_device_ohci_dmamask,
		.coherent_dma_mask = 0xffffffffUL
	}
};

EXPORT_SYMBOL(ks8692_device_ohci);

/* USB EHCI Controller */
static struct resource ks8692_ehci_resource[] = {
	[0] = {
		.start = KS8692_PA_EHCI,
		.end   = KS8692_PA_EHCI + KS8692_SZ_EHCI - 1,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start = IRQ_EHCI,
		.end   = IRQ_EHCI,
		.flags = IORESOURCE_IRQ,
	}
};

static u64 ks8692_device_ehci_dmamask = 0xffffffffUL;

struct platform_device ks8692_device_ehci = {
	.name		  = "pegasus-ehci",
	.id		  = -1,
	.num_resources	  = ARRAY_SIZE(ks8692_ehci_resource),
	.resource	  = ks8692_ehci_resource,
	.dev              = {
		.dma_mask = &ks8692_device_ehci_dmamask,
		.coherent_dma_mask = 0xffffffffUL
	}
};

EXPORT_SYMBOL(ks8692_device_ehci);

/* USB Device (Gadget)*/

static struct resource ks8692_usbgadget_resource[] = {
	[0] = {
		.start = KS8692_PA_USBDEVICE,
		.end   = KS8692_PA_USBDEVICE + KS8692_SZ_USBDEVICE - 1,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start = IRQ_USBDEVICE,
		.end   = IRQ_USBDEVICE,
		.flags = IORESOURCE_IRQ,
	}

};

struct platform_device ks8692_device_usbgadget = {
	.name		  = "pegasus-udc",
	.id		  = -1,
	.num_resources	  = ARRAY_SIZE(ks8692_usbgadget_resource),
	.resource	  = ks8692_usbgadget_resource,
};

EXPORT_SYMBOL(ks8692_device_usbgadget);

/* I2C Controller */
static struct resource ks8692_i2c_resource[] = {
	[0] = {
		.start = KS8692_PA_I2C,
		.end   = KS8692_PA_I2C + KS8692_SZ_I2C - 1,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start = IRQ_I2C,
		.end   = IRQ_I2C,
		.flags = IORESOURCE_IRQ,
	},
};

static u64 ks8692_device_i2c_dmamask = 0xffffffffUL;

struct platform_device ks8692_device_i2c = {
	.name		  = "pegasus-i2c",
	.id		  = -1,
	.num_resources	  = ARRAY_SIZE(ks8692_i2c_resource),
	.resource	  = ks8692_i2c_resource,
	.dev              = {
		.dma_mask = &ks8692_device_i2c_dmamask,
		.coherent_dma_mask = 0xffffffffUL
	}
};

EXPORT_SYMBOL(ks8692_device_i2c);


/* SPI Controller */
static struct resource ks8692_spi_resource[] = {
	[0] = {
		.start = KS8692_PA_SPI,
		.end   = KS8692_PA_SPI + KS8692_SZ_SPI - 1,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start = IRQ_SPI,
		.end   = IRQ_SPI,
		.flags = IORESOURCE_IRQ,
	},
};

#if defined(CONFIG_HAVE_SPI_KSZ8863)
static int cs_gpios[] = {
	KS_GPIO_0,
	KS_GPIO_15,
	KS_GPIO_14,
	-ENOENT
};
#else
static int cs_gpios[] = {
	-ENOENT,
	-ENOENT,
	-ENOENT,
	-ENOENT
};
#endif

static u64 ks8692_device_spi_dmamask = 0xffffffffUL;

struct platform_device ks8692_device_spi = {
	.name		  = "pegasus-spi",
	.id		  = 0,
	.num_resources	  = ARRAY_SIZE(ks8692_spi_resource),
	.resource	  = ks8692_spi_resource,
	.dev              = {
		.platform_data = cs_gpios,
		.dma_mask = &ks8692_device_spi_dmamask,
		.coherent_dma_mask = 0xffffffffUL
	}
};

EXPORT_SYMBOL(ks8692_device_spi);

#if defined(CONFIG_SPI_FTDI) || defined(CONFIG_SPI_FTDI_MODULE)
/* for ftdiusb spi master controller */
static u64 ftdiusb_device_spi_dmamask = 0xffffffffUL;

struct platform_device ftdiusb_device_spi = {
	.name		  = "ftdiusb-spi", // should same as this driver's name
	.id		  = 2, // should same as this driver's bus number
	.num_resources	  = 0,
	.resource	  = 0,
	.dev              = {
		.dma_mask = &ftdiusb_device_spi_dmamask,
		.coherent_dma_mask = 0xffffffffUL
	}
};

EXPORT_SYMBOL(ftdiusb_device_spi);
#endif

/* I2S Controller */
static struct resource ks8692_i2s_resource[] = {
	[0] = {
		.start = KS8692_PA_I2S,
		.end   = KS8692_PA_I2S + KS8692_SZ_I2S - 1,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start = IRQ_I2S_TX,
		.end   = IRQ_I2S_TX,
		.flags = IORESOURCE_IRQ,
	},
	[2] = {
		.start = IRQ_I2S_RX,
		.end   = IRQ_I2S_RX,
		.flags = IORESOURCE_IRQ,
	}
};

static u64 ks8692_device_i2s_dmamask = 0xffffffffUL;

struct platform_device ks8692_device_i2s = {
	.name		  = "snd_ks8692",
	.id		  = -1,
	.num_resources	  = ARRAY_SIZE(ks8692_i2s_resource),
	.resource	  = ks8692_i2s_resource,
	.dev              = {
		.dma_mask = &ks8692_device_i2s_dmamask,
		.coherent_dma_mask = 0xffffffffUL
	}
};

EXPORT_SYMBOL(ks8692_device_i2s);

#ifdef CONFIG_KSZ8462_HLI_EXT

/* data line is address bus (here, connect to A2) */
#define CMD_HIGH		0x04
/* (0x1c000000 + 0x03000000) */
#define KSZ8462HLI_PA_DATA	(0x1f000000)
#define KSZ8462HLI_PA_CMD	(0x1f000000 + CMD_HIGH)
#define KSZ8462HLI_SZ		4
#ifndef CONFIG_MICREL_FPGA_BOARD
#define IRQ_KSZ8462HLI		(LOW_IRQS+KS8692_INT_EXT_INT2)
#else
#define IRQ_KSZ8462HLI		(LOW_IRQS+KS8692_INT_EXT_INT0)
#endif

/* KSZ8462HLI Network Controller on external bus */
static struct resource ksz8462hli_resource[] = {
	[0] = {
		.start = KSZ8462HLI_PA_DATA,
		.end   = KSZ8462HLI_PA_DATA + KSZ8462HLI_SZ - 1,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start = KSZ8462HLI_PA_CMD ,
		.end   = KSZ8462HLI_PA_CMD + KSZ8462HLI_SZ - 1,
		.flags = IORESOURCE_MEM,
	},
	[2] = {
		.start = IRQ_KSZ8462HLI,
		.end   = IRQ_KSZ8462HLI,
		.flags = IORESOURCE_IRQ,
	},
};

static u64 ksz8462hli_device_dmamask = 0xffffffffUL;

struct platform_device ksz8462hli_device = {
	.name		= "ksz8462_hli",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(ksz8462hli_resource),
	.resource	= ksz8462hli_resource,
	.dev		= {
		.dma_mask = &ksz8462hli_device_dmamask,
		.coherent_dma_mask = 0xffffffffUL
	}
};

EXPORT_SYMBOL(ksz8462hli_device);

#endif /* #ifdef CONFIG_KSZ8462_HLI_EXT */
