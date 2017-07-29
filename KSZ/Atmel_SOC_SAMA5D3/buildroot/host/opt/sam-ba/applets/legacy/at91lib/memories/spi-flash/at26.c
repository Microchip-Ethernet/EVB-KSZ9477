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
#include <board.h>
#include <utility/assert.h>

//------------------------------------------------------------------------------
//         Internal definitions
//------------------------------------------------------------------------------

/// SPI clock frequency used in Hz.
#if defined (BOARD_AT26F004)
// SPI runs at a faster frequency for devices with smaller throughput
#define SPCK            10000000
#else
#define SPCK            1000000
#endif

/// SPI chip select configuration value.
#define CSR             (AT91C_SPI_NCPHA | \
                         SPID_CSR_DLYBCT(BOARD_MCK, 100) | \
                         SPID_CSR_DLYBS(BOARD_MCK, 10) | \
                         SPID_CSR_SCBR(BOARD_MCK, SPCK))

/// Number of recognized dataflash.
#define NUMDATAFLASH    (sizeof(at26Devices) / sizeof(At26Desc))

//------------------------------------------------------------------------------
//         Internal variables
//------------------------------------------------------------------------------

/// Array of recognized serial firmware dataflash chips.
static const At26Desc at26Devices[] = {
    // name,        Jedec ID,       size,  page size, block size, block erase command
    {"AT25DF041A" , 0x0001441F,      512 * 1024, 256,  4 * 1024, AT26_BLOCK_ERASE_4K},
    {"AT25DF161"  , 0x0002461F, 2 * 1024 * 1024, 256,  4 * 1024, AT26_BLOCK_ERASE_4K},
    {"AT26F004"   , 0x0000041F,      512 * 1024, 256,  4 * 1024, AT26_BLOCK_ERASE_4K},
    {"AT26DF081A" , 0x0001451F, 1 * 1024 * 1024, 256,  4 * 1024, AT26_BLOCK_ERASE_4K},
    {"AT26DF161"  , 0x0000461F, 2 * 1024 * 1024, 256,  4 * 1024, AT26_BLOCK_ERASE_4K},
    {"AT26DF161A" , 0x0001461F, 2 * 1024 * 1024, 256,  4 * 1024, AT26_BLOCK_ERASE_4K},
    {"AT26DF321"  , 0x0000471F, 4 * 1024 * 1024, 256,  4 * 1024, AT26_BLOCK_ERASE_4K},
    {"AT25F512B"  , 0x0001651F,       64 * 1024, 256,  4 * 1024, AT26_BLOCK_ERASE_4K},
    {"AT25F512B"  , 0x0000651F,       64 * 1024, 256,  4 * 1024, AT26_BLOCK_ERASE_4K},
    {"AT25DF021"  , 0x0000431F,      256 * 1024, 256,  4 * 1024, AT26_BLOCK_ERASE_4K},
    {"AT26DF641"  , 0x0000481F, 8 * 1024 * 1024, 256,  4 * 1024, AT26_BLOCK_ERASE_4K},
    // Manufacturer: ST
    {"M25P05"     , 0x00102020,       64 * 1024, 256, 32 * 1024, AT26_BLOCK_ERASE_64K},
    {"M25P10"     , 0x00112020,      128 * 1024, 256, 32 * 1024, AT26_BLOCK_ERASE_64K},
    {"M25P20"     , 0x00122020,      256 * 1024, 256, 64 * 1024, AT26_BLOCK_ERASE_64K},
    {"M25P40"     , 0x00132020,      512 * 1024, 256, 64 * 1024, AT26_BLOCK_ERASE_64K},
    {"M25P80"     , 0x00142020, 1 * 1024 * 1024, 256, 64 * 1024, AT26_BLOCK_ERASE_64K},
    {"M25P16"     , 0x00152020, 2 * 1024 * 1024, 256, 64 * 1024, AT26_BLOCK_ERASE_64K},
    {"M25P32"     , 0x00162020, 4 * 1024 * 1024, 256, 64 * 1024, AT26_BLOCK_ERASE_64K},
    {"M25P64"     , 0x00172020, 8 * 1024 * 1024, 256, 64 * 1024, AT26_BLOCK_ERASE_64K},
    // Manufacturer: Windbond
    {"W25X10"     , 0x001130EF,      128 * 1024, 256,  4 * 1024, AT26_BLOCK_ERASE_4K},
    {"W25X20"     , 0x001230EF,      256 * 1024, 256,  4 * 1024, AT26_BLOCK_ERASE_4K},
    {"W25X40"     , 0x001330EF,      512 * 1024, 256,  4 * 1024, AT26_BLOCK_ERASE_4K},
    {"W25X80"     , 0x001430EF, 1 * 1024 * 1024, 256,  4 * 1024, AT26_BLOCK_ERASE_4K},
    // Manufacturer: Macronix
    {"MX25L512"   , 0x001020C2,       64 * 1024, 256,  4 * 1024, AT26_BLOCK_ERASE_4K},
    {"MX25L3205"  , 0x001620C2, 4 * 1024 * 1024, 256, 64 * 1024, AT26_BLOCK_ERASE_64K},
    {"MX25L6405"  , 0x001720C2, 8 * 1024 * 1024, 256,  4 * 1024, AT26_BLOCK_ERASE_4K},
    // Other
    {"SST25VF040" , 0x008D25BF,      512 * 1024, 256,  4 * 1024, AT26_BLOCK_ERASE_4K},
    {"SST25VF080" , 0x008E25BF, 1 * 1024 * 1024, 256,  4 * 1024, AT26_BLOCK_ERASE_4K},
    {"SST25VF032" , 0x004A25BF, 4 * 1024 * 1024, 256,  4 * 1024, AT26_BLOCK_ERASE_4K},
    {"SST25VF064" , 0x004B25BF, 8 * 1024 * 1024, 256,  4 * 1024, AT26_BLOCK_ERASE_4K}
};

