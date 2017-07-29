/**
 * Micrel MRP driver code
 *
 * Copyright (c) 2014-2015 Micrel, Inc.
 *
 * Copyright (c) 2015 Microchip Technology Inc.
 *	Tristram Ha <Tristram.Ha@microchip.com>
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


#define SW_CREDIT_SHAPING_SCALE	0x10000
#define SW_CREDIT_SHAPING_S	16

#define CREDIT_PERCENTAGE_S	(16 + 9)

#define NETWORK_SPEED_IN_MBIT	1000000

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

	val = size;
	val *= slope;
	size = 100;
	size <<= CREDIT_PERCENTAGE_S;
	val = div_u64_rem(val, size, &rem);
	val >>= 3;
	return (u16) val;
}  /* get_hi_credit */

static u16 get_lo_credit(u32 size, u32 slope)
{
	u64 val;
	u32 rem;

	val = size;
	val *= slope;
	size = 100;
	size <<= CREDIT_PERCENTAGE_S;
	val = div_u64_rem(val, size, &rem);
	val >>= 3;
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

static u8 get_queue_priority(struct mrp_info *mrp, u8 tc)
{
	return mrp->prio[tc];
}  /* get_queue_priority */

static void srp_cfg_credit_shaper(struct mrp_info *mrp, u8 port, u8 tc)
{
	u16 credit;
	u16 credit_lo;
	u16 credit_hi;
	u32 idle;
	u32 send;
	u8 queue;
	struct mrp_port_info *info = &mrp->port_info[port];

	credit = get_credit_increment(info->speed,
		info->traffic[tc].bandwidth_used);
	idle = get_idle_slope(info->speed, info->traffic[tc].bandwidth_used);
	send = get_send_slope(idle);
	credit_hi = get_hi_credit(mrp->max_interference_size, idle);
	credit_lo = get_lo_credit(info->traffic[tc].max_frame_size, send);
	queue = get_queue_priority(mrp, tc);
dbg_msg("%s %d:%d=%x %x %x; %u %u %u\n", __func__, port,
	queue, credit, credit_hi, credit_lo, info->traffic[tc].bandwidth_used,
idle, send);
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
				MTI_SCHEDULE_STRICT_PRIO);
			port_set_shaping(sw, port, queue, MTI_SHAPING_OFF);
		}
		sw->reg->unlock(sw);
	} while (0);
#endif
}  /* srp_cfg_credit_shaper */

static void mrp_cfg_dest_addr(struct mrp_info *mrp, u8 index, u8 *dest,
	u32 ports)
{
	struct ksz_sw *sw = container_of(mrp, struct ksz_sw, mrp);

dbg_msg("%s %d=%02x:%02x:%02x:%02x:%02x:%02x %04x\n", __func__, index,
dest[0], dest[1], dest[2], dest[3], dest[4],dest[5],
ports);
	ports &= ~(1 << 15);
	sw->ops->cfg_mac(sw, index, dest, ports, false, true, 2);
}  /* mrp_cfg_dest_addr */

static void mrp_cfg_vlan(struct mrp_info *mrp, u8 index, u16 vid, u32 ports)
{
	struct ksz_sw *sw = container_of(mrp, struct ksz_sw, mrp);

dbg_msg("%s %d=%x %04x\n", __func__, index, vid, ports);
	ports &= ~(1 << 15);
	sw->ops->cfg_vlan(sw, index, vid, 2, ports);
}  /* mrp_cfg_vlan */

static int get_traffic_class(struct mrp_info *mrp, u8 prio)
{
	return mrp->tc[prio];
}  /* get_traffic_class */

static int get_traffic_priority(struct mrp_info *mrp, u8 tc)
{
	int i;

	for (i = 0; i < 4; i++)
		if (mrp->tc[i] == tc)
			return i;
	return 0;
}  /* get_traffic_priority */

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
	bandwidth += 42;
	bandwidth *= interval;
	bandwidth *= frames;
	bandwidth *= 8;
	return bandwidth;
}  /* calculate_bandwidth */

static int cmp_mac(void *first, void *second)
{
	int cmp;
	u8 *a = first;
	u8 *b = second;

	cmp = memcmp(a, b, ETH_ALEN);
	return cmp;
}  /* cmp_mac */

static void show_mac_info(void *this)
{
	struct mrp_mac_info *info = this;

	dbg_msg(
		"%02x:%02x:%02x:%02x:%02x:%02x %d=%04x %04x %04x\n",
		info->addr[0], info->addr[1], info->addr[2],
		info->addr[3], info->addr[4], info->addr[5],
		info->index,
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
		"%d=%03x %04x %04x\n", info->index,
		info->vid, info->ports, info->tx_ports);
}  /* show_vlan_info */

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

	cmp = b->tc - a->tc;
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

void *get_show(int (*cmp)(void *a, void *b))
{
	if (cmp == cmp_mac)
		return show_mac_info;
	else if (cmp == cmp_vlan)
		return show_vlan_info;
	else
		return show_stream_info;
}  /* get_show */

static void mrp_init_list(struct mrp_node_anchor *list)
{
	list->last = &list->anchor;
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
	if (delete > 1)
		kfree(next->data);

	/* Free the node. */
	kfree(next);
	return NULL;
}  /* mrp_delete_this_node */

