/*
 *  arch/arm/mach-ksz8692/board-micrel.c
 *
 *  Copyright (C) 2006-2015 Micrel, Inc.
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
 */
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/string.h>
#include <linux/export.h>
#include <linux/i2c.h>
#include <linux/spi/spi.h>

#include <linux/io.h>
#include <asm/irq.h>
#include <asm/setup.h>
#include <asm/system_info.h>
#include <asm/system_misc.h>
#include <linux/param.h>
#include <asm/mach-types.h>

#include <asm/mach/arch.h>
#include <asm/mach/flash.h>
#include <asm/mach/irq.h>
#include <asm/mach/map.h>

#include <linux/interrupt.h>
#include <asm/mach/time.h>

#include <mach/gpio.h>

#define IRQT_HIGH	IRQ_TYPE_LEVEL_HIGH
#define IRQT_LOW	IRQ_TYPE_LEVEL_LOW
#define IRQT_RISING	IRQ_TYPE_EDGE_RISING
#define IRQT_FALLING	IRQ_TYPE_EDGE_FALLING
#define IRQT_BOTHEDGE	IRQ_TYPE_EDGE_BOTH

unsigned int ksz_system_bus_clock;
EXPORT_SYMBOL(ksz_system_bus_clock);

int delay_softirq;
EXPORT_SYMBOL(delay_softirq);


#if defined(CONFIG_MTD_CFI)
#include <linux/mtd/physmap.h>

#ifndef CONFIG_MTD_PHYSMAP_LEN
#define CONFIG_MTD_PHYSMAP_LEN		0x800000
#endif

/* This is the size of the image that can be written. */
#define CONFIG_CENTAUR_IMAGE_SIZE  (CONFIG_MTD_PHYSMAP_LEN - \
	CONFIG_CENTAUR_LOADER_SIZE - CONFIG_CENTAUR_SPARE_SIZE)

/* This is the size of the root filesystem image that is supposedly read-only.
*/
#if defined(CONFIG_BLK_DEV_INITRD) || defined(CONFIG_CRAMFS) || \
	(defined(CONFIG_SQUASHFS) && !defined(CONFIG_MTD_ROOTFS_SPLIT))
#define CONFIG_CENTAUR_RAMDISK_OFFSET  (CONFIG_CENTAUR_LOADER_SIZE + \
	CONFIG_CENTAUR_KERNEL_SIZE)
#define CONFIG_CENTAUR_RAMDISK_SIZE    (CONFIG_CENTAUR_IMAGE_SIZE - \
	CONFIG_CENTAUR_KERNEL_SIZE - CONFIG_CENTAUR_FS_SIZE)
#define CONFIG_CENTAUR_FS_OFFSET       MTDPART_OFS_APPEND
#else
#define CONFIG_CENTAUR_RAMDISK_SIZE  0
#define CONFIG_CENTAUR_FS_OFFSET       (CONFIG_CENTAUR_LOADER_SIZE + \
	CONFIG_CENTAUR_KERNEL_SIZE)
#endif

#if (CONFIG_CENTAUR_FS_SIZE == 0)
#if defined(CONFIG_JFFS2_FS) || defined(CONFIG_MTD_ROOTFS_SPLIT)
#undef CONFIG_CENTAUR_FS_SIZE
#define CONFIG_CENTAUR_FS_SIZE		(CONFIG_CENTAUR_IMAGE_SIZE - \
	CONFIG_CENTAUR_KERNEL_SIZE)
#endif
#endif

