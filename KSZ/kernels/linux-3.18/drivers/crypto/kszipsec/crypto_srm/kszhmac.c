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


#ifndef DEF_KSZ
#define  CRYPTO_HW_DUMP 1
#endif

handle_ctx _hmac_mctx[ CRYPTO_HASH_MAX_CONTEXTS + 1 ];
crypto_module _hmac_ctx;

int _hmac_init (
	U32 mmap )
{
	EMEMSET( &_hmac_mctx[ 0 ], 0, sizeof( _hmac_mctx ));
	EMEMSET( &_hmac_ctx, 0, sizeof( _hmac_ctx ));

	// Initialize HMAC crypto module contexts
	PDEBUG(EDINIT,"crypto_init: HMAC Contexts (%d) Initialization.\n",CRYPTO_HASH_MAX_CONTEXTS);
	PDEBUG(EDINIT,"crypto_init:\tdata=%X, ctx=%X, ctrl=%X, stat=%X, secret=%X\n"
		"\t\t\t\tctrl1=%X, ctrl2=%X, ctrl3=%X, seqn=%X\n"
		"\t\t\t\tnmap @ 0x%lX, ctx @ %p\n\n",
		ELPSEC_HASH_DATA,
		ELPSEC_HOST_HASH_OFF + ELPSEC_HASH_CONTEXT,
		ELPSEC_HOST_HASH_OFF + ELPSEC_HASH_CTRL,
		ELPSEC_HOST_HASH_OFF + ELPSEC_HASH_STATUS,
		ELPSEC_HASH_SECRET,
		ELPSEC_HOST_HASH_OFF + ELPSEC_HASH_CTRL1,
		ELPSEC_HOST_HASH_OFF + ELPSEC_HASH_CTRL2,
		ELPSEC_HOST_HASH_OFF + ELPSEC_HASH_CTRL3,
		ELPSEC_HOST_HASH_OFF + ELPSEC_HASH_SEQN,
		mmap,&_hmac_ctx);

	_hmac_ctx.cookie = ELP_COOKIE;
	_hmac_ctx.active = 1;
#if 0
	_hmac_ctx.type	= CRYPTO_MODULE_HMAC;
#else
	_hmac_ctx.type	= CRYPTO_CONTEXT_HMAC;
#endif
	_hmac_ctx.max	= CRYPTO_HASH_MAX_CONTEXTS;
	_hmac_ctx.mctx	= _hmac_mctx;
	_hmac_ctx.data_size = 0;
	_hmac_ctx.data	= (U32 *)(mmap + ELPSEC_HOST_MEMORY_START);
	_hmac_ctx.ctrl	= (U32 *)(mmap + ELPSEC_HOST_HASH_OFF + ELPSEC_HASH_CTRL);
	_hmac_ctx.ctrl1	= (U32 *)(mmap + ELPSEC_HOST_HASH_OFF + ELPSEC_HASH_CTRL1);
	_hmac_ctx.ctrl2	= (U32 *)(mmap + ELPSEC_HOST_HASH_OFF + ELPSEC_HASH_CTRL2);
	_hmac_ctx.ctrl3	= (U32 *)(mmap + ELPSEC_HOST_HASH_OFF + ELPSEC_HASH_CTRL3);
	_hmac_ctx.ctrl4	= (U32 *)(mmap + ELPSEC_HASH_SECRET);
	_hmac_ctx.ctrl5	= (U32 *)(mmap + ELPSEC_HOST_HASH_OFF + ELPSEC_HASH_SEQN);
	_hmac_ctx.stat	= (U32 *)(mmap + ELPSEC_HASH_STATUS);

	return CRYPTO_OK;
}


static int _hmac_xxx_get_context (
        handle_ctx *ctx )
{
	int i;
	U32 *piv = (U32 *)ctx->iv;

	ctx->iv_size = ctx->key_size;

	// WARNING
	// The hmac context is spaced by one word
	//MEMCPY32HTONL(ctx->iv,pctx,  ctx->iv_size/4);
	for ( i = 0; i <= ctx->iv_size / 2; i += 2 )
		*piv++ = ctx->pctx[ i ];

	return 0;
}


