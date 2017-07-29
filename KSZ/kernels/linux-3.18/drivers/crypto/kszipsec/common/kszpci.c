/*-----------------------------------------------------------------------
//
// Proprietary Information of Elliptic Semiconductor
// Copyright (C) 2002-2005, all rights reserved
// Elliptic Semiconductor, Inc.
//
// As part of our confidentiality  agreement, Elliptic Semiconductor and
// the Company, as  a  Receiving Party, of  this  information  agrees to
// keep strictly  confidential  all Proprietary Information  so received
// from Elliptic Semiconductor. Such Proprietary Information can be used
// solely for  the  purpose  of evaluating  and/or conducting a proposed
// business  relationship  or  transaction  between  the  parties.  Each
// Party  agrees  that  any  and  all  Proprietary  Information  is  and
// shall remain confidential and the property of Elliptic Semiconductor.
// The  Company  may  not  use  any of  the  Proprietary  Information of
// Elliptic Semiconductor for any purpose other  than  the  above-stated
// purpose  without the prior written consent of Elliptic Semiconductor.
//
//-----------------------------------------------------------------------
//
// Project:
//
//   ELPIPSEC
//
// Description:
//
// Accessing a PCI memory region using mmap() on /dev/mem
//	Make sure (with lspci -vvs x:y.z) that "Region 0" is memory and that
//	"Region 1" is I/O.
//
//
//-----------------------------------------------------------------------
//
// Copyright (C) 2006-2007, Micrel, Inc.
//
//-----------------------------------------------------------------------*/

#include "elpipsec.h"

char busversion[] = "Elliptic Semiconductor (C). ELPIPSEC PCI Library V"VERSION" ["__DATE__" "__TIME__"]";

int elpsec_pci_init(elp_id *tid, elphw_if *tif,unsigned long flags)
{
#ifdef ELPSEC_PCI
	EMEMSET(tif,0,sizeof(elphw_if));

	tif->pmem = 0;
	tif->preg = 0;

	tif->bar0_size = ELPSEC_PCI_MEMORY_SIZE;
	tif->bar1_size = ELPSEC_PCI_MEMORY_SIZE;
	tif->bar2_size = ELPSEC_PCI_MEMORY_SIZE;
	tif->bar3_size = ELPSEC_PCI_MEMORY_SIZE;
	tif->bar4_size = ELPSEC_PCI_MEMORY_SIZE;

	// Check IO permissions to be able to open /dev/mem
	if(iopl(3))
	{
		fprintf(stderr,"Cannot get I/O PL  permissions.\n");
		return ESPAH_FAILED;
	}

	tif->pci_all_dev = pci_alloc(); /* Allocate memory for all_devices */

	if (!tif->pci_all_dev)
		return ESPAH_FAILED;

	pci_init(tif->pci_all_dev);     /* Initialisation of all_devices   */

	// Scan the PCI bus, and find the elp toe device
	pci_scan_bus(tif->pci_all_dev); /* Scan the PCI bus(es)         */

	for (tif->toe_dev = tif->pci_all_dev->devices; tif->toe_dev; tif->toe_dev =tif->toe_dev->next)
	{
		pci_fill_info(tif->toe_dev,PCI_FILL_IDENT | PCI_FILL_BASES);
		if (tif->toe_dev->vendor_id == tid->vendor_id && tif->toe_dev->device_id == tid->device_id)
			break;
	}

	if (!tif->toe_dev)
	{
		pci_cleanup(tif->pci_all_dev);
		return ESPAH_FAILED;
	}

	// We now open the memory...
	tif->toe_fd = open ( "/dev/mem", O_RDWR);

	if (tif->toe_fd < 0)
	{
		pci_cleanup(tif->pci_all_dev);
		return ESPAH_FAILED;
	}

	if (flags&ELP_PCI_MAP_BAR_1)
	{
		// BAR1 registers access
		tif->bar1 = pci_read_long( tif->toe_dev, 0x14) & PCI_BASE_ADDRESS_MEM_MASK;

		// map the PCI registry area (man 2 mmap for more info)
		tif->preg = (char *) mmap(NULL,ELPSEC_PCI_MEMORY_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, tif->toe_fd, (off_t)tif->bar1);
		if (tif->preg == MAP_FAILED)
		{
			printf("elpsec_pci_init: reg:%ld , fd:%x, msz:%d \n",tif->bar1,tif->toe_fd,ELPSEC_PCI_MEMORY_SIZE);
			perror("nmap: registers");
			return ESPAH_FAILED;
		}
	}

	if (flags&ELP_PCI_MAP_BAR_0)
	{
		// BAR0 memory access
		tif->bar0 = pci_read_long( tif->toe_dev, 0x10) & PCI_BASE_ADDRESS_MEM_MASK;

		// map the PCI memory area (man 2 mmap for more info)
		tif->pmem = (char *) mmap(NULL,ELPSEC_PCI_MEMORY_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, tif->toe_fd, (off_t)tif->bar0);
		if (tif->pmem == MAP_FAILED)
		{
			printf("elpsec_pci_init: mem:%ld , fd:%x, msz:%d \n",tif->bar0,tif->toe_fd,ELPSEC_PCI_MEMORY_SIZE);
			perror("nmap: registers");
			return ESPAH_FAILED;
		}
	}
	return ESPAH_OK;
#else
	return ESPAH_NOT_IMPLEMENTED;
#endif
}

void elpsec_pci_cleanup(elphw_if *tif)
{
#ifdef ELPSEC_PCI
	if (tif->pmem)
		munmap((void *)tif->pmem, ELPSEC_PCI_MEMORY_SIZE);
	if (tif->preg)
		munmap((void *)tif->preg, ELPSEC_PCI_MEMORY_SIZE);

	if (tif->toe_fd>0)
		close(tif->toe_fd);
	if (tif->pci_all_dev)
		pci_cleanup(tif->pci_all_dev);
#endif
}

void elpsec_pci_reset(elphw_if *tif)
{
#ifdef ELPSEC_PCI
	U32 conf = 0;
	pci_write_long( tif->toe_dev, 0x40,1);
	conf = pci_read_long( tif->toe_dev, 0x40);
	pci_write_long( tif->toe_dev, 0x40,0);
	//printf("Resetting ELP Board [0x%x] ...\n", conf);
#endif
}


void elpsec_info (elphw_if *tif)
{
#ifdef ELPSEC_PCI
	printf("\n%s\n",busversion);
	fprintf(stderr,"ELPSEC device has been found on %d:%d.%d\n",
		tif->toe_dev->bus,tif->toe_dev->dev,tif->toe_dev->func);
	fprintf(stderr,"ELPSEC registers @ 0x%lX [%d] mapped @%p\n",
		tif->bar1,ELPSEC_PCI_MEMORY_SIZE,tif->preg);
#endif
}
