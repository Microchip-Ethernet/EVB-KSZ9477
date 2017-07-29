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

#include "at26.h"
#include "at26d.h"
#include "board.h"
#include <utility/math.h>
#include <utility/assert.h>

/*****/
#include <utility/trace.h>
/*****/

//------------------------------------------------------------------------------
//         Local functions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// Wait for transfer to finish calling the SPI driver ISR. (interrupts are disabled)
/// \param pAt26  Pointer to an AT26 driver instance.
//------------------------------------------------------------------------------
static void AT26D_Wait(At26 *pAt26)
{
    // Wait for transfer to finish
    while (AT26_IsBusy(pAt26))
        SPID_Handler(pAt26->pSpid);
}

//------------------------------------------------------------------------------
/// Reads and returns the status register of the serial flash.
/// \param pAt26  Pointer to an AT26 driver instance.
//------------------------------------------------------------------------------
static unsigned char AT26D_ReadStatus(At26 *pAt26)
{
    unsigned char error, status;

    SANITY_CHECK(pAt26);

    // Issue a status read command
    error = AT26_SendCommand(pAt26, AT26_READ_STATUS, 1, &status, 1, 0, 0, 0);
    ASSERT(!error, "-F- AT26_GetStatus: Failed to issue command.\n\r");

    // Wait for transfer to finish
    AT26D_Wait(pAt26);

    return status;
}

//------------------------------------------------------------------------------
/// Writes the given value in the status register of the serial flash device.
/// \param pAt26  Pointer to an AT26 driver instance.
/// \param status  Status to write.
//------------------------------------------------------------------------------
static void AT26D_WriteStatus(At26 *pAt26, unsigned char status)
{
    unsigned char error;

    SANITY_CHECK(pAt26);

    // Issue a write status command
    error = AT26_SendCommand(pAt26, AT26_WRITE_STATUS, 1, &status, 1, 0, 0, 0);
    ASSERT(!error, "-F- AT26_WriteStatus: Failed to issue command.\n\r");
    // Wait for transfer to finish
    AT26D_Wait(pAt26);
}


//------------------------------------------------------------------------------
//         Global functions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// Waits for the serial flash device to become ready to accept new commands.
/// \param pAt26  Pointer to an AT26 driver instance.
//------------------------------------------------------------------------------
void AT26D_WaitReady(At26 *pAt26)
{
    unsigned char ready = 0;

    SANITY_CHECK(pAt26);

    // Read status register and check busy bit
    while (!ready) {

        ready = ((AT26D_ReadStatus(pAt26) & AT26_STATUS_RDYBSY) == AT26_STATUS_RDYBSY_READY);
    }
}

//------------------------------------------------------------------------------
/// Reads and returns the serial flash device ID.
/// \param pAt26  Pointer to an AT26 driver instance.
//------------------------------------------------------------------------------
unsigned int AT26D_ReadJedecId(At26 *pAt26)
{
    unsigned char error;
    unsigned int id = 0;

    SANITY_CHECK(pAt26);

    // Issue a read ID command
    error = AT26_SendCommand(pAt26, AT26_READ_JEDEC_ID, 1,
                             (unsigned char *) &id, 3, 0, 0, 0);
    ASSERT(!error, "-F- AT26_GetJedecId: Could not issue command.\n\r");

    // Wait for transfer to finish
    AT26D_Wait(pAt26);

    return id;
}

//------------------------------------------------------------------------------
/// Enables critical writes operation on a serial flash device, such as sector
/// protection, status register, etc.
/// \para pAt26  Pointer to an AT26 driver instance.
//------------------------------------------------------------------------------
void AT26D_EnableWrite(At26 *pAt26)
{
    unsigned char error;

    SANITY_CHECK(pAt26);

    // Issue a write enable command
    error = AT26_SendCommand(pAt26, AT26_WRITE_ENABLE, 1, 0, 0, 0, 0, 0);
    ASSERT(!error, "-F- AT26_EnableWrite: Could not issue command.\n\r");

    // Wait for transfer to finish
    AT26D_Wait(pAt26);
}

