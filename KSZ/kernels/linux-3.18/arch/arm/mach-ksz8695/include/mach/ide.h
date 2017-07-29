/*
 * linux/include/asm/ks8695/ide.h
 *
 * Copyright (c) 1998 Hugo Fiennes & Nicolas Pitre
 *
 * 18-aug-2000: Cleanup by Erik Mouw (J.A.K.Mouw@its.tudelft.nl)
 *              Get rid of the special ide_init_hwif_ports() functions
 *              and make a generalised function that can be used by all
 *              architectures.
 */
// Modified by LIQUN RUAN for KS8695P/PX
#include <linux/config.h>
#include <linux/version.h>
#include <asm/irq.h>
#include <asm/hardware.h>
#include <asm/mach-types.h>

#include "ks8695_utils.h"

//#define	DEBUG_THIS

#ifdef	DEBUG_THIS

static void ide_debug(unsigned long data_port)
{
	int i;
	unsigned long va;

#ifdef	DEBUG_THIS
	printk("%s\n", __FUNCTION__);
	printk("offset-------value\n");
	i = KS8695_2000;
	printk("0x%04x     0x%08x\n", i, KS8695_UTIL_READ_REG(i));
	i += 4;
	printk("0x%04x     0x%08x\n", i, KS8695_UTIL_READ_REG(i));
	i += 4;
	printk("0x%04x     0x%08x\n", i, KS8695_UTIL_READ_REG(i));
	i += 4;
	printk("0x%04x     0x%08x\n", i, KS8695_UTIL_READ_REG(i));
	i += 4;
	printk("0x%04x     0x%08x\n", i, KS8695_UTIL_READ_REG(i));
	i += 4;
	printk("0x%04x     0x%08x\n", i, KS8695_UTIL_READ_REG(i));
	i = KS8695_202C;
	printk("0x%04x     0x%08x\n", i, KS8695_UTIL_READ_REG(i));
	i = KS8695_203C;
	printk("0x%04x     0x%08x\n", i, KS8695_UTIL_READ_REG(i));
	i = KS8695_2100;
	printk("0x%04x     0x%08x\n", i, KS8695_UTIL_READ_REG(i));
	i = KS8695_2104;
	printk("0x%04x     0x%08x\n", i, KS8695_UTIL_READ_REG(i));
	i = KS8695_2200;
	printk("0x%04x     0x%08x\n", i, KS8695_UTIL_READ_REG(i));
	i += 4;
	printk("0x%04x     0x%08x\n", i, KS8695_UTIL_READ_REG(i));
	i += 4;
	printk("0x%04x     0x%08x\n", i, KS8695_UTIL_READ_REG(i));
	i += 4;
	printk("0x%04x     0x%08x\n", i, KS8695_UTIL_READ_REG(i));
	i += 4;
	printk("0x%04x     0x%08x\n", i, KS8695_UTIL_READ_REG(i));
	i += 4;
	printk("0x%04x     0x%08x\n", i, KS8695_UTIL_READ_REG(i));
	i += 4;
	printk("0x%04x     0x%08x\n", i, KS8695_UTIL_READ_REG(i));
	i += 4;
	printk("0x%04x     0x%08x\n", i, KS8695_UTIL_READ_REG(i));
	i += 4;
	printk("0x%04x     0x%08x\n", i, KS8695_UTIL_READ_REG(i));
	i += 4;
	printk("0x%04x     0x%08x\n", i, KS8695_UTIL_READ_REG(i));
#endif

	va = (unsigned long)ioremap((data_port & 0xffff0000), 0x1000);
	if (0 == va) {
		printk("%s: ioremap for va failed\n", __FUNCTION__);
	} else {
		printk("%s: data_port=0x%08lx\n", __FUNCTION__, data_port);
		for (i = 0; i < 8; i ++) {
			printk("offset: 0x%08lx val=0x%02x\n", va + i, inb(va + i));
		}
		iounmap((char *)va);
	}
}
#endif

/*
 * Set up a hw structure for a specified data port, control port and IRQ.
 * This should follow whatever the default interface uses.
 */
static __inline__ void ide_init_hwif_ports(hw_regs_t *hw, unsigned long data_port, unsigned long ctrl_port, int *irq)
{
	unsigned long reg = data_port;
	int i, inc = 1;

#ifdef	DEBUG_THIS
	printk("%s: data_port=0x%08lx, ctrl_port=0x%08lx\n", __FUNCTION__, data_port, ctrl_port);
#endif

	if (0 == data_port || 0 == ctrl_port) {
		return;
	}

#ifndef CONFIG_PCI_KS8695P_MAPPING
	// if PCI IO physical address, remap to virtual address
	if ((reg & 0xffff0000) == KS8695P_PCI_IO_BASE) {
		reg = (unsigned long)ioremap(reg, (IDE_STATUS_OFFSET - IDE_DATA_OFFSET) * inc);
		//do we have a place to do iounmap later??? 
	}
	if ((ctrl_port & 0xffff0000) == KS8695P_PCI_IO_BASE) {
		ctrl_port = (unsigned long)ioremap(ctrl_port, 1);
		//do we have a place to do iounmap later??? 
	}
#ifdef	DEBUG_THIS
	ide_debug(data_port);
	printk("%s: ctrl_port=0x%08lx, value=0x%02x\n", __FUNCTION__, ctrl_port, inb(ctrl_port));
#endif
#endif

	//RLQ, IDE_DATA_OFFSET 0, IDE_STATUS_OFFSET 7, defined in include/linux/ide.h
	for (i = IDE_DATA_OFFSET; i <= IDE_STATUS_OFFSET; i++) {
		hw->io_ports[i] = reg;
		reg += inc;
	}
	//RLQ, IDE_CONTROL_OFFSET 8, defined in include/linux/ide.h
	hw->io_ports[IDE_CONTROL_OFFSET] = ctrl_port;
}

/*
 * This registers the standard ports for this architecture with the IDE
 * driver.
 */
static __inline__ void ide_init_default_hwifs(void)
{
	/*RLQ, enable irq can't be execute here due to race condition, each individual driver needs to add it within the driver*/
}
