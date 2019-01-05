#include "wnp.h"
#include "unpifi.h"
#include "datatype.h"

#ifndef _SYS_SOCKET_H
#include <sys\timeb.h>
#include <process.h>
#include "ip_icmp.h"

#else
#include <net/if.h>
#include <linux/sockios.h>
#include <linux/if_packet.h>
#define ARPHRD_ETHER 	1		/* Ethernet 10Mbps		*/
#include <linux/if_ether.h>
#include <sys/timeb.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "wrapthread.h"
#ifndef IPV6_TCLASS
#define IPV6_TCLASS		67
#endif

#define _PATH_PROCNET_IFINET6           "/proc/net/if_inet6"

struct ipv6_info {
	char devname[20];
	struct sockaddr_in6 addr;
	int plen;
	int scope;
	int if_idx;
};

#define _PATH_SYSNET_DEV		"/sys/class/net/"

#define NETDEV_ADDRESS			"address"
#define NETDEV_FLAGS			"flags"
#define NETDEV_IFINDEX			"ifindex"
#define NETDEV_OPERSTATE		"operstate"

#endif


#if defined(_MSC_VER)
typedef uint8_t u8;
typedef int16_t s16;
typedef uint16_t u16;
typedef uint32_t u32;
typedef int64_t s64;
typedef uint64_t u64;

#include <packon.h>
#define __packed;
#endif

#if defined(__GNUC__)
#ifndef __packed
#define __packed __attribute__((packed))
#endif
#endif

#ifdef _SYS_SOCKET_H

#define USE_NET_IOCTL
#define USE_TIMESTAMP_OPER

#include "ksz_ptp.c"
#else
#include "ksz_ptp.h"
#endif

#define PTP_PROTO		0x88F7

#define HSR_PROTO		0x892F

#define HSR_NETWORK_ID_SHIFT	13
#define HSR_LANE_ID_SHIFT	12

struct hsr_hdr {
	u16 messageLength;
	u16 sequenceId;
	u16 proto;
} __packed;

#define PRP_PROTO		0x88FB

#define PRP_LANE_ID_SHIFT	12

struct prp_trailer {
	u16 sequenceId;
	u16 messageLength;
	u16 proto;
} __packed;

#if defined(_MSC_VER)
#include <packoff.h>
#endif


int gWaitDelay = 500;

char *PTP_ip_addr = "224.0.1.129";
char *P2P_ip_addr = "224.0.0.107";
char *PTP_ip_addr6_const = "ff02::0181";
char *P2P_ip_addr6_const = "ff02::6b";
char PTP_ip_addr6[20];
char P2P_ip_addr6[20];

#define PTP_EVENT_PORT			319
#define PTP_GENERAL_PORT		320

int ip_family;
int ipv6_interface = 0;
int dbg_rcv = 0;
int hsr = 0;
int prp = 0;
int prp_size = 60;
int ptp_proto = PTP_PROTO;
int port_acl_test = 0;

SOCKET event_fd;
SOCKET general_fd;
SOCKET uni_event_fd;
SOCKET uni_general_fd;
SOCKET management4_fd;
SOCKET eth_fd;

SOCKET *sockptr;
char devname[20];
struct dev_info ptpdev;

int event_msgs[] = {
	SYNC_MSG,
	DELAY_REQ_MSG,
	PDELAY_REQ_MSG,
	PDELAY_RESP_MSG,
	-1
};

int general_msgs[] = {
	FOLLOW_UP_MSG,
	DELAY_RESP_MSG,
	PDELAY_RESP_FOLLOW_UP_MSG,
	-1
};

int ptp_2step = 0;
int ptp_alternate = 0;
int ptp_unicast = 0;

struct sockaddr_in event_addr;
struct sockaddr_in general_addr;
struct sockaddr_in p2p_event_addr;
struct sockaddr_in p2p_general_addr;
struct sockaddr_in management_addr;
struct sockaddr_in6 event_addr6;
struct sockaddr_in6 general_addr6;
struct sockaddr_in6 p2p_event_addr6;
struct sockaddr_in6 p2p_general_addr6;
struct sockaddr_in6 management_addr6;
#ifdef _SYS_SOCKET_H
struct sockaddr_ll eth_pdelay_addr;
struct sockaddr_ll eth_others_addr;
u8 *eth_pdelay_buf;
u8 *eth_others_buf;

u8 eth_pdelay[] = { 0x01, 0x80, 0xC2, 0x00, 0x00, 0x0E };
u8 eth_others[] = { 0x01, 0x1B, 0x19, 0x00, 0x00, 0x00 };

u8 hw_addr[ETH_ALEN];

int ptp_hw;

pthread_mutex_t disp_mutex = PTHREAD_MUTEX_INITIALIZER;
#endif

u8 host_addr[16];
u8 host_addr6[16];

typedef struct {
	int fTaskStop;
	int multicast;
	int unicast;
	int management4;
	int *msgs;
	int *acl_test;

#if defined(_WIN32)
	HANDLE hevTaskComplete;
#endif
} TTaskParam, *PTTaskParam;


struct ptp_clock_identity selfClockIdentity;
struct ptp_clock_identity masterClockIdentity;
static int ptp_correction;
static int ptp_count = 1;
static int ptp_domain;
static int ptp_dst_port;
static int ptp_src_port;
static int ptp_on;
static int ptp_rx_port;
static u32 ptp_rx_sec;
static u32 ptp_rx_nsec;
struct ptp_utime ptp_rx_sync[8];
struct ptp_utime ptp_rx_delay[8];
struct ptp_utime ptp_rx_pdelay[8];
struct ptp_utime ptp_rx_pdresp[8];
struct ptp_utime ptp_tx_sync[8];
struct ptp_utime ptp_tx_delay[8];
struct ptp_utime ptp_tx_pdelay[8];
struct ptp_utime ptp_tx_pdresp[8];
static int send_tlv;
static int reserved3;

static u16 seqid_sync;
static u16 seqid_delay_req;
static u16 seqid_pdelay_req;
static u16 seqid_management;
static u16 seqid_signaling;
static u16 seqid_announce;
static u32 sync_sec;

static u16 seqid_hsr;
static u16 seqid_prp;

static u8 transport;

int get_tx_port(int dst_port)
{
	int port;
	int bits = dst_port;

	port = 0;
	while (bits) {
		if ((bits & 1) && bits != 1) {
			port = 0;
			break;
		}
		port++;
		bits >>= 1;
	}
	return port;
}

void prepare_hdr(struct ptp_msg_hdr *hdr, int message, int len, int seqid,
	int ctrl, int interval, struct ptp_clock_identity *id)
{
	len += sizeof(struct ptp_msg_hdr);

	hdr->transportSpecific = transport;
	hdr->messageType = message;
	hdr->reserved1 = 0;
	hdr->versionPTP = 2;
	hdr->messageLength = htons(len);
	hdr->domainNumber = ptp_domain;
	hdr->reserved2 = 0;
	if (ptp_version < 2)
		hdr->reserved2 = ptp_dst_port;
	hdr->flagField.data = 0;
	if (ptp_alternate && (SYNC_MSG == message ||
			FOLLOW_UP_MSG == message ||
			ANNOUNCE_MSG == message ||
			DELAY_RESP_MSG == message))
		hdr->flagField.flag.alternateMasterFlag = 1;
	if (ptp_2step && (SYNC_MSG == message || PDELAY_RESP_MSG == message))
		hdr->flagField.flag.twoStepFlag = 1;
	if (ptp_unicast)
		hdr->flagField.flag.unicastFlag = 1;
	if (ANNOUNCE_MSG == message) {
		hdr->flagField.flag.ptpTimescale = 1;
		hdr->flagField.flag.utcOffsetValid = 1;
	}
	hdr->correctionField.scaled_nsec_hi = 0;
	hdr->correctionField.scaled_nsec_lo = 0;
	if (ptp_correction) {
		hdr->correctionField.scaled_nsec_hi =
			htonl(ptp_correction >> 16);
		hdr->correctionField.scaled_nsec_lo =
			htonl(ptp_correction << SCALED_NANOSEC_S);
	}
	hdr->reserved3 = htonl(reserved3);
	memcpy(&hdr->sourcePortIdentity.clockIdentity, id,
		sizeof(struct ptp_clock_identity));
	hdr->sourcePortIdentity.port = htons(1);
	hdr->sequenceId = htons(seqid);
	hdr->controlField = ctrl;
	hdr->logMessageInterval = interval;
}

void *tlv_msg(void *msg, int *size, u16 tlvType, int ext)
{
	struct ptp_tlv *tlv = msg;
	int len = 0;

	switch (tlvType) {
	case TLV_ORGANIZATION_EXTENSION:
	{
		struct ptp_organization_ext_tlv *org = msg;
		struct IEEE_C37_238_data *data =
			(struct IEEE_C37_238_data *) org->dataField;
		struct IEEE_802_1AS_data_1 *avb =
			(struct IEEE_802_1AS_data_1 *) org->dataField;

		switch (ext) {
		case 0:
			org->organizationId[0] = 0x1C;
			org->organizationId[1] = 0x12;
			org->organizationId[2] = 0x9D;
			org->organizationSubType[0] = 0;
			org->organizationSubType[1] = 0;
			org->organizationSubType[2] = 0x01;
			data->grandmasterID = htons(0x00FE);
			data->grandmasterTimeInaccuracy = htonl(50);
			data->networkTimeInaccuracy = htonl(200);
			data->reserved = 0;
			len = sizeof(struct ptp_organization_ext_tlv) - 1 +
				sizeof(struct IEEE_C37_238_data);
			data++;
			msg = data;
			break;
		case 1:
			org->organizationId[0] = 0x00;
			org->organizationId[1] = 0x80;
			org->organizationId[2] = 0xC2;
			org->organizationSubType[0] = 0;
			org->organizationSubType[1] = 0;
			org->organizationSubType[2] = 0x01;
			avb->cumulativeScaledRateOffset = htonl(0);
			avb->gmTimeBaseIndicator = htons(0);
			memset(&avb->lastGmPhaseChange, 0, 12);
			avb->scaledLastGmFreqChange = htonl(0);
			len = sizeof(struct ptp_organization_ext_tlv) - 1 +
				sizeof(struct IEEE_802_1AS_data_1);
			avb++;
			msg = avb;
			break;
		}
		break;
	}
	case TLV_ALTERNATE_TIME_OFFSET_INDICATOR:
	{
		struct ptp_alternate_time_offset_tlv *alt = msg;

		alt->keyField = 0;
		alt->currentOffset = htonl(1000);
		alt->jumpSeconds = htonl(0);
		alt->timeOfNextJump.hi = htons(0);
		alt->timeOfNextJump.lo = htonl(10000000);
		alt->displayName.lengthField = 3;
		alt->displayName.textField[0] = 'P';
		alt->displayName.textField[1] = 'S';
		alt->displayName.textField[2] = 'T';
		len = sizeof(struct ptp_alternate_time_offset_tlv) - 1 +
			alt->displayName.lengthField;
		msg = &alt->displayName.textField[3];
		break;
	}
	default:
		return msg;
	}
	tlv->tlvType = htons(tlvType);
	if (len & 1) {
		u8 *pad = msg;

		*pad = 0;
		msg = pad + 1;
		len++;
	}
	*size += len;
	len -= sizeof(struct ptp_tlv);
	tlv->lengthField = htons(len);
	return msg;
}

struct ptp_msg *signaling_msg(int type, int message, u8 period, u32 duration)
{
	static char payload[(sizeof(struct ptp_msg) + 2000) & ~3];
	struct ptp_msg* msg = (struct ptp_msg *) payload;
	int len;
	int logInterval;
	int seqid;
	int ctrl;
	struct ptp_clock_identity *clock;
	struct ptp_msg_signaling *signaling;
	struct ptp_request_unicast_tlv *request;
	struct ptp_grant_unicast_tlv *grant;
	struct ptp_cancel_unicast_tlv *cancel;

	clock = NULL;
	ctrl = 5;
	logInterval = 0x7F;
	seqid_signaling++;
	seqid = seqid_signaling;
	signaling = &msg->data.signaling;
	switch (type) {
	case TLV_REQUEST_UNICAST_TRANSMISSION:
		clock = &selfClockIdentity;
		memcpy(&signaling->b.targetPortIdentity.clockIdentity,
			&masterClockIdentity,
			sizeof(struct ptp_clock_identity));
		signaling->b.targetPortIdentity.port = htons(0xffff);
		request = signaling->tlv.request;
		request->tlv.tlvType = htons(type);
		request->tlv.lengthField = htons(sizeof(*request) - 4);
		request->messageType = message;
		request->reserved1 = 0;
		request->logInterMessagePeriod = period;
		request->durationField = htonl(duration);
		break;
	case TLV_GRANT_UNICAST_TRANSMISSION:
		clock = &masterClockIdentity;
		memcpy(&signaling->b.targetPortIdentity.clockIdentity,
			&selfClockIdentity,
			sizeof(struct ptp_clock_identity));
		signaling->b.targetPortIdentity.port = htons(1);
		grant = signaling->tlv.grant;
		grant->tlv.tlvType = htons(type);
		grant->tlv.lengthField = htons(sizeof(*grant) - 4);
		grant->messageType = message;
		grant->reserved1 = 0;
		grant->logInterMessagePeriod = period;
		grant->durationField = htonl(duration);
		grant->reserved2 = 0;
		grant->renewal = 1;
		break;
	case TLV_CANCEL_UNICAST_TRANSMISSION:
		clock = &selfClockIdentity;
		memcpy(&signaling->b.targetPortIdentity.clockIdentity,
			&masterClockIdentity,
			sizeof(struct ptp_clock_identity));
		signaling->b.targetPortIdentity.port = htons(0xffff);
		cancel = signaling->tlv.cancel;
		cancel->tlv.tlvType = htons(type);
		cancel->tlv.lengthField = htons(sizeof(*cancel) - 4);
		cancel->messageType = message;
		cancel->reserved1 = 0;
		cancel->reserved2 = 0;
		break;
	case TLV_ACKNOWLEDGE_CANCEL_UNICAST_TRANSMISSION:
		clock = &masterClockIdentity;
		memcpy(&signaling->b.targetPortIdentity.clockIdentity,
			&selfClockIdentity,
			sizeof(struct ptp_clock_identity));
		signaling->b.targetPortIdentity.port = htons(1);
		cancel = signaling->tlv.cancel;
		cancel->tlv.tlvType = htons(type);
		cancel->tlv.lengthField = htons(sizeof(*cancel) - 4);
		cancel->messageType = message;
		cancel->reserved1 = 0;
		cancel->reserved2 = 0;
		break;
	}
	len = sizeof(struct ptp_msg_signaling_base) + 4 +
		ntohs(signaling->tlv.request[0].tlv.lengthField);
	prepare_hdr(&msg->hdr, SIGNALING_MSG, len, seqid, ctrl, logInterval,
		clock);
	return msg;
}

struct ptp_msg *management_msg(int id, int error_id, int n)
{
	static char payload[(sizeof(struct ptp_msg) + 2000) & ~3];
	struct ptp_msg* msg = (struct ptp_msg *) payload;
	int len;
	int logInterval;
	int seqid;
	int ctrl;
	int i;
	int m;
	char ch;
	struct ptp_clock_identity *clock;
	struct ptp_msg_management *management;
	struct ptp_management_error_tlv *error;
	struct ptp_management_tlv *tlv;
	struct ptp_timestamp *ts;
	struct ptp_text *text;

