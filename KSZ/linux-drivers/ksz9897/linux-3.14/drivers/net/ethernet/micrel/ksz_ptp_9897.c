/**
 * Micrel PTP common code
 *
 * Copyright (c) 2015 Microchip Technology Inc.
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


#if 0
#define ENABLE_10_MHZ_CLK
#endif


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
		t3 = div_s64_rem(diff, NSEC_PER_SEC, &rem);
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

#ifdef PTP_PROCESS
static void calc_diff64(struct ptp_ltime *prev, struct ptp_ltime *cur,
	struct ptp_ltime *result)
{
	struct ptp_ltime diff;
	s64 prev_nsec = prev->nsec;
	s64 cur_nsec = cur->nsec;
	s64 scaled_nsec = (s64) NANOSEC_IN_SEC << SCALED_NANOSEC_S;

	if (prev->sec < 0)
		prev_nsec = -prev_nsec;
	if (cur->sec < 0)
		cur_nsec = -cur_nsec;
	diff.sec = cur->sec - prev->sec;
	diff.nsec = cur_nsec - prev_nsec;
	if (diff.nsec >= scaled_nsec) {
		diff.nsec -= scaled_nsec;
		diff.sec++;
	} else if (diff.nsec <= -scaled_nsec) {
		diff.nsec += scaled_nsec;
		diff.sec--;
	}
	if (diff.sec > 0 && diff.nsec < 0) {
		diff.nsec += scaled_nsec;
		diff.sec--;
	} else if (diff.sec < 0 && diff.nsec > 0) {
		diff.nsec -= scaled_nsec;
		diff.sec++;
	}
	if (diff.nsec < 0 && diff.sec < 0)
		diff.nsec = -diff.nsec;
	result->sec = diff.sec;
	result->nsec = diff.nsec;
}  /* calc_diff64 */
#endif

static void ptp_write_index(struct ptp_info *ptp, int shift, u8 unit)
{
	struct ksz_sw *sw = container_of(ptp, struct ksz_sw, ptp_hw);
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
	if (sec >= 3)
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
			dbg_msg("gap too small: %d=%d\n", i, cur->gap.nsec);
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
			dbg_msg("%d: %d:%9d %d %d:%9d %d: %d:%9d\n",
				i, cur->start.sec, cur->start.nsec, cur->len,
				cur->gap.sec, cur->gap.nsec, cur->iterate,
				cur->stop.sec, cur->stop.nsec);
			if (cur->stop.sec > next->start.sec ||
					(cur->stop.sec == next->start.sec &&
					cur->stop.nsec > next->stop.nsec))
				dbg_msg("> %d %d:%9d %d:%9d\n", i,
					cur->stop.sec, cur->stop.nsec,
					next->start.sec, next->start.nsec);
			add_nsec(&cur->start, cur->iterate);
			cur->stop = cur->start;
			add_nsec(&cur->stop, cur->len);
			if (!i)
				prev->start = cur->start;
		}
		dbg_msg("%d:%9d\n", prev->start.sec, prev->start.nsec);
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
	drift64 = div64_u64(drift64, interval64);
	return (u32) drift64;
}

static u32 clk_adjust_val(int diff, u32 interval)
{
	u32 adjust;
	u32 rem;
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
		adjust64 = div_u64_rem(adjust64, 25000000, &rem);
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
		printk(KERN_INFO "tso %d off!\n", tso);
		ptp->tso_sys &= ~tso_bit;
	}
	ptp->tso_dev[tso] = NULL;
}  /* ptp_tso_off */

static inline void ptp_tx_reset(struct ptp_info *ptp, u8 tso, u32 *ctrl_ptr)
{
	u32 ctrl;
	struct ksz_sw *sw = container_of(ptp, struct ksz_sw, ptp_hw);

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
	struct ksz_sw *sw = container_of(ptp, struct ksz_sw, ptp_hw);

	sw->ops->acquire(sw);
}  /* ptp_acquire */

static void ptp_release(struct ptp_info *ptp)
{
	struct ksz_sw *sw = container_of(ptp, struct ksz_sw, ptp_hw);

	sw->ops->release(sw);
}  /* ptp_release */

static void get_ptp_time(struct ptp_info *ptp, struct ptp_utime *t)
{
	u16 data;
	u16 subnsec;
	struct ksz_sw *sw = container_of(ptp, struct ksz_sw, ptp_hw);

	data = sw->cached.ptp_clk_ctrl;
	data |= PTP_READ_TIME;
	sw_w16(sw, REG_PTP_CLK_CTRL, data);
	do {
		u8 buf[12];
		u16 *w_ptr;
		u32 *d_ptr;

		sw_r(sw, REG_PTP_RTC_SUB_NANOSEC__2, buf, 10);
		w_ptr = (u16 *) buf;
		subnsec = be16_to_cpu(*w_ptr);
		++w_ptr;
		d_ptr = (u32 *) w_ptr;
		t->nsec = be32_to_cpu(*d_ptr);
		++d_ptr;
		t->sec = be32_to_cpu(*d_ptr);
	} while (0);
#if 1
if (subnsec > PTP_RTC_SUB_NANOSEC_M)
printk(" ?%x ", subnsec);
#endif
	subnsec &= PTP_RTC_SUB_NANOSEC_M;
	add_nsec(t, subnsec * 8);
}  /* get_ptp_time */

static void set_ptp_time(struct ptp_info *ptp, struct ptp_utime *t)
{
	u16 data;
	struct ksz_sw *sw = container_of(ptp, struct ksz_sw, ptp_hw);

	data = sw->cached.ptp_clk_ctrl;
	sw_w16(sw, REG_PTP_RTC_SUB_NANOSEC__2, 0);
	sw_w32(sw, REG_PTP_RTC_NANOSEC, t->nsec);
	sw_w32(sw, REG_PTP_RTC_SEC, t->sec);
	data |= PTP_LOAD_TIME;
	sw_w16(sw, REG_PTP_CLK_CTRL, data);
}  /* set_ptp_time */

static void adjust_ptp_time(struct ptp_info *ptp, int add, u32 sec, u32 nsec,
	int adj_hack)
{
	u16 ctrl;
	u16 adj = 0;
	u32 val = nsec;
	struct ksz_sw *sw = container_of(ptp, struct ksz_sw, ptp_hw);

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
	sw_w32(sw, REG_PTP_RTC_SEC, sec);
	do {
		if (nsec > NANOSEC_IN_SEC - 1)
			nsec = NANOSEC_IN_SEC - 1;
		sw_w32(sw, REG_PTP_RTC_NANOSEC, nsec);
		sw_w16(sw, REG_PTP_CLK_CTRL, ctrl);
		val -= nsec;
		nsec = val;
	} while (val);
	if (adj_hack && (adj & PTP_CLK_ADJ_ENABLE))
		sw_w16(sw, REG_PTP_CLK_CTRL, adj);
}  /* adjust_ptp_time */

static void adjust_sync_time(struct ptp_info *ptp, int diff, u32 interval,
	u32 duration)
{
	u32 adjust;
	struct ksz_sw *sw = container_of(ptp, struct ksz_sw, ptp_hw);

	adjust = clk_adjust_val(diff, interval);
	adjust |= PTP_TMP_RATE_ENABLE;
	sw_w32(sw, REG_PTP_RATE_DURATION, duration);
	sw_w32(sw, REG_PTP_SUBNANOSEC_RATE, adjust);
}  /* adjust_sync_time */

static void ptp_rx_reset(struct ptp_info *ptp, u8 tsi, u32 *ctrl_ptr)
{
	u32 ctrl;
	struct ksz_sw *sw = container_of(ptp, struct ksz_sw, ptp_hw);

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
	struct ksz_sw *sw = container_of(ptp, struct ksz_sw, ptp_hw);

	ptp_write_index(ptp, PTP_TSI_INDEX_S, tsi);
	ctrl = sw_r32(sw, REG_PTP_CTRL_STAT__4);
	ctrl &= ~(TRIG_RESET | TS_RESET);

	/* Disable previous timestamp interrupt. */
	if (ptp->ts_intr & tsi_bit) {
		ptp->ts_intr &= ~tsi_bit;
		ctrl &= ~TS_INT_ENABLE;
		ts_intr = tsi_bit;
	}

	/* Disable previous timestamp detection. */
	ctrl &= ~TS_ENABLE;
	sw_w32(sw, REG_PTP_CTRL_STAT__4, ctrl);

	/*
	 * Need to turn off cascade mode if it is used previously; otherwise,
	 * event counter keeps increasing.
	 */
	if (ptp->cascade_rx & tsi_bit) {
		ptp_rx_reset(ptp, tsi, &ctrl);
		sw_w32(sw, REG_TS_CTRL_STAT__4, 0);
		ptp->cascade_rx &= ~tsi_bit;
	}
	if (ts_intr)
		sw_w32(sw, REG_PTP_INT_STATUS__4, ts_intr);
}  /* ptp_rx_off */

static inline void ptp_rx_intr(struct ptp_info *ptp, u16 tsi_bit, u32 *ctrl)
{
	ptp->ts_intr |= tsi_bit;
	*ctrl |= TS_INT_ENABLE;
}  /* ptp_rx_intr */

