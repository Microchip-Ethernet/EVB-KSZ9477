//*----------------------------------------------------------------------------
//*         ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : main.h
//* Object              : main application header
//*----------------------------------------------------------------------------

#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>

// Autobaudrate State Machine Phases
#define AT91C_INIT                0
#define AT91C_OSC_FREQ_1ST_PASS    1
#define AT91C_OSC_FREQ_2ND_PASS    2
#define AT91C_SET_BAUDRATE        3
#define AT91C_TEST_UART            4
#define AT91C_FINAL                5

#define AT91SAM9M11
//*----------------------------------------------------------------------------
//* AT91SAM9M11
//*----------------------------------------------------------------------------
#ifdef AT91SAM9M11
#include "AT91SAM9M11.h"
#define AT91C_MASTER_CLOCK      48000000

// UDP High Speed Part
#define UDP_HIGH_SPEED      1

// DBGU Part
#define AT91C_DRXD      AT91C_PB12_DRXD
#define AT91C_DTXD      AT91C_PB13_DTXD
#define DBGU_PIO_ID     AT91C_ID_PIOB
#define DBGU_BASE_PIO   AT91C_BASE_PIOB

#define AT91f_OpenDbguPIO() { \
    AT91C_BASE_PIOB->PIO_ASR = AT91C_DTXD | AT91C_DRXD; \
    AT91C_BASE_PIOB->PIO_PDR = AT91C_DTXD | AT91C_DRXD; \
}
#define AT91f_CloseDbguPIO() { \
    AT91C_BASE_PIOB->PIO_ODR = AT91C_DTXD | AT91C_DRXD; \
    AT91C_BASE_PIOB->PIO_PER = AT91C_DTXD | AT91C_DRXD; \
}

#endif


#ifdef UDP_HIGH_SPEED
#include "cdc_enumerate_hs.h"
#else
#include "cdc_enumerate.h"
#endif


/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
// MISCELLANEOUS
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef TRUE
#define    TRUE                    1
#endif
#ifndef FALSE
#define    FALSE                   0
#endif

#define    DELAY                   1000000

#define AT91C_BAUDRATE_115200    115200


#ifdef UDP_HIGH_SPEED
#define SIZEBUFMAX              512
#else
#define SIZEBUFMAX              64
#endif

#define AT91C_DBGU_ASYNC_MODE ( AT91C_DBGU_MR_CHMODE_NORMAL + \
                                AT91C_DBGU_MR_NBSTOP_1_BIT + \
                                AT91C_DBGU_MR_PAR_NONE + \
                                AT91C_DBGU_MR_CHRL_8_BITS + \
                                AT91C_DBGU_MR_CLKS_CLOCK )
#define AT91C_DBGU_ERRORS        (AT91C_DBGU_SR_OVRE | AT91C_DBGU_SR_FRAME | AT91C_DBGU_SR_PARE)

typedef struct _AT91S_XMODEM
{
    // Public Methods:
    void (*AT91F_XMD_Xup)   (char *pData, unsigned int length);
    void (*AT91F_XMD_Xdown) (char *pData, unsigned int length);
} AT91S_XMODEM, *AT91PS_XMODEM;

#endif
