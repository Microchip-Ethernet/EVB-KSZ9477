/* ----------------------------------------------------------------------------
 *         SAM Software Package License 
 * ----------------------------------------------------------------------------
 * Copyright (c) 2013, Atmel Corporation
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

/** \file */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include <board.h>
#include <libnandflash.h>
#include <string.h>

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/
 
/** Casts */
#define ECC(skipBlock)    ((struct EccNandFlash *) skipBlock)
#define RAW(skipBlock)    ((struct RawNandFlash *) skipBlock)
#define MODEL(skipBlock)  ((struct NandFlashModel *) skipBlock)

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/
 
/**
 * \brief Returns BADBLOCK if the given block of a nandflash device is bad; returns
 * GOODBLOCK if the block is good; or returns a NandCommon_ERROR code.
 *
 * \param skipBlock  Pointer to a SkipBlockNandFlash instance.
 * \param block  Number of block to check.
 */
 
uint8_t SkipBlockNandFlash_CheckBlock(
    const struct SkipBlockNandFlash *skipBlock,
    uint16_t block)
{

#if !defined (OP_BOOTSTRAP_on)

    uint8_t spare[NandCommon_MAXPAGESPARESIZE];
    uint8_t error;
    uint8_t badBlockMarker;
    const struct NandSpareScheme *scheme;
    /* Retrieve model scheme */
    scheme = NandFlashModel_GetScheme(MODEL(skipBlock));
    
    /* Read spare area of first page of block */
    error = RawNandFlash_ReadPage(RAW(skipBlock), block, 0, 0, spare);
    if (error) {

        TRACE_ERROR("CheckBlock: Cannot read page #0 of block #%d\n\r", block);
        return error;
    }

    NandSpareScheme_ReadBadBlockMarker(scheme, spare, &badBlockMarker);
    if (badBlockMarker != 0xFF) {

        return BADBLOCK;
    }

    /* Read spare area of second page of block */
    error = RawNandFlash_ReadPage(RAW(skipBlock), block, 1, 0, spare);
    if (error) {

        TRACE_ERROR("CheckBlock: Cannot read page #1 of block #%d\n\r", block);
        return error;
    }

    NandSpareScheme_ReadBadBlockMarker(scheme, spare, &badBlockMarker);
    if (badBlockMarker != 0xFF) {

        return BADBLOCK;
    }
#endif

    return GOODBLOCK;
}

/**
 * \brief Initializes a SkipBlockNandFlash instance. Scans the device to retrieve or
 * create block status information.
 * \param skipBlock  Pointer to a SkipBlockNandFlash instance.
 * \param model  Pointer to the underlying nand chip model. Can be 0.
 * \param commandAddress  Address at which commands are sent.
 * \param addressAddress  Address at which addresses are sent.
 * \param dataAddress  Address at which data is sent.
 * \param pinChipEnable  Pin controlling the CE signal of the NandFlash.
 * \param pinReadyBusy  Pin used to monitor the ready/busy signal of the Nand.
 */

uint8_t SkipBlockNandFlash_Initialize(
    struct SkipBlockNandFlash *skipBlock,
    const struct NandFlashModel *model,
    uint32_t commandAddress,
    uint32_t addressAddress,
    uint32_t dataAddress,
    const Pin pinChipEnable,
    const Pin pinReadyBusy)
{
    uint8_t error;
#if !defined(OP_BOOTSTRAP_on)
    uint32_t numBlocks;
    uint32_t block;
#endif

    TRACE_DEBUG("SkipBlockNandFlash_Initialize()\n\r");

    /* Initialize SkipBlockNandFlash */
    #if !defined(OP_BOOTSTRAP_on)
    error = EccNandFlash_Initialize(ECC(skipBlock),
                                    model,
                                    commandAddress,
                                    addressAddress,
                                    dataAddress,
                                    pinChipEnable,
                                    pinReadyBusy);
    #else
    error = RawNandFlash_Initialize(RAW(skipBlock),
                                    model,
                                    commandAddress,
                                    addressAddress,
                                    dataAddress,
                                    pinChipEnable,
                                    pinReadyBusy);
#endif

#if !defined(OP_BOOTSTRAP_on)
    if (error) {

        return error;
    }

    /* Retrieve model information */
    numBlocks = NandFlashModel_GetDeviceSizeInBlocks(MODEL(skipBlock));

    /* Initialize block statuses */
    TRACE_DEBUG("Retrieving bad block information ...\n\r");

    /* Retrieve block status from their first page spare area */

    for (block = 0; block < numBlocks; block++) {

        /* Read spare of first page */
        error = SkipBlockNandFlash_CheckBlock(skipBlock, block);

        if (error != GOODBLOCK) {
            
            if (error == BADBLOCK) {
                
                TRACE_DEBUG("Block #%d is bad\n\r", (unsigned int)block);
            }
            else {
                
                TRACE_ERROR(
                "SkipBlockNandFlash_Initialize: Cannot retrieve info from block #%u\n\r", (unsigned int)block);
            }
        }
    }
#endif

    return 0;
}


