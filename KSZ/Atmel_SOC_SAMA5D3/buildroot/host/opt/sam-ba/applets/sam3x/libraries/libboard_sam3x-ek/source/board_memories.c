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
 * Implementation of memories configuration on board.
 *
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/
#include "board.h"


/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/
/* Definition for the used SDRAM device */
static SSdramc_Memory sdram_dev;

/* SDRAM MT48LC16M16A2 configuration */
static const SSdramc_Memory SDRAM_MICRON_MT48LC16M16A2 =
{
  {
    SDRAMC_CR_NC_COL9,  // 9 column bits (512 bytes)
    SDRAMC_CR_NR_ROW13,  // 13 row bits    (8K)
    SDRAMC_CR_NB_BANK4,  // SDRAM 4 bank
    SDRAMC_CR_CAS_LATENCY2,    // CAS Latency 3
    SDRAMC_CR_DBW,    // Data bus width 16 bits
    2,  // Write Recovery Delay
    9,  // Row Cycle Delay and Row Refresh Cycle
    3,  // Row Precharge Delay
    3,  // Row to Column Delay
    6,  // Active to Precharge Delay
    10,  // Exit Self Refresh to Active Delay
    24,  //bk1 is at the bit 24, 1+9+13+1
  }
};
/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Configures the EBI for NandFlash access.
 */
extern void BOARD_ConfigureNandFlash( Smc* pSmc )
{
    /* Enable peripheral clock */
    PMC_EnablePeripheral( ID_SMC ) ;

    pSmc->SMC_CS_NUMBER[0].SMC_SETUP = SMC_SETUP_NWE_SETUP(0)
                                     | SMC_SETUP_NCS_WR_SETUP(0)
                                     | SMC_SETUP_NRD_SETUP(0)
                                     | SMC_SETUP_NCS_RD_SETUP(0);

    pSmc->SMC_CS_NUMBER[0].SMC_PULSE = SMC_PULSE_NWE_PULSE(2)
                                     | SMC_PULSE_NCS_WR_PULSE(3)
                                     | SMC_PULSE_NRD_PULSE(2)
                                     | SMC_PULSE_NCS_RD_PULSE(3);

    pSmc->SMC_CS_NUMBER[0].SMC_CYCLE = SMC_CYCLE_NWE_CYCLE(3)
                                     | SMC_CYCLE_NRD_CYCLE(3);

    pSmc->SMC_CS_NUMBER[0].SMC_TIMINGS = SMC_TIMINGS_TCLR(1)
                                       | SMC_TIMINGS_TADL(6)
                                       | SMC_TIMINGS_TAR(4)
                                       | SMC_TIMINGS_TRR(2)
                                       | SMC_TIMINGS_TWB(9)
                                       | SMC_TIMINGS_RBNSEL(7)
                                       |(SMC_TIMINGS_NFSEL);

    pSmc->SMC_CS_NUMBER[0].SMC_MODE = SMC_MODE_READ_MODE
                                    | SMC_MODE_WRITE_MODE
                                    | SMC_MODE_DBW_BIT_8;
}

#if 1
/**
 * \brief Configures the EBI for %NorFlash access.
 */
