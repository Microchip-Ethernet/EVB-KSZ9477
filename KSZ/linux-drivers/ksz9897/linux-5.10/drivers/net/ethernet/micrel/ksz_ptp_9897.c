/**
 * Microchip PTP common code
 *
 * Copyright (c) 2015-2020 Microchip Technology Inc.
 *	Tristram Ha <Tristram.Ha@microchip.com>
 *
 * Copyright (c) 2009-2015 Micrel, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */


#define CURRENT_UTC_OFFSET  37 /* 1 Jan 2017 */


#if 0
#define NO_PPS_DETECT
#endif
#if 0
#define DBG_MSG_DROP
#endif


static int mhz_gpo;
static int pps_gpo = DEFAULT_PPS_GPO + 1;


#define FMT_NSEC_SIZE			12

static char *format_nsec(char *str, u32 nsec)
{
	u32 nsec0;
	u32 nsec1;
	u32 nsec2;
	char str0[4];

	nsec0 = nsec % 1000;
	nsec1 = (nsec / 1000) % 1000;
	nsec2 = (nsec / 1000000) % 1000;
	sprintf(str0, "%03u", nsec0);
	if (nsec2)
		sprintf(str, "%3u.%03u.%s", nsec2, nsec1, str0);
	else if (nsec1)
		sprintf(str, "    %3u.%s", nsec1, str0);
	else
		sprintf(str, "        %3u", nsec0);
	return str;
}  /* format_nsec */

struct pseudo_iphdr {
	__u8 ttl;
	__u8 protocol;
	__be16 tot_len;
	__be32 saddr;
	__be32 daddr;
};

struct pseudo_ip6hdr {
	__be16 payload_len;
	__u8 hop_limit;
	__u8 nexthdr;
	struct in6_addr saddr;
	struct in6_addr daddr;
};

static u32 timestamp_val(u32 timestamp, u8 *sec)
{
	*sec = timestamp >> 30;
	timestamp <<= 2;
	timestamp >>= 2;
	return timestamp;
}  /* timestamp_val */

static void calc_diff(struct ksz_ptp_time *prev, struct ksz_ptp_time *cur,
	struct ksz_ptp_time *result)
{
	struct ksz_ptp_time diff;
	int prev_nsec = prev->nsec;
	int cur_nsec = cur->nsec;

	if (prev->sec < 0)
		prev_nsec = -prev_nsec;
	if (cur->sec < 0)
		cur_nsec = -cur_nsec;
	diff.sec = cur->sec - prev->sec;
	diff.nsec = cur_nsec - prev_nsec;
	if (diff.nsec >= NANOSEC_IN_SEC) {
		diff.nsec -= NANOSEC_IN_SEC;
		diff.sec++;
	} else if (diff.nsec <= -NANOSEC_IN_SEC) {
		diff.nsec += NANOSEC_IN_SEC;
		diff.sec--;
	}
	if (diff.sec > 0 && diff.nsec < 0) {
		diff.nsec += NANOSEC_IN_SEC;
		diff.sec--;
	} else if (diff.sec < 0 && diff.nsec > 0) {
		diff.nsec -= NANOSEC_IN_SEC;
		diff.sec++;
	}
	if (diff.nsec < 0 && diff.sec < 0)
		diff.nsec = -diff.nsec;
	result->sec = diff.sec;
	result->nsec = diff.nsec;
}  /* calc_diff */

static void calc_udiff(struct ptp_utime *prev, struct ptp_utime *cur,
	struct ksz_ptp_time *result)
{
	struct ksz_ptp_time t1;
	struct ksz_ptp_time t2;

	if (prev->sec > (1UL << 31) || cur->sec > (1UL << 31)) {
		s64 t3;
		s64 t4;
		s64 diff;
		s32 rem;

		t3 = (u64) prev->sec * NANOSEC_IN_SEC + prev->nsec;
		t4 = (u64) cur->sec * NANOSEC_IN_SEC + cur->nsec;
		diff = t4 - t3;
		t3 = div_s64_s32_rem(diff, NANOSEC_IN_SEC, &rem);
		result->sec = (s32) t3;
		result->nsec = rem;
		return;
	}
	t1.sec = prev->sec;
	t1.nsec = prev->nsec;
	t2.sec = cur->sec;
	t2.nsec = cur->nsec;
	calc_diff(&t1, &t2, result);
}  /* calc_udiff */

static void ptp_write_index(struct ptp_info *ptp, int shift, u8 unit)
{
	struct ksz_sw *sw = ptp->parent;
#ifndef USE_OLD_PTP_UNIT_INDEX
	u32 index = sw->cached.ptp_unit_index;

	index &= ~(PTP_UNIT_M << shift);
	index |= (u32) unit << shift;
	sw->cached.ptp_unit_index = index;
	sw->reg->w32(sw, REG_PTP_UNIT_INDEX__4, index);
#else
	sw->reg->w32(sw, REG_PTP_UNIT_INDEX__4, unit);
#endif
}  /* ptp_write_index */

static void add_nsec(struct ptp_utime *t, u32 nsec)
{
	t->nsec += nsec;
	if (t->nsec >= NANOSEC_IN_SEC) {
		t->nsec -= NANOSEC_IN_SEC;
		t->sec++;
	}
}  /* add_nsec */

static void sub_nsec(struct ptp_utime *t, u32 nsec)
{
	if (t->nsec < nsec) {
		t->nsec += NANOSEC_IN_SEC;
		t->sec--;
	}
	t->nsec -= nsec;
}  /* sub_nsec */

static void update_ts(struct ptp_ts *ts, u32 cur_sec)
{
	int sec;
	u8 sec_chk;

	ts->t.nsec = timestamp_val(ts->timestamp, &sec_chk);
	if (ts->timestamp)
		sec = (cur_sec - sec_chk) & 3;
	else
		sec = 0;
	if (sec >= 2)
		sec -= 4;
	ts->t.sec = cur_sec - sec;
}  /* update_ts */

#define INIT_NSEC			40
#define MIN_CYCLE_NSEC			8
#define MIN_GAP_NSEC			120
#define PULSE_NSEC			8

static int check_cascade(struct ptp_info *ptp, int first, int total,
	u16 *repeat, u32 sec, u32 nsec)
{
	struct ptp_output *cur;
	struct ptp_output *next;
	struct ptp_output *prev;
	int diff;
	int i;
	int tso;
	int min_cnt;
	int cnt;

	tso = first;
	cur = &ptp->outputs[tso];
	next = &ptp->outputs[first + total];
	next->start = cur->start;
	add_nsec(&next->start, cur->iterate);
	for (i = 0; i < total; i++, tso++) {
		cur = &ptp->outputs[tso];
		cur->stop = cur->start;
		add_nsec(&cur->stop, cur->len);
		next = &ptp->outputs[tso + 1];
		calc_udiff(&cur->stop, &next->start, &cur->gap);
		if ((cur->gap.sec < 0 || (!cur->gap.sec && cur->gap.nsec < 0))
				&& (i < total - 1 || 1 != *repeat)) {
			dbg_msg("gap too small: %d=%d"NL, i, cur->gap.nsec);
			return 1;
		}
	}
	if (1 == *repeat)
		goto check_cascade_done;

	min_cnt = *repeat;
	tso = first + 1;
	for (i = 1; i < total; i++, tso++) {
		cur = &ptp->outputs[tso];
		prev = &ptp->outputs[tso - 1];
		if (cur->iterate < prev->iterate) {
			diff = prev->iterate - cur->iterate;
			cnt = prev->gap.nsec / diff + 1;
		} else if (cur->iterate > prev->iterate) {
			diff = cur->iterate - prev->iterate;
			cnt = cur->gap.nsec / diff + 1;
		} else
			cnt = *repeat;
		if (min_cnt > cnt)
			min_cnt = cnt;
	}
	if (*repeat > min_cnt)
		*repeat = min_cnt;
	prev = &ptp->outputs[first + tso];
	for (cnt = 0; cnt < *repeat; cnt++) {
		tso = first;
		for (i = 0; i < total; i++, tso++) {
			cur = &ptp->outputs[tso];
			next = &ptp->outputs[tso + 1];
			dbg_msg("%d: %d:%9d %d %d:%9d %d: %d:%9d"NL,
				i, cur->start.sec, cur->start.nsec, cur->len,
				cur->gap.sec, cur->gap.nsec, cur->iterate,
				cur->stop.sec, cur->stop.nsec);
			if (cur->stop.sec > next->start.sec ||
					(cur->stop.sec == next->start.sec &&
					cur->stop.nsec > next->stop.nsec))
				dbg_msg("> %d %d:%9d %d:%9d"NL, i,
					cur->stop.sec, cur->stop.nsec,
					next->start.sec, next->start.nsec);
			add_nsec(&cur->start, cur->iterate);
			cur->stop = cur->start;
			add_nsec(&cur->stop, cur->len);
			if (!i)
				prev->start = cur->start;
		}
		dbg_msg("%d:%9d"NL, prev->start.sec, prev->start.nsec);
	}

check_cascade_done:
	tso = first;
	cur = &ptp->outputs[tso];
	if (cur->trig.sec >= sec)
		return 0;

	for (i = 0; i < total; i++, tso++) {
		cur = &ptp->outputs[tso];
		cur->trig.sec += sec;
		add_nsec(&cur->trig, nsec);
	}
	return 0;
}

#define MAX_DRIFT_CORR			6250000
#define LOW_DRIFT_CORR			2499981
#define MAX_U32_S			32
#define MAX_DIVIDER_S			31

static u32 drift_in_sec(u32 abs_offset, u64 interval64)
{
	u64 drift64;

	drift64 = abs_offset;
	drift64 *= NANOSEC_IN_SEC;
	drift64 = div_u64_u64(drift64, interval64);
	return (u32) drift64;
}

static u32 clk_adjust_val(int diff, u32 interval)
{
	u32 adjust;
	u64 adjust64;

	if (0 == diff)
		return 0;
	if (diff < 0)
		adjust = -diff;
	else
		adjust = diff;

	/* 2^32 * adjust * 1000000000 / interval / 25000000 */
	if (interval != NANOSEC_IN_SEC)
		adjust = drift_in_sec(adjust, interval);

	if (adjust >= MAX_DRIFT_CORR)
		adjust = 0x3fffffff;
	else {
		adjust64 = 1LL << 32;
		adjust64 *= adjust;
		adjust64 = div_u64_u32(adjust64, 25000000);
		adjust = (u32) adjust64;
		if (adjust >= 0x40000000)
			adjust = 0x3fffffff;
	}
	if (diff < 0)
		adjust |= PTP_RATE_DIR;
	return adjust;
}  /* clk_adjust_val */

static void ptp_tso_off(struct ptp_info *ptp, u8 tso, u16 tso_bit)
{
	ptp->reg->tx_off(ptp, tso);
	ptp->tso_intr &= ~tso_bit;
	ptp->tso_used &= ~tso_bit;
	if (ptp->tso_sys & tso_bit) {
		printk(KERN_INFO "tso %d off!"NL, tso);
		ptp->tso_sys &= ~tso_bit;
	}
	ptp->tso_dev[tso] = NULL;
}  /* ptp_tso_off */

static inline void ptp_tx_reset(struct ptp_info *ptp, u8 tso, u32 *ctrl_ptr)
{
	u32 ctrl;
	struct ksz_sw *sw = ptp->parent;

	if (!ctrl_ptr) {
		ctrl_ptr = &ctrl;
		ptp_write_index(ptp, PTP_TOU_INDEX_S, tso);
		*ctrl_ptr = sw->reg->r32(sw, REG_PTP_CTRL_STAT__4);
	}
	*ctrl_ptr &= ~TS_RESET;
	*ctrl_ptr |= TRIG_RESET;
	sw->reg->w32(sw, REG_PTP_CTRL_STAT__4, *ctrl_ptr);
	*ctrl_ptr &= ~TRIG_RESET;
	sw->reg->w32(sw, REG_PTP_CTRL_STAT__4, *ctrl_ptr);
}  /* ptp_tx_reset */

static inline void ptp_gpo_reset(struct ptp_info *ptp, int gpo, u8 tso,
	u32 *ctrl_ptr)
{
	ptp_tx_reset(ptp, tso, ctrl_ptr);
	ptp->cascade_gpo[gpo].tso &= ~(1 << tso);
}  /* ptp_gpo_reset */

/* -------------------------------------------------------------------------- */

static void ptp_acquire(struct ptp_info *ptp)
{
	struct ksz_sw *sw = ptp->parent;

	sw->ops->acquire(sw);
}  /* ptp_acquire */

static void ptp_release(struct ptp_info *ptp)
{
	struct ksz_sw *sw = ptp->parent;

	sw->ops->release(sw);
}  /* ptp_release */

static void get_ptp_time(struct ptp_info *ptp, struct ptp_utime *t)
{
	u16 data;
	u16 subnsec;
	struct ksz_sw *sw = ptp->parent;

	data = sw->cached.ptp_clk_ctrl;
	data |= PTP_READ_TIME;
	sw->reg->w16(sw, REG_PTP_CLK_CTRL, data);
	do {
		u8 buf[12];
		u16 *w_ptr;
		u32 *d_ptr;

		sw->reg->r(sw, REG_PTP_RTC_SUB_NANOSEC__2, buf, 10);
		w_ptr = (u16 *) buf;
		subnsec = be16_to_cpu(*w_ptr);
		++w_ptr;
		d_ptr = (u32 *) w_ptr;
		t->nsec = be32_to_cpu(*d_ptr);
		++d_ptr;
		t->sec = be32_to_cpu(*d_ptr);
	} while (0);
	subnsec &= PTP_RTC_SUB_NANOSEC_M;
	add_nsec(t, subnsec * 8);
}  /* get_ptp_time */

static void set_ptp_time(struct ptp_info *ptp, struct ptp_utime *t)
{
	u16 data;
	struct ksz_sw *sw = ptp->parent;

	data = sw->cached.ptp_clk_ctrl;
	sw->reg->w16(sw, REG_PTP_RTC_SUB_NANOSEC__2, 0);
	sw->reg->w32(sw, REG_PTP_RTC_NANOSEC, t->nsec);
	sw->reg->w32(sw, REG_PTP_RTC_SEC, t->sec);
	data |= PTP_LOAD_TIME;
	sw->reg->w16(sw, REG_PTP_CLK_CTRL, data);
}  /* set_ptp_time */

static void adjust_ptp_time(struct ptp_info *ptp, int add, u32 sec, u32 nsec,
	int adj_hack)
{
	u16 ctrl;
	u16 adj = 0;
	u32 val = nsec;
	struct ksz_sw *sw = ptp->parent;

	ctrl = sw->cached.ptp_clk_ctrl;
	if (add)
		ctrl |= PTP_STEP_DIR;
	else
		ctrl &= ~PTP_STEP_DIR;
	sw->cached.ptp_clk_ctrl = ctrl;
	if (adj_hack) {
		adj = ctrl;
		ctrl &= ~PTP_CLK_ADJ_ENABLE;
	}
	ctrl |= PTP_STEP_ADJ;
	sw->reg->w32(sw, REG_PTP_RTC_SEC, sec);
	do {
		if (nsec > NANOSEC_IN_SEC - 1)
			nsec = NANOSEC_IN_SEC - 1;
		sw->reg->w32(sw, REG_PTP_RTC_NANOSEC, nsec);
		sw->reg->w16(sw, REG_PTP_CLK_CTRL, ctrl);
		val -= nsec;
		nsec = val;
	} while (val);
	if (adj_hack && (adj & PTP_CLK_ADJ_ENABLE))
		sw->reg->w16(sw, REG_PTP_CLK_CTRL, adj);
#ifdef NO_PPS_DETECT
	if (add && (sec || nsec >= 1000))
		ptp->clk_add = 1;
#endif
}  /* adjust_ptp_time */

static void adjust_sync_time(struct ptp_info *ptp, int diff, u32 interval,
	u32 duration)
{
	u32 adjust;
	struct ksz_sw *sw = ptp->parent;

	adjust = clk_adjust_val(diff, interval);
	adjust |= PTP_TMP_RATE_ENABLE;
	sw->reg->w32(sw, REG_PTP_RATE_DURATION, duration);
	sw->reg->w32(sw, REG_PTP_SUBNANOSEC_RATE, adjust);
}  /* adjust_sync_time */

static void ptp_rx_reset(struct ptp_info *ptp, u8 tsi, u32 *ctrl_ptr)
{
	u32 ctrl;
	struct ksz_sw *sw = ptp->parent;

	if (!ctrl_ptr) {
		ctrl_ptr = &ctrl;
		ptp_write_index(ptp, PTP_TSI_INDEX_S, tsi);
		*ctrl_ptr = sw->reg->r32(sw, REG_PTP_CTRL_STAT__4);
	}
	*ctrl_ptr &= ~TRIG_RESET;
	*ctrl_ptr |= TS_RESET;
	sw->reg->w32(sw, REG_PTP_CTRL_STAT__4, *ctrl_ptr);
	*ctrl_ptr &= ~TS_RESET;
	sw->reg->w32(sw, REG_PTP_CTRL_STAT__4, *ctrl_ptr);
}  /* ptp_rx_reset */

static void ptp_rx_off(struct ptp_info *ptp, u8 tsi)
{
	u32 ctrl;
	u16 tsi_bit = (1 << tsi);
	u32 ts_intr = 0;
	struct ksz_sw *sw = ptp->parent;

	ptp_write_index(ptp, PTP_TSI_INDEX_S, tsi);
	ctrl = sw->reg->r32(sw, REG_PTP_CTRL_STAT__4);
	ctrl &= ~(TRIG_RESET | TS_RESET);

	/* Disable previous timestamp interrupt. */
	if (ptp->ts_intr & tsi_bit) {
		ptp->ts_intr &= ~tsi_bit;
		ctrl &= ~TS_INT_ENABLE;
		ts_intr = tsi_bit;
	}

	/* Disable previous timestamp detection. */
	ctrl &= ~TS_ENABLE;
	sw->reg->w32(sw, REG_PTP_CTRL_STAT__4, ctrl);

	/*
	 * Need to turn off cascade mode if it is used previously; otherwise,
	 * event counter keeps increasing.
	 */
	if (ptp->cascade_rx & tsi_bit) {
		ptp_rx_reset(ptp, tsi, &ctrl);
		sw->reg->w32(sw, REG_TS_CTRL_STAT__4, 0);
		ptp->cascade_rx &= ~tsi_bit;
	}
	if (ts_intr)
		sw->reg->w32(sw, REG_PTP_INT_STATUS__4, ts_intr);
}  /* ptp_rx_off */

static inline void ptp_rx_intr(struct ptp_info *ptp, u16 tsi_bit, u32 *ctrl)
{
	ptp->ts_intr |= tsi_bit;
	*ctrl |= TS_INT_ENABLE;
}  /* ptp_rx_intr */

static inline void ptp_rx_on(struct ptp_info *ptp, u8 tsi, int intr)
{
	u32 ctrl;
	struct ksz_sw *sw = ptp->parent;

	ctrl = sw->reg->r32(sw, REG_PTP_CTRL_STAT__4);
	ctrl &= ~(TRIG_RESET | TS_RESET);

	/* Enable timestamp interrupt. */
	if (intr)
		ptp_rx_intr(ptp, (1 << tsi), &ctrl);

	ctrl |= TS_ENABLE;
	sw->reg->w32(sw, REG_PTP_CTRL_STAT__4, ctrl);
}  /* ptp_rx_on */

static void ptp_rx_restart(struct ptp_info *ptp, u8 tsi)
{
	u32 ctrl;
	struct ksz_sw *sw = ptp->parent;

	ptp_write_index(ptp, PTP_TSI_INDEX_S, tsi);
	ctrl = sw->reg->r32(sw, REG_PTP_CTRL_STAT__4);
	ctrl &= ~(TRIG_RESET | TS_RESET);
	ctrl &= ~TS_ENABLE;
	sw->reg->w32(sw, REG_PTP_CTRL_STAT__4, ctrl);
	ctrl |= TS_ENABLE;
	sw->reg->w32(sw, REG_PTP_CTRL_STAT__4, ctrl);
}  /* ptp_rx_restart */

static u32 ts_event_gpi(u8 gpi, u8 event)
{
	u32 ctrl;
	u32 data;

	ctrl = event;
	ctrl <<= TS_DETECT_S;
	data = gpi & TS_GPI_M;
	data <<= TS_GPI_S;
	ctrl |= data;
	return ctrl;
}

static u32 ts_cascade(int prev)
{
	u32 ctrl;

	ctrl = prev & TS_CASCADE_UPS_M;
	ctrl <<= TS_CASCADE_UPS_S;
	ctrl |= TS_CASCADE_ENABLE;
	return ctrl;
}

static void ptp_rx_event(struct ptp_info *ptp, u8 tsi, u8 gpi, u8 event,
	int intr)
{
	u32 ctrl;
	struct ksz_sw *sw = ptp->parent;

	/* Config pattern. */
	ptp_write_index(ptp, PTP_TSI_INDEX_S, tsi);
	ctrl = ts_event_gpi(gpi, event);
	sw->reg->w32(sw, REG_TS_CTRL_STAT__4, ctrl);

	/* Enable timestamp detection. */
	ptp_rx_on(ptp, tsi, intr);
}  /* ptp_rx_event */

static void ptp_rx_cascade_event(struct ptp_info *ptp, u8 first, u8 total,
	u8 gpi, u8 event, int intr)
{
	int last;
	int tsi;
	u32 ctrl;
	u32 tail;
	int i;
	int prev;
	struct ksz_sw *sw = ptp->parent;

	last = (first + total - 1) % MAX_TIMESTAMP_UNIT;
	tsi = last;
	tail = TS_CASCADE_TAIL;
	for (i = 1; i < total; i++) {
		ptp_write_index(ptp, PTP_TSI_INDEX_S, tsi);
		prev = tsi - 1;
		if (prev < 0)
			prev = MAX_TIMESTAMP_UNIT - 1;
		ctrl = ts_event_gpi(gpi, event);
		ctrl |= ts_cascade(prev);
		ctrl |= tail;
		ptp->cascade_rx |= (1 << tsi);
		sw->reg->w32(sw, REG_TS_CTRL_STAT__4, ctrl);

		/* Enable timestamp interrupt. */
		if (intr) {
			ctrl = sw->reg->r32(sw, REG_PTP_CTRL_STAT__4);
			ptp_rx_intr(ptp, (1 << tsi), &ctrl);
			sw->reg->w32(sw, REG_PTP_CTRL_STAT__4, ctrl);
		}
		--tsi;
		if (tsi < 0)
			tsi = MAX_TIMESTAMP_UNIT - 1;
		tail = 0;
	}
	ptp_write_index(ptp, PTP_TSI_INDEX_S, first);
	ctrl = ts_event_gpi(gpi, event);
	ctrl |= ts_cascade(last);
	ptp->cascade_rx |= (1 << first);
	sw->reg->w32(sw, REG_TS_CTRL_STAT__4, ctrl);

	/* Enable timestamp detection. */
	ptp_rx_on(ptp, first, intr);
}  /* ptp_rx_cascade_event */

static u32 ptp_get_event_cnt(struct ptp_info *ptp, u8 tsi, void *ptr)
{
	struct ksz_sw *sw = ptp->parent;

	ptp_write_index(ptp, PTP_TSI_INDEX_S, tsi);
	return sw->reg->r32(sw, REG_TS_CTRL_STAT__4);
}  /* ptp_get_event_cnt */

static void ptp_get_events(struct ptp_info *ptp, u32 reg_ns, size_t len,
	void *buf, void *ptr)
{
	int i;
	u32 *data = buf;
	struct ksz_sw *sw = ptp->parent;

	sw->reg->r(sw, reg_ns, buf, len);
	for (i = 0; i < len / sizeof(u32); i++)
		data[i] = be32_to_cpu(data[i]);
}  /* ptp_get_events */

static void ptp_read_event_func(struct ptp_info *ptp, u8 tsi, void *ptr,
	u32 (*get_event_cnt)(struct ptp_info *ptp, u8 tsi, void *ptr),
	void (*get_events)(struct ptp_info *ptp, u32 reg_ns, size_t len,
	void *buf, void *ptr))
{
	u32 ctrl;
	u16 tsi_bit = (1 << tsi);
	u8 buf[96];
	u32 *d_ptr;
	u32 reg_ns;
	struct ptp_utime t;
	u32 sub;
	int max_ts;
	int num;
	int i;
	int edge;
	struct ptp_event *event = &ptp->events[tsi];
	int last = event->num;

	ctrl = get_event_cnt(ptp, tsi, ptr);
	num = (ctrl >> TS_EVENT_DETECT_S) & TS_EVENT_DETECT_M;
	max_ts = (num <= event->max) ? num : event->max;
	if (event->num >= max_ts)
		return;
	i = event->num;

	reg_ns = REG_TS_EVENT_0_NANOSEC + TS_EVENT_SAMPLE * i;
	get_events(ptp, reg_ns, 12 * (max_ts - event->num), buf, ptr);
	d_ptr = (u32 *) buf;
	for (; i < max_ts; i++) {
		t.nsec = (*d_ptr);
		++d_ptr;
		t.sec = (*d_ptr);
		++d_ptr;
		sub = (*d_ptr) & TS_EVENT_SUB_NANOSEC_M;
		++d_ptr;
		edge = ((t.nsec >> TS_EVENT_EDGE_S) & TS_EVENT_EDGE_M);
		t.nsec &= TS_EVENT_NANOSEC_M;
		add_nsec(&t, sub * 8);
#if 1
/*
 * THa  2011/10/06
 * Unit sometimes detects rising edge when it is configured to detect falling
 * edge only.  This happens in the case of hooking up the output pin to an
 * input pin and using two units running opposite cycle in cascade mode.  The
 * 8 ns switch pulse before the cycle is too short to detect properly,
 * resulting in missing edges.
 * When detecting events directly from the output pin, the minimum pulse time
 * is 24 ns for proper detection without missing any edge.
 */
		if (event->event < 2 && edge != event->event)
			edge = event->event;
#endif
		event->edge |= edge << i;
		event->t[i] = t;
	}
	event->num = max_ts;

	/* Indicate there is new event. */
	if (event->num > last)
		ptp->ts_status |= tsi_bit;
}  /* ptp_read_event_func */

static void ptp_read_event(struct ptp_info *ptp, u8 tsi)
{
	ptp_read_event_func(ptp, tsi, NULL, ptp_get_event_cnt,
		ptp_get_events);
}  /* ptp_read_event */

static u32 trig_cascade(int prev)
{
	u32 ctrl;

	ctrl = prev & TRIG_CASCADE_UPS_M;
	ctrl <<= TRIG_CASCADE_UPS_S;
	return ctrl;
}

static void ptp_tx_off(struct ptp_info *ptp, u8 tso)
{
	u32 ctrl;
	u16 tso_bit = (1 << tso);
	struct ksz_sw *sw = ptp->parent;

	ptp_write_index(ptp, PTP_TOU_INDEX_S, tso);

	/* Disable previous trigger out if not already completed. */
	ctrl = sw->reg->r32(sw, REG_PTP_CTRL_STAT__4);
	ctrl &= ~(TRIG_RESET | TS_RESET);
	if (ctrl & TRIG_ENABLE) {
		ctrl &= ~TRIG_ENABLE;
		sw->reg->w32(sw, REG_PTP_CTRL_STAT__4, ctrl);
	}

	/*
	 * Using cascade mode previously need to reset the trigger output so
	 * that an errorneous output will not be generated during next
	 * cascade mode setup.
	 */
	if (ptp->cascade_tx & tso_bit) {
		ptp_gpo_reset(ptp, ptp->outputs[tso].gpo, tso, &ctrl);
		ptp->cascade_tx &= ~tso_bit;
	} else {
		ctrl = sw->reg->r32(sw, REG_TRIG_CTRL__4);
		if (ctrl & TRIG_CASCADE_ENABLE) {
			ctrl &= ~TRIG_CASCADE_ENABLE;
			ctrl &= ~TRIG_CASCADE_TAIL;
			ctrl |= trig_cascade(TRIG_CASCADE_UPS_M);
			sw->reg->w32(sw, REG_TRIG_CTRL__4, ctrl);
		}
	}
}  /* ptp_tx_off */

static void ptp_tx_on(struct ptp_info *ptp, u8 tso)
{
	u32 ctrl;
	struct ksz_sw *sw = ptp->parent;

	ctrl = sw->reg->r32(sw, REG_PTP_CTRL_STAT__4);
	ctrl &= ~(TRIG_RESET | TS_RESET);
	ctrl |= TRIG_ENABLE;
	sw->reg->w32(sw, REG_PTP_CTRL_STAT__4, ctrl);
}  /* ptp_tx_on */

static void ptp_tx_trigger_time(struct ptp_info *ptp, u8 tso, u32 sec, u32 nsec)
{
	struct ksz_sw *sw = ptp->parent;

	sw->reg->w32(sw, REG_TRIG_TARGET_SEC, sec);
	sw->reg->w32(sw, REG_TRIG_TARGET_NANOSEC, nsec);
}  /* ptp_tx_trigger_time */

static u32 trig_event_gpo(u8 gpo, u8 event)
{
	u32 ctrl;
	u32 data;

	ctrl = event & TRIG_PATTERN_M;
	ctrl <<= TRIG_PATTERN_S;
	data = gpo & TRIG_GPO_M;
	data <<= TRIG_GPO_S;
	ctrl |= data;
	return ctrl;
}

