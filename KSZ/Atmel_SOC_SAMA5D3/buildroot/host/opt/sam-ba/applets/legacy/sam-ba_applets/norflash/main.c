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
#include "../common/applet.h"
#include <board.h>
#include <board_memories.h>
#include <pio/pio.h>
#include <memories/norflash/NorFlashCFI.h>
#include <memories/norflash/NorFlashApi.h>
#include <utility/math.h>
#include <utility/trace.h>


//------------------------------------------------------------------------------
//         Local definitions
//------------------------------------------------------------------------------
/// Max size of read and write buffer.
#define MAX_BUFFER_SIZE  0x10000


//------------------------------------------------------------------------------
//         Local structures
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// Structure for storing parameters for each command that can be performed by
/// the applet.
//------------------------------------------------------------------------------
struct _Mailbox {

    /// Command send to the monitor to be executed.
    unsigned int command;
    /// Returned status, updated at the end of the monitor execution.
    unsigned int status;

    /// Input Arguments in the argument area
    union {

        /// Input arguments for the Init command.
        struct {

            /// Communication link used.
            unsigned int comType;
            /// Trace level.
            unsigned int traceLevel;

        } inputInit;

        /// Output arguments for the Init command.
        struct {

            /// Memory size.
            unsigned int memorySize;
            /// Buffer address.
            unsigned int bufferAddress;
            /// Buffer size.
            unsigned int bufferSize;
        } outputInit;

        /// Input arguments for the Write command.
        struct {

            /// Buffer address.
            unsigned int bufferAddr;
            /// Buffer size.
            unsigned int bufferSize;
            /// Memory offset.
            unsigned int memoryOffset;

        } inputWrite;

        /// Output arguments for the Write command.
        struct {

            /// Bytes written.
            unsigned int bytesWritten;
        } outputWrite;

        /// Input arguments for the Read command.
        struct {

            /// Buffer address.
            unsigned int bufferAddr;
            /// Buffer size.
            unsigned int bufferSize;
            /// Memory offset.
            unsigned int memoryOffset;

        } inputRead;

        /// Output arguments for the Read command.
        struct {

            /// Bytes read.
            unsigned int bytesRead;

        } outputRead;

        /// Input arguments for the Full Erase command.
        // NONE

        /// Output arguments for the Full Erase command.
        // NONE

        /// Input arguments for the Buffer Erase command.
        struct {

            /// Memory offset to be erase.
            unsigned int memoryOffset;

        } inputBufferErase;

        /// Output arguments for the Buffer Erase command.
        struct {

            /// erased size in bytes
            unsigned int bytesErased;

        } outputBufferErase;

    } argument;
};

//------------------------------------------------------------------------------
//         Global variables
//------------------------------------------------------------------------------

/// End of program space (code + data).
extern unsigned int end;


//------------------------------------------------------------------------------
//         Local variables
//------------------------------------------------------------------------------
/// Communication type
static unsigned int comType;

/// Norflash device structure.
static struct NorFlash norFlash;

/// Last erased sector id, this will avoid to erase if the sector is already erased.
static unsigned short lastErasedSector = 0xFFFF;

/// Indicate the farthest memory offset ever erase, if current write address is less
/// than the lastErasedOffset, the related sector should be erase again before write.
static unsigned int lastErasedOffset = 0;

/// NOR Flash memory size (in bytes)
unsigned int memSize = 0;

#ifdef PINS_NORFLASH
/// Pins used to access to norflash.
static const Pin pPinsNf[] = {PINS_NORFLASH};
#else
/// Pins used to access to nandflash.
static const Pin pPinsNf[] = {{0, 0, 0, 0, 0}};
#endif

