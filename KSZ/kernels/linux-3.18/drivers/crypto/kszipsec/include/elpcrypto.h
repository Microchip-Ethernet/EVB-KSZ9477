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
//-----------------------------------------------------------------------
//
// Copyright (C) 2006-2007, Micrel, Inc.
//
//-----------------------------------------------------------------------*/


#ifndef _ELPCRYPTO_H_
#define _ELPCRYPTO_H_

#include "elpcryptohw.h"


#define CRYPTO_TLS1_VERSION		0x0301
#define CRYPTO_TLS1_VERSION_MAJOR	0x03
#define CRYPTO_TLS1_VERSION_MINOR	0x01


#define CRYPTO_NUM2STR(n,s)	(\
		s[3]=(unsigned long)(((n)    )&0xff),\
		s[2]=(unsigned long)(((n)>> 8)&0xff),\
		s[1]=(unsigned long)(((n)>>16)&0xff),\
		s[0]=(unsigned long)(((n)>>24)&0xff))


enum crypto_rsa_keys
{
	CRYPTO_RSA_INVALID_KEY,
	CRYPTO_RSA_PUBLIC_KEY,
	CRYPTO_RSA_PRIVATE_KEY
};


enum crypto_rsa_modes
{
	CRYPTO_RSA_INVALID_MODE,
	CRYPTO_RSA_PUBLIC_ENCRYPT,
	CRYPTO_RSA_PRIVATE_DECRYPT,
	CRYPTO_RSA_HW_VECTOR_PUBLIC,
	CRYPTO_RSA_HW_VECTOR_PRIVATE
};


enum crypto_rsa_paddings
{
	CRYPTO_RSA_RSA_NO_PADDING,
	CRYPTO_RSA_RSA_PKCS1_PADDING,
	CRYPTO_RSA_RSA_SSLV23_PADDING
};

enum crypto_errors
{
	CRYPTO_OK			=  0,
	CRYPTO_FAILED			= -1,
	CRYPTO_INPROGRESS		= -2,
	CRYPTO_INVALID_HANDLE		= -3,
	CRYPTO_INVALID_CONTEXT		= -4,
	CRYPTO_INVALID_SIZE		= -5,
	CRYPTO_NOT_INITIALIZED		= -6,
	CRYPTO_NO_MEM			= -7,
	CRYPTO_INVALID_ALG		= -8,
	CRYPTO_INVALID_KEY_SIZE		= -9,
	CRYPTO_INVALID_ARGUMENT		= -10,
	CRYPTO_MODULE_DISABLED		= -11,
	CRYPTO_NOT_IMPLEMENTED		= -12,
	CRYPTO_INVALID_BLOCK_ALIGNMENT	= -13,
	CRYPTO_INVALID_MODE		= -14,
	CRYPTO_INVALID_KEY		= -15,
	CRYPTO_AUTHENTICATION_FAILED	= -16,
	CRYPTO_SRM_FAILED		= -17
};

#define ENCRYPT          0
#define DECRYPT          1


#define CRYPTO_MAC_MIN_BLOCK_SIZE      1
#define CRYPTO_MAC_MD5_SIZE            16
#define CRYPTO_MAC_SHA1_SIZE           20
#define CRYPTO_MAC_SHA256_SIZE         32
#define CRYPTO_MAC_SHA512_SIZE         64
#define CRYPTO_MAC_ALIGNMENT           64



#define CRYPTO_AES_MIN_BLOCK_SIZE      16
#define CRYPTO_DES_MIN_BLOCK_SIZE       8
#define CRYPTO_HASH_MIN_BLOCK_SIZE      1
#define CRYPTO_HASH_MD5_SIZE            16
#define CRYPTO_HASH_SHA1_SIZE           20
#define CRYPTO_HASH_SHA256_SIZE         32
#define CRYPTO_HASH_SHA512_SIZE         64
#define CRYPTO_HASH_ALIGNMENT           64
#define CRYPTO_MAX_BLOCK_SIZE           2048


#define CRYPTO_3DES_KEY_SIZE_WORDS	6
#define CRYPTO_3DES_KEY_SIZE_BYTES	(CRYPTO_3DES_KEY_SIZE_WORDS*4)
#define CRYPTO_DES_KEY_SIZE_WORDS	2
#define CRYPTO_DES_KEY_SIZE_BYTES	(CRYPTO_DES_KEY_SIZE_WORDS*4)


