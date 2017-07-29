/* ---------------------------------------------------------------------------
                        Copyright (c) 2007 Micrel, Inc.
   ---------------------------------------------------------------------------
    Author      Date        Descriptions
    THa         08/27/07    Created file.
   ---------------------------------------------------------------------------
*/


/* -------------------------------------------------------------------------- */

#define PEGASUS_ALIGNMENT	4

#define PEGASUS_CRA_PRIORITY	300
#define PEGASUS_COMPOSITE_PRIORITY 400

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

static int aes_setkey (
	struct crypto_tfm *tfm,
	const uint8_t *key,
	unsigned int keylen )
{
	struct aes_ctx *ctx = crypto_tfm_ctx(tfm);
	u32 *flags = &tfm->crt_flags;

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
	struct crypto_tfm *tfm,
	uint8_t *out,
	const uint8_t *in )
{
	struct aes_ctx *ctx = crypto_tfm_ctx(tfm);

	ksz_aes_ecb( in, out, ctx, AES_BLOCK_SIZE, CRYPTO_ENCRYPT );
}  /* aes_encrypt */

static void aes_decrypt (
	struct crypto_tfm *tfm,
	uint8_t *out,
	const uint8_t *in )
{
	struct aes_ctx *ctx = crypto_tfm_ctx(tfm);

	ksz_aes_ecb( in, out, ctx, AES_BLOCK_SIZE, CRYPTO_DECRYPT );
}  /* aes_decrypt */

static struct crypto_alg aes_alg = {
	.cra_name		=	"aes",
	.cra_flags		=	CRYPTO_ALG_TYPE_CIPHER,
	.cra_blocksize		=	AES_BLOCK_SIZE,
	.cra_ctxsize		=	sizeof(struct aes_ctx),

	.cra_driver_name	=	"aes-pegasus",
	.cra_priority		=	PEGASUS_CRA_PRIORITY,
	.cra_alignmask		=	PEGASUS_ALIGNMENT - 1,

	.cra_module		=	THIS_MODULE,
	.cra_list		=	LIST_HEAD_INIT(aes_alg.cra_list),
	.cra_u			=	{
		.cipher = {
			.cia_min_keysize	=	AES_MIN_KEY_SIZE,
			.cia_max_keysize	=	AES_MAX_KEY_SIZE,
			.cia_setkey	   	= 	aes_setkey,
			.cia_encrypt	 	=	aes_encrypt,
			.cia_decrypt	  	=	aes_decrypt,
		}
	}
};


static int aes_encrypt_ecb (
	struct blkcipher_desc *desc,
	struct scatterlist *dst,
	struct scatterlist *src,
	unsigned int nbytes )
{
	struct aes_ctx *ctx = crypto_blkcipher_ctx(desc->tfm);
	struct blkcipher_walk walk;
	int err;

	blkcipher_walk_init(&walk, dst, src, nbytes);
	err = blkcipher_walk_virt(desc, &walk);

	while ((nbytes = walk.nbytes)) {
		ksz_aes_ecb( walk.src.virt.addr, walk.dst.virt.addr, ctx,
			nbytes, CRYPTO_ENCRYPT );
		nbytes = 0;
		err = blkcipher_walk_done(desc, &walk, nbytes);
	}

	return err;
}  /* aes_encrypt_ecb */

static int aes_decrypt_ecb (
	struct blkcipher_desc *desc,
	struct scatterlist *dst,
	struct scatterlist *src,
	unsigned int nbytes )
{
	struct aes_ctx *ctx = crypto_blkcipher_ctx(desc->tfm);
	struct blkcipher_walk walk;
	int err;

	blkcipher_walk_init(&walk, dst, src, nbytes);
	err = blkcipher_walk_virt(desc, &walk);

	while ((nbytes = walk.nbytes)) {
		ksz_aes_ecb( walk.src.virt.addr, walk.dst.virt.addr, ctx,
			nbytes, CRYPTO_DECRYPT );
		nbytes = 0;
		err = blkcipher_walk_done(desc, &walk, nbytes);
	}

	return err;
}  /* aes_decrypt_ecb */

static struct crypto_alg aes_ecb_alg = {
	.cra_name		=	"ecb(aes)",
	.cra_flags		=	CRYPTO_ALG_TYPE_BLKCIPHER,
	.cra_blocksize		=	AES_BLOCK_SIZE,
	.cra_ctxsize		=	sizeof(struct aes_ctx),