static void ptp_tx_event(struct ptp_info *ptp, u8 tso, u8 gpo, u8 event,
	u32 pulse, u32 cycle, u16 cnt, u32 sec, u32 nsec, u32 iterate,
	int intr, int now, int opt)
{
	u32 ctrl;
	u32 pattern = 0;
	u16 tso_bit = (1 << tso);
	struct ptp_output *cur = &ptp->outputs[tso];
	struct ksz_sw *sw = ptp->parent;

	/* Hardware immediately keeps level high on new GPIO if not reset. */
	if (cur->level && gpo != cur->gpo)
		ptp_gpo_reset(ptp, cur->gpo, tso, NULL);

	ptp_write_index(ptp, PTP_TOU_INDEX_S, tso);

	/* Config pattern. */
	ctrl = trig_event_gpo(gpo, event);
	if (intr)
		ctrl |= TRIG_NOTIFY;
	if (now)
		ctrl |= TRIG_NOW;
	if (opt)
		ctrl |= TRIG_EDGE;
	ctrl |= trig_cascade(TRIG_CASCADE_UPS_M);
	sw->reg->w32(sw, REG_TRIG_CTRL__4, ctrl);

	/* Config pulse width. */
	if (TRIG_REG_OUTPUT == event) {
		pattern = pulse & TRIG_BIT_PATTERN_M;
		cur->level = 0;
		if (cnt) {
			u32 reg;

			reg = cnt - 1;
			reg %= 16;
			while (reg) {
				pulse >>= 1;
				reg--;
			}
			if (pulse & 1)
				cur->level = 1;
		}
		pulse = 0;
	} else if (event >= TRIG_NEG_PULSE) {
		if (0 == pulse)
			pulse = 1;
		else if (pulse > TRIG_PULSE_WIDTH_M)
			pulse = TRIG_PULSE_WIDTH_M;
		sw->reg->w24(sw, REG_TRIG_PULSE_WIDTH__4 + 1, pulse);
	}

	/* Config cycle width. */
	if (event >= TRIG_NEG_PERIOD) {
		u32 data = cnt;
		int min_cycle = pulse * PULSE_NSEC + MIN_CYCLE_NSEC;

		if (cycle < min_cycle)
			cycle = min_cycle;
		sw->reg->w32(sw, REG_TRIG_CYCLE_WIDTH, cycle);

		/* Config trigger count. */
		data <<= TRIG_CYCLE_CNT_S;
		pattern |= data;
		sw->reg->w32(sw, REG_TRIG_CYCLE_CNT, pattern);
	}

	cur->len = 0;
	if (event >= TRIG_NEG_PERIOD) {
		if (cnt)
			cur->len += cycle * cnt;
		else
			cur->len += 0xF0000000;
	} else if (event >= TRIG_NEG_PULSE)
		cur->len += pulse * PULSE_NSEC;
	else
		cur->len += MIN_CYCLE_NSEC;

	cur->start.sec = sec;
	cur->start.nsec = nsec;
	cur->iterate = iterate;
	cur->trig = cur->start;
	cur->stop = cur->start;
	add_nsec(&cur->stop, cur->len);
	cur->gpo = gpo;

	switch (event) {
	case TRIG_POS_EDGE:
	case TRIG_NEG_PULSE:
	case TRIG_NEG_PERIOD:
		cur->level = 1;
		break;
	case TRIG_REG_OUTPUT:
		break;
	default:
		cur->level = 0;
		break;
	}

	if (ptp->cascade)
		return;

	/*
	 * Need to reset after completion.  Otherwise, this output pattern
	 * does not behave consistently in cascade mode.
	 */
	if (TRIG_NEG_EDGE == event)
		ptp->cascade_tx |= tso_bit;

	ptp->cascade_gpo[gpo].total = 0;
	if (cur->level)
		ptp->cascade_gpo[gpo].tso |= tso_bit;
	else
		ptp->cascade_gpo[gpo].tso &= ~tso_bit;

	/* Config trigger time. */
	ptp_tx_trigger_time(ptp, tso, sec, nsec);

	/* Enable trigger. */
	ptp_tx_on(ptp, tso);
}  /* ptp_tx_event */

static void ptp_pps_event(struct ptp_info *ptp, u8 gpo, u32 sec)
{
	u32 pattern;
	u32 ctrl;
	u32 nsec;
	u32 pulse = (20000000 / 8);	/* 20 ms */
	u32 cycle = 1000000000;
	u16 cnt = 0;
	u8 tso = ptp->pps_tso;
	u8 event = TRIG_POS_PERIOD;
	struct ksz_sw *sw = ptp->parent;

	ptp_tx_off(ptp, tso);

	/* Config pattern. */
	ctrl = trig_event_gpo(gpo, event);
	ctrl |= TRIG_NOTIFY;
	ctrl |= TRIG_NOW;
	ctrl |= trig_cascade(TRIG_CASCADE_UPS_M);
	sw->reg->w32(sw, REG_TRIG_CTRL__4, ctrl);

	/* Config pulse width. */
	if (pulse > TRIG_PULSE_WIDTH_M)
		pulse = TRIG_PULSE_WIDTH_M;
	sw->reg->w24(sw, REG_TRIG_PULSE_WIDTH__4 + 1, pulse);

	/* Config cycle width. */
	sw->reg->w32(sw, REG_TRIG_CYCLE_WIDTH, cycle);

	/* Config trigger count. */
	pattern = cnt;
	pattern <<= TRIG_CYCLE_CNT_S;
	sw->reg->w32(sw, REG_TRIG_CYCLE_CNT, pattern);

	/* Config trigger time. */
	if (ptp->pps_offset >= 0)
		nsec = ptp->pps_offset;
	else {
		nsec = NANOSEC_IN_SEC + ptp->pps_offset;
		sec--;
	}
	ptp_tx_trigger_time(ptp, tso, sec, nsec);

	/* Enable trigger. */
	ptp_tx_on(ptp, tso);
}  /* ptp_pps_event */

static void cfg_10MHz(struct ptp_info *ptp, u8 tso, u8 gpo, u32 sec, u32 nsec)
{
	u32 pattern;
	u32 ctrl;
	u32 pulse = 6;
	u32 cycle = 200;
	u16 cnt = 0;
	u8 event = TRIG_POS_PERIOD;
	struct ksz_sw *sw = ptp->parent;

	/* Config pattern. */
	ctrl = trig_event_gpo(gpo, event);
	ctrl |= TRIG_NOTIFY;
	if (1 == tso)
		ctrl |= TRIG_EDGE;
	ctrl |= trig_cascade(TRIG_CASCADE_UPS_M);
	sw->reg->w32(sw, REG_TRIG_CTRL__4, ctrl);

	/* Config pulse width. */
	if (pulse > TRIG_PULSE_WIDTH_M)
		pulse = TRIG_PULSE_WIDTH_M;
	sw->reg->w32(sw, REG_TRIG_PULSE_WIDTH__4 + 0, pulse);

	/* Config cycle width. */
	sw->reg->w32(sw, REG_TRIG_CYCLE_WIDTH, cycle);

	/* Config trigger count. */
	pattern = cnt;
	pattern <<= TRIG_CYCLE_CNT_S;
	sw->reg->w32(sw, REG_TRIG_CYCLE_CNT, pattern);

	ptp_tx_trigger_time(ptp, tso, sec, nsec);
}  /* cfg_10MHz */

static void ptp_10MHz(struct ptp_info *ptp, u8 tso, u8 gpo, u32 sec)
{
	int i;
	u32 nsec;

	/* Config trigger time. */
	if (ptp->pps_offset >= 0)
		nsec = ptp->pps_offset;
	else {
		nsec = NANOSEC_IN_SEC + ptp->pps_offset;
		sec--;
	}
	for (i = 0; i < 2; i++) {
		ptp_tx_off(ptp, tso);

		cfg_10MHz(ptp, tso, gpo, sec, nsec);

		/* Enable trigger. */
		ptp_tx_on(ptp, tso);

		tso = 1;
		nsec += 12 * 8;
	}
}  /* ptp_10MHz */

static void ptp_tx_cascade_cycle(struct ptp_info *ptp, u8 tso, u32 nsec)
{
	struct ksz_sw *sw = ptp->parent;

	sw->reg->w32(sw, REG_TRIG_ITERATE_TIME, nsec);
}  /* ptp_tx_cascade_cycle */

static void ptp_tx_cascade_on(struct ptp_info *ptp, u8 tso, u8 first, u8 last,
	u16 repeat)
{
	u32 ctrl;
	struct ksz_sw *sw = ptp->parent;

	ctrl = sw->reg->r32(sw, REG_TRIG_CTRL__4);
	ctrl |= TRIG_CASCADE_ENABLE;
	ctrl &= ~trig_cascade(TRIG_CASCADE_UPS_M);
	if (tso == first)
		ctrl |= trig_cascade(last);
	else
		ctrl |= trig_cascade(tso - 1);
	if (repeat && tso == last) {
		ctrl |= TRIG_CASCADE_TAIL;
		ctrl |= repeat - 1;
	}
	sw->reg->w32(sw, REG_TRIG_CTRL__4, ctrl);
}  /* ptp_tx_cascade_on */

static int ptp_tx_cascade(struct ptp_info *ptp, u8 first, u8 total,
	u16 repeat, u32 sec, u32 nsec, int intr)
{
	int i;
	u8 tso;
	u8 last;
	struct ptp_output *cur;

	last = first + total - 1;
	if (last >= MAX_TRIG_UNIT)
		return 1;
	if (check_cascade(ptp, first, total, &repeat, sec, nsec)) {
		dbg_msg("cascade repeat timing is not right"NL);
		return 1;
	}
	tso = last;
	for (i = 0; i < total; i++, tso--) {
		cur = &ptp->outputs[tso];
		ptp_write_index(ptp, PTP_TOU_INDEX_S, tso);
		ptp_tx_trigger_time(ptp, tso, cur->trig.sec,
			cur->trig.nsec);
		ptp_tx_cascade_cycle(ptp, tso, cur->iterate);
		ptp_tx_cascade_on(ptp, tso, first, last, repeat);
		ptp->cascade_tx |= (1 << tso);
	}

	/* Do not reset last unit to keep level high. */
	if (ptp->outputs[last].level) {
		ptp->cascade_tx &= ~(1 << last);
		ptp->cascade_gpo[ptp->outputs[last].gpo].tso |= (1 << last);
	} else
		ptp->cascade_gpo[ptp->outputs[last].gpo].tso &= ~(1 << last);
	ptp_tx_on(ptp, first);
	return 0;
}  /* ptp_tx_cascade */

/* -------------------------------------------------------------------------- */

static void set_ptp_domain(struct ptp_info *ptp, u8 domain)
{
	u16 ctrl;
	struct ksz_sw *sw = ptp->parent;

	ctrl = sw->reg->r16(sw, REG_PTP_DOMAIN_VERSION) & ~PTP_DOMAIN_M;
	ctrl |= domain;
	sw->reg->w16(sw, REG_PTP_DOMAIN_VERSION, ctrl);
}  /* set_ptp_domain */

static void set_ptp_mode(struct ptp_info *ptp, u16 mode)
{
	u16 val;
	u16 sav;
	struct ksz_sw *sw = ptp->parent;

	val = sw->reg->r16(sw, REG_PTP_MSG_CONF1);
	sav = val;
	val &= ~(PTP_1STEP | PTP_TC_P2P | PTP_MASTER);
	val |= mode;
	if (val != sav)
		sw->reg->w16(sw, REG_PTP_MSG_CONF1, val);
}  /* set_ptp_mode */

static void synchronize_clk(struct ptp_info *ptp)
{
	u32 sec;
	int inc;

	if (ptp->adjust_offset < 0 || ptp->adjust_sec < 0) {
		ptp->adjust_offset = -ptp->adjust_offset;
		ptp->adjust_sec = -ptp->adjust_sec;
		inc = false;
	} else
		inc = true;
	sec = (u32) ptp->adjust_sec;
	ptp->reg->adjust_time(ptp, inc, sec, ptp->adjust_offset,
		ptp->features & PTP_ADJ_HACK);
	ptp->offset_changed = ptp->adjust_offset;
	ptp->adjust_offset = 0;
	ptp->adjust_sec = 0;
}  /* synchronize_clk */

static void set_ptp_adjust(struct ptp_info *ptp, u32 adjust)
{
	struct ksz_sw *sw = ptp->parent;

	sw->reg->w32(sw, REG_PTP_SUBNANOSEC_RATE, adjust);
}  /* set_ptp_adjust */

static inline void unsyntonize_clk(struct ptp_info *ptp)
{
	u16 ctrl;
	struct ksz_sw *sw = ptp->parent;

	ctrl = sw->cached.ptp_clk_ctrl;
	ctrl &= ~PTP_CLK_ADJ_ENABLE;
	sw->cached.ptp_clk_ctrl = ctrl;
	sw->reg->w16(sw, REG_PTP_CLK_CTRL, ctrl);
}  /* unsyntonize_clk */

static void syntonize_clk(struct ptp_info *ptp)
{
	u16 ctrl;
	struct ksz_sw *sw = ptp->parent;

	ctrl = sw->cached.ptp_clk_ctrl;
	ctrl |= PTP_CLK_ADJ_ENABLE;
	sw->cached.ptp_clk_ctrl = ctrl;
	sw->reg->w16(sw, REG_PTP_CLK_CTRL, ctrl);
}  /* syntonize_clk */

static u16 get_ptp_delay(struct ptp_info *ptp, uint p, u32 reg)
{
	struct ksz_sw *sw = ptp->parent;
	u16 data;

	sw->ops->p_r16(sw, p, reg, &data);
	return data;
}  /* get_ptp_delay */

static void set_ptp_delay(struct ptp_info *ptp, uint p, u32 reg, u16 nsec)
{
	struct ksz_sw *sw = ptp->parent;

	sw->ops->p_w16(sw, p, reg, nsec);
}  /* set_ptp_delay */

static u16 get_ptp_ingress(struct ptp_info *ptp, uint p)
{
	return get_ptp_delay(ptp, p, REG_PTP_PORT_RX_DELAY__2);
}

static u16 get_ptp_egress(struct ptp_info *ptp, uint p)
{
	return get_ptp_delay(ptp, p, REG_PTP_PORT_TX_DELAY__2);
}

static short get_ptp_asym(struct ptp_info *ptp, uint p)
{
	short val;

	val = get_ptp_delay(ptp, p, REG_PTP_PORT_ASYM_DELAY__2);
	if (val & 0x8000)
		val = -(val & ~0x8000);
	return val;
}

static u32 get_ptp_link(struct ptp_info *ptp, uint p)
{
	struct ksz_sw *sw = ptp->parent;
	u32 data;

	sw->ops->p_r32(sw, p, REG_PTP_PORT_LINK_DELAY__4, &data);
	return data;
}

static void set_ptp_ingress(struct ptp_info *ptp, uint p, u16 nsec)
{
	set_ptp_delay(ptp, p, REG_PTP_PORT_RX_DELAY__2, nsec);
}

static void set_ptp_egress(struct ptp_info *ptp, uint p, u16 nsec)
{
	set_ptp_delay(ptp, p, REG_PTP_PORT_TX_DELAY__2, nsec);
}

static void set_ptp_asym(struct ptp_info *ptp, uint p, short nsec)
{
	if (nsec < 0)
		nsec = -nsec | 0x8000;
	set_ptp_delay(ptp, p, REG_PTP_PORT_ASYM_DELAY__2, nsec);
}

static void set_ptp_link(struct ptp_info *ptp, uint p, u32 nsec)
{
	struct ksz_sw *sw = ptp->parent;

	sw->ops->p_w32(sw, p, REG_PTP_PORT_LINK_DELAY__4, nsec);
}

static inline void dbp_tx_ts(char *name, u8 port, u32 timestamp)
{
	u8 overflow;
	char ts[FMT_NSEC_SIZE];

	timestamp = timestamp_val(timestamp, &overflow);
	format_nsec(ts, timestamp);
	dbg_msg("%s p:%d c:%u %08x:%s"NL, name, port, overflow, timestamp, ts);
}  /* dbp_tx_ts */

static void ptp_tsm_resp(void *data, void *param)
{
	struct tsm_db *db = (struct tsm_db *) data;
	struct ptp_ts *ts = param;
	u32 timestamp;
	u8 sec_chk;

	db->cmd |= TSM_CMD_RESP;
	db->cur_sec = htonl(ts->t.sec);
	db->cur_nsec = htonl(ts->t.nsec);
	timestamp = timestamp_val(ts->timestamp, &sec_chk);
	db->timestamp = htonl(timestamp);
	db->cur_nsec = db->timestamp;
}  /* ptp_tsm_resp */

static void ptp_tsm_get_time_resp(void *data, void *param)
{
	struct tsm_get_time *get = (struct tsm_get_time *) data;
	struct ptp_utime *t = param;

	get->cmd |= TSM_CMD_GET_TIME_RESP;
	get->sec = htonl(t->sec);
	get->nsec = htonl(t->nsec);
}  /* ptp_tsm_get_time_resp */

static void add_tx_delay(struct ptp_ts *ts, int delay, u32 cur_sec)
{
	update_ts(ts, cur_sec);

	/*
	 * Save timestamp without transmit latency for PTP stack that adjusts
	 * transmit latency itself.
	 */
	ts->r = ts->t;
	add_nsec(&ts->t, delay);
	ts->timestamp = ts->t.nsec;
}  /* add_tx_delay */

static void save_tx_ts(struct ptp_info *ptp, struct ptp_tx_ts *tx,
	struct ptp_hw_ts *htx, int delay, uint port)
{
	unsigned long diff = 0;

	add_tx_delay(&htx->ts, delay, ptp->cur_time.sec);
	if (ptp->overrides & PTP_CHECK_PATH_DELAY) {
		if (ptp->last_rx_ts.t.sec) {
			struct ksz_ptp_time diff;

			calc_udiff(&htx->ts.t, &ptp->last_rx_ts.t, &diff);
			dbg_msg("pd: %d"NL, diff.nsec);
		} else
			ptp->last_tx_ts = htx->ts;
	}
	tx->ts = htx->ts;
	if (tx->data.len) {
		struct tsm_db *db = (struct tsm_db *) tx->data.buf;
		u8 msg = tx->data.buf[0] & 3;

		tx->resp_time = jiffies;
		if (tx->req_time)
			diff = tx->resp_time - tx->req_time;
		if (diff < 4 * ptp->delay_ticks) {
			if (tx->missed) {
				if (diff > 2 * ptp->delay_ticks)
					dbg_msg("  caught: %d, %lu; %x=%04x"NL,
						port, diff, msg,
						ntohs(db->seqid));
				if (tx->dev) {
					file_dev_setup_msg(tx->dev,
						tx->data.buf, tx->data.len,
						ptp_tsm_resp, &tx->ts);
					tx->dev = NULL;
				}

				/* Invalidate the timestamp. */
				tx->ts.timestamp = 0;
				tx->req_time = 0;
			}
		} else {
			dbg_msg("  new: %d, %lu; %x=%04x"NL, port, diff,
				msg, ntohs(db->seqid));
		}
		tx->missed = false;
	}
	if (tx->skb) {
		int len;
		u64 ns;
		struct skb_shared_hwtstamps shhwtstamps;
		struct ksz_sw *sw = ptp->parent;

		if (ptp->tx_en & (1 << 8))
			ns = (u64) tx->ts.t.sec * NANOSEC_IN_SEC +
				tx->ts.t.nsec;
		else
			ns = (u64) tx->ts.r.sec * NANOSEC_IN_SEC +
				tx->ts.r.nsec;
		memset(&shhwtstamps, 0, sizeof(shhwtstamps));
		shhwtstamps.hwtstamp = ns_to_ktime(ns);

		/* Indicate which port message is sent out.
		 * Can only report physical port.
		 */
		tx->msg->hdr.reserved2 = get_log_port(sw, port);
		len = (unsigned char *) tx->msg - tx->skb->data;
		__skb_pull(tx->skb, len);
		skb_tstamp_tx(tx->skb, &shhwtstamps);

		dev_kfree_skb_irq(tx->skb);
		tx->skb = NULL;
	}
	htx->sending = false;
}  /* save_tx_ts */

static int get_speed_index(struct ptp_info *ptp, uint port)
{
	int index;
	struct ksz_sw *sw = ptp->parent;
	struct ksz_port_info *info = get_port_info(sw, port);
	int speed = (media_connected == info->state) ?
		info->tx_rate / TX_RATE_UNIT : 0;

	if (speed == 1000)
		index = 0;
	else if (speed == 100)
		index = 1;
	else
		index = 2;
	return index;
}  /* get_speed_index */

static int get_tx_time(struct ptp_info *ptp, uint port, uint p, u16 status)
{
	int delay;
	int index;
	u32 reg;
	u32 *timestamp = NULL;
	struct ptp_tx_ts *tx = NULL;
	struct ptp_hw_ts *htx = NULL;
	struct ksz_sw *sw = ptp->parent;

	index = get_speed_index(ptp, port);
	while (status) {
		delay = ptp->tx_latency[port][index];
		if (status & PTP_PORT_XDELAY_REQ_INT) {
			reg = REG_PTP_PORT_XDELAY_TS;
			tx = &ptp->tx_dreq[port];
			htx = &ptp->hw_dreq[port];
			status &= ~PTP_PORT_XDELAY_REQ_INT;
		} else if (status & PTP_PORT_SYNC_INT) {
			reg = REG_PTP_PORT_SYNC_TS;
			tx = &ptp->tx_sync[port];
			htx = &ptp->hw_sync[port];
			status &= ~PTP_PORT_SYNC_INT;
		} else {
			reg = REG_PTP_PORT_PDRESP_TS;
			tx = &ptp->tx_resp[port];
			htx = &ptp->hw_resp[port];
			status &= ~PTP_PORT_PDELAY_RESP_INT;
			timestamp = &ptp->pdelay_resp_timestamp[port];
		}
		sw->ops->p_r32(sw, p, reg, &htx->ts.timestamp);
		if (timestamp && *timestamp) {
			htx->ts.timestamp = *timestamp;
			delay = 0;
			*timestamp = 0;
		}
		save_tx_ts(ptp, tx, htx, delay, port);
	}
	if (!htx)
		return false;

	return true;
}  /* get_tx_time */

static void generate_tx_event(struct ptp_info *ptp, int gpo)
{
	struct ptp_utime t;

	if (gpo >= MAX_GPIO)
		return;
	ptp->first_sec = 0;
	ptp->intr_sec = 0;
	ptp->update_sec_jiffies = jiffies;
	ptp->reg->get_time(ptp, &t);
	t.sec += 1;
	if (t.nsec >= (NANOSEC_IN_SEC - ptp->delay_ticks * 50000000))
		t.sec += 1;
	if (pps_gpo)
		ptp->reg->pps_event(ptp, gpo, t.sec);
	if (mhz_gpo)
		ptp->reg->ptp_10MHz(ptp, ptp->mhz_tso, ptp->mhz_gpo, t.sec);
	schedule_delayed_work(&ptp->update_sec, (1000000 - t.nsec / 1000) * HZ
		/ 1000000);
	ptp->clk_add = 0;
}  /* generate_tx_event */

static void ptp_check_pps(struct work_struct *work)
{
	struct delayed_work *dwork = to_delayed_work(work);
	struct ptp_info *ptp =
		container_of(dwork, struct ptp_info, check_pps);

	if (ptp->update_sec_jiffies) {
		ptp->ops->acquire(ptp);
		generate_tx_event(ptp, ptp->pps_gpo);
		ptp->ops->release(ptp);
	}
}  /* ptp_check_pps */

static void prepare_gps(struct ptp_info *ptp)
{
	ptp->ops->acquire(ptp);
	ptp->tsi_used |= (1 << ptp->gps_tsi);
	ptp->events[ptp->gps_tsi].event = 1;
	ptp->events[ptp->gps_tsi].timeout = 0;
	ptp->reg->rx_event(ptp, ptp->gps_tsi, ptp->gps_gpi, DETECT_RISE, true);
	ptp->ops->release(ptp);
}  /* prepare_gps */

static void prepare_pps(struct ptp_info *ptp)
{
	if (ptp->pps_gpo >= MAX_GPIO)
		return;
	ptp->ops->acquire(ptp);
	if (pps_gpo) {
		ptp->tso_used |= (1 << ptp->pps_tso);
		ptp->tso_sys |= (1 << ptp->pps_tso);
	}
	if (mhz_gpo) {
		ptp->tso_used |= (1 << ptp->mhz_tso);
		ptp->tso_used |= (1 << 1);
		ptp->tso_sys |= (1 << ptp->mhz_tso);
		ptp->tso_sys |= (1 << 1);
	}
	generate_tx_event(ptp, ptp->pps_gpo);
#ifndef NO_PPS_DETECT
	if (pps_gpo) {
		ptp->tsi_used |= (1 << ptp->pps_tsi);
		ptp->tsi_sys |= (1 << ptp->pps_tsi);
		ptp->events[ptp->pps_tsi].num = 0;
		ptp->events[ptp->pps_tsi].event = 1;
		ptp->events[ptp->pps_tsi].edge = 0;
		ptp->events[ptp->pps_tsi].expired = 0;
		ptp->reg->rx_event(ptp, ptp->pps_tsi, ptp->pps_gpo,
				   DETECT_RISE, true);
	}
#endif
	ptp->ops->release(ptp);
}  /* prepare_pps */

/* -------------------------------------------------------------------------- */

static void ptp_tx_intr_enable(struct ptp_info *ptp)
{
	uint n;
	uint p;
	struct ksz_sw *sw = ptp->parent;

	for (n = 1; n <= ptp->ports; n++) {
		p = get_phy_port(sw, n);
		sw->ops->p_w16(sw, p, REG_PTP_PORT_TX_INT_STATUS__2, 0xffff);
		sw->ops->p_w16(sw, p, REG_PTP_PORT_TX_INT_ENABLE__2,
			       ptp->tx_intr);
	}
}  /* ptp_tx_intr_enable */

/* -------------------------------------------------------------------------- */

static int ptp_poll_event(struct ptp_info *ptp, u8 tsi)
{
	int max_ts;
	int num;
	u32 status;
	u16 tsi_bit = (1 << tsi);
	struct ptp_event *event = &ptp->events[tsi];
	struct ksz_sw *sw = ptp->parent;

	ptp->ops->acquire(ptp);
	ptp_write_index(ptp, PTP_TSI_INDEX_S, tsi);
	status = sw->reg->r32(sw, REG_TS_CTRL_STAT__4);
	ptp->ops->release(ptp);
	num = (status >> TS_EVENT_DETECT_S) & TS_EVENT_DETECT_M;
	max_ts = (num <= event->max) ? num : event->max;
	if (max_ts > event->num) {
		ptp->ops->acquire(ptp);
		status = sw->reg->r32(sw, REG_PTP_INT_STATUS__4);
		if (status & tsi_bit)
			sw->reg->w32(sw, REG_PTP_INT_STATUS__4, tsi_bit);
		ptp->reg->read_event(ptp, tsi);
		ptp->ts_status = 0;
		ptp->ops->release(ptp);
		return true;
	}
	return false;
}  /* ptp_poll_event */

static void convert_scaled_nsec(s64 scaled_nsec, int s, s64 *sec, int *nsec)
{
	int sign;
	u64 quot;
	u32 rem;

	/* Convert to positive number first. */
	if (scaled_nsec < 0) {
		sign = -1;
		scaled_nsec = -scaled_nsec;
	} else
		sign = 1;
	scaled_nsec >>= s;
	quot = div_u64_u32_rem(scaled_nsec, NANOSEC_IN_SEC, &rem);
	*sec = quot;
	*nsec = (int) rem;

	/* Positive number means clock is faster. */
	if (1 == sign) {
		*sec = -*sec;
		*nsec = -*nsec;
	}
}  /* convert_scaled_nsec */

static void adj_cur_time(struct ptp_info *ptp)
{
	if (ptp->adjust_offset || ptp->adjust_sec) {
		synchronize_clk(ptp);
		if (ptp->sec_changed || ptp->clk_add)
			generate_tx_event(ptp, ptp->pps_gpo);
#ifndef NO_PPS_DETECT
		else {
			ptp->update_sec_jiffies = jiffies;
			schedule_delayed_work(&ptp->check_pps,
					      msecs_to_jiffies(1200));
		}
#endif
	}
	if (ptp->sec_changed) {
		struct timespec64 ts;
		struct ptp_utime cur;

		ptp->reg->get_time(ptp, &ptp->cur_time);
		ts = ktime_to_timespec64(ktime_get_real());
		cur.sec = ts.tv_sec;
		cur.nsec = ts.tv_nsec;
		calc_udiff(&ptp->cur_time, &cur, &ptp->time_diff);
		ptp->sec_changed = 0;
	}
}  /* adj_cur_time */

static void set_before_adj(struct ptp_info *ptp, struct ptp_utime *cur)
{
	ptp->adjust_offset += cur->nsec;
	ptp->adjust_offset += ptp->set_delay;
	ptp->adjust_offset += ptp->get_delay;
	cur->nsec = 0;
	if (ptp->adjust_offset > NANOSEC_IN_SEC) {
		ptp->adjust_offset -= NANOSEC_IN_SEC;
		cur->sec++;
	}
	ptp->reg->set_time(ptp, cur);
}   /* set_before_adj */

static void set_cur_time(struct ptp_info *ptp, struct ptp_ts *ts)
{
	struct ptp_utime cur;
	s64 diff_sec;
	int diff_nsec;

	ptp->adjust_offset = ts->t.nsec - ts->timestamp;
	ptp->reg->get_time(ptp, &cur);
	diff_nsec = ts->t.nsec - ts->timestamp;
	diff_sec = (s64) ts->t.sec - cur.sec;
	if (ptp->features & PTP_ADJ_SEC) {
		if (diff_sec) {
			s64 nsec;

			nsec = diff_sec;
			nsec *= NANOSEC_IN_SEC;
			nsec += diff_nsec;
			convert_scaled_nsec(-nsec, 0, &ptp->adjust_sec,
				&ptp->adjust_offset);
		} else {
			ptp->adjust_offset = diff_nsec;
			ptp->adjust_sec = 0;
		}
		ptp->sec_changed = ptp->adjust_sec;
	} else {
		if (abs(diff_sec) <= 1) {
			diff_nsec += diff_sec * NANOSEC_IN_SEC;
			if (abs(diff_nsec) < NANOSEC_IN_SEC) {
				ptp->adjust_offset = diff_nsec;
				diff_sec = 0;
			}
		}
		if (diff_sec) {
			cur.sec = ts->t.sec;
			set_before_adj(ptp, &cur);
			ptp->sec_changed = diff_sec;
		}
		ptp->adjust_sec = 0;
	}
	adj_cur_time(ptp);
}  /* set_cur_time */

static void adj_clock(struct work_struct *work)
{
	struct ptp_info *ptp = container_of(work, struct ptp_info, adj_clk);
	struct ptp_utime cur;

	ptp->ops->acquire(ptp);

	ptp->sec_changed = ptp->adjust_sec;
	if (!(ptp->features & PTP_ADJ_SEC)) {

		/* Need to adjust second. */
		if (abs(ptp->adjust_sec) > 1) {
			ptp->reg->get_time(ptp, &cur);
			cur.sec += ptp->adjust_sec;
			set_before_adj(ptp, &cur);
		} else
			ptp->adjust_offset += ptp->adjust_sec * NANOSEC_IN_SEC;
		ptp->adjust_sec = 0;
	}
	adj_cur_time(ptp);
	ptp->ops->release(ptp);
}  /* adj_clock */

static void set_latency(struct work_struct *work)
{
	struct ptp_info *ptp = container_of(work, struct ptp_info, set_latency);
	struct ksz_sw *sw = ptp->parent;
	int index;
	uint n;
	uint p;

	ptp->ops->acquire(ptp);
	for (n = 1; n <= ptp->ports; n++) {
		p = get_phy_port(sw, n);
		if (ptp->link_ports & (1 << p)) {
			index = get_speed_index(ptp, p);
			set_ptp_ingress(ptp, p, ptp->rx_latency[p][index]);
			set_ptp_egress(ptp, p, ptp->tx_latency[p][index]);
		}
	}
	ptp->ops->release(ptp);
	ptp->link_ports = 0;
}  /* set_latency */

static void execute(struct ptp_info *ptp, struct work_struct *work)
{
	queue_work(ptp->access, work);
}  /* execute */

