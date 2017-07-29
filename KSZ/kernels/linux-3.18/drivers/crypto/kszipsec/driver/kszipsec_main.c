/* ---------------------------------------------------------------------------
                     Copyright (c) 2007-2011 Micrel, Inc.
   ---------------------------------------------------------------------------
    Author      Date        Descriptions
    THa         01/11/07    Created file.
    THa         04/05/07    Add AES, DES, and 3DES crypto support.
    THa         06/06/07    Fix decrypt problem.
    THa         08/28/07    Update for Linux 2.6.21 kernel.
    THa         11/27/07    Add IPsec interrupt support.
    THa         02/26/08    Use IPsec interrupt to signal completion.
    THa         01/20/09    Do not read file read/write to pass buffers.
   ---------------------------------------------------------------------------
*/


#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/version.h>
#include <linux/dma-mapping.h>
#include <linux/fs.h>
#include <linux/ioctl.h>
#include <linux/crypto.h>
#include <linux/interrupt.h>
#include <asm/uaccess.h>
#include <asm/io.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Micrel, Inc. <www.micrel.com>");
MODULE_DESCRIPTION("Micrel Pegasus IPsec driver");

MODULE_ALIAS("crypto-pegasus");

#include "elpcrypto.h"
#include "elpipsec.h"
#include "elpipsechw.h"
#include "kszipsec.h"

#ifdef CONFIG_KSZIPSEC_USE_INTR
#include <linux/kthread.h>
#include <linux/skbuff.h>
#endif

#define CRYPTO_MODULE_ALL  \
    ( CRYPTO_MODULE_AES | CRYPTO_MODULE_DES | CRYPTO_MODULE_HMAC | CRYPTO_MODULE_RC4 )

extern espah_module _espah_module;

unsigned char* ksz_in;
unsigned char* ksz_in_outbound;
unsigned char* ksz_out;
unsigned char* ksz_out_outbound;
unsigned char* ksz_rinbuf;
unsigned char* ksz_rinbuf_outbound;
unsigned char* ksz_routbuf;
unsigned char* ksz_routbuf_outbound;
unsigned short ksz_thread_id = 0;

#ifdef CONFIG_KSZIPSEC_USE_INTR
volatile int espah_in_intr = 1;
volatile int espah_out_intr = 1;

EXPORT_SYMBOL(espah_in_intr);
EXPORT_SYMBOL(espah_out_intr);
#endif

EXPORT_SYMBOL(ksz_in);
EXPORT_SYMBOL(ksz_in_outbound);
EXPORT_SYMBOL(ksz_out);
EXPORT_SYMBOL(ksz_out_outbound);
EXPORT_SYMBOL(ksz_rinbuf);
EXPORT_SYMBOL(ksz_rinbuf_outbound);
EXPORT_SYMBOL(ksz_routbuf);
EXPORT_SYMBOL(ksz_routbuf_outbound);
EXPORT_SYMBOL(ksz_thread_id);

/* ------------------------------------------------------------------------- */

static int   dev_major = 0;
static char* ksz_dev_name = "pegasus-ipsec";

#ifdef CONFIG_KSZIPSEC_USE_INTR
static char* intr_name = "ipsec";
#endif


enum {
    SEM_CRYTPO,
    SEM_ESPAH,
    SEM_LAST
};

typedef struct {
    struct semaphore sem;

    int              nType;

    int              nLen;
    unsigned char*   pBuf;
    unsigned char*   pKey;

    int              nIn;
    int              nInSize;
    unsigned char*   pIn;
    unsigned char*   pbIn;

    int              nOut;
    int              nOutSize;
    unsigned char*   pOut;
    unsigned char*   pbOut;
} TDevInfo, *PTDevInfo;


static TDevInfo gDev[ SEM_LAST ];


typedef struct _handle_ptr {
    int                 handle;
    struct _handle_ptr* next;
} THandlePtr, *PTHandlePtr;

#define MAX_HANDLE_NUM  (ESPAH_HANDLES_MAX - 1)

typedef struct {
    unsigned char* pbIn;
    unsigned char* pbOut;

    PTDevInfo  pInfo;

    THandlePtr handles[ MAX_HANDLE_NUM ];
    THandlePtr free_handles;
    THandlePtr used_handles;
} TCharDev, *PTCharDev;

/* ------------------------------------------------------------------------- */

static int dev_open (
    struct inode* inode,
    struct file*  filp )
{
    PTCharDev    dev = ( PTCharDev ) filp->private_data;
    unsigned int minor = MINOR( inode->i_rdev );

    if ( !dev ) {
        dev = kmalloc( sizeof( TCharDev ), GFP_KERNEL );
        if ( dev ) {
            int i;

            memset( dev, 0, sizeof( TCharDev ));
            for ( i = 0; i < MAX_HANDLE_NUM; i++ ) {
                dev->handles[ i ].handle = -1;
                dev->handles[ i ].next = dev->free_handles.next;
                dev->free_handles.next = &dev->handles[ i ];
            }
            dev->free_handles.handle = MAX_HANDLE_NUM;

            dev->pInfo = &gDev[ minor ];
            filp->private_data = dev;
        }
        else
            return -ENOMEM;
    }
    return 0;
}  /* dev_open */


