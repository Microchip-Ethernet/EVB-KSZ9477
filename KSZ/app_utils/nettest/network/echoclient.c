#include "wnp.h"
#include "datatype.h"
#ifdef _SYS_SOCKET_H
#include <unistd.h>
#endif


void
str_cli (
    FILE   *fp,
    SOCKET sockfd )
{
    int            maxfdp1;
    int            stdineof;
    fd_set         rset;
    struct timeval timer;
    char           sendline[ MAXLINE ];
    char           recvline[ MAXBUFFER + 2 ];

#ifdef _SYS_SOCKET_H
    printf( "Type Ctrl-D or '.' to exit.\n" );

#else
    printf( "Type Ctrl-Z or '.' to exit.\n" );
#endif
    stdineof = FALSE;
    FD_ZERO( &rset );
    FOREVER {
        FD_SET( sockfd, &rset );
        timerclear( &timer );
        timer.tv_sec = 1;
        maxfdp1 = sockfd + 1;

        if ( !stdineof ) {
            if ( Fgets( sendline, MAXLINE, fp ) == NULL  ||
                    sendline[ 0 ] == '.' ) {
                stdineof = TRUE;

                // send FIN
                Shutdown( sockfd, SHUT_WR );
                continue;
            }
            Writen( sockfd, sendline, strlen( sendline ));
        }

        Select( maxfdp1, &rset, NULL, NULL, &timer );

        // socket is readable
        if ( FD_ISSET( sockfd, &rset ) ) {
            if ( Readline( sockfd, recvline, MAXBUFFER ) <= 0 ) {
                if ( stdineof )

                    // normal termination
                    return;
                else
                    err_quit( "str_cli: server terminated prematurely" );
            }
            Fputs( recvline, stdout );
        }
    }

#if 0
    while ( Fgets( sendline, MAXLINE, fp ) != NULL ) {
        if ( sendline[ 0 ] == '.' )
            break;
        Writen( sockfd, sendline, strlen( sendline ));
        FD_SET( sockfd, &rset );
        timerclear( &timer );
        timer.tv_usec = 100;
        maxfdp1 = sockfd + 1;
        Select( maxfdp1, &rset, NULL, NULL, &timer );

        // socket is readable
        if ( FD_ISSET( sockfd, &rset ) ) {
            if ( Readline( sockfd, recvline, MAXBUFFER ) <= 0 )
                err_quit( "str_cli: server terminated prematurely" );
            Fputs( recvline, stdout );
        }
	}
#endif
}  /* str_cli */


int main (
    int   argc,
    char* argv[] )
{
    struct sockaddr_in servaddr;
    SOCKET             sockfd;
    int                port = IPPORT_ECHO;

    if ( argc < 2 ) {
        printf( "usage: %s <IP address>\n", argv[ 0 ]);
        return( 1 );
    }
    if ( argc > 2 )
    {
        int i;

        for ( i = 2; i < argc; i++ )
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

    SocketInit( 0 );

    sockfd = Socket( AF_INET, SOCK_STREAM, 0 );

    bzero( &servaddr, sizeof( servaddr ));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(( short ) port );

    Inet_pton( AF_INET, argv[ 1 ], &servaddr.sin_addr );
    Connect( sockfd, ( SA* ) &servaddr, sizeof( servaddr ));
    str_cli( stdin, sockfd );
    closesocket( sockfd );
    SocketExit();
    return 0;
}
