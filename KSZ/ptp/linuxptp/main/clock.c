/**
 * @file clock.c
 * @note Copyright (C) 2011 Richard Cochran <richardcochran@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */
#include <errno.h>
#include <linux/net_tstamp.h>
#include <poll.h>
#include <stdlib.h>
#include <string.h>
#ifdef KSZ_1588_PTP
#include <stdarg.h>
#endif
#include <time.h>
#include <sys/queue.h>

#include "address.h"
#include "bmc.h"
#include "clock.h"
#include "clockadj.h"
#include "clockcheck.h"
#include "foreign.h"
#include "filter.h"
#include "hash.h"
#include "missing.h"
#include "msg.h"
#include "phc.h"
#include "port.h"
#include "servo.h"
#include "stats.h"
#include "print.h"
#include "rtnl.h"
#include "sk.h"
#include "tlv.h"
#include "tsproc.h"
#include "uds.h"
#include "util.h"

#define N_CLOCK_PFD (N_POLLFD + 1) /* one extra per port, for the fault timer */
#define POW2_41 ((double)(1ULL << 41))

struct port {
	LIST_ENTRY(port) list;
#ifdef KSZ_1588_PTP
	char *name;
#endif
};

struct freq_estimator {
	tmv_t origin1;
	tmv_t ingress1;
	unsigned int max_count;
	unsigned int count;
};

struct clock_stats {
	struct stats *offset;
	struct stats *freq;
	struct stats *delay;
	unsigned int max_count;
};

struct clock_subscriber {
	LIST_ENTRY(clock_subscriber) list;
	uint8_t events[EVENT_BITMASK_CNT];
	struct PortIdentity targetPortIdentity;
	struct address addr;
	UInteger16 sequenceId;
	time_t expiration;
};

struct clock {
	enum clock_type type;
	struct config *config;
	clockid_t clkid;
	struct servo *servo;
	enum servo_type servo_type;
	struct defaultDS dds;
	struct dataset default_dataset;
	struct currentDS cur;
	struct parent_ds dad;
	struct timePropertiesDS tds;
	struct ClockIdentity ptl[PATH_TRACE_MAX];
	struct foreign_clock *best;
	struct ClockIdentity best_id;
	LIST_HEAD(ports_head, port) ports;
	struct port *uds_port;
	struct pollfd *pollfd;
	int pollfd_valid;
	int nports; /* does not include the UDS port */
	int last_port_number;
	int sde;
	struct hash *index2port;
	int free_running;
	int freq_est_interval;
	int grand_master_capable; /* for 802.1AS only */
	int utc_timescale;
	int utc_offset_set;
	int leap_set;
	int kernel_leap;
	int utc_offset;  /* grand master role */
	int current_utc_offset;  /* UTC offset fallback */
	int time_flags;  /* grand master role */
	int time_source; /* grand master role */
	enum servo_state servo_state;
	tmv_t master_offset;
	tmv_t path_delay;
	tmv_t ingress_ts;
	struct tsproc *tsproc;
	struct freq_estimator fest;
	struct time_status_np status;
	double nrr;
	struct clock_description desc;
	struct clock_stats stats;
	int stats_interval;
	struct clockcheck *sanity_check;
	struct interface uds_interface;
	LIST_HEAD(clock_subscribers_head, clock_subscriber) subscribers;
#ifdef KSZ_1588_PTP
	tmv_t origin_ts;
	enum delay_mechanism dm;
	int direct;
	int ieee_c37_238;
	int transparent;
	int port_mask;
	int master_port;
	int dev_cnt;
	int drift;
	int skip_sync_check;
	int use_one_step;
	int use_2_step_pdelay;
	UInteger8 port_cnt;
	UInteger8 version;
	UInteger8 initialSyncReceiptTimeout;
	UInteger8 waitPdelayReqInterval;
	UInteger8 waitSyncInterval;
	UInteger32 access_delay;
	UInteger32 min_sync_interval;
	struct port *dispatch;
	struct port *host_port;
	struct port *slave_port;
#endif
};

struct clock the_clock;

static void handle_state_decision_event(struct clock *c);
static int clock_resize_pollfd(struct clock *c, int new_nports);
static void clock_remove_port(struct clock *c, struct port *p);

static int cid_eq(struct ClockIdentity *a, struct ClockIdentity *b)
{
	return 0 == memcmp(a, b, sizeof(*a));
}

#ifndef LIST_FOREACH_SAFE
#define	LIST_FOREACH_SAFE(var, head, field, tvar)			\
	for ((var) = LIST_FIRST((head));				\
	    (var) && ((tvar) = LIST_NEXT((var), field), 1);		\
	    (var) = (tvar))
#endif

static void remove_subscriber(struct clock_subscriber *s)
{
	LIST_REMOVE(s, list);
	free(s);
}

static void clock_update_subscription(struct clock *c, struct ptp_message *req,
				      uint8_t *bitmask, uint16_t duration)
{
	struct clock_subscriber *s;
	int i, remove = 1;
	struct timespec now;

	for (i = 0; i < EVENT_BITMASK_CNT; i++) {
		if (bitmask[i]) {
			remove = 0;
			break;
		}
	}

	LIST_FOREACH(s, &c->subscribers, list) {
		if (!memcmp(&s->targetPortIdentity, &req->header.sourcePortIdentity,
		            sizeof(struct PortIdentity))) {
			/* Found, update the transport address and event
			 * mask. */
			if (!remove) {
				s->addr = req->address;
				memcpy(s->events, bitmask, EVENT_BITMASK_CNT);
				clock_gettime(CLOCK_MONOTONIC, &now);
				s->expiration = now.tv_sec + duration;
			} else {
				remove_subscriber(s);
			}
			return;
		}
	}
	if (remove)
		return;
	/* Not present yet, add the subscriber. */
	s = malloc(sizeof(*s));
	if (!s) {
		pr_err("failed to allocate memory for a subscriber");
		return;
	}
	s->targetPortIdentity = req->header.sourcePortIdentity;
	s->addr = req->address;
	memcpy(s->events, bitmask, EVENT_BITMASK_CNT);
	clock_gettime(CLOCK_MONOTONIC, &now);
	s->expiration = now.tv_sec + duration;
	s->sequenceId = 0;
	LIST_INSERT_HEAD(&c->subscribers, s, list);
}

static void clock_get_subscription(struct clock *c, struct ptp_message *req,
				   uint8_t *bitmask, uint16_t *duration)
{
	struct clock_subscriber *s;
	struct timespec now;

	LIST_FOREACH(s, &c->subscribers, list) {
		if (!memcmp(&s->targetPortIdentity, &req->header.sourcePortIdentity,
			    sizeof(struct PortIdentity))) {
			memcpy(bitmask, s->events, EVENT_BITMASK_CNT);
			clock_gettime(CLOCK_MONOTONIC, &now);
			if (s->expiration < now.tv_sec)
				*duration = 0;
			else
				*duration = s->expiration - now.tv_sec;
			return;
		}
	}
	/* A client without entry means the client has no subscriptions. */
	memset(bitmask, 0, EVENT_BITMASK_CNT);
	*duration = 0;
}

static void clock_flush_subscriptions(struct clock *c)
{
	struct clock_subscriber *s, *tmp;

	LIST_FOREACH_SAFE(s, &c->subscribers, list, tmp) {
		remove_subscriber(s);
	}
}

static void clock_prune_subscriptions(struct clock *c)
{
	struct clock_subscriber *s, *tmp;
	struct timespec now;

	clock_gettime(CLOCK_MONOTONIC, &now);
	LIST_FOREACH_SAFE(s, &c->subscribers, list, tmp) {
		if (s->expiration <= now.tv_sec) {
			pr_info("subscriber %s timed out",
				pid2str(&s->targetPortIdentity));
			remove_subscriber(s);
		}
	}
}

void clock_send_notification(struct clock *c, struct ptp_message *msg,
			     int msglen, enum notification event)
{
	unsigned int event_pos = event / 8;
	uint8_t mask = 1 << (event % 8);
	struct port *uds = c->uds_port;
	struct clock_subscriber *s;

	LIST_FOREACH(s, &c->subscribers, list) {
		if (!(s->events[event_pos] & mask))
			continue;
		/* send event */
		msg->header.sequenceId = htons(s->sequenceId);
		s->sequenceId++;
		msg->management.targetPortIdentity.clockIdentity =
			s->targetPortIdentity.clockIdentity;
		msg->management.targetPortIdentity.portNumber =
			htons(s->targetPortIdentity.portNumber);
		msg->address = s->addr;
		port_forward_to(uds, msg);
	}
}

void clock_destroy(struct clock *c)
{
	struct port *p, *tmp;

	clock_flush_subscriptions(c);
	LIST_FOREACH_SAFE(p, &c->ports, list, tmp) {
		clock_remove_port(c, p);
	}
#ifdef KSZ_1588_PTP
	port_exit_ptp(c);
#endif
	if (c->pollfd[0].fd >= 0) {
		rtnl_close(c->pollfd[0].fd);
	}
	port_close(c->uds_port);
	free(c->pollfd);
	hash_destroy(c->index2port, NULL);
	if (c->clkid != CLOCK_REALTIME) {
		phc_close(c->clkid);
	}
	servo_destroy(c->servo);
	tsproc_destroy(c->tsproc);
	stats_destroy(c->stats.offset);
	stats_destroy(c->stats.freq);
	stats_destroy(c->stats.delay);
	if (c->sanity_check)
		clockcheck_destroy(c->sanity_check);
	memset(c, 0, sizeof(*c));
	msg_cleanup();
}

