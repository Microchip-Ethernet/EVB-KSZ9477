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
/*
    Constants: Remap types
        BOARD_ROM - ROM or EBI CS0 is mirrored in the remap zone.
        BOARD_RAM - RAM is mirrored in the remap zone.
*/
#define BOARD_ROM               0
#define BOARD_RAM               1

//------------------------------------------------------------------------------
//         Internal functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/// Returns the current remap (see <Remap types>).
//------------------------------------------------------------------------------
/*static unsigned char BOARD_GetRemap()
{
    volatile unsigned int *remap = (volatile unsigned int *) 0;
    volatile unsigned int *ram = (volatile unsigned int *) AT91C_IRAM;
    // Try to write in 0 and see if this affects the RAM
    unsigned int temp = *ram;
    *ram = temp + 1;
    if (*remap == *ram) {

        *ram = temp;
        return BOARD_RAM;
    }
    else {

        *ram = temp;
        return BOARD_ROM;
    }
}*/

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
/// Initialize Vdd EBI external memory
//------------------------------------------------------------------------------
void BOARD_ConfigureVddMemSel(unsigned char VddMemSel)
{
    AT91C_BASE_CCFG->CCFG_EBICSA &= ~AT91C_EBI_OSMODE;

    if(VddMemSel == VDDMEMSEL_3V3)
    {
        AT91C_BASE_CCFG->CCFG_EBICSA |= AT91C_EBI_OSALLN1;
        AT91C_BASE_CCFG->CCFG_EBICSA &= ~AT91C_EBI_OSALLN0;
    }
    else
    {
        AT91C_BASE_CCFG->CCFG_EBICSA &= ~AT91C_EBI_OSALLN1;
        AT91C_BASE_CCFG->CCFG_EBICSA &= ~AT91C_EBI_OSALLN0;
    }
}


//------------------------------------------------------------------------------
/// Initialize and configure the SDRAM
//------------------------------------------------------------------------------
void BOARD_ConfigureSdram(unsigned char busWidth)
{
    // Micron MT48LC16M16A2
    unsigned int i;
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

    //-- 1st Step : Program the memory device type into Memory Device Register
    WRITE(AT91C_BASE_SDDRC, SDDRC_MDR , AT91C_MD_SDR_SDRAM
                                        | sdrc_dbw);    // SDRAM type 3.3V + 32bit MODE

    //-- 2nd Step : Program the SDR-SDRAM device into the Configuration Register 
    //--            (number of columns, rows, cas latency)
    //--            and into the Timing Register (asynchronous timing)
    WRITE(AT91C_BASE_SDDRC, SDDRC_CR  , AT91C_NC_DDR10_SDR9
                                        | AT91C_NR_13
                                        | AT91C_CAS_3);    // row = 13, column = 9 SDRAM CAS = 3

    WRITE(AT91C_BASE_SDDRC, SDDRC_T0PR, AT91C_TRAS_4
                                        | AT91C_TRCD_2
                                        | AT91C_TWR_2
                                        | AT91C_TRC_4
                                        | AT91C_TRP_3
                                        | AT91C_TRRD_3
                                        | AT91C_TWTR_1
                                        | AT91C_TMRD_6);

    //-- 3rd Step : this step is performed only with mobile SDRAM
  
    sleep_time(50000);               // --------- WAIT ---------

    //-- 4th Step : a NOP command is performed => allow to enable clk
    WRITE(AT91C_BASE_SDDRC, SDDRC_MR, AT91C_MODE_NOP_CMD);  // NOP command
    pSdram[0] = 0x00000000;          // Dummy read to access SDRAM : validate preceeding command

    //-- 5th Step : an All Bank Precharge command is issued to the SDR-SDRAM 
    WRITE(AT91C_BASE_SDDRC, SDDRC_MR, AT91C_MODE_PRCGALL_CMD);  // Precharge All Banks command
    pSdram[0] = 0x00000000;  // Dummy read to access SDRAM : validate preceeding command

    //-- 6th Step : eight auto refresh cycles are provided
    for(i=0;i<8;i++) {
        WRITE(AT91C_BASE_SDDRC, SDDRC_MR, AT91C_MODE_RFSH_CMD);  // AutoRefresh command
        pSdram[0] = 0x00000000;  // Dummy read to access SDRAM : validate preceeding command
    }

    //-- 7th Step : a Mode Register Set is issued to program the parameters of the SDR-SDRAM device 
    WRITE(AT91C_BASE_SDDRC, SDDRC_MR, AT91C_MODE_LMR_CMD);  // Set MR JEDEC compliant : Load mode Register command
    pSdram[8] = 0x00000000;    // Perform LMR burst=1, lat=2

    //-- 8th Step : this step is performed only with mobile SDRAM

    //-- 9th Step : Set Normal mode  
    WRITE(AT91C_BASE_SDDRC, SDDRC_MR, AT91C_MODE_NORMAL_CMD);  // Set Normal mode : Any access to the DDRSDRAMC is decoded normally
    pSdram[0] = 0x00000000;  // Dummy read to access SDRAM : validate preceeding command

    //-- 10th Step : Set Refresh timer
    WRITE(AT91C_BASE_SDDRC, SDDRC_RTR, 781); // Set Refresh Timer (ex: ((64 x 10^-3)/8192) x 100 x 10^6 ) => 781 for 100 MHz
}

