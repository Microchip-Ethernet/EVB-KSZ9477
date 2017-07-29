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

//------------------------------------------------------------------------------
//         Headers
//------------------------------------------------------------------------------

#include "../common/applet.h"
#include <board.h>
#include <board_memories.h>
#include <pio/pio.h>
#include <utility/trace.h>
#include <utility/math.h>
#include <spi-flash/at26.h>
#include <spi-flash/at26d.h>

#include <string.h>

//------------------------------------------------------------------------------
//         Local definitions
//------------------------------------------------------------------------------

/// SPI clock frequency in Hz.
#define SPCK    12000000


#if defined (at91sam7s) || defined (at91sam7x) || defined (at91sam7l) || defined (at91sam7se) || defined (at91sam7a3)
/// Build a tiny applet for devices with small SRAM size
#define TINY_APPPLET
/// Stack size in SRAM
#define STACK_SIZE 0x100

/// Last erased sector id, this will avoid to erase if the block is already erased.
static unsigned short lastErasedBlock = 0xFFFF;

/// Indicate the farthest memory offset ever erase, if current write address is less
/// than the address, the related block should be erase again before write.
static unsigned int writtenAddress = 0;

#else

/// Read write buffer size in serial flash block number
#if defined (at91cap7)
#define BUFFER_NB_BLOCK   1
#else
#define BUFFER_NB_BLOCK   4
#endif

#define TEMP_SIZE    blockSize
#endif


// Max size of data we can tranfsert in one shot
#define PDC_MAX_COUNT 0xFFFF


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
            /// serial flash index.
            unsigned int at26Idx;

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

            /// Memory offset to be erase.
            unsigned int bytesErased;

        } outputBufferErase;
    } argument;
};

//------------------------------------------------------------------------------
/// Holds parameters to configure access to one AT26 serialflash.
//------------------------------------------------------------------------------
struct _At26Select {

    /// Address of the SPI peripheral connected to the serialflash.
    AT91PS_SPI pSpiHw;
    /// SPI peripheral index (e.g. SPI0 -> 0, SPI1 -> 1).
    unsigned char spiIndex;
    /// SPI peripheral identifier.
    unsigned char spiId;
    /// List of pins used by the SPI (MISO, MOSI & SPCK, no NPCS).
    const Pin *pPinsSpi;
    /// Number of pins in list.
    unsigned char numPinsSpi;
    /// Chip select value.
    unsigned char cs;
    /// Chip select pin definition.
    const Pin *pPinCs;
};

//------------------------------------------------------------------------------
//         Global variables
//------------------------------------------------------------------------------

/// End of program space (code + data).
extern int end;
extern int _sstack;

//------------------------------------------------------------------------------
//         Local variables
//------------------------------------------------------------------------------
/// Communication type
static unsigned int comType;

/// SPI driver instance.
static Spid spid;

/// AT26 driver instance.
static At26 at26;

/// Size of one page in the serial flash, in bytes.
static unsigned int pageSize;
/// Size of one block in the serial flash, in bytes.
static unsigned int blockSize;
/// Size of the buffer used for read/write operations in bytes.
static unsigned int bufferSize;


#ifdef BOARD_AT26_A_SPI_BASE

/// SPI pin list instance for serialflash A.
static const Pin pinsSpiA[] = {BOARD_AT26_A_SPI_PINS};
/// SPI chip select pin instance for serialflash A.
static const Pin pinCsA[] = {BOARD_AT26_A_NPCS_PIN};

#endif //#ifdef BOARD_AT26_A_SPI_BASE

#ifdef BOARD_AT26_B_SPI_BASE

/// Serial flash B pin usage
static const Pin pinsSpiB[] = {BOARD_AT26_B_SPI_PINS};
static const Pin pinCsB[] = {BOARD_AT26_B_NPCS_PIN};

#endif //#ifdef BOARD_AT26_B_SPI_BASE

