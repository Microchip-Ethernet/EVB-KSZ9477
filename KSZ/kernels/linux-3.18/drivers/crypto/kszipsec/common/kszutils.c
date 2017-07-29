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
//   ELPSEC
//
// Description:
//
//
//
//-----------------------------------------------------------------------
//
// Copyright (C) 2006-2007, Micrel, Inc.
//
//-----------------------------------------------------------------------*/

#if defined( ELPSEC_LINUX ) || defined( DEF_LINUX )
#include <elputils.h>
#endif


void dumpword(U32 *from, int size, char *msg,int bige)
{
	U32 off = 0;
	unsigned long  wlen = ((size)>>2);
	if (size%4)
		wlen++;
	EPRINTF("%s: (%ld) %d bytes @ %p\n",msg?msg:" ",wlen,size,from);
	while (wlen--)
	{
		if (bige)
			EPRINTF("0x%02lX: %08lX\n",off,*from);
			//EPRINTF("%08X\n",htonl(*from));
		else
			EPRINTF("0x%02lX: %08lX\n",off,*from);
		from++;
		off += 4;
	}
}

void dumpword_ex(U32 *mem, int size, char *msg,int col,int bige)
{
	int d,len;
	char dmp[400];
	char *ptmp = dmp;
	U32 val;
	if (!mem)
	return;
	EPRINTF("%s",msg?msg:" ");
	*ptmp = '\0';
	for (d=0;d<size;d++)
	{
		if (d> col && (d%col)==0)
		{
			ptmp = dmp;
			EPRINTF("%s\n",ptmp);
		}
		if (bige)
			val = htonl(mem[d]);
		else
			val = mem[d];

		len = ESPRINTF(ptmp,"%08lx ",val); ptmp+=len;
	}
	if (ptmp != dmp)
	{
		ptmp = dmp;
		EPRINTF("%s\n",ptmp);
	}
}

void dumpmem(char *mem, int size, char *msg,U32 bige)
{
	int d,len;
	char dmp[400];
	char *ptmp = dmp;

	if (!mem)
		return;
	EPRINTF("%s: %d bytes\n",msg?msg:" ",size);
	*ptmp = '\0';
	for (d=0;d<size;d++)
	{
		if (d> 15 && (d%16)==0)
		{
			ptmp = dmp;
			EPRINTF("%s\n",ptmp);
		}
		len = ESPRINTF(ptmp,"%2.2x ",mem[d]&0xFF); ptmp+=len;
	}
	if (ptmp != dmp)
	{
		ptmp = dmp;
		EPRINTF("%s\n",ptmp);
	}
}


int ememcmp (
	void* src,
	void* dst,
	int   len )
{
	unsigned char* psrc = ( unsigned char* ) src;
	unsigned char* pdst = ( unsigned char* ) dst;
	int            ret = 0;

	while ( len-- ) {
		ret = *pdst++ - *psrc++;
		if ( ret )
			break;
	}
	return( ret );
}  /* ememcmp */


/* elputils.c */
void memcpy32(volatile U32 *dst, volatile U32 *src, int len)
{
	int i;
	for (i = len - 1; i >= 0; i--) {
		dst[i] = src[i];
	}
}

void memcpy32htonl(U32 *dst, U32 *src, int len)
{
	register int i = len;
	while(i)
	{
		i--;
		dst[i]=htonl(src[i]);
	}
}


#ifndef ELPSEC_LINUX
void *ememset(void *src, int c, int size)
{
	char *psrc = (char *)src;

	if (!src)
		return 0;

	while(size--)
	{
		*psrc=(char)c; psrc++;
	}
	return src;
}

void *ememcpy(void *src, void *dst, int size)
{
	char *pdst = (char *)dst;
	char *psrc = (char *)src;

	if (!src || ! dst)
		return 0;

	while(size--)
	{
		*pdst=(*psrc); pdst++; psrc++;
	}
	return dst;
}

void *ememmove(void *src, const void *dst, int size)
{
	if (size != 0)
	{
		char *src1 = src;
		const char *dst1 = dst;

		if (src1 <= dst1)
		{
			do
			{
				*src1++ = *dst1++;
			} while (--size != 0);
		}
		else
		{
			dst1 += size;
			src1 += size;
			do
			{
				*--src1 = *--dst1;
			} while (--size != 0);
		}
	}
	return (src);
}
#endif


int wcopyton(U32 *src, U32 *dst, U32 size)
{
	while(size--)
	{
		*dst=htonl(*src);
		dst++;
		src++;
	}
	return size;
}
