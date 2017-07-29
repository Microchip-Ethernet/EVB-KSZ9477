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

/*----------------------------------------------------------------------------
 *        Definiation
 *----------------------------------------------------------------------------*/
 
#define DDR2_SDRAM      0x06
#define NC_DDR10_SDR9   0x01
#define NR_ROW_BIT_12   0x01
#define NR_ROW_BIT_13   0x02
#define SDR_SDRAM       0x01

#define DDRC2_MODE_NORMAL_CMD       (0x0) // (HDDRSDRC2) Normal Mode
#define DDRC2_MODE_NOP_CMD          (0x1) // (HDDRSDRC2) Issue a NOP Command at every access
#define DDRC2_MODE_PRCGALL_CMD      (0x2) // (HDDRSDRC2) Issue a All Banks Precharge Command at every access
#define DDRC2_MODE_LMR_CMD          (0x3) // (HDDRSDRC2) Issue a Load Mode Register at every access
#define DDRC2_MODE_RFSH_CMD         (0x4) // (HDDRSDRC2) Issue a Refresh
#define DDRC2_MODE_EXT_LMR_CMD      (0x5) // (HDDRSDRC2) Issue an Extended Load Mode Register
#define DDRC2_MODE_DEEP_CMD         (0x6) // (HDDRSDRC2) Enter Deep Power Mode
#define DDRC2_MODE_Reserved         (0x7) // (HDDRSDRC2) Reserved value

#define ADDR_CCFG_EBICSA  (uint32_t *)(0xFFFFDE00 + 0x118)

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Changes the mapping of the chip so that the remap area mirrors the
 * internal ROM or the EBI CS0.
 */
void BOARD_RemapRom( void )
{
    MATRIX->MATRIX_MRCR = 0;
}

/**
 * \brief Changes the mapping of the chip so that the remap area mirrors the
 * internal RAM.
 */

void BOARD_RemapRam( void )
{
    MATRIX->MATRIX_MRCR = MATRIX_MRCR_RCB0 | MATRIX_MRCR_RCB1;
}

/**
 * \brief Initialize Vdd EBI drive
 * \param 0: 1.8V 1: 3.3V
 */
void BOARD_ConfigureVddMemSel( uint8_t VddMemSel )
{

    if (VddMemSel == 1) {
         *ADDR_CCFG_EBICSA |=  (1u << 16);
         *ADDR_CCFG_EBICSA &= ~(1u << 17);
    }
    else {
         *ADDR_CCFG_EBICSA &= ~(1u << 16);
         *ADDR_CCFG_EBICSA &= ~(1u << 17);
    }
}
 
/**
 * \brief Configures DDR2 (MT47H64M16HR-3 128MB)
 MT47H64M16HR : 8 Meg x 16 x 8 banks
 Refresh count: 8K
 Row address: A[12:0] (8K)
 Column address A[9:0] (1K)
 Bank address BA[2:0] a(24,25) (8) 
 */

