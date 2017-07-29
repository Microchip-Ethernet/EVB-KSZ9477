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
 * MSRP protocol (part of 802.1Q-2011)
 */

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#ifdef MICREL_1588_PTP_
#include <time.h>
extern time_t start_time;
#endif

#include "parse.h"
#include "mrpd.h"
#include "mrp.h"
#include "msrp.h"
#include "mmrp.h"

int msrp_txpdu(void);
int msrp_send_notifications(struct msrp_attribute *attrib, int notify);

#ifdef MICREL_1588_PTP_DEV
unsigned char MSRP_ADDR[] = { 0x01, 0x00, 0xC2, 0x00, 0x00, 0x0E };
#else
unsigned char MSRP_ADDR[] = { 0x01, 0x80, 0xC2, 0x00, 0x00, 0x0E };
#endif

extern unsigned char STATION_ADDR[];

/* global variables */
SOCKET msrp_socket;
struct msrp_database *MSRP_db;
#ifdef MICREL_1588_PTP
SOCKET msrp_sockets[8];
struct msrp_database *MSRP_dbs[8];
static time_t last_event_time;
struct msrp_attribute domain_attrib;
struct msrp_attribute listener_attrib;
struct msrp_attribute talker_attrib;
#endif

static char *msrp_attrib_type_string(int t)
{
	switch (t) {
	case MSRP_TALKER_ADV_TYPE:
		return "Talker Advertise";
	case MSRP_TALKER_FAILED_TYPE:
		return "Talker Failed";
	case MSRP_LISTENER_TYPE:
		return "Listener";
	case MSRP_DOMAIN_TYPE:
		return "Domain";
	default:
		return "TYPE ???";
	}
}

struct msrp_attribute *msrp_lookup(struct msrp_attribute *rattrib)
{
	struct msrp_attribute *attrib;
	int mac_eq;

	attrib = MSRP_db->attrib_list;
	while (NULL != attrib) {
		if (rattrib->type == attrib->type) {
			if (MSRP_DOMAIN_TYPE == attrib->type) {
				mac_eq = memcmp(&(attrib->attribute.domain),
						&(rattrib->attribute.domain),
						sizeof(msrpdu_domain_t));
				if (0 == mac_eq)
					return attrib;
			} else {
				/* compare on the stream ID */
				mac_eq =
				    memcmp(attrib->attribute.talk_listen.
					   StreamID,
					   rattrib->attribute.talk_listen.
					   StreamID, 8);
				if (0 == mac_eq)
					return attrib;
			}
		}
		attrib = attrib->next;
	}
	return NULL;
}

int msrp_add(struct msrp_attribute *rattrib)
{
	struct msrp_attribute *attrib;
	struct msrp_attribute *attrib_tail;
	int mac_eq;

	/* XXX do a lookup first to guarantee uniqueness? */

	attrib_tail = attrib = MSRP_db->attrib_list;

	while (NULL != attrib) {
		/* sort list into types, then sorted in order within types */
		if (rattrib->type == attrib->type) {
			if (MSRP_DOMAIN_TYPE == attrib->type) {
				mac_eq = memcmp(&(attrib->attribute.domain),
						&(rattrib->attribute.domain),
						sizeof(msrpdu_domain_t));

				if (mac_eq < 0) {
					/* possible tail insertion ... */

					/*
					 * see if there is a another of the same following
					 * not likely since valid values are only 0 and 1
					 */
					if (NULL != attrib->next) {
						if (attrib->type ==
						    attrib->next->type) {
							attrib = attrib->next;
							continue;
						}
					}

					rattrib->next = attrib->next;
					rattrib->prev = attrib;
					attrib->next = rattrib;
					return 0;

				} else {
					/* head insertion ... */
					rattrib->next = attrib;
					rattrib->prev = attrib->prev;
					attrib->prev = rattrib;
					if (NULL != rattrib->prev)
						rattrib->prev->next = rattrib;
					else
						MSRP_db->attrib_list = rattrib;

					return 0;
				}
			} else {
				mac_eq =
				    memcmp(attrib->attribute.talk_listen.
					   StreamID,
					   rattrib->attribute.talk_listen.
					   StreamID, 8);

				if (mac_eq < 0) {
					/* possible tail insertion ... */

					if (NULL != attrib->next) {
						if (attrib->type ==
						    attrib->next->type) {
							attrib = attrib->next;
							continue;
						}
					}

					rattrib->next = attrib->next;
					rattrib->prev = attrib;
					attrib->next = rattrib;
					return 0;

				} else {
					/* head insertion ... */
					rattrib->next = attrib;
					rattrib->prev = attrib->prev;
					attrib->prev = rattrib;
					if (NULL != rattrib->prev)
						rattrib->prev->next = rattrib;
					else
						MSRP_db->attrib_list = rattrib;

					return 0;
				}
			}
		}
		attrib_tail = attrib;
		attrib = attrib->next;
	}

	/* if we are here we didn't need to stitch in a a sorted entry
	 * so append it onto the tail (if it exists)
	 */

	if (NULL == attrib_tail) {
		rattrib->next = NULL;
		rattrib->prev = NULL;
		MSRP_db->attrib_list = rattrib;
	} else {
		rattrib->next = NULL;
		rattrib->prev = attrib_tail;
		attrib_tail->next = rattrib;
	}

	return 0;
}

int msrp_merge(struct msrp_attribute *rattrib)
{
	struct msrp_attribute *attrib;

	attrib = msrp_lookup(rattrib);

	if (NULL == attrib)
		return -1;	/* shouldn't happen */

	/* we always update the last mac address state for diagnostics */
#ifdef MICREL_1588_PTP
	if (rattrib->registrar.macaddr[0] ||
	    rattrib->registrar.macaddr[1] ||
	    rattrib->registrar.macaddr[2])
#endif
	memcpy(attrib->registrar.macaddr, rattrib->registrar.macaddr, 6);

	/* some attribute types carry updated fault condition information
	 * from the bridges indicating either insufficient bandwidth or
	 * excessive latency between the talker and listener. We merge
	 * these status conditions with the existing attribute without
	 * necessarily changing the MRP state (we let the FSM functions
	 * handle these)
	 */
	switch (attrib->type) {
	case MSRP_TALKER_ADV_TYPE:
	case MSRP_TALKER_FAILED_TYPE:
		attrib->attribute.talk_listen.FailureInformation.FailureCode =
		    rattrib->attribute.talk_listen.FailureInformation.
		    FailureCode;
		memcpy(attrib->attribute.talk_listen.FailureInformation.
		       BridgeID,
		       rattrib->attribute.talk_listen.FailureInformation.
		       BridgeID, 8);
#ifdef ENABLE_MERGED_LATENCY
		attrib->attribute.talk_listen.AccumulatedLatency =
		    rattrib->attribute.talk_listen.AccumulatedLatency;
#endif
		break;
	case MSRP_LISTENER_TYPE:
		if (attrib->substate != rattrib->substate) {
			attrib->substate = rattrib->substate;
#ifndef MICREL_1588_PTP
			attrib->registrar.mrp_state = MRP_MT_STATE;	/* ugly - force a notify */
#endif
		}
		break;
	case MSRP_DOMAIN_TYPE:
		/* doesn't/shouldn't happen */
		break;
	default:
		break;
	}
	return 0;
}

int msrp_event(int event, struct msrp_attribute *rattrib)
{
	struct msrp_attribute *attrib;
	int rc;
#ifdef MICREL_1588_PTP
	int next_event;
	int tx_op = 0;
	time_t ticks = time(NULL);

if (event != MRP_EVENT_LVATIMER && event != MRP_EVENT_TX &&
event != MRP_EVENT_PERIODIC)
if (ofp) {
if (rattrib && rattrib->type != MSRP_DOMAIN_TYPE)
fprintf(ofp, "=%02X  ", rattrib->attribute.talk_listen.StreamID[7]);
fprintf(ofp, "%s %d %s %ld %ld\n", __func__, event, mrp_event_string(event),
ticks - start_time, ticks - last_event_time);
}
#endif
	switch (event) {
	case MRP_EVENT_LVATIMER:
/* Attributes are not actually sent in this event. */
#ifndef MICREL_1588_PTP
		mrp_lvatimer_stop(&(MSRP_db->mrp_db));
		mrp_jointimer_stop(&(MSRP_db->mrp_db));
		/* update state */
		attrib = MSRP_db->attrib_list;

		while (NULL != attrib) {
#if LOG_MSRP
			mrpd_log_printf("MSRP -> mrp_applicant_fsm\n");
#endif
			mrp_applicant_fsm(&(MSRP_db->mrp_db),
					  &(attrib->applicant), MRP_EVENT_TXLA);
			mrp_registrar_fsm(&(attrib->registrar),
					  &(MSRP_db->mrp_db), MRP_EVENT_TXLA);
			attrib = attrib->next;
		}
#endif

#ifdef MICREL_1588_PTP
		tx_op =
#endif
		mrp_lvatimer_fsm(&(MSRP_db->mrp_db), MRP_EVENT_LVATIMER);

/*
 * Attributes are not actually sent in this event.  Wait for next transmit
 * opportunity.
 */
#ifndef MICREL_1588_PTP
		msrp_txpdu();
#endif
		break;
	case MRP_EVENT_RLA:
/* Attributes are not necessarily needed to be sent in this event. */
#ifndef MICREL_1588_PTP
		mrp_jointimer_start(&(MSRP_db->mrp_db));
#endif
		/* update state */
		attrib = MSRP_db->attrib_list;

		while (NULL != attrib) {
			if (rattrib && rattrib->type != attrib->type) {
				attrib = attrib->next;
				continue;
			}
#if LOG_MSRP
			mrpd_log_printf("MSRP -> mrp_applicant_fsm\n");
#endif
#ifdef MICREL_1588_PTP
			tx_op |=
#endif
			mrp_applicant_fsm(&(MSRP_db->mrp_db),
					  &(attrib->applicant), MRP_EVENT_RLA);
			mrp_registrar_fsm(&(attrib->registrar),
					  &(MSRP_db->mrp_db), MRP_EVENT_RLA);
			attrib = attrib->next;
		}

		mrp_lvatimer_fsm(&(MSRP_db->mrp_db), MRP_EVENT_RLA);

		break;
	case MRP_EVENT_TX:
		mrp_jointimer_stop(&(MSRP_db->mrp_db));
#ifdef MICREL_1588_PTP
		/*
		 * Do this first so that tx! becomes txLA! if LeaveAll is
		 * indicated.
		 */
		mrp_lvatimer_fsm(&(MSRP_db->mrp_db), MRP_EVENT_TX);
		if (MRP_SND_LVA == MSRP_db->mrp_db.lva.sndmsg)
			MSRP_db->mrp_db.lva.tx = 0xf;

		attrib = MSRP_db->attrib_list;

		while (NULL != attrib) {
#if LOG_MSRP
			mrpd_log_printf("MSRP -> mrp_applicant_fsm\n");
#endif
			next_event = 3;
			if (MSRP_LISTENER_TYPE == attrib->type)
				next_event = 4;
			else if (MSRP_DOMAIN_TYPE == attrib->type)
				next_event = 8;
			if (MSRP_db->mrp_db.lva.tx & next_event) {
				tx_op |=
				mrp_applicant_fsm(&(MSRP_db->mrp_db),
					&(attrib->applicant), MRP_EVENT_TXLA);
				mrp_registrar_fsm(&(attrib->registrar),
					&(MSRP_db->mrp_db), MRP_EVENT_TXLA);
			} else {
				MSRP_db->mrp_db.registrar_state =
					attrib->registrar.mrp_state;
				tx_op |=
				mrp_applicant_fsm(&(MSRP_db->mrp_db),
					&(attrib->applicant), MRP_EVENT_TX);
			}
			attrib = attrib->next;
		}
#else
		attrib = MSRP_db->attrib_list;

		while (NULL != attrib) {
#if LOG_MSRP
			mrpd_log_printf("MSRP -> mrp_applicant_fsm\n");
#endif
			mrp_applicant_fsm(&(MSRP_db->mrp_db),
					  &(attrib->applicant), MRP_EVENT_TX);
			attrib = attrib->next;
		}

		mrp_lvatimer_fsm(&(MSRP_db->mrp_db), MRP_EVENT_TX);
#endif

#ifdef MICREL_1588_PTP
		rc =
#endif
		msrp_txpdu();
#ifdef MICREL_1588_PTP
		next_event = 0;

		/* Not all attributes sent. */
		if (rc) {
			if (MRP_SND_LVA == MSRP_db->mrp_db.lva.sndmsg)
				next_event = MRP_EVENT_TXLAF;
			else
				/* Send rest in next tx!. */
				tx_op |= 2;
		} else if (MRP_SND_LVA == MSRP_db->mrp_db.lva.sndmsg) {
			next_event = MRP_EVENT_RLA;
			mrp_lvatimer_fsm(&(MSRP_db->mrp_db), MRP_EVENT_RLA);
		}
		if (next_event) {
			attrib = MSRP_db->attrib_list;
			while (NULL != attrib) {
				tx_op |=
				mrp_applicant_fsm(&(MSRP_db->mrp_db),
					&(attrib->applicant), next_event);
				mrp_registrar_fsm(&(attrib->registrar),
					&(MSRP_db->mrp_db), next_event);
				attrib = attrib->next;
			}
		}
#endif
		break;
	case MRP_EVENT_LVTIMER:
		mrp_lvtimer_stop(&(MSRP_db->mrp_db));
		attrib = MSRP_db->attrib_list;

		while (NULL != attrib) {
			mrp_registrar_fsm(&(attrib->registrar),
					  &(MSRP_db->mrp_db),
					  MRP_EVENT_LVTIMER);

			attrib = attrib->next;
		}
		break;
	case MRP_EVENT_PERIODIC:
/* MSRP does not process this event */
#ifndef MICREL_1588_PTP
		attrib = MSRP_db->attrib_list;

		while (NULL != attrib) {
#if LOG_MSRP
			mrpd_log_printf("MSRP -> mrp_applicant_fsm\n");
#endif
#ifdef MICREL_1588_PTP
			tx_op |=
#endif
			mrp_applicant_fsm(&(MSRP_db->mrp_db),
					  &(attrib->applicant),
					  MRP_EVENT_PERIODIC);
			attrib = attrib->next;
		}
#endif
		break;
	case MRP_EVENT_NEW:
	case MRP_EVENT_JOIN:
	case MRP_EVENT_RNEW:
	case MRP_EVENT_RJOININ:
	case MRP_EVENT_RJOINMT:
	case MRP_EVENT_LV:
	case MRP_EVENT_RIN:
	case MRP_EVENT_RMT:
	case MRP_EVENT_RLV:
/* Attributes are not necessarily needed to be sent in this event. */
#ifndef MICREL_1588_PTP
		mrp_jointimer_start(&(MSRP_db->mrp_db));
#endif
		if (NULL == rattrib)
			return -1;	/* XXX internal fault */

		/* update state */
		attrib = msrp_lookup(rattrib);

		if (NULL == attrib) {
#ifdef MICREL_1588_PTP
			/* Do not want to create empty attribute. */
			if (MRP_EVENT_RMT == event) {
				free(rattrib);
				break;
			}
#endif
			msrp_add(rattrib);
			attrib = rattrib;
		} else {
#ifdef MICREL_1588_PTP
			if (MSRP_LISTENER_TYPE == rattrib->type &&
			    MRP_EVENT_LV == event)
				rattrib->substate = attrib->substate;
#endif
			msrp_merge(rattrib);
			free(rattrib);
		}

#ifdef MICREL_1588_PTP
		tx_op =
#endif
		mrp_applicant_fsm(&(MSRP_db->mrp_db), &(attrib->applicant),
				  event);

		/* remap local requests into registrar events */
		switch (event) {
		case MRP_EVENT_NEW:
#ifndef MICREL_1588_PTP
			mrp_registrar_fsm(&(attrib->registrar),
					  &(MSRP_db->mrp_db), MRP_EVENT_RNEW);
#endif
			break;
		case MRP_EVENT_JOIN:
#ifndef MICREL_1588_PTP
			if (MRP_IN_STATE == attrib->registrar.mrp_state)
				mrp_registrar_fsm(&(attrib->registrar),
						  &(MSRP_db->mrp_db),
						  MRP_EVENT_RJOININ);
			else
				mrp_registrar_fsm(&(attrib->registrar),
						  &(MSRP_db->mrp_db),
						  MRP_EVENT_RJOINMT);
#endif
			break;
		case MRP_EVENT_LV:
#ifndef MICREL_1588_PTP
			mrp_registrar_fsm(&(attrib->registrar),
					  &(MSRP_db->mrp_db), MRP_EVENT_RLV);
#endif
			break;
		default:
			rc = mrp_registrar_fsm(&(attrib->registrar),
					       &(MSRP_db->mrp_db), event);
			if (-1 == rc) {
				printf
				    ("MSRP registrar error on attrib->type = %s (%d)\n",
				     msrp_attrib_type_string(attrib->type),
				     attrib->type);
			}
			break;
		}
		break;
	default:
		break;
	}
#ifdef MICREL_1588_PTP
	/* Send attributes in next transmit opportunity. */
	if (tx_op) {
		mrp_jointimer_start(&(MSRP_db->mrp_db));

		/* Not continuing previous tx!. */
		if (!(tx_op & 2))
			MSRP_db->mrp_db.tx_attrib = NULL;
	}
	last_event_time = ticks;
#endif

	/*
	 * XXX should honor the MSRP_db->mrp_db.registration and
	 * MSRP_db->mrp_db.participant controls
	 */

	/* generate local notifications */
	attrib = MSRP_db->attrib_list;

	while (NULL != attrib) {
		if (MRP_NOTIFY_NONE != attrib->registrar.notify) {
			msrp_send_notifications(attrib,
						attrib->registrar.notify);
			attrib->registrar.notify = MRP_NOTIFY_NONE;
		}
		attrib = attrib->next;
	}

	return 0;
}

struct msrp_attribute *msrp_alloc()
{
	struct msrp_attribute *attrib;

	attrib = malloc(sizeof(struct msrp_attribute));
	if (NULL == attrib)
		return NULL;

	memset(attrib, 0, sizeof(struct msrp_attribute));

#ifdef MICREL_1588_PTP
	attrib->applicant.new_state = MRP_VO_STATE;
#endif
	attrib->applicant.mrp_state = MRP_VO_STATE;
	attrib->applicant.tx = 0;
	attrib->applicant.sndmsg = MRP_SND_NULL;
	attrib->applicant.encode = MRP_ENCODE_OPTIONAL;

	attrib->registrar.mrp_state = MRP_MT_STATE;
	attrib->registrar.notify = MRP_NOTIFY_NONE;

	return attrib;
}

void msrp_increment_streamid(uint8_t * streamid)
{

	int i;

	i = 7;
	while (i > 0) {
		if (255 != streamid[i]) {
			streamid[i]++;
			return;
		}
		streamid[i] = 0;
		i--;
	}
	return;
}

