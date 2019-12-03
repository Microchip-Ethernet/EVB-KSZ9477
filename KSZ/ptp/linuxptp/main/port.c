/**
 * @file port.c
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
#include <arpa/inet.h>
#include <errno.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/queue.h>
#if 1
#include <linux/if_ether.h>
#endif

#include "bmc.h"
#include "clock.h"
#include "filter.h"
#include "missing.h"
#include "msg.h"
#include "phc.h"
#include "port.h"
#include "print.h"
#include "sk.h"
#include "tlv.h"
#include "tmv.h"
#include "tsproc.h"
#include "util.h"

#ifdef KSZ_1588_PTP

#if 0
#define KSZ_DBG_HOST
#define KSZ_DBG_TIMER
#endif
#if 0
#define KSZ_DBG_MISS
#endif
#if 0
#define KSZ_DBG_TIMEOUT
#endif
#ifdef KSZ_DBG_TIMEOUT
static uint16_t fup_to_id;
static struct timespec fup_ts;
static struct timespec sync_ts;
static unsigned long fup_nsec;
#endif
#ifdef KSZ_DBG_MISS
static uint32_t sync_rx_slave;
#endif

#define _ptp_second
#define _ptp_text

#define USE_NET_IOCTL
#define USE_TIMESTAMP_OPER

#include "ksz_ptp.c"

struct dev_info ptpdev;
#endif

#define ALLOWED_LOST_RESPONSES 3
#define ANNOUNCE_SPAN 1

enum syfu_state {
	SF_EMPTY,
	SF_HAVE_SYNC,
	SF_HAVE_FUP,
};

enum syfu_event {
	SYNC_MISMATCH,
	SYNC_MATCH,
	FUP_MISMATCH,
	FUP_MATCH,
};

struct nrate_estimator {
	double ratio;
	tmv_t origin1;
	tmv_t ingress1;
#ifdef KSZ_1588_PTP
	tmv_t origin2;
	tmv_t ingress2;
#endif
	unsigned int max_count;
	unsigned int count;
	int ratio_valid;
};

struct tc_txd {
	TAILQ_ENTRY(tc_txd) list;
	struct ptp_message *msg;
	tmv_t residence;
	int ingress_port;
};

struct port {
	LIST_ENTRY(port) list;
	char *name;
	struct clock *clock;
	struct transport *trp;
	enum timestamp_type timestamping;
	struct fdarray fda;
	int fault_fd;
	int phc_index;
	int jbod;
	struct foreign_clock *best;
	enum syfu_state syfu;
	struct ptp_message *last_syncfup;
	struct ptp_message *delay_req;
	struct ptp_message *peer_delay_req;
	struct ptp_message *peer_delay_resp;
	struct ptp_message *peer_delay_fup;
#ifdef KSZ_1588_PTP
	struct ptp_message *sync;
	struct ptp_message *follow_up;
	struct ptp_message *delay_resp;
	struct ptp_message *pdelay_resp;
	struct ptp_message *pdelay_resp_fup;
	struct ptp_message *last_sync;
	struct ptp_message *last_fup;
	struct ptp_message *last_announce;
	struct ptp_message *prev_announce;
	struct ptp_message *fwd;
	int msg_cnt;
	tmv_t last_sync_tmv;
	tmv_t last_tx_sync_tmv;
	u32 sync_interval;
	u32 actual_sync_interval;
	int sync_cnt;
	int sync_max;
	struct port *host_port;
	int index;
	int dest_port;
	int forward_port;
	int receive_port;
	int pdelay_resp_port;
	int pdelay_resp_fup_port;
	int phys_port;
	int virt_port;
	int port_mask;
	int new_state;
	char *basename;
	char *devname;
	u32 p2p_sec;
	u32 p2p_nsec;
	u32 followUpReceiptTimeout;
	u32 syncTxContTimeout;
	int syncTxCont;
	u32 ann_rx_timeout:1;
	u32 ann_tx_timeout:1;
	u32 sync_rx_timeout:1;
	u32 sync_tx_timeout:1;
	u32 fup_rx_timeout:1;
	u32 fup_tx_timeout:1;
	u32 gm_change:1;
	u32 tx_ann:1;
	u32 sync_rx_tx:1;
	u32 multiple_pdr:1;
	u32 clear_pdelay_req:1;
	u32 report_announce:1;
	u32 report_link:1;
	u32 report_signaling:1;
	u32 report_sync:1;
	u32 isMeasuringDelay:1;
	u32 lostResponses:1;
	u32 fwd_sync:1;
	u32 skip_tx_sync:1;
	u32 announce_ok:1;
	u32 sync_fup_ok:1;
	u32 pdelay_resp_missed:1;
	u32 tx_err:1;
	u32 rx_sync_timeout:1;
	u32 last_rx_sec;
	u32 rx_sec;
	u32 tx_sec;
	u32 fup_rx;
	u32 sync_rx;
	u32 fup_tx;
	u32 sync_tx;
#ifdef KSZ_DBG_MISS
	uint16_t ann_seqid;
	uint16_t sync_seqid;
	uint16_t fup_seqid;
	uint16_t pdelay_req_seqid;
	uint16_t pdelay_resp_seqid;
	uint16_t pdelay_resp_fup_seqid;
	uint16_t req_seqid;
#endif
	int cnt_pdelay_resp;
	int cnt_pdelay_resp_fup;
	int max_pdelay_req;
	struct timespec first_req_ts;
	struct timespec pdelay_req_ts;
	struct timespec pdelay_resp_ts;
	struct timespec pdelay_resp_fup_ts;
	struct ptp_message *delayed_pdelay_req;
	struct ptp_message *delayed_pdelay_resp;
#endif
	int peer_portid_valid;
	struct PortIdentity peer_portid;
	struct {
		UInteger16 announce;
		UInteger16 delayreq;
		UInteger16 sync;
#ifdef KSZ_1588_PTP
		UInteger16 signal;
#endif
	} seqnum;
	tmv_t peer_delay;
	struct tsproc *tsproc;
	int log_sync_interval;
	struct nrate_estimator nrate;
	unsigned int pdr_missing;
	unsigned int multiple_seq_pdr_count;
	unsigned int multiple_pdr_detected;
	enum port_state (*state_machine)(enum port_state state,
					 enum fsm_event event, int mdiff);
	/* portDS */
	struct PortIdentity portIdentity;
	enum port_state     state; /*portState*/
	Integer64           asymmetry;
	int                 asCapable;
	Integer8            logMinDelayReqInterval;
	TimeInterval        peerMeanPathDelay;
	Integer8            logAnnounceInterval;
	UInteger8           announceReceiptTimeout;
	int                 announce_span;
	UInteger8           syncReceiptTimeout;
	UInteger8           transportSpecific;
	Integer8            logSyncInterval;
	Enumeration8        delayMechanism;
	Integer8            logMinPdelayReqInterval;
	UInteger32          neighborPropDelayThresh;
	int                 follow_up_info;
	int                 freq_est_interval;
	int                 hybrid_e2e;
	int                 match_transport_specific;
	int                 min_neighbor_prop_delay;
	int                 path_trace_enabled;
	int                 tc_spanning_tree;
	int                 rx_timestamp_offset;
	int                 tx_timestamp_offset;
	int                 link_status;
#ifdef KSZ_1588_PTP
	Integer8            initialLogSyncInterval;
	Integer8            operLogSyncInterval;
	Integer8            initialLogPdelayReqInterval;
	Integer8            operLogPdelayReqInterval;
	UInteger32          neighborPropDelay;
	UInteger16	    seqnumPdelayReq;
	UInteger16	    seqnumSync;
	int		    report_interval;
	int		    master_only;
	int		    log_exception;
	int		    no_asCapable;
	int		    no_announce;
	int		    no_id_check;
#endif
	struct fault_interval flt_interval_pertype[FT_CNT];
	enum fault_type     last_fault_type;
	unsigned int        versionNumber; /*UInteger4*/
	/* foreignMasterDS */
	LIST_HEAD(fm, foreign_clock) foreign_masters;
	/* TC book keeping */
	TAILQ_HEAD(tct, tc_txd) tc_transmitted;
};

#define portnum(p) (p->portIdentity.portNumber)

#ifdef KSZ_1588_PTP
#define portdst(p) (1 << ((p) - 1))
#endif

#define NSEC2SEC 1000000000LL

#ifdef KSZ_1588_PTP
int port_set_peer_delay(struct port *p)
{
	int port = p->phys_port;

	/* Use virtual port if available. */
	if (p->virt_port)
		port = p->virt_port;

#ifdef KSZ_DBG_HOST
if (!is_peer_port(p->clock, p))
printf(" !! %s %d %p\n", __func__, portnum(p), p);
#endif
	if (need_dest_port(p->clock))
		port = p->pdelay_resp_port;
	if (!port)
		return -ENODEV;

	/* Physical port is 1-based. */
	if (!p->virt_port)
		--port;
	return set_peer_delay(&ptpdev,
		port, (int) p->peer_delay);
}

int port_get_msg_info(struct port *p, struct ptp_header *header, int *tx,
	u32 *port, u32 *sec, u32 *nsec)
{
	int rc;

	rc = get_msg_info(&ptpdev, header, tx,
		port, sec, nsec);
	return rc;
}

int port_set_msg_info(struct port *p, struct ptp_header *header, u32 ports,
	u32 sec, u32 nsec)
{
	int rc;

	rc = set_msg_info(&ptpdev, header,
		ports, sec, nsec);
	return rc;
}

int port_set_port_cfg(struct port *p, int enable, int asCapable)
{
	int port = p->phys_port;

	/* Use virtual port if available. */
	if (p->virt_port)
		port = p->virt_port;
	if (!port)
		return -ENODEV;

	/* Physical port is 1-based. */
	if (!p->virt_port)
		--port;
	return set_port_cfg(&ptpdev,
		port, enable, asCapable);
}

int port_exit_ptp(struct clock *c)
{
	int rc;
	struct timePropertiesDS *tp = clock_time_properties(c);

	if (tp->flags & UTC_OFF_VALID)
		rc = set_utc_offset(&ptpdev,
			tp->currentUtcOffset);
	rc = set_global_cfg(&ptpdev,
		0, 0, 0, 0);
	rc = ptp_dev_exit(&ptpdev);
	close(ptpdev.sock);
	return rc;
}

int port_init_ptp(struct port *p, int cap, int *drift, UInteger8 *version,
	UInteger8 *ports, UInteger32 *access_delay)
{
	int offset;
	int rc;
	int master;
	int two_step;
	int p2p;
	int as;
	int unicast;
	int alternate;
	int csum;
	int check;
	int delay_assoc;
	int pdelay_assoc;
	int sync_assoc;
	int drop_sync;
	int priority;
	int started;
	UInteger8 domain;

	strncpy(ptpdev.name, p->devname, sizeof(ptpdev.name));
	ptpdev.sock = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

	rc = ptp_dev_init(&ptpdev, cap,
		drift, version, ports, &ptp_host_port);
	pr_info("  version=%d ports=%d",
		*version, *ports);
	ptp_drift = *drift;
	ptp_version = *version;
	ptp_ports = *ports;
	rc = get_global_cfg(&ptpdev,
		&master, &two_step, &p2p, &as,
		&unicast, &alternate, &csum, &check,
		&delay_assoc, &pdelay_assoc, &sync_assoc, &drop_sync,
		&priority, &domain, access_delay, &started);
	pr_info("  access_delay=%u", *access_delay);
	if (!get_min_sync_interval(p->clock)) {
		UInteger32 min_sync_interval;

		if (*access_delay >= 1000000)
			/* About ^-2. */
			min_sync_interval = 200000000;
		else if (*access_delay >= 100000)
			min_sync_interval = 60000000;
		else
			min_sync_interval = 30000000;
		set_min_sync_interval(p->clock, min_sync_interval);
	}
	rc = set_global_cfg(&ptpdev,
		0, clock_two_step(p->clock), (p->delayMechanism == DM_P2P),
		need_stop_forwarding(p->clock) | boundary_clock(p->clock) |
		p->no_announce);
	rc = set_hw_domain(&ptpdev,
		clock_domain_number(p->clock));
	rc = get_utc_offset(&ptpdev,
		&offset);
	pr_info("  UTC offset: %d", offset);
	if (offset) {
		struct timePropertiesDS *tp = clock_time_properties(p->clock);

		if (offset > tp->currentUtcOffset) {
			set_master_utc_offset(p->clock, offset);
			tp->currentUtcOffset = offset;
		} else if (!(tp->flags & UTC_OFF_VALID)) {
			if (tp->currentUtcOffset)
				set_master_utc_offset(p->clock,
					tp->currentUtcOffset);
		}
	}
	return rc;
}

int new_state(struct port *p)
{
	int ret = p->new_state;

	p->new_state = 0;
	return ret;
}

void port_set_host_port(struct port *p, struct port *host_port)
{
#if 0
printf("%s %d %d; %p %p\n", __func__, portnum(p), portnum(host_port),
p, host_port);
#endif
	p->host_port = host_port;
}

void port_set_port_state(struct port *p, enum fsm_event event)
{
#if 0
printf("%s %d %d %d\n", __func__, portnum(p), p->state, p->host_port->state);
#endif
	port_dispatch(p, event, 0);
}
#endif

static int port_capable(struct port *p);
static int port_is_ieee8021as(struct port *p);
static void port_nrate_initialize(struct port *p);

static int announce_compare(struct ptp_message *m1, struct ptp_message *m2)
{
	struct announce_msg *a = &m1->announce, *b = &m2->announce;
	int len =
		sizeof(a->grandmasterPriority1) +
		sizeof(a->grandmasterClockQuality) +
		sizeof(a->grandmasterPriority2) +
		sizeof(a->grandmasterIdentity) +
		sizeof(a->stepsRemoved);

	return memcmp(&a->grandmasterPriority1, &b->grandmasterPriority1, len);
}

static void announce_to_dataset(struct ptp_message *m, struct port *p,
				struct dataset *out)
{
	struct announce_msg *a = &m->announce;
	out->priority1    = a->grandmasterPriority1;
	out->identity     = a->grandmasterIdentity;
	out->quality      = a->grandmasterClockQuality;
	out->priority2    = a->grandmasterPriority2;
	out->stepsRemoved = a->stepsRemoved;
	out->sender       = m->header.sourcePortIdentity;
	out->receiver     = p->portIdentity;
}

static int clear_fault_asap(struct fault_interval *faint)
{
	switch (faint->type) {
	case FTMO_LINEAR_SECONDS:
		return faint->val == 0 ? 1 : 0;
	case FTMO_LOG2_SECONDS:
		return faint->val == FRI_ASAP ? 1 : 0;
	case FTMO_CNT:
		return 0;
	}
	return 0;
}

static int msg_current(struct ptp_message *m, struct timespec now)
{
	int64_t t1, t2, tmo;

	t1 = m->ts.host.tv_sec * NSEC2SEC + m->ts.host.tv_nsec;
	t2 = now.tv_sec * NSEC2SEC + now.tv_nsec;

	if (m->header.logMessageInterval < -63) {
		tmo = 0;
	} else if (m->header.logMessageInterval > 31) {
		tmo = INT64_MAX;
	} else if (m->header.logMessageInterval < 0) {
		tmo = 4LL * NSEC2SEC / (1 << -m->header.logMessageInterval);
	} else {
		tmo = 4LL * (1 << m->header.logMessageInterval) * NSEC2SEC;
	}

	return t2 - t1 < tmo;
}

static int msg_source_equal(struct ptp_message *m1, struct foreign_clock *fc)
{
	struct PortIdentity *id1, *id2;
	id1 = &m1->header.sourcePortIdentity;
	id2 = &fc->dataset.sender;
	return 0 == memcmp(id1, id2, sizeof(*id1));
}

static int pid_eq(struct PortIdentity *a, struct PortIdentity *b)
{
	return 0 == memcmp(a, b, sizeof(*a));
}

static int source_pid_eq(struct ptp_message *m1, struct ptp_message *m2)
{
	return pid_eq(&m1->header.sourcePortIdentity,
		      &m2->header.sourcePortIdentity);
}

enum fault_type last_fault_type(struct port *port)
{
	return port->last_fault_type;
}

void fault_interval(struct port *port, enum fault_type ft,
		    struct fault_interval *i)
{
	i->type = port->flt_interval_pertype[ft].type;
	i->val = port->flt_interval_pertype[ft].val;
}

int port_fault_fd(struct port *port)
{
	return port->fault_fd;
}

struct fdarray *port_fda(struct port *port)
{
	return &port->fda;
}

#ifdef KSZ_1588_PTP
static int get_cnt_from_log(int log_seconds, int seconds)
{
	int cnt;

	if (log_seconds < 0) {
		log_seconds *= -1;
		cnt = 1 << log_seconds;
		cnt *= seconds;
	} else {
		cnt = 1 << log_seconds;
		cnt = seconds / cnt;
	}
	return cnt;
}

static u32 calculate_interval(unsigned int scale, int log_seconds)
{
	uint64_t ns;
	int i;

	if (log_seconds < 0) {
		log_seconds *= -1;
		for (i = 1, ns = scale * 500000000ULL; i < log_seconds; i++) {
			ns >>= 1;
		}
	} else {
		ns = scale * (1 << log_seconds);
		ns *= NS_PER_SEC;
	}
	ns += 500;
	ns /= 1000;
	return (u32)ns;
}
#endif

int set_tmo_log(int fd, unsigned int scale, int log_seconds)
{
	struct itimerspec tmo = {
		{0, 0}, {0, 0}
	};
	uint64_t ns;
	int i;

	if (log_seconds < 0) {

		log_seconds *= -1;
		for (i = 1, ns = scale * 500000000ULL; i < log_seconds; i++) {
			ns >>= 1;
		}

#ifdef KSZ_1588_PTP
		/* -6 */
		if (scale == 1 && ns < NS_PER_SEC && ns >= 15625000) {
			ns -= 50000;
			/* -5 */
			if (ns <= 31200000)
				ns -= 50000;
		}
#endif
		while (ns >= NS_PER_SEC) {
			ns -= NS_PER_SEC;
			tmo.it_value.tv_sec++;
		}
		tmo.it_value.tv_nsec = ns;

	} else
		tmo.it_value.tv_sec = scale * (1 << log_seconds);

	return timerfd_settime(fd, 0, &tmo, NULL);
}

int set_tmo_lin(int fd, int seconds)
{
	struct itimerspec tmo = {
		{0, 0}, {0, 0}
	};

	tmo.it_value.tv_sec = seconds;
	return timerfd_settime(fd, 0, &tmo, NULL);
}

#ifdef KSZ_1588_PTP
int set_tmo_us(int fd, int microseconds)
{
	uint64_t ns;
	struct itimerspec tmo = {
		{0, 0}, {0, 0}
	};

	ns = microseconds;
	ns *= (NS_PER_SEC / 1000000);
	tmo.it_value.tv_sec = ns / NS_PER_SEC;
	tmo.it_value.tv_nsec = ns % NS_PER_SEC;
	return timerfd_settime(fd, 0, &tmo, NULL);
}
#endif

int set_tmo_random(int fd, int min, int span, int log_seconds)
{
	uint64_t value_ns, min_ns, span_ns;
	struct itimerspec tmo = {
		{0, 0}, {0, 0}
	};

	if (log_seconds >= 0) {
		min_ns = min * NS_PER_SEC << log_seconds;
		span_ns = span * NS_PER_SEC << log_seconds;
	} else {
		min_ns = min * NS_PER_SEC >> -log_seconds;
		span_ns = span * NS_PER_SEC >> -log_seconds;
	}

	value_ns = min_ns + (span_ns * (random() % (1 << 15) + 1) >> 15);

	tmo.it_value.tv_sec = value_ns / NS_PER_SEC;
	tmo.it_value.tv_nsec = value_ns % NS_PER_SEC;

	return timerfd_settime(fd, 0, &tmo, NULL);
}

int port_set_fault_timer_log(struct port *port,
			     unsigned int scale, int log_seconds)
{
	return set_tmo_log(port->fault_fd, scale, log_seconds);
}

int port_set_fault_timer_lin(struct port *port, int seconds)
{
	return set_tmo_lin(port->fault_fd, seconds);
}

static void fc_clear(struct foreign_clock *fc)
{
	struct ptp_message *m;

	while (fc->n_messages) {
		m = TAILQ_LAST(&fc->messages, messages);
		TAILQ_REMOVE(&fc->messages, m, list);
		fc->n_messages--;
		msg_put(m);
	}
}

static void fc_prune(struct foreign_clock *fc)
{
	struct timespec now;
	struct ptp_message *m;

	clock_gettime(CLOCK_MONOTONIC, &now);

	while (fc->n_messages > FOREIGN_MASTER_THRESHOLD) {
		m = TAILQ_LAST(&fc->messages, messages);
		TAILQ_REMOVE(&fc->messages, m, list);
		fc->n_messages--;
		msg_put(m);
	}

	while (!TAILQ_EMPTY(&fc->messages)) {
		m = TAILQ_LAST(&fc->messages, messages);
		if (msg_current(m, now))
			break;
		TAILQ_REMOVE(&fc->messages, m, list);
		fc->n_messages--;
		msg_put(m);
	}
}

#ifndef KSZ_1588_PTP_
static void ts_add(struct timespec *ts, int ns)
{
	if (!ns) {
		return;
	}
	ts->tv_nsec += ns;
	while (ts->tv_nsec < 0) {
		ts->tv_nsec += (long) NS_PER_SEC;
		ts->tv_sec--;
	}
	while (ts->tv_nsec >= (long) NS_PER_SEC) {
		ts->tv_nsec -= (long) NS_PER_SEC;
		ts->tv_sec++;
	}
}
#endif

#ifdef KSZ_1588_PTP
static void ts_to_ts(struct Timestamp *src, struct Timestamp *dst)
{
	dst->seconds_lsb = ntohl(src->seconds_lsb);
	dst->seconds_msb = ntohs(src->seconds_msb);
	dst->nanoseconds = ntohl(src->nanoseconds);
}

static void ts_diff(struct timespec *start, struct timespec *stop,
		    struct timespec *diff)
{
	*diff = *stop;
	diff->tv_sec -= start->tv_sec;
	if (diff->tv_nsec < start->tv_nsec) {
		diff->tv_sec--;
		diff->tv_nsec += 1000000000;
	}
	diff->tv_nsec -= start->tv_nsec;
}
#endif

static void ts_to_timestamp(struct timespec *src, struct Timestamp *dst)
{
	dst->seconds_lsb = src->tv_sec;
	dst->seconds_msb = 0;
	dst->nanoseconds = src->tv_nsec;
}

/*
 * Returns non-zero if the announce message is different than last.
 */
static int add_foreign_master(struct port *p, struct ptp_message *m)
{
	struct foreign_clock *fc;
	struct ptp_message *tmp;
	int broke_threshold = 0, diff = 0;
	int threshold = FOREIGN_MASTER_THRESHOLD;

	LIST_FOREACH(fc, &p->foreign_masters, list) {
		if (msg_source_equal(m, fc))
			break;
	}
	if (!fc) {
		pr_notice("port %hu: new foreign master %s", portnum(p),
			pid2str(&m->header.sourcePortIdentity));

		fc = malloc(sizeof(*fc));
		if (!fc) {
			pr_err("low memory, failed to add foreign master");
			return 0;
		}
		memset(fc, 0, sizeof(*fc));
		TAILQ_INIT(&fc->messages);
		LIST_INSERT_HEAD(&p->foreign_masters, fc, list);
		fc->port = p;
		fc->dataset.sender = m->header.sourcePortIdentity;
		/* We do not count this first message, see 9.5.3(b) */
#ifdef KSZ_1588_PTP
		if (!port_is_ieee8021as(p))
#endif
		return 0;
	}
#ifdef KSZ_1588_PTP
	if (port_is_ieee8021as(p) && !fc->n_messages)
		threshold = 1;
#endif

	/*
	 * If this message breaks the threshold, that is an important change.
	 */
	fc_prune(fc);
	if (threshold - 1 == fc->n_messages)
		broke_threshold = 1;

	/*
	 * Okay, go ahead and add this announcement.
	 */
	msg_get(m);
	fc->n_messages++;
	TAILQ_INSERT_HEAD(&fc->messages, m, list);

	/*
	 * Test if this announcement contains changed information.
	 */
	if (fc->n_messages > 1) {
		tmp = TAILQ_NEXT(m, list);
		diff = announce_compare(m, tmp);
	}

	return broke_threshold || diff;
}

static int follow_up_info_append(struct port *p, struct ptp_message *m)
{
	struct follow_up_info_tlv *fui;
	fui = (struct follow_up_info_tlv *) m->follow_up.suffix;
	fui->type = TLV_ORGANIZATION_EXTENSION;
	fui->length = sizeof(*fui) - sizeof(fui->type) - sizeof(fui->length);
	memcpy(fui->id, ieee8021_id, sizeof(ieee8021_id));
	fui->subtype[2] = 1;
	clock_get_follow_up_info(p->clock, fui);
	m->tlv_count = 1;
	return sizeof(*fui);
}

