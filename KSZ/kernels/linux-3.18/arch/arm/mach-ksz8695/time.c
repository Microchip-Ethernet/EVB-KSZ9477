/*
 * arch/arm/mach-ksz8695/time.c
 *
 * Micrel Pegasus clocksource, clockevents, and timer interrupt handlers.
 * Copyright (c) 2015 Micrel, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */


#include <linux/clockchips.h>


#define KS8695_CLOCK_RATE	(TICKS_PER_uSEC * 1000000)


static inline void disable_timer1(void)
{
	unsigned long reg;

	reg = KS_R(KS8695_TIMER_CTRL);
	reg &= ~(TIMER_TIME1_ENABLE);
	KS_W(KS8695_TIMER_CTRL, reg);
}  /* disable_timer1 */


static inline void enable_timer1(void)
{
	unsigned long reg;

	reg = KS_R(KS8695_TIMER_CTRL);
	reg |= TIMER_TIME1_ENABLE;
	KS_W(KS8695_TIMER_CTRL, reg);
}  /* enable_timer1 */


static inline void setup_timer1(unsigned long interval)
{
	unsigned long pcount;
	unsigned long value;

	pcount = interval >> 1;
	value = interval - pcount;
	KS_W(KS8695_TIMER1, value);
	KS_W(KS8695_TIMER1_PCOUNT, pcount);
	enable_timer1();
}  /* setup_timer1 */


static int
centaur_set_next_event(unsigned long delta, struct clock_event_device *dev)
{
	setup_timer1(delta);
	return 0;
}

static void
centaur_set_mode(enum clock_event_mode mode, struct clock_event_device *dev)
{
	switch (mode) {
	case CLOCK_EVT_MODE_PERIODIC:
		KS_W(KS8695_TIMER1, TIMER_DATA_VALUE);
		KS_W(KS8695_TIMER1_PCOUNT, TIMER_PULSE_VALUE);
		enable_timer1();
		break;

	case CLOCK_EVT_MODE_ONESHOT:
		disable_timer1();
		break;

	case CLOCK_EVT_MODE_UNUSED:
	case CLOCK_EVT_MODE_SHUTDOWN:
	default:
		/* initializing, released, or preparing for suspend */
		disable_timer1();
		break;
	}
}

static struct clock_event_device ckevt_centaur = {
	.name		= "centaur",
	.features	= CLOCK_EVT_FEAT_PERIODIC | CLOCK_EVT_FEAT_ONESHOT,
	.shift		= 32,
	.rating		= 200,
	.cpumask	= cpu_all_mask,
	.set_next_event	= centaur_set_next_event,
	.set_mode	= centaur_set_mode,
};


static irqreturn_t
centaur_timer_interrupt(int irq, void *dev_id)
{
	struct clock_event_device *c = dev_id;

#ifdef CONFIG_TICK_ONESHOT
	if (c->mode == CLOCK_EVT_MODE_ONESHOT) {
		disable_timer1();
		c->event_handler(c);
	}
	else if (c->mode == CLOCK_EVT_MODE_PERIODIC) {
		c->event_handler(c);
	}
#else
	c->event_handler(c);
#endif

	return IRQ_HANDLED;
}

static struct irqaction centaur_timer_irq = {
	.name		= "timer",
	.flags		= IRQF_DISABLED | IRQF_TIMER | IRQF_IRQPOLL,
	.handler	= centaur_timer_interrupt,
	.dev_id		= &ckevt_centaur,
};

static void __init centaur_timer_init(void)
{
	/*
	 * Initialise to a known state (all timers off)
	 */
        KS_W(KS8695_TIMER_CTRL, 0);

	/*
	 * Make irqs happen for the system timer
	 */
	setup_irq(KS8695_INT_TIMERINT1, &centaur_timer_irq);

#ifdef CONFIG_DELAYED_TIMER
	setup_irq(KS8695_INT_TIMERINT0, &delayed_timer_irq);
#endif

	clockevents_config_and_register(&ckevt_centaur, KS8695_CLOCK_RATE,
		2, 0xffffffffu);
}

#ifdef CONFIG_PM
static void pegasus_timer_suspend(void)
{
}  /* pegasus_timer_suspend */

static void pegasus_timer_resume(void)
{
}  /* pegasus_timer_resume */
#else
#define pegasus_timer_suspend NULL
#define pegasus_timer_resume NULL
#endif

