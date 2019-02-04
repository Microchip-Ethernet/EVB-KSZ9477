
#define AUTH_HDR_LEN		20

#define AUTH_VECTOR_LEN		16
#define CHAP_VALUE_LENGTH       16
#define MAX_STRING_LEN		254	/* RFC2138: string 0-253 octets */


/* random numbers in isaac.c */
/* context of random number generator */
typedef struct fr_randctx {
  uint32_t randcnt;
  uint32_t randrsl[256];
  uint32_t randmem[256];
  uint32_t randa;
  uint32_t randb;
  uint32_t randc;
} fr_randctx;


/*
------------------------------------------------------------------------------
http://burtleburtle.net/bob/rand/isaac.html
rand.c: By Bob Jenkins.  My random number generator, ISAAC.  Public Domain
MODIFIED:
  960327: Creation (addition of randinit, really)
  970719: use context, not global variables, for internal state
  980324: make a portable version
  010626: Note this is public domain
------------------------------------------------------------------------------
*/


#define RANDSIZL   (8)  /* I recommend 8 for crypto, 4 for simulations */
#define RANDSIZ    (1<<RANDSIZL)

#define ind(mm,x)  ((mm)[(x>>2)&(RANDSIZ-1)])
#define rngstep(mix,a,b,mm,m,m2,r,x) \
{ \
  x = *m;  \
  a = ((a^(mix)) + *(m2++)) & 0xffffffff; \
  *(m++) = y = (ind(mm,x) + a + b) & 0xffffffff; \
  *(r++) = b = (ind(mm,y>>RANDSIZL) + x) & 0xffffffff; \
}

void fr_isaac(fr_randctx *ctx)
{
   register uint32_t a,b,x,y,*m,*mm,*m2,*r,*mend;
   mm=ctx->randmem; r=ctx->randrsl;
   a = ctx->randa; b = (ctx->randb + (++ctx->randc)) & 0xffffffff;
   for (m = mm, mend = m2 = m+(RANDSIZ/2); m<mend; )
   {
      rngstep( a<<13, a, b, mm, m, m2, r, x);
      rngstep( a>>6 , a, b, mm, m, m2, r, x);
      rngstep( a<<2 , a, b, mm, m, m2, r, x);
      rngstep( a>>16, a, b, mm, m, m2, r, x);
   }
   for (m2 = mm; m2<mend; )
   {
      rngstep( a<<13, a, b, mm, m, m2, r, x);
      rngstep( a>>6 , a, b, mm, m, m2, r, x);
      rngstep( a<<2 , a, b, mm, m, m2, r, x);
      rngstep( a>>16, a, b, mm, m, m2, r, x);
   }
   ctx->randb = b; ctx->randa = a;
}


#define mix(a,b,c,d,e,f,g,h) \
{ \
   a^=b<<11; d+=a; b+=c; \
   b^=c>>2;  e+=b; c+=d; \
   c^=d<<8;  f+=c; d+=e; \
   d^=e>>16; g+=d; e+=f; \
   e^=f<<10; h+=e; f+=g; \
   f^=g>>4;  a+=f; g+=h; \
   g^=h<<8;  b+=g; h+=a; \
   h^=a>>9;  c+=h; a+=b; \
}

/* if (flag==1), then use the contents of randrsl[] to initialize mm[]. */
void fr_randinit(fr_randctx *ctx, int flag)
{
  int i;
  uint32_t a,b,c,d,e,f,g,h;
  uint32_t *m,*r;
  ctx->randa = ctx->randb = ctx->randc = 0;
  m=ctx->randmem;
  r=ctx->randrsl;
  a=b=c=d=e=f=g=h=0x9e3779b9;  /* the golden ratio */

  for (i=0; i<4; ++i) {        /* scramble it */
    mix(a,b,c,d,e,f,g,h);
  }

  if (flag) {
    /* initialize using the contents of r[] as the seed */
    for (i=0; i<RANDSIZ; i+=8) {
      a+=r[i  ]; b+=r[i+1]; c+=r[i+2]; d+=r[i+3];
      e+=r[i+4]; f+=r[i+5]; g+=r[i+6]; h+=r[i+7];
      mix(a,b,c,d,e,f,g,h);
      m[i  ]=a; m[i+1]=b; m[i+2]=c; m[i+3]=d;
      m[i+4]=e; m[i+5]=f; m[i+6]=g; m[i+7]=h;
    }
     /* do a second pass to make all of the seed affect all of m */
    for (i=0; i<RANDSIZ; i+=8) {
      a+=m[i  ]; b+=m[i+1]; c+=m[i+2]; d+=m[i+3];
      e+=m[i+4]; f+=m[i+5]; g+=m[i+6]; h+=m[i+7];
      mix(a,b,c,d,e,f,g,h);
      m[i  ]=a; m[i+1]=b; m[i+2]=c; m[i+3]=d;
      m[i+4]=e; m[i+5]=f; m[i+6]=g; m[i+7]=h;
    }
  } else {
    for (i=0; i<RANDSIZ; i+=8) {
      /* fill in mm[] with messy stuff */
      mix(a,b,c,d,e,f,g,h);
      m[i  ]=a; m[i+1]=b; m[i+2]=c; m[i+3]=d;
      m[i+4]=e; m[i+5]=f; m[i+6]=g; m[i+7]=h;
    }
  }

  fr_isaac(ctx);       /* fill in the first set of results */
  ctx->randcnt=RANDSIZ;  /* prepare to use the first set of results */
}


static fr_randctx fr_rand_pool;	/* across multiple calls */
static int fr_rand_initialized = 0;

static char secret[128];


#define FNV_MAGIC_INIT (0x811c9dc5)
#define FNV_MAGIC_PRIME (0x01000193)

