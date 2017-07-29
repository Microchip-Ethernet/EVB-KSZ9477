/* ---------------------------------------------------------------------------
                     Copyright (c) 2007-2009 Micrel, Inc.
   ---------------------------------------------------------------------------
    Author      Date        Descriptions
    THa         01/12/07    Created file.
    THa         05/19/08    Update file.
    THa         01/20/09    Do not read file read/write to pass buffers.
   ---------------------------------------------------------------------------
*/


#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include "elpcrypto.h"
#include "elpipsec.h"
#include "elpipsechw.h"
#include "kszipsec.h"


/* ------------------------------------------------------------------------- */

#define CRYPTO_DEV_NAME  "/dev/crypto"
#define ESPAH_DEV_NAME   "/dev/espah"

/* ------------------------------------------------------------------------- */

#define MESSAGE_STR_LEN  160

static char message_str[ MESSAGE_STR_LEN ];

/* ------------------------------------------------------------------------- */

static int fn_crypto = 0;
static int fn_espah = 0;

void ExitDriver ( void )
{
    if ( fn_crypto ) {
        close( fn_crypto );
        fn_crypto = 0;
    }
    if ( fn_espah ) {
        close( fn_espah );
        fn_espah = 0;
    }
}  /* ExitDriver */


int InitDriver ( void )
{
    int result = -1;

    fn_crypto = open( CRYPTO_DEV_NAME, O_RDWR );
    if ( fn_crypto <= 0 )
        return( result );
    fn_espah = open( ESPAH_DEV_NAME, O_RDWR );
    if ( fn_espah <= 0 ) {
        close( fn_crypto );
        return( result );
    }
    result = 0;

    return( result );
}  /* InitDriver */

/* ------------------------------------------------------------------------- */

void dev_ioctl (
    int       fn,
    int       dev_ioc,
    PTRequest req,
    int*      pResult )
{
    int rc;

    req->nSize = sizeof( TRequest );
    if ( !( rc = ioctl( fn, dev_ioc, req ))  &&
            DEV_IOC_OK == req->nResult ) {
        *pResult = req->hwResult;
    }
}  /* dev_ioctl */

/* ------------------------------------------------------------------------- */

int crypto_close (
    int handle )
{
    TRequest req;
    int      result = CRYPTO_INVALID_HANDLE;

    if ( fn_crypto ) {
        req.handle = handle;
        req.nCmd = IPSEC_CLOSE;
        dev_ioctl( fn_crypto, DEV_IOC_SET, &req, &result );
    }
    return( result );
}  /* crypto_close */


int crypto_open (
    int algorithm,
    int mode )
{
    TRequest req;
    int      result = CRYPTO_INVALID_HANDLE;

    if ( fn_crypto ) {
        req.param.open.algorithm = algorithm;
        req.param.open.mode = mode;
        req.nCmd = IPSEC_OPEN;
        dev_ioctl( fn_crypto, DEV_IOC_SET, &req, &result );
    }
    return( result );
}  /* crypto_open */

/* ------------------------------------------------------------------------- */

char* crypto_error_msg (
    int err )
{
    TRequest req;

    if ( fn_crypto ) {
        req.param.Mem.nMsg = err;
        req.param.Mem.nLen = MESSAGE_STR_LEN;
        req.param.Mem.pBuf = message_str;
        req.nCmd = IPSEC_ERROR_MSG;

        req.nSize = sizeof( TRequest );
        if ( ioctl( fn_crypto, DEV_IOC_STR, &req )  ||
                DEV_IOC_OK != req.nResult ) {
            message_str[ 0 ] = '?';
            message_str[ 1 ] = '\0';
        }
    }
    return ( message_str );
}  /* crypto_error_msg */