// NOTE: len to be expected
// MD5  16
// SHA1 20
int _hmac_set_context (
	handle_ctx    *ctx,
	unsigned char *key,
	int            keysize,
	unsigned char *iv,
	int            ivsize,
	int            psize )
{
	if ( psize )
	{
		ctx->first_use = 0;
	}

	switch ( ctx->algmode )
	{
		case CRYPTO_MODE_MD5:
			ctx->key_size = CRYPTO_HASH_MD5_SIZE;
			ctx->mode = ELPSEC_HASH_MD5;
			ctx->prev_data_size = 0;
			return CRYPTO_OK;
			break;
		case CRYPTO_MODE_SHA256:
			ctx->key_size = CRYPTO_HASH_SHA256_SIZE;
			ctx->mode = ELPSEC_HASH_SHA256;
			ctx->prev_data_size = 0;
			return CRYPTO_OK;
			break;
		case CRYPTO_MODE_SHA512:
			ctx->key_size = CRYPTO_HASH_SHA512_SIZE;
			ctx->mode = ELPSEC_HASH_SHA512;
			ctx->prev_data_size = 0;
			return CRYPTO_OK;
			break;
		case CRYPTO_MODE_SHA1:
			ctx->key_size = CRYPTO_HASH_SHA1_SIZE;
			ctx->mode = ELPSEC_HASH_SHA1;
			ctx->prev_data_size = 0;
			return CRYPTO_OK;
			break;
		case CRYPTO_MODE_TLSMAC_MD5:
		case CRYPTO_MODE_HMAC_MD5:
			ctx->key_size = CRYPTO_HASH_MD5_SIZE;
			ctx->mode = ELPSEC_HASH_MD5 | ELPSEC_HASH_HMAC;
			keysize = ctx->key_size;
			break;
		case CRYPTO_MODE_HMAC_SHA512:
			ctx->key_size = CRYPTO_HASH_SHA512_SIZE;
			ctx->mode = ELPSEC_HASH_SHA512 | ELPSEC_HASH_HMAC;
			break;
		case CRYPTO_MODE_HMAC_SHA256:
			ctx->key_size = CRYPTO_HASH_SHA256_SIZE;
			ctx->mode = ELPSEC_HASH_SHA256 | ELPSEC_HASH_HMAC;
			break;
		case CRYPTO_MODE_TLSMAC_SHA1:
		case CRYPTO_MODE_HMAC_SHA1:
			ctx->key_size = CRYPTO_HASH_SHA1_SIZE;
			ctx->mode = ELPSEC_HASH_SHA1 | ELPSEC_HASH_HMAC;
			keysize = ctx->key_size;
			break;
		case CRYPTO_MODE_SSLMAC_SHA1:
			ctx->key_size = CRYPTO_HASH_SHA1_SIZE;
			ctx->mode = ELPSEC_HASH_SHA1 | ELPSEC_HASH_HMAC |
				ELPSEC_HASH_SSLMAC;
			keysize = ctx->key_size;
			break;
		case CRYPTO_MODE_SSLMAC_MD5:
			ctx->key_size = CRYPTO_HASH_MD5_SIZE;
			ctx->mode = ELPSEC_HASH_MD5 | ELPSEC_HASH_HMAC |
				ELPSEC_HASH_SSLMAC;
			keysize = ctx->key_size;
			break;
		default:
			return CRYPTO_INVALID_ALG;
			break;
	}

#ifdef CRYPTO_HW_DUMP
	PDUMPWORD(EDDUMP,(U32 *)key,keysize,"SECTOE: SECRET",0);
#endif
  
	// If an iv has been specified then it should be used instead of
	// preset on
	if ( iv )
	{
		ctx->preset_iv = 0;
		ctx->iv_size = keysize;
		EMEMCPY( ctx->iv, iv, ctx->iv_size );
	}
	else
		ctx->preset_iv = 1;

	ctx->prev_data_size = psize;
	EMEMCPY( ctx->key, key, ctx->key_size );

	return CRYPTO_OK;
}


