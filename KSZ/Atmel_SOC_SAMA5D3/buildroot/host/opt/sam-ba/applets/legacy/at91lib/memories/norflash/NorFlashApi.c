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

//------------------------------------------------------------------------------
//         Headers
//------------------------------------------------------------------------------
#include "NorFlashApi.h"
#include "NorFlashCommon.h"
#include <utility/math.h>
#include <utility/trace.h>
#include <string.h>

//------------------------------------------------------------------------------
//         Exported functions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// It will invokes different associate function to implement a RESET command.
/// \param pNorFlash  Pointer to a NorFlash instance.
/// \param address  Address offset.
//------------------------------------------------------------------------------
void NORFLASH_Reset(struct NorFlash *pNorFlash, unsigned int address)
{
    ((pNorFlash->pOperations)->_fReset)(&(pNorFlash->norFlashInfo), address);
}

//------------------------------------------------------------------------------
/// It will invokes associate function to implement a read manufactory ID command.
/// \param pNorFlash  Pointer to a NorFlash instance.
//------------------------------------------------------------------------------
unsigned int NORFLASH_ReadManufactoryID(struct NorFlash *pNorFlash)
{ 
    return ((pNorFlash->pOperations)->_fReadManufactoryID)(&(pNorFlash->norFlashInfo));
}

//------------------------------------------------------------------------------
/// It will invokes associate function to implement a read device ID command.
/// ID command.
/// \param pNorFlash  Pointer to a NorFlash instance.
//------------------------------------------------------------------------------
unsigned int NORFLASH_ReadDeviceID(struct NorFlash *pNorFlash)
{
    return ((pNorFlash->pOperations)->_fReadDeviceID)(&(pNorFlash->norFlashInfo));
}

//------------------------------------------------------------------------------
/// Erases the specified block of the device. Returns 0 if the operation was
/// successful; otherwise returns an error code.
/// \param pNorFlash  Pointer to a NorFlash instance.
/// \param address Address offset to be erase.
//------------------------------------------------------------------------------
unsigned char NORFLASH_EraseSector(
    struct NorFlash *pNorFlash, 
    unsigned int address)
{
    return ((pNorFlash->pOperations)->_fEraseSector)(&(pNorFlash->norFlashInfo), address);
}

//------------------------------------------------------------------------------
/// Erases all the block of the device. Returns 0 if the operation was successful;
/// otherwise returns an error code.
/// \param pNorFlash  Pointer to a NorFlash instance.
//------------------------------------------------------------------------------
unsigned char NORFLASH_EraseChip(
    struct NorFlash *pNorFlash)
{
    return ((pNorFlash->pOperations)->_fEraseChip)(&(pNorFlash->norFlashInfo));
}

//------------------------------------------------------------------------------
/// Sends data to the pNorFlash chip from the provided buffer.
/// \param pNorFlash  Pointer to a NorFlash instance.
/// \param address Start address offset to be wrote.
/// \param buffer Buffer where the data is stored.
/// \param size Number of bytes that will be written.
//------------------------------------------------------------------------------
unsigned char NORFLASH_WriteData(
    struct NorFlash *pNorFlash,
    unsigned int address,
    unsigned char *buffer,
    unsigned int size)
{
    return ((pNorFlash->pOperations)->_fWriteData)(&(pNorFlash->norFlashInfo), address, buffer, size);
}

//------------------------------------------------------------------------------
/// Reads data from the NandFlash chip into the provided buffer.
/// \param pNorFlash  Pointer to a NorFlash instance.
/// \param buffer  Buffer where the data will be stored.
/// \param size  Number of bytes that will be read.
//------------------------------------------------------------------------------
unsigned char NORFLASH_ReadData(
    struct NorFlash *pNorFlash,
    unsigned int  address,
    unsigned char *buffer,
    unsigned int size)
{
    unsigned int busAddress;
    unsigned char busWidth;
    unsigned int i;
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
