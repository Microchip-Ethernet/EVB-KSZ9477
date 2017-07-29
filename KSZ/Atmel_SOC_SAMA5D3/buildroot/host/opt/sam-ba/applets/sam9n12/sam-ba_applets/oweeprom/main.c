/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012, Atmel Corporation

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

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/
#include "../common/applet.h"
#include <board.h>
#include <include/trace.h>
#include <include/pio.h>
#include <string.h>
#include <include/oweeprom.h>

/*----------------------------------------------------------------------------
 *         Local definitions
 *----------------------------------------------------------------------------*/
#define MAX_RETRIES    20
#define PIN_1WIRE   {1 << 4, PIOA, ID_PIOA, PIO_INPUT, PIO_DEFAULT}
#define DEVICE_ON_BOARD    2

/*----------------------------------------------------------------------------
 *        Local structures
 *----------------------------------------------------------------------------*/
/** Structure for storing parameters for each command that can be performed by the applet.*/
struct _Mailbox {

    /** Command send to the monitor to be executed. */
    uint32_t command;
    /** Returned status, updated at the end of the monitor execution.*/
    uint32_t status;

    /** Input Arguments in the argument area*/
    union {

        /** Input arguments for the Init command.*/
        struct {

            /** Communication link used.*/
            uint32_t comType;
            /** Trace level.*/
            uint32_t traceLevel;

        } inputInit;

        /** Output arguments for the Init command.*/
        struct {
            
            /** Memory size.*/
            uint32_t memorySize;
            /** Buffer address.*/
            uint32_t bufferAddress;
            /** Buffer size.*/
            uint32_t bufferSize;
            /** Number of devices detected */
            uint32_t numOfDevices;
            /** Address of device Info */
            uint32_t deviceInfoAddr;

        } outputInit;

        /** Input arguments for the Write command.*/
        struct {

            /** Buffer address.*/
            uint32_t bufferAddr;
            /** Buffer size.*/
            uint32_t bufferSize;
            /** Memory offset.*/
            uint32_t memoryOffset;
            /** Low 32-bit Device ROM Serial Number */
            uint32_t deviceSN_L;
            /** High 32-bit Device ROM Serial Number */
            uint32_t deviceSN_H;

        } inputWrite;

        /** Output arguments for the Write command.*/
        struct {

            /** Bytes written.*/
            uint32_t bytesWritten;

        } outputWrite;

        /** Input arguments for the Read command.*/
        struct {

            /** Buffer address.*/
            uint32_t bufferAddr;
            /** Buffer size.*/
            uint32_t bufferSize;
            /** Memory offset.*/
            uint32_t memoryOffset;
            /** Low 32-bit Device ROM Serial Number */
            uint32_t deviceSN_L;
            /** High 32-bit Device ROM Serial Number */
            uint32_t deviceSN_H;

        } inputRead;

        /** Output arguments for the Read command.*/
        struct {

            /** Bytes read.*/
            uint32_t bytesRead;

        } outputRead;

        /** Input arguments for the Full Erase command.*/
        /* NONE */

        /** Output arguments for the Full Erase command.*/
        /* NONE */

        /** Input arguments for the Buffer Erase command.*/
        /* NONE */

        /** Output arguments for the Buffer Erase command.*/
        /* NONE */
    } argument;
};

/*----------------------------------------------------------------------------
 *        Global variables
 *----------------------------------------------------------------------------*/

/** End of program space (code + data). */
extern uint32_t _end;
extern uint32_t _sstack;

/* One-wire pin */
static Pin pin1Wire[] = {PIN_1WIRE};

/** Communication type with SAM-BA GUI.*/
static uint32_t comType;

/* Device ROM Serial Number */
uint8_t myDevices[DEVICE_ON_BOARD][8] __attribute__((aligned(4))) = {{0, 0}};

/* Content of the whole memory */
uint8_t memContent[DS2433_SIZE_BYTES] = {0};

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/
/**
 * \brief Convert device serial number from two 32-bit pointers to one 8-bit array
 * \param pHigh  pointer to higher 32 bits of the serial number
 * \param pLow  pointer to lower 32 bits of the serial number
 * \param pBuf  pointer to a 8-bit array where a 16-byte of serial number is to be stored
 */
static void device_number_converter(uint32_t *pHigh, uint32_t *pLow, uint8_t *pBuf)
{
    uint32_t i = 0;
    
    /* Convert lower 8-byte serial number */
    for (i = 0; i < 4; i++) {
        pBuf[i] = *((uint8_t *)pLow + i);
    }
    
    /* Convert higher 8-byte serial number */
    for (i = 0; i < 4; i++) {
        pBuf[4 + i] = *((uint8_t *)pHigh + i);
    }
}

