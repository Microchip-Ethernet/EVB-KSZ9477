/****************************************************************************
  Copyright (c) 2012, Intel Corporation
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

   1. Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.

   2. Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.

   3. Neither the name of the Intel Corporation nor the names of its
      contributors may be used to endorse or promote products derived from
      this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE.

******************************************************************************/
/*
 * MRP protocol (part of 802.1Q-2011)
 */

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>

#include "mrpd.h"
#include "mrp.h"

#ifdef MICREL_1588_PTP
extern int mrp_index;

#define USE_NET_IOCTL

#include "ksz_mrp_api.c"

struct dev_info mrpdev;
void *fd = &mrpdev;

void exit_mrp_dev(void)
{
	int rc;

	rc = mrp_dev_exit(&mrpdev);
	close(mrpdev.sock);
}

int init_mrp_dev(char *name)
{
	int rc;
	char *p;

	strncpy(mrpdev.name, name, sizeof(mrpdev.name));
	p = strchr(mrpdev.name, '.');
	if (p)
		*p = '\0';
	mrpdev.sock = socket(AF_INET, SOCK_DGRAM, 0);
	rc = mrp_dev_init(&mrpdev, 0, &mrp_version, &mrp_ports);
	if (ofp)
		fprintf(ofp, "version=%d ports=%d\n", mrp_version, mrp_ports);
	return mrp_ports;
}
#endif


/* state machine controls */
int p2pmac;

char *mrp_event_string(int e)
{
	switch (e) {
	case MRP_EVENT_BEGIN:
		return "Begin!";
	case MRP_EVENT_NEW:
		return "New!";
	case MRP_EVENT_JOIN:
		return "Join!";
	case MRP_EVENT_LV:
		return "Lv!";
	case MRP_EVENT_TX:
		return "tx!";
	case MRP_EVENT_TXLA:
		return "txLA!";
	case MRP_EVENT_TXLAF:
		return "txLAF!";
	case MRP_EVENT_RNEW:
		return "rNew!";
	case MRP_EVENT_RJOININ:
		return "rJoinIn!";
	case MRP_EVENT_RIN:
		return "rIn!";
	case MRP_EVENT_RJOINMT:
		return "rJoinMt!";
	case MRP_EVENT_RMT:
		return "rMt!";
	case MRP_EVENT_RLV:
		return "rLv!";
	case MRP_EVENT_RLA:
		return "rLA!";
	case MRP_EVENT_FLUSH:
		return "Flush!";
	case MRP_EVENT_REDECLARE:
		return "Re-Declare!";
	case MRP_EVENT_PERIODIC:
		return "periodic!";
	case MRP_EVENT_PERIODIC_ENABLE:
		return "ENABLE";
	case MRP_EVENT_PERIODIC_DISABLE:
		return "DISABLE";
	case MRP_EVENT_LVTIMER:
		return "leavetimer!";
	case MRP_EVENT_LVATIMER:
		return "leavealltimer!";
	default:
		return "UNKNOWN";
	}
}

static char *mrp_state_string(int s)
{
	switch (s) {
	case MRP_VO_STATE:
		return "VO";
	case MRP_VP_STATE:
		return "VP";
	case MRP_VN_STATE:
		return "VN";
	case MRP_AN_STATE:
		return "AN";
	case MRP_AA_STATE:
		return "AA";
	case MRP_QA_STATE:
		return "QA";
	case MRP_LA_STATE:
		return "LA";
	case MRP_AO_STATE:
		return "AO";
	case MRP_QO_STATE:
		return "QO";
	case MRP_AP_STATE:
		return "AP";
	case MRP_QP_STATE:
		return "QP";
	case MRP_LO_STATE:
		return "LO";

	case MRP_IN_STATE:
		return "IN";
	case MRP_LV_STATE:
		return "LV";
	case MRP_MT_STATE:
		return "MT";
	default:
		return "??";
	}
}

static char *mrp_lvatimer_state_string(int s)
{
	if (s == MRP_TIMER_PASSIVE)
		return "PASSIVE";
	else if (s == MRP_TIMER_ACTIVE)
		return "ACTIVE";
	else
		return "??";
}

static int client_lookup(client_t * list, struct sockaddr_in *newclient)
{
	client_t *client_item;

	client_item = list;

	if (NULL == newclient)
		return 0;

	while (NULL != client_item) {
		if (client_item->client.sin_port == newclient->sin_port)
			return 1;
		client_item = client_item->next;
	}
	return 0;
}