static struct mtd_partition physmap_partitions[] = {
	{
		.name =		"loader",
		.size =		CONFIG_CENTAUR_LOADER_SIZE,
		.offset =	0,
		.mask_flags =	MTD_WRITEABLE,  /* force read-only */
	}, {
#if defined(CONFIG_MTD_ROOTFS_SPLIT)
		.name =		"image",
		.size =		CONFIG_CENTAUR_IMAGE_SIZE,
#else
		.name =		"linux",
		.size =		CONFIG_CENTAUR_KERNEL_SIZE,
		.mask_flags =	MTD_WRITEABLE,  /* force read-only */
#endif
		.offset =	MTDPART_OFS_APPEND,
	},

#if (CONFIG_CENTAUR_RAMDISK_SIZE != 0)
	{
		.name =		"rootfs",
		.offset =	CONFIG_CENTAUR_RAMDISK_OFFSET,
		.size =		CONFIG_CENTAUR_RAMDISK_SIZE,
		.mask_flags =	MTD_WRITEABLE,  /* force read-only */
	},
#endif

#if (CONFIG_CENTAUR_FS_SIZE != 0)
	{
#if (CONFIG_CENTAUR_RAMDISK_SIZE != 0)
		.name =		"rootfs_data",
#else
		.name =		"rootfs",
#endif
		.offset =	CONFIG_CENTAUR_FS_OFFSET,
		.size =		CONFIG_CENTAUR_FS_SIZE,
	},
#endif

#if (CONFIG_CENTAUR_SPARE_SIZE != 0)
	{
		.name =		"spare",
		.offset =	CONFIG_MTD_PHYSMAP_LEN -
			CONFIG_CENTAUR_SPARE_SIZE,
		.size =		CONFIG_CENTAUR_SPARE_SIZE,
	},
#endif
};

#define NUM_PARTITIONS	(sizeof(physmap_partitions) / \
	sizeof(struct mtd_partition))
#endif


/*
 * All IO addresses are mapped onto VA 0xFFFx.xxxx, where x.xxxx
 * is the (PA >> 12).
 *
 * Setup a VA for the Integrator interrupt controller (for header #0,
 * just for now).
 */


/*
 * Logical    Physical
 * F0000000   10000000   PCI I/O             PHYS_PCI_IO_BASE        (max 64K)
 * f0c80000   03200000   External IO         PHYS_EXTERNAL_IO_BASE   (max 16MB)
 * f0A00000   1C000000   Flash Space         PHYS_FLASH_MEM_BASE     (max 32MB)
 * F1FFF000   1FFF0000   Chip Register Base  PHYS_REG_BASE           (max 64K)
 * 20000000   20000000   Host bridge memory  PHYS_PCIBG_MEM_BASE     (max 256M)
 * C8xxx000   30000000   PCI memory          PHYS_PCI_MEM_BASE       (max 256M)
 * C0000000   00000000   System memory       PAGE_OFFSET             (max 256M)
 * D0000000                                  HIGH_MEMORY
 * D0800000                                  VMALLOC_START
 * E0000000                                  VMALLOC_END
 */

static struct map_desc ks8692_io_desc[] __initdata = {
	{
		(unsigned long) IO_ADDRESS(KS8692_IO_BASE),
		__phys_to_pfn(KS8692_IO_BASE),
		KS8692_IO_SIZE,
		MT_DEVICE
	}
	,
	{
		PCI_IO_VADDR + KS8692_PCI_IO_BASE,
		__phys_to_pfn(KS8692_PCI_IO_BASE),
		KS8692_PCI_IO_SIZE,
		MT_DEVICE
	}
};

static void __init ks8692_processor_info(void)
{
	unsigned long id, rev;

	id = __raw_readl(VIO(KS8692_DEVICE_ID));
	rev = __raw_readl(VIO(KS8692_REVISION_ID));

	printk(KERN_INFO "Pegasus ID=%04lx  SubID=%02lx  Revision=%02lx\n", id,
		(rev & (0x7 << 5)) >> 5, (rev & 0x1F));
	system_rev = rev & 0x1F;
	system_serial_high = (id << 16) | ((rev & (0x7 << 5)) << 3) |
		system_rev;
#ifdef CONFIG_KSZ8692VB
	if ((rev & 0x1F) < 2)
		printk(KERN_INFO "This kernel does not work for this chip.\n");
#endif
}

static unsigned int sysclk[4] = { 50000, 124997, 166662, 199995 };
static unsigned int cpuclk[8] = { 50, 125, 166, 200, 250, 250, 250, 250 };
static unsigned int ipsecclk[4] = { 50, 125, 166, 200 };
static unsigned int memclk[4] = { 100, 125, 166, 200 };
static unsigned int pciclk[2] = { 33, 66 };

