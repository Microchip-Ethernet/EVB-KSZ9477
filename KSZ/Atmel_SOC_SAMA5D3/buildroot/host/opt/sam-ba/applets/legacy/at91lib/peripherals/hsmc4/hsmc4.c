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

#include "hsmc4.h"

//------------------------------------------------------------------------------
//         Local variables
//------------------------------------------------------------------------------
/// Store value of current read only HSMC4_CTRL register.
static unsigned int hsmc4Ctrl;

//------------------------------------------------------------------------------
//         Internal functions
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// Returns 1 if the host main controller has terminated the command.
/// read mode.
/// otherwise returns 0.
//-----------------------------------------------------------------------------
unsigned char HSMC4_CommandDone(void)
{
    return ((AT91C_BASE_HSMC4->HSMC4_SR & AT91C_HSMC4_CMDDONE) == AT91C_HSMC4_CMDDONE);
} 

//------------------------------------------------------------------------------
//         Exported functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/// Sets the mode of the HSMC4 to one of the following values:
/// - AT91C_HSMC4_PAGESIZE
/// - AT91C_HSMC4_WSPARE   
/// - AT91C_HSMC4_RSPARE   
/// - AT91C_HSMC4_EDGECTRL 
/// - AT91C_HSMC4_RBEDGE   
/// - AT91C_HSMC4_DTOCYC   
/// - AT91C_HSMC4_DTOMUL   
/// \param mode  mode.
//------------------------------------------------------------------------------
void HSMC4_SetMode(unsigned int mode)
{
    AT91C_BASE_HSMC4->HSMC4_CFG = mode;
}

//-----------------------------------------------------------------------------
/// Reset the HSMC4 Nand flash controll host.
//-----------------------------------------------------------------------------
void HSMC4_ResetNfc(void)
{
    //Disable all the HSMC4 interrupts
    AT91C_BASE_HSMC4 -> HSMC4_IDR = 0xFFFFFFFF;	
    AT91C_BASE_HSMC4 -> HSMC4_CTRL = 0;
    hsmc4Ctrl = 0;
}

//-----------------------------------------------------------------------------
/// Enable NAND flsah controller host through the APB interface.
//-----------------------------------------------------------------------------
void HSMC4_EnableNfc(void)
{
    hsmc4Ctrl |= AT91C_HSMC4_NFCEN;
    AT91C_BASE_HSMC4->HSMC4_CTRL = hsmc4Ctrl;
}

//-----------------------------------------------------------------------------
/// Acticated and perform a data transfer between the Host and a Nand Flash.
//-----------------------------------------------------------------------------
void HSMC4_EnableNfcHost(void)
{
    hsmc4Ctrl |= AT91C_HSMC4_HOSTEN;
    AT91C_BASE_HSMC4->HSMC4_CTRL = hsmc4Ctrl;
}

//-----------------------------------------------------------------------------
/// Enable host transfer data from the internal SRAM to the memory device.
//-----------------------------------------------------------------------------
void HSMC4_EnableHostTransfer(void)
{
    hsmc4Ctrl |= AT91C_HSMC4_HOSTWR;
    // The HOSTWR field can be modified if the host controller is not busy.
    while((AT91C_BASE_HSMC4->HSMC4_SR & AT91C_HSMC4_HOSTBUSY) == AT91C_HSMC4_HOSTBUSY);
    AT91C_BASE_HSMC4->HSMC4_CTRL = hsmc4Ctrl;
    while((AT91C_BASE_HSMC4->HSMC4_SR & AT91C_HSMC4_HOSTBUSY) == AT91C_HSMC4_HOSTBUSY);
}

//-----------------------------------------------------------------------------
/// Enables the host main controller reads both main and spare area in read mode.
//-----------------------------------------------------------------------------
void HSMC4_EnableSpareRead(void)
{
    AT91C_BASE_HSMC4->HSMC4_CFG |= AT91C_HSMC4_RSPARE;
}

//-----------------------------------------------------------------------------
/// The host main controller skips spare area in read mode.
//-----------------------------------------------------------------------------
void HSMC4_DisableSpareRead(void)
{
    AT91C_BASE_HSMC4->HSMC4_CFG &= 0xFFFFFDFF;
}