int mrp_client_add(client_t ** list, struct sockaddr_in *newclient)
{
	client_t *client_item;

	client_item = *list;

	if (NULL == newclient)
#ifdef MICREL_1588_PTP
		return 0;
#else
		return -1;
#endif

	if (client_lookup(client_item, newclient))
		return 0;	/* already present */

	/* handle 1st entry into list */
	if (NULL == client_item) {
		client_item = malloc(sizeof(client_t));
		if (NULL == client_item)
			return -1;
		client_item->next = NULL;
		client_item->client = *newclient;
		*list = client_item;
#ifdef MICREL_1588_PTP
		return 1;
#else
		return 0;
#endif
	}

	while (client_item) {
		if (NULL == client_item->next) {
			client_item->next = malloc(sizeof(client_t));
			if (NULL == client_item->next)
				return -1;
			client_item = client_item->next;
			client_item->next = NULL;
			client_item->client = *newclient;
#ifdef MICREL_1588_PTP
			return 1;
#else
			return 0;
#endif
		}
		client_item = client_item->next;
	}
	return -1;
}

int mrp_client_delete(client_t ** list, struct sockaddr_in *newclient)
{
	client_t *client_item;
	client_t *client_last;

	client_item = *list;
	client_last = NULL;

	if (NULL == newclient)
		return 0;

	if (NULL == client_item)
		return 0;

	while (NULL != client_item) {
		if (0 == memcmp((uint8_t *) newclient,
				(uint8_t *) & client_item->client,
				sizeof(struct sockaddr_in))) {

			if (client_last) {
				client_last->next = client_item->next;
				free(client_item);
			} else {
				/* reset the head pointer */
				*list = client_item->next;
				free(client_item);
			}
			return 0;
		}
		client_last = client_item;
		client_item = client_item->next;
	}
	/* not found ... no error */
	return 0;
}

int mrp_jointimer_start(struct mrp_database *mrp_db)
{
	int ret = 0;
	/* 10.7.4.1 - interval between transmit opportunities
	 * for applicant state machine
	 */
#if LOG_TIMERS
	if (mrp_db->join_timer_running)
		mrpd_log_printf("MRP join timer running\n");
	else
		mrpd_log_printf("MRP join timer start \n");
#endif
	if (!mrp_db->join_timer_running) {
		ret = mrpd_timer_start(mrp_db->join_timer, MRP_JOINTIMER_VAL);
	}
	if (ret >= 0)
		mrp_db->join_timer_running = 1;
	return ret;
}

int mrp_jointimer_stop(struct mrp_database *mrp_db)
{
#if LOG_TIMERS
	mrpd_log_printf("MRP stop join timer\n");
#endif
	mrp_db->join_timer_running = 0;
	return mrpd_timer_stop(mrp_db->join_timer);
}

int mrp_lvtimer_start(struct mrp_database *mrp_db)
{
	int ret;
	/* leavetimer has expired (10.7.5.21)
	 * controls how long the Registrar state machine stays in the
	 * LV state before transitioning to the MT state.
	 */
#if LOG_TIMERS
	if (mrp_db->lv_timer_running)
		mrpd_log_printf("MRP start leave timer *ALREADY RUNNING*\n");
	else
		mrpd_log_printf("MRP start leave timer\n");
#endif
	ret = mrpd_timer_start(mrp_db->lv_timer, MRP_LVTIMER_VAL);
	if (ret >= 0)
		mrp_db->lv_timer_running = 1;
	return ret;
}

int mrp_lvtimer_stop(struct mrp_database *mrp_db)
{
#if LOG_TIMERS
	mrpd_log_printf("MRP stop leave timer\n");
#endif
	mrp_db->lv_timer_running = 0;
	return mrpd_timer_stop(mrp_db->lv_timer);
}

static unsigned long lva_next;

int mrp_lvatimer_start(struct mrp_database *mrp_db)
{
	int ret = 0;
	int timeout = 0;
	/* leavealltimer has expired. (10.7.5.22)
	 * on expire, sends a LEAVEALL message
	 * value is RANDOM in range (LeaveAllTime , 1.5xLeaveAllTime)
	 * timer is for all attributes of a given application and port, but
	 * expires each listed attribute individually (per application)
	 */
	timeout = MRP_LVATIMER_VAL + (random() % (MRP_LVATIMER_VAL / 2));
#if LOG_TIMERS
	if (mrp_db->lva_timer_running)
		mrpd_log_printf("MRP leaveAll timer already running \n",
				timeout);
	else
		mrpd_log_printf("MRP start leaveAll timer (%d ms)\n", timeout);
#endif
	if (!mrp_db->lva_timer_running)
		ret = mrpd_timer_start(mrp_db->lva_timer, timeout);
	if (ret >= 0)
		mrp_db->lva_timer_running = 1;
	return ret;
}

