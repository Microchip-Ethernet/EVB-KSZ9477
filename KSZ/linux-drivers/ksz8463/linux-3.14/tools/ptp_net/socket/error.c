/* -----------------------------------------------------------------------------

    Modified from W. Richard Stevens's UNIX Network Programming to run under
    Windows
----------------------------------------------------------------------------- */


#include <stdarg.h>
#include <stdio.h>

#ifdef __BORLANDC__
#include <windows.h>

#elif defined( _MSC_VER )
#include <winsock2.h>

#pragma message( "support snprintf" )
#define HAVE_SNPRINTF
#define HAVE_VSNPRINTF

#elif defined( __GNUC__ )
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#endif


#define MAXLINE  512


enum {
    LOG_ERR,
    LOG_INFO
};


static FILE* logfp = NULL;
static int   daemon_proc = 0;

void
SocketExit ( void )
{

#ifndef __GNUC__
    WSACleanup();
#endif
    if ( logfp ) {
        fclose( logfp );
        logfp = NULL;
    }
}  /* SocketExit */


void
SocketInit (
    int daemon )
{

#ifndef __GNUC__
    WSADATA wsaData;
#endif

    if ( daemon ) {
        daemon_proc = 1;
        logfp = fopen( "winsock.log", "wt" );
    }

#ifdef __GNUC__
#ifndef _SYS_SOCKET_H
    sockinit();
#endif

#else
    if ( WSAStartup( 0x101, &wsaData ) ) {
        fprintf( stderr, "Could not initialize WinSock\n" );
        if ( logfp ) {
            fprintf( logfp, "Could not initialize WinSock\n" );
            fclose( logfp );
            logfp = NULL;
        }
        exit( 1 );
    }
    if ( 0x101 != wsaData.wVersion ) {
        fprintf( stderr, "Version %x not supported\n", wsaData.wVersion );
        if ( logfp ) {
            fprintf( logfp, "Version %x not supported\n", wsaData.wVersion );
            fclose( logfp );
            logfp = NULL;
        }
        exit( 1 );
    }
#endif
}  /* SocketInit */

/* -------------------------------------------------------------------------- */

static const char *
err_string (
    int errorno )
{

#ifndef __GNUC__
    static char* error_table[] = {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        "Invalid",
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        "Not socket",
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        "Addres in use",
        "Address not available",
        NULL,
        NULL,
        "Network reset",
        "Connection aborted",
        "Connection reset",
        NULL,
        "Is connected",
        "Is not connected",
        NULL,
        NULL,
        "Connection timed out",
        "Connection refused",
        NULL,
        NULL,
        NULL,
        "No route to host",
        NULL
    };

    if ( errorno >= WSABASEERR ) {
        errorno -= WSABASEERR;
        if ( errorno < sizeof( error_table ) / sizeof( char* ) ) {
            if ( error_table[ errorno ] != NULL ) {
                return( error_table[ errorno ]);
            }
        }
        errorno += WSABASEERR;
        switch ( errorno ) {
            case WSASYSNOTREADY:
                return( "System not ready" );
            case WSAVERNOTSUPPORTED:
                return( "Version not supported" );
            case WSANOTINITIALISED:
                return( "Not initialized" );
            case WSAHOST_NOT_FOUND:
                return( "Host not found" );
            case WSATRY_AGAIN:
                return( "Try again" );
            case WSANO_DATA:
                return( "No data" );
        }
        return( NULL );
    }
#endif

#ifdef _SYS_SOCKET_H
    return(( const char* ) strerror( errorno ));

#else
    return( NULL );
#endif
}  /* err_string */


/* Print a message and return to caller.
 * Caller specifies "errnoflag" and "level". */

static void
err_doit (
    int        errnoflag,
    int        level,
    const char *fmt,
    va_list    ap )
{
    int  errno_save;
    int  n;
    char buf[ MAXLINE ];
    const char *errstr;

#ifndef __GNUC__
    /* value caller might want printed */
    errno_save = WSAGetLastError();

#else
    errno_save = errno;
#endif

#ifdef HAVE_VSNPRINTF
    /* this is safe */
    _vsnprintf( buf, sizeof( buf ), fmt, ap );

#else
    /* this is not safe */
#if 0
    vsprintf( buf, fmt, ap );
#else
    vsnprintf( buf, sizeof( buf ), fmt, ap );
#endif
#endif
    n = strlen( buf );
    if ( errnoflag ) {
        errstr = err_string( errno_save );
        if ( errstr ) {

#ifdef HAVE_SNPRINTF
            _snprintf( buf + n, sizeof( buf ) - n, ": %s", errstr );

#else
            sprintf( buf + n, ": %s", errstr );
#endif
        }
        else

#ifdef HAVE_SNPRINTF
            _snprintf( buf + n, sizeof( buf ) - n, ": %x", errno_save );

#else
            sprintf( buf + n, ": %x", errno_save );
#endif
    }
    strcat( buf, "\n" );

    if ( daemon_proc ) {
        if ( logfp ) {
            fprintf( logfp, buf );
            if ( LOG_ERR == level ) {
                fflush( logfp );
            }
        }
    }
    else {

        /* in case stdout and stderr are the same */
        fflush( stdout );
        fputs( buf, stderr );
        fflush( stderr );
    }
}  /* err_doit */


/* Fatal error related to a system call.
 * Print a message, dump core, and terminate. */

void
err_dump (
    const char *fmt, ... )
{
    va_list ap;

    va_start( ap, fmt );
    err_doit( 1, LOG_ERR, fmt, ap );
    va_end( ap );
    SocketExit();

    /* dump core and terminate */
    abort();

    /* shouldn't get here */
    exit( 1 );
}  /* err_dump */


/* Nonfatal error unrelated to a system call.
 * Print a message and return. */

void
err_msg (
    const char *fmt, ... )
{
    va_list ap;

    va_start( ap, fmt );
    err_doit( 0, LOG_INFO, fmt, ap );
    va_end( ap );
}  /* err_msg */


/* Fatal error unrelated to a system call.
 * Print a message and terminate. */

void
err_quit (
    const char *fmt, ... )
{
    va_list ap;

    va_start( ap, fmt );
    err_doit( 0, LOG_ERR, fmt, ap );
    va_end( ap );
    SocketExit();
    exit( 1 );
}  /* err_quit */


/* Nonfatal error related to a system call.
 * Print a message and return. */

void
err_ret (
    const char *fmt, ... )
{
    va_list ap;

    va_start( ap, fmt );
    err_doit( 1, LOG_INFO, fmt, ap );
    va_end( ap );
}  /* err_ret */


/* Fatal error related to a system call.
 * Print a message and terminate. */

void
err_sys (
    const char *fmt, ... )
{
    va_list ap;

    va_start( ap, fmt );
    err_doit( 1, LOG_ERR, fmt, ap );
    va_end( ap );
    SocketExit();
    exit( 1 );
}  /* err_sys */


int invalid_err(void)
{
#ifndef __GNUC__
	int errno_save;

	/* value caller might want printed */
	errno_save = WSAGetLastError();
	return errno_save == 11;
#else
	return errno == EINVAL;
#endif
}
