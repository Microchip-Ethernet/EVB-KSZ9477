/*
 * Watchdog driver for Micrel SoC.
 *
 * (C) 2007 Andrew Victor
 * (C) 2009-2011 Micrel, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/platform_device.h>
#include <linux/watchdog.h>
#include <asm/io.h>
#include <asm/uaccess.h>
#include <mach/platform.h>
#include <mach/hardware.h>


/* seconds */
#define WDT_DEFAULT_TIME	5
#define WDT_MAX_TIME		170

/* microseconds */
#define WDT_MARGIN		800000

static int wdt_time = WDT_DEFAULT_TIME;
static int nowayout = WATCHDOG_NOWAYOUT;

module_param(wdt_time, int, 0);
MODULE_PARM_DESC(wdt_time, "Watchdog time in seconds. (default="__MODULE_STRING(WDT_DEFAULT_TIME) ")");

#ifdef CONFIG_WATCHDOG_NOWAYOUT
module_param(nowayout, int, 0);
MODULE_PARM_DESC(nowayout, "Watchdog cannot be stopped once started (default=" __MODULE_STRING(WATCHDOG_NOWAYOUT) ")");
#endif


static unsigned long wdt_busy;

/* ......................................................................... */

/*
 * Disable the watchdog.
 */
static void inline wdt_stop(void)
{
	unsigned long reg;

	reg = READ_TIMER_CTRL();
	DISABLE_TIMER(reg);
}

/*
 * Enable and reset the watchdog.
 */
static void inline wdt_start(void)
{
	unsigned long reg;
	unsigned long interval;
	unsigned long pcount;
	unsigned long value;

	/* disable timer0 */
	wdt_stop();

	/* program timer0 */
	interval = 1000000 * wdt_time;

	/* add some margin because of application delay. */
	interval += WDT_MARGIN;
	interval *= TICKS_PER_uSEC;
	value = interval;
	pcount = 2;
	value |= 0xFF;
	WRITE_TIMER_VALUE(value, pcount);

	/* re-enable timer0 */
	reg = READ_TIMER_CTRL();
	ENABLE_TIMER(reg);
}

/*
 * Reload the watchdog timer.  (ie, pat the watchdog)
 */
static void inline wdt_reload(void)
{
	unsigned long reg;

	local_irq_disable();

	/* disable, then re-enable timer0 */
	reg = READ_TIMER_CTRL();
	DISABLE_TIMER(reg);
	ENABLE_TIMER(reg);

	local_irq_enable();
}

/*
 * Change the watchdog time interval.
 */
static int wdt_settimeout(int new_time)
{
	if ((new_time <= 0) || (new_time > WDT_MAX_TIME))
		return -EINVAL;

	/* Set new watchdog time. It will be used when wdt_start() is called. */
	wdt_time = new_time;
	return 0;
}

/* ......................................................................... */

static struct timer_list timer;

/*
 * Watchdog device is opened, and watchdog starts running.
 */
static int wdt_open(struct inode *inode, struct file *file)
{
	if (test_and_set_bit(0, &wdt_busy))
		return -EBUSY;

	timer.expires = jiffies + (wdt_time * 1000000 + WDT_MARGIN / 2) *
		HZ / 1000000;
	add_timer(&timer);
	wdt_start();
	return nonseekable_open(inode, file);
}

/*
 * Close the watchdog device.
 * If CONFIG_WATCHDOG_NOWAYOUT is NOT defined then the watchdog is also
 *  disabled.
 */
static int wdt_close(struct inode *inode, struct file *file)
{
	/* Disable the watchdog when file is closed */
	if (!nowayout)
		wdt_stop();
	if (timer.expires) {
		del_timer_sync(&timer);
		timer.expires = 0;
	}

	clear_bit(0, &wdt_busy);
	return 0;
}

static struct watchdog_info wdt_info = {
	.identity	= "micrel watchdog",
	.options	= WDIOF_SETTIMEOUT | WDIOF_KEEPALIVEPING,
};

/*
 * Handle commands from user-space.
 */
