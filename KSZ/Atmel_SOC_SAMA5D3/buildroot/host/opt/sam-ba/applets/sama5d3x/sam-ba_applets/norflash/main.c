/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
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
#include "../common/applet.h"
#include <board.h>
#include <libnorflash.h>
#include <string.h>

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/
 
/** Max size of read and write buffer. */
#define MAX_BUFFER_SIZE  0x20000

/*----------------------------------------------------------------------------
 *        Local structures
 *----------------------------------------------------------------------------*/

/** \brief Structure for storing parameters for each command that can be
 * performed by the applet.*/
 
struct _Mailbox {

    /** Command send to the monitor to be executed. */
    uint32_t command;
    /** Returned status, updated at the end of the monitor execution.*/
    uint32_t status;

    /** Input Arguments in the argument area*/
    union {

        /** Input arguments for the Init command.*/
        struct {

            /** Communication link used.*/
            uint32_t comType;
            /** Trace level. */
            uint32_t traceLevel;

        } inputInit;

        /** Output arguments for the Init command.*/
        struct {

            /** Memory size.*/
            uint32_t memorySize;
            /** Buffer address.*/
            uint32_t bufferAddress;
            /** Buffer size.*/
            uint32_t bufferSize;
        } outputInit;

        /** Input arguments for the Write command.*/
        struct {

            /** Buffer address.*/
            uint32_t bufferAddr;
            /** Buffer size.*/
            uint32_t bufferSize;
            /** Memory offset.*/
            uint32_t memoryOffset;

        } inputWrite;

        /** Output arguments for the Write command.*/
        struct {

            /** Bytes written.*/
            uint32_t bytesWritten;
        } outputWrite;

        /** Input arguments for the Read command.*/
        struct {

            /** Buffer address.*/
            uint32_t bufferAddr;
            /** Buffer size.*/
            uint32_t bufferSize;
            /** Memory offset.*/
            uint32_t memoryOffset;

        } inputRead;

        /** Output arguments for the Read command.*/
        struct {

            /** Bytes read.*/
            uint32_t bytesRead;

        } outputRead;

        /** Input arguments for the Full Erase command.*/
        // NONE

        /** Output arguments for the Full Erase command.*/
        // NONE

        /** Input arguments for the Buffer Erase command.*/
        struct {

            /** Memory offset to be erase.*/
            uint32_t memoryOffset;

        } inputBufferErase;

        /** Output arguments for the Buffer Erase command.*/
        struct {

            /** erased size in bytes*/
            uint32_t bytesErased;

        } outputBufferErase;

    } argument;
};

/*----------------------------------------------------------------------------
 *         Global variables
 *----------------------------------------------------------------------------*/
/** End of program space (code + data). */

extern uint32_t _end;

/*----------------------------------------------------------------------------
 *         Local variables
 *----------------------------------------------------------------------------*/
/** Communication type with SAM-BA GUI.*/
static uint32_t comType;

/** Norflash device structure.*/
static struct NorFlash norFlash;

/** Last erased sector id, this will avoid to erase if the sector is already erased.*/
static uint16_t lastErasedSector = 0xFFFF;

/** Indicate the farthest memory offset ever erase, if current write address is less
    than the lastErasedOffset, the related sector should be erase again before write. */
static uint32_t lastErasedOffset = 0;

/** NOR Flash memory size (in bytes)*/
static uint32_t memSize = 0;

#ifdef PINS_NORFLASH
/** Pins used to access to norflash.*/
static const Pin pPinsNf[] = {PINS_NORFLASH};
#else
/** Pins used to access to nandflash.*/
static const Pin pPinsNf[] = {{0, 0, 0, 0, 0}};
#endif


/*----------------------------------------------------------------------------
 *         local functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Check is the pmecc parameter header is valid 
  \return 1 if the pmecc parameter header is valid; otherwise returns 0
 */
