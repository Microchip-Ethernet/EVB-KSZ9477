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

#include "board_memories.h"
#include "board.h"
#include <pio/pio.h>

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
        BOARD_FLASH - Flash is mirrored in the remap zone.
        BOARD_RAM - RAM is mirrored in the remap zone.
*/
#define BOARD_FLASH             0
#define BOARD_RAM               1

//------------------------------------------------------------------------------
//         Internal function
//------------------------------------------------------------------------------
/*
    Function: BOARD_GetRemap
        Returns the current remap (see <Remap types>).
*/
static unsigned char BOARD_GetRemap( void )
{
    volatile unsigned int *remap = (volatile unsigned int *) 0;
    volatile unsigned int *ram = (volatile unsigned int *) AT91C_ISRAM;

    // Try to write in 0 and see if this affects the RAM
    unsigned int temp = *ram;
    *ram = temp + 1;
    if (*remap == *ram) {

        *ram = temp;
        return BOARD_RAM;
    }
    else {

        *ram = temp;
        return BOARD_FLASH;
    }
}

//------------------------------------------------------------------------------
//         Exported functions
//------------------------------------------------------------------------------
/*
    Function: BOARD_RemapFlash
        Changes the mapping of the chip so that the remap area mirrors the
        internal flash.
*/
void BOARD_RemapFlash( void )
{
    if (BOARD_GetRemap() != BOARD_FLASH) {

        AT91C_BASE_MC->MC_RCR = AT91C_MC_RCB;
    }
}

/*
    Function: BOARD_RemapRam
        Changes the mapping of the chip so that the remap area mirrors the
        internal RAM.
*/
void BOARD_RemapRam( void )
{
    if (BOARD_GetRemap() != BOARD_RAM) {

        AT91C_BASE_MC->MC_RCR = AT91C_MC_RCB;
    }
}