static void __init ks8692_clock_info(void)
{
	unsigned int sys_clock = __raw_readl(VIO(KS8692_SYSTEM_BUS_CLOCK));
	int bus = sys_clock & SYSTEM_BUS_CLOCK_MASK;
	int mem = (sys_clock & MEM_CLOCK_MASK) >> 2;
	int cpu = (sys_clock & CPU_CLOCK_MASK) >> 4;
	int pci = (sys_clock & PCI_BUS_CLOCK_66) >> 7;
	int ipsec = (sys_clock & IPSEC_CLOCK_MASK) >> 9;

	printk(KERN_INFO
		"Clocks: System %u MHz, CPU %u MHz, DDR %u MHz, PCI %u MHz, \
IPsec %u MHz\n",
		(sysclk[bus] + 50) / 1000, cpuclk[cpu], memclk[mem],
		pciclk[pci], ipsecclk[ipsec]);
	ksz_system_bus_clock = sysclk[bus];

	/* Use calibrated value if available. */
	sys_clock = __raw_readl(VIO(0x6038));
	bus = sys_clock - ksz_system_bus_clock;
	if (abs(bus) < 10)
		ksz_system_bus_clock = sys_clock;
	printk(KERN_INFO "System bus %u KHz\n", ksz_system_bus_clock);
}

static void __init ks8692_map_io(void)
{
	iotable_init(ks8692_io_desc, ARRAY_SIZE(ks8692_io_desc));

	ks8692_processor_info();
	ks8692_clock_info();
}

#define KS8692_VALID_INT1	0xff0ff7f0
#define KS8692_VALID_INT2	0x03ffffff

#define KS8692_NO_MASK_IRQ1  (\
	(1 << KS8692_INT_LAN_STOP_RX) | \
	(1 << KS8692_INT_LAN_STOP_TX) | \
	(1 << KS8692_INT_LAN_BUF_RX_STATUS) | \
	(1 << KS8692_INT_LAN_BUF_TX_STATUS) | \
	(1 << KS8692_INT_LAN_RX_STATUS) | \
	(1 << KS8692_INT_LAN_TX_STATUS) | \
	(1 << KS8692_INT_WAN_STOP_RX) | \
	(1 << KS8692_INT_WAN_STOP_TX) | \
	(1 << KS8692_INT_WAN_BUF_RX_STATUS) | \
	(1 << KS8692_INT_WAN_BUF_TX_STATUS) | \
	(1 << KS8692_INT_WAN_RX_STATUS) | \
	(1 << KS8692_INT_WAN_TX_STATUS) | \
	0)

#define KS8692_NO_MASK_IRQ2  (\
	(1 << KS8692_INT_UART1_TX) | \
	(1 << KS8692_INT_UART1_RX) | \
	(1 << KS8692_INT_UART1_LINE_ERR) | \
	(1 << KS8692_INT_UART1_MODEMS) | \
	(1 << KS8692_INT_UART2_TX) | \
	(1 << KS8692_INT_UART2_RX) | \
	(1 << KS8692_INT_UART2_LINE_ERR) | \
	(1 << KS8692_INT_UART3_TX) | \
	(1 << KS8692_INT_UART3_RX) | \
	(1 << KS8692_INT_UART3_LINE_ERR) | \
	(1 << KS8692_INT_UART4_TX) | \
	(1 << KS8692_INT_UART4_RX) | \
	(1 << KS8692_INT_UART4_LINE_ERR) | \
	0)


static void sc_ack_irq1(struct irq_data *d)
{
	__raw_writel((1 << d->irq), VIO(KS8692_INT_STATUS1));
}

static void sc_ack_irq2(struct irq_data *d)
{
	unsigned int irq = d->irq - LOW_IRQS;
	__raw_writel((1 << irq), VIO(KS8692_INT_STATUS2));
}

static void sc_mask_irq1(struct irq_data *d)
{
	__raw_writel(__raw_readl(VIO(KS8692_INT_ENABLE1)) &
		~(1 << d->irq), VIO(KS8692_INT_ENABLE1));
}

static void sc_mask_irq2(struct irq_data *d)
{
	unsigned int irq = d->irq - LOW_IRQS;
	__raw_writel(__raw_readl(VIO(KS8692_INT_ENABLE2)) &
		~(1 << irq), VIO(KS8692_INT_ENABLE2));
}

static void sc_mask_ack_irq1(struct irq_data *d)
{
	__raw_writel(__raw_readl(VIO(KS8692_INT_ENABLE1)) &
		~(1 << d->irq), VIO(KS8692_INT_ENABLE1));
	__raw_writel((1 << d->irq), VIO(KS8692_INT_STATUS1));
}

