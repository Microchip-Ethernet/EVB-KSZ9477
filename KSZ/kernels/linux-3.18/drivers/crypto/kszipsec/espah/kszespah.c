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
//   ELPISECPDU
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
#ifdef DEF_LINUX
#include <linux/kernel.h>
#include <linux/module.h>
#include <asm/memory.h>
#endif

#include "elpipsec.h"
#include "elpipsechw.h"
#endif


static char __espah_version__[] = "Elliptic Semiconductor (C). ESPAH V" VERSION " <"HWVERSION">";

espah_module _espah_module;
espah_handle _espah_handle[ESPAH_HANDLES_MAX + 1];

static int espah_context_initialized = 0;
#if defined(ELPSEC_LINUX)
static elp_mutex espah_context_lock;
#endif

// Global debug flag used int printing macros
unsigned int _pd_verbose = 0;

char *
espah_get_version (void)
{
	return __espah_version__;
}


// Function to set debug mask; caller
// must privide a complite bitmask of desired options
void espah_set_debug (unsigned int dflag)
{
	_pd_verbose = dflag;
}

unsigned int espah_get_debug (void)
{
	return _pd_verbose;
}


// Initialize crypto context
// flags: specifies which modules should be enabled
// mmap:  start of the crypto hardware physical memory
int
espah_init (int flags, U32 mmap)
{
	int i;

	elp_mutex_init (espah_context_lock);
	EMEMSET (&_espah_handle[0], 0, sizeof (_espah_handle));
	EMEMSET (&_espah_module, 0, sizeof (_espah_module));

	elp_mutex_init (_espah_module.mlock);
	_espah_module.cookie = ELP_COOKIE;
	_espah_module.active = 1;
	_espah_module.max = ESPAH_HANDLES_MAX;
	_espah_module.ctx_handle = _espah_handle;

	_espah_module.int_ctrl = (U32 *) (mmap + ESPAH_INT_EN_REG);
	_espah_module.int_stat = (U32 *) (mmap + ESPAH_INT_STAT_REG);
	_espah_module.arbiter_req = (U32 *) (mmap + ESPAH_SEC_REQ_REG);
	_espah_module.arbiter_gnt = (U32 *) (mmap + ESPAH_SEC_GNT_REG);
	_espah_module.srm_go = (U32 *) (mmap + ESPAH_SRM_GO_REG);
	_espah_module.srm_rdy = (U32 *) (mmap + ESPAH_SRM_RDY_REG);
	_espah_module.out_src_ptr = (U32 *) (mmap + ESPAH_OUT_SRC_PTR_REG);
	_espah_module.out_dst_ptr = (U32 *) (mmap + ESPAH_OUT_DST_PTR_REG);
	_espah_module.out_offset = (U32 *) (mmap + ESPAH_OUT_OFFSET_REG);
	_espah_module.out_stat = (U32 *) (mmap + ESPAH_OUT_STAT_REG);
	_espah_module.out_sai = (U32 *) (mmap + ESPAH_OUT_SAI_REG);
	_espah_module.in_src_ptr = (U32 *) (mmap + ESPAH_IN_SRC_PTR_REG);
	_espah_module.in_dst_ptr = (U32 *) (mmap + ESPAH_IN_DST_PTR_REG);
	_espah_module.in_offset = (U32 *) (mmap + ESPAH_IN_OFFSET_REG);
	_espah_module.in_stat = (U32 *) (mmap + ESPAH_IN_STAT_REG);
	_espah_module.in_sai = (U32 *) (mmap + ESPAH_IN_SAI_REG);
	_espah_module.srm_cmd0 = (U32 *) (mmap + ESPAH_SRM_CMD_0_REG);
	_espah_module.srm_cmd1 = (U32 *) (mmap + ESPAH_SRM_CMD_1_REG);
	_espah_module.srm_cmd2 = (U32 *) (mmap + ESPAH_SRM_CMD_2_REG);
	_espah_module.srm_ret0 = (U32 *) (mmap + ESPAH_SRM_RET_0_REG);
	_espah_module.srm_ret1 = (U32 *) (mmap + ESPAH_SRM_RET_1_REG);

#ifndef DEF_KSZ
	_espah_module.out_packet = (U32 *) (mmap + ESPAH_DPRAM_BASE + ESPAH_SA_POOL_SIZE);
	_espah_module.in_packet = (U32 *) (mmap + ESPAH_DPRAM_BASE + ESPAH_DPRAM_PACKET_IN_SIZE + ESPAH_SA_POOL_SIZE);
#else
	_espah_module.out_packet = (U32 *) (ESPAH_DPRAM_BASE + ESPAH_OUT_BASE);
	_espah_module.in_packet = (U32 *) (ESPAH_DPRAM_BASE + ESPAH_IN_BASE);
#endif

	for (i = 0; i < ESPAH_HANDLES_MAX; i++)
	{
		_espah_handle[i].taken = 0;
		_espah_handle[i].index = i;
		_espah_handle[i].module = &_espah_module;	// back pointer to the global control
		// hardware context is two SAs ; outbound and inbound

#ifndef DEF_KSZ
		_espah_handle[i].sa_ctx = (U32 *) (mmap + ESPAH_DPRAM_BASE + (ESPAH_SA_SIZE * 2 * i));
#else
		_espah_handle[i].sa_ctx = (U32 *) (ESPAH_SA_BASE + (ESPAH_SA_SIZE * 2 * i));
#endif
	}

	espah_context_initialized = 1;
	return ESPAH_OK;

}

