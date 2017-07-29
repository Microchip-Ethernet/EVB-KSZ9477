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


#ifndef _ELPPKMHW_H
#define _ELPPKMHW_H

#include "elptypes.h"

#define ELPSEC_HOST_HMAC_OFF		0x32000
#define ELPSEC_HOST_HASH_OFF		ELPSEC_HOST_HMAC_OFF
#define ELPSEC_HOST_DES_OFF		0x34000
#define ELPSEC_HOST_AES_OFF		0x38000
#define ELPSEC_HOST_RC4_OFF		0x36000

#define ELPSEC_HOST_MEMORY_START	0x20000

#define ELPSEC_HARDWARE_MEMORY_SIZE	2048
#define ELPSEC_LOOP_WAIT		10000

#define ELPSEC_GLOBAL_STATUS		0x0004
#define ELPSEC_STATUS_DONE		1
#define ELPSEC_HASH_STATUS_DONE		(1<<16)
#define ELPSEC_DES_STATUS_DONE		(1<<17)
#define ELPSEC_RC4_STATUS_DONE		(1<<18)
#define ELPSEC_AES_STATUS_DONE		(1<<19)
/***********************************************************************************/
/* SRM  SRM  SRM  SRM  SRM  SRM  SRM  SRM  SRM  SRM  SRM  SRM  SRM  SRM  SRM  SRM  */
/***********************************************************************************/

#define ELPSEC_SRM_CMD_0		0x0060
#define ELPSEC_SRM_CMD_1		0x0064
#define ELPSEC_SRM_CMD_2		0x0068
#define ELPSEC_SRM_RET_0		0x0070
#define ELPSEC_SRM_RET_1		0x0074

#define ELPSEC_SRM_C1_COMMAND		0

/*   SRM Cryptographic Memory Request Command Format */

#define ELPSEC_SRM_C1_MEMREQUEST	0
#define ELPSEC_SRM_C1_MREQ_ENCRALG	2
#define ELPSEC_SRM_C1_MREQ_ENCBLOCKS	5
#define ELPSEC_SRM_C1_MREQ_ENCCTX	11
#define ELPSEC_SRM_C1_MREQ_HASHALG	25
#define ELPSEC_SRM_C1_MREQ_HASHBLOCKS	28
#define ELPSEC_SRM_C2_MREQ_HASHBLOCKS	0
#define ELPSEC_SRM_C2_MREQ_HASHCTX	2
#define ELPSEC_SRM_C2_MREQ_THREADID_1	16
#define ELPSEC_SRM_C2_MREQ_THREADID_N	19
#define ELPSEC_SRM_C3_MREQ_THREADID_N	0

#define ELPSEC_SRM_R1_MREQ_ENCRTOKEN	0
#define ELPSEC_SRM_R1_MREQ_ENCRBLOCKS	8
#define ELPSEC_SRM_R1_MREQ_ENCRCTX	14
#define ELPSEC_SRM_R1_MREQ_ENCRDIRTY	28
#define ELPSEC_SRM_R1_MREQ_HASHTOKEN	29
#define ELPSEC_SRM_R2_MREQ_HASHTOKEN	0
#define ELPSEC_SRM_R2_MREQ_HASHBLOCKS	5
#define ELPSEC_SRM_R2_MREQ_HASHCTX	11
#define ELPSEC_SRM_R2_MREQ_HASHDIRTY	25

/*   SRM Cryptographic Memory Release Command Format */

#define ELPSEC_SRM_C1_MREL_MEMRELEASE	2
#define ELPSEC_SRM_C1_MREL_ENCRTOKEN	2
#define ELPSEC_SRM_C1_MREL_ENCBLOCKS	10
#define ELPSEC_SRM_C1_MREL_ENCRCTX	16
#define ELPSEC_SRM_C1_MREL_ENCRPEND	30
#define ELPSEC_SRM_C1_MREL_HASHTOKEN	31
#define ELPSEC_SRM_C2_MREL_HASHTOKEN	0
#define ELPSEC_SRM_C2_MREL_HASHBLOCKS	7
#define ELPSEC_SRM_C2_MREL_HASHCTX	13
#define ELPSEC_SRM_C2_MREL_HASHPEND	17

