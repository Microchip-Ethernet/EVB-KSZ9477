/* arch/arm/mach-ksz8692/devs.h
 *
 * Copyright (c) 2004 Simtec Electronics
 * Ben Dooks <ben@simtec.co.uk>
 *
 * Header file for s3c2410 standard platform devices
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * Modifications:
 *      18-Aug-2004 BJD  Created initial version
 *	27-Aug-2004 BJD  Added timers 0 through 3
 *	10-Feb-2005 BJD	 Added camera from guillaume.gourat@nexvision.tv
*/

#include <linux/platform_device.h>

extern struct platform_device ks8692_device_ohci;
extern struct platform_device ks8692_device_ehci;
extern struct platform_device ks8692_device_usbgadget;