//------------------------------------------------------------------------------
/// Initialize and configure the DDRAM
//------------------------------------------------------------------------------
void BOARD_ConfigureDdram(
    unsigned char ddrModel,
    unsigned char busWidth
    )
{
    // Micron MT46H16M16LF
    unsigned int i;
    volatile unsigned int *pDdram = (unsigned int *) AT91C_EBI_DDRAM;
    unsigned short ddrc_dbw = 0;

    switch (busWidth) {
        case 16:
            ddrc_dbw = AT91C_B16MODE_16_BITS;
            break;

        case 32:
        default:
            ddrc_dbw = AT91C_B16MODE_32_BITS;
            break;

    }

    // Enable DDR controller Clock
    AT91C_BASE_PMC->PMC_SCER = AT91C_PMC_DDR;

    // Step 1: program the memory device type into Memory Device Register
    // Memory Device Register
    WRITE(AT91C_BASE_SDDRC, SDDRC_MDR,   AT91C_MD_LP_DDR_SDRAM
                                       | ddrc_dbw );

    // Step 2: program the features of the Mobile DDR into the Configuration Register
    //         number of columns, rows, banks and cas latency

    // Configuration Register (Normal driver strength(0) | Disable DLL reset(0) | SDRAM CAS = 3 | row = 13 | column = 9)
    WRITE(AT91C_BASE_SDDRC, SDDRC_CR,   AT91C_DLL_RESET_DISABLED
                                      | AT91C_CAS_3
                                      | AT91C_NR_13
                                      | AT91C_NC_DDR9_SDR8 );

    // Timing 0 Parameter Register
    WRITE(AT91C_BASE_SDDRC, SDDRC_T0PR,   AT91C_TMRD_2
                                        | AT91C_TWTR_1
                                        | AT91C_TRRD_2
                                        | AT91C_TRP_3
                                        | AT91C_TRC_8
                                        | AT91C_TWR_2
                                        | AT91C_TRCD_3
                                        | AT91C_TRAS_5);

    // Timing 1 Parameter Register
    WRITE(AT91C_BASE_SDDRC, SDDRC_T1PR,   AT91C_TXP_4
                                        | AT91C_TXSRD_12
                                        | AT91C_TXSNR_12
                                        | AT91C_TRFC_9 );

    // Step 3: program temperature compensated self refresh (tcr), 
    // Partial array self refresh (pasr) 
    // and Drive strength (ds) into the Low-power Register. 

    // --------- WAIT ---------                       

    // Step 4: perform a NOP command in order to allow to enable clk    
    // NOP command
    WRITE(AT91C_BASE_SDDRC, SDDRC_MR, AT91C_MODE_NOP_CMD);
    pDdram[0] = 0x00000000;         // Dummy write to access SDRAM : validate preceeding command

    sleep_time(200);

    // Step 5: perform an All Banks Precharge command     
    // Precharge All Banks command
    WRITE(AT91C_BASE_SDDRC, SDDRC_MR, AT91C_MODE_PRCGALL_CMD);
    pDdram[0] = 0x00000000;         // Dummy write to access SDRAM : validate preceeding command

    // Step 6: two auto refresh cycles are provided    
    for (i=0;i<2;i++)
    {
        // AutoRefresh command
        WRITE(AT91C_BASE_SDDRC, SDDRC_MR, AT91C_MODE_RFSH_CMD);
        pDdram[0] = 0x00000000;         // Dummy write to access SDRAM : validate preceeding command
    }

    // Step 7: an extended mode register set cycle is issued     
    // Extended Mode Register Set command
    WRITE(AT91C_BASE_SDDRC, SDDRC_MR, AT91C_MODE_EXT_LMR_CMD);
    pDdram[0x400000] = 0x00000000;  //@0x71000000 (BA[0]=0 BA[1]=1)
    
    // Step 8: a mode register set cycle is issued     
    // Mode Register Set command
    WRITE(AT91C_BASE_SDDRC, SDDRC_MR, AT91C_MODE_LMR_CMD); 
    pDdram[0] = 0x00000000;
    
    // Step 9: Set Normal mode             
    // Set Normal mode : Any access to the DDRSDRAMC is decoded normally
    WRITE(AT91C_BASE_SDDRC, SDDRC_MR, AT91C_MODE_NORMAL_CMD);
    pDdram[0] = 0x00000000;

    // Step 10: Perform a write access to any DDR-SDRAM address         
    pDdram[0] = 0x00000000;

    // a third write to avoid DLL fine tuning
    pDdram[0] = 0x00000000;
    
    // Step 11: Set Refresh timer    
    // Set Refresh Timer : ((64 x 10^-3)/8192) x 48 x 10^6   --->  375 for 48 MHz
    //WRITE(AT91C_BASE_SDDRC, SDDRC_RTR, 375);
    // Set Refresh Timer : ((64 x 10^-3)/8192) x 100 x 10^6   --->  781 for 100 MHz
    WRITE(AT91C_BASE_SDDRC, SDDRC_RTR, 781);

    // --------- WAIT ---------
    sleep_time(2000);
}


