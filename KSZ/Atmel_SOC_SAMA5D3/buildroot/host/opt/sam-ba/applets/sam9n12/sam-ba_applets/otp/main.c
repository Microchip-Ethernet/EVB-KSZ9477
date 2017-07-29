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
#include <include/trace.h>
#include <string.h>

/*----------------------------------------------------------------------------
 *        Internal definitions
 *----------------------------------------------------------------------------*/

/** OTP CFG Word Address */
#define OTP_CFG_WORDADDR    9

/** OTP CFG Offset in bit */
#define CFG_OFFSET          24

/** OTP Size in bit */
#define OTP_BIT_SIZE        320

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

            /** OTP address.*/
            uint32_t otpAddr;
            /** CFG flag.*/
            uint32_t isCfg;
            /** OTP data to be fuse.*/
            uint32_t data;

        } inputWrite;

        /** Output arguments for the Write command.*/

        /** Input arguments for the Read command.*/
        struct {

            /** OTP address. */
            uint32_t otpAddr;
            /** CFG flag.*/
            uint32_t isCfg;
        } inputRead;

        /** Output arguments for the Read command.*/
        struct {
            /** OTP read.*/
            uint32_t status;
        } outputRead;
    } argument;
};

/*----------------------------------------------------------------------------
 *        Global variables
 *----------------------------------------------------------------------------*/

/** End of program space (code + data). */
extern int _end;
extern int _sstack;
/** Communication type with SAM-BA GUI.*/
static uint32_t comType;

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
    uint32_t wordPosition, fuseStatus, fuseDate;
    uint32_t isCfg;
    /* INIT */  
    // ----------------------------------------------------------
    // OPT INIT:
    // ----------------------------------------------------------
    if (pMailbox->command == APPLET_CMD_INIT) {
        /* Save communication link type */
        comType = pMailbox->argument.inputInit.comType;

#if (DYN_TRACES == 1)
        dwTraceLevel = pMailbox->argument.inputInit.traceLevel;
#endif
        TRACE_INFO("READ OTP CFG command\n\r");
        // bufferAddress = (uint32_t) &_end ;
        pMailbox->argument.outputInit.bufferAddress = ((uint32_t) &_end);
        pMailbox->argument.outputInit.bufferSize = 100;
        pMailbox->argument.outputInit.memorySize = OTP_BIT_SIZE /8;
        pMailbox->status = APPLET_SUCCESS;
    }
    // ----------------------------------------------------------
    // READ OTP:
    // ----------------------------------------------------------
    else if (pMailbox->command == APPLET_CMD_OTP_READ) {
        TRACE_INFO("READ OTP command\n\r");
        wordPosition = pMailbox->argument.inputRead.otpAddr;
        isCfg = pMailbox->argument.inputRead.isCfg;
        if (isCfg){
            fuseStatus = FUSE_Read (OTP_CFG_WORDADDR );
            pMailbox->argument.outputRead.status = fuseStatus >> CFG_OFFSET;
        } else {
            fuseStatus = FUSE_Read (wordPosition );
            pMailbox->argument.outputRead.status = fuseStatus;
        }
        pMailbox->status = APPLET_SUCCESS;
    }

    // ----------------------------------------------------------
    // WRITE OTP:
    // ----------------------------------------------------------
    else if (pMailbox->command == APPLET_CMD_OTP_WRITE) {
        TRACE_INFO("WRITE OTP command\n\r");
        wordPosition = pMailbox->argument.inputWrite.otpAddr;
        isCfg = pMailbox->argument.inputRead.isCfg;
        if (isCfg){
            fuseDate = pMailbox->argument.inputWrite.data << CFG_OFFSET;
            FUSE_Write (fuseDate, OTP_CFG_WORDADDR );
        } else {
            fuseDate = pMailbox->argument.inputWrite.data;
            FUSE_Write (fuseDate, wordPosition );
        }
        TRACE_INFO("WRITE OTP achieved\n\r");
        pMailbox->status = APPLET_SUCCESS;
    }

    /* Acknowledge the end of command */
    TRACE_INFO("\tEnd of applet (command : %lx --- status : %lx)\n\r", pMailbox->command, pMailbox->status);

    /*  Notify the host application of the end of the command processing */
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