char* crypto_get_version ( void )
{
    TRequest req;

    if ( fn_crypto ) {
        req.param.Mem.nLen = MESSAGE_STR_LEN;
        req.param.Mem.pBuf = message_str;
        req.nCmd = IPSEC_VERSION_STR;

        req.nSize = sizeof( TRequest );
        if ( ioctl( fn_crypto, DEV_IOC_STR, &req )  ||
                DEV_IOC_OK != req.nResult ) {
            message_str[ 0 ] = '\0';
        }
    }
    return ( message_str );
}  /* crypto_get_version */

/* ------------------------------------------------------------------------- */

static void crypto_context (
    PTRequest      req,
    int            handle,
    unsigned char* key,
    int            keysize,
    unsigned char* iv,
    int            ivsize,
    int            psize )
{
    req->handle = handle;
    req->param.crypto.key = key;
    req->param.crypto.keysize = keysize;
    req->param.crypto.iv = iv;
    req->param.crypto.ivsize = ivsize;
    req->param.crypto.psize = psize;
    req->nCmd = IPSEC_CONTEXT;
}  /* crypto_context */


int crypto_get_context (
    int            handle,
    unsigned char* iv,
    int*           ivsize,
    int*           psize )
{
    TRequest req;
    int      keysize = 0;
    int      result = CRYPTO_INVALID_HANDLE;

    if ( fn_crypto ) {
	if ( psize )
	    keysize = *psize;
        crypto_context( &req, handle, NULL, 0, iv, *ivsize, keysize );
        dev_ioctl( fn_crypto, DEV_IOC_GET, &req, &result );
        if ( CRYPTO_OK == result ) {
            *ivsize = req.param.crypto.ivsize;
	    if ( psize )
		*psize = req.param.crypto.psize;
        }
    }
    return( result );
}  /* crypto_get_context */


int crypto_set_context (
    int            handle,
    unsigned char* key,
    int            keysize,
    unsigned char* iv,
    int            ivsize,
    int            psize )
{
    TRequest req;
    int      result = CRYPTO_INVALID_HANDLE;

    if ( fn_crypto ) {
        crypto_context( &req, handle, key, keysize, iv, ivsize, psize );
        dev_ioctl( fn_crypto, DEV_IOC_SET, &req, &result );
    }
    return( result );
}  /* crypto_set_context */


static int crypto_wait (
    int            algorithm,
    int            handle,
    int            decrypt,
    unsigned char* pt,
    int            ptsize,
    unsigned char* out,
    int*           outsize,
    int            wait )
{
    TRequest req;
    int      result = CRYPTO_INVALID_HANDLE;

    if ( fn_crypto ) {
        if ( out  &&  !outsize )
            return CRYPTO_INVALID_ARGUMENT;

        req.handle = handle;
        req.param.crypto.algorithm = algorithm;
        req.param.crypto.decrypt = decrypt;
        req.param.crypto.key = pt;
        req.param.crypto.keysize = ptsize;
        req.param.crypto.iv = out;
        if ( out )
            req.param.crypto.ivsize = *outsize;
        else
            req.param.crypto.ivsize = 0;
        req.param.crypto.wait = wait;
        req.nCmd = IPSEC_WAIT;
        dev_ioctl( fn_crypto, DEV_IOC_GET, &req, &result );
        if ( CRYPTO_OK == result ) {
            if ( out )
                *outsize = req.param.crypto.ivsize;
        }
    }
    return( result );
}  /* crypto_wait */


int crypto_aes_wait_ (
    int            handle,
    int            decrypt,
    unsigned char* pt,
    int            ptsize,
    unsigned char* out,
    int*           outsize,
    int            wait )
{
    return( crypto_wait( ALG_AES,
	handle, decrypt, pt, ptsize, out, outsize, wait ));
}  /* crypto_aes_wait_ */


int crypto_des_wait_ (
    int            handle,
    int            decrypt,
    unsigned char* pt,
    int            ptsize,
    unsigned char* out,
    int*           outsize,
    int            wait )
{
    return( crypto_wait( ALG_DES,
	handle, decrypt, pt, ptsize, out, outsize, wait ));
}  /* crypto_des_wait_ */