static void ptp_hw_disable(struct ptp_info *ptp)
{
	int i;
	u32 ctrl;
	struct ksz_sw *sw = ptp->parent;

	for (i = 0; i < 2; i++) {
		sw->cached.ptp_unit_index =
			(i << PTP_TSI_INDEX_S) |
			(i << PTP_TOU_INDEX_S);
		sw->reg->w32(sw, REG_PTP_UNIT_INDEX__4,
			sw->cached.ptp_unit_index);
		ctrl = TS_RESET | TRIG_RESET;
		sw->reg->w32(sw, REG_PTP_CTRL_STAT__4, ctrl);
		sw->reg->w32(sw, REG_PTP_CTRL_STAT__4, 0);
		sw->reg->w32(sw, REG_TRIG_CTRL__4, 0);
		sw->reg->w32(sw, REG_TS_CTRL_STAT__4, 0);
	}
	sw->cached.ptp_unit_index = (i << PTP_TOU_INDEX_S);
	sw->reg->w32(sw, REG_PTP_UNIT_INDEX__4, sw->cached.ptp_unit_index);
	ctrl = TRIG_RESET;
	sw->reg->w32(sw, REG_PTP_CTRL_STAT__4, ctrl);
	sw->reg->w32(sw, REG_PTP_CTRL_STAT__4, 0);
	sw->reg->w32(sw, REG_TRIG_CTRL__4, 0);
	sw->reg->w32(sw, REG_PTP_SUBNANOSEC_RATE, 0);
}  /* ptp_hw_disable */

static void ptp_hw_enable(struct ptp_info *ptp)
{
	uint n;
	uint p;
	int index;
	u16 data;
	struct ksz_sw *sw = ptp->parent;

	ptp->ops->acquire(ptp);
	ptp_hw_disable(ptp);
#ifndef ACL_TEST
	data = sw->reg->r16(sw, REG_PTP_MSG_CONF1);
dbg_msg("msg_conf1: %x"NL, data);
	data = ptp->mode;
	sw->reg->w16(sw, REG_PTP_MSG_CONF1, data);
	if ((data & PTP_ENABLE))
		sw->overrides |= PTP_TAG;
#endif
	data = sw->reg->r16(sw, REG_PTP_MSG_CONF2);
dbg_msg("msg_conf2: %x"NL, data);
	sw->reg->w16(sw, REG_PTP_MSG_CONF2, ptp->cfg);
	data = sw->reg->r16(sw, REG_PTP_CLK_CTRL);
dbg_msg("clk_ctrl: %x"NL, data);
	data |= PTP_CLK_ENABLE;
	data &= ~PTP_CLK_ADJ_ENABLE;
	sw->cached.ptp_clk_ctrl = data;
#if 1
	if (!(sw->features & NEW_CAP))
		data |= PTP_CLK_RESET;
#endif
	sw->reg->w16(sw, REG_PTP_CLK_CTRL, data);

	sw->reg->w16(sw, REG_SW_HSR_TPID__2, 0x892F);

	for (n = 1; n <= ptp->ports; n++) {
		p = get_phy_port(sw, n);
		index = get_speed_index(ptp, p);
		set_ptp_ingress(ptp, p, ptp->rx_latency[p][index]);
		set_ptp_egress(ptp, p, ptp->tx_latency[p][index]);
	}

	/* PTP stack is still running while device is reset. */
	if (ptp->drift_set) {
		ptp->drift = ptp->drift_set;
		ptp->adjust = clk_adjust_val(ptp->drift, NANOSEC_IN_SEC);
		set_ptp_adjust(ptp, ptp->adjust);
		syntonize_clk(ptp);
		ptp->ptp_synt = true;
	}

	ptp->ops->release(ptp);
}  /* ptp_hw_enable */

static void init_tx_ts(struct ptp_tx_ts *ts)
{
	ts->ts.timestamp = 0;
	ts->req_time = 0;
	ts->resp_time = 0;
	ts->missed = false;
	ts->hdr.messageType = 7;
}  /* init_tx_ts */

static void ptp_init_hw(struct ptp_info *ptp)
{
	uint n;
	uint p;
	uint port;
	struct ksz_sw *sw = ptp->parent;

	ptp->ops->acquire(ptp);
	for (n = 1; n <= ptp->ports; n++) {
		int index;

		port = get_phy_port(sw, n);
		p = port;
		ptp->hw_sync[port].ts.timestamp = 0;
		ptp->hw_sync[port].sending = false;
		ptp->hw_dreq[port].ts.timestamp = 0;
		ptp->hw_dreq[port].sending = false;
		ptp->hw_resp[port].ts.timestamp = 0;
		ptp->hw_resp[port].sending = false;
		init_tx_ts(&ptp->tx_sync[port]);
		init_tx_ts(&ptp->tx_dreq[port]);
		init_tx_ts(&ptp->tx_resp[port]);
		sw->ops->p_r32(sw, p, REG_PTP_PORT_XDELAY_TS,
			       &ptp->xdelay_ts[port]);
		sw->ops->p_r32(sw, p, REG_PTP_PORT_PDRESP_TS,
			       &ptp->pdresp_ts[port]);
		index = get_speed_index(ptp, port);
		ptp->rx_latency[port][index] = get_ptp_ingress(ptp, p);
		ptp->tx_latency[port][index] = get_ptp_egress(ptp, p);
		ptp->asym_delay[port][index] = get_ptp_asym(ptp, p);
		ptp->peer_delay[port] = get_ptp_link(ptp, p);
		dbg_msg("%d = %d %d %d; %u"NL, port,
			ptp->rx_latency[port][index],
			ptp->tx_latency[port][index],
			ptp->asym_delay[port][index],
			ptp->peer_delay[port]);
		set_ptp_link(ptp, p, 0);
		ptp->peer_delay[port] = 0;
	}
	ptp->ops->release(ptp);
}  /* ptp_init_hw */

static void ptp_check(struct ptp_info *ptp)
{
	struct ptp_utime cur;
	struct ptp_utime now;
	struct ksz_sw *sw = ptp->parent;

	ptp->features |= PTP_ADJ_HACK;
	ptp->ops->acquire(ptp);
	ptp->reg->get_time(ptp, &cur);
	ptp->reg->adjust_time(ptp, true, 10, 0, true);
	ptp->reg->get_time(ptp, &now);
dbg_msg("%08x:%08x %08x:%08x"NL, cur.sec, cur.nsec, now.sec, now.nsec);
	if (now.sec - cur.sec >= 10) {
		ptp->features &= ~PTP_ADJ_HACK;
		ptp->features |= PTP_ADJ_SEC;
		ptp->reg->adjust_time(ptp, false, 10, 0, true);
		ptp->version = 1;
	}
/*
 * THa  2013/01/08
 * The Rev. D chip has a problem of decrementing nanosecond that is bigger than
 * the current nanosecond when continual clock adjustment is enabled.  The
 * workaround is to use the PTP_ADJ_HACK code although the actual problem
 * avoided is now different.
 */
	if (!(ptp->features & PTP_ADJ_HACK)) {
		u16 data;

		data = sw->cached.ptp_clk_ctrl;
		sw->cached.ptp_clk_ctrl |= PTP_CLK_ADJ_ENABLE;
		sw->reg->w16(sw, REG_PTP_CLK_CTRL, sw->cached.ptp_clk_ctrl);
		if (cur.sec < 1)
			cur.sec = 1;
		cur.nsec = 0;
		ptp->reg->set_time(ptp, &cur);
		ptp->reg->adjust_time(ptp, false, 0, 800000000, false);
		ptp->reg->get_time(ptp, &now);
		dbg_msg("%x:%u %x:%u"NL, cur.sec, cur.nsec, now.sec, now.nsec);
		if (abs(now.sec - cur.sec) > 2) {
			ptp->reg->get_time(ptp, &now);
			dbg_msg("! %x:%u"NL, now.sec, now.nsec);
			ptp->features |= PTP_ADJ_HACK;
			sw->reg->w16(sw, REG_PTP_CLK_CTRL, data);

			sw->reg->w16(sw, REG_PTP_CLK_CTRL,
				data | PTP_CLK_ADJ_ENABLE);
			ptp->reg->set_time(ptp, &cur);
			ptp->reg->adjust_time(ptp, false, 0, 800000000, true);
			ptp->reg->get_time(ptp, &now);
			dbg_msg("ok %x:%u"NL, now.sec, now.nsec);
		}
		sw->cached.ptp_clk_ctrl = data;
		sw->reg->w16(sw, REG_PTP_CLK_CTRL, data);
	}
	ptp->version = 2;
	ptp->ops->release(ptp);
}  /* ptp_check */

static void ptp_start(struct ptp_info *ptp, int init)
{
	u32 ctrl;
	struct timespec64 ts;
	struct ptp_utime t;
	struct ksz_sw *sw = ptp->parent;

	if (!ptp->version) {
		ptp_hw_enable(ptp);
		ptp_check(ptp);
		if (ptp->test_access_time)
			ptp->test_access_time(ptp);
		ptp_init_hw(ptp);
	} else
	if (init && (sw->features & NEW_CAP))
		ptp_hw_enable(ptp);
	ptp->ops->acquire(ptp);
	ctrl = sw->reg->r16(sw, REG_PTP_MSG_CONF1);
	if (ctrl == ptp->mode) {
		ptp->cfg = sw->reg->r16(sw, REG_PTP_MSG_CONF2);
		ptp->domain = sw->reg->r16(sw, REG_PTP_DOMAIN_VERSION) &
			PTP_DOMAIN_M;
		if (!init) {
			ptp->ops->release(ptp);
			return;
		}
	} else if (!init)
		ptp->mode = ctrl;
	if (ptp->mode != ptp->def_mode) {
		dbg_msg("mode changed: %04x %04x; %04x %04x"NL,
			ptp->mode, ptp->def_mode, ptp->cfg, ptp->def_cfg);
		ptp->mode = ptp->def_mode;
		ptp->cfg = ptp->def_cfg;
		ptp->ptp_synt = false;
	}
	dbg_msg("ptp_start: %04x %04x"NL,
		ptp->mode, ptp->cfg);
	sw->reg->w16(sw, REG_PTP_MSG_CONF1, ptp->mode);
	sw->reg->w16(sw, REG_PTP_MSG_CONF2, ptp->cfg);
	sw->reg->w32(sw, REG_PTP_INT_STATUS__4, 0xffffffff);
	ptp->tx_intr = PTP_PORT_XDELAY_REQ_INT;
#if 0
	ptp->tx_intr = PTP_PORT_XDELAY_REQ_INT | PTP_PORT_PDELAY_RESP_INT |
		PTP_PORT_SYNC_INT;
#endif
	ptp_tx_intr_enable(ptp);
	ptp->ops->release(ptp);

	ts = ktime_to_timespec64(ktime_get_real());
	t.sec = ts.tv_sec;
	t.nsec = ts.tv_nsec;

	/* Adjust for leap seconds. */
	t.sec += ptp->utc_offset;
	ptp->ops->acquire(ptp);
	set_ptp_time(ptp, &t);
	ptp->cur_time = t;
	ptp->ops->release(ptp);

	prepare_pps(ptp);
	ptp->started = true;
}  /* ptp_start */

static void save_msg_info(struct ptp_info *ptp, struct ptp_msg_info *info,
	struct ptp_msg_hdr *hdr, u32 port, u32 timestamp)
{
	struct ptp_msg_options *data = &info->data;

	memcpy(&data->id, &hdr->sourcePortIdentity,
		sizeof(struct ptp_port_identity));
	data->seqid = hdr->sequenceId;
	data->domain = hdr->domainNumber;
	data->port = port;
	data->ts.timestamp = timestamp;
	update_ts(&data->ts, ptp->cur_time.sec);
	info->sec = ptp->sec_lo;
}  /* save_msg_info */

static void exit_msg_info(struct ptp_msg_info info[])
{
	struct ptp_msg_info *msg;
	struct ptp_msg_info *prev;
	int msg_type;

	for (msg_type = SYNC_MSG; msg_type <= MANAGEMENT_MSG; msg_type++) {
		prev = &info[msg_type];
		msg = prev->next;
		while (msg) {
			prev->next = msg->next;
			kfree(msg);
			msg = prev->next;
		}
		info[msg_type].data.port = 0;
	}
}  /* exit_msg_info */

static void init_msg_info(struct ptp_msg_info info[], spinlock_t *lock)
{
	int msg_type;

	spin_lock_init(lock);
	for (msg_type = SYNC_MSG; msg_type <= MANAGEMENT_MSG; msg_type++) {
		info[msg_type].data.port = 0;
		info[msg_type].next = NULL;
	}
}  /* init_msg_info */

static void check_expired_msg(struct ptp_info *ptp, struct ptp_msg_info info[],
	spinlock_t *lock, int *cnt)
{
	struct ptp_msg_info *msg;
	struct ptp_msg_info *prev;
	int msg_type;
	int diff;
	unsigned long flags;

	spin_lock_irqsave(lock, flags);
	for (msg_type = SYNC_MSG; msg_type <= MANAGEMENT_MSG; msg_type++) {
		prev = &info[msg_type];
		msg = prev->next;
		while (msg) {
			diff = abs(ptp->sec_lo - msg->sec);
			if (diff >= 4) {
				if (cnt && *cnt > 0)
					(*cnt)--;
				prev->next = msg->next;
				kfree(msg);
				msg = prev;
			}
			prev = msg;
			msg = msg->next;
		}
	}
	spin_unlock_irqrestore(lock, flags);
}  /* check_expired_msg */

static int find_msg_info(struct ptp_msg_info *msg_info, spinlock_t *lock,
	struct ptp_msg_hdr *hdr, struct ptp_port_identity *id, int remove,
	struct ptp_msg_options *info)
{
	struct ptp_msg_info *rx_msg = msg_info;
	struct ptp_msg_info *prev;
	struct ptp_msg_options *data;
	int ret = false;
	unsigned long flags;

	spin_lock_irqsave(lock, flags);
	prev = rx_msg;
	rx_msg = rx_msg->next;
	while (rx_msg) {
		data = &rx_msg->data;
		if (!memcmp(&data->id, id, sizeof(struct ptp_port_identity))
				&& data->seqid == hdr->sequenceId &&
				data->domain == hdr->domainNumber) {
			info->port = data->port;
			info->ts = data->ts;
			if (remove) {
				prev->next = rx_msg->next;
				kfree(rx_msg);
			}
			ret = true;
			break;
		}
		prev = rx_msg;
		rx_msg = rx_msg->next;
	}
	spin_unlock_irqrestore(lock, flags);
	return ret;
}  /* find_msg_info */

static int ptp_stop(struct ptp_info *ptp, int hw_access)
{
	flush_work(&ptp->adj_clk);
	flush_work(&ptp->set_latency);
	cancel_delayed_work_sync(&ptp->check_pps);
	cancel_delayed_work_sync(&ptp->update_sec);
	flush_workqueue(ptp->access);
	ptp->update_sec_jiffies = 0;
	exit_msg_info(ptp->rx_msg_info);
	exit_msg_info(ptp->tx_msg_info);

	/* S2 chip can be reset. */
	ptp->ptp_synt = false;

	/* Stop processing PTP interrupts. */
	ptp->started = false;
	ptp->first_drift = ptp->drift = 0;
	ptp->tx_intr = 0;

	/* Stop triggered outputs and timestamp inputs. */
	if (hw_access) {
		ptp->ops->acquire(ptp);
		ptp_hw_disable(ptp);
		ptp_tx_intr_enable(ptp);
		ptp->ops->release(ptp);
	}

#ifdef DEBUG_MSG
	dbg_print_work(&db.dbg_print);
#endif
	return false;
}  /* ptp_stop */

static struct file_dev_info *find_minor_dev(struct file_dev_info *info)
{
	struct ptp_info *ptp = info->dev;
	struct file_dev_info *dev;
	struct file_dev_info *prev;

	dev = ptp->dev[info->minor ^ 1];
	prev = ptp->dev[info->minor];
	while (prev != info && prev && dev) {
		prev = prev->next;
		dev = dev->next;
	}
	if (prev != info)
		dev = NULL;
	return dev;
}  /* find_minor_dev */

static void ptp_init_state(struct ptp_info *ptp)
{
	struct ptp_utime t;
	struct ptp_msg_info *tx_msg;

	if (ptp->op_state) {
		ptp->op_state++;
		return;
	}
	mutex_lock(&ptp->lock);
	tx_msg = &ptp->tx_msg_info[7];
	tx_msg->data.port = 0;
	tx_msg->data.ts.timestamp = 0;
	ptp->tx_msg_cnt = 0;
	ptp->overrides &= ~PTP_USE_DEFAULT_PORT;
	mutex_unlock(&ptp->lock);

	if (!ptp->started)
		return;
	ptp->reg->start(ptp, false);

	ptp_init_hw(ptp);

	ptp->ops->acquire(ptp);
	ptp->adjust_offset = 0;
	ptp->offset_changed = 0;
	memset(&ptp->last_rx_ts, 0, sizeof(struct ptp_ts));
	memset(&ptp->last_tx_ts, 0, sizeof(struct ptp_ts));

#ifdef DBG_MSG_DROP
	memset(ptp->seqid_sync, 0, sizeof(u16) * MAX_PTP_PORT);
	memset(ptp->seqid_fup, 0, sizeof(u16) * MAX_PTP_PORT);
	memset(ptp->seqid_pdelay_req, 0, sizeof(u16) * MAX_PTP_PORT);
	memset(ptp->seqid_pdelay_resp, 0, sizeof(u16) * MAX_PTP_PORT);
	memset(ptp->seqid_pdelay_resp_fup, 0, sizeof(u16) * MAX_PTP_PORT);
#endif

	if (!ptp->ptp_synt) {
		syntonize_clk(ptp);
		ptp->ptp_synt = true;
	}
	ptp->reg->get_time(ptp, &t);
	ptp->cur_time = t;
	ptp->op_state = 1;

	/* Do not try to adjust drift automatically. */
	if (!ptp->first_drift)
		ptp->first_drift = 1;
	ptp->ops->release(ptp);
}  /* ptp_init_state */

#ifdef DBG_PROC_SYNC
static struct ptp_utime last_rcv;
static s64 first_sync;
static s64 first_recv;
#endif

static void ptp_exit_state(struct ptp_info *ptp)
{
	if (ptp->op_state > 1) {
		ptp->op_state--;
		return;
	}
	if (ptp->mode & PTP_MASTER) {
		u16 data;
		struct ksz_sw *sw = ptp->parent;

		ptp->ops->acquire(ptp);
		data = sw->reg->r16(sw, REG_PTP_MSG_CONF1);
		data &= ~PTP_MASTER;
		sw->reg->w16(sw, REG_PTP_MSG_CONF1, data);
		ptp->ops->release(ptp);
		ptp->mode &= ~PTP_MASTER;
		ptp->def_mode &= ~PTP_MASTER;
	}
	ptp->adjust_offset = 0;
	ptp->offset_changed = 0;
	ptp->tx_msg_cnt = 0;
	ptp->overrides &= ~PTP_USE_DEFAULT_PORT;
	ptp->tx_en = ptp->rx_en = 0;
	ptp->tx_en_ports = ptp->rx_en_ports = 0;
	if (ptp->cap & PTP_USE_ONE_STEP)
		ptp->overrides &= ~(PTP_VERIFY_TIMESTAMP |
				    PTP_UPDATE_PDELAY_RESP_TIME);
	ptp->cap = 0;
	ptp->op_mode = 0;
	ptp->op_state = 0;
	ptp->forward = FWD_MAIN_DEV;
#ifdef DBG_PROC_SYNC
	last_rcv.sec = 0;
	first_recv = 0;
	first_sync = 0;
#endif

	/* Indicate drift is not being set by PTP stack. */
	ptp->drift_set = 0;
}  /* ptp_exit_state */

static struct ptp_msg *check_ptp_msg(u8 *data, u16 **udp_check_ptr)
{
	struct ethhdr *eth = (struct ethhdr *) data;
	struct vlan_ethhdr *vlan = (struct vlan_ethhdr *) data;
	struct iphdr *iph = NULL;
	struct ipv6hdr *ip6h = NULL;
	struct udphdr *udp;
	int ipv6;
	struct ptp_msg *msg;

	if (eth->h_proto == htons(0x88F7)) {
		msg = (struct ptp_msg *)(eth + 1);
		goto check_ptp_version;
	}

	if (eth->h_proto == htons(ETH_P_8021Q)) {
		if (vlan->h_vlan_encapsulated_proto == htons(ETH_P_8021Q)) {
			unsigned char *ptr = (unsigned char *) vlan;

			ptr += VLAN_HLEN;
			vlan = (struct vlan_ethhdr *) ptr;
		}
		if (vlan->h_vlan_encapsulated_proto == htons(0x88F7)) {
			msg = (struct ptp_msg *)(vlan + 1);
			goto check_ptp_version;
		}
		ipv6 = vlan->h_vlan_encapsulated_proto == htons(ETH_P_IPV6);
		if (vlan->h_vlan_encapsulated_proto != htons(ETH_P_IP) &&
				!ipv6)
			return NULL;
		ip6h = (struct ipv6hdr *)(vlan + 1);
		iph = (struct iphdr *)(vlan + 1);
	} else {
		ipv6 = eth->h_proto == htons(ETH_P_IPV6);
		if (eth->h_proto != htons(ETH_P_IP) && !ipv6)
			return NULL;
		ip6h = (struct ipv6hdr *)(eth + 1);
		iph = (struct iphdr *)(eth + 1);
	}

	if (ipv6) {
		if (ip6h->nexthdr != IPPROTO_UDP)
			return NULL;

		udp = (struct udphdr *)(ip6h + 1);
		if (udp_check_ptr)
			*udp_check_ptr = &udp->check;
	} else {
		if (iph->protocol != IPPROTO_UDP)
			return NULL;
		if (ntohs(iph->frag_off) & IP_OFFSET)
			return NULL;

		udp = (struct udphdr *)(iph + 1);
		if (udp_check_ptr)
			*udp_check_ptr = &udp->check;
	}

	if (udp->dest != htons(319) && udp->dest != htons(320))
		return NULL;

	msg = (struct ptp_msg *)(udp + 1);

check_ptp_version:
	if (msg->hdr.versionPTP >= 2)
		return msg;
	return NULL;
}  /* check_ptp_msg */

static struct ptp_msg *check_ptp_event(u8 *data)
{
	struct ptp_msg *msg;

	msg = check_ptp_msg(data, NULL);
	if (!msg)
		return NULL;
	switch (msg->hdr.messageType) {
	case SYNC_MSG:
		break;
	case DELAY_REQ_MSG:
		break;
	case PDELAY_REQ_MSG:
		break;
	case PDELAY_RESP_MSG:
		break;
	default:
		msg = NULL;
		break;
	}
	return msg;
}

/**
 * update_ptp_msg - Update PTP message
 * @data:	The PTP frame data.
 * @port:	Buffer to hold the tx port, or hoding the rx port.
 * @timestamp:	Buffer to hold the tx timestamp, or holding the rx timestamp.
 * @overrides:	Parameter to do something with the reserved fields.
 *
 * This function serves two purposes so that driver code is compatible to the
 * PTP stack using the first generation PTP operation behavior.
 * The PTP header reserved fieids were used to store the port and timestamp.
 * When receiving and if necessary those field are filled with the rx port
 * and timestamp so that old PTP stack can retrieve those information.
 * When transmiting the tx port and timestamp are retrieved before those fields
 * are filled with zero.
 */
static struct ptp_msg *update_ptp_msg(u8 *data, u8 *port, u32 *timestamp,
	u32 overrides)
{
	struct ptp_msg *msg;
	u16 *udp_check_loc = NULL;
	int udp_check = 0;

	msg = check_ptp_msg(data, &udp_check_loc);
	if (!msg)
		return NULL;
	if (msg->hdr.reserved2 != *port) {
		u8 data = msg->hdr.reserved2;

		/*
		 * Hardware automatically updates the port number to the
		 * actual port sending the Pdelay_Req message.
		 */
		if ((overrides & PTP_UPDATE_PDELAY_RESP_PORT) &&
		    PDELAY_RESP_MSG == msg->hdr.messageType) {
			u16 reply = ntohs(msg->data.pdelay_resp.
				requestingPortIdentity.port);

			if (reply - 1 == *port) {
				udp_check += reply;
				msg->data.pdelay_resp.requestingPortIdentity.
					port = htons(*port);
				udp_check -= *port;
			}
		}
		if (overrides & PTP_ZERO_RESERVED_FIELD) {
			udp_check += data;
			msg->hdr.reserved2 = *port;
			udp_check -= *port;
		}
		*port = data;
	}
	if (msg->hdr.reserved3 != htonl(*timestamp)) {
		u32 tmp = ntohl(msg->hdr.reserved3);

		if (overrides & PTP_ZERO_RESERVED_FIELD) {
			int i;
			u16 *data = (u16 *) &msg->hdr.reserved3;

			for (i = 0; i < 2; i++)
				udp_check += ntohs(data[i]);
			msg->hdr.reserved3 = htonl(*timestamp);
			for (i = 0; i < 2; i++)
				udp_check -= ntohs(data[i]);
		}
		*timestamp = tmp;
	}
	if ((overrides & PTP_VERIFY_TIMESTAMP) &&
			PDELAY_RESP_MSG == msg->hdr.messageType &&
			msg->hdr.flagField.flag.twoStepFlag) {
		struct ptp_utime rx;

		rx.nsec = ntohl(msg->data.pdelay_resp.requestReceiptTimestamp.
			nsec);
		rx.sec = ntohl(msg->data.pdelay_resp.requestReceiptTimestamp.
			sec.lo);
		*timestamp = (rx.sec << 30) | rx.nsec;
	}
	if (udp_check && udp_check_loc) {
		u16 check;

		check = ntohs(*udp_check_loc);
		udp_check += check;
		udp_check = (udp_check >> 16) + (udp_check & 0xffff);
		udp_check += (udp_check >> 16);
		check = (u16) udp_check;
		if (!check)
			check = -1;
		*udp_check_loc = htons(check);
	}
	return msg;
}  /* update_ptp_msg */

static void get_rx_tstamp(void *ptr, struct sk_buff *skb)
{
	struct ptp_info *ptp = ptr;
	struct ptp_msg *msg;
	struct ptp_msg_options *rx_msg;
	struct ptp_ts ts;
	u64 ns;
	struct skb_shared_hwtstamps *shhwtstamps = skb_hwtstamps(skb);

	if (!shhwtstamps)
		return;

	/* Received PTP messages are saved in database. */
	if (ptp->op_mode > 1) {

		/* Use previously parsed PTP message if available. */
		msg = ptp->rx_msg;
		if (!msg)
			msg = check_ptp_msg(skb->data, NULL);
		if (!msg || msg->hdr.messageType & 0x8)
			return;
	}

	rx_msg = &ptp->rx_msg_info[7].data;
	ts = rx_msg->ts;

	ns = (u64) ts.t.sec * NANOSEC_IN_SEC + ts.t.nsec;
	memset(shhwtstamps, 0, sizeof(*shhwtstamps));
	shhwtstamps->hwtstamp = ns_to_ktime(ns);
}  /* get_rx_tstamp */

static void get_tx_tstamp(struct ptp_info *ptp, struct sk_buff *skb)
{
	struct ksz_sw *sw = ptp->parent;
	int cnt;
	uint m;
	uint n;
	uint p;
	struct ptp_msg *msg;
	u32 ports;
	u32 intr;
	bool dest;
	struct ptp_tx_ts *tx;
	struct ptp_tx_ts *xtx;
	struct sk_buff *orig_skb = skb;

	if (ptp->tx_msg_parsed)
		msg = ptp->tx_msg;
	else
		msg = check_ptp_msg(skb->data, NULL);
	ptp->tx_msg_parsed = false;
	if (!msg || msg->hdr.messageType & 0x8)
		return;

	dest = false;
	if (ptp->tx_ports & sw->PORT_MASK)
		dest = true;
	m = sw->PORT_MASK & ~sw->HOST_MASK;
	if (!dest)
		ports = m;
	else
		ports = ptp->tx_ports & m;
	if (SYNC_MSG == msg->hdr.messageType) {
		xtx = ptp->tx_sync;
		intr = PTP_PORT_SYNC_INT;
	} else if (PDELAY_RESP_MSG == msg->hdr.messageType) {
		xtx = ptp->tx_resp;
		intr = PTP_PORT_PDELAY_RESP_INT;
	} else {
		xtx = ptp->tx_dreq;
		intr = PTP_PORT_XDELAY_REQ_INT;
	}
	if (!(ptp->tx_intr & intr))
		return;

	/* Only accept socket buffer from application. */
	if (!orig_skb->sk)
		return;
	cnt = 0;
	for (n = 1; n <= ptp->ports; n++) {
		p = get_phy_port(sw, n);
		if (!(ports & (1 << p)))
			continue;
		tx = &xtx[p];
		if (tx->skb) {
			dev_kfree_skb_irq(tx->skb);
			tx->skb = NULL;
		}
		if (!cnt) {
			skb = skb_clone_sk(orig_skb);
			if (!skb)
				break;
		}

		/* Need to create socket buffer for more than 1 port. */
		if (cnt++) {
			skb = skb_copy(orig_skb, GFP_ATOMIC);
			if (!skb)
				break;
			skb->sk = orig_skb->sk;
			msg = check_ptp_event(skb->data);
		}
		tx->skb = skb;
		tx->msg = msg;
		skb_shinfo(skb)->tx_flags |= SKBTX_IN_PROGRESS;
	}
}  /* get_tx_tstamp */

static int ptp_hwtstamp_ioctl(struct ptp_info *ptp, struct ifreq *ifr,
			      u16 ports)
{
	struct hwtstamp_config config;

	if (copy_from_user(&config, ifr->ifr_data, sizeof(config)))
		return -EFAULT;

	/* reserved for future extensions */
	if (config.flags)
		return -EINVAL;

	switch (config.tx_type) {
	case HWTSTAMP_TX_OFF:
		ptp->tx_en_ports &= ~ports;
		if (!ptp->tx_en_ports)
			ptp->tx_en &= ~1;
		break;
	case HWTSTAMP_TX_ONESTEP_SYNC:
	case HWTSTAMP_TX_ON:
		ptp->tx_en_ports |= ports;
		ptp->tx_en |= 1;
		break;
	default:
		return -ERANGE;
	}

	switch (config.rx_filter) {
	case HWTSTAMP_FILTER_NONE:
		if (!ptp->cap && (ptp->rx_en & 1) && (ptp->rx_en & (1 << 8))) {
			ptp->tx_en &= ~(1 << 8);
			ptp->rx_en &= ~(1 << 8);
		}
		ptp->rx_en_ports &= ~ports;
		if (!ptp->rx_en_ports)
			ptp->rx_en &= ~1;
		break;
	case HWTSTAMP_FILTER_ALL:
#if 0
		ptp->rx_en |= 1;
		break;
#endif
	default:
		if (!ptp->cap && !(ptp->rx_en & 1) && (ptp->tx_en & 1)) {
			ptp->tx_en |= (1 << 8);
			ptp->rx_en |= (1 << 8);
		}
		ptp->rx_en_ports |= ports;
		ptp->rx_en |= 1;
		break;
	}

	return copy_to_user(ifr->ifr_data, &config, sizeof(config)) ?
		-EFAULT : 0;
}

