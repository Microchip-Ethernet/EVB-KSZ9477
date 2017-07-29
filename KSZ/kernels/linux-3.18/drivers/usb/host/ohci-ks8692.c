/*
 * OHCI HCD (Host Controller Driver) for USB.
 *
 * (C) Copyright 1999 Roman Weissgaerber <weissg@vienna.at>
 * (C) Copyright 2000-2002 David Brownell <dbrownell@users.sourceforge.net>
 * (C) Copyright 2002 Hewlett-Packard Company
 *
 * Bus Glue for Micrel Pegasus KSZ8692 OHCI
 *
 * Written by Christopher Hoover <ch@hpl.hp.com>
 * Based on fragments of previous driver by Rusell King et al.
 *
 * Modified for LH7A404 from ohci-sa1111.c
 *  by Durgesh Pattamatta <pattamattad@sharpsec.com>
 * Modified for Micrel Pegasus KSZ8692 OHCI
 *  by David Choi <david.choi@micrel.com>
 *
 * This file is licenced under the GPL.
 */

#include <linux/platform_device.h>
#include <linux/signal.h>

#include "ks8692.h"

/*-------------------------------------------------------------------------*/
static void ks8692_start_ohc(struct usb_hcd *hcd)
{
	u32 uReg;

#define	ks8692_write	au_writel
#define	ks8692_read	au_readl

	/* feature enable: reset to zero is to enable a feature */
	uReg = au_readl(KS8692_FEATURE_INTER_CFG);
	/* bit0:USB host */
	au_writel(KS8692_FEATURE_INTER_CFG, uReg & ~0x01);

	/* Interrupt mode */
	uReg = ks8692_read(KS8692_INT_CONTL1);
	ks8692_write(KS8692_INT_CONTL1, uReg & ~INT_USB_HOST_OHCI);

	/* Interrupt enable */
	uReg = ks8692_read(KS8692_INT_ENABLE1);
	ks8692_write(KS8692_INT_ENABLE1, uReg | INT_USB_HOST_OHCI);
	/* to verify */
	uReg = ks8692_read(KS8692_INT_ENABLE1);

	/* Interrupt status */
	uReg = ks8692_read(KS8692_INT_STATUS1);
	/* Clear INT */
	ks8692_write(KS8692_INT_STATUS1, uReg & ~INT_USB_HOST_OHCI);

	/* Interrupt priority */
	uReg = ks8692_read(KS8692_INT_USB_PRIORITY);
	/* lowest priority */
	ks8692_write(KS8692_INT_USB_PRIORITY, uReg & ~0xfff);
}

static void ks8692_stop_ohc(struct platform_device *dev)
{

}


/*-------------------------------------------------------------------------*/

/* configure so an HC device and id are always provided */
/* always called with process context; sleeping is OK */


/**
 * usb_ohci_ks8692_probe - initialize KS8692-based HCDs
 * Context: !in_interrupt()
 *
 * Allocates basic resources for this USB host controller, and
 * then invokes the start() method for the HCD associated with it
 * through the hotplug entry's driver_data.
 *
 */
static int usb_ohci_ks8692_probe(const struct hc_driver *driver,
			  struct platform_device *dev)
{
	struct usb_hcd *hcd = NULL;
	int retval;

	if (dev->resource[1].flags != IORESOURCE_IRQ) {
		pr_debug("resource[1] is not IORESOURCE_IRQ\n");
		return -ENOMEM;
	}

	hcd = usb_create_hcd(driver, &dev->dev, "ks8692");
	if (!hcd)
		return -ENOMEM;
	hcd->rsrc_start = dev->resource[0].start;
	hcd->rsrc_len = dev->resource[0].end - dev->resource[0].start + 1;

	if (!request_mem_region(hcd->rsrc_start, hcd->rsrc_len, hcd_name)) {
		pr_debug("request_mem_region failed\n");
		retval = -EBUSY;
		goto err1;
	}

	hcd->regs = ioremap(hcd->rsrc_start, hcd->rsrc_len);
	if (!hcd->regs) {
		pr_debug("ioremap failed\n");
		retval = -ENOMEM;
		goto err2;
	}

	ohci_hcd_init(hcd_to_ohci(hcd));
	retval = usb_add_hcd(hcd, dev->resource[1].start, IRQF_DISABLED);
	if (retval == 0) {
		ks8692_start_ohc(hcd);
		return retval;
	}
	ks8692_stop_ohc(dev);
	iounmap(hcd->regs);
 err2:
	release_mem_region(hcd->rsrc_start, hcd->rsrc_len);
 err1:
	usb_put_hcd(hcd);
	return retval;
}


