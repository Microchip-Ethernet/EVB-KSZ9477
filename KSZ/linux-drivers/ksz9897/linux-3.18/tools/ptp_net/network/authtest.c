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
#include <fcntl.h>
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


#include "ksz_802_1x.h"

#include <errno.h>
#include "ksz_radius.c"

#define EAPOL_PROTO		0x888E

struct llc {
	u16 len;
	u8 dsap;
	u8 ssap;
	u8 ctrl;
} __packed;

#if defined(_MSC_VER)
#include <packoff.h>
#endif


#if 0
#define DBG_RADIUS
#define DBG_MSG
#endif
#if 0
#define DBG_STATE
#endif


int gWaitDelay = 100;

#define RADIUS_AUTHEN_DST_PORT		1812
#define RADIUS_ACCNT_DST_PORT		1813
#define RADIUS_AUTHEN_SRC_PORT		1645
#define RADIUS_ACCNT_SRC_PORT		1646

#define NUM_OF_PORTS			6

int ip_family;
int ipv6_interface = 0;
int dbg_rcv = 0;
int eapol_proto = EAPOL_PROTO;

SOCKET radius_fd;
int auth_ports;
char ethnames[NUM_OF_PORTS][20];
char drvname[80];
u16 radius_dst_port;
u16 radius_src_port;

char devname[20];

struct sockaddr_in radius_addr;
#ifdef _SYS_SOCKET_H

u8 eth_eapol[] = { 0x01, 0x80, 0xC2, 0x00, 0x00, 0x03 };

u8 hw_addr[ETH_ALEN];

pthread_mutex_t disp_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t radius_id_mutex = PTHREAD_MUTEX_INITIALIZER;

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

static void get_radius_id(struct radius_info *radius)
{
	static u8 radius_id;

	Pthread_mutex_lock(&radius_id_mutex);
	radius->id = radius_id++;
	radius->sent = TRUE;
	Pthread_mutex_unlock(&radius_id_mutex);
}
#endif

u8 host_addr[16];
u8 host_addr6[16];

struct eap_timers {
	int authWhile_;
	int aWhile_;
	int heldWhile_;
	int quietWhile_;
	int reAuthWhen_;
	int startWhen_;
};

#ifdef DBG_STATE
static char *timers[6] = {
	"authWhile",
	"aWhile",
	"heldWhile",
	"quietWhile",
	"reAuthWhen",
	"startWhen",
};
#endif

struct eap_vars {
	u32 authAbort_:1;
	u32 authFail_:1;
	u32 authStart_:1;
	u32 authTimeout_:1;
	u32 authSuccess_:1;
	u32 eapFail_:1;
	u32 eapolEap_:1;
	u32 eapSuccess_:1;
	u32 eapTimeout_:1;
	u32 initialize_:1;
	u32 keyAvailable_:1;
	u32 keyDone_:1;
	u32 keyRun_:1;
	u32 keyTxEnabled_:1;
	u32 portEnabled_:1;
	u32 portValid_:1;
	u32 reAuthenticate_:1;
	u32 suppAbort_:1;
	u32 suppFail_:1;
	u32 suppStart_:1;
	u32 suppSuccess_:1;
	u32 suppTimeout_:1;
	u32 rxKey_:1;
	u8 authPortStatus_;
	u8 portControl_;
	u8 portStatus_;
	u8 suppPortStatus_;
};

enum {
	AUTH_PAE_INVALID,
	AUTH_PAE_INITIALIZE,
	AUTH_PAE_DISCONNECTED,
	AUTH_PAE_RESTART,
	AUTH_PAE_CONNECTING,
	AUTH_PAE_AUTHENTICATING,
	AUTH_PAE_AUTHENTICATED,
	AUTH_PAE_ABORTING,
	AUTH_PAE_HELD,
	AUTH_PAE_FORCE_AUTH,
	AUTH_PAE_FORCE_UNAUTH,
};

struct eap_auth_vars {
	u32 eapolLogoff_:1;
	u32 eapolStart_:1;
	u32 eapReq_:1;
	u32 eapRestart_:1;
	u32 eapNoReq_:1;
	u32 eapResp_:1;
	u8 portMode_;
	int reAuthCount_;
};

struct eap_auth_const {
	int quietPeriod_;
	int reAuthMax_;
	int serverTimeout_;
	int reAuthPeriod_;
	u32 reAuthEnabled_:1;
};

enum {
	AUTH_BKE_INVALID,
	AUTH_BKE_REQUEST,
	AUTH_BKE_RESPONSE,
	AUTH_BKE_SUCCESS,
	AUTH_BKE_FAIL,
	AUTH_BKE_TIMEOUT,
	AUTH_BKE_IDLE,
	AUTH_BKE_INITIALIZE,
	AUTH_BKE_IGNORE,
};

enum {
	SUPP_PAE_INVALID,
	SUPP_PAE_LOGOFF,
	SUPP_PAE_DISCONNECTED,
	SUPP_PAE_CONNECTING,
	SUPP_PAE_AUTHENTICATING,
	SUPP_PAE_HELD,
	SUPP_PAE_AUTHENTICATED,
	SUPP_PAE_RESTART,
	SUPP_PAE_S_FORCE_AUTH,
	SUPP_PAE_S_FORCE_UNAUTH,
};

enum {
	AUTH_KEY_INVALID,
	AUTH_KEY_NO_TRANSMIT,
	AUTH_KEY_TRANSMIT,
};

enum {
	SUPP_KEY_INVALID,
	SUPP_KEY_NO_TRANSMIT,
	SUPP_KEY_TRANSMIT,
};

enum {
	KEY_INVALID,
	KEY_NO_RECEIVE,
	KEY_RECEIVE,
};

enum {
	RE_AUTH_INVALID,
	RE_AUTH_INITIALIZE,
	RE_AUTHENTICATE,
};

struct eap_supp_vars {
	u32 logoffSent_:1;
	u32 eapNoResp_:1;
	u32 userLogoff_:1;
	u32 suppKeyAvailable_:1;
	u8 sPortMode_;
	int startCount_;
};

struct eap_supp_const {
	int heldPeriod_;
	int startPeriod_;
	int maxStart_;
	int authPeriod_;
};

enum {
	SUPP_BKE_INVALID,
	SUPP_BKE_REQUEST,
	SUPP_BKE_RESPONSE,
	SUPP_BKE_SUCCESS,
	SUPP_BKE_FAIL,
	SUPP_BKE_TIMEOUT,
	SUPP_BKE_IDLE,
	SUPP_BKE_INITIALIZE,
	SUPP_BKE_RECEIVE,
};

enum {
	Authorized,
	Unauthorized,
};

enum {
	Auto = 1,
	ForceAuthorized,
	ForceUnauthorized,
};

#define AUTH_PAE_STATE_MACHINE		(1 << 0)
#define AUTH_BKE_STATE_MACHINE		(1 << 1)
#define SUPP_PAE_STATE_MACHINE		(1 << 2)
#define SUPP_BKE_STATE_MACHINE		(1 << 3)
#define AUTH_KEY_STATE_MACHINE		(1 << 4)
#define SUPP_KEY_STATE_MACHINE		(1 << 5)
#define KEY_RX_STATE_MACHINE		(1 << 6)
#define RE_AUTH_STATE_MACHINE		(1 << 7)

#define ALL_STATE_MACHINE		\
	(AUTH_PAE_STATE_MACHINE |	\
	AUTH_BKE_STATE_MACHINE |	\
	SUPP_PAE_STATE_MACHINE |	\
	SUPP_BKE_STATE_MACHINE |	\
	AUTH_KEY_STATE_MACHINE |	\
	SUPP_KEY_STATE_MACHINE |	\
	KEY_RX_STATE_MACHINE |	\
	RE_AUTH_STATE_MACHINE)


struct thread_info {
	pthread_cond_t  cond;
	pthread_mutex_t mutex;
};


struct auth_info {
	SOCKET eth_fd;
	struct sockaddr_ll eth_eapol_addr;
	u8 *eth_eapol_buf;
	int link;
	int port;
	u8 eap_first_req;
	u8 eap_radius_req;
	struct thread_info eap_radius_timeout;
	struct thread_info update_sig;

	u8 auth_pae_state;
	u8 auth_bke_state;
	u8 supp_pae_state;
	u8 supp_bke_state;
	u8 auth_key_tx_state;
	u8 supp_key_tx_state;
	u8 key_rx_state;
	u8 re_auth_state;
	u8 mode;
	u8 state;
	u8 code;
	u8 eap_id;
	u8 eap_resp_id;
	u32 update;
	u32 eap_resp;
	u32 eap_req;
	int eap_timers[6];
	struct eap_vars eap_var;
	struct eap_auth_vars auth_var;
	struct eap_supp_vars supp_var;
	struct eapol_frame *eapol;
	u8 eapol_data[1600];
	u8 eap[80];
	u8 resp_data[80];
	u16 resp_len;
	struct radius_info radius;
};

static struct eap_auth_const eap_auth_consts;
static struct eap_supp_const eap_supp_consts;

#define authWhile		(info->eap_timers[0])
#define aWhile			(info->eap_timers[1])
#define heldWhile		(info->eap_timers[2])
#define quietWhile		(info->eap_timers[3])
#define reAuthWhen		(info->eap_timers[4])
#define startWhen		(info->eap_timers[5])

#define authAbort		(info->eap_var.authAbort_)
#define authFail		(info->eap_var.authFail_)
#define authPortStatus		(info->eap_var.authPortStatus_)
#define authStart		(info->eap_var.authStart_)
#define authTimeout		(info->eap_var.authTimeout_)
#define authSuccess		(info->eap_var.authSuccess_)
#define eapFail			(info->eap_var.eapFail_)
#define eapolEap		(info->eap_var.eapolEap_)
#define eapSuccess		(info->eap_var.eapSuccess_)
#define eapTimeout		(info->eap_var.eapTimeout_)
#define initialize		(info->eap_var.initialize_)
#define keyAvailable		(info->eap_var.keyAvailable_)
#define keyDone			(info->eap_var.keyDone_)
#define keyRun			(info->eap_var.keyRun_)
#define keyTxEnabled		(info->eap_var.keyTxEnabled_)
#define portControl		(info->eap_var.portControl_)
#define portEnabled		(info->eap_var.portEnabled_)
#define portStatus		(info->eap_var.portStatus_)
#define portValid		(info->eap_var.portValid_)
#define reAuthenticate		(info->eap_var.reAuthenticate_)
#define suppAbort		(info->eap_var.suppAbort_)
#define suppFail		(info->eap_var.suppFail_)
#define suppPortStatus		(info->eap_var.suppPortStatus_)
#define suppStart		(info->eap_var.suppStart_)
#define suppSuccess		(info->eap_var.suppSuccess_)
#define suppTimeout		(info->eap_var.suppTimeout_)

#define rxKey			(info->eap_var.rxKey_)

#define eapolLogoff		(info->auth_var.eapolLogoff_)
#define eapolStart		(info->auth_var.eapolStart_)
#define eapReq			(info->auth_var.eapReq_)
#define eapRestart		(info->auth_var.eapRestart_)
#define portMode		(info->auth_var.portMode_)
#define reAuthCount		(info->auth_var.reAuthCount_)
#define eapNoReq		(info->auth_var.eapNoReq_)
#define eapResp			(info->auth_var.eapResp_)	

#define logoffSent		(info->supp_var.logoffSent_)
#define sPortMode		(info->supp_var.sPortMode_)
#define startCount		(info->supp_var.startCount_)
#define userLogoff		(info->supp_var.userLogoff_)
#define eapNoResp		(info->supp_var.eapNoResp_)

#define suppKeyAvailable	(info->supp_var.suppKeyAvailable_)

#define quietPeriod		(eap_auth_consts.quietPeriod_)
#define reAuthMax		(eap_auth_consts.reAuthMax_)
#define serverTimeout		(eap_auth_consts.serverTimeout_)
#define reAuthPeriod		(eap_auth_consts.reAuthPeriod_)
#define reAuthEnabled		(eap_auth_consts.reAuthEnabled_)

#define heldPeriod		(eap_supp_consts.heldPeriod_)
#define startPeriod		(eap_supp_consts.startPeriod_)
#define maxStart		(eap_supp_consts.maxStart_)
#define authPeriod		(eap_supp_consts.authPeriod_)


static void prepare_len(struct eapol_frame *eapol, u16 len)
{
	eapol->version = 2;
	eapol->len = htons(len);
}

static void prepare_eapol(struct eapol_frame *eapol, u8 type)
{
	eapol->type = type;
	prepare_len(eapol, 0);
}

static void prepare_eap(struct eapol_frame *eapol, u16 len)
{
	eapol->type = EAP_PACKET;
	prepare_len(eapol, len);
}

static void send_eapol(struct auth_info *auth, struct eapol_frame *eapol,
	int len)
{
	SOCKET sockfd = auth->eth_fd;
	SAI *pservaddr;
	socklen_t servlen;
	char *buf;

	pservaddr = (SAI *) &auth->eth_eapol_addr;
	servlen = sizeof(auth->eth_eapol_addr);
	buf = (char *) auth->eth_eapol_buf;
	memcpy(&buf[14], eapol, len);
	len += 14;
	Sendto(sockfd, buf, len, 0, (SA *) pservaddr, servlen);
#ifdef DBG_MSG
{
int i;
if (len > 20)
	len = 20;
printf("%d = ", sockfd);
for (i = 0; i < len; i++)
printf("%02x ", (unsigned char) buf[i]);
printf("\n");
}
#endif
}  /* send_eapol */

static void send_radius(SOCKET sockfd, struct radius_frame *radius, int len,
	SA *pservaddr, socklen_t servlen)
{
	char *buf = (char *) radius;

	Sendto(sockfd, buf, len, 0, pservaddr, servlen);
}  /* send_radius */

static void send_start(struct auth_info *auth, struct eapol_frame *eapol)
{
	prepare_eapol(eapol, EAPOL_START);
	send_eapol(auth, eapol, sizeof(struct eapol_frame));
}  /* send_start */

static void send_logoff(struct auth_info *auth, struct eapol_frame *eapol)
{
	prepare_eapol(eapol, EAPOL_LOGOFF);
	send_eapol(auth, eapol, sizeof(struct eapol_frame));
}  /* send_logoff */

#if 0
static void send_request(struct auth_info *auth, struct eapol_frame *eapol,
	u8 id)
{
	u16 len;
	struct eap_frame *eap = (struct eap_frame *)(eapol + 1);
	struct eap_body *body = (struct eap_body *)(eap + 1);

	eap->code = EAP_CODE_REQUEST;
	eap->id = id;
	body->type = EAP_TYPE_IDENTITY;
	len = sizeof(struct eap_frame) + sizeof(struct eap_body);
	eap->len = htons(len);
	prepare_eap(eapol, len);
	len += sizeof(struct eapol_frame);
	send_eapol(auth, eapol, len);
}  /* send_request */
#endif