static void sc_mask_ack_irq2(struct irq_data *d)
{
	unsigned int irq = d->irq - LOW_IRQS;
	__raw_writel(__raw_readl(VIO(KS8692_INT_ENABLE2)) &
		~(1 << irq), VIO(KS8692_INT_ENABLE2));
	__raw_writel((1 << irq), VIO(KS8692_INT_STATUS2));
}

static void sc_unmask_irq1(struct irq_data *d)
{
	__raw_writel(__raw_readl(VIO(KS8692_INT_ENABLE1)) |
		(1 << d->irq), VIO(KS8692_INT_ENABLE1));
}

static void sc_unmask_irq2(struct irq_data *d)
{
	unsigned int irq = d->irq - LOW_IRQS;
	__raw_writel(__raw_readl(VIO(KS8692_INT_ENABLE2)) |
		(1 << irq), VIO(KS8692_INT_ENABLE2));
}

static unsigned int sc_startup(struct irq_data *d)
{
	if (KS8692_INT_EXT_INT0 + LOW_IRQS <= d->irq &&
			d->irq <= KS8692_INT_EXT_INT3 + LOW_IRQS)
		ksz_gpio_enable(irq_to_gpio(d->irq), 1);
	sc_unmask_irq2(d);
	return 0;
}

static void sc_shutdown(struct irq_data *d)
{
	sc_mask_irq2(d);
	if (KS8692_INT_EXT_INT0 + LOW_IRQS <= d->irq &&
			d->irq <= KS8692_INT_EXT_INT3 + LOW_IRQS)
		ksz_gpio_enable(irq_to_gpio(d->irq), 0);
}

static int sc_irq_set_type(struct irq_data *d, unsigned int type)
{
	unsigned int ctrl, mode;
	unsigned int gpio;
	int level_triggered = 0;

	if (KS8692_INT_EXT_INT0 + LOW_IRQS > d->irq ||
			d->irq > KS8692_INT_EXT_INT3 + LOW_IRQS)
		return -EINVAL;

	gpio = d->irq;
	gpio -= KS8692_INT_EXT_INT0 + LOW_IRQS;
	gpio <<= 2;

	ctrl = KS_R(KS8692_GPIO_CTRL);
	ctrl &= ~(0x7 << gpio);

	mode = GPIO_INT_LOW;
	switch (type) {
	case IRQT_LOW:
		level_triggered = 1;
		break;
	case IRQT_HIGH:
		mode = GPIO_INT_HIGH;
		level_triggered = 1;
		break;
	case IRQT_RISING:
		mode = GPIO_INT_RISE_EDGE;
		break;
	case IRQT_FALLING:
		mode = GPIO_INT_FALL_EDGE;
		break;
	case IRQT_BOTHEDGE:
		mode = GPIO_INT_BOTH_EDGE;
		break;
	default:
		return -EINVAL;
	}

	if (level_triggered)
		__irq_set_handler_locked(d->irq, handle_level_irq);
	else
		__irq_set_handler_locked(d->irq, handle_edge_irq);

	ctrl |= mode << gpio;
	KS_W(KS8692_GPIO_CTRL, ctrl);
	return 0;
}

static struct irq_chip sc_chip1 = {
	.name = "pegasus",
	.irq_mask_ack = sc_mask_ack_irq1,
	.irq_ack = sc_ack_irq1,
	.irq_mask = sc_mask_irq1,
	.irq_unmask = sc_unmask_irq1,
};

static struct irq_chip sc_chip2 = {
	.name = "pegasus",
	.irq_startup = sc_startup,
	.irq_shutdown = sc_shutdown,
	.irq_set_type = sc_irq_set_type,
	.irq_mask_ack = sc_mask_ack_irq2,
	.irq_ack = sc_ack_irq2,
	.irq_mask = sc_mask_irq2,
	.irq_unmask = sc_unmask_irq2,
};