static int dev_release (
    struct inode* inode,
    struct file*  filp )
{
    PTCharDev   dev = ( PTCharDev ) filp->private_data;
    PTHandlePtr ptr;

    if ( dev ) {
        while ( dev->used_handles.handle ) {
            ptr = dev->used_handles.next;
            if ( SEM_ESPAH == dev->pInfo->nType )
                espah_close( ptr->handle );
            else
                crypto_close( ptr->handle );
            dev->used_handles.next = ptr->next;
            --dev->used_handles.handle;
        }
        kfree( dev );
    }
    filp->private_data = NULL;
    return 0;
}  /* dev_release */


static int alloc_buf (
    int             bufsize,
    unsigned char** pBuf,
    int*            nBufSize,
    unsigned char** pInput )
{
    if ( *nBufSize != 0  &&  bufsize > *nBufSize ) {
        kfree( *pBuf );
        *pBuf = NULL;
        *nBufSize = 0;
    }
    if ( !*pBuf ) {
        *nBufSize = ( bufsize + 3 ) & ~3;
        *pBuf = kmalloc( *nBufSize, GFP_KERNEL );
        if ( !*pBuf ) {
            *nBufSize = 0;
            return -ENOMEM;
        }
    }
    *pInput = *pBuf;
    return 0;
}  /* alloc_buf */


static int get_crypto_param (
    PTDevInfo dev,
    int*      algorithm,
    int*      mode,
    int*      wait,
    PTRequest pReq )
{
    __get_user( *algorithm, &pReq->param.crypto.algorithm );
    __get_user( *mode, &pReq->param.crypto.decrypt );
    __get_user( *wait, &pReq->param.crypto.wait );
#ifdef DEBUG
    printk( " >%d, %d, %d\n", *algorithm, *mode, *wait );
#endif

    __get_user( dev->pIn, &pReq->param.crypto.key );
    __get_user( dev->nIn, &pReq->param.crypto.keysize );
    __get_user( dev->pOut, &pReq->param.crypto.iv );
    __get_user( dev->nOut, &pReq->param.crypto.ivsize );
#ifdef DEBUG
    printk( " >%d %p\n", dev->nIn, dev->pIn );
    printk( " >%d %p\n", dev->nOut, dev->pOut );
#endif

    /* An input buffer is passed. */
    if ( dev->pIn ) {
        if ( alloc_buf( dev->nIn, &dev->pbIn, &dev->nInSize, &dev->pIn ) )
            return -ENOMEM;

        /* buffer is not empty. */
        if ( dev->nIn ) {
            if ( !access_ok( VERIFY_READ, pReq->param.crypto.key, dev->nIn )
                    ||  copy_from_user( dev->pIn, pReq->param.crypto.key,
                    dev->nIn ) ) {
                return -EFAULT;
            }
        }
    }

    /* An output buffer is passed. */
    if ( dev->pOut ) {
        if ( alloc_buf( dev->nOut, &dev->pbOut, &dev->nOutSize, &dev->pOut ) )
            return -ENOMEM;
    }
    return 0;
}  /* get_crypto_param */


static int set_crypto_param (
    PTDevInfo dev,
    PTRequest pReq )
{
    /* An output buffer is passed. */
    if ( dev->pOut ) {
        if ( !access_ok( VERIFY_WRITE, pReq->param.crypto.iv, dev->nOut )  ||
                copy_to_user( pReq->param.crypto.iv, dev->pOut, dev->nOut ) )
            return -EFAULT;
        __put_user( dev->nOut, &pReq->param.crypto.ivsize );
    }
    return 0;
}  /* set_crypto_param */


static int get_sslmac_param (
    PTDevInfo dev,
    int*      protocol,
    int*      sequence,
    PTRequest pReq )
{
    __get_user( *protocol, &pReq->param.ssl.protocol );
    __get_user( *sequence, &pReq->param.ssl.sequence );

    __get_user( dev->pIn, &pReq->param.ssl.pt );
    __get_user( dev->nIn, &pReq->param.ssl.ptsize );
    __get_user( dev->pOut, &pReq->param.ssl.out );
    __get_user( dev->nOut, &pReq->param.ssl.outsize );

    if ( !access_ok( VERIFY_READ, pReq->param.ssl.key, dev->nOut )  ||
             copy_from_user( dev->pKey, pReq->param.ssl.key, dev->nOut ) ) {
        return -EFAULT;
    }

    /* An input buffer is passed. */
    if ( dev->pIn ) {
        if ( alloc_buf( dev->nIn, &dev->pbIn, &dev->nInSize, &dev->pIn ) )
            return -ENOMEM;

        /* buffer is not empty. */
        if ( dev->nIn ) {
            if ( !access_ok( VERIFY_READ, pReq->param.ssl.pt, dev->nIn )  ||
                    copy_from_user( dev->pIn, pReq->param.ssl.pt, dev->nIn ) ) {
                return -EFAULT;
            }
        }
    }

    /* An output buffer is passed. */
    if ( dev->pOut ) {
        if ( alloc_buf( dev->nOut, &dev->pbOut, &dev->nOutSize, &dev->pOut ) )
            return -ENOMEM;
    }
    return 0;
}  /* get_sslmac_param */