	len = 0;
	clock = &selfClockIdentity;
	ctrl = 4;
	logInterval = 0x7F;
	seqid_management++;
	seqid = seqid_management;
	management = &msg->data.management;
	memcpy(&management->b.targetPortIdentity.clockIdentity,
		&masterClockIdentity, sizeof(struct ptp_clock_identity));
	management->b.targetPortIdentity.port = htons(1);
	management->b.startingBoundaryHops = 5;
	management->b.boundaryHops = 5;
	management->b.actionField = MANAGEMENT_RESPONSE;
	management->b.reserved2 = 0;
	if (error_id) {
		error = management->tlv.error;
		error->tlv.tlvType = htons(TLV_MANAGEMENT_ERROR_STATUS);
		m = 8 + n;
		if (m & 1)
			m++;
		error->tlv.lengthField = htons(m);
		error->managementErrorId = htons(error_id);
		error->managementId = htons(id);
		error->reserved1 = 0;
		text = (struct ptp_text *) error->data;
		if (n > 51)
			text->lengthField = 50;
		else
			text->lengthField = n - 1;
		ch = 'A';
		for (i = 0; i < text->lengthField; i++) {
			text->textField[i] = ch;
			ch++;
			if (ch > 'z')
				ch = 'A';
		}
		for (; i < m; i++)
			text->textField[i] = '\0';
		len = sizeof(struct ptp_msg_management_base) + 4 +
			ntohs(error->tlv.lengthField);
	} else {
		tlv = management->tlv.normal;
		tlv->tlv.tlvType = htons(TLV_MANAGEMENT);
		switch (id) {
		case M_TIME:
			n = 10;
			tlv->tlv.lengthField = htons(2 + n);
			tlv->managementId = htons(M_TIME);
			ts = (struct ptp_timestamp *) tlv->dataField;
			ts->sec.hi = 0;
			ts->sec.lo = htonl(1234);
			ts->nsec = htonl(5678);
			len = sizeof(struct ptp_msg_management_base) + 4 +
				ntohs(tlv->tlv.lengthField);
			break;
		}
	}
	prepare_hdr(&msg->hdr, MANAGEMENT_MSG, len, seqid, ctrl, logInterval,
		clock);
	return msg;
}

void prepare_msg(struct ptp_msg *msg, int message)
{
	int len;
	int logInterval;
	int seqid;
	int ctrl;
	int correction;
	int port = 0;
	struct ptp_clock_identity *clock;
	struct ptp_msg_sync *sync;
	struct ptp_msg_follow_up *follow_up;
	struct ptp_msg_delay_resp *delay_resp;
	struct ptp_msg_pdelay_req *pdelay_req;
	struct ptp_msg_pdelay_resp *pdelay_resp;
	struct ptp_msg_pdelay_resp_follow_up *pdelay_follow_up;
	struct ptp_msg_announce* announce;
	struct ptp_clock_quality *quality;
	void *tlv;

	correction = ptp_correction;
	clock = &selfClockIdentity;
	ctrl = 5;
	logInterval = 0x7F;
	switch (message) {
	case SYNC_MSG:
		len = sizeof(struct ptp_msg_sync);
		ctrl = 0;
		if (!ptp_unicast)
			logInterval = 0;
		seqid_sync++;
		seqid = seqid_sync;
		sync = &msg->data.sync;
		sync->originTimestamp.sec.hi = 0;
		if ((ptp_2step || ptp_dst_port) && ptp_correction != 1) {
			sync->originTimestamp.sec.lo = 0;
			sync->originTimestamp.nsec = 0;
		} else {
			sync->originTimestamp.sec.lo = htonl(sync_sec++);
			sync->originTimestamp.nsec = htonl(1000);
		}
		clock = &masterClockIdentity;
		break;
	case FOLLOW_UP_MSG:
		len = sizeof(struct ptp_msg_follow_up);
		ctrl = 2;
		if (!ptp_unicast)
			logInterval = 0;
		seqid = seqid_sync;
		follow_up = &msg->data.follow_up;
		follow_up->preciseOriginTimestamp.sec.hi = 0;
		follow_up->preciseOriginTimestamp.sec.lo = htonl(sync_sec);
		follow_up->preciseOriginTimestamp.nsec = htonl(1000);
		if (ptp_on)
			port = get_tx_port(ptp_dst_port);
		if (port && ptp_tx_sync[port - 1].nsec) {
			follow_up->preciseOriginTimestamp.sec.lo =
				htonl(ptp_tx_sync[port - 1].sec);
			follow_up->preciseOriginTimestamp.nsec =
				htonl(ptp_tx_sync[port - 1].nsec);
		}
		clock = &masterClockIdentity;
		if (send_tlv) {
			tlv = follow_up + 1;
			tlv = tlv_msg(tlv, &len, TLV_ORGANIZATION_EXTENSION,
				1);
		}
		break;
	case DELAY_REQ_MSG:
		len = sizeof(struct ptp_msg_sync);
		ctrl = 1;
		seqid_delay_req++;
		seqid = seqid_delay_req;
		sync = &msg->data.sync;
		sync->originTimestamp.sec.hi = 0;
		sync->originTimestamp.sec.lo = 0;
		sync->originTimestamp.nsec = 0;
		break;
	case DELAY_RESP_MSG:
		len = sizeof(struct ptp_msg_delay_resp);
		ctrl = 3;
		if (!ptp_unicast)
			logInterval = 1;
		seqid = seqid_delay_req;
		delay_resp = &msg->data.delay_resp;
		delay_resp->receiveTimestamp.sec.hi = 0;
		delay_resp->receiveTimestamp.sec.lo = htonl(sync_sec);
		delay_resp->receiveTimestamp.nsec = htonl(2000);
		memcpy(&delay_resp->requestingPortIdentity.clockIdentity,
			&selfClockIdentity, sizeof(struct ptp_clock_identity));
		delay_resp->requestingPortIdentity.port = htons(1);
		clock = &masterClockIdentity;
		break;
	case PDELAY_REQ_MSG:
		len = sizeof(struct ptp_msg_pdelay_req);
		seqid_pdelay_req++;
		seqid = seqid_pdelay_req;
		pdelay_req = &msg->data.pdelay_req;
		pdelay_req->originTimestamp.sec.hi = 0;
		pdelay_req->originTimestamp.sec.lo = htonl(sync_sec);
		pdelay_req->originTimestamp.nsec = htonl(1000);
		memset(&pdelay_req->reserved, 0,
			sizeof(struct ptp_clock_identity));
		break;
	case PDELAY_RESP_MSG:
		len = sizeof(struct ptp_msg_pdelay_resp);
		seqid = seqid_pdelay_req;
		pdelay_resp = &msg->data.pdelay_resp;
		pdelay_resp->requestReceiptTimestamp.sec.hi = 0;
		if (ptp_2step) {
			pdelay_resp->requestReceiptTimestamp.sec.lo =
				htonl(sync_sec);
			pdelay_resp->requestReceiptTimestamp.nsec =
				htonl(2000);
		} else {
			pdelay_resp->requestReceiptTimestamp.sec.lo = 0;
			pdelay_resp->requestReceiptTimestamp.nsec = 0;
			ptp_correction = 12345;
		}
		memcpy(&pdelay_resp->requestingPortIdentity.clockIdentity,
			&selfClockIdentity, sizeof(struct ptp_clock_identity));
		pdelay_resp->requestingPortIdentity.port = htons(1);
		clock = &masterClockIdentity;
		break;
	case PDELAY_RESP_FOLLOW_UP_MSG:
		len = sizeof(struct ptp_msg_pdelay_resp_follow_up);
		seqid = seqid_pdelay_req;
		pdelay_follow_up = &msg->data.pdelay_resp_follow_up;
		pdelay_follow_up->responseOriginTimestamp.sec.hi = 0;
		pdelay_follow_up->responseOriginTimestamp.sec.lo =
			htonl(sync_sec);
		pdelay_follow_up->responseOriginTimestamp.nsec =
			htonl(3000);
		if (ptp_on)
			port = get_tx_port(ptp_dst_port);
		if (port && ptp_tx_pdresp[port - 1].nsec) {
			pdelay_follow_up->responseOriginTimestamp.sec.lo =
				htonl(ptp_tx_pdresp[port - 1].sec);
			pdelay_follow_up->responseOriginTimestamp.nsec =
				htonl(ptp_tx_pdresp[port - 1].nsec);
		}
		memcpy(&pdelay_follow_up->requestingPortIdentity.clockIdentity,
			&selfClockIdentity, sizeof(struct ptp_clock_identity));
		pdelay_follow_up->requestingPortIdentity.port = htons(1);
		clock = &masterClockIdentity;
		break;
	case ANNOUNCE_MSG:
		len = sizeof(struct ptp_msg_announce);
		if (!ptp_unicast)
			logInterval = 1;
		seqid_announce++;
		seqid = seqid_announce;
		announce = &msg->data.announce;
		announce->originTimestamp.sec.hi = 0;
		announce->originTimestamp.sec.lo = htonl(sync_sec++);
		announce->originTimestamp.nsec = htonl(1000);
		announce->currentUtcOffset = htons(34);
		announce->grandmasterPriority1 = 255;
		quality = &announce->grandmasterClockQuality;
		quality->clockClass = 255;
		quality->clockAccuracy = 0xFE;
		quality->offsetScaledLogVariance = htons(200);
		announce->grandmasterPriority2 = 255;
		memcpy(&announce->grandmasterIdentity, &masterClockIdentity,
			sizeof(struct ptp_clock_identity));
		announce->stepsRemoved = htons(0);
		announce->timeSource = 0xA0;
		clock = &masterClockIdentity;
		if (send_tlv) {
			tlv = announce + 1;
			tlv = tlv_msg(tlv, &len, TLV_ORGANIZATION_EXTENSION,
				0);
			tlv = tlv_msg(tlv, &len,
				TLV_ALTERNATE_TIME_OFFSET_INDICATOR, 0);
		}
		break;
	default:
		len = 0;
		seqid = 0;
		break;
	}
	prepare_hdr(&msg->hdr, message, len, seqid, ctrl, logInterval,
		clock);
	if (PDELAY_REQ_MSG == message && ptp_dst_port)
		msg->hdr.sourcePortIdentity.port = htons(ptp_src_port);
	else if (ptp_src_port)
		msg->hdr.sourcePortIdentity.port = htons(ptp_src_port);
	ptp_correction = correction;
}

void send_msg(struct ptp_msg *msg, int family, int len)
{
	SOCKET sockfd;
	SAI *pservaddr;
	socklen_t servlen;
	char *buf = (char *) msg;
	int ptp_start = 0;

	if (!len)
		len = ntohs(msg->hdr.messageLength);
	if (AF_INET6 == family) {
		buf[len] = 0x15;
		buf[len + 1] = 0x88;
		len += 2;
	}

#ifdef _SYS_SOCKET_H
	if (AF_PACKET == family) {
		sockfd = eth_fd;
		switch (msg->hdr.messageType) {
		case PDELAY_REQ_MSG:
		case PDELAY_RESP_MSG:
		case PDELAY_RESP_FOLLOW_UP_MSG:
			pservaddr = (SAI *) &eth_pdelay_addr;
			servlen = sizeof(eth_pdelay_addr);
			buf = (char *) eth_pdelay_buf;
			break;
		default:
			pservaddr = (SAI *) &eth_others_addr;
			servlen = sizeof(eth_others_addr);
			buf = (char *) eth_others_buf;
			break;
		}
		ptp_start = 14;
		if (hsr) {
			struct hsr_hdr *hdr = (struct hsr_hdr *) &buf[14];

			hdr->messageLength = len + sizeof(struct hsr_hdr);
			hdr->messageLength |= 1 << HSR_LANE_ID_SHIFT;
			hdr->messageLength |= 5 << HSR_NETWORK_ID_SHIFT;
			hdr->messageLength = htons(hdr->messageLength);
			hdr->sequenceId = htons(seqid_hsr++);
			hdr->proto = htons(PTP_PROTO);
			ptp_start += 6;
		}
		memcpy(&buf[ptp_start], msg, len);
		len += ptp_start;
		if (prp) {
			int prp_len = prp_size;

			prp_len -= sizeof(struct prp_trailer);
			if (1 == prp)
				prp_len += 2;
			if (len < prp_len) {
				memset(&buf[len], 0, prp_len - len);
				len = prp_len;
			}
		}
	} else
#endif
	switch (msg->hdr.messageType) {
	case SYNC_MSG:
	case DELAY_REQ_MSG:
		sockfd = event_fd;
		if (AF_INET6 == family) {
			pservaddr = (SAI *) &event_addr6;
			servlen = sizeof(event_addr6);
		} else {
			pservaddr = &event_addr;
			servlen = sizeof(event_addr);
		}
		break;
	case PDELAY_REQ_MSG:
	case PDELAY_RESP_MSG:
		sockfd = event_fd;
		if (AF_INET6 == family) {
			pservaddr = (SAI *) &p2p_event_addr6;
			servlen = sizeof(p2p_event_addr6);
		} else {
			pservaddr = &p2p_event_addr;
			servlen = sizeof(p2p_event_addr);
		}
		break;
	case PDELAY_RESP_FOLLOW_UP_MSG:
		sockfd = general_fd;
		if (AF_INET6 == family) {
			pservaddr = (SAI *) &p2p_general_addr6;
			servlen = sizeof(p2p_general_addr6);
		} else {
			pservaddr = &p2p_general_addr;
			servlen = sizeof(p2p_general_addr);
		}
		break;
	case MANAGEMENT_MSG:
		sockfd = general_fd;
		if (AF_INET6 == family) {
			if (ptp_unicast) {
				pservaddr = (SAI *) &general_addr6;
				servlen = sizeof(general_addr6);
			} else {
				pservaddr = (SAI *) &management_addr6;
				servlen = sizeof(management_addr6);
			}
		} else {
			sockfd = management4_fd;
			if (ptp_unicast && AF_INET == ip_family) {
				pservaddr = &general_addr;
				servlen = sizeof(general_addr);
			} else {
				pservaddr = &management_addr;
				servlen = sizeof(management_addr);
			}
		}
		break;
	default:
		sockfd = general_fd;
		if (AF_INET6 == family) {
			pservaddr = (SAI *) &general_addr6;
			servlen = sizeof(general_addr6);
		} else {
			pservaddr = &general_addr;
			servlen = sizeof(general_addr);
			if (port_acl_test) {
				pservaddr = &event_addr;
				servlen = sizeof(event_addr);
			}
		}
		break;
	}
	if (prp) {
		struct prp_trailer *tail;

		tail = (struct prp_trailer *) &buf[len];
		tail->sequenceId = htons(seqid_prp++);
		tail->messageLength = len - ptp_start +
			sizeof(struct prp_trailer);
		if (1 == prp)
			tail->messageLength -= 2;
		else
			tail->proto = htons(PRP_PROTO);
		len = tail->messageLength + ptp_start;
		tail->messageLength |= (0xA | 1) << PRP_LANE_ID_SHIFT;
		tail->messageLength = htons(tail->messageLength);
	}
	Sendto(sockfd, buf, len, 0, (SA *) pservaddr, servlen);
}  /* send_msg */

void disp_timestamp(struct ptp_timestamp *ts)
{
	printf("%04x%08x:%9u", ntohs(ts->sec.hi), ntohl(ts->sec.lo),
		ntohl(ts->nsec));
}

void disp_identity(struct ptp_clock_identity *id)
{
	printf("%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x",
		id->addr[0], id->addr[1], id->addr[2], id->addr[3],
		id->addr[4], id->addr[5], id->addr[6], id->addr[7]);
}

void disp_port_identity(struct ptp_port_identity *id)
{
	printf("%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x=%04x",
		id->clockIdentity.addr[0], id->clockIdentity.addr[1],
		id->clockIdentity.addr[2], id->clockIdentity.addr[3],
		id->clockIdentity.addr[4], id->clockIdentity.addr[5],
		id->clockIdentity.addr[6], id->clockIdentity.addr[7],
		ntohs(id->port));
}