//------------------------------------------------------------------------------
//         Exported functions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// Initializes an AT26 driver instance with the given SPI driver and chip
/// select value.
/// \param pAt26  Pointer to an AT26 driver instance.
/// \param pSpid  Pointer to an SPI driver instance.
/// \param cs  Chip select value to communicate with the serial flash.
//------------------------------------------------------------------------------
void AT26_Configure(At26 *pAt26, Spid *pSpid, unsigned char cs)
{
    SpidCmd *pCommand;

    SANITY_CHECK(pAt26);
    SANITY_CHECK(pSpid);
    SANITY_CHECK(cs < 4);

    // Configure the SPI chip select for the serial flash
    SPID_ConfigureCS(pSpid, cs, CSR);

    // Initialize the AT26 fields
    pAt26->pSpid = pSpid;
    pAt26->pDesc = 0;

    // Initialize the command structure
    pCommand = &(pAt26->command);
    pCommand->pCmd = (unsigned char *) pAt26->pCmdBuffer;
    pCommand->callback = 0;
    pCommand->pArgument = 0;
    pCommand->spiCs = cs;
}

//------------------------------------------------------------------------------
/// Returns 1 if the serial flash driver is currently busy executing a command;
/// otherwise returns 0.
/// \param pAt26  Pointer to an At26 driver instance.
//------------------------------------------------------------------------------
unsigned char AT26_IsBusy(At26 *pAt26)
{
    return SPID_IsBusy(pAt26->pSpid);
}

//------------------------------------------------------------------------------
/// Sends a command to the serial flash through the SPI. The command is made up
/// of two parts: the first is used to transmit the command byte and optionally,
/// address and dummy bytes. The second part is the data to send or receive.
/// This function does not block: it returns as soon as the transfer has been
/// started. An optional callback can be invoked to notify the end of transfer.
/// Return 0 if successful; otherwise, returns AT26_ERROR_BUSY if the AT26
/// driver is currently executing a command, or AT26_ERROR_SPI if the command
/// cannot be sent because of a SPI error.
/// \param pAt26  Pointer to an At26 driver instance.
/// \param cmd  Command byte.
/// \param cmdSize  Size of command (command byte + address bytes + dummy bytes).
/// \param pData Data buffer.
/// \param dataSize  Number of bytes to send/receive.
/// \param address  Address to transmit.
/// \param callback  Optional user-provided callback to invoke at end of transfer.
/// \param pArgument  Optional argument to the callback function.
//------------------------------------------------------------------------------
unsigned char AT26_SendCommand(
    At26 *pAt26,
    unsigned char cmd,
    unsigned char cmdSize,
    unsigned char *pData,
    unsigned int dataSize,
    unsigned int address,
    SpidCallback callback,
    void *pArgument)

{
    SpidCmd *pCommand;

    SANITY_CHECK(pAt26);

    // Check if the SPI driver is available
    if (AT26_IsBusy(pAt26)) {

        return AT26_ERROR_BUSY;
    }

    // Store command and address in command buffer
    pAt26->pCmdBuffer[0] = (cmd & 0x000000FF)
                           | ((address & 0x0000FF) << 24)
                           | ((address & 0x00FF00) << 8)
                           | ((address & 0xFF0000) >> 8);

    // Update the SPI transfer descriptor
    pCommand = &(pAt26->command);
     pCommand->cmdSize = cmdSize;
     pCommand->pData = pData;
     pCommand->dataSize = dataSize;
     pCommand->callback = callback;
     pCommand->pArgument = pArgument;

     // Start the SPI transfer
     if (SPID_SendCommand(pAt26->pSpid, pCommand)) {

         return AT26_ERROR_SPI;
     }

     return 0;
}

//------------------------------------------------------------------------------
/// Tries to detect a serial firmware flash device given its JEDEC identifier.
/// The JEDEC id can be retrieved by sending the correct command to the device.
/// Returns the corresponding AT26 descriptor if found; otherwise returns 0.
/// \param pAt26  Pointer to an AT26 driver instance.
/// \param jedecId  JEDEC identifier of device.
//------------------------------------------------------------------------------
const At26Desc * AT26_FindDevice(At26 *pAt26, unsigned int jedecId)
{
    unsigned int i = 0;

    SANITY_CHECK(pAt26);

    // Search if device is recognized
    pAt26->pDesc = 0;
    while ((i < NUMDATAFLASH) && !(pAt26->pDesc)) {

        if ((jedecId & 0xFF00FFFF) == (at26Devices[i].jedecId & 0xFF00FFFF)) {

            pAt26->pDesc = &(at26Devices[i]);
        }

        i++;
    }

    return pAt26->pDesc;
}

