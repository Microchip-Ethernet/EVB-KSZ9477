/*-----------------------------------------------------------------------
//
// Proprietary Information of Elliptic Semiconductor
// Copyright (C) 2005, all rights reserved
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
//   ELPIPSEC
//
// Description:
//
//
// This file maps defines a system abstraction layer for some generic
// functions and data structures
//
//
//-----------------------------------------------------------------------
//
// Copyright (C) 2006-2007, Micrel, Inc.
//
//-----------------------------------------------------------------------*/


#ifndef _ELPIPSEC_H_
#define _ELPIPSEC_H_

#include "elputils.h"

enum espah_errors
{
	ESPAH_OK			=  0,
	ESPAH_FAILED			= -1,
	ESPAH_SOFT_TTL			= -2,
	ESPAH_HARD_TTL			= -3,
	ESPAH_SA_INACTIVE		= -4,
	ESPAH_REPLAY			= -5,
	ESPAH_ICV_FAIL			= -6,
	ESPAH_SEQ_ROLL			= -7,
	ESPAH_MEM_ERROR			= -8,
	ESPAH_VERS_ERROR		= -9,
	ESPAH_PROT_ERROR		= -10,
	ESPAH_PYLD_ERROR		= -11,
	ESPAH_PAD_ERROR			= -12,
	ESPAH_INPROGRESS		= -22,
	ESPAH_INVALID_HANDLE		= -23,
	ESPAH_INVALID_CONTEXT		= -24,
	ESPAH_INVALID_SIZE		= -25,
	ESPAH_NOT_INITIALIZED		= -26,
	ESPAH_NO_MEM			= -27,
	ESPAH_INVALID_ALG		= -28,
	ESPAH_INVALID_KEY_SIZE		= -29,
	ESPAH_INVALID_ARGUMENT		= -30,
	ESPAH_MODULE_DISABLED		= -31,
	ESPAH_NOT_IMPLEMENTED		= -32,
	ESPAH_INVALID_BLOCK_ALIGNMENT	= -33,
	ESPAH_INVALID_MODE		= -34,
	ESPAH_INVALID_KEY		= -35,
	ESPAH_AUTHENTICATION_FAILED	= -36,
	ESPAH_FAILED_TIMEOUT		= -37
};


enum espah_modes {
	ESPAH_MODE_DEFAULT,
	ESPAH_MODE_MAX,
};

#define ELP_SA_SEQNUM		0x00
#define ELP_SA_ANTI_REPL	0x08
#define ELP_SA_AUTH_KEY		0x10
#define ELP_SA_CIPHER_KEY	0x24
#define ELP_SA_IV		0x44
#define ELP_SA_REMOTE_SPI	0x54
#define ELP_SA_CIPHER_TOK	0x64
#define ELP_SA_AUTH_TOK		0x66
#define ELP_SA_THREAD_ID	0x6A
#define ELP_SA_HARD_TTLHI	0x6C
#define ELP_SA_HARD_TTLLO	0x70
#define ELP_SA_SOFT_TTLHI	0x74
#define ELP_SA_SOFT_TTLLO	0x78
#define ELP_SA_ALG		0x7C
#define ELP_SA_FLAGS		0x7E


typedef struct {
    unsigned int   seq_num_hi;
    unsigned int   seq_num_lo;
    unsigned int   anti_replay_hi;
    unsigned int   anti_replay_lo;
    unsigned char  auth_key[ 20 ];
    unsigned char  cipher_key[ 32 ];
    unsigned char  icv[ 16 ];
    unsigned int   SPI;
    unsigned int   reserved2[ 3 ];
    unsigned short cipher_tok;
    unsigned short auth_tok;
    unsigned char  reserved3[ 2 ];
    unsigned char  thread_id;
    unsigned char  reserved4;
    unsigned int   hard_life_hi;
    unsigned int   hard_life_lo;
    unsigned int   soft_life_hi;
    unsigned int   soft_life_lo;
    unsigned char  alg;
    unsigned char  reserved5;
    unsigned short mode;
    unsigned int   reserved6[ 32 ];
} Elliptic_SA, *PElliptic_SA;


#define ESP_SHIFT    4

#define ESP_NULL     0
#define ESP_DES      1
#define ESP_3DES     2
#define ESP_AES128   3
#define ESP_AES192   4
#define ESP_AES256   5

#define AH_MD5       1
#define AH_SHA1      2

#define ESPAH_ENABLE        ( 1 << ESPAH_ENABLED_BIT )
#define TTL_ENABLE          ( 1 << ESPAH_TTL_ENABLE_BIT )
#define TTL_MODE            ( 1 << ESPAH_TTL_TYPE_BIT )
#define AH_MODE             ( 1 << ESPAH_TRANSFORM_BIT )
#define TUNNEL_MODE         ( 1 << ESPAH_MODE_BIT )
#define ANTI_REPLAY_ENABLE  ( 1 << ESPAH_ANTI_REPLY_ENABLE_BIT )
#define EXT_SEQNUM_ENABLE   ( 1 << ESPAH_EXTENDED_SEQNUM_BIT )


#ifdef __KERNEL__
extern unsigned char* ksz_in;
extern unsigned char* ksz_in_outbound;
extern unsigned char* ksz_out;
extern unsigned char* ksz_out_outbound;
extern unsigned char* ksz_rinbuf;
extern unsigned char* ksz_rinbuf_outbound;
extern unsigned char* ksz_routbuf;
extern unsigned char* ksz_routbuf_outbound;
extern unsigned short ksz_thread_id;

