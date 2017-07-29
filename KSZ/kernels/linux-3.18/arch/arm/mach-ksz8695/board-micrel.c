/*
 *  arch/arm/mach-ksz8695/board-micrel.c
 *
 *  Copyright (C) 2004-2015 Micrel, Inc.
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

#include <mach/ks8695_utils.h>

int delay_softirq;
EXPORT_SYMBOL(delay_softirq);


#include <linux/mtd/physmap.h>

#ifndef CONFIG_MTD_PHYSMAP_LEN
#define CONFIG_MTD_PHYSMAP_LEN		0x400000
#endif

/* This is the size of the image that can be written. */
#define CONFIG_CENTAUR_IMAGE_SIZE  (CONFIG_MTD_PHYSMAP_LEN - \
	CONFIG_CENTAUR_LOADER_SIZE)

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
};

#define NUM_PARTITIONS	(sizeof(physmap_partitions) / \
	sizeof(struct mtd_partition))


/*
 * All IO addresses are mapped onto VA 0xFFFx.xxxx, where x.xxxx
 * is the (PA >> 12).
 *
 * Setup a VA for the Integrator interrupt controller (for header #0,
 * just for now).
 */

#define PCI_IO_VADDR		0xE0000000

/*
 * Logical    Physical
 * 10000000   10000000   PCI memory          PHYS_PCI_MEM_BASE       (max 512M)
 * 08000000   08000000   PCI I/O             PHYS_PCI_IO_BASE        (max 16M)
 * f0ffc000   03ff0000   Chip Register Base  PHYS_REG_BASE           (max 64K)
 * f0c80000   03200000   External IO         PHYS_EXTERNAL_IO_BASE   (max 16MB)
 * f0A00000   02800000   Flash Space         PHYS_FLASH_MEM_BASE     (max 8MB)
 */

static struct map_desc ks8695_io_desc[] __initdata = {
	{
		(unsigned long) IO_ADDRESS(KS8695_IO_BASE),
		__phys_to_pfn(KS8695_IO_BASE),
		KS8695_IO_SIZE,
		MT_DEVICE
	}
	,
	{
		(unsigned long) PCI_IO_VADDR + KS8695P_PCI_IO_BASE,
		__phys_to_pfn(KS8695P_PCI_IO_BASE),
		KS8695P_PCI_IO_SIZE,
		MT_DEVICE
	}
};

static void __init ks8695_processor_info(void)
{
	unsigned long id, rev;

	id = __raw_readl(KS_VIO_BASE + KS8695_DEVICE_ID);
	rev = __raw_readl(KS_VIO_BASE + KS8695_REVISION_ID);

	printk(KERN_INFO "Centaur ID=%04lx  SubID=%02lx  Revision=%02lx\n", id,
		(rev & (0xF << 4)) >> 4, (rev & 0xF));
	system_rev = rev & 0xF;
	system_serial_high = (id << 16) | ((rev & (0xF << 4)) << 4) |
		system_rev;
}

static unsigned int sysclk[8] = { 25000, 31300, 33300, 41700, 50000, 62500,
	100000, 125000 };
static unsigned int cpuclk[8] = { 415, 415, 553, 553, 830, 830, 1660, 1660 };

static void __init ks8695_clock_info(void)
{
	unsigned int sys_clock =
		__raw_readl(KS_VIO_BASE + KS8695_SYSTEN_BUS_CLOCK);
	int bus = 7 - (sys_clock & 7);

	printk(KERN_INFO "Clocks: System %u.%u MHz, CPU %u.%u MHz\n",
		sysclk[bus] / 1000, (sysclk[bus] % 1000) / 100,
		cpuclk[bus] / 10, cpuclk[bus] % 10);
}

static void __init ks8695_map_io(void)
{
	iotable_init(ks8695_io_desc, ARRAY_SIZE(ks8695_io_desc));

	ks8695_processor_info();
	ks8695_clock_info();
}

#define KS8695_VALID_INT	0xff03ffff