int _ssl_mac (
    int            handle,
    unsigned char  protocol,
    int            sequence,
    unsigned char* key,
    unsigned char* pt,
    int            ptsize,
    unsigned char* out,
    int            outsize )
{
    TRequest req;
    int      result = CRYPTO_INVALID_HANDLE;

    if ( fn_crypto ) {

        req.handle = handle;
        req.param.ssl.protocol = protocol;
        req.param.ssl.sequence = sequence;
        req.param.ssl.key = key;
        req.param.ssl.pt = pt;
        req.param.ssl.ptsize = ptsize;
        req.param.ssl.out = out;
        req.param.ssl.outsize = outsize;
        req.nCmd = IPSEC_SSL;
        dev_ioctl( fn_crypto, DEV_IOC_GET, &req, &result );
    }
    return( result );
}  /* _ssl_mac */


int crypto_hmac_wait_ (
    int            handle,
    unsigned char* pt,
    int            ptsize,
    unsigned char* out,
    int*           outsize,
    int            wait )
{
    return( crypto_wait( ALG_HMAC,
	handle, 0, pt, ptsize, out, outsize, wait ));
}  /* crypto_hmac_wait_ */


int crypto_rc4_wait_ (
    int            handle,
    unsigned char* pt,
    int            ptsize,
    unsigned char* out,
    int*           outsize,
    int            wait )
{
    return( crypto_wait( ALG_RC4,
	handle, 0, pt, ptsize, out, outsize, wait ));
}  /* crypto_rc4_wait_ */

/* ------------------------------------------------------------------------- */

char* espah_error_msg (
    int err )
{
    TRequest req;

    if ( fn_espah ) {
        req.param.Mem.nMsg = err;
        req.param.Mem.nLen = MESSAGE_STR_LEN;
        req.param.Mem.pBuf = message_str;
        req.nCmd = IPSEC_ERROR_MSG;

        req.nSize = sizeof( TRequest );
        if ( ioctl( fn_espah, DEV_IOC_STR, &req )  ||
                DEV_IOC_OK != req.nResult ) {
            message_str[ 0 ] = '?';
            message_str[ 1 ] = '\0';
        }
    }
    return ( message_str );
}  /* espah_error_msg */


char* espah_get_version ( void )
{
    TRequest req;

    if ( fn_espah ) {
        req.param.Mem.nLen = MESSAGE_STR_LEN;
        req.param.Mem.pBuf = message_str;
        req.nCmd = IPSEC_VERSION_STR;

        req.nSize = sizeof( TRequest );
        if ( ioctl( fn_espah, DEV_IOC_STR, &req )  ||
                DEV_IOC_OK != req.nResult ) {
            message_str[ 0 ] = '\0';
        }
    }
    return ( message_str );
}  /* espah_get_version */

/* ------------------------------------------------------------------------- */

int espah_close (
    int handle )
{
    TRequest req;
    int      result = ESPAH_INVALID_HANDLE;

    if ( fn_espah ) {
        req.handle = handle;
        req.nCmd = IPSEC_CLOSE;
        dev_ioctl( fn_espah, DEV_IOC_SET, &req, &result );
    }
    return( result );
}  /* espah_close */


int espah_open (
    int algorithm,
    int mode )
{
    TRequest req;
    int      result = ESPAH_INVALID_HANDLE;

    if ( fn_espah ) {
        req.param.open.algorithm = algorithm;
        req.param.open.mode = mode;
        req.nCmd = IPSEC_OPEN;
        dev_ioctl( fn_espah, DEV_IOC_SET, &req, &result );
    }
    return( result );
}  /* espah_open */


static void espah_context (
    PTRequest      req,
    int            handle,
    int            direction,
    unsigned char* SA )
{
    req->handle = handle;
    req->param.espah.SA = SA;
    req->param.espah.direction = direction;
    req->nCmd = IPSEC_CONTEXT;
}  /* espah_context */


