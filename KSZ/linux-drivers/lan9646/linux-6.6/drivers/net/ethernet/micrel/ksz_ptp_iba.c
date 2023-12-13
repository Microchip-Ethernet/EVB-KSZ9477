/**
 * Microchip PTP common code in IBA format
 *
 * Copyright (c) 2015-2022 Microchip Technology Inc.
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


static void *get_time_pre(struct ksz_iba_info *info, void *in, void *obj)
{
	u32 *data = in;

	iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_16, REG_PTP_CLK_CTRL, *data);
	iba_cmd_set(info, IBA_CMD_READ, IBA_CMD_32, REG_PTP_RTC_SEC, 0);
	iba_cmd(info, IBA_CMD_READ, IBA_CMD_32, REG_PTP_RTC_NANOSEC);
	iba_cmd(info, IBA_CMD_READ, IBA_CMD_16, REG_PTP_RTC_SUB_NANOSEC__2);
	return info->fptr;
}  /* get_time_pre */

static int get_time_post(struct ksz_iba_info *info, void *out, void *obj)
{
	struct ptp_utime *t = obj;
	int i = 0;
	u16 subnsec = 0;

	while (info->regs[i].cmd != (u32) -1) {
		if (IBA_CMD_READ == (info->regs[i].cmd >> IBA_CMD_S)) {
			u32 reg = (info->regs[i].cmd & IBA_CMD_ADDR_M);
			u32 size = (info->regs[i].cmd & IBA_CMD_32);

			switch (reg) {
			case REG_PTP_RTC_SEC:
				t->sec = info->ops->get_val(size,
					info->regs[i].data[0]);
				break;
			case REG_PTP_RTC_NANOSEC:
				t->nsec = info->ops->get_val(size,
					info->regs[i].data[0]);
				break;
			case REG_PTP_RTC_SUB_NANOSEC__2:
				subnsec = (u16) info->ops->get_val(size,
					info->regs[i].data[0]);
				break;
			}
		}
		i++;
	}

	add_nsec(t, subnsec * 8);
	return i;
}  /* get_time_post */

static void get_ptp_time_iba(struct ptp_info *ptp, struct ptp_utime *t)
{
	struct ksz_sw *sw = ptp->parent;
	struct ksz_iba_info *info = &sw->info->iba;
	u32 data[3];

	data[0] = sw->cached.ptp_clk_ctrl;
	data[0] |= PTP_READ_TIME;
	info->ops->req(info, data, NULL, t, get_time_pre, get_time_post);
}  /* get_ptp_time_iba */

static void *set_time_pre(struct ksz_iba_info *info, void *in, void *obj)
{
	u32 *data = in;
	struct ptp_utime *t = obj;

	iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_16,
		REG_PTP_RTC_SUB_NANOSEC__2, 0);
	iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_32, REG_PTP_RTC_NANOSEC,
		t->nsec);
	iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_32, REG_PTP_RTC_SEC,
		t->sec);
	iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_16, REG_PTP_CLK_CTRL,
		data[0]);
	return info->fptr;
}  /* set_time_pre */

static void set_ptp_time_iba(struct ptp_info *ptp, struct ptp_utime *t)
{
	struct ksz_sw *sw = ptp->parent;
	struct ksz_iba_info *info = &sw->info->iba;
	u32 data[3];

	data[0] = sw->cached.ptp_clk_ctrl;
	data[0] |= PTP_LOAD_TIME;
	info->ops->req(info, data, NULL, t, set_time_pre, NULL);
}  /* set_ptp_time_iba */

static void *adjust_time_pre(struct ksz_iba_info *info, void *in,
	void *obj)
{
	u32 *data = in;
	u32 nsec = data[4];
	u32 val = nsec;

	iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_32, REG_PTP_RTC_SEC,
		data[3]);
	do {
		if (nsec > NANOSEC_IN_SEC - 1)
			nsec = NANOSEC_IN_SEC - 1;
		iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_32,
			REG_PTP_RTC_NANOSEC, nsec);
		iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_16, REG_PTP_CLK_CTRL,
			data[2]);
		val -= nsec;
		nsec = val;
	} while (val);
	if (data[5]) {
		iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_16, REG_PTP_CLK_CTRL,
			data[5]);
	}
	return info->fptr;
}  /* adjust_time_pre */

static void adjust_ptp_time_iba(struct ptp_info *ptp, int add, u32 sec,
	u32 nsec, int adj_hack)
{
	struct ksz_sw *sw = ptp->parent;
	struct ksz_iba_info *info = &sw->info->iba;
	u32 data[6];
	u16 ctrl;
	u16 adj = 0;

	data[2] = sw->cached.ptp_clk_ctrl;
	ctrl = data[2];
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
	data[2] = ctrl;
	data[3] = sec;
	data[4] = nsec;
	data[5] = 0;
	if (adj_hack && (adj & PTP_CLK_ADJ_ENABLE))
		data[5] = adj;
	info->ops->req(info, data, NULL, NULL, adjust_time_pre, NULL);
#ifdef NO_PPS_DETECT
	if (add && (sec || nsec >= 1000))
		ptp->clk_add = 1;
#endif
}  /* adjust_ptp_time_iba */

