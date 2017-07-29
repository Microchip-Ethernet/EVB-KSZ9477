/*
 *  linux/arch/arm/mach-ks8692/pci.c
 *
 *  PCI bios-type initialisation for PCI machines
 *
 *  Bits taken from various places.
 */
#include <linux/kernel.h>
#include <linux/pci.h>
#include <linux/init.h>
#include <linux/version.h>

#include <asm/irq.h>
#include <asm/mach/pci.h>
#include <mach/hardware.h>

struct pci_bus __init *ks8692_pci_scan_bus(int nr, struct pci_sys_data *sys);
int __init ks8692_pci_setup(int nr, struct pci_sys_data *sys);
void __init ks8692_pci_brge_init(void);
void __init ks8692_pci_postinit(void);

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

static int __init ks8692_pci_map_irq(const struct pci_dev *dev, u8 slot, u8 pin)
{
	int rel;

	if (slot == 0)
		return 0;

#ifdef USE_EXT3_INT
	if (pin == 4)
		return 5 + LOW_IRQS;
#endif

	rel = slot + pin;
	if (rel > 8)
		return rel - 7 + LOW_IRQS;
	else
		return rel - 4 + LOW_IRQS;
}

static u8 __init ks8692_pci_swizzle(struct pci_dev *dev, u8 *pinp)
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

#ifdef USE_EXT3_INT
	/* hardcoded only for USB card to have its own irq */
	if (*pinp == 2)
		*pinp = 4;
#endif

	return PCI_SLOT(dev->devfn);
}

static struct hw_pci ks8692_pci __initdata = {
	.swizzle	= ks8692_pci_swizzle,
	.map_irq	= ks8692_pci_map_irq,
	.setup		= ks8692_pci_setup,
	.nr_controllers	= 1,
	.scan		= ks8692_pci_scan_bus,
	.preinit	= ks8692_pci_brge_init,
	.postinit	= ks8692_pci_postinit,
};

static int __init ks8692_pci_init(void)
{
	pci_common_init(&ks8692_pci);
	return 0;
}

subsys_initcall(ks8692_pci_init);