int disp_tlv(void *msg, int left)
{
	struct ptp_tlv *tlv = msg;
	int len = ntohs(tlv->lengthField);

	if (len + 4 > left) {
		if (dbg_rcv >= 4)
			printf("  \nTLV length not correct: %d %d\n",
				len, left);
		return 0;
	}
	switch (ntohs(tlv->tlvType)) {
	case TLV_ORGANIZATION_EXTENSION:
	{
		struct ptp_organization_ext_tlv *org = msg;

		printf("\n%02x%02x%02x.%02x%02x%02x ",
			org->organizationId[0],
			org->organizationId[1],
			org->organizationId[2],
			org->organizationSubType[0],
			org->organizationSubType[1],
			org->organizationSubType[2]);
		if (0x1C == org->organizationId[0] &&
				0x12 == org->organizationId[1] &&
				0x9D == org->organizationId[2]) {
			struct IEEE_C37_238_data *data =
				(struct IEEE_C37_238_data *) org->dataField;

			printf("%04x %u %u",
				ntohs(data->grandmasterID),
				ntohl(data->grandmasterTimeInaccuracy),
				ntohl(data->networkTimeInaccuracy));

			/* The 2011 standard uses the wrong size. */
			if (0x0C == len)
				len = sizeof(struct ptp_organization_ext_tlv)
					- 1 + sizeof(struct IEEE_C37_238_data);
		} else if (0x00 == org->organizationId[0] &&
				0x80 == org->organizationId[1] &&
				0xC2 == org->organizationId[2]) {
			struct IEEE_802_1AS_data_1 *data =
				(struct IEEE_802_1AS_data_1 *) org->dataField;

#if (__BITS_PER_LONG == 64)
			printf("%d %u %d,%ld %d",
#else
			printf("%d %u %d,%lld %d",
#endif
				ntohl(data->cumulativeScaledRateOffset),
				ntohs(data->gmTimeBaseIndicator),
				data->lastGmPhaseChange.hi,
				data->lastGmPhaseChange.lo,
				ntohl(data->scaledLastGmFreqChange));
		}
		left -= len + 4;
		break;
	}
	case TLV_ALTERNATE_TIME_OFFSET_INDICATOR:
	{
		struct ptp_alternate_time_offset_tlv *alt = msg;
		u64 sec;
		int i;

		sec = ntohs(alt->timeOfNextJump.hi);
		sec <<= 32;
		sec |= ntohl(alt->timeOfNextJump.lo);
#if (__BITS_PER_LONG == 64)
		printf("\n%u:%d %d %lu ", alt->keyField,
#else
		printf("\n%u:%d %d %llu ", alt->keyField,
#endif
			ntohl(alt->currentOffset),
			ntohl(alt->jumpSeconds), sec);
		for (i = 0; i < alt->displayName.lengthField; i++)
			printf("%c", alt->displayName.textField[i]);
		left -= len + 4;
		break;
	}
	default:
		left = 0;
		break;
	}
	return left;
}  /* disp_tlv */

static int get_rx_timestamp(struct ptp_msg_hdr *hdr)
{
	u32 port;
	u32 sec;
	u32 nsec;
	int rc;
	int tx = 0;

	rc = get_msg_info(&ptpdev, hdr, &tx, &port, &sec, &nsec);
	if (!rc) {
		ptp_rx_port = port;
		ptp_rx_sec = sec;
		ptp_rx_nsec = nsec;
		switch (hdr->messageType) {
		case SYNC_MSG:
			ptp_rx_sync[port - 1].sec = sec;
			ptp_rx_sync[port - 1].nsec = nsec;
			break;
		case DELAY_REQ_MSG:
			ptp_rx_delay[port - 1].sec = sec;
			ptp_rx_delay[port - 1].nsec = nsec;
			break;
		case PDELAY_REQ_MSG:
			ptp_rx_pdelay[port - 1].sec = sec;
			ptp_rx_pdelay[port - 1].nsec = nsec;
			break;
		case PDELAY_RESP_MSG:
			ptp_rx_pdresp[port - 1].sec = sec;
			ptp_rx_pdresp[port - 1].nsec = nsec;
			break;
		default:
			ptp_rx_port = 0;
		}
	}
	return rc;
}

#if 0
static int get_tx_timestamp(struct ptp_msg_hdr *hdr)
{
	u32 port;
	u32 sec;
	u32 nsec;
	int rc;
	int tx = 1;

	rc = get_msg_info(&ptpdev, hdr, &tx, &port, &sec, &nsec);
	if (!rc) {
		ptp_tx_port = port;
		ptp_tx_sec = sec;
		ptp_tx_nsec = nsec;
		switch (hdr->messageType) {
		case SYNC_MSG:
				printf("%x=%x:%9u\n", port, sec, nsec);
			ptp_tx_sync[port - 1].sec = sec;
			ptp_tx_sync[port - 1].nsec = nsec;
			break;
		case DELAY_REQ_MSG:
			ptp_tx_delay[port - 1].sec = sec;
			ptp_tx_delay[port - 1].nsec = nsec;
			break;
		case PDELAY_REQ_MSG:
			ptp_tx_pdelay[port - 1].sec = sec;
			ptp_tx_pdelay[port - 1].nsec = nsec;
			break;
		case PDELAY_RESP_MSG:
			ptp_tx_pdresp[port - 1].sec = sec;
			ptp_tx_pdresp[port - 1].nsec = nsec;
			break;
		}
	}
	return rc;
}
#endif

void disp_msg(struct ptp_msg *req, int len)
{
	int msglen;
	u16 seqid;
	u32 nsec_hi;
	u32 nsec_lo;
	s64 nsec;
	struct ptp_clock_quality *quality;
	u8 *data;
	struct ptp_utime pdresp;

	msglen = ntohs(req->hdr.messageLength);
	if (AF_INET6 == ip_family)
		len -= 2;
	if (msglen != len) {
		if (AF_PACKET != ip_family && dbg_rcv >= 4)
			printf("  \nlen %d != %d\n", msglen, len);
		if (msglen > len)
			msglen = len;
	}
	seqid = ntohs(req->hdr.sequenceId);
	nsec_hi = ntohl(req->hdr.correctionField.scaled_nsec_hi);
	nsec_lo = ntohl(req->hdr.correctionField.scaled_nsec_lo);
	nsec = nsec_hi;
	nsec <<= 32;
	nsec |= nsec_lo;
	nsec >>= 16;
	switch (req->hdr.messageType) {
	case SYNC_MSG:
		if (dbg_rcv < 2)
			return;
		if (dbg_rcv >= 4)
			printf("\n");
		printf("sync:\t\t");
		disp_timestamp(&req->data.sync.originTimestamp);
		break;
	case FOLLOW_UP_MSG:
		if (dbg_rcv < 2)
			return;
		if (dbg_rcv >= 4)
			printf("\n");
		printf("follow_up:\t");
		disp_timestamp(&req->data.follow_up.preciseOriginTimestamp);
		data = &req->data.data[sizeof(struct ptp_msg_follow_up)];
		msglen -= sizeof(struct ptp_msg_follow_up) +
			sizeof(struct ptp_msg_hdr);
		while (msglen) {
			int newlen;

			newlen = disp_tlv(data, msglen);
			data += msglen - newlen;
			msglen = newlen;
		}
		break;
	case DELAY_REQ_MSG:
		if (dbg_rcv >= 4)
			printf("\n");
		printf("delay_req:\t\t");
		disp_timestamp(&req->data.sync.originTimestamp);
		break;
	case DELAY_RESP_MSG:
		if (dbg_rcv >= 4)
			printf("\n");
		printf("delay_resp:\t\t");
		disp_timestamp(&req->data.delay_resp.receiveTimestamp);
		printf("  ");
		disp_port_identity(&req->data.delay_resp.
			requestingPortIdentity);
		break;
	case PDELAY_REQ_MSG:
		if (dbg_rcv >= 4)
			printf("\n");
		printf("pdelay_req:\t\t");
		disp_timestamp(&req->data.pdelay_req.originTimestamp);
		printf("  ");
		disp_port_identity(&req->data.pdelay_req.reserved);
		break;
	case PDELAY_RESP_MSG:
		pdresp.sec = ntohl(req->data.pdelay_resp.
			requestReceiptTimestamp.sec.lo);
		pdresp.nsec = ntohl(req->data.pdelay_resp.
			requestReceiptTimestamp.nsec);
		pdresp.nsec += nsec;
		while (pdresp.nsec >= 1000000000) {
			pdresp.nsec -= 1000000000;
			pdresp.sec++;	
		}
		if (dbg_rcv >= 4)
			printf("\n");
		printf("pdelay_resp:\t\t");
		disp_timestamp(&req->data.pdelay_resp.requestReceiptTimestamp);
		printf("  ");
		disp_port_identity(&req->data.pdelay_resp.
			requestingPortIdentity);
		if (pdresp.sec) {
			printf("\npdelay_resp_follow_up:\t");
			printf("0000%08x:%9u", pdresp.sec, pdresp.nsec);
		}
		break;
	case PDELAY_RESP_FOLLOW_UP_MSG:
		if (dbg_rcv >= 4)
			printf("\n");
		printf("pdelay_resp_follow_up:\t");
		disp_timestamp(&req->data.pdelay_resp_follow_up.
			responseOriginTimestamp);
		printf("  ");
		disp_port_identity(&req->data.pdelay_resp_follow_up.
			requestingPortIdentity);
		break;
	case ANNOUNCE_MSG:
		if (dbg_rcv < 2)
			return;
		if (dbg_rcv >= 4)
			printf("\n");
		printf("announce:\t");
		disp_timestamp(&req->data.announce.originTimestamp);
		printf("  ");
		disp_identity(&req->data.announce.grandmasterIdentity);
		quality = &req->data.announce.grandmasterClockQuality;
		printf("\no=%d p=%x,%x q=%x,%x,%u s=%u t=%x",
			ntohs(req->data.announce.currentUtcOffset),
			req->data.announce.grandmasterPriority1,
			req->data.announce.grandmasterPriority2,
			quality->clockClass, quality->clockAccuracy,
			ntohs(quality->offsetScaledLogVariance),
			ntohs(req->data.announce.stepsRemoved),
			req->data.announce.timeSource);
		data = &req->data.data[sizeof(struct ptp_msg_announce)];
		msglen -= sizeof(struct ptp_msg_announce) +
			sizeof(struct ptp_msg_hdr);
		while (msglen) {
			int newlen;

			newlen = disp_tlv(data, msglen);
			data += msglen - newlen;
			msglen = newlen;
		}
		break;
	case MANAGEMENT_MSG:
		if (dbg_rcv < 2)
			return;
		if (dbg_rcv >= 4)
			printf("\n");
		printf("management:\t");
		break;
	case SIGNALING_MSG:
		if (dbg_rcv < 2)
			return;
		if (dbg_rcv >= 4)
			printf("\n");
		printf("signaling:\t");
		msglen -= sizeof(struct ptp_msg_signaling_base) +
			sizeof(struct ptp_msg_hdr);
		disp_tlv(&req->data.signaling.tlv, msglen);
		break;
	}
	printf("\n");
	if (ptp_version >= 2) {
		if (ptp_rx_port)
			printf("r=%x %x:%9u\n", ptp_rx_port,
				ptp_rx_sec, ptp_rx_nsec);
	} else
		printf("r=%x %04x\n",
			req->hdr.reserved2, ntohl(req->hdr.reserved3));
	printf("d=%x", req->hdr.domainNumber);
	printf("  ");
	printf("f=%04x", htons(req->hdr.flagField.data));
	printf("  ");
	printf("c=%08x%08x", nsec_hi, nsec_lo);
#if (__BITS_PER_LONG == 64)
	printf("=%8ld", nsec);
#else
	printf("=%8lld", nsec);
#endif
	printf("  ");
	printf("s=%04x", seqid);
	printf("  ");
	disp_port_identity(&req->hdr.sourcePortIdentity);
	printf("\n\n");
}  /* disp_msg */

static void disp_tx_timestamp(struct ptp_msg_hdr *hdr)
{
	u32 port;
	u32 sec;
	u32 nsec;
	int rc;
	int tx = 1;
	int timeout = 2;

	if (ptp_version < 2 || (!dbg_rcv && !ptp_on))
		return;
	do {
		rc = get_msg_info(&ptpdev, hdr, &tx, &port, &sec, &nsec);
		Pthread_mutex_lock(&disp_mutex);
		if (!rc) {
			if (dbg_rcv)
				printf("%x=%x:%9u\n", port, sec, nsec);
			timeout = 2;
			switch (hdr->messageType) {
			case SYNC_MSG:
				ptp_tx_sync[port - 1].sec = sec;
				ptp_tx_sync[port - 1].nsec = nsec;
				break;
			case DELAY_REQ_MSG:
				ptp_tx_delay[port - 1].sec = sec;
				ptp_tx_delay[port - 1].nsec = nsec;
				break;
			case PDELAY_REQ_MSG:
				ptp_tx_pdelay[port - 1].sec = sec;
				ptp_tx_pdelay[port - 1].nsec = nsec;
				break;
			case PDELAY_RESP_MSG:
				ptp_tx_pdresp[port - 1].sec = sec;
				ptp_tx_pdresp[port - 1].nsec = nsec;
				break;
			}
		} else
			print_err(rc);
		Pthread_mutex_unlock(&disp_mutex);
		if (timeout-- < 1)
			break;
	} while (tx);
}  /* disp_tx_timestamp */

void resp_msg(struct ptp_msg *req, int family)
{
	char payload[sizeof(struct ptp_msg) + 4];
	char data[sizeof(struct ptp_msg) + 4];
	struct ptp_msg* resp = (struct ptp_msg *) payload;
	int len;
	int logInterval;
	int message;
	int seqid;
	int ctrl;
	int correction;
	int port = 0;
	int dst_port = ptp_dst_port;
	u32 nsec_hi;
	u32 nsec_lo;
	u32 tx_sec = 0;
	u32 tx_nsec = 0;
	struct ptp_clock_identity *clock;
	struct ptp_msg_delay_resp *delay_resp;
	struct ptp_msg_pdelay_resp *pdelay_resp;
	struct ptp_msg_pdelay_resp_follow_up *pdelay_follow_up;

	if ((long) req & 3) {
		memmove(data, req, sizeof(struct ptp_msg));
		req = (struct ptp_msg *) data;
	}

	/* Own multicast mesage. */
	if (!memcmp(&req->hdr.sourcePortIdentity.clockIdentity,
			&selfClockIdentity,
			sizeof(struct ptp_clock_identity)))
		return;

	/* Not same domain. */
	if (req->hdr.domainNumber != ptp_domain && ptp_domain < 200)
		return;

	if (ptp_rx_port)
		dst_port = 1 << (ptp_rx_port - 1);
	correction = ptp_correction;
	clock = &selfClockIdentity;
	logInterval = 0x7F;
	switch (req->hdr.messageType) {
	case DELAY_REQ_MSG:
		message = DELAY_RESP_MSG;
		len = sizeof(struct ptp_msg_delay_resp);
		ctrl = 3;
		logInterval = 0x7F;
		seqid = ntohs(req->hdr.sequenceId);
		nsec_hi = ntohl(req->hdr.correctionField.scaled_nsec_hi);
		nsec_lo = ntohl(req->hdr.correctionField.scaled_nsec_lo);
		ptp_correction = (nsec_hi << 16) | (nsec_lo >> 16);
		delay_resp = &resp->data.delay_resp;
		delay_resp->receiveTimestamp.sec.hi = 0;
		delay_resp->receiveTimestamp.sec.lo = htonl(sync_sec);
		delay_resp->receiveTimestamp.nsec = htonl(2000);
		if (ptp_on)
			port = ptp_rx_port;
		if (port) {
			delay_resp->receiveTimestamp.sec.lo =
				htonl(ptp_rx_delay[port - 1].sec);
			delay_resp->receiveTimestamp.nsec =
				htonl(ptp_rx_delay[port - 1].nsec);
		}
		memcpy(&delay_resp->requestingPortIdentity,
			&req->hdr.sourcePortIdentity,
			sizeof(struct ptp_port_identity));
		break;
	case PDELAY_REQ_MSG:
		message = PDELAY_RESP_MSG;
		len = sizeof(struct ptp_msg_pdelay_resp);
		ctrl = 5;
		logInterval = 0x7F;
		seqid = ntohs(req->hdr.sequenceId);
		pdelay_resp = &resp->data.pdelay_resp;
		pdelay_resp->requestReceiptTimestamp.sec.hi = 0;
		if (ptp_2step) {
			pdelay_resp->requestReceiptTimestamp.sec.lo =
				htonl(sync_sec);
			pdelay_resp->requestReceiptTimestamp.nsec =
				htonl(2000);
			if (ptp_on)
				port = ptp_rx_port;
			if (port) {
				tx_sec = ptp_rx_pdelay[port - 1].sec;
				tx_nsec = ptp_rx_pdelay[port - 1].nsec;
				pdelay_resp->requestReceiptTimestamp.sec.lo =
					htonl(ptp_rx_pdelay[port - 1].sec);
				pdelay_resp->requestReceiptTimestamp.nsec =
					htonl(ptp_rx_pdelay[port - 1].nsec);
			}
		} else {
			nsec_hi = ntohl(req->hdr.correctionField.
				scaled_nsec_hi);
			nsec_lo = ntohl(req->hdr.correctionField.
				scaled_nsec_lo);
			ptp_correction = (nsec_hi << 16) | (nsec_lo >> 16);
			if (ptp_on)
				port = ptp_rx_port;
			if (port) {
				tx_sec = ptp_rx_pdelay[port - 1].sec;
				tx_nsec = ptp_rx_pdelay[port - 1].nsec;
			} else {
				ptp_correction += 12345;
			}
			pdelay_resp->requestReceiptTimestamp.sec.lo = 0;
			pdelay_resp->requestReceiptTimestamp.nsec = 0;
		}
		memcpy(&pdelay_resp->requestingPortIdentity,
			&req->hdr.sourcePortIdentity,
			sizeof(struct ptp_port_identity));
		if (ptp_2step) {
			int save_dbg = dbg_rcv;

			prepare_hdr(&resp->hdr, message, len, seqid, ctrl,
				logInterval, clock);
			if (ptp_version >= 2)
				set_msg_info(&ptpdev, &resp->hdr, dst_port,
					tx_sec, tx_nsec);
			send_msg(resp, family, 0);
			tx_sec = tx_nsec = 0;
			dbg_rcv = 0;
			disp_tx_timestamp(&resp->hdr);
			dbg_rcv = save_dbg;
		} else
			break;

		message = PDELAY_RESP_FOLLOW_UP_MSG;
		len = sizeof(struct ptp_msg_pdelay_resp_follow_up);
		ctrl = 5;
		logInterval = 0x7F;
		seqid = ntohs(req->hdr.sequenceId);
		nsec_hi = ntohl(req->hdr.correctionField.scaled_nsec_hi);
		nsec_lo = ntohl(req->hdr.correctionField.scaled_nsec_lo);
		ptp_correction = (nsec_hi << 16) | (nsec_lo >> 16);
		pdelay_follow_up = &resp->data.pdelay_resp_follow_up;
		pdelay_follow_up->responseOriginTimestamp.sec.hi = 0;
		pdelay_follow_up->responseOriginTimestamp.sec.lo =
			htonl(sync_sec);
		pdelay_follow_up->responseOriginTimestamp.nsec =
			htonl(3000);
		if (ptp_on)
			port = ptp_rx_port;
		if (port && ptp_tx_pdresp[port - 1].nsec) {
			pdelay_follow_up->responseOriginTimestamp.sec.lo =
				htonl(ptp_tx_pdresp[port - 1].sec);
			pdelay_follow_up->responseOriginTimestamp.nsec =
				htonl(ptp_tx_pdresp[port - 1].nsec);
		}
		memcpy(&pdelay_follow_up->requestingPortIdentity,
			&req->hdr.sourcePortIdentity,
			sizeof(struct ptp_port_identity));
		break;
	default:
		return;
	}
	prepare_hdr(&resp->hdr, message, len, seqid, ctrl, logInterval,
		clock);
	ptp_correction = correction;
	if (ptp_version >= 2)
		set_msg_info(&ptpdev, &resp->hdr, dst_port, tx_sec, tx_nsec);
	send_msg(resp, family, 0);
}  /* resp_msg */

int get_cmd(FILE *fp)
{
	int count;
	int hcount;
	unsigned int num[8];
	unsigned int hex[8];
	int len = 0;
	int cont = 1;
	char cmd[80];
	char line[80];
	char payload[(sizeof(struct ptp_msg) + 2000) & ~3];
	struct ptp_msg* msg = (struct ptp_msg *) payload;

	do {
		printf("> ");
		if (fgets(line, 80, fp) == NULL)
			break;
		cmd[0] = '\0';
		count = sscanf(line, "%s %d %d %d %d", cmd,
			(unsigned int *) &num[0],
			(unsigned int *) &num[1],
			(unsigned int *) &num[2],
			(unsigned int *) &num[3]);
		hcount = sscanf(line, "%s %x %x %x %x", cmd,
			(unsigned int *) &hex[0],
			(unsigned int *) &hex[1],
			(unsigned int *) &hex[2],
			(unsigned int *) &hex[3]);
		if (!strcmp(cmd, "sci") || !strcmp(cmd, "mci")) {
			struct ptp_clock_identity id;
			struct ptp_clock_identity* clock;

			count = sscanf(line, "%s %x:%x:%x:%x:%x:%x:%x:%x", cmd,
				&num[0], &num[1], &num[2], &num[3],
				&num[4], &num[5], &num[6], &num[7]);
			if (!strcmp(cmd, "sci"))
				clock = &selfClockIdentity;
			else
				clock = &masterClockIdentity;
			if (count >= 9) {
				for (count = 0; count < 8; count++)
					id.addr[count] = (u8) num[count];
				memcpy(clock, &id,
					sizeof(struct ptp_clock_identity));
			}
			printf("%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\n",
				clock->addr[0],
				clock->addr[1],
				clock->addr[2],
				clock->addr[3],
				clock->addr[4],
				clock->addr[5],
				clock->addr[6],
				clock->addr[7]);
		} else if (!strcmp(cmd, "mg")) {
			msg = management_msg(M_NULL_MANAGEMENT, M_NO_SUCH_ID,
				1200);
			send_msg(msg, ip_family, len);

			/* Cannot break message into fragments. */
			if (AF_PACKET == ip_family)
				continue;
			msg = management_msg(M_NULL_MANAGEMENT, M_NO_SUCH_ID,
				1406);
			send_msg(msg, ip_family, len);
			msg = management_msg(M_NULL_MANAGEMENT, M_NO_SUCH_ID,
				1408);
			send_msg(msg, ip_family, len);
			msg = management_msg(M_NULL_MANAGEMENT, M_NO_SUCH_ID,
				1410);
			send_msg(msg, ip_family, len);
			msg = management_msg(M_NULL_MANAGEMENT, M_NO_SUCH_ID,
				1412);
			send_msg(msg, ip_family, len);
			msg = management_msg(M_NULL_MANAGEMENT, M_NO_SUCH_ID,
				1500);
			send_msg(msg, ip_family, len);
			msg = management_msg(M_TIME, 0, 0);
			send_msg(msg, AF_INET, len);
		} else if (!strcmp(cmd, "sg")) {
			msg = signaling_msg(TLV_REQUEST_UNICAST_TRANSMISSION,
				ANNOUNCE_MSG, 0, 60);
			send_msg(msg, ip_family, len);
			msg = signaling_msg(TLV_GRANT_UNICAST_TRANSMISSION,
				ANNOUNCE_MSG, 0, 60);
			send_msg(msg, ip_family, len);
			msg = signaling_msg(TLV_CANCEL_UNICAST_TRANSMISSION,
				ANNOUNCE_MSG, 0, 0);
			send_msg(msg, ip_family, len);
			msg = signaling_msg(
				TLV_ACKNOWLEDGE_CANCEL_UNICAST_TRANSMISSION,
				ANNOUNCE_MSG, 0, 0);
			send_msg(msg, ip_family, len);
		} else if (!strcmp(cmd, "hw")) {
			return 2;
		} else if (!strcmp(cmd, "acl")) {
			return 3;
		} else
		switch (line[0]) {
		case 'l':
			if (count >= 2)
				len = num[0];
			else
				printf("%d\n", len);
			break;
		case 'm':
			if (hcount >= 2)
				seqid_sync += hex[0];
			prepare_msg(msg, SYNC_MSG);
			if (ptp_version >= 2)
				set_msg_info(&ptpdev, &msg->hdr, ptp_dst_port,
					0, 0);
			send_msg(msg, ip_family, len);
			if (msg->hdr.flagField.flag.twoStepFlag)
				disp_tx_timestamp(&msg->hdr);
			break;
		case 'n':
			if (hcount >= 2)
				seqid_sync += hex[0];
			prepare_msg(msg, FOLLOW_UP_MSG);
			send_msg(msg, ip_family, len);
			break;
		case 'a':
			if (hcount >= 2)
				seqid_delay_req += hex[0];
			prepare_msg(msg, DELAY_REQ_MSG);
			if (ptp_version >= 2)
				set_msg_info(&ptpdev, &msg->hdr, ptp_dst_port,
					0, 0);
			send_msg(msg, ip_family, len);
			disp_tx_timestamp(&msg->hdr);
			break;
		case 'b':
			if (hcount >= 2)
				seqid_delay_req += hex[0];
			prepare_msg(msg, DELAY_RESP_MSG);
			send_msg(msg, ip_family, len);
			break;
		case 'x':
			if (hcount >= 2)
				seqid_pdelay_req += hex[0];
			prepare_msg(msg, PDELAY_REQ_MSG);
			if (ptp_version >= 2)
				set_msg_info(&ptpdev, &msg->hdr, ptp_dst_port,
					0, 0);
			send_msg(msg, ip_family, len);
			disp_tx_timestamp(&msg->hdr);
			break;
		case 'y':
			if (hcount >= 2)
				seqid_pdelay_req += hex[0];
			prepare_msg(msg, PDELAY_RESP_MSG);
			if (ptp_version >= 2)
				set_msg_info(&ptpdev, &msg->hdr, ptp_dst_port,
					0, 0);
			send_msg(msg, ip_family, len);
			if (msg->hdr.flagField.flag.twoStepFlag)
				disp_tx_timestamp(&msg->hdr);
			break;
		case 'z':
			if (hcount >= 2)
				seqid_pdelay_req += hex[0];
			prepare_msg(msg, PDELAY_RESP_FOLLOW_UP_MSG);
			send_msg(msg, ip_family, len);
			break;
		case 'e':
			if (hcount >= 2)
				seqid_announce += hex[0];
			prepare_msg(msg, ANNOUNCE_MSG);
			send_msg(msg, ip_family, len);
			break;
		case 'c':
			if (count >= 2)
				ptp_correction = num[0];
			else
				printf("%d\n", ptp_correction);
			break;
		case 'd':
			if (count >= 2)
				ptp_domain = num[0];
			else
				printf("%d\n", ptp_domain);
			break;
		case 'o':
			if (count >= 2)
				ptp_on = num[0];
			else
				printf("%d\n", ptp_on);
			break;
		case 'p':
			if (hcount >= 2) {
				ptp_dst_port = hex[0];
				if (ptp_version >= 2) {
					int rc;

					msg->hdr.messageType = 7;
					rc = set_msg_info(&ptpdev, &msg->hdr,
						ptp_dst_port, 0, 0);
					if (rc)
						print_err(rc);
				}
			} else
				printf("%x\n", ptp_dst_port);
			break;
		case 'r':
			if (count >= 2)
				prp_size = num[0];
			else
				printf("%d\n", prp_size);
			break;
		case 's':
			if (count >= 2)
				ptp_src_port = num[0];
			else
				printf("%d\n", ptp_src_port);
			break;
		case 't':
			if (count >= 2)
				ptp_2step = num[0];
			else
				printf("2-step=%d\n", ptp_2step);
			break;
		case 'u':
			if (count >= 2)
				ptp_count = num[0];
			else
				printf("%d\n", ptp_count);
			break;
		case 'v':
			if (count >= 2)
				ptp_alternate = num[0];
			else
				printf("%d\n", ptp_alternate);
			break;
		case 'w':
			if (count >= 2)
				send_tlv = num[0];
			else
				printf("%d\n", send_tlv);
			break;
		case 'h':
			printf("\tm [h#]\tSync\n");
			printf("\tn [h#]\tFollow_Up\n");
			printf("\ta [h#]\tDelay_Req\n");
			printf("\tb [h#]\tDelay_Resp\n");
			printf("\tx [h#]\tPdelay_Req\n");
			printf("\ty [h#]\tPdelay_Resp\n");
			printf("\tz [h#]\tPdelay_Resp_Follow_Up\n");
			printf("\te [h#]\tAnnounce\n");
			printf("\tmg\tManagement test\n");
			printf("\tsg\tSignaling test\n");
			printf("\tc\tcorrection\n");
			printf("\td\tdomain\n");
			printf("\tl\tset arbitrary length\n");
			printf("\tr\tset PRP frame length\n");
			printf("\tp\tdestination port\n");
			printf("\ts\tsource port\n");
			printf("\tt\t0 = 1-step; 1 = 2-step\n");
			printf("\tu\treply count\n");
			printf("\tv\talternate master\n");
			printf("\tw\tsend TLV\n");
			printf("\tmci\tmaster clockIdentity\n");
			printf("\tsci\tslave clockIdentity\n");
			printf("\th\thelp\n");
			printf("\tq\tquit\n");
			break;
		case 'q':
			cont = 0;
			break;
		}
	} while (cont);
	return 0;
}  /* get_cmd */

int get_hw_cmd(FILE *fp)
{
	int count;
	int hcount;
	unsigned int num[10];
	unsigned int hex[10];
	int rc;
	int cont = 1;
	char cmd[80];
	char line[80];
	int rx_latency;
	int tx_latency;
	int asym_delay;
	u8 ptp_domain = 0;
	u32 ptp_access_delay = 0;
	int ptp_alternate = 0;
	int ptp_as = 0;
	int ptp_check = 0;
	int ptp_csum = 0;
	int ptp_master = 0;
	int ptp_2step = 0;
	int ptp_p2p = 0;
	int ptp_unicast = 0;
	int ptp_drop_sync = 0;
	int ptp_delay_assoc = 0;
	int ptp_pdelay_assoc = 0;
	int ptp_sync_assoc = 0;
	int ptp_priority = 0;
	int ptp_started = 0;
	void *fd = &ptpdev;

	get_global_cfg(fd, &ptp_master, &ptp_2step, &ptp_p2p,
		&ptp_as, &ptp_unicast, &ptp_alternate, &ptp_csum, &ptp_check,
		&ptp_delay_assoc, &ptp_pdelay_assoc, &ptp_sync_assoc,
		&ptp_drop_sync, &ptp_priority, &ptp_domain, &ptp_access_delay,
		&ptp_started);
	do {
		printf("> ");
		if (fgets(line, 80, fp) == NULL)
			break;
		cmd[0] = '\0';
		count = sscanf(line, "%s %u %u %u %u %u %u %u %u %u %u", cmd,
			(unsigned int *) &num[0],
			(unsigned int *) &num[1],
			(unsigned int *) &num[2],
			(unsigned int *) &num[3],
			(unsigned int *) &num[4],
			(unsigned int *) &num[5],
			(unsigned int *) &num[6],
			(unsigned int *) &num[7],
			(unsigned int *) &num[8],
			(unsigned int *) &num[9]);
		hcount = sscanf(line, "%s %x %x %x %x %x %x %x %x %x %x", cmd,
			(unsigned int *) &hex[0],
			(unsigned int *) &hex[1],
			(unsigned int *) &hex[2],
			(unsigned int *) &hex[3],
			(unsigned int *) &hex[4],
			(unsigned int *) &hex[5],
			(unsigned int *) &hex[6],
			(unsigned int *) &hex[7],
			(unsigned int *) &hex[8],
			(unsigned int *) &hex[9]);
		if (count > 1 && !num[0] && hex[0])
			for (rc = 0; rc < count - 1; rc++)
				num[rc] = hex[rc];
		if (!strcmp(cmd, "sci") || !strcmp(cmd, "mci")) {
			struct ptp_clock_identity id;
			struct ptp_clock_identity* clock;

			count = sscanf(line, "%s %x:%x:%x:%x:%x:%x:%x:%x", cmd,
				&num[0], &num[1], &num[2], &num[3],
				&num[4], &num[5], &num[6], &num[7]);
			if (!strcmp(cmd, "sci"))
				clock = &selfClockIdentity;
			else
				clock = &masterClockIdentity;
			if (count >= 9) {
				for (count = 0; count < 8; count++)
					id.addr[count] = (u8) num[count];
				memcpy(clock, &id,
					sizeof(struct ptp_clock_identity));
				rc = 0;
				if (!strcmp(cmd, "sci"))
					rc = set_clock_ident(fd, 0, &id);
				else if (ptp_version >= 2)
					rc = set_clock_ident(fd, 1, &id);
				print_err(rc);
			}
			printf("%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\n",
				clock->addr[0],
				clock->addr[1],
				clock->addr[2],
				clock->addr[3],
				clock->addr[4],
				clock->addr[5],
				clock->addr[6],
				clock->addr[7]);
		} else if (!strcmp(cmd, "huc")) {
			if (count >= 2) {
				ptp_csum = num[0];
				set_hw_csum(fd, ptp_csum);
			} else
				printf("udp csum = %d\n", ptp_csum);
		} else if (!strcmp(cmd, "has")) {
			if (count >= 2) {
				ptp_as = num[0];
				set_hw_as(fd, ptp_as);
			} else
				printf("802.1as = %d\n", ptp_as);
		} else if (!strcmp(cmd, "hds")) {
			if (count >= 2) {
				ptp_drop_sync = num[0];
				set_hw_drop_sync(fd, ptp_drop_sync);
			} else
				printf("drop sync = %d\n", ptp_drop_sync);
		} else if (!strcmp(cmd, "hda")) {
			if (count >= 2) {
				ptp_delay_assoc = num[0];
				set_hw_delay_assoc(fd, ptp_delay_assoc);
			} else
				printf("delay assoc = %d\n", ptp_delay_assoc);
		} else if (!strcmp(cmd, "hpda")) {
			if (count >= 2) {
				ptp_pdelay_assoc = num[0];
				set_hw_pdelay_assoc(fd, ptp_pdelay_assoc);
			} else
				printf("pdelay assoc = %d\n", ptp_pdelay_assoc);
		} else if (!strcmp(cmd, "hsa")) {
			if (count >= 2) {
				ptp_sync_assoc = num[0];
				set_hw_sync_assoc(fd, ptp_sync_assoc);
			} else
				printf("sync assoc = %d\n", ptp_sync_assoc);
		} else if (!strcmp(cmd, "hp")) {
			if (count >= 2) {
				ptp_priority = num[0];
				set_hw_priority(fd, ptp_priority);
			} else
				printf("priority = %d\n", ptp_priority);
		} else if (!strcmp(cmd, "sw")) {
			return 1;
		} else if (!strcmp(cmd, "acl")) {
			return 3;
		} else if ('c' == line[1]) {
			switch (line[0]) {
			case 'g':
				rc = get_clock(fd, &num[0], &num[1]);
				if (!rc)
					printf("%x:%9u\n", num[0], num[1]);
				else
					print_err(rc);
				break;
			case 's':
				if (count < 2)
					break;
				if (count < 3)
					num[1] = 0;
				rc = set_clock(fd, num[0], num[1]);
				print_err(rc);
				break;
			case 'i':
				if (count < 2)
					break;
				if (count < 3)
					num[1] = 0;
				if (900000000 <= num[0] && count >= 4)
					rc = set_clock(fd,
						0xffffffff, 100000000);
				rc = get_clock(fd, &num[2], &num[3]);
				rc = adj_freq(fd, num[1], num[0], 0, 0);
				rc = get_clock(fd, &num[4], &num[5]);
				printf("%x:%9u\n", num[2], num[3]);
				printf("%x:%9u\n", num[4], num[5]);
				break;
			case 'd':
				if (count < 2)
					break;
				if (count < 3)
					num[1] = 0;
				if (900000000 <= num[0] && count >= 4)
					rc = set_clock(fd, 1, 0);
				rc = get_clock(fd, &num[2], &num[3]);
				rc = adj_freq(fd, -num[1], -num[0], 0, 0);
				rc = get_clock(fd, &num[4], &num[5]);
				printf("%x:%9u\n", num[2], num[3]);
				printf("%x:%9u\n", num[4], num[5]);
				break;
			case 'a':
				if (count < 2) {
					rc = get_freq(fd, &ptp_drift);
					if (!rc)
						printf("drift = %d\n",
							ptp_drift);
					else
						print_err(rc);
					break;
				}
				num[1] = 1000000000;
				rc = adj_freq(fd, 0, 0, num[0], num[1]);
				print_err(rc);
				break;
			}
		} else if ('d' == line[1]) {
			switch (line[0]) {
			case 'g':
				if (count < 2)
					break;
				rc = get_delays(fd, num[0], &rx_latency,
					&tx_latency, &asym_delay);
				if (!rc)
					printf("%u:%u %u %d\n", num[0],
						rx_latency, tx_latency,
						asym_delay);
				else
					print_err(rc);
				break;
			case 's':
				if (count < 5)
					break;
				rc = set_delays(fd, num[0], num[1], num[2],
					num[3]);
				print_err(rc);
				break;
			case 'p':
				if (count < 2)
					break;
				if (count < 3) {
					rc = get_peer_delay(fd, num[0],
						&asym_delay);
					if (!rc)
						printf("%u:%u\n", num[0],
							asym_delay);
					else
						print_err(rc);
				} else {
					rc = set_peer_delay(fd, num[0],
						num[1]);
					print_err(rc);
				}
				break;
			}
		} else
		switch (line[0]) {
		case 'a':
			if (count >= 2) {
				ptp_alternate = num[0];
				set_hw_alternate(fd, ptp_alternate);
			} else
				printf("alternate = %d\n", ptp_alternate);
			break;
		case 'c':
			if (count >= 2) {
				ptp_check = num[0];
				set_hw_domain_check(fd, ptp_check);
			} else
				printf("domain check = %d\n", ptp_check);
			break;
		case 'd':
			if (count >= 2) {
				ptp_domain = (u8) num[0];
				set_hw_domain(fd, ptp_domain);
			} else
				printf("domain = %u\n", ptp_domain);
			break;
		case 'e':
			if (count >= 2) {
				ptp_p2p = num[0];
				set_hw_p2p(fd, ptp_p2p);
			} else
				printf("p2p = %d\n", ptp_p2p);
			break;
		case 'm':
			if (count >= 2) {
				ptp_master = num[0];
				set_hw_master(fd, ptp_master);
			} else
				printf("master = %d\n", ptp_master);
			break;
		case 'p':
			if (count >= 2) {
				ptp_2step = num[0];
				set_hw_2_step(fd, ptp_2step);
			} else
				printf("2-step = %d\n", ptp_2step);
			break;
		case 'u':
			if (count >= 2) {
				ptp_unicast = num[0];
				set_hw_unicast(fd, ptp_unicast);
			} else
				printf("unicast = %d\n", ptp_unicast);
			break;
		case 'r':
			if (hcount < 2)
				break;
			if (hcount < 3)
				hex[1] = 2;
			hex[2] = hex[1];
			rc = get_reg(fd, hex[2], hex[0], &hex[1]);
			if (!rc) {
				if (4 == hex[2])
					printf("%08x\n", hex[1]);
				else if (2 == hex[2])
					printf("%04x\n", hex[1]);
				else
					printf("%02x\n", hex[1]);
			} else
				print_err(rc);
			break;
		case 'w':
			if (hcount < 3)
				break;
			if (hcount < 4)
				hex[2] = 2;
			rc = set_reg(fd, hex[2], hex[0], hex[1]);
			break;
		case 'h':
			printf("\tgc\n");
			printf("\tsc sec [nsec]\n");
			printf("\tic nsec [sec]\n");
			printf("\tdc nsec [sec]\n");
			printf("\tac drift [interval]\n");
			printf("\n");
			printf("\tgd port\n");
			printf("\tsd port rx tx asym\n");
			printf("\tpd port [delay]\n");
			printf("\n");
			printf("\tsci [clockIdentity]\n");
			printf("\tmci [clockIdentity]\n");
			printf("\n");
			printf("\td [domain]\n");
			printf("\ta [0,1]\t\talternate\n");
			printf("\tc [0,1]\t\tdomain check\n");
			printf("\te [0,1]\t\tp2p\n");
			printf("\tm [0,1]\t\tmaster\n");
			printf("\tp [0,1]\t\t2-step\n");
			printf("\tu [0,1]\t\tunicast\n");
			printf("\thas [0,1]\t802.1as\n");
			printf("\thds [0,1]\tdrop Sync/Delay_Req\n");
			printf("\thuc [0,1]\tUDP checksum\n");
			printf("\thda [0,1]\tdelay assoc\n");
			printf("\thpda [0,1]\tpdelay assoc\n");
			printf("\thsa [0,1]\tsync assoc\n");
			printf("\thp [0,1]\tmessage priority\n");
			printf("\n");
			printf("\tr reg [width]\n");
			printf("\tw reg val [width]\n");
			break;
		case 'q':
			cont = 0;
			break;
		}
	} while (cont);
	return 0;
}  /* get_hw_cmd */

static u8 acl_dst_addr[6];
static u8 acl_src_addr[6];
static u8 acl_dst_ip[4];
static u8 acl_src_ip[4];
static u8 acl_ip_mask[4];
static u8 acl_protocol;
static u8 acl_port;
static u8 acl_index;
static u16 acl_eth_type;
static u16 acl_max_port;
static u16 acl_min_port;
static int acl_test;
static int acl_count;

struct acl_test_case {
	u8 mode;
	u8 enable;
	u8 src;
	u8 equal;
	void *param1;
	void *param2;
};

static struct acl_test_case acl_test_cases_a[] = {
	{ 1, 1, 0, 2, &acl_eth_type, NULL },
	{ 1, 1, 0, 1, &acl_eth_type, NULL },
	{ 1, 2, 2, 2, NULL, acl_src_addr },
	{ 1, 2, 2, 1, NULL, acl_src_addr },
	{ 1, 2, 1, 2, NULL, acl_dst_addr },
	{ 1, 2, 1, 1, NULL, acl_dst_addr },
	{ 1, 3, 2, 2, &acl_eth_type, acl_src_addr },
	{ 1, 3, 2, 1, &acl_eth_type, acl_src_addr },
	{ 1, 3, 1, 2, &acl_eth_type, acl_dst_addr },
	{ 1, 3, 1, 1, &acl_eth_type, acl_dst_addr },

	{ 2, 1, 2, 2, acl_src_ip, acl_ip_mask },
	{ 2, 1, 2, 1, acl_src_ip, acl_ip_mask },
	{ 2, 1, 1, 2, acl_dst_ip, acl_ip_mask },
	{ 2, 1, 1, 1, acl_dst_ip, acl_ip_mask },

	{ 2, 2, 0, 0, NULL, NULL },

	{ 3, 0, 0, 2, &acl_protocol, NULL },
	{ 3, 0, 0, 1, &acl_protocol, NULL },
	{ 3, 2, 2, 1, &acl_min_port, &acl_max_port },
	{ 3, 2, 2, 2, &acl_min_port, &acl_max_port },
	{ 3, 2, 2, 3, &acl_min_port, &acl_max_port },
	{ 3, 2, 1, 1, &acl_min_port, &acl_max_port },
	{ 3, 2, 1, 2, &acl_min_port, &acl_max_port },
	{ 3, 2, 1, 3, &acl_min_port, &acl_max_port },

	{ 0, 0, 0, 0, NULL, NULL }
};

static struct acl_test_case acl_test_cases_b[] = {
	{ 1, 1, 0, 2, &acl_eth_type, NULL },
	{ 1, 2, 2, 2, NULL, acl_src_addr },
	{ 1, 2, 1, 2, NULL, acl_dst_addr },
	{ 1, 3, 2, 2, &acl_eth_type, acl_src_addr },
	{ 1, 3, 1, 2, &acl_eth_type, acl_dst_addr },

	{ 2, 1, 2, 2, acl_src_ip, acl_ip_mask },
	{ 2, 1, 1, 2, acl_dst_ip, acl_ip_mask },

	{ 3, 0, 0, 2, &acl_protocol, NULL },
	{ 3, 2, 2, 1, &acl_min_port, &acl_max_port },
	{ 3, 2, 2, 2, &acl_min_port, &acl_max_port },
	{ 3, 2, 1, 1, &acl_min_port, &acl_max_port },
	{ 3, 2, 1, 2, &acl_min_port, &acl_max_port },

	{ 0, 0, 0, 0, NULL, NULL }
};

static struct acl_test_case acl_test_cases_c[] = {
	{ 1, 1, 0, 2, &acl_eth_type, NULL },
	{ 1, 2, 2, 2, NULL, acl_src_addr },
	{ 1, 2, 1, 2, NULL, acl_dst_addr },
	{ 1, 3, 2, 2, &acl_eth_type, acl_src_addr },
	{ 1, 3, 1, 2, &acl_eth_type, acl_dst_addr },

#if 0
	{ 3, 0, 0, 2, &acl_protocol, NULL },
	{ 3, 2, 2, 1, &acl_min_port, &acl_max_port },
	{ 3, 2, 2, 2, &acl_min_port, &acl_max_port },
	{ 3, 2, 1, 1, &acl_min_port, &acl_max_port },
	{ 3, 2, 1, 2, &acl_min_port, &acl_max_port },
#endif

	{ 0, 0, 0, 0, NULL, NULL }
};

static struct acl_test_case acl_test_cases_d[] = {
	{ 1, 1, 0, 2, &acl_eth_type, NULL },
	{ 1, 2, 2, 2, NULL, acl_src_addr },
	{ 1, 2, 1, 2, NULL, acl_dst_addr },
	{ 1, 3, 2, 2, &acl_eth_type, acl_src_addr },
	{ 1, 3, 1, 2, &acl_eth_type, acl_dst_addr },

	{ 0, 0, 0, 0, NULL, NULL }
};

static struct acl_test_case *acl_test_cases;

static char acl_sysfs[40];

enum acl_file_index {
	ACL_INDEX,
	ACL_MODE,
	ACL_ENABLE,
	ACL_SRC,
	ACL_EQUAL,
	ACL_MAP_MODE,
	ACL_PORTS,
	ACL_RULESET,
	ACL_ADDR,
	ACL_TYPE,
	ACL_IP_ADDR,
	ACL_IP_MASK,
	ACL_PROTOCOL,
	ACL_MAX_PORT,
	ACL_MIN_PORT,
	ACL_PORT_MODE,

	ACL_LAST
};

static char *acl_files[ACL_LAST] = {
	"index",
	"mode",
	"enable",
	"src",
	"equal",
	"map_mode",
	"ports",
	"ruleset",
	"addr",
	"type",
	"ip_addr",
	"ip_mask",
	"protocol",
	"max_port",
	"min_port",
	"port_mode",
};

static int set_acl_param(char *val, char *file)
{
	char cmd[100];
	int rc;

	sprintf(cmd, "echo %s > %s/sw%u/%u_acl_%s",
		val, acl_sysfs, acl_port, acl_port, file);
	rc = system(cmd);
	if (rc)
		printf("%d: %s\n", rc, cmd);
	return rc;
}

static int prep_acl(void)
{
	char val[20];
	int rc;

	sprintf(val, "%x", 1 << acl_index);
	rc = set_acl_param(val, acl_files[ACL_RULESET]);
	if (rc)
		return rc;
	sprintf(val, "%u", 3);
	rc = set_acl_param(val, acl_files[ACL_MAP_MODE]);
	return rc;
}

static int prog_acl(u8 mode, u8 enable, u8 src, u8 equal, void *param1,
	void *param2)
{
	char val[20];
	u16 *eth_type;
	u8 *addr;
	u8 *protocol;
	u16 *port;
	int rc;

	switch (mode) {
	case 1:
		if (src) {
			sprintf(val, "%u", src - 1);
			rc = set_acl_param(val, acl_files[ACL_SRC]);
			if (rc)
				goto prog_acl_done;
		}
		if (equal) {
			sprintf(val, "%u", equal - 1);
			rc = set_acl_param(val, acl_files[ACL_EQUAL]);
			if (rc)
				goto prog_acl_done;
		}
		eth_type = param1;
		addr = param2;
		switch (enable) {
		case 1:
			if (!eth_type)
				break;
			sprintf(val, "%x", *eth_type);
			rc = set_acl_param(val, acl_files[ACL_TYPE]);
			if (rc)
				goto prog_acl_done;
			break;
		case 2:
			if (!addr)
				break;
			sprintf(val, "%x:%x:%x:%x:%x:%x",
				addr[0], addr[1], addr[2],
				addr[3], addr[4], addr[5]);
			rc = set_acl_param(val, acl_files[ACL_ADDR]);
			if (rc)
				goto prog_acl_done;
			break;
		case 3:
			if (!eth_type)
				break;
			sprintf(val, "%x", *eth_type);
			rc = set_acl_param(val, acl_files[ACL_TYPE]);
			if (rc)
				goto prog_acl_done;
			if (!addr)
				break;
			sprintf(val, "%x:%x:%x:%x:%x:%x",
				addr[0], addr[1], addr[2],
				addr[3], addr[4], addr[5]);
			rc = set_acl_param(val, acl_files[ACL_ADDR]);
			if (rc)
				goto prog_acl_done;
			break;
		}
		break;
	case 2:
		if (src) {
			sprintf(val, "%u", src - 1);
			rc = set_acl_param(val, acl_files[ACL_SRC]);
			if (rc)
				goto prog_acl_done;
		}
		if (equal) {
			sprintf(val, "%u", equal - 1);
			rc = set_acl_param(val, acl_files[ACL_EQUAL]);
			if (rc)
				goto prog_acl_done;
		}
		switch (enable) {
		case 1:
			addr = param1;
			if (!addr)
				break;
			sprintf(val, "%u.%u.%u.%u",
				addr[0], addr[1], addr[2], addr[3]);
			rc = set_acl_param(val, acl_files[ACL_IP_ADDR]);
			if (rc)
				goto prog_acl_done;
			addr = param2;
			if (!addr)
				break;
			sprintf(val, "%u.%u.%u.%u",
				addr[0], addr[1], addr[2], addr[3]);
			rc = set_acl_param(val, acl_files[ACL_IP_MASK]);
			if (rc)
				goto prog_acl_done;
			break;
		case 2:
			break;
		}
		break;
	case 3:
		switch (enable) {
		case 0:
			if (equal) {
				sprintf(val, "%u", equal - 1);
				rc = set_acl_param(val, acl_files[ACL_EQUAL]);
			}
			protocol = param1;
			sprintf(val, "%u", *protocol);
			rc = set_acl_param(val, acl_files[ACL_PROTOCOL]);
			if (rc)
				goto prog_acl_done;
			break;
		case 1:
			break;
		case 2:
			if (src) {
				sprintf(val, "%u", src - 1);
				rc = set_acl_param(val, acl_files[ACL_SRC]);
			}
			sprintf(val, "%u", equal);
			rc = set_acl_param(val, acl_files[ACL_PORT_MODE]);
			if (rc)
				goto prog_acl_done;
			port = param1;
			if (!port)
				break;
			sprintf(val, "%u", *port);
			rc = set_acl_param(val, acl_files[ACL_MIN_PORT]);
			if (rc)
				goto prog_acl_done;
			port = param2;
			if (!port)
				break;
			sprintf(val, "%u", *port);
			rc = set_acl_param(val, acl_files[ACL_MAX_PORT]);
			if (rc)
				goto prog_acl_done;
			break;
		}
		break;
	}
	sprintf(val, "%u", enable);
	rc = set_acl_param(val, acl_files[ACL_ENABLE]);
	if (rc)
		goto prog_acl_done;
	sprintf(val, "%u", mode);
	rc = set_acl_param(val, acl_files[ACL_MODE]);

prog_acl_done:
	return rc;
}

int get_acl_cmd(FILE *fp)
{
	int count;
	int hcount;
	unsigned int num[10];
	unsigned int hex[10];
	int rc;
	int cont = 1;
	char cmd[80];
	char line[80];

	do {
		printf("> ");
		if (fgets(line, 80, fp) == NULL)
			break;
		cmd[0] = '\0';
		count = sscanf(line, "%s %u %u %u %u %u %u %u %u %u %u", cmd,
			(unsigned int *) &num[0],
			(unsigned int *) &num[1],
			(unsigned int *) &num[2],
			(unsigned int *) &num[3],
			(unsigned int *) &num[4],
			(unsigned int *) &num[5],
			(unsigned int *) &num[6],
			(unsigned int *) &num[7],
			(unsigned int *) &num[8],
			(unsigned int *) &num[9]);
		hcount = sscanf(line, "%s %x %x %x %x %x %x %x %x %x %x", cmd,
			(unsigned int *) &hex[0],
			(unsigned int *) &hex[1],
			(unsigned int *) &hex[2],
			(unsigned int *) &hex[3],
			(unsigned int *) &hex[4],
			(unsigned int *) &hex[5],
			(unsigned int *) &hex[6],
			(unsigned int *) &hex[7],
			(unsigned int *) &hex[8],
			(unsigned int *) &hex[9]);
		if (count > 1 && !num[0] && hex[0])
			for (rc = 0; rc < count - 1; rc++)
				num[rc] = hex[rc];
		if (!strcmp(cmd, "da") || !strcmp(cmd, "sa")) {
			u8 *addr;

			count = sscanf(line, "%s %x:%x:%x:%x:%x:%x", cmd,
				&num[0], &num[1], &num[2], &num[3],
				&num[4], &num[5]);
			if (!strcmp(cmd, "da"))
				addr = acl_dst_addr;
			else
				addr = acl_src_addr;
			if (count >= 7) {
				for (count = 0; count < 6; count++)
					addr[count] = (u8) num[count];
			} else
				printf("%02x:%02x:%02x:%02x:%02x:%02x\n",
					addr[0],
					addr[1],
					addr[2],
					addr[3],
					addr[4],
					addr[5]);
		} else if (!strcmp(cmd, "ipd") || !strcmp(cmd, "ips") ||
		    !strcmp(cmd, "ipm")) {
			u8 *addr;

			count = sscanf(line, "%s %u.%u.%u.%u", cmd,
				&num[0], &num[1], &num[2], &num[3]);
			if (!strcmp(cmd, "ipd"))
				addr = acl_dst_ip;
			else if (!strcmp(cmd, "ips"))
				addr = acl_src_ip;
			else
				addr = acl_ip_mask;
			if (count >= 5) {
				for (count = 0; count < 4; count++)
					addr[count] = (u8) num[count];
			} else
				printf("%u.%u.%u.%u\n",
					addr[0],
					addr[1],
					addr[2],
					addr[3]);
		} else if (!strcmp(cmd, "sw")) {
			return 1;
		} else if (!strcmp(cmd, "hw")) {
			return 2;
		} else
		switch (line[0]) {
		case 'c':
			if (count >= 2) {
				acl_protocol = (u8) num[0];
			} else
				printf("protocol = %u\n", acl_protocol);
			break;
		case 'd':
			if (count >= 2) {
				gWaitDelay = num[0];
			} else
				printf("delay = %u\n", gWaitDelay);
			break;
		case 'i':
			if (count >= 2) {
				acl_index = (u8) num[0];
			} else
				printf("index = %u\n", acl_index);
			break;
		case 'm':
			if (count >= 2) {
				acl_max_port = (u16) num[0];
			} else
				printf("max port = %u\n", acl_max_port);
			break;
		case 'n':
			if (count >= 2) {
				acl_min_port = (u16) num[0];
			} else
				printf("min port = %u\n", acl_min_port);
			break;
		case 'p':
			if (count >= 2) {
				acl_port = (u8) num[0];
			} else
				printf("port = %u\n", acl_port);
			break;
		case 't':
			if (count >= 2) {
				acl_eth_type = (u16) hex[0];
			} else
				printf("ethtype = %04x\n", acl_eth_type);
			break;
		case 'x':
			if (!acl_test) {
				prep_acl();
				acl_count = 0;
				acl_test = 1;
			}
			break;
		case 'z':
			if (acl_test)
				break;
			switch (num[0]) {
			case 0:
				acl_dst_addr[0] = 0x01;
				acl_dst_addr[1] = 0x00;
				acl_dst_addr[2] = 0x5e;
				acl_dst_addr[3] = 0x00;
				acl_dst_addr[4] = 0x00;
				acl_dst_addr[5] = 0x6b;
				acl_eth_type = 0x0800;
				acl_test_cases = acl_test_cases_a;
				break;
			case 1:
				acl_dst_addr[0] = 0x01;
				acl_dst_addr[1] = 0x00;
				acl_dst_addr[2] = 0x5e;
				acl_dst_addr[3] = 0x00;
				acl_dst_addr[4] = 0x00;
				acl_dst_addr[5] = 0x6b;
				acl_eth_type = 0x0800;
				acl_test_cases = acl_test_cases_b;
				break;
			case 2:
				acl_dst_addr[0] = 0x33;
				acl_dst_addr[1] = 0x33;
				acl_dst_addr[2] = 0x00;
				acl_dst_addr[3] = 0x00;
				acl_dst_addr[4] = 0x00;
				acl_dst_addr[5] = 0x6b;
				acl_eth_type = 0x86dd;
				acl_test_cases = acl_test_cases_c;
				break;
			case 3:
				acl_dst_addr[0] = 0x01;
				acl_dst_addr[1] = 0x80;
				acl_dst_addr[2] = 0xc2;
				acl_dst_addr[3] = 0x00;
				acl_dst_addr[4] = 0x00;
				acl_dst_addr[5] = 0x0e;
				acl_eth_type = 0x88f7;
				acl_test_cases = acl_test_cases_d;
				break;
			}
			break;
		case 'h':
			printf("\tda [dst mac addr]\n");
			printf("\tsa [src mac addr]\n");
			printf("\n");
			printf("\tipd [dst ip addr]\n");
			printf("\tips [src ip addr]\n");
			printf("\tipm [ip mask]\n");
			printf("\n");
			printf("\tc [protocol]\n");
			printf("\td [delay]\n");
			printf("\ti [index]\n");
			printf("\tm [max port]\n");
			printf("\tn [min port]\n");
			printf("\tp [port]\n");
			printf("\tt [ether type]\n");
			printf("\tx\tstart test]\n");
			break;
		case 'q':
			cont = 0;
			break;
		}
	} while (cont);
	return 0;
}  /* get_acl_cmd */

static SOCKET create_sock(char *devname, char *ptp_ip, char *p2p_ip,
	char *local_ip, int port, int multi_loop)
{
	SOCKET sockfd;
	struct sockaddr_in servaddr;
	struct sockaddr_in6 servaddr6;
#if 0
	struct in_addr local;
#endif
	char *sockopt;
	int family = AF_INET;
	int reuse = 1;

	bzero(&servaddr, sizeof(servaddr));
	bzero(&servaddr6, sizeof(servaddr6));
	if (inet_pton(AF_INET, local_ip, &servaddr.sin_addr) > 0)
		family = AF_INET;
	else if (inet_pton(AF_INET6, local_ip, &servaddr6.sin6_addr) > 0)
		family = AF_INET6;

	sockfd = Socket(family, SOCK_DGRAM, 0);

	if (AF_INET6 == family) {
		servaddr6.sin6_family = family;
		memcpy(servaddr6.sin6_addr.s6_addr, &in6addr_any,
			sizeof(in6addr_any));
		servaddr6.sin6_port = htons((short) port);
	} else {
		servaddr.sin_family = family;
		servaddr.sin_addr.s_addr = INADDR_ANY;
		servaddr.sin_port = htons((short) port);
	}

	sockopt = (char *) &reuse;
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, sockopt,
			sizeof(reuse)) < 0) {
		printf("reuse\n");
		return -1;
	}
	if (AF_INET6 == family) {
		struct ipv6_mreq mreq;
		u_int iface;
		int hop;
		u_int loop;

		Bind(sockfd, (SA *) &servaddr6, sizeof(servaddr6));
#ifdef IPV6_CLASS
		if (PTP_EVENT_PORT == port) {
			u_int tclass;

			tclass = 0xff;
			sockopt = (char *) &tclass;
			if (setsockopt(sockfd, IPPROTO_IPV6, IPV6_TCLASS,
					sockopt, sizeof(tclass)) < 0) {
				err_ret("no tclass");
			}
		}
#endif

		if (!ptp_ip)
			return sockfd;

		inet_pton(AF_INET6, ptp_ip, &mreq.ipv6mr_multiaddr);
		mreq.ipv6mr_interface = ipv6_interface;
		sockopt = (char *) &mreq;
		if (setsockopt(sockfd, IPPROTO_IPV6, IPV6_ADD_MEMBERSHIP,
				sockopt, sizeof(mreq)) < 0) {
			err_ret("add member");
			return -1;
		}
		inet_pton(AF_INET6, p2p_ip, &mreq.ipv6mr_multiaddr);
		mreq.ipv6mr_interface = ipv6_interface;
		sockopt = (char *) &mreq;
		if (setsockopt(sockfd, IPPROTO_IPV6, IPV6_ADD_MEMBERSHIP,
				sockopt, sizeof(mreq)) < 0) {
			err_ret("add member to p2p");
			return -1;
		}
		if (ipv6_interface) {
			iface = ipv6_interface;
			sockopt = (char *) &iface;
			if (setsockopt(sockfd, IPPROTO_IPV6, IPV6_MULTICAST_IF,
					sockopt, sizeof(iface)) < 0) {
				err_ret("multi if");
				return -1;
			}
		}
		hop = 1;
		sockopt = (char *) &hop;
		if (setsockopt(sockfd, IPPROTO_IPV6, IPV6_MULTICAST_HOPS,
				sockopt, sizeof(hop)) < 0) {
			err_ret("hop");
			return -1;
		}
		loop = 0;
		if (multi_loop)
			loop = 1;
		sockopt = (char *) &loop;
		if (setsockopt(sockfd, IPPROTO_IPV6, IPV6_MULTICAST_LOOP,
				sockopt, sizeof(loop)) < 0) {
			err_ret("loop");
			return -1;
		}
	} else {
		struct ip_mreqn mreq;
		u_char hop;
		u_char loop;
		int tos;

		Bind(sockfd, (SA *) &servaddr, sizeof(servaddr));
		if (PTP_EVENT_PORT == port) {
			tos = 0xb8;
			sockopt = (char *) &tos;
			if (setsockopt(sockfd, IPPROTO_IP, IP_TOS,
					sockopt, sizeof(tos)) < 0) {
				err_ret("tos");
				return -1;
			}
		}

		if (!ptp_ip)
			return sockfd;

		mreq.imr_multiaddr.s_addr = inet_addr(ptp_ip);
		mreq.imr_address.s_addr = inet_addr(local_ip);
		mreq.imr_ifindex = ipv6_interface;
		sockopt = (char *) &mreq;
		if (setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, sockopt,
				sizeof(mreq)) < 0) {
			err_ret("add member");
			return -1;
		}
		mreq.imr_multiaddr.s_addr = inet_addr(p2p_ip);
		mreq.imr_address.s_addr = inet_addr(local_ip);
		mreq.imr_ifindex = ipv6_interface;
		sockopt = (char *) &mreq;
		if (setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, sockopt,
				sizeof(mreq)) < 0) {
			err_ret("add member to p2p");
			return -1;
		}
		mreq.imr_ifindex = ipv6_interface;
		sockopt = (char *) &mreq;
		if (setsockopt(sockfd, IPPROTO_IP, IP_MULTICAST_IF, sockopt,
				sizeof(mreq)) < 0) {
			err_ret("multi if");
			return -1;
		}
		hop = 1;
		sockopt = (char *) &hop;
		if (setsockopt(sockfd, IPPROTO_IP, IP_MULTICAST_TTL, sockopt,
				sizeof(hop)) < 0) {
			err_ret("hop");
			return -1;
		}
		loop = 0;
		if (multi_loop)
			loop = 1;
		sockopt = (char *) &loop;
		if (setsockopt(sockfd, IPPROTO_IP, IP_MULTICAST_LOOP, sockopt,
				sizeof(loop)) < 0) {
			err_ret("loop");
			return -1;
		}
		if (setsockopt(sockfd, SOL_SOCKET, SO_BINDTODEVICE,
		    devname, strlen(devname))) {
			err_ret("bindtodev");
			return -1;
		}
	}
	return sockfd;
}  /* create_sock */