static void *adjust_sync_time_pre(struct ksz_iba_info *info, void *in,
	void *obj)
{
	u32 *data = in;

	iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_32, REG_PTP_RATE_DURATION,
		data[0]);
	iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_32, REG_PTP_SUBNANOSEC_RATE,
		data[1]);
	return info->fptr;
}

static void adjust_sync_time_iba(struct ptp_info *ptp, int diff, u32 interval,
	u32 duration)
{
	struct ksz_sw *sw = ptp->parent;
	struct ksz_iba_info *info = &sw->info->iba;
	u32 data[2];
	u32 adjust;

	adjust = clk_adjust_val(diff, interval);
	adjust |= PTP_TMP_RATE_ENABLE;
	data[0] = duration;
	data[1] = adjust;
	info->ops->req(info, data, NULL, NULL, adjust_sync_time_pre, NULL);
}  /* adjust_sync_time_iba */

static void *ptp_unit_index_pre(struct ksz_iba_info *info, void *in, void *obj)
{
	u32 *data = in;
	int shift = data[0];
	u8 unit = (u8) data[1];
	struct ptp_info *ptp = obj;

	iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_32, REG_PTP_UNIT_INDEX__4,
		ptp_unit_index(ptp, shift, unit));
	return info->fptr;
}  /* ptp_unit_index_pre */

static void *rx_reset_pre(struct ksz_iba_info *info, void *in, void *obj)
{
	iba_cmd_set(info, IBA_CMD_READ, IBA_CMD_32, REG_PTP_CTRL_STAT__4, 0);
	iba_cmd_set(info, IBA_CMD_WRITE_1, IBA_CMD_32, REG_PTP_CTRL_STAT__4,
		TS_RESET);
	iba_cmd_set(info, IBA_CMD_READ, IBA_CMD_32, REG_PTP_CTRL_STAT__4, 0);
	iba_cmd_set(info, IBA_CMD_WRITE_0, IBA_CMD_32, REG_PTP_CTRL_STAT__4,
		TS_ENABLE | TS_RESET);
	return info->fptr;
}  /* rx_reset_pre */

static void ptp_rx_reset_iba(struct ptp_info *ptp, u8 tsi, u32 *ctrl_ptr)
{
	struct ksz_sw *sw = ptp->parent;
	struct ksz_iba_info *info = &sw->info->iba;
	int rc;
	u32 buf[8];
	void *func[3];
	void *data_in[2];
	u32 *data = buf;
	int i = 0;

	if (!ctrl_ptr) {
		data_in[i] = data;
		data[0] = PTP_TSI_INDEX_S;
		data[1] = tsi;
		data += 2;
		func[i++] = ptp_unit_index_pre;
	}

	data_in[i] = data;
	func[i++] = rx_reset_pre;

	func[i] = NULL;
	iba_assert(info, __func__, i, sizeof(func), buf, data, sizeof(buf));
	rc = info->ops->reqs(info, data_in, NULL, ptp, func, NULL);
}  /* ptp_rx_reset_iba */

static void *rx_off_pre(struct ksz_iba_info *info, void *in, void *obj)
{
	iba_cmd_set(info, IBA_CMD_READ, IBA_CMD_32, REG_PTP_CTRL_STAT__4, 0);
	iba_cmd_set(info, IBA_CMD_WRITE_0, IBA_CMD_32, REG_PTP_CTRL_STAT__4,
		TS_INT_ENABLE | TS_ENABLE);
	return info->fptr;
}  /* rx_off_pre */

static void ptp_rx_off_iba(struct ptp_info *ptp, u8 tsi)
{
	struct ksz_sw *sw = ptp->parent;
	struct ksz_iba_info *info = &sw->info->iba;
	u16 tsi_bit = (1 << tsi);
	u32 ts_intr = 0;
	int rc;
	u32 buf[13];
	void *func[6];
	void *data_in[5];
	u32 *data = buf;
	u32 *data_out;
	int i = 0;

	data_in[i] = data;
	data[0] = PTP_TSI_INDEX_S;
	data[1] = tsi;
	data += 2;
	func[i++] = ptp_unit_index_pre;

	/* Disable previous timestamp interrupt. */
	if (ptp->ts_intr & tsi_bit) {
		ptp->ts_intr &= ~tsi_bit;
		ts_intr = tsi_bit;
	}

	data_in[i] = data;
	func[i++] = rx_off_pre;

	/*
	 * Need to turn off cascade mode if it is used previously; otherwise,
	 * event counter keeps increasing.
	 */
	if (ptp->cascade_rx & tsi_bit) {
		data_in[i] = data;
		func[i++] = rx_reset_pre;

		data_in[i] = data;
		data[0] = IBA_CMD_32;
		data[1] = REG_TS_CTRL_STAT__4;
		data[2] = 0;
		data += 3;
		func[i++] = info->ops->w_pre;
		ptp->cascade_rx &= ~tsi_bit;
	}
	if (ts_intr) {
		data_in[i] = data;
		data[0] = IBA_CMD_32;
		data[1] = REG_PTP_INT_STATUS__4;
		data[2] = ts_intr;
		data += 3;
		func[i++] = info->ops->w_pre;
	}

	data_out = data;
	data = iba_prepare(info, REG_PTP_CTRL_STAT__4, data);
	data = iba_prepare(info, -1, data);

	func[i] = NULL;
	iba_assert(info, __func__, i, sizeof(func), buf, data, sizeof(buf));
	rc = info->ops->reqs(info, data_in, data_out, ptp, func,
		info->ops->r_post);
}  /* ptp_rx_off_iba */

