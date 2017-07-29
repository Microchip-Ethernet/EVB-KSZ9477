/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support 
 * ----------------------------------------------------------------------------
 * Copyright (c) 2009, Atmel Corporation
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

/*
    Title: Memories implementation
*/

//------------------------------------------------------------------------------
//         Headers
//------------------------------------------------------------------------------

#include <board.h>
#include <pio/pio.h>

//------------------------------------------------------------------------------
//         Exported functions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// Configures the EBI for NandFlash access. Pins must be configured after or
/// before calling this function.
//------------------------------------------------------------------------------
void BOARD_ConfigureNandFlash(unsigned char busWidth)
{
#if defined(CHIP_NAND_CTRL)
    AT91PS_HSMC4 pHSMC4 = AT91C_BASE_HSMC4;    
#endif
    AT91PS_HSMC4_CS pSMC = AT91C_BASE_HSMC4_CS1;

    // Open EBI clock
    AT91C_BASE_PMC->PMC_PCER = (1<< AT91C_ID_HSMC4);
 
#if defined(CHIP_NAND_CTRL)
    // Enable the Nand Flash Controller
    pHSMC4 ->HSMC4_CTRL = AT91C_HSMC4_NFCEN;
#endif
    
    pSMC->HSMC4_SETUP = 0
                    | ((0 <<  0) & AT91C_HSMC4_NWE_SETUP)
                    | ((1 <<  8) & AT91C_HSMC4_NCS_WR_SETUP)
                    | ((0 << 16) & AT91C_HSMC4_NRD_SETUP)
                    | ((1 << 24) & AT91C_HSMC4_NCS_RD_SETUP);

    pSMC->HSMC4_PULSE = 0
                    | ((2 <<  0) & AT91C_HSMC4_NWE_PULSE)
                    | ((3 <<  8) & AT91C_HSMC4_NCS_WR_PULSE)
                    | ((3 << 16) & AT91C_HSMC4_NRD_PULSE)
                    | ((4 << 24) & AT91C_HSMC4_NCS_RD_PULSE);

    pSMC->HSMC4_CYCLE = 0
                  | ((4 <<  0) & AT91C_HSMC4_NWE_CYCLE)
                  | ((7 << 16) & AT91C_HSMC4_NRD_CYCLE);

    pSMC->HSMC4_TIMINGS = 0
                    | ((1 <<  0) & AT91C_HSMC4_TCLR) // CLE to REN
                    | ((2 <<  4) & AT91C_HSMC4_TADL) // ALE to Data
                    | ((1 <<  8) & AT91C_HSMC4_TAR)  // ALE to REN
                    | ((1 << 16) & AT91C_HSMC4_TRR)  // Ready to REN
                    | ((2 << 24) & AT91C_HSMC4_TWB)  // WEN to REN
                    | (7<<28)
                    |(AT91C_HSMC4_NFSEL)              // Nand Flash Timing
                    ;
    
        
    if (busWidth == 8) {
        pSMC->HSMC4_MODE = AT91C_HSMC4_DBW_WIDTH_EIGTH_BITS | AT91C_HSMC4_READ_MODE | AT91C_HSMC4_WRITE_MODE;
    }
    else if (busWidth == 16) {
        pSMC->HSMC4_MODE = AT91C_HSMC4_DBW_WIDTH_SIXTEEN_BITS | AT91C_HSMC4_READ_MODE | AT91C_HSMC4_WRITE_MODE;
    }
}

