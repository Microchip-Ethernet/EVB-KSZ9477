/**
 * Microchip MRP driver code
 *
 * Copyright (c) 2015-2017 Microchip Technology Inc.
 *	Tristram Ha <Tristram.Ha@microchip.com>
 *
 * Copyright (c) 2014-2015 Micrel, Inc.
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
#define DEBUG_MRP_MEM
#endif


static int get_actual_port(struct mrp_info *mrp, u8 port)
{
	struct ksz_sw *sw = container_of(mrp, struct ksz_sw, mrp);

	return sw_get_dev_port(sw, 0, mrp->ports, port + 1);
}  /* get_actual_port */

#ifdef CONFIG_KSZ_MSRP
#define SW_CREDIT_SHAPING_SCALE	0x10000
#define SW_CREDIT_SHAPING_S	16

#define CREDIT_PERCENTAGE_S	(16 + 9)

#define NETWORK_SPEED_IN_MBIT	1000000

static char *format_num(char *str, u32 num)
{
	u32 num0;
	u32 num1;
	u32 num2;
	u32 num3;

	num0 = num % 1000;
	num1 = (num / 1000) % 1000;
	num2 = (num / 1000000) % 1000;
	num3 = (num / 1000000000);
	if (num3)
		sprintf(str, "%u,%03u,%03u,%03u", num3, num2, num1, num0);
	else if (num2)
		sprintf(str, "%u,%03u,%03u", num2, num1, num0);
	else if (num1)
		sprintf(str, "%u,%3u", num1, num0);
	else
		sprintf(str, "%u", num0);
	return str;
}  /* format_num */

static char *format_per(char *str, u32 per)
{
	u64 val;
	u32 num;
	u32 num0;
	u32 num1;

	val = per;
	val *= 100;
	val += 1 << (CREDIT_PERCENTAGE_S - 1);
	val >>= CREDIT_PERCENTAGE_S;
	num = (u32) val;
	num0 = num % 100;
	num1 = num / 100;
	if (num1)
		sprintf(str, "%u.%02u%%", num1, num0);
	else
		sprintf(str, "0.%02u%%", num0);
	return str;
}  /* format_per */

static u16 get_credit_increment(u32 speed, u32 bandwidth)
{
	u64 val;
	u32 rem;

	speed *= NETWORK_SPEED_IN_MBIT;

	/* Cannot get higher than the running speed. */
	if (bandwidth > speed)
		return 0;
	val = bandwidth;
	val <<= SW_CREDIT_SHAPING_S;
	val += speed / 2;
	val = div_u64_rem(val, speed, &rem);

	/* Cannot become zero. */
	if (!val)
		val = 1;
	return (u16) val;
}  /* get_credit_increment */

static u16 get_hi_credit(u32 size, u32 slope)
{
	u64 val;
	u32 rem;

	/* Preamable + CRC + IFG */
	size += 8 + 4 + 12;
	val = size;
	val *= slope;
	size = 100;
	size <<= CREDIT_PERCENTAGE_S;
	val += 50 << CREDIT_PERCENTAGE_S;
	val = div_u64_rem(val, size, &rem);
	return (u16) val;
}  /* get_hi_credit */

static u16 get_lo_credit(u32 size, u32 slope)
{
	u64 val;
	u32 rem;

	/* Preamable + vlan_ethhdr + CRC + IFG */
	size += 8 + 14 + 4 + 4 + 12;
	val = size;
	val *= slope;
	size = 100;
	size <<= CREDIT_PERCENTAGE_S;
	val += 50 << CREDIT_PERCENTAGE_S;
	val = div_u64_rem(val, size, &rem);
	return (u16) val;
}  /* get_lo_credit */

static u32 get_idle_slope(u32 speed, u32 bandwidth)
{
	u64 val;
	u32 rem;

	speed *= NETWORK_SPEED_IN_MBIT;

	/* Cannot get higher than the running speed. */
	if (bandwidth > speed)
		return 0;
	val = bandwidth;
	val *= 100;
	val <<= CREDIT_PERCENTAGE_S;
	val = div_u64_rem(val, speed, &rem);
	return (u32) val;
}  /* get_idle_slope */

static u32 get_send_slope(u32 idle_slope)
{
	u32 slope;

	slope = 100;
	slope <<= CREDIT_PERCENTAGE_S;
	slope -= idle_slope;
	return slope;
}  /* get_send_slope */

static u8 get_queue_priority(struct mrp_info *mrp, int tc)
{
	return mrp->prio[tc];
}  /* get_queue_priority */

static void srp_cfg_credit_shaper(struct mrp_info *mrp, u8 lp,
	struct mrp_port_info *info, struct mrp_traffic_info *traffic)
{
	u16 credit;
	u16 credit_lo;
	u16 credit_hi;
	u32 idle;
	u32 send;
	int port;
	u8 queue;
	char bw_str[20];
	char idle_str[20];
	char send_str[20];

	port = get_actual_port(mrp, lp);
	credit = get_credit_increment(info->speed,
		traffic->bandwidth_used);
	idle = get_idle_slope(info->speed, traffic->bandwidth_used);
	send = get_send_slope(idle);
	credit_hi = get_hi_credit(mrp->max_interference_size, idle);
	credit_lo = get_lo_credit(traffic->max_frame_size, send);
	queue = traffic->queue;

	format_num(bw_str, traffic->bandwidth_used);
	format_per(idle_str, idle);
	format_per(send_str, send);
dbg_msg("  %s %d:%d=%u %u %u; %s %s %s\n", __func__, port,
	queue, credit, credit_hi, credit_lo,
	bw_str, idle_str, send_str);

#ifdef CONFIG_HAVE_KSZ9897
	do {
		struct ksz_sw *sw = container_of(mrp, struct ksz_sw, mrp);

		sw->reg->lock(sw);
		if (credit > 1) {
			port_set_hi_water_mark(sw, port, queue, credit_hi);
			port_set_lo_water_mark(sw, port, queue, credit_lo);
			port_set_increment(sw, port, queue, credit);
			port_set_schedule_mode(sw, port, queue,
				MTI_SCHEDULE_STRICT_PRIO);
			port_set_shaping(sw, port, queue, MTI_SHAPING_SRP);
		} else {
			port_set_schedule_mode(sw, port, queue,
				MTI_SCHEDULE_WRR);
			port_set_shaping(sw, port, queue, MTI_SHAPING_OFF);
		}
		sw->reg->unlock(sw);
	} while (0);
#endif
}  /* srp_cfg_credit_shaper */

static void srp_cfg_idle_slope(struct mrp_info *mrp, int port,
	struct mrp_port_info *info, u64 idle_slope)
{
	u16 credit;
	u16 credit_lo;
	u16 credit_hi;
	u32 idle;
	u32 send;
	char bw_str[20];
	char idle_str[20];
	char send_str[20];
	struct ksz_sw *sw = container_of(mrp, struct ksz_sw, mrp);
	struct ksz_port_cfg *cfg = &sw->info->port_cfg[port];

	credit = get_credit_increment(info->speed, idle_slope);
	idle = get_idle_slope(info->speed, idle_slope);
	send = get_send_slope(idle);
	credit_hi = get_hi_credit(mrp->max_interference_size, idle);
	credit_lo = get_lo_credit(1500, send);
	format_num(bw_str, idle_slope);
	format_per(idle_str, idle);
	format_per(send_str, send);
dbg_msg("  %s %d:%d=%u %u %u; %s %s %s\n", __func__, port,
	cfg->q_index, credit, credit_hi, credit_lo,
	bw_str, idle_str, send_str);

#ifdef CONFIG_HAVE_KSZ9897
	sw->reg->lock(sw);
	port_set_hi_water_mark(sw, port, cfg->q_index, credit_hi);
	port_set_lo_water_mark(sw, port, cfg->q_index, credit_lo);
	port_set_increment(sw, port, cfg->q_index, credit);
	sw->reg->unlock(sw);
#endif
}  /* srp_cfg_idle_slope */
#endif

static void mrp_cfg_dest_addr(struct mrp_info *mrp, u8 index, u8 *dest,
	u32 ports, u16 fid)
{
	struct ksz_sw *sw = container_of(mrp, struct ksz_sw, mrp);

dbg_msg("  %s %d=%02x:%02x:%02x:%02x:%02x:%02x %04x %x\n", __func__, index,
dest[0], dest[1], dest[2], dest[3], dest[4],dest[5],
ports, fid);
	ports &= SRP_PORT_AVAIL | SRP_PORT_READY;
	ports = sw_get_dest_port(sw, 0, mrp->ports, ports);
	sw->ops->cfg_mac(sw, index, dest, ports, false, fid != 0, fid);
}  /* mrp_cfg_dest_addr */

static void mrp_cfg_vlan(struct mrp_info *mrp, u8 index, u16 vid, u16 fid,
	u32 ports)
{
	struct ksz_sw *sw = container_of(mrp, struct ksz_sw, mrp);

dbg_msg("  %s %d=%x %x %04x\n", __func__, index, vid, fid, ports);
	ports &= SRP_PORT_AVAIL | SRP_PORT_READY;
	ports = sw_get_dest_port(sw, 0, mrp->ports, ports);

	/* Needed to catch unwanted multicast traffic. */
	if (ports)
		ports |= sw->HOST_MASK;
	sw->ops->cfg_vlan(sw, index, vid, fid, ports);
}  /* mrp_cfg_vlan */

#ifdef CONFIG_KSZ_MSRP
static int get_traffic_class(struct mrp_info *mrp, u8 prio)
{
	return mrp->tc[prio];
}  /* get_traffic_class */

static struct mrp_traffic_info *get_traffic_info(struct mrp_port_info *port,
	int tc)
{
	if (SR_CLASS_A == tc)
		return &port->traffic[0];
	else
		return &port->traffic[1];
}  /* get_traffic_info */

static struct mrp_port_info *get_port_info(struct mrp_info *mrp, u8 port)
{
	port = get_actual_port(mrp, port);
	return &mrp->port_info[port];
}  /* get_port_info */

static int frames_per_sec(int traffic_class)
{
	int frames;

	switch (traffic_class) {
	case SR_CLASS_A:
		frames = 8000;
		break;
	case SR_CLASS_B:
	default:
		frames = 4000;
	}
	return frames;
}  /* frames_per_sec */

static u64 calculate_bandwidth(u32 size, u32 interval, u32 frames)
{
	u64 bandwidth;

	bandwidth = size;

	/* Preamable + vlan_ethhdr + CRC + IFG */
	bandwidth += 8 + 14 + 4 + 4 + 12;
	bandwidth *= interval;
	bandwidth *= frames;
	bandwidth *= 8;
	return bandwidth;
}  /* calculate_bandwidth */
#endif

static int cmp_mac(void *first, void *second)
{
	int cmp;
	struct mrp_mac_info *a = first;
	struct mrp_mac_info *b = second;

	cmp = a->fid - b->fid;
	if (!cmp)
		cmp = memcmp(a->addr, b->addr, ETH_ALEN);
	return cmp;
}  /* cmp_mac */

static void show_mac_info(void *this)
{
	struct mrp_mac_info *info = this;

	dbg_msg(
		"%02x:%02x:%02x:%02x:%02x:%02x %d=%03x r:%04x s:%04x t:%04x\n",
		info->addr[0], info->addr[1], info->addr[2],
		info->addr[3], info->addr[4], info->addr[5],
		info->index, info->fid,
		info->mrp_ports, info->srp_ports, info->tx_ports);
}  /* show_mac_info */

static int cmp_vlan(void *first, void *second)
{
	int cmp;
	struct mrp_vlan_info *a = first;
	struct mrp_vlan_info *b = second;

	cmp = a->vid - b->vid;
	if (!cmp)
		cmp = memcmp(a->addr, b->addr, ETH_ALEN);
	return cmp;
}  /* cmp_vlan */

static void show_vlan_info(void *this)
{
	struct mrp_vlan_info *info = this;

	if (info->addr[0] != 0xff)
		dbg_msg(
			"[%02x:%02x:%02x:%02x:%02x:%02x] ",
			info->addr[0], info->addr[1], info->addr[2],
			info->addr[3], info->addr[4], info->addr[5]);
	dbg_msg(
		"%d=%03x.%03x r:%04x t:%04x\n", info->index,
		info->vid, info->fid, info->ports, info->tx_ports);
}  /* show_vlan_info */

#ifdef CONFIG_KSZ_MSRP
static void prepare_stream_info(struct SRP_reservation *reserv, u8 tc,
	struct srp_stream_info *x)
{
	x->reserv = reserv;
	x->id = reserv->stream->id;
	x->age = reserv->streamAge;
	x->rank = reserv->stream->rank;
	x->tc = tc;
}  /* prepare_stream_info */

static int cmp_stream(struct srp_stream_info *a, struct srp_stream_info *b)
{
	int cmp;

	cmp = a->tc - b->tc;
	if (cmp)
		return cmp;
	cmp = a->rank - b->rank;
	if (cmp)
		return cmp;
	cmp = a->age - b->age;
	if (cmp)
		return cmp;
	cmp = memcmp(a->id, b->id, 8);
	return cmp;
}  /* cmp_stream */

static int cmp_lower_stream(void *first, void *second)
{
	return cmp_stream(second, first);
}  /* cmp_lower_stream */

static int cmp_higher_stream(void *first, void *second)
{
	return cmp_stream(first, second);
}  /* cmp_higher_stream */

static void show_stream_info(void *this)
{
	struct srp_stream_info *info = this;

	dbg_msg(
		"p:%u r:%u t:%08x %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\n",
		info->tc, info->rank, info->age,
		info->id[0], info->id[1], info->id[2], info->id[3],
		info->id[4], info->id[5], info->id[6], info->id[7]);
}  /* show_stream_info */
#endif

#ifdef DEBUG
static void *get_show(int (*cmp)(void *a, void *b))
{
	if (cmp == cmp_mac)
		return show_mac_info;
	else if (cmp == cmp_vlan)
		return show_vlan_info;

#ifdef CONFIG_KSZ_MSRP
	else
		return show_stream_info;
#else
	else
		return NULL;
#endif
}  /* get_show */
#endif

static void mrp_init_list(struct mrp_node_anchor *list)
{
	list->last = &list->anchor;
	list->anchor.next = NULL;
}  /* mrp_init_list */

static void *mrp_find_node(struct mrp_node_anchor *list,
	int (*cmp)(void *a, void *b), void *data)
{
	int c;
	struct mrp_node *prev;
	struct mrp_node *next;

	prev = &list->anchor;
	next = prev->next;
	while (next) {
		c = cmp(next->data, data);

		/* Exact match. */
		if (!c)
			goto mrp_find_node_done;

		/* Will not be found as list is sorted. */
		if (c > 0) {
#ifdef DEBUG
			void (*show)(void *this) = get_show(cmp);

dbg_msg(" %s ", __func__);
			show(next->data);
#endif
			next = NULL;
			break;
		}
		prev = next;
		next = prev->next;
	}

mrp_find_node_done:
	list->last = prev;
	return next;
}  /* mrp_find_node */

static void mrp_insert_node(struct mrp_node_anchor *list,
	int (*cmp)(void *a, void *b), struct mrp_node *this)
{
	int c;
	struct mrp_node *prev;
	struct mrp_node *next;

	if (list->last != &list->anchor) {
		prev = list->last;
		next = prev->next;
#ifdef DEBUG
dbg_msg(" %s ", __func__);
		if (next) {
			void (*show)(void *this) = get_show(cmp);

			show(next->data);
		} else
dbg_msg("last one\n");
#endif
		c = 1;
		if (next) {
			c = cmp(next->data, this->data);
		}
		if (c > 0) {
			this->next = prev->next;
			prev->next = this;
			list->last = &list->anchor;
			return;
		}
	}
	prev = &list->anchor;
	next = prev->next;
	while (next) {
		c = cmp(next->data, this->data);

		/* Stop if next one is higher in the list. */
		if (c > 0)
			break;
		prev = next;
		next = prev->next;
	}
	this->next = prev->next;
	prev->next = this;
	list->last = &list->anchor;
}  /* mrp_insert_node */

static struct mrp_node *mrp_delete_this_node(struct mrp_node_anchor *list,
	int (*cmp)(void *a, void *b), struct mrp_node *this, int delete)
{
	int c;
	struct mrp_node *prev;
	struct mrp_node *next;

	if (list->last != &list->anchor) {
		prev = list->last;
		next = prev->next;
#ifdef DEBUG
dbg_msg(" %s ", __func__);
		if (next) {
			void (*show)(void *this) = get_show(cmp);

			show(next->data);
		} else
dbg_msg("last one\n");
#endif
		c = 1;
		if (next == this)
			c = 0;
		else if (next)
			c = cmp(next->data, this->data);

		/* Exact match. */
		if (!c)
			goto mrp_delete_this_node_done;
	}
	prev = &list->anchor;
	next = prev->next;
	while (next) {
		c = cmp(next->data, this->data);

		/* Exact match. */
		if (!c)
			goto mrp_delete_this_node_done;

		/* Stop if next one is higher in the list. */
		if (c > 0)
			break;
		prev = next;
		next = prev->next;
	}

	/* Nothing is removed. */
	return NULL;

mrp_delete_this_node_done:
	prev->next = this->next;
	list->last = &list->anchor;

	/* Just remove the node. */
	if (!delete)
		return next;

	/* Free the node data. */
#ifdef DEBUG_MRP_MEM
if (delete > 1)
dbg_msg(" %s %p\n", __func__, next->data);
#endif
	if (delete > 1)
		kfree(next->data);

#ifdef DEBUG_MRP_MEM
dbg_msg(" %s %p\n", __func__, next);
#endif
	/* Free the node. */
	kfree(next);
	return NULL;
}  /* mrp_delete_this_node */

static void mrp_delete_node(struct mrp_node_anchor *list,
	int (*cmp)(void *a, void *b), struct mrp_node *this)
{
	mrp_delete_this_node(list, cmp, this, 2);
}  /* mrp_delete_node */

static struct mrp_node *mrp_remove_node(struct mrp_node_anchor *list,
	int (*cmp)(void *a, void *b), struct mrp_node *this)
{
	return mrp_delete_this_node(list, cmp, this, 0);
}  /* mrp_remove_node */

static void mrp_show_node(struct mrp_node_anchor *list,
	void (*show)(void *a))
{
	struct mrp_node *next;

	next = list->anchor.next;
	while (next) {
		show(next->data);
		next = next->next;
	}
}  /* mrp_show_node */