struct sock_buf {
	struct sockaddr *from;
	u8 *buf;
	int len;
};

static int check_loop(struct sockaddr *sa, int salen)
{
	struct sockaddr_in *addr4;
	struct sockaddr_in6 *addr6;
#ifdef _SYS_SOCKET_H
	struct sockaddr_ll *addr;
#endif

	if (AF_INET6 == sa->sa_family) {
		addr6 = (struct sockaddr_in6 *) sa;
		if (memcmp(&addr6->sin6_addr, host_addr6, 16) == 0)
			return 1;
		if (memcmp(&addr6->sin6_addr.s6_addr[12], host_addr, 4) == 0)
			return 2;
	} else if (AF_INET == sa->sa_family) {
		addr4 = (struct sockaddr_in *) sa;
		if (memcmp(&addr4->sin_addr, host_addr, 4) == 0)
			return 1;
	} else {
#ifdef _SYS_SOCKET_H
		addr = (struct sockaddr_ll *) sa;
		if (addr->sll_ifindex != eth_pdelay_addr.sll_ifindex)
			return 2;
		if (memcmp(addr->sll_addr, hw_addr, ETH_ALEN) == 0)
			return 1;
#endif
	}
	return 0;
}

static int check_dup(struct sock_buf *cur, struct sock_buf *last, int len)
{
	if (cur->len == last->len &&
			memcmp(cur->from, last->from, len) == 0 &&
			memcmp(cur->buf, last->buf, cur->len) == 0)
		return 1;
	return 0;
}