int espah_get_context (
    int            handle,
    int            direction,
    unsigned char* SA )
{
    TRequest req;
    int      result = ESPAH_INVALID_HANDLE;

    if ( fn_espah ) {
        espah_context( &req, handle, direction, SA );
        dev_ioctl( fn_espah, DEV_IOC_GET, &req, &result );
    }
    return( result );
}  /* espah_get_context */


int espah_set_context (
    int                  handle,
    int                  direction,
    const unsigned char* SA )
{
    TRequest req;
    int      result = ESPAH_INVALID_HANDLE;

    if ( fn_espah ) {
        espah_context( &req, handle, direction, ( unsigned char* ) SA );
        dev_ioctl( fn_espah, DEV_IOC_SET, &req, &result );
    }
    return( result );
}  /* espah_set_context */


int espah_wait (
    int            handle,
    int            direction,
    unsigned char* pt,
    int            ptsize,
    unsigned char* out,
    int*           outsize,
    int            wait )
{
    TRequest req;
    int      result = ESPAH_INVALID_HANDLE;

    if ( fn_espah ) {
        if ( out  &&  !outsize )
            return CRYPTO_INVALID_ARGUMENT;

        req.handle = handle;
        req.param.espah.direction = direction;
        req.param.espah.pt = pt;
        req.param.espah.ptsize = ptsize;
        req.param.espah.out = out;
        if ( out )
            req.param.espah.outsize = *outsize;
        else
            req.param.espah.outsize = 0;
        req.param.espah.wait = wait;
        req.nCmd = IPSEC_WAIT;
        dev_ioctl( fn_espah, DEV_IOC_GET, &req, &result );
        if ( CRYPTO_OK == result ) {
            if ( out )
                *outsize = req.param.espah.outsize;
        }
    }
    return( result );
}  /* espah_wait */

/* ------------------------------------------------------------------------- */

#ifdef TEST

#ifdef TEST_ESPAH
static U32 opcode = 0x00000010;
static U32 insize = 0x00000068;
static U32 outsize = 0x00000098;
static U32 retcode = 0x00000000;

static U32 SA[ 256 / 4 ] = {
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x9BBFA117,
0xD749E032,
0x9FC0E371,
0x7A8CDC6C,
0x0E5FAB28,
0x291EEB30,
0x7E904E29,
0xD5C2827E,
0x5FC3D76B,
0xDA7E3D23,
0x32435E4C,
0x14C83847,
0xD93F886C,
0xF854C27C,
0x8DE7E81B,
0x632E5A76,
0x9AC99F33,
0x7F79A367,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00020000,
0x80E51000,
0x00000000,
0x80E51000,
0x00000000,
0x21000052,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
0x00000000,
};

static U32 inbuf[ 0x68 / 4 ] = {
0x68000045,
0x00400000,
0xAEA80440,
0x0E08A8C0,
0x8508A8C0,
0x54000045,
0x00400000,
0xF2D70140,
0x0E0510AC,
0x880510AC,
0xF69C0008,
0x01000BE6,
0x433C0DBE,
0x0009A886,
0x0B0A0908,
0x0F0E0D0C,
0x13121110,
0x17161514,
0x1B1A1918,
0x1F1E1D1C,
0x23222120,
0x27262524,
0x2B2A2928,
0x2F2E2D2C,
0x33323130,
0x37363534,
};

static U32 outbuf[ 0x98 / 4 ] = {
0x98000045,
0x00400000,
0x50A83240,
0x0E08A8C0,
0x8508A8C0,
0x7F79A367,
0x01000000,
0xF854C27C,
0x8DE7E81B,
0x632E5A76,
0x9AC99F33,
0xEC097C5E,
0x762DB5E1,
0xB72650E8,
0xC8E2B9C4,
0xE2084906,
0xA75F0C4E,
0x9E02C102,
0x6C772129,
0x54E5A746,
0x2C922265,
0xC80D52FD,
0xF88F34B1,
0x7F51DE9C,
0x0FF0D40F,
0x9A07E18C,
0xEFA1E8F8,
0x874980CE,
0x4A7C3180,
0x33DC889F,
0x015D2299,
0x64BF077D,
0x5082D9F2,
0x84300A3F,
0x3326F8D2,
0xF9C9FC1C,
0x51A04AD7,
0x42051671,
};
#endif

