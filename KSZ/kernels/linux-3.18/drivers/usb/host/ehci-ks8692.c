/*
 * EHCI HCD (Host Controller Driver) for USB.
 *
 * (C) Copyright 2000-2004 David Brownell <dbrownell@users.sourceforge.net>
 *
 * Bus Glue for Micrel Pegasus KSZ8692 EHCI
 *
 * Based on "ohci-ks8692.c" by Matt Porter <mporter@kernel.crashing.org>
 *
 * Modified for Micrel Pegasus KSZ8692 EHCI
 *  by David Choi <david.choi@micrel.com>
 *
 * This file is licenced under the GPL.
 */

#include <linux/platform_device.h>
#include "ks8692.h"

/*-------------------------------------------------------------------------*/

static void ks8692_start_ehc(struct platform_device *dev)
{
	u32 uReg;

#ifndef ks8692_write
#define ks8692_write    au_writel
#endif
#ifndef ks8692_read
#define ks8692_read     au_readl
#endif

	pr_debug(__FILE__ ": starting KS8692 EHCI USB Controller\n");

	/* feature enable: reset to zero is to enable a feature */
	uReg = ks8692_read(KS8692_FEATURE_INTER_CFG);

	/* bit0:host enable */
	ks8692_write(KS8692_FEATURE_INTER_CFG, (uReg & ~0x01));

	/* Interrupt mode */
	uReg = ks8692_read(KS8692_INT_CONTL1);
	ks8692_write(KS8692_INT_CONTL1, uReg & ~INT_USB_HOST_EHCI);

	/* Interrupt enable */
	uReg = ks8692_read(KS8692_INT_ENABLE1);
	ks8692_write(KS8692_INT_ENABLE1, uReg | INT_USB_HOST_EHCI);

	/* Interrupt status */
	uReg = ks8692_read(KS8692_INT_STATUS1);
	/* Clear INT */
	ks8692_write(KS8692_INT_STATUS1, uReg & ~(INT_USB_HOST_EHCI));

	/* Interrupt priority */
	uReg = ks8692_read(KS8692_INT_USB_PRIORITY);
	/* lowest priority */
	ks8692_write(KS8692_INT_USB_PRIORITY, uReg & ~0xfff);

}

static void ks8692_stop_ehc(struct platform_device *dev)
{
	pr_debug(__FILE__ ": stopping KS8692 EHCI USB Controller\n");

}

/*-------------------------------------------------------------------------*/

/* configure so an HC device and id are always provided */
/* always called with process context; sleeping is OK */

/**
 * usb_ehci_ks8692_probe - initialize KS8692-based HCDs
 * Context: !in_interrupt()
 *
 * Allocates basic resources for this USB host controller, and
 * then invokes the start() method for the HCD associated with it
 * through the hotplug entry's driver_data.
 *
 */
int usb_ehci_ks8692_probe(const struct hc_driver *driver,
			  struct platform_device *dev)
{
	int retval;
	struct usb_hcd *hcd;
	struct ehci_hcd *ehci;

	if (dev->resource[1].flags != IORESOURCE_IRQ) {
		pr_debug("ehci_ks8692 resource[1] is not IORESOURCE_IRQ");
		retval = -ENOMEM;
	}

	hcd = usb_create_hcd(driver, &dev->dev, "KS8692");
	if (!hcd)
		return -ENOMEM;

	hcd->rsrc_start = dev->resource[0].start;
	hcd->rsrc_len = dev->resource[0].end - dev->resource[0].start + 1;

	if (!request_mem_region(hcd->rsrc_start, hcd->rsrc_len, hcd_name)) {
		pr_debug("KS8692 EHCI:request_mem_region failed");
		retval = -EBUSY;
		goto err1;
	}

	hcd->regs = ioremap(hcd->rsrc_start, hcd->rsrc_len);

	if (!hcd->regs) {
		pr_debug("ioremap failed");
		retval = -ENOMEM;
		goto err2;
	}

	ehci = hcd_to_ehci(hcd);

	ehci->has_synopsys_hc_bug = 1;

	ehci->caps = hcd->regs;
	ehci->regs = hcd->regs + HC_LENGTH(ehci,
		ehci_readl(ehci, &ehci->caps->hc_capbase));

