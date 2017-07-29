/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2010, Atmel Corporation
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

#ifndef PMECC_H
#define PMECC_H

/*------------------------------------------------------------------------------ */
/*         Definition                                                                 */
/*------------------------------------------------------------------------------ */

/** defines the maximum value of the error correcting capability */
#define NB_ERROR_MAX  25

/** Start address of ECC cvalue in spare zone, this must not be 0 since Bad block tag are at 0. */
#define PMECC_ECC_DEFAULT_START_ADDR   0x02

/** Address of Galois Field Table 512 mapping in ROM. */
#define GALOIS_TABLE_512_ROM_MAPPING   0x00108000

/** Address of Galois Field Table 1024 mapping in ROM. */
#define GALOIS_TABLE_1024_ROM_MAPPING  0x00110000

/** The ROM code embeds the software used in the process of ECC detection/correction*/
#define PMECC_CORRECTIONALGO_ROM_ADDRESS 0x100008

/** Use 2 Galois Field Table from ROM */
#define GALOIS_TABLE_IN_ROM

/*------------------------------------------------------------------------------ */
/*         Types                                                                 */
/*------------------------------------------------------------------------------ */

/** PMECC configuration descriptor */
typedef struct _PmeccDescriptor {
    /** Number of Sectors in one Page */
    uint32_t pageSize;
    /** The spare area size is equal to (SPARESIZE+1) bytes */
    uint32_t spareSize;
    /** 0 for 512, 1 for 1024 bytes, like in PMECCFG register */ 
    uint32_t sectorSize;
    /** Coded value of ECC bit number correction (0 (2 bits), 1 (4 bits), 2 (8 bits), 3 (12 bits), 4 (24 bits), 5 (NU)) */	
    uint32_t errBitNbrCapability;
    /** Real size in bytes of ECC in spare */
    uint32_t eccSizeByte;
    /** The first byte address of the ECC area */
    uint32_t eccStartAddr;
    /** The last byte address of the ECC area */    
    uint32_t eccEndAddr;
    /** NAND Write Access*/
    uint32_t nandWR;
    /** Spare Enable */
    uint32_t spareEna;
    /** Automatic Mode */
    uint32_t modeAuto;
    /** The PMECC Module data path Setup Time is set to CLKCTRL+1. */
    uint32_t clkCtrl;
    /** */
    uint32_t interrupt;
    /** defines the error correcting capability selected at encoding/decoding time */
    int32_t tt;
    /** degree of the remainders, GF(2**mm) */
    int32_t mm;
    /** length of codeword =  nn=2**mm -1 */
    int32_t nn;
    /** Gallois field table */
    int16_t *alpha_to;
    /** Index of Gallois field table */
    int16_t *index_of;
    /** */
    int16_t partialSyn[100];
    /** Holds the current syndrome value, an element of that table belongs to the field.*/
    int16_t si[100];
    /** sigma table */
    int16_t smu[NB_ERROR_MAX + 2][2 * NB_ERROR_MAX + 1];
    /** polynom order */
    int16_t lmu[NB_ERROR_MAX + 1];
} PmeccDescriptor;

/*------------------------------------------------------------------------------ */
/*         Exported functions                                                    */
/*------------------------------------------------------------------------------ */

extern uint8_t PMECC_Initialize(PmeccDescriptor *pPmeccDescriptor, 
                                uint8_t sectorSize,
                                uint8_t eccErrorsPersector,
                                uint32_t pageDataSize,
                                uint32_t pageSpareSize,
                                uint16_t EccOffset,
                                uint8_t spareProtected);

#if !defined (USE_PMECC_EMBEDDED_ALGO)
extern uint32_t PMECC_CorrectionAlgo( PmeccDescriptor *pPmeccDescriptor,
                                   uint32_t PMECC_status,
                                   uint32_t pageBuffer);
#endif

extern void build_gf( uint32_t mm, int16_t* index_of, int16_t* alpha_to );
extern PmeccDescriptor * PMECC_GetCurrentPmeccDescriptor(void);

extern void PMECC_Disable( void );
#endif

