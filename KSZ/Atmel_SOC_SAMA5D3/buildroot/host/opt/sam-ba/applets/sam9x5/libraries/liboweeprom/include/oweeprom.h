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
#ifndef OWEEPROM_H
#define OWEEPROM_H

/*--------------------------------------------------------------------------- */
/*         Headers                                                            */
/*--------------------------------------------------------------------------- */
#include <board.h>
#include <include/trace.h>

/*--------------------------------------------------------------------------- */
/*         Definition                                                         */
/*--------------------------------------------------------------------------- */
/** ROM Command Definitions */
#define ROM_COMMAND_READ             0x33
#define ROM_COMMAND_MATCH            0x55
#define ROM_COMMAND_SEARCH           0xF0
#define ROM_COMMAND_SKIP             0xCC
#define ROM_COMMAND_RESUME           0xA5
#define ROM_COMMAND_OSKIP            0x3C
#define ROM_COMMAND_OMATCH           0x69

/** Memory Command Definitions */
#define MEMORY_COMMAND_WSCRATCHPAD   0x0F
#define MEMORY_COMMAND_RSCRATCHPAD   0xAA
#define MEMORY_COMMAND_CSCRATCHPAD   0x55
#define MEMORY_COMMAND_READMEMORY    0xF0

/** Electrical Characteristics Definitions */
#define tSLOT    65
#define tRSTL    480
#define tPDH     15
#define tPDL     60
#define tWOL     60
#define tW1L     5
#define tRL      5
#define tMSR     10
#define tPROG    13000

/** Device Characteristics Definitions */
#define FAMILY_CODE_DS2431           0x2D
#define FAMILY_CODE_DS2433           0x23
#define DS2431_SIZE_BYTES            0x88
#define DS2433_SIZE_BYTES           0x200
#define DS2431_SIZE_SCRATCHPAD        0x8
#define DS2433_SIZE_SCRATCHPAD       0x20

/*--------------------------------------------------------------------------- */
/*         Exported functions                                                 */
/*--------------------------------------------------------------------------- */
extern WEAK void OW_SetPinLevel(Pin *pin, const uint8_t level);
extern uint32_t OW_SearchDevice(Pin *pin, uint8_t *device_no, uint32_t expected_num);
extern uint32_t OW_ReadMemory(Pin      *pin, 
                              uint8_t  *device_no, 
                              uint16_t addr, 
                              uint8_t  *pData, 
                              uint32_t size);

extern uint32_t OW_WriteMemory(Pin      *pin, 
                               uint8_t  *device_no, 
                               uint16_t addr, 
                               uint8_t  *pData,
                               uint32_t size);

#endif /*#ifndef OWEEPROM_H */
