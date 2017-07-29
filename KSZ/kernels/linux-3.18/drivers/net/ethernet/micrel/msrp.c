/*
 *	IEEE 802.1Qat Multiple Stream Registration Protocol (MSRP)
 *
 *	Copyright (c) 2016 Microchip Technology Inc.
 *
 *	Copyright (c) 2012 Massachusetts Institute of Technology
 *
 *	Adapted from code in net/8021q/vlan_gvrp.c
 *	Copyright (c) 2008 Patrick McHardy <kaber@trash.net>
 *
 *	This program is free software; you can redistribute it and/or
 *	modify it under the terms of the GNU General Public License
 *	version 2 as published by the Free Software Foundation.
 */


#ifndef ETH_P_MSRP
#define ETH_P_MSRP		0x22EA
#endif


#define MRP_MSRP_ADDRESS	{ 0x01, 0x80, 0xc2, 0x00, 0x00, 0x0E }

enum msrp_attributes {
	MSRP_ATTR_INVALID,

	/* Used in PDU but not in storage. */
	MSRP_ATTR_TALKER,
	MSRP_ATTR_TALKER_FAILED,
	MSRP_ATTR_LISTENER,
	MSRP_ATTR_DOMAIN,
	__MSRP_ATTR_MAX
};
#define MSRP_ATTR_MAX	(__MSRP_ATTR_MAX - 1)

enum msrp_listener_attributes {
	MSRP_LISTENER_IGNORE,
	MSRP_LISTENER_ASKFAILED,
	MSRP_LISTENER_READY,
	MSRP_LISTENER_READYFAIL,
};

/* Attribute length is 25. */
struct srp_talker {
	u8 id[8];
	u8 dest[ETH_ALEN];
	u16 vlan_id;
	u16 max_frame_size;
	u16 max_interval_frames;
	u8 reserved:4;
	u8 rank:1;
	u8 priority:3;
	u32 accumulated_latency;
} __packed;

/* Attribute length is 34. */
struct srp_talker_failed {
	u8 id[8];
	u8 dest[ETH_ALEN];
	u16 vlan_id;
	u16 max_frame_size;
	u16 max_interval_frames;
	u8 reserved:4;
	u8 rank:1;
	u8 priority:3;
	u32 accumulated_latency;
	u8 bridge_id[8];
	u8 failure_code;
} __packed;

/* Attribute length is 8. */
struct srp_listener {
	u8 id[8];
	u8 substate;
	u8 nextval;
} __packed;

/* Attribute length is 4. */
struct srp_domain {
	u8 class_id;
	u8 class_priority;
	u16 class_vid;
} __packed;


static struct mrp_application srp_mrp_app __read_mostly = {
	.type		= MRP_APPLICATION_MSRP,
	.maxattr	= MSRP_ATTR_MAX,
	.pkttype.type	= htons(ETH_P_MSRP),
	.group_address	= MRP_MSRP_ADDRESS,
	.version	= 0,
};

static void msrp_attrvalue_inc(void *value, u8 len)
{
	if (sizeof(struct srp_talker) == len ||
	    sizeof(struct srp_talker_failed) == len) {
		u8 dest_len;
		struct srp_talker *talker = value;

		len = 8;
		dest_len = 6;
		while (len > 0 && !++talker->id[--len])
			;
		while (dest_len > 0 && !++talker->dest[--dest_len])
			;
	} else if (sizeof(struct srp_listener) == len) {
		struct srp_listener *listener = value;

		len = 8;
		while (len > 0 && !++listener->id[--len])
			;
	} else if (sizeof(struct srp_domain) == len) {
		struct srp_domain *domain = value;

		domain->class_id++;
		domain->class_priority++;
	}
else
dbg_msg(" %s ?\n", __func__);
}

static int msrp_attrvalue_cmp(const void *value, const void *attr, u8 len)
{
	if (sizeof(struct srp_talker) == len ||
	    sizeof(struct srp_talker_failed) == len)
		return memcmp(value, attr, 8 + 6);
	else if (sizeof(struct srp_listener) == len)
		return memcmp(value, attr, 8);
	else if (sizeof(struct srp_domain) == len)
		return memcmp(value, attr, 2);
	return 0;
}

