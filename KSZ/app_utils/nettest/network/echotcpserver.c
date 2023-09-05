
#ifdef _WIN32
#include <process.h>
#endif
#include "wnp.h"
#include "datatype.h"
#ifdef _SYS_SOCKET_H
#include <unistd.h>
#endif


void
str_echo (
    void* param )
{
    int*    sockfd = ( int* ) param;
    ssize_t n;
    char    line[ MAXBUFFER + 2 ];

    FOREVER {
        if ( ( n = Readline( *sockfd, line, MAXBUFFER )) <= 0 ) {

            /* connection closed by other end */
            break;
        }

        if ( line[ 0 ] == '\n' ) {
            break;
        }
        Writen( *sockfd, line, n );
    }
    closesocket( *sockfd );

#ifdef _WIN32
    _endthread();
#endif
}  /* str_echo */


void echo_server (
    int listenfd,
    int udpfd )
{
    struct sockaddr_in cliaddr;
    char               mesg[ MAXBUFFER + 2 ];
    int                nready;
    int                connfd;
    int                maxfdp1;
    fd_set             rset;
    ssize_t            n;
    socklen_t          len;

#ifndef _WIN32
    pid_t              pid;
#endif

    FD_ZERO( &rset );
    maxfdp1 = max( listenfd, udpfd ) + 1;
    FOREVER {
        FD_SET(( SOCKET ) listenfd, &rset );
        FD_SET(( SOCKET ) udpfd, &rset );
        if ( ( nready = select( maxfdp1, &rset, NULL, NULL, NULL )) < 0 ) {

#ifdef _WIN32
            if ( WSAGetLastError() == WSAEINTR )

                /* back to for() */
                continue;
            else
#endif
                err_sys( "select error" );
        }

        if ( FD_ISSET( listenfd, &rset )) {
            len = sizeof( cliaddr );
            connfd = Accept( listenfd, ( SA* ) &cliaddr, &len );

#ifdef _WIN32
            _beginthread( str_echo, 4096, &connfd );

#else
            if ( ( pid = fork()) == 0 ) {
                closesocket( listenfd );
                str_echo( &connfd );
                exit( 0 );
            }
            closesocket( connfd );
#endif
        }

        if ( FD_ISSET( udpfd, &rset ) ) {
            len = sizeof( cliaddr );
            n = Recvfrom( udpfd, mesg, MAXBUFFER, 0, ( SA* ) &cliaddr, &len );

            Sendto( udpfd, mesg, n, 0, ( SA* ) &cliaddr, len );
        }
    }
}  /* echo_server */


int main (
    int   argc,
    char* argv[] )
{
    struct sockaddr_in servaddr;
    int                listenfd;
    int                udpfd;
    int                port = IPPORT_ECHO;
    const int          on = 1;

    SocketInit( 1 );

    if ( argc > 1 )
    {
        int i;

        for ( i = 1; i < argc; i++ )
        {
            if ( '-' == argv[ i ][ 0 ]  ||  '/' == argv[ i ][ 0 ] )
            {
                switch ( argv[ i ][ 1 ] )
                {
                    case 'p':
                    case 'P':
                        port = 9877;
                        if ( '=' == argv[ i ][ 2 ] )
                        {
                            port = atoi( &argv[ i ][ 3 ]);
                        }
                        break;
                }
            }
        }
    }

    /* create listening TCP socket */
    listenfd = Socket( AF_INET, SOCK_STREAM, 0 );

    bzero( &servaddr, sizeof( servaddr ));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = htonl( INADDR_ANY );
    servaddr.sin_port        = htons(( short ) port );

    Setsockopt( listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof( on ));
    Bind( listenfd, ( SA* ) &servaddr, sizeof( servaddr ));

    Listen( listenfd, LISTENQ );

    /* create UDP socket */
    udpfd = Socket( AF_INET, SOCK_DGRAM, 0 );

    bzero( &servaddr, sizeof( servaddr ));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = htonl( INADDR_ANY );
    servaddr.sin_port        = htons(( short ) port );

    Bind( udpfd, ( SA* ) &servaddr, sizeof( servaddr ));

    printf( "echo server listening" );
    if ( port != IPPORT_ECHO )
    {
        printf( " in port %u", port );
    }
    printf( "...\n" );
    echo_server( listenfd, udpfd );
    closesocket( listenfd );
    closesocket( udpfd );
    SocketExit();
    return 0;
}
