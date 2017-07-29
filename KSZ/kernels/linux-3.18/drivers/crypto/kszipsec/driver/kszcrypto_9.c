/* ---------------------------------------------------------------------------
                        Copyright (c) 2007 Micrel, Inc.
   ---------------------------------------------------------------------------
    Author      Date        Descriptions
    THa         08/28/07    Created file.
   ---------------------------------------------------------------------------
*/


/* -------------------------------------------------------------------------- */

#define AES_MIN_KEY_SIZE	16
#define AES_MAX_KEY_SIZE	32

#define AES_BLOCK_SIZE		16


struct aes_ctx {
	int keysize;
	int ivsize;
	u8  key[ AES_MAX_KEY_SIZE ];
	u8  iv[ AES_BLOCK_SIZE ];
};


static inline void ksz_aes_ecb (
	const u8 *input,
	u8 *output,
	struct aes_ctx* ctx,
	unsigned int count,
	int decrypt )
{
	int err;
	int handle;
	unsigned int outsize;

	handle = crypto_open( CRYPTO_CONTEXT_AES, CRYPTO_MODE_AES_ECB );
	if ( handle < 0 ) {
		printk( "crypto_open: %s\n", crypto_error_msg( handle ));
		return;
	}
	err = crypto_set_context( handle, ctx->key, ctx->keysize, ctx->iv,
		ctx->ivsize, 0 );
	if ( err != CRYPTO_OK ) {
		printk( "crypto_set_context: %s\n", crypto_error_msg( err ));
		goto aes_ecb_error;
	}
	outsize = count;
	err = crypto_aes_wait_( handle, decrypt, ( u8* ) input, count, output,
		&outsize, 1 );
	if ( err != CRYPTO_OK ) {
		printk( "crypto_aes_wait: %s\n", crypto_error_msg( err ));
		goto aes_ecb_error;
	}

aes_ecb_error:
	crypto_close( handle );
}  /* ksz_aes_ecb */

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 17))
static inline void ksz_aes_cbc (
	const u8 *input,
	u8 *output,
	struct aes_ctx* ctx,
	u8 *iv,
	unsigned int count,
	int decrypt )
{
	int err;
	int handle;
	unsigned int outsize;
	unsigned int psize;

	handle = crypto_open( CRYPTO_CONTEXT_AES, CRYPTO_MODE_AES_CBC );
	if ( handle < 0 ) {
		printk( "crypto_open: %s\n", crypto_error_msg( handle ));
		return;
	}
	err = crypto_set_context( handle, ctx->key, ctx->keysize, iv,
		ctx->ivsize, 0 );
	if ( err != CRYPTO_OK ) {
		printk( "crypto_set_context: %s\n", crypto_error_msg( err ));
		goto aes_cbc_error;
	}
	outsize = count;
	err = crypto_aes_wait_( handle, decrypt, ( u8* ) input, count, output,
		&outsize, 1 );
	if ( err != CRYPTO_OK ) {
		printk( "crypto_aes_wait: %s\n", crypto_error_msg( err ));
		goto aes_cbc_error;
	}
	err = crypto_get_context( handle, iv, &ctx->ivsize, &psize );
	if ( err != CRYPTO_OK ) {
		printk( "crypto_get_context: %s\n",
			crypto_error_msg( err ));
		goto aes_cbc_error;
	}

aes_cbc_error:
	crypto_close( handle );
}  /* ksz_aes_cbc */
#endif

static int aes_setkey (
	void *ctx_arg,
	const uint8_t *key,
	unsigned int keylen,
	uint32_t *flags )
{
	struct aes_ctx *ctx = ctx_arg;

	if (keylen != 16 && keylen != 24 && keylen != 32) {
		*flags |= CRYPTO_TFM_RES_BAD_KEY_LEN;
		return -EINVAL;
	}

	ctx->keysize = keylen;
	memcpy( ctx->key, key, keylen );
	ctx->ivsize = AES_BLOCK_SIZE;

	return 0;
}  /* aes_setkey */