static int msrp_attr_cmp(const struct mrp_attr *attr,
			 const void *value, u8 len, u8 type)
{
	if (MSRP_ATTR_TALKER == type && 25 == len) {
		type = MSRP_ATTR_TALKER_FAILED;
		len = 34;
	}
	if (attr->type != type)
		return attr->type - type;
	if (attr->len != len)
		return attr->len - len;
	return msrp_attrvalue_cmp(attr->value, value, len);
}

static int msrp_attr_chk(u8 attrtype, u8 attrlen)
{
	if ((MSRP_ATTR_LISTENER == attrtype &&
	    sizeof(struct srp_listener) - 2 == attrlen) ||
	    (MSRP_ATTR_TALKER == attrtype &&
	    sizeof(struct srp_talker) == attrlen) ||
	    (MSRP_ATTR_TALKER_FAILED == attrtype &&
	    sizeof(struct srp_talker_failed) == attrlen) ||
	    (MSRP_ATTR_DOMAIN == attrtype &&
	    sizeof(struct srp_domain) == attrlen))
		return 0;
	return -1;
}

static u8 msrp_attr_len(u8 attrtype, u8 attrlen)
{
	if (MSRP_ATTR_LISTENER == attrtype)
		return 8;
	if (MSRP_ATTR_TALKER == attrtype)
		return 8;
	if (MSRP_ATTR_TALKER_FAILED == attrtype)
		return 8;
	if (MSRP_ATTR_DOMAIN == attrtype)
		return 1;
	return attrlen;
}

static u8 msrp_attr_type(struct mrp_attr *attr)
{
	u8 type = attr->type;

	if (MSRP_ATTR_TALKER_FAILED == attr->type) {
		struct srp_talker_failed *talker =
			(struct srp_talker_failed *) attr->value;

		if (!talker->failure_code)
			type = MSRP_ATTR_TALKER;
	}
	return type;
}

static void msrp_attr_upd(const void *value, struct mrp_attr *attr)
{
	const u8 *data = value;

	/* Update talker failure code. */
	if (MSRP_ATTR_TALKER_FAILED == attr->type)
		memcpy(&attr->value[25], &data[25], 34 - 25);

	/* Update listener substate. */
	else if (MSRP_ATTR_LISTENER == attr->type)
		attr->value[8] = data[8];
}

static int chk_listen_id(u8 *first, u8 *next)
{
	if (!memcmp(first, next, 6) && (first[6] < next[6] ||
	    (first[6] == next[6] && first[7] <= next[7]))) {
		int diff;

		diff = next[6];
		diff -= first[6];
		diff <<= 8;
		diff |= next[7];
		diff -= first[7];
		return diff;
	} else
		return 0x10000;
}

static int find_used_space(int cnt, int left, int cnt_per_byte)
{
	int num;

	num = cnt - left;
	num += (cnt_per_byte - 1);
	num /= cnt_per_byte;
	return num;
}

static int find_largest_cnt(int cnt)
{
	int num;
	int attr_cnt;
	int decl_cnt;
	int attr_left;
	int decl_left;

	num = 21;
	attr_left = (3 - (cnt % 3)) % 3;
	decl_left = (4 - (cnt % 4)) % 4;
	do {
		--num;
		attr_cnt = find_used_space(num, attr_left, 3);
		decl_cnt = find_used_space(num, decl_left, 4);
#ifdef DBG_MRP
dbg_msg(" f: c=%d a=%d d=%d n=%d %d\n",
cnt, attr_left, decl_left, num, attr_cnt + decl_cnt);
#endif
	} while (attr_cnt + decl_cnt > 11);
	return num;
}

