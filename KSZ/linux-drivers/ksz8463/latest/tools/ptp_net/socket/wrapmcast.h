#ifndef _WRAPMCAST_H
#define _WRAPMCAST_H


int
mcast_join(int sockfd, const SA *sa, socklen_t salen,
		   const char *ifname, u_int ifindex);

void
Mcast_join(int sockfd, const SA *sa, socklen_t salen,
		   const char *ifname, u_int ifindex);

int
mcast_leave(int sockfd, const SA *sa, socklen_t salen);

void
Mcast_leave(int sockfd, const SA *sa, socklen_t salen);

int
mcast_get_if(int sockfd);

int
Mcast_get_if(int sockfd);

int
mcast_get_loop(int sockfd);

int
Mcast_get_loop(int sockfd);

int
mcast_get_ttl(int sockfd);

int
Mcast_get_ttl(int sockfd);

int
mcast_set_if(int sockfd, const char *ifname, u_int ifindex);

void
Mcast_set_if(int sockfd, const char *ifname, u_int ifindex);

int
mcast_set_loop(int sockfd, int onoff);

void
Mcast_set_loop(int sockfd, int onoff);

int
mcast_set_ttl(int sockfd, int val);

void
Mcast_set_ttl(int sockfd, int val);


#endif
