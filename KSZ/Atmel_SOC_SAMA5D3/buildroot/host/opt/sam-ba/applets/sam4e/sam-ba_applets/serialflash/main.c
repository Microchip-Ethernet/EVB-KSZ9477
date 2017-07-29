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
#include <string.h>

/*----------------------------------------------------------------------------
 *        Internal definitions
 *----------------------------------------------------------------------------*/

/** Stack size in SRAM */
#define STACK_SIZE 0x100

/** Communication type with SAM-BA GUI.*/
static uint32_t comType;

/** Last erased sector id, this will avoid to erase if the block is already erased. */
static uint16_t lastErasedBlock = 0xFFFF;

/** Indicate the farthest memory offset ever erase, if current write address is less
 than the address, the related block should be erase again before write. */
static uint32_t writtenAddress = 0;



/** Max size of data we can tranfsert in one shot */
#define PDC_MAX_COUNT 0xFFFF

/** Chip select value used to select the AT25 chip. */
#define SPI_CS          3
/** SPI peripheral pins to configure to access the serial flash. */
#define SPI_PINS        PINS_SPI, PIN_SPI_NPCS3_AT25

/*----------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/
/** Structure for storing parameters for each command that can be performed by
the applet. */
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
            /**Trace level.*/
            uint32_t traceLevel;
            /** Serial flash index.*/
            uint32_t at25Idx;

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

            /** Buffer address. */
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

            /** Memory offset to be erase.*/
            uint32_t bytesErased;

        } outputBufferErase;
    } argument;
};

/*----------------------------------------------------------------------------
 *        Global variables
 *----------------------------------------------------------------------------*/

/** End of program space (code + data). */
extern int end;
extern int _sstack;

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

/** SPI driver instance. */
static Spid spid;

/** Serial flash driver instance. */
static At25 at25;

/** Pins to configure for the application. */
static Pin pins[] = {SPI_PINS};

/** Size of one page in the serial flash, in bytes.  */
static uint32_t pageSize;

/** Size of one block in the serial flash, in bytes.  */
static uint32_t blockSize;

/**Size of the buffer used for read/write operations in bytes. */
static uint32_t bufferSize;

/**Size of the block to be erased in bytes. */
static uint32_t eraseBlockSize;
/*----------------------------------------------------------------------------
 *         Global functions
 *----------------------------------------------------------------------------*/


/**
 * \brie Applet main entry. This function decodes received command and executes it.
 * \param argc  always 1
 * \param argv  Address of the argument area.
*/