int msrp_recv_msg()
{
	char *msgbuf;
	int bytes = 0;
	eth_hdr_t *eth;
	mrpdu_t *mrpdu;
	mrpdu_message_t *mrpdu_msg;
	unsigned char *mrpdu_msg_ptr;
	unsigned char *mrpdu_msg_eof;
	mrpdu_vectorattrib_t *mrpdu_vectorptr;
	uint16_t numvalues;
	uint16_t numvalues_processed;
	int numvectorbytes;
	uint8_t vect_3pack;
	uint8_t vect_4pack;
	int vectidx;
	int vectevt[4];
	int vectevt_idx;
	uint8_t srclassID_firstval;
	uint8_t srclassprio_firstval;
	uint16_t srclassvid_firstval;
	uint8_t streamid_firstval[8];
	uint8_t destmac_firstval[6];
	struct msrp_attribute *attrib;
	int endmarks;
	int *listener_vectevt = NULL;
	int listener_vectevt_sz = 0;
	int listener_vectevt_idx;
	int listener_endbyte;
#ifdef MICREL_1588_PTP
	uint16_t VectorHeader;
	uint8_t *unaligned;
#if 0
	int rLA = 0;
#endif
	int rLA_domain = 0;
	int rLA_listener = 0;
	int rLA_talker = 0;
	time_t ticks = time(NULL);

if (ofp)
fprintf(ofp, " > %ld %ld\n",
ticks - start_time, ticks - last_event_time);
#endif

	bytes = mrpd_recvmsgbuf(msrp_socket, &msgbuf);
	if (bytes <= 0)
		goto out;
	if ((unsigned int)bytes < (sizeof(eth_hdr_t) + sizeof(mrpdu_t) +
				   sizeof(mrpdu_message_t)))
		goto out;

	eth = (eth_hdr_t *) msgbuf;

	/* note that MSRP frames should always arrive untagged (no vlan) */
	if (MSRP_ETYPE != ntohs(eth->typelen)) {
		goto out;
	}
	/* XXX check dest mac address too? */

	mrpdu = (mrpdu_t *) (msgbuf + sizeof(struct eth_hdr));

	/*
	 * ProtocolVersion handling - a receiver must process received frames with a lesser
	 * protocol version consistent with the older protocol processing requirements (e.g. a V2
	 * agent receives a V1 message, the V1 message should be parsed with V1 rules).
	 *
	 * However - if an agent receives a NEWER protocol, the agent should still attempt
	 * to parse the frame. If the agent finds an AttributeType not recognized
	 * the agent discards the current message including any associated trailing vectors
	 * up to the end-mark, and resumes with the next message or until the end of the PDU
	 * is reached.
	 *
	 * If a VectorAttribute is found with an unknown Event for the Type, the specific
	 * VectorAttrute is discarded and processing continues with the next VectorAttribute.
	 */

	if (MSRP_PROT_VER != mrpdu->ProtocolVersion) {	/* XXX should accept ... */
		goto out;
	}
	mrpdu_msg_ptr = MRPD_GET_MRPDU_MESSAGE_LIST(mrpdu);

	mrpdu_msg_eof = (unsigned char *)mrpdu_msg_ptr;
	mrpdu_msg_eof += bytes;
	mrpdu_msg_eof -= sizeof(eth_hdr_t);
	mrpdu_msg_eof -= MRPD_OFFSETOF_MRPD_GET_MRPDU_MESSAGE_LIST;

	endmarks = 0;

#if LOG_MSRP
	mrpd_log_printf("MSRP msrp_recv_msg() START\n");
#endif

	while (mrpdu_msg_ptr < (mrpdu_msg_eof - 2)) {
		mrpdu_msg = (mrpdu_message_t *) mrpdu_msg_ptr;
		if ((mrpdu_msg->AttributeType == 0) &&
		    (mrpdu_msg->AttributeLength == 0)) {
			mrpdu_msg_ptr += 2;
			endmarks++;
			if (endmarks < 2)
				continue;	/* end-mark of message-list */
			else {
				break;	/* two endmarks - end of message list */
			}
		}

		endmarks = 0;

#if LOG_MSRP
		mrpd_log_printf("MSRP msrp_recv_msg() msg addr 0x%X\n",
				((int)mrpdu_msg_ptr) & 0x3);
#endif

		switch (mrpdu_msg->AttributeType) {
		case MSRP_DOMAIN_TYPE:
			if (mrpdu_msg->AttributeLength != 4) {
				/* we can seek for an endmark to recover .. but this version
				 * dumps the entire packet as malformed
				 */
				goto out;
			}

			mrpdu_vectorptr =
			    (mrpdu_vectorattrib_t *) & (mrpdu_msg->Data[2]);
			mrpdu_msg_ptr = (uint8_t *) mrpdu_vectorptr;
			while (!((mrpdu_msg_ptr[0] == 0)
				 && (mrpdu_msg_ptr[1] == 0))) {
#ifdef MICREL_1588_PTP
				unaligned = (uint8_t *)
					&mrpdu_vectorptr->VectorHeader;
				VectorHeader = ((uint16_t) unaligned[0] << 8) |
					unaligned[1];
				numvalues =
				    MRPDU_VECT_NUMVALUES(VectorHeader);
#else
				numvalues =
				    MRPDU_VECT_NUMVALUES(ntohs
							 (mrpdu_vectorptr->
							  VectorHeader));
#endif

				if (0 == numvalues) {
					/* skip this null attribute ... some switches generate these ... */
					/* 2 byte numvalues + 4 byte FirstValue + (0) vector bytes */
					mrpdu_msg_ptr =
					    (uint8_t *) mrpdu_vectorptr;
					mrpdu_msg_ptr += 6;

					mrpdu_vectorptr =
					    (mrpdu_vectorattrib_t *)
					    mrpdu_msg_ptr;
					continue;
				}
				if ((mrpdu_vectorptr->FirstValue_VectorEvents +
				     numvalues / 3) >= mrpdu_msg_eof) {
					/* Malformed - runs off the end of the pdu */
					goto out;
				}
/* Generate rLA event at the very beginnning and only once. */
#ifdef MICREL_1588_PTP
				if (MRPDU_VECT_LVA(VectorHeader) && !rLA_domain) {
					msrp_event(MRP_EVENT_RLA, &domain_attrib);
					rLA_domain = 1;
				}
#endif
				srclassID_firstval =
				    mrpdu_vectorptr->FirstValue_VectorEvents[0];
				srclassprio_firstval =
				    mrpdu_vectorptr->FirstValue_VectorEvents[1];
				srclassvid_firstval = ((uint16_t)
						       mrpdu_vectorptr->
						       FirstValue_VectorEvents
						       [2]) << 8 |
				    mrpdu_vectorptr->FirstValue_VectorEvents[3];

				/* if not an even multiple ... */
				if (numvalues != ((numvalues / 3) * 3))
					numvectorbytes = (numvalues / 3) + 1;
				else
					numvectorbytes = (numvalues / 3);

				for (vectidx = 4;
				     vectidx <= (numvectorbytes + 4);
				     vectidx++) {
					vect_3pack =
					    mrpdu_vectorptr->
					    FirstValue_VectorEvents[vectidx];
					vectevt[0] = vect_3pack / 36;
					vectevt[1] =
					    (vect_3pack - vectevt[0] * 36) / 6;
					vectevt[2] =
					    vect_3pack - (36 * vectevt[0]) -
					    (6 * vectevt[1]);

					numvalues_processed =
					    (numvalues > 3 ? 3 : numvalues);

					for (vectevt_idx = 0;
					     vectevt_idx < numvalues_processed;
					     vectevt_idx++) {

						attrib = msrp_alloc();
						if (NULL == attrib)
							goto out;	/* oops - internal error */

						attrib->type = MSRP_DOMAIN_TYPE;
						attrib->attribute.domain.
						    SRclassID =
						    srclassID_firstval;
						attrib->attribute.domain.
						    SRclassPriority =
						    srclassprio_firstval;
						attrib->attribute.domain.
						    SRclassVID =
						    srclassvid_firstval;

						srclassID_firstval++;
						srclassprio_firstval++;

						memcpy(attrib->registrar.
						       macaddr, eth->srcaddr,
						       6);

						switch (vectevt[vectevt_idx]) {
						case MRPDU_NEW:
							msrp_event
							    (MRP_EVENT_RNEW,
							     attrib);
							break;
						case MRPDU_JOININ:
							msrp_event
							    (MRP_EVENT_RJOININ,
							     attrib);
							break;
						case MRPDU_IN:
							msrp_event
							    (MRP_EVENT_RIN,
							     attrib);
							break;
						case MRPDU_JOINMT:
							msrp_event
							    (MRP_EVENT_RJOINMT,
							     attrib);
							break;
						case MRPDU_MT:
							msrp_event
							    (MRP_EVENT_RMT,
							     attrib);
							break;
						case MRPDU_LV:
							msrp_event
							    (MRP_EVENT_RLV,
							     attrib);
							break;
						default:
							free(attrib);
							break;
						}
					}
					numvalues -= numvalues_processed;
				}

#ifndef MICREL_1588_PTP
				if (MRPDU_VECT_LVA
				    (ntohs(mrpdu_vectorptr->VectorHeader)))
					msrp_event(MRP_EVENT_RLA, NULL);
#endif

				/* 2 byte numvalues + 4 byte FirstValue + (n) vector bytes */
				mrpdu_msg_ptr = (uint8_t *) mrpdu_vectorptr;
				mrpdu_msg_ptr += 6 + numvectorbytes;

				mrpdu_vectorptr =
				    (mrpdu_vectorattrib_t *) mrpdu_msg_ptr;
			}
			break;
		case MSRP_LISTENER_TYPE:
			if (mrpdu_msg->AttributeLength != 8) {
				/* we can seek for an endmark to recover .. but this version
				 * dumps the entire packet as malformed
				 */
				goto out;
			}

			/* MSRP uses AttributeListLength ...  */
			mrpdu_vectorptr =
			    (mrpdu_vectorattrib_t *) & (mrpdu_msg->Data[2]);
			mrpdu_msg_ptr = (uint8_t *) mrpdu_vectorptr;

			while (!((mrpdu_msg_ptr[0] == 0)
				 && (mrpdu_msg_ptr[1] == 0))) {
#ifdef MICREL_1588_PTP
				unaligned = (uint8_t *)
					&mrpdu_vectorptr->VectorHeader;
				VectorHeader = ((uint16_t) unaligned[0] << 8) |
					unaligned[1];
				numvalues =
				    MRPDU_VECT_NUMVALUES(VectorHeader);
#else
				numvalues =
				    MRPDU_VECT_NUMVALUES(ntohs
							 (mrpdu_vectorptr->
							  VectorHeader));
#endif

#if LOG_MSRP
				mrpd_log_printf
				    ("MSRP msrp_recv_msg() LISTENER vector addr 0x%X, n = %d, VectorHeader (ntohs) %d, VectorHeader read %d\n",
				     ((int)mrpdu_vectorptr) & 0x3, numvalues,
#ifdef MICREL_1588_PTP
				     VectorHeader,
#else
				     ntohs(mrpdu_vectorptr->VectorHeader),
#endif
				     ((uint8_t *) mrpdu_vectorptr)[0] << 8 |
				     ((uint8_t *) mrpdu_vectorptr)[1]);
#endif

				if (0 == numvalues) {
					/* 2 byte numvalues + 8 byte FirstValue + (0) vector bytes */
					mrpdu_msg_ptr =
					    (uint8_t *) mrpdu_vectorptr;
					mrpdu_msg_ptr += 10;

					mrpdu_vectorptr =
					    (mrpdu_vectorattrib_t *)
					    mrpdu_msg_ptr;
					/* Malformed - cant tell how long the trailing vectors are */
					continue;
				}
#ifdef MICREL_1588_PTP
				if ((mrpdu_vectorptr->FirstValue_VectorEvents +
				    (numvalues + 2) / 3 +
				    (numvalues + 3) / 4) >=
#else
				if ((mrpdu_vectorptr->FirstValue_VectorEvents +
				     numvalues / 3 + numvalues / 4) >=
#endif
				    mrpdu_msg_eof) {
					/* Malformed - runs off the end of the pdu */
					goto out;
				}
/* Generate rLA event at the very beginnning and only once. */
#ifdef MICREL_1588_PTP
				if (MRPDU_VECT_LVA(VectorHeader) && !rLA_listener) {
					msrp_event(MRP_EVENT_RLA, &listener_attrib);
					rLA_listener = 1;
				}
#endif
				memcpy(streamid_firstval,
				       &
				       (mrpdu_vectorptr->FirstValue_VectorEvents
					[0]), 8);

				/*
				 * parse the 4-packed events first to figure out the substates, then
				 * insert them as we parse the 3-packed events for the MRP state machines
				 */

#ifdef MICREL_1588_PTP
				numvectorbytes = (numvalues + 3) / 4;
				vectidx = 8 + (numvalues + 2) / 3;
#else
				/* if not an even multiple ... */
				if (numvalues != ((numvalues / 4) * 4))
					numvectorbytes = (numvalues / 4) + 1;
				else
					numvectorbytes = (numvalues / 4);

				if (numvalues != ((numvalues / 3) * 3))
					vectidx = 8 + (numvalues / 3) + 1;
				else
					vectidx = 8 + (numvalues / 3);
#endif

				listener_endbyte = vectidx + numvectorbytes;

				if (&
				    (mrpdu_vectorptr->FirstValue_VectorEvents
				     [listener_endbyte]) >= mrpdu_msg_eof)
					goto out;

				if (NULL == listener_vectevt) {
					listener_vectevt_sz = 64;;
					listener_vectevt =
					    (int *)malloc(listener_vectevt_sz *
							  sizeof(int));
					if (NULL == listener_vectevt)
						goto out;
				}

				listener_vectevt_idx = 0;

				for (; vectidx < listener_endbyte; vectidx++) {
					vect_4pack =
					    mrpdu_vectorptr->
					    FirstValue_VectorEvents[vectidx];

					vectevt[3] =
					    vect_4pack -
					    ((vect_4pack >> 2) << 2);
					vect_4pack = vect_4pack >> 2;
					vectevt[2] =
					    vect_4pack -
					    ((vect_4pack >> 2) << 2);
					vect_4pack = vect_4pack >> 2;
					vectevt[1] =
					    vect_4pack -
					    ((vect_4pack >> 2) << 2);
					vect_4pack = vect_4pack >> 2;
					vectevt[0] =
					    vect_4pack -
					    ((vect_4pack >> 2) << 2);
					vect_4pack = vect_4pack >> 2;

					numvalues_processed =
					    (numvalues > 4 ? 4 : numvalues);

					for (vectevt_idx = 0;
					     vectevt_idx < numvalues_processed;
					     vectevt_idx++) {
						if (listener_vectevt_idx ==
						    listener_vectevt_sz) {
							listener_vectevt =
							    realloc
							    (listener_vectevt,
							     (listener_vectevt_sz
							      +
							      64) *
							     sizeof(int));
							if (NULL ==
							    listener_vectevt)
								goto out;
							listener_vectevt_sz +=
							    64;
						}
						listener_vectevt
						    [listener_vectevt_idx] =
						    vectevt[vectevt_idx];
						listener_vectevt_idx++;
					}
					numvalues -= numvalues_processed;
				}

				numvalues =
#ifdef MICREL_1588_PTP
				    MRPDU_VECT_NUMVALUES(VectorHeader);
#else
				    MRPDU_VECT_NUMVALUES(ntohs
							 (mrpdu_vectorptr->
							  VectorHeader));
#endif

				/* if not an even multiple ... */
				if (numvalues != ((numvalues / 3) * 3))
					numvectorbytes = (numvalues / 3) + 1;
				else
					numvectorbytes = (numvalues / 3);

				listener_vectevt_idx = 0;

				for (vectidx = 8;
				     vectidx <= (numvectorbytes + 8);
				     vectidx++) {
					vect_3pack =
					    mrpdu_vectorptr->
					    FirstValue_VectorEvents[vectidx];
					vectevt[0] = vect_3pack / 36;
					vectevt[1] =
					    (vect_3pack - vectevt[0] * 36) / 6;
					vectevt[2] =
					    vect_3pack - (36 * vectevt[0]) -
					    (6 * vectevt[1]);

					numvalues_processed =
					    (numvalues > 3 ? 3 : numvalues);

					for (vectevt_idx = 0;
					     vectevt_idx < numvalues_processed;
					     vectevt_idx++,
					     listener_vectevt_idx++) {

						if (MSRP_LISTENER_IGNORE ==
						    listener_vectevt
						    [listener_vectevt_idx]) {
							msrp_increment_streamid
							    (streamid_firstval);
							continue;
						}

						attrib = msrp_alloc();
						if (NULL == attrib)
							goto out;	/* oops - internal error */

						attrib->type =
						    MSRP_LISTENER_TYPE;

						memcpy(attrib->attribute.
						       talk_listen.StreamID,
						       streamid_firstval, 8);
						attrib->substate =
						    listener_vectevt
						    [listener_vectevt_idx];
						msrp_increment_streamid
						    (streamid_firstval);
#if 0
						listener_vectevt_idx++;
#endif
#ifdef MICREL_1588_PTP
attrib->attribute.talk_listen.port = mrp_index + 1;
#endif

						memcpy(attrib->registrar.
						       macaddr, eth->srcaddr,
						       6);

#if LOG_MSRP
						mrpd_log_printf
						    ("MSRP msrp_recv_msg() Listener[%d][%d] attrib %d\n",
						     vectidx, vectevt_idx,
						     vectevt[vectevt_idx]);
#endif

						switch (vectevt[vectevt_idx]) {
						case MRPDU_NEW:
							msrp_event
							    (MRP_EVENT_RNEW,
							     attrib);
							break;
						case MRPDU_JOININ:
							msrp_event
							    (MRP_EVENT_RJOININ,
							     attrib);
							break;
						case MRPDU_IN:
							msrp_event
							    (MRP_EVENT_RIN,
							     attrib);
							break;
						case MRPDU_JOINMT:
							msrp_event
							    (MRP_EVENT_RJOINMT,
							     attrib);
							break;
						case MRPDU_MT:
							msrp_event
							    (MRP_EVENT_RMT,
							     attrib);
							break;
						case MRPDU_LV:
							msrp_event
							    (MRP_EVENT_RLV,
							     attrib);
							break;
						default:
							free(attrib);
							break;
						}
					}
					numvalues -= numvalues_processed;
				}

#ifndef MICREL_1588_PTP
				if (MRPDU_VECT_LVA
				    (ntohs(mrpdu_vectorptr->VectorHeader)))
					msrp_event(MRP_EVENT_RLA, NULL);
#endif

				numvalues =
#ifdef MICREL_1588_PTP
				    MRPDU_VECT_NUMVALUES(VectorHeader);
#else
				    MRPDU_VECT_NUMVALUES(ntohs
							 (mrpdu_vectorptr->
							  VectorHeader));
#endif
				if (numvalues != ((numvalues / 4) * 4))
					numvectorbytes += (numvalues / 4) + 1;
				else
					numvectorbytes += (numvalues / 4);

				/* 2 byte numvalues + 8 byte FirstValue + (n) vector bytes */
				mrpdu_msg_ptr = (uint8_t *) mrpdu_vectorptr;
				mrpdu_msg_ptr += 10 + numvectorbytes;

				mrpdu_vectorptr =
				    (mrpdu_vectorattrib_t *) mrpdu_msg_ptr;
			}

			break;
		case MSRP_TALKER_ADV_TYPE:
			/* another place where the spec munges with reality ...
			 * we can start out as a talker advertise type, but can get back
			 * a talker failed from the bridge in response ... in which
			 * by the spec we are supposed to merge the talker failed into
			 * the talker advertise and change the attribute type ...
			 *
			 * but also note the spec says that a talker cant change the
			 * firstvalues definition of a stream without tearing down the
			 * existing stream, wait two leave-all periods, then re-advertise
			 * the stream.
			 */
			if (mrpdu_msg->AttributeLength != 25) {
				/* we can seek for an endmark to recover .. but this version
				 * dumps the entire packet as malformed
				 */
				goto out;
			}

			/* MSRP uses AttributeListLength ...  */
			mrpdu_vectorptr =
			    (mrpdu_vectorattrib_t *) & (mrpdu_msg->Data[2]);
			mrpdu_msg_ptr = (uint8_t *) mrpdu_vectorptr;

			while (!((mrpdu_msg_ptr[0] == 0)
				 && (mrpdu_msg_ptr[1] == 0))) {
#ifdef MICREL_1588_PTP
				unaligned = (uint8_t *)
					&mrpdu_vectorptr->VectorHeader;
				VectorHeader = ((uint16_t) unaligned[0] << 8) |
					unaligned[1];
				numvalues =
				    MRPDU_VECT_NUMVALUES(VectorHeader);
#else
				numvalues =
				    MRPDU_VECT_NUMVALUES(ntohs
							 (mrpdu_vectorptr->
							  VectorHeader));
#endif

				if (0 == numvalues) {
					/* 2 byte numvalues + 25 byte FirstValue + (0) vector bytes */
					mrpdu_msg_ptr =
					    (uint8_t *) mrpdu_vectorptr;
					mrpdu_msg_ptr += 27;

					mrpdu_vectorptr =
					    (mrpdu_vectorattrib_t *)
					    mrpdu_msg_ptr;
					continue;
				}
				if ((mrpdu_vectorptr->FirstValue_VectorEvents +
				     numvalues / 3) >= mrpdu_msg_eof) {
					/* Malformed - runs off the end of the pdu */
					printf
					    ("bad talker adv PDU too long \n");
					goto out;
				}
/* Generate rLA event at the very beginnning and only once. */
#ifdef MICREL_1588_PTP
				if (MRPDU_VECT_LVA(VectorHeader) && !rLA_talker) {
					msrp_event(MRP_EVENT_RLA, &talker_attrib);
					rLA_talker = 1;
				}
#endif
				memcpy(streamid_firstval,
				       mrpdu_vectorptr->FirstValue_VectorEvents,
				       8);
				memcpy(destmac_firstval,
				       &
				       (mrpdu_vectorptr->FirstValue_VectorEvents
					[8]), 6);

				/* if not an even multiple ... */
				if (numvalues != ((numvalues / 3) * 3))
					numvectorbytes = (numvalues / 3) + 1;
				else
					numvectorbytes = (numvalues / 3);

				for (vectidx = 25;
				     vectidx <= (numvectorbytes + 25);
				     vectidx++) {
					vect_3pack =
					    mrpdu_vectorptr->
					    FirstValue_VectorEvents[vectidx];
					vectevt[0] = vect_3pack / 36;
					vectevt[1] =
					    (vect_3pack - vectevt[0] * 36) / 6;
					vectevt[2] =
					    vect_3pack - (36 * vectevt[0]) -
					    (6 * vectevt[1]);

					numvalues_processed =
					    (numvalues > 3 ? 3 : numvalues);

					for (vectevt_idx = 0;
					     vectevt_idx < numvalues_processed;
					     vectevt_idx++) {

						attrib = msrp_alloc();
						if (NULL == attrib)
							goto out;	/* oops - internal error */

						attrib->type =
						    MSRP_TALKER_ADV_TYPE;

						/* note this ISNT from us ... */
						attrib->direction =
						    MSRP_DIRECTION_LISTENER;

						memcpy(attrib->attribute.
						       talk_listen.StreamID,
						       streamid_firstval, 8);
						memcpy(attrib->attribute.
						       talk_listen.
						       DataFrameParameters.
						       Dest_Addr,
						       destmac_firstval, 6);

						msrp_increment_streamid
						    (streamid_firstval);
						mmrp_increment_macaddr
						    (destmac_firstval);

						attrib->attribute.talk_listen.
						    DataFrameParameters.
						    Vlan_ID =
						    mrpdu_vectorptr->
						    FirstValue_VectorEvents[14];
						attrib->attribute.talk_listen.
						    DataFrameParameters.
						    Vlan_ID <<= 8;
						attrib->attribute.talk_listen.
						    DataFrameParameters.
						    Vlan_ID |=
						    mrpdu_vectorptr->
						    FirstValue_VectorEvents[15];

						attrib->attribute.talk_listen.
						    TSpec.MaxFrameSize =
						    mrpdu_vectorptr->
						    FirstValue_VectorEvents[16];
						attrib->attribute.talk_listen.
						    TSpec.MaxFrameSize <<= 8;
						attrib->attribute.talk_listen.
						    TSpec.MaxFrameSize |=
						    mrpdu_vectorptr->
						    FirstValue_VectorEvents[17];

						attrib->attribute.talk_listen.
						    TSpec.MaxIntervalFrames =
						    mrpdu_vectorptr->
						    FirstValue_VectorEvents[18];
						attrib->attribute.talk_listen.
						    TSpec.
						    MaxIntervalFrames <<= 8;
						attrib->attribute.talk_listen.
						    TSpec.MaxIntervalFrames |=
						    mrpdu_vectorptr->
						    FirstValue_VectorEvents[19];

						attrib->attribute.talk_listen.
						    PriorityAndRank =
						    mrpdu_vectorptr->
						    FirstValue_VectorEvents[20];

						attrib->attribute.talk_listen.
						    AccumulatedLatency =
						    mrpdu_vectorptr->
						    FirstValue_VectorEvents[21];
						attrib->attribute.talk_listen.
						    AccumulatedLatency <<= 8;
						attrib->attribute.talk_listen.
						    AccumulatedLatency |=
						    mrpdu_vectorptr->
						    FirstValue_VectorEvents[22];
						attrib->attribute.talk_listen.
						    AccumulatedLatency <<= 8;
						attrib->attribute.talk_listen.
						    AccumulatedLatency |=
						    mrpdu_vectorptr->
						    FirstValue_VectorEvents[23];
						attrib->attribute.talk_listen.
						    AccumulatedLatency <<= 8;
						attrib->attribute.talk_listen.
						    AccumulatedLatency |=
						    mrpdu_vectorptr->
						    FirstValue_VectorEvents[24];
#ifdef MICREL_1588_PTP
attrib->attribute.talk_listen.port = mrp_index + 1;
#endif

						memcpy(attrib->registrar.
						       macaddr, eth->srcaddr,
						       6);

#if LOG_MSRP
						mrpd_log_printf
						    ("MSRP msrp_recv_msg() TalkerAdv[%d][%d] attrib %d\n",
						     vectidx, vectevt_idx,
						     vectevt[vectevt_idx]);
#endif

						switch (vectevt[vectevt_idx]) {
						case MRPDU_NEW:
							msrp_event
							    (MRP_EVENT_RNEW,
							     attrib);
							break;
						case MRPDU_JOININ:
							msrp_event
							    (MRP_EVENT_RJOININ,
							     attrib);
							break;
						case MRPDU_IN:
							msrp_event
							    (MRP_EVENT_RIN,
							     attrib);
							break;
						case MRPDU_JOINMT:
							msrp_event
							    (MRP_EVENT_RJOINMT,
							     attrib);
							break;
						case MRPDU_MT:
							msrp_event
							    (MRP_EVENT_RMT,
							     attrib);
							break;
						case MRPDU_LV:
							msrp_event
							    (MRP_EVENT_RLV,
							     attrib);
							break;
						default:
							free(attrib);
							break;
						}
					}
					numvalues -= numvalues_processed;
				}

#ifndef MICREL_1588_PTP
				if (MRPDU_VECT_LVA
				    (ntohs(mrpdu_vectorptr->VectorHeader)))
					msrp_event(MRP_EVENT_RLA, NULL);
#endif

				/* 2 byte numvalues + 25 byte FirstValue + (n) vector bytes */
				mrpdu_msg_ptr = (uint8_t *) mrpdu_vectorptr;
				mrpdu_msg_ptr += 27 + numvectorbytes;

				mrpdu_vectorptr =
				    (mrpdu_vectorattrib_t *) mrpdu_msg_ptr;
			}
			break;
		case MSRP_TALKER_FAILED_TYPE:
			if (mrpdu_msg->AttributeLength != 34) {
				/* we can seek for an endmark to recover .. but this version
				 * dumps the entire packet as malformed
				 */
				goto out;
			}

			/* MSRP uses AttributeListLength ...  */
			mrpdu_vectorptr =
			    (mrpdu_vectorattrib_t *) & (mrpdu_msg->Data[2]);
			mrpdu_msg_ptr = (uint8_t *) mrpdu_vectorptr;
			while (!((mrpdu_msg_ptr[0] == 0)
				 && (mrpdu_msg_ptr[1] == 0))) {
#ifdef MICREL_1588_PTP
				unaligned = (uint8_t *)
					&mrpdu_vectorptr->VectorHeader;
				VectorHeader = ((uint16_t) unaligned[0] << 8) |
					unaligned[1];
				numvalues =
				    MRPDU_VECT_NUMVALUES(VectorHeader);
#else
				numvalues =
				    MRPDU_VECT_NUMVALUES(ntohs
							 (mrpdu_vectorptr->
							  VectorHeader));
#endif

				if (0 == numvalues) {
					/* 2 byte numvalues + 34 byte FirstValue + (0) vector bytes */
					mrpdu_msg_ptr =
					    (uint8_t *) mrpdu_vectorptr;
					mrpdu_msg_ptr += 36;
					mrpdu_vectorptr =
					    (mrpdu_vectorattrib_t *)
					    mrpdu_msg_ptr;
					continue;
				}
				if ((mrpdu_vectorptr->FirstValue_VectorEvents +
				     numvalues / 3) >= mrpdu_msg_eof)
					/* Malformed - runs off the end of the pdu */
					goto out;

/* Generate rLA event at the very beginnning and only once. */
#ifdef MICREL_1588_PTP
				if (MRPDU_VECT_LVA(VectorHeader) && !rLA_talker) {
					msrp_event(MRP_EVENT_RLA, &talker_attrib);
					rLA_talker = 1;
				}
#endif
				memcpy(streamid_firstval,
				       mrpdu_vectorptr->FirstValue_VectorEvents,
				       8);
				memcpy(destmac_firstval,
				       &
				       (mrpdu_vectorptr->FirstValue_VectorEvents
					[8]), 6);

				/* if not an even multiple ... */
				if (numvalues != ((numvalues / 3) * 3))
					numvectorbytes = (numvalues / 3) + 1;
				else
					numvectorbytes = (numvalues / 3);

				for (vectidx = 34;
				     vectidx <= (numvectorbytes + 34);
				     vectidx++) {
					vect_3pack =
					    mrpdu_vectorptr->
					    FirstValue_VectorEvents[vectidx];
					vectevt[0] = vect_3pack / 36;
					vectevt[1] =
					    (vect_3pack - vectevt[0] * 36) / 6;
					vectevt[2] =
					    vect_3pack - (36 * vectevt[0]) -
					    (6 * vectevt[1]);

					numvalues_processed =
					    (numvalues > 3 ? 3 : numvalues);

					for (vectevt_idx = 0;
					     vectevt_idx < numvalues_processed;
					     vectevt_idx++) {

						attrib = msrp_alloc();
						if (NULL == attrib)
							goto out;	/* oops - internal error */
						/* update the failure information on merge, but don't support
						 * different ADV and FAILED_TYPES in the list of attributes */
						attrib->type =
						    MSRP_TALKER_ADV_TYPE;

						/* NOTE this isn't from us */
						attrib->direction =
						    MSRP_DIRECTION_LISTENER;

						memcpy(attrib->attribute.
						       talk_listen.StreamID,
						       streamid_firstval, 8);
						memcpy(attrib->attribute.
						       talk_listen.
						       DataFrameParameters.
						       Dest_Addr,
						       destmac_firstval, 6);

						msrp_increment_streamid
						    (streamid_firstval);
						mmrp_increment_macaddr
						    (destmac_firstval);

						attrib->attribute.talk_listen.
						    DataFrameParameters.
						    Vlan_ID =
						    mrpdu_vectorptr->
						    FirstValue_VectorEvents[14];
						attrib->attribute.talk_listen.
						    DataFrameParameters.
						    Vlan_ID <<= 8;
						attrib->attribute.talk_listen.
						    DataFrameParameters.
						    Vlan_ID |=
						    mrpdu_vectorptr->
						    FirstValue_VectorEvents[15];

						attrib->attribute.talk_listen.
						    TSpec.MaxFrameSize =
						    mrpdu_vectorptr->
						    FirstValue_VectorEvents[16];
						attrib->attribute.talk_listen.
						    TSpec.MaxFrameSize <<= 8;
						attrib->attribute.talk_listen.
						    TSpec.MaxFrameSize |=
						    mrpdu_vectorptr->
						    FirstValue_VectorEvents[17];

						attrib->attribute.talk_listen.
						    TSpec.MaxIntervalFrames =
						    mrpdu_vectorptr->
						    FirstValue_VectorEvents[18];
						attrib->attribute.talk_listen.
						    TSpec.
						    MaxIntervalFrames <<= 8;
						attrib->attribute.talk_listen.
						    TSpec.MaxIntervalFrames |=
						    mrpdu_vectorptr->
						    FirstValue_VectorEvents[19];

						attrib->attribute.talk_listen.
						    PriorityAndRank =
						    mrpdu_vectorptr->
						    FirstValue_VectorEvents[20];

						attrib->attribute.talk_listen.
						    AccumulatedLatency =
						    mrpdu_vectorptr->
						    FirstValue_VectorEvents[21];
						attrib->attribute.talk_listen.
						    AccumulatedLatency <<= 8;
						attrib->attribute.talk_listen.
						    AccumulatedLatency |=
						    mrpdu_vectorptr->
						    FirstValue_VectorEvents[22];
						attrib->attribute.talk_listen.
						    AccumulatedLatency <<= 8;
						attrib->attribute.talk_listen.
						    AccumulatedLatency |=
						    mrpdu_vectorptr->
						    FirstValue_VectorEvents[23];
						attrib->attribute.talk_listen.
						    AccumulatedLatency <<= 8;
						attrib->attribute.talk_listen.
						    AccumulatedLatency |=
						    mrpdu_vectorptr->
						    FirstValue_VectorEvents[24];

						memcpy(attrib->attribute.
						       talk_listen.
						       FailureInformation.
						       BridgeID,
						       &(mrpdu_vectorptr->
							 FirstValue_VectorEvents
							 [25]), 8);

						attrib->attribute.talk_listen.
						    FailureInformation.
						    FailureCode =
						    mrpdu_vectorptr->
						    FirstValue_VectorEvents[33];
#ifdef MICREL_1588_PTP
attrib->attribute.talk_listen.port = mrp_index + 1;
#endif

						memcpy(attrib->registrar.
						       macaddr, eth->srcaddr,
						       6);

						switch (vectevt[vectevt_idx]) {
						case MRPDU_NEW:
							msrp_event
							    (MRP_EVENT_RNEW,
							     attrib);
							break;
						case MRPDU_JOININ:
							msrp_event
							    (MRP_EVENT_RJOININ,
							     attrib);
							break;
						case MRPDU_IN:
							msrp_event
							    (MRP_EVENT_RIN,
							     attrib);
							break;
						case MRPDU_JOINMT:
							msrp_event
							    (MRP_EVENT_RJOINMT,
							     attrib);
							break;
						case MRPDU_MT:
							msrp_event
							    (MRP_EVENT_RMT,
							     attrib);
							break;
						case MRPDU_LV:
							msrp_event
							    (MRP_EVENT_RLV,
							     attrib);
							break;
						default:
							free(attrib);
							break;
						}
					}
					numvalues -= numvalues_processed;
				}

#ifndef MICREL_1588_PTP
				if (MRPDU_VECT_LVA
				    (ntohs(mrpdu_vectorptr->VectorHeader)))
					msrp_event(MRP_EVENT_RLA, NULL);
#endif

				/* 2 byte numvalues + 34 byte FirstValue + (n) vector bytes */
				mrpdu_msg_ptr = (uint8_t *) mrpdu_vectorptr;
				mrpdu_msg_ptr += 36 + numvectorbytes;

				mrpdu_vectorptr =
				    (mrpdu_vectorattrib_t *) mrpdu_msg_ptr;
			}
			break;
		default:
			/* unrecognized attribute type
			 * we can seek for an endmark to recover .. but this version
			 * dumps the entire packet as malformed
			 */
			printf
			    ("################## unrecognized attribute type (%d)\n",
			     mrpdu_msg->AttributeType);
			goto out;
		}
	}
#ifdef MICREL_1588_PTP
if (ofp) {
fprintf(ofp, " <\n");
fflush(ofp);
}
#endif

	if (listener_vectevt)
		free(listener_vectevt);

	free(msgbuf);
	return 0;
 out:
	if (listener_vectevt)
		free(listener_vectevt);

	free(msgbuf);

	return -1;
}

#ifdef MICREL_1588_PTP
static int dbg_listener;

static int chk_listen_id(uint8_t *first, uint8_t *next)
{
	if (!memcmp(first, next, 6) && (first[6] < next[6] ||
	    first[6] == next[6] && first[7] <= next[7])) {
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
if (ofp && dbg_listener)
fprintf(ofp, " f: c=%d a=%d d=%d n=%d %d\n",
cnt, attr_left, decl_left, num, attr_cnt + decl_cnt);
	} while (attr_cnt + decl_cnt > 11);
	return num;
}

static void msrp_prepare_tx(uint32_t type, int lva)
{
	uint8_t cid_firstval = 0;
	uint8_t prio_firstval = 0;
	uint8_t mac_firstval[6];
	uint8_t streamid_firstval[8];
	struct msrp_attribute *attrib;
	struct msrp_attribute *first = NULL;
	struct msrp_attribute *last = NULL;
	struct msrp_attribute *optional = NULL;
	int firstval_max;
	int firstval_cnt = 0;
	int firstval_optional = 0;
	int listen_cnt = 1;
	int orig_type = type;

	if (MSRP_DOMAIN_TYPE == type)
		firstval_max = (((2 + 4) + 1) * 2 - (2 + 4)) * 3 - 2;
	else if (MSRP_LISTENER_TYPE == type)
		firstval_max = (((2 + 8) + 2) * 2 - (2 + 8)) / 2 * 3 - 2;
	else if (MSRP_TALKER_ADV_TYPE == type)
		firstval_max = (((2 + 25) + 1) * 2 - (2 + 25)) * 3 - 2;
	else {
		firstval_max = (((2 + 34) + 1) * 2 - (2 + 34)) * 3 - 2;
		type = MSRP_TALKER_ADV_TYPE;
	}
	attrib = MSRP_db->attrib_list;
	while (attrib != NULL) {
		if (type != attrib->type)
			goto next;
		if ((MSRP_TALKER_ADV_TYPE == orig_type &&
		    attrib->attribute.talk_listen.
		    FailureInformation.FailureCode) ||
		    (MSRP_TALKER_FAILED_TYPE == orig_type &&
		    !attrib->attribute.talk_listen.
		    FailureInformation.FailureCode))
			goto next;
		attrib->nextval = 0;
		if (0 == attrib->applicant.tx)
			goto next;
		last = attrib;
		if (firstval_cnt) {
			int firstval_next = 1;

			if (MSRP_DOMAIN_TYPE == attrib->type) {
				++cid_firstval;
				++prio_firstval;
				if (cid_firstval !=
				    attrib->attribute.domain.SRclassID ||
				    prio_firstval !=
				    attrib->attribute.domain.SRclassPriority)
					firstval_next = 0;
			} else if (MSRP_LISTENER_TYPE == attrib->type) {
				int diff;

				diff = chk_listen_id(streamid_firstval,
					attrib->attribute.talk_listen.
					StreamID);
if (ofp && dbg_listener)
fprintf(ofp, " D:%d\n", diff);
				msrp_increment_streamid(streamid_firstval);
				if (memcmp(attrib->attribute.talk_listen.
				    StreamID,
				    streamid_firstval, 8)) {
					int max;

					firstval_next = 0;
					max = find_largest_cnt(listen_cnt);
if (ofp && dbg_listener)
fprintf(ofp, " l=c:%d d:%d m:%d\n", listen_cnt, diff, max);
					if (diff <= max) {
						listen_cnt += diff;
if (ofp && dbg_listener)
fprintf(ofp, "d=%d\n", diff);
						attrib->nextval = (uint16_t)
							diff - 1;
						optional = NULL;
						firstval_optional = 0;
						first = attrib;
						memcpy(streamid_firstval,
							attrib->attribute.
							talk_listen.StreamID,
							8);
						firstval_cnt = 1;
						goto next;
					}
				} else {
					++listen_cnt;
				}
			} else {
				msrp_increment_streamid(streamid_firstval);
				mmrp_increment_macaddr(mac_firstval);
				if (memcmp(attrib->attribute.talk_listen.
				    StreamID,
				    streamid_firstval, 8) ||
				    memcmp(attrib->attribute.talk_listen.
				    DataFrameParameters.Dest_Addr,
				    mac_firstval, 6))
					firstval_next = 0;
			}
			if (!firstval_next)
				first = NULL;
			else {
				++firstval_cnt;
				if (MRP_ENCODE_OPTIONAL ==
				    attrib->applicant.encode) {
					if (!optional)
						optional = attrib;
					++firstval_optional;
					if (firstval_optional > firstval_max)
						first = NULL;
				} else {
					optional = NULL;
					firstval_optional = 0;
				}
			}
		}
		if (!first) {
			while (firstval_optional) {
				optional->applicant.tx = 0;
				optional = optional->next;
				--firstval_optional;
			}
			optional = NULL;
			firstval_optional = 0;
			if (MRP_ENCODE_OPTIONAL == attrib->applicant.encode) {
				attrib->applicant.tx = 0;
				goto next;
			}
			first = attrib;
			if (MSRP_DOMAIN_TYPE == attrib->type) {
				cid_firstval = attrib->attribute.domain.
					SRclassID;
				prio_firstval = attrib->attribute.domain.
					SRclassPriority;
			} else if (MSRP_LISTENER_TYPE == attrib->type) {
				memcpy(streamid_firstval,
					attrib->attribute.talk_listen.
					StreamID, 8);
				listen_cnt = 1;
			} else {
				memcpy(streamid_firstval,
					attrib->attribute.talk_listen.
					StreamID, 8);
				memcpy(mac_firstval,
					attrib->attribute.talk_listen.
					DataFrameParameters.Dest_Addr,
					6);
			}
			firstval_cnt = 1;
			last = NULL;
		}

next:
		attrib = attrib->next;
	}

	/* Need to send at least one for LeaveAll. */
	if (lva && last && !last->applicant.tx)
		last->applicant.tx = 1;
	if (MSRP_LISTENER_TYPE == type)
		dbg_listener = 0;
}
#endif

int
msrp_emit_domainvectors(unsigned char *msgbuf, unsigned char *msgbuf_eof,
			int *bytes_used, int lva)
{
	mrpdu_vectorattrib_t *mrpdu_vectorptr;
	uint16_t numvalues;
	uint8_t vect_3pack;
	int vectidx;
	int vectevt[3];
	int vectevt_idx;
	uint8_t srclassID_firstval;
	uint8_t srclassprio_firstval;
	uint16_t srclassvid_firstval;
	int attriblistlen;
	struct msrp_attribute *attrib;
/* pending review and deletion */
#ifdef MSRP_AGGREGATE_DOMAINS_VECTORS
	struct msrp_attribute *vattrib;
#endif
	mrpdu_message_t *mrpdu_msg;
	unsigned char *mrpdu_msg_ptr = msgbuf;
	unsigned char *mrpdu_msg_eof = msgbuf_eof;
#ifdef MICREL_1588_PTP
	uint16_t VectorHeader;
	uint8_t *unaligned;
#endif

#ifdef MICREL_1588_PTP
	if (mrpdu_msg_ptr > (mrpdu_msg_eof - (4 + 6 + 1 + 4)))
#else
	/* need at least 5 bytes for a single vector */
	if (mrpdu_msg_ptr > (mrpdu_msg_eof - 5))
#endif
		goto oops;

	mrpdu_msg = (mrpdu_message_t *) mrpdu_msg_ptr;
	mrpdu_msg->AttributeType = MSRP_DOMAIN_TYPE;
	mrpdu_msg->AttributeLength = 4;

#ifdef MICREL_1588_PTP
	msrp_prepare_tx(MSRP_DOMAIN_TYPE, lva);

	attrib = MSRP_db->mrp_db.tx_attrib;
	if (attrib) {
		if (MSRP_DOMAIN_TYPE != attrib->type) {
			*bytes_used = 0;
			return 0;
		}
	} else
#endif
	attrib = MSRP_db->attrib_list;

	mrpdu_vectorptr = (mrpdu_vectorattrib_t *) & (mrpdu_msg->Data[2]);

#ifdef MICREL_1588_PTP
	while ((mrpdu_msg_ptr <= (mrpdu_msg_eof - (4 + 2 + 1 + 4))) &&
	       (NULL != attrib)) {
#else
	while ((mrpdu_msg_ptr < (mrpdu_msg_eof - 2)) && (NULL != attrib)) {
#endif

		if (MSRP_DOMAIN_TYPE != attrib->type) {
			attrib = attrib->next;
			continue;
		}

		if (0 == attrib->applicant.tx) {
#ifdef MICREL_1588_PTP
			MSRP_db->mrp_db.registrar_state =
				attrib->registrar.mrp_state;
			mrp_applicant_chk(&MSRP_db->mrp_db,
				&attrib->applicant);
#endif
			attrib = attrib->next;
			continue;
		}
#ifndef MICREL_1588_PTP
		if (MRP_ENCODE_OPTIONAL == attrib->applicant.encode) {
			attrib->applicant.tx = 0;
			attrib = attrib->next;
			continue;
		}
#endif

		/* pointing to at least one attribute which needs to be transmitted */
		srclassID_firstval = attrib->attribute.domain.SRclassID;
		srclassprio_firstval = attrib->attribute.domain.SRclassPriority;
		srclassvid_firstval = attrib->attribute.domain.SRclassVID;

		mrpdu_vectorptr->FirstValue_VectorEvents[0] =
		    srclassID_firstval;
		mrpdu_vectorptr->FirstValue_VectorEvents[1] =
		    srclassprio_firstval;
		mrpdu_vectorptr->FirstValue_VectorEvents[2] =
		    (uint8_t) (srclassvid_firstval >> 8);
		mrpdu_vectorptr->FirstValue_VectorEvents[3] =
		    (uint8_t) srclassvid_firstval;

		switch (attrib->applicant.sndmsg) {
		case MRP_SND_IN:
			/*
			 * If 'In' in indicated by the applicant attribute, the
			 * look at the registrar state to determine whether to
			 * send an In (if registrar is also In) or an Mt if the
			 * registrar is either Mt or Lv.
			 */
			if (MRP_IN_STATE == attrib->registrar.mrp_state)
				vectevt[0] = MRPDU_IN;
			else
				vectevt[0] = MRPDU_MT;
			break;
		case MRP_SND_NEW:
			vectevt[0] = MRPDU_NEW;
			break;
		case MRP_SND_LV:
			vectevt[0] = MRPDU_LV;
			break;
		case MRP_SND_JOIN:
			/* IF 'Join' in indicated by the applicant, look at
			 * the corresponding registrar state to determine whether
			 * to send a JoinIn (if the registar state is 'In') or
			 * a JoinMt if the registrar state is MT or LV.
			 */
			if (MRP_IN_STATE == attrib->registrar.mrp_state)
				vectevt[0] = MRPDU_JOININ;
			else
				vectevt[0] = MRPDU_JOINMT;
			break;
		default:
			/* huh? */
			goto oops;
			break;
		}

#ifdef MICREL_1588_PTP
		/* Attribute sent so change state. */
		MSRP_db->mrp_db.registrar_state = attrib->registrar.mrp_state;
		mrp_applicant_chk(&MSRP_db->mrp_db, &attrib->applicant);
#endif

		vectevt_idx = 1;
		numvalues = 1;
		vectevt[1] = 0;
		vectevt[2] = 0;

		/* now attempt to vectorize contiguous other attributes
		 * which also need to be transmitted
		 */

		vectidx = 4;

/* pending review and deletion */
#ifdef MSRP_AGGREGATE_DOMAINS_VECTORS
		vattrib = attrib->next;

		while (NULL != vattrib) {
			if (MSRP_DOMAIN_TYPE != vattrib->type)
				break;

			if (0 == vattrib->applicant.tx)
				break;

			srclassID_firstval++;
			srclassprio_firstval++;

			if (srclassID_firstval !=
			    vattrib->attribute.domain.SRclassID)
				break;

			vattrib->applicant.tx = 0;

			switch (vattrib->applicant.sndmsg) {
			case MRP_SND_IN:
				/*
				 * If 'In' in indicated by the applicant attribute, the
				 * look at the registrar state to determine whether to
				 * send an In (if registrar is also In) or an Mt if the
				 * registrar is either Mt or Lv.
				 */
				if (MRP_IN_STATE ==
				    vattrib->registrar.mrp_state)
					vectevt[vectevt_idx] = MRPDU_IN;
				else
					vectevt[vectevt_idx] = MRPDU_MT;
				break;
			case MRP_SND_NEW:
				vectevt[vectevt_idx] = MRPDU_NEW;
				break;
			case MRP_SND_LV:
				vectevt[vectevt_idx] = MRPDU_LV;
				break;
			case MRP_SND_JOIN:
				/* IF 'Join' in indicated by the applicant, look at
				 * the corresponding registrar state to determine whether
				 * to send a JoinIn (if the registar state is 'In') or
				 * a JoinMt if the registrar state is MT or LV.
				 */
				if (MRP_IN_STATE == attrib->registrar.mrp_state)
					vectevt[vectevt_idx] = MRPDU_JOININ;
				else
					vectevt[vectevt_idx] = MRPDU_JOINMT;
				break;
			default:
				/* huh? */
				goto oops;
				break;
			}

#ifdef MICREL_1588_PTP
			/* Attribute sent so change state. */
			MSRP_db->mrp_db.registrar_state =
				vattrib->registrar.mrp_state;
			mrp_applicant_chk(&MSRP_db->mrp_db,
				&vattrib->applicant);
#endif

			vectevt_idx++;
			numvalues++;

			if (vectevt_idx > 2) {
				vect_3pack = MRPDU_3PACK_ENCODE(vectevt[0],
								vectevt[1],
								vectevt[2]);

				mrpdu_vectorptr->FirstValue_VectorEvents
				    [vectidx] = vect_3pack;
				vectidx++;
				vectevt[0] = 0;
				vectevt[1] = 0;
				vectevt[2] = 0;
				vectevt_idx = 0;
			}

			if (&(mrpdu_vectorptr->FirstValue_VectorEvents[vectidx])
			    > (mrpdu_msg_eof - 2))
				goto oops;

			vattrib = vattrib->next;
		}
#endif

		/* handle any trailers */
		if (vectevt_idx > 0) {
			vect_3pack = MRPDU_3PACK_ENCODE(vectevt[0],
							vectevt[1], vectevt[2]);

			mrpdu_vectorptr->FirstValue_VectorEvents[vectidx] =
			    vect_3pack;
			vectidx++;
		}

		if (&(mrpdu_vectorptr->FirstValue_VectorEvents[vectidx]) >
		    (mrpdu_msg_eof - 2))
			goto oops;

#ifdef MICREL_1588_PTP
		VectorHeader = MRPDU_VECT_NUMVALUES(numvalues);

		if (lva)
			VectorHeader |= MRPDU_VECT_LVA(0xFFFF);

		unaligned = (uint8_t *) &mrpdu_vectorptr->VectorHeader;
		unaligned[0] = (uint8_t)(VectorHeader >> 8);
		unaligned[1] = (uint8_t) VectorHeader;
#else
		mrpdu_vectorptr->VectorHeader = MRPDU_VECT_NUMVALUES(numvalues);

		if (lva)
			mrpdu_vectorptr->VectorHeader |= MRPDU_VECT_LVA(0xFFFF);

		mrpdu_vectorptr->VectorHeader =
		    htons(mrpdu_vectorptr->VectorHeader);
#endif

		mrpdu_msg_ptr =
		    &(mrpdu_vectorptr->FirstValue_VectorEvents[vectidx]);
		mrpdu_vectorptr = (mrpdu_vectorattrib_t *) mrpdu_msg_ptr;

		attrib = attrib->next;

	}
#ifdef MICREL_1588_PTP
	MSRP_db->mrp_db.tx_attrib = attrib;
#endif

	if (mrpdu_vectorptr == (mrpdu_vectorattrib_t *) & (mrpdu_msg->Data[2])) {
		*bytes_used = 0;
		return 0;
	}

	/* endmark */
	*mrpdu_msg_ptr = 0;
	mrpdu_msg_ptr++;
	*mrpdu_msg_ptr = 0;
	mrpdu_msg_ptr++;

	*bytes_used = (mrpdu_msg_ptr - msgbuf);

	attriblistlen = mrpdu_msg_ptr - &(mrpdu_msg->Data[2]);
	mrpdu_msg->Data[0] = (uint8_t) (attriblistlen >> 8);
	mrpdu_msg->Data[1] = (uint8_t) attriblistlen;

#if LOG_MSRP
	mrpd_log_printf("MSRP msrp_recv_msg() DONE (OK)\n");
#endif
#ifdef MICREL_1588_PTP
	/* Not all attributes sent. */
	if (attrib)
		return -1;
#endif
	return 0;
 oops:
#if LOG_MSRP
	mrpd_log_printf("MSRP msrp_recv_msg() DONE (OOPS)\n");
#endif
	/* an internal error - caller should assume TXLAF */
	*bytes_used = 0;
	return -1;
}

int
msrp_emit_talkvectors(unsigned char *msgbuf, unsigned char *msgbuf_eof,
		      int *bytes_used, int lva, uint32_t type)
{
	mrpdu_vectorattrib_t *mrpdu_vectorptr;
	uint16_t numvalues;
	uint8_t vect_3pack;
	int vectidx;
	int vectevt[3];
	int vectevt_idx;
	uint8_t streamid_firstval[8];
	uint8_t destmac_firstval[6];
	int attriblistlen;
	struct msrp_attribute *attrib, *vattrib;
	mrpdu_message_t *mrpdu_msg;
	unsigned char *mrpdu_msg_ptr = msgbuf;
	unsigned char *mrpdu_msg_eof = msgbuf_eof;
	int mac_eq;
#ifdef MICREL_1588_PTP
	uint16_t VectorHeader;
	uint8_t *unaligned;
#endif
#if 1
	int minimum;

	if (MSRP_TALKER_FAILED_TYPE == type)
		minimum = 34;
	else
		minimum = 25;
#endif

#ifdef MICREL_1588_PTP
	if (mrpdu_msg_ptr > (mrpdu_msg_eof - (minimum + 6 + 1 + 4)))
#else
	/* need at least 28 bytes for a single vector */
	if (mrpdu_msg_ptr > (mrpdu_msg_eof - 28))
#endif
		goto oops;

	/*
	 * as an endpoint, we don't advertise talker failed attributes (which
	 * only a listener should receive) - but since this daemon could
	 * function dual-mode - listening to streams as well as being a talker
	 * station - we only advertise the talker vectors for declared streams,
	 * not those we know about as a listener ...
	 */
	mrpdu_msg = (mrpdu_message_t *) mrpdu_msg_ptr;
	mrpdu_msg->AttributeType = MSRP_TALKER_ADV_TYPE;
	mrpdu_msg->AttributeLength = 25;
#if 1
	mrpdu_msg->AttributeType = type;
	mrpdu_msg->AttributeLength = minimum;
#endif

#ifdef MICREL_1588_PTP
	msrp_prepare_tx(type, lva);

	attrib = MSRP_db->mrp_db.tx_attrib;
	if (attrib) {
		if (MSRP_TALKER_ADV_TYPE != attrib->type) {
			*bytes_used = 0;
			return 0;
		}
	} else
#endif
	attrib = MSRP_db->attrib_list;

	mrpdu_vectorptr = (mrpdu_vectorattrib_t *) & (mrpdu_msg->Data[2]);

#ifdef MICREL_1588_PTP
	while ((mrpdu_msg_ptr <= (mrpdu_msg_eof - (minimum + 2 + 1 + 4))) &&
	       (NULL != attrib)) {
#else
	while ((mrpdu_msg_ptr < (mrpdu_msg_eof - 2)) && (NULL != attrib)) {
#endif

		if (MSRP_TALKER_ADV_TYPE != attrib->type) {
			attrib = attrib->next;
			continue;
		}
		if ((MSRP_TALKER_ADV_TYPE == type &&
		    attrib->attribute.talk_listen.
		    FailureInformation.FailureCode) ||
		    (MSRP_TALKER_FAILED_TYPE == type &&
		    !attrib->attribute.talk_listen.
		    FailureInformation.FailureCode)) {
			attrib = attrib->next;
			continue;
		}
#ifdef CHECK
		if (MSRP_DIRECTION_LISTENER == attrib->direction) {
			attrib = attrib->next;
			continue;
		}
#endif
		if (0 == attrib->applicant.tx) {
#ifdef MICREL_1588_PTP
			MSRP_db->mrp_db.registrar_state =
				attrib->registrar.mrp_state;
			mrp_applicant_chk(&MSRP_db->mrp_db,
				&attrib->applicant);
#endif
			attrib = attrib->next;
			continue;
		}
#ifndef MICREL_1588_PTP
		if (MRP_ENCODE_OPTIONAL == attrib->applicant.encode) {
			attrib->applicant.tx = 0;
			attrib = attrib->next;
			continue;
		}
#endif

		/* pointing to at least one attribute which needs to be transmitted */
		memcpy(streamid_firstval,
		       attrib->attribute.talk_listen.StreamID, 8);
		memcpy(destmac_firstval,
		       attrib->attribute.talk_listen.DataFrameParameters.
		       Dest_Addr, 6);
		memcpy(mrpdu_vectorptr->FirstValue_VectorEvents,
		       streamid_firstval, 8);
		memcpy(&(mrpdu_vectorptr->FirstValue_VectorEvents[8]),
		       destmac_firstval, 6);

		mrpdu_vectorptr->FirstValue_VectorEvents[14] =
		    attrib->attribute.talk_listen.DataFrameParameters.
		    Vlan_ID >> 8;
		mrpdu_vectorptr->FirstValue_VectorEvents[15] =
		    (uint8_t) attrib->attribute.talk_listen.
		    DataFrameParameters.Vlan_ID;

		mrpdu_vectorptr->FirstValue_VectorEvents[16] =
		    attrib->attribute.talk_listen.TSpec.MaxFrameSize >> 8;
		mrpdu_vectorptr->FirstValue_VectorEvents[17] =
		    (uint8_t) attrib->attribute.talk_listen.TSpec.MaxFrameSize;

		mrpdu_vectorptr->FirstValue_VectorEvents[18] =
		    attrib->attribute.talk_listen.TSpec.MaxIntervalFrames >> 8;
		mrpdu_vectorptr->FirstValue_VectorEvents[19] =
		    (uint8_t) attrib->attribute.talk_listen.
		    TSpec.MaxIntervalFrames;

		mrpdu_vectorptr->FirstValue_VectorEvents[20] =
		    attrib->attribute.talk_listen.PriorityAndRank;

		mrpdu_vectorptr->FirstValue_VectorEvents[21] =
		    attrib->attribute.talk_listen.AccumulatedLatency >> 24;
		mrpdu_vectorptr->FirstValue_VectorEvents[22] =
		    attrib->attribute.talk_listen.AccumulatedLatency >> 16;
		mrpdu_vectorptr->FirstValue_VectorEvents[23] =
		    attrib->attribute.talk_listen.AccumulatedLatency >> 8;
		mrpdu_vectorptr->FirstValue_VectorEvents[24] =
		    attrib->attribute.talk_listen.AccumulatedLatency;

#if 1
		if (MSRP_TALKER_FAILED_TYPE == type) {
			memcpy(&mrpdu_vectorptr->FirstValue_VectorEvents[25],
			    attrib->attribute.talk_listen.
			    FailureInformation.BridgeID, 8);
			mrpdu_vectorptr->FirstValue_VectorEvents[33] =
			    attrib->attribute.talk_listen.
			    FailureInformation.FailureCode;
		}
#endif

		switch (attrib->applicant.sndmsg) {
		case MRP_SND_IN:
			/*
			 * If 'In' in indicated by the applicant attribute, the
			 * look at the registrar state to determine whether to
			 * send an In (if registrar is also In) or an Mt if the
			 * registrar is either Mt or Lv.
			 */
			if (MRP_IN_STATE == attrib->registrar.mrp_state)
				vectevt[0] = MRPDU_IN;
			else
				vectevt[0] = MRPDU_MT;
			break;
		case MRP_SND_NEW:
			vectevt[0] = MRPDU_NEW;
			break;
		case MRP_SND_LV:
			vectevt[0] = MRPDU_LV;
			break;
		case MRP_SND_JOIN:
			/* IF 'Join' in indicated by the applicant, look at
			 * the corresponding registrar state to determine whether
			 * to send a JoinIn (if the registar state is 'In') or
			 * a JoinMt if the registrar state is MT or LV.
			 */
			if (MRP_IN_STATE == attrib->registrar.mrp_state)
				vectevt[0] = MRPDU_JOININ;
			else
				vectevt[0] = MRPDU_JOINMT;
			break;
		default:
			/* huh? */
			goto oops;
			break;
		}

#ifdef MICREL_1588_PTP
		/* Attribute sent so change state. */
		MSRP_db->mrp_db.registrar_state = attrib->registrar.mrp_state;
		mrp_applicant_chk(&MSRP_db->mrp_db, &attrib->applicant);
#endif

		vectevt_idx = 1;
		numvalues = 1;
		vectevt[1] = 0;
		vectevt[2] = 0;

		/* now attempt to vectorize contiguous other attributes
		 * which also need to be transmitted
		 */

#if 0
		vectidx = 25;
#else
		vectidx = minimum;
#endif
		vattrib = attrib->next;

		while (NULL != vattrib) {
			if (MSRP_TALKER_ADV_TYPE != vattrib->type)
				break;

#if 1
			if ((MSRP_TALKER_ADV_TYPE == type &&
			    vattrib->attribute.talk_listen.
			    FailureInformation.FailureCode) ||
			    (MSRP_TALKER_FAILED_TYPE == type &&
			    !vattrib->attribute.talk_listen.
			    FailureInformation.FailureCode))
				break;
#endif

			if (0 == vattrib->applicant.tx)
				break;

			msrp_increment_streamid(streamid_firstval);
			mmrp_increment_macaddr(destmac_firstval);

			mac_eq = memcmp(vattrib->attribute.talk_listen.StreamID,
					streamid_firstval, 8);

			if (0 != mac_eq)
				break;

#ifdef MICREL_1588_PTP
			mac_eq = memcmp(vattrib->attribute.talk_listen.
				DataFrameParameters.Dest_Addr,
				destmac_firstval, 6);

			if (0 != mac_eq)
				break;
#endif

			vattrib->applicant.tx = 0;

			switch (vattrib->applicant.sndmsg) {
			case MRP_SND_IN:
				/*
				 * If 'In' in indicated by the applicant attribute, the
				 * look at the registrar state to determine whether to
				 * send an In (if registrar is also In) or an Mt if the
				 * registrar is either Mt or Lv.
				 */
				if (MRP_IN_STATE ==
				    vattrib->registrar.mrp_state)
					vectevt[vectevt_idx] = MRPDU_IN;
				else
					vectevt[vectevt_idx] = MRPDU_MT;
				break;
			case MRP_SND_NEW:
				vectevt[vectevt_idx] = MRPDU_NEW;
				break;
			case MRP_SND_LV:
				vectevt[vectevt_idx] = MRPDU_LV;
				break;
			case MRP_SND_JOIN:
				/* IF 'Join' in indicated by the applicant, look at
				 * the corresponding registrar state to determine whether
				 * to send a JoinIn (if the registar state is 'In') or
				 * a JoinMt if the registrar state is MT or LV.
				 */
				if (MRP_IN_STATE == attrib->registrar.mrp_state)
					vectevt[vectevt_idx] = MRPDU_JOININ;
				else
					vectevt[vectevt_idx] = MRPDU_JOINMT;
				break;
			default:
				/* huh? */
				goto oops;
				break;
			}

#ifdef MICREL_1588_PTP
			/* Attribute sent so change state. */
			MSRP_db->mrp_db.registrar_state =
				vattrib->registrar.mrp_state;
			mrp_applicant_chk(&MSRP_db->mrp_db,
				&vattrib->applicant);
#endif

			vectevt_idx++;
			numvalues++;

#ifdef MICREL_1588_PTP
			vattrib = vattrib->next;
#endif
			if (vectevt_idx > 2) {
				vect_3pack = MRPDU_3PACK_ENCODE(vectevt[0],
								vectevt[1],
								vectevt[2]);

				mrpdu_vectorptr->FirstValue_VectorEvents
				    [vectidx] = vect_3pack;
				vectidx++;
				vectevt[0] = 0;
				vectevt[1] = 0;
				vectevt[2] = 0;
				vectevt_idx = 0;
#ifdef MICREL_1588_PTP
				if (&(mrpdu_vectorptr->
				    FirstValue_VectorEvents[vectidx]) >
				    (mrpdu_msg_eof - (1 + 4)))
					break;
#endif
			}

#ifndef MICREL_1588_PTP
			if (&(mrpdu_vectorptr->FirstValue_VectorEvents[vectidx])
			    > (mrpdu_msg_eof - 2))
				goto oops;

			vattrib = vattrib->next;
#endif
		}

		/* handle any trailers */
		if (vectevt_idx > 0) {
			vect_3pack = MRPDU_3PACK_ENCODE(vectevt[0],
							vectevt[1], vectevt[2]);

			mrpdu_vectorptr->FirstValue_VectorEvents[vectidx] =
			    vect_3pack;
			vectidx++;
		}

#ifndef MICREL_1588_PTP
		if (&(mrpdu_vectorptr->FirstValue_VectorEvents[vectidx]) >
		    (mrpdu_msg_eof - 2))
			goto oops;
#endif

#ifdef MICREL_1588_PTP
		VectorHeader = MRPDU_VECT_NUMVALUES(numvalues);

		if (lva)
			VectorHeader |= MRPDU_VECT_LVA(0xFFFF);

		unaligned = (uint8_t *) &mrpdu_vectorptr->VectorHeader;
		unaligned[0] = (uint8_t)(VectorHeader >> 8);
		unaligned[1] = (uint8_t) VectorHeader;
#else
		mrpdu_vectorptr->VectorHeader = MRPDU_VECT_NUMVALUES(numvalues);

		if (lva)
			mrpdu_vectorptr->VectorHeader |= MRPDU_VECT_LVA(0xFFFF);

		mrpdu_vectorptr->VectorHeader =
		    htons(mrpdu_vectorptr->VectorHeader);
#endif

		mrpdu_msg_ptr =
		    &(mrpdu_vectorptr->FirstValue_VectorEvents[vectidx]);
		mrpdu_vectorptr = (mrpdu_vectorattrib_t *) mrpdu_msg_ptr;

#ifdef MICREL_1588_PTP
		attrib = vattrib;
#else
		attrib = attrib->next;
#endif

	}
#ifdef MICREL_1588_PTP
	MSRP_db->mrp_db.tx_attrib = attrib;
#endif

	if (mrpdu_vectorptr == (mrpdu_vectorattrib_t *) & (mrpdu_msg->Data[2])) {
		*bytes_used = 0;
		return 0;
	}

	/* endmark */
	*mrpdu_msg_ptr = 0;
	mrpdu_msg_ptr++;
	*mrpdu_msg_ptr = 0;
	mrpdu_msg_ptr++;

	*bytes_used = (mrpdu_msg_ptr - msgbuf);

	attriblistlen = mrpdu_msg_ptr - &(mrpdu_msg->Data[2]);
	mrpdu_msg->Data[0] = (uint8_t) (attriblistlen >> 8);
	mrpdu_msg->Data[1] = (uint8_t) attriblistlen;
#ifdef MICREL_1588_PTP
	/* Not all attributes sent. */
	if (attrib)
		return -1;
#endif
	return 0;
 oops:
	/* an internal error - caller should assume TXLAF */
	*bytes_used = 0;
	return -1;
}

int
msrp_emit_listenvectors(unsigned char *msgbuf, unsigned char *msgbuf_eof,
			int *bytes_used, int lva)
{
	mrpdu_vectorattrib_t *mrpdu_vectorptr;
	mrpdu_message_t *mrpdu_msg;
	unsigned char *mrpdu_msg_ptr = msgbuf;
	unsigned char *mrpdu_msg_eof = msgbuf_eof;
	uint16_t numvalues;
	uint8_t vect_3pack;
	uint8_t vect_4pack;
	int vectidx;
	int attriblistlen;
	int vectevt[4];
	int vectevt_idx;
	int *listen_declare = NULL;
	int listen_declare_sz = 64;
	int listen_declare_idx = 0;
	int listen_declare_end = 0;
	uint8_t streamid_firstval[8];
	struct msrp_attribute *attrib, *vattrib;
	int mac_eq;
#ifdef MICREL_1588_PTP
	int nextval;
#endif
#ifdef MICREL_1588_PTP
	uint16_t VectorHeader;
	uint8_t *unaligned;
#endif

#ifdef MICREL_1588_PTP
	if (mrpdu_msg_ptr > (mrpdu_msg_eof - (8 + 6 + 2 + 4)))
#else
	/* need at least 13 bytes for a single vector */
	if (mrpdu_msg_ptr > (mrpdu_msg_eof - 13))
#endif
		goto oops;

	mrpdu_msg = (mrpdu_message_t *) mrpdu_msg_ptr;
	mrpdu_msg->AttributeType = MSRP_LISTENER_TYPE;
	mrpdu_msg->AttributeLength = 8;

	listen_declare = (int *)malloc(listen_declare_sz * sizeof(int));
	if (NULL == listen_declare)
		goto oops;

#ifdef MICREL_1588_PTP
	msrp_prepare_tx(MSRP_LISTENER_TYPE, lva);
#endif

#ifndef MICREL_1588_PTP
	/* if we have a listener type registered, always send out an update,
	 * so mark all as ready.
	 */
	attrib = MSRP_db->attrib_list;
	while (attrib) {
		if (MSRP_LISTENER_TYPE == attrib->type) {
			attrib->applicant.tx = 1;
		}
		attrib = attrib->next;
	}
#endif

#ifdef MICREL_1588_PTP
	attrib = MSRP_db->mrp_db.tx_attrib;
	if (attrib) {
		if (MSRP_LISTENER_TYPE != attrib->type) {
			*bytes_used = 0;
			return 0;
		}
	} else
#endif
	attrib = MSRP_db->attrib_list;
	mrpdu_vectorptr = (mrpdu_vectorattrib_t *) & (mrpdu_msg->Data[2]);

#ifdef MICREL_1588_PTP
	while ((mrpdu_msg_ptr <= (mrpdu_msg_eof - (8 + 2 + 2 + 4))) &&
	       (NULL != attrib)) {
#else
	while ((mrpdu_msg_ptr < (mrpdu_msg_eof - 2)) && (NULL != attrib)) {
#endif

		if (MSRP_LISTENER_TYPE != attrib->type) {
			attrib = attrib->next;
			continue;
		}

		if (0 == attrib->applicant.tx) {
#ifdef MICREL_1588_PTP
			MSRP_db->mrp_db.registrar_state =
				attrib->registrar.mrp_state;
			mrp_applicant_chk(&MSRP_db->mrp_db,
				&attrib->applicant);
#endif
			attrib = attrib->next;
			continue;
		}
#ifdef MICREL_1588_PTP_
		if (MRP_ENCODE_OPTIONAL == attrib->applicant.encode) {
			attrib->applicant.tx = 0;
			attrib = attrib->next;
			continue;
		}
#endif

		listen_declare_idx = 0;

		/* if we have a listener type registered, we always will
		 * send out an update. We also don't bother trying to
		 * insert IGNORES between stream IDs - we only send out
		 * contiguous active streams in messages
		 */

		/* pointing to at least one attribute which needs to be transmitted */
		memcpy(streamid_firstval,
		       attrib->attribute.talk_listen.StreamID, 8);
		memcpy(&(mrpdu_vectorptr->FirstValue_VectorEvents),
		       attrib->attribute.talk_listen.StreamID, 8);

		switch (attrib->applicant.sndmsg) {
		case MRP_SND_IN:
			/*
			 * If 'In' in indicated by the applicant attribute, the
			 * look at the registrar state to determine whether to
			 * send an In (if registrar is also In) or an Mt if the
			 * registrar is either Mt or Lv.
			 */
			if (MRP_IN_STATE == attrib->registrar.mrp_state)
				vectevt[0] = MRPDU_IN;
			else
				vectevt[0] = MRPDU_MT;
			break;
		case MRP_SND_NEW:
			vectevt[0] = MRPDU_NEW;
			break;
		case MRP_SND_LV:
			vectevt[0] = MRPDU_LV;
			break;
		case MRP_SND_JOIN:
			/* IF 'Join' in indicated by the applicant, look at
			 * the corresponding registrar state to determine whether
			 * to send a JoinIn (if the registar state is 'In') or
			 * a JoinMt if the registrar state is MT or LV.
			 */
			if (MRP_IN_STATE == attrib->registrar.mrp_state)
				vectevt[0] = MRPDU_JOININ;
			else
				vectevt[0] = MRPDU_JOINMT;
			break;
		default:
			/* huh? */
			goto oops;
			break;
		}

#ifdef MICREL_1588_PTP
		/* Attribute sent so change state. */
		MSRP_db->mrp_db.registrar_state = attrib->registrar.mrp_state;
		mrp_applicant_chk(&MSRP_db->mrp_db, &attrib->applicant);
#endif

		vectevt_idx = 1;
		numvalues = 1;
		vectevt[1] = 0;
		vectevt[2] = 0;

		if (listen_declare_sz == (listen_declare_idx + 1)) {
			listen_declare =
			    (int *)realloc(listen_declare,
					   (64 +
					    listen_declare_sz) * sizeof(int));
			if (NULL == listen_declare)
				goto oops;

			listen_declare_sz += 64;
		}

		listen_declare[listen_declare_idx] = attrib->substate;
		listen_declare_idx++;

		/* now attempt to vectorize contiguous other attributes
		 * which also need to be transmitted
		 */

		vectidx = 8;
		vattrib = attrib->next;

#ifdef MICREL_1588_PTP
		/* See if next value is close enough for efficient encoding. */
		nextval = 0;
		if (vattrib)
			nextval = vattrib->nextval;
#endif
		while (NULL != vattrib) {
			if (MSRP_LISTENER_TYPE != vattrib->type)
				break;

#ifdef MICREL_1588_PTP
			/* No need to fill dummy attribute. */
			if (!nextval) {
#endif
			if (0 == vattrib->applicant.tx)
				break;

			msrp_increment_streamid(streamid_firstval);

			mac_eq = memcmp(vattrib->attribute.talk_listen.StreamID,
					streamid_firstval, 8);

			if (0 != mac_eq)
				break;

			vattrib->applicant.tx = 0;

			switch (vattrib->applicant.sndmsg) {
			case MRP_SND_IN:
				/*
				 * If 'In' in indicated by the applicant attribute, the
				 * look at the registrar state to determine whether to
				 * send an In (if registrar is also In) or an Mt if the
				 * registrar is either Mt or Lv.
				 */
				if (MRP_IN_STATE ==
				    vattrib->registrar.mrp_state)
					vectevt[vectevt_idx] = MRPDU_IN;
				else
					vectevt[vectevt_idx] = MRPDU_MT;
				break;
			case MRP_SND_NEW:
				vectevt[vectevt_idx] = MRPDU_NEW;
				break;
			case MRP_SND_LV:
				vectevt[vectevt_idx] = MRPDU_LV;
				break;
			case MRP_SND_JOIN:
				/* IF 'Join' in indicated by the applicant, look at
				 * the corresponding registrar state to determine whether
				 * to send a JoinIn (if the registar state is 'In') or
				 * a JoinMt if the registrar state is MT or LV.
				 */
				if (MRP_IN_STATE == attrib->registrar.mrp_state)
					vectevt[vectevt_idx] = MRPDU_JOININ;
				else
					vectevt[vectevt_idx] = MRPDU_JOINMT;
				break;
			default:
				/* huh? */
				goto oops;
				break;
			}

#ifdef MICREL_1588_PTP
			/* Attribute sent so change state. */
			MSRP_db->mrp_db.registrar_state =
				vattrib->registrar.mrp_state;
			mrp_applicant_chk(&MSRP_db->mrp_db,
				&vattrib->applicant);
			} else {
				/* Fill in dummy attribute. */
				msrp_increment_streamid(streamid_firstval);
				vectevt[vectevt_idx] = MRPDU_NEW;
			}
#endif
			vectevt_idx++;
			numvalues++;

			if (listen_declare_sz == (listen_declare_idx + 1)) {
				listen_declare =
				    (int *)realloc(listen_declare,
						   (64 +
						    listen_declare_sz) *
						   sizeof(int));
				listen_declare_sz += 64;
			}

#ifdef MICREL_1588_PTP
			/* Fill in dummpy declaration. */
			if (nextval)
				listen_declare[listen_declare_idx] =
					MSRP_LISTENER_IGNORE;
			else
#endif
			listen_declare[listen_declare_idx] = vattrib->substate;
			listen_declare_idx++;

#ifdef MICREL_1588_PTP
			if (nextval)
				--nextval;
			else {
#endif
			vattrib = vattrib->next;
#ifdef MICREL_1588_PTP
				if (vattrib)
					nextval = vattrib->nextval;
			}
#endif
			if (vectevt_idx > 2) {
				vect_3pack = MRPDU_3PACK_ENCODE(vectevt[0],
								vectevt[1],
								vectevt[2]);

				mrpdu_vectorptr->FirstValue_VectorEvents
				    [vectidx] = vect_3pack;
				vectidx++;
				vectevt[0] = 0;
				vectevt[1] = 0;
				vectevt[2] = 0;
				vectevt_idx = 0;
#ifdef MICREL_1588_PTP
				if (&(mrpdu_vectorptr->
				    FirstValue_VectorEvents[vectidx]) >
				    (mrpdu_msg_eof - ((numvalues + 3) / 4 + 6)))
					break;
#endif
			}

#ifndef MICREL_1588_PTP
			if (&(mrpdu_vectorptr->FirstValue_VectorEvents[vectidx])
			    > (mrpdu_msg_eof - 2))
				goto oops;

			vattrib = vattrib->next;
#endif
		}

		/* handle any trailers */
		if (vectevt_idx > 0) {
			vect_3pack = MRPDU_3PACK_ENCODE(vectevt[0],
							vectevt[1], vectevt[2]);

			mrpdu_vectorptr->FirstValue_VectorEvents[vectidx] =
			    vect_3pack;
			vectidx++;
		}

		/* now emit the 4-packed events */

		listen_declare_end = listen_declare_idx;

		for (listen_declare_idx = 0;
		     listen_declare_idx < ((listen_declare_end / 4) * 4);
		     listen_declare_idx += 4) {

#ifndef MICREL_1588_PTP
			if (&(mrpdu_vectorptr->FirstValue_VectorEvents[vectidx])
			    > (mrpdu_msg_eof - 2))
				goto oops;
#endif

			vect_4pack =
			    MRPDU_4PACK_ENCODE(listen_declare
					       [listen_declare_idx],
					       listen_declare
					       [listen_declare_idx + 1],
					       listen_declare
					       [listen_declare_idx + 2],
					       listen_declare
					       [listen_declare_idx + 3]);

			mrpdu_vectorptr->FirstValue_VectorEvents
			    [vectidx] = vect_4pack;
			vectidx++;

			if (&(mrpdu_vectorptr->FirstValue_VectorEvents[vectidx])
#ifdef MICREL_1588_PTP
			    > (mrpdu_msg_eof - (1 + 4)))
#else
			    > (mrpdu_msg_eof - 3))
#endif
				goto oops;
		}

		/* handle any trailers */
		vectevt_idx = 0;
		vectevt[0] = 0;
		vectevt[1] = 0;
		vectevt[2] = 0;
		vectevt[3] = 0;
		while (listen_declare_idx < listen_declare_end) {
			vectevt[vectevt_idx] =
			    listen_declare[listen_declare_idx];
			listen_declare_idx++;
			vectevt_idx++;
		}
		if (vectevt_idx) {
			vect_4pack = MRPDU_4PACK_ENCODE(vectevt[0],
							vectevt[1],
							vectevt[2], vectevt[3]);

			mrpdu_vectorptr->FirstValue_VectorEvents[vectidx] =
			    vect_4pack;
			vectidx++;
		}

#ifndef MICREL_1588_PTP
		if (&(mrpdu_vectorptr->FirstValue_VectorEvents[vectidx]) >
		    (mrpdu_msg_eof - 2))
			goto oops;
#endif

#ifdef MICREL_1588_PTP
		VectorHeader = MRPDU_VECT_NUMVALUES(numvalues);

		if (lva)
			VectorHeader |= MRPDU_VECT_LVA(0xFFFF);

		unaligned = (uint8_t *) &mrpdu_vectorptr->VectorHeader;
		unaligned[0] = (uint8_t)(VectorHeader >> 8);
		unaligned[1] = (uint8_t) VectorHeader;
#else
		mrpdu_vectorptr->VectorHeader = MRPDU_VECT_NUMVALUES(numvalues);

		if (lva)
			mrpdu_vectorptr->VectorHeader |= MRPDU_VECT_LVA(0xFFFF);

		mrpdu_vectorptr->VectorHeader =
		    htons(mrpdu_vectorptr->VectorHeader);
#endif

		mrpdu_msg_ptr =
		    &(mrpdu_vectorptr->FirstValue_VectorEvents[vectidx]);

#ifdef MICREL_1588_PTP
		attrib = vattrib;
#else
		attrib = attrib->next;
#endif

		mrpdu_vectorptr = (mrpdu_vectorattrib_t *) mrpdu_msg_ptr;
	}
#ifdef MICREL_1588_PTP
	MSRP_db->mrp_db.tx_attrib = attrib;
#endif

	if (mrpdu_vectorptr == (mrpdu_vectorattrib_t *) & (mrpdu_msg->Data[2])) {
		if (listen_declare)
			free(listen_declare);
		*bytes_used = 0;
		return 0;
	}

	/* endmark */
	*mrpdu_msg_ptr = 0;
	mrpdu_msg_ptr++;
	*mrpdu_msg_ptr = 0;
	mrpdu_msg_ptr++;

	*bytes_used = (mrpdu_msg_ptr - msgbuf);

	attriblistlen = mrpdu_msg_ptr - &(mrpdu_msg->Data[2]);
	mrpdu_msg->Data[0] = (uint8_t) (attriblistlen >> 8);
	mrpdu_msg->Data[1] = (uint8_t) attriblistlen;

	free(listen_declare);
#ifdef MICREL_1588_PTP
	/* Not all attributes sent. */
	if (attrib)
		return -1;
#endif
	return 0;
 oops:
	/* an internal error - caller should assume TXLAF */
	if (listen_declare)
		free(listen_declare);
	*bytes_used = 0;
	return -1;
}

int msrp_txpdu(void)
{
	unsigned char *msgbuf, *msgbuf_wrptr;
	int msgbuf_len;
	int bytes = 0;
	eth_hdr_t *eth;
	mrpdu_t *mrpdu;
	unsigned char *mrpdu_msg_ptr;
	unsigned char *mrpdu_msg_eof;
	int rc;
	int lva = 0;

	msgbuf = (unsigned char *)malloc(MAX_FRAME_SIZE);
	if (NULL == msgbuf)
		return -1;
	msgbuf_len = 0;

	msgbuf_wrptr = msgbuf;

	eth = (eth_hdr_t *) msgbuf_wrptr;

	/* note that MSRP frames should always be untagged (no vlan) */
	eth->typelen = htons(MSRP_ETYPE);
	memcpy(eth->destaddr, MSRP_ADDR, sizeof(eth->destaddr));
	memcpy(eth->srcaddr, STATION_ADDR, sizeof(eth->srcaddr));

	msgbuf_wrptr += sizeof(eth_hdr_t);

	mrpdu = (mrpdu_t *) msgbuf_wrptr;

	mrpdu->ProtocolVersion = MSRP_PROT_VER;
	mrpdu_msg_ptr = MRPD_GET_MRPDU_MESSAGE_LIST(mrpdu);
	mrpdu_msg_eof = (unsigned char *)msgbuf + MAX_FRAME_SIZE;

#ifndef MICREL_1588_PTP
	if (MSRP_db->mrp_db.lva.tx) {
		lva = 1;
		MSRP_db->mrp_db.lva.tx = 0;
	}
#endif

#ifdef MICREL_1588_PTP
	/* Check sending LeaveAll for talker attribute type. */
	lva = 0;
	if (MSRP_db->mrp_db.lva.tx & 1)
		lva = 1;
#endif
	rc = msrp_emit_talkvectors(mrpdu_msg_ptr, mrpdu_msg_eof, &bytes, lva,
		MSRP_TALKER_ADV_TYPE);
#ifndef MICREL_1588_PTP
	if (-1 == rc)
		goto out;
#endif

	mrpdu_msg_ptr += bytes;

#ifdef MICREL_1588_PTP
	/* LeaveAll for talker attribute type sent. */
	if (bytes)
		MSRP_db->mrp_db.lva.tx &= ~1;

	/* No more space. */
	if (-1 == rc)
		goto send;

	/* Check sending LeaveAll for talker failed attribute type. */
	lva = 0;
	if (MSRP_db->mrp_db.lva.tx & 2)
		lva = 1;
	rc = msrp_emit_talkvectors(mrpdu_msg_ptr, mrpdu_msg_eof, &bytes, lva,
		MSRP_TALKER_FAILED_TYPE);

	mrpdu_msg_ptr += bytes;

	/* LeaveAll for talker failed attribute type sent. */
	if (bytes)
		MSRP_db->mrp_db.lva.tx &= ~2;

	/* No more space. */
	if (-1 == rc)
		goto send;
#else
	if (mrpdu_msg_ptr >= (mrpdu_msg_eof - 2))
		goto out;
#endif

#ifdef MICREL_1588_PTP
	/* Check sending LeaveAll for listener attribute type. */
	lva = 0;
	if (MSRP_db->mrp_db.lva.tx & 4)
		lva = 1;
#endif
	rc = msrp_emit_listenvectors(mrpdu_msg_ptr, mrpdu_msg_eof, &bytes, lva);
#ifndef MICREL_1588_PTP
	if (-1 == rc)
		goto out;
#endif

	mrpdu_msg_ptr += bytes;

#ifdef MICREL_1588_PTP
	/* LeaveAll for listener attribute type sent. */
	if (bytes)
		MSRP_db->mrp_db.lva.tx &= ~4;

	/* No more space. */
	if (-1 == rc)
		goto send;

	/* Check sending LeaveAll for domain attribute type. */
	lva = 0;
	if (MSRP_db->mrp_db.lva.tx & 8)
		lva = 1;
#endif
	rc = msrp_emit_domainvectors(mrpdu_msg_ptr, mrpdu_msg_eof, &bytes, lva);
#ifndef MICREL_1588_PTP
	if (-1 == rc)
		goto out;
#endif

	mrpdu_msg_ptr += bytes;

#ifdef MICREL_1588_PTP
	/* LeaveAll for domain attribute type sent. */
	if (bytes)
		MSRP_db->mrp_db.lva.tx &= ~8;

	/* No more space. */
	if (-1 == rc)
		goto send;

send:
#endif

	if (mrpdu_msg_ptr == MRPD_GET_MRPDU_MESSAGE_LIST(mrpdu)) {
		goto out;	/* nothing to send */
	}

	/* endmark */
	if (mrpdu_msg_ptr <= (mrpdu_msg_eof - 2)) {
		*mrpdu_msg_ptr = 0;
		mrpdu_msg_ptr++;
		*mrpdu_msg_ptr = 0;
		mrpdu_msg_ptr++;
	} else
		goto out;

	msgbuf_len = mrpdu_msg_ptr - msgbuf;

	bytes = mrpd_send(msrp_socket, msgbuf, msgbuf_len, 0);
#if LOG_MSRP
	mrpd_log_printf("MSRP send PDU\n");
#endif
	if (bytes <= 0)
		goto out;
#ifdef MICREL_1588_PTP
	do {
	time_t ticks = time(NULL);
if (ofp) {
fprintf(ofp, " %s %ld %ld; %d\n", __func__,
ticks - start_time, ticks - last_event_time, lva);
fflush(ofp);
}
	} while (0);
#endif

#ifndef MICREL_1588_PTP
	free(msgbuf);
	return 0;
#endif
 out:
	free(msgbuf);
#ifdef MICREL_1588_PTP
if (ofp && !bytes && MSRP_db->attrib_list)
fprintf(ofp, " %s nothing to send\n", __func__);
	return rc;
#else
	/* caller should assume TXLAF */
	return -1;
#endif
}

#ifdef MICREL_1588_PTP
static void to_domain(struct msrp_attribute *rattrib,
	struct SRP_domain_class *domain)
{
	domain->id = rattrib->attribute.domain.SRclassID;
	domain->priority = rattrib->attribute.domain.SRclassPriority;
	domain->vlan_id = rattrib->attribute.domain.SRclassVID;
}

static void to_listener(struct msrp_attribute *rattrib,
	struct SRP_listener *listener)
{
	memcpy(listener->id, rattrib->attribute.talk_listen.StreamID, 8);
	listener->substate = rattrib->substate;
}

static void to_talker(struct msrp_attribute *rattrib,
	struct SRP_talker *talker)
{
	memcpy(talker->id, rattrib->attribute.talk_listen.StreamID, 8);
	memcpy(talker->dest,
		rattrib->attribute.talk_listen.DataFrameParameters.Dest_Addr,
		6);
	talker->vlan_id =
		rattrib->attribute.talk_listen.DataFrameParameters.Vlan_ID;
	talker->priority = rattrib->attribute.talk_listen.PriorityAndRank >> 5;
	talker->rank = !!
		(rattrib->attribute.talk_listen.PriorityAndRank & 0x10);
	talker->MaxFrameSize =
		rattrib->attribute.talk_listen.TSpec.MaxFrameSize;
	talker->MaxIntervalFrames =
		rattrib->attribute.talk_listen.TSpec.MaxIntervalFrames;
if (talker->MaxIntervalFrames >= 4000) {
	if (3 == talker->priority)
		talker->MaxIntervalFrames /= 8000;
	else
		talker->MaxIntervalFrames /= 4000;
}
	talker->AccumulatedLatency =
		rattrib->attribute.talk_listen.AccumulatedLatency;
	if (rattrib->attribute.talk_listen.FailureInformation.FailureCode) {
		memcpy(talker->bridge_id,
			rattrib->attribute.talk_listen.
			FailureInformation.BridgeID, 8);
		talker->FailureCode =
			rattrib->attribute.talk_listen.
			FailureInformation.FailureCode;
	} else {
		memset(talker->bridge_id, 0, 8);
		talker->FailureCode = RFC_NO_ERROR;
	}
}

static int msrp_propagate(struct msrp_attribute *rattrib, int notify)
{
	int rc = 0;

	if (MSRP_DOMAIN_TYPE == rattrib->type) {
		struct SRP_domain_class domain;

		to_domain(rattrib, &domain);
		if (MRP_NOTIFY_LV == notify)
			rc = set_domain_lv(fd, mrp_index + 1, &domain);
		else
			rc = set_domain_rx(fd, mrp_index + 1, &domain);

		/* No need to propagate. */
		return 0;
	} else if (MSRP_LISTENER_TYPE == rattrib->type) {
		struct SRP_listener listener;

		to_listener(rattrib, &listener);
		if (MRP_NOTIFY_LV == notify)
			rc = set_listener_lv(fd, mrp_index + 1, &listener);
		else
			rc = set_listener_rx(fd, mrp_index + 1, &listener);
		rc = handle_propagation(rc, notify);
		if (rc)
			goto msrp_propagate_done;

	} else {
		struct SRP_talker talker;

		to_talker(rattrib, &talker);
		if (MRP_NOTIFY_LV == notify)
			rc = set_talker_lv(fd, mrp_index + 1, &talker);
		else
			rc = set_talker_rx(fd, mrp_index + 1, &talker);
		rc = handle_propagation(rc, notify);
		if (rc)
			goto msrp_propagate_done;
	}

msrp_propagate_done:
	return rc;
}

#endif

int msrp_send_notifications(struct msrp_attribute *attrib, int notify)
{
	char *msgbuf;
	char *variant;
	char *regsrc;
#ifdef MICREL_1588_PTP
	struct sockaddr_in *new_client;
	int old_index;
	int reclaim;
	char mrp_state[20];
#else
	char mrp_state[8];
#endif
	client_t *client;

	if (NULL == attrib)
		return -1;

	msgbuf = (char *)malloc(MAX_MRPD_CMDSZ);
	if (NULL == msgbuf)
		return -1;

	variant = regsrc = NULL;

	variant = (char *)malloc(128);
	regsrc = (char *)malloc(128);

	if ((NULL == variant) || (NULL == regsrc))
		goto free_msgbuf;

	memset(msgbuf, 0, MAX_MRPD_CMDSZ);

	if (MSRP_LISTENER_TYPE == attrib->type) {
		sprintf(variant, "L:D=%d,S=%02x%02x%02x%02x%02x%02x%02x%02x",
			attrib->substate,
			attrib->attribute.talk_listen.StreamID[0],
			attrib->attribute.talk_listen.StreamID[1],
			attrib->attribute.talk_listen.StreamID[2],
			attrib->attribute.talk_listen.StreamID[3],
			attrib->attribute.talk_listen.StreamID[4],
			attrib->attribute.talk_listen.StreamID[5],
			attrib->attribute.talk_listen.StreamID[6],
			attrib->attribute.talk_listen.StreamID[7]);
	} else if (MSRP_DOMAIN_TYPE == attrib->type) {
		sprintf(variant, "D:C=%d,P=%d,V=%04x",
			attrib->attribute.domain.SRclassID,
			attrib->attribute.domain.SRclassPriority,
			attrib->attribute.domain.SRclassVID);
	} else {
		sprintf(variant, "T:S=%02x%02x%02x%02x%02x%02x%02x%02x"
			",A=%02x%02x%02x%02x%02x%02x"
			",V=%04x"
			",Z=%d"
			",I=%d"
			",P=%d"
			",L=%d"
			",B=%02x%02x%02x%02x%02x%02x%02x%02x"
			",C=%d",
			attrib->attribute.talk_listen.StreamID[0],
			attrib->attribute.talk_listen.StreamID[1],
			attrib->attribute.talk_listen.StreamID[2],
			attrib->attribute.talk_listen.StreamID[3],
			attrib->attribute.talk_listen.StreamID[4],
			attrib->attribute.talk_listen.StreamID[5],
			attrib->attribute.talk_listen.StreamID[6],
			attrib->attribute.talk_listen.StreamID[7],
			attrib->attribute.talk_listen.DataFrameParameters.
			Dest_Addr[0],
			attrib->attribute.talk_listen.DataFrameParameters.
			Dest_Addr[1],
			attrib->attribute.talk_listen.DataFrameParameters.
			Dest_Addr[2],
			attrib->attribute.talk_listen.DataFrameParameters.
			Dest_Addr[3],
			attrib->attribute.talk_listen.DataFrameParameters.
			Dest_Addr[4],
			attrib->attribute.talk_listen.DataFrameParameters.
			Dest_Addr[5],
			attrib->attribute.talk_listen.DataFrameParameters.
			Vlan_ID,
			attrib->attribute.talk_listen.TSpec.MaxFrameSize,
			attrib->attribute.talk_listen.TSpec.MaxIntervalFrames,
			attrib->attribute.talk_listen.PriorityAndRank,
			attrib->attribute.talk_listen.AccumulatedLatency,
			attrib->attribute.talk_listen.FailureInformation.
			BridgeID[0],
			attrib->attribute.talk_listen.FailureInformation.
			BridgeID[1],
			attrib->attribute.talk_listen.FailureInformation.
			BridgeID[2],
			attrib->attribute.talk_listen.FailureInformation.
			BridgeID[3],
			attrib->attribute.talk_listen.FailureInformation.
			BridgeID[4],
			attrib->attribute.talk_listen.FailureInformation.
			BridgeID[5],
			attrib->attribute.talk_listen.FailureInformation.
			BridgeID[6],
			attrib->attribute.talk_listen.FailureInformation.
			BridgeID[7],
			attrib->attribute.talk_listen.FailureInformation.
			FailureCode);
	}

	sprintf(regsrc, "R=%02x%02x%02x%02x%02x%02x",
		attrib->registrar.macaddr[0],
		attrib->registrar.macaddr[1],
		attrib->registrar.macaddr[2],
		attrib->registrar.macaddr[3],
		attrib->registrar.macaddr[4], attrib->registrar.macaddr[5]);

	mrp_decode_state(&attrib->registrar, &attrib->applicant,
				 mrp_state, sizeof(mrp_state));

	switch (notify) {
	case MRP_NOTIFY_NEW:
		sprintf(msgbuf, "SNE %s %s %s\n", variant, regsrc, mrp_state);
		break;
	case MRP_NOTIFY_JOIN:
		sprintf(msgbuf, "SJO %s %s %s\n", variant, regsrc, mrp_state);
		break;
	case MRP_NOTIFY_LV:
		sprintf(msgbuf, "SLE %s %s %s\n", variant, regsrc, mrp_state);
		break;
	default:
		goto free_msgbuf;
		break;
	}

#ifdef MICREL_1588_PTP
if (ofp)
fprintf(ofp, "%s %s", __func__, msgbuf);
	new_client = MSRP_db->mrp_db.new_client;
	reclaim = MSRP_db->mrp_db.reclaim;
	if (mrp_port > 1 && !new_client && reclaim != 1) {
		int rc = msrp_propagate(attrib, notify);

		/* Skip notifying the host. */
		if (rc != 1)
			goto free_msgbuf;
	}
	old_index = mrp_index;
	mrp_index = 0;
	MSRP_db = MSRP_dbs[mrp_index];
#endif
	client = MSRP_db->mrp_db.clients;
	while (NULL != client) {
#ifdef MICREL_1588_PTP
		/* Only send to new client if there is one. */
		if (!new_client || !memcmp(new_client, &client->client,
		    sizeof(struct sockaddr_in)))
#endif
		mrpd_send_ctl_msg(&(client->client), msgbuf, MAX_MRPD_CMDSZ);
		client = client->next;
	}
#ifdef MICREL_1588_PTP
	mrp_index = old_index;
	MSRP_db = MSRP_dbs[mrp_index];
#endif

 free_msgbuf:
	if (regsrc)
		free(regsrc);
	if (variant)
		free(variant);
	free(msgbuf);
	return 0;
}

int msrp_dumptable(struct sockaddr_in *client)
{
	char *msgbuf;
	char *msgbuf_wrptr;
	char *stage;
	char *variant;
	char *regsrc;
	struct msrp_attribute *attrib;
	int m = 0;
	int n;
#ifdef MICREL_1588_PTP
	char mrp_state[20];

	if (!client)
		return 0;
#else
	char mrp_state[8];
#endif

	msgbuf = (char *)malloc(MAX_MRPD_CMDSZ);
	if (NULL == msgbuf)
		return -1;

	stage = variant = regsrc = NULL;

	stage = (char *)malloc(128);
	variant = (char *)malloc(128);
	regsrc = (char *)malloc(128);

	if ((NULL == stage) || (NULL == variant) || (NULL == regsrc))
		goto free_msgbuf;

	memset(msgbuf, 0, MAX_MRPD_CMDSZ);

	msgbuf_wrptr = msgbuf;

	attrib = MSRP_db->attrib_list;
	if (attrib == NULL) {
		sprintf(msgbuf, "MSRP:Empty\n");
	}

	while (NULL != attrib) {
		if (MSRP_LISTENER_TYPE == attrib->type) {
			sprintf(variant,
				"L:D=%d,S=%02x%02x%02x%02x%02x%02x%02x%02x",
				attrib->substate,
				attrib->attribute.talk_listen.StreamID[0],
				attrib->attribute.talk_listen.StreamID[1],
				attrib->attribute.talk_listen.StreamID[2],
				attrib->attribute.talk_listen.StreamID[3],
				attrib->attribute.talk_listen.StreamID[4],
				attrib->attribute.talk_listen.StreamID[5],
				attrib->attribute.talk_listen.StreamID[6],
				attrib->attribute.talk_listen.StreamID[7]);
		} else if (MSRP_DOMAIN_TYPE == attrib->type) {
			sprintf(variant, "D:C=%d,P=%d,V=%04x",
				attrib->attribute.domain.SRclassID,
				attrib->attribute.domain.SRclassPriority,
				attrib->attribute.domain.SRclassVID);
		} else {
			sprintf(variant, "T:S=%02x%02x%02x%02x%02x%02x%02x%02x"
				",A=%02x%02x%02x%02x%02x%02x"
				",V=%04x"
				",Z=%d"
				",I=%d"
				",P=%d"
				",L=%d"
				",B=%02x%02x%02x%02x%02x%02x%02x%02x"
				",C=%d",
				attrib->attribute.talk_listen.StreamID[0],
				attrib->attribute.talk_listen.StreamID[1],
				attrib->attribute.talk_listen.StreamID[2],
				attrib->attribute.talk_listen.StreamID[3],
				attrib->attribute.talk_listen.StreamID[4],
				attrib->attribute.talk_listen.StreamID[5],
				attrib->attribute.talk_listen.StreamID[6],
				attrib->attribute.talk_listen.StreamID[7],
				attrib->attribute.talk_listen.
				DataFrameParameters.Dest_Addr[0],
				attrib->attribute.talk_listen.
				DataFrameParameters.Dest_Addr[1],
				attrib->attribute.talk_listen.
				DataFrameParameters.Dest_Addr[2],
				attrib->attribute.talk_listen.
				DataFrameParameters.Dest_Addr[3],
				attrib->attribute.talk_listen.
				DataFrameParameters.Dest_Addr[4],
				attrib->attribute.talk_listen.
				DataFrameParameters.Dest_Addr[5],
				attrib->attribute.talk_listen.
				DataFrameParameters.Vlan_ID,
				attrib->attribute.talk_listen.TSpec.
				MaxFrameSize,
				attrib->attribute.talk_listen.TSpec.
				MaxIntervalFrames,
				attrib->attribute.talk_listen.PriorityAndRank,
				attrib->attribute.talk_listen.
				AccumulatedLatency,
				attrib->attribute.talk_listen.
				FailureInformation.BridgeID[0],
				attrib->attribute.talk_listen.
				FailureInformation.BridgeID[1],
				attrib->attribute.talk_listen.
				FailureInformation.BridgeID[2],
				attrib->attribute.talk_listen.
				FailureInformation.BridgeID[3],
				attrib->attribute.talk_listen.
				FailureInformation.BridgeID[4],
				attrib->attribute.talk_listen.
				FailureInformation.BridgeID[5],
				attrib->attribute.talk_listen.
				FailureInformation.BridgeID[6],
				attrib->attribute.talk_listen.
				FailureInformation.BridgeID[7],
				attrib->attribute.talk_listen.
				FailureInformation.FailureCode);
		}

		mrp_decode_state(&attrib->registrar, &attrib->applicant,
				 mrp_state, sizeof(mrp_state));

		sprintf(regsrc, "R=%02x%02x%02x%02x%02x%02x %s",
			attrib->registrar.macaddr[0],
			attrib->registrar.macaddr[1],
			attrib->registrar.macaddr[2],
			attrib->registrar.macaddr[3],
			attrib->registrar.macaddr[4],
			attrib->registrar.macaddr[5], mrp_state);

		sprintf(stage, "%s %s\n", variant, regsrc);

		n = sprintf(msgbuf_wrptr, "%s", stage);
		if (m < n)
			m = n;
		msgbuf_wrptr += strlen(stage);
		attrib = attrib->next;
		if ((msgbuf + MAX_MRPD_CMDSZ) - msgbuf_wrptr <= m * 2) {
			mrpd_send_ctl_msg(client, msgbuf, MAX_MRPD_CMDSZ);
			msgbuf_wrptr = msgbuf;
		}
	}

	mrpd_send_ctl_msg(client, msgbuf, MAX_MRPD_CMDSZ);

 free_msgbuf:
	if (regsrc)
		free(regsrc);
	if (variant)
		free(variant);
	if (stage)
		free(stage);
	free(msgbuf);
	return 0;

}

/* S+? - (re)JOIN a stream */
/* S++ - NEW a stream      */
static int msrp_cmd_parse_join_or_new_stream(char *buf, int buflen,
					     struct msrpdu_talker_fail
					     *talker_ad, int *err_index)
{
	struct parse_param specs[] = {
		{"S" PARSE_ASSIGN, parse_c64, talker_ad->StreamID},
		{"A" PARSE_ASSIGN, parse_mac,
		 talker_ad->DataFrameParameters.Dest_Addr},
		{"V" PARSE_ASSIGN, parse_u16,
		 &talker_ad->DataFrameParameters.Vlan_ID},
		{"Z" PARSE_ASSIGN, parse_u16, &talker_ad->TSpec.MaxFrameSize},
		{"I" PARSE_ASSIGN, parse_u16,
		 &talker_ad->TSpec.MaxIntervalFrames},
		{"P" PARSE_ASSIGN, parse_u8, &talker_ad->PriorityAndRank},
		{"L" PARSE_ASSIGN, parse_u32, &talker_ad->AccumulatedLatency},
		{0, parse_null, 0}
	};
	if (buflen < 22)
		return -1;
	memset(talker_ad, 0, sizeof(*talker_ad));
	return parse(buf + 4, buflen - 4, specs, err_index);
}

/*
 * Required fields are:
 * talker_ad->StreamID
 * talker_ad->DataFrameParameters.Dest_Addr
 * talker_ad->DataFrameParameters.Vlan_ID
 * talker_ad->TSpec.MaxFrameSize
 * talker_ad->TSpec.MaxIntervalFrames
 * talker_ad->PriorityAndRank
 * talker_ad->AccumulatedLatency
 *
 */

static int msrp_cmd_join_or_new_stream(struct msrpdu_talker_fail *talker_ad,
				       int mrp_event)
{
	struct msrp_attribute *attrib;

#ifdef MICREL_1588_PTP_DEV
	static uint8_t last_addr;
	static uint8_t last_id[2];

	int i = 0;
	int num = 0;
	int test = 0;
#endif

#ifdef MICREL_1588_PTP
	if (mrp_port > 1) {
		int notify;
		int rc;
		struct msrp_attribute copy;
		struct SRP_talker talker;

		attrib = &copy;
		if (MRP_EVENT_NEW == mrp_event)
			notify = MRP_NOTIFY_NEW;
		else
			notify = MRP_NOTIFY_JOIN;
		attrib->type = MSRP_TALKER_ADV_TYPE;
		if (!talker_ad->TSpec.MaxIntervalFrames) {
			talker_ad->TSpec.MaxIntervalFrames = 1;
			talker_ad->FailureInformation.FailureCode = 1;
		}
		attrib->attribute.talk_listen = *talker_ad;
		to_talker(attrib, &talker);
		rc = set_talker_rx(fd, 0, &talker);
		rc = handle_propagation(rc, notify);
		if (1 == rc)
			rc = 0;
		return rc;
	}
#endif

#ifdef MICREL_1588_PTP_DEV
	if ((talker_ad->StreamID[6] & 0x80) && last_addr + 1 ==
	    talker_ad->DataFrameParameters.Dest_Addr[5]) {
		test = talker_ad->StreamID[6] & 0xf;
		num = talker_ad->StreamID[7];
		--num;
		talker_ad->StreamID[6] = last_id[0];
		talker_ad->StreamID[7] = last_id[1] + 1;
		i = num;
	} else {
		last_addr = talker_ad->DataFrameParameters.Dest_Addr[5];
		last_id[0] = talker_ad->StreamID[6];
		last_id[1] = talker_ad->StreamID[7];
	}
next:
#endif

	attrib = msrp_alloc();
	if (NULL == attrib) {
		return -1;
	}
	attrib->type = MSRP_TALKER_ADV_TYPE;
	if (!talker_ad->TSpec.MaxIntervalFrames) {
		talker_ad->TSpec.MaxIntervalFrames = 1;
		talker_ad->FailureInformation.FailureCode = 1;
	}
	attrib->attribute.talk_listen = *talker_ad;
	msrp_event(mrp_event, attrib);

#ifdef MICREL_1588_PTP_DEV
	if (i) {
		uint8_t id = talker_ad->StreamID[7];
		uint8_t addr = talker_ad->DataFrameParameters.Dest_Addr[5];

		switch (test) {
		case 2:
			if (num > 22 && i > num - 22) {
				talker_ad->StreamID[7] += 1;
				talker_ad->DataFrameParameters.Dest_Addr[5] +=
					1;
			} else {
				talker_ad->StreamID[7] += 2;
				talker_ad->DataFrameParameters.Dest_Addr[5] +=
					2;
			}
			break;
		case 3:
			if (num > 120 && i > num - 120) {
				talker_ad->StreamID[7] += 2;
				talker_ad->DataFrameParameters.Dest_Addr[5] +=
					2;
			} else {
				talker_ad->StreamID[7] += 1;
				talker_ad->DataFrameParameters.Dest_Addr[5] +=
					1;
			}
			break;
		case 1:
		default:
			talker_ad->StreamID[7] += 1;
			talker_ad->DataFrameParameters.Dest_Addr[5] += 1;
			break;
		}
		if (talker_ad->StreamID[7] < id) {
			talker_ad->StreamID[6]++;
			if (0 == talker_ad->StreamID[6])
				talker_ad->StreamID[5]++;
		}
		if (talker_ad->DataFrameParameters.Dest_Addr[5] < addr) {
			talker_ad->DataFrameParameters.Dest_Addr[4]++;
			if (0 == talker_ad->DataFrameParameters.Dest_Addr[4])
				talker_ad->DataFrameParameters.Dest_Addr[3]++;
		}
		--i;
		goto next;
	}
#endif
	return 0;
}

/* S-- - LV a stream */
static int msrp_cmd_parse_leave_stream(char *buf, int buflen,
				       struct msrpdu_talker_fail *talker_ad,
				       int *err_index)
{
	struct parse_param specs[] = {
		{"S" PARSE_ASSIGN, parse_c64, talker_ad->StreamID},
		{"A" PARSE_ASSIGN, parse_mac,
		 talker_ad->DataFrameParameters.Dest_Addr},
		{0, parse_null, 0}
	};
	if (buflen < 22)
		return -1;
	memset(talker_ad, 0, sizeof(*talker_ad));
	return parse(buf + 4, buflen - 4, specs, err_index);
}

static int msrp_cmd_leave_stream(struct msrpdu_talker_fail *talker_ad)
{
	struct msrp_attribute *attrib;

#ifdef MICREL_1588_PTP_DEV
	static uint8_t last_addr;
	static uint8_t last_id[2];

	int i = 0;
	int num = 0;
	int test = 0;
#endif

#ifdef MICREL_1588_PTP
	if (mrp_port > 1) {
		int notify;
		int rc;
		struct msrp_attribute copy;
		struct SRP_talker talker;

		attrib = &copy;
		notify = MRP_NOTIFY_LV;
		attrib->type = MSRP_TALKER_ADV_TYPE;
		attrib->attribute.talk_listen = *talker_ad;
		to_talker(attrib, &talker);
		rc = set_talker_lv(fd, 0, &talker);
		rc = handle_propagation(rc, notify);
		if (1 == rc)
			rc = 0;
		return rc;
	}
#endif

#ifdef MICREL_1588_PTP_DEV
	if ((talker_ad->StreamID[6] & 0x80) && last_addr + 1 ==
	    talker_ad->DataFrameParameters.Dest_Addr[5]) {
		test = talker_ad->StreamID[6] & 0xf;
		num = talker_ad->StreamID[7];
		--num;
		talker_ad->StreamID[6] = last_id[0];
		talker_ad->StreamID[7] = last_id[1] + 1;
		i = num;
	} else {
		last_addr = talker_ad->DataFrameParameters.Dest_Addr[5];
		last_id[0] = talker_ad->StreamID[6];
		last_id[1] = talker_ad->StreamID[7];
	}
next:
#endif

	attrib = msrp_alloc();
	if (NULL == attrib) {
		return -1;
	}
	attrib->type = MSRP_TALKER_ADV_TYPE;
	attrib->attribute.talk_listen = *talker_ad;
	msrp_event(MRP_EVENT_LV, attrib);

#ifdef MICREL_1588_PTP_DEV
	if (i) {
		uint8_t id = talker_ad->StreamID[7];
		uint8_t addr = talker_ad->DataFrameParameters.Dest_Addr[5];

		switch (test) {
		case 2:
			if (num > 22 && i > num - 22) {
				talker_ad->StreamID[7] += 1;
				talker_ad->DataFrameParameters.Dest_Addr[5] +=
					1;
			} else {
				talker_ad->StreamID[7] += 2;
				talker_ad->DataFrameParameters.Dest_Addr[5] +=
					2;
			}
			break;
		case 3:
			if (num > 120 && i > num - 120) {
				talker_ad->StreamID[7] += 2;
				talker_ad->DataFrameParameters.Dest_Addr[5] +=
					2;
			} else {
				talker_ad->StreamID[7] += 1;
				talker_ad->DataFrameParameters.Dest_Addr[5] +=
					1;
			}
			break;
		case 1:
		default:
			talker_ad->StreamID[7] += 1;
			talker_ad->DataFrameParameters.Dest_Addr[5] += 1;
			break;
		}
		if (talker_ad->StreamID[7] < id) {
			talker_ad->StreamID[6]++;
			if (0 == talker_ad->StreamID[6])
				talker_ad->StreamID[5]++;
		}
		if (talker_ad->DataFrameParameters.Dest_Addr[5] < addr) {
			talker_ad->DataFrameParameters.Dest_Addr[4]++;
			if (0 == talker_ad->DataFrameParameters.Dest_Addr[4])
				talker_ad->DataFrameParameters.Dest_Addr[3]++;
		}
		--i;
		goto next;
	}
#endif

	return 0;
}

/* S+L   Report a listener status */
static int msrp_cmd_parse_report_listener_status(char *buf, int buflen,
						 struct msrpdu_talker_fail
						 *talker_ad,
						 uint32_t * substate,
						 int *err_index)
{
	struct parse_param specs[] = {
		{"L" PARSE_ASSIGN, parse_c64, talker_ad->StreamID},
		{"D" PARSE_ASSIGN, parse_u32, substate},
		{0, parse_null, 0}
	};
	if (buflen < 26)
		return -1;
	memset(talker_ad, 0, sizeof(*talker_ad));
	return parse(buf + 4, buflen - 4, specs, err_index);
}

#ifdef MICREL_1588_PTP_DEV
static uint8_t skip_attribs1[] = {
	20,
	19, 20, 18 };
static uint8_t skip_attribs2[] = {
	1, 19,
	19, 20, 18 };
static uint8_t skip_attribs3[] = {
	1, 1, 18,
	19, 20, 18 };
static uint8_t skip_attribs4[] = {
	1, 1, 1, 20,
	19, 20, 18 };
#endif

static int msrp_cmd_report_listener_status(struct msrpdu_talker_fail *talker_ad,
					   uint32_t substate)
{
	struct msrp_attribute *attrib;

#ifdef MICREL_1588_PTP_DEV
	static uint8_t last_id[2];

	uint8_t *skip_attribs = skip_attribs1;
	size_t skip_size = sizeof(skip_attribs1);
	int i = 0;
	int num = 0;
	int test = 0;
	unsigned int n = 0;
#endif

#ifdef MICREL_1588_PTP
	if (mrp_port > 1) {
		int notify;
		int rc;
		struct msrp_attribute copy;
		struct SRP_listener listener;

		attrib = &copy;
		notify = MRP_NOTIFY_JOIN;
		attrib->type = MSRP_LISTENER_TYPE;
		attrib->direction = MSRP_DIRECTION_LISTENER;
		attrib->substate = substate;
		attrib->attribute.talk_listen = *talker_ad;
		to_listener(attrib, &listener);
		rc = set_listener_rx(fd, 0, &listener);
		rc = handle_propagation(rc, notify);
		if (1 == rc)
			rc = 0;
		return rc;
	}
#endif

#ifdef MICREL_1588_PTP_DEV
	if (talker_ad->StreamID[6] & 0x80) {
		test = talker_ad->StreamID[6] & 0xf;
		num = talker_ad->StreamID[7];
		if (4 <= test && test <= 7) {
			switch (test) {
			case 4:
				skip_attribs = skip_attribs1;
				skip_size = sizeof(skip_attribs1);
				break;
			case 5:
				skip_attribs = skip_attribs2;
				skip_size = sizeof(skip_attribs2);
				break;
			case 6:
				skip_attribs = skip_attribs3;
				skip_size = sizeof(skip_attribs3);
				break;
			case 7:
				skip_attribs = skip_attribs4;
				skip_size = sizeof(skip_attribs4);
				break;
			}
			n = num >> 4;
			num &= 0xf;
		}
		talker_ad->StreamID[6] = last_id[0];
		talker_ad->StreamID[7] = last_id[1];
		i = num;
		dbg_listener = 1;
	} else {
		last_id[0] = talker_ad->StreamID[6];
		last_id[1] = talker_ad->StreamID[7];
	}

next:
	if (i) {
		uint8_t addr = talker_ad->StreamID[7];

		substate = MSRP_LISTENER_ASKFAILED;
		switch (test) {
		case 1:
			talker_ad->StreamID[7] += 1;
			break;
		case 2:
			if (num > 27 && i > num - 27)
				talker_ad->StreamID[7] += 1;
			else
				talker_ad->StreamID[7] += 21;
			break;
		case 3:
			if (num > 120 && i > num - 120)
				talker_ad->StreamID[7] += 21;
			else
				talker_ad->StreamID[7] += 1;
			break;
		default:
			if (n < skip_size)
				talker_ad->StreamID[7] += skip_attribs[n++];
			else
				talker_ad->StreamID[7] += 18;
			break;
		}
		if (talker_ad->StreamID[7] < addr) {
			talker_ad->StreamID[6]++;
			if (0 == talker_ad->StreamID[6])
				talker_ad->StreamID[5]++;
		}
	}
#endif

	attrib = msrp_alloc();
	if (NULL == attrib) {
		return -1;
	}
	attrib->type = MSRP_LISTENER_TYPE;
	attrib->direction = MSRP_DIRECTION_LISTENER;
	attrib->substate = substate;
	attrib->attribute.talk_listen = *talker_ad;
	msrp_event(MRP_EVENT_JOIN, attrib);

#ifdef MICREL_1588_PTP_DEV
	if (i) {
		--i;
		goto next;
	}
#endif

	return 0;
}

/* S-L   Withdraw a listener status */
static int msrp_cmd_parse_withdraw_listener_status(char *buf, int buflen, struct msrpdu_talker_fail
						   *talker_ad, int *err_index)
{
	struct parse_param specs[] = {
		{"L" PARSE_ASSIGN, parse_c64, talker_ad->StreamID},
		{0, parse_null, 0}
	};
	if (buflen < 22)
		return -1;

	memset(talker_ad, 0, sizeof(*talker_ad));
	return parse(buf + 4, buflen - 4, specs, err_index);
}

static int msrp_cmd_withdraw_listener_status(struct msrpdu_talker_fail
					     *talker_ad)
{
	struct msrp_attribute *attrib;

#ifdef MICREL_1588_PTP_DEV
	static uint8_t last_id[2];

	uint8_t *skip_attribs = skip_attribs1;
	size_t skip_size = sizeof(skip_attribs1);
	int i = 0;
	int num = 0;
	int test = 0;
	unsigned int n = 0;
#endif

#ifdef MICREL_1588_PTP
	if (mrp_port > 1) {
		int notify;
		int rc;
		struct msrp_attribute copy;
		struct SRP_listener listener;

		attrib = &copy;
		notify = MRP_NOTIFY_LV;
		attrib->type = MSRP_LISTENER_TYPE;
		attrib->attribute.talk_listen = *talker_ad;
		to_listener(attrib, &listener);
		rc = set_listener_lv(fd, 0, &listener);
		rc = handle_propagation(rc, notify);
		if (1 == rc)
			rc = 0;
		return rc;
	}
#endif

#ifdef MICREL_1588_PTP_DEV
	if (talker_ad->StreamID[6] & 0x80) {
		test = talker_ad->StreamID[6] & 0xf;
		num = talker_ad->StreamID[7];
		talker_ad->StreamID[6] = 0;
		talker_ad->StreamID[7] = 0;
		if (4 <= test && test <= 7) {
			switch (test) {
			case 4:
				skip_attribs = skip_attribs1;
				skip_size = sizeof(skip_attribs1);
				break;
			case 5:
				skip_attribs = skip_attribs2;
				skip_size = sizeof(skip_attribs2);
				break;
			case 6:
				skip_attribs = skip_attribs3;
				skip_size = sizeof(skip_attribs3);
				break;
			case 7:
				skip_attribs = skip_attribs4;
				skip_size = sizeof(skip_attribs4);
				break;
			}
			n = num >> 4;
			num &= 0xf;
		}
		talker_ad->StreamID[6] = last_id[0];
		talker_ad->StreamID[7] = last_id[1];
		i = num;
	} else {
		last_id[0] = talker_ad->StreamID[6];
		last_id[1] = talker_ad->StreamID[7];
	}

next:
	if (i) {
		uint8_t addr = talker_ad->StreamID[7];

		switch (test) {
		case 1:
			talker_ad->StreamID[7] += 1;
			break;
		case 2:
			if (num > 27 && i > num - 27)
				talker_ad->StreamID[7] += 1;
			else
				talker_ad->StreamID[7] += 21;
			break;
		case 3:
			if (num > 120 && i > num - 120)
				talker_ad->StreamID[7] += 21;
			else
				talker_ad->StreamID[7] += 1;
			break;
		default:
			if (n < skip_size)
				talker_ad->StreamID[7] += skip_attribs[n++];
			else
				talker_ad->StreamID[7] += 18;
			break;
		}
		if (talker_ad->StreamID[7] < addr) {
			talker_ad->StreamID[6]++;
			if (0 == talker_ad->StreamID[6])
				talker_ad->StreamID[5]++;
		}
	}
#endif

	attrib = msrp_alloc();
	if (NULL == attrib) {
		return -1;
	}
	attrib->type = MSRP_LISTENER_TYPE;
	attrib->attribute.talk_listen = *talker_ad;
	msrp_event(MRP_EVENT_LV, attrib);

#ifdef MICREL_1588_PTP_DEV
	if (i) {
		--i;
		goto next;
	}
#endif

	return 0;
}

/* S+D   Report a domain status */
/* S-D   Withdraw a domain status */
static int msrp_cmd_parse_domain_status(char *buf, int buflen,
					struct msrpdu_domain *domain,
					int *err_index)
{
	struct parse_param specs[] = {
		{"C" PARSE_ASSIGN, parse_u8, &domain->SRclassID},
		{"P" PARSE_ASSIGN, parse_u8, &domain->SRclassPriority},
		{"V" PARSE_ASSIGN, parse_u16_04x, &domain->SRclassVID},
		{0, parse_null, 0}
	};
	if (buflen < 18)
		return -1;
	memset(domain, 0, sizeof(*domain));
	return parse(buf + 4, buflen - 4, specs, err_index);
}

static int msrp_cmd_report_domain_status(struct msrpdu_domain *domain,
					 int report)
{
	struct msrp_attribute *attrib;

#ifdef MICREL_1588_PTP
	if (mrp_port > 1) {
		int notify;
		int rc;
		struct msrp_attribute copy;
		struct SRP_domain_class class;

		attrib = &copy;
		if (report)
			notify = MRP_NOTIFY_JOIN;
		else
			notify = MRP_NOTIFY_LV;
		attrib->type = MSRP_DOMAIN_TYPE;
		attrib->attribute.domain = *domain;
		to_domain(attrib, &class);
		if (MRP_NOTIFY_LV == notify)
			rc = set_domain_lv(fd, 0, &class);
		else
			rc = set_domain_rx(fd, 0, &class);
		rc = handle_propagation(rc, notify);
		if (1 == rc)
			rc = 0;
		return rc;
	}
#endif

	attrib = msrp_alloc();
	if (NULL == attrib) {
		return -1;
	}

	attrib->type = MSRP_DOMAIN_TYPE;
	attrib->attribute.domain = *domain;
	if (report)
		msrp_event(MRP_EVENT_JOIN, attrib);
	else
		msrp_event(MRP_EVENT_LV, attrib);

	return 0;
}

int msrp_recv_cmd(char *buf, int buflen, struct sockaddr_in *client)
{
	int rc;
	char respbuf[12];
	int mrp_event;
	unsigned int substate;
	struct msrpdu_domain domain_param;
	struct msrpdu_talker_fail talker_param;
	int err_index;

	if (NULL == MSRP_db) {
		snprintf(respbuf, sizeof(respbuf) - 1, "ERC %s\n", buf);
		mrpd_send_ctl_msg(client, respbuf, sizeof(respbuf));
		goto out;
	}

	rc = mrp_client_add(&(MSRP_db->mrp_db.clients), client);
#ifdef MICREL_1588_PTP
	if (rc < 0)
		return rc;
	/* It is a new client. */
	if (1 == rc) {
		struct msrp_attribute *attrib;
		int i;

		for (i = 0; i < mrp_port; i++) {
			mrp_index = i;
			MSRP_db = MSRP_dbs[mrp_index];
			MSRP_db->mrp_db.new_client = client;

			attrib = MSRP_db->attrib_list;
			while (NULL != attrib) {
				if (MRP_IN_STATE ==
				    attrib->registrar.mrp_state) {
					msrp_send_notifications(attrib,
						MRP_NOTIFY_NEW);
				}
				attrib = attrib->next;
			}
			MSRP_db->mrp_db.new_client = NULL;
		}
		mrp_index = 0;
		MSRP_db = MSRP_dbs[mrp_index];
	}
#endif

	if (buflen < 3)
		return -1;

	if ('S' != buf[0])
		return -1;

	/*
	 * S?? - query MSRP Registrar database
	 * S+? - (re)JOIN a stream
	 * S++   NEW a stream
	 * S-- - LV a stream
	 * S+L   Report a listener status
	 * S-L   Withdraw a listener status
	 * S+D   Report a domain status
	 * S-D   Withdraw a domain status
	 */

	if (strncmp(buf, "S??", 3) == 0) {
		msrp_dumptable(client);

	} else if (strncmp(buf, "S-L", 3) == 0) {

		/* buf[] should look similar to 'S-L:L=xxyyzz...' */
		rc = msrp_cmd_parse_withdraw_listener_status(buf, buflen,
							     &talker_param,
							     &err_index);
		if (rc)
			goto out_ERP;
		rc = msrp_cmd_withdraw_listener_status(&talker_param);
		if (rc)
			goto out_ERI;	/* oops - internal error */
	} else if (strncmp(buf, "S-D", 3) == 0) {

		/* buf[] should look similar to 'S-D:C=%d,P=%d,V:%04x" */
		rc = msrp_cmd_parse_domain_status(buf, buflen, &domain_param,
						  &err_index);
		if (rc)
			goto out_ERP;
		rc = msrp_cmd_report_domain_status(&domain_param, 0);
		if (rc)
			goto out_ERI;	/* oops - internal error */
	} else if (strncmp(buf, "S--", 3) == 0) {
		/* buf[] should look similar to 'S--:S=xxyyzz...' */
		rc = msrp_cmd_parse_leave_stream(buf, buflen, &talker_param,
						 &err_index);
		if (rc)
			goto out_ERP;
		rc = msrp_cmd_leave_stream(&talker_param);
		if (rc)
			goto out_ERI;	/* oops - internal error */
	} else if (strncmp(buf, "S+L", 3) == 0) {
		/* buf[] should look similar to 'S+L:L=xxyyzz...:D=a' */
		rc = msrp_cmd_parse_report_listener_status(buf, buflen,
							   &talker_param,
							   &substate,
							   &err_index);
		if (rc)
			goto out_ERP;
#ifdef MICREL_1588_PTP
		talker_param.port = 0;
#endif
		rc = msrp_cmd_report_listener_status(&talker_param, substate);
		if (rc)
			goto out_ERI;	/* oops - internal error */
	} else if (strncmp(buf, "S+D", 3) == 0) {
		/* buf[] should look similar to 'S+D:C=%d,P=%d,V=%04x" */
		rc = msrp_cmd_parse_domain_status(buf, buflen, &domain_param,
						  &err_index);
		if (rc)
			goto out_ERP;
		rc = msrp_cmd_report_domain_status(&domain_param, 1);
		if (rc)
			goto out_ERI;	/* oops - internal error */
	} else if ((strncmp(buf, "S+?", 3) == 0)
		   || (strncmp(buf, "S++", 3) == 0)) {
		/*
		 * create or join a stream
		 * interesting to note the spec doesn't talk about
		 * what happens if two talkers attempt to define the identical
		 * stream twice  - does the bridge report STREAM_CHANGE error?
		 */

		/*
		   buf[] should look similar to "S=%02x%02x%02x%02x%02x%02x%02x%02x"
		   ",A=%02x%02x%02x%02x%02x%02x"
		   ",V=%04x" \
		   ",Z=%d" \
		   ",I=%d" \
		   ",P=%d" \
		   ",L=%d" \
		 */
		rc = msrp_cmd_parse_join_or_new_stream(buf, buflen,
						       &talker_param,
						       &err_index);
		if (rc)
			goto out_ERP;
		if ('?' == buf[2]) {
			mrp_event = MRP_EVENT_JOIN;
		} else {
			mrp_event = MRP_EVENT_NEW;
		}
#ifdef MICREL_1588_PTP
		talker_param.port = 0;
		talker_param.StreamAge = 0;
#endif
		rc = msrp_cmd_join_or_new_stream(&talker_param, mrp_event);
		if (rc)
			goto out_ERI;	/* oops - internal error */
	} else {
		snprintf(respbuf, sizeof(respbuf) - 1, "ERC %s", buf);
		mrpd_send_ctl_msg(client, respbuf, sizeof(respbuf));
		goto out;
	}
	return 0;

 out_ERI:
	snprintf(respbuf, sizeof(respbuf) - 1, "ERI %s", buf);
	mrpd_send_ctl_msg(client, respbuf, sizeof(respbuf));
	goto out;

 out_ERP:
	snprintf(respbuf, sizeof(respbuf) - 1, "ERP %s", buf);
	mrpd_send_ctl_msg(client, respbuf, sizeof(respbuf));
	goto out;

 out:
	return -1;
}

int msrp_init(int msrp_enable)
{
	int rc;

	/* XXX doesn't handle re-start */

#ifdef MICREL_1588_PTP
	domain_attrib.type = MSRP_DOMAIN_TYPE;
	listener_attrib.type = MSRP_LISTENER_TYPE;
	talker_attrib.type = MSRP_TALKER_ADV_TYPE;
#endif

	msrp_socket = INVALID_SOCKET;
	MSRP_db = NULL;

	if (0 == msrp_enable) {
		return 0;
	}
#ifdef MICREL_1588_PTP
	mrp_index = 0;

next_port:
#endif
	rc = mrpd_init_protocol_socket(MSRP_ETYPE, &msrp_socket, MSRP_ADDR);
	if (rc < 0)
		return -1;

	MSRP_db = malloc(sizeof(struct msrp_database));

	if (NULL == MSRP_db)
		goto abort_socket;

	memset(MSRP_db, 0, sizeof(struct msrp_database));

	/* if registration is FIXED or FORBIDDEN
	 * updates from MRP are discarded, and
	 * only IN and JOININ messages are sent
	 */
	MSRP_db->mrp_db.registration = MRP_REGISTRAR_CTL_NORMAL;	/* default */

	/* if participant role is 'SILENT' (or non-participant)
	 * applicant doesn't send any messages -
	 *
	 * Note - theoretically configured per-attribute
	 */
	MSRP_db->mrp_db.participant = MRP_APPLICANT_CTL_NORMAL;	/* default */

	rc = mrpd_init_timers(&(MSRP_db->mrp_db));

	if (rc < 0)
		goto abort_alloc;

	mrp_lvatimer_fsm(&(MSRP_db->mrp_db), MRP_EVENT_BEGIN);
#ifdef MICREL_1588_PTP
	msrp_sockets[mrp_index] = msrp_socket;
	MSRP_dbs[mrp_index] = MSRP_db;
	++mrp_index;
	if (mrp_index < mrp_port)
		goto next_port;
#endif

	return 0;

 abort_alloc:
	/* free MSRP_db and related structures */
	free(MSRP_db);
	MSRP_db = NULL;
 abort_socket:
	mrpd_close_socket(msrp_socket);
	msrp_socket = INVALID_SOCKET;
	/* XXX */
	return -1;
}

void msrp_bye(struct sockaddr_in *client)
{
#ifdef MICREL_1588_PTP
if (ofp) {
fprintf(ofp, "   %s %p\n", __func__, client);
fflush(ofp);
}
#endif
	if (NULL != MSRP_db)
		mrp_client_delete(&(MSRP_db->mrp_db.clients), client);
}

int msrp_reclaim(void)
{
	struct msrp_attribute *sattrib, *free_sattrib;

	if (NULL == MSRP_db)
		return 0;

#ifdef MICREL_1588_PTP
if (ofp) {
if (2 == MSRP_db->mrp_db.reclaim)
	fprintf(ofp, "cleanup\n");
else if (MSRP_db->attrib_list)
	fprintf(ofp, "%s\n", __func__);
}
	MSRP_db->mrp_db.reclaim = 1;
#endif
	sattrib = MSRP_db->attrib_list;
	while (NULL != sattrib) {
		if ((sattrib->registrar.mrp_state == MRP_MT_STATE) &&
#ifdef MICREL_1588_PTP
		    sattrib->applicant.aging <= 1 &&
#endif
		    ((sattrib->applicant.mrp_state == MRP_VO_STATE) ||
		     (sattrib->applicant.mrp_state == MRP_AO_STATE) ||
		     (sattrib->applicant.mrp_state == MRP_QO_STATE))) {
			if (NULL != sattrib->prev)
				sattrib->prev->next = sattrib->next;
			else
				MSRP_db->attrib_list = sattrib->next;
			if (NULL != sattrib->next)
				sattrib->next->prev = sattrib->prev;
			free_sattrib = sattrib;
			sattrib = sattrib->next;
			msrp_send_notifications(free_sattrib, MRP_NOTIFY_LV);
			free(free_sattrib);
		} else
			sattrib = sattrib->next;
	}
#ifdef MICREL_1588_PTP
	MSRP_db->mrp_db.reclaim = 0;
#endif
	return 0;
}