//------------------------------------------------------------------------------
/// Initialize and configure the BCRAM
//------------------------------------------------------------------------------
void BOARD_ConfigureBcram(unsigned char busWidth)
{  
    volatile unsigned int *pBcram = (unsigned int *) AT91C_EBI_BCRAM;  
  
    // Configure EBI
    AT91C_BASE_CCFG->CCFG_EBICSA |= AT91C_EBI_CS1A_BCRAMC;
  
    // Configure A23 and A24 PIO as Periph A
    AT91C_BASE_PIOD->PIO_PDR = AT91C_PIO_PD12 | AT91C_PIO_PD13;
    AT91C_BASE_PIOD->PIO_ASR = AT91C_PIO_PD12 | AT91C_PIO_PD13;
    
    // Step 1: The Cellular Ram  memory type must be set in the BCRAMC Memory Device Register.
    // -------------------------------------------------------------------------
    // Burst CellularRAM Version 1.5 
    // (BCRAMC_MDR = 0x00000001)
    AT91C_BASE_BCRAMC->BCRAMC_MDR = AT91C_BCRAMC_MD_BCRAM_V15;            

    // Step 2: Temperature compensated self refresh (TCSR) and partial array 
    //    refresh (PAR) must be set in the BCRAMC Low Power register.    
    // -------------------------------------------------------------------------    
    // Low power register => Low-power is inhibited, Internal Temperature Sensor choosen
    // PAR[2:0]      : Partial Array Refresh = 000 (Full Array)
    // TCR_TCSR[5:4] : Temperature Compensated Refresh/Self-refresh = 00 (Internal sensor or 70°C)
    // LPCB[9:8]     : Low Power Command Bit = 00 (Low power Feature inhibited)
    // (BCRAMC_LPR    = 0x00000000)
     AT91C_BASE_BCRAMC->BCRAMC_LPR = AT91C_BCRAMC_PAR_FULL | 
                                     //AT91C_BCRAMC_TCR_INTERNAL_OR_70C | 
                                     AT91C_BCRAMC_LPCB_DISABLE;
       
    // High Speed Register
    // DA(0) Decode Cycle = 0 (No decode cycle added)
    // (BCRAMC_HSR    = 0x00000000)
    AT91C_BASE_BCRAMC->BCRAMC_HSR = AT91C_BCRAMC_DA_DISABLE;            

    // Step 3: Asynchronous timings (TCKA, TCRE..) must be set in the BCRAMC Timing Register.    
    // -------------------------------------------------------------------------    
    // TCW[3:0]   : Chip Enable to End of Write = 3 
    // TCRES[5:4] : Control Register Enable Setup = 2 
    // TCKA[11:8] : BCWE High to BCCK Valid = 0 
    // (BCRAMC_TPR = 0x00000023)
    AT91C_BASE_BCRAMC->BCRAMC_TPR = AT91C_BCRAMC_TCW_3 |
                                    AT91C_BCRAMC_TCRES_2 |
                                    AT91C_BCRAMC_TCKA_0;
                                      
    // Step 4: Cellular Ram  features must be set in the HBCRAMC Configuration Register:
    // – number rows, latency, drive strength (DS), the data bus width and cram_enabled bit must be high.    
    // -------------------------------------------------------------------------        
    // CRAM_EN(0)            : BCRAM enabled = 0
    // LM[6:4]               : Latency Mode = 011 = 3 cycles (reset value)
    // DBW[8]                : Data Bus Width = 1 (0->32bits / 1->16bits)
    // BOUNDARY_WORD[13:12]  : Number of Words in Row = 01 = 128 words by row   
    // ADDRDATA_MUX[16]      : Address and Data bus Multiplexed ? = 0 => NO
    // DS[21:20]             : Drive Strength = 00 => FULL
    // VAR_FIX_LAT[24]       : Variable or Fixed latency ? = 0 => VARIABLE
    // 3 latency cycles, dbw = 16 bits, 128 words per row, address & data bus 
    // not muxed, full drive strength, variable latency
    // (BCRAMC_CR    = 0x00001130)
    AT91C_BASE_BCRAMC->BCRAMC_CR = AT91C_BCRAMC_CAS_3 |
                                   AT91C_BCRAM_NWIR_128 |
                                   AT91C_BCRAM_ADMX_NO_MUX |
                                   AT91C_BCRAM_DS_FULL_DRIVE |
                                   AT91C_BCRAM_VFLAT_VARIABLE;
    switch (busWidth) {
        case 16:
            AT91C_BASE_BCRAMC->BCRAMC_CR |= AT91C_BCRAMC_DBW_16_BITS; 
            break;

        case 32:
        default:
            AT91C_BASE_BCRAMC->BCRAMC_CR |= AT91C_BCRAMC_DBW_32_BITS; 
            break;

    }
    
    // + BCRAMC enabled
    AT91C_BASE_BCRAMC->BCRAMC_CR |= AT91C_BCRAMC_EN;    
    
    // Step 5: Perform a write to the Cellular Ram  device and the Bus Configuration Register (BCR) and 
    // Refresh Configuration Register (RCR) are programmed automatically.         
    // Dummy write to access BCRAM : validate preceeding command
    pBcram[0]    = 0x12345678;//00000000;     
}