static void aes_encrypt (
	void *ctx_arg,
	uint8_t *out,
	const uint8_t *in )
{
	struct aes_ctx *ctx = ctx_arg;

	ksz_aes_ecb( in, out, ctx, AES_BLOCK_SIZE, CRYPTO_ENCRYPT );
}  /* aes_encrypt */

static void aes_decrypt (
	void *ctx_arg,
	uint8_t *out,
	const uint8_t *in )
{
	struct aes_ctx *ctx = ctx_arg;

	ksz_aes_ecb( in, out, ctx, AES_BLOCK_SIZE, CRYPTO_DECRYPT );
}  /* aes_decrypt */

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 17))
static unsigned int aes_encrypt_ecb (
	const struct cipher_desc *desc,
	u8 *out,
	const u8 *in,
	unsigned int nbytes )
{
	struct aes_ctx *ctx = crypto_tfm_ctx( desc->tfm );

	ksz_aes_ecb( in, out, ctx, nbytes, CRYPTO_ENCRYPT );
	return nbytes & ~(AES_BLOCK_SIZE - 1);
}  /* aes_encrypt_ecb */

static unsigned int aes_decrypt_ecb (
	const struct cipher_desc *desc,
	u8 *out,
	const u8 *in,
	unsigned int nbytes )
{
	struct aes_ctx *ctx = crypto_tfm_ctx( desc->tfm );

	ksz_aes_ecb( in, out, ctx, nbytes, CRYPTO_DECRYPT );
	return nbytes & ~(AES_BLOCK_SIZE - 1);
}  /* aes_decrypt_ecb */

static unsigned int aes_encrypt_cbc (
	const struct cipher_desc *desc,
	u8 *out,
	const u8 *in,
	unsigned int nbytes )
{
	struct aes_ctx *ctx = crypto_tfm_ctx( desc->tfm );

	ksz_aes_cbc( in, out, ctx, desc->info, nbytes, CRYPTO_ENCRYPT );
	return nbytes & ~(AES_BLOCK_SIZE - 1);
}  /* aes_encrypt_cbc */

static unsigned int aes_decrypt_cbc (
	const struct cipher_desc *desc,
	u8 *out,
	const u8 *in,
	unsigned int nbytes )
{
	struct aes_ctx *ctx = crypto_tfm_ctx( desc->tfm );

	ksz_aes_cbc( in, out, ctx, desc->info, nbytes, CRYPTO_DECRYPT );
	return nbytes & ~(AES_BLOCK_SIZE - 1);
}  /* aes_decrypt_cbc */
#endif

static struct crypto_alg aes_alg = {
	.cra_name		=	"aes",
	.cra_flags		=	CRYPTO_ALG_TYPE_CIPHER,
	.cra_blocksize		=	AES_BLOCK_SIZE,
	.cra_ctxsize		=	sizeof(struct aes_ctx),
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 17))
	.cra_driver_name	=	"aes-ksz8692",
	.cra_priority		=	300,
	.cra_alignmask		=	3,
#endif
	.cra_module		=	THIS_MODULE,
	.cra_list		=	LIST_HEAD_INIT(aes_alg.cra_list),
	.cra_u			=	{
		.cipher = {
			.cia_min_keysize	=	AES_MIN_KEY_SIZE,
			.cia_max_keysize	=	AES_MAX_KEY_SIZE,
			.cia_setkey		=	aes_setkey,
			.cia_encrypt		=	aes_encrypt,
			.cia_decrypt		=	aes_decrypt,
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 17))
			.cia_encrypt_ecb	=	aes_encrypt_ecb,
			.cia_decrypt_ecb	=	aes_decrypt_ecb,
			.cia_encrypt_cbc	=	aes_encrypt_cbc,
			.cia_decrypt_cbc	=	aes_decrypt_cbc,
#endif
		}
	}
};

int __init ksz_init_aes (void)
{
	printk(KERN_NOTICE "Using KSZ8692 for AES algorithm.\n");

	return crypto_register_alg(&aes_alg);
}  /* ksz_init_aes */

void __exit ksz_fini_aes (void)
{
	crypto_unregister_alg(&aes_alg);
}  /* ksz_fini_aes */

/* -------------------------------------------------------------------------- */

#define DES_KEY_SIZE		8
#define DES_BLOCK_SIZE		8

