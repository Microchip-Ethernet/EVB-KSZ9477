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
 * \page skip_nand_page SkipBlockNandFlash
 * 
 * \section Purpose 
 * 
 * SkipBlockNandFlash layer supplies application a set of interface to operate nandflash, which include 
 * initialize, block erase, block write/read, page write/read. This layer is called by upper layer 
 * applications, and it will call lower layer drivers, such as \ref ecc_nand_page, \ref raw_nand_page. 
 * 
 * \section Usage
 * -# SkipBlockNandFlash_Initialize() is used to initializes a SkipBlockNandFlash instance. Scans 
 *      the device to retrieve or create block status information. 
 * -# SkipBlockNandFlash_EraseBlock() is used to erase a certain block in the device, user can 
 *      select "check block status before erase" or "erase without check" 
 * -# User can use SkipBlockNandFlash_WriteBlock() to write a certain block and SkipBlockNandFlash_WritePage() 
 *      to write a certain page. The functions will check the block status before write, if the block 
 *      is not a good block, the write command will not be issued. 
 * -# User can use SkipBlockNandFlash_ReadBlock() to read a certain block and SkipBlockNandFlash_ReadPage() 
 *      to read a certain page. The functions will check the block status before read, if the block 
 *      is not a good block, the read command will not be issued. ECC is also checked after read 
 *      operation is finished, an error will be reported if ecc check got errors. 
*/

#ifndef SKIPBLOCKNANDFLASH_H
#define SKIPBLOCKNANDFLASH_H

/*------------------------------------------------------------------------------ */
/*         Headers                                                               */
/*------------------------------------------------------------------------------ */

#include "NandCommon.h"
#include "EccNandFlash.h"

/*------------------------------------------------------------------------------ */
/*         Definitions                                                           */
/*------------------------------------------------------------------------------ */

#define NandBlockStatus_BAD   0xBA

/* Erase types */
/** Check block before erase */
#define NORMAL_ERASE    0x00000000
/** Do NOT check the block status before erasing it */
#define SCRUB_ERASE     0x0000EA11
/** Values returned by the CheckBlock() function */
#define BADBLOCK        255
#define GOODBLOCK       254


/*------------------------------------------------------------------------------ */
/*         Types                                                                 */
/*------------------------------------------------------------------------------ */

struct SkipBlockNandFlash {
    struct EccNandFlash ecc;
};

/*------------------------------------------------------------------------------ */
/*         Exported functions                                                    */
/*------------------------------------------------------------------------------ */

extern uint8_t SkipBlockNandFlash_CheckBlock(
    const struct SkipBlockNandFlash *skipBlock,
    uint16_t block);

extern uint8_t SkipBlockNandFlash_Initialize(
    struct SkipBlockNandFlash *skipBlock,
    const struct NandFlashModel *model,
    uint32_t commandAddress,
    uint32_t addressAddress,
    uint32_t dataAddress,
    const Pin pinChipEnable,
    const Pin pinReadyBusy);

extern uint8_t SkipBlockNandFlash_EraseBlock(
    struct SkipBlockNandFlash *skipBlock,
    uint16_t block,
    uint32_t eraseType);

extern uint8_t SkipBlockNandFlash_ReadPage(
    const struct SkipBlockNandFlash *skipBlock,
    uint16_t block,
    uint16_t page,
    void *data,
    void *spare);

uint8_t SkipBlockNandFlash_ReadBlock(
    const struct SkipBlockNandFlash *skipBlock,
    uint16_t block,
    void *data);

extern uint8_t SkipBlockNandFlash_WritePage(
    const struct SkipBlockNandFlash *skipBlock,
    uint16_t block,
    uint16_t page,
    void *data,
    void *spare);

uint8_t SkipBlockNandFlash_WriteBlock(
    const struct SkipBlockNandFlash *skipBlock,
    uint16_t block,
    void *data);

#endif /*#ifndef SKIPBLOCKNANDFLASH_H */

