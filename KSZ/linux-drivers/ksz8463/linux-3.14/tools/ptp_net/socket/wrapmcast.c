

#include "wnp.h"
#include <linux/sockios.h>
#include <net/if.h>
#include <errno.h>
#include <sys/ioctl.h>


int
mcast_join(int sockfd, const SA *sa, socklen_t salen,
		   const char *ifname, u_int ifindex)
{
	switch (sa->sa_family) {
	case AF_INET: {
		struct ip_mreq		mreq;
		struct ifreq		ifreq;

		memcpy(&mreq.imr_multiaddr,
			   &((struct sockaddr_in *) sa)->sin_addr,
			   sizeof(struct in_addr));

		if (ifindex > 0) {
			if (if_indextoname(ifindex, ifreq.ifr_name) == NULL) {
				errno = ENXIO;	/* i/f index not found */
				return(-1);
			}
			goto doioctl;
		} else if (ifname != NULL) {
			strncpy(ifreq.ifr_name, ifname, IFNAMSIZ);
doioctl:
			if (ioctl(sockfd, SIOCGIFADDR, &ifreq) < 0)
				return(-1);
			memcpy(&mreq.imr_interface,
				   &((struct sockaddr_in *) &ifreq.ifr_addr)->sin_addr,
				   sizeof(struct in_addr));
		} else
			mreq.imr_interface.s_addr = htonl(INADDR_ANY);

		return(setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP,
						  &mreq, sizeof(mreq)));
	}
/* end mcast_join1 */

/* include mcast_join2 */
#ifdef	IPV6
	case AF_INET6: {
		struct ipv6_mreq	mreq6;

		memcpy(&mreq6.ipv6mr_multiaddr,
			   &((struct sockaddr_in6 *) sa)->sin6_addr,
			   sizeof(struct in6_addr));

		if (ifindex > 0)
			mreq6.ipv6mr_interface = ifindex;
		else if (ifname != NULL)
			if ( (mreq6.ipv6mr_interface = if_nametoindex(ifname)) == 0) {
				errno = ENXIO;	/* i/f name not found */
				return(-1);
			}
		else
			mreq6.ipv6mr_interface = 0;

		return(setsockopt(sockfd, IPPROTO_IPV6, IPV6_ADD_MEMBERSHIP,
						  &mreq6, sizeof(mreq6)));
	}
#endif

	default:
		errno = EPROTONOSUPPORT;
		return(-1);
	}
}
/* end mcast_join2 */

void
Mcast_join(int sockfd, const SA *sa, socklen_t salen,
		   const char *ifname, u_int ifindex)
{
	if (mcast_join(sockfd, sa, salen, ifname, ifindex) < 0)
		err_sys("mcast_join error");
}


int
mcast_leave(int sockfd, const SA *sa, socklen_t salen)
{
	switch (sa->sa_family) {
	case AF_INET: {
		struct ip_mreq		mreq;

		memcpy(&mreq.imr_multiaddr,
			   &((struct sockaddr_in *) sa)->sin_addr,
			   sizeof(struct in_addr));
		mreq.imr_interface.s_addr = htonl(INADDR_ANY);
		return(setsockopt(sockfd, IPPROTO_IP, IP_DROP_MEMBERSHIP,
						  &mreq, sizeof(mreq)));
	}

#ifdef	IPV6
	case AF_INET6: {
		struct ipv6_mreq	mreq6;

		memcpy(&mreq6.ipv6mr_multiaddr,
			   &((struct sockaddr_in6 *) sa)->sin6_addr,
			   sizeof(struct in6_addr));
		mreq6.ipv6mr_interface = 0;
		return(setsockopt(sockfd, IPPROTO_IPV6, IPV6_DROP_MEMBERSHIP,
						  &mreq6, sizeof(mreq6)));
	}
#endif

	default:
		errno = EPROTONOSUPPORT;
		return(-1);
	}
}

void
Mcast_leave(int sockfd, const SA *sa, socklen_t salen)
{
	if (mcast_leave(sockfd, sa, salen) < 0)
		err_sys("mcast_leave error");
}


int
mcast_get_if(int sockfd)
{
#if 0
	switch (sockfd_to_family(sockfd)) {
	case AF_INET: {
		/* TODO: similar to mcast_set_if() */
		return(-1);
	}

#ifdef	IPV6
	case AF_INET6: {
		u_int		index;
		socklen_t	len;

		len = sizeof(index);
		if (getsockopt(sockfd, IPPROTO_IPV6, IPV6_MULTICAST_IF,
					   &index, &len) < 0)
			return(-1);
		return(index);
	}
#endif

	default:
		errno = EPROTONOSUPPORT;
		return(-1);
	}
#else
	return -1;
#endif
}

int
Mcast_get_if(int sockfd)
{
	int		rc;

	if ( (rc = mcast_get_if(sockfd)) < 0)
		err_sys("mcast_get_if error");
	return(rc);
}


int
mcast_get_loop(int sockfd)
{
#if 0
	switch (sockfd_to_family(sockfd)) {
	case AF_INET: {
		u_char		flag;
		socklen_t	len;

		len = sizeof(flag);
		if (getsockopt(sockfd, IPPROTO_IP, IP_MULTICAST_LOOP,
					   &flag, &len) < 0)
			return(-1);
		return(flag);
	}

#ifdef	IPV6
	case AF_INET6: {
		u_int		flag;
		socklen_t	len;

		len = sizeof(flag);
		if (getsockopt(sockfd, IPPROTO_IPV6, IPV6_MULTICAST_LOOP,
					   &flag, &len) < 0)
			return(-1);
		return(flag);
	}
#endif

	default:
		errno = EPROTONOSUPPORT;
		return(-1);
	}
#else
	return -1;
#endif
}

