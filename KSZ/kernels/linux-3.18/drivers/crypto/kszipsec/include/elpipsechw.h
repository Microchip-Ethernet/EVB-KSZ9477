/*-----------------------------------------------------------------------
//
// Proprietary Information of Elliptic Semiconductor
// Copyright (C) 2002, all rights reserved
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


#ifndef _ELPIPSECHW_H
#define _ELPIPSECHW_H

#include "elptypes.h"

#ifdef DEF_KSZ
#define HWVERSION "KSZ8692P"
#else
#define HWVERSION "AVNET PCI HW05092708"
#endif


enum {
	ESPAH_INBOUND_DIRECTION,
	ESPAH_OUTBOUND_DIRECTION
};

enum {
	ESPAH_ESP_TRANSFORM,
	ESPAH_AH_TRANSFORM
};
enum {
	ESPAH_BYTE_TTL,
	ESPAH_TIME_TTL,
	ESPAH_NO_TTL=0xFF
};

#define ESPAH_GLOBAL_OFFSET         0x0000

#define ESPAH_INT_EN_REG            (ESPAH_GLOBAL_OFFSET+0x0000)
#define ESPAH_INT_STAT_REG          (ESPAH_GLOBAL_OFFSET+0x0004)
#define ESPAH_SEC_REQ_REG           (ESPAH_GLOBAL_OFFSET+0x0008)
#define ESPAH_SEC_GNT_REG           (ESPAH_GLOBAL_OFFSET+0x000c)
#define ESPAH_SRM_GO_REG            (ESPAH_GLOBAL_OFFSET+0x0010)
#define ESPAH_SRM_RDY_REG           (ESPAH_GLOBAL_OFFSET+0x0014)
#define ESPAH_OUT_SRC_PTR_REG       (ESPAH_GLOBAL_OFFSET+0x0020)
#define ESPAH_OUT_DST_PTR_REG       (ESPAH_GLOBAL_OFFSET+0x0024)
#define ESPAH_OUT_SAI_REG           (ESPAH_GLOBAL_OFFSET+0x002c)
#define ESPAH_IN_SRC_PTR_REG        (ESPAH_GLOBAL_OFFSET+0x0040)
#define ESPAH_IN_DST_PTR_REG        (ESPAH_GLOBAL_OFFSET+0x0044)
#define ESPAH_IN_SAI_REG            (ESPAH_GLOBAL_OFFSET+0x004c)
#define ESPAH_OUT_STAT_REG          (ESPAH_GLOBAL_OFFSET+0x0030)
#define ESPAH_IN_STAT_REG           (ESPAH_GLOBAL_OFFSET+0x0050)
#define ESPAH_OUT_OFFSET_REG        (ESPAH_GLOBAL_OFFSET+0x0028)
#define ESPAH_IN_OFFSET_REG         (ESPAH_GLOBAL_OFFSET+0x0048)
#define ESPAH_SRM_CMD_0_REG         (ESPAH_GLOBAL_OFFSET+0x0060)
#define ESPAH_SRM_CMD_1_REG         (ESPAH_GLOBAL_OFFSET+0x0064)
#define ESPAH_SRM_CMD_2_REG         (ESPAH_GLOBAL_OFFSET+0x0068)
#define ESPAH_SRM_RET_0_REG         (ESPAH_GLOBAL_OFFSET+0x0070)
#define ESPAH_SRM_RET_1_REG         (ESPAH_GLOBAL_OFFSET+0x0074)

/* bits */
#define ESPAH_IN_STAT_LENGTH            0
#ifdef DEF_KSZ
#define ESPAH_IN_STAT_LENGTH_SIZE      16
#else
#define ESPAH_IN_STAT_LENGTH_SIZE      13
#endif
#define ESPAH_IN_STAT_RET_CODE         24
#define ESPAH_IN_STAT_RET_CODE_SIZE     4
#define ESPAH_IN_STAT_BUSY             31

#define ESPAH_INT_STAT_OUTBND_DONE      0
#define ESPAH_INT_STAT_INBND_DONE       1

/* STAT codes that go into the STAT_RET_CODE secion of a register */
#define TOE_ESPAH_STAT_OK          0
#define TOE_ESPAH_STAT_BUSY        1
#define TOE_ESPAH_STAT_SOFT_TTL    2
#define TOE_ESPAH_STAT_HARD_TTL    3
#define TOE_ESPAH_STAT_SA_INACTIVE 4
#define TOE_ESPAH_STAT_REPLAY      5
#define TOE_ESPAH_STAT_ICV_FAIL    6
#define TOE_ESPAH_STAT_SEQ_ROLL    7
#define TOE_ESPAH_STAT_MEM_ERROR   8
#define TOE_ESPAH_STAT_VERS_ERROR  9
#define TOE_ESPAH_STAT_PROT_ERROR  10
#define TOE_ESPAH_STAT_PYLD_ERROR  11
#define TOE_ESPAH_STAT_PAD_ERROR   12


// Security Base:
#define ESPAH_SEC_BASE_ADDR         (ESPAH_GLOBAL_OFFSET+0x020000)

#ifndef DEF_KSZ
// DPRAM on PCI configuration
#define ESPAH_DPRAM_BASE            (ESPAH_GLOBAL_OFFSET+0x400000)
// 0x2000 - 0x20 - 0xE0 (0x20 is for the DDT and 0xE0 to keep SA aligned)
#define ESPAH_DPRAM_SIZE            (0x2000 - 0x20 - 0xE0)
#endif

