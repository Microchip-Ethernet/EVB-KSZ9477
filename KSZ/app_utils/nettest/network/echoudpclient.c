#include "wnp.h"
#include "datatype.h"
#ifdef _SYS_SOCKET_H
#include <arpa/inet.h>
#include <unistd.h>
#endif


void
dg_cli (
    FILE      *fp,
    int       sockfd,
    SAI       *pservaddr,
    socklen_t servlen )
{
    int                maxfdp1;
    int                n;
    char               sendline[ MAXLINE ];
    char               recvline[ MAXBUFFER + 2 ];
    char               reply_addr[ sizeof( struct sockaddr_in6 )];
    struct sockaddr_in *preply_addr = ( struct sockaddr_in* ) reply_addr;
    struct sockaddr_in6 *preply_addr6 = ( struct sockaddr_in6* ) reply_addr;
    socklen_t          len;
    fd_set             rset;
    struct timeval     timer;
    int                sin_zero = 1;

#ifdef _SYS_SOCKET_H
    printf( "Type Ctrl-D to exit.\n" );

#else
    printf( "Type Ctrl-Z to exit.\n" );
#endif
    bzero( reply_addr, sizeof( reply_addr ));
    FD_ZERO( &rset );

    while ( Fgets( sendline, MAXLINE, fp ) != NULL ) {
        Sendto( sockfd, sendline, strlen( sendline ), 0, ( SA* ) pservaddr,
            servlen );

        FD_SET(( SOCKET ) sockfd, &rset );
        timerclear( &timer );
        timer.tv_sec = 0;
        timer.tv_usec = 200000;
        maxfdp1 = sockfd + 1;

        Select( maxfdp1, &rset, NULL, NULL, &timer );

        // socket is not readable
        if ( !FD_ISSET( sockfd, &rset ) ) {
            continue;
        }

        len = servlen;
        n = Recvfrom( sockfd, recvline, MAXBUFFER, 0, ( SA* ) reply_addr,
            &len );

#if 1
        if ( AF_INET == preply_addr->sin_family ) {
            if ( !sin_zero ) {
                memset( preply_addr->sin_zero, 0, 8 );
            }
            else if ( 1 == sin_zero ) {
                if ( preply_addr->sin_zero[ 0 ] ) {
                    sin_zero = 0;
                    printf( "not zero!\n" );
                }
                else
                    sin_zero = 2;
            }
        }
#endif
        if ( len != servlen  ||  memcmp( pservaddr, reply_addr, len ) != 0 ) {
            if ( AF_INET6 == preply_addr->sin_family )
                Inet_ntop( preply_addr6->sin6_family,
                    &preply_addr6->sin6_addr, recvline,
                    sizeof( recvline ));
            else
                Inet_ntop( preply_addr->sin_family,
                    &preply_addr->sin_addr, recvline,
                    sizeof( recvline ));
            printf( "reply from %s (ignored)\n", recvline );
            continue;
        }

        /* null terminate */
        recvline[ n ] = 0;
        Fputs( recvline, stdout );
    }
}  /* dg_cli */


int main (
    int   argc,
    char* argv[] )
{
    struct sockaddr_in servaddr;
    struct sockaddr_in6 servaddr6;
    SOCKET             sockfd;
    char               recvline[ MAXLINE ];
    struct in_addr     **pptr = NULL;
    struct hostent     *hp = NULL;
    struct servent     *sp = NULL;
    int                family = AF_INET;
    int                got_addr = 0;
    int                port = IPPORT_ECHO;

    SocketInit( 0 );

    if ( argc < 2 ) {
        err_quit( "usage: %s <hostname> [-d]\n", argv[ 0 ]);
    }

    if ( argc > 1 )
    {
        int i;

        for ( i = 1; i < argc; i++ )
        {
            if ( '-' == argv[ i ][ 0 ]  ||  '/' == argv[ i ][ 0 ] )
            {
                switch ( argv[ i ][ 1 ] )
                {
                    case 'D':
                    case 'd':
                        if ( IPPORT_ECHO == port )
                            port = IPPORT_DISCARD;
                        break;
                    case 'p':
                    case 'P':
                        port = 9877;
                        if ( '=' == argv[ i ][ 2 ] )
                        {
                            port = atoi( &argv[ i ][ 3 ]);
                        }
                        break;
                    case 'H':
                    case 'h':
                        printf( "\t-d use discard port\n" );
                        printf( "\t-p port number\n" );
                        err_quit( "" );
                        break;
                }
            }
            else if ( !got_addr ) 
            {
                bzero( &servaddr, sizeof( servaddr ));
                bzero( &servaddr6, sizeof( servaddr6 ));
                if ( inet_pton( AF_INET, argv[ i ], &servaddr.sin_addr ) > 0 )
                {
                }
                else if ( inet_pton( AF_INET6, argv[ i ],
                        &servaddr6.sin6_addr ) > 0 )
                {
                    family = AF_INET6;
                }
                else if ( ( hp = gethostbyname( argv[ i ])) == NULL )
                    err_sys( "hostname error for %s", argv[ i ]);
                got_addr = 1;
            }
            else if ( !sp )
            {
                if ( ( sp = getservbyname( argv[ i ], "udp" )) == NULL )
                    err_quit( "getservbyname error for %s", argv[ i ]);
            }
        }
    }

    if ( hp ) {
        pptr = ( struct in_addr ** ) hp->h_addr_list;
        if ( *pptr == NULL )
            err_quit( "unable to connect" );
    }

    sockfd = Socket( family, SOCK_DGRAM, 0 );

    if ( AF_INET6 == family )
    {
        servaddr6.sin6_family = AF_INET6;
        if ( sp )
        {
            servaddr6.sin6_port = sp->s_port;
        }
        else
            servaddr6.sin6_port = htons(( short ) port );
        if ( pptr )
            memcpy( &servaddr6.sin6_addr, *pptr, sizeof( struct in_addr ));
        servaddr6.sin6_scope_id = 2;
        printf( "trying %s\n",
            Inet_ntop( servaddr6.sin6_family, &servaddr6.sin6_addr, recvline,
                sizeof( recvline )));
    }
    else
    {
        servaddr.sin_family = AF_INET;
        if ( sp )
        {
            servaddr.sin_port = sp->s_port;
        }
        else
            servaddr.sin_port = htons(( short ) port );
        if ( pptr )
            memcpy( &servaddr.sin_addr, *pptr, sizeof( struct in_addr ));
        printf( "trying %s\n",
            Inet_ntop( servaddr.sin_family, &servaddr.sin_addr, recvline,
                sizeof( recvline )));
    }

    if ( AF_INET6 == family )
        dg_cli( stdin, sockfd, ( SAI* ) &servaddr6, sizeof( servaddr6 ));
    else
        dg_cli( stdin, sockfd, &servaddr, sizeof( servaddr ));
    closesocket( sockfd );
    SocketExit();
    return 0;
}