#define DES3_KEY_SIZE		(3 * DES_KEY_SIZE)
#define DES3_BLOCK_SIZE		DES_BLOCK_SIZE


struct des_ctx {
	int keysize;
	int ivsize;
	u8  key[ DES3_KEY_SIZE ];
	u8  iv[ DES_BLOCK_SIZE ];
};


static inline void ksz_des_ecb (
	const u8 *input,
	u8 *output,
	struct des_ctx* ctx,
	unsigned int count,
	int decrypt,
	int mode )
{
	int err;
	int handle;
	unsigned int outsize;

	handle = crypto_open( CRYPTO_CONTEXT_DES, mode );
	if ( handle < 0 ) {
		printk( "crypto_open: %s\n", crypto_error_msg( handle ));
		return;
	}
	err = crypto_set_context( handle, ctx->key, ctx->keysize, ctx->iv,
		ctx->ivsize, 0 );
	if ( err != CRYPTO_OK ) {
		printk( "crypto_set_context: %s\n", crypto_error_msg( err ));
		goto des_ecb_error;
	}
	outsize = count;
	err = crypto_des_wait_( handle, decrypt, ( u8* ) input, count, output,
		&outsize, 1 );
	if ( err != CRYPTO_OK ) {
		printk( "crypto_des_wait: %s\n", crypto_error_msg( err ));
		goto des_ecb_error;
	}

des_ecb_error:
	crypto_close( handle );
}  /* ksz_des_ecb */

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 17))
static inline void ksz_des_cbc (
	const u8 *input,
	u8 *output,
	struct des_ctx* ctx,
	u8 *iv,
	unsigned int count,
	int decrypt,
	int mode )
{
	int err;
	int handle;
	unsigned int outsize;
	unsigned int psize;

	handle = crypto_open( CRYPTO_CONTEXT_DES, mode );
	if ( handle < 0 ) {
		printk( "crypto_open: %s\n", crypto_error_msg( handle ));
		return;
	}
	err = crypto_set_context( handle, ctx->key, ctx->keysize, iv,
		ctx->ivsize, 0 );
	if ( err != CRYPTO_OK ) {
		printk( "crypto_set_context: %s\n", crypto_error_msg( err ));
		goto des_cbc_error;
	}
	outsize = count;
	err = crypto_des_wait_( handle, decrypt, ( u8* ) input, count, output,
		&outsize, 1 );
	if ( err != CRYPTO_OK ) {
		printk( "crypto_des_wait: %s\n", crypto_error_msg( err ));
		goto des_cbc_error;
	}
	err = crypto_get_context( handle, iv, &ctx->ivsize, &psize );
	if ( err != CRYPTO_OK ) {
		printk( "crypto_get_context: %s\n",
			crypto_error_msg( err ));
		goto des_cbc_error;
	}

des_cbc_error:
	crypto_close( handle );
}  /* ksz_des_cbc */
#endif

static int des_setkey (
	void *ctx_arg,
	const u8 *key,
	unsigned int keylen,
	u32 *flags )
{
	struct des_ctx *ctx = ctx_arg;

	ctx->keysize = keylen;
	memcpy( ctx->key, key, keylen );
	ctx->ivsize = DES_BLOCK_SIZE;

	return 0;
}  /* des_setkey */

static void des_encrypt (
	void *ctx,
	u8 *dst,
	const u8 *src )
{
	ksz_des_ecb( src, dst, ctx, DES_BLOCK_SIZE, CRYPTO_ENCRYPT,
		CRYPTO_MODE_DES_ECB );
}  /* des_encrypt */

static void des_decrypt (
	void *ctx,
	u8 *dst,
	const u8 *src )
{
	ksz_des_ecb( src, dst, ctx, DES_BLOCK_SIZE, CRYPTO_DECRYPT,
		CRYPTO_MODE_DES_ECB );
}  /* des_decrypt */

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 17))
static unsigned int des_encrypt_ecb (
	const struct cipher_desc *desc,
	u8 *out,
	const u8 *in,
	unsigned int nbytes )
{
	struct des_ctx *ctx = crypto_tfm_ctx( desc->tfm );

	ksz_des_ecb( in, out, ctx, nbytes, CRYPTO_ENCRYPT,
		CRYPTO_MODE_DES_ECB );
	return nbytes & ~(DES_BLOCK_SIZE - 1);
}  /* des_encrypt_ecb */

