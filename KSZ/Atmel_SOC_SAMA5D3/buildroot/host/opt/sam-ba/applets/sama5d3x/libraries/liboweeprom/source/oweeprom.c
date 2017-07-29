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

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/
#include <board.h>
#include <oweeprom.h>
#include <assert.h>
#include <string.h>

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/
uint8_t DeviceFound = 0;
uint8_t DeviceNo[8] = {0};
uint8_t LastDiscrepancy;
uint8_t LastFamilyDiscrepancy;
uint8_t LastDeviceFlag;
uint8_t crc8;

/* CRC table */
static uint8_t dscrc_table[] = {
        0, 94,188,226, 97, 63,221,131,194,156,126, 32,163,253, 31, 65,
      157,195, 33,127,252,162, 64, 30, 95,  1,227,189, 62, 96,130,220,
       35,125,159,193, 66, 28,254,160,225,191, 93,  3,128,222, 60, 98,
      190,224,  2, 92,223,129, 99, 61,124, 34,192,158, 29, 67,161,255,
       70, 24,250,164, 39,121,155,197,132,218, 56,102,229,187, 89,  7,
      219,133,103, 57,186,228,  6, 88, 25, 71,165,251,120, 38,196,154,
      101, 59,217,135,  4, 90,184,230,167,249, 27, 69,198,152,122, 36,
      248,166, 68, 26,153,199, 37,123, 58,100,134,216, 91,  5,231,185,
      140,210, 48,110,237,179, 81, 15, 78, 16,242,172, 47,113,147,205,
       17, 79,173,243,112, 46,204,146,211,141,111, 49,178,236, 14, 80,
      175,241, 19, 77,206,144,114, 44,109, 51,209,143, 12, 82,176,238,
       50,108,142,208, 83, 13,239,177,240,174, 76, 18,145,207, 45,115,
      202,148,118, 40,171,245, 23, 73,  8, 86,180,234,105, 55,213,139,
       87,  9,235,181, 54,104,138,212,149,203, 41,119,244,170, 72, 22,
      233,183, 85, 11,136,214, 52,106, 43,117,151,201, 74, 20,246,168,
      116, 42,200,150, 21, 75,169,247,182,232, 10, 84,215,137,107, 53
};

static uint8_t docrc8(uint8_t value);
static void delay(volatile uint32_t num);
static uint8_t OW_Reset(Pin *pin);
static uint8_t OW_Search(Pin *pin);
static uint8_t OW_First(Pin *pin);
static uint8_t OW_Next(Pin *pin);
static uint8_t OW_ReadBit(Pin *pin);
static uint8_t OW_ReadByte(Pin *pin);
static void OW_WriteByte(Pin *pin, uint8_t byte_value);
static void OW_WriteBitH(Pin *pin);
static void OW_WriteBitL(Pin *pin);
static void OW_WriteScratchpad(Pin *pin, uint8_t addrh,uint8_t addrl,
                               uint32_t size_scratchpad,uint8_t *pData);
static void OW_ReadScratchpad(Pin *pin, uint32_t size_scratchpad,uint8_t *pData);
static void OW_CopyScratchpad(Pin *pin, uint8_t *pData);

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/
/**
 * \brief Change the level of the pin
 * \param pin  Pointer to the pin instance
 * \param level  The level of the pin
 */
extern WEAK void OW_SetPinLevel(Pin *pin, const uint8_t level)
{
    if (!level) {
        pin->type = PIO_OUTPUT_0;
        PIO_Configure(pin, 1);
    } else {
        pin->type = PIO_INPUT;
        PIO_Configure(pin, 1);
    }
}

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/
/**
 * \brief Caculate the CRC
 * \param value  Input value.
 * \return CRC value.
 */
static uint8_t docrc8(uint8_t value)
{
   crc8 = dscrc_table[crc8 ^ value];
   return crc8;
}

/**
 * \brief Delay microseconds
 * \param num  The number of microseconds to be delayed
 */
static void delay(volatile uint32_t num)
{
    volatile uint32_t us;
    
    for(; num > 0; num--) {  
        for( us = ( BOARD_MCK/100000000 ); us > 0; us--) {  
            asm("nop");
        }
    }
}

/**
 * \brief Reset the 1-Wire bus and return the presence of any device
 * \param pin  Pointer to the pin instance
 * \return 1 if device is present. 0 if no device is present
 */
static uint8_t OW_Reset(Pin *pin)
{    
    OW_SetPinLevel(pin, 0);
    delay(tRSTL);
    
    OW_SetPinLevel(pin, 1);
    delay(tPDH/2);
    while(PIO_Get(pin));
    while(!PIO_Get(pin));
    delay(tPDL/2);
    
    return 1;
}

