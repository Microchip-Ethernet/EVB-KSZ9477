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


#define TWITIMEOUTMAX 50000

//------------------------------------------------------------------------------
//         Headers
//------------------------------------------------------------------------------

#include "twid.h"
#include <twi/twi.h>
#include <utility/assert.h>
#include <utility/trace.h>

//------------------------------------------------------------------------------
//         Local types
//------------------------------------------------------------------------------

/// TWI driver callback function.
typedef void (*TwiCallback)(Async *);

//------------------------------------------------------------------------------
/// TWI asynchronous transfer descriptor.
//------------------------------------------------------------------------------
typedef struct _AsyncTwi {

    /// Asynchronous transfer status.
    volatile unsigned char status;
    // Callback function to invoke when transfer completes or fails.
    TwiCallback callback;
    /// Pointer to the data buffer.
    unsigned char *pData;
    /// Total number of bytes to transfer.
    unsigned int num;
    /// Number of already transferred bytes.
    unsigned int transferred;

} AsyncTwi;

//------------------------------------------------------------------------------
//         Global functions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// Initializes a TWI driver instance, using the given TWI peripheral. The
/// peripheral must have been initialized properly before calling this function.
/// \param pTwid  Pointer to the Twid instance to initialize.
/// \param pTwi  Pointer to the TWI peripheral to use.
//------------------------------------------------------------------------------
void TWID_Initialize(Twid *pTwid, AT91S_TWI *pTwi)
{
    TRACE_DEBUG("TWID_Initialize()\n\r");
    SANITY_CHECK(pTwid);
    SANITY_CHECK(pTwi);

    // Initialize driver
    pTwid->pTwi = pTwi;
    pTwid->pTransfer = 0;
}

//------------------------------------------------------------------------------
/// Interrupt handler for a TWI peripheral. Manages asynchronous transfer
/// occuring on the bus. This function MUST be called by the interrupt service
/// routine of the TWI peripheral if asynchronous read/write are needed.
/// \param pTwid  Pointer to a Twid instance.
//------------------------------------------------------------------------------
void TWID_Handler(Twid *pTwid)
{
    unsigned char status;
    AsyncTwi *pTransfer = (AsyncTwi *) pTwid->pTransfer;
    AT91S_TWI *pTwi = pTwid->pTwi;

    SANITY_CHECK(pTwid);

    // Retrieve interrupt status
    status = TWI_GetMaskedStatus(pTwi);

    // Byte received
    if (TWI_STATUS_RXRDY(status)) {

        pTransfer->pData[pTransfer->transferred] = TWI_ReadByte(pTwi);
        pTransfer->transferred++;

        // Transfer finished ?
        if (pTransfer->transferred == pTransfer->num) {

            TWI_DisableIt(pTwi, AT91C_TWI_RXRDY);
            TWI_EnableIt(pTwi, AT91C_TWI_TXCOMP);
        }
        // Last byte ?
        else if (pTransfer->transferred == (pTransfer->num - 1)) {

            TWI_Stop(pTwi);
        }
    }
    // Byte sent
    else if (TWI_STATUS_TXRDY(status)) {

        // Transfer finished ?
        if (pTransfer->transferred == pTransfer->num) {

            TWI_DisableIt(pTwi, AT91C_TWI_TXRDY);
            TWI_EnableIt(pTwi, AT91C_TWI_TXCOMP);
            TWI_SendSTOPCondition(pTwi);
        }
        // Bytes remaining
        else {

            TWI_WriteByte(pTwi, pTransfer->pData[pTransfer->transferred]);
            pTransfer->transferred++;
        }
    }
    // Transfer complete
    else if (TWI_STATUS_TXCOMP(status)) {

        TWI_DisableIt(pTwi, AT91C_TWI_TXCOMP);
        pTransfer->status = 0;
        if (pTransfer->callback) {
            
            pTransfer->callback((Async *) pTransfer);
        }
        pTwid->pTransfer = 0;
    }
}

