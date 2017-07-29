/* ----------------------------------------------------------------------------
 *         SAM Software Package License 
 * ----------------------------------------------------------------------------
 * Copyright (c) 2011, Atmel Corporation
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

#ifndef _NANDSMC_
#define _NANDSMC_

/*----------------------------------------------------------------------------
 *        Type
 *----------------------------------------------------------------------------*/
typedef union _SmcOperation {
    uint8_t BCfg;
    struct _SmcOpBits {
        uint8_t nfc:1,     /**< NAND Flash Controller 0: disable, 1: enable */
                nfcSram:1, /**< NAND Flash Controller host sram 0: disable, 1: enable */
                xfrDma:1,  /**< Send/Stop data transfer */
                eccType:3, /**< ECC type 0:Software Ecc, 1: Hsiao Ecc, 2: Pmecc */
                res: 2;    /**< reserved*/
    } bCfg;
} SmcOperation;
 
/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/
/*
 * NFC Transfer paramter
 */
#define SMC_TRANS_WITH_DMA ( 1 << 0 )
#define SMC_TRANS_HOST_EN  ( 1 << 1 )

/*
 * NFC ALE CLE command paramter
 */
#define SMC_ALE_COL_EN     ( 1 << 0 ) 
#define SMC_ALE_ROW_EN     ( 1 << 1 ) 
#define SMC_CLE_WRITE_EN   ( 1 << 2 ) 
#define SMC_CLE_DATA_EN    ( 1 << 3 ) 
#define SMC_CLE_VCMD2_EN   ( 1 << 4 ) 

/*
 * NFC paramter
 */
#define SMC_NFC_ENABLE  1
#define SMC_NFC_DISABLE 0
#define SMC_NFC_SRAM_ENABLE  1
#define SMC_NFC_SRAM_DISABLE 0
#define SMC_TRANS_DMA_ENABLE  1
#define SMC_TRANS_DMA_DISABLE 0

/*
 * NFC ECC paramter
 */
#define SMC_ECC_NOECC     0
#define SMC_ECC_SOFTWARE  1
#define SMC_ECC_PMECC     2
#define SMC_ECC_INTERNAL  3
#define SMC_ECC_HSIAO     4


/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/*
 * NFC functions
 */
extern void Smc_OpConfigure(uint8_t cfg);
extern uint8_t Smc_GetOpStatus(void);
extern uint8_t isSmcOpNfcEn(void);
extern void enableSmcOpNfc(void);
extern void disableSmcOpNfc(void);
extern uint8_t isSmcOpNfcSramEn(void);
extern void enableSmcOpNfcSram(void);
extern void disableSmcOpNfcSram(void);
extern uint8_t isSmcOpTransDmaEn(void);
extern void enableSmcOpTransDma(void);
extern void disableSmcOpTransDma(void);
extern uint8_t isSmcOpNoEcc(void);
extern uint8_t isSmcOpEccHsiao(void);
extern uint8_t isSmcOpEccPmecc(void);
extern void setSmcOpEccType(uint8_t eccTpye);
extern uint8_t getSmcOpEccType(void);

extern void Smc_Issue_Cle_Ale(
     const struct RawNandFlash *raw,
     uint8_t mode,
     uint32_t cmd1,
     uint32_t cmd2,
     uint32_t colAddress,
     uint32_t rowAddress);

extern void Smc_Data_Array_Out (
    uint8_t busWidth,
    uint8_t hostSram,
    uint8_t *buffer,
    uint32_t size);

extern void Smc_Data_Array_In (
    uint8_t busWidth,
    uint8_t hostSram,
    uint8_t *buffer,
    uint32_t size);

extern void Smc_WaitForNandReady(const struct RawNandFlash *raw);
extern uint8_t Smc_IsOperationComplete(const struct RawNandFlash *raw);
#endif /* #ifndef _NANDSMC_ */