/* may be called without controller electrically present */
/* may be called with controller, bus, and devices active */

/**
 * usb_hcd_ks8692_remove - shutdown processing for KS8692-based HCDs
 * @dev: USB Host Controller being removed
 * Context: !in_interrupt()
 *
 * Reverses the effect of usb_hcd_ks8692_probe(), first invoking
 * the HCD's stop() method.  It is always called from a thread
 * context, normally "rmmod", "apmd", or something similar.
 *
 */
static void usb_ohci_ks8692_remove(struct usb_hcd *hcd,
	struct platform_device *dev)
{
	usb_remove_hcd(hcd);
	ks8692_stop_ohc(dev);
	iounmap(hcd->regs);
	release_mem_region(hcd->rsrc_start, hcd->rsrc_len);
	usb_put_hcd(hcd);
}

/*-------------------------------------------------------------------------*/

static int
ohci_ks8692_start(struct usb_hcd *hcd)
{
	struct ohci_hcd	*ohci = hcd_to_ohci(hcd);
	int		ret;

	ret = ohci_init(ohci);
	if (ret < 0)
		return ret;

	ret = ohci_run(ohci);
	if (ret < 0) {
		ohci_stop(hcd);
		return ret;
	}

	return 0;
}

/*-------------------------------------------------------------------------*/

static const struct hc_driver ohci_ks8692_hc_driver = {
	.description =		hcd_name,
	.product_desc =		KS8692_SOC_OHCI_NAME,
	.hcd_priv_size =	sizeof(struct ohci_hcd),

	/*
	 * generic hardware linkage
	 */
	.irq =			ohci_irq,
	.flags =		HCD_USB11 | HCD_MEMORY,

	/*
	 * basic lifecycle operations
	 */
	.start =		ohci_ks8692_start,
#ifdef	CONFIG_PM
	/* suspend:		ohci_ks8692_suspend,  -- tbd */
	/* resume:		ohci_ks8692_resume,   -- tbd */
#endif /*CONFIG_PM*/
	.stop =			ohci_stop,
	.shutdown = ohci_shutdown,

	/*
	 * managing i/o requests and associated device resources
	 */
	.urb_enqueue =		ohci_urb_enqueue,
	.urb_dequeue =		ohci_urb_dequeue,
	.endpoint_disable =	ohci_endpoint_disable,

	/*
	 * scheduling support
	 */
	.get_frame_number =	ohci_get_frame,

	/*
	 * root hub support
	 */
	.hub_status_data =	ohci_hub_status_data,
	.hub_control =		ohci_hub_control,
#ifdef	CONFIG_PM
	.bus_suspend =		ohci_bus_suspend,
	.bus_resume =		ohci_bus_resume,
#endif
	.start_port_reset =	ohci_start_port_reset,
};

/*-------------------------------------------------------------------------*/

static int ohci_hcd_ks8692_drv_probe(struct platform_device *pdev)
{
	int ret;

	pr_debug("In ohci_hcd_ks8692_drv_probe");

	if (usb_disabled())
		return -ENODEV;

	ret = usb_ohci_ks8692_probe(&ohci_ks8692_hc_driver, pdev);
	return ret;
}

static int ohci_hcd_ks8692_drv_remove(struct platform_device *pdev)
{
	struct usb_hcd *hcd = platform_get_drvdata(pdev);

	usb_ohci_ks8692_remove(hcd, pdev);
	return 0;
}
	/*TBD*/
/*static int ohci_hcd_ks8692_drv_suspend(struct platform_device *dev)
{
	struct usb_hcd *hcd = platform_get_drvdata(dev);

	return 0;
}
static int ohci_hcd_ks8692_drv_resume(struct platform_device *dev)
{
	struct usb_hcd *hcd = platform_get_drvdata(dev);

	return 0;
}
*/

static struct platform_driver ohci_hcd_ks8692_driver = {
	.probe		= ohci_hcd_ks8692_drv_probe,
	.remove		= ohci_hcd_ks8692_drv_remove,
	/*.suspend	= ohci_hcd_ks8692_drv_suspend, */
	/*.resume	= ohci_hcd_ks8692_drv_resume, */
	.shutdown	= usb_hcd_platform_shutdown,
	.driver		= {
		.name	= "pegasus-ohci",
		.owner	= THIS_MODULE,
	},
};