/**
 * \brief Send bit '1' of data to the 1-Wire bus
 * \param pin  Pointer to the pin instance
 */
static void OW_WriteBitH(Pin *pin)
{
    OW_SetPinLevel(pin, 0);
    delay(tW1L);
    OW_SetPinLevel(pin, 1);
    delay(tSLOT-tW1L);
}

/**
 * \brief Send bit '0' of data to the 1-Wire bus
 * \param pin  Pointer to the pin instance
 */
static void OW_WriteBitL(Pin *pin)
{
    OW_SetPinLevel(pin, 0);
    delay(tWOL);
    OW_SetPinLevel(pin, 1);
    delay(tSLOT-tWOL); 
}

/**
 * \brief Send one byte of data to the 1-Wire bus
 * \param pin  Pointer to the pin instance
 * \param The byte to be sent
 */
static void OW_WriteByte(Pin *pin, uint8_t byte_value)
{
    uint8_t bit;
    uint8_t t[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
    
    for( bit = 0; bit < 8; bit++) {
        if(byte_value&t[bit]) {
            OW_WriteBitH(pin);
        } else {
            OW_WriteBitL(pin);
        }
    }
}

/**
 * \brief Read one bit of data from the 1-Wire bus
 * \param pin  Pointer to the pin instance
 * \return 1 if the bit read is 1. 0 if 0
 */
static uint8_t OW_ReadBit(Pin *pin)
{
     uint8_t status;
     
     OW_SetPinLevel(pin, 0);
     delay(tRL);
     OW_SetPinLevel(pin, 1);
     delay(tMSR/2);
     status = (uint8_t)PIO_Get(pin);
     delay(tSLOT-tRL-tMSR);

     return status;
}

/**
 * \brief Read one byte of data from the 1-Wire bus
 * \param pin  Pointer to the pin instance
 * \return The byte read from 1-Wire bus
 */
static uint8_t OW_ReadByte(Pin *pin)
{    
    uint8_t bit,data = 0;
    
    for (bit = 0; bit < 8; bit++) {
        if(OW_ReadBit(pin)) {
            data |= (1 << bit);
        }
    }
    
    return data;
}

/**
 * \brief Write the scratchpad of data to the device
 * \param pin  Pointer to the pin instance
 * \param addrh  The higher 8 bits of the memory address
 * \param addrl  The lower 8 bits of the memory address
 * \param size_scratchpad  The size of the device scratchpad
 * \param pData  Pointer to the data to be written
 */
static void OW_WriteScratchpad(Pin *pin, 
                             uint8_t addrh,
                             uint8_t addrl,
                             uint32_t size_scratchpad,
                             uint8_t *pData)
{
    uint32_t i;
    uint8_t crc[2];
    crc[0] = 0;
    crc[1] = crc[0];
    
    OW_WriteByte(pin, MEMORY_COMMAND_WSCRATCHPAD);
    
    OW_WriteByte(pin, addrl);
    OW_WriteByte(pin, addrh);
    
    for(i = 0; i < size_scratchpad; i++) {
        OW_WriteByte(pin, pData[i]);
    }
    
    crc[0] = OW_ReadByte(pin);
    crc[1] = OW_ReadByte(pin);
}

/**
 * \brief Read the scratchpad of data from the device
 * \param pin  Pointer to the pin instance
 * \param size_scratchpad  The size of the device scratchpad
 * \param pData  Point to where the data read is stored
 */
static void OW_ReadScratchpad(Pin *pin, uint32_t size_scratchpad,uint8_t *pData)
{
    uint32_t i;
    
    OW_WriteByte(pin, MEMORY_COMMAND_RSCRATCHPAD);
    
    for(i = 0; i< size_scratchpad + 5; i++) {
        pData[i] = OW_ReadByte(pin);
    }
}

/**
 * \brief Copy the data in scratchpad of the device
 * \param pin  Pointer to the pin instance
 * \param pData  3-byte authorization pattern
 */
static void OW_CopyScratchpad(Pin *pin, uint8_t *pData)
{    
    OW_WriteByte(pin, MEMORY_COMMAND_CSCRATCHPAD);
    OW_WriteByte(pin, pData[0]);
    OW_WriteByte(pin, pData[1]);
    OW_WriteByte(pin, pData[2]);
    
    delay(tPROG);
}

/**
 * \brief Perform the 1-Wire Search Algorithm on the 1-Wire bus using the existing search state.
 * \param pin  Pointer to the pin instance
 * \return 1 if device is found and ROM number(ID) will be stored in DeviceNo. 0 if not.
 */
static uint8_t OW_Search(Pin *pin)
{
    uint8_t id_bit_number;
    uint8_t last_zero, rom_byte_number, search_result;
    uint8_t id_bit, cmp_id_bit;
    uint8_t rom_byte_mask, search_direction;
    
    // initialize for search
    id_bit_number = 1;
    last_zero = 0;
    rom_byte_number = 0;
    rom_byte_mask = 1;
    search_result = 0;
    crc8 = 0;
    
    // if the last call was not the last one
    if (!LastDeviceFlag) {
        // 1-Wire reset
        if (!OW_Reset(pin)) {
            // reset the search
            LastDiscrepancy = 0;
            LastDeviceFlag = 0;
            LastFamilyDiscrepancy = 0;
            return 0;
        }

        // issue the search command 
        OW_WriteByte(pin, ROM_COMMAND_SEARCH);  
    
        // loop to do the search
        do {
            // read a bit and its complement
            id_bit = OW_ReadBit(pin);
            cmp_id_bit = OW_ReadBit(pin);
        
            // check for no devices on 1-wire
            if ((id_bit == 1) && (cmp_id_bit == 1)) {
                break;
            } else {
                // all devices coupled have 0 or 1
                if (id_bit != cmp_id_bit) {
                    search_direction = id_bit;  // bit write value for search
                } else {
                    // if this discrepancy if before the Last Discrepancy
                    // on a previous next then pick the same as last time
                    if (id_bit_number < LastDiscrepancy) {
                        search_direction = ((DeviceNo[rom_byte_number] & rom_byte_mask) > 0);
                    } else {
                        // if equal to last pick 1, if not then pick 0
                        search_direction = (id_bit_number == LastDiscrepancy);
                    }
                    
                    // if 0 was picked then record its position in LastZero
                    if (search_direction == 0) {
                        last_zero = id_bit_number;
                    
                        // check for Last discrepancy in family
                        if (last_zero < 9)
                            LastFamilyDiscrepancy = last_zero;
                    }
                }
    
                // set or clear the bit in the ROM byte rom_byte_number
                // with mask rom_byte_mask
                if (search_direction == 1) {
                    DeviceNo[rom_byte_number] |= rom_byte_mask;
                } else {
                    DeviceNo[rom_byte_number] &= ~rom_byte_mask;
                }

                // serial number search direction write bit
                if (search_direction == 1) {
                    OW_WriteBitH(pin);
                } else {
                    OW_WriteBitL(pin);
                }

                // increment the byte counter id_bit_number
                // and shift the mask rom_byte_mask
                id_bit_number++;
                rom_byte_mask <<= 1;
        
                /* if the mask is 0 then go to new SerialNum byte rom_byte_number and reset mask */
                if (rom_byte_mask == 0) {
                    docrc8(DeviceNo[rom_byte_number]);  /* accumulate the CRC */
                    rom_byte_number++;
                    rom_byte_mask = 1;
                }
            }
        } while (rom_byte_number < 8);  /* loop until through all ROM bytes 0-7 */
    
        /* if the search was successful then */
        if (!((id_bit_number < 65) || (crc8 != 0))) {
            /* search successful so set LastDiscrepancy,LastDeviceFlag,search_result */
            LastDiscrepancy = last_zero;
        
            /* check for last device */
            if (LastDiscrepancy == 0) {
                LastDeviceFlag = 1;
            }

            search_result = 1;
        }
    }

    /* if no device found then reset counters so next 'search' will be like a first */
    if (!search_result || !DeviceNo[0]) {
        LastDiscrepancy = 0;
        LastDeviceFlag = 0;
        LastFamilyDiscrepancy = 0;
        search_result = 0;
    }
    
    return search_result;
}

/**
 * \brief Find the 'first' devices on the 1-Wire bus
 * \param pin  Pointer to the pin instance
 * \return 1 if device is found and ROM number(ID) will be stored in DeviceNo. 0 if not.
 */
static uint8_t OW_First(Pin *pin)
{
   /* reset the search state */
   LastDiscrepancy = 0;
   LastDeviceFlag = 0;
   LastFamilyDiscrepancy = 0;

   return OW_Search(pin);
}

/**
 * \brief Find the 'next' devices on the 1-Wire bus
 * \param pin  Pointer to the pin instance
 * \return 1 if device is found and ROM number(ID) will be stored in DeviceNo. 0 if not.
 */
static uint8_t OW_Next(Pin *pin)
{
   /* leave the search state alone */
   return OW_Search(pin);
}

/**
 * \brief Search device(s) on the 1-Wire bus
 * \param pin  Pointer to the pin instance
 * \param expected_num  The expected number of device on 1-wire bus
 * \return The number of device found
 */
extern uint32_t OW_SearchDevice(Pin *pin, uint8_t *device_no, const uint32_t expected_num)
{
    uint32_t moreDevice, i, cnt = 0;
    uint32_t j = expected_num;

    moreDevice = OW_First(pin);
    while (moreDevice && j) {
        /* Store device info */
        DeviceFound = ++cnt;
        for (i = 8; i > 0; i--) {
            (device_no + (expected_num - j) * 8)[i - 1] = DeviceNo[i - 1];
        }

        j--;

        moreDevice = OW_Next(pin);
    }
    
    return cnt;
}

/**
 * \brief Read the memory from the specified address
 * \param pin  Pointer to the pin instance
 * \param addrh  The higher 8 bits of the memory address
 * \param addrl  The lower 8 bits of the memory address
 * \param bytes  The number of bytes to be read
 * \param pData  Point to where the data read is stored
 * \retval Bytes read
 */
extern uint32_t OW_ReadMemory(Pin      *pin, 
                              uint8_t  *device_no, 
                              uint16_t addr, 
                              uint8_t  *pData, 
                              uint32_t size)
{
    uint32_t i;
    uint8_t addrh = (uint8_t)((addr & 0xFF00) >> 8);
    uint8_t addrl = (uint8_t)(addr & 0xFF);
    
    OW_Reset(pin);
    OW_WriteByte(pin, ROM_COMMAND_MATCH);
        
    for(i = 0; i < 8; i++) {
        OW_WriteByte(pin, device_no[i]);
    }

   
    OW_WriteByte(pin, MEMORY_COMMAND_READMEMORY);
    
    OW_WriteByte(pin, addrl);
    OW_WriteByte(pin, addrh);    
    
    for (i = 0; size > 0; size--) {
        pData[i] = OW_ReadByte(pin);
        i++;
    }

    return i;
}

/**
 * \brief Read the memory from the specified address
 * \param pin  Pointer to the pin instance
 * \param addrh  The higher 8 bits of the memory address
 * \param addrl  The lower 8 bits of the memory address
 * \param bytes  The number of bytes to be written
 * \param pData  Point to where the data read is stored
 * \retval Bytes written
 */
extern uint32_t OW_WriteMemory(Pin      *pin, 
                               uint8_t  *device_no, 
                               uint16_t addr, 
                               uint8_t  *pData,
                               uint32_t size)
{
    uint32_t i, j;
    uint8_t addrh, addrl;
    uint8_t buffer[DS2433_SIZE_SCRATCHPAD + 5];
    
    uint32_t scratchpad_size = 0;
    
    if (FAMILY_CODE_DS2431 == device_no[0]) {
        scratchpad_size = DS2431_SIZE_SCRATCHPAD;
    } else if (FAMILY_CODE_DS2433 == device_no[0]) {
        scratchpad_size = DS2433_SIZE_SCRATCHPAD;
    } else {
        TRACE_INFO("Unknown family code\r\n");
        return 0;
    }
    
    for (i = 0; i < size; i += scratchpad_size) {
        /* Write Scratchpad */
        OW_Reset(pin);
        OW_WriteByte(pin, ROM_COMMAND_MATCH);
        
        for(j = 0; j < 8; j++) {
            OW_WriteByte(pin, device_no[j]);
        }

        addrh = (uint8_t)((addr & 0xFF00) >> 8);
        addrl = (uint8_t)(addr & 0xFF);
        addr += scratchpad_size;
        
        OW_WriteScratchpad(pin, addrh, addrl, scratchpad_size, pData + i);
        
        /* Read and compare Scratchpad */
        OW_Reset(pin);
        OW_WriteByte(pin, ROM_COMMAND_MATCH);
        
        for(j = 0; j < 8; j++) {
            OW_WriteByte(pin, device_no[j]);
        }
        OW_ReadScratchpad(pin, scratchpad_size, buffer);

        /* Copy Scratchpad */
        OW_Reset(pin);
        OW_WriteByte(pin, ROM_COMMAND_MATCH);

        for(j = 0; j < 8; j++) {
            OW_WriteByte(pin, device_no[j]);
        }

        OW_CopyScratchpad(pin, buffer);
    }

    return size;
}
