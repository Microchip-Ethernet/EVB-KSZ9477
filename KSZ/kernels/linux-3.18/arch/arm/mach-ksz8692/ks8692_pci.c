/*
	Copyright (c) 2006-2012, Micrel, Inc.

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

	This driver is for Micrel's KSZ8692 SoC Chipset as PCI bridge driver.

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

#include <linux/io.h>
#include <asm/mach/pci.h>


/* Since there is no extra PCI bridge in KSZ8692 reference board, we only need
 * to support type 0 configuration space access, but not type 1.
 *
 * Also use:
 *	IDSEL 16 for slot 1,
 *	IDSEL 17 for slot 2,
 *	IDSEL 18 for bridge if it is configured as a guest device.
 */
#define CONFIG_CMD(but, devfn, where)	\
	(0x80000000 | (bus->number << 16) | (devfn << 8) | \
	(where & 0xfffffffc))

static DEFINE_SPINLOCK(ks8692_lock);


static int ks8692_read_config(struct pci_bus *bus, unsigned int devfn,
	int where, int size, u32 *val)
{
	u32 reg, shift;
	unsigned long flags;

	spin_lock_irqsave(&ks8692_lock, flags);
	shift = where & (4 - size);
	KS8692_WRITE_REG(KS8692_PBCA, CONFIG_CMD(bus, devfn, where));
	reg = KS8692_READ_REG(KS8692_PBCD);
	spin_unlock_irqrestore(&ks8692_lock, flags);

	*val = (reg >> (shift*8));

	return PCIBIOS_SUCCESSFUL;
}

static int ks8692_write_config(struct pci_bus *bus, unsigned int devfn,
	int where, int size, u32 val)
{
	u32 reg, shift;
	unsigned long flags;

	spin_lock_irqsave(&ks8692_lock, flags);

	shift = where & (4 - size);
	KS8692_WRITE_REG(KS8692_PBCA, CONFIG_CMD(bus, devfn, where));
	reg = KS8692_READ_REG(KS8692_PBCD);

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

	KS8692_WRITE_REG(KS8692_PBCA, CONFIG_CMD(bus, devfn, where));
	KS8692_WRITE_REG(KS8692_PBCD, reg);
	spin_unlock_irqrestore(&ks8692_lock, flags);

	return PCIBIOS_SUCCESSFUL;
}

static struct pci_ops ks8692_ops = {
	.read = ks8692_read_config,
	.write = ks8692_write_config,
};

static struct resource pci_mem = {
	.name  = "PCI memory space",
	.start = KS8692_PCI_MEM_BASE,
	.end   = (KS8692_PCI_MEM_BASE - 1 + KS8692_PCI_MEM_SIZE),
	.flags = IORESOURCE_MEM,
};

static struct resource pci_io = {
	.name  = "PCI IO space",
	.start = KS8692_PCI_IO_BASE,
	.end   = KS8692_PCI_IO_BASE + KS8692_PCI_IO_SIZE - 1,
	.flags = IORESOURCE_IO,
};

struct pci_bus __init *ks8692_pci_scan_bus(int nr, struct pci_sys_data *sys)
{
	return pci_scan_root_bus(NULL, sys->busnr, &ks8692_ops, sys,
		&sys->resources);
}

static int __init ks8692_setup_resources(struct list_head *resource)
{
	request_resource(&iomem_resource, &pci_mem);
	request_resource(&ioport_resource, &pci_io);

	pci_add_resource(resource, &pci_io);
	pci_add_resource(resource, &pci_mem);
	return 1;
}

int __init ks8692_pci_setup(int nr, struct pci_sys_data *sys)
{
	int ret = 0;

	if (nr == 0) {
		sys->io_offset = PCIBG_IO_BASE;
		sys->mem_offset = PCIBG_MEM_BASE;
		ret = ks8692_setup_resources(&sys->resources);
	}
	return ret;
}

void __init ks8692_configure_interrupt(void)
{
	u32 uReg;

	uReg = KS8692_READ_REG(KS8692_GPIO_MODE);

	/* set it to output first, KS8692 has 4 gpio pins for interrupt, device
	 * driver will set them accordingly
	 */
	uReg |= 0x0000000f;
	KS8692_WRITE_REG(KS8692_GPIO_MODE, uReg);
}

void __init ks8692_pci_brge_init(void)
{
	unsigned long flags;

	pcibios_min_io = 0;
	pcibios_min_mem = 0;

	/* note that we need a stage 1 initialization in .S file to set 0x202c,
	 * before the stage 2 initialization here
	 */
	spin_lock_irqsave(&ks8692_lock, flags);

	/* stage 1 initialization, subid, subdevice = 0x0001 */
	KS8692_WRITE_REG(KS8692_CRCSID, 0x00010001);

	/* stage 2 initialization */
	/* prefetch limits with 16 words, retru enable */
	KS8692_WRITE_REG(KS8692_PBCS, PCI_PREFETCH_WORDS16);

	/* configure memory mapping */
	KS8692_WRITE_REG(KS8692_PMBA, PCIBG_MEM_BASE);
	/* enable memory address translation */
	KS8692_WRITE_REG(KS8692_PMBAC, PCI_TRANS_ENABLE);
	/* mask bits */
	KS8692_WRITE_REG(KS8692_PMBAM, PMBAM_MEM_MASK);
	/* physical memory address */
	KS8692_WRITE_REG(KS8692_PMBAT, 0);

	/* configure IO mapping */
	KS8692_WRITE_REG(KS8692_PIOBA, PCIBG_IO_BASE);
	/* enable IO address translation */
	KS8692_WRITE_REG(KS8692_PIOBAC, PCI_TRANS_ENABLE);
	/* mask bits */
	KS8692_WRITE_REG(KS8692_PIOBAM, PIOBAM_IO_MASK);

/* THa  2009/04/14
   Not doing anything and jump directly to the ks8692_configure_interrupt
   routine will somehow affect the PCI interrupt not working well.  Weird!
*/
	wmb();
	KS8692_WRITE_REG(KS8692_PIOBAT, 0);

	ks8692_configure_interrupt();
	spin_unlock_irqrestore(&ks8692_lock, flags);
}


#define PCI_AHB_BRIDGE_VENDOR_ID  0x16C6
#define PCI_AHB_BRIDGE_DEVICE_ID  0x8692

void __init ks8692_pci_postinit(void)
{
	struct pci_dev *dev = NULL;
	u16 cmd;

	/* Assume host bridge is not initialized by the bootloader. */
	dev = pci_get_device(PCI_AHB_BRIDGE_VENDOR_ID,
		PCI_AHB_BRIDGE_DEVICE_ID, dev);
	if (dev) {
		pci_write_config_dword(dev, PCI_BASE_ADDRESS_0, PCIBG_MEM_BASE);

		pci_read_config_word(dev, PCI_COMMAND, &cmd);
		cmd &= ~PCI_COMMAND_IO;
		cmd |= PCI_COMMAND_MASTER | PCI_COMMAND_MEMORY;
		pci_write_config_word(dev, PCI_COMMAND, cmd);
	}
	dev = pci_get_device(PCI_VENDOR_ID_ATHEROS, PCI_ANY_ID, dev);
	if (dev)
		pci_mem.start += 0x10000;
}

