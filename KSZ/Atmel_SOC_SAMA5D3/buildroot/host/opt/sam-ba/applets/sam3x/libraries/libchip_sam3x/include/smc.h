/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2010, Atmel Corporation
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
/**
*  \file
*
*  Definitions and function prototype for smc module
*/

#ifndef _SMC_
#define _SMC_

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/

/*
 * NFC definitions
 */

/** Base address of NFC SRAM */
#define NFC_SRAM_BASE_ADDRESS 0x20100000
/** Base address for NFC Address Command */
#define NFC_CMD_BASE_ADDR     0x60000000

/*
 * ECC definitions (Hsiao Code Errors)
 */

/** A single bit was incorrect but has been recovered. */
#define Hsiao_ERROR_SINGLEBIT         1

/** The original code has been corrupted. */
#define Hsiao_ERROR_ECC               2

/** Multiple bits are incorrect in the data and they cannot be corrected. */
#define Hsiao_ERROR_MULTIPLEBITS      3

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/*
 * NFC functions
 */

extern void SMC_NFC_Configure(Smc* pSmc, uint32_t mode);
extern void SMC_NFC_Reset(Smc* pSmc);
extern void SMC_NFC_EnableNfc(Smc* pSmc);
extern void SMC_NFC_EnableSpareRead(Smc* pSmc);
extern void SMC_NFC_DisableSpareRead(Smc* pSmc);
extern void SMC_NFC_EnableSpareWrite(Smc* pSmc);
extern void SMC_NFC_DisableSpareWrite(Smc* pSmc);
extern uint8_t SMC_NFC_isSpareRead(Smc* pSmc);
extern uint8_t SMC_NFC_isSpareWrite(Smc* pSmc);
extern uint8_t SMC_NFC_isTransferComplete(Smc* pSmc);
extern uint8_t SMC_NFC_isReadyBusy(Smc* pSmc);
extern uint8_t SMC_NFC_isNfcBusy(Smc* pSmc);
extern uint32_t SMC_NFC_GetStatus(Smc* pSmc);

extern void SMC_NFC_SendCommand(Smc* pSmc, uint32_t cmd, uint32_t addressCycle, uint32_t cycle0);

/*
 * ECC functions
 */
extern void SMC_ECC_Configure(Smc* pSmc, uint32_t type, uint32_t pageSize);
extern uint32_t SMC_ECC_GetCorrectoinType(Smc* pSmc);
extern uint8_t SMC_ECC_GetStatus(Smc *pSmc, uint8_t eccNumber);
extern void SMC_ECC_GetValue(Smc* pSmc, uint32_t *ecc);
extern void SMC_ECC_GetEccParity(
    uint32_t pageDataSize,
    uint8_t *code,
    uint8_t dataPath);
extern uint8_t SMC_ECC_VerifyHsiao(
    uint8_t *data,
    uint32_t size,
    const uint8_t *originalCode,
    const uint8_t *verifyCode,
    uint8_t dataPath);

#endif /* #ifndef _SMC_ */