/*   SRM Cryptographic ENGINE Request Command Format */
#define ELPSEC_SRM_C1_ENGINEREQUEST	1
#define ELPSEC_SRM_C1_EREQ_ENCRCTX	2
#define ELPSEC_SRM_C1_EREQ_ENCRFLAG	17
#define ELPSEC_SRM_C1_EREQ_HASHCTX	18
#define ELPSEC_SRM_C2_EREQ_HASHFLAG	1
#define ELPSEC_SRM_C2_EREQ_THREADID_1	2
#define ELPSEC_SRM_C2_EREQ_THREADID_N	5

#define ELPSEC_SRM_R1_EREQ_ENCRTOKEN	0
#define ELPSEC_SRM_R1_EREQ_ENCRDIRTY	4
#define ELPSEC_SRM_R1_EREQ_HASHTOKEN	5
#define ELPSEC_SRM_R1_EREQ_HASHDIRTY	9

/*   SRM Cryptographic Engine Release Command Format */
#define ELPSEC_SRM_C1_ENGINERELEASE	3
#define ELPSEC_SRM_C1_EREL_ENCRCTX	2
#define ELPSEC_SRM_C1_EREL_HASHCTX	6
#define ELPSEC_SRM_C1_EREL_THREADID_1	10
#define ELPSEC_SRM_C1_EREL_THREADID_N	13


/***********************************************************************************/
/*DES/3DES DES/3DES DES/3DES DES/3DES DES/3DES DES/3DES DES/3DES DES/3DES DES/3DES */
/***********************************************************************************/
#define ELPSEC_DES_DATA			0x24000
#define ELPSEC_DES_CONTEXT		0x0100
#define ELPSEC_DES_CTRL			0x0000
#define ELPSEC_DES_STATUS		0x0004


#define TOE_DES_CP_CNTRL_BIT_DES_MODE	0
#define TOE_DES_CP_CNTRL_BIT_CBC_MODE	1
#define TOE_DES_CP_CNTRL_BIT_ENCRYPT	2
#define TOE_DES_CP_CNTRL_BIT_ENDIAN	3
#define TOE_DES_CP_CNTRL_BIT_RET_IV	6
#define TOE_DES_CP_CNTRL_BIT_STR_IV	7
#define TOE_DES_CP_CNTRL_BIT_RET_KEY	17
#define TOE_DES_CP_CNTRL_BIT_IV_IDX_LO	20
#define TOE_DES_CP_CNTRL_BIT_IV_IDX_HI	(TOE_DES_CP_CNTRL_BIT_IV_IDX_LO+TOE_DES_IV_IDX_WIDTH)
#define TOE_DES_CP_CNTRL_BIT_BLK_IDX_LO	24
#define TOE_DES_CP_CNTRL_BIT_BLK_IDX_HI	(TOE_DES_CP_CNTRL_BIT_BLK_IDX_LO+TOE_DES_BLK_IDX_WIDTH)
#define TOE_DES_CP_CNTRL_BIT_N_BLKS_LO	8
#define TOE_DES_CP_CNTRL_BIT_N_BLKS_HI	(TOE_DES_CP_CNTRL_BIT_N_BLKS_LO+TOE_DES_N_BLKS_WIDTH)

#define TOE_DES_CP_STAT_BIT_DONE	0

#define ELPSEC_DES_ECB			(0)
#define ELPSEC_DES_CBC			(1<<TOE_DES_CP_CNTRL_BIT_CBC_MODE)

#define ELPSEC_3DES_CBC			((1<<TOE_DES_CP_CNTRL_BIT_CBC_MODE) | (1<<TOE_DES_CP_CNTRL_BIT_DES_MODE))
#define ELPSEC_3DES_ECB			(1<<TOE_DES_CP_CNTRL_BIT_DES_MODE)

#define ELPSEC_DES_ENCRYPT		(1<<TOE_DES_CP_CNTRL_BIT_ENCRYPT)
#define ELPSEC_DES_CONTEXT_SIZE		0x20 // bytes
#define ELPSEC_DES_CONTEXT_WSIZE	(ELPSEC_DES_CONTEXT_SIZE/4) // words


/***********************************************************************************/
/* AES AES AES AES AES AES AES AES AES AES AES AES AES AES AES AES AES AES AES AES */
/***********************************************************************************/
#define ELPSEC_AES_DATA			0x28000
#define ELPSEC_AES_CONTEXT		0x0100
#define ELPSEC_AES_CTRL			0x0000
#define ELPSEC_AES_STATUS		0x0004
#define ELPSEC_AES_CTRL_1		0x0008

