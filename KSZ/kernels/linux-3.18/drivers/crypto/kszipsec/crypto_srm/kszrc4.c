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


handle_ctx _rc4_mctx[ CRYPTO_RC4_MAX_CONTEXTS + 1 ];
crypto_module _rc4_ctx;

int _rc4_init (
	U32 mmap )
{
	EMEMSET( &_rc4_mctx[ 0 ], 0, sizeof( _rc4_mctx ));
	EMEMSET( &_rc4_ctx, 0, sizeof( _rc4_ctx ));

	// Initialize RC4 crypto module contexts
	PDEBUG(EDINIT,"crypto_init: RC4 Contexts (%d) Initialization.\n",CRYPTO_RC4_MAX_CONTEXTS);
	PDEBUG(EDINIT,"crypto_init:\tdata=%X, ctx=%X, ctrl=%X, stat=%X\n"
		"\t\t\t\tkey=%X, src=%X, dst=%X, len=%X\n"
		"\t\t\t\tnmap @ 0x%lX\n\n",
		ELPSEC_RC4_DATA,
		ELPSEC_HOST_RC4_OFF + ELPSEC_RC4_CONTEXT,
		ELPSEC_HOST_RC4_OFF + ELPSEC_RC4_CTRL,
		ELPSEC_RC4_STATUS,
		ELPSEC_HOST_RC4_OFF + ELPSEC_RC4_KEY,
		ELPSEC_HOST_RC4_OFF + ELPSEC_RC4_SRC,
		ELPSEC_HOST_RC4_OFF + ELPSEC_RC4_DST,
		ELPSEC_HOST_RC4_OFF + ELPSEC_RC4_LEN,
		mmap);

	elp_mutex_init( _rc4_ctx.mlock );
	_rc4_ctx.cookie	= ELP_COOKIE;
	_rc4_ctx.active	= 1;
	_rc4_ctx.type	= CRYPTO_MODULE_RC4;
	_rc4_ctx.max	= CRYPTO_RC4_MAX_CONTEXTS;
	_rc4_ctx.mctx	= _rc4_mctx;
	_rc4_ctx.data_size = 0;
	_rc4_ctx.data	= (U32 *)(mmap + ELPSEC_HOST_MEMORY_START);
	_rc4_ctx.ctrl	= (U32 *)(mmap + ELPSEC_HOST_RC4_OFF + ELPSEC_RC4_CTRL);
	_rc4_ctx.key	= (U32 *)(mmap + ELPSEC_HOST_RC4_OFF + ELPSEC_RC4_KEY );
	_rc4_ctx.src	= (U32 *)(mmap + ELPSEC_HOST_RC4_OFF + ELPSEC_RC4_SRC);
	_rc4_ctx.dst	= (U32 *)(mmap + ELPSEC_HOST_RC4_OFF + ELPSEC_RC4_DST);
	_rc4_ctx.len	= (U32 *)(mmap + ELPSEC_HOST_RC4_OFF + ELPSEC_RC4_LEN);
#ifdef USE_GLOBAL_STATUS
	_rc4_ctx.stat	= (U32 *)(mmap + ELPSEC_GLOBAL_STATUS);
#else
	_rc4_ctx.stat	= (U32 *)(mmap + ELPSEC_HOST_RC4_OFF + ELPSEC_RC4_STATUS);
#endif

	return CRYPTO_OK;
}