#define CRYPTO_MODULE_AES		1
#define CRYPTO_MODULE_DES		2
#define CRYPTO_MODULE_RC4		4
#if 0
#define CRYPTO_MODULE_HMAC		6
#else
#define CRYPTO_MODULE_HMAC		8
#endif

#define CRYPTO_MODULES_DEFAULT_FLAGS (CRYPTO_MODULE_AES | CRYPTO_MODULE_DES)

#define CRYPTO_RC4_MAX_CONTEXTS		4
#define CRYPTO_AES_MAX_CONTEXTS		8
#define CRYPTO_DES_MAX_CONTEXTS		8
#define CRYPTO_HASH_MAX_CONTEXTS	8

#define CRYPTO_CONTEXTS_MAX		\
	(CRYPTO_RC4_MAX_CONTEXTS	\
	+CRYPTO_AES_MAX_CONTEXTS	\
	+CRYPTO_DES_MAX_CONTEXTS	\
	+CRYPTO_HASH_MAX_CONTEXTS+1)

enum crypto_modes {
	CRYPTO_MODE_DEFAULT,
	CRYPTO_MODE_3DES_CBC,
	CRYPTO_MODE_3DES_ECB,
	CRYPTO_MODE_DES_CBC,
	CRYPTO_MODE_DES_ECB,
	CRYPTO_MODE_AES_CBC,
	CRYPTO_MODE_AES_ECB,
	CRYPTO_MODE_AES_CCM,
	CRYPTO_MODE_AES_GCM,
	CRYPTO_MODE_AES_CTR,
	CRYPTO_MODE_AES_OMAC,
	CRYPTO_MODE_AES_OMAC_V2,
	CRYPTO_MODE_SHA1,
	CRYPTO_MODE_SHA256,
	CRYPTO_MODE_SHA512,
	CRYPTO_MODE_MD5,
	CRYPTO_MODE_HMAC_SHA256,
	CRYPTO_MODE_HMAC_SHA512,
	CRYPTO_MODE_HMAC_SHA1,
	CRYPTO_MODE_HMAC_MD5,
	CRYPTO_MODE_SSLMAC_SHA1,
	CRYPTO_MODE_SSLMAC_MD5,
	CRYPTO_MODE_TLSMAC_SHA1,
	CRYPTO_MODE_TLSMAC_MD5,
	CRYPTO_MODE_RSA_512,
	CRYPTO_MODE_RSA_1024,
	CRYPTO_MODE_PRNG_NOISE,
	CRYPTO_MODE_ECC,
	CRYPTO_MODE_RC4_40,
	CRYPTO_MODE_RC4_128,
	CRYPTO_MODE_MAX,
};

#define	CRYPTO_CONTEXT_AES		CRYPTO_MODULE_AES
#define	CRYPTO_CONTEXT_DES		CRYPTO_MODULE_DES
#define	CRYPTO_CONTEXT_RC4		CRYPTO_MODULE_RC4
#if 0
#define	CRYPTO_CONTEXT_HMAC		CRYPTO_MODULE_HMAC
#else
#define	CRYPTO_CONTEXT_HMAC		6
#endif


struct crypto_module_;

//  crypto module context descriptor
typedef struct handle_ctx_
{
	elp_mutex mlock;		// mutext to protect globally accessible objects;
	int taken;
	int index;			// module's context index
	int mode;			// module  mode
	int alg_par;			// alg parameter for a specific mode
	int preset_iv;			// indicates that a module should use internal prest IV value
	int first_use;			// indicates that context just has been initialized/taken
					// and this is the first use
	int algmode;
	int out_size;			// output data size
	unsigned char * data_out; 	// output buffer for non-blocking mode

	int iv_size;
	int key_size;
	U8  key[128];
	U8  iv[ELPSEC_RC4_CONTEXT_SIZE];
	int prev_data_size;		// for multiple calls of hmac_wait; needed for last call

	int curr_handle;
	struct crypto_module_ *hw_module; // back pointer to the hardware module
	volatile U32 *ctx;		// crypto module context pointer
	volatile U32 *secret;		// crypto module secret pointer

	volatile U32 *modulus;
	volatile U32 *n_prime;		// Extended Euclidean
	volatile U32 *m_residue;	// n residue of M
	volatile U32 *x_residue;	// initial residue
	volatile U32 *exponent;

	//RSA
	volatile U32 *memory_a;
	volatile U32 *memory_b;
	volatile U32 *memory_c;
	volatile U32 *memory_d;

	//ECC
	volatile U32 *a;
	volatile U32 *b;
	volatile U32 *k;
	volatile U32 *x;
	volatile U32 *y;


	// SRM specific
	unsigned char context_data[0x100],   // 256 bytes for context dumps
	              context_secret[0x100]; // 256 bytes for secret

	U32 *pctx;
	U32 data_token,
	    context_token,
	    context_index,
	    engine_token,
	    encrypt_token,
	    blocks,
	    pdata,
	    mem,
	    algo;

} handle_ctx;


