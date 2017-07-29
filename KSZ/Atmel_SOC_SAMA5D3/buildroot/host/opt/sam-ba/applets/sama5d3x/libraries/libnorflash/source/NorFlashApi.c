/* ----------------------------------------------------------------------------
 *         SAM Software Package License 
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012, Atmel Corporation
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

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include <board.h>
#include <libnorflash.h>
#include <string.h>

/*----------------------------------------------------------------------------
 *        Export functions
 *----------------------------------------------------------------------------*/

/**
 * \brief It will invokes different associate function to implement a RESET command.
 * \param pNorFlash  Pointer to a NorFlash instance.
 * \param address  Address offset.
 */
void NORFLASH_Reset(struct NorFlash *pNorFlash, uint32_t address)
{
    if ((pNorFlash->cmdSet) == CMD_SET_AMD) {
        AMD_Reset(&(pNorFlash->norFlashInfo), address);
    }else {
        INTEL_Reset(&(pNorFlash->norFlashInfo), address);
    }
}

/**
 * \brief It will invokes associate function to implement a read device ID command.
 * ID command.
 * \param pNorFlash  Pointer to a NorFlash instance.
 */
uint32_t NORFLASH_ReadDeviceID(struct NorFlash *pNorFlash)
{
    uint32_t ret;
    if ((pNorFlash->cmdSet) == CMD_SET_AMD) {
        ret =AMD_ReadDeviceID(&(pNorFlash->norFlashInfo));
    } else {
        ret =INTEL_ReadDeviceID(&(pNorFlash->norFlashInfo));
    }
    return ret;
}

/**
 * \brief Erases the specified block of the device. 
 * \param pNorFlash  Pointer to a NorFlash instance.
 * \param address Address offset to be erase.
 * \returns 0 if the operation was successful; otherwise returns an error code.
 */
uint8_t NORFLASH_EraseSector(
    struct NorFlash *pNorFlash, 
    uint32_t address)
{
    uint8_t ret;
    if ((pNorFlash->cmdSet) == CMD_SET_AMD) {
        ret = AMD_EraseSector(&(pNorFlash->norFlashInfo),address);
    }else {
        ret = INTEL_EraseSector(&(pNorFlash->norFlashInfo),address);
    }
    return ret;
}

/**
 * \brief Erases all the block of the device. 
 * \param pNorFlash  Pointer to a NorFlash instance.
 * \returns 0 if the operation was successful; otherwise returns an error code.
 */
uint8_t NORFLASH_EraseChip(
    struct NorFlash *pNorFlash)
{
    uint8_t ret;
    if ((pNorFlash->cmdSet) == CMD_SET_AMD) {
        ret = AMD_EraseChip(&(pNorFlash->norFlashInfo));
    } else {
        ret = INTEL_EraseChip(&(pNorFlash->norFlashInfo));
    }
    return ret;
}

/**
 * \brief Sends data to the pNorFlash chip from the provided buffer.
 * \param pNorFlash  Pointer to a NorFlash instance.
 * \param address Start address offset to be wrote.
 * \param buffer Buffer where the data is stored.
 * \param size Number of bytes that will be written.
 */
uint8_t NORFLASH_WriteData(
    struct NorFlash *pNorFlash,
    uint32_t address,
    uint8_t *buffer,
    uint32_t size)
{
    uint8_t ret;
    if ((pNorFlash->cmdSet) == CMD_SET_AMD) {
        ret = AMD_Write_Data(&(pNorFlash->norFlashInfo),address, buffer, size);
    } else {
        ret = INTEL_Write_Data(&(pNorFlash->norFlashInfo),address, buffer, size);
    }
    return ret;
}

/**
 * \brief Reads data from the NorFlash chip into the provided buffer.
 * \param pNorFlash  Pointer to a NorFlash instance.
 * \param buffer  Buffer where the data will be stored.
 * \param size  Number of bytes that will be read.
 */
uint8_t NORFLASH_ReadData(
    struct NorFlash *pNorFlash,
    uint32_t address,
    uint8_t *buffer,
    uint32_t size)
{
    uint32_t busAddress;
    uint8_t busWidth;
    uint32_t i;
    busWidth = NorFlash_GetDataBusWidth(&(pNorFlash->norFlashInfo));
    
    busAddress = NorFlash_GetAddressInChip(&(pNorFlash->norFlashInfo), address);
    if ((busWidth / 8 ) == FLASH_CHIP_WIDTH_16BITS ){ 
        size = (size + 1) >> 1;
    }
    if ((busWidth/8) == FLASH_CHIP_WIDTH_32BITS ){ 
        size = (size + 3) >> 2;
    }
    for(i = 0; i < size; i++) {
        ReadRawData(busWidth, busAddress, buffer);
        buffer+= (busWidth / 8);
        busAddress+= (busWidth / 8);

    }
    return 0;
}