static void send_eap_resp(struct auth_info *auth, struct eapol_frame *eapol,
	u8 id, u8 *resp, u16 resp_len)
{
	u16 len;
	struct eap_frame *eap = (struct eap_frame *)(eapol + 1);
	u8 *data = (u8 *)(eap + 1);

	eap->code = EAP_CODE_RESPONSE;
	eap->id = id;
	memcpy(data, resp, resp_len);
	len = sizeof(struct eap_frame) + resp_len;
	eap->len = htons(len);
	prepare_eap(eapol, len);
	len += sizeof(struct eapol_frame);
	send_eapol(auth, eapol, len);
}  /* send_eap_resp */

#if 0
static void send_response(struct auth_info *auth, struct eapol_frame *eapol,
	u8 id, u8 *resp, u16 resp_len)
{
	u16 len;
	struct eap_frame *eap = (struct eap_frame *)(eapol + 1);
	struct eap_body *body = (struct eap_body *)(eap + 1);

	eap->code = EAP_CODE_RESPONSE;
	eap->id = id;
	body->type = EAP_TYPE_IDENTITY;
	memcpy(body + 1, resp, resp_len);
	len = sizeof(struct eap_frame) + sizeof(struct eap_body);
	len += resp_len;
	eap->len = htons(len);
	prepare_eap(eapol, len);
	len += sizeof(struct eapol_frame);
	send_eapol(auth, eapol, len);
}  /* send_response */
#endif

static void send_success(struct auth_info *auth, struct eapol_frame *eapol,
	u8 id)
{
	u16 len;
	struct eap_frame *eap = (struct eap_frame *)(eapol + 1);

	eap->code = EAP_CODE_SUCCESS;
	eap->id = id;
	len = sizeof(struct eap_frame);
	eap->len = htons(len);
	prepare_eap(eapol, len);
	len += sizeof(struct eapol_frame);
	send_eapol(auth, eapol, len);
}  /* send_success */

static void send_failure(struct auth_info *auth, struct eapol_frame *eapol,
	u8 id)
{
	u16 len;
	struct eap_frame *eap = (struct eap_frame *)(eapol + 1);

	eap->code = EAP_CODE_FAILURE;
	eap->id = id;
	len = sizeof(struct eap_frame);
	eap->len = htons(len);
	prepare_eap(eapol, len);
	len += sizeof(struct eapol_frame);
	send_eapol(auth, eapol, len);
}  /* send_failure */

static void signal_radius_resp(struct thread_info *pthread, u8 *req)
{
	Pthread_mutex_lock(&pthread->mutex);
	*req = 0;
	pthread_cond_signal(&pthread->cond);
	Pthread_mutex_unlock(&pthread->mutex);
}  /* signal_radius_resp */

static void signal_update(struct thread_info *pthread, u32 *ptr, u32 update)
{
	Pthread_mutex_lock(&pthread->mutex);
	*ptr = update;
	pthread_cond_signal(&pthread->cond);
	Pthread_mutex_unlock(&pthread->mutex);
}  /* signal_update */

static void wait_for_resp(struct auth_info *info)
{
	struct timeb tb;
	struct timespec ts;
	struct thread_info *pthread;
	int n;

	ftime(&tb);
	ts.tv_sec = tb.time;
	ts.tv_nsec = (tb.millitm + 100) * 1000 * 1000;
	if (ts.tv_nsec >= 1000000000) {
		ts.tv_nsec -= 1000000000;
		ts.tv_sec++;
	}

	/* Windows PC may pop out a dialog box asking user information. */
	if (1 == info->eap_first_req)
		ts.tv_sec += 30;

	pthread = &info->eap_radius_timeout;
	Pthread_mutex_lock(&pthread->mutex);
	if (info->eap_radius_req)
		n = pthread_cond_timedwait(&pthread->cond,
			&pthread->mutex, &ts);
	Pthread_mutex_unlock(&pthread->mutex);

	if (info->eap_radius_req) {
		if (1 == info->eap_first_req)
			info->eap_first_req++;
		info->eap_radius_req = 0;
		eapTimeout = TRUE;
		signal_update(&info->update_sig, &info->update,
			AUTH_BKE_STATE_MACHINE);
	}
}  /* wait_for_resp */

static void send_eap(struct auth_info *info, struct eapol_frame *eapol,
	struct eap_frame *src, u16 len)
{
	struct eap_frame *eap = (struct eap_frame *)(eapol + 1);

	memcpy(eap, src, len);
	prepare_eap(eapol, len);
	len += sizeof(struct eapol_frame);
	if (!(info->eap_req & 2))
		info->eap_radius_req = 1;
	send_eapol(info, eapol, len);

	/* Do not wait for response if sending success or failure. */
	if (!(info->eap_req & 2))
		wait_for_resp(info);
}  /* send_eap */


static void proc_auth_req(struct auth_info *info)
{
	struct eap_frame *eap = (struct eap_frame *) info->eap;
	struct eap_body *body = (struct eap_body *)(eap + 1);

	info->eap_resp_id = eap->id;
	if (EAP_CODE_REQUEST == eap->code) {
		if (EAP_TYPE_IDENTITY == body->type) {
			info->eap_resp = 1;
			info->resp_data[0] = body->type;
			strcpy((char *) &info->resp_data[1], "testing");
			info->resp_len = 7 + 1;
			eapResp = TRUE;
			info->update |= SUPP_BKE_STATE_MACHINE;
		} else if (EAP_TYPE_MD5_CHALLENGE == body->type) {
			u8 *data = (u8 *)(body + 1);

			info->eap_resp = 2;
			info->resp_data[0] = body->type;
			memcpy(&info->resp_data[1], data, 17);
			eap_md5(eap->id, "password", data, &info->resp_data[2]);
			info->resp_len = 18;
			eapResp = TRUE;
			info->update |= SUPP_BKE_STATE_MACHINE;
		}
	}
}  /* proc_auth_req */

static void send_auth_req(struct auth_info *info)
{
	if (1 <= info->eap_req && info->eap_req <= 3)
		send_eap(info, info->eapol,
			(struct eap_frame *) info->radius.eap,
			info->radius.eap_len);
}  /* send_auth_req */

static void send_supp_resp(struct auth_info *info)
{
	if (1 <= info->eap_resp && info->eap_resp <= 2) {
		send_eap_resp(info, info->eapol, info->eap_resp_id,
			info->resp_data, info->resp_len);
	}
}  /* send_supp_resp */

static void set_val_dword(struct radius_attrib *attrib, u8 type, u32 val)
{
	attrib->val = type;
	attrib->len = 6;
	val = htonl(val);
	memcpy(attrib + 1, &val, 4);
}  /* set_val_dword */

#if 0
static void set_val_word(struct radius_attrib *attrib, u8 type, u16 val)
{
	attrib->val = type;
	attrib->len = 4;
	val = htons(val);
	memcpy(attrib + 1, &val, 2);
}  /* set_val_word */
#endif

static void set_val_station(struct radius_attrib *attrib, u8 type, u8 *addr)
{
	char *buf = (char *)(attrib + 1);

	attrib->val = type;
	attrib->len = 6 * 2 + 5 + 2;
	sprintf(buf, "%02X-%02X-%02X-%02X-%02X-%02X",
		addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);
}  /* set_val_station */

static void set_val(struct radius_attrib *attrib, u8 type, u8 *val, u16 len)
{
	attrib->val = type;
	attrib->len = 2 + len;
	if (val)
		memcpy(attrib + 1, val, len);
}  /* set_val */

u16 prep_eap_md5(struct eap_frame *eap, u8 id)
{
	u16 len;
	struct eap_body *body = (struct eap_body *)(eap + 1);
	u8 *data = (u8 *)(body + 1);

	eap->code = EAP_CODE_REQUEST;
	eap->id = id;
	body->type = EAP_TYPE_MD5_CHALLENGE;
	len = sizeof(struct eap_frame) + sizeof(struct eap_body);
	data[0] = 16;
	memset(&data[1], 0x12, 16);
	len += 1 + 16;
	eap->len = htons(len);
	return len;
}  /* prep_eap_md5 */

static void proc_radius_msg(struct radius_frame *radius,
	struct radius_info *info, int len, int server)
{
	struct radius_attrib *attrib;
	u8 *data;
	u8 eap_len;
	int eap_index;
	struct eap_frame *eap;
	struct eap_body *body;
	u16 msglen = ntohs(radius->len);
	char password[129];

	if (len > msglen)
		len = msglen;
	info->code = radius->code;
	if (server)
		info->id = radius->id;
	else if (radius->id != info->id) {
		return;
	}

	info->packet.data = (u8 *) radius;
	memcpy(info->packet.vector, radius->vector, 16);
	data = (u8 *)(radius + 1);

	info->eap_code = 0;
	info->eap_len = 0;
	eap_index = 0;

	len -= sizeof(struct radius_frame);
	attrib = (struct radius_attrib *) data;
	while (len > sizeof(struct radius_attrib) && len >= attrib->len) {
		switch (attrib->val) {
		case RADIUS_USER_NAME:
			info->name_len = attrib->len - 2;
			memcpy(info->name, attrib + 1, info->name_len);
			info->name[info->name_len] = 0;
			break;
		case RADIUS_USER_PASSWORD:
			info->password_len = attrib->len - 2;
			memcpy(password, attrib + 1, info->password_len);
			rad_pwdecode(password, info->password_len, secret,
				radius->vector);
			info->password_len = strlen(password);
			memcpy(info->password, password, info->password_len);
			break;
		case RADIUS_EAP_MESSAGE:
			eap_len = attrib->len - 2;
			memcpy(&info->eap[eap_index], attrib + 1, eap_len);
			if (!eap_index) {
				eap = (struct eap_frame *) info->eap;
				body = (struct eap_body *)(eap + 1);
				info->eap_code = eap->code;
				info->eap_type = body->type;
				info->eap_data = (u8 *)(body + 1);
				if (server) {
					if (EAP_CODE_RESPONSE == eap->code &&
					    EAP_TYPE_IDENTITY == body->type)
						info->eap_id = eap->id;
				} else {
					info->eap_id = eap->id;
				}
			}
			eap_index += eap_len;
			info->eap_len += eap_len;
			break;
		case RADIUS_REPLY_MESSAGE:
			info->msg_len = attrib->len - 2;
			memcpy(info->msg, attrib + 1, info->msg_len);
			info->msg[info->msg_len] = 0;
#ifdef DBG_RADIUS
printf("reply: %s\n", info->msg);
#endif
			break;
		case RADIUS_STATE:
			info->state_len = attrib->len - 2;
			memcpy(info->state, attrib + 1, info->state_len);
#ifdef DBG_RADIUS
printf("state: %d\n", info->state_len);
#endif
			memcpy(info->packet.state, info->state,
				info->state_len);
			break;
		case RADIUS_MESSAGE_AUTHENTICATOR:
			if (attrib->len != 18)
				break;
			memcpy(info->authen, attrib + 1, 16);
			info->packet.offset = (u8 *)(attrib) -
				info->packet.data;
			break;
		}
		len -= attrib->len;
		data += attrib->len;
		attrib = (struct radius_attrib *) data;
	}
	info->packet.code = info->code;
	info->packet.data_len = msglen;
	if (RADIUS_CODE_ACCESS_REQUEST == info->code) {
		memcpy(&info->original, &info->packet,
			sizeof(struct radius_packet));
		memcpy(info->original.vector, radius->vector, 16);
	}
	if (rad_verify(&info->packet, &info->original, secret)) {
		return;
	}
#ifdef DBG_RADIUS
	if (RADIUS_CODE_ACCESS_REQUEST != info->code) {
		if (RADIUS_CODE_ACCESS_ACCEPT == info->code)
			printf("accept\n");
		else if (RADIUS_CODE_ACCESS_REJECT == info->code)
			printf("reject\n");
		else if (RADIUS_CODE_ACCESS_CHALLENGE == info->code) {
#if 0
			u8 req[17];
			u8 resp[16];

			memcpy(req, info->eap_data, 17);
#if 1
			strcpy((char *) info->password, "password");
			respond_eap_md5(info);
#endif
			eap_md5(info->eap_id, "password", req, resp);
if (memcmp(&info->eap_data[1], resp, 16)) {
int i;
printf("not match\n");
for (i = 0; i < 16; i++)
printf("%02x ", resp[i]);
printf("\n");
}
#endif
		}
	}
#endif
}  /* proc_radius_msg */

static void prep_radius_msg(struct radius_frame *radius,
	struct radius_info *info, u8 code, u8 id)
{
	struct radius_attrib *attrib;
	u8 *data;
	u32 len = sizeof(struct radius_frame);

	radius->code = code;
	radius->id = id;
	if (RADIUS_CODE_ACCESS_REQUEST == code) {
		prep_radius_req(radius);
	} else
		memcpy(radius->vector, info->original.vector, 16);
	memcpy(info->packet.vector, radius->vector, 16);

	info->packet.data = (u8 *) radius;
	data = (u8 *)(radius + 1);

	if (info->ip_addr[0]) {
		attrib = (struct radius_attrib *) data;
		set_val(attrib, RADIUS_NAS_IP_ADDRESS, info->ip_addr, 4);
		len += attrib->len;
		data += attrib->len;
	}

	if (info->port) {
		attrib = (struct radius_attrib *) data;
		set_val_dword(attrib, RADIUS_NAS_PORT, info->port);
		len += attrib->len;
		data += attrib->len;

		attrib = (struct radius_attrib *) data;
		set_val_dword(attrib, RADIUS_NAS_PORT_TYPE,
			NAS_PORT_TYPE_ETHERNET);
		len += attrib->len;
		data += attrib->len;
	}

	if (info->name_len) {
		attrib = (struct radius_attrib *) data;
		set_val(attrib, RADIUS_USER_NAME, info->name, info->name_len);
		len += attrib->len;
		data += attrib->len;
	}

	if (info->password_len) {
		make_passwd(info->encrypted, &info->password_len,
			info->password, info->password_len,
			secret, radius->vector);
		attrib = (struct radius_attrib *) data;
		set_val(attrib, RADIUS_USER_PASSWORD, info->encrypted,
			info->password_len);
		len += attrib->len;
		data += attrib->len;
	}

	if (info->src[0] != 0xff) {
		attrib = (struct radius_attrib *) data;
		set_val_station(attrib, RADIUS_CALLED_STATION_ID, info->src);
		len += attrib->len;
		data += attrib->len;
	}

	if (info->dst[0] != 0xff) {
		attrib = (struct radius_attrib *) data;
		set_val_station(attrib, RADIUS_CALLING_STATION_ID, info->dst);
		len += attrib->len;
		data += attrib->len;
	}