/*
The following are correct rules of using HMAC authentication for a multiple chunks of data:
1.	If both out_buf and in_buf buffers are specified then the HMAC function
    authenticate the data in the in_buf and places a result in the out_buf.
2.	If only the in_buf is provided then the HMAC function authenticates
    the data in the in_buf and expects more data to be followed.
3.	If only the out_buf is provided then the HMAC function considers
    it as a final call and retrieves a result digest and stores it in the out_buf location.
*/
int crypto_hmac_wait_ (
	int            handle,
	unsigned char *in_buf,
	int            in_size,
	unsigned char *out_buf,
	int           *out_size,
	int            wait )
{
	U32 mode;
	U32 total = 0;
	int data_size = 0;
	int wait_count = ELPSEC_LOOP_WAIT;

	handle_ctx *ctx = context_lookup( handle );

	if ( !ctx )
		return CRYPTO_INVALID_HANDLE;

	if ( in_size > CRYPTO_MAX_BLOCK_SIZE )
		return CRYPTO_INVALID_ARGUMENT;

	if ( out_size && (( *out_size ) < ctx->key_size ) )
	{
		return CRYPTO_INVALID_ARGUMENT;
	}

	// NOTE: alignment for SHA512 is 128 bytes not 64
	if ( !out_size &&
			( in_size % ((( ctx->mode & ELPSEC_HASH_SHA512 ) ==
			ELPSEC_HASH_SHA512 ) ? 128 : CRYPTO_HASH_ALIGNMENT ))
			!= 0 )
		return CRYPTO_INVALID_BLOCK_ALIGNMENT;

	// acquire context
	elp_mutex_lock( ctx->hw_module->mlock );

	mode = ctx->mode | ELPSEC_HASH_STR_2CTX | ELPSEC_HASH_STR_2MSG;

	// srm allocate
	if ( elp_crypto_srm_setup( ctx, ELPSEC_HARDWARE_MEMORY_SIZE,
			CRYPTO_CONTEXT_HMAC ) )
	{
		elp_mutex_unlock( ctx->hw_module->mlock );
		return CRYPTO_SRM_FAILED;
	}

	// If a in_buf has not been specified then this call is just to
	// retrieve the result
	if ( in_buf )
	{
		MEMCPY32HTONL( ctx->secret, (U32 *) ctx->key,
			ctx->key_size >> 2 );

		if ( ctx->iv_size )
			MEMCPY32HTONL( ctx->pctx, (U32 *) ctx->iv,
				ctx->iv_size >> 2 );

		MEMCPY32HTONL((U32 *) ctx->pdata, (U32 *) in_buf,
			( in_size >> 2 ) + 1 );
		ctx->prev_data_size += in_size;

		// final block
		if ( out_buf )
		{
			total = ctx->prev_data_size;
			mode |= ELPSEC_HASH_MSG_END;
		}

#ifdef CRYPTO_HW_DUMP
		PDUMPWORD(EDDUMP,(U32 *)ctx->pdata,in_size,"HASH INPUT",0);
		PDUMPWORD(EDDUMP,(U32 *)ctx->secret,ctx->key_size,"HASH SECRET",0);
#endif

		// on the very first call set appropriate flags
		// which are the start of the message and use predefined IV
		if ( ctx->first_use )
			mode |= ELPSEC_HASH_MSG_BEGIN;

		ctx->first_use = 0;

		*ctx->hw_module->ctrl1 = 0;
		*ctx->hw_module->ctrl3 = 0;
		// NOTE:  Store context index number?
		*ctx->hw_module->ctrl2 = ctx->context_index << TOE_HASH_CTRL2_CTX_IDX;
		*ctx->hw_module->ctrl1 = ELPSEC_HASH_MSG_TOTAL( total ) |
			ELPSEC_HASH_MSG_SIZE( in_size );
		*ctx->hw_module->ctrl3 =
			ELPSEC_HASH_SECRET_SIZE( ctx->key_size ) |
			ELPSEC_HASH_SECRET_ADDR((
			ELPSEC_HASH_BLOCK_PAGE_SIZE * ctx->context_index ));

		*ctx->hw_module->ctrl = (mode);

		if ( !wait && (( *ctx->hw_module->stat &
				ELPSEC_HASH_STATUS_DONE) == 0 ) )
		{
			ctx->out_size = ctx->key_size;
			ctx->data_out  = out_buf;

			elp_mutex_unlock( ctx->hw_module->mlock );
			return CRYPTO_INPROGRESS;
		}

		PDEBUG(EDHASH,"HMAC CTRL=0x%lX [%lx] [I:%d]\n",*ctx->hw_module->ctrl,*ctx->hw_module->stat, ctx->index);
		while ( wait_count &&
				( *ctx->hw_module->stat &
				ELPSEC_HASH_STATUS_DONE ) ==0 )
		{
			wait_count--;
		}

		PDEBUG(EDHASH,"HMAC CTRL=0x%lX [%lx] [w:%d]\n",*ctx->hw_module->ctrl,*ctx->hw_module->stat,wait_count);
		PDEBUG(EDHASH,"HMAC CTRL1=0x%lX CTRL2=0x%lX CTRL3=0x%lX CTRL4=0x%lX SEQN=0x%lX \n",
			*ctx->hw_module->ctrl1,*ctx->hw_module->ctrl2,*ctx->hw_module->ctrl3,
			*ctx->hw_module->ctrl4,*ctx->hw_module->ctrl5);

		*ctx->hw_module->stat |= ELPSEC_HASH_STATUS_DONE;

		if ( !wait_count )
		{
			PINFO("HMAC FAILED: CTRL=0x%lX [%lx] [w:%d]\n",*ctx->hw_module->ctrl,*ctx->hw_module->stat,wait_count);
			PINFO("HMAC FAILED: CTRL1=0x%lX CTRL2=0x%lX CTRL3=0x%lX CTRL4=0x%lX SEQN=0x%lX \n",
				*ctx->hw_module->ctrl1,*ctx->hw_module->ctrl2,*ctx->hw_module->ctrl3,
				*ctx->hw_module->ctrl4,*ctx->hw_module->ctrl5);
			elp_mutex_unlock( ctx->hw_module->mlock );
			return CRYPTO_FAILED;
		}

		switch ( ctx->algmode )
		{
			case CRYPTO_MODE_MD5:
			case CRYPTO_MODE_SHA1:
			case CRYPTO_MODE_SHA256:
			case CRYPTO_MODE_SHA512:
			case CRYPTO_MODE_HMAC_MD5:
			case CRYPTO_MODE_HMAC_SHA1:
			case CRYPTO_MODE_HMAC_SHA256:
			case CRYPTO_MODE_HMAC_SHA512:
				data_size = ctx->key_size;
				break;
			default:
				data_size = ctx->key_size;
				break;
		}
#ifdef CRYPTO_HW_DUMP
		PDUMPWORD(EDDUMP,(U32 *)ctx->pctx,data_size,"CONTEXT 0",0);
		PDUMPWORD(EDDUMP,(U32 *)ctx->pdata, data_size, "MSG CONTEXT", 0);
#endif
	} // ??? this should be further up

	_hmac_xxx_get_context( ctx );

	MEMCPY32HTONL((U32 *) ctx->iv, ctx->pctx, ctx->iv_size >> 2 );

	if ( out_buf )
	{
		MEMCPY32HTONL(( U32* ) out_buf, ( U32* ) ctx->pdata,
			data_size >> 2 );
		if ( !out_size )
		{
			elp_mutex_unlock( ctx->hw_module->mlock );
			return CRYPTO_INVALID_ARGUMENT;
		}
		*out_size = data_size;
	}

	if ( elp_crypto_srm_fini( ctx ) )
	{
		elp_mutex_unlock( ctx->hw_module->mlock );
		return CRYPTO_SRM_FAILED;
	}
	elp_mutex_unlock( ctx->hw_module->mlock );
	return CRYPTO_OK;
}


