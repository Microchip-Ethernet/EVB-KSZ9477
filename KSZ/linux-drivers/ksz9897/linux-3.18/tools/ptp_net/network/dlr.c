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
#include <fcntl.h>
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

typedef uint8_t u8;
typedef int16_t s16;
typedef uint16_t u16;
typedef uint32_t u32;
typedef int64_t s64;
typedef uint64_t u64;

struct ksz_net_info {
	void *msg;
	int len;
	int family;
	struct sockaddr *addr;
	socklen_t addrlen;
	void (*send)(void *msg, int family, int len, struct sockaddr *addr,
		socklen_t addrlen);
};

struct ksz_net_hdr {
	u8 mod;
	u8 svc;
	u8 class;
	u8 id;
	u16 sequenceId;
	u16 messageLength;
} __packed;

struct ksz_net_msg {
	struct ksz_net_hdr hdr;
	u32 data;
} __packed;


#include "ksz_req.h"
#include "ksz_sw_api.h"
#include "ksz_dlr_net.c"
#include "ksz_hsr_api.h"

#if defined(_MSC_VER)
#include <packoff.h>
#endif


int gWaitDelay = 100;

char *KSZ_ip_addr = "224.0.1.123";
char *KSZ_ip_addr6_const = "ff02::0123";
char KSZ_ip_addr6[20];

#define KSZ_EVENT_PORT			1234

int ip_family;
int ipv6_interface = 0;
int dbg_rcv = 0;

SOCKET event_fd;

SOCKET *sockptr;
char devname[20];

struct sockaddr_in event_addr;
struct sockaddr_in client_addr;
struct sockaddr_in6 event_addr6;
struct sockaddr_in6 client_addr6;

pthread_mutex_t disp_mutex = PTHREAD_MUTEX_INITIALIZER;

u8 host_addr[16];
u8 host_addr6[16];
u8 hw_addr[ETH_ALEN];

struct dlr_info dlr;
struct dlr_info active_dlr;

typedef struct {
	int fTaskStop;
	int multicast;
	void *info;

#if defined(_WIN32)
	HANDLE hevTaskComplete;
#endif
} TTaskParam, *PTTaskParam;


struct ksz_net_info net_info;

static void print_topology(u8 topology)
{
	printf("topology: %s\n", DLR_TOPOLOGY_RING == topology ?
		"ring" : "linear");
}

static void print_network(u8 network)
{
	printf("network: ");
	switch (network) {
	case DLR_NET_NORMAL:
		printf("normal\n");
		break; 
	case DLR_NET_RING_FAULT:
		printf("ring fault\n");
		break; 
	case DLR_NET_UNEXPECTED_LOOP_DETECTED:
		printf("unexpected loop\n");
		break; 
	case DLR_NET_PARTIAL_FAULT:
		printf("partial fault\n");
		break; 
	case DLR_NET_RAPID_FAULT:
		printf("rapid fault\n");
		break; 
	}
}

static void print_status(u8 status)
{
	printf("status: ");
	switch (status) {
	case DLR_STAT_BACKUP_SUPERVISOR:
		printf("backup supervisor\n");
		break;
	case DLR_STAT_ACTIVE_SUPERVISOR:
		printf("active supervisor\n");
		break;
	case DLR_STAT_RING_NODE:
		printf("ring node\n");
		break;
	case DLR_STAT_NO_SUPERVISOR:
		printf("no supervisor\n");
		break;
	case DLR_STAT_NODE_NOT_SUPPORTED:
		printf("not supported\n");
		break;
	}
}

static void print_super_cfg(struct ksz_dlr_super_cfg *cfg)
{
	printf("E:%u  P:%u  I:%u  T:%u  V:%u\n",
		cfg->enable, cfg->prec, cfg->beacon_interval,
		cfg->beacon_timeout, cfg->vid);
}

static void print_dlr_cap(u32 flags)
{
	printf("caps: %08x\n", flags);
	printf("%08x\tannounce based\n",
		DLR_CAP_ANNOUNCE_BASED);
	printf("%08x\tbeacon based\n",
		DLR_CAP_BEACON_BASED);
	printf("%08x\tsupervisor capable\n",
		DLR_CAP_SUPERVISOR_CAPABLE);
	printf("%08x\tgateway capable\n",
		DLR_CAP_GATEWAY_CAPABLE);
	printf("%08x\tflush table capable\n",
		DLR_CAP_FLUSH_TABLE_CAPABLE);
}

static void print_dlr_node(struct ksz_dlr_active_node *node)
{
	printf("%02x:%02x:%02x:%02x:%02x:%02x  ",
		node->addr[0],
		node->addr[1],
		node->addr[2],
		node->addr[3],
		node->addr[4],
		node->addr[5]);
	printf("%3u.%3u.%3u.%3u\n",
		(u8)(node->ip_addr),
		(u8)(node->ip_addr >> 8),
		(u8)(node->ip_addr >> 16),
		(u8)(node->ip_addr >> 24));
}

static void print_all(struct ksz_dlr_gateway_capable *capable)
{
	print_topology(capable->net_topology);
	print_network(capable->net_status);
	print_status(capable->super_status);
	print_super_cfg(&capable->super_cfg);
	print_dlr_node(&capable->last_active[0]);
	print_dlr_node(&capable->last_active[1]);
	print_dlr_node(&capable->active_super_addr);
	print_dlr_cap(capable->cap);
}

