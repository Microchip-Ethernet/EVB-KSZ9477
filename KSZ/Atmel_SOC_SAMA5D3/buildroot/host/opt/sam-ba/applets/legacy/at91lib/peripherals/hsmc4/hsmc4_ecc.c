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
#include "hsmc4_ecc.h"
#include <utility/trace.h>
#include <utility/assert.h>

//------------------------------------------------------------------------------
//         Internal function
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/// Counts and return the number of bits set to '1' in the given byte.
/// \param byte  Byte to count.
//------------------------------------------------------------------------------
static unsigned char CountBitsInByte(unsigned char byte)
{
    unsigned char count = 0;
    while (byte > 0) {

        if (byte & 1) {

            count++;
        }
        byte >>= 1;
    }

    return count;
}
//------------------------------------------------------------------------------
/// Counts and return the number of bits set to '1' in the given hsiao code.
/// \param code  Hsizo code.
//------------------------------------------------------------------------------
static unsigned char CountBitsInCode(unsigned char *code)
{
    return CountBitsInByte(code[0])
           + CountBitsInByte(code[1])
           + CountBitsInByte(code[2]);
}

//------------------------------------------------------------------------------
/// Get all ECC parity and Nparity value.
//------------------------------------------------------------------------------
void HSMC4_EccGetValue(unsigned int *ecc)
{
   ecc[0] = AT91C_BASE_HSMC4->HSMC4_ECCPR0; 
   ecc[1] = AT91C_BASE_HSMC4->HSMC4_ECCPR1; 
   ecc[2] = AT91C_BASE_HSMC4->HSMC4_ECCPR2; 
   ecc[3] = AT91C_BASE_HSMC4->HSMC4_ECCPR3; 
   ecc[4] = AT91C_BASE_HSMC4->HSMC4_ECCPR4; 
   ecc[5] = AT91C_BASE_HSMC4->HSMC4_ECCPR5; 
   ecc[6] = AT91C_BASE_HSMC4->HSMC4_ECCPR6; 
   ecc[7] = AT91C_BASE_HSMC4->HSMC4_ECCPR7; 
   ecc[8] = AT91C_BASE_HSMC4->HSMC4_ECCPR8; 
   ecc[9] = AT91C_BASE_HSMC4->HSMC4_ECCPR9; 
   ecc[10] = AT91C_BASE_HSMC4->HSMC4_ECCPR10; 
   ecc[11] = AT91C_BASE_HSMC4->HSMC4_ECCPR11; 
   ecc[12] = AT91C_BASE_HSMC4->HSMC4_ECCPR12; 
   ecc[13] = AT91C_BASE_HSMC4->HSMC4_ECCPR13; 
   ecc[14] = AT91C_BASE_HSMC4->HSMC4_ECCPR14; 
   ecc[15] = AT91C_BASE_HSMC4->HSMC4_Eccpr15; 
#ifdef DUMP_ECC_PARITY   
      TRACE_INFO("Ecc parity(0-7) %x, %x, %x, %x, %x, %x, %x, %x \n\r",ecc[0],ecc[1],ecc[2],ecc[3],ecc[4],ecc[5],ecc[6],ecc[7]);
      TRACE_INFO("Ecc parity(8-15) %x, %x, %x, %x, %x, %x, %x, %x \n\r",ecc[8],ecc[9],ecc[10],ecc[11],ecc[12],ecc[13],ecc[14],ecc[15]);
#endif   
}

//------------------------------------------------------------------------------
//         Exported functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/// Configures ECC mode in HSMC4 peripheral as specified. 
/// \param type  Type of correction.
/// \param pageSize  Page size of NAND flash device.
//------------------------------------------------------------------------------
void HSMC4_EccConfigure(unsigned int type, unsigned int pageSize)
{
    // Software Reset ECC.
    AT91C_BASE_HSMC4->HSMC4_ECCCR = (0x1 <<  1) ;
    AT91C_BASE_HSMC4->HSMC4_ECCCMD = type | pageSize;
}

