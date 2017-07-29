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
#include <sys/ioctl.h>
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


typedef uint8_t u8;
typedef int16_t s16;
typedef uint16_t u16;
typedef uint32_t u32;
typedef int64_t s64;
typedef uint64_t u64;


#if defined(_MSC_VER)
#include <packon.h>
#define __packed;
#endif

#if defined(__GNUC__)
#ifndef __packed
#define __packed __attribute__((packed))
#endif
#endif


struct ptp_second {
	u16 hi;
	u32 lo;
} __packed;

struct ptp_timestamp {
	struct ptp_second sec;
	u32 nsec;
} __packed;

#define SCALED_NANOSEC_S		16
#define SCALED_NANOSEC_MULT		(1 << SCALED_NANOSEC_S)

struct ptp_correction {
	int scaled_nsec_hi;
	u32 scaled_nsec_lo;
} __packed;

struct ptp_clock_identity {
	u8 addr[8];
};

struct ptp_port_identity {
	struct ptp_clock_identity clockIdentity;
	u16 port;
} __packed;

struct ptp_port_address {
	u16 networkProtocol;
	u16 addressLength;
	u8 addressField[1];
} __packed;

struct ptp_text {
	u8 lengthField;
	u8 textField[1];
} __packed;

#define SYNC_MSG			0x0
#define DELAY_REQ_MSG			0x1
#define PDELAY_REQ_MSG			0x2
#define PDELAY_RESP_MSG			0x3
#define FOLLOW_UP_MSG			0x8
#define DELAY_RESP_MSG			0x9
#define PDELAY_RESP_FOLLOW_UP_MSG	0xA
#define ANNOUNCE_MSG			0xB
#define SIGNALING_MSG			0xC
#define MANAGEMENT_MSG			0xD

struct ptp_msg_hdr {
#ifdef __BIG_ENDIAN_BITFIELD
	u8 transportSpecific:4;
	u8 messageType:4;
	u8 reserved1:4;
	u8 versionPTP:4;
#else
	u8 messageType:4;
	u8 transportSpecific:4;
	u8 versionPTP:4;
	u8 reserved1:4;
#endif
	u16 messageLength;
	u8 domainNumber;
	u8 reserved2;
	union {
		struct {
#ifdef __BIG_ENDIAN_BITFIELD
			u8 reservedFlag7:1;
			u8 profileSpecific1:1;
			u8 profileSpecific2:1;
			u8 reservedFlag4:1;
			u8 reservedFlag3:1;
			u8 unicastFlag:1;
			u8 twoStepFlag:1;
			u8 alternateMasterFlag:1;
			u8 reservedFlag;
#else
			u8 alternateMasterFlag:1;
			u8 twoStepFlag:1;
			u8 unicastFlag:1;
			u8 reservedFlag3:1;
			u8 reservedFlag4:1;
			u8 profileSpecific1:1;
			u8 profileSpecific2:1;
			u8 reservedFlag7:1;
			u8 reservedFlag;
#endif
		} __packed flag;
		u16 data;
	} __packed flagField;
	struct ptp_correction correctionField;
	u32 reserved3;
	struct ptp_port_identity sourcePortIdentity;
	u16 sequenceId;
	u8 controlField;
	char logMessageInterval;
} __packed;

struct ptp_msg_sync {
	struct ptp_timestamp originTimestamp;
} __packed;

struct ptp_msg_follow_up {
	struct ptp_timestamp preciseOriginTimestamp;
} __packed;

struct ptp_msg_delay_resp {
	struct ptp_timestamp receiveTimestamp;
	struct ptp_port_identity requestingPortIdentity;
} __packed;

struct ptp_msg_pdelay_req {
	struct ptp_timestamp originTimestamp;
	struct ptp_port_identity reserved;
} __packed;

struct ptp_msg_pdelay_resp {
	struct ptp_timestamp requestReceiptTimestamp;
	struct ptp_port_identity requestingPortIdentity;
} __packed;

struct ptp_msg_pdelay_resp_follow_up {
	struct ptp_timestamp responseOriginTimestamp;
	struct ptp_port_identity requestingPortIdentity;
} __packed;

union ptp_msg_data {
	struct ptp_msg_sync sync;
	struct ptp_msg_follow_up follow_up;
	struct ptp_msg_delay_resp delay_resp;
	struct ptp_msg_pdelay_req pdelay_req;
	struct ptp_msg_pdelay_resp pdelay_resp;
	struct ptp_msg_pdelay_resp_follow_up pdelay_resp_follow_up;
	u8 data[8];
} __packed;

struct ptp_msg {
	struct ptp_msg_hdr hdr;
	union ptp_msg_data data;
};


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

struct llc {
	u16 len;
	u8 dsap;
	u8 ssap;
	u8 ctrl;
} __packed;

struct bridge_id {
	u16 prio;
	u8 addr[6];
} __packed;

struct bpdu {
	u16 protocol;
	u8 version;
	u8 type;
	u8 flags;
	struct bridge_id root;
	u32 root_path_cost;
	struct bridge_id bridge_id;
	u16 port_id;
	u16 message_age;
	u16 max_age;
	u16 hello_time;
	u16 forward_delay;
	u8 version_length;
} __packed;

#if defined(_MSC_VER)
#include <packoff.h>
#endif


int gWaitDelay = 100;

#define PTP_EVENT_PORT			319
#define PTP_GENERAL_PORT		320

int ip_family;
int ipv6_interface = 0;
int dbg_rcv = 0;
int ptp_proto = PTP_PROTO;

SOCKET eth_fd[4];
int rstp_ports;
char ethnames[4][20];

char devname[20];

int ptp_2step = 0;
int ptp_alternate = 0;
int ptp_unicast = 0;

#ifdef _SYS_SOCKET_H
struct sockaddr_ll eth_bpdu_addr[4];
struct sockaddr_ll eth_others_addr[4];
u8 *eth_bpdu_buf[4];
u8 *eth_others_buf[4];

u8 eth_bpdu[] = { 0x01, 0x80, 0xC2, 0x00, 0x00, 0x00 };
u8 eth_others[] = { 0x01, 0x1B, 0x19, 0x00, 0x00, 0x01 };

u8 hw_addr[ETH_ALEN];

pthread_mutex_t disp_mutex = PTHREAD_MUTEX_INITIALIZER;
#endif

u8 host_addr[16];
u8 host_addr6[16];