int _hmac_get_context (
	handle_ctx    *ctx,
	unsigned char *iv,
	int           *ivsize,
	int           *psize )
{
	switch ( ctx->algmode )
	{
		case CRYPTO_MODE_HMAC_SHA1:
			*ivsize = CRYPTO_HASH_SHA1_SIZE;
			break;
		case CRYPTO_MODE_HMAC_MD5:
			*ivsize = CRYPTO_HASH_MD5_SIZE;
			break;
		default:
			return CRYPTO_INVALID_ALG;
			break;
	}

	EMEMCPY( iv, ctx->iv, ctx->iv_size );
	*psize = ctx->iv_size;

	return CRYPTO_OK;
}


int _ssl_mac (
	int            handle,
	unsigned char  protocol,
	int            seq_num,
	unsigned char *mac_sec,
	unsigned char *input,
	int            length,
	unsigned char *md,
	int            mdsz )
{
	int res, clen, phdr_len, loff;
	unsigned char *out,*pseq;
	int len = mdsz;
	int *plen = &len;
	unsigned char buf[128];

	handle_ctx *ctx = context_lookup( handle );
	if ( !ctx )
		return CRYPTO_INVALID_HANDLE;

	res = crypto_set_context( handle, mac_sec, 0, 0, 0, 0 );
	if ( res < 0 )
	{
		return res;
	}

	len = ctx->key_size;
	EMEMSET( buf, 0, sizeof( buf ));

	// FIRST STAGE
	// First hmac 64 byte chunk of pseudo header (SSL 12 ir TLS 14) plus whatever bytes of message
	// if the complete message is less that that then do it in one shot

	switch ( ctx->algmode )
	{
		case CRYPTO_MODE_TLSMAC_SHA1:
		case CRYPTO_MODE_TLSMAC_MD5:
			phdr_len = 13;
			pseq = &buf[ 4 ];
			CRYPTO_NUM2STR( seq_num, pseq );
			buf[ 8 ] = protocol;
			buf[ 9 ] = CRYPTO_TLS1_VERSION_MAJOR;
			buf[ 10 ] = CRYPTO_TLS1_VERSION_MINOR;
			buf[ 11 ] = length >> 8;
			buf[ 12 ] = length & 0xff;
			break;
		case CRYPTO_MODE_SSLMAC_MD5:
			phdr_len = 11;
			pseq = &buf[ 4 ];
			CRYPTO_NUM2STR( seq_num, pseq );
			buf[ phdr_len - 3 ] = protocol;
			buf[ phdr_len - 2 ] = length >> 8;
			buf[ phdr_len - 1 ] = length & 0xff;
			break;
		case CRYPTO_MODE_SSLMAC_SHA1:
			*ctx->hw_module->ctrl5 = 0;
			phdr_len = 7;
			pseq = &buf[ 0 ];
			CRYPTO_NUM2STR( seq_num, pseq );
			buf[ phdr_len - 3 ] = protocol;
			buf[ phdr_len - 2 ] = length >> 8;
			buf[ phdr_len - 1 ] = length & 0xff;
			break;
		default:
			return CRYPTO_INVALID_ALG;
			break;
	}

	if ( length > ( 64 - phdr_len ) )
	{
		clen = 64;
		loff = ( 64 - phdr_len );
		length -= ( 64 - phdr_len );
		plen = 0;
		out = 0;
	}
	else
	{
		clen = length + phdr_len;
		loff = 0;
		length = 0;
		plen = &len;
		out = md;
	}

	EMEMCPY((char *) &buf[ phdr_len ], input, clen );
	res = crypto_hmac_wait_( handle, buf, clen, out, plen, 1 );
	if ( res < 0 )
	{
		return res;
	}

	while ( length )
	{
		if ( length > 2048 )
		{
			length -= 2048;
			clen 	= 2048;
			plen 	= 0;
			out 	= 0;
		}
		else
		{
			clen 	= length;
			length 	= 0;
			len 	= ctx->key_size;
			plen 	= &len;
			out 	= md;
		}
		res = crypto_hmac_wait_( handle, &input[ loff ], clen, out,
			plen, 1 );
		if ( res < 0 )
		{
			return res;
		}

		loff += length;
	}

	return( len );
}