//------------------------------------------------------------------------------
/// Returns type of ECC correction setting.
//------------------------------------------------------------------------------
unsigned int HSMC4_GetEccCorrectoinType(void)
{
    return ((AT91C_BASE_HSMC4->HSMC4_ECCCMD)& AT91C_ECC_TYPCORRECT);
}

//------------------------------------------------------------------------------
/// Returns ECC status by giving ecc number
/// \param eccNumber  ecc parity number from 0 to 15.
//------------------------------------------------------------------------------
unsigned char HSMC4_GetEccStatus(unsigned char eccNumber)
{
    unsigned int status;
    if (eccNumber < 8){
        status = AT91C_BASE_HSMC4->HSMC4_ECCSR1;
    } 
    else {
        status = AT91C_BASE_HSMC4->HSMC4_ECCSR2;
        eccNumber -=8;
    }
    return ((status >> (eccNumber * 4)) & 0x07);
}
//------------------------------------------------------------------------------
/// Verifies 4-bytes hsiao codes for a data block whose size is a page Size
/// word. Page words block is verified between the given HSIAO code 
/// generated by hardware and original HSIAO codes store has been previously stored.
/// Returns 0 if the data is correct, Hsiao_ERROR_SINGLEBIT if one or more
/// block(s) have had a single bit corrected, or either Hsiao_ERROR_ECC
/// or Hsiao_ERROR_MULTIPLEBITS.
/// \param data  Data buffer to verify.
/// \param originalCode  Original codes.
/// \param verifyCode  codes to be verified.
//------------------------------------------------------------------------------
static unsigned char HSMC4_VerifyPageOf8bitHsiao(
    unsigned char *data,
    const unsigned char *originalCode,
    const unsigned char *verifyCode)
{
    unsigned char correctionCode[4];
    unsigned char bitCount;
    // Xor both codes together
    correctionCode[0] = verifyCode[0] ^ originalCode[0];
    correctionCode[1] = verifyCode[1] ^ originalCode[1];
    correctionCode[2] = verifyCode[2] ^ originalCode[2];
    correctionCode[3] = verifyCode[3] ^ originalCode[3];
    TRACE_DEBUG("Correction code = %02X %02X %02X %02X\n\r",
                correctionCode[0], correctionCode[1], correctionCode[2], correctionCode[3]);
    // If all bytes are 0, there is no error
    if ((correctionCode[0] == 0)
        && (correctionCode[1] == 0)
        && (correctionCode[2] == 0)
        && (correctionCode[3] == 0)) {

        return 0;
    }
     // If there is a single bit error, there are 15 bits set to 1
    bitCount = CountBitsInByte(correctionCode[0]) + 
               CountBitsInByte(correctionCode[1]) + 
               CountBitsInByte(correctionCode[2]) + 
               CountBitsInByte(correctionCode[3]);
    if (bitCount == 15) {
        // Get byte and bit indexes
        unsigned short byte = (correctionCode[0] & 0xf0) >> 4;
        byte |= (correctionCode[1] & 0xff) << 4;
        unsigned char bit = correctionCode[0] & 0x0f;
        // Correct bit
        TRACE_INFO("Correcting byte #%d at bit %d\n\r", byte, bit);
        data[byte] ^= (1 << bit);

        return Hsiao_ERROR_SINGLEBIT;
    }
   
    // Check if ECC has been corrupted
    if (bitCount == 1) {
        return Hsiao_ERROR_ECC;
    }
    // Otherwise, this is a multi-bit error
    else {
        return Hsiao_ERROR_MULTIPLEBITS;
    }
}

