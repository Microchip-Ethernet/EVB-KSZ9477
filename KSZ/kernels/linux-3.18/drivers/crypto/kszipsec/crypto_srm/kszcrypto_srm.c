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
// Security Resource Manager driver
//
//
//-----------------------------------------------------------------------
//
// Copyright (C) 2006-2007, Micrel, Inc.
//
//-----------------------------------------------------------------------*/

#if defined( ELPSEC_LINUX ) || defined( DEF_LINUX )
#if defined( DEF_LINUX )
#include <linux/kernel.h>
#endif

#include "elpipsec.h"
#include "elpipsechw.h"
#include "elpcryptohw.h"
#include "elpcrypto.h"

/* you must previous initialize the ESPAH module */
extern espah_module _espah_module;
#endif

// Request context and data blocks from the SRM
//
int
elp_srm_request_blocks (
	U32 encryption_algo,
	U32 encryption_blocks,
	U32 prefered_encryption_context_token,
	U32 hash_algo,
	U32 hash_blocks,
	U32 prefered_hash_context_token,
	U32 thread_id,
	// stuff after this is replies
	U32 * r_encryption_base_token,
	U32 * r_encryption_blocks,
	U32 * r_encryption_context_token,
	U32 * r_encryption_context_dirty_flag,
	U32 * r_hash_base_token,
	U32 * r_hash_blocks,
	U32 * r_hash_context_token,
	U32 * r_hash_context_dirty_flag )
{
	U32 t;

	// build 31:0
	t = ( encryption_algo << ELPSEC_SRM_C1_MREQ_ENCRALG )				|
		( encryption_blocks << ELPSEC_SRM_C1_MREQ_ENCBLOCKS )			|
		( prefered_encryption_context_token << ELPSEC_SRM_C1_MREQ_ENCCTX )	|
		( hash_algo << ELPSEC_SRM_C1_MREQ_HASHALG )				|
		(( hash_blocks & 0xF ) << ELPSEC_SRM_C1_MREQ_HASHBLOCKS );

	*_espah_module.srm_cmd0 = t;

	// build 63:32
	t = (hash_blocks >> 4) |
		(prefered_hash_context_token << ELPSEC_SRM_C2_MREQ_HASHCTX) |
		(thread_id << ELPSEC_SRM_C2_MREQ_THREADID_1);
	*_espah_module.srm_cmd1 = t;

	// build 66:64
	*_espah_module.srm_cmd2 = 0x1;

	// do
	*_espah_module.srm_go = 1;

	t = 1UL << 20;
	while ((*_espah_module.srm_rdy & 1) == 0)
	{
		if (!--t)
		{
			return ESPAH_FAILED_TIMEOUT;
		}
	}

	// read results

	// parse bits 31:0
	t = *_espah_module.srm_ret0;
	if (r_encryption_base_token)
		*r_encryption_base_token = (t >> ELPSEC_SRM_R1_MREQ_ENCRTOKEN) & 0x00FF;
	if (r_encryption_blocks)
		*r_encryption_blocks = (t >> ELPSEC_SRM_R1_MREQ_ENCRBLOCKS) & 0x003F;
	if (r_encryption_context_token)
		*r_encryption_context_token = (t >> ELPSEC_SRM_R1_MREQ_ENCRCTX) & 0x3FFF;
	if (r_encryption_context_dirty_flag)
		*r_encryption_context_dirty_flag = (t >> ELPSEC_SRM_R1_MREQ_ENCRDIRTY) & 0x0001;
	if (r_hash_base_token)
		*r_hash_base_token = (t >> ELPSEC_SRM_R1_MREQ_HASHTOKEN);
	// parse bits 63:32
	t = *_espah_module.srm_ret1;
	if (r_hash_base_token)
		*r_hash_base_token |= ((t >> ELPSEC_SRM_R2_MREQ_HASHTOKEN) & 0x000F) << 3;
	if (r_hash_blocks)
		*r_hash_blocks = (t >> ELPSEC_SRM_R2_MREQ_HASHBLOCKS) & 0x003F;
	if (r_hash_context_token)
		*r_hash_context_token = (t >> ELPSEC_SRM_R2_MREQ_HASHCTX) & 0x3FFF;
	if (r_hash_context_dirty_flag)
		*r_hash_context_dirty_flag = (t >> ELPSEC_SRM_R2_MREQ_HASHDIRTY) & 0x0001;

	return 0;
}

