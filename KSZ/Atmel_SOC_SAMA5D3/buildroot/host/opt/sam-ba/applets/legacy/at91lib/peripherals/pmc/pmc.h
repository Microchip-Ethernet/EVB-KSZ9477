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

#ifndef PMC_H
#define PMC_H

//------------------------------------------------------------------------------
//         Type
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// Describes the PLL configuration.
//-----------------------------------------------------------------------------
typedef struct _pll {
    unsigned int mul;    /// PLL A Multiplier
    unsigned int div;    /// Divider 
    unsigned int usbdiv; ///  usb Divider
    unsigned int pllout; /// Specifies the number of slow clock cycles before the LOCKA bit is set in PMC_SR after CKGR_PLLAR is written
} pllConfiguration;


//-----------------------------------------------------------------------------
/// Describes the MCKR configuration.
//-----------------------------------------------------------------------------
typedef struct _mck {

    unsigned int prescaler;  /// Master/Processor Clock Prescaler
    unsigned int mdiv;       /// Master Clock Division
    unsigned int plldiv2;    /// PLLA divisor by 2
    unsigned int rev;
} mckrConfiguration;

//------------------------------------------------------------------------------
//         Global functions
//------------------------------------------------------------------------------

extern void PMC_DisableProcessorClock(void);
extern void PMC_EnablePeripheral(unsigned int id);
extern void PMC_DisablePeripheral(unsigned int id);

extern void PMC_EnableAllPeripherals(void);
extern void PMC_DisableAllPeripherals(void);
extern unsigned int PMC_IsAllPeriphEnabled(void);
extern unsigned int PMC_IsPeriphEnabled(unsigned int id);

extern void PMC_SwitchMck2SlowClock(void);
extern void PMC_SetMckSelection(unsigned int clockSource, mckrConfiguration *mckr);
extern void PMC_EnableMainOsc(void);
extern void PMC_SetPllClockPMC_SetPllClock(pllConfiguration *pll);
extern void PMC_ConfigureMckWithPlla(pllConfiguration *pll, mckrConfiguration *mckr);
extern void PMC_BypassMainOsc(void);

#endif //#ifndef PMC_H