static inline void rx_intr_iba(struct ptp_info *ptp, u16 tsi_bit, u32 *ctrl)
{
	ptp->ts_intr |= tsi_bit;
	*ctrl |= TS_INT_ENABLE;
}  /* rx_intr_iba */

static void *rx_on_pre(struct ksz_iba_info *info, void *in, void *obj)
{
	u32 *data = in;
	u8 tsi = (u8) data[0];
	int intr = data[1];
	struct ptp_info *ptp = obj;
	u32 ctrl = 0;

	iba_cmd_set(info, IBA_CMD_READ, IBA_CMD_32, REG_PTP_CTRL_STAT__4, 0);

	/* Enable timestamp interrupt. */
	if (intr)
		ptp_rx_intr(ptp, (1 << tsi), &ctrl);

	ctrl |= TS_ENABLE;
	iba_cmd_set(info, IBA_CMD_WRITE_1, IBA_CMD_32, REG_PTP_CTRL_STAT__4,
		ctrl);
	return info->fptr;
}  /* rx_on_pre */

static void *rx_restart_pre(struct ksz_iba_info *info, void *in, void *obj)
{
	iba_cmd_set(info, IBA_CMD_READ, IBA_CMD_32, REG_PTP_CTRL_STAT__4, 0);
	iba_cmd_set(info, IBA_CMD_WRITE_0, IBA_CMD_32, REG_PTP_CTRL_STAT__4,
		TS_ENABLE);
	iba_cmd_set(info, IBA_CMD_READ, IBA_CMD_32, REG_PTP_CTRL_STAT__4, 0);
	iba_cmd_set(info, IBA_CMD_WRITE_1, IBA_CMD_32, REG_PTP_CTRL_STAT__4,
		TS_ENABLE);
	return info->fptr;
}  /* rx_restart_pre */

static void ptp_rx_restart_iba(struct ptp_info *ptp, u8 tsi)
{
	struct ksz_sw *sw = ptp->parent;
	struct ksz_iba_info *info = &sw->info->iba;
	int rc;
	void *func[3];
	void *data_in[2];
	u32 buf[8];
	u32 *data = buf;
	int i = 0;

	data_in[i] = data;
	data[0] = PTP_TSI_INDEX_S;
	data[1] = tsi;
	data += 2;
	func[i++] = ptp_unit_index_pre;

	data_in[i] = data;
	func[i++] = rx_restart_pre;

	func[i] = NULL;
	iba_assert(info, __func__, i, sizeof(func), buf, data, sizeof(buf));
	rc = info->ops->reqs(info, data_in, NULL, ptp, func, NULL);
}  /* ptp_rx_restart_iba */

static void *rx_event_pre(struct ksz_iba_info *info, void *in, void *obj)
{
	u32 *data = in;
	u8 tsi = data[0];
	u8 gpi = data[1];
	u8 event = data[2];
	struct ptp_info *ptp = obj;
	u32 ctrl;

	iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_32, REG_PTP_UNIT_INDEX__4,
		ptp_unit_index(ptp, PTP_TSI_INDEX_S, tsi));

	/* Config pattern. */
	ctrl = ts_event_gpi(gpi, event);
	iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_32, REG_TS_CTRL_STAT__4,
		ctrl);
	return info->fptr;
}  /* rx_event_pre */

static void ptp_rx_event_iba(struct ptp_info *ptp, u8 tsi, u8 gpi, u8 event,
	int intr)
{
	struct ksz_sw *sw = ptp->parent;
	struct ksz_iba_info *info = &sw->info->iba;
	int rc;
	void *func[3];
	void *data_in[2];
	u32 buf[8];
	u32 *data = buf;
	int i = 0;

	data_in[i] = data;
	data[0] = tsi;
	data[1] = gpi;
	data[2] = event;
	data += 3;
	func[i++] = rx_event_pre;

	data_in[i] = data;
	data[0] = tsi;
	data[1] = intr;
	data += 2;
	func[i++] = rx_on_pre;

	func[i] = NULL;
	iba_assert(info, __func__, i, sizeof(func), buf, data, sizeof(buf));
	rc = info->ops->reqs(info, data_in, NULL, ptp, func, NULL);
}  /* ptp_rx_event_iba */