// Hardware crypto module pointers
// Descriptor of multiple hadrware crypto module contexts
typedef struct crypto_module_
{
	U32 cookie;			// magic cookie
	elp_mutex mlock;		// mutext to protect globally accessible objects;
	int active;			// Do we have actually any hardware
	int type;			// Context type
	int max;			// Contexts number
	int curr_handle;		// This is curent handle accessing this hardware, need to triger retrieving context
//	int	aindex;	// Valid only after lookup, to indicate what is a context index for a requested handle
	handle_ctx *mctx;

	int data_size;			// data size loaded in the data memory
	volatile U32 *stat;		// crypto module status register pointer
	volatile U32 *data;		// crypto module data memory pointer

	volatile U32 *ctrl;		// common control register pointer
	volatile U32 *ctrl1;		// common control register pointer
// shared for aes_gcm hmac
	volatile U32 *ctrl2;		// gcm control register pointer
	volatile U32 *ctrl3;		// gcm current IV length pointer
	volatile U32 *ctrl4;		// gcm current AAD length pointer
	volatile U32 *ctrl5;		// gcm message length pointer
	volatile U32 *ctrl6;		// gcm total IV length pointer
	volatile U32 *ctrl7;		//
	volatile U32 *ctrl8;		//
	volatile U32 *ctrl9;		// gcm total AAD length pointer
	volatile U32 *ctrl10;		// gcm total message length pointer
	volatile U32 *ctrl11;		// gcm total message length pointer

	// RC4 specific control
	volatile U32 *key;
	volatile U32 *src;
	volatile U32 *dst;
	volatile U32 *len;
#if 0
	volatile U32 *ctx_ctrl;
	volatile U32 *ctx_stat;
	volatile U32 *ctx_data;
	volatile U32 *ctx_addr;
#endif
} crypto_module;

typedef struct crypto_prng_ctx_
{
	U32 cookie;			// magic cookie
	int active;			// Do we have actually any hardware
	int type;			// Context type

	volatile U32 *status;		// Active high, valid random number in the rand register
	volatile U32 *halt;		// Halts further number generation
	volatile U32 *lock;		// locks access ro the internal registers , must be reset to enable it back
	volatile U32 *rand;		// 128 bit randomm number
	volatile U32 *counter;		// 128 bit counter block
	volatile U32 *seed;		// write: 128 bit seed value read: noise data
	volatile U32 *noise_ctrl;	// enables accumulation of external entropy
} crypto_prng_ctx;


typedef U32 chandle_t;
handle_ctx *context_lookup(U32 handle);
int espah_init(int modules, U32 mmap);
int crypto_init(int modules, U32 mmap);
void crypto_set_debug(unsigned int dflag);
char *crypto_error_msg(int err);
int crypto_set_context ( int handle, unsigned char *key, int ksize, unsigned char *iv, int ivsize, int psize );
int crypto_open(int type, int mode);
int crypto_close(int handle);
int crypto_get_context ( int handle, unsigned char *iv, int *ivsize, int *psize );
int crypto_status(int handle, int *size);

int crypto_sslmac_wait_(
	int handle,
	int seq_num, int proto_type,
	unsigned char *in_buf, int in_size,
	unsigned char *out_buf, int *out_size , int wait);

#ifdef DO_OMAC
int crypto_aes_omac_wait_(
	int handle,
	unsigned char *in_buf, int in_size,
	unsigned char *out_buf, int *out_size, int wait );
#endif

int crypto_hmac_wait_(
	int handle,
	unsigned char *in_buf, int in_size,
	unsigned char *out_buf, int *out_size , int wait);

int crypto_des_wait_(
	int handle,
	int decrypt,
	unsigned char *in_buf, int in_size,
	unsigned char *out_buf, int *out_size, int wait );

int crypto_aes_wait_(
	int handle,
	int decrypt,
	unsigned char *in_buf, int in_size,
	unsigned char *out_buf, int *out_size, int wait );

int crypto_rc4_wait_(
	int handle,
	unsigned char *in_buf, int in_size,
	unsigned char *out_buf, int *out_size, int wait );


