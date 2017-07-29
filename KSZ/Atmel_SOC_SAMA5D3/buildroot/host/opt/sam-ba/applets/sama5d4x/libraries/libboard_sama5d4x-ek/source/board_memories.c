/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2013, Atmel Corporation
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

/** \addtogroup ddrd_module
 *
 * The DDR/SDR SDRAM Controller (DDRSDRC) is a multiport memory controller. It comprises
 * four slave AHB interfaces. All simultaneous accesses (four independent AHB ports) are interleaved
 * to maximize memory bandwidth and minimize transaction latency due to SDRAM protocol.
 *
 * \section ddr2 Configures DDR2
 *
 * The DDR2-SDRAM devices are initialized by the following sequence:
 * <ul>
 * <li> EBI Chip Select 1 is assigned to the DDR2SDR Controller, Enable DDR2 clock x2 in PMC.</li>
 * <li> Step 1: Program the memory device type</li>
 * <li> Step 2:
 *  -# Program the features of DDR2-SDRAM device into the Configuration Register.
 *  -# Program the features of DDR2-SDRAM device into the Timing Register HDDRSDRC2_T0PR.
 *  -# Program the features of DDR2-SDRAM device into the Timing Register HDDRSDRC2_T1PR.
 *  -# Program the features of DDR2-SDRAM device into the Timing Register HDDRSDRC2_T2PR. </li>
 * <li> Step 3: An NOP command is issued to the DDR2-SDRAM to enable clock. </li>
 * <li> Step 4:  An NOP command is issued to the DDR2-SDRAM </li>
 * <li> Step 5: An all banks precharge command is issued to the DDR2-SDRAM. </li>
 * <li> Step 6: An Extended Mode Register set (EMRS2) cycle is  issued to chose between commercialor high  temperature operations.</li>
 * <li> Step 7: An Extended Mode Register set (EMRS3) cycle is issued to set all registers to 0. </li>
 * <li> Step 8:  An Extended Mode Register set (EMRS1) cycle is issued to enable DLL.</li>
 * <li> Step 9:  Program DLL field into the Configuration Register.</li>
 * <li> Step 10: A Mode Register set (MRS) cycle is issued to reset DLL.</li>
 * <li> Step 11: An all banks precharge command is issued to the DDR2-SDRAM.</li>
 * <li> Step 12: Two auto-refresh (CBR) cycles are provided. Program the auto refresh command (CBR) into the Mode Register.</li>
 * <li> Step 13: Program DLL field into the Configuration Register to low(Disable DLL reset).</li>
 * <li> Step 14: A Mode Register set (MRS) cycle is issued to program the parameters of the DDR2-SDRAM devices.</li>
 * <li> Step 15: Program OCD field into the Configuration Register to high (OCD calibration default). </li>
 * <li> Step 16: An Extended Mode Register set (EMRS1) cycle is issued to OCD default value.</li>
 * <li> Step 17: Program OCD field into the Configuration Register to low (OCD calibration mode exit).</li>
 * <li> Step 18: An Extended Mode Register set (EMRS1) cycle is issued to enable OCD exit.</li>
 * <li> Step 19,20: A mode Normal command is provided. Program the Normal mode into Mode Register.</li>
 * <li> Step 21: Write the refresh rate into the count field in the Refresh Timer register. The DDR2-SDRAM device requires a refresh every 15.625 or 7.81. </li>
 * </ul>
*/
/*@{*/
/*@}*/

/** \addtogroup sdram_module
 *
 * \section sdram Configures SDRAM
 *
 * The SDR-SDRAM devices are initialized by the following sequence:
 * <ul>
 * <li> EBI Chip Select 1 is assigned to the DDR2SDR Controller, Enable DDR2 clock x2 in PMC.</li>
 * <li> Step 1. Program the memory device type into the Memory Device Register</li>
 * <li> Step 2. Program the features of the SDR-SDRAM device into the Timing Register and into the Configuration Register.</li>
 * <li> Step 3. For low-power SDRAM, temperature-compensated self refresh (TCSR), drive strength (DS) and partial array self refresh (PASR) must be set in the Low-power Register.</li>
 * <li> Step 4. A NOP command is issued to the SDR-SDRAM. Program NOP command into Mode Register, the application must
 * set Mode to 1 in the Mode Register. Perform a write access to any SDR-SDRAM address to acknowledge this command.
 * Now the clock which drives SDR-SDRAM device is enabled.</li>
 * <li> Step 5. An all banks precharge command is issued to the SDR-SDRAM. Program all banks precharge command into Mode Register, the application must set Mode to 2 in the
 * Mode Register . Perform a write access to any SDRSDRAM address to acknowledge this command.</li>
 * <li> Step 6. Eight auto-refresh (CBR) cycles are provided. Program the auto refresh command (CBR) into Mode Register, the application must set Mode to 4 in the Mode Register.
 * Once in the idle state, two AUTO REFRESH cycles must be performed.</li>
 * <li> Step 7. A Mode Register set (MRS) cycle is issued to program the parameters of the SDRSDRAM
 * devices, in particular CAS latency and burst length. </li>
 * <li> Step 8. For low-power SDR-SDRAM initialization, an Extended Mode Register set (EMRS) cycle is issued to program the SDR-SDRAM parameters (TCSR, PASR, DS). The write
 * address must be chosen so that BA[1] is set to 1 and BA[0] is set to 0 </li>
 * <li> Step 9. The application must go into Normal Mode, setting Mode to 0 in the Mode Register and perform a write access at any location in the SDRAM to acknowledge this command.</li>
 * <li> Step 10. Write the refresh rate into the count field in the DDRSDRC Refresh Timer register </li>
* </ul>
*/
/*@{*/
/*@}*/



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

#define MT46H128M16LFCK        1
#define MT47H128M8CF           2
#define MT47H128M16            3
#define MT47H64M16             4
#define MT42L128M32D1GU        5

#define BA0_16BIT         (1 << 25)
#define BA1_16BIT         (1 << 26)

#define BA0_32BIT         (1 << 26)
#define BA1_32BIT         (1 << 27)

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Changes the mapping of the chip so that the remap area mirrors the
 * internal ROM or the EBI CS0.
 */
void BOARD_RemapRom( void )
{
    AXIMX->AXIMX_REMAP = 0;
}

/**
 * \brief Changes the mapping of the chip so that the remap area mirrors the
 * internal RAM.
 */
