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

#ifndef HSMC4_ECC_H
#define HSMC4_ECC_H

//------------------------------------------------------------------------------
//         Headers
//------------------------------------------------------------------------------

#include <board.h>

//------------------------------------------------------------------------------
//         Definitions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \page "Hsiao Code Errors"
/// These are the possible errors when trying to verify a block of data encoded
/// using a Hsiao code:
/// 
/// !Errors:
///  - Hsiao_ERROR_SINGLEBIT
///  - Hsiao_ERROR_ECC
///  - Hsiao_ERROR_MULTIPLEBITS

/// A single bit was incorrect but has been recovered.
#define Hsiao_ERROR_SINGLEBIT         1

/// The original code has been corrupted.
#define Hsiao_ERROR_ECC               2

/// Multiple bits are incorrect in the data and they cannot be corrected.
#define Hsiao_ERROR_MULTIPLEBITS      3

//------------------------------------------------------------------------------
//         Exported functions
//------------------------------------------------------------------------------

extern void HSMC4_EccConfigure(unsigned int type, unsigned int pageSize);

extern unsigned int HSMC4_GetEccCorrectoinType(void);

extern void HSMC4_EccGetValue(unsigned int *ecc);

extern void HSMC4_GetEccParity(
    unsigned int pageDataSize, 
    unsigned char *code, 
    unsigned char dataPath);
   
extern unsigned char HSMC4_VerifyHsiao(
    unsigned char *data,
    unsigned int size,
    const unsigned char *originalCode,
    const unsigned char *verifyCode,
    unsigned char dataPath);

#endif //#ifndef HSMC4_ECC_H

