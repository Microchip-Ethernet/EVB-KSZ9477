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
 
/**
 * \unit 
 * !Purpose 
 * 
 *     Type and methods for manipulating NandFlash models. 
 * 
 * !Usage 
 * 
 * -# Find the model of a NandFlash using its device ID with the 
 *    NandFlashModel_Find function. 
 * 
 * -# Retrieve parameters of a NandFlash model using the following functions: 
 *    - NandFlashModel_GetDeviceId 
 *    - NandFlashModel_GetDeviceSizeInBlocks 
 *    - NandFlashModel_GetDeviceSizeInPages 
 *    - NandFlashModel_GetDeviceSizeInBytes 
 *    - NandFlashModel_GetBlockSizeInPages 
 *    - NandFlashModel_GetBlockSizeInBytes 
 *    - NandFlashModel_GetPageDataSize 
 *    - NandFlashModel_GetPageSpareSize
 *    - NandFlashModel_GetDataBusWidth 
 *    - NandFlashModel_UsesSmallBlocksRead 
 *    - NandFlashModel_UsesSmallBlocksWrite 
 */


#ifndef NANDFLASHMODEL_H
#define NANDFLASHMODEL_H
/** \addtogroup nand_model
 *@{
 */

/*------------------------------------------------------------------------------ */
/*         Forward declarations                                                  */
/*------------------------------------------------------------------------------ */

struct NandSpareScheme;

/*------------------------------------------------------------------------------ */
/*         Definitions                                                           */
/*------------------------------------------------------------------------------ */

/** \addtogroup nand_model_option NandFlashModel options
 *  @{
 * This page lists the possible options for a NandFlash chip. 
 * 
 * \section Options
 * - NandFlashModel_DATABUS8 
 * - NandFlashModel_DATABUS16 
 * - NandFlashModel_COPYBACK 
 */

/** Indicates the Nand uses an 8-bit databus. */
#define NandFlashModel_DATABUS8     (0 << 0)

/** Indicates the Nand uses a 16-bit databus. */
#define NandFlashModel_DATABUS16    (1 << 0)

/** The Nand supports the copy-back function (internal page-to-page copy). */
#define NandFlashModel_COPYBACK     (1 << 1)
/** @}*/

/*------------------------------------------------------------------------------ */
/*         Types                                                                 */
/*------------------------------------------------------------------------------ */

/** Describes a particular model of NandFlash device. */
struct NandFlashModel {

    /** Identifier for the device. */
    uint8_t deviceId;
    /** Special options for the NandFlash. */
    uint8_t options;
    /** Size of the data area of a page, in bytes. */
    uint16_t pageSizeInBytes;
    /** Size of the spare area of a page, in bytes. */
    uint16_t spareSizeInBytes;
    /** Size of the device in MB. */
    uint16_t deviceSizeInMegaBytes;
    /** Size of one block in kilobytes. */
    uint16_t blockSizeInKBytes;
    /** Spare area placement scheme */
    const struct NandSpareScheme *scheme;
};

/*------------------------------------------------------------------------------ */
/*         Exported functions                                                    */
/*------------------------------------------------------------------------------ */

extern uint8_t NandFlashModel_Find(
    const struct NandFlashModel *modelList,
    uint32_t size,
    uint32_t id,
    struct NandFlashModel *model);

extern uint8_t NandFlashModel_TranslateAccess(
    const struct NandFlashModel *model,
    uint32_t address,
    uint32_t size,
    uint16_t *block,
    uint16_t *page,
    uint16_t *offset);

extern const struct NandSpareScheme * NandFlashModel_GetScheme(
    const struct NandFlashModel *model);

extern uint8_t NandFlashModel_GetDeviceId(
    const struct NandFlashModel *model);

extern uint16_t NandFlashModel_GetDeviceSizeInBlocks(
    const struct NandFlashModel *model);

extern uint32_t NandFlashModel_GetDeviceSizeInPages(
    const struct NandFlashModel *model);

extern uint64_t NandFlashModel_GetDeviceSizeInBytes(
    const struct NandFlashModel *model);

extern uint32_t NandFlashModel_GetDeviceSizeInMBytes(
    const struct NandFlashModel *model);

extern uint16_t NandFlashModel_GetBlockSizeInPages(
    const struct NandFlashModel *model);

extern uint32_t NandFlashModel_GetBlockSizeInBytes(
    const struct NandFlashModel *model);

extern uint32_t NandFlashModel_GetPageDataSize(
    const struct NandFlashModel *model);

extern uint16_t NandFlashModel_GetPageSpareSize(
    const struct NandFlashModel *model);

extern uint8_t NandFlashModel_GetDataBusWidth(
    const struct NandFlashModel *model);

extern uint8_t NandFlashModel_HasSmallBlocks(
    const struct NandFlashModel *model);

extern uint8_t NandFlashModel_SupportsCopyBack(
    const struct NandFlashModel *model);
/**@}*/
#endif /*#ifndef NANDFLASHMODEL_H */

