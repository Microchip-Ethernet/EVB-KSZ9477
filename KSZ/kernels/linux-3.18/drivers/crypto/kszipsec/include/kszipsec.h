/* ---------------------------------------------------------------------------
                     Copyright (c) 2007-2009 Micrel, Inc.
   ---------------------------------------------------------------------------
    Author      Date        Descriptions
    THa         01/12/07    Created file.
    THa         01/20/09    Do not read file read/write to pass buffers.
   ---------------------------------------------------------------------------
*/


#ifndef _KSZIPSEC_H
#define _KSZIPSEC_H


typedef struct {
    int   nLen;
    int   nMsg;
    char* pBuf;
} TMem, *PTMem;


typedef struct {
    int algorithm;
    int mode;
} TOpen, *PTOpen;


typedef struct {
    unsigned char* SA;
    int            direction;
    unsigned char* pt;
    int            ptsize;
    unsigned char* out;
    int            outsize;
    int            wait;
} TESPAH, *PTESPAH;


enum {
    ALG_AES,
    ALG_DES,
    ALG_HMAC,
    ALG_RC4
};

#define CRYPTO_ENCRYPT  0
#define CRYPTO_DECRYPT  1

typedef struct {
    int            algorithm;
    int            decrypt;
    unsigned char* key;
    int            keysize;
    unsigned char* iv;
    int            ivsize;
    int            psize;
    int            wait;
} TCrypto, *PTCrypto;


typedef struct {
    int            protocol;
    int            sequence;
    unsigned char* key;
    unsigned char* pt;
    int            ptsize;
    unsigned char* out;
    int            outsize;
} TSSL, *PTSSL;


enum {
    IPSEC_OPEN,
    IPSEC_CLOSE,
    IPSEC_CONTEXT,
    IPSEC_WAIT,
    IPSEC_ERROR_MSG,
    IPSEC_VERSION_STR,
    IPSEC_SSL,
};


enum {
    DEV_IOC_OK,
    DEV_IOC_INVALID_SIZE,
    DEV_IOC_INVALID_CMD,
    DEV_IOC_INVALID_LEN
};

typedef struct {
    int   nSize;
    int   nCmd;
    int   nResult;

    int   handle;
    int   hwResult;
    union {
        TMem    Mem;
        TCrypto crypto;
        TESPAH  espah;
        TOpen   open;
        TSSL    ssl;
    } param;
} TRequest, *PTRequest;


#define DEV_IOC_MAGIC  0x92

#define DEV_IOC_STR  _IOR( DEV_IOC_MAGIC, 1, TRequest )
#define DEV_IOC_GET  _IOR( DEV_IOC_MAGIC, 2, TRequest )
#define DEV_IOC_SET  _IOW( DEV_IOC_MAGIC, 3, TRequest )

#define DEV_IOC_MAX  3


void ExitDriver ( void );
int InitDriver ( void );


#endif
