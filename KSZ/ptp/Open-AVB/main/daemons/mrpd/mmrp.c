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
 * MMRP protocol (part of 802.1Q-2011)
 */

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>

#include "parse.h"
#include "mrpd.h"
#include "mrp.h"
#include "mmrp.h"

int mmrp_send_notifications(struct mmrp_attribute *attrib, int notify);
int mmrp_txpdu(void);

#ifdef MICREL_1588_PTP_DEV
unsigned char MMRP_ADDR[] = { 0x01, 0x00, 0xC2, 0x00, 0x00, 0x20 };
#else
unsigned char MMRP_ADDR[] = { 0x01, 0x80, 0xC2, 0x00, 0x00, 0x20 };
#endif

extern unsigned char STATION_ADDR[];

SOCKET mmrp_socket;

struct mmrp_database *MMRP_db;
#ifdef MICREL_1588_PTP
SOCKET mmrp_sockets[8];
struct mmrp_database *MMRP_dbs[8];
static time_t last_event_time;
#endif

struct mmrp_attribute *mmrp_lookup(struct mmrp_attribute *rattrib)
{
	struct mmrp_attribute *attrib;
	int mac_eq;

	attrib = MMRP_db->attrib_list;
	while (NULL != attrib) {
		if (rattrib->type == attrib->type) {
			if (MMRP_SVCREQ_TYPE == attrib->type) {
				/* this makes no sense to me ...
				 * its boolean .. but ..
				 */
				if (attrib->attribute.svcreq ==
				    rattrib->attribute.svcreq)
					return attrib;
			} else {
				mac_eq = memcmp(attrib->attribute.macaddr,
						rattrib->attribute.macaddr, 6);
				if (0 == mac_eq)
					return attrib;
			}
		}
		attrib = attrib->next;
	}
	return NULL;
}