//------------------------------------------------------------------------------
/// Initializes the SDRAM controller so the external SDRAM chip connected to the
/// EBI is accessible. The EBI pins for the SDRAM must be configured prior to
/// calling this function.
//------------------------------------------------------------------------------
void BOARD_ConfigureSdram(unsigned char busWidth)
{
    volatile unsigned int i;
    static const Pin pinsSdram[] = {PINS_SDRAM};
    volatile unsigned int *pSdram = (unsigned int *) AT91C_EBI_SDRAM;
    unsigned short sdrc_dbw = 0;

    switch (busWidth) {
        case 16:
        default:
            sdrc_dbw = AT91C_SDRC_DBW_16_BITS;
            break;

        case 32:
            sdrc_dbw = AT91C_SDRC_DBW_32_BITS;
            break;

    }


    // Enable corresponding PIOs
    PIO_Configure(pinsSdram, PIO_LISTSIZE(pinsSdram));
    
    // Enable EBI chip select for the SDRAM
    WRITE(AT91C_BASE_EBI, EBI_CSA, AT91C_EBI_CS1A_SDRAMC);
    
#define AT91C_SDRC_NC_9           (0x1)
#define AT91C_SDRC_NR_13          (0x2 << 2)
#define AT91C_SDRC_CAS_2          (0x2 << 5)
#define AT91C_SDRC_NB_4_BANKS     (0x1 << 4)
#define AT91C_SDRC_TWR_2          (0x2 << 7)
#define AT91C_SDRC_TRC_4          (0x4 << 11)
#define AT91C_SDRC_TRP_4          (0x4 << 15)
#define AT91C_SDRC_TRCD_2         (0x2 << 19)
#define AT91C_SDRC_TRAS_3         (0x3 << 23)
#define AT91C_SDRC_TXSR_4         (0x4 << 27)

    // CFG Control Register
    WRITE(AT91C_BASE_SDRC, SDRC_CR, AT91C_SDRC_NC_9
                                    | AT91C_SDRC_NR_13
                                    | AT91C_SDRC_CAS_2
                                    | AT91C_SDRC_NB_4_BANKS
                                    | AT91C_SDRC_TWR_2
                                    | AT91C_SDRC_TRC_4
                                    | AT91C_SDRC_TRP_4
                                    | AT91C_SDRC_TRCD_2
                                    | AT91C_SDRC_TRAS_3
                                    | AT91C_SDRC_TXSR_4);
            
    for (i = 0; i < 1000; i++);

    WRITE(AT91C_BASE_SDRC, SDRC_MR, sdrc_dbw | AT91C_SDRC_MODE_NOP_CMD); // Perform NOP
    pSdram[0] = 0x00000000;

    WRITE(AT91C_BASE_SDRC, SDRC_MR, sdrc_dbw | AT91C_SDRC_MODE_PRCGALL_CMD); // Set PRCHG AL
    pSdram[0] = 0x00000000;                     // Perform PRCHG

    for (i = 0; i < 10000; i++);

    WRITE(AT91C_BASE_SDRC, SDRC_MR, sdrc_dbw | AT91C_SDRC_MODE_RFSH_CMD);    // Set 1st CBR
    pSdram[1] = 0x00000001;                     // Perform CBR

    WRITE(AT91C_BASE_SDRC, SDRC_MR, sdrc_dbw | AT91C_SDRC_MODE_RFSH_CMD);    // Set 2 CBR
    pSdram[2] = 0x00000002;                     // Perform CBR

    WRITE(AT91C_BASE_SDRC, SDRC_MR, sdrc_dbw | AT91C_SDRC_MODE_RFSH_CMD);    // Set 3 CBR
    pSdram[3] = 0x00000003;                    // Perform CBR

    WRITE(AT91C_BASE_SDRC, SDRC_MR, sdrc_dbw | AT91C_SDRC_MODE_RFSH_CMD);    // Set 4 CBR
    pSdram[4] = 0x00000004;                   // Perform CBR

    WRITE(AT91C_BASE_SDRC, SDRC_MR, sdrc_dbw | AT91C_SDRC_MODE_RFSH_CMD);    // Set 5 CBR
    pSdram[5] = 0x00000005;                   // Perform CBR

    WRITE(AT91C_BASE_SDRC, SDRC_MR, sdrc_dbw | AT91C_SDRC_MODE_RFSH_CMD);    // Set 6 CBR
    pSdram[6] = 0x00000006;                 // Perform CBR

    WRITE(AT91C_BASE_SDRC, SDRC_MR, sdrc_dbw | AT91C_SDRC_MODE_RFSH_CMD);    // Set 7 CBR
    pSdram[7] = 0x00000007;                 // Perform CBR

    WRITE(AT91C_BASE_SDRC, SDRC_MR, sdrc_dbw | AT91C_SDRC_MODE_RFSH_CMD);    // Set 8 CBR
    pSdram[8] = 0x00000008;                 // Perform CBR

    WRITE(AT91C_BASE_SDRC, SDRC_MR, sdrc_dbw | AT91C_SDRC_MODE_LMR_CMD);     // Set LMR operation
    pSdram[9] = 0xcafedede;                 // Perform LMR burst=1, lat=2

    WRITE(AT91C_BASE_SDRC, SDRC_TR, sdrc_dbw | (BOARD_MCK * 7) / 1000000);     // Set Refresh Timer

    WRITE(AT91C_BASE_SDRC, SDRC_MR, sdrc_dbw | AT91C_SDRC_MODE_NORMAL_CMD);  // Set Normal mode
    pSdram[0] = 0x00000000;                     // Perform Normal mode
}