static int clock_fault_timeout(struct port *port, int set)
{
	struct fault_interval i;

	if (!set) {
		pr_debug("clearing fault on port %d", port_number(port));
		return port_set_fault_timer_lin(port, 0);
	}

	fault_interval(port, last_fault_type(port), &i);

	if (i.type == FTMO_LINEAR_SECONDS) {
		pr_debug("waiting %d seconds to clear fault on port %d",
			 i.val, port_number(port));
		return port_set_fault_timer_lin(port, i.val);
	} else if (i.type == FTMO_LOG2_SECONDS) {
		pr_debug("waiting 2^{%d} seconds to clear fault on port %d",
			 i.val, port_number(port));
		return port_set_fault_timer_log(port, 1, i.val);
	}

	pr_err("Unsupported fault interval type %d", i.type);
	return -1;
}

static void clock_freq_est_reset(struct clock *c)
{
	c->fest.origin1 = tmv_zero();
	c->fest.ingress1 = tmv_zero();
	c->fest.count = 0;
}

static void clock_link_status(void *ctx, int index, int linkup)
{
	struct clock *c = ctx;
	struct port *p;
	char key[16];

	snprintf(key, sizeof(key), "%d", index);
	p = hash_lookup(c->index2port, key);
	if (!p) {
		return;
	}
	port_link_status_set(p, linkup);
	if (linkup) {
		port_dispatch(p, EV_FAULT_CLEARED, 0);
#ifdef KSZ_1588_PTP
		if (port_is_aed_master(p)) {
			port_dispatch(p, EV_RS_GRAND_MASTER, 0);
		} else if (port_is_aed(p)) {
			port_dispatch(p, EV_RS_SLAVE, 0);
		} else if (c->slave_port && p != c->slave_port)
			port_dispatch(p, EV_RS_GRAND_MASTER, 0);
#endif
	} else {
		port_dispatch(p, EV_FAULT_DETECTED, 0);
		/*
		 * A port going down can affect the BMCA result.
		 * Force a state decision event.
		 */
#ifdef KSZ_1588_PTP
		if (!port_is_aed(p))
#endif
		c->sde = 1;
	}
}

static void clock_management_send_error(struct port *p,
					struct ptp_message *msg, int error_id)
{
	if (port_management_error(port_identity(p), p, msg, error_id))
		pr_err("failed to send management error status");
}

/* The 'p' and 'req' paremeters are needed for the GET actions that operate
 * on per-client datasets. If such actions do not apply to the caller, it is
 * allowed to pass both of them as NULL.
 */
static int clock_management_fill_response(struct clock *c, struct port *p,
					  struct ptp_message *req,
					  struct ptp_message *rsp, int id)
{
	int datalen = 0, respond = 0;
	struct management_tlv *tlv;
	struct management_tlv_datum *mtd;
	struct time_status_np *tsn;
	struct grandmaster_settings_np *gsn;
	struct subscribe_events_np *sen;
	struct PTPText *text;

	tlv = (struct management_tlv *) rsp->management.suffix;
	tlv->type = TLV_MANAGEMENT;
	tlv->id = id;

	switch (id) {
	case TLV_USER_DESCRIPTION:
		text = (struct PTPText *) tlv->data;
		text->length = c->desc.userDescription.length;
		memcpy(text->text, c->desc.userDescription.text, text->length);
		datalen = 1 + text->length;
		respond = 1;
		break;
	case TLV_DEFAULT_DATA_SET:
		memcpy(tlv->data, &c->dds, sizeof(c->dds));
		datalen = sizeof(c->dds);
		respond = 1;
		break;
	case TLV_CURRENT_DATA_SET:
		memcpy(tlv->data, &c->cur, sizeof(c->cur));
		datalen = sizeof(c->cur);
		respond = 1;
		break;
#ifdef KSZ_1588_PTP
	case TLV_TRANSPARENT_CLOCK_DEFAULT_DATA_SET:
	{
		struct transparent_clock_default_data_set *dds =
			(struct transparent_clock_default_data_set *) tlv->data;

		respond = 1;
		if (!transparent_clock(c))
			break;
		memcpy(&dds->clockIdentity, &c->dds.clockIdentity,
			sizeof(struct ClockIdentity));
		dds->numberPorts = c->port_cnt;
		dds->delayMechanism = c->dm;
		dds->primaryDomain = c->dds.domainNumber;
		datalen = sizeof(*dds);
		break;
	}
	case TLV_TRANSPARENT_CLOCK_PORT_DATA_SET:
		if (!transparent_clock(c)) {
			respond = 1;
			break;
		}
		break;
	case TLV_TIME:
	{
		struct timespec now;
		struct Timestamp *ts = (struct Timestamp *) tlv->data;

		clock_gettime(c->clkid, &now);
		ts->nanoseconds = now.tv_nsec;
		ts->seconds_lsb = now.tv_sec;
		ts->seconds_msb = 0;
		datalen = sizeof(*ts);
		respond = 1;
		break;
	}
#endif
	case TLV_PARENT_DATA_SET:
		memcpy(tlv->data, &c->dad.pds, sizeof(c->dad.pds));
		datalen = sizeof(c->dad.pds);
		respond = 1;
		break;
	case TLV_TIME_PROPERTIES_DATA_SET:
		memcpy(tlv->data, &c->tds, sizeof(c->tds));
		datalen = sizeof(c->tds);
		respond = 1;
		break;
	case TLV_PRIORITY1:
		mtd = (struct management_tlv_datum *) tlv->data;
		mtd->val = c->dds.priority1;
		datalen = sizeof(*mtd);
		respond = 1;
		break;
	case TLV_PRIORITY2:
		mtd = (struct management_tlv_datum *) tlv->data;
		mtd->val = c->dds.priority2;
		datalen = sizeof(*mtd);
		respond = 1;
		break;
	case TLV_DOMAIN:
		mtd = (struct management_tlv_datum *) tlv->data;
		mtd->val = c->dds.domainNumber;
		datalen = sizeof(*mtd);
		respond = 1;
		break;
	case TLV_SLAVE_ONLY:
		mtd = (struct management_tlv_datum *) tlv->data;
		mtd->val = c->dds.flags & DDS_SLAVE_ONLY;
		datalen = sizeof(*mtd);
		respond = 1;
		break;
	case TLV_CLOCK_ACCURACY:
		mtd = (struct management_tlv_datum *) tlv->data;
		mtd->val = c->dds.clockQuality.clockAccuracy;
		datalen = sizeof(*mtd);
		respond = 1;
		break;
	case TLV_TRACEABILITY_PROPERTIES:
		mtd = (struct management_tlv_datum *) tlv->data;
		mtd->val = c->tds.flags & (TIME_TRACEABLE|FREQ_TRACEABLE);
		datalen = sizeof(*mtd);
		respond = 1;
		break;
	case TLV_TIMESCALE_PROPERTIES:
		mtd = (struct management_tlv_datum *) tlv->data;
		mtd->val = c->tds.flags & PTP_TIMESCALE;
		datalen = sizeof(*mtd);
		respond = 1;
		break;
	case TLV_TIME_STATUS_NP:
		tsn = (struct time_status_np *) tlv->data;
		tsn->master_offset = c->master_offset;
		tsn->ingress_time = tmv_to_nanoseconds(c->ingress_ts);
		tsn->cumulativeScaledRateOffset =
			(Integer32) (c->status.cumulativeScaledRateOffset +
				      c->nrr * POW2_41 - POW2_41);
		tsn->scaledLastGmPhaseChange = c->status.scaledLastGmPhaseChange;
		tsn->gmTimeBaseIndicator = c->status.gmTimeBaseIndicator;
		tsn->lastGmPhaseChange = c->status.lastGmPhaseChange;
		if (cid_eq(&c->dad.pds.grandmasterIdentity, &c->dds.clockIdentity))
			tsn->gmPresent = 0;
		else
			tsn->gmPresent = 1;
		tsn->gmIdentity = c->dad.pds.grandmasterIdentity;
		datalen = sizeof(*tsn);
		respond = 1;
		break;
	case TLV_GRANDMASTER_SETTINGS_NP:
		gsn = (struct grandmaster_settings_np *) tlv->data;
		gsn->clockQuality = c->dds.clockQuality;
		gsn->utc_offset = c->utc_offset;
		gsn->time_flags = c->time_flags;
		gsn->time_source = c->time_source;
		datalen = sizeof(*gsn);
		respond = 1;
		break;
	case TLV_SUBSCRIBE_EVENTS_NP:
		if (p != c->uds_port) {
			/* Only the UDS port allowed. */
			break;
		}
		sen = (struct subscribe_events_np *)tlv->data;
		clock_get_subscription(c, req, sen->bitmask, &sen->duration);
		respond = 1;
#ifdef KSZ_1588_PTP
	case TLV_WAKE_INFO:
		mtd = (struct management_tlv_datum *) tlv->data;
		mtd->val = 0;
		datalen = sizeof(*mtd);
		respond = 1;
		break;
#endif
	}
	if (respond) {
		if (datalen % 2) {
			tlv->data[datalen] = 0;
			datalen++;
		}
		tlv->length = sizeof(tlv->id) + datalen;
		rsp->header.messageLength += sizeof(*tlv) + datalen;
		rsp->tlv_count = 1;
	}
	return respond;
}

static int clock_management_get_response(struct clock *c, struct port *p,
					 int id, struct ptp_message *req)
{
	struct PortIdentity pid = port_identity(p);
	struct ptp_message *rsp;
	int respond;

	rsp = port_management_reply(pid, p, req);
	if (!rsp) {
		return 0;
	}
	respond = clock_management_fill_response(c, p, req, rsp, id);
	if (respond)
		port_prepare_and_send(p, rsp, 0);
	msg_put(rsp);
	return respond;
}

