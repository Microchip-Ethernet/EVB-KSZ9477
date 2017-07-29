/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support  -  ROUSSET  -
 * ----------------------------------------------------------------------------
 * Copyright (c) 2008, Atmel Corporation
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * - Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the disclaimer below in the documentation and/or
 * other materials provided with the distribution.
 *
 * Atmel's name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ----------------------------------------------------------------------------
 */

#include "main.h"

extern struct _AT91S_CDC   pCDC;
extern AT91S_XMODEM        xModem;
extern AT91PS_XMODEM       AT91F_XMODEM_Open(AT91PS_XMODEM);
extern void                InitReset(void);


/// Globals
volatile unsigned int      StateMachine = AT91C_FINAL;
volatile unsigned int      CurrentMainClock;



//-------------------------------------------------------------------------------
/// Autobaudrate State Machine
//-------------------------------------------------------------------------------
unsigned int AT91F_EndOfCalibration(void)
{
    unsigned int status;
    static unsigned short NbOfEvents;

    return StateMachine;
}


//-------------------------------------------------------------------------------
/// Performs very low level HW initialization
//-------------------------------------------------------------------------------
void AT91F_LowLevelInit()
{
    //-------------------------------------------------------------------------------
    // Xmodem + CDC Open
    //-------------------------------------------------------------------------------
//    AT91F_XMODEM_Open(&xModem);
    AT91F_CDC_Open(&pCDC, AT91C_BASE_UDPHS, AT91C_BASE_UDPHS_FIFO);
}




