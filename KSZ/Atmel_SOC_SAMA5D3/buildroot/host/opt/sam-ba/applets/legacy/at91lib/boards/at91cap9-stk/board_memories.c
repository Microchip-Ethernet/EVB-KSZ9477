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

/*
    Title: Memories implementation
*/

//------------------------------------------------------------------------------
//         Headers
//------------------------------------------------------------------------------

#include <board.h>
#include <pio/pio.h>
#include "board_memories.h"
                       
/*
    Macros:
        READ - Reads a register value. Useful to add trace information to read
               accesses.
        WRITE - Writes data in a register. Useful to add trace information to
                write accesses.
*/
#define READ(peripheral, register)          (peripheral->register)
#define WRITE(peripheral, register, value)  (peripheral->register = value)

//------------------------------------------------------------------------------
//         Internal definitions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//         Internal functions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// Use in SDRAM and DDRAM configguration
//------------------------------------------------------------------------------
void sleep_time(unsigned int timeval)
{
    unsigned int i;
    for( i=0; i<timeval; i++);
}
//------------------------------------------------------------------------------
//         Exported functions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// Initialize Vdd EBI external memory
//------------------------------------------------------------------------------
void BOARD_ConfigureVddMemSel(unsigned char VddMemSel)
{
    AT91C_BASE_CCFG->CCFG_EBICSA &= ~AT91C_EBI_OSMODE;

    if(VddMemSel == VDDMEMSEL_3V3)
    {
        AT91C_BASE_CCFG->CCFG_EBICSA |= AT91C_EBI_OSALLN1;
        AT91C_BASE_CCFG->CCFG_EBICSA |= AT91C_EBI_OSALLN0;
    }
    else
    {
        AT91C_BASE_CCFG->CCFG_EBICSA &= ~AT91C_EBI_OSALLN1;
        AT91C_BASE_CCFG->CCFG_EBICSA |=  AT91C_EBI_OSALLN0;
    }
}

//------------------------------------------------------------------------------
/// Changes the mapping of the chip so that the remap area mirrors the
///   internal ROM or the EBI CS0.
//------------------------------------------------------------------------------
void BOARD_RemapRom()
{
    WRITE(AT91C_BASE_MATRIX, MATRIX_MRCR, 0);
}

//------------------------------------------------------------------------------
/// Changes the mapping of the chip so that the remap area mirrors the
///   internal RAM.
//------------------------------------------------------------------------------
void BOARD_RemapRam()
{
    WRITE(AT91C_BASE_MATRIX, MATRIX_MRCR, (AT91C_MATRIX_RCA926I | AT91C_MATRIX_RCA926D));
}

//------------------------------------------------------------------------------
/// Initialize and configure the SDRAM
//------------------------------------------------------------------------------
void BOARD_ConfigureSdram(unsigned char busWidth)
{
    static const Pin pinsSdram[] = {PINS_SDRAM};
    volatile unsigned int *pSdram = (unsigned int *) AT91C_EBI_SDRAM;
    unsigned short sdrc_dbw = 0;

    switch (busWidth) {
        case 16:
            sdrc_dbw = AT91C_B16MODE_16_BITS;
            break;

        case 32:
        default:
            sdrc_dbw = AT91C_B16MODE_32_BITS;
            break;

    }

    // Enable corresponding PIOs
    PIO_Configure(pinsSdram, 1);
    
    WRITE(AT91C_BASE_SDDRC, SDDRC_MDR , AT91C_MD_SDR_SDRAM 
                                        | sdrc_dbw);    // SDRAM type 3.3V
                                        
    WRITE(AT91C_BASE_SDDRC, SDDRC_CR  , AT91C_NC_DDR10_SDR9 
                                        | AT91C_NR_13 
                                        | AT91C_CAS_3);    // row = 13, column = 9 SDRAM CAS = 3
    
    WRITE(AT91C_BASE_SDDRC, SDDRC_LPR , 0x00000000);    // Low power register => Low-power is inhibited // No define

    sleep_time(50000);               // --------- WAIT ---------

    WRITE(AT91C_BASE_SDDRC, SDDRC_MR, AT91C_MODE_NOP_CMD);  // NOP command
    pSdram[0] = 0x00000000;          // Dummy read to access SDRAM : validate preceeding command
    
    WRITE(AT91C_BASE_SDDRC, SDDRC_MR, AT91C_MODE_NOP_CMD);  // NOP command
    pSdram[0] = 0x00000000;  // Dummy read to access SDRAM : validate preceeding command
    
    WRITE(AT91C_BASE_SDDRC, SDDRC_MR, AT91C_MODE_NOP_CMD);  // NOP command
    pSdram[0] = 0x00000000;  // Dummy read to access SDRAM : validate preceeding command

    WRITE(AT91C_BASE_SDDRC, SDDRC_MR, AT91C_MODE_PRCGALL_CMD);  // Precharge All Banks command
    pSdram[0] = 0x00000000;  // Dummy read to access SDRAM : validate preceeding command

    sleep_time(50000);               // --------- WAIT ---------

    WRITE(AT91C_BASE_SDDRC, SDDRC_MR, AT91C_MODE_RFSH_CMD);  // AutoRefresh command
    pSdram[0] = 0x00000000;  // Dummy read to access SDRAM : validate preceeding command
       
    sleep_time(50000);               // --------- WAIT ---------

    WRITE(AT91C_BASE_SDDRC, SDDRC_MR, AT91C_MODE_RFSH_CMD);  // AutoRefresh command
    pSdram[0] = 0x00000000;  // Dummy read to access SDRAM : validate preceeding command
    
    sleep_time(50000);               // --------- WAIT ---------

    WRITE(AT91C_BASE_SDDRC, SDDRC_MR, AT91C_MODE_LMR_CMD);  // Set MR JEDEC compliant : Load mode Register command
    pSdram[19] = 0x5a5a5b5b;    // Perform LMR burst=1, lat=2

    WRITE(AT91C_BASE_SDDRC, SDDRC_MR, AT91C_MODE_NORMAL_CMD);  // Set Normal mode : Any access to the DDRSDRAMC is decoded normally
    pSdram[0] = 0x00000000;  // Dummy read to access SDRAM : validate preceeding command 

    WRITE(AT91C_BASE_SDDRC, SDDRC_RTR, 781);         // Set Refresh Timer (ex: ((64 x 10^-3)/8192) x 100 x 10^6 ) => 781 for 100 MHz
                                     
    WRITE(AT91C_BASE_SDDRC, SDDRC_HS, AT91C_OVL);        // High speed register : Optimization is disabled
       
    sleep_time(50000);               // --------- WAIT ---------
}


