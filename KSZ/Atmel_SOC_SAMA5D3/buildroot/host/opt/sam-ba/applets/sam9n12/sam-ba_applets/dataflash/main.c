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
#include <libspiflash.h>
#include <string.h>
/*----------------------------------------------------------------------------
 *        Internal definitions
 *----------------------------------------------------------------------------*/

/** SPI clock frequency in Hz. */
#define SPCK    8000000

/** Stack size in SRAM */
#define STACK_SIZE 0x100

/** Max size of data we can tranfsert in one shot */
#define MAX_COUNT 0xFFFF
#define BUFFER_NB_PAGE 24
/** Chip select value used to select the at45 chip. */
#define SPI_CS          0
/** SPI peripheral pins to configure to access the data flash. */
#define SPI_PINS        PINS_SPI0, PIN_SPI0_NPCS0

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
            uint32_t at45Idx;

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
extern int _end;
extern int _sstack;
/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/
/** Communication type with SAM-BA GUI.*/
static uint32_t comType;

/** Global DMA driver instance for all DMA transfers in application. */
static sDmad dmad;

/** SPI driver instance. */
static Spid spid;

/** Serial flash driver instance. */
static At45 at45;

/** Pins to configure for the application. */
static Pin pins[] = {SPI_PINS};

/** Size of one page in the serial flash, in bytes.  */
static uint32_t pageSize;

/** Number of pages in dataflash. */
static uint32_t numPages;

