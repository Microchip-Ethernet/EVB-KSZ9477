/**
 * Micrel PTP common code
 *
 * Copyright (c) 2015-2016 Microchip Technology Inc.
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


#if 1
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
#define MAX_U32_SHIFT			32
#define MAX_DIVIDER_SHIFT		31

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
		adjust |= PTP_RATE_DIR << 16;
	return adjust;
}  /* clk_adjust_val */

static void ptp_tso_off(struct ptp_info *ptp, u8 tso, u16 tso_bit)
{
	ptp->reg->tx_off(ptp, tso);
	ptp->tso_intr &= ~tso_bit;
	ptp->tso_used &= ~tso_bit;
	ptp->tso_dev[tso] = NULL;
}  /* ptp_tso_off */

static inline void ptp_tx_reset(struct ptp_info *ptp, u16 tso_bit)
{
	ptp->reg->write(ptp, ADDR_16, TRIG_RESET, tso_bit);
}  /* ptp_tx_reset */

static inline void ptp_gpo_reset(struct ptp_info *ptp, int gpo, u16 tso_bit)
{
	ptp_tx_reset(ptp, tso_bit);
	ptp->cascade_gpo[gpo].tso &= ~tso_bit;
}  /* ptp_gpo_reset */

/* -------------------------------------------------------------------------- */

static void ptp_acquire(struct ptp_info *ptp)
{
	struct ksz_sw *sw = container_of(ptp, struct ksz_sw, ptp_hw);

	mutex_lock(sw->hwlock);
#ifdef PTP_SPI
	mutex_lock(sw->reglock);
#endif
}  /* ptp_acquire */

static void ptp_release(struct ptp_info *ptp)
{
	struct ksz_sw *sw = container_of(ptp, struct ksz_sw, ptp_hw);

#ifdef PTP_SPI
	mutex_unlock(sw->reglock);
#endif
	mutex_unlock(sw->hwlock);
}  /* ptp_release */

static u32 ptp_read(struct ptp_info *ptp, int addr, u32 reg)
{
	struct ksz_sw *sw = container_of(ptp, struct ksz_sw, ptp_hw);
	u32 ret = 0xffffffff;

	switch (addr) {
	case ADDR_16:
		ret = sw_r16(sw, reg);
		break;
	case ADDR_32:
		ret = sw_r32(sw, reg);
		break;
	case ADDR_8:
		ret = sw_r8(sw, reg);
		break;
	}
	return ret;
}  /* ptp_read */

static void ptp_write(struct ptp_info *ptp, int addr, u32 reg, u32 val)
{
	struct ksz_sw *sw = container_of(ptp, struct ksz_sw, ptp_hw);

	switch (addr) {
	case ADDR_16:
		sw_w16(sw, reg, val);
		break;
	case ADDR_32:
		sw_w32(sw, reg, val);
		break;
	case ADDR_8:
		sw_w8(sw, reg, val);
		break;
	}
}  /* ptp_write */

static void get_ptp_time(struct ptp_info *ptp, struct ptp_utime *t)
{
	u16 data;
	u8 subnsec;
	struct ksz_sw *sw = container_of(ptp, struct ksz_sw, ptp_hw);

	data = sw->cached.ptp_clk_ctrl;
	data |= PTP_READ_RTC;
	ptp_write(ptp, ADDR_16, PTP_CLK_CTRL, data);
	t->sec = ptp_read(ptp, ADDR_32, PTP_RTC_SEC_L);
	t->nsec = ptp_read(ptp, ADDR_32, PTP_RTC_NANOSEC_L);
	subnsec = ptp_read(ptp, ADDR_8, PTP_RTC_SUB_NANOSEC);
	add_nsec(t, subnsec * 8);
}  /* get_ptp_time */

static void set_ptp_time(struct ptp_info *ptp, struct ptp_utime *t)
{
	u16 data;
	struct ksz_sw *sw = container_of(ptp, struct ksz_sw, ptp_hw);

	data = sw->cached.ptp_clk_ctrl;
	ptp_write(ptp, ADDR_8, PTP_RTC_SUB_NANOSEC, 0);
	ptp_write(ptp, ADDR_32, PTP_RTC_SEC_L, t->sec);
	ptp_write(ptp, ADDR_32, PTP_RTC_NANOSEC_L, t->nsec);
	data |= PTP_LOAD_TIME;
	ptp_write(ptp, ADDR_16, PTP_CLK_CTRL, data);
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
	ctrl |= PTP_STEP_TIME;
	ptp_write(ptp, ADDR_32, PTP_RTC_SEC_L, sec);
	do {
		if (nsec > NANOSEC_IN_SEC - 1)
			nsec = NANOSEC_IN_SEC - 1;
		ptp_write(ptp, ADDR_32, PTP_RTC_NANOSEC_L, nsec);
		ptp_write(ptp, ADDR_16, PTP_CLK_CTRL, ctrl);
		val -= nsec;
		nsec = val;
	} while (val);
	if (adj_hack && (adj & PTP_CLK_ADJ_ENABLE))
		ptp_write(ptp, ADDR_16, PTP_CLK_CTRL, adj);
}  /* adjust_ptp_time */

static void adjust_sync_time(struct ptp_info *ptp, int diff, u32 interval,
	u32 duration)
{
	u32 adjust;

	adjust = clk_adjust_val(diff, interval);
	adjust |= PTP_TMP_RATE_ENABLE << 16;
	ptp_write(ptp, ADDR_32, PTP_RATE_DURATION_L, duration);
	ptp_write(ptp, ADDR_32, PTP_SUBNANOSEC_RATE_L, adjust);
}  /* adjust_sync_time */

static inline void ptp_rx_reset(struct ptp_info *ptp, u16 tsi_bit)
{
	ptp_write(ptp, ADDR_16, TS_RESET, tsi_bit);
}  /* ptp_rx_reset */

static void ptp_rx_off(struct ptp_info *ptp, u8 tsi)
{
	u16 ctrl;
	u16 tsi_bit = (1 << tsi);

	/* Disable previous timestamp interrupt. */
	if (ptp->ts_intr & tsi_bit) {
		ptp->ts_intr &= ~tsi_bit;
		ptp_write(ptp, ADDR_16, TS_INT_ENABLE, ptp->ts_intr);
	}

	/* Disable previous timestamp detection. */
	ctrl = ptp_read(ptp, ADDR_16, TS_ENABLE);
	if (ctrl & tsi_bit) {
		ctrl &= ~tsi_bit;
		ptp_write(ptp, ADDR_16, TS_ENABLE, ctrl);
	}

	/*
	 * Need to turn off cascade mode if it is used previously; otherwise,
	 * event counter keeps increasing.
	 */
	if (ptp->cascade_rx & tsi_bit) {
		ptp_rx_reset(ptp, tsi_bit);
		ptp->cascade_rx &= ~tsi_bit;
	}
}  /* ptp_rx_off */

static inline void ptp_rx_intr(struct ptp_info *ptp, u16 tsi_bit)
{
	ptp->ts_intr |= tsi_bit;
	ptp_write(ptp, ADDR_16, TS_INT_ENABLE, ptp->ts_intr);
}  /* ptp_rx_intr */

static inline void ptp_rx_on(struct ptp_info *ptp, u16 tsi_bit)
{
	u16 ctrl;

	ctrl = ptp_read(ptp, ADDR_16, TS_ENABLE);
	ctrl |= tsi_bit;
	ptp_write(ptp, ADDR_16, TS_ENABLE, ctrl);
}  /* ptp_rx_on */

static void ptp_rx_restart(struct ptp_info *ptp, u16 tsi_bit)
{
	u16 ctrl;

	ctrl = ptp_read(ptp, ADDR_16, TS_ENABLE);
	ctrl &= ~tsi_bit;
	ptp_write(ptp, ADDR_16, TS_ENABLE, ctrl);
	ctrl |= tsi_bit;
	ptp_write(ptp, ADDR_16, TS_ENABLE, ctrl);
}  /* ptp_rx_restart */

static void ptp_rx_event(struct ptp_info *ptp, u8 tsi, u8 gpi, u8 event,
	int intr)
{
	u32 reg;
	u16 ctrl;
	u16 tsi_bit = (1 << tsi);

	/* Config pattern. */
	reg = TSn_CONF(tsi);
	ctrl = event | ((gpi & 0xf) << 8);
	ptp_write(ptp, ADDR_16, reg, ctrl);

	/* Enable timestamp interrupt. */
	if (intr)
		ptp_rx_intr(ptp, tsi_bit);

	/* Enable timestamp detection. */
	ptp_rx_on(ptp, tsi_bit);
}  /* ptp_rx_event */