//-----------------------------------------------------------------------------
/// Enables the host main controller writes both main and spare area in write
/// mode.
//-----------------------------------------------------------------------------
void HSMC4_EnableSpareWrite(void)
{
    AT91C_BASE_HSMC4->HSMC4_CFG |= AT91C_HSMC4_WSPARE;
}

//-----------------------------------------------------------------------------
/// The host main controller skips spare area in write mode.
//-----------------------------------------------------------------------------
void HSMC4_DisableSpareWrite(void)
{
    AT91C_BASE_HSMC4->HSMC4_CFG &= 0xFFFFFEFF;
}

//-----------------------------------------------------------------------------
/// Returns 1 if the host main controller reads both main and spare area in 
/// read mode.
/// otherwise returns 0.
//-----------------------------------------------------------------------------
unsigned char HSMC4_isSpareRead(void)
{
    return (((AT91C_BASE_HSMC4->HSMC4_CFG) >> 9) & 0x1);
}

//-----------------------------------------------------------------------------
/// Returns 1 if the host main controller writes both main and spare area in 
/// write mode.
/// otherwise returns 0.
//-----------------------------------------------------------------------------
unsigned char HSMC4_isSpareWrite(void)
{
    return (((AT91C_BASE_HSMC4->HSMC4_CFG) >> 8) & 0x1);
}


//-----------------------------------------------------------------------------
/// Returns 1 if the host main controller has terminated the data transmission.
/// otherwise returns 0.
//-----------------------------------------------------------------------------
unsigned char HSMC4_TransferComplete(void)
{
    return ((AT91C_BASE_HSMC4->HSMC4_SR & AT91C_HSMC4_XFRDONE) == AT91C_HSMC4_XFRDONE);
}

//-----------------------------------------------------------------------------
/// Returns 1 if  edge has been detected on the Ready/Busy line.
/// otherwise returns 0.
//-----------------------------------------------------------------------------
unsigned char HSMC4_isReadyBusy(void)
{
    return ((AT91C_BASE_HSMC4->HSMC4_SR & AT91C_HSMC4_RBEDGE0) == AT91C_HSMC4_RBEDGE0);
}

//-----------------------------------------------------------------------------
/// Returns 1 if the Controller is activated and accesses the memory device.
/// otherwise returns 0.
//-----------------------------------------------------------------------------
unsigned char HSMC4_isNfcBusy(void)
{
    return ((AT91C_BASE_HSMC4->HSMC4_SR & AT91C_HSMC4_HOSTBUSY) == AT91C_HSMC4_HOSTBUSY);
}

//-----------------------------------------------------------------------------
/// Returns 1 if the ecc is ready
/// otherwise returns 0.
//-----------------------------------------------------------------------------
unsigned char HSMC4_isEccReady(void)
{
    return ((AT91C_BASE_HSMC4->HSMC4_SR & AT91C_HSMC4_ECCRDY) == AT91C_HSMC4_ECCRDY);
}

//-----------------------------------------------------------------------------
/// Returns the current status register of the HSMC4 peripheral. This
/// resets the internal value of the status register, so further read may yield
/// different values.
//-----------------------------------------------------------------------------
unsigned int HSMC4_GetStatus(void)
{
    return AT91C_BASE_HSMC4->HSMC4_SR;
}

//------------------------------------------------------------------------------
//         HOST command functions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// Returns 1 if the host controller is busy.
/// otherwise returns 0.
//------------------------------------------------------------------------------
unsigned char HSMC4_isHostBusy(void)
{
    return (((*((volatile unsigned int *) (CMD_BASE_ADDR + AT91C_HSMC4_HOSTCMD))) & 0x8000000) == 0x8000000);
}

//------------------------------------------------------------------------------
/// Uses the HOST nandflash conntroller to send a command to the NFC
/// \param cmd  command to send.
/// \param addressCycle  address cycle when command access id decoded.
/// \param cycle0  address at first cycle.
//------------------------------------------------------------------------------
void HSMC4_SendCommand (unsigned int cmd, unsigned int addressCycle, unsigned int cycle0)
{
   volatile unsigned int *pCommandAddress;
   // Wait until host controller is not busy.
   while(HSMC4_isHostBusy());
    // Send the command plus the ADDR_CYCLE
    pCommandAddress = (volatile unsigned int *) (cmd + CMD_BASE_ADDR);
    AT91C_BASE_HSMC4->HSMC4_ADDR = cycle0;
    *pCommandAddress = addressCycle;
    while( !HSMC4_CommandDone());
}