//-----------------------------------------------------------------------------
/// Asynchronously reads data from a slave on the TWI bus. An optional
/// callback function is triggered when the transfer is complete.
/// Returns 0 if the transfer has been started; otherwise returns a TWI error
/// code.
/// \param pTwid  Pointer to a Twid instance.
/// \param address  TWI slave address.
/// \param iaddress  Optional slave internal address.
/// \param isize  Internal address size in bytes.
/// \param pData  Data buffer for storing received bytes.
/// \param num  Number of bytes to read.
/// \param pAsync  Asynchronous transfer descriptor.
//-----------------------------------------------------------------------------
unsigned char TWID_Read(
    Twid *pTwid,
    unsigned char address,
    unsigned int iaddress,
    unsigned char isize,
    unsigned char *pData,
    unsigned int num,
    Async *pAsync)
{
    AT91S_TWI *pTwi = pTwid->pTwi;
    AsyncTwi *pTransfer = (AsyncTwi *) pTwid->pTransfer;
    unsigned int timeout;

    //TRACE_DEBUG("TWID_Read()\n\r");
    SANITY_CHECK(pTwid);
    SANITY_CHECK((address & 0x80) == 0);
    SANITY_CHECK((iaddress & 0xFF000000) == 0);
    SANITY_CHECK(isize < 4);

    // Check that no transfer is already pending
    if (pTransfer) {

        TRACE_ERROR("TWID_Read: A transfer is already pending\n\r");
        return TWID_ERROR_BUSY;
    }

    // Set STOP signal if only one byte is sent
    if (num == 1) {

        TWI_Stop(pTwi);
    }

    // Asynchronous transfer
    if (pAsync) {
    
        // Update the transfer descriptor
        pTwid->pTransfer = pAsync;
        pTransfer = (AsyncTwi *) pAsync;
        pTransfer->status = ASYNC_STATUS_PENDING;
        pTransfer->pData = pData;
        pTransfer->num = num;
        pTransfer->transferred = 0;
        
        // Enable read interrupt and start the transfer
        TWI_EnableIt(pTwi, AT91C_TWI_RXRDY);
        TWI_StartRead(pTwi, address, iaddress, isize);
    }
    // Synchronous transfer
    else {

        // Start read
        TWI_StartRead(pTwi, address, iaddress, isize);

        // Read all bytes, setting STOP before the last byte
        while (num > 0) {

            // Last byte
            if (num == 1) {

                TWI_Stop(pTwi);
            }

            // Wait for byte then read and store it
            timeout = 0;
            while( !TWI_ByteReceived(pTwi) && (++timeout<TWITIMEOUTMAX) );
            if (timeout == TWITIMEOUTMAX) {
                TRACE_ERROR("TWID Timeout BR\n\r");
                return TWID_ERROR_TIMEOUT;
            }
            *pData++ = TWI_ReadByte(pTwi);
            num--;
        }

        // Wait for transfer to be complete
        timeout = 0;
        while( !TWI_TransferComplete(pTwi) && (++timeout<TWITIMEOUTMAX) );
        if (timeout == TWITIMEOUTMAX) {
            TRACE_ERROR("TWID Timeout TC\n\r");
            return TWID_ERROR_TIMEOUT;
        }
    }

    return 0;
}

//------------------------------------------------------------------------------
/// Asynchronously sends data to a slave on the TWI bus. An optional callback
/// function is invoked whenever the transfer is complete.
/// \param pTwid  Pointer to a Twid instance.
/// \param address  Slave address.
/// \param iaddress  Optional slave internal address.
/// \param isize  Number of internal address bytes.
/// \param pData  Data buffer to send.
/// \param num  Number of bytes to send.
/// \param pAsync  Pointer to an Asynchronous transfer descriptor.
//------------------------------------------------------------------------------
unsigned char TWID_Write(
    Twid *pTwid,
    unsigned char address,
    unsigned int iaddress,
    unsigned char isize,
    unsigned char *pData,
    unsigned int num,
    Async *pAsync)
{
    AT91S_TWI *pTwi = pTwid->pTwi;
    AsyncTwi *pTransfer = (AsyncTwi *) pTwid->pTransfer;
    unsigned int timeout;

    //TRACE_DEBUG("TWID_Write()\n\r");
    //TRACE_DEBUG("0x%X\n\r", pData[0]);
    SANITY_CHECK(pTwi);
    SANITY_CHECK((address & 0x80) == 0);
    SANITY_CHECK((iaddress & 0xFF000000) == 0);
    SANITY_CHECK(isize < 4);

    // Check that no transfer is already pending
    if (pTransfer) {

        TRACE_ERROR("TWI_Write: A transfer is already pending\n\r");
        return TWID_ERROR_BUSY;
    }

    // Asynchronous transfer
    if (pAsync) {
    
        // Update the transfer descriptor
        pTwid->pTransfer = pAsync;
        pTransfer = (AsyncTwi *) pAsync;
        pTransfer->status = ASYNC_STATUS_PENDING;
        pTransfer->pData = pData;
        pTransfer->num = num;
        pTransfer->transferred = 1;
    
        // Enable write interrupt and start the transfer
        TWI_StartWrite(pTwi, address, iaddress, isize, *pData);
        TWI_EnableIt(pTwi, AT91C_TWI_TXRDY);
    }
    // Synchronous transfer
    else {

        // Start write
        TWI_StartWrite(pTwi, address, iaddress, isize, *pData++);
        num--;

        // Send all bytes
        while (num > 0) {
        
            // Wait before sending the next byte
            timeout = 0;
            while( !TWI_ByteSent(pTwi) && (++timeout<TWITIMEOUTMAX) );
            if (timeout == TWITIMEOUTMAX) {
                TRACE_ERROR("TWID Timeout BS\n\r");
                return TWID_ERROR_TIMEOUT;
            }

            TWI_WriteByte(pTwi, *pData++);
            num--;
        }

        // Wait for actual end of transfer
        timeout = 0;

#ifdef TWI_V3XX
        // Send a STOP condition
        TWI_SendSTOPCondition(pTwi);
#endif

        while( !TWI_TransferComplete(pTwi) && (++timeout<TWITIMEOUTMAX) );
        if (timeout == TWITIMEOUTMAX) {
            TRACE_ERROR("TWID Timeout TC2\n\r");
            return TWID_ERROR_TIMEOUT;
        }

    }
    
    return 0;
}