typedef struct {
	int fTaskStop;
	int multicast;
	int unicast;
	int management4;
	int port;
	int *msgs;

#if defined(_WIN32)
	HANDLE hevTaskComplete;
#endif
} TTaskParam, *PTTaskParam;


static struct bridge_id selfBridge;
static struct bridge_id testBridge;
static int test_port = 1;
struct ptp_clock_identity selfClockIdentity;
struct ptp_clock_identity masterClockIdentity;
static int ptp_correction;
static int ptp_domain;
static int ptp_dst_port;
static int ptp_src_port;
static int reserved3;

static u16 seqid_sync;
static u16 seqid_delay_req;
static u16 seqid_pdelay_req;
static u32 sync_sec;

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

#define BPDU_TYPE_CONFIG	0
#define BPDU_TYPE_CONFIG_RSTP	2
#define BPDU_TYPE_TCN		0x80


#define TOPOLOGY_CHANGE		(1 << 0)
#define PROPOSAL		(1 << 1)
#define PORT_ROLE_S		2
#define PORT_ROLE_ALTERNATE	1
#define PORT_ROLE_ROOT		2
#define PORT_ROLE_DESIGNATED	3
#define LEARNING		(1 << 4)
#define FORWARDING		(1 << 5)
#define AGREEMENT		(1 << 6)
#define TOPOLOGY_CHANGE_ACK	(1 << 7)


void prepare_bpdu(struct bpdu *bpdu)
{
	bpdu->protocol = 0;
	bpdu->flags = 0;
	bpdu->root.prio = htons(0x7000);
	bpdu->root.addr[0] = 0x00;
	bpdu->root.addr[1] = 0xBF;
	bpdu->root.addr[2] = 0xCB;
	bpdu->root.addr[3] = 0xFC;
	bpdu->root.addr[4] = 0xBF;
	bpdu->root.addr[5] = 0xC0;
	bpdu->root_path_cost = htonl(200000);
	bpdu->bridge_id.prio = htons(0x8000);
	bpdu->bridge_id.addr[0] = 0x00;
	bpdu->bridge_id.addr[1] = 0x10;
	bpdu->bridge_id.addr[2] = 0xA1;
	bpdu->bridge_id.addr[3] = 0xFC;
	bpdu->bridge_id.addr[4] = 0xBF;
	bpdu->bridge_id.addr[5] = 0xC0;
	bpdu->port_id = htons(0x8001);
	bpdu->message_age = htons(10 * 256);
	bpdu->max_age = htons(20 * 256);
	bpdu->hello_time = htons(2 * 256);
	bpdu->forward_delay = htons(15 * 256);
	bpdu->version_length = 0;
}

void prepare_stp(struct bpdu *bpdu)
{
	prepare_bpdu(bpdu);
	bpdu->version = 0;
	bpdu->type = BPDU_TYPE_CONFIG;
}

