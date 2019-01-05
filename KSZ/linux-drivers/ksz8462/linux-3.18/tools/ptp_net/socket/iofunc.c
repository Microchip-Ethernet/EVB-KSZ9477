#include "wnp.h"


static ssize_t
my_read (
    SOCKET fd,
    char   *ptr )
{
    static int  read_cnt = 0;
    static char *read_ptr;
    static char read_buf[ MAXBUFFER ];

    if ( read_cnt <= 0 ) {

#ifndef __GNUC__
again:
#endif
        if ( ( read_cnt = recv( fd, read_buf, sizeof( read_buf ), 0 )) < 0 ) {

#ifndef __GNUC__
            if ( WSAGetLastError() == WSAEINTR )
                goto again;
#endif
            return( -1 );
        }
        else if ( read_cnt == 0 ) {
            return( 0 );
        }
        read_ptr = read_buf;
    }

    read_cnt--;
    *ptr = *read_ptr++;
    return( 1 );
}  /* my_read */


ssize_t
readline (
    SOCKET fd,
    void   *vptr,
    size_t maxlen )
{
    size_t n;
    int    rc;
    char   c;
    char   *ptr;

    ptr = vptr;
    for ( n = 1; n < maxlen; n++ ) {
        if ( ( rc = my_read( fd, &c )) == 1 ) {
            *ptr++ = c;
            if ( c == '\n' )

                /* newline is stored, like fgets() */
                break;
        }
        else if ( rc == 0 ) {
            if ( n == 1 )

                /* EOF, no data read */
                return( 0 );
            else

                /* EOF, some data was read */
                break;
        }
        else

            /* error, errno set by read() */
            return( -1 );
    }

    /* null terminate like fgets() */
    *ptr = 0;
    return( n );
}  /* readline */


ssize_t
Readline (
    SOCKET fd,
    void   *ptr,
    size_t maxlen )
{
    ssize_t n;

    if ( ( n = readline( fd, ptr, maxlen )) < 0 )
        err_ret( "readline error" );
    return( n );
}  /* Readline */


ssize_t
readn (
    SOCKET fd,
    void   *vptr,
    size_t maxlen )
{
    size_t n;
    int    rc;
    char   c;
    char   *ptr;

    ptr = vptr;
    for ( n = 0; n < maxlen; n++ ) {
        if ( ( rc = my_read( fd, &c )) == 1 ) {
            *ptr++ = c;
        }
        else if ( rc == 0 ) {
            if ( n == 0 )

                /* EOF, no data read */
                return( 0 );
            else

                /* EOF, some data was read */
                break;
        }
        else

            /* error, errno set by read() */
            return( -1 );
    }
    return( n );
}  /* readn */


ssize_t
Readn (
    SOCKET fd,
    void   *ptr,
    size_t maxlen )
{
    ssize_t n;

    if ( ( n = readn( fd, ptr, maxlen )) < 0 )
        err_ret( "readn error" );
    return( n );
}  /* Readn */

/* -------------------------------------------------------------------------- */

/* Write "n" bytes to a descriptor. */
ssize_t
writen (
    SOCKET     fd,
    const void *vptr,
    size_t     n )
{
    size_t     nleft;
    ssize_t    nwritten;
    const char *ptr;

    ptr = vptr;
    nleft = n;
    while ( nleft > 0 ) {
        if ( ( nwritten = send( fd, ptr, nleft, 0 )) <= 0 ) {

#ifndef __GNUC__
            if ( WSAGetLastError() == WSAEINTR )

                /* and call send() again */
                nwritten = 0;
            else
#endif

                /* error */
                return( -1 );
        }

        nleft -= nwritten;
        ptr   += nwritten;
    }
    return( n );
}  /* writen */


void
Writen (
    SOCKET fd,
    void   *ptr,
    size_t nbytes )
{
    if ( writen( fd, ptr, nbytes ) != ( ssize_t ) nbytes )
        err_ret( "writen error" );
}  /* Writen */