#ifdef CONFIG_KSZ_MSRP
static struct SRP_stream *srp_create_stream(u8 *id, u8 *dest, u16 vlan_id,
	u16 size, u16 interval, u8 prio, u8 rank)
{
	struct SRP_stream *stream;

	stream = kzalloc(sizeof(struct SRP_stream), GFP_KERNEL);
#ifdef DEBUG_MRP_MEM
dbg_msg(" %s %p\n", __func__, stream);
#endif
	if (stream) {
		memcpy(stream->id, id, 8);
		memcpy(stream->dest, dest, ETH_ALEN);
		stream->vlan_id = vlan_id;
		stream->MaxFrameSize = size;
		stream->MaxIntervalFrames = interval;
		stream->priority = prio;
		stream->rank = rank;
	}
	return stream;
}  /* srp_create_stream */

static struct SRP_stream *srp_find_stream_id(struct mrp_info *mrp, u8 *id)
{
	int cmp;
	struct SRP_stream *stream;

	stream = mrp->stream_by_id.id_next;
	while (stream) {
		cmp = memcmp(stream->id, id, 8);
		if (!cmp)
			break;
		stream = stream->id_next;
	}
	return stream;
}  /* srp_find_stream_id */

static struct SRP_stream *srp_find_dest_addr(struct mrp_info *mrp, u8 *dest)
{
	int cmp;
	struct SRP_stream *stream;

	stream = mrp->stream_by_dest.dest_next;
	while (stream) {
		cmp = memcmp(stream->dest, dest, ETH_ALEN);
		if (!cmp)
			break;
		stream = stream->dest_next;
	}
	return stream;
}  /* srp_find_dest_addr */

static void srp_insert_stream_by_id(struct mrp_info *mrp,
	struct SRP_stream *stream)
{
	struct SRP_stream *prev;
	struct SRP_stream *next;

	prev = &mrp->stream_by_id;
	next = prev->id_next;
	while (next) {
		if (memcmp(next->id, stream->id, 8) > 0)
			break;
		prev = next;
		next = prev->id_next;
	}
	if (next) {
		stream->id_next = next;
		next->id_prev = stream;
	}
	stream->id_prev = prev;
	prev->id_next = stream;
}  /* srp_insert_stream_by_id */

static void srp_insert_stream_by_dest(struct mrp_info *mrp,
	struct SRP_stream *stream)
{
	struct SRP_stream *prev;
	struct SRP_stream *next;

	prev = &mrp->stream_by_dest;
	next = prev->dest_next;
	while (next) {
		if (memcmp(next->dest, stream->dest, ETH_ALEN) > 0)
			break;
		prev = next;
		next = prev->dest_next;
	}
	if (next) {
		stream->dest_next = next;
		next->dest_prev = stream;
	}
	stream->dest_prev = prev;
	prev->dest_next = stream;
}  /* srp_insert_stream_by_dest */

static void srp_remove_stream(struct SRP_stream *stream, int free)
{
	if (stream->id_next)
		stream->id_next->id_prev = stream->id_prev;
	stream->id_prev->id_next = stream->id_next;
	if (stream->dest_next)
		stream->dest_next->dest_prev = stream->dest_prev;
	stream->dest_prev->dest_next = stream->dest_next;
#ifdef DEBUG_MRP_MEM
dbg_msg(" %s %p %d\n", __func__, stream, free);
#endif
	if (free)
		kfree(stream);
}  /* srp_remove_stream */

static struct SRP_reservation *srp_create_reservation(u8 *id, u8 dir, u8 dec,
	u32 latency, u8 *bridge_id, u8 code)
{
	struct SRP_reservation *reserv;

	reserv = kzalloc(sizeof(struct SRP_reservation), GFP_KERNEL);
#ifdef DEBUG_MRP_MEM
dbg_msg(" %s %p\n", __func__, reserv);
#endif
	if (reserv) {
		memcpy(reserv->id, id, 8);
		reserv->direction = dir;
		reserv->declaration = dec;
		reserv->latency = latency;
		memcpy(reserv->bridge_id, bridge_id, 8);
		reserv->code = code;
	}
	return reserv;
}  /* srp_create_reservation */

static struct SRP_reservation *srp_find_reservation(
	struct SRP_reservation *head, u8 *id, u8 dir)
{
	int cmp;
	struct SRP_reservation *reserv;

	reserv = head->next;
	while (reserv) {
		cmp = memcmp(reserv->id, id, 8);
		if (!cmp && dir == reserv->direction)
			break;
		if (cmp > 0)
			return NULL;
		reserv = reserv->next;
	}
	return reserv;
}  /* srp_find_reservation */

static void srp_insert_reservation(struct SRP_reservation *head,
	struct SRP_reservation *reserv)
{
	int cmp;
	struct SRP_reservation *prev;
	struct SRP_reservation *next;

	prev = head;
	next = prev->next;
	while (next) {
		cmp = memcmp(next->id, reserv->id, 8);
		if (cmp > 0)
			break;
		if (0 == cmp && next->declaration > reserv->declaration)
			break;
		prev = next;
		next = prev->next;
	}
	if (next) {
		reserv->next = next;
		next->prev = reserv;
	}
	reserv->prev = prev;
	prev->next = reserv;
}  /* srp_insert_reservation */

static void srp_remove_reservation(struct SRP_reservation *reserv, int free)
{
	if (reserv->next)
		reserv->next->prev = reserv->prev;
	reserv->prev->next = reserv->next;
#ifdef DEBUG_MRP_MEM
dbg_msg(" %s %p %d\n", __func__, reserv, free);
#endif
	if (free)
		kfree(reserv);
}  /* srp_remove_reservation */

static void chk_reservation(struct mrp_port_info *info, int port)
{
	struct SRP_reservation *reserv;

dbg_msg("%d:\n", port);
dbg_msg("  registered: %p\n", &info->registered);
	reserv = info->registered.next;
	while (reserv) {
dbg_msg("%p %02x:%02x %d %d\n", reserv,
reserv->id[6], reserv->id[7], reserv->direction,
	reserv->declaration);
		reserv = reserv->next;
	}
dbg_msg("  declared: %p\n", &info->declared);
	reserv = info->declared.next;
	while (reserv) {
dbg_msg("%p %02x:%02x %d %d\n", reserv,
reserv->id[6], reserv->id[7], reserv->direction,
	reserv->declaration);
		reserv = reserv->next;
	}
dbg_msg("  active:\n");
	mrp_show_node(&info->active, show_stream_info);
dbg_msg("  passive:\n");
	mrp_show_node(&info->passive, show_stream_info);
dbg_msg("A:%u B:%u T:%u\n",
	info->traffic[0].bandwidth_left,
	info->traffic[1].bandwidth_left,
	info->bandwidth_left);
dbg_msg("\n");
}  /* chk_reservation */
#endif

static struct mrp_node *mrp_alloc_node(size_t data_size)
{
	struct mrp_node *node;

	node = kzalloc(sizeof(struct mrp_node), GFP_KERNEL);
#ifdef DEBUG_MRP_MEM
dbg_msg(" %s %p %u\n", __func__, node, data_size);
#endif
	if (!node)
		return NULL;
	node->data = kzalloc(data_size, GFP_KERNEL);
#ifdef DEBUG_MRP_MEM
dbg_msg(" %s %p\n", __func__, node->data);
#endif
	if (!node->data) {
		kfree(node);
		return NULL;
	}
	return node;
}  /* mrp_alloc_node */

static void mrp_free_node(struct mrp_node *node)
{
#ifdef DEBUG_MRP_MEM
dbg_msg(" %s %p %p\n", __func__, node->data, node);
#endif
	kfree(node->data);
	kfree(node);
}  /* mrp_free_node */

static struct mrp_node *mrp_get_mac_info(struct mrp_node_anchor *list,
	u8 *addr, u16 fid)
{
	struct mrp_node *node;
	struct mrp_mac_info data;

	data.fid = fid;
	memcpy(data.addr, addr, ETH_ALEN);
	node = mrp_find_node(list, cmp_mac, &data);
	if (!node) {
		struct mrp_mac_info *info;

		node = mrp_alloc_node(sizeof(struct mrp_mac_info));
		if (!node)
			return NULL;
		info = node->data;
		info->fid = fid;
		memcpy(info->addr, data.addr, ETH_ALEN);
		mrp_insert_node(list, cmp_mac, node);
	}
	return node;
}  /* mrp_get_mac_info */

static struct mrp_node *mrp_get_vlan_info(struct mrp_node_anchor *list,
	u16 vid, u8 *addr)
{
	struct mrp_node *node;
	struct mrp_vlan_info data;

	data.vid = vid;
	if (addr)
		memcpy(data.addr, addr, ETH_ALEN);
	else
		memset(data.addr, 0xff, ETH_ALEN);
	node = mrp_find_node(list, cmp_vlan, &data);
	if (!node) {
		struct mrp_vlan_info *info;

		node = mrp_alloc_node(sizeof(struct mrp_vlan_info));
		if (!node)
			return NULL;
		info = node->data;
		info->vid = vid;
		memcpy(info->addr, data.addr, ETH_ALEN);
		mrp_insert_node(list, cmp_vlan, node);
	}
	return node;
}  /* mrp_get_vlan_info */

static u16 mrp_find_vlan_ports(struct mrp_node_anchor *list, u16 vid,
	u8 *index, u16 *fid)
{
	struct mrp_node *prev;
	struct mrp_node *next;
	struct mrp_vlan_info *info;
	u16 ports = 0;

	prev = &list->anchor;
	next = prev->next;
	while (next) {
		info = next->data;
		if (vid == info->vid && !(info->ports & SRP_PORT_IGNORE)) {
			ports |= info->ports;
			if (info->ports) {
				if (index && *index != info->index)
					*index = info->index;
				if (fid && *fid != info->fid)
					*fid = info->fid;
			}
		} else if (vid > info->vid)
			break;
		prev = next;
		next = prev->next;
	}
	return ports;
}  /* mrp_find_vlan_ports */

static struct mrp_report *mrp_create_report(struct SRP_reservation *reserv,
	u8 port)
{
	struct mrp_report *attrib;

	attrib = kzalloc(sizeof(struct mrp_report), GFP_KERNEL);
#ifdef DEBUG_MRP_MEM
dbg_msg(" %s %p\n", __func__, attrib);
#endif
	if (attrib) {
		attrib->attrib = reserv;
		attrib->port = port;
	}
	return attrib;
}  /* mrp_create_report */

static void add_attrib_report(struct mrp_info *mrp, void *ptr, u8 action,
	u8 type, u8 port)
{
	struct mrp_report *attrib;

	attrib = mrp_create_report(ptr, port);
	if (!attrib)
		return;

	attrib->action = action;
	attrib->type = type;

	if (mrp->report_tail)
		mrp->report_tail->next = attrib;
	mrp->report_tail = attrib;
	if (!mrp->report_head)
		mrp->report_head = attrib;
}  /* add_attrib_report */

static u8 mrp_alloc_mac(struct mrp_info *mrp)
{
	struct ksz_sw *sw = container_of(mrp, struct ksz_sw, mrp);

	return sw->ops->alloc_mac(sw);
}  /* mrp_alloc_mac */

static void mrp_free_mac(struct mrp_info *mrp, u8 index)
{
	struct ksz_sw *sw = container_of(mrp, struct ksz_sw, mrp);

	sw->ops->free_mac(sw, index);
}  /* mrp_free_mac */

static u8 mrp_alloc_vlan(struct mrp_info *mrp)
{
	struct ksz_sw *sw = container_of(mrp, struct ksz_sw, mrp);

	return sw->ops->alloc_vlan(sw);
}  /* mrp_alloc_vlan */

static void mrp_free_vlan(struct mrp_info *mrp, u8 index)
{
	struct ksz_sw *sw = container_of(mrp, struct ksz_sw, mrp);

	sw->ops->free_vlan(sw, index);
}  /* mrp_free_vlan */

static u16 mrp_alloc_fid(struct mrp_info *mrp, u16 vid)
{
	struct ksz_sw *sw = container_of(mrp, struct ksz_sw, mrp);

	return sw->ops->alloc_fid(sw, vid);
}  /* mrp_alloc_fid */

static void mrp_free_fid(struct mrp_info *mrp, u16 fid)
{
	struct ksz_sw *sw = container_of(mrp, struct ksz_sw, mrp);

	sw->ops->free_fid(sw, fid);
}  /* mrp_free_fid */

#ifdef CONFIG_KSZ_MSRP
static u16 mrp_get_fid(struct mrp_info *mrp, u16 vid, u8 *addr)
{
	struct mrp_node *node;
	struct mrp_vlan_info data;
	u16 fid = 0;

	data.vid = vid;
	memcpy(data.addr, addr, ETH_ALEN);
	node = mrp_find_node(&mrp->vlan_list, cmp_vlan, &data);
	if (node) {
		struct mrp_vlan_info *vlan = node->data;

		fid = vlan->fid;
	}
	return fid;
}  /* mrp_get_fid */
#endif

static int proc_mrp_lv(struct mrp_info *mrp, struct mrp_node *node, u16 ports,
	u16 *tx_ports, u8 type)
{
	int p;
	int result = DEV_IOC_OK;

dbg_msg(" %s %x %x\n", __func__, ports, *tx_ports);
	if (!ports) {

		/* Ask all ports to withdraw the declaration. */
		for (p = 0; p <= mrp->ports; p++)
			if (*tx_ports & (1 << p))
				add_attrib_report(mrp, node,
					MRP_ACTION_LV, type, p);
		*tx_ports = 0;

		result = DEV_IOC_MRP_REPORT;
	} else {
		int uninitialized_var(q);
		int cnt = 0;

		for (p = 0; p <= mrp->ports; p++)
			if (ports & (1 << p)) {
				q = p;
				cnt++;
			}
		if (1 == cnt) {
			*tx_ports &= ~(1 << q);
			add_attrib_report(mrp, node, MRP_ACTION_LV, type, q);

			result = DEV_IOC_MRP_REPORT;
		}
	}
	return result;
}  /* proc_mrp_lv */

static int proc_mrp_lv_mac(struct mrp_info *mrp, u8 port,
	struct MRP_mac *mac)
{
	struct mrp_node *node;
	struct mrp_mac_info data;
	struct mrp_mac_info *info;
	u16 mrp_ports;
	u16 ports;
	int result = DEV_IOC_OK;

dbg_msg(" %s p:%d %02x:%02x:%02x:%02x:%02x:%02x\n", __func__, port,
	mac->addr[0],
	mac->addr[1],
	mac->addr[2],
	mac->addr[3],
	mac->addr[4],
	mac->addr[5]);

	data.fid = 0;
	memcpy(data.addr, mac->addr, ETH_ALEN);
	node = mrp_find_node(&mrp->mac_list, cmp_mac, &data);
	if (!node)
		return DEV_IOC_INVALID_CMD;

	info = node->data;
	mrp_ports = info->mrp_ports;
	ports = info->ports;
	info->mrp_ports &= ~(1 << port);
	info->ports = info->mrp_ports | info->srp_ports;

	/* There is no change in port membership. */
	if (mrp_ports == info->mrp_ports)
		return result;
	if (ports != info->ports) {
		mrp_cfg_dest_addr(mrp, info->index, info->addr, info->ports,
			info->fid);
		if (!info->ports) {
			mrp_free_mac(mrp, info->index);
			if (mrp->no_report)
				mrp_delete_node(&mrp->mac_list, cmp_mac, node);
			else
				mrp_remove_node(&mrp->mac_list, cmp_mac, node);
		}
	}
	if (!mrp->no_report)
		result = proc_mrp_lv(mrp, node, info->mrp_ports,
			&info->tx_ports, MRP_TYPE_MAC);
#ifdef DEBUG
	mrp_show_node(&mrp->mac_list, show_mac_info);
#endif
	return result;
}  /* proc_mrp_lv_mac */

static int proc_mrp_rx_mac(struct mrp_info *mrp, u8 port,
	struct MRP_mac *mac)
{
	struct mrp_node *node;
	struct mrp_mac_info *info;
	u16 mrp_ports;
	u16 ports;
	int p;
	int result = DEV_IOC_OK;

dbg_msg(" %s p:%d %02x:%02x:%02x:%02x:%02x:%02x\n", __func__, port,
	mac->addr[0],
	mac->addr[1],
	mac->addr[2],
	mac->addr[3],
	mac->addr[4],
	mac->addr[5]);

	node = mrp_get_mac_info(&mrp->mac_list, mac->addr, 0);
	if (!node)
		return -ENOMEM;
	info = node->data;
	info->srp_ports &= ~SRP_PORT_BLACKLIST;
	info->ports &= ~SRP_PORT_BLACKLIST;
	mrp_ports = info->mrp_ports;
	ports = info->ports;
	info->mrp_ports |= (1 << port);
	info->ports = info->mrp_ports | info->srp_ports;

	/* There is change in port membership. */
	if (mrp_ports != info->mrp_ports) {

		/* First time setting up MAC table. */
		if (!ports) {
			info->index = mrp_alloc_mac(mrp);
			if (!info->index) {
				mrp_delete_node(&mrp->mac_list, cmp_mac, node);
				return -ENOMEM;
			}
		}
		mrp_cfg_dest_addr(mrp, info->index, info->addr, info->ports,
			info->fid);
	}
#ifdef DEBUG
	mrp_show_node(&mrp->mac_list, show_mac_info);
#endif
	if (mrp->no_report)
		return result;

	/* Ask all other ports to declare the attribute. */
	for (p = 0; p <= mrp->ports; p++)
		if (p != port && !(info->tx_ports & (1 << p))) {
			info->tx_ports |= (1 << p);

			add_attrib_report(mrp, node, MRP_ACTION_TX,
				MRP_TYPE_MAC, p);
			result = DEV_IOC_MRP_REPORT;
		}
	return result;
}  /* proc_mrp_rx_mac */

static int proc_mrp_lv_vlan(struct mrp_info *mrp, u8 port,
	struct MRP_vlan *vlan)
{
	struct mrp_node *node;
	struct mrp_vlan_info *info;
	struct mrp_vlan_info data;
	u16 ports;
	int result = DEV_IOC_OK;

dbg_msg(" %s p:%d %d\n", __func__, port, vlan->id);
	data.vid = vlan->id;
	memset(data.addr, 0xff, ETH_ALEN);
	node = mrp_find_node(&mrp->vlan_list, cmp_vlan, &data);
	if (!node)
		return DEV_IOC_INVALID_CMD;

	info = node->data;
	ports = info->ports;
	info->ports &= ~(1 << port);