#ifdef _SYS_SOCKET_H
void *

#else
void
#endif
ReceiveTask(void *param)
{
	PTTaskParam pTaskParam;
	u8 *recvbuf;
	SOCKET sockfd;
	SOCKET fd[3];
	struct sock_buf buf[2];
	struct sockaddr_in6 cliaddr[2];
	struct sockaddr_in *addr4;
	struct sockaddr_in6 *addr6;
#ifdef _SYS_SOCKET_H
	struct sockaddr_ll *addr;
#endif
	struct timeval timer;
	fd_set rset;
	fd_set allrset;
	socklen_t len;
	int maxfdp1;
	struct ptp_msg *msg;
	int i;
	char in_addr[80];
	int cur;
	int last;
	int nsel;
	int looped;
	int msglen;
	int *acl = NULL;
	int acl_testing = 0;

	pTaskParam = (PTTaskParam) param;
	fd[0] = (SOCKET) pTaskParam->multicast;
	fd[1] = (SOCKET) pTaskParam->unicast;
	fd[2] = (SOCKET) pTaskParam->management4;
	len = (MAXBUFFER + 3) & ~3;
	recvbuf = malloc(len * 2);
	buf[0].len = buf[1].len = 0;
	buf[0].buf = recvbuf;
	buf[1].buf = recvbuf + len;
	buf[0].from = (struct sockaddr *) &cliaddr[0];
	buf[1].from = (struct sockaddr *) &cliaddr[1];
	cur = 0;
	last = 1;

#ifdef _WIN32
	SetEvent( pTaskParam->hevTaskComplete );
#endif
	if (pTaskParam->acl_test)
		acl = pTaskParam->acl_test;

	bzero(cliaddr, sizeof(cliaddr));

	FD_ZERO(&allrset);
	FD_SET(fd[0], &allrset);
	if (fd[1])
		FD_SET(fd[1], &allrset);
	if (fd[2])
		FD_SET(fd[2], &allrset);
	maxfdp1 = fd[0];
	if ((int) fd[1] > maxfdp1)
		maxfdp1 = fd[1];
	if ((int) fd[2] > maxfdp1)
		maxfdp1 = fd[2];
	maxfdp1++;
	FOREVER {
		if ( pTaskParam->fTaskStop ) {
			break;
		}

		rset = allrset;
		sockfd = 0;

		timerclear( &timer );
		timer.tv_usec = gWaitDelay * 1000;

		if (acl_testing) {
			struct acl_test_case *test =
				&acl_test_cases[*acl - 1];

			prog_acl(test->mode, test->enable, test->src,
				test->equal, test->param1, test->param2);
			(*acl)++;
			printf(".");
			fflush(stdout);
			if (!test->mode) {
				printf("count = %d / %d\n", acl_count,
					*acl - 2);
				acl_testing = 0;
				(*acl) = 0;
			}
		}

		nsel = Select( maxfdp1, &rset, NULL, NULL, &timer );

		/* socket is not readable */
		if (!nsel) {
			if (pTaskParam->fTaskStop) {
				break;
			}
			continue;
		}

		for (i = 0; i < 3; i++) {
			if (nsel <= 0)
				break;

			len = sizeof(struct sockaddr_in6);
			if (FD_ISSET(fd[i], &rset) && sockfd != fd[i])
				sockfd = fd[i];
			else
				continue;

			buf[cur].len = Recvfrom(sockfd, buf[cur].buf,
				MAXBUFFER, 0, buf[cur].from, &len);
			--nsel;
			if (AF_INET6 == buf[cur].from->sa_family) {
				addr6 = (struct sockaddr_in6 *) buf[cur].from;
				inet_ntop(AF_INET6, &addr6->sin6_addr,
					in_addr, sizeof(in_addr));
			} else if (AF_INET == buf[cur].from->sa_family) {
				addr4 = (struct sockaddr_in *) buf[cur].from;
				inet_ntop(AF_INET, &addr4->sin_addr,
					in_addr, sizeof(in_addr));
			} else {
#ifdef _SYS_SOCKET_H
				addr = (struct sockaddr_ll *) buf[cur].from;
				sprintf(in_addr,
					"%02x:%02x:%02x:%02x:%02x:%02x [%d]",
					addr->sll_addr[0], addr->sll_addr[1],
					addr->sll_addr[2], addr->sll_addr[3],
					addr->sll_addr[4], addr->sll_addr[5],
					addr->sll_ifindex);
#endif
			}
			if (dbg_rcv)
				Pthread_mutex_lock(&disp_mutex);
			if (dbg_rcv >= 4)
				printf("r: %d=%d %d=%s\n", sockfd,
					buf[cur].len, len, in_addr);
			msglen = buf[cur].len;
#ifdef _SYS_SOCKET_H
			if (AF_PACKET == buf[cur].from->sa_family) {
				msg = (struct ptp_msg *) &buf[cur].buf[14];
				msglen -= 14;
			} else
#endif
				msg = (struct ptp_msg *) buf[cur].buf;
			if (msg->hdr.versionPTP < 2) {
				if (dbg_rcv >= 4)
					printf("PTPv1 not supported\n");
				if (dbg_rcv)
					Pthread_mutex_unlock(&disp_mutex);
				continue;
			}
			looped = check_loop(buf[cur].from, len);
			if (looped) {
				int ignored = 1;

				if (MANAGEMENT_MSG == msg->hdr.messageType &&
						1 == looped)
					ignored = 0;
				if (ignored) {
					if (dbg_rcv >= 4)
						printf("(ignored)\n");
					if (dbg_rcv)
						Pthread_mutex_unlock(
							&disp_mutex);
					continue;
				}
			}
			if (check_dup(&buf[cur], &buf[last], len)) {
				if (dbg_rcv >= 4)
					printf("(dup)\n");
				if (dbg_rcv)
					Pthread_mutex_unlock(&disp_mutex);
				continue;
			} else {
				if (looped && dbg_rcv >= 4)
					printf("(looped)\n");
				cur = !cur;
				last = !last;
			}
			if (ptp_version >= 2) {
				int rc;

				ptp_rx_port = 0;
				rc = get_rx_timestamp(&msg->hdr);
				if (rc && dbg_rcv > 5)
					print_err(rc);
			}
			if (dbg_rcv)
				disp_msg(msg, msglen);
			if (dbg_rcv)
				Pthread_mutex_unlock(&disp_mutex);
#if 0
			if (ptp_count > 0 &&
					(DELAY_REQ_MSG ==
					msg->hdr.messageType ||
					PDELAY_REQ_MSG ==
					msg->hdr.messageType)) {
				int count;
				u16 seqid = ntohs(msg->hdr.sequenceId) -
					ptp_count + 1;
				u16 saved = msg->hdr.sequenceId;

				if (ptp_count > 2)
					seqid++;
				for (count = 0; count < ptp_count; count++) {
					msg->hdr.sequenceId = htons(seqid);
					resp_msg(msg,
						buf[last].from->sa_family);
					seqid++;
				}
				msg->hdr.sequenceId = saved;
			}
#endif
			if (acl_testing) {
				acl_count++;
				printf("^");
				fflush(stdout);
			} else if (acl && *acl)
				acl_testing = 1;
		}
	}
	free(recvbuf);
	pTaskParam->fTaskStop = TRUE;

#ifdef _WIN32
	SetEvent( pTaskParam->hevTaskComplete );
#endif

#ifdef _SYS_SOCKET_H
	return NULL;
#endif
}  /* ReceiveTask */