int mrp_lvatimer_stop(struct mrp_database *mrp_db)
{
#if LOG_TIMERS
	mrpd_log_printf("MRP stop leaveAll timer\n");
#endif
	mrp_db->lva_timer_running = 0;
	return mrpd_timer_stop(mrp_db->lva_timer);
}

int mrp_lvatimer_fsm(struct mrp_database *mrp_db, int event)
{
	int la_state;
	int sndmsg = MRP_SND_NONE;
	int tx = 0;
#ifdef MICREL_1588_PTP
	int rc = 0;
#endif

	if (NULL == mrp_db)
		return -1;

	la_state = mrp_db->lva.state;

	switch (event) {
	case MRP_EVENT_BEGIN:
		la_state = MRP_TIMER_PASSIVE;
		mrp_lvatimer_start(mrp_db);
		break;
	case MRP_EVENT_TX:
		if (la_state == MRP_TIMER_ACTIVE) {
			tx = 1;
			sndmsg = MRP_SND_LVA;
			la_state = MRP_TIMER_PASSIVE;
		}
		break;
	case MRP_EVENT_RLA:
		la_state = MRP_TIMER_PASSIVE;
		mrp_lvatimer_stop(mrp_db);
		mrp_lvatimer_start(mrp_db);
		break;
	case MRP_EVENT_LVATIMER:
		la_state = MRP_TIMER_ACTIVE;
		mrp_lvatimer_stop(mrp_db);
		mrp_lvatimer_start(mrp_db);
		break;
	default:
		printf("mrp_lvatimer_fsm:unexpected event (%d), state %s\n",
			event, mrp_lvatimer_state_string(la_state));
		return -1;
		break;
	}
#if LOG_MVRP || LOG_MSRP || LOG_MMRP
	if (mrp_db->lva.state != la_state) {
		mrpd_log_printf("mrp_lvatimer_fsm event %s state %s -> %s\n",
				mrp_event_string(event),
				mrp_lvatimer_state_string(mrp_db->lva.state),
				mrp_lvatimer_state_string(la_state));
	} else {
		mrpd_log_printf("mrp_lvatimer_fsm event %s state %s\n",
				mrp_event_string(event),
				mrp_lvatimer_state_string(la_state));
	}
#endif
#ifdef MICREL_1588_PTP
	/* Request transmit opportunity. */
	if (la_state != mrp_db->lva.state && MRP_TIMER_ACTIVE == la_state)
		rc = 1;
#endif
	mrp_db->lva.state = la_state;
	mrp_db->lva.sndmsg = sndmsg;
	mrp_db->lva.tx = tx;

#ifdef MICREL_1588_PTP
	return rc;
#else
	return 0;
#endif
}

#ifdef LATER
int mrp_periodictimer_fsm(struct mrp_database *mrp_db, int event)
{
	int p_state;
	int sndmsg = MRP_SND_NONE;
	int tx = 0;

	if (NULL == mrp_db)
		return -1;

	p_state = mrp_db->periodic.state;

	switch (event) {
	case MRP_EVENT_BEGIN:
		p_state = MRP_TIMER_ACTIVE;
		mrp_periodictimer_start();
		break;
	case MRP_EVENT_PERIODIC:
		if (p_state == MRP_TIMER_ACTIVE) {
			mrp_periodictimer_start();
		}
		break;
	case MRP_EVENT_PERIODIC_DISABLE:
		p_state = MRP_TIMER_PASSIVE;
		/* this lets the timer expire without rescheduling */
		break;
	case MRP_EVENT_PERIODIC_ENABLE:
		if (p_state == MRP_TIMER_PASSIVE) {
			p_state = MRP_TIMER_ACTIVE;
			mrp_periodictimer_start();
		}
		break;
	default:
		printf("mrp_periodictimer_fsm:unexpected event (%d), state %s\n",
			event, mrp_lvatimer_state_string(p_state));
		return;
		break;
	}
	mrp_db->periodic.state = p_state;
	mrp_db->periodic.sndmsg = sndmsg;
	mrp_db->periodic.tx = tx;
}
#endif

/*
 * per-attribute MRP FSM
 */