	/* There is no change in port membership. */
	if (ports == info->ports)
		return result;
	ports = mrp_find_vlan_ports(&mrp->vlan_list, data.vid, NULL, NULL);
	mrp_cfg_vlan(mrp, info->index, info->vid, info->fid, ports);
	if (!ports) {
		mrp_free_fid(mrp, info->fid);
		mrp_free_vlan(mrp, info->index);
	}
	if (!info->ports) {
		if (mrp->no_report)
			mrp_delete_node(&mrp->vlan_list, cmp_vlan, node);
		else
			mrp_remove_node(&mrp->vlan_list, cmp_vlan, node);
	}

	if (!mrp->no_report)
		result = proc_mrp_lv(mrp, node, info->ports,
			&info->tx_ports, MRP_TYPE_VLAN);
#ifdef DEBUG
	mrp_show_node(&mrp->vlan_list, show_vlan_info);
#endif
	return result;
}  /* proc_mrp_lv_vlan */

static int proc_mrp_rx_vlan(struct mrp_info *mrp, u8 port,
	struct MRP_vlan *vlan)
{
	struct mrp_node *node;
	struct mrp_vlan_info *info;
	u16 ports;
	int p;
	int result = DEV_IOC_OK;

dbg_msg(" %s p:%d %d\n", __func__, port, vlan->id);
	node = mrp_get_vlan_info(&mrp->vlan_list, vlan->id, NULL);
	if (!node)
		return -ENOMEM;
	info = node->data;
	ports = info->ports;
	info->ports |= (1 << port);

	/* There is change in port membership. */
	if (ports != info->ports) {
		info->ports |= SRP_PORT_IGNORE;
		ports = mrp_find_vlan_ports(&mrp->vlan_list, vlan->id,
			&info->index, &info->fid);
		info->ports &= ~SRP_PORT_IGNORE;

		/* First time setting up VLAN table. */
		if (!ports) {
			info->index = mrp_alloc_vlan(mrp);
			if (!info->index) {
				mrp_delete_node(&mrp->vlan_list, cmp_vlan,
					node);
				return -ENOMEM;
			}
			info->fid = mrp_alloc_fid(mrp, info->vid);
		}
		ports |= info->ports;
		mrp_cfg_vlan(mrp, info->index, info->vid, info->fid, ports);
	}
#ifdef DEBUG
	mrp_show_node(&mrp->vlan_list, show_vlan_info);
#endif
	if (mrp->no_report)
		return result;

	/* Ask all other ports to declare the attribute. */
	for (p = 0; p <= mrp->ports; p++) {
		if (p != port && !(info->tx_ports & (1 << p))) {
			info->tx_ports |= (1 << p);

			add_attrib_report(mrp, node, MRP_ACTION_TX,
				MRP_TYPE_VLAN, p);
			result = DEV_IOC_MRP_REPORT;
		}
	}
	return result;
}  /* proc_mrp_rx_vlan */

#ifdef CONFIG_KSZ_MSRP
static int proc_mrp_lv_domain(struct mrp_info *mrp, u8 port,
	struct SRP_domain_class *domain)
{
	int result = DEV_IOC_OK;

dbg_msg(" %s %d %d %d %d\n", __func__, port,
	domain->id, domain->priority, domain->vlan_id);
	if (mrp->no_report)
		return result;

	/* Coming from the host. */
	if (port == mrp->ports) {
		for (port = 0; port < mrp->ports; port++)
			add_attrib_report(mrp, NULL, MRP_ACTION_LV,
				MRP_TYPE_DOMAIN, port);
		result = DEV_IOC_MRP_REPORT;
	}
	return result;
}  /* proc_mrp_lv_domain */

static int proc_mrp_rx_domain(struct mrp_info *mrp, u8 port,
	struct SRP_domain_class *domain)
{
	int result = DEV_IOC_OK;

dbg_msg(" %s %d %d %d %d\n", __func__, port,
	domain->id, domain->priority, domain->vlan_id);
	mrp->domain = *domain;
	if (mrp->no_report)
		return result;

	/* Coming from the host. */
	if (port == mrp->ports) {
		for (port = 0; port < mrp->ports; port++)
			add_attrib_report(mrp, NULL, MRP_ACTION_TX,
				MRP_TYPE_DOMAIN, port);
		result = DEV_IOC_MRP_REPORT;
	}
	return result;
}  /* proc_mrp_rx_domain */

static u32 calculate_max_bandwidth(u32 speed, u32 percent)
{
	u64 bandwidth;
	u32 rem;

	bandwidth = speed;
	bandwidth *= percent;
	bandwidth *= NETWORK_SPEED_IN_MBIT;
	bandwidth = div_u64_rem(bandwidth, 100, &rem);
	return (u32) bandwidth;
}  /* calculate_max_bandwidth */

static int srp_update_mac(struct mrp_info *mrp, u8 *addr, u16 fid, u16 ports,
	int up)
{
	struct mrp_node_anchor *list;
	struct mrp_node *node;
	struct mrp_mac_info *mac;
	struct mrp_mac_info *update;

	node = mrp_get_mac_info(&mrp->mac_list, addr, fid);
	if (!node)
		return -ENOMEM;
	mac = node->data;
	mac->srp_ports &= ~SRP_PORT_BLACKLIST;
	if (up) {
		/* Forward in port. */
		mac->srp_ports |= ports;
		ports = mac->srp_ports | mac->mrp_ports;
		list = &mrp->mac_up;
	} else {
		/* Filter in port. */
		mac->srp_ports &= ~ports;
		ports = mac->ports & ~ports;
		list = &mrp->mac_down;
	}
	mac->ports = mac->srp_ports | mac->mrp_ports;
#ifdef DEBUG
	mrp_show_node(&mrp->mac_list, show_mac_info);
#endif
	node = mrp_get_mac_info(list, addr, fid);
	if (!node)
		return -ENOMEM;
	update = node->data;
	update->ports = ports;
	update->index = mac->index;
	return 0;
}  /* srp_update_mac */

static int srp_update_vlan(struct mrp_info *mrp, u16 vid, u8 *addr, u16 ports,
	int up)
{
	struct mrp_node_anchor *list;
	struct mrp_node *node;
	struct mrp_vlan_info *vlan;
	struct mrp_vlan_info *update;

	node = mrp_get_vlan_info(&mrp->vlan_list, vid, addr);
	if (!node)
		return -ENOMEM;
	vlan = node->data;
	if (up) {
		/* Forward in port. */
		vlan->ports |= ports;
		list = &mrp->vlan_up;
	} else {
		/* Filter in port. */
		vlan->ports &= ~ports;
		list = &mrp->vlan_down;
	}
#ifdef DEBUG
	mrp_show_node(&mrp->vlan_list, show_vlan_info);
#endif
	node = mrp_get_vlan_info(list, vid, addr);
	if (!node)
		return -ENOMEM;
	update = node->data;
	update->fid = vlan->fid;
	update->ports = vlan->ports;
	return 0;
}  /* srp_update_vlan */

static int drop_reservation(struct mrp_info *mrp, u8 port,
	struct SRP_reservation *t_reserv, int active)
{
	u64 bandwidth;
	struct mrp_node *prev;
	struct mrp_node *next;
	struct SRP_reservation *reserv;
	struct SRP_stream *stream;
	int tc;
	struct mrp_traffic_info *traffic;
	struct mrp_port_info *info;
	int result = 0;
	struct mrp_node_anchor *list;
	struct srp_stream_info *data;

	info = get_port_info(mrp, port);
	if (active)
		list = &info->active;
	else
		list = &info->passive;
	prev = &list->anchor;
	next = prev->next;
	while (next) {
		data = next->data;
		reserv = data->reserv;

		if (reserv == t_reserv) {
			if (active) {
				u16 fid;

				stream = reserv->stream;
				tc = data->tc;
				bandwidth = calculate_bandwidth(
					stream->MaxFrameSize,
					stream->MaxIntervalFrames,
					frames_per_sec(tc));

				traffic = get_traffic_info(info, tc);
				traffic->bandwidth_left += bandwidth;
				traffic->bandwidth_used -= bandwidth;
				info->bandwidth_left += bandwidth;

				fid = mrp_get_fid(mrp, stream->vlan_id,
					stream->dest);
				result = srp_update_mac(mrp, stream->dest, fid,
					1 << port, false);
				if (!result)
					result = srp_update_vlan(mrp,
						stream->vlan_id, stream->dest,
						1 << port, false);
			}

			/* Remove node from list. */
			prev->next = next->next;
			mrp_free_node(next);
			result = 1;
			break;
		}
		prev = next;
		next = prev->next;
	}
	return result;
}  /* drop_reservation */

static void srp_cfg_mac(struct mrp_info *mrp, struct mrp_node_anchor *list)
{
	struct mrp_node *prev;
	struct mrp_node *next;
	struct mrp_mac_info *mac;

	prev = &list->anchor;
	next = prev->next;
	while (next) {
		prev->next = next->next;

		mac = next->data;
		mrp_cfg_dest_addr(mrp, mac->index, mac->addr, mac->ports,
			mac->fid);

		mrp_free_node(next);

		next = prev->next;
	}
	list->last = &list->anchor;
}  /* srp_cfg_mac */

static void srp_cfg_vlan(struct mrp_info *mrp, struct mrp_node_anchor *list)
{
	struct mrp_node *prev;
	struct mrp_node *next;
	struct mrp_vlan_info *vlan;
	u16 ports;

	prev = &list->anchor;
	next = prev->next;
	while (next) {
		prev->next = next->next;

		vlan = next->data;
		ports = mrp_find_vlan_ports(&mrp->vlan_list, vlan->vid,
			&vlan->index, &vlan->fid);
		mrp_cfg_vlan(mrp, vlan->index, vlan->vid, vlan->fid, ports);

		mrp_free_node(next);

		next = prev->next;
	}
	list->last = &list->anchor;
}  /* srp_cfg_vlan */

static void srp_cfg_reservation(struct mrp_info *mrp)
{
	u8 port;
	int tc;
	struct mrp_port_info *info;
	struct mrp_traffic_info *traffic;

	srp_cfg_mac(mrp, &mrp->mac_down);
	srp_cfg_vlan(mrp, &mrp->vlan_down);
	for (port = 0; port <= mrp->ports; port++) {
		info = get_port_info(mrp, port);
		for (tc = SR_CLASS_A; tc >= SR_CLASS_B; tc--) {
			traffic = get_traffic_info(info, tc);
			if (traffic->bandwidth_used !=
			    traffic->bandwidth_set) {
				srp_cfg_credit_shaper(mrp, port, info,
					traffic);
				traffic->bandwidth_set =
					traffic->bandwidth_used;
				info->bandwidth[traffic->queue].operIdleSlope =
					traffic->bandwidth_set;
			}
		}
	}
	srp_cfg_mac(mrp, &mrp->mac_up);
	srp_cfg_vlan(mrp, &mrp->vlan_up);
}  /* srp_cfg_reservation */

static struct mrp_node *create_stream_info(struct mrp_info *mrp,
	struct SRP_reservation *t_reserv)
{
	struct mrp_node *node;
	struct srp_stream_info *info;

	node = mrp_alloc_node(sizeof(struct srp_stream_info));
	if (!node)
		return NULL;
	info = node->data;
	prepare_stream_info(t_reserv,
		get_traffic_class(mrp, t_reserv->stream->priority), info);
	return node;
}  /* create_stream_info */

static void add_reservation(struct mrp_port_info *info, int active,
	struct mrp_node *node)
{
	struct mrp_node_anchor *list;
	int (*cmp)(void *a, void *b);

	if (active) {
		list = &info->active;
		cmp = cmp_higher_stream;
	} else {
		list = &info->passive;
		cmp = cmp_lower_stream;
	}
	mrp_insert_node(list, cmp, node);
}  /* add_reservation */

static struct SRP_reservation *mrp_link_listener(struct mrp_info *mrp,
	struct mrp_port_info *info, struct SRP_stream *stream)
{
	struct SRP_reservation *reserv;

	/* Create linked listener declaration. */
	reserv = srp_find_reservation(&info->declared, stream->id,
		SRP_LISTENER);
	if (!reserv) {

		/* Listener declaration is not known yet. */
		reserv = srp_create_reservation(stream->id, SRP_LISTENER,
			0, 0, mrp->id, 0);
		if (!reserv)
			return NULL;

		reserv->stream = stream;
		srp_insert_reservation(&info->declared, reserv);
	}
	return reserv;
}  /* mrp_link_listener */

static int mrp_update_listener(struct mrp_info *mrp,
	struct SRP_reservation *l_reserv, struct SRP_stream *stream)
{
	int declaration;
	int i;
	struct SRP_reservation *reserv;
	struct SRP_reservation *t_reserv;
	struct mrp_port_info *info;
	int result = DEV_IOC_OK;

	info = get_port_info(mrp, stream->in_port);
	if (!l_reserv)
		l_reserv = srp_find_reservation(&info->declared, stream->id,
			SRP_LISTENER);
	if (!l_reserv)
dbg_msg("  ! not found\n");
	if (!l_reserv)
		return result;

	declaration = 0;
	for (i = 0; i <= mrp->ports; i++) {
		if (i == stream->in_port)
			continue;
		info = get_port_info(mrp, i);
		reserv = srp_find_reservation(&info->registered,
			stream->id, SRP_LISTENER);
		t_reserv = srp_find_reservation(&info->declared,
			stream->id, SRP_TALKER);
		if (reserv && t_reserv) {
			if (SRP_FAILED == t_reserv->declaration)
				declaration |= SRP_ASKING_FAILED_SCALE;
			else
				declaration |= (1 << reserv->declaration);
		}
	}

	/* No more listeners. */
	if (!declaration) {
		int free = true;

dbg_msg("listener leaving\n");
		if (!mrp->no_report) {
			free = false;
			add_attrib_report(mrp, l_reserv, MRP_ACTION_LV,
				MRP_TYPE_LISTENER, stream->in_port);
			result = DEV_IOC_MRP_REPORT;
		}
		srp_remove_reservation(l_reserv, free);
		return result;
	}

	if (declaration > SRP_READY_SCALE)
		declaration = SRP_READY_FAILED;
	else if (declaration == SRP_READY_SCALE)
		declaration = SRP_READY;
	else
		declaration = SRP_ASKING_FAILED;

	/* Declaration is different. */
	if (declaration != l_reserv->declaration) {
		l_reserv->declaration = declaration;
if (mrp->no_report)
dbg_msg("%s %d %d\n", __func__, stream->in_port, declaration);
		if (!mrp->no_report) {
			add_attrib_report(mrp, l_reserv, MRP_ACTION_TX,
				MRP_TYPE_LISTENER, stream->in_port);

			/* Ask application to retrieve attributes. */
			result = DEV_IOC_MRP_REPORT;
		}
	}
	return result;
}  /* mrp_update_listener */

static int drop_other_reservations(struct mrp_info *mrp, u8 port,
	struct SRP_reservation *t_reserv, u32 required_bandwidth)
{
	u64 bandwidth;
	u64 avail_bandwidth = 0;
	struct mrp_node *prev;
	struct mrp_node *next;
	struct mrp_node *last = NULL;
	struct SRP_reservation *reserv;
	int cmp;
	struct SRP_stream *stream;
	int tc;
	struct mrp_traffic_info *traffic;
	struct mrp_port_info *info;
	struct srp_stream_info b;
	struct srp_stream_info *data;
	int result;

	info = get_port_info(mrp, port);
	prepare_stream_info(t_reserv,
		get_traffic_class(mrp, t_reserv->stream->priority), &b);

	/* Go through the loop first to check if there are enough bandwidth. */
	prev = &info->active.anchor;
	next = prev->next;
	while (next) {
		data = next->data;
		reserv = data->reserv;
		tc = data->tc;

		cmp = cmp_lower_stream(&b, next->data);

		/* stream has higher priority. */
		if (cmp < 0)
			break;
		stream = reserv->stream;
		bandwidth = calculate_bandwidth(stream->MaxFrameSize,
			stream->MaxIntervalFrames, frames_per_sec(tc));
		avail_bandwidth += bandwidth;
		if (avail_bandwidth >= required_bandwidth) {
			last = next;
			break;
		}
		prev = next;
		next = prev->next;
	}

	/* No bandwidth at all for the new stream. */
	if (avail_bandwidth < required_bandwidth)
		return 0;

	prev = &info->active.anchor;
	next = prev->next;
	while (next) {
		u16 fid;

		data = next->data;
		reserv = data->reserv;
		tc = data->tc;

		stream = reserv->stream;
		bandwidth = calculate_bandwidth(stream->MaxFrameSize,
			stream->MaxIntervalFrames, frames_per_sec(tc));

		traffic = get_traffic_info(info, tc);
		traffic->bandwidth_left += bandwidth;
		traffic->bandwidth_used -= bandwidth;

		/* Remove node from list. */
		prev->next = next->next;
		next->next = NULL;

		reserv->declaration = SRP_FAILED;
		reserv->code = RFC_NO_BANDWIDTH;

		reserv->pair->code = RFC_PREEMPTED_BY_RANK;

		fid = mrp_get_fid(mrp, stream->vlan_id, stream->dest);
		result = srp_update_mac(mrp, stream->dest, fid, 1 << port,
			false);
		if (!result)
			result = srp_update_vlan(mrp,
				stream->vlan_id, stream->dest, 1 << port,
					false);

		if (!mrp->no_report)
			add_attrib_report(mrp, reserv, MRP_ACTION_TX,
				MRP_TYPE_TALKER, port);

		mrp_update_listener(mrp, NULL, stream);

		add_reservation(info, false, next);

		/* Enough bandwidth freed. */
		if (next == last)
			break;
		next = prev->next;
	}

	/* Increase bandwidth */
	info->bandwidth_left += avail_bandwidth;
	return 1;
}  /* drop_other_reservations */