int
elp_srm_release_blocks (
	U32 encryption_base_token,
	U32 encryption_blocks,
	U32 encryption_context_token,
	U32 encryption_context_flag,
	U32 hash_base_token,
	U32 hash_blocks,
	U32 hash_context_token,
	U32 hash_context_flag,
	U32 thread_id )
{
	U32 t;

	// bits 31:0
	t = 0x02 |
		(encryption_base_token << ELPSEC_SRM_C1_MREL_ENCRTOKEN)		|
		(encryption_blocks << ELPSEC_SRM_C1_MREL_ENCBLOCKS)		|
		(encryption_context_token << ELPSEC_SRM_C1_MREL_ENCRCTX)	|
		(encryption_context_flag << ELPSEC_SRM_C1_MREL_ENCRPEND)	|
		((hash_base_token & 1) << ELPSEC_SRM_C1_MREL_HASHTOKEN);
	*_espah_module.srm_cmd0 = t;

	// bits 63:32
	t = (hash_base_token >> 1) |
		(hash_blocks << ELPSEC_SRM_C2_MREL_HASHBLOCKS)		|
		(hash_context_token << ELPSEC_SRM_C2_MREL_HASHCTX)	|
		(hash_context_flag << ELPSEC_SRM_C2_MREL_HASHPEND)	| (thread_id << 28);
	*_espah_module.srm_cmd1 = t;

	// bits 78:64
	t = (thread_id >> 4) | (0x01 << (76 - 64));	// ???
	*_espah_module.srm_cmd2 = t;

	// do
	*_espah_module.srm_go = 1;

	t = 1UL << 20;
	while ((*_espah_module.srm_rdy & 1) == 0)
	{
		if (!--t)
		{
			return ESPAH_FAILED_TIMEOUT;
		}
	}

	return 0;
}

int
elp_srm_engine_request (
	U32 encryption_request,
	U32 encryption_flag,
	U32 hash_request,
	U32 hash_flag,
	U32 thread_id,
	// replies
	U32 * r_encryption_resource_token,
	U32 * r_encryption_flags,
	U32 * r_hash_resource_token,
	U32 * r_hash_flags)
{
	U32 t;

	// bits 31:0
	t = 1 | (encryption_request << ELPSEC_SRM_C1_EREQ_ENCRCTX)	|
		(encryption_flag << ELPSEC_SRM_C1_EREQ_ENCRFLAG)	|
		(hash_request << ELPSEC_SRM_C1_EREQ_HASHCTX);
	*_espah_module.srm_cmd0 = t;

	// bits 63:32
	t = (hash_flag << ELPSEC_SRM_C2_EREQ_HASHFLAG) |
		(thread_id << ELPSEC_SRM_C2_EREQ_THREADID_1) | (1UL << 18);
	*_espah_module.srm_cmd1 = t;

	// do
	*_espah_module.srm_go = 1;

	t = 1UL << 20;
	while ((*_espah_module.srm_rdy & 1) == 0)
	{
		if (!--t)
		{
			return ESPAH_FAILED_TIMEOUT;
		}
	}

	// read response

	// bits 9:0
	t = *_espah_module.srm_ret0;
	if (r_encryption_resource_token)
		*r_encryption_resource_token = t & 0x000F;
	if (r_encryption_flags)
		*r_encryption_flags = (t >> ELPSEC_SRM_R1_EREQ_ENCRDIRTY) & 1;
	if (r_hash_resource_token)
		*r_hash_resource_token = (t >> ELPSEC_SRM_R1_EREQ_HASHTOKEN) & 0x000F;
	if (r_hash_flags)
		*r_hash_flags = (t >> ELPSEC_SRM_R1_EREQ_HASHDIRTY) & 1;

	return 0;
}