static unsigned int des_decrypt_ecb (
	const struct cipher_desc *desc,
	u8 *out,
	const u8 *in,
	unsigned int nbytes )
{
	struct des_ctx *ctx = crypto_tfm_ctx( desc->tfm );

	ksz_des_ecb( in, out, ctx, nbytes, CRYPTO_DECRYPT,
		CRYPTO_MODE_DES_ECB );
	return nbytes & ~(DES_BLOCK_SIZE - 1);
}  /* des_decrypt_ecb */

static unsigned int des_encrypt_cbc (
	const struct cipher_desc *desc,
	u8 *out,
	const u8 *in,
	unsigned int nbytes )
{
	struct des_ctx *ctx = crypto_tfm_ctx( desc->tfm );

	ksz_des_cbc( in, out, ctx, desc->info, nbytes, CRYPTO_ENCRYPT,
		CRYPTO_MODE_DES_CBC );
	return nbytes & ~(DES_BLOCK_SIZE - 1);
}  /* des_encrypt_cbc */

static unsigned int des_decrypt_cbc (
	const struct cipher_desc *desc,
	u8 *out,
	const u8 *in,
	unsigned int nbytes )
{
	struct des_ctx *ctx = crypto_tfm_ctx( desc->tfm );

	ksz_des_cbc( in, out, ctx, desc->info, nbytes, CRYPTO_DECRYPT,
		CRYPTO_MODE_DES_CBC );
	return nbytes & ~(DES_BLOCK_SIZE - 1);
}  /* des_decrypt_cbc */
#endif


static int des3_setkey (
	void *ctx_arg,
	const u8 *key,
	unsigned int keylen,
	u32 *flags )
{
	struct des_ctx *ctx = ctx_arg;
#if 0
	const u32 *K = (const u32 *)key;

	if (unlikely(!((K[0] ^ K[2]) | (K[1] ^ K[3])) ||
		     !((K[2] ^ K[4]) | (K[3] ^ K[5]))))
	{
		*flags |= CRYPTO_TFM_RES_BAD_KEY_SCHED;
		return -EINVAL;
	}
#endif

	ctx->keysize = keylen;
	memcpy( ctx->key, key, keylen );
	ctx->ivsize = DES3_BLOCK_SIZE;

	return 0;
}  /* des3_setkey */

static void des3_encrypt (
	void *ctx,
	u8 *dst,
	const u8 *src )
{
	ksz_des_ecb( src, dst, ctx, DES3_BLOCK_SIZE, CRYPTO_ENCRYPT,
		CRYPTO_MODE_3DES_ECB );
}  /* des3_encrypt */

static void des3_decrypt (
	void *ctx,
	u8 *dst,
	const u8 *src )
{
	ksz_des_ecb( src, dst, ctx, DES3_BLOCK_SIZE, CRYPTO_DECRYPT,
		CRYPTO_MODE_3DES_ECB );
}  /* des3_decrypt */

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 17))
static unsigned int des3_encrypt_ecb (
	const struct cipher_desc *desc,
	u8 *out,
	const u8 *in,
	unsigned int nbytes )
{
	struct des_ctx *ctx = crypto_tfm_ctx( desc->tfm );

	ksz_des_ecb( in, out, ctx, nbytes, CRYPTO_ENCRYPT,
		CRYPTO_MODE_3DES_ECB );
	return nbytes & ~(DES3_BLOCK_SIZE - 1);
}  /* des3_encrypt_ecb */

static unsigned int des3_decrypt_ecb (
	const struct cipher_desc *desc,
	u8 *out,
	const u8 *in,
	unsigned int nbytes )
{
	struct des_ctx *ctx = crypto_tfm_ctx( desc->tfm );

	ksz_des_ecb( in, out, ctx, nbytes, CRYPTO_DECRYPT,
		CRYPTO_MODE_3DES_ECB );
	return nbytes & ~(DES3_BLOCK_SIZE - 1);
}  /* des3_decrypt_ecb */

