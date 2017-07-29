#include "unpifi.h"

#ifdef _SYS_SOCKET_H
#include <linux/sockios.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define _PATH_PROCNET_IFINET6           "/proc/net/if_inet6"

#define IPV6_ADDR_LOOPBACK      0x0010U
#define IPV6_ADDR_LINKLOCAL     0x0020U
#define IPV6_ADDR_SITELOCAL     0x0040U

#define IPV6_ADDR_COMPATv4      0x0080U

#define IPV6_ADDR_SCOPE_MASK    0x00f0U

struct ipv6_info {
	char devname[20];
	struct sockaddr_in6 addr;
	int plen;
	int scope;
	int if_idx;
};

char *ipv6_scope(int scope)
{
	char *str;

	switch (scope & IPV6_ADDR_SCOPE_MASK) {
	case 0:
		str = "Global";
		break;
	case IPV6_ADDR_LINKLOCAL:
		str = "Link";
		break;
	case IPV6_ADDR_SITELOCAL:
		str = "Site";
		break;
	case IPV6_ADDR_COMPATv4:
		str = "Compat";
		break;
	case IPV6_ADDR_LOOPBACK:
		str = "Host";
		break;
	default:
		str = "Unknown";
	}
	return str;
}

static struct ipv6_info *found_ipv6(char *name, struct ipv6_info *head)
{
	struct ipv6_info *ipv6 = head;

	while (AF_INET6 == ipv6->addr.sin6_family) {
		if (!strcmp(name, ipv6->devname))
			return ipv6;
		ipv6++;
	}
	return NULL;
}
#endif

struct ifi_info *get_ifi_info(int family, int doaliases)
{
	struct ifi_info *ifi;
	struct ifi_info *ifihead;
	struct ifi_info **ifipnext;
	int sockfd;
	int len;
	int lastlen;
	int flags;
	int myflags;
	char *ptr;
	char *buf;
	char lastname[IFNAMSIZ];
	char *cptr;
	struct ifconf ifc;
	struct ifreq *ifr;
	struct ifreq ifrcopy;
	struct sockaddr_in *sinptr;
	struct sockaddr_in6 *sin6ptr;

#ifdef _SYS_SOCKET_H
	FILE *f;
	int dad_status;
	int count;
	char addr6[40];
	char addr6p[8][5];

	struct ipv6_info *ipv6;
	struct ipv6_info *ipv6head = NULL;

	f = fopen(_PATH_PROCNET_IFINET6, "r");
	if (!f)
		goto create_sock;
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
		ipv6++;
		count--;
		if (1 == count)
			break;
	}
	ipv6->addr.sin6_family = AF_UNSPEC;
	fclose(f);