#if defined(BOARD_AT26F004)

//------------------------------------------------------------------------------
// Reads and returns the status register of the serial flash.
// \param pAt26  Pointer to an AT26 driver instance.
//------------------------------------------------------------------------------
unsigned char AT26F004_Unprotect(At26 *pAt26)
{
    unsigned char error;
    unsigned int  sector, sectorAddress = 0;

    for (sector = 0 ; sector < 11 ; sector ++)
    {
        sectorAddress = 0x0;

        if (sector == 10)
            sectorAddress = 0x7C000;
        else if (sector == 9)
            sectorAddress = 0x7A000;
        else if (sector == 8)
            sectorAddress = 0x78000;
        else if (sector == 7)
            sectorAddress = 0x70000;
        else
            sectorAddress = sectorAddress + (0x10000 * sector);

        // Write Enable
        AT26D_EnableWrite(pAt26);

        error = AT26_SendCommand(pAt26, AT26_UNPROTECT_SECTOR, 4, 0, 0, sectorAddress, 0, 0);
        ASSERT(!error, "-F- AT26_SectorUnprotect: Failed to issue command.\n\r");

        // Wait for transfer to finish
        AT26D_Wait(pAt26);
    }

    return 0;
}
#endif

//------------------------------------------------------------------------------
/// Unprotects the contents of the serial flash device.
/// Returns 0 if the device has been unprotected; otherwise returns
/// SF_PROTECTED.
/// \param pAt26  Pointer to an AT26 driver instance.
//------------------------------------------------------------------------------
unsigned char AT26D_Unprotect(At26 *pAt26)
{
    unsigned char status;

    SANITY_CHECK(pAt26);

    // Get the status register value to check the current protection
    status = AT26D_ReadStatus(pAt26);
    if ((status & AT26_STATUS_SWP) == AT26_STATUS_SWP_PROTNONE) {

        // Protection already disabled
        return 0;
    }

    // Check if sector protection registers are locked
    if ((status & AT26_STATUS_SPRL) == AT26_STATUS_SPRL_LOCKED) {

        // Unprotect sector protection registers by writing the status reg.
        AT26D_EnableWrite(pAt26);
        AT26D_WriteStatus(pAt26, 0);
    }

    // Perform a global unprotect command
    AT26D_EnableWrite(pAt26);

    #if defined(BOARD_AT26F004)
    AT26F004_Unprotect(pAt26);
    #endif

    AT26D_WriteStatus(pAt26, 0);

    // Check the new status
    status = AT26D_ReadStatus(pAt26);
    if ((status & (AT26_STATUS_SPRL | AT26_STATUS_SWP)) != 0) {

        return AT26_ERROR_PROTECTED;
    }
    else {

        return 0;
    }
}

//------------------------------------------------------------------------------
/// Erases all the content of the memory chip.
/// \param pAt26  Pointer to an AT26 driver instance.
//------------------------------------------------------------------------------
unsigned char AT26D_EraseChip(At26 *pAt26)
{
    unsigned char status;
    unsigned char error;

    SANITY_CHECK(pAt26);

    // Check that the flash is unprotected
    status = AT26D_ReadStatus(pAt26);
    if ((status & AT26_STATUS_SWP) != AT26_STATUS_SWP_PROTNONE) {
        return AT26_ERROR_PROTECTED;
    }

    // Enable critical write operation
      AT26D_EnableWrite(pAt26);

    // Erase the chip
    error = AT26_SendCommand(pAt26, AT26_CHIP_ERASE_2, 1, 0, 0, 0, 0, 0);
    ASSERT(!error, "-F- AT26_ChipErase: Could not issue command.\n\r");
    // Wait for transfer to finish
    AT26D_Wait(pAt26);
    // Poll the Serial flash status register until the operation is achieved
    AT26D_WaitReady(pAt26);

    return 0;
}