#define KS8695_NO_MASK_IRQ  (\
	(1 << KS8695_INT_UART_TX) | \
	(1 << KS8695_INT_UART_RX) | \
	(1 << KS8695_INT_UART_LINE_ERR) | \
	(1 << KS8695_INT_UART_MODEMS) | \
	(1 << KS8695_INT_LAN_STOP_RX) | \
	(1 << KS8695_INT_LAN_STOP_TX) | \
	(1 << KS8695_INT_LAN_BUF_RX_STATUS) | \
	(1 << KS8695_INT_LAN_BUF_TX_STATUS) | \
	(1 << KS8695_INT_LAN_RX_STATUS) | \
	(1 << KS8695_INT_LAN_TX_STATUS) | \
	(1 << KS8695_INT_WAN_STOP_RX) | \
	(1 << KS8695_INT_WAN_STOP_TX) | \
	(1 << KS8695_INT_WAN_BUF_RX_STATUS) | \
	(1 << KS8695_INT_WAN_BUF_TX_STATUS) | \
	(1 << KS8695_INT_WAN_RX_STATUS) | \
	(1 << KS8695_INT_WAN_TX_STATUS) | \
	(1 << KS8695_INT_WAN_PHY_STATUS) | \
	0)

static void sc_ack_irq(struct irq_data *d)
{
	__raw_writel((1 << d->irq), KS_VIO_BASE + KS8695_INT_STATUS);
}

static void sc_mask_irq(struct irq_data *d)
{
	__raw_writel(__raw_readl(KS_VIO_BASE + KS8695_INT_ENABLE) &
		~(1 << d->irq), KS_VIO_BASE + KS8695_INT_ENABLE);
}

static void sc_mask_ack_irq(struct irq_data *d)
{
	__raw_writel(__raw_readl(KS_VIO_BASE + KS8695_INT_ENABLE) &
		~(1 << d->irq), KS_VIO_BASE + KS8695_INT_ENABLE);
	__raw_writel((1 << d->irq), KS_VIO_BASE + KS8695_INT_STATUS);
}

static void sc_unmask_irq(struct irq_data *d)
{
	__raw_writel(__raw_readl(KS_VIO_BASE + KS8695_INT_ENABLE) |
		(1 << d->irq), KS_VIO_BASE + KS8695_INT_ENABLE);
}

static unsigned int sc_startup(struct irq_data *d)
{
	if (2 <= d->irq && d->irq <= 5)
		ks8695_util_enable_interrupt(d->irq, 1);
	sc_unmask_irq(d);
	return 0;
}

static void sc_shutdown(struct irq_data *d)
{
	sc_mask_irq(d);
	if (2 <= d->irq && d->irq <= 5)
		ks8695_util_enable_interrupt(d->irq, 0);
}

static struct irq_chip sc_chip = {
	.name	= "centaur",
	.irq_startup = sc_startup,
	.irq_shutdown = sc_shutdown,
	.irq_mask_ack = sc_mask_ack_irq,
	.irq_ack = sc_ack_irq,
	.irq_mask = sc_mask_irq,
	.irq_unmask = sc_unmask_irq,
};

static void __init ks8695_init_irq(void)
{
	unsigned int i;

	/* Disable all interrupts initially. */
	__raw_writel(0, KS_VIO_BASE + KS8695_INT_CONTL);
	__raw_writel(0, KS_VIO_BASE + KS8695_INT_ENABLE);

	for (i = 0; i < NR_IRQS; i++) {
		if (((1 << i) & KS8695_VALID_INT) != 0) {
			if (((1 << i) & KS8695_NO_MASK_IRQ) != 0)
				irq_set_chip_and_handler(i, &dummy_irq_chip,
					handle_level_irq);
			else
				irq_set_chip_and_handler(i, &sc_chip,
					handle_level_irq);
			set_irq_flags(i, IRQF_VALID | IRQF_PROBE);
		}
	}

#ifdef CONFIG_KS884X_LOAD_BOARD
	ks8695_util_enable_interrupt(2, 1);
#endif
}

#ifdef CONFIG_MTD_CFI
static struct physmap_flash_data ks8695_flash_data = {
#if defined(CONFIG_ARCH_KS8695PM) || defined(CONFIG_ARCH_KS8695MB)
	.width		= 1,
#elif defined(CONFIG_ARCH_KS8695L) || defined(CONFIG_ARCH_KS8695V)
	.width          = 2,
#else
	.width          = 1,
#endif
	.nr_parts	= ARRAY_SIZE(physmap_partitions),
	.parts		= physmap_partitions,
};