#ifndef DEF_KSZ
#define ESPAH_DPRAM_PACKET_OUT_SIZE  (0x800)  // 2K for in/out
#define ESPAH_DPRAM_PACKET_IN_SIZE   (0x800)
#define ESPAH_DDT_SIZE               (0x10)
#define ESPAH_DIRECTION              1
#else
#define ESPAH_DPRAM_PACKET_OUT_SIZE  (0x10000)  // 64K for IP in/out
#define ESPAH_DPRAM_PACKET_IN_SIZE   (0x10000)
#define ESPAH_DDT_SIZE               (0x10)
#define ESPAH_DIRECTION              2
#define ESPAH_DPRAM_PACKET_OFFSET    (ESPAH_DPRAM_PACKET_OUT_SIZE / sizeof( U32 ))
#define ESPAH_DDT_OFFSET             (ESPAH_DDT_SIZE / sizeof( U32 ))
#endif

#define ESPAH_SA_SIZE               0x100  // 256 bytes per SA

#ifndef DEF_KSZ
#define ESPAH_SA_POOL_SIZE          (ESPAH_DPRAM_SIZE - (ESPAH_DPRAM_PACKET_OUT_SIZE+ESPAH_DPRAM_PACKET_IN_SIZE))
#define ESPAH_SA_MAX_NUMBER         (ESPAH_SA_POOL_SIZE/ESPAH_SA_SIZE)

#else
#define ESPAH_SA_POOL_SIZE          0
#define ESPAH_SA_MAX_NUMBER         16

#ifdef DEF_LINUX
extern unsigned char* ipsec_sa_map;
extern dma_addr_t ipsec_sa_base;

#define ESPAH_DPRAM_BASE  ipsec_sa_map

#define PHYS_ADDR( x )  (( unsigned char* )( x ) - ipsec_sa_map + ipsec_sa_base )

#else
#define ESPAH_DPRAM_BASE  0x700000

#define PHYS_ADDR( x )  x
#endif

#define ESPAH_DPRAM_SIZE  ( \
    ESPAH_DPRAM_PACKET_OUT_SIZE * ESPAH_DIRECTION + \
    ESPAH_DPRAM_PACKET_IN_SIZE * ESPAH_DIRECTION + \
    ESPAH_DDT_SIZE * 2 * ESPAH_DIRECTION + \
    0x100 - \
    ESPAH_DDT_SIZE * 2 * ESPAH_DIRECTION )
#define ESPAH_SA_BASE  ( ESPAH_DPRAM_BASE + ESPAH_DPRAM_SIZE )
#define ESPAH_SIZE  ( ESPAH_SA_SIZE * ESPAH_SA_MAX_NUMBER + \
    ESPAH_DPRAM_SIZE )
#endif

#define ESPAH_HANDLES_MAX		(ESPAH_SA_MAX_NUMBER/2)  // we need two sa per handle

#define ESPAH_OUT_BASE       (ESPAH_SA_POOL_SIZE)
#define ESPAH_IN_BASE        (ESPAH_SA_POOL_SIZE + ESPAH_DPRAM_PACKET_OUT_SIZE * ESPAH_DIRECTION)
#define ESPAH_SRC_DDT_BASE   (ESPAH_SA_POOL_SIZE + ESPAH_DPRAM_PACKET_OUT_SIZE * ESPAH_DIRECTION + ESPAH_DPRAM_PACKET_IN_SIZE * ESPAH_DIRECTION)
#define ESPAH_DST_DDT_BASE   (ESPAH_SA_POOL_SIZE + ESPAH_DPRAM_PACKET_OUT_SIZE * ESPAH_DIRECTION + ESPAH_DPRAM_PACKET_IN_SIZE * ESPAH_DIRECTION + ESPAH_DDT_SIZE * ESPAH_DIRECTION)

#define ESPAH_AUTH_KEY_LEN_BYTE		20
#define ESPAH_AUTH_KEY_LEN_WORD		ESPAH_AUTH_KEY_LEN_BYTE/4
#define ESPAH_ENCR_KEY_LEN_BYTE		32
#define ESPAH_ENCR_KEY_LEN_WORD		ESPAH_ENCR_KEY_LEN_BYTE/4
#define ESPAH_IV_LEN_BYTE		16
#define ESPAH_IV_LEN_WORD		ESPAH_IV_LEN_BYTE/4
#define ESPAH_SPI_LEN_BYTE		8
#define ESPAH_SPI_LEN_WORD		ESPAH_SPI_LEN_BYTE/4
#define ESPAH_TTL_LEN_BYTE		8
#define ESPAH_TTL_LEN_WORD		ESPAH_TTL_LEN_BYTE/4
#define ESPAH_THREAD_ID_LEN_BYTE	2


#define ESPAH_ENABLED_BIT		0
#define ESPAH_TTL_ENABLE_BIT		2
#define ESPAH_TTL_TYPE_BIT		3
#define ESPAH_TRANSFORM_BIT		4
#define ESPAH_MODE_BIT			5
#define ESPAH_ANTI_REPLY_ENABLE_BIT	7
#define ESPAH_EXTENDED_SEQNUM_BIT	14

// Memory layout (default)
// 2K for input
// 2K for output
// 3.75K for SA (enough for 15 simplex SAs)

#endif
