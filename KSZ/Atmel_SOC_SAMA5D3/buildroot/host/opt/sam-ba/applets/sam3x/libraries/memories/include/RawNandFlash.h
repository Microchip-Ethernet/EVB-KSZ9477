/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2009, Atmel Corporation
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
  *  Include Defines & macros for the raw nand flash layer.
  */

#ifndef RAWNANDFLASH_H
#define RAWNANDFLASH_H

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/
#include <stdint.h>

#include "NandFlashModel.h"
#include "NandFlashDma.h"
/*----------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/


/** Describes a physical NandFlash chip connected to the SAM microcontroller.*/
struct RawNandFlash {

    /** Model describing this NandFlash characteristics.*/
    struct NandFlashModel model;
    /** Address for sending commands to the NandFlash.*/
    uint32_t commandAddress;
    /** Address for sending addresses to the NandFlash.*/
    uint32_t addressAddress;
    /** Address for sending data to the NandFlash.*/
    uint32_t dataAddress;
    /** Pin used to enable the NandFlash chip.*/
    Pin pinChipEnable;
    /** Pin used to monitor the ready/busy signal from the NandFlash.*/
    Pin pinReadyBusy;
};


/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/
extern uint8_t RawNandFlash_Initialize(
    struct RawNandFlash *raw,
    const struct NandFlashModel *model,
    uint32_t commandAddress,
    uint32_t addressAddress,
    uint32_t dataAddress,
    const Pin pinChipEnable,
    const Pin pinReadyBusy);

extern void RawNandFlash_Reset(const struct RawNandFlash *raw);

extern uint32_t RawNandFlash_ReadId(const struct RawNandFlash *raw);

extern uint8_t RawNandFlash_EraseBlock(
    const struct RawNandFlash *raw,
    uint16_t block);

extern uint8_t RawNandFlash_ReadPage(
    const struct RawNandFlash *raw,
    uint16_t block,
    uint16_t page,
    void *data,
    void *spare);

extern uint8_t RawNandFlash_WritePage(
    const struct RawNandFlash *raw,
    uint16_t block,
    uint16_t page,
    void *data,
    void *spare);

extern uint8_t RawNandFlash_CopyPage(
    const struct RawNandFlash *raw,
    uint16_t sourceBlock,
    uint16_t sourcePage,
    uint16_t destBlock,
    uint16_t destPage);

extern uint8_t RawNandFlash_CopyBlock(
    const struct RawNandFlash *raw,
    uint16_t sourceBlock,
    uint16_t destBlock);

#endif /*#ifndef RAWNANDFLASH_H*/