static void *rx_cascade_event_pre(struct ksz_iba_info *info, void *in,
	void *obj)
{
	u32 *data = in;
	u8 first = data[0];
	u8 total = data[1];
	u8 gpi = data[2];
	u8 event = data[3];
	int intr = data[4];
	struct ptp_info *ptp = obj;
	int last;
	int tsi;
	u32 ctrl;
	u32 tail;
	int i;
	int prev;

	last = (first + total - 1) % MAX_TIMESTAMP_UNIT;
	tsi = last;
	tail = TS_CASCADE_TAIL;
	for (i = 1; i < total; i++) {
		iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_32,
			REG_PTP_UNIT_INDEX__4,
			ptp_unit_index(ptp, PTP_TSI_INDEX_S, tsi));

		prev = tsi - 1;
		if (prev < 0)
			prev = MAX_TIMESTAMP_UNIT - 1;
		ctrl = ts_event_gpi(gpi, event);
		ctrl |= ts_cascade(prev);
		ctrl |= tail;
		ptp->cascade_rx |= (1 << tsi);
		iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_32,
			REG_TS_CTRL_STAT__4, ctrl);

		/* Enable timestamp interrupt. */
		if (intr) {
			ctrl = 0;
			ptp_rx_intr(ptp, (1 << tsi), &ctrl);
			iba_cmd_set(info, IBA_CMD_READ, IBA_CMD_32,
				REG_PTP_CTRL_STAT__4, 0);
			iba_cmd_set(info, IBA_CMD_WRITE_1, IBA_CMD_32,
				REG_PTP_CTRL_STAT__4, ctrl);
		}
		--tsi;
		if (tsi < 0)
			tsi = MAX_TIMESTAMP_UNIT - 1;
		tail = 0;
	}
	iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_32, REG_PTP_UNIT_INDEX__4,
		ptp_unit_index(ptp, PTP_TSI_INDEX_S, first));

	ctrl = ts_event_gpi(gpi, event);
	ctrl |= ts_cascade(last);
	ptp->cascade_rx |= (1 << first);
	iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_32, REG_TS_CTRL_STAT__4,
		ctrl);
	return info->fptr;
}  /* rx_cascade_event_pre */

static void ptp_rx_cascade_event_iba(struct ptp_info *ptp, u8 first, u8 total,
	u8 gpi, u8 event, int intr)
{
	struct ksz_sw *sw = ptp->parent;
	struct ksz_iba_info *info = &sw->info->iba;
	int rc;
	void *func[3];
	void *data_in[2];
	u32 buf[8];
	u32 *data = buf;
	int i = 0;

	data_in[i] = data;
	data[0] = first;
	data[1] = total;
	data[2] = gpi;
	data[3] = event;
	data[4] = intr;
	data += 5;
	func[i++] = rx_cascade_event_pre;

	data_in[i] = data;
	data[0] = first;
	data[1] = intr;
	data += 2;
	func[i++] = rx_on_pre;

	func[i] = NULL;
	iba_assert(info, __func__, i, sizeof(func), buf, data, sizeof(buf));
	rc = info->ops->reqs(info, data_in, NULL, ptp, func, NULL);
}  /* ptp_rx_cascade_event_iba */

static u32 ptp_get_event_cnt_iba(struct ptp_info *ptp, u8 tsi, void *ptr)
{
	struct ksz_iba_info *info = ptr;
	int rc;
	void *func[3];
	void *data_in[2];
	u32 buf[8];
	u32 *data = buf;
	u32 *data_out;
	int i = 0;

	data_in[i] = data;
	data[0] = PTP_TSI_INDEX_S;
	data[1] = tsi;
	data += 2;
	func[i++] = ptp_unit_index_pre;

	data_in[i] = data;
	data[0] = IBA_CMD_32;
	data[1] = REG_TS_CTRL_STAT__4;
	data += 3;
	func[i++] = info->ops->r_pre;

	data_out = data;
	data = iba_prepare(info, REG_TS_CTRL_STAT__4, data);
	data = iba_prepare(info, -1, data);

	func[i] = NULL;
	iba_assert(info, __func__, i, sizeof(func), buf, data, sizeof(buf));
	rc = info->ops->reqs(info, data_in, data_out, ptp, func,
		info->ops->r_post);
	return data_out[1];
}  /* ptp_get_event_cnt_iba */

static void ptp_get_events_iba(struct ptp_info *ptp, u32 reg_ns, size_t len,
	void *buf, void *ptr)
{
	struct ksz_iba_info *info = ptr;

	info->ops->burst(info, reg_ns, len, buf, 0,
		info->ops->get_pre, info->ops->get_post_le);
}  /* ptp_get_events_iba */