extern void BOARD_ConfigureNorFlash( Smc* pSmc )
{
    /* Enable peripheral clock */
    PMC_EnablePeripheral( ID_SMC ) ;

    /* Configure SMC, NCS0 is assigned to a norflash */
    pSmc->SMC_CS_NUMBER[0].SMC_SETUP = SMC_SETUP_NWE_SETUP(2)
                                     | SMC_SETUP_NCS_WR_SETUP(0)
                                     | SMC_SETUP_NRD_SETUP(0)
                                     | SMC_SETUP_NCS_RD_SETUP(0);

    pSmc->SMC_CS_NUMBER[0].SMC_PULSE = SMC_PULSE_NWE_PULSE(6)
                                     | SMC_PULSE_NCS_WR_PULSE(0xA)
                                     | SMC_PULSE_NRD_PULSE(0xA)
                                     | SMC_PULSE_NCS_RD_PULSE(0xA);

    pSmc->SMC_CS_NUMBER[0].SMC_CYCLE = SMC_CYCLE_NWE_CYCLE(0xA)
                                     | SMC_CYCLE_NRD_CYCLE(0xA);

    pSmc->SMC_CS_NUMBER[0].SMC_MODE  = SMC_MODE_READ_MODE
                                     | SMC_MODE_WRITE_MODE
                                     | SMC_MODE_DBW_BIT_16
                                     | SMC_MODE_EXNW_MODE_DISABLED
                                     | SMC_MODE_TDF_CYCLES(0x1);
}
#endif
/**
 * \brief An accurate one-to-one comparison is necessary between PSRAM and SMC waveforms for
 *   a complete SMC configuration.
 *  \note The system is running at 48 MHz for the EBI Bus.
 *        Please refer to the "AC Characteristics" section of the customer product datasheet.
 */
extern void BOARD_ConfigurePSRAM( Smc* pSmc )
{
     /* Enable peripheral clock */
    PMC_EnablePeripheral( ID_SMC ) ;

    /* Configure SMC, NCS1 is assigned to a external PSRAM */
    /**
     * PSRAM IS66WV51216BLL
     * 55 ns Access time
     * tdoe = 25 ns max
     * SMC1 (timing SAM3X read mode SMC) = 21 ns of setup
     * 21 + 55 = 76 ns => at least 5 cycles at 64 MHz
     * Write pulse width minimum = 45 ns (PSRAM)
     */
    pSmc->SMC_CS_NUMBER[1].SMC_SETUP = SMC_SETUP_NWE_SETUP( 1 )
                                     | SMC_SETUP_NCS_WR_SETUP( 0 )
                                     | SMC_SETUP_NRD_SETUP( 2 )
                                     | SMC_SETUP_NCS_RD_SETUP( 0 ) ;

    pSmc->SMC_CS_NUMBER[1].SMC_PULSE = SMC_PULSE_NWE_PULSE( 3 )
                                     | SMC_PULSE_NCS_WR_PULSE( 4 )
                                     | SMC_PULSE_NRD_PULSE( 3 )
                                     | SMC_PULSE_NCS_RD_PULSE( 5 ) ;

    /* NWE_CYCLE:     The total duration of the write cycle.
                      NWE_CYCLE = NWE_SETUP + NWE_PULSE + NWE_HOLD
                      = NCS_WR_SETUP + NCS_WR_PULSE + NCS_WR_HOLD
                      (tWC) Write Cycle Time min. 70ns
       NRD_CYCLE:     The total duration of the read cycle.
                      NRD_CYCLE = NRD_SETUP + NRD_PULSE + NRD_HOLD
                      = NCS_RD_SETUP + NCS_RD_PULSE + NCS_RD_HOLD
                      (tRC) Read Cycle Time min. 70ns. */
    pSmc->SMC_CS_NUMBER[1].SMC_CYCLE = SMC_CYCLE_NWE_CYCLE( 4 )
                                     | SMC_CYCLE_NRD_CYCLE( 5 ) ;
 
    pSmc->SMC_CS_NUMBER[1].SMC_MODE  = SMC_MODE_READ_MODE
                                     | SMC_MODE_WRITE_MODE
                                     | SMC_MODE_DBW_BIT_16 ;
}

/**
 * \brief Initialize and configure the SDRAM.
 */
extern void BOARD_ConfigureSdram( void )
{
    static const Pin pinsSdram[] = { PINS_SDRAM } ;

    /* The SAM3X-EK-REVA board uses the SDRAM of MT48LC16M16A2 */
    sdram_dev = SDRAM_MICRON_MT48LC16M16A2 ;

    /* Enable corresponding PIOs */
    PIO_PinConfigure( pinsSdram, PIO_LISTSIZE(pinsSdram) ) ;

    /* Configure the SDRAMC used */
    SDRAMC_Configure( &sdram_dev, SDRAMC_CLK ) ;
}