//------------------------------------------------------------------------------
/// Function to initialize and configure the PSRAM
//------------------------------------------------------------------------------
void BOARD_ConfigurePsram(void) 
{
    const Pin pinPsram[] = {BOARD_PSRAM_PINS};
    unsigned int tmp;

    // Open EBI clock
    AT91C_BASE_PMC->PMC_PCER = (1<< AT91C_ID_HSMC4);

    // Configure I/O
    PIO_Configure(pinPsram, PIO_LISTSIZE(pinPsram));

    // Setup the PSRAM (HSMC4_EBI.CS0, 0x60000000 ~ 0x60FFFFFF)
    #if 0
    AT91C_BASE_HSMC4_CS0->HSMC4_SETUP = 0
                        | ((1 <<  0) & AT91C_HSMC4_NWE_SETUP)
                        | ((1 <<  8) & AT91C_HSMC4_NCS_WR_SETUP)
                        | ((1 << 16) & AT91C_HSMC4_NRD_SETUP)
                        | ((1 << 24) & AT91C_HSMC4_NCS_RD_SETUP)
                        ;
    AT91C_BASE_HSMC4_CS0->HSMC4_PULSE = 0
                        | ((7 <<  0) & AT91C_HSMC4_NWE_PULSE)
                        | ((7 <<  8) & AT91C_HSMC4_NCS_WR_PULSE)
                        | ((7 << 16) & AT91C_HSMC4_NRD_PULSE)
                        | ((7 << 24) & AT91C_HSMC4_NCS_RD_PULSE)
                        ;
    AT91C_BASE_HSMC4_CS0->HSMC4_CYCLE = 0
                        | ((8 <<  0) & AT91C_HSMC4_NWE_CYCLE)
                        | ((8 << 16) & AT91C_HSMC4_NRD_CYCLE)
                        ;
    #else
    AT91C_BASE_HSMC4_CS0->HSMC4_SETUP = 0
                        | ((0 <<  0) & AT91C_HSMC4_NWE_SETUP)
                        | ((2 <<  8) & AT91C_HSMC4_NCS_WR_SETUP)
                        | ((2 << 16) & AT91C_HSMC4_NRD_SETUP)
                        | ((2 << 24) & AT91C_HSMC4_NCS_RD_SETUP)
                        ;
    AT91C_BASE_HSMC4_CS0->HSMC4_PULSE = 0
                        | ((6 <<  0) & AT91C_HSMC4_NWE_PULSE)
                        | ((6 <<  8) & AT91C_HSMC4_NCS_WR_PULSE)
                        | ((6 << 16) & AT91C_HSMC4_NRD_PULSE)
                        | ((6 << 24) & AT91C_HSMC4_NCS_RD_PULSE)
                        ;
    AT91C_BASE_HSMC4_CS0->HSMC4_CYCLE = 0
                        | ((8 <<  0) & AT91C_HSMC4_NWE_CYCLE)
                        | ((8 << 16) & AT91C_HSMC4_NRD_CYCLE)
                        ;
    #endif

    tmp = AT91C_BASE_HSMC4_CS0->HSMC4_TIMINGS
        & (AT91C_HSMC4_OCMSEN | AT91C_HSMC4_RBNSEL | AT91C_HSMC4_NFSEL);
    AT91C_BASE_HSMC4_CS0->HSMC4_TIMINGS = tmp
                        | ((0 <<  0) & AT91C_HSMC4_TCLR) // CLE to REN
                        | ((0 <<  4) & AT91C_HSMC4_TADL) // ALE to Data
                        | ((0 <<  8) & AT91C_HSMC4_TAR)  // ALE to REN
                        | ((0 << 16) & AT91C_HSMC4_TRR)  // Ready to REN
                        | ((0 << 24) & AT91C_HSMC4_TWB)  // WEN to REN
                        ;
    tmp = AT91C_BASE_HSMC4_CS0->HSMC4_MODE & ~(AT91C_HSMC4_DBW);
    AT91C_BASE_HSMC4_CS0->HSMC4_MODE = tmp
                        | (AT91C_HSMC4_READ_MODE)
                        | (AT91C_HSMC4_WRITE_MODE)
                        | (AT91C_HSMC4_DBW_WIDTH_SIXTEEN_BITS)
                        //| (AT91C_HSMC4_PMEN)
                        ;
}

