/*
 *  linux/arch/arm/mach-ks8692/cpu.c
 *
 *  Copyright (C) 2001-2002 Deep Blue Solutions Ltd.
 *
 *  $Id: //depot/swdev/LAN/Switch/KSZ/kernels/linux-3.18/arch/arm/mach-ksz8692/cpu.c#3 $
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * CPU support functions
 */
#include <linux/module.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/cpufreq.h>
#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/smp.h>
#include <linux/init.h>

#include <asm/hardware.h>
#include <asm/io.h>
#include <asm/mach-types.h>

static struct cpufreq_driver ks8692_driver;

static unsigned int bus_clock[8] = { 125000, 100000, 62500, 50000, 41700, 33300, 31300, 25000 };
static unsigned int cpu_clock[8] = { 166000, 166000, 83000, 83000, 55300, 55300, 41500, 41500 };

/*
 * Validate the speed policy.
 */
static int ks8692_verify_policy(struct cpufreq_policy *policy)
{
	unsigned int core_clock;

	cpufreq_verify_within_limits(policy, 
				     policy->cpuinfo.min_freq, 
				     policy->cpuinfo.max_freq);

	return 0;
}


static int ks8692_set_target(struct cpufreq_policy *policy,
				 unsigned int target_freq,
				 unsigned int relation)
{
	unsigned long cpus_allowed;
	int cpu = policy->cpu;
	struct cpufreq_freqs freqs;
	unsigned int  current_clock, i;

	/*
	 * Save this threads cpus_allowed mask.
	 */
	cpus_allowed = current->cpus_allowed;

	/*
	 * Bind to the specified CPU.  When this call returns,
	 * we should be running on the right CPU.
	 */
	set_cpus_allowed(current, 1 << cpu);
	BUG_ON(cpu != smp_processor_id());

	/* get current setting */
	current_clock  = __raw_readl(KS8692_VA_IO_BASE + 0x4);

	freqs.old = cpu_clock[current_clock];

	/* icst525_khz_to_vco rounds down -- so we need the next
	 * larger freq in case of CPUFREQ_RELATION_L.
	 */
	if (target_freq > policy->max)
		target_freq = policy->max;
	freqs.new = target_freq;
	freqs.cpu = policy->cpu;

	if (freqs.old == freqs.new) {
		set_cpus_allowed(current, cpus_allowed);
		return 0;
	}

	cpufreq_notify_transition(&freqs, CPUFREQ_PRECHANGE);

	/*assume that asycronious mode is always on*/

	for ( i = 0; i < 8; i++)
	{
	   if (cpu_clock[i] == freqs.new)
	       break;	   
	}
	__raw_writel(i, KS8692_VA_IO_BASE + 0x4);
	/*
	 * Restore the CPUs allowed mask.
	 */
	set_cpus_allowed(current, cpus_allowed);

	cpufreq_notify_transition(&freqs, CPUFREQ_POSTCHANGE);

	return 0;
}

static int ks8692_cpufreq_init(struct cpufreq_policy *policy)
{
	unsigned long cpus_allowed;
	unsigned int cpu = policy->cpu;

	cpus_allowed = current->cpus_allowed;

	set_cpus_allowed(current, 1 << cpu);
	BUG_ON(cpu != smp_processor_id());

	/* set default policy and cpuinfo */
	policy->governor = CPUFREQ_DEFAULT_GOVERNOR;
	policy->cpuinfo.max_freq = 166000;
	policy->cpuinfo.min_freq = 41500;
	policy->cpuinfo.transition_latency = 1000000; /* 1 ms, assumed */
	policy->cur = policy->min = policy->max = __raw_readl(KS8692_VA_IO_BASE + 0x4);
	set_cpus_allowed(current, cpus_allowed);
	return 0;
}

static struct cpufreq_driver ks8692_driver = {
	.verify		= ks8692_verify_policy,
	.target		= ks8692_set_target,
	.init		= ks8692_cpufreq_init,
	.name		= "centaur",
};

static int __init ks8692_cpu_init(void)
{
	return cpufreq_register_driver(&ks8692_driver);
}

static void __exit ks8692_cpu_exit(void)

	cpufreq_unregister_driver(&ks8692_driver);
}

MODULE_AUTHOR ("Hui Jia");
MODULE_DESCRIPTION ("cpufreq driver for Micrel Centaur SoCs");
MODULE_LICENSE ("GPL");

module_init(ks8692_cpu_init);
module_exit(ks8692_cpu_exit);
