/*
 * arch/arm/mach-ksz8692/gpio.c
 *
 * Copyright (C) 2006 Andrew Victor
 * Updated to GPIOLIB, Copyright 2008 Simtec Electronics
 *                     Daniel Silverstone <dsilvers@simtec.co.uk>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <linux/kernel.h>
#include <linux/mm.h>
#include <linux/init.h>
#include <linux/debugfs.h>
#include <linux/seq_file.h>
#include <linux/module.h>
#include <linux/io.h>

#include <mach/hardware.h>
#include <asm/mach/irq.h>

#include <mach/regs-gpio.h>
#include <mach/gpio.h>


void ksz_gpio_enable(unsigned int pin, int gpio)
{
	u32 x;

	x = KS_R(KS_IOPC);
	x &= ~((1 << 3) << (pin << 2));
	if (gpio)
		x |= ((1 << 3) << (pin << 2));
	KS_W(KS_IOPC, x);

	/* set pin as input */
	x = KS_R(KS_IOPM);
	x &= ~IOPM(pin);
	KS_W(KS_IOPM, x);
}
EXPORT_SYMBOL(ksz_gpio_enable);

/*
 * Configure a GPIO line for either GPIO function, or its internal
 * function (Interrupt, Timer, etc).
 */
static void ksz_gpio_mode(unsigned int pin, int gpio)
{
	unsigned long x, flags;

	/* only GPIO 0..3 have internal functions */
	if (pin > KS_GPIO_3)
		return;

	local_irq_save(flags);

	x = KS_R(KS_IOPC);
	x &= ~((1 << 3) << (pin << 2));
	if (gpio)
		x |= ((1 << 3) << (pin << 2));
	KS_W(KS_IOPC, x);

	local_irq_restore(flags);
}


/* .... Generic GPIO interface .............................................. */

/*
 * Configure the GPIO line as an input.
 */
static int ksz_gpio_direction_input(struct gpio_chip *gc, unsigned int pin)
{
	unsigned long x, flags;

	if (pin > KS_GPIO_15)
		return -EINVAL;

	/* set pin to GPIO mode */
	ksz_gpio_mode(pin, 1);

	local_irq_save(flags);

	/* set pin as input */
	x = KS_R(KS_IOPM);
	x &= ~IOPM(pin);
	KS_W(KS_IOPM, x);

	local_irq_restore(flags);

	return 0;
}


/*
 * Configure the GPIO line as an output, with default state.
 */
static int ksz_gpio_direction_output(struct gpio_chip *gc,
	unsigned int pin, int state)
{
	unsigned long x, flags;

	if (pin > KS_GPIO_15)
		return -EINVAL;

	local_irq_save(flags);

	/* set line state */
	x = KS_R(KS_IOPD);
	if (state)
		x |= IOPD(pin);
	else
		x &= ~IOPD(pin);
	KS_W(KS_IOPD, x);

	/* set pin as output */
	x = KS_R(KS_IOPM);
	x |= IOPM(pin);
	KS_W(KS_IOPM, x);

	local_irq_restore(flags);

	return 0;
}


/*
 * Set the state of an output GPIO line.
 */
static void ksz_gpio_set_value(struct gpio_chip *gc,
	unsigned int pin, int state)
{
	unsigned long x, flags;

	if (pin > KS_GPIO_15)
		return;

	local_irq_save(flags);

	/* set output line state */
	x = KS_R(KS_IOPD);
	if (state)
		x |= IOPD(pin);
	else
		x &= ~IOPD(pin);
	KS_W(KS_IOPD, x);

	local_irq_restore(flags);
}


/*
 * Read the state of a GPIO line.
 */
static int ksz_gpio_get_value(struct gpio_chip *gc, unsigned int pin)
{
	u32 x;

	if (pin > KS_GPIO_15)
		return -EINVAL;

	x = KS_R(KS_IOPD);
	return (x & IOPD(pin)) != 0;
}


/*
 * Map GPIO line to IRQ number.
 */