static void msrp_prepare_tx(struct mrp_applicant *app, u8 attrtype,
	int firstval_max)
{
	u8 firstval[40];
	int firstval_cnt = 0;
	int firstval_opt = 0;
	int listen_cnt = 0;
	struct rb_node *node, *next;
	struct rb_node *opt = NULL;
	struct mrp_attr *attr;
	struct mrp_attr *first = NULL;
	struct mrp_attr dummy;
	struct mrp_attr *last = &dummy;
	enum mrp_tx_action last_action = MRP_TX_ACTION_NONE;
	u8 attr_type = attrtype;
	u8 attr_len;
	struct srp_listener *listener;

	/* MSRP_ATTR_TALKER_FAILED type is used internally in storage. */
	if (MSRP_ATTR_TALKER == attrtype)
		attr_type = MSRP_ATTR_TALKER_FAILED;
	memset(firstval, 0, sizeof(firstval));
	for (node = rb_first(&app->mad);
	     next = node ? rb_next(node) : NULL, node != NULL;
	     node = next) {
		attr = rb_entry(node, struct mrp_attr, node);
		if (attr_type != attr->type)
			continue;
		attr_len = attr->len;
		if (MSRP_ATTR_TALKER_FAILED == attr_type) {
			struct srp_talker_failed *talker =
				(struct srp_talker_failed *) attr->value;

			if ((MSRP_ATTR_TALKER == attrtype &&
			    talker->failure_code) ||
			    (MSRP_ATTR_TALKER_FAILED == attrtype &&
			    !talker->failure_code))
				continue;
		}

		/* Used only for listener. */
		listener = NULL;
		if (MSRP_ATTR_LISTENER == attr_type) {
			listener = (struct srp_listener *) attr->value;

			/* Actual attribute length. */
			attr_len = 8;
			listener->nextval = 0;
		}
		if (MRP_TX_ACTION_NONE == attr->action)
{
dbg_msg(" no send\n");
			continue;
}

		/* At least one attribute that is trying to send something. */
		if (last) {
			last = attr;
			last_action = attr->action;
		}
		if (firstval_cnt) {
			int firstval_next = 1;
			int diff = 0;

			if (MSRP_ATTR_LISTENER == attrtype)
				diff = chk_listen_id(firstval, attr->value);

			app->attrval_inc(firstval, attr->len);
			if (memcmp(firstval, attr->value, attr_len))
				firstval_next = 0;

			if (MSRP_ATTR_LISTENER == attrtype) {
				if (!firstval_next) {
					int max;

					max = find_largest_cnt(listen_cnt);
					if (diff <= max) {
						listen_cnt += diff;
						listener->nextval = diff - 1;
						opt = NULL;
						firstval_opt = 0;
						first = attr;
						memcpy(firstval, attr->value,
							attr_len);
						firstval_cnt = 1;
						continue;
					}
				} else
					++listen_cnt;
			}
			if (!firstval_next)
				first = NULL;
			else {
				++firstval_cnt;
				if (MRP_TX_ACTION_S_JOIN_IN_OPTIONAL ==
				    attr->action ||
				    MRP_TX_ACTION_S_IN_OPTIONAL ==
				    attr->action) {
					if (!opt) {
						opt = node;
						firstval_opt = firstval_cnt % 3;
						if (!firstval_opt)
							firstval_opt = 3;
					} else
						++firstval_opt;
					if (firstval_opt >= firstval_max)
						first = NULL;
				} else {
					opt = NULL;
					firstval_opt = 0;
				}
			}
		}
		if (!first) {
			while (firstval_opt) {
				first = rb_entry(opt, struct mrp_attr, node);
				first->action = MRP_TX_ACTION_NONE;
				opt = rb_next(opt);
				--firstval_opt;
			}
			opt = NULL;
			firstval_opt = 0;
			if (MRP_TX_ACTION_S_JOIN_IN_OPTIONAL == attr->action ||
			    MRP_TX_ACTION_S_IN_OPTIONAL == attr->action) {
				attr->action = MRP_TX_ACTION_NONE;
				continue;
			}
			first = attr;
			memcpy(firstval, attr->value, attr_len);
			firstval_cnt = 1;
			if (MSRP_ATTR_LISTENER == attrtype)
				listen_cnt = 1;

			/* There is at least one attribute sending. */
			last = NULL;
		}
	}

	/* Need to send at least one for LeaveAll. */
	if ((app->lva.tx & (1 << (attrtype - 1))) && last &&
	    MRP_TX_ACTION_NONE == last->action)
		last->action = last_action;
}

/* attrlist + mrp_vecattr_hdr + attrlen + vaevents + 4 endmarks */
#define MSRP_MIN			(2 + 2 + 1 + 4)

#define MSRP_TALKER_MIN			(25 + MRP_MIN)
#define MSRP_TALKER_FAILED_MIN		(34 + MRP_MIN)
#define MSRP_LISTENER_MIN		(9 + MRP_MIN)
#define MSRP_DOMAIN_MIN			(4 + MRP_MIN)