	/* cache this readonly data; minimize chip reads */
	ehci->hcs_params = ehci_readl(ehci, &ehci->caps->hcs_params);

	/* ehci_hcd_init(hcd_to_ehci(hcd)); */

	retval = usb_add_hcd(hcd, dev->resource[1].start, IRQF_DISABLED);
	if (retval == 0) {
		ks8692_start_ehc(dev);
		return retval;
	}

	ks8692_stop_ehc(dev);
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
 * usb_ehci_hcd_ks8692_remove - shutdown processing for KS8692-based HCDs
 * @dev: USB Host Controller being removed
 * Context: !in_interrupt()
 *
 * Reverses the effect of usb_ehci_hcd_ks8692_probe(), first invoking
 * the HCD's stop() method.  It is always called from a thread
 * context, normally "rmmod", "apmd", or something similar.
 *
 */
void usb_ehci_ks8692_remove(struct usb_hcd *hcd, struct platform_device *dev)
{
	usb_remove_hcd(hcd);
	iounmap(hcd->regs);
	release_mem_region(hcd->rsrc_start, hcd->rsrc_len);
	usb_put_hcd(hcd);
	ks8692_stop_ehc(dev);
}

/*-------------------------------------------------------------------------*/

static const struct hc_driver ehci_ks8692_hc_driver = {
	.description = hcd_name,
	.product_desc = KS8692_SOC_EHCI_NAME,
	.hcd_priv_size = sizeof(struct ehci_hcd),

	/*
	 * generic hardware linkage
	 */
	.irq = ehci_irq,
	.flags = HCD_MEMORY | HCD_USB2,

	/*
	 * basic lifecycle operations
	 */
	.reset = ehci_init,
	.start = ehci_run,
	.stop = ehci_stop,
	.shutdown = ehci_shutdown,

	/*
	 * managing i/o requests and associated device resources
	 */
	.urb_enqueue = ehci_urb_enqueue,
	.urb_dequeue = ehci_urb_dequeue,
	.endpoint_disable = ehci_endpoint_disable,
	.endpoint_reset = ehci_endpoint_reset,

	/*
	 * scheduling support
	 */
	.get_frame_number = ehci_get_frame,

	/*
	 * root hub support
	 */
	.hub_status_data = ehci_hub_status_data,
	.hub_control = ehci_hub_control,
#ifdef	CONFIG_PM
	.hub_suspend = ehci_hub_suspend,
	.hub_resume = ehci_hub_resume,
#endif
	.relinquish_port = ehci_relinquish_port,
	.port_handed_over = ehci_port_handed_over,
	.clear_tt_buffer_complete = ehci_clear_tt_buffer_complete,
};

/*-------------------------------------------------------------------------*/

static int ehci_hcd_ks8692_drv_probe(struct platform_device *pdev)
{
	int ret;

	pr_debug("In ehci_hcd_ks8692_drv_probe\n");

	if (usb_disabled())
		return -ENODEV;

	ret = usb_ehci_ks8692_probe(&ehci_ks8692_hc_driver, pdev);
	return ret;
}

static int ehci_hcd_ks8692_drv_remove(struct platform_device *pdev)
{
	struct usb_hcd *hcd = platform_get_drvdata(pdev);

	usb_ehci_ks8692_remove(hcd, pdev);
	return 0;
}

 /*TBD*/
/*static int ehci_hcd_ks8692_drv_suspend(struct device *dev)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct usb_hcd *hcd = dev_get_drvdata(dev);

	return 0;
}
static int ehci_hcd_ks8692_drv_resume(struct device *dev)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct usb_hcd *hcd = dev_get_drvdata(dev);

	return 0;
}
*/

MODULE_ALIAS("pegasus-ehci");

static struct platform_driver ehci_hcd_ks8692_driver = {
	.probe = ehci_hcd_ks8692_drv_probe,
	.remove = ehci_hcd_ks8692_drv_remove,
	/*.suspend      = ehci_hcd_ks8692_drv_suspend, */
	/*.resume       = ehci_hcd_ks8692_drv_resume, */
	.shutdown = usb_hcd_platform_shutdown,
	.driver = {
		.name   = "pegasus-ehci",
		.owner	= THIS_MODULE,
	},
};