#ifdef MICREL_1588_PTP
int mrp_applicant_chk(struct mrp_database *mrp_db,
		      mrp_applicant_attribute_t * attrib)
{
	if (attrib->new_state != attrib->mrp_state) {
		if (MRP_VO_STATE == attrib->new_state) {
			if (!attrib->aging)
				attrib->aging = 4;
		} else if (MRP_LO_STATE != attrib->new_state)
			attrib->aging = 0;
		attrib->mrp_state = attrib->new_state;
	}
	if (MRP_MT_STATE != mrp_db->registrar_state)
		attrib->aging = 0;
	if (attrib->sndmsg != MRP_SND_NULL) {
		if (attrib->aging > 1)
			--attrib->aging;
		if (1 == attrib->aging && MRP_LO_STATE != attrib->mrp_state)
			mrp_db->reclaim = 2;
		attrib->sndmsg = MRP_SND_NULL;
	}
	return 0;
}
#endif

int mrp_applicant_fsm(struct mrp_database *mrp_db,
		      mrp_applicant_attribute_t * attrib, int event)
{
	int tx = 0;
	int optional = 0;
	int mrp_state = attrib->mrp_state;
	int sndmsg = MRP_SND_NULL;
#ifdef MICREL_1588_PTP
	int rc = 0;
#endif
	(void)mrp_db;

	switch (event) {
	case MRP_EVENT_BEGIN:
		mrp_state = MRP_VO_STATE;
		break;
	case MRP_EVENT_NEW:
		/*
		 * New declaration (publish) event as a result
		 * of a mad_join request
		 */
		switch (mrp_state) {
		case MRP_VN_STATE:
		case MRP_AN_STATE:
			/* do nothing */
			break;
		default:
			mrp_state = MRP_VN_STATE;
			break;
		}
		break;
	case MRP_EVENT_JOIN:
		/*
		 * declaration (of interest) event as a result of
		 * a mad_join request
		 */
		switch (mrp_state) {
		case MRP_LO_STATE:
		case MRP_VO_STATE:
			mrp_state = MRP_VP_STATE;
			break;
		case MRP_LA_STATE:
			mrp_state = MRP_AA_STATE;
			break;
		case MRP_AO_STATE:
			mrp_state = MRP_AP_STATE;
			break;
		case MRP_QO_STATE:
			mrp_state = MRP_QP_STATE;
			break;
		default:
			break;
		}
		break;
	case MRP_EVENT_LV:
		/*
		 * declaration removal event as a result of a mad_leave request
		 */
		switch (mrp_state) {
		case MRP_VN_STATE:
		case MRP_AN_STATE:
		case MRP_AA_STATE:
		case MRP_QA_STATE:
			mrp_state = MRP_LA_STATE;
			break;
		case MRP_VP_STATE:
			mrp_state = MRP_VO_STATE;
			break;
		case MRP_AP_STATE:
			mrp_state = MRP_AO_STATE;
			break;
		case MRP_QP_STATE:
			mrp_state = MRP_QO_STATE;
			break;
		default:
			break;
		}
		break;
	case MRP_EVENT_TXLA:
		/*
		 * transmit leaveall is signaled (overrides a TX)
		 */
		switch (mrp_state) {
		case MRP_VO_STATE:
			/* send <NULL> only if it improves encoding */
			optional = 1;
			tx = 1;
			sndmsg = MRP_SND_IN;
			mrp_state = MRP_LO_STATE;
			break;
		case MRP_VP_STATE:
			tx = 1;
			sndmsg = MRP_SND_IN;
			mrp_state = MRP_AA_STATE;
			break;
		case MRP_VN_STATE:
			/* send NEW */
			tx = 1;
#ifdef MICREL_1588_PTP
			sndmsg = MRP_SND_JOIN;
#else
			sndmsg = MRP_SND_NEW;
#endif
			mrp_state = MRP_AN_STATE;
			break;
		case MRP_AN_STATE:
			/* send NEW */
			tx = 1;
			sndmsg = MRP_SND_NEW;
			mrp_state = MRP_QA_STATE;
			break;
		case MRP_QP_STATE:
		case MRP_AP_STATE:
		case MRP_AA_STATE:
			/* send JOIN */
			tx = 1;
			sndmsg = MRP_SND_JOIN;
			mrp_state = MRP_QA_STATE;
			break;
		case MRP_QA_STATE:
			/* send JOIN */
			tx = 1;
			sndmsg = MRP_SND_JOIN;
			break;
		case MRP_LA_STATE:
		case MRP_AO_STATE:
		case MRP_QO_STATE:
			/* send <NULL> only if it improves encoding */
			optional = 1;
			tx = 1;
			sndmsg = MRP_SND_IN;
			mrp_state = MRP_LO_STATE;
			break;
		case MRP_LO_STATE:
			/* send <NULL> */
			optional = 1;
			tx = 1;
			sndmsg = MRP_SND_IN;
#ifndef MICREL_1588_PTP
			mrp_state = MRP_VO_STATE;
#endif
			break;
		default:
			break;
		}
		break;
	case MRP_EVENT_TXLAF:
#ifdef MICREL_1588_PTP
		/* Do not change state if already sent. */
		if (MRP_SND_NULL == attrib->sndmsg)
			break;
#endif
		/*
		 * transmit leaveall failure (no room)
		 */
		switch (mrp_state) {
		case MRP_VO_STATE:
			mrp_state = MRP_LO_STATE;
			break;
		case MRP_LO_STATE:
		case MRP_VP_STATE:
		case MRP_VN_STATE:
			/* don't advance state */
			break;
		case MRP_AN_STATE:
			mrp_state = MRP_VN_STATE;
			break;
		case MRP_QP_STATE:
		case MRP_AP_STATE:
		case MRP_AA_STATE:
		case MRP_QA_STATE:
			mrp_state = MRP_VP_STATE;
			break;
		case MRP_QO_STATE:
		case MRP_AO_STATE:
		case MRP_LA_STATE:
			mrp_state = MRP_LO_STATE;
			break;
		default:
			break;
		}
		break;
	case MRP_EVENT_TX:
		/*
		 * transmit updates unless leaveall is signaled
		 * (then it becomes a TXLA)
		 */
		switch (mrp_state) {
		case MRP_VO_STATE:
			/* send <NULL> only if it improves encoding */
			tx = 1;
			optional = 1;
			sndmsg = MRP_SND_IN;
			break;
		case MRP_VP_STATE:
			/* send JOIN */
			tx = 1;
			sndmsg = MRP_SND_JOIN;
			mrp_state = MRP_AA_STATE;
			break;
		case MRP_VN_STATE:
			/* send NEW */
			tx = 1;
			sndmsg = MRP_SND_NEW;
			mrp_state = MRP_AN_STATE;
			break;
		case MRP_AN_STATE:
			/* send NEW */
			tx = 1;
			sndmsg = MRP_SND_NEW;
			mrp_state = MRP_QA_STATE;
#ifdef MICREL_1588_PTP
			if (MRP_IN_STATE != mrp_db->registrar_state)
				mrp_state = MRP_AA_STATE;
if (ofp)
fprintf(ofp, "tx %p an -> qa; %d -> %d\n", attrib,
attrib->sndmsg, sndmsg);
#endif
			break;
		case MRP_AP_STATE:
		case MRP_AA_STATE:
			/* send JOIN */
			tx = 1;
			sndmsg = MRP_SND_JOIN;
			mrp_state = MRP_QA_STATE;
			break;
		case MRP_QA_STATE:
			/* send JOIN only if it improves encoding */
			tx = 1;
			optional = 1;
			sndmsg = MRP_SND_JOIN;
			break;
		case MRP_LA_STATE:
			/* send LV */
			tx = 1;
			sndmsg = MRP_SND_LV;
			mrp_state = MRP_VO_STATE;
			break;
		case MRP_AO_STATE:
		case MRP_QO_STATE:
		case MRP_QP_STATE:
			/* send <NULL> only if it improves encoding */
			tx = 1;
			optional = 1;
			sndmsg = MRP_SND_IN;
			break;
		case MRP_LO_STATE:
			/* send <NULL> */
			tx = 1;
			sndmsg = MRP_SND_IN;
			mrp_state = MRP_VO_STATE;
			break;
		default:
			break;
		}
		break;
	case MRP_EVENT_RNEW:
		/* do nothing */
		break;

	case MRP_EVENT_RJOININ:
		switch (mrp_state) {
		case MRP_VO_STATE:
			if (0 == p2pmac)
				mrp_state = MRP_AO_STATE;
			break;
		case MRP_VP_STATE:
			if (0 == p2pmac) {
				mrp_state = MRP_AP_STATE;
			}
			break;
		case MRP_AA_STATE:
			mrp_state = MRP_QA_STATE;
			break;
		case MRP_AO_STATE:
			mrp_state = MRP_QO_STATE;
			break;
		case MRP_AP_STATE:
			mrp_state = MRP_QP_STATE;
			break;
		default:
			break;
		}
		break;
	case MRP_EVENT_RIN:
		switch (mrp_state) {
		case MRP_AA_STATE:
			if (1 == p2pmac)
				mrp_state = MRP_QA_STATE;
			break;
		default:
			break;
		}
		break;
	case MRP_EVENT_RJOINMT:
	case MRP_EVENT_RMT:
		switch (mrp_state) {
		case MRP_QA_STATE:
			mrp_state = MRP_AA_STATE;
			break;
		case MRP_QO_STATE:
			mrp_state = MRP_AO_STATE;
			break;
		case MRP_QP_STATE:
			mrp_state = MRP_AP_STATE;
			break;
		case MRP_LO_STATE:
			mrp_state = MRP_VO_STATE;
			break;
		default:
			break;
		}
		break;

	case MRP_EVENT_RLV:
	case MRP_EVENT_RLA:
	case MRP_EVENT_REDECLARE:
		switch (mrp_state) {
		case MRP_VO_STATE:
			mrp_state = MRP_LO_STATE;
			break;
		case MRP_AN_STATE:
			mrp_state = MRP_VN_STATE;
			break;
		case MRP_QA_STATE:
		case MRP_AA_STATE:
			mrp_state = MRP_VP_STATE;
			break;
		case MRP_AO_STATE:
		case MRP_QO_STATE:
			mrp_state = MRP_LO_STATE;
			break;
		case MRP_AP_STATE:
		case MRP_QP_STATE:
			mrp_state = MRP_VP_STATE;
			break;
		default:
			break;
		}
		break;
	case MRP_EVENT_PERIODIC:
		switch (mrp_state) {
		case MRP_QA_STATE:
			mrp_state = MRP_AA_STATE;
			break;
		case MRP_QP_STATE:
			mrp_state = MRP_AP_STATE;
			break;
		default:
			break;
		}
		break;

	default:
#ifdef MICREL_1588_PTP
if (ofp)
fprintf(ofp, "! %s %p e:%d s:%d %s\n", __func__, attrib,
event, mrp_state, mrp_event_string(event));
#endif
		printf("mrp_applicant_fsm:unexpected event %s (%d)\n",
		       mrp_event_string(event), event);
		return -1;
		break;
	}
#ifdef MICREL_1588_PTP
	if (event != MRP_EVENT_PERIODIC) {
if (ofp)
fprintf(ofp, "%s %p s:%d -> %d; m:%d -> %d; t:%d -> %d=%d\n", __func__, attrib,
attrib->mrp_state, mrp_state,
attrib->sndmsg, sndmsg,
attrib->tx, tx, optional);
if (ofp)
fprintf(ofp, "mrp_applicant event %s, state %s -> %s\n",
				mrp_event_string(event),
				mrp_state_string(attrib->mrp_state),
				mrp_state_string(mrp_state));
	}
#endif

	attrib->tx = tx;

#if LOG_MVRP || LOG_MSRP || LOG_MMRP
	if (attrib->mrp_state != mrp_state) {
		mrpd_log_printf("mrp_applicant_fsm event %s, state %s -> %s\n",
				mrp_event_string(event),
				mrp_state_string(attrib->mrp_state),
				mrp_state_string(mrp_state));
	} else {
		mrpd_log_printf("mrp_applicant_fsm event %s, state %s\n",
				mrp_event_string(event),
				mrp_state_string(mrp_state));
	}
#endif
#ifdef MICREL_1588_PTP
	/* Need to send attribute in state changes to following: */
	mrp_db->registrar_state = MRP_MT_STATE;
	if (attrib->mrp_state != mrp_state) {
		switch (mrp_state) {
		case MRP_VN_STATE:
		case MRP_AN_STATE:
		case MRP_AA_STATE:
		case MRP_LA_STATE:
		case MRP_VP_STATE:
		case MRP_AP_STATE:
		case MRP_LO_STATE:
			rc = 1;
			break;
		case MRP_VO_STATE:

			/* Attribute is not being sent. */
			if (!tx) {
				if (!attrib->aging)
					attrib->aging = 3;
			}
			break;
		default:
			break;
		}
		mrp_db->registrar_state = MRP_IN_STATE;
	}
#endif

#ifdef MICREL_1588_PTP
	/* Update state after attribute is sent. */
	attrib->new_state = mrp_state;
	if (!tx)
#endif
	attrib->mrp_state = mrp_state;
	attrib->sndmsg = sndmsg;
	attrib->encode = (optional ? MRP_ENCODE_OPTIONAL : MRP_ENCODE_YES);
#ifdef MICREL_1588_PTP
	return rc;
#else
	return 0;
#endif
}