static struct follow_up_info_tlv *follow_up_info_extract(struct ptp_message *m)
{
	struct follow_up_info_tlv *f;
#ifdef KSZ_1588_PTP
	struct TLV *tlv;
	uint8_t *ptr;
	int i;

	ptr = (uint8_t *) m->follow_up.suffix;
	for (i = 0; i < m->tlv_count; i++) {
		tlv = (struct TLV *) ptr;
		f = (struct follow_up_info_tlv *) tlv;
		if (f->type == TLV_ORGANIZATION_EXTENSION &&
		    f->length >= sizeof(*f) - sizeof(struct TLV) &&
//		    !memcmp(f->id, ieee8021_id, sizeof(ieee8021_id)) &&
		    f->subtype[0] == 0 && f->subtype[1] == 0 &&
		    f->subtype[2] == 1)
			return f;
		ptr += sizeof(struct TLV) + tlv->length;
	}
	return NULL;
#else
	f = (struct follow_up_info_tlv *) m->follow_up.suffix;

	if (m->tlv_count != 1 ||
	    f->type != TLV_ORGANIZATION_EXTENSION ||
	    f->length != sizeof(*f) - sizeof(f->type) - sizeof(f->length) ||
//	    memcmp(f->id, ieee8021_id, sizeof(ieee8021_id)) ||
	    f->subtype[0] || f->subtype[1] || f->subtype[2] != 1) {
		return NULL;
	}
#endif
	return f;
}

#ifdef KSZ_1588_PTP
static int interval_info_append(struct port *p, struct ptp_message *m)
{
	struct interval_info_tlv *ii;

	ii = (struct interval_info_tlv *) m->signaling.suffix;
	ii->type = TLV_ORGANIZATION_EXTENSION;
	ii->length = sizeof(*ii) - sizeof(ii->type) - sizeof(ii->length);
	memcpy(ii->id, ieee8021_id, sizeof(ieee8021_id));
	ii->subtype[2] = 2;
	ii->linkDelayInterval = 0x7f;
	ii->announceInterval = 0x7f;
	ii->timeSyncInterval = p->logSyncInterval;
	ii->flags = 0x3;
	ii->reserved = 0;
	m->tlv_count = 1;
	return sizeof(*ii);
}

static struct interval_info_tlv *interval_info_extract(struct ptp_message *m)
{
	struct interval_info_tlv *f;
	struct TLV *tlv;
	uint8_t *ptr;
	int i;

	ptr = (uint8_t *) m->signaling.suffix;
	for (i = 0; i < m->tlv_count; i++) {
		tlv = (struct TLV *) ptr;
		f = (struct interval_info_tlv *) tlv;
		if (f->type == TLV_ORGANIZATION_EXTENSION &&
		    f->length >= sizeof(*f) - sizeof(struct TLV) &&
		    !memcmp(f->id, ieee8021_id, sizeof(ieee8021_id)) &&
		    f->subtype[0] == 0 && f->subtype[1] == 0 &&
		    f->subtype[2] == 2)
			return f;
		ptr += sizeof(struct TLV) + tlv->length;
	}
	return NULL;
}

static struct wake_info_tlv *wake_info_extract(struct ptp_message *m)
{
	struct wake_info_tlv *f;
	struct TLV *tlv;
	uint8_t *ptr;
	int i;

	ptr = (uint8_t *) m->signaling.suffix;
	for (i = 0; i < m->tlv_count; i++) {
		tlv = (struct TLV *) ptr;
		f = (struct wake_info_tlv *) tlv;
		if (f->type == TLV_ORGANIZATION_EXTENSION &&
		    f->length >= sizeof(*f) - sizeof(struct TLV) &&
		    f->id[0] == 0x00 && f->id[1] == 0x10 && f->id[2] == 0xA1 &&
		    f->subtype[0] == 0 && f->subtype[1] == 0 &&
		    f->subtype[2] == 2)
			return f;
		ptr += sizeof(struct TLV) + tlv->length;
	}
	return NULL;
}
#endif

static void free_foreign_masters(struct port *p)
{
	struct foreign_clock *fc;
	while ((fc = LIST_FIRST(&p->foreign_masters)) != NULL) {
		LIST_REMOVE(fc, list);
		fc_clear(fc);
		free(fc);
	}
}

static int fup_sync_ok(struct ptp_message *fup, struct ptp_message *sync)
{
	int64_t tfup, tsync;
	tfup = tmv_to_nanoseconds(timespec_to_tmv(fup->hwts.sw));
	tsync = tmv_to_nanoseconds(timespec_to_tmv(sync->hwts.sw));
	/*
	 * NB - If the sk_check_fupsync option is not enabled, then
	 * both of these time stamps will be zero.
	 */
	if (tfup < tsync) {
		return 0;
	}
	return 1;
}

static int incapable_ignore(struct port *p, struct ptp_message *m)
{
	if (port_capable(p)) {
		return 0;
	}
	if (msg_type(m) == ANNOUNCE || msg_type(m) == SYNC) {
		return 1;
	}
	return 0;
}

static int path_trace_append(struct port *p, struct ptp_message *m,
			     struct parent_ds *dad)
{
	struct path_trace_tlv *ptt;
	int length = 1 + dad->path_length;

	if (length > PATH_TRACE_MAX) {
		return 0;
	}
	ptt = (struct path_trace_tlv *) m->announce.suffix;
	ptt->type = TLV_PATH_TRACE;
	ptt->length = length * sizeof(struct ClockIdentity);
	memcpy(ptt->cid, dad->ptl, ptt->length);
	ptt->cid[length - 1] = clock_identity(p->clock);
	m->tlv_count = 1;
	return ptt->length + sizeof(ptt->type) + sizeof(ptt->length);
}

static int path_trace_ignore(struct port *p, struct ptp_message *m)
{
	struct ClockIdentity cid;
	struct path_trace_tlv *ptt;
#ifdef KSZ_1588_PTP
	struct TLV *tlv;
	uint8_t *ptr;
#endif
	int i, cnt;

	if (!p->path_trace_enabled) {
		return 0;
	}
	if (msg_type(m) != ANNOUNCE) {
		return 0;
	}
#ifndef KSZ_1588_PTP
	if (m->tlv_count != 1) {
		return 1;
	}
	ptt = (struct path_trace_tlv *) m->announce.suffix;
	if (ptt->type != TLV_PATH_TRACE) {
		return 1;
	}
#else
	ptr = (uint8_t *) m->announce.suffix;
	for (i = 0; i < m->tlv_count; i++) {
		tlv = (struct TLV *) ptr;
		if (tlv->type == TLV_PATH_TRACE)
			break;
		ptr += sizeof(struct TLV) + tlv->length;
	}
	if (i >= m->tlv_count)
		return 1;
	ptt = (struct path_trace_tlv *) tlv;
#endif
	cnt = path_length(ptt);
	cid = clock_identity(p->clock);
	for (i = 0; i < cnt; i++) {
		if (0 == memcmp(&ptt->cid[i], &cid, sizeof(cid)))
			return 1;
	}
	return 0;
}

static int peer_prepare_and_send(struct port *p, struct ptp_message *msg,
				 int event)
{
	int cnt;
#ifdef KSZ_1588_PTP
	int port = 0;
#endif
	if (msg_pre_send(msg)) {
		return -1;
	}

#ifdef KSZ_1588_PTP
	if (need_dest_port(p->clock)) {
		switch (msg_type(msg)) {
		case PDELAY_RESP:
		case PDELAY_RESP_FOLLOW_UP:
			if (get_hw_version(p->clock) >= 2)
				port = p->receive_port;
			break;
		default:
			port = get_master_port(p->clock);

			if (get_hw_version(p->clock) < 1)
				msg->header.sourcePortIdentity.portNumber = 0;
			if (port) {
				if (get_hw_version(p->clock) < 2) {
					msg->header.reserved1 = port;
					port = 0;
				}
			} else {
				if (get_hw_version(p->clock) < 2)
					msg->header.reserved1 =
						all_ports(p->clock);
			}
			break;
		}
	}
	if (p->p2p_sec || p->p2p_nsec || port) {
		port_set_msg_info(p, &msg->header,
			portdst(port), p->p2p_sec, p->p2p_nsec);
		p->p2p_sec = p->p2p_nsec = 0;
	}
#endif
	cnt = transport_peer(p->trp, &p->fda, event, msg);
	if (cnt <= 0) {
		return -1;
	}
#ifndef KSZ_1588_PTP_
	if (msg_sots_valid(msg)) {
		ts_add(&msg->hwts.ts, p->tx_timestamp_offset);
	}
#endif
	return 0;
}

#ifdef KSZ_1588_PTP
static int c37_238_append(struct port *p, struct ptp_message *m)
{
	struct ieee_c37_238_info_tlv *c37;
	struct ieee_c37_238_data *data;
	struct alternate_time_offset_tlv *alt;
	int length;

	c37 = (struct ieee_c37_238_info_tlv *) m->announce.suffix;
	c37->org.type = TLV_ORGANIZATION_EXTENSION;
	c37->org.length = sizeof(*c37) - sizeof(c37->org.type) -
		sizeof(c37->org.length);
	memcpy(c37->org.id, ieee_c37_238_id, sizeof(ieee_c37_238_id));
	c37->org.subtype[2] = 1;
	data = &c37->data;
	data->grandmasterID = 0x00FE;
	data->grandmasterTimeInaccuracy = 50;
	data->networkTimeInaccuracy = 200;
	data->reserved = 0;
	length = sizeof(*c37);

	alt = (struct alternate_time_offset_tlv *)(data + 1);
	alt->hdr.type = TLV_ALTERNATE_TIME_OFFSET_INDICATOR;
	alt->keyField = 0;
	alt->currentOffset = 0;
	alt->jumpSeconds = 0;
	alt->timeOfNextJump.seconds_msb = 0;
	alt->timeOfNextJump.seconds_lsb = 0;
	alt->displayName.lengthField = 3;
	alt->displayName.textField[0] = 'P';
	alt->displayName.textField[1] = 'S';
	alt->displayName.textField[2] = 'T';
	alt->hdr.length = sizeof(*alt) - sizeof(struct tlv_hdr) - 1 +
		alt->displayName.lengthField;
	if (alt->hdr.length & 1) {
		uint8_t *pad = (uint8_t *) alt;

		pad[alt->hdr.length + sizeof(struct tlv_hdr)] = '\0';
		alt->hdr.length++;
	}
	length += alt->hdr.length + sizeof(struct tlv_hdr);
	m->tlv_count = 2;
	return length;
}

static int c37_238_extract(struct ptp_message *m,
	struct ieee_c37_238_data **c37, struct alternate_time_offset_tlv **alt)
{
	struct ieee_c37_238_info_tlv *c;
	struct alternate_time_offset_tlv *a;

	c = (struct ieee_c37_238_info_tlv *) m->announce.suffix;

	if (m->tlv_count != 2 ||
	    c->org.type != TLV_ORGANIZATION_EXTENSION ||
	    c->org.length < sizeof(*c) - sizeof(c->org.type) -
	    sizeof(c->org.length) ||
	    memcmp(c->org.id, ieee_c37_238_id, sizeof(ieee_c37_238_id)) ||
	    c->org.subtype[0] || c->org.subtype[1] || c->org.subtype[2] != 1) {
		return FALSE;
	}
	*c37 = &c->data;
	a = (struct alternate_time_offset_tlv *)(*c37 + 1);
	if (a->hdr.type != TLV_ALTERNATE_TIME_OFFSET_INDICATOR ||
	    a->hdr.length < sizeof(*a) - sizeof(struct tlv_hdr))
		return FALSE;
	*alt = a;
	return TRUE;
}
#endif

static int port_capable(struct port *p)
{
	if (!port_is_ieee8021as(p)) {
		/* Normal 1588 ports are always capable. */
		goto capable;
	}

#ifdef KSZ_1588_PTP
	if (port_is_ieee8021as(p) && p->no_asCapable) {
		goto capable;
	}
#endif

	if (tmv_to_nanoseconds(p->peer_delay) >	p->neighborPropDelayThresh) {
		if (p->asCapable)
			pr_debug("port %hu: peer_delay (%" PRId64 ") > neighborPropDelayThresh "
				"(%" PRId32 "), resetting asCapable", portnum(p),
				tmv_to_nanoseconds(p->peer_delay),
				p->neighborPropDelayThresh);
		goto not_capable;
	}

	if (tmv_to_nanoseconds(p->peer_delay) <	p->min_neighbor_prop_delay) {
		if (p->asCapable)
			pr_debug("port %hu: peer_delay (%" PRId64 ") < min_neighbor_prop_delay "
				"(%" PRId32 "), resetting asCapable", portnum(p),
				tmv_to_nanoseconds(p->peer_delay),
				p->min_neighbor_prop_delay);
		goto not_capable;
	}

	if (p->pdr_missing > ALLOWED_LOST_RESPONSES) {
		if (p->asCapable)
			pr_debug("port %hu: missed %d peer delay resp, "
				"resetting asCapable", portnum(p), p->pdr_missing);
		goto not_capable;
	}

	if (p->multiple_seq_pdr_count) {
		if (p->asCapable)
			pr_debug("port %hu: multiple sequential peer delay resp, "
				"resetting asCapable", portnum(p));
		goto not_capable;
	}

#ifdef KSZ_1588_PTP
	if (p->multiple_pdr) {
		if (p->asCapable)
			pr_debug("port %hu: multiple peer delay resp, "
				"resetting asCapable", portnum(p));
		goto not_capable;
	}
#endif

	if (!p->peer_portid_valid) {
		if (p->asCapable)
			pr_debug("port %hu: invalid peer port id, "
				"resetting asCapable", portnum(p));
		goto not_capable;
	}

	if (!p->nrate.ratio_valid) {
		if (p->asCapable)
			pr_debug("port %hu: invalid nrate, "
				"resetting asCapable", portnum(p));
		goto not_capable;
	}

capable:
	if (!p->asCapable)
		pr_debug("port %hu: setting asCapable", portnum(p));
#ifdef KSZ_1588_PTP
	/* Port 0 can be IEEE 802.1AS port. */
	if (!p->asCapable && port_is_ieee8021as(p) && portnum(p) > 0) {
		if (p->state == PS_MASTER || p->state == PS_GRAND_MASTER) {
			/* Want to send Announce as fast as possible. */
			if (!get_slave_port(p->clock) && !p->tx_ann) {
				set_tmo_log(p->fda.fd[FD_MANNO_TIMER], 1, -10);
				if (!p->ann_tx_timeout) {
					p->ann_tx_timeout = 1;
				}
			}
		}
		port_set_port_cfg(p, 1, 1);
#if 0
printf(" as: %d\n", portnum(p));
#endif
	}
#endif
	p->asCapable = 1;
	return 1;

not_capable:
#ifdef KSZ_1588_PTP
	/* Port 0 can be IEEE 802.1AS port. */
	if (p->asCapable && port_is_ieee8021as(p) && portnum(p) > 0) {
		port_set_port_cfg(p, 1, 0);
#if 0
printf(" !as: %d\n", portnum(p));
#endif
	}
#endif
	if (p->asCapable)
		port_nrate_initialize(p);
	p->asCapable = 0;
	return 0;
}

static int port_clr_tmo(int fd)
{
	struct itimerspec tmo = {
		{0, 0}, {0, 0}
	};
	return timerfd_settime(fd, 0, &tmo, NULL);
}

static int port_ignore(struct port *p, struct ptp_message *m)
{
	struct ClockIdentity c1, c2;

	if (incapable_ignore(p, m)) {
		return 1;
	}
	if (path_trace_ignore(p, m)) {
		return 1;
	}
	if (msg_transport_specific(m) != p->transportSpecific) {
		return 1;
	}
	if (pid_eq(&m->header.sourcePortIdentity, &p->portIdentity)) {
		return 1;
	}
	if (m->header.domainNumber != clock_domain_number(p->clock)) {
		return 1;
	}

	c1 = clock_identity(p->clock);
	c2 = m->header.sourcePortIdentity.clockIdentity;

	if (0 == memcmp(&c1, &c2, sizeof(c1))) {
#ifdef KSZ_1588_PTP
		/* Allow own Pdelay_Resp to detect multiple responses. */
		if (msg_type(m) == PDELAY_RESP)
			return 0;
#if 0
		if (msg_type(m) == PDELAY_REQ ||
		    msg_type(m) == PDELAY_RESP_FOLLOW_UP)
			return 0;
#endif
#endif
		return 1;
	}
	return 0;
}

/*
 * Test whether a 802.1AS port may transmit a sync message.
 */
static int port_sync_incapable(struct port *p)
{
	struct ClockIdentity cid;
	struct PortIdentity pid;

	if (!port_is_ieee8021as(p)) {
		return 0;
	}
	if (clock_gm_capable(p->clock)) {
		return 0;
	}
	cid = clock_identity(p->clock);
	pid = clock_parent_identity(p->clock);
	if (!memcmp(&cid, &pid.clockIdentity, sizeof(cid))) {
		/*
		 * We are the GM, but without gmCapable set.
		 */
		return 1;
	}
	return 0;
}

static int port_is_ieee8021as(struct port *p)
{
	return p->follow_up_info ? 1 : 0;
}

#ifdef KSZ_1588_PTP
int port_is_aed(struct port *p)
{
	return p->follow_up_info && p->no_announce ? 1 : 0;
}

int port_is_aed_master(struct port *p)
{
	return p->follow_up_info && p->no_announce && p->master_only ? 1 : 0;
}