static void ptp_rx_cascade_event(struct ptp_info *ptp, u8 first, u8 total,
	u8 gpi, u8 event, int intr)
{
	int last;
	int tsi;
	u32 reg;
	u16 ctrl;
	u16 tail;
	int i;
	int prev;

	last = (first + total - 1) % MAX_TIMESTAMP_UNIT;
	tsi = last;
	tail = TS_CASCADE_TAIL;
	for (i = 1; i < total; i++) {
		reg = TSn_CONF(tsi);
		prev = tsi - 1;
		if (prev < 0)
			prev = MAX_TIMESTAMP_UNIT - 1;
		ctrl = event | ((gpi & 0xf) << 8);
		ctrl |= TS_CASCADE_EN | ((prev & 0xf) << 1);
		ctrl |= tail;
		ptp->cascade_rx |= (1 << tsi);
		ptp_write(ptp, ADDR_16, reg, ctrl);

		/* Enable timestamp interrupt. */
		if (intr)
			ptp->ts_intr |= (1 << tsi);
		--tsi;
		if (tsi < 0)
			tsi = MAX_TIMESTAMP_UNIT - 1;
		tail = 0;
	}
	reg = TSn_CONF(first);
	ctrl = event | ((gpi & 0xf) << 8);
	ctrl |= TS_CASCADE_EN | ((last & 0xf) << 1);
	ptp->cascade_rx |= (1 << first);
	ptp_write(ptp, ADDR_16, reg, ctrl);

	/* Enable timestamp interrupt. */
	if (intr)
		ptp_rx_intr(ptp, (1 << first));

	/* Enable timestamp detection. */
	ptp_rx_on(ptp, (1 << first));
}  /* ptp_rx_cascade_event */

static void ptp_read_event(struct ptp_info *ptp, u8 tsi)
{
	u32 reg;
	u16 ctrl;
	u16 tsi_bit = (1 << tsi);

	u32 reg_ns;
	u32 reg_s;
	u32 reg_sub;
	struct ptp_utime t;
	u16 sub;
	int max_ts;
	int num;
	int i;
	int edge;
	struct ptp_event *event = &ptp->events[tsi];
	int last = event->num;

	reg = TSn_EVENT_STATUS(tsi);
	ctrl = ptp_read(ptp, ADDR_16, reg);
	num = (ctrl & TS_NO_EVENT_DET_MASK) >> 1;
	max_ts = (num <= event->max) ? num : event->max;
	i = event->num;

	reg_ns = TSn_0_EVENT_NANOSEC_L(tsi) + 0x10 * i;
	reg_s = TSn_0_EVENT_SEC_L(tsi) + 0x10 * i;
	reg_sub = TSn_0_EVENT_SUB_NANOSEC(tsi) + 0x10 * i;
	for (; i < max_ts; i++) {
		t.nsec = ptp_read(ptp, ADDR_32, reg_ns);
		t.sec = ptp_read(ptp, ADDR_32, reg_s);
		sub = ptp_read(ptp, ADDR_16, reg_sub);
		edge = ((t.nsec >> 30) & 1);
		t.nsec <<= 2;
		t.nsec >>= 2;
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
		reg_ns += 0x10;
		reg_s += 0x10;
		reg_sub += 0x10;
	}
	event->num = max_ts;

	/* Indicate there is new event. */
	if (event->num > last)
		ptp->ts_status |= tsi_bit;
}  /* ptp_read_event */

static void ptp_tx_off(struct ptp_info *ptp, u8 tso)
{
	u16 ctrl;
	u16 tso_bit = (1 << tso);

	/* Disable previous trigger out if not already completed. */
	ctrl = ptp_read(ptp, ADDR_16, TRIG_EN);
	if (ctrl & tso_bit) {
		ctrl &= ~tso_bit;
		ptp_write(ptp, ADDR_16, TRIG_EN, ctrl);
	}

	/*
	 * Using cascade mode previously need to reset the trigger output so
	 * that an errorneous output will not be generated during next
	 * cascade mode setup.
	 */
	if (ptp->cascade_tx & tso_bit) {
		ptp_gpo_reset(ptp, ptp->outputs[tso].gpo, tso_bit);
		ptp->cascade_tx &= ~tso_bit;
	} else {
		u32 reg = TRIGn_CONF_1(tso);

		ctrl = ptp_read(ptp, ADDR_16, reg);
		if (ctrl & TRIG_CASCADE_EN) {
			ctrl &= ~TRIG_CASCADE_EN;
			ctrl &= ~TRIG_CASCADE_TAIL;
			ctrl |= TRIG_CASCADE_UPS_MASK;
			ptp_write(ptp, ADDR_16, reg, ctrl);
		}
	}
}  /* ptp_tx_off */

static void ptp_tx_on(struct ptp_info *ptp, u8 tso)
{
	u16 ctrl;
	u16 tso_bit = (1 << tso);

	ctrl = ptp_read(ptp, ADDR_16, TRIG_EN);
	ctrl |= tso_bit;
	ptp_write(ptp, ADDR_16, TRIG_EN, ctrl);
}  /* ptp_tx_on */

static void ptp_tx_trigger_time(struct ptp_info *ptp, u8 tso, u32 sec, u32 nsec)
{
	u32 reg;

	reg = TRIGn_TARGET_SEC_L(tso);
	ptp_write(ptp, ADDR_32, reg, sec);
	reg = TRIGn_TARGET_NANOSEC_L(tso);
	ptp_write(ptp, ADDR_32, reg, nsec);
}  /* ptp_tx_trigger_time */

