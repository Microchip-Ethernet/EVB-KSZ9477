#ifndef __DATATYPE_H
#define __DATATYPE_H

typedef char            INT8;
typedef unsigned char   UINT8;
typedef unsigned char   BYTE;
typedef unsigned char   UCHAR;
typedef short           INT16;

#ifndef SHORT
typedef short           SHORT;
#endif
typedef unsigned short  UINT16;
typedef unsigned short  USHORT;
typedef unsigned short  WORD;
typedef unsigned long   DWORD;
typedef unsigned long   ULONG;
typedef unsigned int    UINT;

#ifndef __OS2DEF__
typedef int             BOOL;
#endif
typedef unsigned char   BOOLEAN;

#ifndef min
#define min( a, b )  ((( a ) < ( b )) ? ( a ) : ( b ))
#endif

#ifndef max
#define max( a, b )  ((( a ) > ( b )) ? ( a ) : ( b ))
#endif

#ifndef FAR

#ifdef _WIN32
#define FAR

#else
#define FAR far
#endif
#endif


#define FALSE  0
#define TRUE   1

#ifndef NULL
#define NULL  (( void* ) 0 )
#endif

#ifndef LOBYTE
#define LOBYTE(w)           ((BYTE)(w))
#endif
#ifndef HIBYTE
#define HIBYTE(w)           ((BYTE)((WORD)(w) >> 8))
#endif

#ifndef LOWORD
#define LOWORD(l)           ((WORD)(l))
#endif
#ifndef HIWORD
#define HIWORD(l)           ((WORD)((DWORD)(l) >> 16))
#endif

#ifndef MAKEWORD
#define MAKEWORD(low, high) ((WORD)(((BYTE)(low)) | (((WORD)((BYTE)(high))) << 8)))
#endif

#define null()

#define FOREVER  for (;;)

#endif
