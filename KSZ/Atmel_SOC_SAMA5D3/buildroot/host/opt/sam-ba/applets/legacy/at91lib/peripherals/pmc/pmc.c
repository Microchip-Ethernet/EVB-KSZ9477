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

//------------------------------------------------------------------------------
//         Headers
//------------------------------------------------------------------------------

#include <board.h>
#include <pmc/pmc.h>
#include <utility/assert.h>
#include <utility/trace.h>

#define MASK_STATUS 0x3FFFFFFC
#define AT91C_CKGR_SRC01      (1<<29)

//------------------------------------------------------------------------------
//         Local functions
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
/// Set prescaler for MCK.
/// \param prescaler Master Clock prescaler
//------------------------------------------------------------------------------
static void _PMC_SetMckPrescaler(unsigned int prescaler)
{
    unsigned int mckr;
    mckr = AT91C_BASE_PMC->PMC_MCKR;
    AT91C_BASE_PMC->PMC_MCKR = mckr & (mckr & ~AT91C_PMC_PRES);
    // Change MCK Prescaler divider in PMC_MCKR register 
    AT91C_BASE_PMC->PMC_MCKR |= prescaler;

    // Wait until the master clock is established 
    while( !(AT91C_BASE_PMC->PMC_SR & AT91C_PMC_MCKRDY) );
}

static void _PMC_SetPllDiv2(unsigned int div2) 
{
  
#if defined (AT91C_PMC_MCKR_PLLADIV2)
    if (div2 != 0) {
        AT91C_BASE_PMC->PMC_MCKR |= AT91C_PMC_MCKR_PLLADIV2;
    } else {
        AT91C_BASE_PMC->PMC_MCKR = AT91C_BASE_PMC->PMC_MCKR & (~AT91C_PMC_MCKR_PLLADIV2);
    }
#endif
#if defined (AT91C_PMC_PDIV_2)
    if (div2 != 0) {
        AT91C_BASE_PMC->PMC_MCKR |= AT91C_PMC_PDIV_2;
    } else {
        AT91C_BASE_PMC->PMC_MCKR = AT91C_BASE_PMC->PMC_MCKR & (~AT91C_PMC_PDIV_2);
    }
#endif
    
#if defined (AT91C_PMC_PLLADIV2)
    if (div2 != 0) {
        AT91C_BASE_PMC->PMC_MCKR |= AT91C_PMC_PLLADIV2;
    } else {
        AT91C_BASE_PMC->PMC_MCKR = AT91C_BASE_PMC->PMC_MCKR & (~AT91C_PMC_PLLADIV2);
    }
#endif

}

//------------------------------------------------------------------------------
/// Switch MCK to main clock.
//------------------------------------------------------------------------------
static void _PMC_SwitchMck2MainClock()
{
    // Select Main Oscillator as input clock for MCK 
    AT91C_BASE_PMC->PMC_MCKR = (AT91C_BASE_PMC->PMC_MCKR & ~AT91C_PMC_CSS) | AT91C_PMC_CSS_MAIN_CLK ;

    // Wait until the master clock is established 
    while( !(AT91C_BASE_PMC->PMC_SR & AT91C_PMC_MCKRDY) );
}

//------------------------------------------------------------------------------
/// Switch MCK to PLLA clock.
//------------------------------------------------------------------------------
static void _PMC_SwitchMck2PllaClock(mckrConfiguration *mckr)
{
    unsigned int prescaler;
    prescaler = AT91C_BASE_PMC->PMC_MCKR & AT91C_PMC_PRES;
#if defined AT91C_PMC_MDIV
    AT91C_BASE_PMC->PMC_MCKR = (AT91C_BASE_PMC->PMC_MCKR & ~ AT91C_PMC_MDIV) | mckr->mdiv;
#endif
    // Select PLLA as input clock for MCK 
#if defined ( AT91C_PMC_CSS_PLLA_CLK)
    AT91C_BASE_PMC->PMC_MCKR = (AT91C_BASE_PMC->PMC_MCKR & ~AT91C_PMC_CSS)|  AT91C_PMC_CSS_PLLA_CLK | prescaler;
#endif

#if defined ( AT91C_PMC_CSS_PLL_CLK)
    AT91C_BASE_PMC->PMC_MCKR = (AT91C_BASE_PMC->PMC_MCKR & ~AT91C_PMC_CSS)| AT91C_PMC_CSS_PLL_CLK| prescaler;
#endif
    // Wait until the master clock is established 
    while( !(AT91C_BASE_PMC->PMC_SR & AT91C_PMC_MCKRDY) );
}

