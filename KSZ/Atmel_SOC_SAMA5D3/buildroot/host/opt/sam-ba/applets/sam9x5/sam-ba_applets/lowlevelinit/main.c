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
 *        Local definitions
 *----------------------------------------------------------------------------*/
/* Initialization mode */
#define EK_MODE 0
#define USER_DEFINED_CRYSTAL 1
#define BYASS_MODE 2

/*----------------------------------------------------------------------------
 *        Local structures
 *----------------------------------------------------------------------------*/
/** 
 * \brief Structure for storing parameters for each command that can be performed by the applet.
 */
struct _Mailbox {

    /* Command send to the monitor to be executed. */
    uint32_t command;
    /* Returned status, updated at the end of the monitor execution. */
    uint32_t status;

    /* Input Arguments in the argument area */
    union {

        /* Input arguments for the Init command. */
        struct {

            /* Communication link used. */
            uint32_t comType;
            /* Trace level. */
            uint32_t traceLevel;
            /* Low initialization mode */
            uint32_t mode;
            /* frequency of user-defined crystal */
            uint32_t crystalFreq;
            /* frequency of external clock in bypass mode */
            uint32_t extClk;

        } inputInit;

        /* Output arguments for the Init command. */
        /* None */

        /* Input arguments for the Write command. */
        /* None */

        /* Output arguments for the Write command. */
        /* None */

        /* Input arguments for the Read command. */
        /* None */

        /* Output arguments for the Read command. */
        /* None */

        /* Input arguments for the Full Erase command.*/
        /* NONE */

        /* Output arguments for the Full Erase command. */
        /* NONE */

        /* Input arguments for the Buffer Erase command.*/
        /* None */

        /* Output arguments for the Buffer Erase command. */
        /* NONE */
    } argument;
};

/* Startup time of main oscillator (in number of slow clock ticks).*/
#define USER_OSCOUNT(a)           ((a) << 8) 
/* USB PLL divisor value to obtain a 48MHz clock. */
#define USER_USBDIV(a)            ((a) << 28)  
/* PLL frequency range. */
#define USER_CKGR_PLL(a)          ((a) << 14) 
/* PLL startup time (in number of slow clock ticks).  */
#define USER_PLLCOUNT(a)          ((a) << 8) 
/* PLL MUL value.  */
#define USER_MUL(a)               ((a) << 16)
/* PLL DIV value.   */
#define USER_DIV(a)               (a)
/* Master clock prescaler value.  */
#define USER_PRESCALER(a)         ((a) << 4)
/* PLLA divisor by 2   */
#define USER_PLLADIV2(a)          ((a) << 12)
/* Master clock division   */
#define USER_MDIV(a)              ((a) << 8)
/* Define clock timeout  */
#define CLOCK_TIMEOUT             0xFFFFFFFF

/**
 * \brief  Configure the PMC if the frequency of the external oscillator is different from the one mounted on EK
 * \param crystalFreq  The frequency of the external oscillator
 */
