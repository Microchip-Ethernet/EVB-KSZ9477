/*
 * ks8692_ictrol.h
 *
 */
#ifndef	__KS8692_IOCTRL_H
#define	__KS8692_IOCTRL_H

#ifndef	__KERNEL__
#include <stdio.h>
#endif


/* 
 * PHY Definitions 
 */

#define SPEED_UNKNOWN			      0
#define SPEED_10				 100000
#define SPEED_100				1000000
#define SPEED_1G			   10000000

#define DUPLEX_UNKNOWN			0
#define HALF_DUPLEX				0
#define FULL_DUPLEX				0x01		// default for full duplex
#define STATUS_CABLE_CROSSOVER  0x02
#define STATUS_CABLE_REVERSED   0x04

#define SW_PHY_AUTO				0    /* auto-negotiation link speed\duplex mode */
#define SW_PHY_10BASE_T			1    /* 10Base-T */
#define SW_PHY_10BASE_T_FD		2    /* 10Base-T Full Duplex */
#define SW_PHY_100BASE_TX		3    /* 100Base-TX */
#define SW_PHY_100BASE_TX_FD	4    /* 100Base-TX Full Duplex */
#define SW_PHY_DEFAULT			SW_PHY_AUTO

/* 
 * Device\Driver Statistics definitions 
 */

/* Driver Statistics definitions */
typedef enum
{
        OID_COUNTER_FIRST,
/* 0 */ OID_COUNTER_DIRECTED_BYTES_XMIT = OID_COUNTER_FIRST, /* total bytes transmitted  */
/* 1 */ OID_COUNTER_DIRECTED_FRAMES_XMIT,    /* total packets transmitted */

/* 2 */ OID_COUNTER_DIRECTED_BYTES_RCV,      /* total bytes received   */
/* 3 */ OID_COUNTER_DIRECTED_FRAMES_RCV,     /* total packets received */
/* 4 */ OID_COUNTER_BROADCAST_BYTES_RCV,
/* 5 */ OID_COUNTER_BROADCAST_FRAMES_RCV,    /* total broadcast packets received  */
/* 6 */ OID_COUNTER_MULTICAST_FRAMES_RCV,    /* total multicast packets received  */
/* 7 */ OID_COUNTER_UNICAST_FRAMES_RCV,      /* total unicast packets received    */

/* 8 */ OID_COUNTER_XMIT_ERROR,              /* total transmit errors */
/* 9 */ OID_COUNTER_XMIT_ALLOC_FAIL,         /* transmit fail because no enought memory in the Tx Packet Memory */
/*10 */ OID_COUNTER_XMIT_DROPPED,            /* transmit packet drop because no buffer in the host memory */
/*11 */ OID_COUNTER_XMIT_INT_UNDERRUN,       /* transmit underrun from interrupt status */
/*12 */ OID_COUNTER_XMIT_INT_STOP,           /* transmit DMA MAC process stop from interrupt status */
/*13 */ OID_COUNTER_XMIT_INT,                /* transmit Tx interrupt status */

/*14 */ OID_COUNTER_RCV_ERROR,               /* total receive errors */
/*15 */ OID_COUNTER_RCV_ERROR_CRC,           /* receive packet with CRC error */
/*16 */ OID_COUNTER_RCV_ERROR_MII,           /* receive MII error */
/*17 */ OID_COUNTER_RCV_ERROR_TOOLONG,       /* receive frame too long error */
/*18 */ OID_COUNTER_RCV_ERROR_RUNT,          /* receive Runt frame error */
/*19 */ OID_COUNTER_RCV_ERROR_IP,            /* receive frame with IP checksum error */
/*20 */ OID_COUNTER_RCV_ERROR_TCP,           /* receive frame with TCP checksum error */
/*21 */ OID_COUNTER_RCV_ERROR_UDP,           /* receive frame with UDP checksum error */
/*22 */ OID_COUNTER_RCV_NO_BUFFER,           /* receive failed because of RX_BUF_UNAVAIL interrupt status */
/*23 */ OID_COUNTER_RCV_DROPPED,             /* receive packet drop because no buffer in the host memory */
/*24 */ OID_COUNTER_RCV_INT_STOP,            /* receive DMA MAC process stop from interrupt status */
/*25 */ OID_COUNTER_RCV_INT,                 /* receive Rx interrupt status */

        OID_COUNTER_LAST
} EOidCounter;

