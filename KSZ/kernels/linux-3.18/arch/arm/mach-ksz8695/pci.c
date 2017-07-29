/*
	Copyright (c) 2003-2012, Micrel, Inc.

	Written 2003 by LIQUN RUAN

	This software may be used and distributed according to the terms of
	the GNU General Public License (GPL), incorporated herein by reference.
	Drivers based on or derived from this code fall under the GPL and must
	retain the authorship, copyright and license notice. This file is not
	a complete program and may only be used when the entire operating
	system is licensed under the GPL.

	The author can be reached as liqun.ruan@micrel.com
	Micrel, Inc.
	1931 Fortune Drive
	San Jose, CA 95131

	This driver is for Micrel's KSZ8695P Chipset as PCI bridge driver.

	Support and updates available at
	www.kendin.com or www.micrel.com

*/

#include <linux/sched.h>
#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/pci.h>
#include <linux/ptrace.h>
#include <linux/interrupt.h>
#include <linux/mm.h>
#include <linux/init.h>
#include <linux/ioport.h>

#include <asm/mach/pci.h>
#include <mach/hardware.h>
#include "ks8695_io.h"

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
#define	KS8695_PBCA			0x2100
#define	KS8695_2100			0x2100
#define	KS8695_PBCD			0x2104
#define	KS8695_2104			0x2104

/* bridge mode related registers */
#define	KS8695_PBM			0x2200
#define	KS8695_2200			0x2200
#define	KS8695_PBCS			0x2204
#define	KS8695_2204			0x2204
#define	KS8695_PMBA			0x2208
#define	KS8695_2208			0x2208
#define	KS8695_PMBAC			0x220c
#define	KS8695_220C			0x220c
#define	KS8695_PMBAM			0x2210
#define	KS8695_2210			0x2210
#define	KS8695_PMBAT			0x2214
#define	KS8695_2214			0x2214
#define	KS8695_PIOBA			0x2218
#define	KS8695_2218			0x2218
#define	KS8695_PIOBAC			0x221c
#define	KS8695_221C			0x221c
#define	KS8695_PIOBAM			0x2220
#define	KS8695_2220			0x2220
#define	KS8695_PIOBAT			0x2224
#define	KS8695_2224			0x2224

/* Since there is no extra bridge in KS8695P reference board, we only need to
 * support type 0 configuration space access, but not type 1.
 *
 * Also use:
 *	IDSEL 16 for slot 1,
 *	IDSEL 17 for slot 2,
 *	IDSEL 18 for bridge if it is configured as a guest device.
 */
#define CONFIG_CMD(but, devfn, where)	\
	(0x80000000 | (bus->number << 16) | (devfn << 8) | \
	(where & 0xfffffffc))

static DEFINE_SPINLOCK(ks8695p_lock);


static int ks8695p_read_config(struct pci_bus *bus, unsigned int devfn,
	int where, int size, u32 *val)
{
	u32 reg, shift;
	unsigned long flags;

	spin_lock_irqsave(&ks8695p_lock, flags);
	shift = where & (4 - size);
	KS8695_WRITE(KS8695_2100, CONFIG_CMD(bus, devfn, where));
	reg = KS8695_READ(KS8695_2104);
	spin_unlock_irqrestore(&ks8695p_lock, flags);

	*val = (reg >> (shift * 8));

	return PCIBIOS_SUCCESSFUL;
}