	if (info->framed) {
		attrib = (struct radius_attrib *) data;
		set_val_dword(attrib, RADIUS_FRAMED_IP_ADDRESS, info->framed);
		len += attrib->len;
		data += attrib->len;
	}

	attrib = (struct radius_attrib *) data;
	set_val_dword(attrib, RADIUS_SERVICE_TYPE, SERVICE_TYPE_FRAMED);
	len += attrib->len;
	data += attrib->len;

	if (info->mtu) {
		attrib = (struct radius_attrib *) data;
		set_val_dword(attrib, RADIUS_FRAMED_MTU, info->mtu);
		len += attrib->len;
		data += attrib->len;
	}

	if (info->msg_len) {
		attrib = (struct radius_attrib *) data;
		set_val(attrib, RADIUS_REPLY_MESSAGE, info->msg, info->msg_len);
		len += attrib->len;
		data += attrib->len;
	}

	if (info->state_len) {
		attrib = (struct radius_attrib *) data;
		set_val(attrib, RADIUS_STATE, info->state, info->state_len);
		memcpy(info->original.state, info->state, info->state_len);
		len += attrib->len;
		data += attrib->len;
	}

	if (info->eap_len) {
		int eap_frag;
		int eap_len = info->eap_len;
		int eap_index = 0;

		while (eap_len) {
			eap_frag = eap_len;
			if (eap_frag > 255)
				eap_frag = 255;
			attrib = (struct radius_attrib *) data;
			set_val(attrib, RADIUS_EAP_MESSAGE,
				&info->eap[eap_index], eap_frag);
			len += attrib->len;
			data += attrib->len;
			eap_index += eap_frag;
			eap_len -= eap_frag;
		}
	}

	info->packet.offset = 0;
	if (info->eap_len) {
		info->packet.offset = data - info->packet.data;
		attrib = (struct radius_attrib *) data;
		memset(info->authen, 0, 16);
		set_val(attrib, RADIUS_MESSAGE_AUTHENTICATOR, info->authen, 16);
		len += attrib->len;
		data += attrib->len;
	}

	radius->len = htons(len);
	info->len = len;

	info->packet.code = code;
	info->packet.data_len = len;
	rad_sign(&info->packet, &info->original, secret);
#ifdef DBG_RADIUS_
printf(" %02x %02x %02x %02x\n",
radius->vector[0], radius->vector[1],
radius->vector[2], radius->vector[3]);
if (info->packet.offset) {
printf("%02x %02x %02x %02x\n",
info->radius_data[info->packet.offset + 2],
info->radius_data[info->packet.offset + 3],
info->radius_data[info->packet.offset + 4],
info->radius_data[info->packet.offset + 5]);
}
#endif
	if (RADIUS_CODE_ACCESS_REQUEST == code) {
		memcpy(&info->original, &info->packet,
			sizeof(struct radius_packet));
		memcpy(info->original.vector, radius->vector, 16);
	}
}  /* prep_radius_msg */

static void prep_access_request_simple_req(struct radius_info *info)
{
	sprintf((char *) info->name, "testing");
	info->name_len = strlen((char *) info->name);

	sprintf((char *) info->password, "password");
	info->password_len = strlen((char *) info->password);

	info->msg_len = 0;
	info->state_len = 0;

	info->eap_len = 0;

	get_radius_id(info);
	prep_radius_msg(info->frame, info, RADIUS_CODE_ACCESS_REQUEST,
		info->id);
}  /* prep_access_request_simple_req */

static void prep_access_request_req(struct radius_info *info)
{
	struct eap_frame *eap = (struct eap_frame *) info->eap;
	struct eap_body *body = (struct eap_body *)(eap + 1);
	u8 *data;

	sprintf((char *) info->name, "testing");
	info->name_len = strlen((char *) info->name);

	info->msg_len = 0;
	info->state_len = 0;

	info->eap_id = 0;

	eap->code = EAP_CODE_RESPONSE;
	eap->id = info->eap_id;
	info->eap_len = sizeof(struct eap_frame) + sizeof(struct eap_body);
	body->type = EAP_TYPE_IDENTITY;
	data = (u8 *)(body + 1);
	sprintf((char *) data, "testing");
	info->eap_len += info->name_len;
	eap->len = htons(info->eap_len);

	get_radius_id(info);
	prep_radius_msg(info->frame, info, RADIUS_CODE_ACCESS_REQUEST,
		info->id);
}  /* prep_access_request_req */

static void prep_access_challenge_req(struct radius_info *info)
{
	struct eap_frame *eap = (struct eap_frame *) info->eap;
	struct eap_body *body = (struct eap_body *)(eap + 1);
	u8 *data;

#if 0
	sprintf((char *) info->password, "password");
	info->password_len = strlen((char *) info->password);
#endif

	info->msg_len = 0;

	eap->code = EAP_CODE_RESPONSE;
	eap->id = info->eap_id;
	info->eap_len = sizeof(struct eap_frame) + sizeof(struct eap_body);
	body->type = EAP_TYPE_MD5_CHALLENGE;
	data = (u8 *)(body + 1);
	info->eap_len += 17;
#if 0
	sprintf((char *) &data[17], "testing");
	info->eap_len += 7;
#endif
	eap->len = htons(info->eap_len);

	get_radius_id(info);
	prep_radius_msg(info->frame, info, RADIUS_CODE_ACCESS_REQUEST,
		info->id);
}  /* prep_access_challenge_req */

static void prep_access_req(struct radius_info *info)
{
	get_radius_id(info);
	prep_radius_msg(info->frame, info, RADIUS_CODE_ACCESS_REQUEST,
		info->id);
}  /* prep_access_req */

static void send_access_req(struct auth_info *info)
{
	prep_access_req(&info->radius);
#if 0
	info->eap_radius_req = 1;
#endif
	send_radius(radius_fd, info->radius.frame,
		info->radius.len, (SA *) &radius_addr,
		sizeof(radius_addr));
#if 0
	wait_for_resp(info);
#endif
}  /* send_access_req */


static void prep_access_accept_simple_rsp(struct radius_info *info)
{
	info->name_len = strlen((char *) info->name);

	info->password_len = 0;

	sprintf((char *) info->msg, "Hello, %s", info->name);
	info->msg_len = strlen((char *) info->msg);

	info->state_len = 0;

	info->eap_len = 0;

	prep_radius_msg(info->frame, info, RADIUS_CODE_ACCESS_ACCEPT,
		info->id);
}  /* prep_access_accept_simple_rsp */

static void prep_access_accept_rsp(struct radius_info *info)
{
	struct eap_frame *eap = (struct eap_frame *) info->eap;

	info->name_len = strlen((char *) info->name);

	info->password_len = 0;

	sprintf((char *) info->msg, "Hello, %s", info->name);
	info->msg_len = strlen((char *) info->msg);

	info->state_len = 0;

	eap->code = EAP_CODE_SUCCESS;
	eap->id = ++info->eap_id;
	info->eap_len = sizeof(struct eap_frame);
	eap->len = htons(info->eap_len);

	prep_radius_msg(info->frame, info, RADIUS_CODE_ACCESS_ACCEPT,
		info->id);
}  /* prep_access_accept_rsp */

static void prep_access_challenge_rsp(struct radius_info *info)
{
	struct eap_frame *eap = (struct eap_frame *) info->eap;
	struct eap_body *body = (struct eap_body *)(eap + 1);
	u8 *data;

	info->name_len = 0;

	strcpy((char *) info->msg, "Hello, %u");
	info->msg_len = 9;

	info->password_len = 0;

	info->state_len = 16;
	memset(info->state, 0xAC, 16);

	eap->code = EAP_CODE_REQUEST;
	eap->id = ++info->eap_id;
	info->eap_len = sizeof(struct eap_frame) + sizeof(struct eap_body);
	body->type = EAP_TYPE_MD5_CHALLENGE;
	data = (u8 *)(body + 1);
	data[0] = 16;
	memset(&data[1], 0xAA, 16);
	info->eap_len += 17;
	eap->len = htons(info->eap_len);

	prep_radius_msg(info->frame, info, RADIUS_CODE_ACCESS_CHALLENGE,
		info->id);
}  /* prep_access_challenge_rsp */

static int resp_radius_msg(struct radius_info *radius)
{
	int ret = 0;

	if (RADIUS_CODE_ACCESS_REQUEST == radius->code) {
		if (EAP_CODE_RESPONSE == radius->eap_code) {
			if (EAP_TYPE_IDENTITY == radius->eap_type) {
				prep_access_challenge_rsp(radius);
				ret = 1;
			} else if (EAP_TYPE_MD5_CHALLENGE == radius->eap_type) {
				if (memcmp(radius->packet.state,
				    radius->original.state,
				    radius->state_len)) {
					return 0;
				}
				prep_access_accept_rsp(radius);
				ret = 1;
			}
		} else if (!memcmp(radius->password, "password",
			   radius->password_len)) {
			prep_access_accept_simple_rsp(radius);
			ret = 1;
		}
	}
	if (RADIUS_CODE_ACCESS_CHALLENGE == radius->code) {
		if (EAP_CODE_REQUEST == radius->eap_code) {
			if (EAP_TYPE_MD5_CHALLENGE == radius->eap_type) {
				prep_access_challenge_req(radius);
				ret = 1;
			}
		}
	}
	return ret;
}  /* resp_radius_msg */

static void prep_init_req(struct radius_frame *radius,
	struct radius_info *info)
{
	struct eap_frame *eap = (struct eap_frame *) info->eap;
	struct eap_body *body = (struct eap_body *)(eap + 1);

	info->src[0] = 0xff;
	info->dst[0] = 0xff;

	eap->code = EAP_CODE_REQUEST;
	eap->id = info->eap_id;
	body->type = EAP_TYPE_IDENTITY;
	info->eap_len = sizeof(struct eap_frame) + sizeof(struct eap_body);
	eap->len = htons(info->eap_len);
	prep_radius_msg(radius, info, RADIUS_CODE_ACCESS_REQUEST, info->id);
}  /* prep_init_req */

static void prep_success(struct radius_frame *radius,
	struct radius_info *info)
{
	struct eap_frame *eap = (struct eap_frame *) info->eap;

	memset(info, 0, sizeof(struct radius_info));
	info->frame = (struct radius_frame *) info->radius_data;
	info->src[0] = 0xff;
	info->dst[0] = 0xff;

	eap->code = EAP_CODE_SUCCESS;
	eap->id = info->id++;
	info->eap_len = sizeof(struct eap_frame);
	eap->len = htons(info->eap_len);
	prep_radius_msg(radius, info, RADIUS_CODE_ACCESS_ACCEPT, 0);
}  /* prep_success */

static void prep_fail(struct radius_frame *radius,
	struct radius_info *info)
{
	struct eap_frame *eap = (struct eap_frame *) info->eap;

	memset(info, 0, sizeof(struct radius_info));
	info->frame = (struct radius_frame *) info->radius_data;
	info->src[0] = 0xff;
	info->dst[0] = 0xff;

	eap->code = EAP_CODE_FAILURE;
	eap->id = info->id++;
	info->eap_len = sizeof(struct eap_frame);
	eap->len = htons(info->eap_len);
	prep_radius_msg(radius, info, RADIUS_CODE_ACCESS_ACCEPT, 0);
}  /* prep_fail */


#define txCannedSuccess()	send_success(info, info->eapol, info->eap_id++)

#define txCannedFail()		send_failure(info, info->eapol, info->eap_id++)

#define txReq()			send_auth_req(info)

#define sendRespToServer(void)	send_access_req(info)

void abortAuth(void)
{}

#define txStart()		send_start(info, info->eapol)

#define txLogoff()		send_logoff(info, info->eapol)

void abortSupp(void)
{}

#define getSuppRsp()		proc_auth_req(info)

#define txSuppRsp()		send_supp_resp(info)

void txKey(void)
{}

void txSuppKey(void)
{}

void processKey(void)
{}


typedef struct {
	int fTaskStop;
	int fd[NUM_OF_PORTS + 1];
	int port;
	int *msgs;
	struct auth_info *info;

#if defined(_WIN32)
	HANDLE hevTaskComplete;
#endif
} TTaskParam, *PTTaskParam;


#if 0
static int test_port = 1;

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
#endif

static int sw_host_port;

static int get_host_port(void)
{
	char sysfs[80];
	char buf[20];
	int fd;
	int n;
	int ret = 0;

	sprintf(sysfs, "%s/host_port", drvname);
	fd = open(sysfs, O_RDONLY);
	if (fd > 0) {
		n = read(fd, buf, 20);
		buf[n] = '\0';
		ret = atoi(buf);
		close(fd);
	}
	return ret;
}  /* get_host_port */

static void authorize_port(struct auth_info *info, int enable)
{
	char sysfs[80];
	char buf[20];
	int fd;
	int n;
	int p = info->port;

	if (sw_host_port && p >= sw_host_port - 1)
		p++;
	sprintf(sysfs, "%s%d/%d_authen_mode", drvname, p, p);
	fd = open(sysfs, O_RDWR);
	if (fd > 0) {
		if (enable)
			buf[0] = '0';
		else
			buf[0] = '1';
		buf[1] = '\0';
		n = write(fd, buf, 2);
		close(fd);
	}
}  /* authorize_port */

static int chk_port(struct auth_info *info)
{
	char sysfs[80];
	char buf[20];
	int fd;
	int n;
	int p = info->port;
	int ret = 0;

	if (sw_host_port && p >= sw_host_port - 1)
		p++;
	sprintf(sysfs, "%s%d/%d_speed", drvname, p, p);
	fd = open(sysfs, O_RDONLY);
	if (fd > 0) {
		n = read(fd, buf, 20);
		if (n > 2 && '0' == buf[1])
			ret = 1;
		close(fd);
	}
	return ret;
}  /* chk_port */

u32 proc_radius(struct auth_info *info)
{
	u32 update = 0;

	switch (info->radius.eap_code) {
	case EAP_CODE_REQUEST:
		info->eap_req = 1;
		eapReq = TRUE;
		update |= AUTH_PAE_STATE_MACHINE;
		update |= AUTH_BKE_STATE_MACHINE;
		break;
	case EAP_CODE_SUCCESS:
		info->eap_req = 2;
		eapSuccess = TRUE;
		update |= AUTH_PAE_STATE_MACHINE;
		update |= AUTH_BKE_STATE_MACHINE;
		break;
	case EAP_CODE_FAILURE:
		info->eap_req = 3;
		eapFail = TRUE;
		update |= AUTH_PAE_STATE_MACHINE;
		update |= AUTH_BKE_STATE_MACHINE;
		break;
	default:
		eapNoReq = TRUE;
		update |= AUTH_BKE_STATE_MACHINE;
		break;
	}
	eapResp = FALSE;
	return update;
}  /* proc_radius */


struct auth_state {
	int change;
	int new_state;
};

