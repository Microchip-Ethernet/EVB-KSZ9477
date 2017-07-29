/**
 * Micrel driver request common code
 *
 * Copyright (c) 2015 Microchip Technology Inc.
 *	Tristram Ha <Tristram.Ha@microchip.com>
 *
 * Copyright (c) 2009-2014 Micrel, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */


#include "ksz_req.h"


#define PARAM_DATA_SIZE			80

static int chk_ioctl_size(int len, int size, int additional, int *req_size,
	int *result, void *param, u8 *data)
{
	if (len < size) {
		printk(KERN_INFO "wrong size: %d %d\n", len, size);
		*req_size = size + additional;
		*result = DEV_IOC_INVALID_LEN;
		return -1;
	}
	if (size >= PARAM_DATA_SIZE) {
		printk(KERN_INFO "large size: %d\n", size);
		*result = -EFAULT;
		return -1;
	}
	if (data && (!access_ok(VERIFY_READ, param, size) ||
			copy_from_user(data, param, size))) {
		*result = -EFAULT;
		return -1;
	}
	return 0;
}  /* chk_ioctl_size */