static void print_dlr_msg(u8 err)
{
	switch (err) {
	case STATUS_INVALID_ATTRIB_VALUE:
		printf("invalid attrib\n");
		break;
	case STATUS_OBJECT_STATE_CONFLICT:
		printf("object conflict\n");
		break;
	case STATUS_REPLY_DATA_TOO_LARGE:
		printf("data too large\n");
		break;
	}
}

struct dlr_node {
	void *data;
	struct dlr_node *next;
	struct dlr_node *link;
};

struct dlr_node_anchor {
	struct dlr_node anchor;
	struct dlr_node *last;
};

static struct dlr_node *active_node;
static struct dlr_node_anchor dlr_list;

struct dlr_net_info {
	struct ksz_dlr_active_node node;
	struct sockaddr_in addr;
	struct ksz_net_info net;
	struct dlr_info dlr;
};

static void print_dlr_list(void);
static void print_dlr_ring(void);

static void print_dlr_help(void)
{
	printf("\tv\tRevision\n");
	printf("\tc\tCapabilities\n");
	printf("\tt\tTopology\n");
	printf("\tn\tNetwork\n");
	printf("\ts\tStatus\n");
	printf("\tr\tRing participant count\n");
	printf("\tl\tRing participant list\n");
	printf("\te [p]\tActive node at port\n");
	printf("\td\tActive supervisor address\n");
	printf("\tp\tActive supervisor precedence\n");
	printf("\tib [#]\tBeacon interval\n");
	printf("\ttb [#]\tBeacon timeout\n");
	printf("\tpb [#]\tPrecedence\n");
	printf("\tvb [#]\tVLAN id\n");
	printf("\ta\tAll\n");
	printf("\tC [#]\tSupervisor config\n");
	printf("\tF [#]\tRing fault count\n");
	printf("\tV\tVerify Fault\n");
	printf("\tR\tClear Rapid Fault\n");
	printf("\tS\tRestart SignOn\n");
	printf("\tG\tClear Gateway Fault\n");
	printf("\tN\tChange notifications\n");
	printf("\thsr\tswitch to hsr\n");
	printf("\tsw\tswitch to sw\n");
	printf("\th\thelp\n");
	printf("\tq\tquit\n");
}

int get_dlr_cmd(FILE *fp)
{
	int count;
	int hcount;
	unsigned int num[8];
	unsigned int hex[8];
	int cont = 1;
	u8 err = 0;
	u8 prec = 0;
	u32 flags = 0;
	struct ksz_dlr_active_node node;
	struct ksz_dlr_active_node nodes[10];
	struct ksz_dlr_gateway_capable capable;
	struct ksz_dlr_super_cfg cfg;
	u16 cnt = 0;
	u16 rev = 0;
	u16 size;
	u8 network = 0;
	u8 status = 0;
	u8 topology = 0;
	char cmd[80];
	char line[80];
	int rc;
	u8 precedence = 0;
	u32 beacon_interval = 400;
	u32 beacon_timeout = 1960;
	u16 vid = 0;
	void *fd = &net_info;
	struct dlr_net_info *data;

	do {
		printf("dlr> ");
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
		if (active_node) {
			data = active_node->data;
			memcpy(fd, &data->net, sizeof(struct ksz_net_info));
		}
		if (!strcmp(cmd, "sw"))
			return 3;
		else if (!strcmp(cmd, "hsr"))
			return 2;
		else if (!strcmp(cmd, "dlr"))
			print_dlr_help();
		else
		if ('b' == line[1]) {
			switch (line[0]) {
			case 'i':
				if (count >= 2)
					beacon_interval = (u16) num[0];
				else
					printf("beacon interval = %u\n",
						beacon_interval);
				break;
			case 't':
				if (count >= 2)
					beacon_timeout = (u16) num[0];
				else
					printf("beacon timeout = %u\n",
						beacon_timeout);
				break;
			case 'p':
				if (count >= 2)
					precedence = (u8) num[0];
				else
					printf("precedence = %u\n",
						precedence);
				break;
			case 'v':
				if (count >= 2)
					vid = (u16) num[0];
				else
					printf("VLAN id = %u\n",
						vid);
				break;
			}
		} else
		switch (line[0]) {
		case 't':
			w_dlr_topology(fd, NULL);
			break;
		case 'n':
			w_dlr_network(fd, NULL);
			break;
		case 'a':
			w_dlr_all(fd, NULL);
			break;
		case 'v':
			w_dlr_revision(fd, NULL);
			break;
		case 's':
			w_dlr_super_status(fd, NULL);
			break;
		case 'C':
			if (count >= 2) {
				cfg.enable = !!num[0];
				cfg.beacon_interval = beacon_interval;
				cfg.beacon_timeout = beacon_timeout;
				cfg.prec = precedence;
				cfg.vid = vid;
				w_dlr_super_cfg(fd, &cfg);
			} else {
				w_dlr_super_cfg(fd, NULL);
			}
			break;
		case 'F':
			if (count >= 2) {
				cnt = num[0];
				w_dlr_ring_fault_cnt(fd, &cnt);
			} else {
				w_dlr_ring_fault_cnt(fd, NULL);
			}
			break;
		case 'e':
			w_dlr_active_node(fd, NULL);
			break;
		case 'r':
			w_dlr_ring_part_cnt(fd, NULL);
			break;
		case 'l':
			w_dlr_ring_part_list(fd, NULL, 0);
			break;
		case 'd':
			w_dlr_active_super_addr(fd, NULL);
			break;
		case 'p':
			w_dlr_active_super_prec(fd, NULL);
			break;
		case 'c':
			w_dlr_cap(fd, NULL); 
			break;
		case 'L':
			print_dlr_list();
			print_dlr_ring();
			break;
		case 'V':
			w_dlr_verify_fault(fd, NULL);
			break;
		case 'R':
			w_dlr_clear_rapid_fault(fd, NULL);
			break;
		case 'S':
			w_dlr_restart_sign_on(fd, NULL);
			break;
		case 'G':
			w_dlr_clear_gateway_fault(fd, NULL);
			break;
		case 'h':
			print_dlr_help();
			break;
		case 'q':
			cont = 0;
			break;
		}
	} while (cont);
	return 0;
}  /* get_dlr_cmd */

