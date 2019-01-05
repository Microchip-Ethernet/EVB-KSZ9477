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


#include "ksz_req.h"
#include "ksz_ptp.h"


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

struct _bridge_id {
	u16 prio;
	u8 addr[6];
} __packed;

struct _port_id {
	u8 prio;
	u8 num;
} __packed;

struct bpdu {
	u16 protocol;
	u8 version;
	u8 type;
	u8 flags;
	struct _bridge_id root;
	u32 root_path_cost;
	struct _bridge_id bridge_id;
	struct _port_id port_id;
	u16 message_age;
	u16 max_age;
	u16 hello_time;
	u16 forward_delay;
	u8 version_length;
} __packed;

#if defined(_MSC_VER)
#include <packoff.h>
#endif


#define NUM_OF_PORTS			4


int gWaitDelay = 100;

#define PTP_EVENT_PORT			319
#define PTP_GENERAL_PORT		320

int ip_family;
int ipv6_interface = 0;
int dbg_rcv = 0;
int ptp_proto = PTP_PROTO;
int eth_ucast;
int eth_vlan;

SOCKET eth_fd[NUM_OF_PORTS];
SOCKET stp_fd[NUM_OF_PORTS];
int rstp_ports;
char ethnames[NUM_OF_PORTS][20];

char devname[20];

int ptp_2step = 0;
int ptp_alternate = 0;
int ptp_unicast = 0;

#ifdef _SYS_SOCKET_H
struct sockaddr_ll eth_bpdu_addr[NUM_OF_PORTS];
struct sockaddr_ll eth_others_addr[NUM_OF_PORTS];
struct sockaddr_ll eth_ucast_addr[NUM_OF_PORTS];
u8 *eth_bpdu_buf[NUM_OF_PORTS];
u8 *eth_others_buf[NUM_OF_PORTS];
u8 *eth_ucast_buf[NUM_OF_PORTS];

u8 eth_bpdu[] = { 0x01, 0x80, 0xC2, 0x00, 0x00, 0x00 };
u8 eth_others[] = { 0x01, 0x1B, 0x19, 0x00, 0x00, 0x01 };

u8 hw_addr[ETH_ALEN];

pthread_mutex_t disp_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t sec_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t tx_mutex = PTHREAD_MUTEX_INITIALIZER;

void pthread_cond_init_(pthread_cond_t *cond)
{
	pthread_cond_init(cond, NULL);
}

void pthread_mutex_init_(pthread_mutex_t *mutex)
{
	pthread_mutexattr_t attr;

	pthread_mutexattr_init(&attr);
	pthread_mutex_init(mutex, &attr);
}

struct thread_info {
	pthread_cond_t  cond;
	pthread_mutex_t mutex;
};

int rx_wait[NUM_OF_PORTS];
struct thread_info rx_thread[NUM_OF_PORTS];
struct thread_info tx_done_thread;
struct thread_info tx_job_thread;
struct thread_info tx_next_thread;
struct thread_info tx_periodic_thread;

static void signal_update(struct thread_info *pthread, int *signal, int val)
{
	Pthread_mutex_lock(&pthread->mutex);
	if (signal)
		*signal = val;
	pthread_cond_signal(&pthread->cond);
	Pthread_mutex_unlock(&pthread->mutex);
}

static void signal_wait_(struct thread_info *pthread, int cond,
	struct timespec *ts)
{
	int n;

	Pthread_mutex_lock(&pthread->mutex);
	if (!cond)
		n = pthread_cond_timedwait(&pthread->cond,
			&pthread->mutex, ts);
	Pthread_mutex_unlock(&pthread->mutex);
}

static void signal_long_wait(struct thread_info *pthread, int cond)
{
	struct timeb tb;
	struct timespec ts;
	int n;

	ftime(&tb);
	ts.tv_sec = tb.time;
	ts.tv_nsec = (tb.millitm + 100 - 10) * 1000 * 1000;
	if (ts.tv_nsec >= 1000000000) {
		ts.tv_nsec -= 1000000000;
		ts.tv_sec++;
	}
	ts.tv_sec += 2;

	signal_wait_(pthread, cond, &ts);
}

static void signal_wait(struct thread_info *pthread, int cond)
{
	struct timeb tb;
	struct timespec ts;
	int n;

	ftime(&tb);
	ts.tv_sec = tb.time;
	ts.tv_nsec = (tb.millitm + 100 - 10) * 1000 * 1000;
	if (ts.tv_nsec >= 1000000000) {
		ts.tv_nsec -= 1000000000;
		ts.tv_sec++;
	}

	signal_wait_(pthread, cond, &ts);
}

static void signal_init(struct thread_info *pthread)
{
	pthread_cond_init_(&pthread->cond);
	pthread_mutex_init_(&pthread->mutex);
}
#endif

u8 host_addr[16];
u8 host_addr6[16];

struct rx_param {
	int *bpdu;
	int *others;
	int cnt;
};

typedef struct {
	int fTaskStop;
	void *param;

#if defined(_WIN32)
	HANDLE hevTaskComplete;
#endif
} TTaskParam, *PTTaskParam;


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

#define NUM_OF_ADDR			6

static u8 rx_addr[NUM_OF_ADDR][6];
static int rx_num[NUM_OF_ADDR][NUM_OF_PORTS];
static int rx_cnt;

static struct _bridge_id root_bridge;
static struct _bridge_id rx_desg_bridge;
static struct _bridge_id rx_root_bridge;
static struct _bridge_id bridges[NUM_OF_PORTS];
static struct _bridge_id *bridge_id = &bridges[0];
static u16 port_id = 1;
static uint root_path_cost;
static uint rx_root_path_cost;
static u8 ts_addr[NUM_OF_PORTS][6];
static int path_cost_dec;
static int tx_delay;


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
	memcpy(&bpdu->root, &root_bridge, sizeof(struct _bridge_id));
	bpdu->root_path_cost = htonl(root_path_cost);
	memcpy(&bpdu->bridge_id, bridge_id, sizeof(struct _bridge_id));
	bpdu->port_id.prio = 0x80;
	bpdu->port_id.num = port_id;
	bpdu->message_age = htons(1 * 256);
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

void prepare_tcn(struct bpdu *bpdu)
{
	prepare_bpdu(bpdu);
	bpdu->version = 0;
	bpdu->type = BPDU_TYPE_TCN;
}

void prepare_rstp(struct bpdu *bpdu)
{
	prepare_bpdu(bpdu);
	bpdu->version = 2;
	bpdu->type = BPDU_TYPE_CONFIG_RSTP;
}

