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

/**
 * \file
 *
 * Implementation of extram applet for SAM-BA.
 *
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "../common/applet.h"
#include "board.h"

#include <string.h>

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/

/** Base address of SDRAM */
#define EXTRAM_ADDR EBI_SDRAMC_ADDR
/** Size of SDRAM */
#define EXTRAM_SIZE BOARD_SDRAM_SIZE

/** External RAM is SDRAM */
#define TYPE_SDRAM 0
/** External RAM is DDRAM */
#define TYPE_DDRAM 1
/** External RAM is PSRAM */
#define TYPE_PSRAM 2


/*----------------------------------------------------------------------------
 *        Local structures
 *----------------------------------------------------------------------------*/

/** \brief Structure for storing parameters for each command that can be
 * performed by the applet.*/

struct _Mailbox {

    /** Command send to the monitor to be executed. */
    uint32_t command;
    /** Returned status, updated at the end of the monitor execution. */
    uint32_t status;

    /** Input Arguments in the argument area */
    union {

        /** Input arguments for the Init command. */
        struct {

            /** Communication link used. */
            uint32_t comType;
            /** Trace level. */
            uint32_t traceLevel;
            /** External memory voltage selection. */
            uint32_t VddMemSel;
            /** External RAM type. */
            uint32_t ramType;
            /** External RAM bus width. */
            uint32_t dataBusWidth;
            /** External DDRAM Model. */
            uint32_t ddrModel;

        } inputInit;

        /** Output arguments for the Init command. */
        struct {

            /** Memory size. */
            uint32_t memorySize;
            /** Buffer address. */
            uint32_t bufferAddress;
            /** Buffer size. */
            uint32_t bufferSize;
        } outputInit;
    } argument;
};


/*----------------------------------------------------------------------------
 *        Variables
 *----------------------------------------------------------------------------*/

/** Marks the end of program space. */
extern uint32_t end;


/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Go/No-Go test of the first 10K-Bytes of external RAM access.
 *
 * \return 0 if test is failed else 1.
 */
static uint8_t ExtRAM_TestOk(void)
{
    uint32_t i;
    uint32_t *ptr = (uint32_t *) EXTRAM_ADDR;

    for (i = 0; i < 10 * 1024; ++i) {

        if (i & 1) {
            ptr[i] = 0x55AA55AA | (1 << i);
        }
        else {
            ptr[i] = 0xAA55AA55 | (1 << i);
        }
    }

    for (i = 0; i < 10 * 1024; ++i) {
        if (i & 1) {
            if (ptr[i] != (0x55AA55AA | (1 << i))) {
                return 0;
            }
        }
        else {
            if (ptr[i] != (0xAA55AA55 | (1 << i))) {
                return 0;
            }
        }
    }

    return 1;
}

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Applet code for initializing the external RAM.
 */
int main(int argc, char **argv)
{
    struct _Mailbox *pMailbox = (struct _Mailbox *) argv;
    uint32_t ramType = 0;
    uint32_t dataBusWidth = 0;
    uint32_t ddrModel = 0;
    uint32_t comType = 0;

    /* ---------------------------------------------------------- */
    /* INIT: */
    /* ---------------------------------------------------------- */
    if (pMailbox->command == APPLET_CMD_INIT) {
        /* Save info of communication link */
        comType = pMailbox->argument.inputInit.comType;

        /*  Re-configurate UART   (MCK maybe change in LowLevelInit())  */
        UART_Configure(115200, BOARD_MCK);

        ramType = pMailbox->argument.inputInit.ramType;
        dataBusWidth = pMailbox->argument.inputInit.dataBusWidth;
        ddrModel = pMailbox->argument.inputInit.ddrModel;

#if (DYN_TRACES == 1)
        dwTraceLevel = pMailbox->argument.inputInit.traceLevel;
#endif

        TRACE_INFO("-- EXTRAM Applet %s --\n\r", SAM_BA_APPLETS_VERSION);
        TRACE_INFO("-- %s\n\r", BOARD_NAME);
        TRACE_INFO("INIT command:\n\r");

        TRACE_INFO("\tCommunication link type : %d\n\r",(unsigned int)( pMailbox->argument.inputInit.comType));
        TRACE_INFO("\tData bus width : %d bits\n\r", (unsigned int)dataBusWidth);
        if (ramType == TYPE_SDRAM) {
           TRACE_INFO("\tExternal RAM type : %s\n\r", "SDRAM");
        }
        else {
            TRACE_INFO("\tUnknow External RAM type\n\r");
        }

        if (pMailbox->argument.inputInit.ramType == TYPE_SDRAM) {
            /* Configure SDRAM controller */
            TRACE_INFO("\tInit SDRAM...\n\r");
            BOARD_ConfigureSdram();
        }

        /* Test external RAM access */
        if (ExtRAM_TestOk()) {

            pMailbox->status = APPLET_SUCCESS;
            TRACE_INFO("\tInit successful.\n\r");
        }
        else {
            pMailbox->status = APPLET_FAIL;
            TRACE_INFO("\tInit failure.\n\r");
        }

        pMailbox->argument.outputInit.bufferAddress = ((uint32_t) &end);
        pMailbox->argument.outputInit.bufferSize = 0;
        pMailbox->argument.outputInit.memorySize = EXTRAM_SIZE;
    }

    /* Acknowledge the end of command */
    TRACE_INFO("\tEnd of applet (command : %x --- status : %x)\n\r", (unsigned int)(pMailbox->command), (unsigned int)(pMailbox->status));

    /* Notify the host application of the end of the command processing */
    pMailbox->command = ~(pMailbox->command);
    if (comType == DBGU_COM_TYPE) {
        UART_PutChar(0x6);
    }

    return 0;
}