void BOARD_RemapRam( void )
{
    AXIMX->AXIMX_REMAP = AXIMX_REMAP_REMAP0;
}

#define H64MX_DDR_SLAVE_PORT0   3

void matrix_configure_slave_ddr(void)
{
     int ddr_port;

     /* Disable write protection */
     MATRIX0->MATRIX_WPMR = MPDDRC_WPMR_WPKEY_PASSWD;

     /* Partition external DDR */
     /* DDR port 0 not used from NWd */
     for (ddr_port = 1 ; ddr_port < 8 ; ddr_port++) {
           MATRIX0->MATRIX_SSR[H64MX_DDR_SLAVE_PORT0 + ddr_port]   = 0x00FFFFFF;
           MATRIX0->MATRIX_SRTSR[H64MX_DDR_SLAVE_PORT0 + ddr_port] = 0x0000000F;
           MATRIX0->MATRIX_SASSR[H64MX_DDR_SLAVE_PORT0 + ddr_port] = 0x0000FFFF;
     }
}

#define MATRIX_KEY_VAL (0x4D4154u)

void matrix_configure_slave_nand(void)
{
    /* Disable write protection */
    MATRIX0->MATRIX_WPMR = MATRIX_WPMR_WPKEY(MATRIX_KEY_VAL);
    MATRIX1->MATRIX_WPMR = MATRIX_WPMR_WPKEY(MATRIX_KEY_VAL);

    /* Partition internal SRAM */
    MATRIX0->MATRIX_SSR[11]   = 0x00010101;
    MATRIX0->MATRIX_SRTSR[11] = 0x05;
    MATRIX0->MATRIX_SASSR[11] = 0x05;

    MATRIX1->MATRIX_SRTSR[3] = 0xBBBBBBBB;
    MATRIX1->MATRIX_SSR[3]   = 0x00FFFFFF;
    MATRIX1->MATRIX_SASSR[3] = 0xBBBBBBBB;

    MATRIX1->MATRIX_SRTSR[4] = 0x01;
    MATRIX1->MATRIX_SSR[4]   = 0x00FFFFFF;
    MATRIX1->MATRIX_SASSR[4] = 0x01;
    MATRIX1->MATRIX_MEIER = 0x3FF;
}


/**
 * \brief Configures LPDDR1
 *
 *  # 2£ºLPDDR1 (MT46H128M16LFCK_5): 
         * 8 Meg x 32 x 8 banks x 2 die 
         * 512MB x 2 chip = 1G
 */