espah_handle *
espah_context_lookup (U32 handle)
{
	if (handle < ESPAH_HANDLES_MAX)
		return &_espah_handle[handle];
	else
		return NULL;
}


void espah_get_buffers (
	unsigned char** in,
	unsigned char** out )
{
	*in = ( unsigned char* ) _espah_module.in_packet;
	*out = ( unsigned char* ) _espah_module.out_packet;
}

#ifdef DEF_LINUX
EXPORT_SYMBOL(espah_get_buffers);
#endif


int
espah_close (int handle)
{
	espah_handle *ctx = espah_context_lookup (handle);
	elp_mutex_lock (espah_context_lock);
	if (ctx)
	{
		ctx->taken = 0;
		PDEBUG (EDCTX, "espah_close: handle:%d.\n", handle);
		elp_mutex_unlock (espah_context_lock);
		return ESPAH_OK;
	}
	elp_mutex_unlock (espah_context_lock);
	return ESPAH_INVALID_HANDLE;
}

#ifdef DEF_LINUX
EXPORT_SYMBOL(espah_close);
#endif

int
espah_open (int type, int mode)
{
	int i;

	if (!espah_context_initialized)
		return ESPAH_NOT_INITIALIZED;

	elp_mutex_lock (espah_context_lock);
	for (i = 0; i < _espah_module.max; i++)
	{
		if (!_espah_module.ctx_handle[i].taken)
		{
			_espah_module.ctx_handle[i].taken = 1;
			_espah_module.ctx_handle[i].mode = mode;
			PDEBUG (EDCTX, "espah_open: type:%d mode:%d handle:%d.\n", type, mode, i);

			elp_mutex_unlock (espah_context_lock);
			return i;
		}

	}
	elp_mutex_unlock (espah_context_lock);
	return ESPAH_NO_MEM;
}

#ifdef DEF_LINUX
EXPORT_SYMBOL(espah_open);
#endif