#define MSRP_TALKER_OPT_MAX		MRP_OPT_MAX(25)
#define MSRP_TALKER_FAILED_OPT_MAX	MRP_OPT_MAX(34)
#define MSRP_DOMAIN_OPT_MAX		MRP_OPT_MAX(4)
#define MSRP_LISTENER_OPT_MAX		\
	((((2 + 8) + 2) * 2 - (2 + 8)) / 2 * 3)

static int msrp_tx(struct mrp_applicant *app, u8 *msg_buf, u8 *msg_eof,
	int *bytes, u8 attrtype, u8 attrlen, u8 attrmax, u8 msg_min)
{
	struct rb_node *node, *next;
	struct mrp_attr *attr;
	struct mrp_msg_hdr *mh;
	struct mrp_vecattr_hdr *vah;
	u8 firstval[40];
	u8 vectevt[3];
	int i = 0;
	int len = 0;
	int num_break = false;
	int node_break = false;
	u8 *msg_ptr = msg_buf;
	u16 *attr_list;
	u8 attr_type = attrtype;
	int nextval;
	u8 *list_decl;

	/* MSRP_ATTR_TALKER_FAILED type is used internally in storage. */
	if (MSRP_ATTR_TALKER == attrtype)
		attr_type = MSRP_ATTR_TALKER_FAILED;
	*bytes = 0;

	/* Check if previous attribute types are all sent. */
	node = app->last_node;
	if (node) {
dbg_msg("%s 3\n", __func__);
		attr = rb_entry(node, struct mrp_attr, node);
		if (attr_type != attr->type)
			return 0;
	} else
		node = rb_first(&app->mad);

	/* Need one more byte for listener substate. */
	if (MSRP_ATTR_LISTENER == attrtype)
		msg_min++;

	/* mrp_msg_hdr + mrp_vecattr_hdr + attrlen + vaevents + 4 endmarks */
	if (msg_ptr > (msg_eof - (sizeof(struct mrp_msg_hdr) + 2 + msg_min)))
		return -1;
	memset(vectevt, 0, 3);

	msrp_prepare_tx(app, attrtype, attrmax);

	mh = (struct mrp_msg_hdr *) msg_ptr;
	mh->attrtype = attrtype;
	mh->attrlen = attrlen;
	msg_ptr += sizeof(struct mrp_msg_hdr);

	attr_list = (u16 *) msg_ptr;
	msg_ptr += 2;

	vah = (struct mrp_vecattr_hdr *) msg_ptr;
	msg_ptr += sizeof(struct mrp_vecattr_hdr);

	list_decl = kzalloc(1600 / 2, GFP_KERNEL);
	for (;
	     next = node ? rb_next(node) : NULL, node != NULL;
	     node = next) {

		/* Check if there is enough space for all required data. */
		if (!len && msg_ptr > (msg_eof - msg_min))
{
dbg_msg(" no space\n");
			break;
}

		attr = rb_entry(node, struct mrp_attr, node);
		if (attr_type != attr->type)
			continue;
		if (MSRP_ATTR_TALKER_FAILED == attr_type) {
			struct srp_talker_failed *talker =
				(struct srp_talker_failed *) attr->value;

			if ((MSRP_ATTR_TALKER == attrtype &&
			    talker->failure_code) ||
			    (MSRP_ATTR_TALKER_FAILED == attrtype &&
			    !talker->failure_code))
				continue;
		}

		/* See if next value is close enough for efficient encoding. */
		nextval = 0;
		if (MSRP_ATTR_LISTENER == attr_type) {
			struct srp_listener *listener =
				(struct srp_listener *) attr->value;

			nextval = listener->nextval;
		}
		if (!nextval)
			--nextval;

		if (MRP_TX_ACTION_NONE == attr->action) {
			if (mrp_applicant_chk(attr))
				mrp_attr_destroy(app, attr);

#if 0
if (i)
dbg_msg(" no snd\n");
#endif
			/* In case there are events waiting. */
			i += 2;
			goto val_end;
		}

		do {
#if 0
dbg_msg(" %d; %d  ", len, nextval);
#endif
		if (nextval > 0) {

			/* Fill in dummy attribute. */
			app->attrval_inc(firstval, attr->len);
#if 0
dbg_msg(" iinc [%02x] [%02x] ", firstval[7], firstval[6]);
#endif
			vectevt[i] = MRP_VECATTR_EVENT_NEW;
			list_decl[len] = MSRP_LISTENER_IGNORE;
			--nextval;
		} else {
		if (len) {
			--nextval;
			app->attrval_inc(firstval, attr->len);
#if 0
dbg_msg(" ne [%02x] [%02x] ", firstval[7], firstval[6]);
#endif
			if (memcmp(firstval, attr->value, attrlen)) {
#if 0
dbg_msg(" diff [%02x] [%02x] ", firstval[7], attr->value[7]);
#endif
				/* Process with current node. */
				next = node;
				num_break = true;
				i = 3;
				goto val_end;
			}
		}
		if (!len) {
			memcpy(firstval, attr->value, attrlen);
			memcpy(vah->firstattrvalue, firstval, attrlen);
			msg_ptr += attrlen;
		}
		switch (attr->action) {
		case MRP_TX_ACTION_S_JOIN_IN:
		case MRP_TX_ACTION_S_JOIN_IN_OPTIONAL:
			vectevt[i] = MRP_REGISTRAR_IN == attr->reg_state ?
				MRP_VECATTR_EVENT_JOIN_IN :
				MRP_VECATTR_EVENT_JOIN_MT;
			break;
		case MRP_TX_ACTION_S_IN:
		case MRP_TX_ACTION_S_IN_OPTIONAL:
			vectevt[i] = MRP_REGISTRAR_IN == attr->reg_state ?
				MRP_VECATTR_EVENT_IN :
				MRP_VECATTR_EVENT_MT;
			break;
		case MRP_TX_ACTION_S_NEW:
			vectevt[i] = MRP_VECATTR_EVENT_NEW;
			break;
		case MRP_TX_ACTION_S_LV:
			vectevt[i] = MRP_VECATTR_EVENT_LV;
			break;
		default:
			break;
		}
		if (MSRP_ATTR_LISTENER == attrtype) {
			struct srp_listener *listener =
				(struct srp_listener *) attr->value;

			list_decl[len] = listener->substate;
		}
		if (mrp_applicant_chk(attr))
			mrp_attr_destroy(app, attr);
		}

		++i;
		++len;

val_end:
		if (i >= 3) {
#if 0
dbg_msg(" vect:%d ", nextval);
#endif
			*msg_ptr++ = mrp_3pack_encode(vectevt, &i);
			if (msg_ptr > msg_eof - (1 + (len + 3) / 4 + 4)) {
				num_break = true;
				node_break = true;
				nextval = -1;
			}
		}
		if (num_break) {
#if 0
dbg_msg(" num: %d ", nextval);
#endif
			put_unaligned(cpu_to_be16(len), &vah->lenflags);
			if (app->lva.tx & (1 << (attrtype - 1)))
				vah->lenflags |= MRP_VECATTR_HDR_FLAG_LA;
			if (MSRP_ATTR_LISTENER == attrtype) {
				int j;

				memset(&list_decl[len], 0, len & 3);
				for (j = 0; j < len; j += 4)
					*msg_ptr++ =
						mrp_4pack_encode(&list_decl[j]);
			}
			len = 0;
			num_break = false;

			vah = (struct mrp_vecattr_hdr *) msg_ptr;
			msg_ptr += sizeof(struct mrp_vecattr_hdr);
if (nextval >= 0)
dbg_msg(" ?? ");
nextval = -1;
		}
		} while (nextval >= 0);
		if (node_break)
			break;
	}
	if (len) {
		if (i)
			*msg_ptr++ = mrp_3pack_encode(vectevt, &i);
		put_unaligned(cpu_to_be16(len), &vah->lenflags);
		if (app->lva.tx & (1 << (attrtype - 1)))
			vah->lenflags |= MRP_VECATTR_HDR_FLAG_LA;
		if (MSRP_ATTR_LISTENER == attrtype) {
			int j;

			memset(&list_decl[len], 0, len & 3);
			for (j = 0; j < len; j += 4)
				*msg_ptr++ = mrp_4pack_encode(&list_decl[j]);
		}
	}
	app->last_node = node;
	kfree(list_decl);

	if (msg_ptr == msg_buf +
	    sizeof(struct mrp_msg_hdr) + 2 +
	    sizeof(struct mrp_vecattr_hdr)) {
		return 0;
	}
	*msg_ptr++ = MRP_END_MARK;
	*msg_ptr++ = MRP_END_MARK;

	*bytes = msg_ptr - msg_buf;
	len = msg_ptr - (u8 *) attr_list;
	*attr_list = htons(len - 2);

	/* Not all attributes sent. */
	if (node)
		return -1;
	return 0;
}