static int ptp_chk_rx_msg(struct ptp_info *ptp, u8 *data, uint port)
{
	struct ptp_msg *msg;
	struct ksz_sw *sw = ptp->parent;

	/* Use previously parsed PTP message if available. */
	msg = ptp->rx_msg;
	if (!msg)
		msg = check_ptp_msg(data, NULL);
	if (!msg)
		return false;
	ptp->rx_msg = msg;

	if ((sw->features & USE_802_1X_AUTH) &&
	    !(sw->on_ports & (1 << port))) {
		return true;
	}
	return false;
}  /* ptp_chk_rx_msg */

static int ptp_drop_pkt(struct ptp_info *ptp, struct sk_buff *skb, u32 vlan_id,
	int *tag, int *ptp_tag, int *forward)
{
	struct ksz_sw *sw = ptp->parent;

	/* Not PTP message. */
	if (!get_rx_tag_ptp(&sw->tag))
		return false;
	do {
		u16 vid;
		u16 *protocol;

		if (!(ptp->vid))
			break;
		if (vlan_get_tag(skb, &vid))
			break;
		vid &= VLAN_VID_MASK;
		protocol = (u16 *) &skb->data[VLAN_ETH_HLEN - 2];

		if (!vid)
			break;
		if (*protocol == ntohs(0x88F7) && vid != ptp->vid)
			return true;
	} while (0);
	*ptp_tag = get_rx_tag_ports(&sw->tag);
	ptp->ops->get_rx_info(ptp, skb->data, *ptp_tag, sw->tag.timestamp);
	*forward = ptp->forward;
	if (!ptp->op_state && !(ptp->rx_en & 1)) {
		*ptp_tag = 0;
		return false;
	}
	if (ptp_chk_rx_msg(ptp, skb->data, *ptp_tag))
		return true;
	if (ptp->rx_en & 1)
		ptp->ops->get_rx_tstamp(ptp, skb);
	(*ptp_tag)++;
	return false;
}  /* ptp_drop_pkt */

static void set_msg_info(struct ptp_info *ptp, struct ptp_msg_hdr *hdr,
	u32 port, u32 timestamp)
{
	struct ptp_msg_info *tx_msg;
	struct ptp_msg_info *info;

	tx_msg = &ptp->tx_msg_info[hdr->messageType];
	info = kzalloc(sizeof(struct ptp_msg_info), GFP_KERNEL);
	if (info) {
		unsigned long flags;

		spin_lock_irqsave(&ptp->tx_msg_lock, flags);
		save_msg_info(ptp, info, hdr, port, timestamp);
		info->next = tx_msg->next;
		tx_msg->next = info;
		if (ptp->tx_msg_cnt >= 0)
			ptp->tx_msg_cnt++;
		spin_unlock_irqrestore(&ptp->tx_msg_lock, flags);
	}
}  /* set_msg_info */

static int proc_ptp_hw_access(struct ptp_info *ptp, int cmd, int subcmd,
	int option, void *data, size_t len, struct file_dev_info *info,
	int *output, int wait);

#ifdef DBG_PROC_SYNC
static void handle_sync(struct ptp_info *ptp, struct ptp_msg *msg)
{
	struct ptp_utime recv;
	struct ptp_utime sync;
	struct ksz_ptp_time drift;
	struct ksz_ptp_time interval;
	struct ksz_ptp_time offset;
	s64 corr;
	u64 nsec;
	s64 drift_per_sec;
	s64 avg;
	s64 cur_recv;
	s64 cur_sync;
static s64 sync_corr;
static struct ptp_ts ts;
static struct ptp_utime last_sync;
static struct ksz_ptp_time last_offset;

	sync.sec = sync.nsec = 0;
	if (SYNC_MSG == msg->hdr.messageType) {
		struct ptp_msg_info *rx_msg;

		rx_msg = &ptp->rx_msg_info[7];
		ts = rx_msg->data.ts;

		corr = htonl(msg->hdr.correctionField.scaled_nsec_hi);
		corr <<= 32;
		corr |= htonl(msg->hdr.correctionField.scaled_nsec_lo);
		corr >>= 16;
		sync_corr = corr;

		/* This is one-step Sync. */
		if (!msg->hdr.flagField.flag.twoStepFlag) {
			sync.sec = ntohl(msg->data.sync.
				originTimestamp.sec.lo);
			sync.nsec = ntohl(msg->data.sync.
				originTimestamp.nsec);
		}
	} else if (FOLLOW_UP_MSG == msg->hdr.messageType) {
		corr = htonl(msg->hdr.correctionField.scaled_nsec_hi);
		corr <<= 32;
		corr |= htonl(msg->hdr.correctionField.scaled_nsec_lo);
		corr >>= 16;
		sync_corr += corr;
		sync.sec = ntohl(msg->data.follow_up.
			preciseOriginTimestamp.sec.lo);
		sync.nsec = ntohl(msg->data.follow_up.
			preciseOriginTimestamp.nsec);
	}

	/* Sync transmit timestamp not received. */
	if (!sync.sec)
		return;
	if (sync_corr) {
		s32 rem;

		corr = ts.t.sec;
		corr *= NANOSEC_IN_SEC;
		corr += ts.t.nsec;
		corr -= sync_corr;
		corr = div_s64_s32_rem(corr, NANOSEC_IN_SEC, &rem);
		ts.t.sec = (u32) corr;
		ts.t.nsec = rem;
	}
#if 0
	ts.t.nsec += 5;
	ts.t.nsec /= 10;
	ts.t.nsec *= 10;
	sync.nsec += 5;
	sync.nsec /= 10;
	sync.nsec *= 10;
#endif
	calc_udiff(&sync, &ts.t, &offset);
	cur_recv = cur_sync = avg = 0;
	if (first_sync) {
		nsec = sync.sec;
		nsec *= NANOSEC_IN_SEC;
		nsec += sync.nsec;
		cur_sync = nsec;
		nsec = ts.t.sec;
		nsec *= NANOSEC_IN_SEC;
		nsec += ts.t.nsec;
		cur_recv = nsec;
		cur_sync -= first_sync;
		cur_recv -= first_recv;
		cur_recv -= cur_sync;
		cur_recv = abs(cur_recv);
		cur_recv *= NANOSEC_IN_SEC;
	} else {
		nsec = sync.sec;
		nsec *= NANOSEC_IN_SEC;
		nsec += sync.nsec;
		first_sync = nsec;
		nsec = ts.t.sec;
		nsec *= NANOSEC_IN_SEC;
		nsec += ts.t.nsec;
		first_recv = nsec;
	}
	nsec = 0;
	drift_per_sec = 0;
	if (last_rcv.sec) {
		calc_udiff(&last_sync, &sync, &interval);
		calc_diff(&last_offset, &offset, &drift);
		nsec = interval.sec;
		nsec *= NANOSEC_IN_SEC;
		nsec += interval.nsec;
		drift_per_sec = abs(drift.sec);
		drift_per_sec *= NANOSEC_IN_SEC;
		drift_per_sec += abs(drift.nsec);
		drift_per_sec *= NANOSEC_IN_SEC;
		drift_per_sec = div_s64_s64(drift_per_sec, nsec);
		avg = div_s64_s64(cur_recv, cur_sync);
	}
	if (sync_corr) {
		cur_recv = avg * nsec;
		cur_recv = div_s64_u32(cur_recv, NANOSEC_IN_SEC);
		cur_recv += nsec;
		corr = last_rcv.sec;
		corr *= NANOSEC_IN_SEC;
		corr += last_rcv.nsec;
		cur_recv += corr;
		corr = recv.sec;
		corr *= NANOSEC_IN_SEC;
		corr += recv.nsec;
		corr -= cur_recv;
printk(" corr: %lld %lld %lld"NL, sync_corr, corr, corr - sync_corr);
		sync_corr = 0;
	}
dbg_msg("sync: %x:%9u %x:%9u p:%10lld d:%lld a:%lld %lld"NL,
ts.t.sec, ts.t.nsec,
sync.sec, sync.nsec, nsec, drift_per_sec, avg, drift_per_sec - avg);
dbg_msg("o: %d"NL, offset.nsec);
#if 0
	if (nsec && nsec < 5000000000) {
		struct ptp_clk_options clk_opt;
		int drift_set;
		int output;
		int err;

		output = 1;
		clk_opt.sec = clk_opt.nsec = 0;

		drift_set = (int) drift_per_sec;
		if (drift_set < 5 && abs(offset.nsec) > 1000) {
			clk_opt.sec = offset.sec;
			clk_opt.nsec = offset.nsec;
			if (offset.nsec < 0)
				output = 2;
			last_rcv.sec = 0;
			ts.t.sec = 0;
			first_recv = 0;
			first_sync = 0;
		}

		if (drift.nsec < 0)
			drift_set = -drift_set;
		drift_set += ptp->drift;

		clk_opt.drift = drift_set;
		clk_opt.interval = NANOSEC_IN_SEC;
		err = proc_ptp_hw_access(ptp,
			DEV_CMD_PUT, DEV_PTP_CLK, output,
			&clk_opt, sizeof(clk_opt), NULL, &output,
			false);
	}
#endif
	last_sync = sync;
	last_rcv = ts.t;
	last_offset = offset;
}  /* handle_sync */
#endif

static struct ptp_msg *ptp_set_rx_info(struct ptp_info *ptp, u8 *data, u8 port,
	u32 timestamp)
{
	struct ptp_msg *msg;
#ifdef DBG_MSG_DROP
	u16 *seqid;
#endif
	u32 overrides = ptp->overrides;

#ifndef DBG_MSG_DROP
	/* Do not need to parse PTP message. */
	if (1 == ptp->op_mode)
		return NULL;
#endif

	/* Set receive port and timestamp inside the PTP message. */
	if (0 == ptp->op_mode && ptp->op_state) {
		overrides |= PTP_ZERO_RESERVED_FIELD;
		overrides |= PTP_UPDATE_PDELAY_RESP_PORT;
	} else
		overrides &= ~PTP_ZERO_RESERVED_FIELD;
	msg = update_ptp_msg(data, &port, &timestamp, overrides);

#ifdef DBG_PROC_SYNC
	if (ptp->overrides & PTP_CHECK_SYNC_TIME)
		handle_sync(ptp, msg);
#endif
#ifdef DBG_MSG_DROP
	switch (msg->hdr.messageType) {
	case SYNC_MSG:
		seqid = &ptp->seqid_sync[port];
		break;
	case FOLLOW_UP_MSG:
		seqid = &ptp->seqid_fup[port];
		break;
	case PDELAY_REQ_MSG:
		seqid = &ptp->seqid_pdelay_req[port];
		break;
	case PDELAY_RESP_MSG:
		seqid = &ptp->seqid_pdelay_resp[port];
		break;
	case PDELAY_RESP_FOLLOW_UP_MSG:
		seqid = &ptp->seqid_pdelay_resp_fup[port];
		break;
	default:
		seqid = NULL;
		break;
	}
	if (seqid) {
		if (((*seqid + 1) & 0xffff) != ntohs(msg->hdr.sequenceId) &&
		    *seqid)
			printk(KERN_INFO " %d=%x:%04x %04x"NL, port,
			       msg->hdr.messageType, *seqid,
			       ntohs(msg->hdr.sequenceId));
		*seqid = ntohs(msg->hdr.sequenceId);
	}
#endif

	/* Do not need to save PTP messages. */
	if (ptp->op_mode <= 1)
		msg = NULL;
	return msg;
}  /* ptp_set_rx_info */

#if 1
/* Used for 802.1BA test tool to accept Announce messages. */
static int ba_hack;
#endif

static struct ptp_msg *ptp_get_tx_info(struct ptp_info *ptp, u8 *data,
	u32 *tx_port, u32 *tx_timestamp)
{
	struct ptp_msg *msg;
	u32 overrides = ptp->overrides;
	u32 timestamp = 0;
	u8 port = 0;

	/* Need to know about PTP message for queue assignment. */
#if 0
#if 1
	if (!ba_hack)
#endif
	if ((1 == ptp->op_mode || 2 == ptp->op_mode) && !ptp->tx_msg_cnt) {
		/*
		 * This packet is not parsed and will be checked again if
		 * necessary.
		 */
		ptp->tx_msg_parsed = false;
		return NULL;
	}
#endif

	/* Get receive port and timestamp inside the PTP message. */
	if (0 == ptp->op_mode)
		overrides |= PTP_ZERO_RESERVED_FIELD;
	msg = update_ptp_msg(data, &port, &timestamp, overrides);
	if (msg) {
		/* Get transmit port and timestamp inside the PTP message. */
		if (0 == ptp->op_mode) {
			if (port)
				*tx_port = port;
			if (timestamp)
				*tx_timestamp = timestamp;
		}

		/* Simulate passing transmit information from application. */
		if (ptp->overrides & PTP_TEST_TX_INFO) {
			u32 tx_ports = 0;

			if (port)
				tx_ports = port;
			set_msg_info(ptp, &msg->hdr, tx_ports, timestamp);
		}
	}
	return msg;
}  /* ptp_get_tx_info */

static void ptp_get_rx_info(struct ptp_info *ptp, u8 *data, u8 port,
	u32 timestamp)
{
	int index;
	struct ptp_msg *msg;
	struct ptp_msg_info *rx_msg;
	struct ptp_msg_info *info = NULL;

	/* Indicate PTP message is not parsed yet. */
	ptp->rx_msg = NULL;

	/* Entry is not used for PTP message. */
	rx_msg = &ptp->rx_msg_info[7];
	rx_msg->data.port = port;
	rx_msg->data.ts.timestamp = timestamp;
	update_ts(&rx_msg->data.ts, ptp->cur_time.sec);

	index = get_speed_index(ptp, port);
	sub_nsec(&rx_msg->data.ts.t, ptp->rx_latency[port][index]);
	timestamp = (rx_msg->data.ts.t.sec << 30) | rx_msg->data.ts.t.nsec;
	if (ptp->overrides & PTP_CHECK_PATH_DELAY) {
		if (ptp->last_tx_ts.t.sec) {
			struct ksz_ptp_time diff;

			calc_udiff(&ptp->last_tx_ts.t, &rx_msg->data.ts.t,
				&diff);
			dbg_msg("pd: %d"NL, diff.nsec);
		} else
			ptp->last_rx_ts = rx_msg->data.ts;
	}
#if 0
	if (ptp->overrides & PTP_CHECK_SYNC_TIME)
dbg_msg(" %x; %08x; %x:%09u"NL, ptp->cur_time.sec, timestamp,
rx_msg->data.ts.t.sec, rx_msg->data.ts.t.nsec);
#endif

	msg = ptp_set_rx_info(ptp, data, port, timestamp);
	if (!msg)
		return;

	/* Indicate PTP message is parsed. */
	ptp->rx_msg = msg;

	rx_msg = &ptp->rx_msg_info[msg->hdr.messageType];
	switch (msg->hdr.messageType) {
	case SYNC_MSG:
		if (!memcmp(&msg->hdr.sourcePortIdentity, &ptp->masterIdentity,
		    sizeof(struct ptp_clock_identity))) {
			rx_msg->data.port = port;
			rx_msg->data.ts.timestamp = timestamp;
		}
		info = kzalloc(sizeof(struct ptp_msg_info), GFP_KERNEL);
		break;

	/* General messages that do not need tracking. */
	case DELAY_RESP_MSG:
	case ANNOUNCE_MSG:
	case SIGNALING_MSG:
	case PDELAY_RESP_FOLLOW_UP_MSG:
		break;
	case MANAGEMENT_MSG:
	{
		u8 action = msg->data.management.b.actionField;

		/* No need to track management response message. */
		if (MANAGEMENT_RESPONSE == action ||
				MANAGEMENT_ACKNOWLEDGE == action)
			break;
	}

	/* fallthrough */
	default:
		info = kzalloc(sizeof(struct ptp_msg_info), GFP_KERNEL);
		break;
	}
	if (info) {
		unsigned long flags;

		spin_lock_irqsave(&ptp->rx_msg_lock, flags);
		save_msg_info(ptp, info, &msg->hdr, port, timestamp);
		info->next = rx_msg->next;
		rx_msg->next = info;
		spin_unlock_irqrestore(&ptp->rx_msg_lock, flags);
	}
}  /* ptp_get_rx_info */

static void ptp_set_tx_info(struct ptp_info *ptp, u8 *data, void *ptr)
{
	struct ksz_sw *sw = ptp->parent;
	int found;
	bool dest;
	bool prio;
	struct ptp_msg *msg;
	struct ptp_msg_options tx_msg;
	struct ksz_sw_tx_tag *tag = ptr;

	tx_msg.port = 0;
	tx_msg.ts.timestamp = 0;

	/* Assume packet will be parsed to determine PTP message type. */
	ptp->tx_msg_parsed = true;
	ptp->tx_msg = ptp_get_tx_info(ptp, data, &tx_msg.port,
		&tx_msg.ts.timestamp);
	dest = false;
	if (get_tx_tag_ports(sw, tag))
		dest = true;
	prio = dest;
	if (!ptp->tx_msg) {

		/* Block PTP messages for blocked ports. */
		if ((sw->features & USE_802_1X_AUTH) && !dest) {
			if (!ptp->tx_msg_parsed) {
				ptp->tx_msg = check_ptp_msg(data, NULL);
				ptp->tx_msg_parsed = true;
			}
			if (ptp->tx_msg)
				set_tx_tag_ports(tag, sw->on_ports);
		}

		/* Remember transmit ports for transmit timestamp report. */
		ptp->tx_ports = get_tx_tag_ports(sw, tag);
		return;
	}
	msg = ptp->tx_msg;

	/* Check whether application sets transmit information using API. */
	found = find_msg_info(&ptp->tx_msg_info[msg->hdr.messageType],
		&ptp->tx_msg_lock, &msg->hdr, &msg->hdr.sourcePortIdentity,
		true, &tx_msg);
	if (found) {
		uint port;
		u32 bits;
		struct ptp_tx_ts *tx = NULL;

		port = 0;
		if (tx_msg.port)
			bits = tx_msg.port;
		else
			bits = get_tx_tag_ports(sw, tag);
		bits &= sw->PORT_MASK;
		while (bits) {
			if ((bits & 1) && bits != 1) {
				port = 0;
				break;
			}
			++port;
			bits >>= 1;
		}
		switch (msg->hdr.messageType) {
		case SYNC_MSG:
			if (port)
				tx = &ptp->tx_sync[port - 1];
			break;
		case DELAY_REQ_MSG:
			if (port)
				tx = &ptp->tx_dreq[port - 1];
			break;
		case PDELAY_REQ_MSG:
			if (port)
				tx = &ptp->tx_dreq[port - 1];
			break;
		case PDELAY_RESP_MSG:
			if (port) {
				tx = &ptp->tx_resp[port - 1];
				if ((ptp->overrides &
				    PTP_UPDATE_PDELAY_RESP_TIME) &&
				    msg->hdr.flagField.flag.twoStepFlag)
					ptp->pdelay_resp_timestamp[port - 1] =
						tx_msg.ts.timestamp;
			}
			break;
		default:
			tx = NULL;
		}
		if (tx) {
			tx->ts.timestamp = 0;
			tx->req_time = 0;
			tx->hdr.messageType = 7;
		}
		found = 2;
		if (ptp->tx_msg_cnt > 0)
			ptp->tx_msg_cnt--;
	}

	/* Check whether a default port is set.  Only used in testing. */
	if (!found && (ptp->overrides & PTP_USE_DEFAULT_PORT)) {
		tx_msg.port = ptp->tx_msg_info[7].data.port;
		tx_msg.ts.timestamp = ptp->tx_msg_info[7].data.ts.timestamp;
		found = 2;
	}

	/* Only PDELAY_RESP_MSG requires timestamp in transmission. */
	if (!found && PDELAY_RESP_MSG == msg->hdr.messageType) {
		int two_step = msg->hdr.flagField.flag.twoStepFlag;
		struct ptp_msg_pdelay_resp *resp = &msg->data.pdelay_resp;

		found = find_msg_info(&ptp->rx_msg_info[PDELAY_REQ_MSG],
			&ptp->rx_msg_lock, &msg->hdr,
			&resp->requestingPortIdentity, !two_step, &tx_msg);

		/* Need to specify timestamp in 1-step mode. */
		if (!two_step && found) {
			struct ptp_ts ts;

			/* Calculate timestamp automatically. */
			ts = tx_msg.ts;
			tx_msg.ts.timestamp = (ts.t.sec << 30) | ts.t.nsec;
		}
	}
	if (ba_hack) {
		if (msg->hdr.messageType == ANNOUNCE_MSG &&
		    memcmp(&data[6], sw->info->mac_addr, ETH_ALEN))
			memcpy(&data[6], sw->info->mac_addr, ETH_ALEN);
	}

	tag->timestamp = tx_msg.ts.timestamp;

	/* Specific ports are specified. */
	if (dest)
		goto set_tx_info_done;

	/* No need to set outgoing port for unicast message. */
	if (msg->hdr.flagField.flag.unicastFlag && !(data[0] & 1))
		goto set_tx_info_done;

	if (found || tx_msg.port) {
		if (tx_msg.port) {
			uint ports;

			if (1 == found)
				ports = (1 << tx_msg.port);
			else
				ports = tx_msg.port;
			if (ports)
				prio = true;
			set_tx_tag_ports(tag, ports);
		}
		goto set_tx_info_done;
	} else if (ptp->op_mode != 3)
		goto set_tx_info_done;

	/* Automatically find a port to send. */
	switch (msg->hdr.messageType) {
	case DELAY_REQ_MSG:
		if (ptp->rx_msg_info[SYNC_MSG].data.ts.timestamp) {
			tx_msg.port = ptp->rx_msg_info[SYNC_MSG].data.port;
			found = true;
		}
		break;
	case PDELAY_RESP_MSG:
		/* Already determined from previous code. */
		break;
	case PDELAY_RESP_FOLLOW_UP_MSG:
		found = find_msg_info(&ptp->rx_msg_info[PDELAY_REQ_MSG],
			&ptp->rx_msg_lock, &msg->hdr, &msg->data.
			pdelay_resp_follow_up.requestingPortIdentity,
			true, &tx_msg);
		break;
	case DELAY_RESP_MSG:
		found = find_msg_info(&ptp->rx_msg_info[DELAY_REQ_MSG],
			&ptp->rx_msg_lock, &msg->hdr, &msg->data.
			delay_resp.requestingPortIdentity,
			true, &tx_msg);
		break;
	case MANAGEMENT_MSG:
	{
		u8 action = msg->data.management.b.actionField;

		/* Not response to management request message. */
		if (MANAGEMENT_GET == action || MANAGEMENT_SET == action ||
		    MANAGEMENT_COMMAND == action)
			break;

		found = find_msg_info(&ptp->rx_msg_info[MANAGEMENT_MSG],
			&ptp->rx_msg_lock, &msg->hdr, &msg->data.
			management.b.targetPortIdentity,
			true, &tx_msg);
		break;
	}
	default:
		break;
	}

	if (found)
		set_tx_tag_ports(tag, (1 << tx_msg.port));
dbg_msg("  tx m:%x f:%d p:%x"NL, msg->hdr.messageType, found,
get_tx_tag_ports(sw, tag));

set_tx_info_done:
	if ((sw->features & USE_802_1X_AUTH) && !dest) {
		set_tx_tag_ports(tag, sw->on_ports);
	}

	/* Remember transmit ports for transmit timestamp report. */
	ptp->tx_ports = get_tx_tag_ports(sw, tag);

	/* Need destination ports for queue assignment to work. */
	if (prio)
		set_tx_tag_queue(sw, tag, sw->ctrl_queue);

	do {
		uint m;
		uint n;
		uint p;
		u32 ports;
		u32 intr;
		struct ptp_tx_ts *tx;
		struct ptp_tx_ts *xtx;

		/* Not PTP event message. */
		if (msg->hdr.messageType & 0x8)
			break;
		m = sw->PORT_MASK & ~sw->HOST_MASK;
		if (!dest)
			ports = m;
		else
			ports = ptp->tx_ports & m;
		if (SYNC_MSG == msg->hdr.messageType) {
			xtx = ptp->tx_sync;
			intr = PTP_PORT_SYNC_INT;
		} else if (PDELAY_RESP_MSG == msg->hdr.messageType) {
			xtx = ptp->tx_resp;
			intr = PTP_PORT_PDELAY_RESP_INT;
		} else {
			xtx = ptp->tx_dreq;
			intr = PTP_PORT_XDELAY_REQ_INT;
		}

		/* Transmit timestamps are not retrieved. */
		if (!(ptp->tx_intr & intr))
			break;
		for (n = 1; n <= ptp->ports; n++) {
			p = get_phy_port(sw, n);
			if (!(ports & (1 << p)))
				continue;
			tx = &xtx[p];
			memcpy(&tx->hdr, &msg->hdr,
				sizeof(struct ptp_msg_hdr));

			/* Clear previous timestamp if any exists. */
			tx->ts.timestamp = 0;
		}
	} while (0);
}  /* ptp_set_tx_info */

static void proc_ptp_get_cfg(struct ptp_info *ptp, u8 *data)
{
	struct ptp_cfg_options *cmd = (struct ptp_cfg_options *) data;
	struct ksz_sw *sw = ptp->parent;

	ptp->ops->acquire(ptp);
	ptp->mode = sw->reg->r16(sw, REG_PTP_MSG_CONF1);
	ptp->cfg = sw->reg->r16(sw, REG_PTP_MSG_CONF2);
	ptp->domain = sw->reg->r16(sw, REG_PTP_DOMAIN_VERSION) & PTP_DOMAIN_M;
	cmd->priority = !!sw->ops->chk(sw, REG_PTP_EVENT_PRIO_CTRL,
				       PTP_PRIO_ENABLE);
	ptp->ops->release(ptp);

	/* Check mode in case the switch is reset outside of driver control. */
	if (ptp->mode != ptp->def_mode && ptp->started) {
		dbg_msg("mode mismatched: %04x %04x; %04x %04x"NL,
			ptp->mode, ptp->def_mode, ptp->cfg, ptp->def_cfg);
		ptp->mode = ptp->def_mode;
		ptp->cfg = ptp->def_cfg;
		ptp->reg->start(ptp, false);
	}
	cmd->two_step = (ptp->mode & PTP_1STEP) ? 0 : 1;
	cmd->master = (ptp->mode & PTP_MASTER) ? 1 : 0;
	cmd->p2p = (ptp->mode & PTP_TC_P2P) ? 1 : 0;
	cmd->as = (ptp->mode & PTP_802_1AS) ? 1 : 0;
	cmd->unicast = (ptp->cfg & PTP_UNICAST_ENABLE) ? 1 : 0;
	cmd->alternate = (ptp->cfg & PTP_ALTERNATE_MASTER) ? 1 : 0;
	cmd->domain_check = (ptp->cfg & PTP_DOMAIN_CHECK) ? 1 : 0;
	cmd->udp_csum = (ptp->cfg & PTP_UDP_CHECKSUM) ? 1 : 0;
	cmd->delay_assoc = (ptp->cfg & PTP_DELAY_CHECK) ? 1 : 0;
	cmd->pdelay_assoc = (ptp->cfg & PTP_PDELAY_CHECK) ? 1 : 0;
	cmd->sync_assoc = (ptp->cfg & PTP_SYNC_CHECK) ? 1 : 0;
	cmd->drop_sync = (ptp->cfg & PTP_DROP_SYNC_DELAY_REQ) ? 1 : 0;
	cmd->reserved = ptp->started;
	cmd->domain = ptp->domain;
	cmd->access_delay = ptp->get_delay;
}  /* proc_ptp_get_cfg */

static int proc_ptp_set_cfg(struct ptp_info *ptp, u8 *data)
{
	struct ptp_cfg_options *cmd = (struct ptp_cfg_options *) data;
	u16 cfg;
	u16 mode;
	u8 domain;
	struct ksz_sw *sw = ptp->parent;

	mode = ptp->mode;
	cfg = ptp->cfg;
	domain = ptp->domain;
	if (cmd->domain_set) {
		domain = cmd->domain;
	} else {
		if (cmd->two_step_set) {
			if (cmd->two_step)
				ptp->mode &= ~PTP_1STEP;
			else
				ptp->mode |= PTP_1STEP;
		}
		if (cmd->master_set) {
			if (cmd->master)
				ptp->mode |= PTP_MASTER;
			else
				ptp->mode &= ~PTP_MASTER;
		}
		if (cmd->p2p_set) {
			if (cmd->p2p)
				ptp->mode |= PTP_TC_P2P;
			else
				ptp->mode &= ~PTP_TC_P2P;
		}
		if (cmd->as_set) {
			if (cmd->as)
				ptp->mode |= PTP_802_1AS;
			else
				ptp->mode &= ~PTP_802_1AS;
		}
		if (cmd->unicast_set) {
			if (cmd->unicast)
				ptp->cfg |= PTP_UNICAST_ENABLE;
			else
				ptp->cfg &= ~PTP_UNICAST_ENABLE;
		}
		if (cmd->alternate_set) {
			if (cmd->alternate)
				ptp->cfg |= PTP_ALTERNATE_MASTER;
			else
				ptp->cfg &= ~PTP_ALTERNATE_MASTER;
		}
		if (cmd->domain_check_set) {
			if (cmd->domain_check)
				ptp->cfg |= PTP_DOMAIN_CHECK;
			else
				ptp->cfg &= ~PTP_DOMAIN_CHECK;
		}
		if (cmd->udp_csum_set) {
			if (cmd->udp_csum)
				ptp->cfg |= PTP_UDP_CHECKSUM;
			else
				ptp->cfg &= ~PTP_UDP_CHECKSUM;
		}
		if (cmd->delay_assoc_set) {
			if (cmd->delay_assoc)
				ptp->cfg |= PTP_DELAY_CHECK;
			else
				ptp->cfg &= ~PTP_DELAY_CHECK;
		}
		if (cmd->pdelay_assoc_set) {
			if (!(ptp->mode & PTP_1STEP))
				cmd->pdelay_assoc = 0;
			if (cmd->pdelay_assoc)
				ptp->cfg |= PTP_PDELAY_CHECK;
			else
				ptp->cfg &= ~PTP_PDELAY_CHECK;
		}
		if (cmd->sync_assoc_set) {
			if (cmd->sync_assoc)
				ptp->cfg |= PTP_SYNC_CHECK;
			else
				ptp->cfg &= ~PTP_SYNC_CHECK;
		}
		if (cmd->drop_sync_set) {
			if (cmd->drop_sync)
				ptp->cfg |= PTP_DROP_SYNC_DELAY_REQ;
			else
				ptp->cfg &= ~PTP_DROP_SYNC_DELAY_REQ;
		}
		if (cmd->priority_set) {
			ptp->ops->acquire(ptp);
			sw->ops->cfg(sw, REG_PTP_EVENT_PRIO_CTRL,
				     PTP_PRIO_ENABLE, cmd->priority);
			sw->ops->cfg(sw, REG_PTP_GENERAL_PRIO_CTRL,
				     PTP_PRIO_ENABLE, cmd->priority);
			ptp->ops->release(ptp);
		}
	}
	ptp->ops->acquire(ptp);
	if (mode != ptp->mode) {
		u16 tx_intr = ptp->tx_intr;

		/* For efficiency. */
		if ((ptp->mode & PTP_1STEP) &&
		    !(ptp->overrides & PTP_VERIFY_TIMESTAMP))
			ptp->tx_intr &= ~
				(PTP_PORT_SYNC_INT | PTP_PORT_PDELAY_RESP_INT);
		else
			ptp->tx_intr |=
				(PTP_PORT_SYNC_INT | PTP_PORT_PDELAY_RESP_INT);
		dbg_msg("mode: %x %x; %x"NL, mode, ptp->mode, ptp->tx_intr);
		mode = ptp->mode;
		if (ptp->overrides & PTP_VERIFY_TIMESTAMP)
			mode |= PTP_1STEP;
		sw->reg->w16(sw, REG_PTP_MSG_CONF1, mode);
		ptp->def_mode = mode;
		if (tx_intr != ptp->tx_intr)
			ptp_tx_intr_enable(ptp);
	}
	if (cfg != ptp->cfg) {
		dbg_msg("cfg: %x %x"NL, cfg, ptp->cfg);
		sw->reg->w16(sw, REG_PTP_MSG_CONF2, ptp->cfg);
	}
	if (domain != ptp->domain) {
		ptp->domain = domain;
		set_ptp_domain(ptp, ptp->domain);
	}
	ptp->ops->release(ptp);
	return 0;
}  /* proc_ptp_set_cfg */