static void print_hsr_cap(u32 flags)
{
	printf("caps: %08x\n", flags);
	printf("%08x\thw duplicate discard\n",
		HSR_CAP_DUPLICATE_DISCARD);
	printf("%08x\tRedBox capable\n",
		HSR_CAP_REDBOX_CAPABLE);
}

static void print_hsr_network(u8 network)
{
	printf("network: ");
	switch (network) {
	case 0:
		printf("fault\n");
		break; 
	case 1:
		printf("normal\n");
		break; 
	}
}

static void print_hsr_node(struct ksz_hsr_node *node)
{
	printf("%02x:%02x:%02x:%02x:%02x:%02x\n",
		node->addr[0],
		node->addr[1],
		node->addr[2],
		node->addr[3],
		node->addr[4],
		node->addr[5]);
}

#if 0
static void print_hsr_help(void)
{
	printf("\tc\tCapabilities\n");
	printf("\tr\tRing participant count\n");
	printf("\tl\tRing participant list\n");
	printf("\tN\tChange notifications\n");
	printf("\tdlr\tswitch to dlr\n");
	printf("\tsw\tswitch to sw\n");
	printf("\th\thelp\n");
	printf("\tq\tquit\n");
}

int get_hsr_cmd(FILE *fp)
{
	int count;
	int hcount;
	unsigned int num[8];
	unsigned int hex[8];
	int cont = 1;
	u8 err = 0;
	u32 flags = 0;
	struct ksz_hsr_node nodes[10];
	u16 cnt = 0;
	u8 network = 0;
	u16 size;
	char cmd[80];
	char line[80];
	int rc;
	void *fd = &swdev;

	do {
		printf("hsr> ");
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
		if (!strcmp(cmd, "sw"))
			return 3;
		else if (!strcmp(cmd, "dlr"))
			return 1;
		else if (!strcmp(cmd, "hsr"))
			print_hsr_help();
		else
		switch (line[0]) {
		case 'n':
			rc = get_hsr_network(fd, &network);
			if (rc)
				print_sw_err(rc);
			else
				print_hsr_network(network);
			break;
		case 'r':
			rc = get_hsr_ring_part_cnt(fd, &cnt);
			if (rc)
				print_sw_err(rc);
			else
				printf("ring part cnt: %u\n", cnt);
			break;
		case 'l':
			size = sizeof(nodes);
			rc = get_hsr_ring_part_list(fd, nodes, &size, &err);
			if (rc)
				print_sw_err(rc);
			else {
				for (err = 0; err < size /
				     sizeof(struct ksz_hsr_node); err++)
					print_hsr_node(&nodes[err]);
			}
			break;
		case 'c':
			rc = get_hsr_cap(fd, &flags);
			if (rc)
				print_sw_err(rc);
			else
				print_hsr_cap(flags);
			break;
		case 'N':
			if (count >= 2) {
				rc = set_hsr_notify(&swdev, num[0]);
				if (rc)
					print_sw_err(rc);
			}
			break;
		case 'h':
			print_hsr_help();
			break;
		case 'q':
			cont = 0;
			break;
		}
	} while (cont);
	return 0;
}  /* get_hsr_cmd */

static void print_sw_help(void)
{
	printf("\tl <p> [0,1]\tlearning\n");
	printf("\tr <p> [0,1]\trx\n");
	printf("\tt <p> [0,1]\ttx\n");
	printf("\ts <p> [0,1]\tpower\n");
	printf("\tN\t\tChange notifications\n");
	printf("\tdlr\t\tswitch to dlr\n");
	printf("\thsr\t\tswitch to hsr\n");
	printf("\th\t\thelp\n");
	printf("\tq\t\tquit\n");
}

int get_cmd(FILE *fp)
{
	int count;
	int hcount;
	unsigned int num[8];
	unsigned int hex[8];
	int cont = 1;
	u8 err = 0;
	char cmd[80];
	char line[80];
	int get;
	int rc;
	void *fd = &swdev;

	do {
		printf("sw> ");
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
		if (!strcmp(cmd, "sw"))
			print_dlr_help();
		else if (!strcmp(cmd, "dlr"))
			return 1;
		else if (!strcmp(cmd, "hsr"))
			return 2;
		else
		switch (line[0]) {
		case 'l':
			if (count >= 3)
				rc = set_port_learn(fd, num[0], !!num[1]);
			else if (count >= 2)
				rc = get_port_learn(fd, num[0], &get);
			else
				break;
			if (rc)
				print_sw_err(rc);
			else if (count < 3)
				printf("%d\n", get);
			break;
		case 'r':
			if (count >= 3)
				rc = set_port_rx(fd, num[0], !!num[1]);
			else if (count >= 2)
				rc = get_port_rx(fd, num[0], &get);
			else
				break;
			if (rc)
				print_sw_err(rc);
			else if (count < 3)
				printf("%d\n", get);
			break;
		case 't':
			if (count >= 3)
				rc = set_port_tx(fd, num[0], !!num[1]);
			else if (count >= 2)
				rc = get_port_tx(fd, num[0], &get);
			else
				break;
			if (rc)
				print_sw_err(rc);
			else if (count < 3)
				printf("%d\n", get);
			break;
		case 's':
			if (count >= 3)
				rc = set_port_power(fd, num[0],
					!!num[1]);
			else if (count >= 2)
				rc = get_port_power(fd, num[0], &get);
			else
				break;
			if (rc)
				print_sw_err(rc);
			else if (count < 3)
				printf("%d\n", get);
			break;
		case 'N':
			if (count >= 2) {
				rc = set_sw_notify(&swdev, num[0]);
				if (rc)
					print_sw_err(rc);
			}
			break;
		case 'h':
			print_sw_help();
			break;
		case 'q':
			cont = 0;
			break;
		}
	} while (cont);
	return 0;
}  /* get_cmd */
#endif

