/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support 
 * ----------------------------------------------------------------------------
 * Copyright (c) 2008, Atmel Corporation
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
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

#ifndef HSMC4_H
#define HSMC4_H

//------------------------------------------------------------------------------
//         Headers
//------------------------------------------------------------------------------

#include <board.h>

//------------------------------------------------------------------------------
//         Definitions
//------------------------------------------------------------------------------
#define NFC_SRAM_BASE_ADDRESS 0x20100000

#ifndef BOARD_NF_COMMAND_ADDR
    #define CMD_BASE_ADDR 0x60000000
#else
    #define CMD_BASE_ADDR BOARD_NF_COMMAND_ADDR
#endif

//------------------------------------------------------------------------------
//         Exported functions
//------------------------------------------------------------------------------
extern void HSMC4_SendCommand (unsigned int cmd, unsigned int addressCycle, unsigned int cycle0);
extern unsigned char HSMC4_isHostBusy(void);
extern unsigned char HSMC4_TransferComplete(void);
extern unsigned char HSMC4_isReadyBusy(void);
extern unsigned char HSMC4_isNfcBusy(void);
extern unsigned char HSMC4_isEccReady(void);
extern void HSMC4_SetMode(unsigned int mode);
extern void HSMC4_ResetNfc(void);
extern void HSMC4_EnableNfc(void);
extern void HSMC4_EnableNfcHost(void);

extern void HSMC4_EnableSpareRead(void);
extern void HSMC4_DisableSpareRead(void);
extern void HSMC4_EnableSpareWrite(void);
extern void HSMC4_DisableSpareWrite(void);
extern unsigned char HSMC4_isSpareRead(void);
extern unsigned char HSMC4_isSpareWrite(void);
extern unsigned int HSMC4_GetStatus(void);

#endif //#ifndef HSMC4_H