static int set_sslmac_param (
    PTDevInfo dev,
    PTRequest pReq )
{
    /* An output buffer was passed. */
    if ( dev->pOut ) {
        if ( !access_ok( VERIFY_WRITE, pReq->param.ssl.out, dev->nOut )  ||
                copy_to_user( pReq->param.ssl.out, dev->pOut, dev->nOut ) )
            return -EFAULT;
        __put_user( dev->nOut, &pReq->param.ssl.outsize );
    }
    return 0;
}  /* set_sslmac_param */


static int get_espah_param (
    PTDevInfo dev,
    int*      direction,
    int*      wait,
    PTRequest pReq )
{
    __get_user( *direction, &pReq->param.espah.direction );
    __get_user( *wait, &pReq->param.espah.wait );

    __get_user( dev->pIn, &pReq->param.espah.pt );
    __get_user( dev->nIn, &pReq->param.espah.ptsize );
    __get_user( dev->pOut, &pReq->param.espah.out );
    __get_user( dev->nOut, &pReq->param.espah.outsize );

    /* An input buffer is passed. */
    if ( dev->pIn ) {
        if ( alloc_buf( dev->nIn, &dev->pbIn, &dev->nInSize, &dev->pIn ) )
            return -ENOMEM;

        /* buffer is not empty. */
        if ( dev->nIn ) {
            if ( !access_ok( VERIFY_READ, pReq->param.espah.pt, dev->nIn )  ||
                    copy_from_user( dev->pIn, pReq->param.espah.pt,
                    dev->nIn ) ) {
                return -EFAULT;
            }
        }
    }

    /* An output buffer is passed. */
    if ( dev->pOut ) {
        if ( alloc_buf( dev->nOut, &dev->pbOut, &dev->nOutSize, &dev->pOut ) )
            return -ENOMEM;
    }
    return 0;
}  /* get_espah_param */


static int set_espah_param (
    PTDevInfo dev,
    PTRequest pReq )
{
    /* An output buffer was passed. */
    if ( dev->pOut ) {
        if ( !access_ok( VERIFY_WRITE, pReq->param.espah.out, dev->nOut )  ||
                copy_to_user( pReq->param.espah.out, dev->pOut, dev->nOut ) )
            return -EFAULT;
        __put_user( dev->nOut, &pReq->param.espah.outsize );
    }
    return 0;
}  /* set_espah_param */


#ifdef HAVE_UNLOCKED_IOCTL
static long dev_ioctl (
    struct file*  filp,
    unsigned int  cmd,
    unsigned long arg )
#else
static int dev_ioctl (
    struct inode* inode,
    struct file*  filp,
    unsigned int  cmd,
    unsigned long arg )