static int start_passive_reservation(struct mrp_info *mrp, u8 port)
{
	u64 bandwidth;
	struct mrp_node *prev;
	struct mrp_node *next;
	struct SRP_reservation *reserv;
	struct SRP_stream *stream;
	int tc;
	struct mrp_traffic_info *traffic;
	struct mrp_port_info *info;
	int started = 0;
	int result;
	struct srp_stream_info *data;

	info = get_port_info(mrp, port);
	prev = &info->passive.anchor;
	next = prev->next;
	while (next) {
		data = next->data;
		reserv = data->reserv;

		stream = reserv->stream;
		tc = data->tc;
		traffic = get_traffic_info(info, tc);
		bandwidth = calculate_bandwidth(stream->MaxFrameSize,
			stream->MaxIntervalFrames, frames_per_sec(tc));
		if (bandwidth <= traffic->bandwidth_left) {
			u16 fid;

			traffic->bandwidth_left -= bandwidth;
			traffic->bandwidth_used += bandwidth;
			info->bandwidth_left -= bandwidth;

			reserv->declaration = SRP_ADVERTISE;
			reserv->code = RFC_NO_ERROR;

			reserv->pair->code = RFC_NO_ERROR;

			fid = mrp_get_fid(mrp, stream->vlan_id, stream->dest);
			result = srp_update_mac(mrp, stream->dest, fid,
				1 << port, true);
			if (!result)
				result = srp_update_vlan(mrp, stream->vlan_id,
					stream->dest, 1 << port, true);

			mrp_update_listener(mrp, NULL, stream);

			if (!mrp->no_report) {
				add_attrib_report(mrp, reserv, MRP_ACTION_TX,
					MRP_TYPE_TALKER, port);
				started = 1;
			}

			/* Remove node from list. */
			prev->next = next->next;
			next->next = NULL;

			add_reservation(info, true, next);

			next = prev;
		}
		prev = next;
		next = prev->next;
	}
	return started;
}  /* start_passive_reservation */

static void mrp_combine_list(struct mrp_node_anchor *old_list,
	struct mrp_node_anchor *new_list)
{
	struct mrp_node *prev;
	struct mrp_node *next;

	prev = &old_list->anchor;
	next = prev->next;
	while (next) {

		/* Remove node from list. */
		prev->next = next->next;
		next->next = NULL;
		mrp_insert_node(new_list, cmp_higher_stream, next);
		next = prev->next;
	}
}  /* mrp_combine_list */

static void update_reservation(struct mrp_info *mrp, u8 port)
{
	struct mrp_node *prev;
	struct mrp_node *next;
	struct SRP_reservation *reserv;
	struct SRP_reservation *l_reserv;
	struct SRP_reservation *t_reserv;
	struct SRP_stream *stream;
	int tc;
	u8 code;
	u8 declaration;
	u16 fid;
	u32 bandwidth;
	struct mrp_traffic_info *traffic;
	struct mrp_port_info *info;
	struct srp_stream_info *data;
	struct mrp_node_anchor list;
#ifdef DEBUG
	char bw_used[20];
#endif

	info = get_port_info(mrp, port);
	mrp_init_list(&list);
	mrp_combine_list(&info->active, &list);
	mrp_combine_list(&info->passive, &list);
	mrp_show_node(&list, show_stream_info);

	/* Reset bandwidth used. */
	for (tc = SR_CLASS_A; tc >= SR_CLASS_B; tc--) {
		traffic = get_traffic_info(info, tc);
		traffic->bandwidth_used = 0;

		/* Make sure credit settings will be updated. */
		if (traffic->bandwidth_set)
			traffic->bandwidth_set = 1;
		traffic->max_frame_size = 0;
	}
	prev = &list.anchor;
	next = prev->next;
	while (next) {

		/* Remove node from list. */
		prev->next = next->next;
		next->next = NULL;
		data = next->data;
		reserv = data->reserv;
		l_reserv = reserv->pair;

		stream = reserv->stream;
		t_reserv = stream->t_reserv;

		/* Listener or talker is not ready. */
		if (SRP_ASKING_FAILED == l_reserv->declaration ||
		    SRP_FAILED == t_reserv->declaration) {
			add_reservation(info, false, next);
			next = prev->next;
			continue;
		}

		tc = data->tc;
		traffic = get_traffic_info(info, tc);
		bandwidth = calculate_bandwidth(stream->MaxFrameSize,
			stream->MaxIntervalFrames, frames_per_sec(tc));

		/* Assume reservation has no problem. */
		code = reserv->code;
		declaration = reserv->declaration;
dbg_msg("%d c:%d d:%d\n", port, reserv->code, reserv->declaration);
dbg_msg("l c:%d d:%d\n", l_reserv->code, l_reserv->declaration);
dbg_msg("t c:%d d:%d\n", t_reserv->code, t_reserv->declaration);
		code = RFC_NO_ERROR;
		if (bandwidth > traffic->bandwidth_left) {
			code = RFC_NO_BANDWIDTH_FOR_TRAFFIC_CLASS;
		} else if (bandwidth > info->bandwidth_left) {
			code = RFC_NO_BANDWIDTH;
		}

		fid = mrp_get_fid(mrp, stream->vlan_id, stream->dest);
		if (RFC_NO_ERROR == code) {

			/* Reduce bandwidth */
			info->bandwidth_left -= bandwidth;
			traffic->bandwidth_left -= bandwidth;
			traffic->bandwidth_used += bandwidth;
			if (stream->MaxFrameSize > traffic->max_frame_size)
				traffic->max_frame_size = stream->MaxFrameSize;
			srp_update_mac(mrp, stream->dest, fid, 1 << port,
				true);
			srp_update_vlan(mrp, stream->vlan_id, stream->dest,
				1 << port, true);
			add_reservation(info, true, next);
			declaration = SRP_ADVERTISE;
		} else {
			srp_update_mac(mrp, stream->dest, fid, 1 << port,
				false);
			srp_update_vlan(mrp, stream->vlan_id, stream->dest,
				1 << port, false);
			add_reservation(info, false, next);
			declaration = SRP_FAILED;
		}
		if (declaration != reserv->declaration ||
		    code != reserv->code) {
dbg_msg("changed: %d:%d %d:%d\n", declaration, reserv->declaration,
code, reserv->code);
			reserv->declaration = declaration;
			reserv->code = code;
			if (!mrp->no_report)
				add_attrib_report(mrp, reserv, MRP_ACTION_TX,
					MRP_TYPE_TALKER, port);

			mrp_update_listener(mrp, NULL, stream);
		}
		next = prev->next;
	}

#ifdef DEBUG
dbg_msg("  active:\n");
	mrp_show_node(&info->active, show_stream_info);
dbg_msg("  passive:\n");
	mrp_show_node(&info->passive, show_stream_info);
	for (tc = SR_CLASS_A; tc >= SR_CLASS_B; tc--) {
		traffic = get_traffic_info(info, tc);
		format_num(bw_used, traffic->bandwidth_used);
dbg_msg("%d: %s\n", tc, bw_used);
	}
#endif

	srp_cfg_reservation(mrp);
}  /* update_reservation */

static int check_avail_bandwidth(struct mrp_info *mrp, u8 port,
	struct SRP_stream *stream, struct SRP_reservation *t_reserv)
{
	u64 bandwidth;
	int tc;
	struct mrp_traffic_info *traffic;
	struct mrp_port_info *info;
	int result;
	char bw_max[20];
	char bw_left[20];
	char tbw_max[20];
	char tbw_left[20];

	info = get_port_info(mrp, port);
	tc = get_traffic_class(mrp, stream->priority);
	traffic = get_traffic_info(info, tc);
	bandwidth = calculate_bandwidth(stream->MaxFrameSize,
		stream->MaxIntervalFrames, frames_per_sec(tc));
	format_num(bw_max, info->bandwidth_max);
	format_num(bw_left, info->bandwidth_left);
	format_num(tbw_max, traffic->bandwidth_max);
	format_num(tbw_left, traffic->bandwidth_left);
dbg_msg("bw:%u %16llu %s %s\n", port, bandwidth, bw_left, tbw_left);

	if (bandwidth > traffic->bandwidth_left) {
		t_reserv->code = RFC_NO_BANDWIDTH_FOR_TRAFFIC_CLASS;
dbg_msg("tc %llu %s\n", bandwidth, tbw_max);

		/* See if this stream has higher rank. */
		if (bandwidth <= traffic->bandwidth_max) {
dbg_msg("higher rank\n");
			if (drop_other_reservations(mrp, port, t_reserv,
					bandwidth))
				t_reserv->code = RFC_NO_ERROR;
		}
	} else if (bandwidth > info->bandwidth_left) {
		t_reserv->code = RFC_NO_BANDWIDTH;
dbg_msg("port %llu %s\n", bandwidth, bw_max);

		/* See if the lower SR class has used all of the bandwidth. */
		if (bandwidth <= info->bandwidth_max) {
dbg_msg("higher SR class\n");
			if (drop_other_reservations(mrp, port, t_reserv,
					bandwidth))
				t_reserv->code = RFC_NO_ERROR;
		}
	}

	if (RFC_NO_ERROR == t_reserv->code) {
		struct mrp_node *active;
		u16 fid;
		u16 ports = 1 << port;

		/* Reduce bandwidth */
		info->bandwidth_left -= bandwidth;
		traffic->bandwidth_left -= bandwidth;
		traffic->bandwidth_used += bandwidth;
		if (stream->MaxFrameSize > traffic->max_frame_size)
			traffic->max_frame_size = stream->MaxFrameSize;

		active = create_stream_info(mrp, t_reserv);
		if (!active)
			return SRP_ASKING_FAILED;

		add_reservation(info, true, active);

		fid = mrp_get_fid(mrp, stream->vlan_id, stream->dest);
		result = srp_update_mac(mrp, stream->dest, fid, ports, true);
		if (result)
			return SRP_ASKING_FAILED;
		result = srp_update_vlan(mrp,
			stream->vlan_id, stream->dest, ports, true);
		return SRP_READY;
	} else {
		struct mrp_node *passive;

		t_reserv->declaration = SRP_FAILED;
dbg_msg("no bw: %d\n", t_reserv->code);
		if (!mrp->no_report)
			add_attrib_report(mrp, t_reserv, MRP_ACTION_TX,
				MRP_TYPE_TALKER, port);
		passive = create_stream_info(mrp, t_reserv);
		if (passive)
			add_reservation(info, false, passive);
	}
	return SRP_ASKING_FAILED;
}  /* check_avail_bandwidth */

static int proc_mrp_tx_listener(struct mrp_info *mrp, u8 port,
	struct SRP_reservation *l_reserv, struct SRP_reservation *t_reserv,
	struct SRP_stream *stream)
{
	struct SRP_reservation *reserv;
	int result = DEV_IOC_OK;
	int started = 0;
	struct mrp_port_info *info;
	u8 declaration = l_reserv->declaration;

	info = get_port_info(mrp, port);

	/* Talker is not ready. */
	if (SRP_FAILED == stream->t_reserv->declaration) {
		declaration = SRP_ASKING_FAILED;
	} else {

		/* Find talker reservation if already created. */
		if (!t_reserv)
			t_reserv = srp_find_reservation(&info->declared,
				l_reserv->id, SRP_TALKER);
		if (!t_reserv)
			declaration = SRP_ASKING_FAILED;
		else {
			if (SRP_FAILED == t_reserv->declaration)
				declaration = SRP_ASKING_FAILED;
			if (!t_reserv->pair) {
				t_reserv->pair = l_reserv;
				l_reserv->pair = t_reserv;
			}
		}
	}

	/* Check available bandwidth. */
	if (declaration != SRP_ASKING_FAILED) {

		/* Actual reservation is not made yet. */
		if (RFC_NO_BANDWIDTH == l_reserv->code) {
			declaration = check_avail_bandwidth(mrp, port, stream,
				t_reserv);
			if (declaration != SRP_ASKING_FAILED) {
				l_reserv->code = RFC_NO_ERROR;
				srp_cfg_reservation(mrp);
			}
		}
	} else if (RFC_NO_BANDWIDTH != l_reserv->code) {

		/* Listener is no longer ready to receive stream. */
		if (!drop_reservation(mrp, port, t_reserv, true))
			drop_reservation(mrp, port, t_reserv, false);

		/* Used to indicate reservation is not done yet. */
		l_reserv->code = RFC_NO_BANDWIDTH;
		started = start_passive_reservation(mrp, port);
		srp_cfg_reservation(mrp);
	}

	info = get_port_info(mrp, stream->in_port);
	reserv = srp_find_reservation(&info->declared, l_reserv->id,
		SRP_LISTENER);

	/* Used to find out whether to send declaration back to talker. */
	mrp->listeners++;

	if (started)
		result = DEV_IOC_MRP_REPORT;
	return result;
}  /* proc_mrp_tx_listener */

static int proc_mrp_lv_listener(struct mrp_info *mrp, u8 port,
	struct SRP_listener *listener)
{
	struct SRP_reservation *l_reserv;
	struct SRP_reservation *t_reserv;
	struct mrp_port_info *info;
	int declaration;
	int result = DEV_IOC_OK;
	int started = 0;

	info = get_port_info(mrp, port);
dbg_msg(" %s p:%d %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x s:%u\n", __func__,
port,
listener->id[0],
listener->id[1],
listener->id[2],
listener->id[3],
listener->id[4],
listener->id[5],
listener->id[6],
listener->id[7],
listener->substate);
	l_reserv = srp_find_reservation(&info->registered, listener->id,
		SRP_LISTENER);
	if (!l_reserv)
dbg_msg("  ! not found\n");
	if (!l_reserv)
		return result;

	/* Check if a talker reservation is using bandwidth. */
	t_reserv = srp_find_reservation(&info->declared, listener->id,
		SRP_TALKER);
	if (!t_reserv) {

		/* Delete listener reservation when leaving. */
		srp_remove_reservation(l_reserv, true);
		return result;
	}

	/* Remember the listener state. */
	declaration = l_reserv->declaration;

	t_reserv->pair = NULL;

	/* Delete listener reservation when leaving. */
	srp_remove_reservation(l_reserv, true);

	/* Update the listener attribute reported back to talker. */
	result = mrp_update_listener(mrp, NULL, t_reserv->stream);

	/* Listener reservation is not using bandwidth if not ready. */
	if (declaration != SRP_ASKING_FAILED) {
		if (t_reserv->declaration != SRP_ADVERTISE) {

			/* Look in passive list for reservation. */
			if (drop_reservation(mrp, port, t_reserv, false)) {
dbg_msg(" reset advert\n");
				if (!mrp->no_report) {
					t_reserv->declaration = SRP_ADVERTISE;
					t_reserv->code = RFC_NO_ERROR;
					add_attrib_report(mrp, t_reserv,
						MRP_ACTION_TX,
						MRP_TYPE_TALKER, port);
				}
			}
		} else if (!drop_reservation(mrp, port, t_reserv, true))
			drop_reservation(mrp, port, t_reserv, false);

		started = start_passive_reservation(mrp, port);
		srp_cfg_reservation(mrp);
	}

	if (DEV_IOC_OK == result && started)
		result = DEV_IOC_MRP_REPORT;
	return result;
}  /* proc_mrp_lv_listener */

static int proc_mrp_rx_listener(struct mrp_info *mrp, u8 port,
	struct SRP_listener *listener)
{
	int result = DEV_IOC_OK;
	u8 declaration = SRP_READY;
	struct SRP_reservation *l_reserv;
	struct SRP_stream *stream;
	struct mrp_port_info *info;

	info = get_port_info(mrp, port);
dbg_msg(" %s p:%d %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x s:%u\n", __func__,
port,
listener->id[0],
listener->id[1],
listener->id[2],
listener->id[3],
listener->id[4],
listener->id[5],
listener->id[6],
listener->id[7],
listener->substate);
	if (SRP_IGNORED == listener->substate)
		return DEV_IOC_INVALID_CMD;

	declaration = listener->substate;
	stream = srp_find_stream_id(mrp, listener->id);

	/* Create reservation if new. */
	l_reserv = srp_find_reservation(&info->registered, listener->id,
		SRP_LISTENER);
	if (!l_reserv) {
		struct timespec ts;

		l_reserv = srp_create_reservation(listener->id, SRP_LISTENER,
			declaration, 0, mrp->id, RFC_NO_BANDWIDTH);
		if (!l_reserv)
			return -ENOMEM;

		ts = ktime_to_timespec(ktime_get_real());
		l_reserv->streamAge = ts.tv_sec;
		srp_insert_reservation(&info->registered, l_reserv);
	} else {
		l_reserv->declaration = declaration;
	}

	/* Stream may not exist yet when listener is received. */
	l_reserv->stream = stream;

	/* There is a talker. */
	if (stream && stream->t_reserv && stream->in_port != port) {
		int rc;
		struct SRP_reservation *reserv;

		mrp->listeners = 0;
		result = proc_mrp_tx_listener(mrp, port, l_reserv, NULL,
			stream);

		/* Likely due to errors. */
		if (!mrp->listeners)
			return result;

		info = get_port_info(mrp, stream->in_port);
		reserv = mrp_link_listener(mrp, info, stream);
		if (!reserv)
			return -ENOMEM;

		/* Listener declaration will be updated in following call. */
		rc = mrp_update_listener(mrp, reserv, stream);
		if (DEV_IOC_OK != rc)
			result = rc;
	}
	return result;
}  /* proc_mrp_rx_listener */

static int proc_mrp_tx_talker(struct mrp_info *mrp, u8 port,
	struct SRP_talker *talker)
{
	u8 declaration;
	u64 bandwidth;
	int tc;
	struct mrp_traffic_info *traffic;
	struct ksz_port_cfg *cfg;
	u8 code = talker->FailureCode;
	u32 latency = talker->AccumulatedLatency;
	struct SRP_stream *stream_id = NULL;
	struct SRP_stream *stream_dest;
	struct SRP_reservation *t_reserv;
	struct SRP_reservation *l_reserv;
	struct mrp_port_info *info;
	int result = DEV_IOC_OK;
	char bw_max[20];
	char tbw_max[20];
	struct ksz_sw *sw = container_of(mrp, struct ksz_sw, mrp);

	cfg = &sw->info->port_cfg[port];
	info = get_port_info(mrp, port);
dbg_msg(" %s p:%d %u\n", __func__, port, info->bandwidth_max);
	stream_id = srp_find_stream_id(mrp, talker->id);
	if (code != RFC_NO_ERROR)
		goto get_talker_done;

	tc = get_traffic_class(mrp, talker->priority);
	if (port > mrp->ports)
		code = RFC_PORT_IS_NOT_AVB;
	else if (talker->MaxFrameSize > mrp->max_interference_size)
		code = RFC_MAXFRAMESIZE_TOO_LARGE;
	else if (!tc)
		code = RFC_PRIORITY_IS_NOT_SR_CLASS;
	if (code)
		goto get_talker_done;

	traffic = get_traffic_info(info, tc);
	stream_dest = srp_find_dest_addr(mrp, talker->dest);
	if (stream_id && !stream_dest)
		code = RFC_STREAM_ID_USED;
	else if (stream_dest && !stream_id)
		code = RFC_DEST_ADDR_USED;
	if (code)
		goto get_talker_done;