// Returns a user friendly error message for a correspponding error code
char *
espah_error_msg (int err)
{
	switch (err)
	{
	case ESPAH_OK:
		return "Operation has succeeded";
		break;
	case ESPAH_FAILED:
		return "Operation has failed";
		break;
	case ESPAH_FAILED_TIMEOUT:
		return "Operation has failed on timeout";
		break;
	case ESPAH_INPROGRESS:
		return "Operation in progress";
		break;
	case ESPAH_INVALID_HANDLE:
		return "Invalid handle";
		break;
	case ESPAH_INVALID_CONTEXT:
		return "Invalid context";
		break;
	case ESPAH_INVALID_SIZE:
		return "Invalid size";
		break;
	case ESPAH_NOT_INITIALIZED:
		return "Crypto library has not been initialized";
		break;
	case ESPAH_NO_MEM:
		return "No context memory";
		break;
	case ESPAH_INVALID_ALG:
		return "Algorithm is not supported";
		break;
	case ESPAH_INVALID_KEY_SIZE:
		return "Invalid key size";
		break;
	case ESPAH_INVALID_ARGUMENT:
		return "Invalid argument";
		break;
	case ESPAH_MODULE_DISABLED:
		return "Crypto module disabled";
		break;
	case ESPAH_NOT_IMPLEMENTED:
		return "Function is not implemented";
		break;
	case ESPAH_INVALID_BLOCK_ALIGNMENT:
		return "Invalid block alignment";
		break;
	case ESPAH_INVALID_MODE:
		return "Invalid mode";
		break;
	case ESPAH_INVALID_KEY:
		return "Invalid key";
		break;
	case ESPAH_AUTHENTICATION_FAILED:
		return "Authentication failed";
		break;
	case ESPAH_SOFT_TTL:
		return "The soft TTL limit was hit";
		break;
	case ESPAH_HARD_TTL:
		return "The hard TTL limit was hit";
		break;
	case ESPAH_SA_INACTIVE:
		return "The SA is not active";
		break;
	case ESPAH_REPLAY:
		return "The packet was determined to be a replay";
		break;
	case ESPAH_ICV_FAIL:
		return "The ICV check failed";
		break;
	case ESPAH_SEQ_ROLL:
		return "The Sequence Number rolled over to zero";
		break;
	case ESPAH_MEM_ERROR:
		return "The destination (or source) memory structure was not of sufficient";
		break;
	case ESPAH_VERS_ERROR:
		return "The IP version was incorrect for the SA";
		break;
	case ESPAH_PROT_ERROR:
		return "The packet IPsec protocol (ESP or AH) does not match the SA";
		break;
	case ESPAH_PYLD_ERROR:
		return "The payload length does not align to a multiple of the block size";
		break;
	case ESPAH_PAD_ERROR:
		return "The ESP padding contained within the received packet has incorrect values";
		break;
	default:
		return "Invalid error code";
		break;
	}
	return "Invalid error code";
}

#ifdef DEF_LINUX
EXPORT_SYMBOL(espah_error_msg);
#endif


// This function sets the raw ipsec contexts. The context usually which is been
// retrived by the get_context function, manually formatted according with the
// hardware specification or  initialized by the build_sa function
int espah_set_context (int handle, int direction, const unsigned char *SA)
{
	espah_handle *ctx;
	/* lookup context */
	ctx = espah_context_lookup (handle);
	if (ctx == NULL)
	{
		return -1;
	}
	/* copy */
	memcpy32htonl (((U32 *) ctx->sa_ctx) + ((direction & 1) * (ESPAH_SA_SIZE / 4)), (U32 *) SA, ESPAH_SA_SIZE / 4);
	PDUMPWORD (EDDUMP, ((U32 *) ctx->sa_ctx) + ((direction & 1) * (ESPAH_SA_SIZE / 4)), ESPAH_SA_SIZE, "SA", 0);
	return 0;
}

#ifdef DEF_LINUX
EXPORT_SYMBOL(espah_get_context);
#endif

int espah_get_context (int handle, int direction, unsigned char *SA)
{
	espah_handle *ctx;
	/* lookup context */
	ctx = espah_context_lookup (handle);
	if (ctx == NULL)
	{
		return -1;
	}
	/* copy */
	memcpy32htonl ((U32 *) SA, ((U32 *) ctx->sa_ctx) + ((direction & 1) * (ESPAH_SA_SIZE / 4)), ESPAH_SA_SIZE / 4);
	return 0;
}

#ifdef DEF_LINUX
EXPORT_SYMBOL(espah_set_context);
#endif

