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


static int get_handle_by_descriptor (int descr);

static volatile int _context_initialized = 0;
#if defined(ELPSEC_LINUX)
static elp_mutex context_lock;
#endif

static char __version__[] = "Elliptic Semiconductor (C). ELPCRYPTO V" VERSION;

char *
crypto_get_version (void)
{
	return __version__;
}


#if defined( ELPSEC_LINUX ) || defined( DEF_LINUX )
extern handle_ctx _rc4_mctx[CRYPTO_RC4_MAX_CONTEXTS + 1];
extern handle_ctx _aes_mctx[CRYPTO_AES_MAX_CONTEXTS + 1];
extern handle_ctx _des_mctx[CRYPTO_DES_MAX_CONTEXTS + 1];
extern handle_ctx _hmac_mctx[CRYPTO_HASH_MAX_CONTEXTS + 1];


extern crypto_module _rc4_ctx;
extern crypto_module _aes_ctx;
extern crypto_module _des_ctx;
extern crypto_module _hmac_ctx;
#endif

// Global debug flag used int printing macros
//unsigned int _pd_verbose=0;

// Function to set debug mask; caller
// must privide a complite bitmask of desired options
void
crypto_set_debug (unsigned int dflag)
{
	_pd_verbose = dflag;
}

// Global pool of crypto handles
// the handle is a unique number constructed by the
// hardware crypto module ID and index of a context
// so during look up we could quickly and safly locate
// corresponding data structure (crypto module)
// HANDLE 0 IS INVALID
// HANDLE = [MODULE_TYPE<<16][CONTEXT_INDEX]
static U32 _gchandles[CRYPTO_CONTEXTS_MAX];


// Initialize crypto context for all enabled
// hardware crypto modules.
// flags: specifies which modules should be enabled
// mmap:  start of the crypto hardware physical memory
// a unique handle is composed here during initialization
// it containes a crypto module's type ORed with a sequential index withing the
// maximum number contexts of a module
// and placed in the corresponding index of _gchandles
// Note that the PDU and PRNG do not have handles
int
crypto_init (int flags, U32 mmap)
{
	int i;
	int gh = 1;

	EMEMSET (_gchandles, 0, sizeof (_gchandles));
	elp_mutex_init (context_lock);

	// Initialize AES crypto module contexts
	if (flags & CRYPTO_MODULE_AES)
	{
		_aes_init (mmap);

		for (i = 0; i < CRYPTO_AES_MAX_CONTEXTS; i++)
		{
			_gchandles[gh++] = (U32) ((CRYPTO_MODULE_AES << 16) | i);
			_aes_mctx[i].taken = 0;
			_aes_mctx[i].index = i;
			_aes_mctx[i].hw_module = &_aes_ctx;
			_aes_mctx[i].ctx = (U32 *) (mmap + ELPSEC_HOST_MEMORY_START);
			_aes_mctx[i].mem = mmap;
		}
	}
	// Initialize RC4 crypto module contexts
	if (flags & CRYPTO_MODULE_RC4)
	{
		_rc4_init (mmap);

		for (i = 0; i < CRYPTO_RC4_MAX_CONTEXTS; i++)
		{
			_gchandles[gh++] = (U32) ((CRYPTO_MODULE_RC4 << 16) | i);
			_rc4_mctx[i].index = i;
			_rc4_mctx[i].hw_module = &_rc4_ctx;
			_rc4_mctx[i].taken = 0;
			_rc4_mctx[i].ctx = (U32 *) (mmap + ELPSEC_HOST_MEMORY_START);
			_rc4_mctx[i].mem = mmap;
		}
	}

	// Initialize DES crypto module contexts
	if (flags & CRYPTO_MODULE_DES)
	{
		_des_init (mmap);
		for (i = 0; i < CRYPTO_DES_MAX_CONTEXTS; i++)
		{
			_gchandles[gh++] = (U32) ((CRYPTO_MODULE_DES << 16) | i);
			_des_mctx[i].taken = 0;
			_des_mctx[i].ctx = (U32 *) (mmap + ELPSEC_HOST_MEMORY_START);
			_des_mctx[i].index = i;
			_des_mctx[i].hw_module = &_des_ctx;
			_des_mctx[i].mem = mmap;
		}
	}
	// Initialize HMAC crypto module contexts
	if (flags & CRYPTO_MODULE_HMAC)
	{
		_hmac_init (mmap);


		for (i = 0; i < CRYPTO_HASH_MAX_CONTEXTS; i++)
		{
#if 0
			_gchandles[gh++] = (U32) ((CRYPTO_MODULE_HMAC << 16) | i);
#else
			_gchandles[gh++] = (U32) ((CRYPTO_CONTEXT_HMAC << 16) | i);
#endif
			_hmac_mctx[i].taken = 0;
			_hmac_mctx[i].index = i;
			_hmac_mctx[i].hw_module = &_hmac_ctx;
			_hmac_mctx[i].ctx = (U32 *) (mmap + ELPSEC_HOST_MEMORY_START);
			_hmac_mctx[i].secret = (U32 *) (mmap + ELPSEC_HOST_MEMORY_START);
			_hmac_mctx[i].mem = mmap;
		}
	}

	_context_initialized = 1;
	return CRYPTO_OK;

}