static inline void ptp_rx_on(struct ptp_info *ptp, u8 tsi, int intr)
{
	u32 ctrl;
	struct ksz_sw *sw = container_of(ptp, struct ksz_sw, ptp_hw);

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
	struct ksz_sw *sw = container_of(ptp, struct ksz_sw, ptp_hw);

	ptp_write_index(ptp, PTP_TSI_INDEX_S, tsi);
	ctrl = sw_r32(sw, REG_PTP_CTRL_STAT__4);
	ctrl &= ~(TRIG_RESET | TS_RESET);
#ifdef CHK_SPI_ACCESS
if ((ctrl & (TS_INT_ENABLE | TS_ENABLE)) != (TS_INT_ENABLE | TS_ENABLE)) {
printk(" rx: %08x; %x\n", ctrl, sw_r32(sw, REG_PTP_UNIT_INDEX__4));
#if 1
ctrl |= TS_INT_ENABLE;
#endif
}
#endif
	ctrl &= ~TS_ENABLE;
	sw_w32(sw, REG_PTP_CTRL_STAT__4, ctrl);
	ctrl |= TS_ENABLE;
	sw_w32(sw, REG_PTP_CTRL_STAT__4, ctrl);
#ifdef CHK_SPI_ACCESS
do {
u32 status;
status = sw_r32(sw, REG_PTP_CTRL_STAT__4);
if ((status & (TS_INT_ENABLE | TS_ENABLE)) != (TS_INT_ENABLE | TS_ENABLE)) {
printk(" rx: %s %08x %08x; %x\n", __func__, status, ctrl, sw_r32(sw, REG_PTP_UNIT_INDEX__4));
	sw_w32(sw, REG_PTP_CTRL_STAT__4, ctrl);
}
} while (0);
#endif
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
	struct ksz_sw *sw = container_of(ptp, struct ksz_sw, ptp_hw);

	/* Config pattern. */
	ptp_write_index(ptp, PTP_TSI_INDEX_S, tsi);
	ctrl = ts_event_gpi(gpi, event);
	sw_w32(sw, REG_TS_CTRL_STAT__4, ctrl);

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
	struct ksz_sw *sw = container_of(ptp, struct ksz_sw, ptp_hw);

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
		sw_w32(sw, REG_TS_CTRL_STAT__4, ctrl);

		/* Enable timestamp interrupt. */
		if (intr) {
			ctrl = sw_r32(sw, REG_PTP_CTRL_STAT__4);
			ptp_rx_intr(ptp, (1 << tsi), &ctrl);
			sw_w32(sw, REG_PTP_CTRL_STAT__4, ctrl);
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
	sw_w32(sw, REG_TS_CTRL_STAT__4, ctrl);

	/* Enable timestamp detection. */
	ptp_rx_on(ptp, first, intr);
}  /* ptp_rx_cascade_event */

static u32 ptp_get_event_cnt(struct ptp_info *ptp, u8 tsi, void *ptr)
{
	struct ksz_sw *sw = container_of(ptp, struct ksz_sw, ptp_hw);

	ptp_write_index(ptp, PTP_TSI_INDEX_S, tsi);
	return sw_r32(sw, REG_TS_CTRL_STAT__4);
}  /* ptp_get_event_cnt */

static void ptp_get_events(struct ptp_info *ptp, u32 reg_ns, size_t len,
	void *buf, void *ptr)
{
	int i;
	u32 *data = buf;
	struct ksz_sw *sw = container_of(ptp, struct ksz_sw, ptp_hw);

	sw_r(sw, reg_ns, buf, len);
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
#if 0
printk("edge: %x %x\n", event->event, edge);
#endif
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
	struct ksz_sw *sw = container_of(ptp, struct ksz_sw, ptp_hw);

	ptp_write_index(ptp, PTP_TOU_INDEX_S, tso);

	/* Disable previous trigger out if not already completed. */
	ctrl = sw_r32(sw, REG_PTP_CTRL_STAT__4);
	ctrl &= ~(TRIG_RESET | TS_RESET);
	if (ctrl & TRIG_ENABLE) {
		ctrl &= ~TRIG_ENABLE;
		sw_w32(sw, REG_PTP_CTRL_STAT__4, ctrl);
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
		ctrl = sw_r32(sw, REG_TRIG_CTRL__4);
		if (ctrl & TRIG_CASCADE_ENABLE) {
			ctrl &= ~TRIG_CASCADE_ENABLE;
			ctrl &= ~TRIG_CASCADE_TAIL;
			ctrl |= trig_cascade(TRIG_CASCADE_UPS_M);
			sw_w32(sw, REG_TRIG_CTRL__4, ctrl);
		}
	}
}  /* ptp_tx_off */

static void ptp_tx_on(struct ptp_info *ptp, u8 tso)
{
	u32 ctrl;
	struct ksz_sw *sw = container_of(ptp, struct ksz_sw, ptp_hw);

	ctrl = sw->reg->r32(sw, REG_PTP_CTRL_STAT__4);
	ctrl &= ~(TRIG_RESET | TS_RESET);
	ctrl |= TRIG_ENABLE;
	sw->reg->w32(sw, REG_PTP_CTRL_STAT__4, ctrl);
}  /* ptp_tx_on */

static void ptp_tx_trigger_time(struct ptp_info *ptp, u8 tso, u32 sec, u32 nsec)
{
	struct ksz_sw *sw = container_of(ptp, struct ksz_sw, ptp_hw);

	sw_w32(sw, REG_TRIG_TARGET_SEC, sec);
	sw_w32(sw, REG_TRIG_TARGET_NANOSEC, nsec);
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
	struct ksz_sw *sw = container_of(ptp, struct ksz_sw, ptp_hw);

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
	sw_w32(sw, REG_TRIG_CTRL__4, ctrl);

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
		sw_w24(sw, REG_TRIG_PULSE_WIDTH__4 + 1, pulse);
	}

	/* Config cycle width. */
	if (event >= TRIG_NEG_PERIOD) {
		u32 data = cnt;
		int min_cycle = pulse * PULSE_NSEC + MIN_CYCLE_NSEC;

		if (cycle < min_cycle)
			cycle = min_cycle;
		sw_w32(sw, REG_TRIG_CYCLE_WIDTH, cycle);

		/* Config trigger count. */
		data <<= TRIG_CYCLE_CNT_S;
		pattern |= data;
		sw_w32(sw, REG_TRIG_CYCLE_CNT, pattern);
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
	struct ksz_sw *sw = container_of(ptp, struct ksz_sw, ptp_hw);

	ptp_tx_off(ptp, tso);

	/* Config pattern. */
	ctrl = trig_event_gpo(gpo, event);
	ctrl |= TRIG_NOTIFY;
	ctrl |= TRIG_NOW;
	ctrl |= trig_cascade(TRIG_CASCADE_UPS_M);
	sw_w32(sw, REG_TRIG_CTRL__4, ctrl);

	/* Config pulse width. */
	if (pulse > TRIG_PULSE_WIDTH_M)
		pulse = TRIG_PULSE_WIDTH_M;
	sw_w24(sw, REG_TRIG_PULSE_WIDTH__4 + 1, pulse);

	/* Config cycle width. */
	sw_w32(sw, REG_TRIG_CYCLE_WIDTH, cycle);

	/* Config trigger count. */
	pattern = cnt;
	pattern <<= TRIG_CYCLE_CNT_S;
	sw_w32(sw, REG_TRIG_CYCLE_CNT, pattern);

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
	struct ksz_sw *sw = container_of(ptp, struct ksz_sw, ptp_hw);

	/* Config pattern. */
	ctrl = trig_event_gpo(gpo, event);
	ctrl |= TRIG_NOTIFY;
	if (1 == tso)
		ctrl |= TRIG_EDGE;
	ctrl |= trig_cascade(TRIG_CASCADE_UPS_M);
	sw_w32(sw, REG_TRIG_CTRL__4, ctrl);

	/* Config pulse width. */
	if (pulse > TRIG_PULSE_WIDTH_M)
		pulse = TRIG_PULSE_WIDTH_M;
	sw_w32(sw, REG_TRIG_PULSE_WIDTH__4 + 0, pulse);

	/* Config cycle width. */
	sw_w32(sw, REG_TRIG_CYCLE_WIDTH, cycle);

	/* Config trigger count. */
	pattern = cnt;
	pattern <<= TRIG_CYCLE_CNT_S;
	sw_w32(sw, REG_TRIG_CYCLE_CNT, pattern);

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
	struct ksz_sw *sw = container_of(ptp, struct ksz_sw, ptp_hw);

	sw_w32(sw, REG_TRIG_ITERATE_TIME, nsec);
}  /* ptp_tx_cascade_cycle */

static void ptp_tx_cascade_on(struct ptp_info *ptp, u8 tso, u8 first, u8 last,
	u16 repeat)
{
	u32 ctrl;
	struct ksz_sw *sw = container_of(ptp, struct ksz_sw, ptp_hw);

	ctrl = sw_r32(sw, REG_TRIG_CTRL__4);
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
	sw_w32(sw, REG_TRIG_CTRL__4, ctrl);
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
		dbg_msg("cascade repeat timing is not right\n");
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
	struct ksz_sw *sw = container_of(ptp, struct ksz_sw, ptp_hw);

	ctrl = sw->reg->r16(sw, REG_PTP_DOMAIN_VERSION) & ~PTP_DOMAIN_M;
	ctrl |= domain;
	sw->reg->w16(sw, REG_PTP_DOMAIN_VERSION, ctrl);
}  /* set_ptp_domain */

static void set_ptp_mode(struct ptp_info *ptp, u16 mode)
{
	u16 val;
	u16 sav;
	struct ksz_sw *sw = container_of(ptp, struct ksz_sw, ptp_hw);

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
	struct ksz_sw *sw = container_of(ptp, struct ksz_sw, ptp_hw);

	sw->reg->w32(sw, REG_PTP_SUBNANOSEC_RATE, adjust);
}  /* set_ptp_adjust */

static inline void unsyntonize_clk(struct ptp_info *ptp)
{
	u16 ctrl;
	struct ksz_sw *sw = container_of(ptp, struct ksz_sw, ptp_hw);

	ctrl = sw->cached.ptp_clk_ctrl;
	ctrl &= ~PTP_CLK_ADJ_ENABLE;
	sw->cached.ptp_clk_ctrl = ctrl;
	sw->reg->w16(sw, REG_PTP_CLK_CTRL, ctrl);
}  /* unsyntonize_clk */

static void syntonize_clk(struct ptp_info *ptp)
{
	u16 ctrl;
	struct ksz_sw *sw = container_of(ptp, struct ksz_sw, ptp_hw);

	ctrl = sw->cached.ptp_clk_ctrl;
	ctrl |= PTP_CLK_ADJ_ENABLE;
	sw->cached.ptp_clk_ctrl = ctrl;
	sw->reg->w16(sw, REG_PTP_CLK_CTRL, ctrl);
}  /* syntonize_clk */

static u16 get_ptp_delay(struct ptp_info *ptp, int port, u32 reg)
{
	struct ksz_sw *sw = container_of(ptp, struct ksz_sw, ptp_hw);

	reg = PORT_CTRL_ADDR(port, reg);
	return sw->reg->r16(sw, reg);
}  /* get_ptp_delay */

static void set_ptp_delay(struct ptp_info *ptp, int port, u32 reg, u16 nsec)
{
	struct ksz_sw *sw = container_of(ptp, struct ksz_sw, ptp_hw);

	reg = PORT_CTRL_ADDR(port, reg);
	sw->reg->w16(sw, reg, nsec);
}  /* set_ptp_delay */

static u16 get_ptp_ingress(struct ptp_info *ptp, int port)
{
	return get_ptp_delay(ptp, port, REG_PTP_PORT_RX_DELAY__2);
}

static u16 get_ptp_egress(struct ptp_info *ptp, int port)
{
	return get_ptp_delay(ptp, port, REG_PTP_PORT_TX_DELAY__2);
}

static short get_ptp_asym(struct ptp_info *ptp, int port)
{
	short val;

	val = get_ptp_delay(ptp, port, REG_PTP_PORT_ASYM_DELAY__2);
	if (val & 0x8000)
		val = -(val & ~0x8000);
	return val;
}

static u32 get_ptp_link(struct ptp_info *ptp, int port)
{
	u32 reg = PORT_CTRL_ADDR(port, REG_PTP_PORT_LINK_DELAY__4);
	struct ksz_sw *sw = container_of(ptp, struct ksz_sw, ptp_hw);

	return sw->reg->r32(sw, reg);
}

static void set_ptp_ingress(struct ptp_info *ptp, int port, u16 nsec)
{
	set_ptp_delay(ptp, port, REG_PTP_PORT_RX_DELAY__2, nsec);
}

static void set_ptp_egress(struct ptp_info *ptp, int port, u16 nsec)
{
	set_ptp_delay(ptp, port, REG_PTP_PORT_TX_DELAY__2, nsec);
}

static void set_ptp_asym(struct ptp_info *ptp, int port, short nsec)
{
	if (nsec < 0)
		nsec = -nsec | 0x8000;
	set_ptp_delay(ptp, port, REG_PTP_PORT_ASYM_DELAY__2, nsec);
}

static void set_ptp_link(struct ptp_info *ptp, int port, u32 nsec)
{
	u32 reg = PORT_CTRL_ADDR(port, REG_PTP_PORT_LINK_DELAY__4);
	struct ksz_sw *sw = container_of(ptp, struct ksz_sw, ptp_hw);

	sw->reg->w32(sw, reg, nsec);
}

static inline void dbp_tx_ts(char *name, u8 port, u32 timestamp)
{
	u8 overflow;
	char ts[FMT_NSEC_SIZE];

	timestamp = timestamp_val(timestamp, &overflow);
	format_nsec(ts, timestamp);
	dbg_msg("%s p:%d c:%u %08x:%s\n", name, port, overflow, timestamp, ts);
}  /* dbp_tx_ts */

static void ptp_setup_udp_msg(struct ptp_dev_info *info, u8 *data, int len,
	void (*func)(u8 *data, void *param), void *param)
{
	u8 buf[MAX_TSM_UDP_LEN];
	int in_intr = in_interrupt();

	if (len > MAX_TSM_UDP_LEN)
		len = MAX_TSM_UDP_LEN;
	if (!in_intr)
		mutex_lock(&info->lock);
	memcpy(buf, data, len);
	if (func)
		func(buf, param);
	len += 2;
	if (info->read_len + len <= info->read_max) {
		u16 *udp_len = (u16 *) &info->read_buf[info->read_len];

		*udp_len = len;
		udp_len++;
		memcpy(udp_len, buf, len - 2);
		info->read_len += len;
	}
	if (!in_intr)
		mutex_unlock(&info->lock);
	wake_up_interruptible(&info->wait_udp);
}  /* ptp_setup_udp_msg */

static void ptp_tsm_resp(u8 *data, void *param)
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

static void ptp_tsm_get_time_resp(u8 *data, void *param)
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
	struct ptp_hw_ts *htx, int delay, int port)
{
	unsigned long diff = 0;

