#include "unpifi.h"


int main(int argc, char **argv)
{
	struct ifi_info *ifi;
	struct ifi_info *ifihead;
	struct sockaddr *sa;
	u_char *ptr;
	int i;
	int family = AF_INET;
	int doaliases;
	int notfirst;
	char addr[128 + 8];
	size_t len = sizeof(addr);

	if (argc != 3)
		err_quit("usage: prifinfo <inet4|inet6> <doaliases>");

	if (strcmp(argv[1], "inet4") == 0)
		family = AF_INET;
	else if (strcmp(argv[1], "inet6") == 0)
		family = AF_INET6;
	else
		err_quit("invalid <address-family>");
	doaliases = atoi(argv[2]);

	ifihead = get_ifi_info(family, doaliases);
	for (ifi = ifihead; ifi != NULL; ifi = ifi->ifi_next) {
		printf("%s=%d: <", ifi->ifi_name, ifi->ifi_index);
		notfirst = 0;
		if (ifi->ifi_flags & IFF_UP) {
			printf("UP");
			notfirst = 1;
		}
		if (ifi->ifi_flags & IFF_BROADCAST) {
			if (notfirst)
				printf(" ");
			printf("BCAST");
			notfirst = 1;
		}
		if (ifi->ifi_flags & IFF_MULTICAST) {
			if (notfirst)
				printf(" ");
			printf("MCAST");
			notfirst = 1;
		}
		if (ifi->ifi_flags & IFF_LOOPBACK) {
			if (notfirst)
				printf(" ");
			printf("LOOP");
			notfirst = 1;
		}
		if (ifi->ifi_flags & IFF_POINTOPOINT) {
			if (notfirst)
				printf(" ");
			printf("P2P");
			notfirst = 1;
		}
		printf(">\n");

		if ((i = ifi->ifi_hlen) > 0) {
			ptr = ifi->ifi_haddr;
			do {
				printf("%s%02x", (i == ifi->ifi_hlen) ? "  " :
					":", *ptr++);
			} while (--i > 0);
			printf("\n");
		}
		if ((sa = ifi->ifi_addr) != NULL)
			printf("  IP addr: %s\n",
				sock_ntop_host(sa, sizeof(*sa), addr, len));
		if ((sa = ifi->ifi_addr6) != NULL)
			printf("  IPv6 addr: %s/%d Scope:%s\n",
				sock_ntop_host(sa, sizeof(*sa), addr, len),
					ifi->ifi_plen,
					ipv6_scope(ifi->ifi_scope));
		if ((sa = ifi->ifi_brdaddr) != NULL)
			printf("  broadcast addr: %s\n",
				sock_ntop_host(sa, sizeof(*sa), addr, len));
		if ((sa = ifi->ifi_dstaddr) != NULL)
			printf("  destination addr: %s\n",
				sock_ntop_host(sa, sizeof(*sa), addr, len));
	}
	free_ifi_info(ifihead);
	return 0;
}