int espah_build_sa (
	unsigned char *sabuf,		/* 128 bytes */
	unsigned char *auth_key,	/* 32 bytes */
	unsigned char *cipher_key,	/* 32 bytes */
	unsigned char *iv,		/* 16 bytes */
	unsigned char *spi,		/* 4 bytes */
	unsigned char *hard_ttl,	/* 8 bytes */
	unsigned char *soft_ttl,	/* 8 bytes */
	unsigned enc_alg,
	unsigned auth_alg,
	unsigned ttl_type,		/* byte, time */
	unsigned anti_replay,		/* OFF, ON*/
	unsigned ext_seq,		/* OFF, ON */
	unsigned transform,		/* ESP, AH */
	unsigned mode )			/* TRANSPORT, TUNNEL */
{
	// Unique thread id
	static U16 thread_id=1;
	U16 *pflags,flags ;

	EMEMSET(sabuf,0,ESPAH_SA_SIZE);
	EMEMCPY(&sabuf[0x10],auth_key,   ESPAH_AUTH_KEY_LEN_BYTE);
	EMEMCPY(&sabuf[0x24],cipher_key, ESPAH_ENCR_KEY_LEN_BYTE);
	EMEMCPY(&sabuf[0x44],iv,         ESPAH_IV_LEN_BYTE);
	EMEMCPY(&sabuf[0x54],spi,        ESPAH_SPI_LEN_BYTE);
	EMEMCPY(&sabuf[0x6A],&thread_id, ESPAH_THREAD_ID_LEN_BYTE);
	EMEMCPY(&sabuf[0x6C],hard_ttl,   ESPAH_TTL_LEN_BYTE);
	EMEMCPY(&sabuf[0x74],soft_ttl,   ESPAH_TTL_LEN_BYTE);
	if (transform == ESPAH_ESP_TRANSFORM)
		sabuf[0x7C]= ((unsigned char)enc_alg)<<4|(unsigned char)auth_alg;
	else
		sabuf[0x7C]= (unsigned char)auth_alg;

	pflags =(unsigned short*)&sabuf[0x7E];
	flags = 0x0001 | (mode<<ESPAH_MODE_BIT) |
		(transform<<ESPAH_TRANSFORM_BIT) |
		(ext_seq << ESPAH_ANTI_REPLY_ENABLE_BIT) |
		(ext_seq<<ESPAH_EXTENDED_SEQNUM_BIT);

	if (ttl_type !=  ESPAH_NO_TTL)
	{
		flags |= (ttl_type <<ESPAH_TTL_TYPE_BIT)|(1 << ESPAH_TTL_ENABLE_BIT);
	}

	*pflags = htons(flags);
	thread_id ++;

	return ESPAH_OK;
}

#ifdef DEF_LINUX
EXPORT_SYMBOL(espah_build_sa);
#endif