int main(int argc, char **argv)
{
    struct _Mailbox *pMailbox = (struct _Mailbox *) argv;
    uint32_t bufferSize, bufferAddr, memoryOffset;
    uint32_t  eraseStartSector, eraseEndSector, bytesToErase;
    uint32_t i;
    const uint8_t busWidth[3] = {FLASH_CHIP_WIDTH_8BITS, FLASH_CHIP_WIDTH_16BITS, FLASH_CHIP_WIDTH_32BITS};
   
    // ----------------------------------------------------------
    // INIT:
    // ----------------------------------------------------------
    if (pMailbox->command == APPLET_CMD_INIT) {
        /* Save communication link type */
        comType = pMailbox->argument.inputInit.comType;

#if (DYN_TRACES == 1)
        dwTraceLevel = pMailbox->argument.inputInit.traceLevel;
#endif

        TRACE_INFO("-- NorFlash Applet %s --\n\r", SAM_BA_APPLETS_VERSION);
        TRACE_INFO("-- %s\n\r", BOARD_NAME);
        TRACE_INFO("INIT command\n\r");
        
        PIO_Configure(pPinsNf, PIO_LISTSIZE(pPinsNf));
        norFlash.norFlashInfo.baseAddress = BOARD_NORFLASH_ADDR;
        /* Check device CFI and get Vendor setting from it. */
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
            TRACE_INFO("manufacture-deviceID : 0x%08x\n\r", (unsigned int) (NORFLASH_ReadDeviceID(&norFlash)));
            /* Get device parameters */
            memSize = NorFlash_GetDeviceSizeInBytes(&(norFlash.norFlashInfo));
            pMailbox->argument.outputInit.bufferAddress = ((uint32_t) &_end);
            bufferSize = NorFlash_GetDeviceMaxBlockSize(&(norFlash.norFlashInfo));
            if (bufferSize > MAX_BUFFER_SIZE) bufferSize = MAX_BUFFER_SIZE;
            pMailbox->argument.outputInit.bufferSize = bufferSize;
            pMailbox->argument.outputInit.memorySize = memSize;

            TRACE_INFO("bufferSize : %d memorySize : %d bufferAddr: 0x%x \n\r",
                   (unsigned int)(pMailbox->argument.outputInit.bufferSize),
                   (unsigned int)(pMailbox->argument.outputInit.memorySize),
                   (unsigned int)(&_end));
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
               (unsigned int)memoryOffset, (unsigned int)bufferAddr, (unsigned int)bufferSize);

        if (memoryOffset < lastErasedOffset) {
            lastErasedSector = 0xFFFF;
        }
        lastErasedOffset = memoryOffset + bufferSize - 1;
        eraseStartSector = NorFlash_GetDeviceSectorInRegion(&(norFlash.norFlashInfo), memoryOffset);
        eraseEndSector = NorFlash_GetDeviceSectorInRegion(&(norFlash.norFlashInfo), lastErasedOffset);
        do {
            TRACE_INFO("lastErasedSector %d \n\r", (unsigned int)lastErasedSector);
            if (eraseStartSector > lastErasedSector || lastErasedSector == 0xFFFF) {
                TRACE_INFO("Sector Erase in sector %d \n\r", (unsigned int)eraseStartSector);
                if (NORFLASH_EraseSector(
                    &norFlash,
                    NorFlash_GetDeviceSectorAddress(&(norFlash.norFlashInfo),eraseStartSector))) {

                    TRACE_INFO("Sector Erase failed in sector %d \n\r", (unsigned int)eraseStartSector);
                    pMailbox->status = APPLET_FAIL;
                    goto exit;
                }
                lastErasedSector = eraseStartSector;
            }
            eraseStartSector++;
        } while (eraseStartSector <= eraseEndSector);
        /* Write the buffer contents. */
        if (NORFLASH_WriteData(&norFlash,
                               memoryOffset,
                               (uint8_t *)bufferAddr,
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
               (unsigned int)memoryOffset, (unsigned int)bufferAddr, (unsigned int)bufferSize);
        NORFLASH_ReadData(&norFlash, memoryOffset, (uint8_t *) bufferAddr, bufferSize);
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
                    TRACE_INFO("Sector Erase failed in sector %d \n\r", (unsigned int)i);
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
    /* Acknowledge the end of command */
    TRACE_INFO("\tEnd of applet (command : %x --- status : %x)\n\r", (unsigned int)pMailbox->command, (unsigned int)pMailbox->status);
    /* Notify the host application of the end of the command processing*/
    pMailbox->command = ~(pMailbox->command);
    /* Send ACK character */
    if (comType == DBGU_COM_TYPE) {
         /* Wait for the transmitter to be ready */
        while ( (DBGU->DBGU_SR & DBGU_SR_TXEMPTY) == 0 ) ;
        /* Send character */
         DBGU->DBGU_THR= 0x06 ;
    }
    return 0;
}