static void user_defined_LowlevelInit (uint32_t crystalFreq)
{
    uint8_t i;
    volatile uint32_t read = 0;
    uint32_t oscount, range, mul, div, pllcount, prescaler, plladiv2, mdiv, _dwTimeout = 0;

    switch (crystalFreq) {
    /* When the crystal frequency is 12MHz */
    case 12000000:
        /* PLLA Clock = crystalFreq * (mul + 1) / div = 12MHz * (199 + 1) / 3 = 800MHz */
        mul = USER_MUL(199);
        div = USER_DIV(3);
        /* Processor Clock = PLLA Clock / PLLA_DIV2 / prescaler = 800MHz / 2 / 1 = 400MHz */
        plladiv2 = USER_PLLADIV2(1);
        prescaler = USER_PRESCALER(0);
        /* DDR clock = Processor Clock / MDIV / PLLADIV = 800MHz / 3 / 2 = 133MHz */
        mdiv = USER_MDIV(3);
        /* Please refer to Power Management Controller of the product datasheet */
        range = USER_CKGR_PLL(0);
        pllcount = USER_PLLCOUNT(63);
        oscount = USER_OSCOUNT(64);
        break;

    /* other master clock configurations */
    
    default:
        break;
    }
    
    if ((uint32_t)LowLevelInit < EBI_CS0_ADDR) /* Code in internal SRAM */
    {
        /* Switch to MAIN clock + prescaler */
        read = PMC->PMC_MCKR;
        read &= ~(PMC_MCKR_CSS_Msk);
        read |= PMC_MCKR_CSS_MAIN_CLK;
        PMC->PMC_MCKR = read;
        while (!(PMC->PMC_SR & PMC_SR_MCKRDY));
        
        PMC->CKGR_MOR = CKGR_MOR_KEY(0x37) | oscount | CKGR_MOR_MOSCRCEN | CKGR_MOR_MOSCXTEN | CKGR_MOR_MOSCSEL;
        _dwTimeout = 0;
        while (!(PMC->PMC_SR & PMC_SR_MOSCXTS) && (_dwTimeout++ < CLOCK_TIMEOUT));
        
        PMC->CKGR_PLLAR = 0;

        /* Initialize PLLA */
        PMC->CKGR_PLLAR = CKGR_PLLAR_STUCKTO1 | mul | range | pllcount | div;
        _dwTimeout = 0;
        while (!(PMC->PMC_SR & PMC_SR_LOCKA) && (_dwTimeout++ < CLOCK_TIMEOUT));
        
        /* Wait for the master clock if it was already initialized */
        for ( _dwTimeout =  0; !(PMC->PMC_SR & PMC_SR_MCKRDY) && (_dwTimeout++ < CLOCK_TIMEOUT) ; );

        /* Switch to fast clock
        **********************/
        /* Switch to main oscillator + prescaler */
        read = PMC->PMC_MCKR;
        read &= ~(PMC_MCKR_MDIV_Msk);
        
        read |= mdiv | plladiv2;
        PMC->PMC_MCKR = read;
       
        /* Wait for the master clock if it was already initialized */
        for ( _dwTimeout =  0; !(PMC->PMC_SR & PMC_SR_MCKRDY) && (_dwTimeout++ < CLOCK_TIMEOUT) ; );
      
        /* Switch to main oscillator + prescaler */
        read = PMC->PMC_MCKR;
        read &= ~(PMC_MCKR_PRES_Msk);
        read |= prescaler;
        PMC->PMC_MCKR = read;

        /* Wait for the master clock if it was already initialized */
        for(_dwTimeout = 0; !(PMC->PMC_SR & PMC_SR_MCKRDY) && (_dwTimeout++ < CLOCK_TIMEOUT); );

        /* Switch to PLL + prescaler */
        read = PMC->PMC_MCKR;
        read &= ~(PMC_MCKR_CSS_Msk);
        read |= PMC_MCKR_CSS_PLLA_CLK;
        PMC->PMC_MCKR = read;

        /* Wait for the master clock if it was already initialized */
        for( _dwTimeout = 0; !(PMC->PMC_SR & PMC_SR_MCKRDY) && (_dwTimeout++ < CLOCK_TIMEOUT); );
    } 

    /* Initialize AIC */
    AIC->AIC_IDCR = 0xFFFFFFFF;
    AIC->AIC_SVR[0] = 0;

    for (i = 1; i < 31; i++) {
        AIC->AIC_SVR[i] = 0;
    }
    AIC->AIC_SPU = 0;

    /* Unstack nested interrupts */
    for (i = 0; i < 8 ; i++) {

        AIC->AIC_EOICR = 0;
    }
    /* Remap */
     BOARD_RemapRam();

}

/**
 * \brief  Configure the PMC in bypass mode. An external clock should be input to XIN as the source clock.
 *
 * \param extClk  The frequency of the external clock
 */