int crypto_rc4_wait_ (
	int            handle,
	unsigned char *in_buf,
	int            in_size,
	unsigned char *out_buf,
	int           *out_size,
	int            wait )
{
	int dsize = 0;
	U32 mode;
	int wait_count = ELPSEC_LOOP_WAIT;
	handle_ctx *ctx;

	if ( ( in_buf == 0 ) || ( out_buf == 0 ) || ( out_size == 0 ) )
		return CRYPTO_INVALID_ARGUMENT;
	if ( ( *out_size ) < in_size )
		return CRYPTO_INVALID_ARGUMENT;

	ctx = context_lookup( handle );
	if (!ctx)
		return CRYPTO_INVALID_HANDLE;

	// acquire context
	elp_mutex_lock( ctx->hw_module->mlock );

	// srm allocate
	if ( elp_crypto_srm_setup( ctx, ELPSEC_HARDWARE_MEMORY_SIZE,
			CRYPTO_CONTEXT_RC4 ) )
	{
		elp_mutex_unlock( ctx->hw_module->mlock );
		return CRYPTO_SRM_FAILED;
	}

	// Alway load key
	MEMCPY32HTONL( ctx->secret, ctx->key, ctx->key_size / 4 );
	PDUMPWORD(EDRC4,ctx->secret,ctx->key_size,"RC4 KEY",0);

	if ( in_buf )
	{
		// Have to use 32 bit copy so align the data size
		dsize = ( in_size >> 2 );
		dsize += (in_size % 4 ) ? 1 : 0;
		MEMCPY32HTONL((U32 *) ctx->pdata, (U32 *) in_buf, dsize );
		PDUMPWORD(EDRC4,ctx->pdata,in_size,"RC4 INPUT",0);
	}

	mode = ctx->mode | ( ctx->context_index << ELPSEC_RC4_CTRL_PAGE );

	// for the first use generate context and encrypt
	// else just encrypt
	if ( ctx->first_use )
	{
		mode |= ELPSEC_RC4_CTRL_MODE_0;
	}
	else
	{
		mode |= ELPSEC_RC4_CTRL_MODE_1;

		// Load context from the temporary storage
		MEMCPY32( ctx->pctx, ctx->iv, ELPSEC_RC4_CONTEXT_WSIZE );
		PDUMPWORD(EDRC4,ctx->pctx, ELPSEC_RC4_CONTEXT_SIZE/4,"RC4 SET CONTEXT",0);
	}

	ctx->first_use = 0;

	*ctx->hw_module->len = in_size;

	// data is located at offset 0 always
	*ctx->hw_module->src = 0;
	*ctx->hw_module->dst = 0;
	*ctx->hw_module->ctrl = (mode);

// TOM: put wait=0 stuff in

#ifdef USE_GLOBAL_STATUS
	while ( wait_count &&
		( *ctx->hw_module->stat & ELPSEC_RC4_STATUS_DONE ) == 0 )
#else
	while ( wait_count &&
		( *ctx->hw_module->stat & ELPSEC_STATUS_DONE ) == 0 )
#endif
	{
		wait_count--;
	}

	PDEBUG(EDRC4,"RC4:%d: CTRL=0x%lX <-%lX [STAT=%lx][CNT:%d]\n",ctx->index,
		*ctx->hw_module->ctrl,mode,
		*ctx->hw_module->stat, wait_count);

#ifdef USE_GLOBAL_STATUS
	*ctx->hw_module->stat |= ELPSEC_RC4_STATUS_DONE;
#endif
	if ( !wait_count )
	{
		elp_mutex_unlock( ctx->hw_module->mlock );
		return CRYPTO_FAILED;
	}

	PDUMPWORD(EDRC4,ctx->pdata,in_size,"RC4 OUTPUT",0);
	// save context into the temporary storage
	MEMCPY32( ctx->iv, ctx->pctx, ELPSEC_RC4_CONTEXT_WSIZE );
	PDUMPWORD(EDRC4,ctx->pctx, ELPSEC_RC4_CONTEXT_SIZE/4,"RC4 GET CONTEXT",0);

	if ( out_size && out_buf )
	{
		MEMCPY32HTONL((U32 *) out_buf, ctx->pdata, dsize );
		*out_size = dsize << 2;
	}

	if ( elp_crypto_srm_fini( ctx ) )
	{
		elp_mutex_unlock( ctx->hw_module->mlock );
		return CRYPTO_SRM_FAILED;
	}

	elp_mutex_unlock( ctx->hw_module->mlock );
	return CRYPTO_OK;
}


// load key or a complete context which is pointed by iv
// context must be exactly 256 bytes
int _rc4_set_context (
	handle_ctx    *ctx,
	unsigned char *key,
	int            len,
	unsigned char *iv,
	int            ivsize )
{
	int wlen = ( len >> 2 ) + ( len % 4 ) ? 1 : 0;

	wlen = ( len >> 2 );
	wlen += ( len % 4 ) ? 1 : 0;

	ctx->first_use = 1;
	switch ( ctx->algmode )
	{
		case CRYPTO_MODE_RC4_40:
			ctx->mode = ELPSEC_RC4_CTRL_40;
			break;
		case CRYPTO_MODE_RC4_128:
			ctx->mode = ELPSEC_RC4_CTRL_128;
			break;
	}

	// acquire context
	elp_mutex_lock( ctx->hw_module->mlock );

	if ( key )
	{
		if ( len > ELPSEC_RC4_KEY_SIZE )
		{
			elp_mutex_unlock( ctx->hw_module->mlock );
			return CRYPTO_INVALID_KEY_SIZE;
		}

		// Have to use 32 bit copy so aling the data size
		// NOTE LOADING KEY IN BIG ENDIAN
		ctx->key_size = wlen * 4;
		EMEMCPY( ctx->key, key, ctx->key_size );
	}

	if ( iv )
	{
		if ( ivsize != ELPSEC_RC4_CONTEXT_SIZE )
		{
			elp_mutex_unlock( ctx->hw_module->mlock );
			return CRYPTO_INVALID_SIZE;
		}

		ctx->first_use = 0;
		ctx->iv_size = ELPSEC_RC4_CONTEXT_SIZE;
		EMEMCPY( ctx->iv, iv, ctx->iv_size );
	}

	elp_mutex_unlock( ctx->hw_module->mlock );
	return CRYPTO_OK;
}


// read complete context from the RC4 context memory
int _rc4_get_context (
	handle_ctx    *ctx,
	unsigned char *iv,
	int           *ivsize )
{
	// acquire context
	elp_mutex_lock( ctx->hw_module->mlock );

	if ( iv )
	{
		if ( *ivsize != ELPSEC_RC4_CONTEXT_SIZE )
		{
			elp_mutex_unlock( ctx->hw_module->mlock );
			return CRYPTO_INVALID_SIZE;
		}
		ctx->iv_size = ELPSEC_RC4_CONTEXT_SIZE;
		EMEMCPY( iv, ctx->iv, ctx->iv_size );
	}

	elp_mutex_unlock( ctx->hw_module->mlock );
	return CRYPTO_OK;
}
