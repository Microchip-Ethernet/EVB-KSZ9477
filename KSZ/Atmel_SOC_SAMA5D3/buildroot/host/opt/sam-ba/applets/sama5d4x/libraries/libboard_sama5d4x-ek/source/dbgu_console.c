/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support 
 * ----------------------------------------------------------------------------
 * Copyright (c) 2013, Atmel Corporation
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
 * Implements DBGU console.
 *
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"

#include <stdio.h>
#include <stdint.h>

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/

/** The Pheripheral has no HW ID */
#define ID_NOTUSED         0xFF

/** Usart Hw ID (ID_USART0) */
#define CONSOLE_ID              (pDbgPort->bID)
/** Usart Hw interface used by the console (USART0). */
#define CONSOLE_DBGU            ((Dbgu*)pDbgPort->pHw)
/** Pins description list */
#define CONSOLE_PINLIST         (pDbgPort->pPioList)
/** Pins description list size */
#define CONSOLE_PINLISTSIZE     (pDbgPort->bPioListSize)

/*----------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/

/**
 * Debug port struct
 */
typedef struct _DbgPort {
    const  void*   pHw;
    const  Pin*    pPioList;
    const  uint8_t bPioListSize;
    const  uint8_t bID;
} sDbgPort;

/*----------------------------------------------------------------------------
 *        Variables
 *----------------------------------------------------------------------------*/

/** Pins for DBGU */
static const Pin pinsDbgu[] = {PINS_DBGU};
/** Pins for USART0 */
static const Pin pinsUs0[] = {PIN_USART0_TXD, PIN_USART0_RXD};
/** Pins for USART3 */
static const Pin pinsUs3[] = {PIN_USART3_TXD, PIN_USART3_RXD};

/** Uses DBGU as debug port */
static sDbgPort dbgpDbgu =
{
    DBGU,
    pinsDbgu, PIO_LISTSIZE(pinsDbgu),
    ID_NOTUSED
};
/** Uses USART0 as debug port */
static sDbgPort dbgpUs0  =
{
    USART0,
    pinsUs0, PIO_LISTSIZE(pinsUs0),
    ID_USART0
};

/** Uses USART0 as debug port */
static sDbgPort dbgpUs3  =
{
    USART3,
    pinsUs3, PIO_LISTSIZE(pinsUs3),
    ID_USART3
};

/** Current used debug port */
static sDbgPort *pDbgPort = &dbgpUs3;

/** Console initialize status */
uint8_t _bConsoleIsInitialized = 0;

/**
 * \brief Select USART0 as DBGU port.
 */
void DBGU_ConsoleUseUSART0(void)
{
    pDbgPort = &dbgpUs0;
    _bConsoleIsInitialized = 0;
}

/**
 * \brief Select USART3 as DBGU port.
 */
void DBGU_ConsoleUseUSART3(void)
{
    pDbgPort = &dbgpUs3;
    _bConsoleIsInitialized = 0;
}

/**
 * \brief Select DBGU as DBGU port.
 */
void DBGU_ConsoleUseDBGU(void)
{
    pDbgPort = &dbgpDbgu;
    _bConsoleIsInitialized = 0;
}

/**
 * \brief Configures an DBGU peripheral with the specified parameters.
 *
 * \param baudrate  Baudrate at which the DBGU should operate (in Hz).
 * \param masterClock  Frequency of the system master clock (in Hz).
 */
extern void DBGU_Configure( uint32_t baudrate, uint32_t masterClock)
{
#if 1
    /* Configure PIO */
    PIO_Configure(CONSOLE_PINLIST, CONSOLE_PINLISTSIZE);

    if ( ID_NOTUSED != CONSOLE_ID )
    {
        PMC_EnablePeripheral(CONSOLE_ID);
    }

    /* Configure mode register */
    if (CONSOLE_DBGU!= DBGU ) {
        CONSOLE_DBGU->DBGU_MR = DBGU_MR_CHMODE_NORM | DBGU_MR_PAR_NONE | US_MR_CHRL_8_BIT;
    }
    else {
        CONSOLE_DBGU->DBGU_MR = DBGU_MR_CHMODE_NORM | DBGU_MR_PAR_NONE;
    }
    /* Reset and disable receiver & transmitter */
    CONSOLE_DBGU->DBGU_CR = DBGU_CR_RSTRX | DBGU_CR_RSTTX;
    CONSOLE_DBGU->DBGU_IDR = 0xFFFFFFFF;
    CONSOLE_DBGU->DBGU_CR = DBGU_CR_RXDIS | DBGU_CR_TXDIS;
    /* Configure baudrate */
    CONSOLE_DBGU->DBGU_BRGR = (masterClock/2 / baudrate) / 16;
    /* Enable receiver and transmitter */
    CONSOLE_DBGU->DBGU_CR = DBGU_CR_RXEN | DBGU_CR_TXEN;
#endif
    _bConsoleIsInitialized = 1 ;
#if defined(__GNUC__)
    //setvbuf(stdout, (char*)NULL, _IONBF, 0);
#endif
}

/**
 * \brief Outputs a character on the DBGU line.
 *
 * \note This function is synchronous (i.e. uses polling).
 * \param c  Character to send.
 */
extern void DBGU_PutChar( uint8_t c )
{
    if ( !_bConsoleIsInitialized )
    {
        DBGU_Configure(CONSOLE_BAUDRATE, BOARD_MCK);
    }

    /* Wait for the transmitter to be ready */
    while ( (CONSOLE_DBGU->DBGU_SR & DBGU_SR_TXEMPTY) == 0 ) ;

    /* Send character */
    CONSOLE_DBGU->DBGU_THR=c ;
}

/**
 * \brief Input a character from the DBGU line.
 *
 * \note This function is synchronous
 * \return character received.
 */
extern uint32_t DBGU_GetChar( void )
{
    if ( !_bConsoleIsInitialized )
    {
    //    DBGU_Configure(CONSOLE_BAUDRATE, BOARD_MCK);
    }

    while ( (CONSOLE_DBGU->DBGU_SR & DBGU_SR_RXRDY) == 0 ) ;
    return CONSOLE_DBGU->DBGU_RHR ;
}

/**
 * \brief Check if there is Input from DBGU line.
 *
 * \return true if there is Input.
 */
extern uint32_t DBGU_IsRxReady( void )
{
    if ( !_bConsoleIsInitialized )
    {
        //DBGU_Configure( CONSOLE_BAUDRATE, BOARD_MCK ) ;
    }
    return (CONSOLE_DBGU->DBGU_SR & DBGU_SR_RXRDY) > 0 ;
}