/*
 *	A fast hash function.  For details, see:
 *
 *	http://www.isthe.com/chongo/tech/comp/fnv/
 *
 *	Which also includes public domain source.  We've re-written
 *	it here for our purposes.
 */
uint32_t fr_hash(const void *data, size_t size)
{
	const uint8_t *p = data;
	const uint8_t *q = p + size;
	uint32_t      hash = FNV_MAGIC_INIT;

	/*
	 *	FNV-1 hash each octet in the buffer
	 */
	while (p != q) {
		/*
		 *	XOR the 8-bit quantity into the bottom of
		 *	the hash.
		 */
		hash ^= (uint32_t) (*p++);

		/*
		 *	Multiple by 32-bit magic FNV prime, mod 2^32
		 */
		hash *= FNV_MAGIC_PRIME;
#if 0
		/*
		 *	Potential optimization.
		 */
		hash += (hash<<1) + (hash<<4) + (hash<<7) + (hash<<8) + (hash<<24);
#endif
    }

    return hash;
}

/*
 *	Continue hashing data.
 */
uint32_t fr_hash_update(const void *data, size_t size, uint32_t hash)
{
	const uint8_t *p = data;
	const uint8_t *q = p + size;

	while (p != q) {
		hash *= FNV_MAGIC_PRIME;
		hash ^= (uint32_t) (*p++);
    }

    return hash;

}


uint32_t fr_rand(void);

/*
 *	Seed the random number generator.
 *
 *	May be called any number of times.
 */
void fr_rand_seed(const void *data, size_t size)
{
	uint32_t hash;

	/*
	 *	Ensure that the pool is initialized.
	 */
	if (!fr_rand_initialized) {
		int fd;

		memset(&fr_rand_pool, 0, sizeof(fr_rand_pool));

		fd = open("/dev/urandom", O_RDONLY);
		if (fd >= 0) {
			size_t total;
			ssize_t this;

			total = this = 0;
			while (total < sizeof(fr_rand_pool.randrsl)) {
				this = read(fd, fr_rand_pool.randrsl,
					    sizeof(fr_rand_pool.randrsl) - total);
				if ((this < 0) && (errno != EINTR)) break;
				if (this > 0) total += this;
 			}
			close(fd);
		} else {
			fr_rand_pool.randrsl[0] = fd;
			fr_rand_pool.randrsl[1] = time(NULL);
			fr_rand_pool.randrsl[2] = errno;
		}

		fr_randinit(&fr_rand_pool, 1);
		fr_rand_pool.randcnt = 0;
		fr_rand_initialized = 1;
	}

	if (!data) return;

	/*
	 *	Hash the user data
	 */
	hash = fr_rand();
	if (!hash) hash = fr_rand();
	hash = fr_hash_update(data, size, hash);

	fr_rand_pool.randmem[fr_rand_pool.randcnt] ^= hash;
}


/*
 *	Return a 32-bit random number.
 */
uint32_t fr_rand(void)
{
	uint32_t num;

	/*
	 *	Ensure that the pool is initialized.
	 */
	if (!fr_rand_initialized) {
		fr_rand_seed(NULL, 0);
	}

	num = fr_rand_pool.randrsl[fr_rand_pool.randcnt++];
	if (fr_rand_pool.randcnt >= 256) {
		fr_rand_pool.randcnt = 0;
		fr_isaac(&fr_rand_pool);
	}

	return num;
}


#ifndef WITH_OPENSSL_MD5
/*  The below was retrieved from
 *  http://www.openbsd.org/cgi-bin/cvsweb/~checkout~/src/sys/crypto/md5.h?rev=1.1
 *  With the following changes: uint64_t => uint32_t[2]
 *  Commented out #include <sys/cdefs.h>
 *  Commented out the __BEGIN and __END _DECLS, and the __attributes.
 */

/*
 * This code implements the MD5 message-digest algorithm.
 * The algorithm is due to Ron Rivest.  This code was
 * written by Colin Plumb in 1993, no copyright is claimed.
 * This code is in the public domain; do with it what you wish.
 *
 * Equivalent code is available from RSA Data Security, Inc.
 * This code has been tested against that, and is equivalent,
 * except that you don't need to include two pages of legalese
 * with every copy.
 */

#define	MD5_BLOCK_LENGTH		64
#define	MD5_DIGEST_LENGTH		16

typedef struct FR_MD5Context {
	uint32_t state[4];			/* state */
	uint32_t count[2];			/* number of bits, mod 2^64 */
	uint8_t buffer[MD5_BLOCK_LENGTH];	/* input buffer */
} FR_MD5_CTX;

/* include <sys/cdefs.h> */

/* __BEGIN_DECLS */
void	 fr_MD5Init(FR_MD5_CTX *);
void	 fr_MD5Update(FR_MD5_CTX *, const uint8_t *, size_t)
/*		__attribute__((__bounded__(__string__,2,3)))*/;
void	 fr_MD5Final(uint8_t [MD5_DIGEST_LENGTH], FR_MD5_CTX *)
/*		__attribute__((__bounded__(__minbytes__,1,MD5_DIGEST_LENGTH)))*/;
void	 fr_MD5Transform(uint32_t [4], const uint8_t [MD5_BLOCK_LENGTH])
/*		__attribute__((__bounded__(__minbytes__,1,4)))*/
/*		__attribute__((__bounded__(__minbytes__,2,MD5_BLOCK_LENGTH)))*/;
/* __END_DECLS */

#else  /* WITH_OPENSSL_HASH */

#define FR_MD5_CTX	MD5_CTX
#define fr_MD5Init	MD5_Init
#define fr_MD5Update	MD5_Update
#define fr_MD5Final	MD5_Final
#define fr_MD5Transform MD5_Transform
#endif


