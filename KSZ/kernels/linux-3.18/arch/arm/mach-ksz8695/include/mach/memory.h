/*
 *  arch/arm/mach-ksz8695/include/mach/memory.h
 *
 *  Copyright (C) 2002-2011 Micrel, Inc.
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
#ifndef __ASM_ARCH_MEMORY_H
#define __ASM_ARCH_MEMORY_H

#define BUS_OFFSET		UL(0x10000000)

#ifndef __ASSEMBLY__
/*
 * Virtual view <-> DMA view memory address translations
 * virt_to_bus: Used to translate the virtual address to an
 *              address suitable to be passed to set_dma_addr
 * bus_to_virt: Used to convert an address for DMA operations
 *              to an address that the kernel can use.
 */
#ifdef CONFIG_PCI
#define __virt_to_bus(x)   ((x) - PAGE_OFFSET + BUS_OFFSET)
#define __bus_to_virt(x)   ((x) - BUS_OFFSET + PAGE_OFFSET)

#define __virt_to_local(x)  ((x) - PAGE_OFFSET)
#define __local_to_virt(x)  ((x) + PAGE_OFFSET)

extern struct bus_type pci_bus_type;

#define is_pci_device(dev)		\
	(dev && dev->bus == &pci_bus_type)

#define __arch_pfn_to_dma(dev, pfn)				\
	({ dma_addr_t __dma = __pfn_to_phys(pfn);		\
	   if (is_pci_device(dev))				\
		__dma = __dma - PHYS_OFFSET + BUS_OFFSET;	\
	   __dma; })

#define __arch_dma_to_pfn(dev, addr)				\
	({ dma_addr_t __dma = addr;				\
	   if (is_pci_device(dev))				\
		__dma = __dma + PHYS_OFFSET - BUS_OFFSET;	\
	   __phys_to_pfn(__dma);				\
	})

#define __arch_dma_to_virt(dev, addr)	\
	({is_pci_device(dev) ?		\
	(void *)__bus_to_virt(addr) :	\
	(void *)__local_to_virt(addr); })

#define __arch_virt_to_dma(dev, addr)	\
	({is_pci_device(dev) ?		\
	__virt_to_bus((unsigned long)(addr)) :	\
	__virt_to_local((unsigned long)(addr)); })
#endif
#endif

#endif