void process_wake_info(struct clock *c, struct port *p, int event)
{
#if 0
	struct clock *c = p->clock;
#endif

	if (!port_is_aed(p))
		return;
	if (p->log_exception)
		exception_log(c, "%s sleeping",
			      event ? "Stop" : "Start");
#if 1
	for (p = clock_first_port(c); p; p = LIST_NEXT(p, list)) {
#endif
#if 0
	if (p) {
#endif
		if (event) {
			if (p->state != PS_PASSIVE)
				return;
			port_dispatch(p, EV_POWERUP, 0);
			if (port_is_aed_master(p))
				port_dispatch(p, EV_RS_GRAND_MASTER, 0);
			else
				port_dispatch(p, EV_RS_SLAVE, 0);
		} else {
			port_dispatch(p, EV_RS_PASSIVE, 0);
		}
	}
}
#endif

static void port_management_send_error(struct port *p, struct port *ingress,
				       struct ptp_message *msg, int error_id)
{
	if (port_management_error(p->portIdentity, ingress, msg, error_id))
		pr_err("port %hu: management error failed", portnum(p));
}

static const Octet profile_id_drr[] = {0x00, 0x1B, 0x19, 0x00, 0x01, 0x00};
static const Octet profile_id_p2p[] = {0x00, 0x1B, 0x19, 0x00, 0x02, 0x00};

static int port_management_fill_response(struct port *target,
					 struct ptp_message *rsp, int id)
{
	int datalen = 0, respond = 0;
	struct management_tlv *tlv;
	struct management_tlv_datum *mtd;
	struct portDS *pds;
	struct port_ds_np *pdsnp;
	struct port_properties_np *ppn;
	struct clock_description *desc;
	struct mgmt_clock_description *cd;
	uint8_t *buf;
	uint16_t u16;
#ifdef KSZ_1588_PTP
	uint32_t *ptr32;
#endif

	tlv = (struct management_tlv *) rsp->management.suffix;
	tlv->type = TLV_MANAGEMENT;
	tlv->id = id;

	switch (id) {
	case TLV_NULL_MANAGEMENT:
		datalen = 0;
		respond = 1;
		break;
	case TLV_CLOCK_DESCRIPTION:
		cd = &rsp->last_tlv.cd;
		buf = tlv->data;
		cd->clockType = (UInteger16 *) buf;
		buf += sizeof(*cd->clockType);
		*cd->clockType = clock_type(target->clock);
		cd->physicalLayerProtocol = (struct PTPText *) buf;
		switch(transport_type(target->trp)) {
		case TRANS_UDP_IPV4:
		case TRANS_UDP_IPV6:
		case TRANS_IEEE_802_3:
			ptp_text_set(cd->physicalLayerProtocol, "IEEE 802.3");
			break;
		default:
			ptp_text_set(cd->physicalLayerProtocol, NULL);
			break;
		}
		buf += sizeof(struct PTPText) + cd->physicalLayerProtocol->length;

		cd->physicalAddress = (struct PhysicalAddress *) buf;
		u16 = transport_physical_addr(target->trp,
                                              cd->physicalAddress->address);
		memcpy(&cd->physicalAddress->length, &u16, 2);
		buf += sizeof(struct PhysicalAddress) + u16;

		cd->protocolAddress = (struct PortAddress *) buf;
		u16 = transport_type(target->trp);
		memcpy(&cd->protocolAddress->networkProtocol, &u16, 2);
		u16 = transport_protocol_addr(target->trp,
                                              cd->protocolAddress->address);
		memcpy(&cd->protocolAddress->addressLength, &u16, 2);
		buf += sizeof(struct PortAddress) + u16;

		desc = clock_description(target->clock);
		cd->manufacturerIdentity = buf;
		memcpy(cd->manufacturerIdentity,
                       desc->manufacturerIdentity, OUI_LEN);
		buf += OUI_LEN;
		*(buf++) = 0; /* reserved */

		cd->productDescription = (struct PTPText *) buf;
		ptp_text_copy(cd->productDescription, &desc->productDescription);
		buf += sizeof(struct PTPText) + cd->productDescription->length;

		cd->revisionData = (struct PTPText *) buf;
		ptp_text_copy(cd->revisionData, &desc->revisionData);
		buf += sizeof(struct PTPText) + cd->revisionData->length;

		cd->userDescription = (struct PTPText *) buf;
		ptp_text_copy(cd->userDescription, &desc->userDescription);
		buf += sizeof(struct PTPText) + cd->userDescription->length;

		if (target->delayMechanism == DM_P2P) {
			memcpy(buf, profile_id_p2p, PROFILE_ID_LEN);
		} else {
			memcpy(buf, profile_id_drr, PROFILE_ID_LEN);
		}
		buf += PROFILE_ID_LEN;
		datalen = buf - tlv->data;
		respond = 1;
		break;
	case TLV_PORT_DATA_SET:
		pds = (struct portDS *) tlv->data;
		pds->portIdentity            = target->portIdentity;
		if (target->state == PS_GRAND_MASTER) {
			pds->portState = PS_MASTER;
		} else {
			pds->portState = target->state;
		}
		pds->logMinDelayReqInterval  = target->logMinDelayReqInterval;
		pds->peerMeanPathDelay       = target->peerMeanPathDelay;
		pds->logAnnounceInterval     = target->logAnnounceInterval;
		pds->announceReceiptTimeout  = target->announceReceiptTimeout;
		pds->logSyncInterval         = target->logSyncInterval;
		if (target->delayMechanism) {
			pds->delayMechanism = target->delayMechanism;
#ifdef KSZ_1588_PTP
			if (target->delayMechanism == DM_NONE)
				pds->delayMechanism = 0xFE;
#endif
		} else {
			pds->delayMechanism = DM_E2E;
		}
		pds->logMinPdelayReqInterval = target->logMinPdelayReqInterval;
		pds->versionNumber           = target->versionNumber;
		datalen = sizeof(*pds);
		respond = 1;
		break;
#ifdef KSZ_1588_PTP
	case TLV_TRANSPARENT_CLOCK_PORT_DATA_SET:
	{
		struct transparent_clock_port_data_set *pds =
			(struct transparent_clock_port_data_set *) tlv->data;

		memcpy(&pds->portIdentity, &target->portIdentity,
			sizeof(struct PortIdentity));
		pds->faultyFlag = FALSE;
		pds->peerMeanPathDelay = target->peerMeanPathDelay;
		pds->logMinPdelayReqInterval = target->logMinPdelayReqInterval;
		datalen = sizeof(*pds);
		respond = 1;
		break;
	}
	case TLV_DISABLE_PORT:
	case TLV_ENABLE_PORT:
		respond = 1;
		break;
	case TLV_MASTER_ONLY:
		mtd = (struct management_tlv_datum *) tlv->data;
		mtd->val = target->master_only;
		datalen = sizeof(*mtd);
		respond = 1;
		break;
	case TLV_INITIAL_LOG_PDELAY_REQ_INTERVAL:
		mtd = (struct management_tlv_datum *) tlv->data;
		mtd->val = target->initialLogPdelayReqInterval;
		datalen = sizeof(*mtd);
		respond = 1;
		break;
	case TLV_OPER_LOG_PDELAY_REQ_INTERVAL:
		mtd = (struct management_tlv_datum *) tlv->data;
		mtd->val = target->operLogPdelayReqInterval;
		datalen = sizeof(*mtd);
		respond = 1;
		break;
	case TLV_INITIAL_LOG_SYNC_INTERVAL:
		mtd = (struct management_tlv_datum *) tlv->data;
		mtd->val = target->initialLogSyncInterval;
		datalen = sizeof(*mtd);
		respond = 1;
		break;
	case TLV_OPER_LOG_SYNC_INTERVAL:
		mtd = (struct management_tlv_datum *) tlv->data;
		mtd->val = target->operLogSyncInterval;
		datalen = sizeof(*mtd);
		respond = 1;
		break;
	case TLV_NEIGHBOR_PROP_DELAY:
		ptr32 = (uint32_t *) tlv->data;
		*ptr32 = htonl(target->neighborPropDelay);
		datalen = sizeof(uint32_t);
		respond = 1;
		break;
#endif
	case TLV_LOG_ANNOUNCE_INTERVAL:
		mtd = (struct management_tlv_datum *) tlv->data;
		mtd->val = target->logAnnounceInterval;
		datalen = sizeof(*mtd);
		respond = 1;
		break;
	case TLV_ANNOUNCE_RECEIPT_TIMEOUT:
		mtd = (struct management_tlv_datum *) tlv->data;
		mtd->val = target->announceReceiptTimeout;
		datalen = sizeof(*mtd);
		respond = 1;
		break;
	case TLV_LOG_SYNC_INTERVAL:
		mtd = (struct management_tlv_datum *) tlv->data;
		mtd->val = target->logSyncInterval;
		datalen = sizeof(*mtd);
		respond = 1;
		break;
	case TLV_VERSION_NUMBER:
		mtd = (struct management_tlv_datum *) tlv->data;
		mtd->val = target->versionNumber;
		datalen = sizeof(*mtd);
		respond = 1;
		break;
	case TLV_DELAY_MECHANISM:
		mtd = (struct management_tlv_datum *) tlv->data;
#ifdef KSZ_1588_PTP
		if (target->delayMechanism == DM_NONE)
			mtd->val = 0xFE;
		else
#endif
		if (target->delayMechanism)
			mtd->val = target->delayMechanism;
		else
			mtd->val = DM_E2E;
		datalen = sizeof(*mtd);
		respond = 1;
		break;
	case TLV_LOG_MIN_PDELAY_REQ_INTERVAL:
		mtd = (struct management_tlv_datum *) tlv->data;
		mtd->val = target->logMinPdelayReqInterval;
		datalen = sizeof(*mtd);
		respond = 1;
		break;
	case TLV_PORT_DATA_SET_NP:
		pdsnp = (struct port_ds_np *) tlv->data;
		pdsnp->neighborPropDelayThresh = target->neighborPropDelayThresh;
		pdsnp->asCapable = target->asCapable;
		datalen = sizeof(*pdsnp);
		respond = 1;
		break;
	case TLV_PORT_PROPERTIES_NP:
		ppn = (struct port_properties_np *)tlv->data;
		ppn->portIdentity = target->portIdentity;
		if (target->state == PS_GRAND_MASTER)
			ppn->port_state = PS_MASTER;
		else
			ppn->port_state = target->state;
		ppn->timestamping = target->timestamping;
		ptp_text_set(&ppn->interface, target->name);
		datalen = sizeof(*ppn) + ppn->interface.length;
		respond = 1;
		break;
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

static int port_management_get_response(struct port *target,
					struct port *ingress, int id,
					struct ptp_message *req)
{
	struct PortIdentity pid = port_identity(target);
	struct ptp_message *rsp;
	int respond;

	rsp = port_management_reply(pid, ingress, req);
	if (!rsp) {
		return 0;
	}
	respond = port_management_fill_response(target, rsp, id);
#ifdef KSZ_1588_PTP
	ingress->dest_port = ingress->receive_port;
#endif
	if (respond)
		port_prepare_and_send(ingress, rsp, 0);
	msg_put(rsp);
	return respond;
}

static int port_management_set(struct port *target,
			       struct port *ingress, int id,
			       struct ptp_message *req)
{
	int respond = 0;
	struct management_tlv *tlv;
	struct port_ds_np *pdsnp;
#ifdef KSZ_1588_PTP
	struct management_tlv_datum *mtd;
	uint32_t *ptr32;
	uint32_t val32;
	struct config *cfg = clock_config(target->clock);
#endif

	tlv = (struct management_tlv *) req->management.suffix;
#ifdef KSZ_1588_PTP
	mtd = (struct management_tlv_datum *) tlv->data;
	ptr32 = (uint32_t *) tlv->data;
#endif

	switch (id) {
	case TLV_PORT_DATA_SET_NP:
		pdsnp = (struct port_ds_np *) tlv->data;
		target->neighborPropDelayThresh = pdsnp->neighborPropDelayThresh;
		respond = 1;
		break;
#ifdef KSZ_1588_PTP
	case TLV_DISABLE_PORT:
		if (PS_DISABLED != target->state) {
			port_dispatch(target, EV_DESIGNATED_DISABLED, 0);
		}
		respond = 1;
		break;
	case TLV_ENABLE_PORT:
		if (PS_DISABLED == target->state) {
			port_dispatch(target, EV_DESIGNATED_ENABLED, 0);
			if (target->link_status) {
				if (port_is_aed_master(target))
					port_dispatch(target, EV_RS_GRAND_MASTER, 0);
				else if (port_is_aed(target))
					port_dispatch(target, EV_RS_SLAVE, 0);
			}
		}
		respond = 1;
		break;
	case TLV_MASTER_ONLY:
		if (target->master_only != mtd->val) {
			target->master_only = mtd->val;
			config_set_section_int(cfg, target->name,
					       "masterOnly",
					       target->master_only);
			cfg->changed = 1;
		}
		respond = 1;
		break;
	case TLV_INITIAL_LOG_PDELAY_REQ_INTERVAL:
		if (target->initialLogPdelayReqInterval != mtd->val) {
			target->initialLogPdelayReqInterval = mtd->val;
			config_set_section_int(cfg, target->name,
					       "initialLogPdelayReqInterval",
					       target->initialLogPdelayReqInterval);
			cfg->changed = 1;
		}
		respond = 1;
		break;
	case TLV_OPER_LOG_PDELAY_REQ_INTERVAL:
		if (target->operLogPdelayReqInterval != mtd->val) {
			target->operLogPdelayReqInterval = mtd->val;
			config_set_section_int(cfg, target->name,
					       "operLogPdelayReqInterval",
					       target->operLogPdelayReqInterval);
			cfg->changed = 1;
		}
		respond = 1;
		break;
	case TLV_INITIAL_LOG_SYNC_INTERVAL:
		if (target->initialLogSyncInterval != mtd->val) {
			target->initialLogSyncInterval = mtd->val;
			config_set_section_int(cfg, target->name,
					       "initialLogSyncInterval",
					       target->initialLogSyncInterval);
			cfg->changed = 1;
		}
		respond = 1;
		break;
	case TLV_OPER_LOG_SYNC_INTERVAL:
		if (target->operLogSyncInterval != mtd->val) {
			target->operLogSyncInterval = mtd->val;
			config_set_section_int(cfg, target->name,
					       "operLogSyncInterval",
					       target->operLogSyncInterval);
			cfg->changed = 1;
		}
		respond = 1;
		break;
	case TLV_NEIGHBOR_PROP_DELAY:
		val32 = ntohl(*ptr32);
		if (target->neighborPropDelay != val32) {
			target->neighborPropDelay = val32;
			config_set_section_int(cfg, target->name,
					       "neighborPropDelay",
					       target->neighborPropDelay);
			cfg->changed = 1;
		}
		respond = 1;
		break;
#endif
	}
	if (respond && !port_management_get_response(target, ingress, id, req))
		pr_err("port %hu: failed to send management set response", portnum(target));
	return respond ? 1 : 0;
}

static void port_nrate_calculate(struct port *p, tmv_t origin, tmv_t ingress)
{
	struct nrate_estimator *n = &p->nrate;

	/*
	 * We experienced a successful exchanges of peer delay request
	 * and response, reset pdr_missing for this port.
	 */
	p->pdr_missing = 0;
#ifdef KSZ_1588_PTP
	p->isMeasuringDelay = TRUE;
	p->lostResponses = FALSE;
#endif

	if (!n->ingress1) {
		n->ingress1 = ingress;
		n->origin1 = origin;
#ifdef KSZ_1588_PTP
		n->ingress2 = ingress;
		n->origin2 = origin;
#endif
		return;
	}
#ifdef KSZ_1588_PTP
	do {
		tmv_t diff;
		tmv_t other_interval;
		tmv_t own_interval;

		own_interval = tmv_sub(ingress, n->ingress2);
		other_interval = tmv_sub(origin, n->origin2);
		diff = tmv_sub(own_interval, other_interval);
		if (diff < 0)
			diff = -diff;
		n->ingress2 = ingress;
		n->origin2 = origin;

		/* Should not be bigger than 6,250,000 ns. */
		if (diff > NS_PER_SEC / 16)
			goto nrate_exit;
	} while (0);
#endif
	n->count++;
	if (n->count < n->max_count) {
		return;
	}
	if (tmv_eq(ingress, n->ingress1)) {
		pr_warning("bad timestamps in nrate calculation");
		return;
	}
	n->ratio =
		tmv_dbl(tmv_sub(origin, n->origin1)) /
		tmv_dbl(tmv_sub(ingress, n->ingress1));
#ifdef KSZ_1588_PTP
#if 1
	if (n->ratio > 1.01 || n->ratio < 0.99)
printf("ratio: %lf\n", n->ratio);
#endif
	if (n->ratio > 1.01 || n->ratio < 0.99)
		n->ratio = 1.0;

nrate_exit:
#endif
	n->ingress1 = ingress;
	n->origin1 = origin;
	n->count = 0;
	n->ratio_valid = 1;
}

static void port_nrate_initialize(struct port *p)
{
	int shift = p->freq_est_interval - p->logMinPdelayReqInterval;

	if (shift < 0)
		shift = 0;
	else if (shift >= sizeof(int) * 8) {
		shift = sizeof(int) * 8 - 1;
		pr_warning("freq_est_interval is too long");
	}

	/* We start in the 'incapable' state. */
	p->pdr_missing = ALLOWED_LOST_RESPONSES + 1;
	p->asCapable = 0;

#ifdef KSZ_1588_PTP
	if (p->no_asCapable)
		p->asCapable = 1;
#endif
	p->peer_portid_valid = 0;

	p->nrate.origin1 = tmv_zero();
	p->nrate.ingress1 = tmv_zero();
	p->nrate.max_count = (1 << shift);
	p->nrate.count = 0;
	p->nrate.ratio = 1.0;
	p->nrate.ratio_valid = 0;
}

static int port_set_announce_tmo(struct port *p)
{
#ifdef KSZ_DBG_HOST
if (!is_peer_port(p->clock, p))
printf("  !! %s\n", __func__);
#endif
	if (!p->ann_rx_timeout) {
#ifdef KSZ_DBG_TIMER
#if 0 
if (portnum(p) == 5)
#endif
printf(" %s %d\n", __func__, portnum(p));
#endif
		p->ann_rx_timeout = 1;
	}
	return set_tmo_random(p->fda.fd[FD_ANNOUNCE_TIMER],
			      p->announceReceiptTimeout,
			      p->announce_span, p->logAnnounceInterval);
}

static int port_set_delay_tmo(struct port *p)
{
#ifdef KSZ_DBG_HOST
if (!is_peer_port(p->clock, p))
printf("  !! %s %d\n", __func__, portnum(p));
#endif
	if (p->delayMechanism == DM_P2P) {
		if (p->logMinPdelayReqInterval == 127)
			return 0;
		return set_tmo_log(p->fda.fd[FD_DELAY_TIMER], 1,
			       p->logMinPdelayReqInterval);
	} else {

#ifdef KSZ_1588_PTP
		if (p->delayMechanism == DM_NONE)
			return 0;
#endif
		return set_tmo_random(p->fda.fd[FD_DELAY_TIMER], 0, 2,
				p->logMinDelayReqInterval);
	}
}

static int port_set_manno_tmo(struct port *p)
{
#ifdef KSZ_DBG_HOST
if (!is_host_port(p->clock, p))
printf("  !! %s\n", __func__);
#endif
	if (!p->ann_tx_timeout) {
#ifdef KSZ_DBG_TIMER
#if 0 
if (portnum(p) == 5)
#endif
printf(" %s %d\n", __func__, portnum(p));
#endif
		p->ann_tx_timeout = 1;
	}
	return set_tmo_log(p->fda.fd[FD_MANNO_TIMER], 1, p->logAnnounceInterval);
}

static int port_set_qualification_tmo(struct port *p)
{
	return set_tmo_log(p->fda.fd[FD_QUALIFICATION_TIMER],
		       1+clock_steps_removed(p->clock), p->logAnnounceInterval);
}

static int port_set_sync_rx_tmo(struct port *p)
{
#ifdef KSZ_DBG_HOST
if (!is_peer_port(p->clock, p))
printf("  !! %s\n", __func__);
#endif
	if (!p->sync_rx_timeout) {
#ifdef KSZ_DBG_TIMER
#if 0 
if (portnum(p) == 5)
#endif
printf(" %s %d=%u\n", __func__, portnum(p),
calculate_interval(p->syncReceiptTimeout, p->log_sync_interval));
#endif
		p->sync_rx_timeout = 1;
	}
#ifdef KSZ_DBG_TIMEOUT
	clock_gettime(CLOCK_MONOTONIC, &sync_ts);
#endif
	return set_tmo_log(p->fda.fd[FD_SYNC_RX_TIMER],
			   p->syncReceiptTimeout, p->logSyncInterval);
}

static int port_set_sync_tx_tmo(struct port *p)
{
#ifdef KSZ_DBG_HOST
if (!is_host_port(p->clock, p))
printf("  !! %s\n", __func__);
#endif
	if (!p->sync_tx_timeout) {
#ifdef KSZ_DBG_TIMER
#if 0 
if (portnum(p) == 5)
#endif
printf(" %s %d\n", __func__, portnum(p));
#endif
		p->sync_tx_timeout = 1;
	}
	return set_tmo_log(p->fda.fd[FD_SYNC_TX_TIMER], 1, p->logSyncInterval);
}

#ifdef KSZ_1588_PTP
#if 0
static int port_set_sync_fup_tx_tmo(struct port *p)
{
	if (!p->sync_tx_timeout) {
#ifdef KSZ_DBG_TIMER
#if 0
if (portnum(p) == 5)
#endif
printf(" %s %d\n", __func__, portnum(p));
#endif
		p->sync_tx_timeout = 1;
	}
	return set_tmo_us(p->fda.fd[FD_SYNC_TX_TIMER], 10000);
}
#endif

static int port_set_fup_rx_tmo(struct port *p)
{
	if (!p->fup_rx_timeout) {
#ifdef KSZ_DBG_TIMER
#if 1
if (portnum(p) == 5)
#endif
printf(" %s %d\n", __func__, portnum(p));
#endif
		p->fup_rx_timeout = 1;
	}
#ifdef KSZ_DBG_TIMEOUT
	clock_gettime(CLOCK_MONOTONIC, &fup_ts);
#endif
	return set_tmo_us(p->fda.fd[FD_FUP_RX_TIMER],
			  p->followUpReceiptTimeout);
}

static int port_set_sync_cont_tmo(struct port *p)
{
	if (!p->fup_tx_timeout) {
#ifdef KSZ_DBG_TIMER
if (portnum(p) == 5)
printf(" %s %d=%u\n", __func__, portnum(p), p->syncTxContTimeout);
#endif
		p->fup_tx_timeout = 1;
	}
	return set_tmo_us(p->fda.fd[FD_SYNC_CONT_TIMER],
			  p->syncTxContTimeout);
}

void port_update_grandmaster(struct port *p)
{
	if (!p->gm_change) {
#if 0
printf(" %s %p:%d\n", __func__, p, portnum(p));
#endif
		p->gm_change = 1;

		/* Stop self sync transmit. */
		if (port_is_ieee8021as(p) && p->sync_tx_timeout) {
#ifdef KSZ_DBG_TIMER
#if 0
if (portnum(p) == 5)
#endif
printf(" %s sync_tx %d\n", __func__, portnum(p));
#endif
			p->sync_tx_timeout = 0;
			port_clr_tmo(p->fda.fd[FD_SYNC_TX_TIMER]);
		}
	}
}

int port_get_info(struct port *p)
{
	int rc;
	u8 phys_port;
	u8 virt_port;
	u32 port_mask;

	rc = ptp_port_info(&ptpdev, p->basename, &phys_port, &virt_port,
			   &port_mask);
	if (!rc) {
		p->phys_port = phys_port;
		p->virt_port = virt_port;
		p->port_mask = port_mask;

		/* Need to use physical port in P2P. */
		if (get_hw_version(p->clock) <= 2) {
			if (is_peer_port(p->clock, p))
				phys_port = p->phys_port;
			else
				phys_port = ptp_host_port;
			if (p->portIdentity.portNumber != phys_port) {
#if 1
printf(" p:%d=%d\n", portnum(p), phys_port);
#endif
				p->portIdentity.portNumber = phys_port;
			}
		}
	}
	return rc;
}

int port_matched(struct port *p, int n)
{
	int port = p->phys_port;

	/* Use virtual port if available. */
	if (p->virt_port)
		port = p->virt_port;
	if (port == n)
		return TRUE;
	return FALSE;
}
#endif

static void port_show_transition(struct port *p,
				 enum port_state next, enum fsm_event event)
{
	if (event == EV_FAULT_DETECTED) {
		pr_notice("port %hu: %s to %s on %s (%s)", portnum(p),
			  ps_str[p->state], ps_str[next], ev_str[event],
			  ft_str(last_fault_type(p)));
	} else {
		pr_notice("port %hu: %s to %s on %s", portnum(p),
			  ps_str[p->state], ps_str[next], ev_str[event]);
	}
}

static void port_slave_priority_warning(struct port *p)
{
	UInteger16 n = portnum(p);
	pr_warning("port %hu: master state recommended in slave only mode", n);
	pr_warning("port %hu: defaultDS.priority1 probably misconfigured", n);
}

static int port_delay_request(struct port *p);
static void port_synchronize(struct port *p,
			     struct timespec ingress_ts,
			     struct timestamp origin_ts,
			     Integer64 correction1, Integer64 correction2)
{
	enum servo_state state;
	tmv_t t1, t1c, t2, c1, c2;

#ifdef KSZ_DBG_HOST
if (!is_peer_port(p->clock, p))
printf("  !! %s %d\n", __func__, portnum(p));
#endif
#if 0
printf("%s %d\n", __func__, portnum(p));
#endif
	port_set_sync_rx_tmo(p);

	t1 = timestamp_to_tmv(origin_ts);
	t2 = timespec_to_tmv(ingress_ts);
	c1 = correction_to_tmv(correction1);
	c2 = correction_to_tmv(correction2);
	t1c = tmv_add(t1, tmv_add(c1, c2));

	state = clock_synchronize(p->clock, t2, t1c);
#if 0
printf("%s %d %d\n", __func__, portnum(p), state);
#endif
	switch (state) {
	case SERVO_UNLOCKED:
		port_dispatch(p, EV_SYNCHRONIZATION_FAULT, 0);
		break;
	case SERVO_JUMP:
		port_dispatch(p, EV_SYNCHRONIZATION_FAULT, 0);
		if (p->delay_req) {
			msg_put(p->delay_req);
			p->delay_req = NULL;
		}
		if (p->peer_delay_req) {
			msg_put(p->peer_delay_req);
			p->peer_delay_req = NULL;
#ifdef KSZ_1588_PTP
			p->clear_pdelay_req = 1;
#endif
		}
		break;
	case SERVO_LOCKED:
		port_dispatch(p, EV_MASTER_CLOCK_SELECTED, 0);
#ifdef KSZ_1588_PTP
		if (p->best && p->best->bad_cnt) {
			if (p->rx_sec != p->last_rx_sec) {
				p->last_rx_sec = p->rx_sec;
				p->best->good_cnt++;
				if (p->best->good_cnt > 4) {
					p->best->good_cnt = 0;
					p->best->bad_cnt--;
					if (!p->best->bad_cnt)
						p->best->bad_master = 0;
				}
			}
		}
#endif
		break;
#ifdef KSZ_1588_PTP
	case SERVO_LOCKING:
		if (p->delay_req) {
			msg_put(p->delay_req);
			p->delay_req = NULL;
		}
		if (p->peer_delay_req) {
			msg_put(p->peer_delay_req);
			p->peer_delay_req = NULL;
			p->clear_pdelay_req = 1;
		}
#if 1
		if (p->delayMechanism == DM_E2E)
			port_delay_request(p);
#endif
		break;
#endif
	}
}

/*
 * Handle out of order packets. The network stack might
 * provide the follow up _before_ the sync message. After all,
 * they can arrive on two different ports. In addition, time
 * stamping in PHY devices might delay the event packets.
 */
static void port_syfufsm(struct port *p, enum syfu_event event,
			 struct ptp_message *m)
{
	struct ptp_message *syn, *fup;

	switch (p->syfu) {
	case SF_EMPTY:
		switch (event) {
		case SYNC_MISMATCH:
			msg_get(m);
			p->last_syncfup = m;
			p->syfu = SF_HAVE_SYNC;
			break;
		case FUP_MISMATCH:
#ifdef KSZ_1588_PTP
			/*
			 * Unlikely to receive Sync/Follow_Up messages not
			 * in sequence in 802.1AS.
			 */
			if (port_is_ieee8021as(p)) {
				break;
			}
#endif
			msg_get(m);
			p->last_syncfup = m;
			p->syfu = SF_HAVE_FUP;
			break;
		case SYNC_MATCH:
			break;
		case FUP_MATCH:
			break;
		}
		break;

	case SF_HAVE_SYNC:
		switch (event) {
		case SYNC_MISMATCH:
			msg_put(p->last_syncfup);
#ifdef KSZ_1588_PTP
			/*
			 * Unlikely to receive Sync/Follow_Up messages not
			 * in sequence in 802.1AS.
			 */
			if (port_is_ieee8021as(p)) {
				p->last_syncfup = NULL;
				p->syfu = SF_EMPTY;
				break;
			}
#endif
			msg_get(m);
			p->last_syncfup = m;
			break;
		case SYNC_MATCH:
			break;
		case FUP_MISMATCH:
			msg_put(p->last_syncfup);
#ifdef KSZ_1588_PTP
			/*
			 * Unlikely to receive Sync/Follow_Up messages not
			 * in sequence in 802.1AS.
			 */
			if (port_is_ieee8021as(p)) {
				p->last_syncfup = NULL;
				p->syfu = SF_EMPTY;
				break;
			}
#endif
			msg_get(m);
			p->last_syncfup = m;
			p->syfu = SF_HAVE_FUP;
			break;
		case FUP_MATCH:
			syn = p->last_syncfup;
			port_synchronize(p, syn->hwts.ts, m->ts.pdu,
					 syn->header.correction,
					 m->header.correction);
			/* May be removed in flush_last_sync(). */
			if (p->last_syncfup)
			msg_put(p->last_syncfup);
			p->syfu = SF_EMPTY;
			break;
		}
		break;

	case SF_HAVE_FUP:
		switch (event) {
		case SYNC_MISMATCH:
			msg_put(p->last_syncfup);
			msg_get(m);
			p->last_syncfup = m;
			p->syfu = SF_HAVE_SYNC;
			break;
		case SYNC_MATCH:
			fup = p->last_syncfup;
			port_synchronize(p, m->hwts.ts, fup->ts.pdu,
					 m->header.correction,
					 fup->header.correction);
			/* May be removed in flush_last_sync(). */
			if (p->last_syncfup)
			msg_put(p->last_syncfup);
			p->syfu = SF_EMPTY;
			break;
		case FUP_MISMATCH:
			msg_put(p->last_syncfup);
			msg_get(m);
			p->last_syncfup = m;
			break;
		case FUP_MATCH:
			break;
		}
		break;
	}
}

static int port_pdelay_request(struct port *p)
{
	struct ptp_message *msg;
	int err;

#ifdef KSZ_DBG_HOST
if (!is_peer_port(p->clock, p))
printf("  !! %s\n", __func__);
#endif
#ifndef KSZ_1588_PTP
	/* If multiple pdelay resp were not detected the counter can be reset */
	if (!p->multiple_pdr_detected)
		p->multiple_seq_pdr_count = 0;
	p->multiple_pdr_detected = 0;
#endif
#ifdef KSZ_1588_PTP
	if (p->tx_err)
printf(" pdelay_req %d ", portnum(p));
	if (!p->multiple_pdr_detected && p->multiple_seq_pdr_count)
		p->multiple_seq_pdr_count--;
	p->multiple_pdr_detected = 0;
#endif

	msg = msg_allocate();
	if (!msg)
		return -1;

	msg->hwts.type = p->timestamping;

	msg->header.tsmt               = PDELAY_REQ | p->transportSpecific;
	msg->header.ver                = PTP_VERSION;
	msg->header.messageLength      = sizeof(struct pdelay_req_msg);
	msg->header.domainNumber       = clock_domain_number(p->clock);
	msg->header.correction         = -p->asymmetry;
	msg->header.sourcePortIdentity = p->portIdentity;
	msg->header.sequenceId         = p->seqnum.delayreq++;
	msg->header.control            = CTL_OTHER;
	msg->header.logMessageInterval = port_is_ieee8021as(p) ?
		p->logMinPdelayReqInterval : 0x7f;

#ifdef KSZ_1588_PTP
	if (need_dest_port(p->clock) && p->pdelay_resp_port)
		msg->header.sourcePortIdentity.portNumber = p->pdelay_resp_port;
	msg->header.flagField[1] |= PTP_TIMESCALE;
	clock_gettime(CLOCK_MONOTONIC, &p->pdelay_req_ts);
#endif
	err = peer_prepare_and_send(p, msg, 1);
	if (err) {
		pr_err("port %hu: send peer delay request failed", portnum(p));
		goto out;
	}
#ifndef KSZ_1588_PTP
	if (msg_sots_missing(msg)) {
		pr_err("missing timestamp on transmitted peer delay request");
		goto out;
	}
#endif
#ifdef KSZ_1588_PTP
	if (port_is_aed(p)) {
#if 0
	if (p->neighborPropDelay && p->seqnumPdelayReq)
printf("  seqnum: %d=%04x\n", portnum(p), p->seqnumPdelayReq);
#endif
	if (p->neighborPropDelay && p->seqnumPdelayReq)
		p->seqnumPdelayReq--;
	}
#endif

	if (p->peer_delay_req) {
		if (port_capable(p)) {
			p->pdr_missing++;
			if (!p->lostResponses && p->isMeasuringDelay) {
#ifdef KSZ_DBG_MISS
				if (port_is_aed(p))
printf(" missing: %d=%d\n", portnum(p), p->pdr_missing);
				p->req_seqid = p->peer_delay_req->header.sequenceId;
#endif
				if (p->pdr_missing >= ALLOWED_LOST_RESPONSES) {
					p->lostResponses = TRUE;
					p->isMeasuringDelay = FALSE;
					if (p->log_exception)
						exception_log(p->clock,
							      "Pdelay response timeout at port %hu", portnum(p));
				}
			}
		}
		msg_put(p->peer_delay_req);
	}
	p->peer_delay_req = msg;
	return 0;
out:
	msg_put(msg);
	return -1;
}

static int port_delay_request(struct port *p)
{
	struct ptp_message *msg;

	/* Time to send a new request, forget current pdelay resp and fup */
	if (p->peer_delay_resp) {
		msg_put(p->peer_delay_resp);
		p->peer_delay_resp = NULL;
	}
	if (p->peer_delay_fup) {
		msg_put(p->peer_delay_fup);
		p->peer_delay_fup = NULL;
	}

	if (p->delayMechanism == DM_P2P)
		return port_pdelay_request(p);

#ifdef KSZ_DBG_HOST
if (!is_peer_port(p->clock, p))
printf("  !! %s\n", __func__);
#endif
	msg = msg_allocate();
	if (!msg)
		return -1;

	msg->hwts.type = p->timestamping;

	msg->header.tsmt               = DELAY_REQ | p->transportSpecific;
	msg->header.ver                = PTP_VERSION;
	msg->header.messageLength      = sizeof(struct delay_req_msg);
	msg->header.domainNumber       = clock_domain_number(p->clock);
	msg->header.correction         = -p->asymmetry;
	msg->header.sourcePortIdentity = p->portIdentity;
	msg->header.sequenceId         = p->seqnum.delayreq++;
	msg->header.control            = CTL_DELAY_REQ;
	msg->header.logMessageInterval = 0x7f;

	if (p->hybrid_e2e) {
		struct ptp_message *dst = TAILQ_FIRST(&p->best->messages);
		msg->address = dst->address;
		msg->header.flagField[0] |= UNICAST;
	}

#ifdef KSZ_1588_PTP
	msg->header.flagField[1] |= PTP_TIMESCALE;
	p->dest_port = get_master_port(p->clock);
#endif
	if (port_prepare_and_send(p, msg, 1)) {
		pr_err("port %hu: send delay request failed", portnum(p));
		goto out;
	}
#ifndef KSZ_1588_PTP
	if (msg_sots_missing(msg)) {
		pr_err("missing timestamp on transmitted delay request");
		goto out;
	}
#endif

	if (p->delay_req)
		msg_put(p->delay_req);

	p->delay_req = msg;
	return 0;
out:
	msg_put(msg);
	return -1;
}

#if 0
static unsigned char test_data[] = {
	0x0d, 0x00, 0x16, 0x00, 0xab, 0x56, 0x78, 0xab,
	0xcd, 0x00, 0x8b, 0xa0, 0xf9, 0x52, 0xf4, 0x40,
	0xff, 0x52, 0xad, 0xd1, 0x96, 0xee, 0x93, 0x55,
	0xe1, 0xad
};

static int test_append(struct port *p, struct ptp_message *m)
{
	u8 *tlv = m->announce.suffix;
	memcpy(tlv, test_data, sizeof(test_data));
	m->tlv_count = 1;
	return sizeof(test_data);
}
#endif

#ifdef KSZ_1588_PTP
static int prepare_sync(struct port *p)
{
	struct ptp_message *msg, *fup;
	int pdulen;

	msg = msg_allocate();
	if (!msg)
		return -1;
	fup = msg_allocate();
	if (!fup) {
		msg_put(msg);
		return -1;
	}

	pdulen = sizeof(struct sync_msg);
	msg->hwts.type = p->timestamping;

	msg->header.tsmt               = SYNC | p->transportSpecific;
	msg->header.ver                = PTP_VERSION;
	msg->header.messageLength      = pdulen;
	msg->header.domainNumber       = clock_domain_number(p->clock);
	msg->header.sourcePortIdentity = p->portIdentity;
	msg->header.sequenceId         = p->seqnum.sync++;
	msg->header.control            = CTL_SYNC;
	msg->header.logMessageInterval = p->logSyncInterval;

	if (p->timestamping != TS_ONESTEP)
		msg->header.flagField[0] |= TWO_STEP;

	msg->header.flagField[1] |= PTP_TIMESCALE;

	pdulen = sizeof(struct follow_up_msg);
	fup->hwts.type = p->timestamping;

	if (p->follow_up_info)
		pdulen += follow_up_info_append(p, fup);

	fup->header.tsmt               = FOLLOW_UP | p->transportSpecific;
	fup->header.ver                = PTP_VERSION;
	fup->header.messageLength      = pdulen;
	fup->header.domainNumber       = clock_domain_number(p->clock);
	fup->header.sourcePortIdentity = p->portIdentity;
	fup->header.sequenceId         = p->seqnum.sync - 1;
	fup->header.control            = CTL_FOLLOW_UP;
	fup->header.logMessageInterval = p->logSyncInterval;
	fup->header.flagField[1] |= PTP_TIMESCALE;

	get_hw_clock(p->clock, &msg->hwts.ts);
	ts_to_timestamp(&msg->hwts.ts, &fup->follow_up.preciseOriginTimestamp);

	p->last_sync = msg;
	p->last_fup = fup;
	return 0;
}
#endif

static int port_tx_announce(struct port *p)
{
	struct parent_ds *dad = clock_parent_ds(p->clock);
	struct timePropertiesDS *tp = clock_time_properties(p->clock);
	struct ptp_message *msg;
	int err, pdulen;

#ifdef KSZ_DBG_HOST
if (!is_host_port(p->clock, p))
printf("  !! %s\n", __func__);
#endif
#if 0
if (portnum(p) == 5)
printf("tx ann: %d=%x\n", portnum(p), p->seqnum.announce);
#endif
#ifdef KSZ_1588_PTP
	if (p->no_announce) {
printf("  !! %s\n", __func__);
		return 0;
	}
#endif
	p->tx_ann = 1;
	if (!port_capable(p)) {
		return 0;
	}
	msg = msg_allocate();
	if (!msg)
		return -1;

	pdulen = sizeof(struct announce_msg);
	msg->hwts.type = p->timestamping;

	if (p->path_trace_enabled)
		pdulen += path_trace_append(p, msg, dad);
#ifdef KSZ_1588_PTP
	if (clock_c37_238(p->clock))
		pdulen += c37_238_append(p, msg);
#if 0
pdulen += test_append(p, msg);
#endif
#endif

	msg->header.tsmt               = ANNOUNCE | p->transportSpecific;
	msg->header.ver                = PTP_VERSION;
	msg->header.messageLength      = pdulen;
	msg->header.domainNumber       = clock_domain_number(p->clock);
	msg->header.sourcePortIdentity = p->portIdentity;
	msg->header.sequenceId         = p->seqnum.announce++;
	msg->header.control            = CTL_OTHER;
	msg->header.logMessageInterval = p->logAnnounceInterval;

	msg->header.flagField[1] = tp->flags;

	msg->announce.currentUtcOffset        = tp->currentUtcOffset;
	msg->announce.grandmasterPriority1    = dad->pds.grandmasterPriority1;
	msg->announce.grandmasterClockQuality = dad->pds.grandmasterClockQuality;
	msg->announce.grandmasterPriority2    = dad->pds.grandmasterPriority2;
	msg->announce.grandmasterIdentity     = dad->pds.grandmasterIdentity;
	msg->announce.stepsRemoved            = clock_steps_removed(p->clock);
	msg->announce.timeSource              = tp->timeSource;

#ifdef KSZ_1588_PTP
	p->dest_port = 0;
	if (p->gm_change) {
		p->gm_change = 0;
	}
#endif
	err = port_prepare_and_send(p, msg, 0);
	if (err)
		pr_err("port %hu: send announce failed", portnum(p));
	msg_put(msg);
	return err;
}

static int port_tx_sync(struct port *p)
{
	struct ptp_message *msg, *fup;
	int err, pdulen;
	int event = p->timestamping == TS_ONESTEP ? TRANS_ONESTEP : TRANS_EVENT;

#ifdef KSZ_DBG_HOST
if (!is_host_port(p->clock, p))
printf("  !! %s\n", __func__);
#endif
	p->tx_ann = 0;
	if (!port_capable(p)) {
		return 0;
	}
	if (port_sync_incapable(p)) {
		return 0;
	}
#ifdef KSZ_1588_PTP
	if (p->sync) {
		msg = p->sync;
		p->sync = NULL;
		msg_put(msg);
	}
	if (p->follow_up) {
		msg = p->follow_up;
		p->follow_up = NULL;
		msg_put(msg);
	}
#endif
	msg = msg_allocate();
	if (!msg)
		return -1;
	fup = msg_allocate();
	if (!fup) {
		msg_put(msg);
		return -1;
	}

	pdulen = sizeof(struct sync_msg);
	msg->hwts.type = p->timestamping;

	msg->header.tsmt               = SYNC | p->transportSpecific;
	msg->header.ver                = PTP_VERSION;
	msg->header.messageLength      = pdulen;
	msg->header.domainNumber       = clock_domain_number(p->clock);
	msg->header.sourcePortIdentity = p->portIdentity;
	msg->header.sequenceId         = p->seqnum.sync++;
	msg->header.control            = CTL_SYNC;
	msg->header.logMessageInterval = p->logSyncInterval;
	if (p->last_sync && !p->sync_max && p->fwd_sync)
		msg->header.logMessageInterval =
			p->last_sync->header.logMessageInterval;

	if (p->timestamping != TS_ONESTEP)
		msg->header.flagField[0] |= TWO_STEP;

#ifdef KSZ_1588_PTP
	msg->header.flagField[1] |= PTP_TIMESCALE;
	p->dest_port = 0;
	if (get_hw_version(p->clock) < 2)
		p->dest_port = all_ports(p->clock);
	if (port_is_ieee8021as(p) && p->last_sync) {
		msg->header.correction = p->last_sync->header.correction;
		msg->sync.originTimestamp = p->last_sync->sync.originTimestamp;
	}
	if (is_host_port(p->clock, p) && !is_peer_port(p->clock, p) &&
	    event == TRANS_EVENT)
		event = TRANS_DEFER_EVENT;
#endif
	err = port_prepare_and_send(p, msg, event);
	if (err) {
		pr_err("port %hu: send sync failed", portnum(p));
		goto out;
	}
	if (p->timestamping == TS_ONESTEP) {
		goto out;
	} else if (msg_sots_missing(msg)) {
#ifdef KSZ_1588_PTP
		err = 0;
		msg_get(msg);
		if (p->sync)
			msg_put(p->sync);
		p->sync = msg;
		msg_get(fup);
		if (p->follow_up)
			msg_put(p->follow_up);
		p->follow_up = fup;
#else
		pr_err("missing timestamp on transmitted sync");
		err = -1;
#endif
		goto out;
	}

	/*
	 * Send the follow up message right away.
	 */
	pdulen = sizeof(struct follow_up_msg);
	fup->hwts.type = p->timestamping;

	if (p->follow_up_info)
		pdulen += follow_up_info_append(p, fup);

	fup->header.tsmt               = FOLLOW_UP | p->transportSpecific;
	fup->header.ver                = PTP_VERSION;
	fup->header.messageLength      = pdulen;
	fup->header.domainNumber       = clock_domain_number(p->clock);
	fup->header.sourcePortIdentity = p->portIdentity;
	fup->header.sequenceId         = p->seqnum.sync - 1;
	fup->header.control            = CTL_FOLLOW_UP;
	fup->header.logMessageInterval = p->logSyncInterval;
	if (p->last_sync && !p->sync_max && p->fwd_sync)
		fup->header.logMessageInterval =
			p->last_sync->header.logMessageInterval;
	fup->header.flagField[1] |= PTP_TIMESCALE;

	ts_to_timestamp(&msg->hwts.ts, &fup->follow_up.preciseOriginTimestamp);
#ifdef KSZ_1588_PTP
	if (port_is_ieee8021as(p) && p->last_fup) {
		tmv_t egress, ingress = timespec_to_tmv(p->last_sync->hwts.ts);
		tmv_t residence;
		double rr;
		Integer64 c1, c2;

		egress = timespec_to_tmv(msg->hwts.ts);
		residence = tmv_sub(egress, ingress);
		rr = clock_rate_ratio(p->clock);
		if (rr != 1.0) {
			residence = dbl_tmv(tmv_dbl(residence) * rr);
		}
		fup->header.correction = p->last_fup->header.correction;
		c1 = fup->header.correction;
		c2 = c1 + tmv_to_TimeInterval(residence);
		c2 += tmv_to_TimeInterval(p->peer_delay);
		c2 += p->asymmetry;
		fup->header.correction = c2;
		ts_to_ts(&p->last_fup->follow_up.preciseOriginTimestamp,
			 &fup->follow_up.preciseOriginTimestamp);
#if 0
		fup->follow_up.preciseOriginTimestamp.seconds_lsb =
			ntohl(p->last_fup->follow_up.preciseOriginTimestamp.
			seconds_lsb);
		fup->follow_up.preciseOriginTimestamp.seconds_msb =
			ntohs(p->last_fup->follow_up.preciseOriginTimestamp.
			seconds_msb);
		fup->follow_up.preciseOriginTimestamp.nanoseconds =
			ntohl(p->last_fup->follow_up.preciseOriginTimestamp.
			nanoseconds);
#endif
	}
#endif

	err = port_prepare_and_send(p, fup, 0);
	if (err)
		pr_err("port %hu: send follow up failed", portnum(p));
out:
	msg_put(msg);
	msg_put(fup);
	return err;
}

#ifdef KSZ_1588_PTP
static int port_tx_signaling(struct port *p)
{
	struct ptp_message *msg;
	int err, pdulen;

	msg = msg_allocate();
	if (!msg)
		return -1;

	pdulen = sizeof(struct signaling_msg);
	msg->hwts.type = p->timestamping;

	pdulen += interval_info_append(p, msg);

	msg->header.tsmt               = SIGNALING | p->transportSpecific;
	msg->header.ver                = PTP_VERSION;
	msg->header.messageLength      = pdulen;
	msg->header.domainNumber       = clock_domain_number(p->clock);
	msg->header.sourcePortIdentity = p->portIdentity;
	msg->header.sequenceId         = p->seqnum.signal++;
	msg->header.control            = CTL_OTHER;
	msg->header.logMessageInterval = 0x7f;

	memset(&msg->signaling.targetPortIdentity, 0xff,
		sizeof(struct PortIdentity));

	p->dest_port = 0;
	err = port_prepare_and_send(p, msg, 0);
	if (err)
		pr_err("port %hu: send signaling failed", portnum(p));
	msg_put(msg);
	return err;
}
#endif

/*
 * port initialize and disable
 */
static int port_is_enabled(struct port *p)
{
	switch (p->state) {
	case PS_INITIALIZING:
	case PS_FAULTY:
	case PS_DISABLED:
		return 0;
	case PS_LISTENING:
	case PS_PRE_MASTER:
	case PS_MASTER:
	case PS_GRAND_MASTER:
	case PS_PASSIVE:
	case PS_UNCALIBRATED:
	case PS_SLAVE:
		break;
	}
	return 1;
}

static void flush_last_sync(struct port *p)
{
	if (p->syfu != SF_EMPTY) {
		msg_put(p->last_syncfup);
		p->last_syncfup = NULL;
		p->syfu = SF_EMPTY;
	}
}

static void flush_delay_req(struct port *p)
{
	if (p->delay_req) {
		msg_put(p->delay_req);
		p->delay_req = NULL;
	}
}

static void flush_peer_delay(struct port *p)
{
	if (p->peer_delay_req) {
		msg_put(p->peer_delay_req);
		p->peer_delay_req = NULL;
	}
	if (p->peer_delay_resp) {
		msg_put(p->peer_delay_resp);
		p->peer_delay_resp = NULL;
	}
	if (p->peer_delay_fup) {
		msg_put(p->peer_delay_fup);
		p->peer_delay_fup = NULL;
	}
#ifdef KSZ_1588_PTP
	if (p->sync) {
		msg_put(p->sync);
		p->sync = NULL;
	}
	if (p->follow_up) {
		msg_put(p->follow_up);
		p->follow_up = NULL;
	}
	if (p->delay_resp) {
		msg_put(p->delay_resp);
		p->delay_resp = NULL;
	}
	if (p->pdelay_resp) {
		msg_put(p->pdelay_resp);
		p->pdelay_resp = NULL;
	}
	if (p->pdelay_resp_fup) {
		msg_put(p->pdelay_resp_fup);
		p->pdelay_resp_fup = NULL;
	}
	p->clear_pdelay_req = 1;
#endif
}

void port_clear_sync_fup(struct port *p, void *param)
{
	if (p->last_sync) {
		msg_put(p->last_sync);
		p->last_sync = NULL;
	}
	if (p->last_fup) {
		msg_put(p->last_fup);
		p->last_fup = NULL;
	}
}

void port_restart_tx(struct port *p, void *param)
{
	p->gm_change = 1;

	/* Stop continuous sync transmit. */
	port_clr_tmo(p->fda.fd[FD_SYNC_CONT_TIMER]);
	if (p->fup_tx_timeout) {
#ifdef KSZ_DBG_TIMER
if (portnum(p) == 5)
printf(" %s fup_tx %d\n", __func__, portnum(p));
#endif
		p->fup_tx_timeout = 0;
	}

	/* Want to send Announce for new grandmaster. */
	if (!p->no_announce) {
		set_tmo_log(p->fda.fd[FD_MANNO_TIMER], 1, -10); /*~1ms*/
		if (!p->ann_tx_timeout) {
			p->ann_tx_timeout = 1;
		}
	}
	if (!p->no_announce || p->master_only)
		port_set_sync_tx_tmo(p);
}

void port_stop_tx(struct port *p, void *param)
{
	port_dispatch(p, EV_RS_GRAND_MASTER, 0);
	port_clr_tmo(p->fda.fd[FD_MANNO_TIMER]);
	if (p->ann_tx_timeout) {
		p->ann_tx_timeout = 0;
	}
	port_clr_tmo(p->fda.fd[FD_SYNC_TX_TIMER]);
	if (p->sync_tx_timeout) {
		p->sync_tx_timeout = 0;
	}
}

void port_set_last_sync_fup(struct port *p, void *param)
{
	struct port *q = param;

	if (!port_is_enabled(p))
		return;
	if (p->last_sync)
		msg_put(p->last_sync);
	p->last_sync = q->last_sync;
	if (p->last_sync)
		msg_get(p->last_sync);
	if (p->last_fup)
		msg_put(p->last_fup);
	p->last_fup = q->last_fup;
	if (p->last_fup)
		msg_get(p->last_fup);
}

static void port_set_sync_timeout(struct port *p, void *param)
{
	uint32_t *timeout = param;

	if (!p->sync_max) {
		p->actual_sync_interval = *timeout + 100;
		p->syncTxContTimeout = p->actual_sync_interval;
	} else
		p->syncTxContTimeout = p->actual_sync_interval + 100000;
}

void port_tx_last_sync(struct port *p, void *param)
{
	struct timespec *now = param;
	tmv_t t = timespec_to_tmv(*now);

	if (p->state != PS_MASTER && p->state != PS_GRAND_MASTER)
		return;
	if (t > p->last_tx_sync_tmv &&
	    t - p->last_tx_sync_tmv < 20000000ULL)
		return;
	port_tx_sync(p);
}

void port_reset_sync_interval(struct port *p, void *param)
{
	p->sync_interval = calculate_interval(1, p->logSyncInterval);
	p->actual_sync_interval = p->sync_interval;
	p->syncTxContTimeout = p->sync_interval;
	port_set_sync_cont_tmo(p);
}

static void for_all_ports(struct port *p,
			  void (*func)(struct port *p, void *), void *param)
{
	struct port *q;

	for (q = clock_first_port(p->clock); q; q = LIST_NEXT(q, list)) {
		if (portnum(q) == 0)
			continue;
		func(q, param);
	}
}

static void for_other_ports(struct port *p,
			    void (*func)(struct port *p, void *), void *param)
{
	struct port *q;

	for (q = clock_first_port(p->clock); q; q = LIST_NEXT(q, list)) {
		if (q == p || portnum(q) == 0)
			continue;
		func(q, param);
	}
}

static void determine_sync_interval(struct port *p)
{
	struct timespec now;
	tmv_t t;

	clock_gettime(CLOCK_MONOTONIC, &now);
	t = timespec_to_tmv(now);
	if (p->last_sync_tmv) {
		int64_t diff = t - p->last_sync_tmv;

		if (diff > 0 && diff < 8000000000) {
			int offset;

			diff /= 1000;
			offset = (int)diff - p->sync_interval;
			if (offset > 0 && offset < 30000) {
				diff /= 10;
				diff *= 10;
				if (diff > p->actual_sync_interval) {
					p->actual_sync_interval = (u32)diff;
					for_other_ports(p,
							port_set_sync_timeout,
							&p->actual_sync_interval);
#ifdef KSZ_DBG_TIMEOUT
printf(" sync_interval: %u\n", p->actual_sync_interval);
#endif
				}
			}
		}
	}
	p->last_sync_tmv = t;
}

static void port_clear_fda(struct port *p, int count)
{
	int i;

	for (i = 0; i < count; i++)
		p->fda.fd[i] = -1;
}

static void port_disable(struct port *p)
{
	int i;

#ifdef KSZ_1588_PTP
	/* Port 0 can be IEEE 802.1AS port. */
	if (p->asCapable && port_is_ieee8021as(p) && portnum(p) > 0)
		port_set_port_cfg(p, 1, 0);
	p->tx_ann = 0;
	if (portnum(p) > 0) {
#ifdef KSZ_DBG_MISS
printf("%d=%u:%u %u:%u\n", portnum(p),
	p->sync_rx, p->fup_rx, p->sync_tx, p->fup_tx);
#endif
		p->sync_rx = 0;
		p->sync_tx = 0;
		p->fup_rx = 0;
		p->fup_tx = 0;
	}
	if (p->last_announce) {
		msg_put(p->last_announce);
		p->last_announce = NULL;
	}
	if (p->prev_announce) {
		msg_put(p->prev_announce);
		p->prev_announce = NULL;
	}
	if (p->last_sync) {
		msg_put(p->last_sync);
		p->last_sync = NULL;
	}
	if (p->last_fup) {
		msg_put(p->last_fup);
		p->last_fup = NULL;
	}
#endif
	flush_last_sync(p);
	flush_delay_req(p);
	flush_peer_delay(p);

	p->best = NULL;
	free_foreign_masters(p);
	transport_close(p->trp, &p->fda);

	for (i = 0; i < N_TIMER_FDS; i++) {
		close(p->fda.fd[FD_ANNOUNCE_TIMER + i]);
	}
	port_clear_fda(p, N_POLLFD);
	clock_fda_changed(p->clock);
}

static int port_initialize(struct port *p)
{
	struct config *cfg = clock_config(p->clock);
	int fd[N_TIMER_FDS], i;

	p->multiple_seq_pdr_count  = 0;
	p->multiple_pdr_detected   = 0;
	p->last_fault_type         = FT_UNSPECIFIED;
	p->logMinDelayReqInterval  = config_get_int(cfg, p->name, "logMinDelayReqInterval");
	p->peerMeanPathDelay       = 0;
	p->logAnnounceInterval     = config_get_int(cfg, p->name, "logAnnounceInterval");
	p->announceReceiptTimeout  = config_get_int(cfg, p->name, "announceReceiptTimeout");
	p->syncReceiptTimeout      = config_get_int(cfg, p->name, "syncReceiptTimeout");
	p->transportSpecific       = config_get_int(cfg, p->name, "transportSpecific");
	p->transportSpecific     <<= 4;
	p->logSyncInterval         = config_get_int(cfg, p->name, "logSyncInterval");
	p->logMinPdelayReqInterval = config_get_int(cfg, p->name, "logMinPdelayReqInterval");
	p->neighborPropDelayThresh = config_get_int(cfg, p->name, "neighborPropDelayThresh");
	p->min_neighbor_prop_delay = config_get_int(cfg, p->name, "min_neighbor_prop_delay");
#ifdef KSZ_1588_PTP
	p->followUpReceiptTimeout  = config_get_int(cfg, p->name, "followUpReceiptTimeout");
	if (p->follow_up_info)
		p->tc_spanning_tree = 1;
	if (p->follow_up_info && p->no_asCapable) {
		p->master_only = config_get_int(cfg, p->name, "masterOnly");
		p->initialLogPdelayReqInterval = config_get_int(cfg, p->name, "initialLogPdelayReqInterval");
		if (p->initialLogPdelayReqInterval == 127 && !p->master_only)
			p->initialLogPdelayReqInterval = 0;
		p->operLogPdelayReqInterval = config_get_int(cfg, p->name, "operLogPdelayReqInterval");
		if (p->operLogPdelayReqInterval == 127 && !p->master_only)
			p->operLogPdelayReqInterval = 0;
		p->initialLogSyncInterval = config_get_int(cfg, p->name, "initialLogSyncInterval");
		p->operLogSyncInterval = config_get_int(cfg, p->name, "operLogSyncInterval");
		p->neighborPropDelay = config_get_int(cfg, p->name, "neighborPropDelay");
		p->logSyncInterval = p->initialLogSyncInterval;
		p->logMinPdelayReqInterval = p->initialLogPdelayReqInterval;
		p->report_announce = 1;
		if (!p->master_only)
			p->report_signaling = 1;
		else
			p->report_sync = 1;
		p->report_interval = 0;
		p->max_pdelay_req = 1;
	}
	p->log_sync_interval = 8;
	p->sync_interval = calculate_interval(1, p->logSyncInterval);
	p->actual_sync_interval = p->sync_interval;
	if (p->follow_up_info) {
		p->followUpReceiptTimeout = p->sync_interval;
		if (p->followUpReceiptTimeout > 125000)
			p->followUpReceiptTimeout = 125000;

		/* Use longer timeout the first time. */
		p->syncTxContTimeout = p->actual_sync_interval + 100000;
	}
#endif

	for (i = 0; i < N_TIMER_FDS; i++) {
		fd[i] = -1;
	}
	for (i = 0; i < N_TIMER_FDS; i++) {
		fd[i] = timerfd_create(CLOCK_MONOTONIC, 0);
		if (fd[i] < 0) {
			pr_err("timerfd_create: %s", strerror(errno));
			goto no_timers;
		}
	}
	if (transport_open(p->trp, p->name, &p->fda, p->timestamping))
		goto no_tropen;

	for (i = 0; i < N_TIMER_FDS; i++) {
		p->fda.fd[FD_ANNOUNCE_TIMER + i] = fd[i];
	}

#ifdef KSZ_1588_PTP
	if (is_peer_port(p->clock, p))
#endif
	if (port_set_announce_tmo(p))
		goto no_tmo;

	port_nrate_initialize(p);

	clock_fda_changed(p->clock);
	return 0;

no_tmo:
	transport_close(p->trp, &p->fda);
no_tropen:
no_timers:
	for (i = 0; i < N_TIMER_FDS; i++) {
		if (fd[i] >= 0)
			close(fd[i]);
	}
	return -1;
}

static int port_renew_transport(struct port *p)
{
	int res;

	if (!port_is_enabled(p)) {
		return 0;
	}
	transport_close(p->trp, &p->fda);
	port_clear_fda(p, FD_ANNOUNCE_TIMER);
	res = transport_open(p->trp, p->name, &p->fda, p->timestamping);
	/* Need to call clock_fda_changed even if transport_open failed in
	 * order to update clock to the now closed descriptors. */
	clock_fda_changed(p->clock);
	return res;
}

/*
 * Returns non-zero if the announce message is different than last.
 */
static int update_current_master(struct port *p, struct ptp_message *m)
{
	struct foreign_clock *fc = p->best;
	struct ptp_message *tmp;
#ifndef KSZ_1588_PTP
	struct parent_ds *dad;
	struct path_trace_tlv *ptt;
#endif
	struct timePropertiesDS tds;

#ifdef KSZ_DBG_HOST
if (!is_peer_port(p->clock, p))
printf(" !! %s\n", __func__);
#endif
	if (!msg_source_equal(m, fc))
		return add_foreign_master(p, m);

	if (p->state != PS_PASSIVE) {
		tds.currentUtcOffset = m->announce.currentUtcOffset;
		tds.flags = m->header.flagField[1];
		tds.timeSource = m->announce.timeSource;
		clock_update_time_properties(p->clock, tds);
	}
#ifndef KSZ_1588_PTP
	/* Update pathTrace in clock_update_slave(). */
	if (p->path_trace_enabled) {
		ptt = (struct path_trace_tlv *) m->announce.suffix;
		dad = clock_parent_ds(p->clock);
		memcpy(dad->ptl, ptt->cid, ptt->length);
		dad->path_length = path_length(ptt);
	}
#endif
	port_set_announce_tmo(p);
	fc_prune(fc);
	msg_get(m);
	fc->n_messages++;
	TAILQ_INSERT_HEAD(&fc->messages, m, list);
	if (fc->n_messages > 1) {
		tmp = TAILQ_NEXT(m, list);
		return announce_compare(m, tmp);
	}
	return 0;
}

struct dataset *port_best_foreign(struct port *port)
{
	return port->best ? &port->best->dataset : NULL;
}

/* message processing routines */

/*
 * Returns non-zero if the announce message is both qualified and different.
 */
static int process_announce(struct port *p, struct ptp_message *m)
{
	int result = 0;

#ifdef KSZ_1588_PTP
	p->announce_ok = 0;
	if (p->no_announce && p->report_announce) {
		exception_log(p->clock, "Announce received at port %hu",
			      portnum(p));
		p->report_announce = 0;
	}
	if (p->no_announce)
		return result;
#ifdef KSZ_DBG_MISS
	if (((p->ann_seqid + 1) & 0xffff) != m->header.sequenceId &&
	    p->ann_seqid)
printf(" ann %d=%04x %04x\n", portnum(p),
	p->ann_seqid, m->header.sequenceId);
	p->ann_seqid = m->header.sequenceId;
#endif
	if (clock_c37_238(p->clock)) {
		struct ieee_c37_238_data *c37;
		struct alternate_time_offset_tlv *alt;

		if (!c37_238_extract(m, &c37, &alt))
			return result;
	}

	/* Grandmaster cannot be self. */
	if (!memcmp(&p->portIdentity.clockIdentity,
	    &m->announce.grandmasterIdentity, sizeof(struct ClockIdentity)))
		return result;
#endif
	/* Do not qualify announce messages with stepsRemoved >= 255, see
	 * IEEE1588-2008 section 9.3.2.5 (d)
	 */
	if (m->announce.stepsRemoved >= 255)
		return result;

	switch (p->state) {
	case PS_INITIALIZING:
	case PS_FAULTY:
	case PS_DISABLED:
		break;
	case PS_LISTENING:
	case PS_PRE_MASTER:
	case PS_MASTER:
	case PS_GRAND_MASTER:
		result = add_foreign_master(p, m);
		p->announce_ok = 1;
		break;
	case PS_PASSIVE:
	case PS_UNCALIBRATED:
	case PS_SLAVE:
		result = update_current_master(p, m);
		p->announce_ok = 1;
		break;
	}
	return result;
}

static int process_delay_req(struct port *p, struct ptp_message *m)
{
	struct ptp_message *msg;
	int err;

	if (p->state != PS_MASTER && p->state != PS_GRAND_MASTER)
		return 0;

	if (p->delayMechanism == DM_P2P) {
		pr_warning("port %hu: delay request on P2P port", portnum(p));
		return 0;
	}

	msg = msg_allocate();
	if (!msg)
		return -1;

	msg->hwts.type = p->timestamping;

	msg->header.tsmt               = DELAY_RESP | p->transportSpecific;
	msg->header.ver                = PTP_VERSION;
	msg->header.messageLength      = sizeof(struct delay_resp_msg);
	msg->header.domainNumber       = m->header.domainNumber;
	msg->header.correction         = m->header.correction;
	msg->header.sourcePortIdentity = p->portIdentity;
	msg->header.sourcePortIdentity = p->host_port->portIdentity;
	msg->header.sequenceId         = m->header.sequenceId;
	msg->header.control            = CTL_DELAY_RESP;
	msg->header.logMessageInterval = p->logMinDelayReqInterval;

	ts_to_timestamp(&m->hwts.ts, &msg->delay_resp.receiveTimestamp);

	msg->delay_resp.requestingPortIdentity = m->header.sourcePortIdentity;

	if (p->hybrid_e2e && m->header.flagField[0] & UNICAST) {
		msg->address = m->address;
		msg->header.flagField[0] |= UNICAST;
		msg->header.logMessageInterval = 0x7f;
	}

#ifdef KSZ_1588_PTP
	msg->header.flagField[1] |= PTP_TIMESCALE;
	p->dest_port = p->receive_port;
#endif
	err = port_prepare_and_send(p, msg, 0);
	if (err)
		pr_err("port %hu: send delay response failed", portnum(p));
	msg_put(msg);
	return err;
}

static void process_delay_resp(struct port *p, struct ptp_message *m)
{
	struct delay_req_msg *req;
	struct delay_resp_msg *rsp = &m->delay_resp;
	struct PortIdentity master;
	tmv_t c3, t3, t4, t4c;

	if (!p->delay_req)
		return;

	master = clock_parent_identity(p->clock);
	req = &p->delay_req->delay_req;

	if (p->state != PS_UNCALIBRATED && p->state != PS_SLAVE)
		return;
	if (!pid_eq(&rsp->requestingPortIdentity, &req->hdr.sourcePortIdentity))
		return;
	if (rsp->hdr.sequenceId != ntohs(req->hdr.sequenceId))
		return;
	if (!pid_eq(&master, &m->header.sourcePortIdentity))
		return;

#ifdef KSZ_1588_PTP
	if (msg_sots_missing(p->delay_req)) {
		if (p->delay_resp)
			msg_put(p->delay_resp);
		p->delay_resp = m;
	} else
		p->delay_resp = NULL;
	if (msg_sots_missing(p->delay_req))
		goto next;
#endif
	c3 = correction_to_tmv(m->header.correction);
	t3 = timespec_to_tmv(p->delay_req->hwts.ts);
	t4 = timestamp_to_tmv(m->ts.pdu);
	t4c = tmv_sub(t4, c3);

	clock_path_delay(p->clock, t3, t4c);

#ifdef KSZ_1588_PTP
next:
#endif
	if (p->logMinDelayReqInterval == rsp->hdr.logMessageInterval) {
		return;
	}
	if (m->header.flagField[0] & UNICAST) {
		/* Unicast responses have logMinDelayReqInterval set to 0x7F. */
		return;
	}
	if (rsp->hdr.logMessageInterval < -10 ||
	    rsp->hdr.logMessageInterval > 22) {
		pl_info(300, "port %hu: ignore bogus delay request interval 2^%d",
			portnum(p), rsp->hdr.logMessageInterval);
		return;
	}
	p->logMinDelayReqInterval = rsp->hdr.logMessageInterval;
	pr_notice("port %hu: minimum delay request interval 2^%d",
		  portnum(p), p->logMinDelayReqInterval);
}

static void process_follow_up(struct port *p, struct ptp_message *m)
{
	enum syfu_event event;
	struct PortIdentity master;
#ifdef KSZ_DBG_MISS
	if (((p->fup_seqid + 1) & 0xffff) != m->header.sequenceId &&
	    p->fup_seqid)
printf(" fup %d=%04x %04x\n", portnum(p),
	p->fup_seqid, m->header.sequenceId);
	p->fup_seqid = m->header.sequenceId;
#endif
#ifdef KSZ_DBG_TIMEOUT
	if (fup_to_id && fup_to_id + 1 != m->header.sequenceId)
printf(" fup to id %x\n", m->header.sequenceId);
	fup_to_id = 0;
#endif
	p->sync_fup_ok = 0;
	switch (p->state) {
	case PS_INITIALIZING:
	case PS_FAULTY:
	case PS_DISABLED:
	case PS_LISTENING:
	case PS_PRE_MASTER:
	case PS_MASTER:
	case PS_GRAND_MASTER:
	case PS_PASSIVE:
		return;
	case PS_UNCALIBRATED:
	case PS_SLAVE:
		break;
	}
	master = clock_parent_identity(p->clock);
#ifdef KSZ_1588_PTP
	if (!skip_sync_check(p->clock) && !p->no_announce)
#endif
	if (memcmp(&master, &m->header.sourcePortIdentity, sizeof(master)))
		return;

	if (p->follow_up_info) {
		struct follow_up_info_tlv *fui = follow_up_info_extract(m);
		if (!fui)
			return;
		clock_follow_up_info(p->clock, fui);
	}

	if (p->syfu == SF_HAVE_SYNC &&
	    p->last_syncfup->header.sequenceId == m->header.sequenceId) {
		event = FUP_MATCH;
	} else {
		event = FUP_MISMATCH;
	}
#ifdef KSZ_1588_PTP
	/* Out of sequence Follow_Up does not satisfy receive timer. */
	if (event == FUP_MATCH && port_is_ieee8021as(p)) {
#ifdef KSZ_DBG_TIMEOUT
		struct timespec now;

		clock_gettime(CLOCK_MONOTONIC, &now);
		now.tv_sec -= fup_ts.tv_sec;
		if (now.tv_nsec < fup_ts.tv_nsec) {
			now.tv_sec--;
			now.tv_nsec += 1000000000;
		}
		now.tv_nsec -= fup_ts.tv_nsec;
		if (now.tv_sec == 0 && now.tv_nsec > fup_nsec) {
			fup_nsec = now.tv_nsec;
printf(" fup_nsec %lu\n", fup_nsec);
		}
#endif
		port_clr_tmo(p->fda.fd[FD_FUP_RX_TIMER]);
		if (p->fup_rx_timeout) {
#ifdef KSZ_DBG_TIMER
#if 1
if (portnum(p) == 5)
#endif
printf(" %s fup_rx %d\n", __func__, portnum(p));
#endif
			p->fup_rx_timeout = 0;
		}
		if (p->last_sync)
			msg_put(p->last_sync);
		p->last_sync = p->last_syncfup;
		msg_get(p->last_sync);
		if (p->last_fup)
			msg_put(p->last_fup);
		p->last_fup = m;
		msg_get(p->last_fup);
		p->sync_fup_ok = 1;
	}
#endif
	port_syfufsm(p, event, m);
}

static int gptp_test = 1;
static int gptp_test_case = 4;

static int gptp_auto_1as_9_3_rsp(struct port *p, struct ptp_message *m)
{
	if (p->delayed_pdelay_req) {
#if 0
		if (p->delayed_pdelay_req == m)
			msg_put(m);
		else
printf(" not same %s\n %p %p", __func__, p->delayed_pdelay_req, m);
		p->delayed_pdelay_req = NULL;
#endif
		return 0;
	}
	if (gptp_test_case == 4) {
		int ret = 0;

#if 1
#if 0
printf(" req: %p %04x %02x%02x%02x%02x%02x%02x%02x%02x %04x\n",
m,
m->header.sequenceId,
m->header.sourcePortIdentity.clockIdentity.id[0],
m->header.sourcePortIdentity.clockIdentity.id[1],
m->header.sourcePortIdentity.clockIdentity.id[2],
m->header.sourcePortIdentity.clockIdentity.id[3],
m->header.sourcePortIdentity.clockIdentity.id[4],
m->header.sourcePortIdentity.clockIdentity.id[5],
m->header.sourcePortIdentity.clockIdentity.id[6],
m->header.sourcePortIdentity.clockIdentity.id[7],
m->header.sourcePortIdentity.portNumber
);
#endif
		if (p->cnt_pdelay_resp) {
			msg_get(m);
			p->delayed_pdelay_req = m;
			set_tmo_us(p->fda.fd[FD_PDELAY_RESP_FUP_TIMER],
				   300000);
			ret = -1;
		}
#endif
		p->cnt_pdelay_resp++;
		if (p->cnt_pdelay_resp > p->max_pdelay_req) {
			p->cnt_pdelay_resp = 0;
		}
		return ret;
	}
	return 0;
}

static int gptp_auto_1as_9_3_rsp_fup(struct port *p, struct ptp_message *m)
{
	if (p->delayed_pdelay_resp) {
#if 0
		if (p->delayed_pdelay_resp == m)
			msg_put(m);
		else
printf(" not same %s\n %p %p", __func__, p->delayed_pdelay_resp, m);
		p->delayed_pdelay_resp = NULL;
#endif
		return 0;
	}
	if (gptp_test_case == 4) {
		int ret = 0;

#if 1
		if (p->cnt_pdelay_resp_fup) {
			msg_get(m);
			p->delayed_pdelay_resp = m;
			set_tmo_us(p->fda.fd[FD_PDELAY_RESP_FUP_TIMER],
				   100000);
			ret = -1;
		}
		p->cnt_pdelay_resp_fup++;
		if (p->cnt_pdelay_resp_fup > p->max_pdelay_req) {
			p->cnt_pdelay_resp_fup = 0;
		}
		if (!p->first_req_ts.tv_sec)
			clock_gettime(CLOCK_MONOTONIC, &p->first_req_ts);
		if (p->max_pdelay_req && !p->cnt_pdelay_resp_fup) {
			struct timespec diff;
			struct timespec now;

			clock_gettime(CLOCK_MONOTONIC, &now);
			ts_diff(&p->first_req_ts, &now, &diff);
			if (diff.tv_sec >= 10) {
printf(" sec: %ld %ld\n", diff.tv_sec, diff.tv_nsec);
				p->max_pdelay_req++;
				p->first_req_ts = now;
				p->cnt_pdelay_resp = 0;
				p->cnt_pdelay_resp_fup = 0;
				if (p->max_pdelay_req > 5) {
					p->max_pdelay_req = 0;
					p->first_req_ts.tv_sec = 0;
				}
			}
		}
		return ret;
#endif
	}
	return 0;
}

static int process_pdelay_req(struct port *p, struct ptp_message *m)
{
	struct ptp_message *rsp, *fup;
	int err;

	if (p->delayMechanism == DM_E2E) {
		pr_warning("port %hu: pdelay_req on E2E port", portnum(p));
		return 0;
	}
#ifdef KSZ_1588_PTP
	if (port_is_aed(p) && p->state == PS_PASSIVE)
		return 0;
	if (gptp_test) {
		if (gptp_auto_1as_9_3_rsp(p, m))
			return 0;
	}
#endif
	if (p->delayMechanism == DM_AUTO) {
		pr_info("port %hu: peer detected, switch to P2P", portnum(p));
		p->delayMechanism = DM_P2P;
#ifdef KSZ_1588_PTP
		set_hw_p2p(&ptpdev, 1);
#endif
		port_set_delay_tmo(p);
	}
	if (p->peer_portid_valid) {
		if (!p->no_id_check)
		if (!pid_eq(&p->peer_portid, &m->header.sourcePortIdentity)) {
			pr_err("port %hu: received pdelay_req msg with "
				"unexpected peer port id %s",
				portnum(p),
				pid2str(&m->header.sourcePortIdentity));
			p->peer_portid_valid = 0;
			port_capable(p);
		}
	} else {
		p->peer_portid_valid = 1;
		p->peer_portid = m->header.sourcePortIdentity;
		pr_debug("port %hu: peer port id set to %s", portnum(p),
			pid2str(&p->peer_portid));
	}

#ifdef KSZ_DBG_MISS
	if (((p->pdelay_req_seqid + 1) & 0xffff) != m->header.sequenceId &&
	    p->pdelay_req_seqid)
printf(" pdelay_req %d=%04x %04x\n", portnum(p),
	p->pdelay_req_seqid, m->header.sequenceId);
	p->pdelay_req_seqid = m->header.sequenceId;
#endif

	rsp = msg_allocate();
	if (!rsp)
		return -1;
	fup = msg_allocate();
	if (!fup) {
		msg_put(rsp);
		return -1;
	}

	rsp->hwts.type = p->timestamping;

	rsp->header.tsmt               = PDELAY_RESP | p->transportSpecific;
	rsp->header.ver                = PTP_VERSION;
	rsp->header.messageLength      = sizeof(struct pdelay_resp_msg);
	rsp->header.domainNumber       = m->header.domainNumber;
	rsp->header.sourcePortIdentity = p->portIdentity;
	rsp->header.sequenceId         = m->header.sequenceId;
	rsp->header.control            = CTL_OTHER;
	rsp->header.logMessageInterval = 0x7f;

#ifdef KSZ_1588_PTP
	if (clock_two_step_pdelay(p->clock))
#endif
	/*
	 * NB - There is no kernel support for one step P2P messaging,
	 * so we always send a follow up message.
	 */
	rsp->header.flagField[0] |= TWO_STEP;

	/*
	 * NB - We do not have any fraction nanoseconds for the correction
	 * fields, neither in the response or the follow up.
	 */
#ifdef KSZ_1588_PTP
	if (need_dest_port(p->clock))
		rsp->header.sourcePortIdentity.portNumber = p->receive_port;
	rsp->header.flagField[1] |= PTP_TIMESCALE;
	p->p2p_sec = p->p2p_nsec = 0;
	if (clock_one_step(p->clock)) {
		if (get_hw_version(p->clock) < 2) {
			rsp->header.reserved2 = ((m->hwts.ts.tv_sec & 3) << 30)
				| m->hwts.ts.tv_nsec;
			rsp->header.reserved2 = htonl(rsp->header.reserved2);
		}
		if (get_hw_version(p->clock) >= 2) {
			p->p2p_sec = m->hwts.ts.tv_sec;
			p->p2p_nsec = m->hwts.ts.tv_nsec;
		}
	}
	rsp->header.correction = m->header.correction;
	if (clock_two_step_pdelay(p->clock))
#endif
	ts_to_timestamp(&m->hwts.ts, &rsp->pdelay_resp.requestReceiptTimestamp);
	rsp->pdelay_resp.requestingPortIdentity = m->header.sourcePortIdentity;

	fup->hwts.type = p->timestamping;

	fup->header.tsmt               = PDELAY_RESP_FOLLOW_UP | p->transportSpecific;
	fup->header.ver                = PTP_VERSION;
	fup->header.messageLength      = sizeof(struct pdelay_resp_fup_msg);
	fup->header.domainNumber       = m->header.domainNumber;
#ifndef KSZ_1588_PTP
	fup->header.correction         = m->header.correction;
#endif
	fup->header.sourcePortIdentity = p->portIdentity;
	fup->header.sequenceId         = m->header.sequenceId;
	fup->header.control            = CTL_OTHER;
	fup->header.logMessageInterval = 0x7f;

	fup->pdelay_resp_fup.requestingPortIdentity = m->header.sourcePortIdentity;

#ifdef KSZ_1588_PTP
	if (need_dest_port(p->clock))
		fup->header.sourcePortIdentity.portNumber = p->receive_port;
	fup->header.flagField[1] |= PTP_TIMESCALE;
#endif
	err = peer_prepare_and_send(p, rsp, 1);
	if (err) {
		pr_err("port %hu: send peer delay response failed", portnum(p));
		goto out;
	}
#ifdef KSZ_1588_PTP
	if (!clock_two_step_pdelay(p->clock))
		goto out;
#endif
	if (msg_sots_missing(rsp)) {
#ifdef KSZ_1588_PTP
		msg_get(rsp);
		if (p->pdelay_resp)
			msg_put(p->pdelay_resp);
		p->pdelay_resp = rsp;
		msg_get(fup);
		if (p->pdelay_resp_fup)
			msg_put(p->pdelay_resp_fup);
		p->pdelay_resp_fup = fup;
#else
		pr_err("missing timestamp on transmitted peer delay response");
#endif
		goto out;
	}

	ts_to_timestamp(&rsp->hwts.ts,
			&fup->pdelay_resp_fup.responseOriginTimestamp);

	err = peer_prepare_and_send(p, fup, 0);
	if (err)
		pr_err("port %hu: send pdelay_resp_fup failed", portnum(p));

out:
	msg_put(rsp);
	msg_put(fup);
	return err;
}

static void port_peer_delay(struct port *p)
{
	tmv_t c1, c2, t1, t2, t3, t3c, t4;
	struct ptp_message *req = p->peer_delay_req;
	struct ptp_message *rsp = p->peer_delay_resp;
	struct ptp_message *fup = p->peer_delay_fup;
	tmv_t c3;
#ifdef KSZ_1588_PTP
	struct PortIdentity *portIdentity = &p->portIdentity;
#endif

	/* Check for response, validate port and sequence number. */

	if (!rsp)
		return;

#ifdef KSZ_1588_PTP
	if (need_dest_port(p->clock)) {
		struct PortIdentity pid;

		pid = p->portIdentity;
		pid.portNumber = p->receive_port;
		portIdentity = &pid;
	}
	if (!pid_eq(&rsp->pdelay_resp.requestingPortIdentity, portIdentity))
#else
	if (!pid_eq(&rsp->pdelay_resp.requestingPortIdentity, &p->portIdentity))
#endif
		return;

	if (rsp->header.sequenceId != ntohs(req->header.sequenceId))
		return;

	t1 = timespec_to_tmv(req->hwts.ts);
	t4 = timespec_to_tmv(rsp->hwts.ts);
	c1 = correction_to_tmv(rsp->header.correction + p->asymmetry);
#if 0
printf("%lld %lld %lld %lld = %lld ", t1, t4, t4 - t1, c1, t4 - t1 - c1);
#endif

	/* Process one-step response immediately. */
	if (one_step(rsp)) {
		t2 = tmv_zero();
		t3 = tmv_zero();
		c2 = tmv_zero();
		c3 = t1;
		goto calc;
	}

	/* Check for follow up, validate port and sequence number. */

	if (!fup)
		return;

	if (!pid_eq(&fup->pdelay_resp_fup.requestingPortIdentity, &p->portIdentity))
		return;

	if (fup->header.sequenceId != rsp->header.sequenceId)
		return;

	if (!source_pid_eq(fup, rsp))
		return;

	/* Process follow up response. */
	t2 = timestamp_to_tmv(rsp->ts.pdu);
	t3 = timestamp_to_tmv(fup->ts.pdu);
	c2 = correction_to_tmv(fup->header.correction);
	c3 = tmv_zero();
calc:
	t3c = tmv_add(t3, tmv_add(c1, c2));
	c3 = tmv_add(t3c, c3);

	if (p->follow_up_info)
		port_nrate_calculate(p, c3, t4);

	tsproc_set_clock_rate_ratio(p->tsproc, p->nrate.ratio *
				    clock_rate_ratio(p->clock));
	tsproc_up_ts(p->tsproc, t1, t2);
	tsproc_down_ts(p->tsproc, t3c, t4);
	if (tsproc_update_delay(p->tsproc, &p->peer_delay))
		return;

	p->peerMeanPathDelay = tmv_to_TimeInterval(p->peer_delay);
#if 0
printf(" p: %d=%lld\n", portnum(p), p->peer_delay);
#endif
#ifdef KSZ_1588_PTP
	if (p->peer_delay < 0)
		p->peer_delay = p->neighborPropDelay;
	if (!p->peer_delay)
		p->peer_delay = 1;
#endif

	if (p->state == PS_UNCALIBRATED || p->state == PS_SLAVE) {
		clock_peer_delay(p->clock, p->peer_delay, t1, t2,
				 p->nrate.ratio);
	}
#ifdef KSZ_1588_PTP
	c3 = p->peer_delay - p->neighborPropDelay;
	if (!p->neighborPropDelay || c3 >= 100 || c3 <= -100) {
		struct config *cfg = clock_config(p->clock);

		p->neighborPropDelay = (int) p->peer_delay;
		config_set_section_int(cfg, p->name, "neighborPropDelay",
				       p->neighborPropDelay);
		cfg->changed = 1;
	}
	port_set_peer_delay(p);
	msg_put(p->peer_delay_resp);
	p->peer_delay_resp = NULL;
	if (p->peer_delay_fup) {
		msg_put(p->peer_delay_fup);
		p->peer_delay_fup = NULL;
	}
#endif

	msg_put(p->peer_delay_req);
#ifdef KSZ_DBG_MISS
	if (p->req_seqid)
printf(" last pdelay_req: %04x %04x\n", ntohs(p->req_seqid),
ntohs(p->peer_delay_req->header.sequenceId));
	p->req_seqid = 0;
#endif
	p->peer_delay_req = NULL;
}

static int process_pdelay_resp(struct port *p, struct ptp_message *m)
{
#ifdef KSZ_1588_PTP
	if (p->tx_err)
		p->tx_err = 0;
	p->multiple_pdr = 0;
	if (0 == memcmp(&p->portIdentity, &m->header.sourcePortIdentity,
		        sizeof(struct ClockIdentity))) {
		p->multiple_pdr = 1;
		return 0;
	}

#if 0
	/* Typical response time is 1.5 ms. */
	do {
		struct timespec diff;

		clock_gettime(CLOCK_MONOTONIC, &p->pdelay_resp_ts);
		ts_diff(&p->pdelay_req_ts, &p->pdelay_resp_ts, &diff);
printf(" pdelay_resp \t\t%d=%ld:%6lu\n", portnum(p), diff.tv_sec,
	diff.tv_nsec / 1000);
	} while (0);
#endif
#if 0
printf(" rsp: %04x %x %x\n", m->header.sequenceId, m->header.tsmt, m->header.ver);
#endif
#ifdef KSZ_DBG_MISS
	p->pdelay_resp_missed = 0;
	if (((p->pdelay_resp_seqid + 1) & 0xffff) != m->header.sequenceId &&
	    p->pdelay_resp_seqid) {
printf(" pdelay_resp %d=%04x %04x\n", portnum(p),
	p->pdelay_resp_seqid, m->header.sequenceId);
		p->pdelay_resp_missed = 1;
	}
	p->pdelay_resp_seqid = m->header.sequenceId;
#endif
#endif
	if (p->peer_delay_resp) {
		p->multiple_pdr = 1;
		if (!source_pid_eq(p->peer_delay_resp, m)) {
			pr_err("port %hu: multiple peer responses", portnum(p));
			if (!p->multiple_pdr_detected) {
				p->multiple_pdr_detected = 1;
				p->multiple_seq_pdr_count++;
			}
			if (p->multiple_seq_pdr_count >= 3) {
				p->last_fault_type = FT_BAD_PEER_NETWORK;
				return -1;
			}
		}
	}
	if (!p->peer_delay_req) {
#ifdef KSZ_1588_PTP
		/* peer_delay_req is cleared by self. */
		if (p->clear_pdelay_req) {
			p->clear_pdelay_req = 0;
			return 0;
		}
#endif
		pr_err("port %hu: rogue peer delay response", portnum(p));
		return -1;
	}
	if (p->peer_portid_valid) {
		if (!p->no_id_check)
		if (!pid_eq(&p->peer_portid, &m->header.sourcePortIdentity)) {
			pr_err("port %hu: received pdelay_resp msg with "
				"unexpected peer port id %s",
				portnum(p),
				pid2str(&m->header.sourcePortIdentity));
			p->peer_portid_valid = 0;
			port_capable(p);
		}
	} else {
		p->peer_portid_valid = 1;
		p->peer_portid = m->header.sourcePortIdentity;
		pr_debug("port %hu: peer port id set to %s", portnum(p),
			pid2str(&p->peer_portid));
	}

	if (p->peer_delay_resp) {
		msg_put(p->peer_delay_resp);
	}
	msg_get(m);
	p->peer_delay_resp = m;
#ifdef KSZ_1588_PTP
	p->clear_pdelay_req = 0;
	if (msg_sots_missing(p->peer_delay_req))
		return 0;
#endif
	port_peer_delay(p);
	return 0;
}

static void process_pdelay_resp_fup(struct port *p, struct ptp_message *m)
{
#ifdef KSZ_1588_PTP

#if 0
	/* Typical response time is 1.8 ms. */
	do {
		struct timespec diff;

		clock_gettime(CLOCK_MONOTONIC, &p->pdelay_resp_fup_ts);
		ts_diff(&p->pdelay_req_ts, &p->pdelay_resp_fup_ts, &diff);
printf(" pdelay_resp_fup \t%d=%ld:%6lu\n", portnum(p), diff.tv_sec,
	diff.tv_nsec / 1000);
	} while (0);
#endif
#ifdef KSZ_DBG_MISS
	if (((p->pdelay_resp_fup_seqid + 1) & 0xffff) != m->header.sequenceId &&
	    p->pdelay_resp_fup_seqid)
printf(" pdelay_resp_fup %d=%04x %04x\n", portnum(p),
	p->pdelay_resp_fup_seqid, m->header.sequenceId);
	if (p->pdelay_resp_missed)
printf(" missed %04x %04x\n", p->pdelay_resp_fup_seqid, m->header.sequenceId);
	p->pdelay_resp_fup_seqid = m->header.sequenceId;
	if (p->pdelay_resp_fup_seqid != p->pdelay_resp_seqid)
printf(" !same %04x %04x\n", p->pdelay_resp_seqid, p->pdelay_resp_fup_seqid);
#endif
	if (!p->no_id_check)
	if (0 == memcmp(&p->portIdentity, &m->header.sourcePortIdentity,
		        sizeof(struct ClockIdentity))) {
		return;
	}
#endif
	if (!p->peer_delay_req)
		return;

	if (p->peer_delay_fup)
		msg_put(p->peer_delay_fup);

	msg_get(m);
	p->peer_delay_fup = m;
#ifdef KSZ_1588_PTP
	if (msg_sots_missing(p->peer_delay_req))
		return;
#endif
	port_peer_delay(p);
}

static void process_sync(struct port *p, struct ptp_message *m)
{
	enum syfu_event event;
	struct PortIdentity master;
#ifdef KSZ_DBG_MISS
	if (((p->sync_seqid + 1) & 0xffff) != m->header.sequenceId &&
	    p->sync_seqid)
printf(" sync %d=%04x %04x\n", portnum(p),
	p->sync_seqid, m->header.sequenceId);
	p->sync_seqid = m->header.sequenceId;
#endif
#ifdef KSZ_1588_PTP
	p->sync_fup_ok = 0;
	if (p->master_only && p->report_sync) {
		exception_log(p->clock, "Sync received at port %hu",
			      portnum(p));
		p->report_sync = 0;
	}
#endif
	switch (p->state) {
	case PS_INITIALIZING:
	case PS_FAULTY:
	case PS_DISABLED:
	case PS_LISTENING:
	case PS_PRE_MASTER:
	case PS_MASTER:
	case PS_GRAND_MASTER:
	case PS_PASSIVE:
#ifdef KSZ_1588_PTP
		if (p->rx_sync_timeout &&
		    (p->state == PS_MASTER || p->state == PS_GRAND_MASTER)) {
			p->rx_sync_timeout = 0;
#if 1
			port_tx_announce(p);
#endif
#ifdef KSZ_DBG_MISS
			p->prev_announce->header.sequenceId = p->ann_seqid;
			p->ann_seqid--;
#endif
			if (process_announce(p, p->prev_announce)) {
				clock_update_state(p->clock);
				break;
			}
		}
#endif
		return;
	case PS_UNCALIBRATED:
	case PS_SLAVE:
		break;
	}
	master = clock_parent_identity(p->clock);
#ifdef KSZ_1588_PTP
	if (!skip_sync_check(p->clock) && !p->no_announce)
#endif
	if (memcmp(&master, &m->header.sourcePortIdentity, sizeof(master))) {
		return;
	}

	if (m->header.logMessageInterval != p->log_sync_interval) {
#ifdef KSZ_1588_PTP
		struct port *q;
#endif

		p->log_sync_interval = m->header.logMessageInterval;
		clock_sync_interval(p->clock, p->log_sync_interval);
#ifdef KSZ_1588_PTP
		p->sync_interval = calculate_interval(1, p->log_sync_interval);
		p->actual_sync_interval = p->sync_interval;
		for (q = clock_first_port(p->clock); q;
		     q = LIST_NEXT(q, list)) {
			if (q == p || portnum(q) == 0)
				continue;
			if (q->logSyncInterval != p->log_sync_interval) {
				int diff = q->logSyncInterval -
					p->log_sync_interval;

				if (diff > 0)
					q->sync_max = (1 << diff) - 1;
				else
					q->sync_max = 0;
				q->sync_cnt = q->sync_max;
			}

			/* Not slower interval. */
			if (!q->sync_max) {
				q->sync_interval = p->sync_interval;
				q->actual_sync_interval = q->sync_interval;
				q->syncTxContTimeout = q->sync_interval +
					100000;
			}
		}
#ifdef KSZ_DBG_TIMEOUT
printf(" first sync: %d\n", p->sync_interval);
#endif
#endif
	}
#ifdef KSZ_1588_PTP
	determine_sync_interval(p);
	if (m->header.logMessageInterval != p->logSyncInterval &&
	    p->report_interval) {
		p->report_interval--;
		if (!p->report_interval) {
			exception_log(p->clock,
				      "Sync interval unchanged at port %hu",
				      portnum(p));
			p->seqnumSync = get_cnt_from_log(p->log_sync_interval,
							 2);
		}
	} else if (p->report_interval)
		p->report_interval = 0;
#endif

	m->header.correction += p->asymmetry;

#ifdef KSZ_1588_PTP
	p->rx_sec = m->hwts.ts.tv_sec;
	if (need_dest_port(p->clock)) {
		if (get_hw_version(p->clock) < 2)
			set_master_port(p->clock, m->header.reserved1);
		if (get_hw_version(p->clock) >= 2)
			set_master_port(p->clock, p->receive_port);
	}
#endif
	if (one_step(m)) {
		port_synchronize(p, m->hwts.ts, m->ts.pdu,
				 m->header.correction, 0);
		flush_last_sync(p);
		return;
	}

	if (p->syfu == SF_HAVE_FUP &&
	    fup_sync_ok(p->last_syncfup, m) &&
	    p->last_syncfup->header.sequenceId == m->header.sequenceId) {
		event = SYNC_MATCH;
	} else {
		event = SYNC_MISMATCH;
#ifdef KSZ_1588_PTP
		p->sync_fup_ok = 1;
		if (p->followUpReceiptTimeout && !p->fup_rx_timeout)
			port_set_fup_rx_tmo(p);
#endif
	}
	port_syfufsm(p, event, m);
}

#ifdef KSZ_1588_PTP
static void process_interval_info(struct port *p, struct interval_info_tlv *ii)
{
	struct port *q;
	struct port *s;
	int logSyncInterval;

	if (port_is_aed(p) && p->report_signaling) {
		exception_log(p->clock, "Signaling received at port %hu",
			      portnum(p));
		p->report_signaling = 0;
	}
	if (!port_is_aed_master(p) ||
	    p->logSyncInterval == ii->timeSyncInterval)
		return;
	if (ii->timeSyncInterval == 126 &&
	    ii->linkDelayInterval == 126 &&
	    ii->announceInterval == 126)
printf(" ? %d=126\n", portnum(p));
printf(" timeSyncInterval: %d=%d %d\n", portnum(p),
	p->logSyncInterval, ii->timeSyncInterval);
	if (ii->timeSyncInterval < -6 || ii->timeSyncInterval > 2)
		return;
	p->logSyncInterval = ii->timeSyncInterval;
	logSyncInterval = p->logSyncInterval;
	q = p;
	s = get_slave_port(p->clock);
	if (!s)
		return;
	for (p = clock_first_port(q->clock); p; p = LIST_NEXT(p, list)) {
		if (p == q || p == s)
			continue;
		if (logSyncInterval > p->logSyncInterval)
			logSyncInterval = p->logSyncInterval;
	}
	if (s->logSyncInterval != logSyncInterval) {
printf(" change sync: %d=%d\n", portnum(s), logSyncInterval);
		s->report_interval = 3;
		s->logSyncInterval = logSyncInterval;
		port_tx_signaling(s);
	}
}

#if 0
static void process_wake_info(struct port *p, struct wake_info_tlv *wake)
{
	struct clock *c = p->clock;

	if (!port_is_aed(p))
		return;
	if (p->log_exception)
		exception_log(c, "%s sleeping", wake->event ? "Stop" : "Start");
	for (p = clock_first_port(c); p; p = LIST_NEXT(p, list)) {
		if (wake->event) {
			if (p->state != PS_PASSIVE)
				continue;
			port_dispatch(p, EV_POWERUP, 0);
			if (port_is_aed_master(p))
				port_dispatch(p, EV_RS_GRAND_MASTER, 0);
			else
				port_dispatch(p, EV_RS_SLAVE, 0);
		} else {
			port_dispatch(p, EV_RS_PASSIVE, 0);
		}
	}
}
#endif

static void process_signaling(struct port *p, struct ptp_message *m)
{
	void *tlv;
	struct PortIdentity *tpid;
	struct ClockIdentity *tcid, wildcard = {
		{0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff}
	};

	tpid = &m->signaling.targetPortIdentity;
	tcid = &tpid->clockIdentity;
	if (memcmp(tcid, &wildcard, sizeof(struct ClockIdentity)) &&
	    memcmp(tcid, &p->portIdentity.clockIdentity, sizeof(struct ClockIdentity))) {
		return;
	}
	if (tpid->portNumber != 0xffff &&
	    tpid->portNumber != p->portIdentity.portNumber)
		return;

	tlv = interval_info_extract(m);
	if (tlv)
		process_interval_info(p, tlv);
#if 0
	tlv = wake_info_extract(m);
	if (tlv)
		process_wake_info(p, tlv);
#endif
}
#endif

#if 1
#include "tc.c"
#endif

void port_tc_flush(struct port *p, void *param)
{
	tc_flush(p);
}

/* public methods */

void port_close(struct port *p)
{
	if (port_is_enabled(p)) {
		port_disable(p);
	}
	transport_destroy(p->trp);
	tsproc_destroy(p->tsproc);
	if (p->fault_fd >= 0)
		close(p->fault_fd);
	free(p);
}

struct foreign_clock *port_compute_best(struct port *p)
{
	struct foreign_clock *fc;
	struct ptp_message *tmp;
	int threshold = FOREIGN_MASTER_THRESHOLD;

#ifdef KSZ_1588_PTP
	if (port_is_ieee8021as(p))
		threshold = 1;
#endif
	p->best = NULL;

	LIST_FOREACH(fc, &p->foreign_masters, list) {
		tmp = TAILQ_FIRST(&fc->messages);
		if (!tmp)
			continue;

		announce_to_dataset(tmp, p, &fc->dataset);

		fc_prune(fc);

#ifdef KSZ_1588_PTP
		if (fc->bad_master)
			continue;
#endif
		if (fc->n_messages < threshold)
			continue;

		if (!p->best)
			p->best = fc;
		else if (dscmp(&fc->dataset, &p->best->dataset) > 0)
			p->best = fc;
		else
			fc_clear(fc);
	}

	return p->best;
}

static void port_e2e_transition(struct port *p, enum port_state next)
{
	port_clr_tmo(p->fda.fd[FD_ANNOUNCE_TIMER]);
	port_clr_tmo(p->fda.fd[FD_SYNC_RX_TIMER]);
	port_clr_tmo(p->fda.fd[FD_DELAY_TIMER]);
	port_clr_tmo(p->fda.fd[FD_QUALIFICATION_TIMER]);
	port_clr_tmo(p->fda.fd[FD_MANNO_TIMER]);
	port_clr_tmo(p->fda.fd[FD_SYNC_TX_TIMER]);
#ifdef KSZ_1588_PTP
	p->ann_rx_timeout = 0;
	p->ann_tx_timeout = 0;
	p->sync_rx_timeout = 0;
	p->sync_tx_timeout = 0;
#endif

	switch (next) {
	case PS_INITIALIZING:
		break;
	case PS_FAULTY:
	case PS_DISABLED:
#ifdef KSZ_1588_PTP
		if (p == get_slave_port(p->clock))
			set_slave_port(p->clock, NULL);
#endif
		port_disable(p);
		break;
	case PS_LISTENING:
#ifdef KSZ_1588_PTP
		if (p == get_slave_port(p->clock))
			set_slave_port(p->clock, NULL);
		if (!is_peer_port(p->clock, p) ||
		    clock_slave_only(p->clock) ||
		    PS_MASTER == p->state ||
		    PS_GRAND_MASTER == p->state)
			break;
#endif
		port_set_announce_tmo(p);
		break;
	case PS_PRE_MASTER:
#ifdef KSZ_1588_PTP
		if (!is_host_port(p->clock, p))
			break;
#endif
		port_set_qualification_tmo(p);
		break;
	case PS_MASTER:
	case PS_GRAND_MASTER:
#ifdef KSZ_1588_PTP
		free_foreign_masters(p);
		if (p == get_slave_port(p->clock))
			set_slave_port(p->clock, NULL);

		/* Only host port handles master clock operation. */
		if (!is_host_port(p->clock, p))
			break;
#endif
		set_tmo_log(p->fda.fd[FD_MANNO_TIMER], 1, -10); /*~1ms*/
#ifdef KSZ_1588_PTP
		if (!p->ann_tx_timeout) {
#ifdef KSZ_DBG_TIMER
#if 0 
if (portnum(p) == 5)
#endif
printf(" %s ann_tx %d\n", __func__, portnum(p));
#endif
			p->ann_tx_timeout = 1;
		}
#endif
		port_set_sync_tx_tmo(p);
		break;
	case PS_PASSIVE:

#ifdef KSZ_1588_PTP
		/* Host port does not handle Announce. */
		if (!is_peer_port(p->clock, p))
			break;
#endif
		port_set_announce_tmo(p);
		break;
	case PS_UNCALIBRATED:
#ifdef KSZ_1588_PTP
		if (is_peer_port(p->clock, p))
			set_slave_port(p->clock, p);
		p->tx_ann = 0;
#endif
		flush_last_sync(p);
		flush_delay_req(p);
		/* fall through */
	case PS_SLAVE:

#ifdef KSZ_1588_PTP
		/* Host port does not handle Announce. */
		if (is_peer_port(p->clock, p) &&
		    !clock_slave_only(p->clock))
#endif
		port_set_announce_tmo(p);

#ifdef KSZ_1588_PTP
		/* Host port does not handle delay. */
		if (!is_peer_port(p->clock, p))
			break;
#endif
		port_set_delay_tmo(p);
		break;
	};
}

static void port_p2p_transition(struct port *p, enum port_state next)
{
	port_clr_tmo(p->fda.fd[FD_ANNOUNCE_TIMER]);
	port_clr_tmo(p->fda.fd[FD_SYNC_RX_TIMER]);
	/* Leave FD_DELAY_TIMER running. */
	port_clr_tmo(p->fda.fd[FD_QUALIFICATION_TIMER]);
	port_clr_tmo(p->fda.fd[FD_MANNO_TIMER]);
	port_clr_tmo(p->fda.fd[FD_SYNC_TX_TIMER]);
#ifdef KSZ_1588_PTP
	port_clr_tmo(p->fda.fd[FD_FUP_RX_TIMER]);
	port_clr_tmo(p->fda.fd[FD_SYNC_CONT_TIMER]);
	p->ann_rx_timeout = 0;
	p->ann_tx_timeout = 0;
	p->sync_rx_timeout = 0;
	p->sync_tx_timeout = 0;
	p->fup_rx_timeout = 0;
	p->fup_tx_timeout = 0;
#endif

	switch (next) {
	case PS_INITIALIZING:
		break;
	case PS_FAULTY:
	case PS_DISABLED:
#ifdef KSZ_1588_PTP
		if (p == get_slave_port(p->clock))
			set_slave_port(p->clock, NULL);
#endif
		port_disable(p);
		break;
	case PS_LISTENING:
#ifdef KSZ_1588_PTP
		if (p == get_slave_port(p->clock))
			set_slave_port(p->clock, NULL);

		/* Host port does not handle Announce. */
		if (is_peer_port(p->clock, p) &&
		    !clock_slave_only(p->clock) &&
		    !p->no_announce &&
		    PS_MASTER != p->state &&
		    PS_GRAND_MASTER != p->state)
#endif
		port_set_announce_tmo(p);

#ifdef KSZ_1588_PTP
		/* Host port does not handle delay. */
		if (!is_peer_port(p->clock, p))
			break;
#endif
		port_set_delay_tmo(p);
		break;
	case PS_PRE_MASTER:

#ifdef KSZ_1588_PTP
		/* Only host port handles master clock operation. */
		if (!is_host_port(p->clock, p))
			break;
#endif
		port_set_qualification_tmo(p);
		break;
	case PS_MASTER:
	case PS_GRAND_MASTER:
#ifdef KSZ_1588_PTP
		/* Check sync interval again when becoming slave. */
		p->log_sync_interval = 8;
		if (port_is_ieee8021as(p) && p == get_slave_port(p->clock)) {
			struct timespec now;

#if 0
			clock_gettime(CLOCK_MONOTONIC, &now);
			now.tv_sec -= sync_ts.tv_sec;
			if (now.tv_nsec < sync_ts.tv_nsec) {
				now.tv_sec--;
				now.tv_nsec += 1000000000;
			}
			now.tv_nsec -= sync_ts.tv_nsec;
#endif
			clock_gettime(CLOCK_MONOTONIC, &now);
			for_all_ports(p,
				      port_tx_last_sync, &now);
			clock_set_follow_up_info(p->clock);
			for_all_ports(p,
				      port_clear_sync_fup, NULL);
			for_other_ports(p,
					port_restart_tx, NULL);
		}
		if (p == get_slave_port(p->clock))
			set_slave_port(p->clock, NULL);

		/* Only host port handles master clock operation. */
		if (!is_host_port(p->clock, p))
			break;

		/* Only forward Sync/Follow_Up/Announce from slave port. */
		if (port_is_ieee8021as(p) && get_slave_port(p->clock))
			break;
		if (p->no_announce) {
			if (p->master_only)
				port_set_sync_tx_tmo(p);
			break;
		}
#endif
		set_tmo_log(p->fda.fd[FD_MANNO_TIMER], 1, -10); /*~1ms*/
#ifdef KSZ_1588_PTP
		if (!p->ann_tx_timeout) {
#ifdef KSZ_DBG_TIMER
#if 0 
if (portnum(p) == 5)
#endif
printf(" %s ann_tx %d\n", __func__, portnum(p));
#endif
			p->ann_tx_timeout = 1;
		}
		if (!port_is_ieee8021as(p) || clock_gm_capable(p->clock))
#endif
		port_set_sync_tx_tmo(p);
		break;
	case PS_PASSIVE:

#ifdef KSZ_1588_PTP
		/* Host port does not handle Announce. */
		if (!is_peer_port(p->clock, p))
			break;
		if (port_is_aed(p))
			port_clr_tmo(p->fda.fd[FD_DELAY_TIMER]);
		if (!p->no_announce)
#endif
		port_set_announce_tmo(p);
		break;
	case PS_UNCALIBRATED:
#ifdef KSZ_1588_PTP
		if (is_peer_port(p->clock, p))
			set_slave_port(p->clock, p);
		if (port_is_aed(p) && p->log_sync_interval > p->logSyncInterval)
			port_tx_signaling(p);
		p->tx_ann = 0;
#endif
		flush_last_sync(p);
		flush_peer_delay(p);
		/* fall through */
	case PS_SLAVE:

#ifdef KSZ_1588_PTP
		/* Host port does not handle Announce and Sync. */
		if (!is_peer_port(p->clock, p) || clock_slave_only(p->clock))
			break;
		if (!p->no_announce)
#endif
		port_set_announce_tmo(p);
		break;
	};
}

void port_dispatch(struct port *p, enum fsm_event event, int mdiff)
{
	enum port_state next;
	enum port_state old = p->state;

#if 0
if (event)
printf("%s %d %d\n", __func__, portnum(p), event);
#endif
	if (clock_slave_only(p->clock)) {
		if (event == EV_RS_MASTER || event == EV_RS_GRAND_MASTER) {
			port_slave_priority_warning(p);
		}
	}
	next = p->state_machine(p->state, event, mdiff);
#ifdef KSZ_1588_PTP
	if (!clock_slave_only(p->clock)) {
		if (transparent_clock(p->clock) &&
		    (PS_UNCALIBRATED != p->state && PS_SLAVE != p->state) &&
		    !clock_master_lost(p->clock)) {
			switch (next) {
			case PS_MASTER:
			case PS_GRAND_MASTER:
			case PS_PASSIVE:
#if 0
printf(" change to listen %d\n", portnum(p));
#endif
				next = PS_LISTENING;

				if (next != p->state)
					break;

				/* Will not go through transition. */
				port_clr_tmo(p->fda.fd[FD_ANNOUNCE_TIMER]);
				if (p->ann_rx_timeout) {
#ifdef KSZ_DBG_TIMER
#if 0 
if (portnum(p) == 5)
#endif
printf(" %s ann_rx %d\n", __func__, portnum(p));
#endif
					p->ann_rx_timeout = 0;
				}
				break;
			default:
				break;
			}
		}
	}
#endif

	if (PS_FAULTY == next) {
		struct fault_interval i;
		fault_interval(p, last_fault_type(p), &i);
		if (clear_fault_asap(&i)) {
			pr_notice("port %hu: clearing fault immediately", portnum(p));
			next = p->state_machine(next, EV_FAULT_CLEARED, 0);
		}
	}
	if (PS_INITIALIZING == next) {
		/*
		 * This is a special case. Since we initialize the
		 * port immediately, we can skip right to listening
		 * state if all goes well.
		 */
		if (port_is_enabled(p)) {
			port_disable(p);
		}
		if (port_initialize(p)) {
			event = EV_FAULT_DETECTED;
		} else {
			event = EV_INIT_COMPLETE;
		}
		next = p->state_machine(next, event, 0);
	}

	if (next == p->state)
		return;

	port_show_transition(p, next, event);

	if (p->delayMechanism == DM_P2P) {
		port_p2p_transition(p, next);
	} else {
		port_e2e_transition(p, next);
	}

#ifdef KSZ_1588_PTP
	if (p->state != PS_INITIALIZING)
		p->report_link = 1;
	if (event == EV_SYNCHRONIZATION_FAULT && p->best) {
		if (!p->best->bad_master) {
			p->best->good_cnt = 0;
			p->best->bad_cnt++;
			if (p->best->bad_cnt > 5) {
printf(" too many faults\n");
				p->best->bad_master = 1;
				set_tmo_us(p->fda.fd[FD_ANNOUNCE_TIMER], 10000);
			}
		}
	}
	if (boundary_clock(p->clock))
		;
	else if (!is_host_port(p->clock, p))
		;
	else if (next == PS_MASTER || next == PS_GRAND_MASTER)
		set_hw_master(&ptpdev, 1);
	else if (p->state == PS_MASTER || p->state == PS_GRAND_MASTER)
		set_hw_master(&ptpdev, 0);
	else if (need_stop_forwarding(p->clock)) {
		if (p->state == PS_SLAVE)
			set_hw_as(&ptpdev, 1);
		else if (next == PS_SLAVE)
			set_hw_as(&ptpdev, 0);
	}
	p->new_state = 1;
	if (port_is_aed(p)) {
		if (next == PS_LISTENING) {
			if (p->operLogPdelayReqInterval !=
			    p->initialLogPdelayReqInterval &&
			    p->operLogPdelayReqInterval !=
			    p->logMinPdelayReqInterval) {
				p->seqnumPdelayReq = get_cnt_from_log(
					p->logMinPdelayReqInterval,
					get_waitPdelayReqInterval(p->clock));
			}
		} else if (next == PS_SLAVE) {
			if (!boundary_clock(p->clock) &&
			    p->operLogSyncInterval != p->initialLogSyncInterval)
				p->seqnumSync = get_cnt_from_log(
					p->log_sync_interval,
					get_waitSyncInterval(p->clock));
		} else if (next == PS_UNCALIBRATED) {
			tmv_t t = tmv_zero();

			if (p->neighborPropDelay) {
				p->peer_delay = p->neighborPropDelay;
				clock_peer_delay(p->clock, p->peer_delay, t, t,
						 p->nrate.ratio);
			}
			set_tmo_us(p->fda.fd[FD_SYNC_RX_TIMER],
				   1000000 *
				   get_initialSyncReceiptTimeout(p->clock));
		}
	}
#endif
	p->state = next;

#ifdef KSZ_1588_PTP
	if (p->state == PS_UNCALIBRATED) {
		if (p->last_announce) {
			for_other_ports(p,
					port_stop_tx, NULL);
			tc_forward(p, p->last_announce);
			msg_put(p->last_announce);
			p->last_announce = NULL;
		}
	}

	/* Pass event to host port. */
	if (transparent_clock(p->clock) && !port_dispatched(p->clock) &&
	    p != p->host_port) {
		clock_port_dispatch(p->clock, p);
		switch (next) {
		case PS_FAULTY:
			update_dev_cnt(p->clock, -1);
			if (0 == get_dev_cnt(p->clock))
				port_dispatch(p->host_port,
					      EV_FAULT_DETECTED, 0);
			break;
		case PS_LISTENING:

			/* Not being slave anymore. */
			if (PS_UNCALIBRATED == old || PS_SLAVE == old) {
				port_dispatch(p->host_port, event, 0);
			} else if (PS_FAULTY == old || PS_INITIALIZING == old) {
				update_dev_cnt(p->clock, 1);
				if (0 != get_dev_cnt(p->clock))
					port_dispatch(p->host_port,
						      EV_FAULT_CLEARED, 0);
			}
			break;
		case PS_MASTER:
		case PS_GRAND_MASTER:
			port_dispatch(p->host_port, event, 0);
			clock_set_port_state(p->clock, event);
			break;
		case PS_UNCALIBRATED:
		case PS_SLAVE:
			port_dispatch(p->host_port, event, 0);
			clock_set_port_state(p->clock,
					     EV_INIT_COMPLETE);
			break;
		default:
			break;
		}
		clock_port_dispatch(p->clock, NULL);
	}
#endif
	port_notify_event(p, NOTIFY_PORT_STATE);

	if (p->jbod && next == PS_UNCALIBRATED) {
		if (clock_switch_phc(p->clock, p->phc_index)) {
			p->last_fault_type = FT_SWITCH_PHC;
			port_dispatch(p, EV_FAULT_DETECTED, 0);
			return;
		}
		clock_sync_interval(p->clock, p->log_sync_interval);
	}
}

#ifdef KSZ_1588_PTP
static int matched_ptp_header(struct ptp_header *src, struct ptp_header *dst)
{
	if (!pid_eq(&src->sourcePortIdentity, &dst->sourcePortIdentity))
		return 0;
	if (src->sequenceId != dst->sequenceId)
		return 0;
	return 1;
}

static int process_delayed_sync(struct port *p, struct ptp_message *msg)
{
	struct ptp_message *sync = p->sync;
	struct ptp_message *fup = p->follow_up;
	struct ptp_header *hdr;
	int pdulen;
	int err = 0;
	struct port *q = p;

	if (!fup)
		return 0;

	hdr = &sync->header;
	if (!matched_ptp_header(&msg->header, hdr))
		return 0;

	/*
	 * Send the follow up message right away.
	 */
	pdulen = sizeof(struct follow_up_msg);
	fup->hwts.type = p->timestamping;

	if (p->follow_up_info)
		pdulen += follow_up_info_append(p, fup);

	fup->header.tsmt               = FOLLOW_UP | p->transportSpecific;
	fup->header.ver                = PTP_VERSION;
	fup->header.messageLength      = pdulen;
	fup->header.domainNumber       = clock_domain_number(p->clock);
	fup->header.sourcePortIdentity = p->portIdentity;
	fup->header.sequenceId         = p->seqnum.sync - 1;
	fup->header.control            = CTL_FOLLOW_UP;
	fup->header.logMessageInterval = p->logSyncInterval;

	ts_to_timestamp(&msg->hwts.ts, &fup->follow_up.preciseOriginTimestamp);
	if (port_is_ieee8021as(p) && p->last_fup) {
		tmv_t egress, ingress = timespec_to_tmv(p->last_sync->hwts.ts);
		tmv_t residence;
		double rr;
		Integer64 c1, c2;

		egress = timespec_to_tmv(msg->hwts.ts);
		residence = tmv_sub(egress, ingress);
		rr = clock_rate_ratio(p->clock);
		if (rr != 1.0) {
			residence = dbl_tmv(tmv_dbl(residence) * rr);
		}
		fup->header.correction = p->last_fup->header.correction;
		c1 = fup->header.correction;
		c2 = c1 + tmv_to_TimeInterval(residence);
		c2 += tmv_to_TimeInterval(p->peer_delay);
		c2 += p->asymmetry;
		fup->header.correction = c2;
		ts_to_ts(&p->last_fup->follow_up.preciseOriginTimestamp,
			 &fup->follow_up.preciseOriginTimestamp);
#if 0
		fup->follow_up.preciseOriginTimestamp.seconds_lsb =
			ntohl(p->last_fup->follow_up.preciseOriginTimestamp.
			seconds_lsb);
		fup->follow_up.preciseOriginTimestamp.seconds_msb =
			ntohs(p->last_fup->follow_up.preciseOriginTimestamp.
			seconds_msb);
		fup->follow_up.preciseOriginTimestamp.nanoseconds =
			ntohl(p->last_fup->follow_up.preciseOriginTimestamp.
			nanoseconds);
#endif
	}

	fup->header.flagField[1] |= PTP_TIMESCALE;
	p->dest_port = msg->header.reserved1;

	/* Follow_Up needs to be sent by individual port. */
	if (!is_peer_port(p->clock, p)) {
		q = get_port(p->clock, p->dest_port);
		if (!q)
			return err;
	}
	err = port_prepare_and_send(q, fup, 0);
	if (err)
		pr_err("port %hu: send follow up failed", portnum(p));
	if (!need_dest_port(p->clock) && is_peer_port(p->clock, p)) {
		msg = p->sync;
		p->sync = NULL;
		msg_put(msg);
		msg = p->follow_up;
		p->follow_up = NULL;
		msg_put(msg);
	}
	return err;
}

static void process_delayed_delay_req(struct port *p, struct ptp_message *msg)
{
	struct ptp_header *hdr;

	hdr = &p->delay_req->header;
	if (!matched_ptp_header(&msg->header, hdr))
		return;

	if (need_dest_port(p->clock) &&
			msg->header.reserved1 != get_master_port(p->clock))
		return;

	memcpy(&p->delay_req->hwts.ts, &msg->hwts.ts, sizeof(msg->hwts.ts));
	if (p->delay_resp) {
		msg = p->delay_resp;
		process_delay_resp(p, msg);
		if (!p->delay_resp)
			msg_put(msg);
	}
}

static int process_delayed_pdelay_req(struct port *p, struct ptp_message *msg)
{
	struct ptp_header *hdr;
	int err = 0;

	/* Response to Pdelay_Req message may already be processed. */
	if (!p->peer_delay_req)
		return 0;

	hdr = &p->peer_delay_req->header;
	if (!matched_ptp_header(&msg->header, hdr))
		return 0;

	/* Pdelay_Req in 1-step mode has real port number in port identity. */
#if 0
	if (need_dest_port(p->clock) &&
	    (p->state == PS_UNCALIBRATED || p->state == PS_SLAVE) &&
	    msg->header.reserved1 != get_master_port(p->clock))
		return 0;
#endif
#if 1
	if (need_dest_port(p->clock) &&
	    msg->header.reserved1 != p->pdelay_resp_port)
		return 0;
#endif

	memcpy(&p->peer_delay_req->hwts.ts, &msg->hwts.ts,
		sizeof(msg->hwts.ts));
	if (p->peer_delay_resp) {
		if (need_dest_port(p->clock) &&
		    msg->header.reserved1 != p->pdelay_resp_port)
			return err;
		msg = p->peer_delay_resp;
		p->peer_delay_resp = NULL;
		err = process_pdelay_resp(p, msg);
		msg_put(msg);
	}
	return err;
}

static int process_delayed_pdelay_resp(struct port *p, struct ptp_message *msg)
{
	struct ptp_message *rsp = p->pdelay_resp;
	struct ptp_message *fup = p->pdelay_resp_fup;
	struct ptp_header *hdr;
	int err = -1;

	if (!fup)
		return 0;

	hdr = &rsp->header;
	if (!matched_ptp_header(&msg->header, hdr))
		return 0;

	if (gptp_test) {
		if (gptp_auto_1as_9_3_rsp_fup(p, msg))
			return 0;
	}

	ts_to_timestamp(&msg->hwts.ts,
			&fup->pdelay_resp_fup.responseOriginTimestamp);

	p->receive_port = msg->header.reserved1;
	err = peer_prepare_and_send(p, fup, 0);
	if (err)
		pr_err("port %hu: send pdelay_resp_fup failed", portnum(p));
	msg = p->pdelay_resp;
	p->pdelay_resp = NULL;
	msg_put(msg);
	msg = p->pdelay_resp_fup;
	p->pdelay_resp_fup = NULL;
	msg_put(msg);
	return err;
}

enum fsm_event port_tx_event(struct port *p, int fd_index)
{
	enum fsm_event event = EV_NONE;
	struct ptp_message *msg;
	int cnt, fd = p->fda.fd[fd_index];

	msg = msg_allocate();
	if (!msg)
		return EV_FAULT_DETECTED;

	msg->hwts.type = p->timestamping;

	cnt = transport_recv_err(p->trp, fd, msg);
	if (cnt <= 0) {
		pr_err("port %hu: recv message failed", portnum(p));
		msg_put(msg);
		return EV_POWERUP;
	}

	switch (msg_type(msg)) {
	case SYNC:
#ifdef KSZ_DBG_HOST
if (!is_host_port(p->clock, p))
printf("  !! %s %d a\n", __func__, portnum(p));
#endif
		if (process_delayed_sync(p, msg))
			event = EV_FAULT_DETECTED;
		break;
	case DELAY_REQ:
#ifdef KSZ_DBG_HOST
if (!is_peer_port(p->clock, p))
printf("  !! %s %d b\n", __func__, portnum(p));
#endif
		process_delayed_delay_req(p, msg);
		break;
	case PDELAY_REQ:
#ifdef KSZ_DBG_HOST
if (!is_peer_port(p->clock, p))
printf("  !! %s %d c\n", __func__, portnum(p));
#endif
		if (process_delayed_pdelay_req(p, msg))
			event = EV_FAULT_DETECTED;
		break;
	case PDELAY_RESP:
#ifdef KSZ_DBG_HOST
if (!is_peer_port(p->clock, p))
printf("  !! %s %d d\n", __func__, portnum(p));
#endif
		if (process_delayed_pdelay_resp(p, msg))
			event = EV_FAULT_DETECTED;
		break;
	}

	msg_put(msg);
	return event;
}
#endif

enum fsm_event port_event(struct port *p, int fd_index)
{
	enum fsm_event event = EV_NONE;
	struct ptp_message *msg;
#ifdef KSZ_1588_PTP
	struct ptp_message *dup = NULL;
#endif
	int cnt, fd = p->fda.fd[fd_index], err;

	switch (fd_index) {
	case FD_SYNC_RX_TIMER:
		p->rx_sync_timeout = 1;
		if (port_is_ieee8021as(p)) {
#ifdef KSZ_DBG_TIMER
printf("syn: %d=%d %d\n", fd_index, p->announceReceiptTimeout, p->syncReceiptTimeout);
#endif
			port_clr_tmo(p->fda.fd[FD_SYNC_RX_TIMER]);
			if (p->sync_rx_timeout) {
#ifdef KSZ_DBG_TIMER
#if 0 
if (portnum(p) == 5)
#endif
printf(" %s sync_rx %d\n", __func__, portnum(p));
#endif
				p->sync_rx_timeout = 0;
			}
#ifdef KSZ_DBG_TIMEOUT_
		do {
			struct timespec now;

			clock_gettime(CLOCK_MONOTONIC, &now);
printf("%ld.%9ld %ld.%9ld ", sync_ts.tv_sec, sync_ts.tv_nsec, now.tv_sec, now.tv_nsec);
			now.tv_sec -= sync_ts.tv_sec;
			if (now.tv_nsec < sync_ts.tv_nsec) {
				now.tv_sec--;
				now.tv_nsec += 1000000000;
			}
			now.tv_nsec -= sync_ts.tv_nsec;
printf(" %ld.%lu sync\n", now.tv_sec, now.tv_nsec);
		} while (0);
#endif
#ifdef KSZ_DBG_TIMEOUT
clock_gettime(CLOCK_MONOTONIC, &sync_ts);
#endif
		}
		if (port_is_aed(p)) {
			exception_log(p->clock, "Sync lost at port %hu",
				      portnum(p));
			p->log_sync_interval = 8;
			port_clr_tmo(p->fda.fd[FD_ANNOUNCE_TIMER]);
			if (p->ann_rx_timeout) {
#ifdef KSZ_DBG_TIMER
#if 0 
if (portnum(p) == 5)
#endif
printf(" %s ann_rx %d\n", __func__, portnum(p));
#endif
				p->ann_rx_timeout = 0;
			}
			if (p->state == PS_SLAVE) {
				port_show_transition(p, PS_UNCALIBRATED,
						     EV_RS_SLAVE);
				p->state = PS_UNCALIBRATED;
			}
			for_other_ports(p,
					port_reset_sync_interval, NULL);
			if (!p->last_sync) {
				if (p->last_fup) {
					msg_put(p->last_fup);
				}
				prepare_sync(p);
				for_other_ports(p, port_set_last_sync_fup, p);
			}
			return EV_NONE;
		}
	case FD_ANNOUNCE_TIMER:
		if (fd_index == FD_ANNOUNCE_TIMER)
			p->rx_sync_timeout = 0;
		pr_debug("port %hu: %s timeout", portnum(p),
			 fd_index == FD_SYNC_RX_TIMER ? "rx sync" : "announce");
		if (p->best)
			fc_clear(p->best);
#ifdef KSZ_DBG_HOST
if (!is_peer_port(p->clock, p))
printf("  !! %s 1\n", __func__);
#endif
		if (clock_slave_only(p->clock) ||
		    PS_MASTER == p->state || PS_GRAND_MASTER == p->state) {
			port_clr_tmo(p->fda.fd[FD_ANNOUNCE_TIMER]);
			port_clr_tmo(p->fda.fd[FD_SYNC_RX_TIMER]);
			if (p->ann_rx_timeout) {
#ifdef KSZ_DBG_TIMER
#if 0 
if (portnum(p) == 5)
#endif
printf(" %s ann_rx %d\n", __func__, portnum(p));
#endif
				p->ann_rx_timeout = 0;
			}
			if (p->sync_rx_timeout) {
#ifdef KSZ_DBG_TIMER
#if 0 
if (portnum(p) == 5)
#endif
printf(" %s sync_rx %d\n", __func__, portnum(p));
#endif
				p->sync_rx_timeout = 0;
			}
		}
		else
		port_set_announce_tmo(p);
#ifdef KSZ_1588_PTP
		if (clock_slave_only(p->clock) && clock_master_lost(p->clock)
				&& port_renew_transport(p)) {
#else
		if (clock_slave_only(p->clock) && p->delayMechanism != DM_P2P &&
		    port_renew_transport(p)) {
#endif
			return EV_FAULT_DETECTED;
		}
		if (p->syncTxCont) {
			p->syncTxCont = 0;
		}
#ifdef KSZ_DBG_TIMER
printf("ann: %d=%d %d\n", fd_index, portnum(p), p->syncTxCont);
#endif
		return EV_ANNOUNCE_RECEIPT_TIMEOUT_EXPIRES;

	case FD_DELAY_TIMER:
		pr_debug("port %hu: delay timeout", portnum(p));
#ifdef KSZ_DBG_HOST
if (!is_peer_port(p->clock, p))
printf("  !! %s %d 2a %p\n", __func__, portnum(p), p);
#endif
#if 1
		if (port_is_aed(p)) {
			if (p->seqnumPdelayReq == 1) {
				p->seqnumPdelayReq = 0;
				p->logMinPdelayReqInterval =
					p->operLogPdelayReqInterval;
				if (p->log_exception)
					exception_log(p->clock,
						      "Pdelay interval changes to %d at port %hu", p->operLogPdelayReqInterval, portnum(p));
			}
		}
#endif
		port_set_delay_tmo(p);
		return port_delay_request(p) ? EV_FAULT_DETECTED : EV_NONE;

	case FD_QUALIFICATION_TIMER:
		pr_debug("port %hu: qualification timeout", portnum(p));
		return EV_QUALIFICATION_TIMEOUT_EXPIRES;

	case FD_MANNO_TIMER:
#ifdef KSZ_DBG_HOST
if (!is_host_port(p->clock, p))
printf("  !! %s %d 3\n", __func__, portnum(p));
#endif
		pr_debug("port %hu: master tx announce timeout", portnum(p));
		port_set_manno_tmo(p);
		return port_tx_announce(p) ? EV_FAULT_DETECTED : EV_NONE;

	case FD_SYNC_TX_TIMER:
		pr_debug("port %hu: master sync timeout", portnum(p));
#ifdef KSZ_DBG_HOST
if (!is_host_port(p->clock, p))
printf("  !! %s %d 4\n", __func__, portnum(p));
#endif
#ifdef KSZ_1588_PTP
		/* Clearing the timeout may not take effect yet. */
		if (p->state != PS_MASTER && p->state != PS_GRAND_MASTER)
			return event;
#endif

		port_set_sync_tx_tmo(p);
		return port_tx_sync(p) ? EV_FAULT_DETECTED : EV_NONE;

#ifdef KSZ_1588_PTP
	case FD_FUP_RX_TIMER:
		port_clr_tmo(p->fda.fd[FD_FUP_RX_TIMER]);
		if (p->fup_rx_timeout) {
#ifdef KSZ_DBG_TIMER
#if 0
if (portnum(p) == 5)
#endif
printf(" %s fup_rx %d\n", __func__, portnum(p));
#endif
			p->fup_rx_timeout = 0;
		}
		if (p->syfu == SF_HAVE_SYNC) {
			msg_put(p->last_syncfup);
			p->syfu = SF_EMPTY;
		}
#ifdef KSZ_DBG_TIMEOUT
		do {
			struct timespec now;

			clock_gettime(CLOCK_MONOTONIC, &now);
printf("%ld.%9ld %ld.%9ld ", fup_ts.tv_sec, fup_ts.tv_nsec, now.tv_sec, now.tv_nsec);
			now.tv_sec -= fup_ts.tv_sec;
			if (now.tv_nsec < fup_ts.tv_nsec) {
				now.tv_sec--;
				now.tv_nsec += 1000000000;
			}
			now.tv_nsec -= fup_ts.tv_nsec;
printf(" %lu ", now.tv_nsec);
		} while (0);
#endif
#if defined(KSZ_DBG_TIMEOUT) && defined(KSZ_DBG_MISS)
		fup_to_id = p->fup_seqid;
printf(" fup to: %x\n", p->fup_seqid);
#endif
		for_other_ports(p,
				port_tc_flush, NULL);
		if (p->no_announce)
printf(" no ann timeout\n");
		if (p->no_announce)
			return EV_NONE;
		if (p->last_fup)
			return EV_NONE;
		return port_event(p, FD_ANNOUNCE_TIMER);
	case FD_SYNC_CONT_TIMER:
		/* Use accurate interval in case Sync is no longer received. */
		p->syncTxContTimeout = p->sync_interval;
		port_set_sync_cont_tmo(p);
		port_tx_sync(p);
		p->fwd_sync = 0;
		p->skip_tx_sync = 0;
		do {
			struct timespec now;

			clock_gettime(CLOCK_MONOTONIC, &now);
			p->last_tx_sync_tmv = timespec_to_tmv(now);
		} while (0);
#ifdef KSZ_DBG_TIMER_
printf(" sync cont\n");
#endif
		return EV_NONE;
	case FD_PDELAY_RESP_FUP_TIMER:
		port_clr_tmo(p->fda.fd[FD_PDELAY_RESP_FUP_TIMER]);
		if (p->delayed_pdelay_req) {
			process_pdelay_req(p, p->delayed_pdelay_req);
			msg_put(p->delayed_pdelay_req);
			p->delayed_pdelay_req = NULL;
		} else if (p->delayed_pdelay_resp) {
			process_delayed_pdelay_resp(p, p->delayed_pdelay_resp);
			msg_put(p->delayed_pdelay_resp);
			p->delayed_pdelay_resp = NULL;
		}
		return EV_NONE;
#endif
	}

	msg = msg_allocate();
	if (!msg)
		return EV_FAULT_DETECTED;

	msg->hwts.type = p->timestamping;

	cnt = transport_recv(p->trp, fd, msg);
	if (cnt <= 0) {
		pr_err("port %hu: recv message failed", portnum(p));
		msg_put(msg);
#ifdef KSZ_1588_PTP
		return EV_POWERUP;
#else
		return EV_FAULT_DETECTED;
#endif
	}
#ifdef KSZ_1588_PTP
	/* A hack to drop looped transmitted raw frame. */
	if (cnt <= 1) {
		msg_put(msg);
		return EV_NONE;
	}
	p->receive_port = portnum(p);
	if (need_dest_port(p->clock)) {
		if (get_hw_version(p->clock) >= 2) {
			u32 port;
			u32 sec;
			u32 nsec;
			int rc;
			int tx = 0;

			rc = port_get_msg_info(p, &msg->header, &tx,
				&port, &sec, &nsec);
			if (!rc) {
#if 0
printf("rc: %d\n", port);
#endif
				p->receive_port = port;
			}
		} else {
			p->receive_port = msg->header.reserved1;
		}
	}
#endif
#ifdef KSZ_1588_PTP
	if (port_is_ieee8021as(p) &&
	    (msg_type(msg) == SYNC || msg_type(msg) == FOLLOW_UP ||
	    msg_type(msg) == ANNOUNCE)) {
		dup = msg_duplicate(msg, cnt);
		p->msg_cnt = cnt;
	}
#endif
	err = msg_post_recv(msg, cnt);
	if (err) {
		switch (err) {
		case -EBADMSG:
			pr_err("port %hu: bad message", portnum(p));
			break;
		case -ETIME:
			pr_err("port %hu: received %s without timestamp",
				portnum(p), msg_type_string(msg_type(msg)));
			break;
		case -EPROTO:
			pr_debug("port %hu: ignoring message", portnum(p));
			break;
		}
#ifdef KSZ_1588_PTP
		if (dup)
			msg_put(dup);
#endif
		msg_put(msg);
		return EV_NONE;
	}
	if (msg_sots_valid(msg)) {
#ifndef KSZ_1588_PTP_
		ts_add(&msg->hwts.ts, -p->rx_timestamp_offset);
#endif
#ifdef KSZ_1588_PTP
		if (msg_type(msg) == SYNC)
#endif
		clock_check_ts(p->clock, msg->hwts.ts);
	}
#ifdef KSZ_1588_PTP
	if (msg_type(msg) == SYNC) {
		p->sync_rx++;
#ifdef KSZ_DBG_MISS
		sync_rx_slave++;
#endif
	} else if (msg_type(msg) == FOLLOW_UP)
		p->fup_rx++;
#endif
	if (port_ignore(p, msg)) {
#ifdef KSZ_1588_PTP
		if (dup)
			msg_put(dup);
#endif
		msg_put(msg);
		return EV_NONE;
	}

	switch (msg_type(msg)) {
	case SYNC:
#ifdef KSZ_DBG_HOST
if (!is_peer_port(p->clock, p))
printf("  !! %s %d a\n", __func__, portnum(p));
#endif
		process_sync(p, msg);
#ifdef KSZ_1588_PTP
		if (dup && p->sync_fup_ok) {
			tc_fwd_event(p, dup);
		}
#endif
		break;
	case DELAY_REQ:
#ifdef KSZ_DBG_HOST
if (!is_peer_port(p->clock, p))
printf("  !! %s %d b\n", __func__, portnum(p));
#endif
		if (process_delay_req(p, msg))
			event = EV_FAULT_DETECTED;
		break;
	case PDELAY_REQ:
#ifdef KSZ_DBG_HOST
if (!is_peer_port(p->clock, p))
printf("  !! %s %d c\n", __func__, portnum(p));
else
#endif
		if (process_pdelay_req(p, msg))
			event = EV_FAULT_DETECTED;
		break;
	case PDELAY_RESP:
#ifdef KSZ_DBG_HOST
if (!is_peer_port(p->clock, p))
printf("  !! %s %d d\n", __func__, portnum(p));
#endif
#ifdef KSZ_1588_PTP
		p->pdelay_resp_port = p->receive_port;
#endif
		if (process_pdelay_resp(p, msg))
			event = EV_FAULT_DETECTED;
		break;
	case FOLLOW_UP:
#ifdef KSZ_DBG_HOST
if (!is_peer_port(p->clock, p))
printf("  !! %s %d e\n", __func__, portnum(p));
#endif
		process_follow_up(p, msg);
#ifdef KSZ_1588_PTP
		if (dup && p->sync_fup_ok) {
			struct follow_up_info_tlv *f;

			f = (struct follow_up_info_tlv *)
				dup->follow_up.suffix;
			clock_get_follow_up_info(p->clock, f);
			tlv_pre_send((struct TLV *)f, NULL);
			tc_fwd_folup(p, dup);
		}
		for_other_ports(p, port_set_last_sync_fup, p);
		if (port_is_aed(p)) {
			if (p->state == PS_SLAVE && p->seqnumSync) {
				p->seqnumSync--;
				if (!p->seqnumSync) {
					p->report_interval = get_cnt_from_log(
					p->log_sync_interval,
					1);
					p->logSyncInterval = p->operLogSyncInterval;
					port_tx_signaling(p);
					if (p->log_exception &&
					    p->log_sync_interval !=
					    p->logSyncInterval)
						exception_log(p->clock,
							      "Sync interval changes to %d at port %hu", p->operLogSyncInterval, portnum(p));
			p->seqnumSync = get_cnt_from_log(p->logSyncInterval,
							 10);
				}
			}
#if 0
			} else if (p->state == PS_UNCALIBRATED &&
				   p->log_sync_interval > p->logSyncInterval)
				port_tx_signaling(p);
			if (p->state == PS_UNCALIBRATED)
printf(" %d %d\n", p->log_sync_interval, p->logSyncInterval);
#endif
		}
#endif
		break;
	case DELAY_RESP:
#ifdef KSZ_DBG_HOST
if (!is_peer_port(p->clock, p))
printf("  !! %s %d f\n", __func__, portnum(p));
#endif
		process_delay_resp(p, msg);
#ifdef KSZ_1588_PTP
		if (p->delay_resp)
			msg_get(msg);
#endif
		break;
	case PDELAY_RESP_FOLLOW_UP:
#ifdef KSZ_DBG_HOST
if (!is_peer_port(p->clock, p))
printf("  !! %s %d g\n", __func__, portnum(p));
#endif
#ifdef KSZ_1588_PTP
		p->pdelay_resp_fup_port = p->receive_port;
#endif
		process_pdelay_resp_fup(p, msg);
		break;
	case ANNOUNCE:
#ifdef KSZ_DBG_HOST
if (!is_peer_port(p->clock, p))
printf("  !! %s %d h\n", __func__, portnum(p));
#endif
		if (process_announce(p, msg))
			event = EV_STATE_DECISION_EVENT;
#ifdef KSZ_1588_PTP
		if (dup && p->announce_ok) {
			if (p->state == PS_SLAVE ||
			    p->state == PS_UNCALIBRATED) {
				tc_forward(p, dup);
			} else if (event == EV_STATE_DECISION_EVENT) {
				if (p->last_announce) {
					msg_put(p->last_announce);
				}
				msg_get(dup);
				p->last_announce = dup;
#ifdef KSZ_DBG_TIMEOUT
printf("first ann\n");
#endif
			}
		}
		if (event == EV_STATE_DECISION_EVENT) {
			if (p->prev_announce)
				msg_put(p->prev_announce);
			msg_get(msg);
			p->prev_announce = msg;
		}
#endif
		break;
	case SIGNALING:
#ifdef KSZ_1588_PTP
		process_signaling(p, msg);
#endif
		break;
	case MANAGEMENT:
		if (clock_manage(p->clock, p, msg))
			event = EV_STATE_DECISION_EVENT;
		break;
	}

#ifdef KSZ_1588_PTP
	if (dup)
		msg_put(dup);
#endif
	msg_put(msg);
	return event;
}

int port_forward(struct port *p, struct ptp_message *msg)
{
	int cnt;
#ifdef KSZ_1588_PTP
	if (p->forward_port)
		port_set_msg_info(p, &msg->header,
			portdst(p->forward_port), 0, 0);
#endif
	cnt = transport_send(p->trp, &p->fda, 0, msg);
	return cnt <= 0 ? -1 : 0;
}

int port_forward_to(struct port *p, struct ptp_message *msg)
{
	int cnt;
#ifdef KSZ_1588_PTP
	if (p->forward_port)
		port_set_msg_info(p, &msg->header,
			portdst(p->forward_port), 0, 0);
#endif
	cnt = transport_sendto(p->trp, &p->fda, 0, msg);
	return cnt <= 0 ? -1 : 0;
}

int port_prepare_and_send(struct port *p, struct ptp_message *msg, int event)
{
	int cnt;

	if (msg_pre_send(msg))
		return -1;
#ifdef KSZ_1588_PTP
	if (need_dest_port(p->clock) && p->dest_port) {
		if (get_hw_version(p->clock) < 2)
			msg->header.reserved1 = p->dest_port;
		if (get_hw_version(p->clock) >= 2)
			port_set_msg_info(p, &msg->header,
				portdst(p->dest_port), 0, 0);
	}
	if (portnum(p) == ptp_host_port) {
		if (get_hw_version(p->clock) >= 2)
			port_set_msg_info(p, &msg->header,
				p->port_mask, 0, 0);
	}
	if (msg_type(msg) == SYNC) {
#ifdef KSZ_DBG_MISS
		if (!p->sync_tx)
printf(" rx sync: %d=%d\n", portnum(p), sync_rx_slave);
#endif
		p->sync_tx++;
	} else if (msg_type(msg) == FOLLOW_UP)
		p->fup_tx++;
#endif

	if (msg->header.flagField[0] & UNICAST) {
		cnt = transport_sendto(p->trp, &p->fda, event, msg);
	} else {
		cnt = transport_send(p->trp, &p->fda, event, msg);
	}
	if (cnt <= 0) {
		return -1;
	}
#ifndef KSZ_1588_PTP_
	if (msg_sots_valid(msg)) {
		ts_add(&msg->hwts.ts, p->tx_timestamp_offset);
	}
#endif
	return 0;
}

struct PortIdentity port_identity(struct port *p)
{
	return p->portIdentity;
}

int port_number(struct port *p)
{
	return portnum(p);
}

int port_link_status_get(struct port *p)
{
	return p->link_status;
}

void port_link_status_set(struct port *p, int up)
{
	p->link_status = up ? 1 : 0;
	pr_notice("port %hu: link %s", portnum(p), up ? "up" : "down");
#ifdef KSZ_1588_PTP
	if (port_is_aed(p) && p->report_link)
		exception_log(p->clock,
			      "port %hu: link %s", portnum(p), up ?
			      "up" : "down");
#endif
}

int port_manage(struct port *p, struct port *ingress, struct ptp_message *msg)
{
	struct management_tlv *mgt;
	UInteger16 target = msg->management.targetPortIdentity.portNumber;

	if (target != portnum(p) && target != 0xffff) {
		return 0;
	}
	mgt = (struct management_tlv *) msg->management.suffix;

	switch (management_action(msg)) {
	case GET:
		if (port_management_get_response(p, ingress, mgt->id, msg))
			return 1;
		break;
	case SET:
		if (port_management_set(p, ingress, mgt->id, msg))
			return 1;
		break;
	case COMMAND:
		break;
	default:
		return -1;
	}

	switch (mgt->id) {
	case TLV_NULL_MANAGEMENT:
	case TLV_CLOCK_DESCRIPTION:
	case TLV_PORT_DATA_SET:
	case TLV_LOG_ANNOUNCE_INTERVAL:
	case TLV_ANNOUNCE_RECEIPT_TIMEOUT:
	case TLV_LOG_SYNC_INTERVAL:
	case TLV_VERSION_NUMBER:
#ifndef KSZ_1588_PTP
	case TLV_ENABLE_PORT:
	case TLV_DISABLE_PORT:
#endif
	case TLV_UNICAST_NEGOTIATION_ENABLE:
	case TLV_UNICAST_MASTER_TABLE:
	case TLV_UNICAST_MASTER_MAX_TABLE_SIZE:
	case TLV_ACCEPTABLE_MASTER_TABLE_ENABLED:
	case TLV_ALTERNATE_MASTER:
	case TLV_TRANSPARENT_CLOCK_PORT_DATA_SET:
	case TLV_DELAY_MECHANISM:
	case TLV_LOG_MIN_PDELAY_REQ_INTERVAL:
		port_management_send_error(p, ingress, msg, TLV_NOT_SUPPORTED);
		break;
	default:
		port_management_send_error(p, ingress, msg, TLV_NO_SUCH_ID);
		return -1;
	}
	return 1;
}

int port_management_error(struct PortIdentity pid, struct port *ingress,
			  struct ptp_message *req, Enumeration16 error_id)
{
	struct ptp_message *msg;
	struct management_tlv *mgt;
	struct management_error_status *mes;
	int err = 0, pdulen;

	msg = port_management_reply(pid, ingress, req);
	if (!msg) {
		return -1;
	}
	mgt = (struct management_tlv *) req->management.suffix;
	mes = (struct management_error_status *) msg->management.suffix;
	mes->type = TLV_MANAGEMENT_ERROR_STATUS;
	mes->length = 8;
	mes->error = error_id;
	mes->id = mgt->id;
	pdulen = msg->header.messageLength + sizeof(*mes);
	msg->header.messageLength = pdulen;
	msg->tlv_count = 1;

#ifdef KSZ_1588_PTP
	ingress->dest_port = ingress->receive_port;
#endif
	err = port_prepare_and_send(ingress, msg, 0);
	msg_put(msg);
	return err;
}

static struct ptp_message *
port_management_construct(struct PortIdentity pid, struct port *ingress,
			  UInteger16 sequenceId,
			  struct PortIdentity *targetPortIdentity,
			  UInteger8 boundaryHops, uint8_t action)
{
	struct ptp_message *msg;
	int pdulen;

	msg = msg_allocate();
	if (!msg)
		return NULL;

	pdulen = sizeof(struct management_msg);
	msg->hwts.type = ingress->timestamping;

	msg->header.tsmt               = MANAGEMENT | ingress->transportSpecific;
	msg->header.ver                = PTP_VERSION;
	msg->header.messageLength      = pdulen;
	msg->header.domainNumber       = clock_domain_number(ingress->clock);
	msg->header.sourcePortIdentity = pid;
	msg->header.sequenceId         = sequenceId;
	msg->header.control            = CTL_MANAGEMENT;
	msg->header.logMessageInterval = 0x7f;

	if (targetPortIdentity)
		msg->management.targetPortIdentity = *targetPortIdentity;
	msg->management.startingBoundaryHops = boundaryHops;
	msg->management.boundaryHops = boundaryHops;

	switch (action) {
	case GET: case SET:
		msg->management.flags = RESPONSE;
		break;
	case COMMAND:
		msg->management.flags = ACKNOWLEDGE;
		break;
	}
	return msg;
}

struct ptp_message *port_management_reply(struct PortIdentity pid,
					  struct port *ingress,
					  struct ptp_message *req)
{
	UInteger8 boundaryHops;

	boundaryHops = req->management.startingBoundaryHops -
		       req->management.boundaryHops;
	return port_management_construct(pid, ingress,
					 req->header.sequenceId,
					 &req->header.sourcePortIdentity,
					 boundaryHops,
					 management_action(req));
}

struct ptp_message *port_management_notify(struct PortIdentity pid,
					   struct port *port)
{
	return port_management_construct(pid, port, 0, NULL, 1, GET);
}

void port_notify_event(struct port *p, enum notification event)
{
	struct PortIdentity pid = port_identity(p);
	struct ptp_message *msg;
	UInteger16 msg_len;
	int id;

	switch (event) {
	case NOTIFY_PORT_STATE:
		id = TLV_PORT_DATA_SET;
		break;
	default:
		return;
	}
	/* targetPortIdentity and sequenceId will be filled by
	 * clock_send_notification */
	msg = port_management_notify(pid, p);
	if (!msg)
		return;
	if (!port_management_fill_response(p, msg, id))
		goto err;
	msg_len = msg->header.messageLength;
	if (msg_pre_send(msg))
		goto err;
	clock_send_notification(p->clock, msg, msg_len, event);
err:
	msg_put(msg);
}

struct port *port_open(int phc_index,
		       enum timestamp_type timestamping,
		       int number,
		       struct interface *interface,
		       struct clock *clock)
{
	struct config *cfg = clock_config(clock);
	struct port *p = malloc(sizeof(*p));
	enum transport_type transport;
	int i;

	if (!p)
		return NULL;

	memset(p, 0, sizeof(*p));
	TAILQ_INIT(&p->tc_transmitted);

	p->state_machine = clock_slave_only(clock) ? ptp_slave_fsm : ptp_fsm;
	p->phc_index = phc_index;
	p->jbod = config_get_int(cfg, interface->name, "boundary_clock_jbod");
	transport = config_get_int(cfg, interface->name, "network_transport");

	if (transport == TRANS_UDS)
		; /* UDS cannot have a PHC. */
	else if (!interface->ts_info.valid)
		pr_warning("port %d: get_ts_info not supported", number);
	else if (phc_index >= 0 && phc_index != interface->ts_info.phc_index) {
		if (p->jbod) {
			pr_warning("port %d: just a bunch of devices", number);
			p->phc_index = interface->ts_info.phc_index;
		} else {
			pr_err("port %d: PHC device mismatch", number);
			pr_err("port %d: /dev/ptp%d requested, ptp%d attached",
			       number, phc_index, interface->ts_info.phc_index);
			goto err_port;
		}
	}

#ifdef KSZ_1588_PTP
	p->basename = interface->basename;
	p->devname = interface->devname;
	p->host_port = p;

	/* Port number may not be the same as index. */
	p->index = number;
#endif
	p->name = interface->name;
	p->asymmetry = config_get_int(cfg, p->name, "delayAsymmetry");
	p->asymmetry <<= 16;
	p->announce_span = transport == TRANS_UDS ? 0 : ANNOUNCE_SPAN;
	p->follow_up_info = config_get_int(cfg, p->name, "follow_up_info");
	p->freq_est_interval = config_get_int(cfg, p->name, "freq_est_interval");
	p->hybrid_e2e = config_get_int(cfg, p->name, "hybrid_e2e");
	p->path_trace_enabled = config_get_int(cfg, p->name, "path_trace_enabled");
	p->rx_timestamp_offset = config_get_int(cfg, p->name, "ingressLatency");
	p->tx_timestamp_offset = config_get_int(cfg, p->name, "egressLatency");
#ifdef KSZ_1588_PTP
	p->log_exception = config_get_int(cfg, p->name, "log_exception");
	p->no_asCapable = config_get_int(cfg, p->name, "no_asCapable");
	p->no_announce = config_get_int(cfg, p->name, "no_announce");
	p->no_id_check = config_get_int(cfg, p->name, "no_id_check");
#endif
	p->link_status = 1;
	p->clock = clock;
	p->trp = transport_create(cfg, transport);
	if (!p->trp)
		goto err_port;
	p->timestamping = timestamping;
	p->portIdentity.clockIdentity = clock_identity(clock);
	p->portIdentity.portNumber = number;
	p->state = PS_INITIALIZING;
	p->delayMechanism = config_get_int(cfg, p->name, "delay_mechanism");
	p->versionNumber = PTP_VERSION;

	if (p->hybrid_e2e && p->delayMechanism != DM_E2E) {
		pr_warning("port %d: hybrid_e2e only works with E2E", number);
	}

	/* Set fault timeouts to a default value */
	for (i = 0; i < FT_CNT; i++) {
		p->flt_interval_pertype[i].type = FTMO_LOG2_SECONDS;
		p->flt_interval_pertype[i].val = 4;
	}
	p->flt_interval_pertype[FT_BAD_PEER_NETWORK].type = FTMO_LINEAR_SECONDS;
	p->flt_interval_pertype[FT_BAD_PEER_NETWORK].val =
		config_get_int(cfg, p->name, "fault_badpeernet_interval");

	p->flt_interval_pertype[FT_UNSPECIFIED].val =
		config_get_int(cfg, p->name, "fault_reset_interval");

	p->tsproc = tsproc_create(config_get_int(cfg, p->name, "tsproc_mode"),
				  config_get_int(cfg, p->name, "delay_filter"),
				  config_get_int(cfg, p->name, "delay_filter_length"));
	if (!p->tsproc) {
		pr_err("Failed to create time stamp processor");
		goto err_transport;
	}
	p->nrate.ratio = 1.0;

	port_clear_fda(p, N_POLLFD);
	p->fault_fd = -1;
	if (number) {
		p->fault_fd = timerfd_create(CLOCK_MONOTONIC, 0);
		if (p->fault_fd < 0) {
			pr_err("timerfd_create failed: %m");
			goto err_tsproc;
		}
	}
	return p;

err_tsproc:
	tsproc_destroy(p->tsproc);
err_transport:
	transport_destroy(p->trp);
err_port:
	free(p);
	return NULL;
}

enum port_state port_state(struct port *port)
{
	return port->state;
}