void fr_md5_calc(uint8_t *output, const uint8_t *input,
		     unsigned int inlen)
{
	FR_MD5_CTX	context;

	fr_MD5Init(&context);
	fr_MD5Update(&context, input, inlen);
	fr_MD5Final(output, &context);
}


#ifndef WITH_OPENSSL_MD5
/*	The below was retrieved from
 *	http://www.openbsd.org/cgi-bin/cvsweb/~checkout~/src/sys/crypto/md5.c?rev=1.1
 *	with the following changes:
 *	#includes commented out.
 *	Support context->count as uint32_t[2] instead of uint64_t
 *	u_int* to uint*
 */

/*
 * This code implements the MD5 message-digest algorithm.
 * The algorithm is due to Ron Rivest.	This code was
 * written by Colin Plumb in 1993, no copyright is claimed.
 * This code is in the public domain; do with it what you wish.
 *
 * Equivalent code is available from RSA Data Security, Inc.
 * This code has been tested against that, and is equivalent,
 * except that you don't need to include two pages of legalese
 * with every copy.
 *
 * To compute the message digest of a chunk of bytes, declare an
 * MD5Context structure, pass it to fr_MD5Init, call fr_MD5Update as
 * needed on buffers full of bytes, and then call fr_MD5Final, which
 * will fill a supplied 16-byte array with the digest.
 */

/*#include <sys/param.h>*/
/*#include <sys/systm.h>*/
/*#include <crypto/md5.h>*/

#define PUT_64BIT_LE(cp, value) do {				\
	(cp)[7] = (value)[1] >> 24;					\
	(cp)[6] = (value)[1] >> 16;					\
	(cp)[5] = (value)[1] >> 8;					\
	(cp)[4] = (value)[1];						\
	(cp)[3] = (value)[0] >> 24;					\
	(cp)[2] = (value)[0] >> 16;					\
	(cp)[1] = (value)[0] >> 8;					\
	(cp)[0] = (value)[0]; } while (0)

#define PUT_32BIT_LE(cp, value) do {					\
	(cp)[3] = (value) >> 24;					\
	(cp)[2] = (value) >> 16;					\
	(cp)[1] = (value) >> 8;						\
	(cp)[0] = (value); } while (0)