static int ksz_gpio_to_irq(struct gpio_chip *gc, unsigned int pin)
{
	/* only GPIO 0..3 can generate IRQ */
	if (pin > KS_GPIO_3)
		return -EINVAL;

	return pin + KS_INT_EXT_INT0 + LOW_IRQS;
}


/*
 * Map IRQ number to GPIO line.
 */
int irq_to_gpio(unsigned int irq)
{
	if ((irq < KS_INT_EXT_INT0 + LOW_IRQS) ||
			(irq > KS_INT_EXT_INT3 + LOW_IRQS))
		return -EINVAL;

	return irq - (KS_INT_EXT_INT0 + LOW_IRQS);
}
EXPORT_SYMBOL(irq_to_gpio);

/* GPIOLIB interface */

static struct gpio_chip ksz_gpio_chip = {
	.label			= "KSZ",
	.direction_input	= ksz_gpio_direction_input,
	.direction_output	= ksz_gpio_direction_output,
	.get			= ksz_gpio_get_value,
	.set			= ksz_gpio_set_value,
	.to_irq			= ksz_gpio_to_irq,
	.base			= 0,
	.ngpio			= 16,
	.can_sleep		= 0,
};

/* Register the GPIOs */
void ksz_register_gpios(void)
{
	if (gpiochip_add(&ksz_gpio_chip))
		printk(KERN_ERR "Unable to register core GPIOs\n");
}

/* .... Debug interface ..................................................... */

#ifdef CONFIG_DEBUG_FS

static int ksz_gpio_show(struct seq_file *s, void *unused)
{
	u32 enable[] = {
		IOPC_IOEINT0EN, IOPC_IOEINT1EN, IOPC_IOEINT2EN, IOPC_IOEINT3EN,
		IOPC_IOTIM0EN, IOPC_IOTIM1EN
	};
	u32 intmask[] = {
		IOPC_IOEINT0TM, IOPC_IOEINT1TM, IOPC_IOEINT2TM, IOPC_IOEINT3TM
	};
	u32 mode, ctrl, data;
	int i;

	mode = KS_R(KS_IOPM);
	ctrl = KS_R(KS_IOPC);
	data = KS_R(KS_IOPD);

	seq_printf(s, "Pin\tI/O\tFunction\tState\n\n");

	for (i = KS_GPIO_0; i <= KS_GPIO_15; i++) {
		seq_printf(s, "%i:\t", i);

		seq_printf(s, "%s\t", (mode & IOPM(i)) ? "Output" : "Input");

		if (i <= KS_GPIO_3) {
			if (ctrl & enable[i]) {
				seq_printf(s, "EXT%i ", i);

				switch ((ctrl & intmask[i]) >> (4 * i)) {
				case IOPC_TM_LOW:
					seq_printf(s, "(Low)");
					break;
				case IOPC_TM_HIGH:
					seq_printf(s, "(High)");
					break;
				case IOPC_TM_RISING:
					seq_printf(s, "(Rising)");
					break;
				case IOPC_TM_FALLING:
					seq_printf(s, "(Falling)");
					break;
				case IOPC_TM_EDGE:
					seq_printf(s, "(Edges)");
					break;
				}
			} else
				seq_printf(s, "GPIO\t");
		} else if (i <= KS_GPIO_5) {
			if (ctrl & enable[i])
				seq_printf(s, "TOUT%i\t", i - KS_GPIO_4);
			else
				seq_printf(s, "GPIO\t");
		} else
			seq_printf(s, "GPIO\t");

		seq_printf(s, "\t");

		seq_printf(s, "%i\n", (data & IOPD(i)) ? 1 : 0);
	}
	return 0;
}

static int ksz_gpio_open(struct inode *inode, struct file *file)
{
	return single_open(file, ksz_gpio_show, NULL);
}

static const struct file_operations ksz_gpio_operations = {
	.open		= ksz_gpio_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static int __init ksz_gpio_debugfs_init(void)
{
	(void) debugfs_create_file("ksz_gpio", S_IFREG | S_IRUGO, NULL, NULL,
		&ksz_gpio_operations);
	return 0;
}
postcore_initcall(ksz_gpio_debugfs_init);

#endif