#ifdef TEST_CIPHER
static int cipher = 1;
static int mode = 0;
static int keysize = 8;
static int ptsize = 64;
static int encmode = 0;

static U32 KEY[ 0x2 ] = {
0xE5A5645B,
0xBE716687,
};

static U32 IV[ 0x2 ] = {
0xAABE6BFB,
0xD15CF0E1,
};

static U32 PT[ 0x40 / 4 ] = {
0x40978BB5,
0x6F2CFCAE,
0xC110ED2C,
0x59498F5E,
0xDC0407FA,
0x53AD60F7,
0x4B3852C4,
0x6E09A9B8,
0xE3AEA135,
0xC953DA9D,
0x258B63C7,
0xED7FD4F2,
0xD3C983DB,
0xA72676E3,
0x80F25EC8,
0x3CEEFC07,
};

static U32 CT[ 0x40 / 4 ] = {
0xC29A5A6D,
0xEB3450D1,
0x248423CA,
0x8EF66A66,
0xB5FC0808,
0xEDF1E73A,
0x6965F82B,
0xA565050F,
0xC316983F,
0xF52A9C18,
0x9F65C489,
0x69640553,
0x6DC0488D,
0x8B267392,
0x04011F97,
0x804E06D6,
};


static int context_modes[][ 3 ] = {
	{ CRYPTO_MODE_AES_ECB, CRYPTO_MODE_AES_CBC, CRYPTO_MODE_AES_CTR },
	{ CRYPTO_MODE_DES_ECB, CRYPTO_MODE_DES_CBC, 0 },
	{ CRYPTO_MODE_3DES_ECB, CRYPTO_MODE_3DES_CBC, 0 },
};
static int context_values[] = {
	CRYPTO_CONTEXT_AES, CRYPTO_CONTEXT_DES, CRYPTO_CONTEXT_DES
};
static char* cipher_names[] = { "AES", "DES", "3DES" };
static char* mode_names[] = { "ECB", "CBC", "CTR" };

#endif

#ifdef TEST_HMAC
static int hash = 1;
static int mode = 1;
static int keysize = 20;
static int ptsize = 64;
static int protocol = 0;
static int sequence = 0;

static U32 KEY[ 0x5 ] = {
0xFB877E71,
0xE1AABE6B,
0x5BD15CF0,
0x87E5A564,
0xB5BE7166,
};

static U32 PT[ 0x40 / 4 ] = {
0xAE40978B,
0x2C6F2CFC,
0x5EC110ED,
0xFA59498F,
0xF7DC0407,
0xC453AD60,
0xB84B3852,
0x356E09A9,
0x9DE3AEA1,
0xC7C953DA,
0xF2258B63,
0xDBED7FD4,
0xE3D3C983,
0xC8A72676,
0x0780F25E,
0x9D3CEEFC,
};

static U32 CT[ 0x5 ] = {
0x7D68778E,
0xBD653E6C,
0x333F5DB8,
0x9DD401BC,
0x6252CF61,
};

static int context_modes[][ 4 ] = {
	{ CRYPTO_MODE_MD5, CRYPTO_MODE_HMAC_MD5,
	CRYPTO_MODE_SSLMAC_MD5, CRYPTO_MODE_TLSMAC_MD5 },
	{ CRYPTO_MODE_SHA1, CRYPTO_MODE_HMAC_SHA1,
	CRYPTO_MODE_SSLMAC_SHA1, CRYPTO_MODE_TLSMAC_SHA1 },
	{ CRYPTO_MODE_SHA256, CRYPTO_MODE_HMAC_SHA256, 0, 0 },
	{ CRYPTO_MODE_SHA512, CRYPTO_MODE_HMAC_SHA512, 0, 0 },
};
static char* mode_names[] = { "HASH", "HMAC", "SSLMAC", "TLSMAC" };
static char* hash_names[] = { "MD5", "SHA1", "SHA256", "SHA512" };