static const uint8_t PADDING[MD5_BLOCK_LENGTH] = {
	0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

/*
 * Start MD5 accumulation.  Set bit count to 0 and buffer to mysterious
 * initialization constants.
 */
void
fr_MD5Init(FR_MD5_CTX *ctx)
{
	ctx->count[0] = 0;
	ctx->count[1] = 0;
	ctx->state[0] = 0x67452301;
	ctx->state[1] = 0xefcdab89;
	ctx->state[2] = 0x98badcfe;
	ctx->state[3] = 0x10325476;
}

/*
 * Update context to reflect the concatenation of another buffer full
 * of bytes.
 */
void
fr_MD5Update(FR_MD5_CTX *ctx, const unsigned char *input, size_t len)
{
	size_t have, need;

	/* Check how many bytes we already have and how many more we need. */
	have = (size_t)((ctx->count[0] >> 3) & (MD5_BLOCK_LENGTH - 1));
	need = MD5_BLOCK_LENGTH - have;

	/* Update bitcount */
/*	ctx->count += (uint64_t)len << 3;*/
	if ((ctx->count[0] += ((uint32_t)len << 3)) < (uint32_t)len) {
	/* Overflowed ctx->count[0] */
		ctx->count[1]++;
	}
	ctx->count[1] += ((uint32_t)len >> 29);

	if (len >= need) {
		if (have != 0) {
			memcpy(ctx->buffer + have, input, need);
			fr_MD5Transform(ctx->state, ctx->buffer);
			input += need;
			len -= need;
			have = 0;
		}

		/* Process data in MD5_BLOCK_LENGTH-byte chunks. */
		while (len >= MD5_BLOCK_LENGTH) {
			fr_MD5Transform(ctx->state, input);
			input += MD5_BLOCK_LENGTH;
			len -= MD5_BLOCK_LENGTH;
		}
	}

	/* Handle any remaining bytes of data. */
	if (len != 0)
		memcpy(ctx->buffer + have, input, len);
}

/*
 * Final wrapup - pad to 64-byte boundary with the bit pattern
 * 1 0* (64-bit count of bits processed, MSB-first)
 */
void
fr_MD5Final(uint8_t digest[MD5_DIGEST_LENGTH], FR_MD5_CTX *ctx)
{
	uint8_t count[8];
	size_t padlen;
	int i;

	/* Convert count to 8 bytes in little endian order. */
	PUT_64BIT_LE(count, ctx->count);

	/* Pad out to 56 mod 64. */
	padlen = MD5_BLOCK_LENGTH -
	    ((ctx->count[0] >> 3) & (MD5_BLOCK_LENGTH - 1));
	if (padlen < 1 + 8)
		padlen += MD5_BLOCK_LENGTH;
	fr_MD5Update(ctx, PADDING, padlen - 8); /* padlen - 8 <= 64 */
	fr_MD5Update(ctx, count, 8);

	if (digest != NULL) {
		for (i = 0; i < 4; i++)
			PUT_32BIT_LE(digest + i * 4, ctx->state[i]);
	}
	memset(ctx, 0, sizeof(*ctx));	/* in case it's sensitive */
}


/* The four core functions - F1 is optimized somewhat */

/* #define F1(x, y, z) (x & y | ~x & z) */
#define F1(x, y, z) (z ^ (x & (y ^ z)))
#define F2(x, y, z) F1(z, x, y)
#define F3(x, y, z) (x ^ y ^ z)
#define F4(x, y, z) (y ^ (x | ~z))

/* This is the central step in the MD5 algorithm. */
#define MD5STEP(f, w, x, y, z, data, s) \
	( w += f(x, y, z) + data,  w = w<<s | w>>(32-s),  w += x )

/*
 * The core of the MD5 algorithm, this alters an existing MD5 hash to
 * reflect the addition of 16 longwords of new data.  fr_MD5Update blocks
 * the data and converts bytes into longwords for this routine.
 */
void
fr_MD5Transform(uint32_t state[4], const uint8_t block[MD5_BLOCK_LENGTH])
{
	uint32_t a, b, c, d, in[MD5_BLOCK_LENGTH / 4];

	for (a = 0; a < MD5_BLOCK_LENGTH / 4; a++) {
		in[a] = (uint32_t)(
		    (uint32_t)(block[a * 4 + 0]) |
		    (uint32_t)(block[a * 4 + 1]) <<  8 |
		    (uint32_t)(block[a * 4 + 2]) << 16 |
		    (uint32_t)(block[a * 4 + 3]) << 24);
	}

	a = state[0];
	b = state[1];
	c = state[2];
	d = state[3];

	MD5STEP(F1, a, b, c, d, in[ 0] + 0xd76aa478,  7);
	MD5STEP(F1, d, a, b, c, in[ 1] + 0xe8c7b756, 12);
	MD5STEP(F1, c, d, a, b, in[ 2] + 0x242070db, 17);
	MD5STEP(F1, b, c, d, a, in[ 3] + 0xc1bdceee, 22);
	MD5STEP(F1, a, b, c, d, in[ 4] + 0xf57c0faf,  7);
	MD5STEP(F1, d, a, b, c, in[ 5] + 0x4787c62a, 12);
	MD5STEP(F1, c, d, a, b, in[ 6] + 0xa8304613, 17);
	MD5STEP(F1, b, c, d, a, in[ 7] + 0xfd469501, 22);
	MD5STEP(F1, a, b, c, d, in[ 8] + 0x698098d8,  7);
	MD5STEP(F1, d, a, b, c, in[ 9] + 0x8b44f7af, 12);
	MD5STEP(F1, c, d, a, b, in[10] + 0xffff5bb1, 17);
	MD5STEP(F1, b, c, d, a, in[11] + 0x895cd7be, 22);
	MD5STEP(F1, a, b, c, d, in[12] + 0x6b901122,  7);
	MD5STEP(F1, d, a, b, c, in[13] + 0xfd987193, 12);
	MD5STEP(F1, c, d, a, b, in[14] + 0xa679438e, 17);
	MD5STEP(F1, b, c, d, a, in[15] + 0x49b40821, 22);

	MD5STEP(F2, a, b, c, d, in[ 1] + 0xf61e2562,  5);
	MD5STEP(F2, d, a, b, c, in[ 6] + 0xc040b340,  9);
	MD5STEP(F2, c, d, a, b, in[11] + 0x265e5a51, 14);
	MD5STEP(F2, b, c, d, a, in[ 0] + 0xe9b6c7aa, 20);
	MD5STEP(F2, a, b, c, d, in[ 5] + 0xd62f105d,  5);
	MD5STEP(F2, d, a, b, c, in[10] + 0x02441453,  9);
	MD5STEP(F2, c, d, a, b, in[15] + 0xd8a1e681, 14);
	MD5STEP(F2, b, c, d, a, in[ 4] + 0xe7d3fbc8, 20);
	MD5STEP(F2, a, b, c, d, in[ 9] + 0x21e1cde6,  5);
	MD5STEP(F2, d, a, b, c, in[14] + 0xc33707d6,  9);
	MD5STEP(F2, c, d, a, b, in[ 3] + 0xf4d50d87, 14);
	MD5STEP(F2, b, c, d, a, in[ 8] + 0x455a14ed, 20);
	MD5STEP(F2, a, b, c, d, in[13] + 0xa9e3e905,  5);
	MD5STEP(F2, d, a, b, c, in[ 2] + 0xfcefa3f8,  9);
	MD5STEP(F2, c, d, a, b, in[ 7] + 0x676f02d9, 14);
	MD5STEP(F2, b, c, d, a, in[12] + 0x8d2a4c8a, 20);

	MD5STEP(F3, a, b, c, d, in[ 5] + 0xfffa3942,  4);
	MD5STEP(F3, d, a, b, c, in[ 8] + 0x8771f681, 11);
	MD5STEP(F3, c, d, a, b, in[11] + 0x6d9d6122, 16);
	MD5STEP(F3, b, c, d, a, in[14] + 0xfde5380c, 23);
	MD5STEP(F3, a, b, c, d, in[ 1] + 0xa4beea44,  4);
	MD5STEP(F3, d, a, b, c, in[ 4] + 0x4bdecfa9, 11);
	MD5STEP(F3, c, d, a, b, in[ 7] + 0xf6bb4b60, 16);
	MD5STEP(F3, b, c, d, a, in[10] + 0xbebfbc70, 23);
	MD5STEP(F3, a, b, c, d, in[13] + 0x289b7ec6,  4);
	MD5STEP(F3, d, a, b, c, in[ 0] + 0xeaa127fa, 11);
	MD5STEP(F3, c, d, a, b, in[ 3] + 0xd4ef3085, 16);
	MD5STEP(F3, b, c, d, a, in[ 6] + 0x04881d05, 23);
	MD5STEP(F3, a, b, c, d, in[ 9] + 0xd9d4d039,  4);
	MD5STEP(F3, d, a, b, c, in[12] + 0xe6db99e5, 11);
	MD5STEP(F3, c, d, a, b, in[15] + 0x1fa27cf8, 16);
	MD5STEP(F3, b, c, d, a, in[2 ] + 0xc4ac5665, 23);

	MD5STEP(F4, a, b, c, d, in[ 0] + 0xf4292244,  6);
	MD5STEP(F4, d, a, b, c, in[7 ] + 0x432aff97, 10);
	MD5STEP(F4, c, d, a, b, in[14] + 0xab9423a7, 15);
	MD5STEP(F4, b, c, d, a, in[5 ] + 0xfc93a039, 21);
	MD5STEP(F4, a, b, c, d, in[12] + 0x655b59c3,  6);
	MD5STEP(F4, d, a, b, c, in[3 ] + 0x8f0ccc92, 10);
	MD5STEP(F4, c, d, a, b, in[10] + 0xffeff47d, 15);
	MD5STEP(F4, b, c, d, a, in[1 ] + 0x85845dd1, 21);
	MD5STEP(F4, a, b, c, d, in[8 ] + 0x6fa87e4f,  6);
	MD5STEP(F4, d, a, b, c, in[15] + 0xfe2ce6e0, 10);
	MD5STEP(F4, c, d, a, b, in[6 ] + 0xa3014314, 15);
	MD5STEP(F4, b, c, d, a, in[13] + 0x4e0811a1, 21);
	MD5STEP(F4, a, b, c, d, in[4 ] + 0xf7537e82,  6);
	MD5STEP(F4, d, a, b, c, in[11] + 0xbd3af235, 10);
	MD5STEP(F4, c, d, a, b, in[2 ] + 0x2ad7d2bb, 15);
	MD5STEP(F4, b, c, d, a, in[9 ] + 0xeb86d391, 21);

	state[0] += a;
	state[1] += b;
	state[2] += c;
	state[3] += d;
}
#endif


void
fr_hmac_md5(const uint8_t *text, int text_len,
	      const uint8_t *key, int key_len,
	      uint8_t *digest)
{
        FR_MD5_CTX context;
        uint8_t k_ipad[65];    /* inner padding -
                                      * key XORd with ipad
                                      */
        uint8_t k_opad[65];    /* outer padding -
                                      * key XORd with opad
                                      */
        uint8_t tk[16];
        int i;
        /* if key is longer than 64 bytes reset it to key=MD5(key) */
        if (key_len > 64) {

		FR_MD5_CTX      tctx;

                fr_MD5Init(&tctx);
                fr_MD5Update(&tctx, key, key_len);
                fr_MD5Final(tk, &tctx);

                key = tk;
                key_len = 16;
        }

        /*
         * the HMAC_MD5 transform looks like:
         *
         * MD5(K XOR opad, MD5(K XOR ipad, text))
         *
         * where K is an n byte key
         * ipad is the byte 0x36 repeated 64 times

         * opad is the byte 0x5c repeated 64 times
         * and text is the data being protected
         */

        /* start out by storing key in pads */
        memset( k_ipad, 0, sizeof(k_ipad));
        memset( k_opad, 0, sizeof(k_opad));
        memcpy( k_ipad, key, key_len);
        memcpy( k_opad, key, key_len);

        /* XOR key with ipad and opad values */
        for (i = 0; i < 64; i++) {
                k_ipad[i] ^= 0x36;
                k_opad[i] ^= 0x5c;
        }
        /*
         * perform inner MD5
         */
        fr_MD5Init(&context);                   /* init context for 1st
                                              * pass */
        fr_MD5Update(&context, k_ipad, 64);      /* start with inner pad */
        fr_MD5Update(&context, text, text_len); /* then text of datagram */
        fr_MD5Final(digest, &context);          /* finish up 1st pass */
        /*
         * perform outer MD5
         */
        fr_MD5Init(&context);                   /* init context for 2nd
                                              * pass */
        fr_MD5Update(&context, k_opad, 64);     /* start with outer pad */
        fr_MD5Update(&context, digest, 16);     /* then results of 1st
                                              * hash */
        fr_MD5Final(digest, &context);          /* finish up 2nd pass */
}


#define AUTH_PASS_LEN (AUTH_VECTOR_LEN)
#if 0
/*************************************************************************
 *
 *      Function: make_secret
 *
 *      Purpose: Build an encrypted secret value to return in a reply
 *               packet.  The secret is hidden by xoring with a MD5 digest
 *               created from the shared secret and the authentication
 *               vector.  We put them into MD5 in the reverse order from
 *               that used when encrypting passwords to RADIUS.
 *
 *************************************************************************/
static void make_secret(uint8_t *digest, const uint8_t *vector,
			const char *secret, const uint8_t *value)
{
	FR_MD5_CTX context;
        int             i;

	fr_MD5Init(&context);
	fr_MD5Update(&context, vector, AUTH_VECTOR_LEN);
	fr_MD5Update(&context, (const uint8_t *) secret, strlen(secret));
	fr_MD5Final(digest, &context);

        for ( i = 0; i < AUTH_VECTOR_LEN; i++ ) {
		digest[i] ^= value[i];
        }
}
#endif


void prep_radius_req(struct radius_frame *rp)
{
	int i;
	uint32_t hash, base;

	/*
	 *	Don't expose the actual contents of the random
	 *	pool.
	 */
	base = fr_rand();
	for (i = 0; i < AUTH_VECTOR_LEN; i += sizeof(uint32_t)) {
		hash = fr_rand() ^ base;
		memcpy(rp->vector + i, &hash, sizeof(hash));
	}
	fr_rand();		/* stir the pool again */
}


#define MAX_PASS_LEN (128)
static void make_passwd(uint8_t *output, size_t *outlen,
			const uint8_t *input, size_t inlen,
			const char *secret, const uint8_t *vector)
{
	FR_MD5_CTX context, old;
	uint8_t	digest[AUTH_VECTOR_LEN];
	uint8_t passwd[MAX_PASS_LEN];
	int	i, n;
	int	len;

	/*
	 *	If the length is zero, round it up.
	 */
	len = inlen;

	if (len > MAX_PASS_LEN) len = MAX_PASS_LEN;

	memcpy(passwd, input, len);
	if (len < sizeof(passwd)) memset(passwd + len, 0, sizeof(passwd) - len);

	if (len == 0) {
		len = AUTH_PASS_LEN;
	}

	else if ((len & 0x0f) != 0) {
		len += 0x0f;
		len &= ~0x0f;
	}
	*outlen = len;

	fr_MD5Init(&context);
	fr_MD5Update(&context, (const uint8_t *) secret, strlen(secret));
	old = context;

	/*
	 *	Do first pass.
	 */
	fr_MD5Update(&context, vector, AUTH_PASS_LEN);

	for (n = 0; n < len; n += AUTH_PASS_LEN) {
		if (n > 0) {
			context = old;
			fr_MD5Update(&context,
				       passwd + n - AUTH_PASS_LEN,
				       AUTH_PASS_LEN);
		}

		fr_MD5Final(digest, &context);
		for (i = 0; i < AUTH_PASS_LEN; i++) {
			passwd[i + n] ^= digest[i];
		}
	}

	memcpy(output, passwd, len);
}

/*
 *	Encode password.
 *
 *	We assume that the passwd buffer passed is big enough.
 *	RFC2138 says the password is max 128 chars, so the size
 *	of the passwd buffer must be at least 129 characters.
 *	Preferably it's just MAX_STRING_LEN.
 *
 *	int *pwlen is updated to the new length of the encrypted
 *	password - a multiple of 16 bytes.
 */
int rad_pwencode(char *passwd, size_t *pwlen, const char *secret,
		 const uint8_t *vector)
{
	FR_MD5_CTX context, old;
	uint8_t	digest[AUTH_VECTOR_LEN];
	int	i, n, secretlen;
	int	len;

	/*
	 *	RFC maximum is 128 bytes.
	 *
	 *	If length is zero, pad it out with zeros.
	 *
	 *	If the length isn't aligned to 16 bytes,
	 *	zero out the extra data.
	 */
	len = *pwlen;

	if (len > 128) len = 128;

	if (len == 0) {
		memset(passwd, 0, AUTH_PASS_LEN);
		len = AUTH_PASS_LEN;
	} else if ((len % AUTH_PASS_LEN) != 0) {
		memset(&passwd[len], 0, AUTH_PASS_LEN - (len % AUTH_PASS_LEN));
		len += AUTH_PASS_LEN - (len % AUTH_PASS_LEN);
	}
	*pwlen = len;

	/*
	 *	Use the secret to setup the decryption digest
	 */
	secretlen = strlen(secret);

	fr_MD5Init(&context);
	fr_MD5Update(&context, (const uint8_t *) secret, secretlen);
	old = context;		/* save intermediate work */

	/*
	 *	Encrypt it in place.  Don't bother checking
	 *	len, as we've ensured above that it's OK.
	 */
	for (n = 0; n < len; n += AUTH_PASS_LEN) {
		if (n == 0) {
			fr_MD5Update(&context, vector, AUTH_PASS_LEN);
			fr_MD5Final(digest, &context);
		} else {
			context = old;
			fr_MD5Update(&context,
				     (uint8_t *) passwd + n - AUTH_PASS_LEN,
				     AUTH_PASS_LEN);
			fr_MD5Final(digest, &context);
		}

		for (i = 0; i < AUTH_PASS_LEN; i++) {
			passwd[i + n] ^= digest[i];
		}
	}

	return 0;
}

/*
 *	Decode password.
 */
int rad_pwdecode(char *passwd, size_t pwlen, const char *secret,
		 const uint8_t *vector)
{
	FR_MD5_CTX context, old;
	uint8_t	digest[AUTH_VECTOR_LEN];
	int	i;
	size_t	n, secretlen;

	/*
	 *	The RFC's say that the maximum is 128.
	 *	The buffer we're putting it into above is 254, so
	 *	we don't need to do any length checking.
	 */
	if (pwlen > 128) pwlen = 128;

	/*
	 *	Catch idiots.
	 */
	if (pwlen == 0) goto done;

	/*
	 *	Use the secret to setup the decryption digest
	 */
	secretlen = strlen(secret);

	fr_MD5Init(&context);
	fr_MD5Update(&context, (const uint8_t *) secret, secretlen);
	old = context;		/* save intermediate work */

	/*
	 *	The inverse of the code above.
	 */
	for (n = 0; n < pwlen; n += AUTH_PASS_LEN) {
		if (n == 0) {
			fr_MD5Update(&context, vector, AUTH_VECTOR_LEN);
			fr_MD5Final(digest, &context);

			context = old;
			if (pwlen > AUTH_PASS_LEN) {
				fr_MD5Update(&context, (uint8_t *) passwd,
					     AUTH_PASS_LEN);
			}
		} else {
			fr_MD5Final(digest, &context);

			context = old;
			if (pwlen > (n + AUTH_PASS_LEN)) {
				fr_MD5Update(&context, (uint8_t *) passwd + n,
					     AUTH_PASS_LEN);
			}
		}

		for (i = 0; i < AUTH_PASS_LEN; i++) {
			passwd[i + n] ^= digest[i];
		}
	}

 done:
	passwd[pwlen] = '\0';
	return strlen(passwd);
}


/*
 *	Do a comparison of two authentication digests by comparing
 *	the FULL digest.  Otehrwise, the server can be subject to
 *	timing attacks that allow attackers find a valid message
 *	authenticator.
 *
 *	http://www.cs.rice.edu/~dwallach/pub/crosby-timing2009.pdf
 */
int rad_digest_cmp(const uint8_t *a, const uint8_t *b, size_t length)
{
	int result = 0;
	size_t i;

	for (i = 0; i < length; i++) {
		result |= a[i] ^ b[i];
	}

	return result;		/* 0 is OK, !0 is !OK, just like memcmp */
}


/*
 *	Validates the requesting client NAS.  Calculates the
 *	Request Authenticator based on the clients private key.
 */
static int calc_acctdigest(RADIUS_PACKET *packet, const char *secret)
{
	uint8_t		digest[AUTH_VECTOR_LEN];
	FR_MD5_CTX		context;

	/*
	 *	Zero out the auth_vector in the received packet.
	 *	Then append the shared secret to the received packet,
	 *	and calculate the MD5 sum. This must be the same
	 *	as the original MD5 sum (packet->vector).
	 */
	memset(packet->data + 4, 0, AUTH_VECTOR_LEN);

	/*
	 *  MD5(packet + secret);
	 */
	fr_MD5Init(&context);
	fr_MD5Update(&context, packet->data, packet->data_len);
	fr_MD5Update(&context, (const uint8_t *) secret, strlen(secret));
	fr_MD5Final(digest, &context);

	/*
	 *	Return 0 if OK, 2 if not OK.
	 */
	if (rad_digest_cmp(digest, packet->vector, AUTH_VECTOR_LEN) != 0) return 2;
	return 0;
}


/*
 *	Validates the requesting client NAS.  Calculates the
 *	Response Authenticator based on the clients private key.
 */
static int calc_replydigest(RADIUS_PACKET *packet, RADIUS_PACKET *original,
			    const char *secret)
{
	uint8_t		calc_digest[AUTH_VECTOR_LEN];
	FR_MD5_CTX		context;

	/*
	 *	Very bad!
	 */
	if (original == NULL) {
		return 3;
	}

	/*
	 *  Copy the original vector in place.
	 */
	memcpy(packet->data + 4, original->vector, AUTH_VECTOR_LEN);

	/*
	 *  MD5(packet + secret);
	 */
	fr_MD5Init(&context);
	fr_MD5Update(&context, packet->data, packet->data_len);
	fr_MD5Update(&context, (const uint8_t *) secret, strlen(secret));
	fr_MD5Final(calc_digest, &context);

	/*
	 *  Copy the packet's vector back to the packet.
	 */
	memcpy(packet->data + 4, packet->vector, AUTH_VECTOR_LEN);

	/*
	 *	Return 0 if OK, 2 if not OK.
	 */
	if (rad_digest_cmp(packet->vector, calc_digest, AUTH_VECTOR_LEN) != 0) return 2;
	return 0;
}


/*
 *	Verify the Request/Response Authenticator
 *	(and Message-Authenticator if present) of a packet.
 */
int rad_verify(RADIUS_PACKET *packet, RADIUS_PACKET *original,
	       const char *secret)
{
	uint8_t			*ptr;
	int			length;
	int			attrlen;

	if (!packet || !packet->data) return -1;

	/*
	 *	Before we allocate memory for the attributes, do more
	 *	sanity checking.
	 */
	ptr = packet->data + AUTH_HDR_LEN;
	length = packet->data_len - AUTH_HDR_LEN;
	while (length > 0) {
		uint8_t	msg_auth_vector[AUTH_VECTOR_LEN];
		uint8_t calc_auth_vector[AUTH_VECTOR_LEN];

		attrlen = ptr[1];

		switch (ptr[0]) {
		default:	/* don't do anything. */
			break;

			/*
			 *	Note that more than one Message-Authenticator
			 *	attribute is invalid.
			 */
		case RADIUS_MESSAGE_AUTHENTICATOR:
			memcpy(msg_auth_vector, &ptr[2], sizeof(msg_auth_vector));
			memset(&ptr[2], 0, AUTH_VECTOR_LEN);

			switch (packet->code) {
			default:
				break;

			case RADIUS_CODE_ACCNT_RESPONSE:
				if (original &&
				    (original->code ==
				    RADIUS_CODE_STATUS_SERVER)) {
					goto do_ack;
				}

			case RADIUS_CODE_ACCNT_REQUEST:
			  	memset(packet->data + 4, 0, AUTH_VECTOR_LEN);
				break;

			do_ack:
			case RADIUS_CODE_ACCESS_ACCEPT:
			case RADIUS_CODE_ACCESS_REJECT:
			case RADIUS_CODE_ACCESS_CHALLENGE:
				if (!original) {
printf("no original\n");
					return -1;
				}
				memcpy(packet->data + 4, original->vector, AUTH_VECTOR_LEN);
				break;
			}

			fr_hmac_md5(packet->data, packet->data_len,
				    (const uint8_t *) secret, strlen(secret),
				    calc_auth_vector);
			if (rad_digest_cmp(calc_auth_vector, msg_auth_vector,
				   sizeof(calc_auth_vector)) != 0) {
printf("invalid Message-Authenticator\n");
				/* Silently drop packet, according to RFC 3579 */
				return -1;
			} /* else the message authenticator was good */

			/*
			 *	Reinitialize Authenticators.
			 */
			memcpy(&ptr[2], msg_auth_vector, AUTH_VECTOR_LEN);
			memcpy(packet->data + 4, packet->vector, AUTH_VECTOR_LEN);
			break;
		} /* switch over the attributes */

		ptr += attrlen;
		length -= attrlen;
	} /* loop over the packet, sanity checking the attributes */

#if 0
	/*
	 *	It looks like a RADIUS packet, but we don't know what it is
	 *	so can't validate the authenticators.
	 */
	if ((packet->code == 0) || (packet->code >= FR_MAX_PACKET_CODE)) {
		char buffer[32];
		fr_strerror_printf("Received Unknown packet code %d "
			   "from client %s port %d: Cannot validate Request/Response Authenticator.",
			   packet->code,
			   inet_ntop(packet->src_ipaddr.af,
				     &packet->src_ipaddr.ipaddr,
				     buffer, sizeof(buffer)),
			   packet->src_port);
		return -1;
	}
#endif

	/*
	 *	Calculate and/or verify Request or Response Authenticator.
	 */
	switch(packet->code) {
		int rcode;
		case RADIUS_CODE_ACCESS_REQUEST:
		case RADIUS_CODE_STATUS_SERVER:
			/*
			 *	The authentication vector is random
			 *	nonsense, invented by the client.
			 */
			break;

		case RADIUS_CODE_ACCNT_REQUEST:
			if (calc_acctdigest(packet, secret) > 1) {
				return -1;
			}
			break;

			/* Verify the reply digest */
		case RADIUS_CODE_ACCESS_ACCEPT:
		case RADIUS_CODE_ACCESS_REJECT:
		case RADIUS_CODE_ACCESS_CHALLENGE:
		case RADIUS_CODE_ACCNT_RESPONSE:
			rcode = calc_replydigest(packet, original, secret);
			if (rcode > 1) {
printf("invalid respone authenticator\n");
				return -1;
			}
			break;

		default:
printf("unknown packet\n");
			return -1;
	}

	return 0;
}


/*
 *	Sign a previously encoded packet.
 */
int rad_sign(RADIUS_PACKET *packet, const RADIUS_PACKET *original,
	     const char *secret)
{
	struct radius_frame *hdr = (struct radius_frame *) packet->data;

	/*
	 *	If there's a Message-Authenticator, update it
	 *	now, BEFORE updating the authentication vector.
	 */
	if (packet->offset > 0) {
		uint8_t calc_auth_vector[AUTH_VECTOR_LEN];

		switch (packet->code) {
		case RADIUS_CODE_ACCNT_RESPONSE:
			if (original && original->code ==
			    RADIUS_CODE_STATUS_SERVER) {
				goto do_ack;
			}

		case RADIUS_CODE_ACCNT_REQUEST:
			memset(hdr->vector, 0, AUTH_VECTOR_LEN);
			break;

		do_ack:
		case RADIUS_CODE_ACCESS_ACCEPT:
		case RADIUS_CODE_ACCESS_REJECT:
		case RADIUS_CODE_ACCESS_CHALLENGE:
			if (!original) {
printf("no orginal\n");
				return -1;
			}
			memcpy(hdr->vector, original->vector,
			       AUTH_VECTOR_LEN);
			break;

		default:	/* others have vector already set to zero */
			break;

		}

		/*
		 *	Set the authentication vector to zero,
		 *	calculate the HMAC, and put it
		 *	into the Message-Authenticator
		 *	attribute.
		 */
		fr_hmac_md5(packet->data, packet->data_len,
			    (const uint8_t *) secret, strlen(secret),
			    calc_auth_vector);
		memcpy(packet->data + packet->offset + 2,
		       calc_auth_vector, AUTH_VECTOR_LEN);

		/*
		 *	Copy the original request vector back
		 *	to the raw packet.
		 */
		memcpy(hdr->vector, packet->vector, AUTH_VECTOR_LEN);
	}

	/*
	 *	Switch over the packet code, deciding how to
	 *	sign the packet.
	 */
	switch (packet->code) {
		/*
		 *	Request packets are not signed, bur
		 *	have a random authentication vector.
		 */
	case RADIUS_CODE_ACCESS_REQUEST:
	case RADIUS_CODE_STATUS_SERVER:
		break;

		/*
		 *	Reply packets are signed with the
		 *	authentication vector of the request.
		 */
	default:
		{
			uint8_t digest[16];

			FR_MD5_CTX	context;
			fr_MD5Init(&context);
			fr_MD5Update(&context, packet->data, packet->data_len);
			fr_MD5Update(&context, (const uint8_t *) secret,
				     strlen(secret));
			fr_MD5Final(digest, &context);

			memcpy(hdr->vector, digest, AUTH_VECTOR_LEN);
			memcpy(packet->vector, digest, AUTH_VECTOR_LEN);
			break;
		}
	}/* switch over packet codes */

	return 0;
}


int respond_eap_md5(struct radius_info *info)
{
	size_t valuesize;
	uint8_t identifier;
	uint8_t *value;
	FR_MD5_CTX context;
	uint8_t response[16];
	char *password = (char *) info->password;

	identifier = info->eap_id;
	valuesize = info->eap_data[0];
	value = &info->eap_data[1];

	/* now do the CHAP operation ourself, rather than build the
	 * buffer. We could also call rad_chap_encode, but it wants
	 * a CHAP-Challenge, which we don't want to bother with.
	 */
	fr_MD5Init(&context);
	fr_MD5Update(&context, &identifier, 1);
	fr_MD5Update(&context, (uint8_t *) password, strlen(password));
	fr_MD5Update(&context, value, valuesize);
	fr_MD5Final(response, &context);

	memcpy(value, response, 16);

	return 1;
}


void eap_md5(u8 id, char *password, u8 *eap_data, u8 *response)
{
	FR_MD5_CTX context;
	size_t valuesize;
	uint8_t *value;

	valuesize = eap_data[0];
	value = &eap_data[1];

	fr_MD5Init(&context);
	fr_MD5Update(&context, &id, 1);
	fr_MD5Update(&context, (uint8_t *) password, strlen(password));
	fr_MD5Update(&context, value, valuesize);
	fr_MD5Final(response, &context);
}

