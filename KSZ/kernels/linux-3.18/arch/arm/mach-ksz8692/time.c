/*
 * arch/arm/mach-ksz8692/time.c
 *
 * Micrel Pegasus clocksource, clockevents, and timer interrupt handlers.
 * Copyright (c) 2008-2015 Micrel, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */


#include <linux/clockchips.h>


static inline void disable_timer1(void)
{
	unsigned long reg;

	reg = KS_R(KS8692_TIMER_CTRL);
	reg &= ~(TIMER_TIME1_ENABLE);
	KS_W(KS8692_TIMER_CTRL, reg);
}  /* disable_timer1 */


static inline void enable_timer1(void)
{
	unsigned long reg;

	reg = KS_R(KS8692_TIMER_CTRL);
	reg |= TIMER_TIME1_ENABLE;
	KS_W(KS8692_TIMER_CTRL, reg);
}  /* enable_timer1 */


static inline void setup_timer1(unsigned long interval)
{
	unsigned long pcount;
	unsigned long value;

	pcount = interval >> 1;
	value = interval - pcount;
	KS_W(KS8692_TIMER1, value);
	KS_W(KS8692_TIMER1_PCOUNT, pcount);
	enable_timer1();
}  /* setup_timer1 */


static int
pegasus_set_next_event(unsigned long delta, struct clock_event_device *dev)
{
	setup_timer1(delta);
	return 0;
}

static void
pegasus_set_mode(enum clock_event_mode mode, struct clock_event_device *dev)
{
	switch (mode) {
	case CLOCK_EVT_MODE_PERIODIC:
		KS_W(KS8692_TIMER1, TIMER_DATA_VALUE);
		KS_W(KS8692_TIMER1_PCOUNT, TIMER_PULSE_VALUE);
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

static struct clock_event_device ckevt_pegasus = {
	.name		= "pegasus",
	.features	= CLOCK_EVT_FEAT_PERIODIC | CLOCK_EVT_FEAT_ONESHOT,
	.shift		= 32,
	.rating		= 200,
	.cpumask	= cpu_all_mask,
	.set_next_event	= pegasus_set_next_event,
	.set_mode	= pegasus_set_mode,
};


static irqreturn_t
pegasus_timer_interrupt(int irq, void *dev_id)
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

static struct irqaction pegasus_timer_irq = {
	.name		= "timer",
	.flags		= IRQF_DISABLED | IRQF_TIMER | IRQF_IRQPOLL,
	.handler	= pegasus_timer_interrupt,
	.dev_id		= &ckevt_pegasus,
};


static cycle_t pegasus_read_cycle(struct clocksource *cs)
{
	return(KS8692_READ_REG(KS8692_TIMER1_COUNTER));
}

static struct clocksource cksrc_pegasus = {
	.name           = "pegasus",
	.rating         = 200,
	.read           = pegasus_read_cycle,
	.mask           = CLOCKSOURCE_MASK(32),
	.shift          = 20,
	.flags		= CLOCK_SOURCE_IS_CONTINUOUS,
};


static void __init pegasus_timer_init(void)
{
	cksrc_pegasus.mult =
		clocksource_khz2mult(ksz_system_bus_clock,
			cksrc_pegasus.shift);
	clocksource_register(&cksrc_pegasus);

	KS_W(KS8692_GPIO_MODE, 0xFF00);
	KS_W(KS8692_GPIO_DATA, 0x3000);

	/*
	 * Initialise to a known state (all timers off)
	 */
        KS_W(KS8692_TIMER_CTRL, 0);

	/*
	 * Make irqs happen for the system timer
	 */
	setup_irq((KS8692_INT_TIMERINT1 + LOW_IRQS), &pegasus_timer_irq);

#ifdef CONFIG_DELAYED_TIMER
	setup_irq((KS8692_INT_TIMERINT0 + LOW_IRQS), &delayed_timer_irq);
#endif

	ckevt_pegasus.mult =
		div_sc(TICKS_PER_uSEC * 1000000, NSEC_PER_SEC,
			ckevt_pegasus.shift);
	ckevt_pegasus.max_delta_ns =
		clockevent_delta2ns(0xffffffff, &ckevt_pegasus);
	ckevt_pegasus.min_delta_ns =
		clockevent_delta2ns(0x200, &ckevt_pegasus);
	clockevents_register_device(&ckevt_pegasus);
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

