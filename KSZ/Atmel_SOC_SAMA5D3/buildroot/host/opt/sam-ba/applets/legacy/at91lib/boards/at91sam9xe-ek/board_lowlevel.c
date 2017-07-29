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

#include "board.h"
#include "board_memories.h"
#include <pmc/pmc.h>

//------------------------------------------------------------------------------
//         Local definitions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \page "SAM9XE - Oscillator & PLL Parameters"
/// This page lists the parameters which are set for the PLL and main
/// oscillator configuration.
///
/// !Parameters
/// - BOARD_OSCOUNT
/// - BOARD_CKGR_PLLA
/// - BOARD_PLLACOUNT
/// - BOARD_MULA
/// - BOARD_DIVA
/// - BOARD_CKGR_PLLB
/// - BOARD_PLLBCOUNT
/// - BOARD_MULB
/// - BOARD_DIVB
/// - BOARD_USBDIV
/// - BOARD_PRESCALER

/// Main oscillator startup time (in number of slow clock ticks). 
#define BOARD_OSCOUNT           (AT91C_CKGR_OSCOUNT & (64 << 8))

/// PLLA frequency range.
#define BOARD_CKGR_PLLA         (AT91C_CKGR_SRCA | AT91C_CKGR_OUTA_2)
/// PLLA startup time (in number of slow clock ticks).
#define BOARD_PLLACOUNT         (63 << 8)
/// PLLA MUL value.
#define BOARD_MULA              (AT91C_CKGR_MULA & (96 << 16))
/// PLLA DIV value.
#define BOARD_DIVA              (AT91C_CKGR_DIVA & 9)

/// PLLB frequency range
#define BOARD_CKGR_PLLB         AT91C_CKGR_OUTB_1
/// PLLB startup time (in number of slow clock ticks).
#define BOARD_PLLBCOUNT         BOARD_PLLACOUNT
/// PLLB MUL value.
#define BOARD_MULB              (124 << 16)
/// PLLB DIV value.
#define BOARD_DIVB              12

/// USB PLL divisor value to obtain a 48MHz clock.
#define BOARD_USBDIV            AT91C_CKGR_USBDIV_2
/// Master clock prescaler value.
#define BOARD_PRESCALER         AT91C_PMC_MDIV_2
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//         Local functions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// Default spurious interrupt handler
//------------------------------------------------------------------------------
void DefaultSpuriousHandler(void)
{
    while (1);
}

//------------------------------------------------------------------------------
/// Default handler for fast interrupt requests.
//------------------------------------------------------------------------------
void DefaultFiqHandler(void)
{
    while (1);
}

//------------------------------------------------------------------------------
/// Default handler for standard interrupt requests.
//------------------------------------------------------------------------------
void DefaultIrqHandler(void)
{
    while (1);
}

//------------------------------------------------------------------------------
//         Global functions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// Performs the low-level initialization of the chip.
//------------------------------------------------------------------------------
void LowLevelInit(unsigned int clockConfigEnable)
{
    unsigned char i;
    pllConfiguration pll;
    mckrConfiguration mckr;

    // Set flash wait states
    //----------------------
    AT91C_BASE_EFC->EFC_FMR = 6 << 8;
    if (clockConfigEnable)
    {
        // Switch MCK to Slow clock 
        PMC_SwitchMck2SlowClock();
        //  enable Main oscillator 
        PMC_EnableMainOsc();
        // Then, cofigure PLLA and switch clock
        // MCK = 18.432MHz * 73 / 14 / 1 / 2 = 48MHz -> 0x10483F0E
        pll.mul = 0x49;  pll.div = 0x0E; pll.usbdiv = 0; pll.pllout = 0;
        mckr.prescaler = AT91C_PMC_PRES_CLK; mckr.mdiv = AT91C_PMC_MDIV_2; mckr.plldiv2 = 0;
        PMC_ConfigureMckWithPlla(&pll, &mckr);
    }

    // Initialize AIC
    //---------------
    AT91C_BASE_AIC->AIC_IDCR = 0xFFFFFFFF;
    AT91C_BASE_AIC->AIC_SVR[0] = (unsigned int) DefaultFiqHandler;
    for (i = 1; i < 31; i++) {

        AT91C_BASE_AIC->AIC_SVR[i] = (unsigned int) DefaultIrqHandler;
    }
    AT91C_BASE_AIC->AIC_SPU = (unsigned int) DefaultSpuriousHandler;

    // Unstack nested interrupts
    for (i = 0; i < 8 ; i++) {

        AT91C_BASE_AIC->AIC_EOICR = 0;
    }

    // Watchdog initialization
    //------------------------
    AT91C_BASE_WDTC->WDTC_WDMR = AT91C_WDTC_WDDIS;

    // Remap
    //------
    BOARD_RemapRam();

}