// Control register definitions
#define ELPSEC_AES_CP_CNTRL_BIT_ENCRYPT      2
#define ELPSEC_AES_CP_CNTRL_BIT_CBC_MODE     3
#define ELPSEC_AES_CP_CNTRL_BIT_MODE_LO      0
#define ELPSEC_AES_CP_CNTRL_BIT_CTR_MODE     4
#define ELPSEC_AES_CP_CNTRL_BIT_STR_IV       5
#define ELPSEC_AES_CP_CNTRL_BIT_RET_IV       6
#define ELPSEC_AES_CP_CNTRL_BIT_RET_INV_KEY  7
#define ELPSEC_AES_CP_CNTRL_BIT_STR_INV_KEY  8
#define ELPSEC_AES_CP_CNTRL_BIT_RET_FWD_KEY  9
#define ELPSEC_AES_CP_CNTRL_BIT_N_BLKS_LO    10
//#define ELPSEC_AES_CP_CNTRL_BIT_IV_IDX_LO    (ELPSEC_AES_CP_CNTRL_BIT_N_BLKS_LO + ELPSEC_AES_N_BLKS_WIDTH)
#define ELPSEC_AES_CP_CNTRL_BIT_IV_IDX_LO    18
#define ELPSEC_AES_CP_CNTRL_BIT_BLK_IDX_LO   21

#define ELPSEC_AES_CTRL_MSG_SIZE(s)	((s)<<ELPSEC_AES_CP_CNTRL_BIT_N_BLKS_LO)

// Second control register for CCM mode
#define ELPSEC_AES_CP_CNTRL1_BIT_N_AUTH_BLKS_LO   0
#define ELPSEC_AES_CP_CNTRL1_BIT_AUTH_ONLY        8
#define ELPSEC_AES_CP_CNTRL1_BIT_N_BYTES          16
#define ELPSEC_AES_CP_CNTRL1_BIT_MSG_END          29
#define ELPSEC_AES_CP_CNTRL1_BIT_MSG_BEGIN        30
#define ELPSEC_AES_CP_CNTRL1_BIT_CCM_MODE         31
#define ELPSEC_AES_CP_CNTRL1_BIT_OMAC_MODE        31
#define ELPSEC_AES_CP_CNTRL1_BIT_OMAC_VERS        8
#define ELPSEC_AES_CP_CNTRL1_BIT_U_LENGTH         9


#define ELPSEC_AES_CTRL1_MSG_END	(1<<ELPSEC_AES_CP_CNTRL1_BIT_MSG_END)
#define ELPSEC_AES_CTRL1_MSG_BEGIN	(1<<ELPSEC_AES_CP_CNTRL1_BIT_MSG_BEGIN)
#define ELPSEC_AES_CTRL1_CCM_MODE	(1<<ELPSEC_AES_CP_CNTRL1_BIT_CCM_MODE)
#define ELPSEC_AES_CTRL1_AUTH_ONLY	(1<<ELPSEC_AES_CP_CNTRL1_BIT_AUTH_ONLY)
#define ELPSEC_AES_CTRL1_OMAC_MODE	(1<<ELPSEC_AES_CP_CNTRL1_BIT_OMAC_MODE)
#define ELPSEC_AES_CTRL1_OMAC_V2	(1<<ELPSEC_AES_CP_CNTRL1_BIT_OMAC_VERS)
#define ELPSEC_AES_CTRL1_MSG_SIZE(s)	((s)<<ELPSEC_AES_CP_CNTRL1_BIT_N_BYTES)
#define ELPSEC_AES_CTRL1_AAD_BLOCKS(s)	((s)<<ELPSEC_AES_CP_CNTRL1_BIT_N_AUTH_BLKS_LO)
#define ELPSEC_AES_CTRL1_TAG_BLOCKS(s)	((s)<<ELPSEC_AES_CP_CNTRL1_BIT_U_LENGTH)
#define ELPSEC_AES_CTRL1_CCM_MSG_SIZE(s) ((s)<<ELPSEC_AES_CP_CNTRL_BIT_N_BLKS_LO)


#define ELPSEC_AES_IV_IDX_WIDTH		3  //Valid range 1-3.
#define ELPSEC_AES_BLK_IDX_WIDTH	7  //Valid range 1-32.