// handle is an index into _gchandles array  which contains a composit number
// which breakes a handle into actual module type and index into module's array
handle_ctx *
context_lookup (U32 handle)
{
	int type, index, gh;
	crypto_module *ctx = 0;

	if (!_context_initialized)
		return NULL;

	if (handle <= 0 || handle > CRYPTO_CONTEXTS_MAX)
		return NULL;

	gh = _gchandles[handle];

	type = (gh >> 16) & 0x0000FFFF;
	index = gh & 0x0000FFFF;

	switch (type)
	{
	case CRYPTO_CONTEXT_RC4:
		ctx = &_rc4_ctx;
		break;
	case CRYPTO_CONTEXT_AES:
		ctx = &_aes_ctx;
		break;
	case CRYPTO_CONTEXT_DES:
		ctx = &_des_ctx;
		break;
	case CRYPTO_CONTEXT_HMAC:
		ctx = &_hmac_ctx;
		break;
		// Invalid crypto module type
	default:
		return NULL;
		break;
	}
	if (ctx->cookie != ELP_COOKIE)
	{
		PERROR ("context_lookup: Invalid or corrupted context memory.[%p]\n", ctx);
		return NULL;
	}

	// check if a cryto module has been activated and
	// an index actually is valid for a chosen crypto module context
	// Should we lock the context? probably not ...
	if (!ctx->active || index > ctx->max || !ctx->mctx[index].taken)
		return NULL;

	PDEBUG (EDCTX, "context_lookup: handle:%ld @ %p[%d].\n", handle, ctx, index);

	return &ctx->mctx[index];
}