struct ip_info {
	struct sockaddr_in addr;
	struct sockaddr_in6 addr6;
	u8 hwaddr[8];
	int plen;
	int scope;
	int if_idx;
};

int get_host_info(char *devname, struct ip_info *info)
{
	struct ifi_info *ifi;
	struct ifi_info *ifihead;

	ifihead = get_ifi_info(AF_INET, 1);
	for (ifi = ifihead; ifi != NULL; ifi = ifi->ifi_next) {
		if (!strcmp(devname, ifi->ifi_name)) {
			info->if_idx = ifi->ifi_index;
			if (ifi->ifi_addr != NULL)
				memcpy(&info->addr, ifi->ifi_addr,
					sizeof(struct sockaddr_in));
			memset(info->hwaddr, 0, 8);
			if (ifi->ifi_hlen > 0)
				memcpy(info->hwaddr, ifi->ifi_haddr,
					ifi->ifi_hlen);
			info->plen = 0;
			if (ifi->ifi_addr6 != NULL) {
				memcpy(&info->addr6, ifi->ifi_addr6,
					sizeof(struct sockaddr_in6));
				info->plen = ifi->ifi_plen;
				info->scope = ifi->ifi_scope;
			} else if (ifi->ifi_hlen > 0) {
				u8 *data = (u8 *) &info->addr6.sin6_addr;

				memset(data, 0, 16);
				data[0] = 0xfe;
				data[1] = 0x80;
				memcpy(&data[8], ifi->ifi_haddr, 3);
				data[8] ^= 0x02;
				data[11] = 0xff;
				data[12] = 0xfe;
				memcpy(&data[13], &ifi->ifi_haddr[3], 3);
				info->addr6.sin6_family = AF_INET6;
				info->plen = 64;
				info->scope = 0x20;
			}
			return 1;
		}
	}
	free_ifi_info(ifihead);
	return 0;
}