#define ELPSEC_AES_N_BLKS_WIDTH		(ELPSEC_AES_BLK_IDX_WIDTH+1)
#define ELPSEC_AES_DATA_WIDTH		32
#define ELPSEC_AES_KEY_WIDTH		32


#define ELPSEC_AES_BLOCK_PAGE_SIZE	16 // bytes
#define ELPSEC_AES_BLOCK_PAGE_WSIZE	(ELPSEC_AES_BLOCK_PAGE_SIZE/4) // words

#define ELPSEC_AES_CONTEXT_SIZE		(0x50) // bytes
#define ELPSEC_AES_CONTEXT_WSIZE	(ELPSEC_AES_CONTEXT_SIZE/4) // words
#define ELPSEC_AES_OUTPUT_DATA_OFFSET	4
#define ELPSEC_AES_OMAC			(1<<ELPSEC_AES_CP_CNTRL_BIT_CBC_MODE)
#define ELPSEC_AES_CBC			(1<<ELPSEC_AES_CP_CNTRL_BIT_CBC_MODE)
#define ELPSEC_AES_CTR			(1<<ELPSEC_AES_CP_CNTRL_BIT_CTR_MODE)
#define ELPSEC_AES_ECB			(0)
#define ELPSEC_AES_CCM			0x80000000	// This is only for software information

#define ELPSEC_AES128			(0)
#define ELPSEC_AES192			(1)
#define ELPSEC_AES256			(2)
#define ELPSEC_AES_ENCRYPT		(1<<ELPSEC_AES_CP_CNTRL_BIT_ENCRYPT)

/***********************************************************************************/
/* HMAC HMAC HMAC HMAC HMAC HMAC HMAC HMAC HMAC HMAC HMAC HMAC HMAC HMAC HMAC HMAC */
/***********************************************************************************/

#define ELPSEC_HASH_DATA		0x22000
#define ELPSEC_HASH_SECRET		0x33000
#define ELPSEC_HASH_CONTEXT		0x0800
#define ELPSEC_HASH_CTRL		0x0000
#define ELPSEC_HASH_STATUS		0x0004
#define ELPSEC_HASH_CTRL1		0x0008
#define ELPSEC_HASH_CTRL2		0x000C
#define ELPSEC_HASH_CTRL3		0x0010
#define ELPSEC_HASH_SEQN		0x0014

#define TOE_HASH_HMAC_SET		0
#define TOE_HASH_SSLMAC_SET		1
#define TOE_HASH_MSG_BEGIN		2
#define TOE_HASH_MSG_END		3
#define TOE_HASH_RET_CTX		4
#define TOE_HASH_STR_CTX		5
#define TOE_HASH_STR_MSG		6
#define TOE_HASH_MODE			7
#define TOE_HASH_IV_LEN			24

#define TOE_HASH_CTRL1_TOTAL		16
#define TOE_HASH_CTRL1_SIZE		0

#define TOE_HASH_CTRL3_SECRET_ADDR	0
#define TOE_HASH_CTRL3_SECRET_SIZE	16

#define TOE_HASH_CTRL2_IV_ADDR		0
#define TOE_HASH_CTRL2_CTX_IDX		24
#define TOE_HASH_CTRL2_MSG_STAR_BLOCK	16

#define ELPSEC_HASH_HMAC		(1<<TOE_HASH_HMAC_SET)
#define ELPSEC_HASH_SSLMAC		(1<<TOE_HASH_SSLMAC_SET)
#define ELPSEC_HASH_MSG_BEGIN		(1<<TOE_HASH_MSG_BEGIN)
#define ELPSEC_HASH_MSG_END		(1<<TOE_HASH_MSG_END)
#define ELPSEC_HASH_RET_CTX		(1<<TOE_HASH_RET_CTX)
#define ELPSEC_HASH_STR_2CTX		(1<<TOE_HASH_STR_CTX)
#define ELPSEC_HASH_STR_2MSG		(1<<TOE_HASH_STR_MSG)
#define ELPSEC_HASH_SHA256		(1<<TOE_HASH_MODE)
#define ELPSEC_HASH_SHA512		(3<<TOE_HASH_MODE)
#define ELPSEC_HASH_SHA1		(4<<TOE_HASH_MODE)
#define ELPSEC_HASH_MD5			(5<<TOE_HASH_MODE)
#define ELPSEC_HASH_IV_LEN(l)		((l)<<TOE_HASH_IV_LEN)