int
mrp_registrar_fsm(mrp_registrar_attribute_t * attrib,
		  struct mrp_database *mrp_db, int event)
{
	int mrp_state = attrib->mrp_state;
	int notify = MRP_NOTIFY_NONE;

	switch (event) {
	case MRP_EVENT_BEGIN:
		mrp_state = MRP_MT_STATE;
		break;
	case MRP_EVENT_RLV:
#ifndef MICREL_1588_PTP
		notify = MRP_NOTIFY_LV;
#endif
#ifdef MICREL_1588_PTP
if (ofp)
fprintf(ofp, "rx LV: %s\n", mrp_state_string(attrib->mrp_state));
#endif
		/* fall thru */
	case MRP_EVENT_TXLA:
	case MRP_EVENT_RLA:
	case MRP_EVENT_REDECLARE:
		/*
		 * on link-status-change
		 * trigger Applicant and Registrar state machines to re-declare
		 * previously registered attributes.
		 */
		switch (mrp_state) {
		case MRP_IN_STATE:
			mrp_lvtimer_start(mrp_db);
			mrp_state = MRP_LV_STATE;
#ifdef MICREL_1588_PTP
if (ofp)
fprintf(ofp, "  lvtimer starts to lv: %s\n", mrp_event_string(event));
#endif
		default:
			break;
		}
		break;
	case MRP_EVENT_RNEW:
		notify = MRP_NOTIFY_NEW;
		switch (mrp_state) {
		case MRP_MT_STATE:
		case MRP_IN_STATE:
			mrp_state = MRP_IN_STATE;
			break;
		case MRP_LV_STATE:
			/* should stop leavetimer - but we have only 1 lvtimer
			 * for all attributes, and recieving a LVTIMER event
			 * is a don't-care if the attribute is in the IN state.
			 */
			mrp_state = MRP_IN_STATE;
			break;
		default:
			break;
		}
#ifdef MICREL_1588_PTP
if (ofp)
fprintf(ofp, "  rnew: %d\n", mrp_state);
#endif
		break;
	case MRP_EVENT_RJOININ:
	case MRP_EVENT_RJOINMT:
		switch (mrp_state) {
		case MRP_MT_STATE:
			notify = MRP_NOTIFY_JOIN;
			mrp_state = MRP_IN_STATE;
			break;
		case MRP_IN_STATE:
			mrp_state = MRP_IN_STATE;
			break;
		case MRP_LV_STATE:
			/* should stop leavetimer - but we have only 1 lvtimer
			 * for all attributes, and receiving a LVTIMER event
			 * is a don't-care if the attribute is in the IN state.
			 */
#ifndef MICREL_1588_PTP
			notify = MRP_NOTIFY_JOIN;
#endif
			mrp_state = MRP_IN_STATE;
			break;
		default:
			break;
		}
#ifdef MICREL_1588_PTP
if (ofp)
fprintf(ofp, "  rjoin: %d\n", mrp_state);
#endif
		break;

	case MRP_EVENT_LVTIMER:
		switch (mrp_state) {
		case MRP_LV_STATE:
#ifdef MICREL_1588_PTP
			notify = MRP_NOTIFY_LV;
#endif
			mrp_state = MRP_MT_STATE;
			break;
		case MRP_MT_STATE:
			mrp_state = MRP_MT_STATE;
			break;
		case MRP_IN_STATE:
		default:
			break;
		}
#ifdef MICREL_1588_PTP
if (ofp)
fprintf(ofp, " lvtimer %s -> %s\n", mrp_state_string(attrib->mrp_state), mrp_state_string(mrp_state));
#endif
		break;
	case MRP_EVENT_FLUSH:
#ifndef MICREL_1588_PTP
		notify = MRP_NOTIFY_LV;
#endif
		switch (mrp_state) {
		case MRP_LV_STATE:
#ifdef MICREL_1588_PTP
			notify = MRP_NOTIFY_LV;
#endif
			mrp_state = MRP_MT_STATE;
			break;
		case MRP_MT_STATE:
		case MRP_IN_STATE:
			mrp_state = MRP_MT_STATE;
			break;
		default:
			break;
		}
		break;
	case MRP_EVENT_RIN:
		break;
	case MRP_EVENT_RMT:
		/* ignore on soon to be deleted attributes */
		break;
	default:
#ifdef MICREL_1588_PTP
if (ofp)
fprintf(ofp, "! %s %p e:%d s:%d %s\n", __func__, attrib,
event, mrp_state, mrp_event_string(event));
#endif
		printf("mrp_registrar_fsm:unexpected event %s (%d), state %s\n",
		       mrp_event_string(event), event,
		       mrp_state_string(mrp_state));
		return -1;
		break;
	}
#if LOG_MVRP || LOG_MSRP || LOG_MMRP
	if (attrib->mrp_state != mrp_state) {
		mrpd_log_printf("mrp_registrar_fsm event %s, state %s -> %s\n",
				mrp_event_string(event),
				mrp_state_string(attrib->mrp_state),
				mrp_state_string(mrp_state));

	} else {
		mrpd_log_printf("mrp_registrar_fsm event %s, state %s\n",
				mrp_event_string(event),
				mrp_state_string(mrp_state));
	}
#endif
#ifdef MICREL_1588_PTP
if (ofp)
fprintf(ofp, "  %s %p %d -> %d; %d -> %d\n", __func__, attrib,
attrib->mrp_state, mrp_state,
attrib->notify, notify);
if (ofp)
fprintf(ofp, "  mrp_registrar event %s, state %s -> %s\n",
				mrp_event_string(event),
				mrp_state_string(attrib->mrp_state),
				mrp_state_string(mrp_state));
#endif
	attrib->mrp_state = mrp_state;
	attrib->notify = notify;
	return 0;
}