#ifdef _SYS_SOCKET_H
int get_dev_info(char *devname, struct ip_info *info)
{
	FILE *f;
	int dad_status;
	int count;
	int rc;
	char addr6[40];
	char addr6p[8][5];

	struct ipv6_info *ipv6;
	struct ipv6_info *ipv6head = NULL;

	char path[80];
	char file[40];
	int num[6];
	int found = FALSE;

	/* No IP address. */
	info->addr.sin_family = AF_UNSPEC;

	/* Assume no IPv6 address. */
	info->plen = 0;
	memset(info->hwaddr, 0, 8);

	f = fopen(_PATH_PROCNET_IFINET6, "r");
	if (!f)
		goto get_dev_raw;
	count = 10;
	ipv6head = calloc(count, sizeof(struct ipv6_info));
	ipv6 = ipv6head;
	while (fscanf(f, "%4s%4s%4s%4s%4s%4s%4s%4s %02x %02x %02x %02x %20s\n",
			addr6p[0], addr6p[1], addr6p[2], addr6p[3], addr6p[4],
			addr6p[5], addr6p[6], addr6p[7],
			&ipv6->if_idx, &ipv6->plen, &ipv6->scope, &dad_status,
			ipv6->devname) != EOF) {
		sprintf(addr6, "%s:%s:%s:%s:%s:%s:%s:%s",
			addr6p[0], addr6p[1], addr6p[2], addr6p[3],
			addr6p[4], addr6p[5], addr6p[6], addr6p[7]);
		inet_pton(AF_INET6, addr6,
			(struct sockaddr *) &ipv6->addr.sin6_addr);
		ipv6->addr.sin6_family = AF_INET6;
		if (!strcmp(devname, ipv6->devname)) {
			memcpy(&info->addr6, &ipv6->addr,
				sizeof(struct sockaddr_in6));
			info->if_idx = ipv6->if_idx;
			info->plen = ipv6->plen;
			info->scope = ipv6->scope;
			found = TRUE;
			break;
		}
		ipv6++;
		count--;
		if (1 == count)
			break;
	}
	free(ipv6head);
	fclose(f);

get_dev_raw:
	if (found)
		goto get_dev_addr;

	sprintf(path, "%s%s/%s", _PATH_SYSNET_DEV, devname, NETDEV_FLAGS);
	f = fopen(path, "r");
	if (!f)
		goto get_dev_done;
	rc = fscanf(f, "%x", &num[0]);
	fclose(f);

	sprintf(path, "%s%s/%s", _PATH_SYSNET_DEV, devname, NETDEV_OPERSTATE);
	f = fopen(path, "r");
	if (!f)
		goto get_dev_addr;
	rc = fscanf(f, "%s", file);
	fclose(f);
	if ((!strcmp(file, "up") && !(num[0] & IFF_UP)) ||
	    (!strcmp(file, "down") && (num[0] & IFF_UP)))
		printf(" ? %s 0x%04x\n", file, num[0]);

	/* Device not running. */
	if (!(num[0] & IFF_UP))
		goto get_dev_done;

get_dev_addr:
	sprintf(path, "%s%s/%s", _PATH_SYSNET_DEV, devname, NETDEV_IFINDEX);
	f = fopen(path, "r");
	if (f) {
		rc = fscanf(f, "%u", &num[0]);
		fclose(f);
		if (!found)
			info->if_idx = num[0];
		else if (info->if_idx != num[0])
			printf(" ? %d %d\n", info->if_idx, num[0]);
	}

	found = TRUE;

	sprintf(path, "%s%s/%s", _PATH_SYSNET_DEV, devname, NETDEV_ADDRESS);
	f = fopen(path, "r");
	if (!f)
		goto get_dev_done;
	rc = fscanf(f, "%x:%x:%x:%x:%x:%x",
		&num[0], &num[1], &num[2], &num[3], &num[4], &num[5]);
	fclose(f);
	for (count = 0; count < 6; count++)
		info->hwaddr[count] = (u8) num[count];

get_dev_done:
	return found;
}

static void add_multi(SOCKET sockfd, char *local_if)
{
	struct ifreq ifr;
	int rc;

	strcpy(ifr.ifr_name, local_if);
	ifr.ifr_hwaddr.sa_family = AF_UNSPEC;
	memcpy(ifr.ifr_hwaddr.sa_data, eth_pdelay, ETH_ALEN);
	rc = ioctl(sockfd, SIOCADDMULTI, &ifr);
	if (eth_others[0]) {
		memcpy(ifr.ifr_hwaddr.sa_data, eth_others, ETH_ALEN);
		rc = ioctl(sockfd, SIOCADDMULTI, &ifr);
	}
}

static void del_multi(SOCKET sockfd, char *local_if)
{
	struct ifreq ifr;
	int rc;

	strcpy(ifr.ifr_name, local_if);
	ifr.ifr_hwaddr.sa_family = AF_UNSPEC;
	memcpy(ifr.ifr_hwaddr.sa_data, eth_pdelay, ETH_ALEN);
	rc = ioctl(sockfd, SIOCDELMULTI, &ifr);
	if (eth_others[0]) {
		memcpy(ifr.ifr_hwaddr.sa_data, eth_others, ETH_ALEN);
		rc = ioctl(sockfd, SIOCDELMULTI, &ifr);
	}
}

static SOCKET create_raw(struct ip_info *info, char *dest)
{
	SOCKET sockfd;
	struct ethhdr *eh;
	int addr[ETH_ALEN];
	int cnt;

	sockfd = Socket(AF_PACKET, SOCK_RAW, htons(ptp_proto));
	if (sockfd < 0)
		return sockfd;

	cnt = sscanf(dest, "%x:%x:%x:%x:%x:%x",
		&addr[0], &addr[1], &addr[2], &addr[3], &addr[4], &addr[5]);
	eth_pdelay_addr.sll_family = PF_PACKET;
	eth_pdelay_addr.sll_protocol = htons(ptp_proto);
	eth_pdelay_addr.sll_ifindex = info->if_idx;
	eth_pdelay_addr.sll_hatype = ARPHRD_ETHER;
	eth_pdelay_addr.sll_halen = ETH_ALEN;
	if (ETH_ALEN == cnt) {
		eth_pdelay_addr.sll_pkttype = PACKET_OTHERHOST;
		eth_pdelay_addr.sll_addr[0] = (u8) addr[0];
		eth_pdelay_addr.sll_addr[1] = (u8) addr[1];
		eth_pdelay_addr.sll_addr[2] = (u8) addr[2];
		eth_pdelay_addr.sll_addr[3] = (u8) addr[3];
		eth_pdelay_addr.sll_addr[4] = (u8) addr[4];
		eth_pdelay_addr.sll_addr[5] = (u8) addr[5];
	} else {
		eth_pdelay_addr.sll_pkttype = PACKET_MULTICAST;
		memcpy(eth_pdelay_addr.sll_addr, eth_pdelay, ETH_ALEN);
	}
	eth_pdelay_addr.sll_addr[6] = 0x00;
	eth_pdelay_addr.sll_addr[7] = 0x00;
	eth_others_addr.sll_family = PF_PACKET;
	eth_others_addr.sll_protocol = htons(ptp_proto);
	eth_others_addr.sll_ifindex = info->if_idx;
	eth_others_addr.sll_hatype = ARPHRD_ETHER;
	eth_others_addr.sll_halen = ETH_ALEN;
	if (ETH_ALEN == cnt) {
		eth_others_addr.sll_pkttype = PACKET_OTHERHOST;
		eth_others_addr.sll_addr[0] = (u8) addr[0];
		eth_others_addr.sll_addr[1] = (u8) addr[1];
		eth_others_addr.sll_addr[2] = (u8) addr[2];
		eth_others_addr.sll_addr[3] = (u8) addr[3];
		eth_others_addr.sll_addr[4] = (u8) addr[4];
		eth_others_addr.sll_addr[5] = (u8) addr[5];
	} else {
		eth_others_addr.sll_pkttype = PACKET_MULTICAST;
		if (eth_others[0])
			memcpy(eth_others_addr.sll_addr, eth_others, ETH_ALEN);
		else
			memcpy(eth_others_addr.sll_addr, eth_pdelay, ETH_ALEN);
	}
	eth_others_addr.sll_addr[6] = 0x00;
	eth_others_addr.sll_addr[7] = 0x00;

	eth_pdelay_buf = malloc(1518);
	eth_others_buf = malloc(1518);
	memcpy(eth_pdelay_buf, eth_pdelay_addr.sll_addr, ETH_ALEN);
	memcpy(&eth_pdelay_buf[ETH_ALEN], info->hwaddr, ETH_ALEN);
	eh = (struct ethhdr *) eth_pdelay_buf;
	eh->h_proto = htons(ptp_proto);
	memcpy(eth_others_buf, eth_others_addr.sll_addr, ETH_ALEN);
	memcpy(&eth_others_buf[ETH_ALEN], info->hwaddr, ETH_ALEN);
	eh = (struct ethhdr *) eth_others_buf;
	eh->h_proto = htons(ptp_proto);

	return sockfd;
}
#endif