//------------------------------------------------------------------------------
/// Verifies 3-bytes hsiao codes for a data block whose size is multiple of
/// 256 bytes. Each 256-bytes block is verified between the given HSIAO code 
/// generated by hardware and original HSIAO codes store has been previously stored.
/// Returns 0 if the data is correct, Hsiao_ERROR_SINGLEBIT if one or more
/// block(s) have had a single bit corrected, or either Hsiao_ERROR_ECC
/// or Hsiao_ERROR_MULTIPLEBITS.
/// \param data  Data buffer to verify.
/// \param size  Size of the data in words.
/// \param originalCode  Original codes.
/// \param verifyCode  codes to be verified.
//------------------------------------------------------------------------------
static unsigned char HSMC4_Verify256x8bitHsiao(
    unsigned char *data,
    unsigned int size,
    const unsigned char *originalCode,
    const unsigned char *verifyCode)
{
    unsigned char correctionCode[3];
    unsigned int position = 0;
    unsigned char byte;
    unsigned char bit;
    unsigned char error = 0;
    
    TRACE_DEBUG("HSMC4_Verify512x8bitHsiao()\n\r");
    while (position < size) {
        // Xor both codes together
        correctionCode[0] = verifyCode[0] ^ originalCode[0];
        correctionCode[1] = verifyCode[1] ^ originalCode[1];
        correctionCode[2] = verifyCode[2] ^ originalCode[2];
        TRACE_DEBUG("Correction code = %02X %02X %02X\n\r",
            correctionCode[0], correctionCode[1], correctionCode[2]);
            
        // If all bytes are 0, there is no error
        if ( correctionCode[0] || correctionCode[1] || correctionCode[2]) {
            // If there is a single bit error, there are 11 bits set to 1
            if (CountBitsInCode(correctionCode) == 11) {
                // Get byte and bit indexes
                byte = (correctionCode[0] & 0xf8) >> 3;
                byte |= (correctionCode[1] & 0x07) << 5;
                bit = correctionCode[0] & 0x07;
                // Correct bit
                TRACE_INFO("Correcting byte #%d at bit %d\n\r", (position + byte), bit);
                data[byte] ^= (1 << bit);
                error = Hsiao_ERROR_SINGLEBIT;
            }
            // Check if ECC has been corrupted
            else if (CountBitsInCode(correctionCode) == 1) {
                return Hsiao_ERROR_ECC;
            }
            else {
                // Otherwise, this is a multi-bit error
                return Hsiao_ERROR_MULTIPLEBITS;
            }
        }
        data += 256;
        originalCode += 3;
        verifyCode += 3;
        position += 256;
    }
    return error;
}

//------------------------------------------------------------------------------
/// Verifies 3-bytes hsiao codes for a data block whose size is multiple of
/// 512 bytes. Each 512-bytes block is verified between the given HSIAO code 
/// generated by hardware and original HSIAO codes store has been previously stored.
/// Returns 0 if the data is correct, Hsiao_ERROR_SINGLEBIT if one or more
/// block(s) have had a single bit corrected, or either Hsiao_ERROR_ECC
/// or Hsiao_ERROR_MULTIPLEBITS.
/// \param data  Data buffer to verify.
/// \param size  Size of the data in words.
/// \param originalCode  Original codes.
/// \param verifyCode  codes to be verified.
//------------------------------------------------------------------------------
static unsigned char HSMC4_Verify512x8bitHsiao(
    unsigned char *data,
    unsigned int size,
    const unsigned char *originalCode,
    const unsigned char *verifyCode)
{
    unsigned char correctionCode[3];
    unsigned int position = 0;
    unsigned short byte;
    unsigned char bit;
    unsigned char error = 0;
    
    TRACE_DEBUG("HSMC4_Verify512x8bitHsiao()\n\r");
    while (position < size) {
        // Xor both codes together
        correctionCode[0] = verifyCode[0] ^ originalCode[0];
        correctionCode[1] = verifyCode[1] ^ originalCode[1];
        correctionCode[2] = verifyCode[2] ^ originalCode[2];
        TRACE_DEBUG("Correction code = %02X %02X %02X\n\r",
            correctionCode[0], correctionCode[1], correctionCode[2]);
            
        // If all bytes are 0, there is no error
        if ( correctionCode[0] || correctionCode[1] || correctionCode[2]) {
            // If there is a single bit error, there are 11 bits set to 1
            if (CountBitsInCode(correctionCode) == 12) {
                // Get byte and bit indexes
                byte = (correctionCode[0] & 0xf8) >> 3;
                byte |= (correctionCode[1] & 0x0f) << 5;
                bit = correctionCode[0] & 0x07;
                // Correct bit
                TRACE_INFO("Correcting byte #%d at bit %d\n\r", (position + byte), bit);
                data[byte] ^= (1 << bit);
                error = Hsiao_ERROR_SINGLEBIT;
            }
            // Check if ECC has been corrupted
            else if (CountBitsInCode(correctionCode) == 1) {
                return Hsiao_ERROR_ECC;
            }
            else {
                // Otherwise, this is a multi-bit error
                return Hsiao_ERROR_MULTIPLEBITS;
            }
        }
        data += 512;
        originalCode += 3;
        verifyCode += 3;
        position += 512;
    }
    return error;
}