static long wdt_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	void __user *argp = (void __user *)arg;
	int __user *p = argp;
	int new_value;

	switch(cmd) {
		case WDIOC_KEEPALIVE:
			/* pat the watchdog */
			wdt_reload();
			return 0;

		case WDIOC_GETSUPPORT:
			return copy_to_user(argp, &wdt_info, sizeof(wdt_info)) ? -EFAULT : 0;

		case WDIOC_SETTIMEOUT:
			if (get_user(new_value, p))
				return -EFAULT;

			if (wdt_settimeout(new_value))
				return -EINVAL;

			/* Enable new time value */
			wdt_start();

			/* Return current value */
			return put_user(wdt_time, p);

		case WDIOC_GETTIMEOUT:
			return put_user(wdt_time, p);

		case WDIOC_GETSTATUS:
		case WDIOC_GETBOOTSTATUS:
			return put_user(0, p);

		case WDIOC_SETOPTIONS:
			if (get_user(new_value, p))
				return -EFAULT;

			if (new_value & WDIOS_DISABLECARD)
				wdt_stop();
			if (new_value & WDIOS_ENABLECARD)
				wdt_start();
			return 0;

		default:
			return -ENOTTY;
	}
}

/*
 * Pat the watchdog whenever device is written to.
 */
static ssize_t wdt_write(struct file *file, const char *data, size_t len, loff_t *ppos)
{
	/* pat the watchdog */
	wdt_reload();
	if (timer.expires && timer.expires - jiffies <
			WDT_MARGIN * HZ / 1000000) {
		del_timer_sync(&timer);
		timer.expires = 0;
	}
	return len;
}

static void watchdog_monitor(unsigned long ptr)
{
	wdt_reload();
	timer.expires = 0;
}

/* ......................................................................... */

static const struct file_operations wdt_fops = {
	.owner		= THIS_MODULE,
	.llseek		= no_llseek,
	.unlocked_ioctl	= wdt_ioctl,
	.open		= wdt_open,
	.release	= wdt_close,
	.write		= wdt_write,
};

static struct miscdevice wdt_miscdev = {
	.minor		= WATCHDOG_MINOR,
	.name		= "watchdog",
	.fops		= &wdt_fops,
};

static int wdt_probe(struct platform_device *pdev)
{
	int res;

	if (wdt_miscdev.parent)
		return -EBUSY;
	wdt_miscdev.parent = &pdev->dev;

	/* Check that the heartbeat value is within range; if not reset to the default */
	if (wdt_settimeout(wdt_time)) {
		wdt_settimeout(WDT_DEFAULT_TIME);
		pr_info("micrel_wdt: wdt_time value must be 1 <= wdt_time <= %i, using %d\n", wdt_time, WDT_MAX_TIME);
	}

	res = misc_register(&wdt_miscdev);
	if (res)
		return res;

	init_timer(&timer);
	timer.function = watchdog_monitor;
	printk("Micrel Watchdog Timer enabled (%d seconds%s)\n", wdt_time, nowayout ? ", nowayout" : "");
	return 0;
}

static int __exit wdt_remove(struct platform_device *pdev)
{
	int res;

	res = misc_deregister(&wdt_miscdev);
	if (!res)
		wdt_miscdev.parent = NULL;

	return res;
}

static void wdt_shutdown(struct platform_device *pdev)
{
	wdt_stop();
}

#ifdef CONFIG_PM

static int wdt_suspend(struct platform_device *pdev, pm_message_t message)
{
	wdt_stop();
	return 0;
}

static int wdt_resume(struct platform_device *pdev)
{
	if (wdt_busy)
		wdt_start();
	return 0;
}

#else
#define wdt_suspend NULL
#define wdt_resume  NULL
#endif

static struct platform_driver wdt_driver = {
	.probe		= wdt_probe,
	.remove		= wdt_remove,
	.shutdown	= wdt_shutdown,
	.suspend	= wdt_suspend,
	.resume		= wdt_resume,
	.driver		= {
		.name	= "micrel_wdt",
		.owner	= THIS_MODULE,
	},
};

#if 0
static int __init wdt_init(void)
{
	/* Check that the heartbeat value is within range; if not reset to the default */
	if (wdt_settimeout(wdt_time)) {
		wdt_settimeout(WDT_DEFAULT_TIME);
		pr_info("micrel_wdt: wdt_time value must be 1 <= wdt_time <= %i, using %d\n", wdt_time, WDT_MAX_TIME);
	}

	return platform_driver_register(&wdt_driver);
}

static void __exit wdt_exit(void)
{
	platform_driver_unregister(&wdt_driver);
}

module_init(wdt_init);
module_exit(wdt_exit);
#else
module_platform_driver(wdt_driver);
#endif

MODULE_AUTHOR("Micrel, Inc.");
MODULE_DESCRIPTION("Watchdog driver for Micrel SoC");
MODULE_LICENSE("GPL");
MODULE_ALIAS_MISCDEV(WATCHDOG_MINOR);