int mrp_decode_state(mrp_registrar_attribute_t * rattrib,
		     mrp_applicant_attribute_t * aattrib, char *str, int strlen)
{
	char reg_stat[8];

	switch (rattrib->mrp_state) {
	case MRP_IN_STATE:
		snprintf(reg_stat, sizeof(reg_stat) - 1, "IN");
		break;
	case MRP_LV_STATE:
		snprintf(reg_stat, sizeof(reg_stat) - 1, "LV");
		break;
	case MRP_MT_STATE:
		snprintf(reg_stat, sizeof(reg_stat) - 1, "MT");
		break;
	default:
#ifdef MICREL_1588_PTP
if (ofp)
fprintf(ofp, "  ?? %x\n", rattrib->mrp_state);
#endif
		snprintf(reg_stat, sizeof(reg_stat) - 1, "%d",
			 rattrib->mrp_state);
		break;
	}

	switch (aattrib->mrp_state) {
	case MRP_VO_STATE:
		snprintf(str, strlen - 1, "VO/%s", reg_stat);
		break;
	case MRP_VP_STATE:
		snprintf(str, strlen - 1, "VP/%s", reg_stat);
		break;
	case MRP_VN_STATE:
		snprintf(str, strlen - 1, "VN/%s", reg_stat);
		break;
	case MRP_AN_STATE:
		snprintf(str, strlen - 1, "AN/%s", reg_stat);
		break;
	case MRP_AA_STATE:
		snprintf(str, strlen - 1, "AA/%s", reg_stat);
		break;
	case MRP_QA_STATE:
		snprintf(str, strlen - 1, "QA/%s", reg_stat);
		break;
	case MRP_LA_STATE:
		snprintf(str, strlen - 1, "LA/%s", reg_stat);
		break;
	case MRP_AO_STATE:
		snprintf(str, strlen - 1, "AO/%s", reg_stat);
		break;
	case MRP_QO_STATE:
		snprintf(str, strlen - 1, "QO/%s", reg_stat);
		break;
	case MRP_AP_STATE:
		snprintf(str, strlen - 1, "AP/%s", reg_stat);
		break;
	case MRP_QP_STATE:
		snprintf(str, strlen - 1, "QP/%s", reg_stat);
		break;
	case MRP_LO_STATE:
		snprintf(str, strlen - 1, "LO/%s", reg_stat);
		break;
	default:
#ifdef MICREL_1588_PTP
if (ofp)
fprintf(ofp, "  ??? %x\n", aattrib->mrp_state);
#endif
		snprintf(str, strlen - 1, "%d/%s", aattrib->mrp_state,
			 reg_stat);
		break;
	}
	return 0;
}

int mrp_init(void)
{
	p2pmac = MRP_DEFAULT_POINT_TO_POINT_MAC;	/* operPointToPointMAC */
	lva_next = MRP_LVATIMER_VAL;	/* leaveall timeout in msec */

	return 0;
}