//------------------------------------------------------------------------------
/// Verifies 4-bytes hsiao codes for a data block whose size is a page Size
/// word. Page words block is verified between the given HSIAO code 
/// generated by hardware and original HSIAO codes store has been previously stored.
/// Returns 0 if the data is correct, Hsiao_ERROR_SINGLEBIT if one or more
/// block(s) have had a single bit corrected, or either Hsiao_ERROR_ECC
/// or Hsiao_ERROR_MULTIPLEBITS.
/// \param data  Data buffer to verify.
/// \param originalCode  Original codes.
/// \param verifyCode  codes to be verified.
//------------------------------------------------------------------------------
static unsigned char HSMC4_VerifyPageOf16bitHsiao(
    unsigned short *data,
    const unsigned char *originalCode,
    const unsigned char *verifyCode)
{
    unsigned char correctionCode[4];
    unsigned char bitCount;
    // Xor both codes together
    correctionCode[0] = verifyCode[0] ^ originalCode[0];
    correctionCode[1] = verifyCode[1] ^ originalCode[1];
    correctionCode[2] = verifyCode[2] ^ originalCode[2];
    correctionCode[3] = verifyCode[3] ^ originalCode[3];
    TRACE_DEBUG("Correction code = %02X %02X %02X %02X\n\r",
                correctionCode[0], correctionCode[1], correctionCode[2], correctionCode[3]);
    // If all bytes are 0, there is no error
    if ((correctionCode[0] == 0)
        && (correctionCode[1] == 0)
        && (correctionCode[2] == 0)
        && (correctionCode[3] == 0)) {

        return 0;
    }
     // If there is a single bit error, there are 11 bits set to 1
    bitCount = CountBitsInByte(correctionCode[0]) + 
               CountBitsInByte(correctionCode[1]) + 
               CountBitsInByte(correctionCode[2]) + 
               CountBitsInByte(correctionCode[3]);
    printf("bitCount = %d \n\r",bitCount);
    if (bitCount == 12) {
        // Get byte and bit indexes
        unsigned char word = (correctionCode[0] & 0xf0) >> 4;
        word |= (correctionCode[1] & 0xff) << 4;
        unsigned char bit = correctionCode[0] & 0x0f;
        // Correct bit
        TRACE_INFO("Correcting word #%d at bit %d\n\r", word, bit);
        data[word] ^= (1 << bit);

        return Hsiao_ERROR_SINGLEBIT;
    }
   
    // Check if ECC has been corrupted
    if (bitCount == 1) {
        return Hsiao_ERROR_ECC;
    }
    // Otherwise, this is a multi-bit error
    else {
        return Hsiao_ERROR_MULTIPLEBITS;
    }
}