int crypto_srand(unsigned char *seed, int size);
int crypto_rand(unsigned char *rbuf, int size);
int crypto_rand_mode(unsigned int mode);


char *crypto_get_version(void);

int _ssl_mac(int handle, unsigned char protocol,
	int seq_num, unsigned char *mac_sec,
	unsigned char *input, int length,
	unsigned char *md, int mdsz);



#define crypto_hmac_wait(h,in,isz,ou,ousz) crypto_hmac_wait_(h,(char *)(in),(isz),(char *)(ou),(int *)(ousz),1)
#define crypto_hmac(h,in,isz,ou,ousz) crypto_hmac_wait_(h,(char *)(in),(isz),(char *)(ou),(int *)(ousz),0)

#define crypto_aes_wait(h,m,in,isz,ou,ousz) crypto_aes_wait_(h,m,(char *)(in),(isz),(char *)(ou),(int *)(ousz),1)
#define crypto_aes(h,m,in,isz,ou,ousz) crypto_aes_wait_(h,m,(char *)(in),(isz),(char *)(ou),(int *)(ousz),0)

#define crypto_des_wait(h,m,in,isz,ou,ousz) crypto_des_wait_(h,m,(char *)(in),(isz),(char *)(ou),(int *)(ousz),1)
#define crypto_des(h,m,in,isz,ou,ousz) crypto_des_wait_(h,m,(char *)(in),(isz),(char *)(ou),(int *)(ousz),0)

#define crypto_rc4_wait(h,in,isz,ou,ousz) crypto_des_wait_(h,m,(char *)(in),(isz),(char *)(ou),(int *)(ousz),1)
#define crypto_rc4(h,in,isz,ou,ousz) crypto_des_wait_(h,m,(char *)(in),(isz),(char *)(ou),(int *)(ousz),0)

int _aes_init(U32 mmap);
int _des_init(U32 mmap);
int _rc4_init(U32 mmap);
int _hmac_init(U32 mmap);
int _sslmac_init(U32 mmap);
int _aes_get_context(handle_ctx *ctx, unsigned char *iv, int *ivsize);
int _aes_set_context(handle_ctx *ctx, unsigned char *key, int keysize, unsigned char *iv, int ivsize);
int _des_set_context(handle_ctx *ctx, unsigned char *key, int keysize, unsigned char *iv);
int _des_get_context(handle_ctx *ctx, unsigned char *iv, int *ivsize);
int _hmac_set_context(handle_ctx *ctx, unsigned char *key, int keysize, unsigned char *iv, int ivsize, int psize);
int _hmac_get_context(handle_ctx *ctx, unsigned char *iv, int *ivsize, int *psize);
int _rc4_set_context(handle_ctx *ctx, unsigned char *key, int keysize, unsigned char *iv, int ivsize);
int _rc4_get_context(handle_ctx *ctx, unsigned char *iv, int *ivsize);

// SRM SRM SRM SRM
int elp_srm_request_blocks( U32 encryption_algo,
                            U32 encryption_blocks,
                            U32 prefered_encryption_context_token,
                            U32 hash_algo,
                            U32 hash_blocks,
                            U32 prefered_hash_context_token,
                            U32 thread_id,
                            // stuff after this is replies
                            U32 *r_encryption_base_token,
                            U32 *r_encryption_blocks,
                            U32 *r_encryption_context_token,
                            U32 *r_encryption_context_dirty_flag,
                            U32 *r_hash_base_token,
                            U32 *r_hash_blocks,
                            U32 *r_hash_context_token,
                            U32 *r_hash_context_dirty_flag);

int elp_srm_release_blocks(U32 encryption_base_token,
                           U32 encryption_blocks,
                           U32 encryption_context_token,
                           U32 encryption_context_flag,
                           U32 hash_base_token,
                           U32 hash_blocks,
                           U32 hash_context_token,
                           U32 hash_context_flag,
                           U32 thread_id);

int elp_srm_engine_request(U32 encryption_request,
                           U32 encryption_flag,
                           U32 hash_request,
                           U32 hash_flag,
                           U32 thread_id,
                           // replies
                           U32 *r_encryption_resource_token,
                           U32 *r_encryption_flags,
                           U32 *r_hash_resource_token,
                           U32 *r_hash_flags);

int elp_srm_engine_release(U32 encryption_resource_token,
                           U32 hash_resource_token,
                           U32 thread_id);


int elp_crypto_srm_setup(handle_ctx *ctx, U32 in_size, U32 algo);
int elp_crypto_srm_fini(handle_ctx *ctx);

#endif