static int ks8695p_write_config(struct pci_bus *bus, unsigned int devfn,
	int where, int size, u32 val)
{
	u32 reg, shift;
	unsigned long flags;

	spin_lock_irqsave(&ks8695p_lock, flags);

	shift = where & (4 - size);
	KS8695_WRITE(KS8695_2100, CONFIG_CMD(bus, devfn, where));
	reg = KS8695_READ(KS8695_2104);

	if (size == 1) {
		switch (shift) {
		case 3:
			reg &= 0x00ffffff;
			reg |= val << 24;
			break;

		case 2:
			reg &= 0xff00ffff;
			reg |= val << 16;
			break;

		case 1:
			reg &= 0xffff00ff;
			reg |= val << 8;
			break;

		default:
			reg &= 0xffffff00;
			reg |= val;
			break;
		}
	} else if (size == 2) {
		switch (shift) {
		case 2:
			reg &= 0x0000ffff;
			reg |= val << 16;
			break;
		default:
			reg &= 0xffff0000;
			reg |= val;
			break;
		}
	} else
		reg = val;

	KS8695_WRITE(KS8695_2100, CONFIG_CMD(bus, devfn, where));
	KS8695_WRITE(KS8695_2104, reg);
	spin_unlock_irqrestore(&ks8695p_lock, flags);

	return PCIBIOS_SUCCESSFUL;
}

static struct pci_ops ks8695p_ops = {
	.read = ks8695p_read_config,
	.write = ks8695p_write_config,
};

static struct resource pci_mem = {
	.name  = "PCI memory space",
	.start = KS8695P_PCI_MEM_BASE,
	.end   = (KS8695P_PCI_MEM_BASE - 1 + KS8695P_PCI_MEM_SIZE),
	.flags = IORESOURCE_MEM,
};

static struct resource pci_io = {
	.name  = "PCI IO space",
	.start = KS8695P_PCI_IO_BASE,
	.end   = KS8695P_PCI_IO_BASE + KS8695P_PCI_IO_SIZE - 1,
	.flags = IORESOURCE_IO,
};

struct pci_bus __init *ks8695p_pci_scan_bus(int nr, struct pci_sys_data *sys)
{
	return pci_scan_root_bus(NULL, sys->busnr, &ks8695p_ops, sys,
		&sys->resources);
}

static int __init ks8695p_setup_resources(struct list_head *resource)
{
	request_resource(&iomem_resource, &pci_mem);
	request_resource(&ioport_resource, &pci_io);

	pci_add_resource(resource, &pci_io);
	pci_add_resource(resource, &pci_mem);
	return 1;
}

int __init ks8695p_pci_setup(int nr, struct pci_sys_data *sys)
{
	int ret = 0;

	if (nr == 0) {
		sys->io_offset = KS8695P_PCI_IO_BASE;
		sys->mem_offset = KS8695P_PCI_MEM_BASE;
		ret = ks8695p_setup_resources(&sys->resources);
	}
	return ret;
}

void __init ks8695p_configure_interrupt(void)
{
	u32 uReg;

	uReg = KS8695_READ(KS8695_GPIO_MODE);

/* KS8695P-based chips */
#ifdef CONFIG_KS8695P
	/* set it to output first, KS8695P has 4 gpio pins for interrupt,
	 * device driver will set them accordingly
	 */
	uReg |= 0x0000000f;
#else
	/* set it to output first, KS8695/X has 3 gpio pins for interrupt */
	uReg |= 0x00000007;
#endif
	KS8695_WRITE(KS8695_GPIO_MODE, uReg);
}

void __init ks8695p_pci_brge_init(void)
{
	unsigned long flags;

	pcibios_min_io = 0;
	pcibios_min_mem = 0;

	/* note that we need a stage 1 initialization in .S file to set 0x202c,
	 * before the stage 2 initialization here
	 */
	spin_lock_irqsave(&ks8695p_lock, flags);

	/* stage 1 initialization, subid, subdevice = 0x0001 */
	KS8695_WRITE(KS8695_202C, 0x00010001);

	/* stage 2 initialization */
	/* prefetch limits with 16 words, retru enable */
	KS8695_WRITE(KS8695_2204, 0x40000000);

	/* configure memory mapping */
	KS8695_WRITE(KS8695_2208, KS8695P_PCIBG_MEM_BASE);
	/* enable memory address translation */
	KS8695_WRITE(KS8695_220C, PMBAC_TRANS_ENABLE);
	/* mask bits */
	KS8695_WRITE(KS8695_2210, KS8695P_PCI_MEM_MASK);
	/* physical memory address */
	KS8695_WRITE(KS8695_2214, 0);

	/* configure IO mapping */
	KS8695_WRITE(KS8695_2218, KS8695P_PCIBG_IO_BASE);
	/* enable IO address translation */
	KS8695_WRITE(KS8695_221C, PMBAC_TRANS_ENABLE);
	/* mask bits */
	KS8695_WRITE(KS8695_2220, KS8695P_PCI_IO_MASK);
	KS8695_WRITE(KS8695_2224, 0);

	ks8695p_configure_interrupt();
	spin_unlock_irqrestore(&ks8695p_lock, flags);
}