void prepare_rstp(struct bpdu *bpdu)
{
	prepare_bpdu(bpdu);
	bpdu->version = 2;
	bpdu->type = BPDU_TYPE_CONFIG_RSTP;
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

void prepare_msg(struct ptp_msg *msg, int message)
{
	int len;
	int logInterval;
	int seqid;
	int ctrl;
	int correction;
	struct ptp_clock_identity *clock;
	struct ptp_msg_sync *sync;
	struct ptp_msg_follow_up *follow_up;
	struct ptp_msg_delay_resp *delay_resp;
	struct ptp_msg_pdelay_req *pdelay_req;
	struct ptp_msg_pdelay_resp *pdelay_resp;
	struct ptp_msg_pdelay_resp_follow_up *pdelay_follow_up;

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
		clock = &masterClockIdentity;
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
		memcpy(&pdelay_follow_up->requestingPortIdentity.clockIdentity,
			&selfClockIdentity, sizeof(struct ptp_clock_identity));
		pdelay_follow_up->requestingPortIdentity.port = htons(1);
		clock = &masterClockIdentity;
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

void send_bpdu(int p, struct bpdu *bpdu, int len)
{
	SOCKET sockfd = eth_fd[p];
	SAI *pservaddr;
	socklen_t servlen;
	struct llc * llc;
	char *buf = (char *) bpdu;

	pservaddr = (SAI *) &eth_bpdu_addr[p];
	servlen = sizeof(eth_bpdu_addr[0]);
	buf = (char *) eth_bpdu_buf[p];
	llc = (struct llc *) &buf[12];
	memcpy(llc + 1, bpdu, len);
	len += 3;
	llc->len = htons(len);
	len += 14;
	Sendto(sockfd, buf, len, 0, (SA *) pservaddr, servlen);
}  /* send_bpdu */

void send_msg(int p, struct ptp_msg *msg, int len, u8 *src)
{
	SOCKET sockfd = eth_fd[p];
	SAI *pservaddr;
	socklen_t servlen;
	char *buf = (char *) msg;

	if (!len)
		len = ntohs(msg->hdr.messageLength);

	pservaddr = (SAI *) &eth_others_addr[p];
	servlen = sizeof(eth_others_addr[0]);
	buf = (char *) eth_others_buf[p];
	memcpy(&buf[6], src, 6);
	memcpy(&buf[14], msg, len);
	len += 14;
	Sendto(sockfd, buf, len, 0, (SA *) pservaddr, servlen);
}

void MakeRootPortConfig(int p, struct bpdu *bpdu)
{
	prepare_stp(bpdu);
	bpdu->port_id = htons(0x8002);
	send_bpdu(p, bpdu, sizeof(struct bpdu) - 1);
}

void MakeAlternatePortConfig(int p, struct bpdu *bpdu)
{
	prepare_stp(bpdu);
	bpdu->port_id = htons(0x8003);
	send_bpdu(p, bpdu, sizeof(struct bpdu) - 1);
}

void MakeRootPortBigMsgTimesConfig(int p, struct bpdu *bpdu)
{
	prepare_stp(bpdu);
	send_bpdu(p, bpdu, sizeof(struct bpdu) - 1);
}

void MakeRootPortRST(int p, struct bpdu *bpdu)
{
	prepare_rstp(bpdu);
	bpdu->flags = PROPOSAL | AGREEMENT |
		FORWARDING | LEARNING |
		PORT_ROLE_DESIGNATED << PORT_ROLE_S;
	bpdu->port_id = htons(0x8002);
	send_bpdu(p, bpdu, sizeof(struct bpdu));
}

void MakeAlternatePortRST(int p, struct bpdu *bpdu)
{
	prepare_rstp(bpdu);
	bpdu->flags = PROPOSAL | AGREEMENT |
		FORWARDING | LEARNING |
		PORT_ROLE_DESIGNATED << PORT_ROLE_S;
	bpdu->root_path_cost = htonl(200000 + ntohl(bpdu->root_path_cost));
	bpdu->bridge_id.prio = htons(0x8000);
	bpdu->bridge_id.addr[0] = 0x00;
	bpdu->bridge_id.addr[1] = 0x10;
	bpdu->bridge_id.addr[2] = 0xA1;
	bpdu->bridge_id.addr[3] = 0x01;
	bpdu->bridge_id.addr[4] = 0x00;
	bpdu->bridge_id.addr[5] = 0x02;
	bpdu->port_id = htons(0x8003);
	bpdu->message_age = htons(11 * 256);
	send_bpdu(p, bpdu, sizeof(struct bpdu));
}

void NotifyTC_RST(int p, struct bpdu *bpdu)
{
	prepare_rstp(bpdu);
	bpdu->flags = TOPOLOGY_CHANGE |
		PORT_ROLE_DESIGNATED << PORT_ROLE_S;
	bpdu->root_path_cost = htonl(600000 + ntohl(bpdu->root_path_cost));
	bpdu->bridge_id.prio = htons(0x8000);
	bpdu->bridge_id.addr[0] = 0x00;
	bpdu->bridge_id.addr[1] = 0x10;
	bpdu->bridge_id.addr[2] = 0xA1;
	bpdu->bridge_id.addr[3] = 0x02;
	bpdu->bridge_id.addr[4] = 0x00;
	bpdu->bridge_id.addr[5] = 0x02;
	bpdu->message_age = htons(12 * 256);
	send_bpdu(p, bpdu, sizeof(struct bpdu));
}

void MakeRootPortPathCostRST(int p, struct bpdu *bpdu)
{
	prepare_rstp(bpdu);
	bpdu->flags = PROPOSAL | AGREEMENT |
		FORWARDING | LEARNING |
		PORT_ROLE_DESIGNATED << PORT_ROLE_S;
	bpdu->root_path_cost = htonl(100000);
	bpdu->port_id = htons(0x8002);
	send_bpdu(p, bpdu, sizeof(struct bpdu));
}

void MakeRootPortDesignatedBridgeIDRST(int p, struct bpdu *bpdu)
{
	prepare_rstp(bpdu);
	bpdu->flags = PROPOSAL | AGREEMENT |
		FORWARDING | LEARNING |
		PORT_ROLE_DESIGNATED << PORT_ROLE_S;
	bpdu->bridge_id.prio = htons(0x8000);
	bpdu->bridge_id.addr[0] = 0x00;
	bpdu->bridge_id.addr[1] = 0x10;
	bpdu->bridge_id.addr[2] = 0xA1;
	bpdu->bridge_id.addr[3] = 0x00;
	bpdu->bridge_id.addr[4] = 0x00;
	bpdu->bridge_id.addr[5] = 0x02;
	bpdu->port_id = htons(0x8002);
	send_bpdu(p, bpdu, sizeof(struct bpdu));
}

void MakeRootPortDesignatedPortIDRST(int p, struct bpdu *bpdu)
{
	prepare_rstp(bpdu);
	bpdu->flags = PROPOSAL | AGREEMENT |
		FORWARDING | LEARNING |
		PORT_ROLE_DESIGNATED << PORT_ROLE_S;
	bpdu->port_id = htons(0x8001);
	send_bpdu(p, bpdu, sizeof(struct bpdu));
}

void MakeBackupPortIDRST(int p, struct bpdu *bpdu)
{
	prepare_rstp(bpdu);
	bpdu->flags = PROPOSAL | AGREEMENT |
		FORWARDING | LEARNING |
		PORT_ROLE_DESIGNATED << PORT_ROLE_S;
	memcpy(&bpdu->bridge_id, &testBridge, sizeof(struct bridge_id));
	bpdu->port_id = htons(0x8003);
	send_bpdu(p, bpdu, sizeof(struct bpdu));
}

void MigratePort2STP(void)
{
}

void MakeRootPortSmallMsgTimesRST(int p, struct bpdu *bpdu)
{
	prepare_rstp(bpdu);
	send_bpdu(p, bpdu, sizeof(struct bpdu));
}

void MakeRootPortHelloTimeZeroRST(int p, struct bpdu *bpdu)
{
	prepare_rstp(bpdu);
	send_bpdu(p, bpdu, sizeof(struct bpdu));
}

void MakeRootPortHelloTimeLessThanOneRST(int p, struct bpdu *bpdu)
{
	prepare_rstp(bpdu);
	send_bpdu(p, bpdu, sizeof(struct bpdu));
}

void MakeRootPortBigMsgTimesRST(int p, struct bpdu *bpdu)
{
	prepare_rstp(bpdu);
	send_bpdu(p, bpdu, sizeof(struct bpdu));
}

void MakeRootPortVeryStaleRST(int p, struct bpdu *bpdu)
{
	prepare_rstp(bpdu);
	send_bpdu(p, bpdu, sizeof(struct bpdu));
}

void MakeRootPortAlmostStaleRST(int p, struct bpdu *bpdu)
{
	prepare_rstp(bpdu);
	send_bpdu(p, bpdu, sizeof(struct bpdu));
}


void wait_sec(int sec)
{
	printf("Wait %d seconds...", sec);
	fflush(stdout);
	sleep(sec);
	printf("\n");
	fflush(stdout);
}

static int rstp_send[4];
static int rstp_type[4];
static int rstp_setting;

void wait_for_send(int p)
{
	while (rstp_send[p])
		usleep(50);
}

void RSTP_5_1(struct bpdu *bpdu, struct ptp_msg *msg)
{
	int i;
	u8 id[6];

	id[0] = 0x00;
	id[1] = 0x51;
	id[2] = 0xAA;

	printf("1: MakeRootPortConfig\n");
	printf("2: MakeAlternatePortRST\n");
	rstp_setting = 1;
	rstp_send[0] = 1;
	rstp_type[0] = 1;

	rstp_send[1] = 3;
	rstp_type[1] = 4;

	if (rstp_ports > 2) {
		printf("3: NotifyTC_RST\n");
		rstp_type[2] = 9;
	}
	fflush(stdout);
	rstp_setting = 0;
	wait_for_send(1);

	id[3] = 0x05;
	id[4] = 0x11;
	id[5] = 0x11;
	for (i = 0; i < 10; i++) {
		prepare_msg(msg, SYNC_MSG);
		send_msg(0, msg, 0, id);
	}
	id[3] = 0x06;
	id[4] = 0x22;
	id[5] = 0x22;
	for (i = 0; i < 10; i++) {
		prepare_msg(msg, SYNC_MSG);
		send_msg(1, msg, 0, id);
	}
	if (rstp_ports > 2) {
		id[3] = 0x07;
		id[4] = 0x33;
		id[5] = 0x33;
		for (i = 0; i < 10; i++) {
			prepare_msg(msg, SYNC_MSG);
			send_msg(2, msg, 0, id);
		}
	}

	rstp_type[1] = 0;
	printf("2: stop MakeAlternatePortRST\n");
	fflush(stdout);

	wait_sec(3);
	rstp_type[0] = 0;
	printf("1: stop MakeRootPortConfig\n");
	fflush(stdout);

	wait_sec(11);
	id[3] = 0x08;
	id[4] = 0x11;
	id[5] = 0x11;
	for (i = 0; i < 10; i++) {
		prepare_msg(msg, SYNC_MSG);
		send_msg(0, msg, 0, id);
	}
	id[3] = 0x09;
	id[4] = 0x22;
	id[5] = 0x22;
	for (i = 0; i < 10; i++) {
		prepare_msg(msg, SYNC_MSG);
		send_msg(1, msg, 0, id);
	}
	if (rstp_ports > 2) {
		id[3] = 0x10;
		id[4] = 0x33;
		id[5] = 0x33;
		for (i = 0; i < 10; i++) {
			prepare_msg(msg, SYNC_MSG);
			send_msg(2, msg, 0, id);
		}
	}
	wait_sec(2);
}

void RSTP_5_1_1(struct bpdu *bpdu, struct ptp_msg *msg)
{
	int i;
	u8 id[6];
	int p = 0;

	id[0] = 0x00;
	id[1] = 0x51;
	id[2] = 0xAA;
	printf("MakeRootPortConfig\n");
	fflush(stdout);
	rstp_send[p] = 3;
	rstp_type[p] = 1;
	wait_for_send(p);
	id[3] = 0x05;
	id[4] = 0x11;
	id[5] = 0x11;
	for (i = 0; i < 10; i++) {
		prepare_msg(msg, SYNC_MSG);
		send_msg(p, msg, 0, id);
	}
	wait_sec(3);
	rstp_type[p] = 0;
	printf("stop MakeRootPortConfig\n");
	fflush(stdout);
	wait_sec(11);
	id[3] = 0x08;
	id[4] = 0x11;
	id[5] = 0x11;
	for (i = 0; i < 10; i++) {
		prepare_msg(msg, SYNC_MSG);
		send_msg(p, msg, 0, id);
	}
	wait_sec(2);
}

void RSTP_5_1_2(struct bpdu *bpdu, struct ptp_msg *msg)
{
	int i;
	u8 id[6];
	int p = 1;

	id[0] = 0x00;
	id[1] = 0x51;
	id[2] = 0xAA;
	printf("MakeAlternatePortRST\n");
	fflush(stdout);
	rstp_send[p] = 3;
	rstp_type[p] = 4;
	wait_for_send(p);
	id[3] = 0x06;
	id[4] = 0x22;
	id[5] = 0x22;
	for (i = 0; i < 10; i++) {
		prepare_msg(msg, SYNC_MSG);
		send_msg(p, msg, 0, id);
	}
	rstp_type[p] = 0;
	printf("stop MakeAlternatePortRST\n");
	fflush(stdout);
	wait_sec(3);
	wait_sec(11);
	id[3] = 0x09;
	id[4] = 0x22;
	id[5] = 0x22;
	for (i = 0; i < 10; i++) {
		prepare_msg(msg, SYNC_MSG);
		send_msg(p, msg, 0, id);
	}
	wait_sec(2);
}

void RSTP_5_1_3(struct bpdu *bpdu, struct ptp_msg *msg)
{
	int i;
	u8 id[6];
	int p = 2;

	id[0] = 0x00;
	id[1] = 0x51;
	id[2] = 0xAA;
	printf("NotifyTC_RST\n");
	fflush(stdout);
	NotifyTC_RST(p, bpdu);
	sleep(3);
	id[3] = 0x07;
	id[4] = 0x33;
	id[5] = 0x33;
	for (i = 0; i < 10; i++) {
		prepare_msg(msg, SYNC_MSG);
		send_msg(p, msg, 0, id);
	}
	sleep(6);
	wait_sec(3);
	wait_sec(11);
	id[3] = 0x10;
	id[4] = 0x33;
	id[5] = 0x33;
	for (i = 0; i < 10; i++) {
		prepare_msg(msg, SYNC_MSG);
		send_msg(p, msg, 0, id);
	}
	wait_sec(2);
}

void RSTP_5_2(struct bpdu *bpdu, struct ptp_msg *msg)
{
	int i;
	u8 id[6];

	id[0] = 0x00;
	id[1] = 0x52;
	id[2] = 0xAA;

	printf("1: MakeRootPortRST\n");
	fflush(stdout);
	rstp_send[0] = 1;
	rstp_type[0] = 3;
	wait_for_send(0);

	id[3] = 0x03;
	id[4] = 0x11;
	id[5] = 0x11;
	for (i = 0; i < 10; i++) {
		prepare_msg(msg, SYNC_MSG);
		send_msg(0, msg, 0, id);
	}
	wait_sec(2);
	printf("1: MakeAlternatePortRST\n");
	printf("2: MakeRootPortRST\n");
	fflush(stdout);
	rstp_setting = 1;
	rstp_send[0] = 1;
	rstp_type[0] = 4;

	rstp_send[1] = 3;
	rstp_type[1] = 3;
	rstp_setting = 0;
	wait_for_send(1);

	id[3] = 0x06;
	id[4] = 0x11;
	id[5] = 0x11;
	for (i = 0; i < 10; i++) {
		prepare_msg(msg, SYNC_MSG);
		send_msg(0, msg, 0, id);
	}

	rstp_type[1] = 0;
	printf("2: stop MakeRootPortRST\n");
	fflush(stdout);

	wait_sec(6);
	id[3] = 0x08;
	id[4] = 0x11;
	id[5] = 0x11;
	for (i = 0; i < 10; i++) {
		prepare_msg(msg, SYNC_MSG);
		send_msg(0, msg, 0, id);
	}
	wait_sec(2);
	rstp_type[0] = 0;
}

void RSTP_5_2_1(struct bpdu *bpdu, struct ptp_msg *msg)
{
	int i;
	u8 id[6];
	int p = 0;

	id[0] = 0x00;
	id[1] = 0x52;
	id[2] = 0xAA;
	printf("MakeRootPortRST\n");
	fflush(stdout);
	rstp_send[p] = 3;
	rstp_type[p] = 3;
	wait_for_send(p);
	id[3] = 0x03;
	id[4] = 0x11;
	id[5] = 0x11;
	for (i = 0; i < 10; i++) {
		prepare_msg(msg, SYNC_MSG);
		send_msg(p, msg, 0, id);
	}
	wait_sec(2);
	printf("MakeAlternatePortRST\n");
	fflush(stdout);
	rstp_send[p] = 3;
	rstp_type[p] = 4;
	wait_for_send(p);
	id[3] = 0x06;
	id[4] = 0x11;
	id[5] = 0x11;
	for (i = 0; i < 10; i++) {
		prepare_msg(msg, SYNC_MSG);
		send_msg(p, msg, 0, id);
	}
	wait_sec(6);
	id[3] = 0x08;
	id[4] = 0x11;
	id[5] = 0x11;
	for (i = 0; i < 10; i++) {
		prepare_msg(msg, SYNC_MSG);
		send_msg(p, msg, 0, id);
	}
	wait_sec(2);
	rstp_type[p] = 0;
}

void RSTP_5_2_2(struct bpdu *bpdu, struct ptp_msg *msg)
{
	int p = 1;

#if 1
	sleep(7);
#else
	wait_sec(2);
#endif
	printf("MakeRootPortRST\n");
	fflush(stdout);
	rstp_send[p] = 3;
	rstp_type[p] = 3;
	wait_for_send(p);
	rstp_type[p] = 0;
	printf("stop MakeRootPortRST\n");
	fflush(stdout);
}

void RSTP_5_3_A_1(struct bpdu *bpdu, struct ptp_msg *msg)
{
	printf("MakeRootPortRST\n");
	fflush(stdout);
	rstp_send[0] = 2;
	rstp_type[0] = 3;
	wait_for_send(0);
	rstp_type[0] = 0;
	wait_sec(2);
}

void RSTP_5_3_B_1(struct bpdu *bpdu, struct ptp_msg *msg)
{
	printf("MakeRootPortPathCostRST\n");
	fflush(stdout);
	rstp_send[0] = 2;
	rstp_type[0] = 5;
	wait_for_send(0);
	rstp_type[0] = 0;
	wait_sec(2);
}

void RSTP_5_3_C_1(struct bpdu *bpdu, struct ptp_msg *msg)
{
	printf("MakeRootPortDesignatedBridgeIDRST\n");
	fflush(stdout);
	rstp_send[0] = 2;
	rstp_type[0] = 6;
	wait_for_send(0);
	rstp_type[0] = 0;
	wait_sec(2);
}

void RSTP_5_3_D_1(struct bpdu *bpdu, struct ptp_msg *msg)
{
	printf("MakeRootPortDesignatedPortIDRST\n");
	fflush(stdout);
	rstp_send[0] = 2;
	rstp_type[0] = 7;
	wait_for_send(0);
	rstp_type[0] = 0;
	wait_sec(2);
}

void RSTP_5_3_E_1(struct bpdu *bpdu, struct ptp_msg *msg)
{
	printf("MakeRootPortRST\n");
	fflush(stdout);
	rstp_send[0] = 2;
	rstp_type[0] = 3;
	wait_for_send(0);
	rstp_type[0] = 0;
	wait_sec(2);
}

void RSTP_5_3_A_2(struct bpdu *bpdu, struct ptp_msg *msg)
{
	sleep(4);
}

void RSTP_5_3_B_2(struct bpdu *bpdu, struct ptp_msg *msg)
{
	printf("MakeRootPortRST\n");
	fflush(stdout);
	rstp_send[1] = 2;
	rstp_type[1] = 3;
	wait_for_send(1);
	rstp_type[1] = 0;
	wait_sec(2);
}

void RSTP_5_3_C_2(struct bpdu *bpdu, struct ptp_msg *msg)
{
	printf("MakeRootPortRST\n");
	fflush(stdout);
	rstp_send[1] = 2;
	rstp_type[1] = 3;
	wait_for_send(1);
	rstp_type[1] = 0;
	wait_sec(2);
}

void RSTP_5_3_D_2(struct bpdu *bpdu, struct ptp_msg *msg)
{
	printf("MakeBackupPortIDRST\n");
	fflush(stdout);
	rstp_send[1] = 2;
	rstp_type[1] = 8;
	wait_for_send(1);
	rstp_type[1] = 0;
	wait_sec(2);
}

void RSTP_5_3_E_2(struct bpdu *bpdu, struct ptp_msg *msg)
{
	printf("MakeRootPortRST\n");
	fflush(stdout);
	rstp_send[1] = 2;
	rstp_type[1] = 3;
	wait_for_send(1);
	rstp_type[1] = 0;
	wait_sec(2);
}

void disp_msg(void *msg, int len)
{
	struct llc *llc = (struct llc *) msg;
	int msglen;

	msglen = ntohs(llc->len);
	if (msglen < 1500) {
		if (0x42 == llc->dsap &&
		    0x42 == llc->ssap &&
		    0x03 == llc->ctrl) {
			struct bpdu *bpdu = (struct bpdu *)(llc + 1);

			printf("%x %x %02x\n",
				bpdu->version,
				bpdu->type,
				bpdu->flags);
			printf("%04x %02x:%02x:%02x:%02x:%02x:%02x\n",
				ntohs(bpdu->root.prio),
				bpdu->root.addr[0],
				bpdu->root.addr[1],
				bpdu->root.addr[2],
				bpdu->root.addr[3],
				bpdu->root.addr[4],
				bpdu->root.addr[5]);
			printf("%u\n", ntohl(bpdu->root_path_cost));
			printf("%04x %02x:%02x:%02x:%02x:%02x:%02x\n",
				ntohs(bpdu->bridge_id.prio),
				bpdu->bridge_id.addr[0],
				bpdu->bridge_id.addr[1],
				bpdu->bridge_id.addr[2],
				bpdu->bridge_id.addr[3],
				bpdu->bridge_id.addr[4],
				bpdu->bridge_id.addr[5]);
			printf("%04x\n",
				ntohs(bpdu->port_id));
			printf("%04x %04x %04x %04x\n",
				ntohs(bpdu->message_age),
				ntohs(bpdu->max_age),
				ntohs(bpdu->hello_time),
				ntohs(bpdu->forward_delay));
		}
	}
}  /* disp_msg */

int get_cmd(FILE *fp)
{
	int count;
	int hcount;
	unsigned int num[8];
	unsigned int hex[8];
	int cont = 1;
	int p = 0;
	u8 id[6];
	char cmd[80];
	char line[80];
	char payload[(sizeof(struct bpdu) + 20) & ~3];
	char ptp_payload[(sizeof(struct ptp_msg) + 200) & ~3];
	struct bpdu *bpdu = (struct bpdu *) payload;
	struct ptp_msg *msg = (struct ptp_msg *) ptp_payload;

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
#if 1
			struct bridge_id id;
			struct bridge_id *bridge;

			count = sscanf(line, "%s %x:%x:%x:%x:%x:%x:%x:%x", cmd,
				&num[0], &num[1], &num[2], &num[3],
				&num[4], &num[5], &num[6], &num[7]);
			if (!strcmp(cmd, "sci"))
				bridge = &selfBridge;
			else
				bridge = &testBridge;
			if (count >= 9) {
				id.prio = (num[1] << 8) | num[0];
				for (count = 0; count < 6; count++)
					id.addr[count] = (u8) num[count + 2];
				memcpy(bridge, &id,
					sizeof(struct bridge_id));
			}
			printf("%04x-%02x:%02x:%02x:%02x:%02x:%02x\n",
				ntohs(bridge->prio),
				bridge->addr[0],
				bridge->addr[1],
				bridge->addr[2],
				bridge->addr[3],
				bridge->addr[4],
				bridge->addr[5]);
#endif
		} else
		switch (line[0]) {
#if 0
		case 'm':
			prepare_bpdu(bpdu);
			bpdu->flags = PROPOSAL |
				PORT_ROLE_ALTERNATE << PORT_ROLE_S;
			send_bpdu(bpdu, sizeof(struct bpdu));
			bpdu->flags = PROPOSAL |
				PORT_ROLE_ROOT << PORT_ROLE_S;
			send_bpdu(bpdu, sizeof(struct bpdu));
			bpdu->flags = PROPOSAL |
				PORT_ROLE_DESIGNATED << PORT_ROLE_S;
			send_bpdu(bpdu, sizeof(struct bpdu));
			bpdu->type = BPDU_TYPE_TCN;
			bpdu->flags = TOPOLOGY_CHANGE;
			send_bpdu(bpdu, 4);
			break;
		case 'n':
			prepare_msg(msg, SYNC_MSG);
			id[0] = 0x00;
			id[1] = 0x51;
			id[2] = 0xAA;
			id[3] = 0x05;
			id[4] = 0x11;
			id[5] = 0x11;
			send_msg(msg, len, id);
			prepare_msg(msg, SYNC_MSG);
			id[3] = 0x06;
			id[4] = 0x22;
			id[5] = 0x22;
			send_msg(msg, len, id);
			prepare_msg(msg, SYNC_MSG);
			id[3] = 0x07;
			id[4] = 0x33;
			id[5] = 0x33;
			send_msg(msg, len, id);
			break;
#endif
		case 'a':
			MakeRootPortRST(p, bpdu);
			break;
		case 'b':
			MakeAlternatePortRST(p, bpdu);
			break;
		case 'c':
			MakeRootPortPathCostRST(p, bpdu);
			break;
		case 'd':
			MakeRootPortDesignatedBridgeIDRST(p, bpdu);
			break;
		case 'e':
			MakeRootPortDesignatedPortIDRST(p, bpdu);
			break;
		case 'f':
			MakeBackupPortIDRST(p, bpdu);
			break;
		case 'v':
			if (rstp_ports > 1)
				RSTP_5_1(bpdu, msg);
			else if (1 == test_port)
				RSTP_5_1_1(bpdu, msg);
			else if (2 == test_port)
				RSTP_5_1_2(bpdu, msg);
			else if (3 == test_port)
				RSTP_5_1_3(bpdu, msg);
			break;
		case 'w':
			if (rstp_ports > 1)
				RSTP_5_2(bpdu, msg);
			else if (1 == test_port)
				RSTP_5_2_1(bpdu, msg);
			else if (2 == test_port)
				RSTP_5_2_2(bpdu, msg);
			break;
		case 'j':
			if (1 == test_port)
				RSTP_5_3_A_1(bpdu, msg);
			else if (2 == test_port)
				RSTP_5_3_A_2(bpdu, msg);
			break;
		case 'k':
			if (1 == test_port)
				RSTP_5_3_B_1(bpdu, msg);
			else if (2 == test_port)
				RSTP_5_3_B_2(bpdu, msg);
			break;
		case 'l':
			if (1 == test_port)
				RSTP_5_3_C_1(bpdu, msg);
			else if (2 == test_port)
				RSTP_5_3_C_2(bpdu, msg);
			break;
		case 'm':
			if (1 == test_port)
				RSTP_5_3_D_1(bpdu, msg);
			else if (2 == test_port)
				RSTP_5_3_D_2(bpdu, msg);
			break;
		case 'n':
			if (1 == test_port)
				RSTP_5_3_E_1(bpdu, msg);
			else if (2 == test_port)
				RSTP_5_3_E_2(bpdu, msg);
			break;
		case 't':
			NotifyTC_RST(p, bpdu);
			break;
		case 's':
			id[0] = 0x00;
			id[1] = 0x51;
			id[2] = 0xAA;
			id[3] = 0x05;
			id[4] = 0x11;
			id[5] = 0x11;
			prepare_msg(msg, SYNC_MSG);
			send_msg(p, msg, 0, id);
			break;
		case 'p':
			if (count >= 2) {
				test_port = num[0];
				if (1 <= test_port && test_port <= rstp_ports)
					p = test_port - 1;
			} else
				printf("%d\n", test_port);
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

struct sock_buf {
	struct sockaddr *from;
	u8 *buf;
	int len;
};

static int check_loop(struct sockaddr *sa, int salen, int port)
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
		if (addr->sll_ifindex != eth_bpdu_addr[port].sll_ifindex)
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
	struct bpdu *bpdu;
	int i;
	char in_addr[80];
	int cur;
	int last;
	int nsel;
	int looped;
	int msglen;

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
				printf("r: %d=%d %d=%s  ", sockfd,
					buf[cur].len, len, in_addr);
			msglen = buf[cur].len;
#ifdef _SYS_SOCKET_H
			if (AF_PACKET == buf[cur].from->sa_family) {
				bpdu = (struct bpdu *) &buf[cur].buf[14];
				msglen -= 14;
			} else
#endif
				bpdu = (struct bpdu *) buf[cur].buf;
			looped = check_loop(buf[cur].from, len,
				pTaskParam->port);
			if (looped) {
				int ignored = 1;

				if (1 == looped)
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
				if (dbg_rcv >= 4) {
					if (looped)
						printf("(looped)\n");
					else
						printf("\n");
				}
				cur = !cur;
				last = !last;
			}
			if (dbg_rcv)
				disp_msg(bpdu, msglen);
			if (dbg_rcv)
				Pthread_mutex_unlock(&disp_mutex);
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

#ifdef _SYS_SOCKET_H
void *

#else
void
#endif
TransmitTask(void *param)
{
	PTTaskParam pTaskParam;
	char payload[(sizeof(struct bpdu) + 20) & ~3];
	struct bpdu *bpdu = (struct bpdu *) payload;
	int p;

	pTaskParam = (PTTaskParam) param;
	FOREVER {
		if ( pTaskParam->fTaskStop ) {
			break;
		}

		sleep(2);
		if (rstp_setting)
			continue;
		for (p = 0; p < rstp_ports; p++) {
			switch (rstp_type[p]) {
			case 1:
				MakeRootPortConfig(p, bpdu);
				break;
			case 3:
				MakeRootPortRST(p, bpdu);
				break;
			case 4:
				MakeAlternatePortRST(p, bpdu);
				break;
			case 5:
				MakeRootPortPathCostRST(p, bpdu);
				break;
			case 6:
				MakeRootPortDesignatedBridgeIDRST(p, bpdu);
				break;
			case 7:
				MakeRootPortDesignatedPortIDRST(p, bpdu);
				break;
			case 8:
				MakeBackupPortIDRST(p, bpdu);
				break;
			case 9:
				NotifyTC_RST(p, bpdu);
				rstp_type[p] = 0;
				break;
			}
			if (rstp_send[p])
				--rstp_send[p];
		}
	}
	pTaskParam->fTaskStop = TRUE;

#ifdef _WIN32
	SetEvent( pTaskParam->hevTaskComplete );
#endif

#ifdef _SYS_SOCKET_H
	return NULL;
#endif
}  /* TransmitTask */

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
	fscanf(f, "%x", &num[0]);
	fclose(f);

	sprintf(path, "%s%s/%s", _PATH_SYSNET_DEV, devname, NETDEV_OPERSTATE);
	f = fopen(path, "r");
	if (!f)
		goto get_dev_addr;
	fscanf(f, "%s", file);
	fclose(f);
	if ((!strcmp(file, "up") && !(num[0] & IFF_UP)) ||
	    (!strcmp(file, "down") && (num[0] & IFF_UP)))
		printf(" ? %s 0x%04x\n", file, num[0]);

	/* Device not running. */
	if (!(num[0] & IFF_UP))
		goto get_dev_done;

	found = TRUE;

get_dev_addr:
	sprintf(path, "%s%s/%s", _PATH_SYSNET_DEV, devname, NETDEV_IFINDEX);
	f = fopen(path, "r");
	if (f) {
		fscanf(f, "%u", &num[0]);
		fclose(f);
		if (!found)
			info->if_idx = num[0];
		else if (info->if_idx != num[0])
			printf(" ? %d %d\n", info->if_idx, num[0]);
	}

	sprintf(path, "%s%s/%s", _PATH_SYSNET_DEV, devname, NETDEV_ADDRESS);
	f = fopen(path, "r");
	if (!f)
		goto get_dev_done;
	fscanf(f, "%x:%x:%x:%x:%x:%x",
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
	memcpy(ifr.ifr_hwaddr.sa_data, eth_bpdu, ETH_ALEN);
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
	memcpy(ifr.ifr_hwaddr.sa_data, eth_bpdu, ETH_ALEN);
	rc = ioctl(sockfd, SIOCDELMULTI, &ifr);
	if (eth_others[0]) {
		memcpy(ifr.ifr_hwaddr.sa_data, eth_others, ETH_ALEN);
		rc = ioctl(sockfd, SIOCDELMULTI, &ifr);
	}
}

static SOCKET create_raw(struct ip_info *info, char *dest, int p)
{
	SOCKET sockfd;
	struct ethhdr *eh;
	struct llc *llc;
	int addr[ETH_ALEN];
	int cnt;

	sockfd = Socket(AF_PACKET, SOCK_RAW, htons(ptp_proto));
	if (sockfd < 0)
		return sockfd;

	cnt = sscanf(dest, "%x:%x:%x:%x:%x:%x",
		&addr[0], &addr[1], &addr[2], &addr[3], &addr[4], &addr[5]);
	eth_bpdu_addr[p].sll_family = PF_PACKET;
	eth_bpdu_addr[p].sll_protocol = htons(ptp_proto);
	eth_bpdu_addr[p].sll_ifindex = info->if_idx + p;
	eth_bpdu_addr[p].sll_hatype = ARPHRD_ETHER;
	eth_bpdu_addr[p].sll_halen = ETH_ALEN;
	if (ETH_ALEN == cnt) {
		eth_bpdu_addr[p].sll_pkttype = PACKET_OTHERHOST;
		eth_bpdu_addr[p].sll_addr[0] = (u8) addr[0];
		eth_bpdu_addr[p].sll_addr[1] = (u8) addr[1];
		eth_bpdu_addr[p].sll_addr[2] = (u8) addr[2];
		eth_bpdu_addr[p].sll_addr[3] = (u8) addr[3];
		eth_bpdu_addr[p].sll_addr[4] = (u8) addr[4];
		eth_bpdu_addr[p].sll_addr[5] = (u8) addr[5];
	} else {
		eth_bpdu_addr[p].sll_pkttype = PACKET_MULTICAST;
		memcpy(eth_bpdu_addr[p].sll_addr, eth_bpdu, ETH_ALEN);
	}
	eth_bpdu_addr[p].sll_addr[6] = 0x00;
	eth_bpdu_addr[p].sll_addr[7] = 0x00;
	eth_others_addr[p].sll_family = PF_PACKET;
	eth_others_addr[p].sll_protocol = htons(ptp_proto);
	eth_others_addr[p].sll_ifindex = info->if_idx + p;
	eth_others_addr[p].sll_hatype = ARPHRD_ETHER;
	eth_others_addr[p].sll_halen = ETH_ALEN;
	if (ETH_ALEN == cnt) {
		eth_others_addr[p].sll_pkttype = PACKET_OTHERHOST;
		eth_others_addr[p].sll_addr[0] = (u8) addr[0];
		eth_others_addr[p].sll_addr[1] = (u8) addr[1];
		eth_others_addr[p].sll_addr[2] = (u8) addr[2];
		eth_others_addr[p].sll_addr[3] = (u8) addr[3];
		eth_others_addr[p].sll_addr[4] = (u8) addr[4];
		eth_others_addr[p].sll_addr[5] = (u8) addr[5];
	} else {
		eth_others_addr[p].sll_pkttype = PACKET_MULTICAST;
		if (eth_others[0])
			memcpy(eth_others_addr[p].sll_addr, eth_others,
				ETH_ALEN);
		else
			memcpy(eth_others_addr[p].sll_addr, eth_bpdu,
				ETH_ALEN);
	}
	eth_others_addr[p].sll_addr[6] = 0x00;
	eth_others_addr[p].sll_addr[7] = 0x00;

	eth_bpdu_buf[p] = malloc(1518);
	eth_others_buf[p] = malloc(1518);
	memcpy(eth_bpdu_buf[p], eth_bpdu_addr[p].sll_addr, ETH_ALEN);
	memcpy(&eth_bpdu_buf[p][ETH_ALEN], info->hwaddr, ETH_ALEN);
	eh = (struct ethhdr *) eth_bpdu_buf[p];
	eh->h_proto = htons(ptp_proto);
	llc = (struct llc *) &eth_bpdu_buf[p][12];
	llc->dsap = 0x42;
	llc->ssap = 0x42;
	llc->ctrl = 0x03;
	memcpy(eth_others_buf[p], eth_others_addr[p].sll_addr, ETH_ALEN);
	memcpy(&eth_others_buf[p][ETH_ALEN], info->hwaddr, ETH_ALEN);
	eh = (struct ethhdr *) eth_others_buf[p];
	eh->h_proto = htons(ptp_proto);

	return sockfd;
}
#endif

int main(int argc, char *argv[])
{
	TTaskParam param[4];

#ifdef _SYS_SOCKET_H
	pthread_t tid[4];
	pthread_t tidT[4];
	void *status;

#elif defined( _WIN32 )
	DWORD rc;
#endif
	char dest_ip[40];
	char host_ip4[40];
	char host_ip6[40];
	char *host_ip;
	int family;
	int i;
	int p;
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
	family = AF_PACKET;
	dbg_rcv = 5;
	rstp_ports = 1;
	dest_ip[0] = '\0';
	if (argc > 2) {
		i = 2;
		while (i < argc) {
			if ('-' == argv[i][0]) {
				switch (argv[i][1]) {
				case 'p':
					if ('0' <= argv[i][2] &&
					    argv[i][2] <= '9')
						rstp_ports = argv[i][2] - '0';
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
				}
			}
			++i;
		}
	}
	strncpy(devname, argv[1], sizeof(devname));
	host_ip = strchr(devname, '.');
	if (host_ip != NULL)
		*host_ip = 0;
	strncpy(ethnames[0], argv[1], 20);
	if (rstp_ports > 1) {
		int len = strlen(ethnames[0]);

		for (p = 1; p < rstp_ports; p++) {
			strncpy(ethnames[p], ethnames[0], 20);
			ethnames[p][len - 1] += p;
		}
	}

	testBridge.prio = htons(0x8000);
	testBridge.addr[0] = 0x00;
	testBridge.addr[1] = 0x10;
	testBridge.addr[2] = 0xA1;
	testBridge.addr[3] = 0x00;
	testBridge.addr[4] = 0x00;
	testBridge.addr[5] = 0x01;

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
		memcpy(hw_addr, info.hwaddr, ETH_ALEN);
		selfBridge.prio = htons(0x8000);
		memcpy(&selfBridge.addr[0], info.hwaddr, 6);
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
		selfBridge.prio = htons(0x8000);
		memcpy(&selfBridge.addr[0], info.hwaddr, 6);
#endif
	} else {
		printf("cannot locate IP address\n");
		exit(1);
	}

	ip_family = family;

	for (p = 0; p < rstp_ports; p++) {
		eth_fd[p] = create_raw(&info, dest_ip, p);
		if (eth_fd[p] < 0) {
			printf("Cannot create socket\n");
			return 1;
		}
		add_multi(eth_fd[p], ethnames[p]);
	}

	for (i = 0; i < rstp_ports; i++) {
		param[i].fTaskStop = FALSE;
		param[i].multicast = eth_fd[i];
		param[i].unicast = 0;
		param[i].management4 = 0;
		param[i].port = i;

		Pthread_create(&tid[i], NULL, ReceiveTask, &param[i]);
	}
	Pthread_create(&tidT[0], NULL, TransmitTask, &param[0]);

	if ( !param[0].fTaskStop ) {
		do {
			if (!get_cmd(stdin))
				break;
		} while (1);
		for (i = 0; i < rstp_ports; i++) {
			param[i].fTaskStop = TRUE;
		}
	}

	// wait for task to end
	for (i = 0; i < rstp_ports; i++) {
		Pthread_join( tid[i], &status );
	}
	Pthread_join( tidT[0], &status );

	for (p = 0; p < rstp_ports; p++) {
		if (eth_fd[p] > 0) {
			del_multi(eth_fd[p], ethnames[p]);
			free(eth_bpdu_buf[p]);
			free(eth_others_buf[p]);
			closesocket(eth_fd[p]);
		}
	}
	SocketExit();

	return 0;
}