void  BOARD_Configure_LPDDR1(void)
{
    uint32_t dummy_value;
    volatile uint32_t i;

    dummy_value = 0x00000000;
    matrix_configure_slave_ddr();
    PMC->PMC_PCER0 = (1 << (ID_MPDDRC));
    PMC->PMC_SCER  |= PMC_SCER_DDRCK;

    // -------------- Memory Device Register  :  32bit mode - DDR2 mode
    MPDDRC->MPDDRC_MD   =  MPDDRC_MD_MD_LPDDR_SDRAM; // 32bit MODE (bit 4 = 0)  + LPDDR1 memory type

    MPDDRC->MPDDRC_RD_DATA_PATH = MPDDRC_RD_DATA_PATH_SHIFT_SAMPLING_SHIFT_ONE_CYCLE;

    // -------------- Timing 0-3 Parameter Registers

    MPDDRC->MPDDRC_TPR0 = MPDDRC_TPR0_TRAS(8) |  //40ns = 8
                          MPDDRC_TPR0_TRCD(3) |  //15ns = 3
                          MPDDRC_TPR0_TWR(3)  |  //15ns = 4
                          MPDDRC_TPR0_TRC(10) |  //55ns = 10
                          MPDDRC_TPR0_TRP(3)  |  //15ns = 3
                          MPDDRC_TPR0_TRRD(2) |  //10.8ns = 2
                          MPDDRC_TPR0_TWTR(2) |  //7.5ns = 2
                          MPDDRC_TPR0_TMRD(2);   //2ck

    MPDDRC->MPDDRC_TPR1 = MPDDRC_TPR1_TRFC(13)  |  //72ns =13
                          MPDDRC_TPR1_TXSNR(15) |  //82ns =15
                          MPDDRC_TPR1_TXSRD(20) |  //112.5ns = 20
                          MPDDRC_TPR1_TXP(2);      //2ck

    MPDDRC->MPDDRC_TPR2 = MPDDRC_TPR2_TXARD(2)  |  //2ck
                          MPDDRC_TPR2_TXARDS(2) |  //2ck
                          MPDDRC_TPR2_TRPA(3)   |  //15ns = 3 
                          MPDDRC_TPR2_TRTP(3)   |  //15ns = 3
                          MPDDRC_TPR2_TFAW(8);     //44ns = 8
    MPDDRC->MPDDRC_LPR = 0;

    // -------------------- Additional DDR setting ------------------------
    dummy_value = MPDDRC->MPDDRC_IO_CALIBR;
    dummy_value &= ~MPDDRC_IO_CALIBR_RDIV_Msk;
    dummy_value &= ~MPDDRC_IO_CALIBR_TZQIO_Msk;

    dummy_value |= MPDDRC_IO_CALIBR_RDIV_RZQ_60_RZQ_50;
    dummy_value |= MPDDRC_IO_CALIBR_TZQIO(5);   // warning : needed for test with high temperature
    dummy_value |= MPDDRC_IO_CALIBR_EN_CALIB_ENABLE_CALIBRATION;

    MPDDRC->MPDDRC_IO_CALIBR = dummy_value;

    // -------------------------- LPDDR1 INITialisation --------------------------
    // ---------------------------------------------------------------------------

    // -------------- Configuration Register  :  CAS 3, ROW 14, COLUMN 10

    MPDDRC->MPDDRC_CR = MPDDRC_CR_NR_14_ROW_BITS     |
                        MPDDRC_CR_NC_10_COL_BITS     |
                        MPDDRC_CR_CAS_DDR_CAS3       |
                        MPDDRC_CR_DLL_RESET_DISABLED |
                        MPDDRC_CR_DQMS_NOT_SHARED    |
                        MPDDRC_CR_ENRDM_OFF          |
                        MPDDRC_CR_NB_8_BANKS         |
                        MPDDRC_CR_NDQS_DISABLED      |
                        MPDDRC_CR_UNAL_SUPPORTED     |
                        MPDDRC_CR_OCD_DDR2_EXITCALIB;

    // -------------- Low-power Register  :  Low-power Feature is inhibited, Clock Frozen disabled,

    MPDDRC->MPDDRC_LPR = MPDDRC_LPR_LPCB_NOLOWPOWER       |
                         MPDDRC_LPR_CLK_FR_DISABLED       |
                         MPDDRC_LPR_LPDDR2_PWOFF_DISABLED |
                         MPDDRC_LPR_PASR(0)               |
                         MPDDRC_LPR_DS(0)                 |
                         MPDDRC_LPR_TIMEOUT_NONE          |
                         MPDDRC_LPR_APDE_DDR2_FAST_EXIT   |
                         MPDDRC_LPR_UPD_MR_NO_UPDATE;
     for (i = 0; i < 13300; i++)
         asm("nop");

    // -------------- Mode Register : command  NOP --> ENABLE CLOCK output (Mode Register Select LPDDR2 is ignored)
    MPDDRC->MPDDRC_MR = MPDDRC_MR_MODE_NOP_CMD;
    *(uint32_t *)DDR_CS_ADDR  = 0x0000000;
     for (i = 0; i < 13300; i++)
         asm("nop");

    // A minimum pause of 200  is provided to precede any signal toggle
    // -------------- Mode Register : command  NOP --> CKE is driven high
    MPDDRC->MPDDRC_MR = MPDDRC_MR_MODE_NOP_CMD;
    *(uint32_t *)DDR_CS_ADDR = 0x0000000;

    // -------------- Mode Register : command  All Banks Precharge
    MPDDRC->MPDDRC_MR = MPDDRC_MR_MODE_PRCGALL_CMD;
    *(uint32_t *)DDR_CS_ADDR   = 0x0000000;

    // -------------- Mode Register : command  NOP
    MPDDRC->MPDDRC_MR = MPDDRC_MR_MODE_NOP_CMD;
    *(uint32_t *)DDR_CS_ADDR = 0x0000000;

    // -------------- Mode Register : command  Auto-Refresh
    MPDDRC->MPDDRC_MR = MPDDRC_MR_MODE_RFSH_CMD;
    *(uint32_t *)DDR_CS_ADDR = 0x0000000;

    // -------------- Mode Register : command  NOP
    MPDDRC->MPDDRC_MR = MPDDRC_MR_MODE_NOP_CMD;
    *(uint32_t *)DDR_CS_ADDR = 0x0000000;

    // -------------- Mode Register : command  Auto-Refresh

    MPDDRC->MPDDRC_MR = MPDDRC_MR_MODE_RFSH_CMD;
    *(uint32_t *)DDR_CS_ADDR = 0x0000000;

    // -------------- Mode Register : command  NOP

    MPDDRC->MPDDRC_MR = MPDDRC_MR_MODE_NOP_CMD;
    *(uint32_t *)DDR_CS_ADDR = 0x0000000;

    // ------ Mode Register : command  Load Mode Register  : Set EMR Ext Mode Reg EMR2 BA0=0 BA1=1
    //               0x08000000 = (BA1  bit 27)   0x04000000 = (BA0  bit 26)
    //               with BA1 = 0 and BA0 = 0

    MPDDRC->MPDDRC_MR = MPDDRC_MR_MODE_LMR_CMD;
    *(uint32_t *)DDR_CS_ADDR = 0x0000000;

    // -------------- Mode Register : command  NOP
    MPDDRC->MPDDRC_MR = MPDDRC_MR_MODE_NOP_CMD;
    *(uint32_t *)DDR_CS_ADDR = 0x0000000;

    // -------------- Mode Register : command  Extended Load Mode Register  (EMRS3) : Set EMR Ext Mode Reg EMR3 BA0=1 BA1=1
    //                                0x08000000 = (BA1  bit 27)   0x04000000 = (BA0  bit 26)
    //                                Set EMR Ext Mode Reg EMR2 BA0=0 BA1=1

    MPDDRC->MPDDRC_MR = MPDDRC_MR_MODE_EXT_LMR_CMD;
    *(uint32_t *)(DDR_CS_ADDR | BA1_32BIT) = 0x0000000;

    // -------------- Mode Register : command  NOP

    MPDDRC->MPDDRC_MR = MPDDRC_MR_MODE_NOP_CMD;
    *(uint32_t *)DDR_CS_ADDR = 0x0000000;

    // -------------- Mode Register : command  Normal mode
    MPDDRC->MPDDRC_MR = MPDDRC_MR_MODE_NORMAL_CMD;
    *(uint32_t *)DDR_CS_ADDR = 0x0000000;

     // -------------- Refresh Time Register
    MPDDRC->MPDDRC_RTR = 2746 ;
}

/**
 * \brief Configures DDR2 (MT47H128M16RT 128MB/ MT47H128M8CF )
    MT47H128M8CF-25E
    #    * 1.8V
    #    * 128 Meg x 8 (16 Meg x 8 x 8 banks)
    #    * 128MB x 4 chip = 512MB

    MT47H128M16-25E
    #    * 1.8V
    #    * 128 Meg x 16 (16 Meg x 16 x 8 banks) 
    #    * 256MB x 2 chip = 512MB
 */