	add_tx_delay(&htx->ts, delay, ptp->cur_time.sec);
	if (!htx->sim_2step) {
		struct tsm_db *db = (struct tsm_db *) tx->data.buf;
		u8 msg = tx->data.buf[0] & 3;

		tx->ts = htx->ts;
		tx->resp_time = jiffies;
		if (tx->req_time)
			diff = tx->resp_time - tx->req_time;
		if (diff < 4 * ptp->delay_ticks) {
			if (tx->missed) {
				if (diff > 2 * ptp->delay_ticks)
					dbg_msg("  caught: %d, %lu; %x=%04x\n",
						port, diff, msg,
						ntohs(db->seqid));
				if (tx->dev) {
					ptp_setup_udp_msg(tx->dev,
						tx->data.buf, tx->data.len,
						ptp_tsm_resp, &tx->ts);
					tx->dev = NULL;
				}

				/* Invalidate the timestamp. */
				tx->ts.timestamp = 0;
				tx->req_time = 0;
			}
		} else {
			dbg_msg("  new: %d, %lu; %x=%04x\n", port, diff,
				msg, ntohs(db->seqid));
		}
		tx->missed = false;
		if (tx->skb) {
			int len;
			u64 ns;
			struct skb_shared_hwtstamps shhwtstamps;

			if (ptp->tx_en & (1 << 8))
				ns = (u64) tx->ts.t.sec * NANOSEC_IN_SEC +
					tx->ts.t.nsec;
			else
				ns = (u64) tx->ts.r.sec * NANOSEC_IN_SEC +
					tx->ts.r.nsec;
			memset(&shhwtstamps, 0, sizeof(shhwtstamps));
			shhwtstamps.hwtstamp = ns_to_ktime(ns);

			/* Indicate which port message is sent out. */
			tx->msg->hdr.reserved2 = port + 1;
			len = (unsigned char *) tx->msg - tx->skb->data;
			__skb_pull(tx->skb, len);
			skb_tstamp_tx(tx->skb, &shhwtstamps);

			/* buffer not released yet. */
			if (skb_shinfo(tx->skb)->tx_flags & SKBTX_HW_TSTAMP)
				skb_shinfo(tx->skb)->tx_flags &=
					~SKBTX_IN_PROGRESS;
			else
				dev_kfree_skb_irq(tx->skb);
			tx->skb = NULL;
		}
	}
	htx->sending = false;
}  /* save_tx_ts */

static int get_speed_index(struct ptp_info *ptp, int port)
{
	int index;

	if (1000 == ptp->linked[port])
		index = 0;
	else if (100 == ptp->linked[port])
		index = 1;
	else
		index = 2;
	return index;
}  /* get_speed_index */

static int get_tx_time(struct ptp_info *ptp, int port, u16 status)
{
	int delay;
	int index;
	u32 reg;
	struct ptp_tx_ts *tx = NULL;
	struct ptp_hw_ts *htx = NULL;
	struct ksz_sw *sw = container_of(ptp, struct ksz_sw, ptp_hw);

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
		}
		htx->ts.timestamp = sw->reg->r32(sw,
			PORT_CTRL_ADDR(port, reg));
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
	ptp->reg->pps_event(ptp, gpo, t.sec);
#ifdef ENABLE_10_MHZ_CLK
	ptp->reg->ptp_10MHz(ptp, ptp->mhz_tso, ptp->mhz_gpo, t.sec);
#endif
	schedule_delayed_work(&ptp->update_sec, (1000000 - t.nsec / 1000) * HZ
		/ 1000000);
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
	ptp->tso_used |= (1 << ptp->pps_tso);
	ptp->tso_sys |= (1 << ptp->pps_tso);
#ifdef ENABLE_10_MHZ_CLK
	ptp->tso_used |= (1 << ptp->mhz_tso);
	ptp->tso_used |= (1 << 1);
	ptp->tso_sys |= (1 << ptp->mhz_tso);
	ptp->tso_sys |= (1 << 1);
#endif
	generate_tx_event(ptp, ptp->pps_gpo);
	ptp->tsi_used |= (1 << ptp->pps_tsi);
	ptp->tsi_sys |= (1 << ptp->pps_tsi);
	ptp->events[ptp->pps_tsi].num = 0;
	ptp->events[ptp->pps_tsi].event = 1;
	ptp->events[ptp->pps_tsi].edge = 0;
	ptp->events[ptp->pps_tsi].expired = 0;
	ptp->reg->rx_event(ptp, ptp->pps_tsi, ptp->pps_gpo, DETECT_RISE, true);
	ptp->ops->release(ptp);
}  /* prepare_pps */

/* -------------------------------------------------------------------------- */

