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
/// \page "RawNandflash"
///
/// !!!Purpose
/// 
/// RawNandflash is a bl Nandflash driver, it directly interacts with hardware's register to 
/// operate Nandflash interface, and it is called by upper layer drivers, such as EccNandFlash
///  
/// !!!Usage
///
/// -# RawNandFlash_Initialize is used to initializes a RawNandFlash instance based on the given
///      model and physical interface. If no model is provided, then the function tries to autodetect
///      it.
/// -# RawNandFlash_Reset is used to reset a Nandflash device.
/// -# RawNandFlash_ReadId is used to read a Nandflash's id.
/// -# RawNandFlash_EraseBlock is used to erase a certain Nandflash device's block.
/// -# RawNandFlash_ReadPage and RawNandFlash_WritePage is used to do read/write operation.
/// -# RawNandFlash_CopyPage is used to issue copypage command to Nandflash device.
/// -# RawNandFlash_CopyBlock calls RawNandFlash_CopyPage to do a Nandflash block copy.
//------------------------------------------------------------------------------


#ifndef RAWNANDFLASH_H
#define RAWNANDFLASH_H

//------------------------------------------------------------------------------
//         Headers
//------------------------------------------------------------------------------

#include "NandFlashModel.h"
#include <pio/pio.h>

//------------------------------------------------------------------------------
//         Types
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// Describes a physical NandFlash chip connected to the SAM microcontroller.
//------------------------------------------------------------------------------
struct RawNandFlash {

    /// Model describing this NandFlash characteristics.
    struct NandFlashModel model;
    /// Address for sending commands to the NandFlash.
    unsigned int commandAddress;
    /// Address for sending addresses to the NandFlash
    unsigned int addressAddress;
    /// Address for sending data to the NandFlash.
    unsigned int dataAddress;
    /// Pin used to enable the NandFlash chip.
    Pin pinChipEnable;
    /// Pin used to monitor the ready/busy signal from the NandFlash.
    Pin pinReadyBusy;
};

//------------------------------------------------------------------------------
//         Exported functions
//------------------------------------------------------------------------------

extern unsigned char RawNandFlash_Initialize(
    struct RawNandFlash *raw,
    const struct NandFlashModel *model,
    unsigned int commandAddress,
    unsigned int addressAddress,
    unsigned int dataAddress,
    const Pin pinChipEnable,
    const Pin pinReadyBusy);

extern void RawNandFlash_Reset(const struct RawNandFlash *raw);

extern unsigned int RawNandFlash_ReadId(const struct RawNandFlash *raw);

extern unsigned char RawNandFlash_EraseBlock(
    const struct RawNandFlash *raw,
    unsigned short block);

extern unsigned char RawNandFlash_ReadPage(
    const struct RawNandFlash *raw,
    unsigned short block,
    unsigned short page,
    void *data,
    void *spare);

extern unsigned char RawNandFlash_WritePage(
    const struct RawNandFlash *raw,
    unsigned short block,
    unsigned short page,
    void *data,
    void *spare);

extern unsigned char RawNandFlash_CopyPage(
    const struct RawNandFlash *raw,
    unsigned short sourceBlock,
    unsigned short sourcePage,
    unsigned short destBlock,
    unsigned short destPage);

extern unsigned char RawNandFlash_CopyBlock(
    const struct RawNandFlash *raw,
    unsigned short sourceBlock,
    unsigned short destBlock);

extern unsigned int NandDisableInternalEcc(const struct RawNandFlash *raw);
#endif //#ifndef RAWNANDFLASH_H