#endif

#ifdef TEST_SSL
static int hash = 0;
static int mode = 2;
static int keysize = 16;
static int ptsize = 1;
static int protocol = 22;
static int sequence = 1;

static U32 KEY[ 0x4 ] = {
0xFF517369,
0xCD29EC4A,
0xFBF2ABBA,
0xC27C46E3,
};

static U32 PT[ 0x4 / 4 ] = {
0x00000054,
};

static U32 CT[ 0x4 ] = {
0xF0733B77,
0xE6888C38,
0x3F23E8E8,
0xFAED8893,
};

static int context_modes[][ 4 ] = {
	{ CRYPTO_MODE_MD5, CRYPTO_MODE_HMAC_MD5,
	CRYPTO_MODE_SSLMAC_MD5, CRYPTO_MODE_TLSMAC_MD5 },
	{ CRYPTO_MODE_SHA1, CRYPTO_MODE_HMAC_SHA1,
	CRYPTO_MODE_SSLMAC_SHA1, CRYPTO_MODE_TLSMAC_SHA1 },
	{ CRYPTO_MODE_SHA256, CRYPTO_MODE_HMAC_SHA256, 0, 0 },
	{ CRYPTO_MODE_SHA512, CRYPTO_MODE_HMAC_SHA512, 0, 0 },
};
static char* mode_names[] = { "HASH", "HMAC", "SSLMAC", "TLSMAC" };
static char* hash_names[] = { "MD5", "SHA1", "SHA256", "SHA512" };

#endif

#ifdef TEST_RC4
static int keysize = 5;
static int ptsize = 4;

static unsigned int KEY[ 0x2 ] = {
0x9D7257A5,
0x000000EC,
};

static unsigned int PT[ 0x4 / 4 ] = {
0xB824CAE6,
};

static unsigned int CT[ 0x4 / 4 ] = {
0xDA077E24,
};
#endif


