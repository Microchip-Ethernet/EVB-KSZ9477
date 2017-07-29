/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support 
 * ----------------------------------------------------------------------------
 * Copyright (c) 2011, Atmel Corporation
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
 * Provides the low-level initialization function that called on chip startup.
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"

/*----------------------------------------------------------------------------
 *        Internal functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Default spurious interrupt handler. Infinite loop.
 */
void defaultSpuriousHandler( void )
{
    while (1);
}

/**
 * \brief Default handler for fast interrupt requests. Infinite loop.
 */
void defaultFiqHandler( void )
{
    while (1);
}

/**
 * \brief Default handler for standard interrupt requests. Infinite loop.
 */
void defaultIrqHandler( void )
{
    while (1);
}

/* Define clock timeout */
#define CLOCK_TIMEOUT    0xFFFFFFFF

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Performs the low-level initialization of the chip.
 * This includes EFC and master clock configuration.
 * It also enable a low level on the pin NRST triggers a user reset.
 */
extern WEAK void LowLevelInit( void )
{
    uint8_t i;
    uint32_t _dwTimeout = 0;
    volatile uint32_t read = 0;
    
    if ((uint32_t)LowLevelInit < EBI_CS0_ADDR) /* Code not in external mem */
    {
        /* Switch to PLL + prescaler */
        read = PMC->PMC_MCKR;
        read &= ~(PMC_MCKR_CSS_Msk);
        read |= PMC_MCKR_CSS_MAIN_CLK;
        PMC->PMC_MCKR = read;
        while (!(PMC->PMC_SR & PMC_SR_MCKRDY));
        
        PMC->CKGR_MOR = CKGR_MOR_KEY(0x37) | CKGR_MOR_MOSCXTST(64) | CKGR_MOR_MOSCRCEN | CKGR_MOR_MOSCXTEN | CKGR_MOR_MOSCSEL;
        _dwTimeout = 0;
        while (!(PMC->PMC_SR & PMC_SR_MOSCXTS) && (_dwTimeout++ < CLOCK_TIMEOUT));
        
        PMC->CKGR_PLLAR = 0;

        /* Initialize PLLA */
        PMC->CKGR_PLLAR = CKGR_PLLAR_STUCKTO1
                        | CKGR_PLLAR_MULA(199) 
                        | CKGR_PLLAR_OUTA(0)
                        | CKGR_PLLAR_PLLACOUNT(63)
                        | CKGR_PLLAR_DIVA(3);
        _dwTimeout = 0;
        while (!(PMC->PMC_SR & PMC_SR_LOCKA) && (_dwTimeout++ < CLOCK_TIMEOUT));
        
        /* Wait for the master clock if it was already initialized */
        for ( _dwTimeout =  0; !(PMC->PMC_SR & PMC_SR_MCKRDY) && (_dwTimeout++ < CLOCK_TIMEOUT) ; );

        /* Switch to fast clock
        **********************/
        /* Switch to main oscillator + prescaler */
        read = PMC->PMC_MCKR;
        read &= ~(PMC_MCKR_MDIV_Msk);
        read |= (PMC_MCKR_MDIV_PCK_DIV3 | PMC_MCKR_PLLADIV2_DIV2);
        PMC->PMC_MCKR = read;
       
        /* Wait for the master clock if it was already initialized */
        for ( _dwTimeout =  0; !(PMC->PMC_SR & PMC_SR_MCKRDY) && (_dwTimeout++ < CLOCK_TIMEOUT) ; );
      
        /* Switch to main oscillator + prescaler */
        read = PMC->PMC_MCKR;
        read &= ~(PMC_MCKR_PRES_Msk);
        read |= PMC_MCKR_PRES_CLOCK;
        PMC->PMC_MCKR = read;

        /* Wait for the master clock if it was already initialized */
        for ( _dwTimeout =  0; !(PMC->PMC_SR & PMC_SR_MCKRDY) && (_dwTimeout++ < CLOCK_TIMEOUT) ; );

        /* Switch to PLL + prescaler */
        read = PMC->PMC_MCKR;
        read &= ~(PMC_MCKR_CSS_Msk);
        read |= PMC_MCKR_CSS_PLLA_CLK;
        PMC->PMC_MCKR = read;

        /* Wait for the master clock if it was already initialized */
        for ( _dwTimeout =  0; !(PMC->PMC_SR & PMC_SR_MCKRDY) && (_dwTimeout++ < CLOCK_TIMEOUT) ; );
    } 

    /* Initialize AIC */
    AIC->AIC_IDCR = 0xFFFFFFFF;
    AIC->AIC_SVR[0] = (unsigned int) defaultFiqHandler;

    for (i = 1; i < 31; i++) {
        AIC->AIC_SVR[i] = (unsigned int) defaultIrqHandler;
    }
    AIC->AIC_SPU = (unsigned int) defaultSpuriousHandler;

    /* Unstack nested interrupts */
    for (i = 0; i < 8 ; i++) {

        AIC->AIC_EOICR = 0;
    }
    /* Remap */
     BOARD_RemapRam();

}