/// Array of pin usage for each serial flash declared in board.h
static const struct _At26Select at26Select[2] = {
#ifdef BOARD_AT26_A_SPI_BASE
    {
        BOARD_AT26_A_SPI_BASE,
        BOARD_AT26_A_SPI,
        BOARD_AT26_A_SPI_ID,
        pinsSpiA,
        PIO_LISTSIZE(pinsSpiA),
        BOARD_AT26_A_NPCS,
        pinCsA
    },
#else
    {0, 0, 0, 0, 0, 0, 0},
#endif
#ifdef BOARD_AT26_B_SPI_BASE
    {
        BOARD_AT26_B_SPI_BASE,
        BOARD_AT26_B_SPI,
        BOARD_AT26_B_SPI_ID,
        pinsSpiB,
        PIO_LISTSIZE(pinsSpiB),
        BOARD_AT26_B_NPCS,
        pinCsB
    }
#else
    {0, 0, 0, 0, 0, 0, 0}
#endif
};

/// Current serial flash index
volatile unsigned char at26Index = 0;


/// Size of the block to be erased in bytes. 
static unsigned int eraseBlockSize;

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
    unsigned int jedecId;
    unsigned int bytesToWrite, bytesToRead, bufferAddr, startMemoryOffset, memoryOffset, packetSize;
    // index on read/write buffer
    unsigned char *pBuffer;
    // Temporary buffer used for non block aligned read/write
    unsigned int tempBufferAddr;
    // Offset in destination buffer during buffer copy
    unsigned int bufferOffset;
    unsigned int i;

    // Configure the DBGU
    TRACE_CONFIGURE_ISP(DBGU_STANDARD, 115200, BOARD_MCK);

    // Configure pins (must be done each time because of some old ROM codes that reset PIO usage)
    if (at26Select[at26Index].pSpiHw != 0) {
        PIO_Configure(at26Select[at26Index].pPinsSpi, at26Select[at26Index].numPinsSpi);
        PIO_Configure(at26Select[at26Index].pPinCs, 1);
    }

    // ----------------------------------------------------------
    // INIT:
    // ----------------------------------------------------------
    if (pMailbox->command == APPLET_CMD_INIT) {
        // Save info of communication link
        comType = pMailbox->argument.inputInit.comType;

        at26Index = pMailbox->argument.inputInit.at26Idx;

#if (DYN_TRACES == 1)
        traceLevel = pMailbox->argument.inputInit.traceLevel;
#endif

        TRACE_INFO("-- SerialFlash AT25/AT26 applet %s --\n\r", SAM_BA_APPLETS_VERSION);
        TRACE_INFO("-- %s\n\r", BOARD_NAME);

        if (at26Select[at26Index].pSpiHw == 0) {
            pMailbox->status = APPLET_NO_DEV;
            pMailbox->argument.outputInit.bufferSize = 0;
            pMailbox->argument.outputInit.memorySize = 0;
            pMailbox->argument.outputInit.bufferAddress = (unsigned int) &end;

            TRACE_INFO("INIT command: No Serialflash %d defined for this board\n\r", \
                   pMailbox->argument.inputInit.at26Idx);

            pMailbox->status = APPLET_NO_DEV;
            goto exit;
        }
        else {
            TRACE_INFO("INIT command: Serialflash %d : SPI %x SPI_NPCS %x (0x%x)\n\r", \
                   pMailbox->argument.inputInit.at26Idx,
                   at26Select[at26Index].spiIndex,
                   at26Select[at26Index].cs,
                   (unsigned int) &(pMailbox->argument.inputInit.at26Idx));

            // Initialize the SPI and serial flash
            SPID_Configure(&spid, at26Select[at26Index].pSpiHw, at26Select[at26Index].spiId);
            PIO_Configure(at26Select[at26Index].pPinsSpi, at26Select[at26Index].numPinsSpi);
            PIO_Configure(at26Select[at26Index].pPinCs, 1);

            AT26_Configure(&at26, &spid, at26Select[at26Index].cs);
            TRACE_INFO("\tSPI and AT25/AT26 drivers initialized\n\r");
            pMailbox->argument.outputInit.bufferAddress = (unsigned int) &end;

            // Read the JEDEC ID of the device to identify it
            jedecId = AT26D_ReadJedecId(&at26);
            if (AT26_FindDevice(&at26, jedecId) == 0) {
                pMailbox->status = APPLET_DEV_UNKNOWN;
                pMailbox->argument.outputInit.bufferSize = 0;
                pMailbox->argument.outputInit.memorySize = 0;
                TRACE_INFO("\tDevice Unknown\n\r");
                goto exit;
            }
            else {
                if (AT26D_Unprotect(&at26)) {
                    TRACE_INFO("Can not unprotect the flash\n\r");
                    pMailbox->status = APPLET_UNPROTECT_FAIL;
                    goto exit;
                }
                // Get device parameters
                pMailbox->status = APPLET_SUCCESS;
                pageSize = AT26_PageSize(&at26);
                blockSize = AT26_BlockSize(&at26);

                if ((AT26_BlockEraseCmd(&at26) ==  AT26_BLOCK_ERASE_64K)
                     || (AT26_ManId(&at26) == ATMEL_SPI_FLASH) ) {
                    eraseBlockSize = 64 * 1024;
                } else {
                    eraseBlockSize = 4 * 1024;
                }

                if (AT26_ManId(&at26) == SST_SPI_FLASH) {
                    /* SST Flash write is slower, we reduce buffer size to avoid USB timeout */
                    bufferSize = 10 * pageSize;
                }
                else{
#ifdef TINY_APPPLET
                    bufferSize = ((unsigned int) &_sstack) - ((unsigned int) &end)  // user area
                         - STACK_SIZE                                               // stack size (if same area of applet code)
                         - pageSize;                                                // tempbuffer size to to make not aligned write operations
#else
                    bufferSize = BUFFER_NB_BLOCK * blockSize;
#endif
                }
                bufferSize -= bufferSize % pageSize; //integer number of pages can be contained in each buffer
                if ( bufferSize < pageSize) {
                    TRACE_INFO("\t No enought memory to load buffer.\n\r");
                    goto exit;
                } 
                pMailbox->argument.outputInit.bufferSize = bufferSize;
                pMailbox->argument.outputInit.memorySize = AT26_Size(&at26);
                TRACE_INFO("\t%s blockSize : 0x%x bufferAddr : 0x%x\n\r",
                       at26.pDesc->name, blockSize, pMailbox->argument.outputInit.bufferAddress);
            }
        }
    }

    // ----------------------------------------------------------
    // WRITE:
    // ----------------------------------------------------------
    else if (pMailbox->command == APPLET_CMD_WRITE) {
        startMemoryOffset = pMailbox->argument.inputWrite.memoryOffset;
        memoryOffset      = startMemoryOffset;
        bufferAddr        = pMailbox->argument.inputWrite.bufferAddr;
        tempBufferAddr    = bufferAddr + bufferSize;
        bytesToWrite      = pMailbox->argument.inputWrite.bufferSize;
        TRACE_INFO("WRITE at offset: 0x%x buffer at : 0x%x of: 0x%x Bytes\n\r",
               memoryOffset, bufferAddr, bytesToWrite);
        // Check word alignment
        if (memoryOffset % 4) {

            pMailbox->status = APPLET_ALIGN_ERROR;
            goto exit;
        }
        pBuffer = (unsigned char *) bufferAddr;

#ifdef TINY_APPPLET

        if ((memoryOffset % pageSize) != 0) {

            // We are not page aligned, retrieve first page content to update it
            if (memoryOffset < writtenAddress) {
                lastErasedBlock = 0xFFFF;
            }
            // Flush temp buffer
            memset((unsigned int *)tempBufferAddr, 0xFF, pageSize);

            bufferOffset = (memoryOffset % pageSize);
            packetSize = pageSize - bufferOffset;
            memoryOffset -= bufferOffset;
            // Read page to be updated
            AT26D_Read(&at26, (unsigned char *) tempBufferAddr, pageSize, memoryOffset);
            // Fill retrieved page with data to be programmed
            memcpy((unsigned char *)(tempBufferAddr + bufferOffset), pBuffer, packetSize);

             if (((memoryOffset / blockSize) > lastErasedBlock) || (lastErasedBlock == 0xFFFF)) {
                 // Erase the block to be updated
                AT26D_EraseBlock(&at26, memoryOffset);
                 lastErasedBlock = (memoryOffset / blockSize);
            }

            // Write the page contents
            AT26D_Write(&at26, (unsigned char *) tempBufferAddr, pageSize, memoryOffset);
            bytesToWrite = (bytesToWrite > packetSize) ? (bytesToWrite - packetSize) : 0;
            pBuffer += packetSize;
            memoryOffset += pageSize;
            writtenAddress = memoryOffset;
        }

        // If it remains more than one page to write
        while (bytesToWrite >= pageSize) {
            if (memoryOffset < writtenAddress) {
                lastErasedBlock = 0xFFFF;
            }
             if (((memoryOffset / blockSize) > lastErasedBlock) || (lastErasedBlock == 0xFFFF)) {
                 // Erase the block to be updated
                AT26D_EraseBlock(&at26, memoryOffset);
                 lastErasedBlock = (memoryOffset / blockSize);
            }
            // Write the page contents
            AT26D_Write(&at26, (unsigned char *) pBuffer, pageSize, memoryOffset);
            pBuffer += pageSize;
            memoryOffset += pageSize;
            bytesToWrite -= pageSize;
            writtenAddress = memoryOffset;
        }

        // Write remaining data
        if (bytesToWrite > 0) {

            // Read previous content of page
            AT26D_Read(&at26, (unsigned char *) tempBufferAddr, pageSize, memoryOffset);
            // Fill retrieved block with data to be programmed
            memcpy((unsigned char *)tempBufferAddr, pBuffer, bytesToWrite);
            if (((memoryOffset / blockSize) > lastErasedBlock) || (lastErasedBlock == 0xFFFF)) {
                 // Erase the block to be updated
                AT26D_EraseBlock(&at26, memoryOffset);
                 lastErasedBlock = (memoryOffset / blockSize);
            }
            // Write the page contents
            AT26D_Write(&at26, (unsigned char *) tempBufferAddr, pageSize, memoryOffset);
            writtenAddress = memoryOffset + bytesToWrite;
            // No more bytes to write
            bytesToWrite = 0;
        }

#else

        if ((memoryOffset % blockSize) != 0) {
            // We are not block aligned, retrieve first block content to update it
            // Flush temp buffer
            memset((unsigned int *)tempBufferAddr, 0xFF, blockSize);

            bufferOffset = (memoryOffset % blockSize);
            packetSize = blockSize - bufferOffset;
            memoryOffset -= bufferOffset;
            // Read block to be updated
            AT26D_Read(&at26, (unsigned char *) tempBufferAddr, blockSize, memoryOffset);
            // Fill retrieved block with data to be programmed
            memcpy((unsigned char *)(tempBufferAddr + bufferOffset), pBuffer, packetSize);

            // Erase the block to be updated
            AT26D_EraseBlock(&at26, memoryOffset);

            // Write the block contents
            AT26D_Write(&at26, (unsigned char *) tempBufferAddr, blockSize, memoryOffset);
            if (bytesToWrite > packetSize) {
                bytesToWrite -= packetSize;
            }
            else {
                bytesToWrite = 0;
            }
            pBuffer += packetSize;
            memoryOffset += blockSize;
        }

        // If it remains more than one block to write
        while (bytesToWrite >= blockSize) {
            // Erase the block to be updated
            AT26D_EraseBlock(&at26, memoryOffset);
            // Write the block contents
            AT26D_Write(&at26, (unsigned char *) pBuffer, blockSize, memoryOffset);
            pBuffer += blockSize;
            memoryOffset += blockSize;
            bytesToWrite -= blockSize;
        }

        // Write remaining data
        if (((startMemoryOffset % blockSize) == 0) && (bytesToWrite > 0)) {
            // Read previous content of block
            AT26D_Read(&at26, (unsigned char *) tempBufferAddr, blockSize, memoryOffset);
            // Fill retrieved block with data to be programmed
            memcpy((unsigned char *)tempBufferAddr, pBuffer, bytesToWrite);

            // Erase the block to be updated
            AT26D_EraseBlock(&at26, memoryOffset);

            // Write the block contents
            AT26D_Write(&at26, (unsigned char *) tempBufferAddr, blockSize, memoryOffset);
            // No more bytes to write
            bytesToWrite = 0;
        }

#endif

        TRACE_INFO("WRITE return byte written : 0x%x Bytes\n\r",
               pMailbox->argument.inputWrite.bufferSize - bytesToWrite);

        pMailbox->argument.outputWrite.bytesWritten = pMailbox->argument.inputWrite.bufferSize - bytesToWrite;
        pMailbox->status = APPLET_SUCCESS;
    }

    // ----------------------------------------------------------
    // READ:
    // ----------------------------------------------------------
    else if (pMailbox->command == APPLET_CMD_READ) {
        memoryOffset = pMailbox->argument.inputRead.memoryOffset;
        bufferAddr   = pMailbox->argument.inputRead.bufferAddr;
        bytesToRead  = pMailbox->argument.inputRead.bufferSize;

        TRACE_INFO("READ at offset: 0x%x buffer at : 0x%x of: 0x%x Bytes\n\r",
               memoryOffset, bufferAddr, bytesToRead);
        // Check word alignment
        if (memoryOffset % 4) {

            pMailbox->status = APPLET_ALIGN_ERROR;
            goto exit;
        }
        pBuffer = (unsigned char *) bufferAddr;

        // Read packet after packets
        while (((unsigned int)pBuffer < (bufferAddr + bufferSize)) && (bytesToRead > 0)) {

            packetSize = min(PDC_MAX_COUNT, bytesToRead);
            AT26D_Read(&at26, pBuffer, packetSize, memoryOffset);
            pBuffer += packetSize;
            bytesToRead -= packetSize;
            memoryOffset += packetSize;
        }

        TRACE_INFO("READ return byte read : 0x%x Bytes\n\r",
               pMailbox->argument.inputRead.bufferSize - bytesToRead);

        pMailbox->argument.outputRead.bytesRead = pMailbox->argument.inputRead.bufferSize - bytesToRead;
        pMailbox->status = APPLET_SUCCESS;
    }

    // ----------------------------------------------------------
    // FULL ERASE:
    // ----------------------------------------------------------
    else if (pMailbox->command == APPLET_CMD_FULL_ERASE) {
        TRACE_INFO("FULL ERASE\n\r");

        // Unprotected the flash
        if (AT26D_Unprotect(&at26)) {

            TRACE_INFO("\tCan not unprotect the flash\n\r");
            pMailbox->status = APPLET_UNPROTECT_FAIL;
            goto exit;
        }

        TRACE_INFO("\tFlash unprotected\n\r");

        // Erase the chip
        TRACE_INFO("\tChip is being erased...\n\r");

        if (AT26D_EraseChip(&at26)) {

            TRACE_INFO("\tErasing error\n\r");
            pMailbox->status = APPLET_ERASE_FAIL;
            goto exit;
        }

        TRACE_INFO("Full Erase achieved\n\r");
        pMailbox->status = APPLET_SUCCESS;
    }
    // ----------------------------------------------------------
    // BUFFER ERASE:
    // ----------------------------------------------------------
    else if (pMailbox->command == APPLET_CMD_BUFFER_ERASE) {
        TRACE_INFO("BUFFER ERASE \n\r");
        memoryOffset = pMailbox->argument.inputBufferErase.memoryOffset;
        if (eraseBlockSize == 64 * 1024)
            if (AT26D_Erase64KBlock(&at26, memoryOffset + eraseBlockSize)) {
                pMailbox->status = APPLET_ERASE_FAIL;
                TRACE_INFO("Block erasing error\n\r");
                goto exit;
            }
        else {
            for (i = 0; i< 32; i++) {
                if (AT26D_EraseBlock(&at26, memoryOffset + i * eraseBlockSize )) {
                    pMailbox->status = APPLET_ERASE_FAIL;
                    TRACE_INFO("Block erasing error\n\r");
                    goto exit;
                }
            }
        }
        if (eraseBlockSize == 64 * 1024)
            pMailbox->argument.outputBufferErase.bytesErased = eraseBlockSize;
        else 
            pMailbox->argument.outputBufferErase.bytesErased = eraseBlockSize * 32;
        pMailbox->status = APPLET_SUCCESS;
    }
exit:
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