static int msrp_parse_events(struct mrp_applicant *app,
	u8 **msg_ptr, u8 *msg_eof, u8 attrlen, u8 attrtype)
{
	struct mrp_vecattr_hdr *vah;
	u16 valen;
	u16 LA;
	u8 firstval[40];
	u8 vaevent;
	u8 vaevents;
	int add_len = 0;
	u8 *decl_ptr = NULL;
	u8 decl[4];
	int i = 4;
	int ignore;

	vah = (struct mrp_vecattr_hdr *) *msg_ptr;
	valen = get_unaligned(&vah->lenflags);
	LA = valen & MRP_VECATTR_HDR_FLAG_LA;
	valen &= MRP_VECATTR_HDR_LEN_MASK;
	valen = be16_to_cpu(valen);

	/* Zero length is allowed in new MSRP spec. */

	*msg_ptr += sizeof(struct mrp_vecattr_hdr);

	/* Do it once for each attribute type. */
	if (LA && !(app->lva.rx & (1 << attrtype))) {
#if 1
app->rla_jiffies = jiffies;
#endif
		app->lva_type = attrtype;
		mrp_mad_event(app, MRP_EVENT_R_LA);
		app->lva_type = 0;
		app->lva.rx |= (1 << attrtype);
	}

	/* Listener storage has extra stuff. */
	if (attrlen < sizeof(struct srp_talker_failed))
		memset(firstval, 0, sizeof(struct srp_talker_failed));
	memcpy(firstval, vah->firstattrvalue, attrlen);
	*msg_ptr += attrlen;

	if (!valen)
		return 0;

	if (MSRP_ATTR_LISTENER == attrtype) {
		/* For substate. */
		attrlen += 2;
		add_len = (valen + 3) / 4;
		decl_ptr = *msg_ptr + (valen + 2) / 3;
	} else if (MSRP_ATTR_TALKER == attrtype) {
		attrtype = MSRP_ATTR_TALKER_FAILED;
		memset(&firstval[25], 0, 34 - 25);
		attrlen = 34;
	}
	if (*msg_ptr + (valen + 2) / 3 + add_len > msg_eof)
{
dbg_msg(" not enough %p %d %d %p\n", *msg_ptr, valen, add_len, msg_eof);
		return -1;
}

	/* In a VectorAttribute, the Vector contains events which are packed
	 * three to a byte. We process one byte of the Vector at a time.
	 */
	while (valen > 0) {
		vaevents = **msg_ptr;
		*msg_ptr += sizeof(vaevents);

		/* Extract and process the first event. */
		vaevent = vaevents / (__MRP_VECATTR_EVENT_MAX *
				      __MRP_VECATTR_EVENT_MAX);
		if (vaevent >= __MRP_VECATTR_EVENT_MAX) {
			/* The byte is malformed; stop processing. */
			return -1;
		}
		ignore = false;
		if (decl_ptr) {
			if (4 == i)
				mrp_4pack_decode(*decl_ptr++, decl, &i);
			if (MSRP_LISTENER_IGNORE == decl[i])
				ignore = true;
			firstval[8] = decl[i++];
		}
		if (!ignore)
			mrp_update_attr(app, firstval, attrlen, attrtype,
				vaevent);

		/* If present, extract and process the second event. */
		if (!--valen)
			break;
		vaevents %= (__MRP_VECATTR_EVENT_MAX *
			     __MRP_VECATTR_EVENT_MAX);
		vaevent = vaevents / __MRP_VECATTR_EVENT_MAX;
		app->attrval_inc(firstval, attrlen);
		ignore = false;
		if (decl_ptr) {
			if (4 == i)
				mrp_4pack_decode(*decl_ptr++, decl, &i);
			if (MSRP_LISTENER_IGNORE == decl[i])
				ignore = true;
			firstval[8] = decl[i++];
		}
		if (!ignore)
			mrp_update_attr(app, firstval, attrlen, attrtype,
				vaevent);

		/* If present, extract and process the third event. */
		if (!--valen)
			break;
		vaevents %= __MRP_VECATTR_EVENT_MAX;
		vaevent = vaevents;
		app->attrval_inc(firstval, attrlen);
		ignore = false;
		if (decl_ptr) {
			if (4 == i)
				mrp_4pack_decode(*decl_ptr++, decl, &i);
			if (MSRP_LISTENER_IGNORE == decl[i])
				ignore = true;
			firstval[8] = decl[i++];
		}
		if (!ignore)
			mrp_update_attr(app, firstval, attrlen, attrtype,
				vaevent);
		app->attrval_inc(firstval, attrlen);
		--valen;
	}
#if 0
dbg_msg(" decl_ptr: %p %p\n", *msg_ptr, decl_ptr);
#endif
	if (decl_ptr)
		*msg_ptr = decl_ptr;
	return 0;
}