//------------------------------------------------------------------------------
/// Erases the specified block of the serial firmware dataflash.
/// Returns 0 if successful; otherwise returns AT26_ERROR_PROTECTED if the
/// device is protected or AT26_ERROR_BUSY if it is busy executing a command.
/// \param pAt26  Pointer to an AT26 driver instance.
/// \param address  Address of the block to erase.
//------------------------------------------------------------------------------
unsigned char AT26D_EraseBlock(At26 *pAt26, unsigned int address)
{
    unsigned char status;
    unsigned char error;

    SANITY_CHECK(pAt26);

    // Check that the flash is ready and unprotected
    status = AT26D_ReadStatus(pAt26);
    if ((status & AT26_STATUS_RDYBSY) != AT26_STATUS_RDYBSY_READY) {
        TRACE_ERROR("AT26D_EraseBlock : Flash busy\n\r");
        return AT26_ERROR_BUSY;
    }
    else if ((status & AT26_STATUS_SWP) != AT26_STATUS_SWP_PROTNONE) {
        TRACE_ERROR("AT26D_EraseBlock : Flash protected\n\r");
        return AT26_ERROR_PROTECTED;
    }

    // Enable critical write operation
      AT26D_EnableWrite(pAt26);

    // Start the block erase command
    error = AT26_SendCommand(pAt26, AT26_BlockEraseCmd(pAt26), 4, 0, 0, address, 0, 0);
    ASSERT(!error, "-F- AT26_EraseBlock: Could not issue command.\n\r");
    // Wait for transfer to finish
    AT26D_Wait(pAt26);
    // Poll the Serial flash status register until the operation is achieved
    AT26D_WaitReady(pAt26);

    return 0;
}

//------------------------------------------------------------------------------
/// Erases the specified 64KB block of the serial firmware dataflash.
/// Returns 0 if successful; otherwise returns AT26_ERROR_PROTECTED if the
/// device is protected or AT26_ERROR_BUSY if it is busy executing a command.
/// \param pAt26  Pointer to an AT26 driver instance.
/// \param address  Address of the block to erase.
//------------------------------------------------------------------------------
unsigned char AT26D_Erase64KBlock(At26 *pAt26, unsigned int address)
{
    unsigned char status;
    unsigned char error;

    SANITY_CHECK(pAt26);

    // Check that the flash is ready and unprotected
    status = AT26D_ReadStatus(pAt26);
    if ((status & AT26_STATUS_RDYBSY) != AT26_STATUS_RDYBSY_READY) {
        TRACE_ERROR("AT26D_EraseBlock : Flash busy\n\r");
        return AT26_ERROR_BUSY;
    }
    else if ((status & AT26_STATUS_SWP) != AT26_STATUS_SWP_PROTNONE) {
        TRACE_ERROR("AT26D_EraseBlock : Flash protected\n\r");
        return AT26_ERROR_PROTECTED;
    }

    // Enable critical write operation
      AT26D_EnableWrite(pAt26);

    // Start the block erase command
    error = AT26_SendCommand(pAt26, AT26_BLOCK_ERASE_64K, 4, 0, 0, address, 0, 0);
    ASSERT(!error, "-F- AT26_EraseBlock: Could not issue command.\n\r");
    // Wait for transfer to finish
    AT26D_Wait(pAt26);
    // Poll the Serial flash status register until the operation is achieved
    AT26D_WaitReady(pAt26);

    return 0;
}