//------------------------------------------------------------------------------
//         Global functions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// Disables the processor clock
//------------------------------------------------------------------------------
void PMC_DisableProcessorClock(void)
{    
    AT91C_BASE_PMC->PMC_SCDR = AT91C_PMC_PCK;   
    while ((AT91C_BASE_PMC->PMC_SCSR & AT91C_PMC_PCK) != AT91C_PMC_PCK); 
}

//------------------------------------------------------------------------------
/// Enables the clock of a peripheral. The peripheral ID (AT91C_ID_xxx) is used
/// to identify which peripheral is targetted.
/// Note that the ID must NOT be shifted (i.e. 1 << AT91C_ID_xxx).
/// \param id  Peripheral ID (AT91C_ID_xxx).
//------------------------------------------------------------------------------
void PMC_EnablePeripheral(unsigned int id)
{
    SANITY_CHECK(id < 32);

    if ((AT91C_BASE_PMC->PMC_PCSR & (1 << id)) == (1 << id)) {

        TRACE_INFO("PMC_EnablePeripheral: clock of peripheral"
                   " %u is already enabled\n\r",
                   id);
    }
    else {

        AT91C_BASE_PMC->PMC_PCER = 1 << id;
    }
}

//------------------------------------------------------------------------------
/// Disables the clock of a peripheral. The peripheral ID (AT91C_ID_xxx) is used
/// to identify which peripheral is targetted.
/// Note that the ID must NOT be shifted (i.e. 1 << AT91C_ID_xxx).
/// \param id  Peripheral ID (AT91C_ID_xxx).
//------------------------------------------------------------------------------
void PMC_DisablePeripheral(unsigned int id)
{
    SANITY_CHECK(id < 32);

    if ((AT91C_BASE_PMC->PMC_PCSR & (1 << id)) != (1 << id)) {

        TRACE_INFO("PMC_DisablePeripheral: clock of peripheral"
                   " %u is not enabled\n\r",
                   id);
    }
    else {

        AT91C_BASE_PMC->PMC_PCDR = 1 << id;
    }
}

//------------------------------------------------------------------------------
/// Enable all the periph clock via PMC
/// (Becareful of the last 2 bits, it is not periph clock)
//------------------------------------------------------------------------------
void PMC_EnableAllPeripherals(void)
{
    AT91C_BASE_PMC->PMC_PCER = MASK_STATUS;
    while( (AT91C_BASE_PMC->PMC_PCSR & MASK_STATUS) != MASK_STATUS);
    TRACE_INFO("Enable all periph clocks\n\r"); 
}

//------------------------------------------------------------------------------
/// Disable all the periph clock via PMC
/// (Becareful of the last 2 bits, it is not periph clock)
//------------------------------------------------------------------------------
void PMC_DisableAllPeripherals(void)
{
    AT91C_BASE_PMC->PMC_PCDR = MASK_STATUS;
    while((AT91C_BASE_PMC->PMC_PCSR & MASK_STATUS) != 0);
    TRACE_INFO("Disable all periph clocks\n\r");
}

//-----------------------------------------------------------------------------
/// Get Periph Status
//-----------------------------------------------------------------------------
unsigned int PMC_IsAllPeriphEnabled(void)
{
    return (AT91C_BASE_PMC->PMC_PCSR == MASK_STATUS);
}

//-----------------------------------------------------------------------------
/// Get Periph Status
//-----------------------------------------------------------------------------
unsigned int PMC_IsPeriphEnabled(unsigned int id)
{
    return (AT91C_BASE_PMC->PMC_PCSR & (1 << id));
}

