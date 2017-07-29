/**
 * @file pi.c
 * @brief Implements a Proportional Integral clock servo.
 * @note Copyright (C) 2011 Richard Cochran <richardcochran@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */
#include <stdlib.h>
#include <math.h>
#ifdef KSZ_1588_PTP
#include <stdio.h>
#include "mave.h"
#endif

#include "config.h"
#include "pi.h"
#include "print.h"
#include "servo_private.h"

#ifdef KSZ_1588_PTP
#define HWTS_KP_SCALE 0.5
#define HWTS_KI_SCALE 0.1
#else
#define HWTS_KP_SCALE 0.7
#define HWTS_KI_SCALE 0.3
#endif
#define SWTS_KP_SCALE 0.1
#define SWTS_KI_SCALE 0.001

#define MAX_KP_NORM_MAX 1.0
#define MAX_KI_NORM_MAX 2.0

#define FREQ_EST_MARGIN 0.001

struct pi_servo {
	struct servo servo;
	int64_t offset[2];
	uint64_t local[2];
	double drift;
	double kp;
	double ki;
	double last_freq;
	int count;
	/* configuration: */
	double configured_pi_kp;
	double configured_pi_ki;
	double configured_pi_kp_scale;
	double configured_pi_kp_exponent;
	double configured_pi_kp_norm_max;
	double configured_pi_ki_scale;
	double configured_pi_ki_exponent;
	double configured_pi_ki_norm_max;
};

#ifdef KSZ_1588_PTP
struct std_dev_data {
	double prev_avg;
	double prev_dev;
	double last_dev;
	double max_avg;
	double min_avg;
	double max_dev;
	double min_dev;
	unsigned int dev_cnt;
};

static struct std_dev_data drift_dev;
static struct std_dev_data dev_dev;
static struct std_dev_data offset_dev;
static struct filter *offset_avg;
static tmv_t last_offset_avg;

void reset_dev(struct std_dev_data *d)
{
	d->prev_avg = 0.0;
	d->prev_dev = 0.0;
	d->last_dev = 0.0;
	d->dev_cnt = 0;
	d->max_avg = 0.0;
	d->min_avg = 6250000.0;
	d->max_dev = 0.0;
	d->min_dev = 100.0;
}

double running_dev(struct std_dev_data *d, double num)
{
	double avg;
	double dev;

	if (d->dev_cnt > 20000000) {
		pr_info("dev = %lf, %lf", d->last_dev, d->prev_avg);
		d->prev_dev = d->last_dev * d->last_dev * 2;
		d->dev_cnt = 2;
	}
	d->dev_cnt++;
	avg = d->prev_avg + (num - d->prev_avg) / d->dev_cnt;
	dev = d->prev_dev + (num - d->prev_avg) * (num - avg);
	d->prev_avg = avg;
	d->prev_dev = dev;
	d->last_dev = sqrt(dev / d->dev_cnt);
	if (d->dev_cnt > 4) {
		avg = fabs(avg);
		if (avg > d->max_avg)
			d->max_avg = avg;
		if (avg < d->min_avg)
			d->min_avg = avg;
		if (d->last_dev > 0.01) {
			if (d->last_dev > d->max_dev)
				d->max_dev = d->last_dev;
			if (d->last_dev < d->min_dev)
				d->min_dev = d->last_dev;
		}
	}
	return d->last_dev;
}

static void display_dev(struct std_dev_data *d, char *title)
{
	pr_info("%s:", title);
	pr_info("dev = %lf, %lf", d->last_dev, d->prev_avg);
	pr_info("min = %lf, %lf; max = %lf, %lf",
		d->min_dev, d->min_avg, d->max_dev, d->max_avg);
}

static void save_interval(struct pi_servo *s, double offset, double local_ts)
{
	s->offset[0] = s->offset[1];
	s->local[0] = s->local[1];
	s->offset[1] = offset;
	s->local[1] = local_ts;
}

static double check_offset(struct pi_servo *s, double offset, double local_ts)
{
	double interval;

	save_interval(s, offset, local_ts);

	/* Make sure last local time is valid. */
	if (s->local[0] < 0)
		return offset;

	interval = s->local[1] - s->local[0];

	/* Normalize offset if interval is greater than 0.8 second. */
	if (interval > 800000000) {
		offset *= 1000000000;
		offset /= interval;
	}
	return offset;
}

