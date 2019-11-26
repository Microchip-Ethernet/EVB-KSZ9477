/**
 * Microchip MRP driver code
 *
 * Copyright (c) 2015-2019 Microchip Technology Inc.
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


/* CONFIG_KSZ_AVB enables hardware bandwidth programming.
   CONFIG_KSZ_MRP enables MMRP and MVRP.
   CONFIG_KSZ_MSRP enables MSRP.  Needs CONFIG_KSZ_AVB and CONFIG_KSZ_MRP.
*/

#if !defined(CONFIG_KSZ_AVB) || !defined(CONFIG_KSZ_MRP)
#undef CONFIG_KSZ_MSRP
#endif

#ifdef CONFIG_KSZ_MRP
#if 0
#define DEBUG_MRP_MEM
#endif
#if 1
#define DEBUG_MRP_OPER
#endif
#if 1
#define DEBUG_MVRP
static int dbg_mrp_vlan = 1;
#endif
#if 1
#define DEBUG_MSRP
#endif
#endif

#if 1
#ifdef CONFIG_KSZ_MRP
static int mrp_10_1_2f_hack;
static int fqtss_hack;
static int fqtss_34_2_3_hack;
#endif
#ifdef CONFIG_KSZ_MSRP
static int mrp_10_1_8a_hack;
static int mrp_10_5_1_hack;
static int mrp_10_5_1c_hack;
static int mrp_10_5_1d_hack;
static int msrp_35_1_14g_hack;
static int fqtss_34_2_1b_hack;
static int fqtss_34_2_5b_hack;
static int fqtss_34_2_9b_hack;
static int regeneration_hack;
#endif
#endif


static const u8 bcast_addr[] = {
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
};

static const u8 maap_addr[][6] = {
	/* Used by MAAP. */
	{ 0x91, 0xE0, 0xF0, 0x00, 0xFF, 0x00 },
	/* Used by AVB Discovery Protocol. */
	{ 0x91, 0xE0, 0xF0, 0x01, 0x00, 0x00 },
	/* Used by AVB AECP Test Status Message. */
	{ 0x01, 0x1B, 0xC5, 0x0A, 0xC0, 0x00 },

	/* This is sent by Mac and contains only a repeat of these bytes!? */
	{ 0xAB, 0xBA, 0xCA, 0xFE, 0xBE, 0xEF },
};

#define BCAST_DA_ACL_ENTRY		10
#define AVB_BOUNDARY_ACL_ENTRY		11

struct avtpdu {
	u8 subtype;
#ifdef __BIG_ENDIAN_BITFIELD
	u8 sv:1;
	u8 version:3;
	u8 mr:1;
	u8 fsd:2;
	u8 tv:2;
#else
	u8 tv:2;
	u8 fsd:2;
	u8 mr:1;
	u8 version:3;
	u8 sv:1;
#endif
	u8 seq_num;
#ifdef __BIG_ENDIAN_BITFIELD
	u8 format_spec_data_1:7;
	u8 tu:1;
#else
	u8 tu:1;
	u8 format_spec_data_1:7;
#endif
	u8 stream_id[8];
	u32 avtp_timestamp;
	u32 format_spec_data_2;
	u16 stream_data_len;
	u16 format_spec_data_3;
} __packed;

struct avtpdu_ctrl {
#ifdef __BIG_ENDIAN_BITFIELD
	u32 subtype:8;
	u32 sv:1;
	u32 version:3;
	u32 format_spec_data:9;
	u32 ctrl_data_len:11;
#else
	u32 ctrl_data_len:11;
	u32 format_spec_data:9;
	u8 version:3;
	u8 sv:1;
	u32 subtype:8;
#endif
	u8 stream_id[8];
} __packed;

struct maap_pdu {
	u8 subtype;
#ifdef __BIG_ENDIAN_BITFIELD
	u8 sv:1;
	u8 version:3;
	u8 message_type:4;
	u16 maap_version:5;
	u16 ctrl_data_len:11;
#else
	u8 message_type:4;
	u8 version:3;
	u8 sv:1;
	union {
		struct {
			u16 ctrl_data_len:11;
			u16 maap_version:5;
		} __packed data_len;
		u16 data;
	} __packed len;
#endif
	u8 stream_id[8];
	u8 req_start_addr[6];
	u16 req_cnt;
	u8 conflict_start_addr[6];
	u16 conflict_cnt;
} __packed;

#define AVTP_SUBTYPE_AAF		0x02
#define AVTP_SUBTYPE_CVF		0x03
#define AVTP_SUBTYPE_CRF		0x04
#define AVTP_SUBTYPE_TSCF		0x05
#define AVTP_SUBTYPE_SVF		0x06
#define AVTP_SUBTYPE_RVF		0x07
#define AVTP_SUBTYPE_VSF_STREAM		0x6F
#define AVTP_SUBTYPE_EF_STREAM		0x7F
#define AVTP_SUBTYPE_NTSCF		0x82
#define AVTP_SUBTYPE_ADP		0xFA
#define AVTP_SUBTYPE_AECP		0xFB
#define AVTP_SUBTYPE_ACMP		0xFC
#define AVTP_SUBTYPE_MAAP		0xFE
#define AVTP_SUBTYPE_EF_CONTROL		0xFF

#ifdef CONFIG_KSZ_AVB
static struct mrp_port_info *mrp_get_port_info(struct mrp_info *mrp, u8 port)
{
	return &mrp->port_info[port];
}  /* mrp_get_port_info */

static void setup_acl_drop(struct mrp_info *mrp, uint port)
{
	struct ksz_sw *sw = mrp->parent;
	struct ksz_port_cfg *cfg = get_port_cfg(sw, port);
	struct ksz_acl_table *acl;
	int i = BCAST_DA_ACL_ENTRY;

	mutex_lock(&sw->acllock);

	acl = &cfg->acl_info[i];
	acl->mode = ACL_MODE_LAYER_2;
	acl->enable = ACL_ENABLE_2_BOTH;
	acl->equal = 1;
	acl->src = 0;
	memcpy(acl->mac, bcast_addr, ETH_ALEN);
	acl->eth_type = 0x22F0;

	acl->first_rule = i;
	acl->ruleset = (1 << i);
	acl->ruleset = 0;

	acl->map_mode = ACL_MAP_MODE_REPLACE;
	acl->ports = 0;
	sw_w_acl_table(sw, port, i, acl);

	mutex_unlock(&sw->acllock);
}  /* setup_acl_drop */

static void setup_acl_remap(struct mrp_info *mrp, uint port)
{
	struct ksz_sw *sw = mrp->parent;
	struct ksz_port_cfg *cfg = get_port_cfg(sw, port);
	struct mrp_port_info *info = mrp_get_port_info(mrp, port);
	struct ksz_acl_table *acl;
	int i = AVB_BOUNDARY_ACL_ENTRY;

	mutex_lock(&sw->acllock);

	acl = &cfg->acl_info[i];
	acl->mode = ACL_MODE_LAYER_2;
	acl->enable = ACL_ENABLE_2_TYPE;
	acl->equal = 1;
	acl->eth_type = 0x22F0;

#ifdef CONFIG_KSZ_MSRP
	if (regeneration_hack) {
		acl->eth_type = 0;
		acl->equal = 0;
	}
#endif

	acl->first_rule = i;
	acl->ruleset = (1 << i);

	acl->map_mode = ACL_MAP_MODE_DISABLE;
	acl->ports = 0;
	acl->prio_mode = ACL_PRIO_MODE_REPLACE;
	acl->prio = info->priority[SR_CLASS_B].regenerated_priority;
	acl->vlan_prio_replace = 1;
	acl->vlan_prio = info->priority[SR_CLASS_B].regenerated_priority;
	sw_w_acl_table(sw, port, i, acl);

	mutex_unlock(&sw->acllock);
}  /* setup_acl_remap */

static void enable_acl_remap(struct mrp_info *mrp, uint port, bool remap,
			     bool drop)
{
	struct ksz_sw *sw = mrp->parent;
	struct ksz_port_cfg *cfg = get_port_cfg(sw, port);
	struct ksz_acl_table *acl;
	int i = AVB_BOUNDARY_ACL_ENTRY;

	mutex_lock(&sw->acllock);

	acl = &cfg->acl_info[i];
dbg_msg(" remap: %d=%d-%d %d:%d"NL, port, remap, drop, cfg->avb_a, cfg->avb_b);
	if (remap)
		acl->ruleset = (1 << i);
	else
		acl->ruleset = 0;
	sw_w_acl_ruleset(sw, port, i, acl);

	i = BCAST_DA_ACL_ENTRY;
	acl = &cfg->acl_info[i];
	if (drop)
		acl->ruleset = (1 << i);
	else
		acl->ruleset = 0;
	sw_w_acl_ruleset(sw, port, i, acl);

	mutex_unlock(&sw->acllock);
	sw->ops->acquire(sw);
	if (drop) {
		if (!(mrp->mcast_ports & (1 << port))) {
			mrp->mcast_ports |= (1 << port);
			if (!mrp->mcast_port_cnt)
				sw->ops->fwd_unk_mcast(sw, true);
			mrp->mcast_port_cnt++;
		}
	} else {
		if (mrp->mcast_ports & (1 << port)) {
			mrp->mcast_ports &= ~(1 << port);
			mrp->mcast_port_cnt--;
			if (!mrp->mcast_port_cnt)
				sw->ops->fwd_unk_mcast(sw, false);
		}
	}
	sw->ops->release(sw);
}  /* enable_acl_remap */

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

static char *format_per(char *str, u32 per, bool verbose)
{
	u64 val;
	u32 num;
	u32 num0;
	u32 num1;

	val = per;
	val *= 1000;
	val += 1 << (CREDIT_PERCENTAGE_S - 1);
	val >>= CREDIT_PERCENTAGE_S;
	num = (u32) val;
	num0 = num % 1000;
	num1 = num / 1000;
	if (num1)
		sprintf(str, "%u.%03u", num1, num0);
	else
		sprintf(str, "0.%03u", num0);
	if (verbose)
		strcpy(str, PER_CHAR);
	return str;
}  /* format_per */

static u16 get_credit_increment(u32 speed, u32 bandwidth)
{
	u64 val;

	speed *= NETWORK_SPEED_IN_MBIT;

	/* Cannot get higher than the running speed. */
	if (bandwidth > speed)
		return 0;
	val = bandwidth;
	val <<= SW_CREDIT_SHAPING_S;
	val += speed / 2;
	val = div_u64_u32(val, speed);

	/* Cannot become zero. */
	if (!val)
		val = 1;
	return (u16) val;
}  /* get_credit_increment */

static u16 get_credit_watermark(u16 size)
{
	/* Preamable + vlan_ethhdr + CRC + IFG = 42 */
	size += 8 + 14 + 4 + 4 + 12;
	return size;
}  /* get_credit_watermark */

static u32 get_idle_slope(u32 speed, u32 bandwidth)
{
	u64 val;

	speed *= NETWORK_SPEED_IN_MBIT;

	/* Cannot get higher than the running speed. */
	if (bandwidth > speed)
		return 0;
	val = bandwidth;
	val *= 100;
	val <<= CREDIT_PERCENTAGE_S;
	val = div_u64_u32(val, speed);
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
	return mrp->queue[tc];
}  /* get_queue_priority */

static void srp_cfg_credit_shaper(struct mrp_info *mrp, uint port,
	struct mrp_port_info *info, struct mrp_traffic_info *traffic)
{
	u16 credit;
	u32 idle;
	u32 send;
	u8 queue;
#ifdef DEBUG_MRP_OPER
	char bw_str[20];
	char idle_str[20];
	char send_str[20];
#endif
	struct ksz_sw *sw = mrp->parent;

	if (!(sw->features & AVB_SUPPORT))
		return;
	credit = get_credit_increment(info->speed, traffic->bandwidth_used);
	idle = get_idle_slope(info->speed, traffic->bandwidth_used);
	send = get_send_slope(idle);
	queue = traffic->queue;
	info->bandwidth[traffic->queue].operIdleSlope = idle;

#ifdef DEBUG_MRP_OPER
	format_num(bw_str, traffic->bandwidth_used);
	format_per(idle_str, idle, true);
	format_per(send_str, send, true);
dbg_msg("  %s %d:%d=%u; %s %s %s"NL, __func__, port,
	queue, credit,
	bw_str, idle_str, send_str);
#endif

#if defined(CONFIG_HAVE_KSZ9897) || defined(CONFIG_HAVE_LAN937X)
	do {
		if (credit < 2)
			credit = info->credit[queue];
		sw->reg->lock(sw);
		if (credit > 1) {
			port_set_increment(sw, port, queue, credit);
#if 0
			port_set_schedule_mode(sw, port, queue,
				MTI_SCHEDULE_STRICT_PRIO);
			port_set_shaping(sw, port, queue, MTI_SHAPING_SRP);
#endif
		} else {
#if 0
			port_set_schedule_mode(sw, port, queue,
				MTI_SCHEDULE_WRR);
			port_set_shaping(sw, port, queue, MTI_SHAPING_OFF);
#endif
		}
		sw->reg->unlock(sw);
	} while (0);
#endif
}  /* srp_cfg_credit_shaper */

static void srp_cfg_idle_slope(struct mrp_info *mrp, uint port, uint queue,
	struct mrp_port_info *info, u32 idle)
{
	u16 credit;
	u16 credit_lo;
	u16 credit_hi;
	u32 send;
	u64 idle_slope;
#if 0
	char bw_str[20];
	char idle_str[20];
	char send_str[20];
#endif
	struct ksz_sw *sw = mrp->parent;

	idle_slope = info->speed;
	idle_slope *= NETWORK_SPEED_IN_MBIT;
	idle_slope *= idle;
	send = 100;
	send <<= CREDIT_PERCENTAGE_S;
	idle_slope = div_u64_u32(idle_slope, send);

	credit = get_credit_increment(info->speed, idle_slope);
	info->credit[queue] = credit;
	send = get_send_slope(idle);
	credit_hi = get_credit_watermark(mrp->max_interference_size);
	credit_lo = get_credit_watermark(1500);
#if 0
	format_num(bw_str, idle_slope);
	format_per(idle_str, idle, true);
	format_per(send_str, send, true);
dbg_msg("  %s %d:%d=%u %u %u; %s %s %s"NL, __func__, port,
	queue, credit, credit_hi, credit_lo,
	bw_str, idle_str, send_str);
#endif

#if defined(CONFIG_HAVE_KSZ9897) || defined(CONFIG_HAVE_LAN937X)
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
#endif
}  /* srp_cfg_idle_slope */

static u32 calculate_max_bandwidth(u32 speed, u32 percent)
{
	u64 bandwidth;

	bandwidth = speed;
	bandwidth *= percent;
	bandwidth *= NETWORK_SPEED_IN_MBIT;
	bandwidth = div_u64_u32(bandwidth, 100);
	return (u32) bandwidth;
}  /* calculate_max_bandwidth */

static int get_traffic_index(int tc)
{
	if (SR_CLASS_A == tc)
		return 1;
	return 0;
}

static struct mrp_traffic_info *get_traffic_info(struct mrp_port_info *port,
	int tc)
{
	if (SR_CLASS_A == tc)
		return &port->traffic[1];
	else
		return &port->traffic[0];
}  /* get_traffic_info */
#endif

#ifdef CONFIG_KSZ_MRP
static void mrp_cfg_dest_addr(struct mrp_info *mrp, u8 index, u8 *dest,
	u32 ports, u16 fid)
{
	struct ksz_sw *sw = mrp->parent;

#ifdef DEBUG_MRP_OPER
dbg_msg("  %s %d=%02x:%02x:%02x:%02x:%02x:%02x %04x %x"NL, __func__, index,
dest[0], dest[1], dest[2], dest[3], dest[4],dest[5],
ports, fid);
#endif
	ports &= SRP_PORT_AVAIL | SRP_PORT_READY;
	sw->ops->cfg_mac(sw, index, dest, ports, false, fid != 0, fid);
}  /* mrp_cfg_dest_addr */

static void mrp_cfg_vlan(struct mrp_info *mrp, u8 index, u16 vid, u16 fid,
	u32 ports)
{
	struct ksz_sw *sw = mrp->parent;

#ifdef DEBUG_MVRP
if (dbg_mrp_vlan || vid == 2 || vid > 4090)
dbg_msg("  %s %d=%x %x %04x"NL, __func__, index, vid, fid, ports);
#endif
	ports &= SRP_PORT_AVAIL | SRP_PORT_READY;

#if 0
	/* Needed to catch unwanted multicast traffic. */
	if (ports)
		ports |= sw->HOST_MASK;
#endif
	sw->ops->cfg_vlan(sw, index, vid, fid, ports);
}  /* mrp_cfg_vlan */

#if 0
static int mrp_req_cfg_vlan(struct mrp_info *mrp, u8 index, u16 vid, u16 fid,
	u32 ports)
{
	struct sk_buff *skb;
	u16 *data;
	u32 *dword;

	skb = alloc_skb(64, GFP_ATOMIC);
	if (!skb)
		return -ENOMEM;

	data = (u16 *)skb->data;
	*data++ = index;
	*data++ = vid;
	*data++ = fid;
	dword = (u32 *)data;
	*dword = ports;
	skb_queue_tail(&mrp->vlanq, skb);
	if (!mrp->vlanq_sched) {
		mrp->vlanq_sched = 1;
		schedule_work(&mrp->cfg_vlan);
	}
	return 0;
}  /* mrp_req_cfg_vlan */
#endif

static void mrp_cfg_vlan_work(struct work_struct *work)
{
#ifdef DEBUG_MVRP
	int save_dbg_vlan;
#endif
	u16 *data;
	u32 *dword;
	u8 index;
	u16 vid;
	u16 fid;
	u32 ports;
	bool last;
	struct sk_buff *skb;
	struct mrp_info *mrp = container_of(work, struct mrp_info, cfg_vlan);

	last = skb_queue_empty(&mrp->vlanq);
	while (!last) {
		skb = skb_dequeue(&mrp->vlanq);
		last = skb_queue_empty(&mrp->vlanq);
		if (!skb)
			continue;
		data = (u16 *)skb->data;
		index = (u8) *data++;
		vid = *data++;
		fid = *data++;
		dword = (u32 *)data;
		ports = *dword;
#ifdef DEBUG_MVRP
		save_dbg_vlan = dbg_mrp_vlan;
		dbg_mrp_vlan = 0;
#endif
		mrp_cfg_vlan(mrp, index, vid, fid, ports);
#ifdef DEBUG_MVRP
		dbg_mrp_vlan = save_dbg_vlan;
#endif
		kfree_skb(skb);
	}
	mrp->vlanq_sched = 0;
}  /* mrp_cfg_vlan_work */

static int cmp_mac(void *first, void *second)
{
	int cmp;
	struct mrp_mac_info *a = first;
	struct mrp_mac_info *b = second;

#if 0
dbg_msg("%s %02x:%02x:%02x:%02x:%02x:%02x=%x %02x:%02x:%02x:%02x:%02x:%02x=%x"NL, __func__,
a->addr[0], a->addr[1], a->addr[2], a->addr[3], a->addr[4], a->addr[5], a->fid,
b->addr[0], b->addr[1], b->addr[2], b->addr[3], b->addr[4], b->addr[5], b->fid);
#endif
	cmp = a->fid - b->fid;
	if (!cmp)
		cmp = memcmp(a->addr, b->addr, ETH_ALEN);
	return cmp;
}  /* cmp_mac */

static void show_mac_info(void *this)
{
	struct mrp_mac_info *info = this;

	dbg_msg(
		"%02x:%02x:%02x:%02x:%02x:%02x %d=%03x r:%04x s:%04x t:%04x"NL,
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
		"%d=%03x.%03x r:%04x t:%04x"NL, info->index,
		info->vid, info->fid, info->ports, info->tx_ports);
}  /* show_vlan_info */

#ifdef CONFIG_KSZ_MSRP
static int get_traffic_class(struct mrp_info *mrp, u8 prio)
{
	return mrp->tc[prio];
}  /* get_traffic_class */

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

	/* Mininum frame size is 68. */
#if 1
	if (size < 46 && fqtss_34_2_5b_hack)
		size = 46 - 4;
	else
#endif
	if (size < 46)
		size = 46;
#if 1
	if (size < 100 && fqtss_34_2_9b_hack)
		size = 100;
#endif
	bandwidth = size;

	/* Preamable + vlan_ethhdr + CRC + IFG */
	bandwidth += 8 + 14 + 4 + 4 + 12;

	/* AVnu MSRP test says to add one more byte for bridge. */
	bandwidth += 1;
	bandwidth *= interval;
	bandwidth *= frames;
	bandwidth *= 8;
	return bandwidth;
}  /* calculate_bandwidth */

static u64 get_stream_age(struct mrp_port_info *info)
{
	struct timespec ts;
	u64 age;

	ts = ktime_to_timespec(ktime_get_real());
	age = ts.tv_sec;
	age *= 1000000000;
	age += ts.tv_nsec;
	if (age == info->age)
		age++;
	info->age = age;
	return age;
}

static void prepare_stream_info(struct SRP_reserv *reserv,
				struct srp_stream_info *x)
{
	x->reserv = reserv;
	x->id = reserv->stream->id;
	x->age = reserv->streamAge;
	x->rank = reserv->stream->rank;
}  /* prepare_stream_info */

static int cmp_stream(struct srp_stream_info *a, struct srp_stream_info *b)
{
	int cmp;

	/* Only rank and stream age are compared. */
	cmp = a->rank - b->rank;
	if (cmp)
		return cmp;

	if (a->age > b->age)
		return 1;
	else if (a->age < b->age)
		return -1;
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
		"r:%u t:%08llx %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x"NL,
		info->rank, info->age,
		info->id[0], info->id[1], info->id[2], info->id[3],
		info->id[4], info->id[5], info->id[6], info->id[7]);
}  /* show_stream_info */
#endif

#ifdef DEBUG_MRP_BASIC
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
#ifdef DEBUG_MRP_BASIC
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
#ifdef DEBUG_MRP_BASIC
dbg_msg(" %s ", __func__);
		if (next) {
			void (*show)(void *this) = get_show(cmp);

			show(next->data);
		} else
dbg_msg("last one"NL);
#endif
		c = 1;
		if (next) {
			c = cmp(next->data, this->data);
		}
		if (c > 0) {
			this->next = prev->next;
			prev->next = this;
			list->last = &list->anchor;
			list->cnt++;
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
	list->cnt++;
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
#ifdef DEBUG_MRP_BASIC
dbg_msg(" %s ", __func__);
		if (next) {
			void (*show)(void *this) = get_show(cmp);

			show(next->data);
		} else
dbg_msg("last one"NL);
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
	list->cnt--;

	/* Just remove the node. */
	if (!delete)
		return next;

	/* Free the node data. */
#ifdef DEBUG_MRP_MEM
if (delete > 1)
dbg_msg(" %s %p"NL, __func__, next->data);
#endif
	if (delete > 1)
		kfree(next->data);

#ifdef DEBUG_MRP_MEM
dbg_msg(" %s %p"NL, __func__, next);
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
#endif

#ifdef CONFIG_KSZ_MSRP
static struct SRP_stream *srp_create_stream(u8 *id, u8 *dest, u16 vlan_id,
	u16 size, u16 interval, u8 prio, u8 rank, u8 reserved, u32 latency)
{
	struct SRP_stream *stream;

	stream = kzalloc(sizeof(struct SRP_stream), GFP_KERNEL);
#ifdef DEBUG_MRP_MEM
dbg_msg(" %s %p"NL, __func__, stream);
#endif
	if (stream) {
		memcpy(stream->id, id, 8);
		memcpy(stream->dest, dest, ETH_ALEN);
		stream->vlan_id = vlan_id;
		stream->MaxFrameSize = size;
		stream->MaxIntervalFrames = interval;
		stream->priority = prio;
		stream->rank = rank;
		stream->reserved = reserved;
		stream->latency = latency;
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
dbg_msg(" %s %p %d"NL, __func__, stream, free);
#endif
	if (free)
		kfree(stream);
}  /* srp_remove_stream */

static struct SRP_reserv *srp_create_reserv(u8 *id, u8 dir, u8 dec,
					    u32 latency, const u8 *bridge_id,
					    u8 code)
{
	struct SRP_reserv *reserv;

	reserv = kzalloc(sizeof(struct SRP_reserv), GFP_KERNEL);
#ifdef DEBUG_MRP_MEM
dbg_msg(" %s %p"NL, __func__, reserv);
#endif
	if (reserv) {
		memcpy(reserv->id, id, 8);
		reserv->direction = dir;
		reserv->declaration = dec;
		reserv->latency = latency;
		memcpy(reserv->bridge_id, bridge_id, 8);
		reserv->code = code;
		reserv->rx_code = code;
		reserv->ticks = jiffies;
	}
	return reserv;
}  /* srp_create_reserv */

static struct SRP_reserv *srp_find_reserv(struct SRP_reserv *head, u8 *id,
					  u8 dir)
{
	int cmp;
	struct SRP_reserv *reserv;

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
}  /* srp_find_reserv */

static void srp_insert_reserv(struct SRP_reserv *head,
			      struct SRP_reserv *reserv)
{
	int cmp;
	struct SRP_reserv *prev;
	struct SRP_reserv *next;

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
}  /* srp_insert_reserv */

static void srp_remove_reserv(struct SRP_reserv *reserv, int free)
{
	if (reserv->next)
		reserv->next->prev = reserv->prev;
	reserv->prev->next = reserv->next;
#ifdef DEBUG_MRP_MEM
dbg_msg(" %s %p %d"NL, __func__, reserv, free);
#endif
	if (free)
		kfree(reserv);
}  /* srp_remove_reserv */

static void chk_reserv(struct mrp_port_info *info, uint port)
{
	struct SRP_reserv *reserv;
	int tc;
	struct mrp_traffic_info *traffic;

#if 0
	if (!info->link)
#else
	if (!info->link && port > 2)
#endif
		return;
dbg_msg("%d %d:"NL, info->index, port);
dbg_msg("  registered: %p"NL, &info->registered);
	reserv = info->registered.next;
	while (reserv) {
dbg_msg("%p %02x:%02x:%02x %d %d %02d=%04x"NL, reserv,
reserv->id[5], reserv->id[6], reserv->id[7], reserv->direction,
	reserv->declaration, reserv->code, reserv->code_bits);
		reserv = reserv->next;
	}
dbg_msg("  declared: %p"NL, &info->declared);
	reserv = info->declared.next;
	while (reserv) {
dbg_msg("%p %02x:%02x:%02x %d %d %02d=%04x"NL, reserv,
reserv->id[5], reserv->id[6], reserv->id[7], reserv->direction,
	reserv->declaration, reserv->code, reserv->code_bits);
		reserv = reserv->next;
	}
	for (tc = SR_CLASS_A; tc >= SR_CLASS_B; tc--) {
		traffic = get_traffic_info(info, tc);
dbg_msg("  active:"NL);
		mrp_show_node(&traffic->active, show_stream_info);
#if 1
dbg_msg("  passive:"NL);
		mrp_show_node(&traffic->passive, show_stream_info);
dbg_msg("m=%u u=%u l=%u"NL,
		traffic->bandwidth_max,
		traffic->bandwidth_used,
		traffic->bandwidth_left);
#endif
	}
dbg_msg("T:%u"NL, info->bandwidth_used);
dbg_msg(NL);
}  /* chk_reserv */
#endif

#ifdef CONFIG_KSZ_MRP
static struct mrp_node *mrp_alloc_node(size_t data_size)
{
	struct mrp_node *node;

	node = kzalloc(sizeof(struct mrp_node), GFP_KERNEL);
#ifdef DEBUG_MRP_MEM
dbg_msg(" %s %p %u"NL, __func__, node, data_size);
#endif
	if (!node)
		return NULL;
	node->data = kzalloc(data_size, GFP_KERNEL);
#ifdef DEBUG_MRP_MEM
dbg_msg(" %s %p"NL, __func__, node->data);
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
dbg_msg(" %s %p %p"NL, __func__, node->data, node);
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

#if 0
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
		} else if (vid < info->vid)
			break;
		prev = next;
		next = prev->next;
	}
	return ports;
}  /* mrp_find_vlan_ports */
#endif

static struct mrp_report *mrp_create_report(struct SRP_reserv *reserv,
	u8 port)
{
	struct mrp_report *attrib;

	attrib = kzalloc(sizeof(struct mrp_report), GFP_KERNEL);
#ifdef DEBUG_MRP_MEM
dbg_msg(" %s %p"NL, __func__, attrib);
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
	struct ksz_sw *sw = mrp->parent;

	return sw->ops->alloc_mac(sw);
}  /* mrp_alloc_mac */

static void mrp_free_mac(struct mrp_info *mrp, u8 index)
{
	struct ksz_sw *sw = mrp->parent;

	sw->ops->free_mac(sw, index);
}  /* mrp_free_mac */

static u8 mrp_alloc_vlan(struct mrp_info *mrp)
{
	struct ksz_sw *sw = mrp->parent;

	return sw->ops->alloc_vlan(sw);
}  /* mrp_alloc_vlan */

static void mrp_free_vlan(struct mrp_info *mrp, u8 index)
{
	struct ksz_sw *sw = mrp->parent;

	sw->ops->free_vlan(sw, index);
}  /* mrp_free_vlan */

static u16 mrp_alloc_fid(struct mrp_info *mrp, u16 vid)
{
	struct ksz_sw *sw = mrp->parent;

	return sw->ops->alloc_fid(sw, vid);
}  /* mrp_alloc_fid */

static void mrp_free_fid(struct mrp_info *mrp, u16 fid)
{
	struct ksz_sw *sw = mrp->parent;

	sw->ops->free_fid(sw, fid);
}  /* mrp_free_fid */

#ifdef CONFIG_KSZ_MSRP
static u16 mrp_get_fid(struct mrp_info *mrp, u16 vid, u8 *addr)
{
	struct mrp_node *node;
	struct mrp_vlan_info data;
	u16 fid = 0;

	data.vid = vid;
#if 0
	memcpy(data.addr, addr, ETH_ALEN);
#else
	memset(data.addr, 0xFF, ETH_ALEN);
#endif
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
	uint n;
	uint p;
	struct ksz_sw *sw = mrp->parent;
	int result = DEV_IOC_OK;

#ifdef DEBUG_MVRP
if (dbg_mrp_vlan)
#endif
dbg_msg(" %s %x %x"NL, __func__, ports, *tx_ports);
	if (!ports) {

		/* Ask all ports to withdraw the declaration. */
		for (n = 0; n <= mrp->ports; n++) {
			p = get_phy_port(sw, n);
			if (*tx_ports & (1 << p)) {
				add_attrib_report(mrp, node,
					MRP_ACTION_LV, type, p);
			}
		}
		*tx_ports = 0;
	} else {
		uint uninitialized_var(q);
		int cnt = 0;

		for (n = 0; n <= mrp->ports; n++) {
			p = get_phy_port(sw, n);
			if (ports & (1 << p)) {
				q = p;
				cnt++;
			}
		}
		if (1 == cnt) {
			*tx_ports &= ~(1 << q);
			add_attrib_report(mrp, node, MRP_ACTION_LV, type, q);
		}
	}
	if (mrp->report_head)
		result = DEV_IOC_MRP_REPORT;
	return result;
}  /* proc_mrp_lv */

