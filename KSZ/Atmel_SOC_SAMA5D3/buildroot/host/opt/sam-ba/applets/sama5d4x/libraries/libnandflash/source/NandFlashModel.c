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

/**
 * \brief Get the interger part of input, given a certain result, i.e.  return = result / input.
 * \param result  a certain output we want to calculate.
 * \param input  the input of the division.
 * \return the value of interger part of the result/input.
 */
/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/
/**
 * \brief Looks for a NandFlashModel corresponding to the given ID inside a list of
 * model. If found, the model variable is filled with the correct values.
 * \param modelList  List of NandFlashModel instances.
 * \param size  Number of models in list.
 * \param chipId  Identifier returned by the Nand(id1|(id2<<8)|(id3<<16)|(id4<<24)).
 * \param model  NandFlashModel instance to update with the model parameters.
 * \return 0 if a matching model has been found; otherwise it
 * returns NandCommon_ERROR_UNKNOWNMODEL.
*/
uint8_t NandFlashModel_Find(
    const struct NandFlashModel *modelList,
    uint32_t size,
    uint32_t chipId,
    struct NandFlashModel *model)
{
    uint8_t found = 0, id2, id4;
    uint32_t i;
    #if defined(CHIP_NAND_CTRL)
    uint8_t pageSize = 0;
    #endif
    id2 = (uint8_t)(chipId>>8);
    id4 = (uint8_t)(chipId>>24);

    TRACE_INFO("Nandflash ID is 0x%08X\n\r", (unsigned int)chipId);

    for(i=0; i<size; i++) {
        if(modelList[i].deviceId == id2) {
            found = 1;

            if(model) {

                memcpy(model, &modelList[i], sizeof(struct NandFlashModel));

                if(model->blockSizeInKBytes == 0 || model->pageSizeInBytes == 0) {
                    TRACE_DEBUG("Fetch from ID4(0x%.2x):\r\n", id4);
                    /* Fetch from the extended ID4
                    * ID4 D5  D4 BlockSize || D1  D0  PageSize
                    *     0   0   64K      || 0   0   1K
                    *     0   1   128K     || 0   1   2K
                    *     1   0   256K     || 1   0   4K
                    *     1   1   512K     || 1   1   8k */
                    switch(id4 & 0x03) {
                        case 0x00: model->pageSizeInBytes = 1024; break;
                        case 0x01: model->pageSizeInBytes = 2048; break;
                        case 0x02: model->pageSizeInBytes = 4096; break;
                        case 0x03: model->pageSizeInBytes = 8192; break;
                    }
                    switch(id4 & 0x30) {
                        case 0x00: model->blockSizeInKBytes = 64;  break;
                        case 0x10: model->blockSizeInKBytes = 128; break;
                        case 0x20: model->blockSizeInKBytes = 256; break;
                        case 0x30: model->blockSizeInKBytes = 512; break;
                    }
                }
            }
            TRACE_DEBUG("NAND Model found:\r\n");
            TRACE_DEBUG(" * deviceId = 0x%02X\r\n", model->deviceId);
            TRACE_DEBUG(" * deviceSizeInMegaBytes = %d\r\n", model->deviceSizeInMegaBytes);
            TRACE_DEBUG(" * blockSizeInkBytes = %d\r\n", model->blockSizeInKBytes);
            TRACE_DEBUG(" * pageSizeInBytes = %d\r\n", model->pageSizeInBytes);
            TRACE_DEBUG(" * options = 0x%02X\r\n", model->options);
            break;
        }
    }

    // Check if chip has been detected
    if (found) {

        return 0;
    }
    else {

        return NandCommon_ERROR_UNKNOWNMODEL;
    }
}

/**
 * \brief Translates address/size access of a NandFlashModel to block, page and
 * offset values. The values are stored in the provided variables if their
 * pointer is not 0.
 * \param model  Pointer to a NandFlashModel instance.
 * \param address  Access address.
 * \param size  Access size in bytes.
 * \param block  Stores the first accessed block number.
 * \param page  Stores the first accessed page number inside the first block.
 * \param offset  Stores the byte offset inside the first accessed page.
 * \return 0 if the access is correct; otherwise returns
 * NandCommon_ERROR_OUTOFBOUNDS.
*/
uint8_t NandFlashModel_TranslateAccess(
    const struct NandFlashModel *model,
    uint32_t address,
    uint32_t size,
    uint16_t *block,
    uint16_t *page,
    uint16_t *offset)
{
     /* Check that access is not too big */
    if ((address + size) > NandFlashModel_GetDeviceSizeInBytes(model)) {

        TRACE_DEBUG("NandFlashModel_TranslateAccess: out-of-bounds access.\n\r");
        return NandCommon_ERROR_OUTOFBOUNDS;
    }

    /* Get Nand info */
    uint32_t blockSize = NandFlashModel_GetBlockSizeInBytes(model);
    uint32_t pageSize = NandFlashModel_GetPageDataSize(model);

    /* Translate address */
    uint16_t tmpBlock = address / blockSize;
    address -= tmpBlock * blockSize;
    uint16_t tmpPage = address / pageSize;
    address -= tmpPage * pageSize;
    uint16_t tmpOffset = address;

    // Save results
    if (block) {

        *block = tmpBlock;
    }
    if (page) {

        *page = tmpPage;
    }
    if (offset) {

        *offset = tmpOffset;
    }

    return 0;
}

