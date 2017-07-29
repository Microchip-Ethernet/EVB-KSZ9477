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


handle_ctx _des_mctx[ CRYPTO_DES_MAX_CONTEXTS + 1 ];
crypto_module _des_ctx;

static int _des_xxx_set_context(handle_ctx *ctxp);
static int _des_xxx_get_context(handle_ctx *ctxp);

int _des_init (
	U32 mmap )
{
	EMEMSET( &_des_mctx[ 0 ], 0, sizeof( _des_mctx ));
	EMEMSET( &_des_ctx, 0, sizeof( _des_ctx ));

	PDEBUG(EDINIT,"crypto_init: DES Contexts (%d) Initialization.\n",CRYPTO_DES_MAX_CONTEXTS);
	PDEBUG(EDINIT,"crypto_init:\tdata=%X, ctx=%X, ctrl=%X, stat=%X\n"
		"\t\t\t\tnmap @ 0x%lX, ctx @ %p\n\n",
		ELPSEC_DES_DATA,
		ELPSEC_HOST_DES_OFF + ELPSEC_DES_CONTEXT,
		ELPSEC_HOST_DES_OFF + ELPSEC_DES_CTRL,
		ELPSEC_HOST_DES_OFF + ELPSEC_DES_STATUS,
		mmap,&_des_ctx);

	elp_mutex_init( _des_ctx.mlock );
	_des_ctx.cookie = ELP_COOKIE;
	_des_ctx.active = 1;
	_des_ctx.type	= CRYPTO_MODULE_DES;
	_des_ctx.max	= CRYPTO_DES_MAX_CONTEXTS;
	_des_ctx.mctx	= _des_mctx;
	_des_ctx.data	= (U32 *)(mmap + ELPSEC_HOST_MEMORY_START);
	_des_ctx.ctrl	= (U32 *)(mmap + ELPSEC_HOST_DES_OFF + ELPSEC_DES_CTRL);
#ifdef USE_GLOBAL_STATUS
	_des_ctx.stat	= (U32 *)(mmap + ELPSEC_GLOBAL_STATUS);
#else
	_des_ctx.stat	= (U32 *)(mmap + ELPSEC_HOST_DES_OFF + ELPSEC_DES_STATUS);
#endif

	return CRYPTO_OK;
}


int crypto_des_wait_ (
	int            handle,
	int            decrypt,
	unsigned char *in_buf,
	int            in_size,
	unsigned char *out_buf,
	int           *out_size,
	int            wait )
{
	U32 mode, blocks;
	int wait_count = ELPSEC_LOOP_WAIT;
	handle_ctx *ctx = context_lookup( handle );

	if ( ( decrypt != ENCRYPT ) && ( decrypt != DECRYPT ) )
		return CRYPTO_INVALID_ARGUMENT;
	if ( ( in_buf == 0 ) || ( out_buf == 0 ) || ( out_size == 0 ) )
		return CRYPTO_INVALID_ARGUMENT;
	if ( in_size < CRYPTO_DES_MIN_BLOCK_SIZE )
		return CRYPTO_INVALID_ARGUMENT;
	if ( ( in_size % CRYPTO_DES_MIN_BLOCK_SIZE ) != 0 )
		return CRYPTO_INVALID_BLOCK_ALIGNMENT;
	if ( ( *out_size ) < in_size )
		return CRYPTO_INVALID_ARGUMENT;

	if ( !ctx )
		return CRYPTO_INVALID_HANDLE;

	// acquire context
	elp_mutex_lock( ctx->hw_module->mlock );

	// srm allocate
	if ( elp_crypto_srm_setup( ctx, ELPSEC_HARDWARE_MEMORY_SIZE,
			CRYPTO_CONTEXT_DES ) )
	{
		elp_mutex_unlock( ctx->hw_module->mlock );
		return CRYPTO_SRM_FAILED;
	}
	_des_xxx_set_context( ctx );

	MEMCPY32HTONL( ctx->pdata, (U32 *)in_buf, in_size >> 2 );

	PDUMPWORD(EDDUMP,ctx->pdata,in_size,"SECTOE: DES INPUT",0);
	PDUMPWORD(EDDUMP,ctx->pctx,ELPSEC_DES_CONTEXT_SIZE,"SECTOE: DES CTX ",0);

	// first calculate a number of 16 byte blocks
	blocks = in_size >> 3;  // len/ELPSEC_DES_BLOCK_PAGE_SIZE

	mode = ctx->mode;
	mode |= decrypt ? 0 : ELPSEC_DES_ENCRYPT;
	mode |= ( 1 << TOE_DES_CP_CNTRL_BIT_RET_IV ) |
		( 1 << TOE_DES_CP_CNTRL_BIT_STR_IV ) |
		( 1 << TOE_DES_CP_CNTRL_BIT_RET_KEY ) |
		( ctx->context_index << TOE_DES_CP_CNTRL_BIT_IV_IDX_LO ) |
		( blocks << TOE_DES_CP_CNTRL_BIT_N_BLKS_LO );

	*ctx->hw_module->ctrl = (mode);

#ifdef USE_GLOBAL_STATUS
	if ( !wait &&
		( *ctx->hw_module->stat & ELPSEC_DES_STATUS_DONE ) == 0 )
#else
	if ( !wait &&
		( *ctx->hw_module->stat & ELPSEC_STATUS_DONE ) == 0 )
#endif
	{
		ctx->out_size = in_size;
		ctx->data_out  = out_buf;
		elp_mutex_unlock( ctx->hw_module->mlock );
		return CRYPTO_INPROGRESS;
	}

	PDEBUG(EDDES,"DES CTRL=0x%lX [%lx] [I:%d]\n",*ctx->hw_module->ctrl,*ctx->hw_module->stat, ctx->index);

#ifdef USE_GLOBAL_STATUS
	while ( wait_count &&
		( *ctx->hw_module->stat & ELPSEC_DES_STATUS_DONE ) == 0 )
#else
	while ( wait_count &&
		( *ctx->hw_module->stat & ELPSEC_STATUS_DONE ) == 0 )
#endif
	{
		wait_count--;
	}

	PDEBUG(EDDES,"DES CTRL=0x%lX [%lx] [w:%d]\n",*ctx->hw_module->ctrl,*ctx->hw_module->stat,wait_count);

#ifdef USE_GLOBAL_STATUS
	*ctx->hw_module->stat |= ELPSEC_DES_STATUS_DONE;
#endif
	if ( !wait_count )
	{
		PINFO("DES FAILED: CTRL=0x%lX [%lx] [I:%d]\n",*ctx->hw_module->ctrl, *ctx->hw_module->stat, ctx->index);
		elp_mutex_unlock( ctx->hw_module->mlock );
		return CRYPTO_FAILED;
	}

//	PDUMPWORD(EDDUMP,ctx->ctx,ELPSEC_DES_CONTEXT_SIZE,"SECTOE: DES CTX ",0);
	PDUMPWORD(EDDUMP,ctx->pdata,in_size,"SECTOE: DES OUTPUT",0);

	_des_xxx_get_context( ctx );
	if ( out_size && out_buf )
	{
		MEMCPY32HTONL(( U32* ) out_buf, ( U32* ) ctx->pdata,
			in_size >> 2 );
		*out_size = in_size;
	}

	if ( elp_crypto_srm_fini( ctx ) )
	{
		elp_mutex_unlock( ctx->hw_module->mlock );
		return CRYPTO_SRM_FAILED;
	}

	elp_mutex_unlock( ctx->hw_module->mlock );
	return CRYPTO_OK;
}