//------------------------------------------------------------------------------
/// Verifies 3-bytes hsiao codes for a data block whose size is multiple of
/// 256 word.Each 256-words block is verified between the given HSIAO code 
/// generated by hardware and original HSIAO codes store has been previously stored.
/// Returns 0 if the data is correct, Hsiao_ERROR_SINGLEBIT if one or more
/// block(s) have had a single bit corrected, or either Hsiao_ERROR_ECC
/// or Hsiao_ERROR_MULTIPLEBITS.
/// \param data  Data buffer to verify.
/// \param size  Size of the data in words.
/// \param originalCode  Original codes.
/// \param verifyCode  codes to be verified.
//------------------------------------------------------------------------------
static unsigned char HSMC4_Verify256x16bitHsiao(
    unsigned short *data,
    unsigned int size,
    const unsigned char *originalCode,
    const unsigned char *verifyCode
    )
{
    unsigned char correctionCode[3];
    unsigned int position = 0;
    unsigned char word;
    unsigned char bit;
    unsigned char error = 0;
    
    TRACE_DEBUG("HSMC4_Verify512x8bitHsiao()\n\r");
    while (position < size) {
        // Xor both codes together
        correctionCode[0] = verifyCode[0] ^ originalCode[0];
        correctionCode[1] = verifyCode[1] ^ originalCode[1];
        correctionCode[2] = verifyCode[2] ^ originalCode[2];
        TRACE_DEBUG("Correction code = %02X %02X %02X\n\r",
            correctionCode[0], correctionCode[1], correctionCode[2]);
            
        // If all bytes are 0, there is no error
        if ( correctionCode[0] || correctionCode[1] || correctionCode[2]) {
            // If there is a single bit error, there are 11 bits set to 1
            if (CountBitsInCode(correctionCode) == 12) {
                // Get word and bit indexes
                word = (correctionCode[0] & 0xf0) >> 4;
                word |= (correctionCode[1] & 0x0f) << 4;
                bit = correctionCode[0] & 0x0f;
                // Correct bit
                TRACE_INFO("Correcting word #%d at bit %d\n\r", (position + word), bit);
                data[word] ^= (1 << bit);
                error = Hsiao_ERROR_SINGLEBIT;
            }
            // Check if ECC has been corrupted
            else if (CountBitsInCode(correctionCode) == 1) {
                return Hsiao_ERROR_ECC;
            }
            else {
                // Otherwise, this is a multi-bit error
                return Hsiao_ERROR_MULTIPLEBITS;
            }
        }
        data += 256;
        originalCode += 3;
        verifyCode += 3;
        position += 256;
    }
    return error;
}