//------------------------------------------------------------------------------
/// Configures the EBI for NandFlash access. Pins must be configured after or
/// before calling this function.
//------------------------------------------------------------------------------
void BOARD_ConfigureNandFlash(unsigned char busWidth)
{
    // Configure EBI
    AT91C_BASE_EBI->EBI_CSA |= AT91C_EBI_CS3A_SMC_NandFlash;

#define AT91C_SMC2_NWS_2            ((unsigned int) 1 <<  0)
#define AT91C_SMC2_TDF_2_CYCLES     ((unsigned int) 2 <<  8)
#define AT91C_SMC2_BAT_8BIT         ((unsigned int) 0 << 12)
#define AT91C_SMC2_DRP_STANDARD     ((unsigned int) 0 << 15)
#define AT91C_SMC2_RWSETUP_0_CYCLE  ((unsigned int) 0 << 24)
#define AT91C_SMC2_RWHOLD_1_CYCLE   ((unsigned int) 1 << 28)

    // Configure SMC
    AT91C_BASE_SMC->SMC2_CSR[3] =
         AT91C_SMC2_NWS_2           // 2 wait states required required by the NAND Flash device
       | AT91C_SMC2_WSEN            // NWS register enabled
       | AT91C_SMC2_TDF_2_CYCLES    // 2 Data Float Time Cycles required by the NAND Flash device
       | AT91C_SMC2_BAT_8BIT        // 1 8-bit device connected over the bus
       | AT91C_SMC2_DRP_STANDARD    // Standard Read protocol required by the NAND Flash device
       | AT91C_SMC2_ACSS_STANDARD   // Standard address to chip select
       | AT91C_SMC2_RWSETUP_0_CYCLE // 0 Read/Write Setup time required by the Nand Flash Device
       | AT91C_SMC2_RWHOLD_1_CYCLE; // 1 Read/Write Setup time required by the ECC controller
    
    if (busWidth == 8) {
        AT91C_BASE_SMC->SMC2_CSR[3] |=  AT91C_SMC2_DBW_8;
    }
    else if (busWidth == 16) {
 
        AT91C_BASE_SMC->SMC2_CSR[3] |=  AT91C_SMC2_DBW_16;
    }       
}

//------------------------------------------------------------------------------
/// Configures a list of AT91S_EFC instances.
/// \param list  Pointer to a list of AT91S_EFC instances.
/// \param size  Size of the AT91S_EFC list.
/// \param numWaitStates  Number of state cycles value for the EFC.
//------------------------------------------------------------------------------
void BOARD_ConfigureFlash48MHz(void)
{
    /* Set flash wait states in the EFC
     **********************************/
    /* 48MHz = 1 wait state */
#if defined(at91sam7se512)
    AT91C_BASE_EFC0->EFC_FMR = AT91C_MC_FWS_2FWS;
    AT91C_BASE_EFC1->EFC_FMR = AT91C_MC_FWS_2FWS;
#elif defined(at91sam7se32) || defined(at91sam7se256)
    AT91C_BASE_EFC->EFC_FMR = AT91C_MC_FWS_2FWS;
#else
    #error No chip definition ?
#endif
}

//------------------------------------------------------------------------------
/// Configures the EBI for NorFlash access at 48MHz.
/// \Param busWidth Bus width 
//------------------------------------------------------------------------------
void BOARD_ConfigureNorFlash(unsigned char busWidth)
{
    
    // Configure SMC
    AT91C_BASE_SMC->SMC2_CSR[0] =
         ((unsigned int) 2 <<  0)       // 2 wait states required required by the NOR Flash device
       | AT91C_SMC2_WSEN                // NWS register enabled
       | ((unsigned int) 1 <<  8)       // 1 Data Float Time Cycles required by the NOR Flash device
       | AT91C_SMC2_BAT_8BIT            // 1 8-bit device connected over the bus
       | AT91C_SMC2_DRP_STANDARD        // Standard Read protocol required by the NOR Flash device
       | ((unsigned int) 1 << 24)       // 1 Read/Write Setup time required by the NOR Flash Device
       | ((unsigned int) 2 << 28);      // 2 Read/Write Setup time required by the ECC controller
    if (busWidth == 8) {
        AT91C_BASE_SMC->SMC2_CSR[0] |=  AT91C_SMC2_DBW_8;
    }
    else if (busWidth == 16) {
 
        AT91C_BASE_SMC->SMC2_CSR[0] |=  AT91C_SMC2_DBW_16;
    }
}