#endif
{
    PTCharDev ptr = ( PTCharDev ) filp->private_data;
    PTDevInfo dev = ptr->pInfo;
    PTRequest pReq = ( PTRequest ) arg;
    char*     msg;
    int*      pOutSize;
    int       algorithm;
    int       direction;
    int       handle;
    int       ivsize;
    int       keysize;
    int       len;
    int       msg_len;
    int       mode;
    int       psize;
    int       wait;
    int       nReqSize;
    int       nResult;
    int       SubCmd;
    int       err = 0;
    int       result = 0;

    if ( _IOC_TYPE( cmd ) != DEV_IOC_MAGIC ) {
        return -ENOTTY;
    }
    if ( _IOC_NR( cmd ) > DEV_IOC_MAX ) {
        return -ENOTTY;
    }
    if ( ( _IOC_DIR( cmd ) & _IOC_READ ) ) {
        err = !access_ok( VERIFY_WRITE, ( void* ) arg, _IOC_SIZE( cmd ));
    }
    else if ( ( _IOC_DIR( cmd ) & _IOC_WRITE ) ) {
        err = !access_ok( VERIFY_READ, ( void* ) arg, _IOC_SIZE( cmd ));
    }
    if ( err ) {
        printk( KERN_ALERT "err fault\n" );
        return -EFAULT;
    }
    if ( down_interruptible( &dev->sem ) ) {
        return -ERESTARTSYS;
    }

    // check request size
    __get_user( nReqSize, &pReq->nSize );
    if ( nReqSize < sizeof( TRequest ) ) {
        printk( KERN_INFO "wrong size: %d %d\n", nReqSize, sizeof( TRequest ));
        goto dev_ioctl_size;
    }

    // assume success
    nResult = DEV_IOC_OK;
    err = CRYPTO_OK;
    __get_user( SubCmd, &pReq->nCmd );
    __get_user( handle, &pReq->handle );
    switch ( cmd ) {
        case DEV_IOC_SET:
#ifdef DEBUG
            printk( "set: %d, %d\n", SubCmd, handle );
#endif
            switch ( SubCmd ) {
                case IPSEC_CONTEXT:
                    if ( SEM_ESPAH == dev->nType ) {
                        __get_user( direction, &pReq->param.espah.direction );
                        if ( !access_ok( VERIFY_READ, pReq->param.espah.SA,
                                sizeof( Elliptic_SA ))  ||
                                copy_from_user( dev->pBuf,
                                pReq->param.espah.SA,
                                sizeof( Elliptic_SA )) ) {
                            result = -EFAULT;
                            goto dev_ioctl_done;
                        }
#ifdef DEBUG
                        printk( "espah_set: %d\n", direction );
#endif
                        err = espah_set_context( handle, direction, dev->pBuf );
#ifdef DEBUG
                        if ( err != CRYPTO_OK )
                            printk( "espah_set_context: %s\n",
                                espah_error_msg( err ));
#endif
                    }
                    else {
                        unsigned char* iv = NULL;

                        __get_user( keysize, &pReq->param.crypto.keysize );
                        __get_user( ivsize, &pReq->param.crypto.ivsize );
                        __get_user( psize, &pReq->param.crypto.psize );
                        if ( !access_ok( VERIFY_READ, pReq->param.crypto.key,
                                keysize )  ||
                                copy_from_user( dev->pKey,
                                pReq->param.crypto.key, keysize ) ) {
                            result = -EFAULT;
                            goto dev_ioctl_done;
                        }
                        if ( ivsize ) {
                            iv = dev->pBuf;
                            if ( !access_ok( VERIFY_READ,
                                    pReq->param.crypto.iv, ivsize )  ||
                                    copy_from_user( dev->pBuf,
                                    pReq->param.crypto.iv, ivsize ) ) {
                                result = -EFAULT;
                                goto dev_ioctl_done;
                            }
                        }
                        err = crypto_set_context( handle, dev->pKey, keysize,
                            iv, ivsize, psize );
#if 0
                        if ( err != CRYPTO_OK )
                            printk( "crypto_set_context: %s\n",
                                crypto_error_msg( err ));
#endif
                    }
                    break;
                case IPSEC_OPEN:
                    __get_user( algorithm, &pReq->param.open.algorithm );
                    __get_user( mode, &pReq->param.open.mode );
                    if ( SEM_ESPAH == dev->nType ) {
                        err = espah_open( algorithm, mode );
#ifdef DEBUG
                        if ( err < 0 )
                            printk( "espah_open: %d, %s\n", err,
                                espah_error_msg( err ));
#endif
                    }
                    else {
                        err = crypto_open( algorithm, mode );
                    }
                    if ( err >= 0 ) {
                        PTHandlePtr pHandle;

                        pHandle = ptr->free_handles.next;
                        ptr->free_handles.next = pHandle->next;
                        --ptr->free_handles.handle;
                        pHandle->handle = err;
                        pHandle->next = ptr->used_handles.next;
                        ptr->used_handles.next = pHandle;
                        ++ptr->used_handles.handle;
                    }
                    break;
                case IPSEC_CLOSE:
                    if ( SEM_ESPAH == dev->nType ) {
                        err = espah_close( handle );
                    }
                    else {
                        err = crypto_close( handle );
                    }
                    if ( err >= 0 ) {
                        PTHandlePtr pPrev = &ptr->used_handles;
                        PTHandlePtr pHandle = pPrev->next;

                        while ( pHandle ) {
                            if ( handle == pHandle->handle ) {
                                pPrev->next = pHandle->next;
                                --ptr->used_handles.handle;
                                pHandle->handle = -1;
                                pHandle->next = ptr->free_handles.next;
                                ptr->free_handles.next = pHandle;
                                ++ptr->free_handles.handle;
                                break;
                            }
                            pHandle = pPrev->next;
                        }
                    }
                    break;
                default:
                    nResult = DEV_IOC_INVALID_CMD;
            }
            break;
        case DEV_IOC_GET:
            switch ( SubCmd ) {
                case IPSEC_WAIT:
                    if ( SEM_ESPAH == dev->nType ) {
                        if ( ( result = get_espah_param( dev, &direction,
                                &wait, pReq )) )
                            goto dev_ioctl_done;
                        err = espah_wait( handle, direction, dev->pIn,
                            dev->nIn, dev->pOut, &dev->nOut, wait );
                        if ( CRYPTO_OK == err ) {
                            if ( ( result = set_espah_param( dev, pReq )) )
                                goto dev_ioctl_done;
                        }
                    }
                    else {
                        if ( ( result = get_crypto_param( dev, &algorithm,
                                &mode, &wait, pReq )) )
                            goto dev_ioctl_done;
                        if ( dev->pOut )
                            pOutSize = &dev->nOut;
                        else
                            pOutSize = NULL;
                        switch ( algorithm ) {
                            case ALG_AES:
                                err = crypto_aes_wait_( handle, mode,
                                    dev->pIn, dev->nIn, dev->pOut, pOutSize,
                                    wait );
                                break;
                            case ALG_DES:
                                err = crypto_des_wait_( handle, mode,
                                    dev->pIn, dev->nIn, dev->pOut, pOutSize,
                                    wait );
                                break;
                            case ALG_HMAC:
#ifdef DEBUG
                                printk( " >hmac: %d, %d, %d\n",
                                    dev->nIn, dev->nOut, wait );
#endif
                                err = crypto_hmac_wait_( handle, dev->pIn,
                                    dev->nIn, dev->pOut, pOutSize, wait );
                                break;
                            case ALG_RC4:
#ifdef DEBUG
                                printk( " >rc4: %d, %d, %d\n",
                                    dev->nIn, dev->nOut, wait );
#endif
                                err = crypto_rc4_wait_( handle, dev->pIn,
                                    dev->nIn, dev->pOut, pOutSize, wait );
                                break;
                            default:
                                nResult = DEV_IOC_INVALID_CMD;
                        }
#ifdef DEBUG
                        if ( err != CRYPTO_OK )
                            printk( "crypto_wait: %s\n",
                                crypto_error_msg( err ));
#endif
                        if ( CRYPTO_OK == err ) {
                            if ( ( result = set_crypto_param( dev, pReq )) )
                                goto dev_ioctl_done;
                        }
                    }
                    break;
                case IPSEC_SSL:
                {
                    int protocol;
                    int sequence;

                    if ( ( result = get_sslmac_param( dev, &protocol,
                            &sequence, pReq )) )
                        goto dev_ioctl_done;
                    err = _ssl_mac( handle, protocol, sequence, dev->pKey,
                        dev->pIn, dev->nIn, dev->pOut, dev->nOut );
#ifdef DEBUG
                    if ( err < 0 )
                        printk( "_ssl_mac: %s\n",
                            crypto_error_msg( err ));
#endif
                    if ( err >= 0 ) {
                        if ( ( result = set_sslmac_param( dev, pReq )) )
                           goto dev_ioctl_done;
                    }
                    break;
                }
                case IPSEC_CONTEXT:
                    if ( SEM_ESPAH == dev->nType ) {
                        __get_user( direction, &pReq->param.espah.direction );
                        err = espah_get_context( handle, direction, dev->pBuf );
                        if ( !access_ok( VERIFY_WRITE, pReq->param.espah.SA,
                                sizeof( Elliptic_SA ))  ||
                                copy_to_user( pReq->param.espah.SA, dev->pBuf,
                                sizeof( Elliptic_SA )) ) {
                            result = -EFAULT;
                            goto dev_ioctl_done;
                        }
                    }
                    else {
                        __get_user( ivsize, &pReq->param.crypto.ivsize );
                        __get_user( psize, &pReq->param.crypto.psize );
                        err = crypto_get_context( handle, dev->pBuf, &ivsize,
                            &psize );
                        if ( CRYPTO_OK == err  &&  (
                                !access_ok( VERIFY_WRITE,
                                pReq->param.crypto.iv, ivsize )  ||
                                copy_to_user( pReq->param.crypto.iv, dev->pBuf,
                                ivsize )) ) {
                            result = -EFAULT;
                            goto dev_ioctl_done;
                        }
                        __put_user( ivsize, &pReq->param.crypto.ivsize );
                        __put_user( psize, &pReq->param.crypto.psize );
                    }
                    break;
                default:
                    nResult = DEV_IOC_INVALID_CMD;
            }
            break;
        case DEV_IOC_STR:
            __get_user( len, &pReq->param.Mem.nLen );
#ifdef DEBUG
            printk( "str: %d, %d\n", SubCmd, len );
#endif
            switch ( SubCmd ) {
                case IPSEC_ERROR_MSG:
                    __get_user( msg_len, &pReq->param.Mem.nMsg );
#ifdef DEBUG
                    printk( "err: %d\n", msg_len );
#endif
                    if ( SEM_ESPAH == dev->nType )
                        msg = espah_error_msg( msg_len );
                    else
                        msg = crypto_error_msg( msg_len );
                    msg_len = strlen( msg ) + 1;
                    if ( len >= msg_len ) {
                        if ( !access_ok( VERIFY_WRITE, pReq->param.Mem.pBuf,
                                msg_len )  ||
                                copy_to_user( pReq->param.Mem.pBuf, msg,
                                msg_len ) ) {
                            result = -EFAULT;
                            goto dev_ioctl_done;
                        }
                    }
                    else {
                        nResult = DEV_IOC_INVALID_LEN;
                    }
                    __put_user( msg_len, &pReq->param.Mem.nLen );
                    break;
                case IPSEC_VERSION_STR:
                    if ( SEM_ESPAH == dev->nType )
                        msg = espah_get_version();
                    else
                        msg = crypto_get_version();
                    msg_len = strlen( msg ) + 1;
                    if ( len >= msg_len ) {
                        if ( !access_ok( VERIFY_WRITE, pReq->param.Mem.pBuf,
                                msg_len )  ||
                                copy_to_user( pReq->param.Mem.pBuf, msg,
                                msg_len ) ) {
                            result = -EFAULT;
                            goto dev_ioctl_done;
                        }
                    }
                    else {
                        nResult = DEV_IOC_INVALID_LEN;
                    }
                    __put_user( msg_len, &pReq->param.Mem.nLen );
                    break;
                default:
                    nResult = DEV_IOC_INVALID_CMD;
            }
            break;
        default:
            result = -ENOTTY;
            goto dev_ioctl_done;
    }
#ifdef DEBUG
    printk( "  :%d, %d\n", err, nResult );
#endif
    __put_user( err, &pReq->hwResult );
    __put_user( nResult, &pReq->nResult );

dev_ioctl_done:
    up( &dev->sem );
    return( result );

dev_ioctl_size:
    __put_user( sizeof( TRequest ), &pReq->nSize );
    __put_user( -1, &pReq->nResult );
    goto dev_ioctl_done;
}  /* dev_ioctl */