//------------------------------------------------------------------------------
/// Initialize and configure the DDRAM
//------------------------------------------------------------------------------
void BOARD_ConfigureDdram(
    unsigned char ddrModel,
    unsigned char busWidth
    )
{
   
}

//------------------------------------------------------------------------------
/// Configures the EBI for NandFlash access at 100MHz.
/// \Param busWidth Bus width 
//------------------------------------------------------------------------------
void BOARD_ConfigureNandFlash(unsigned char busWidth)
{
    // Configure EBI
    AT91C_BASE_CCFG->CCFG_EBICSA |= AT91C_EBI_CS3A_SM;

    // Configure SMC 
    
    // Configure SMC
    AT91C_BASE_SMC->SMC_SETUP3 = 0x00010001;
    AT91C_BASE_SMC->SMC_PULSE3 = 0x03030303;
    AT91C_BASE_SMC->SMC_CYCLE3 = 0x00050005;
    AT91C_BASE_SMC->SMC_CTRL3  = 0x00020003;
    
    if (busWidth == 8) {

        AT91C_BASE_SMC->SMC_CTRL3 |= AT91C_SMC_DBW_WIDTH_EIGTH_BITS;
    }
    else if (busWidth == 16) {
 
        AT91C_BASE_SMC->SMC_CTRL3 |= AT91C_SMC_DBW_WIDTH_SIXTEEN_BITS;
    }
    else if (busWidth == 32) {
 
        AT91C_BASE_SMC->SMC_CTRL3 |= AT91C_SMC_DBW_WIDTH_THIRTY_TWO_BITS;
    }
}

//------------------------------------------------------------------------------
/// Configures the EBI for NandFlash access at 48MHz.
/// \Param busWidth Bus width 
//------------------------------------------------------------------------------
void BOARD_ConfigureNandFlash48MHz(unsigned char busWidth)
{
    // Configure EBI
    AT91C_BASE_CCFG->CCFG_EBICSA |= AT91C_EBI_CS3A_SM;

    // Configure SMC 
    AT91C_BASE_SMC->SMC_SETUP3 = 0x00010001;
    AT91C_BASE_SMC->SMC_PULSE3 = 0x04030302;
    AT91C_BASE_SMC->SMC_CYCLE3 = 0x00070004;
    AT91C_BASE_SMC->SMC_CTRL3  = (AT91C_SMC_READMODE
                                  | AT91C_SMC_WRITEMODE
                                  | AT91C_SMC_NWAITM_NWAIT_DISABLE
                                  | ((0x1 << 16) & AT91C_SMC_TDF));
                           
    if (busWidth == 8) {

        AT91C_BASE_SMC->SMC_CTRL3 |= AT91C_SMC_DBW_WIDTH_EIGTH_BITS;
    }
    else if (busWidth == 16) {
 
        AT91C_BASE_SMC->SMC_CTRL3 |= AT91C_SMC_DBW_WIDTH_SIXTEEN_BITS;
    }
    else if (busWidth == 32) {
 
        AT91C_BASE_SMC->SMC_CTRL3 |= AT91C_SMC_DBW_WIDTH_THIRTY_TWO_BITS;
    }
}

