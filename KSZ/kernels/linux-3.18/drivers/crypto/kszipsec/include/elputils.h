/*-----------------------------------------------------------------------
//
// Proprietary Information of Elliptic Semiconductor
// Copyright (C) 2002-2005, all rights reserved
// Elliptic Semiconductor, Inc.
//
// As part of our confidentiality  agreement, Elliptic Semiconductor and
// the Company, as  a  Receiving Party, of  this  information  agrees to
// keep strictly  confidential  all Proprietary Information  so received
// from Elliptic Semiconductor. Such Proprietary Information can be used
// solely for  the  purpose  of evaluating  and/or conducting a proposed
// business  relationship  or  transaction  between  the  parties.  Each
// Party  agrees  that  any  and  all  Proprietary  Information  is  and
// shall remain confidential and the property of Elliptic Semiconductor.
// The  Company  may  not  use  any of  the  Proprietary  Information of
// Elliptic Semiconductor for any purpose other  than  the  above-stated
// purpose  without the prior written consent of Elliptic Semiconductor.
//
//-----------------------------------------------------------------------
//
// Project:
//
//   ELP - TOE
//
// Description:
//
//
// This file maps defines a system abstraction layer for some generic
// functions and data structures
//
//
//-----------------------------------------------------------------------
//
// Copyright (C) 2006-2007, Micrel, Inc.
//
//-----------------------------------------------------------------------*/


#ifndef _ELPUTILS_H_
#define _ELPUTILS_H_

#include "elptypes.h"

#ifndef htons
#define htons(x) \
({ \
	U16 __x = (x); \
	((U16)( \
		(((U16)(__x) & (U16)0x00ffU) << 8) | \
		(((U16)(__x) & (U16)0xff00U) >> 8) )); \
})

#define ntohs(x) htons(x)
#endif
#ifndef htonl

#define htonl(x) \
({ \
	U32 __x = (x); \
	((U32)( \
		(((U32)(__x) & (U32)0x000000ffUL) << 24) | \
		(((U32)(__x) & (U32)0x0000ff00UL) <<  8) | \
		(((U32)(__x) & (U32)0x00ff0000UL) >>  8) | \
		(((U32)(__x) & (U32)0xff000000UL) >> 24) )); \
})
#define ntohl(x) htonl(x)
#endif
#define htonl_e(x) \
({ \
	U32 __x = (x); \
	((U32)( \
		(((U32)(__x) & (U32)0x0000ffffUL) << 16) | \
		(((U32)(__x) & (U32)0xffff0000UL) >> 16) )); \
})

void	dumpword_ex(U32 *mem, int size, char *msg,int col,int bige);
void	dumpword(U32 *from, int size, char *msg,int bige);
void	dumpmem(char *mem, int size, char *msg,U32 bige);
void	memcpy32htonl(U32 *dst, U32 *src, int len);
void	memcpy32(volatile U32 *dst, volatile U32 *src, int len);
void	memcpy32htonl_r(U32 *dst, U32 *src, int len);
void	memcpy32_e(U32 *dst, U32 *src, int len);
void	memcpy32_re(U32 *dst, U32 *src, int len);
void	memcpy32_r(U32 *dst, U32 *src, int len);
void	memset32(U32 *dst, U32 val, int len);
int	wcopy(U32 *src, U32 *dst, U32 size);
int	wcopyton(U32 *src, U32 *dst, U32 size);
int	wcmp(U32 *src, U32 *dst, U32 size);
int	bytecmp(U8 *src, U8 *dst, U32 size);

#if defined (ELPSEC_LINUX)
void	dumpstruct(FILE *out, char *mem, int size, char *sname,char *msg);
#endif

#define DUMPWORD(m,t,z,f)	dumpword((U32 *)(m),(t),(z),(f))
#define DUMPWORD_(m,t,z,f)
#define MEMCPY(d,s,z)		memcpy((d),(s),(z))
#define MEMCPY32(d,s,z)		memcpy32((U32 *)(d),(U32 *)(s),(z))
#define MEMCPY32_E(d,s,z)	memcpy32_e((U32 *)(d),(U32 *)(s),(z))
#define MEMCPY32_R(d,s,z)	memcpy32_r((U32 *)(d),(U32 *)(s),(z))
#define MEMCPY32HTONL(d,s,z)	memcpy32htonl((U32 *)(d),(U32 *)(s),(z))
#define MEMCPY32HTONL_R(d,s,z)	memcpy32htonl_r((U32 *)(d),(U32 *)(s),(z))
#define MEMCPY32_RE(d,s,z)	memcpy32_re((U32 *)(d),(U32 *)(s),(z))
#define MEMSET32(d,v,z)		memset32((U32 *)(d),(v),(z))
#define MEMSET(d,v,z)		memset((d),(v),(z))

#define BTOW(i)			((((i)?(i):-3)-1)/4+1)

#ifdef DO_PERF
#include "elpperf.h"
#else
#define ELP_PERF_DECLARE(x)
#define ELP_PERF_CPU(x)
#define ELP_PERF_START(x)
#define ELP_PERF_STOP(x)
#define ELP_PERF_REPORT(x,m)
#define ELP_PERF_REPORT_MORE(x,m)
#endif

#define SIZE_QUANT   64
void	minit(void *buffer, long len);
void	*mget(long size);
void	mfree(void *buf);

#endif
