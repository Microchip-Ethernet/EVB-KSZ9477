/*
	Copyright (c) 2006-2007, Micrel Semiconductors

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

	header file for ks8692_utils.c.
*/

#ifndef __KS8692_UTILS_H
#define __KS8692_UTILS_H

#include <linux/types.h>
#include <asm/io.h>

#define KS8692_UTIL_WRITE_REG(reg, value)	((*(volatile uint32_t *)(IO_ADDRESS(KS8692_IO_BASE) + (reg))) = value)
#define KS8692_UTIL_READ_REG(reg)		(*(volatile uint32_t *)(IO_ADDRESS(KS8692_IO_BASE) + (reg)))

/* function prototypes */
void ks8692_util_gpio_init(u32 gpioPin);
void ks8692_util_gpio_configure(u32 gpio, u32 bSet);
void ks8692_util_enable_interrupt(u32 irq, u32 bEnable);
void ks8692_util_reset_use_count(u32 irq);

#endif /*__KS8692_UTILS_H */