int
crypto_status (int handle, int *size)
{

	// lookup checks everything
	handle_ctx *ctx = context_lookup (handle);
	if (!ctx)
		return CRYPTO_INVALID_HANDLE;

	// acquire context
	elp_mutex_lock (ctx->hw_module->mlock);

	switch (ctx->algmode)
	{
	case CRYPTO_MODE_RC4_40:
	case CRYPTO_MODE_RC4_128:
#ifdef USE_GLOBAL_STATUS
		if ((*ctx->hw_module->stat & ELPSEC_RC4_STATUS_DONE) == 0)
#else
		if ((*ctx->hw_module->stat & ELPSEC_STATUS_DONE) == 0)
#endif
		{
			if (*ctx->hw_module->stat == 0)
			{
				elp_mutex_unlock (ctx->hw_module->mlock);
				return CRYPTO_INPROGRESS;
			}
			else
			{
				U32 *pdata = (U32 *) ctx->pdata;
				U32 *pout = (U32 *) ctx->data_out;
				U32 sz = ctx->out_size >> 2;
				if (pout)
					MEMCPY32HTONL (pout, pdata, sz);
				if (size)
				{
					*size = ctx->out_size;
				}
			}
		}
		break;

	case CRYPTO_MODE_SHA1:
	case CRYPTO_MODE_SHA256:
	case CRYPTO_MODE_MD5:
	case CRYPTO_MODE_HMAC_SHA256:
	case CRYPTO_MODE_HMAC_SHA1:
	case CRYPTO_MODE_HMAC_MD5:
	case CRYPTO_MODE_SSLMAC_SHA1:
	case CRYPTO_MODE_SSLMAC_MD5:
	case CRYPTO_MODE_TLSMAC_SHA1:
	case CRYPTO_MODE_TLSMAC_MD5:
#ifdef USE_GLOBAL_STATUS
		if ((*ctx->hw_module->stat & ELPSEC_HASH_STATUS_DONE) == 0)
#else
		if ((*ctx->hw_module->stat & ELPSEC_STATUS_DONE) == 0)
#endif
		{
			if (*ctx->hw_module->stat == 0)
			{
				elp_mutex_unlock (ctx->hw_module->mlock);
				return CRYPTO_INPROGRESS;
			}
			else
			{
				U32 *pdata = (U32 *) ctx->pdata;
				U32 *pout = (U32 *) ctx->data_out;
				U32 sz = ctx->out_size >> 2;
				if (pout)
					MEMCPY32HTONL (pout, pdata, sz);


				if (size)
				{
					*size = ctx->out_size;
				}
			}
		}
		break;
	case CRYPTO_MODE_AES_CBC:
	case CRYPTO_MODE_AES_ECB:
#ifdef USE_GLOBAL_STATUS
		if ((*ctx->hw_module->stat & ELPSEC_AES_STATUS_DONE) == 0)
#else
		if ((*ctx->hw_module->stat & ELPSEC_STATUS_DONE) == 0)
#endif
		{
			elp_mutex_unlock (ctx->hw_module->mlock);
			return CRYPTO_INPROGRESS;
		}
		else
		{
			U32 *pdata = (U32 *) ctx->pdata;
			U32 *pout = (U32 *) ctx->data_out;
			U32 sz = ctx->out_size >> 2;
			MEMCPY32HTONL (pout, pdata, sz);

			if (size)
			{
				*size = ctx->out_size;
			}
		}
		break;
	case CRYPTO_MODE_3DES_CBC:
	case CRYPTO_MODE_3DES_ECB:
	case CRYPTO_MODE_DES_CBC:
	case CRYPTO_MODE_DES_ECB:
#ifdef USE_GLOBAL_STATUS
		if ((*ctx->hw_module->stat & ELPSEC_DES_STATUS_DONE) == 0)
#else
		if ((*ctx->hw_module->stat & ELPSEC_STATUS_DONE) == 0)
#endif
		{
			elp_mutex_unlock (ctx->hw_module->mlock);
			return CRYPTO_INPROGRESS;
		}
		else
		{
			U32 *pdata = (U32 *) ctx->pdata;
			U32 *pout = (U32 *) ctx->data_out;
			U32 sz = ctx->out_size >> 2;
			MEMCPY32HTONL (pout, pdata, sz);

			if (size)
			{
				*size = ctx->out_size;
			}
		}
		break;
	default:
		elp_mutex_unlock (ctx->hw_module->mlock);
		return CRYPTO_INVALID_ALG;
		break;
	}

	elp_mutex_unlock (ctx->hw_module->mlock);
	return CRYPTO_OK;
}

// Releases a crypto context back into appropriate module's pool
int
crypto_close (int handle)
{
	handle_ctx *ctx = context_lookup (handle);
	elp_mutex_lock (context_lock);
	if (ctx)
	{
		ctx->taken = 0;
		PDEBUG (EDCTX, "crypto_close: handle:%d [%d].\n", handle, ctx->index);
		elp_mutex_unlock (context_lock);
		return CRYPTO_OK;
	}
	elp_mutex_unlock (context_lock);
	return CRYPTO_INVALID_HANDLE;
}