int
Mcast_get_loop(int sockfd)
{
	int		rc;

	if ( (rc = mcast_get_loop(sockfd)) < 0)
		err_sys("mcast_get_loop error");
	return(rc);
}


int
mcast_get_ttl(int sockfd)
{
#if 0
	switch (sockfd_to_family(sockfd)) {
	case AF_INET: {
		u_char		ttl;
		socklen_t	len;

		len = sizeof(ttl);
		if (getsockopt(sockfd, IPPROTO_IP, IP_MULTICAST_TTL,
					   &ttl, &len) < 0)
			return(-1);
		return(ttl);
	}

#ifdef	IPV6
	case AF_INET6: {
		int			hop;
		socklen_t	len;

		len = sizeof(hop);
		if (getsockopt(sockfd, IPPROTO_IPV6, IPV6_MULTICAST_HOPS,
					   &hop, &len) < 0)
			return(-1);
		return(hop);
	}
#endif

	default:
		errno = EPROTONOSUPPORT;
		return(-1);
	}
#else
	return -1;
#endif
}

int
Mcast_get_ttl(int sockfd)
{
	int		rc;

	if ( (rc = mcast_get_ttl(sockfd)) < 0)
		err_sys("mcast_get_ttl error");
	return(rc);
}


int
mcast_set_if(int sockfd, const char *ifname, u_int ifindex)
{
#if 0
	switch (sockfd_to_family(sockfd)) {
	case AF_INET: {
		struct in_addr		inaddr;
		struct ifreq		ifreq;

		if (ifindex > 0) {
			if (if_indextoname(ifindex, ifreq.ifr_name) == NULL) {
				errno = ENXIO;	/* i/f index not found */
				return(-1);
			}
			goto doioctl;
		} else if (ifname != NULL) {
			strncpy(ifreq.ifr_name, ifname, IFNAMSIZ);
doioctl:
			if (ioctl(sockfd, SIOCGIFADDR, &ifreq) < 0)
				return(-1);
			memcpy(&inaddr,
				   &((struct sockaddr_in *) &ifreq.ifr_addr)->sin_addr,
				   sizeof(struct in_addr));
		} else
			inaddr.s_addr = htonl(INADDR_ANY);	/* remove prev. set default */

		return(setsockopt(sockfd, IPPROTO_IP, IP_MULTICAST_IF,
						  &inaddr, sizeof(struct in_addr)));
	}

#ifdef	IPV6
	case AF_INET6: {
		u_int	index;

		if ( (index = ifindex) == 0) {
			if (ifname == NULL) {
				errno = EINVAL;	/* must supply either index or name */
				return(-1);
			}
			if ( (index = if_nametoindex(ifname)) == 0) {
				errno = ENXIO;	/* i/f name not found */
				return(-1);
			}
		}
		return(setsockopt(sockfd, IPPROTO_IPV6, IPV6_MULTICAST_IF,
						  &index, sizeof(index)));
	}
#endif

	default:
		errno = EPROTONOSUPPORT;
		return(-1);
	}
#else
	return -1;
#endif
}

void
Mcast_set_if(int sockfd, const char *ifname, u_int ifindex)
{
	if (mcast_set_if(sockfd, ifname, ifindex) < 0)
		err_sys("mcast_set_if error");
}


int
mcast_set_loop(int sockfd, int onoff)
{
#if 0
	switch (sockfd_to_family(sockfd)) {
	case AF_INET: {
		u_char		flag;

		flag = onoff;
		return(setsockopt(sockfd, IPPROTO_IP, IP_MULTICAST_LOOP,
						  &flag, sizeof(flag)));
	}

#ifdef	IPV6
	case AF_INET6: {
		u_int		flag;

		flag = onoff;
		return(setsockopt(sockfd, IPPROTO_IPV6, IPV6_MULTICAST_LOOP,
						  &flag, sizeof(flag)));
	}
#endif

	default:
		errno = EPROTONOSUPPORT;
		return(-1);
	}
#else
	return -1;
#endif
}
/* end mcast_set_loop */

void
Mcast_set_loop(int sockfd, int onoff)
{
	if (mcast_set_loop(sockfd, onoff) < 0)
		err_sys("mcast_set_loop error");
}


int
mcast_set_ttl(int sockfd, int val)
{
#if 0
	switch (sockfd_to_family(sockfd)) {
	case AF_INET: {
		u_char		ttl;

		ttl = val;
		return(setsockopt(sockfd, IPPROTO_IP, IP_MULTICAST_TTL,
						  &ttl, sizeof(ttl)));
	}

#ifdef	IPV6
	case AF_INET6: {
		int		hop;

		hop = val;
		return(setsockopt(sockfd, IPPROTO_IPV6, IPV6_MULTICAST_HOPS,
						  &hop, sizeof(hop)));
	}
#endif

	default:
		errno = EPROTONOSUPPORT;
		return(-1);
	}
#else
	return -1;
#endif
}

void
Mcast_set_ttl(int sockfd, int val)
{
	if (mcast_set_ttl(sockfd, val) < 0)
		err_sys("mcast_set_ttl error");
}
