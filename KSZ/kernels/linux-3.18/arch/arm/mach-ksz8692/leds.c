/*
 * Driver for the 2 user LEDs found on the KSZ9692PB
 * Based on DaVinci's DM365 board code
 *
 * License terms: GNU General Public License (GPL) version 2
 * Author: Linus Walleij <triad@df.lth.se>
 */
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/io.h>
#include <linux/slab.h>
#include <linux/leds.h>

#include <mach/hardware.h>
#include <mach/platform.h>


struct pegasus_led {
	struct led_classdev	cdev;
	u32			mask;
};

/*
 * The triggers lines up below will only be used if the
 * LED triggers are compiled in.
 */
static const struct {
	const char *name;
	const char *trigger;
} pegasus_leds[] = {
	{ "pegasus:0", "cpu0" },
#ifdef CONFIG_LEDS_TRIGGER_HEARTBEAT
	{ "pegasus:1", "heartbeat", },
#else
	{ "pegasus:1", "mmc0", },
#endif
};

static void pegasus_led_set(struct led_classdev *cdev,
	enum led_brightness b)
{
	struct pegasus_led *led = container_of(cdev,
		struct pegasus_led, cdev);
	u32 val = __raw_readl(VIO(KS8692_GPIO_DATA));

	if (b != LED_OFF)
		val &= ~led->mask;
	else
		val |= led->mask;
	__raw_writel(val, VIO(KS8692_GPIO_DATA));
}

static enum led_brightness pegasus_led_get(struct led_classdev *cdev)
{
	struct pegasus_led *led = container_of(cdev,
		struct pegasus_led, cdev);
	u32 val = __raw_readl(VIO(KS8692_GPIO_DATA));

	return (val & led->mask) ? LED_OFF : LED_FULL;
}

static int __init pegasus_leds_init(void)
{
	int i;
	u32 val = __raw_readl(VIO(KS8692_GPIO_DATA));

	val |= 0x0f00;
	__raw_writel(val, VIO(KS8692_GPIO_DATA));
	for (i = 0; i < ARRAY_SIZE(pegasus_leds); i++) {
		struct pegasus_led *led;

		led = kzalloc(sizeof(*led), GFP_KERNEL);
		if (!led)
			break;

		led->cdev.name = pegasus_leds[i].name;
		led->cdev.brightness_set = pegasus_led_set;
		led->cdev.brightness_get = pegasus_led_get;
		led->cdev.default_trigger = pegasus_leds[i].trigger;
		led->mask = BIT(i + 8);

		if (led_classdev_register(NULL, &led->cdev) < 0) {
			kfree(led);
			break;
		}
	}

	return 0;
}

/*
 * Since we may have triggers on any subsystem, defer registration
 * until after subsystem_init.
 */
fs_initcall(pegasus_leds_init);
