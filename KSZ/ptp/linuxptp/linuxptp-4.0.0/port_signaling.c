/**
 * @file port_signaling.c
 * @brief Implements signaling messages
 * @note Copyright (C) 2018 Richard Cochran <richardcochran@gmail.com>
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
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1335 USA.
 */
#include "port.h"
#include "port_private.h"
#include "print.h"
#include "unicast_client.h"
#include "unicast_service.h"

const struct PortIdentity wildcard_pid = {
	.clockIdentity = {
		{0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff}
	},
	.portNumber = 0xffff,
};

struct ptp_message *port_signaling_construct(struct port *p,
					     const struct PortIdentity *tpid)
{
	struct ptp_message *msg;

	msg = msg_allocate();
	if (!msg) {
		return NULL;
	}
	msg->hwts.type                 = p->timestamping;
	msg->header.tsmt               = SIGNALING | p->transportSpecific;
	msg->header.ver                = PTP_VERSION;
	msg->header.messageLength      = sizeof(struct signaling_msg);
	msg->header.domainNumber       = clock_domain_number(p->clock);
	msg->header.sourcePortIdentity = p->portIdentity;
	msg->header.sequenceId         = p->seqnum.signaling++;
	msg->header.logMessageInterval = 0x7F;
	msg->signaling.targetPortIdentity = *tpid;

	return msg;
}

struct ptp_message *port_signaling_uc_construct(struct port *p,
						struct address *address,
						struct PortIdentity *tpid)
{
	struct ptp_message *msg;

	msg = port_signaling_construct(p, tpid);
	if (!msg) {
		return NULL;
	}

	msg->header.flagField[0] |= UNICAST;
	msg->address = *address;

	return msg;
}

static int8_t set_interval(int8_t current_interval,
			   int8_t new_interval,
			   int8_t initial_interval)
{
	switch (new_interval) {
	case SIGNAL_NO_CHANGE:
		return current_interval;
	case SIGNAL_SET_INITIAL:
		return initial_interval;
	default:
		return new_interval;
	}
}

static int process_interval_request(struct port *p,
				    struct msg_interval_req_tlv *r)
{

	p->logAnnounceInterval = set_interval(p->logAnnounceInterval,
					      r->announceInterval,
					      p->initialLogAnnounceInterval);

	p->logSyncInterval = set_interval(p->logSyncInterval,
					  r->timeSyncInterval,
					  p->initialLogSyncInterval);

	p->logPdelayReqInterval = set_interval(p->logPdelayReqInterval,
					       r->linkDelayInterval,
					       p->logMinPdelayReqInterval);

	return 0;
}

static int process_interface_rate(struct port *p,
                                 struct msg_interface_rate_tlv *r)
{
       Integer64 delayAsymmetry;
       double    nsDelay;
       Integer64 slaveBitPeriod;
       Integer64 masterBitPeriod;

       if (p->iface_rate_tlv && interface_ifinfo_valid(p->iface)) {
               slaveBitPeriod = interface_bitperiod(p->iface);
               masterBitPeriod = r->interfaceBitPeriod;

               /* Delay Asymmetry Calculation */
               nsDelay = (double)(masterBitPeriod - slaveBitPeriod) / (2 * 1.0e9);
               delayAsymmetry =
                       (r->numberOfBitsAfterTimestamp - r->numberOfBitsBeforeTimestamp)  * nsDelay;

               if (delayAsymmetry != p->portAsymmetry) {
                       p->asymmetry += ((delayAsymmetry - p->portAsymmetry) << 16);
                       p->portAsymmetry = delayAsymmetry;
               }
       }
       return 0;
}

int process_signaling(struct port *p, struct ptp_message *m)
{
	struct tlv_extra *extra;
	struct organization_tlv *org;
	struct msg_interval_req_tlv *r;
	struct msg_interface_rate_tlv *rate;
	int err = 0, result;

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

	/* Ignore signaling messages not addressed to this port. */
	if (!pid_eq(&m->signaling.targetPortIdentity, &p->portIdentity) &&
	    !pid_eq(&m->signaling.targetPortIdentity, &wildcard_pid)) {
		return 0;
	}

	TAILQ_FOREACH(extra, &m->tlv_list, list) {
		switch (extra->tlv->type) {
		case TLV_REQUEST_UNICAST_TRANSMISSION:
			result = unicast_service_add(p, m, extra);
			switch (result) {
			case SERVICE_GRANTED:
				err = unicast_service_grant(p, m, extra);
				break;
			case SERVICE_DENIED:
				err = unicast_service_deny(p, m, extra);
				break;
			case SERVICE_DISABLED:
			default:
				break;
			}
			break;

		case TLV_GRANT_UNICAST_TRANSMISSION:
			unicast_client_grant(p, m, extra);
			break;

		case TLV_CANCEL_UNICAST_TRANSMISSION:
			err = unicast_client_cancel(p, m, extra);
			unicast_service_remove(p, m, extra);
			break;

		case TLV_ACKNOWLEDGE_CANCEL_UNICAST_TRANSMISSION:
			break;

		case TLV_ORGANIZATION_EXTENSION:
			org = (struct organization_tlv *)extra->tlv;

			if (0 == memcmp(org->id, ieee8021_id, sizeof(ieee8021_id)) &&
			    org->subtype[0] == 0 && org->subtype[1] == 0 && org->subtype[2] == 2) {
				r = (struct msg_interval_req_tlv *) extra->tlv;
				err = process_interval_request(p, r);
			} else if (0 == memcmp(org->id, itu_t_id, sizeof(itu_t_id)) &&
				   org->subtype[0] == 0 && org->subtype[1] == 0 && org->subtype[2] == 2) {
				rate = (struct msg_interface_rate_tlv *) extra->tlv;
				err = process_interface_rate(p, rate);
			}
			break;
		}
	}
	return err;
}

int port_tx_interval_request(struct port *p,
			     Integer8 announceInterval,
			     Integer8 timeSyncInterval,
			     Integer8 linkDelayInterval)
{
	struct msg_interval_req_tlv *mir;
	struct PortIdentity tpid;
	struct ptp_message *msg;
	struct tlv_extra *extra;
	int err;

	if (!port_capable(p)) {
		return 0;
	}
	memset(&tpid, 0xff, sizeof(tpid));
	msg = port_signaling_construct(p, &tpid);
	if (!msg) {
		return -1;
	}
	extra = msg_tlv_append(msg, sizeof(*mir));
	if (!extra) {
		err = -1;
		goto out;
	}
	mir = (struct msg_interval_req_tlv *) extra->tlv;
	mir->type = TLV_ORGANIZATION_EXTENSION;
	mir->length = sizeof(*mir) - sizeof(mir->type) - sizeof(mir->length);
	memcpy(mir->id, ieee8021_id, sizeof(ieee8021_id));
	mir->subtype[2] = 2;
	mir->timeSyncInterval = timeSyncInterval;
	mir->announceInterval = announceInterval;
	mir->linkDelayInterval = linkDelayInterval;
	mir->flags = 0;

	err = port_prepare_and_send(p, msg, TRANS_GENERAL);
	if (err) {
		pr_err("%s: send signaling failed", p->log_name);
	}
out:
	msg_put(msg);
	return err;
}