static int msrp_parse_msg(struct mrp_applicant *app, u8 **msg_ptr, u8 *msg_eof)
{
	struct mrp_msg_hdr *mh;
	u16 *attr_list;
	int rc;
	int add_len = 0;

	/*
	 * End mark terminates the message.  Happen when there are filler
	 * bytes in the frame.
	 */
	mh = (struct mrp_msg_hdr *) *msg_ptr;
	if (MRP_END_MARK == mh->attrtype &&
	    MRP_END_MARK == mh->attrlen) {
		return -1;
	}

	/* Check whether the attribute type is understood. */
	rc = app->attr_chk(mh->attrtype, mh->attrlen);
	if (rc < 0)
		return -1;

	if (MSRP_ATTR_LISTENER == mh->attrtype)
		add_len++;

	*msg_ptr += sizeof(struct mrp_msg_hdr);
	attr_list = (u16 *) *msg_ptr;
	if (ntohs(*attr_list) < mh->attrlen + 4)
{
int i;
u8 *data = *msg_ptr;

for (i = 0; i < msg_eof - *msg_ptr; i++) {
dbg_msg("%02x ", data[i]);
if ((i % 16) == 15)
dbg_msg("\n");
}
if ((i % 16))
dbg_msg("\n");
dbg_msg(" bad attrlist: %d %d\n", ntohs(*attr_list), mh->attrlen);
		return -1;
}
	*msg_ptr += 2;
	while (*msg_ptr <= (msg_eof - (2 + 1 + add_len))) {
		rc = msrp_parse_events(app, msg_ptr, msg_eof,
			mh->attrlen, mh->attrtype);
		if (rc < 0)
			return rc;
		rc = mrp_parse_end_mark(msg_ptr, msg_eof);
		if (rc <= 0) {
			u16 len = *msg_ptr - (u8 *) attr_list;

			if (len - 2 != ntohs(*attr_list))
dbg_msg("attrlist %u %u\n", ntohs(*attr_list), len - 2);
		}

		/* End mark terminates the vector list. */
		if (rc <= 0)
			return rc;
	}
	return 0;
}