static void disp_bpdu(struct bpdu *bpdu)
{
	u8 role;

	if (BPDU_TYPE_TCN != bpdu->type) {
		printf("%04x=%02x%02x%02x%02x%02x%02x "
			"%04x=%02x%02x%02x%02x%02x%02x:"
			"%02x%02x %u\n",
			ntohs(bpdu->root.prio),
			bpdu->root.addr[0],
			bpdu->root.addr[1],
			bpdu->root.addr[2],
			bpdu->root.addr[3],
			bpdu->root.addr[4],
			bpdu->root.addr[5],
			ntohs(bpdu->bridge_id.prio),
			bpdu->bridge_id.addr[0],
			bpdu->bridge_id.addr[1],
			bpdu->bridge_id.addr[2],
			bpdu->bridge_id.addr[3],
			bpdu->bridge_id.addr[4],
			bpdu->bridge_id.addr[5],
			bpdu->port_id.prio, bpdu->port_id.num,
			ntohl(bpdu->root_path_cost));
		printf("%u %u %u %u  ",
			htons(bpdu->message_age) / 256,
			htons(bpdu->max_age) / 256,
			htons(bpdu->hello_time) / 256,
			htons(bpdu->forward_delay) / 256);
		printf("%02X:", bpdu->flags);
		if (bpdu->flags & TOPOLOGY_CHANGE_ACK)
			printf("K");
		else
			printf("-");
		if (bpdu->flags & AGREEMENT)
			printf("A");
		else
			printf("-");
		if (bpdu->flags & FORWARDING)
			printf("F");
		else
			printf("-");
		if (bpdu->flags & LEARNING)
			printf("L");
		else
			printf("-");
		role = bpdu->flags >> PORT_ROLE_S;
		role &= PORT_ROLE_DESIGNATED;
		switch (role) {
		case PORT_ROLE_ALTERNATE:
			printf("N");
			break;
		case PORT_ROLE_ROOT:
			printf("R");
			break;
		case PORT_ROLE_DESIGNATED:
			printf("D");
			break;
		default:
			if (BPDU_TYPE_CONFIG_RSTP == bpdu->type)
				printf("?");
			else
				printf("-");
		}
		if (bpdu->flags & PROPOSAL)
			printf("P");
		else
			printf("-");
		if (bpdu->flags & TOPOLOGY_CHANGE)
			printf("T");
		else
			printf("-");
	}
	printf("  %04x %u %02x",
		htons(bpdu->protocol),
		bpdu->version, bpdu->type);
	if (BPDU_TYPE_CONFIG_RSTP == bpdu->type)
		printf(" %u", bpdu->version_length);
	printf("\n");
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

enum {
	FRAME_unknown,
	FRAME_untagged,
	BPDU_RootAgreementRST,
	BPDU_MakeRootPortConfig,
	BPDU_MakeRootPortBigMsgTimesConfig,
	BPDU_MakeRootPortStaleConfig,
	BPDU_MakeRootPortVeryStaleConfig,
	BPDU_MakeRootPortBadProtocolIdConfig,
	BPDU_MakeRootPortTooFewOctetsConfig,
	BPDU_MakeAlternatePortConfig,
	BPDU_MakeRootPortRST,
	BPDU_MakeRootPortRST_1,
	BPDU_MakeRootPortRST_2,
	BPDU_MakeRootPortNextProposingRST,
	BPDU_MakeRootPortProposingRST,
	BPDU_MakeRootPortBigMsgTimesRST,
	BPDU_MakeRootPortSmallMsgTimesRST,
	BPDU_MakeRootPortBadMsgTimesRST,
	BPDU_MakeRootPortStaleRST,
	BPDU_MakeRootPortVeryStaleRST,
	BPDU_MakeRootPortAlmostStaleRST,
	BPDU_MakeRootPortBadProtocolIdRST,
	BPDU_MakeRootPortTooFewOctetsRST,
	BPDU_MakeRootPortHelloTimeZeroRST,
	BPDU_MakeRootPortHelloTimeLessThanOneRST,
	BPDU_MakeAlternatePortRST,
	BPDU_MakeAlternatePortRST_1,
	BPDU_MakeAlternatePortRST_2,
	BPDU_MakeRootPortPathCostRST,
	BPDU_MakeRootPortDesignatedBridgeIDRST,
	BPDU_MakeRootPortDesignatedPortIDRST,
	BPDU_MakeBackupPortRST,
	BPDU_MakeBackupPortRST_1,
	BPDU_MakeBackupPortIDRST,
	BPDU_MigratePort2STP,
	BPDU_MigratePort2RSTP,
	BPDU_NotifyTC_RST,
	BPDU_BadProtocolId_TCN_BPDU,
};

struct tx_job_type {
	int port;
	int type;
	int cnt;
	u16 vid;
	uint sec;
};

static int disp_pkt[NUM_OF_PORTS];

#define MAX_TX_JOB_CNT			8
#define MAX_TX_CONT_JOB_CNT		4

static int tx_job_cnt;
static int tx_cont_job_cnt;
static int tx_job_running;
static struct tx_job_type tx_jobs[MAX_TX_JOB_CNT];
static struct tx_job_type tx_cont_jobs[MAX_TX_CONT_JOB_CNT];

static void add_tx_job(int port, int type, int cnt)
{
	struct tx_job_type *tx_job;

	Pthread_mutex_lock(&tx_mutex);
	if (cnt) {
		if (MAX_TX_JOB_CNT == tx_job_cnt)
printf(" ??\n");
		if (MAX_TX_JOB_CNT == tx_job_cnt)
			goto done;
		tx_job = &tx_jobs[tx_job_cnt++];
		tx_job->port = port;
		tx_job->type = type;
		tx_job->cnt = cnt;

		/* periodic */
		if (tx_job->cnt < 0) {
			if (MAX_TX_CONT_JOB_CNT == tx_cont_job_cnt)
printf(" ???\n");
			if (MAX_TX_CONT_JOB_CNT == tx_cont_job_cnt)
				goto done;
			memcpy(&tx_cont_jobs[tx_cont_job_cnt], tx_job,
				sizeof(struct tx_job_type));
			tx_cont_job_cnt++;
			tx_job->cnt = 1;
		}
	} else {
		int n;

		for (n = 0; n < tx_cont_job_cnt; n++) {
			tx_job = &tx_cont_jobs[n];
			if (tx_job->cnt &&
			    tx_job->port == port &&
			    tx_job->type == type)
				tx_job->cnt = 0;
		}
	}

done:
	Pthread_mutex_unlock(&tx_mutex);
}

static int get_packet_type(char *name)
{
	if (!strcmp(name, "untagged"))
		return FRAME_untagged;
	else if (!strcmp(name, "RootAgreementRST"))
		return BPDU_RootAgreementRST;
	else if (!strcmp(name, "MakeRootPortConfig"))
		return BPDU_MakeRootPortConfig;
	else if (!strcmp(name, "MakeRootPortBigMsgTimesConfig"))
		return BPDU_MakeRootPortBigMsgTimesConfig;
	else if (!strcmp(name, "MakeRootPortStaleConfig"))
		return BPDU_MakeRootPortStaleConfig;
	else if (!strcmp(name, "MakeRootPortVeryStaleConfig"))
		return BPDU_MakeRootPortVeryStaleConfig;
	else if (!strcmp(name, "MakeRootPortBadProtocolIdConfig"))
		return BPDU_MakeRootPortBadProtocolIdConfig;
	else if (!strcmp(name, "MakeRootPortTooFewOctetsConfig"))
		return BPDU_MakeRootPortTooFewOctetsConfig;
	else if (!strcmp(name, "MakeAlternatePortConfig"))
		return BPDU_MakeAlternatePortConfig;
	else if (!strcmp(name, "MakeRootPortRST"))
		return BPDU_MakeRootPortRST;
	else if (!strcmp(name, "MakeRootPortRST_1"))
		return BPDU_MakeRootPortRST_1;
	else if (!strcmp(name, "MakeRootPortRST_2"))
		return BPDU_MakeRootPortRST_2;
	else if (!strcmp(name, "MakeRootPortNextProposingRST"))
		return BPDU_MakeRootPortNextProposingRST;
	else if (!strcmp(name, "MakeRootPortProposingRST"))
		return BPDU_MakeRootPortProposingRST;
	else if (!strcmp(name, "MakeRootPortBigMsgTimesRST"))
		return BPDU_MakeRootPortBigMsgTimesRST;
	else if (!strcmp(name, "MakeRootPortSmallMsgTimesRST"))
		return BPDU_MakeRootPortSmallMsgTimesRST;
	else if (!strcmp(name, "MakeRootPortBadMsgTimesRST"))
		return BPDU_MakeRootPortBadMsgTimesRST;
	else if (!strcmp(name, "MakeRootPortStaleRST"))
		return BPDU_MakeRootPortStaleRST;
	else if (!strcmp(name, "MakeRootPortVeryStaleRST"))
		return BPDU_MakeRootPortVeryStaleRST;
	else if (!strcmp(name, "MakeRootPortAlmostStaleRST"))
		return BPDU_MakeRootPortAlmostStaleRST;
	else if (!strcmp(name, "MakeRootPortBadProtocolIdRST"))
		return BPDU_MakeRootPortBadProtocolIdRST;
	else if (!strcmp(name, "MakeRootPortTooFewOctetsRST"))
		return BPDU_MakeRootPortTooFewOctetsRST;
	else if (!strcmp(name, "MakeRootPortHelloTimeZeroRST"))
		return BPDU_MakeRootPortHelloTimeZeroRST;
	else if (!strcmp(name, "MakeRootPortHelloTimeLessThanOneRST"))
		return BPDU_MakeRootPortHelloTimeLessThanOneRST;
	else if (!strcmp(name, "MakeAlternatePortRST"))
		return BPDU_MakeAlternatePortRST;
	else if (!strcmp(name, "MakeAlternatePortRST_1"))
		return BPDU_MakeAlternatePortRST_1;
	else if (!strcmp(name, "MakeAlternatePortRST_2"))
		return BPDU_MakeAlternatePortRST_2;
	else if (!strcmp(name, "MakeRootPortPathCostRST"))
		return BPDU_MakeRootPortPathCostRST;
	else if (!strcmp(name, "MakeRootPortDesignatedBridgeIDRST"))
		return BPDU_MakeRootPortDesignatedBridgeIDRST;
	else if (!strcmp(name, "MakeRootPortDesignatedPortIDRST"))
		return BPDU_MakeRootPortDesignatedPortIDRST;
	else if (!strcmp(name, "MakeBackupPortRST"))
		return BPDU_MakeBackupPortRST;
	else if (!strcmp(name, "MakeBackupPortRST_1"))
		return BPDU_MakeBackupPortRST_1;
	else if (!strcmp(name, "MakeBackupPortIDRST"))
		return BPDU_MakeBackupPortIDRST;
	else if (!strcmp(name, "MigratePort2STP"))
		return BPDU_MigratePort2STP;
	else if (!strcmp(name, "MigratePort2RSTP"))
		return BPDU_MigratePort2RSTP;
	else if (!strcmp(name, "NotifyTC_RST"))
		return BPDU_NotifyTC_RST;
	else if (!strcmp(name, "BadProtocolId_TCN_BPDU"))
		return BPDU_BadProtocolId_TCN_BPDU;
	return FRAME_unknown;
}

struct job_info {
	int cmd;
	int sec;
	struct tx_job_type tx_job;
	u8 addr[6];
};

#define MAX_JOB_CNT			60

static struct job_info jobs[MAX_JOB_CNT];
static int job_cnt;

int get_ts_port(char *ts_name)
{
	int p;

	if ('T' != ts_name[0] || 'S' != ts_name[1])
		return -1;
	p = ts_name[2] - '1';
	if (0 <= p && p < rstp_ports)
		return p;
	return -1;
}

static void parse_file(FILE *ifp)
{
	char line[80];
	char ts_name[20];
	char cmd[10];
	char type[40];
	int cnt;
	int n;
	int p;
	int num[6];
	int vid;
	struct job_info *job;

	job_cnt = 0;
	rx_cnt = 0;
	while (fgets(line, 80, ifp)) {
		vid = 0;
		cmd[0] = '\0';
		n = sscanf(line, "%s %d %s %s %u\n",
			cmd, &cnt, ts_name, type, &vid);
		if (!n)
			continue;
		if ('#' == cmd[0])
			continue;
		if (MAX_JOB_CNT == job_cnt)
printf("  !!\n");
		if (MAX_JOB_CNT == job_cnt)
			break;
		job = &jobs[job_cnt];
		switch (cmd[0]) {
		case 'r':
			p = get_ts_port(ts_name);
			if (p < 0)
				break;
			job->cmd = 4;
			job->tx_job.port = p;
			job->tx_job.cnt = cnt;
			job_cnt++;
			break;
		case 't':
			p = get_ts_port(ts_name);
			if (p < 0)
				break;
			job->cmd = 1;
			job->tx_job.port = p;
			job->tx_job.type = get_packet_type(type);
			job->tx_job.vid = (u16) vid;
			job->tx_job.cnt = cnt;
			job_cnt++;
			break;
		case 'w':
			job->cmd = 2;
			job->sec = cnt;
			if (cnt < 0) {
				p = get_ts_port(ts_name);
				if (p < 0)
					break;
				job->tx_job.port = p;
			}
			job_cnt++;
			break;
		case 's':
			p = get_ts_port(ts_name);
			if (p < 0)
				break;
			n = sscanf(type, "%02x-%02x-%02x-%02x-%02x-%02x",
				&num[0],
				&num[1],
				&num[2],
				&num[3],
				&num[4],
				&num[5]);
			if (6 == n) {
				job->cmd = 3;
				job->tx_job.port = p;
				for (n = 0; n < 6; n++)
					job->addr[n] = (u8) num[n];
				job_cnt++;
			}
			break;
		case 'v':
			p = get_ts_port(ts_name);
			if (p < 0)
				break;
			n = sscanf(type, "%02x-%02x-%02x-%02x-%02x-%02x",
				&num[0],
				&num[1],
				&num[2],
				&num[3],
				&num[4],
				&num[5]);
			if (6 == n) {
				job->cmd = 6;
				job->tx_job.port = p;
				job->tx_job.cnt = cnt;
				for (n = 0; n < 6; n++)
					job->addr[n] = (u8) num[n];
				job_cnt++;
			}
			break;
		case 'c':
			job->cmd = 5;
			job->sec = cnt;
			job_cnt++;
			break;
		case 'd':
			p = get_ts_port(ts_name);
			if (p < 0)
				break;
			n = sscanf(type, "%02x-%02x-%02x-%02x-%02x-%02x",
				&num[0],
				&num[1],
				&num[2],
				&num[3],
				&num[4],
				&num[5]);
			if (6 == n) {
				job->cmd = 7;
				job->tx_job.port = p;
				job->tx_job.cnt = cnt;
				for (n = 0; n < 6; n++)
					job->addr[n] = (u8) num[n];
				job_cnt++;
			}
			break;
		}
	}
}

static void read_file(char *str)
{
	char cmd[20];
	char file[80];
	char tmp[80];
	FILE *ifp;
	int n;

	n = sscanf(str, "%s %s %s", cmd, file, tmp);
	if (n < 2)
		return;
	ifp = fopen(file, "rt");
	if (!ifp)
		return;
	parse_file(ifp);
	fclose(ifp);
}

void send_bpdu(int p, struct bpdu *bpdu, int len)
{
	SOCKET sockfd = stp_fd[p];
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
	int index = 14;
	char *buf = (char *) msg;

	if (!len)
		len = ntohs(msg->hdr.messageLength);

	if (eth_ucast) {
		pservaddr = (SAI *) &eth_ucast_addr[p];
		buf = (char *) eth_ucast_buf[p];
	} else {
		pservaddr = (SAI *) &eth_others_addr[p];
		buf = (char *) eth_others_buf[p];
	}
	servlen = sizeof(eth_others_addr[0]);
	memcpy(&buf[6], src, 6);
	if (eth_vlan) {
		index += 4;
		len += 4;
	}
	memcpy(&buf[index], msg, len);
	len += 14;
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

void disp_ptp_msg(struct ptp_msg *req, int len, int port,
	struct sockaddr_ll *addr)
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
	printf("%d: %02x:%02x:%02x:%02x:%02x:%02x [%d]\n",
		port,
		addr->sll_addr[0], addr->sll_addr[1],
		addr->sll_addr[2], addr->sll_addr[3],
		addr->sll_addr[4], addr->sll_addr[5],
		addr->sll_ifindex);
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
}  /* disp_ptp_msg */

void MakeRootPortConfig_(int p, struct bpdu *bpdu)
{
	bridge_id = &bridges[p];
	port_id = 1;
	prepare_stp(bpdu);
}

void MakeRootPortConfig(int p, struct bpdu *bpdu)
{
	MakeRootPortConfig_(p, bpdu);
	send_bpdu(p, bpdu, sizeof(struct bpdu) - 1);
}

void MakeRootPortBigMsgTimesConfig(int p, struct bpdu *bpdu)
{
	MakeRootPortConfig_(p, bpdu);
	bpdu->message_age = htons(1 * 256);
	bpdu->max_age = htons(40 * 256);
	bpdu->hello_time = htons(10 * 256);
	bpdu->forward_delay = htons(30 * 256);
	send_bpdu(p, bpdu, sizeof(struct bpdu) - 1);
}

void MakeRootPortStaleConfig(int p, struct bpdu *bpdu)
{
	MakeRootPortConfig_(p, bpdu);
	bpdu->message_age = htons(20 * 256);
	send_bpdu(p, bpdu, sizeof(struct bpdu) - 1);
}

void MakeRootPortVeryStaleConfig(int p, struct bpdu *bpdu)
{
	MakeRootPortConfig_(p, bpdu);
	bpdu->message_age = htons(0xdead);
	send_bpdu(p, bpdu, sizeof(struct bpdu) - 1);
}

void MakeRootPortBadProtocolIdConfig(int p, struct bpdu *bpdu)
{
	MakeRootPortConfig_(p, bpdu);
	bpdu->protocol = htons(1);
	send_bpdu(p, bpdu, sizeof(struct bpdu) - 1);
}

void MakeRootPortTooFewOctetsConfig(int p, struct bpdu *bpdu)
{
	MakeRootPortConfig_(p, bpdu);
	send_bpdu(p, bpdu, sizeof(struct bpdu) - 2);
}

void MakeAlternatePortConfig(int p, struct bpdu *bpdu)
{
	bridge_id = &bridges[p];
	port_id = 1;
	prepare_stp(bpdu);

	/* Cannot change root bridge id, root path cost, bridge id, port id. */
	bpdu->port_id.prio = 0xF0;
	send_bpdu(p, bpdu, sizeof(struct bpdu) - 1);
}

void MakeRootPortRST_(int p, struct bpdu *bpdu)
{
	bridge_id = &bridges[p];
	port_id = 1;
	prepare_rstp(bpdu);
	bpdu->flags =
		FORWARDING | LEARNING |
		PORT_ROLE_DESIGNATED << PORT_ROLE_S;
}

void MakeRootPortRST(int p, struct bpdu *bpdu)
{
	MakeRootPortRST_(p, bpdu);
	send_bpdu(p, bpdu, sizeof(struct bpdu));
}

void MakeRootPortProposingRST(int p, struct bpdu *bpdu)
{
	MakeRootPortRST_(p, bpdu);
	bpdu->flags |= PROPOSAL;
	send_bpdu(p, bpdu, sizeof(struct bpdu));
}

void MakeRootPortNextProposingRST(int p, struct bpdu *bpdu)
{
	MakeRootPortRST_(p, bpdu);
	bpdu->flags |= PROPOSAL;
	bpdu->root_path_cost = htonl(0);
	bpdu->message_age = htons(0 * 256);
	send_bpdu(p, bpdu, sizeof(struct bpdu));
}

void MakeRootPortRST_1(int p, struct bpdu *bpdu)
{
	/* Make it like sending from TS1 for better comparison. */
	bridge_id = &bridges[0];
	port_id = 1;
	prepare_rstp(bpdu);
	bpdu->flags =
		FORWARDING | LEARNING |
		PORT_ROLE_DESIGNATED << PORT_ROLE_S;
	send_bpdu(p, bpdu, sizeof(struct bpdu));
}

void MakeRootPortRST_2(int p, struct bpdu *bpdu)
{
	/* Make it like sending from TS1 for better comparison. */
	bridge_id = &bridges[0];

	/* But use different port. */
	port_id = p + 1;
	prepare_rstp(bpdu);
	bpdu->flags =
		FORWARDING | LEARNING |
		PORT_ROLE_DESIGNATED << PORT_ROLE_S;
	send_bpdu(p, bpdu, sizeof(struct bpdu));
}

void MakeRootPortBigMsgTimesRST(int p, struct bpdu *bpdu)
{
	MakeRootPortRST_(p, bpdu);
	bpdu->message_age = htons(1 * 256);
	bpdu->max_age = htons(40 * 256);
	bpdu->hello_time = htons(10 * 256);
	bpdu->forward_delay = htons(30 * 256);
	send_bpdu(p, bpdu, sizeof(struct bpdu));
}

void MakeRootPortSmallMsgTimesRST(int p, struct bpdu *bpdu)
{
	MakeRootPortRST_(p, bpdu);
	bpdu->message_age = htons(1 * 256);
	bpdu->max_age = htons(6 * 256);
	bpdu->hello_time = htons(1 * 256);
	bpdu->forward_delay = htons(4 * 256);
	send_bpdu(p, bpdu, sizeof(struct bpdu));
}

void MakeRootPortBadMsgTimesRST(int p, struct bpdu *bpdu)
{
	MakeRootPortRST_(p, bpdu);
	bpdu->max_age = htons(41 * 256);
	bpdu->hello_time = htons(2 * 256);
	bpdu->forward_delay = htons(31 * 256);
	send_bpdu(p, bpdu, sizeof(struct bpdu));
}

void MakeRootPortStaleRST(int p, struct bpdu *bpdu)
{
	MakeRootPortRST_(p, bpdu);
	bpdu->message_age = htons(20 * 256);
	send_bpdu(p, bpdu, sizeof(struct bpdu));
}

void MakeRootPortVeryStaleRST(int p, struct bpdu *bpdu)
{
	MakeRootPortRST_(p, bpdu);
	bpdu->message_age = htons(0xdead);
	send_bpdu(p, bpdu, sizeof(struct bpdu));
}

void MakeRootPortAlmostStaleRST(int p, struct bpdu *bpdu)
{
	MakeRootPortRST_(p, bpdu);
	bpdu->message_age = htons(18 * 256);
#if 1
	bpdu->hello_time = htons(1 * 256);
#endif
	send_bpdu(p, bpdu, sizeof(struct bpdu));
}

void MakeRootPortBadProtocolIdRST(int p, struct bpdu *bpdu)
{
	MakeRootPortRST_(p, bpdu);
	bpdu->protocol = htons(1);
	send_bpdu(p, bpdu, sizeof(struct bpdu));
}

void MakeRootPortTooFewOctetsRST(int p, struct bpdu *bpdu)
{
	MakeRootPortRST_(p, bpdu);
	send_bpdu(p, bpdu, sizeof(struct bpdu) - 1);
}

void MakeRootPortHelloTimeZeroRST(int p, struct bpdu *bpdu)
{
	MakeRootPortRST_(p, bpdu);
	bpdu->hello_time = 0;
	send_bpdu(p, bpdu, sizeof(struct bpdu));
}

void MakeRootPortHelloTimeLessThanOneRST(int p, struct bpdu *bpdu)
{
	MakeRootPortRST_(p, bpdu);
	bpdu->hello_time = htons(0x50);
	send_bpdu(p, bpdu, sizeof(struct bpdu));
}

void RootAgreementRST(int p, struct bpdu *bpdu)
{
	bridge_id = &bridges[p];
	port_id = p + 1;
	prepare_rstp(bpdu);
	bpdu->flags =
		FORWARDING | LEARNING | AGREEMENT |
		PORT_ROLE_ROOT << PORT_ROLE_S;

	/* Need a higher path cost for root port. */
	bpdu->root_path_cost = htonl(root_path_cost + rx_root_path_cost);
	send_bpdu(p, bpdu, sizeof(struct bpdu));
}

void MakeAlternatePortRST(int p, struct bpdu *bpdu)
{
	bridge_id = &bridges[p];
	port_id = 1;
	prepare_rstp(bpdu);
	bpdu->flags =
		FORWARDING | LEARNING |
		PORT_ROLE_DESIGNATED << PORT_ROLE_S;

	/* Cannot change root bridge id, root path cost, bridge id, port id. */
	bpdu->port_id.prio = 0xF0;

	/*
	 * RSTP.op.4.1.A says wait 6 seconds after sending this for AutoEdge
	 * to open the port, but AutoEdge takes 3 seconds to indicate operEdge,
	 * and the port needs 3 * HelloTime timeout to begin the edgeDelayWhile
	 * timer.
	 */

	/*
	 * RSTP.op.4.2.B expects the port to be opened after 21 seconds.
	 * Not sure how that can be accomplished.
	 */
	send_bpdu(p, bpdu, sizeof(struct bpdu));
}

void MakeAlternatePortRST_1(int p, struct bpdu *bpdu)
{
	bridge_id = &bridges[p];
	port_id = 1;
	prepare_rstp(bpdu);
	bpdu->flags =
		FORWARDING | LEARNING |
		PORT_ROLE_DESIGNATED << PORT_ROLE_S;

	/* Cannot change root bridge id, root path cost, bridge id, port id. */
	bpdu->port_id.prio = 0xF0;

	/*
	 * RSTP.op.4.1.A says wait 6 seconds after sending this for AutoEdge
	 * to open the port, but AutoEdge takes 3 seconds to indicate operEdge,
	 * and the port needs 3 * HelloTime timeout to begin the edgeDelayWhile
	 * timer.
	 */
	bpdu->hello_time = htons(1 * 256);

	/*
	 * RSTP.op.4.2.B expects the port to be opened after 21 seconds.
	 * Not sure how that can be accomplished.
	 */
	send_bpdu(p, bpdu, sizeof(struct bpdu));
}

void MakeAlternatePortRST_2(int p, struct bpdu *bpdu)
{
	bridge_id = &bridges[p];
	port_id = 1;
	prepare_rstp(bpdu);
	bpdu->flags =
		FORWARDING | LEARNING |
		PORT_ROLE_DESIGNATED << PORT_ROLE_S;

	/* Cannot change root bridge id, root path cost, bridge id, port id. */
	bpdu->port_id.prio = 0xF0;

	/*
	 * RSTP.op.4.2.B expects the port to be opened after 21 seconds.
	 * Not sure how that can be accomplished.
	 */
	bpdu->hello_time = htons(7 * 256);
	send_bpdu(p, bpdu, sizeof(struct bpdu));
}

void NotifyTC_RST(int p, struct bpdu *bpdu)
{
	struct _bridge_id id;

	memcpy(&id, &root_bridge, sizeof(struct _bridge_id));
	id.addr[5] += 0x0A;

	/* Topology change is not accepted from inferior designated port. */
	bridge_id = &bridges[p];
	bridge_id = &id;
	port_id = p + 1;
	prepare_rstp(bpdu);
	id.addr[5] += 0x01;
	memcpy(&bpdu->root, bridge_id, sizeof(struct _bridge_id));
	bpdu->flags = TOPOLOGY_CHANGE |
		AGREEMENT |
		PORT_ROLE_ROOT << PORT_ROLE_S;

#if 0
	/* Need a higher path cost for root port. */
	bpdu->root_path_cost = htonl(600000 + ntohl(bpdu->root_path_cost));
	bpdu->message_age = htons(12 * 256);
#endif
	send_bpdu(p, bpdu, sizeof(struct bpdu));
}

void BadProtocolId_TCN_BPDU(int p, struct bpdu *bpdu)
{
	prepare_tcn(bpdu);
	bpdu->protocol = htons(1);
	send_bpdu(p, bpdu, 7);
}

void MakeRootPortPathCostRST(int p, struct bpdu *bpdu)
{
	MakeRootPortRST_(p, bpdu);
	bpdu->root_path_cost = htonl(100000);
	send_bpdu(p, bpdu, sizeof(struct bpdu));
}

void MakeRootPortDesignatedBridgeIDRST(int p, struct bpdu *bpdu)
{
	MakeRootPortRST_(p, bpdu);
	bpdu->bridge_id.prio = htons(0xE000);
	send_bpdu(p, bpdu, sizeof(struct bpdu));
}

void MakeRootPortDesignatedPortIDRST(int p, struct bpdu *bpdu)
{
	MakeRootPortRST_(p, bpdu);
	bpdu->port_id.prio = 0x70;
	send_bpdu(p, bpdu, sizeof(struct bpdu));
}

void MakeBackupPortRST(int p, struct bpdu *bpdu)
{
	MakeRootPortRST_(p, bpdu);
	memcpy(&bpdu->bridge_id, &rx_desg_bridge, sizeof(struct _bridge_id));
	send_bpdu(p, bpdu, sizeof(struct bpdu));
}

void MakeBackupPortRST_1(int p, struct bpdu *bpdu)
{
	MakeRootPortRST_(p, bpdu);
	memcpy(&bpdu->bridge_id, &rx_desg_bridge, sizeof(struct _bridge_id));
	bpdu->bridge_id.prio = 0;
	send_bpdu(p, bpdu, sizeof(struct bpdu));
}

void MakeBackupPortIDRST(int p, struct bpdu *bpdu)
{
	MakeRootPortRST_(p, bpdu);
	memcpy(&bpdu->bridge_id, &rx_desg_bridge, sizeof(struct _bridge_id));
	bpdu->port_id.num = p + 2;
	send_bpdu(p, bpdu, sizeof(struct bpdu));
}

void MigratePort2STP(int p, struct bpdu *bpdu)
{
	struct _bridge_id id;

	memcpy(&id, &root_bridge, sizeof(struct _bridge_id));
	id.addr[5] += 0x0F;

	bridge_id = &bridges[p];
	bridge_id = &id;
	port_id = p + 1;
	prepare_stp(bpdu);
	memcpy(&bpdu->root, bridge_id, sizeof(struct _bridge_id));

	/* Should not cause the port to become root port. */
	bpdu->root.prio = htons(0xF000);
	send_bpdu(p, bpdu, sizeof(struct bpdu) - 1);
}

void MigratePort2RSTP(int p, struct bpdu *bpdu)
{
	struct _bridge_id id;

	memcpy(&id, &root_bridge, sizeof(struct _bridge_id));
	id.addr[5] += 0x0F;

	bridge_id = &bridges[p];
	bridge_id = &id;
	port_id = p + 1;
	prepare_rstp(bpdu);
	bpdu->flags =
		PORT_ROLE_ALTERNATE << PORT_ROLE_S;
	memcpy(&bpdu->root, bridge_id, sizeof(struct _bridge_id));

	/* Should not cause the port to become root port. */
	bpdu->root.prio = htons(0xF000);
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

void wait_for_rx(int p)
{
	rx_wait[p] = 1;
	signal_long_wait(&rx_thread[p], FALSE);
}

static int rstp_send[4];
static int rstp_type[4];
static int rstp_setting;

void request_to_send(void)
{
	signal_update(&tx_job_thread, NULL, 0);
}

void wait_for_send(void)
{
	signal_wait(&tx_done_thread, !tx_job_cnt);
}

static void process_jobs(void)
{
	int i;
	int j;
	int p;
	u16 vid;
	u8 *buf;
	int tx_job = 0;
	struct job_info *job;

	for (i = 0; i < job_cnt; i++) {
		job = &jobs[i];
		switch (job->cmd) {
		case 1:
			p = job->tx_job.port;
			vid = job->tx_job.vid;
			if (vid) {
				u16 *word = (u16 *) &eth_ucast_buf[p][14];

				*word = htons(vid);
			}
			add_tx_job(job->tx_job.port, job->tx_job.type,
				job->tx_job.cnt);
			tx_job = job->tx_job.cnt;
			break;
		case 2:
			if (tx_job) {
				tx_job = 0;
				request_to_send();
				wait_for_send();
			}
			p = job->tx_job.port;
			if (job->sec >= 0)
				wait_sec(job->sec);
			else
				wait_for_rx(p);
			break;
		case 3:
			p = job->tx_job.port;
			buf = ts_addr[p];
			memcpy(buf, job->addr, 6);
			break;
		case 4:
			p = job->tx_job.port;
			if (job->tx_job.cnt)
				disp_pkt[p] = 1;
			else
				disp_pkt[p] = 0;
			break;
		case 5:
			path_cost_dec = 1;
			if (job->sec)
				tx_delay = 1000000 / job->sec;
			break;
		case 6:
			p = job->tx_job.port;
			for (j = 0; j < rx_cnt; j++) {
				if (!memcmp(rx_addr[j], job->addr, 6))
					break;
			}
			if (j == rx_cnt && rx_cnt < NUM_OF_ADDR &&
			    job->tx_job.cnt < 0) {
				memcpy(rx_addr[j], job->addr, 6);
				rx_cnt++;
			}
			if (j < rx_cnt) {
				if (job->tx_job.cnt >= 0) {
					printf(" TS%d to TS%d ",
						job->addr[5] & 3, p + 1);
					if (rx_num[j][p] == job->tx_job.cnt)
						printf("PASS\n");
					else
						printf("FAIL\n");
				} else {
					rx_num[j][p] = 0;
				}
			}
			break;
		case 7:
			p = job->tx_job.port;
			if (job->tx_job.cnt >= 0) {
				memcpy(eth_ucast_buf[p], job->addr, 6);
				eth_ucast = 1;
			} else
				eth_ucast = 0;
			break;
		}
	}
	job_cnt = 0;
	tx_cont_job_cnt = 0;
	path_cost_dec = 0;
	tx_delay = 0;
	root_path_cost = 200000;
}

void disp_msg(void *msg, int len, int port, struct sockaddr_ll *addr)
{
	struct llc *llc = (struct llc *) msg;
	int msglen;

	msglen = ntohs(llc->len);
	if (msglen < 1500) {
		if (0x42 == llc->dsap &&
		    0x42 == llc->ssap &&
		    0x03 == llc->ctrl) {
			struct timeb tb;
			struct bpdu *bpdu = (struct bpdu *)(llc + 1);

			memcpy(&rx_root_bridge, &bpdu->root,
				sizeof(struct _bridge_id));
			memcpy(&rx_desg_bridge, &bpdu->bridge_id,
				sizeof(struct _bridge_id));
			rx_root_path_cost = ntohl(bpdu->root_path_cost);
			if (!dbg_rcv && !disp_pkt[port])
				return;
			ftime(&tb);
			printf("\n");
			printf("%lu:%04u\n", tb.time, tb.millitm);
			printf("%d: %02x:%02x:%02x:%02x:%02x:%02x [%d]",
				port,
				addr->sll_addr[0], addr->sll_addr[1],
				addr->sll_addr[2], addr->sll_addr[3],
				addr->sll_addr[4], addr->sll_addr[5],
				addr->sll_ifindex);
			printf("  %04x %02x%02x%02x\n",
				msglen, llc->dsap, llc->ssap, llc->ctrl);
			disp_bpdu(bpdu);
			fflush(stdout);
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
	int n;
	int p = 0;
	u8 id[6];
	char cmd[80];
	char line[80];
	char payload[(sizeof(struct bpdu) + 20) & ~3];
	char ptp_payload[(sizeof(struct ptp_msg) + 200) & ~3];
	struct bpdu *bpdu = (struct bpdu *) payload;
	struct ptp_msg *msg = (struct ptp_msg *) ptp_payload;
	int save_dbg_rcv = dbg_rcv;

	dbg_rcv = 0;
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
		switch (line[0]) {
		case 'a':
			n = p;
			if (count >= 2) {
				n = num[0];
				if (1 <= n && n <= rstp_ports)
					n--;
			}
			MakeRootPortRST(n, bpdu);
			break;
		case 'b':
			n = p;
			if (count >= 2) {
				n = num[0];
				if (1 <= n && n <= rstp_ports)
					n--;
			}
			MakeBackupPortRST(n, bpdu);
			break;
		case 'u':
			n = p;
			if (count >= 2) {
				n = num[0];
				if (1 <= n && n <= rstp_ports)
					n--;
			}
			MakeBackupPortRST_1(n, bpdu);
			break;
		case 'c':
			n = p;
			if (count >= 2) {
				n = num[0];
				if (1 <= n && n <= rstp_ports)
					n--;
			}
			MakeAlternatePortRST(n, bpdu);
			break;
		case 'd':
			n = p;
			if (count >= 2) {
				n = num[0];
				if (1 <= n && n <= rstp_ports)
					n--;
			}
			MakeRootPortRST_1(n, bpdu);
			break;
		case 'm':
			n = p;
			if (count >= 2) {
				n = num[0];
				if (1 <= n && n <= rstp_ports)
					n--;
			}
			MigratePort2RSTP(n, bpdu);
			break;
		case 'n':
			n = p;
			if (count >= 2) {
				n = num[0];
				if (1 <= n && n <= rstp_ports)
					n--;
			}
			MigratePort2STP(n, bpdu);
			break;
		case 't':
			n = p;
			if (count >= 2) {
				n = num[0];
				if (1 <= n && n <= rstp_ports)
					n--;
			}
			NotifyTC_RST(n, bpdu);
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
			printf("\tr <f>\tread script\n");
			printf("\tp [#]\tport\n");
			printf("\ta [#]\tMakeRootPort\n");
			printf("\tb [#]\tMakeBackupPort\n");
			printf("\tc [#]\tMakeAlternatePort\n");
			printf("\td [#]\tMakeRootPort_1\n");
			printf("\tm [#]\tMigratePort2RSTP\n");
			printf("\tn [#]\tMigratePort2STP\n");
			printf("\tt [#]\tNotifyTC_RST\n");
			printf("\tp\tdestination port\n");
			printf("\th\thelp\n");
			printf("\tq\tquit\n");
			break;
		case 'q':
			cont = 0;
			break;
		case 'r':
			read_file(line);
			process_jobs();
			break;
		case 10:
			if (dbg_rcv)
				dbg_rcv = 0;
			else
				dbg_rcv = save_dbg_rcv;
			break;
		}
	} while (cont);
	dbg_rcv = save_dbg_rcv;
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
#if 0
	if (cur->len == last->len &&
			memcmp(cur->from, last->from, len) == 0 &&
			memcmp(cur->buf, last->buf, cur->len) == 0)
		return 1;
#endif
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
	struct rx_param *rx_param;
	u8 *recvbuf;
	SOCKET sockfd;
	SOCKET fd[8];
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
	struct ptp_msg *msg;
	int i;
	int j;
	char in_addr[80];
	int cur;
	int last;
	int nsel;
	int looped;
	int msglen;

	pTaskParam = (PTTaskParam) param;
	rx_param = pTaskParam->param;

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
	maxfdp1 = rx_param->bpdu[0];
	j = 0;
	for (i = 0; i < rx_param->cnt; i++) {
		fd[j] = rx_param->bpdu[i];
		FD_SET(fd[j], &allrset);
		if (fd[j] > maxfdp1)
			maxfdp1 = fd[j];
		++j;
		fd[j] = rx_param->others[i];
		FD_SET(fd[j], &allrset);
		if (fd[j] > maxfdp1)
			maxfdp1 = fd[j];
		++j;
	}
	maxfdp1++;
	FOREVER {
		if ( pTaskParam->fTaskStop ) {
			break;
		}

#if 1
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

		for (i = 0; i < rx_param->cnt * 2; i++) {
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
			addr = NULL;
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
			bpdu = NULL;
			msg = NULL;
			msglen = buf[cur].len;
#ifdef _SYS_SOCKET_H
			if (AF_PACKET == buf[cur].from->sa_family) {
				if (!(i & 1)) {
					bpdu = (struct bpdu *)
						&buf[cur].buf[12];
					msglen -= 12;
				} else {
					int index = 14;
					u16 *word = (u16 *)
						&buf[cur].buf[12];

					if (*word == ntohs(ETH_P_8021Q))
						index += 4;
					msg = (struct ptp_msg *)
						&buf[cur].buf[index];
					msglen -= index;
				}
			} else
#endif
				msg = (struct ptp_msg *) buf[cur].buf;
			looped = check_loop(buf[cur].from, len,
				i / 2);
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
			j = i / 2;
			if (bpdu) {
int save = disp_pkt[j];
				if (rx_wait[j]) {
					rx_wait[j] = 0;
disp_pkt[j] = 1;
				}
					signal_update(&rx_thread[i / 2],
						NULL, 0);
				disp_msg(bpdu, msglen, i / 2, addr);
disp_pkt[j] = save;
			}
			if (msg) {
				int k;

				for (k = 0; k < rx_cnt; k++) {
					if (!memcmp(rx_addr[k],
					    addr->sll_addr, 6)) {
						rx_num[k][j]++;
						break;
					}
				}
			}
			if (msg && disp_pkt[i / 2])
				disp_ptp_msg(msg, msglen, i / 2, addr);
			if (dbg_rcv)
				Pthread_mutex_unlock(&disp_mutex);
		}
#endif
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
	char payload[(sizeof(struct bpdu) + 40) & ~3];
	struct bpdu *bpdu = (struct bpdu *) payload;
	struct ptp_msg *msg = (struct ptp_msg *) payload;
	struct tx_job_type *tx_job;
	int i;
	int n;
	int p;
	u8 *id;

	pTaskParam = (PTTaskParam) param;
	FOREVER {
		if ( pTaskParam->fTaskStop ) {
			break;
		}

		signal_wait(&tx_job_thread, tx_job_cnt);

		Pthread_mutex_lock(&tx_mutex);
		for (i = 0; i < tx_job_cnt; i++) {
			tx_job = &tx_jobs[i];
			p = tx_job->port;
			switch (tx_job->type) {
			case BPDU_RootAgreementRST:
				RootAgreementRST(p, bpdu);
				break;
			case BPDU_MakeRootPortConfig:
				MakeRootPortConfig(p, bpdu);
				break;
			case BPDU_MakeRootPortStaleConfig:
				MakeRootPortStaleConfig(p, bpdu);
				break;
			case BPDU_MakeRootPortVeryStaleConfig:
				MakeRootPortVeryStaleConfig(p, bpdu);
				break;
			case BPDU_MakeRootPortBadProtocolIdConfig:
				MakeRootPortBadProtocolIdConfig(p, bpdu);
				break;
			case BPDU_MakeRootPortTooFewOctetsConfig:
				MakeRootPortTooFewOctetsConfig(p, bpdu);
				break;
			case BPDU_MakeAlternatePortConfig:
				MakeAlternatePortConfig(p, bpdu);
				break;
			case BPDU_MakeRootPortRST:
				for (n = 0; n < tx_job->cnt; n++) {
					MakeRootPortRST(p, bpdu);
					if (tx_delay) {
						root_path_cost -=
							path_cost_dec;
						usleep(tx_delay);
					}
				}
				break;
			case BPDU_MakeRootPortRST_1:
				MakeRootPortRST_1(p, bpdu);
				break;
			case BPDU_MakeRootPortRST_2:
				MakeRootPortRST_2(p, bpdu);
				break;
			case BPDU_MakeRootPortNextProposingRST:
				MakeRootPortNextProposingRST(p, bpdu);
				break;
			case BPDU_MakeRootPortProposingRST:
				MakeRootPortProposingRST(p, bpdu);
				break;
			case BPDU_MakeRootPortBigMsgTimesRST:
				MakeRootPortBigMsgTimesRST(p, bpdu);
				break;
			case BPDU_MakeRootPortSmallMsgTimesRST:
				MakeRootPortSmallMsgTimesRST(p, bpdu);
				break;
			case BPDU_MakeRootPortBadMsgTimesRST:
				MakeRootPortBadMsgTimesRST(p, bpdu);
				break;
			case BPDU_MakeRootPortStaleRST:
				MakeRootPortStaleRST(p, bpdu);
				break;
			case BPDU_MakeRootPortVeryStaleRST:
				MakeRootPortVeryStaleRST(p, bpdu);
				break;
			case BPDU_MakeRootPortAlmostStaleRST:
				MakeRootPortAlmostStaleRST(p, bpdu);
				break;
			case BPDU_MakeRootPortBadProtocolIdRST:
				MakeRootPortBadProtocolIdRST(p, bpdu);
				break;
			case BPDU_MakeRootPortTooFewOctetsRST:
				MakeRootPortTooFewOctetsRST(p, bpdu);
				break;
			case BPDU_MakeRootPortHelloTimeZeroRST:
				MakeRootPortHelloTimeZeroRST(p, bpdu);
				break;
			case BPDU_MakeRootPortHelloTimeLessThanOneRST:
				MakeRootPortHelloTimeLessThanOneRST(p, bpdu);
				break;
			case BPDU_MakeAlternatePortRST:
				MakeAlternatePortRST(p, bpdu);
				break;
			case BPDU_MakeAlternatePortRST_1:
				MakeAlternatePortRST_1(p, bpdu);
				break;
			case BPDU_MakeAlternatePortRST_2:
				MakeAlternatePortRST_2(p, bpdu);
				break;
			case BPDU_MakeRootPortPathCostRST:
				MakeRootPortPathCostRST(p, bpdu);
				break;
			case BPDU_MakeRootPortDesignatedBridgeIDRST:
				MakeRootPortDesignatedBridgeIDRST(p, bpdu);
				break;
			case BPDU_MakeRootPortDesignatedPortIDRST:
				MakeRootPortDesignatedPortIDRST(p, bpdu);
				break;
			case BPDU_MakeBackupPortRST:
				MakeBackupPortRST(p, bpdu);
				break;
			case BPDU_MakeBackupPortIDRST:
				MakeBackupPortIDRST(p, bpdu);
				break;
			case BPDU_MigratePort2STP:
				for (n = 0; n < tx_job->cnt; n++) {
					MigratePort2STP(p, bpdu);
				}
				break;
			case BPDU_MigratePort2RSTP:
				for (n = 0; n < tx_job->cnt; n++) {
					MigratePort2RSTP(p, bpdu);
				}
				break;
			case BPDU_NotifyTC_RST:
				NotifyTC_RST(p, bpdu);
				break;
			case BPDU_BadProtocolId_TCN_BPDU:
				BadProtocolId_TCN_BPDU(p, bpdu);
				break;
			case FRAME_untagged:
				id = ts_addr[p];
				for (n = 0; n < tx_job->cnt; n++) {
					prepare_msg(msg, SYNC_MSG);
					send_msg(p, msg, 0, id);
				}
				break;
			case FRAME_unknown:
printf("tx %d %d\n", p, tx_job->cnt);
				break;
			}
		}
		if (tx_job_cnt) {
			signal_update(&tx_done_thread, NULL, 0);
			signal_update(&tx_next_thread, NULL, 0);
		}
		tx_job_cnt = 0;
		Pthread_mutex_unlock(&tx_mutex);
	}
	pTaskParam->fTaskStop = TRUE;

#ifdef _WIN32
	SetEvent( pTaskParam->hevTaskComplete );
#endif

#ifdef _SYS_SOCKET_H
	return NULL;
#endif
}  /* TransmitTask */

#ifdef _SYS_SOCKET_H
void *

#else
void
#endif
PeriodicTask(void *param)
{
	PTTaskParam pTaskParam;
	char payload[(sizeof(struct bpdu) + 20) & ~3];
	struct bpdu *bpdu = (struct bpdu *) payload;
	struct tx_job_type *tx_job;
	int i;

	pTaskParam = (PTTaskParam) param;
	FOREVER {
		if ( pTaskParam->fTaskStop ) {
			break;
		}

		/* Wait for initial jobs. */
		signal_wait(&tx_periodic_thread, tx_cont_job_cnt);
		if (!tx_cont_job_cnt)
			continue;

		/* Wait for job sending. */
		signal_wait(&tx_next_thread, !tx_job_cnt);

		/* Wait for 2 seconds. */
		signal_long_wait(&tx_periodic_thread, !tx_cont_job_cnt);

		Pthread_mutex_lock(&tx_mutex);
		for (i = 0; i < tx_cont_job_cnt; i++) {
			if (!tx_cont_jobs[i].cnt)
				continue;
			if (MAX_TX_JOB_CNT == tx_job_cnt)
printf("  !\n");
			if (MAX_TX_JOB_CNT == tx_job_cnt)
				break;
			tx_job = &tx_jobs[tx_job_cnt++];
			memcpy(tx_job, &tx_cont_jobs[i],
				sizeof(struct tx_job_type));
			tx_job->cnt = 1;
		}
		Pthread_mutex_unlock(&tx_mutex);

		request_to_send();
	}
	pTaskParam->fTaskStop = TRUE;

#ifdef _WIN32
	SetEvent( pTaskParam->hevTaskComplete );
#endif

#ifdef _SYS_SOCKET_H
	return NULL;
#endif
}  /* PeriodicTask */

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

static void add_multi(SOCKET sockfd, char *local_if, u8 *addr)
{
	struct ifreq ifr;
	int rc;

	strcpy(ifr.ifr_name, local_if);
	ifr.ifr_hwaddr.sa_family = AF_UNSPEC;
	memcpy(ifr.ifr_hwaddr.sa_data, addr, ETH_ALEN);
	rc = ioctl(sockfd, SIOCADDMULTI, &ifr);
}

static void del_multi(SOCKET sockfd, char *local_if, u8 *addr)
{
	struct ifreq ifr;
	int rc;

	strcpy(ifr.ifr_name, local_if);
	ifr.ifr_hwaddr.sa_family = AF_UNSPEC;
	memcpy(ifr.ifr_hwaddr.sa_data, addr, ETH_ALEN);
	rc = ioctl(sockfd, SIOCDELMULTI, &ifr);
}

static SOCKET create_raw(struct ip_info *info, char *dest, int p, int stp)
{
	SOCKET sockfd;
	struct ethhdr *eh;
	struct llc *llc;
	int addr[ETH_ALEN];
	int cnt;
	u16 proto;
	u16 *word;
	struct sockaddr_ll *sock_addr;
	u8 *eth_addr;
	u8 **eth_buf;

	if (stp) {
		proto = htons(ETH_P_802_2);
		sock_addr = &eth_bpdu_addr[p];
		eth_addr = eth_bpdu;
		eth_buf = &eth_bpdu_buf[p];
	} else {
		proto = htons(ptp_proto);
		sock_addr = &eth_others_addr[p];
		eth_addr = eth_others;
		eth_buf = &eth_others_buf[p];
	}
	sockfd = Socket(AF_PACKET, SOCK_RAW, proto);
	if (sockfd < 0)
		return sockfd;

	cnt = sscanf(dest, "%x:%x:%x:%x:%x:%x",
		&addr[0], &addr[1], &addr[2], &addr[3], &addr[4], &addr[5]);
	sock_addr->sll_family = PF_PACKET;
	sock_addr->sll_protocol = proto;
	sock_addr->sll_ifindex = info->if_idx + p;
	sock_addr->sll_hatype = ARPHRD_ETHER;
	sock_addr->sll_halen = ETH_ALEN;
	if (ETH_ALEN == cnt) {
		sock_addr->sll_pkttype = PACKET_OTHERHOST;
		sock_addr->sll_addr[0] = (u8) addr[0];
		sock_addr->sll_addr[1] = (u8) addr[1];
		sock_addr->sll_addr[2] = (u8) addr[2];
		sock_addr->sll_addr[3] = (u8) addr[3];
		sock_addr->sll_addr[4] = (u8) addr[4];
		sock_addr->sll_addr[5] = (u8) addr[5];
	} else {
		sock_addr->sll_pkttype = PACKET_MULTICAST;
		memcpy(sock_addr->sll_addr, eth_addr, ETH_ALEN);
	}
	sock_addr->sll_addr[6] = 0x00;
	sock_addr->sll_addr[7] = 0x00;
#if 1
		if (setsockopt(sockfd, SOL_SOCKET, SO_BINDTODEVICE,
		    ethnames[p], strlen(ethnames[p]))) {
			err_ret("bindtodev");
			return -1;
		}
#endif

	*eth_buf = malloc(1518);
	memcpy(*eth_buf, sock_addr->sll_addr, ETH_ALEN);
	memcpy((*eth_buf) + ETH_ALEN, info->hwaddr, ETH_ALEN);
	eh = (struct ethhdr *) *eth_buf;
	eh->h_proto = proto;
	if (eth_vlan) {
		word = (u16 *)((*eth_buf) + 16);
		*word-- = proto;
		*word-- = htons(0);
		*word-- = htons(ETH_P_8021Q);
	}
	if (stp) {
		llc = (struct llc *)((*eth_buf) + 12);
		llc->dsap = 0x42;
		llc->ssap = 0x42;
		llc->ctrl = 0x03;
	}
	memcpy(&eth_ucast_addr[p], sock_addr, sizeof(struct sockaddr_ll));
	sock_addr = &eth_ucast_addr[p];
	eth_buf = &eth_ucast_buf[p];
	if (ETH_ALEN == cnt) {
		sock_addr->sll_pkttype = PACKET_OTHERHOST;
		sock_addr->sll_addr[0] = (u8) addr[0];
		sock_addr->sll_addr[1] = (u8) addr[1];
		sock_addr->sll_addr[2] = (u8) addr[2];
		sock_addr->sll_addr[3] = (u8) addr[3];
		sock_addr->sll_addr[4] = (u8) addr[4];
		sock_addr->sll_addr[5] = (u8) addr[5];
	}
	*eth_buf = malloc(1518);
	memcpy(*eth_buf, sock_addr->sll_addr, ETH_ALEN);
	memcpy((*eth_buf) + ETH_ALEN, info->hwaddr, ETH_ALEN);
	eh = (struct ethhdr *) *eth_buf;
	eh->h_proto = proto;
	if (eth_vlan) {
		word = (u16 *)((*eth_buf) + 16);
		*word-- = proto;
		*word-- = htons(0);
		*word-- = htons(ETH_P_8021Q);
	}
	memcpy(ts_addr[p], info->hwaddr, ETH_ALEN);

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
	int i;
	int p;
	struct ip_info info;
	int multi_loop = 0;
	int unicast_sock = 0;
	struct rx_param rx_param;

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
	dbg_rcv = 3;
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
					if (rstp_ports > NUM_OF_PORTS)
						rstp_ports = NUM_OF_PORTS;
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
					break;
				case 'v':
					eth_vlan = 1;
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

	root_bridge.prio = htons(0x7000);
	root_bridge.addr[0] = 0x00;
	root_bridge.addr[1] = 0xBF;
	root_bridge.addr[2] = 0xCB;
	root_bridge.addr[3] = 0xFC;
	root_bridge.addr[4] = 0xBF;
	root_bridge.addr[5] = 0xC0;

	root_path_cost = 200000;

	for (p = 0; p < NUM_OF_PORTS; p++) {
		bridges[p].prio = htons(0xF000);
		bridges[p].addr[0] = 0x00;
		bridges[p].addr[1] = 0x10;
		bridges[p].addr[2] = 0xA1;
		bridges[p].addr[3] = 0xFC;
		bridges[p].addr[4] = 0xBF;
		bridges[p].addr[5] = 0xC0 + p + 1;
	}

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
#endif
	} else {
		printf("cannot locate IP address\n");
		exit(1);
	}

	ip_family = family;

	for (p = 0; p < rstp_ports; p++) {
		stp_fd[p] = create_raw(&info, dest_ip, p, 1);
		if (stp_fd[p] < 0) {
			printf("Cannot create socket\n");
			return 1;
		}
		eth_fd[p] = create_raw(&info, dest_ip, p, 0);
		if (eth_fd[p] < 0) {
			printf("Cannot create socket\n");
			return 1;
		}
		add_multi(stp_fd[p], ethnames[p], eth_bpdu);
		add_multi(eth_fd[p], ethnames[p], eth_others);
#if 0
		memcpy(&eth_bpdu_buf[p][6], hw_addr, ETH_ALEN);
		memcpy(&eth_others_buf[p][6], hw_addr, ETH_ALEN);
		memcpy(&eth_ucast_buf[p][6], hw_addr, ETH_ALEN);
#endif
		signal_init(&rx_thread[p]);
	}

	signal_init(&tx_done_thread);
	signal_init(&tx_job_thread);
	signal_init(&tx_next_thread);
	signal_init(&tx_periodic_thread);
	job_cnt = 0;

	rx_param.bpdu = stp_fd;
	rx_param.others = eth_fd;
	rx_param.cnt = rstp_ports;

	for (i = 0; i < 3; i++) {
		param[i].fTaskStop = FALSE;
	}
		param[0].param = &rx_param;

	Pthread_create(&tid[0], NULL, ReceiveTask, &param[0]);
	Pthread_create(&tid[1], NULL, TransmitTask, &param[1]);
	Pthread_create(&tid[2], NULL, PeriodicTask, &param[2]);

	if ( !param[0].fTaskStop ) {
		do {
			if (!get_cmd(stdin))
				break;
		} while (1);
		for (i = 0; i < 3; i++) {
			param[i].fTaskStop = TRUE;
		}
	}
	signal_update(&tx_done_thread, NULL, 0);
	signal_update(&tx_job_thread, NULL, 0);
	signal_update(&tx_next_thread, NULL, 0);
	signal_update(&tx_periodic_thread, NULL, 0);

	// wait for task to end
	for (i = 0; i < 3; i++) {
		Pthread_join( tid[i], &status );
	}

	for (p = 0; p < rstp_ports; p++) {
		if (stp_fd[p] > 0) {
			del_multi(stp_fd[p], ethnames[p], eth_bpdu);
			del_multi(eth_fd[p], ethnames[p], eth_others);
			free(eth_bpdu_buf[p]);
			free(eth_others_buf[p]);
			free(eth_ucast_buf[p]);
			closesocket(stp_fd[p]);
			closesocket(eth_fd[p]);
		}
	}
	SocketExit();

	return 0;
}
