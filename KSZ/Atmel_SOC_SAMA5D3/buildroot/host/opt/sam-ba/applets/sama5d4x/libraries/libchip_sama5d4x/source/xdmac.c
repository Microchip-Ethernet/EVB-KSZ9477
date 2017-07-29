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


/**
 * \file
 *
 * Implementation of xDMA controller (XDMAC).
 *
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"

#include <stdint.h>
/** \addtogroup dmac_functions XDMAC Functions
 *@{
 */

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

uint32_t XDMAC_GetType( Xdmac *pXdmac)
{
    return pXdmac->XDMAC_GTYPE;
}

uint32_t XDMAC_GetConfig( Xdmac *pXdmac)
{
    return pXdmac->XDMAC_GCFG;
}

uint32_t XDMAC_GetArbiter( Xdmac *pXdmac)
{
    return pXdmac->XDMAC_GWAC;
}

/**
 * \brief Enables XDMAC global interrupt.
 *
 * \param pXdmac Pointer to the XDMAC peripheral.
 * \param dwInteruptMask IT to be enabled.
 */
void XDMAC_EnableGIt (Xdmac *pXdmac, uint32_t dwInteruptMask )
{
    pXdmac->XDMAC_GIE = dwInteruptMask;
}

/**
 * \brief Disables XDMAC global interrupt
 *
 * \param pXdmac Pointer to the XDMAC peripheral.
 * \param dwInteruptMask IT to be enabled
 */
void XDMAC_DisableGIt (Xdmac *pXdmac, uint32_t dwInteruptMask )
{
    pXdmac->XDMAC_GID = dwInteruptMask;
}

uint32_t XDMAC_GetGItMask( Xdmac *pXdmac )
{
    return (pXdmac->XDMAC_GIM);
}

uint32_t XDMAC_GetGIsr( Xdmac *pXdmac )
{
    return (pXdmac->XDMAC_GIS);
}

uint32_t XDMAC_GetMaskedGIsr( Xdmac *pXdmac )
{
    uint32_t _dwStatus;
    _dwStatus = pXdmac->XDMAC_GIS;
    _dwStatus &= pXdmac->XDMAC_GIM;
    return _dwStatus;
}

/**
 * \brief enables the relevant channel of given XDMAC.
 *
 * \param pXdmac Pointer to the XDMAC peripheral.
 * \param channel Particular channel number.
 */
void XDMAC_EnableChannel( Xdmac *pXdmac, uint8_t channel )
{
    pXdmac->XDMAC_GE |= XDMAC_GE_EN0 << channel;
}

/**
 * \brief enables the relevant channels of given XDMAC.
 *
 * \param pXdmac Pointer to the XDMAC peripheral.
 * \param bmChannels Channels bitmap.
 */
void XDMAC_EnableChannels( Xdmac *pXdmac, uint8_t bmChannels )
{
    pXdmac->XDMAC_GE = bmChannels;
}

/**
 * \brief Disables the relevant channel of given XDMAC.
 *
 * \param pXdmac Pointer to the XDMAC peripheral.
 * \param channel Particular channel number.
 */
void XDMAC_DisableChannel( Xdmac *pXdmac, uint8_t channel )
{
    pXdmac->XDMAC_GD |= XDMAC_GD_DI0 << channel;
}

/**
 * \brief Disables the relevant channels of given XDMAC.
 *
 * \param pXdmac Pointer to the XDMAC peripheral.
 * \param bmChannels Channels bitmap.
 */
void XDMAC_DisableChannels( Xdmac *pXdmac, uint8_t bmChannels )
{
    pXdmac->XDMAC_GD = bmChannels;
}

uint32_t XDMAC_GetChStatus(Xdmac *pXdmac)
{
    return pXdmac->XDMAC_GS;
}

void XDMAC_SuspendReadChannel( Xdmac *pXdmac, uint8_t channel )
{
    pXdmac->XDMAC_GRS |= XDMAC_GRS_RS0 << channel;
}


void XDMAC_SuspendWriteChannel( Xdmac *pXdmac, uint8_t channel )
{
    pXdmac->XDMAC_GWS |= XDMAC_GWS_WS0 << channel;
}

void XDMAC_SuspendReadWriteChannel( Xdmac *pXdmac, uint8_t channel )
{
    pXdmac->XDMAC_GRWS |= XDMAC_GRWS_RWS0 << channel;
}

