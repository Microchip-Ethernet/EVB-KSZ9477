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

#include "wdt.h"
#include <board.h>

//------------------------------------------------------------------------------
//         Global functions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// Set Mode
//------------------------------------------------------------------------------
void WDT_SetMode(AT91PS_WDTC pWDTC, unsigned int Mode)
{
    pWDTC->WDTC_WDMR = Mode;
}

//------------------------------------------------------------------------------
/// Restart
//------------------------------------------------------------------------------
void WDT_Restart(AT91PS_WDTC pWDTC)
{
    pWDTC->WDTC_WDCR = 0xA5000001;
}

//------------------------------------------------------------------------------
/// Get status
//------------------------------------------------------------------------------
unsigned int WDT_GetStatus(AT91PS_WDTC pWDTC)
{
    return(pWDTC->WDTC_WDSR & 0x3);
}

//------------------------------------------------------------------------------
/// Get period
//------------------------------------------------------------------------------
unsigned int WDT_GetPeriod(unsigned int ms)
{
    if ((ms < 4) || (ms > 16000)) {
        return 0;
    }
    return((ms << 8) / 1000);
}