static void check_dev(struct pi_servo *s, double offset, double ppb,
	enum servo_state state)
{
	double dev;
	static enum servo_state last_state;

	if (s->count < 2 + 4)
		return;

	last_offset_avg = filter_sample(offset_avg, fabs(offset));
	dev = running_dev(&offset_dev, offset);
	dev = running_dev(&dev_dev, dev);
	dev = running_dev(&drift_dev, ppb);

	if (state != last_state) {
		last_state = state;
		if (SERVO_UNLOCKED == state) {
			reset_dev(&offset_dev);
			reset_dev(&dev_dev);
			reset_dev(&drift_dev);
			filter_reset(offset_avg);
		}
	}
}
#endif

static void pi_destroy(struct servo *servo)
{
	struct pi_servo *s = container_of(servo, struct pi_servo, servo);
	free(s);
#ifdef KSZ_1588_PTP
	pr_info(" ");
	display_dev(&offset_dev, "offset");
	display_dev(&dev_dev, "dev");
	display_dev(&drift_dev, "drift");
	pr_info("avg: %lld", last_offset_avg);
	filter_destroy(offset_avg);
#endif
}

static double pi_sample(struct servo *servo,
			int64_t offset,
			uint64_t local_ts,
			double weight,
			enum servo_state *state)
{
	struct pi_servo *s = container_of(servo, struct pi_servo, servo);
	double ki_term, ppb = s->last_freq;
	double freq_est_interval, localdiff;

	switch (s->count) {
	case 0:
		s->offset[0] = offset;
		s->local[0] = local_ts;
		*state = SERVO_UNLOCKED;
		s->count = 1;
		break;
	case 1:
		s->offset[1] = offset;
		s->local[1] = local_ts;

		/* Make sure the first sample is older than the second. */
		if (s->local[0] >= s->local[1]) {
			*state = SERVO_UNLOCKED;
			s->count = 0;
			break;
		}

		/* Wait long enough before estimating the frequency offset. */
		localdiff = (s->local[1] - s->local[0]) / 1e9;
		localdiff += localdiff * FREQ_EST_MARGIN;
		freq_est_interval = 0.016 / s->ki;
		if (freq_est_interval > 1000.0) {
			freq_est_interval = 1000.0;
		}
		if (localdiff < freq_est_interval) {
			*state = SERVO_UNLOCKED;
			break;
		}

		/* Adjust drift by the measured frequency offset. */
		s->drift += (1e9 - s->drift) * (s->offset[1] - s->offset[0]) /
						(s->local[1] - s->local[0]);

		if (s->drift < -servo->max_frequency)
			s->drift = -servo->max_frequency;
		else if (s->drift > servo->max_frequency)
			s->drift = servo->max_frequency;

		if ((servo->first_update &&
		     servo->first_step_threshold &&
		     servo->first_step_threshold < fabs(offset)) ||
		    (servo->step_threshold &&
		     servo->step_threshold < fabs(offset)))
			*state = SERVO_JUMP;
		else
			*state = SERVO_LOCKED;

		ppb = s->drift;
		s->count = 2;
#ifdef KSZ_1588_PTP
		running_dev(&drift_dev, s->drift);
		if (*state == SERVO_JUMP) {
			reset_dev(&drift_dev);
			reset_dev(&offset_dev);
			reset_dev(&dev_dev);
			filter_reset(offset_avg);
		}
#endif
		break;
	case 2:
#ifdef KSZ_1588_PTP
		/* Delay jump for E2E getting accurate path delay first. */
		if (*state == SERVO_LOCKING) {
			*state = SERVO_JUMP;
			ppb = s->drift;
			break;

		/* There is still a big enough offset after jump. */
		} else if (*state == SERVO_JUMP && abs(offset) >= 500) {
			ppb = s->drift;
			break;
		}
	default:
#endif
		/*
		 * reset the clock servo when offset is greater than the max
		 * offset value. Note that the clock jump will be performed in
		 * step 1, so it is not necessary to have clock jump
		 * immediately. This allows re-calculating drift as in initial
		 * clock startup.
		 */
		if (servo->step_threshold &&
		    servo->step_threshold < fabs(offset)) {
			*state = SERVO_UNLOCKED;
			s->count = 0;
			break;
		}

#ifdef KSZ_1588_PTP
		offset = check_offset(s, offset, local_ts);
#endif
		ki_term = s->ki * offset * weight;
		ppb = s->kp * offset * weight + s->drift + ki_term;
		if (ppb < -servo->max_frequency) {
			ppb = -servo->max_frequency;
		} else if (ppb > servo->max_frequency) {
			ppb = servo->max_frequency;
		} else {
			s->drift += ki_term;
		}
		*state = SERVO_LOCKED;
#ifdef KSZ_1588_PTP
		check_dev(s, offset, ppb, *state);
		if (s->count < 2 + 5)
			s->count++;
#endif
		break;
	}