static SOCKET create_sock(char *devname, char *multi_ip, char *local_ip,
	int port, int multi_loop)
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
	if (AF_INET6 == family) {
		struct ipv6_mreq mreq;
		u_int iface;
		int hop;
		u_int loop;

		Bind(sockfd, (SA *) &servaddr6, sizeof(servaddr6));
#ifdef IPV6_CLASS
		if (KSZ_EVENT_PORT == port) {
			u_int tclass;

			tclass = 0xff;
			sockopt = (char *) &tclass;
			if (setsockopt(sockfd, IPPROTO_IPV6, IPV6_TCLASS,
					sockopt, sizeof(tclass)) < 0) {
				err_ret("no tclass");
			}
		}
#endif

		if (!multi_ip)
			return sockfd;

		inet_pton(AF_INET6, multi_ip, &mreq.ipv6mr_multiaddr);
		mreq.ipv6mr_interface = ipv6_interface;
		sockopt = (char *) &mreq;
		if (setsockopt(sockfd, IPPROTO_IPV6, IPV6_ADD_MEMBERSHIP,
				sockopt, sizeof(mreq)) < 0) {
			err_ret("add member");
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
		if (KSZ_EVENT_PORT == port) {
			tos = 0xb8;
			sockopt = (char *) &tos;
			if (setsockopt(sockfd, IPPROTO_IP, IP_TOS,
					sockopt, sizeof(tos)) < 0) {
				err_ret("tos");
				return -1;
			}
		}

		if (!multi_ip)
			return sockfd;

		mreq.imr_multiaddr.s_addr = inet_addr(multi_ip);
		mreq.imr_address.s_addr = inet_addr(local_ip);
		mreq.imr_ifindex = ipv6_interface;
		sockopt = (char *) &mreq;
		if (setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, sockopt,
				sizeof(mreq)) < 0) {
			err_ret("add member");
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

void send_msg(void *msg, int family, int len, struct sockaddr *addr,
	socklen_t addrlen)
{
	char *buf = (char *) msg;

	if (!addr) {
		if (AF_INET6 == family) {
			addr = (SA *) &event_addr6;
			addrlen = sizeof(event_addr6);
		} else {
			addr = (SA *) &event_addr;
			addrlen = sizeof(event_addr);
		}
	}
	Sendto(event_fd, buf, len, 0, addr, addrlen);
}  /* send_msg */

static void init_net_info(struct ksz_net_info *info, int family)
{
	info->family = family;
	info->addr = NULL;
	info->addrlen = 0;
	info->send = send_msg;
}

static struct dlr_node *dlr_alloc_node(size_t data_size)
{
	struct dlr_node *node;

	node = malloc(sizeof(struct dlr_node));
	if (!node)
		return NULL;
	node->data = malloc(data_size);
	if (!node->data) {
		free(node);
		return NULL;
	}
	return node;
}  /* dlr_alloc_node */

static void dlr_free_node(struct dlr_node *node)
{
	struct dlr_net_info *data;

	data = node->data;
	if (data->dlr.max_cnt)
		free(data->dlr.nodes);

	/* Free the node data. */
	free(node->data);

	/* Free the node. */
	free(node);
}  /* dlr_free_node */

static void dlr_exit_list(struct dlr_node_anchor *list)
{
	struct dlr_node *prev;
	struct dlr_node *next;

	prev = &list->anchor;
	next = prev->next;
	while (next) {
printf("D\n");
		prev = next;
		next = next->next;
		dlr_free_node(prev);
	}
	list->anchor.next = NULL;
}  /* dlr_exit_list */

static void dlr_init_list(struct dlr_node_anchor *list)
{
	list->last = &list->anchor;
	list->anchor.next = NULL;
}  /* dlr_init_list */

static void *dlr_find_node(struct dlr_node_anchor *list,
	int (*cmp)(void *a, void *b), void *data)
{
	int c;
	struct dlr_node *prev;
	struct dlr_node *next;

	prev = &list->anchor;
	next = prev->next;
	while (next) {
		c = cmp(next->data, data);

		/* Exact match. */
		if (!c)
			goto dlr_find_node_done;

		/* Will not be found as list is sorted. */
		if (c > 0) {
			next = NULL;
			break;
		}
		prev = next;
		next = prev->next;
	}

dlr_find_node_done:
	list->last = prev;
	return next;
}  /* dlr_find_node */

static void dlr_insert_node(struct dlr_node_anchor *list,
	int (*cmp)(void *a, void *b), struct dlr_node *this)
{
	int c;
	struct dlr_node *prev;
	struct dlr_node *next;

	if (list->last != &list->anchor) {
		prev = list->last;
		next = prev->next;
		c = 1;
		if (next) {
			c = cmp(next->data, this->data);
		}
		if (c > 0) {
			this->next = prev->next;
			prev->next = this;
			list->last = &list->anchor;
			return;
		}
	}
	prev = &list->anchor;
	next = prev->next;
	while (next) {
		c = cmp(next->data, this->data);

		/* Stop if next one is higher in the list. */
		if (c > 0)
			break;
		prev = next;
		next = prev->next;
	}
	this->next = prev->next;
	prev->next = this;
printf("insert\n");
	list->last = &list->anchor;
}  /* dlr_insert_node */

static void dlr_delete_node(struct dlr_node_anchor *list,
	int (*cmp)(void *a, void *b), struct dlr_node *this)
{
	int c;
	struct dlr_node *prev;
	struct dlr_node *next;

	if (list->last != &list->anchor) {
		prev = list->last;
		next = prev->next;
		c = 1;
		if (next == this)
			c = 0;
		else if (next)
			c = cmp(next->data, this->data);

		/* Exact match. */
		if (!c)
			goto dlr_delete_this_node_done;
	}
	prev = &list->anchor;
	next = prev->next;
	while (next) {
		c = cmp(next->data, this->data);

		/* Exact match. */
		if (!c)
			goto dlr_delete_this_node_done;

		/* Stop if next one is higher in the list. */
		if (c > 0)
			break;
		prev = next;
		next = prev->next;
	}

	/* Nothing is removed. */
	return;

dlr_delete_this_node_done:
	prev->next = this->next;
	list->last = &list->anchor;

	dlr_free_node(next);
}  /* dlr_delete_node */

static int cmp_dlr(void *first, void *second)
{
	int cmp;

	struct dlr_net_info *a = first;
	struct dlr_net_info *b = second;

	cmp = memcmp(&a->node.ip_addr, &b->node.ip_addr, 4);
#if 0
	if (!cmp)
		cmp = memcmp(a->node.addr, b->node.addr, ETH_ALEN);
#endif
	return cmp;
}  /* cmp_dlr */

static struct dlr_node *dlr_get_node(struct dlr_node_anchor *list,
	struct ksz_net_info *net)
{
	struct dlr_node *node;
	struct dlr_net_info data;
	struct ksz_dlr_active_node active;
	struct sockaddr_in *addr4 = NULL;
	struct sockaddr_in6 *addr6;

	if (AF_INET6 == net->family) {
		addr6 = (struct sockaddr_in6 *) net->addr;
	} else if (AF_INET == net->family) {
		addr4 = (struct sockaddr_in *) net->addr;
		memcpy(&active.ip_addr, &addr4->sin_addr, 4);
		memset(&active.addr, 0, ETH_ALEN);
	}
	memcpy(&data.node, &active, sizeof(struct ksz_dlr_active_node));
	node = dlr_find_node(list, cmp_dlr, &data);
	if (!node) {
		struct dlr_net_info *info;

		node = dlr_alloc_node(sizeof(struct dlr_net_info));
		if (!node)
			return NULL;
		info = node->data;
		memcpy(&info->node, &active,
			sizeof(struct ksz_dlr_active_node));
		memcpy(&info->addr, addr4, sizeof(struct sockaddr_in));
		memcpy(&info->net, net, sizeof(struct ksz_net_info));
		info->net.addr = (struct sockaddr *) &info->addr;
		dlr_insert_node(list, cmp_dlr, node);
	}
	return node;
}  /* dlr_get_node */

void proc_dlr_resp(struct dlr_node *node, void *fd, struct dlr_info *info)
{
	struct dlr_net_info *data = node->data;
	struct ksz_net_info *net = fd;
	struct dlr_msg *msg = net->msg;
	int i;
	int proc;

	proc = 1;
	switch (msg->hdr.svc) {
	case SVC_DLR_VERIFY_FAULT_LOCATION:
		print_dlr_msg(info->err);
		break;
	case SVC_DLR_CLEAR_RAPID_FAULTS:
		print_dlr_msg(info->err);
		break;
	case SVC_DLR_RESTART_SIGN_ON:
		print_dlr_msg(info->err);
		break;
	case SVC_DLR_CLEAR_GATEWAY_PARTIAL_FAULT:
		print_dlr_msg(info->err);
		break;
	default:
		proc = 0;
		break;
	}
	if (proc)
		return;
	proc = 1;
	switch (msg->hdr.class) {
	case DLR_GET_REVISION:
		printf("revision: %u\n", info->rev);
		break;
	default:
		proc = 0;
		break;
	}
	if (proc)
		return;
	proc = 1;
	switch (msg->hdr.id) {
	case 0:
		print_all(&info->capable);
		if (DLR_STAT_ACTIVE_SUPERVISOR == info->capable.super_status) {
			if (memcmp(&info->capable.active_super_addr,
			    &data->node, sizeof(struct ksz_dlr_active_node)))
printf(" !!\n");
			active_node = node;
			memcpy(&net_info, &data->net,
				sizeof(struct ksz_net_info));
			memcpy(&active_dlr.capable, &info->capable,
				sizeof(struct ksz_dlr_gateway_capable));
			active_dlr.topology = info->capable.net_topology;
			active_dlr.network = info->capable.net_status;
			active_dlr.super_status = info->capable.super_status;
			memcpy(&active_dlr.super_cfg,
				&info->capable.super_cfg,
				sizeof(struct ksz_dlr_super_cfg));
			memcpy(active_dlr.last_active,
				info->capable.last_active,
				sizeof(struct ksz_dlr_active_node) * 2);
			memcpy(&active_dlr.super_addr, &info->super_addr,
				sizeof(struct ksz_dlr_active_node));
			active_dlr.flags = info->capable.cap;
		}
		break;
	case DLR_GET_NETWORK_TOPOLOGY:
		if (!active_node || active_node == node)
			print_topology(info->topology);
		if (active_node == node)
			active_dlr.topology = info->topology;
		break;
	case DLR_GET_NETWORK_STATUS:
		if (!active_node || active_node == node)
			print_network(info->network);
		if (active_node == node)
			active_dlr.network = info->network;
		break;
	case DLR_GET_RING_SUPERVISOR_STATUS:
		if (!active_node || active_node == node)
			print_status(info->super_status);
		if (active_node == node)
			active_dlr.super_status = info->super_status;
		break;
	case DLR_SET_RING_SUPERVISOR_CONFIG:
		if (!active_node || active_node == node)
			print_super_cfg(&info->super_cfg);
		if (active_node == node)
			memcpy(&active_dlr.super_cfg, &info->super_cfg,
				sizeof(struct ksz_dlr_super_cfg));
		break;
	case DLR_SET_RING_FAULT_COUNT:
		if (!active_node || active_node == node)
			printf("ring fault cnt: %u\n", info->fault_cnt);
		if (active_node == node)
			active_dlr.fault_cnt = info->fault_cnt;
		break;
	case DLR_GET_LAST_ACTIVE_NODE_ON_PORT_1:
		if (!active_node || active_node == node) {
			print_dlr_node(&info->last_active[0]);
			print_dlr_node(&info->last_active[1]);
		}
		if (active_node == node)
			memcpy(active_dlr.last_active, info->last_active,
				sizeof(struct ksz_dlr_active_node) * 2);
		break;
	case DLR_GET_RING_PARTICIPANTS_COUNT:
		if (!active_node || active_node == node)
			printf("ring part cnt: %u\n", info->node_cnt);
		if (active_node == node) {
			active_dlr.node_cnt = info->node_cnt;
			if (info->max_cnt < active_dlr.node_cnt) {
				if (info->max_cnt)
					free(info->nodes);
				info->max_cnt = info->node_cnt;
				info->nodes = malloc(
					sizeof(struct ksz_dlr_active_node) *
					info->node_cnt);
			}
			if (active_dlr.max_cnt < active_dlr.node_cnt) {
				if (active_dlr.max_cnt)
					free(active_dlr.nodes);
				active_dlr.max_cnt = active_dlr.node_cnt;
				active_dlr.nodes = malloc(
					sizeof(struct ksz_dlr_active_node) *
					active_dlr.node_cnt);
			}
		}
		break;
	case DLR_GET_RING_PARTICIPANTS_LIST:
		for (i = 0; i < info->node_cnt; i++)
			print_dlr_node(&info->nodes[i]);
		if (active_node == node) {
			if (active_dlr.max_cnt >= info->node_cnt) {
				memcpy(active_dlr.nodes, info->nodes,
					sizeof(struct ksz_dlr_active_node) *
					info->node_cnt);
			}
		}
		break;
	case DLR_GET_ACTIVE_SUPERVISOR_ADDRESS:
		if (!active_node || active_node == node)
			print_dlr_node(&info->super_addr);
		if (active_node == node) {
			memcpy(&active_dlr.super_addr, &info->super_addr,
				sizeof(struct ksz_dlr_active_node));
		} else {
			if (memcmp(&active_dlr.super_addr, &info->super_addr,
			    sizeof(struct ksz_dlr_active_node)))
printf(" !!\n");
		}
		break;
	case DLR_GET_ACTIVE_SUPERVISOR_PRECEDENCE:
		if (!active_node || active_node == node)
			printf("precedence: %u\n", info->prec);
		if (active_node == node) {
			active_dlr.prec = info->prec;
		} else {
			if (info->prec != active_dlr.prec)
				printf("prec %d %d\n", info->prec,
					active_dlr.prec);
		}
		break;
	case DLR_GET_CAPABILITY_FLAGS:
		print_dlr_cap(info->flags);
		if (active_node == node)
			active_dlr.flags = info->flags;
		break;
	case DLR_SET_IP_ADDRESS:
		if (info->node.ip_addr) {
if (info->node.ip_addr != data->node.ip_addr)
printf(" ! same\n");
			memcpy(data->node.addr, info->node.addr, ETH_ALEN);
printf(" first\n");
			if (!node->link)
				w_dlr_all(net, NULL);
		} else {
printf("leave\n");
			if (active_node == node)
				active_node = NULL;
			dlr_delete_node(&dlr_list, cmp_dlr, node);
		}
		break;
	default:
		proc = 0;
		break;
	}
	if (proc)
		return;
}  /* proc_dlr_resp */

static void print_dlr_list(void)
{
	struct dlr_net_info *info;
	struct dlr_node *next = dlr_list.anchor.next;

printf("---\n");
	while (next) {
		info = next->data;
		print_dlr_node(&info->node);
printf(" - ");
		print_dlr_node(&info->dlr.node);
		next = next->next;
	}
printf("+++\n");
}

static void print_dlr_ring(void)
{
	struct dlr_net_info *info;
	struct dlr_node *link = dlr_list.anchor.link;

printf("---\n");
	while (link) {
		info = link->data;
		print_dlr_node(&info->dlr.node);
		link = link->next;
	}
printf("+++\n");
}

void proc_msg(struct ksz_net_info *net_info)
{
	struct ksz_net_msg *msg = net_info->msg;
	int len = net_info->len;
	int msglen;
	u16 seqid;
	struct dlr_node *node;
	struct dlr_net_info *info;
	int rc = 0;

	msglen = ntohs(msg->hdr.messageLength);
	if (msglen != len) {
		if (AF_PACKET != ip_family && dbg_rcv >= 4)
			printf("  \nlen %d != %d\n", msglen, len);
		if (msglen > len)
			msglen = len;
	}
	seqid = ntohs(msg->hdr.sequenceId);
	if (DEV_MOD_DLR == msg->hdr.mod) {
		node = dlr_get_node(&dlr_list, net_info);
		if (!node)
			return;
		info = node->data;
		rc = proc_dlr_msg(net_info, &info->dlr);
		if (1 == rc) {
			proc_dlr_resp(node, net_info, &info->dlr);
		} else if (0 == rc && DLR_SET_IP_ADDRESS == msg->hdr.id)
			w_dlr_ip_addr(net_info, &dlr.node);
	}
}  /* proc_msg */

struct sock_buf {
	struct sockaddr *from;
	u8 *buf;
	int len;
};

static int check_loop(struct sockaddr *sa, int salen)
{
	struct sockaddr_in *addr4;
	struct sockaddr_in6 *addr6;

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
	SOCKET fd[1];
	struct sock_buf buf[2];
	struct sockaddr_in6 cliaddr[2];
	struct sockaddr_in *addr4;
	struct sockaddr_in6 *addr6;
	struct timeval timer;
	fd_set rset;
	fd_set allrset;
	socklen_t len;
	int maxfdp1;
	struct ksz_net_msg *msg;
	int i;
	char in_addr[80];
	int cur;
	int last;
	int nsel;
	int looped;
	int msglen;
	struct ksz_net_info *net_info;

	pTaskParam = (PTTaskParam) param;
	fd[0] = (SOCKET) pTaskParam->multicast;
	net_info = pTaskParam->info;
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
	maxfdp1 = fd[0];
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

		for (i = 0; i < 1; i++) {
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
				memcpy(&client_addr6, addr6,
					sizeof(struct sockaddr_in6));
				net_info->addr = (struct sockaddr *)
					&client_addr6;
				net_info->addrlen =
					sizeof(struct sockaddr_in6);
			} else if (AF_INET == buf[cur].from->sa_family) {
				addr4 = (struct sockaddr_in *) buf[cur].from;
				inet_ntop(AF_INET, &addr4->sin_addr,
					in_addr, sizeof(in_addr));
				memcpy(&client_addr, addr4,
					sizeof(struct sockaddr_in));
				net_info->addr = (struct sockaddr *)
					&client_addr;
				net_info->addrlen =
					sizeof(struct sockaddr_in);
			}
			if (dbg_rcv)
				Pthread_mutex_lock(&disp_mutex);
			if (dbg_rcv >= 4)
				printf("r: %d=%d %d=%s\n", sockfd,
					buf[cur].len, len, in_addr);
			msglen = buf[cur].len;
			msg = (struct ksz_net_msg *) buf[cur].buf;
			looped = check_loop(buf[cur].from, len);
			if (looped) {
				int ignored = 1;

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
			net_info->msg = msg;
			net_info->len = msglen;
			proc_msg(net_info);
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

static void handle_dlr_msg(u16 cmd, void *data, int len)
{
	u32 *dword = data;

	switch (cmd) {
	case DEV_INFO_QUIT:
		break;
	case DEV_INFO_DLR_LINK:
	{
		len -= 4;
		printf("link status: x%x\n", *dword);
		if (len >= 4 + sizeof(struct ksz_dlr_active_node)) {
			struct ksz_dlr_active_node *active =
				(struct ksz_dlr_active_node *)(dword + 1);

			print_dlr_node(active);
		}
		break;
	}
	case DEV_INFO_DLR_CFG:
		printf("cfg: %x\n", *dword);
		break;
	}
}

static void handle_hsr_msg(u16 cmd, void *data, int len)
{
	u32 *dword = data;

	switch (cmd) {
	case DEV_INFO_QUIT:
		break;
	case DEV_INFO_HSR_LINK:
	{
		len -= 4;
		printf("link status: x%x\n", *dword);
		if (len >= 4 + sizeof(struct ksz_hsr_node)) {
			struct ksz_hsr_node *active =
				(struct ksz_hsr_node *)(dword + 1);

			print_hsr_node(active);
		}
		break;
	}
	}
}

static void handle_sw_msg(u16 cmd, void *data, int len)
{
	u32 *dword = data;

	switch (cmd) {
	case DEV_INFO_QUIT:
		break;
	case DEV_INFO_SW_LINK:
	{
		break;
	}
	case DEV_INFO_SW_ACL:
		printf("acl: %x\n", *dword);
		break;
	}
}

#if 0
void *NotificationTask(void *param)
{
	int len;
	u8 data[MAX_REQUEST_SIZE];
	PTTaskParam pTaskParam = param;

	pTaskParam->fTaskStop = FALSE;
	do {
		len = sw_recv(&swdev, data, MAX_REQUEST_SIZE);
		if (len > 0) {
			struct ksz_resp_msg *msg = (struct ksz_resp_msg *)
				data;

			switch (msg->module) {
			case DEV_MOD_BASE:
				handle_sw_msg(msg->cmd, msg->resp.data, len);
				break;
			case DEV_MOD_DLR:
				handle_dlr_msg(msg->cmd, msg->resp.data, len);
				break;
			case DEV_MOD_HSR:
				handle_hsr_msg(msg->cmd, msg->resp.data, len);
				break;
			default:
				printf("[%d] ", len);
				fflush(stdout);
			}
		}
	} while (!pTaskParam->fTaskStop);
	return NULL;
}
#endif

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
#endif

int main(int argc, char *argv[])
{
	TTaskParam param[2];

#ifdef _SYS_SOCKET_H
	pthread_t tid[2];
	void *status;

#elif defined( _WIN32 )
	DWORD rc;
#endif
	char dest_ip[40];
	char host_ip4[40];
	char host_ip6[40];
	char *host_ip;
	int family;
	char *multi_ip = NULL;
	int i;
	struct ip_info info;
	int multi_loop = 0;

	SocketInit(0);

	if (argc < 2) {
		printf("usage: %s <local_if>\n",
			argv[0]);
		return 1;
	}
	family = AF_INET;
	dest_ip[0] = '\0';
	strcpy(KSZ_ip_addr6, KSZ_ip_addr6_const);
	if (argc > 2) {
		i = 2;
		while (i < argc) {
			if ('-' == argv[i][0]) {
				switch (argv[i][1]) {
				case '6':
					family = AF_INET6;
					if (argv[i][2]) {
						KSZ_ip_addr6[3] = argv[i][2];
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
				case 'u':
					++i;
					strcpy(dest_ip, argv[i]);
					break;
				case 'v':
					++i;
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
	} else {
		printf("cannot locate IP address\n");
		exit(1);
	}

	ip_family = family;
	if (AF_INET6 == family) {
		host_ip = host_ip6;
		event_addr6.sin6_family = family;
		event_addr6.sin6_port = htons(KSZ_EVENT_PORT);

		multi_ip = KSZ_ip_addr6;

		inet_pton(family, multi_ip, &event_addr6.sin6_addr);
	} else {
		family = AF_INET;
		host_ip = host_ip4;
		event_addr.sin_family = family;
		event_addr.sin_port = htons(KSZ_EVENT_PORT);

		multi_ip = KSZ_ip_addr;

		event_addr.sin_addr.s_addr = inet_addr(multi_ip);
	}

	event_fd = create_sock(argv[1], multi_ip, host_ip, KSZ_EVENT_PORT, 0);
	if (event_fd < 0) {
		printf("Cannot create socket\n");
		return 1;
	}
	sockptr = &event_fd;

	init_net_info(&net_info, family);
	dlr.max_cnt = 0;
	active_dlr.max_cnt = 0;
	dlr_init_list(&dlr_list);

	i = 0;
	param[i].fTaskStop = FALSE;
	param[i].multicast = event_fd;
	param[i].info = &net_info;

#ifdef _SYS_SOCKET_H
	Pthread_create(&tid[i], NULL, ReceiveTask, &param[i]);
#if 0
	Pthread_create(&tid[1], NULL, NotificationTask, &param[1]);
#endif

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

	if ( !param[0].fTaskStop ) {
		int rc;

		dlr.node.ip_addr = (host_addr[0]) | (host_addr[1] << 8) |
			(host_addr[2] << 16) | (host_addr[3] << 24);
		memcpy(dlr.node.addr, hw_addr, ETH_ALEN);

		/* Signal server is ready. */
		w_dlr_ip_addr(&net_info, &dlr.node);
#if 0
		rc = sw_dev_init(&swdev, 0, &sw_version, &sw_ports);
		if (rc) {
			print_sw_err(rc);
			param[0].fTaskStop = TRUE;
			param[1].fTaskStop = TRUE;
			goto done;
		}
		rc = set_sw_notify(&swdev,
			SW_INFO_LINK_CHANGE);
			rc = set_dlr_notify(&swdev,
				DLR_INFO_CFG_CHANGE | DLR_INFO_LINK_LOST);
			rc = set_hsr_notify(&swdev,
				HSR_INFO_LINK_LOST);
#endif
		rc = 1;
		do {
			switch (rc) {
			case 1:
				rc = get_dlr_cmd(stdin);
				break;
#if 0
			case 2:
				rc = 3;
				rc = get_hsr_cmd(stdin);
				break;
			default:
				rc = get_cmd(stdin);
				break;
#endif
			}
			if (!rc)
				break;
		} while (1);

		/* Signal server is quitting. */
		net_info.addr = NULL;
		memset(&dlr.node, 0, sizeof(struct ksz_dlr_active_node));
		w_dlr_ip_addr(&net_info, &dlr.node);
		dlr_exit_list(&dlr_list);

		param[1].fTaskStop = TRUE;
		param[0].fTaskStop = TRUE;
	}

#if 0
done:
#endif
	// wait for task to end
	i = 0;

#ifdef _SYS_SOCKET_H
	Pthread_join(tid[0], &status);
#if 0
	Pthread_join(tid[1], &status);
#endif

#elif defined( _WIN32 )
	rc = WaitForSingleObject( param[i].hevTaskComplete, INFINITE );
	if ( WAIT_FAILED == rc ) {

	}
	ResetEvent( param[i].hevTaskComplete );
	Sleep( 1 );

#else
	DelayMillisec( 200 );
#endif
	if (dlr.max_cnt)
		free(dlr.nodes);
	if (active_dlr.max_cnt)
		free(active_dlr.nodes);

	closesocket(event_fd);
	SocketExit();

	return 0;
}
