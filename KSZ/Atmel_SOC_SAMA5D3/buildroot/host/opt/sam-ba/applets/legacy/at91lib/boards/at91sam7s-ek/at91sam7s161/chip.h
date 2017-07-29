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
/// \unit
/// !Purpose
///
/// Definition of AT91SAM7S161 characteristics and features
///
/// !Usage
/// -# For ARM core feature, see "AT91SAM7S161 - ARM core features".
/// -# For IP features, see "AT91SAM7S16 - IP features".
/// -# For misc, see "AT91SAM7S16 - Misc".
//------------------------------------------------------------------------------
 
#ifndef CHIP_H 
#define CHIP_H

//------------------------------------------------------------------------------
//         Headers
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//         Definitions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \page "AT91SAM7S16 - ARM core features"
/// This page lists several characteristics related to the ARM core
///

//ARM core features

/// ARM core definition.
#define arm7tdmi

/// family definition.
#define at91sam7s

//------------------------------------------------------------------------------
/// \page "AT91SAM7S16 - IP features"
/// This page lists several characteristics related to the embedded IP
///

//IP FEATURES

// EFC GPNVM number
#define CHIP_EFC_NUM_GPNVMS    2

/// Indicates chip has an EFC. 
#define CHIP_FLASH_EFC 

/// Address of the IAP function in ROM.
#define CHIP_FLASH_IAP_ADDRESS         0x300E08 

//------------------------------------------------------------------------------
/// \page "AT91SAM7S16 - Misc "
/// This page lists misc features
///

//Misc 

#endif //#ifndef CHIP_H

