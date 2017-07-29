/*
 * Copyright (c) 2002-2011, Micrel, Inc.
 *
 * This software may be used and distributed according to the terms of the
 * GNU General Public License (GPL), incorporated herein by reference.
 * Drivers based on or derived from this code fall under the GPL and must
 * retain the authorship, copyright and license notice. This file is not
 * a complete program and may only be used when the entire operating
 * system is licensed under the GPL.
 *
 *	The author may be reached as liqun.ruan@micrel.com
 *	Micrel, Inc.
 *	1931 Fortune Dr.
 *	San Jose, CA 95131
 *
 *	This file contains utilities for Micrel's KS8695/KS8695P/KS8695X SOHO Router Chipset.
 *	And added to kernel for shared interrupt control. It also served as a contralized place to
 *	provide routines shared for all KS8695 serials, including KS8695/P/X/PX.
 *
 *	Support and updates available at
 *	www.micrel.com/ks8695/		not ready yet!!!
 */
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/io.h>

#include <linux/version.h>
#include <mach/ks8695_utils.h>


static u32 interrupt_bin[MAXIRQNUM + 1] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0
};

/*
 * ks8695_util_gpio_init
 *	This function is used to initiate given gpio pin. It is initially for gpio corresponding to extended device
 *	control, but can be used as generic gpio control routine.
 *
 * Argument(s)
 * 	gpioPin		GPIO pin used for miniPCI slot.
 *
 * Return(s)
 *	NONE
 */
void ks8695_util_gpio_init(u32 gpioPin)
{
	u32 uReg;

	if (gpioPin > 3) {
		printk("%s: given gpio pin (%d) out of range (0-3)\n", __FUNCTION__, gpioPin);
		return;
	}

	/* make sure GPIO corresponding to miniPCI interface as input pin */
	uReg = KS8695_UTIL_READ_REG(KS8695_GPIO_MODE);
	uReg &= ~(1L << gpioPin);
	KS8695_UTIL_WRITE_REG(KS8695_GPIO_MODE, uReg);
}

/*
 * ks8695_util_gpio_configure
 *	This function is used to configure given gpio pin corresponding to PCI interrupt bit.
 *
 * Argument(s)
 * 	gpio	gpio pin to configure/reset
 * 	bSet	flag to configure/reset the given gpio pin
 *
 * Return(s)
 *	NONE
 */
void ks8695_util_gpio_configure(u32 gpio, u32 bSet)
{
	u32 uReg;

#if defined(CONFIG_ARCH_KS8695PM) || defined (CONFIG_ARCH_KS8695MB)
	if (gpio > 3) {
		printk("%s: given gpio pin (%d) out of range (0-3)\n", __FUNCTION__, gpio);
#else
	if (gpio > 2) {
		printk("%s: given gpio pin (%d) out of range (0-2)\n", __FUNCTION__, gpio);
#endif
		return;
	}

	if (bSet) {
		uReg = KS8695_UTIL_READ_REG(KS8695_GPIO_MODE);
		uReg &= ~(1 << gpio);
		KS8695_UTIL_WRITE_REG(KS8695_GPIO_MODE, uReg);
	}

	uReg = KS8695_UTIL_READ_REG(KS8695_GPIO_CTRL);
	/* clear related bits */
	uReg &= ~(0xf << (gpio << 2));
	if (bSet) {
		/* EXT0-EXT3 for interrupt and level detection (active low) */
		uReg |= (0x08 << (gpio << 2));
	}
	KS8695_UTIL_WRITE_REG(KS8695_GPIO_CTRL, uReg);
}

/*
 * ks8695_util_enable_interrupt
 *	This function is used to enable/disable interrupt associated with KS8695P PCI inerface
 *
 * Argument(s)
 * 	irq	interrupt to enable/disable
 * 	bEnable	flag to enable/disable interrupt
 *
 * Return(s)
 *	NONE
 */
void ks8695_util_enable_interrupt(u32 irq, u32 bEnable)
{
	u32 uIER;

	if (irq > MAXIRQNUM) {
		printk("%s: given irq %d is out of range (0 - %d)\n", __FUNCTION__, irq, MAXIRQNUM);
		return;
	}

#ifndef CONFIG_KS8695M
	if (irq > 4)
		return;
#endif

	/* if corresponding interrupt enabled already in shared case, simply return */
        if (bEnable) {
		interrupt_bin[irq]++;
		if (interrupt_bin[irq] > 1) {
			//printk("%s: irq %d is in use, use count %d\n", __FUNCTION__, irq, interrupt_bin[irq]);
			return;
		}
	}
	else {
		interrupt_bin[irq]--;
		if (interrupt_bin[irq] > 0) {
			//printk("%s: irq %d is still in use, use count %d\n", __FUNCTION__, irq, interrupt_bin[irq]);
			return;
		}
		else {
			/*printk("%s: irq %d, use count is zero already\n", __FUNCTION__, irq); */
		}
	}

	/* if EXT related interrupt, and no device uses it any more, clear corresponding gpio accordingly */
#if defined(CONFIG_ARCH_KS8695PM) || defined (CONFIG_ARCH_KS8695MB)
	if (irq > 1 && irq < 6) {
#else
	if (irq > 1 && irq < 5) {
#endif
		u32 gpio = irq - KS8695_INT_EXT_INT0;

		if (!bEnable && 0 == interrupt_bin[irq])
			ks8695_util_gpio_configure(gpio, 0);
		else if (bEnable && 1 == interrupt_bin[irq])
			ks8695_util_gpio_configure(gpio, 1);
	}

	uIER = KS8695_UTIL_READ_REG(KS8695_INT_ENABLE);
	if (bEnable)
		uIER |= (1L << irq);
	else
		uIER &= ~(1L << irq);
	KS8695_UTIL_WRITE_REG(KS8695_INT_ENABLE, uIER);
}

/*
 * ks8695_util_reset_use_count
 *	This function is used to reset use count for given irq. It is a back door to reset irq use count and corresponding
 *	interrupt in case something going wrong for debugging purpose.
 *
 * Argument(s)
 * 	irq	interrupt to reset
 *
 * Return(s)
 *	NONE
 */
void ks8695_util_reset_use_count(u32 irq)
{
	if (irq > MAXIRQNUM) {
		printk("%s: given irq %d is out of range (0 - %d)\n", __FUNCTION__, irq, MAXIRQNUM);
		return;
	}

	/* for consistency checking */
	if (interrupt_bin[irq] > 0) {
		printk("%s: warning, use count %d for irq %d is not zero before forcing reset count\n", __FUNCTION__, interrupt_bin[irq], irq);
	}

	/* let function to minus 1, and don't complain */
	interrupt_bin[irq] = 1;
	ks8695_util_enable_interrupt(irq, 0);
}

EXPORT_SYMBOL(ks8695_util_gpio_init);
EXPORT_SYMBOL(ks8695_util_gpio_configure);
EXPORT_SYMBOL(ks8695_util_enable_interrupt);
EXPORT_SYMBOL(ks8695_util_reset_use_count);