static void auth_pae_init_init(struct auth_info *info,
	struct auth_state *state)
{
#ifdef DBG_STATE
printf(" %s:%d\n", __func__, info->port);
#endif
	portMode = Auto;
}  /* auth_pae_init_init */

static void auth_pae_init_next(struct auth_info *info,
	struct auth_state *state)
{
#ifdef DBG_STATE
printf(" %s:%d i:%d e:%d\n", __func__, info->port, initialize, portEnabled);
#endif
	if (!(initialize || !portEnabled))
		state->new_state = AUTH_PAE_DISCONNECTED;
}  /* auth_pae_init_next */

static void auth_pae_disc_init(struct auth_info *info,
	struct auth_state *state)
{
#ifdef DBG_STATE
printf(" %s:%d\n", __func__, info->port);
#endif
	if (authPortStatus == Authorized)
		authorize_port(info, FALSE);
	authPortStatus = Unauthorized;
	reAuthCount = 0;
	eapolLogoff = FALSE;
}  /* auth_pae_disc_init */

static void auth_pae_disc_next(struct auth_info *info,
	struct auth_state *state)
{
	state->new_state = AUTH_PAE_RESTART;
}  /* auth_pae_disc_next */

static void auth_pae_restart_init(struct auth_info *info,
	struct auth_state *state)
{
#ifdef DBG_STATE
printf(" %s:%d\n", __func__, info->port);
#endif
	eapRestart = TRUE;
}  /* auth_pae_restart_init */

static void auth_pae_restart_next(struct auth_info *info,
	struct auth_state *state)
{
	if (!eapRestart)
		state->new_state = AUTH_PAE_CONNECTING;
}  /* auth_pae_restart_next */

static void auth_pae_conn_init(struct auth_info *info,
	struct auth_state *state)
{
#ifdef DBG_STATE
printf(" %s:%d %d\n", __func__, info->port, reAuthCount);
#endif
	reAuthenticate = FALSE;
	++reAuthCount;
}  /* auth_pae_conn_init */

static void auth_pae_conn_next(struct auth_info *info,
	struct auth_state *state)
{
	if (eapolLogoff || (reAuthCount > reAuthMax))
		state->new_state = AUTH_PAE_DISCONNECTED;
	if ((eapReq && (reAuthCount <= reAuthMax)) ||
	    eapSuccess || eapFail)
		state->new_state = AUTH_PAE_AUTHENTICATING;
}  /* auth_pae_conn_next */

static void auth_pae_authg_init(struct auth_info *info,
	struct auth_state *state)
{
#ifdef DBG_STATE
printf(" %s:%d\n", __func__, info->port);
#endif
	eapolStart = FALSE;
	authSuccess = FALSE;
	authFail = FALSE;
	authTimeout = FALSE;

	/* Signal authStart for Backend IDLE. */
	authStart = TRUE;
	info->update |= AUTH_BKE_STATE_MACHINE;

	keyRun = FALSE;
	keyDone = FALSE;
}  /* auth_pae_authg_init */

static void auth_pae_authg_next(struct auth_info *info,
	struct auth_state *state)
{
	if (eapolStart || eapolLogoff || authTimeout)
		state->new_state = AUTH_PAE_ABORTING;
	if (authFail || (keyDone && !portValid))
		state->new_state = AUTH_PAE_HELD;
	if (authSuccess && portValid)
		state->new_state = AUTH_PAE_AUTHENTICATED;
}  /* auth_pae_authg_next */

static void auth_pae_authd_init(struct auth_info *info,
	struct auth_state *state)
{
#ifdef DBG_STATE
printf(" %s:%d\n", __func__, info->port);
#endif
	if (authPortStatus == Unauthorized)
		authorize_port(info, TRUE);
	authPortStatus = Authorized;
	reAuthCount = 0;
}  /* auth_pae_authd_init */

static void auth_pae_authd_next(struct auth_info *info,
	struct auth_state *state)
{
	if (eapolStart || reAuthenticate)
		state->new_state = AUTH_PAE_RESTART;
	if (eapolLogoff || !portValid)
		state->new_state = AUTH_PAE_DISCONNECTED;
}  /* auth_pae_authd_next */

static void auth_pae_abort_init(struct auth_info *info,
	struct auth_state *state)
{
#ifdef DBG_STATE
printf(" %s:%d\n", __func__, info->port);
#endif
	/* Signal authAbort for Backend. */
	authAbort = TRUE;
	info->update |= AUTH_BKE_STATE_MACHINE;

	keyRun = FALSE;
	keyDone = FALSE;
}  /* auth_pae_abort_init */

static void auth_pae_abort_next(struct auth_info *info,
	struct auth_state *state)
{
	if (!eapolLogoff && !authAbort)
		state->new_state = AUTH_PAE_RESTART;
	if (eapolLogoff && !authAbort)
		state->new_state = AUTH_PAE_DISCONNECTED;
}  /* auth_pae_abort_next */

static void auth_pae_held_init(struct auth_info *info,
	struct auth_state *state)
{
#ifdef DBG_STATE
printf(" %s:%d\n", __func__, info->port);
#endif
	if (authPortStatus == Authorized)
		authorize_port(info, FALSE);
	authPortStatus = Unauthorized;
	quietWhile = quietPeriod;
	eapolLogoff = FALSE;
}  /* auth_pae_held_init */

static void auth_pae_held_next(struct auth_info *info,
	struct auth_state *state)
{
	if (0 == quietWhile)
		state->new_state = AUTH_PAE_RESTART;
}  /* auth_pae_held_next */

static void auth_pae_force_auth_init(struct auth_info *info,
	struct auth_state *state)
{
#ifdef DBG_STATE
printf(" %s:%d\n", __func__, info->port);
#endif
	if (authPortStatus == Unauthorized)
		authorize_port(info, TRUE);
	authPortStatus = Authorized;
	portMode = ForceAuthorized;
	eapolStart = FALSE;
	txCannedSuccess();
}  /* auth_pae_for_auth_init_init */

static void auth_pae_force_auth_next(struct auth_info *info,
	struct auth_state *state)
{
	if (eapolStart)
		state->new_state = AUTH_PAE_FORCE_AUTH;
}  /* auth_pae_force_auth_next */

static void auth_pae_force_unauth_init(struct auth_info *info,
	struct auth_state *state)
{
#ifdef DBG_STATE
printf(" %s:%d\n", __func__, info->port);
#endif
	if (authPortStatus == Authorized)
		authorize_port(info, FALSE);
	authPortStatus = Unauthorized;
	portMode = ForceUnauthorized;
	eapolStart = FALSE;
	txCannedFail();
}  /* auth_pae_for_unauth_init_init */

static void auth_pae_force_unauth_next(struct auth_info *info,
	struct auth_state *state)
{
	if (eapolStart)
		state->new_state = AUTH_PAE_FORCE_UNAUTH;
}  /* auth_pae_force_unauth_next */

static void auth_pae_next(struct auth_info *info,
	struct auth_state *state)
{
	int new_state = state->new_state;

	if (new_state)
		return;
	if (((portControl == Auto) && (portMode != portControl)) ||
	    initialize || !portEnabled)
		state->new_state = AUTH_PAE_INITIALIZE;
	if ((portControl == ForceAuthorized) && (portMode != portControl) &&
	    !(initialize || !portEnabled))
		state->new_state = AUTH_PAE_FORCE_AUTH;
	if ((portControl == ForceUnauthorized) && (portMode != portControl) &&
	    !(initialize || !portEnabled))
		state->new_state = AUTH_PAE_FORCE_UNAUTH;
	if (!new_state && state->new_state == info->auth_pae_state)
		state->new_state = 0;
}  /* auth_pae_next */


static void auth_bke_req_init(struct auth_info *info,
	struct auth_state *state)
{
#ifdef DBG_STATE
printf(" %s:%d\n", __func__, info->port);
#endif

#if 1
	/* Not sure where to reset eapTimeout. */
	eapTimeout = FALSE;
#endif
	txReq();
	eapReq = FALSE;
}  /* auth_bke_req_init */

static void auth_bke_req_next(struct auth_info *info,
	struct auth_state *state)
{
	if (eapTimeout)
		state->new_state = AUTH_BKE_TIMEOUT;
	if (eapolEap)
		state->new_state = AUTH_BKE_RESPONSE;
	if (eapReq)
		state->new_state = AUTH_BKE_REQUEST;
}  /* auth_bke_req_next */

static void auth_bke_resp_init(struct auth_info *info,
	struct auth_state *state)
{
#ifdef DBG_STATE
printf(" %s:%d\n", __func__, info->port);
#endif
	authTimeout = FALSE;
	eapolEap = FALSE;
	eapNoReq = FALSE;
	aWhile = serverTimeout;
	eapResp = TRUE;
	sendRespToServer();
}  /* auth_bke_resp_init */

static void auth_bke_resp_next(struct auth_info *info,
	struct auth_state *state)
{
	if (0 == aWhile)
		state->new_state = AUTH_BKE_TIMEOUT;
	if (eapSuccess)
		state->new_state = AUTH_BKE_SUCCESS;
	if (eapFail)
		state->new_state = AUTH_BKE_FAIL;
	if (eapNoReq)
		state->new_state = AUTH_BKE_IGNORE;
	if (eapReq)
		state->new_state = AUTH_BKE_REQUEST;
}  /* auth_bke_resp_next */

static void auth_bke_succ_init(struct auth_info *info,
	struct auth_state *state)
{
#ifdef DBG_STATE
printf(" %s:%d\n", __func__, info->port);
#endif
	txReq();

	/* Signal authSuccess for PAE AUTHENTICATING. */
	authSuccess = TRUE;
	info->update |= AUTH_PAE_STATE_MACHINE;

	keyRun = TRUE;
}  /* auth_bke_succ_init */

static void auth_bke_succ_next(struct auth_info *info,
	struct auth_state *state)
{
	state->new_state = AUTH_BKE_IDLE;
}  /* auth_bke_succ_next */

static void auth_bke_fail_init(struct auth_info *info,
	struct auth_state *state)
{
#ifdef DBG_STATE
printf(" %s:%d\n", __func__, info->port);
#endif
	txReq();

	/* Signal authFail for PAE AUTHENTICATING. */
	authFail = TRUE;
	info->update |= AUTH_PAE_STATE_MACHINE;
}  /* auth_bke_fail_init */

static void auth_bke_fail_next(struct auth_info *info,
	struct auth_state *state)
{
	state->new_state = AUTH_BKE_IDLE;
}  /* auth_bke_fail_next */

static void auth_bke_timeout_init(struct auth_info *info,
	struct auth_state *state)
{
#ifdef DBG_STATE
printf(" %s:%d\n", __func__, info->port);
#endif
	/* Signal authTimeout for PAE AUTHENTICATING. */
	authTimeout = TRUE;
	info->update |= AUTH_PAE_STATE_MACHINE;
}  /* auth_bke_timeout_init */

static void auth_bke_timeout_next(struct auth_info *info,
	struct auth_state *state)
{
	state->new_state = AUTH_BKE_IDLE;
}  /* auth_bke_timeout_next */

static void auth_bke_idle_init(struct auth_info *info,
	struct auth_state *state)
{
#ifdef DBG_STATE
printf(" %s:%d\n", __func__, info->port);
#endif
	/* Wait for authStart in PAE AUTHENTICATING. */
	authStart = FALSE;
}  /* auth_bke_idle_init */

static void auth_bke_idle_next(struct auth_info *info,
	struct auth_state *state)
{
	if (eapReq && authStart)
		state->new_state = AUTH_BKE_REQUEST;
	if (eapSuccess && authStart)
		state->new_state = AUTH_BKE_SUCCESS;
	if (eapFail && authStart)
		state->new_state = AUTH_BKE_FAIL;
}  /* auth_bke_idle_next */

static void auth_bke_init_init(struct auth_info *info,
	struct auth_state *state)
{
#ifdef DBG_STATE
printf(" %s:%d\n", __func__, info->port);
#endif
	abortAuth();
	eapNoReq = FALSE;

	/* Reset authAbort for PAE ABORT. */
	authAbort = FALSE;
	info->update |= AUTH_PAE_STATE_MACHINE;
}  /* auth_bke_init_init */

static void auth_bke_init_next(struct auth_info *info,
	struct auth_state *state)
{
	if (!((portControl != Auto) || initialize || authAbort))
		state->new_state = AUTH_BKE_IDLE;
}  /* auth_bke_init_next */

static void auth_bke_ignore_init(struct auth_info *info,
	struct auth_state *state)
{
#ifdef DBG_STATE
printf(" %s:%d\n", __func__, info->port);
#endif
	eapNoReq = FALSE;
}  /* auth_bke_ignore_init */

static void auth_bke_ignore_next(struct auth_info *info,
	struct auth_state *state)
{
	if (eapolEap)
		state->new_state = AUTH_BKE_RESPONSE;
	if (eapReq)
		state->new_state = AUTH_BKE_REQUEST;
	if (eapTimeout)
		state->new_state = AUTH_BKE_TIMEOUT;
}  /* auth_bke_ignore_next */

static void auth_bke_next(struct auth_info *info,
	struct auth_state *state)
{
	int new_state = state->new_state;

	if (new_state)
		return;
	if ((portControl != Auto) || initialize || authAbort)
		state->new_state = AUTH_BKE_INITIALIZE;
	if (!new_state && state->new_state == info->auth_bke_state)
		state->new_state = 0;
}  /* auth_bke_next */


static void supp_pae_logoff_init(struct auth_info *info,
	struct auth_state *state)
{
#ifdef DBG_STATE
printf(" %s:%d\n", __func__, info->port);
#endif
	txLogoff();
	logoffSent = TRUE;
	suppPortStatus = Unauthorized;
}  /* supp_pae_logoff_init */

static void supp_pae_logoff_next(struct auth_info *info,
	struct auth_state *state)
{
	if (!userLogoff)
		state->new_state = SUPP_PAE_DISCONNECTED;
}  /* supp_pae_logoff_next */

static void supp_pae_disc_init(struct auth_info *info,
	struct auth_state *state)
{
#ifdef DBG_STATE
printf(" %s:%d\n", __func__, info->port);
#endif
	sPortMode = Auto;
	startCount = 0;
	logoffSent = FALSE;
	suppPortStatus = Unauthorized;

	/* Signal suppAbort for Backend. */
	suppAbort = TRUE;
	info->update |= SUPP_BKE_STATE_MACHINE;
}  /* supp_pae_disc_init */

static void supp_pae_disc_next(struct auth_info *info,
	struct auth_state *state)
{
	if (!(initialize || !portEnabled))
		state->new_state = SUPP_PAE_CONNECTING;
}  /* supp_pae_disc_next */

static void supp_pae_conn_init(struct auth_info *info,
	struct auth_state *state)
{
#ifdef DBG_STATE
printf(" %s:%d\n", __func__, info->port);
#endif
	startWhen = startPeriod;
	++startCount;
	eapolEap = FALSE;
	txStart();
}  /* supp_pae_conn_init */

