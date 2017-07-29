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
 * Implementation of extram applet for ISP.
 *
 */
 
/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "../common/applet.h"
#include <board.h>

#include <string.h>

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/

/* Board DDRAM size*/
#define BOARD_DDRAM_SIZE        (128*1024*1024)  // 128 MB
#define BOARD_SDRAM_SIZE        (32*1024*1024)   // 32 MB
/* Define clock timeout */
#define CLOCK_TIMEOUT    0xFFFFFFFF

/*----------------------------------------------------------------------------
 *        Local structures
 *----------------------------------------------------------------------------*/

/** \brief Structure for storing parameters for each command that can be 
 *   performed by the applet. */
 
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
            /** Trace level.*/
            uint32_t traceLevel;
            /** External memory voltage selection.*/
            uint32_t VddMemSel;
            /** External RAM type.*/
            uint32_t ramType;
            /** External RAM bus width.*/
            uint32_t dataBusWidth;
            /** External DDRAM Model.*/
            uint32_t ddrModel;

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
    } argument;
};


/*----------------------------------------------------------------------------
 *        Global variables
 *----------------------------------------------------------------------------*/
/** End of program space (code + data).*/
extern uint32_t _end;
/** Depending on DYN_TRACES, dwTraceLevel is a modifable runtime variable or a define */
//uint32_t dwTraceLevel;

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/
 /**
 * \brief  Go/No-Go test of the first 10K-Bytes of external RAM access.
 *
 * \return 0 if test is failed else 1.
 */

static unsigned char ExtRAM_TestOk(void)
{
    uint32_t i;
    uint32_t *ptr = (uint32_t *) EBI_DDRSDRC_ADDR;

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

static uint8_t isLowlevelInitialized( void )
{
    uint32_t read;
    read = PMC->CKGR_PLLAR;
    if ( read == CKGR_PLLAR_STUCKTO1 |\
                 CKGR_PLLAR_MULA(149) |\
                 CKGR_PLLAR_OUTA(0) |\
                 CKGR_PLLAR_PLLACOUNT(63) ||
                 CKGR_PLLAR_DIVA(3))
    {
        read = PMC->PMC_MCKR;
        if ( read == (PMC_MCKR_CSS_PLLA_CLK | PMC_MCKR_PLLADIV2_DIV2 | PMC_MCKR_MDIV_PCK_DIV3))
        {
            return 1;
        }
    }
    return 0;
}

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/
/**
 * \brief  Applet main entry. This function decodes received command and executes it.
 *
 * \param argc  always 1
 * \param argv  Address of the argument area..
 */
 
int main(int argc, char **argv)
{
    struct _Mailbox *pMailbox = (struct _Mailbox *) argv;
    uint32_t comType = pMailbox->argument.inputInit.comType;
    /* INIT: */
    if (pMailbox->command == APPLET_CMD_INIT) 
    {
        /* Save communication link type */
        WDT->WDT_MR = WDT_MR_WDDIS;
        if(!isLowlevelInitialized())
        {
            pMailbox->status = APPLET_FAIL;
            pMailbox->argument.outputInit.bufferAddress = ((uint32_t) &_end);
            pMailbox->argument.outputInit.bufferSize = 99;
            pMailbox->command = ~(pMailbox->command);
            return 0;
        }
#if (DYN_TRACES == 1)
        //dwTraceLevel = 0;
#endif

#if (TRACE_LEVEL==0) && (DYN_TRACES==1) 
        if (comType == DBGU_COM_TYPE)
        {
            /* Function TRACE_CONFIGURE_ISP wiil be bypass due to the 0 TRACE_LEVEL. We shall reconfigure the baut rate. */
            //DBGU_Configure( 115200 , BOARD_MCK);
             DBGU->DBGU_MR = DBGU_MR_CHMODE_NORM | DBGU_MR_PAR_NONE;
            /* Reset and disable receiver & transmitter */
            DBGU->DBGU_CR = DBGU_CR_RSTRX | DBGU_CR_RSTTX;
            DBGU->DBGU_IDR = 0xFFFFFFFF;
            DBGU->DBGU_CR = DBGU_CR_RSTRX | DBGU_CR_RSTTX | DBGU_CR_RXDIS | DBGU_CR_TXDIS;
            /* Configure baudrate */
            DBGU->DBGU_BRGR = (BOARD_MCK / 115200) / 16;
            /* Enable receiver and transmitter */
            DBGU->DBGU_CR = DBGU_CR_RXEN | DBGU_CR_TXEN;
        }

#endif
    
        //TRACE_INFO("-- EXTRAM Applet %s --\n\r", SAM_BA_APPLETS_VERSION);
        //TRACE_INFO("-- %s\n\r", BOARD_NAME);
        //TRACE_INFO("-- Compiled: %s %s --\n\r", __DATE__, __TIME__);
        //TRACE_INFO("INIT command:\n\r");

        //TRACE_INFO("\tCommunication link type : %lu\n\r", pMailbox->argument.inputInit.comType);
        
        //TRACE_INFO("\tInit EBI Vdd : %s\n\r", (pMailbox->argument.inputInit.VddMemSel)?"3.3V":"1.8V");
        //BOARD_ConfigureVddMemSel(pMailbox->argument.inputInit.VddMemSel);

        /* Configure DDRAM controller */

        if ( pMailbox->argument.inputInit.ramType == 0) 
        {
            //TRACE_INFO("\tExternal RAM type : %s\n\r", "SDRAM");
            BOARD_ConfigureSdram();
            pMailbox->argument.outputInit.memorySize = BOARD_SDRAM_SIZE;
        }
        else 
        {
            //TRACE_INFO("\tExternal RAM type : %s\n\r", "DDRAM");
            BOARD_ConfigureDdram();
            pMailbox->argument.outputInit.memorySize = BOARD_DDRAM_SIZE;
        }
        /* Test external RAM access */
        if (ExtRAM_TestOk()) 
        {

            pMailbox->status = APPLET_SUCCESS;
        }
        else {
            pMailbox->status = APPLET_FAIL;
        }
        pMailbox->argument.outputInit.bufferAddress = ((uint32_t) &_end);
        pMailbox->argument.outputInit.bufferSize = 0;
        //TRACE_INFO("\tInit successful.\n\r");
    }

    /* Acknowledge the end of command */
    //TRACE_INFO("\tEnd of applet (command : %lx --- status : %lx)\n\r", pMailbox->command, pMailbox->status);

    /* Notify the host application of the end of the command processing */
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