static void cancel_rx_unit(struct ptp_info *ptp, int tsi)
{
	int first;
	int last;
	int tsi_bit;
	struct ptp_event *events;

	ptp->ops->acquire(ptp);
	first = tsi;
	events = &ptp->events[tsi];
	if (events->last) {
		first = events->first;
		last = events->last;
	} else
		last = first + 1;
	tsi = first;
	ptp->events[tsi].timeout = 0;
	do {
		if (tsi >= MAX_TIMESTAMP_UNIT)
			tsi = 0;
		events = &ptp->events[tsi];
		events->first = 0;
		events->last = 0;
		tsi_bit = 1 << tsi;
		if (ptp->tsi_used & tsi_bit) {
			if (events->num < events->max) {
				ptp->reg->read_event(ptp, tsi);
				ptp->ts_status = 0;
			}
			ptp->reg->rx_off(ptp, tsi);
			ptp->tsi_intr &= ~tsi_bit;
			ptp->tsi_used &= ~tsi_bit;
			if (ptp->tsi_sys & tsi_bit) {
				printk(KERN_INFO "tsi %d off!"NL, tsi);
				ptp->tsi_sys &= ~tsi_bit;
				ptp->update_sec_jiffies = jiffies;
				schedule_delayed_work(&ptp->update_sec,
						      msecs_to_jiffies(1000));
			}
			ptp->tsi_dev[tsi] = NULL;
		}
		++tsi;
	} while (tsi != last);
	ptp->ops->release(ptp);
}  /* cancel_rx_unit */

static int check_expired_rx_unit(struct ptp_info *ptp, int tsi)
{
	int first;
	u32 expired;
	struct ptp_event *events;
	struct ksz_ptp_time diff;
	struct ptp_utime t;

	events = &ptp->events[tsi];
	first = tsi;
	if (events->last)
		first = events->first;
	events = &ptp->events[first];
	if (events->num && events->timeout) {
		ptp->ops->acquire(ptp);
		ptp->reg->get_time(ptp, &t);
		ptp->ops->release(ptp);
		calc_udiff(events->t, &t, &diff);
		if (diff.sec >= 0 && diff.nsec >= 0) {
			expired = diff.sec * 1000 + diff.nsec / 1000000;
			expired = expired * HZ / 1000;
			if (expired > events->timeout) {
				cancel_rx_unit(ptp, first);
				return 1;
			}
		}
	}
	return 0;
}  /* check_expired_rx_unit */

static int proc_dev_rx_event(struct file_dev_info *info, u8 *data)
{
	struct ptp_info *ptp = info->dev;
	struct ptp_tsi_options *cmd = (struct ptp_tsi_options *) data;
	u8 event;
	int first;
	int i;
	int intr;
	int tsi;
	int avail;
	int total;
	int last;
	int tsi_bit;
	struct ptp_event *events;

	tsi = cmd->tsi;
	total = cmd->total;
	if (!total)
		total = 1;
	first = tsi;

	/* Cancel operation. */
	if ((cmd->flags & PTP_CMD_CANCEL_OPER)) {
		if (tsi >= MAX_TIMESTAMP_UNIT)
			return DEV_IOC_UNIT_UNAVAILABLE;
		cancel_rx_unit(ptp, tsi);
		goto proc_ptp_rx_cascade_event_done;
	}
	if (tsi >= MAX_TIMESTAMP_UNIT) {
		first = 0;
		do {
			for (tsi = first; tsi < MAX_TIMESTAMP_UNIT; tsi++)
				if (!(ptp->tsi_used & (1 << tsi)) &&
						!ptp->events[tsi].last)
					break;
			if (tsi >= MAX_TIMESTAMP_UNIT)
				return DEV_IOC_UNIT_UNAVAILABLE;
			first = tsi;
			avail = 1;
			for (i = 1; i < total; i++)
				if (!(ptp->tsi_used & (1 << tsi)) &&
						!ptp->events[tsi].last) {
					++avail;
					++tsi;
					if (tsi >= MAX_TIMESTAMP_UNIT)
						tsi = 0;
				} else {
					++first;
					break;
				}
		} while (avail < total);
	} else {
		for (i = 0; i < total; i++) {
			if (ptp->tsi_used & (1 << tsi) ||
					ptp->events[tsi].last)
				if (!check_expired_rx_unit(ptp, tsi))
					return DEV_IOC_UNIT_USED;
			++tsi;
			if (tsi >= MAX_TIMESTAMP_UNIT)
				tsi = 0;
		}
	}
	if (cmd->gpi >= MAX_GPIO)
		return -EINVAL;
	if (0 == cmd->event)
		event = DETECT_FALL;
	else if (1 == cmd->event)
		event = DETECT_RISE;
	else {
		event = DETECT_RISE | DETECT_FALL;
		cmd->event = 2;
	}
	tsi = first;
	last = first + total;
	if (last > MAX_TIMESTAMP_UNIT)
		last -= MAX_TIMESTAMP_UNIT;
	intr = cmd->flags & PTP_CMD_INTR_OPER;
	ptp->ops->acquire(ptp);
	for (i = 0; i < total; i++) {
		tsi_bit = 1 << tsi;
		ptp->tsi_used |= tsi_bit;
		if (intr & !(cmd->flags & PTP_CMD_SILENT_OPER)) {
			ptp->tsi_intr |= tsi_bit;
			ptp->tsi_dev[tsi] = info;
		}
		events = &ptp->events[tsi];
		events->num = 0;
		events->event = cmd->event;
		events->edge = 0;
		events->expired = 0;
		if (total > 1) {
			events->first = first;
			events->last = last;
		}
		++tsi;
		if (tsi >= MAX_TIMESTAMP_UNIT)
			tsi = 0;
	}
	tsi = first;
	ptp->events[tsi].timeout = cmd->timeout * HZ / 1000;

	/* Zero timeout means repeatable. */
	if (!ptp->events[tsi].timeout && cmd->timeout)
		ptp->events[tsi].timeout = 1;
	if (total > 1)
		ptp->reg->rx_cascade_event(ptp, tsi, total, cmd->gpi, event,
			intr);
	else
		ptp->reg->rx_event(ptp, tsi, cmd->gpi, event, intr);
	ptp->ops->release(ptp);

proc_ptp_rx_cascade_event_done:
	*data = tsi;
	return 0;
}  /* proc_dev_rx_event */

static int find_avail_tx_unit(struct ptp_info *ptp, int total, int *unit)
{
	int avail;
	int first;
	int i;
	int tso;

	first = 0;
	do {
		for (tso = first; tso < MAX_TRIG_UNIT; tso++)
			if (!(ptp->tso_used & (1 << tso)))
				break;
		if (tso >= MAX_TRIG_UNIT)
			return DEV_IOC_UNIT_UNAVAILABLE;
		first = tso++;
		avail = 1;
		for (i = 1; i < total; i++) {
			if (tso >= MAX_TRIG_UNIT)
				return DEV_IOC_UNIT_UNAVAILABLE;
			if (!(ptp->tso_used & (1 << tso))) {
				++avail;
				++tso;
			} else {
				++first;
				break;
			}
		}
	} while (avail < total);
	*unit = first;
	return 0;
}  /* find_avail_tx_unit */

static int proc_dev_tx_event(struct file_dev_info *info, u8 *data)
{
	struct ptp_info *ptp = info->dev;
	struct ptp_tso_options *cmd = (struct ptp_tso_options *) data;
	int gpo;
	int intr;
	int tso;
	int tso_bit;
	struct ptp_utime t;
	u16 active;
	u32 status;
	int err = 0;
	struct ksz_sw *sw = ptp->parent;

	gpo = cmd->gpo;
	if (gpo >= MAX_GPIO)
		return -EINVAL;
	if (cmd->event > TRIG_REG_OUTPUT)
		return -EINVAL;
	tso = cmd->tso;
	tso_bit = 1 << tso;

	/* Cancel operation. */
	if ((cmd->flags & PTP_CMD_CANCEL_OPER)) {
		if (tso >= MAX_TRIG_UNIT)
			return DEV_IOC_UNIT_UNAVAILABLE;
		ptp->ops->acquire(ptp);

		/* Reset the tso. */
		ptp->cascade_tx |= tso_bit;
		ptp_tso_off(ptp, tso, tso_bit);
		ptp->ops->release(ptp);
		goto proc_dev_tx_event_done;
	}
	if (ptp->cascade && (tso < ptp->cascade_gpo[gpo].first ||
			tso >= ptp->cascade_gpo[gpo].first +
			ptp->cascade_gpo[gpo].total))
		return DEV_IOC_UNIT_UNAVAILABLE;

	/* Find available unit for use. */
	if (tso >= MAX_TRIG_UNIT) {
		int rc = find_avail_tx_unit(ptp, 1, &tso);

		if (rc)
			return rc;
	} else if (!ptp->cascade && (ptp->tso_used & tso_bit)) {

		/* See whether previous operation is completed. */
		ptp->ops->acquire(ptp);
		ptp_write_index(ptp, PTP_TOU_INDEX_S, tso);
		active = sw->reg->r32(sw, REG_PTP_CTRL_STAT__4);
		status = sw->reg->r32(sw, REG_PTP_TRIG_STATUS__4);
		ptp->ops->release(ptp);
		if (active & TRIG_ACTIVE) {
			u16 error = (status >> TRIG_ERROR_S) &
				PTP_TRIG_UNIT_M;

			if (!(error & tso_bit))
				return DEV_IOC_UNIT_USED;
			dbg_msg("trig err: %d"NL, tso);
		}
		if (!(active & TRIG_ACTIVE)) {
			u16 done = status & PTP_TRIG_UNIT_M;

			if (!(done & tso_bit)) {
				/* Reset the unit. */
				ptp->cascade_tx |= tso_bit;
				dbg_msg(" !? trig done: %d"NL, tso);
			}
		}
		ptp->ops->acquire(ptp);
		ptp_tso_off(ptp, tso, tso_bit);
		ptp->ops->release(ptp);
	}
	ptp->ops->acquire(ptp);
	if (!ptp->cascade && (cmd->flags & PTP_CMD_REL_TIME) &&
			cmd->sec < 100) {
		ptp->reg->get_time(ptp, &t);
		if (0 == cmd->sec) {
			cmd->nsec += t.nsec;
			cmd->nsec += 500;
			cmd->nsec /= 1000;
			cmd->nsec *= 1000;
			if (cmd->nsec >= NANOSEC_IN_SEC) {
				cmd->nsec -= NANOSEC_IN_SEC;
				cmd->sec++;
			}
		}
		cmd->sec += t.sec;
	}
	intr = cmd->flags & PTP_CMD_INTR_OPER;
	if (intr & !(cmd->flags & PTP_CMD_SILENT_OPER)) {
		ptp->tso_intr |= tso_bit;
		ptp->tso_dev[tso] = info;
	}
	ptp->tso_used |= tso_bit;
	ptp->reg->tx_event(ptp, tso, cmd->gpo, cmd->event, cmd->pulse,
		cmd->cycle, cmd->cnt, cmd->sec, cmd->nsec, cmd->iterate, intr,
		!(cmd->flags & PTP_CMD_ON_TIME),
		(cmd->flags & PTP_CMD_CLK_OPT));
	if (cmd->flags & PTP_CMD_ON_TIME) {
		status = sw->reg->r32(sw, REG_PTP_TRIG_STATUS__4);
		status = (status >> TRIG_ERROR_S) & PTP_TRIG_UNIT_M;
		if (status & tso_bit)
			err = DEV_IOC_UNIT_ERROR;
	}
	ptp->ops->release(ptp);

proc_dev_tx_event_done:
	*data = tso;
	return err;
}  /* proc_dev_tx_event */

static int proc_ptp_tx_cascade_init(struct ptp_info *ptp, u8 *data)
{
	struct ptp_tso_options *cmd = (struct ptp_tso_options *) data;
	int first;
	int gpo;
	int i;
	int tso;
	int total;
	u32 status;
	struct ksz_sw *sw = ptp->parent;

	tso = cmd->tso;
	gpo = cmd->gpo;
	total = cmd->total;
	if (!total)
		return -EINVAL;
	if (gpo >= MAX_GPIO)
		return -EINVAL;
	first = tso;

	/* Cancel operation. */
	if ((cmd->flags & PTP_CMD_CANCEL_OPER)) {
		if (tso >= MAX_TRIG_UNIT)
			return DEV_IOC_UNIT_UNAVAILABLE;
		if (first != ptp->cascade_gpo[gpo].first ||
				total != ptp->cascade_gpo[gpo].total) {
			first = ptp->cascade_gpo[gpo].first;
			total = ptp->cascade_gpo[gpo].total;
		}

		/* Reset the last unit in case it is used to raise the level. */
		first = first + total - 1;
		if (ptp->outputs[first].level) {
			ptp->cascade_tx |= (1 << first);
			ptp->tso_used |= (1 << first);
		}
		ptp->ops->acquire(ptp);
		for (i = 0; i < total; i++, tso++) {
			if (ptp->tso_used & (1 << tso))
				ptp_tso_off(ptp, tso, (1 << tso));
		}
		tso = total;
		ptp->cascade = false;
		ptp->ops->release(ptp);
		goto proc_ptp_tx_cascade_init_done;
	}

	if (ptp->cascade)
		return DEV_IOC_UNIT_UNAVAILABLE;

	/* Find available units for use. */
	if (tso >= MAX_TRIG_UNIT) {
		int rc = find_avail_tx_unit(ptp, total, &first);

		if (rc)
			return rc;
	} else {
		for (i = 0; i < total; i++) {
			if (tso >= MAX_TRIG_UNIT)
				return DEV_IOC_UNIT_UNAVAILABLE;
			if (ptp->tso_used & (1 << tso))
				return DEV_IOC_UNIT_USED;
			++tso;
		}
	}

	if ((cmd->flags & PTP_CMD_CASCADE_RESET_OPER))
		goto proc_ptp_tx_cascade_init_set;

	/* Last operation was not in cascade mode. */
	if (!ptp->cascade_gpo[gpo].total)
		goto proc_ptp_tx_cascade_init_set;

	/* previous last unit. */
	i = ptp->cascade_gpo[gpo].first + ptp->cascade_gpo[gpo].total - 1;

	/* current last unit. */
	tso = first + total - 1;

	/* Last operation not ended high. */
	if (tso == i || !ptp->outputs[i].level)
		goto proc_ptp_tx_cascade_init_set;

	ptp->ops->acquire(ptp);
	ptp_write_index(ptp, PTP_GPIO_INDEX_S, gpo);
	status = sw->reg->r32(sw, REG_PTP_CTRL_STAT__4);

	/* Current level is high. */
	if (status & GPIO_IN) {

		/* Set unit to hold the level high. */
		ptp->reg->tx_event(ptp, tso, gpo, TRIG_POS_EDGE, 0, 0, 1, 0, 1,
			0, PTP_CMD_INTR_OPER, 1, 0);

		/* Release the signal from the previous last unit. */
		ptp_gpo_reset(ptp, ptp->outputs[i].gpo, i, NULL);
	}
	ptp->ops->release(ptp);

proc_ptp_tx_cascade_init_set:
	ptp->cascade = true;
	ptp->cascade_gpo[gpo].first = first;
	ptp->cascade_gpo[gpo].total = total;
	tso = first;

proc_ptp_tx_cascade_init_done:
	*data = tso;
	return 0;
}  /* proc_ptp_tx_cascade_init */

static int proc_ptp_tx_cascade(struct ptp_info *ptp, u8 *data)
{
	struct ptp_tso_options *cmd = (struct ptp_tso_options *) data;
	int gpo;
	int tso;
	int total;
	struct ptp_utime t;

	gpo = cmd->gpo;
	if (gpo >= MAX_GPIO)
		return -EINVAL;
	tso = cmd->tso;
	total = cmd->total;
	if (!ptp->cascade || tso != ptp->cascade_gpo[gpo].first ||
			total != ptp->cascade_gpo[gpo].total)
		return DEV_IOC_UNIT_UNAVAILABLE;

	/* Cancel operation. */
	if ((cmd->flags & PTP_CMD_CANCEL_OPER)) {
		proc_ptp_tx_cascade_init(ptp, data);
		goto proc_ptp_tx_cascade_done;
	}
	ptp->ops->acquire(ptp);
	if ((cmd->flags & PTP_CMD_REL_TIME) && cmd->sec < 100) {
		ptp->reg->get_time(ptp, &t);
		cmd->sec += t.sec;
	}
	total = ptp->reg->tx_cascade(ptp, tso, total, cmd->cnt, cmd->sec,
		cmd->nsec, cmd->flags & PTP_CMD_INTR_OPER);
	if (!total)
		ptp->cascade = false;
	ptp->ops->release(ptp);

proc_ptp_tx_cascade_done:
	*data = tso;
	return 0;
}  /* proc_ptp_tx_cascade */

static void proc_tsm_get_gps(struct ptp_info *ptp, u8 *data)
{
	struct tsm_get_gps *get = (struct tsm_get_gps *) data;

	if (!ptp->gps_dev)
		return;

	get->cmd |= TSM_CMD_GET_TIME_RESP;
	get->seqid = htons(ptp->gps_seqid);
	get->sec = htonl(ptp->gps_time.sec);
	get->nsec = htonl(ptp->gps_time.nsec);
	file_dev_setup_msg(ptp->gps_dev, data, sizeof(struct tsm_get_gps),
		NULL, NULL);
	ptp->gps_dev = NULL;
}  /* proc_tsm_get_gps */

static int proc_dev_get_event(struct file_dev_info *info, u8 *data)
{
	struct ptp_info *ptp = info->dev;
	int len;
	struct ptp_tsi_info *in = (struct ptp_tsi_info *) data;
	u8 buf[sizeof(struct ptp_utime) * MAX_TIMESTAMP_EVENT_UNIT +
		sizeof(struct ptp_tsi_info)];
	struct ptp_tsi_info *out = (struct ptp_tsi_info *) buf;

	if (in->unit >= MAX_TIMESTAMP_UNIT)
		return -EINVAL;
	if (!ptp->events[in->unit].num)
		return DEV_IOC_UNIT_UNAVAILABLE;
	out->cmd = in->cmd | PTP_CMD_RESP;
	out->unit = in->unit;
	out->event = ptp->events[in->unit].event;
	out->num = ptp->events[in->unit].num;
	out->edge = ptp->events[in->unit].edge;
	len = sizeof(struct ptp_utime) * out->num;
	memcpy(out->t, ptp->events[in->unit].t, len);
	len += sizeof(struct ptp_tsi_info);
	file_dev_setup_msg(info, buf, len, NULL, NULL);
	return 0;
}  /* proc_dev_get_event */

static int proc_ptp_get_event(struct ptp_info *ptp, u8 *data)
{
	struct ptp_tsi_info *in = (struct ptp_tsi_info *) data;
	int ret = -1;

	if (ptp->tsi_dev[in->unit])
		ret = proc_dev_get_event(ptp->tsi_dev[in->unit], data);
	return ret;
}  /* proc_ptp_get_event */

static int proc_ptp_get_trig(struct ptp_info *ptp, u8 *data, u16 done,
	u16 error)
{
	int len;
	struct ptp_tsi_info *in = (struct ptp_tsi_info *) data;
	u8 buf[sizeof(struct ptp_utime) + sizeof(struct ptp_tsi_info)];
	struct ptp_tsi_info *out = (struct ptp_tsi_info *) buf;
	struct ptp_output *cur;
	int tso = in->unit;
	int tso_bit = (1 << tso);

	out->cmd = in->cmd | PTP_CMD_RESP;
	out->unit = in->unit;
	cur = &ptp->outputs[tso];
	if (error & tso_bit)
		out->event = 1;
	else if (!(done & tso_bit))
		out->event = 2;
	else
		out->event = 0;
	out->num = 1;
	len = sizeof(struct ptp_utime) * out->num;
	memcpy(out->t, &cur->trig, len);
	len += sizeof(struct ptp_tsi_info);
	if (ptp->tso_dev[tso]) {
		file_dev_setup_msg(ptp->tso_dev[tso], buf, len, NULL, NULL);
		return 0;
	}
	return -1;
}  /* proc_ptp_get_trig */

static int proc_dev_poll_event(struct file_dev_info *info, u8 *data)
{
	struct ptp_info *ptp = info->dev;
	struct ptp_tsi_info *in = (struct ptp_tsi_info *) data;

	if (in->unit >= MAX_TIMESTAMP_UNIT)
		return -EINVAL;
	if (!ptp_poll_event(ptp, in->unit))
		return DEV_IOC_UNIT_UNAVAILABLE;
	return proc_dev_get_event(info, data);
}  /* proc_dev_poll_event */

static int proc_dev_get_event_info(struct file_dev_info *info, u8 *data)
{
	struct ptp_tsi_info *in = (struct ptp_tsi_info *) data;

	in->unit = MAX_TIMESTAMP_UNIT;
	in->event = MAX_TIMESTAMP_EVENT_UNIT;
	in->num = 0;
	return 0;
}  /* proc_dev_get_event_info */

static int proc_ptp_get_output(struct ptp_info *ptp, u8 *data)
{
	int *output = (int *) data;
	struct ptp_tso_options *in = (struct ptp_tso_options *) data;

	if (in->gpo >= MAX_GPIO)
		return -EINVAL;
	*output = ptp->cascade_gpo[in->gpo].tso;
	return 0;
}  /* proc_ptp_get_output */

static void proc_ptp_get_clk(struct ptp_info *ptp, u8 *data)
{
	struct ptp_utime t;
	struct ptp_clk_options *cmd = (struct ptp_clk_options *) data;

	ptp->ops->acquire(ptp);
	ptp->reg->get_time(ptp, &t);
	ptp->ops->release(ptp);
	cmd->sec = t.sec;
	cmd->nsec = t.nsec;
}  /* proc_ptp_get_clk */

static int proc_ptp_set_clk(struct ptp_info *ptp, u8 *data)
{
	struct ptp_utime t;
	struct ptp_clk_options *cmd = (struct ptp_clk_options *) data;
	struct timespec64 ts;
	struct ptp_utime sys_time;

	t.sec = cmd->sec;
	t.nsec = cmd->nsec;
	ptp->ops->acquire(ptp);
	ts = ktime_to_timespec64(ktime_get_real());
	sys_time.sec = ts.tv_sec;
	sys_time.nsec = ts.tv_nsec;
	ptp->reg->set_time(ptp, &t);
	ptp->cur_time = t;
	calc_udiff(&ptp->cur_time, &sys_time, &ptp->time_diff);
	generate_tx_event(ptp, ptp->pps_gpo);
	ptp->ops->release(ptp);
	dbg_msg(" set clk: %x:%09u"NL, cmd->sec, cmd->nsec);
	return 0;
}  /* proc_ptp_set_clk */

static int proc_ptp_adj_clk(struct ptp_info *ptp, u8 *data, int adjust)
{
	struct ptp_clk_options *cmd = (struct ptp_clk_options *) data;

	adjust--;
	if (cmd->sec > 1) {
		ptp->adjust_sec = cmd->sec;
		ptp->adjust_offset = cmd->nsec;
		if (!adjust) {
			ptp->adjust_sec = -ptp->adjust_sec;
			ptp->adjust_offset = -ptp->adjust_offset;
		}
		dbg_msg("adj clk: %d %u:%09u"NL, adjust, cmd->sec, cmd->nsec);
		cmd->sec = cmd->nsec = 0;
		ptp->adj_clk.func(&ptp->adj_clk);
	}
	ptp->ops->acquire(ptp);
	if (cmd->nsec || cmd->sec) {
		ptp->sec_changed = cmd->sec;
		if (!(ptp->features & PTP_ADJ_SEC)) {
			cmd->nsec += cmd->sec * NANOSEC_IN_SEC;
			cmd->sec = 0;
		}
		ptp->reg->adjust_time(ptp, adjust, cmd->sec, cmd->nsec,
			ptp->features & PTP_ADJ_HACK);
		ptp->offset_changed = cmd->nsec;
		if (!adjust)
			ptp->offset_changed = -cmd->nsec;
		if (ptp->sec_changed || ptp->clk_add)
			generate_tx_event(ptp, ptp->pps_gpo);
#ifndef NO_PPS_DETECT
		else {
			ptp->update_sec_jiffies = jiffies;
			schedule_delayed_work(&ptp->check_pps,
					      msecs_to_jiffies(1200));
		}
#endif
		if (ptp->sec_changed) {
			if (adjust)
				ptp->cur_time.sec += cmd->sec;
			else
				ptp->cur_time.sec -= cmd->sec;
			ptp->sec_changed = 0;
		}
		if (adjust)
			add_nsec(&ptp->cur_time, cmd->nsec);
		else
			sub_nsec(&ptp->cur_time, cmd->nsec);
		if (cmd->sec)
		dbg_msg(" adj clk: %d %u:%09u"NL, adjust, cmd->sec, cmd->nsec);
	}
	if (cmd->interval) {
		ptp->drift = cmd->drift;
		if (ptp->drift > MAX_DRIFT_CORR)
			ptp->drift = MAX_DRIFT_CORR;
		else if (ptp->drift < -MAX_DRIFT_CORR)
			ptp->drift = -MAX_DRIFT_CORR;
		ptp->drift_set = ptp->drift;
		ptp->adjust = clk_adjust_val(ptp->drift, cmd->interval);
		set_ptp_adjust(ptp, ptp->adjust);
		if (!ptp->ptp_synt) {
			syntonize_clk(ptp);
			ptp->ptp_synt = true;
		}
if (!ptp->first_drift && ptp->drift_set)
dbg_msg("first drift: %d"NL, ptp->drift_set);
		if (!ptp->first_drift)
			ptp->first_drift = ptp->drift_set;
#if 0
		dbg_msg(" adj drift: %d"NL, cmd->drift);
#endif
	}
	ptp->ops->release(ptp);
	return 0;
}  /* proc_ptp_adj_clk */

static int proc_ptp_get_delay(struct ptp_info *ptp, uint port, u8 *data)
{
	struct ptp_delay_values *delay = (struct ptp_delay_values *) data;
	struct ksz_sw *sw = ptp->parent;

	if (port > ptp->ports)
		return DEV_IOC_INVALID_CMD;
	port = get_phy_port(sw, port);
	ptp->ops->acquire(ptp);
	delay->rx_latency = get_ptp_ingress(ptp, port);
	delay->tx_latency = get_ptp_egress(ptp, port);
	delay->asym_delay = get_ptp_asym(ptp, port);
	ptp->ops->release(ptp);
	return 0;
}  /* proc_ptp_get_delay */

static int proc_ptp_set_delay(struct ptp_info *ptp, uint port, u8 *data)
{
	struct ptp_delay_values *delay = (struct ptp_delay_values *) data;
	struct ksz_sw *sw = ptp->parent;
	int index;

	if (port > ptp->ports)
		return DEV_IOC_INVALID_CMD;
	port = get_phy_port(sw, port);
	ptp->ops->acquire(ptp);
	set_ptp_ingress(ptp, port, delay->rx_latency);
	set_ptp_egress(ptp, port, delay->tx_latency);
	set_ptp_asym(ptp, port, delay->asym_delay);
	index = get_speed_index(ptp, port);
	ptp->rx_latency[port][index] = delay->rx_latency;
	ptp->tx_latency[port][index] = delay->tx_latency;
	ptp->asym_delay[port][index] = delay->asym_delay;
	ptp->ops->release(ptp);
	dbg_msg("set delay: %d = %d %d %d"NL, port,
		ptp->rx_latency[port][index],
		ptp->tx_latency[port][index],
		ptp->asym_delay[port][index]);
	return 0;
}  /* proc_ptp_set_delay */

static int proc_ptp_get_peer_delay(struct ptp_info *ptp, uint port, u8 *data)
{
	struct ptp_delay_values *delay = (struct ptp_delay_values *) data;
	struct ksz_sw *sw = ptp->parent;
	u32 link;

	if (port > ptp->ports)
		return DEV_IOC_INVALID_CMD;
	port = get_phy_port(sw, port);
	ptp->ops->acquire(ptp);
	delay->rx_latency = 0;
	delay->tx_latency = 0;
	delay->asym_delay = 0;
	link = get_ptp_link(ptp, port);
	delay->reserved = link;
	delay->rx_latency = link >> 16;
	ptp->ops->release(ptp);
	return 0;
}  /* proc_ptp_get_peer_delay */

static int proc_ptp_set_peer_delay(struct ptp_info *ptp, uint port, u8 *data)
{
	struct ptp_delay_values *delay = (struct ptp_delay_values *) data;
	struct ksz_sw *sw = ptp->parent;
	u32 link;

	if (port > ptp->ports)
		return DEV_IOC_INVALID_CMD;
	port = get_phy_port(sw, port);
	ptp->ops->acquire(ptp);
	link = delay->rx_latency;
	link <<= 16;
	link |= delay->reserved;
	if (link != ptp->peer_delay[port]) {
		set_ptp_link(ptp, port, link);
		ptp->peer_delay[port] = link;
		if (abs(link - ptp->peer_delay[port]) > 5)
			dbg_msg("set delay: %d = %d"NL, port,
				ptp->peer_delay[port]);
	}
	ptp->ops->release(ptp);
	return 0;
}  /* proc_ptp_set_peer_delay */