void BOARD_ConfigureDdram( void )
{
    volatile uint8_t *pDdr = (uint8_t *) EBI_DDRSDRC_ADDR;
    uint32_t i;
    volatile uint32_t cr = 0;

 
    *ADDR_CCFG_EBICSA = 0x01020002; /* EBI Chip Select 1 is assigned to the DDR2SDR Controller */

    /* Enable DDR2 clock x2 in PMC */
    PMC->PMC_SCER = PMC_SCER_DDRCK;
    
    /* Disable anticipated read */
    i = DDRSDRC->DDRSDRC_HS;
    DDRSDRC->DDRSDRC_HS = i | DDRSDRC_HS_DIS_ANTICIP_READ;

    /* Step 1: Program the memory device type */

    DDRSDRC->DDRSDRC_MD = DDRSDRC_MD_MD(DDR2_SDRAM) | DDRSDRC_MD_DBW;

    /* Step 2:
       1. Program the features of DDR2-SDRAM device into the Configuration Register.
       2. Program the features of DDR2-SDRAM device into the Timing Register HDDRSDRC2_T0PR.
       3. Program the features of DDR2-SDRAM device into the Timing Register HDDRSDRC2_T1PR.
       4. Program the features of DDR2-SDRAM device into the Timing Register HDDRSDRC2_T2PR. */

    DDRSDRC->DDRSDRC_CR = DDRSDRC_CR_NC(NC_DDR10_SDR9)  // 10 column bits (1K) /
                        | DDRSDRC_CR_NR(NR_ROW_BIT_13)  // 13 row bits    (8K)
                        | DDRSDRC_CR_CAS(3)             // CAS Latency 3
                        | (0x1 << 20);                  // (DDRSDRC) DDR2 8 bank

    /* assume timings for 7.5ns min clock period */

    DDRSDRC->DDRSDRC_TPR0 = DDRSDRC_TPR0_TRAS(6)    //  6 * 7.5 = 45 ns
                          | DDRSDRC_TPR0_TRCD(2)    //  2 * 7.5 = 15 ns
                          | DDRSDRC_TPR0_TWR(2)     //  2 * 7.5 = 15 ns
                          | DDRSDRC_TPR0_TRC(8)     //  8 * 7.5 = 60 ns
                          | DDRSDRC_TPR0_TRP(2)     //  2 * 7.5 = 15 ns
                          | DDRSDRC_TPR0_TRRD(2)    //  2 * 7.5 = 15 ns
                          | DDRSDRC_TPR0_TWTR(1)    //  2 clock cycle
                          | DDRSDRC_TPR0_TMRD(2);   //  2 clock cycles

    DDRSDRC->DDRSDRC_TPR1 = DDRSDRC_TPR1_TRFC(18)   // 18 * 7.5 = 135 ns (min 127.5 ns for 1Gb DDR)
                          | DDRSDRC_TPR1_TXSNR(19)  // 19 * 7.5 > 142.5ns TXSNR: Exit self refresh delay to non read command
                          | DDRSDRC_TPR1_TXSRD(200) // min 200 clock cycles, TXSRD: Exit self refresh delay to Read command
                          | DDRSDRC_TPR1_TXP(2);    //  2 * 7.5 = 15 ns

    DDRSDRC->DDRSDRC_TPR2 = DDRSDRC_TPR2_TXARD(2)   //  min 2 clock cycles
                          | DDRSDRC_TPR2_TXARDS(7)  //  min 7 clock cycles
                          | DDRSDRC_TPR2_TRPA(3)    //  min 18ns
                          | DDRSDRC_TPR2_TRTP(1) ;  //  2 * 7.5 = 15 ns (min 7.5ns)

    /* Step 3: An NOP command is issued to the DDR2-SDRAM to enable clock. */
    DDRSDRC->DDRSDRC_MR = DDRSDRC_MR_MODE(DDRC2_MODE_NOP_CMD);
    /* Perform a write access to any DDR2-SDRAM address to acknowledge this command.*/
    *pDdr = 0;  /* Now clocks which drive DDR2-SDRAM device are enabled.*/
    /* A minimum pause of 200 ¦Ìs is provided to precede any signal toggle. (6 core cycles per iteration, core is at 396MHz: min 13200 loops) */
    for (i = 0; i < 13300; i++) {
        asm("nop");
    }

    /* Step 4:  An NOP command is issued to the DDR2-SDRAM */
    DDRSDRC->DDRSDRC_MR = DDRSDRC_MR_MODE(DDRC2_MODE_NOP_CMD);
    /* Perform a write access to any DDR2-SDRAM address to acknowledge this command.*/
    *pDdr = 0; /* Now CKE is driven high.*/
    /* wait 400 ns min */
    for (i = 0; i < 100; i++) {
        asm("nop");
    }

    /* Step 5: An all banks precharge command is issued to the DDR2-SDRAM. */
    DDRSDRC->DDRSDRC_MR = DDRSDRC_MR_MODE(DDRC2_MODE_PRCGALL_CMD);
    /* Perform a write access to any DDR2-SDRAM address to acknowledge this command.*/
    *pDdr = 0;
    /* wait 400 ns min */
    for (i = 0; i < 100; i++) {
        asm("nop");
    }

    /* Step 6: An Extended Mode Register set (EMRS2) cycle is  issued to chose between commercialor high  temperature operations. */
    DDRSDRC->DDRSDRC_MR = DDRSDRC_MR_MODE(DDRC2_MODE_EXT_LMR_CMD);
     *((uint8_t *)(pDdr + 0x2000000)) = 0; /* The write address must be chosen so that BA[1] is set to 1 and BA[0] is set to 0. */
    /* wait 2 cycles min */
    for (i = 0; i < 100; i++) {
        asm("nop");
    }

    /* Step 7: An Extended Mode Register set (EMRS3) cycle is issued to set all registers to 0. */
    DDRSDRC->DDRSDRC_MR = DDRSDRC_MR_MODE(DDRC2_MODE_EXT_LMR_CMD);
    *((uint8_t *)(pDdr + 0x3000000)) = 0;  /* The write address must be chosen so that BA[1] is set to 1 and BA[0] is set to 1.*/
    /* wait 2 cycles min */
    for (i = 0; i < 100; i++) {
        asm("nop");
    }

    /* Step 8:  An Extended Mode Register set (EMRS1) cycle is issued to enable DLL. */
    DDRSDRC->DDRSDRC_MR = DDRSDRC_MR_MODE(DDRC2_MODE_EXT_LMR_CMD);
    *((uint8_t *)(pDdr + 0x1000000)) = 0;  /* The write address must be chosen so that BA[1] is set to 0 and BA[0] is set to 1. */
    /* An additional 200 cycles of clock are required for locking DLL */
    for (i = 0; i < 10000; i++) {
        asm("nop");
    }

    /* Step 9:  Program DLL field into the Configuration Register.*/
    cr = DDRSDRC->DDRSDRC_CR;
    DDRSDRC->DDRSDRC_CR = cr | 	DDRSDRC_CR_DLL;

    /* Step 10: A Mode Register set (MRS) cycle is issued to reset DLL. */
    DDRSDRC->DDRSDRC_MR = DDRSDRC_MR_MODE(DDRC2_MODE_LMR_CMD);
    *(pDdr) = 0;  /* The write address must be chosen so that BA[1:0] bits are set to 0. */
    /* wait 2 cycles min */
    for (i = 0; i < 100; i++) {
        asm("nop");
    }

    /* Step 11: An all banks precharge command is issued to the DDR2-SDRAM. */
    DDRSDRC->DDRSDRC_MR = DDRSDRC_MR_MODE(DDRC2_MODE_PRCGALL_CMD);
    *(pDdr) = 0;  /* Perform a write access to any DDR2-SDRAM address to acknowledge this command */
    /* wait 2 cycles min */
    for (i = 0; i < 100; i++) {
        asm("nop");
    }

    /* Step 12: Two auto-refresh (CBR) cycles are provided. Program the auto refresh command (CBR) into the Mode Register. */
    DDRSDRC->DDRSDRC_MR = DDRSDRC_MR_MODE(DDRC2_MODE_RFSH_CMD);
    *(pDdr) = 0;  /* Perform a write access to any DDR2-SDRAM address to acknowledge this command */
    /* wait 2 cycles min */
    for (i = 0; i < 100; i++) {
        asm("nop");
    }
    /* Configure 2nd CBR. */
    DDRSDRC->DDRSDRC_MR = DDRSDRC_MR_MODE(DDRC2_MODE_RFSH_CMD);
    *(pDdr) = 0;  /* Perform a write access to any DDR2-SDRAM address to acknowledge this command */
    /* wait 2 cycles min */
    for (i = 0; i < 100; i++) {
        asm("nop");
    }

    /* Step 13: Program DLL field into the Configuration Register to low(Disable DLL reset). */
    cr = DDRSDRC->DDRSDRC_CR;
    DDRSDRC->DDRSDRC_CR = cr & (~DDRSDRC_CR_DLL);

    /* Step 14: A Mode Register set (MRS) cycle is issued to program the parameters of the DDR2-SDRAM devices. */
    DDRSDRC->DDRSDRC_MR = DDRSDRC_MR_MODE(DDRC2_MODE_LMR_CMD);
    *(pDdr) = 0;  /* The write address must be chosen so that BA[1:0] are set to 0. */
    /* wait 2 cycles min */
    for (i = 0; i < 100; i++) {
        asm("nop");
    }
   
    /* Step 15: Program OCD field into the Configuration Register to high (OCD calibration default). */
    cr = DDRSDRC->DDRSDRC_CR;
    DDRSDRC->DDRSDRC_CR = cr | DDRSDRC_CR_OCD(0x07);

    /* Step 16: An Extended Mode Register set (EMRS1) cycle is issued to OCD default value. */
    DDRSDRC->DDRSDRC_MR = DDRSDRC_MR_MODE(DDRC2_MODE_EXT_LMR_CMD);
    *((uint8_t *)(pDdr + 0x1000000)) = 0;  /* The write address must be chosen so that BA[1] is set to 0 and BA[0] is set to 1.*/
    /* wait 2 cycles min */
    for (i = 0; i < 100; i++) {
        asm("nop");
    }

    /* Step 17: Program OCD field into the Configuration Register to low (OCD calibration mode exit). */
    cr = DDRSDRC->DDRSDRC_CR;
    DDRSDRC->DDRSDRC_CR = cr & (~DDRSDRC_CR_OCD(0x07));

    /* Step 18: An Extended Mode Register set (EMRS1) cycle is issued to enable OCD exit.*/
    DDRSDRC->DDRSDRC_MR = DDRSDRC_MR_MODE(DDRC2_MODE_EXT_LMR_CMD);
    *((uint8_t *)(pDdr + 0x1000000)) = 0;  /* The write address must be chosen so that BA[1] is set to 0 and BA[0] is set to 1.*/
    /* wait 2 cycles min */
    for (i = 0; i < 100; i++) {
        asm("nop");
    }

    /* Step 19,20: A mode Normal command is provided. Program the Normal mode into Mode Register. */
    DDRSDRC->DDRSDRC_MR = DDRSDRC_MR_MODE(DDRC2_MODE_NORMAL_CMD);       
    *(pDdr) = 0;

    /* Step 21: Write the refresh rate into the count field in the Refresh Timer register. The DDR2-SDRAM device requires a refresh every 15.625 ¦Ìs or 7.81 ¦Ìs. 
    With a 100MHz frequency, the refresh timer count register must to be set with (15.625 /100 MHz) = 1562 i.e. 0x061A or (7.81 /100MHz) = 781 i.e. 0x030d. */

    DDRSDRC->DDRSDRC_RTR = DDRSDRC_RTR_COUNT(0x00000411); /* Set Refresh timer 7.8125 us*/
    /* Read optimization" shall be un-selected on this revision. */
    DDRSDRC->DDRSDRC_HS = 0x04;
    /* OK now we are ready to work on the DDRSDR */
    /* wait for end of calibration */
    for (i = 0; i < 500; i++) {
        asm("    nop");
    }
}