int mmrp_add(struct mmrp_attribute *rattrib)
{
	struct mmrp_attribute *attrib;
	struct mmrp_attribute *attrib_tail;
	int mac_eq;

	/* XXX do a lookup first to guarantee uniqueness? */

	attrib_tail = attrib = MMRP_db->attrib_list;

	while (NULL != attrib) {
		/* sort list into types, then sorted in order within types */
		if (rattrib->type == attrib->type) {
			if (MMRP_SVCREQ_TYPE == attrib->type) {
				if (attrib->attribute.svcreq <
				    rattrib->attribute.svcreq) {
					/* possible tail insertion ... */

					if (NULL != attrib->next) {
						if (MMRP_SVCREQ_TYPE ==
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
						MMRP_db->attrib_list = rattrib;

					return 0;
				}
			} else {
				mac_eq = memcmp(attrib->attribute.macaddr,
						rattrib->attribute.macaddr, 6);

				if (mac_eq < 0) {
					/* possible tail insertion ... */

					if (NULL != attrib->next) {
						if (MMRP_MACVEC_TYPE ==
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
						MMRP_db->attrib_list = rattrib;

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
		MMRP_db->attrib_list = rattrib;
	} else {
		rattrib->next = NULL;
		rattrib->prev = attrib_tail;
		attrib_tail->next = rattrib;
	}

	return 0;
}

int mmrp_merge(struct mmrp_attribute *rattrib)
{
	struct mmrp_attribute *attrib;

	attrib = mmrp_lookup(rattrib);

	if (NULL == attrib)
		return -1;	/* shouldn't happen */

	/* primarily we update the last mac address state for diagnostics */
#ifdef MICREL_1588_PTP
	if (rattrib->registrar.macaddr[0] ||
	    rattrib->registrar.macaddr[1] ||
	    rattrib->registrar.macaddr[2])
#endif
	memcpy(attrib->registrar.macaddr, rattrib->registrar.macaddr, 6);
	return 0;
}

int mmrp_event(int event, struct mmrp_attribute *rattrib)
{
	struct mmrp_attribute *attrib;
#ifdef MICREL_1588_PTP
	int next_event;
	int rc;
	int tx_op = 0;
	time_t ticks = time(NULL);

if (event != MRP_EVENT_LVATIMER && event != MRP_EVENT_TX &&
event != MRP_EVENT_PERIODIC)
if (ofp) {
if (rattrib)
fprintf(ofp, "=%02x  ", rattrib->attribute.macaddr[5]);
fprintf(ofp, "%s %d %s %ld %ld\n", __func__, event, mrp_event_string(event),
ticks - start_time, ticks - last_event_time);
}
#endif
	switch (event) {
	case MRP_EVENT_LVATIMER:
/* Attributes are not actually sent in this event. */
#ifndef MICREL_1588_PTP
		mrp_lvatimer_stop(&(MMRP_db->mrp_db));
		mrp_jointimer_stop(&(MMRP_db->mrp_db));
		/* update state */
		attrib = MMRP_db->attrib_list;

		while (NULL != attrib) {
#if LOG_MMRP
			mrpd_log_printf("MMRP -> mrp_applicant_fsm\n");
#endif
			mrp_applicant_fsm(&(MMRP_db->mrp_db),
					  &(attrib->applicant), MRP_EVENT_TXLA);
			mrp_registrar_fsm(&(attrib->registrar),
					  &(MMRP_db->mrp_db), MRP_EVENT_TXLA);
			attrib = attrib->next;
		}
#endif

#ifdef MICREL_1588_PTP
		tx_op =
#endif
		mrp_lvatimer_fsm(&(MMRP_db->mrp_db), MRP_EVENT_LVATIMER);

/*
 * Attributes are not actually sent in this event.  Wait for next transmit
 * opportunity.
 */
#ifndef MICREL_1588_PTP
		mmrp_txpdu();
#endif
		break;
	case MRP_EVENT_RLA:
/* Attributes are not necessarily needed to be sent in this event. */
#ifndef MICREL_1588_PTP
		mrp_jointimer_start(&(MMRP_db->mrp_db));
#endif
		/* update state */
		attrib = MMRP_db->attrib_list;

		while (NULL != attrib) {
#if LOG_MMRP
			mrpd_log_printf("MMRP -> mrp_applicant_fsm\n");
#endif
#ifdef MICREL_1588_PTP
			tx_op |=
#endif
			mrp_applicant_fsm(&(MMRP_db->mrp_db),
					  &(attrib->applicant), MRP_EVENT_RLA);
			mrp_registrar_fsm(&(attrib->registrar),
					  &(MMRP_db->mrp_db), MRP_EVENT_RLA);
			attrib = attrib->next;
		}

		mrp_lvatimer_fsm(&(MMRP_db->mrp_db), MRP_EVENT_RLA);

		break;
	case MRP_EVENT_TX:
		mrp_jointimer_stop(&(MMRP_db->mrp_db));
#ifdef MICREL_1588_PTP
		/*
		 * Do this first so that tx! becomes txLA! if LeaveAll is
		 * indicated.
		 */
		mrp_lvatimer_fsm(&(MMRP_db->mrp_db), MRP_EVENT_TX);
		if (MRP_SND_LVA == MMRP_db->mrp_db.lva.sndmsg)
			MMRP_db->mrp_db.lva.tx = 0x3;

		attrib = MMRP_db->attrib_list;

		while (NULL != attrib) {
#if LOG_MMRP
			mrpd_log_printf("MMRP -> mrp_applicant_fsm\n");
#endif
			next_event = 1;
			if (MMRP_SVCREQ_TYPE == attrib->type)
				next_event = 2;
			if (MMRP_db->mrp_db.lva.tx & next_event) {
				tx_op |=
				mrp_applicant_fsm(&(MMRP_db->mrp_db),
					&(attrib->applicant), MRP_EVENT_TXLA);
				mrp_registrar_fsm(&(attrib->registrar),
					&(MMRP_db->mrp_db), MRP_EVENT_TXLA);
			} else {
				MMRP_db->mrp_db.registrar_state =
					attrib->registrar.mrp_state;
				tx_op |=
				mrp_applicant_fsm(&(MMRP_db->mrp_db),
					&(attrib->applicant), MRP_EVENT_TX);
			}
			attrib = attrib->next;
		}
#else
		attrib = MMRP_db->attrib_list;

		while (NULL != attrib) {
#if LOG_MMRP
			mrpd_log_printf("MMRP -> mrp_applicant_fsm\n");
#endif
			mrp_applicant_fsm(&(MMRP_db->mrp_db),
					  &(attrib->applicant), MRP_EVENT_TX);
			attrib = attrib->next;
		}

		mrp_lvatimer_fsm(&(MMRP_db->mrp_db), MRP_EVENT_TX);
#endif

#ifdef MICREL_1588_PTP
		rc =
#endif
		mmrp_txpdu();
#ifdef MICREL_1588_PTP
		next_event = 0;

		/* Not all attributes sent. */
		if (rc) {
			if (MRP_SND_LVA == MMRP_db->mrp_db.lva.sndmsg)
				next_event = MRP_EVENT_TXLAF;
			else
				/* Send rest in next tx!. */
				tx_op |= 2;
		} else if (MRP_SND_LVA == MMRP_db->mrp_db.lva.sndmsg) {
			next_event = MRP_EVENT_RLA;
			mrp_lvatimer_fsm(&(MMRP_db->mrp_db), MRP_EVENT_RLA);
		}
		if (next_event) {
			attrib = MMRP_db->attrib_list;
			while (NULL != attrib) {
				tx_op |=
				mrp_applicant_fsm(&(MMRP_db->mrp_db),
					&(attrib->applicant), next_event);
				mrp_registrar_fsm(&(attrib->registrar),
					&(MMRP_db->mrp_db), next_event);
				attrib = attrib->next;
			}
		}
#endif
		break;
	case MRP_EVENT_LVTIMER:
		mrp_lvtimer_stop(&(MMRP_db->mrp_db));
		attrib = MMRP_db->attrib_list;

		while (NULL != attrib) {
			mrp_registrar_fsm(&(attrib->registrar),
					  &(MMRP_db->mrp_db),
					  MRP_EVENT_LVTIMER);

			attrib = attrib->next;
		}
		break;
	case MRP_EVENT_PERIODIC:
		attrib = MMRP_db->attrib_list;

		while (NULL != attrib) {
#if LOG_MMRP
			mrpd_log_printf("MMRP -> mrp_applicant_fsm\n");
#endif
#ifdef MICREL_1588_PTP
			tx_op |=
#endif
			mrp_applicant_fsm(&(MMRP_db->mrp_db),
					  &(attrib->applicant),
					  MRP_EVENT_PERIODIC);
			attrib = attrib->next;
		}
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
		mrp_jointimer_start(&(MMRP_db->mrp_db));
#endif
		if (NULL == rattrib)
			return -1;	/* XXX internal fault */

		/* update state */
		attrib = mmrp_lookup(rattrib);

		if (NULL == attrib) {
#ifdef MICREL_1588_PTP
			/* Do not want to create empty attribute. */
			if (MRP_EVENT_RMT == event) {
				free(rattrib);
				break;
			}
#endif
			mmrp_add(rattrib);
			attrib = rattrib;
		} else {
			mmrp_merge(rattrib);
			free(rattrib);
		}

#if LOG_MMRP
		mrpd_log_printf("MMRP -> mrp_applicant_fsm\n");
#endif
#ifdef MICREL_1588_PTP
		tx_op =
#endif
		mrp_applicant_fsm(&(MMRP_db->mrp_db), &(attrib->applicant),
				  event);
		/* remap local requests into registrar events */
		switch (event) {
		case MRP_EVENT_NEW:
#ifndef MICREL_1588_PTP
			mrp_registrar_fsm(&(attrib->registrar),
					  &(MMRP_db->mrp_db), MRP_EVENT_RNEW);
#endif
			break;
		case MRP_EVENT_JOIN:
#ifndef MICREL_1588_PTP
			if (MRP_IN_STATE == attrib->registrar.mrp_state)
				mrp_registrar_fsm(&(attrib->registrar),
						  &(MMRP_db->mrp_db),
						  MRP_EVENT_RJOININ);
			else
				mrp_registrar_fsm(&(attrib->registrar),
						  &(MMRP_db->mrp_db),
						  MRP_EVENT_RJOINMT);
#endif
			break;
		case MRP_EVENT_LV:
#ifndef MICREL_1588_PTP
			mrp_registrar_fsm(&(attrib->registrar),
					  &(MMRP_db->mrp_db), MRP_EVENT_RLV);
#endif
			break;
		default:
			mrp_registrar_fsm(&(attrib->registrar),
					  &(MMRP_db->mrp_db), event);
			break;
		}
		break;
	default:
		break;
	}
#ifdef MICREL_1588_PTP
	/* Send attributes in next transmit opportunity. */
	if (tx_op) {
		mrp_jointimer_start(&(MMRP_db->mrp_db));

		/* Not continuing previous tx!. */
		if (!(tx_op & 2))
			MMRP_db->mrp_db.tx_attrib = NULL;
	}
	last_event_time = ticks;
#endif

	/*
	 * XXX should honor the MMRP_db->mrp_db.registration and
	 * MMRP_db->mrp_db.participant controls
	 */

	/* generate local notifications */
	attrib = MMRP_db->attrib_list;

	while (NULL != attrib) {
		if (MRP_NOTIFY_NONE != attrib->registrar.notify) {
			mmrp_send_notifications(attrib,
						attrib->registrar.notify);
			attrib->registrar.notify = MRP_NOTIFY_NONE;
		}
		attrib = attrib->next;
	}

	return 0;
}

struct mmrp_attribute *mmrp_alloc()
{
	struct mmrp_attribute *attrib;

	attrib = malloc(sizeof(struct mmrp_attribute));
	if (NULL == attrib)
		return NULL;

	memset(attrib, 0, sizeof(struct mmrp_attribute));

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

void mmrp_increment_macaddr(uint8_t * macaddr)
{

	int i;

	i = 5;
	while (i > 0) {
		if (255 != macaddr[i]) {
			macaddr[i]++;
			return;
		}
		macaddr[i] = 0;
		i--;
	}
	return;
}

int mmrp_recv_msg()
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
	int vectidx;
	int vectevt[3];
	int vectevt_idx;
	uint8_t svcreq_firstval;
	uint8_t macvec_firstval[6];
	struct mmrp_attribute *attrib;
	int endmarks;
#ifdef MICREL_1588_PTP
	uint16_t VectorHeader;
	uint8_t *unaligned;
	int rLA = 0;
	time_t ticks = time(NULL);

if (ofp)
fprintf(ofp, " > %ld %ld\n",
ticks - start_time, ticks - last_event_time);
#endif

	bytes = mrpd_recvmsgbuf(mmrp_socket, &msgbuf);
	if (bytes <= 0)
		goto out;

	if ((unsigned int)bytes < (sizeof(eth_hdr_t) + sizeof(mrpdu_t) +
				   sizeof(mrpdu_message_t)))
		goto out;

	eth = (eth_hdr_t *) msgbuf;

	/* note that MMRP frames should always arrive untagged (no vlan) */
	if (MMRP_ETYPE != ntohs(eth->typelen))
		goto out;

	/* XXX check dest mac address too? */

	mrpdu = (mrpdu_t *) (msgbuf + sizeof(struct eth_hdr));

	if (MMRP_PROT_VER != mrpdu->ProtocolVersion)	/* should accept */
		goto out;

	mrpdu_msg_ptr = MRPD_GET_MRPDU_MESSAGE_LIST(mrpdu);

	mrpdu_msg_eof = (unsigned char *)mrpdu_msg_ptr;
	mrpdu_msg_eof += bytes;
	mrpdu_msg_eof -= sizeof(eth_hdr_t);
	mrpdu_msg_eof -= MRPD_OFFSETOF_MRPD_GET_MRPDU_MESSAGE_LIST;

	endmarks = 0;

	while (mrpdu_msg_ptr < (mrpdu_msg_eof - 2)) {
		mrpdu_msg = (mrpdu_message_t *) mrpdu_msg_ptr;
		if ((mrpdu_msg->AttributeType == 0) &&
		    (mrpdu_msg->AttributeLength == 0)) {
			mrpdu_msg_ptr += 2;
			endmarks++;
			if (endmarks < 2)
				continue;	/* end-mark */
			else
				break;	/* two endmarks - end of messages */
		}

		endmarks = 0;	/* reset the endmark counter */

		switch (mrpdu_msg->AttributeType) {
		case MMRP_SVCREQ_TYPE:
			if (mrpdu_msg->AttributeLength != 1) {
				/* we could seek for an endmark to recover
				 */
				goto out;
			}
			/* AttributeListLength not used for MMRP, hence
			 * Data points to the beginning of the VectorAttributes
			 */
			mrpdu_vectorptr =
			    (mrpdu_vectorattrib_t *) mrpdu_msg->Data;
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

				if (0 == numvalues)
					/* Malformed - cant tell how long the trailing vectors are */
					goto out;

				if ((mrpdu_vectorptr->FirstValue_VectorEvents +
				     numvalues / 3) >= mrpdu_msg_eof)
					/* Malformed - runs off the end of the pdu */
					goto out;

/* Generate rLA event at the very beginnning and only once. */
#ifdef MICREL_1588_PTP
				if (MRPDU_VECT_LVA(VectorHeader) && !rLA) {
					mmrp_event(MRP_EVENT_RLA, NULL);
					rLA = 1;
				}
#endif

				svcreq_firstval =
				    mrpdu_vectorptr->FirstValue_VectorEvents[0];

				/* if not an even multiple ... */
				if (numvalues != ((numvalues / 3) * 3))
					numvectorbytes = (numvalues / 3) + 1;
				else
					numvectorbytes = (numvalues / 3);

				for (vectidx = 1;
				     vectidx <= (numvectorbytes + 1);
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

						if (1 < svcreq_firstval)	/*discard junk */
							continue;

						attrib = mmrp_alloc();
						if (NULL == attrib)
							goto out;	/* oops - internal error */

						attrib->type = MMRP_SVCREQ_TYPE;
						attrib->attribute.svcreq =
						    svcreq_firstval;
						svcreq_firstval++;
						memcpy(attrib->registrar.
						       macaddr, eth->srcaddr,
						       6);

						switch (vectevt[vectevt_idx]) {
						case MRPDU_NEW:
							mmrp_event
							    (MRP_EVENT_RNEW,
							     attrib);
							break;
						case MRPDU_JOININ:
							mmrp_event
							    (MRP_EVENT_RJOININ,
							     attrib);
							break;
						case MRPDU_IN:
							mmrp_event
							    (MRP_EVENT_RIN,
							     attrib);
							break;
						case MRPDU_JOINMT:
							mmrp_event
							    (MRP_EVENT_RJOINMT,
							     attrib);
							break;
						case MRPDU_MT:
							mmrp_event
							    (MRP_EVENT_RMT,
							     attrib);
							break;
						case MRPDU_LV:
							mmrp_event
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

				/* as either firstval is either 0 or 1 ... the common
				 * case will be nulls for evt_2 and evt_3 ...
				 */
#ifndef MICREL_1588_PTP
				if (MRPDU_VECT_LVA
				    (ntohs(mrpdu_vectorptr->VectorHeader)))
					mmrp_event(MRP_EVENT_RLA, NULL);
#endif

				/* 2 byte numvalues + 34 byte FirstValue + (n) vector bytes */
				mrpdu_msg_ptr = (uint8_t *) mrpdu_vectorptr;
				mrpdu_msg_ptr += 3 + numvectorbytes;
				mrpdu_vectorptr =
				    (mrpdu_vectorattrib_t *) mrpdu_msg_ptr;
			}

			break;
		case MMRP_MACVEC_TYPE:
			if (mrpdu_msg->AttributeLength != 6) {
				/* we can seek for an endmark to recover .. but this version
				 * dumps the entire packet as malformed
				 */
				goto out;
			}
			/* AttributeListLength not used for MMRP, hence
			 * Data points to the beginning of the VectorAttributes
			 */
			mrpdu_vectorptr =
			    (mrpdu_vectorattrib_t *) mrpdu_msg->Data;
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

				if (0 == numvalues)
					/* Malformed - cant tell how long the trailing vectors are */
					goto out;

				if ((mrpdu_vectorptr->FirstValue_VectorEvents +
				     numvalues / 3) >= mrpdu_msg_eof)
					/* Malformed - runs off the end of the pdu */
					goto out;

/* Generate rLA event at the very beginnning and only once. */
#ifdef MICREL_1588_PTP
				if (MRPDU_VECT_LVA(VectorHeader) && !rLA) {
					mmrp_event(MRP_EVENT_RLA, NULL);
					rLA = 1;
				}
#endif

				memcpy(macvec_firstval,
				       mrpdu_vectorptr->FirstValue_VectorEvents,
				       6);

				/* if not an even multiple ... */
				if (numvalues != ((numvalues / 3) * 3))
					numvectorbytes = (numvalues / 3) + 1;
				else
					numvectorbytes = (numvalues / 3);

				for (vectidx = 6;
				     vectidx <= (numvectorbytes + 6);
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

						attrib = mmrp_alloc();
						if (NULL == attrib)
							goto out;	/* oops - internal error */

						attrib->type = MMRP_MACVEC_TYPE;
						memcpy(attrib->attribute.
						       macaddr, macvec_firstval,
						       6);
						mmrp_increment_macaddr
						    (macvec_firstval);

						memcpy(attrib->registrar.
						       macaddr, eth->srcaddr,
						       6);

						switch (vectevt[vectevt_idx]) {
						case MRPDU_NEW:
							mmrp_event
							    (MRP_EVENT_RNEW,
							     attrib);
							break;
						case MRPDU_JOININ:
							mmrp_event
							    (MRP_EVENT_RJOININ,
							     attrib);
							break;
						case MRPDU_IN:
							mmrp_event
							    (MRP_EVENT_RIN,
							     attrib);
							break;
						case MRPDU_JOINMT:
							mmrp_event
							    (MRP_EVENT_RJOINMT,
							     attrib);
							break;
						case MRPDU_MT:
							mmrp_event
							    (MRP_EVENT_RMT,
							     attrib);
							break;
						case MRPDU_LV:
							mmrp_event
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
					mmrp_event(MRP_EVENT_RLA, NULL);
#endif

				/* 1 byte Type, 1 byte Len, 6 byte FirstValue, and (n) vector bytes */
				mrpdu_msg_ptr = (uint8_t *) mrpdu_vectorptr;
				mrpdu_msg_ptr += 8 + numvectorbytes;

				mrpdu_vectorptr =
				    (mrpdu_vectorattrib_t *) mrpdu_msg_ptr;
			}
			break;
		default:
			/* unrecognized attribute type
			 * we can seek for an endmark to recover .. but this version
			 * dumps the entire packet as malformed
			 */
			goto out;
		}
	}
#ifdef MICREL_1588_PTP
if (ofp) {
fprintf(ofp, " <\n");
fflush(ofp);
}
#endif

	free(msgbuf);
	return 0;
 out:
	free(msgbuf);

	return -1;
}

#ifdef MICREL_1588_PTP
static void mmrp_prepare_tx(uint32_t type, int lva)
{
	uint8_t svc_firstval = 0;
	uint8_t mac_firstval[6];
	struct mmrp_attribute *attrib;
	struct mmrp_attribute *first = NULL;
	struct mmrp_attribute *last = NULL;
	struct mmrp_attribute *optional = NULL;
	int firstval_max;
	int firstval_cnt = 0;
	int firstval_optional = 0;

	if (MMRP_SVCREQ_TYPE == type)
		firstval_max = (((2 + 1) + 1) * 2 - (2 + 1)) * 3 - 2;
	else
		firstval_max = (((2 + 6) + 1) * 2 - (2 + 6)) * 3 - 2;
	attrib = MMRP_db->attrib_list;
	while (attrib != NULL) {
		if (type != attrib->type)
			goto next;
		if (0 == attrib->applicant.tx)
			goto next;
		last = attrib;
		if (firstval_cnt) {
			int firstval_next = 1;

			if (MMRP_SVCREQ_TYPE == attrib->type) {
				++svc_firstval;
				if (svc_firstval != attrib->attribute.svcreq)
					firstval_next = 0;
			} else {
				mmrp_increment_macaddr(mac_firstval);
				if (memcmp(attrib->attribute.macaddr,
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
			if (MMRP_SVCREQ_TYPE == attrib->type)
				svc_firstval = attrib->attribute.svcreq;
			else
				memcpy(mac_firstval, attrib->attribute.macaddr,
					6);
			firstval_cnt = 1;
			last = NULL;
		}

next:
		attrib = attrib->next;
	}

	/* Need to send at least one for LeaveAll. */
	if (lva && last && !last->applicant.tx)
		last->applicant.tx = 1;
}
#endif

int
mmrp_emit_svcvectors(unsigned char *msgbuf, unsigned char *msgbuf_eof,
		     int *bytes_used, int lva)
{
	mrpdu_vectorattrib_t *mrpdu_vectorptr;
	uint16_t numvalues;
	uint8_t vect_3pack;
	int vectidx;
	int vectevt[3];
	int vectevt_idx;
	uint8_t svcreq_firstval;
	struct mmrp_attribute *attrib, *vattrib;
	mrpdu_message_t *mrpdu_msg;
	unsigned char *mrpdu_msg_ptr = msgbuf;
	unsigned char *mrpdu_msg_eof = msgbuf_eof;
#ifdef MICREL_1588_PTP
	uint16_t VectorHeader;
	uint8_t *unaligned;
#endif

#ifdef MICREL_1588_PTP
	if (mrpdu_msg_ptr > (mrpdu_msg_eof - (1 + 4 + 1 + 4)))
#else
	/* need at least 6 bytes for a single vector */
	if (mrpdu_msg_ptr > (mrpdu_msg_eof - 6))
#endif
		goto oops;

	mrpdu_msg = (mrpdu_message_t *) mrpdu_msg_ptr;
	mrpdu_msg->AttributeType = MMRP_SVCREQ_TYPE;
	mrpdu_msg->AttributeLength = 1;

#ifdef MICREL_1588_PTP
	mmrp_prepare_tx(MMRP_SVCREQ_TYPE, lva);

	attrib = MMRP_db->mrp_db.tx_attrib;
	if (attrib) {
		if (MMRP_SVCREQ_TYPE != attrib->type) {
			*bytes_used = 0;
			return 0;
		}
	} else
#endif
	attrib = MMRP_db->attrib_list;

	mrpdu_vectorptr = (mrpdu_vectorattrib_t *) mrpdu_msg->Data;

#ifdef MICREL_1588_PTP
	while ((mrpdu_msg_ptr < (mrpdu_msg_eof - (1 + 2 + 1 + 4))) &&
	       (NULL != attrib)) {
#else
	while ((mrpdu_msg_ptr < (mrpdu_msg_eof - 2)) && (NULL != attrib)) {
#endif

		if (MMRP_SVCREQ_TYPE != attrib->type) {
			attrib = attrib->next;
			continue;
		}

		if (0 == attrib->applicant.tx) {
#ifdef MICREL_1588_PTP
			MMRP_db->mrp_db.registrar_state =
				attrib->registrar.mrp_state;
			mrp_applicant_chk(&MMRP_db->mrp_db, &attrib->applicant);
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
		svcreq_firstval = attrib->attribute.svcreq;
		mrpdu_vectorptr->FirstValue_VectorEvents[0] =
		    attrib->attribute.svcreq;

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
		MMRP_db->mrp_db.registrar_state = attrib->registrar.mrp_state;
		mrp_applicant_chk(&MMRP_db->mrp_db, &attrib->applicant);
#endif

		vectevt_idx = 1;
		numvalues = 1;

		/* now attempt to vectorize contiguous other attributes
		 * which also need to be transmitted
		 */

		vectidx = 2;
		vattrib = attrib->next;

		while (NULL != vattrib) {
			if (MMRP_SVCREQ_TYPE != vattrib->type)
				break;

			if (0 == vattrib->applicant.tx)
				break;

			svcreq_firstval++;

			if (vattrib->attribute.svcreq != svcreq_firstval)
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
			MMRP_db->mrp_db.registrar_state =
				vattrib->registrar.mrp_state;
			mrp_applicant_chk(&MMRP_db->mrp_db,
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

		/* 2 byte header, followed by FirstValues/Vectors - remember vectidx starts at 0 */
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
	MMRP_db->mrp_db.tx_attrib = attrib;
#endif

	if (mrpdu_vectorptr == (mrpdu_vectorattrib_t *) mrpdu_msg->Data) {
		*bytes_used = 0;
		return 0;
	}

	/* endmark */
	*mrpdu_msg_ptr = 0;
	mrpdu_msg_ptr++;
	*mrpdu_msg_ptr = 0;
	mrpdu_msg_ptr++;

	*bytes_used = (mrpdu_msg_ptr - msgbuf);

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
mmrp_emit_macvectors(unsigned char *msgbuf, unsigned char *msgbuf_eof,
		     int *bytes_used, int lva)
{
	mrpdu_vectorattrib_t *mrpdu_vectorptr;
	mrpdu_message_t *mrpdu_msg;
	unsigned char *mrpdu_msg_ptr = msgbuf;
	unsigned char *mrpdu_msg_eof = msgbuf_eof;
	uint16_t numvalues;
	uint8_t vect_3pack;
	int vectidx;
	int vectevt[3];
	int vectevt_idx;
	uint8_t macvec_firstval[6];
	struct mmrp_attribute *attrib, *vattrib;
	int mac_eq;
#ifdef MICREL_1588_PTP
	uint16_t VectorHeader;
	uint8_t *unaligned;
#endif

#ifdef MICREL_1588_PTP
	if (mrpdu_msg_ptr > (mrpdu_msg_eof - (6 + 4 + 1 + 4)))
#else
	/* need at least 11 bytes for a single vector */
	if (mrpdu_msg_ptr > (mrpdu_msg_eof - 11))
#endif
		goto oops;

	mrpdu_msg = (mrpdu_message_t *) mrpdu_msg_ptr;
	mrpdu_msg->AttributeType = MMRP_MACVEC_TYPE;
	mrpdu_msg->AttributeLength = 6;

#ifdef MICREL_1588_PTP
	mmrp_prepare_tx(MMRP_MACVEC_TYPE, lva);

	attrib = MMRP_db->mrp_db.tx_attrib;
	if (attrib) {
		if (MMRP_MACVEC_TYPE != attrib->type) {
			*bytes_used = 0;
			return 0;
		}
	} else
#endif
	attrib = MMRP_db->attrib_list;

	mrpdu_vectorptr = (mrpdu_vectorattrib_t *) mrpdu_msg->Data;

#ifdef MICREL_1588_PTP
	while ((mrpdu_msg_ptr <= (mrpdu_msg_eof - (6 + 2 + 1 + 4))) &&
	       (NULL != attrib)) {
#else
	while ((mrpdu_msg_ptr < (mrpdu_msg_eof - 2)) && (NULL != attrib)) {
#endif

		if (MMRP_MACVEC_TYPE != attrib->type) {
			attrib = attrib->next;
			continue;
		}

		if (0 == attrib->applicant.tx) {
#ifdef MICREL_1588_PTP
			MMRP_db->mrp_db.registrar_state =
				attrib->registrar.mrp_state;
			mrp_applicant_chk(&MMRP_db->mrp_db, &attrib->applicant);
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
		memcpy(macvec_firstval, attrib->attribute.macaddr, 6);
		memcpy(mrpdu_vectorptr->FirstValue_VectorEvents,
		       attrib->attribute.macaddr, 6);

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
		MMRP_db->mrp_db.registrar_state = attrib->registrar.mrp_state;
		mrp_applicant_chk(&MMRP_db->mrp_db, &attrib->applicant);
#endif

		vectevt_idx = 1;
		numvalues = 1;

		vectevt[1] = 0;
		vectevt[2] = 0;

		/* now attempt to vectorize contiguous other attributes
		 * which also need to be transmitted
		 */

		vectidx = 6;
		vattrib = attrib->next;

		while (NULL != vattrib) {
			if (MMRP_MACVEC_TYPE != vattrib->type)
				break;

			if (0 == vattrib->applicant.tx)
				break;

			mmrp_increment_macaddr(macvec_firstval);

			mac_eq =
			    memcmp(vattrib->attribute.macaddr, macvec_firstval,
				   6);

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
			MMRP_db->mrp_db.registrar_state =
				vattrib->registrar.mrp_state;
			mrp_applicant_chk(&MMRP_db->mrp_db,
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
			    > (mrpdu_msg_eof - 11))
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

		/* 2 byte header, followed by FirstValues/Vectors - remember vectidx starts at 0 */
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
	MMRP_db->mrp_db.tx_attrib = attrib;
#endif

	if (mrpdu_vectorptr == (mrpdu_vectorattrib_t *) mrpdu_msg->Data) {
		*bytes_used = 0;
		return 0;
	}

	/* endmark */
	*mrpdu_msg_ptr = 0;
	mrpdu_msg_ptr++;
	*mrpdu_msg_ptr = 0;
	mrpdu_msg_ptr++;

	*bytes_used = (mrpdu_msg_ptr - msgbuf);

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

int mmrp_txpdu(void)
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

	/* note that MMRP frames should always be untagged (no vlan) */
	eth->typelen = htons(MMRP_ETYPE);
	memcpy(eth->destaddr, MMRP_ADDR, sizeof(eth->destaddr));
	memcpy(eth->srcaddr, STATION_ADDR, sizeof(eth->srcaddr));

	msgbuf_wrptr += sizeof(eth_hdr_t);

	mrpdu = (mrpdu_t *) msgbuf_wrptr;

	/*
	 * ProtocolVersion handling - a receiver must process received frames with a lesser
	 * protcol version consistent with the older protocol processing requirements (e.g. a V2
	 * agent receives a V1 message, the V1 message shoudl be parsed with V1 rules).
	 *
	 * However - if an agent receives a NEWER protocol, the agent shoudl still attempt
	 * to parse the frame. If the agent finds an AttributeType not recognized
	 * the agent discards the current message including any associated trailing vectors
	 * up to the end-mark, and resumes with the next message or until the end of the PDU
	 * is reached.
	 *
	 * If a VectorAttribute is found with an unknown Event for the Type, the specific
	 * VectorAttrute is discarded and processing continues with the next VectorAttribute.
	 */

	mrpdu->ProtocolVersion = MMRP_PROT_VER;
	mrpdu_msg_ptr = MRPD_GET_MRPDU_MESSAGE_LIST(mrpdu);
	mrpdu_msg_eof = (unsigned char *)msgbuf + MAX_FRAME_SIZE;

	/*
	 * Iterate over all attributes, transmitting those marked
	 * with 'tx', attempting to coalesce multiple contiguous tx attributes
	 * with appropriate vector encodings.
	 *
	 * MMRP_MACVEC_TYPE FirstValue is the 6-byte MAC address, with
	 * corresponding attrib_length=6
	 *
	 * MMRP_SVCREQ_TYPE FirstValue is a single byte - values follow,
	 * attrib_length=1
	 *
	 * MMRP uses ThreePackedEvents for all vector encodings
	 *
	 * the expanded version of the MRPDU looks like
	 * ProtocolVersion
	 * AttributeType
	 * AttributeLength
	 * <Variable number of>
	 *              LeaveAllEvent | NumberOfValues
	 *              <Variable FirstValue>
	 *              <VectorEventBytes>
	 * EndMark
	 *
	 * in effect, each AttributeType present gets its own 'message' with
	 * variable number of vectors. So with MMRP, you will have at most
	 * two messages (SVCREQ or MACVEC)
	 */

#ifndef MICREL_1588_PTP
	if (MMRP_db->mrp_db.lva.tx) {
		lva = 1;
		MMRP_db->mrp_db.lva.tx = 0;
	}
#endif

#ifdef MICREL_1588_PTP
	/* Check sending LeaveAll for MAC attribute type. */
	lva = 0;
	if (MMRP_db->mrp_db.lva.tx & 1)
		lva = 1;
#endif
	rc = mmrp_emit_macvectors(mrpdu_msg_ptr, mrpdu_msg_eof, &bytes, lva);
#ifndef MICREL_1588_PTP
	if (-1 == rc)
		goto out;
#endif

	mrpdu_msg_ptr += bytes;

#ifdef MICREL_1588_PTP
	/* LeaveAll for MAC attribute type sent. */
	if (bytes)
		MMRP_db->mrp_db.lva.tx &= ~1;

	/* No more space. */
	if (-1 == rc)
		goto send;

	/* Check sending LeaveAll for SVC attribute type. */
	lva = 0;
	if (MMRP_db->mrp_db.lva.tx & 2)
		lva = 1;
#else
	if (mrpdu_msg_ptr >= (mrpdu_msg_eof - 2))
		goto out;
#endif

	rc = mmrp_emit_svcvectors(mrpdu_msg_ptr, mrpdu_msg_eof, &bytes, lva);
#ifndef MICREL_1588_PTP
	if (-1 == rc)
		goto out;
#endif

	mrpdu_msg_ptr += bytes;

#ifdef MICREL_1588_PTP
	/* LeaveAll for SVC attribute type sent. */
	if (bytes)
		MMRP_db->mrp_db.lva.tx &= ~2;

	/* No more space. */
	if (-1 == rc)
		goto send;

send:
#endif

	/* endmark */

	if (mrpdu_msg_ptr == MRPD_GET_MRPDU_MESSAGE_LIST(mrpdu)) {
		free(msgbuf);
		return 0;
	}

	if (mrpdu_msg_ptr <= (mrpdu_msg_eof - 2)) {
		*mrpdu_msg_ptr = 0;
		mrpdu_msg_ptr++;
		*mrpdu_msg_ptr = 0;
		mrpdu_msg_ptr++;
	} else
		goto out;

	msgbuf_len = mrpdu_msg_ptr - msgbuf;

	bytes = mrpd_send(mmrp_socket, msgbuf, msgbuf_len, 0);
#if LOG_MMRP
	mrpd_log_printf("MMRP send PDU\n");
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
if (ofp && !bytes && MMRP_db->attrib_list)
fprintf(ofp, " %s nothing to send\n", __func__);
	return rc;
#else
	/* caller should assume TXLAF */
	return -1;
#endif
}

#ifdef MICREL_1588_PTP
static void to_mac(struct mmrp_attribute *rattrib,
	struct MRP_mac *mac)
{
	if (MMRP_MACVEC_TYPE == rattrib->type) {
		memcpy(mac->addr, rattrib->attribute.macaddr, 6);
	} else {
		mac->addr[0] = rattrib->attribute.svcreq;
	}
}

static int mmrp_propagate(struct mmrp_attribute *rattrib, int notify)
{
	int rc = 0;

	if (MMRP_MACVEC_TYPE == rattrib->type) {
		struct MRP_mac mac;

		to_mac(rattrib, &mac);
		if (MRP_NOTIFY_LV == notify)
			rc = set_mac_lv(fd, mrp_index + 1, &mac);
		else
			rc = set_mac_rx(fd, mrp_index + 1, &mac);
		rc = handle_propagation(rc, notify);
		if (rc)
			goto mmrp_propagate_done;
	} else if (MMRP_SVCREQ_TYPE == rattrib->type) {
		struct MRP_mac svc;

		to_mac(rattrib, &svc);
		if (MRP_NOTIFY_LV == notify)
			rc = set_mac_lv(fd, mrp_index + 1, &svc);
		else
			rc = set_mac_rx(fd, mrp_index + 1, &svc);
		rc = handle_propagation(rc, notify);
		if (rc)
			goto mmrp_propagate_done;
	}

mmrp_propagate_done:
	return rc;
}

#endif

int mmrp_send_notifications(struct mmrp_attribute *attrib, int notify)
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

	if (MMRP_SVCREQ_TYPE == attrib->type) {
		sprintf(variant, "S=%d", attrib->attribute.svcreq);
	} else {
		sprintf(variant, "M=%02x%02x%02x%02x%02x%02x",
			attrib->attribute.macaddr[0],
			attrib->attribute.macaddr[1],
			attrib->attribute.macaddr[2],
			attrib->attribute.macaddr[3],
			attrib->attribute.macaddr[4],
			attrib->attribute.macaddr[5]);
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
		snprintf(msgbuf, MAX_MRPD_CMDSZ - 1, "MNE %s %s %s\n", variant, regsrc, mrp_state);
		break;
	case MRP_NOTIFY_JOIN:
		snprintf(msgbuf, MAX_MRPD_CMDSZ - 1, "MJO %s %s %s\n",  variant, regsrc, mrp_state);
		break;
	case MRP_NOTIFY_LV:
		snprintf(msgbuf, MAX_MRPD_CMDSZ - 1, "MLE %s %s %s\n",  variant, regsrc, mrp_state);
		break;
	default:
		goto free_msgbuf;
		break;
	}

#ifdef MICREL_1588_PTP
if (ofp)
fprintf(ofp, "%s %s", __func__, msgbuf);
	new_client = MMRP_db->mrp_db.new_client;
	reclaim = MMRP_db->mrp_db.reclaim;
	if (mrp_port > 1 && !new_client && !reclaim) {
		int rc = mmrp_propagate(attrib, notify);

		/* Skip notifying the host. */
		if (rc != 1)
			goto free_msgbuf;
	}
	old_index = mrp_index;
	mrp_index = 0;
	MMRP_db = MMRP_dbs[mrp_index];
#endif
	client = MMRP_db->mrp_db.clients;
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
	MMRP_db = MMRP_dbs[mrp_index];
#endif

 free_msgbuf:
	if (variant)
		free(variant);
	if (regsrc)
		free(regsrc);
	free(msgbuf);
	return 0;
}

int mmrp_dumptable(struct sockaddr_in *client)
{
	char *msgbuf;
	char *msgbuf_wrptr;
	char *stage;
	char *variant;
	char *regsrc;
	struct mmrp_attribute *attrib;
	int m = 0;
	int n;
#ifdef MICREL_1588_PTP

	if (!client)
		return 0;
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

	attrib = MMRP_db->attrib_list;

	if (attrib == NULL) {
		sprintf(msgbuf, "MMRP:Empty\n");
	}

	while (NULL != attrib) {
		if (MMRP_SVCREQ_TYPE == attrib->type) {
			sprintf(variant, "S=%d", attrib->attribute.svcreq);
		} else {
			sprintf(variant, "M=%02x%02x%02x%02x%02x%02x",
				attrib->attribute.macaddr[0],
				attrib->attribute.macaddr[1],
				attrib->attribute.macaddr[2],
				attrib->attribute.macaddr[3],
				attrib->attribute.macaddr[4],
				attrib->attribute.macaddr[5]);
		}
		sprintf(regsrc, "R=%02x%02x%02x%02x%02x%02x",
			attrib->registrar.macaddr[0],
			attrib->registrar.macaddr[1],
			attrib->registrar.macaddr[2],
			attrib->registrar.macaddr[3],
			attrib->registrar.macaddr[4],
			attrib->registrar.macaddr[5]);
		switch (attrib->registrar.mrp_state) {
		case MRP_IN_STATE:
			sprintf(stage, "MIN %s %s\n", variant, regsrc);
			break;
		case MRP_LV_STATE:
			sprintf(stage, "MLV %s %s\n", variant, regsrc);
			break;
		case MRP_MT_STATE:
			sprintf(stage, "MMT %s %s\n", variant, regsrc);
			break;
		default:
			break;
		}
		n = sprintf(msgbuf_wrptr, "%s", stage);
		if (m < n)
			m = n;
		msgbuf_wrptr += strnlen(stage, 128);
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

int mmrp_cmd_parse_mac(char *buf, int buflen, uint8_t * mac, int *err_index)
{
	struct parse_param specs[] = {
		{"M" PARSE_ASSIGN, parse_mac, mac},
		{0, parse_null, 0}
	};
	if (buflen < 17)
		return -1;
	memset(mac, 0, 6);
	return parse(buf + 4, buflen - 4, specs, err_index);
}

int mmrp_cmd_mac(uint8_t * mac, int mrp_event)
{
	struct mmrp_attribute *attrib;

#ifdef MICREL_1588_PTP_DEV
	static uint8_t last_addr[2];

	int i = 0;
	int num = 0;
	int test = 0;
#endif

#ifdef MICREL_1588_PTP
	if (mrp_port > 1) {
		int notify;
		int rc;
		struct mmrp_attribute copy;
		struct MRP_mac mrp_mac;

		attrib = &copy;
		if (MRP_EVENT_LV == mrp_event)
			notify = MRP_NOTIFY_LV;
		else if (MRP_EVENT_NEW == mrp_event)
			notify = MRP_NOTIFY_NEW;
		else
			notify = MRP_NOTIFY_JOIN;
		attrib->type = MMRP_MACVEC_TYPE;
		memcpy(attrib->attribute.macaddr, mac, 6);
		to_mac(attrib, &mrp_mac);
		if (MRP_EVENT_LV == mrp_event)
			rc = set_mac_lv(fd, 0, &mrp_mac);
		else
			rc = set_mac_rx(fd, 0, &mrp_mac);
		rc = handle_propagation(rc, notify);
		if (1 == rc)
			rc = 0;
		return rc;
	}
#endif

#ifdef MICREL_1588_PTP_DEV
	if ((mac[4] & 0x80)) {
		test = (mac[4] >> 4) & 0x7;
		num = mac[4] & 0xf;
		num <<= 8;
		num |= mac[5];
		--num;
		mac[4] = last_addr[0];
		mac[5] = last_addr[1] + 1;
		i = num;
	} else {
		last_addr[0] = mac[4];
		last_addr[1] = mac[5];
	}
next:
#endif

	attrib = mmrp_alloc();
	if (NULL == attrib)
		return -1;
	attrib->type = MMRP_MACVEC_TYPE;
	memcpy(attrib->attribute.macaddr, mac, 6);
	mmrp_event(mrp_event, attrib);

#ifdef MICREL_1588_PTP_DEV
	if (i) {
		unsigned char addr = mac[5];

		switch (test) {
		case 2:
			if (num > 23 && i > num - 23)
				mac[5] += 1;
			else
				mac[5] += 2;
			break;
		case 3:
			if (num > 164 && i > num - 164)
				mac[5] += 2;
			else
				mac[5] += 1;
			break;
		case 1:
		default:
			mac[5] += 1;
			break;
		}
		if (mac[5] < addr) {
			mac[4]++;
			if (0 == mac[4])
				mac[3]++;
		}
		--i;
		goto next;
	}
#endif
	return 0;
}

int mmrp_cmd_parse_service(char *buf, int buflen,
			   uint8_t * service, int *err_index)
{
	struct parse_param specs[] = {
		{"S" PARSE_ASSIGN, parse_u8, service},
		{0, parse_null, 0}
	};
	*service = 0;
	if (buflen < 5)
		return -1;
	return parse(buf + 4, buflen - 4, specs, err_index);
}

int mmrp_cmd_service(uint8_t service, int mrp_event)
{
	struct mmrp_attribute *attrib;

#ifdef MICREL_1588_PTP
	if (mrp_port > 1) {
		int notify;
		int rc;
		struct mmrp_attribute copy;
		struct MRP_mac mac;

		attrib = &copy;
		if (MRP_EVENT_LV == mrp_event)
			notify = MRP_NOTIFY_LV;
		else if (MRP_EVENT_NEW == mrp_event)
			notify = MRP_NOTIFY_NEW;
		else
			notify = MRP_NOTIFY_JOIN;
		attrib->type = MMRP_SVCREQ_TYPE;
		attrib->attribute.svcreq = service;
		to_mac(attrib, &mac);
		if (MRP_EVENT_LV == mrp_event)
			rc = set_mac_lv(fd, 0, &mac);
		else
			rc = set_mac_rx(fd, 0, &mac);
		rc = handle_propagation(rc, notify);
		if (1 == rc)
			rc = 0;
		return rc;
	}
#endif

	attrib = mmrp_alloc();
	if (NULL == attrib)
		return -1;
	attrib->type = MMRP_SVCREQ_TYPE;
	attrib->attribute.svcreq = service;
	mmrp_event(mrp_event, attrib);
	return 0;
}

int mmrp_recv_cmd(char *buf, int buflen, struct sockaddr_in *client)
{
	int rc;
	int err_index;
	char respbuf[12];
	int mrp_event;
	uint8_t svcreq_param;
	uint8_t macvec_param[6];

	if (NULL == MMRP_db) {
		snprintf(respbuf, sizeof(respbuf) - 1, "ERC %s\n", buf);
		mrpd_send_ctl_msg(client, respbuf, sizeof(respbuf));
		goto out;
	}

	rc = mrp_client_add(&(MMRP_db->mrp_db.clients), client);
#ifdef MICREL_1588_PTP
	if (rc < 0)
		return rc;
	/* It is a new client. */
	if (1 == rc) {
		struct mmrp_attribute *attrib;
		int i;

		for (i = 0; i < mrp_port; i++) {
			mrp_index = i;
			MMRP_db = MMRP_dbs[mrp_index];
			MMRP_db->mrp_db.new_client = client;

			attrib = MMRP_db->attrib_list;
			while (NULL != attrib) {

				/* Notify host when it is started. */
				if (MRP_IN_STATE ==
				    attrib->registrar.mrp_state) {
					mmrp_send_notifications(attrib,
						MRP_NOTIFY_NEW);
				}
				attrib = attrib->next;
			}
			MMRP_db->mrp_db.new_client = NULL;
		}
		mrp_index = 0;
		MMRP_db = MMRP_dbs[mrp_index];
	}
#endif

	if (buflen < 3)
		return -1;

	if ('M' != buf[0])
		return -1;

	/*
	 * M?? - query MMRP Registrar MAC Address database
	 * M+? - JOIN a MAC address or service declaration
	 * M++   NEW a MAC Address (XXX: MMRP doesn't use 'New' though?)
	 * M-- - LV a MAC address or service declaration
	 */
	if (strncmp(buf, "M??", 3) == 0) {
		mmrp_dumptable(client);
	} else if (strncmp(buf, "M--:S", 5) == 0) {
		rc = mmrp_cmd_parse_service(buf, buflen, &svcreq_param,
					    &err_index);
		if (rc)
			goto out_ERP;
		rc = mmrp_cmd_service(svcreq_param, MRP_EVENT_LV);
		if (rc)
			goto out_ERI;
	} else if (strncmp(buf, "M--:M", 5) == 0) {
		/*
		 * XXX note could also register VID with mac address if we ever wanted to
		 * support more than one Spanning Tree context
		 */

		/* buf[] should look similar to 'M--:M=010203040506' */
		rc = mmrp_cmd_parse_mac(buf, buflen, macvec_param, &err_index);
		if (rc)
			goto out_ERP;
		rc = mmrp_cmd_mac(macvec_param, MRP_EVENT_LV);
		if (rc)
			goto out_ERI;
	} else if ((strncmp(buf, "M++:S", 5) == 0)
		   || (strncmp(buf, "M+?:S", 5) == 0)) {
		/* buf[] should look similar to 'M+?:S=1' or 'M++:S=1'
		 */
		rc = mmrp_cmd_parse_service(buf, buflen, &svcreq_param,
					    &err_index);
		if (rc)
			goto out_ERP;
		if ('?' == buf[2]) {
			mrp_event = MRP_EVENT_JOIN;
		} else {
			mrp_event = MRP_EVENT_NEW;
		}
		rc = mmrp_cmd_service(svcreq_param, mrp_event);
		if (rc)
			goto out_ERI;
	} else if ((strncmp(buf, "M++:M", 5) == 0)
		   || (strncmp(buf, "M+?:M", 5) == 0)) {
		/* buf[] should look similar to 'M+?:M=010203040506' */
		rc = mmrp_cmd_parse_mac(buf, buflen, macvec_param, &err_index);
		if (rc)
			goto out_ERP;
		if ('?' == buf[2]) {
			mrp_event = MRP_EVENT_JOIN;
		} else {
			mrp_event = MRP_EVENT_NEW;
		}
		rc = mmrp_cmd_mac(macvec_param, mrp_event);
		if (rc)
			goto out_ERI;
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

int mmrp_init(int mmrp_enable)
{
	int rc;

	/* XXX doesn't handle re-start */

	mmrp_socket = INVALID_SOCKET;
	MMRP_db = NULL;

	if (0 == mmrp_enable) {
		return 0;
	}

#ifdef MICREL_1588_PTP
	mrp_index = 0;

next_port:
#endif
	rc = mrpd_init_protocol_socket(MMRP_ETYPE, &mmrp_socket, MMRP_ADDR);
	if (rc < 0)
		return -1;

	MMRP_db = malloc(sizeof(struct mmrp_database));

	if (NULL == MMRP_db)
		goto abort_socket;

	memset(MMRP_db, 0, sizeof(struct mmrp_database));

	/* if registration is FIXED or FORBIDDEN
	 * updates from MRP are discarded, and
	 * only IN and JOININ messages are sent
	 */
	MMRP_db->mrp_db.registration = MRP_REGISTRAR_CTL_NORMAL;	/* default */

	/* if participant role is 'SILENT' (or non-participant)
	 * applicant doesn't send any messages -
	 *
	 * Note - theoretically configured per-attribute
	 */
	MMRP_db->mrp_db.participant = MRP_APPLICANT_CTL_NORMAL;	/* default */

	rc = mrpd_init_timers(&(MMRP_db->mrp_db));

	if (rc < 0)
		goto abort_alloc;

	mrp_lvatimer_fsm(&(MMRP_db->mrp_db), MRP_EVENT_BEGIN);
#ifdef MICREL_1588_PTP
	mmrp_sockets[mrp_index] = mmrp_socket;
	MMRP_dbs[mrp_index] = MMRP_db;
	++mrp_index;
	if (mrp_index < mrp_port)
		goto next_port;
#endif
	return 0;

 abort_alloc:
	/* free MMRP_db and related structures */
	free(MMRP_db);
	MMRP_db = NULL;
 abort_socket:
	mrpd_close_socket(mmrp_socket);
	mmrp_socket = INVALID_SOCKET;
	/* XXX */
	return -1;
}

int mmrp_reclaim(void)
{
	struct mmrp_attribute *mattrib, *free_mattrib;

	if (NULL == MMRP_db)
		return 0;

#ifdef MICREL_1588_PTP
if (ofp) {
if (2 == MMRP_db->mrp_db.reclaim)
	fprintf(ofp, "cleanup\n");
else if (MMRP_db->attrib_list)
	fprintf(ofp, "%s\n", __func__);
}
	MMRP_db->mrp_db.reclaim = 1;
#endif
	mattrib = MMRP_db->attrib_list;
	while (NULL != mattrib) {
		if ((mattrib->registrar.mrp_state == MRP_MT_STATE) &&
#ifdef MICREL_1588_PTP
		    mattrib->applicant.aging <= 1 &&
#endif
		    ((mattrib->applicant.mrp_state == MRP_VO_STATE) ||
		     (mattrib->applicant.mrp_state == MRP_AO_STATE) ||
		     (mattrib->applicant.mrp_state == MRP_QO_STATE))) {
			if (NULL != mattrib->prev)
				mattrib->prev->next = mattrib->next;
			else
				MMRP_db->attrib_list = mattrib->next;
			if (NULL != mattrib->next)
				mattrib->next->prev = mattrib->prev;
			free_mattrib = mattrib;
			mattrib = mattrib->next;
			mmrp_send_notifications(free_mattrib, MRP_NOTIFY_LV);
			free(free_mattrib);
		} else
			mattrib = mattrib->next;
	}
#ifdef MICREL_1588_PTP
	MMRP_db->mrp_db.reclaim = 0;
#endif
	return 0;
}

void mmrp_bye(struct sockaddr_in *client)
{
#ifdef MICREL_1588_PTP
if (ofp) {
fprintf(ofp, "   %s %p\n", __func__, client);
fflush(ofp);
}
#endif
	if (NULL != MMRP_db)
		mrp_client_delete(&(MMRP_db->mrp_db.clients), client);
}