#define ELPSEC_HASH_MSG_TOTAL(t)	((t)<<TOE_HASH_CTRL1_TOTAL)
#define ELPSEC_HASH_MSG_SIZE(s)		((s)<<TOE_HASH_CTRL1_SIZE)

#define ELPSEC_HASH_SECRET_ADDR(t)	((0xFF&(t))<<TOE_HASH_CTRL3_SECRET_ADDR)
#define ELPSEC_HASH_SECRET_SIZE(s)	((s)<<TOE_HASH_CTRL3_SECRET_SIZE)

#define ELPSEC_HASH_IV_ADDR(t)		((t)<<TOE_HASH_CTRL2_IV_ADDR)
#define ELPSEC_HASH_CTX_IDX(s)		((s)<<TOE_HASH_CTRL2_CTX_IDX)
#define ELPSEC_HASH_MSG_START(s)	((s)<<TOE_HASH_CTRL2_MSG_STAR_BLOCK)


#define ELPSEC_HASH_IV_PAGE_SIZE	20 // bytes
#define ELPSEC_HASH_LEN_SIZE		8
#define ELPSEC_HASH_TRAIL_SIZE		1


#define ELPSEC_HASH_BLOCK_PAGE_SIZE	64 // bytes
#define ELPSEC_HASH_BLOCK_PAGE_WSIZE	(ELPSEC_HASH_BLOCK_PAGE_SIZE/4) // words

#define ELPSEC_HASH_CTRL_REG_OFFSET	0x0
#define ELPSEC_HASH_STATUS_REG_OFFSET	0x4
#define ELPSEC_HASH_DEST_REG_OFFSET	0x8
#define ELPSEC_HASH_CBASE_REG_OFFSET	0xc
#define ELPSEC_HASH_CLEN_REG_OFFSET	0x10
#define ELPSEC_HASH_SECRET0_REG_OFFSET	0x14
#define ELPSEC_HASH_SECRET1_REG_OFFSET	0x18
#define ELPSEC_HASH_SECRET2_REG_OFFSET	0x1c
#define ELPSEC_HASH_SECRET3_REG_OFFSET	0x20
#define ELPSEC_HASH_SECRET4_REG_OFFSET	0x24
#define ELPSEC_HASH_SEQN0_REG_OFFSET	0x28
#define ELPSEC_HASH_CONTEXT_OFFSET	0x100
#define ELPSEC_HASH_CONTEXT_SIZE	0x40


/***********************************************************************************/
/* RC4 RC4 RC4 RC4 RC4 RC4 RC4 RC4 RC4 RC4 RC4 RC4 RC4 RC4 RC4 RC4 RC4 RC4 RC4 RC4 */
/***********************************************************************************/
#define ELPSEC_RC4_KEY			0x0000
#define ELPSEC_RC4_CTRL			0x0020
#define ELPSEC_RC4_STATUS		0x0024
#define ELPSEC_RC4_SRC			0x0028
#define ELPSEC_RC4_DST			0x002C
#define ELPSEC_RC4_LEN			0x0030

#define ELPSEC_RC4_CONTEXT		0x1000
#define ELPSEC_RC4_DATA			0x26000
#define ELPSEC_RC4_KEY_OFF		0x16000
#define ELPSEC_RC4_CTX_OFF		0x10000

#define ELPSEC_RC4_KEY_SIZE		16 // bytes
#define ELPSEC_RC4_KEY_WSIZE		(ELPSEC_RC4_KEY_SIZE/4)// words
#define ELPSEC_RC4_CONTEXT_SIZE		260 // 256 + r % j
#define ELPSEC_RC4_CONTEXT_WSIZE	(ELPSEC_RC4_CONTEXT_SIZE/4)// words
#define ELPSEC_RC4_CONTEXT_MEM_MAX	512 // Actual context memory
#define ELPSEC_RC4_CTRL_PAGE		0
#define ELPSEC_RC4_CTRL_40		0
#define ELPSEC_RC4_CTRL_128		(1<<11)
#define ELPSEC_RC4_CTRL_MODE_0		(0<<9) // Generate context from key and encryption
#define ELPSEC_RC4_CTRL_MODE_1		(1<<9) // Encrypt with existing context
#define ELPSEC_RC4_CTRL_MODE_2		(2<<9) // Generate context from key with no encryption


#endif
