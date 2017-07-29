/*-----------------------------------------------------------------------
//
// Proprietary Information of Elliptic Semiconductor
// Copyright (C) 2002-2004, all rights reserved
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
#include <elpcrypto.h>
#endif


handle_ctx _aes_mctx[ CRYPTO_AES_MAX_CONTEXTS + 1 ];
crypto_module _aes_ctx;

static int _aes_xxx_set_context (handle_ctx * ctx);
static int _aes_xxx_get_context (handle_ctx * ctx);

int _aes_init (
	U32 mmap )
{
	EMEMSET( &_aes_mctx[ 0 ], 0, sizeof( _aes_mctx ));
	EMEMSET( &_aes_ctx, 0, sizeof( _aes_ctx ));

	// Initialize AES crypto module contexts
	PDEBUG (EDINIT, "crypto_init: AES Contexts (%d) Initialization.\n",
		CRYPTO_AES_MAX_CONTEXTS);
	PDEBUG (EDINIT,
		"crypto_init:\tdata=%X, ctx=%X, ctrl=%X,  stat=%X\n"
		"\t\t\t\tnmap @ 0x%lX, ctx @ %p\n\n",
		ELPSEC_AES_DATA,
		ELPSEC_HOST_AES_OFF + ELPSEC_AES_CONTEXT,
		ELPSEC_HOST_AES_OFF + ELPSEC_AES_CTRL,
		ELPSEC_HOST_AES_OFF + ELPSEC_AES_STATUS, mmap, &_aes_ctx);

	elp_mutex_init( _aes_ctx.mlock );
	_aes_ctx.cookie = ELP_COOKIE;
	_aes_ctx.active = 1;
	_aes_ctx.type = CRYPTO_MODULE_AES;
	_aes_ctx.max = CRYPTO_AES_MAX_CONTEXTS;
	_aes_ctx.mctx = _aes_mctx;
	_aes_ctx.data_size = 0;
	_aes_ctx.data = (U32 *)(mmap + ELPSEC_HOST_MEMORY_START);
	_aes_ctx.ctrl = (U32 *)(mmap + ELPSEC_HOST_AES_OFF + ELPSEC_AES_CTRL);
#ifdef USE_GLOBAL_STATUS
	_aes_ctx.stat = (U32 *)(mmap + ELPSEC_GLOBAL_STATUS);
#else
	_aes_ctx.stat = (U32 *)(mmap + ELPSEC_HOST_AES_OFF + ELPSEC_AES_STATUS);
#endif

	return CRYPTO_OK;
}


int crypto_aes_wait_ (
	int            handle,
	int            decrypt,
	unsigned char *in_buf,
	int            in_size,
	unsigned char *out_buf,
	int           *out_size,
	int            wait )
{
	int dsize;
	U32 mode, blocks;
	handle_ctx *ctx;
	int wait_count = ELPSEC_LOOP_WAIT;

	if ( ( decrypt != ENCRYPT ) && ( decrypt != DECRYPT ) )
		return CRYPTO_INVALID_ARGUMENT;
	if ( ( in_buf == 0 ) || ( out_buf == 0 ) || ( out_size == 0 ) )
		return CRYPTO_INVALID_ARGUMENT;
	if ( in_size < CRYPTO_AES_MIN_BLOCK_SIZE )
		return CRYPTO_INVALID_ARGUMENT;
	if ( ( in_size % CRYPTO_AES_MIN_BLOCK_SIZE ) != 0 )
		return CRYPTO_INVALID_BLOCK_ALIGNMENT;
	if ( ( *out_size ) < in_size )
		return CRYPTO_INVALID_ARGUMENT;

	ctx = context_lookup( handle );
	if ( !ctx )
		return CRYPTO_INVALID_HANDLE;

	// acquire context
	elp_mutex_lock( ctx->hw_module->mlock );

	// srm allocate
	if ( elp_crypto_srm_setup( ctx, ELPSEC_HARDWARE_MEMORY_SIZE,
			CRYPTO_CONTEXT_AES ) )
	{
		elp_mutex_unlock( ctx->hw_module->mlock );
		return CRYPTO_SRM_FAILED;
	}

	_aes_xxx_set_context( ctx );

	// first calculate a number of 16 byte blocks
	blocks = in_size >> 4;
	ctx->prev_data_size += in_size;

	mode = ctx->mode;
	mode |= decrypt ? 0 : ELPSEC_AES_ENCRYPT;

	if ( in_buf )
	{
		MEMCPY32HTONL( ctx->pdata, (U32 *) in_buf, in_size >> 2 );
		PDUMPWORD (EDDUMP, ctx->pdata, in_size, "SECTOE: AES INPUT", 0);
	}

	mode |= ( 1UL << ELPSEC_AES_CP_CNTRL_BIT_RET_FWD_KEY );
	mode |= ( 1UL << ELPSEC_AES_CP_CNTRL_BIT_RET_IV );
	mode |= ( 1UL << ELPSEC_AES_CP_CNTRL_BIT_STR_IV );
	mode |= ( ctx->context_index <<  ELPSEC_AES_CP_CNTRL_BIT_IV_IDX_LO );
	mode |= ELPSEC_AES_CTRL_MSG_SIZE( blocks );

	*ctx->hw_module->ctrl = (mode);

#ifdef USE_GLOBAL_STATUS
	if ( !wait && ( *ctx->hw_module->stat & ELPSEC_AES_STATUS_DONE ) == 0 )
#else
	if ( !wait && ( *ctx->hw_module->stat & ELPSEC_STATUS_DONE ) == 0 )
#endif
	{
		ctx->out_size = in_size;
		ctx->data_out = out_buf;
		elp_mutex_unlock( ctx->hw_module->mlock );
		return CRYPTO_INPROGRESS;
	}

#ifdef USE_GLOBAL_STATUS
	while ( wait_count &&
		( *ctx->hw_module->stat & ELPSEC_AES_STATUS_DONE ) == 0 )
#else
	while ( wait_count &&
		( *ctx->hw_module->stat & ELPSEC_STATUS_DONE ) == 0 )
#endif
	{
		wait_count--;
	}

	PDEBUG (EDAES, "AES CTRL=0x%lX  [%lx] [w:%d] %d bytes [%ld blocks]\n",
		*ctx->hw_module->ctrl,
		*ctx->hw_module->stat, wait_count, in_size, blocks);

#ifdef USE_GLOBAL_STATUS
	*ctx->hw_module->stat |= ELPSEC_AES_STATUS_DONE;
#endif

	ctx->first_use = 0;

	if ( !wait_count )
	{
		PINFO ("AES FAILED: CTRL=0x%lX [%lx] [I:%d]\n",
			*ctx->hw_module->ctrl,
			*ctx->hw_module->stat, ctx->index);
		elp_mutex_unlock( ctx->hw_module->mlock );
		return CRYPTO_FAILED;
	}

	dsize = in_size;

	PDUMPWORD (EDDUMP, ctx->pdata, dsize, "SECTOE: AES OUTPUT", 0);

	_aes_xxx_get_context( ctx );
	if ( out_size && out_buf )
	{
		MEMCPY32HTONL(( U32* ) out_buf, ( U32* ) ctx->pdata,
			dsize >> 2 );
		*out_size = dsize;
	}

	if ( elp_crypto_srm_fini( ctx ) )
	{
		elp_mutex_unlock( ctx->hw_module->mlock );
		return CRYPTO_SRM_FAILED;
	}

	elp_mutex_unlock( ctx->hw_module->mlock );
	return CRYPTO_OK;
}


// [KYE1_0]
// [KYE1_1]
// [KYE1_2]
// [KYE1_3] <- AES128
// [KYE1_4]
// [KYE1_5] <- AES192
// [KYE1_6]
// [KYE1_7] <- AES256
// [RKEY_0]
// [RKEY_1]
// [RKEY_2]
// [RKEY_3]
// [RKEY_4]
// [RKEY_5]
// [RKEY_6]
// [RKEY_7] <- REVKEY
// [IV_0  ]
// [IV_1  ]
// [IV_2  ]
// [IV_3  ] <- IV
static int _aes_xxx_set_context (
	handle_ctx *ctx )
{
	U32 wlen = ( ctx->key_size >> 2 );

	MEMCPY32HTONL( ctx->pctx, ctx->key, wlen );
	if ( ctx->iv_size )
		MEMCPY32HTONL((U32 *) &ctx->pctx[ 16 ], ctx->iv,
			CRYPTO_AES_MIN_BLOCK_SIZE / 4 );
	PDUMPWORD(EDDUMP,ctx->pctx,ELPSEC_AES_CONTEXT_SIZE,"SET AES CONTEXT",0);
	return 0;
}


static int _aes_xxx_get_context (
	handle_ctx *ctx )
{
	if ( ctx->iv_size )
		MEMCPY32HTONL( ctx->iv, (U32 *) &ctx->pctx[ 16 ],
			CRYPTO_AES_MIN_BLOCK_SIZE / 4 );
	PDUMPWORD(EDDUMP,ctx->pctx,ELPSEC_AES_CONTEXT_SIZE,"GET AES CONTEXT",0);
	return 0;
}


int _aes_set_context (
	handle_ctx    *ctx,
	unsigned char *key,
	int            keysize,
	unsigned char *iv,
	int            ivsize )
{
	if ( ( keysize != 16 ) && ( keysize != 24 ) && ( keysize != 32 ) )
	{
		return CRYPTO_INVALID_KEY_SIZE;
	}

	ctx->first_use = 1;
	ctx->alg_par = 0;
	ctx->prev_data_size = 0;
	ctx->key_size = keysize;
	switch ( ctx->algmode )
	{
		case CRYPTO_MODE_AES_CBC:
			ctx->mode = ELPSEC_AES_CBC;
			ctx->iv_size  = CRYPTO_AES_MIN_BLOCK_SIZE;
			EMEMCPY( ctx->iv, iv, ctx->iv_size );
			EMEMCPY( ctx->key, key, ctx->key_size );
			break;
		case CRYPTO_MODE_AES_ECB:
			ctx->iv_size  = 0;
			ctx->mode = ELPSEC_AES_ECB;
			EMEMCPY( ctx->key, key, ctx->key_size );
			break;
		default:
			return CRYPTO_INVALID_ALG;
			break;
	}

	if ( keysize == 16 )
		ctx->mode |= ELPSEC_AES128;
	else if ( keysize == 24 )
		ctx->mode |= ELPSEC_AES192;
	else if ( keysize == 32 )
		ctx->mode |= ELPSEC_AES256;
	else
		return CRYPTO_INVALID_KEY_SIZE;

	return CRYPTO_OK;
}


int _aes_get_context (
	handle_ctx    *ctx,
	unsigned char *iv,
	int           *ivsize )
{
	switch ( ctx->algmode )
	{
		case CRYPTO_MODE_AES_ECB:
			// No Context for the ECB mode
			*ivsize = 0;
			break;
		case CRYPTO_MODE_AES_CBC:
			EMEMCPY( iv, ctx->iv, ctx->iv_size );
			*ivsize = ctx->iv_size;
			break;
		default:
			return CRYPTO_INVALID_ALG;
			break;
	}

	return CRYPTO_OK;
}