//------------------------------------------------------------------------------
/// Writes data at the specified address on the serial firmware dataflash. The
/// page(s) to program must have been erased prior to writing. This function
/// handles page boundary crossing automatically.
/// Returns 0 if successful; otherwise, returns AT26_ERROR_PROGRAM is there has
/// been an error during the data programming.
/// \param pAt26  Pointer to an AT26 driver instance.
/// \param pData  Data buffer.
/// \param size  Number of bytes in buffer.
/// \param address  Write address.
//------------------------------------------------------------------------------
unsigned char AT26D_Write(
    At26 *pAt26,
    unsigned char *pData,
    unsigned int size,
    unsigned int address)
{
    unsigned int pageSize;
    unsigned int writeSize;
    unsigned char error;
    #if !defined(BOARD_AT26F004)
    unsigned char status;
    #endif
    unsigned int i = 0;

    SANITY_CHECK(pAt26);
    SANITY_CHECK(pData);

    // Retrieve device page size
    pageSize = AT26_PageSize(pAt26);

    // Program one page after the other
    while (size > 0) {
        // Compute number of bytes to program in page
        #if defined(BOARD_AT26F004)
        writeSize = 1;
        #else
        writeSize = min(size, pageSize - (address % pageSize));
        #endif

        // Enable critical write operation
        AT26D_EnableWrite(pAt26);
        if (AT26_ManId(pAt26) == SST_SPI_FLASH) {

            error = AT26_SendCommand(pAt26, AT26_SEQUENTIAL_PROGRAM_1, 4,
                               pData, 2, address, 0, 0);
            
            ASSERT(!error, "-F- AT26_WritePage: Failed to issue command.\n\r");
    
            /* Wait for transfer to finish */
            AT26D_Wait(pAt26);
            /* Poll the Serial flash status register until the operation is achieved */
            AT26D_WaitReady(pAt26);

            for (i = 2; i < pageSize; i += 2) {
                error = AT26_SendCommand(pAt26, AT26_SEQUENTIAL_PROGRAM_1, 1,
                                   pData + i, 2, 0, 0, 0);

                ASSERT(!error, "-F- AT26_WritePage: Failed to issue command.\n\r");
        
                /* Wait for transfer to finish */
                AT26D_Wait(pAt26);
                /* Poll the Serial flash status register until the operation is achieved */
                AT26D_WaitReady(pAt26);
            }
        
        }
     else
     {
        // Program page
        error = AT26_SendCommand(pAt26, AT26_BYTE_PAGE_PROGRAM, 4,
                           pData, writeSize, address, 0, 0);
        ASSERT(!error, "-F- AT26_WritePage: Failed to issue command.\n\r");
        // Wait for transfer to finish
        AT26D_Wait(pAt26);
        // Poll the Serial flash status register until the operation is achieved
        AT26D_WaitReady(pAt26);
     }
 
        #if !defined(AT26F004)
        // Make sure that write was without error
        status = AT26D_ReadStatus(pAt26);
        if ((status & AT26_STATUS_EPE) == AT26_STATUS_EPE_ERROR) {

            return AT26_ERROR_PROGRAM;
        }
        #endif

        pData += writeSize;
        size -= writeSize;
        address += writeSize;
    }

    return 0;
}

//------------------------------------------------------------------------------
/// Reads data from the specified address on the serial flash.
/// \param pAt26  Pointer to an AT26 driver instance.
/// \param pData  Data buffer.
/// \param size  Number of bytes to read.
/// \param address  Read address.
//------------------------------------------------------------------------------
unsigned char AT26D_Read(
    At26 *pAt26,
    unsigned char *pData,
    unsigned int size,
    unsigned int address)
{
    unsigned char error;
    unsigned int read_len;

    while (size > 0) {
        read_len = min(size, 0xffff);
        // Start a read operation
        error = AT26_SendCommand(pAt26, AT26_READ_ARRAY_LF, 4, pData, read_len, address, 0, 0);
        ASSERT(!error, "-F- AT26_Read: Could not issue command.\n\r");
        if (error) {
            break;
        }
        // Wait for transfer to finish
        AT26D_Wait(pAt26);
        size -= read_len;
        address += read_len;
        pData += read_len;
    }

    return error;
}