#define MIB_COUNTER_NUM         32   /* max MIB counter per port */


/* 
 * Device IOCTRL definitions 
 */

#define BUFFER_COUNT            6
#define BUFFER_LENGTH           (2 * 1024)

#define NEWLINE			"\n"

#define MAX_REGADDR_OFFSET     0xEE00


enum {
	HW_REG_READ, 		//Read all registers
	HW_REG_WRITE, 		//Write all registers
	HW_REG_HWPOLL,
	HW_REG_HWDUMPREG,
	HW_REG_RESET,		//Write hardware reset register
	HW_REG_HWGETTXCNT1,	
	HW_REG_HWGETTXCNT2,	
	HW_REG_HWGETRXCNT1,	
	HW_REG_HWGETRXCNT2,
	HW_REG_HWBUFREAD,
	HW_REG_HWBUFWRITE,
	HW_REG_HWBUFFILL,
	HW_REG_HWBUFTX,
	HW_REG_HWSHOWMIB,
	HW_REG_HWCLEARMIB,
	HW_REG_HWDUMPTX,
	HW_REG_HWDUMPRX,
	HW_REG_HWTESTCABLE,
	HW_REG_HWGETLINK,
	HW_REG_HWSETLINK,
	HW_REG_HWSHOWRXDB,
	HW_REG_HWSHOWTXDB,
	HW_PHY_GETLINK,
	HW_PHY_SETLINK,
	HW_SET_MULTI,
	HW_SET_MACFILTER,
	HW_GET_MACFILTER,
	HW_SET_IPFILTER,
	HW_GET_IPFILTER,
	HW_PCI_REG_READ, 		
	HW_PCI_REG_WRITE,
	HW_PCI_HEADER
};

/* Total is DUMP_BUFFER_MAX for 'sParam', 'rParam' space */
#define	DUMP_BUFFER_MAX		      1024
#define IO_USER_BUF_MAX_SIZE      ( DUMP_BUFFER_MAX / (sizeof(long) * 2 )  )
#define IO_USER_RX_BUF_SIZE       ( (DUMP_BUFFER_MAX - 4 ) / 2 )

#if (1)
typedef struct 
{
    uint8_t 	byId;
    uint16_t	usLen;
    struct 
    {
        uint32_t	uData[IO_USER_BUF_MAX_SIZE*sizeof(char)];
    } sParam[1];
    struct 
    {
        uint32_t	uData[IO_USER_BUF_MAX_SIZE*sizeof(char)];
    } rParam[1];
} KSIOCTRL, *PKSIOCTRL;
#endif

#if (0)
typedef struct 
{
    uint8_t 	byId;
    uint16_t	usLen;
    struct 
    {
       union {
        uint32_t	uData[IO_USER_BUF_MAX_SIZE*sizeof(char)];
       } u;
       union {
        uint8_t		byData[IO_USER_BUF_MAX_SIZE*sizeof(long)];
       } by;
    } sParam[1];
    struct 
    {
       union {
        uint32_t	uData[IO_USER_BUF_MAX_SIZE*sizeof(char)];
       } u;
       union {
        uint8_t		byData[IO_USER_BUF_MAX_SIZE*sizeof(long)];
       } by;
    } rParam[1];
} KSIOCTRL, *PKSIOCTRL;
#endif

/*
 * local defines
 */

/* The proprietary IOCTL code for KSZ8692 IO access */
#define SIOC_KS_DEBUG   	(SIOCDEVPRIVATE + 10)
#define SIOC_KS_WEB     	(SIOCDEVPRIVATE + 11)

#endif	/*__KS8692_IOCTRL_H*/
