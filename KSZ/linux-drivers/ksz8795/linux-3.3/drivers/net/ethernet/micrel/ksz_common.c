/**
 * Micrel Ethernet driver common code
 *
 * Copyright (c) 2015 Microchip Technology Inc.
 *	Tristram Ha <Tristram.Ha@microchip.com>
 *
 * Copyright (c) 2009-2011 Micrel, Inc.
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


/**
 * ksz_start_timer - start kernel timer
 * @info:	Kernel timer information.
 * @time:	The time tick.
 *
 * This routine starts the kernel timer after the specified time tick.
 */
static void ksz_start_timer(struct ksz_timer_info *info, int time)
{
	info->cnt = 0;
	info->timer.expires = jiffies + time;
	add_timer(&info->timer);

	/* infinity */
	info->max = -1;
}  /* ksz_start_timer */

/**
 * ksz_stop_timer - stop kernel timer
 * @info:	Kernel timer information.
 *
 * This routine stops the kernel timer.
 */
static void ksz_stop_timer(struct ksz_timer_info *info)
{
	if (info->max) {
		info->max = 0;
		del_timer_sync(&info->timer);
	}
}  /* ksz_stop_timer */

static void ksz_init_timer(struct ksz_timer_info *info, int period,
	void (*function)(unsigned long), void *data)
{
	info->max = 0;
	info->period = period;
	init_timer(&info->timer);
	info->timer.function = function;
	info->timer.data = (unsigned long) data;
}  /* ksz_init_timer */

static void ksz_update_timer(struct ksz_timer_info *info)
{
	++info->cnt;
	if (info->max > 0) {
		if (info->cnt < info->max) {
			info->timer.expires = jiffies + info->period;
			add_timer(&info->timer);
		} else
			info->max = 0;
	} else if (info->max < 0) {
		info->timer.expires = jiffies + info->period;
		add_timer(&info->timer);
	}
}  /* ksz_update_timer */

/* -------------------------------------------------------------------------- */

#define DBG_CH  '-'

#ifdef DEBUG_MSG

/* 2 lines buffer. */
#define DEBUG_MSG_BUF			(80 * 2)

#define PRINT_MSG_SIZE			(80 * 150)
#define PRINT_INT_SIZE			(80 * 10)

#define DEBUG_MSG_SIZE			(PRINT_MSG_SIZE + PRINT_INT_SIZE + \
	DEBUG_MSG_BUF * 2)

struct dbg_print {
	char *dbg_buf;
	char *int_buf;
	char *msg;
	char *int_msg;
	int msg_cnt;
	int int_cnt;
	int last_msg_line;
	int last_int_line;
	unsigned long lock;

	struct work_struct dbg_print;
	struct ksz_timer_info dbg_timer_info;
};

static struct dbg_print db;

static void print_buf(char *buf, char **msg, int *cnt, int *last)
{
	char ch;
	char *start;

	if (*last)
		printk(KERN_INFO "%c\n", DBG_CH);
	*last = 0;
	if ('\n' == buf[*cnt - 2] && DBG_CH == buf[*cnt - 1]) {
		buf[*cnt - 1] = '\0';
		*last = 1;
	}
	*msg = buf;

	/* Kernel seems to limit printk buffer to 1024 bytes. */
	while (strlen(buf) >= 1024) {
		start = &buf[1020];
		while (start != buf && *start != '\n')
			start--;
		if (start != buf) {
			start++;
			ch = *start;
			*start = '\0';
			printk(KERN_INFO "%s", buf);
			*start = ch;
			buf = start;
		}
	}
	*cnt = 0;
	printk(KERN_INFO "%s", buf);
}  /* print_buf */

static void dbg_print_work(struct work_struct *work)
{
	if (db.msg != db.dbg_buf)
		print_buf(db.dbg_buf, &db.msg, &db.msg_cnt,
			&db.last_msg_line);
	if (db.int_msg != db.int_buf) {
		printk(KERN_INFO "---\n");
		print_buf(db.int_buf, &db.int_msg, &db.int_cnt,
			&db.last_int_line);
	}
}  /* dbg_print_work */

static void dbg_monitor(unsigned long ptr)
{
	struct dbg_print *dbp = (struct dbg_print *) ptr;

	dbg_print_work(&dbp->dbg_print);
	ksz_update_timer(&dbp->dbg_timer_info);
}  /* dbg_monitor */