static int _des_xxx_set_context (
	handle_ctx *ctx )
{
	if ( ctx->iv_size )
		MEMCPY32HTONL( ctx->pctx, ctx->iv, 2 ); // iv = 8 bytes
	MEMCPY32HTONL((U32 *) &ctx->pctx[ 2 ], ctx->key, ctx->key_size );

	PDUMPWORD(EDDUMP,ctx->pctx,ctx->key_size*4 ,"ELPSEC: DES CONTEXT ",0);
	return 0;
}


static int _des_xxx_get_context (
	handle_ctx *ctx )
{
	if ( ctx->iv_size )
		MEMCPY32HTONL( ctx->iv, ctx->pctx,  2 ); // iv = 8 bytes
	return 0;
}


int _des_set_context (
	handle_ctx    *ctx,
	unsigned char *key,
	int            keysize,
	unsigned char *iv )
{
	switch ( ctx->algmode )
	{
		case CRYPTO_MODE_3DES_CBC:
			ctx->mode = ELPSEC_3DES_CBC;
			ctx->key_size = CRYPTO_3DES_KEY_SIZE_BYTES;
			ctx->iv_size = CRYPTO_DES_MIN_BLOCK_SIZE;
			EMEMCPY( ctx->key, key, ctx->key_size );
			EMEMCPY( ctx->iv, iv, ctx->iv_size );
			break;
		case CRYPTO_MODE_3DES_ECB:
			ctx->mode = ELPSEC_3DES_ECB;
			ctx->key_size = CRYPTO_3DES_KEY_SIZE_BYTES;
			ctx->iv_size = 0;
			EMEMCPY( ctx->key, key, ctx->key_size );
			break;
		case CRYPTO_MODE_DES_CBC:
			ctx->mode = ELPSEC_DES_CBC;
			ctx->key_size = CRYPTO_DES_KEY_SIZE_BYTES;
			ctx->iv_size = CRYPTO_DES_MIN_BLOCK_SIZE;
			EMEMCPY( ctx->key, key, ctx->key_size );
			EMEMCPY( ctx->iv, iv, ctx->iv_size );
			break;
		case CRYPTO_MODE_DES_ECB:
			ctx->mode = ELPSEC_DES_ECB;
			ctx->key_size = CRYPTO_DES_KEY_SIZE_BYTES;
			ctx->iv_size = 0;
			EMEMCPY( ctx->key, key, ctx->key_size );
			break;
		default:
			return CRYPTO_INVALID_ALG;
			break;
	}

	return CRYPTO_OK;
}


int _des_get_context (
	handle_ctx    *ctx,
	unsigned char *iv,
	int           *ivsize )
{
	switch ( ctx->algmode )
	{
		case CRYPTO_MODE_3DES_ECB:
			// No Context for the ECB mode
			*ivsize = 0;
			break;
		case CRYPTO_MODE_3DES_CBC:
			EMEMCPY( iv, ctx->iv, ctx->iv_size );
			*ivsize = ctx->iv_size;
			break;
		case CRYPTO_MODE_DES_ECB:
			// No Context for the ECB mode
			*ivsize = 0;
			break;
		case CRYPTO_MODE_DES_CBC:
			EMEMCPY( iv, ctx->iv, ctx->iv_size );
			*ivsize = ctx->iv_size;
			break;
		default:
			return CRYPTO_INVALID_ALG;
			break;
	}

	return CRYPTO_OK;
}
