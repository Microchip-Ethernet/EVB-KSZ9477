#include "main.h"

typedef unsigned char  uchar;
typedef unsigned short ushort;
typedef unsigned long  ulong;

unsigned int sizeOfData;
char modeOfTransfer;
char error;

#define CRC16POLY   0x1021              /* CRC 16  polynom */

//*----------------------------------------------------------------------------
//* \fn    AT91F_GetCrc
//* \brief Compute the CRC
//*----------------------------------------------------------------------------
unsigned short AT91F_GetCrc(char ptr, unsigned short crc)
{

    unsigned short cmpt;

    crc = crc ^ (int) ptr << 8;

    for (cmpt = 0; cmpt < 8; cmpt++)
    {
        if (crc & 0x8000)
            crc = crc << 1 ^ CRC16POLY;
        else
            crc = crc << 1;
    }

    return (crc & 0xFFFF);
}

//*----------------------------------------------------------------------------
//* \fn    AT91F_PutChar
//* \brief This function allows data rx by USART
//*----------------------------------------------------------------------------
void AT91F_PutChar(char data)
{
    while (!(AT91C_BASE_DBGU->DBGU_SR & AT91C_DBGU_SR_TXRDY));
    AT91C_BASE_DBGU->DBGU_THR = (data & 0x1FF);
}

//*----------------------------------------------------------------------------
//* \fn    AT91F_GetChar
//* \brief This function allows data rx by USART
//*----------------------------------------------------------------------------
char AT91F_GetChar(void)
{
    int timeout = AT91C_MASTER_CLOCK/10;

    while(!(AT91C_BASE_DBGU->DBGU_SR & AT91C_DBGU_SR_RXRDY) && timeout)
            timeout--;
    if (timeout)  // Test for timeout in AT91F_GetChar
        return ((AT91C_BASE_DBGU->DBGU_RHR) & 0x1FF);
    else
        error = 1;
    return 0xff;
}

/* Runtime flags: */
//#define USECRC  (1<<0)
//#define VERIFY  (1<<1)
//#define YMODEM  (1<<2)

/* Current xmodem operation: */
//#define XNULL   0
//#define XUP     1
//#define XDOWN   2

/* X/Ymodem protocol: */
#define SOH     0x01
//#define STX     0x02
#define EOT     0x04
#define ACK     0x06
#define NAK     0x15
#define CAN     0x18
#define ESC     0x1b

#define PKTLEN_128  128
//#define PKTLEN_1K   1024

//*----------------------------------------------------------------------------
//* \fn    getbytes
//* \brief
//*----------------------------------------------------------------------------
static ushort getbytes(char *pData, unsigned int length)
{
    ushort  crc = 0;
    unsigned int cpt;
    char c;

    for (cpt = 0; cpt < length; ++cpt)
    {
        c = AT91F_GetChar();
        if (error)
            return 1;
        crc = AT91F_GetCrc(c,crc);
        //crc = (crc << 8) ^ xcrc16tab[(crc>>8) ^ c];
        if(sizeOfData || modeOfTransfer)
        {
            *pData++ = c;
             if(length == PKTLEN_128) sizeOfData--;
        }
    }

    return crc;
}

//*----------------------------------------------------------------------------
//* \fn    putPacket
//* \brief Used by Xup to send packets.
//*----------------------------------------------------------------------------
static int putPacket(uchar *tmppkt, uchar sno)
{
    int     i;
    ushort  chksm;
    char data;

    chksm = 0;

    AT91F_PutChar(SOH);

    AT91F_PutChar(sno);
    AT91F_PutChar((uchar)~(sno));

    for(i=0;i<PKTLEN_128;i++)
    {
        if(sizeOfData || modeOfTransfer)
        {
            data = *tmppkt++;
            sizeOfData--;
        }
        else
            data = 0x00;

        AT91F_PutChar(data);

        //chksm = (chksm<<8) ^ xcrc16tab[(chksm>>8)^data];
        chksm = AT91F_GetCrc(data,chksm);
    }

    /* An "endian independent way to extract the CRC bytes. */
    AT91F_PutChar((char)(chksm >> 8));
    AT91F_PutChar((char)chksm);

    return(AT91F_GetChar());  /* Wait for ack */
}

//*----------------------------------------------------------------------------
//* \fn    getPacket
//* \brief Used by Xdown to retrieve packets.
//*----------------------------------------------------------------------------
static int getPacket(char *pData, uchar sno)
{
    uchar   seq[2];
    ushort  crc, xcrc;

    getbytes((char *)seq,2);
    xcrc = getbytes(pData,PKTLEN_128);
    if(error)
        return (-1);

    /* An "endian independent way to combine the CRC bytes. */
    crc  = (ushort)AT91F_GetChar() << 8;
    crc += (ushort)AT91F_GetChar();

    if(error == 1)
        return (-1);

    if ((crc != xcrc) || (seq[0] !=  sno) || (seq[1] != (uchar) (~sno)))
    {
        AT91F_PutChar(CAN);
        return(-1);
    }

    AT91F_PutChar(ACK);
    return(0);
}

