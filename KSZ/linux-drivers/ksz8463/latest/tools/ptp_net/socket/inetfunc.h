#ifndef _INET_FUNC_H
#define _INET_FUNC_H


const char * _inet_ntop ( int af, const void *src, char *dst, size_t size );
const char * Inet_ntop ( int family, const void *addrptr, char *strptr,
    size_t len );
int inet_pton ( int af, const char *src, void *dst );
void Inet_pton ( int family, const char *strptr, void *addrptr );

char *sock_ntop(const struct sockaddr *sa, socklen_t salen, char *str,
	size_t len);
char *sock_ntop_host(const struct sockaddr *sa, socklen_t salen, char *str,
	size_t len);

#endif