#ifdef KSZ_1588_PTP
int clock_master_lost(struct clock *c)
{
	enum port_state state;
	struct port *p;
int n = 0;

	LIST_FOREACH(p, &c->ports, list) {
n++;
		if (skip_host_port(c, p))
			continue;
		state = port_state(p);
		if (PS_SLAVE == state ||
		    PS_UNCALIBRATED == state)
{
if (!c->slave_port)
printf(" no slave? %d\n", n);
			return 0;
}
	}
if (c->slave_port)
printf(" slave ?\n");
	return 1;
}

int clock_master_selected(struct clock *c)
{
	enum port_state state;
	struct port *p;

	LIST_FOREACH(p, &c->ports, list) {
		if (p == c->host_port)
			continue;
		state = port_state(p);
		if (PS_MASTER == state || PS_GRAND_MASTER == state)
			return 1;
	}
	return 0;
}
#endif

static int clock_management_set(struct clock *c, struct port *p,
				int id, struct ptp_message *req, int *changed)
{
	int respond = 0;
	struct management_tlv *tlv;
	struct management_tlv_datum *mtd;
	struct grandmaster_settings_np *gsn;
	struct subscribe_events_np *sen;

	tlv = (struct management_tlv *) req->management.suffix;

	switch (id) {
	case TLV_PRIORITY1:
		mtd = (struct management_tlv_datum *) tlv->data;
		c->dds.priority1 = mtd->val;
		*changed = 1;
		respond = 1;
		break;
	case TLV_PRIORITY2:
		mtd = (struct management_tlv_datum *) tlv->data;
		c->dds.priority2 = mtd->val;
		*changed = 1;
		respond = 1;
		break;
	case TLV_GRANDMASTER_SETTINGS_NP:
		gsn = (struct grandmaster_settings_np *) tlv->data;
		c->dds.clockQuality = gsn->clockQuality;
		c->utc_offset = gsn->utc_offset;
		c->time_flags = gsn->time_flags;
		c->time_source = gsn->time_source;
		*changed = 1;
		respond = 1;
		break;
	case TLV_SUBSCRIBE_EVENTS_NP:
		sen = (struct subscribe_events_np *)tlv->data;
		clock_update_subscription(c, req, sen->bitmask,
					  sen->duration);
		respond = 1;
		break;
#ifdef KSZ_1588_PTP
	case TLV_WAKE_INFO:
		mtd = (struct management_tlv_datum *) tlv->data;
		process_wake_info(c, p, mtd->val);
		respond = 1;
		break;
#endif
	}
	if (respond && !clock_management_get_response(c, p, id, req))
		pr_err("failed to send management set response");
	return respond ? 1 : 0;
}

static void clock_stats_update(struct clock_stats *s,
			       int64_t offset, double freq)
{
	struct stats_result offset_stats, freq_stats, delay_stats;

	stats_add_value(s->offset, offset);
	stats_add_value(s->freq, freq);

	if (stats_get_num_values(s->offset) < s->max_count)
		return;

	stats_get_result(s->offset, &offset_stats);
	stats_get_result(s->freq, &freq_stats);

	/* Path delay stats are updated separately, they may be empty. */
	if (!stats_get_result(s->delay, &delay_stats)) {
		pr_info("rms %4.0f max %4.0f "
			"freq %+6.0f +/- %3.0f "
			"delay %5.0f +/- %3.0f",
			offset_stats.rms, offset_stats.max_abs,
			freq_stats.mean, freq_stats.stddev,
			delay_stats.mean, delay_stats.stddev);
	} else {
		pr_info("rms %4.0f max %4.0f "
			"freq %+6.0f +/- %3.0f",
			offset_stats.rms, offset_stats.max_abs,
			freq_stats.mean, freq_stats.stddev);
	}

	stats_reset(s->offset);
	stats_reset(s->freq);
	stats_reset(s->delay);
}

static enum servo_state clock_no_adjust(struct clock *c, tmv_t ingress,
					tmv_t origin)
{
	double fui;
	double ratio, freq;
	struct freq_estimator *f = &c->fest;
	enum servo_state state = SERVO_UNLOCKED;
	/*
	 * The ratio of the local clock freqency to the master clock
	 * is estimated by:
	 *
	 *    (ingress_2 - ingress_1) / (origin_2 - origin_1)
	 *
	 * Both of the origin time estimates include the path delay,
	 * but we assume that the path delay is in fact constant.
	 * By leaving out the path delay altogther, we can avoid the
	 * error caused by our imperfect path delay measurement.
	 */
	if (!f->ingress1) {
		f->ingress1 = ingress;
		f->origin1 = origin;
		return state;
	}
	f->count++;
	if (f->count < f->max_count) {
		return state;
	}
	if (tmv_eq(ingress, f->ingress1)) {
		pr_warning("bad timestamps in rate ratio calculation");
		return state;
	}

	ratio = tmv_dbl(tmv_sub(origin, f->origin1)) /
		tmv_dbl(tmv_sub(ingress, f->ingress1));
	freq = (1.0 - ratio) * 1e9;

	if (c->stats.max_count > 1) {
		clock_stats_update(&c->stats,
				   tmv_to_nanoseconds(c->master_offset), freq);
	} else {
		pr_info("master offset %10" PRId64 " s%d freq %+7.0f "
			"path delay %9" PRId64,
			tmv_to_nanoseconds(c->master_offset), state, freq,
			tmv_to_nanoseconds(c->path_delay));
	}

	fui = 1.0 + (c->status.cumulativeScaledRateOffset + 0.0) / POW2_41;

	pr_debug("peer/local    %.9f", c->nrr);
	pr_debug("fup_info      %.9f", fui);
	pr_debug("product       %.9f", fui * c->nrr);
	pr_debug("sum-1         %.9f", fui + c->nrr - 1.0);
	pr_debug("master/local  %.9f", ratio);
	pr_debug("diff         %+.9f", ratio - (fui + c->nrr - 1.0));

	f->ingress1 = ingress;
	f->origin1 = origin;
	f->count = 0;

	return state;
}

static void clock_update_grandmaster(struct clock *c)
{
	struct parentDS *pds = &c->dad.pds;
	memset(&c->cur, 0, sizeof(c->cur));
	memset(c->ptl, 0, sizeof(c->ptl));
	pds->parentPortIdentity.clockIdentity   = c->dds.clockIdentity;
	pds->parentPortIdentity.portNumber      = 0;
	pds->grandmasterIdentity                = c->dds.clockIdentity;
	pds->grandmasterClockQuality            = c->dds.clockQuality;
	pds->grandmasterPriority1               = c->dds.priority1;
	pds->grandmasterPriority2               = c->dds.priority2;
	c->dad.path_length                      = 0;
	c->tds.currentUtcOffset                 = c->utc_offset;
	c->tds.flags                            = c->time_flags;
	c->tds.timeSource                       = c->time_source;
}

static void clock_update_slave(struct clock *c)
{
	struct parentDS *pds = &c->dad.pds;
	struct ptp_message *msg        = TAILQ_FIRST(&c->best->messages);
	c->cur.stepsRemoved            = 1 + c->best->dataset.stepsRemoved;
	pds->parentPortIdentity        = c->best->dataset.sender;
	pds->grandmasterIdentity       = msg->announce.grandmasterIdentity;
	pds->grandmasterClockQuality   = msg->announce.grandmasterClockQuality;
	pds->grandmasterPriority1      = msg->announce.grandmasterPriority1;
	pds->grandmasterPriority2      = msg->announce.grandmasterPriority2;

#ifdef KSZ_1588_PTP
	/* Update pathTrace here instead in update_current_master(). */
	do {
		struct path_trace_tlv *ptt;

		ptt = (struct path_trace_tlv *) msg->announce.suffix;
		memcpy(c->dad.ptl, ptt->cid, ptt->length);
		c->dad.path_length = path_length(ptt);
	} while (0);
#endif
	c->tds.currentUtcOffset        = msg->announce.currentUtcOffset;
	c->tds.flags                   = msg->header.flagField[1];
	c->tds.timeSource              = msg->announce.timeSource;
	if (!(c->tds.flags & PTP_TIMESCALE)) {
		pr_warning("foreign master not using PTP timescale");
	}
	if (c->tds.currentUtcOffset < c->current_utc_offset) {
		pr_warning("running in a temporal vortex");
	}
}

static int clock_utc_correct(struct clock *c, tmv_t ingress)
{
	struct timespec offset;
	int utc_offset, leap, clock_leap;
	uint64_t ts;

	if (!c->utc_timescale)
		return 0;

	if (c->tds.flags & UTC_OFF_VALID && c->tds.flags & TIME_TRACEABLE) {
		utc_offset = c->tds.currentUtcOffset;
	} else if (c->tds.currentUtcOffset > c->current_utc_offset) {
		utc_offset = c->tds.currentUtcOffset;
	} else {
		utc_offset = c->current_utc_offset;
	}

	if (c->tds.flags & LEAP_61) {
		leap = 1;
	} else if (c->tds.flags & LEAP_59) {
		leap = -1;
	} else {
		leap = 0;
	}

	/* Handle leap seconds. */
	if ((leap || c->leap_set) && c->clkid == CLOCK_REALTIME) {
		/* If the clock will be stepped, the time stamp has to be the
		   target time. Ignore possible 1 second error in utc_offset. */
		if (c->servo_state == SERVO_UNLOCKED) {
			ts = tmv_to_nanoseconds(tmv_sub(ingress,
							c->master_offset));
			if (c->tds.flags & PTP_TIMESCALE)
				ts -= utc_offset * NS_PER_SEC;
		} else {
			ts = tmv_to_nanoseconds(ingress);
		}

		/* Suspend clock updates in the last second before midnight. */
		if (is_utc_ambiguous(ts)) {
			pr_info("clock update suspended due to leap second");
			return -1;
		}

		clock_leap = leap_second_status(ts, c->leap_set,
						&leap, &utc_offset);
		if (c->leap_set != clock_leap) {
			if (c->kernel_leap)
				sysclk_set_leap(clock_leap);
			else
				servo_leap(c->servo, clock_leap);
			c->leap_set = clock_leap;
		}
	}

	/* Update TAI-UTC offset of the system clock if valid and traceable. */
	if (c->tds.flags & UTC_OFF_VALID && c->tds.flags & TIME_TRACEABLE &&
	    c->utc_offset_set != utc_offset && c->clkid == CLOCK_REALTIME) {
		sysclk_set_tai_offset(utc_offset);
		c->utc_offset_set = utc_offset;
	}

	if (!(c->tds.flags & PTP_TIMESCALE))
		return 0;

	offset.tv_sec = utc_offset;
	offset.tv_nsec = 0;
	/* Local clock is UTC, but master is TAI. */
	c->master_offset = tmv_add(c->master_offset, timespec_to_tmv(offset));
	return 0;
}