static void __init ks8692_init_irq(void)
{
	unsigned int i;
	unsigned int j;

	/* Disable all interrupts initially. */
	__raw_writel(0, VIO(KS8692_INT_CONTL1));
	__raw_writel(0, VIO(KS8692_INT_CONTL2));
	__raw_writel(0, VIO(KS8692_INT_ENABLE1));
	__raw_writel(0, VIO(KS8692_INT_ENABLE2));

	/* Assign low IRQ (0 - 31) */
	for (i = 0; i < LOW_IRQS; i++) {
		if (((1 << i) & KS8692_VALID_INT1) != 0) {
			if (((1 << i) & KS8692_NO_MASK_IRQ1) != 0)
				irq_set_chip_and_handler(i, &dummy_irq_chip,
					handle_level_irq);
			else
				irq_set_chip_and_handler(i, &sc_chip1,
					handle_level_irq);
			set_irq_flags(i, IRQF_VALID | IRQF_PROBE);
		}
	}

	/* Assign high IRQ (32 - 63) */
	for (i = LOW_IRQS, j = 0; i < NR_IRQS; i++, j++) {
		if (((1 << j) & KS8692_VALID_INT2) != 0) {
			if (((1 << j) & KS8692_NO_MASK_IRQ2) != 0)
				irq_set_chip_and_handler(i, &dummy_irq_chip,
					handle_level_irq);
			else
				irq_set_chip_and_handler(i, &sc_chip2,
					handle_level_irq);
			set_irq_flags(i, IRQF_VALID | IRQF_PROBE);
		}
	}
}

#ifdef CONFIG_MTD_CFI
static struct physmap_flash_data ks8692_flash_data = {
	.width		= 2,
	.nr_parts	= ARRAY_SIZE(physmap_partitions),
	.parts		= physmap_partitions,
};

static struct resource cfi_flash_resource = {
	.start		= KS8692_FLASH_START,
	.end		= KS8692_FLASH_START + CONFIG_MTD_PHYSMAP_LEN - 1,
	.flags		= IORESOURCE_MEM,
};

static struct platform_device cfi_flash_device = {
	.name		= "physmap-flash",
	.id		= 0,
	.dev		= {
		.platform_data = &ks8692_flash_data,
	},
	.num_resources	= 1,
	.resource	= &cfi_flash_resource,
};
#endif

#if defined(CONFIG_MICREL_WATCHDOG) || defined(CONFIG_MICREL_WATCHDOG_MODULE)
static struct platform_device watchdog_device = {
	.name		= "micrel_wdt",
	.id		= -1,
	.num_resources	= 0,
};
#endif


#include "devs.c"

struct ks8692_board {
	struct platform_device  **devices;
	unsigned int              devices_count;
};

static struct platform_device *ks8692_devices[] __initdata = {
#if 0
	&ks8692_device_syscfg1,
	&ks8692_device_pci,
	&ks8692_device_ddr,
	&ks8692_device_sdram,
	&ks8692_device_wan,
	&ks8692_device_lan,
#endif
	&ks8692_device_usbgadget,
	&ks8692_device_ohci,
	&ks8692_device_ehci,
	&ks8692_device_i2c,
	&ks8692_device_sdi,
	&ks8692_device_spi,
#if defined(CONFIG_SPI_FTDI) || defined(CONFIG_SPI_FTDI_MODULE)
	&ftdiusb_device_spi,
#endif
#ifdef CONFIG_KSZ8462_HLI_EXT
	&ksz8462hli_device,
#endif
#if 0
	&ks8692_device_syscfg2,
#endif

};

static struct ks8692_board _ks8692_board __initdata = {
	.devices       = ks8692_devices,
	.devices_count = ARRAY_SIZE(ks8692_devices)
};

void ks8692_set_ext_bus(void)
{
#define EXT_IO_CTRL_VALUE       0xc0300000 /* 0xc0300041 */

	unsigned long dwData;

	/* Set external bus to base address is 0x03000000, 16-bit data bus */
	KS_W(KS8692_IO_CTRL0, EXT_IO_CTRL_VALUE);

	dwData = KS_R(KS8692_MEM_GENERAL);
	dwData &= ~(0xf0000000);
	dwData |= (ROM_TIME_MULTIPLER_1 | EXT_IO0_DW16);
	KS_W(KS8692_MEM_GENERAL, dwData);
}