// Allocates a handle for crypto module and initialize in with
// an appropriate type
// Added static variable to keep last opened context index
// that will make sure we exersize all available contexts for a particular
// module this feature added only for the sake of testing and could be removed
// if desired. Usually we run multiple operation for each mode so it does ensure
// that all contexts are exercised
int
crypto_open (int type, int mode)
{
	crypto_module *ctx = 0;
	int i, h;
	int context_index_start = (mode >> 16) & 0xF;

	mode &= ~(0xFF << 16);

	if (!_context_initialized)
		return CRYPTO_NOT_INITIALIZED;

	switch (type)
	{
	case CRYPTO_CONTEXT_AES:
		switch (mode)
		{
		case CRYPTO_MODE_AES_ECB:
		case CRYPTO_MODE_AES_CBC:
		case CRYPTO_MODE_AES_CTR:
			break;
		default:
			return CRYPTO_INVALID_MODE;
			break;
		}
		ctx = &_aes_ctx;
		break;
	case CRYPTO_CONTEXT_DES:
		switch (mode)
		{
		case CRYPTO_MODE_DES_ECB:
		case CRYPTO_MODE_DES_CBC:
		case CRYPTO_MODE_3DES_ECB:
		case CRYPTO_MODE_3DES_CBC:
			break;
		default:
			return CRYPTO_INVALID_MODE;
			break;
		}
		ctx = &_des_ctx;
		break;
	case CRYPTO_CONTEXT_HMAC:
		switch (mode)
		{
		case CRYPTO_MODE_HMAC_SHA1:
		case CRYPTO_MODE_HMAC_MD5:
		case CRYPTO_MODE_HMAC_SHA256:
		case CRYPTO_MODE_HMAC_SHA512:
		case CRYPTO_MODE_SHA256:
		case CRYPTO_MODE_SHA512:
		case CRYPTO_MODE_SHA1:
		case CRYPTO_MODE_MD5:
		case CRYPTO_MODE_TLSMAC_SHA1:
		case CRYPTO_MODE_TLSMAC_MD5:
		case CRYPTO_MODE_SSLMAC_SHA1:
		case CRYPTO_MODE_SSLMAC_MD5:
			break;
		default:
			return CRYPTO_INVALID_MODE;
			break;
		}
		ctx = &_hmac_ctx;
		break;
	case CRYPTO_CONTEXT_RC4:
		switch (mode)
		{
		case CRYPTO_MODE_RC4_40:
		case CRYPTO_MODE_RC4_128:
			break;
		default:
			return CRYPTO_INVALID_MODE;
			break;
		}
		ctx = &_rc4_ctx;
		break;
	default:
		return CRYPTO_INVALID_ALG;
		break;
	}

	elp_mutex_lock (context_lock);
	for (i = context_index_start; i < ctx->max; i++)
	{
		if (!ctx->mctx[i].taken)
		{
			ctx->mctx[i].taken = 1;
			ctx->mctx[i].first_use = 1;
			ctx->mctx[i].mode = mode;
			ctx->mctx[i].algmode = mode;
			h = get_handle_by_descriptor ((type << 16) | i);
			PDEBUG (EDCTX, "crypto_open: type:%d mode:%d handle:%d [ctx:%d].\n", type, mode, h, i);
//      context_index_start = (context_index_start+1) % ctx->max;
			elp_mutex_unlock (context_lock);
			return h;
		}

	}
	elp_mutex_unlock (context_lock);
	return CRYPTO_NO_MEM;

}

// finds an index (external handle) for a compound internal handle
static int
get_handle_by_descriptor (int descr)
{
	int i;

	for (i = 1; i < CRYPTO_CONTEXTS_MAX; i++)
	{
		if (_gchandles[i] == descr)
			return i;
	}

	return 0;  // invalid handle
}