#define PCI_AHB_BRIDGE_VENDOR_ID  0x16C6
#define PCI_AHB_BRIDGE_DEVICE_ID  0x8695

void __init ks8695p_pci_postinit(void)
{
	struct pci_dev *dev = NULL;
	u16 cmd;

	/* Assume host bridge is not initialized by the bootloader. */
	dev = pci_get_device(PCI_AHB_BRIDGE_VENDOR_ID,
		PCI_AHB_BRIDGE_DEVICE_ID, dev);
	if (dev) {
		pci_write_config_dword(dev, PCI_BASE_ADDRESS_0,
			KS8695P_PCIBG_MEM_BASE);

		pci_read_config_word(dev, PCI_COMMAND, &cmd);
		cmd &= ~PCI_COMMAND_IO;
		cmd |= PCI_COMMAND_MASTER | PCI_COMMAND_MEMORY;
		pci_write_config_word(dev, PCI_COMMAND, cmd);
	}
	dev = pci_get_device(PCI_VENDOR_ID_ATHEROS, PCI_ANY_ID, dev);
	if (dev)
		pci_mem.start += 0x10000;
}


/*
 *  2 -->|---|  3 --->|---|  4 --->|---|
 *       |   |        |   |        |   |
 *  3 -->|   |  4 --->|   |  2 --->|   |
 *       |   |        |   |        |   |
 *  4 -->|   |  2 --->|   |  3 --->|   |
 *       |   |        |   |        |   |
 *  5 -->|   |  5 --->|   |  5 --->|   |
 *       |___|        |___|        |___|
 */

static int __init ks8695p_pci_map_irq(const struct pci_dev *dev, u8 slot,
	u8 pin)
{
#ifdef CONFIG_KS8695M
	int rel;

	if (slot == 0)
		return 0;
	if (pin == 4)
		return 5;

	rel = slot + pin;
	if (rel > 8)
		return rel - 7;
	else
		return rel - 4;
#else
	if (slot == 0)
		return 0;
	return 2;
#endif
}

static u8 __init ks8695p_pci_swizzle(struct pci_dev *dev, u8 *pinp)
{
	int pin = *pinp - 1;

	while (dev->bus->self) {
		pin = (pin + PCI_SLOT(dev->devfn)) & 3;
		/*
		 * move up the chain of bridges,
		 * swizzling as we go.
		 */
		dev = dev->bus->self;
	}
	*pinp = pin + 1;

	/* hardcoded only for USB card to have its own irq */
	if (*pinp == 2)
		*pinp = 4;

	return PCI_SLOT(dev->devfn);
}

static struct hw_pci ks8695p_pci __initdata = {
	.swizzle	= ks8695p_pci_swizzle,
	.map_irq	= ks8695p_pci_map_irq,
	.setup		= ks8695p_pci_setup,
	.nr_controllers	= 1,
	.scan		= ks8695p_pci_scan_bus,
	.preinit	= ks8695p_pci_brge_init,
	.postinit	= ks8695p_pci_postinit,
};

static int __init ks8695p_pci_init(void)
{
	pci_common_init(&ks8695p_pci);
	return 0;
}

subsys_initcall(ks8695p_pci_init);
