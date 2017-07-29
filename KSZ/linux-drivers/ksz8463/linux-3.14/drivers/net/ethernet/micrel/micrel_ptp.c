/*
 * PTP 1588 clock using Micrel PTP switch
 *
 * Copyright (C) 2010 OMICRON electronics GmbH
 * Copyright (C) 2013-2015 Micrel, Inc.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */
#include <linux/device.h>
#include <linux/hrtimer.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/of_platform.h>
#include <linux/timex.h>
#include <linux/io.h>

#include <linux/ptp_clock_kernel.h>

#define N_ALARM		0
#define N_EXT_TS	2

struct micrel_ptp_info {
	struct ptp_clock *clock;
	struct ptp_clock_info caps;
	struct ptp_info *ptp;

	u32 clock_events;
	u64 alarm_interval;
	u64 alarm_value;
};

static void ptp_event_pps(struct micrel_ptp_info *info)
{
	struct ptp_clock_event event;

	event.type = PTP_CLOCK_PPS;
	ptp_clock_event(info->clock, &event);
}

#if 0
static void ptp_event_alarm(struct micrel_ptp_info *info)
{
	struct ptp_clock_event event;

	event.type = PTP_CLOCK_ALARM;
	event.index = 0;
	event.timestamp = info->alarm_value;
	ptp_clock_event(info->clock, &event);
}
#endif

static void ptp_event_trigger(struct micrel_ptp_info *info, int index,
	u32 sec, u32 nsec)
{
	struct ptp_clock_event event;

	event.type = PTP_CLOCK_EXTTS;
	event.index = index;
	event.timestamp = sec;
	event.timestamp *= NSEC_PER_SEC;
	event.timestamp += nsec;
	ptp_clock_event(info->clock, &event);
}

/*
 * PTP clock operations
 */

static int ptp_adjfreq(struct ptp_clock_info *clock, s32 ppb)
{
	struct ptp_clk_options clk_opt;
	int output;
	struct micrel_ptp_info *info =
		container_of(clock, struct micrel_ptp_info, caps);
	int err = 0;

	output = 1;
	clk_opt.sec = clk_opt.nsec = 0;
	clk_opt.drift = -ppb;
	clk_opt.interval = NANOSEC_IN_SEC;
	err = proc_ptp_hw_access(info->ptp,
		DEV_CMD_PUT, DEV_PTP_CLK, output,
		&clk_opt, sizeof(clk_opt), NULL, &output,
		true);
	return err;
}

static int ptp_adjtime(struct ptp_clock_info *clock, s64 delta)
{
	struct ptp_clk_options clk_opt;
	int output;
	struct micrel_ptp_info *info =
		container_of(clock, struct micrel_ptp_info, caps);
	int neg_adj = 0;
	int err = 0;

	if (delta < 0) {
		neg_adj = 1;
		delta = -delta;
	}
	clk_opt.sec = div_u64_rem(delta, NSEC_PER_SEC, &clk_opt.nsec);
	if (!neg_adj)
		output = 2;
	else
		output = 1;
	clk_opt.interval = 0;
	err = proc_ptp_hw_access(info->ptp,
		DEV_CMD_PUT, DEV_PTP_CLK, output,
		&clk_opt, sizeof(clk_opt), NULL, &output,
		true);
	return err;
}

static int ptp_gettime(struct ptp_clock_info *clock, struct timespec *ts)
{
	struct ptp_clk_options clk_opt;
	int output;
	struct micrel_ptp_info *info =
		container_of(clock, struct micrel_ptp_info, caps);
	int err = 0;

	if (!ts)
		return -info->ptp->drift;
	err = proc_ptp_hw_access(info->ptp,
		DEV_CMD_GET, DEV_PTP_CLK, 0,
		&clk_opt, sizeof(clk_opt), NULL, &output,
		true);
	if (err)
		return err;
	ts->tv_sec = clk_opt.sec;
	ts->tv_nsec = clk_opt.nsec;
	return 0;
}

static int ptp_settime(struct ptp_clock_info *clock, const struct timespec *ts)
{
	struct ptp_clk_options clk_opt;
	int output;
	struct micrel_ptp_info *info =
		container_of(clock, struct micrel_ptp_info, caps);
	int err = 0;

	output = 0;
	clk_opt.sec = ts->tv_sec;
	clk_opt.nsec = ts->tv_nsec;
	err = proc_ptp_hw_access(info->ptp,
		DEV_CMD_PUT, DEV_PTP_CLK, output,
		&clk_opt, sizeof(clk_opt), NULL, &output,
		true);
	return err;
}

static int ptp_enable(struct ptp_clock_info *clock,
	struct ptp_clock_request *rq, int on)
{
	struct micrel_ptp_info *info =
		container_of(clock, struct micrel_ptp_info, caps);
	struct ptp_info *ptp = info->ptp;
	u32 bit;

	switch (rq->type) {
	case PTP_CLK_REQ_EXTTS:
		if (rq->extts.index >= 2)
			return -EINVAL;
		bit = 1 << rq->extts.index;
		if (on)
			ptp->clock_events |= bit;
		else
			ptp->clock_events &= ~bit;
		return 0;

	case PTP_CLK_REQ_PPS:
		bit = 1 << 31;
		if (on)
			ptp->clock_events |= bit;
		else
			ptp->clock_events &= ~bit;
		return 0;

	default:
		break;
	}

	return -EOPNOTSUPP;
}

static struct ptp_clock_info ptp_caps = {
	.owner		= THIS_MODULE,
	/* Only 16 characters. */
	.name		= "Micrel clock",
	.max_adj	= MAX_DRIFT_CORR,
	.n_alarm	= N_ALARM,
	.n_ext_ts	= N_EXT_TS,
	.n_per_out	= 0,
	.pps		= 1,
	.adjfreq	= ptp_adjfreq,
	.adjtime	= ptp_adjtime,
	.gettime	= ptp_gettime,
	.settime	= ptp_settime,
	.enable		= ptp_enable,
};

static int micrel_ptp_probe(struct ptp_info *ptp)
{
	struct micrel_ptp_info *info;
#if 0
	struct timespec now;
#endif
	int err = -ENOMEM;

	info = kzalloc(sizeof(*info), GFP_KERNEL);
	if (!info)
		goto no_memory;

	err = -ENODEV;

	info->caps = ptp_caps;

#if 0
	getnstimeofday(&now);
	ptp_settime(&info->caps, &now);
#endif

	info->clock = ptp_clock_register(&info->caps, ptp->parent);
	if (IS_ERR(info->clock)) {
		err = PTR_ERR(info->clock);
		goto no_clock;
	}
	info->ptp = ptp;
	ptp->clock_info = info;

	return 0;

no_clock:
	kfree(info);
no_memory:
	return err;
}

static int micrel_ptp_remove(struct ptp_info *ptp)
{
	struct micrel_ptp_info *info = ptp->clock_info;

	ptp_clock_unregister(info->clock);
	kfree(info);
	ptp->clock_info = NULL;

	return 0;
}