static void ptp_read_event_iba(struct ptp_info *ptp, u8 tsi)
{
	struct ksz_sw *sw = ptp->parent;
	struct ksz_iba_info *info = &sw->info->iba;

	ptp_read_event_func(ptp, tsi, info, ptp_get_event_cnt_iba,
		ptp_get_events_iba);
}  /* ptp_read_event_iba */

static void *tx_reset_pre(struct ksz_iba_info *info, void *in, void *obj)
{
	iba_cmd_set(info, IBA_CMD_READ, IBA_CMD_32, REG_PTP_CTRL_STAT__4, 0);
	iba_cmd_set(info, IBA_CMD_WRITE_1, IBA_CMD_32, REG_PTP_CTRL_STAT__4,
		TRIG_RESET);
	iba_cmd_set(info, IBA_CMD_READ, IBA_CMD_32, REG_PTP_CTRL_STAT__4, 0);
	iba_cmd_set(info, IBA_CMD_WRITE_0, IBA_CMD_32, REG_PTP_CTRL_STAT__4,
		TRIG_ENABLE | TRIG_RESET);
	return info->fptr;
}  /* tx_reset_pre */

static void *tx_off_pre(struct ksz_iba_info *info, void *in, void *obj)
{
	iba_cmd_set(info, IBA_CMD_READ, IBA_CMD_32, REG_PTP_CTRL_STAT__4, 0);
	iba_cmd_set(info, IBA_CMD_WRITE_0, IBA_CMD_32, REG_PTP_CTRL_STAT__4,
		TRIG_ENABLE);
	return info->fptr;
}  /* tx_off_pre */

static void *tx_init_pre(struct ksz_iba_info *info, void *in, void *obj)
{
	iba_cmd_set(info, IBA_CMD_READ, IBA_CMD_32, REG_TRIG_CTRL__4, 0);
	iba_cmd_set(info, IBA_CMD_WRITE_0, IBA_CMD_32, REG_TRIG_CTRL__4,
		TRIG_CASCADE_ENABLE | TRIG_CASCADE_TAIL);
	iba_cmd_set(info, IBA_CMD_READ, IBA_CMD_32, REG_TRIG_CTRL__4, 0);
	iba_cmd_set(info, IBA_CMD_WRITE_1, IBA_CMD_32, REG_TRIG_CTRL__4,
		trig_cascade(TRIG_CASCADE_UPS_M));
	return info->fptr;
}  /* tx_init_pre */

static void ptp_tx_off_iba(struct ptp_info *ptp, u8 tso)
{
	struct ksz_sw *sw = ptp->parent;
	struct ksz_iba_info *info = &sw->info->iba;
	u16 tso_bit = (1 << tso);
	int rc;
	u32 buf[8 + 8];
	void *func[5];
	void *data_in[4];
	u32 *data = buf;
	u32 *data_out;
	int i = 0;

	data_in[i] = data;
	data[0] = PTP_TOU_INDEX_S;
	data[1] = tso;
	data += 2;
	func[i++] = ptp_unit_index_pre;

	data_in[i] = data;
	func[i++] = tx_off_pre;

	/*
	 * Using cascade mode previously need to reset the trigger output so
	 * that an errorneous output will not be generated during next
	 * cascade mode setup.
	 */
	if (ptp->cascade_tx & tso_bit) {
		data_in[i] = data;
		func[i++] = tx_reset_pre;

		ptp->cascade_gpo[ptp->outputs[tso].gpo].tso &= ~tso_bit;
		ptp->cascade_tx &= ~tso_bit;
	}
	data_in[i] = data;
	func[i++] = tx_init_pre;

	data_out = data;
	data = iba_prepare(info, -1, data);

	func[i] = NULL;
	iba_assert(info, __func__, i, sizeof(func), buf, data, sizeof(buf));
	rc = info->ops->reqs(info, data_in, data_out, ptp, func,
		info->ops->r_post);
}  /* ptp_tx_off_iba */

static void *tx_on_pre(struct ksz_iba_info *info, void *in, void *obj)
{
	struct ptp_info *ptp = obj;
	u32 *data = in;
	u8 tso = (u8)data[0];

	iba_cmd_set(info, IBA_CMD_READ, IBA_CMD_32, REG_PTP_CTRL_STAT__4, 0);

	/* Do a reset on last TOU in previous cascade operation. */
	if (ptp->cascade_tx & (1 << (tso + 16))) {
		ptp->cascade_tx &= ~(1 << (tso + 16));
		iba_cmd_set(info, IBA_CMD_WRITE_1, IBA_CMD_32,
			REG_PTP_CTRL_STAT__4, TRIG_RESET);
	}
	iba_cmd_set(info, IBA_CMD_WRITE_0, IBA_CMD_32, REG_PTP_CTRL_STAT__4,
		TRIG_ENABLE | TRIG_RESET);
	iba_cmd_set(info, IBA_CMD_WRITE_1, IBA_CMD_32, REG_PTP_CTRL_STAT__4,
		TRIG_ENABLE);
	return info->fptr;
}  /* tx_on_pre */