static void bypass_LowLevelInit (uint32_t extClk)
{
    uint8_t i;
    volatile uint32_t read = 0;
    uint32_t oscount, range, mul, div, pllcount, prescaler, plladiv2, mdiv, _dwTimeout = 0;

    switch (extClk) {
    /* When external clock frequency is 12MHz */
    case 12000000:
        /* PLLA Clock = extClk * (mul + 1) / div = 12MHz * (199 + 1) / 3 = 800MHz */
        mul = USER_MUL(199);
        div = USER_DIV(3);
        /* Processor Clock = PLLA Clock / PLLA_DIV2 / prescaler = 800MHz / 2 / 1 = 400MHz */
        plladiv2 = USER_PLLADIV2(1);
        prescaler = USER_PRESCALER(0);
        /* DDR clock = Processor Clock / MDIV / PLLADIV = 800MHz / 3 / 2 = 133MHz */
        mdiv = USER_MDIV(3);
        /* Please refer to Power Management Controller of the product datasheet */
        range = USER_CKGR_PLL(0);
        pllcount = USER_PLLCOUNT(63);
        oscount = USER_OSCOUNT(64);
        break;

    
    /* other master clock configurations */
    
    default:
        break;
    }
    
    if ((uint32_t)LowLevelInit < EBI_CS0_ADDR) /* Code in internal SRAM */
    {
        /* Switch to MAIN clock + prescaler */
        read = PMC->PMC_MCKR;
        read &= ~(PMC_MCKR_CSS_Msk);
        read |= PMC_MCKR_CSS_MAIN_CLK;
        PMC->PMC_MCKR = read;
        while (!(PMC->PMC_SR & PMC_SR_MCKRDY));
        
        PMC->CKGR_MOR = CKGR_MOR_KEY(0x37) | oscount | CKGR_MOR_MOSCRCEN | CKGR_MOR_MOSCXTBY;
        PMC->CKGR_MOR |= CKGR_MOR_KEY(0x37) | CKGR_MOR_MOSCSEL;
        _dwTimeout = 0;
        while (!(PMC->PMC_SR & PMC_SR_MOSCXTS) && (_dwTimeout++ < CLOCK_TIMEOUT));
        
        PMC->CKGR_PLLAR = 0;

        /* Initialize PLLA */
        PMC->CKGR_PLLAR = CKGR_PLLAR_STUCKTO1 | mul | range | pllcount | div;
        _dwTimeout = 0;
        while (!(PMC->PMC_SR & PMC_SR_LOCKA) && (_dwTimeout++ < CLOCK_TIMEOUT));
        
        /* Wait for the master clock if it was already initialized */
        for ( _dwTimeout =  0; !(PMC->PMC_SR & PMC_SR_MCKRDY) && (_dwTimeout++ < CLOCK_TIMEOUT) ; );

        /* Switch to fast clock
        **********************/
        /* Switch to main oscillator + prescaler */
        read = PMC->PMC_MCKR;
        read &= ~(PMC_MCKR_MDIV_Msk);
        
        read |= mdiv | plladiv2;
        PMC->PMC_MCKR = read;
       
        /* Wait for the master clock if it was already initialized */
        for ( _dwTimeout =  0; !(PMC->PMC_SR & PMC_SR_MCKRDY) && (_dwTimeout++ < CLOCK_TIMEOUT) ; );
      
        /* Switch to main oscillator + prescaler */
        read = PMC->PMC_MCKR;
        read &= ~(PMC_MCKR_PRES_Msk);
        read |= prescaler;
        PMC->PMC_MCKR = read;

        /* Wait for the master clock if it was already initialized */
        for(_dwTimeout = 0; !(PMC->PMC_SR & PMC_SR_MCKRDY) && (_dwTimeout++ < CLOCK_TIMEOUT); );

        /* Switch to PLL + prescaler */
        read = PMC->PMC_MCKR;
        read &= ~(PMC_MCKR_CSS_Msk);
        read |= PMC_MCKR_CSS_PLLA_CLK;
        PMC->PMC_MCKR = read;

        /* Wait for the master clock if it was already initialized */
        for( _dwTimeout = 0; !(PMC->PMC_SR & PMC_SR_MCKRDY) && (_dwTimeout++ < CLOCK_TIMEOUT); );
    } 

    /* Initialize AIC */
    AIC->AIC_IDCR = 0xFFFFFFFF;
    AIC->AIC_SVR[0] = 0;

    for (i = 1; i < 31; i++) {
        AIC->AIC_SVR[i] = 0;
    }
    AIC->AIC_SPU = 0;

    /* Unstack nested interrupts */
    for (i = 0; i < 8 ; i++) {

        AIC->AIC_EOICR = 0;
    }
    /* Remap */
     BOARD_RemapRam();

}

static void EK_LowLevelInit (void)
{
    LowLevelInit();
}
/*----------------------------------------------------------------------------
 *         Global functions
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
    uint32_t mode, crystalFreq, extClk;
    uint32_t comType = pMailbox->argument.inputInit.comType;

    /* ---------------------------------------------------------- */
    /* INIT:                                                      */
    /* ---------------------------------------------------------- */
    if (pMailbox->command == APPLET_CMD_INIT) {

        mode = pMailbox->argument.inputInit.mode;
        crystalFreq = pMailbox->argument.inputInit.crystalFreq;
        extClk = pMailbox->argument.inputInit.extClk;

        switch (mode) {
        case EK_MODE: 
            EK_LowLevelInit();
            pMailbox->status = APPLET_SUCCESS;
            break;
        case USER_DEFINED_CRYSTAL:
            user_defined_LowlevelInit(crystalFreq);
            pMailbox->status = APPLET_SUCCESS;
            break;
        case BYASS_MODE:
            bypass_LowLevelInit(extClk);
            pMailbox->status = APPLET_SUCCESS;
            break;
        default:
            pMailbox->status = APPLET_DEV_UNKNOWN;
            break;
        }
    } else {
        pMailbox->status = APPLET_DEV_UNKNOWN;
    }

    /* Configure mode register */
    DBGU->DBGU_MR = DBGU_MR_CHMODE_NORM | DBGU_MR_PAR_NONE | US_MR_CHRL_8_BIT;
    /* Reset and disable receiver & transmitter */
    DBGU->DBGU_CR = DBGU_CR_RSTRX | DBGU_CR_RSTTX;
    DBGU->DBGU_IDR = 0xFFFFFFFF;
    DBGU->DBGU_CR = DBGU_CR_RSTRX | DBGU_CR_RSTTX | DBGU_CR_RXDIS | DBGU_CR_TXDIS;
    /* Configure baudrate */
    DBGU->DBGU_BRGR = (BOARD_MCK / 115200) / 16;
    /* Enable receiver and transmitter */
    DBGU->DBGU_CR = DBGU_CR_RXEN | DBGU_CR_TXEN;

    /* Notify the host application of the end of the command processing */
    pMailbox->command = ~(pMailbox->command);
    // Send ACK character
    if (comType == DBGU_COM_TYPE) {
         /* Wait for the transmitter to be ready */
        while ( (DBGU->DBGU_SR & DBGU_SR_TXEMPTY) == 0 ) ;
        /* Send character */
         DBGU->DBGU_THR= 0x06 ;
        //DBGU_PutChar(0x6);
    }
    return 0;
}