static int proc_ptp_get_port_cfg(struct ptp_info *ptp, uint port, u8 *data)
{
	struct ptp_delay_values *delay = (struct ptp_delay_values *) data;
	struct ksz_sw *sw = ptp->parent;
	struct ksz_port_cfg *cfg;

	if (port > ptp->ports)
		return DEV_IOC_INVALID_CMD;
	port = get_phy_port(sw, port);
	cfg = get_port_cfg(sw, port);
	delay->reserved = 0;
	if (cfg->ptp_enabled)
		delay->reserved |= PTP_PORT_ENABLED;
	if (cfg->asCapable)
		delay->reserved |= PTP_PORT_ASCAPABLE;
	return 0;
}  /* proc_ptp_get_port_cfg */

static int proc_ptp_set_port_cfg(struct ptp_info *ptp, uint port, u8 *data)
{
	struct ptp_delay_values *delay = (struct ptp_delay_values *) data;
	struct ksz_sw *sw = ptp->parent;
	struct ksz_port_cfg *cfg;

	if (port > ptp->ports)
		return DEV_IOC_INVALID_CMD;
	port = get_phy_port(sw, port);
	cfg = get_port_cfg(sw, port);
	cfg->ptp_enabled = !!(delay->reserved & PTP_PORT_ENABLED);
	if (cfg->ptp_enabled)
		cfg->asCapable = !!(delay->reserved & PTP_PORT_ASCAPABLE);
	else
		cfg->asCapable = false;

#ifdef CONFIG_KSZ_MSRP
	if (sw->features & MRP_SUPPORT) {
		struct mrp_info *mrp = &sw->mrp;

dbg_msg("as: %d=%d"NL, port, cfg->asCapable);
		mrp->ops->chk_talker(mrp, port);
	}
#endif
	return 0;
}  /* proc_ptp_set_port_cfg */

static void ptp_tx_done(struct ptp_info *ptp, int tso)
{
	int first;
	int last;
	int prev;
	u32 data;
	struct ksz_sw *sw = ptp->parent;

	ptp_write_index(ptp, PTP_TOU_INDEX_S, tso);
	data = sw->reg->r32(sw, REG_TRIG_CTRL__4);
	if (data & TRIG_CASCADE_ENABLE) {
		last = tso;
		do {
			--tso;
			ptp_write_index(ptp, PTP_TOU_INDEX_S, tso);
			data = sw->reg->r32(sw, REG_TRIG_CTRL__4);
			prev = (data >> TRIG_CASCADE_UPS_S) &
				TRIG_CASCADE_UPS_M;
			if (prev == last)
				break;
		} while (tso > 0);
		first = tso;
		for (tso = last; tso > first; tso--)
			ptp_tso_off(ptp, tso, (1 << tso));
	}
	ptp_tso_off(ptp, tso, (1 << tso));
}  /* ptp_tx_done */

static struct ptp_tx_ts *proc_get_ts(struct ptp_info *ptp, uint port, u8 msg,
	u16 seqid, u8 *mac, struct file_dev_info *info, int len)
{
	struct ptp_tx_ts *tx;
	int from_stack = false;
	u8 *data = NULL;
	struct ksz_sw *sw = ptp->parent;
	bool linked = (media_connected == sw->port_info[port].state);

	if (info)
		data = info->write_buf;
	if (SYNC_MSG == msg)
		tx = &ptp->tx_sync[port];
	else if (PDELAY_RESP_MSG == msg)
		tx = &ptp->tx_resp[port];
	else
		tx = &ptp->tx_dreq[port];
	if (seqid || mac[0] || mac[1])
		from_stack = true;
	if (data && tx->req_time && linked && port < 5)
		dbg_msg("  last %x=%04x: p=%d, j=%lu"NL, msg, seqid, port,
			jiffies - tx->req_time);
	tx->missed = false;
	tx->req_time = jiffies;
	if (tx->ts.timestamp && from_stack) {
		unsigned long diff = tx->req_time - tx->resp_time;

		/* The timestamp is not valid. */
		if (diff >= 4 * ptp->delay_ticks) {
			dbg_msg("  invalid: %x=%04x: %d, %lu"NL,
				msg, seqid, port, diff);
			tx->ts.timestamp = 0;
		} else if (diff > 2 * ptp->delay_ticks)
			dbg_msg("  ready? %x=%04x: %d, %lu"NL,
				msg, seqid, port, diff);
	}
	if (!tx->ts.timestamp && linked && data) {
		int rc = wait_event_interruptible_timeout(ptp->wait_ts[port],
			0 != tx->ts.timestamp, ptp->delay_ticks);

		if (rc < 0)
			return NULL;
	}
	if (!tx->ts.timestamp) {
		if (from_stack && data) {
			tx->missed = true;
			memcpy(tx->data.buf, data, len);
			tx->data.len = len;
			tx->dev = info;
		}
		if (linked && port < 5)
			dbg_msg("  missed %x=%04x: p=%d, j=%lu"NL,
				msg, seqid, port, jiffies - tx->req_time);
		tx = NULL;
	}
	return tx;
}  /* proc_get_ts */

static int proc_ptp_get_timestamp(struct ptp_info *ptp, u8 *data,
	struct file_dev_info *info)
{
	struct ptp_ts_options *opt = (struct ptp_ts_options *) data;

	if (opt->timestamp) {
		struct ptp_ts ts;

		ts.timestamp = opt->timestamp;
		update_ts(&ts, ptp->cur_time.sec);
		opt->sec = ts.t.sec;
		opt->nsec = ts.t.nsec;
	} else {
		struct ptp_tx_ts *tx;
		struct tsm_db *db;
		uint port;
		struct ksz_sw *sw = ptp->parent;

		if (opt->port > ptp->ports)
			return DEV_IOC_INVALID_CMD;

		/* Save timestamp information for later reporting. */
		if (info) {
			db = (struct tsm_db *) info->write_buf;
			db->cmd = opt->msg;
			db->cmd |= TSM_CMD_DB_GET;
			db->index = opt->port << 1;
			db->seqid = htons(opt->seqid);
			db->mac[0] = opt->mac[0];
			db->mac[1] = opt->mac[1];
		}
		port = get_phy_port(sw, opt->port);
		tx = proc_get_ts(ptp, port, opt->msg,
			opt->seqid, opt->mac, info, sizeof(struct tsm_db));
		if (!tx)
			return -EAGAIN;
		if (ptp->cap & PTP_KNOW_ABOUT_LATENCY) {
			opt->sec = tx->ts.r.sec;
			opt->nsec = tx->ts.r.nsec;
		} else {
			opt->sec = tx->ts.t.sec;
			opt->nsec = tx->ts.t.nsec;
		}
		tx->ts.timestamp = 0;
		tx->req_time = 0;
	}
	return 0;
}  /* proc_ptp_get_timestamp */

static struct ptp_tx_ts *proc_get_ts_port(struct ptp_info *ptp, u8 msg,
	uint *port, int *more)
{
	uint m;
	uint p;
	struct ptp_tx_ts *tx;
	struct ptp_tx_ts *xts = NULL;
	struct ksz_sw *sw = ptp->parent;
	struct ksz_port_info *info;
	bool linked;

	*more = false;
	for (m = 1; m <= ptp->ports; m++) {
		p = get_phy_port(sw, m);
		if (SYNC_MSG == msg)
			tx = &ptp->tx_sync[p];
		else if (PDELAY_RESP_MSG == msg)
			tx = &ptp->tx_resp[p];
		else
			tx = &ptp->tx_dreq[p];

		/* Same type of event message has been sent. */
		if (tx->hdr.messageType != msg)
			continue;

		*more = true;

		/* Have all information ready. */
		if (xts)
			break;

		info = get_port_info(sw, p);
		linked = (media_connected == info->state);
		if (!tx->ts.timestamp && linked) {
			int rc = wait_event_interruptible_timeout(
				ptp->wait_ts[p], 0 != tx->ts.timestamp,
				ptp->delay_ticks);

			if (rc < 0)
				return NULL;
		}

		/* Transmit timestamp ready. */
		if (tx->ts.timestamp) {
			xts = tx;
			*port = p;
			*more = false;
			tx->ts.timestamp = 0;
			tx->req_time = 0;
			tx->hdr.messageType = 7;
		}
	}
	return xts;
}  /* proc_get_ts_port */

static int proc_ptp_get_msg_info(struct ptp_info *ptp, u8 *data,
	struct file_dev_info *info, int *tx)
{
	struct ksz_sw *sw = ptp->parent;
	struct ptp_msg_options *opt = (struct ptp_msg_options *) data;

	if (!*tx) {
		struct ptp_msg_hdr hdr;
		struct ptp_msg_options tx_msg;
		int found;

		memcpy(&hdr.sourcePortIdentity, &opt->id,
			sizeof(struct ptp_port_identity));
		hdr.messageType = opt->msg;
		hdr.sequenceId = opt->seqid;
		hdr.domainNumber = opt->domain;
		found = find_msg_info(&ptp->rx_msg_info[hdr.messageType],
			&ptp->rx_msg_lock, &hdr, &hdr.sourcePortIdentity,
			true, &tx_msg);
		if (found) {
			opt->port = get_log_port(sw, tx_msg.port);
			opt->ts = tx_msg.ts;
		} else
			return DEV_IOC_UNIT_UNAVAILABLE;
	} else {
		struct ptp_tx_ts *xts;
		uint port = 0;

		/* Not event message. */
		if (opt->msg & 0x8)
			return DEV_IOC_INVALID_CMD;

		xts = proc_get_ts_port(ptp, opt->msg, &port, tx);
		if (xts) {
			if (ptp->cap & PTP_KNOW_ABOUT_LATENCY) {
				opt->ts.t.sec = xts->ts.r.sec;
				opt->ts.t.nsec = xts->ts.r.nsec;
			} else {
				opt->ts.t.sec = xts->ts.t.sec;
				opt->ts.t.nsec = xts->ts.t.nsec;
			}
			opt->port = get_log_port(sw, port);
		} else
			return -EAGAIN;
	}
	return 0;
}  /* proc_ptp_get_msg_info */

static int proc_ptp_set_msg_info(struct ptp_info *ptp, u8 *data,
	struct file_dev_info *info)
{
	struct ksz_sw *sw = ptp->parent;
	struct ptp_msg_options *opt = (struct ptp_msg_options *) data;

	/* Used for testing. */
	if (7 == opt->msg) {
		struct ptp_msg_info *tx_msg;
		u32 ports = opt->port;

		if (ports >= (1 << ptp->ports))
			return DEV_IOC_INVALID_CMD;

		ports = sw->ops->get_phy_mask_from_log(sw, ports);

		/* Do not allow sending to host port. */
		if (ports == sw->HOST_MASK)
			return DEV_IOC_INVALID_CMD;

		/* Host port is not sending. */
		ports &= ~sw->HOST_MASK;
		tx_msg = &ptp->tx_msg_info[opt->msg];
		tx_msg->data.port = ports;
		tx_msg->data.ts.timestamp = opt->ts.timestamp;
		if (opt->port) {
			ptp->tx_msg_cnt = -1;
			ptp->overrides |= PTP_USE_DEFAULT_PORT;
		} else {
			ptp->tx_msg_cnt = 0;
			ptp->overrides &= ~PTP_USE_DEFAULT_PORT;
		}
	} else {
		struct ptp_msg_hdr hdr;
		u32 ports = opt->port;

		if (ports >= (1 << ptp->ports))
			return DEV_IOC_INVALID_CMD;

		ports = sw->ops->get_phy_mask_from_log(sw, ports);

		/* Do not allow sending to host port. */
		if (ports == sw->HOST_MASK)
			return DEV_IOC_INVALID_CMD;

		/* Host port is not sending. */
		ports &= ~sw->HOST_MASK;
		memcpy(&hdr.sourcePortIdentity, &opt->id,
			sizeof(struct ptp_port_identity));
		hdr.messageType = opt->msg;
		hdr.sequenceId = opt->seqid;
		hdr.domainNumber = opt->domain;
		opt->ts.timestamp = (opt->ts.t.sec << 30) |
			opt->ts.t.nsec;
		set_msg_info(ptp, &hdr, ports, opt->ts.timestamp);
	}
	return 0;
}  /* proc_ptp_set_msg_info */

static int parse_tsm_msg(struct file_dev_info *info, int len)
{
	struct ptp_info *ptp = info->dev;
	u8 *data = info->write_buf;
	u8 cmd = data[0] & 0xf0;
	u8 msg = data[0] & 0x03;
	int result = 0;

	switch (cmd) {
	case TSM_CMD_DB_GET_TIME:
	{
		struct tsm_get_time *get = (struct tsm_get_time *) data;
		struct ptp_ts ts;

		ts.timestamp = ntohl(get->nsec);
		if (ts.timestamp) {
			update_ts(&ts, ptp->cur_time.sec);
		} else {
			ptp->ops->acquire(ptp);
			ptp->reg->get_time(ptp, &ts.t);
			ptp->ops->release(ptp);
		}
		file_dev_setup_msg(info, data, len, ptp_tsm_get_time_resp,
			&ts.t);
		break;
	}
	case TSM_CMD_DB_GET:
	{
		struct ksz_sw *sw = ptp->parent;
		struct tsm_db *db = (struct tsm_db *) data;

		if (db->index <= (1 << 7)) {
			struct ptp_tx_ts *tx;
			uint port = db->index >> 1;

			if (port > ptp->ports)
				break;
			port = get_phy_port(sw, port);
			tx = proc_get_ts(ptp, port, msg, ntohs(db->seqid),
				db->mac, info, len);
			if (tx) {
				file_dev_setup_msg(info, data, len,
					ptp_tsm_resp, &tx->ts);
				tx->ts.timestamp = 0;
				tx->req_time = 0;
			}
		}
		break;
	}
	case TSM_CMD_GET_GPS_TS:
	{
		/* First time to get GPS timestamp. */
		if (MAX_TIMESTAMP_UNIT == ptp->gps_tsi) {
			ptp->gps_tsi = DEFAULT_GPS_TSI;
			if (ptp->tsi_used & (1 << ptp->gps_tsi))
				ptp->reg->rx_off(ptp, ptp->gps_tsi);
			prepare_gps(ptp);
			ptp->gps_seqid = 0;
		}
		ptp->gps_req_time = jiffies;
		ptp->gps_dev = info;
		if (ptp->gps_resp_time) {
			unsigned long diff = ptp->gps_req_time -
				ptp->gps_resp_time;

			/* The timestamp is not valid. */
			if (diff >= 2 * ptp->delay_ticks) {
				dbg_msg("  invalid gps: %lu"NL, diff);
				ptp->gps_time.sec = 0;
			}
		}
		if (ptp->gps_time.sec) {
			proc_tsm_get_gps(ptp, data);
			ptp->gps_time.sec = 0;
			ptp->gps_req_time = 0;
		} else
			dbg_msg("  missed gps"NL);
		break;
	}
	case TSM_CMD_CNF_SET:
	{
		struct tsm_cfg *cfg = (struct tsm_cfg *) data;
		u32 ingress = htonl(cfg->ingress_delay);

		ptp->ops->acquire(ptp);
		if (0xFF == cfg->port) {
			u16 mode;

			if (cfg->enable & 0x04)
				ptp->mode |= PTP_TC_P2P;
			else
				ptp->mode &= ~PTP_TC_P2P;
			mode = ptp->mode;
			if (ptp->overrides & PTP_VERIFY_TIMESTAMP)
				mode |= PTP_1STEP;
			set_ptp_mode(ptp, mode);
			ptp->def_mode = ptp->mode;
		} else {
			u8 n = cfg->port - 1;
			u8 port = n;

			if ((cfg->enable & 0x10) && n < ptp->ports &&
					ptp->peer_delay[port] != ingress) {
				ptp->peer_delay[port] = ingress;
				set_ptp_link(ptp, port, ingress);
			}
		}
		ptp->ops->release(ptp);
		break;
	}
	case TSM_CMD_CLOCK_SET:
	{
		struct tsm_clock_set *clk = (struct tsm_clock_set *) data;
		struct ptp_ts ts;

		ts.t.sec = ntohl(clk->sec);
		ts.t.nsec = ntohl(clk->nsec);
		ts.timestamp = ntohl(clk->timestamp);
		ptp->ops->acquire(ptp);
		set_cur_time(ptp, &ts);
		ptp->ops->release(ptp);
		ptp->state = 2;
		break;
	}
	case TSM_CMD_CLOCK_CORRECT:
	{
		struct tsm_clock_correct *clk = (struct tsm_clock_correct *)
			data;
		u32 drift;
		u32 nsec;
		int ptp_offset;

		drift = ntohl(clk->drift);
		nsec = ntohl(clk->nsec);
		ptp_offset = ntohl(clk->offset);
		if (2 == (clk->add >> 4))
			break;

		ptp->ops->acquire(ptp);
		if (nsec) {
			ptp->reg->adjust_time(ptp, !ptp_offset, 0, nsec,
				ptp->features & PTP_ADJ_HACK);
			ptp->offset_changed = nsec;
			if (ptp_offset)
				ptp->offset_changed = -nsec;
#ifndef NO_PPS_DETECT
			ptp->update_sec_jiffies = jiffies;
			schedule_delayed_work(&ptp->check_pps,
					      msecs_to_jiffies(1200));
#endif
		}
		if (clk->add & 1)
			ptp->drift = drift;
		else
			ptp->drift = -drift;
		if (ptp->drift > MAX_DRIFT_CORR)
			ptp->drift = MAX_DRIFT_CORR;
		else if (ptp->drift < -MAX_DRIFT_CORR)
			ptp->drift = -MAX_DRIFT_CORR;
		ptp->drift_set = ptp->drift;
		ptp->adjust = clk_adjust_val(ptp->drift,
			NANOSEC_IN_SEC);
		set_ptp_adjust(ptp, ptp->adjust);
if (!ptp->first_drift)
dbg_msg("  first drift: %d"NL, ptp->drift_set);
		if (!ptp->first_drift)
			ptp->first_drift = ptp->drift_set;
		ptp->ops->release(ptp);
		break;
	}
	default:
		dbg_msg("tsm cmd: %02X, %d"NL, cmd, len);
	}
	return result;
}  /* parse_tsm_msg */

static int ptp_get_port_info(struct ptp_info *ptp, u8 *data, int *output)
{
	struct net_device *netdev;
	struct ksz_port *netport;
	u32 mask;
	int len;
	int c;
	int i;
	int n;
	int p;
	int phys_port;
	int virt_port;
	char devname[40];
	char *dot;
	char *dot2;
	char *name = (char *)data;
	bool matched = false;
	unsigned int vlan = 0;
	int result = DEV_IOC_OK;
	struct ksz_sw *sw = ptp->parent;
	int dev_count = sw->dev_count + sw->dev_offset;

	len = strnlen(name, sizeof(devname));
	strncpy(devname, name, len);
	devname[len] = '\0';
	dot = strchr(devname, '.');
	if (dot) {
		++dot;
		n = sscanf(dot, "%u", &vlan);
		dot2 = strchr(dot, '.');
		if (dot2) {
			*dot2 = '\0';
			len = strnlen(devname, sizeof(devname));
		}
	}

	/* Check real network device. */
	for (n = 0; n < dev_count; n++) {
		netdev = sw->netdev[n];
		if (!strncmp(netdev->name, devname, len) &&
		    sw->netport[n]) {
			netport = sw->netport[n];
			virt_port = netport->first_port;
			phys_port = get_phy_port(sw, virt_port);
			mask = 0;
			for (c = 0, i = netport->first_port;
			     c < netport->port_cnt; c++, i++) {
				p = get_phy_port(sw, i);
				if (p == sw->HOST_PORT)
					continue;
				mask |= (1 << p);
			}
			matched = true;
			break;
		}
	}

	/* Check virtual VLAN device. */
	if (!matched && vlan > VLAN_PORT_START &&
	    vlan <= sw->mib_port_cnt + VLAN_PORT_START) {
		--dot;
		*dot = '\0';
		--vlan;
		for (n = 0; n < dev_count; n++) {
			netdev = sw->netdev[n];
			if (!strncmp(netdev->name, devname, len) &&
			    sw->netport[n]) {
				netport = sw->netport[n];
				virt_port = netport->first_port;
				virt_port += vlan - VLAN_PORT_START;
				phys_port = get_phy_port(sw, virt_port);
				mask = (1 << phys_port);
				matched = true;
				break;
			}
		}
	}
	if (matched) {
		data[0] = 'M';
		data[1] = 'i';
		data[2] = 'c';
		data[3] = 'r';
		data[4] = phys_port + 1;
		data[5] = virt_port;
		*output = mask;
	} else {
		result = DEV_IOC_INVALID_CMD;
	}
	return result;
}  /* ptp_get_port_info */

static int execute_wait(struct ptp_work *work)
{
	int rc = 0;

	execute(work->ptp, &work->work);
	wait_for_completion(&work->done);
	return rc;
}  /* execute_wait */

static void proc_ptp_work(struct work_struct *work)
{
	struct ptp_work *parent =
		container_of(work, struct ptp_work, work);
	struct ptp_info *ptp = parent->ptp;
	struct file_dev_info *info = parent->dev_info;
	u8 *data = parent->param.data;
	uint port;
	u32 reg;
	u32 val;
	size_t width;
	int result = DEV_IOC_OK;
	struct ksz_sw *sw = ptp->parent;

	parent->output = parent->option;
	switch (parent->cmd) {
	case DEV_CMD_INFO:
		switch (parent->subcmd) {
		case DEV_INFO_INIT:
/* ptp_hwstamp_ctl is called first in Linuxptp, and it crashes occasionally. */
#if 0
			if (ptp->op_mode)
				ptp->tx_en = ptp->rx_en = 0;
#endif
			if (ptp->op_state)
				goto skip;
			ptp->cap = ptp->op_mode = 0;
			if ('1' == data[0] &&
                            '5' == data[1] &&
                            '8' == data[2] &&
                            '8' == data[3] &&
                            'v' == data[4] &&
                            '2' == data[5]) {
				int cap = parent->option;

/*
 * op_mode 0	Original mode of using reserved fields to specify port.
 * op_mode 1	Have multiple devices and use standard Linux PTP API to receive
 * 		timestamps.  Do not need to know about PTP messages except the
 * 		only case of sending 1-step Pdelay_Resp timestamp.  The
 * 		destination port is already known by other means.
 * op_mode 2	The destination port is communicated well before sending the
 * 		PTP message.
 * op_mode 3	Use single device and do not know about multiple ports.
 */
				ptp->forward = FWD_MAIN_DEV;
				if (cap & PTP_HAVE_MULT_DEVICES)
					ptp->forward = FWD_VLAN_DEV |
						       FWD_STP_DEV;
				if ((cap & PTP_HAVE_MULT_DEVICES) &&
				    (cap & PTP_CAN_RX_TIMESTAMP)) {
					ptp->op_mode = 1;
				} else if (cap & PTP_HAVE_MULT_DEVICES) {
					ptp->op_mode = 2;
				} else if (!(cap & (PTP_KNOW_ABOUT_MULT_PORTS |
						    PTP_HAVE_MULT_PORTS))) {
					ptp->op_mode = 3;
				} else if (cap & PTP_USE_RESERVED_FIELDS) {
					ptp->op_mode = 0;
				} else {
					ptp->op_mode = 2;
				}
				if (cap & PTP_CAN_RX_TIMESTAMP) {
					if (cap & PTP_KNOW_ABOUT_LATENCY) {
						ptp->rx_en &= ~(1 << 8);
						ptp->tx_en &= ~(1 << 8);
					} else {
						ptp->rx_en |= (1 << 8);
						ptp->tx_en |= (1 << 8);
					}
				}
				if (cap & PTP_USE_ONE_STEP)
					ptp->overrides |=
						PTP_VERIFY_TIMESTAMP |
						PTP_UPDATE_PDELAY_RESP_TIME;
				ptp->cap = cap;
dbg_msg("op_mode: %x %d %x:%x"NL, ptp->cap, ptp->op_mode, ptp->rx_en, ptp->tx_en);
			}

skip:
			ptp_init_state(ptp);
			parent->output = ptp->drift;
			break;
		case DEV_INFO_EXIT:
			ptp_exit_state(ptp);
			break;
		case DEV_INFO_RESET:
			reg = parent->option;
			break;
		case DEV_INFO_PORT:
			result = ptp_get_port_info(ptp, data, &parent->output);
			break;
		default:
			result = DEV_IOC_INVALID_CMD;
			break;
		}
		break;
	case DEV_CMD_PUT:
		switch (parent->subcmd) {
		case DEV_PTP_CFG:
			result = proc_ptp_set_cfg(ptp, data);
			break;
		case DEV_PTP_TEVT:
			result = proc_dev_rx_event(info, data);
			parent->output = *data;
			break;
		case DEV_PTP_TOUT:
			result = proc_dev_tx_event(info, data);
			parent->output = *data;
			break;
		case DEV_PTP_CASCADE:
			if (parent->option)
				result = proc_ptp_tx_cascade(ptp, data);
			else
				result = proc_ptp_tx_cascade_init(ptp, data);
			parent->output = *data;
			break;
		case DEV_PTP_CLK:
			parent->option &= 0xffff;
			if (parent->option)
				result = proc_ptp_adj_clk(ptp, data,
					parent->option);
			else
				result = proc_ptp_set_clk(ptp, data);
			break;
		case DEV_PTP_DELAY:
			port = parent->option;
			result = proc_ptp_set_delay(ptp, port, data);
			break;
		case DEV_PTP_REG:
			reg = parent->option;
			if (ptp->op_mode > 0 || ptp->cap) {
				u32 *param = (u32 *) data;

				switch (param[0]) {
				case 4:
					width = 4;
					break;
				case 1:
					width = 1;
					break;
				default:
					width = 2;
					break;
				}
				reg = param[1];
				val = param[2];
			} else {
				val = reg >> 16;
				reg &= 0xffff;
				width = 2;
			}
			ptp->ops->acquire(ptp);
			switch (width) {
			case 4:
				sw->reg->w32(sw, reg, val);
				break;
			case 1:
				sw->reg->w8(sw, reg, val);
				break;
			default:
				sw->reg->w16(sw, reg, val);
			}
			ptp->ops->release(ptp);
			break;
		case DEV_PTP_PEER_DELAY:
			port = parent->option;
			result = proc_ptp_set_peer_delay(ptp, port, data);
			break;
		case DEV_PTP_PORT_CFG:
			port = parent->option;
			result = proc_ptp_set_port_cfg(ptp, port, data);
			break;
		default:
			result = DEV_IOC_INVALID_CMD;
			break;
		}
		break;
	case DEV_CMD_GET:
		switch (parent->subcmd) {
		case DEV_PTP_CFG:
			proc_ptp_get_cfg(ptp, data);
			break;
		case DEV_PTP_TEVT:
			if (2 == parent->option)
				result = proc_dev_get_event_info(info, data);
			else if (1 == parent->option)
				result = proc_dev_poll_event(info, data);

			/* Not actually used. */
			else
				result = proc_dev_get_event(info, data);
			break;
		case DEV_PTP_TOUT:
			break;
		case DEV_PTP_CLK:
			parent->option &= 0xffff;
			if ((ptp->op_mode > 0 || ptp->cap) && parent->option) {
				parent->output = ptp->drift;
				break;
			}
			proc_ptp_get_clk(ptp, data);
			break;
		case DEV_PTP_DELAY:
			port = parent->option;
			result = proc_ptp_get_delay(ptp, port, data);
			break;
		case DEV_PTP_REG:
			reg = parent->option;
			width = 2;
			if (ptp->op_mode > 0 || ptp->cap) {
				u32 *param = (u32 *) data;

				switch (param[0]) {
				case 4:
					width = 4;
					break;
				case 1:
					width = 1;
					break;
				default:
					width = 2;
					break;
				}
				reg = param[1];
				val = param[2];
			}
			ptp->ops->acquire(ptp);
			switch (width) {
			case 4:
				parent->output = sw->reg->r32(sw, reg);
				break;
			case 1:
				parent->output = sw->reg->r8(sw, reg);
				break;
			default:
				parent->output = sw->reg->r16(sw, reg);
			}
			ptp->ops->release(ptp);
			break;
		case DEV_PTP_PEER_DELAY:
			port = parent->option;
			result = proc_ptp_get_peer_delay(ptp, port, data);
			break;
		case DEV_PTP_PORT_CFG:
			port = parent->option;
			result = proc_ptp_get_port_cfg(ptp, port, data);
			break;
		}
		break;
	default:
		result = DEV_IOC_INVALID_CMD;
		break;
	}
	parent->result = result;
	parent->used = false;
	complete(&parent->done);
}  /* proc_ptp_work */

static int proc_ptp_hw_access(struct ptp_info *ptp, int cmd, int subcmd,
	int option, void *data, size_t len, struct file_dev_info *info,
	int *output, int wait)
{
	struct ptp_access *access;
	struct ptp_work *work;
	int ret = 0;

	access = &ptp->hw_access;
	mutex_lock(&access->lock);
	work = &access->works[access->index];
	if (work->used) {
		pr_alert("work full"NL);
		mutex_unlock(&access->lock);
		return -EFAULT;
	}
	work->cmd = cmd;
	work->subcmd = subcmd;
	work->option = option;
	memcpy(work->param.data, data, len);
	work->dev_info = info;
	work->wait = wait;
	work->used = true;
	access->index++;
	access->index &= PTP_WORK_LAST;
	init_completion(&work->done);
	if (!wait) {
		execute(ptp, &work->work);
		goto hw_access_end;
	}
	ret = execute_wait(work);

	/* Cannot continue if ERESTARTSYS. */
	if (ret < 0)
		goto hw_access_end;

	ret = work->result;
	if (DEV_IOC_OK == ret && (DEV_CMD_GET == work->cmd ||
	    (work->cmd == DEV_CMD_INFO && work->subcmd == DEV_INFO_PORT)))
		memcpy(data, work->param.data, len);
	*output = work->output;

hw_access_end:
	mutex_unlock(&access->lock);
	return ret;
}  /* proc_ptp_hw_access */

static void exit_ptp_work(struct ptp_info *ptp)
{
	struct ptp_access *access;
	struct ptp_work *work;
	int i;

	access = &ptp->hw_access;
	for (i = 0; i < PTP_WORK_NUM; i++) {
		work = &access->works[i];
		flush_work(&work->work);
	}
}  /* exit_ptp_work */

static void init_ptp_work(struct ptp_info *ptp)
{
	struct ptp_access *access;
	struct ptp_work *work;
	int i;

	access = &ptp->hw_access;
	mutex_init(&access->lock);
	for (i = 0; i < PTP_WORK_NUM; i++) {
		work = &access->works[i];
		work->ptp = ptp;
		INIT_WORK(&work->work, proc_ptp_work);
		init_completion(&work->done);
	}
}  /* init_ptp_work */

#ifdef CONFIG_PTP_1588_CLOCK
#include "micrel_ptp.c"
#endif

