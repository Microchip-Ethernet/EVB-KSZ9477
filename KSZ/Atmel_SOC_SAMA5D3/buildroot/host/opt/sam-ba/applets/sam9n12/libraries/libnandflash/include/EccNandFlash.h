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
 * \page ecc_nand_page ECC Nand Flash
 * 
 * \section Purpose
 * 
 * EccNandFlash layer is called by SkipBlockNandFlash driver, it will call the bl driver (RawNandFlash) 
 * to do write/read operations, and do ECC check to the write/read result, it then will feedback the 
 * ecc check result to the upper SkipBlockNandFlash layer driver. 
 * 
 * \section Usage 
 * 
 * -# EccNandFlash_Initialize() is used to initializes an EccNandFlash instance. 
 * -# EccNandFlash_WritePage() is used to write a Nandflash page with ecc result, the function 
 *      will calculate ecc for the data that is going to be written, and write data and spare(with 
 *      calculated ecc) to Nandflash device. 
 * -# EccNandFlash_ReadPage() is uese to read a Nandflash page with ecc check, the function 
 *      will read out data and spare first, then it calculates ecc with data and then compare with 
 *      the readout ecc, and feedback the ecc check result to dl driver. 
*/

#ifndef ECCNANDFLASH_H
#define ECCNANDFLASH_H

/*------------------------------------------------------------------------------ */
/*         Headers                                                               */
/*------------------------------------------------------------------------------ */

#include "RawNandFlash.h"
#include <board.h>

/*------------------------------------------------------------------------------ */
/*         Types                                                                 */
/*------------------------------------------------------------------------------ */

struct EccNandFlash {

    struct RawNandFlash raw;
};

/*------------------------------------------------------------------------------ */
/*         Exported functions                                                    */
/*------------------------------------------------------------------------------ */

extern uint8_t EccNandFlash_Initialize(
    struct EccNandFlash *ecc,
    const struct NandFlashModel *model,
    uint32_t commandAddress,
    uint32_t addressAddress,
    uint32_t dataAddress,
    const Pin pinChipEnable,
    const Pin pinReadyBusy);

extern uint8_t EccNandFlash_ReadPage(
    const struct EccNandFlash *ecc,
    uint16_t block,
    uint16_t page,
    void *data,
    void *spare);

extern uint8_t EccNandFlash_WritePage(
    const struct EccNandFlash *ecc,
    uint16_t block,
    uint16_t page,
    void *data,
    void *spare);

#endif /*#ifndef ECCNANDFLASH_H */