int
elp_srm_engine_release (U32 encryption_resource_token, U32 hash_resource_token, U32 thread_id)
{
	U32 t;

	// bits 28:0
	t = 3 | (encryption_resource_token << ELPSEC_SRM_C1_EREL_ENCRCTX) |
		(hash_resource_token << ELPSEC_SRM_C1_EREL_HASHCTX)		|
		(thread_id << ELPSEC_SRM_C1_EREL_THREADID_1) | (0x1 << 26);

	*_espah_module.srm_cmd0 = t;

	// do
	*_espah_module.srm_go = 1;

	t = 1UL << 20;
	while ((*_espah_module.srm_rdy & 1) == 0)
	{
		if (!--t)
		{
			return ESPAH_FAILED_TIMEOUT;
		}
	}

	return 0;
}

int
elp_crypto_srm_setup (handle_ctx * ctx, U32 in_size, U32 algo)
{
	U32 blocks;

	ctx->algo = algo;
	ctx->blocks = (in_size + 63) >> 6;
	if (elp_srm_request_blocks (algo,
			ctx->blocks,	// data blocks
			0,	//prefered token
			0, 0, 0, ctx->index | (algo << 6),
			&ctx->data_token,
			&blocks,
			&ctx->context_token,
			NULL, NULL, NULL, NULL, NULL))
	{
		return -1;
	}

	if (blocks != ctx->blocks)
	{
		return -1;
	}

	if (elp_srm_engine_request (ctx->context_token, 1, 0, 0,
			ctx->index | (algo << 6), &ctx->encrypt_token,
			NULL, NULL, NULL))
	{
		// free the memory block
		elp_srm_release_blocks (ctx->data_token, ctx->blocks, ctx->context_token,
			0, 0, 0, 0, 0, ctx->index | (algo << 6));

		return -1;
	}

	switch (algo)
	{
		case CRYPTO_CONTEXT_HMAC:
			ctx->secret = (U32*)ctx->ctx + ((((ctx->context_token<<2)|0x10000) + ELPSEC_HASH_CONTEXT )>>2);
			ctx->pctx   = (U32*)ctx->ctx + (((ctx->context_token<<2)|0x10000)>>2);
			ctx->context_index = (ctx->context_token>>4)&0x7;
			break;
		case CRYPTO_CONTEXT_RC4:
			ctx->secret = ctx->ctx + (ELPSEC_RC4_KEY_OFF>>2);
			ctx->pctx   = ( U32* )( ctx->ctx + ((ELPSEC_RC4_CTX_OFF + (ctx->context_token<<2)) >> 2));
			ctx->context_index = (ctx->context_token>>7)&0x7;
			break;
		default:
		case CRYPTO_CONTEXT_AES:
			ctx->context_index = ((ctx->context_token-0x2040)/20);
			ctx->pctx   = (U32*)ctx->ctx + (((ctx->context_token<<2)|0x10000)>>2);
			break;
		case CRYPTO_CONTEXT_DES:
			ctx->context_index = (ctx->context_token>>3)&0x7;
			ctx->pctx   = (U32*)ctx->ctx + (((ctx->context_token<<2)|0x10000)>>2);
			break;

	}

	ctx->pdata  = ((U32)ctx->ctx + ((ctx->data_token & 0xE0) << 8) + ((ctx->data_token & 0x1F) << 6));
	PDEBUG (EDCTX, "SRM SETUP [ID:%lX] alg:%d: blocks:%d=%d: ctoken:%X dtoken:%X etoken:%X [data@%X ctx@%p key@%p]\n",
		ctx->index | (algo << 6),
		(int)algo, (int)blocks, (int)ctx->blocks, (int)ctx->context_token,
		(int)ctx->data_token, (int)ctx->encrypt_token,
		(int)ctx->pdata, ctx->pctx, ctx->secret);

	return 0;
}

int
elp_crypto_srm_fini (handle_ctx * ctx)
{
	int failed = 0;
	// SRM unlock memory
	if (elp_srm_release_blocks (ctx->data_token, ctx->blocks, ctx->context_token,
			0, 0, 0, 0, 0,
			ctx->index | (ctx->algo << 6)) != 0)
	{
		failed = 1;
	}

	// SRM release engine
	if (elp_srm_engine_release (ctx->encrypt_token, 0, ctx->index | (ctx->algo << 6)))
	{
		failed = 1;
	}

	return failed ? -1 : 0;
}