static void ptp_tx_intr_enable(struct ptp_info *ptp)
{
	u32 reg;
	int i;
	struct ksz_sw *sw = container_of(ptp, struct ksz_sw, ptp_hw);

	for (i = 0; i < ptp->ports; i++) {
		reg = PORT_CTRL_ADDR(i, REG_PTP_PORT_TX_INT_STATUS__2);
		sw->reg->w16(sw, reg, 0xffff);
		reg = PORT_CTRL_ADDR(i, REG_PTP_PORT_TX_INT_ENABLE__2);
		sw->reg->w16(sw, reg, ptp->tx_intr);
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
	struct ksz_sw *sw = container_of(ptp, struct ksz_sw, ptp_hw);

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
	quot = div_u64_rem(scaled_nsec, NSEC_PER_SEC, &rem);
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
		if (ptp->sec_changed)
			generate_tx_event(ptp, ptp->pps_gpo);
		else {
			ptp->update_sec_jiffies = jiffies;
			schedule_delayed_work(&ptp->check_pps,
				1200 * HZ / 1000);
		}
	}
	if (ptp->sec_changed) {
		struct timespec ts;
		struct ptp_utime cur;

		ptp->reg->get_time(ptp, &ptp->cur_time);
		ts = ktime_to_timespec(ktime_get_real());
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
	int index;
	int p;

	ptp->ops->acquire(ptp);
	for (p = 0; p < ptp->ports; p++) {
		if (ptp->linked[p] & 0x80000000) {
			ptp->linked[p] &= ~0x80000000;
			index = get_speed_index(ptp, p);
			set_ptp_ingress(ptp, p, ptp->rx_latency[p][index]);
			set_ptp_egress(ptp, p, ptp->tx_latency[p][index]);
		}
	}
	ptp->ops->release(ptp);
}  /* set_latency */

static void execute(struct ptp_info *ptp, struct work_struct *work)
{
	queue_work(ptp->access, work);
}  /* execute */

static void ptp_hw_disable(struct ptp_info *ptp)
{
	int i;
	u32 ctrl;
	struct ksz_sw *sw = container_of(ptp, struct ksz_sw, ptp_hw);

	for (i = 0; i < 2; i++) {
		sw->cached.ptp_unit_index =
			(i << PTP_TSI_INDEX_S) |
			(i << PTP_TOU_INDEX_S);
		sw_w32(sw, REG_PTP_UNIT_INDEX__4, sw->cached.ptp_unit_index);
		ctrl = TS_RESET | TRIG_RESET;
		sw_w32(sw, REG_PTP_CTRL_STAT__4, ctrl);
		sw_w32(sw, REG_PTP_CTRL_STAT__4, 0);
		sw_w32(sw, REG_TRIG_CTRL__4, 0);
		sw_w32(sw, REG_TS_CTRL_STAT__4, 0);
	}
	sw->cached.ptp_unit_index = (i << PTP_TOU_INDEX_S);
	sw_w32(sw, REG_PTP_UNIT_INDEX__4, sw->cached.ptp_unit_index);
	ctrl = TRIG_RESET;
	sw_w32(sw, REG_PTP_CTRL_STAT__4, ctrl);
	sw_w32(sw, REG_PTP_CTRL_STAT__4, 0);
	sw_w32(sw, REG_TRIG_CTRL__4, 0);
}  /* ptp_hw_disable */

static void ptp_hw_enable(struct ptp_info *ptp)
{
	int i;
	u16 data;
	struct ksz_sw *sw = container_of(ptp, struct ksz_sw, ptp_hw);

	ptp->ops->acquire(ptp);
	ptp_hw_disable(ptp);
#ifndef ACL_TEST
	data = sw_r16(sw, REG_PTP_MSG_CONF1);
dbg_msg("msg_conf1: %x\n", data);
	data = ptp->mode;
	sw_w16(sw, REG_PTP_MSG_CONF1, data);
	data = sw_r16(sw, REG_PTP_MSG_CONF1);
	if ((sw->overrides & TAIL_TAGGING) && (data & PTP_ENABLE))
		sw->overrides |= PTP_TAG;
#endif
	data = sw_r16(sw, REG_PTP_MSG_CONF2);
dbg_msg("msg_conf2: %x\n", data);
	sw_w16(sw, REG_PTP_MSG_CONF2, ptp->cfg);
	data = sw_r16(sw, REG_PTP_CLK_CTRL);
dbg_msg("clk_ctrl: %x\n", data);
	data |= PTP_CLK_ENABLE;
	data &= ~PTP_CLK_ADJ_ENABLE;
	sw->cached.ptp_clk_ctrl = data;
#if 1
	if (!(sw->features & NEW_CAP))
		data |= PTP_CLK_RESET;
#endif
	sw_w16(sw, REG_PTP_CLK_CTRL, data);

	ptp->drift_set = ptp->drift = 0;
	sw->reg->w32(sw, REG_PTP_SUBNANOSEC_RATE, 0);

	sw->reg->w16(sw, REG_SW_HSR_TPID__2, 0x892F);

	for (i = 0; i < ptp->ports; i++) {
		ptp->rx_latency[i][0] = 390;
		ptp->tx_latency[i][0] = 140;
		ptp->rx_latency[i][1] = 580;
		ptp->rx_latency[i][1] = 620;
		ptp->tx_latency[i][1] = 140;
		ptp->rx_latency[i][2] = 580;
		ptp->rx_latency[i][2] = 620;
		ptp->tx_latency[i][2] = 140;
	}
	for (i = 0; i < ptp->ports; i++) {
		set_ptp_ingress(ptp, i, ptp->rx_latency[i][0]);
		set_ptp_egress(ptp, i, ptp->tx_latency[i][0]);
	}

	ptp->ops->release(ptp);
}  /* ptp_hw_enable */

static void ptp_start(struct ptp_info *ptp, int init)
{
	u32 ctrl;
	struct timespec ts;
	struct ptp_utime t;
	struct ksz_sw *sw = container_of(ptp, struct ksz_sw, ptp_hw);

#if defined(NO_DIRECT_ACCESS)
do {
if (!sw->info->iba.use_iba) {
printk("%s\n", __func__);
	ptp->started = true;
return;
}
} while (0);
#endif
	if (init && (sw->features & NEW_CAP))
		ptp_hw_enable(ptp);
	ptp->ops->acquire(ptp);
	ctrl = sw_r16(sw, REG_PTP_MSG_CONF1);
	if (ctrl == ptp->mode) {
		ptp->cfg = sw_r16(sw, REG_PTP_MSG_CONF2);
		ptp->domain = sw_r16(sw, REG_PTP_DOMAIN_VERSION) &
			PTP_DOMAIN_M;
		if (!init) {
			ptp->ops->release(ptp);
			return;
		}
	} else if (!init)
		ptp->mode = ctrl;
	if (ptp->mode != ptp->def_mode) {
		dbg_msg("mode changed: %04x %04x; %04x %04x\n",
			ptp->mode, ptp->def_mode, ptp->cfg, ptp->def_cfg);
		ptp->mode = ptp->def_mode;
		ptp->cfg = ptp->def_cfg;
		ptp->ptp_synt = false;
	}
	dbg_msg("ptp_start: %04x %04x\n",
		ptp->mode, ptp->cfg);
	sw_w16(sw, REG_PTP_MSG_CONF1, ptp->mode);
	sw_w16(sw, REG_PTP_MSG_CONF2, ptp->cfg);
	sw_w32(sw, REG_PTP_INT_STATUS__4, 0xffffffff);
	if (sw->overrides & TAIL_TAGGING)
		sw->overrides |= PTP_TAG;
	ptp_tx_intr_enable(ptp);
	ptp->ops->release(ptp);

	ts = ktime_to_timespec(ktime_get_real());
	t.sec = ts.tv_sec;
	t.nsec = ts.tv_nsec;
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

#if 0
printk("save %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x.%04x %x %04x %x\n",
hdr->sourcePortIdentity.clockIdentity.addr[0],
hdr->sourcePortIdentity.clockIdentity.addr[1],
hdr->sourcePortIdentity.clockIdentity.addr[2],
hdr->sourcePortIdentity.clockIdentity.addr[3],
hdr->sourcePortIdentity.clockIdentity.addr[4],
hdr->sourcePortIdentity.clockIdentity.addr[5],
hdr->sourcePortIdentity.clockIdentity.addr[6],
hdr->sourcePortIdentity.clockIdentity.addr[7],
hdr->sourcePortIdentity.port,
hdr->messageType, hdr->sequenceId, hdr->domainNumber);
#endif
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

	spin_lock(lock);
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
	spin_unlock(lock);
}  /* check_expired_msg */

static int find_msg_info(struct ptp_msg_info *msg_info, spinlock_t *lock,
	struct ptp_msg_hdr *hdr, struct ptp_port_identity *id, int remove,
	struct ptp_msg_options *info)
{
	struct ptp_msg_info *rx_msg = msg_info;
	struct ptp_msg_info *prev;
	struct ptp_msg_options *data;
	int ret = false;

	spin_lock(lock);
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
	spin_unlock(lock);
	return ret;
}  /* find_msg_info */

static int ptp_stop(struct ptp_info *ptp)
{
	flush_work(&ptp->adj_clk);
	flush_work(&ptp->set_latency);
	flush_workqueue(ptp->access);
	ptp->update_sec_jiffies = 0;
	ptp->ops->acquire(ptp);
	exit_msg_info(ptp->rx_msg_info);
	exit_msg_info(ptp->tx_msg_info);

	/* Stop triggered outputs and timestamp inputs. */
	ptp_hw_disable(ptp);

	/* S2 chip can be reset. */
	ptp->ptp_synt = false;

	/* Stop processing PTP interrupts. */
	ptp->started = false;
	ptp->first_drift = 0;
	ptp->ops->release(ptp);

#ifdef DEBUG_MSG
	dbg_print_work(&db.dbg_print);
#endif
	return false;
}  /* ptp_stop */

static void init_tx_ts(struct ptp_tx_ts *ts)
{
	ts->ts.timestamp = 0;
	ts->req_time = 0;
	ts->resp_time = 0;
	ts->missed = false;
	ts->hdr.messageType = 7;
}  /* init_tx_ts */

static struct ptp_dev_info *find_minor_dev(struct ptp_dev_info *info)
{
	struct ptp_info *ptp = info->ptp;
	struct ptp_dev_info *dev;
	struct ptp_dev_info *prev;

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

static void ptp_init_hw(struct ptp_info *ptp)
{
	int port;
	u32 reg;
	struct ksz_sw *sw = container_of(ptp, struct ksz_sw, ptp_hw);

#if defined(NO_DIRECT_ACCESS)
do {
	struct ksz_sw *sw = container_of(ptp, struct ksz_sw, ptp_hw);
if (!sw->info->iba.use_iba) {
printk("%s\n", __func__);
return;
}
} while (0);
#endif
	ptp->ops->acquire(ptp);
	for (port = 0; port < ptp->ports; port++) {
		int index;

		ptp->hw_sync[port].ts.timestamp = 0;
		ptp->hw_sync[port].sending = false;
		ptp->hw_dreq[port].ts.timestamp = 0;
		ptp->hw_dreq[port].sending = false;
		ptp->hw_resp[port].ts.timestamp = 0;
		ptp->hw_resp[port].sending = false;
		init_tx_ts(&ptp->tx_sync[port]);
		init_tx_ts(&ptp->tx_dreq[port]);
		init_tx_ts(&ptp->tx_resp[port]);
		reg = PORT_CTRL_ADDR(port, REG_PTP_PORT_XDELAY_TS);
		ptp->xdelay_ts[port] = sw->reg->r32(sw, reg);
		reg = PORT_CTRL_ADDR(port, REG_PTP_PORT_PDRESP_TS);
		ptp->pdresp_ts[port] = sw->reg->r32(sw, reg);
		index = get_speed_index(ptp, port);
		ptp->rx_latency[port][index] = get_ptp_ingress(ptp, port);
		ptp->tx_latency[port][index] = get_ptp_egress(ptp, port);
		ptp->asym_delay[port][index] = get_ptp_asym(ptp, port);
		ptp->peer_delay[port] = get_ptp_link(ptp, port);
		dbg_msg("%d = %d %d %d; %u\n", port,
			ptp->rx_latency[port][index],
			ptp->tx_latency[port][index],
			ptp->asym_delay[port][index],
			ptp->peer_delay[port]);
		set_ptp_link(ptp, port, 0);
		ptp->peer_delay[port] = 0;
	}
	ptp->ops->release(ptp);
}  /* ptp_init_hw */

static void ptp_init_state(struct ptp_info *ptp)
{
	u32 reg;
	struct ptp_utime t;
	struct ptp_msg_info *tx_msg;

	mutex_lock(&ptp->lock);
	ptp->udp_head = ptp->udp_tail = 0;
	for (reg = 0; reg < MAX_TSM_UDP_CNT; reg++)
		ptp->udp[reg].len = 0;
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

	if (!ptp->ptp_synt) {
		syntonize_clk(ptp);
		ptp->ptp_synt = true;
	}
	ptp->reg->get_time(ptp, &t);
	ptp->cur_time = t;
	ptp->op_state = 1;
	ptp->ops->release(ptp);
}  /* ptp_init_state */

static void ptp_exit_state(struct ptp_info *ptp)
{
	if (ptp->mode & PTP_MASTER) {
		u16 data;
		struct ksz_sw *sw = container_of(ptp, struct ksz_sw, ptp_hw);

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
	ptp->cap = 0;
	ptp->op_mode = 0;
	ptp->op_state = 0;
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
	struct ksz_sw *sw = container_of(ptp, struct ksz_sw, ptp_hw);
	int cnt;
	int p;
	struct ptp_msg *msg;
	u32 port;
	u32 intr;
	struct ptp_tx_ts *tx;
	struct sk_buff *orig_skb = skb;

	if (ptp->tx_msg_parsed)
		msg = ptp->tx_msg;
	else
		msg = check_ptp_msg(skb->data, NULL);
	ptp->tx_msg_parsed = false;
	if (!msg || msg->hdr.messageType & 0x8)
		return;

	if (ptp->tx_ports & sw->TAIL_TAG_LOOKUP)
		port = (1 << ptp->ports) - 1;
	else
		port = ptp->tx_ports & ((1 << ptp->ports) - 1);
	if (SYNC_MSG == msg->hdr.messageType) {
		tx = ptp->tx_sync;
		intr = PTP_PORT_SYNC_INT;
	} else if (PDELAY_RESP_MSG == msg->hdr.messageType) {
		tx = ptp->tx_resp;
		intr = PTP_PORT_PDELAY_RESP_INT;
	} else {
		tx = ptp->tx_dreq;
		intr = PTP_PORT_XDELAY_REQ_INT;
	}
	if (!(ptp->tx_intr & intr))
		return;
	cnt = 0;
	for (p = 0; p < ptp->ports; p++, tx++) {
		if (!(port & (1 << p)))
			continue;
		if (tx->skb) {
			if (skb_shinfo(tx->skb)->tx_flags & SKBTX_HW_TSTAMP)
				skb_shinfo(tx->skb)->tx_flags &=
					~SKBTX_IN_PROGRESS;
			else {
				dev_kfree_skb_irq(tx->skb);
				tx->skb = NULL;
			}
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

static int ptp_hwtstamp_ioctl(struct ptp_info *ptp, struct ifreq *ifr)
{
	struct hwtstamp_config config;

	if (copy_from_user(&config, ifr->ifr_data, sizeof(config)))
		return -EFAULT;

	/* reserved for future extensions */
	if (config.flags)
		return -EINVAL;

	switch (config.tx_type) {
	case HWTSTAMP_TX_OFF:
		ptp->tx_en &= ~1;
		break;
	case HWTSTAMP_TX_ONESTEP_SYNC:
	case HWTSTAMP_TX_ON:
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
		ptp->rx_en &= ~1;
		break;
	case HWTSTAMP_FILTER_ALL:
		ptp->rx_en |= 1;
		break;
	default:
		if (!ptp->cap && !(ptp->rx_en & 1) && (ptp->tx_en & 1)) {
			ptp->tx_en |= (1 << 8);
			ptp->rx_en |= (1 << 8);
		}
		ptp->rx_en |= 1;
		break;
	}

	return copy_to_user(ifr->ifr_data, &config, sizeof(config)) ?
		-EFAULT : 0;
}

#ifdef CONFIG_KSZ_STP
#if 0
static int ptp_chk_rx_msg(struct ptp_info *ptp, u8 *data, u8 port)
{
	struct ptp_msg *msg;
	struct ptp_msg_options *last;

	/* Use previously parsed PTP message if available. */
	msg = ptp->rx_msg;
	if (!msg)
		msg = check_ptp_msg(data, NULL);
	if (!msg)
		return false;
	ptp->rx_msg = msg;

	last = &ptp->rx_msg_chk[msg->hdr.messageType];
	if (!memcmp(&last->id, &msg->hdr.sourcePortIdentity,
	    sizeof(struct ptp_port_identity)) &&
	    last->seqid == ntohs(msg->hdr.sequenceId) &&
	    last->domain == msg->hdr.domainNumber) {
dbg_msg(" drop: %x %d %d; %04x %04x\n", last->msg, last->port, port,
last->seqid, ntohs(msg->hdr.sequenceId));
		return true;
	}
	memcpy(&last->id, &msg->hdr.sourcePortIdentity,
		sizeof(struct ptp_port_identity));
	last->seqid = ntohs(msg->hdr.sequenceId);
	last->domain = msg->hdr.domainNumber;
	last->msg = msg->hdr.messageType;
	last->port = port;
	return false;
}  /* ptp_chk_rx_msg */
#endif
#endif

static int ptp_drop_pkt(struct ptp_info *ptp, struct sk_buff *skb, u32 vlan_id,
	int *tag, int *ptp_tag)
{
	struct ksz_sw *sw = container_of(ptp, struct ksz_sw, ptp_hw);

	/* Not PTP message. */
	if (!(sw->tag.ports & 0x80))
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
	if (!(vlan_id & (1 << *tag)))
		*tag = 0;
	*ptp_tag = sw->tag.ports & ~0x80;
	ptp->ops->get_rx_info(ptp, skb->data, *ptp_tag, sw->tag.timestamp);
	if (!ptp->op_state) {
		*ptp_tag = 0;
		return false;
	}
#ifdef CONFIG_KSZ_STP_
	if (ptp_chk_rx_msg(ptp, skb->data, *ptp_tag))
		return true;
#endif
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
		spin_lock(&ptp->tx_msg_lock);
		save_msg_info(ptp, info, hdr, port, timestamp);
		info->next = tx_msg->next;
		tx_msg->next = info;
		if (ptp->tx_msg_cnt >= 0)
			ptp->tx_msg_cnt++;
		spin_unlock(&ptp->tx_msg_lock);
	}
}  /* set_msg_info */

static int proc_ptp_hw_access(struct ptp_info *ptp, int cmd, int subcmd,
	int option, void *data, size_t len, struct ptp_dev_info *info,
	int *output, int wait);

static struct ptp_utime last_rcv;
static s64 first_sync;
static s64 first_recv;

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
		u32 rem;

		corr = ts.t.sec;
		corr *= NANOSEC_IN_SEC;
		corr += ts.t.nsec;
		corr -= sync_corr;
		corr = div_s64_rem(corr, NANOSEC_IN_SEC, &rem);
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
		drift_per_sec = div64_s64(drift_per_sec, nsec);
		avg = div64_s64(cur_recv, cur_sync);
	}
	if (sync_corr) {
		u32 rem;

		cur_recv = avg * nsec;
		cur_recv = div_s64_rem(cur_recv, NANOSEC_IN_SEC, &rem);
		cur_recv += nsec;
		corr = last_rcv.sec;
		corr *= NANOSEC_IN_SEC;
		corr += last_rcv.nsec;
		cur_recv += corr;
		corr = recv.sec;
		corr *= NANOSEC_IN_SEC;
		corr += recv.nsec;
		corr -= cur_recv;
printk(" corr: %lld %lld %lld\n", sync_corr, corr, corr - sync_corr);
		sync_corr = 0;
	}
dbg_msg("sync: %x:%9u %x:%9u p:%10lld d:%lld a:%lld %lld\n",
ts.t.sec, ts.t.nsec,
sync.sec, sync.nsec, nsec, drift_per_sec, avg, drift_per_sec - avg);
dbg_msg("o: %d\n", offset.nsec);
#if 1
	if (nsec && nsec < 5000000000) {
		struct ptp_clk_options clk_opt;
		int output;
		int err;

		output = 1;
		clk_opt.sec = clk_opt.nsec = 0;

		ptp->drift = (int) drift_per_sec;
		if (ptp->drift < 5 && abs(offset.nsec) > 1000) {
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
			ptp->drift = -ptp->drift;
		ptp->drift += ptp->drift_set;

		clk_opt.drift = ptp->drift;
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

static struct ptp_msg *ptp_set_rx_info(struct ptp_info *ptp, u8 *data, u8 port,
	u32 timestamp)
{
	struct ptp_msg *msg;
	u32 overrides = ptp->overrides;

	/* Do not need to parse PTP message. */
	if (1 == ptp->op_mode)
		return NULL;

	/* Set receive port and timestamp inside the PTP message. */
	if (0 == ptp->op_mode && 1 == ptp->op_state)
		overrides |= PTP_ZERO_RESERVED_FIELD;
	else
		overrides &= ~PTP_ZERO_RESERVED_FIELD;
	port++;
	msg = update_ptp_msg(data, &port, &timestamp, overrides);
#if 1
	if (ptp->overrides & PTP_CHECK_SYNC_TIME)
		handle_sync(ptp, msg);
#endif

	/* Do not need to save PTP messages. */
	if (0 == ptp->op_mode)
		msg = NULL;
	return msg;
}  /* ptp_set_rx_info */

static struct ptp_msg *ptp_get_tx_info(struct ptp_info *ptp, u8 *data,
	u32 *tx_port, u32 *tx_timestamp)
{
	struct ptp_msg *msg;
	u32 overrides = ptp->overrides;
	u32 timestamp = 0;
	u8 port = 0;

	if ((1 == ptp->op_mode || 2 == ptp->op_mode) && !ptp->tx_msg_cnt) {
		/*
		 * This packet is not parsed and will be checked again if
		 * necessary.
		 */
		ptp->tx_msg_parsed = false;
		return NULL;
	}

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
#if 0
	if (ptp->overrides & PTP_CHECK_SYNC_TIME)
dbg_msg(" %x; %08x; %x:%09u\n", ptp->cur_time.sec, timestamp,
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
	default:
		info = kzalloc(sizeof(struct ptp_msg_info), GFP_KERNEL);
		break;
	}
	if (info) {
		spin_lock(&ptp->rx_msg_lock);
		save_msg_info(ptp, info, &msg->hdr, port, timestamp);
		info->next = rx_msg->next;
		rx_msg->next = info;
		spin_unlock(&ptp->rx_msg_lock);
	}
}  /* ptp_get_rx_info */

static void ptp_set_tx_info(struct ptp_info *ptp, u8 *data, void *ptr)
{
	struct ksz_sw *sw = container_of(ptp, struct ksz_sw, ptp_hw);
	int found;
	struct ptp_msg *msg;
	struct ptp_msg_options tx_msg;
	struct ksz_sw_tx_tag *tag = ptr;

	tx_msg.port = 0;
	tx_msg.ts.timestamp = 0;

	/* Assume packet will be parsed to determine PTP message type. */
	ptp->tx_msg_parsed = true;
	ptp->tx_msg = ptp_get_tx_info(ptp, data, &tx_msg.port,
		&tx_msg.ts.timestamp);
	if (!ptp->tx_msg) {
		/* Remember transmit ports for transmit timestamp report. */
		ptp->tx_ports = tag->ports;
		return;
	}
	msg = ptp->tx_msg;

	/* Check whether application sets transmit information using API. */
	found = find_msg_info(&ptp->tx_msg_info[msg->hdr.messageType],
		&ptp->tx_msg_lock, &msg->hdr, &msg->hdr.sourcePortIdentity,
		true, &tx_msg);
	if (found) {
		int port;
		u32 bits;
		struct ptp_tx_ts *tx = NULL;

		port = 0;
		bits = tx_msg.port;
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
			if (port)
				tx = &ptp->tx_resp[port - 1];
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
			int delay;
			int index;
			struct ptp_ts ts;

			/* Calculate timestamp automatically. */
			ts = tx_msg.ts;
			index = get_speed_index(ptp, tx_msg.port);
			delay = ptp->rx_latency[tx_msg.port][index];
			sub_nsec(&ts.t, delay);
			tx_msg.ts.timestamp = (ts.t.sec << 30) | ts.t.nsec;
		}
	}

	tag->timestamp = tx_msg.ts.timestamp;

	/* Specific ports are specified. */
	if (!(tag->ports & sw->TAIL_TAG_LOOKUP))
		goto set_tx_info_done;

	/* No need to set outgoing port for unicast message. */
	if (msg->hdr.flagField.flag.unicastFlag)
		goto set_tx_info_done;

	if (found || tx_msg.port) {
		if (tx_msg.port) {
			if (1 == found)
				tag->ports = (1 << tx_msg.port);
			else
				tag->ports = tx_msg.port;
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
		tag->ports = (1 << tx_msg.port);
dbg_msg("  tx m:%x f:%d p:%x\n", msg->hdr.messageType, found, tag->ports);

set_tx_info_done:

	/* Remember transmit ports for transmit timestamp report. */
	ptp->tx_ports = tag->ports;

	do {
		int p;
		u32 port;
		u32 intr;
		struct ptp_tx_ts *tx;

		/* Not PTP event message. */
		if (msg->hdr.messageType & 0x8)
			break;
		if (ptp->tx_ports & sw->TAIL_TAG_LOOKUP)
			port = (1 << ptp->ports) - 1;
		else
			port = ptp->tx_ports & ((1 << ptp->ports) - 1);
		if (SYNC_MSG == msg->hdr.messageType) {
			tx = ptp->tx_sync;
			intr = PTP_PORT_SYNC_INT;
		} else if (PDELAY_RESP_MSG == msg->hdr.messageType) {
			tx = ptp->tx_resp;
			intr = PTP_PORT_PDELAY_RESP_INT;
		} else {
			tx = ptp->tx_dreq;
			intr = PTP_PORT_XDELAY_REQ_INT;
		}

		/* Transmit timestamps are not retrieved. */
		if (!(ptp->tx_intr & intr))
			break;
		for (p = 0; p < ptp->ports; p++, tx++) {
			if (!(port & (1 << p)))
				continue;
			memcpy(&tx->hdr, &msg->hdr,
				sizeof(struct ptp_msg_hdr));
		}
	} while (0);
}  /* ptp_set_tx_info */

static void proc_ptp_get_cfg(struct ptp_info *ptp, u8 *data)
{
	struct ptp_cfg_options *cmd = (struct ptp_cfg_options *) data;
	struct ksz_sw *sw = container_of(ptp, struct ksz_sw, ptp_hw);

	ptp->ops->acquire(ptp);
	ptp->mode = sw->reg->r16(sw, REG_PTP_MSG_CONF1);
	ptp->cfg = sw->reg->r16(sw, REG_PTP_MSG_CONF2);
	ptp->domain = sw->reg->r16(sw, REG_PTP_DOMAIN_VERSION) & PTP_DOMAIN_M;
	ptp->ops->release(ptp);

	/* Check mode in case the switch is reset outside of driver control. */
	if (ptp->mode != ptp->def_mode && ptp->started) {
		dbg_msg("mode mismatched: %04x %04x; %04x %04x\n",
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
	cmd->priority = (ptp->cfg & PTP_ALL_HIGH_PRIO) ? 1 : 0;
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
	struct ksz_sw *sw = container_of(ptp, struct ksz_sw, ptp_hw);

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
			if (cmd->priority)
				ptp->cfg |= PTP_ALL_HIGH_PRIO;
			else
				ptp->cfg &= ~PTP_ALL_HIGH_PRIO;
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
		dbg_msg("mode: %x %x\n", mode, ptp->mode);
		mode = ptp->mode;
		if (ptp->overrides & PTP_VERIFY_TIMESTAMP)
			mode |= PTP_1STEP;
		sw->reg->w16(sw, REG_PTP_MSG_CONF1, mode);
		ptp->def_mode = mode;
		if (tx_intr != ptp->tx_intr)
			ptp_tx_intr_enable(ptp);
	}
	if (cfg != ptp->cfg) {
		dbg_msg("cfg: %x %x\n", cfg, ptp->cfg);
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
				printk(KERN_INFO "tsi %d off!\n", tsi);
				ptp->tsi_sys &= ~tsi_bit;
				ptp->update_sec_jiffies = jiffies;
				schedule_delayed_work(&ptp->update_sec,
					1000 * HZ / 1000);
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
	int last;
	u32 expired;
	struct ptp_event *events;
	struct ksz_ptp_time diff;
	struct ptp_utime t;

	events = &ptp->events[tsi];
	first = tsi;
	if (events->last) {
		first = events->first;
		last = events->last;
	} else
		last = first + 1;
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

static int proc_dev_rx_event(struct ptp_dev_info *info, u8 *data)
{
	struct ptp_info *ptp = info->ptp;
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

static int proc_dev_tx_event(struct ptp_dev_info *info, u8 *data)
{
	struct ptp_info *ptp = info->ptp;
	struct ptp_tso_options *cmd = (struct ptp_tso_options *) data;
	int gpo;
	int intr;
	int tso;
	int tso_bit;
	struct ptp_utime t;
	u16 active;
	u32 status;
	int err = 0;
	struct ksz_sw *sw = container_of(ptp, struct ksz_sw, ptp_hw);

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
			dbg_msg("trig err: %d\n", tso);
		}
		if (!(active & TRIG_ACTIVE)) {
			u16 done = status & PTP_TRIG_UNIT_M;

			if (!(done & tso_bit)) {
				/* Reset the unit. */
				ptp->cascade_tx |= tso_bit;
				dbg_msg(" !? trig done: %d\n", tso);
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
	struct ksz_sw *sw = container_of(ptp, struct ksz_sw, ptp_hw);

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
	int first;
	int gpo;
	int tso;
	int total;
	struct ptp_utime t;

	gpo = cmd->gpo;
	if (gpo >= MAX_GPIO)
		return -EINVAL;
	tso = cmd->tso;
	total = cmd->total;
	first = tso;
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
	ptp_setup_udp_msg(ptp->gps_dev, data, sizeof(struct tsm_get_gps),
		NULL, NULL);
	ptp->gps_dev = NULL;
}  /* proc_tsm_get_gps */

static int proc_dev_get_event(struct ptp_dev_info *info, u8 *data)
{
	struct ptp_info *ptp = info->ptp;
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
	ptp_setup_udp_msg(info, buf, len, NULL, NULL);
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
		ptp_setup_udp_msg(ptp->tso_dev[tso], buf, len, NULL, NULL);
		return 0;
	}
	return -1;
}  /* proc_ptp_get_trig */

static int proc_dev_poll_event(struct ptp_dev_info *info, u8 *data)
{
	struct ptp_info *ptp = info->ptp;
	struct ptp_tsi_info *in = (struct ptp_tsi_info *) data;

	if (in->unit >= MAX_TIMESTAMP_UNIT)
		return -EINVAL;
	if (!ptp_poll_event(ptp, in->unit))
		return DEV_IOC_UNIT_UNAVAILABLE;
	return proc_dev_get_event(info, data);
}  /* proc_dev_poll_event */

static int proc_dev_get_event_info(struct ptp_dev_info *info, u8 *data)
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
	struct timespec ts;
	struct ptp_utime sys_time;

	t.sec = cmd->sec;
	t.nsec = cmd->nsec;
	ptp->ops->acquire(ptp);
	ts = ktime_to_timespec(ktime_get_real());
	sys_time.sec = ts.tv_sec;
	sys_time.nsec = ts.tv_nsec;
	ptp->reg->set_time(ptp, &t);
	ptp->cur_time = t;
	calc_udiff(&ptp->cur_time, &sys_time, &ptp->time_diff);
	generate_tx_event(ptp, ptp->pps_gpo);
	ptp->ops->release(ptp);
	dbg_msg(" set clk: %x:%09u\n", cmd->sec, cmd->nsec);
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
		dbg_msg("adj clk: %d %u:%09u\n", adjust, cmd->sec, cmd->nsec);
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
		if (ptp->sec_changed)
			generate_tx_event(ptp, ptp->pps_gpo);
		else {
			ptp->update_sec_jiffies = jiffies;
			schedule_delayed_work(&ptp->check_pps,
				1200 * HZ / 1000);
		}
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
		dbg_msg(" adj clk: %d %u:%09u\n", adjust, cmd->sec, cmd->nsec);
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
dbg_msg("first drift: %d\n", ptp->drift_set);
		if (!ptp->first_drift)
			ptp->first_drift = ptp->drift_set;
		dbg_msg(" adj drift: %d\n", cmd->drift);
	}
	ptp->ops->release(ptp);
	return 0;
}  /* proc_ptp_adj_clk */

static int proc_ptp_get_delay(struct ptp_info *ptp, int port, u8 *data)
{
	struct ptp_delay_values *delay = (struct ptp_delay_values *) data;

	if (port >= ptp->ports)
		return DEV_IOC_INVALID_CMD;
	ptp->ops->acquire(ptp);
	delay->rx_latency = get_ptp_ingress(ptp, port);
	delay->tx_latency = get_ptp_egress(ptp, port);
	delay->asym_delay = get_ptp_asym(ptp, port);
	ptp->ops->release(ptp);
	return 0;
}  /* proc_ptp_get_delay */

static int proc_ptp_set_delay(struct ptp_info *ptp, int port, u8 *data)
{
	struct ptp_delay_values *delay = (struct ptp_delay_values *) data;
	int index;

	if (port >= ptp->ports)
		return DEV_IOC_INVALID_CMD;
	ptp->ops->acquire(ptp);
	set_ptp_ingress(ptp, port, delay->rx_latency);
	set_ptp_egress(ptp, port, delay->tx_latency);
	set_ptp_asym(ptp, port, delay->asym_delay);
	index = get_speed_index(ptp, port);
	ptp->rx_latency[port][index] = delay->rx_latency;
	ptp->tx_latency[port][index] = delay->tx_latency;
	ptp->asym_delay[port][index] = delay->asym_delay;
	ptp->ops->release(ptp);
	dbg_msg("set delay: %d = %d %d %d\n", port,
		ptp->rx_latency[port][index],
		ptp->tx_latency[port][index],
		ptp->asym_delay[port][index]);
	return 0;
}  /* proc_ptp_set_delay */

static int proc_ptp_get_peer_delay(struct ptp_info *ptp, int port, u8 *data)
{
	struct ptp_delay_values *delay = (struct ptp_delay_values *) data;
	u32 link;

	if (port >= ptp->ports)
		return DEV_IOC_INVALID_CMD;
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

static int proc_ptp_set_peer_delay(struct ptp_info *ptp, int port, u8 *data)
{
	struct ptp_delay_values *delay = (struct ptp_delay_values *) data;
	u32 link;

	if (port >= ptp->ports)
		return DEV_IOC_INVALID_CMD;
	ptp->ops->acquire(ptp);
	link = delay->rx_latency;
	link <<= 16;
	link |= delay->reserved;
	if (link != ptp->peer_delay[port]) {
		set_ptp_link(ptp, port, link);
		ptp->peer_delay[port] = link;
		dbg_msg("set delay: %d = %d\n", port,
			ptp->peer_delay[port]);
	}
	ptp->ops->release(ptp);
	return 0;
}  /* proc_ptp_set_peer_delay */

static void ptp_tx_done(struct ptp_info *ptp, int tso)
{
	int first;
	int last;
	int prev;
	u32 data;
	struct ksz_sw *sw = container_of(ptp, struct ksz_sw, ptp_hw);

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

static struct ptp_tx_ts *proc_get_ts(struct ptp_info *ptp, u8 port, u8 msg,
	u16 seqid, u8 *mac, struct ptp_dev_info *info, int len)
{
	struct ptp_tx_ts *tx;
	int from_stack = false;
	u8 *data = NULL;

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
	if (data && tx->req_time && ptp->linked[port])
		dbg_msg("  last %x=%04x: %d, %lu\n", msg, seqid, port,
			jiffies - tx->req_time);
	tx->missed = false;
	tx->req_time = jiffies;
	if (tx->ts.timestamp && from_stack) {
		unsigned long diff = tx->req_time - tx->resp_time;

		/* The timestamp is not valid. */
		if (diff >= 4 * ptp->delay_ticks) {
			dbg_msg("  invalid: %x=%04x: %d, %lu\n",
				msg, seqid, port, diff);
			tx->ts.timestamp = 0;
		} else if (diff > 2 * ptp->delay_ticks)
			dbg_msg("  ready? %x=%04x: %d, %lu\n",
				msg, seqid, port, diff);
	}
	if (!tx->ts.timestamp && ptp->linked[port] && data) {
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
		if (ptp->linked[port])
			dbg_msg("  missed %x=%04x: %d, %lu\n",
				msg, seqid, port, jiffies - tx->req_time);
		tx = NULL;
	}
	return tx;
}  /* proc_get_ts */

static int proc_ptp_get_timestamp(struct ptp_info *ptp, u8 *data,
	struct ptp_dev_info *info)
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

		if (opt->port >= ptp->ports)
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
		tx = proc_get_ts(ptp, opt->port, opt->msg,
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
	int *port, int *more)
{
	int p;
	struct ptp_tx_ts *tx;
	struct ptp_tx_ts *xts = NULL;

	*more = false;
	for (p = 0; p < ptp->ports; p++) {
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

		if (!tx->ts.timestamp && ptp->linked[p]) {
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
	struct ptp_dev_info *info, int *tx)
{
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
			opt->port = tx_msg.port + 1;
			opt->ts = tx_msg.ts;
		} else
			return DEV_IOC_UNIT_UNAVAILABLE;
	}
	else {
		struct ptp_tx_ts *xts;
		int port = 0;

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
			opt->port = port + 1;
		} else
			return -EAGAIN;
	}
	return 0;
}  /* proc_ptp_get_msg_info */

static int proc_ptp_set_msg_info(struct ptp_info *ptp, u8 *data,
	struct ptp_dev_info *info)
{
	struct ptp_msg_options *opt = (struct ptp_msg_options *) data;

	/* Used for testing. */
	if (7 == opt->msg) {
		struct ptp_msg_info *tx_msg;

		tx_msg = &ptp->tx_msg_info[opt->msg];
		tx_msg->data.port = opt->port;
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

		memcpy(&hdr.sourcePortIdentity, &opt->id,
			sizeof(struct ptp_port_identity));
		hdr.messageType = opt->msg;
		hdr.sequenceId = opt->seqid;
		hdr.domainNumber = opt->domain;
		opt->ts.timestamp = (opt->ts.t.sec << 30) |
			opt->ts.t.nsec;
		set_msg_info(ptp, &hdr, opt->port, opt->ts.timestamp);
	}
	return 0;
}  /* proc_ptp_set_msg_info */

static int parse_tsm_msg(struct ptp_dev_info *info, int len)
{
	struct ptp_info *ptp = info->ptp;
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
		ptp_setup_udp_msg(info, data, len, ptp_tsm_get_time_resp,
			&ts.t);
		break;
	}
	case TSM_CMD_DB_GET:
	{
		struct tsm_db *db = (struct tsm_db *) data;

		if (db->index <= (1 << 7)) {
			struct ptp_tx_ts *tx;
			int port = db->index >> 1;

			if (port > ptp->ports)
				break;
			tx = proc_get_ts(ptp, port, msg, ntohs(db->seqid),
				db->mac, info, len);
			if (tx) {
				ptp_setup_udp_msg(info, data, len,
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
				dbg_msg("  invalid gps: %lu\n", diff);
				ptp->gps_time.sec = 0;
			}
		}
		if (ptp->gps_time.sec) {
			proc_tsm_get_gps(ptp, data);
			ptp->gps_time.sec = 0;
			ptp->gps_req_time = 0;
		} else
			dbg_msg("  missed gps\n");
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
			u8 port = cfg->port - 1;

			if ((cfg->enable & 0x10) && port < ptp->ports &&
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
			ptp->update_sec_jiffies = jiffies;
			schedule_delayed_work(&ptp->check_pps,
				1200 * HZ / 1000);
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
dbg_msg("  first drift: %d\n", ptp->drift_set);
		if (!ptp->first_drift)
			ptp->first_drift = ptp->drift_set;
		ptp->ops->release(ptp);
		break;
	}
	default:
		dbg_msg("tsm cmd: %02X, %d\n", cmd, len);
	}
	return result;
}  /* parse_tsm_msg */

static struct ptp_info *ptp_priv;

static struct ptp_dev_info *alloc_dev_info(unsigned int minor)
{
	struct ptp_dev_info *info;

	info = kzalloc(sizeof(struct ptp_dev_info), GFP_KERNEL);
	if (info) {
		info->ptp = ptp_priv;
		sema_init(&info->sem, 1);
		mutex_init(&info->lock);
		init_waitqueue_head(&info->wait_udp);
		info->write_len = 1000;
		info->write_buf = kzalloc(info->write_len, GFP_KERNEL);
		info->read_max = 60000;
		info->read_buf = kzalloc(info->read_max, GFP_KERNEL);

		info->minor = minor;
		info->next = ptp_priv->dev[minor];
		ptp_priv->dev[minor] = info;
	}
	return info;
}  /* alloc_dev_info */

static void free_dev_info(struct ptp_dev_info *info)
{
	if (info) {
		struct ptp_info *ptp = info->ptp;
		unsigned int minor = info->minor;
		struct ptp_dev_info *prev = ptp->dev[minor];

		if (prev == info) {
			ptp->dev[minor] = info->next;
		} else {
			while (prev && prev->next != info)
				prev = prev->next;
			if (prev)
				prev->next = info->next;
		}
		kfree(info->read_buf);
		kfree(info->write_buf);
		kfree(info);
	}
}  /* free_dev_info */

static int ptp_dev_open(struct inode *inode, struct file *filp)
{
	struct ptp_dev_info *info = (struct ptp_dev_info *)
		filp->private_data;
	unsigned int minor = MINOR(inode->i_rdev);

	if (minor > 1)
		return -ENODEV;
	if (!info) {
		info = alloc_dev_info(minor);
		if (info)
			filp->private_data = info;
		else
			return -ENOMEM;
	}
	return 0;
}  /* ptp_dev_open */

static int ptp_dev_release(struct inode *inode, struct file *filp)
{
	struct ptp_dev_info *info = (struct ptp_dev_info *)
		filp->private_data;

	free_dev_info(info);
	filp->private_data = NULL;
	return 0;
}  /* ptp_dev_release */

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
	struct ptp_dev_info *info = parent->dev_info;
	u8 *data = parent->param.data;
	int port;
	u32 reg;
	u32 val;
	size_t width;
	int result = DEV_IOC_OK;
	struct ksz_sw *sw = container_of(ptp, struct ksz_sw, ptp_hw);

	parent->output = parent->option;
	switch (parent->cmd) {
	case DEV_CMD_INFO:
		switch (parent->subcmd) {
		case DEV_INFO_INIT:
			if (ptp->op_mode)
				ptp->tx_en = ptp->rx_en = 0;
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
				if ((cap & PTP_HAVE_MULT_DEVICES) &&
				    (cap & PTP_CAN_RX_TIMESTAMP))
					ptp->op_mode = 1;
				else if (cap & PTP_HAVE_MULT_DEVICES)
					ptp->op_mode = 2;
				else if (!(cap & (PTP_KNOW_ABOUT_MULT_PORTS |
				    PTP_HAVE_MULT_PORTS)))
					ptp->op_mode = 3;
				else if (cap & PTP_USE_RESERVED_FIELDS)
					ptp->op_mode = 0;
				else
					ptp->op_mode = 2;
				if (cap & PTP_CAN_RX_TIMESTAMP) {
					if (cap & PTP_KNOW_ABOUT_LATENCY) {
						ptp->rx_en &= ~(1 << 8);
						ptp->tx_en &= ~(1 << 8);
					} else {
						ptp->rx_en |= (1 << 8);
						ptp->tx_en |= (1 << 8);
					}
				}
				ptp->cap = cap;
dbg_msg("op_mode: %x %d %x\n", ptp->cap, ptp->op_mode, ptp->tx_en);
			}
			ptp_init_state(ptp);
			parent->output = ptp->drift_set;
			break;
		case DEV_INFO_EXIT:
			ptp_exit_state(ptp);
			break;
		case DEV_INFO_RESET:
			reg = parent->option;
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
			if ((ptp->op_mode > 0 || ptp->cap) && parent->option) {
				parent->output = ptp->drift_set;
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
	int option, void *data, size_t len, struct ptp_dev_info *info,
	int *output, int wait)
{
	struct ptp_access *access;
	struct ptp_work *work;
	int ret = 0;

	access = &ptp->hw_access;
	work = &access->works[access->index];
	if (work->used) {
		pr_alert("work full\n");
		return -EFAULT;
	}
	work->cmd = cmd;
	work->subcmd = subcmd;
	work->option = option;
	memcpy(work->param.data, data, len);
	work->dev_info = info;
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
		return ret;

	ret = work->result;
	if (DEV_IOC_OK == ret && DEV_CMD_GET == work->cmd)
		memcpy(data, work->param.data, len);
	*output = work->output;

hw_access_end:
	return ret;
}  /* proc_ptp_hw_access */

static void init_ptp_work(struct ptp_info *ptp)
{
	struct ptp_access *access;
	struct ptp_work *work;
	int i;

	access = &ptp->hw_access;
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
#if defined(NO_DIRECT_ACCESS)
	struct ksz_sw *sw = container_of(ptp, struct ksz_sw, ptp_hw);
#endif

	if (ptp->update_sec_jiffies) {
#ifndef NO_SEC_TIMESTAMP
		ptp->cur_time.sec++;
#else
#if defined(NO_DIRECT_ACCESS)
if (sw->info->iba.use_iba) {
#endif
#if 1
		ptp->ops->acquire(ptp);
		ptp->reg->get_time(ptp, &ptp->cur_time);
		ptp->ops->release(ptp);
#endif
#if defined(NO_DIRECT_ACCESS)
}
#endif
#endif
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
		schedule_delayed_work(&ptp->update_sec, 1000 * HZ / 1000);
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
	u32 rem;

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
			clk = div_u64_rem(clk, ptp->clk_divider, &rem);
		dbg_msg(" %u %u=%llu\n", clk_delay[i], hw_delay[i], clk);
		if (clk_delay[i] < clk_delay[5])
			clk_delay[5] = clk_delay[i];
		if (hw_delay[i] < hw_delay[5])
			hw_delay[5] = hw_delay[i];
	}
	clk = hw_delay[5];
	clk *= 1000000;
	if (ptp->clk_divider)
		clk = div_u64_rem(clk, ptp->clk_divider, &rem);
	dbg_msg("%u %llu\n", clk_delay[5], clk);
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
	dbg_msg("delay_ticks: %lu\n", ptp->delay_ticks);
}  /* test_access_time */

static void set_ptp_drift(struct ptp_info *ptp, int drift)
{
	drift /= 100;
	drift *= 100;
	drift = -drift;
	ptp->first_drift = ptp->drift_set = ptp->drift = drift;
	ptp->first_sec = 0;
	ptp->adjust = clk_adjust_val(drift, NANOSEC_IN_SEC);
	set_ptp_adjust(ptp, ptp->adjust);
	syntonize_clk(ptp);
	ptp->ptp_synt = true;
	dbg_msg("drift: %d\n", drift);
}  /* set_ptp_drift */

static void check_sys_time(struct ptp_info *ptp, unsigned long cur_jiffies,
	union ktime cur_ktime)
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
		u32 rem;
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
		drift_jiffies = div_s64_rem(drift_jiffies, passed_sec, &rem);

		cur_ktime.tv64 -= ptp->first_ktime.tv64;
		drift_ktime = cur_ktime.tv64 - passed_nsec;
		drift_ktime = div_s64_rem(drift_ktime, passed_sec, &rem);

		if (!ptp->clk_divider) {
			if (!ptp->first_drift)
				set_ptp_drift(ptp, (int) drift_ktime);
			else
				printk(KERN_INFO "%lld %lld\n",
					drift_jiffies, drift_ktime);
			return;
		}

		clk_cnt = div_u64_rem(ptp->total_clk_cnt, passed_sec, &rem);

		clk = ptp->total_clk_cnt * 1000000;
		clk = div_u64_rem(clk, ptp->clk_divider, &rem);
		drift_clk = clk;
		if (drift_clk < 0)
			ptp->overrides &= ~PTP_CHECK_SYS_TIME;
		drift_clk -= passed_nsec;
		drift_clk = div_s64_rem(drift_clk, passed_sec, &rem);

		if (!ptp->first_drift)
			set_ptp_drift(ptp, (int) drift_clk);
		else
			printk(KERN_INFO "%10llu %lld %lld %lld\n",
				clk_cnt, drift_clk, drift_jiffies, drift_ktime);
	}
}  /* check_sys_time */

static int dbg_ts_intr;
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
	union ktime cur_ktime;
	struct timespec ts;
	struct ksz_sw *sw = container_of(ptp, struct ksz_sw, ptp_hw);

	cur_ktime = ktime_get_real();
	ts = ktime_to_timespec(cur_ktime);

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

proc_chk_ts_intr:
	status = (int_status >> TS_INT_S) & PTP_TS_UNIT_M;
	if (!status)
		goto proc_ptp_port_intr;

	for (i = 0; i < MAX_TIMESTAMP_UNIT; i++) {
		tsi_bit = 1 << i;
		if (!(status & tsi_bit))
			continue;
if (!(status & ptp->ts_intr)) {
printk("  !!\n");
ptp->reg->rx_reset(ptp, i, NULL);
}
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
		if (i == ptp->pps_tsi) {
			struct ptp_utime sys_time;

			if (event->num > 1)
if (dbg_ts_intr < 20) {
dbg_msg(" events %d %x:%9u %x:%9u; %x\n", event->num,
event->t[0].sec, event->t[0].nsec,
event->t[event->num - 1].sec, event->t[event->num - 1].nsec,
ptp->cur_time.sec);
++dbg_ts_intr;
dbg_msg(" %d %d; %x %x %x\n", event->timeout, event->last,
ptp->ts_status, ptp->ts_intr, ptp->tsi_used);
}
#ifndef NO_SEC_TIMESTAMP
			ptp->cur_time.sec = event->t[0].sec;
			ptp->cur_time.nsec = event->t[0].nsec;
if (0 == ptp->cur_time.sec)
printk("  ???  ");
#if 1
if (dbg_ts_intr < 3) {
dbg_msg("%x:%9u\n", ptp->cur_time.sec, ptp->cur_time.nsec);
++dbg_ts_intr;
}
#endif
#ifndef NO_SEC_TIMESTAMP
			ptp->update_sec_jiffies = 0;
#endif
#endif
			ptp->sec_lo++;
			sys_time.sec = ts.tv_sec;
			sys_time.nsec = ts.tv_nsec;
			calc_udiff(&ptp->cur_time, &sys_time, &ptp->time_diff);
			if (!ptp->intr_sec)
				ptp->intr_sec = ptp->cur_time.sec;
#if 0
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
	}
	ptp_chk_rx_events(ptp);
	ptp->ts_status = 0;

proc_ptp_port_intr:

	goto proc_chk_trig_intr;

proc_ptp_intr_done:
	return;
}  /* proc_ptp_intr */

static void proc_ptp_tx_intr(struct ptp_info *ptp, int port)
{
	u32 reg;
	u16 status;
	struct ksz_sw *sw = container_of(ptp, struct ksz_sw, ptp_hw);

	reg = PORT_CTRL_ADDR(port, REG_PTP_PORT_TX_INT_STATUS__2);
	status = sw->reg->r16(sw, reg);
	if (status) {
		sw->reg->w16(sw, reg, status);
		status &= ptp->tx_intr;
		if (get_tx_time(ptp, port, status))
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
	int port;

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
		port--;
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
#if 0
printk("%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x.%04x %x %04x %x\n",
hdr.sourcePortIdentity.clockIdentity.addr[0],
hdr.sourcePortIdentity.clockIdentity.addr[1],
hdr.sourcePortIdentity.clockIdentity.addr[2],
hdr.sourcePortIdentity.clockIdentity.addr[3],
hdr.sourcePortIdentity.clockIdentity.addr[4],
hdr.sourcePortIdentity.clockIdentity.addr[5],
hdr.sourcePortIdentity.clockIdentity.addr[6],
hdr.sourcePortIdentity.clockIdentity.addr[7],
hdr.sourcePortIdentity.port,
hdr.messageType, hdr.sequenceId, hdr.domainNumber);
#endif
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
printk("%u:%09u\n", ts.t.sec, ts.t.nsec);
#endif
		ptp_data.ts.sec = ts.t.sec;
		ptp_data.ts.nsec = ts.t.nsec;
		err = copy_to_user(ifr->ifr_data, &ptp_data, sizeof(ptp_data));
		break;
	case PTP_GET_TIME:
	{
		struct timespec ts;
		struct ksz_ptp_time cur_time;
		struct ksz_ptp_time sys_time;

		ts = ktime_to_timespec(ktime_get_real());
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
		drift = ptp->drift_set;
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
	struct ptp_dev_info *info)
{
	struct ksz_request *req = (struct ksz_request *) arg;
	int len;
	int maincmd;
	int req_size;
	int subcmd;
	int output;
	u8 data[PARAM_DATA_SIZE];
	struct ptp_dev_info *dev;
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
			struct ksz_sw *sw = container_of(ptp,
				struct ksz_sw, ptp_hw);

			if (chk_ioctl_size(len, 6,
					SIZEOF_ksz_request,
					&req_size, &result, &req->param, data))
				goto dev_ioctl_resp;
			if (len < 6) {
				result = DEV_IOC_INVALID_LEN;
				break;
			}

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
			data[5] = ptp->ports;
			if (v2) {
				data[6] = sw->HOST_PORT + 1;
				data[7] = 0;
			} else
				data[5] = sw->HOST_PORT;
			if (!access_ok(VERIFY_WRITE, req->param.data, len) ||
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
				ptp_setup_udp_msg(dev, data, 4, NULL, NULL);
			ptp_setup_udp_msg(info, data, 4, NULL, NULL);
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
				false);
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
				false);
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
			if (!access_ok(VERIFY_WRITE, req->param.data,
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
				if (!access_ok(VERIFY_WRITE, req->param.data,
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
			if (!access_ok(VERIFY_WRITE, req->param.data,
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
			if (!access_ok(VERIFY_WRITE, req->param.data,
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
			if (!access_ok(VERIFY_WRITE, req->param.data,
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
			if (!access_ok(VERIFY_WRITE, req->param.data,
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
			if (!access_ok(VERIFY_WRITE, req->param.data,
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
			if (!access_ok(VERIFY_WRITE, req->param.data,
					sizeof(struct ptp_msg_options)) ||
					copy_to_user(req->param.data, data,
					sizeof(struct ptp_msg_options))) {
				err = -EFAULT;
				goto dev_ioctl_done;
			}
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

#ifdef HAVE_UNLOCKED_IOCTL
static long ptp_dev_ioctl(struct file *filp, unsigned int cmd,
	unsigned long arg)
#else
static int ptp_dev_ioctl(struct inode *inode, struct file *filp,
	unsigned int cmd, unsigned long arg)
#endif
{
	struct ptp_dev_info *info = (struct ptp_dev_info *)
		filp->private_data;
	struct ptp_info *ptp = info->ptp;
	int err = 0;

	if (_IOC_TYPE(cmd) != DEV_IOC_MAGIC)
		return -ENOTTY;
	if (_IOC_NR(cmd) > DEV_IOC_MAX)
		return -ENOTTY;
	if (_IOC_DIR(cmd) & _IOC_READ)
		err = !access_ok(VERIFY_WRITE, (void *) arg, _IOC_SIZE(cmd));
	else if (_IOC_DIR(cmd) & _IOC_WRITE)
		err = !access_ok(VERIFY_READ, (void *) arg, _IOC_SIZE(cmd));
	if (err) {
		printk(KERN_ALERT "err fault\n");
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
	struct ptp_dev_info *info = (struct ptp_dev_info *)
		filp->private_data;
	ssize_t result = 0;
	int rc;

	if (!info->read_len) {
		*offp = 0;
		rc = wait_event_interruptible(info->wait_udp,
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
	struct ptp_dev_info *info = (struct ptp_dev_info *)
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
		dbg_msg("tsm: %x\n", info->write_buf[0]);
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

static const struct file_operations ptp_dev_fops = {
	.read		= ptp_dev_read,
	.write		= ptp_dev_write,
#ifdef HAVE_UNLOCKED_IOCTL
	.unlocked_ioctl	= ptp_dev_ioctl,
#else
	.ioctl		= ptp_dev_ioctl,
#endif
	.open		= ptp_dev_open,
	.release	= ptp_dev_release,
};

static struct class *ptp_class;

static int init_ptp_device(int dev_major, char *dev_name, char *minor_name)
{
	int result;

	printk(KERN_INFO "  PTP driver %s %s\n", __DATE__, __TIME__);
	result = register_chrdev(dev_major, dev_name, &ptp_dev_fops);
	if (result < 0) {
		printk(KERN_WARNING "%s: can't get major %d\n", dev_name,
			dev_major);
		return result;
	}
	if (0 == dev_major)
		dev_major = result;
	ptp_class = class_create(THIS_MODULE, dev_name);
	if (IS_ERR(ptp_class)) {
		unregister_chrdev(dev_major, dev_name);
		return -ENODEV;
	}
	device_create(ptp_class, NULL, MKDEV(dev_major, 0), NULL, dev_name);
	device_create(ptp_class, NULL, MKDEV(dev_major, 1), NULL, minor_name);
	return dev_major;
}  /* init_ptp_device */

static void exit_ptp_device(int dev_major, char *dev_name)
{
	device_destroy(ptp_class, MKDEV(dev_major, 1));
	device_destroy(ptp_class, MKDEV(dev_major, 0));
	class_destroy(ptp_class);
	unregister_chrdev(dev_major, dev_name);
}  /* exit_ptp_device */

static void ptp_check(struct ptp_info *ptp)
{
	struct ptp_utime cur;
	struct ptp_utime now;
	struct ksz_sw *sw = container_of(ptp, struct ksz_sw, ptp_hw);

#if defined(NO_DIRECT_ACCESS)
do {
if (!sw->info->iba.use_iba) {
printk("%s\n", __func__);
	ptp->version = 2;
return;
}
} while (0);
#endif
	ptp->features |= PTP_ADJ_HACK;
	ptp->ops->acquire(ptp);
	ptp->reg->get_time(ptp, &cur);
	ptp->reg->adjust_time(ptp, true, 10, 0, true);
	ptp->reg->get_time(ptp, &now);
dbg_msg("%08x:%08x %08x:%08x\n", cur.sec, cur.nsec, now.sec, now.nsec);
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
		dbg_msg("%x:%u %x:%u\n", cur.sec, cur.nsec, now.sec, now.nsec);
		if (abs(now.sec - cur.sec) > 2) {
			ptp->reg->get_time(ptp, &now);
			dbg_msg("! %x:%u\n", now.sec, now.nsec);
			ptp->features |= PTP_ADJ_HACK;
			sw->reg->w16(sw, REG_PTP_CLK_CTRL, data);

			sw->reg->w16(sw, REG_PTP_CLK_CTRL,
				data | PTP_CLK_ADJ_ENABLE);
			ptp->reg->set_time(ptp, &cur);
			ptp->reg->adjust_time(ptp, false, 0, 800000000, true);
			ptp->reg->get_time(ptp, &now);
			dbg_msg("ok %x:%u\n", now.sec, now.nsec);
		}
		sw->cached.ptp_clk_ctrl = data;
		sw->reg->w16(sw, REG_PTP_CLK_CTRL, data);
	}
	ptp->version = 2;
	ptp->ops->release(ptp);
}  /* ptp_check */

static void ptp_set_identity(struct ptp_info *ptp, u8 *addr)
{
	memcpy(&ptp->clockIdentity.addr[0], &addr[0], 3);
	ptp->clockIdentity.addr[3] = 0xFF;
	ptp->clockIdentity.addr[4] = 0xFE;
	memcpy(&ptp->clockIdentity.addr[5], &addr[3], 3);
}  /* ptp_set_identity */

static void ptp_init(struct ptp_info *ptp, u8 *mac_addr)
{
	int i;

	ptp->get_delay = 100000;
	ptp->set_delay = 100000;
	ptp->delay_ticks = 2;
	ptp->access = create_singlethread_workqueue("ptp_access");
	init_ptp_work(ptp);
	mutex_init(&ptp->lock);
	for (i = 0; i < MAX_PTP_PORT; i++)
		init_waitqueue_head(&ptp->wait_ts[i]);
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
	ptp->cfg |= PTP_PDELAY_CHECK | PTP_DELAY_CHECK;
	ptp->cfg |= PTP_SYNC_CHECK;
#endif
	ptp->def_mode = ptp->mode;
	ptp->def_cfg = ptp->cfg;
	ptp->trig_intr = PTP_TRIG_UNIT_M;
	ptp->tx_intr = PTP_PORT_XDELAY_REQ_INT;
#if 0
	ptp->tx_intr = PTP_PORT_XDELAY_REQ_INT | PTP_PORT_PDELAY_RESP_INT |
		PTP_PORT_SYNC_INT;
#endif

#if !defined(NO_DIRECT_ACCESS)
	ptp_hw_enable(ptp);
#endif
	if (!ptp->ports)
		ptp->ports = MAX_PTP_PORT;
	ptp_check(ptp);
	if (!ptp->get_clk_cnt)
		ptp->get_clk_cnt = _get_clk_cnt;
	if (!ptp->test_access_time)
		ptp->test_access_time = _test_access_time;
#if !defined(NO_DIRECT_ACCESS)
	if (ptp->test_access_time)
		ptp->test_access_time(ptp);
#endif

	ptp->gps_tsi = MAX_TIMESTAMP_UNIT;
	ptp->gps_gpi = DEFAULT_GPS_GPI;
	ptp->pps_gpo = DEFAULT_PPS_GPO;
	ptp->pps_tsi = DEFAULT_PPS_TSI;
	ptp->pps_tso = DEFAULT_PPS_TSO;
	ptp->mhz_gpo = DEFAULT_MHZ_GPO;
	ptp->mhz_tso = DEFAULT_MHZ_TSO;
#if 0
	ptp->pps_gpo = MAX_GPIO;
#endif

	for (i = 0; i < MAX_TIMESTAMP_UNIT; i++)
		ptp->events[i].max = MAX_TIMESTAMP_EVENT_UNIT;

	init_msg_info(ptp->rx_msg_info, &ptp->rx_msg_lock);
	init_msg_info(ptp->tx_msg_info, &ptp->tx_msg_lock);
	ptp_init_hw(ptp);
	do {
		struct ksz_sw *sw = container_of(ptp, struct ksz_sw, ptp_hw);

		for (i = sw->phy_port_cnt; i < ptp->ports; i++)
			ptp->linked[i] = 1000;
	} while (0);

	ptp_priv = ptp;
	sprintf(ptp->dev_name[0], "ptp_dev");
	sprintf(ptp->dev_name[1], "ptp_event");
	ptp->dev_major = init_ptp_device(0, ptp->dev_name[0],
		ptp->dev_name[1]);

#ifdef CONFIG_PTP_1588_CLOCK
	micrel_ptp_probe(ptp);
#endif
}  /* ptp_init */

static void ptp_exit(struct ptp_info *ptp)
{
	ptp->ops->acquire(ptp);
	ptp->tx_intr = 0;
	ptp_tx_intr_enable(ptp);
	ptp->ops->release(ptp);

	if (ptp->access) {
		destroy_workqueue(ptp->access);
		ptp->access = NULL;
	}
	if (ptp->dev_major >= 0)
		exit_ptp_device(ptp->dev_major, ptp->dev_name[0]);

#ifdef CONFIG_PTP_1588_CLOCK
	micrel_ptp_remove(ptp);
#endif
}  /* ptp_exit */

enum {
	PROC_SET_PTP_FEATURES,
	PROC_SET_PTP_OVERRIDES,
	PROC_SET_PTP_VID,
};

static ssize_t sysfs_ptp_read(struct ptp_info *ptp, int proc_num, ssize_t len,
	char *buf)
{
	switch (proc_num) {
	case PROC_SET_PTP_FEATURES:
		len += sprintf(buf + len, "%08x:\n", ptp->features);
		len += sprintf(buf + len, "\t%08x = adjust hack\n",
			PTP_ADJ_HACK);
		len += sprintf(buf + len, "\t%08x = adjust sec\n",
			PTP_ADJ_SEC);
		break;
	case PROC_SET_PTP_OVERRIDES:
		len += sprintf(buf + len, "%08x:\n", ptp->overrides);
		len += sprintf(buf + len, "\t%08x = PTP port forwarding\n",
			PTP_PORT_FORWARD);
		len += sprintf(buf + len, "\t%08x = PTP port TX forwarding\n",
			PTP_PORT_TX_FORWARD);
		len += sprintf(buf + len, "\t%08x = PTP verify timestamp\n",
			PTP_VERIFY_TIMESTAMP);
		len += sprintf(buf + len, "\t%08x = PTP zero reserved field\n",
			PTP_ZERO_RESERVED_FIELD);
		len += sprintf(buf + len, "\t%08x = PTP check system time\n",
			PTP_CHECK_SYS_TIME);
		len += sprintf(buf + len, "\t%08x = PTP check sync time\n",
			PTP_CHECK_SYNC_TIME);
		break;
	case PROC_SET_PTP_VID:
		len += sprintf(buf + len, "0x%04x\n", ptp->vid);
		break;
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
#ifdef PTP_PROCESS
		if ((changes & (PTP_SYNT | PTP_SIM_2_STEP))) {
#ifdef PTP_2_STEP
			if (num & PTP_SIM_2_STEP) {
				ptp->sim_2_step = true;
				ptp->mode &= ~PTP_1STEP;
			} else {
				ptp->sim_2_step = false;
				ptp->mode |= PTP_1STEP;
			}
#endif
			if (num & (PTP_SYNT | PTP_SIM_2_STEP)) {
				ptp_init_state(ptp);
				if (num & PTP_SYNT) {
					ptp->sim = 1;
					ptp->I = 0;
					ptp->KP = 50;
					ptp->KI = 5;
				}
			} else {
				ptp_exit_state(ptp);
				dbg_msg("exit ptp\n");
			}
		}
#endif
		break;
	case PROC_SET_PTP_OVERRIDES:
		if ('0' != buf[0] || 'x' != buf[1])
			sscanf(buf, "%x", &num);
		changes = ptp->overrides ^ num;
		if ((changes & PTP_CHECK_SYS_TIME) &&
				(ptp->overrides & PTP_CHECK_SYS_TIME))
			ptp->first_sec = 0;
#if 1
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

static struct ptp_ops ptp_ops = {
	.acquire		= ptp_acquire,
	.release		= ptp_release,

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

	.sysfs_read		= sysfs_ptp_read,
	.sysfs_write		= sysfs_ptp_write,

	.drop_pkt		= ptp_drop_pkt,
	.get_rx_info		= ptp_get_rx_info,
	.set_tx_info		= ptp_set_tx_info,
};