static void supp_pae_conn_next(struct auth_info *info,
	struct auth_state *state)
{
	if (eapolEap)
		state->new_state = SUPP_PAE_RESTART;
	if (eapSuccess || eapFail)
		state->new_state = SUPP_PAE_AUTHENTICATING;
	if ((0 == startWhen) && (startCount >= maxStart) && portValid)
		state->new_state = SUPP_PAE_AUTHENTICATED;
	if ((0 == startWhen) && (startCount >= maxStart) && !portValid)
		state->new_state = SUPP_PAE_HELD;
	if ((0 == startWhen) && (startCount < maxStart))
		state->new_state = SUPP_PAE_CONNECTING;
}  /* supp_pae_conn_next */

static void supp_pae_authg_init(struct auth_info *info,
	struct auth_state *state)
{
#ifdef DBG_STATE
printf(" %s:%d\n", __func__, info->port);
#endif
	startCount = 0;
	suppSuccess = FALSE;
	suppFail = FALSE;
	suppTimeout = FALSE;
	keyRun = FALSE;
	keyDone = FALSE;

	/* Signal suppStart for Backend IDLE. */
	suppStart = TRUE;
	info->update |= SUPP_BKE_STATE_MACHINE;
}  /* supp_pae_authg_init */

static void supp_pae_authg_next(struct auth_info *info,
	struct auth_state *state)
{
	if (suppSuccess && portValid)
		state->new_state = SUPP_PAE_AUTHENTICATED;
	if (suppFail || (keyDone && !portValid))
		state->new_state = SUPP_PAE_HELD;
	if (suppTimeout)
		state->new_state = SUPP_PAE_CONNECTING;
}  /* supp_pae_authg_next */

static void supp_pae_held_init(struct auth_info *info,
	struct auth_state *state)
{
#ifdef DBG_STATE
printf(" %s:%d\n", __func__, info->port);
#endif
	heldWhile = heldPeriod;
	suppPortStatus = Unauthorized;
}  /* supp_pae_held_init */

static void supp_pae_held_next(struct auth_info *info,
	struct auth_state *state)
{
	if (eapolEap)
		state->new_state = SUPP_PAE_RESTART;
	if (0 == heldWhile)
		state->new_state = SUPP_PAE_CONNECTING;
}  /* supp_pae_held_next */

static void supp_pae_authd_init(struct auth_info *info,
	struct auth_state *state)
{
#ifdef DBG_STATE
printf(" %s:%d\n", __func__, info->port);
#endif
	suppPortStatus = Authorized;
}  /* supp_pae_authd_init */

static void supp_pae_authd_next(struct auth_info *info,
	struct auth_state *state)
{
	if (eapolEap && portValid)
		state->new_state = SUPP_PAE_RESTART;
	if (!portValid)
		state->new_state = SUPP_PAE_DISCONNECTED;
}  /* supp_pae_authd_next */

static void supp_pae_restart_init(struct auth_info *info,
	struct auth_state *state)
{
#ifdef DBG_STATE
printf(" %s:%d\n", __func__, info->port);
#endif
	eapRestart = TRUE;
}  /* supp_pae_restart_init */

static void supp_pae_restart_next(struct auth_info *info,
	struct auth_state *state)
{
	if (!eapRestart)
		state->new_state = SUPP_PAE_AUTHENTICATING;
}  /* supp_pae_restart_next */

static void supp_pae_s_force_auth_init(struct auth_info *info,
	struct auth_state *state)
{
#ifdef DBG_STATE
printf(" %s:%d\n", __func__, info->port);
#endif
	suppPortStatus = Authorized;
	sPortMode = ForceAuthorized;
}  /* supp_pae_s_for_auth_init_init */

#if 0
static void supp_pae_s_force_auth_next(struct auth_info *info,
	struct auth_state *state)
{
}  /* supp_pae_s_force_auth_next */
#endif

static void supp_pae_s_force_unauth_init(struct auth_info *info,
	struct auth_state *state)
{
#ifdef DBG_STATE
printf(" %s:%d\n", __func__, info->port);
#endif
	suppPortStatus = Unauthorized;
	sPortMode = ForceUnauthorized;
	txLogoff();
}  /* supp_pae_s_for_unauth_init_init */

#if 0
static void supp_pae_s_force_unauth_next(struct auth_info *info,
	struct auth_state *state)
{
}  /* supp_pae_s_force_unauth_next */
#endif

static void supp_pae_next(struct auth_info *info,
	struct auth_state *state)
{
	int new_state = state->new_state;

	if (new_state)
		return;
	if ((userLogoff && !logoffSent) && !(initialize || !portEnabled))
		state->new_state = SUPP_PAE_LOGOFF;
	if (((portControl == Auto) && (sPortMode != portControl)) ||
	    initialize || !portEnabled)
		state->new_state = SUPP_PAE_DISCONNECTED;
	if ((portControl == ForceAuthorized) && (sPortMode != portControl) &&
	    !(initialize || !portEnabled))
		state->new_state = SUPP_PAE_S_FORCE_AUTH;
	if ((portControl == ForceUnauthorized) && (sPortMode != portControl) &&
	    !(initialize || !portEnabled))
		state->new_state = SUPP_PAE_S_FORCE_UNAUTH;
	if (!new_state && state->new_state == info->supp_pae_state)
		state->new_state = 0;
}  /* supp_pae_next */


static void supp_bke_req_init(struct auth_info *info,
	struct auth_state *state)
{
#ifdef DBG_STATE
printf(" %s:%d\n", __func__, info->port);
#endif
	authWhile = 0;
	eapReq = TRUE;
	getSuppRsp();
}  /* supp_bke_req_init */

static void supp_bke_req_next(struct auth_info *info,
	struct auth_state *state)
{
	if (eapResp)
		state->new_state = SUPP_BKE_RESPONSE;
	if (eapNoResp)
		state->new_state = SUPP_BKE_RECEIVE;
	if (eapFail)
		state->new_state = SUPP_BKE_FAIL;
	if (eapSuccess)
		state->new_state = SUPP_BKE_SUCCESS;
}  /* supp_bke_req_next */

static void supp_bke_resp_init(struct auth_info *info,
	struct auth_state *state)
{
#ifdef DBG_STATE
printf(" %s:%d\n", __func__, info->port);
#endif
	txSuppRsp();
	eapResp = FALSE;
}  /* supp_bke_resp_init */

static void supp_bke_resp_next(struct auth_info *info,
	struct auth_state *state)
{
	state->new_state = SUPP_BKE_RECEIVE;
}  /* supp_bke_resp_next */

static void supp_bke_succ_init(struct auth_info *info,
	struct auth_state *state)
{
#ifdef DBG_STATE
printf(" %s:%d\n", __func__, info->port);
#endif
	keyRun = TRUE;

	/* Signal suppSuccess for PAE AUTHENTICATING. */
	suppSuccess = TRUE;
	info->update |= SUPP_PAE_STATE_MACHINE;
}  /* supp_bke_succ_init */

static void supp_bke_succ_next(struct auth_info *info,
	struct auth_state *state)
{
	state->new_state = SUPP_BKE_IDLE;
}  /* supp_bke_succ_next */

static void supp_bke_fail_init(struct auth_info *info,
	struct auth_state *state)
{
#ifdef DBG_STATE
printf(" %s:%d\n", __func__, info->port);
#endif
	/* Signal suppFail for PAE AUTHENTICATING. */
	suppFail = TRUE;
	info->update |= SUPP_PAE_STATE_MACHINE;
}  /* supp_bke_fail_init */

static void supp_bke_fail_next(struct auth_info *info,
	struct auth_state *state)
{
	state->new_state = SUPP_BKE_IDLE;
}  /* supp_bke_fail_next */

static void supp_bke_timeout_init(struct auth_info *info,
	struct auth_state *state)
{
#ifdef DBG_STATE
printf(" %s:%d\n", __func__, info->port);
#endif
	/* Signal suppTimeout for PAE AUTHENTICATING. */
	suppTimeout = TRUE;
	info->update |= SUPP_PAE_STATE_MACHINE;
}  /* supp_bke_timeout_init */

static void supp_bke_timeout_next(struct auth_info *info,
	struct auth_state *state)
{
	state->new_state = SUPP_BKE_IDLE;
}  /* supp_bke_timeout_next */

static void supp_bke_idle_init(struct auth_info *info,
	struct auth_state *state)
{
#ifdef DBG_STATE
printf(" %s:%d\n", __func__, info->port);
#endif
	/* Wait for PAE AUTHENTICATING. */
	suppStart = FALSE;
}  /* supp_bke_idle_init */

static void supp_bke_idle_next(struct auth_info *info,
	struct auth_state *state)
{
	if (eapolEap && suppStart)
		state->new_state = SUPP_BKE_REQUEST;
	if (eapSuccess && suppStart)
		state->new_state = SUPP_BKE_SUCCESS;
	if (eapFail && suppStart)
		state->new_state = SUPP_BKE_FAIL;
}  /* supp_bke_idle_next */

static void supp_bke_init_init(struct auth_info *info,
	struct auth_state *state)
{
#ifdef DBG_STATE
printf(" %s:%d\n", __func__, info->port);
#endif
	abortSupp();
	suppAbort = FALSE;
}  /* supp_bke_init_init */

static void supp_bke_init_next(struct auth_info *info,
	struct auth_state *state)
{
	if (!(initialize || suppAbort))
		state->new_state = SUPP_BKE_IDLE;
}  /* supp_bke_init_next */

static void supp_bke_recv_init(struct auth_info *info,
	struct auth_state *state)
{
#ifdef DBG_STATE
printf(" %s:%d\n", __func__, info->port);
#endif
	authWhile = authPeriod;
	eapolEap = FALSE;
	eapNoResp = FALSE;
}  /* supp_bke_recv_init */

static void supp_bke_recv_next(struct auth_info *info,
	struct auth_state *state)
{
	if (0 == authWhile)
		state->new_state = SUPP_BKE_TIMEOUT;
	if (eapSuccess)
		state->new_state = SUPP_BKE_SUCCESS;
	if (eapFail)
		state->new_state = SUPP_BKE_FAIL;
	if (eapolEap)
		state->new_state = SUPP_BKE_REQUEST;
}  /* supp_bke_recv_next */

static void supp_bke_next(struct auth_info *info,
	struct auth_state *state)
{
	int new_state = state->new_state;

	if (new_state)
		return;
	if (initialize || suppAbort)
		state->new_state = SUPP_BKE_INITIALIZE;
	if (!new_state && state->new_state == info->supp_bke_state)
		state->new_state = 0;
}  /* supp_bke_next */


static void auth_key_no_tx_init(struct auth_info *info,
	struct auth_state *state)
{
#ifdef DBG_STATE
printf(" %s:%d\n", __func__, info->port);
#endif
}  /* auth_key_no_tx_init */

static void auth_key_no_tx_next(struct auth_info *info,
	struct auth_state *state)
{
	if (!(initialize || (portControl != Auto)) && keyTxEnabled &&
	    keyAvailable && keyRun)
		state->new_state = AUTH_KEY_TRANSMIT;
}  /* auth_key_no_tx_next */

static void auth_key_tx_init(struct auth_info *info,
	struct auth_state *state)
{
#ifdef DBG_STATE
printf(" %s:%d\n", __func__, info->port);
#endif
	txKey();
	keyAvailable = FALSE;
	keyDone = TRUE;
}  /* auth_key_tx_init */

static void auth_key_tx_next(struct auth_info *info,
	struct auth_state *state)
{
	if (keyAvailable)
		state->new_state = AUTH_KEY_TRANSMIT;
	if (!keyTxEnabled || !keyRun)
		state->new_state = AUTH_KEY_NO_TRANSMIT;
}  /* auth_key_tx_next */

static void auth_key_next(struct auth_info *info,
	struct auth_state *state)
{
	int new_state = state->new_state;

	if (initialize || (portControl != Auto))
		state->new_state = AUTH_KEY_NO_TRANSMIT;
	if (!new_state && state->new_state == info->auth_key_tx_state)
		state->new_state = 0;
}  /* auth_key_next */


static void supp_key_no_tx_init(struct auth_info *info,
	struct auth_state *state)
{
#ifdef DBG_STATE
printf(" %s:%d\n", __func__, info->port);
#endif
}  /* supp_key_no_tx_init */

static void supp_key_no_tx_next(struct auth_info *info,
	struct auth_state *state)
{
	if (!(initialize || (portControl != Auto)) && keyTxEnabled &&
	    suppKeyAvailable && keyRun)
		state->new_state = SUPP_KEY_TRANSMIT;
}  /* supp_key_no_tx_next */

static void supp_key_tx_init(struct auth_info *info,
	struct auth_state *state)
{
#ifdef DBG_STATE
printf(" %s:%d\n", __func__, info->port);
#endif
	txSuppKey();
	keyAvailable = FALSE;
	keyDone = TRUE;
}  /* supp_key_tx_init */

static void supp_key_tx_next(struct auth_info *info,
	struct auth_state *state)
{
	if (suppKeyAvailable)
		state->new_state = SUPP_KEY_TRANSMIT;
	if (!keyTxEnabled || !keyRun)
		state->new_state = SUPP_KEY_NO_TRANSMIT;
}  /* supp_key_tx_next */

static void supp_key_next(struct auth_info *info,
	struct auth_state *state)
{
	int new_state = state->new_state;

	if (initialize || (portControl != Auto))
		state->new_state = SUPP_KEY_NO_TRANSMIT;
	if (!new_state && state->new_state == info->supp_key_tx_state)
		state->new_state = 0;
}  /* supp_key_next */


static void key_no_rx_init(struct auth_info *info,
	struct auth_state *state)
{
#ifdef DBG_STATE
printf(" %s:%d\n", __func__, info->port);
#endif
}  /* key_no_rx_init */

static void key_no_rx_next(struct auth_info *info,
	struct auth_state *state)
{
	if (!(initialize || (portControl != Auto)) && rxKey)
		state->new_state = KEY_RECEIVE;
}  /* key_no_rx_next */

static void key_rx_init(struct auth_info *info,
	struct auth_state *state)
{
#ifdef DBG_STATE
printf(" %s:%d\n", __func__, info->port);
#endif
	processKey();
	rxKey = FALSE;
}  /* key_rx_init */

static void key_rx_next(struct auth_info *info,
	struct auth_state *state)
{
	if (rxKey)
		state->new_state = KEY_RECEIVE;
}  /* key_rx_next */

static void key_next(struct auth_info *info,
	struct auth_state *state)
{
	int new_state = state->new_state;

	if (initialize || (portControl != Auto))
		state->new_state = KEY_NO_RECEIVE;
	if (!new_state && state->new_state == info->key_rx_state)
		state->new_state = 0;
}  /* key_next */