static void *tx_trigger_time_iba(struct ksz_iba_info *info, u32 sec, u32 nsec)
{
	iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_32, REG_TRIG_TARGET_SEC,
		sec);
	iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_32, REG_TRIG_TARGET_NANOSEC,
		nsec);
	return info->fptr;
}  /* tx_trigger_time_iba */

static void *tx_restart_pre(struct ksz_iba_info *info, void *in, void *obj)
{
	u32 *data = in;
	u32 ctrl = data[1];
	u32 sec = data[2];
	u32 nsec = data[3];

	if (ctrl)
		iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_32, REG_TRIG_CTRL__4,
			    ctrl);
	tx_trigger_time_iba(info, sec, nsec);
	tx_on_pre(info, in, obj);
	return info->fptr;
}  /* tx_restart_pre */

static void ptp_tx_restart_iba(struct ptp_info *ptp, u8 tso, u32 ctrl, u32 sec,
			       u32 nsec)
{
	struct ksz_sw *sw = ptp->parent;
	struct ksz_iba_info *info = &sw->info->iba;
	int rc;
	void *func[3];
	void *data_in[2];
	u32 buf[8];
	u32 *data = buf;
	int i = 0;

	data_in[i] = data;
	data[0] = PTP_TOU_INDEX_S;
	data[1] = tso;

	/* Re-use tso for next command. */
	data += 1;
	func[i++] = ptp_unit_index_pre;

	data_in[i] = data;
	data[1] = ctrl;
	data[2] = sec;
	data[3] = nsec;
	data += 4;
	func[i++] = tx_restart_pre;

	func[i] = NULL;
	iba_assert(info, __func__, i, sizeof(func), buf, data, sizeof(buf));
	rc = info->ops->reqs(info, data_in, NULL, ptp, func, NULL);
}  /* ptp_tx_restart_iba */

static void *tx_event_pre(struct ksz_iba_info *info, void *in, void *obj)
{
	u32 *data = in;
	u32 ctrl = data[1];
	u32 pulse = data[2];
	u32 cycle = data[3];
	u32 pattern = data[4];
	u32 sec = data[5];
	u32 nsec = data[6];

	iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_32, REG_TRIG_CTRL__4, ctrl);
	if (pulse)
		iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_24,
			REG_TRIG_PULSE_WIDTH__4 + 1, pulse);
	if (cycle) {
		iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_32,
			REG_TRIG_CYCLE_WIDTH, cycle);
		iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_32,
			REG_TRIG_CYCLE_CNT, pattern);
	}

	/* Trigger time is set later in cascade mode. */
	if (sec) {
		tx_trigger_time_iba(info, sec, nsec);
		tx_on_pre(info, in, obj);
	}
	return info->fptr;
}  /* tx_event_pre */

static void ptp_tx_event_iba(struct ptp_info *ptp, u8 tso, u32 ctrl, u32 pulse,
	u32 cycle, u32 pattern, u32 sec, u32 nsec)
{
	struct ksz_sw *sw = ptp->parent;
	struct ksz_iba_info *info = &sw->info->iba;
	int rc;
	void *func[3];
	void *data_in[2];
	u32 buf[20];
	u32 *data = buf;
	int i = 0;

	data_in[i] = data;
	data[0] = PTP_TOU_INDEX_S;
	data[1] = tso;
	data += 2;
	func[i++] = ptp_unit_index_pre;

	data_in[i] = data;
	data[0] = tso;
	data[1] = ctrl;
	data[2] = pulse;
	data[3] = cycle;
	data[4] = pattern;
	data[5] = sec;
	data[6] = nsec;
	data += 7;
	func[i++] = tx_event_pre;

	func[i] = NULL;
	iba_assert(info, __func__, i, sizeof(func), buf, data, sizeof(buf));
	rc = info->ops->reqs(info, data_in, NULL, ptp, func, NULL);
}  /* ptp_tx_event_iba */