int espah_wait (int handle, int direction, unsigned char *in, int in_size, unsigned char *out, int *out_size, int wait)
{
	espah_handle *ctx;
	volatile U32 *stat, ret, timeout, *base, osize, ret_code, flags;
	int iphdr_len;
	U32 *psa;
	int src_ddt = ESPAH_SRC_DDT_BASE / sizeof( U32 );
	int dst_ddt = ESPAH_DST_DDT_BASE / sizeof( U32 );

#if 0
	if (out == NULL || out_size == NULL)
		return ESPAH_INVALID_ARGUMENT;
#endif
	if (in_size > ESPAH_DPRAM_PACKET_IN_SIZE)
		return ESPAH_INVALID_SIZE;
	if (direction != ESPAH_INBOUND_DIRECTION && direction != ESPAH_OUTBOUND_DIRECTION)
		return ESPAH_INVALID_ARGUMENT;

	/* look up handle */
	ctx = espah_context_lookup (handle);
	if (ctx < 0)
		return ESPAH_INVALID_CONTEXT;

	elp_mutex_lock (espah_context_lock);

	// Fetch the mode value tunnel/trunsport so we could correctly
	// offset output data and insert outer ip header
	psa = (U32 *)(((U32 *) ctx->sa_ctx) + ((direction & 1) * (ESPAH_SA_SIZE / 4)));
	flags = (psa[0x1F] & 0x00000020);

	// get base of DPRAM
	base = _espah_module.out_packet - (ESPAH_SA_POOL_SIZE / 4);

#ifdef DEF_KSZ
	src_ddt += ESPAH_DDT_OFFSET * direction;
	dst_ddt += ESPAH_DDT_OFFSET * direction;
#endif
	if (in != NULL)
	{
		/* copy input and build DDT */
#ifndef DEF_KSZ
		memcpy32htonl ((U32 *)ctx->module->in_packet, (U32 *) in, (in_size + 3) >> 2);
#else
		if ( out != NULL )
		memcpy32((U32 *)ctx->module->in_packet + ESPAH_DPRAM_PACKET_OFFSET * direction, (U32 *) in, (in_size + 3) >> 2);
#endif

		/* setup the source DDT */
		base[src_ddt + 3] = 0;	// len
		base[src_ddt + 2] = 0;	// ptr
		base[src_ddt + 1] = in_size;

#ifndef DEF_KSZ
		base[(ESPAH_SRC_DDT_BASE / 4) + 0] = ESPAH_IN_BASE;
#else
		base[src_ddt + 0] = PHYS_ADDR( ESPAH_IN_BASE + ESPAH_DPRAM_BASE + ESPAH_DPRAM_PACKET_OUT_SIZE * direction );
#endif

		/* setup the dest DDT */
		base[dst_ddt + 3] = 0;	// len
		base[dst_ddt + 2] = 0;	// ptr
		base[dst_ddt + 1] = ESPAH_DPRAM_PACKET_OUT_SIZE;

#ifndef DEF_KSZ
		base[(ESPAH_DST_DDT_BASE / 4) + 0] = ESPAH_OUT_BASE;
#else
		base[dst_ddt + 0] = PHYS_ADDR( ESPAH_OUT_BASE + ESPAH_DPRAM_BASE + ESPAH_DPRAM_PACKET_OUT_SIZE * direction );
#endif

		/* setup the registers (sai is the address within the DPRAM) */
		if (direction == ESPAH_INBOUND_DIRECTION)
		{
			*_espah_module.in_offset = 0;

#ifndef DEF_KSZ
			*_espah_module.in_dst_ptr = ESPAH_DST_DDT_BASE;
			*_espah_module.in_src_ptr = ESPAH_SRC_DDT_BASE;
			*_espah_module.in_sai = (U32) ctx->sa_ctx - (U32) base + (ESPAH_SA_SIZE * direction);
#else
			*_espah_module.in_dst_ptr =
				PHYS_ADDR( ESPAH_DST_DDT_BASE +
				ESPAH_DPRAM_BASE );
			*_espah_module.in_src_ptr =
				PHYS_ADDR( ESPAH_SRC_DDT_BASE +
				ESPAH_DPRAM_BASE );
			*_espah_module.in_sai =
				PHYS_ADDR((U32) ctx->sa_ctx +
				(ESPAH_SA_SIZE * direction));
#endif
		}
		else
		{
			*_espah_module.out_offset = 0;

#ifndef DEF_KSZ
			*_espah_module.out_dst_ptr = ESPAH_DST_DDT_BASE;
			*_espah_module.out_src_ptr = ESPAH_SRC_DDT_BASE;
			*_espah_module.out_sai = (U32) ctx->sa_ctx - (U32) base + (ESPAH_SA_SIZE * direction);
#else
			*_espah_module.out_dst_ptr =
				PHYS_ADDR( ESPAH_DST_DDT_BASE +
				ESPAH_DDT_SIZE +
				ESPAH_DPRAM_BASE );
			*_espah_module.out_src_ptr =
				PHYS_ADDR( ESPAH_SRC_DDT_BASE +
				ESPAH_DDT_SIZE +
				ESPAH_DPRAM_BASE );
			*_espah_module.out_sai =
				PHYS_ADDR((U32) ctx->sa_ctx +
				(ESPAH_SA_SIZE * direction));
#endif
		}
	}

	if (direction == ESPAH_INBOUND_DIRECTION)
	{
		stat = _espah_module.in_stat;
	}
	else
	{
		stat = _espah_module.out_stat;
	}


	if (wait)
	{
		timeout = 10000;
#if 1
		if ( in_size >= 59900 )
			timeout = 40000;
		else
		if ( in_size >= 39800 )
			timeout = 30000;
		else
		if ( in_size >= 20000 )
			timeout = 20000;
#endif
		while ((*stat & (1UL << ESPAH_IN_STAT_BUSY)))
		{
			// put a yield in here (such as usleep)

			// decrement counter
			if (!--timeout)
			{
				elp_mutex_unlock (espah_context_lock);
				return ESPAH_FAILED_TIMEOUT;
			}
		}
	}
	else
	{
		if ((*stat & (1UL << ESPAH_IN_STAT_BUSY)))
		{
			elp_mutex_unlock (espah_context_lock);
			return ESPAH_INPROGRESS;
		}
	}

	/* at this point the packet is ready to be copied out to the user, check the ret code first */
	if (direction == ESPAH_INBOUND_DIRECTION)
	{
		ret = *_espah_module.in_stat;
	}
	else
	{
		ret = *_espah_module.out_stat;
	}

	ret_code = ((ret >> ESPAH_IN_STAT_RET_CODE) & ((1 << ESPAH_IN_STAT_RET_CODE_SIZE) - 1));
	switch (ret_code)
	{
		// This is a warning
		case -ESPAH_SOFT_TTL:
			PDEBUG(EDIPSEC,"SOFT TTL HIT RETURN: %08X\n", (int)ret);
		case ESPAH_OK:
			break;
		default:
			PDUMPWORD (EDIPSEC, (U32 *)base,8,"FAILED: DDT BASE",0);
			PDUMPWORD (EDIPSEC, (U32 *)ctx->module->in_packet,ESPAH_DPRAM_PACKET_IN_SIZE,"FAILED: PACKET IN",0);
			PDUMPWORD (EDIPSEC, (U32 *)ctx->module->out_packet,ESPAH_DPRAM_PACKET_OUT_SIZE,"FAILED: PACKET OUT",0);
			PDUMPWORD (EDIPSEC, ((U32 *) ctx->sa_ctx) + ((direction & 1) * (ESPAH_SA_SIZE / 4)), ESPAH_SA_SIZE, "FAILED: SA", 0);
			PDEBUG(EDIPSEC,"FAILED RETURN: %08X\n", (int)ret);
			elp_mutex_unlock (espah_context_lock);
			return -ret_code;
		break;
	}
	ret &= (1 << ESPAH_IN_STAT_LENGTH_SIZE) - 1;	// get output size
	osize = ret;
	ret = ((ret + 3) >> 2) << 2;	// round up to next 4 byte boundary if not 0 mod 4

	if (ret > *out_size)
	{
		// TODO: overflow error
		elp_mutex_unlock (espah_context_lock);
		return ESPAH_INVALID_SIZE;
	}

	*out_size = osize;
	// Here we go the nasty hack for the PCI core in case of the inbound tunnel mode
	// We could access only in 32 bit word and for the tunnel mode
	// we do not copy external IP header so shift the output buffer instead
	// hopefully other buses might allow the byte access
	// actually if there are no options and/or routing table the ip header is 20
	// bytes long which is 4 words however we could not rely on that ....
	if ( out != NULL )
	{
#ifndef DEF_KSZ
	memcpy32htonl ((U32 *) out, (U32 *) ctx->module->out_packet, ret >> 2);
#else
	memcpy32((U32 *) out, (U32 *) ctx->module->out_packet + ESPAH_DPRAM_PACKET_OFFSET * direction, ret >> 2);
#endif
	if (direction == ESPAH_INBOUND_DIRECTION && flags)
	{
		iphdr_len = (out[0] & 0xF) * 4;
//		printf("MOVE %d bytes to %d offset [FL:0x%X - %d]\n",ret ,iphdr_len,psa[0x1F],flags);
		EMEMMOVE(out, out + iphdr_len, ret - iphdr_len);
#if 1
		*out_size -= iphdr_len;
#endif
	}
	}
	elp_mutex_unlock (espah_context_lock);
	PDUMPWORD (EDDUMP, ((U32 *) ctx->sa_ctx) + ((direction & 1) * (ESPAH_SA_SIZE / 4)), ESPAH_SA_SIZE / 2, "SA", 0);

	return ESPAH_OK;
}

#ifdef DEF_LINUX
EXPORT_SYMBOL(espah_wait);
#endif