/**
 * \brief Applet main entry. This function decodes received command and executes it.
 * \param familyCode  The family code of the device
 * \retval  The size of device memory
 */
static uint32_t get_device_memory_size(uint8_t familyCode)
{
    uint32_t memorySize = 0;
    
    switch (familyCode) {
    case FAMILY_CODE_DS2431:
        memorySize = DS2431_SIZE_BYTES;
        break;
    
    case FAMILY_CODE_DS2433:
        memorySize = DS2433_SIZE_BYTES;
        break;
    
    default:
        memorySize = 0;
        TRACE_INFO("Unknown family code\r\n");
        break;
    }
    
    return memorySize;
}
 
/*----------------------------------------------------------------------------
 *         Global functions
 *----------------------------------------------------------------------------*/
/**
 * \brief Applet main entry. This function decodes received command and executes it.
 * \param argc  always 1
 * \param argv  Address of the argument area.
*/
int main(int argc, char **argv)
{
    struct _Mailbox *pMailbox = (struct _Mailbox *) argv;
    volatile uint32_t i, retry = 0;
    uint32_t numOfDevices = 0;
    uint32_t targetSize = 0;
    uint32_t *lowDeviceSN, *highDeviceSN = 0;
    uint32_t memoryOffset, bufferAddr, bytesToRead, bytesToWrite;
    uint8_t *pBuffer;
    uint8_t targetDeviceNo[8] = {0};

    /* Disable watchdog timer */
    WDT_Disable(WDT);
    /* Configure one wire pin */
    PIO_Configure(pin1Wire, PIO_LISTSIZE(pin1Wire));

    // ----------------------------------------------------------
    // INIT:
    // ----------------------------------------------------------
    if (pMailbox->command == APPLET_CMD_INIT) {
        /* Save communication link type */
        comType = pMailbox->argument.inputInit.comType;

#if (DYN_TRACES == 1)
        dwTraceLevel = pMailbox->argument.inputInit.traceLevel;
#endif
        TRACE_INFO("-- One-wire EEPROM Applet %s --\n\r", SAM_BA_APPLETS_VERSION);
        TRACE_INFO("-- %s\n\r", BOARD_NAME);

        /* Search devices on one-wire bus */
        for (retry = 0; retry < MAX_RETRIES; retry++) {
            numOfDevices = OW_SearchDevice(pin1Wire, myDevices[0], DEVICE_ON_BOARD);
            if (numOfDevices) {
                break;
            }
        }

        /* List all serial numbers of the devices found */
        TRACE_INFO("Found %d devices\r\n", (unsigned int)numOfDevices);
        for (i = 0; i < numOfDevices; i++) {

            lowDeviceSN = (uint8_t *)myDevices[i];
            highDeviceSN = (uint8_t *)myDevices[i] + 4;
            TRACE_INFO("Device %d\t%08x%08x\r\n", (unsigned int)(i + 1), 
                        (unsigned int)(*highDeviceSN), (unsigned int)(*lowDeviceSN));
        }
        
        /**
         * Only the size of the first found device is returned.
         * Other sizes are retrieved by SAM-BA tcl.
         * To be improved
         */
        pMailbox->argument.outputInit.memorySize = get_device_memory_size(myDevices[0][0]);       
        
        pMailbox->argument.outputInit.numOfDevices = numOfDevices;
        pMailbox->argument.outputInit.bufferAddress = (uint32_t) &_end;
        pMailbox->argument.outputInit.bufferSize = DS2433_SIZE_BYTES;
        pMailbox->argument.outputInit.deviceInfoAddr = myDevices[0];
        
        pMailbox->status = APPLET_SUCCESS;
    }

    // ----------------------------------------------------------
    // WRITE:
    // ----------------------------------------------------------
    else if (pMailbox->command == APPLET_CMD_WRITE) {

        memoryOffset = pMailbox->argument.inputWrite.memoryOffset;
        bufferAddr   = pMailbox->argument.inputWrite.bufferAddr;
        bytesToWrite = pMailbox->argument.inputWrite.bufferSize;
        
        lowDeviceSN  = &pMailbox->argument.inputWrite.deviceSN_L;
        highDeviceSN = &pMailbox->argument.inputWrite.deviceSN_H;
     
        device_number_converter(highDeviceSN, lowDeviceSN, targetDeviceNo);
        targetSize = get_device_memory_size(targetDeviceNo[0]);
        
        /* Check if the size of data to be written is valid for target device */
        if (targetSize < (memoryOffset + bytesToWrite)) {
            
            pMailbox->argument.outputWrite.bytesWritten = 0;
            if (!targetSize) {
                /* The family code of target device is unknown */
                pMailbox->status = APPLET_DEV_UNKNOWN;
            } else {
                /* The size of target device is too small */
                TRACE_INFO("Memory Overflow!\r\n");
                pMailbox->status = APPLET_WRITE_FAIL;
            }
            goto exit;
        }
        
        pBuffer = (uint8_t *) bufferAddr;
        /* Retrieve the memory content and modify it */
        OW_ReadMemory(pin1Wire, targetDeviceNo, 0, memContent, targetSize);
        for (i = 0; i < bytesToWrite; i++) {
            memContent[memoryOffset + i] = pBuffer[i];
        }
        
        TRACE_INFO("Target Device: %08x%08x\tMemory Size: 0x%x bytes\r\n", 
                  (unsigned int)(*highDeviceSN), (unsigned int)(*lowDeviceSN), (unsigned int)targetSize);
        TRACE_INFO("WRITE at offset: 0x%x buffer at : 0x%x of: 0x%x Bytes\n\r",
                   (unsigned int)memoryOffset, (unsigned int)bufferAddr, (unsigned int)bytesToWrite);
        
        /* Program the memory with modified content */           
        OW_WriteMemory(pin1Wire, targetDeviceNo, 0, memContent, targetSize);

        TRACE_INFO("WRITE return byte written : 0x%x Bytes\n\r", (unsigned int)bytesToWrite);
        pMailbox->argument.outputWrite.bytesWritten = bytesToWrite;
        pMailbox->status = APPLET_SUCCESS;
    }

    // ----------------------------------------------------------
    // READ:
    // ----------------------------------------------------------
    else if (pMailbox->command == APPLET_CMD_READ) {

        memoryOffset = pMailbox->argument.inputRead.memoryOffset;
        bufferAddr   = pMailbox->argument.inputRead.bufferAddr;
        bytesToRead  = pMailbox->argument.inputRead.bufferSize;

        lowDeviceSN  = &pMailbox->argument.inputWrite.deviceSN_L;
        highDeviceSN = &pMailbox->argument.inputWrite.deviceSN_H;

        device_number_converter(highDeviceSN, lowDeviceSN, targetDeviceNo);
        targetSize = get_device_memory_size(targetDeviceNo[0]);

        /* Check if the size of data to be read is valid for target device */
        if (targetSize < (memoryOffset + bytesToRead)) {
            
            pMailbox->argument.outputRead.bytesRead = 0;
            if (!targetSize) {
                /* The family code of target device is unknown */
                pMailbox->status = APPLET_DEV_UNKNOWN;
            } else {
                /* The size of target device is too small */
                TRACE_INFO("Memory Overflow!\r\n");
                pMailbox->status = APPLET_WRITE_FAIL;
            }
            goto exit;
        }

        pBuffer = (uint8_t *) bufferAddr;
        
        TRACE_INFO("Target Device: %08x%08x\tMemory Size: 0x%x bytes\r\n", 
                   (unsigned int)(*highDeviceSN), (unsigned int)(*lowDeviceSN), (unsigned int)targetSize);
        TRACE_INFO("READ at offset: 0x%x buffer at : 0x%x of: 0x%x Bytes\n\r",
                   (unsigned int)memoryOffset, (unsigned int)bufferAddr, (unsigned int)bytesToRead);

        pMailbox->argument.outputRead.bytesRead = 
            OW_ReadMemory(pin1Wire, targetDeviceNo, memoryOffset, pBuffer, bytesToRead);
        TRACE_INFO("READ return byte read : 0x%x Bytes\n\r", (unsigned int)pMailbox->argument.outputRead.bytesRead);
        
        pMailbox->status = APPLET_SUCCESS;
    }

exit:
    /* Acknowledge the end of command */
    TRACE_INFO("\tEnd of applet (command : %x --- status : %x)\n\r", (unsigned int)pMailbox->command, (unsigned int)pMailbox->status);

    /* Notify the host application of the end of the command processing */
    pMailbox->command = ~(pMailbox->command);
    /* Send ACK character */
    if (comType == DBGU_COM_TYPE) {
         /* Wait for the transmitter to be ready */
        while ( (DBGU->DBGU_SR & DBGU_SR_TXEMPTY) == 0 ) ;
        /* Send character */
        DBGU->DBGU_THR= 0x06 ;
    }
    return 0;

}

