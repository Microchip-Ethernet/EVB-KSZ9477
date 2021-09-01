#ifndef _WRAPSOCK_H
#define _WRAPSOCK_H


int Accept ( int fd, struct sockaddr *sa, socklen_t *salenptr );
void Bind ( int fd, struct sockaddr *sa, socklen_t salen );
void Connect ( int fd, struct sockaddr *sa, socklen_t salen );
void Getpeername ( int fd, struct sockaddr *sa, socklen_t *salenptr );
void Getsockname ( int fd, struct sockaddr *sa, socklen_t *salenptr );
void Listen ( int fd, int backlog );
ssize_t Recv ( int fd, void *ptr, size_t nbytes, int flags );
ssize_t Recvfrom ( int fd, void *ptr, size_t nbytes, int flags,
    struct sockaddr *sa, socklen_t *salenptr );

#if !defined( __GNUC__ )  ||  defined( _SYS_SOCKET_H )
void Getsockopt ( int fd, int level, int optname, void *optval,
    socklen_t *optlenptr );
int Select ( int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds,
    struct timeval *timeout );
void Setsockopt ( int fd, int level, int optname, const void *optval,
    socklen_t optlen );
#endif
void Send ( int fd, const void *ptr, size_t nbytes, int flags );
void Sendto ( int fd, void *ptr, size_t nbytes, int flags,
    struct sockaddr *sa, socklen_t salen );
void Shutdown ( int fd, int how );
int Socket ( int family, int type, int protocol );

void tvsub ( struct timeval *tdiff, struct timeval *t1, struct timeval *t0 );

#endif