static void mrp_delete_node(struct mrp_node_anchor *list,
	int (*cmp)(void *a, void *b), struct mrp_node *this, int delete)
{
	mrp_delete_this_node(list, cmp, this, ++delete);
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

static struct SRP_stream *srp_create_stream(u8 *id, u8 *dest, u16 vlan_id,
	u16 size, u16 interval, u8 prio, u8 rank)
{
	struct SRP_stream *stream;

	stream = kzalloc(sizeof(struct SRP_stream), GFP_KERNEL);
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

static void srp_remove_stream(struct mrp_info *mrp, struct SRP_stream *stream)
{
	if (stream->id_next)
		stream->id_next->id_prev = stream->id_prev;
	stream->id_prev->id_next = stream->id_next;
	if (stream->dest_next)
		stream->dest_next->dest_prev = stream->dest_prev;
	stream->dest_prev->dest_next = stream->dest_next;
	kfree(stream);
}  /* srp_remove_stream */

static struct SRP_reservation *srp_create_reservation(u8 *id, u8 dir, u8 dec,
	u32 latency, u8 *bridge_id, u8 code)
{
	struct SRP_reservation *reserv;

	reserv = kzalloc(sizeof(struct SRP_reservation), GFP_KERNEL);
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

static void srp_remove_reservation(struct SRP_reservation *reserv)
{
	if (reserv->next)
		reserv->next->prev = reserv->prev;
	reserv->prev->next = reserv->next;
	kfree(reserv);
}  /* srp_remove_reservation */

static void chk_reservation(struct mrp_port_info *info, int port)
{
	struct SRP_reservation *reserv;

dbg_msg("%d:\n", port);
dbg_msg("  registered: %p\n", &info->registered);
	reserv = info->registered.next;
	while (reserv) {
dbg_msg("%02x:%02x %d %d\n", reserv->id[6], reserv->id[7], reserv->direction,
	reserv->declaration);
		reserv = reserv->next;
	}
dbg_msg("  declared: %p\n", &info->declared);
	reserv = info->declared.next;
	while (reserv) {
dbg_msg("%02x:%02x %d %d\n", reserv->id[6], reserv->id[7], reserv->direction,
	reserv->declaration);
		reserv = reserv->next;
	}
dbg_msg("  active:\n");
	mrp_show_node(&info->active, show_stream_info);
dbg_msg("  passive:\n");
	mrp_show_node(&info->passive, show_stream_info);
dbg_msg("A:%u B:%u T:%u\n",
	info->traffic[SR_CLASS_A].bandwidth_left,
	info->traffic[SR_CLASS_B].bandwidth_left,
	info->bandwidth_left);
dbg_msg("\n");
}  /* chk_reservation */

static struct mrp_node *mrp_get_mac_info(struct mrp_node_anchor *list,
	u8 *addr)
{
	struct mrp_node *node;

	node = mrp_find_node(list, cmp_mac, addr);
	if (!node) {
		node = kzalloc(sizeof(struct mrp_node), GFP_KERNEL);
		if (!node)
			return NULL;
		node->data = kzalloc(sizeof(struct mrp_mac_info), GFP_KERNEL);
		if (!node->data) {
			kfree(node);
			return NULL;
		}
		memcpy(node->data, addr, ETH_ALEN);
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

		node = kzalloc(sizeof(struct mrp_node), GFP_KERNEL);
		if (!node)
			return NULL;
		node->data = kzalloc(sizeof(struct mrp_vlan_info), GFP_KERNEL);
		if (!node->data) {
			kfree(node);
			return NULL;
		}
		info = node->data;
		info->vid = vid;
		memcpy(info->addr, data.addr, ETH_ALEN);
		mrp_insert_node(list, cmp_vlan, node);
	}
	return node;
}  /* mrp_get_vlan_info */

static u16 mrp_find_vlan_ports(struct mrp_node_anchor *list, u16 vid,
	u8 *index)
{
	struct mrp_node *prev;
	struct mrp_node *next;
	struct mrp_vlan_info *info;
	u16 ports = 0;

	prev = &list->anchor;
	next = prev->next;
	while (next) {
		info = next->data;
		if (vid == info->vid) {
			ports |= info->ports;
			if (info->ports && index && *index != info->index)
				*index = info->index;
		} else if (vid > info->vid)
			break;
		prev = next;
		next = prev->next;
	}
	return ports;
}

static struct mrp_report *mrp_create_report(struct SRP_reservation *reserv,
	u8 port)
{
	struct mrp_report *attrib;

	attrib = kzalloc(sizeof(struct mrp_report), GFP_KERNEL);
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

static int proc_mrp_lv(struct mrp_info *mrp, struct mrp_node *node, u16 ports,
	u16 *tx_ports, u8 type)
{
	int p;
	int result = DEV_IOC_OK;

	if (!ports) {

		/* Ask all ports to withdraw the declaration. */
		for (p = 0; p < mrp->ports; p++)
			if (*tx_ports & (1 << p))
				add_attrib_report(mrp, node,
					MRP_ACTION_LV, type, p);
		*tx_ports = 0;

		/* Notify the host of the Leave indication. */
		/* Used to free the attribute. */
		add_attrib_report(mrp, node, MRP_ACTION_LV, type, mrp->ports);
		result = DEV_IOC_MRP_REPORT;
	} else {
		int uninitialized_var(q);
		int cnt = 0;

		for (p = 0; p < mrp->ports; p++)
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
	struct mrp_mac_info *info;
	u16 mrp_ports;
	u16 ports;
	int result = DEV_IOC_OK;
dbg_msg("%s %d %02x:%02x:%02x:%02x:%02x:%02x\n", __func__, port,
	mac->addr[0],
	mac->addr[1],
	mac->addr[2],
	mac->addr[3],
	mac->addr[4],
	mac->addr[5]);

	node = mrp_find_node(&mrp->mac_list, cmp_mac, mac->addr);
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
		mrp_cfg_dest_addr(mrp, info->index, info->addr, info->ports);
		if (!info->ports) {
			mrp_free_mac(mrp, info->index);
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
dbg_msg("%s %d %02x:%02x:%02x:%02x:%02x:%02x\n", __func__, port,
	mac->addr[0],
	mac->addr[1],
	mac->addr[2],
	mac->addr[3],
	mac->addr[4],
	mac->addr[5]);

	node = mrp_get_mac_info(&mrp->mac_list, mac->addr);
	if (!node)
		return -ENOMEM;
	info = node->data;
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
				mrp_delete_node(&mrp->mac_list, cmp_mac, node,
					true);
				return -ENOMEM;
			}
		}
		mrp_cfg_dest_addr(mrp, info->index, info->addr, info->ports);
	}
#ifdef DEBUG
	mrp_show_node(&mrp->mac_list, show_mac_info);
#endif
	if (mrp->no_report)
		return result;

	/* Ask all other ports to declare the attribute. */
	for (p = 0; p <= mrp->ports; p++)
		if (p != port && !(info->tx_ports & (1 << p))) {
			if (p < mrp->ports)
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

dbg_msg("%s %d %d\n", __func__, port, vlan->id);
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
	ports = mrp_find_vlan_ports(&mrp->vlan_list, data.vid, NULL);
	mrp_cfg_vlan(mrp, info->index, info->vid, ports);
	if (!ports)
		mrp_free_vlan(mrp, info->index);
	if (!info->ports)
		mrp_remove_node(&mrp->vlan_list, cmp_vlan, node);

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

dbg_msg("%s %d %d\n", __func__, port, vlan->id);
	node = mrp_get_vlan_info(&mrp->vlan_list, vlan->id, NULL);
	if (!node)
		return -ENOMEM;
	info = node->data;
	ports = info->ports;
	info->ports |= (1 << port);

	/* There is change in port membership. */
	if (ports != info->ports) {
		ports = mrp_find_vlan_ports(&mrp->vlan_list, vlan->id,
			&info->index);

		/* First time setting up VLAN table. */
		if (!ports) {
			info->index = mrp_alloc_vlan(mrp);
			if (!info->index) {
				mrp_delete_node(&mrp->vlan_list, cmp_vlan,
					node, true);
				return -ENOMEM;
			}
		}
		mrp_cfg_vlan(mrp, info->index, info->vid, ports);
	}
#ifdef DEBUG
	mrp_show_node(&mrp->vlan_list, show_vlan_info);
#endif
	if (mrp->no_report)
		return result;

	/* Ask all other ports to declare the attribute. */
	for (p = 0; p <= mrp->ports; p++)
		if (p != port && !(info->tx_ports & (1 << p))) {
			if (p < mrp->ports)
				info->tx_ports |= (1 << p);
			add_attrib_report(mrp, node, MRP_ACTION_TX,
				MRP_TYPE_VLAN, p);
			result = DEV_IOC_MRP_REPORT;
		}
	return result;
}  /* proc_mrp_rx_vlan */

static int proc_mrp_lv_domain(struct mrp_info *mrp, u8 port,
	struct SRP_domain_class *domain)
{
dbg_msg("%s %d %d %d %d\n", __func__, port,
	domain->id, domain->priority, domain->vlan_id);
	if (mrp->no_report)
		return DEV_IOC_OK;

	/* Coming from the host. */
	if (port == mrp->ports) {
		for (port = 0; port < mrp->ports; port++)
			add_attrib_report(mrp, NULL, MRP_ACTION_LV,
				MRP_TYPE_DOMAIN, port);
	}
	return DEV_IOC_OK;
}  /* proc_mrp_lv_domain */

static int proc_mrp_rx_domain(struct mrp_info *mrp, u8 port,
	struct SRP_domain_class *domain)
{
dbg_msg("%s %d %d %d %d\n", __func__, port,
	domain->id, domain->priority, domain->vlan_id);
	mrp->domain = *domain;
	if (mrp->no_report)
		return DEV_IOC_OK;

	/* Coming from the host. */
	if (port == mrp->ports) {
		for (port = 0; port < mrp->ports; port++)
			add_attrib_report(mrp, NULL, MRP_ACTION_TX,
				MRP_TYPE_DOMAIN, port);
	}
	return DEV_IOC_OK;
}  /* proc_mrp_rx_domain */

static int srp_update_mac(struct mrp_info *mrp, u8 *addr, u16 ports, int up)
{
	struct mrp_node_anchor *list;
	struct mrp_node *node;
	struct mrp_mac_info *mac;
	struct mrp_mac_info *update;

	node = mrp_get_mac_info(&mrp->mac_list, addr);
	if (!node)
		return -ENOMEM;
	mac = node->data;
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
#ifdef DEBUG
	mrp_show_node(&mrp->mac_list, show_mac_info);
#endif
	node = mrp_get_mac_info(list, addr);
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
	u8 tc;
	struct mrp_port_info *info = &mrp->port_info[port];
	int result = 0;
	struct mrp_node_anchor *list;
	struct srp_stream_info *data;

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
				stream = reserv->stream;
				tc = data->tc;
				tc = get_traffic_class(mrp, stream->priority);
				bandwidth = calculate_bandwidth(stream->MaxFrameSize,
					stream->MaxIntervalFrames, frames_per_sec(tc));

				info->traffic[tc].bandwidth_left += bandwidth;
				info->traffic[tc].bandwidth_used -= bandwidth;
				info->bandwidth_left += bandwidth;

				result = srp_update_mac(mrp, stream->dest,
					1 << port, false);
				if (!result)
					result = srp_update_vlan(mrp,
						stream->vlan_id, stream->dest,
						1 << port, false);
			}

			/* Remove node from list. */
			prev->next = next->next;
			kfree(next);
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
		mrp_cfg_dest_addr(mrp, mac->index, mac->addr, mac->ports);

		kfree(next->data);
		kfree(next);

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
			&vlan->index);
		mrp_cfg_vlan(mrp, vlan->index, vlan->vid, ports);

		kfree(next->data);
		kfree(next);

		next = prev->next;
	}
	list->last = &list->anchor;
}  /* srp_cfg_vlan */

static void srp_cfg_reservation(struct mrp_info *mrp)
{
	u8 port;
	u8 tc;
	struct mrp_port_info *info;

	srp_cfg_mac(mrp, &mrp->mac_down);
	srp_cfg_vlan(mrp, &mrp->vlan_down);
	for (port = 0; port <= mrp->ports; port++) {
		info = &mrp->port_info[port];
		for (tc = SR_CLASS_A; tc <= SR_CLASS_B; tc++) {
			if (info->traffic[tc].bandwidth_used !=
			    info->traffic[tc].bandwidth_set) {
				srp_cfg_credit_shaper(mrp, port, tc);
				info->traffic[tc].bandwidth_set =
					info->traffic[tc].bandwidth_used;
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

	node = kzalloc(sizeof(struct mrp_node), GFP_KERNEL);
	if (!node)
		return NULL;
	info = kzalloc(sizeof(struct srp_stream_info), GFP_KERNEL);
	if (!info) {
		kfree(node);
		return NULL;
	}
	prepare_stream_info(t_reserv,
		get_traffic_class(mrp, t_reserv->stream->priority), info);
	node->data = info;
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

static int mrp_update_listener(struct mrp_info *mrp,
	struct SRP_reservation *l_reserv, struct SRP_stream *stream)
{
	int declaration;
	int i;
	struct SRP_reservation *reserv;
	struct SRP_reservation *t_reserv;
	struct mrp_port_info *info = &mrp->port_info[stream->in_port];
	int result = DEV_IOC_OK;

	if (!l_reserv)
		l_reserv = srp_find_reservation(&info->declared, stream->id,
			SRP_LISTENER);
	if (!l_reserv)
		return result;

	declaration = 0;
	for (i = 0; i <= mrp->ports; i++) {
		if (i == stream->in_port)
			continue;
		info = &mrp->port_info[i];
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
dbg_msg("listener leaving\n");
		if (!mrp->no_report) {
			add_attrib_report(mrp, l_reserv, MRP_ACTION_LV,
				MRP_TYPE_LISTENER, stream->in_port);
			result = DEV_IOC_MRP_REPORT;
		} else
			srp_remove_reservation(l_reserv);
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
	u8 tc;
	struct mrp_port_info *info = &mrp->port_info[port];
	struct srp_stream_info b;
	struct srp_stream_info *data;
	int result;

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
		tc = get_traffic_class(mrp, stream->priority);
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
		data = next->data;
		reserv = data->reserv;
		tc = data->tc;

		stream = reserv->stream;
		bandwidth = calculate_bandwidth(stream->MaxFrameSize,
			stream->MaxIntervalFrames, frames_per_sec(tc));

		info->traffic[tc].bandwidth_left += bandwidth;
		info->traffic[tc].bandwidth_used -= bandwidth;

		/* Remove node from list. */
		prev->next = next->next;

		reserv->declaration = SRP_FAILED;
		reserv->code = RFC_NO_BANDWIDTH;

		reserv->pair->code = RFC_PREEMPTED_BY_RANK;

		result = srp_update_mac(mrp, stream->dest, 1 << port, false);
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
	u8 tc;
	struct mrp_port_info *info = &mrp->port_info[port];
	int started = 0;
	int result;
	struct srp_stream_info *data;

	prev = &info->passive.anchor;
	next = prev->next;
	while (next) {
		data = next->data;
		reserv = data->reserv;

		stream = reserv->stream;
		tc = data->tc;
		bandwidth = calculate_bandwidth(stream->MaxFrameSize,
			stream->MaxIntervalFrames, frames_per_sec(tc));
		if (bandwidth <= info->traffic[tc].bandwidth_left) {
			info->traffic[tc].bandwidth_left -= bandwidth;
			info->traffic[tc].bandwidth_used += bandwidth;
			info->bandwidth_left -= bandwidth;

			reserv->declaration = SRP_ADVERTISE;
			reserv->code = RFC_NO_ERROR;

			reserv->pair->code = RFC_NO_ERROR;

			result = srp_update_mac(mrp, stream->dest, 1 << port,
				true);
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

			add_reservation(info, true, next);

			next = prev;
		}
		prev = next;
		next = prev->next;
	}
	return started;
}  /* start_passive_reservation */

static int check_avail_bandwidth(struct mrp_info *mrp, u8 port,
	struct SRP_stream *stream, struct SRP_reservation *t_reserv)
{
	u64 bandwidth;
	u8 tc;
	struct mrp_port_info *info = &mrp->port_info[port];
	int result;

	tc = get_traffic_class(mrp, stream->priority);
	bandwidth = calculate_bandwidth(stream->MaxFrameSize,
		stream->MaxIntervalFrames, frames_per_sec(tc));
dbg_msg("bw: %llu %u %u\n", bandwidth, info->bandwidth_left,
info->traffic[tc].bandwidth_left);

	if (bandwidth > info->traffic[tc].bandwidth_left) {
		t_reserv->code = RFC_NO_BANDWIDTH_FOR_TRAFFIC_CLASS;
dbg_msg("tc %llu %u\n", bandwidth, info->traffic[tc].bandwidth_max);

		/* See if this stream has higher rank. */
		if (bandwidth <= info->traffic[tc].bandwidth_max) {
dbg_msg("higher rank\n");
			if (drop_other_reservations(mrp, port, t_reserv,
					bandwidth))
				t_reserv->code = RFC_NO_ERROR;
		}
	} else if (bandwidth > info->bandwidth_left) {
		t_reserv->code = RFC_NO_BANDWIDTH;
dbg_msg("port %llu %u\n", bandwidth, info->bandwidth_max);

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
		u16 ports = 1 << port;

		/* Reduce bandwidth */
		info->bandwidth_left -= bandwidth;
		info->traffic[tc].bandwidth_left -= bandwidth;
		info->traffic[tc].bandwidth_used += bandwidth;
		if (stream->MaxFrameSize > info->traffic[tc].max_frame_size)
			info->traffic[tc].max_frame_size =
				stream->MaxFrameSize;

		active = create_stream_info(mrp, t_reserv);
		if (!active)
			return SRP_ASKING_FAILED;

		add_reservation(info, true, active);

		result = srp_update_mac(mrp, stream->dest, ports, true);
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
	int result;
	int started = 0;
	struct mrp_port_info *info = &mrp->port_info[port];
	u8 declaration = l_reserv->declaration;

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
		l_reserv->code = RFC_NO_BANDWIDTH;
		started = start_passive_reservation(mrp, port);
		srp_cfg_reservation(mrp);
	}

	info = &mrp->port_info[stream->in_port];
	reserv = srp_find_reservation(&info->declared, l_reserv->id,
		SRP_LISTENER);
	if (!reserv) {

		/* Listener declaration is not known yet. */
		declaration = 0;
		reserv = srp_create_reservation(l_reserv->id, SRP_LISTENER,
			declaration, 0, mrp->id, 0);
		if (!reserv)
			return -ENOMEM;

		reserv->stream = stream;
		srp_insert_reservation(&info->declared, reserv);
	}

	/* Listener declaration will be updated in following call. */
	result = mrp_update_listener(mrp, reserv, stream);
	if (DEV_IOC_OK == result && started)
		result = DEV_IOC_MRP_REPORT;
	return result;
}  /* proc_mrp_tx_listener */

static int proc_mrp_lv_listener(struct mrp_info *mrp, u8 port,
	struct SRP_listener *listener)
{
	struct SRP_reservation *l_reserv;
	struct SRP_reservation *t_reserv;
	struct mrp_port_info *info = &mrp->port_info[port];
	int declaration;
	int result = DEV_IOC_OK;
	int started = 0;

dbg_msg("%s %d %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x %u\n", __func__, port,
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
		return result;

	/* Check if a talker reservation is using bandwidth. */
	t_reserv = srp_find_reservation(&info->declared, listener->id,
		SRP_TALKER);
	if (!t_reserv) {

		/* Delete listener reservation when leaving. */
		srp_remove_reservation(l_reserv);
		return result;
	}

	/* Remember the listener state. */
	declaration = l_reserv->declaration;

	t_reserv->pair = NULL;

	/* Delete listener reservation when leaving. */
	srp_remove_reservation(l_reserv);

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
	struct mrp_port_info *info = &mrp->port_info[port];

dbg_msg("%s %d %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x %u\n", __func__, port,
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
		result = proc_mrp_tx_listener(mrp, port, l_reserv, NULL,
			stream);
	}
	return result;
}  /* proc_mrp_rx_listener */

static int proc_mrp_tx_talker(struct mrp_info *mrp, u8 port,
	struct SRP_talker *talker)
{
	u8 declaration;
	u64 bandwidth;
	u8 tc;
	u8 code = talker->FailureCode;
	u32 latency = talker->AccumulatedLatency;
	struct SRP_stream *stream_id = NULL;
	struct SRP_stream *stream_dest;
	struct SRP_reservation *t_reserv;
	struct SRP_reservation *l_reserv;
	struct mrp_port_info *info = &mrp->port_info[port];
	int result = DEV_IOC_OK;

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

	stream_id = srp_find_stream_id(mrp, talker->id);
	stream_dest = srp_find_dest_addr(mrp, talker->dest);
	if (stream_id && !stream_dest)
		code = RFC_STREAM_ID_USED;
	else if (stream_dest && !stream_id)
		code = RFC_DEST_ADDR_USED;
	if (code)
		goto get_talker_done;

	bandwidth = calculate_bandwidth(talker->MaxFrameSize,
		talker->MaxIntervalFrames, frames_per_sec(tc));
dbg_msg(" t bw: %llu %u %u\n", bandwidth, info->bandwidth_max,
info->traffic[tc].bandwidth_max);
	if (bandwidth > info->traffic[tc].bandwidth_max)
		code = RFC_NO_BANDWIDTH_FOR_TRAFFIC_CLASS;
	else if (bandwidth > info->bandwidth_max)
		code = RFC_NO_BANDWIDTH;

get_talker_done:

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
	struct mrp_port_info *info = &mrp->port_info[port];
	int result = DEV_IOC_OK;
		int p;
	struct mrp_node *mac_node;
	struct mrp_node *vlan_node;
	struct mrp_vlan_info data;


dbg_msg("%s %d %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\n", __func__, port,
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
		srp_remove_reservation(l_reserv);

	for (p = 0; p <= mrp->ports; p++) {
		if (p == port)
			continue;

		info = &mrp->port_info[p];
		t_reserv = srp_find_reservation(&info->declared, talker->id,
			SRP_TALKER);
		if (!t_reserv)
{
dbg_msg("no talker reserv: %d\n", p);
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
			add_attrib_report(mrp, t_reserv, MRP_ACTION_LV,
				MRP_TYPE_TALKER, p);
			result = DEV_IOC_MRP_REPORT;
		} else
			srp_remove_reservation(t_reserv);
	}

	srp_cfg_reservation(mrp);

	/* This is purely used to free the stream after reporting. */
	if (!mrp->no_report)
		add_attrib_report(mrp, reserv, MRP_ACTION_LV, MRP_TYPE_TALKER,
			mrp->ports + 1);
	else {
		srp_remove_stream(mrp, reserv->stream);
		srp_remove_reservation(reserv);
	}

	mac_node = mrp_find_node(&mrp->mac_list, cmp_mac, talker->dest);
	if (mac_node) {
		struct mrp_mac_info *mac = NULL;

#ifdef DEBUG
		mrp_show_node(&mrp->mac_list, show_mac_info);
#endif
		mac = mac_node->data;
		mac->srp_ports &= ~(1 << 15);
		mac->ports = mac->srp_ports | mac->mrp_ports;
		mrp_cfg_dest_addr(mrp, mac->index, mac->addr, mac->ports);
		if (!mac->ports) {
			mrp_free_mac(mrp, mac->index);
			mrp_delete_node(&mrp->mac_list, cmp_mac, mac_node,
				true);
		}
	}
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
		vlan->ports &= ~(1 << 15);
		ports = mrp_find_vlan_ports(&mrp->vlan_list, data.vid, NULL);
		mrp_cfg_vlan(mrp, vlan->index, vlan->vid, ports);
		if (!ports)
			mrp_free_vlan(mrp, vlan->index);

		/* Nobody is using the VLAN. */
		if (!vlan->ports)
			mrp_delete_node(&mrp->vlan_list, cmp_vlan,
				vlan_node, true);
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
	struct mrp_port_info *info = &mrp->port_info[port];

dbg_msg("%s %d %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\n", __func__, port,
talker->id[0],
talker->id[1],
talker->id[2],
talker->id[3],
talker->id[4],
talker->id[5],
talker->id[6],
talker->id[7]);
dbg_msg("  %02x:%02x:%02x:%02x:%02x:%02x %04x %u %u:%u %u %u %u\n",
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

		/* Setup initial MAC configuration. */
		node = mrp_get_mac_info(&mrp->mac_list, talker->dest);
		if (!node)
			return -ENOMEM;
		mac = node->data;
		ports = mac->ports;
		mac->srp_ports = (1 << 15);
		mac->ports = mac->mrp_ports | mac->srp_ports;

		/* First time setting up MAC table. */
		if (!ports)
			mac->index = mrp_alloc_mac(mrp);

		/* Setup initial VLAN configuration. */
		node = mrp_get_vlan_info(&mrp->vlan_list, talker->vlan_id,
			talker->dest);
		if (!node)
			return -ENOMEM;
		vlan = node->data;
		ports = vlan->ports;
		vlan->ports = (1 << 15);

		/* First time setting up VLAN table. */
		if (!ports)
			vlan->index = mrp_alloc_vlan(mrp);
#ifdef DEBUG
		mrp_show_node(&mrp->mac_list, show_mac_info);
		mrp_show_node(&mrp->vlan_list, show_vlan_info);
#endif
	} else {
		reserv->declaration = declaration;
		reserv->latency = talker->AccumulatedLatency;
		memcpy(reserv->bridge_id, talker->bridge_id, 8);
		reserv->code = talker->FailureCode;
		if (port == mrp->ports)
			return result;
	}
	reserv->stream = stream;

	for (i = 0; i <= mrp->ports; i++) {
		if (i == port)
			continue;
		result = proc_mrp_tx_talker(mrp, i, talker);
		if (result < 0)
			return result;
	}
	return result;
}  /* proc_mrp_rx_talker */

static int proc_mrp_get_tx(struct mrp_info *mrp, struct mrp_cfg_options *cmd,
	int *output)
{
	struct mrp_report *attrib;
	struct SRP_reservation *reserv;
	struct SRP_stream *stream;
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
			kfree(info);
			kfree(node);
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
			kfree(info);
			kfree(node);
		}
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

			srp_remove_reservation(reserv);

			/* Special one to free the stream. */
			if (next && next->port == mrp->ports + 1) {
				reserv = next->attrib;
				srp_remove_stream(mrp, reserv->stream);
				srp_remove_reservation(reserv);

				kfree(attrib);
				attrib = next;
			}
		}
	}

	/* Assume there are more attributes to report. */
	mrp->report_head = attrib->next;
	if (mrp->report_tail == attrib) {
		mrp->report_tail = NULL;
		result = DEV_IOC_OK;
	}
	kfree(attrib);
	return result;
}  /* proc_mrp_get_tx */

static int proc_mrp_get_attribute(struct mrp_info *mrp, u8 *data, int *output)
{
	struct mrp_cfg_options *cmd = (struct mrp_cfg_options *) data;
	int result = DEV_IOC_OK;

	switch (cmd->type) {
	case MRP_TYPE_UNKNOWN:
		result = proc_mrp_get_tx(mrp, cmd, output);
		break;
	case MRP_TYPE_MAC:
		break;
	case MRP_TYPE_VLAN:
		break;
	case MRP_TYPE_DOMAIN:
		break;
	case MRP_TYPE_LISTENER:
		break;
	case MRP_TYPE_TALKER:
		break;
	}
	return result;
}  /* proc_mrp_get_attribute */

static int proc_mrp_set_attribute(struct mrp_info *mrp, u8 *data)
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
	case MRP_TYPE_DOMAIN:
		if (MRP_ACTION_RX == cmd->action)
			result = proc_mrp_rx_domain(mrp, port,
				&cmd->data.domain);
		else if (MRP_ACTION_LV == cmd->action)
			result = proc_mrp_lv_domain(mrp, port,
				&cmd->data.domain);
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
	}
	return result;
}  /* proc_mrp_set_attribute */

static void mrp_execute(struct mrp_info *mrp, struct work_struct *work)
{
	queue_work(mrp->access, work);
}  /* mrp_execute */

static int mrp_execute_wait(struct mrp_work *work)
{
	int rc = 0;

	mrp_execute(work->mrp, &work->work);
	wait_for_completion(&work->done);
	return rc;
}  /* mrp_execute_wait */

static void proc_mrp_work(struct work_struct *work)
{
	struct mrp_work *parent =
		container_of(work, struct mrp_work, work);
	struct mrp_info *mrp = parent->mrp;
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
			result = proc_mrp_set_attribute(mrp, data);
			break;
		default:
			result = DEV_IOC_INVALID_CMD;
			break;
		}
		break;
	case DEV_CMD_GET:
		switch (parent->subcmd) {
		case DEV_MRP_ATTRIBUTE:
			result = proc_mrp_get_attribute(mrp, data,
				&parent->output);
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
}  /* proc_mrp_work */

static int proc_mrp_hw_access(struct mrp_info *mrp, int cmd, int subcmd,
	int option, void *data, size_t len, int *output, int wait)
{
	struct mrp_access *access;
	struct mrp_work *work;
	int ret = 0;

	access = &mrp->hw_access;
	work = &access->works[access->index];
	if (work->used) {
		pr_alert("work full\n");
		return -EFAULT;
	}
	work->cmd = cmd;
	work->subcmd = subcmd;
	work->option = option;
	memcpy(work->param.data, data, len);
	work->used = true;
	access->index++;
	access->index &= MRP_WORK_LAST;
	init_completion(&work->done);
	if (!wait) {
		mrp_execute(mrp, &work->work);
		goto hw_access_end;
	}
	ret = mrp_execute_wait(work);

	/* Cannot continue if ERESTARTSYS. */
	if (ret < 0)
		return ret;

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

static void init_mrp_work(struct mrp_info *mrp)
{
	struct mrp_access *access;
	struct mrp_work *work;
	int i;

	access = &mrp->hw_access;
	for (i = 0; i < MRP_WORK_NUM; i++) {
		work = &access->works[i];
		work->mrp = mrp;
		INIT_WORK(&work->work, proc_mrp_work);
		init_completion(&work->done);
	}
}  /* init_mrp_work */



static int mrp_dev_req(struct mrp_info *mrp, char *arg)
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
	size_t param_size;

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

	switch (cmd->type) {
	case MRP_TYPE_MAC:
		param_size = SIZEOF_MRP_mac;
		break;
	case MRP_TYPE_VLAN:
		param_size = SIZEOF_MRP_vlan;
		break;
	case MRP_TYPE_DOMAIN:
		param_size = SIZEOF_SRP_domain_class;
		break;
	case MRP_TYPE_LISTENER:
		param_size = SIZEOF_SRP_listener;
		break;
	default:
		param_size = SIZEOF_SRP_talker;
		break;
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
					maincmd, subcmd, 0,
					data, 6, &output, true);
			} else
				result = DEV_IOC_INVALID_LEN;
			break;
		case DEV_INFO_EXIT:
			result = proc_mrp_hw_access(mrp,
				maincmd, subcmd, 0,
				data, 0, &output, true);

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
			result = proc_mrp_hw_access(mrp,
				maincmd, subcmd, 0,
				data, len, &output, true);
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
			result = proc_mrp_hw_access(mrp,
				maincmd, subcmd, 0,
				data, len, &output, true);
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

static u32 calculate_max_bandwidth(u32 speed, u32 percent)
{
	u32 bandwidth;

	bandwidth = speed;
	bandwidth *= percent;
	bandwidth /= 100;
	bandwidth *= NETWORK_SPEED_IN_MBIT;
	return bandwidth;
}  /* calculate_max_bandwidth */

static void mrp_set_bandwidth(struct mrp_port_info *info)
{
	u32 bandwidth;

	bandwidth = calculate_max_bandwidth(info->speed,
		info->bandwidth[SR_CLASS_A].deltaBandwidth +
		info->bandwidth[SR_CLASS_B].deltaBandwidth);
	info->bandwidth_max = bandwidth;
	info->bandwidth_left = bandwidth;

	bandwidth = calculate_max_bandwidth(info->speed,
		info->bandwidth[SR_CLASS_A].deltaBandwidth);
	info->traffic[SR_CLASS_A].bandwidth_max = bandwidth;
	info->traffic[SR_CLASS_A].bandwidth_left = bandwidth;

	bandwidth = calculate_max_bandwidth(info->speed,
		info->bandwidth[SR_CLASS_B].deltaBandwidth);
	bandwidth += info->traffic[SR_CLASS_A].bandwidth_left;
	info->traffic[SR_CLASS_B].bandwidth_max = bandwidth;
	info->traffic[SR_CLASS_B].bandwidth_left = bandwidth;
}  /* mrp_set_bandwidth */

static void mrp_set_speed(struct mrp_info *mrp, int port, u32 speed)
{
	struct mrp_port_info *info = &mrp->port_info[port];

	if (speed != info->speed) {
		if (speed) {
			info->speed = speed;
			mrp_set_bandwidth(info);
		}
	}
}  /* mrp_set_speed */

static void mrp_init(struct mrp_info *mrp)
{
	u8 port;
	u8 tc;
	struct mrp_port_info *info;
	struct ksz_sw *sw = container_of(mrp, struct ksz_sw, mrp);

	mrp->access = create_singlethread_workqueue("mrp_access");
	init_mrp_work(mrp);
	mutex_init(&mrp->lock);

	mrp->ports = sw->mib_port_cnt - 1;

	mrp->id[0] = 0x01;
	mrp->id[1] = 0x80;
	mrp->id[2] = 0xA6;
	mrp->id[3] = 0x98;
	mrp->id[4] = 0x97;
	mrp->id[5] = 0x01;
	mrp->id[6] = 0x01;
	mrp->id[7] = 0x01;
	mrp->max_interference_size = 9000;
	mrp->tc[2] = SR_CLASS_B;
	mrp->tc[3] = SR_CLASS_A;
	mrp->prio[SR_CLASS_A] = 3;
	mrp->prio[SR_CLASS_B] = 2;

	mrp_init_list(&mrp->mac_down);
	mrp_init_list(&mrp->mac_up);
	mrp_init_list(&mrp->vlan_down);
	mrp_init_list(&mrp->vlan_up);

	mrp_init_list(&mrp->mac_list);
	mrp_init_list(&mrp->vlan_list);

	for (port = 0; port <= mrp->ports; port++) {
		info = &mrp->port_info[port];
		info->speed = 100;

		info->bandwidth[SR_CLASS_A].traffic_class = 3;
		info->bandwidth[SR_CLASS_A].deltaBandwidth = 50;
		info->bandwidth[SR_CLASS_A].adminIdleSlope = 0;

		info->bandwidth[SR_CLASS_B].traffic_class = 2;
		info->bandwidth[SR_CLASS_B].deltaBandwidth = 25;
		info->bandwidth[SR_CLASS_B].adminIdleSlope = 0;

		for (tc = 0; tc < 4; tc++)
			info->algorithm[tc].traffic_class = tc;
		info->algorithm[2].algorithm = 1;
		info->algorithm[3].algorithm = 1;

		mrp_set_bandwidth(info);
dbg_msg("bw: %d %u; %u %u; %u %u\n", port, info->bandwidth_left,
	info->traffic[SR_CLASS_A].bandwidth_max,
	info->traffic[SR_CLASS_A].bandwidth_left,
	info->traffic[SR_CLASS_B].bandwidth_max,
	info->traffic[SR_CLASS_B].bandwidth_left);

		mrp_init_list(&info->active);
		mrp_init_list(&info->passive);
#ifdef CONFIG_HAVE_KSZ9897
	do {
		int queue = 3;
		u16 credit;
		u16 credit_hi;
		u16 credit_lo;
		u8 schedule;
		u8 shaping;

		sw->reg->lock(sw);
		credit_hi = port_get_hi_water_mark(sw, port, queue);
		credit_lo = port_get_lo_water_mark(sw, port, queue);
		credit = port_get_increment(sw, port, queue);
		schedule = port_get_schedule_mode(sw, port, queue);
		shaping = port_get_shaping(sw, port, queue);
		for (queue = 0; queue < 4; queue++)
			port_set_schedule_mode(sw, port, queue,
				MTI_SCHEDULE_STRICT_PRIO);
		sw->reg->unlock(sw);
dbg_msg("%d %x %x %x %u %u\n", port,
credit, credit_hi, credit_lo, schedule, shaping);
	} while (0);
#endif
	}
}  /* mrp_init */

static void mrp_exit(struct mrp_info *mrp)
{
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