static int msrp_rx(struct mrp_applicant *app, u8 *data, int len)
{
	struct mrp_pdu_hdr *ph;
	u8 *msg_ptr;
	u8 *msg_eof;
	int rc;

	ph = (struct mrp_pdu_hdr *) data;
	if (ph->version != app->app->version)
		return -1;

	app->lva.rx = 0;

	msg_ptr = (u8 *)(ph + 1);
	msg_eof = msg_ptr + len - sizeof(struct mrp_pdu_hdr);

	while (msg_ptr <= (msg_eof - (2 + 2))) {
		rc = msrp_parse_msg(app, &msg_ptr, msg_eof);
		if (rc < 0)
			return rc;

		/* End mark terminates the frame. */
		rc = mrp_parse_end_mark(&msg_ptr, msg_eof);
		if (rc <= 0)
			return rc;
	}
	return 0;
}

static int msrp_rxpdu(struct mrp_applicant *app, u8 *data, int len)
{
	return msrp_rx(app, data, len);
}

static int msrp_txpdu(struct mrp_applicant *app)
{
	int bytes;
	int err;
	u8 *msg_buf;
	u8 *msg_eof;
	u8 *msg_ptr;

	err = mrp_pdu_init(app);
	if (err < 0)
		return err;

	msg_buf = app->pdu->data;
	msg_eof = msg_buf + app->dev->mtu;
	msg_buf++;
	msg_ptr = msg_buf;

	err = msrp_tx(app, msg_ptr, msg_eof, &bytes,
		MSRP_ATTR_TALKER, sizeof(struct srp_talker),
		MSRP_TALKER_OPT_MAX, MSRP_TALKER_MIN);

	/* LeaveAll for MAC attribute type sent. */
	if (bytes) {
		msg_ptr += bytes;
		app->lva.tx &= ~(1 << (MSRP_ATTR_TALKER - 1));

		/* No more space. */
		if (-1 == err)
			goto send;
	}

	err = msrp_tx(app, msg_ptr, msg_eof, &bytes,
		MSRP_ATTR_TALKER_FAILED, sizeof(struct srp_talker_failed),
		MSRP_TALKER_FAILED_OPT_MAX, MSRP_TALKER_FAILED_MIN);

	/* LeaveAll for MAC attribute type sent. */
	if (bytes) {
		msg_ptr += bytes;
		app->lva.tx &= ~(1 << (MSRP_ATTR_TALKER_FAILED - 1));

		/* No more space. */
		if (-1 == err)
			goto send;
	}

	err = msrp_tx(app, msg_ptr, msg_eof, &bytes,
		MSRP_ATTR_LISTENER, sizeof(struct srp_listener) - 2,
		MSRP_LISTENER_OPT_MAX, MSRP_LISTENER_MIN);

	/* LeaveAll for SVC attribute type sent. */
	if (bytes) {
		msg_ptr += bytes;
		app->lva.tx &= ~(1 << (MSRP_ATTR_LISTENER - 1));

		/* No more space. */
		if (-1 == err)
			goto send;
	}

	err = msrp_tx(app, msg_ptr, msg_eof, &bytes,
		MSRP_ATTR_DOMAIN, sizeof(struct srp_domain),
		MSRP_DOMAIN_OPT_MAX, MSRP_DOMAIN_MIN);

	/* LeaveAll for SVC attribute type sent. */
	if (bytes) {
		msg_ptr += bytes;
		app->lva.tx &= ~(1 << (MSRP_ATTR_DOMAIN - 1));

		/* No more space. */
		if (-1 == err)
			goto send;
	}

send:

	return mrp_txpdu(app, msg_buf, msg_ptr, msg_eof, err);
}