void XDMAC_ResumeReadWriteChannel( Xdmac *pXdmac, uint8_t channel )
{
    pXdmac->XDMAC_GRWR |= XDMAC_GRWR_RWR0 << channel;
}

void XDMAC_SoftwareTransferReq(Xdmac *pXdmac, uint8_t channel)
{

    pXdmac->XDMAC_GSWR |= (XDMAC_GSWR_SWREQ0 << channel);
}

uint32_t XDMAC_GetSoftwareTransferStatus(Xdmac *pXdmac)
{
    return pXdmac->XDMAC_GSWS;
}

void XDMAC_SoftwareFlushReq(Xdmac *pXdmac, uint8_t channel)
{

    pXdmac->XDMAC_GSWF |= XDMAC_GSWF_SWF0 << channel;
}

void XDMAC_EnableChannelIt (Xdmac *pXdmac, uint8_t channel, uint32_t dwInteruptMask )
{
    pXdmac->XDMAC_CHID[channel].XDMAC_CIE = dwInteruptMask;
}

void XDMAC_DisableChannelIt (Xdmac *pXdmac, uint8_t channel, uint32_t dwInteruptMask )
{
    pXdmac->XDMAC_CHID[channel].XDMAC_CID = dwInteruptMask;
}

uint32_t XDMAC_GetChannelItMask (Xdmac *pXdmac, uint8_t channel)
{
    return pXdmac->XDMAC_CHID[channel].XDMAC_CIM;
}

uint32_t XDMAC_GetChannelIsr (Xdmac *pXdmac, uint8_t channel)
{
    return pXdmac->XDMAC_CHID[channel].XDMAC_CIS;
}

uint32_t XDMAC_GetMaskChannelI (Xdmac *pXdmac, uint8_t channel)
{
    uint32_t status;
    status = pXdmac->XDMAC_CHID[channel].XDMAC_CIS;
    status &= pXdmac->XDMAC_CHID[channel].XDMAC_CIM;

    return status;
}

void XDMAC_SetSourceAddr(Xdmac *pXdmac, uint8_t channel, uint32_t addr)
{
    pXdmac->XDMAC_CHID[channel].XDMAC_CSA = addr;
}

void XDMAC_SetDestinationAddr(Xdmac *pXdmac, uint8_t channel, uint32_t addr)
{
    pXdmac->XDMAC_CHID[channel].XDMAC_CDA = addr;
}

void XDMAC_SetDescriptorAddr(Xdmac *pXdmac, uint8_t channel, uint32_t addr, uint32_t ndaif)
{
    pXdmac->XDMAC_CHID[channel].XDMAC_CNDA =  ( addr & 0xFFFFFFFC ) | ndaif;
}

void XDMAC_SetDescriptorControl(Xdmac *pXdmac, uint8_t channel, uint32_t config)
{
    pXdmac->XDMAC_CHID[channel].XDMAC_CNDC = config;
}

void XDMAC_SetMicroblockControl(Xdmac *pXdmac, uint8_t channel, uint32_t ublen)
{

    pXdmac->XDMAC_CHID[channel].XDMAC_CUBC = ublen;
}

void XDMAC_SetBlockControl(Xdmac *pXdmac, uint8_t channel, uint32_t blen)
{
    pXdmac->XDMAC_CHID[channel].XDMAC_CBC = blen;
}

void XDMAC_SetChannelConfig(Xdmac *pXdmac, uint8_t channel, uint32_t config)
{
    pXdmac->XDMAC_CHID[channel].XDMAC_CC = config;
}

uint32_t XDMAC_GetChannelConfig(Xdmac *pXdmac, uint8_t channel)
{
    return pXdmac->XDMAC_CHID[channel].XDMAC_CC;
}

void XDMAC_SetDataStride_MemPattern(Xdmac *pXdmac, uint8_t channel, uint32_t dds_msp)
{
    pXdmac->XDMAC_CHID[channel].XDMAC_CDS_MSP = dds_msp;
}

void XDMAC_SetSourceMicroBlockStride(Xdmac *pXdmac, uint8_t channel, uint32_t subs)
{
    pXdmac->XDMAC_CHID[channel].XDMAC_CSUS = subs;
}

void XDMAC_SetDestinationMicroBlockStride(Xdmac *pXdmac, uint8_t channel, uint32_t dubs)
{
    pXdmac->XDMAC_CHID[channel].XDMAC_CDUS = dubs;
}
/**@}*/

