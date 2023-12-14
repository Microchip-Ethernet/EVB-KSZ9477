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
#define __packed
#endif

#if defined(__GNUC__)
#ifndef __packed
#define __packed __attribute__((packed))
#endif
#endif


#if 0
#include "ksz_req.h"
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


#define NUM_OF_PORTS			4


int gWaitDelay = 100;

#define PTP_EVENT_PORT			319
#define PTP_GENERAL_PORT		320

int ip_family;
int ipv6_interface = 0;
int ptp_proto = PTP_PROTO;
int eth_vlan;

SOCKET eth_fd[NUM_OF_PORTS];
int rstp_ports;
char ethnames[NUM_OF_PORTS][20];

char devname[20];

int ptp_2step = 0;
int ptp_alternate = 0;
int ptp_unicast = 0;
int vlan = 0;
int vlan_prio = 2;
int no_len = 0;

#ifdef _SYS_SOCKET_H
struct sockaddr_ll eth_bpdu_addr[NUM_OF_PORTS];
u8 *eth_bpdu_buf[NUM_OF_PORTS];

u8 eth_bpdu[] = { 0x01, 0x80, 0xC2, 0x00, 0x00, 0x11 };

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
	ts.tv_nsec = (tb.millitm + 10) * 1000 * 1000;
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

static u8 ts_addr[NUM_OF_PORTS][6];
static int tx_delay;


void send_data(int p, u8 data[], int len)
{
	SOCKET sockfd = eth_fd[p];
	SAI *pservaddr;
	socklen_t servlen;
	char *buf;
	u16 *ptr;
	int hdr_len = 14;

	pservaddr = (SAI *) &eth_bpdu_addr[p];
	servlen = sizeof(eth_bpdu_addr[0]);
	buf = (char *) eth_bpdu_buf[p];
	ptr = (u16 *) &buf[12];
	if (vlan) {
		u16 tag = vlan - 1;

		if (tag > 4094)
			tag = 0;
		tag |= vlan_prio << 13;
		*ptr++ = htons(ETH_P_8021Q);
		*ptr++ = htons(tag);
		if (no_len)
			*ptr++ = 0xffff;
		else
			*ptr++ = htons(0x22f0);
		len -= 0;
		hdr_len += 4;
	} else {
		if (no_len)
			*ptr++ = 0xffff;
		else
			*ptr++ = htons(len);
	}
	memcpy(ptr, data, len);
	len += hdr_len;
	Sendto(sockfd, buf, len, 0, (SA *) pservaddr, servlen);
}  /* send_data */


int get_cmd(FILE *fp)
{
	int count;
	int hcount;
	unsigned int num[8];
	unsigned int hex[8];
	int cont = 1;
	int i;
	int n;
	int p = 0;
	char cmd[80];
	char line[80];
	u8 payload[1500];

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
			memset(payload, 0x00, 1500);
			n = 1;
			if (count >= 2)
				n = num[0];
			for (i = 0; i < n; i++) {
				send_data(p, payload, 150);
				if ((i % 500) == (500 - 1))
					signal_wait(&tx_job_thread, 0);
			}
			break;
		case 'b':
			memset(payload, 0xff, 1500);
			n = 1;
			if (count >= 2)
				n = num[0];
			for (i = 0; i < n; i++) {
				send_data(p, payload, 1500);
				if ((i % 50) == (50 - 1))
					signal_wait(&tx_job_thread, 0);
			}
			break;
		case 'c':
			memset(payload, 0x55, 1500);
			n = 1;
			if (count >= 2)
				n = num[0];
			for (i = 0; i < n; i++) {
				send_data(p, payload, 1500);
				if ((i % 50) == (50 - 1))
					signal_wait(&tx_job_thread, 0);
			}
			break;
		case 'd':
			memset(payload, 0xaa, 1500);
			n = 1;
			if (count >= 2)
				n = num[0];
			for (i = 0; i < n; i++) {
				send_data(p, payload, 1500);
				if ((i % 50) == (50 - 1))
					signal_wait(&tx_job_thread, 0);
			}
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
			printf("\ta [#]\t0 pattern\n");
			printf("\tb [#]\t1 pattern\n");
			printf("\tc [#]\t01 pattern\n");
			printf("\td [#]\t10 pattern\n");
			printf("\tp\tdestination port\n");
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
#if 0
	if (cur->len == last->len &&
			memcmp(cur->from, last->from, len) == 0 &&
			memcmp(cur->buf, last->buf, cur->len) == 0)
		return 1;
#endif
	return 0;
}

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

static SOCKET create_raw(struct ip_info *info, char *dest, int p)
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

	proto = htons(ETH_P_802_2);
	sock_addr = &eth_bpdu_addr[p];
	eth_addr = eth_bpdu;
	eth_buf = &eth_bpdu_buf[p];
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
	struct rx_param rx_param;

	SocketInit(0);

	if (argc < 2) {
		printf("usage: %s <local_if>",
			argv[0]);
		printf("\t[-p<#>] [-v] [-x #][-y #][-l]\n");
		return 1;
	}
	family = AF_PACKET;
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
				case 'u':
					++i;
					if (i >= argc)
						break;
					strcpy(dest_ip, argv[i]);
					break;
				case 'v':
					eth_vlan = 1;
					break;
				case 'x':
					++i;
					if (i >= argc)
						break;
					vlan = atoi(argv[i]);
					++vlan;
					break;
				case 'y':
					++i;
					if (i >= argc)
						break;
					vlan_prio = atoi(argv[i]);
					if (vlan_prio > 7)
						vlan_prio = 7;
					break;
				case 'l':
					no_len = 1;
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
		eth_fd[p] = create_raw(&info, dest_ip, p);
		if (eth_fd[p] < 0) {
			printf("Cannot create socket\n");
			return 1;
		}
		add_multi(eth_fd[p], ethnames[p], eth_bpdu);
	}
	signal_init(&tx_job_thread);
	signal_update(&tx_job_thread, NULL, 0);

	rx_param.bpdu = eth_fd;
	rx_param.cnt = rstp_ports;

	for (i = 0; i < 3; i++) {
		param[i].fTaskStop = FALSE;
	}
		param[0].param = &rx_param;

	if ( !param[0].fTaskStop ) {
		do {
			if (!get_cmd(stdin))
				break;
		} while (1);
		for (i = 0; i < 3; i++) {
			param[i].fTaskStop = TRUE;
		}
	}

	for (p = 0; p < rstp_ports; p++) {
		if (eth_fd[p] > 0) {
			del_multi(eth_fd[p], ethnames[p], eth_bpdu);
			free(eth_bpdu_buf[p]);
			closesocket(eth_fd[p]);
		}
	}
	SocketExit();

	return 0;
}