int main(int argc, char **argv)
{
    struct _Mailbox *pMailbox = (struct _Mailbox *) argv;
    uint32_t jedecId;
    uint32_t bytesToWrite, bytesToRead, bufferAddr, startMemoryOffset, memoryOffset, packetSize;
    /* index on read/write buffer */
    uint8_t *pBuffer;
    /* Temporary buffer used for non block aligned read/write */
    uint32_t tempBufferAddr;
    /* Offset in destination buffer during buffer copy */
    uint32_t bufferOffset;
    uint32_t i;

     /* Configure the DBGU */
    TRACE_CONFIGURE_ISP(DBGU_STANDARD, 115200, BOARD_MCK);

     /* INIT */  
     
    if (pMailbox->command == APPLET_CMD_INIT) {
        // Save info of communication link
        comType = pMailbox->argument.inputInit.comType;

        TRACE_INFO("-- SerialFlash AT25/AT25 applet %s --\n\r", SAM_BA_APPLETS_VERSION);
        TRACE_INFO("-- %s\n\r", BOARD_NAME);

        /* Configure pins */
        PIO_Configure(pins, PIO_LISTSIZE(pins));

        /* Initialize the SPI and serial flash */
        PIO_Configure(pins, PIO_LISTSIZE(pins));
        SPID_Configure(&spid, SPI, ID_SPI);
        AT25_Configure(&at25, &spid, SPI_CS);

        TRACE_INFO("\tSPI and AT25/AT25 drivers initialized\n\r");
        pMailbox->argument.outputInit.bufferAddress = (unsigned int) &end;

        /* Read the JEDEC ID of the device to identify it */
        jedecId = AT25D_ReadJedecId(&at25);
        if (AT25_FindDevice(&at25, jedecId) == 0) {
            pMailbox->status = APPLET_DEV_UNKNOWN;
            pMailbox->argument.outputInit.bufferSize = 0;
            pMailbox->argument.outputInit.memorySize = 0;
            TRACE_INFO("\tDevice Unknown\n\r");
            goto exit;
        }
        else {
            if (AT25D_Unprotect(&at25)) {
                TRACE_INFO("Can not unprotect the flash\n\r");
                pMailbox->status = APPLET_UNPROTECT_FAIL;
                goto exit;
            }
            /* Get device parameters */
            pMailbox->status = APPLET_SUCCESS;
            pageSize = AT25_PageSize(&at25);
            blockSize = AT25_BlockSize(&at25);
          
            if ((AT25_BlockEraseCmd(&at25) ==  AT25_BLOCK_ERASE_64K)
                 || (AT25_ManId(&at25) == ATMEL_SPI_FLASH) ) {
                eraseBlockSize = 64 * 1024;
            } else {
               eraseBlockSize = 4 * 1024;
            }
            /* Program page */
             if (AT25_ManId(&at25) == SST_SPI_FLASH) {
                /* SST Flash write is slower, we reduce buffer size to avoid USB timeout */
                bufferSize = 10 * pageSize;
            } else {             
            bufferSize = IRAM_SIZE                        // sram size
                 - ( ((uint32_t) &end) - IRAM_ADDR )      // program size (romcode, code+data)
                 - STACK_SIZE - pageSize;                 // stack size at the end
            } 
            /* integer number of pages can be contained in each buffer */
            bufferSize -= bufferSize % pageSize; 
            if ( bufferSize < pageSize) {
                TRACE_INFO("\t No enought memory to load buffer.\n\r");
                goto exit;
            } 
            bufferSize = (bufferSize > eraseBlockSize) ? eraseBlockSize: bufferSize;
            pMailbox->argument.outputInit.bufferSize = bufferSize;
            pMailbox->argument.outputInit.memorySize = AT25_Size(&at25);
            TRACE_INFO("\t%s blockSize : 0x%x bufferAddr : 0x%x\n\r",
                   at25.pDesc->name, (unsigned int)blockSize, (unsigned int)(pMailbox->argument.outputInit.bufferAddress));
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
               (unsigned int)memoryOffset, (unsigned int)bufferAddr, (unsigned int)bytesToWrite);
        /* Check word alignment */
        if (memoryOffset % 4) {

            pMailbox->status = APPLET_ALIGN_ERROR;
            goto exit;
        }

        if (AT25D_Unprotect(&at25)) {

            TRACE_INFO("\tCan not unprotect the flash\n\r");
            pMailbox->status = APPLET_UNPROTECT_FAIL;
            goto exit;
        }
        pBuffer = (uint8_t *) bufferAddr;

        if ((memoryOffset % pageSize) != 0) {

            /*  We are not page aligned, retrieve first page content to update it*/
            if (memoryOffset < writtenAddress) {
                lastErasedBlock = 0xFFFF;
            }
            /*  Flush temp buffer */
            memset((uint32_t *)tempBufferAddr, 0xFF, pageSize);

            bufferOffset = (memoryOffset % pageSize);
            packetSize = pageSize - bufferOffset;
            memoryOffset -= bufferOffset;
            /*  Read page to be updated*/
            AT25D_Read(&at25, (uint8_t *) tempBufferAddr, pageSize, memoryOffset);
            /* Fill retrieved page with data to be programmed */
            memcpy((uint8_t *)(tempBufferAddr + bufferOffset), pBuffer, packetSize);

             if (((memoryOffset / blockSize) > lastErasedBlock) || (lastErasedBlock == 0xFFFF)) {
                /* Erase the block to be updated */
                AT25D_EraseBlock(&at25, memoryOffset);
                lastErasedBlock = (memoryOffset / blockSize);
            }

            /*  Write the page contents */
            AT25D_Write(&at25, (uint8_t *) tempBufferAddr, pageSize, memoryOffset);
            bytesToWrite = (bytesToWrite > packetSize) ? (bytesToWrite - packetSize) : 0;
            pBuffer += packetSize;
            memoryOffset += pageSize;
            writtenAddress = memoryOffset;
        }

        /*  If it remains more than one page to write */
        while (bytesToWrite >= pageSize) {
            if (memoryOffset < writtenAddress) {
                lastErasedBlock = 0xFFFF;
            }
             if (((memoryOffset / blockSize) > lastErasedBlock) || (lastErasedBlock == 0xFFFF)) {
                 /* Erase the block to be updated */
                AT25D_EraseBlock(&at25, memoryOffset);
                 lastErasedBlock = (memoryOffset / blockSize);
            }
            /*  Write the page contents */
            AT25D_Write(&at25, (uint8_t *) pBuffer, pageSize, memoryOffset);
            pBuffer += pageSize;
            memoryOffset += pageSize;
            bytesToWrite -= pageSize;
            writtenAddress = memoryOffset;
        }

        /*  Write remaining data */
        if (bytesToWrite > 0) {
            /*  Flush temp buffer */
            memset((uint32_t *)tempBufferAddr, 0xFF, pageSize);
            /*  Fill retrieved block with data to be programmed */
            memcpy((uint8_t *)tempBufferAddr, pBuffer, bytesToWrite);
            if (((memoryOffset / blockSize) > lastErasedBlock) || (lastErasedBlock == 0xFFFF)) {
                 /*  Erase the block to be updated */
                AT25D_EraseBlock(&at25, memoryOffset);
                 lastErasedBlock = (memoryOffset / blockSize);
            }
            /*  Write the page contents */;
            AT25D_Write(&at25, (uint8_t *) tempBufferAddr, pageSize, memoryOffset);
            writtenAddress = memoryOffset + bytesToWrite;
            /*  No more bytes to write */
            bytesToWrite = 0;
        }

        TRACE_INFO("WRITE return byte written : 0x%x Bytes\n\r",
               (unsigned int)(pMailbox->argument.inputWrite.bufferSize - bytesToWrite));

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
              (unsigned int)memoryOffset, (unsigned int)bufferAddr,(unsigned int)bytesToRead);
        /*  Check word alignment */
        if (memoryOffset % 4) {

            pMailbox->status = APPLET_ALIGN_ERROR;
            goto exit;
        }
        pBuffer = (uint8_t *) bufferAddr;

        /* Read packet after packets */
        while (((uint32_t)pBuffer < (bufferAddr + bufferSize)) && (bytesToRead > 0)) {

            packetSize = min(PDC_MAX_COUNT, bytesToRead);
            AT25D_Read(&at25, pBuffer, packetSize, memoryOffset);
            pBuffer += packetSize;
            bytesToRead -= packetSize;
            memoryOffset += packetSize;
        }

        TRACE_INFO("READ return byte read : 0x%x Bytes\n\r",
               (unsigned int)(pMailbox->argument.inputRead.bufferSize - bytesToRead));

        pMailbox->argument.outputRead.bytesRead = pMailbox->argument.inputRead.bufferSize - bytesToRead;
        pMailbox->status = APPLET_SUCCESS;
    }

    // ----------------------------------------------------------
    // FULL ERASE:
    // ----------------------------------------------------------
    else if (pMailbox->command == APPLET_CMD_FULL_ERASE) {
        TRACE_INFO("FULL ERASE\n\r");
        if (AT25D_EraseChip(&at25)) {
            TRACE_INFO("Erasing error\n\r");
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
        if (eraseBlockSize == 64 * 1024) {
            if (AT25D_Erase64KBlock(&at25, memoryOffset + eraseBlockSize)) {
                pMailbox->status = APPLET_ERASE_FAIL;
                TRACE_INFO("Block erasing error\n\r");
                goto exit;
            }
        } else {
            for (i = 0; i< 32; i++) {
                if (AT25D_EraseBlock(&at25, memoryOffset + i * eraseBlockSize )) {
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
    /* Acknowledge the end of command */
    TRACE_INFO("\tEnd of applet (command : %x --- status : %x)\n\r", (unsigned int)pMailbox->command, (unsigned int)pMailbox->status);

    /*  Notify the host application of the end of the command processing */
    pMailbox->command = ~(pMailbox->command);
    if (comType == DBGU_COM_TYPE) {
        UART_PutChar(0x6);
    }

    return 0;
}