	bandwidth = calculate_bandwidth(talker->MaxFrameSize,
		talker->MaxIntervalFrames, frames_per_sec(tc));
	format_num(bw_max, info->bandwidth_max);
	format_num(tbw_max, traffic->bandwidth_max);
dbg_msg(" t bw: %llu %s %s\n", bandwidth, bw_max, tbw_max);
	if (bandwidth > traffic->bandwidth_max)
		code = RFC_NO_BANDWIDTH_FOR_TRAFFIC_CLASS;
	else if (bandwidth > info->bandwidth_max)
		code = RFC_NO_BANDWIDTH;

get_talker_done:
if (code)
dbg_msg(" code: %d\n", code);

	/* Create reservation if new. */
	t_reserv = srp_find_reservation(&info->declared, talker->id,
		SRP_TALKER);
	declaration = code ? SRP_FAILED : SRP_ADVERTISE;
	if (!t_reserv) {
		struct timespec ts;

		t_reserv = srp_create_reservation(talker->id, SRP_TALKER,
			declaration, latency, mrp->id, code);
		if (!t_reserv)
			return -ENOMEM;

		ts = ktime_to_timespec(ktime_get_real());
		t_reserv->streamAge = ts.tv_sec;
		t_reserv->stream = stream_id;
		srp_insert_reservation(&info->declared, t_reserv);
	} else {
		t_reserv->declaration = declaration;
		t_reserv->latency = latency;
		memcpy(t_reserv->bridge_id, mrp->id, 8);
		t_reserv->code = code;
	}
	if (!mrp->no_report) {
		add_attrib_report(mrp, t_reserv, MRP_ACTION_TX,
			MRP_TYPE_TALKER, port);
		result = DEV_IOC_MRP_REPORT;
	}

	l_reserv = srp_find_reservation(&info->registered, talker->id,
		SRP_LISTENER);
	if (l_reserv) {
		int rc;

		rc = proc_mrp_tx_listener(mrp, port, l_reserv, t_reserv,
			t_reserv->stream);
	}

	/* Ask application to retrieve attributes. */
	return result;
}  /* proc_mrp_tx_talker */

static int proc_mrp_lv_talker(struct mrp_info *mrp, u8 port,
	struct SRP_talker *talker)
{
	struct SRP_reservation *l_reserv;
	struct SRP_reservation *reserv;
	struct SRP_reservation *t_reserv;
	struct mrp_port_info *info;
	int result = DEV_IOC_OK;
	int p;
	struct mrp_node *mac_node;
	struct mrp_node *vlan_node;
	struct mrp_vlan_info data;
	struct mrp_mac_info mac_data;
	u16 fid = 0;
	int free = true;

	info = get_port_info(mrp, port);
dbg_msg(" %s p:%d %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\n", __func__,
port,
talker->id[0],
talker->id[1],
talker->id[2],
talker->id[3],
talker->id[4],
talker->id[5],
talker->id[6],
talker->id[7]);
	reserv = srp_find_reservation(&info->registered, talker->id,
		SRP_TALKER);
	if (!reserv)
		return result;

	/* No listener propagation if no talker. */
	l_reserv = srp_find_reservation(&info->declared, talker->id,
		SRP_LISTENER);
	if (l_reserv)
		srp_remove_reservation(l_reserv, true);

	for (p = 0; p <= mrp->ports; p++) {
		if (p == port)
			continue;

		info = get_port_info(mrp, p);
		t_reserv = srp_find_reservation(&info->declared, talker->id,
			SRP_TALKER);
		if (!t_reserv)
{
dbg_msg("  no talker reserv: %d\n", p);
			continue;
}

		/* Unlink listener from talker. */
		l_reserv = srp_find_reservation(&info->registered, talker->id,
			SRP_LISTENER);
		if (l_reserv) {
			l_reserv->pair = NULL;

			/* Drop reservation if listener is ready. */
			if (l_reserv->declaration != SRP_ASKING_FAILED) {
				drop_reservation(mrp, p, t_reserv, true);
if (l_reserv->code != RFC_NO_ERROR)
dbg_msg(" not ok? %d\n", l_reserv->code);
				l_reserv->code = RFC_NO_BANDWIDTH;
				start_passive_reservation(mrp, p);
			} else
				drop_reservation(mrp, p, t_reserv, false);
		}

		/* Reservation will be freed after reporting leaving. */
		if (!mrp->no_report) {
			free = false;
			add_attrib_report(mrp, t_reserv, MRP_ACTION_LV,
				MRP_TYPE_TALKER, p);
			result = DEV_IOC_MRP_REPORT;
		}
		srp_remove_reservation(t_reserv, free);
	}

	srp_cfg_reservation(mrp);

	/* This is purely used to free the stream after reporting. */
	if (!mrp->no_report) {
		free = false;
		add_attrib_report(mrp, reserv, MRP_ACTION_LV, MRP_TYPE_TALKER,
			mrp->ports + 1);
	}
	srp_remove_stream(reserv->stream, free);
	srp_remove_reservation(reserv, free);

	data.vid = talker->vlan_id;
	memcpy(data.addr, talker->dest, ETH_ALEN);
	vlan_node = mrp_find_node(&mrp->vlan_list, cmp_vlan, &data);
	if (vlan_node) {
		u16 ports;
		struct mrp_vlan_info *vlan = NULL;

#ifdef DEBUG
		mrp_show_node(&mrp->vlan_list, show_vlan_info);
#endif
		vlan = vlan_node->data;
		fid = vlan->fid;
		vlan->ports &= SRP_PORT_AVAIL;
		ports = mrp_find_vlan_ports(&mrp->vlan_list, data.vid, NULL,
			NULL);
		mrp_cfg_vlan(mrp, vlan->index, vlan->vid, vlan->fid, ports);
		if (!ports) {
			mrp_free_fid(mrp, vlan->fid);
			mrp_free_vlan(mrp, vlan->index);
		}

		/* Nobody is using the VLAN. */
		if (!vlan->ports)
			mrp_delete_node(&mrp->vlan_list, cmp_vlan, vlan_node);
	}
	mac_data.fid = fid;
	memcpy(mac_data.addr, talker->dest, ETH_ALEN);
	mac_node = mrp_find_node(&mrp->mac_list, cmp_mac, &mac_data);
	if (mac_node) {
		struct mrp_mac_info *mac = NULL;

#ifdef DEBUG
		mrp_show_node(&mrp->mac_list, show_mac_info);
#endif
		mac = mac_node->data;
		mac->srp_ports &= SRP_PORT_AVAIL;
		mac->ports = mac->srp_ports | mac->mrp_ports;
		mrp_cfg_dest_addr(mrp, mac->index, mac->addr, mac->ports,
			mac->fid);
		if (!mac->ports) {
			mrp_free_mac(mrp, mac->index);
			mrp_delete_node(&mrp->mac_list, cmp_mac, mac_node);
		}
	}
	return result;
}  /* proc_mrp_lv_talker */

static int proc_mrp_rx_talker(struct mrp_info *mrp, u8 port,
	struct SRP_talker *talker)
{
	int i;
	int result = DEV_IOC_OK;
	u8 declaration;
	struct SRP_reservation *reserv;
	struct SRP_stream *stream;
	struct mrp_port_info *info;

	info = get_port_info(mrp, port);
dbg_msg(" %s p:%d %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\n", __func__,
port,
talker->id[0],
talker->id[1],
talker->id[2],
talker->id[3],
talker->id[4],
talker->id[5],
talker->id[6],
talker->id[7]);
dbg_msg("  %02x:%02x:%02x:%02x:%02x:%02x %03x %u:%u f:%u i:%u l:%u c:%u\n",
talker->dest[0],
talker->dest[1],
talker->dest[2],
talker->dest[3],
talker->dest[4],
talker->dest[5],
talker->vlan_id, talker->priority, talker->rank,
talker->MaxFrameSize, talker->MaxIntervalFrames, talker->AccumulatedLatency,
talker->FailureCode);

	/* Create stream if new. */
	stream = srp_find_stream_id(mrp, talker->id);
	if (!stream) {
		stream = srp_create_stream(talker->id, talker->dest,
			talker->vlan_id, talker->MaxFrameSize,
			talker->MaxIntervalFrames, talker->priority,
			talker->rank);
		if (stream) {
			srp_insert_stream_by_id(mrp, stream);
			srp_insert_stream_by_dest(mrp, stream);
		}
	} else if (!memcmp(stream->dest, talker->dest, ETH_ALEN)) {
		stream->vlan_id = talker->vlan_id;
		stream->MaxFrameSize = talker->MaxFrameSize;
		stream->MaxIntervalFrames = talker->MaxIntervalFrames;
		stream->priority = talker->priority;
		stream->rank = talker->rank;
	} else
		stream = NULL;
	if (!stream)
		return -ENOMEM;

	/* Create reservation if new. */
	reserv = srp_find_reservation(&info->registered, talker->id,
		SRP_TALKER);
	declaration = talker->FailureCode ? SRP_FAILED : SRP_ADVERTISE;
	if (!reserv) {
		struct mrp_node *node;
		struct mrp_mac_info *mac;
		struct mrp_vlan_info *vlan;
		u8 index;
		u16 fid;
		u16 ports = 1 << port;

		reserv = srp_create_reservation(talker->id, SRP_TALKER,
			declaration, talker->AccumulatedLatency,
			talker->bridge_id, talker->FailureCode);
		if (!reserv)
			return -ENOMEM;

		/* Indicate registration source. */
		reserv->streamAge = 0;
		srp_insert_reservation(&info->registered, reserv);
		stream->in_port = port;
		stream->t_reserv = reserv;

		/* Setup initial VLAN configuration. */
		ports = mrp_find_vlan_ports(&mrp->vlan_list, talker->vlan_id,
			&index, &fid);
		node = mrp_get_vlan_info(&mrp->vlan_list, talker->vlan_id,
			talker->dest);
		if (!node)
			return -ENOMEM;
		vlan = node->data;
		vlan->ports = SRP_PORT_READY;

		/* First time setting up VLAN table. */
		if (!ports) {
			vlan->index = mrp_alloc_vlan(mrp);
			vlan->fid = mrp_alloc_fid(mrp, vlan->vid);
			mrp_cfg_vlan(mrp, vlan->index, vlan->vid, vlan->fid,
				vlan->ports);
		} else {
			vlan->index = index;
			vlan->fid = fid;
		}

		/* Setup initial MAC configuration. */
		node = mrp_get_mac_info(&mrp->mac_list, talker->dest,
			vlan->fid);
		if (!node)
			return -ENOMEM;
		mac = node->data;
		ports = mac->ports;
		mac->srp_ports = SRP_PORT_READY;
		mac->ports = mac->mrp_ports | mac->srp_ports;

		/* First time setting up MAC table. */
		if (!ports) {
			mac->index = mrp_alloc_mac(mrp);
			mrp_cfg_dest_addr(mrp, mac->index, mac->addr,
				mac->ports, mac->fid);
		}
#ifdef DEBUG
		mrp_show_node(&mrp->mac_list, show_mac_info);
		mrp_show_node(&mrp->vlan_list, show_vlan_info);
#endif
	} else {
		reserv->declaration = declaration;
		reserv->latency = talker->AccumulatedLatency;
		memcpy(reserv->bridge_id, talker->bridge_id, 8);
		reserv->code = talker->FailureCode;
	}
	reserv->stream = stream;

	mrp->listeners = 0;
	for (i = 0; i <= mrp->ports; i++) {
		if (i == port)
			continue;
		result = proc_mrp_tx_talker(mrp, i, talker);
		if (result < 0)
			return result;
	}

	/* There are no listeners. */
	if (!mrp->listeners)
		return result;

	reserv = mrp_link_listener(mrp, info, stream);
	if (!reserv)
		return -ENOMEM;

	/* Listener declaration will be updated in following call. */
	result = mrp_update_listener(mrp, reserv, stream);
	return result;
}  /* proc_mrp_rx_talker */
#endif

static int proc_mrp_get_tx(struct mrp_info *mrp, int start,
	struct mrp_cfg_options *cmd, int *output)
{
	struct mrp_report *attrib;

#ifdef CONFIG_KSZ_MSRP
	struct SRP_reservation *reserv;
	struct SRP_stream *stream;
#endif
	int result = DEV_IOC_MRP_REPORT;

	attrib = mrp->report_head;
	if (!attrib)
		return DEV_IOC_INVALID_CMD;

	*output = 0;
	cmd->action = attrib->action;
	cmd->type = attrib->type;
	cmd->port = attrib->port + 1;
	if (MRP_TYPE_MAC == attrib->type) {
		struct MRP_mac *mac = &cmd->data.mac;
		struct mrp_node *node = attrib->attrib;
		struct mrp_mac_info *info = node->data;

		memcpy(mac->addr, info->addr, ETH_ALEN);
		*output = SIZEOF_MRP_mac;
		if (MRP_ACTION_LV == attrib->action &&
		    attrib->port == mrp->ports &&
		    !info->ports) {
			mrp_free_node(node);
		}
	} else if (MRP_TYPE_VLAN == attrib->type) {
		struct MRP_vlan *vlan = &cmd->data.vlan;
		struct mrp_node *node = attrib->attrib;
		struct mrp_vlan_info *info = node->data;

		vlan->id = info->vid;
		*output = SIZEOF_MRP_vlan;
		if (MRP_ACTION_LV == attrib->action &&
		    attrib->port == mrp->ports &&
		    !info->ports) {
			mrp_free_node(node);
		}

#ifdef CONFIG_KSZ_MSRP
	} else if (MRP_TYPE_DOMAIN == attrib->type) {
		struct SRP_domain_class *domain = &cmd->data.domain;

		*domain = mrp->domain;
		*output = SIZEOF_SRP_domain_class;
	} else if (MRP_TYPE_LISTENER == attrib->type ||
		   MRP_TYPE_TALKER == attrib->type) {
		reserv = attrib->attrib;
		if (SRP_TALKER == reserv->direction) {
			struct SRP_talker *talker = &cmd->data.talker;

			stream = reserv->stream;
			memcpy(talker->id, stream->id, 8);
			memcpy(talker->dest, stream->dest, ETH_ALEN);
			talker->vlan_id = stream->vlan_id;
			talker->MaxFrameSize = stream->MaxFrameSize;
			talker->MaxIntervalFrames = stream->MaxIntervalFrames;
			talker->priority = stream->priority;
			talker->rank = stream->rank;
			talker->reserved = 0;
			talker->AccumulatedLatency = reserv->latency;
			memcpy(talker->bridge_id, reserv->bridge_id, 8);
			talker->FailureCode = reserv->code;
			*output = SIZEOF_SRP_talker;
		} else {
			memcpy(cmd->data.listener.id, reserv->id, 8);
			cmd->data.listener.substate = reserv->declaration;
			*output = SIZEOF_SRP_listener;
		}

		/* Did receive Leave indication. */
		if (MRP_ACTION_LV == attrib->action) {
			struct mrp_report *next = attrib->next;

#ifdef DEBUG_MRP_MEM
dbg_msg(" r %s %p\n", __func__, reserv);
#endif
			kfree(reserv);

			/* Special one to free the stream. */
			if (next && next->port == mrp->ports + 1) {
				reserv = next->attrib;
#ifdef DEBUG_MRP_MEM
dbg_msg(" s %s %p\n", __func__, reserv->stream);
dbg_msg(" r2 %s %p\n", __func__, reserv);
#endif
				kfree(reserv->stream);
				kfree(reserv);

#ifdef DEBUG_MRP_MEM
dbg_msg(" 1 %s %p\n", __func__, attrib);
#endif
				kfree(attrib);
				attrib = next;
			}
		}
#endif
	}

	/* Assume there are more attributes to report. */
	mrp->report_head = attrib->next;
	if (mrp->report_tail == attrib) {
		mrp->report_tail = NULL;
		result = DEV_IOC_OK;
	}
#ifdef DEBUG_MRP_MEM
dbg_msg(" %s %p\n", __func__, attrib);
#endif
	kfree(attrib);
	return result;
}  /* proc_mrp_get_tx */

static int proc_mrp_get_attribute(struct mrp_info *mrp, int start, u8 *data,
	int *output)
{
	struct mrp_cfg_options *cmd = (struct mrp_cfg_options *) data;
	int result = DEV_IOC_OK;

	switch (cmd->type) {
	case MRP_TYPE_UNKNOWN:
		result = proc_mrp_get_tx(mrp, start, cmd, output);
		break;
	case MRP_TYPE_MAC:
		break;
	case MRP_TYPE_VLAN:
		break;

#ifdef CONFIG_KSZ_MSRP
	case MRP_TYPE_DOMAIN:
		break;
	case MRP_TYPE_LISTENER:
		break;
	case MRP_TYPE_TALKER:
		break;
#endif
	}
	return result;
}  /* proc_mrp_get_attribute */

#ifdef CONFIG_KSZ_MSRP
static int mrp_set_bandwidth(struct mrp_port_info *info)
{
	int q0;
	int q1;
	int tc;
	u32 bandwidth;
	u32 bandwidth_left;
	struct mrp_traffic_info *traffic;
	int check = false;

	q0 = info->traffic[0].queue;
	q1 = info->traffic[1].queue;
	bandwidth = calculate_max_bandwidth(info->speed,
		info->bandwidth[q0].deltaBandwidth +
		info->bandwidth[q1].deltaBandwidth);

	/* The link speed is changed. */
	if (bandwidth != info->bandwidth_max) {

		/* Bandwidth is being used. */
		if (info->bandwidth_left != info->bandwidth_max ||
		    info->passive.anchor.next)
			check = true;
		info->bandwidth_max = bandwidth;
		info->bandwidth_left = bandwidth;
	}

	bandwidth_left = 0;
	for (tc = SR_CLASS_A; tc >= SR_CLASS_B; tc--) {
		traffic = get_traffic_info(info, tc);
		bandwidth = calculate_max_bandwidth(info->speed,
			info->bandwidth[traffic->queue].deltaBandwidth);
		bandwidth += bandwidth_left;
		traffic->bandwidth_max = bandwidth;
		traffic->bandwidth_left = bandwidth;
		bandwidth_left = bandwidth;
	}
	return check;
}  /* mrp_set_bandwidth */

static void mrp_set_speed(struct mrp_info *mrp, int port, u32 speed)
{
	struct mrp_port_info *info;

	info = get_port_info(mrp, port);
	if (speed != info->speed) {
		if (speed) {
			info->speed = speed;
			if (mrp_set_bandwidth(info)) {
				mrp->no_report = 1;
				update_reservation(mrp, port);
				mrp->no_report = 0;
			}
		}
	}
}  /* mrp_set_speed */
#endif

