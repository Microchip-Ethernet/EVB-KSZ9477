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

#include "at45.h"
#include "at45d.h"
#include <board.h>
#include <utility/assert.h>

//------------------------------------------------------------------------------
//         Local functions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// Wait for transfer to finish calling the SPI driver ISR (interrupts are
/// disabled).
/// \param pAt45  Pointer to an AT45 driver instance.
//------------------------------------------------------------------------------
static void AT45D_Wait(At45 *pAt45)
{
    SANITY_CHECK(pAt45);

    // Wait for transfer to finish
    while (AT45_IsBusy(pAt45)) {
    
        SPID_Handler(pAt45->pSpid);
    }
}


//------------------------------------------------------------------------------
//         Global functions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// Waits for the At45 to be ready to accept new commands.
/// \param pAt45  Pointer to a At45 driver instance.
//------------------------------------------------------------------------------
void AT45D_WaitReady(At45 *pAt45) 
{
    unsigned char ready = 0;

    SANITY_CHECK(pAt45);

    // Poll device until it is ready
    while (!ready) {

        ready = AT45_STATUS_READY(AT45D_GetStatus(pAt45));
    }
}

//------------------------------------------------------------------------------
/// Retrieves and returns the At45 current status, or 0 if an error
/// happened.
/// \param pAt45  Pointer to a At45 driver instance.
//------------------------------------------------------------------------------
unsigned char AT45D_GetStatus(At45 *pAt45)
{
    unsigned char error;
    unsigned char status;

    SANITY_CHECK(pAt45);

    // Issue a status register read command
    error = AT45_SendCommand(pAt45, AT45_STATUS_READ, 1, &status, 1, 0, 0, 0);
    ASSERT(!error, "-F- AT45_GetStatus: Failed to issue command.\n\r");

    // Wait for command to terminate
    while (AT45_IsBusy(pAt45)) {
    
        AT45D_Wait(pAt45);
    }

    return status;
}

//------------------------------------------------------------------------------
/// Reads data from the At45 inside the provided buffer. Since a continuous
/// read command is used, there is no restriction on the buffer size and read
/// address.
/// \param pAt45  Pointer to a At45 driver instance.
/// \param pBuffer  Data buffer.
/// \param size  Number of bytes to read.
/// \param address  Address at which data shall be read.
//------------------------------------------------------------------------------
void AT45D_Read(
    At45 *pAt45,
    unsigned char *pBuffer,
    unsigned int size,
    unsigned int address) 
{
    unsigned char error;

    SANITY_CHECK(pAt45);
    SANITY_CHECK(pBuffer);

    // Issue a continuous read array command
    error = AT45_SendCommand(pAt45, AT45_CONTINUOUS_READ_LEG, 8, pBuffer, size, address, 0, 0);
    ASSERT(!error, "-F- AT45_Read: Failed to issue command\n\r");

    // Wait for the read command to execute
    while (AT45_IsBusy(pAt45)) {
    
        AT45D_Wait(pAt45);
    }
}

//------------------------------------------------------------------------------
/// Writes data on the At45 at the specified address. Only one page of
/// data is written that way; if the address is not at the beginning of the
/// page, the data is written starting from this address and wraps around to
/// the beginning of the page.
/// \param pAt45  Pointer to a At45 driver instance.
/// \param pBuffer  Buffer containing the data to write.
/// \param size  Number of bytes to write.
/// \param address  Destination address on the At45.
//------------------------------------------------------------------------------
void AT45D_Write(
    At45 *pAt45,
    unsigned char *pBuffer,
    unsigned int size,
    unsigned int address) 
{
    unsigned char error;

    SANITY_CHECK(pAt45);
    SANITY_CHECK(pBuffer);
    SANITY_CHECK(size <= pAt45->pDesc->pageSize);

    // Issue a page write through buffer 1 command
    error = AT45_SendCommand(pAt45, AT45_PAGE_WRITE_BUF1, 4, pBuffer, size, address, 0, 0);
    ASSERT(!error, "-F- AT45_Write: Could not issue command.\n\r");

    // Wait until the command is sent
    while (AT45_IsBusy(pAt45)) {
    
        AT45D_Wait(pAt45);
    }

    // Wait until the At45 becomes ready again
    AT45D_WaitReady(pAt45);
}

//------------------------------------------------------------------------------
/// Erases a page of data at the given address in the At45.
/// \param pAt45  Pointer to a At45 driver instance.
/// \param address  Address of page to erase.
//------------------------------------------------------------------------------
void AT45D_Erase(At45 *pAt45, unsigned int address) 
{
    unsigned char error;

    SANITY_CHECK(pAt45);

    // Issue a page erase command.
    error = AT45_SendCommand(pAt45, AT45_PAGE_ERASE, 4, 0, 0, address, 0, 0);
    ASSERT(!error, "-F- AT45_Erase: Could not issue command.\n\r");

    // Wait for end of transfer
    while (AT45_IsBusy(pAt45)) {
    
        AT45D_Wait(pAt45);
    }

    // Poll until the At45 has completed the erase operation
    AT45D_WaitReady(pAt45);
}

//------------------------------------------------------------------------------
/// Configure power-of-2 binary page size in the At45.
/// \param pAt45  Pointer to a At45 driver instance.
//------------------------------------------------------------------------------

void AT45D_BinaryPage(At45 *pAt45) 
{
    unsigned char error;
    unsigned char opcode[3]= {AT45_BINARY_PAGE};
    SANITY_CHECK(pAt45);

    // Issue a binary page command.

    error = AT45_SendCommand(pAt45, AT45_BINARY_PAGE_FIRST_OPCODE, 1, opcode, 3, 0, 0, 0);
   
    ASSERT(!error, "-F- AT45_Erase: Could not issue command.\n\r");

    // Wait for end of transfer
    while (AT45_IsBusy(pAt45)) {
    
        AT45D_Wait(pAt45);
    }

    // Wait until the At45 becomes ready again
    AT45D_WaitReady(pAt45);
}
