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
/// \unit
///
/// !!!Purpose
/// 
/// The AT45 Dataflash driver is based on the corresponding AT45 driver. 
/// A AT45 instance has to be initialized using the Dataflash levle function
/// AT45_Configure(). AT45 Dataflash can be automatically detected using 
/// the AT45_FindDevice() function. Then AT45 dataflash operations such as 
/// read, write and erase DF can be launched using AT45_SendCommand function
/// with corresponding AT45 command set.
/// 
/// !!!Usage
/// 
/// -# Reads data from the At45 at the specified address using AT45D_Read().
/// -# Writes data on the At45 at the specified address using AT45D_Write().
/// -# Erases a page of data at the given address using AT45D_Erase().
/// -# Poll until the At45 has completed of corresponding operations using 
///    AT45D_WaitReady().
/// -# Retrieves and returns the At45 current using AT45D_GetStatus().
//------------------------------------------------------------------------------


#ifndef AT45D_H
#define AT45D_H

//------------------------------------------------------------------------------
//         Headers
//------------------------------------------------------------------------------

#include "at45.h"

//------------------------------------------------------------------------------
//         Global functions
//------------------------------------------------------------------------------

extern void AT45D_WaitReady(At45 *pAt45); 

extern unsigned char AT45D_GetStatus(At45 *pAt45);

extern void AT45D_Read(
    At45 *pAt45,
    unsigned char *pBuffer,
    unsigned int size,
    unsigned int address); 

extern void AT45D_Write(
    At45 *pAt45,
    unsigned char *pBuffer,
    unsigned int size,
    unsigned int address); 

extern void AT45D_Erase(At45 *pAt45, unsigned int address);

extern void AT45D_BinaryPage(At45 *pAt45);

#endif //#ifndef AT45D_H