static void *pps_event_pre(struct ksz_iba_info *info, void *in, void *obj)
{
	u32 *data = in;
	u8 gpo = data[3];
	u32 sec = data[4];
	struct ptp_info *ptp = obj;
	u32 pattern;
	u32 ctrl;
	u32 nsec;
	u32 pulse = (20000000 / 8);	/* 20 ms */
	u32 cycle = 1000000000;
	u16 cnt = 0;
	u8 event = TRIG_POS_PERIOD;

	/* Config pattern. */
	ctrl = trig_event_gpo(gpo, event);
	ctrl |= TRIG_NOTIFY;
	ctrl |= TRIG_NOW;
	ctrl |= trig_cascade(TRIG_CASCADE_UPS_M);
	iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_32, REG_TRIG_CTRL__4, ctrl);

	/* Config pulse width. */
	if (pulse > TRIG_PULSE_WIDTH_M)
		pulse = TRIG_PULSE_WIDTH_M;
	iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_24,
		REG_TRIG_PULSE_WIDTH__4 + 1, pulse);

	/* Config cycle width. */
	iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_32, REG_TRIG_CYCLE_WIDTH,
		cycle);

	/* Config trigger count. */
	pattern = cnt;
	pattern <<= TRIG_CYCLE_CNT_S;
	iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_32, REG_TRIG_CYCLE_CNT,
		pattern);

	/* Config trigger time. */
	if (ptp->pps_offset >= 0) {
		nsec = ptp->pps_offset;
	} else {
		nsec = NANOSEC_IN_SEC + ptp->pps_offset;
		sec--;
	}
	tx_trigger_time_iba(info, sec, nsec);

	return info->fptr;
}  /* pps_event_pre */

static void ptp_pps_event_iba(struct ptp_info *ptp, u8 gpo, u32 sec)
{
	struct ksz_sw *sw = ptp->parent;
	struct ksz_iba_info *info = &sw->info->iba;
	u8 tso = ptp->pps_tso;
	int rc;
	void *func[5];
	void *data_in[4];
	u32 buf[20];
	u32 *data = buf;
	int i = 0;

	ptp_tx_off_iba(ptp, tso);

	data_in[i] = data;
	data[3] = gpo;
	data[4] = sec;
	data += 5;
	func[i++] = pps_event_pre;

	data_in[i] = data;
	data[0] = tso;
	data += 1;
	func[i++] = tx_on_pre;

	func[i] = NULL;
	iba_assert(info, __func__, i, sizeof(func), buf, data, sizeof(buf));
	rc = info->ops->reqs(info, data_in, NULL, ptp, func, NULL);
}  /* ptp_pps_event */

static void *ptp_10MHz_pre(struct ksz_iba_info *info, void *in, void *obj)
{
	u32 *data = in;
	u8 tso = data[3];
	u8 gpo = data[4];
	u32 sec = data[5];
	u32 nsec = data[6];
	u32 pattern;
	u32 ctrl;
	u32 pulse = 6;
	u32 cycle = 200;
	u16 cnt = 0;
	u8 event = TRIG_POS_PERIOD;

	/* Config pattern. */
	ctrl = trig_event_gpo(gpo, event);
	ctrl |= TRIG_NOTIFY;
	if (1 == tso)
		ctrl |= TRIG_EDGE;
	ctrl |= trig_cascade(TRIG_CASCADE_UPS_M);
	iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_32, REG_TRIG_CTRL__4, ctrl);

	/* Config pulse width. */
	if (pulse > TRIG_PULSE_WIDTH_M)
		pulse = TRIG_PULSE_WIDTH_M;
	iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_32,
		REG_TRIG_PULSE_WIDTH__4 + 0, pulse);

	/* Config cycle width. */
	iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_32, REG_TRIG_CYCLE_WIDTH,
		cycle);

	/* Config trigger count. */
	pattern = cnt;
	pattern <<= TRIG_CYCLE_CNT_S;
	iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_32, REG_TRIG_CYCLE_CNT,
		pattern);

	tx_trigger_time_iba(info, sec, nsec);

	return info->fptr;
}  /* ptp_10MHz_pre */

static void ptp_10MHz_iba(struct ptp_info *ptp, u8 tso, u8 gpo, u32 sec)
{
	struct ksz_sw *sw = ptp->parent;
	struct ksz_iba_info *info = &sw->info->iba;
	int n;
	u32 nsec;
	int rc;
	void *func[5];
	void *data_in[4];
	u32 buf[20];
	u32 *data = buf;
	u32 *data_out;
	int k = 0;

	/* Config trigger time. */
	if (ptp->pps_offset >= 0) {
		nsec = ptp->pps_offset;
	} else {
		nsec = NANOSEC_IN_SEC + ptp->pps_offset;
		sec--;
	}

	for (n = 0; n < 2; n++) {
		ptp_tx_off_iba(ptp, tso);

		k = 0;
		data = buf;

		data_in[k] = data;
		data[3] = tso;
		data[4] = gpo;
		data[5] = sec;
		data[6] = nsec;
		data += 7;
		func[k++] = ptp_10MHz_pre;

		data_in[k] = data;
		data[0] = tso;
		data += 1;
		func[k++] = tx_on_pre;

		data_out = data;
		data = iba_prepare(info, REG_PTP_CTRL_STAT__4, data);
		data = iba_prepare(info, -1, data);

		func[k] = NULL;
		iba_assert(info, __func__, k, sizeof(func), buf, data,
			sizeof(buf));
		rc = info->ops->reqs(info, data_in, data_out, ptp, func,
			info->ops->r_post);

		tso = 1;
		nsec += 12 * 8;
	}
}  /* ptp_10MHz_iba */