#ifdef PROC_MRP
#ifndef MRP_PASSTHRU
static int proc_mrp_xmit(struct mrp_info *mrp, int p, struct sk_buff *skb);
#endif

#include "mrp.c"
#include "mmrp.c"
#include "mvrp.c"

#ifdef CONFIG_KSZ_MSRP
#include "msrp.c"

static void mrp_get_talker(struct SRP_talker *talker,
	struct srp_talker_failed *attr)
{
	memcpy(talker, attr, sizeof(struct srp_talker_failed));
	talker->vlan_id = ntohs(talker->vlan_id);
	talker->MaxFrameSize = ntohs(talker->MaxFrameSize);
	talker->MaxIntervalFrames = ntohs(talker->MaxIntervalFrames);
	talker->AccumulatedLatency = ntohl(talker->AccumulatedLatency);
}  /* mrp_get_talker */

static void mrp_set_talker(struct SRP_talker *talker,
	struct srp_talker_failed *attr)
{
	memcpy(attr, talker, sizeof(struct srp_talker_failed));
	attr->vlan_id = htons(attr->vlan_id);
	attr->max_frame_size = htons(attr->max_frame_size);
	attr->max_interval_frames = htons(attr->max_interval_frames);
	attr->accumulated_latency = htonl(attr->accumulated_latency);
}  /* mrp_set_talker */

static void mrp_get_listener(struct SRP_listener *listener,
	struct srp_listener *attr)
{
	memcpy(listener->id, attr->id, 8);
	listener->substate = attr->substate;
}  /* mrp_get_listener */

static void mrp_set_listener(struct SRP_listener *listener,
	struct srp_listener *attr)
{
	memcpy(attr->id, listener->id, 8);
	attr->substate = listener->substate;
}  /* mrp_set_listener */

static void mrp_get_domain(struct SRP_domain_class *domain,
	struct srp_domain *attr)
{
	domain->id = attr->class_id;
	domain->priority = attr->class_priority;
	domain->vlan_id = ntohs(attr->class_vid);
}  /* mrp_get_domain */

static void mrp_set_domain(struct SRP_domain_class *domain,
	struct srp_domain *attr)
{
	attr->class_id = domain->id;
	attr->class_priority = domain->priority;
	attr->class_vid = htons(domain->vlan_id);
}  /* mrp_set_domain */
#endif

static int proc_mrp_join_mac(struct mrp_info *mrp, int port,
	struct MRP_mac *mac)
{
	struct mrp_port *p;
	struct mrp_applicant *app;

	p = &mrp->mrp_ports[port];
	app = rcu_dereference(p->applicants[mac_mrp_app.type]);

	mmrp_req_join_mac(app, mac->addr);
	return 0;
}  /* proc_mrp_join_mac */

static int proc_mrp_leave_mac(struct mrp_info *mrp, int port,
	struct MRP_mac *mac)
{
	struct mrp_port *p;
	struct mrp_applicant *app;

	p = &mrp->mrp_ports[port];
	app = rcu_dereference(p->applicants[mac_mrp_app.type]);

	mmrp_req_leave_mac(app, mac->addr);
	return 0;
}  /* proc_mrp_leave_mac */

static int proc_mrp_join_vlan(struct mrp_info *mrp, int port,
	struct MRP_vlan *vlan)
{
	struct mrp_port *p;
	struct mrp_applicant *app;

	p = &mrp->mrp_ports[port];
	app = rcu_dereference(p->applicants[vlan_mrp_app.type]);

	mvrp_req_join(app, vlan->id);
	return 0;
}  /* proc_mrp_join_vlan */

static int proc_mrp_leave_vlan(struct mrp_info *mrp, int port,
	struct MRP_vlan *vlan)
{
	struct mrp_port *p;
	struct mrp_applicant *app;

	p = &mrp->mrp_ports[port];
	app = rcu_dereference(p->applicants[vlan_mrp_app.type]);

	mvrp_req_leave(app, vlan->id);
	return 0;
}  /* proc_mrp_leave_vlan */

#ifdef CONFIG_KSZ_MSRP
static int proc_mrp_new_talker(struct mrp_info *mrp, int port,
	struct SRP_talker *talker)
{
	struct srp_talker_failed attr;
	struct mrp_port *p;
	struct mrp_applicant *app;

	p = &mrp->mrp_ports[port];
	app = rcu_dereference(p->applicants[srp_mrp_app.type]);

	mrp_set_talker(talker, &attr);
	msrp_req_new_talker(app, &attr);
	return 0;
}  /* proc_mrp_new_talker */

static int proc_mrp_leave_talker(struct mrp_info *mrp, int port,
	struct SRP_talker *talker)
{
	struct srp_talker_failed attr;
	struct mrp_port *p;
	struct mrp_applicant *app;

	p = &mrp->mrp_ports[port];
	app = rcu_dereference(p->applicants[srp_mrp_app.type]);

	mrp_set_talker(talker, &attr);
	msrp_req_leave_talker(app, &attr);
	return 0;
}  /* proc_mrp_leave_talker */

static int proc_mrp_new_listener(struct mrp_info *mrp, int port,
	struct SRP_listener *listener)
{
	struct srp_listener attr;
	struct mrp_port *p;
	struct mrp_applicant *app;

	p = &mrp->mrp_ports[port];
	app = rcu_dereference(p->applicants[srp_mrp_app.type]);

	mrp_set_listener(listener, &attr);
	msrp_req_new_listener(app, &attr);
	return 0;
}  /* proc_mrp_new_listener */

static int proc_mrp_leave_listener(struct mrp_info *mrp, int port,
	struct SRP_listener *listener)
{
	struct srp_listener attr;
	struct mrp_port *p;
	struct mrp_applicant *app;

	p = &mrp->mrp_ports[port];
	app = rcu_dereference(p->applicants[srp_mrp_app.type]);

	mrp_set_listener(listener, &attr);
	msrp_req_leave_listener(app, &attr);
	return 0;
}  /* proc_mrp_leave_listener */

static int proc_mrp_join_domain(struct mrp_info *mrp, int port,
	struct SRP_domain_class *domain)
{
	struct srp_domain attr;
	struct mrp_port *p;
	struct mrp_applicant *app;

	p = &mrp->mrp_ports[port];
	app = rcu_dereference(p->applicants[srp_mrp_app.type]);

	mrp_set_domain(domain, &attr);
	msrp_req_join_domain(app, &attr);
	return 0;
}  /* proc_mrp_join_domain */

static int proc_mrp_leave_domain(struct mrp_info *mrp, int port,
	struct SRP_domain_class *domain)
{
	struct srp_domain attr;
	struct mrp_port *p;
	struct mrp_applicant *app;

	p = &mrp->mrp_ports[port];
	app = rcu_dereference(p->applicants[srp_mrp_app.type]);

	mrp_set_domain(domain, &attr);
	msrp_req_leave_domain(app, &attr);
	return 0;
}  /* proc_mrp_leave_domain */
#endif
#endif

static int proc_mrp_set_attribute(struct mrp_info *mrp, int start, u8 *data)
{
	struct mrp_cfg_options *cmd = (struct mrp_cfg_options *) data;
	u8 port = cmd->port;
	int result = DEV_IOC_OK;

	if (!port)
		port = mrp->ports;
	else
		--port;
	switch (cmd->type) {
	case MRP_TYPE_MAC:
		if (MRP_ACTION_RX == cmd->action)
			result = proc_mrp_rx_mac(mrp, port, &cmd->data.mac);
		else if (MRP_ACTION_LV == cmd->action)
			result = proc_mrp_lv_mac(mrp, port, &cmd->data.mac);
#ifdef PROC_MRP
		else if (MRP_ACTION_DECL == cmd->action)
			result = proc_mrp_join_mac(mrp,
				get_actual_port(mrp, port), &cmd->data.mac);
		else if (MRP_ACTION_DROP == cmd->action)
			result = proc_mrp_leave_mac(mrp,
				get_actual_port(mrp, port), &cmd->data.mac);
#endif
		else if (MRP_ACTION_ON == cmd->action) {
			mrp->no_report = 1;
			result = proc_mrp_rx_mac(mrp, port, &cmd->data.mac);
			mrp->no_report = 0;
		} else if (MRP_ACTION_OFF == cmd->action) {
			mrp->no_report = 1;
			result = proc_mrp_lv_mac(mrp, port, &cmd->data.mac);
			mrp->no_report = 0;
		} else
			mrp_show_node(&mrp->mac_list, show_mac_info);
		break;
	case MRP_TYPE_VLAN:
		if (MRP_ACTION_RX == cmd->action)
			result = proc_mrp_rx_vlan(mrp, port, &cmd->data.vlan);
		else if (MRP_ACTION_LV == cmd->action)
			result = proc_mrp_lv_vlan(mrp, port, &cmd->data.vlan);
#ifdef PROC_MRP
		else if (MRP_ACTION_DECL == cmd->action)
			result = proc_mrp_join_vlan(mrp,
				get_actual_port(mrp, port),
				&cmd->data.vlan);
		else if (MRP_ACTION_DROP == cmd->action)
			result = proc_mrp_leave_vlan(mrp,
				get_actual_port(mrp, port),
				&cmd->data.vlan);
#endif
		else if (MRP_ACTION_ON == cmd->action) {
			mrp->no_report = 1;
			result = proc_mrp_rx_vlan(mrp, port, &cmd->data.vlan);
			mrp->no_report = 0;
		} else if (MRP_ACTION_OFF == cmd->action) {
			mrp->no_report = 1;
			result = proc_mrp_lv_vlan(mrp, port, &cmd->data.vlan);
			mrp->no_report = 0;
		} else
			mrp_show_node(&mrp->vlan_list, show_vlan_info);
		break;

#ifdef CONFIG_KSZ_MSRP
	case MRP_TYPE_DOMAIN:
		if (MRP_ACTION_RX == cmd->action)
			result = proc_mrp_rx_domain(mrp, port,
				&cmd->data.domain);
		else if (MRP_ACTION_LV == cmd->action)
			result = proc_mrp_lv_domain(mrp, port,
				&cmd->data.domain);
#ifdef PROC_MRP
		else if (MRP_ACTION_DECL == cmd->action)
			result = proc_mrp_join_domain(mrp,
				get_actual_port(mrp, port),
				&cmd->data.domain);
		else if (MRP_ACTION_DROP == cmd->action)
			result = proc_mrp_leave_domain(mrp,
				get_actual_port(mrp, port),
				&cmd->data.domain);
#endif
		else if (MRP_ACTION_ON == cmd->action) {
			mrp->no_report = 1;
			result = proc_mrp_rx_domain(mrp, port,
				&cmd->data.domain);
			mrp->no_report = 0;
		} else if (MRP_ACTION_OFF == cmd->action) {
			mrp->no_report = 1;
			result = proc_mrp_lv_domain(mrp, port,
				&cmd->data.domain);
			mrp->no_report = 0;
		}
		break;
	case MRP_TYPE_LISTENER:
		if (MRP_ACTION_RX == cmd->action)
			result = proc_mrp_rx_listener(mrp, port,
				&cmd->data.listener);
		else if (MRP_ACTION_LV == cmd->action)
			result = proc_mrp_lv_listener(mrp, port,
				&cmd->data.listener);
#ifdef PROC_MRP
		else if (MRP_ACTION_DECL == cmd->action)
			result = proc_mrp_new_listener(mrp,
				get_actual_port(mrp, port),
				&cmd->data.listener);
		else if (MRP_ACTION_DROP == cmd->action)
			result = proc_mrp_leave_listener(mrp,
				get_actual_port(mrp, port),
				&cmd->data.listener);
#endif
		else if (MRP_ACTION_ON == cmd->action) {
			mrp->no_report = 1;
			result = proc_mrp_rx_listener(mrp, port,
				&cmd->data.listener);
			mrp->no_report = 0;
		} else if (MRP_ACTION_OFF == cmd->action) {
			mrp->no_report = 1;
			result = proc_mrp_lv_listener(mrp, port,
				&cmd->data.listener);
			mrp->no_report = 0;
		}
		break;
	case MRP_TYPE_TALKER:
		if (MRP_ACTION_RX == cmd->action)
			result = proc_mrp_rx_talker(mrp, port,
				&cmd->data.talker);
		else if (MRP_ACTION_LV == cmd->action)
			result = proc_mrp_lv_talker(mrp, port,
				&cmd->data.talker);
#ifdef PROC_MRP
		else if (MRP_ACTION_DECL == cmd->action)
			result = proc_mrp_new_talker(mrp,
				get_actual_port(mrp, port),
				&cmd->data.talker);
		else if (MRP_ACTION_DROP == cmd->action)
			result = proc_mrp_leave_talker(mrp,
				get_actual_port(mrp, port),
				&cmd->data.talker);
#endif
		else if (MRP_ACTION_ON == cmd->action) {
			mrp->no_report = 1;
			result = proc_mrp_rx_talker(mrp, port,
				&cmd->data.talker);
			mrp->no_report = 0;
		} else if (MRP_ACTION_OFF == cmd->action) {
			mrp->no_report = 1;
			result = proc_mrp_lv_talker(mrp, port,
				&cmd->data.talker);
			mrp->no_report = 0;
		} else {
			int i;

			for (i = 0; i <= mrp->ports; i++)
				chk_reservation(&mrp->port_info[i], i);
		}
		break;
#endif
	case MRP_TYPE_PORT:

#ifdef CONFIG_KSZ_MSRP
		if (MRP_ACTION_SPEED == cmd->action) {
			int speed = start;

			if (1000 == speed || 100 == speed || 10 == speed) {
				mrp_set_speed(mrp, port, speed);
			}
		}
#endif
		break;
	}
	return result;
}  /* proc_mrp_set_attribute */

static int proc_mrp_cfg_mcast_addr(struct mrp_info *mrp, u16 fid, u8 *dest)
{
	struct ksz_sw *sw = container_of(mrp, struct ksz_sw, mrp);
	int result = DEV_IOC_OK;

	sw->ops->cfg_mac(sw, 1, dest, 0, true, fid != 0, fid);
	return result;
}  /* proc_mrp_cfg_mcast_addr */

#ifdef PROC_MRP
static int proc_mrp_xmit(struct mrp_info *mrp, int p, struct sk_buff *skb)
{
	int rc;
	struct ksz_sw *sw = container_of(mrp, struct ksz_sw, mrp);
	const struct net_device_ops *ops = sw->main_dev->netdev_ops;
	int result = DEV_IOC_OK;

#ifdef DBG_MRP_
dbg_msg("  T\n");
#endif

	/* Send to host port by simulating receiving. */
	if (p == sw->HOST_PORT) {
		skb->data[11] ^= 0x01;
		skb->protocol = eth_type_trans(skb, skb->dev);
		netif_rx_ni(skb);
		return 0;
	}

	/* Do not send if network device is not ready. */
	if (!netif_running(sw->main_dev) || !netif_carrier_ok(sw->main_dev)) {
		kfree_skb(skb);
		return 0;
	}

	/* Do not send to port if its link is lost. */
	if (media_disconnected == sw->port_state[p].state) {
		kfree_skb(skb);
		return 0;
	}

	if (skb->len < 60) {
		int len = 60 - skb->len;
		memset(&skb->data[skb->len], 0, len);
		skb_put(skb, len);
	}
	sw->net_ops->add_tail_tag(sw, skb, (1 << p));
	do {
		rc = ops->ndo_start_xmit(skb, skb->dev);
		if (NETDEV_TX_BUSY == rc) {
			rc = wait_event_interruptible_timeout(sw->queue,
				!netif_queue_stopped(sw->main_dev),
				50 * HZ / 1000);

			rc = NETDEV_TX_BUSY;
		}
	} while (NETDEV_TX_BUSY == rc);
	return result;
}  /* proc_mrp_mrp_xmit */
#endif