/**
 * \brief Erases a block of a SkipBlock NandFlash.
 * \param skipBlock  Pointer to a SkipBlockNandFlash instance.
 * \param block  Number of block to erase.
 * \return the RawNandFlash_EraseBlock code or NandCommon_ERROR_WRONGSTATUS.
*/

uint8_t SkipBlockNandFlash_EraseBlock(
    struct SkipBlockNandFlash *skipBlock,
    uint16_t block,
    uint32_t eraseType)
{
    uint8_t error;
    const struct NandSpareScheme *scheme;
    uint8_t spare[NandCommon_MAXPAGESPARESIZE];

    /* TRACE_INFO("SkipBlockNandFlash_EraseBlock(%d)\n\r", block); */

    if (eraseType != SCRUB_ERASE) {
        /* Check block status */
        if (SkipBlockNandFlash_CheckBlock(skipBlock, block) != GOODBLOCK) {
    
            TRACE_INFO("SkipBlockNandFlash_EraseBlock: Block is BAD\n\r");
            return NandCommon_ERROR_BADBLOCK;
        }
    }

    /* Erase block */
    error = RawNandFlash_EraseBlock(RAW(skipBlock), block);
    if (error) {

        /* Try to mark the block as BAD */
        TRACE_ERROR("SkipBlockNandFlash_EraseBlock: Cannot erase block, try to mark it BAD\n\r");

        /* Retrieve model scheme */
        scheme = NandFlashModel_GetScheme(MODEL(skipBlock));

        memset(spare, 0xFF, NandCommon_MAXPAGESPARESIZE);
        NandSpareScheme_WriteBadBlockMarker(scheme, spare, NandBlockStatus_BAD);
        return RawNandFlash_WritePage(RAW(skipBlock), block, 0, 0, spare);
    }

    return 0;
}

/**
 * \brief Reads the data and/or the spare area of a page on a SkipBlock nandflash. If
 * the data pointer is not 0, then the block MUST not be BAD
 * \param skipBlock  Pointer to a SkipBlockNandFlash instance.
 * \param block  Number of block to read page from.
 * \param page  Number of page to read inside the given block.
 * \param data  Data area buffer, can be 0.
 * \param spare  Spare area buffer, can be 0.
 * \return NandCommon_ERROR_BADBLOCK if the block is BAD; Otherwise, returns
 * EccNandFlash_ReadPage().
*/

uint8_t SkipBlockNandFlash_ReadPage(
    const struct SkipBlockNandFlash *skipBlock,
    uint16_t block,
    uint16_t page,
    void *data,
    void *spare)
{
#if !defined(OP_BOOTSTRAP_on)
    /* Check that the block is not BAD if data is requested */
    if (SkipBlockNandFlash_CheckBlock(skipBlock, block) != GOODBLOCK) {

        TRACE_ERROR("SkipBlockNandFlash_ReadPage: Block is BAD.\n\r");
        return NandCommon_ERROR_BADBLOCK;
    }

    /* Read data with ECC verification */
    return EccNandFlash_ReadPage(ECC(skipBlock), block, page, data, spare);
#else
    return RawNandFlash_ReadPage(RAW(skipBlock), block, page, data, spare);
#endif
}

/**
 * \brief Reads the data of a whole block on a SkipBlock nandflash.
 * \param skipBlock  Pointer to a SkipBlockNandFlash instance.
 * \param block  Number of block to read page from.
 * \param page  Number of page to read inside the given block.
 * \param data  Data area buffer, can be 0.
 * \param spare  Spare area buffer, can be 0.
 * \return NandCommon_ERROR_BADBLOCK if the block is BAD; Otherwise, returns
 * EccNandFlash_ReadPage().
*/