static int forwarding(struct clock *c, struct port *p)
{
	enum port_state ps = port_state(p);
	switch (ps) {
	case PS_MASTER:
	case PS_GRAND_MASTER:
	case PS_SLAVE:
	case PS_UNCALIBRATED:
	case PS_PRE_MASTER:
		return 1;
	default:
		break;
	}
	if (p == c->uds_port && ps != PS_FAULTY) {
		return 1;
	}
	return 0;
}

/* public methods */

UInteger8 clock_class(struct clock *c)
{
	return c->dds.clockQuality.clockClass;
}

struct config *clock_config(struct clock *c)
{
	return c->config;
}

static int clock_add_port(struct clock *c, int phc_index,
			  enum timestamp_type timestamping,
			  struct interface *iface)
{
	struct port *p, *piter, *lastp = NULL;
	int fd, index;
	char key[16];

	if (clock_resize_pollfd(c, c->nports + 1)) {
		return -1;
	}
	p = port_open(phc_index, timestamping, ++c->last_port_number, iface, c);
	if (!p) {
		/* No need to shrink pollfd */
		return -1;
	}
	LIST_FOREACH(piter, &c->ports, list) {
		lastp = piter;
	}
	if (lastp) {
		LIST_INSERT_AFTER(lastp, p, list);
	} else {
		LIST_INSERT_HEAD(&c->ports, p, list);
	}
	c->nports++;
	clock_fda_changed(c);

	/* Remember the index to port mapping, for link status tracking. */
	fd = sk_interface_fd();
	if (fd < 0) {
		return -1;
	}
	index = sk_interface_index(fd, iface->name);
	if (index < 0) {
		close(fd);
		return -1;
	}
	snprintf(key, sizeof(key), "%d", index);
	if (hash_insert(c->index2port, key, p)) {
		pr_err("failed to add port with index %d twice!", index);
		close(fd);
		return -1;
	}
	close(fd);

#ifdef KSZ_1588_PTP
	/* The final device is the host port for master clock. */
	if (c->direct && !strchr(iface->basename, '.'))
		c->host_port = p;
#endif

	return 0;
}

static void clock_remove_port(struct clock *c, struct port *p)
{
	/* Do not call clock_resize_pollfd, it's pointless to shrink
	 * the allocated memory at this point, clock_destroy will free
	 * it all anyway. This function is usable from other parts of
	 * the code, but even then we don't mind if pollfd is larger
	 * than necessary. */
	LIST_REMOVE(p, list);
	c->nports--;
	clock_fda_changed(c);
	port_close(p);
}