/**
 * \brief Returns the spare area placement scheme used by a particular nandflash
 * model.
 * \param model  Pointer to a NandFlashModel instance.
 */
const struct NandSpareScheme * NandFlashModel_GetScheme(
    const struct NandFlashModel *model)
{
    return model->scheme;
}

/**
 * \brief Returns the device ID of a particular NandFlash model.
 * \param model  Pointer to a NandFlashModel instance.
 */
uint8_t NandFlashModel_GetDeviceId(
   const struct NandFlashModel *model)
{
    return model->deviceId;
}

/**
 * \brief Returns the number of blocks in the entire device.
 * \param model  Pointer to a NandFlashModel instance.
 */
uint16_t NandFlashModel_GetDeviceSizeInBlocks(
   const struct NandFlashModel *model)
{
    return (1024* model->deviceSizeInMegaBytes) / model->blockSizeInKBytes;
}

/**
 * \brief Returns the number of pages in the entire device.
 * \param model  Pointer to a NandFlashModel instance.
*/
uint32_t NandFlashModel_GetDeviceSizeInPages(
   const struct NandFlashModel *model)
{
    return (uint32_t) NandFlashModel_GetDeviceSizeInBlocks(model) //* 8 // HACK
           * NandFlashModel_GetBlockSizeInPages(model);
}

/**
 * \brief Returns the size of the whole device in bytes (this does not include the
 * size of the spare zones).
 * \param model  Pointer to a NandFlashModel instance.
*/
uint64_t NandFlashModel_GetDeviceSizeInBytes(
   const struct NandFlashModel *model)
{
    return ((uint64_t) model->deviceSizeInMegaBytes) << 20;
}

/**
 * \brief Returns the size of the whole device in Mega bytes (this does not include the
 * size of the spare zones).
 * \param model  Pointer to a NandFlashModel instance.
 */
uint32_t NandFlashModel_GetDeviceSizeInMBytes(
   const struct NandFlashModel *model)
{
    return ((uint32_t) model->deviceSizeInMegaBytes);
}

/**
 * \brief Returns the number of pages in one single block of a device.
 * \param model  Pointer to a NandFlashModel instance.
*/
uint16_t NandFlashModel_GetBlockSizeInPages(
   const struct NandFlashModel *model)
{
    return model->blockSizeInKBytes * 1024 / model->pageSizeInBytes;
}

/**
 * \brief Returns the size in bytes of one single block of a device. This does not
 * take into account the spare zones size.
 * \param model  Pointer to a NandFlashModel instance.
*/
uint32_t NandFlashModel_GetBlockSizeInBytes(
   const struct NandFlashModel *model)
{
    return model->blockSizeInKBytes * 1024;
}

/**
 * \brief Returns the size of the data area of a page in bytes.
 * \param model  Pointer to a NandFlashModel instance.
*/
uint32_t NandFlashModel_GetPageDataSize(
   const struct NandFlashModel *model)
{
    return model->pageSizeInBytes;
}

/**
 * \brief Returns the size of the spare area of a page in bytes.
 * \param model  Pointer to a NandFlashModel instance.
*/
uint16_t NandFlashModel_GetPageSpareSize(
   const struct NandFlashModel *model)
{
    if (model->spareSizeInBytes) {
        return model->spareSizeInBytes;
    }
    else {
        return (model->pageSizeInBytes >> 5); /* Spare size is 16/512 of data size */
    }
}

/**
 * \brief Returns the number of bits used by the data bus of a NandFlash device.
 * \param model  Pointer to a NandFlashModel instance.
*/
uint8_t NandFlashModel_GetDataBusWidth(
   const struct NandFlashModel *model)
{
   
    return (model->options&NandFlashModel_DATABUS16)? 16: 8;
}

/**
 * \brief Returns 1 if the given NandFlash model uses the "small blocks/pages"
 * command set; otherwise returns 0.
 * \param model  Pointer to a NandFlashModel instance.
*/
uint8_t NandFlashModel_HasSmallBlocks(
   const struct NandFlashModel *model)
{
    return (model->pageSizeInBytes <= 512 )? 1: 0;
}

/**
 * \brief Returns 1 if the device supports the copy-back operation. Otherwise returns
 * 0.
 * \param model  Pointer to a NandFlashModel instance.
*/
uint8_t NandFlashModel_SupportsCopyBack(
    const struct NandFlashModel *model)
{
    return ((model->options & NandFlashModel_COPYBACK) != 0);
}