/**Size of the buffer used for read/write operations in bytes. */
static uint32_t bufferSize;

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

    const At45Desc *pDesc = 0;
    uint32_t bytesToWrite, bytesToRead, bufferAddr, memoryOffset, packetSize;
    /* index on read/write buffer */
    uint8_t *pBuffer;
    /* Temporary buffer used for non block aligned read/write */
    uint32_t tempBufferAddr;
    /* Offset in destination buffer during buffer copy */
    uint32_t bufferOffset;

    /* Configure pins */
    PIO_Configure(pins, PIO_LISTSIZE(pins));

    if (pMailbox->command == APPLET_CMD_INIT) {
        /* Save communication link type */
        comType = pMailbox->argument.inputInit.comType;

#if (DYN_TRACES == 1)
        dwTraceLevel = pMailbox->argument.inputInit.traceLevel;
#endif

        TRACE_INFO("-- DataFlash AT45 Applet %s --\n\r", SAM_BA_APPLETS_VERSION);
        TRACE_INFO("-- %s\n\r", BOARD_NAME);
        
        /* Initialize DMA driver instance with polling mode */
        DMAD_Initialize( &dmad, 1 );
        /* Initialize the SPI and serial flash */
        SPID_Configure(&spid, SPI0, ID_SPI0, &dmad);
        AT45_Configure(&at45, &spid, SPI_CS, 1);
        TRACE_INFO("SPI and at45 drivers initialized\n\r");
        pMailbox->argument.outputInit.bufferAddress = (uint32_t) &_end ;
        /* Read the JEDEC ID of the device to identify it */
        pDesc = AT45_FindDevice(&at45, AT45D_GetStatus(&at45));
         if (!pDesc) {
            pMailbox->status = APPLET_DEV_UNKNOWN;
            pMailbox->argument.outputInit.bufferSize = 0;
            pMailbox->argument.outputInit.memorySize = 0;
            TRACE_INFO("Device Unknown\n\r");
            goto exit;
        }
        else {
            /* Get device parameters */
            pMailbox->status = APPLET_SUCCESS;
            pageSize = AT45_PageSize(&at45);
            numPages = AT45_PageNumber(&at45);
            /* Program page */
            bufferSize = BUFFER_NB_PAGE * pageSize;
            pMailbox->argument.outputInit.bufferSize = bufferSize;
            pMailbox->argument.outputInit.memorySize = numPages * pageSize;
            TRACE_INFO("%s numPages : 0x%x bufferAddr : 0x%x\n\r",
                   at45.pDesc->name, (unsigned int)numPages, (unsigned int)pMailbox->argument.outputInit.bufferAddress);
        }
    }

    // ----------------------------------------------------------
    // WRITE:
    // ----------------------------------------------------------
    else if (pMailbox->command == APPLET_CMD_WRITE) {
        memoryOffset = pMailbox->argument.inputWrite.memoryOffset;
        bufferAddr   = pMailbox->argument.inputWrite.bufferAddr;
        bytesToWrite = pMailbox->argument.inputWrite.bufferSize;
        TRACE_INFO("WRITE at offset: 0x%x buffer at : 0x%x of: 0x%x Bytes\n\r",
               (unsigned int)memoryOffset, (unsigned int)bufferAddr,(unsigned int) bytesToWrite);

        pBuffer = (unsigned char *) bufferAddr;
        tempBufferAddr = bufferAddr + bufferSize;

        if ((memoryOffset % pageSize) != 0) {

            /* We are not page aligned, retrieve first page content to update it */
            memset((unsigned int *)tempBufferAddr, 0xFF, pageSize);

            bufferOffset = (memoryOffset % pageSize);

            if( (bytesToWrite + bufferOffset) < pageSize) {
                packetSize = bytesToWrite;
            }
            else {
                packetSize = pageSize - bufferOffset;
            }

            memoryOffset -= bufferOffset;

            /* Read page to be updated */
            AT45D_Read(&at45, (unsigned char *) tempBufferAddr, pageSize, memoryOffset);

            /* Fill retrieved page with data to be programmed */
            memcpy((unsigned char *)(tempBufferAddr + bufferOffset), pBuffer, packetSize);

            /* Write the page contents */
            AT45D_Write(&at45, (unsigned char *) tempBufferAddr, pageSize, memoryOffset);

            bytesToWrite -= packetSize;
            pBuffer += packetSize;
            memoryOffset += pageSize;
        }

        /* If it remains more than one page to write */
        while (bytesToWrite >= pageSize) {
            /* Write the page contents */
            AT45D_Write(&at45, pBuffer, pageSize, memoryOffset);
            pBuffer += pageSize;
            memoryOffset += pageSize;
            bytesToWrite -= pageSize;
        }

        /* Write remaining data */
        if (bytesToWrite > 0) {

            /* Read previous content of page */
            AT45D_Read(&at45, (unsigned char *) tempBufferAddr, pageSize, memoryOffset);

            /* Fill retrieved block with data to be programmed */
            memcpy((unsigned char *)tempBufferAddr, pBuffer, bytesToWrite);

            /* Write the page contents */
            AT45D_Write(&at45, (unsigned char *) tempBufferAddr, pageSize, memoryOffset);

            /* No more bytes to write */
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
               (unsigned int)memoryOffset, (unsigned int)bufferAddr, (unsigned int)bytesToRead);

        pBuffer = (unsigned char *) bufferAddr;

        /* Read packet after packets */
        while (((unsigned int)pBuffer < (bufferAddr + bufferSize)) && (bytesToRead > 0)) {

            packetSize = min(MAX_COUNT, bytesToRead);
            AT45D_Read(&at45, pBuffer, packetSize, memoryOffset);

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
        TRACE_INFO("FULL ERASE command\n\r");

        memoryOffset = 0;
        while (memoryOffset < (pageSize * numPages)) {

            /* Erase the page */
            AT45D_Erase(&at45, memoryOffset);
            memoryOffset += pageSize;
        }
        TRACE_INFO("Full Erase achieved\n\r");
        pMailbox->status = APPLET_SUCCESS;
    }
    // ----------------------------------------------------------
    // BUFFER ERASE:
    // ----------------------------------------------------------
    else if (pMailbox->command == APPLET_CMD_BUFFER_ERASE) {

        TRACE_INFO("BUFFER ERASE command\n\r");

        memoryOffset = pMailbox->argument.inputBufferErase.memoryOffset;
        while (memoryOffset < (pMailbox->argument.inputBufferErase.memoryOffset + bufferSize)) {

            /* Erase the page */
            AT45D_Erase(&at45, memoryOffset);
            memoryOffset += pageSize;
        }
        TRACE_INFO("Buffer Erase achieved\n\r");
        pMailbox->status = APPLET_SUCCESS;
    }
    // ----------------------------------------------------------
    // CONFIGURE IN BINARY MODE (power of two page size):
    // ----------------------------------------------------------
    else if (pMailbox->command == APPLET_CMD_BINARY_PAGE) {

        TRACE_INFO("BINARY PAGE SET command\n\r");
         /* Configure power-of-2 binary page size. */
        AT45D_BinaryPage(&at45);
        TRACE_INFO("Binary Page achieved\n\r");
        pMailbox->status = APPLET_SUCCESS;
    }

exit:
    /* Acknowledge the end of command */
    TRACE_INFO("\tEnd of applet (command : %x --- status : %x)\n\r", (unsigned int)pMailbox->command, (unsigned int)pMailbox->status);

    /*  Notify the host application of the end of the command processing */
    pMailbox->command = ~(pMailbox->command);
    if (comType == DBGU_COM_TYPE) {
        DBGU_PutChar(0x6);
    }
    return 0;
}