void BOARD_Configure_DDR2(uint8_t device)
{
    volatile uint8_t *pDdr = (uint8_t *) DDR_CS_ADDR;
    volatile uint32_t i;

    volatile uint32_t dummy_value;

    matrix_configure_slave_ddr();
    /* Enable DDR2 clock x2 in PMC */
    PMC->PMC_PCER0 = (1 << (ID_MPDDRC));
    PMC->PMC_SCER  |= PMC_SCER_DDRCK;

    /* Step 1: Program the memory device type */
    /* DBW = 0 (32 bits bus wide); Memory Device = 6 = DDR2-SDRAM = 0x00000006*/

    MPDDRC->MPDDRC_MD = MPDDRC_MD_MD_DDR2_SDRAM;
    MPDDRC->MPDDRC_RD_DATA_PATH = MPDDRC_RD_DATA_PATH_SHIFT_SAMPLING_SHIFT_ONE_CYCLE;

    // Bus Freq (MHz)  176MHz
    // T=1/F (ns) = 5.7ns
    if (device == MT47H128M8CF) {
        MPDDRC->MPDDRC_TPR0 = MPDDRC_TPR0_TRAS(8)    // 40ns = 8
                            | MPDDRC_TPR0_TRCD(3)    // 12.5ns = 3
                            | MPDDRC_TPR0_TWR(3)     // 15ns = 3
                            | MPDDRC_TPR0_TRC(10)    // 55ns = 10
                            | MPDDRC_TPR0_TRP(3)     // 12.5 = 3
                            | MPDDRC_TPR0_TRRD(2)    // 8ns = 2
                            | MPDDRC_TPR0_TWTR(2)    // 10ns =2
                            | MPDDRC_TPR0_TMRD(2);   // 2 clock cycles
    }
    if (device == MT47H128M16) {
        MPDDRC->MPDDRC_TPR0 = MPDDRC_TPR0_TRAS(8)    // 45ns = 8
                            | MPDDRC_TPR0_TRCD(3)    // 15ns = 3
                            | MPDDRC_TPR0_TWR(3)     // 15ns = 3
                            | MPDDRC_TPR0_TRC(10)    // 55ns = 10
                            | MPDDRC_TPR0_TRP(3)     // 15ns = 3
                            | MPDDRC_TPR0_TRRD(3)    // 13ns = 3
                            | MPDDRC_TPR0_TWTR(2)    // 10ns =2
                            | MPDDRC_TPR0_TMRD(2);   // 2 clock cycles
    }
    if (device == MT47H64M16) {
        MPDDRC->MPDDRC_TPR0 = MPDDRC_TPR0_TRAS(8)    // 45ns = 8
                            | MPDDRC_TPR0_TRCD(3)    // 15ns = 3
                            | MPDDRC_TPR0_TWR(3)     // 15ns = 3
                            | MPDDRC_TPR0_TRC(10)    // 55ns = 10
                            | MPDDRC_TPR0_TRP(3)     // 15ns = 3
                            | MPDDRC_TPR0_TRRD(2)    // 10ns = 2
                            | MPDDRC_TPR0_TWTR(2)    // 7.5ns =2
                            | MPDDRC_TPR0_TMRD(2);   // 2 clock cycles
    }
    if (device == MT47H128M8CF) {
        MPDDRC->MPDDRC_TPR1 = MPDDRC_TPR1_TRFC(23)   // 127.5ns = 23
                            | MPDDRC_TPR1_TXSNR(25)  // 137.5ns = 25
                            | MPDDRC_TPR1_TXSRD(200) // 200ck 
                            | MPDDRC_TPR1_TXP(2) ;   // 2ck
    }
    if (device == MT47H128M16) {
        MPDDRC->MPDDRC_TPR1 = MPDDRC_TPR1_TRFC(35)   // 197.5ns = 35
                            | MPDDRC_TPR1_TXSNR(37)  // 207.5ns = 37
                            | MPDDRC_TPR1_TXSRD(200) // 200ck 
                            | MPDDRC_TPR1_TXP(2) ;   // 2ck
    }
    if (device == MT47H64M16) {
        MPDDRC->MPDDRC_TPR1 = MPDDRC_TPR1_TRFC(23)   // 127.5ns = 23
                            | MPDDRC_TPR1_TXSNR(25)  // 137.5ns = 25
                            | MPDDRC_TPR1_TXSRD(200) // 200ck 
                            | MPDDRC_TPR1_TXP(2) ;   // 2ck
    }
    if (device == MT47H128M8CF || device == MT47H128M16) {
        MPDDRC->MPDDRC_TPR2 = MPDDRC_TPR2_TXARD(8)   //8ck
                            | MPDDRC_TPR2_TXARDS(2)  //2ck
                            | MPDDRC_TPR2_TRPA(3)    //15ns = 3
                            | MPDDRC_TPR2_TRTP(2)    //7.5ns = 2
                            | MPDDRC_TPR2_TFAW(7) ;  //35ns = 7
    }
    if (device == MT47H64M16) {
        MPDDRC->MPDDRC_TPR2 = MPDDRC_TPR2_TXARD(8)   //8ck
                            | MPDDRC_TPR2_TXARDS(8)  //8ck
                            | MPDDRC_TPR2_TRPA(3)    //15ns = 3
                            | MPDDRC_TPR2_TRTP(2)    //8ns = 2
                            | MPDDRC_TPR2_TFAW(8) ;  //45ns = 8
    }
    MPDDRC->MPDDRC_LPR = 0;
    dummy_value  =  MPDDRC->MPDDRC_IO_CALIBR;
    dummy_value &= ~MPDDRC_IO_CALIBR_RDIV_Msk;
    dummy_value &= ~MPDDRC_IO_CALIBR_TZQIO_Msk;
    dummy_value |= MPDDRC_IO_CALIBR_RDIV_RZQ_60_RZQ_50;
    dummy_value |= MPDDRC_IO_CALIBR_TZQIO(5);                    // warning : needed for test with high temperature
    dummy_value |= MPDDRC_IO_CALIBR_EN_CALIB_ENABLE_CALIBRATION;
    MPDDRC->MPDDRC_IO_CALIBR = dummy_value;


/* Step 2: Program the features of DDR2-SDRAM device into the Timing Register.*/
    MPDDRC->MPDDRC_CR = ((device == MT47H64M16) ? MPDDRC_CR_NR_13_ROW_BITS : MPDDRC_CR_NR_14_ROW_BITS) |
                        MPDDRC_CR_NC_10_COL_BITS     |
                        MPDDRC_CR_CAS_DDR_CAS3       |
                        MPDDRC_CR_DLL_RESET_DISABLED |
                        MPDDRC_CR_DQMS_NOT_SHARED    |
                        MPDDRC_CR_ENRDM_OFF          |
                        MPDDRC_CR_NB_8_BANKS         |
                        MPDDRC_CR_NDQS_DISABLED      |
                        MPDDRC_CR_UNAL_SUPPORTED     |
                        MPDDRC_CR_OCD_DDR2_EXITCALIB;
    /* DDRSDRC Low-power Register */
    for (i = 0; i < 13300; i++)
        asm("nop");

/* Step 3: An NOP command is issued to the DDR2-SDRAM. Program the NOP command into
    the Mode Register, the application must set MODE to 1 in the Mode Register. */
    MPDDRC->MPDDRC_MR = MPDDRC_MR_MODE_NOP_CMD;
    /* Perform a write access to any DDR2-SDRAM address to acknowledge this command */
    *pDdr = 0;  /* Now clocks which drive DDR2-SDRAM device are enabled.*/

    /* A minimum pause of 200 ¦Ìs is provided to precede any signal toggle. (6 core cycles per iteration, core is at 396MHz: min 13200 loops) */
    for (i = 0; i < 13300; i++)
        asm("nop");

/* Step 4:  An NOP command is issued to the DDR2-SDRAM */
    MPDDRC->MPDDRC_MR = MPDDRC_MR_MODE_NOP_CMD;
    /* Perform a write access to any DDR2-SDRAM address to acknowledge this command.*/
    *pDdr = 0; /* Now CKE is driven high.*/
    /* wait 400 ns min */
    for (i = 0; i < 100; i++)
        asm("nop");

/* Step 5: An all banks precharge command is issued to the DDR2-SDRAM. */
    MPDDRC->MPDDRC_MR = MPDDRC_MR_MODE_PRCGALL_CMD;
    /* Perform a write access to any DDR2-SDRAM address to acknowledge this command.*/
    *pDdr = 0;
    /* wait 400 ns min */
    for (i = 0; i < 100; i++)
        asm("nop");

/* Step 6: An Extended Mode Register set (EMRS2) cycle is  issued to chose between commercialor high  temperature operations. */
    MPDDRC->MPDDRC_MR = MPDDRC_MR_MODE_EXT_LMR_CMD;
    if (device == MT47H64M16) {
        *((uint8_t *)(pDdr + BA1_16BIT)) = 0; /* The write address must be chosen so that BA[1] is set to 1 and BA[0] is set to 0. */
    } else {
        *((uint8_t *)(pDdr + BA1_32BIT)) = 0; /* The write address must be chosen so that BA[1] is set to 1 and BA[0] is set to 0. */
    }
    /* wait 2 cycles min */
    for (i = 0; i < 100; i++)
        asm("nop");

/* Step 7: An Extended Mode Register set (EMRS3) cycle is issued to set all registers to 0. */
    MPDDRC->MPDDRC_MR = MPDDRC_MR_MODE_EXT_LMR_CMD;
    if (device == MT47H64M16) {
        *((uint8_t *)(pDdr + BA1_16BIT + BA0_16BIT)) = 0;  /* The write address must be chosen so that BA[1] is set to 1 and BA[0] is set to 1.*/
    } else {
        *((uint8_t *)(pDdr + BA1_32BIT + BA0_32BIT)) = 0;  /* The write address must be chosen so that BA[1] is set to 1 and BA[0] is set to 1.*/
    }
    /* wait 2 cycles min */
    for (i = 0; i < 100; i++)
        asm("nop");

 /* Step 8:  An Extended Mode Register set (EMRS1) cycle is issued to enable DLL. */
    MPDDRC->MPDDRC_MR = MPDDRC_MR_MODE_EXT_LMR_CMD;
    if (device == MT47H64M16) {
        *((uint8_t *)(pDdr + BA0_16BIT)) = 0;  /* The write address must be chosen so that BA[1] is set to 0 and BA[0] is set to 1. */
    } else {
        *((uint8_t *)(pDdr + BA0_32BIT)) = 0;  /* The write address must be chosen so that BA[1] is set to 0 and BA[0] is set to 1. */
    }
    /* An additional 200 cycles of clock are required for locking DLL */
    for (i = 0; i < 10000; i++)
        asm("nop");

/* Step 9:  Program DLL field into the Configuration Register.*/
    MPDDRC->MPDDRC_CR |= MPDDRC_CR_DLL_RESET_ENABLED;

/* Step 10: A Mode Register set (MRS) cycle is issued to reset DLL. */
    MPDDRC->MPDDRC_MR = MPDDRC_MR_MODE_LMR_CMD;
    *(pDdr) = 0;  /* The write address must be chosen so that BA[1:0] bits are set to 0. */
    /* wait 2 cycles min */
    for (i = 0; i < 100; i++) {
        asm("nop");
    }

/* Step 11: An all banks precharge command is issued to the DDR2-SDRAM. */
    MPDDRC->MPDDRC_MR = MPDDRC_MR_MODE_PRCGALL_CMD;
    *(pDdr) = 0;  /* Perform a write access to any DDR2-SDRAM address to acknowledge this command */
    /* wait 2 cycles min */
    for (i = 0; i < 100; i++)
        asm("nop");

/* Step 12: Two auto-refresh (CBR) cycles are provided. Program the auto refresh command (CBR) into the Mode Register. */
    MPDDRC->MPDDRC_MR = MPDDRC_MR_MODE_RFSH_CMD;
    *(pDdr) = 0;  /* Perform a write access to any DDR2-SDRAM address to acknowledge this command */
    /* wait 2 cycles min */
    for (i = 0; i < 100; i++)
        asm("nop");

    /* Configure 2nd CBR. */
    MPDDRC->MPDDRC_MR = MPDDRC_MR_MODE_RFSH_CMD;
    *(pDdr) = 0;  /* Perform a write access to any DDR2-SDRAM address to acknowledge this command */
    /* wait 2 cycles min */
    for (i = 0; i < 100; i++)
        asm("nop");

/* Step 13: Program DLL field into the Configuration Register to low(Disable DLL reset). */
    MPDDRC->MPDDRC_CR &= ~MPDDRC_CR_DLL_RESET_ENABLED;

/* Step 14: A Mode Register set (MRS) cycle is issued to program the parameters of the DDR2-SDRAM devices. */
    MPDDRC->MPDDRC_MR = MPDDRC_MR_MODE_LMR_CMD;
    *(pDdr) = 0;  /* The write address must be chosen so that BA[1:0] are set to 0. */
    /* wait 2 cycles min */
    for (i = 0; i < 100; i++)
        asm("nop");

/* Step 15: Program OCD field into the Configuration Register to high (OCD calibration default). */
    MPDDRC->MPDDRC_CR |= MPDDRC_CR_OCD_DDR2_DEFAULT_CALIB;

/* Step 16: An Extended Mode Register set (EMRS1) cycle is issued to OCD default value. */
    MPDDRC->MPDDRC_MR = MPDDRC_MR_MODE_EXT_LMR_CMD;
    if (device == MT47H64M16) {
        *((uint8_t *)(pDdr + BA0_16BIT)) = 0;  /* The write address must be chosen so that BA[1] is set to 0 and BA[0] is set to 1.*/
    } else {
        *((uint8_t *)(pDdr + BA0_32BIT)) = 0;  /* The write address must be chosen so that BA[1] is set to 0 and BA[0] is set to 1.*/
    }
    /* wait 2 cycles min */
    for (i = 0; i < 100; i++)
        asm("nop");

/* Step 17: Program OCD field into the Configuration Register to low (OCD calibration mode exit). */
   MPDDRC->MPDDRC_CR &= ~(MPDDRC_CR_OCD_DDR2_DEFAULT_CALIB);

/* Step 18: An Extended Mode Register set (EMRS1) cycle is issued to enable OCD exit.*/
    MPDDRC->MPDDRC_MR = MPDDRC_MR_MODE_EXT_LMR_CMD;
    if (device == MT47H64M16) {
        *((uint8_t *)(pDdr + BA0_16BIT)) = 0;  /* The write address must be chosen so that BA[1] is set to 0 and BA[0] is set to 1.*/
    } else {
        *((uint8_t *)(pDdr + BA0_32BIT)) = 0;  /* The write address must be chosen so that BA[1] is set to 0 and BA[0] is set to 1.*/
    }
    /* wait 2 cycles min */
    for (i = 0; i < 100; i++)
        asm("nop");

/* Step 19,20: A mode Normal command is provided. Program the Normal mode into Mode Register. */
    MPDDRC->MPDDRC_MR = MPDDRC_MR_MODE_NORMAL_CMD;
    *(pDdr) = 0;

/* Step 21: Write the refresh rate into the count field in the Refresh Timer register. The DDR2-SDRAM device requires a refresh every 15.625 ¦Ìs or 7.81 ¦Ìs.
   With a 100MHz frequency, the refresh timer count register must to be set with (15.625 /100 MHz) = 1562 i.e. 0x061A or (7.81 /100MHz) = 781 i.e. 0x030d. */
    /* For MT47H64M16HR, The refresh period is 64ms (commercial), This equates to an average
       refresh rate of 7.8125¦Ìs (commercial), To ensure all rows of all banks are properly
       refreshed, 8192 REFRESH commands must be issued every 64ms (commercial) */
    /* ((64 x 10(^-3))/8192) x133 x (10^6) */
    MPDDRC->MPDDRC_RTR = MPDDRC_RTR_COUNT(688); /* Set Refresh timer 7.8125 us*/
    /* OK now we are ready to work on the DDRSDR */
    /* wait for end of calibration */
    for (i = 0; i < 500; i++)
        asm(" nop");
}

