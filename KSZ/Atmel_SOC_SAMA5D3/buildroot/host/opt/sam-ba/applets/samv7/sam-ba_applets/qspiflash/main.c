/* ----------------------------------------------------------------------------
 *         SAM Software Package License 
 * ----------------------------------------------------------------------------
 * Copyright (c) 2014, Atmel Corporation
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


/** Last erased sector id, this will avoid to erase if the block is already erased. */
static unsigned short lastErasedBlock = 0xFFFF;

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
/** Communication type with SAM-BA GUI.*/
static uint32_t comType;

/** Pins to configure for the application. */
static Pin pins[] = PINS_QSPI;

/** Size of one page in the serial flash, in bytes.  */
static uint32_t sectorSize;

/** Size of one block in the serial flash, in bytes.  */
static uint32_t blockSize;

/**Size of the buffer used for read/write operations in bytes. */
static uint32_t bufferSize;

/**Size of the buffer used for read/write operations in bytes. */
static uint32_t contReadReset = 0;


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
    uint32_t i;
    uint32_t Buffer[4];
    uint32_t jedecId;
    uint32_t bytesToWrite, bytesToRead, bufferAddr, memoryOffset;
    uint8_t *pMemory = (uint8_t *)( QSPIMEM_ADDR );
    uint8_t *pRBuf;
    uint32_t __Start_SP;
    uint32_t (*__Start_New)(void);
    /* INIT */  
    /* Configure pins */
  
    if (pMailbox->command == APPLET_CMD_INIT) {
        /* Save communication link type */
        comType = pMailbox->argument.inputInit.comType;

#if (DYN_TRACES == 1)
        dwTraceLevel = pMailbox->argument.inputInit.traceLevel;
#endif

        TRACE_INFO("-- Qspi SerialFlash (S25fl1) applet %s --\n\r", SAM_BA_APPLETS_VERSION);
        TRACE_INFO("-- %s\n\r", BOARD_NAME);
     

        pMailbox->argument.outputInit.bufferAddress = (uint32_t) &end + 0x10000 ;
        PIO_Configure(pins, PIO_LISTSIZE(pins));
        ENABLE_PERIPHERAL(ID_QSPI);

        S25FL1D_InitFlashInterface(1);
        TRACE_INFO("QSPI drivers initialized\n\r");

        /* enable quad mode */
        S25FL1D_QuadMode(1);
        /* Read the JEDEC ID of the device to identify it */
        jedecId = S25FL1D_ReadJedecId();
        TRACE_INFO("-- jedecId is %x \n\r", (unsigned int)jedecId);
        if (jedecId != 0x1154001) {
            pMailbox->status = APPLET_DEV_UNKNOWN;
            pMailbox->argument.outputInit.bufferSize = 0;
            pMailbox->argument.outputInit.memorySize = 0;
            TRACE_INFO("Device Unknown\n\r");
            goto exit;
        } else {
            /* Get device parameters */
            pMailbox->status = APPLET_SUCCESS;
            sectorSize = 4 * 1024;
            blockSize = 64 * 1024;
            bufferSize = 10 * sectorSize;
            /* integer number of pages can be contained in each buffer */
            bufferSize -= bufferSize % sectorSize; 
            if ( bufferSize < sectorSize) {
                TRACE_INFO("No enough memory to load buffer.\n\r");
                goto exit;
            } 
            pMailbox->argument.outputInit.bufferSize = bufferSize;
            pMailbox->argument.outputInit.memorySize = 2 * 1024 * 1024;
            TRACE_INFO(" blockSize : 0x%x bufferAddr : 0x%x\n\r",
                    (unsigned int)blockSize, (unsigned int)pMailbox->argument.outputInit.bufferAddress);
        }
    }

    // ----------------------------------------------------------
    // WRITE:
    // ----------------------------------------------------------
    else if (pMailbox->command == APPLET_CMD_WRITE) {
        memoryOffset = pMailbox->argument.inputWrite.memoryOffset;
        bufferAddr        = pMailbox->argument.inputWrite.bufferAddr;
        bytesToWrite      = pMailbox->argument.inputWrite.bufferSize;
        
        TRACE_INFO("WRITE at offset: 0x%x buffer at : 0x%x of: 0x%x Bytes\n\r",
               (unsigned int)memoryOffset, (unsigned int)bufferAddr, (unsigned int)bytesToWrite);
        /* Check word alignment */
        if (memoryOffset % 4) {

            pMailbox->status = APPLET_ALIGN_ERROR;
            goto exit;
        }
        if (contReadReset){
           TRACE_INFO("Reset continue read mode \n\r");
           S25FL1D_ContModeReset();
           contReadReset = 0;
        }
        if (((memoryOffset / blockSize) > lastErasedBlock) || (lastErasedBlock == 0xFFFF) || memoryOffset == 0) {
            /* Erase the block to be updated */
            TRACE_INFO("Erase 64K block from %x \n\r", memoryOffset);
            S25FL1D_Erase64KBlock(memoryOffset);
            lastErasedBlock = (memoryOffset / blockSize);
        }
        /*  Write the contents */
        TRACE_INFO("S25FL1D_Write from %x \n\r", *(uint32_t *)bufferAddr);
        S25FL1D_Write((uint32_t *)bufferAddr, bytesToWrite, memoryOffset, 0);
        TRACE_INFO("WRITE return byte written : 0x%x Bytes\n\r",
               (unsigned int)(pMailbox->argument.inputWrite.bufferSize ));

        pMailbox->argument.outputWrite.bytesWritten = pMailbox->argument.inputWrite.bufferSize;
        pMailbox->status = APPLET_SUCCESS;
    }

    // ----------------------------------------------------------
    // READ:
    // ----------------------------------------------------------
    else if (pMailbox->command == APPLET_CMD_READ) {
        memoryOffset = pMailbox->argument.inputRead.memoryOffset;
        bufferAddr   = pMailbox->argument.inputRead.bufferAddr;
        bytesToRead  = pMailbox->argument.inputRead.bufferSize;
        pRBuf = (uint8_t *)bufferAddr;
        TRACE_INFO("READ at offset: 0x%x buffer at : 0x%x of: 0x%x Bytes\n\r",
               (unsigned int)memoryOffset, (unsigned int)bufferAddr, (unsigned int)bytesToRead);
        S25FL1D_ReadQuadIO(Buffer, sizeof(Buffer), 0, 0, 0 );
        contReadReset = 1;
        for (i = 0; i < bytesToRead; i++) *pRBuf++ = *pMemory++;
        TRACE_INFO("READ return byte read : 0x%x Bytes\n\r",
               (unsigned int)(pMailbox->argument.inputRead.bufferSize ));

        pMailbox->argument.outputRead.bytesRead = pMailbox->argument.inputRead.bufferSize ;
        pMailbox->status = APPLET_SUCCESS;
    }

    // ----------------------------------------------------------
    // FULL ERASE:
    // ----------------------------------------------------------
    else if (pMailbox->command == APPLET_CMD_BUFFER_ERASE) {

        TRACE_INFO("BUFFER ERASE \n\r");
        memoryOffset = pMailbox->argument.inputBufferErase.memoryOffset;
        S25FL1D_Erase64KBlock(memoryOffset);
        pMailbox->argument.outputBufferErase.bytesErased = blockSize;
        pMailbox->status = APPLET_SUCCESS;
    }
    else if (pMailbox->command == APPLET_EXECUTE_QSPI) {

        TRACE_INFO("Enter XIP mode and execute from QSPI flash..., sam-ba will be halted\n\r");
        S25FL1D_ReadQuadIO(Buffer, sizeof(Buffer), 0, 1, 0 );
        __Start_New = (uint32_t(*) (void) ) Buffer[1];
        __Start_SP = Buffer[0];
        asm ("MSR msp, %0\n" : : "r" (__Start_SP) : "sp");
        __Start_New();
        pMailbox->status = APPLET_SUCCESS;
    }

exit:
    /* Acknowledge the end of command */
    TRACE_INFO("\tEnd of applet (command : %x --- status : %x)\n\r", (unsigned int)pMailbox->command, (unsigned int)pMailbox->status);

    /*  Notify the host application of the end of the command processing */
    pMailbox->command = ~(pMailbox->command);
    if (comType == DBGU_COM_TYPE) {
        DBG_PutChar(0x6);
    }
    return 0;
}