static void re_auth_init_init(struct auth_info *info,
	struct auth_state *state)
{
#ifdef DBG_STATE
printf(" %s:%d\n", __func__, info->port);
#endif
	reAuthWhen = reAuthPeriod;
}  /* re_auth_init_init */

static void re_auth_init_next(struct auth_info *info,
	struct auth_state *state)
{
	if (!(initialize || (portControl != Auto) ||
	    (portControl == Unauthorized) || !reAuthEnabled) &&
	    (0 == reAuthWhen))
		state->new_state = RE_AUTHENTICATE;
}  /* re_auth_init_next */

static void re_authen_init(struct auth_info *info,
	struct auth_state *state)
{
#ifdef DBG_STATE
printf(" %s:%d\n", __func__, info->port);
#endif
	reAuthenticate = TRUE;
}  /* re_authen_init */

static void re_authen_next(struct auth_info *info,
	struct auth_state *state)
{
	state->new_state = RE_AUTH_INITIALIZE;
}  /* re_authen_next */

static void re_auth_next(struct auth_info *info,
	struct auth_state *state)
{
	int new_state = state->new_state;

	if (initialize || (portControl != Auto) ||
	    (portControl == Unauthorized) || !reAuthEnabled)
		state->new_state = RE_AUTH_INITIALIZE;
	if (!new_state && state->new_state == info->re_auth_state)
		state->new_state = 0;
}  /* re_auth_next */


static int auth_proc_state(struct auth_info *info, struct auth_state *state,
	void (*state_init)(struct auth_info *info, struct auth_state *state),
	void (*state_next)(struct auth_info *info, struct auth_state *state))
{
	if (state->new_state) {
		state->new_state = 0;
		state_init(info, state);
		if (1 == state->change)
			return 1;
	}
	if (state_next)
		state_next(info, state);
	return 0;
}  /* auth_proc_state */

static u32 eap_timers_state_machine(struct auth_info *info)
{
	int i;
	u32 update = 0;

	for (i = 0; i < sizeof(info->eap_timers) / sizeof(int); i++) {

		/* Do not decrement if zero. */
		if (!info->eap_timers[i])
			continue;
		--info->eap_timers[i];
		if (!info->eap_timers[i])
#ifdef DBG_STATE
printf("t: %s:%d\n", timers[i], info->port);
#endif

		/* Signal checking other state machines. */
		if (!info->eap_timers[i])
			update = ALL_STATE_MACHINE;
	}
	return update;
}  /* eap_timers_state_machine */

static void auth_pae_state_machine(struct auth_info *info)
{
	struct auth_state state_info;
	u8 *state = &info->auth_pae_state;

	if (!(info->update & AUTH_PAE_STATE_MACHINE))
		return;
	info->update &= ~AUTH_PAE_STATE_MACHINE;
	state_info.change = 1;
	state_info.new_state = 0;
	do {
		state_info.change--;
		switch (*state) {
		case AUTH_PAE_INITIALIZE:
			if (auth_proc_state(info, &state_info,
			    auth_pae_init_init, auth_pae_init_next))
				goto done;
			break;
		case AUTH_PAE_DISCONNECTED:
			if (auth_proc_state(info, &state_info,
			    auth_pae_disc_init, auth_pae_disc_next))
				goto done;
			break;
		case AUTH_PAE_RESTART:
			if (auth_proc_state(info, &state_info,
			    auth_pae_restart_init, auth_pae_restart_next))
				goto done;
			break;
		case AUTH_PAE_CONNECTING:
			if (auth_proc_state(info, &state_info,
			    auth_pae_conn_init, auth_pae_conn_next))
				goto done;
			break;
		case AUTH_PAE_AUTHENTICATING:
			if (auth_proc_state(info, &state_info,
			    auth_pae_authg_init, auth_pae_authg_next))
				goto done;
			break;
		case AUTH_PAE_AUTHENTICATED:
			if (auth_proc_state(info, &state_info,
			    auth_pae_authd_init, auth_pae_authd_next))
				goto done;
			break;
		case AUTH_PAE_ABORTING:
			if (auth_proc_state(info, &state_info,
			    auth_pae_abort_init, auth_pae_abort_next))
				goto done;
			break;
		case AUTH_PAE_HELD:
			if (auth_proc_state(info, &state_info,
			    auth_pae_held_init, auth_pae_held_next))
				goto done;
			break;
		case AUTH_PAE_FORCE_AUTH:
			if (auth_proc_state(info, &state_info,
			    auth_pae_force_auth_init,
			    auth_pae_force_auth_next))
				goto done;
			break;
		case AUTH_PAE_FORCE_UNAUTH:
			if (auth_proc_state(info, &state_info,
			    auth_pae_force_unauth_init,
			    auth_pae_force_unauth_next))
			break;
		}
		auth_pae_next(info, &state_info);

		/* There is a new state. */
		if (state_info.new_state) {
			*state = state_info.new_state;
			state_info.change++;
		}
	} while (state_info.change);
done:
	return;
}  /* auth_pae_state_machine */

static void auth_bke_state_machine(struct auth_info *info)
{
	struct auth_state state_info;
	u8 *state = &info->auth_bke_state;

	if (!(info->update & AUTH_BKE_STATE_MACHINE))
		return;
	info->update &= ~AUTH_BKE_STATE_MACHINE;
	state_info.change = 1;
	state_info.new_state = 0;
	do {
		state_info.change--;
		switch (*state) {
		case AUTH_BKE_REQUEST:
			if (auth_proc_state(info, &state_info,
			    auth_bke_req_init, auth_bke_req_next))
				goto done;
			break;
		case AUTH_BKE_RESPONSE:
			if (auth_proc_state(info, &state_info,
			    auth_bke_resp_init, auth_bke_resp_next))
				goto done;
			break;
		case AUTH_BKE_SUCCESS:
			if (auth_proc_state(info, &state_info,
			    auth_bke_succ_init, auth_bke_succ_next))
				goto done;
			break;
		case AUTH_BKE_FAIL:
			if (auth_proc_state(info, &state_info,
			    auth_bke_fail_init, auth_bke_fail_next))
				goto done;
			break;
		case AUTH_BKE_TIMEOUT:
			if (auth_proc_state(info, &state_info,
			    auth_bke_timeout_init, auth_bke_timeout_next))
				goto done;
			break;
		case AUTH_BKE_IDLE:
			if (auth_proc_state(info, &state_info,
			    auth_bke_idle_init, auth_bke_idle_next))
				goto done;
			break;
		case AUTH_BKE_INITIALIZE:
			if (auth_proc_state(info, &state_info,
			    auth_bke_init_init, auth_bke_init_next))
				goto done;
			break;
		case AUTH_BKE_IGNORE:
			if (auth_proc_state(info, &state_info,
			    auth_bke_ignore_init, auth_bke_ignore_next))
				goto done;
			break;
		}
		auth_bke_next(info, &state_info);

		/* There is a new state. */
		if (state_info.new_state) {
			*state = state_info.new_state;
			state_info.change++;
		}
	} while (state_info.change);
done:
	return;
}  /* auth_bke_state_machine */

static void supp_pae_state_machine(struct auth_info *info)
{
	struct auth_state state_info;
	u8 *state = &info->supp_pae_state;

	if (!(info->update & SUPP_PAE_STATE_MACHINE))
		return;
	info->update &= ~SUPP_PAE_STATE_MACHINE;
	state_info.change = 1;
	state_info.new_state = 0;
	do {
		state_info.change--;
		switch (*state) {
		case SUPP_PAE_LOGOFF:
			if (auth_proc_state(info, &state_info,
			    supp_pae_logoff_init, supp_pae_logoff_next))
				goto done;
			break;
		case SUPP_PAE_DISCONNECTED:
			if (auth_proc_state(info, &state_info,
			    supp_pae_disc_init, supp_pae_disc_next))
				goto done;
			break;
		case SUPP_PAE_CONNECTING:
			if (auth_proc_state(info, &state_info,
			    supp_pae_conn_init, supp_pae_conn_next))
				goto done;
			break;
		case SUPP_PAE_AUTHENTICATING:
			if (auth_proc_state(info, &state_info,
			    supp_pae_authg_init, supp_pae_authg_next))
				goto done;
			break;
		case SUPP_PAE_HELD:
			if (auth_proc_state(info, &state_info,
			    supp_pae_held_init, supp_pae_held_next))
				goto done;
			break;
		case SUPP_PAE_AUTHENTICATED:
			if (auth_proc_state(info, &state_info,
			    supp_pae_authd_init, supp_pae_authd_next))
				goto done;
			break;
		case SUPP_PAE_RESTART:
			if (auth_proc_state(info, &state_info,
			    supp_pae_restart_init, supp_pae_restart_next))
				goto done;
			break;
		case SUPP_PAE_S_FORCE_AUTH:
			if (auth_proc_state(info, &state_info,
			    supp_pae_s_force_auth_init, NULL))
				goto done;
			break;
		case SUPP_PAE_S_FORCE_UNAUTH:
			if (auth_proc_state(info, &state_info,
			    supp_pae_s_force_unauth_init, NULL))
				goto done;
			break;
		}
		supp_pae_next(info, &state_info);

		/* There is a new state. */
		if (state_info.new_state) {
			*state = state_info.new_state;
			state_info.change++;
		}
	} while (state_info.change);
done:
	return;
}  /* supp_pae_state_machine */

static void supp_bke_state_machine(struct auth_info *info)
{
	struct auth_state state_info;
	u8 *state = &info->supp_bke_state;

	if (!(info->update & SUPP_BKE_STATE_MACHINE))
		return;
	info->update &= ~SUPP_BKE_STATE_MACHINE;
	state_info.change = 1;
	state_info.new_state = 0;
	do {
		state_info.change--;
		switch (*state) {
		case SUPP_BKE_REQUEST:
			if (auth_proc_state(info, &state_info,
			    supp_bke_req_init, supp_bke_req_next))
				goto done;
			break;
		case SUPP_BKE_RESPONSE:
			if (auth_proc_state(info, &state_info,
			    supp_bke_resp_init, supp_bke_resp_next))
				goto done;
			break;
		case SUPP_BKE_SUCCESS:
			if (auth_proc_state(info, &state_info,
			    supp_bke_succ_init, supp_bke_succ_next))
				goto done;
			break;
		case SUPP_BKE_FAIL:
			if (auth_proc_state(info, &state_info,
			    supp_bke_fail_init, supp_bke_fail_next))
				goto done;
			break;
		case SUPP_BKE_TIMEOUT:
			if (auth_proc_state(info, &state_info,
			    supp_bke_timeout_init, supp_bke_timeout_next))
				goto done;
			break;
		case SUPP_BKE_IDLE:
			if (auth_proc_state(info, &state_info,
			    supp_bke_idle_init, supp_bke_idle_next))
				goto done;
			break;
		case SUPP_BKE_INITIALIZE:
			if (auth_proc_state(info, &state_info,
			    supp_bke_init_init, supp_bke_init_next))
				goto done;
			break;
		case SUPP_BKE_RECEIVE:
			if (auth_proc_state(info, &state_info,
			    supp_bke_recv_init, supp_bke_recv_next))
				goto done;
			break;
		}
		supp_bke_next(info, &state_info);

		/* There is a new state. */
		if (state_info.new_state) {
			*state = state_info.new_state;
			state_info.change++;
		}
	} while (state_info.change);
done:
	return;
}  /* supp_bke_state_machine */

static void auth_key_tx_state_machine(struct auth_info *info)
{
	struct auth_state state_info;
	u8 *state = &info->auth_key_tx_state;

	if (!(info->update & AUTH_KEY_STATE_MACHINE))
		return;
	info->update &= ~AUTH_KEY_STATE_MACHINE;
	state_info.change = 1;
	state_info.new_state = 0;
	do {
		state_info.change--;
		switch (*state) {
		case AUTH_KEY_NO_TRANSMIT:
			if (auth_proc_state(info, &state_info,
			    auth_key_no_tx_init, auth_key_no_tx_next))
				goto done;
			break;
		case AUTH_KEY_TRANSMIT:
			if (auth_proc_state(info, &state_info,
			    auth_key_tx_init, auth_key_tx_next))
				goto done;
			break;
		}
		auth_key_next(info, &state_info);

		/* There is a new state. */
		if (state_info.new_state) {
			*state = state_info.new_state;
			state_info.change++;
		}
	} while (state_info.change);
done:
	return;
}  /* auth_key_tx_state_machine */

static void supp_key_tx_state_machine(struct auth_info *info)
{
	struct auth_state state_info;
	u8 *state = &info->supp_key_tx_state;

	if (!(info->update & SUPP_KEY_STATE_MACHINE))
		return;
	info->update &= ~SUPP_KEY_STATE_MACHINE;
	state_info.change = 1;
	state_info.new_state = 0;
	do {
		state_info.change--;
		switch (*state) {
		case SUPP_KEY_NO_TRANSMIT:
			if (auth_proc_state(info, &state_info,
			    supp_key_no_tx_init, supp_key_no_tx_next))
				goto done;
			break;
		case SUPP_KEY_TRANSMIT:
			if (auth_proc_state(info, &state_info,
			    supp_key_tx_init, supp_key_tx_next))
				goto done;
			break;
		}
		supp_key_next(info, &state_info);

		/* There is a new state. */
		if (state_info.new_state) {
			*state = state_info.new_state;
			state_info.change++;
		}
	} while (state_info.change);
done:
	return;
}  /* supp_key_tx_state_machine */

static void key_rx_state_machine(struct auth_info *info)
{
	struct auth_state state_info;
	u8 *state = &info->key_rx_state;

	if (!(info->update & KEY_RX_STATE_MACHINE))
		return;
	info->update &= ~KEY_RX_STATE_MACHINE;
	state_info.change = 1;
	state_info.new_state = 0;
	do {
		state_info.change--;
		switch (*state) {
		case KEY_NO_RECEIVE:
			if (auth_proc_state(info, &state_info,
			    key_no_rx_init, key_no_rx_next))
				goto done;
			break;
		case KEY_RECEIVE:
			if (auth_proc_state(info, &state_info,
			    key_rx_init, key_rx_next))
				goto done;
			break;
		}
		key_next(info, &state_info);

		/* There is a new state. */
		if (state_info.new_state) {
			*state = state_info.new_state;
			state_info.change++;
		}
	} while (state_info.change);
done:
	return;
}  /* key_rx_state_machine */