static int ks8692_add_devices(struct ks8692_board *board)
{
	int ret;

	if (board != NULL) {
		struct platform_device **ptr = board->devices;
		int i;

		for (i = 0; i < board->devices_count; i++, ptr++) {
			ret = platform_device_register(*ptr);
			if (ret)
				printk(KERN_ERR
					"failed to add device %s (%d) @%p\n",
					(*ptr)->name, ret, *ptr);
		}

		/* mask any error, we may not need all these board
		 * devices */
		ret = 0;
	}

#ifdef CONFIG_KSZ8462_HLI_EXT
	ks8692_set_ext_bus();
#endif /* #ifdef CONFIG_KS846X_HLL_EXT */
#if defined(CONFIG_KS8851_MLL) || defined(CONFIG_KS8851_MLL_MODULE)
	ks8692_set_ext_bus();
#endif

	return ret;
}

#ifdef CONFIG_RTC_DRV_DS1307
static struct i2c_board_info __initdata pegasus_i2c_board_info[] = {
	{
		I2C_BOARD_INFO("rtc-ds1307", 0x68),
	},
};

static int __init pegasus_i2c_init(void)
{
	return i2c_register_board_info(0, pegasus_i2c_board_info,
				       ARRAY_SIZE(pegasus_i2c_board_info));
}
arch_initcall(pegasus_i2c_init);
#endif

#ifdef CONFIG_I2C_GPIO
#include <linux/i2c-gpio.h>

static struct i2c_gpio_platform_data i2c_gpio_data = {
	.sda_pin		= 12,
	.scl_pin		= 13,
	.sda_is_open_drain	= 0,
	.scl_is_open_drain	= 0,
	.scl_is_output_only	= 1,
	.udelay			= 1,
	.timeout		= 1,
};

struct platform_device i2c_gpio_master = {
	.name		= "i2c-gpio",
	.id		= -1,
	.num_resources	= 0,
	.resource	= NULL,
	.dev		= {
		.platform_data = &i2c_gpio_data,
	},
};

static int __init i2c_gpio_init(void)
{
	return platform_device_register(&i2c_gpio_master);
}
arch_initcall(i2c_gpio_init);
#endif

#include "setup_ks8851.c"
#include "setup_ksz8851_mll.c"
#include "setup_ksz8463.c"
#include "setup_ksz8863.c"
#include "setup_ksz8795.c"
#include "setup_ksz8895.c"
#include "setup_ksz9897.c"
#include "setup_spidev.c"

#ifdef CONFIG_SPI_FTDI
static void *pegasus_late_call[5];
static int pegasus_call_ptr;

void pegasus_init_late_call(void)
{
	void (*func)(void);
	int i = 0;

	func = pegasus_late_call[i++];
	while (func) {
		func();
		func = pegasus_late_call[i++];
	}
}
EXPORT_SYMBOL(pegasus_init_late_call);

void pegasus_register_late_call(void *func)
{
	if (pegasus_call_ptr < 4)
		pegasus_late_call[pegasus_call_ptr++] = func;
}
EXPORT_SYMBOL(pegasus_register_late_call);

static int __init pegasus_ftdi_init(void)
{
	int i;

	for (i = 0; i < 5; i++)
		pegasus_late_call[i] = NULL;
	return 0;
}
arch_initcall(pegasus_ftdi_init);
#endif

static void __init ks8692_init(void)
{
	ksz_register_gpios();

#if defined(CONFIG_MICREL_WATCHDOG) || defined(CONFIG_MICREL_WATCHDOG_MODULE)
	platform_device_register(&watchdog_device);
#endif
	ks8692_add_devices(&_ks8692_board);

#ifdef CONFIG_MTD_CFI
	platform_device_register(&cfi_flash_device);
#endif
}


/*
 * How long is the timer interval?
 */
#define TIMER_CORRECTION	(-6)

#define TIMER_INTERVAL	     (TICKS_PER_uSEC * 1000000 / CONFIG_HZ + \
	TIMER_CORRECTION)
#define TIMER_DATA_VALUE     (TIMER_INTERVAL >> 1)
#define TIMER_PULSE_VALUE    (TIMER_INTERVAL - TIMER_DATA_VALUE)
#define TIMER_VALUE          (TIMER_DATA_VALUE + TIMER_PULSE_VALUE)
#define TICKS2USECS(x)	     ((x) / TICKS_PER_uSEC)
#define TIMER_GET_VALUE()    (__raw_readl(VIO(KS8692_TIMER1)) + \
	__raw_readl(VIO(KS8692_TIMER1_PCOUNT)))

