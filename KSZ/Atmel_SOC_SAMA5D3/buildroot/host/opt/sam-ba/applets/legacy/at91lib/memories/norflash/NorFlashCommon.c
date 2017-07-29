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
#include "NorFlashCommon.h"

#include <utility/trace.h>
#include <string.h>

//------------------------------------------------------------------------------
//         Internal macros
//------------------------------------------------------------------------------

#define WRITE_COMMAND8(commandAddress, command) \
    {*(volatile unsigned char *)(commandAddress) = (unsigned char) command;}
#define WRITE_COMMAND16(commandAddress, command) \
    {*(volatile unsigned short *)(commandAddress) = (unsigned short) command;}
#define WRITE_COMMAND32(commandAddress, command) \
    {*(volatile unsigned int *)(commandAddress) = (unsigned int) command;}
    
#define WRITE_DATA8(dataAddress, data) \
    {(*((volatile unsigned char *) dataAddress)) = (unsigned char) data;}
#define WRITE_DATA16(dataAddress, data) \
    {(*((volatile unsigned short *) dataAddress)) = (unsigned short) data;}
#define WRITE_DATA32(dataAddress, data) \
    {(*((volatile unsigned int *) dataAddress)) = (unsigned int) data;}
    
#define READ_DATA8(dataAddress) \
    (*((volatile unsigned char *) dataAddress))
#define READ_DATA16(dataAddress) \
    (*((volatile unsigned short *) dataAddress))
#define READ_DATA32(dataAddress) \
    (*((volatile unsigned int *) dataAddress))
    
    
//------------------------------------------------------------------------------
//         Exported functions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// Write a command to address.
/// \param busWidth Bus width in device.
/// \param commandAddress Command address offset.
/// \param command Command to be send.
//------------------------------------------------------------------------------
unsigned char WriteCommand(
    unsigned char busWidth, 
    unsigned int commandAddress, 
    unsigned int command)
{
    if (busWidth == 8 ){
        WRITE_COMMAND8(commandAddress, command);
    }
    else if( busWidth == 16 ){
        WRITE_COMMAND16(commandAddress, command);
    }
    else if(busWidth == 32 ){
        WRITE_COMMAND32(commandAddress, command);
    }
    return 0;
}


//------------------------------------------------------------------------------
/// Reads data from the NorFlash chip into the provided buffer.
/// \param busWidth  Bus width in device.
/// \param address  Address of data.
/// \param buffer  Buffer where the data will be stored.
//------------------------------------------------------------------------------
void ReadRawData(
    unsigned char busWidth,
    unsigned int  address,
    unsigned char *buffer)
{
    if (busWidth == 8 ){    
            *buffer = READ_DATA8(address);
    }
    else if( busWidth == 16 ){
        
        unsigned short *buffer16 = (unsigned short *) buffer;
        *buffer16 = READ_DATA16(address);
    }
    else if(busWidth == 32 ){
        unsigned int *buffer32 = (unsigned int *) buffer;
        *buffer32 = READ_DATA32(address);
    }
}

//------------------------------------------------------------------------------
/// Writes data to the NorFlash chip from the provided buffer.
/// \param busWidth  Bus width in device.
/// \param address  Address of data.
/// \param buffer  Buffer where the data will be stored.
//------------------------------------------------------------------------------

void WriteRawData(
    unsigned char busWidth,
    unsigned int  address,
    unsigned char *buffer)

{
    if (busWidth == 8 ){    
        WRITE_DATA8(address, *buffer);
    }
    else if( busWidth == 16 ){
        unsigned short *buffer16 = (unsigned short *) buffer;
        WRITE_DATA16(address, *buffer16);
    }
    else if(busWidth == 32 ){
        unsigned int *buffer32 = (unsigned int *) buffer;
        WRITE_DATA32(address, *buffer32);
    }
}