//------------------------------------------------------------------------------
/// Verifies hsiao codes for a data block. The block is verified between the given 
/// HSIAO code generated by hardware and original HSIAO codes store has been 
/// previously stored.
/// Returns 0 if the data is correct, Hsiao_ERROR_SINGLEBIT if one or more
/// block(s) have had a single bit corrected, or either Hsiao_ERROR_ECC
/// or Hsiao_ERROR_MULTIPLEBITS.
/// \param data  Data buffer to verify.
/// \param size  Size of the data in words.
/// \param originalCode  Original codes.
/// \param verifyCode  codes to be verified.
/// \param dataPath 8bit/16bit data path.
//------------------------------------------------------------------------------
unsigned char HSMC4_VerifyHsiao(
    unsigned char *data,
    unsigned int size,
    const unsigned char *originalCode,
    const unsigned char *verifyCode,
    unsigned char dataPath)
{
    unsigned char correctionType;
    unsigned char error = 0;
    correctionType = HSMC4_GetEccCorrectoinType();
    // For 16-bit data path
    if (dataPath == 16) {
        switch (correctionType){
            case AT91C_ECC_TYPCORRECT_ONE_PER_PAGE:
                error = HSMC4_VerifyPageOf16bitHsiao((unsigned short*)data, originalCode, verifyCode);
                break;
            case AT91C_ECC_TYPCORRECT_ONE_EVERY_256_BYTES:
                error= HSMC4_Verify256x16bitHsiao((unsigned short*)data, size / 2, originalCode, verifyCode);
                break;
            case AT91C_ECC_TYPCORRECT_ONE_EVERY_512_BYTES:
                TRACE_WARNING("16-bit 512 per page correction not yet implement! \n\r");
                break;
        }
    }
    // For 8-bit data path
    else {
        switch (correctionType){
            case AT91C_ECC_TYPCORRECT_ONE_PER_PAGE:
                error = HSMC4_VerifyPageOf8bitHsiao(data, originalCode, verifyCode);
                break;
            case AT91C_ECC_TYPCORRECT_ONE_EVERY_256_BYTES:
                 error = HSMC4_Verify256x8bitHsiao(data, size, originalCode, verifyCode);
                 break;
            case AT91C_ECC_TYPCORRECT_ONE_EVERY_512_BYTES:
                error = HSMC4_Verify512x8bitHsiao(data, size, originalCode, verifyCode);
                break;
        }
    }
    return error;
}

//------------------------------------------------------------------------------
/// Get 32-bit ECC code for 16-bit data path NAND flash.
/// 32-bit ECC is generated in order to perform one bit correction 
/// for a page in page 512/1024/2048/4096 for 16-bit words
/// \param size  Data size in bytes.
/// \param code  Codes buffer.
//------------------------------------------------------------------------------
void HSMC4_Get24bitPerPageEcc(unsigned int pageDataSize, unsigned char *code)
{
    unsigned int eccParity;
    unsigned int eccNparity;
    unsigned int ecc[16];
    // Get Parity value.
    HSMC4_EccGetValue(ecc);
     
    //  ----   P16384'P8192'P4096'P2048'  P1024'P512'P256' ---  4th. Ecc Byte to store
    /// P128'  P64'   P32'  P16'  P8'     P4'   P2'  P1'   ---  3rd. Ecc Byte to store
    //  ----   P16384 P8192 P4096 P2048   P1024 P512 P256  ---  2nd. Ecc Byte to store
    //  P128   P64    P32   P16   P8      P4    P2   P1    ---  1st. Ecc Byte to store
    
    // Invert codes (linux compatibility)    
    eccParity = ~(ecc[0]);
    eccNparity = ~(ecc[1]);
    TRACE_DEBUG("ecc Parity is 0x%08x, ecc Nparity is 0x%08x \n\r", eccParity, eccNparity);
    code[0] = eccParity & 0xff;
    code[1] = (eccParity >> 8 )& 0xff;
    code[2] = eccNparity & 0xff;
    code[3] = (eccNparity >> 8 )& 0xff;
}

//------------------------------------------------------------------------------
/// Get 24-bit ECC code for 8-bit data path NAND flash.
/// 24-bit ECC is generated in order to perform one bit correction 
/// for 256 byte in page 512/1024/2048/4096 for 8-bit words
/// \param size  Data size in bytes.
/// \param code  Codes buffer.
//------------------------------------------------------------------------------
void HSMC4_Get24bitPer256Ecc(unsigned int pageDataSize, unsigned char *code)
{
    unsigned char i;
    unsigned char numEcc;
    unsigned int eccParity;
    unsigned int ecc[16];
    HSMC4_EccGetValue(ecc);
    numEcc = pageDataSize / 256;
  
    //  P2048' P1024' P512' P256' P128'   P64'  P32' P16'  ---  3rd. Ecc Byte to store
    //  P8'    P4'    P2'   P1'   P2048   P1024 P512 P256  ---  2nd. Ecc Byte to store
    //  P128   P64    P32   P16   P8      P4    P2   P1    ---  1st. Ecc Byte to store
    for (i = 0; i < numEcc; i++) {
        // Get Parity and NParity value.
        eccParity = ecc[i];
        // Invert codes (linux compatibility)
        eccParity = ~eccParity; 
        TRACE_DEBUG("ecc Parity%d is 0x%08x \n\r", i, eccParity);
        code[i * 3] = eccParity & 0xff;
        code[i * 3 + 1] = (eccParity >> 8) & 0xff;
        code[i * 3 + 2] = (eccParity >> 16) & 0xff;
    }
}