//------------------------------------------------------------------------------
/// Switch MCK to slow clock.
//------------------------------------------------------------------------------
void PMC_SwitchMck2SlowClock(void)
{
    // Select Slow Clock as input clock for MCK 
    AT91C_BASE_PMC->PMC_MCKR = AT91C_PMC_CSS_SLOW_CLK ;

    // Wait until the master clock is established 
    while( !(AT91C_BASE_PMC->PMC_SR & AT91C_PMC_MCKRDY) );
}

//------------------------------------------------------------------------------
/// Selection of Master Clock.
/// \param clockSource  Master Clock source.
/// \param mckr  MCKR configuration instance.
///
/// \note
/// The PMC_MCKR register must not be programmed in a single write
/// operation (see. Product Data Sheet).
//------------------------------------------------------------------------------
void PMC_SetMckSelection(unsigned int clockSource, mckrConfiguration *mckr)
{
    switch ( clockSource )
    {
        case AT91C_PMC_CSS_SLOW_CLK :
            PMC_SwitchMck2SlowClock();
            _PMC_SetMckPrescaler(mckr->prescaler);
            break;

        case AT91C_PMC_CSS_MAIN_CLK :
            _PMC_SwitchMck2MainClock();
            _PMC_SetMckPrescaler(mckr->prescaler);
            break;
#if defined ( AT91C_PMC_CSS_PLLA_CLK)
        case AT91C_PMC_CSS_PLLA_CLK :
            _PMC_SetMckPrescaler(mckr->prescaler);
            _PMC_SwitchMck2PllaClock(mckr);
            break ;
#endif
#if defined ( AT91C_PMC_CSS_PLL_CLK)
        case AT91C_PMC_CSS_PLL_CLK :
            _PMC_SetMckPrescaler(mckr->prescaler);
            _PMC_SwitchMck2PllaClock(mckr);
            break ;
#endif
    }
}

//------------------------------------------------------------------------------
/// Configure PLLA/PLL clock by giving MUL and DIV. Disable PLLA/PLL when 'mul' set to 0.
/// \param pll  PLL configuration instance.
//------------------------------------------------------------------------------
void PMC_SetPllClock(pllConfiguration *pll)
{
    unsigned int ckgr_src = 0;
    unsigned int ckgr_usbdiv = 0;
#if defined (AT91C_CKGR_SRCA) || defined (AT91C_CKGR_SRC)
    ckgr_src = AT91C_CKGR_SRC01;
    ckgr_usbdiv = 0;
#endif
#if defined  (AT91C_CKGR_USBDIV)
    ckgr_usbdiv = (AT91C_CKGR_USBDIV & ((pll->usbdiv) << 28));
#endif
    if (pll->mul != 0)
    {
#if defined ( AT91C_PMC_CSS_PLLA_CLK)
#if !defined (AT91C_CKGR_OUTA) 
    #define AT91C_CKGR_OUTA 0
#endif
        // Init PLLA speed 
        AT91C_BASE_PMC->PMC_PLLAR = ckgr_src |
                                    ckgr_usbdiv |
                                    AT91C_CKGR_PLLACOUNT  |
                                    (AT91C_CKGR_MULA & (((pll->mul) - 1) << 16))|
                                    (AT91C_CKGR_DIVA & (pll->div)) |
                                    (AT91C_CKGR_OUTA & ((pll->pllout) << 14));
#endif
#if defined ( AT91C_PMC_CSS_PLL_CLK)
#if !defined (AT91C_CKGR_OUT) 
    #define AT91C_CKGR_OUT 0
#endif

        // Init PLL speed 
        AT91C_BASE_PMC->PMC_PLLR = ckgr_src |
                                    ckgr_usbdiv |
                                    AT91C_CKGR_PLLCOUNT  |
                                   (AT91C_CKGR_MUL & (((pll->mul) - 1) << 16)) |
                                   (AT91C_CKGR_DIV & (pll->div)) |
                                   (AT91C_CKGR_OUT & ((pll->pllout) << 14));
#endif
#if defined ( AT91C_PMC_CSS_PLLA_CLK)
        // Wait for PLLA stabilization 
        while( !(AT91C_BASE_PMC->PMC_SR & AT91C_PMC_LOCKA) );
#endif
#if defined ( AT91C_PMC_CSS_PLL_CLK)
        // Wait for PLL stabilization 
        while( !(AT91C_BASE_PMC->PMC_SR & AT91C_PMC_LOCK) );
#endif
    }
#if defined ( AT91C_PMC_CSS_PLLA_CLK)
    else
    {
        AT91C_BASE_PMC->PMC_PLLAR = ckgr_src; /* disable PLL A */
    }
#endif
#if defined ( AT91C_PMC_CSS_PLL_CLK)
    else
    {
        AT91C_BASE_PMC->PMC_PLLR = ckgr_src; /* disable PLL  */
    }
#endif
}