//*----------------------------------------------------------------------------
//* \fn    Xup
//* \brief Called when a transfer from target to host is being made (considered
//*        an upload).
//*----------------------------------------------------------------------------
static void Xup(char *pData, unsigned int length)
{
    uchar   c, sno = 1;
    int     done;

    error = 0;
    if(!length) modeOfTransfer = 1;
    else{
        sizeOfData = length;
        modeOfTransfer = 0;
    }

    if (length & (PKTLEN_128-1)) {
        length += PKTLEN_128;
        length &= ~(PKTLEN_128-1);
    }

    /* Startup synchronization... */
    /* Wait to receive a NAK or 'C' from receiver. */
    done = 0;
    while(!done) {
        c = (uchar)AT91F_GetChar();
        if(error) { // Test for timeout in AT91F_GetChar
            error = 0;
            c = (uchar)AT91F_GetChar();
            if (error){
                error = 0;
                return;
//                return -2;
            }
        }
        switch(c) {
        case NAK:
            done = 1;
            // ("CSM");
            break;
        case 'C':
            done = 1;
            // ("CRC");
            break;
        case 'q':   /* ELS addition, not part of XMODEM spec. */
           return;
//           return(0);
        default:
            break;
        }
    }

    done = 0;
    sno = 1;
    while(!done) {
        c = (uchar)putPacket((uchar *)pData, sno);
        if(error) { // Test for timeout in AT91F_GetChar
            error = 0;
            return;
//            return (-1);
        }
        switch(c) {
        case ACK:
            ++sno;
            length -= PKTLEN_128;
            pData += PKTLEN_128;
            // ("A");
            break;
        case NAK:
            // ("N");
            break;
        case CAN:
        case EOT:
        default:
            done = -1;
            break;
        }
        if (!length) {
            AT91F_PutChar(EOT);
            AT91F_GetChar();  /* Flush the ACK */
            break;
        }
        // ("!");
    }

    modeOfTransfer = 0;
    // ("Xup_done.");
    return;
    //    return(0);
}


//*----------------------------------------------------------------------------
//* \fn    Xdown
//* \brief Called when a transfer from host to target is being made (considered
//*        an download).
//*----------------------------------------------------------------------------
static void Xdown(char *pData, unsigned int length)
{
    long    timeout;
    char    c;
    int     done, nbrOfTimeOut = 100;
    uchar   sno = 0x01;
    int     dataTransfered = 0;

    unsigned int loopsPerSecond = AT91C_MASTER_CLOCK/10;

    error = 0;

    if(length == 0) modeOfTransfer = 1;
    else{
        sizeOfData = length;
        modeOfTransfer = 0;
    }

    /* Startup synchronization... */
    /* Continuously send NAK or 'C' until sender responds. */
    // ("Xdown");
    while(1) {
        AT91F_PutChar('C');
        timeout = loopsPerSecond;
        while(!(AT91C_BASE_DBGU->DBGU_SR & AT91C_DBGU_SR_RXRDY) && timeout)
            timeout--;
        if (timeout)
            break;

        if(!(--nbrOfTimeOut))
            return;
//            return -1;
    }

    done = 0;
    // ("Got response");
    while(done == 0) {
        c = (char)AT91F_GetChar();
        if(error) { // Test for timeout in AT91F_GetChar
            error = 0;
            return;
//            return (-1);
        }
        switch(c) {
        case SOH:               /* 128-byte incoming packet */
            // ("O");
            done = getPacket(pData, sno);
            if(error) { // Test for timeout in AT91F_GetChar
                error = 0;
                return;
//                return (-1);
            }
            if (done == 0) {
                ++sno;
                pData += PKTLEN_128;
                dataTransfered += PKTLEN_128;
            }
            break;
        case EOT:   // ("E");
             AT91F_PutChar(ACK);
             done = dataTransfered;
             break;
        case CAN:       // ("C");
        case ESC:       /* "X" User-invoked abort */
        default:
            done = -1;
            break;
        }
        // ("!");
    }
    modeOfTransfer = 0;
    return;
//    return(done);
}

//*----------------------------------------------------------------------------
//* \fn    AT91F_XMODEM_Open
//* \brief Initialize XMODEM service
//*----------------------------------------------------------------------------
AT91PS_XMODEM AT91F_XMODEM_Open(AT91PS_XMODEM pXmodem)
{
    pXmodem->AT91F_XMD_Xup   = Xup;
    pXmodem->AT91F_XMD_Xdown = Xdown;

    error = 0;

    return pXmodem;
}