create_sock:
#endif
	sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

	lastlen = 0;

	/* initial buffer size guess */
	len = 100 * sizeof(struct ifreq);
	for (;;) {
		buf = malloc(len);
		ifc.ifc_len = len;
		ifc.ifc_buf = buf;
		if (ioctl(sockfd, SIOCGIFCONF, &ifc) < 0) {
			if (!invalid_err() || lastlen != 0)
				err_sys("ioctl error");
		} else {
			if (ifc.ifc_len == lastlen)
				break;
			lastlen = ifc.ifc_len;
		}
		len += 10 * sizeof(struct ifreq);
		free(buf);
	}
	ifihead = NULL;
	ifipnext = &ifihead;
	lastname[0] = 0;
	for (ptr = buf; ptr < buf + ifc.ifc_len; ) {
		ifr = (struct ifreq *)(void *) ptr;

#ifdef HAVE_SOCKADDR_SA_LEN
		len = max(sizeof(struct sockaddr), ifr->ifr_addr.sa_len);
#else
		switch (ifr->ifr_addr.sa_family) {
		case AF_INET6:
			len = sizeof(struct sockaddr_in6);
			break;
		case AF_INET:
		default:
			len = sizeof(struct sockaddr);
			break;
		}
#endif
		ptr += sizeof(ifr->ifr_name) + len;

		if (ifr->ifr_addr.sa_family != family)
			continue;

		myflags = 0;
		if ((cptr = strchr(ifr->ifr_name, ':')) != NULL)
			*cptr = 0;
		if (strncmp(lastname, ifr->ifr_name, IFNAMSIZ) == 0) {
			if (doaliases == 0)
				continue;
			myflags = IFI_ALIAS;
		}
		memcpy(lastname, ifr->ifr_name, IFNAMSIZ);

		ifrcopy = *ifr;
		ioctl(sockfd, SIOCGIFFLAGS, &ifrcopy);
		flags = ifrcopy.ifr_flags;
		if ((flags & IFF_UP) == 0)
			continue;

		ifi = calloc(1, sizeof(struct ifi_info));
		*ifipnext = ifi;
		ifipnext = &ifi->ifi_next;

		ifi->ifi_flags = flags;
		ifi->ifi_myflags = myflags;
		memcpy(ifi->ifi_name, ifr->ifr_name, IFI_NAME);
		ifi->ifi_name[IFI_NAME - 1] = '\0';
		switch (ifr->ifr_addr.sa_family) {
		case AF_INET:
			sinptr = (struct sockaddr_in *) &ifr->ifr_addr;
			if (ifi->ifi_addr == NULL) {
				ifi->ifi_addr = calloc(1,
					sizeof(struct sockaddr_in));
				memcpy(ifi->ifi_addr, sinptr,
					sizeof(struct sockaddr_in));

#ifdef _SYS_SOCKET_H
				ipv6 = found_ipv6(ifr->ifr_name, ipv6head);
				if (ipv6) {
					ifi->ifi_addr6 = calloc(1,
						sizeof(struct sockaddr_in6));
					memcpy(ifi->ifi_addr6, &ipv6->addr,
						sizeof(struct sockaddr_in6));
					ifi->ifi_plen = ipv6->plen;
					ifi->ifi_scope = ipv6->scope;
				}
#endif
#ifdef SIOCGIFBRDADDR
				if (flags & IFF_BROADCAST) {
					ioctl(sockfd, SIOCGIFBRDADDR, &ifrcopy);
					sinptr = (struct sockaddr_in *)
						&ifrcopy.ifr_broadaddr;
					ifi->ifi_brdaddr = calloc(1,
						sizeof(struct sockaddr_in));
					memcpy(ifi->ifi_brdaddr, sinptr,
						sizeof(struct sockaddr_in));
				}
#endif
#ifdef SIOCGIFDSTADDR
				if (flags & IFF_POINTOPOINT) {
					ioctl(sockfd, SIOCGIFDSTADDR, &ifrcopy);
					sinptr = (struct sockaddr_in *)
						&ifrcopy.ifr_dstaddr;
					ifi->ifi_dstaddr = calloc(1,
						sizeof(struct sockaddr_in));
					memcpy(ifi->ifi_dstaddr, sinptr,
						sizeof(struct sockaddr_in));
				}
#endif
			}
			break;
		case AF_INET6:
			sin6ptr = (struct sockaddr_in6 *) &ifr->ifr_addr;
			if (ifi->ifi_addr == NULL) {
				ifi->ifi_addr = calloc(1,
					sizeof(struct sockaddr_in6));
				memcpy(ifi->ifi_addr, sin6ptr,
					sizeof(struct sockaddr_in6));
			}
			break;
		default:
			break;
		}
		if (ioctl(sockfd, SIOCGIFHWADDR, &ifrcopy) >= 0) {
			switch (ifrcopy.ifr_addr.sa_family) {
			case AF_LOCAL:
				ifi->ifi_hlen = 6;
				memcpy(ifi->ifi_haddr,
					ifrcopy.ifr_addr.sa_data,
					ifi->ifi_hlen);
				break;
			}
		}
		if (ioctl(sockfd, SIOCGIFINDEX, &ifrcopy) >= 0)
			ifi->ifi_index = ifrcopy.ifr_ifindex;
	}

#ifdef _SYS_SOCKET_H
	if (ipv6head)
		free(ipv6head);
#endif
	free(buf);
	close(sockfd);
	return ifihead;
}

void free_ifi_info(struct ifi_info *ifihead)
{
	struct ifi_info *ifi;
	struct ifi_info *ifinext;

	for (ifi = ifihead; ifi != NULL; ifi = ifinext) {
		if (ifi->ifi_addr != NULL)
			free(ifi->ifi_addr);
		if (ifi->ifi_brdaddr != NULL)
			free(ifi->ifi_brdaddr);
		if (ifi->ifi_dstaddr != NULL)
			free(ifi->ifi_dstaddr);
		ifinext = ifi->ifi_next;
		free(ifi);
	}
}
