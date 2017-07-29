/*
	Copyright (c) 2002-2011, Micrel Inc.

	Written 2004 by LIQUN RUAN

	This software may be used and distributed according to the terms of 
	the GNU General Public License (GPL), incorporated herein by reference.
	Drivers based on or derived from this code fall under the GPL and must
	retain the authorship, copyright and license notice. This file is not
	a complete program and may only be used when the entire operating
	system is licensed under the GPL.

	The author may be reached as lruan@kendin.com
	Micrel Semiconductors
	1931 Fortune Dr.
	San Jose, CA 95131

	header file for ks8695_utils.c.
*/

#ifndef __KS8695_UTILS_H
#define __KS8695_UTILS_H

#include <linux/types.h>
#include <linux/version.h>
#include <mach/hardware.h>

#define KS8695_UTIL_WRITE_REG(reg, value)	((*(volatile uint32_t *)(IO_ADDRESS(KS8695_IO_BASE) + (reg))) = value)
#define KS8695_UTIL_READ_REG(reg)		(*(volatile uint32_t *)(IO_ADDRESS(KS8695_IO_BASE) + (reg)))

/* function prototypes */
void ks8695_util_gpio_init(u32 gpioPin);
void ks8695_util_gpio_configure(u32 gpio, u32 bSet);
void ks8695_util_enable_interrupt(u32 irq, u32 bEnable);
void ks8695_util_reset_use_count(u32 irq);

#endif /*__KS8695_UTILS_H */