#if 0
static loff_t dev_llseek (
    struct file* filp,
    loff_t       off,
    int          whence )
{
    return off;
}  /* dev_llseek */
#endif


static ssize_t dev_read (
    struct file* filp,
    char*        buf,
    size_t       count,
    loff_t*      offp )
{
    ssize_t   result = 0;

    return( result );
}  /* dev_read */


static ssize_t dev_write (
    struct file* filp,
    const char*  buf,
    size_t       count,
    loff_t*      offp )
{
    ssize_t   result = 0;

    return( result );
}  /* dev_write */

/* -------------------------------------------------------------------------- */

static
struct {
    int handle;
    int flags;
} ESPAH_Handles[ MAX_HANDLE_NUM ];


int ksz_request (
    int dir )
{
    int handle;
    int i;

    for ( i = 0; i < MAX_HANDLE_NUM; i++ ) {
        if ( !( ESPAH_Handles[ i ].flags & ( 1 << dir )) ) {
            if ( !ESPAH_Handles[ i ].flags ) {
                handle = espah_open( 0, ESPAH_MODE_DEFAULT );
                ESPAH_Handles[ i ].handle = handle;
            }
            else
                handle = ESPAH_Handles[ i ].handle;
            ESPAH_Handles[ i ].flags |= ( 1 << dir );
            return( handle );
        }
    }
    return( -1 );
}  /* ksz_request */