static int init_dbg(void)
{
	db.dbg_buf = kmalloc(DEBUG_MSG_SIZE, GFP_KERNEL);
	if (!db.dbg_buf)
		return -ENOMEM;

	db.msg = db.dbg_buf;
	*db.msg = '\0';
	db.int_buf = db.dbg_buf + PRINT_MSG_SIZE + DEBUG_MSG_BUF;
	db.int_msg = db.int_buf;
	*db.int_msg = '\0';
	db.msg_cnt = db.int_cnt = 0;
	db.last_msg_line = 1;
	db.last_int_line = 1;
	db.lock = 0;

	INIT_WORK(&db.dbg_print, dbg_print_work);

	/* 100 ms timeout */
	ksz_init_timer(&db.dbg_timer_info, 100 * HZ / 1000, dbg_monitor, &db);
	ksz_start_timer(&db.dbg_timer_info, db.dbg_timer_info.period);

	return 0;
}  /* init_dbg */

static void exit_dbg(void)
{
	if (db.dbg_buf) {
		ksz_stop_timer(&db.dbg_timer_info);
		flush_work(&db.dbg_print);

		if (db.msg != db.dbg_buf)
			printk(KERN_DEBUG "%s\n", db.dbg_buf);
		if (db.int_msg != db.int_buf)
			printk(KERN_DEBUG "%s\n", db.int_buf);
		kfree(db.dbg_buf);
		db.dbg_buf = NULL;
	}
}  /* exit_dbg */
#endif

static void dbg_msg(char *fmt, ...)
{
#ifdef DEBUG_MSG
	va_list args;
	char **msg;
	int *dbg_cnt;
	int left;
	int in_intr = in_interrupt();
	int n;

	dbg_cnt = &db.msg_cnt;
	msg = &db.msg;
	left = PRINT_MSG_SIZE - db.msg_cnt - 1;
	if (left <= 0) {
		db.last_msg_line = 1;
		return;
	}

	/* Called within interrupt routines. */
	if (in_intr) {
		/*
		 * If not able to get lock then put in the interrupt message
		 * buffer.
		 */
		if (test_bit(1, &db.lock)) {
			dbg_cnt = &db.int_cnt;
			msg = &db.int_msg;
			left = PRINT_INT_SIZE - db.int_cnt - 1;
			in_intr = 0;
		}
	} else
		set_bit(1, &db.lock);
	va_start(args, fmt);
	n = vsnprintf(*msg, left + 1, fmt, args);
	va_end(args);
	if (n > 0) {
		if (left > n)
			left = n;
		*dbg_cnt += left;
		*msg += left;
	}
	if (!in_intr)
		clear_bit(1, &db.lock);
#endif
}  /* dbg_msg */

/* -------------------------------------------------------------------------- */

static inline void dbp_mac_addr(u8 *addr)
{
	dbg_msg("%02x:%02x:%02x:%02x:%02x:%02x",
		addr[0], addr[1], addr[2],
		addr[3], addr[4], addr[5]);
}  /* dbp_mac_addr */

static inline void dbp_pkt(struct sk_buff *skb, char first, char *msg, int hdr)
{
	int i;
	int len = skb->len;
	u8 *data = (u8 *) skb->data;

	if (!first || first != data[0]) {
		if (msg)
			dbg_msg(msg);
		if (hdr && len > 0x50)
			len = 0x50;
		for (i = 0; i < len; i++) {
			dbg_msg("%02x ", data[i]);
			if ((i % 16) == 15)
				dbg_msg("\n");
		}
		if ((i % 16))
			dbg_msg("\n");
	}
}  /* dbp_pkt */

static int get_num_val(const char *buf)
{
	int num = -1;

	if ('0' == buf[0] && 'x' == buf[1])
		sscanf(&buf[2], "%x", (unsigned int *) &num);
	else if ('0' == buf[0] && 'b' == buf[1]) {
		int i = 2;

		num = 0;
		while (buf[i]) {
			num <<= 1;
			num |= buf[i] - '0';
			i++;
		}
	} else if ('0' == buf[0] && 'd' == buf[1])
		sscanf(&buf[2], "%u", &num);
	else
		sscanf(buf, "%d", &num);
	return num;
}  /* get_num_val */

