/* -----------------------------------------------------------------------------

    Modified from W. Richard Stevens's UNIX Network Programming to run under
    Windows
----------------------------------------------------------------------------- */

/*
 * Socket wrapper functions.
 * These could all go into separate files, so only the ones needed cause
 * the corresponding function to be added to the executable.  If sockets
 * are a library (SVR4) this might make a difference (?), but if sockets
 * are in the kernel (BSD) it doesn't matter.
 *
 * These wrapper functions also use the same prototypes as POSIX.1g,
 * which might differ from many implementations (i.e., POSIX.1g specifies
 * the fourth argument to getsockopt() as "void *", not "char *").
 *
 * If your system's headers are not correct [i.e., the Solaris 2.5
 * <sys/socket.h> omits the "const" from the second argument to both
 * bind() and connect()], you'll get warnings of the form:
 *warning: passing arg 2 of `bind' discards `const' from pointer target type
 *warning: passing arg 2 of `connect' discards `const' from pointer target type
 */

#include "wnp.h"


int
Accept (
    int             fd,
    struct sockaddr *sa,
    socklen_t       *salenptr )
{
    int n;

#ifndef __GNUC__
again:
#endif
    if ( ( n = accept( fd, sa, salenptr )) < 0 ) {

#ifndef __GNUC__
        if ( WSAGetLastError() == WSAECONNABORTED )
            goto again;
        else
#endif
            err_sys( "accept error" );
    }
    return( n );
}  /* Accept */


void
Bind (
    int             fd,
    struct sockaddr *sa,
    socklen_t       salen )
{
    if ( bind( fd, sa, salen ) < 0 )
        err_sys( "bind error" );
}  /* Bind */


void
Connect (
    int             fd,
    struct sockaddr *sa,
    socklen_t       salen )
{
    if ( connect( fd, sa, salen ) < 0 )
        err_sys( "connect error" );
}  /* Connect */


void
Getpeername (
    int             fd,
    struct sockaddr *sa,
    socklen_t       *salenptr )
{
    if ( getpeername( fd, sa, salenptr ) < 0 )
        err_sys( "getpeername error" );
}  /* Getpeername */


void
Getsockname (
    int             fd,
    struct sockaddr *sa,
    socklen_t       *salenptr )
{
    if ( getsockname( fd, sa, salenptr ) < 0 )
        err_sys( "getsockname error" );
}  /* Getsockname */


void
Listen (
    int fd,
    int backlog )
{
#if 0
    char *ptr;

        /*4can override 2nd argument with environment variable */
    if ( ( ptr = getenv( "LISTENQ" )) != NULL )
        backlog = atoi( ptr );
#endif

    if ( listen( fd, backlog ) < 0 )
        err_sys( "listen error" );
}  /* Listen */


ssize_t
Recv (
    int    fd,
    void   *ptr,
    size_t nbytes,
    int    flags )
{
    ssize_t n;

    if ( ( n = recv( fd, ptr, nbytes, flags )) < 0 )
        err_sys( "recv error" );
    return( n );
}  /* Recv */


ssize_t
Recvfrom (
    int             fd,
    void            *ptr,
    size_t          nbytes,
    int             flags,
    struct sockaddr *sa,
    socklen_t       *salenptr )
{
    ssize_t n;

    if ( ( n = recvfrom( fd, ptr, nbytes, flags, sa, salenptr )) < 0 ) {

#ifdef SH
        if ( -1 == n )
            n = 0;

#else
        err_sys( "recvfrom error" );
#endif
    }
    return( n );
}  /* Recvfrom */


#if 0
ssize_t
Recvmsg (
    int           fd,
    struct msghdr *msg,
    int           flags )
{
    ssize_t n;

    if ( ( n = recvmsg( fd, msg, flags )) < 0 )
        err_sys( "recvmsg error" );
    return( n );
}  /* Recvmsg */
#endif


#if !defined( __GNUC__ )  ||  defined( _SYS_SOCKET_H )
void
Getsockopt (
    int       fd,
    int       level,
    int       optname,
    void      *optval,
    socklen_t *optlenptr )
{
    if ( getsockopt( fd, level, optname, optval, optlenptr ) < 0 )
        err_sys( "getsockopt error" );
}  /* Getsockopt */


int
Select (
    int            nfds,
    fd_set         *readfds,
    fd_set         *writefds,
    fd_set         *exceptfds,
    struct timeval *timeout )
{
    int n;

    if ( ( n = select( nfds, readfds, writefds, exceptfds, timeout )) < 0 )
        err_sys( "select error" );

    /* can return 0 on timeout */
    return( n );
}  /* Select */


void
Setsockopt (
    int        fd,
    int        level,
    int        optname,
    const void *optval,
    socklen_t  optlen )
{
    if ( setsockopt( fd, level, optname, optval, optlen ) < 0 )
        err_sys( "setsockopt error" );
}  /* Setsockopt */
#endif


void
Send (
    int        fd,
    const void *ptr,
    size_t     nbytes,
    int        flags )
{
    if ( send( fd, ptr, nbytes, flags ) != ( ssize_t ) nbytes )
        err_sys( "send error" );
}  /* Send */


void
Sendto (
    int             fd,
    void            *ptr,
    size_t          nbytes,
    int             flags,
    struct sockaddr *sa,
    socklen_t       salen )
{
    if ( sendto( fd, ptr, nbytes, flags, sa, salen ) != ( ssize_t ) nbytes )
        err_sys( "sendto error" );
}  /* Sendto */


#if 0
void
Sendmsg (
    int                 fd,
    const struct msghdr *msg,
    int                 flags )
{
    int     i;
    ssize_t nbytes;

    /* must first figure out what return value should be */
    nbytes = 0;
    for ( i = 0; i < msg->msg_iovlen; i++ )
        nbytes += msg->msg_iov[ i ].iov_len;

    if ( sendmsg( fd, msg, flags ) != nbytes )
        err_sys( "sendmsg error" );
}  /* Sendmsg */
#endif


void
Shutdown (
    int fd,
    int how )
{
    if ( shutdown( fd, how ) < 0 )
        err_sys( "shutdown error" );
}  /* Shutdown */


#if 0
int
Sockatmark (
    int fd )
{
    int n;

    if ( ( n = sockatmark( fd )) < 0 )
        err_sys( "sockatmark error" );
    return( n );
}  /* Sockatmark */
#endif


int
Socket (
    int family,
    int type,
    int protocol )
{
    int n;

    if ( ( n = socket( family, type, protocol )) < 0 )
        err_sys( "socket error" );
    return( n );
}  /* Socket */


#if 0
void
Socketpair (
    int family,
    int type,
    int protocol,
    int *fd )
{
    int n;

    if ( ( n = socketpair( family, type, protocol, fd )) < 0 )
        err_sys( "socketpair error" );
}  /* Socketpair */
#endif


void
tvsub (
    struct timeval *tdiff,
    struct timeval *t1,
    struct timeval *t0 )
{

    tdiff->tv_sec = t1->tv_sec - t0->tv_sec;
    tdiff->tv_usec = t1->tv_usec - t0->tv_usec;
    if ( tdiff->tv_usec < 0 )
        tdiff->tv_sec--, tdiff->tv_usec += 1000000;
}  /* tvsub */