EXPORT_SYMBOL(ksz_request);


void ksz_release (
    int handle,
    int dir )
{
    int i;

    for ( i = 0; i < MAX_HANDLE_NUM; i++ ) {
        if ( handle == ESPAH_Handles[ i ].handle ) {
            ESPAH_Handles[ i ].flags &= ~( 1 << dir );
            if ( !ESPAH_Handles[ i ].flags ) {
                if ( handle >= 0 )
                    espah_close( handle );
                ESPAH_Handles[ i ].handle = -1;
            }
            break;
        }
    }
}  /* ksz_release */

EXPORT_SYMBOL(ksz_release);


static void ksz_init ( void )
{
    int i;

    for ( i = 0; i < MAX_HANDLE_NUM; i++ ) {
        ESPAH_Handles[ i ].handle = -1;
        ESPAH_Handles[ i ].flags = 0;
    }
    espah_get_buffers( &ksz_in, &ksz_out );
    ksz_in_outbound = &ksz_in[ ESPAH_DPRAM_PACKET_OUT_SIZE ];
    ksz_out_outbound = &ksz_out[ ESPAH_DPRAM_PACKET_OUT_SIZE ];
}  /* ksz_init */

/* -------------------------------------------------------------------------- */

#ifdef CONFIG_USE_KSZCRYPT
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 21))
#include <crypto/algapi.h>
#include "kszcrypto_21.c"
#else
#include "kszcrypto_9.c"
#endif
#endif

/* -------------------------------------------------------------------------- */

static unsigned int ipsec_base = 0;
static void* ipsec_map = NULL;

unsigned char* ipsec_sa_map = NULL;
dma_addr_t ipsec_sa_base = 0;

struct file_operations ipsec_dev_fops = {
#if 0
    llseek: dev_llseek,
#endif
    read: dev_read,
    write: dev_write,
#ifdef HAVE_UNLOCKED_IOCTL
    unlocked_ioctl: dev_ioctl,
#else
    ioctl: dev_ioctl,
#endif
    open: dev_open,
    release: dev_release,
};


#ifdef CONFIG_KSZIPSEC_USE_INTR
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 24))
extern int xfrm4_rcv_encap ( struct sk_buff *skb, int nexthdr, __be32 spi,
    int encap_type );
#else
extern int xfrm4_rcv_encap ( struct sk_buff* skb, __u16 );
#endif
extern int xfrm4_output_finish ( struct sk_buff *skb );


static struct sk_buff* xfrm4_rcv_skb_head = NULL;
static struct sk_buff* xfrm4_rcv_skb_tail = NULL;
static struct sk_buff* xfrm4_output_skb_head = NULL;
static struct sk_buff* xfrm4_output_skb_tail = NULL;

static struct task_struct* xfrm4_rcv_th = NULL;
static struct task_struct* xfrm4_output_th = NULL;

static wait_queue_head_t xfrm4_rcv_wqh;
static wait_queue_head_t xfrm4_output_wqh;

wait_queue_head_t espah_in_wqh;
wait_queue_head_t espah_out_wqh;

EXPORT_SYMBOL(espah_in_wqh);
EXPORT_SYMBOL(espah_out_wqh);


int xfrm4_hw_rcv (
    struct sk_buff* skb
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 24))
    ,
    int             nexthdr,
    __be32          spi
#endif
    )
{
    unsigned long flags;

    skb->skb_next = NULL;

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 24))
    skb->nexthdr = nexthdr;
    skb->spi = spi;