/**
 * \brief Configures the EBI for Sdram (LPSDR Micron MT48H8M16) access.
 */
void BOARD_ConfigureSdram( void )
{
    static const Pin pinsSdram[] = {EBI_SDRAM_PINS};
    uint32_t i;

    /* Configure PIO */
    PIO_Configure(pinsSdram, 1);

    *ADDR_CCFG_EBICSA = 0x00020102; /* EBI Chip Select 1 is assigned to the DDR2SDR Controller */

    /* Enable DDR2 clock x2 in PMC */
    PMC->PMC_SCER = PMC_SCER_DDRCK;

    /* The initialization sequence is generated by software. 
    The low-power DDR1-SDRAM devices are initialized by the following sequence: */

    /* Step 1. Program the memory device type into the Memory Device Register */
    DDRSDRC->DDRSDRC_MD = DDRSDRC_MD_MD(SDR_SDRAM);  
  
    /* 2. Program the features of the SDR-SDRAM device into the Timing Register , 
    and into the Configuration Register.*/
     DDRSDRC->DDRSDRC_CR = DDRSDRC_CR_NC(NC_DDR10_SDR9)  // 9 column bits 
                        | DDRSDRC_CR_NR(NR_ROW_BIT_12)   // 12 row bits (4K)
                        | DDRSDRC_CR_CAS(3)              // CAS Latency 3
                        | DDRSDRC_CR_DIS_DLL 
                        | DDRSDRC_CR_DS
                        | (0x0 << 20);                   // (DDRSDRC) 4 bank

    /* assume timings for 7.5ns min clock period */

    DDRSDRC->DDRSDRC_TPR0 = DDRSDRC_TPR0_TRAS(6)    //  6 * 7.5 = 45 ns ( min 45ns)
                          | DDRSDRC_TPR0_TRCD(4)    //  4 * 7.5 = 30 ns (min 19.2 ns)
                          | DDRSDRC_TPR0_TWR(3)     //  3 * 7.5 = 22.5 ns (min 15 ns)
                          | DDRSDRC_TPR0_TRC(10)    //  10 * 7.5 = 75 ns (min 67.5 ns)
                          | DDRSDRC_TPR0_TRP(4)     //  4 * 7.5 = 30 ns (min 19.2 ns)
                          | DDRSDRC_TPR0_TRRD(3)    //  3 * 7.5 = 22.5 ns (min 15 ns)
                          | DDRSDRC_TPR0_TWTR(2)    //  2 clock cycle
                          | DDRSDRC_TPR0_TMRD(3);   //  3 clock cycles

    DDRSDRC->DDRSDRC_TPR1 = DDRSDRC_TPR1_TRFC(11)   // 11 * 7.5 = 82.5 ns (min 75 ns)
                          | DDRSDRC_TPR1_TXSNR(0)   //  This field is unique to DDR-SDRAM devices
                          | DDRSDRC_TPR1_TXSRD(0)   // This field is unique to DDR-SDRAM devices
                          | DDRSDRC_TPR1_TXP(0);    // This field is unique to Low-power DDR-SDRAM devices and DDR2-SDRAM devices

    /* Step 3. For low-power SDRAM, temperature-compensated self refresh (TCSR), 
    drive strength (DS) and partial array self refresh (PASR) must be set in the Low-power Register.*/
    DDRSDRC->DDRSDRC_LPR = 0;

    /* A minimum pause of 200 ¦Ìs is provided to precede any signal toggle. (6 core cycles per iteration, core is at 396MHz: min 13200 loops) */
    for (i = 0; i < 13300; i++) {
        asm("nop");
    }

    /* Step 4. A NOP command is issued to the SDR-SDRAM. Program NOP command into Mode Register, the application must 
    set Mode to 1 in the Mode Register. Perform a write access to any SDR-SDRAM address to acknowledge this command. 
    Now the clock which drives SDR-SDRAM device is enabled.*/
    DDRSDRC->DDRSDRC_MR = DDRSDRC_MR_MODE(DDRC2_MODE_NOP_CMD);
    *(uint32_t *)(EBI_DDRSDRC_ADDR) = 0;
    for (i = 0; i < 13302; i++) {
        asm("nop");
    }

    /* Step 5. An all banks precharge command is issued to the SDR-SDRAM. Program all banks
       precharge command into Mode Register, the application must set Mode to 2 in the
       Mode Register . Perform a write access to any SDRSDRAM address to acknowledge this command. */
    DDRSDRC->DDRSDRC_MR = DDRSDRC_MR_MODE(DDRC2_MODE_PRCGALL_CMD);
    *(uint32_t *)(EBI_DDRSDRC_ADDR + 2) = 0x2;  
   
    /* Step 6. Eight auto-refresh (CBR) cycles are provided. Program the auto refresh command
    (CBR) into Mode Register, the application must set Mode to 4 in the Mode Register.
    Once in the idle state, two AUTO REFRESH cycles must be performed. */
    DDRSDRC->DDRSDRC_MR = DDRSDRC_MR_MODE(DDRC2_MODE_RFSH_CMD);
    *(uint32_t *)(EBI_DDRSDRC_ADDR + 4 ) = 0x4; 
  
    DDRSDRC->DDRSDRC_MR = DDRSDRC_MR_MODE(DDRC2_MODE_RFSH_CMD);
    *(uint32_t *)(EBI_DDRSDRC_ADDR + 8 ) = 0x8; 
  
    /* Step 7. A Mode Register set (MRS) cycle is issued to program the parameters of the SDRSDRAM
    devices, in particular CAS latency and burst length. */ 
    DDRSDRC->DDRSDRC_MR = DDRSDRC_MR_MODE(DDRC2_MODE_LMR_CMD);
    *(uint32_t *)(EBI_DDRSDRC_ADDR + 0x10) = 0x10; 

    /* Step 8. For low-power SDR-SDRAM initialization, an Extended Mode Register set (EMRS)
    cycle is issued to program the SDR-SDRAM parameters (TCSR, PASR, DS). The write
    address must be chosen so that BA[1] is set to 1 and BA[0] is set to 0 */ 
    DDRSDRC->DDRSDRC_MR = DDRSDRC_MR_MODE(DDRC2_MODE_EXT_LMR_CMD);
    *((uint32_t *)(EBI_DDRSDRC_ADDR + 0x1000000)) = 0;  

    /* Step 9. The application must go into Normal Mode, setting Mode to 0 in the Mode Register
    and perform a write access at any location in the SDRAM to acknowledge this command. */
    DDRSDRC->DDRSDRC_MR = DDRSDRC_MR_MODE(DDRC2_MODE_NORMAL_CMD); 
    *(uint32_t *)(EBI_DDRSDRC_ADDR + 0x12 ) = 0x12;

   /* Step 10. Write the refresh rate into the count field in the DDRSDRC Refresh Timer register */
   DDRSDRC->DDRSDRC_RTR = DDRSDRC_RTR_COUNT(1170); /* Set Refresh timer 15.625 us*/
}

