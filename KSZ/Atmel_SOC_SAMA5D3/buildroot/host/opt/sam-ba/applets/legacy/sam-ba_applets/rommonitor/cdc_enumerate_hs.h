//*----------------------------------------------------------------------------
//*      ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : cdc_enumerate_hs.h
//* Object              : Handle CDC enumeration
//*
//* 1.0 Apr 20 200 	: ODi Creation
//*----------------------------------------------------------------------------
#ifndef CDC_ENUMERATE_H
#define CDC_ENUMERATE_H

#include "usb.h"

#define AT91C_EP_OUT   1
#define AT91C_EP_IN    2
#define AT91C_EP_INTER 3

//! CDC data structure
typedef struct _AT91S_CDC
{
    AT91PS_UDPHS         pInterface;
    volatile unsigned int * pInterfaceEPT;
    unsigned char        currentConfiguration;    //!< Current configuration
    unsigned char        currentConnection;       //!< Current connection
    unsigned short       devStatus;               //!< Device Status Cf Table 9.4 in USB spec
    unsigned short       eptStatus;
    S_usb_request        *pSetup;                 //!< Last setup packet received
    unsigned char (*IsConfigured)(struct _AT91S_CDC *pCdc);
    unsigned int  (*Write) (struct _AT91S_CDC *pCdc, const char *pData, unsigned int length);
    unsigned int  (*Read)  (struct _AT91S_CDC *pCdc, char *pData, unsigned int length);
} AT91S_CDC, *AT91PS_CDC;

AT91PS_CDC AT91F_CDC_Open(AT91PS_CDC pCdc, AT91PS_UDPHS pUdp, volatile unsigned int * pFIFO);
void AT91F_InitUSB(void);

#endif