#endif

    local_irq_save( flags );
    if ( xfrm4_rcv_skb_tail )
        xfrm4_rcv_skb_tail->skb_next = skb;
    xfrm4_rcv_skb_tail = skb;
    if ( !xfrm4_rcv_skb_head )
        xfrm4_rcv_skb_head = skb;
    local_irq_restore( flags );

    wake_up_interruptible( &xfrm4_rcv_wqh );
    return 0;
}  /* xfrm4_hw_rcv */


static int xfrm4_rcv_thread (
    void* data )
{
    struct sk_buff* skb;
    int             rc;

    set_user_nice( current, -3 );
    current->flags |= PF_NOFREEZE;

    set_current_state( TASK_INTERRUPTIBLE );
    while ( !kthread_should_stop() ) {

        if ( ( rc = wait_event_interruptible( xfrm4_rcv_wqh,
                xfrm4_rcv_skb_head )) ) {
            continue;
        }

        local_irq_disable();
        skb = xfrm4_rcv_skb_head;
        while ( skb ) {
            xfrm4_rcv_skb_head = skb->skb_next;
            local_irq_enable();

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 24))
            xfrm4_rcv_encap( skb, skb->nexthdr, skb->spi, 0 );
#else
            xfrm4_rcv_encap( skb, 0 );
#endif

            local_irq_disable();
            skb = xfrm4_rcv_skb_head;
        }
        xfrm4_rcv_skb_tail = NULL;
        local_irq_enable();

        set_current_state( TASK_INTERRUPTIBLE );
    }
    __set_current_state( TASK_RUNNING );
    return 0;
}  /* xfrm4_rcv_thread */


int xfrm4_hw_output (
    struct sk_buff* skb )
{
    unsigned long flags;

    skb->skb_next = NULL;

    local_irq_save( flags );
    if ( xfrm4_output_skb_tail )
        xfrm4_output_skb_tail->skb_next = skb;
    xfrm4_output_skb_tail = skb;
    if ( !xfrm4_output_skb_head )
        xfrm4_output_skb_head = skb;
    local_irq_restore( flags );

    wake_up_interruptible( &xfrm4_output_wqh );
    return 0;
}  /* xfrm4_hw_output */


static int xfrm4_output_thread (
    void* data )
{
    struct sk_buff* skb;
    int             rc;

    set_user_nice( current, -3 );
    current->flags |= PF_NOFREEZE;

    set_current_state( TASK_INTERRUPTIBLE );
    while ( !kthread_should_stop() ) {

        if ( ( rc = wait_event_interruptible( xfrm4_output_wqh,
                xfrm4_output_skb_head )) ) {
            continue;
        }

        local_irq_disable();
        skb = xfrm4_output_skb_head;
        while ( skb ) {
            xfrm4_output_skb_head = skb->skb_next;
            local_irq_enable();

            xfrm4_output_finish( skb );

            local_irq_disable();
            skb = xfrm4_output_skb_head;
        }
        xfrm4_output_skb_tail = NULL;
        local_irq_enable();

        set_current_state( TASK_INTERRUPTIBLE );
    }
    __set_current_state( TASK_RUNNING );
    return 0;
}  /* xfrm4_output_thread */


#define ESPAH_INT_CTRL_ENABLE  0x80000000

#define ESPAH_INT_AES          0x00080000
#define ESPAH_INT_RC4          0x00040000
#define ESPAH_INT_DES          0x00020000
#define ESPAH_INT_HMAC         0x00010000

#define ESPAH_INT_SRM          0x00000100
#define ESPAH_INT_INBOUND      0x00000002
#define ESPAH_INT_OUTBOUND     0x00000001

static
#if (LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 0))
void

#else
irqreturn_t
#endif
kszipsec_interrupt (
    int             irq,
    void*           dev_id
#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,21))
    ,
    struct pt_regs* regs
#endif
    )
{
    U32 status = *_espah_module.int_stat;

#ifdef CONFIG_DEBUG_KSZIPSEC
    printk( KERN_DEBUG "%lx+\n", status );
#endif
    if ( ( status &
        ( ESPAH_INT_SRM | ESPAH_INT_INBOUND | ESPAH_INT_OUTBOUND )) )
    *_espah_module.int_stat = status;

    KS8692_WRITE_REG( KS8692_INT_STATUS1, KS8692_INTMASK_IPSEC );

    if ( ( status & ESPAH_INT_OUTBOUND ) ) {
        espah_out_intr = 1;
        wake_up_interruptible( &espah_out_wqh );
    }
    if ( ( status & ESPAH_INT_INBOUND ) ) {
        espah_in_intr = 1;
        wake_up_interruptible( &espah_in_wqh );
    }

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 0))
    return IRQ_HANDLED;
#endif
}  /* kszipsec_interrupt */
#endif