/* Use the buffer pointers directly to skip one memory copy. */
#if 1
#define USE_DIRECT_PTR
#endif

#ifdef USE_DIRECT_PTR
#define KSZ_IN       ksz_in
#define KSZ_OUT      ksz_out
#define KSZ_IN_OUT   ksz_in_outbound
#define KSZ_OUT_OUT  ksz_out_outbound
#else
#define KSZ_IN       ksz_rinbuf
#define KSZ_OUT      ksz_routbuf
#define KSZ_IN_OUT   ksz_rinbuf_outbound
#define KSZ_OUT_OUT  ksz_routbuf_outbound
#endif

#if ( defined( CONFIG_XFRM_USER ) || defined( CONFIG_XFRM_USER_MODULE )) && defined( CONFIG_NETFILTER )
#if 1
#define CONFIG_KSZIPSEC_USE_INTR
#endif
#endif

#ifdef CONFIG_KSZIPSEC_USE_INTR
#define ESPAH_WAIT  0
#else
#define ESPAH_WAIT  1
#endif

#ifdef CONFIG_KSZIPSEC_USE_INTR
extern volatile int espah_in_intr;
extern volatile int espah_out_intr;

#ifdef _NET_XFRM_H
extern wait_queue_head_t espah_in_wqh;
extern wait_queue_head_t espah_out_wqh;

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 24))
extern int xfrm4_hw_rcv ( struct sk_buff* skb, int nexthdr, __be32 spi );
#else
extern int xfrm4_hw_rcv ( struct sk_buff* skb );
#endif
extern int xfrm4_hw_output ( struct sk_buff* skb );
#endif
#endif

int ksz_request ( int dir );
void ksz_release ( int handle, int dir );
#endif


struct espah_module_;

//  crypto module context descriptor
typedef struct espah_handle_
{
	elp_mutex mlock;		// mutext to protect globally accessible objects;
	int taken;
	int index;			// module's context index
	int mode;			// module  mode
	int curr_handle;

	struct espah_module_ *module;	// back pointer to the hardware module
	volatile U32 *sa_ctx;
} espah_handle;


// Hardware crypto module pointers
// Descriptor of multiple hadrware crypto module contexts
typedef struct espah_module_
{
	U32 cookie;			// magic cookie
	elp_mutex mlock;		// mutext to protect globally accessible objects;
	int active;			// Do we have actually any hardware
	int type;			// Context type
	int max;			// Contexts number
	int curr_handle;		// This is curent handle accessing this hardware, need to triger retrieving context

	espah_handle *ctx_handle;

	volatile U32 *int_ctrl;		// Enables for individual interrupt sources
	volatile U32 *int_stat;		// Interrupt status; to clear write 1
	volatile U32 *arbiter_req;	// Request the security block arbiter
	volatile U32 *arbiter_gnt;	// Security block has been granted
	volatile U32 *srm_go;		// Kick off a request for security resources
	volatile U32 *srm_rdy;		// Status of the security resource request
	volatile U32 *out_src_ptr;	// Pointer to source packet memory structure in system memory; DWORD Aligned
	volatile U32 *out_dst_ptr;	//Pointer to destination memory structure for post processed packet; DWORD Aligned
	volatile U32 *out_offset;	// Ofset in packet memory structure of start of packet
	volatile U32 *out_stat;		// Status register (lenght:ret_code;busy) bitmask
	volatile U32 *out_sai;		// Pointer to SA structure in the system memory; Writing starts the engine!! 128 bytes aligned!!!
	volatile U32 *in_src_ptr;	// Pointer to source packet memory structure in system memory; DWORD Aligned
	volatile U32 *in_dst_ptr;	//Pointer to destination memory structure for post processed packet; DWORD Aligned
	volatile U32 *in_offset;	// Ofset in packet memory structure of start of packet
	volatile U32 *in_stat;		// Status register (lenght:ret_code;busy) bitmask
	volatile U32 *in_sai;		// Pointer to SA structure in the system memory; Writing starts the engine!! 128 bytes aligned!!!

	volatile U32 *srm_cmd0;		// Command structure from the security control manager
	volatile U32 *srm_cmd1;
	volatile U32 *srm_cmd2;
	volatile U32 *srm_ret0;
	volatile U32 *srm_ret1;

	volatile U32 *out_packet;
	volatile U32 *in_packet;
} espah_module;


espah_handle *espah_context_lookup(U32 handle);
int espah_init(int modules, U32 mmap);
int espah_open(int type, int mode);
int espah_close(int handle);
void espah_set_debug(unsigned int dflag);
unsigned int espah_get_debug (void);
char *espah_error_msg(int err);
char *espah_get_version(void);
void espah_get_buffers(unsigned char** in, unsigned char** out);

int espah_get_context(int handle, int direction, unsigned char *SA);
int espah_set_context(int handle, int direction, const unsigned char *SA);


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
	unsigned mode );		/* TRANSPORT, TUNNEL */
/**
   Process or wait for a packet
   @param handle    The ESPAH handle
   @param direction Inbound or Outbound (ESPAH_INBOUND_DIRECTION or ESPAH_OUTBOUND_DIRECTION)
   @param in        The input data (can be NULL)
   @param in_size   The size of the input
   @param out       The output
   @param out_size  The max and resulting size of the output
   @param wait      Wait for completion (1==yes,0==no)
   @param ret_code  [out] The engine return code.
*/
int espah_wait(int handle, int direction,
               unsigned char *in, int in_size,
               unsigned char *out, int *out_size, int wait);

#endif
