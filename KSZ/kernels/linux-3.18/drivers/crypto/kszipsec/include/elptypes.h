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


#ifndef _ELPTYPES_H_
#define _ELPTYPES_H_

#define ELP_COOKIE		0xE117BACE

// This is USER SPACE ONLY implementattion
#if defined (ELPSEC_LINUX)
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// fetch LINUX user space mutex definitions
#include <pthread.h>
typedef pthread_mutex_t elp_mutex;
#define elp_mutex_init(m)	pthread_mutex_init(&m,0)
#define elp_mutex_delete(m)	(pthread_mutex_destroy(&m))
#define elp_mutex_lock(m)	(pthread_mutex_lock(&m))
#define elp_mutex_unlock(m)	(pthread_mutex_unlock(&m))


#if defined (ELPSEC_PCI)
#include <sys/ioctl.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/io.h>
#include <sys/mman.h>
#include <pci/pci.h>
#endif

#define EPRINTF		printf
#define ESPRINTF	sprintf
#define EMEMSET		memset
#define EMEMCPY		memcpy
#define EMEMMOVE	memmove
#else

typedef int elp_mutex;
#define elp_mutex_init(m)
#define elp_mutex_delete(m)
#define elp_mutex_lock(m)
#define elp_mutex_unlock(m)


#define EPRINTF(...)
#define ESPRINTF(...) 0

// Prototypes for the OSless library
void *ememcpy (void *src, void *dst, int size);
void *ememset (void *src, int c, int size);
void *ememmove (void *src, const void *dst, int size);

#define EMEMSET(s,v,z) ememset(s,v,z)
#define EMEMCPY(d,s,z) ememcpy(s,d,z)
#define EMEMMOVE(d,s,z) ememmove(d,s,z)

#ifndef NULL
  #define NULL ((void*)0)
#endif
#endif


#undef MAX
#undef MIN
#define MAX(x, y) ( ((x)>(y))?(x):(y) )
#define MIN(x, y) ( ((x)<(y))?(x):(y) )
extern unsigned int _pd_verbose;

#define EDINIT		0x0001 // Initialization
#define EDRSA		0x0002
#define EDAES		0x0004
#define EDDES		0x0008
#define EDHASH		0x0010
#define EDPRNG		0x0020
#define EDCTX		0x0040
#define EDUTIL		0x0080
#define EDIPSEC		0x0100
#define EDRC4		0x0200
#define EDDUMP		0x1000


#define PDEBUG_ID   "<0: ecrypto> "
#define PINFO_ID    "<1: ecrypto> "
#define PERROR_ID   "<2: ecrypto> "
#define EASSERT(a) if(!(a)) {EPRINTF("Assertion: line %d in %s\n", __LINE__, __FILE__); }

#ifdef CRYPTO_NO_DEBUG
#define PDEBUG(type, format, args...)
#define PERROR(format, args...)
#define PINFO(format, args...)
#define PDUMPMEM(l,b,s,m)
#define PDUMPWORD(l,b,s,m,e)
#else
#define PDPROC(type,f)	{if ((type &_pd_verbose)==type ) (f);}
#define PDEBUG(type, format, args...)   {if ((type&_pd_verbose)==type) EPRINTF(PDEBUG_ID format, ##args );}
#define PERROR(format, args...)	EPRINTF(PERROR_ID format, ##args )
#define PINFO(format, args...)	EPRINTF(PINFO_ID format, ##args )
#define PDUMPMEM(l,b,s,m) do { if((l&_pd_verbose)==l){ dumpmem(b,s,m,0); } } while(0)
#define PDUMPWORD(l,b,s,m,e) do { if((l&_pd_verbose)==l){ DUMPWORD(b,s,m,e); } } while(0)
#endif

typedef unsigned char  U8;      /* unsigned 8-bit  integer */
typedef unsigned short U16;     /* unsigned 16-bit integer */

#ifdef __x86_64__
typedef unsigned U32;
typedef short    S32;
#else
typedef unsigned long  U32;     /* unsigned 32-bit integer */
typedef signed int     S32;     /* 32-bit signed integer */
#endif

typedef unsigned long long U64; /* unsigned 64-bit integer */

typedef signed char      S8;      /* 8-bit  signed integer */
typedef signed short     S16;     /* 16-bit signed integer */
typedef signed long long S64;     /* 64 bit signed integer */

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


#define TOE_WRITEL(v,a,o)	(*(volatile U32 *)((U32)(a)+(U32)(o))=(U32)(v))
#define TOE_READL(a,o)		*(volatile U32 *)((U32)(a)+(U32)(o))


#define ELPSEC_PCI_MEMORY_SIZE	(16*1024*1024)
#define ELP_VENDORID		0xE117
#define ELP_DEVICEID		0xE5F0
#define TOE_PCI_EXT_CFG_0x40	0x40


#define ELP_PCI_MAP_BAR_0	0x0001
#define ELP_PCI_MAP_BAR_1	0x0002
#define ELP_PCI_MAP_BAR_2	0x0004
#define ELP_PCI_MAP_BAR_3	0x0008


// This structure defines control and access registers and memory regions
// mapped into host virtual and physical memory
// it also holds a bus control and config information
typedef struct elphw_if_s
{
	// Virtual address mapping
	volatile char *pmem;  //  Bar0
	volatile char *preg;  //  Bar1

//#ifdef ELPSEC_PCI

	int irq;

	// PCI specific structures and working variables
	U32 bar0;	//
	U32 bar1;	//
	U32 bar2;	//
	U32 bar3;	//
	U32 bar4;	//
	U32 bar0_size;
	U32 bar1_size;
	U32 bar2_size;
	U32 bar3_size;
	U32 bar4_size;

	struct pci_access *pci_all_dev;
	struct pci_dev *toe_dev;
	int toe_fd;          /* The file descriptor for opening /dev/mem */
//#endif
} elphw_if;

typedef struct elp_id_s
{
	U16 vendor_id;
	U16 device_id;
} elp_id;

int elpsec_pci_init(elp_id *tid, elphw_if *tif,unsigned long flags);
void elpsec_pci_cleanup(elphw_if *tif);
void elpsec_info (elphw_if *tif);
void elpsec_pci_reset(elphw_if *tif);

#endif