//------------------------------------------------------------------------------
//         Global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/// Applet main entry. This function decodes received command and executes it.
/// \param argc  always 1
/// \param argv  Address of the argument area.
//------------------------------------------------------------------------------
int main(int argc, char **argv)
{
    struct _Mailbox *pMailbox = (struct _Mailbox *) argv;
    unsigned int bufferSize, bufferAddr, memoryOffset;
    unsigned int  eraseStartSector, eraseEndSector, bytesToErase;
    unsigned int i;
    const unsigned char busWidth[3] = {FLASH_CHIP_WIDTH_8BITS, FLASH_CHIP_WIDTH_16BITS, FLASH_CHIP_WIDTH_32BITS};

    TRACE_CONFIGURE_ISP(DBGU_STANDARD, 115200, BOARD_MCK);
    PIO_Configure(pPinsNf, PIO_LISTSIZE(pPinsNf));

    // ----------------------------------------------------------
    // INIT:
    // ----------------------------------------------------------
    if (pMailbox->command == APPLET_CMD_INIT) {
        // Save info of communication link
        comType = pMailbox->argument.inputInit.comType;

#if (DYN_TRACES == 1)
        traceLevel = pMailbox->argument.inputInit.traceLevel;
#endif

        TRACE_INFO("-- NorFlash Applet %s --\n\r", SAM_BA_APPLETS_VERSION);
        TRACE_INFO("-- %s\n\r", BOARD_NAME);
        TRACE_INFO("INIT command\n\r");

        norFlash.norFlashInfo.baseAddress = BOARD_NORFLASH_ADDR;
        // Check device CFI and get Vendor setting from it.
        TRACE_INFO("\t Common Flash Interface detecting...\n\r");

        for (i = 0; i < 3; i++) {
            // Configure SMC for Norflash accesses
            TRACE_INFO("\t Try bus width %d bits\n\r", busWidth[i] * 8);
            BOARD_ConfigureNorFlash(busWidth[i] * 8);
            if (!NorFlash_CFI_Detect(&norFlash, busWidth[i])) break;
        }

        if (norFlash.norFlashInfo.cfiCompatible == 0) {
            pMailbox->status = APPLET_DEV_UNKNOWN;
            pMailbox->argument.outputInit.bufferSize = 0;
            pMailbox->argument.outputInit.memorySize = 0;
            TRACE_INFO("Device Unknown\n\r");
            goto exit;
        }
        else {
            TRACE_INFO("manufactureID : 0x%08x, deviceID : 0x%08x\n\r",
                   NORFLASH_ReadManufactoryID(&norFlash),
                   NORFLASH_ReadDeviceID(&norFlash));
            NORFLASH_ReadManufactoryID(&norFlash);
            // Get device parameters
            memSize = NorFlash_GetDeviceSizeInBytes(&(norFlash.norFlashInfo));
            pMailbox->argument.outputInit.bufferAddress = ((unsigned int) &end);
#if defined (at91sam7se)
            pMailbox->argument.outputInit.bufferAddress = 0x21000000;
#endif            
            bufferSize = NorFlash_GetDeviceMaxBlockSize(&(norFlash.norFlashInfo));
            if (bufferSize > MAX_BUFFER_SIZE) bufferSize = MAX_BUFFER_SIZE;
            pMailbox->argument.outputInit.bufferSize = bufferSize;
            pMailbox->argument.outputInit.memorySize = memSize;

            TRACE_INFO("bufferSize : %d memorySize : %d bufferAddr: 0x%x \n\r",
                   pMailbox->argument.outputInit.bufferSize,
                   pMailbox->argument.outputInit.memorySize,
                   (unsigned int) &end);
        }
    }

    // ----------------------------------------------------------
    // WRITE:
    // ----------------------------------------------------------
    else if (pMailbox->command == APPLET_CMD_WRITE) {
        memoryOffset = pMailbox->argument.inputWrite.memoryOffset;
        bufferAddr = pMailbox->argument.inputWrite.bufferAddr;
        bufferSize = pMailbox->argument.inputWrite.bufferSize;

        TRACE_INFO("WRITE at offset: 0x%x buffer at : 0x%x of: 0x%x Bytes\n\r",
               memoryOffset, bufferAddr, bufferSize);

        if (memoryOffset < lastErasedOffset) {
            lastErasedSector = 0xFFFF;
        }
        lastErasedOffset = memoryOffset + bufferSize - 1;
        eraseStartSector = NorFlash_GetDeviceSectorInRegion(&(norFlash.norFlashInfo), memoryOffset);
        eraseEndSector = NorFlash_GetDeviceSectorInRegion(&(norFlash.norFlashInfo), lastErasedOffset);
        do {
            TRACE_INFO("lastErasedSector %d \n\r", lastErasedSector);
            if (eraseStartSector > lastErasedSector || lastErasedSector == 0xFFFF) {
                TRACE_INFO("Sector Erase in sector %d \n\r", eraseStartSector);
                if (NORFLASH_EraseSector(
                    &norFlash,
                    NorFlash_GetDeviceSectorAddress(&(norFlash.norFlashInfo),eraseStartSector))) {

                    TRACE_INFO("Sector Erase failed in sector %d \n\r", eraseStartSector);
                    pMailbox->status = APPLET_FAIL;
                    goto exit;
                }
                lastErasedSector = eraseStartSector;
            }
            eraseStartSector++;
        } while (eraseStartSector <= eraseEndSector);
        // Write the buffer contents.
        if (NORFLASH_WriteData(&norFlash,
                               memoryOffset,
                               (unsigned char *)bufferAddr,
                               bufferSize)) {
            TRACE_INFO("Program failed \n\r");
            pMailbox->status = APPLET_FAIL;
            goto exit;
        }
        pMailbox->argument.outputWrite.bytesWritten = bufferSize;
        pMailbox->status = APPLET_SUCCESS;
    }

    // ----------------------------------------------------------
    // READ:
    // ----------------------------------------------------------
    else if (pMailbox->command == APPLET_CMD_READ) {
        memoryOffset = pMailbox->argument.inputRead.memoryOffset;
        bufferAddr   = pMailbox->argument.inputRead.bufferAddr;
        bufferSize   = pMailbox->argument.inputRead.bufferSize;

        TRACE_INFO("READ at offset: 0x%x buffer at : 0x%x of: 0x%x Bytes\n\r",
               memoryOffset, bufferAddr, bufferSize);
        NORFLASH_ReadData(&norFlash, memoryOffset, (unsigned char *) bufferAddr, bufferSize);
        pMailbox->argument.outputRead.bytesRead = bufferSize;
        pMailbox->status = APPLET_SUCCESS;
    }
    // ----------------------------------------------------------
    // BUFFER ERASE:
    // ----------------------------------------------------------
    else if (pMailbox->command == APPLET_CMD_BUFFER_ERASE) {
        TRACE_INFO("BUFFER ERASE command\n\r");
        memoryOffset = pMailbox->argument.inputBufferErase.memoryOffset;

        bytesToErase = NorFlash_GetDeviceMaxBlockSize(&(norFlash.norFlashInfo)) * 2;
        bytesToErase = ((memoryOffset + bytesToErase) > memSize) ? (memSize - memoryOffset): bytesToErase;
        lastErasedOffset = memoryOffset + bytesToErase;
        eraseStartSector = NorFlash_GetDeviceSectorInRegion(&(norFlash.norFlashInfo), memoryOffset);
        eraseEndSector = NorFlash_GetDeviceSectorInRegion(&(norFlash.norFlashInfo), lastErasedOffset);
        for (i = eraseStartSector; i <= eraseEndSector; i++) {
            if (NORFLASH_EraseSector(
                &norFlash,
                NorFlash_GetDeviceSectorAddress(&(norFlash.norFlashInfo),i))) {
                    TRACE_INFO("Sector Erase failed in sector %d \n\r", i);
                pMailbox->status = APPLET_FAIL;
                goto exit;
            }
            lastErasedSector = i;
        }
        pMailbox->argument.outputBufferErase.bytesErased = bytesToErase;
        TRACE_INFO("Buffer Erase achieved\n\r");
        pMailbox->status = APPLET_SUCCESS;
    }

    // ----------------------------------------------------------
    // FULL ERASE:
    // ----------------------------------------------------------
    else if (pMailbox->command == APPLET_CMD_FULL_ERASE) {
        TRACE_INFO("FULL ERASE command\n\r");
        if (NORFLASH_EraseChip(&norFlash)) {
            TRACE_INFO("Full Erase failed! \n\r");
            pMailbox->status = APPLET_FAIL;
            goto exit;
        }
        TRACE_INFO("Full Erase achieved\n\r");
        pMailbox->status = APPLET_SUCCESS;
    }


exit :
    // Acknowledge the end of command
    TRACE_INFO("\tEnd of applet (command : %x --- status : %x)\n\r", pMailbox->command, pMailbox->status);
    // Notify the host application of the end of the command processing
    pMailbox->command = ~(pMailbox->command);
    // Send ACK character
    if (comType == DBGU_COM_TYPE) {
        DBGU_PutChar(0x6);
    }

    return 0;
}