static void re_auth_state_machine(struct auth_info *info)
{
	struct auth_state state_info;
	u8 *state = &info->re_auth_state;

	if (!(info->update & RE_AUTH_STATE_MACHINE))
		return;
	info->update &= ~RE_AUTH_STATE_MACHINE;
	state_info.change = 1;
	state_info.new_state = 0;
	do {
		state_info.change--;
		switch (*state) {
		case RE_AUTH_INITIALIZE:
			if (auth_proc_state(info, &state_info,
			    re_auth_init_init, re_auth_init_next))
				goto done;
			break;
		case RE_AUTHENTICATE:
			if (auth_proc_state(info, &state_info,
			    re_authen_init, re_authen_next))
				goto done;
			break;
		}
		re_auth_next(info, &state_info);

		/* There is a new state. */
		if (state_info.new_state) {
			*state = state_info.new_state;
			state_info.change++;
		}
	} while (state_info.change);
done:
	return;
}  /* re_auth_state_machine */


static void auth_init(struct auth_info *info)
{
	memset(info, 0, sizeof(struct auth_info));
	info->eapol = (struct eapol_frame *) info->eapol_data;

	/* Initialize constants. */
	quietPeriod = 60;
	reAuthMax = 2;
	serverTimeout = 30;
serverTimeout = 3;
	heldPeriod = 60;
	startPeriod = 30;
	maxStart = 3;
	authPeriod = 30;
	reAuthPeriod = 3600;
	reAuthPeriod = 60;
	reAuthEnabled = TRUE;
}  /* auth_init */

static void auth_ready(struct auth_info *info)
{
	portControl = Auto;
	authPortStatus = Unauthorized;

	initialize = TRUE;
	signal_update(&info->update_sig, &info->update, ALL_STATE_MACHINE);
}  /* auth_ready */

static void auth_start(struct auth_info *info)
{
	while (info->update)
		sleep(1);
	initialize = FALSE;

#if 0
	portEnabled = TRUE;
	portValid = TRUE;
#endif
	signal_update(&info->update_sig, &info->update, ALL_STATE_MACHINE);
}  /* auth_start */

void wait_sec(int sec)
{
	printf("Wait %d seconds...", sec);
	fflush(stdout);
	sleep(sec);
	printf("\n");
	fflush(stdout);
}

#ifdef DBG_RADIUS
static void disp_eap(struct eap_frame *eap)
{
	struct eap_body *body = (struct eap_body *)(eap + 1);
	u16 len = ntohs(eap->len);
	int i;
	u8 *data;

	printf("c:%x i:%02x l:%u\n",
		eap->code,
		eap->id,
		len);
	if (EAP_CODE_REQUEST == eap->code) {
		printf("%x\n",
			body->type);
		if (EAP_TYPE_MD5_CHALLENGE == body->type) {
			data = (u8 *)(body + 1);

			for (i = 0; i < 16 + 1; i++)
				printf("%02x ", data[i]);
			printf("\n");
		}
	} else if (EAP_CODE_RESPONSE == eap->code) {
		int resp_len = len - sizeof(struct eapol_frame)	- 1;
		data = (u8 *)(body + 1);

		if (resp_len > 20)
			resp_len = 20;
		printf("%x: ", body->type);
		for (i = 0; i < resp_len; i++)
			printf("%02x ", data[i]);
		printf("\n");
		if (EAP_TYPE_IDENTITY == body->type) {
			for (i = 0; i < resp_len; i++)
				printf("%c", data[i]);
			printf("\n");
		}
	}
}  /* disp_eap */

static void disp_eapol(struct eapol_frame *eapol, int len)
{
	int msglen;

	msglen = ntohs(eapol->len);
	if (msglen < 1500) {
		printf("v:%x t:%x l:%u\n",
			eapol->version,
			eapol->type,
			htons(eapol->len));
		if (EAP_PACKET == eapol->type) {
			disp_eap((struct eap_frame *)(eapol + 1));
		}
	}
}  /* disp_eapol */
#endif

static u32 proc_id_resp(struct auth_info *info, u32 update)
{
	/* Response for first request. */
	if (2 == info->eap_first_req) {
#ifdef DBG_MSG
printf("get first resp: %d\n", info->auth_bke_state);
#endif
		eapTimeout = FALSE;
		info->eap_first_req++;
		info->auth_bke_state = AUTH_BKE_REQUEST;
		update |= AUTH_BKE_STATE_MACHINE;
	}
	return update;
}  /* proc_id_resp */

static void proc_eapol(struct auth_info *info, struct eapol_frame *eapol)
{
	u32 update = 0;

	if (EAPOL_START == eapol->type) {
		if (2 <= info->eap_first_req) {
			info->eap_first_req = 0;
			eapTimeout = FALSE;
			return;
		}

#if 1
		/* Throw out any previous EAP packet. */
		eapolEap = FALSE;
#endif
		eapolStart = TRUE;
		update |= AUTH_PAE_STATE_MACHINE;
		if (1 == info->state && portControl == Auto &&
		    AUTH_PAE_CONNECTING == info->auth_pae_state) {
			struct radius_info init;

			memset(&init, 0, sizeof(struct radius_info));
			init.frame = (struct radius_frame *) init.radius_data;
			init.id = info->radius.id;
			init.eap_id = info->radius.eap_id;
			prep_init_req(init.frame, &init);
			proc_radius_msg(init.frame, &info->radius,
				init.len, FALSE);
			info->radius.eap_id++;

			/* Indicate very first request for identity. */
			info->eap_first_req = 1;
			update |= proc_radius(info);
		}
	} else if (EAPOL_LOGOFF == eapol->type) {
		eapolLogoff = TRUE;
		update |= AUTH_PAE_STATE_MACHINE;
	} else if (EAP_PACKET == eapol->type) {
		struct eap_frame *eap = (struct eap_frame *)(eapol + 1);

		if (EAP_CODE_SUCCESS == eap->code) {
			eapSuccess = TRUE;
			if (info->state != 0) {
				update |= AUTH_PAE_STATE_MACHINE;
				update |= AUTH_BKE_STATE_MACHINE;
			}
			if (info->state != 1) {
				update |= SUPP_PAE_STATE_MACHINE;
				update |= SUPP_BKE_STATE_MACHINE;
			}
		} else if (EAP_CODE_FAILURE == eap->code) {
			eapFail = TRUE;
			if (info->state != 0) {
				update |= AUTH_PAE_STATE_MACHINE;
				update |= AUTH_BKE_STATE_MACHINE;
			}
			if (info->state != 1) {
				update |= SUPP_PAE_STATE_MACHINE;
				update |= SUPP_BKE_STATE_MACHINE;
			}
		} else {
			u16 len = ntohs(eap->len);

			/* Save in eap for later processing. */
			memcpy(info->eap, eap, len);

			/* For Authenticator. */
			if (EAP_CODE_RESPONSE == eap->code &&
			    1 == info->state) {
				struct radius_info *radius = &info->radius;
				struct eap_body *body = (struct eap_body *)
					(eap + 1);

				radius->eap_len = len;
				memcpy(radius->eap, eap, len);
				if (EAP_TYPE_IDENTITY == body->type) {
					radius->name_len = radius->eap_len -
						5;
					memcpy(radius->name, body + 1,
						radius->name_len);

				update = proc_id_resp(info, update);
				} else if (EAP_TYPE_NAK == body->type) {
#ifdef DBG_MSG
					u8 *auth_type = (u8 *)(body + 1);
printf("nak: %d\n", *auth_type);
#endif
				} else
					info->eap_first_req = 0;
				signal_radius_resp(&info->eap_radius_timeout,
					&info->eap_radius_req);
			}
			eapolEap = TRUE;
			if (info->state != 0) {
				update |= AUTH_BKE_STATE_MACHINE;
			}
			if (info->state != 1) {
				update |= SUPP_PAE_STATE_MACHINE;
				update |= SUPP_BKE_STATE_MACHINE;
			}
		}
	}
	signal_update(&info->update_sig, &info->update, update);
}  /* proc_eapol */


int get_cmd(FILE *fp, struct auth_info *info)
{
	int count;
	int hcount;
	unsigned int num[8];
	unsigned int hex[8];
	int cont = 1;
	char cmd[80];
	char line[80];
	struct thread_info *pthread = &info->update_sig;

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
		} else
		switch (line[0]) {
		case 'o':
			portControl = Auto;
			signal_update(pthread, &info->update,
				ALL_STATE_MACHINE);
			break;
		case 'a':
			portControl = ForceAuthorized;
			signal_update(pthread, &info->update,
				ALL_STATE_MACHINE);
			break;
		case 'u':
			portControl = ForceUnauthorized;
			signal_update(pthread, &info->update,
				ALL_STATE_MACHINE);
			break;
		case 'r':
			eapRestart = FALSE;
			signal_update(pthread, &info->update,
				ALL_STATE_MACHINE);
			break;
		case 's':
			info->eap_req = 1;
			eapReq = TRUE;
			signal_update(pthread, &info->update,
				AUTH_PAE_STATE_MACHINE |
				AUTH_BKE_STATE_MACHINE);
			break;
		case 'i':
			eapNoReq = TRUE;
			signal_update(pthread, &info->update,
				AUTH_PAE_STATE_MACHINE |
				AUTH_BKE_STATE_MACHINE);
			break;
		case 'x':
			info->eap_req = 2;
			prep_success(info->radius.frame, &info->radius);
			eapSuccess = TRUE;
			signal_update(pthread, &info->update,
				AUTH_PAE_STATE_MACHINE |
				AUTH_BKE_STATE_MACHINE);
			break;
		case 'y':
			info->eap_req = 3;
			prep_fail(info->radius.frame, &info->radius);
			eapFail = TRUE;
			signal_update(pthread, &info->update,
				AUTH_PAE_STATE_MACHINE |
				AUTH_BKE_STATE_MACHINE);
			break;
		case 'l':
			userLogoff = TRUE;
			signal_update(pthread, &info->update,
				ALL_STATE_MACHINE);
			break;
		case 'm':
			userLogoff = FALSE;
			signal_update(pthread, &info->update,
				ALL_STATE_MACHINE);
			break;
		case 'c':
			if (info->mode != 3) {
				prep_access_request_req(&info->radius);
				send_radius(radius_fd, info->radius.frame,
					info->radius.len, (SA *) &radius_addr,
					sizeof(radius_addr));
			}
			break;
		case 'd':
			if (info->mode != 3) {
				prep_access_challenge_req(&info->radius);
				send_radius(radius_fd, info->radius.frame,
					info->radius.len, (SA *) &radius_addr,
					sizeof(radius_addr));
			}
			break;
		case 'e':
			if (info->mode != 3) {
				prep_access_request_simple_req(&info->radius);
				send_radius(radius_fd, info->radius.frame,
					info->radius.len, (SA *) &radius_addr,
					sizeof(radius_addr));
			}
			break;
		case 'z':
			break;
#if 0
		case 'p':
			if (count >= 2) {
				test_port = num[0];
				if (1 <= test_port && test_port <= auth_ports)
					p = test_port - 1;
			} else
				printf("%d\n", test_port);
			break;
#endif
		case 'h':
			printf("\th\thelp\n");
			printf("\tq\tquit\n");
			break;
		case 'q':
			if (0 == info->mode &&
			    SUPP_PAE_AUTHENTICATED == info->supp_pae_state) {
				userLogoff = TRUE;
				signal_update(pthread, &info->update,
					ALL_STATE_MACHINE);
			}
			cont = 0;
			break;
		}
	} while (cont);
	return 0;
}  /* get_cmd */

static SOCKET create_sock(char *devname, char *local_ip, int port)
{
	SOCKET sockfd;
	struct sockaddr_in servaddr;
	struct sockaddr_in6 servaddr6;
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
	if (setsockopt(sockfd, SOL_SOCKET, SO_BINDTODEVICE,
	    devname, strlen(devname))) {
		err_ret("bindtodev");
		return -1;
	}
	if (AF_INET6 == family) {
		Bind(sockfd, (SA *) &servaddr6, sizeof(servaddr6));
	} else {
		Bind(sockfd, (SA *) &servaddr, sizeof(servaddr));
	}
	return sockfd;
}  /* create_sock */

struct sock_buf {
	struct sockaddr *from;
	u8 *buf;
	int len;
};

static int check_loop(struct sockaddr *sa, int salen, struct auth_info *auth)
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
		if (addr->sll_ifindex != auth->eth_eapol_addr.sll_ifindex)
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
	struct auth_info *auth;
	struct auth_info *info;
	struct radius_info *radius_info;
	u8 *recvbuf;
	SOCKET sockfd;
	SOCKET fd[NUM_OF_PORTS + 1];
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
	struct eapol_frame *eapol;
	struct radius_frame *radius;
	int i;
	char in_addr[80];
	int cur;
	int last;
	int nsel;
	int looped;
	int msglen;
	int ports;

	pTaskParam = (PTTaskParam) param;
	info = pTaskParam->info;
	radius_info = &info->radius;
	ports = auth_ports + 1;
	if (3 == info->mode || 0 == info->mode)
		ports = 1;
	for (i = 0; i < ports; i++)
		fd[i] = (SOCKET) pTaskParam->fd[i];

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
	for (i = 0; i < ports; i++)
		FD_SET(fd[i], &allrset);
	maxfdp1 = fd[i - 1];
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

		eapol = NULL;
		radius = NULL;
		addr4 = NULL;
		addr = NULL;
		for (i = 0; i < ports; i++) {
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

				/* Ignore frames from main eth0. */
				if (addr->sll_ifindex <
				    info->eth_eapol_addr.sll_ifindex)
					continue;
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
				eapol = (struct eapol_frame *)
					&buf[cur].buf[14];
				msglen -= 14;
			} else