#ifdef MODULE
int __init init_module ( void )
#else
static
int __init ipsec_init ( void )
#endif
{
    int i;
    int result;

    ipsec_base = KS8692_READ_REG( KS8692_IPSEC_CFG );
    if ( !( ipsec_base & IPSEC_ENABLE ) ) {
        KS8692_WRITE_REG( KS8692_IPSEC_CFG, ipsec_base | IPSEC_ENABLE );
    }
    ipsec_base &= IPSEC_BASE_MASK;

    result = register_chrdev( dev_major, ksz_dev_name, &ipsec_dev_fops );
    if ( result < 0 ) {
        printk( KERN_WARNING "%s: can't get major %d\n", ksz_dev_name,
            dev_major );
        return result;
    }
    if ( 0 == dev_major ) {
        dev_major = result;
    }

    if ( !request_mem_region( ipsec_base, 0x40000, ksz_dev_name ) ) {
        return -ENODEV;
    }
    ipsec_map = ioremap( ipsec_base, 0x40000 );
    ipsec_sa_map = ( unsigned char* ) dma_alloc_coherent( NULL,
        ESPAH_SIZE, &ipsec_sa_base, GFP_KERNEL | GFP_DMA );
    if ( !ipsec_sa_map ) {
        iounmap( ipsec_map );
        release_mem_region( ipsec_base, 0x40000 );
        return -ENOMEM;
    }

    for ( i = 0; i < SEM_LAST; i++ ) {
        memset( &gDev[ i ], 0, sizeof( TCharDev ));
        sema_init( &gDev[ i ].sem, 1 );
        gDev[ i ].nType = i;

        gDev[ i ].nLen = 0x10000;
        gDev[ i ].pBuf = kmalloc( gDev[ i ].nLen, GFP_KERNEL );
        gDev[ i ].pKey = kmalloc( 0x200, GFP_KERNEL );
    }
    ksz_rinbuf = kmalloc( ESPAH_DPRAM_PACKET_IN_SIZE * ESPAH_DIRECTION,
        GFP_KERNEL );
    ksz_routbuf = kmalloc( ESPAH_DPRAM_PACKET_OUT_SIZE * ESPAH_DIRECTION,
        GFP_KERNEL );
    ksz_rinbuf_outbound = &ksz_rinbuf[ ESPAH_DPRAM_PACKET_OUT_SIZE ];
    ksz_routbuf_outbound = &ksz_routbuf[ ESPAH_DPRAM_PACKET_OUT_SIZE ];

    espah_init( 0, ( U32 ) ipsec_map );
    crypto_init( CRYPTO_MODULE_ALL, ( U32 ) ipsec_map );
    ksz_init();

#ifdef CONFIG_KSZIPSEC_USE_INTR
    if ( ( !request_irq( KS8692_INT_IPSEC, kszipsec_interrupt,
            0, intr_name, NULL )) ) {
        unsigned int reg;

        reg = KS8692_READ_REG( KS8692_INT_ENABLE1 );
        reg |= INT_IPSEC;
        KS8692_WRITE_REG( KS8692_INT_ENABLE1, reg );
        *_espah_module.int_ctrl =
            ESPAH_INT_CTRL_ENABLE |
#if 0
            ESPAH_INT_AES | ESPAH_INT_RC4 |
            ESPAH_INT_DES | ESPAH_INT_HMAC |
#endif
            ESPAH_INT_SRM |
            ESPAH_INT_INBOUND | ESPAH_INT_OUTBOUND;
    }

    init_waitqueue_head( &espah_in_wqh );
    init_waitqueue_head( &espah_out_wqh );
    init_waitqueue_head( &xfrm4_rcv_wqh );
    init_waitqueue_head( &xfrm4_output_wqh );
    xfrm4_output_th = kthread_create( xfrm4_output_thread, NULL,
        "xfrm4_output" );
    if ( xfrm4_output_th )
        wake_up_process( xfrm4_output_th );
    xfrm4_rcv_th = kthread_create( xfrm4_rcv_thread, NULL, "xfrm4_rcv" );
    if ( xfrm4_rcv_th )
        wake_up_process( xfrm4_rcv_th );
#endif

#ifdef CONFIG_USE_KSZCRYPT
    ksz_init_aes();
    ksz_init_des();
#endif

    return 0;
}  /* ipsec_init */


#ifdef MODULE
void __exit cleanup_module ( void )
#else
static
void __exit ipsec_exit ( void )
#endif
{
    int i;

#ifdef CONFIG_USE_KSZCRYPT
    ksz_fini_aes();
    ksz_fini_des();
#endif

#ifdef CONFIG_KSZIPSEC_USE_INTR
    if ( xfrm4_rcv_th )
        kthread_stop( xfrm4_rcv_th );
    if ( xfrm4_output_th )
        kthread_stop( xfrm4_output_th );

    free_irq( KS8692_INT_IPSEC, NULL );
#endif

    unregister_chrdev( dev_major, ksz_dev_name );
    if ( ipsec_sa_map ) {
        dma_free_coherent( NULL, ESPAH_SIZE, ipsec_sa_map, ipsec_sa_base );
    }
    if ( ipsec_map )
        iounmap( ipsec_map );
    release_mem_region( ipsec_base, 0x40000 );
    for ( i = 0; i < SEM_LAST; i++ ) {
        kfree( gDev[ i ].pBuf );
        kfree( gDev[ i ].pKey );
        if ( gDev[ i ].pIn )
            kfree( gDev[ i ].pIn );
        if ( gDev[ i ].pOut )
            kfree( gDev[ i ].pOut );
    }
    kfree( ksz_rinbuf );
    kfree( ksz_routbuf );
}  /* ipsec_exit */


#ifndef MODULE
module_init( ipsec_init );
module_exit( ipsec_exit );
#endif