static struct resource cfi_flash_resource = {
	.start		= KS8695_FLASH_START,
	.end		= KS8695_FLASH_START + CONFIG_MTD_PHYSMAP_LEN - 1,
	.flags		= IORESOURCE_MEM,
};

static struct platform_device cfi_flash_device = {
	.name		= "physmap-flash",
	.id		= 0,
	.dev		= {
		.platform_data = &ks8695_flash_data,
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

static void __init ks8695_init(void)
{

#if defined(CONFIG_MICREL_WATCHDOG) || defined(CONFIG_MICREL_WATCHDOG_MODULE)
	platform_device_register(&watchdog_device);
#endif

#ifdef CONFIG_MTD_CFI
	platform_device_register(&cfi_flash_device);
#endif
}


/*
 * Where is the timer (VA)?
 */
#define TIMER_VA_BASE		IO_ADDRESS(KS8695_IO_BASE)

/*
 * How long is the timer interval?
 */
#define TIMER_INTERVAL	     (TICKS_PER_uSEC * 1000000 / CONFIG_HZ)
#define TIMER_DATA_VALUE     (TIMER_INTERVAL >> 1)
#define TIMER_PULSE_VALUE    (TIMER_INTERVAL - TIMER_DATA_VALUE)
#define TIMER_VALUE          (TIMER_DATA_VALUE + TIMER_PULSE_VALUE)
#define TICKS2USECS(x)	     ((x) / TICKS_PER_uSEC)
#define TIMER_GET_VALUE(x)   (__raw_readl(x + KS8695_TIMER1) + \
	__raw_readl(x + KS8695_TIMER1_PCOUNT))


#ifdef CONFIG_DELAYED_TIMER
static inline void disable_timer0(void)
{
	unsigned long reg;

	reg = KS_R(KS8695_TIMER_CTRL);
	reg &= ~(TIMER_TIME0_ENABLE);
	KS_W(KS8695_TIMER_CTRL, reg);
}  /* disable_timer0 */

static inline void enable_timer0(void)
{
	unsigned long reg;

	reg = KS_R(KS8695_TIMER_CTRL);
	reg |= TIMER_TIME0_ENABLE;
	KS_W(KS8695_TIMER_CTRL, reg);
}  /* enable_timer0 */

static inline void setup_timer0(unsigned int microsec)
{
	unsigned long interval;
	unsigned long pcount;
	unsigned long value;

	interval = TICKS_PER_uSEC * microsec;
	value = interval >> 1;
	pcount = interval - value;
	KS_W(KS8695_TIMER0, value);
	KS_W(KS8695_TIMER0_PCOUNT, pcount);
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

	KS_W(KS8695_INT_STATUS, KS8695_INTMASK_TIMERINT0);

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


static void ks8695_restart(enum reboot_mode mode, const char* cmd)
{
	unsigned int val;

	if (mode == REBOOT_SOFT)
		soft_restart(0);

	/*
	 * To reset, use the watchdog timer
	 */
	val = __raw_readl(TIMER_VA_BASE + KS8695_TIMER_CTRL) & 0x02;
	__raw_writel(val, TIMER_VA_BASE + KS8695_TIMER_CTRL);
	val = (10 << 8) | 0xFF;
	__raw_writel(val, TIMER_VA_BASE + KS8695_TIMER0);
	val = __raw_readl(TIMER_VA_BASE + KS8695_TIMER_CTRL) | 0x01;
	__raw_writel(val, TIMER_VA_BASE + KS8695_TIMER_CTRL);
}

MACHINE_START(MICREL_CENTAUR, "Micrel Centaur")
	/* Maintainer: Micrel, Inc. */
	.atag_offset	= 0x00000100,
	.init_machine	= ks8695_init,
	.map_io		= ks8695_map_io,
	.init_irq	= ks8695_init_irq,
	.init_time	= centaur_timer_init,
	.restart	= ks8695_restart,
MACHINE_END