#endif
				radius = (struct radius_frame *) buf[cur].buf;

			auth = info;
			if (ports > 1 && i > 0) {
				int n;

				for (n = 0; n < i - 1; n++)
					auth++;
				radius_info = &auth->radius;
			}

			looped = check_loop(buf[cur].from, len, auth);
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
			if (eapol) {

				/* Save MAC address for Authenticator. */
				if (1 == auth->state)
					memcpy(radius_info->dst,
						addr->sll_addr, ETH_ALEN);

#ifdef DBG_RADIUS
				if (dbg_rcv)
					disp_eapol(eapol, msglen);
#endif
				if (msglen >= ntohs(eapol->len))
					proc_eapol(auth, eapol);
			}
			do {
				if (!radius)
					break;
				auth = info;

				/* Find out which port sends the request. */
				if (3 != info->mode) {
					int p;

					for (p = 0; p < auth_ports; p++) {
						radius_info = &auth->radius;
						if (radius_info->sent &&
						    radius_info->id ==
						    radius->id)
							break;
						auth++;
					}
					if (p >= auth_ports)
						break;
					radius_info->sent = FALSE;
				}
				proc_radius_msg(radius, radius_info,
					msglen, info->mode == 3);
				if (3 == info->mode) {
					if (resp_radius_msg(radius_info))
						send_radius(fd[0],
							radius_info->frame,
							radius_info->len,
							(SA *) addr4, len);
				} else {
					u32 update = 0;

#if 0
					if (resp_radius_msg(radius_info))
						send_radius(fd[0],
							radius_info->frame,
							radius_info->len,
							(SA *) addr4, len);
#endif
					update = proc_radius(auth);
					signal_radius_resp(
						&auth->eap_radius_timeout,
						&auth->eap_radius_req);
					signal_update(&auth->update_sig,
						&auth->update, update);
				}
			} while (0);
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
StateTask(void *param)
{
	PTTaskParam pTaskParam;
	struct auth_info *info;
	struct thread_info *pthread;
	struct timeb tb;
	struct timespec ts;
	int n;

	pTaskParam = (PTTaskParam) param;
	info = pTaskParam->info;
	pthread = &info->update_sig;
	FOREVER {
		if ( pTaskParam->fTaskStop ) {
			break;
		}

		ftime(&tb);
		ts.tv_sec = tb.time;
		ts.tv_nsec = (tb.millitm + 100) * 1000 * 1000;
		if (ts.tv_nsec >= 1000000000) {
			ts.tv_nsec -= 1000000000;
			ts.tv_sec++;
		}
		n = chk_port(info);
		if (n != info->link) {
			info->link = n;
			if (info->link) {
				portEnabled = TRUE;
				portValid = TRUE;
			} else {
				portEnabled = FALSE;
				portValid = FALSE;
			}
			eapSuccess = FALSE;
			eapFail = FALSE;
			signal_update(&info->update_sig, &info->update,
				ALL_STATE_MACHINE);
		}

		Pthread_mutex_lock(&pthread->mutex);
		if (!info->update)
			n = pthread_cond_timedwait(&pthread->cond,
				&pthread->mutex, &ts);
		Pthread_mutex_unlock(&pthread->mutex);

		if (info->state != 1) {
			info->update &= ~AUTH_PAE_STATE_MACHINE;
			info->update &= ~AUTH_BKE_STATE_MACHINE;
		}
		if (info->state != 0) {
			info->update &= ~SUPP_PAE_STATE_MACHINE;
			info->update &= ~SUPP_BKE_STATE_MACHINE;
		}
		auth_pae_state_machine(info);
		auth_bke_state_machine(info);
		supp_pae_state_machine(info);
		supp_bke_state_machine(info);
		auth_key_tx_state_machine(info);
		supp_key_tx_state_machine(info);
		key_rx_state_machine(info);
		re_auth_state_machine(info);

		if (eapRestart) {
			eapSuccess = FALSE;
			eapFail = FALSE;
			eapRestart = FALSE;
			if (info->state != 0)
				info->update = AUTH_PAE_STATE_MACHINE;
			if (info->state != 1)
				info->update = SUPP_PAE_STATE_MACHINE;
		}
	}
	pTaskParam->fTaskStop = TRUE;

#ifdef _WIN32
	SetEvent( pTaskParam->hevTaskComplete );
#endif

#ifdef _SYS_SOCKET_H
	return NULL;
#endif
}  /* StateTask */

#ifdef _SYS_SOCKET_H
void *

#else
void
#endif
TimerTask(void *param)
{
	PTTaskParam pTaskParam;
	struct auth_info *info;
	struct thread_info *pthread;
	u32 update;

	pTaskParam = (PTTaskParam) param;
	info = pTaskParam->info;
	pthread = &info->update_sig;
	FOREVER {
		if ( pTaskParam->fTaskStop ) {
			break;
		}

		sleep(1);
		update = eap_timers_state_machine(info);
		if (update)
			signal_update(pthread, &info->update, update);
	}
	pTaskParam->fTaskStop = TRUE;

#ifdef _WIN32
	SetEvent( pTaskParam->hevTaskComplete );
#endif

#ifdef _SYS_SOCKET_H
	return NULL;
#endif
}  /* TimerTask */

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
	memcpy(ifr.ifr_hwaddr.sa_data, eth_eapol, ETH_ALEN);
	rc = ioctl(sockfd, SIOCADDMULTI, &ifr);
}

static void del_multi(SOCKET sockfd, char *local_if)
{
	struct ifreq ifr;
	int rc;

	strcpy(ifr.ifr_name, local_if);
	ifr.ifr_hwaddr.sa_family = AF_UNSPEC;
	memcpy(ifr.ifr_hwaddr.sa_data, eth_eapol, ETH_ALEN);
	rc = ioctl(sockfd, SIOCDELMULTI, &ifr);
}

static SOCKET create_raw(struct ip_info *info, char *dest,
	struct auth_info *auth)
{
	SOCKET sockfd;
	struct ethhdr *eh;
	int addr[ETH_ALEN];
	int cnt;

	sockfd = Socket(AF_PACKET, SOCK_RAW, htons(eapol_proto));
	if (sockfd < 0)
		return sockfd;

	cnt = sscanf(dest, "%x:%x:%x:%x:%x:%x",
		&addr[0], &addr[1], &addr[2], &addr[3], &addr[4], &addr[5]);
	auth->eth_eapol_addr.sll_family = PF_PACKET;
	auth->eth_eapol_addr.sll_protocol = htons(eapol_proto);
	auth->eth_eapol_addr.sll_ifindex = info->if_idx + auth->port;
	auth->eth_eapol_addr.sll_hatype = ARPHRD_ETHER;
	auth->eth_eapol_addr.sll_halen = ETH_ALEN;
	if (ETH_ALEN == cnt) {
		auth->eth_eapol_addr.sll_pkttype = PACKET_OTHERHOST;
		auth->eth_eapol_addr.sll_addr[0] = (u8) addr[0];
		auth->eth_eapol_addr.sll_addr[1] = (u8) addr[1];
		auth->eth_eapol_addr.sll_addr[2] = (u8) addr[2];
		auth->eth_eapol_addr.sll_addr[3] = (u8) addr[3];
		auth->eth_eapol_addr.sll_addr[4] = (u8) addr[4];
		auth->eth_eapol_addr.sll_addr[5] = (u8) addr[5];
	} else {
		auth->eth_eapol_addr.sll_pkttype = PACKET_MULTICAST;
		memcpy(auth->eth_eapol_addr.sll_addr, eth_eapol, ETH_ALEN);
	}
	auth->eth_eapol_addr.sll_addr[6] = 0x00;
	auth->eth_eapol_addr.sll_addr[7] = 0x00;

	auth->eth_eapol_buf = malloc(1518);
	memcpy(auth->eth_eapol_buf, auth->eth_eapol_addr.sll_addr, ETH_ALEN);
	eh = (struct ethhdr *) auth->eth_eapol_buf;
	eh->h_proto = htons(eapol_proto);

	return sockfd;
}
#endif

static void radius_init(struct radius_info *radius, u8 *src_addr, u8 *ip_addr)
{
	memset(radius, 0, sizeof(struct radius_info));
	memcpy(radius->src, src_addr, ETH_ALEN);
	memcpy(radius->ip_addr, ip_addr, 4);
	radius->port = 1;
	radius->mtu = 1500;
	radius->frame = (struct radius_frame *) radius->radius_data;
	radius->packet.data = radius->radius_data;
}  /* radius_init */


int main(int argc, char *argv[])
{
	TTaskParam paramState[NUM_OF_PORTS];
	TTaskParam paramTimer[NUM_OF_PORTS];
	TTaskParam paramRx;

#ifdef _SYS_SOCKET_H
	pthread_t tidState[NUM_OF_PORTS];
	pthread_t tidTimer[NUM_OF_PORTS];
	pthread_t tidRx;
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
	struct auth_info *auth_info;
	struct auth_info *auth;
	struct radius_info *radius;
	int auth_mode = 2;
	int daemonize = 0;

	SocketInit(0);

	if (argc < 2) {
		printf("usage: %s <local_if> [-p<#>]",
			argv[0]);
		printf(" [-u <dest_ip>] -s <secret> [-d[#] (debug)]\n");
		return 1;
	}

	strcpy(secret, "testing123");

	family = AF_PACKET;
	dbg_rcv = 3;
	auth_ports = 1;
	dest_ip[0] = '\0';
	if (argc > 2) {
		i = 2;
		while (i < argc) {
			if ('-' == argv[i][0]) {
				switch (argv[i][1]) {
				case 'p':
					if ('1' <= argv[i][2] &&
					    argv[i][2] <= '9')
						auth_ports = argv[i][2] - '0';
					break;
				case 'm':
					if ('0' <= argv[i][2] &&
					    argv[i][2] <= '9')
						auth_mode = argv[i][2] - '0';
					break;
				case 'd':
					dbg_rcv = 5;
					if ('0' <= argv[i][2] &&
					    argv[i][2] <= '9')
						dbg_rcv = argv[i][2] - '0';
					if (!dbg_rcv)
						daemonize = 1;
					break;
				case 's':
					++i;
					strcpy(secret, argv[i]);
					break;
				case 'u':
					++i;
					strcpy(dest_ip, argv[i]);
					break;
				}
			}
			++i;
		}
	}
	if (0 == auth_mode || 3 == auth_mode)
		auth_ports = 1;
	else if (!dest_ip[0]) {
		printf("No RADIUS server\n");
		exit(0);
	}

	drvname[0] = '\0';
	strncpy(devname, argv[1], sizeof(devname));
	host_ip = strchr(devname, '.');
	if (host_ip != NULL)
		*host_ip = 0;
	sprintf(drvname, "/sys/class/net/%s/sw", devname);
	sw_host_port = get_host_port();
	strncpy(ethnames[0], argv[1], 20);
	if (auth_ports > 1) {
		int len = strlen(ethnames[0]);

		for (p = 1; p < auth_ports; p++) {
			strncpy(ethnames[p], ethnames[0], 20);
			ethnames[p][len - 1] += p;
		}
	}

	if (get_host_info(devname, &info)) {
		memcpy(host_addr, &info.addr.sin_addr, 4);
		inet_ntop(AF_INET, &info.addr.sin_addr,
			host_ip4, sizeof(host_ip4));
		ipv6_interface = info.if_idx;
		if (info.plen) {
			inet_ntop(AF_INET6, &info.addr6.sin6_addr,
				host_ip6, sizeof(host_ip6));
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
			memcpy(host_addr6, &info.addr6.sin6_addr, 16);
			ipv6_interface = info.if_idx;
		}
		memcpy(hw_addr, info.hwaddr, ETH_ALEN);
#endif
	} else {
		printf("cannot locate IP address\n");
		exit(1);
	}

	/* Get index from virtual VLAN device. */
	if (strcmp(devname, argv[1]))
		get_dev_info(argv[1], &info);

	if (auth_mode == 3) {
		radius_dst_port = RADIUS_AUTHEN_SRC_PORT;
		radius_src_port = RADIUS_AUTHEN_DST_PORT;
	} else {
		radius_dst_port = RADIUS_AUTHEN_DST_PORT;
		radius_src_port = RADIUS_AUTHEN_SRC_PORT;
	}

	ip_family = family;
	family = AF_INET;
	host_ip = host_ip4;
	radius_addr.sin_family = family;
	radius_addr.sin_port = htons(radius_dst_port);
	radius_addr.sin_addr.s_addr = inet_addr(dest_ip);

	radius_fd = create_sock(devname, host_ip, radius_src_port);
	if (radius_fd < 0) {
		printf("Cannot create socket\n");
		return 1;
	}

	auth_info = malloc(sizeof(struct auth_info) * auth_ports);
	if (!auth_info) {
		printf("Cannot alloc memory\n");
		return 1;
	}

	if (daemonize) {
		i = daemon(1, 0);
		if (i) {
			printf("Fail to daemon\n");
			return i;
		}
	}

	auth = auth_info;
	for (p = 0; p < auth_ports; p++) {
		auth_init(auth);
		auth->mode = auth_mode;
		if (auth_mode)
			auth->state = 1;
		radius = &auth->radius;
		radius_init(radius, hw_addr, host_addr);

		if (auth->mode == 3) {
			radius->src[0] = 0xff;
			radius->dst[0] = 0xff;
			radius->port = 0;
			radius->ip_addr[0] = 0;
			radius->mtu = 1500;
			radius->framed = FRAMED_IP_ADDRESS_ASSIGNED;
		}

		if (auth->mode != 3) {
			auth->port = p;
			auth->eth_fd = create_raw(&info, dest_ip, auth);
			if (auth->eth_fd < 0) {
				printf("Cannot create socket\n");
				return 1;
			}
			add_multi(auth->eth_fd, ethnames[p]);
			memcpy(&auth->eth_eapol_buf[6], hw_addr, ETH_ALEN);
		}
		auth++;
	}
	if (3 == auth_mode)
		auth_ports = 0;

	auth = auth_info;
	for (p = 0; p < auth_ports; p++) {
		pthread_cond_init_(&auth->eap_radius_timeout.cond);
		pthread_mutex_init_(&auth->eap_radius_timeout.mutex);

		pthread_cond_init_(&auth->update_sig.cond);
		pthread_mutex_init_(&auth->update_sig.mutex);

		paramState[p].fTaskStop = FALSE;
		paramState[p].info = auth;
		Pthread_create(&tidState[p], NULL, StateTask, &paramState[p]);

		paramTimer[p].fTaskStop = FALSE;
		paramTimer[p].info = auth;
		Pthread_create(&tidTimer[p], NULL, TimerTask, &paramTimer[p]);

		auth++;
	}
	paramRx.fTaskStop = FALSE;
	paramRx.info = auth_info;
	paramRx.fd[0] = radius_fd;
	if (0 == auth_mode)
		i = 0;
	else
		i = 1;
	auth = auth_info;
	for (p = 0; p < auth_ports; p++) {
		paramRx.fd[i + p] = auth->eth_fd;
		auth++;
	}
	Pthread_create(&tidRx, NULL, ReceiveTask, &paramRx);

	if (auth_mode != 3) {
		auth = auth_info;
		for (p = 0; p < auth_ports; p++)
			auth_ready(auth++);
		auth = auth_info;
		for (p = 0; p < auth_ports; p++)
			auth_start(auth++);
	}

	if (daemonize) {
		FOREVER {
		}
	}
	if (!paramRx.fTaskStop) {
		do {
			if (!get_cmd(stdin, auth_info))
				break;
		} while (1);
		for (p = 0; p < auth_ports; p++) {
			paramState[p].fTaskStop = TRUE;
			paramTimer[p].fTaskStop = TRUE;
		}
		paramRx.fTaskStop = TRUE;
	}

	// wait for task to end
	for (p = 0; p < auth_ports; p++) {
		Pthread_join(tidTimer[p], &status);
		Pthread_join(tidState[p], &status);
	}
	Pthread_join(tidRx, &status);

	auth = auth_info;
	for (p = 0; p < auth_ports; p++) {
		if (auth->eth_fd > 0) {
			del_multi(auth->eth_fd, ethnames[p]);
			free(auth->eth_eapol_buf);
			closesocket(auth->eth_fd);
		}
		auth++;
	}
	free(auth_info);
	closesocket(radius_fd);
	SocketExit();

	return 0;
}