//------------------------------------------------------------------------------
/// Get 24-bit ECC code for 8-bit data path NAND flash.
/// 24-bit ECC is generated in order to perform one bit correction 
/// for 512 byte in page 512/1024/2048/4096 for 8-bit words
/// \param size  Data size in bytes.
/// \param code  Codes buffer.
//------------------------------------------------------------------------------
void HSMC4_Get24bitPer512Ecc(unsigned int pageDataSize, unsigned char *code)
{
    unsigned char i;
    unsigned char numEcc;
    unsigned int eccParity;
    unsigned int ecc[16];
    HSMC4_EccGetValue(ecc);
    numEcc = pageDataSize / 512;
  
    //  P2048' P1024' P512' P256' P128'   P64'  P32' P16'  ---  3rd. Ecc Byte to store
    //  P8'    P4'    P2'   P1'   P2048   P1024 P512 P256  ---  2nd. Ecc Byte to store
    //  P128   P64    P32   P16   P8      P4    P2   P1    ---  1st. Ecc Byte to store
    for (i = 0; i < numEcc; i++) {
        // Get Parity and NParity value.
        eccParity = ecc[i];
        // Invert codes (linux compatibility)
        eccParity = ~eccParity; 
        TRACE_DEBUG("ecc Parity%d is 0x%08x \n\r", i, eccParity);
        code[i * 3] = eccParity & 0xff;
        code[i * 3 + 1] = (eccParity >> 8) & 0xff;
        code[i * 3 + 2] = (eccParity >> 16) & 0xff;
    }
}

//------------------------------------------------------------------------------
/// Get 32-bit ECC code for 16-bit data path NAND flash.
/// 32-bit ECC is generated in order to perform one bit correction 
/// for 256 word in page 512/1024/2048/4096 for 16-bit words
/// \param size  Data size in bytes.
/// \param code  Codes buffer.
//------------------------------------------------------------------------------
void HSMC4_Get32bitPer256Ecc(unsigned int pageDataSize, unsigned char *code)
{
    unsigned char i;
    unsigned char numEcc;
    unsigned int eccParity;
    unsigned int eccNparity;
    unsigned int ecc[16];
    HSMC4_EccGetValue(ecc);
    numEcc = pageDataSize / 256;

    //  P2048' P1024' P512' P256' P128'   P64'  P32' P16'  ---  3rd. Ecc Byte to store
    //  P8'    P4'    P2'   P1'   P2048   P1024 P512 P256  ---  2nd. Ecc Byte to store
    //  P128   P64    P32   P16   P8      P4    P2   P1    ---  1st. Ecc Byte to store
    for (i = 0; i < numEcc; i+= 2) {
        // Get Parity value.
        eccParity = ecc[i];
        // Invert codes (linux compatibility)
        eccParity = ~eccParity; 
        // Get NParity value.
        eccNparity = ecc[i + 1];
        eccNparity = ~eccNparity;
        TRACE_DEBUG("ecc Parity%d is 0x%08x, ecc Nparity%d is 0x%08x \n\r", i, eccParity, i, eccNparity);
        code[i * 3] = eccParity & 0xff;
        code[i * 3 + 1] = ((eccParity >> 8) & 0x0f ) | ((eccNparity & 0x0f) << 4);
        code[i * 3 + 2] = (eccNparity >> 4) & 0xff;

        code[(i + 1) * 3] = (eccParity >> 16) & 0xff;
        code[(i + 1) * 3 + 1] = ((eccParity >> 24) & 0x0f ) | (((eccNparity >> 16)& 0x0f) << 4);
        code[(i + 1) * 3 + 2] =  (eccNparity >> 20) & 0xff;

    }
}