#ifdef CONFIG_DELAYED_TIMER
static inline void disable_timer0(void)
{
	unsigned long reg;

	reg = KS_R(KS8692_TIMER_CTRL);
	reg &= ~(TIMER_TIME0_ENABLE);
	KS_W(KS8692_TIMER_CTRL, reg);
}  /* disable_timer0 */

static inline void enable_timer0(void)
{
	unsigned long reg;

	reg = KS_R(KS8692_TIMER_CTRL);
	reg |= TIMER_TIME0_ENABLE;
	KS_W(KS8692_TIMER_CTRL, reg);
}  /* enable_timer0 */

static inline void setup_timer0(unsigned int microsec)
{
	unsigned long interval;
	unsigned long pcount;
	unsigned long value;

	interval = TICKS_PER_uSEC * microsec;
	value = interval >> 1;
	pcount = interval - value;
	KS_W(KS8692_TIMER0, value);
	KS_W(KS8692_TIMER0_PCOUNT, pcount);
	enable_timer0();
}  /* setup_timer0 */

static struct delayed_tasklet delayed_tasklet_list = { NULL, 0 };

void tasklet_delayed_kill(struct delayed_tasklet *t)
{
	while (t->count)
		yield();
}  /* tasklet_delayed_kill */
EXPORT_SYMBOL(tasklet_delayed_kill);

void tasklet_delayed_schedule(struct delayed_tasklet *t, unsigned int microsec)
{
	unsigned long flags;

	microsec /= DELAYED_TIMER_RESOLUTION;
	if (!microsec)
		microsec = 1;
	t->count = microsec;
	local_irq_save(flags);
	if (!delayed_tasklet_list.next)
		setup_timer0(DELAYED_TIMER_RESOLUTION);
	t->next = delayed_tasklet_list.next;
	delayed_tasklet_list.next = t;
	local_irq_restore(flags);
}
EXPORT_SYMBOL(tasklet_delayed_schedule);

irqreturn_t
delayed_timer_interrupt(int irq, void *dev_id)
{
	struct delayed_tasklet *prev = &delayed_tasklet_list;
	struct delayed_tasklet *list = delayed_tasklet_list.next;

	KS_W(KS8692_INT_STATUS2, KS8692_INTMASK_TIMERINT0);

	while (list) {
		struct delayed_tasklet *t = list;

		list = list->next;

		if (!(--t->count)) {
			tasklet_schedule(&t->tasklet);
			prev->next = t->next;
			continue;
		}
		prev = t;
	}
	if (!delayed_tasklet_list.next)
		disable_timer0();

	return IRQ_HANDLED;
}  /* delayed_timer_interrupt */

static struct irqaction delayed_timer_irq = {
	.name		= "delayed timer",
	.flags		= 0,
	.handler	= delayed_timer_interrupt
};
#endif

#include "time.c"


static void ks8692_restart(enum reboot_mode mode, const char* cmd)
{
	unsigned int val;

	if (mode == REBOOT_SOFT)
		soft_restart(0);

	/*
	 * To reset, use the watchdog timer
	 */
	/*
	 * Need to turn off timer 1 also lest old U-Boot code cannot setup the
	 * clock properly.
	 */
	val = 0;
	__raw_writel(val, VIO(KS8692_TIMER_CTRL));
	val = (10 << 8) | 0xFF;
	__raw_writel(val, VIO(KS8692_TIMER0));
	__raw_writel(2, VIO(KS8692_TIMER0_PCOUNT));
	val = __raw_readl(VIO(KS8692_TIMER_CTRL)) | TIMER_TIME0_ENABLE;
	__raw_writel(val, VIO(KS8692_TIMER_CTRL));
}

MACHINE_START(MICREL_PEGASUS, "Micrel Pegasus")
	/* Maintainer: Micrel, Inc. */
	.atag_offset	= 0x00000100,
	.init_machine	= ks8692_init,
	.map_io		= ks8692_map_io,
	.init_irq	= ks8692_init_irq,
	.init_time	= pegasus_timer_init,
	.restart	= ks8692_restart,
MACHINE_END