struct clock *clock_create(enum clock_type type, struct config *config,
			   const char *phc_device)
{
	enum timestamp_type timestamping =
		config_get_int(config, NULL, "time_stamping");
	int fadj = 0, max_adj = 0, sw_ts = timestamping == TS_SOFTWARE ? 1 : 0;
	enum servo_type servo = config_get_int(config, NULL, "clock_servo");
	int phc_index, required_modes = 0;
	struct clock *c = &the_clock;
	struct port *p;
	unsigned char oui[OUI_LEN];
	char phc[32], *tmp;
	struct interface *iface, *udsif = &c->uds_interface;
	struct timespec ts;
	int sfl;
#ifdef KSZ_1588_PTP
	char name[40];
	char *dot;
#endif

	clock_gettime(CLOCK_REALTIME, &ts);
	srandom(ts.tv_sec ^ ts.tv_nsec);

	if (c->nports)
		clock_destroy(c);

#ifdef KSZ_1588_PTP
	if (CLOCK_TYPE_BOUNDARY == type) {
		c->transparent = config_get_int(config, NULL, "transparent");
		if (c->transparent) {
			type = CLOCK_TYPE_TRANSPARENT;
		}
	}
	c->skip_sync_check = config_get_int(config, NULL, "skip_sync_check");
	c->initialSyncReceiptTimeout = config_get_int(config, NULL, "initialSyncReceiptTimeout");
	c->waitPdelayReqInterval = config_get_int(config, NULL, "waitPdelayReqInterval");
	c->waitSyncInterval = config_get_int(config, NULL, "waitSyncInterval");
#endif
	switch (type) {
#ifdef KSZ_1588_PTP
	case CLOCK_TYPE_TRANSPARENT:
#endif
	case CLOCK_TYPE_ORDINARY:
	case CLOCK_TYPE_BOUNDARY:
		c->type = type;
		break;
	case CLOCK_TYPE_P2P:
	case CLOCK_TYPE_E2E:
	case CLOCK_TYPE_MANAGEMENT:
		return NULL;
	}

	/* Initialize the defaultDS. */
	c->dds.clockQuality.clockClass =
		config_get_int(config, NULL, "clockClass");
	c->dds.clockQuality.clockAccuracy =
		config_get_int(config, NULL, "clockAccuracy");
	c->dds.clockQuality.offsetScaledLogVariance =
		config_get_int(config, NULL, "offsetScaledLogVariance");

	c->desc.productDescription.max_symbols = 64;
	c->desc.revisionData.max_symbols = 32;
	c->desc.userDescription.max_symbols = 128;

	tmp = config_get_string(config, NULL, "productDescription");
	if (count_char(tmp, ';') != 2 ||
	    static_ptp_text_set(&c->desc.productDescription, tmp)) {
		pr_err("invalid productDescription '%s'", tmp);
		return NULL;
	}
	tmp = config_get_string(config, NULL, "revisionData");
	if (count_char(tmp, ';') != 2 ||
	    static_ptp_text_set(&c->desc.revisionData, tmp)) {
		pr_err("invalid revisionData '%s'", tmp);
		return NULL;
	}
	tmp = config_get_string(config, NULL, "userDescription");
	if (static_ptp_text_set(&c->desc.userDescription, tmp)) {
		pr_err("invalid userDescription '%s'", tmp);
		return NULL;
	}
	tmp = config_get_string(config, NULL, "manufacturerIdentity");
	if (OUI_LEN != sscanf(tmp, "%hhx:%hhx:%hhx", &oui[0], &oui[1], &oui[2])) {
		pr_err("invalid manufacturerIdentity '%s'", tmp);
		return NULL;
	}
	memcpy(c->desc.manufacturerIdentity, oui, OUI_LEN);

	c->dds.domainNumber = config_get_int(config, NULL, "domainNumber");

	if (config_get_int(config, NULL, "slaveOnly")) {
		c->dds.flags |= DDS_SLAVE_ONLY;
	}
	if (config_get_int(config, NULL, "twoStepFlag")) {
		c->dds.flags |= DDS_TWO_STEP_FLAG;
	}
	c->dds.priority1 = config_get_int(config, NULL, "priority1");
	c->dds.priority2 = config_get_int(config, NULL, "priority2");

	if (!config_get_int(config, NULL, "gmCapable") &&
	    c->dds.flags & DDS_SLAVE_ONLY) {
		pr_err("Cannot mix 1588 slaveOnly with 802.1AS !gmCapable");
		return NULL;
	}
	if (!config_get_int(config, NULL, "gmCapable") ||
	    c->dds.flags & DDS_SLAVE_ONLY) {
		c->dds.clockQuality.clockClass = 255;
	}

	if (!(c->dds.flags & DDS_TWO_STEP_FLAG)) {
		switch (timestamping) {
		case TS_SOFTWARE:
		case TS_LEGACY_HW:
			pr_err("one step is only possible "
			       "with hardware time stamping");
			return NULL;
		case TS_HARDWARE:
			timestamping = TS_ONESTEP;
			if (config_set_int(config, "time_stamping", TS_ONESTEP))
				return NULL;
			break;
		case TS_ONESTEP:
			break;
		}
	}

	/* Check the time stamping mode on each interface. */
	switch (timestamping) {
	case TS_SOFTWARE:
		required_modes |= SOF_TIMESTAMPING_TX_SOFTWARE |
			SOF_TIMESTAMPING_RX_SOFTWARE |
			SOF_TIMESTAMPING_SOFTWARE;
		break;
	case TS_LEGACY_HW:
		required_modes |= SOF_TIMESTAMPING_TX_HARDWARE |
			SOF_TIMESTAMPING_RX_HARDWARE |
			SOF_TIMESTAMPING_SYS_HARDWARE;
		break;
	case TS_HARDWARE:
	case TS_ONESTEP:
		required_modes |= SOF_TIMESTAMPING_TX_HARDWARE |
			SOF_TIMESTAMPING_RX_HARDWARE |
			SOF_TIMESTAMPING_RAW_HARDWARE;
		break;
	}
	STAILQ_FOREACH(iface, &config->interfaces, list) {
		if (iface->ts_info.valid &&
		    ((iface->ts_info.so_timestamping & required_modes) != required_modes)) {
			pr_err("interface '%s' does not support "
			       "requested timestamping mode", iface->name);
			return NULL;
		}
	}

	iface = STAILQ_FIRST(&config->interfaces);

	/* determine PHC Clock index */
	if (config_get_int(config, NULL, "free_running")) {
		phc_index = -1;
	} else if (timestamping == TS_SOFTWARE || timestamping == TS_LEGACY_HW) {
		phc_index = -1;
	} else if (phc_device) {
		if (1 != sscanf(phc_device, "/dev/ptp%d", &phc_index)) {
			pr_err("bad ptp device string");
			return NULL;
		}
	} else if (iface->ts_info.valid) {
		phc_index = iface->ts_info.phc_index;
	} else {
		pr_err("PTP device not specified and automatic determination"
		       " is not supported. Please specify PTP device.");
		return NULL;
	}
	if (phc_index >= 0) {
		pr_info("selected /dev/ptp%d as PTP clock", phc_index);
	}

#ifdef KSZ_1588_PTP
	strncpy(name, iface->name, sizeof(name));
	dot = strchr(name, '.');
	if (dot)
		*dot = '\0';
	if (generate_clock_identity(&c->dds.clockIdentity, name)) {
#else
	if (generate_clock_identity(&c->dds.clockIdentity, iface->name)) {
#endif
		pr_err("failed to generate a clock identity");
		return NULL;
	}

	/* Configure the UDS. */
	snprintf(udsif->name, sizeof(udsif->name), "%s",
		 config_get_string(config, NULL, "uds_address"));
	if (config_set_section_int(config, udsif->name,
				   "announceReceiptTimeout", 0)) {
		return NULL;
	}
	if (config_set_section_int(config, udsif->name,
				    "delay_mechanism", DM_AUTO)) {
		return NULL;
	}
	if (config_set_section_int(config, udsif->name,
				    "network_transport", TRANS_UDS)) {
		return NULL;
	}
	if (config_set_section_int(config, udsif->name, "delay_filter_length", 1)) {
		return NULL;
	}

	c->config = config;
	c->free_running = config_get_int(config, NULL, "free_running");
	c->freq_est_interval = config_get_int(config, NULL, "freq_est_interval");
	c->grand_master_capable = config_get_int(config, NULL, "gmCapable");
	c->kernel_leap = config_get_int(config, NULL, "kernel_leap");
	c->utc_offset = c->current_utc_offset = config_get_int(config, NULL, "utc_offset");
	c->time_source = config_get_int(config, NULL, "timeSource");

	if (c->free_running) {
		c->clkid = CLOCK_INVALID;
		if (timestamping == TS_SOFTWARE || timestamping == TS_LEGACY_HW) {
			c->utc_timescale = 1;
		}
	} else if (phc_index >= 0) {
		snprintf(phc, sizeof(phc), "/dev/ptp%d", phc_index);
		c->clkid = phc_open(phc);
		if (c->clkid == CLOCK_INVALID) {
			pr_err("Failed to open %s: %m", phc);
			return NULL;
		}
		max_adj = phc_max_adj(c->clkid);
		if (!max_adj) {
			pr_err("clock is not adjustable");
			return NULL;
		}
		clockadj_init(c->clkid);
	} else {
		c->clkid = CLOCK_REALTIME;
		c->utc_timescale = 1;
		clockadj_init(c->clkid);
		max_adj = sysclk_max_freq();
		sysclk_set_leap(0);
	}
	c->utc_offset_set = 0;
	c->leap_set = 0;
	c->time_flags = c->utc_timescale ? 0 : PTP_TIMESCALE;

	if (c->clkid != CLOCK_INVALID) {
		fadj = (int) clockadj_get_freq(c->clkid);
		/* Due to a bug in older kernels, the reading may silently fail
		   and return 0. Set the frequency back to make sure fadj is
		   the actual frequency of the clock. */
		clockadj_set_freq(c->clkid, fadj);
	}
	c->servo = servo_create(c->config, servo, -fadj, max_adj, sw_ts);
	if (!c->servo) {
		pr_err("Failed to create clock servo");
		return NULL;
	}
	c->servo_state = SERVO_UNLOCKED;
	c->servo_type = servo;
	c->tsproc = tsproc_create(config_get_int(config, NULL, "tsproc_mode"),
				  config_get_int(config, NULL, "delay_filter"),
				  config_get_int(config, NULL, "delay_filter_length"));
	if (!c->tsproc) {
		pr_err("Failed to create time stamp processor");
		return NULL;
	}
	c->nrr = 1.0;
	c->stats_interval = config_get_int(config, NULL, "summary_interval");
	c->stats.offset = stats_create();
	c->stats.freq = stats_create();
	c->stats.delay = stats_create();
	if (!c->stats.offset || !c->stats.freq || !c->stats.delay) {
		pr_err("failed to create stats");
		return NULL;
	}
	sfl = config_get_int(config, NULL, "sanity_freq_limit");
	if (sfl) {
		c->sanity_check = clockcheck_create(sfl);
		if (!c->sanity_check) {
			pr_err("Failed to create clock sanity check");
			return NULL;
		}
	}

	/* Initialize the parentDS. */
	clock_update_grandmaster(c);
	c->dad.pds.parentStats                           = 0;
	c->dad.pds.observedParentOffsetScaledLogVariance = 0xffff;
	c->dad.pds.observedParentClockPhaseChangeRate    = 0x7fffffff;
	c->dad.ptl = c->ptl;

	clock_sync_interval(c, 0);

	LIST_INIT(&c->subscribers);
	LIST_INIT(&c->ports);
	c->last_port_number = 0;

	if (clock_resize_pollfd(c, 0)) {
		pr_err("failed to allocate pollfd");
		return NULL;
	}

	/* Open a RT netlink socket. */
	c->pollfd[0].fd = rtnl_open();
	c->pollfd[0].events = POLLIN|POLLPRI;

	/* Create the UDS interface. */
	c->uds_port = port_open(phc_index, timestamping, 0, udsif, c);
	if (!c->uds_port) {
		pr_err("failed to open the UDS port");
		return NULL;
	}
	clock_fda_changed(c);

	c->index2port = hash_create();
	if (!c->index2port) {
		pr_err("failed create index-to-port hash table");
		return NULL;
	}
	/* Create the ports. */
	STAILQ_FOREACH(iface, &config->interfaces, list) {

#ifdef KSZ_1588_PTP
		if (!c->direct && strchr(iface->name, '.'))
			c->direct = 1;
#endif
		if (clock_add_port(c, phc_index, timestamping, iface)) {
			pr_err("failed to open port %s", iface->name);
			return NULL;
		}
	}

	c->dds.numberPorts = c->nports;

	LIST_FOREACH(p, &c->ports, list) {

#ifdef KSZ_1588_PTP
		if (c->host_port && p != c->host_port)
			port_set_host_port(p, c->host_port);
#endif
		port_dispatch(p, EV_INITIALIZE, 0);
	}
	port_dispatch(c->uds_port, EV_INITIALIZE, 0);
	if (c->pollfd[0].fd >= 0) {
		rtnl_link_query(c->pollfd[0].fd);
	}
#ifdef KSZ_1588_PTP
/* Defined in ksz_ptp.h. */
#define PTP_CAN_RX_TIMESTAMP		(1 << 0)
#define PTP_KNOW_ABOUT_LATENCY		(1 << 1)
#define PTP_HAVE_MULT_DEVICES		(1 << 2)
#define PTP_HAVE_MULT_PORTS		(1 << 3)
#define PTP_KNOW_ABOUT_MULT_PORTS	(1 << 4)
#define PTP_USE_RESERVED_FIELDS		(1 << 5)
#define PTP_SEPARATE_PATHS		(1 << 6)
#define PTP_USE_ONE_STEP		(1 << 7)

	p = LIST_FIRST(&c->ports);
	c->dm = config_get_int(config, p->name, "delay_mechanism");
	c->ieee_c37_238 = config_get_int(config, NULL, "c37_238");
	c->use_one_step = config_get_int(config, NULL, "use_one_step");
	c->use_2_step_pdelay = config_get_int(config, NULL,
					      "use_2_step_pdelay");
	c->master_port = 0;
	do {
		int cap;

		if (!c->direct && c->nports > 1)
			c->direct = 1;
		cap = PTP_CAN_RX_TIMESTAMP;
		if (c->direct)
			cap |= PTP_HAVE_MULT_DEVICES;
		cap |= PTP_KNOW_ABOUT_MULT_PORTS;
		if (c->use_one_step && (c->dds.flags & DDS_TWO_STEP_FLAG))
			cap |= PTP_USE_ONE_STEP;
		p = LIST_FIRST(&c->ports);
		port_init_ptp(p, cap, &c->drift, &c->version,
			&c->port_cnt, &c->access_delay);
	} while (0);
	c->port_mask = (1 << c->port_cnt) - 1;
	LIST_FOREACH(p, &c->ports, list) {
		port_get_info(p);
	}
#endif
	return c;
}

struct dataset *clock_best_foreign(struct clock *c)
{
	return c->best ? &c->best->dataset : NULL;
}

struct port *clock_best_port(struct clock *c)
{
	return c->best ? c->best->port : NULL;
}

struct dataset *clock_default_ds(struct clock *c)
{
	struct dataset *out = &c->default_dataset;
	struct defaultDS *in = &c->dds;

	out->priority1              = in->priority1;
	out->identity               = in->clockIdentity;
	out->quality                = in->clockQuality;
	out->priority2              = in->priority2;
	out->stepsRemoved           = 0;
	out->sender.clockIdentity   = in->clockIdentity;
	out->sender.portNumber      = 0;
	out->receiver.clockIdentity = in->clockIdentity;
	out->receiver.portNumber    = 0;

	return out;
}

UInteger8 clock_domain_number(struct clock *c)
{
	return c->dds.domainNumber;
}

struct port *clock_first_port(struct clock *c)
{
	return LIST_FIRST(&c->ports);
}

static int dbg_phase_change;

void clock_follow_up_info(struct clock *c, struct follow_up_info_tlv *f)
{
#if 0
if (dbg_phase_change)
printf("%d %u %d %u.%llu\n", f->cumulativeScaledRateOffset,
f->gmTimeBaseIndicator, f->scaledLastGmPhaseChange,
f->lastGmPhaseChange.nanoseconds_msb,
f->lastGmPhaseChange.nanoseconds_lsb);
#endif
	c->status.cumulativeScaledRateOffset = f->cumulativeScaledRateOffset;
	c->status.scaledLastGmPhaseChange = f->scaledLastGmPhaseChange;
	c->status.gmTimeBaseIndicator = f->gmTimeBaseIndicator;
	memcpy(&c->status.lastGmPhaseChange, &f->lastGmPhaseChange,
	       sizeof(c->status.lastGmPhaseChange));
}

void clock_get_follow_up_info(struct clock *c, struct follow_up_info_tlv *f)
{
	f->cumulativeScaledRateOffset =
		(Integer32) (c->status.cumulativeScaledRateOffset +
			     c->nrr * POW2_41 - POW2_41);
#if 0
if (dbg_phase_change && !f->cumulativeScaledRateOffset) {
printf(" phase change: %d %lf\n", c->status.cumulativeScaledRateOffset, c->nrr);
dbg_phase_change = 0;
}
#endif
	f->scaledLastGmPhaseChange = c->status.scaledLastGmPhaseChange;
	f->gmTimeBaseIndicator = c->status.gmTimeBaseIndicator;
	memcpy(&f->lastGmPhaseChange, &c->status.lastGmPhaseChange,
	       sizeof(c->status.lastGmPhaseChange));
}

void clock_set_follow_up_info(struct clock *c)
{
	struct timespec now;
	uint64_t ns;

	clock_gettime(c->clkid, &now);
	ns = now.tv_sec;
	ns *= NS_PER_SEC;
	ns += now.tv_nsec;
	c->status.cumulativeScaledRateOffset = 0;
	c->status.scaledLastGmPhaseChange = 0;
	c->status.gmTimeBaseIndicator++;
	c->status.lastGmPhaseChange.nanoseconds_msb = 0;
	c->status.lastGmPhaseChange.nanoseconds_lsb = ns;
	c->status.lastGmPhaseChange.fractional_nanoseconds = 0;
}

int clock_gm_capable(struct clock *c)
{
	return c->grand_master_capable && c->dds.priority1 < 255;
}

struct ClockIdentity clock_identity(struct clock *c)
{
	return c->dds.clockIdentity;
}

static int clock_resize_pollfd(struct clock *c, int new_nports)
{
	struct pollfd *new_pollfd;

	/*
	 * Need to allocate one descriptor for RT netlink and one
	 * whole extra block of fds for UDS.
	 */
	new_pollfd = realloc(c->pollfd,
			     (1 + (new_nports + 1) * N_CLOCK_PFD) *
			     sizeof(struct pollfd));
	if (!new_pollfd)
		return -1;
	c->pollfd = new_pollfd;
	return 0;
}

static void clock_fill_pollfd(struct pollfd *dest, struct port *p)
{
	struct fdarray *fda;
	int i;

	fda = port_fda(p);
	for (i = 0; i < N_POLLFD; i++) {
		dest[i].fd = fda->fd[i];
		dest[i].events = POLLIN|POLLPRI;
#ifdef KSZ_1588_PTP
		dest[i].events |= POLLERR;
#endif
	}
	dest[i].fd = port_fault_fd(p);
	dest[i].events = POLLIN|POLLPRI;
}

static void clock_check_pollfd(struct clock *c)
{
	struct port *p;
	struct pollfd *dest = c->pollfd + 1;

	if (c->pollfd_valid)
		return;
	LIST_FOREACH(p, &c->ports, list) {
		clock_fill_pollfd(dest, p);
		dest += N_CLOCK_PFD;
	}
	clock_fill_pollfd(dest, c->uds_port);
	c->pollfd_valid = 1;
}

void clock_fda_changed(struct clock *c)
{
	c->pollfd_valid = 0;
}

static int clock_do_forward_mgmt(struct clock *c,
				 struct port *in, struct port *out,
				 struct ptp_message *msg, int *pre_sent)
{
	if (in == out || !forwarding(c, out))
		return 0;
	if (!*pre_sent) {
		/* delay calling msg_pre_send until
		 * actually forwarding */
		msg_pre_send(msg);
		*pre_sent = 1;
	}
	return port_forward(out, msg);
}

static void clock_forward_mgmt_msg(struct clock *c, struct port *p, struct ptp_message *msg)
{
	struct port *piter;
	int pdulen = 0, msg_ready = 0;

	if (forwarding(c, p) && msg->management.boundaryHops) {
		pdulen = msg->header.messageLength;
		msg->management.boundaryHops--;
		LIST_FOREACH(piter, &c->ports, list) {
			if (clock_do_forward_mgmt(c, p, piter, msg, &msg_ready))
				pr_err("port %d: management forward failed",
				       port_number(piter));
		}
		if (clock_do_forward_mgmt(c, p, c->uds_port, msg, &msg_ready))
			pr_err("uds port: management forward failed");
		if (msg_ready) {
			msg_post_recv(msg, pdulen);
			msg->management.boundaryHops++;
		}
	}
}

int clock_manage(struct clock *c, struct port *p, struct ptp_message *msg)
{
	int changed = 0, res, answers;
	struct port *piter;
	struct management_tlv *mgt;
	struct ClockIdentity *tcid, wildcard = {
		{0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff}
	};

	/* Forward this message out all eligible ports. */
	clock_forward_mgmt_msg(c, p, msg);

	/* Apply this message to the local clock and ports. */
	tcid = &msg->management.targetPortIdentity.clockIdentity;
	if (!cid_eq(tcid, &wildcard) && !cid_eq(tcid, &c->dds.clockIdentity)) {
		return changed;
	}
#ifndef KSZ_1588_PTP
	if (msg->tlv_count != 1) {
		return changed;
	}
#endif
	mgt = (struct management_tlv *) msg->management.suffix;

	/*
	  The correct length according to the management ID is checked
	  in tlv.c, but management TLVs with empty bodies are also
	  received successfully to support GETs and CMDs. At this
	  point the TLV either has the correct length or length 2.
	*/
	switch (management_action(msg)) {
	case GET:
		if (clock_management_get_response(c, p, mgt->id, msg))
			return changed;
		break;
	case SET:
		if (mgt->length == 2 && mgt->id != TLV_NULL_MANAGEMENT) {
#if 1
if (mgt->id != TLV_DISABLE_PORT && mgt->id != TLV_ENABLE_PORT) {
#endif
			clock_management_send_error(p, msg, TLV_WRONG_LENGTH);
			return changed;
#if 1
}
#endif
		}
		if (p != c->uds_port) {
			/* Sorry, only allowed on the UDS port. */
			clock_management_send_error(p, msg, TLV_NOT_SUPPORTED);
			return changed;
		}
		if (clock_management_set(c, p, mgt->id, msg, &changed))
			return changed;
		break;
	case COMMAND:
		break;
	default:
		return changed;
	}

	switch (mgt->id) {
	case TLV_PORT_PROPERTIES_NP:
		if (p != c->uds_port) {
			/* Only the UDS port allowed. */
			clock_management_send_error(p, msg, TLV_NOT_SUPPORTED);
			return 0;
		}
	}

	switch (mgt->id) {
	case TLV_USER_DESCRIPTION:
	case TLV_SAVE_IN_NON_VOLATILE_STORAGE:
	case TLV_RESET_NON_VOLATILE_STORAGE:
	case TLV_INITIALIZE:
	case TLV_FAULT_LOG:
	case TLV_FAULT_LOG_RESET:
	case TLV_DEFAULT_DATA_SET:
	case TLV_CURRENT_DATA_SET:
	case TLV_PARENT_DATA_SET:
	case TLV_TIME_PROPERTIES_DATA_SET:
	case TLV_PRIORITY1:
	case TLV_PRIORITY2:
	case TLV_DOMAIN:
	case TLV_SLAVE_ONLY:
	case TLV_TIME:
	case TLV_CLOCK_ACCURACY:
	case TLV_UTC_PROPERTIES:
	case TLV_TRACEABILITY_PROPERTIES:
	case TLV_TIMESCALE_PROPERTIES:
	case TLV_PATH_TRACE_LIST:
	case TLV_PATH_TRACE_ENABLE:
	case TLV_GRANDMASTER_CLUSTER_TABLE:
	case TLV_ACCEPTABLE_MASTER_TABLE:
	case TLV_ACCEPTABLE_MASTER_MAX_TABLE_SIZE:
	case TLV_ALTERNATE_TIME_OFFSET_ENABLE:
	case TLV_ALTERNATE_TIME_OFFSET_NAME:
	case TLV_ALTERNATE_TIME_OFFSET_MAX_KEY:
	case TLV_ALTERNATE_TIME_OFFSET_PROPERTIES:
	case TLV_TRANSPARENT_CLOCK_DEFAULT_DATA_SET:
	case TLV_PRIMARY_DOMAIN:
	case TLV_TIME_STATUS_NP:
	case TLV_GRANDMASTER_SETTINGS_NP:
	case TLV_SUBSCRIBE_EVENTS_NP:
		clock_management_send_error(p, msg, TLV_NOT_SUPPORTED);
		break;
	default:
		answers = 0;
		LIST_FOREACH(piter, &c->ports, list) {
			res = port_manage(piter, p, msg);
			if (res < 0)
				return changed;
			if (res > 0)
				answers++;
		}
		if (!answers) {
			/* IEEE 1588 Interpretation #21 suggests to use
			 * TLV_WRONG_VALUE for ports that do not exist */
			clock_management_send_error(p, msg, TLV_WRONG_VALUE);
		}
		break;
	}
	return changed;
}

void clock_notify_event(struct clock *c, enum notification event)
{
	struct port *uds = c->uds_port;
	struct PortIdentity pid = port_identity(uds);
	struct ptp_message *msg;
	UInteger16 msg_len;
	int id;

	switch (event) {
	/* set id */
	default:
		return;
	}
	/* targetPortIdentity and sequenceId will be filled by
	 * clock_send_notification */
	msg = port_management_notify(pid, uds);
	if (!msg)
		return;
	if (!clock_management_fill_response(c, NULL, NULL, msg, id))
		goto err;
	msg_len = msg->header.messageLength;
	if (msg_pre_send(msg))
		goto err;
	clock_send_notification(c, msg, msg_len, event);
err:
	msg_put(msg);
}

struct parent_ds *clock_parent_ds(struct clock *c)
{
	return &c->dad;
}

struct PortIdentity clock_parent_identity(struct clock *c)
{
	return c->dad.pds.parentPortIdentity;
}

int clock_poll(struct clock *c)
{
	int cnt, i;
	enum fsm_event event;
	struct pollfd *cur;
	struct port *p;

	clock_check_pollfd(c);
	cnt = poll(c->pollfd, 1 + (c->nports + 1) * N_CLOCK_PFD, -1);
	if (cnt < 0) {
		if (EINTR == errno) {
			return 0;
		} else {
			pr_emerg("poll failed");
			return -1;
		}
	} else if (!cnt) {
		return 0;
	}

	/* Check the RT netlink. */
	cur = c->pollfd;
	if (cur->revents & (POLLIN|POLLPRI)) {
		rtnl_link_status(cur->fd, clock_link_status, c);
	}

	cur++;
	LIST_FOREACH(p, &c->ports, list) {
		/* Let the ports handle their events. */
		for (i = 0; i < N_POLLFD; i++) {
#ifdef KSZ_1588_PTP
			if (cur[i].revents & (POLLERR)) {
				event = port_tx_event(p, i);
#if 1
				cur[i].revents &= ~(POLLIN|POLLPRI);
#endif

				/*
				 * Errors are returned all the time when the
				 * the device is down.  Still the stack cannot
				 * recover whe using L2.
				 */
				if (EV_POWERUP == event) {
					sleep(2);
					break;
				}
			}
#endif
			if (cur[i].revents & (POLLIN|POLLPRI)) {
				event = port_event(p, i);
				if (EV_STATE_DECISION_EVENT == event)
					c->sde = 1;
				port_dispatch(p, event, 0);

#ifdef KSZ_1588_PTP
				/* Only needed for state decision. */
				if (!transparent_clock(c) ||
				    (clock_master_lost(c)))
#endif
				if (EV_ANNOUNCE_RECEIPT_TIMEOUT_EXPIRES == event)
					c->sde = 1;
				/* Clear any fault after a little while. */
				if (PS_FAULTY == port_state(p)) {
					clock_fault_timeout(p, 1);
					break;
				}
			}
		}

		/*
		 * When the fault timer expires we clear the fault,
		 * but only if the link is up.
		 */
		if (cur[N_POLLFD].revents & (POLLIN|POLLPRI)) {
			clock_fault_timeout(p, 0);
			if (port_link_status_get(p)) {
				port_dispatch(p, EV_FAULT_CLEARED, 0);
			}
		}

		cur += N_CLOCK_PFD;
	}

	/* Check the UDS port. */
	for (i = 0; i < N_POLLFD; i++) {
		if (cur[i].revents & (POLLIN|POLLPRI)) {
			event = port_event(c->uds_port, i);
			if (EV_STATE_DECISION_EVENT == event)
				c->sde = 1;
		}
	}

	if (c->sde) {
		handle_state_decision_event(c);
		c->sde = 0;
	}
	clock_prune_subscriptions(c);
	return 0;
}

void clock_path_delay(struct clock *c, tmv_t req, tmv_t rx)
{
#ifdef KSZ_1588_PTP
	/* Wait until syntonization to start calculating path delay. */
	if (c->servo_state == SERVO_UNLOCKED) {

		/* Need valid indication in clock_synchronize(). */
		tsproc_set_delay(c->tsproc, 0);
		return;
	}
#endif
	tsproc_up_ts(c->tsproc, req, rx);

	if (tsproc_update_delay(c->tsproc, &c->path_delay))
		return;

	c->cur.meanPathDelay = tmv_to_TimeInterval(c->path_delay);

	if (c->stats.delay)
		stats_add_value(c->stats.delay,
				tmv_to_nanoseconds(c->path_delay));
}

void clock_peer_delay(struct clock *c, tmv_t ppd, tmv_t req, tmv_t rx,
		      double nrr)
{
	c->path_delay = ppd;
	c->nrr = nrr;

	tsproc_set_delay(c->tsproc, ppd);
	tsproc_up_ts(c->tsproc, req, rx);

	if (c->stats.delay)
		stats_add_value(c->stats.delay, tmv_to_nanoseconds(ppd));
}

int clock_slave_only(struct clock *c)
{
	return c->dds.flags & DDS_SLAVE_ONLY;
}

UInteger16 clock_steps_removed(struct clock *c)
{
	return c->cur.stepsRemoved;
}

int clock_switch_phc(struct clock *c, int phc_index)
{
	struct servo *servo;
	int fadj, max_adj;
	clockid_t clkid;
	char phc[32];

	snprintf(phc, sizeof(phc), "/dev/ptp%d", phc_index);
	clkid = phc_open(phc);
	if (clkid == CLOCK_INVALID) {
		pr_err("Switching PHC, failed to open %s: %m", phc);
		return -1;
	}
	max_adj = phc_max_adj(clkid);
	if (!max_adj) {
		pr_err("Switching PHC, clock is not adjustable");
		phc_close(clkid);
		return -1;
	}
	fadj = (int) clockadj_get_freq(clkid);
	clockadj_set_freq(clkid, fadj);
	servo = servo_create(c->config, c->servo_type, -fadj, max_adj, 0);
	if (!servo) {
		pr_err("Switching PHC, failed to create clock servo");
		phc_close(clkid);
		return -1;
	}
	phc_close(c->clkid);
	servo_destroy(c->servo);
	c->clkid = clkid;
	c->servo = servo;
	c->servo_state = SERVO_UNLOCKED;
	return 0;
}

enum servo_state clock_synchronize(struct clock *c, tmv_t ingress, tmv_t origin)
{
	double adj, weight;
	enum servo_state state = SERVO_UNLOCKED;

#ifdef KSZ_1588_PTP
	if (c->servo_state >= SERVO_LOCKED) {
		tmv_t interval = origin - c->origin_ts;

		if (interval > 0 && interval < c->min_sync_interval)
			return c->servo_state;
	}
	state = c->servo_state;
	c->origin_ts = origin;
#endif
	c->ingress_ts = ingress;

	tsproc_down_ts(c->tsproc, origin, ingress);

	if (tsproc_update_offset(c->tsproc, &c->master_offset, &weight))
		return state;

	if (clock_utc_correct(c, ingress))
		return c->servo_state;

	c->cur.offsetFromMaster = tmv_to_TimeInterval(c->master_offset);

	if (c->free_running)
		return clock_no_adjust(c, ingress, origin);

	adj = servo_sample(c->servo, tmv_to_nanoseconds(c->master_offset),
			   tmv_to_nanoseconds(ingress), weight, &state);
#ifdef KSZ_1588_PTP
	/*
	 * E2E needs path delay to complete offset from master, but path delay
	 * is accurate only after syntonization.
	 */
	if (c->dm == DM_E2E && !c->path_delay &&
	    SERVO_UNLOCKED == c->servo_state && state != c->servo_state &&
	    state != SERVO_LOCKING)
		state = SERVO_LOCKING;
#endif
	c->servo_state = state;

	if (c->stats.max_count > 1) {
		clock_stats_update(&c->stats,
				   tmv_to_nanoseconds(c->master_offset), adj);
	} else {
		pr_info("master offset %10" PRId64 " s%d freq %+7.0f "
			"path delay %9" PRId64,
			tmv_to_nanoseconds(c->master_offset), state, adj,
			tmv_to_nanoseconds(c->path_delay));
	}

	tsproc_set_clock_rate_ratio(c->tsproc, clock_rate_ratio(c));

	switch (state) {
	case SERVO_UNLOCKED:
		break;
#ifdef KSZ_1588_PTP
	case SERVO_LOCKING:
		clockadj_set_freq(c->clkid, -adj);
		break;
#endif
	case SERVO_JUMP:
		clockadj_set_freq(c->clkid, -adj);
		clockadj_step(c->clkid, -tmv_to_nanoseconds(c->master_offset));
		c->ingress_ts = tmv_zero();
		if (c->sanity_check) {
			clockcheck_set_freq(c->sanity_check, -adj);
			clockcheck_step(c->sanity_check,
					-tmv_to_nanoseconds(c->master_offset));
		}
		tsproc_reset(c->tsproc, 0);
		break;
	case SERVO_LOCKED:
		clockadj_set_freq(c->clkid, -adj);
		if (c->clkid == CLOCK_REALTIME)
			sysclk_set_sync();
		if (c->sanity_check)
			clockcheck_set_freq(c->sanity_check, -adj);
		break;
	}
	return state;
}

void clock_sync_interval(struct clock *c, int n)
{
	int shift;

	shift = c->freq_est_interval - n;
	if (shift < 0)
		shift = 0;
	else if (shift >= sizeof(int) * 8) {
		shift = sizeof(int) * 8 - 1;
		pr_warning("freq_est_interval is too long");
	}
	c->fest.max_count = (1 << shift);

	shift = c->stats_interval - n;
	if (shift < 0)
		shift = 0;
	else if (shift >= sizeof(int) * 8) {
		shift = sizeof(int) * 8 - 1;
		pr_warning("summary_interval is too long");
	}
	c->stats.max_count = (1 << shift);

	servo_sync_interval(c->servo, n < 0 ? 1.0 / (1 << -n) : 1 << n);
}

struct timePropertiesDS *clock_time_properties(struct clock *c)
{
	return &c->tds;
}

void clock_update_time_properties(struct clock *c, struct timePropertiesDS tds)
{
	c->tds = tds;
}

static void handle_state_decision_event(struct clock *c)
{
	struct foreign_clock *best = NULL, *fc;
	struct ClockIdentity best_id;
	struct port *piter;
	int fresh_best = 0;
	int n = 0;
	int update_grandmaster = 0;

	LIST_FOREACH(piter, &c->ports, list) {
		fc = port_compute_best(piter);
		if (!fc)
			continue;
		if (!best || dscmp(&fc->dataset, &best->dataset) > 0)
			best = fc;
	}

#ifdef KSZ_1588_PTP
	/* Above code only checks for foreign clocks. */
	if (best) {
		if (dscmp(clock_default_ds(c), &best->dataset) > 0)
			best = NULL;
	}
#endif
	if (best) {
		best_id = best->dataset.identity;
	} else {
		best_id = c->dds.clockIdentity;
	}

	pr_notice("selected best master clock %s",
		  cid2str(&best_id));

	if (!cid_eq(&best_id, &c->best_id)) {
		clock_freq_est_reset(c);
		tsproc_reset(c->tsproc, 1);
#ifdef KSZ_1588_PTP
		if (c->dm == DM_NONE)
			tsproc_set_delay(c->tsproc, 0);
#endif
		c->ingress_ts = tmv_zero();
		c->path_delay = 0;
		c->servo_state = SERVO_UNLOCKED;
		c->nrr = 1.0;
		fresh_best = 1;
	}
	update_grandmaster = fresh_best;

	c->best = best;
	c->best_id = best_id;

	LIST_FOREACH(piter, &c->ports, list) {
		enum port_state ps;
		enum fsm_event event;
		if (skip_host_port(c, piter))
			continue;
		ps = bmc_state_decision(c, piter);
		n++;
		switch (ps) {
		case PS_LISTENING:
			event = EV_NONE;
			break;
		case PS_GRAND_MASTER:
#ifdef KSZ_1588_PTP
#if 1
			if (!new_state(piter)) {
				event = EV_RS_GRAND_MASTER;
				break;
			}
#endif
			pr_notice("%hu: assuming the grand master role", n);
#else
			pr_notice("assuming the grand master role");
#endif
#ifdef KSZ_1588_PTP
			if (update_grandmaster) {
				update_grandmaster = 0;
#endif
			clock_update_grandmaster(c);
#ifdef KSZ_1588_PTP
				clock_update_port_grandmaster(c);
			}
#endif
			event = EV_RS_GRAND_MASTER;
			break;
		case PS_MASTER:
			event = EV_RS_MASTER;
			break;
		case PS_PASSIVE:
			event = EV_RS_PASSIVE;
			break;
		case PS_SLAVE:
			clock_update_slave(c);
#ifdef KSZ_1588_PTP
			clock_update_port_grandmaster(c);
#endif
			event = EV_RS_SLAVE;
			break;
		default:
			event = EV_FAULT_DETECTED;
			break;
		}
		port_dispatch(piter, event, fresh_best);
	}
}

struct clock_description *clock_description(struct clock *c)
{
	return &c->desc;
}

enum clock_type clock_type(struct clock *c)
{
	return c->type;
}

void clock_check_ts(struct clock *c, struct timespec ts)
{
	if (c->sanity_check &&
	    clockcheck_sample(c->sanity_check,
			      ts.tv_sec * NS_PER_SEC + ts.tv_nsec)) {
		servo_reset(c->servo);
	}
}

double clock_rate_ratio(struct clock *c)
{
	return servo_rate_ratio(c->servo);
}

#ifdef KSZ_1588_PTP
int clock_one_step(struct clock *c)
{
	int one_step = c->use_one_step || !(c->dds.flags & DDS_TWO_STEP_FLAG);

	return one_step;
}

int clock_two_step_pdelay(struct clock *c)
{
	int two_step = (c->dds.flags & DDS_TWO_STEP_FLAG);

	if (two_step && c->use_one_step)
		two_step = c->use_2_step_pdelay;
	return two_step;
}

int clock_two_step(struct clock *c)
{
	return (c->dds.flags & DDS_TWO_STEP_FLAG);
}

int clock_c37_238(struct clock *c)
{
	return (1 == c->ieee_c37_238);
}

int all_ports(struct clock *c)
{
	return c->port_mask;
}

int need_dest_port(struct clock *c)
{
	return (!c->direct);
}

int need_stop_forwarding(struct clock *c)
{
	return (1 == c->ieee_c37_238);
}

int boundary_clock(struct clock *c)
{
	return (0 == c->transparent && c->nports > 1);
}

int transparent_clock(struct clock *c)
{
	return (1 == c->transparent && c->nports > 1);
}

void set_transparent_clock(struct clock *c, int transparent)
{
	c->transparent = transparent;
}

UInteger8 get_hw_version(struct clock *c)
{
	return c->version;
}

UInteger8 get_port_cnt(struct clock *c)
{
	return c->port_cnt;
}

UInteger32 get_min_sync_interval(struct clock *c)
{
	return c->min_sync_interval;
}

void set_min_sync_interval(struct clock *c, UInteger32 interval)
{
	c->min_sync_interval = interval;
}

int get_master_port(struct clock *c)
{
	return c->master_port;
}

struct port *get_slave_port(struct clock *c)
{
	return c->slave_port;
}

void set_master_port(struct clock *c, int p)
{
	c->master_port = p;
}

void set_slave_port(struct clock *c, struct port *p)
{
#if 0
if (p)
printf("%s %p\n", __func__, p);
#endif
	c->slave_port = p;
}

int is_host_port(struct clock *c, struct port *p)
{
	int ret = TRUE;

	if (c->transparent && c->host_port && p != c->host_port)
		ret = FALSE;
	return ret;
}

int is_peer_port(struct clock *c, struct port *p)
{
	int ret = TRUE;

	if (c->transparent && c->host_port && p == c->host_port)
		ret = FALSE;
	return ret;
}

int skip_host_port(struct clock *c, struct port *p)
{
	int ret = FALSE;

	if (c->transparent && c->host_port && p == c->host_port)
		ret = TRUE;
	return ret;
}

void update_dev_cnt(struct clock *c, int cnt)
{
	c->dev_cnt += cnt;
}

int get_dev_cnt(struct clock *c)
{
	return c->dev_cnt;
}

struct port *get_port(struct clock *c, int port)
{
	struct port *p;
	int i = 1;

	LIST_FOREACH(p, &c->ports, list) {
		if (port_matched(p, port))
			return p;
		i++;
	}
	return NULL;
}

void set_master_utc_offset(struct clock *c, int offset)
{
	c->utc_offset = offset;
	c->time_flags |= UTC_OFF_VALID;
	c->tds.flags |= UTC_OFF_VALID;
}

int clock_syntonized(struct clock *c)
{
	if (c->servo_state > SERVO_UNLOCKED || c->dm == DM_P2P)
		return TRUE;
	else
		return FALSE;
}

void clock_set_port_state(struct clock *c, enum fsm_event event)
{
	struct port *p;

	LIST_FOREACH(p, &c->ports, list) {
		if (p != c->host_port && p != c->dispatch)
			port_set_port_state(p, event);
	}
}

int is_slave_port(struct clock *c, struct port *p)
{
	return c->slave_port == p;
}

int port_dispatched(struct clock *c)
{
	return c->dispatch != NULL;
}

void clock_port_dispatch(struct clock *c, struct port *p)
{
	c->dispatch = p;
}

void clock_update_port_grandmaster(struct clock *c)
{
	struct port *p;
	int i = 1;

dbg_phase_change = 1;
	LIST_FOREACH(p, &c->ports, list) {
		port_update_grandmaster(p);
		i++;
	}
}

void clock_update_state(struct clock *c)
{
	handle_state_decision_event(c);
}

int skip_sync_check(struct clock *c)
{
	return c->skip_sync_check;
}

int get_initialSyncReceiptTimeout(struct clock *c)
{
	return c->initialSyncReceiptTimeout;
}

int get_waitPdelayReqInterval(struct clock *c)
{
	return c->waitPdelayReqInterval;
}

int get_waitSyncInterval(struct clock *c)
{
	return c->waitSyncInterval;
}

void get_hw_clock(struct clock *c, struct timespec *ts)
{
	clock_gettime(c->clkid, ts);
}

void exception_log(struct clock *c, char const *format, ...)
{
	struct timespec ts;
	va_list ap;
	char buf[1024];

	clock_gettime(c->clkid, &ts);

	va_start(ap, format);
	vsnprintf(buf, sizeof(buf), format, ap);
	va_end(ap);

	timed_print(LOG_ALERT, &ts, buf);
}
#endif