static void ptp_tx_event(struct ptp_info *ptp, u8 tso, u8 gpo, u8 event,
	u32 pulse, u32 cycle, u16 cnt, u32 sec, u32 nsec, u32 iterate,
	int intr, int now, int opt)
{
	u32 reg;
	u16 ctrl;
	u16 tso_bit = (1 << tso);
	struct ptp_output *cur = &ptp->outputs[tso];

	/* Hardware immediately keeps level high on new GPIO if not reset. */
	if (cur->level && gpo != cur->gpo)
		ptp_gpo_reset(ptp, cur->gpo, tso_bit);

	/* Config pattern. */
	reg = TRIGn_CONF_1(tso);
	ctrl = ((event & 0x7) << 4);
	ctrl |= (gpo & 0xf);
	if (intr)
		ctrl |= TRIG_NOTIFY;
	if (now)
		ctrl |= TRIG_NOW;
	if (opt)
		ctrl |= TRIG_CLK_OPT;
	ctrl |= TRIG_CASCADE_UPS_MASK;
	ptp_write(ptp, ADDR_16, reg, ctrl);

	/* Config pulse width. */
	if (TRIG_REG_OUTPUT == event) {
		reg = TRIGn_BIT_PATTERN(tso);
		ptp_write(ptp, ADDR_16, reg, (u16) pulse);
		cur->level = 0;
		if (cnt) {
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
		else if (tso != 11 && pulse > 0xffff)
			pulse = 0xffff;
		reg = TRIGn_PULSE_WIDTH(tso);
		ptp_write(ptp, ADDR_16, reg, (u16) pulse);
		if (11 == tso) {
			if (pulse > 0xffffff)
				pulse = 0xffffff;
			ctrl = ptp_read(ptp, ADDR_16, TRIG_PPS_WS);
			ctrl &= ~TRIG_PPS_WS_MASK;
			ctrl |= ((pulse >> 16) & TRIG_PPS_WS_MASK);
			ptp_write(ptp, ADDR_16, TRIG_PPS_WS, ctrl);
		}
	}

	/* Config cycle width. */
	if (event >= TRIG_NEG_PERIOD) {
		int min_cycle = pulse * PULSE_NSEC + MIN_CYCLE_NSEC;

		if (cycle < min_cycle)
			cycle = min_cycle;
		reg = TRIGn_CYCLE_WIDTH_L(tso);
		ptp_write(ptp, ADDR_32, reg, cycle);

		/* Config trigger count. */
		reg = TRIGn_PER_OCCUR(tso);
		ptp_write(ptp, ADDR_16, reg, cnt);
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
	u32 reg;
	u16 ctrl;
	u32 nsec;
	u32 pulse = (20000000 / 8);	/* 20 ms */
	u32 cycle = 1000000000;
	u16 cnt = 0;
	u8 tso = ptp->pps_tso;
	u8 event = TRIG_POS_PERIOD;

	ptp_tx_off(ptp, tso);

	/* Config pattern. */
	reg = TRIGn_CONF_1(tso);
	ctrl = ((event & 0x7) << 4);
	ctrl |= (gpo & 0xf);
	ctrl |= TRIG_NOTIFY;
	ctrl |= TRIG_NOW;
	ctrl |= TRIG_CASCADE_UPS_MASK;
	ptp_write(ptp, ADDR_16, reg, ctrl);

	/* Config pulse width. */
	reg = TRIGn_PULSE_WIDTH(tso);
	if (11 != tso && pulse > 0xffff)
		pulse = 0xffff;
	ptp_write(ptp, ADDR_16, reg, (u16) pulse);
	if (11 == tso) {
		if (pulse > 0xffffff)
			pulse = 0xffffff;
		ctrl = ptp_read(ptp, ADDR_16, TRIG_PPS_WS);
		ctrl &= ~TRIG_PPS_WS_MASK;
		ctrl |= ((pulse >> 16) & TRIG_PPS_WS_MASK);
		ptp_write(ptp, ADDR_16, TRIG_PPS_WS, ctrl);
	}

	/* Config cycle width. */
	reg = TRIGn_CYCLE_WIDTH_L(tso);
	ptp_write(ptp, ADDR_32, reg, cycle);

	/* Config trigger count. */
	reg = TRIGn_PER_OCCUR(tso);
	ptp_write(ptp, ADDR_16, reg, cnt);

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
	u32 reg;
	u16 ctrl;
	u32 pulse = 6;
	u32 cycle = 200;
	u16 cnt = 0;
	u8 event = TRIG_POS_PERIOD;

	/* Config pattern. */
	reg = TRIGn_CONF_1(tso);
	ctrl = ((event & 0x7) << 4);
	ctrl |= (gpo & 0xf);
	ctrl |= TRIG_NOTIFY;
	ctrl |= TRIG_CASCADE_UPS_MASK;
	if (1 == tso)
		ctrl |= TRIG_CLK_OPT;
	ptp_write(ptp, ADDR_16, reg, ctrl);

	/* Config pulse width. */
	reg = TRIGn_PULSE_WIDTH(tso);
	if (11 != tso && pulse > 0xffff)
		pulse = 0xffff;
	ptp_write(ptp, ADDR_16, reg, (u16) pulse);
	if (11 == tso) {
		if (pulse > 0xffffff)
			pulse = 0xffffff;
		ctrl = ptp_read(ptp, ADDR_16, TRIG_PPS_WS);
		ctrl &= ~TRIG_PPS_WS_MASK;
		ctrl |= ((pulse >> 16) & TRIG_PPS_WS_MASK);
		ptp_write(ptp, ADDR_16, TRIG_PPS_WS, ctrl);
	}

	/* Config cycle width. */
	reg = TRIGn_CYCLE_WIDTH_L(tso);
	ptp_write(ptp, ADDR_32, reg, cycle);

	/* Config trigger count. */
	reg = TRIGn_PER_OCCUR(tso);
	ptp_write(ptp, ADDR_16, reg, cnt);

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

static void ptp_tx_cascade_on(struct ptp_info *ptp, u8 tso, u8 first, u8 last,
	u16 repeat)
{
	u32 reg;
	u16 ctrl;
	int repeat_reg = 0;

	reg = TRIGn_CONF_1(tso);
	ctrl = ptp_read(ptp, ADDR_16, reg);
	ctrl |= TRIG_CASCADE_EN;
	ctrl &= ~TRIG_CASCADE_UPS_MASK;
	if (tso == first)
		ctrl |= ((last & 0xf) << 10);
	else
		ctrl |= (((tso - 1) & 0xf) << 10);
	if (repeat && tso == last) {
		ctrl |= TRIG_CASCADE_TAIL;
		if (((ctrl >> 4) & 0xf) != TRIG_REG_OUTPUT)
			repeat_reg = TRIGn_BIT_PATTERN(tso);
		else
			repeat_reg = TRIGn_PULSE_WIDTH(tso);
	}
	ptp_write(ptp, ADDR_16, reg, ctrl);
	if (repeat_reg)
		ptp_write(ptp, ADDR_16, repeat_reg, repeat - 1);
}  /* ptp_tx_cascade_on */

static void ptp_tx_cascade_cycle(struct ptp_info *ptp, u8 tso, u32 nsec)
{
	u32 reg;

	reg = TRIGn_ITERATE_TIME_L(tso);
	ptp_write(ptp, ADDR_32, reg, nsec);
}  /* ptp_tx_cascade_cycle */

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
	tso = first;
	for (i = 0; i < total; i++, tso++) {
		cur = &ptp->outputs[tso];
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

	ctrl = ptp->reg->read(ptp, ADDR_16, PTP_DOMAIN_VERSION) &
		~PTP_DOMAIN_MASK;
	ctrl |= domain;
	ptp->reg->write(ptp, ADDR_16, PTP_DOMAIN_VERSION, ctrl);
}  /* set_ptp_domain */

static void set_ptp_mode(struct ptp_info *ptp, u16 mode)
{
	u16 val;
	u16 sav;

	val = ptp->reg->read(ptp, ADDR_16, PTP_MSG_CONF1);
	sav = val;
	val &= ~(PTP_1STEP | PTP_TC_P2P | PTP_MASTER);
	val |= mode;
	if (val != sav)
		ptp->reg->write(ptp, ADDR_16, PTP_MSG_CONF1, val);
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
	ptp->reg->write(ptp, ADDR_32, PTP_SUBNANOSEC_RATE_L, adjust);
}  /* set_ptp_adjust */

static inline void unsyntonize_clk(struct ptp_info *ptp)
{
	u16 ctrl;
	struct ksz_sw *sw = container_of(ptp, struct ksz_sw, ptp_hw);

	ctrl = sw->cached.ptp_clk_ctrl;
	ctrl &= ~PTP_CLK_ADJ_ENABLE;
	sw->cached.ptp_clk_ctrl = ctrl;
	ptp->reg->write(ptp, ADDR_16, PTP_CLK_CTRL, ctrl);
}  /* unsyntonize_clk */

static void syntonize_clk(struct ptp_info *ptp)
{
	u16 ctrl;
	struct ksz_sw *sw = container_of(ptp, struct ksz_sw, ptp_hw);

	ctrl = sw->cached.ptp_clk_ctrl;
	ctrl |= PTP_CLK_ADJ_ENABLE;
	sw->cached.ptp_clk_ctrl = ctrl;
	ptp->reg->write(ptp, ADDR_16, PTP_CLK_CTRL, ctrl);
}  /* syntonize_clk */

static u16 get_ptp_delay(struct ptp_info *ptp, int port, u32 reg)
{
	reg += PTP_PORT_INTERVAL(port);
	return ptp->reg->read(ptp, ADDR_16, reg);
}  /* get_ptp_delay */

static void set_ptp_delay(struct ptp_info *ptp, int port, u32 reg, u16 nsec)
{
	reg += PTP_PORT_INTERVAL(port);
	ptp->reg->write(ptp, ADDR_16, reg, nsec);
}  /* set_ptp_delay */

static u16 get_ptp_ingress(struct ptp_info *ptp, int port)
{
	return get_ptp_delay(ptp, port, PTP_PORT1_RX_MAC2PHY_DELAY);
}

static u16 get_ptp_egress(struct ptp_info *ptp, int port)
{
	return get_ptp_delay(ptp, port, PTP_PORT1_TX_MAC2PHY_DELAY);
}

static short get_ptp_asym(struct ptp_info *ptp, int port)
{
	short val;

	val = get_ptp_delay(ptp, port, PTP_PORT1_ASYM_DELAY);
	if (val & 0x8000)
		val = -(val & ~0x8000);
	return val;
}

static u16 get_ptp_link(struct ptp_info *ptp, int port)
{
	return get_ptp_delay(ptp, port, PTP_PORT1_LINK_DELAY);
}

static void set_ptp_ingress(struct ptp_info *ptp, int port, u16 nsec)
{
	set_ptp_delay(ptp, port, PTP_PORT1_RX_MAC2PHY_DELAY, nsec);
}

static void set_ptp_egress(struct ptp_info *ptp, int port, u16 nsec)
{
	set_ptp_delay(ptp, port, PTP_PORT1_TX_MAC2PHY_DELAY, nsec);
}

static void set_ptp_asym(struct ptp_info *ptp, int port, short nsec)
{
	if (nsec < 0)
		nsec = -nsec | 0x8000;
	set_ptp_delay(ptp, port, PTP_PORT1_ASYM_DELAY, nsec);
}

static void set_ptp_link(struct ptp_info *ptp, int port, u16 nsec)
{
	set_ptp_delay(ptp, port, PTP_PORT1_LINK_DELAY, nsec);
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
			tx->msg->hdr.reserved2 = (1 << port);
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

static int get_tx_time(struct ptp_info *ptp, u16 status)
{
	u32 reg = 0;
	int port;
	int delay;
	u32 xts;
	u32 *pts;
	struct ptp_tx_ts *tx = NULL;
	struct ptp_hw_ts *htx = NULL;

	while (status) {
		/* Do port 1 first. */
		if (status & (TS_PORT1_INT_XDELAY | TS_PORT1_INT_SYNC))
			port = 0;
		else if (status & (TS_PORT2_INT_XDELAY | TS_PORT2_INT_SYNC))
			port = 1;
		else
			break;
		xts = 0;
		pts = NULL;
		delay = ptp->tx_latency[port];
		if (status & TS_PORT1_INT_XDELAY) {
			reg = PTP_PORT1_XDELAY_TIMESTAMP_L;
			pts = &ptp->xdelay_ts[port];
			tx = &ptp->tx_dreq[port];
			htx = &ptp->hw_dreq[port];
			status &= ~TS_PORT1_INT_XDELAY;
		} else if (status & TS_PORT1_INT_SYNC) {
			reg = PTP_PORT1_SYNC_TIMESTAMP_L;
			tx = &ptp->tx_sync[port];
			htx = &ptp->hw_sync[port];
			status &= ~TS_PORT1_INT_SYNC;
		} else if (status & TS_PORT2_INT_XDELAY) {
			reg = PTP_PORT1_XDELAY_TIMESTAMP_L;
			pts = &ptp->xdelay_ts[port];
			tx = &ptp->tx_dreq[port];
			htx = &ptp->hw_dreq[port];
			status &= ~TS_PORT2_INT_XDELAY;
		} else if (status & TS_PORT2_INT_SYNC) {
			reg = PTP_PORT1_SYNC_TIMESTAMP_L;
			tx = &ptp->tx_sync[port];
			htx = &ptp->hw_sync[port];
			status &= ~TS_PORT2_INT_SYNC;
		}

		/* PDELAY_REQ and PDELAY_RESP share same interrupt. */
		if (pts) {
			reg += PTP_PORT_INTERVAL(port);
			xts = ptp->reg->read(ptp, ADDR_32, reg);

			if (xts != *pts) {
				*pts = xts;
				htx->ts.timestamp = xts;
				save_tx_ts(ptp, tx, htx, delay, port);
			}

			reg = PTP_PORT1_PDRESP_TIMESTAMP_L;
			pts = &ptp->pdresp_ts[port];
			tx = &ptp->tx_resp[port];
			htx = &ptp->hw_resp[port];

			reg += PTP_PORT_INTERVAL(port);
			xts = ptp->reg->read(ptp, ADDR_32, reg);
			if (xts != *pts) {
				delay = ptp->tx_latency[port];
				*pts = xts;
				htx->ts.timestamp = xts;
				save_tx_ts(ptp, tx, htx, delay, port);
			}
		} else {
			reg += PTP_PORT_INTERVAL(port);
			htx->ts.timestamp = ptp->reg->read(ptp, ADDR_32, reg);
			save_tx_ts(ptp, tx, htx, delay, port);
		}
	}
	if (!htx)
		return false;

	return true;
}  /* get_tx_time */

static void ptp_update_sec(struct work_struct *work)
{
	struct delayed_work *dwork = to_delayed_work(work);
	struct ptp_info *ptp =
		container_of(dwork, struct ptp_info, update_sec);

	if (ptp->update_sec_jiffies) {
		ptp->cur_time.sec++;
		schedule_delayed_work(&ptp->update_sec, 1000 * HZ / 1000);
	}
}  /* ptp_update_sec */

static void generate_tx_event(struct ptp_info *ptp, int gpo)
{
	struct ptp_utime t;

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
	ptp->reg->rx_event(ptp, ptp->gps_tsi, ptp->gps_gpi, TS_DETECT_RISE,
		true);
	ptp->ops->release(ptp);
}  /* prepare_gps */

static void prepare_pps(struct ptp_info *ptp)
{
	ptp->ops->acquire(ptp);
	ptp->tso_used |= (1 << ptp->pps_tso);
#ifdef ENABLE_10_MHZ_CLK
	ptp->tso_used |= (1 << ptp->mhz_tso);
	ptp->tso_used |= (1 << 1);
#endif
	generate_tx_event(ptp, ptp->pps_gpo);
	ptp->tsi_used |= (1 << ptp->pps_tsi);
	ptp->events[ptp->pps_tsi].event = 1;
	ptp->reg->rx_event(ptp, ptp->pps_tsi, ptp->pps_gpo, TS_DETECT_RISE,
		true);
	ptp->ops->release(ptp);
}  /* prepare_pps */

/* -------------------------------------------------------------------------- */

static void ptp_start(struct ptp_info *ptp, int init)
{
	u16 ctrl;
	struct timespec ts;
	struct ptp_utime t;

	ptp_acquire(ptp);
	ctrl = ptp_read(ptp, ADDR_16, PTP_MSG_CONF1);
	if (ctrl == ptp->mode) {
		ptp->cfg = ptp_read(ptp, ADDR_16, PTP_MSG_CONF2);
		ptp->domain = ptp_read(ptp, ADDR_16, PTP_DOMAIN_VERSION) &
			PTP_DOMAIN_MASK;
		if (!init) {
			ptp_release(ptp);
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
	ptp_write(ptp, ADDR_16, PTP_MSG_CONF1, ptp->mode);
	ptp_write(ptp, ADDR_16, PTP_MSG_CONF2, ptp->cfg);
	ptp_write(ptp, ADDR_16, TRIG_INT_ENABLE, ptp->trig_intr);
	ptp_write(ptp, ADDR_16, TS_INT_ENABLE, ptp->ts_intr);
	ptp_release(ptp);

	ts = ktime_to_timespec(ktime_get_real());
	t.sec = ts.tv_sec;
	t.nsec = ts.tv_nsec;
	ptp_acquire(ptp);
	set_ptp_time(ptp, &t);
	ptp->cur_time = t;
	ptp_release(ptp);

	prepare_pps(ptp);
	ptp->started = true;
}  /* ptp_start */

/* -------------------------------------------------------------------------- */

static int ptp_poll_event(struct ptp_info *ptp, u8 tsi)
{
	int max_ts;
	int num;
	u16 status;
	u16 tsi_bit = (1 << tsi);
	u32 reg = TSn_EVENT_STATUS(tsi);
	struct ptp_event *event = &ptp->events[tsi];

	status = ptp->reg->read(ptp, ADDR_16, reg);
	num = (status & TS_NO_EVENT_DET_MASK) >> 1;
	max_ts = (num <= event->max) ? num : event->max;
	if (max_ts > event->num) {
		ptp->ops->acquire(ptp);
		status = ptp->reg->read(ptp, ADDR_16, TS_INT_STATUS);
		if (status & tsi_bit)
			ptp->reg->write(ptp, ADDR_16, TS_INT_STATUS, tsi_bit);
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

static void execute(struct ptp_info *ptp, struct work_struct *work)
{
#ifdef PTP_SPI
	queue_work(ptp->access, work);
#else
	work->func(work);
#endif
}  /* execute */

static int ptp_stop(struct ptp_info *ptp)
{
	struct ksz_sw *sw = container_of(ptp, struct ksz_sw, ptp_hw);

#ifdef PTP_SPI
	flush_work(&ptp->adj_clk);
	flush_workqueue(ptp->access);
#endif
	ptp->update_sec_jiffies = 0;
	ptp->ops->acquire(ptp);
	ptp->reg->write(ptp, ADDR_16, REG_RESET_CTRL,
		PTP_SOFTWARE_RESET);
	udelay(1);
	ptp->reg->write(ptp, ADDR_16, REG_RESET_CTRL, 0);
	sw->cached.ptp_clk_ctrl = ptp->reg->read(ptp, ADDR_16, PTP_CLK_CTRL);
	ptp->ptp_synt = false;
	ptp->started = false;
	ptp->first_drift = ptp->drift_set = ptp->drift = 0;
	ptp->ops->release(ptp);
	return false;
}  /* ptp_stop */

static void init_tx_ts(struct ptp_tx_ts *ts)
{
	ts->ts.timestamp = 0;
	ts->req_time = 0;
	ts->resp_time = 0;
	ts->missed = false;
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

static void ptp_init_state(struct ptp_info *ptp)
{
	int port;
	u32 reg;
	struct ptp_utime t;

	mutex_lock(&ptp->lock);
	ptp->udp_head = ptp->udp_tail = 0;
	for (reg = 0; reg < MAX_TSM_UDP_CNT; reg++)
		ptp->udp[reg].len = 0;
	mutex_unlock(&ptp->lock);

	if (!ptp->started)
		return;
	ptp->reg->start(ptp, false);

	/* Stop automatic drift adjustment if PTP operation is started. */
	if (!ptp->first_drift)
		ptp->first_drift = 1;

	ptp->ops->acquire(ptp);
	for (port = 0; port < MAX_PTP_PORT; port++) {
		ptp->hw_sync[port].ts.timestamp = 0;
		ptp->hw_sync[port].sending = false;
		ptp->hw_dreq[port].ts.timestamp = 0;
		ptp->hw_dreq[port].sending = false;
		ptp->hw_resp[port].ts.timestamp = 0;
		ptp->hw_resp[port].sending = false;
		init_tx_ts(&ptp->tx_sync[port]);
		init_tx_ts(&ptp->tx_dreq[port]);
		init_tx_ts(&ptp->tx_resp[port]);
		reg = PTP_PORT1_XDELAY_TIMESTAMP_L + PTP_PORT_INTERVAL(port);
		ptp->xdelay_ts[port] = ptp->reg->read(ptp, ADDR_32, reg);
		reg = PTP_PORT1_PDRESP_TIMESTAMP_L + PTP_PORT_INTERVAL(port);
		ptp->pdresp_ts[port] = ptp->reg->read(ptp, ADDR_32, reg);
		ptp->rx_latency[port] = get_ptp_ingress(ptp, port);
		ptp->tx_latency[port] = get_ptp_egress(ptp, port);
		ptp->asym_delay[port] = get_ptp_asym(ptp, port);
		ptp->peer_delay[port] = get_ptp_link(ptp, port);
		set_ptp_link(ptp, port, 0);
		dbg_msg("%d = %d %d %d; %d\n", port,
			ptp->rx_latency[port],
			ptp->tx_latency[port],
			ptp->asym_delay[port],
			ptp->peer_delay[port]);
	}

	ptp->adjust_offset = 0;
	ptp->offset_changed = 0;

	if (!ptp->ptp_synt) {
		syntonize_clk(ptp);
		ptp->ptp_synt = true;
	}
	ptp->reg->get_time(ptp, &t);
	ptp->cur_time = t;
	ptp->ops->release(ptp);
}  /* ptp_init_state */

static void ptp_exit_state(struct ptp_info *ptp)
{
	if (ptp->mode & PTP_MASTER) {
		u16 data;

		ptp->ops->acquire(ptp);
		data = ptp->reg->read(ptp, ADDR_16, PTP_MSG_CONF1);
		data &= ~PTP_MASTER;
		ptp->reg->write(ptp, ADDR_16, PTP_MSG_CONF1, data);
		ptp->ops->release(ptp);
		ptp->mode &= ~PTP_MASTER;
		ptp->def_mode &= ~PTP_MASTER;
	}
	ptp->adjust_offset = 0;
	ptp->offset_changed = 0;
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

static int update_ptp_msg(u8 *data, u32 port, u32 overrides)
{
	struct ethhdr *eth = (struct ethhdr *) data;
	struct vlan_ethhdr *vlan = (struct vlan_ethhdr *) data;
	struct iphdr *iph;
	struct ipv6hdr *ip6h;
	struct ptp_msg *msg;
	u32 dst;
	u8 src;
	struct udphdr *udp = NULL;
	int ipv6 = 0;
	int udp_check = 0;

	do {
		if (eth->h_proto == htons(0x88F7)) {
			msg = (struct ptp_msg *)(eth + 1);
			break;
		}

		if (eth->h_proto == htons(ETH_P_8021Q)) {
			if (vlan->h_vlan_encapsulated_proto == htons(0x88F7)) {
				msg = (struct ptp_msg *)(vlan + 1);
				break;
			}
			ipv6 = vlan->h_vlan_encapsulated_proto ==
				htons(ETH_P_IPV6);
			if (vlan->h_vlan_encapsulated_proto != htons(ETH_P_IP)
					&& !ipv6)
				return false;
			ip6h = (struct ipv6hdr *)(vlan + 1);
			iph = (struct iphdr *)(vlan + 1);
		} else {
			ipv6 = eth->h_proto == htons(ETH_P_IPV6);
			if (eth->h_proto != htons(ETH_P_IP) && !ipv6)
				return false;
			ip6h = (struct ipv6hdr *)(eth + 1);
			iph = (struct iphdr *)(eth + 1);
		}

		if (ipv6) {
			if (ip6h->nexthdr != IPPROTO_UDP)
				return false;

			udp = (struct udphdr *)(ip6h + 1);
		} else {
			if (iph->protocol != IPPROTO_UDP)
				return false;

			udp = (struct udphdr *)(iph + 1);
		}

		if (udp->dest != htons(319) && udp->dest != htons(320))
			return false;
		msg = (struct ptp_msg *)(udp + 1);
	} while (0);
	if (msg->hdr.versionPTP < 2)
		return false;
	if ((overrides & PTP_VERIFY_TIMESTAMP) &&
			PDELAY_RESP_MSG == msg->hdr.messageType &&
			msg->hdr.flagField.flag.twoStepFlag) {
		struct ptp_utime rx;
		u32 timestamp;
		int i;
		u16 *data = (u16 *) &msg->hdr.reserved3;

		rx.nsec = ntohl(msg->data.pdelay_resp.requestReceiptTimestamp.
			nsec);
		rx.sec = ntohl(msg->data.pdelay_resp.requestReceiptTimestamp.
			sec.lo);
		timestamp = (rx.sec << 30) | rx.nsec;
		for (i = 0; i < 2; i++)
			udp_check += ntohs(data[i]);
		msg->hdr.reserved3 = htonl(timestamp);
		for (i = 0; i < 2; i++)
			udp_check -= ntohs(data[i]);
	}
	dst = port >> 16;
	port &= 0xffff;
	src = msg->hdr.reserved2;

	/* No destination port specified, use whatever port assigned. */
	if (!src)
		src = port;

	/* No change if all ports is specified, or all ports is assigned. */
	else if (!(overrides & PTP_KEEP_DST_PORT) &&
			src != 3 && port != 0 && port != 3)
		src = port;
	port = src;
	if (overrides & PTP_UPDATE_DST_PORT) {
		switch (msg->hdr.messageType) {
		case PDELAY_REQ_MSG:
		case PDELAY_RESP_MSG:
		case PDELAY_RESP_FOLLOW_UP_MSG:

			/* Ports are always open for Pdelay messages. */
			dst = 3;

			/* Force to all ports to send message. */
			if (!src)
				src = 3;
			port = src & dst;
			break;
		default:
			port = src & dst;

			/*
			 * Zero port still can send message through an open
			 * port, which is not what the application wants.
			 * Need to have the network driver not to send the
			 * packet to workaround the problem.
			 */
			if (!port && src && src != 3)
				return true;
			break;
		}
	}
	if (msg->hdr.reserved2 != port) {
		u8 data = msg->hdr.reserved2;

		udp_check += data;
		msg->hdr.reserved2 = (u8) port;
		udp_check -= port;
	}
	if ((overrides & PTP_ZERO_RESERVED_FIELD) && msg->hdr.reserved3 &&
			(PDELAY_RESP_MSG != msg->hdr.messageType ||
			msg->hdr.flagField.flag.twoStepFlag)) {
		int i;
		u16 *data = (u16 *) &msg->hdr.reserved3;

		for (i = 0; i < 2; i++)
			udp_check += ntohs(data[i]);
		msg->hdr.reserved3 = 0;
	}
	if (udp_check) {
		u16 check;

		/* Zero checksum in IPv4. */
		if (udp && !ipv6 && !udp->check)
			udp = NULL;
		if (udp) {
			check = ntohs(udp->check);
			udp_check += check;
			udp_check = (udp_check >> 16) + (udp_check & 0xffff);
			udp_check += (udp_check >> 16);
			check = (u16) udp_check;
			if (!check)
				check = -1;
			udp->check = htons(check);
		}
	}
	return false;
}  /* update_ptp_msg */

static void get_rx_tstamp(void *ptr, struct sk_buff *skb)
{
	struct ptp_info *ptp = ptr;
	struct ptp_msg *msg;
	u8 port;
	int delay;
	struct ptp_ts ts;
	u64 ns;
	struct skb_shared_hwtstamps *shhwtstamps = skb_hwtstamps(skb);

	if (!shhwtstamps)
		return;
	if (ptp->rx_msg_parsed)
		msg = ptp->rx_msg;
	else {
		msg = check_ptp_event(skb->data);
		ptp->rx_msg_parsed = true;
		ptp->rx_msg = msg;
	}
	if (!msg)
		return;

	ts.timestamp = ntohl(msg->hdr.reserved3);
	update_ts(&ts, ptp->cur_time.sec);
	if (ptp->rx_en & (1 << 8)) {
		port = msg->hdr.reserved2;
		if (port)
			port--;
		delay = ptp->rx_latency[port];
		sub_nsec(&ts.t, delay);
	}

	ns = (u64) ts.t.sec * NANOSEC_IN_SEC + ts.t.nsec;
	memset(shhwtstamps, 0, sizeof(*shhwtstamps));
	shhwtstamps->hwtstamp = ns_to_ktime(ns);
}  /* get_rx_tstamp */

static void get_tx_tstamp(struct ptp_info *ptp, struct sk_buff *skb)
{
	int cnt;
	int p;
	struct ptp_msg *msg;
	u8 port;
	struct ptp_tx_ts *tx;
	struct sk_buff *orig_skb = skb;

	msg = check_ptp_event(skb->data);
	if (!msg)
		return;
	port = msg->hdr.reserved2;
	if (!port)
		port = (1 << MAX_PTP_PORT) - 1;
	cnt = 0;
	if (SYNC_MSG == msg->hdr.messageType)
		tx = ptp->tx_sync;
	else if (PDELAY_RESP_MSG == msg->hdr.messageType)
		tx = ptp->tx_resp;
	else
		tx = ptp->tx_dreq;
	for (p = 0; p < MAX_PTP_PORT; p++, tx++) {
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
		if ((ptp->rx_en & 1) && (ptp->rx_en & (1 << 8))) {
			ptp->tx_en &= ~(1 << 8);
			ptp->rx_en &= ~(1 << 8);
		}
		ptp->rx_en &= ~1;
		break;
	case HWTSTAMP_FILTER_ALL:
#if 0
		ptp->rx_en |= 1;
		break;
#endif
	default:
		if (!(ptp->rx_en & 1) && (ptp->tx_en & 1)) {
			ptp->tx_en |= (1 << 8);
			ptp->rx_en |= (1 << 8);
		}
		ptp->rx_en |= 1;
		break;
	}

	return copy_to_user(ifr->ifr_data, &config, sizeof(config)) ?
		-EFAULT : 0;
}

#ifdef CONFIG_KSZ_STP_
static int check_ptp_bcast_msg(u8 *data, u8 port, u16 tx_ports)
{
	u8 dst;
	struct ptp_msg *msg;

	msg = check_ptp_msg(data, NULL);
	if (msg) {
		dst = msg->hdr.reserved2;
		if (3 == dst || 0 == dst)
			return dst;
		--dst;
		if (dst + 1 != port && (tx_ports & (1 << dst)))
			return 2;
		else
			return 1;
	}
	return 0;
}  /* check_ptp_bcast_msg */
#endif

static int ptp_drop_pkt(struct ptp_info *ptp, struct sk_buff *skb, u32 vlan_id,
	int *tag, int *ptp_tag)
{
	ptp->rx_msg_parsed = false;
	ptp->rx_msg = NULL;
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
	if ((ptp->overrides & PTP_PORT_FORWARD) || (ptp->rx_en & 1)) {
		struct ptp_msg *msg = check_ptp_msg(skb->data, NULL);

		ptp->rx_msg_parsed = true;
		ptp->rx_msg = msg;
		if (msg) {
			/* Indicate this is a PTP message. */
			*ptp_tag = msg->hdr.reserved2;

			/*
			 * Tag is already updated to reflect VLAN forwarding if
			 * tail tagging is used.  This is a case of it not
			 * being used.
			 */
			if (!*tag) {
				*tag = *ptp_tag;
				if (!(vlan_id & (1 << *tag)))
					*tag = 0;
			}
			if (ptp->rx_en & 1)
				ptp->ops->get_rx_tstamp(ptp, skb);
		}
	}
	return false;
}  /* ptp_drop_pkt */

static void proc_ptp_get_cfg(struct ptp_info *ptp, u8 *data)
{
	struct ptp_cfg_options *cmd = (struct ptp_cfg_options *) data;

	ptp->ops->acquire(ptp);
	ptp->mode = ptp->reg->read(ptp, ADDR_16, PTP_MSG_CONF1);
	ptp->cfg = ptp->reg->read(ptp, ADDR_16, PTP_MSG_CONF2);
	ptp->domain = ptp->reg->read(ptp, ADDR_16, PTP_DOMAIN_VERSION) &
		PTP_DOMAIN_MASK;
	ptp->ops->release(ptp);
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
	cmd->as = (ptp->mode & PTP_FORWARD_TO_PORT3) ? 1 : 0;
	cmd->unicast = (ptp->cfg & PTP_UNICAST_ENABLE) ? 1 : 0;
	cmd->alternate = (ptp->cfg & PTP_ALTERNATE_MASTER) ? 1 : 0;
	cmd->domain_check = (ptp->cfg & PTP_DOMAIN_CHECK) ? 1 : 0;
	cmd->udp_csum = (ptp->cfg & PTP_UDP_CHECKSUM) ? 1 : 0;
	cmd->delay_assoc = (ptp->cfg & PTP_DELAY_CHECK) ? 1 : 0;
	cmd->pdelay_assoc = (ptp->cfg & PTP_PDELAY_CHECK) ? 1 : 0;
	cmd->sync_assoc = (ptp->cfg & PTP_SYNC_CHECK) ? 1 : 0;
	cmd->drop_sync = (ptp->cfg & PTP_DROP_SYNC_DELAY_REQ) ? 1 : 0;
	cmd->priority = (ptp->cfg & PTP_ALL_HIGH_PRIORITY) ? 1 : 0;
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
				ptp->mode |= PTP_FORWARD_TO_PORT3;
			else
				ptp->mode &= ~PTP_FORWARD_TO_PORT3;
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
				ptp->cfg |= PTP_ALL_HIGH_PRIORITY;
			else
				ptp->cfg &= ~PTP_ALL_HIGH_PRIORITY;
		}
	}
	ptp->ops->acquire(ptp);
	if (mode != ptp->mode) {
		u16 ts_intr = ptp->ts_intr;

		if (ptp->mode & PTP_1STEP)
			ptp->ts_intr &= ~(TS_PORT2_INT_SYNC |
				TS_PORT1_INT_SYNC);
		else
			ptp->ts_intr |= (TS_PORT2_INT_SYNC |
				TS_PORT1_INT_SYNC);
		dbg_msg("mode: %x %x\n", mode, ptp->mode);
		mode = ptp->mode;
		if (ptp->overrides & PTP_VERIFY_TIMESTAMP)
			mode |= PTP_1STEP;
		ptp->reg->write(ptp, ADDR_16, PTP_MSG_CONF1, mode);
		ptp->def_mode = ptp->mode;
		if (ts_intr != ptp->ts_intr)
			ptp->reg->write(ptp, ADDR_16, TS_INT_ENABLE,
				ptp->ts_intr);
	}
	if (cfg != ptp->cfg) {
		dbg_msg("cfg: %x %x\n", cfg, ptp->cfg);
		ptp->reg->write(ptp, ADDR_16, PTP_MSG_CONF2, ptp->cfg);
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
		event = TS_DETECT_FALL;
	else if (1 == cmd->event)
		event = TS_DETECT_RISE;
	else {
		event = TS_DETECT_RISE | TS_DETECT_FALL;
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
	u16 status;
	int err = 0;

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
		ptp->ops->acquire(ptp);

		/* See whether previous operation is completed. */
		active = ptp->reg->read(ptp, ADDR_16, TRIG_ACTIVE);
		if (active & tso_bit) {
			status = ptp->reg->read(ptp, ADDR_16, TRIG_ERROR);
			if (!(status & tso_bit)) {
				ptp->ops->release(ptp);
				return DEV_IOC_UNIT_USED;
			}
			dbg_msg("trig err: %d\n", tso);
		}
		if (!(active & tso_bit)) {
			status = ptp->reg->read(ptp, ADDR_16, TRIG_DONE);
			if (!(status & tso_bit)) {
				/* Reset the unit. */
				ptp->cascade_tx |= tso_bit;
				dbg_msg(" !? trig done: %d\n", tso);
			}
		}
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
		status = ptp->reg->read(ptp, ADDR_16, TRIG_ERROR);
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
	u16 status;

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
	status = ptp->reg->read(ptp, ADDR_16, GPIO_MONITOR);

	/* Current level is high. */
	if (status & (1 << gpo)) {

		/* Set unit to hold the level high. */
		ptp->reg->tx_event(ptp, tso, gpo, TRIG_POS_EDGE, 0, 0, 1, 0, 1,
			0, PTP_CMD_INTR_OPER, 1, 0);

		/* Release the signal from the previous last unit. */
		ptp_gpo_reset(ptp, ptp->outputs[i].gpo, (1 << i));
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
		cmd->sec = cmd->nsec = 0;
		adj_clock(&ptp->adj_clk);
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

	if (port >= MAX_PTP_PORT)
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

	if (port >= MAX_PTP_PORT)
		return DEV_IOC_INVALID_CMD;
	ptp->ops->acquire(ptp);
	set_ptp_ingress(ptp, port, delay->rx_latency);
	set_ptp_egress(ptp, port, delay->tx_latency);
	set_ptp_asym(ptp, port, delay->asym_delay);
	ptp->rx_latency[port] = delay->rx_latency;
	ptp->tx_latency[port] = delay->tx_latency;
	ptp->asym_delay[port] = delay->asym_delay;
	ptp->ops->release(ptp);
	dbg_msg("set delay: %d = %d %d %d\n", port,
		ptp->rx_latency[port],
		ptp->tx_latency[port],
		ptp->asym_delay[port]);
	return 0;
}  /* proc_ptp_set_delay */

static int proc_ptp_get_peer_delay(struct ptp_info *ptp, int port, u8 *data)
{
	struct ptp_delay_values *delay = (struct ptp_delay_values *) data;

	if (port >= MAX_PTP_PORT)
		return DEV_IOC_INVALID_CMD;
	ptp->ops->acquire(ptp);
	delay->rx_latency = 0;
	delay->tx_latency = 0;
	delay->asym_delay = 0;
	delay->reserved = get_ptp_link(ptp, port);
	ptp->ops->release(ptp);
	return 0;
}  /* proc_ptp_get_peer_delay */

static int proc_ptp_set_peer_delay(struct ptp_info *ptp, int port, u8 *data)
{
	struct ptp_delay_values *delay = (struct ptp_delay_values *) data;

	if (port >= MAX_PTP_PORT)
		return DEV_IOC_INVALID_CMD;
	ptp->ops->acquire(ptp);
	set_ptp_link(ptp, port, delay->reserved);
	ptp->peer_delay[port] = delay->reserved;
	ptp->ops->release(ptp);
	dbg_msg("set delay: %d = %d\n", port,
		ptp->peer_delay[port]);
	return 0;
}  /* proc_ptp_set_peer_delay */

static void ptp_tx_done(struct ptp_info *ptp, int tso)
{
	int first;
	int last;
	int prev;
	u32 reg;
	u16 data;

	reg = TRIGn_CONF_1(tso);
	data = ptp->reg->read(ptp, ADDR_16, reg);
	if (data & TRIG_CASCADE_EN) {
		last = tso;
		do {
			--tso;
			reg = TRIGn_CONF_1(tso);
			data = ptp->reg->read(ptp, ADDR_16, reg);
			prev = (data & TRIG_CASCADE_UPS_MASK) >> 10;
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
		}
#ifdef PTP_SPI
		else if (diff > 2 * ptp->delay_ticks)
			dbg_msg("  ready? %x=%04x: %d, %lu\n",
				msg, seqid, port, diff);
#endif
	}
	if (!tx->ts.timestamp && ptp->linked[port] && data) {
		int rc = wait_event_interruptible_timeout(ptp->wait_ts,
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
#ifndef PTP_SPI
		if (ptp->linked[port])
			dbg_msg("  missed %x=%04x: %d, %lu\n",
				msg, seqid, port, jiffies - tx->req_time);
#endif
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

		if (opt->port >= MAX_PTP_PORT)
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
		opt->sec = tx->ts.r.sec;
		opt->nsec = tx->ts.r.nsec;
		tx->ts.timestamp = 0;
		tx->req_time = 0;
	}
	return 0;
}  /* proc_ptp_get_timestamp */

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

		if (db->index <= 3) {
			struct ptp_tx_ts *tx;
			int port = db->index >> 1;

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

			if ((cfg->enable & 0x10) && port < MAX_PTP_PORT &&
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
#ifdef PTP_SPI
	wait_for_completion(&work->done);
#endif
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
	int result = DEV_IOC_OK;

	parent->output = parent->option;
	switch (parent->cmd) {
	case DEV_CMD_INFO:
		switch (parent->subcmd) {
		case DEV_INFO_INIT:
			ptp_init_state(ptp);
			parent->output = ptp->drift_set;
			break;
		case DEV_INFO_EXIT:
			ptp_exit_state(ptp);
			break;
		case DEV_INFO_RESET:
			reg = parent->option;
			ptp->ops->acquire(ptp);
			ptp->reg->write(ptp, ADDR_16, REG_RESET_CTRL,
				1 << reg);
			udelay(1);
			ptp->reg->write(ptp, ADDR_16, REG_RESET_CTRL, 0);
			ptp->ops->release(ptp);
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
			ptp->ops->acquire(ptp);
			ptp->reg->write(ptp, ADDR_16, reg & 0xffff,
				reg >> 16);
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
			if (parent->option)
				result = proc_dev_poll_event(info, data);

			/* Not actually used. */
			else
				result = proc_dev_get_event(info, data);
			break;
		case DEV_PTP_TOUT:
			break;
		case DEV_PTP_CLK:
			proc_ptp_get_clk(ptp, data);
			break;
		case DEV_PTP_DELAY:
			port = parent->option;
			result = proc_ptp_get_delay(ptp, port, data);
			break;
		case DEV_PTP_REG:
			reg = parent->option;
			ptp->ops->acquire(ptp);
			parent->output = ptp->reg->read(ptp, ADDR_16, reg);
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
#ifdef PTP_SPI
	init_completion(&work->done);
#endif
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

static u32 _get_clk_cnt(void)
{
	return 0;
}

#ifdef PTP_SPI
#define ACCESS_VAL			1000
#else
#define ACCESS_VAL			100
#endif

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

static void proc_ptp_intr(struct ptp_info *ptp)
{
	struct ptp_event *event;
	u16 done;
	u16 error;
	u16 status;
	u16 tsi_bit;
	u8 data[24];
	int i;
	int tsi;
	int last;
	union ktime cur_ktime;
	struct timespec ts;

	cur_ktime = ktime_get_real();
	ts = ktime_to_timespec(cur_ktime);

proc_chk_trig_intr:
	status = ptp->reg->read(ptp, ADDR_16, TRIG_INT_STATUS);
	if (!status)
		goto proc_chk_ts_intr;

	ptp->reg->write(ptp, ADDR_16, TRIG_INT_STATUS, status);
	done = ptp->reg->read(ptp, ADDR_16, TRIG_DONE);
	error = ptp->reg->read(ptp, ADDR_16, TRIG_ERROR);
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
	status = ptp->reg->read(ptp, ADDR_16, TS_INT_STATUS);
	if (!status)
		goto proc_ptp_intr_done;

	ptp->reg->write(ptp, ADDR_16, TS_INT_STATUS, status);
	for (i = 0; i < MAX_TIMESTAMP_UNIT; i++) {
		tsi_bit = 1 << i;
		if (!(status & tsi_bit))
			continue;
		ptp->reg->read_event(ptp, i);
		event = &ptp->events[i];
		if (event->timeout && (event->num < event->max ||
				event->last)) {
			unsigned long expired;

			expired = jiffies + event->timeout;
			event->expired = expired;
			if (event->last) {
				tsi = i + 1;
				do {
					if (tsi >= MAX_TIMESTAMP_UNIT)
						tsi = 0;
					ptp->events[tsi].expired = expired;
					++tsi;
				} while (tsi != event->last);
			}
		} else if (event->last && i != event->first) {
			tsi = i - 1;
			if (tsi < 0)
				tsi = MAX_TIMESTAMP_UNIT - 1;
			if (ptp->tsi_used & (1 << tsi))
				ptp->events[tsi].expired = jiffies;
		}
		if (i == ptp->pps_tsi) {
			struct ptp_utime sys_time;

			ptp->cur_time.sec = event->t[0].sec;
			ptp->cur_time.nsec = event->t[0].nsec;
			ptp->update_sec_jiffies = 0;
			sys_time.sec = ts.tv_sec;
			sys_time.nsec = ts.tv_nsec;
			calc_udiff(&ptp->cur_time, &sys_time, &ptp->time_diff);
			if (!ptp->intr_sec)
				ptp->intr_sec = ptp->cur_time.sec;
			if ((ptp->overrides & PTP_CHECK_SYS_TIME) ||
					!ptp->first_drift)
				check_sys_time(ptp, jiffies, cur_ktime);
#ifdef CONFIG_PTP_1588_CLOCK
			if (ptp->clock_events & (1 << 0))
				ptp_event_trigger(ptp->clock_info, 0,
					ptp->cur_time.sec, ptp->cur_time.nsec);
			if (ptp->clock_events & (1 << 31))
				ptp_event_pps(ptp->clock_info);
#endif
		} else if (i == ptp->gps_tsi) {
			ptp->gps_time.sec = event->t[0].sec;
			ptp->gps_time.nsec = event->t[0].nsec;
			++ptp->gps_seqid;
			ptp->gps_resp_time = jiffies;
		}
	}
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
						jiffies >= event->expired) {
					ptp->reg->read_event(ptp, i);
					stop = true;
				}
			}
		}
		if ((ptp->ts_status & ptp->ts_intr) & tsi_bit) {
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
				ptp->reg->rx_restart(ptp, tsi_bit);
				stop = false;
			}
		}
		if (stop) {
			ptp->reg->rx_off(ptp, i);
			ptp->tsi_intr &= ~tsi_bit;
			ptp->tsi_used &= ~tsi_bit;
			ptp->tsi_dev[i] = NULL;
			tsi = i;
			ptp->events[i].timeout = 0;
			if (i + 1 == event->last) {
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
	ptp->ts_status = 0;
	if (!(status & 0xF000))
		goto proc_chk_trig_intr;

	if (get_tx_time(ptp, status & 0xF000))
		wake_up_interruptible(&ptp->wait_ts);
	goto proc_chk_trig_intr;

proc_ptp_intr_done:
	return;
}  /* proc_ptp_intr */

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
		if (port < 1 || port > MAX_PTP_PORT)
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
			ptp->ops->acquire(ptp);
			ptp->reg->get_time(ptp, &ts.t);
			ptp->ops->release(ptp);
		}
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
	int port;
	int req_size;
	int subcmd;
	int output;
	u8 data[PARAM_DATA_SIZE];
	struct ptp_dev_info *dev;
	int err = 0;
	int result = 0;

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
			req_size = SIZEOF_ksz_request + 4;
			if (len >= 4) {
				data[0] = 'M';
				data[1] = 'i';
				data[2] = 'c';
				data[3] = 'r';
				data[4] = ptp->version;
				data[5] = ptp->ports;
				if (!access_ok(VERIFY_WRITE, req->param.data,
						6) ||
						copy_to_user(req->param.data,
						data, 6)) {
					err = -EFAULT;
					goto dev_ioctl_done;
				}
				result = proc_ptp_hw_access(ptp,
					maincmd, subcmd, 0,
					data, 6, info, &output,
					true);
				__put_user(ptp->drift_set, &req->output);
			} else
				result = DEV_IOC_INVALID_LEN;
			break;
		case DEV_INFO_EXIT:
			result = proc_ptp_hw_access(ptp,
				maincmd, subcmd, 0,
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
				maincmd, subcmd, 0,
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
				maincmd, subcmd, 0,
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
			__get_user(port, &req->output);
			result = proc_ptp_hw_access(ptp,
				maincmd, subcmd, output,
				data, len, info, &output,
				false);
			break;
		case DEV_PTP_REG:
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
			memcpy(&ptp->clockIdentity, data,
				sizeof(struct ptp_clock_identity));
			break;
		case DEV_PTP_PEER_DELAY:
			if (chk_ioctl_size(len,
					sizeof(struct ptp_delay_values),
					SIZEOF_ksz_request,
					&req_size, &result, &req->param, data))
				goto dev_ioctl_resp;
			__get_user(port, &req->output);
			result = proc_ptp_hw_access(ptp,
				maincmd, subcmd, output,
				data, len, info, &output,
				false);
			break;
		case DEV_PTP_UTC_OFFSET:
			ptp->utc_offset = output;
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
			if (output)
				result = proc_ptp_hw_access(ptp,
					maincmd, subcmd, output,
					data, len, info, &output,
					false);
			else
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
			result = proc_ptp_hw_access(ptp,
				maincmd, subcmd, 0,
				data, len, info, &output,
				true);
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
			__get_user(port, &req->output);
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
			result = proc_ptp_hw_access(ptp,
				maincmd, subcmd, output,
				data, len, info, &output,
				true);
			__put_user(output, &req->output);
			break;
		case DEV_PTP_IDENTITY:
			if (!access_ok(VERIFY_WRITE, req->param.data,
					sizeof(struct ptp_clock_identity)) ||
					copy_to_user(req->param.data,
					&ptp->clockIdentity,
					sizeof(struct ptp_clock_identity))) {
				err = -EFAULT;
				goto dev_ioctl_done;
			}
			break;
		case DEV_PTP_PEER_DELAY:
			if (chk_ioctl_size(len,
					sizeof(struct ptp_delay_values),
					SIZEOF_ksz_request,
					&req_size, &result, NULL, NULL))
				goto dev_ioctl_resp;
			__get_user(port, &req->output);
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

	ptp->features |= PTP_ADJ_HACK;
	ptp->ops->acquire(ptp);
	sw->cached.ptp_clk_ctrl = ptp->reg->read(ptp, ADDR_16, PTP_CLK_CTRL);
	ptp->reg->get_time(ptp, &cur);
	ptp->reg->adjust_time(ptp, true, 10, 0, true);
	ptp->reg->get_time(ptp, &now);
	if (now.sec - cur.sec >= 10) {
		ptp->features &= ~PTP_ADJ_HACK;
		ptp->features |= PTP_ADJ_SEC;
		ptp->features |= PTP_PDELAY_HACK;
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
		ptp->reg->write(ptp, ADDR_16, PTP_CLK_CTRL,
			sw->cached.ptp_clk_ctrl);
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
			ptp->reg->write(ptp, ADDR_16, PTP_CLK_CTRL, data);

			ptp->reg->write(ptp, ADDR_16, PTP_CLK_CTRL,
				data | PTP_CLK_ADJ_ENABLE);
			ptp->reg->set_time(ptp, &cur);
			ptp->reg->adjust_time(ptp, false, 0, 800000000, true);
			ptp->reg->get_time(ptp, &now);
			dbg_msg("ok %x:%u\n", now.sec, now.nsec);
		}
		sw->cached.ptp_clk_ctrl = data;
		ptp->reg->write(ptp, ADDR_16, PTP_CLK_CTRL, data);
	}
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
	ptp->delay_ticks = 1;
#ifdef PTP_SPI
	ptp->delay_ticks = 2;
	ptp->access = create_singlethread_workqueue("ptp_access");
#endif
	init_ptp_work(ptp);
	mutex_init(&ptp->lock);
	init_waitqueue_head(&ptp->wait_ts);
	init_waitqueue_head(&ptp->wait_intr);
	INIT_WORK(&ptp->adj_clk, adj_clock);
	INIT_DELAYED_WORK(&ptp->check_pps, ptp_check_pps);
	INIT_DELAYED_WORK(&ptp->update_sec, ptp_update_sec);
	ptp_set_identity(ptp, mac_addr);

	ptp->ports = MAX_PTP_PORT;
	ptp_check(ptp);
	if (!ptp->get_clk_cnt)
		ptp->get_clk_cnt = _get_clk_cnt;
	if (!ptp->test_access_time)
		ptp->test_access_time = _test_access_time;
	if (ptp->test_access_time)
		ptp->test_access_time(ptp);

	ptp->mode = PTP_ENABLE |
		PTP_IPV4_UDP_ENABLE |
		PTP_1STEP;
	ptp->mode |= PTP_IPV6_UDP_ENABLE;
	ptp->mode |= PTP_ETH_ENABLE;
	ptp->cfg = 0;
	ptp->cfg |= PTP_DOMAIN_CHECK;
	ptp->cfg |= PTP_PDELAY_CHECK | PTP_DELAY_CHECK;
	ptp->cfg |= PTP_UNICAST_ENABLE;
	if (ptp->version >= 1) {
		ptp->cfg |= PTP_UDP_CHECKSUM;
		ptp->cfg |= PTP_SYNC_CHECK;
	}
	ptp->def_mode = ptp->mode;
	ptp->def_cfg = ptp->cfg;
	ptp->trig_intr = 0xfff;
	ptp->ts_intr = (TS_PORT2_INT_XDELAY | TS_PORT1_INT_XDELAY);

	ptp->gps_tsi = MAX_TIMESTAMP_UNIT;
	ptp->gps_gpi = DEFAULT_GPS_GPI;
	ptp->pps_gpo = DEFAULT_PPS_GPO;
	ptp->pps_tsi = DEFAULT_PPS_TSI;
	ptp->pps_tso = DEFAULT_PPS_TSO;
	ptp->mhz_gpo = DEFAULT_MHZ_GPO;
	ptp->mhz_tso = DEFAULT_MHZ_TSO;

	for (i = 0; i < MAX_TIMESTAMP_UNIT - 1; i++)
		ptp->events[i].max = 2;
	ptp->events[i].max = MAX_TIMESTAMP_EVENT_UNIT;

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
	ptp->reg->write(ptp, ADDR_16, TRIG_INT_ENABLE, 0);
	ptp->reg->write(ptp, ADDR_16, TS_INT_ENABLE, 0);
	ptp->ops->release(ptp);

#ifdef PTP_SPI
	if (ptp->access) {
		destroy_workqueue(ptp->access);
		ptp->access = NULL;
	}
#endif
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
		len += sprintf(buf + len, "\t%08x = pdelay hack\n",
			PTP_PDELAY_HACK);
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
		ptp->overrides = num;
		break;
	case PROC_SET_PTP_VID:
		ptp->vid = num;
		break;
	}
}

static struct ptp_reg_ops ptp_reg_ops = {
	.read			= ptp_read,
	.write			= ptp_write,

	.get_time		= get_ptp_time,
	.set_time		= set_ptp_time,
	.adjust_time		= adjust_ptp_time,
	.adjust_sync_time	= adjust_sync_time,

	.rx_off			= ptp_rx_off,
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
	.update_msg		= update_ptp_msg,
	.get_rx_tstamp		= get_rx_tstamp,
	.get_tx_tstamp		= get_tx_tstamp,
	.hwtstamp_ioctl		= ptp_hwtstamp_ioctl,
	.ixxat_ioctl		= ixxat_ptp_ioctl,
	.dev_req		= ptp_dev_req,
	.proc_intr		= proc_ptp_intr,

	.sysfs_read		= sysfs_ptp_read,
	.sysfs_write		= sysfs_ptp_write,

	.drop_pkt		= ptp_drop_pkt,
};