//------------------------------------------------------------------------------
/// Configures the EBI for NandFlash access. Pins must be configured after or
/// before calling this function.
//------------------------------------------------------------------------------
void BOARD_ConfigureNandFlash(unsigned char busWidth)
{
    // Configure EBI
    AT91C_BASE_CCFG->CCFG_EBICSA |= AT91C_EBI_CS3A_SM;

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
}

//------------------------------------------------------------------------------
/// Configures the EBI for NandFlash access at 48MHz. Pins must be configured
/// after or before calling this function.
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
}

//------------------------------------------------------------------------------
/// Configures the EBI for NorFlash access
/// \Param busWidth Bus width
//------------------------------------------------------------------------------
void BOARD_ConfigureNorFlash(unsigned char busWidth)
{
    // Configure SMC

    AT91C_BASE_SMC->SMC_SETUP0 = 0x00000002;
    AT91C_BASE_SMC->SMC_PULSE0 = 0x0A0A0A06;
    AT91C_BASE_SMC->SMC_CYCLE0 = 0x000A000A;
    AT91C_BASE_SMC->SMC_CTRL0  = (AT91C_SMC_READMODE
                                  | AT91C_SMC_WRITEMODE
                                  | AT91C_SMC_NWAITM_NWAIT_DISABLE
                                  | ((0x1 << 16) & AT91C_SMC_TDF));

    if (busWidth == 8) {
        AT91C_BASE_SMC->SMC_CTRL0 |= AT91C_SMC_DBW_WIDTH_EIGTH_BITS;
    }
    else if (busWidth == 16) {
        AT91C_BASE_SMC->SMC_CTRL0 |= AT91C_SMC_DBW_WIDTH_SIXTEEN_BITS;
    }
    else if (busWidth == 32) {
        AT91C_BASE_SMC->SMC_CTRL0 |= AT91C_SMC_DBW_WIDTH_THIRTY_TWO_BITS;
    }
}

//------------------------------------------------------------------------------
/// Configures the EBI for NorFlash access at 48MHz.
/// \Param busWidth Bus width
//------------------------------------------------------------------------------
void BOARD_ConfigureNorFlash48MHz(unsigned char busWidth)
{
    // Configure SMC
    AT91C_BASE_SMC->SMC_SETUP0 = 0x00000001;
    AT91C_BASE_SMC->SMC_PULSE0 = 0x07070703;
    AT91C_BASE_SMC->SMC_CYCLE0 = 0x00070007;
    AT91C_BASE_SMC->SMC_CTRL0  = (AT91C_SMC_READMODE
                                  | AT91C_SMC_WRITEMODE
                                  | AT91C_SMC_NWAITM_NWAIT_DISABLE
                                  | ((0x1 << 16) & AT91C_SMC_TDF));

    if (busWidth == 8) {

        AT91C_BASE_SMC->SMC_CTRL0 |= AT91C_SMC_DBW_WIDTH_EIGTH_BITS;
    }
    else if (busWidth == 16) {

        AT91C_BASE_SMC->SMC_CTRL0 |= AT91C_SMC_DBW_WIDTH_SIXTEEN_BITS;
    }
    else if (busWidth == 32) {

        AT91C_BASE_SMC->SMC_CTRL0 |= AT91C_SMC_DBW_WIDTH_THIRTY_TWO_BITS;
    }
}