/**
 * \brief Configures LPDDR2
 *
 *  # 2£ºLPDDR2 (MT42L128M32D1GU-25): 
         * 8 Meg x 32 x 8 banks x 2 die 
         * 512MB x 2 chip = 1G
 */

void BOARD_Configure_LPDDR2(void)
{
    volatile uint32_t i;

    matrix_configure_slave_ddr();
    PMC->PMC_PCER0 = (1 << (ID_MPDDRC));
    PMC->PMC_SCER  |= PMC_SCER_DDRCK;

    MPDDRC->MPDDRC_RD_DATA_PATH = MPDDRC_RD_DATA_PATH_SHIFT_SAMPLING_SHIFT_THREE_CYCLES;

/* Initialization sequence STEP 1
      Program the memory device type into the Memory Device Register */

    /*   Memory device = LPDDR2 => MPDDRC_MD_MD_LPDDR2_SDRAM
      Data bus width = 32 bits => 0x0 (The system is in 64 bits, thus memory data bus width should be 32 bits) */
    MPDDRC->MPDDRC_MD = MPDDRC_MD_MD_LPDDR2_SDRAM;// LPDDR2

    MPDDRC->MPDDRC_CR = MPDDRC_CR_NC_10_COL_BITS |
                        MPDDRC_CR_NR_14_ROW_BITS |
                        MPDDRC_CR_CAS_DDR_CAS3   |
                        MPDDRC_CR_NB_8_BANKS     |
                        MPDDRC_CR_UNAL_SUPPORTED | // Unaligned accesses
                        MPDDRC_CR_ENRDM_ON;

    MPDDRC->MPDDRC_LPR = 0;
    MPDDRC->MPDDRC_LPDDR2_LPR|= MPDDRC_LPDDR2_LPR_DS(0x3);
    for (i = 0; i < 10000; i++)
        asm("nop");
                                                    // Delay loop (at least 200 us)
    // Bus Freq (MHz)  176MHz
    //T=1/F (ns) = 5.7ns

    MPDDRC->MPDDRC_TPR0 = MPDDRC_TPR0_TRAS(7) |       //40ns = 7
                          MPDDRC_TPR0_TRCD(3) |       //15ns = 3
                          MPDDRC_TPR0_TWR(3)  |       //15ns = 3
                          MPDDRC_TPR0_TRC(11) |       //60ns = 11
                          MPDDRC_TPR0_TRP(3)  |       //15ns = 3
                          MPDDRC_TPR0_TRRD(2) |       //11ns = 2
                          MPDDRC_TPR0_TWTR(2) |       //7.5ns = 2
                          MPDDRC_TPR0_TMRD(2);        //2ck

    MPDDRC->MPDDRC_TPR1 = MPDDRC_TPR1_TRFC(23)  |     //130ns = 23
                          MPDDRC_TPR1_TXSNR(25) |     //140ns = 25
                          MPDDRC_TPR1_TXSRD(25) |     //140ns = 25
                          MPDDRC_TPR1_TXP(2) ;        //2ck

    MPDDRC->MPDDRC_TPR2 = MPDDRC_TPR2_TXARD(2) |      //2ck
                          MPDDRC_TPR2_TXARDS(2)|      //2ck
                          MPDDRC_TPR2_TRPA(3)  |      //18ns = 3
                          MPDDRC_TPR2_TRTP(2)  |      //8ns = 2
                          MPDDRC_TPR2_TFAW(9);        //50ns = 9

/*  Initialization sequence STEP 3
    An NOP command is issued to the Low-power DDR2-SDRAM. Program the NOP
    command into the Mode Register, the application must set the MODE (MDDRC Command
    Mode) field to 1 in the Mode Register (see Section 8.1 on page 32). Perform a
    write access to any Low-power DDR2-SDRAM address to acknowledge this command.
    Now, clocks which drive Low-power DDR2-SDRAM devices are enabled.
    A minimum pause of 100 ns must be observed to precede any signal toggle. */

    MPDDRC->MPDDRC_MR = MPDDRC_MR_MODE_NOP_CMD;          // NOP to ENABLE CLOCK output
    *(uint32_t *)DDR_CS_ADDR = 0x00000000;           // Access to memory
    for (i = 0; i < 100; i++) 
        asm("nop");                                      // Delay loop (at least 100 ns)

/*  Initialization sequence STEP 4
    An NOP command is issued to the Low-power DDR2-SDRAM. Program the NOP
    command into the Mode Register, the application must set MODE to 1 in the Mode
    Register (see Section 8.1 on page 32). Perform a write access to any Low-power
    DDR2-SDRAM address to acknowledge this command. Now, CKE is driven high.
    A minimum pause of 200 us must be satisfied before Reset Command.
*/

    MPDDRC->MPDDRC_MR = MPDDRC_MR_MODE_NOP_CMD;      // NOP to drive CKE high
    *(uint32_t *)DDR_CS_ADDR = 0x00000000;       // Access to memory
    for (i = 0; i < 10000; i++)
        asm("nop");
                                                    // Delay loop (at least 200 us)

/*  Initialization sequence STEP 5
    A reset command is issued to the Low-power DDR2-SDRAM. Program
    LPDDR2_CMD in the MODE (MDDRC Command Mode) and MRS (Mode Register
    Select LPDDR2) field of the Mode Register, the application must set MODE to 7 and
    MRS to 63. (see Section 8.1 on page 32). Perform a write access to any Low-power
    DDR2-SDRAM address to acknowledge this command. Now, the reset command is issued.
    A minimum pause of 1us must be satisfied before any commands. */

    MPDDRC->MPDDRC_MR = MPDDRC_MR_MRS(0x3F) | MPDDRC_MR_MODE_LPDDR2_CMD;
    *(uint32_t *)DDR_CS_ADDR = 0x00000000;
    for (i = 0; i < 500; i++) 
        asm("nop");

/*  Initialization sequence STEP 6
    A Mode Register Read command is issued to the Low-power DDR2-SDRAM. Program
    LPPDR2_CMD in the MODE and MRS field of the Mode Register, the
    application must set MODE to 7 and must set MRS field to 0. (see Section 8.1 on
    page 32). Perform a write access to any Low-power DDR2-SDRAM address to
    acknowledge this command. Now, the Mode Register Read command is issued.
    A minimum pause of 10 us must be satisfied before any commands. */

    MPDDRC->MPDDRC_MR = MPDDRC_MR_MODE_LPDDR2_CMD | MPDDRC_MR_MRS(0x00);
    *(uint32_t *)DDR_CS_ADDR = 0x00000000;               // Access to memory
    for (i = 0; i < 5000; i++) 
        asm("nop");

/*  Initialization sequence STEP 7
    A calibration command is issued to the Low-power DDR2-SDRAM. Program the type
    of calibration into the Configuration Register, ZQ field, RESET value (see Section 8.3
    ”MPDDRC Configuration Register?on page 37). In the Mode Register, program the
    MODE field to LPDDR2_CMD value, and the MRS field; the application must set
    MODE to 7 and MRS to 10 (see Section 8.1 LPDDRC Mode Register?on page 34).
    Perform a write access to any Low-power DDR2-SDRAM address to acknowledge
    this command. Now, the ZQ Calibration command is issued. Program the type of calibration
    into the Configuration Register, ZQ field */

    MPDDRC->MPDDRC_CR &= ~MPDDRC_CR_ZQ_Msk;
    MPDDRC->MPDDRC_CR |= MPDDRC_CR_ZQ_RESET;
    MPDDRC->MPDDRC_MR = MPDDRC_MR_MODE_LPDDR2_CMD | MPDDRC_MR_MRS(0x0A);
                                                             // Mode Register Read  command. MODE = 0x7 and MRS = 0x0A
    *(uint32_t *)DDR_CS_ADDR = 0x00000000;                // Access to memory
    for (i = 0; i < 500; i++) 
        asm("nop");
    MPDDRC->MPDDRC_CR &= ~MPDDRC_CR_ZQ_Msk;
    MPDDRC->MPDDRC_CR |= MPDDRC_CR_ZQ_SHORT;

/*  Initialization sequence STEP 8
    A Mode Register Write command is issued to the Low-power DDR2-SDRAM. Program
    LPPDR2_CMD in the MODE and MRS field in the Mode Register, the
    application must set MODE to 7 and must set MRS field to 0.5 (see Section 8.1 on
    page 32). The Mode Register Write command cycle is issued to program the parameters
    of the Low-power DDR2-SDRAM devices, in particular burst length. Perform a
    write access to any Low-power DDR2-SDRAM address to acknowledge this command.
    Now, the Mode Register Write command is issued. */

    MPDDRC->MPDDRC_MR = MPDDRC_MR_MODE_LPDDR2_CMD | MPDDRC_MR_MRS(0x01);
    *(uint32_t *)DDR_CS_ADDR = 0x00000000;               // Access to memory
    for (i = 0; i < 500; i++)
        asm("nop");

/*  Initialization sequence STEP 9
    Mode Register Write Command is issued to the Low-power DDR2-SDRAM. Program
    LPPDR2_CMD in the MODE and MRS field in the Mode Register, the
    application must set MODE to 7 and must set MRS field to 2. (see Section 8.1 on
    page 32). The Mode Register Write command cycle is issued to program the parameters
    of the Low-power DDR2-SDRAM devices, in particular CAS latency. Perform a
    write access to any Low-power DDR2-SDRAM address to acknowledge this command.
    Now, the Mode Register Write command is issued. */

    MPDDRC->MPDDRC_MR = MPDDRC_MR_MODE_LPDDR2_CMD | MPDDRC_MR_MRS(0x02);
    *(uint32_t *)DDR_CS_ADDR  = 0x00000000;               // Access to memory
    for (i = 0; i < 500; i++)
        asm("nop");

/*  Initialization sequence STEP 10
    A Mode Register Write Command is issued to the Low-power DDR2-SDRAM. Program
    LPPDR2_CMD in the MODE and MRS field of the Mode Register, the
    application must set MODE to 7 and must set MRS field to 3. (see Section 8.1 on
    page 32). The Mode Register Write command cycle is issued to program the parameters
    of the Low-power DDR2-SDRAM devices, in particular Drive Strength and Slew
    Rate. Perform a write access to any Low-power DDR2-SDRAM address to acknowledge
    this command. Now, the Mode Register Write command is issued. */

    MPDDRC->MPDDRC_MR = MPDDRC_MR_MODE_LPDDR2_CMD | MPDDRC_MR_MRS(0x03); //0x00000307;
    *(uint32_t *)DDR_CS_ADDR  = 0x00000000;               // Access to memory
    for (i = 0; i < 1000; i++)
        asm("nop");

/* Initialization sequence STEP 11
    A Mode Register Write Command is issued to the Low-power DDR2-SDRAM. Program
    LPPDR2_CMD in the MODE and MRS field of the Mode Register, the
    application must set MODE to 7 and must set MRS field to 16. (see Section 8.1 on
    page 32). Mode Register Write command cycle is issued to program the parameters
    of the Low-power DDR2-SDRAM devices, in particular Partial Array Self Refresh
   (PASR). Perform a write access to any Low-power DDR2-SDRAM address to
    acknowledge this command. Now, the Mode Register Write command is issued.*/

    MPDDRC->MPDDRC_MR = MPDDRC_MR_MODE_LPDDR2_CMD | MPDDRC_MR_MRS(0x10);// 0x00001007;
    *(uint32_t *)DDR_CS_ADDR = 0x00000000;                          // Access to memory
    for (i = 0; i < 500; i++)
        asm("nop");

/*  Initialization sequence STEP 12
    Write the refresh rate into the COUNT field in the Refresh Timer register (see page
    33). (Refresh rate = delay between refresh cycles). The Low-power DDR2-SDRAM
    device requires a refresh every 7.81 ìs. With a 100 MHz frequency, the refresh timer
    count register must to be set with (7.81/100 MHz) = 781 i.e. 0x030d. */
    MPDDRC->MPDDRC_RTR &= ~MPDDRC_RTR_COUNT_Msk;
    MPDDRC->MPDDRC_RTR |= MPDDRC_RTR_COUNT(1373);
    MPDDRC->MPDDRC_MR  = 0x00000000;                        // Set Normal mode
    *(uint32_t *)DDR_CS_ADDR = 0x00000000;              // Perform
    for (i = 0; i < 500; i++)
        asm("nop");
 
    /* Launch short ZQ calibration */
    MPDDRC->MPDDRC_CR &= ~MPDDRC_CR_ZQ_Msk;                   // Enable short calibration in the CR
    MPDDRC->MPDDRC_CR |=  MPDDRC_CR_ZQ_SHORT;
    MPDDRC->MPDDRC_CR |=  MPDDRC_CR_DLL_RESET_ENABLED;
    *(uint32_t *)DDR_CS_ADDR = 0x00000000;              // Perform

    /* Calculate ZQS: search for tZQCS in the memory datasheet => tZQCS = 180 ns*/
    MPDDRC->MPDDRC_LPDDR2_TIM_CAL = MPDDRC_LPDDR2_TIM_CAL_ZQCS(12);
    // Launch short ZQ calibration
    MPDDRC->MPDDRC_CR &= ~(MPDDRC_CR_ZQ_Msk);        // Enable short calibration in the CR
    MPDDRC->MPDDRC_CR |= (MPDDRC_CR_ZQ_LONG);
    *(uint32_t *)DDR_CS_ADDR = 0x00000000;       // Perform
    // Calculate ZQS: search for tZQCS in the memory datasheet => tZQCS = 180 ns
    MPDDRC->MPDDRC_LPDDR2_TIM_CAL = MPDDRC_LPDDR2_TIM_CAL_ZQCS(12);
}