static void ptp_chk_rx_events(struct ptp_info *ptp)
{
	struct ptp_event *event;
	u16 tsi_bit;
	int i;

	for (i = 0; i < MAX_TIMESTAMP_UNIT; i++) {
		int stop;

		stop = false;
		tsi_bit = 1 << i;
		event = &ptp->events[i];
		if (ptp->tsi_used & tsi_bit) {

			/* At least one event. */
			if (event->num || event->expired) {
				if (event->num >= event->max)
					stop = true;
				else if (event->expired &&
					 time_after_eq(jiffies,
					 event->expired)) {
					ptp->reg->read_event(ptp, i);
					stop = true;
				}
			}
		}
		if ((ptp->ts_status & ptp->ts_intr) & tsi_bit) {
			u8 data[24];

			if (ptp->tsi_intr & tsi_bit) {
				data[0] = PTP_CMD_GET_EVENT;
				data[1] = i;
				proc_ptp_get_event(ptp, data);
			}
			if (i == ptp->gps_tsi && ptp->gps_req_time) {
				unsigned long diff = jiffies -
					ptp->gps_req_time;

				if (diff < 2 * ptp->delay_ticks) {
					data[0] = TSM_CMD_GET_GPS_TS;
					proc_tsm_get_gps(ptp, data);
					ptp->gps_time.sec = 0;
				}
				ptp->gps_req_time = 0;
			}

			/* Not used in cascade mode. */
			if (!event->timeout && !event->last) {
				event->num = 0;
				event->edge = 0;
				ptp->reg->rx_restart(ptp, i);
				stop = false;
			}
		}
		if (stop) {
			ptp->reg->rx_off(ptp, i);
			ptp->tsi_intr &= ~tsi_bit;
			ptp->tsi_used &= ~tsi_bit;
			ptp->tsi_dev[i] = NULL;
			ptp->events[i].timeout = 0;
			if (i + 1 == event->last) {
				int tsi;
				int last;

				tsi = event->first;
				last = event->last;
				do {
					if (tsi >= MAX_TIMESTAMP_UNIT)
						tsi = 0;
					ptp->events[tsi].first = 0;
					ptp->events[tsi].last = 0;
					++tsi;
				} while (tsi != last);
			}
		}
	}
}  /* ptp_chk_rx_events */

static void ptp_update_sec(struct work_struct *work)
{
	struct delayed_work *dwork = to_delayed_work(work);
	struct ptp_info *ptp =
		container_of(dwork, struct ptp_info, update_sec);

	if (ptp->update_sec_jiffies) {
		ptp->ops->acquire(ptp);
		ptp->reg->get_time(ptp, &ptp->cur_time);
		ptp->ops->release(ptp);
		if (ptp->cur_time.nsec >= 999000000) {
			ptp->cur_time.nsec = 0;
			ptp->cur_time.sec++;
		}
		ptp->sec_lo++;
		if (!(ptp->sec_lo & 3)) {
			check_expired_msg(ptp, ptp->rx_msg_info,
				&ptp->rx_msg_lock, NULL);
			check_expired_msg(ptp, ptp->tx_msg_info,
				&ptp->tx_msg_lock, &ptp->tx_msg_cnt);
		}
		ptp->ops->acquire(ptp);
		ptp_chk_rx_events(ptp);
		ptp->ops->release(ptp);
		schedule_delayed_work(&ptp->update_sec, msecs_to_jiffies(1000));
	}
}  /* ptp_update_sec */

static u32 _get_clk_cnt(void)
{
	return 0;
}

#define ACCESS_VAL			1000

static void test_get_time(struct ptp_info *ptp, struct ptp_utime *cur,
	struct ptp_utime *now, u32 *cur_cnt, u32 *now_cnt)
{
	ptp->reg->get_time(ptp, cur);
	*cur_cnt = ptp->get_clk_cnt();
	ptp->reg->get_time(ptp, now);
	*now_cnt = ptp->get_clk_cnt();
}

static void test_set_time(struct ptp_info *ptp, struct ptp_utime *cur,
	struct ptp_utime *now, u32 *cur_cnt, u32 *now_cnt)
{
	*cur_cnt = ptp->get_clk_cnt();
	ptp->reg->set_time(ptp, cur);
	*now_cnt = ptp->get_clk_cnt();
	ptp->reg->get_time(ptp, now);
}

static u32 test_avg_time(struct ptp_info *ptp,
	void (*test_time)(struct ptp_info *ptp, struct ptp_utime *cur,
	struct ptp_utime *now, u32 *cur_cnt, u32 *now_cnt))
{
	struct ptp_utime cur;
	struct ptp_utime now;
	struct ksz_ptp_time diff;
	int i;
	int clk_delay[6];
	u32 cur_cnt;
	u32 now_cnt;
	u32 hw_delay[6];
	u64 clk;

	cur.sec = 5;
	cur.nsec = 0x12345678;
	ptp->ops->acquire(ptp);
	for (i = 0; i < 5; i++) {
		test_time(ptp, &cur, &now, &cur_cnt, &now_cnt);
		calc_udiff(&cur, &now, &diff);
		clk_delay[i] = (diff.nsec + (ACCESS_VAL / 2)) / ACCESS_VAL *
			ACCESS_VAL;
		hw_delay[i] = now_cnt - cur_cnt;
	}
	ptp->ops->release(ptp);
	clk_delay[5] = 20000000;
	hw_delay[5] = 50000000;
	for (i = 0; i < 5; i++) {
		clk = hw_delay[i];
		clk *= 1000000;
		if (ptp->clk_divider)
			clk = div_u64_u32(clk, ptp->clk_divider);
		dbg_msg(" %u %u=%llu"NL, clk_delay[i], hw_delay[i], clk);
		if (clk_delay[i] < clk_delay[5])
			clk_delay[5] = clk_delay[i];
		if (hw_delay[i] < hw_delay[5])
			hw_delay[5] = hw_delay[i];
	}
	clk = hw_delay[5];
	clk *= 1000000;
	if (ptp->clk_divider)
		clk = div_u64_u32(clk, ptp->clk_divider);
	dbg_msg("%u %llu"NL, clk_delay[5], clk);
	return clk_delay[5];
}

static void _test_access_time(struct ptp_info *ptp)
{
	ptp->get_delay = test_avg_time(ptp, test_get_time);
	ptp->set_delay = test_avg_time(ptp, test_set_time);
	if (ptp->get_delay < 10000)
		ptp->delay_ticks = 10 * HZ / 1000;
	else if (ptp->get_delay < 12000000)
		ptp->delay_ticks = 20 * HZ / 1000;
	else
		ptp->delay_ticks = 30 * HZ / 1000;
	dbg_msg("delay_ticks: %lu"NL, ptp->delay_ticks);
}  /* test_access_time */

#ifndef NO_PPS_DETECT
static void set_ptp_drift(struct ptp_info *ptp, int drift)
{
	drift /= 100;
	drift *= 100;
	drift = -drift;
	ptp->first_drift = ptp->drift = drift;
	ptp->first_sec = 0;
	ptp->adjust = clk_adjust_val(drift, NANOSEC_IN_SEC);
	set_ptp_adjust(ptp, ptp->adjust);
	syntonize_clk(ptp);
	ptp->ptp_synt = true;
	dbg_msg("drift: %d"NL, drift);
}  /* set_ptp_drift */

static void check_sys_time(struct ptp_info *ptp, unsigned long cur_jiffies,
	ktime_t cur_ktime)
{
	int diff;
	int interval;
	u32 cur_clk_cnt;

	cur_clk_cnt = ptp->get_clk_cnt();
	if (!ptp->first_drift) {
		interval = 8;
		diff = ptp->cur_time.sec - ptp->intr_sec;

		/*
		 * The second interval is not accurate after first setting up
		 * the clock until later.
		 */
		if (diff < 6)
			ptp->first_sec = 0;
	} else
		interval = 10;

	if (!ptp->first_sec) {
		ptp->last_clk_cnt = cur_clk_cnt;
		ptp->total_clk_cnt = 0;
		ptp->last_jiffies = cur_jiffies;
		ptp->total_jiffies = 0;
		ptp->first_ktime = cur_ktime;
		ptp->first_sec = ptp->cur_time.sec;
		return;
	}

	diff = ptp->cur_time.sec - ptp->first_sec;

	if (diff >= 1 && !(diff % interval)) {
		u64 clk;
		u64 clk_cnt;
		s64 drift_clk;
		s64 drift_jiffies;
		s64 drift_ktime;
		u32 passed_sec;
		u64 passed_usec;
		u64 passed_nsec;
		u32 cnt;

		cnt = cur_clk_cnt - ptp->last_clk_cnt;
		ptp->total_clk_cnt += cnt;
		ptp->last_clk_cnt = cur_clk_cnt;

		passed_sec = ptp->cur_time.sec - ptp->first_sec;
		passed_usec = passed_sec;
		passed_usec *= 1000000;
		passed_nsec = passed_usec;
		passed_nsec *= 1000;

		cnt = cur_jiffies - ptp->last_jiffies;
		ptp->total_jiffies += cnt;
		ptp->last_jiffies = cur_jiffies;

		clk = ptp->total_jiffies * (1000000 / HZ);
		drift_jiffies = clk - passed_usec;
		drift_jiffies *= 1000;
		drift_jiffies = div_s64_u32(drift_jiffies, passed_sec);

		cur_ktime -= ptp->first_ktime;
		drift_ktime = cur_ktime - passed_nsec;
		drift_ktime = div_s64_u32(drift_ktime, passed_sec);

		if (!ptp->clk_divider) {
			if (!ptp->first_drift)
				set_ptp_drift(ptp, (int) drift_ktime);
			else
				printk(KERN_INFO "%lld %lld"NL,
					drift_jiffies, drift_ktime);
			return;
		}

		clk_cnt = div_u64_u32(ptp->total_clk_cnt, passed_sec);

		clk = ptp->total_clk_cnt * 1000000;
		clk = div_u64_u32(clk, ptp->clk_divider);
		drift_clk = clk;
		if (drift_clk < 0)
			ptp->overrides &= ~PTP_CHECK_SYS_TIME;
		drift_clk -= passed_nsec;
		drift_clk = div_s64_u32(drift_clk, passed_sec);

		if (!ptp->first_drift)
			set_ptp_drift(ptp, (int) drift_clk);
		else
			printk(KERN_INFO "%10llu %lld %lld %lld"NL,
				clk_cnt, drift_clk, drift_jiffies, drift_ktime);
	}
}  /* check_sys_time */
#endif

static void proc_ptp_intr(struct ptp_info *ptp)
{
	struct ptp_event *event;
	u16 done;
	u16 error;
	u16 status;
	u32 trig_status;
	u32 int_status;
	u16 tsi_bit;
	u8 data[24];
	int i;
	int tsi;
	ktime_t cur_ktime;
	struct timespec64 ts;
	struct ksz_sw *sw = ptp->parent;

	cur_ktime = ktime_get_real();
	ts = ktime_to_timespec64(cur_ktime);

proc_chk_trig_intr:
	int_status = sw->reg->r32(sw, REG_PTP_INT_STATUS__4);
	if (!int_status)
		goto proc_ptp_intr_done;

	sw->reg->w32(sw, REG_PTP_INT_STATUS__4, int_status);

	status = (int_status >> TRIG_INT_S) & PTP_TRIG_UNIT_M;
	if (!status)
		goto proc_chk_ts_intr;

	trig_status = sw->reg->r32(sw, REG_PTP_TRIG_STATUS__4);
	error = (trig_status >> TRIG_ERROR_S) & PTP_TRIG_UNIT_M;
	done = trig_status & PTP_TRIG_UNIT_M;
	for (i = 0; i < MAX_TRIG_UNIT; i++) {
		if (status & (1 << i)) {
			if (ptp->tso_intr & (1 << i)) {
				data[0] = PTP_CMD_GET_OUTPUT;
				data[1] = i;
				proc_ptp_get_trig(ptp, data, done, error);
			}
			ptp_tx_done(ptp, i);
		}
	}
	if (trig_status)
		sw->reg->w32(sw, REG_PTP_TRIG_STATUS__4, trig_status);

proc_chk_ts_intr:
	status = (int_status >> TS_INT_S) & PTP_TS_UNIT_M;
	if (!status)
		goto proc_ptp_port_intr;

	for (i = 0; i < MAX_TIMESTAMP_UNIT; i++) {
		tsi_bit = 1 << i;
		if (!(status & tsi_bit))
			continue;
		ptp->reg->read_event(ptp, i);
		event = &ptp->events[i];
		if (event->timeout &&
		    (event->num < event->max || event->last)) {
			unsigned long expired;

			expired = jiffies + event->timeout;
			if (0 == expired)
				expired = 1;
			event->expired = expired;
			if (event->last) {
				tsi = i + 1;
				while (tsi != event->last) {
					if (tsi >= MAX_TIMESTAMP_UNIT)
						tsi = 0;
					ptp->events[tsi].expired = expired;

					/* Extend timeout for next unit. */
					ptp->events[tsi].timeout =
						event->timeout;
					++tsi;
				}
			}
		}
		if (event->last && i != event->first) {
			tsi = i - 1;
			if (tsi < 0)
				tsi = MAX_TIMESTAMP_UNIT - 1;
			if (ptp->tsi_used & (1 << tsi))
				ptp->events[tsi].expired = jiffies;
		}

		/* For system use only. */
		if (!(ptp->tsi_sys & tsi_bit))
			continue;
#ifndef NO_PPS_DETECT
		if (i == ptp->pps_tsi) {
			struct ptp_utime sys_time;

			ptp->cur_time.sec = event->t[0].sec;
			ptp->cur_time.nsec = event->t[0].nsec;
			ptp->update_sec_jiffies = 0;
			ptp->sec_lo++;
			sys_time.sec = ts.tv_sec;
			sys_time.nsec = ts.tv_nsec;
			calc_udiff(&ptp->cur_time, &sys_time, &ptp->time_diff);
			if (!ptp->intr_sec)
				ptp->intr_sec = ptp->cur_time.sec;
#if 1
			if ((ptp->overrides & PTP_CHECK_SYS_TIME) ||
					!ptp->first_drift)
				check_sys_time(ptp, jiffies, cur_ktime);
#endif
#ifdef CONFIG_PTP_1588_CLOCK
			if (ptp->clock_events & (1 << 0))
				ptp_event_trigger(ptp->clock_info, 0,
					ptp->cur_time.sec, ptp->cur_time.nsec);
			if (ptp->clock_events & (1 << 31))
				ptp_event_pps(ptp->clock_info);
#endif
			if (!(ptp->sec_lo & 3)) {
				check_expired_msg(ptp, ptp->rx_msg_info,
					&ptp->rx_msg_lock, NULL);
				check_expired_msg(ptp, ptp->tx_msg_info,
					&ptp->tx_msg_lock, &ptp->tx_msg_cnt);
			}
		} else if (i == ptp->gps_tsi) {
			ptp->gps_time.sec = event->t[0].sec;
			ptp->gps_time.nsec = event->t[0].nsec;
			++ptp->gps_seqid;
			ptp->gps_resp_time = jiffies;
		}
#endif
	}
	ptp_chk_rx_events(ptp);
	ptp->ts_status = 0;

proc_ptp_port_intr:

	goto proc_chk_trig_intr;

proc_ptp_intr_done:
	return;
}  /* proc_ptp_intr */

static int ptp_get_ts_info(struct ptp_info *ptp, struct net_device *dev,
	struct ethtool_ts_info *info)
{
	int ptp_clock = false;
	struct ksz_sw *sw = ptp->parent;
	int ret = -ENODEV;

#ifdef CONFIG_PTP_1588_CLOCK
	ptp_clock = true;
#endif
	if (!(sw->features & PTP_HW) || !ptp_clock)
		return ethtool_op_get_ts_info(dev, info);
#ifdef CONFIG_PTP_1588_CLOCK
	if (ptp->clock_info)
		ret = micrel_ptp_get_ts_info(ptp, info);
#endif
	return ret;
}  /* ptp_get_ts_info */

static void proc_ptp_tx_intr(struct ptp_info *ptp, uint port)
{
	uint p = port;
	u16 status;
	struct ksz_sw *sw = ptp->parent;

	sw->ops->p_r16(sw, p, REG_PTP_PORT_TX_INT_STATUS__2, &status);
	if (status) {
		sw->ops->p_w16(sw, p, REG_PTP_PORT_TX_INT_STATUS__2, status);
		status &= ptp->tx_intr;
		if (get_tx_time(ptp, port, p, status))
			wake_up_interruptible(&ptp->wait_ts[port]);
	}
}  /* proc_ptp_tx_intr */

#define PTP_ENABLE_TXTS		SIOCDEVPRIVATE
#define PTP_DISABLE_TXTS	(SIOCDEVPRIVATE + 1)
#define PTP_ENABLE_RXTS		(SIOCDEVPRIVATE + 2)
#define PTP_DISABLE_RXTS	(SIOCDEVPRIVATE + 3)
#define PTP_GET_TX_TIMESTAMP	(SIOCDEVPRIVATE + 4)
#define PTP_GET_RX_TIMESTAMP	(SIOCDEVPRIVATE + 5)
#define PTP_SET_TIME		(SIOCDEVPRIVATE + 6)
#define PTP_GET_TIME		(SIOCDEVPRIVATE + 7)
#define PTP_SET_FIPER_ALARM	(SIOCDEVPRIVATE + 8)
#define PTP_SET_ADJ		(SIOCDEVPRIVATE + 9)
#define PTP_GET_ADJ		(SIOCDEVPRIVATE + 10)
#define PTP_CLEANUP_TS		(SIOCDEVPRIVATE + 11)
#define PTP_ADJ_TIME		(SIOCDEVPRIVATE + 12)

struct ixxat_ptp_time {
	/* just 48 bit used */
	u64 sec;
	u32 nsec;
};

struct ixxat_ptp_ident {
	u8 vers;
	u8 mType;
	u16 netwProt;
	u16 seqId;
	struct ptp_port_identity portId;
} __packed;

/* needed for timestamp data over ioctl */
struct ixxat_ptp_data {
	struct ixxat_ptp_ident ident;
	struct ixxat_ptp_time ts;
};

static int ixxat_ptp_ioctl(struct ptp_info *ptp, unsigned int cmd,
	struct ifreq *ifr)
{
	struct ixxat_ptp_time ptp_time;
	struct ixxat_ptp_data ptp_data;
	struct ptp_clk_options clk_opt;
	int output;
	s64 scaled_nsec;
	struct ptp_ts ts;
	struct ptp_tx_ts *tx;
	int drift;
	int err = 0;
	uint port;
	struct ksz_sw *sw = ptp->parent;

	switch (cmd) {
	case PTP_ENABLE_TXTS:
		ptp->tx_en |= 2;
		break;
	case PTP_DISABLE_TXTS:
		ptp->tx_en &= ~2;
		break;
	case PTP_ENABLE_RXTS:
		ptp->rx_en |= 2;
		break;
	case PTP_DISABLE_RXTS:
		ptp->rx_en &= ~2;
		break;
	case PTP_GET_TX_TIMESTAMP:
		if (copy_from_user(&ptp_data, ifr->ifr_data, sizeof(ptp_data)))
			return -EFAULT;

		err = -EINVAL;
		port = htons(ptp_data.ident.portId.port);
		if (port < 1 || port > ptp->ports)
			break;
		port = get_phy_port(sw, port);
		tx = proc_get_ts(ptp, port, ptp_data.ident.mType,
			ptp_data.ident.seqId,
			ptp_data.ident.portId.clockIdentity.addr,
			NULL, 0);
		if (!tx)
			break;
		ptp_data.ts.sec = tx->ts.r.sec;
		ptp_data.ts.nsec = tx->ts.r.nsec;
		tx->ts.timestamp = 0;
		tx->req_time = 0;
		err = copy_to_user(ifr->ifr_data, &ptp_data, sizeof(ptp_data));
		break;
	case PTP_GET_RX_TIMESTAMP:
		if (copy_from_user(&ptp_data, ifr->ifr_data, sizeof(ptp_data)))
			return -EFAULT;

		ts.timestamp = ptp_data.ts.nsec;
		if (ts.timestamp)
			update_ts(&ts, ptp->cur_time.sec);
		else {
			struct ptp_msg_hdr hdr;
			struct ptp_msg_options tx_msg;
			int found;

			ts.t.sec = ts.t.nsec = 0;
			memcpy(&hdr.sourcePortIdentity, &ptp_data.ident.portId,
				sizeof(struct ptp_port_identity));
			hdr.messageType = ptp_data.ident.mType;
			hdr.sequenceId = htons(ptp_data.ident.seqId);
			hdr.domainNumber = ptp_data.ident.vers;
			found = find_msg_info(&ptp->rx_msg_info[
				hdr.messageType],
				&ptp->rx_msg_lock, &hdr,
				&hdr.sourcePortIdentity,
				PDELAY_REQ_MSG != hdr.messageType, &tx_msg);
			if (found) {
				ts.t = tx_msg.ts.t;
			}
		}
#if 0
printk("%u:%09u"NL, ts.t.sec, ts.t.nsec);
#endif
		ptp_data.ts.sec = ts.t.sec;
		ptp_data.ts.nsec = ts.t.nsec;
		err = copy_to_user(ifr->ifr_data, &ptp_data, sizeof(ptp_data));
		break;
	case PTP_GET_TIME:
	{
		struct timespec64 ts;
		struct ksz_ptp_time cur_time;
		struct ksz_ptp_time sys_time;

		ts = ktime_to_timespec64(ktime_get_real());
		sys_time.sec = ts.tv_sec;
		sys_time.nsec = ts.tv_nsec;
		calc_diff(&ptp->time_diff, &sys_time, &cur_time);
		ptp_time.sec = cur_time.sec;
		ptp_time.nsec = cur_time.nsec;
		err = proc_ptp_hw_access(ptp,
			DEV_CMD_GET, DEV_PTP_CLK, 0,
			&clk_opt, sizeof(clk_opt), NULL, &output,
			true);
		if (err)
			break;
		ptp_time.sec = clk_opt.sec;
		ptp_time.nsec = clk_opt.nsec;
		err = copy_to_user(ifr->ifr_data, &ptp_time, sizeof(ptp_time));
		break;
	}
	case PTP_SET_TIME:
		if (copy_from_user(&ptp_time, ifr->ifr_data, sizeof(ptp_time)))
			return -EFAULT;
		output = 0;
		clk_opt.sec = (u32) ptp_time.sec;
		clk_opt.nsec = ptp_time.nsec;
		err = proc_ptp_hw_access(ptp,
			DEV_CMD_PUT, DEV_PTP_CLK, output,
			&clk_opt, sizeof(clk_opt), NULL, &output,
			true);
		break;
	case PTP_ADJ_TIME:
		if (copy_from_user(&scaled_nsec, ifr->ifr_data, sizeof(s64)))
			return -EFAULT;
		convert_scaled_nsec(scaled_nsec, SCALED_NANOSEC_S,
			&ptp->adjust_sec, &ptp->adjust_offset);
		if (ptp->adjust_offset < 0 || ptp->adjust_sec < 0) {
			output = 1;
			ptp->adjust_sec = -ptp->adjust_sec;
			ptp->adjust_offset = -ptp->adjust_offset;
		} else
			output = 2;
		clk_opt.sec = (u32) ptp->adjust_sec;
		clk_opt.nsec = ptp->adjust_offset;
		clk_opt.interval = 0;
		ptp->adjust_sec = 0;
		ptp->adjust_offset = 0;
		err = proc_ptp_hw_access(ptp,
			DEV_CMD_PUT, DEV_PTP_CLK, output,
			&clk_opt, sizeof(clk_opt), NULL, &output,
			true);
		break;
	case PTP_SET_ADJ:
		if (copy_from_user(&drift, ifr->ifr_data, sizeof(drift)))
			return -EFAULT;
		output = 1;
		clk_opt.sec = clk_opt.nsec = 0;
		clk_opt.drift = drift;
		clk_opt.interval = NANOSEC_IN_SEC;
		err = proc_ptp_hw_access(ptp,
			DEV_CMD_PUT, DEV_PTP_CLK, output,
			&clk_opt, sizeof(clk_opt), NULL, &output,
			true);
		break;
	case PTP_GET_ADJ:
		drift = ptp->drift;
		err = copy_to_user(ifr->ifr_data, &drift, sizeof(drift));
		break;
	case PTP_CLEANUP_TS:
		break;
	case PTP_SET_FIPER_ALARM:
		break;
	default:
		err = -EOPNOTSUPP;
	}
	return err;
}

static int ptp_dev_req(struct ptp_info *ptp, char *arg,
	struct file_dev_info *info)
{
	struct ksz_request *req = (struct ksz_request *) arg;
	int len;
	int maincmd;
	int req_size;
	int subcmd;
	int output;
	u8 data[PARAM_DATA_SIZE];
	struct file_dev_info *dev;
	int err = 0;
	int result = 0;
	int v2 = 0;

	/* Assume success. */
	result = DEV_IOC_OK;

	/* Check request size. */
	__get_user(req_size, &req->size);
	if (chk_ioctl_size(req_size, SIZEOF_ksz_request, 0, &req_size,
			&result, NULL, NULL))
		goto dev_ioctl_resp;

