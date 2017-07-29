/*
 * Copyright (c) 2006-2011, Micrel, Inc.
 *
 * This software may be used and distributed according to the terms of the
 * GNU General Public License (GPL), incorporated herein by reference.
 * Drivers based on or derived from this code fall under the GPL and must
 * retain the authorship, copyright and license notice. This file is not
 * a complete program and may only be used when the entire operating
 * system is licensed under the GPL.
 *
 *	The author may be reached as support@micrel.com
 *	Micrel, Inc.
 *	1931 Fortune Dr.
 *	San Jose, CA 95131
 *
 *	This file contains utilities for Micrel's KSZ8692 SOC Chipset.
 *	And added to kernel for shared interrupt control. It also served as a contralized place to
 *	provide routines shared for all KSZ8692 serials.
 *
 *	Support and updates available at support@micrel.com
 */
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/types.h>

#include <linux/version.h>
#include <mach/platform.h>
#include <mach/ks8692_utils.h>


static u32 interrupt_bin[MAXIRQNUM + 1] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0
};

/*
 * ks8692_util_gpio_init
 *	This function is used to initiate given gpio pin. It is initially for gpio corresponding to extended device
 *	control, but can be used as generic gpio control routine.
 *
 * Argument(s)
 * 	gpioPin		GPIO pin used for miniPCI slot.
 *
 * Return(s)
 *	NONE
 */
void ks8692_util_gpio_init(u32 gpioPin)
{
	u32 uReg;

	if (gpioPin > 3) {
		printk("%s: given gpio pin (%d) out of range (0-3)\n", __FUNCTION__, gpioPin);
		return;
	}

	/* make sure GPIO corresponding to miniPCI interface as input pin */
	uReg = KS8692_UTIL_READ_REG(KS8692_GPIO_MODE);
	uReg &= ~(1L << gpioPin);
	KS8692_UTIL_WRITE_REG(KS8692_GPIO_MODE, uReg);
}

/*
 * ks8692_util_gpio_configure
 *	This function is used to configure given gpio pin corresponding to PCI interrupt bit.
 *
 * Argument(s)
 * 	gpio	gpio pin to configure/reset
 * 	bSet	flag to configure/reset the given gpio pin
 *
 * Return(s)
 *	NONE
 */
void ks8692_util_gpio_configure(u32 gpio, u32 bSet)
{
	u32 uReg;

	if (gpio > 3) {
		printk("%s: given gpio pin (%d) out of range (0-3)\n", __FUNCTION__, gpio);
		return;
	}

	if (bSet) {
		uReg = KS8692_UTIL_READ_REG(KS8692_GPIO_MODE);
		uReg &= ~(1 << gpio);
		KS8692_UTIL_WRITE_REG(KS8692_GPIO_MODE, uReg);
	}

	uReg = KS8692_UTIL_READ_REG(KS8692_GPIO_CTRL);
	/* clear related bits */
	uReg &= ~(0x8 << (gpio << 2));
	if (bSet) {
		/* EXT0-EXT3 for interrupt and level detection (active low) */
		uReg |= (0x08 << (gpio << 2));
	}
	KS8692_UTIL_WRITE_REG(KS8692_GPIO_CTRL, uReg);
}

/*
 * ks8692_util_enable_interrupt
 *	This function is used to enable/disable interrupt associated with KS8692 PCI inerface
 *
 * Argument(s)
 * 	irq	interrupt to enable/disable
 * 	bEnable	flag to enable/disable interrupt
 *
 * Return(s)
 *	NONE
 */
void ks8692_util_enable_interrupt(u32 irq, u32 bEnable)
{
	u32 uIER;

	if (irq > MAXIRQNUM)
	{
		printk("%s: given irq %d is out of range (0 - %d)\n", __FUNCTION__, irq, MAXIRQNUM);
		return;
	}

	/* if corresponding interrupt enabled already in shared case, simply return */
	if (bEnable)
	{
		interrupt_bin[irq]++;
		if (interrupt_bin[irq] > 1)
		{
			return;
		}
	}
	else
	{
		interrupt_bin[irq]--;
		if (interrupt_bin[irq] > 0)
		{
			return;
		}
		else
		{
		}
	}

	/* if EXT related interrupt, and no device uses it any more, clear corresponding gpio accordingly */
	if ( KS8692_INT_EXT_INT0 <= irq  &&  irq <= KS8692_INT_EXT_INT3 )
	{
		u32 gpio = irq - KS8692_INT_EXT_INT0;

		if (!bEnable && 0 == interrupt_bin[irq])
		{
			ks8692_util_gpio_configure(gpio, 0);
		}
		else if ( bEnable  &&  1 == interrupt_bin[ irq ] )
		{
			ks8692_util_gpio_configure(gpio, 1);
		}
	}

	uIER = KS8692_UTIL_READ_REG(KS8692_INT_ENABLE2);
	if (bEnable)
		uIER |= (1L << irq);
	else
		uIER &= ~(1L << irq);
	KS8692_UTIL_WRITE_REG(KS8692_INT_ENABLE2, uIER);
}

/*
 * ks8692_util_reset_use_count
 *	This function is used to reset use count for given irq. It is a back door to reset irq use count and corresponding
 *	interrupt in case something going wrong for debugging purpose.
 *
 * Argument(s)
 * 	irq	interrupt to reset
 *
 * Return(s)
 *	NONE
 */
void ks8692_util_reset_use_count(u32 irq)
{
	if (irq > MAXIRQNUM)
	{
		printk("%s: given irq %d is out of range (0 - %d)\n", __FUNCTION__, irq, MAXIRQNUM);
		return;
	}

	/* for consistency checking */
	if (interrupt_bin[irq] > 0)
	{
		printk("%s: warning, use count %d for irq %d is not zero before forcing reset count\n", __FUNCTION__, interrupt_bin[irq], irq);
	}

	/* let function to minus 1, and don't complain */
	interrupt_bin[irq] = 1;
	ks8692_util_enable_interrupt(irq, 0);
}

EXPORT_SYMBOL(ks8692_util_gpio_init);
EXPORT_SYMBOL(ks8692_util_gpio_configure);
EXPORT_SYMBOL(ks8692_util_enable_interrupt);
EXPORT_SYMBOL(ks8692_util_reset_use_count);