/** \brief Configures the EBI for NandFlash access at 133Mhz.
 */
void BOARD_ConfigureNandFlash( uint8_t busWidth )
{
    matrix_configure_slave_nand();
    HSMC->HSMC_CS_NUMBER[3].HSMC_SETUP = 0
                    | HSMC_SETUP_NWE_SETUP(2)
                    | HSMC_SETUP_NCS_WR_SETUP(2)
                    | HSMC_SETUP_NRD_SETUP(2)
                    | HSMC_SETUP_NCS_RD_SETUP(2);

    HSMC->HSMC_CS_NUMBER[3].HSMC_PULSE = 0
                    | HSMC_PULSE_NWE_PULSE(7)
                    | HSMC_PULSE_NCS_WR_PULSE(7)
                    | HSMC_PULSE_NRD_PULSE(7)
                    | HSMC_PULSE_NCS_RD_PULSE(7);

    HSMC->HSMC_CS_NUMBER[3].HSMC_CYCLE = 0
                    | HSMC_CYCLE_NWE_CYCLE(13)
                    | HSMC_CYCLE_NRD_CYCLE(13);

    HSMC->HSMC_CS_NUMBER[3].HSMC_TIMINGS = HSMC_TIMINGS_TCLR(3)
                                       | HSMC_TIMINGS_TADL(27)
                                       | HSMC_TIMINGS_TAR(3)
                                       | HSMC_TIMINGS_TRR(6)
                                       | HSMC_TIMINGS_TWB(5)
                                       | HSMC_TIMINGS_RBNSEL(3)
                                       |(HSMC_TIMINGS_NFSEL);
    HSMC->HSMC_CS_NUMBER[3].HSMC_MODE = HSMC_MODE_READ_MODE |
                                     HSMC_MODE_WRITE_MODE |
                                     ((busWidth == 8 )? HSMC_MODE_DBW_BIT_8 :HSMC_MODE_DBW_BIT_16) |
                                      HSMC_MODE_TDF_CYCLES(1);
}

void BOARD_ConfigureNorFlash( uint8_t busWidth )
{
    uint32_t dbw;
    PMC_EnablePeripheral(ID_HSMC);
    if (busWidth == 8)
    {
        dbw = HSMC_MODE_DBW_BIT_8;
    }
    else {
        dbw = HSMC_MODE_DBW_BIT_16;
    }
    /* Configure SMC, NCS0 is assigned to a norflash */
    HSMC->HSMC_CS_NUMBER[0].HSMC_SETUP = 0x00020001;
    HSMC->HSMC_CS_NUMBER[0].HSMC_PULSE = 0x0B0B0A0A;
    HSMC->HSMC_CS_NUMBER[0].HSMC_CYCLE = 0x000E000B;
    HSMC->HSMC_CS_NUMBER[0].HSMC_TIMINGS = 0x00000000;
    HSMC->HSMC_CS_NUMBER[0].HSMC_MODE  = HSMC_MODE_WRITE_MODE
                                    | HSMC_MODE_READ_MODE
                                    | dbw
                                    | HSMC_MODE_EXNW_MODE_DISABLED
                                    | HSMC_MODE_TDF_CYCLES(1);

}