static unsigned int des3_encrypt_cbc (
	const struct cipher_desc *desc,
	u8 *out,
	const u8 *in,
	unsigned int nbytes )
{
	struct des_ctx *ctx = crypto_tfm_ctx( desc->tfm );

	ksz_des_cbc( in, out, ctx, desc->info, nbytes, CRYPTO_ENCRYPT,
		CRYPTO_MODE_3DES_CBC );
	return nbytes & ~(DES3_BLOCK_SIZE - 1);
}  /* des3_encrypt_cbc */

static unsigned int des3_decrypt_cbc (
	const struct cipher_desc *desc,
	u8 *out,
	const u8 *in,
	unsigned int nbytes )
{
	struct des_ctx *ctx = crypto_tfm_ctx( desc->tfm );

	ksz_des_cbc( in, out, ctx, desc->info, nbytes, CRYPTO_DECRYPT,
		CRYPTO_MODE_3DES_CBC );
	return nbytes & ~(DES3_BLOCK_SIZE - 1);
}  /* des3_decrypt_cbc */
#endif

static struct crypto_alg des_alg = {
	.cra_name		=	"des",
	.cra_flags		=	CRYPTO_ALG_TYPE_CIPHER,
	.cra_blocksize		=	DES_BLOCK_SIZE,
	.cra_ctxsize		=	sizeof(struct des_ctx),
	.cra_module		=	THIS_MODULE,
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 17))
	.cra_driver_name	=	"des-ksz8692",
	.cra_priority		=	300,
	.cra_alignmask		=	3,
#endif
	.cra_list		=	LIST_HEAD_INIT(des_alg.cra_list),
	.cra_u			=	{
		.cipher = {
			.cia_min_keysize	=	DES_KEY_SIZE,
			.cia_max_keysize	=	DES_KEY_SIZE,
			.cia_setkey		=	des_setkey,
			.cia_encrypt		=	des_encrypt,
			.cia_decrypt		=	des_decrypt,
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 17))
			.cia_encrypt_ecb	=	des_encrypt_ecb,
			.cia_decrypt_ecb	=	des_decrypt_ecb,
			.cia_encrypt_cbc	=	des_encrypt_cbc,
			.cia_decrypt_cbc	=	des_decrypt_cbc,
#endif
		}
	}
};

static struct crypto_alg des3_alg = {
	.cra_name		=	"des3_ede",
	.cra_flags		=	CRYPTO_ALG_TYPE_CIPHER,
	.cra_blocksize		=	DES3_BLOCK_SIZE,
	.cra_ctxsize		=	sizeof(struct des_ctx),
	.cra_module		=	THIS_MODULE,
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 17))
	.cra_driver_name	=	"des3-ksz8692",
	.cra_priority		=	300,
	.cra_alignmask		=	3,
#endif
	.cra_list		=	LIST_HEAD_INIT(des3_alg.cra_list),
	.cra_u			=	{
		.cipher = {
			.cia_min_keysize	=	DES3_KEY_SIZE,
			.cia_max_keysize	=	DES3_KEY_SIZE,
			.cia_setkey		=	des3_setkey,
			.cia_encrypt		=	des3_encrypt,
			.cia_decrypt		=	des3_decrypt,
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 17))
			.cia_encrypt_ecb	=	des3_encrypt_ecb,
			.cia_decrypt_ecb	=	des3_decrypt_ecb,
			.cia_encrypt_cbc	=	des3_encrypt_cbc,
			.cia_decrypt_cbc	=	des3_decrypt_cbc,
#endif
		}
	}
};

int __init ksz_init_des (void)
{
	printk(KERN_NOTICE "Using KSZ8692 for DES algorithm.\n");

	if ( crypto_register_alg(&des_alg) )
		return -ENODEV;
	return crypto_register_alg(&des3_alg);
}  /* ksz_init_des */

void __exit ksz_fini_des (void)
{
	crypto_unregister_alg(&des_alg);
	crypto_unregister_alg(&des3_alg);
}  /* ksz_fini_des */