	err = 0;
	__get_user(maincmd, &req->cmd);
	__get_user(subcmd, &req->subcmd);
	__get_user(output, &req->output);
	len = req_size - SIZEOF_ksz_request;
	switch (maincmd) {
	case DEV_CMD_INFO:
		switch (subcmd) {
		case DEV_INFO_INIT:
		{
			struct ksz_sw *sw = ptp->parent;
			int p = ptp->ports;

			if (chk_ioctl_size(len, 6,
					SIZEOF_ksz_request,
					&req_size, &result, &req->param, data))
				goto dev_ioctl_resp;

			if (len >= 8 &&
			    'v' == data[4] && '2' == data[5])
				v2 = 1;
			result = proc_ptp_hw_access(ptp,
				maincmd, subcmd, output,
				data, len, info, &output,
				true);
			__put_user(output, &req->output);
			data[0] = 'M';
			data[1] = 'i';
			data[2] = 'c';
			data[3] = 'r';
			data[4] = ptp->version;
			if (v2) {
				++p;
				data[6] = sw->HOST_PORT + 1;
				data[7] = 0;
			}
			data[5] = p;
			if (!access_ok(req->param.data, len) ||
			    copy_to_user(req->param.data, data, len)) {
				err = -EFAULT;
				goto dev_ioctl_done;
			}
			break;
		}
		case DEV_INFO_EXIT:
			result = proc_ptp_hw_access(ptp,
				maincmd, subcmd, output,
				data, 0, info, &output,
				true);

		/* fall through */
		case DEV_INFO_QUIT:
			if (!info)
				break;
			data[0] = 0xF0;
			dev = find_minor_dev(info);
			if (dev)
				file_dev_setup_msg(dev, data, 4, NULL, NULL);
			file_dev_setup_msg(info, data, 4, NULL, NULL);
			break;
		case DEV_INFO_RESET:
			if (output < 3) {
				result = proc_ptp_hw_access(ptp,
					maincmd, subcmd, output,
					data, 0, info, &output,
					false);
			} else
				result = -EINVAL;
			break;
		case DEV_INFO_PORT:
			if (len < 6) {
				result = DEV_IOC_INVALID_LEN;
				break;
			}
			if (chk_ioctl_size(len, len,
					SIZEOF_ksz_request,
					&req_size, &result, &req->param, data))
				goto dev_ioctl_resp;

			result = proc_ptp_hw_access(ptp,
				maincmd, subcmd, output,
				data, len, info, &output,
				true);
			if (!result) {
				len = 6;
				__put_user(output, &req->output);
				if (!access_ok(req->param.data,
				    len) ||
				    copy_to_user(req->param.data, data, len)) {
					err = -EFAULT;
					goto dev_ioctl_done;
				}
			}
			break;
		default:
			result = DEV_IOC_INVALID_CMD;
			break;
		}
		break;
	case DEV_CMD_PUT:
		switch (subcmd) {
		case DEV_PTP_CFG:
			if (chk_ioctl_size(len, sizeof(struct ptp_cfg_options),
					SIZEOF_ksz_request,
					&req_size, &result, &req->param, data))
				goto dev_ioctl_resp;
			result = proc_ptp_hw_access(ptp,
				maincmd, subcmd, 0,
				data, len, info, &output,
				false);
			break;
		case DEV_PTP_TEVT:
			if (chk_ioctl_size(len, sizeof(struct ptp_tsi_options),
					SIZEOF_ksz_request,
					&req_size, &result, &req->param, data))
				goto dev_ioctl_resp;
			if (!info) {
				err = -EFAULT;
				goto dev_ioctl_done;
			}
			result = proc_ptp_hw_access(ptp,
				maincmd, subcmd, output,
				data, len, info, &output,
				true);
			__put_user(output, &req->output);
			break;
		case DEV_PTP_TOUT:
			if (chk_ioctl_size(len, sizeof(struct ptp_tso_options),
					SIZEOF_ksz_request,
					&req_size, &result, &req->param, data))
				goto dev_ioctl_resp;
			if (!info) {
				err = -EFAULT;
				goto dev_ioctl_done;
			}
			result = proc_ptp_hw_access(ptp,
				maincmd, subcmd, output,
				data, len, info, &output,
				true);
			__put_user(output, &req->output);
			break;
		case DEV_PTP_CASCADE:
			if (chk_ioctl_size(len, sizeof(struct ptp_tso_options),
					SIZEOF_ksz_request,
					&req_size, &result, &req->param, data))
				goto dev_ioctl_resp;
			result = proc_ptp_hw_access(ptp,
				maincmd, subcmd, output,
				data, len, info, &output,
				true);
			__put_user(output, &req->output);
			break;
		case DEV_PTP_CLK:
			if (chk_ioctl_size(len, sizeof(struct ptp_clk_options),
					SIZEOF_ksz_request,
					&req_size, &result, &req->param, data))
				goto dev_ioctl_resp;
			result = proc_ptp_hw_access(ptp,
				maincmd, subcmd, output,
				data, len, info, &output,
				true);
			break;
		case DEV_PTP_DELAY:
			if (chk_ioctl_size(len,
					sizeof(struct ptp_delay_values),
					SIZEOF_ksz_request,
					&req_size, &result, &req->param, data))
				goto dev_ioctl_resp;
			result = proc_ptp_hw_access(ptp,
				maincmd, subcmd, output,
				data, len, info, &output,
				true);
			break;
		case DEV_PTP_REG:
			if ((ptp->op_mode > 0 || ptp->cap) &&
			    chk_ioctl_size(len,
					sizeof(u32) * 3,
					SIZEOF_ksz_request,
					&req_size, &result, &req->param, data))
				goto dev_ioctl_resp;
			result = proc_ptp_hw_access(ptp,
				maincmd, subcmd, output,
				data, len, info, &output,
				false);
			break;
		case DEV_PTP_IDENTITY:
			if (chk_ioctl_size(len,
					sizeof(struct ptp_clock_identity),
					SIZEOF_ksz_request,
					&req_size, &result, &req->param, data))
				goto dev_ioctl_resp;
			if ((ptp->op_mode > 0 || ptp->cap) && output) {
				memcpy(&ptp->masterIdentity, data,
					sizeof(struct ptp_clock_identity));
				break;
			}
			memcpy(&ptp->clockIdentity, data,
				sizeof(struct ptp_clock_identity));
			break;
		case DEV_PTP_PEER_DELAY:
			if (chk_ioctl_size(len,
					sizeof(struct ptp_delay_values),
					SIZEOF_ksz_request,
					&req_size, &result, &req->param, data))
				goto dev_ioctl_resp;
			result = proc_ptp_hw_access(ptp,
				maincmd, subcmd, output,
				data, len, info, &output,
				true);
			break;
		case DEV_PTP_UTC_OFFSET:
			ptp->utc_offset = output;
			break;
		case DEV_PTP_MSG:
			if (chk_ioctl_size(len,
					sizeof(struct ptp_msg_options),
					SIZEOF_ksz_request,
					&req_size, &result, &req->param, data))
				goto dev_ioctl_resp;
			result = proc_ptp_set_msg_info(ptp, data, info);
			break;
		case DEV_PTP_PORT_CFG:
			if (chk_ioctl_size(len,
					sizeof(struct ptp_delay_values),
					SIZEOF_ksz_request,
					&req_size, &result, &req->param, data))
				goto dev_ioctl_resp;
			result = proc_ptp_hw_access(ptp,
				maincmd, subcmd, output,
				data, len, info, &output,
				true);
			break;
		default:
			result = DEV_IOC_INVALID_CMD;
			break;
		}
		break;
	case DEV_CMD_GET:
		switch (subcmd) {
		case DEV_PTP_CFG:
			if (chk_ioctl_size(len, sizeof(struct ptp_cfg_options),
					SIZEOF_ksz_request,
					&req_size, &result, NULL, NULL))
				goto dev_ioctl_resp;
			result = proc_ptp_hw_access(ptp,
				maincmd, subcmd, 0,
				data, len, info, &output,
				true);
			if (!access_ok(req->param.data,
					sizeof(struct ptp_cfg_options)) ||
					copy_to_user(req->param.data, data,
					sizeof(struct ptp_cfg_options))) {
				err = -EFAULT;
				goto dev_ioctl_done;
			}
			break;
		case DEV_PTP_TEVT:
			if (chk_ioctl_size(len, sizeof(struct ptp_tsi_info),
					SIZEOF_ksz_request,
					&req_size, &result, &req->param, data))
				goto dev_ioctl_resp;
			if (!info) {
				err = -EFAULT;
				goto dev_ioctl_done;
			}
			if (output) {
				int wait = false;

				if (2 == output)
					wait = true;
				result = proc_ptp_hw_access(ptp,
					maincmd, subcmd, output,
					data, len, info, &output,
					wait);
				if (!wait)
					break;
				if (!access_ok(req->param.data,
				    len) || copy_to_user(req->param.data,
				    data, len)) {
					err = -EFAULT;
					goto dev_ioctl_done;
				}
			} else
				result = proc_dev_get_event(info, data);
			break;
		case DEV_PTP_TOUT:
			if (chk_ioctl_size(len, sizeof(struct ptp_tso_options),
					SIZEOF_ksz_request,
					&req_size, &result, &req->param, data))
				goto dev_ioctl_resp;
			result = proc_ptp_get_output(ptp, data);
			output = *((int *) data);
			__put_user(output, &req->output);
			break;
		case DEV_PTP_CLK:
			if (chk_ioctl_size(len, sizeof(struct ptp_clk_options),
					SIZEOF_ksz_request,
					&req_size, &result, NULL, NULL))
				goto dev_ioctl_resp;
			if (0 == ptp->op_mode && !ptp->cap)
				output = 0;
			result = proc_ptp_hw_access(ptp,
				maincmd, subcmd, output,
				data, len, info, &output,
				true);
			__put_user(output, &req->output);
			if (!access_ok(req->param.data,
					sizeof(struct ptp_clk_options)) ||
					copy_to_user(req->param.data, data,
					sizeof(struct ptp_clk_options))) {
				err = -EFAULT;
				goto dev_ioctl_done;
			}
			break;
		case DEV_PTP_DELAY:
			if (chk_ioctl_size(len,
					sizeof(struct ptp_delay_values),
					SIZEOF_ksz_request,
					&req_size, &result, NULL, NULL))
				goto dev_ioctl_resp;
			result = proc_ptp_hw_access(ptp,
				maincmd, subcmd, output,
				data, len, info, &output,
				true);
			if (!access_ok(req->param.data,
					sizeof(struct ptp_delay_values)) ||
					copy_to_user(req->param.data, data,
					sizeof(struct ptp_delay_values))) {
				err = -EFAULT;
				goto dev_ioctl_done;
			}
			break;
		case DEV_PTP_REG:
			if ((ptp->op_mode > 0 || ptp->cap) &&
			    chk_ioctl_size(len,
					sizeof(u32) * 3,
					SIZEOF_ksz_request,
					&req_size, &result, &req->param, data))
				goto dev_ioctl_resp;
			result = proc_ptp_hw_access(ptp,
				maincmd, subcmd, output,
				data, len, info, &output,
				true);
			__put_user(output, &req->output);
			break;
		case DEV_PTP_IDENTITY:
		{
			struct ptp_clock_identity *id = &ptp->clockIdentity;

			if ((ptp->op_mode > 0 || ptp->cap) && output)
				id = &ptp->masterIdentity;
			if (!access_ok(req->param.data,
					sizeof(struct ptp_clock_identity)) ||
					copy_to_user(req->param.data, id,
					sizeof(struct ptp_clock_identity))) {
				err = -EFAULT;
				goto dev_ioctl_done;
			}
			break;
		}
		case DEV_PTP_PEER_DELAY:
			if (chk_ioctl_size(len,
					sizeof(struct ptp_delay_values),
					SIZEOF_ksz_request,
					&req_size, &result, NULL, NULL))
				goto dev_ioctl_resp;
			result = proc_ptp_hw_access(ptp,
				maincmd, subcmd, output,
				data, len, info, &output,
				true);
			if (!access_ok(req->param.data,
					sizeof(struct ptp_delay_values)) ||
					copy_to_user(req->param.data, data,
					sizeof(struct ptp_delay_values))) {
				err = -EFAULT;
				goto dev_ioctl_done;
			}
			break;
		case DEV_PTP_UTC_OFFSET:
			__put_user(ptp->utc_offset, &req->output);
			break;
		case DEV_PTP_TIMESTAMP:
			if (chk_ioctl_size(len,
					sizeof(struct ptp_ts_options),
					SIZEOF_ksz_request,
					&req_size, &result, &req->param, data))
				goto dev_ioctl_resp;
			result = proc_ptp_get_timestamp(ptp, data, info);
			if (result)
				goto dev_ioctl_resp;
			if (!access_ok(req->param.data,
					sizeof(struct ptp_ts_options)) ||
					copy_to_user(req->param.data, data,
					sizeof(struct ptp_ts_options))) {
				err = -EFAULT;
				goto dev_ioctl_done;
			}
			break;
		case DEV_PTP_MSG:
			if (chk_ioctl_size(len,
					sizeof(struct ptp_msg_options),
					SIZEOF_ksz_request,
					&req_size, &result, &req->param, data))
				goto dev_ioctl_resp;
			result = proc_ptp_get_msg_info(ptp, data, info,
				&output);
			__put_user(output, &req->output);
			if (result)
				goto dev_ioctl_resp;
			if (!access_ok(req->param.data,
					sizeof(struct ptp_msg_options)) ||
					copy_to_user(req->param.data, data,
					sizeof(struct ptp_msg_options))) {
				err = -EFAULT;
				goto dev_ioctl_done;
			}
			break;
		case DEV_PTP_PORT_CFG:
			if (chk_ioctl_size(len,
					sizeof(struct ptp_delay_values),
					SIZEOF_ksz_request,
					&req_size, &result, NULL, NULL))
				goto dev_ioctl_resp;
			result = proc_ptp_hw_access(ptp,
				maincmd, subcmd, output,
				data, len, info, &output,
				true);
			if (!access_ok(req->param.data,
					sizeof(struct ptp_delay_values)) ||
					copy_to_user(req->param.data, data,
					sizeof(struct ptp_delay_values))) {
				err = -EFAULT;
				goto dev_ioctl_done;
			}
			break;
		default:
			result = DEV_IOC_INVALID_CMD;
			break;
		}
		break;
	default:
		result = DEV_IOC_INVALID_CMD;
		break;
	}

dev_ioctl_resp:
	__put_user(req_size, &req->size);
	__put_user(result, &req->result);

	/* Return ERESTARTSYS so that the system call is called again. */
	if (result < 0)
		err = result;

dev_ioctl_done:
	return err;
}  /* ptp_dev_req */

static long ptp_dev_ioctl(struct file *filp, unsigned int cmd,
	unsigned long arg)
{
	struct file_dev_info *info = (struct file_dev_info *)
		filp->private_data;
	struct ptp_info *ptp = info->dev;
	int err = 0;

	if (_IOC_TYPE(cmd) != DEV_IOC_MAGIC)
		return -ENOTTY;
	if (_IOC_NR(cmd) > DEV_IOC_MAX)
		return -ENOTTY;
	if (_IOC_DIR(cmd) & _IOC_READ)
		err = !access_ok((void *) arg, _IOC_SIZE(cmd));
	else if (_IOC_DIR(cmd) & _IOC_WRITE)
		err = !access_ok((void *) arg, _IOC_SIZE(cmd));
	if (err) {
		printk(KERN_ALERT "err fault"NL);
		return -EFAULT;
	}
	if (down_interruptible(&info->sem))
		return -ERESTARTSYS;

	err = ptp_dev_req(ptp, (char *) arg, info);
	up(&info->sem);
	return err;
}  /* ptp_dev_ioctl */

static ssize_t ptp_dev_read(struct file *filp, char *buf, size_t count,
	loff_t *offp)
{
	struct file_dev_info *info = (struct file_dev_info *)
		filp->private_data;
	ssize_t result = 0;
	int rc;

	if (!info->read_len) {
		*offp = 0;
		rc = wait_event_interruptible(info->wait_msg,
			0 != info->read_len);

		/* Cannot continue if ERESTARTSYS. */
		if (rc < 0)
			return 0;
	}

	if (down_interruptible(&info->sem))
		return -ERESTARTSYS;

	mutex_lock(&info->lock);
	if (*offp >= info->read_len) {
		info->read_len = 0;
		count = 0;
		*offp = 0;
		goto dev_read_done;
	}

	if (*offp + count > info->read_len) {
		count = info->read_len - *offp;
		info->read_len = 0;
	}

	if (copy_to_user(buf, &info->read_buf[*offp], count)) {
		result = -EFAULT;
		goto dev_read_done;
	}
	if (info->read_len)
		*offp += count;
	else
		*offp = 0;
	result = count;

dev_read_done:
	mutex_unlock(&info->lock);
	up(&info->sem);
	return result;
}  /* ptp_dev_read */

static ssize_t ptp_dev_write(struct file *filp, const char *buf, size_t count,
	loff_t *offp)
{
	struct file_dev_info *info = (struct file_dev_info *)
		filp->private_data;
	ssize_t result = 0;
	size_t size;
	int rc;
	u8 cmd;

	if (!count)
		return result;

	if (down_interruptible(&info->sem))
		return -ERESTARTSYS;

	if (*offp >= info->write_len) {
		result = -ENOSPC;
		goto dev_write_done;
	}
	if (*offp + count > info->write_len)
		count = info->write_len - *offp;
	if (copy_from_user(info->write_buf, buf, count)) {
		result = -EFAULT;
		goto dev_write_done;
	}
	cmd = info->write_buf[0] & 0xf0;
	switch (cmd) {
	case TSM_CMD_GET_GPS_TS:
		size = sizeof(struct tsm_get_gps);
		break;
	case TSM_CMD_DB_GET_TIME:
		size = sizeof(struct tsm_get_time);
		break;
	case TSM_CMD_DB_GET:
		size = sizeof(struct tsm_db);
		break;
	case TSM_CMD_CNF_SET:
		size = sizeof(struct tsm_cfg);
		break;
	case TSM_CMD_CLOCK_SET:
		size = sizeof(struct tsm_clock_set);
		break;
	case TSM_CMD_CLOCK_CORRECT:
		size = sizeof(struct tsm_clock_correct);
		break;
	default:
		dbg_msg("tsm: %x"NL, info->write_buf[0]);
		result = count;
		goto dev_write_done;
	}
	if (count < size) {
		result = -EFAULT;
		goto dev_write_done;
	}
	result = size;
	rc = parse_tsm_msg(info, count);
	if (rc)
		result = rc;

dev_write_done:
	up(&info->sem);
	return result;
}  /* ptp_dev_write */

static struct ksz_dev_major ptp_majors[MAX_SW_DEVICES];

static struct file_dev_info *alloc_dev_info(struct ptp_info *ptp, uint minor)
{
	struct file_dev_info *info;

	info = kzalloc(sizeof(struct file_dev_info), GFP_KERNEL);
	if (info) {
		info->dev = ptp;
		sema_init(&info->sem, 1);
		mutex_init(&info->lock);
		init_waitqueue_head(&info->wait_msg);
		info->read_max = 60000;
		info->read_tmp = MAX_TSM_UDP_LEN;
		info->read_buf = kzalloc(info->read_max + info->read_tmp,
			GFP_KERNEL);
		info->read_in = &info->read_buf[info->read_max];
		info->write_len = 1000;
		info->write_buf = kzalloc(info->write_len, GFP_KERNEL);

		info->minor = minor;
		info->next = ptp->dev[minor];
		ptp->dev[minor] = info;
	}
	return info;
}  /* alloc_dev_info */

static void free_dev_info(struct file_dev_info *info)
{
	if (info) {
		int i;
		struct ptp_info *ptp = info->dev;
		uint minor = info->minor;

		for (i = 0; i < MAX_TIMESTAMP_UNIT; i++) {
			if (ptp->tsi_dev[i] == info) {
				cancel_rx_unit(ptp, i);
			}
		}
		for (i = 0; i < MAX_TRIG_UNIT; i++) {
			if (ptp->tso_dev[i] == info) {
				ptp->ops->acquire(ptp);
				ptp_tso_off(ptp, i, (1 << i));
				ptp->ops->release(ptp);
			}
		}
		if (ptp->gps_dev == info)
			ptp->gps_dev = NULL;
		file_gen_dev_release(info, &ptp->dev[minor]);
	}
}  /* free_dev_info */

static int ptp_dev_open(struct inode *inode, struct file *filp)
{
	struct file_dev_info *info = (struct file_dev_info *)
		filp->private_data;
	uint minor = MINOR(inode->i_rdev);
	uint major = MAJOR(inode->i_rdev);
	struct ptp_info *ptp = NULL;
	int i;

	if (minor > 1)
		return -ENODEV;
	for (i = 0; i < MAX_SW_DEVICES; i++) {
		if (ptp_majors[i].major == major) {
			ptp = ptp_majors[i].dev;
			break;
		}
	}
	if (!ptp)
		return -ENODEV;
	if (!info) {
		info = alloc_dev_info(ptp, minor);
		if (info)
			filp->private_data = info;
		else
			return -ENOMEM;
	}
	return 0;
}  /* ptp_dev_open */

static int ptp_dev_release(struct inode *inode, struct file *filp)
{
	struct file_dev_info *info = (struct file_dev_info *)
		filp->private_data;

	free_dev_info(info);
	filp->private_data = NULL;
	return 0;
}  /* ptp_dev_release */

static const struct file_operations ptp_dev_fops = {
	.read		= ptp_dev_read,
	.write		= ptp_dev_write,
	.unlocked_ioctl	= ptp_dev_ioctl,
	.open		= ptp_dev_open,
	.release	= ptp_dev_release,
};

static struct class *ptp_class[MAX_SW_DEVICES];

static int init_ptp_device(int id, int dev_major, char *dev_name,
			   char *minor_name)
{
	int result;

	result = register_chrdev(dev_major, dev_name, &ptp_dev_fops);
	if (result < 0) {
		printk(KERN_WARNING "%s: can't get major %d"NL, dev_name,
			dev_major);
		return result;
	}
	if (0 == dev_major)
		dev_major = result;
	ptp_class[id] = class_create(THIS_MODULE, dev_name);
	if (IS_ERR(ptp_class[id])) {
		unregister_chrdev(dev_major, dev_name);
		return -ENODEV;
	}
	device_create(ptp_class[id], NULL, MKDEV(dev_major, 0), NULL,
		      dev_name);
	device_create(ptp_class[id], NULL, MKDEV(dev_major, 1), NULL,
		      minor_name);
	return dev_major;
}  /* init_ptp_device */

static void exit_ptp_device(int id, int dev_major, char *dev_name)
{
	device_destroy(ptp_class[id], MKDEV(dev_major, 1));
	device_destroy(ptp_class[id], MKDEV(dev_major, 0));
	class_destroy(ptp_class[id]);
	unregister_chrdev(dev_major, dev_name);
}  /* exit_ptp_device */

static void ptp_set_identity(struct ptp_info *ptp, u8 *addr)
{
	memcpy(&ptp->clockIdentity.addr[0], &addr[0], 3);
	ptp->clockIdentity.addr[3] = 0xFF;
	ptp->clockIdentity.addr[4] = 0xFE;
	memcpy(&ptp->clockIdentity.addr[5], &addr[3], 3);
}  /* ptp_set_identity */

static void ptp_init(struct ptp_info *ptp, u8 *mac_addr)
{
	uint i;
	uint n;
	int latency[2][3];
	struct ksz_port_cfg *cfg;
	struct ksz_sw *sw = ptp->parent;

	ptp->utc_offset = CURRENT_UTC_OFFSET;
	ptp->get_delay = 100000;
	ptp->set_delay = 100000;
	ptp->delay_ticks = 2;
	ptp->access = create_singlethread_workqueue("ptp_access");
	init_ptp_work(ptp);
	mutex_init(&ptp->lock);
	for (n = 0; n < MAX_PTP_PORT; n++)
		init_waitqueue_head(&ptp->wait_ts[n]);
	init_waitqueue_head(&ptp->wait_intr);
	INIT_WORK(&ptp->adj_clk, adj_clock);
	INIT_WORK(&ptp->set_latency, set_latency);
	INIT_DELAYED_WORK(&ptp->check_pps, ptp_check_pps);
	INIT_DELAYED_WORK(&ptp->update_sec, ptp_update_sec);
	ptp_set_identity(ptp, mac_addr);

#ifndef ACL_TEST
	ptp->mode = PTP_ENABLE |
		PTP_IPV4_UDP_ENABLE |
		PTP_1STEP;
	ptp->mode |= PTP_IPV6_UDP_ENABLE;
	ptp->mode |= PTP_ETH_ENABLE;
#else
	ptp->mode = PTP_1STEP;
#endif
	ptp->cfg = 0;
	ptp->cfg |= PTP_UNICAST_ENABLE;
	ptp->cfg |= PTP_UDP_CHECKSUM;
#if 1
	ptp->cfg |= PTP_DOMAIN_CHECK;

	/* Pdelay_Req association does not work in 2-step mode anymore. */
	ptp->cfg |= PTP_DELAY_CHECK;
	ptp->cfg |= PTP_SYNC_CHECK;
#endif
	ptp->def_mode = ptp->mode;
	ptp->def_cfg = ptp->cfg;
	ptp->trig_intr = PTP_TRIG_UNIT_M;

	if (!ptp->ports)
		ptp->ports = MAX_PTP_PORT - 1;

	/* KSZ8463: 574 = 415 + 45 + 114 */
	/* KSZ9567 S1: 1246; 616 */
	/* KSZ8463: 70m=908, 100m=1090; 1m=6.07 ns, 483; 582 */
	/* KSZ9567 S1: 70m=1211, 100m = 1369; 1m=5.27 ns, 842; 866 */
	/* KSZ9567 S1: 360 ns */
	/* KSZ9567 S1: 70m=921, 100m = 1072; 1m=5.03 ns, 569; 569 */
	/* KSZ9567 S1: 72 ns */
	/* KSZ9567 S3: 70m=1968, 100m = 2124; 1m=5.20 ns, 1604; 1622 */
	/* KSZ9567 S3: 1080 ns */
	/* KSZ9567 S3: 70m=1012, 100m = 1164; 1m=5.07 ns, 657; 660 */
	/* KSZ9567 S3: 152 ns */

	/* Meinberg LANTIME M1000: 500 ns */
	latency[0][0] = 480;
	latency[1][0] = 150;
	/* Meinberg SyncBox: 800 ns */
	latency[0][1] = 690;
	latency[1][1] = 830;
	/* Meinberg LANTIME M1000: 760 ns */
	latency[0][1] = 720;
	latency[1][1] = 870;
	latency[0][2] = latency[0][1] + 1000;
	latency[1][2] = latency[1][1] + 1000;
	for (n = 1; n <= ptp->ports; n++) {
		i = get_phy_port(sw, n);
		cfg = get_port_cfg(sw, i);
		cfg->ptp_enabled = true;
		if ((sw->features & AVB_SUPPORT) &&
		    !(sw->features & MRP_SUPPORT))
			cfg->asCapable_set = true;
		ptp->rx_latency[i][0] = latency[0][0];
		ptp->tx_latency[i][0] = latency[1][0];
		ptp->rx_latency[i][1] = latency[0][1];
		ptp->tx_latency[i][1] = latency[1][1];
		ptp->rx_latency[i][2] = latency[0][2];
		ptp->tx_latency[i][2] = latency[1][2];
	}
	cfg = get_port_cfg(sw, sw->HOST_PORT);
	cfg->asCapable = true;

	if (!ptp->get_clk_cnt)
		ptp->get_clk_cnt = _get_clk_cnt;
	if (!ptp->test_access_time)
		ptp->test_access_time = _test_access_time;

	ptp->gps_tsi = MAX_TIMESTAMP_UNIT;
	ptp->gps_gpi = DEFAULT_GPS_GPI;
	ptp->pps_gpo = DEFAULT_PPS_GPO;
	if (pps_gpo > MAX_GPIO)
		pps_gpo = 0;
	if (pps_gpo)
		ptp->pps_gpo = pps_gpo - 1;
	ptp->pps_tsi = DEFAULT_PPS_TSI;
	ptp->pps_tso = DEFAULT_PPS_TSO;
	ptp->mhz_gpo = DEFAULT_MHZ_GPO;
	ptp->mhz_tso = DEFAULT_MHZ_TSO;
	if (mhz_gpo > MAX_GPIO)
		mhz_gpo = 0;
	if (mhz_gpo)
		ptp->mhz_gpo = mhz_gpo - 1;

	for (n = 0; n < MAX_TIMESTAMP_UNIT; n++)
		ptp->events[n].max = MAX_TIMESTAMP_EVENT_UNIT;

	init_msg_info(ptp->rx_msg_info, &ptp->rx_msg_lock);
	init_msg_info(ptp->tx_msg_info, &ptp->tx_msg_lock);

	sprintf(ptp->dev_name[0], "ptp_dev");
	sprintf(ptp->dev_name[1], "ptp_event");
	if (sw->id) {
		sprintf(ptp->dev_name[0], "ptp_dev_%u", sw->id);
		sprintf(ptp->dev_name[1], "ptp_event_%u", sw->id);
	}
	ptp->dev_major = init_ptp_device(sw->id, 0, ptp->dev_name[0],
		ptp->dev_name[1]);
	ptp_majors[sw->id].dev = ptp;
	ptp_majors[sw->id].major = ptp->dev_major;

#ifdef CONFIG_PTP_1588_CLOCK_
/* THa  05/30/2018
 * I2C driver is invoked before PPS and PTP, so the clock will not be created.
 */
	micrel_ptp_probe(ptp);
#endif
}  /* ptp_init */

static void ptp_exit(struct ptp_info *ptp)
{
	struct ksz_sw *sw = ptp->parent;

	exit_ptp_work(ptp);
	flush_work(&ptp->adj_clk);
	flush_work(&ptp->set_latency);
	cancel_delayed_work_sync(&ptp->check_pps);
	cancel_delayed_work_sync(&ptp->update_sec);
	if (ptp->access) {
		destroy_workqueue(ptp->access);
		ptp->access = NULL;
	}
	if (ptp->dev_major >= 0)
		exit_ptp_device(sw->id, ptp->dev_major, ptp->dev_name[0]);

#ifdef CONFIG_PTP_1588_CLOCK
	if (ptp->clock_info)
		micrel_ptp_remove(ptp);
#endif
}  /* ptp_exit */

enum {
	PROC_SET_PTP_FEATURES,
	PROC_SET_PTP_OVERRIDES,
	PROC_SET_PTP_VID,
	PROC_SET_PTP_GPIO_1,
	PROC_SET_PTP_GPIO_2,
};

static ssize_t sysfs_ptp_read(struct ptp_info *ptp, int proc_num, ssize_t len,
	char *buf)
{
	switch (proc_num) {
	case PROC_SET_PTP_FEATURES:
		len += sprintf(buf + len, "%08x:"NL, ptp->features);
		len += sprintf(buf + len, "\t%08x = adjust hack"NL,
			PTP_ADJ_HACK);
		len += sprintf(buf + len, "\t%08x = adjust sec"NL,
			PTP_ADJ_SEC);
		break;
	case PROC_SET_PTP_OVERRIDES:
		len += sprintf(buf + len, "%08x:"NL, ptp->overrides);
		len += sprintf(buf + len, "\t%08x = PTP port forwarding"NL,
			(uint)PTP_PORT_FORWARD);
		len += sprintf(buf + len, "\t%08x = PTP port TX forwarding"NL,
			(uint)PTP_PORT_TX_FORWARD);
		len += sprintf(buf + len, "\t%08x = PTP check path delay"NL,
			(uint)PTP_CHECK_PATH_DELAY);
		len += sprintf(buf + len, "\t%08x = PTP verify timestamp"NL,
			(uint)PTP_VERIFY_TIMESTAMP);
		len += sprintf(buf + len, "\t%08x = PTP zero reserved field"NL,
			(uint)PTP_ZERO_RESERVED_FIELD);
		len += sprintf(buf + len, "\t%08x = PTP update pdelay_resp"NL,
			(uint)PTP_UPDATE_PDELAY_RESP_TIME);
		len += sprintf(buf + len, "\t%08x = PTP check system time"NL,
			(uint)PTP_CHECK_SYS_TIME);
		len += sprintf(buf + len, "\t%08x = PTP check sync time"NL,
			(uint)PTP_CHECK_SYNC_TIME);
		break;
	case PROC_SET_PTP_VID:
		len += sprintf(buf + len, "0x%04x"NL, ptp->vid);
		break;
	case PROC_SET_PTP_GPIO_1:
	case PROC_SET_PTP_GPIO_2:
	{
		u32 reg;
		int gpo = (proc_num == PROC_SET_PTP_GPIO_1) ? 0 : 1;
		struct ksz_sw *sw = ptp->parent;

		ptp->ops->acquire(ptp);
		ptp_write_index(ptp, PTP_GPIO_INDEX_S, gpo);
		reg = sw->reg->r32(sw, REG_PTP_CTRL_STAT__4);
		ptp->ops->release(ptp);
		len += sprintf(buf + len, "%d"NL, !(reg & GPIO_MODE_IN));
		break;
	}
	}
	return len;
}

static void sysfs_ptp_write(struct ptp_info *ptp, int proc_num, int num,
	const char *buf)
{
	int changes;

	switch (proc_num) {
	case PROC_SET_PTP_FEATURES:
		if ('0' != buf[0] || 'x' != buf[1])
			sscanf(buf, "%x", &num);
		changes = ptp->features ^ num;
		ptp->features = num;
		break;
	case PROC_SET_PTP_OVERRIDES:
		if ('0' != buf[0] || 'x' != buf[1])
			sscanf(buf, "%x", &num);
		changes = ptp->overrides ^ num;
		if ((changes & PTP_CHECK_SYS_TIME) &&
				(ptp->overrides & PTP_CHECK_SYS_TIME))
			ptp->first_sec = 0;
#ifdef DBG_PROC_SYNC
		if ((changes & PTP_CHECK_SYNC_TIME) &&
				(ptp->overrides & PTP_CHECK_SYNC_TIME)) {
			last_rcv.sec = 0;
			first_recv = 0;
			first_sync = 0;
		}
#endif
		ptp->overrides = num;
		break;
	case PROC_SET_PTP_VID:
		ptp->vid = num;
		break;
	case PROC_SET_PTP_GPIO_1:
	case PROC_SET_PTP_GPIO_2:
	{
		u32 reg;
		int gpo = (proc_num == PROC_SET_PTP_GPIO_1) ? 0 : 1;
		struct ksz_sw *sw = ptp->parent;

		ptp_write_index(ptp, PTP_GPIO_INDEX_S, gpo);
		reg = sw->reg->r32(sw, REG_PTP_CTRL_STAT__4);
		if (num)
			reg &= ~GPIO_MODE_IN;
		else
			reg |= GPIO_MODE_IN;
		sw->reg->w32(sw, REG_PTP_CTRL_STAT__4, reg);
		break;
	}
	}
}

static struct ptp_reg_ops ptp_reg_ops = {
	.get_time		= get_ptp_time,
	.set_time		= set_ptp_time,
	.adjust_time		= adjust_ptp_time,
	.adjust_sync_time	= adjust_sync_time,

	.rx_off			= ptp_rx_off,
	.rx_reset		= ptp_rx_reset,
	.rx_restart		= ptp_rx_restart,
	.rx_event		= ptp_rx_event,
	.rx_cascade_event	= ptp_rx_cascade_event,
	.read_event		= ptp_read_event,

	.tx_off			= ptp_tx_off,
	.tx_event		= ptp_tx_event,
	.pps_event		= ptp_pps_event,
	.ptp_10MHz		= ptp_10MHz,
	.tx_cascade		= ptp_tx_cascade,

	.start			= ptp_start,
};

#ifdef CONFIG_KSZ_IBA
#include "ksz_ptp_iba.c"
#endif

static void ptp_use_iba(struct ptp_info *ptp, bool iba)
{
#ifdef CONFIG_KSZ_IBA
	if (iba)
		ptp->reg = &ptp_iba_ops;
	else
		ptp->reg = &ptp_reg_ops;
#endif
}

static struct ptp_ops ptp_ops = {
	.acquire		= ptp_acquire,
	.release		= ptp_release,
	.use_iba		= ptp_use_iba,

	.init			= ptp_init,
	.exit			= ptp_exit,

	.stop			= ptp_stop,
	.set_identity		= ptp_set_identity,

	.check_msg		= check_ptp_msg,
	.get_rx_tstamp		= get_rx_tstamp,
	.get_tx_tstamp		= get_tx_tstamp,
	.hwtstamp_ioctl		= ptp_hwtstamp_ioctl,
	.ixxat_ioctl		= ixxat_ptp_ioctl,
	.dev_req		= ptp_dev_req,
	.proc_intr		= proc_ptp_intr,
	.proc_tx_intr		= proc_ptp_tx_intr,
	.get_ts_info		= ptp_get_ts_info,

	.sysfs_read		= sysfs_ptp_read,
	.sysfs_write		= sysfs_ptp_write,

	.drop_pkt		= ptp_drop_pkt,
	.get_rx_info		= ptp_get_rx_info,
	.set_tx_info		= ptp_set_tx_info,
};

