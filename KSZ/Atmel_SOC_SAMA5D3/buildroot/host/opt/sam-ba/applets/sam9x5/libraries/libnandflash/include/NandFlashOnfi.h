/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2010, Atmel Corporation
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

#ifndef NANDONFI_H
#define NANDONFI_H

/*------------------------------------------------------------------------------ */
/*         Definitions                                                           */
/*------------------------------------------------------------------------------ */
/** Nand flash chip status response */
#define NAND_IO_RC_PASS 0
#define NAND_IO_RC_FAIL 1
#define NAND_IO_RC_TIMEOUT 2

/** NAND status bit mask */
#define STATUS_BIT_0 0x01
#define STATUS_BIT_1 0x02
#define STATUS_BIT_5 0x20
#define STATUS_BIT_6 0x40

#define NAND_MFR_MICRON     0x2c

/** Nand flash commands */
#define NAND_CMD_RESET                  0xFF
#define NAND_CMD_READ0                  0x00
#define NAND_CMD_READID                 0x90
#define NAND_CMD_STATUS                 0x70
#define NAND_CMD_READ_PARAM_PAGE        0xEC
#define NAND_CMD_SET_FEATURE            0xEF

#define WRITE_NAND_COMMAND(d, adr) *(volatile unsigned char *)((unsigned long)(adr) | BOARD_NF_COMMAND_ADDR) = (unsigned char)(d);
#define WRITE_NAND_ADDRESS(d, adr) *(volatile unsigned char *)((unsigned long)(adr) | BOARD_NF_ADDRESS_ADDR) = (unsigned char)(d);

#define READ_NAND(adr) ((*(volatile uint8_t *)(uint32_t)adr))

#define EBICSA_NAND_D0_ON_D16          (1 << 24)
#define EBICSA_DDR_MP_EN               (1 << 25)
#define EBICSA_EBI_DBPDC               (1 << 9 )

/** Describes memory organization block information in ONFI parameter page*/
typedef struct _OnfiPageParam {
    /** ONFI compatiable */
    uint8_t onfiCompatiable;
    /** JEDEC manufacturer ID */
    uint8_t manufacturerId;
    /** Bus width */
    uint8_t onfiBusWidth;
    /** Number of data bytes per page. */
    uint32_t onfiPageSize;
    /** Number of spare bytes per page. */
    uint16_t onfiSpareSize;
    /** Number of pages per block. */
    uint16_t onfiPagesPerBlock;
    /** Number of blocks per logical unit (LUN). */
    uint16_t onfiBlocksPerLun;
    /** Number of logical units. */
    uint8_t onfiLogicalUnits;
    /** Number of bits of ECC correction */
    uint8_t onfiEccCorrectability;
    /** Device model */
    uint8_t onfiDeviceModel;
} OnfiPageParam;

/*------------------------------------------------------------------------------ */
/*         Exported functions                                                    */
/*------------------------------------------------------------------------------ */
extern void NandInternalEccEnable (void);
extern void NandInternalEccDisable (void);
extern void NandSwitchEcc (uint8_t ecc);
extern uint8_t NandEbiDetect (void);
extern uint8_t NandGetEccStatus (void);
extern uint8_t NandIsOnficompatible (void);
extern uint8_t NandGetOnfiPageParam (OnfiPageParam *pOnfiPageParameter);
extern uint8_t NandEnableInternalEcc (void);
extern uint8_t NandDisableInternalEcc (void);
extern OnfiPageParam * NandGetCurrentOnfiInstance ( void );
extern void NandSetTrimffs(uint8_t enable);
extern uint8_t isNandTrimffs (void);
extern void NandSetTrimPage (uint16_t page);
extern uint16_t NandGetTrimPage (void);
#endif /*#ifndef NANDONFI_H */