//------------------------------------------------------------------------------
/// Configure Enable main oscilator as main clock input.
//------------------------------------------------------------------------------
void PMC_EnableMainOsc(void)
{
#if defined AT91C_CKGR_MOSCSEL
    AT91C_BASE_PMC->PMC_MOR = (0x37 << 16) | (AT91C_CKGR_MOSCXTST & (0x8 << 8)) | AT91C_CKGR_MOSCRCEN | AT91C_CKGR_MOSCXTEN | AT91C_CKGR_MOSCSEL;
    while (!(AT91C_BASE_PMC->PMC_SR & AT91C_PMC_MOSCSELS));
#endif
#if defined AT91C_CKGR_MOSCEN
    if ( !AT91C_BASE_PMC->PMC_MOR & AT91C_CKGR_MOSCEN) {
        AT91C_BASE_PMC->PMC_MOR = AT91C_CKGR_OSCOUNT | AT91C_CKGR_MOSCEN;
        while (!(AT91C_BASE_PMC->PMC_SR & AT91C_PMC_MOSCS));
    }
#endif
#if defined AT91C_SUPC_XTALSEL
    AT91C_BASE_SUPC->SUPC_CR = (0xA5 << 24) | AT91C_SUPC_XTALSEL;
    while ((AT91C_BASE_SUPC->SUPC_SR & AT91C_SUPC_OSCSEL) != AT91C_SUPC_OSCSEL);
#endif
}

//------------------------------------------------------------------------------
/// The Main Oscillator is bypassed
//------------------------------------------------------------------------------
void PMC_BypassMainOsc(void)
{
#if defined (AT91C_CKGR_OSCBYPASS)
    volatile unsigned int timeout;
    AT91C_BASE_PMC->PMC_MOR = AT91C_CKGR_OSCOUNT | AT91C_CKGR_OSCBYPASS;
    for(timeout = 0; timeout<0xffff;timeout++);
    while(!(AT91C_BASE_PMC->PMC_MCFR & AT91C_CKGR_MAINRDY));
#endif
}

//------------------------------------------------------------------------------
/// Configure Configure PLLA/PLL as clock input for MCK.
/// \param pll  PLL configuration instance.
/// \param mckr  MCKR configuration instance.
//------------------------------------------------------------------------------
extern void PMC_ConfigureMckWithPlla(pllConfiguration *pll, mckrConfiguration *mckr)
{
    // First, select Main OSC as input clock for MCK
    _PMC_SwitchMck2MainClock();
    _PMC_SetPllDiv2(mckr->plldiv2);
    // Then, Set PLLA/PLL clock 
    PMC_SetPllClock(pll);
    // Wait until the master clock is established for the case we already turn on the PLL.
    while( !(AT91C_BASE_PMC->PMC_SR & AT91C_PMC_MCKRDY) );
    // Finally, select PllA/PLL as input clock for MCK
#if defined ( AT91C_PMC_CSS_PLLA_CLK)
    PMC_SetMckSelection(AT91C_PMC_CSS_PLLA_CLK, mckr);
#endif
#if defined ( AT91C_PMC_CSS_PLL_CLK)
    PMC_SetMckSelection(AT91C_PMC_CSS_PLL_CLK, mckr);
#endif
}