//------------------------------------------------------------------------------
/// Get 32-bit ECC code for 16-bit data path NAND flash.
/// 32-bit ECC is generated in order to perform one bit correction 
/// for a page in page 512/1024/2048/4096 for 16-bit words
/// \param size  Data size in bytes.
/// \param code  Codes buffer.
//------------------------------------------------------------------------------
void HSMC4_Get32bitPerPageEcc(unsigned int pageDataSize, unsigned char *code)
{
    unsigned int eccParity;
    unsigned int eccNparity;
    unsigned int ecc[16];
    // Get Parity value.
    HSMC4_EccGetValue(ecc);
     
    //  ----   P16384'P8192'P4096'P2048'  P1024'P512'P256' ---  4th. Ecc Byte to store
    /// P128'  P64'   P32'  P16'  P8'     P4'   P2'  P1'   ---  3rd. Ecc Byte to store
    //  ----   P16384 P8192 P4096 P2048   P1024 P512 P256  ---  2nd. Ecc Byte to store
    //  P128   P64    P32   P16   P8      P4    P2   P1    ---  1st. Ecc Byte to store
    
    // Invert codes (linux compatibility)    
    eccParity = ~(ecc[0]);
    eccNparity = ~(ecc[1]);
    TRACE_DEBUG("ecc Parity%d is 0x%08x, ecc Nparity%d is 0x%08x \n\r", eccParity, eccNparity);
    code[0] = eccParity & 0xff;
    code[1] = (eccParity >> 8 )& 0xff;
    code[2] = eccNparity & 0xff;
    code[3] = (eccNparity >> 8 )& 0xff;
}

//------------------------------------------------------------------------------
/// Get ECC code for 8bit/16-bit data path NAND flash by giving data path.
/// 24-bit or 32-bit ECC is generated in order to perform one bit correction 
/// for a page in page 512/1024/2048/4096.
/// \param size  Data size in bytes.
/// \param code  Codes buffer.
/// \param dataPath 8bit/16bit data path.
//------------------------------------------------------------------------------
void HSMC4_GetEccParity(unsigned int pageDataSize, unsigned char *code, unsigned char dataPath)
{
    unsigned char correctionType;
    correctionType = HSMC4_GetEccCorrectoinType();
    // For 16-bit data path
    if (dataPath == 16) {
        switch (correctionType){
            case AT91C_ECC_TYPCORRECT_ONE_PER_PAGE:
                HSMC4_Get32bitPerPageEcc(pageDataSize, code);
                break;
            case AT91C_ECC_TYPCORRECT_ONE_EVERY_256_BYTES:
                HSMC4_Get32bitPer256Ecc(pageDataSize, code);
                break;
            case AT91C_ECC_TYPCORRECT_ONE_EVERY_512_BYTES:
                TRACE_WARNING("16 bit  512 byte correct not yet implement! \n\r");
                break;
        }
    }
    // For 8-bit data path
    else {
        switch (correctionType){
            case AT91C_ECC_TYPCORRECT_ONE_PER_PAGE:
                HSMC4_Get24bitPerPageEcc(pageDataSize, code);
                break;
            case AT91C_ECC_TYPCORRECT_ONE_EVERY_256_BYTES:
                 HSMC4_Get24bitPer256Ecc(pageDataSize, code);
                 break;
            case AT91C_ECC_TYPCORRECT_ONE_EVERY_512_BYTES:
                HSMC4_Get24bitPer512Ecc(pageDataSize, code);
                break;
        }
    }
}