	.cra_driver_name	=	"aes-ecb-pegasus",
	.cra_priority		=	PEGASUS_COMPOSITE_PRIORITY,
	.cra_alignmask		=	PEGASUS_ALIGNMENT - 1,
	.cra_type		=	&crypto_blkcipher_type,

	.cra_module		=	THIS_MODULE,
	.cra_list		=	LIST_HEAD_INIT(aes_ecb_alg.cra_list),
	.cra_u			=	{
		.blkcipher = {
			.min_keysize	=	AES_MIN_KEY_SIZE,
			.max_keysize	=	AES_MAX_KEY_SIZE,
			.setkey	   	= 	aes_setkey,
			.encrypt	=	aes_encrypt_ecb,
			.decrypt	=	aes_decrypt_ecb,
		}
	}
};


static int aes_encrypt_cbc (
	struct blkcipher_desc *desc,
	struct scatterlist *dst,
	struct scatterlist *src,
	unsigned int nbytes )
{
	struct aes_ctx *ctx = crypto_blkcipher_ctx(desc->tfm);
	struct blkcipher_walk walk;
	int err;

	blkcipher_walk_init(&walk, dst, src, nbytes);
	err = blkcipher_walk_virt(desc, &walk);

	while ((nbytes = walk.nbytes)) {
		ksz_aes_cbc( walk.src.virt.addr, walk.dst.virt.addr, ctx,
			walk.iv, nbytes, CRYPTO_ENCRYPT );
		nbytes = 0;
		err = blkcipher_walk_done(desc, &walk, nbytes);
	}

	return err;
}  /* aes_encrypt_cbc */

static int aes_decrypt_cbc (
	struct blkcipher_desc *desc,
	struct scatterlist *dst,
	struct scatterlist *src,
	unsigned int nbytes )
{
	struct aes_ctx *ctx = crypto_blkcipher_ctx(desc->tfm);
	struct blkcipher_walk walk;
	int err;

	blkcipher_walk_init(&walk, dst, src, nbytes);
	err = blkcipher_walk_virt(desc, &walk);

	while ((nbytes = walk.nbytes)) {
		ksz_aes_cbc( walk.src.virt.addr, walk.dst.virt.addr, ctx,
			walk.iv, nbytes, CRYPTO_DECRYPT );
		nbytes = 0;
		err = blkcipher_walk_done(desc, &walk, nbytes);
	}

	return err;
}  /* aes_decrypt_cbc */

static struct crypto_alg aes_cbc_alg = {
	.cra_name		=	"cbc(aes)",
	.cra_flags		=	CRYPTO_ALG_TYPE_BLKCIPHER,
	.cra_blocksize		=	AES_BLOCK_SIZE,
	.cra_ctxsize		=	sizeof(struct aes_ctx),

	.cra_driver_name	=	"aes-cbc-pegasus",
	.cra_priority		=	PEGASUS_COMPOSITE_PRIORITY,
	.cra_alignmask		=	PEGASUS_ALIGNMENT - 1,
	.cra_type		=	&crypto_blkcipher_type,

	.cra_module		=	THIS_MODULE,
	.cra_list		=	LIST_HEAD_INIT(aes_cbc_alg.cra_list),
	.cra_u			=	{
		.blkcipher = {
			.min_keysize	=	AES_MIN_KEY_SIZE,
			.max_keysize	=	AES_MAX_KEY_SIZE,
			.ivsize		=	AES_BLOCK_SIZE,
			.setkey	   	= 	aes_setkey,
			.encrypt	=	aes_encrypt_cbc,
			.decrypt	=	aes_decrypt_cbc,
		}
	}
};


int __init ksz_init_aes (void)
{
	int ret;

	if ((ret = crypto_register_alg(&aes_alg)))
		goto aes_err;

	if ((ret = crypto_register_alg(&aes_ecb_alg)))
		goto aes_ecb_err;

	if ((ret = crypto_register_alg(&aes_cbc_alg)))
		goto aes_cbc_err;

	printk(KERN_NOTICE "Using Pegasus for AES algorithm.\n");

out:
	return ret;

aes_cbc_err:
	crypto_unregister_alg(&aes_ecb_alg);
aes_ecb_err:
	crypto_unregister_alg(&aes_alg);
aes_err:
	printk(KERN_ERR "Pegasus AES initialization failed.\n");
	goto out;
}  /* ksz_init_aes */