static void proc_mrp_cmd(struct mrp_info *mrp, struct mrp_work *parent)
{
	u8 *data = parent->param.data;
	int result = DEV_IOC_OK;

	parent->output = parent->option;
	switch (parent->cmd) {
	case DEV_CMD_INFO:
		switch (parent->subcmd) {
		case DEV_INFO_INIT:
			break;
		case DEV_INFO_EXIT:
			break;
		default:
			result = DEV_IOC_INVALID_CMD;
			break;
		}
		break;
	case DEV_CMD_PUT:
		switch (parent->subcmd) {
		case DEV_MRP_ATTRIBUTE:
			result = proc_mrp_set_attribute(mrp, parent->option,
				data);
			break;
		case DEV_MRP_MCAST_ADDR:
			result = proc_mrp_cfg_mcast_addr(mrp, parent->option,
				data);
			break;
		default:
			result = DEV_IOC_INVALID_CMD;
			break;
		}
		break;
	case DEV_CMD_GET:
		switch (parent->subcmd) {
		case DEV_MRP_ATTRIBUTE:
			result = proc_mrp_get_attribute(mrp, parent->option,
				data, &parent->output);
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
}  /* proc_mrp_cmd */

static void proc_mrp_work(struct work_struct *work)
{
	struct mrp_access *info =
		container_of(work, struct mrp_access, work);
	struct mrp_info *mrp =
		container_of(info, struct mrp_info, hw_access);
	struct mrp_work *cmd;

	cmd = &info->works[info->head];
	while (cmd->used) {
		proc_mrp_cmd(mrp, cmd);
		info->head++;
		info->head &= MRP_WORK_LAST;
		cmd = &info->works[info->head];
	}
}  /* proc_mrp_work */

static int proc_mrp_hw_access(struct mrp_info *mrp, int cmd, int subcmd,
	int option, void *data, size_t len, int *output, struct sk_buff *skb,
	int wait)
{
	struct mrp_access *access;
	struct mrp_work *work;
	int ret = 0;

	access = &mrp->hw_access;
	work = &access->works[access->tail];
	if (work->used) {
		pr_alert("work full\n");
		return -EFAULT;
	}
	work->skb = skb;
	work->cmd = cmd;
	work->subcmd = subcmd;
	work->option = option;
	memcpy(work->param.data, data, len);
	work->used = true;
	access->tail++;
	access->tail &= MRP_WORK_LAST;
	init_completion(&work->done);
	schedule_work(&access->work);
	if (!wait)
		goto hw_access_end;
	wait_for_completion(&work->done);

	ret = work->result;
	*output = work->output;
	if (DEV_CMD_GET == work->cmd) {
		int rc = ret;

		if (DEV_IOC_MRP_REPORT == rc) {
			rc = DEV_IOC_OK;
			len = *output;
		}
		if (DEV_IOC_OK == rc)
			memcpy(data, work->param.data, len);
	}

hw_access_end:
	return ret;
}  /* proc_mrp_hw_access */

static void exit_mrp_work(struct mrp_info *mrp)
{
	struct mrp_access *access;
	struct mrp_work *work;
	int i;

	access = &mrp->hw_access;
	for (i = 0; i < MRP_WORK_NUM; i++) {
		work = &access->works[i];
		flush_work(&work->work);
	}
	flush_work(&access->work);
}  /* exit_mrp_work */

static void init_mrp_work(struct mrp_info *mrp)
{
	struct mrp_access *access;
	struct mrp_work *work;
	int i;

	access = &mrp->hw_access;
	for (i = 0; i < MRP_WORK_NUM; i++) {
		work = &access->works[i];
		work->mrp = mrp;
		work->index = i;
		work->prev = &access->works[(i - 1) & MRP_WORK_LAST];
		INIT_WORK(&work->work, proc_mrp_work);
		init_completion(&work->done);
	}
	access->head = access->tail = 0;
	INIT_WORK(&access->work, proc_mrp_work);
}  /* init_mrp_work */


#ifdef CONFIG_HAVE_KSZ9897
static int mrp_chk_mcast(struct mrp_info *mrp, u8 *addr, u16 vid, u16 proto)
{
	struct mrp_node *mac_node;
	struct mrp_mac_info *mac;
	int output;
	u16 ports;
	int result = 0;
	u16 fid = 0;
	struct vlan_ethhdr *vlan = (struct vlan_ethhdr *) addr;

	/* Only check AVB traffic. */
	if (proto != 0x22F0)
		return 1;

	/* XMOS sends this MAAP periodically. */
	if (vlan->h_vlan_proto != htons(ETH_P_8021Q)) {
		if (!(0x01 <= addr[15] && addr[15] <= 0x03))
dbg_msg(" MAAP? %02X:%02X:%02X:%02X:%02X:%02X %02x\n",
addr[0], addr[1], addr[2], addr[3], addr[4], addr[5], addr[15]);
		if (0x01 <= addr[15] && addr[15] <= 0x03)
			return 1;
	}
	if (vid > 1) {
		ports = mrp_find_vlan_ports(&mrp->vlan_list, vid, NULL,
			&fid);
		if (!ports)
			fid = vid;
	}

	/* Check if the multicast address is registered. */
	mac_node = mrp_get_mac_info(&mrp->mac_list, addr, fid);
	if (!mac_node)
		return -ENOMEM;

	mac = mac_node->data;
	ports = mac->srp_ports | mac->mrp_ports;
	ports &= ~SRP_PORT_READY;

	/* It is being used. */
	if (ports)
		return 2;

dbg_msg(" drop %02X:%02X:%02X:%02X:%02X:%02X\n",
addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);
	mac->srp_ports |= SRP_PORT_BLACKLIST;

	/* Drop the multicast frame. */
	result = proc_mrp_hw_access(mrp, DEV_CMD_PUT, DEV_MRP_MCAST_ADDR,
		fid, addr, ETH_ALEN, &output, NULL, false);
	return result;
}  /* mrp_chk_mcast */
#endif

static int mrp_dev_req(struct mrp_info *mrp, int start, char *arg)
{
	struct ksz_request *req = (struct ksz_request *) arg;
	int len;
	int maincmd;
	int req_size;
	int subcmd;
	int output;
	u8 data[PARAM_DATA_SIZE];
	int err = 0;
	int result = 0;
	struct mrp_cfg_options *cmd = (struct mrp_cfg_options *) &req->param;
	size_t param_size = 0;

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

	if (DEV_MRP_ATTRIBUTE == subcmd) {
		switch (cmd->type) {
		case MRP_TYPE_PORT:
			param_size = 4;
			break;
		case MRP_TYPE_MAC:
			param_size = SIZEOF_MRP_mac;
			break;
		case MRP_TYPE_VLAN:
			param_size = SIZEOF_MRP_vlan;
			break;

#ifdef CONFIG_KSZ_MSRP
		case MRP_TYPE_DOMAIN:
			param_size = SIZEOF_SRP_domain_class;
			break;
		case MRP_TYPE_LISTENER:
			param_size = SIZEOF_SRP_listener;
			break;
		case MRP_TYPE_TALKER:
		default:
			param_size = SIZEOF_SRP_talker;
			break;
#endif
		}
	}

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
				data[4] = mrp->version;
				data[5] = mrp->ports;
				if (!access_ok(VERIFY_WRITE, req->param.data,
						6) ||
						copy_to_user(req->param.data,
						data, 6)) {
					err = -EFAULT;
					goto dev_ioctl_done;
				}
				result = proc_mrp_hw_access(mrp,
					maincmd, subcmd, start,
					data, 6, &output, NULL, true);
			} else
				result = DEV_IOC_INVALID_LEN;
			break;
		case DEV_INFO_EXIT:
			result = proc_mrp_hw_access(mrp,
				maincmd, subcmd, start,
				data, 0, &output, NULL, true);

		/* fall through */
		case DEV_INFO_QUIT:
			break;
		default:
			result = DEV_IOC_INVALID_CMD;
			break;
		}
		break;
	case DEV_CMD_PUT:
		switch (subcmd) {
		case DEV_MRP_ATTRIBUTE:
			if (chk_ioctl_size(len, param_size,
					SIZEOF_ksz_request,
					&req_size, &result, &req->param, data))
				goto dev_ioctl_resp;
			if (MRP_ACTION_SPEED == cmd->action)
				start = output;
			result = proc_mrp_hw_access(mrp,
				maincmd, subcmd, start,
				data, len, &output, NULL, true);
			break;
		default:
			result = DEV_IOC_INVALID_CMD;
			break;
		}
		break;
	case DEV_CMD_GET:
		switch (subcmd) {
		case DEV_MRP_ATTRIBUTE:
			if (chk_ioctl_size(len, param_size,
					SIZEOF_ksz_request,
					&req_size, &result, &req->param, data))
				goto dev_ioctl_resp;

#ifdef CONFIG_KSZ_MSRP
			if (MRP_ACTION_SPEED == cmd->action) {
				int port;
				struct ksz_sw *sw =
					container_of(mrp, struct ksz_sw, mrp);

				port = sw_get_dev_port(sw, start, mrp->ports,
					cmd->port);
				__put_user(mrp->port_info[port].speed,
					&req->output);
				break;
			}
#endif
			result = proc_mrp_hw_access(mrp,
				maincmd, subcmd, start,
				data, len, &output, NULL, true);
			if (!access_ok(VERIFY_WRITE, req->param.data,
					param_size) ||
					copy_to_user(req->param.data, data,
					param_size)) {
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
}  /* mrp_dev_req */

#ifdef PROC_MRP
struct mrp_rcv_work {
	struct work_struct work;
	struct mrp_applicant *app;
	struct sk_buff *skb;
};

static void proc_mrp_rcv_work(struct work_struct *work)
{
	struct mrp_rcv_work *rcv_work =
		container_of(work, struct mrp_rcv_work, work);
	struct mrp_applicant *app = rcv_work->app;
	struct sk_buff *skb = rcv_work->skb;

	app->rxpdu(app, &skb->data[sizeof(struct ethhdr)],
		skb->len - sizeof(struct ethhdr));
	kfree_skb(skb);
	kfree(rcv_work);
}  /* proc_mrp_rcv_work */

static void proc_mrp_rcv(struct mrp_applicant *app, struct sk_buff *skb)
{
	struct mrp_rcv_work *rcv_work;

	rcv_work = kzalloc(sizeof(struct mrp_rcv_work), GFP_KERNEL);
	if (!rcv_work) {
		kfree_skb(skb);
		return;
	}
	INIT_WORK(&rcv_work->work, proc_mrp_rcv_work);
	rcv_work->app = app;
	rcv_work->skb = skb;
	schedule_work(&rcv_work->work);
}  /* proc_mrp_rcv */

static int mrp_rcv(struct mrp_info *mrp, struct sk_buff *skb, int p)
{
	struct mrp_application *appl = NULL;
	struct ethhdr *eth = (struct ethhdr *) skb->data;

	if (eth->h_proto == htons(ETH_P_MVRP))
		appl = &vlan_mrp_app;
	else if (eth->h_proto == htons(ETH_P_MMRP))
		appl = &mac_mrp_app;

#ifdef CONFIG_KSZ_MSRP
	else if (eth->h_proto == htons(ETH_P_MSRP))
		appl = &srp_mrp_app;
#endif
	if (appl) {
		struct mrp_port *port;
		struct mrp_applicant *app;

#ifdef DBG_MRP_
		int i;

dbg_msg("  R:\n");
		for (i = 0; i < skb->len; i++) {
			dbg_msg("%02x ", skb->data[i]);
			if ((i % 16) == 15)
				dbg_msg("\n");
		}
		if ((i % 16))
			dbg_msg("\n");
#endif
		port = &mrp->mrp_ports[p];
		app = rcu_dereference(port->applicants[appl->type]);
		proc_mrp_rcv(app, skb);
		return 0;
	}
	return 1;
}  /* mrp_rcv */
#endif

static void mrp_start(struct mrp_info *mrp)
{
#ifdef PROC_MRP_
	struct mrp_port *p;
	struct mrp_applicant *app;

	p = &mrp->mrp_ports[0];

#if 0
	app = rcu_dereference(p->applicants[vlan_mrp_app.type]);
	mvrp_req_join(app, 2);
	mvrp_req_join(app, 3);
#if 1
	mvrp_req_join(app, 8);
#endif
#endif

#if 0
	do {
		u8 addr[6];

		app = rcu_dereference(p->applicants[mac_mrp_app.type]);
		addr[0] = 0x91;
		addr[1] = 0x00;
		addr[2] = 0x00;
		addr[3] = 0x00;
		addr[4] = 0x00;
		addr[5] = 0x01;
		mmrp_req_join_mac(app, addr);
		addr[5] = 0x03;
		mmrp_req_join_mac(app, addr);
#if 0
		mmrp_req_join_svc(app, 8);
#endif
	} while (0);
#endif

#if 0
	do {
		struct srp_talker_failed talker;
		struct srp_listener listener;
		struct srp_domain domain;

		app = rcu_dereference(p->applicants[srp_mrp_app.type]);

		listener.id[0] = 0x12;
		listener.id[1] = 0x34;
		listener.id[2] = 0x56;
		listener.id[3] = 0x78;
		listener.id[4] = 0x9a;
		listener.id[5] = 0xbc;
		listener.id[6] = 0xde;
		listener.id[7] = 0x01;
		listener.substate = MSRP_LISTENER_READY;
		msrp_req_new_listener(app, &listener);
#if 1
		listener.id[7] = 2;
		msrp_req_new_listener(app, &listener);
		listener.id[7] = 21;
		msrp_req_new_listener(app, &listener);
#endif

		memset(&talker, 0, sizeof(talker));
		talker.id[0] = 0x12;
		talker.id[1] = 0x34;
		talker.id[2] = 0x56;
		talker.id[3] = 0x78;
		talker.id[4] = 0x9a;
		talker.id[5] = 0xbc;
		talker.id[6] = 0xde;
		talker.id[7] = 0x01;
		talker.dest[0] = 0x91;
		talker.dest[1] = 0x34;
		talker.dest[2] = 0x56;
		talker.dest[3] = 0x78;
		talker.dest[4] = 0x9a;
		talker.dest[5] = 0x01;
		talker.vlan_id = htons(2);
		talker.max_frame_size = htons(500);
		talker.max_interval_frames = htons(1);
		talker.rank = 1;
		talker.priority = 2;
		talker.accumulated_latency = htonl(200);
		talker.failure_code = 0;
		msrp_req_new_talker(app, &talker);
		talker.id[7] = 0x02;
		talker.dest[5] = 0x02;
		msrp_req_new_talker(app, &talker);

		domain.class_id = 5;
		domain.class_priority = 2;
		domain.class_vid = htons(2);
		msrp_req_join_domain(app, &domain);
#if 1
		domain.class_id = 6;
		domain.class_priority = 3;
		domain.class_vid = htons(2);
		msrp_req_join_domain(app, &domain);
#endif
	} while (0);
#endif
#endif
}  /* mrp_start */

static void mrp_open(struct mrp_info *mrp)
{
	struct mrp_node *prev;
	struct mrp_node *next;
	struct mrp_mac_info *mac;
	struct mrp_vlan_info *vlan;

#ifdef CONFIG_KSZ_MSRP
	u8 port;
	u8 tc;
	struct mrp_port_info *info;
	struct mrp_traffic_info *traffic;
#endif
	u16 ports = 0;
	struct mrp_vlan_info *prev_vlan = NULL;

	prev = &mrp->mac_list.anchor;
	next = prev->next;
	while (next) {
		mac = next->data;
		mrp_cfg_dest_addr(mrp, mac->index, mac->addr, mac->ports,
			mac->fid);
		prev = next;
		next = prev->next;
	}

	prev = &mrp->vlan_list.anchor;
	next = prev->next;
	while (next) {
		vlan = next->data;

		/* The very first one. */
		if (!prev_vlan)
			prev_vlan = vlan;
		if (prev_vlan->vid == vlan->vid)
			ports |= vlan->ports;
		else {
			mrp_cfg_vlan(mrp, prev_vlan->index, prev_vlan->vid,
				prev_vlan->fid, ports);
			prev_vlan = vlan;
			ports = vlan->ports;
		}
		prev = next;
		next = prev->next;
	}
	if (ports)
		mrp_cfg_vlan(mrp, vlan->index, vlan->vid, vlan->fid, ports);

#ifdef CONFIG_KSZ_MSRP
	for (port = 0; port <= mrp->ports; port++) {
		info = get_port_info(mrp, port);
		for (tc = SR_CLASS_A; tc >= SR_CLASS_B; tc--) {
			traffic = get_traffic_info(info, tc);
			if (!traffic->bandwidth_used)
				continue;
			srp_cfg_credit_shaper(mrp, port, info, traffic);
			traffic->bandwidth_set = traffic->bandwidth_used;
		}
	}
#endif
}  /* mrp_open */

static void mrp_clr_blocked_addr(struct mrp_info *mrp, int hw_access)
{
	struct mrp_node *prev;
	struct mrp_node *next;
	struct mrp_mac_info *mac;

	prev = &mrp->mac_list.anchor;
	next = prev->next;
	while (next) {
		mac = next->data;
		if (mac->srp_ports & SRP_PORT_BLACKLIST) {
			if (hw_access)
				mrp_cfg_dest_addr(mrp, mac->index, mac->addr,
					0, mac->fid);

			/* Remove node from list. */
			prev->next = next->next;
			mrp_free_node(next);
		} else
			prev = next;
		next = prev->next;
	}
	mrp->mac_list.last = &mrp->mac_list.anchor;
}  /* mrp_clr_blocked_addr */

static void mrp_chk_blocked_addr(struct mrp_info *mrp)
{
	int p;
	struct ksz_port_mib *mib;
	struct ksz_sw *sw = container_of(mrp, struct ksz_sw, mrp);
	int dropped = 0;
	int dropping = 0;

	for (p = 0; p < sw->mib_port_cnt; p++) {
		mib = &sw->port_mib[p];

		if (mib->drop != mib->counter[MIB_RX_DROPS]) {
			mib->drop = mib->counter[MIB_RX_DROPS];
			if (!mib->first_drop)
				mib->first_drop = mib->drop;
			mib->last_drop = 0;
			++dropping;
		} else if (mib->first_drop) {
			++dropped;
			if (!mib->last_drop) {
				mib->last_drop = jiffies;
				++dropping;
			} else if (jiffies - mib->last_drop < 1000)
				++dropping;
		}
	}
	if (!dropped || dropping)
		return;
	for (p = 0; p < sw->mib_port_cnt; p++) {
		mib = &sw->port_mib[p];

		mib->first_drop = 0;
		mib->last_drop = 0;
	}
	mrp_clr_blocked_addr(mrp, true);
}  /* mrp_chk_blocked_addr */

static void mrp_close(struct mrp_info *mrp, int hw_access)
{
	mrp_clr_blocked_addr(mrp, hw_access);
#ifdef PROC_MRP_
{
struct mrp_port *p;
struct mrp_applicant *app;
u8 addr[6];
#if 1
p = &mrp->mrp_ports[0];
app = rcu_dereference(p->applicants[vlan_mrp_app.type]);
mvrp_req_leave(app, 2);
mvrp_req_leave(app, 3);
#if 1
mvrp_req_leave(app, 8);
#endif

app = rcu_dereference(p->applicants[mac_mrp_app.type]);
addr[0] = 0x91;
addr[1] = 0x00;
addr[2] = 0x00;
addr[3] = 0x00;
addr[4] = 0x00;
addr[5] = 0x01;
mmrp_req_leave_mac(app, addr);
mmrp_req_leave_svc(app, 8);
#endif
}
#endif
}  /* mrp_close */

#ifdef PROC_MRP
static void proc_mrp_attribute(struct mrp_info *mrp, u8 *data)
{
	u8 p;
	u8 in_port;
	int output;
	int result;
	struct mrp_cfg_options *cmd = (struct mrp_cfg_options *) data;

	in_port = cmd->port;
	result = proc_mrp_set_attribute(mrp, 0, data);
	while (DEV_IOC_MRP_REPORT == result) {
		cmd->action = MRP_ACTION_TX;
		cmd->type = MRP_TYPE_UNKNOWN;
		result = proc_mrp_get_attribute(mrp, 0, data, &output);
		if (cmd->action != MRP_ACTION_TX &&
		    cmd->action != MRP_ACTION_LV)
			continue;

		p = get_actual_port(mrp, cmd->port - 1);
		if (MRP_TYPE_MAC == cmd->type) {
			if (MRP_ACTION_TX == cmd->action)
				proc_mrp_join_mac(mrp, p, &cmd->data.mac);
			else
				proc_mrp_leave_mac(mrp, p, &cmd->data.mac);
		} else if (MRP_TYPE_VLAN == cmd->type) {
			if (MRP_ACTION_TX == cmd->action)
				proc_mrp_join_vlan(mrp, p, &cmd->data.vlan);
			else
				proc_mrp_leave_vlan(mrp, p, &cmd->data.vlan);

#ifdef CONFIG_KSZ_MSRP
		} else if (MRP_TYPE_TALKER == cmd->type) {
			if (MRP_ACTION_TX == cmd->action)
				proc_mrp_new_talker(mrp, p,
					&cmd->data.talker);
			else
				proc_mrp_leave_talker(mrp, p,
					&cmd->data.talker);
		} else if (MRP_TYPE_LISTENER == cmd->type) {
			if (MRP_ACTION_TX == cmd->action)
				proc_mrp_new_listener(mrp, p,
					&cmd->data.listener);
			else
				proc_mrp_leave_listener(mrp, p,
					&cmd->data.listener);
		} else if (MRP_TYPE_DOMAIN == cmd->type) {
			if (MRP_ACTION_TX == cmd->action)
				proc_mrp_join_domain(mrp, p,
					&cmd->data.domain);
			else
				proc_mrp_leave_domain(mrp, p,
					&cmd->data.domain);
#endif
		}
	}
}  /* proc_mrp_attribute */

static void mmrp_acton(struct mrp_applicant *app, struct mrp_attr *attr)
{
	u8 data[40];
	struct mrp_cfg_options *cmd = (struct mrp_cfg_options *) data;
	struct mrp_info *mrp = app->parent;
	struct ksz_sw *sw = container_of(mrp, struct ksz_sw, mrp);

	cmd->port = sw_get_net_port(sw, 0, mrp->ports, app->port);
	if (MMRP_ATTR_MAC == attr->type) {
		memcpy(cmd->data.mac.addr, attr->value, ETH_ALEN);
		cmd->type = MRP_TYPE_MAC;
		if (MRP_NOTIFY_LV == attr->notify)
			cmd->action = MRP_ACTION_LV;
		else
			cmd->action = MRP_ACTION_RX;
	}
	attr->notify = MRP_NOTIFY_NONE;
	if (cmd->type != MRP_TYPE_UNKNOWN)
		proc_mrp_attribute(mrp, data);
}  /* mmrp_acton */

static void mvrp_acton(struct mrp_applicant *app, struct mrp_attr *attr)
{
	u8 data[40];
	struct mrp_cfg_options *cmd = (struct mrp_cfg_options *) data;
	struct mrp_info *mrp = app->parent;
	struct ksz_sw *sw = container_of(mrp, struct ksz_sw, mrp);

	cmd->port = sw_get_net_port(sw, 0, mrp->ports, app->port);
	if (MVRP_ATTR_VID == attr->type) {
		u16 *vid = (u16 *) attr->value;

		cmd->data.vlan.id = ntohs(*vid);
		cmd->type = MRP_TYPE_VLAN;
		if (MRP_NOTIFY_LV == attr->notify)
			cmd->action = MRP_ACTION_LV;
		else
			cmd->action = MRP_ACTION_RX;
	}
	attr->notify = MRP_NOTIFY_NONE;
	if (cmd->type != MRP_TYPE_UNKNOWN)
		proc_mrp_attribute(mrp, data);
}  /* mvrp_acton */

#ifdef CONFIG_KSZ_MSRP
static void msrp_acton(struct mrp_applicant *app, struct mrp_attr *attr)
{
	u8 data[40];
	struct mrp_cfg_options *cmd = (struct mrp_cfg_options *) data;
	struct mrp_info *mrp = app->parent;
	struct ksz_sw *sw = container_of(mrp, struct ksz_sw, mrp);

	cmd->port = sw_get_net_port(sw, 0, mrp->ports, app->port);
	switch (attr->type) {
	case MSRP_ATTR_TALKER_FAILED:
	{
		struct SRP_talker *talker = &cmd->data.talker;
		struct srp_talker_failed *attr_talker =
			(struct srp_talker_failed *) attr->value;

		mrp_get_talker(talker, attr_talker);
		cmd->type = MRP_TYPE_TALKER;
		if (MRP_NOTIFY_LV == attr->notify)
			cmd->action = MRP_ACTION_LV;
		else
			cmd->action = MRP_ACTION_RX;
		break;
	}
	case MSRP_ATTR_LISTENER:
	{
		struct SRP_listener *listener = &cmd->data.listener;
		struct srp_listener *attr_listener =
			(struct srp_listener *) attr->value;

		mrp_get_listener(listener, attr_listener);
		cmd->type = MRP_TYPE_LISTENER;
		if (MRP_NOTIFY_LV == attr->notify)
			cmd->action = MRP_ACTION_LV;
		else
			cmd->action = MRP_ACTION_RX;
		break;
	}
	case MSRP_ATTR_DOMAIN:
	{
		struct SRP_domain_class *domain = &cmd->data.domain;
		struct srp_domain *attr_domain =
			(struct srp_domain *) attr->value;

		mrp_get_domain(domain, attr_domain);
		cmd->type = MRP_TYPE_DOMAIN;
		if (MRP_NOTIFY_LV == attr->notify)
			cmd->action = MRP_ACTION_LV;
		else
			cmd->action = MRP_ACTION_RX;
		break;
	}
	default:
		break;
	}
	attr->notify = MRP_NOTIFY_NONE;
	if (cmd->type != MRP_TYPE_UNKNOWN)
		proc_mrp_attribute(mrp, data);
}  /* msrp_acton */
#endif
#endif

static void setup_mrp(struct mrp_info *mrp, struct net_device *dev)
{
#ifdef PROC_MRP
	u8 lp;
	u8 p;
	int err;
	struct mrp_port *port;
	struct mrp_applicant *app;
	struct ksz_sw *sw = container_of(mrp, struct ksz_sw, mrp);

#ifndef NETIF_F_HW_VLAN_CTAG_FILTER
	prandom32_seed(&rnd, get_random_int());
#endif
	for (p = 0; p < sw->mib_port_cnt; p++) {
		lp = sw_get_net_port(sw, 0, mrp->ports, p);
		if (lp > mrp->ports && p != sw->HOST_PORT)
			continue;
		port = &mrp->mrp_ports[p];
		err = mrp_init_applicant(port, dev, &vlan_mrp_app);
		app = rcu_dereference(port->applicants[vlan_mrp_app.type]);
		mvrp_init_application(app, mrp, p, mvrp_acton);
		mrp_periodic_event(app, MRP_EVENT_PERIODIC_ENABLE);

		err = mrp_init_applicant(port, dev, &mac_mrp_app);
		app = rcu_dereference(port->applicants[mac_mrp_app.type]);
		mmrp_init_application(app, mrp, p, mmrp_acton);
		mrp_periodic_event(app, MRP_EVENT_PERIODIC_ENABLE);

#ifdef CONFIG_KSZ_MSRP
		err = mrp_init_applicant(port, dev, &srp_mrp_app);
		app = rcu_dereference(port->applicants[srp_mrp_app.type]);
		msrp_init_application(app, mrp, p, msrp_acton);
		mrp_periodic_event(app, MRP_EVENT_PERIODIC_DISABLE);
#endif
	}
#endif
}  /* setup_mrp */

static ssize_t sysfs_msrp_read(struct ksz_sw *sw, int proc_num, ssize_t len,
	char *buf)
{
	struct mrp_info *mrp = &sw->mrp;
	int chk = 0;
	int type = SHOW_HELP_NONE;
	char note[40];

	note[0] = '\0';
	if (!(sw->features & AVB_SUPPORT))
		return 0;
	switch (proc_num) {
	case PROC_GET_MSRP_INFO:
		len += sprintf(buf + len,
			"max interference size %u\n",
			mrp->max_interference_size);
		break;
	default:
		type = SHOW_HELP_NONE;
		break;
	}
	return sysfs_show(len, buf, type, chk, note, sw->verbose);
}  /* sysfs_msrp_read */

static int sysfs_msrp_write(struct ksz_sw *sw, int proc_num, int num,
	const char *buf)
{
#if 0
	struct mrp_info *mrp = &sw->mrp;
#endif
	int processed = true;

	if (!(sw->features & AVB_SUPPORT))
		return false;
	switch (proc_num) {
	default:
		processed = false;
		break;
	}
	return processed;
}  /* sysfs_msrp_write */

static ssize_t sysfs_msrp_port_read(struct ksz_sw *sw, int proc_num, int port,
	ssize_t len, char *buf)
{
	struct mrp_info *mrp = &sw->mrp;
	struct mrp_port_info *info;
	struct ksz_port_cfg *cfg;
	u8 lp;
	int chk = 0;
	int type = SHOW_HELP_NUM;
	char note[40];

	note[0] = '\0';
	if (!(sw->features & AVB_SUPPORT))
		return 0;
	lp = sw_get_net_port(sw, 0, mrp->ports, port);
	if (lp > mrp->ports && port != sw->HOST_PORT)
		return 0;
	cfg = &sw->info->port_cfg[port];
	info = &mrp->port_info[port];
	switch (proc_num) {
	case PROC_SET_TC_DELTA_BANDWIDTH:
		chk = info->bandwidth[cfg->q_index].deltaBandwidth;
		break;
	case PROC_SET_TC_ADMIN_IDLE_SLOPE:
		len += sprintf(buf + len,
			"%llu\n",
			info->bandwidth[cfg->q_index].adminIdleSlope);
		type = SHOW_HELP_NONE;
		break;
	case PROC_GET_TC_OPER_IDLE_SLOPE:
		len += sprintf(buf + len,
			"%llu\n",
			info->bandwidth[cfg->q_index].operIdleSlope);
		type = SHOW_HELP_NONE;
		break;
	case PROC_SET_TC_ALGORITHM:
		chk = info->algorithm[cfg->q_index].algorithm;
		if (sw->verbose) {
			switch (chk) {
			case 0:
				strcpy(note, " (strict priority)");
				break;
			case 1:
				strcpy(note, " (credit-based shaping)");
				break;
			case 3:
				strcpy(note, " (weighted round robin)");
				break;
			default:
				strcpy(note, " (reserved)");
				break;
			}
		}
		type = SHOW_HELP_SPECIAL;
		break;
	case PROC_GET_SR_0_RX_PRIO:
		chk = info->priority[SR_CLASS_A].received_priority;
		break;
	case PROC_SET_SR_0_TX_PRIO:
		chk = info->priority[SR_CLASS_A].regenerated_priority;
		break;
	case PROC_GET_SR_0_SRP_DOMAIN_BOUNDARY:
		chk = info->priority[SR_CLASS_A].SRPdomainBoundaryPort;
		break;
	case PROC_GET_SR_1_RX_PRIO:
		chk = info->priority[SR_CLASS_B].received_priority;
		break;
	case PROC_SET_SR_1_TX_PRIO:
		chk = info->priority[SR_CLASS_B].regenerated_priority;
		break;
	case PROC_GET_SR_1_SRP_DOMAIN_BOUNDARY:
		chk = info->priority[SR_CLASS_B].SRPdomainBoundaryPort;
		break;
	default:
		type = SHOW_HELP_NONE;
		break;
	}
	return sysfs_show(len, buf, type, chk, note, sw->verbose);
}  /* sysfs_msrp_port_read */

static int sysfs_msrp_port_write(struct ksz_sw *sw, int proc_num, int port,
	int num, const char *buf)
{
	struct mrp_info *mrp = &sw->mrp;
	struct mrp_port_info *info;
	struct ksz_port_cfg *cfg;
	u8 lp;
	int delta;
	int processed = true;

	if (!(sw->features & AVB_SUPPORT))
		return false;
	lp = sw_get_net_port(sw, 0, mrp->ports, port);
	if (lp > mrp->ports && port != sw->HOST_PORT)
		return false;
	cfg = &sw->info->port_cfg[port];
	info = &mrp->port_info[port];
	switch (proc_num) {
	case PROC_SET_TC_DELTA_BANDWIDTH:
		if (3 == cfg->q_index)
			delta = info->bandwidth[2].deltaBandwidth;
		else if (2 == cfg->q_index)
			delta = info->bandwidth[3].deltaBandwidth;
		else
			delta = 0;
		if (num + delta <= 75)
			info->bandwidth[cfg->q_index].deltaBandwidth = num;
		break;
	case PROC_SET_TC_ADMIN_IDLE_SLOPE:
		if (num >= 0) {
			u64 slope = num;

			slope *= 1000;
			info->bandwidth[cfg->q_index].adminIdleSlope = slope;
			srp_cfg_idle_slope(mrp, port, info, slope);
		}
		break;
	case PROC_SET_TC_ALGORITHM:
		if (0 <= num && num < 2)
			info->algorithm[cfg->q_index].algorithm = num;
		else if (3 == num)
			info->algorithm[cfg->q_index].algorithm = num;

#ifdef CONFIG_HAVE_KSZ9897
		sw->reg->lock(sw);
		if (0 == num || 1 == num) {
			port_set_schedule_mode(sw, port, cfg->q_index,
				MTI_SCHEDULE_STRICT_PRIO);
			port_set_shaping(sw, port, cfg->q_index,
				1 == num ? MTI_SHAPING_SRP : MTI_SHAPING_OFF);
		} else if (3 == num) {
			port_set_schedule_mode(sw, port, cfg->q_index,
				MTI_SCHEDULE_WRR);
			port_set_shaping(sw, port, cfg->q_index,
				MTI_SHAPING_OFF);
		}
		sw->reg->unlock(sw);
#endif
		break;
	case PROC_SET_SR_0_TX_PRIO:
		if (0 <= num && num < 8)
			info->priority[SR_CLASS_A].regenerated_priority = num;
		break;
	case PROC_SET_SR_1_TX_PRIO:
		if (0 <= num && num < 8)
			info->priority[SR_CLASS_B].regenerated_priority = num;
		break;
	default:
		processed = false;
		break;
	}
	return processed;
}  /* sysfs_msrp_port_write */

static void leave_mrp(struct mrp_info *mrp)
{
#ifdef PROC_MRP
	u8 lp;
	u8 p;
	struct ksz_sw *sw = container_of(mrp, struct ksz_sw, mrp);

	for (p = 0; p < sw->mib_port_cnt; p++) {
		lp = sw_get_net_port(sw, 0, mrp->ports, p);
		if (lp > mrp->ports && p != sw->HOST_PORT)
			continue;
		mrp_uninit_applicant(&mrp->mrp_ports[p], &vlan_mrp_app);
		mrp_uninit_applicant(&mrp->mrp_ports[p], &mac_mrp_app);

#ifdef CONFIG_KSZ_MSRP
		mrp_uninit_applicant(&mrp->mrp_ports[p], &srp_mrp_app);
#endif
	}
#endif
}  /* leave_mrp */

static void mrp_init(struct mrp_info *mrp)
{
	struct ksz_sw *sw = container_of(mrp, struct ksz_sw, mrp);

#ifdef CONFIG_KSZ_MSRP
	u8 lp;
	u8 port;
	int tc;
	struct mrp_port_info *info;
	char bw_str1[20];
	char bw_str2[20];
	char bw_str3[20];
	char bw_str4[20];
	char bw_str5[20];
#endif

	mrp->access = create_singlethread_workqueue("mrp_access");
	init_mrp_work(mrp);
	mutex_init(&mrp->lock);

	/* Number of ports can be capped for testing purpose. */
	mrp->ports = sw->mib_port_cnt - 1;

	mrp_init_list(&mrp->mac_list);
	mrp_init_list(&mrp->vlan_list);

#ifdef CONFIG_KSZ_MSRP
	mrp->id[0] = 0x01;
	mrp->id[1] = 0x80;
	mrp->id[2] = 0xA6;
	mrp->id[3] = 0x98;
	mrp->id[4] = 0x97;
	mrp->id[5] = 0x01;
	mrp->id[6] = 0x01;
	mrp->id[7] = 0x01;
	mrp->tc[2] = SR_CLASS_B;
	mrp->tc[3] = SR_CLASS_A;
	mrp->prio[SR_CLASS_A] = 3;
	mrp->prio[SR_CLASS_B] = 2;
	mrp->max_interference_size = 1514 + 6;

	mrp_init_list(&mrp->mac_down);
	mrp_init_list(&mrp->mac_up);
	mrp_init_list(&mrp->vlan_down);
	mrp_init_list(&mrp->vlan_up);

	for (port = 0; port < sw->mib_port_cnt; port++) {
		lp = sw_get_net_port(sw, 0, mrp->ports, port);
		if (lp > mrp->ports && port != sw->HOST_PORT)
			continue;
		info = &mrp->port_info[port];
		info->speed = 100;
		if (sw->port_info[port].tx_rate)
			info->speed = sw->port_info[port].tx_rate /
				TX_RATE_UNIT;

		info->bandwidth[3].deltaBandwidth = 50;
		info->bandwidth[3].adminIdleSlope = 0;
		info->bandwidth[3].operIdleSlope =
			info->bandwidth[3].adminIdleSlope;

		info->bandwidth[2].deltaBandwidth = 25;
		info->bandwidth[2].adminIdleSlope = 0;
		info->bandwidth[2].operIdleSlope =
			info->bandwidth[2].adminIdleSlope;

		for (tc = 0; tc < 4; tc++) {
			info->bandwidth[tc].traffic_class = tc;
			info->algorithm[tc].traffic_class = tc;
		}
		info->algorithm[0].algorithm = 3;
		info->algorithm[1].algorithm = 3;
		info->algorithm[2].algorithm = 1;
		info->algorithm[3].algorithm = 1;

		info->priority[SR_CLASS_A].received_priority =
			mrp->prio[SR_CLASS_A];
		info->priority[SR_CLASS_A].regenerated_priority = 0;
		info->priority[SR_CLASS_B].received_priority =
			mrp->prio[SR_CLASS_B];
		info->priority[SR_CLASS_B].regenerated_priority = 0;

		info->traffic[0].queue = get_queue_priority(mrp, SR_CLASS_A);
		info->traffic[1].queue = get_queue_priority(mrp, SR_CLASS_B);
		mrp_set_bandwidth(info);

		format_num(bw_str1, info->bandwidth_left);
		format_num(bw_str2, info->traffic[0].bandwidth_max);
		format_num(bw_str3, info->traffic[0].bandwidth_left);
		format_num(bw_str4, info->traffic[1].bandwidth_max);
		format_num(bw_str5, info->traffic[1].bandwidth_left);
dbg_msg("bw: %d %s; %s %s; %s %s\n", port,
bw_str1, bw_str2, bw_str3, bw_str4, bw_str5);

		mrp_init_list(&info->active);
		mrp_init_list(&info->passive);
	}
#endif
}  /* mrp_init */

static void mrp_exit(struct mrp_info *mrp)
{
	exit_mrp_work(mrp);
	if (mrp->access) {
		destroy_workqueue(mrp->access);
		mrp->access = NULL;
	}
}  /* mrp_exit */

static struct mrp_ops mrp_ops = {
	.init			= mrp_init,
	.exit			= mrp_exit,

	.dev_req		= mrp_dev_req,
};

