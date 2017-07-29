#include "wnp.h"


char *sock_ntop_(const struct sockaddr *sa, socklen_t salen, char *str,
	size_t len, int doport)
{
	struct sockaddr_in *sin;
	struct sockaddr_in6 *sin6;
	short port;
	char portstr[8];

	switch (sa->sa_family) {
	case AF_INET:
		sin = (struct sockaddr_in *) sa;
		if (inet_ntop(AF_INET, &sin->sin_addr, str, len) == NULL)
			return NULL;
		port = ntohs(sin->sin_port);
		if (doport && port != 0) {
			snprintf(portstr, sizeof(portstr), ".%d", port);
			strcat(str, portstr);
		}
		return str;
	case AF_INET6:
		sin6 = (struct sockaddr_in6 *) sa;
		if (inet_ntop(AF_INET6, &sin6->sin6_addr, str, len) == NULL)
			return NULL;
		port = ntohs(sin6->sin6_port);
		if (doport && port != 0) {
			snprintf(portstr, sizeof(portstr), ".%d", port);
			strcat(str, portstr);
		}
		return str;
	}
	return NULL;
}


char *sock_ntop(const struct sockaddr *sa, socklen_t salen, char *str,
	size_t len)
{
	return sock_ntop_(sa, salen, str, len, 1);
}


char *sock_ntop_host(const struct sockaddr *sa, socklen_t salen, char *str,
	size_t len)
{
	return sock_ntop_(sa, salen, str, len, 0);
}