uint8_t SkipBlockNandFlash_ReadBlock(
    const struct SkipBlockNandFlash *skipBlock,
    uint16_t block,
    void *data)
{
    /* Number of pages per block */
    uint32_t numPagesPerBlock, pageSize;
    /* Page index */
    uint16_t i;
    /* Error returned by SkipBlockNandFlash_WritePage */
    uint8_t error = 0;
    
    /* Retrieve model information */
    pageSize = NandFlashModel_GetPageDataSize(MODEL(skipBlock));
    numPagesPerBlock = NandFlashModel_GetBlockSizeInPages(MODEL(skipBlock));

    /* Check that the block is not BAD if data is requested */
    if (SkipBlockNandFlash_CheckBlock(skipBlock, block) != GOODBLOCK) {

        TRACE_ERROR("SkipBlockNandFlash_ReadBlock: Block is BAD.\n\r");
        return NandCommon_ERROR_BADBLOCK;
    }

    /* Read all the pages of the block */
    for (i = 0; i < numPagesPerBlock; i++) {
        error = EccNandFlash_ReadPage(ECC(skipBlock), block, i, data, 0);
        if (error) {

            TRACE_ERROR("SkipBlockNandFlash_ReadBlock: Cannot read page %d of block %d.\n\r", i, block);
            return error;
        }
        data = (void *) ((uint8_t *) data + pageSize);
    }
    
    return 0;
}

/**
 * \brief Writes the data and/or spare area of a page on a SkipBlock NandFlash.
 * \param skipBlock  Pointer to a SkipBlockNandFlash instance.
 * \param block  Number of the block to write.
 * \param page  Number of the page to write inside the given block.
 * \param data  Data area buffer.
 * \param spare  Spare area buffer.
 * \return NandCommon_ERROR_BADBLOCK if the page is BAD; otherwise,
 * returns EccNandFlash_WritePage().
 */
 
uint8_t SkipBlockNandFlash_WritePage(
    const struct SkipBlockNandFlash *skipBlock,
    uint16_t block,
    uint16_t page,
    void *data,
    void *spare)
{
    /* Check that the block is LIVE */
    if (SkipBlockNandFlash_CheckBlock(skipBlock, block) != GOODBLOCK) {

        TRACE_ERROR("SkipBlockNandFlash_WritePage: Block is BAD.\n\r");
        return NandCommon_ERROR_BADBLOCK;
    }

    /* Write data with ECC calculation */
    return EccNandFlash_WritePage(ECC(skipBlock), block, page, data, spare);
}

/**
 * \brief Writes the data of a whole block on a SkipBlock nandflash.
 * \param skipBlock  Pointer to a SkipBlockNandFlash instance.
 * \param block  Number of block to read page from.
 * \param data  Data area buffer, can be 0.
 * \return NandCommon_ERROR_BADBLOCK if the block is BAD; Otherwise, returns
 * EccNandFlash_ReadPage().
*/

uint8_t SkipBlockNandFlash_WriteBlock(
    const struct SkipBlockNandFlash *skipBlock,
    uint16_t block,
    void *data)
{
    /* Number of pages per block */
    uint32_t numPagesPerBlock;
    /* Page size */
    uint32_t pageSize;
    /* Page index */
    uint16_t i;
    /* Error returned by SkipBlockNandFlash_WritePage */
    uint8_t error = 0;
    
    /* Retrieve model information */
    pageSize = NandFlashModel_GetPageDataSize(MODEL(skipBlock));
    numPagesPerBlock = NandFlashModel_GetBlockSizeInPages(MODEL(skipBlock));

    /* Check that the block is LIVE */
    if (SkipBlockNandFlash_CheckBlock(skipBlock, block) != GOODBLOCK) {

        TRACE_ERROR("SkipBlockNandFlash_WriteBlock: Block is BAD.\n\r");
        return NandCommon_ERROR_BADBLOCK;
    }    
    
    for (i = 0; i < numPagesPerBlock; i++) {
        error = EccNandFlash_WritePage(ECC(skipBlock), block, i, data, 0);
        if (error) {

            TRACE_ERROR("SkipBlockNandFlash_WriteBlock: Cannot write page %d of block %d.\n\r", i, block);
            return NandCommon_ERROR_CANNOTWRITE;
        }
        data = (void *) ((uint8_t *) data + pageSize);
    }

    return 0;
}