	s->last_freq = ppb;
	return ppb;
}

static void pi_sync_interval(struct servo *servo, double interval)
{
	struct pi_servo *s = container_of(servo, struct pi_servo, servo);

	s->kp = s->configured_pi_kp_scale * pow(interval, s->configured_pi_kp_exponent);
	if (s->kp > s->configured_pi_kp_norm_max / interval)
		s->kp = s->configured_pi_kp_norm_max / interval;

	s->ki = s->configured_pi_ki_scale * pow(interval, s->configured_pi_ki_exponent);
	if (s->ki > s->configured_pi_ki_norm_max / interval)
		s->ki = s->configured_pi_ki_norm_max / interval;

	pr_debug("PI servo: sync interval %.3f kp %.3f ki %.6f",
		 interval, s->kp, s->ki);
}

static void pi_reset(struct servo *servo)
{
	struct pi_servo *s = container_of(servo, struct pi_servo, servo);

	s->count = 0;
}

struct servo *pi_servo_create(struct config *cfg, int fadj, int sw_ts)
{
	struct pi_servo *s;

	s = calloc(1, sizeof(*s));
	if (!s)
		return NULL;

	s->servo.destroy = pi_destroy;
	s->servo.sample  = pi_sample;
	s->servo.sync_interval = pi_sync_interval;
	s->servo.reset   = pi_reset;
	s->drift         = fadj;
	s->last_freq     = fadj;
	s->kp            = 0.0;
	s->ki            = 0.0;
	s->configured_pi_kp = config_get_double(cfg, NULL, "pi_proportional_const");
	s->configured_pi_ki = config_get_double(cfg, NULL, "pi_integral_const");
	s->configured_pi_kp_scale = config_get_double(cfg, NULL, "pi_proportional_scale");
	s->configured_pi_kp_exponent =
		config_get_double(cfg, NULL, "pi_proportional_exponent");
	s->configured_pi_kp_norm_max =
		config_get_double(cfg, NULL, "pi_proportional_norm_max");
	s->configured_pi_ki_scale =
		config_get_double(cfg, NULL, "pi_integral_scale");
	s->configured_pi_ki_exponent =
		config_get_double(cfg, NULL, "pi_integral_exponent");
	s->configured_pi_ki_norm_max =
		config_get_double(cfg, NULL, "pi_integral_norm_max");

	if (s->configured_pi_kp && s->configured_pi_ki) {
		/* Use the constants as configured by the user without
		   adjusting for sync interval unless they make the servo
		   unstable. */
		s->configured_pi_kp_scale = s->configured_pi_kp;
		s->configured_pi_ki_scale = s->configured_pi_ki;
		s->configured_pi_kp_exponent = 0.0;
		s->configured_pi_ki_exponent = 0.0;
		s->configured_pi_kp_norm_max = MAX_KP_NORM_MAX;
		s->configured_pi_ki_norm_max = MAX_KI_NORM_MAX;
	} else if (!s->configured_pi_kp_scale || !s->configured_pi_ki_scale) {
		if (sw_ts) {
			s->configured_pi_kp_scale = SWTS_KP_SCALE;
			s->configured_pi_ki_scale = SWTS_KI_SCALE;
		} else {
			s->configured_pi_kp_scale = HWTS_KP_SCALE;
			s->configured_pi_ki_scale = HWTS_KI_SCALE;
		}
	}

#ifdef KSZ_1588_PTP
	offset_avg = mave_create(32);
#endif

	return &s->servo;
}