void __exit ksz_fini_aes (void)
{
	crypto_unregister_alg(&aes_cbc_alg);
	crypto_unregister_alg(&aes_ecb_alg);
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

static int des_setkey (
	struct crypto_tfm *tfm,
	const u8 *key,
	unsigned int keylen )
{
	struct des_ctx *ctx = crypto_tfm_ctx(tfm);
#if 0
	u32 *flags = &tfm->crt_flags;
#endif

	ctx->keysize = keylen;
	memcpy( ctx->key, key, keylen );
	ctx->ivsize = DES_BLOCK_SIZE;

	return 0;
}  /* des_setkey */

static void des_encrypt (
	struct crypto_tfm *tfm,
	u8 *dst,
	const u8 *src )
{
	struct des_ctx *ctx = crypto_tfm_ctx(tfm);

	ksz_des_ecb( src, dst, ctx, DES_BLOCK_SIZE, CRYPTO_ENCRYPT,
		CRYPTO_MODE_DES_ECB );
}  /* des_encrypt */

static void des_decrypt (
	struct crypto_tfm *tfm,
	u8 *dst,
	const u8 *src )
{
	struct des_ctx *ctx = crypto_tfm_ctx(tfm);

	ksz_des_ecb( src, dst, ctx, DES_BLOCK_SIZE, CRYPTO_DECRYPT,
		CRYPTO_MODE_DES_ECB );
}  /* des_decrypt */

static struct crypto_alg des_alg = {
	.cra_name		=	"des",
	.cra_flags		=	CRYPTO_ALG_TYPE_CIPHER,
	.cra_blocksize		=	DES_BLOCK_SIZE,
	.cra_ctxsize		=	sizeof(struct des_ctx),

	.cra_driver_name	=	"des-pegasus",
	.cra_priority		=	PEGASUS_CRA_PRIORITY,
	.cra_alignmask		=	PEGASUS_ALIGNMENT - 1,

	.cra_module		=	THIS_MODULE,
	.cra_list		=	LIST_HEAD_INIT(des_alg.cra_list),
	.cra_u			=	{
		.cipher = {
			.cia_min_keysize	=	DES_KEY_SIZE,
			.cia_max_keysize	=	DES_KEY_SIZE,
			.cia_setkey		=	des_setkey,
			.cia_encrypt		=	des_encrypt,
			.cia_decrypt		=	des_decrypt,
		}
	}
};


static int des_encrypt_ecb (
	struct blkcipher_desc *desc,
	struct scatterlist *dst,
	struct scatterlist *src,
	unsigned int nbytes )
{
	struct des_ctx *ctx = crypto_blkcipher_ctx(desc->tfm);
	struct blkcipher_walk walk;
	int err;

	blkcipher_walk_init(&walk, dst, src, nbytes);
	err = blkcipher_walk_virt(desc, &walk);

	while ((nbytes = walk.nbytes)) {
		ksz_des_ecb( walk.src.virt.addr, walk.dst.virt.addr, ctx,
			nbytes, CRYPTO_ENCRYPT,
			CRYPTO_MODE_DES_ECB );
		nbytes = 0;
		err = blkcipher_walk_done(desc, &walk, nbytes);
	}

	return err;
}  /* des_encrypt_ecb */

static int des_decrypt_ecb (
	struct blkcipher_desc *desc,
	struct scatterlist *dst,
	struct scatterlist *src,
	unsigned int nbytes )
{
	struct des_ctx *ctx = crypto_blkcipher_ctx(desc->tfm);
	struct blkcipher_walk walk;
	int err;

	blkcipher_walk_init(&walk, dst, src, nbytes);
	err = blkcipher_walk_virt(desc, &walk);

	while ((nbytes = walk.nbytes)) {
		ksz_des_ecb( walk.src.virt.addr, walk.dst.virt.addr, ctx,
			nbytes, CRYPTO_DECRYPT,
			CRYPTO_MODE_DES_ECB );
		nbytes = 0;
		err = blkcipher_walk_done(desc, &walk, nbytes);
	}

	return err;
}  /* des_decrypt_ecb */

static struct crypto_alg des_ecb_alg = {
	.cra_name		=	"ecb(des)",
	.cra_flags		=	CRYPTO_ALG_TYPE_BLKCIPHER,
	.cra_blocksize		=	DES_BLOCK_SIZE,
	.cra_ctxsize		=	sizeof(struct des_ctx),

	.cra_driver_name	=	"des-ecb-pegasus",
	.cra_priority		=	PEGASUS_COMPOSITE_PRIORITY,
	.cra_alignmask		=	PEGASUS_ALIGNMENT - 1,
	.cra_type		=	&crypto_blkcipher_type,

	.cra_module		=	THIS_MODULE,
	.cra_list		=	LIST_HEAD_INIT(des_ecb_alg.cra_list),
	.cra_u			=	{
		.blkcipher = {
			.min_keysize	=	DES_KEY_SIZE,
			.max_keysize	=	DES_KEY_SIZE,
			.setkey		=	des_setkey,
			.encrypt	=	des_encrypt_ecb,
			.decrypt	=	des_decrypt_ecb,
		}
	}
};


static int des_encrypt_cbc (
	struct blkcipher_desc *desc,
	struct scatterlist *dst,
	struct scatterlist *src,
	unsigned int nbytes )
{
	struct des_ctx *ctx = crypto_blkcipher_ctx(desc->tfm);
	struct blkcipher_walk walk;
	int err;

	blkcipher_walk_init(&walk, dst, src, nbytes);
	err = blkcipher_walk_virt(desc, &walk);

	while ((nbytes = walk.nbytes)) {
		ksz_des_cbc( walk.src.virt.addr, walk.dst.virt.addr, ctx,
			walk.iv, nbytes, CRYPTO_ENCRYPT,
			CRYPTO_MODE_DES_CBC );
		nbytes = 0;
		err = blkcipher_walk_done(desc, &walk, nbytes);
	}

	return err;
}  /* des_encrypt_cbc */

static int des_decrypt_cbc (
	struct blkcipher_desc *desc,
	struct scatterlist *dst,
	struct scatterlist *src,
	unsigned int nbytes )
{
	struct des_ctx *ctx = crypto_blkcipher_ctx(desc->tfm);
	struct blkcipher_walk walk;
	int err;

	blkcipher_walk_init(&walk, dst, src, nbytes);
	err = blkcipher_walk_virt(desc, &walk);

	while ((nbytes = walk.nbytes)) {
		ksz_des_cbc( walk.src.virt.addr, walk.dst.virt.addr, ctx,
			walk.iv, nbytes, CRYPTO_DECRYPT,
			CRYPTO_MODE_DES_CBC );
		nbytes = 0;
		err = blkcipher_walk_done(desc, &walk, nbytes);
	}

	return err;
}  /* des_decrypt_cbc */

static struct crypto_alg des_cbc_alg = {
	.cra_name		=	"cbc(des)",
	.cra_flags		=	CRYPTO_ALG_TYPE_BLKCIPHER,
	.cra_blocksize		=	DES_BLOCK_SIZE,
	.cra_ctxsize		=	sizeof(struct des_ctx),

	.cra_driver_name	=	"des-cbc-pegasus",
	.cra_priority		=	PEGASUS_COMPOSITE_PRIORITY,
	.cra_alignmask		=	PEGASUS_ALIGNMENT - 1,
	.cra_type		=	&crypto_blkcipher_type,

	.cra_module		=	THIS_MODULE,
	.cra_list		=	LIST_HEAD_INIT(des_cbc_alg.cra_list),
	.cra_u			=	{
		.blkcipher = {
			.min_keysize	=	DES_KEY_SIZE,
			.max_keysize	=	DES_KEY_SIZE,
			.ivsize		=	DES_BLOCK_SIZE,
			.setkey		=	des_setkey,
			.encrypt	=	des_encrypt_cbc,
			.decrypt	=	des_decrypt_cbc,
		}
	}
};


static int des3_setkey (
	struct crypto_tfm *tfm,
	const u8 *key,
	unsigned int keylen )
{
	struct des_ctx *ctx = crypto_tfm_ctx(tfm);
#if 0
	u32 *flags = &tfm->crt_flags;
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
	struct crypto_tfm *tfm,
	u8 *dst,
	const u8 *src )
{
	struct des_ctx *ctx = crypto_tfm_ctx(tfm);

	ksz_des_ecb( src, dst, ctx, DES3_BLOCK_SIZE, CRYPTO_ENCRYPT,
		CRYPTO_MODE_3DES_ECB );
}  /* des3_encrypt */

static void des3_decrypt (
	struct crypto_tfm *tfm,
	u8 *dst,
	const u8 *src )
{
	struct des_ctx *ctx = crypto_tfm_ctx(tfm);

	ksz_des_ecb( src, dst, ctx, DES3_BLOCK_SIZE, CRYPTO_DECRYPT,
		CRYPTO_MODE_3DES_ECB );
}  /* des3_decrypt */

static struct crypto_alg des3_alg = {
	.cra_name		=	"des3_ede",
	.cra_flags		=	CRYPTO_ALG_TYPE_CIPHER,
	.cra_blocksize		=	DES3_BLOCK_SIZE,
	.cra_ctxsize		=	sizeof(struct des_ctx),

	.cra_driver_name	=	"des3-pegasus",
	.cra_priority		=	PEGASUS_CRA_PRIORITY,
	.cra_alignmask		=	PEGASUS_ALIGNMENT - 1,

	.cra_module		=	THIS_MODULE,
	.cra_list		=	LIST_HEAD_INIT(des3_alg.cra_list),
	.cra_u			=	{
		.cipher = {
			.cia_min_keysize	=	DES3_KEY_SIZE,
			.cia_max_keysize	=	DES3_KEY_SIZE,
			.cia_setkey		=	des3_setkey,
			.cia_encrypt		=	des3_encrypt,
			.cia_decrypt		=	des3_decrypt,
		}
	}
};


static int des3_encrypt_ecb (
	struct blkcipher_desc *desc,
	struct scatterlist *dst,
	struct scatterlist *src,
	unsigned int nbytes )
{
	struct des_ctx *ctx = crypto_blkcipher_ctx(desc->tfm);
	struct blkcipher_walk walk;
	int err;

	blkcipher_walk_init(&walk, dst, src, nbytes);
	err = blkcipher_walk_virt(desc, &walk);

	while ((nbytes = walk.nbytes)) {
		ksz_des_ecb( walk.src.virt.addr, walk.dst.virt.addr, ctx,
			nbytes, CRYPTO_ENCRYPT,
			CRYPTO_MODE_3DES_ECB );
		nbytes = 0;
		err = blkcipher_walk_done(desc, &walk, nbytes);
	}

	return err;
}  /* des3_encrypt_ecb */

static int des3_decrypt_ecb (
	struct blkcipher_desc *desc,
	struct scatterlist *dst,
	struct scatterlist *src,
	unsigned int nbytes )
{
	struct des_ctx *ctx = crypto_blkcipher_ctx(desc->tfm);
	struct blkcipher_walk walk;
	int err;

	blkcipher_walk_init(&walk, dst, src, nbytes);
	err = blkcipher_walk_virt(desc, &walk);

	while ((nbytes = walk.nbytes)) {
		ksz_des_ecb( walk.src.virt.addr, walk.dst.virt.addr, ctx,
			nbytes, CRYPTO_DECRYPT,
			CRYPTO_MODE_3DES_ECB );
		nbytes = 0;
		err = blkcipher_walk_done(desc, &walk, nbytes);
	}

	return err;
}  /* des3_decrypt_ecb */

static struct crypto_alg des3_ecb_alg = {
	.cra_name		=	"ecb(des3_ede)",
	.cra_flags		=	CRYPTO_ALG_TYPE_BLKCIPHER,
	.cra_blocksize		=	DES3_BLOCK_SIZE,
	.cra_ctxsize		=	sizeof(struct des_ctx),

	.cra_driver_name	=	"des3-ecb-pegasus",
	.cra_priority		=	PEGASUS_COMPOSITE_PRIORITY,
	.cra_alignmask		=	PEGASUS_ALIGNMENT - 1,
	.cra_type		=	&crypto_blkcipher_type,

	.cra_module		=	THIS_MODULE,
	.cra_list		=	LIST_HEAD_INIT(des3_ecb_alg.cra_list),
	.cra_u			=	{
		.blkcipher = {
			.min_keysize	=	DES3_KEY_SIZE,
			.max_keysize	=	DES3_KEY_SIZE,
			.setkey		=	des3_setkey,
			.encrypt	=	des3_encrypt_ecb,
			.decrypt	=	des3_decrypt_ecb,
		}
	}
};


static int des3_encrypt_cbc (
	struct blkcipher_desc *desc,
	struct scatterlist *dst,
	struct scatterlist *src,
	unsigned int nbytes )
{
	struct des_ctx *ctx = crypto_blkcipher_ctx(desc->tfm);
	struct blkcipher_walk walk;
	int err;

	blkcipher_walk_init(&walk, dst, src, nbytes);
	err = blkcipher_walk_virt(desc, &walk);

	while ((nbytes = walk.nbytes)) {
		ksz_des_cbc( walk.src.virt.addr, walk.dst.virt.addr, ctx,
			walk.iv, nbytes, CRYPTO_ENCRYPT,
			CRYPTO_MODE_3DES_CBC );
		nbytes = 0;
		err = blkcipher_walk_done(desc, &walk, nbytes);
	}

	return err;
}  /* des3_encrypt_cbc */

static int des3_decrypt_cbc (
	struct blkcipher_desc *desc,
	struct scatterlist *dst,
	struct scatterlist *src,
	unsigned int nbytes )
{
	struct des_ctx *ctx = crypto_blkcipher_ctx(desc->tfm);
	struct blkcipher_walk walk;
	int err;

	blkcipher_walk_init(&walk, dst, src, nbytes);
	err = blkcipher_walk_virt(desc, &walk);

	while ((nbytes = walk.nbytes)) {
		ksz_des_cbc( walk.src.virt.addr, walk.dst.virt.addr, ctx,
			walk.iv, nbytes, CRYPTO_DECRYPT,
			CRYPTO_MODE_3DES_CBC );
		nbytes = 0;
		err = blkcipher_walk_done(desc, &walk, nbytes);
	}

	return err;
}  /* des3_decrypt_cbc */

static struct crypto_alg des3_cbc_alg = {
	.cra_name		=	"cbc(des3_ede)",
	.cra_flags		=	CRYPTO_ALG_TYPE_BLKCIPHER,
	.cra_blocksize		=	DES3_BLOCK_SIZE,
	.cra_ctxsize		=	sizeof(struct des_ctx),

	.cra_driver_name	=	"des3-cbc-pegasus",
	.cra_priority		=	PEGASUS_COMPOSITE_PRIORITY,
	.cra_alignmask		=	PEGASUS_ALIGNMENT - 1,
	.cra_type		=	&crypto_blkcipher_type,

	.cra_module		=	THIS_MODULE,
	.cra_list		=	LIST_HEAD_INIT(des3_cbc_alg.cra_list),
	.cra_u			=	{
		.blkcipher = {
			.min_keysize	=	DES3_KEY_SIZE,
			.max_keysize	=	DES3_KEY_SIZE,
			.ivsize		=	DES3_BLOCK_SIZE,
			.setkey		=	des3_setkey,
			.encrypt	=	des3_encrypt_cbc,
			.decrypt	=	des3_decrypt_cbc,
		}
	}
};


int __init ksz_init_des (void)
{
	int ret;

	if ((ret = crypto_register_alg(&des_alg)))
		goto des_err;

	if ((ret = crypto_register_alg(&des_ecb_alg)))
		goto des_ecb_err;

	if ((ret = crypto_register_alg(&des_cbc_alg)))
		goto des_cbc_err;

	if ((ret = crypto_register_alg(&des3_alg)))
		goto des3_err;

	if ((ret = crypto_register_alg(&des3_ecb_alg)))
		goto des3_ecb_err;

	if ((ret = crypto_register_alg(&des3_cbc_alg)))
		goto des3_cbc_err;

	printk(KERN_NOTICE "Using Pegasus for DES algorithm.\n");

out:
	return ret;

des3_cbc_err:
	crypto_unregister_alg(&des3_ecb_alg);
des3_ecb_err:
	crypto_unregister_alg(&des3_alg);
des3_err:
	crypto_unregister_alg(&des_cbc_alg);
des_cbc_err:
	crypto_unregister_alg(&des_ecb_alg);
des_ecb_err:
	crypto_unregister_alg(&des_alg);
des_err:
	printk(KERN_ERR "Pegasus DES initialization failed.\n");
	goto out;
}  /* ksz_init_des */

void __exit ksz_fini_des (void)
{
	crypto_unregister_alg(&des3_cbc_alg);
	crypto_unregister_alg(&des3_ecb_alg);
	crypto_unregister_alg(&des3_alg);
	crypto_unregister_alg(&des_cbc_alg);
	crypto_unregister_alg(&des_ecb_alg);
	crypto_unregister_alg(&des_alg);
}  /* ksz_fini_des */