static int msrp_req_join_domain(struct mrp_applicant *app,
	struct srp_domain *domain)
{
	return mrp_req_new(app, domain, sizeof(struct srp_domain),
		MSRP_ATTR_DOMAIN, MRP_EVENT_JOIN);
}

static int msrp_req_new_listener(struct mrp_applicant *app,
	struct srp_listener *listener)
{
	listener->nextval = 0;
	return mrp_req_new(app, listener, sizeof(struct srp_listener),
		MSRP_ATTR_LISTENER, MRP_EVENT_NEW);
}

static int msrp_req_new_talker(struct mrp_applicant *app,
	struct srp_talker_failed *talker)
{
	return mrp_req_new(app, talker, sizeof(struct srp_talker_failed),
		MSRP_ATTR_TALKER_FAILED, MRP_EVENT_NEW);
}

static void msrp_req_leave_domain(struct mrp_applicant *app,
	struct srp_domain *domain)
{
	mrp_req_leave(app, domain, sizeof(struct srp_domain),
		MSRP_ATTR_DOMAIN);
}

static void msrp_req_leave_listener(struct mrp_applicant *app,
	struct srp_listener *listener)
{
	listener->nextval = 0;
	mrp_req_leave(app, listener, sizeof(struct srp_listener),
		MSRP_ATTR_LISTENER);
}

static void msrp_req_leave_talker(struct mrp_applicant *app,
	struct srp_talker_failed *talker)
{
	mrp_req_leave(app, talker, sizeof(struct srp_talker_failed),
		MSRP_ATTR_TALKER_FAILED);
}

static void msrp_init_application(struct mrp_applicant *app, void *mrp, u8 port,
	void (*acton)(struct mrp_applicant *app, struct mrp_attr *attr))
{
	app->parent = mrp;
	app->port = port;
	app->attrval_inc = msrp_attrvalue_inc;
	app->attr_chk = msrp_attr_chk;
	app->attr_cmp = msrp_attr_cmp;
	app->attr_len = msrp_attr_len;
	app->attr_type = msrp_attr_type;
	app->attr_upd = msrp_attr_upd;
	app->rxpdu = msrp_rxpdu;
	app->txpdu = msrp_txpdu;
	app->acton = acton;
}