int main (
    int   argc,
    char* argv[] )
{
    int err;
    int handle;

#ifdef TEST_ESPAH
    int routsize;
    unsigned char routbuf[ 2000 ];

#else
    int outsize;
    unsigned char outbuf[ 2000 ];
    unsigned char* pt = ( unsigned char* ) PT;
    unsigned char* ct = ( unsigned char* ) CT;
    unsigned char* key = ( unsigned char* ) KEY;
#endif

#ifdef TEST_CIPHER
    int algmode;
    unsigned char* iv = ( unsigned char* ) IV;
    int ( *crypto_wait )( int, int, unsigned char*, int,
        unsigned char*, int*, int );
#endif

#if defined( TEST_HMAC ) || defined( TEST_SSL )
    int algmode;
#endif

    InitDriver();

#ifdef TEST_ESPAH
    printf( "version: %s\n", espah_get_version());

    handle = espah_open( 0, ESPAH_MODE_DEFAULT );
    if ( handle < 0 ) {
        printf( "espah_open: %s\n", espah_error_msg( handle ));
        return 1;
    }
    err = espah_set_context( handle, opcode == 0x11 ?
        ESPAH_INBOUND_DIRECTION : ESPAH_OUTBOUND_DIRECTION,
        ( unsigned char* ) SA );
    if ( err != ESPAH_OK ) {
        printf( "espah_set_context: %s\n", espah_error_msg( err ));
        return 1;
    }
    routsize = sizeof( routbuf );
    err = espah_wait( handle, opcode == 0x11 ?
        ESPAH_INBOUND_DIRECTION : ESPAH_OUTBOUND_DIRECTION,
        ( unsigned char* ) inbuf, insize, routbuf, &routsize, 1 );
    if ( err != ESPAH_OK ) {
        printf( "espah_wait: %s\n", espah_error_msg( err ));
        return 1;
    }
    espah_close( handle );
    printf( "%u=%08x:%u=%08x\n", ( unsigned int ) outsize,
        *(( unsigned int* ) &outbuf[ 0 ]),
        routsize, *(( unsigned int* ) routbuf ));
#endif

#ifndef TEST_ESPAH
#if 0
    printf( "version: %s\n", crypto_get_version());
#endif

#ifdef TEST_CIPHER
    algmode = context_modes[ cipher ][ mode ];

    handle = crypto_open( context_values[ cipher ], algmode );
    if ( handle < 0 ) {
        printf( "crypto_open: %s\n", crypto_error_msg( err ));
        return 1;
    }
    err = crypto_set_context( handle, key, keysize, iv,
        cipher == 0 ? 16 : 8, 0 );
    if ( err != CRYPTO_OK ) {
        printf( "crypto_set_context: %s\n", crypto_error_msg( err ));
        return 1;
    }
    outsize = sizeof( outbuf );
    if ( cipher == 0 )
        crypto_wait = crypto_aes_wait_;
    else
        crypto_wait = crypto_des_wait_;
    err = crypto_wait( handle, encmode, pt, ptsize, outbuf, &outsize, 1 );
    if ( err != CRYPTO_OK ) {
        printf( "crypto_wait: %s\n", crypto_error_msg( err ));
        return 1;
    }
    printf( "CIPHER: %4s-%-3s KEY:%3d DATA:%3d %s\n",
        cipher_names[ cipher ], mode_names[ mode ], keysize, ptsize,
        encmode == 1 ? "DECRYPT" : "ENCRYPT" );
#endif

#if defined( TEST_HMAC ) || defined( TEST_SSL )
    algmode = context_modes[ hash ][ mode ];

    handle = crypto_open( CRYPTO_CONTEXT_HMAC, algmode );
    if ( handle < 0 ) {
        printf( "crypto_open: %s\n", crypto_error_msg( err ));
        return 1;
    }
    outsize = keysize;
    if ( mode >= 2 ) {
        err = _ssl_mac( handle, protocol, sequence, key, pt, ptsize, outbuf,
            outsize );
        if ( err < 0 ) {
            printf( "_ssl_mac: %s\n", crypto_error_msg( err ));
            return 1;
        }
    }
    else {
	err = crypto_set_context( handle, key, keysize, 0, 0, 0 );
        if ( err != CRYPTO_OK ) {
            printf( "crypto_set_context: %s\n", crypto_error_msg( err ));
            return 1;
        }
        err = crypto_hmac_wait_( handle, pt, ptsize, outbuf, &outsize, 1 );
        if ( err != CRYPTO_OK ) {
            printf( "crypto_wait: %s\n", crypto_error_msg( err ));
            return 1;
        }
    }
    printf( "HASH: %4s-%-4s DATA:%4d\n",
        hash_names[ hash ], mode_names[ mode ], ptsize );
#endif

#ifdef TEST_RC4
    handle = crypto_open( CRYPTO_CONTEXT_RC4, CRYPTO_MODE_RC4_40 );
    if ( handle < 0 ) {
        printf( "crypto_open: %s\n", crypto_error_msg( err ));
        return 1;
    }
    err = crypto_set_context( handle, key, keysize, 0, 0, 0 );
    if ( err != CRYPTO_OK ) {
        printf( "crypto_set_context: %s\n", crypto_error_msg( err ));
        return 1;
    }
    outsize = sizeof( outbuf );
    err = crypto_rc4_wait_( handle, pt, ptsize, outbuf, &outsize, 1 );
    if ( err != CRYPTO_OK ) {
        printf( "crypto_wait: %s\n", crypto_error_msg( err ));
        return 1;
    }
    printf( "CIPHER: RC4_%s DATA:%4d\n",
        ( keysize == 5 ) ? "40 " : "128", ptsize );
#endif
    crypto_close( handle );
    printf( "%08x:%08x\n", *(( unsigned int* ) &ct[ 0 ]),
        *(( unsigned int* ) outbuf ));
#endif

    ExitDriver();
    return 0;
}
#endif