static int proc_mrp_lv_mac(struct mrp_info *mrp, uint port,
	struct MRP_mac *mac)
{
	struct mrp_node *node;
	struct mrp_mac_info data;
	struct mrp_mac_info *info;
	u16 mrp_ports;
	u16 ports;
	uint m = BIT(port);
	int result = DEV_IOC_OK;

dbg_msg(" %s %d=%02x:%02x:%02x:%02x:%02x:%02x"NL, __func__, port,
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
	info->rx_ports &= ~m;
	info->mrp_ports &= ~m;
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

static int proc_mrp_rx_mac(struct mrp_info *mrp, uint port,
	struct MRP_mac *mac, u8 new_decl)
{
	struct mrp_node *node;
	struct mrp_mac_info *info;
	u16 mrp_ports;
	u16 ports;
	uint n;
	uint q;
	uint m = BIT(port);
	struct ksz_sw *sw = mrp->parent;
	int result = DEV_IOC_OK;

dbg_msg(" %s %d=%d %02x:%02x:%02x:%02x:%02x:%02x"NL, __func__, port,
	new_decl,
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
	info->rx_ports |= m;
	info->srp_ports &= ~SRP_PORT_BLACKLIST;
	info->ports &= ~SRP_PORT_BLACKLIST;
	mrp_ports = info->mrp_ports;
	ports = info->ports;
	if (new_decl & 0x80)
		new_decl &= ~0x80;
	else
		info->mrp_ports |= m;
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

	if (!new_decl) {
		struct ksz_sw *sw = mrp->parent;

		if (sw->ops->get_tcDetected(sw, port))
			new_decl = true;
	}

	/* Ask all other ports to declare the attribute. */
	for (n = 0; n <= mrp->ports; n++) {
		q = get_phy_port(sw, n);
		if (q != port && (mrp->tx_ports & (1 << q)) &&
		    (mrp->mmrp_tx_ports & (1 << q))) {
			u8 action = MRP_ACTION_TX;
			int existed = info->tx_ports & (1 << q);

			/* Need to update declaration. */
			if (new_decl) {
				action = MRP_ACTION_TX_NEW;
				existed = false;
			}

			/* Attribute was declared. */
			if (existed)
				continue;
			info->tx_ports |= (1 << q);

			add_attrib_report(mrp, node, action,
				MRP_TYPE_MAC, q);
		}
	}
	if (mrp->report_head)
		result = DEV_IOC_MRP_REPORT;
	return result;
}  /* proc_mrp_rx_mac */

static int proc_mrp_lv_vlan(struct mrp_info *mrp, uint port,
	struct MRP_vlan *vlan)
{
	struct mrp_node *node;
	struct mrp_vlan_info *info;
	struct mrp_vlan_info data;
	u16 ports;
	uint m = BIT(port);
	int result = DEV_IOC_OK;

#ifdef DEBUG_MVRP
if (dbg_mrp_vlan || vlan->id == 2 || vlan->id > 4090)
dbg_msg(" %s %d=%d"NL, __func__, port, vlan->id);
#endif
	data.vid = vlan->id;
	memset(data.addr, 0xff, ETH_ALEN);
	node = mrp_find_node(&mrp->vlan_list, cmp_vlan, &data);
	if (!node)
		return DEV_IOC_INVALID_CMD;

	info = node->data;
	ports = info->ports;
	info->rx_ports &= ~m;
	info->ports &= ~m;

	/* There is no change in port membership. */
	if (ports == info->ports)
		return result;
#if 0
	ports = mrp_find_vlan_ports(&mrp->vlan_list, data.vid, NULL, NULL);
#endif
	ports = info->ports;
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
#ifdef DEBUG_MVRP
		if (mrp->vlan_list.cnt < 3)
			dbg_mrp_vlan = 1;
#endif
	}

	if (!mrp->no_report)
		result = proc_mrp_lv(mrp, node, info->ports,
			&info->tx_ports, MRP_TYPE_VLAN);
#ifdef DEBUG_MVRP
#ifdef DEBUG
if (dbg_mrp_vlan)
	mrp_show_node(&mrp->vlan_list, show_vlan_info);
#endif
#endif
	return result;
}  /* proc_mrp_lv_vlan */

static int proc_mrp_rx_vlan(struct mrp_info *mrp, uint port,
	struct MRP_vlan *vlan, u8 new_decl)
{
	struct mrp_node *node;
	struct mrp_vlan_info *info;
	struct ksz_port_cfg *cfg;
	u16 ports;
	int bit;
	int index;
	uint n;
	uint q;
	uint m = BIT(port);
	struct ksz_sw *sw = mrp->parent;
	int result = DEV_IOC_OK;

#ifdef DEBUG_MVRP
if (dbg_mrp_vlan || vlan->id == 2 || vlan->id > 4090)
dbg_msg(" %s %d=%x:%d"NL, __func__, port, new_decl, vlan->id);
#endif
	node = mrp_get_vlan_info(&mrp->vlan_list, vlan->id, NULL);
	if (!node)
		return -ENOMEM;
	info = node->data;
	ports = info->ports;
	info->rx_ports |= m;

	/* MRP.c.10.1.5b
	 * Non-participant does not send out declarations, but received
	 * declaration is propagated, and traffic is not forwarded.
	 */
	if (new_decl & 0x80)
		new_decl &= ~0x80;
	else
		info->ports |= m;

	/* MVRP.c
	 *
	 */
	cfg = get_port_cfg(sw, port);
	index = vlan->id / VID_IN_DATA;
	bit = vlan->id % VID_IN_DATA;
	if (cfg->restricted) {
		if (!(sw->info->vid[index] & (1 << bit)))
			return result;
	}

	/* There is change in port membership. */
	if (ports != info->ports) {
#if 0
		info->ports |= SRP_PORT_IGNORE;
		ports = mrp_find_vlan_ports(&mrp->vlan_list, vlan->id,
			&info->index, &info->fid);
		info->ports &= ~SRP_PORT_IGNORE;
#endif

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
#ifdef DEBUG_MVRP
#ifdef DEBUG
if (dbg_mrp_vlan)
	mrp_show_node(&mrp->vlan_list, show_vlan_info);
	if (mrp->vlan_list.cnt > 4) {
if (dbg_mrp_vlan)
dbg_msg(" stop dbg vlan"NL);
		dbg_mrp_vlan = 0;
	}
#endif
#endif
	if (mrp->no_report)
		return result;

#if 1
	if (mrp->rx_ports) {

if (mrp->rx_ports != sw->rx_ports[0])
dbg_msg(" rx: %x %x"NL, mrp->rx_ports, sw->rx_ports[0]);
	}
#endif
	if (!(mrp->rx_ports & m))
		return result;

	if (!new_decl) {
		if (sw->ops->get_tcDetected(sw, port))
			new_decl = true;
	} else if (new_decl != 1)
		return result;

	/* Ask all other ports to declare the attribute. */
	for (n = 0; n <= mrp->ports; n++) {
		q = get_phy_port(sw, n);
		if (q != port && (mrp->tx_ports & (1 << q)) &&
		    (mrp->mvrp_tx_ports & (1 << q))) {
			u8 action = MRP_ACTION_TX;
			int existed = info->tx_ports & (1 << q);

			/* Need to update declaration. */
			if (new_decl) {
				action = MRP_ACTION_TX_NEW;
				existed = false;
			}

			/* Attribute was declared. */
			if (existed)
				continue;
			info->tx_ports |= (1 << q);

			add_attrib_report(mrp, node, action,
				MRP_TYPE_VLAN, q);
		}
	}
	if (mrp->report_head)
		result = DEV_IOC_MRP_REPORT;
	return result;
}  /* proc_mrp_rx_vlan */
#endif

#ifdef CONFIG_KSZ_MSRP
#define RFC_NO_RESOURCES_BIT		BIT(0)
#define RFC_LATENCY_CHANGED_BIT		BIT(1)
#define RFC_FIRSTVALUE_CHANGED_BIT	BIT(2)
#define RFC_MAXFRAMESIZE_BIT		BIT(3)
#define RFC_ASCAPABLE_BIT		BIT(4)
#define RFC_SRP_BOUNDARY_BIT		BIT(5)
#define RFC_PRIORITY_BIT		BIT(6)
#define RFC_NO_BANDWIDTH_BIT		BIT(7)
#define RFC_NO_BANDWIDTH_TC_BIT		BIT(8)
#define RFC_STREAM_ID_BIT		BIT(9)
#define RFC_DEST_ADDR_BIT		BIT(10)
#define RFC_PREEMPTED_BIT		BIT(11)
#define RFC_SR_MISMATCHED_BIT		BIT(12)
#define RFC_VLAN_TAGGING_BIT		BIT(13)
#define RFC_CHECK_BIT			BIT(31)

static u8 msrp_failure_code(u32 code_bits)
{
	u8 code = RFC_NO_ERROR;

	if (code_bits & RFC_NO_RESOURCES_BIT)
		code = RFC_NO_RESOURCES;
	else if (code_bits & RFC_LATENCY_CHANGED_BIT)
		code = RFC_LATENCY_CHANGED;
	else if (code_bits & RFC_FIRSTVALUE_CHANGED_BIT)
		code = RFC_FIRSTVALUE_CHANGED;
	else if (code_bits & RFC_MAXFRAMESIZE_BIT)
		code = RFC_MAXFRAMESIZE_TOO_LARGE;
	else if (code_bits & (RFC_ASCAPABLE_BIT | RFC_SRP_BOUNDARY_BIT))
		code = RFC_PORT_IS_NOT_AVB;
	else if (code_bits & RFC_PRIORITY_BIT)
		code = RFC_PRIORITY_IS_NOT_SR_CLASS;
	else if (code_bits & RFC_NO_BANDWIDTH_BIT)
		code = RFC_NO_BANDWIDTH;
	else if (code_bits & RFC_NO_BANDWIDTH_TC_BIT)
		code = RFC_NO_BANDWIDTH_FOR_TRAFFIC_CLASS;
	else if (code_bits & RFC_STREAM_ID_BIT)
		code = RFC_STREAM_ID_USED;
	else if (code_bits & RFC_DEST_ADDR_BIT)
		code = RFC_DEST_ADDR_USED;
	else if (code_bits & RFC_PREEMPTED_BIT)
		code = RFC_PREEMPTED_BY_RANK;
	else if (code_bits & RFC_SR_MISMATCHED_BIT)
		code = RFC_SR_CLASS_PRIORITY_MISMATCHED;
	else if (code_bits & RFC_VLAN_TAGGING_BIT)
		code = RFC_VLAN_TAGGING_DISABLED;
	return code;
}  /* msrp_failure_code */
#endif

static void proc_mrp_attribute(struct mrp_info *mrp, u8 *data);

#ifdef CONFIG_KSZ_AVB
static void mrp_set_delta(struct mrp_info *mrp, u8 port, u32 A, u32 B)
{
	u8 data[40];
	struct mrp_cfg_options *cmd = (struct mrp_cfg_options *) data;
	struct ksz_sw *sw = mrp->parent;

if (!(mrp->mask & (1 << port)))
dbg_msg(" !!! %s %d"NL, __func__, port);
	cmd->action = MRP_ACTION_DELTA;
	cmd->type = MRP_TYPE_PORT;
	cmd->port = get_log_port(sw, port);
	cmd->new_decl = 0;
	cmd->data.data[0] = A;
	cmd->data.data[1] = B;
	proc_mrp_attribute(mrp, data);
}  /* mrp_set_delta */

static void mrp_set_speed(struct mrp_info *mrp, u8 port, u32 speed, bool duplex)
{
	u8 data[40];
	struct mrp_cfg_options *cmd = (struct mrp_cfg_options *) data;
	struct ksz_sw *sw = mrp->parent;

if (!(mrp->mask & (1 << port)))
dbg_msg(" !!! %s %d"NL, __func__, port);
	cmd->action = MRP_ACTION_SPEED;
	cmd->type = MRP_TYPE_PORT;
	cmd->port = get_log_port(sw, port);
	cmd->new_decl = 0;
	cmd->data.data[0] = speed;
	cmd->data.data[1] = duplex;
	proc_mrp_attribute(mrp, data);
}  /* mrp_set_speed */
#endif

#ifdef CONFIG_KSZ_MSRP
static void mrp_chk_talker(struct mrp_info *mrp, u8 port)
{
	u8 data[40];
	struct mrp_cfg_options *cmd = (struct mrp_cfg_options *) data;
	struct ksz_sw *sw = mrp->parent;

if (!(mrp->mask & (1 << port)))
dbg_msg(" !!! %s %d"NL, __func__, port);
	cmd->action = MRP_ACTION_CHK_TALKER;
	cmd->type = MRP_TYPE_PORT;
	cmd->port = get_log_port(sw, port);
	cmd->new_decl = 0;
	proc_mrp_attribute(mrp, data);
}  /* mrp_chk_talker */

static void mrp_chk_registered(struct mrp_info *mrp, u8 port)
{
	u8 data[40];
	struct mrp_cfg_options *cmd = (struct mrp_cfg_options *) data;
	struct ksz_sw *sw = mrp->parent;

if (!(mrp->mask & (1 << port)))
dbg_msg(" !!! %s %d"NL, __func__, port);
	cmd->action = MRP_ACTION_CHK_REG;
	cmd->type = MRP_TYPE_PORT;
	cmd->port = get_log_port(sw, port);
	cmd->new_decl = 0;
	proc_mrp_attribute(mrp, data);
}  /* mrp_chk_registered */

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
#ifdef DEBUG_MRP_BASIC
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

#if 0
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
#ifdef DEBUG_MRP_BASIC
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
#endif

static int stream_iter(struct mrp_node_anchor *list, void *param[],
		       int (*oper)(struct mrp_node *prev,
				   struct srp_stream_info *data,
				   void *param[]))
{
	int rc;
	struct mrp_node *prev;
	struct mrp_node *next;

	prev = &list->anchor;
	next = prev->next;
	while (next) {
		rc = oper(prev, next->data, param);

		/* return ok or some other codes */
		if (rc != -EAGAIN)
			return rc;

		prev = next;
		next = prev->next;
	}
	return -EAGAIN;
}

static int stream_oper(struct mrp_node_anchor *list, void *param[],
		       int (*oper)(struct mrp_node *prev,
				   struct srp_stream_info *data,
				   void *param[]))
{
	int rc;
	struct mrp_node *prev;
	struct mrp_node *next;

	prev = &list->anchor;
	next = prev->next;
	while (next) {
		rc = oper(prev, next->data, param);

		/* no more operation */
		if (!rc)
			return 0;

		/* stream not removed */
		if (rc == -EAGAIN)
			prev = next;
		next = prev->next;
	}
	return -EAGAIN;
}

static void mrp_set_traffic(struct mrp_info *mrp, struct SRP_stream *stream,
			    uint port, bool open)
{
	u16 fid;
	u16 ports;
	int result;

	ports = 1 << port;
	fid = mrp_get_fid(mrp, stream->vlan_id, stream->dest);
	result = srp_update_mac(mrp, stream->dest, fid, ports, open);
#if 0
	if (!result)
		result = srp_update_vlan(mrp, stream->vlan_id, stream->dest,
					 ports, open);
#endif
}

static int stream_drop(struct mrp_node *prev,
		       struct srp_stream_info *data, void *param[])
{
	struct mrp_node *next;
	struct SRP_reserv *reserv;
	struct SRP_stream *stream;
	struct mrp_info *mrp = param[0];
	struct mrp_port_info *info = param[1];
	struct mrp_traffic_info *traffic = param[2];
	int *port = param[3];
	struct SRP_reserv *t_reserv = param[4];
	int *active = param[5];

	reserv = data->reserv;
	if (reserv == t_reserv) {
		if (*active) {
			u32 bandwidth;

			stream = reserv->stream;
			bandwidth = stream->bandwidth;

			traffic->bandwidth_used -= bandwidth;
			traffic->bandwidth_left = traffic->bandwidth_max -
				traffic->bandwidth_used;
			if (traffic->bandwidth_other)
				*traffic->bandwidth_other =
					*traffic->bandwidth_avail +
					traffic->bandwidth_left;
			info->bandwidth_used -= bandwidth;
			info->bandwidth_left = info->bandwidth_max -
				info->bandwidth_used;

			mrp_set_traffic(mrp, stream, *port, false);
		}

		/* Remove node from list. */
		next = prev->next;
		prev->next = next->next;
		mrp_free_node(next);

		/* stop doing next in the list */
		return 0;
	}
	return -EAGAIN;
}

static bool drop_reserv(struct mrp_info *mrp, u8 port,
			struct mrp_port_info *info,
			struct SRP_reserv *reserv, int active)
{
	struct mrp_node_anchor *list;
	struct mrp_traffic_info *traffic;
	int rc;
	int tc;
	void *param[6];
	bool result = false;

	tc = get_traffic_class(mrp, reserv->stream->priority);
	traffic = get_traffic_info(info, tc);
	if (active)
		list = &traffic->active;
	else
		list = &traffic->passive;
	param[0] = mrp;
	param[1] = info;
	param[2] = traffic;
	param[3] = &port;
	param[4] = reserv;
	param[5] = &active;
	rc = stream_oper(list, param, stream_drop);
	if (!rc)
		result = true;

	return result;
}  /* drop_reserv */

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

#if 0
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
#endif

#if 0
static int stream_chk_size(struct mrp_node *prev,
			   struct srp_stream_info *data, void *param[])
{
	struct SRP_reserv *reserv;
	struct SRP_stream *stream;
	struct mrp_traffic_info *traffic = param[0];

	reserv = data->reserv;
	stream = reserv->stream;
	if (stream->MaxFrameSize > traffic->max_frame_size)
		traffic->max_frame_size = stream->MaxFrameSize;
	return -EAGAIN;
}
#endif

static void srp_cfg_reserv(struct mrp_info *mrp, struct mrp_port_info *port)
{
	uint n;
	uint p;
#if 0
	u32 max_size;
#endif
	int tc;
	struct mrp_port_info *info;
	struct mrp_traffic_info *traffic;
	struct ksz_sw *sw = mrp->parent;
#if 0
	void *param[6];
#endif

	srp_cfg_mac(mrp, &mrp->mac_down);
#if 0
	srp_cfg_vlan(mrp, &mrp->vlan_down);
#endif
	for (n = 0; n <= mrp->ports; n++) {
		p = get_phy_port(sw, n);
		info = mrp_get_port_info(mrp, p);
		if (port && info != port)
			continue;
		if (!info->status.msrpPortEnabledStatus)
			continue;
		if (!info->link)
			continue;
		for (tc = SR_CLASS_A; tc >= SR_CLASS_B; tc--) {
			traffic = get_traffic_info(info, tc);

#if 0
			/* Find out the maximum frame size. */
			max_size = traffic->max_frame_size;
			traffic->max_frame_size = 0;
			param[0] = traffic;
			stream_iter(&traffic->active, param, stream_chk_size);
			if (max_size && !traffic->max_frame_size)
				traffic->max_frame_size = max_size;
			if (max_size != traffic->max_frame_size) {
dbg_msg("  max size: %u %u"NL, max_size, traffic->max_frame_size);
				/* Make sure credit settings will be updated. */
				if (traffic->bandwidth_set)
					traffic->bandwidth_set = 1;
			}
#endif
			if (traffic->bandwidth_used !=
			    traffic->bandwidth_set) {
				srp_cfg_credit_shaper(mrp, p, info, traffic);
				traffic->bandwidth_set =
					traffic->bandwidth_used;
			}
		}
	}
	srp_cfg_mac(mrp, &mrp->mac_up);
#if 0
	srp_cfg_vlan(mrp, &mrp->vlan_up);
#endif
}  /* srp_cfg_reserv */

static struct mrp_node *create_stream_info(struct mrp_info *mrp,
					   struct SRP_reserv *t_reserv)
{
	struct mrp_node *node;
	struct srp_stream_info *info;

	node = mrp_alloc_node(sizeof(struct srp_stream_info));
	if (!node)
		return NULL;
	info = node->data;
	prepare_stream_info(t_reserv, info);
	return node;
}  /* create_stream_info */

static void add_reserv(struct mrp_traffic_info *traffic, int active,
		       struct mrp_node *node)
{
	struct mrp_node_anchor *list;
	int (*cmp)(void *a, void *b);

	if (active) {
		list = &traffic->active;
		cmp = cmp_lower_stream;
	} else {
		list = &traffic->passive;
		cmp = cmp_higher_stream;
	}
	mrp_insert_node(list, cmp, node);
}  /* add_reserv */

static struct SRP_reserv *mrp_link_listener(struct mrp_info *mrp,
					    struct mrp_port_info *info,
					    struct SRP_stream *stream)
{
	struct SRP_reserv *reserv;

	/* Create linked listener declaration. */
	reserv = srp_find_reserv(&info->declared, stream->id,
				 SRP_LISTENER);
	if (!reserv) {

		/* Listener declaration is not known yet. */
		reserv = srp_create_reserv(stream->id, SRP_LISTENER,
					   0, 0, mrp->id, 0);
		if (!reserv)
			return NULL;

		reserv->stream = stream;
		srp_insert_reserv(&info->declared, reserv);
	}
	reserv->stream = stream;
	return reserv;
}  /* mrp_link_listener */

static int mrp_update_listener(struct mrp_info *mrp,
			       struct SRP_reserv *l_reserv,
			       struct SRP_stream *stream, u8 new_decl)
{
	int declaration;
	int n;
	struct SRP_reserv *reserv;
	struct SRP_reserv *t_reserv;
	struct mrp_port_info *info;
	int result = DEV_IOC_OK;
	int active = mrp->status.msrpEnabledStatus &&
		     info->status.msrpPortEnabledStatus;

	info = mrp_get_port_info(mrp, stream->in_port);
	if (!l_reserv)
		l_reserv = srp_find_reserv(&info->declared, stream->id,
					   SRP_LISTENER);
	if (!l_reserv) {
dbg_msg("  ! L decl not found: %d"NL, stream->in_port);
	}
	if (!l_reserv)
		return result;

	declaration = 0;
	for (n = 0; n <= mrp->ports; n++) {
		if (n == stream->in_port)
			continue;
		info = mrp_get_port_info(mrp, n);
		active = mrp->status.msrpEnabledStatus &&
			info->status.msrpPortEnabledStatus;
		if (!active)
			continue;
		reserv = srp_find_reserv(&info->registered, stream->id,
					 SRP_LISTENER);
		t_reserv = srp_find_reserv(&info->declared, stream->id,
					 SRP_TALKER);
		if (reserv && t_reserv) {
			if (SRP_FAILED == t_reserv->declaration)
				declaration |= SRP_ASKING_FAILED_SCALE;
			else
				declaration |= (1 << reserv->declaration);
		} else if (reserv) {
dbg_msg("  no t_reserv?"NL);
				declaration |= SRP_ASKING_FAILED_SCALE;
		}
	}

	/* info will need to be initialized. */

	/* No more listeners. */
	if (!declaration) {
		int free = true;

#ifdef DEBUG_MSRP
dbg_msg("listener leaving"NL);
#endif
		info = mrp_get_port_info(mrp, stream->in_port);
		active = mrp->status.msrpEnabledStatus &&
			info->status.msrpPortEnabledStatus;
		if (!mrp->no_report && active) {
			free = false;
			add_attrib_report(mrp, l_reserv, MRP_ACTION_LV,
				MRP_TYPE_LISTENER, stream->in_port);
			result = DEV_IOC_MRP_REPORT;
		}
		srp_remove_reserv(l_reserv, free);
		return result;
	}

	if (declaration > SRP_READY_SCALE)
		declaration = SRP_READY_FAILED;
	else if (declaration == SRP_READY_SCALE)
		declaration = SRP_READY;
	else
		declaration = SRP_ASKING_FAILED;

#if 1
	if (fqtss_34_2_1b_hack &&
	    declaration == l_reserv->declaration && declaration == SRP_READY) {
		l_reserv->declaration = SRP_READY_FAILED;
		new_decl = true;
	}
#endif

	/* Declaration is different. */
	if (declaration != l_reserv->declaration) {
		l_reserv->declaration = declaration;
#ifdef DEBUG_MSRP
dbg_msg("l dec: %d=%d"NL, stream->in_port, declaration);
#endif
		info = mrp_get_port_info(mrp, stream->in_port);
		active = mrp->status.msrpEnabledStatus &&
			info->status.msrpPortEnabledStatus;
		if (!mrp->no_report && active) {
			u8 action = MRP_ACTION_TX;

			if (new_decl)
				action = MRP_ACTION_TX_NEW;
			add_attrib_report(mrp, l_reserv, action,
				MRP_TYPE_LISTENER, stream->in_port);

			/* Ask application to retrieve attributes. */
			result = DEV_IOC_MRP_REPORT;
		}
	}
	return result;
}  /* mrp_update_listener */

static int stream_clr_mark(struct mrp_node *prev,
			struct srp_stream_info *data, void *param[])
{
	int *chk = param[0];

	if (*chk && data->mark)
dbg_msg("  mark !!"NL);
	data->mark = false;
	return -EAGAIN;
}

static int stream_set_mark(struct mrp_node *prev,
			struct srp_stream_info *data, void *param[])
{
	data->mark = true;
	return -EAGAIN;
}

static int stream_chk_bandwidth(struct mrp_node *prev,
			struct srp_stream_info *data, void *param[])
{
	int cmp;
	struct srp_stream_info *b = param[0];
	u32 *avail = param[1];
	u32 *required = param[2];
	int *one_stream = param[3];
	char bw_str1[20];
	char bw_str2[20];
	struct SRP_reserv *reserv;

	cmp = cmp_lower_stream(b, data);
#if 0
dbg_msg(" cmp %d  %d:%d %llx:%llx %02x:%02x"NL, cmp,
b->rank, data->rank, b->age, data->age,
b->id[7], data->id[7]);
#endif

	/* stream has higher priority. */
	if (cmp < 0)
		return -ENXIO;
	if (cmp == 0)
		return 0;
	if (!data->mark) {
		reserv = data->reserv;
		if (*one_stream) {
			*avail = reserv->stream->bandwidth;
		} else {
			*avail += reserv->stream->bandwidth;
			data->mark = true;
		}
		format_num(bw_str1, *avail);
		format_num(bw_str2, *required);
dbg_msg("  avail: %s %s"NL, bw_str1, bw_str2);
		if (*avail >= *required) {

			/* in case it is not marked above */
			data->mark = true;
			return 0;
		}
	}
	return -EAGAIN;
}

static int stream_decr_bandwidth(struct mrp_node *prev,
				 struct srp_stream_info *data, void *param[])
{
	u32 bandwidth;
	struct SRP_reserv *reserv;
	struct mrp_port_info *info = param[0];
	struct mrp_traffic_info *traffic = param[1];
	int *mark = param[2];

	if (traffic->bandwidth_used > traffic->bandwidth_max) {
		reserv = data->reserv;
		bandwidth = reserv->stream->bandwidth;
		reserv->code_bits = RFC_NO_BANDWIDTH_TC_BIT;
		if (info->bandwidth_used > info->bandwidth_max)
dbg_msg(" no: %u %u"NL, info->bandwidth_used, info->bandwidth_max);
		if (info->bandwidth_used > info->bandwidth_max)
			reserv->code_bits |= RFC_NO_BANDWIDTH_BIT;
		traffic->bandwidth_used -= bandwidth;
		info->bandwidth_used -= bandwidth;
		data->mark = true;
		*mark = true;
	}
	return -EAGAIN;
}

static int stream_cmp(struct mrp_node *prev, struct srp_stream_info *data,
		      void *param[])
{
	struct SRP_reserv *reserv = param[0];

	if (data->reserv == reserv) {
		data->mark = true;
		return 0;
	}
	return -EAGAIN;
}

static int stream_stop(struct mrp_node *prev, struct srp_stream_info *data,
		       void *param[])
{
	struct mrp_node *next;
	struct SRP_reserv *reserv;
	struct SRP_stream *stream;
	struct mrp_info *mrp = param[0];
	struct mrp_traffic_info *traffic = param[1];
	int *port = param[2];
	int result;

	if (data->mark) {
		u8 decl;

		data->mark = false;

		reserv = data->reserv;
		decl = reserv->declaration;
		reserv->code = msrp_failure_code(reserv->code_bits);
		if (reserv->code)
			reserv->declaration = SRP_FAILED;

		stream = reserv->stream;
		mrp_set_traffic(mrp, stream, *port, false);

		if (!mrp->no_report && decl != reserv->declaration) {
dbg_msg("  no band stop: %x"NL, reserv->code_bits);
			add_attrib_report(mrp, reserv, MRP_ACTION_TX_NEW,
				MRP_TYPE_TALKER, *port);
		}

		result = mrp_update_listener(mrp, NULL, stream, false);

		/* Remove node from list. */
		next = prev->next;
		prev->next = next->next;
		next->next = NULL;

		add_reserv(traffic, false, next);

		return -ENODEV;
	}
	return -EAGAIN;
}

static int stream_reset(struct mrp_node *prev,
			struct srp_stream_info *data, void *param[])
{
	struct SRP_reserv *reserv;

	reserv = data->reserv;
	if (reserv->code_bits &
	    ~(RFC_NO_BANDWIDTH_BIT | RFC_NO_BANDWIDTH_TC_BIT |
	     RFC_PREEMPTED_BIT))
		return -EAGAIN;
	if (!reserv->pair)
printk(" no pair!"NL);
	if (!reserv->pair)
		return -EAGAIN;
	reserv->pair->code = RFC_NO_ERROR;
	return -EAGAIN;
}  /* stream_reset */

static int stream_start(struct mrp_node *prev,
			struct srp_stream_info *data, void *param[])
{
	struct mrp_node *next;
	struct SRP_reserv *reserv;
	struct SRP_stream *stream;
	struct mrp_info *mrp = param[0];
	struct mrp_port_info *info = param[1];
	struct mrp_traffic_info *traffic = param[2];
	int *port = param[3];
	int result;
	u32 bandwidth;
	bool adv = false;

	reserv = data->reserv;
	if (reserv->code_bits &
	    ~(RFC_NO_BANDWIDTH_BIT | RFC_NO_BANDWIDTH_TC_BIT |
	     RFC_PREEMPTED_BIT) || reserv->pair->code != RFC_NO_ERROR)
{
#if 0
dbg_msg(" other error: %x %d"NL, reserv->code_bits, reserv->pair->code);
#endif
		return -EAGAIN;
}
	bandwidth = reserv->stream->bandwidth;
	traffic->bandwidth_left = traffic->bandwidth_max -
		traffic->bandwidth_used;
	if (bandwidth <= traffic->bandwidth_left) {
		/* Remove node from list. */
		next = prev->next;
		prev->next = next->next;
		next->next = NULL;

		add_reserv(traffic, true, next);

		traffic->bandwidth_used += bandwidth;
		info->bandwidth_used += bandwidth;

		if (data->mark) {
			data->mark = false;
			return -ENODEV;
		}

		if (reserv->declaration != SRP_ADVERTISE) {
			reserv->declaration = SRP_ADVERTISE;
			reserv->code_bits = 0;
			reserv->code = RFC_NO_ERROR;
			adv = true;
		}

		stream = reserv->stream;
		mrp_set_traffic(mrp, stream, *port, true);

		if (!mrp->no_report && adv) {
			add_attrib_report(mrp, reserv, MRP_ACTION_TX_NEW,
				MRP_TYPE_TALKER, *port);
		}

		result = mrp_update_listener(mrp, NULL, stream, false);

		return -ENODEV;
	} else if (data->mark) {
dbg_msg(" no bandwidth for this"NL);
		data->mark = false;

		reserv->declaration = SRP_FAILED;
		reserv->code_bits = RFC_NO_BANDWIDTH_TC_BIT;
		info->bandwidth_left = info->bandwidth_max -
			info->bandwidth_used;
		if (bandwidth > info->bandwidth_left)
			reserv->code_bits |= RFC_NO_BANDWIDTH_BIT;
		reserv->code = msrp_failure_code(reserv->code_bits);

		stream = reserv->stream;
		mrp_set_traffic(mrp, stream, *port, false);

		if (!mrp->no_report) {
			add_attrib_report(mrp, reserv, MRP_ACTION_TX_NEW,
				MRP_TYPE_TALKER, *port);
		}

		result = mrp_update_listener(mrp, NULL, stream, false);

	} else if (bandwidth <= info->bandwidth_left &&
		   (reserv->code_bits & RFC_NO_BANDWIDTH_BIT)) {
		reserv->code_bits &= ~RFC_NO_BANDWIDTH_BIT;
		reserv->code = msrp_failure_code(reserv->code_bits);
		if (!mrp->no_report) {
dbg_msg("  no tc"NL);
			add_attrib_report(mrp, reserv,
					  MRP_ACTION_TX,
					  MRP_TYPE_TALKER, *port);
		}
	} else if (bandwidth > info->bandwidth_left &&
		   !(reserv->code_bits & RFC_NO_BANDWIDTH_BIT)) {
		reserv->code_bits |= RFC_NO_BANDWIDTH_BIT;
		reserv->code = msrp_failure_code(reserv->code_bits);
		if (!mrp->no_report) {
dbg_msg("  no bw"NL);
			add_attrib_report(mrp, reserv,
					  MRP_ACTION_TX,
					  MRP_TYPE_TALKER, *port);
		}
	} else if (reserv->pair && reserv->pair->code == RFC_NO_ERROR) {
		reserv->pair->code = RFC_NO_BANDWIDTH;
	}
	return -EAGAIN;
}

static int stream_drop_other(struct mrp_node *prev,
			     struct srp_stream_info *data, void *param[])
{
	struct mrp_node *next;
	struct SRP_reserv *reserv;
	struct SRP_stream *stream;
	struct mrp_info *mrp = param[0];
	struct mrp_traffic_info *traffic = param[1];
	int *port = param[2];
	int *avail = param[3];
	int result;

dbg_msg("%s %p %p"NL, __func__, param, mrp);
	if (data->mark) {
		u32 bandwidth;

		data->mark = false;

		reserv = data->reserv;
		stream = reserv->stream;

		bandwidth = stream->bandwidth;
		*avail += bandwidth;

		traffic->bandwidth_left += bandwidth;
		traffic->bandwidth_used -= bandwidth;
		if (traffic->bandwidth_other)
			*traffic->bandwidth_other =
				*traffic->bandwidth_avail +
				traffic->bandwidth_left;

		reserv->declaration = SRP_FAILED;
		reserv->code_bits = RFC_PREEMPTED_BIT;
		reserv->code = RFC_PREEMPTED_BY_RANK;

		mrp_set_traffic(mrp, stream, *port, false);

		if (!mrp->no_report)
			add_attrib_report(mrp, reserv, MRP_ACTION_TX_NEW,
				MRP_TYPE_TALKER, *port);

		result = mrp_update_listener(mrp, NULL, stream, false);

		/* Remove node from list. */
		next = prev->next;
		prev->next = next->next;
		next->next = NULL;

		add_reserv(traffic, false, next);

		return -ENODEV;
	}
	return -EAGAIN;
}

static bool have_bandwidth(struct mrp_port_info *info,
			   struct mrp_traffic_info *traffic,
			   struct SRP_reserv *t_reserv,
			   u32 required_bandwidth)
{
	u32 avail_bandwidth = 0;
	int cmp;
	int one;
	void *param[6];
	struct srp_stream_info b;
	int rc;

	prepare_stream_info(t_reserv, &b);

	/* Make sure stream age is latest for correct comparison. */
	if (!b.age)
		b.age = get_stream_age(info);

	cmp = 1;
	param[0] = &cmp;
	rc = stream_iter(&traffic->active, param, stream_clr_mark);

	param[0] = &b;
	param[1] = &avail_bandwidth;
	param[2] = &required_bandwidth;
	one = 1;
	param[3] = &one;
	rc = stream_iter(&traffic->active, param, stream_chk_bandwidth);
	if (!rc)
		return true;

	param[0] = &b;
	param[1] = &avail_bandwidth;
	param[2] = &required_bandwidth;
	one = 0;
	param[3] = &one;
	rc = stream_iter(&traffic->active, param, stream_chk_bandwidth);
	if (!rc)
		return true;

dbg_msg(" no bandwidth %s %u %u"NL, __func__, required_bandwidth, info->bandwidth_left);

	/* No bandwidth at all for the new stream. */
	return false;
}  /* have_bandwidth */

static bool drop_other_reserv(struct mrp_info *mrp, u8 port,
			      struct mrp_port_info *info,
			      struct mrp_traffic_info *traffic,
			      struct SRP_reserv *t_reserv,
			      u32 required_bandwidth, bool drop)
{
	u32 avail_bandwidth = 0;
	void *param[6];
	int rc;
	bool ok;

	ok = have_bandwidth(info, traffic, t_reserv, required_bandwidth);
	if (!ok) {
		return false;
	} else if (!drop) {
		int cmp = 0;

		/* reset marked streams */
		param[0] = &cmp;
		rc = stream_iter(&traffic->active, param, stream_clr_mark);
		return true;
	}

	param[0] = mrp;
	param[1] = traffic;
	param[2] = &port;
	param[3] = &avail_bandwidth;
dbg_msg(" stream_drop_other %p %p"NL, param, mrp);
	rc = stream_oper(&traffic->active, param, stream_drop_other);

	/* Increase bandwidth */
	info->bandwidth_left += avail_bandwidth;
	info->bandwidth_used -= avail_bandwidth;
	return true;
}  /* drop_other_reserv */

static bool drop_active_reserv(struct mrp_info *mrp, u8 port,
			struct mrp_port_info *info,
			struct mrp_traffic_info *traffic,
			struct SRP_reserv *reserv)
{
	int rc;
	void *param[6];
	bool drop = false;

dbg_msg("%s"NL, __func__);
	param[0] = reserv;
	rc = stream_iter(&traffic->active, param, stream_cmp);

	/* A stream was marked for stopping.*/
	if (!rc) {
		u32 bandwidth = reserv->stream->bandwidth;

		traffic->bandwidth_used -= bandwidth;
		traffic->bandwidth_left += bandwidth;
		if (traffic->bandwidth_other)
			*traffic->bandwidth_other = *traffic->bandwidth_avail +
				traffic->bandwidth_left;
		info->bandwidth_used -= bandwidth;
		info->bandwidth_left += bandwidth;
		param[0] = mrp;
		param[1] = traffic;
		param[2] = &port;
		rc = stream_oper(&traffic->active, param, stream_stop);
		drop = true;
	}

	return drop;
}

static void stop_active_reserv(struct mrp_info *mrp, u8 port,
			struct mrp_port_info *info,
			struct mrp_traffic_info *traffic)
{
	int rc;
	void *param[6];
	bool mark = false;

	param[0] = info;
	if (traffic->bandwidth_used > traffic->bandwidth_max) {
		param[1] = traffic;
		param[2] = &mark;
		rc = stream_iter(&traffic->active, param,
			stream_decr_bandwidth);
		traffic->bandwidth_left = traffic->bandwidth_max -
			traffic->bandwidth_used;

		/* Increase Class B available bandwidth. */
		if (traffic->bandwidth_other)
			*traffic->bandwidth_other =
				*traffic->bandwidth_avail +
				traffic->bandwidth_left;
		info->bandwidth_left = info->bandwidth_max -
			info->bandwidth_used;
	}

	/* A stream was marked for stopping.*/
	if (mark) {
		param[0] = mrp;
		param[1] = traffic;
		param[2] = &port;
		rc = stream_oper(&traffic->active, param, stream_stop);
	}
}  /* stop_active_reserv */

static void start_passive_reserv(struct mrp_info *mrp, u8 port,
				 struct mrp_port_info *info)
{
	int rc;
	int tc;
	struct mrp_traffic_info *traffic;
	void *param[6];

	param[0] = mrp;
	param[1] = info;
	param[3] = &port;
	for (tc = SR_CLASS_A; tc >= SR_CLASS_B; tc--) {
		traffic = get_traffic_info(info, tc);
		param[2] = traffic;
		rc = stream_oper(&traffic->passive, param, stream_start);
		traffic->bandwidth_left = traffic->bandwidth_max -
			traffic->bandwidth_used;

		/* Decrease Class B available bandwidth. */
		if (traffic->bandwidth_other)
			*traffic->bandwidth_other =
				*traffic->bandwidth_avail +
				traffic->bandwidth_left;
	}
	info->bandwidth_left = info->bandwidth_max - info->bandwidth_used;
}  /* start_passive_reserv */

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

static void chk_passive_reserv(struct mrp_info *mrp, u8 port,
			struct mrp_port_info *info)
{
	int rc;
	int tc;
	struct mrp_traffic_info *traffic;
	void *param[6];

	for (tc = SR_CLASS_A; tc >= SR_CLASS_B; tc--) {
		traffic = get_traffic_info(info, tc);
		rc = stream_iter(&traffic->active, param, stream_set_mark);
		rc = stream_iter(&traffic->passive, param, stream_reset);
		traffic->bandwidth_used = 0;
		mrp_combine_list(&traffic->active, &traffic->passive);
#if 0
		mrp_show_node(&traffic->passive, show_stream_info);
#endif
	}
	info->bandwidth_used = 0;
	start_passive_reserv(mrp, port, info);
}

static u32 chk_avail_tx_bandwidth(struct mrp_info *mrp, u8 port,
				  struct mrp_port_info *info, int tc,
				  struct SRP_reserv *t_reserv, bool drop)
{
	u32 bandwidth;
	struct mrp_traffic_info *traffic;
	char bw[20];
	char bw_max[20];
	char bw_left[20];
	char tbw_max[20];
	char tbw_left[20];
	u32 code_bits = 0;
	struct SRP_stream *stream = t_reserv->stream;

	traffic = get_traffic_info(info, tc);
	traffic->bandwidth_left = traffic->bandwidth_max -
		traffic->bandwidth_used;
	bandwidth = stream->bandwidth;
	format_num(bw, (u32)bandwidth);
	format_num(bw_max, info->bandwidth_max);
	format_num(bw_left, info->bandwidth_left);
	format_num(tbw_max, traffic->bandwidth_max);
	format_num(tbw_left, traffic->bandwidth_left);
#if 0
dbg_msg("bw:%u  %s  %s  %s  %s"NL, port, bw, bw_left, tbw_left, tbw_max);
#endif

	if (bandwidth > traffic->bandwidth_left)
		code_bits |= RFC_NO_BANDWIDTH_TC_BIT;
	if (bandwidth > info->bandwidth_left)
		code_bits |= RFC_NO_BANDWIDTH_BIT;

	/* See if other streams can be dropped to accommodate this one. */
	if (code_bits && bandwidth <= traffic->bandwidth_max) {
		bandwidth -= traffic->bandwidth_left;
		if (drop_other_reserv(mrp, port, info, traffic, t_reserv,
				      bandwidth, drop))
			code_bits = 0;
		else if (tc == SR_CLASS_A &&
			 !(code_bits & RFC_NO_BANDWIDTH_TC_BIT)) {

			/* Class A will have bandwidth from Class B. */
			code_bits = 0;
			if (drop) {
				u32 left;
				u32 used;
				struct mrp_traffic_info *traffic_b;

				traffic_b = get_traffic_info(info, SR_CLASS_B);
				used = traffic->bandwidth_used + bandwidth;
				left = traffic->bandwidth_max - used;
				traffic_b->bandwidth_max =
					traffic_b->bandwidth_delta + left;
				stop_active_reserv(mrp, port, info, traffic_b);
			}
		}
	}

	return code_bits;
}  /* chk_avail_tx_bandwidth */

static int chk_avail_bandwidth(struct mrp_info *mrp, u8 port,
			struct mrp_port_info *info,
			       struct SRP_reserv *t_reserv)
{
	u32 bandwidth;
	int tc;
	struct mrp_traffic_info *traffic;
	int result;
	struct SRP_stream *stream = t_reserv->stream;

	tc = get_traffic_class(mrp, stream->priority);
	traffic = get_traffic_info(info, tc);
	bandwidth = stream->bandwidth;
	t_reserv->code_bits = chk_avail_tx_bandwidth(mrp, port, info, tc,
						     t_reserv, true);
	t_reserv->code = msrp_failure_code(t_reserv->code_bits);

	if (RFC_NO_ERROR == t_reserv->code) {
		struct mrp_node *active;
		u16 fid;
		u16 ports = 1 << port;

		/* Reduce bandwidth */
		info->bandwidth_left -= bandwidth;
		info->bandwidth_used += bandwidth;
		traffic->bandwidth_left -= bandwidth;
		traffic->bandwidth_used += bandwidth;
		if (traffic->bandwidth_other) {
			*traffic->bandwidth_other -= bandwidth;
		}
#if 0
		if (stream->MaxFrameSize > traffic->max_frame_size)
			traffic->max_frame_size = stream->MaxFrameSize;
#endif

		active = create_stream_info(mrp, t_reserv);
		if (!active)
			return SRP_ASKING_FAILED;

		add_reserv(traffic, true, active);

		fid = mrp_get_fid(mrp, stream->vlan_id, stream->dest);
		result = srp_update_mac(mrp, stream->dest, fid, ports, true);
		if (result)
			return SRP_ASKING_FAILED;
#if 0
		result = srp_update_vlan(mrp,
			stream->vlan_id, stream->dest, ports, true);
#endif
		return SRP_READY;
	} else {
		struct mrp_node *passive;

		t_reserv->declaration = SRP_FAILED;
dbg_msg("no bw: %d"NL, t_reserv->code);
		if (!mrp->no_report)
			add_attrib_report(mrp, t_reserv, MRP_ACTION_TX_NEW,
				MRP_TYPE_TALKER, port);
		passive = create_stream_info(mrp, t_reserv);
		if (passive)
			add_reserv(traffic, false, passive);
	}
	return SRP_ASKING_FAILED;
}  /* chk_avail_bandwidth */

static void chk_talker_decl(struct mrp_info *mrp, u8 port,
			struct mrp_port_info *info)
{
	struct SRP_reserv *reserv;

	reserv = info->declared.next;
	while (reserv) {
		/* talker not paired with a listener */
		if (reserv->direction == SRP_TALKER && !reserv->pair &&
		    ((reserv->code && (reserv->code_bits &
		    (RFC_NO_BANDWIDTH_BIT | RFC_NO_BANDWIDTH_TC_BIT))) ||
		    !reserv->code)) {
			int tc;
			u8 code = reserv->code;

			tc = get_traffic_class(mrp, reserv->stream->priority);
			reserv->code_bits =
				chk_avail_tx_bandwidth(mrp, port, info, tc,
						       reserv, false);
			reserv->code = msrp_failure_code(reserv->code_bits);
			if (code != reserv->code) {
				if (reserv->code)
					reserv->declaration = SRP_FAILED;
				else
					reserv->declaration = SRP_ADVERTISE;
				add_attrib_report(mrp, reserv,
					MRP_ACTION_TX_NEW, MRP_TYPE_TALKER,
					port);
			}
		}
		reserv = reserv->next;
	}
}  /* chk_talker_decl */

static int update_reserv(struct mrp_info *mrp, u8 port,
	struct mrp_port_info *info)
{
	struct mrp_traffic_info *traffic;
	int result = DEV_IOC_OK;
	int tc;
#ifdef DEBUG
	char bw_used[20];
	char bw_remain[20];
#endif

	if (!mrp->status.msrpEnabledStatus)
		return result;
	for (tc = SR_CLASS_A; tc >= SR_CLASS_B; tc--) {
		traffic = get_traffic_info(info, tc);
		stop_active_reserv(mrp, port, info, traffic);
#ifdef DEBUG
		format_num(bw_used, traffic->bandwidth_used);
		format_num(bw_remain, traffic->bandwidth_max);
dbg_msg("used %d: %s %s"NL, tc, bw_used, bw_remain);
#endif
	}
	chk_passive_reserv(mrp, port, info);

#ifdef DEBUG
	for (tc = SR_CLASS_A; tc >= SR_CLASS_B; tc--) {
		traffic = get_traffic_info(info, tc);
dbg_msg("  active:"NL);
		mrp_show_node(&traffic->active, show_stream_info);
dbg_msg("  passive:"NL);
		mrp_show_node(&traffic->passive, show_stream_info);
		format_num(bw_used, traffic->bandwidth_used);
dbg_msg("used %d: %s"NL, tc, bw_used);
	}
#endif

	srp_cfg_reserv(mrp, info);

	chk_talker_decl(mrp, port, info);

	if (mrp->report_head)
		result = DEV_IOC_MRP_REPORT;
	return result;
}  /* update_reserv */

static int proc_mrp_tx_listener(struct mrp_info *mrp, u8 port,
				struct mrp_port_info *info,
				struct SRP_reserv *l_reserv,
				struct SRP_reserv *t_reserv,
				struct SRP_stream *stream)
{
	struct mrp_traffic_info *traffic;
	int tc;
	int result = DEV_IOC_OK;
	u8 declaration = l_reserv->declaration;

	/* Talker is not ready. */
	if (SRP_FAILED == stream->t_reserv->declaration) {
dbg_msg("talker not ready"NL);
		declaration = SRP_ASKING_FAILED;
	} else {

		/* Find talker reservation if already created. */
		if (!t_reserv)
			t_reserv = srp_find_reserv(&info->declared,
						   l_reserv->id, SRP_TALKER);
		if (!t_reserv) {
/* talker reservation may not be created yet because of link down. */
dbg_msg("  no t_reserv"NL);
			declaration = SRP_ASKING_FAILED;
		} else {
			if (SRP_FAILED == t_reserv->declaration)
				declaration = SRP_ASKING_FAILED;
#ifdef DEBUG_MSRP_
dbg_msg(" asked: %d"NL, declaration);
#endif
			if (!t_reserv->streamAge) {
				t_reserv->streamAge = get_stream_age(info);
				t_reserv->pair = l_reserv;
				l_reserv->pair = t_reserv;
			}
		}
	}
#ifdef DEBUG_MSRP
	if (t_reserv)
dbg_msg("  T:%d L:%d D:%d"NL, t_reserv->code, l_reserv->code, declaration);
	else
dbg_msg("  L:%d D:%d"NL, l_reserv->code, declaration);
#endif

	tc = get_traffic_class(mrp, stream->priority);
	traffic = get_traffic_info(info, tc);

	/* Check available bandwidth. */
	if (declaration != SRP_ASKING_FAILED) {
#ifdef DEBUG_MSRP_
dbg_msg("not ask failed: %d"NL, l_reserv->code);
#endif

		/* Actual reservation is not made yet. */
		if (RFC_NO_RESOURCES == l_reserv->code) {
#ifdef DEBUG_MSRP_
dbg_msg("not yet"NL);
#endif
			declaration = chk_avail_bandwidth(mrp, port, info,
				t_reserv);
			l_reserv->code = RFC_NO_BANDWIDTH;
			if (declaration != SRP_ASKING_FAILED) {
				l_reserv->code = RFC_NO_ERROR;
				srp_cfg_reserv(mrp, info);
				chk_talker_decl(mrp, port, info);
			}
		} else {
			l_reserv->code = RFC_NO_ERROR;
			start_passive_reserv(mrp, port, info);
			srp_cfg_reserv(mrp, info);
			chk_talker_decl(mrp, port, info);
		}
	} else if (RFC_NO_RESOURCES != l_reserv->code) {

dbg_msg(" no lis: %d"NL, l_reserv->code);
		/* Listener is no longer ready to receive stream. */
		if (l_reserv->code == RFC_NO_ERROR &&
		    drop_active_reserv(mrp, port, info, traffic, t_reserv)) {

			/* Used to indicate reservation is not done yet. */
			l_reserv->code = RFC_NO_BANDWIDTH;
			start_passive_reserv(mrp, port, info);
			srp_cfg_reserv(mrp, info);
			chk_talker_decl(mrp, port, info);
		}
	} else if (t_reserv) {
		struct mrp_node *passive;

		l_reserv->code = RFC_NO_BANDWIDTH;
#ifdef DEBUG_MSRP
dbg_msg("add pas"NL);
#endif
		passive = create_stream_info(mrp, t_reserv);
		if (passive)
			add_reserv(traffic, false, passive);
	}

	/* Used to find out whether to send declaration back to talker. */
	mrp->listeners++;

	if (mrp->report_head)
		result = DEV_IOC_MRP_REPORT;
	return result;
}  /* proc_mrp_tx_listener */

static int mrp_delete_listener(struct mrp_info *mrp, u8 port,
	struct mrp_port_info *info, struct SRP_reserv *l_reserv)
{
	struct SRP_reserv *t_reserv;
	bool drop = false;
	int result = DEV_IOC_OK;
	int active = mrp->status.msrpEnabledStatus &&
		     info->status.msrpPortEnabledStatus;

	/* Check if a talker reservation is using bandwidth. */
	t_reserv = srp_find_reserv(&info->declared, l_reserv->id, SRP_TALKER);
	if (!t_reserv) {
		struct SRP_stream *stream = l_reserv->stream;

		/* Delete listener reservation when leaving. */
		srp_remove_reserv(l_reserv, true);
		if (stream)
			result = mrp_update_listener(mrp, NULL,
				stream, false);
		return result;
	}

	if (t_reserv->declaration == SRP_ADVERTISE &&
	    l_reserv->code == RFC_NO_ERROR) {
		drop = drop_reserv(mrp, port, info, t_reserv, true);
	}
	if (drop) {
#ifdef DEBUG_MSRP
dbg_msg(" drop active"NL);
#endif
#if 1
		if (active)
		start_passive_reserv(mrp, port, info);
#endif
		srp_cfg_reserv(mrp, info);
#if 1
		if (active)
		chk_talker_decl(mrp, port, info);
#endif
	} else {
#ifdef DEBUG_MSRP
dbg_msg(" drop passive"NL);
#endif
		drop_reserv(mrp, port, info, t_reserv, false);
	}

#if 0
	/* Remember the listener state. */
	declaration = l_reserv->declaration;
#endif

	t_reserv->pair = NULL;

	/* Delete listener reservation when leaving. */
	srp_remove_reserv(l_reserv, true);

	/* Update the listener attribute reported back to talker. */
	result = mrp_update_listener(mrp, NULL, t_reserv->stream, false);

	/* Listener reservation is not using bandwidth if not ready. */

	/* no reservation */
	t_reserv->streamAge = 0;

	if (mrp->report_head)
		result = DEV_IOC_MRP_REPORT;
	return result;
}  /* mrp_delete_listener */

static int proc_mrp_lv_listener(struct mrp_info *mrp, u8 port,
	struct SRP_listener *listener)
{
	struct SRP_reserv *l_reserv;
	struct SRP_reserv *t_reserv;
	struct mrp_port_info *info;
	int declaration;
	int result = DEV_IOC_OK;
	bool drop = false;

	info = mrp_get_port_info(mrp, port);
#ifdef DEBUG_MSRP
dbg_msg(" %s p:%d %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x s:%u"NL, __func__,
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
#endif
	l_reserv = srp_find_reserv(&info->registered, listener->id,
				   SRP_LISTENER);
	if (!l_reserv)
{
dbg_msg("  ! not found: %p %d"NL, info, port);
chk_reserv(info, port);
}
	if (!l_reserv)
		return result;
	l_reserv->ticks = jiffies - l_reserv->ticks;
	if (l_reserv->ticks < 100)
dbg_msg(" ?! ");
dbg_msg(" t:%u"NL, l_reserv->ticks * 10 / 1000);

	/* Check if a talker reservation is using bandwidth. */
	t_reserv = srp_find_reserv(&info->declared, listener->id, SRP_TALKER);
	if (!t_reserv) {
		struct SRP_stream *stream = l_reserv->stream;

		/* Delete listener reservation when leaving. */
		srp_remove_reserv(l_reserv, true);
		if (stream)
			result = mrp_update_listener(mrp, NULL,
				stream, false);
		return result;
	}

	if (t_reserv->declaration == SRP_ADVERTISE &&
	    l_reserv->code == RFC_NO_ERROR) {
		drop = drop_reserv(mrp, port, info, t_reserv, true);
	}
	if (drop) {
#ifdef DEBUG_MSRP
dbg_msg(" drop active"NL);
#endif
		start_passive_reserv(mrp, port, info);
		srp_cfg_reserv(mrp, info);
		chk_talker_decl(mrp, port, info);
	} else {
#ifdef DEBUG_MSRP
dbg_msg(" drop passive"NL);
#endif
		drop_reserv(mrp, port, info, t_reserv, false);
	}

	/* Remember the listener state. */
	declaration = l_reserv->declaration;

	t_reserv->pair = NULL;

	/* Delete listener reservation when leaving. */
	srp_remove_reserv(l_reserv, true);

	/* Update the listener attribute reported back to talker. */
	result = mrp_update_listener(mrp, NULL, t_reserv->stream, false);

	/* Listener reservation is not using bandwidth if not ready. */

	/* no reservation */
	t_reserv->streamAge = 0;

	if (mrp->report_head)
		result = DEV_IOC_MRP_REPORT;
	return result;
}  /* proc_mrp_lv_listener */

static int proc_mrp_rx_listener(struct mrp_info *mrp, u8 port,
	struct SRP_listener *listener, u8 new_decl)
{
	int result = DEV_IOC_OK;
	u8 declaration = SRP_READY;
	struct SRP_reserv *l_reserv;
	struct SRP_stream *stream;
	struct mrp_port_info *info;

	info = mrp_get_port_info(mrp, port);
#ifdef DEBUG_MSRP
dbg_msg(" %s p:%d %d %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x s:%u"NL, __func__,
port, new_decl,
listener->id[0],
listener->id[1],
listener->id[2],
listener->id[3],
listener->id[4],
listener->id[5],
listener->id[6],
listener->id[7],
listener->substate);
#endif
	if (SRP_IGNORED == listener->substate)
		return DEV_IOC_INVALID_CMD;

	declaration = listener->substate;
	stream = srp_find_stream_id(mrp, listener->id);

	/* Create reservation if new. */
	l_reserv = srp_find_reserv(&info->registered, listener->id,
				   SRP_LISTENER);
	if (!l_reserv) {
		l_reserv = srp_create_reserv(listener->id, SRP_LISTENER,
					     declaration, 0, mrp->id,
					     RFC_NO_RESOURCES);
		if (!l_reserv)
			return -ENOMEM;

		srp_insert_reserv(&info->registered, l_reserv);
	} else {
		l_reserv->declaration = declaration;
	}

	/* Stream may not exist yet when listener is received. */
	l_reserv->stream = stream;

	/* There is a talker. */
	if (stream && stream->t_reserv && stream->in_port != port) {
		int rc;
		struct SRP_reserv *reserv;

		mrp->listeners = 0;
		result = proc_mrp_tx_listener(mrp, port, info, l_reserv, NULL,
			stream);

		/* Likely due to errors. */
		if (!mrp->listeners)
			return result;

		info = mrp_get_port_info(mrp, stream->in_port);
		reserv = mrp_link_listener(mrp, info, stream);
		if (!reserv)
			return -ENOMEM;

		if (!new_decl) {
			struct ksz_sw *sw = mrp->parent;

			if (sw->ops->get_tcDetected(sw, port))
				new_decl = true;
		}

		/* Listener declaration will be updated in following call. */
		rc = mrp_update_listener(mrp, reserv, stream, new_decl);
		if (DEV_IOC_OK != rc)
			result = rc;
	}
else {
if (!stream)
dbg_msg("no talker stream?"NL);
else if (!stream->t_reserv)
dbg_msg("no talker reserv?"NL);
else
dbg_msg("wrong port: %d %d"NL, port, stream->in_port);
}
	if (mrp->report_head)
		result = DEV_IOC_MRP_REPORT;
	return result;
}  /* proc_mrp_rx_listener */

static u32 mrp_chk_as_port(struct mrp_info *mrp, u8 port,
			struct mrp_port_info *info, int tc)
{
	int avb_a;
	int avb_b;
	int asCapable;
	int i;
	u32 code_bits = 0;
	struct ksz_port_cfg *cfg;
	struct ksz_sw *sw = mrp->parent;

	cfg = get_port_cfg(sw, port);
	avb_a = cfg->avb_a;
	avb_b = cfg->avb_b;
	asCapable = cfg->asCapable | cfg->asCapable_set;
	if (!asCapable)
		code_bits |= RFC_ASCAPABLE_BIT;
	if (tc != SR_CLASS_A && tc != SR_CLASS_B)
		code_bits |= RFC_PRIORITY_BIT;
	for (i = SR_CLASS_A; i >= SR_CLASS_B; i--) {
		if (i != tc)
			continue;
		if (mrp->domain[tc - SR_CLASS_B].id &&
		    info->priority[tc].SRPdomainBoundaryPort)
			code_bits |= RFC_SRP_BOUNDARY_BIT;
	}

#if 1
	if (fqtss_34_2_1b_hack && port < 3)
		code_bits = 0;
#endif

	/* need at least 100 Mbps and full-duplex */
	if (!info->duplex)
		code_bits |= RFC_ASCAPABLE_BIT;
	if (tc == SR_CLASS_A && mrp->domain[1].id)
		cfg->avb_a = code_bits ? false : true;
	else if (tc == SR_CLASS_B)
		cfg->avb_b = code_bits ? false : true;
if (port < 3 && (avb_a != cfg->avb_a || avb_b != cfg->avb_b))
dbg_msg("  avb: %d=%d:%d %x"NL, port, cfg->avb_a, cfg->avb_b, code_bits);
	return code_bits;
}  /* mrp_chk_as_port */

static void mrp_chk_rx_talker(struct mrp_info *mrp, u8 port,
				struct mrp_port_info *info,
				  struct SRP_talker *talker,
				  struct SRP_reserv *reserv)
{
	u8 code = talker->FailureCode;
	u8 new_code = reserv->code;
	u32 code_bits = 0;
	const u8 *bridge_id = talker->bridge_id;
	struct SRP_stream *stream_id = NULL;

	stream_id = srp_find_stream_id(mrp, talker->id);

	/* Stream should alway be found unless out of resource. */
	if (!stream_id)
		code_bits |= RFC_NO_RESOURCES_BIT;
	if (memcmp(stream_id->dest, talker->dest, ETH_ALEN) &&
	    (stream_id->MaxFrameSize != talker->MaxFrameSize ||
	    stream_id->MaxIntervalFrames != talker->MaxIntervalFrames)) {
dbg_msg(" used by other: %x"NL, code_bits);
		code_bits |= RFC_STREAM_ID_BIT;
		code_bits |= RFC_FIRSTVALUE_CHANGED_BIT;
	}
	if (code_bits)
		goto get_talker_done;

	/* Check FirstValue. */
	if (stream_id->latency != talker->AccumulatedLatency)
{
dbg_msg(" L: %x %x"NL, stream_id->latency, talker->AccumulatedLatency);
		code_bits |= RFC_LATENCY_CHANGED_BIT;
}
#if 1
	if (msrp_35_1_14g_hack)
		talker->reserved = 0;
#endif
	if (memcmp(stream_id->dest, talker->dest, ETH_ALEN) ||
	    stream_id->vlan_id != talker->vlan_id ||
	    stream_id->MaxFrameSize != talker->MaxFrameSize ||
	    stream_id->MaxIntervalFrames != talker->MaxIntervalFrames ||
	    stream_id->priority != talker->priority ||
	    stream_id->rank != talker->rank ||
	    stream_id->reserved != talker->reserved) {
		code_bits |= RFC_FIRSTVALUE_CHANGED_BIT;
		goto get_talker_done;
	}

	/* Use original code from talker. */
	if (code)
		goto get_talker_done;

	code_bits |= mrp_chk_as_port(mrp, port, info,
		get_traffic_class(mrp, talker->priority));
	if (talker->MaxFrameSize > 1500)
		code_bits |= RFC_MAXFRAMESIZE_BIT;
	if (!talker->MaxIntervalFrames)
		code_bits |= RFC_NO_BANDWIDTH_BIT;

get_talker_done:
	new_code = msrp_failure_code(code_bits);
#ifdef DEBUG_MSRP
if (port < 3 && new_code)
dbg_msg(" new_code rx: %04x %d %d"NL, code_bits, code, new_code);
#endif

	/* This bridge finds a problem. */
	if (!code && new_code != code) {
		bridge_id = mrp->id;
		code = new_code;
		memcpy(reserv->bridge_id, bridge_id, 8);
	}
	reserv->code = code;
	reserv->code_bits = code_bits;
}  /* mrp_chk_rx_talker */

static void mrp_chk_tx_talker(struct mrp_info *mrp, u8 port,
				struct mrp_port_info *info,
				  struct SRP_reserv *reserv)
{
	int tc;
	u8 code = reserv->code;
	u8 new_code = reserv->code;
	u32 code_bits = 0;
	const u8 *bridge_id = reserv->bridge_id;

	tc = get_traffic_class(mrp, reserv->stream->priority);
	code_bits |= mrp_chk_as_port(mrp, port, info, tc);
	if (code || code_bits)
		goto chk_tx_talker_done;

	do {
		int bit;
		int index;
		struct ksz_port_cfg *cfg;
		struct ksz_sw *sw = mrp->parent;

		cfg = get_port_cfg(sw, port);
		index = reserv->stream->vlan_id / VID_IN_DATA;
		bit = reserv->stream->vlan_id % VID_IN_DATA;
		if (cfg->untagged[index] & (1 << bit)) {
			code_bits = RFC_VLAN_TAGGING_BIT;
			goto chk_tx_talker_done;
		}
	} while (0);

	code_bits = chk_avail_tx_bandwidth(mrp, port, info, tc, reserv, false);

chk_tx_talker_done:
	new_code = msrp_failure_code(code_bits);
#ifdef DEBUG_MSRP
if (new_code && port < 3)
dbg_msg(" new_code tx: %d=%04x %d %d"NL, port, code_bits, code, new_code);
#endif

	/* This bridge finds a problem. */
	if (new_code != code) {
		bridge_id = mrp->id;
		code = new_code;
		memcpy(reserv->bridge_id, bridge_id, 8);
	}
	reserv->code = code;
	reserv->code_bits = code_bits;

	reserv->declaration = code ? SRP_FAILED : SRP_ADVERTISE;

#if 0
	/* A listener is paired. */
	if (reserv->pair) {
		if (code || reserv->pair->declaration == SRP_ASKING_FAILED)
			reserv->pair->code = RFC_NO_BANDWIDTH;
		else
			reserv->pair->code = RFC_NO_ERROR;
	}
#endif
}  /* mrp_chk_tx_talker */

static u32 mrp_max_latency(struct mrp_info *mrp, struct mrp_port_info *info,
			int index,
			struct SRP_talker *talker)
{
	u32 MaxPacketSize = 1542;
	u32 MaxAllocBand;
	u32 portTransmitRate = info->speed;
	u32 MaxFrameSize = talker->MaxFrameSize;
	u32 t_Interval = 125000;
	u64 t_AllStreams;
	u32 t_MaxPacketSize;
	u32 t_StreamPacket;
	u32 t_Mbps = 1;
	u32 t_IPG = 12;
	int q1;
	int q2;
	u64 val;
	u32 rem;

if (!portTransmitRate)
dbg_msg(" !! %s"NL, __func__);
	if (!portTransmitRate)
		portTransmitRate = 100;
	q1 = get_queue_priority(mrp, SR_CLASS_A);
	q2 = get_queue_priority(mrp, SR_CLASS_B);
	MaxAllocBand = info->bandwidth[q1].deltaBandwidth +
		       info->bandwidth[q2].deltaBandwidth;
if (!MaxAllocBand)
dbg_msg(" !! %s"NL, __func__);
	if (!MaxAllocBand)
		MaxAllocBand = 75;
	if (!index)
		t_Interval *= 2;
	if (portTransmitRate != 1000) {
		t_Mbps *= 10;
		t_IPG *= 10;
	}
	MaxFrameSize += 22 + 8;
	t_AllStreams = MaxAllocBand * t_Interval;
	t_StreamPacket = MaxFrameSize * 8 * t_Mbps;
	t_MaxPacketSize = MaxPacketSize * 8 * t_Mbps;
	val = t_AllStreams;
	val = div_u64_u32(val, portTransmitRate);
	val -= t_StreamPacket;
	val -= t_IPG;
	val *= portTransmitRate;
	val = div_u64_u32(val, MaxAllocBand);
	val += t_StreamPacket;
	val += t_MaxPacketSize;
	rem = (u32) val;
	rem += info->latency[index].portTcMaxLatency;
	return rem;
}

static int proc_mrp_tx_talker(struct mrp_info *mrp, u8 port,
			      struct SRP_talker *talker,
			      struct SRP_reserv *reserv, u8 new_decl)
{
	int index;
	u8 declaration;
	u8 code = talker->FailureCode;
	const u8 *bridge_id = talker->bridge_id;
	u32 latency = talker->AccumulatedLatency;
	struct SRP_stream *stream_id = NULL;
	struct SRP_reserv *t_reserv;
	struct SRP_reserv *l_reserv;
	struct mrp_port_info *info;
	int result = DEV_IOC_OK;

	info = mrp_get_port_info(mrp, port);
	stream_id = srp_find_stream_id(mrp, talker->id);

	/* Create reservation if new. */
	t_reserv = srp_find_reserv(&info->declared, talker->id, SRP_TALKER);
	code = reserv->code;
	bridge_id = reserv->bridge_id;
	declaration = code ? SRP_FAILED : SRP_ADVERTISE;
	index = get_traffic_index(get_traffic_class(mrp, talker->priority));
#if 1
	if (!mrp_10_5_1c_hack)
#endif
	latency += mrp_max_latency(mrp, info, index, talker);
	if (!t_reserv) {
		if (!code)
			bridge_id = mrp->id;
		t_reserv = srp_create_reserv(talker->id, SRP_TALKER,
					     declaration, latency, bridge_id,
					     code);
		if (!t_reserv)
			return -ENOMEM;

		t_reserv->stream = stream_id;
		srp_insert_reserv(&info->declared, t_reserv);
	} else {
		t_reserv->declaration = declaration;
		memcpy(t_reserv->bridge_id, bridge_id, 8);
		t_reserv->code = code;
		t_reserv->rx_code = code;
	}
	t_reserv->code_bits = reserv->code_bits;

	/* Check outgoing failures. */
	if (!t_reserv->code)
		mrp_chk_tx_talker(mrp, port, info, t_reserv);

	if (!mrp->no_report) {
		u8 action = MRP_ACTION_TX;

		if (!new_decl && !code && t_reserv->code)
			new_decl = true;
		if (new_decl)
			action = MRP_ACTION_TX_NEW;
		add_attrib_report(mrp, t_reserv, action,
			MRP_TYPE_TALKER, port);
	}

	l_reserv = srp_find_reserv(&info->registered, talker->id,
				   SRP_LISTENER);
	if (l_reserv) {
		int rc;

dbg_msg("have listen: %d=%p"NL, port, l_reserv);
		rc = proc_mrp_tx_listener(mrp, port, info, l_reserv, t_reserv,
			t_reserv->stream);
	}

	/* Ask application to retrieve attributes. */
	if (mrp->report_head)
		result = DEV_IOC_MRP_REPORT;
	return result;
}  /* proc_mrp_tx_talker */

static int mrp_delete_talker(struct mrp_info *mrp, u8 port,
	struct mrp_port_info *info, struct SRP_reserv *reserv)
{
	struct SRP_reserv *l_reserv;
	struct SRP_reserv *t_reserv;
	uint n;
	uint q;
	struct ksz_sw *sw = mrp->parent;
	int result = DEV_IOC_OK;
	struct mrp_node *mac_node;
#if 1
	struct mrp_node *vlan_node;
	struct mrp_vlan_info data;
#endif
	struct mrp_mac_info mac_data;
	u16 fid = 0;
	int free = true;
	int active = mrp->status.msrpEnabledStatus &&
		     info->status.msrpPortEnabledStatus;
	int active_other;

	/* No listener propagation if no talker. */
	l_reserv = srp_find_reserv(&info->declared, reserv->id,
		SRP_LISTENER);
	if (l_reserv) {
		srp_remove_reserv(l_reserv, true);
	}

	for (n = 0; n <= mrp->ports; n++) {
		q = get_phy_port(sw, n);
		if (q == port)
			continue;

		info = mrp_get_port_info(mrp, q);
		active_other = mrp->status.msrpEnabledStatus &&
			info->status.msrpPortEnabledStatus;
		if (!info->status.msrpPortEnabledStatus)
			continue;
		t_reserv = srp_find_reserv(&info->declared, reserv->id,
					   SRP_TALKER);
		if (!t_reserv)
			continue;

		/* Unlink listener from talker. */
		l_reserv = srp_find_reserv(&info->registered, reserv->id,
					   SRP_LISTENER);
		if (l_reserv) {
			bool dropped = false;

			l_reserv->pair = NULL;

			/* stream will be deleted */
			l_reserv->stream = NULL;

			/* Drop reservation if listener is ready. */
			if (l_reserv->declaration != SRP_ASKING_FAILED) {
				dropped = drop_reserv(mrp, q, info, t_reserv,
						      true);
				if (dropped) {
if (l_reserv->code != RFC_NO_ERROR)
dbg_msg(" not ok? %d"NL, l_reserv->code);
#if 1
					if (active_other)
					start_passive_reserv(mrp, q, info);
#endif
				}
#ifdef DEBUG_MSRP
else
dbg_msg(" not dropped"NL);
#endif
			}
			if (!dropped)
				drop_reserv(mrp, q, info, t_reserv, false);
			l_reserv->code = RFC_NO_RESOURCES;
		}

		free = true;
#if 1
		/* Reservation will be freed after reporting leaving. */
		if (!mrp->no_report && active_other) {
			free = false;
			add_attrib_report(mrp, t_reserv, MRP_ACTION_LV,
				MRP_TYPE_TALKER, q);
		}
#endif
		srp_remove_reserv(t_reserv, free);
	}

	srp_cfg_reserv(mrp, NULL);

	free = true;
#if 1
	/* This is purely used to free the stream after reporting. */
	if (!mrp->no_report && active) {
		free = false;
		add_attrib_report(mrp, reserv, MRP_ACTION_LV, MRP_TYPE_TALKER,
			sw->port_cnt);
	}
#endif

#if 1
	data.vid = reserv->stream->vlan_id;
	memcpy(data.addr, reserv->stream->dest, ETH_ALEN);
	vlan_node = mrp_find_node(&mrp->vlan_list, cmp_vlan, &data);
	if (vlan_node) {
#if 0
		u16 ports;
#endif
		struct mrp_vlan_info *vlan = NULL;

#ifdef DEBUG_MRP_BASIC
		mrp_show_node(&mrp->vlan_list, show_vlan_info);
#endif
		vlan = vlan_node->data;
		fid = vlan->fid;
		vlan->ports &= SRP_PORT_AVAIL;
#if 0
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
#endif
	} else
		fid = mrp_alloc_fid(mrp, data.vid);
#endif
	mac_data.fid = fid;
	memcpy(mac_data.addr, reserv->stream->dest, ETH_ALEN);
	mac_node = mrp_find_node(&mrp->mac_list, cmp_mac, &mac_data);
#if 1
	if (!mac_node) {
dbg_msg(" not found! %d %02x:%02x"NL, fid, mac_data.addr[4], mac_data.addr[5]);
		mrp_show_node(&mrp->mac_list, show_mac_info);
	}
#endif
	if (mac_node) {
		struct mrp_mac_info *mac = NULL;

#ifdef DEBUG_MRP_BASIC
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
	srp_remove_stream(reserv->stream, free);
	srp_remove_reserv(reserv, free);

	for (n = 0; n <= mrp->ports; n++) {
		q = get_phy_port(sw, n);
		if (q == port)
			continue;

		info = mrp_get_port_info(mrp, q);
		active_other = mrp->status.msrpEnabledStatus &&
			info->status.msrpPortEnabledStatus;
		if (!active_other)
			continue;
		chk_talker_decl(mrp, q, info);
	}

	if (mrp->report_head)
		result = DEV_IOC_MRP_REPORT;
	return result;
}  /* mrp_delete_talker */

static int proc_mrp_lv_talker(struct mrp_info *mrp, u8 port,
	struct SRP_talker *talker)
{
	struct SRP_reserv *l_reserv;
	struct SRP_reserv *reserv;
	struct SRP_reserv *t_reserv;
	struct mrp_port_info *info;
	int result = DEV_IOC_OK;
	uint n;
	uint q;
	struct ksz_sw *sw = mrp->parent;
	struct mrp_node *mac_node;
#if 1
	struct mrp_node *vlan_node;
	struct mrp_vlan_info data;
#endif
	struct mrp_mac_info mac_data;
	u16 fid = 0;
	int free = true;

	info = mrp_get_port_info(mrp, port);
#ifdef DEBUG_MSRP
dbg_msg(" %s p:%d %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x"NL, __func__,
port,
talker->id[0],
talker->id[1],
talker->id[2],
talker->id[3],
talker->id[4],
talker->id[5],
talker->id[6],
talker->id[7]);
dbg_msg("  %02x:%02x:%02x:%02x:%02x:%02x %03x %u:%u f:%u i:%u l:%u c:%u"NL,
talker->dest[0],
talker->dest[1],
talker->dest[2],
talker->dest[3],
talker->dest[4],
talker->dest[5],
talker->vlan_id, talker->priority, talker->rank,
talker->MaxFrameSize, talker->MaxIntervalFrames, talker->AccumulatedLatency,
talker->FailureCode);
#endif
	reserv = srp_find_reserv(&info->registered, talker->id, SRP_TALKER);
	if (!reserv)
		return result;
	reserv->ticks = jiffies - reserv->ticks;
	if (reserv->ticks < 100)
dbg_msg(" ?! ");
dbg_msg(" t:%u"NL, reserv->ticks * 10 / 1000);

	/* No listener propagation if no talker. */
	l_reserv = srp_find_reserv(&info->declared, talker->id, SRP_LISTENER);
	if (l_reserv) {
		free = false;
		add_attrib_report(mrp, l_reserv, MRP_ACTION_LV,
			MRP_TYPE_LISTENER, port);
		srp_remove_reserv(l_reserv, free);
		free = true;
	}

	for (n = 0; n <= mrp->ports; n++) {
		q = get_phy_port(sw, n);
		if (q == port)
			continue;

		info = mrp_get_port_info(mrp, q);
#if 1
		if (!info->status.msrpPortEnabledStatus)
			continue;
#endif
		t_reserv = srp_find_reserv(&info->declared, talker->id,
					   SRP_TALKER);
		if (!t_reserv)
			continue;

		/* Unlink listener from talker. */
		l_reserv = srp_find_reserv(&info->registered, talker->id,
					   SRP_LISTENER);
		if (l_reserv) {
			bool dropped = false;

			l_reserv->pair = NULL;

			/* stream will be deleted */
			l_reserv->stream = NULL;

			/* Drop reservation if listener is ready. */
			if (l_reserv->declaration != SRP_ASKING_FAILED) {
				dropped = drop_reserv(mrp, q, info, t_reserv,
						      true);
				if (dropped) {
if (l_reserv->code != RFC_NO_ERROR)
dbg_msg(" not ok? %d"NL, l_reserv->code);
					start_passive_reserv(mrp, q, info);
				}
#ifdef DEBUG_MSRP
else
dbg_msg(" not dropped"NL);
#endif
			}
			if (!dropped)
				drop_reserv(mrp, q, info, t_reserv, false);
			l_reserv->code = RFC_NO_RESOURCES;
		}

		/* Reservation will be freed after reporting leaving. */
		if (!mrp->no_report) {
			free = false;
			add_attrib_report(mrp, t_reserv, MRP_ACTION_LV,
				MRP_TYPE_TALKER, q);
		}
		srp_remove_reserv(t_reserv, free);
	}

	srp_cfg_reserv(mrp, NULL);

	/* This is purely used to free the stream after reporting. */
	if (!mrp->no_report) {
		free = false;
		add_attrib_report(mrp, reserv, MRP_ACTION_LV, MRP_TYPE_TALKER,
			sw->port_cnt);
	}
if (memcmp(reserv->stream->dest, talker->dest, ETH_ALEN))
dbg_msg("  not same dest! %02x:%02x %02x:%02x"NL,
reserv->stream->dest[4], reserv->stream->dest[5],
talker->dest[4], talker->dest[5]);
#if 1
	data.vid = reserv->stream->vlan_id;
	memcpy(data.addr, reserv->stream->dest, ETH_ALEN);
	vlan_node = mrp_find_node(&mrp->vlan_list, cmp_vlan, &data);
	if (vlan_node) {
#if 0
		u16 ports;
#endif
		struct mrp_vlan_info *vlan = NULL;

#ifdef DEBUG_MRP_BASIC
		mrp_show_node(&mrp->vlan_list, show_vlan_info);
#endif
		vlan = vlan_node->data;
		fid = vlan->fid;
		vlan->ports &= SRP_PORT_AVAIL;
#if 0
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
#endif
	} else
		fid = mrp_alloc_fid(mrp, data.vid);
#endif
	mac_data.fid = fid;
	memcpy(mac_data.addr, reserv->stream->dest, ETH_ALEN);
	mac_node = mrp_find_node(&mrp->mac_list, cmp_mac, &mac_data);
#if 1
	if (!mac_node) {
dbg_msg(" not found! %d %02x:%02x"NL, fid, mac_data.addr[4], mac_data.addr[5]);
		mrp_show_node(&mrp->mac_list, show_mac_info);
	}
#endif
	if (mac_node) {
		struct mrp_mac_info *mac = NULL;

#ifdef DEBUG_MRP_BASIC
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
	srp_remove_stream(reserv->stream, free);
	srp_remove_reserv(reserv, free);

	for (n = 0; n <= mrp->ports; n++) {
		q = get_phy_port(sw, n);
		if (q == port)
			continue;

		info = mrp_get_port_info(mrp, q);
		if (!info->status.msrpPortEnabledStatus)
			continue;
		chk_talker_decl(mrp, q, info);
	}

	if (mrp->report_head)
		result = DEV_IOC_MRP_REPORT;
	return result;
}  /* proc_mrp_lv_talker */

static int proc_mrp_rx_talker(struct mrp_info *mrp, u8 port,
	struct SRP_talker *talker, u8 new_decl)
{
	uint n;
	uint q;
	struct ksz_sw *sw = mrp->parent;
	int result = DEV_IOC_OK;
	u8 declaration;
	struct SRP_reserv *reserv;
	struct SRP_stream *stream;
	struct mrp_port_info *info;
	u8 code = talker->FailureCode;
	u32 code_bits = 0;

	info = mrp_get_port_info(mrp, port);
#ifdef DEBUG_MSRP
dbg_msg(" %s p:%d %d %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x"NL, __func__,
port,
new_decl,
talker->id[0],
talker->id[1],
talker->id[2],
talker->id[3],
talker->id[4],
talker->id[5],
talker->id[6],
talker->id[7]);
dbg_msg("  %02x:%02x:%02x:%02x:%02x:%02x %03x %u:%u f:%u i:%u l:%u c:%u"NL,
talker->dest[0],
talker->dest[1],
talker->dest[2],
talker->dest[3],
talker->dest[4],
talker->dest[5],
talker->vlan_id, talker->priority, talker->rank,
talker->MaxFrameSize, talker->MaxIntervalFrames, talker->AccumulatedLatency,
talker->FailureCode);
#endif

	/* Create stream if new. */
	stream = srp_find_stream_id(mrp, talker->id);
	if (!stream) {
		stream = srp_find_dest_addr(mrp, talker->dest);
		if (stream)
			code_bits = RFC_DEST_ADDR_BIT;
		stream = srp_create_stream(talker->id, talker->dest,
			talker->vlan_id, talker->MaxFrameSize,
			talker->MaxIntervalFrames, talker->priority,
			talker->rank, talker->reserved,
			talker->AccumulatedLatency);
		if (stream) {
#ifdef DEBUG_MSRP
			char bw_str1[20];
#endif
			int tc = get_traffic_class(mrp, stream->priority);

			stream->bandwidth =
				calculate_bandwidth(stream->MaxFrameSize,
						    stream->MaxIntervalFrames,
						    frames_per_sec(tc));
#ifdef DEBUG_MSRP
		format_num(bw_str1, stream->bandwidth);
dbg_msg("bw: %s"NL, bw_str1);
#endif
			srp_insert_stream_by_id(mrp, stream);
			srp_insert_stream_by_dest(mrp, stream);
		}
	}
	if (!stream)
		return -ENOMEM;

	/* Create reservation if new. */
	reserv = srp_find_reserv(&info->registered, talker->id, SRP_TALKER);
	declaration = code ? SRP_FAILED : SRP_ADVERTISE;
	if (!reserv) {
		struct mrp_node *node;
		struct mrp_mac_info *mac;
#if 0
		struct mrp_vlan_info *vlan;
		u8 index;
#endif
		u16 fid;
		u16 ports = 1 << port;

		reserv = srp_create_reserv(talker->id, SRP_TALKER,
					   declaration,
					   talker->AccumulatedLatency,
					   talker->bridge_id, code);
		if (!reserv)
			return -ENOMEM;

		/* Indicate registration source. */
		reserv->streamAge = 0;
		srp_insert_reserv(&info->registered, reserv);
		stream->in_port = port;
		stream->t_reserv = reserv;

#if 0
		/* Setup initial VLAN configuration. */
		ports = mrp_find_vlan_ports(&mrp->vlan_list, talker->vlan_id,
			&index, &fid);
		node = mrp_get_vlan_info(&mrp->vlan_list, talker->vlan_id,
#if 0
			talker->dest);
#else
			NULL);
#endif
		if (!node)
			return -ENOMEM;
		vlan = node->data;
#if 0
		vlan->ports = SRP_PORT_READY;
#endif
		ports = vlan->ports;

		/* First time setting up VLAN table. */
		if (!ports) {
			vlan->index = mrp_alloc_vlan(mrp);
			vlan->fid = mrp_alloc_fid(mrp, vlan->vid);
#if 1
			vlan->ports = SRP_PORT_READY;
#endif
			mrp_cfg_vlan(mrp, vlan->index, vlan->vid, vlan->fid,
				vlan->ports);
#if 0
		} else {
			vlan->index = index;
			vlan->fid = fid;
		}
#endif
		}
#endif
		fid = mrp_alloc_fid(mrp, talker->vlan_id);

		/* Setup initial MAC configuration. */
		node = mrp_get_mac_info(&mrp->mac_list, talker->dest, fid);
		if (!node)
			return -ENOMEM;
		mac = node->data;
		ports = mac->ports;
		mac->rx_ports |= ports;
		mac->srp_ports = SRP_PORT_READY;
		mac->ports = mac->mrp_ports | mac->srp_ports;

		/* First time setting up MAC table. */
		if (!ports) {
			int tc;
			struct ksz_port_cfg *cfg;
			struct ksz_sw *sw = mrp->parent;

			tc = get_traffic_class(mrp, stream->priority);
			cfg = get_port_cfg(sw, port);
			if ((tc == SR_CLASS_A && cfg->avb_a) ||
			    (tc == SR_CLASS_B && cfg->avb_b))
				ports = mac->ports;
			else
				ports = SRP_PORT_OTHER;
			mac->index = mrp_alloc_mac(mrp);
			mrp_cfg_dest_addr(mrp, mac->index, mac->addr,
				ports, mac->fid);
		}
#ifdef DEBUG_MRP_BASIC
		mrp_show_node(&mrp->mac_list, show_mac_info);
		mrp_show_node(&mrp->vlan_list, show_vlan_info);
#endif
	} else {
		reserv->declaration = declaration;
		reserv->latency = talker->AccumulatedLatency;
		memcpy(reserv->bridge_id, talker->bridge_id, 8);
		reserv->code = code;
		reserv->rx_code = code;
	}
	reserv->stream = stream;
	if (code_bits) {
		reserv->code_bits = code_bits;
		reserv->code = msrp_failure_code(reserv->code_bits);
		memcpy(reserv->bridge_id, mrp->id, 8);
	} else

	/* Check incoming failures. */
	mrp_chk_rx_talker(mrp, port, info, talker, reserv);

	if (!new_decl) {
		struct ksz_sw *sw = mrp->parent;

		if (sw->ops->get_tcDetected(sw, port))
			new_decl = true;
		if (!new_decl && !talker->FailureCode && reserv->code)
			new_decl = true;
	}

	mrp->listeners = 0;
	for (n = 0; n <= mrp->ports; n++) {
		q = get_phy_port(sw, n);
		if (q == port)
			continue;
		info = mrp_get_port_info(mrp, q);
		if (!info->status.msrpPortEnabledStatus)
			continue;
		if (!info->link)
			continue;
		result = proc_mrp_tx_talker(mrp, q, talker, reserv, new_decl);
		if (result < 0)
			return result;
		reserv->tx_ports |= (1 << q);
	}

	/* There are no listeners. */
	if (!mrp->listeners)
		return result;

	info = mrp_get_port_info(mrp, port);
	reserv = mrp_link_listener(mrp, info, stream);
	if (!reserv)
		return -ENOMEM;

	/* Listener declaration will be updated in following call. */
	result = mrp_update_listener(mrp, reserv, stream, false);
	return result;
}  /* proc_mrp_rx_talker */

static void mrp_change_tx_reserv(struct mrp_info *mrp, u8 port,
	struct mrp_port_info *info,
	struct SRP_reserv *reserv, bool *drop)
{
	u8 action;
	u8 code;
	u8 decl;

	if (SRP_TALKER != reserv->direction || reserv->rx_code)
		return;

	code = reserv->code;
	decl = reserv->declaration;

	mrp_chk_tx_talker(mrp, port, info, reserv);
	if (code == reserv->code)
		return;

	action = MRP_ACTION_TX;

	if (reserv->streamAge) {
		if (reserv->code == RFC_PORT_IS_NOT_AVB) {
			int tc = get_traffic_class(mrp,
				reserv->stream->priority);

			drop[tc] = true;
		}
	}
	if (decl != reserv->declaration)
		action = MRP_ACTION_TX_NEW;
	add_attrib_report(mrp, reserv, action, MRP_TYPE_TALKER, port);
}  /* mrp_change_tx_reserv */

static void mrp_drop_reserv(struct mrp_info *mrp, u8 port,
			struct mrp_port_info *info, bool *drop)
{
	struct mrp_traffic_info *traffic;
	int rc;
	int tc;
	void *param[6];

	for (tc = SR_CLASS_A; tc >= SR_CLASS_B; tc--) {
		traffic = get_traffic_info(info, tc);
		if (!drop[tc])
			continue;

		/* Mark all streams to stop. */
		rc = stream_iter(&traffic->active, param, stream_set_mark);
		info->bandwidth_used -= traffic->bandwidth_used;
		traffic->bandwidth_used = 0;
		traffic->bandwidth_left = traffic->bandwidth_max;
		if (traffic->bandwidth_other)
			*traffic->bandwidth_other = *traffic->bandwidth_avail +
				traffic->bandwidth_left;
		param[0] = mrp;
		param[1] = traffic;
		param[2] = &port;
		rc = stream_oper(&traffic->active, param, stream_stop);
	}
	info->bandwidth_left = info->bandwidth_max - info->bandwidth_used;
	chk_passive_reserv(mrp, port, info);

	srp_cfg_reserv(mrp, info);
}  /* mrp_drop_reserv */

static bool mrp_match_tx_reserv(struct mrp_info *mrp, u8 port,
	struct mrp_port_info *info,
	struct SRP_reserv *reserv, struct SRP_reserv *t_reserv)
{
	bool drop[8];
	u8 code;
	u8 decl;

	if (SRP_TALKER != t_reserv->direction ||
	    t_reserv->stream != reserv->stream)
		return false;

	code = t_reserv->code;
	decl = t_reserv->declaration;

	/* use error codes from receive side */
	t_reserv->code_bits = reserv->code_bits;
	t_reserv->code = reserv->code;
	t_reserv->rx_code = reserv->code;
	t_reserv->declaration = t_reserv->code ? SRP_FAILED : SRP_ADVERTISE;
	if (!reserv->code)
		mrp_chk_tx_talker(mrp, port, info, t_reserv);
	drop[SR_CLASS_A] = 0;
	drop[SR_CLASS_B] = 0;
	if (code != t_reserv->code) {
		u8 action = MRP_ACTION_TX;

dbg_msg(" co: %d %d"NL, code, t_reserv->code);
		if (t_reserv->streamAge) {
			if (t_reserv->code == RFC_PORT_IS_NOT_AVB) {
				int tc = get_traffic_class(mrp,
					t_reserv->stream->priority);

dbg_msg("drop"NL);
				drop[tc] = true;
			}
		}
		if (decl != t_reserv->declaration)
			action = MRP_ACTION_TX_NEW;
		add_attrib_report(mrp, t_reserv, action, MRP_TYPE_TALKER, port);
	}
	mrp_drop_reserv(mrp, port, info, drop);
	return true;
}

static void mrp_change_rx_reserv(struct mrp_info *mrp, u8 port,
	struct mrp_port_info *info,
	struct SRP_reserv *reserv)
{
	struct SRP_reserv *t_reserv;
	int n;
	u8 code;

	if (SRP_TALKER != reserv->direction || reserv->rx_code)
		return;

	code = reserv->code;

	/* check if these bits are still there */
	reserv->code_bits &= ~(
		RFC_ASCAPABLE_BIT |
		RFC_SRP_BOUNDARY_BIT |
		RFC_PRIORITY_BIT);
	reserv->code_bits |= mrp_chk_as_port(mrp, port, info,
		get_traffic_class(mrp, reserv->stream->priority));
	reserv->code = msrp_failure_code(reserv->code_bits);
	if (code == reserv->code)
		return;
dbg_msg(" c: %d=%d %d"NL, port, code, reserv->code);
	for (n = 0; n <= mrp->ports; n++) {
		if (n == port)
			continue;
		if (!(reserv->tx_ports & (1 << n)))
			continue;
		info = mrp_get_port_info(mrp, n);
		if (!info->status.msrpPortEnabledStatus)
			continue;
		t_reserv = info->declared.next;
		while (t_reserv) {
			if (mrp_match_tx_reserv(mrp, n, info, reserv,
					     t_reserv))
				break;
			t_reserv = t_reserv->next;
		}
	}
}  /* mrp_change_rx_reserv */

static void mrp_fwd_addr(struct mrp_info *mrp, uint port, bool avb)
{
	struct mrp_node *prev;
	struct mrp_node *next;
	struct mrp_mac_info *mac;

	prev = &mrp->mac_list.anchor;
	next = prev->next;
	while (next) {
		mac = next->data;
		if ((mac->rx_ports & (1 << port))) {
			u16 ports;

			if (avb)
				ports = mac->ports;
			else
				ports = SRP_PORT_OTHER;
			mrp_cfg_dest_addr(mrp, mac->index, mac->addr, ports,
					  mac->fid);
		}
		prev = next;
		next = prev->next;
	}
}  /* mrp_fwd_addr */

static int proc_mrp_chk_talker(struct mrp_info *mrp, u8 port, int tc)
{
	struct mrp_port_info *info;
	struct SRP_reserv *reserv;
	int avb_a;
	int avb_b;
	int result = DEV_IOC_OK;
	bool drop[8];
	struct ksz_port_cfg *cfg;
	struct ksz_sw *sw = mrp->parent;

	cfg = get_port_cfg(sw, port);
	avb_a = cfg->avb_a;
	avb_b = cfg->avb_b;
	info = mrp_get_port_info(mrp, port);
	if (!tc) {
		mrp_chk_as_port(mrp, port, info, SR_CLASS_A);
		tc = SR_CLASS_B;
	}
	mrp_chk_as_port(mrp, port, info, tc);
	if (avb_b != cfg->avb_b) {
#if 0
		if (port < mrp->ports)
#endif
			enable_acl_remap(mrp, port, !cfg->avb_b, cfg->avb_b);
		mrp_fwd_addr(mrp, port, cfg->avb_b);
	} else if (!avb_b && avb_a != cfg->avb_a) {
#if 0
		if (port < mrp->ports)
#endif
			enable_acl_remap(mrp, port, !cfg->avb_a, cfg->avb_a);
		mrp_fwd_addr(mrp, port, cfg->avb_a);
	}
	reserv = info->registered.next;
	while (reserv) {
		mrp_change_rx_reserv(mrp, port, info, reserv);
		reserv = reserv->next;
	}
	drop[SR_CLASS_A] = 0;
	drop[SR_CLASS_B] = 0;
	reserv = info->declared.next;
	while (reserv) {
		mrp_change_tx_reserv(mrp, port, info, reserv, drop);
		reserv = reserv->next;
	}
	mrp_drop_reserv(mrp, port, info, drop);

	if (mrp->report_head)
		result = DEV_IOC_MRP_REPORT;
	return result;
}  /* proc_mrp_chk_talker */

static int is_host_port(struct mrp_info *mrp, u8 port)
{
	struct ksz_sw *sw = mrp->parent;

	return (port == sw->HOST_PORT);
}  /* is_host_port */

static int proc_mrp_lv_domain(struct mrp_info *mrp, u8 port,
	struct SRP_domain_class *domain)
{
	int result = DEV_IOC_OK;
	struct mrp_port_info *info;
	struct SRP_domain_class *self = NULL;

dbg_msg(" %s %d=%d %d %d"NL, __func__, port,
	domain->id, domain->priority, domain->vlan_id);
	if (is_host_port(mrp, port))
		return result;
	info = mrp_get_port_info(mrp, port);
	if (SR_CLASS_B <= domain->id && domain->id <= SR_CLASS_A)
		self = &mrp->domain[domain->id - SR_CLASS_B];
	if (self && (self->id == domain->id &&
	    self->priority == domain->priority)) {
		if (!info->priority[domain->id].SRPdomainBoundaryPort) {
			info->priority[domain->id].SRPdomainBoundaryPort = 1;
			result = proc_mrp_chk_talker(mrp, port, domain->id);
		}
	}

	return result;
}  /* proc_mrp_lv_domain */

static int proc_mrp_rx_domain(struct mrp_info *mrp, u8 port,
	struct SRP_domain_class *domain)
{
	int result = DEV_IOC_OK;
	struct mrp_port_info *info;
	struct SRP_domain_class *self = NULL;

dbg_msg(" %s %d=%d %d %d"NL, __func__, port,
	domain->id, domain->priority, domain->vlan_id);
	if (is_host_port(mrp, port))
		return result;
	if (domain->id >= SR_CLASS_NUM)
		return result;
	info = mrp_get_port_info(mrp, port);
	if (SR_CLASS_B <= domain->id && domain->id <= SR_CLASS_A)
		self = &mrp->domain[domain->id - SR_CLASS_B];
	if (self && (self->id == domain->id &&
	    self->priority == domain->priority)) {
		if (info->priority[domain->id].SRPdomainBoundaryPort) {
			info->priority[domain->id].SRPdomainBoundaryPort = 0;
			result = proc_mrp_chk_talker(mrp, port, domain->id);
		}
	} else if (!info->priority[domain->id].SRPdomainBoundaryPort) {
		info->priority[domain->id].SRPdomainBoundaryPort = 1;
		if (self)
			result = proc_mrp_chk_talker(mrp, port, domain->id);
	}

	return result;
}  /* proc_mrp_rx_domain */

static int proc_mrp_chk_registered(struct mrp_info *mrp, u8 port)
{
	struct SRP_reserv *reserv;
	struct mrp_port_info *info;
	int i;
	int result = DEV_IOC_OK;

dbg_msg("%s %d"NL, __func__, port);
	for (i = 0; i <= mrp->ports; i++) {
		if (i == port)
			continue;
		info = mrp_get_port_info(mrp, i);
		reserv = info->registered.next;
		while (reserv) {
if (SRP_TALKER == reserv->direction)
dbg_msg(" t:%d %x"NL, info->index, reserv->tx_ports);
			if (SRP_TALKER == reserv->direction &&
			    !(reserv->tx_ports & (1 << port))) {
				struct SRP_talker talker;
				struct SRP_reserv *l_reserv;
				int result;

dbg_msg(" need talker decl: %d"NL, i);
				memcpy(&talker, reserv->stream, 25);
dbg_msg(" latency: %u %u"NL, talker.AccumulatedLatency, reserv->stream->latency);
				memcpy(talker.bridge_id, reserv->bridge_id, 8);
				talker.FailureCode = reserv->code;
				result = proc_mrp_tx_talker(mrp, port, &talker,
							    reserv, true);
				if (result < 0)
					continue;
				l_reserv = srp_find_reserv(&info->declared,
							   reserv->stream->id,
							   SRP_LISTENER);
				if (l_reserv)
					mrp_update_listener(mrp,
							    l_reserv,
							    reserv->stream,
							    false);
				chk_reserv(info, i);
			}
			reserv = reserv->next;
		}
	}
	if (mrp->report_head)
		result = DEV_IOC_MRP_REPORT;
	return result;
}  /* proc_mrp_chk_registered */
#endif

#ifdef CONFIG_KSZ_MRP
static int proc_mrp_get_tx(struct mrp_info *mrp, struct mrp_cfg_options *cmd,
			   int *output)
{
	struct mrp_report *attrib;

#ifdef CONFIG_KSZ_MSRP
	struct SRP_reserv *reserv;
	struct SRP_stream *stream;
#endif
	struct ksz_sw *sw = mrp->parent;
	int result = DEV_IOC_MRP_REPORT;

	attrib = mrp->report_head;
	if (!attrib)
		return DEV_IOC_INVALID_CMD;

	*output = 0;
	cmd->action = attrib->action;
	cmd->type = attrib->type;
	cmd->port = get_log_port(sw, attrib->port);
dbg_msg(" %s %d %d"NL, __func__, attrib->port, cmd->port);
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

		*domain = mrp->domain[0];
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
dbg_msg(" r %s %p"NL, __func__, reserv);
#endif
			kfree(reserv);

			/* Special one to free the stream. */
			if (next && next->port == sw->port_cnt) {
				reserv = next->attrib;
#ifdef DEBUG_MRP_MEM
dbg_msg(" s %s %p"NL, __func__, reserv->stream);
dbg_msg(" r2 %s %p"NL, __func__, reserv);
#endif
				kfree(reserv->stream);
				kfree(reserv);

#ifdef DEBUG_MRP_MEM
dbg_msg(" 1 %s %p"NL, __func__, attrib);
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
dbg_msg(" %s %p"NL, __func__, attrib);
#endif
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
#endif

#ifdef CONFIG_KSZ_AVB
static int mrp_set_bandwidth(struct mrp_port_info *info)
{
	int q0;
	int q1;
	int tc;
	u32 bandwidth;
	struct mrp_traffic_info *traffic;
	int check = false;

	q0 = info->traffic[0].queue;
	q1 = info->traffic[1].queue;
	bandwidth = calculate_max_bandwidth(info->speed,
		info->bandwidth[q1].deltaBandwidth +
		info->bandwidth[q0].deltaBandwidth);

	/* The link speed has changed. */
	if (bandwidth != info->bandwidth_max) {
		info->bandwidth_max = bandwidth;

		/* Total bandwidth left will be set again if being used. */
		if (info->bandwidth_used < info->bandwidth_max)
			info->bandwidth_left = info->bandwidth_max -
				info->bandwidth_used;
		else
			info->bandwidth_left = 0;
	}

	for (tc = SR_CLASS_A; tc >= SR_CLASS_B; tc--) {
		traffic = get_traffic_info(info, tc);
		bandwidth = calculate_max_bandwidth(info->speed,
			info->bandwidth[traffic->queue].deltaBandwidth);
		traffic->bandwidth_delta = bandwidth;
		traffic->bandwidth_max = bandwidth;
	}
	for (tc = SR_CLASS_A; tc >= SR_CLASS_B; tc--) {
		traffic = get_traffic_info(info, tc);
		if (traffic->bandwidth_used < traffic->bandwidth_max)
			traffic->bandwidth_left = traffic->bandwidth_max -
				traffic->bandwidth_used;
		else
			/* Bandwidth left will be set after checking. */
			traffic->bandwidth_left = 0;
		if (traffic->bandwidth_other)
			*traffic->bandwidth_other += traffic->bandwidth_left;
		if (traffic->bandwidth_used)
			check = true;
#ifdef CONFIG_KSZ_MSRP
		if (info->declared.next)
			check = true;
#endif
	}
if (check)
dbg_msg("%s %d"NL, __func__, check);
	return check;
}  /* mrp_set_bandwidth */

#ifdef CONFIG_KSZ_MRP
static void mrp_event(struct mrp_info *mrp, uint p, enum mrp_event event);
#endif

static int proc_mrp_set_speed(struct mrp_info *mrp, u8 port, u32 speed,
			      bool duplex)
{
	struct mrp_port_info *info;
	int link;
	int result = DEV_IOC_OK;

	if (speed != 1000 && speed != 100 && speed != 10 && speed != 0)
		return DEV_IOC_INVALID_CMD;
	info = mrp_get_port_info(mrp, port);
	if (speed) {
		if (speed >= 100 && duplex)
			info->duplex = 1;
		else
			info->duplex = 0;
	}
	if (speed && speed != info->speed) {
		info->speed = speed;
		if (mrp_set_bandwidth(info)) {
#ifdef CONFIG_KSZ_MSRP
			result = update_reserv(mrp, port, info);
#endif
		}
	}
	link = info->link;
	info->link = speed != 0;
if (port < 4)
dbg_msg("%s %d=%d:%d %d %d"NL, __func__, port, speed, duplex, info->link, link);
#ifdef CONFIG_KSZ_MSRP
	if (link != info->link && info->link && mrp->started) {
		int rc;

		rc = proc_mrp_chk_registered(mrp, port);
		if (result == DEV_IOC_OK)
			result = rc;
#ifdef CONFIG_KSZ_MRP
		mrp_event(mrp, port, MRP_EVENT_REDECLARE);
#endif
	}
#if 0
	if (link != info->link && !info->link && mrp->started) {
		mrp_event(mrp, port, MRP_EVENT_FLUSH);
	}
#endif
#endif
	return result;
}  /* proc_mrp_set_speed */

static int proc_mrp_set_delta(struct mrp_info *mrp, u8 port, u32 A, u32 B)
{
	struct mrp_port_info *info;
	int q1;
	int q2;
	int result = DEV_IOC_OK;

dbg_msg("%s %d=%d %d"NL, __func__, port, A, B);
	if (A + B > 95)
		return DEV_IOC_INVALID_CMD;
	info = mrp_get_port_info(mrp, port);
	q1 = get_queue_priority(mrp, SR_CLASS_A);
	q2 = get_queue_priority(mrp, SR_CLASS_B);
	info->bandwidth[q1].deltaBandwidth = A;
	info->bandwidth[q2].deltaBandwidth = B;
	if (mrp_set_bandwidth(info)) {
	char bw_str1[20];
	char bw_str2[20];
	char bw_str3[20];
	char bw_str4[20];
	char bw_str5[20];
		format_num(bw_str1, info->bandwidth_used);
		format_num(bw_str2, info->traffic[1].bandwidth_max);
		format_num(bw_str3, info->traffic[1].bandwidth_used);
		format_num(bw_str4, info->traffic[0].bandwidth_max);
		format_num(bw_str5, info->traffic[0].bandwidth_used);
dbg_msg("bw used: %d %s; %s %s; %s %s"NL, port,
bw_str1, bw_str2, bw_str3, bw_str4, bw_str5);
#ifdef CONFIG_KSZ_MSRP
		result = update_reserv(mrp, port, info);
#endif
	}
	return result;
}  /* proc_mrp_set_delta */
#endif

#ifdef CONFIG_KSZ_MRP
static int proc_mrp_xmit(struct mrp_info *mrp, uint p, struct sk_buff *skb);

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

static void proc_mrp_req_lv(struct mrp_info *mrp, uint port,
			    struct mrp_application *appl)
{
	struct mrp_port *p;
	struct mrp_applicant *app;

	p = &mrp->mrp_ports[port];
	app = rcu_dereference(p->applicants[appl->type]);

	mrp_join_timer_exec(app);
}  /* proc_mrp_req_lv */

static int proc_mrp_join_mac(struct mrp_info *mrp, uint port,
	struct MRP_mac *mac, u8 new_decl)
{
	struct mrp_port *p;
	struct mrp_applicant *app;

	p = &mrp->mrp_ports[port];
	app = rcu_dereference(p->applicants[mac_mrp_app.type]);

	mmrp_req_join_mac(app, mac->addr, new_decl);
	return 0;
}  /* proc_mrp_join_mac */

static int proc_leave_mac(struct mrp_info *mrp, uint port,
	struct MRP_mac *mac)
{
	struct mrp_port *p;
	struct mrp_applicant *app;

	p = &mrp->mrp_ports[port];
	app = rcu_dereference(p->applicants[mac_mrp_app.type]);

	return mmrp_req_leave_mac(app, mac->addr);
}  /* proc_leave_mac */

static int proc_mrp_join_vlan(struct mrp_info *mrp, uint port,
	struct MRP_vlan *vlan, u8 new_decl)
{
	struct mrp_port *p;
	struct mrp_applicant *app;

	p = &mrp->mrp_ports[port];
	app = rcu_dereference(p->applicants[vlan_mrp_app.type]);

	mvrp_req_join(app, vlan->id, new_decl);
	return 0;
}  /* proc_mrp_join_vlan */

static int proc_leave_vlan(struct mrp_info *mrp, uint port,
	struct MRP_vlan *vlan)
{
	struct mrp_port *p;
	struct mrp_applicant *app;

	p = &mrp->mrp_ports[port];
	app = rcu_dereference(p->applicants[vlan_mrp_app.type]);

	return mvrp_req_leave(app, vlan->id);
}  /* proc_leave_vlan */

#ifdef CONFIG_KSZ_MSRP
static int proc_mrp_new_talker(struct mrp_info *mrp, uint port,
	struct SRP_talker *talker, u8 new_decl)
{
	struct srp_talker_failed attr;
	struct mrp_port *p;
	struct mrp_applicant *app;

	p = &mrp->mrp_ports[port];
	app = rcu_dereference(p->applicants[srp_mrp_app.type]);

	/* MSRP may be disabled in this port. */
	if (!app)
		return 0;

	mrp_set_talker(talker, &attr);
	msrp_req_new_talker(app, &attr, new_decl);
	return 0;
}  /* proc_mrp_new_talker */

static int proc_leave_talker(struct mrp_info *mrp, uint port,
	struct SRP_talker *talker)
{
	struct srp_talker_failed attr;
	struct mrp_port *p;
	struct mrp_applicant *app;

	p = &mrp->mrp_ports[port];
	app = rcu_dereference(p->applicants[srp_mrp_app.type]);

	mrp_set_talker(talker, &attr);
	return msrp_req_leave_talker(app, &attr);
}  /* proc_leave_talker */

static int proc_mrp_new_listener(struct mrp_info *mrp, uint port,
	struct SRP_listener *listener, u8 new_decl)
{
	struct srp_listener attr;
	struct mrp_port *p;
	struct mrp_applicant *app;

	p = &mrp->mrp_ports[port];
	app = rcu_dereference(p->applicants[srp_mrp_app.type]);

	/* MSRP may be disabled in this port. */
	if (!app)
		return 0;

	mrp_set_listener(listener, &attr);
	msrp_req_new_listener(app, &attr, new_decl);
	return 0;
}  /* proc_mrp_new_listener */

static int proc_leave_listener(struct mrp_info *mrp, uint port,
	struct SRP_listener *listener)
{
	struct srp_listener attr;
	struct mrp_port *p;
	struct mrp_applicant *app;

	p = &mrp->mrp_ports[port];
	app = rcu_dereference(p->applicants[srp_mrp_app.type]);

	mrp_set_listener(listener, &attr);
	return msrp_req_leave_listener(app, &attr);
}  /* proc_leave_listener */

static int proc_mrp_join_domain(struct mrp_info *mrp, uint port,
	struct SRP_domain_class *domain, u8 new_decl)
{
	struct srp_domain attr;
	struct mrp_port *p;
	struct mrp_applicant *app;

	p = &mrp->mrp_ports[port];
	app = rcu_dereference(p->applicants[srp_mrp_app.type]);

	/* MSRP may be disabled in this port. */
	if (!app)
		return 0;

	mrp_set_domain(domain, &attr);
	msrp_req_join_domain(app, &attr, new_decl);
	return 0;
}  /* proc_mrp_join_domain */

static int proc_leave_domain(struct mrp_info *mrp, uint port,
	struct SRP_domain_class *domain)
{
	struct srp_domain attr;
	struct mrp_port *p;
	struct mrp_applicant *app;

	p = &mrp->mrp_ports[port];
	app = rcu_dereference(p->applicants[srp_mrp_app.type]);

	mrp_set_domain(domain, &attr);
	return msrp_req_leave_domain(app, &attr);
}  /* proc_leave_domain */
#endif
#endif

static int proc_mrp_set_attribute(struct mrp_info *mrp, u8 *data)
{
	struct mrp_cfg_options *cmd = (struct mrp_cfg_options *) data;
	struct ksz_sw *sw = mrp->parent;
	int result = DEV_IOC_OK;
#ifdef CONFIG_KSZ_MRP
	int tx_leave = false;
#endif
	uint n = cmd->port;
	uint p;

	p = get_phy_port(sw, n);
	switch (cmd->type) {
#ifdef CONFIG_KSZ_MRP
	case MRP_TYPE_MAC:
		if (MRP_ACTION_RX == cmd->action)
			result = proc_mrp_rx_mac(mrp, p, &cmd->data.mac,
				cmd->new_decl);
		else if (MRP_ACTION_LV == cmd->action)
			result = proc_mrp_lv_mac(mrp, p, &cmd->data.mac);
		else if (MRP_ACTION_DECL == cmd->action)
			result = proc_mrp_join_mac(mrp, p, &cmd->data.mac,
				cmd->new_decl);
		else if (MRP_ACTION_DROP == cmd->action)
			tx_leave = proc_leave_mac(mrp, p, &cmd->data.mac);
		else if (MRP_ACTION_ON == cmd->action) {
			mrp->no_report = 1;
			result = proc_mrp_rx_mac(mrp, p, &cmd->data.mac,
				cmd->new_decl);
			mrp->no_report = 0;
		} else if (MRP_ACTION_OFF == cmd->action) {
			mrp->no_report = 1;
			result = proc_mrp_lv_mac(mrp, p, &cmd->data.mac);
			mrp->no_report = 0;
		} else
			mrp_show_node(&mrp->mac_list, show_mac_info);
		if (tx_leave)
			proc_mrp_req_lv(mrp, p, &mac_mrp_app);
		break;
	case MRP_TYPE_VLAN:
		if (MRP_ACTION_RX == cmd->action)
			result = proc_mrp_rx_vlan(mrp, p, &cmd->data.vlan,
				cmd->new_decl);
		else if (MRP_ACTION_LV == cmd->action)
			result = proc_mrp_lv_vlan(mrp, p, &cmd->data.vlan);
		else if (MRP_ACTION_DECL == cmd->action)
			result = proc_mrp_join_vlan(mrp, p,
				&cmd->data.vlan, cmd->new_decl);
		else if (MRP_ACTION_DROP == cmd->action)
			tx_leave = proc_leave_vlan(mrp, p, &cmd->data.vlan);
		else if (MRP_ACTION_ON == cmd->action) {
			mrp->no_report = 1;
			result = proc_mrp_rx_vlan(mrp, p, &cmd->data.vlan,
				cmd->new_decl);
			mrp->no_report = 0;
		} else if (MRP_ACTION_OFF == cmd->action) {
			mrp->no_report = 1;
			result = proc_mrp_lv_vlan(mrp, p, &cmd->data.vlan);
			mrp->no_report = 0;
		} else
			mrp_show_node(&mrp->vlan_list, show_vlan_info);
		if (tx_leave)
			proc_mrp_req_lv(mrp, p, &vlan_mrp_app);
		break;

#ifdef CONFIG_KSZ_MSRP
	case MRP_TYPE_DOMAIN:
		if (MRP_ACTION_RX == cmd->action)
			result = proc_mrp_rx_domain(mrp, p,
				&cmd->data.domain);
		else if (MRP_ACTION_LV == cmd->action)
			result = proc_mrp_lv_domain(mrp, p,
				&cmd->data.domain);
		else if (MRP_ACTION_DECL == cmd->action)
			result = proc_mrp_join_domain(mrp, p,
				&cmd->data.domain, cmd->new_decl);
		else if (MRP_ACTION_DROP == cmd->action)
			tx_leave = proc_leave_domain(mrp, p, &cmd->data.domain);
		else if (MRP_ACTION_ON == cmd->action) {
			mrp->no_report = 1;
			result = proc_mrp_rx_domain(mrp, p,
				&cmd->data.domain);
			mrp->no_report = 0;
		} else if (MRP_ACTION_OFF == cmd->action) {
			mrp->no_report = 1;
			result = proc_mrp_lv_domain(mrp, p,
				&cmd->data.domain);
			mrp->no_report = 0;
		}
		if (tx_leave)
			proc_mrp_req_lv(mrp, p, &srp_mrp_app);
		break;
	case MRP_TYPE_LISTENER:
		if (MRP_ACTION_RX == cmd->action)
			result = proc_mrp_rx_listener(mrp, p,
				&cmd->data.listener, cmd->new_decl);
		else if (MRP_ACTION_LV == cmd->action)
			result = proc_mrp_lv_listener(mrp, p,
				&cmd->data.listener);
		else if (MRP_ACTION_DECL == cmd->action)
			result = proc_mrp_new_listener(mrp, p,
				&cmd->data.listener, cmd->new_decl);
		else if (MRP_ACTION_DROP == cmd->action)
			tx_leave = proc_leave_listener(mrp, p,
				&cmd->data.listener);
		else if (MRP_ACTION_ON == cmd->action) {
			mrp->no_report = 1;
			result = proc_mrp_rx_listener(mrp, p,
				&cmd->data.listener, cmd->new_decl);
			mrp->no_report = 0;
		} else if (MRP_ACTION_OFF == cmd->action) {
			mrp->no_report = 1;
			result = proc_mrp_lv_listener(mrp, p,
				&cmd->data.listener);
			mrp->no_report = 0;
		}
		if (tx_leave)
			proc_mrp_req_lv(mrp, p, &srp_mrp_app);
		break;
	case MRP_TYPE_TALKER:
		if (MRP_ACTION_RX == cmd->action)
			result = proc_mrp_rx_talker(mrp, p,
				&cmd->data.talker, cmd->new_decl);
		else if (MRP_ACTION_LV == cmd->action)
			result = proc_mrp_lv_talker(mrp, p,
				&cmd->data.talker);
		else if (MRP_ACTION_DECL == cmd->action)
			result = proc_mrp_new_talker(mrp, p,
				&cmd->data.talker, cmd->new_decl);
		else if (MRP_ACTION_DROP == cmd->action)
			tx_leave = proc_leave_talker(mrp, p, &cmd->data.talker);
		else if (MRP_ACTION_ON == cmd->action) {
			mrp->no_report = 1;
			result = proc_mrp_rx_talker(mrp, p,
				&cmd->data.talker, cmd->new_decl);
			mrp->no_report = 0;
		} else if (MRP_ACTION_OFF == cmd->action) {
			mrp->no_report = 1;
			result = proc_mrp_lv_talker(mrp, p,
				&cmd->data.talker);
			mrp->no_report = 0;
		} else {
			int n;
			struct mrp_port_info *info;

			for (n = 0; n <= mrp->ports; n++) {
				info = mrp_get_port_info(mrp, n);
				if (!info->status.msrpPortEnabledStatus)
					continue;
				chk_reserv(info, n);
			}
		}
		if (tx_leave)
			proc_mrp_req_lv(mrp, p, &srp_mrp_app);
		break;
#endif
#endif
	case MRP_TYPE_PORT:

#ifdef CONFIG_KSZ_AVB
		if (MRP_ACTION_SPEED == cmd->action) {
			int speed = cmd->data.data[0];
			bool duplex = cmd->data.data[1];

			result = proc_mrp_set_speed(mrp, p, speed, duplex);
		} else if (MRP_ACTION_DELTA == cmd->action) {
			u32 a = cmd->data.data[0];
			u32 b = cmd->data.data[1];

			result = proc_mrp_set_delta(mrp, p, a, b);
		}
#endif
#ifdef CONFIG_KSZ_MSRP
		if (MRP_ACTION_CHK_TALKER == cmd->action) {
			result = proc_mrp_chk_talker(mrp, p, 0);
		} else if (MRP_ACTION_CHK_REG == cmd->action) {
			result = proc_mrp_chk_registered(mrp, p);
		}
#endif
		break;
	}
	return result;
}  /* proc_mrp_set_attribute */

#ifdef CONFIG_KSZ_MSRP
static void mrp_cfg_mcast_addr(struct mrp_info *mrp, u16 fid, u8 *dest,
			       u16 ports)
{
	struct mrp_node *mac_node;
	struct ksz_sw *sw = mrp->parent;

	sw->ops->cfg_mac(sw, 1, dest, ports, true, fid != 0, fid);
	mac_node = mrp_get_mac_info(&mrp->mac_list, dest, fid);
	if (mac_node) {
		struct mrp_mac_info *mac;

		mac = mac_node->data;

		/* Indicate address is programmed in the lookup table. */
		mac->srp_ports |= SRP_PORT_SET;
	}
}  /* mrp_cfg_mcast_addr */

static void mrp_cfg_mac_work(struct work_struct *work)
{
	u16 *fid;
	u16 *ports;
	u8 addr[ETH_ALEN];
	bool last;
	struct sk_buff *skb;
	struct mrp_info *mrp = container_of(work, struct mrp_info, cfg_mac);

	last = skb_queue_empty(&mrp->macq);
	while (!last) {
		skb = skb_dequeue(&mrp->macq);
		last = skb_queue_empty(&mrp->macq);
		if (!skb)
			continue;
		memcpy(addr, skb->data, ETH_ALEN);
		fid = (u16 *)&skb->data[ETH_ALEN];
		ports = (u16 *)&skb->data[ETH_ALEN + 2];
		mrp_cfg_mcast_addr(mrp, *fid, addr, *ports);
		kfree_skb(skb);
	}
	mrp->macq_sched = 0;
}  /* mrp_cfg_mac_work */

static int mrp_req_cfg_mac(struct mrp_info *mrp, u8 *addr, u16 fid, u16 ports)
{
	struct sk_buff *skb;
	u16 *data;

	skb = alloc_skb(64, GFP_ATOMIC);
	if (!skb)
		return -ENOMEM;

	memcpy(skb->data, addr, ETH_ALEN);
	data = (u16 *)&skb->data[ETH_ALEN];
	*data = fid;
	data++;
	*data = ports;
	skb_queue_tail(&mrp->macq, skb);
	if (!mrp->macq_sched) {
		mrp->macq_sched = 1;
		schedule_work(&mrp->cfg_mac);
	}
	return 0;
}  /* mrp_req_cfg_mac */
#endif

#ifdef CONFIG_KSZ_MRP
static void mrp_rx_proc(struct work_struct *work)
{
	bool last;
	struct sk_buff *skb;
	struct mrp_applicant **data;
	struct mrp_applicant *app;
	struct mrp_info *mrp = container_of(work, struct mrp_info, rx_proc);

	last = skb_queue_empty(&mrp->rxq);
	while (!last) {
		skb = skb_dequeue(&mrp->rxq);
		last = skb_queue_empty(&mrp->rxq);
		if (!skb)
			continue;
		data = (struct mrp_applicant **)skb->cb;
		app = *data;
		app->rxpdu(app, &skb->data[sizeof(struct ethhdr)],
			skb->len - sizeof(struct ethhdr));
		app->cleanup(app);
		kfree_skb(skb);
	}
}  /* mrp_rx_proc */

static int proc_mrp_xmit(struct mrp_info *mrp, uint p, struct sk_buff *skb)
{
	int rc;
	u16 tx_ports;
	u32 ports;
	struct ksz_sw *sw = mrp->parent;
	const struct net_device_ops *ops = sw->main_dev->netdev_ops;
	int result = DEV_IOC_OK;

	/* Send to host port by simulating receiving. */
	if (p == sw->HOST_PORT) {
		skb->data[11] ^= 0x01;
		skb->protocol = eth_type_trans(skb, skb->dev);
		netif_rx_ni(skb);
		return 0;
	}

	/* Do not send if network device is not ready. */
	if (!netif_running(sw->main_dev)) {
		kfree_skb(skb);
		return 0;
	}

	tx_ports = sw->tx_ports[0] & mrp->tx_ports;
#if 1
if (!(tx_ports & (1 << p)) && sw->tx_ports[0] != mrp->tx_ports) {
dbg_msg("  tx close: %d %x %x"NL, p, sw->tx_ports[0], mrp->tx_ports);
}
#endif

	/* Do not send to port if its link is lost. */
	if (media_disconnected == sw->port_state[p].state ||
	    !(tx_ports & (1 << p))) {
		kfree_skb(skb);
		return 0;
	}

	if (skb->len < 60) {
		int len = 60 - skb->len;
		memset(&skb->data[skb->len], 0, len);
		skb_put(skb, len);
	}
	ports = 1 << p;
	ports |= TAIL_TAG_SET_QUEUE;
	sw->net_ops->add_tail_tag(sw, skb, ports);
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
#ifdef CONFIG_KSZ_MRP
	u8 *data = parent->param.data;
#endif
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
#ifdef CONFIG_KSZ_MRP
			result = proc_mrp_set_attribute(mrp, data);
#endif
			break;
		default:
			result = DEV_IOC_INVALID_CMD;
			break;
		}
		break;
	case DEV_CMD_GET:
		switch (parent->subcmd) {
		case DEV_MRP_ATTRIBUTE:
#ifdef CONFIG_KSZ_MRP
			result = proc_mrp_get_attribute(mrp, data,
							&parent->output);
#endif
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
		pr_alert("work full"NL);
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

#ifdef CONFIG_KSZ_MSRP
static void mrp_proc_proto(struct mrp_info *mrp, u8 *addr, u16 port)
{
#if 0
	struct maap_pdu *maap;
	u16 data;

	maap = (struct maap_pdu *)&addr[14];
	if (maap->subtype == AVTP_SUBTYPE_MAAP) {
		data = ntohs(maap->len.data);
dbg_msg(" maap: %u=m:%x v:%d %u %u l:%u"NL
"%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x %02x:%02x:%02x:%02x:%02x:%02x %u"NL,
		port,
		maap->message_type, maap->version, maap->sv,
		data >> 11, data & 0x7f,
		maap->stream_id[0], maap->stream_id[1],
		maap->stream_id[2], maap->stream_id[3],
		maap->stream_id[4], maap->stream_id[5],
		maap->stream_id[6], maap->stream_id[7],
		maap->req_start_addr[0],
		maap->req_start_addr[1],
		maap->req_start_addr[2],
		maap->req_start_addr[3],
		maap->req_start_addr[4],
		maap->req_start_addr[5],
		ntohs(maap->req_cnt));
	} else if (maap->subtype == AVTP_SUBTYPE_ADP) {
#if 0
dbg_msg(" adp: %u="NL, port);
#endif
	}
#endif
}  /* mrp_proc_proto */

static int mrp_chk_mcast(struct mrp_info *mrp, u8 *addr, u16 vid, u16 prio,
			 u16 proto, uint port)
{
	struct mrp_node *mac_node;
	struct mrp_mac_info *mac;
	struct ksz_port_cfg *cfg;
	struct maap_pdu *maap;
#if 0
	struct sk_buff *skb;
	u16 *data;
#endif
	u16 ports;
	u16 fid = 0;
	struct vlan_ethhdr *vlan = (struct vlan_ethhdr *) addr;
	struct ksz_sw *sw = mrp->parent;
	int avb_a;
	int avb_b;
	int avb_0 = 0;
	int *avb = &avb_0;
	int ignore;
	int result;

	cfg = &sw->info->port_cfg[port];
	avb_a = cfg->avb_a;
	avb_b = cfg->avb_b;

	maap = (struct maap_pdu *)&addr[14];
	if (proto == 0x22F0) {
		if (maap->subtype == AVTP_SUBTYPE_MAAP) {
			if (memcmp(vlan->h_dest, maap_addr[0], ETH_ALEN))
dbg_msg("  %02x:%02x:%02x:%02x:%02x:%02x  ",
	vlan->h_dest[0], vlan->h_dest[1], vlan->h_dest[2],
	vlan->h_dest[3], vlan->h_dest[4], vlan->h_dest[5]);
dbg_msg(" maap: %d"NL, maap->message_type);
		}
		if (maap->subtype == AVTP_SUBTYPE_MAAP ||
		    !memcmp(vlan->h_dest, maap_addr[0], ETH_ALEN))
			return 1;
	}

	if (vlan->h_vlan_proto == htons(ETH_P_8021Q))
		maap = (struct maap_pdu *)(vlan + 1);

	/* Priority is already remapped to 0 if port is not AVB. */

	/* SR Class A supported */
	if (prio == mrp->prio[SR_CLASS_A] && mrp->domain[1].id)
		avb = &avb_a;
	if (prio == mrp->prio[SR_CLASS_B])
		avb = &avb_b;

#if 0
	/* XMOS sends this MAAP periodically. */
	if (vlan->h_vlan_proto != htons(ETH_P_8021Q)) {
		if (!(0x01 <= addr[15] && addr[15] <= 0x03))
dbg_msg(" MAAP? %02X:%02X:%02X:%02X:%02X:%02X %02x"NL,
addr[0], addr[1], addr[2], addr[3], addr[4], addr[5], addr[15]);
		if (0x01 <= addr[15] && addr[15] <= 0x03)
			return 1;
	}
#endif
	if (vid > 1) {
#if 0
		ports = mrp_find_vlan_ports(&mrp->vlan_list, vid, NULL,
			&fid);
		if (!ports)
#endif
			fid = sw->info->vid2fid[vid];
	}

	/* Check if the multicast address is registered. */
	mac_node = mrp_get_mac_info(&mrp->mac_list, addr, fid);
	if (!mac_node)
		return -ENOMEM;

	mac = mac_node->data;
	ports = mac->srp_ports | mac->mrp_ports;

	/* Address is used by MRP and already programmed into lookup table. */
	if (ports & SRP_PORT_READY)
		return 2;

#if 1
	if (!mac->ticks) {
dbg_msg(" drop: %d=%d=%02X:%02X:%02X:%02X:%02X:%02X  %02X"NL, port, prio,
addr[0], addr[1], addr[2], addr[3], addr[4], addr[5], maap->subtype);
	}
#endif
	mac->ticks = jiffies + msecs_to_jiffies(10000);

	ignore = (ports & SRP_PORT_BLACKLIST) &&
		!(mac->rx_ports & SRP_PORT_IGNORE);

	/* Address is programmed into lookup table. */
	if (ports & SRP_PORT_SET)
		result = 0;
	else
		result = !*avb;
	mac->rx_ports &= ~SRP_PORT_IGNORE;

	/* Address is already seen before. */
	if (ignore)
		return result;

	mac->rx_ports |= (1 << port);
	mac->srp_ports |= SRP_PORT_BLACKLIST;
	if (!*avb)
		ports = sw->PORT_MASK & ~sw->HOST_MASK;
	else
		ports = 0;

	return mrp_req_cfg_mac(mrp, addr, fid, ports);
}  /* mrp_chk_mcast */
#endif

static int mrp_dev_req(struct mrp_info *mrp, char *arg)
{
	struct ksz_request *req = (struct ksz_request *) arg;
	int len;
	int maincmd;
	int req_size;
	int subcmd;
	int output;
	u8 data[PARAM_DATA_SIZE];
	u8 cmd_data[4];
	int err = 0;
	int result = 0;
	struct mrp_cfg_options *cmd = (struct mrp_cfg_options *) cmd_data;
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
		if (chk_ioctl_size(len, 4, SIZEOF_ksz_request, &req_size,
				&result, &req->param, cmd_data))
			goto dev_ioctl_resp;

		switch (cmd->type) {
		case MRP_TYPE_PORT:
			param_size = 4;
			if (maincmd == DEV_CMD_PUT)
				param_size += sizeof(u32) * 4;
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
					maincmd, subcmd, 0,
					data, 6, &output, NULL, true);
			} else
				result = DEV_IOC_INVALID_LEN;
			break;
		case DEV_INFO_EXIT:
			result = proc_mrp_hw_access(mrp,
				maincmd, subcmd, 0,
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
			result = proc_mrp_hw_access(mrp,
				maincmd, subcmd, 0,
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
				uint port;
				struct ksz_sw *sw = mrp->parent;

				port = get_phy_port(sw, cmd->port);
				__put_user(mrp->port_info[port].speed,
					&req->output);
				break;
			}
#endif
			result = proc_mrp_hw_access(mrp,
				maincmd, subcmd, 0,
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

#ifdef CONFIG_KSZ_MRP
static void mrp_change_attr(struct mrp_applicant *app, void *value, u8 len,
			    u8 type, enum mrp_event event)
{
	struct mrp_attr *attr;

	attr = mrp_attr_lookup(app, value, len, type);
	if (attr) {
		u8 action;

dbg_msg(" attr ");
		/* Check the attribute is being declared. */
		action = mrp_tx_action_table[attr->state];
		if (action != MRP_TX_ACTION_S_JOIN_IN &&
		    action != MRP_TX_ACTION_S_JOIN_IN_OPTIONAL)
			action = mrp_tx_la_action_table[attr->state];

		/* Change Join to New. */
		if (action == MRP_TX_ACTION_S_JOIN_IN ||
		    action == MRP_TX_ACTION_S_JOIN_IN_OPTIONAL)
{
dbg_msg(" event"NL);
			if (mrp_attr_event(app, attr, event))
				mrp_join_timer_arm(app);
}
	}
}

static void mrp_update_event(struct mrp_applicant *app,
			     struct mrp_applicant *to, enum mrp_event event)
{
	struct rb_node *node, *next;
	struct mrp_attr *attr;

	for (node = rb_first(&app->mad);
	     next = node ? rb_next(node) : NULL, node != NULL;
	     node = next) {
		attr = rb_entry(node, struct mrp_attr, node);

		if (attr->reg_state != MRP_REGISTRAR_IN)
			continue;
dbg_msg(" in %d:%02x%02x %d %d -> %d"NL, app->port,
attr->value[0], attr->value[1], attr->len, attr->type, to->port);
		mrp_change_attr(to, attr->value, attr->len, attr->type, event);
	}
}

static void mrp_event_port_app(struct mrp_port *port,
	struct mrp_application *appl, enum mrp_event event)
{
	struct mrp_applicant *app;

	app = rcu_dereference(port->applicants[appl->type]);
	mrp_mad_event(app, event);
	if (event == MRP_EVENT_LV && app->timer_arm.join)
		mrp_join_timer_exec(app);
}  /* mrp_event_port_app */

static void mrp_new_event_port_app(struct mrp_info *mrp, uint p,
				struct mrp_application *appl)
{
	struct mrp_applicant *app;
	struct mrp_applicant *to;
	int n;

	app = rcu_dereference(mrp->mrp_ports[p].applicants[appl->type]);
	for (n = 0; n <= mrp->ports; n++) {
		if (n == p)
			continue;
		to = rcu_dereference(mrp->mrp_ports[n].applicants[appl->type]);
		mrp_update_event(app, to, MRP_EVENT_NEW);
	}
}

static void mrp_event(struct mrp_info *mrp, uint p, enum mrp_event event)
{
	uint m = BIT(p);

	if (!(mrp->mask & m))
		return;
	if (mrp->mmrp_rx_ports & m) {
		mrp_event_port_app(&mrp->mrp_ports[p], &mac_mrp_app, event);
	}
	if (mrp->mvrp_rx_ports & m) {
		mrp_event_port_app(&mrp->mrp_ports[p], &vlan_mrp_app, event);
	}

#ifdef CONFIG_KSZ_MSRP
	if (mrp->status.msrpEnabledStatus &&
	    mrp->port_info[p].status.msrpPortEnabledStatus) {
		mrp_event_port_app(&mrp->mrp_ports[p], &srp_mrp_app, event);
	}
#endif
}  /* mrp_event */

static void mrp_setup_vlan(struct mrp_info *mrp, u16 vid,
			   struct ksz_vlan_table *vlan)
{
	struct mrp_node *node;
	struct mrp_vlan_info *info;
	struct mrp_vlan_info data;
	struct MRP_vlan mrp_vlan;
	int cnt;
	uint n;
	uint p;
	uint q;
	struct ksz_sw *sw = mrp->parent;

	if (!mrp->started)
		return;
	if (vid == 0 || vid == 1 || vid == 4095)
		return;
	cnt = 0;
	q = 0;
	if (vlan->valid) {
		for (n = 0; n <= sw->mib_port_cnt; n++) {
			p = get_phy_port(sw, n);
			if (vlan->ports & (1 << p)) {
				q = p;
				cnt++;
			}
		}
	}
	if (cnt) {
		int bit;
		int index;
		u16 ports;
		int new_decl = false;

#if 1
		node = mrp_get_vlan_info(&mrp->vlan_list, vid, NULL);
		if (!node)
			return;

		info = node->data;
		ports = info->ports;
		info->set_ports = vlan->ports;
		info->ports = info->set_ports;
#if 0
			ports = mrp_find_vlan_ports(&mrp->vlan_list, vid,
				&info->index, &info->fid);
#endif
		if (!ports) {
			info->index = mrp_alloc_vlan(mrp);
			info->fid = vlan->fid;
dbg_msg(" index: %d %d"NL, info->index, info->fid);
		}
#endif
		index = vid / VID_IN_DATA;
		bit = vid % VID_IN_DATA;
		if (!(sw->info->vid[index] & (1 << bit)))
			new_decl = true;
		if (cnt > 1)
			q = sw->port_cnt;
		mrp_vlan.id = vid;
dbg_msg(" q %d %x"NL, q, info->tx_ports);
		for (n = 0; n <= sw->mib_port_cnt; n++) {
			p = get_phy_port(sw, n);
			if (p == q) {
				if (info->tx_ports & BIT(p)) {
					info->tx_ports &= ~BIT(p);
					if (proc_leave_vlan(mrp, p, &mrp_vlan))
						proc_mrp_req_lv(mrp, p, &vlan_mrp_app);
				}
				continue;
			}
			if (!(info->tx_ports & BIT(p))) {
				proc_mrp_join_vlan(mrp, p, &mrp_vlan, new_decl);
				info->tx_ports |= BIT(p);
			}
		}
	} else {
		data.vid = vid;
		memset(data.addr, 0xff, ETH_ALEN);
		node = mrp_find_node(&mrp->vlan_list, cmp_vlan, &data);
		if (node) {
			u16 ports;

			info = node->data;
			info->set_ports = 0;
			info->ports = info->rx_ports;
#if 0
			ports = mrp_find_vlan_ports(&mrp->vlan_list, data.vid,
						    NULL, NULL);
#endif
			ports = info->ports;
			if (!ports) {
				mrp_free_fid(mrp, info->fid);
				mrp_free_vlan(mrp, info->index);
			}
dbg_msg(" delete: %x"NL, info->ports);

			/* Nobody is using the VLAN. */
			if (!info->ports)
				mrp_delete_node(&mrp->vlan_list, cmp_vlan,
						node);
		}
		mrp_vlan.id = vid;
		for (n = 0; n <= sw->mib_port_cnt; n++) {
			p = get_phy_port(sw, n);
			if (proc_leave_vlan(mrp, p, &mrp_vlan))
				proc_mrp_req_lv(mrp, p, &vlan_mrp_app);
		}
	}
}  /* mrp_setup_vlan */

static void proc_mrp_rcv(struct mrp_info *mrp, struct mrp_applicant *app,
			 struct sk_buff *skb)
{
	struct mrp_applicant **data = (struct mrp_applicant **)skb->cb;

	*data = app;
	skb_queue_tail(&mrp->rxq, skb);
	schedule_work(&mrp->rx_proc);
}  /* proc_mrp_rcv */

static int mrp_rcv(struct mrp_info *mrp, struct sk_buff *skb, uint p)
{
	int mac_oper;
	struct mrp_application *appl = NULL;
	struct ethhdr *eth = (struct ethhdr *) skb->data;
	struct ksz_sw *sw = mrp->parent;

	/* MAC_Operational. */
	mac_oper = (sw->dev_ports & (1 << p));

	if (eth->h_proto == htons(ETH_P_MVRP)) {
/* MVRP.c.11.2.3a allows registration with non-forwarding ports. */
#if 0
		mac_oper &= sw->rx_ports[0];
#endif
		appl = &vlan_mrp_app;
		if (!(mrp->mvrp_rx_ports & (1 << p)))
			mac_oper = false;
	} else if (eth->h_proto == htons(ETH_P_MMRP)) {
		mac_oper &= sw->rx_ports[0];
		appl = &mac_mrp_app;
		if (!(mrp->mmrp_rx_ports & (1 << p)))
			mac_oper = false;

#ifdef CONFIG_KSZ_MSRP
	} else if (eth->h_proto == htons(ETH_P_MSRP)) {
		mac_oper &= sw->rx_ports[0];
		appl = &srp_mrp_app;
		if (!mrp->status.msrpEnabledStatus ||
		    !mrp->port_info[p].status.msrpPortEnabledStatus)
			mac_oper = false;
#endif
	}
	if (appl) {
		struct mrp_port *port;
		struct mrp_applicant *app;
		struct ksz_port_info *info;
		uint n;
		uint q;

#ifdef DBG_MRP_

dbg_msg("  R:"NL);
		for (i = 0; i < skb->len; i++) {
			dbg_msg("%02x ", skb->data[i]);
			if ((i % 16) == 15)
				dbg_msg(NL);
		}
		if ((i % 16))
			dbg_msg(NL);
#endif

		/* Check for MRP message sent by self. */
		for (n = 1; n <= sw->mib_port_cnt; n++) {
			q = get_phy_port(sw, n);
			info = get_port_info(sw, q);
			if (!memcmp(eth->h_source, info->mac_addr, ETH_ALEN)) {
				mac_oper = false;
				break;
			}
		}
		if (!mac_oper) {
			kfree_skb(skb);
			return 0;
		}

		port = &mrp->mrp_ports[p];
		app = rcu_dereference(port->applicants[appl->type]);
		if (!app) {
dbg_msg(" no app! %d=%d"NL, p, appl->type);
			kfree_skb(skb);
			return 0;
		}

		/* Destination MAC address needs to match MRP address. */
		if (memcmp(app->group_address, eth->h_dest, ETH_ALEN))
			goto done;
		proc_mrp_rcv(mrp, app, skb);
		return 0;
	}

done:
	if (!memcmp(mrp->svlan_addr, eth->h_dest, ETH_ALEN)) {
		/* Forward frame if port is C-VLAN. */
	}

	/* Known MRP type. */
	if (appl) {
		kfree_skb(skb);
		return 0;
	}
	return 1;
}  /* mrp_rcv */
#endif

#ifdef CONFIG_KSZ_MSRP
static void mrp_delete_reserv(struct mrp_info *mrp, u8 port, int direction)
{
	struct mrp_port_info *info;
	struct SRP_reserv *reserv;
	struct SRP_reserv *next;

	info = mrp_get_port_info(mrp, port);
	reserv = info->registered.next;
	while (reserv) {
		next = reserv->next;
		if (reserv->direction == direction) {
			if (SRP_TALKER == direction)
				mrp_delete_talker(mrp, port, info, reserv);
			else
				mrp_delete_listener(mrp, port, info, reserv);
		}
		reserv = next;
	}
}

static void mrp_reset_reserv(struct mrp_info *mrp, uint first, uint last)
{
	struct mrp_port_info *info;
	struct SRP_reserv *reserv;
	struct SRP_reserv *next;
	uint n;
	uint p;
	struct ksz_sw *sw = mrp->parent;

	for (n = first; n <= last; n++) {
		p = get_phy_port(sw, n);
		mrp_delete_reserv(mrp, p, SRP_LISTENER);
	}
	for (n = first; n <= last; n++) {
		p = get_phy_port(sw, n);
		mrp_delete_reserv(mrp, p, SRP_TALKER);
	}
	for (n = first; n <= last; n++) {
		p = get_phy_port(sw, n);
		info = mrp_get_port_info(mrp, p);
		reserv = info->declared.next;
		while (reserv) {
			next = reserv->next;
			if (SRP_TALKER == reserv->direction &&
			    reserv->stream) {
				struct mrp_port_info *rx;
				struct SRP_reserv *t_reserv;
				struct SRP_stream *stream = reserv->stream;

				rx = mrp_get_port_info(mrp, stream->in_port);
				t_reserv = srp_find_reserv(&rx->registered,
					stream->id, SRP_TALKER);
				if (t_reserv) {
					t_reserv->tx_ports &= ~BIT(p);
				}
			}
			srp_remove_reserv(reserv, true);
			reserv = next;
		}
	}
}  /* mrp_reset_resev */
#endif

static void proc_mrp_attribute(struct mrp_info *mrp, u8 *data)
{
	uint p;
	u8 in_port;
#ifdef CONFIG_KSZ_MRP
	int output;
#endif
	int result;
	struct ksz_sw *sw = mrp->parent;
	struct mrp_cfg_options *cmd = (struct mrp_cfg_options *) data;

	mutex_lock(&mrp->lock);
	in_port = cmd->port;
	result = proc_mrp_set_attribute(mrp, data);
	while (DEV_IOC_MRP_REPORT == result) {
		cmd->action = MRP_ACTION_TX;
		cmd->type = MRP_TYPE_UNKNOWN;
#ifdef CONFIG_KSZ_MRP
		result = proc_mrp_get_attribute(mrp, data, &output);
#endif
		if (cmd->action != MRP_ACTION_TX &&
		    cmd->action != MRP_ACTION_TX_NEW &&
		    cmd->action != MRP_ACTION_LV)
			continue;

		cmd->new_decl = false;
		if (MRP_ACTION_TX_NEW == cmd->action) {
			cmd->action = MRP_ACTION_TX;
			cmd->new_decl = true;
		}
		p = get_phy_port(sw, cmd->port);
#ifdef CONFIG_KSZ_MRP
		if (MRP_TYPE_MAC == cmd->type) {
			if (MRP_ACTION_TX == cmd->action)
				proc_mrp_join_mac(mrp, p, &cmd->data.mac,
					cmd->new_decl);
			else
				mrp->mac_tx[p] |=
					proc_leave_mac(mrp, p,
						       &cmd->data.mac);
		} else if (MRP_TYPE_VLAN == cmd->type) {
			if (MRP_ACTION_TX == cmd->action)
				proc_mrp_join_vlan(mrp, p, &cmd->data.vlan,
					cmd->new_decl);
			else
				mrp->vlan_tx[p] |=
					proc_leave_vlan(mrp, p,
							&cmd->data.vlan);

#ifdef CONFIG_KSZ_MSRP
		} else if (MRP_TYPE_TALKER == cmd->type) {
			if (MRP_ACTION_TX == cmd->action)
				proc_mrp_new_talker(mrp, p,
					&cmd->data.talker, cmd->new_decl);
			else
				mrp->srp_tx[p] |=
					proc_leave_talker(mrp, p,
							   &cmd->data.talker);
		} else if (MRP_TYPE_LISTENER == cmd->type) {
			if (MRP_ACTION_TX == cmd->action)
				proc_mrp_new_listener(mrp, p,
					&cmd->data.listener, cmd->new_decl);
			else
				mrp->srp_tx[p] |=
					proc_leave_listener(mrp, p,
							     &cmd->data.listener);
		} else if (MRP_TYPE_DOMAIN == cmd->type) {
			if (MRP_ACTION_TX == cmd->action)
				proc_mrp_join_domain(mrp, p,
					&cmd->data.domain, cmd->new_decl);
			else
				mrp->srp_tx[p] |=
					proc_leave_domain(mrp, p,
							   &cmd->data.domain);
#endif
		}
#endif
	}
	mutex_unlock(&mrp->lock);
}  /* proc_mrp_attribute */

#ifdef CONFIG_KSZ_MRP
static void mmrp_acton(struct mrp_applicant *app, struct mrp_attr *attr)
{
	u8 data[40];
	struct mrp_cfg_options *cmd = (struct mrp_cfg_options *) data;
	struct mrp_info *mrp = app->parent;
	struct ksz_sw *sw = mrp->parent;

	cmd->port = get_log_port(sw, app->port);
	if (MMRP_ATTR_MAC == attr->type) {
		memcpy(cmd->data.mac.addr, attr->value, ETH_ALEN);
		cmd->type = MRP_TYPE_MAC;
		cmd->new_decl = MRP_NOTIFY_NEW == attr->notify;
		if (!(app->normal & (1 << attr->type)))
			cmd->new_decl |= 0x80;
		if (MRP_NOTIFY_LV == attr->notify)
			cmd->action = MRP_ACTION_LV;
		else
			cmd->action = MRP_ACTION_RX;
	}
	attr->notify = MRP_NOTIFY_NONE;
	if (cmd->type != MRP_TYPE_UNKNOWN)
		proc_mrp_attribute(mrp, data);
}  /* mmrp_acton */

static void mmrp_cleanup(struct mrp_applicant *app)
{
	uint n;
	uint p;
	struct mrp_info *mrp = app->parent;
	struct ksz_sw *sw = mrp->parent;

	for (n = 0; n <= sw->mib_port_cnt; n++) {
		p = get_phy_port(sw, n);
		if (mrp->mac_tx[p]) {
			mrp->mac_tx[p] = 0;
			proc_mrp_req_lv(mrp, p, &mac_mrp_app);
		}
	}
}  /* mmrp_cleanup */

static void mvrp_acton(struct mrp_applicant *app, struct mrp_attr *attr)
{
	u8 data[40];
	struct mrp_cfg_options *cmd = (struct mrp_cfg_options *) data;
	struct mrp_info *mrp = app->parent;
	struct ksz_sw *sw = mrp->parent;

	cmd->port = get_log_port(sw, app->port);
	if (MVRP_ATTR_VID == attr->type) {
		u16 *vid = (u16 *) attr->value;

		cmd->data.vlan.id = ntohs(*vid);
		cmd->type = MRP_TYPE_VLAN;
		cmd->new_decl = MRP_NOTIFY_NEW == attr->notify;
		if (!(app->normal & (1 << attr->type)))
			cmd->new_decl |= 0x80;
		if (MRP_NOTIFY_LV == attr->notify)
			cmd->action = MRP_ACTION_LV;
		else
			cmd->action = MRP_ACTION_RX;
	}
	attr->notify = MRP_NOTIFY_NONE;
	if (cmd->type != MRP_TYPE_UNKNOWN)
		proc_mrp_attribute(mrp, data);
}  /* mvrp_acton */

static void mvrp_cleanup(struct mrp_applicant *app)
{
	uint n;
	uint p;
	struct mrp_info *mrp = app->parent;
	struct ksz_sw *sw = mrp->parent;

	for (n = 0; n <= sw->mib_port_cnt; n++) {
		p = get_phy_port(sw, n);
		if (mrp->vlan_tx[p]) {
			mrp->vlan_tx[p] = 0;
			proc_mrp_req_lv(mrp, p, &vlan_mrp_app);
		}
	}
}  /* mvrp_cleanup */

#ifdef CONFIG_KSZ_MSRP
static void msrp_acton(struct mrp_applicant *app, struct mrp_attr *attr)
{
	u8 data[40];
	struct mrp_cfg_options *cmd = (struct mrp_cfg_options *) data;
	struct mrp_info *mrp = app->parent;
	struct ksz_sw *sw = mrp->parent;

	cmd->port = get_log_port(sw, app->port);
	switch (attr->type) {
	case MSRP_ATTR_TALKER_FAILED:
	{
		struct SRP_talker *talker = &cmd->data.talker;
		struct srp_talker_failed *attr_talker =
			(struct srp_talker_failed *) attr->value;

		mrp_get_talker(talker, attr_talker);
		cmd->type = MRP_TYPE_TALKER;
		cmd->new_decl = MRP_NOTIFY_NEW == attr->notify;
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
		cmd->new_decl = MRP_NOTIFY_NEW == attr->notify;
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
		cmd->new_decl = MRP_NOTIFY_NEW == attr->notify;
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

static void msrp_cleanup(struct mrp_applicant *app)
{
	uint n;
	uint p;
	struct mrp_info *mrp = app->parent;
	struct ksz_sw *sw = mrp->parent;

	for (n = 0; n <= sw->mib_port_cnt; n++) {
		p = get_phy_port(sw, n);
		if (mrp->srp_tx[p]) {
			mrp->srp_tx[p] = 0;
			proc_mrp_req_lv(mrp, p, &srp_mrp_app);
		}
	}
}  /* msrp_cleanup */
#endif
#endif

static void setup_mrp(struct mrp_info *mrp, struct net_device *dev)
{
	struct ksz_mac_table *entry;
	struct ksz_alu_table *alu;
	int i;
	int j;
	struct ksz_sw *sw = mrp->parent;

#ifdef CONFIG_KSZ_MRP

#ifndef NETIF_F_HW_VLAN_CTAG_FILTER
	prandom32_seed(&rnd, get_random_int());
#endif
	memcpy(mrp->cvlan_addr, vlan_mrp_app.group_address, ETH_ALEN);
	memcpy(mrp->svlan_addr, vlan_mrp_app.group_address, ETH_ALEN);
	mrp->svlan_addr[5] = 0x0D;
#endif

	i = sw->info->multi_sys;
	for (j = 0; j < 3; j++) {
		entry = &sw->info->mac_table[--i];
		memcpy(entry->addr, maap_addr[j], ETH_ALEN);
		entry->fid = 0;
		if ((entry->addr[0] & 0x0F) == 0x01)
			entry->ports = sw->PORT_MASK;
		else
			entry->ports = sw->PORT_MASK & ~sw->HOST_MASK;
		alu = &sw->info->alu_table[i];
		alu->forward = FWD_MAIN_DEV | FWD_MCAST | FWD_KNOWN;
		alu->owner = 1;
		alu->valid = 1;
		alu->index = 0;
		alu->type = 2;
		sw->ops->cfg_mac(sw, 0, maap_addr[j], entry->ports, false,
				 false, 0);
	}
	sw->info->multi_sys = i;
}  /* setup_mrp */

#ifdef CONFIG_KSZ_MRP
static struct mrp_applicant *mrp_start_port_app(struct mrp_info *mrp,
	uint p, struct net_device *dev, struct mrp_application *appl)
{
	int err;
	struct mrp_applicant *app;
	struct mrp_port *port;
	struct ksz_sw *sw = mrp->parent;
	struct ksz_port_info *info = &sw->port_info[p];

	port = &mrp->mrp_ports[p];
	err = mrp_init_applicant(port, mrp, p, dev, appl);
	app = rcu_dereference(port->applicants[appl->type]);
	memcpy(app->src_addr, info->mac_addr, ETH_ALEN);
	return app;
}  /* mrp_start_port_app */

static void mrp_stop_port_app(struct mrp_port *port,
	struct mrp_application *appl, int attrtype, bool rx)
{
	struct rb_node *node, *next;
	struct mrp_attr *attr;
	struct mrp_applicant *app;

	app = rcu_dereference(port->applicants[appl->type]);
	if (!app)
printk(" %s!!\n", __func__);
	if (!app)
		return;
	for (node = rb_first(&app->mad);
	     next = node ? rb_next(node) : NULL, node != NULL;
	     node = next) {
		attr = rb_entry(node, struct mrp_attr, node);

		if (rx || (attr->type == attrtype &&
		    attr->reg_state == MRP_REGISTRAR_MT))
			mrp_attr_destroy(app, attr);
	}
	if (rx)
		mrp_uninit_applicant(port, appl);
}  /* mrp_stop_port_app */

static void mrp_start_mmrp_port_app(struct mrp_info *mrp, uint p,
				struct net_device *dev)
{
	struct mrp_applicant *app;

	app = mrp_start_port_app(mrp, p, dev, &mac_mrp_app);
	mmrp_init_application(app, mmrp_acton, mmrp_cleanup);
	mrp_periodic_event(app, MRP_EVENT_PERIODIC_ENABLE);
}  /* mrp_start_mmrp_port_app */

static void mrp_start_mmrp_app(struct mrp_info *mrp)
{
	uint n;
	uint p;
	int err;
	struct ksz_sw *sw = mrp->parent;
	struct net_device *dev = sw->main_dev;

	err = dev_mc_add(dev, mac_mrp_app.group_address);
	for (n = 0; n <= mrp->ports; n++) {
		p = get_phy_port(sw, n);
		if (!(mrp->mmrp_rx_ports & (1 << p)))
			continue;

		mrp_start_mmrp_port_app(mrp, p, dev);
	}
}  /* mrp_start_mmrp_app */

static void mrp_stop_mmrp_app(struct mrp_info *mrp)
{
	uint n;
	uint p;
	struct ksz_sw *sw = mrp->parent;
	struct net_device *dev = sw->main_dev;

	for (n = 0; n <= mrp->ports; n++) {
		p = get_phy_port(sw, n);
		if (!(mrp->mmrp_rx_ports & (1 << p)))
			continue;

		mrp_stop_port_app(&mrp->mrp_ports[p], &mac_mrp_app, 0, true);
	}
	dev_mc_del(dev, mac_mrp_app.group_address);
}  /* mrp_stop_mmrp_app */

static void mrp_start_mvrp_port_app(struct mrp_info *mrp, uint p,
				struct net_device *dev)
{
	struct mrp_applicant *app;

	app = mrp_start_port_app(mrp, p, dev, &vlan_mrp_app);
	mvrp_init_application(app, mvrp_acton, mvrp_cleanup);
	app->group_address = mrp->cvlan_addr;
	mrp_periodic_event(app, MRP_EVENT_PERIODIC_ENABLE);
}  /* mrp_start_mvrp_port_app */

static void mrp_start_mvrp_app(struct mrp_info *mrp)
{
	uint n;
	uint p;
	int err;
	struct ksz_sw *sw = mrp->parent;
	struct net_device *dev = sw->main_dev;

	err = dev_mc_add(dev, vlan_mrp_app.group_address);
	err = dev_mc_add(dev, mrp->svlan_addr);
	for (n = 0; n <= mrp->ports; n++) {
		p = get_phy_port(sw, n);
		if (!(mrp->mvrp_rx_ports & (1 << p)))
			continue;

		mrp_start_mvrp_port_app(mrp, p, dev);
	}
}  /* mrp_start_mvrp_app */

static void mrp_stop_mvrp_app(struct mrp_info *mrp)
{
	uint n;
	uint p;
	struct ksz_sw *sw = mrp->parent;
	struct net_device *dev = sw->main_dev;

	for (n = 0; n <= mrp->ports; n++) {
		p = get_phy_port(sw, n);
		if (!(mrp->mvrp_rx_ports & (1 << p)))
			continue;

		mrp_stop_port_app(&mrp->mrp_ports[p], &vlan_mrp_app, 0, true);
	}
	dev_mc_del(dev, vlan_mrp_app.group_address);
	dev_mc_del(dev, mrp->svlan_addr);
}  /* mrp_stop_mvrp_app */

#ifdef CONFIG_KSZ_MSRP
static void mrp_start_msrp_port_app(struct mrp_info *mrp, uint p,
				struct net_device *dev)
{
	struct mrp_applicant *app;

	app = mrp_start_port_app(mrp, p, dev, &srp_mrp_app);
	msrp_init_application(app, msrp_acton, msrp_cleanup);
	mrp_periodic_event(app, MRP_EVENT_PERIODIC_DISABLE);
}  /* mrp_start_msrp_port_app */

static void mrp_start_msrp_app(struct mrp_info *mrp)
{
	uint n;
	uint p;
	int err;
	struct ksz_sw *sw = mrp->parent;
	struct net_device *dev = sw->main_dev;

	err = dev_mc_add(dev, srp_mrp_app.group_address);
	for (n = 0; n <= mrp->ports; n++) {
		p = get_phy_port(sw, n);
		if (!mrp->port_info[p].status.msrpPortEnabledStatus)
			continue;

		mrp_start_msrp_port_app(mrp, p, dev);
	}
}  /* mrp_start_msrp_app */

static void mrp_stop_msrp_app(struct mrp_info *mrp)
{
	uint n;
	uint p;
	struct ksz_sw *sw = mrp->parent;
	struct net_device *dev = sw->main_dev;

	for (n = 0; n <= mrp->ports; n++) {
		p = get_phy_port(sw, n);
		if (!mrp->port_info[p].status.msrpPortEnabledStatus)
			continue;

		mrp_stop_port_app(&mrp->mrp_ports[p], &srp_mrp_app, 0, true);
	}
	dev_mc_del(dev, srp_mrp_app.group_address);
}  /* mrp_stop_msrp_app */
#endif

#if 0
static void proc_mrp_chk_declared(struct mrp_info *mrp, uint port, int on)
{
	int result;
	struct mrp_node *prev;
	struct mrp_node *next;
	struct mrp_mac_info *mac;
	struct mrp_vlan_info *vlan;
	struct ksz_sw *sw = mrp->parent;
	u8 lp = sw_get_net_port(sw, 0, mrp->ports, port);

#if 1
	struct SRP_reserv *reserv;
	struct mrp_port_info *info;

	info = &mrp->port_info[port];
		if (!mrp->port_info[p].status.msrpPortEnabledStatus)
			continue;

		mrp_start_msrp_port_decl(mrp, &mrp->mrp_ports[p]);
	reserv = info->declared.next;
	while (reserv) {
		if (on) {
			reserv->tx_ports |= BIT(lp);
			if (reserv->direction == SRP_TALKER) {
				struct SRP_talker talker;

				memcpy(&talker, reserv->stream, 25);
				memcpy(talker.bridge_id, reserv->bridge_id, 8);
				talker.FailureCode = reserv->code;
				result = proc_mrp_new_talker(mrp, port,
					&talker, true);
			} else if (reserv->direction == SRP_LISTENER) {
				struct SRP_listener listener;

				memcpy(&listener, reserv->stream, 8);
				listener.substate = reserv->declaration;
				result = proc_mrp_new_listener(mrp, port,
					&listener, true);
			}
		} else {
			reserv->tx_ports &= ~BIT(lp);
		}
		reserv = reserv->next;
	}
#endif
	prev = &mrp->mac_list.anchor;
	next = prev->next;
	while (next) {
		mac = next->data;

		if (mac->tx_ports & BIT(lp) && !on) {
			mac->tx_ports &= ~BIT(lp);
		} else if (!(mac->tx_ports & BIT(port)) && on) {
			struct MRP_mac mrp_mac;

			memcpy(mrp_mac.addr, mac->addr, ETH_ALEN);
			mac->tx_ports |= BIT(lp);
			result = proc_mrp_join_mac(mrp, port,
				&mrp_mac, true);
		}
		prev = next;
		next = prev->next;
	}
	prev = &mrp->vlan_list.anchor;
	next = prev->next;
	while (next) {
		vlan = next->data;

		if (vlan->tx_ports & BIT(port) && !on) {
			vlan->tx_ports &= ~BIT(lp);
		} else if (!(vlan->tx_ports & BIT(port)) && on) {
			struct MRP_vlan mrp_vlan;

			vlan->tx_ports |= BIT(lp);
			mrp_vlan.id = vlan->vid;
			result = proc_mrp_join_vlan(mrp, port,
				&mrp_vlan, true);
		}
		prev = next;
		next = prev->next;
	}
}  /* proc_mrp_chk_declared */
#endif

static void mrp_start_app(struct mrp_info *mrp)
{
	mrp_start_mmrp_app(mrp);
	mrp_start_mvrp_app(mrp);

#ifdef CONFIG_KSZ_MSRP
	if (mrp->status.msrpEnabledStatus)
		mrp_start_msrp_app(mrp);
#endif
}  /* mrp_start_app */

static void mrp_stop_app(struct mrp_info *mrp)
{
	mrp_stop_mmrp_app(mrp);
	mrp_stop_mvrp_app(mrp);

#ifdef CONFIG_KSZ_MSRP
	if (mrp->status.msrpEnabledStatus)
		mrp_stop_msrp_app(mrp);
#endif
}  /* mrp_stop_app */

static void mrp_mmrp_decl(struct mrp_info *mrp, uint p, bool on)
{
	int result;
	struct mrp_node *prev;
	struct mrp_node *next;
	struct mrp_mac_info *mac;
	uint m = BIT(p);

	prev = &mrp->mac_list.anchor;
	next = prev->next;
	while (next) {
		mac = next->data;

		if ((mac->tx_ports & m) && !on) {
			/* Leave request will be sent. */
			mac->tx_ports &= ~m;
		} else if ((mac->mrp_ports & ~m) &&
			   !(mac->tx_ports & m) && on) {
			struct MRP_mac mrp_mac;

			memcpy(mrp_mac.addr, mac->addr, ETH_ALEN);
			mac->tx_ports |= m;
			result = proc_mrp_join_mac(mrp, p, &mrp_mac, true);
		}
		prev = next;
		next = prev->next;
	}
}  /* mrp_mmrp_decl */

static void mrp_mvrp_decl(struct mrp_info *mrp, uint p, bool on)
{
	int result;
	struct mrp_node *prev;
	struct mrp_node *next;
	struct mrp_vlan_info *vlan;
	uint m = BIT(p);

	prev = &mrp->vlan_list.anchor;
	next = prev->next;
	while (next) {
		vlan = next->data;

		if (vlan->ports & SRP_PORT_AVAIL) {
			if ((vlan->tx_ports & m) && !on) {
				/* Leave request will be sent. */
				vlan->tx_ports &= ~m;
			} else if (!(vlan->tx_ports & m) && on) {
				struct MRP_vlan mrp_vlan;

				vlan->tx_ports |= m;
				mrp_vlan.id = vlan->vid;
				result = proc_mrp_join_vlan(mrp, p, &mrp_vlan,
							    true);
			}
		}
		prev = next;
		next = prev->next;
	}
}  /* mrp_mvrp_decl */

#ifdef CONFIG_KSZ_MSRP
static void mrp_msrp_decl(struct mrp_info *mrp, uint p, bool on)
{
	int result;
	struct SRP_reserv *reserv;
	struct mrp_port_info *info;
	uint m = BIT(p);

	info = &mrp->port_info[p];
	reserv = info->declared.next;
	while (reserv) {
		if (on) {
			reserv->tx_ports |= m;
			if (reserv->direction == SRP_TALKER) {
				struct SRP_talker talker;

				memcpy(&talker, reserv->stream, 25);
				memcpy(talker.bridge_id, reserv->bridge_id, 8);
				talker.FailureCode = reserv->code;
				result = proc_mrp_new_talker(mrp, p,
					&talker, true);
			} else if (reserv->direction == SRP_LISTENER) {
				struct SRP_listener listener;

				memcpy(&listener, reserv->stream, 8);
				listener.substate = reserv->declaration;
				result = proc_mrp_new_listener(mrp, p,
					&listener, true);
			}
		} else {
			/* Leave request will be sent. */
			reserv->tx_ports &= ~m;
		}
		reserv = reserv->next;
	}
	if (on) {
#if 0
struct SRP_domain_class domain;
memcpy(&domain, &mrp->domain[0], sizeof(domain));
domain.id = 5;
domain.priority = 6;
proc_mrp_join_domain(mrp, p, &domain, true);
domain.id = 6;
domain.priority = 7;
proc_mrp_join_domain(mrp, p, &domain, true);
#endif
		proc_mrp_join_domain(mrp, p, &mrp->domain[0], true);
		if (mrp->domain[1].id)
			proc_mrp_join_domain(mrp, p, &mrp->domain[1], true);
	}
}  /* mrp_msrp_decl */
#endif

static void mmrp_close_port(struct mrp_info *mrp, uint p)
{
	/* MMRP is not enabled. */
	if (!(mrp->mmrp_tx_ports & BIT(p)))
		return;
	mrp_mmrp_decl(mrp, p, false);
}  /* mmrp_close_port */

static void mmrp_open_port(struct mrp_info *mrp, uint p)
{
	struct mrp_applicant *app;
	struct mrp_port *port = &mrp->mrp_ports[p];

	/* MMRP is not enabled. */
	if (!(mrp->mmrp_tx_ports & BIT(p)))
		return;
	app = rcu_dereference(port->applicants[mac_mrp_app.type]);
if (!app)
dbg_msg(" %s"NL, __func__);
	if (!app) {
		struct ksz_sw *sw = mrp->parent;

		mrp_start_mmrp_port_app(mrp, p, sw->main_dev);
	}
	mrp_mmrp_decl(mrp, p, true);
}  /* mmrp_open_port */

static void mvrp_close_port(struct mrp_info *mrp, uint p)
{
	/* MVRP is not enabled. */
	if (!(mrp->mvrp_tx_ports & BIT(p)))
		return;
	mrp_mvrp_decl(mrp, p, false);
}  /* mvrp_close_port */

static void mvrp_open_port(struct mrp_info *mrp, uint p)
{
	struct mrp_applicant *app;
	struct mrp_port *port = &mrp->mrp_ports[p];

	/* MVRP is not enabled. */
	if (!(mrp->mvrp_tx_ports & BIT(p)))
		return;
	app = rcu_dereference(port->applicants[vlan_mrp_app.type]);
if (!app)
dbg_msg(" %s"NL, __func__);
	if (!app) {
		struct ksz_sw *sw = mrp->parent;

		mrp_start_mvrp_port_app(mrp, p, sw->main_dev);
	}
	mrp_mvrp_decl(mrp, p, true);
}  /* mvrp_open_port */

#ifdef CONFIG_KSZ_MSRP
static void msrp_close_port(struct mrp_info *mrp, uint p)
{
	/* MSRP is not enabled. */
	if (!mrp->status.msrpEnabledStatus ||
	    !mrp->port_info[p].status.msrpPortEnabledStatus)
		return;
	mrp_msrp_decl(mrp, p, false);
}  /* msrp_close_port */

static void msrp_open_port(struct mrp_info *mrp, uint p)
{
	struct mrp_applicant *app;
	struct mrp_port *port = &mrp->mrp_ports[p];

	/* MSRP is not enabled. */
	if (!mrp->status.msrpEnabledStatus ||
	    !mrp->port_info[p].status.msrpPortEnabledStatus)
		return;
	app = rcu_dereference(port->applicants[srp_mrp_app.type]);
if (!app)
dbg_msg(" %s"NL, __func__);
	if (!app) {
		struct ksz_sw *sw = mrp->parent;

		mrp_start_msrp_port_app(mrp, p, sw->main_dev);
	}
	mrp_msrp_decl(mrp, p, true);
}  /* msrp_open_port */
#endif

static void mrp_close_port(struct mrp_info *mrp, uint p)
{
	uint m = BIT(p);

dbg_msg("%s %d=%d"NL, __func__, p, mrp->started);
	if (!mrp->started || !(mrp->tx_ports & m))
		return;
	if (!(mrp->mask & m))
		return;
#ifdef CONFIG_KSZ_MSRP
	msrp_close_port(mrp, p);
#endif
	mvrp_close_port(mrp, p);
	mmrp_close_port(mrp, p);

	/* Every declaration leaves. */
	mrp_event(mrp, p, MRP_EVENT_LV);
#if 1
	mrp_event(mrp, p, MRP_EVENT_R_LV);
#endif
	mrp->tx_ports &= ~m;
	mrp->rx_ports = mrp->tx_ports;
}  /* mrp_close_port */

static void mrp_open_port(struct mrp_info *mrp, uint p)
{
	uint m = BIT(p);

dbg_msg("%s %d=%d"NL, __func__, p, mrp->started);
	if (!mrp->started || (mrp->tx_ports & m))
		return;
	if (!(mrp->mask & m))
		return;
#ifdef CONFIG_KSZ_MSRP
	msrp_open_port(mrp, p);
#endif
	mvrp_open_port(mrp, p);
	mmrp_open_port(mrp, p);
	mrp->tx_ports |= m;
	mrp->rx_ports = mrp->tx_ports;
}  /* mrp_open_port */

#ifdef CONFIG_KSZ_MSRP
static void msrp_open_ports(struct mrp_info *mrp)
{
	uint n;
	uint p;
	struct ksz_sw *sw = mrp->parent;

	for (n = 0; n <= mrp->ports; n++) {
		p = get_phy_port(sw, n);
		if (p == sw->HOST_PORT ||
		    sw->info->port_cfg[p].stp_state[0] == STP_STATE_FORWARDING)
			msrp_open_port(mrp, p);
	}
}  /* msrp_open_ports */
#endif

static void mrp_open_ports(struct mrp_info *mrp)
{
	uint n;
	uint p;
	struct ksz_sw *sw = mrp->parent;

	for (n = 0; n <= mrp->ports; n++) {
		p = get_phy_port(sw, n);
		if (p == sw->HOST_PORT ||
		    sw->info->port_cfg[p].stp_state[0] == STP_STATE_FORWARDING)
			mrp_open_port(mrp, p);
	}
}  /* mrp_open_ports */

static void mrp_from_backup(struct mrp_info *mrp, uint p)
{
dbg_msg("%s %d"NL, __func__, p);
	mrp->rx_ports |= (1 << p);

	/* mrp_open_port will be called when the port is forwarding. */
}  /* mrp_from_backup */

static void mrp_to_backup(struct mrp_info *mrp, uint p)
{
dbg_msg("%s %d"NL, __func__, p);
	mrp_close_port(mrp, p);
}  /* mrp_to_backup */

static void mrp_from_designated(struct mrp_info *mrp, uint p, bool alt)
{
dbg_msg("%s %d=%d"NL, __func__, p, alt);
	if (!mrp->started)
		return;
	mrp_event(mrp, p, MRP_EVENT_REDECLARE);
	if (alt) {
		mrp_close_port(mrp, p);
	}
}  /* mrp_from_designated */

static void mrp_to_designated(struct mrp_info *mrp, uint p)
{
	uint m = BIT(p);

dbg_msg("%s %d"NL, __func__, p);
	if (!mrp->started)
		return;
	mrp_event(mrp, p, MRP_EVENT_FLUSH);
	if (!(mrp->rx_ports & m)) {
dbg_msg("  fwd again"NL);
		mrp->rx_ports |= m;

		/* mrp_open_port will be called when the port is forwarding. */
	}
}  /* mrp_to_designated */

static void mrp_tc_detected(struct mrp_info *mrp, uint p)
{
	uint m = BIT(p);

dbg_msg("%s %d"NL, __func__, p);
	if (!mrp->started)
		return;
	if (!(mrp->mask & m))
		return;
	if (mrp->mmrp_rx_ports & m) {
		mrp_new_event_port_app(mrp, p, &mac_mrp_app);
	}
	if (mrp->mvrp_rx_ports & m) {
		mrp_new_event_port_app(mrp, p, &vlan_mrp_app);
	}

#ifdef CONFIG_KSZ_MSRP
	if (mrp->status.msrpEnabledStatus &&
	    mrp->port_info[p].status.msrpPortEnabledStatus) {
		mrp_new_event_port_app(mrp, p, &srp_mrp_app);
	}
#endif
}  /* mrp_tc_detected */

static void mrp_start(struct mrp_info *mrp)
{
	mrp_start_app(mrp);
	mrp->started = true;
	mrp_open_ports(mrp);
}  /* mrp_start */

static void mrp_stop(struct mrp_info *mrp)
{
	if (mrp->started)
		mrp_stop_app(mrp);
	mrp->started = false;
}  /* mrp_stop */
#endif

#ifdef CONFIG_KSZ_AVB
static void mrp_open_avb(struct mrp_info *mrp)
{
	struct ksz_sw *sw = mrp->parent;
	struct mrp_traffic_info *traffic;
	struct mrp_port_info *info;
	uint n;
	uint p;
	u8 tc;

	if (!(sw->features & AVB_SUPPORT))
		return;
	for (n = 0; n <= mrp->ports; n++) {
		p = get_phy_port(sw, n);
		info = mrp_get_port_info(mrp, p);
		for (tc = SR_CLASS_A; tc >= SR_CLASS_B; tc--) {
			traffic = get_traffic_info(info, tc);
			if (!traffic->bandwidth_used)
				continue;
			srp_cfg_credit_shaper(mrp, p, info, traffic);
			traffic->bandwidth_set = traffic->bandwidth_used;
		}
		if (n) {
			struct ksz_port_cfg *cfg = get_port_cfg(sw, p);
			bool remap = true;
			bool drop = false;

			if (!(sw->features & MRP_SUPPORT)) {
				cfg->avb_a = true;
				cfg->avb_b = true;
				remap = false;
				drop = false;
			}
			setup_acl_drop(mrp, p);
			setup_acl_remap(mrp, p);
			enable_acl_remap(mrp, p, remap, drop);
		}
		for (tc = 0; tc < PRIO_QUEUES; tc++)
			srp_cfg_idle_slope(mrp, p, tc, info,
				info->bandwidth[tc].adminIdleSlope);
	}
}  /* mrp_open_avb */
#endif

#ifdef CONFIG_KSZ_MRP
static void mrp_open_mrp(struct mrp_info *mrp)
{
	struct mrp_node *prev;
	struct mrp_node *next;
	struct mrp_mac_info *mac;
	struct mrp_vlan_info *vlan;
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
}  /* mrp_open_mrp */
#endif

#if defined(CONFIG_KSZ_AVB) || defined(CONFIG_KSZ_MRP)
static void mrp_open(struct mrp_info *mrp)
{
#ifdef CONFIG_KSZ_AVB
	mrp_open_avb(mrp);
#endif
#ifdef CONFIG_KSZ_MRP
	mrp_open_mrp(mrp);
#endif
}  /* mrp_open */
#endif

#ifdef CONFIG_KSZ_MRP
static void mrp_clr_blocked_addr(struct mrp_info *mrp, int hw_access)
{
	struct mrp_node *prev;
	struct mrp_node *next;
	struct mrp_mac_info *mac;

	prev = &mrp->mac_list.anchor;
	next = prev->next;
	while (next) {
		mac = next->data;
		if ((mac->rx_ports & SRP_PORT_DROP) &&
		    (mac->srp_ports & SRP_PORT_BLACKLIST)) {
dbg_msg("  rmv: %02x:%02x:%02x:%02x:%02x:%02x %d"NL,
mac->addr[0], mac->addr[1], mac->addr[2], mac->addr[3], mac->addr[4], mac->addr[5], mac->fid);
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
	struct mrp_node *prev;
	struct mrp_node *next;
	struct mrp_mac_info *mac;
	struct ksz_sw *sw = mrp->parent;

	prev = &mrp->mac_list.anchor;
	next = prev->next;
	while (next) {
		mac = next->data;
		if ((mac->srp_ports & SRP_PORT_BLACKLIST) &&
		    time_after_eq(jiffies, mac->ticks)) {
			uint n;
			uint p;
			bool avb;
			u16 ports;
			struct ksz_port_cfg *cfg;

			if (mac->rx_ports & SRP_PORT_IGNORE)
				mac->rx_ports |= SRP_PORT_DROP;
			mac->rx_ports |= SRP_PORT_IGNORE;
			avb = true;
			for (n = 1; n <= sw->mib_port_cnt; n++) {
				p = get_phy_port(sw, n);
				if (mac->rx_ports & (1 << p)) {
					cfg = get_port_cfg(sw, p);
					if (!cfg->avb_b) {
						avb = false;
						break;
					}
				}
			}
			if (avb)
				ports = sw->HOST_MASK;
			else
				ports = sw->PORT_MASK;
			sw->ops->cfg_mac(sw, mac->index, mac->addr, ports,
					 false, mac->fid != 0, mac->fid);
			mac->ticks = jiffies + msecs_to_jiffies(10000);
		}
		prev = next;
		next = prev->next;
	}
	mrp_clr_blocked_addr(mrp, true);
}  /* mrp_chk_blocked_addr */
#endif

#ifdef CONFIG_KSZ_MRP
static void mrp_close(struct mrp_info *mrp, int hw_access)
{
	if (mrp->started) {
		struct ksz_sw *sw = mrp->parent;

		mrp_close_port(mrp, sw->HOST_PORT);
		mrp_clr_blocked_addr(mrp, hw_access);
#if 0
		mrp->started = false;
#endif
	}
}  /* mrp_close */
#else
static void mrp_close(struct mrp_info *mrp, int hw_access)
{
}
#endif

#ifdef CONFIG_KSZ_AVB
static void mrp_set_slope(struct mrp_info *mrp, uint port, int index,
			  struct mrp_port_info *info, uint per)
{
	u32 slope;
	u64 val = per;

	val <<= CREDIT_PERCENTAGE_S;
	val += 500;
	val = div_u64_u32(val, 1000);
	slope = (u32)val;
	info->bandwidth[index].adminIdleSlope = slope;
	info->bandwidth[index].operIdleSlope = slope;
	srp_cfg_idle_slope(mrp, port, index, info, slope);
}  /* mrp_set_slope */
#endif

static ssize_t sysfs_mrp_read(struct ksz_sw *sw, int proc_num, ssize_t len,
	char *buf)
{
#ifdef CONFIG_KSZ_AVB
	struct mrp_info *mrp = &sw->mrp;
#endif
	int chk = 0;
	int type = SHOW_HELP_NONE;
	char note[40];

	note[0] = '\0';
	switch (proc_num) {
#ifdef CONFIG_KSZ_MSRP
	case PROC_GET_MSRP_INFO:
		if (!(sw->features & AVB_SUPPORT))
			return 0;
		if (!(sw->features & MRP_SUPPORT))
			return 0;
		len += sprintf(buf + len,
			"max interference size %u"NL,
			mrp->max_interference_size);
		if (regeneration_hack)
			len += sprintf(buf + len,
				"regeneration"NL);
		if (ba_hack)
			len += sprintf(buf + len,
				"BA"NL);
		if (mrp_10_1_2f_hack)
			len += sprintf(buf + len,
				"MRP.10.1.2F"NL);
		if (mrp_10_1_8a_hack)
			len += sprintf(buf + len,
				"MRP.10.1.8A"NL);
		if (mrp_10_5_1_hack)
			len += sprintf(buf + len,
				"MRP.10.5.1"NL);
		if (mrp_10_5_1c_hack)
			len += sprintf(buf + len,
				"MRP.10.5.1C"NL);
		if (mrp_10_5_1d_hack)
			len += sprintf(buf + len,
				"MRP.10.5.1D"NL);
		if (msrp_35_1_14g_hack)
			len += sprintf(buf + len,
				"MSRP.35.1.14G"NL);
		if (fqtss_hack)
			len += sprintf(buf + len,
				"FQTSS"NL);
		if (fqtss_34_2_3_hack)
			len += sprintf(buf + len,
				"FQTSS.34.2.3"NL);
		if (fqtss_34_2_1b_hack)
			len += sprintf(buf + len,
				"FQTSS.34.2.1B"NL);
		if (fqtss_34_2_5b_hack)
			len += sprintf(buf + len,
				"FQTSS.34.2.5B"NL);
		if (fqtss_34_2_9b_hack)
			len += sprintf(buf + len,
				"FQTSS.34.2.9B"NL);
		break;
	case PROC_SET_MSRP_ENABLED:
		chk = mrp->status.msrpEnabledStatus;
		type = SHOW_HELP_ON_OFF;
		break;
#endif
#ifdef CONFIG_KSZ_AVB
	case PROC_SET_MSRP_SR_A:
		chk = mrp->domain[1].id != 0;
		type = SHOW_HELP_ON_OFF;
		break;
#endif
	default:
		type = SHOW_HELP_NONE;
		break;
	}
	return sysfs_show(len, buf, type, chk, note, sw->verbose);
}  /* sysfs_mrp_read */

static int sysfs_mrp_write(struct ksz_sw *sw, int proc_num, int num,
	const char *buf)
{
#ifdef CONFIG_KSZ_AVB
	struct mrp_info *mrp = &sw->mrp;
#endif
	int processed = true;

	if (!(sw->features & AVB_SUPPORT))
		return false;
	switch (proc_num) {
#ifdef CONFIG_KSZ_MSRP
	case PROC_GET_MSRP_INFO:
		if (!(sw->features & MRP_SUPPORT))
			break;
		if (!strncmp(buf, "mrp_10.1.2f", 11))
			mrp_10_1_2f_hack = true;
		else if (!strncmp(buf, "mrp_10.1.8a", 11))
			mrp_10_1_8a_hack = true;
		else if (!strncmp(buf, "mrp_10.5.1c", 11))
			mrp_10_5_1c_hack = true;
		else if (!strncmp(buf, "mrp_10.5.1d", 11))
			mrp_10_5_1d_hack = true;
		else if (!strncmp(buf, "mrp_10.5.1", 10))
			mrp_10_5_1_hack = true;
		else if (!strncmp(buf, "msrp_35.1.14g", 13))
			msrp_35_1_14g_hack = true;
		else if (!strncmp(buf, "fqtss_34.2.3", 12))
			fqtss_34_2_3_hack = true;
		else if (!strncmp(buf, "fqtss_34.2.1b", 13))
			fqtss_34_2_1b_hack = true;
		else if (!strncmp(buf, "fqtss_34.2.5b", 13))
			fqtss_34_2_5b_hack = true;
		else if (!strncmp(buf, "fqtss_34.2.9b", 13))
			fqtss_34_2_9b_hack = true;
		else if (!strncmp(buf, "fqtss", 5))
			fqtss_hack = true;
		else if (!strncmp(buf, "ba", 2))
			ba_hack = true;
		else if (!strncmp(buf, "regeneration", 12)) {
			if (!regeneration_hack) {
				uint n;
				uint p;

				regeneration_hack = true;
				for (n = 0; n <= mrp->ports; n++) {
					p = get_phy_port(sw, n);
					setup_acl_remap(mrp, p);
				}
			}
		} else if (!strncmp(buf, "reset", 5)) {
			ba_hack = false;
			mrp_10_1_2f_hack = false;
			mrp_10_1_8a_hack = false;
			mrp_10_5_1_hack = false;
			mrp_10_5_1c_hack = false;
			mrp_10_5_1d_hack = false;
			msrp_35_1_14g_hack = false;
			fqtss_hack = false;
			fqtss_34_2_3_hack = false;
			fqtss_34_2_1b_hack = false;
			fqtss_34_2_5b_hack = false;
			fqtss_34_2_9b_hack = false;
			if (regeneration_hack) {
				uint n;
				uint p;

				regeneration_hack = false;
				for (n = 0; n <= mrp->ports; n++) {
					p = get_phy_port(sw, n);
					setup_acl_remap(mrp, p);
				}
			}
		}
else
dbg_msg(" ?? %s]"NL, buf);
		break;
	case PROC_SET_MSRP_ENABLED:
		if (!(sw->features & MRP_SUPPORT))
			break;
		if (mrp->status.msrpEnabledStatus != !!num) {
			mutex_lock(&mrp->lock);
			if (!mrp->status.msrpEnabledStatus) {
				mrp_reset_reserv(mrp, 0, mrp->ports);
				mrp->status.msrpEnabledStatus = true;
				mrp_start_msrp_app(mrp);
				msrp_open_ports(mrp);
			} else {
				mrp_stop_msrp_app(mrp);
				mrp->status.msrpEnabledStatus = false;
			}
			mutex_unlock(&mrp->lock);
		}
		break;
#endif
#ifdef CONFIG_KSZ_AVB
	case PROC_SET_MSRP_SR_A:
	{
#ifdef CONFIG_KSZ_MSRP
		struct srp_domain domain;
		struct mrp_applicant *app;
#endif
		struct mrp_port_info *info;
		u32 delta_a;
		u32 delta_b;
		int q1;
		int q2;
		uint n;
		uint p;
		int join = 0;

		if (!(sw->features & MRP_SUPPORT))
			break;
		if (num && !mrp->domain[1].id) {
			mrp->domain[1].id = SR_CLASS_A;
			join = 2;
		} else if (!num && mrp->domain[1].id) {
			join = 1;
		}
		if (!join)
			break;
		--join;
#ifdef CONFIG_KSZ_MSRP
		domain.class_id = mrp->domain[1].id;
		domain.class_priority = mrp->domain[1].priority;
		domain.class_vid = htons(mrp->domain[1].vlan_id);
		for (n = 0; n <= mrp->ports; n++) {
			p = get_phy_port(sw, n);

			app = rcu_dereference(mrp->mrp_ports[p].applicants[
					      srp_mrp_app.type]);
			if (!app)
				continue;
			if (join)
				msrp_req_join_domain(app, &domain, true);
			else
				msrp_req_leave_domain(app, &domain);
		}
#endif
		if (!join) {
			mrp->domain[1].id = 0;
		}
		for (n = 0; n <= mrp->ports; n++) {
			p = get_phy_port(sw, n);
			info = &mrp->port_info[p];
			q1 = get_queue_priority(mrp, SR_CLASS_A);
			q2 = get_queue_priority(mrp, SR_CLASS_B);
			delta_a = info->bandwidth[q1].deltaBandwidth;
			delta_b = info->bandwidth[q2].deltaBandwidth;
			if (join) {
				if (delta_a > 95)
					delta_a = 95;
				if (delta_a + delta_b > 95)
					delta_b = 95 - delta_a;
			} else {
				delta_b += delta_a;
				delta_a = 0;
				if (delta_b > 95)
					delta_b = 95;
			}
			mrp_set_delta(mrp, p, delta_a, delta_b);
		}
		break;
	}
#endif
	default:
		processed = false;
		break;
	}
	return processed;
}  /* sysfs_mrp_write */

static ssize_t sysfs_mrp_port_read(struct ksz_sw *sw, int proc_num, uint n,
	ssize_t len, char *buf)
{
	struct mrp_info *mrp = &sw->mrp;
#ifdef CONFIG_KSZ_AVB
	struct mrp_port_info *info;
	int index;
	char per_str[20];
#endif
	uint m;
	uint port;
	struct ksz_port_cfg *cfg;
#ifdef CONFIG_KSZ_MRP
	struct mrp_port *mrp_p;
#endif
	int chk = 0;
	int type = SHOW_HELP_NUM;
	char note[40];

	note[0] = '\0';
#ifdef CONFIG_KSZ_MRP
	switch (proc_num) {
	case PROC_SET_PORT_MMRP_ENABLED:
	case PROC_SET_PORT_MMRP_MAC:
	case PROC_SET_PORT_MMRP_SVC:
	case PROC_SET_PORT_MMRP_REG:
	case PROC_SET_PORT_MVRP_ENABLED:
	case PROC_SET_PORT_MVRP_VID:
	case PROC_SET_PORT_MVRP_REG:
		if (!(sw->features & MRP_SUPPORT))
			return 0;
		break;
	}
#endif
	port = get_sysfs_port(sw, n);
	m = BIT(port);
	if (!(mrp->mask & m))
		return 0;
	cfg = get_port_cfg(sw, port);
#ifdef CONFIG_KSZ_MRP
	mrp_p = &mrp->mrp_ports[port];
#endif
#ifdef CONFIG_KSZ_AVB
	index = cfg->q_index;
	info = &mrp->port_info[port];
#endif
	switch (proc_num) {
#ifdef CONFIG_KSZ_MRP
	case PROC_SET_PORT_MMRP_ENABLED:
		chk = !!(mrp->mmrp_rx_ports & m);
		type = SHOW_HELP_ON_OFF;
		break;
	case PROC_SET_PORT_MMRP_MAC:
		chk = 0;
		if (mrp->mmrp_rx_ports & m) {
			struct mrp_applicant *app;

			app = rcu_dereference(mrp_p->
					      applicants[mac_mrp_app.type]);
			chk = !!(app->normal & (1 << MMRP_ATTR_MAC));
		}
		type = SHOW_HELP_ON_OFF;
		break;
	case PROC_SET_PORT_MMRP_SVC:
		chk = 0;
		if (mrp->mmrp_rx_ports & m) {
			struct mrp_applicant *app;

			app = rcu_dereference(mrp_p->
					      applicants[mac_mrp_app.type]);
			chk = !!(app->normal & (1 << MMRP_ATTR_SVC));
		}
		type = SHOW_HELP_ON_OFF;
		break;
	case PROC_SET_PORT_MMRP_REG:
		if (mrp->mmrp_rx_ports & m) {
			struct mrp_applicant *app;
			struct mrp_attr *attr;
			char *str;
			struct ksz_mac_table *entry;

			entry = &sw->info->mac_entry;
			app = rcu_dereference(mrp_p->
					      applicants[mac_mrp_app.type]);
			attr = mrp_attr_lookup(app, entry->addr, ETH_ALEN,
					MMRP_ATTR_MAC);
			str = "unregistered";
			if (attr) {
				if (attr->fix_state != MRP_REGISTRAR_LV) {
					if (attr->fix_state == MRP_REGISTRAR_IN)
						str = "fixed";
					else
						str = "forbidden";
				} else if (attr->reg_state == MRP_REGISTRAR_IN)
					str = "registered";
			}
			len += sprintf(buf + len,
				"%s"NL, str);
		}
		type = SHOW_HELP_NONE;
		break;
	case PROC_SET_PORT_MVRP_ENABLED:
		chk = !!(mrp->mvrp_rx_ports & m);
		type = SHOW_HELP_ON_OFF;
		break;
	case PROC_SET_PORT_MVRP_VID:
		chk = 0;
		if (mrp->mvrp_rx_ports & m) {
			struct mrp_applicant *app;

			app = rcu_dereference(mrp_p->
					      applicants[vlan_mrp_app.type]);
			chk = !!(app->normal & (1 << MVRP_ATTR_VID));
		}
		type = SHOW_HELP_ON_OFF;
		break;
	case PROC_SET_PORT_MVRP_REG:
		if (mrp->mvrp_rx_ports & m) {
			struct mrp_applicant *app;
			struct mrp_attr *attr;
			char *str;
			__be16 vlan_id = htons(sw->vlan_index);

			app = rcu_dereference(mrp_p->
					      applicants[vlan_mrp_app.type]);
			attr = mrp_attr_lookup(app, &vlan_id, sizeof(vlan_id),
					MVRP_ATTR_VID);
			str = "unregistered";
			if (attr) {
				if (attr->fix_state != MRP_REGISTRAR_LV) {
					if (attr->fix_state == MRP_REGISTRAR_IN)
						str = "fixed";
					else
						str = "forbidden";
				} else if (attr->reg_state == MRP_REGISTRAR_IN)
					str = "registered";
			}
			len += sprintf(buf + len,
				"%s"NL, str);
		}
		type = SHOW_HELP_NONE;
		break;
#endif
#ifdef CONFIG_KSZ_MSRP
	case PROC_SET_PORT_MSRP_ENABLED:
		chk = info->status.msrpPortEnabledStatus;
		type = SHOW_HELP_ON_OFF;
		break;
#endif
#ifdef CONFIG_KSZ_AVB
	case PROC_SET_PORT_ASCAPABLE:
		chk = cfg->asCapable;
		if (!chk && cfg->asCapable_set)
			chk = 2;
		break;
	case PROC_SET_TC_DELTA_BANDWIDTH:
		chk = info->bandwidth[index].deltaBandwidth;
		break;
	case PROC_SET_TC_ADMIN_IDLE_MBPS:
	{
		u64 val = info->bandwidth[index].adminIdleSlope;

		val *= 10;
		val *= info->speed;
		val += 1 << (CREDIT_PERCENTAGE_S - 1);
		val >>= CREDIT_PERCENTAGE_S;
		chk = (u32)val;
		if (chk >= 1000)
			len += sprintf(buf + len,
				"%u,%03u Kbps"NL, chk / 1000, chk % 1000);
		else
			len += sprintf(buf + len,
				"%u Kbps"NL, chk);
		type = SHOW_HELP_NONE;
		break;
	}
	case PROC_SET_TC_ADMIN_IDLE_SLOPE:
		format_per(per_str, info->bandwidth[index].adminIdleSlope,
			   sw->verbose);
		len += sprintf(buf + len,
			"%s"NL, per_str);
		type = SHOW_HELP_NONE;
		break;
	case PROC_GET_TC_OPER_IDLE_SLOPE:
		format_per(per_str, info->bandwidth[index].operIdleSlope,
			   sw->verbose);
		len += sprintf(buf + len,
			"%s"NL, per_str);
		type = SHOW_HELP_NONE;
		break;
	case PROC_SET_TC_ALGORITHM:
		chk = info->algorithm[index].algorithm;
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
	case PROC_GET_SR_B_RX_PRIO:
		chk = info->priority[SR_CLASS_B].received_priority;
		break;
	case PROC_SET_SR_B_TX_PRIO:
		chk = info->priority[SR_CLASS_B].regenerated_priority;
		break;
	case PROC_GET_SR_B_SRP_DOMAIN_BOUNDARY:
		chk = info->priority[SR_CLASS_B].SRPdomainBoundaryPort;
		break;
	case PROC_SET_SR_B_LATENCY:
		index = get_traffic_index(SR_CLASS_B);
		chk = info->latency[index].portTcMaxLatency;
		break;
	case PROC_GET_SR_A_RX_PRIO:
		chk = info->priority[SR_CLASS_A].received_priority;
		break;
	case PROC_SET_SR_A_TX_PRIO:
		chk = info->priority[SR_CLASS_A].regenerated_priority;
		break;
	case PROC_GET_SR_A_SRP_DOMAIN_BOUNDARY:
		chk = info->priority[SR_CLASS_A].SRPdomainBoundaryPort;
		break;
	case PROC_SET_SR_A_LATENCY:
		index = get_traffic_index(SR_CLASS_A);
		chk = info->latency[index].portTcMaxLatency;
		break;
	case PROC_SET_MAX_FRAME_SIZE:
		chk = info->max_frame_size;
		break;
	case PROC_SET_MAX_INTERVAL_FRAMES:
		chk = info->max_interval_frames;
		break;
	case PROC_SET_CLASS_PRIO:
		type = SHOW_HELP_NONE;
		break;
#endif
	default:
		type = SHOW_HELP_NONE;
		break;
	}
	return sysfs_show(len, buf, type, chk, note, sw->verbose);
}  /* sysfs_mrp_port_read */

static int sysfs_mrp_port_write(struct ksz_sw *sw, int proc_num, uint n,
	int num, const char *buf)
{
	struct mrp_info *mrp = &sw->mrp;
#ifdef CONFIG_KSZ_AVB
	struct mrp_port_info *info;
	int index;
#endif
	uint m;
	uint port;
	struct ksz_port_cfg *cfg;
#ifdef CONFIG_KSZ_MRP
	struct mrp_port *mrp_p;
#endif
	int processed = true;

#ifdef CONFIG_LAN937X_MRP
	switch (proc_num) {
	case PROC_SET_PORT_MMRP_ENABLED:
	case PROC_SET_PORT_MMRP_MAC:
	case PROC_SET_PORT_MMRP_SVC:
	case PROC_SET_PORT_MMRP_REG:
	case PROC_SET_PORT_MVRP_ENABLED:
	case PROC_SET_PORT_MVRP_VID:
	case PROC_SET_PORT_MVRP_REG:
		if (!(sw->features & MRP_SUPPORT))
			return true;
		break;
	}
#endif
	port = get_sysfs_port(sw, n);
	m = BIT(port);
	if (!(mrp->mask & m))
		return false;
	cfg = get_port_cfg(sw, port);
#ifdef CONFIG_KSZ_MRP
	mrp_p = &mrp->mrp_ports[port];
#endif
#ifdef CONFIG_KSZ_AVB
	index = cfg->q_index;
	info = &mrp->port_info[port];
#endif
	switch (proc_num) {
#ifdef CONFIG_KSZ_MRP
	case PROC_SET_PORT_MMRP_ENABLED:
		if (!!(mrp->mmrp_rx_ports & m) != !!num) {
			if (num) {
				mrp->mmrp_rx_ports |= m;
				mrp->mmrp_tx_ports |= m;
				mrp_start_mmrp_port_app(mrp, port,
							sw->main_dev);
			} else {
				mrp->mmrp_rx_ports &= ~m;
				mrp_stop_port_app(mrp_p,
						  &mac_mrp_app, 0, true);
			}
		}
		break;
	case PROC_SET_PORT_MMRP_MAC:
		if (mrp->mvrp_rx_ports & m) {
			int on;
			struct mrp_applicant *app;

			app = rcu_dereference(mrp_p->
					      applicants[mac_mrp_app.type]);
			on = !!(app->normal & (1 << MMRP_ATTR_MAC));
			if (on != !!num) {
				if (num) {
					app->normal |= (1 << MMRP_ATTR_MAC);
				} else {
					app->normal &= ~(1 << MMRP_ATTR_MAC);
					mrp_stop_port_app(mrp_p,
							  &mac_mrp_app,
							  MMRP_ATTR_MAC, false);
				}
			}
		}
		break;
	case PROC_SET_PORT_MMRP_SVC:
		if (mrp->mvrp_rx_ports & m) {
			int on;
			struct mrp_applicant *app;

			app = rcu_dereference(mrp_p->
					      applicants[mac_mrp_app.type]);
			on = !!(app->normal & (1 << MMRP_ATTR_SVC));
			if (on != !!num) {
				if (num) {
					app->normal |= (1 << MMRP_ATTR_SVC);
				} else {
					app->normal &= ~(1 << MMRP_ATTR_SVC);
					mrp_stop_port_app(mrp_p,
							  &mac_mrp_app,
							  MMRP_ATTR_SVC, false);
				}
			}
		}
		break;
	case PROC_SET_PORT_MMRP_REG:
		if (mrp->mmrp_rx_ports & m) {
			struct mrp_applicant *app;
			enum mrp_registrar_state state;
			struct ksz_mac_table *entry;

			entry = &sw->info->mac_entry;
			if (num == 2)
				state = MRP_REGISTRAR_MT;
			else if (num == 1)
				state = MRP_REGISTRAR_IN;
			else
				state = MRP_REGISTRAR_LV;
			app = rcu_dereference(mrp_p->
					      applicants[mac_mrp_app.type]);
			mmrp_req_set_mac(app, entry->addr, state);
		}
		break;
	case PROC_SET_PORT_MVRP_ENABLED:
		if (!!(mrp->mvrp_rx_ports & m) != !!num) {
			if (num) {
				mrp->mvrp_rx_ports |= m;
				mrp->mvrp_tx_ports |= m;
				mrp_start_mvrp_port_app(mrp, port,
							sw->main_dev);
			} else {
				mrp->mvrp_rx_ports &= ~m;
				mrp_stop_port_app(mrp_p,
						  &vlan_mrp_app, 0, true);
			}
		}
		break;
	case PROC_SET_PORT_MVRP_VID:
		if (mrp->mvrp_rx_ports & m) {
			int on;
			struct mrp_applicant *app;

			app = rcu_dereference(mrp_p->
					      applicants[vlan_mrp_app.type]);
			on = !!(app->normal & (1 << MVRP_ATTR_VID));
			if (on != !!num) {
				if (num) {
					app->normal |= (1 << MVRP_ATTR_VID);
				} else {
					app->normal &= ~(1 << MVRP_ATTR_VID);
					mrp_stop_port_app(mrp_p,
							  &vlan_mrp_app,
							  MVRP_ATTR_VID, false);
				}
			}
		}
		break;
	case PROC_SET_PORT_MVRP_REG:
		if (mrp->mvrp_rx_ports & m) {
			struct mrp_applicant *app;
			enum mrp_registrar_state state;

			if (num == 2)
				state = MRP_REGISTRAR_MT;
			else if (num == 1)
				state = MRP_REGISTRAR_IN;
			else
				state = MRP_REGISTRAR_LV;
			app = rcu_dereference(mrp_p->
					      applicants[vlan_mrp_app.type]);
			mvrp_req_set(app, sw->vlan_index, state);
		}
		break;
#endif
#ifdef CONFIG_KSZ_MSRP
	case PROC_SET_PORT_MSRP_ENABLED:
	{
		if (!(sw->features & AVB_SUPPORT))
			break;
		if (info->status.msrpPortEnabledStatus == !!num)
			break;

		if (!info->status.msrpPortEnabledStatus) {
			uint l = get_log_port(sw, port);

			mutex_lock(&mrp->lock);
			mrp_reset_reserv(mrp, l, l);
			info->status.msrpPortEnabledStatus = true;
			mrp_start_msrp_port_app(mrp, port, sw->main_dev);
			msrp_open_port(mrp, port);
			mutex_unlock(&mrp->lock);
			mrp_chk_registered(mrp, port);
		} else {
			mutex_lock(&mrp->lock);
			mrp_stop_port_app(mrp_p,
					  &srp_mrp_app, 0, true);
			info->status.msrpPortEnabledStatus = false;
			mutex_unlock(&mrp->lock);
		}
		break;
	}
#endif
#ifdef CONFIG_KSZ_AVB
	case PROC_SET_PORT_ASCAPABLE:
		if (!(sw->features & AVB_SUPPORT))
			break;
		cfg->asCapable_set = !!num;
		if (sw->features & MRP_SUPPORT)
			break;
		break;
	case PROC_SET_TC_DELTA_BANDWIDTH:
		if (index == mrp->queue[SR_CLASS_B] && num >= 0 &&
		    num + info->deltaBandwidth <= 95 &&
		    num + info->deltaBandwidth > 0)
			mrp_set_delta(mrp, port, info->deltaBandwidth, num);
		if (index == mrp->queue[SR_CLASS_A] && num >= 0 && num <= 95)
			info->deltaBandwidth = num;
		break;
	case PROC_SET_TC_ADMIN_IDLE_MBPS:
		if (!info->speed)
			break;
		if (num >= info->speed * 1000)
			num = (info->speed * 1000) - 1;
		num *= 100;
		num /= info->speed;
	case PROC_SET_TC_ADMIN_IDLE_SLOPE:
		if (num >= 0 && num < 100000) {
			mrp_set_slope(mrp, port, index, info, num);
		}
		break;
	case PROC_SET_TC_ALGORITHM:
		if (0 <= num && num < 2)
			info->algorithm[index].algorithm = num;
		else if (3 == num)
			info->algorithm[index].algorithm = num;

#if defined(CONFIG_HAVE_KSZ9897) || defined(CONFIG_HAVE_LAN937X)
		sw->reg->lock(sw);
		if (0 == num || 1 == num) {
			port_set_schedule_mode(sw, port, index,
				MTI_SCHEDULE_STRICT_PRIO);
			port_set_shaping(sw, port, index,
				1 == num ? MTI_SHAPING_SRP : MTI_SHAPING_OFF);
		} else if (3 == num) {
			port_set_schedule_mode(sw, port, index,
				MTI_SCHEDULE_WRR);
			port_set_shaping(sw, port, index,
				MTI_SHAPING_OFF);
		}
		sw->reg->unlock(sw);
#endif
		break;
	case PROC_SET_SR_B_TX_PRIO:
		if (0 <= num && num < 8)
			info->priority[SR_CLASS_B].regenerated_priority = num;
		break;
	case PROC_SET_SR_B_LATENCY:
		index = get_traffic_index(SR_CLASS_B);
		if (0 <= num && num < 100000)
			info->latency[index].portTcMaxLatency = num;
		break;
	case PROC_SET_SR_A_TX_PRIO:
		if (0 <= num && num < 8)
			info->priority[SR_CLASS_A].regenerated_priority = num;
		break;
	case PROC_SET_SR_A_LATENCY:
		index = get_traffic_index(SR_CLASS_A);
		if (0 <= num && num < 100000)
			info->latency[index].portTcMaxLatency = num;
		break;
	case PROC_SET_MAX_FRAME_SIZE:
		if (num < 46)
			num = 46;
		info->max_frame_size = num;
		break;
	case PROC_SET_MAX_INTERVAL_FRAMES:
		if (num < 1)
			num = 1;
		info->max_interval_frames = num;
		break;
	case PROC_SET_CLASS_PRIO:
		if (0 <= num && num <= 7) {
			u32 cnt;

			cnt = 0;
			if (num == 2)
				cnt = 4000;
			else if (num == 3)
				cnt = 8000;
			if (cnt && info->speed) {
				u32 queue = cfg->tc_map[0];
				u32 overhead;
				u32 rate;
				u16 data;

				queue >>= num * PORT_TC_MAP_S;
				queue &= PORT_TC_MAP_M;
				overhead = 22;
				sw->ops->acquire(sw);
				data = sw->reg->r16(sw, REG_AVB_STRATEGY__2);
				sw->ops->release(sw);
				if (data & SW_SHAPING_CREDIT_ACCT)
					overhead += 20;
				rate = info->max_frame_size;
				rate += overhead;
				rate *= info->max_interval_frames;
				rate *= cnt;
				rate *= 8;
				rate /= 1000;
				if (rate >= info->speed * 1000)
					rate = (info->speed * 1000) - 1;
				rate *= 100;
				rate /= info->speed;
				mrp_set_slope(mrp, port, queue, info, rate);
			}
		}
		break;
#endif
	default:
		processed = false;
		break;
	}
	return processed;
}  /* sysfs_mrp_port_write */

#ifdef CONFIG_KSZ_MRP
static void leave_mrp(struct mrp_info *mrp)
{
}  /* leave_mrp */
#endif

static void mrp_init(struct mrp_info *mrp)
{
	struct ksz_sw *sw = mrp->parent;

#ifdef CONFIG_KSZ_AVB
	struct mrp_traffic_info *traffic;
	struct mrp_port_info *info;
	char bw_str1[20];
	char bw_str2[20];
	char bw_str3[20];
	char bw_str4[20];
	char bw_str5[20];
	uint port;
	int index;
	int tc;
#endif

	mrp->access = create_singlethread_workqueue("mrp_access");
	init_mrp_work(mrp);
	mutex_init(&mrp->lock);
	skb_queue_head_init(&mrp->rxq);
	skb_queue_head_init(&mrp->macq);
	skb_queue_head_init(&mrp->vlanq);
#ifdef CONFIG_KSZ_MSRP
	INIT_WORK(&mrp->cfg_mac, mrp_cfg_mac_work);
#endif
#ifdef CONFIG_KSZ_MRP
	INIT_WORK(&mrp->cfg_vlan, mrp_cfg_vlan_work);
	INIT_WORK(&mrp->rx_proc, mrp_rx_proc);
#endif

	/* Number of ports can be capped for testing purpose. */
	mrp->ports = sw->mib_port_cnt;
	mrp->mask = sw->PORT_MASK;
	mrp->other = sw->PORT_MASK & ~sw->HOST_MASK;
	mrp->mmrp_rx_ports = mrp->mmrp_tx_ports = mrp->mask;
	mrp->mvrp_rx_ports = mrp->mvrp_tx_ports = mrp->mask;

#ifdef CONFIG_KSZ_MRP
	mrp_init_list(&mrp->mac_list);
	mrp_init_list(&mrp->vlan_list);
#endif

#ifdef CONFIG_KSZ_AVB
	mrp->id = sw->ops->get_br_id(sw);
	mrp->tc[2] = SR_CLASS_B;
	mrp->tc[3] = SR_CLASS_A;
	mrp->prio[SR_CLASS_B] = 2;
	mrp->prio[SR_CLASS_A] = 3;
	mrp->queue[SR_CLASS_B] = 2;
	mrp->queue[SR_CLASS_A] = 3;
	mrp->domain[0].id = SR_CLASS_B;
	mrp->domain[0].priority = mrp->prio[SR_CLASS_B];
	mrp->domain[0].vlan_id = 2;
	mrp->domain[1].id = SR_CLASS_A;
#if 0
	mrp->domain[1].id = 0;
#endif
	mrp->domain[1].priority = mrp->prio[SR_CLASS_A];
	mrp->domain[1].vlan_id = 2;
	mrp->max_interference_size = 1500;

#ifdef CONFIG_KSZ_MSRP
	mrp_init_list(&mrp->mac_down);
	mrp_init_list(&mrp->mac_up);
	mrp_init_list(&mrp->vlan_down);
	mrp_init_list(&mrp->vlan_up);
#endif

	for (port = 0; port < sw->port_cnt; port++) {
		info = &mrp->port_info[port];
		info->index = port;
		info->max_frame_size = 46;
		info->max_interval_frames = 1;
#ifdef CONFIG_KSZ_MSRP
		if (mrp->status.msrpEnabledStatus)
			info->status.msrpPortEnabledStatus = true;
#endif
		info->speed = 100;
		if (sw->port_info[port].tx_rate)
			info->speed = sw->port_info[port].tx_rate /
				TX_RATE_UNIT;

		tc = mrp->queue[SR_CLASS_A];
		info->bandwidth[tc].deltaBandwidth = 50;
#if 0
		info->bandwidth[tc].deltaBandwidth = 75;
#endif
		info->bandwidth[tc].adminIdleSlope = 75 << CREDIT_PERCENTAGE_S;
		info->bandwidth[tc].operIdleSlope =
			info->bandwidth[tc].adminIdleSlope;
		info->deltaBandwidth = info->bandwidth[tc].deltaBandwidth;

		tc = mrp->queue[SR_CLASS_B];
		info->bandwidth[tc].deltaBandwidth = 25;
#if 0
		info->bandwidth[tc].deltaBandwidth = 0;
#endif
		info->bandwidth[tc].adminIdleSlope = 75 << CREDIT_PERCENTAGE_S;
		info->bandwidth[tc].operIdleSlope =
			info->bandwidth[tc].adminIdleSlope;

		tc = 0;
		info->bandwidth[tc].deltaBandwidth = 0;
		info->bandwidth[tc].adminIdleSlope = 75 << CREDIT_PERCENTAGE_S;
		info->bandwidth[tc].operIdleSlope =
			info->bandwidth[tc].adminIdleSlope;

		for (tc = 0; tc < PRIO_QUEUES; tc++) {
			info->bandwidth[tc].traffic_class = tc;
			info->algorithm[tc].traffic_class = tc;
		}
		for (tc = 0; tc < PRIO_QUEUES - 2; tc++)
			info->algorithm[tc].algorithm = 3;
		for (; tc < PRIO_QUEUES; tc++)
			info->algorithm[tc].algorithm = 1;

		for (tc = SR_CLASS_A; tc >= SR_CLASS_B; tc--) {
			index = get_traffic_index(tc);
			info->latency[index].traffic_class = tc;
			info->latency[index].portTcMaxLatency = 1000;
			if (tc == SR_CLASS_A)
				info->latency[index].portTcMaxLatency = 50000;
			if (tc == SR_CLASS_B)
				info->latency[index].portTcMaxLatency = 50000;

			info->priority[tc].received_priority =
				mrp->prio[tc];
			info->priority[tc].regenerated_priority = 0;
			if (port != sw->HOST_PORT)
				info->priority[tc].SRPdomainBoundaryPort = 1;

			traffic = get_traffic_info(info, tc);
			traffic->queue = get_queue_priority(mrp, tc);

#ifdef CONFIG_KSZ_MSRP
			mrp_init_list(&traffic->active);
			mrp_init_list(&traffic->passive);
#endif
		}
		info->traffic[1].bandwidth_avail =
			&info->traffic[0].bandwidth_delta;
		info->traffic[1].bandwidth_other =
			&info->traffic[0].bandwidth_max;
		info->traffic[0].bandwidth_avail = NULL;
		info->traffic[0].bandwidth_other = NULL;
		mrp_set_bandwidth(info);

		format_num(bw_str1, info->bandwidth_left);
		format_num(bw_str2, info->traffic[1].bandwidth_max);
		format_num(bw_str3, info->traffic[1].bandwidth_left);
		format_num(bw_str4, info->traffic[0].bandwidth_max);
		format_num(bw_str5, info->traffic[0].bandwidth_left);
if (port < 2)
dbg_msg("bw: %d %s; %s %s; %s %s"NL, port,
bw_str1, bw_str2, bw_str3, bw_str4, bw_str5);
	}
#endif
dbg_msg("%s %x %x"NL, __func__, SRP_PORT_AVAIL, SRP_PORT_OTHER);
}  /* mrp_init */

static void mrp_exit(struct mrp_info *mrp)
{
	bool last;
	struct sk_buff *skb;

	last = skb_queue_empty(&mrp->rxq);
	while (!last) {
		skb = skb_dequeue(&mrp->rxq);
		if (skb)
			kfree_skb(skb);
		last = skb_queue_empty(&mrp->rxq);
	}
	last = skb_queue_empty(&mrp->macq);
	while (!last) {
		skb = skb_dequeue(&mrp->macq);
		if (skb)
			kfree_skb(skb);
		last = skb_queue_empty(&mrp->macq);
	}
	last = skb_queue_empty(&mrp->vlanq);
	while (!last) {
		skb = skb_dequeue(&mrp->vlanq);
		if (skb)
			kfree_skb(skb);
		last = skb_queue_empty(&mrp->vlanq);
	}
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

#ifdef CONFIG_KSZ_MRP
	.from_backup		= mrp_from_backup,
	.to_backup		= mrp_to_backup,
	.from_designated	= mrp_from_designated,
	.to_designated		= mrp_to_designated,
	.tc_detected		= mrp_tc_detected,

#ifdef CONFIG_KSZ_MSRP
	.chk_talker		= mrp_chk_talker,
#endif
	.setup_vlan		= mrp_setup_vlan,
#endif
};