int main(int argc, char *argv[])
{
	TTaskParam param[4];

#ifdef _SYS_SOCKET_H
	pthread_t tid[4];
	void *status;

#elif defined( _WIN32 )
	DWORD rc;
#endif
	char dest_ip[40];
	char host_ip4[40];
	char host_ip6[40];
	char *host_ip;
	int family;
	char *ptp_ip = NULL;
	char *p2p_ip = NULL;
	int i;
	int task_cnt;
	struct ip_info info;
	int multi_loop = 0;
	int unicast_sock = 0;

	SocketInit(0);

	if (argc < 2) {
		printf("usage: %s <local_if> [-6[0..f]] [-p]",
			argv[0]);
		printf(" [-u <dest_ip>] [-m (unicast socket)]\n\t");
		printf("[-d[#] (debug rx)] [-l (multicast loop)]\n");
		printf("\t[-r[#] (redundancy)] [-v reserved]\n");
		return 1;
	}
	family = AF_INET;
	dest_ip[0] = '\0';
	strcpy(PTP_ip_addr6, PTP_ip_addr6_const);
	strcpy(P2P_ip_addr6, P2P_ip_addr6_const);
	if (argc > 2) {
		i = 2;
		while (i < argc) {
			if ('-' == argv[i][0]) {
				switch (argv[i][1]) {
				case '6':
					family = AF_INET6;
					if (argv[i][2]) {
						PTP_ip_addr6[3] = argv[i][2];
						if (argv[i][3])
							P2P_ip_addr6[3] =
								argv[i][3];
					}
					break;
#ifdef _SYS_SOCKET_H
				case 'p':
					family = AF_PACKET;
					if ('1' == argv[i][2]) {
						eth_others[0] = 0;
						transport = 1;
					}
					break;
#endif
				case 'r':
					hsr = 2;
					if ('0' <= argv[i][2] &&
							argv[i][2] <= '9')
						hsr = argv[i][2] - '0';
					switch (hsr) {
					case 0:
					case 1:
						prp = hsr + 1;
						hsr = 0;
						break;
					case 2:
					default:
						ptp_proto = HSR_PROTO;
						break;
					}
					break;
				case 'd':
					dbg_rcv = 5;
					if ('0' <= argv[i][2] &&
							argv[i][2] <= '9')
						dbg_rcv = argv[i][2] - '0';
					break;
				case 'l':
					multi_loop = 1;
					break;
				case 'm':
					unicast_sock = 1;
					break;
				case 'u':
					++i;
					strcpy(dest_ip, argv[i]);
					ptp_unicast = 1;
					break;
				case 'v':
					++i;
					reserved3 = atoi(argv[i]);
					break;
				case 't':
					port_acl_test = 1;
					break;
				}
			}
			++i;
		}
	}
	strncpy(devname, argv[1], sizeof(devname));
	host_ip = strchr(devname, '.');
	if (host_ip != NULL)
		*host_ip = 0;
	strncpy(ptpdev.name, devname, sizeof(ptpdev.name));

	sprintf(acl_sysfs, "/sys/class/net/%s", devname);
	acl_eth_type = 0x0800;
	acl_dst_addr[0] = 0x01;
	acl_dst_addr[1] = 0x00;
	acl_dst_addr[2] = 0x5e;
	acl_dst_addr[3] = 0x00;
	acl_dst_addr[4] = 0x00;
	acl_dst_addr[5] = 0x6b;
	acl_protocol = 17;
	acl_min_port = 319;
	acl_max_port = 320;
	acl_ip_mask[0] = 0;
	acl_ip_mask[1] = 0;
	acl_ip_mask[2] = 0;
	acl_ip_mask[3] = 0;
	acl_dst_ip[0] = 224;
	acl_dst_ip[1] = 0;
	acl_dst_ip[2] = 0;
	acl_dst_ip[3] = 107;
	acl_test_cases = acl_test_cases_a;

	masterClockIdentity.addr[0] = 0x00;
	masterClockIdentity.addr[1] = 0x22;
	masterClockIdentity.addr[2] = 0x19;
	masterClockIdentity.addr[3] = 0xFF;
	masterClockIdentity.addr[4] = 0xFE;
	masterClockIdentity.addr[5] = 0xFA;
	masterClockIdentity.addr[6] = 0x23;
	masterClockIdentity.addr[7] = 0x88;

	if (get_host_info(argv[1], &info)) {
		memcpy(host_addr, &info.addr.sin_addr, 4);
		inet_ntop(AF_INET, &info.addr.sin_addr,
			host_ip4, sizeof(host_ip4));
		printf("%s\n", host_ip4);
		ipv6_interface = info.if_idx;
		if (info.plen) {
			inet_ntop(AF_INET6, &info.addr6.sin6_addr,
				host_ip6, sizeof(host_ip6));
			printf("%s\n", host_ip6);
			memcpy(host_addr6, &info.addr6.sin6_addr, 16);
			ipv6_interface = info.if_idx;
		}
#ifdef _SYS_SOCKET_H
		memcpy(hw_addr, info.hwaddr, ETH_ALEN);
#endif
		memcpy(&selfClockIdentity.addr[0], info.hwaddr, 3);
		selfClockIdentity.addr[3] = 0xFF;
		selfClockIdentity.addr[4] = 0xFE;
		memcpy(&selfClockIdentity.addr[5], &info.hwaddr[3], 3);
#ifdef _SYS_SOCKET_H
	} else if (get_dev_info(argv[1], &info)) {
		ipv6_interface = info.if_idx;
		if (info.plen) {
			inet_ntop(AF_INET6, &info.addr6.sin6_addr,
				host_ip6, sizeof(host_ip6));
			printf("%s\n", host_ip6);
			memcpy(host_addr6, &info.addr6.sin6_addr, 16);
			ipv6_interface = info.if_idx;
		}
		memcpy(hw_addr, info.hwaddr, ETH_ALEN);
		memcpy(&selfClockIdentity.addr[0], info.hwaddr, 3);
		selfClockIdentity.addr[3] = 0xFF;
		selfClockIdentity.addr[4] = 0xFE;
		memcpy(&selfClockIdentity.addr[5], &info.hwaddr[3], 3);
		if (AF_INET == family)
			family = AF_PACKET;
#endif
	} else {
		printf("cannot locate IP address\n");
		exit(1);
	}

	ip_family = family;
	if (AF_INET6 == family) {
		host_ip = host_ip6;
		event_addr6.sin6_family = family;
		event_addr6.sin6_port = htons(PTP_EVENT_PORT);

		general_addr6.sin6_family = family;
		general_addr6.sin6_port = htons(PTP_GENERAL_PORT);

		p2p_event_addr6.sin6_family = family;
		p2p_event_addr6.sin6_port = htons(PTP_EVENT_PORT);

		p2p_general_addr6.sin6_family = family;
		p2p_general_addr6.sin6_port = htons(PTP_GENERAL_PORT);
		if (ptp_unicast) {
			inet_pton(family, dest_ip, &event_addr6.sin6_addr);
			inet_pton(family, dest_ip, &general_addr6.sin6_addr);
			inet_pton(family, dest_ip, &p2p_event_addr6.sin6_addr);
			inet_pton(family, dest_ip,
				&p2p_general_addr6.sin6_addr);
		} else {
			ptp_ip = PTP_ip_addr6;
			p2p_ip = P2P_ip_addr6;

			inet_pton(family, ptp_ip, &event_addr6.sin6_addr);
			inet_pton(family, ptp_ip, &general_addr6.sin6_addr);
			inet_pton(family, p2p_ip, &p2p_event_addr6.sin6_addr);
			inet_pton(family, p2p_ip,
				&p2p_general_addr6.sin6_addr);
		}
	} else {
		family = AF_INET;
		host_ip = host_ip4;
		event_addr.sin_family = family;
		event_addr.sin_port = htons(PTP_EVENT_PORT);

		general_addr.sin_family = family;
		general_addr.sin_port = htons(PTP_GENERAL_PORT);

		p2p_event_addr.sin_family = family;
		p2p_event_addr.sin_port = htons(PTP_EVENT_PORT);

		p2p_general_addr.sin_family = family;
		p2p_general_addr.sin_port = htons(PTP_GENERAL_PORT);
		if (ptp_unicast && AF_INET == ip_family) {
			event_addr.sin_addr.s_addr = inet_addr(dest_ip);
			general_addr.sin_addr.s_addr = inet_addr(dest_ip);
			p2p_event_addr.sin_addr.s_addr = inet_addr(dest_ip);
			p2p_general_addr.sin_addr.s_addr = inet_addr(dest_ip);
		} else {
			ptp_ip = PTP_ip_addr;
			p2p_ip = P2P_ip_addr;

			event_addr.sin_addr.s_addr = inet_addr(ptp_ip);
			general_addr.sin_addr.s_addr = inet_addr(ptp_ip);
			p2p_event_addr.sin_addr.s_addr = inet_addr(p2p_ip);
			p2p_general_addr.sin_addr.s_addr = inet_addr(p2p_ip);
		}
	}
	management_addr.sin_family = AF_INET;
	management_addr.sin_port = htons(PTP_GENERAL_PORT);
	inet_pton(AF_INET, PTP_ip_addr, &management_addr.sin_addr);
	management_addr6.sin6_family = AF_INET6;
	management_addr6.sin6_port = htons(PTP_GENERAL_PORT);
	inet_pton(AF_INET6, PTP_ip_addr6, &management_addr6.sin6_addr);

	event_fd = create_sock(argv[1], ptp_ip, p2p_ip, host_ip,
		PTP_EVENT_PORT, 0);
	if (event_fd < 0) {
		printf("Cannot create socket\n");
		return 1;
	}
	general_fd = create_sock(argv[1], ptp_ip, p2p_ip, host_ip,
		PTP_GENERAL_PORT, multi_loop);
	if (general_fd < 0) {
		printf("Cannot create socket\n");
		return 1;
	}
	task_cnt = 2;
	uni_event_fd = event_fd;
	uni_general_fd = general_fd;
	if (!unicast_sock)
		ptp_ip = NULL;
	if (ptp_ip) {
		uni_event_fd = create_sock(argv[1], NULL, NULL, host_ip,
			PTP_EVENT_PORT, 0);
		if (uni_event_fd < 0) {
			printf("Cannot create socket\n");
			return 1;
		}
		uni_general_fd = create_sock(argv[1], NULL, NULL, host_ip,
			PTP_GENERAL_PORT, 0);
		if (uni_general_fd < 0) {
			printf("Cannot create socket\n");
			return 1;
		}
	}
	management4_fd = general_fd;
	if (AF_INET6 == ip_family) {
		management4_fd = create_sock(argv[1], PTP_ip_addr, P2P_ip_addr,
			host_ip4, PTP_GENERAL_PORT, multi_loop);
		if (management4_fd < 0) {
			printf("Cannot create socket\n");
		}
	}
	sockptr = &event_fd;
	ptpdev.sock = event_fd;

#ifdef _SYS_SOCKET_H
	eth_fd = -1;
	if (AF_PACKET == ip_family) {
		eth_fd = create_raw(&info, dest_ip);
		if (eth_fd < 0) {
			printf("Cannot create socket\n");
			return 1;
		}
		add_multi(eth_fd, argv[1]);
		task_cnt++;
		sockptr = &eth_fd;
		ptpdev.sock = eth_fd;
	}
#endif

	memset(param, 0, sizeof(param));
	for (i = 0; i < task_cnt; i++) {
		param[i].fTaskStop = FALSE;
		switch (i) {
		case 0:
			param[i].multicast = event_fd;
			param[i].unicast = uni_event_fd;
			param[i].management4 = 0;
			param[i].msgs = event_msgs;
			if (AF_INET == ip_family || AF_INET6 == ip_family)
				param[i].acl_test = &acl_test;
			break;
		case 1:
			param[i].multicast = general_fd;
			param[i].unicast = uni_general_fd;
			param[i].management4 = management4_fd;
			param[i].msgs = general_msgs;
			break;
		case 2:
			param[i].multicast = eth_fd;
			param[i].unicast = 0;
			param[i].management4 = 0;
			param[i].acl_test = &acl_test;
			break;
		}

#ifdef _SYS_SOCKET_H
		Pthread_create(&tid[i], NULL, ReceiveTask, &param[i]);

#elif defined( _WIN32 )
		param[i].hevTaskComplete =
			CreateEvent( NULL, TRUE, FALSE, NULL );
		if ( NULL == param[i].hevTaskComplete ) {

		}
		_beginthread( ReceiveTask, 4096, &param[i] );

		// wait for task to start
		rc = WaitForSingleObject( param[i].hevTaskComplete, INFINITE );
		if ( WAIT_FAILED == rc ) {

		}
		ResetEvent( param[i].hevTaskComplete );
		Sleep( 1 );
#endif
	}

	if ( !param[0].fTaskStop ) {
		int capability;
		int rc;

		ptp_hw = 0;
		capability = PTP_KNOW_ABOUT_MULT_PORTS;
		rc = ptp_dev_init(&ptpdev, capability,
			&ptp_drift, &ptp_version, &ptp_ports, &ptp_host_port);
		if (!rc) {
			printf("drift=%d version=%d ports=%d\n",
				ptp_drift, ptp_version, ptp_ports);
			ptp_hw = 1;
		}
		rc = 0;
		do {
			switch (rc) {
			case 1:
				rc = get_cmd(stdin);
				break;
			case 2:
				rc = 3;
				if (!ptp_hw)
					break;
				rc = get_hw_cmd(stdin);
				break;
			default:
				rc = get_acl_cmd(stdin);
				break;
			}
			if (!rc)
				break;
		} while (1);
		if (ptp_hw) {
			rc = ptp_dev_exit(&ptpdev);
			if (rc)
				print_err(rc);
		}
		for (i = 0; i < task_cnt; i++) {
			param[i].fTaskStop = TRUE;
		}
	}

	// wait for task to end
	for (i = 0; i < task_cnt; i++) {

#ifdef _SYS_SOCKET_H
		Pthread_join( tid[i], &status );

#elif defined( _WIN32 )
		rc = WaitForSingleObject( param[i].hevTaskComplete, INFINITE );
		if ( WAIT_FAILED == rc ) {

		}
		ResetEvent( param[i].hevTaskComplete );
		Sleep( 1 );

#else
		DelayMillisec( 200 );
#endif
	}

#ifdef _SYS_SOCKET_H
	if (eth_fd > 0) {
		del_multi(eth_fd, argv[1]);
		free(eth_pdelay_buf);
		free(eth_others_buf);
		closesocket(eth_fd);
	}
#endif
	closesocket(event_fd);
	closesocket(general_fd);
	if (uni_event_fd != event_fd)
		closesocket(uni_event_fd);
	if (uni_general_fd != general_fd)
		closesocket(uni_general_fd);
	if (management4_fd != general_fd)
		closesocket(management4_fd);
	SocketExit();

	return 0;
}
