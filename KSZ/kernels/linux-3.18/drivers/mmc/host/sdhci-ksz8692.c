/*  drivers/mmc/host/sdhci-ksz8692.c - SDHCI on Micrel Pegasus SoC
 *
 *  Copyright (C) 2009-2010 Micrel, Inc.
 *  Copyright (C) 2005-2008 Pierre Ossman, All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * Thanks to the following companies for their support:
 *
 *     - JMicron (hardware and technical support)
 */

#include <linux/delay.h>
#include <linux/highmem.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/dma-mapping.h>

#include <linux/mmc/host.h>

#include <linux/scatterlist.h>
#include <linux/io.h>

#include "sdhci.h"

#define DRIVER_NAME "pegasus-sdhci"


/*****************************************************************************\
 *                                                                           *
 * SDHCI core callbacks                                                      *
 *                                                                           *
\*****************************************************************************/

static int sdhci_pci_enable_dma(struct sdhci_host *host)
{
	return 0;
}

static struct sdhci_ops sdhci_pci_ops = {
	.set_clock	= sdhci_set_clock,
	.enable_dma	= sdhci_pci_enable_dma,
	.set_bus_width	= sdhci_set_bus_width,
	.reset		= sdhci_reset,
	.set_uhs_signaling = sdhci_set_uhs_signaling,
};

/*****************************************************************************\
 *                                                                           *
 * Suspend/resume                                                            *
 *                                                                           *
\*****************************************************************************/

#ifdef CONFIG_PM

static int sdhci_suspend(struct platform_device *pdev, pm_message_t state)
{
	struct mmc_host *mmc = platform_get_drvdata(pdev);
	struct sdhci_host *host;

	DBG("Suspending...\n");

	if (mmc == NULL)
		return 0;

	host = mmc_priv(mmc);
	return sdhci_suspend_host(host, state);
}

static int sdhci_resume(struct platform_device *pdev)
{
	struct mmc_host *mmc = platform_get_drvdata(dev);
	struct sdhci_host *host;

	DBG("Resuming...\n");

	if (mmc == NULL)
		return 0;

	host = mmc_priv(mmc);
	return sdhci_resume_host(host);
}

#else /* CONFIG_PM */

#define sdhci_suspend NULL
#define sdhci_resume NULL

#endif /* CONFIG_PM */

/*****************************************************************************\
 *                                                                           *
 * Device probing/removal                                                    *
 *                                                                           *
\*****************************************************************************/

/*
 * Check all resources for the host.
 */
static struct resource *platform_device_resource(struct platform_device *pdev,
	unsigned int mask, int nr)
{
	int i;

	for (i = 0; i < pdev->num_resources; i++)
		if (pdev->resource[i].flags == mask && nr-- == 0)
			return &pdev->resource[i];
	return NULL;
}

/*
 * Check IRQ.
 */
static int platform_device_irq(struct platform_device *pdev, int nr)
{
	int i;

	for (i = 0; i < pdev->num_resources; i++)
		if (pdev->resource[i].flags == IORESOURCE_IRQ && nr-- == 0)
			return pdev->resource[i].start;
	return NO_IRQ;
}

static int sdhci_probe(struct platform_device *pdev)
{
	int ret = 0, irq;
	struct sdhci_host *host = NULL;
	struct resource *r = NULL;

	r = platform_device_resource(pdev, IORESOURCE_MEM, 0);
	irq = platform_device_irq(pdev, 0);
	if (!r || irq == NO_IRQ) {
		printk(KERN_ERR DRIVER_NAME
			": Invalid iomem size. Aborting.\n");
		return -ENXIO;
	}

	r = request_mem_region(r->start, (r->end - r->start + 1), DRIVER_NAME);
	if (!r) {
		printk(KERN_ERR DRIVER_NAME ": request_mem_region failed.\n");
		return -EBUSY;
	}

	host = sdhci_alloc_host(&pdev->dev, 0);
	if (IS_ERR(host)) {
		ret = PTR_ERR(host);
		goto unmap;
	}

	host->hw_name = "Pegasus";
	host->ops = &sdhci_pci_ops;
	host->irq = irq;

	/* SD host controller virtual address */
	host->ioaddr = (void *) VIO(SDIO_HOST_BASE);

	ret = sdhci_add_host(host);
	if (ret)
		goto remove;

	platform_set_drvdata(pdev, host->mmc);

	return 0;

remove:
unmap:
	sdhci_free_host(host);

	return ret;
}

static int sdhci_remove(struct platform_device *pdev)
{
	struct mmc_host *mmc = platform_get_drvdata(pdev);
	struct sdhci_host *host;
	struct resource *r;
	int dead;
	u32 scratch;

	if (!mmc)
		return -ENODEV;

	host = mmc_priv(mmc);

	dead = 0;
	scratch = readl(host->ioaddr + SDHCI_INT_STATUS);
	if (scratch == (u32)-1)
		dead = 1;

	sdhci_remove_host(host, dead);

	r = platform_device_resource(pdev, IORESOURCE_MEM, 0);
	if (r)
		release_mem_region(r->start, (r->end - r->start + 1));

	sdhci_free_host(host);

	platform_set_drvdata(pdev, NULL);
	return 0;
}

static struct platform_driver sdhci_driver = {
	.probe   =  sdhci_probe,
	.remove  =  sdhci_remove,
	.suspend =  sdhci_suspend,
	.resume	 =  sdhci_resume,
	.driver  = {
/*
   [name] field here MUST matches with that of ks8692_device_ehci in
   arch/mach-ksz8692/devs.c. Otherwise this device will never
   be served.
*/
		.name   = DRIVER_NAME,
		.owner  = THIS_MODULE,
	},
};

module_platform_driver(sdhci_driver);

MODULE_AUTHOR("Micrel, Inc. <www.micrel.com>");
MODULE_DESCRIPTION("Micrel Pegasus Secure Digital Host Controller Interface driver");
MODULE_LICENSE("GPL");