static void *tx_cascade_cycle_iba(struct ksz_iba_info *info, u8 tso, u32 nsec)
{
	iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_32, REG_TRIG_ITERATE_TIME,
		nsec);
	return info->fptr;
}  /* tx_cascade_cycle_iba */

static void *tx_cascade_on_pre(struct ksz_iba_info *info, void *in,
	void *obj)
{
	u32 *data = in;
	u8 tso = data[3];
	u8 first = data[4];
	u8 last = data[5];
	u16 repeat = data[6];
	struct ptp_output *cur = obj;
	u32 ctrl;

	tx_trigger_time_iba(info, cur->trig.sec, cur->trig.nsec);
	tx_cascade_cycle_iba(info, tso, (u32)cur->iterate);

	ctrl = data[2];
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
	iba_cmd_set(info, IBA_CMD_WRITE, IBA_CMD_32, REG_TRIG_CTRL__4, ctrl);
	return info->fptr;
}  /* tx_cascade_on_pre */

static int ptp_tx_cascade_iba(struct ptp_info *ptp, u8 first, u8 total,
	u16 repeat, u32 sec, u32 nsec, int intr)
{
	struct ksz_sw *sw = ptp->parent;
	struct ksz_iba_info *info = &sw->info->iba;
	int n;
	u8 tso;
	u8 last;
	struct ptp_output *cur = NULL;
	int rc;
	void *func[5];
	void *data_in[4];
	u32 buf[20];
	u32 *data = buf;
	u32 *data_out;
	int k = 0;

	last = first + total - 1;
	if (last >= MAX_TRIG_UNIT)
		return 1;
	tso = last;
	for (n = 0; n < total; n++, tso--) {
		cur = &ptp->outputs[tso];
		data = buf;
		k = 0;
		data_in[k] = data;
		data[0] = PTP_TOU_INDEX_S;
		data[1] = tso;
		data += 2;
		func[k++] = ptp_unit_index_pre;

		/* Need reset on last TOU in previous cascade operation. */
		if (ptp->cascade_tx & (1 << (tso + 16))) {
			data_in[k] = data;
			func[k++] = tx_reset_pre;
			ptp->cascade_tx &= ~(1 << (tso + 16));
		}
		data_in[k] = data;
		data[0] = IBA_CMD_32;
		data[1] = REG_TRIG_CTRL__4;
		data += 3;
		func[k++] = info->ops->r_pre;

		data_out = data;
		data = iba_prepare(info, REG_TRIG_CTRL__4, data);
		data = iba_prepare(info, -1, data);

		func[k] = NULL;
		iba_assert(info, __func__, k, sizeof(func), buf, data,
			sizeof(buf));
		rc = info->ops->reqs(info, data_in, data_out, ptp, func,
			info->ops->r_post);

		data = buf;
		k = 0;

		data_in[k] = data;
		data[2] = data_out[1];
		data[3] = tso;
		data[4] = first;
		data[5] = last;
		data[6] = repeat;
		data += 7;
		func[k++] = tx_cascade_on_pre;

		func[k] = NULL;
		iba_assert(info, __func__, k, sizeof(func), buf, data,
			sizeof(buf));
		if (tso != first)
			rc = info->ops->reqs(info, data_in, NULL, cur, func,
				NULL);
		ptp->cascade_tx |= (1 << tso);
	}

	data_in[k] = data;
	data[0] = last;
	data += 1;
	func[k++] = tx_on_pre;

	func[k] = NULL;
	iba_assert(info, __func__, k, sizeof(func), buf, data, sizeof(buf));
	rc = info->ops->reqs(info, data_in, NULL, cur, func, NULL);
	return 0;
}  /* ptp_tx_cascade_iba */

static struct ptp_reg_ops ptp_iba_ops = {
	.get_time		= get_ptp_time_iba,
	.set_time		= set_ptp_time_iba,
	.adjust_time		= adjust_ptp_time_iba,
	.adjust_sync_time	= adjust_sync_time_iba,

	.rx_off			= ptp_rx_off_iba,
	.rx_reset		= ptp_rx_reset_iba,
	.rx_restart		= ptp_rx_restart_iba,
	.rx_event		= ptp_rx_event_iba,
	.rx_cascade_event	= ptp_rx_cascade_event_iba,
	.read_event		= ptp_read_event_iba,

	.tx_off			= ptp_tx_off_iba,
	.tx_restart		= ptp_tx_restart_iba,
	.tx_event		= ptp_tx_event_iba,
	.pps_event		= ptp_pps_event_iba,
	.ptp_10MHz		= ptp_10MHz_iba,
	.tx_cascade		= ptp_tx_cascade_iba,

	.start			= ptp_start,
};