/** \brief Configures the EBI for NandFlash access at 133Mhz.
 */
void BOARD_ConfigureNandFlash( uint8_t busWidth )
{
#ifdef BOARD_REV_A_VB
    *ADDR_CCFG_EBICSA &= ~(1u << 8);
    *ADDR_CCFG_EBICSA |= (1 << 3)   /* EBI Chip Select 3 is assigned to the Static Memory Controller and the NAND Flash Logic is activated */
                      | (1 << 9)
                      | (1 << 17);  /* HIGH drive (default). Data Bus + Memory load capacitance < TBD pF. */
                   // | (1 << 25);  /* DDR Multi-port is enabled, performances are increased when using DDR2 (or LP-DDR) and 8-bit NAND Flash */
#endif

#ifdef BOARD_REV_A_EK
#if 1
    *ADDR_CCFG_EBICSA |= (1 << 3)   /* EBI Chip Select 3 is assigned to the Static Memory Controller and the NAND Flash Logic is activated */
                      | (1 << 8)
                      | (1 << 9)
                      | (1 << 17)   /* HIGH drive (default). Data Bus + Memory load capacitance < TBD pF. */
                      | (1 << 24);  /* NAND Flash I/O are connected to D16-D31 in case VDDIOM do not equals VDDNF */
#endif
   //*ADDR_CCFG_EBICSA  = 0x0102020A;
#endif

#ifdef BOARD_REV_B_EK
    *ADDR_CCFG_EBICSA |= (1 << 3)   /* EBI Chip Select 3 is assigned to the Static Memory Controller and the NAND Flash Logic is activated */
                      | (1 << 17)   /* HIGH drive (default). Data Bus + Memory load capacitance < TBD pF. */
                      | (1 << 24);  /* NAND Flash I/O are connected to D16-D31 in case VDDIOM do not equals VDDNF */
                   // | (1 << 25);  /* DDR Multi-port is enabled, performances are increased when using DDR2 (or LP-DDR) and 8-bit NAND Flash */
#endif
    SMC->SMC_CS_NUMBER[3].SMC_SETUP = 0
                    | SMC_SETUP_NWE_SETUP(1)
                    | SMC_SETUP_NCS_WR_SETUP(0)
                    | SMC_SETUP_NRD_SETUP(2)
                    | SMC_SETUP_NCS_RD_SETUP(0);

    SMC->SMC_CS_NUMBER[3].SMC_PULSE = 0
                    | SMC_PULSE_NWE_PULSE(3)
                    | SMC_PULSE_NCS_WR_PULSE(5)
                    | SMC_PULSE_NRD_PULSE(4)
                    | SMC_PULSE_NCS_RD_PULSE(6);

    SMC->SMC_CS_NUMBER[3].SMC_CYCLE = 0
                    | SMC_CYCLE_NWE_CYCLE(5)
                    | SMC_CYCLE_NRD_CYCLE(7);
    SMC->SMC_CS_NUMBER[3].SMC_MODE = SMC_MODE_READ_MODE | SMC_MODE_WRITE_MODE | SMC_MODE_DBW(busWidth/16) | SMC_MODE_TDF_CYCLES(1);    
}

void BOARD_ConfigureNorFlash( uint8_t busWidth )
{
    *ADDR_CCFG_EBICSA = 0x00020002; /* EBI Chip Select 1 is assigned to the DDR2SDR Controller */
    /* Configure SMC, NCS0 is assigned to a norflash */
    SMC->SMC_CS_NUMBER[0].SMC_SETUP = 0x00000002;
    SMC->SMC_CS_NUMBER[0].SMC_PULSE = 0x0A0A0A06;
    SMC->SMC_CS_NUMBER[0].SMC_CYCLE = 0x000A000A;
    SMC->SMC_CS_NUMBER[0].SMC_MODE  = SMC_MODE_WRITE_MODE
                                    | SMC_MODE_READ_MODE
                                    | SMC_MODE_DBW(busWidth/16)
                                    | SMC_MODE_EXNW_MODE(0)
                                    | SMC_MODE_TDF_CYCLES(1);

}