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

#ifndef BOARD_MEMORIES_H
#define BOARD_MEMORIES_H


//------------------------------------------------------------------------------
//         Definitions
//------------------------------------------------------------------------------
#define VDDMEMSEL_1V8 0
#define VDDMEMSEL_3V3 1

//------------------------------------------------------------------------------
//         Exported functions
//------------------------------------------------------------------------------
extern void BOARD_RemapRom(void);

extern void BOARD_RemapRam(void);

extern void BOARD_ConfigureVddMemSel(unsigned char VddMemSel);

extern void BOARD_ConfigureSdram(unsigned char busWidth);

extern void BOARD_ConfigureDdram(unsigned char ddrModel, unsigned char busWidth);

extern void BOARD_ConfigureBcram(unsigned char busWidth);

extern void BOARD_ConfigureNandFlash(unsigned char busWidth);

extern void BOARD_ConfigureNandFlash48MHz(unsigned char busWidth);

extern void BOARD_ConfigureNorFlash(unsigned char busWidth);

extern void BOARD_ConfigureNorFlash48MHz(unsigned char busWidth);

#endif //#ifndef BOARD_MEMORIES_H

