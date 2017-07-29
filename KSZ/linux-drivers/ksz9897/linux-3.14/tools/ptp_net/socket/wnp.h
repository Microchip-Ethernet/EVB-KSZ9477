#ifndef _WNP_H
#define _WNP_H


#ifdef __BORLANDC__
#include <windows.h>

#elif defined( _MSC_VER )
#include <winsock2.h>

#pragma message( "support snprintf" )
#define HAVE_SNPRINTF
#define HAVE_VSNPRINTF

#elif defined( __GNUC__ )
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>


typedef int SOCKET;

#endif


#define SA  struct sockaddr
#define SAI struct sockaddr_in

#ifndef _STDINT_H
typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long  uint32_t;
#endif

#ifndef _SYS_SOCKET_H
typedef char           int8_t;
typedef short          int16_t;
typedef long           int32_t;

typedef int            socklen_t;
typedef int            ssize_t;
#endif

#ifdef _SYS_SOCKET_H
#define closesocket  close
#endif


#include "error.h"
#include "inetfunc.h"
#include "iofunc.h"
#include "wrapmcast.h"
#include "wrapsock.h"
#include "wrapstdio.h"

/* Following could be derived from SOMAXCONN in <sys/socket.h>, but many
   kernels still #define it as 5, while actually supporting many more */
#define LISTENQ         1024    /* 2nd argument to listen() */

/* Miscellaneous constants */
#define MAXBUFFER       65530
#define MAXLINE         4096    /* max text line length */

#define bzero( ptr, n )  memset( ptr, 0, n )

#ifndef SHUT_RD
enum {
    SHUT_RD,
    SHUT_WR,
    SHUT_RDWR
};
#endif

#ifndef INET6_ADDRSTRLEN
#define INET6_ADDRSTRLEN  46
#endif

#ifdef _SYS_SOCKET_H
#define DelayMillisec( milli )  usleep(( milli ) * 1000 )

#else
#define DelayMillisec( milli )  Sleep( milli )
#endif

#endif