// Universal function to initialize a crypto module with an appropreate context
// data which is actually depends on module functionality
// Note that RSA doe not have this feature
int
crypto_set_context (
	int handle,
	unsigned char *key,
	int ksize,
	unsigned char *iv,
	int ivsize,
	int psize )
{
	handle_ctx *ctx = context_lookup (handle);
	if (!ctx)
		return CRYPTO_INVALID_HANDLE;

	PDEBUG (EDCTX, "crypto_set_context: type:%d handle:%d [%d].\n", ctx->hw_module->type, handle, ctx->index);

	switch (ctx->hw_module->type)
	{
	case CRYPTO_CONTEXT_AES:
		return _aes_set_context (ctx, key, ksize, iv, ivsize);
		break;
	case CRYPTO_CONTEXT_DES:
		return _des_set_context (ctx, key, ksize, iv);
		break;
	case CRYPTO_CONTEXT_HMAC:
		return _hmac_set_context (ctx, key, ksize, iv, ivsize, psize);
		break;
	case CRYPTO_CONTEXT_RC4:
		return _rc4_set_context (ctx, key, ksize, iv, ivsize);
		break;
		// Invalid crypto module type
	default:
		return CRYPTO_NOT_IMPLEMENTED;
		break;
	}

	return CRYPTO_OK;
}


int
crypto_get_context (
	int handle,
	unsigned char *iv,
	int *ivsize,
	int *psize )
{
	handle_ctx *ctx = context_lookup (handle);
	if (!ctx)
		return CRYPTO_INVALID_HANDLE;

	if ((!iv) || (*ivsize < ctx->out_size))
		return CRYPTO_INVALID_ARGUMENT;

	PDEBUG (EDCTX, "crypto_get_context: type:%d handle:%d [%d].\n", ctx->hw_module->type, handle, ctx->index);

	switch (ctx->hw_module->type)
	{
	case CRYPTO_CONTEXT_AES:
		return _aes_get_context (ctx, iv, ivsize);
		break;
	case CRYPTO_CONTEXT_DES:
		return _des_get_context (ctx, iv, ivsize);
		break;
	case CRYPTO_CONTEXT_HMAC:
		return _hmac_get_context (ctx, iv, ivsize, psize);
		break;
	case CRYPTO_CONTEXT_RC4:
		return _rc4_get_context (ctx, iv, ivsize);
		break;
	default:
		return CRYPTO_NOT_IMPLEMENTED;
		break;
	}

	return CRYPTO_OK;
}

// Returns a user friendly error message for a correspponding error code
char *
crypto_error_msg (int err)
{
	switch (err)
	{
	case CRYPTO_OK:
		return "Operation has succeeded";
		break;
	case CRYPTO_FAILED:
		return "Operation has failed";
		break;
	case CRYPTO_INPROGRESS:
		return "Operation in progress";
		break;
	case CRYPTO_INVALID_HANDLE:
		return "Invalid handle";
		break;
	case CRYPTO_INVALID_CONTEXT:
		return "Invalid context";
		break;
	case CRYPTO_INVALID_SIZE:
		return "Invalid size";
		break;
	case CRYPTO_NOT_INITIALIZED:
		return "Crypto library has not been initialized";
		break;
	case CRYPTO_NO_MEM:
		return "No context memory";
		break;
	case CRYPTO_INVALID_ALG:
		return "Algorithm is not supported";
		break;
	case CRYPTO_INVALID_KEY_SIZE:
		return "Invalid key size";
		break;
	case CRYPTO_INVALID_ARGUMENT:
		return "Invalid argument";
		break;
	case CRYPTO_MODULE_DISABLED:
		return "Crypto module disabled";
		break;
	case CRYPTO_NOT_IMPLEMENTED:
		return "Function is not implemented";
		break;
	case CRYPTO_INVALID_BLOCK_ALIGNMENT:
		return "Invalid block alignment";
	case CRYPTO_INVALID_MODE:
		return "Invalid mode";
	case CRYPTO_INVALID_KEY:
		return "Invalid key";
	case CRYPTO_AUTHENTICATION_FAILED:
		return "Authentication failed";
	case CRYPTO_SRM_FAILED:
		return "Security Resource Manager failed";
	default:
		return "Invalid error code";
		break;
	}

	return "Invalid error code";
}
