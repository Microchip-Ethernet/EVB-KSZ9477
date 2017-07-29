/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2010, Atmel Corporation
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
  *  \file
  *
  *  Implementation of NFC functions.
  */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"
/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Check if NFC command has done.
 * \param pSmc Pointer to a Smc instance.
 *
 * \return Returns 1 if NFC controller has terminated the command,
 *         otherwise returns 0.
 */
static uint8_t SMC_NFC_CommandDone(Smc* pSmc)
{
    return ((pSmc->SMC_SR & SMC_SR_CMDDONE) == SMC_SR_CMDDONE);
}

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Sets NFC configuration.
 * \param pSmc Pointer to a Smc instance.
 * \param cfg  NFC configuration.
 */
void SMC_NFC_Configure(Smc* pSmc, uint32_t cfg)
{
    pSmc->SMC_CFG = cfg;
}

/**
 * \brief Reset NFC controller.
 * \param pSmc Pointer to a Smc instance.
 */
void SMC_NFC_Reset(Smc* pSmc)
{
    /* Disable all the SMC NFC interrupts */
    pSmc->SMC_IDR = 0xFFFFFFFF;
    pSmc->SMC_CTRL = 0;
}

/**
 * \brief Enable NFC controller.
 * \param pSmc Pointer to a Smc instance.
 */
void SMC_NFC_EnableNfc(Smc* pSmc)
{
    pSmc->SMC_CTRL = SMC_CTRL_NFCEN;
}

/**
 * \brief Enable NFC controller reads both main and spare area in read mode.
 * \param pSmc Pointer to a Smc instance.
 */
void SMC_NFC_EnableSpareRead(Smc* pSmc)
{
    pSmc->SMC_CFG |= SMC_CFG_RSPARE;
}

/**
 * \brief The NFC controller skips spare area in read mode.
 * \param pSmc Pointer to a Smc instance.
 */
void SMC_NFC_DisableSpareRead(Smc* pSmc)
{
    pSmc->SMC_CFG &= (~SMC_CFG_RSPARE);
}

/**
 * \brief Enables the NFC controller writes both main and spare area in write
 * \param pSmc Pointer to a Smc instance.
 */
void SMC_NFC_EnableSpareWrite(Smc* pSmc)
{
    pSmc->SMC_CFG |= SMC_CFG_WSPARE;
}

/**
 * \brief The NFC controller skips spare area in write mode.
 * \param pSmc Pointer to a Smc instance.
 */
void SMC_NFC_DisableSpareWrite(Smc* pSmc)
{
    pSmc->SMC_CFG &= (~SMC_CFG_WSPARE);
}

/**
 * \brief Check if spare area be read in read mode.
 * \param pSmc Pointer to a Smc instance.
 *
 * \return Returns 1 if NFC controller reads both main and spare area in
 *         read mode, otherwise returns 0.
 */
uint8_t SMC_NFC_isSpareRead(Smc* pSmc)
{
    return (((pSmc->SMC_CFG) >> 9) & 0x1);
}

/**
 * \brief Check if spare area be written in write mode.
 * \param pSmc Pointer to a Smc instance.
 *
 * \return Returns 1 if NFC controller writes both main and spare area in
 *         write mode, otherwise returns 0.
 */
uint8_t SMC_NFC_isSpareWrite(Smc* pSmc)
{
    return (((pSmc->SMC_CFG) >> 8) & 0x1);
}

/**
 * \brief Check if NFC transfer complete.
 * \param pSmc Pointer to a Smc instance.
 *
 * \return Returns 1 if NFC controller has terminated the data transmission,
 *         otherwise returns 0.
 */
uint8_t SMC_NFC_isTransferComplete(Smc* pSmc)
{
    return ((pSmc->SMC_SR & SMC_SR_XFRDONE) == SMC_SR_XFRDONE);
}

/**
 * \brief Check Ready/Busy line.
 * \param pSmc Pointer to a Smc instance.
 *
 * \return Returns 1 if  edge has been detected on the Ready/Busy line,
 *         otherwise returns 0.
 */
uint8_t SMC_NFC_isReadyBusy(Smc* pSmc)
{
    return ((pSmc->SMC_SR & SMC_SR_RB_EDGE0) == SMC_SR_RB_EDGE0);
}

/**
 * \brief Check if NFC Controller is busy.
 * \param pSmc Pointer to a Smc instance.
 *
 * \return Returns 1 if NFC Controller is activated and accesses the memory device,
 *         otherwise returns 0.
 */
uint8_t SMC_NFC_isNfcBusy(Smc* pSmc)
{
    return ((pSmc->SMC_SR & SMC_SR_NFCBUSY) == SMC_SR_NFCBUSY);
}

/**
 * \brief Get NFC Status.
 * \param pSmc Pointer to a Smc instance.
 *
 * \return Returns the current status register of SMC NFC Status Register.
 *         This resets the internal value of the status register, so further
 *         read may yield different values.
 */
uint32_t SMC_NFC_GetStatus(Smc* pSmc)
{
    return pSmc->SMC_SR;
}

/*
 * HOST command functions
 */

/**
 * \brief Check if the host controller is busy.
 * \return Returns 1 if the host controller is busy, otherwise returns 0.
 */
static uint8_t SMC_NFC_isHostBusy(void)
{
    return (((*((volatile uint32_t *) (NFC_CMD_BASE_ADDR + NFCADDR_CMD_NFCCMD))) & 0x8000000) == 0x8000000);
}

/**
 * \brief Uses the HOST nandflash conntroller to send a command to the NFC.
 * \param pSmc Pointer to a Smc instance.
 * \param cmd  command to send.
 * \param addressCycle  address cycle when command access id decoded.
 * \param cycle0  address at first cycle.
 */
void SMC_NFC_SendCommand(Smc* pSmc, uint32_t cmd, uint32_t addressCycle, uint32_t cycle0)
{
    volatile uint32_t *pCommandAddress;

    /* Wait until host controller is not busy. */
    while(SMC_NFC_isHostBusy());
    /* Send the command plus the ADDR_CYCLE */
    pCommandAddress = (volatile uint32_t *) (cmd + NFC_CMD_BASE_ADDR);
    pSmc->SMC_ADDR = cycle0;
    *pCommandAddress = addressCycle;
    while( !SMC_NFC_CommandDone(SMC));
}

/*
 * ECC functions
 */

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Counts and return the number of bits set to '1' in the given byte.
 * \param byte  Byte to count.
 */
static uint8_t ECC_CountBitsInByte(uint8_t byte)
{
    uint8_t count = 0;

    while (byte > 0) {

        if (byte & 1) {

            count++;
        }
        byte >>= 1;
    }

    return count;
}

/**
 * \brief Counts and return the number of bits set to '1' in the given hsiao code.
 * \param code  Hsiao code.
 */
static uint8_t ECC_CountBitsInCode(uint8_t *code)
{
    return ECC_CountBitsInByte(code[0])
           + ECC_CountBitsInByte(code[1])
           + ECC_CountBitsInByte(code[2]);
}

/**
 * \brief Get all ECC parity and Nparity value.
 * \param pSmc Pointer to a Smc instance.
 */
void SMC_ECC_GetValue(Smc* pSmc, uint32_t *ecc)
{
   ecc[0] = pSmc->SMC_ECC_PR0;
   ecc[1] = pSmc->SMC_ECC_PR1;
   ecc[2] = pSmc->SMC_ECC_PR2;
   ecc[3] = pSmc->SMC_ECC_PR3;
   ecc[4] = pSmc->SMC_ECC_PR4;
   ecc[5] = pSmc->SMC_ECC_PR5;
   ecc[6] = pSmc->SMC_ECC_PR6;
   ecc[7] = pSmc->SMC_ECC_PR7;
   ecc[8] = pSmc->SMC_ECC_PR8;
   ecc[9] = pSmc->SMC_ECC_PR9;
   ecc[10] = pSmc->SMC_ECC_PR10;
   ecc[11] = pSmc->SMC_ECC_PR11;
   ecc[12] = pSmc->SMC_ECC_PR12;
   ecc[13] = pSmc->SMC_ECC_PR13;
   ecc[14] = pSmc->SMC_ECC_PR14;
   ecc[15] = pSmc->SMC_ECC_PR15;
#ifdef DUMP_ECC_PARITY
      TRACE_INFO("Ecc parity(0-7) %x, %x, %x, %x, %x, %x, %x, %x \n\r",ecc[0],ecc[1],ecc[2],ecc[3],ecc[4],ecc[5],ecc[6],ecc[7]);
      TRACE_INFO("Ecc parity(8-15) %x, %x, %x, %x, %x, %x, %x, %x \n\r",ecc[8],ecc[9],ecc[10],ecc[11],ecc[12],ecc[13],ecc[14],ecc[15]);
#endif
}

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Configures ECC mode.
 * \param pSmc Pointer to a Smc instance.
 * \param type  Type of correction.
 * \param pageSize  Page size of NAND flash device.
 */
void SMC_ECC_Configure(Smc* pSmc, uint32_t type, uint32_t pageSize)
{
    /* Software Reset ECC. */
    pSmc->SMC_ECC_CTRL = (0x1 <<  1) ;
    pSmc->SMC_ECC_MD = type | pageSize;
}

/**
 * \brief Get ECC correction type.
 * \param pSmc Pointer to a Smc instance.
 *
 * \return Returns type of ECC correction setting.
 */
uint32_t SMC_ECC_GetCorrectoinType(Smc* pSmc)
{
    return ((pSmc->SMC_ECC_MD)& SMC_ECC_MD_TYPCORREC_Msk);
}

/**
 * \brief Get ECC status.
 * \param pSmc Pointer to a Smc instance.
 * \param eccNumber  ecc parity number from 0 to 15.
 *
 * \return Returns ECC status by giving ecc number.
 */
uint8_t SMC_ECC_GetStatus(Smc* pSmc, uint8_t eccNumber)
{
    uint32_t status;

    if (eccNumber < 8){
        status = pSmc->SMC_ECC_SR1;
    }
    else {
        status = pSmc->SMC_ECC_SR2;
        eccNumber -=8;
    }
    return ((status >> (eccNumber * 4)) & 0x07);
}

/**
 * \brief Verifies 4-bytes hsiao codes for a data block whose size is a page Size
 * word. Page words block is verified between the given HSIAO code
 * generated by hardware and original HSIAO codes store has been previously stored.
 * Returns 0 if the data is correct, Hsiao_ERROR_SINGLEBIT if one or more
 * block(s) have had a single bit corrected, or either Hsiao_ERROR_ECC
 * or Hsiao_ERROR_MULTIPLEBITS.
 *
 * \param data  Data buffer to verify.
 * \param originalCode  Original codes.
 * \param verifyCode  codes to be verified.
 */
static uint8_t SMC_ECC_VerifyPageOf8bitHsiao(
    uint8_t *data,
    const uint8_t *originalCode,
    const uint8_t *verifyCode)
{
    uint8_t correctionCode[4];
    uint8_t bitCount;

    /* Xor both codes together */
    correctionCode[0] = verifyCode[0] ^ originalCode[0];
    correctionCode[1] = verifyCode[1] ^ originalCode[1];
    correctionCode[2] = verifyCode[2] ^ originalCode[2];
    correctionCode[3] = verifyCode[3] ^ originalCode[3];
    TRACE_DEBUG("Correction code = %02X %02X %02X %02X\n\r",
                correctionCode[0], correctionCode[1], correctionCode[2], correctionCode[3]);
    /* If all bytes are 0, there is no error */
    if ((correctionCode[0] == 0)
        && (correctionCode[1] == 0)
        && (correctionCode[2] == 0)
        && (correctionCode[3] == 0)) {

        return 0;
    }
     /* If there is a single bit error, there are 15 bits set to 1 */
    bitCount = ECC_CountBitsInByte(correctionCode[0]) +
               ECC_CountBitsInByte(correctionCode[1]) +
               ECC_CountBitsInByte(correctionCode[2]) +
               ECC_CountBitsInByte(correctionCode[3]);
    if (bitCount == 15) {
        /* Get byte and bit indexes */
        uint16_t byte = (correctionCode[0] & 0xf0) >> 4;
        byte |= (correctionCode[1] & 0xff) << 4;
        uint8_t bit = correctionCode[0] & 0x0f;

        /* Correct bit */
        TRACE_INFO("Correcting byte #%d at bit %d\n\r", byte, bit);
        data[byte] ^= (1 << bit);

        return Hsiao_ERROR_SINGLEBIT;
    }

    /* Check if ECC has been corrupted */
    if (bitCount == 1) {
        return Hsiao_ERROR_ECC;
    }
    /* Otherwise, this is a multi-bit error */
    else {
        return Hsiao_ERROR_MULTIPLEBITS;
    }
}

/**
 * \brief Verifies 3-bytes hsiao codes for a data block whose size is multiple of
 * 256 bytes. Each 256-bytes block is verified between the given HSIAO code
 * generated by hardware and original HSIAO codes store has been previously stored.
 * Returns 0 if the data is correct, Hsiao_ERROR_SINGLEBIT if one or more
 * block(s) have had a single bit corrected, or either Hsiao_ERROR_ECC
 * or Hsiao_ERROR_MULTIPLEBITS.
 *
 * \param data  Data buffer to verify.
 * \param size  Size of the data in words.
 * \param originalCode  Original codes.
 * \param verifyCode  codes to be verified.
 */
static uint8_t SMC_ECC_Verify256x8bitHsiao(
    uint8_t *data,
    uint32_t size,
    const uint8_t *originalCode,
    const uint8_t *verifyCode)
{
    uint8_t correctionCode[3];
    uint32_t position = 0;
    uint8_t byte;
    uint8_t bit;
    uint8_t error = 0;

    TRACE_DEBUG("SMC_ECC_Verify256x8bitHsiao()\n\r");
    while (position < size) {
        /* Xor both codes together */
        correctionCode[0] = verifyCode[0] ^ originalCode[0];
        correctionCode[1] = verifyCode[1] ^ originalCode[1];
        correctionCode[2] = verifyCode[2] ^ originalCode[2];
        TRACE_DEBUG("Correction code = %02X %02X %02X\n\r",
            correctionCode[0], correctionCode[1], correctionCode[2]);

        /* If all bytes are 0, there is no error */
        if ( correctionCode[0] || correctionCode[1] || correctionCode[2]) {
            /* If there is a single bit error, there are 11 bits set to 1 */
            if (ECC_CountBitsInCode(correctionCode) == 11) {
                /* Get byte and bit indexes */
                byte = (correctionCode[0] & 0xf8) >> 3;
                byte |= (correctionCode[1] & 0x07) << 5;
                bit = correctionCode[0] & 0x07;

                /* Correct bit */
                TRACE_INFO("Correcting byte #%d at bit %d\n\r", (int)(position + byte), (int)bit);
                data[byte] ^= (1 << bit);
                error = Hsiao_ERROR_SINGLEBIT;
            }
            /* Check if ECC has been corrupted */
            else if (ECC_CountBitsInCode(correctionCode) == 1) {
                return Hsiao_ERROR_ECC;
            }
            else {
                /* Otherwise, this is a multi-bit error */
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

/**
 * \brief Verifies 3-bytes hsiao codes for a data block whose size is multiple of
 * 512 bytes. Each 512-bytes block is verified between the given HSIAO code
 * generated by hardware and original HSIAO codes store has been previously stored.
 * Returns 0 if the data is correct, Hsiao_ERROR_SINGLEBIT if one or more
 * block(s) have had a single bit corrected, or either Hsiao_ERROR_ECC
 * or Hsiao_ERROR_MULTIPLEBITS.
 *
 * \param data  Data buffer to verify.
 * \param size  Size of the data in words.
 * \param originalCode  Original codes.
 * \param verifyCode  codes to be verified.
 */
static uint8_t SMC_ECC_Verify512x8bitHsiao(
    uint8_t *data,
    uint32_t size,
    const uint8_t *originalCode,
    const uint8_t *verifyCode)
{
    uint8_t correctionCode[3];
    uint32_t position = 0;
    uint16_t byte;
    uint8_t bit;
    uint8_t error = 0;

    TRACE_DEBUG("SMC_ECC_Verify512x8bitHsiao()\n\r");
    while (position < size) {
        /* Xor both codes together */
        correctionCode[0] = verifyCode[0] ^ originalCode[0];
        correctionCode[1] = verifyCode[1] ^ originalCode[1];
        correctionCode[2] = verifyCode[2] ^ originalCode[2];
        TRACE_DEBUG("Correction code = %02X %02X %02X\n\r",
            correctionCode[0], correctionCode[1], correctionCode[2]);

        /* If all bytes are 0, there is no error */
        if ( correctionCode[0] || correctionCode[1] || correctionCode[2]) {
            /* If there is a single bit error, there are 11 bits set to 1 */
            if (ECC_CountBitsInCode(correctionCode) == 12) {
                /* Get byte and bit indexes */
                byte = (correctionCode[0] & 0xf8) >> 3;
                byte |= (correctionCode[1] & 0x0f) << 5;
                bit = correctionCode[0] & 0x07;

                /* Correct bit */
                TRACE_INFO("Correcting byte #%d at bit %d\n\r", (int)(position + byte), (int)bit);
                data[byte] ^= (1 << bit);
                error = Hsiao_ERROR_SINGLEBIT;
            }
            /* Check if ECC has been corrupted */
            else if (ECC_CountBitsInCode(correctionCode) == 1) {
                return Hsiao_ERROR_ECC;
            }
            else {
                /* Otherwise, this is a multi-bit error */
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

/**
 * \breif Verifies 4-bytes hsiao codes for a data block whose size is a page Size
 * word. Page words block is verified between the given HSIAO code
 * generated by hardware and original HSIAO codes store has been previously stored.
 * Returns 0 if the data is correct, Hsiao_ERROR_SINGLEBIT if one or more
 * block(s) have had a single bit corrected, or either Hsiao_ERROR_ECC
 * or Hsiao_ERROR_MULTIPLEBITS.
 *
 * \param data  Data buffer to verify.
 * \param originalCode  Original codes.
 * \param verifyCode  codes to be verified.
 */
static uint8_t SMC_ECC_VerifyPageOf16bitHsiao(
    uint16_t *data,
    const uint8_t *originalCode,
    const uint8_t *verifyCode)
{
    uint8_t correctionCode[4];
    uint8_t bitCount;

    /* Xor both codes together */
    correctionCode[0] = verifyCode[0] ^ originalCode[0];
    correctionCode[1] = verifyCode[1] ^ originalCode[1];
    correctionCode[2] = verifyCode[2] ^ originalCode[2];
    correctionCode[3] = verifyCode[3] ^ originalCode[3];
    TRACE_DEBUG("Correction code = %02X %02X %02X %02X\n\r",
                correctionCode[0], correctionCode[1], correctionCode[2], correctionCode[3]);
    /* If all bytes are 0, there is no error */
    if ((correctionCode[0] == 0)
        && (correctionCode[1] == 0)
        && (correctionCode[2] == 0)
        && (correctionCode[3] == 0)) {

        return 0;
    }
     /* If there is a single bit error, there are 11 bits set to 1 */
    bitCount = ECC_CountBitsInByte(correctionCode[0]) +
               ECC_CountBitsInByte(correctionCode[1]) +
               ECC_CountBitsInByte(correctionCode[2]) +
               ECC_CountBitsInByte(correctionCode[3]);
    TRACE_DEBUG("bitCount = %d \n\r",bitCount);
    if (bitCount == 12) {
        /* Get byte and bit indexes */
        uint8_t word = (correctionCode[0] & 0xf0) >> 4;
        word |= (correctionCode[1] & 0xff) << 4;
        uint8_t bit = correctionCode[0] & 0x0f;

        /* Correct bit */
        TRACE_INFO("Correcting word #%d at bit %d\n\r", word, bit);
        data[word] ^= (1 << bit);

        return Hsiao_ERROR_SINGLEBIT;
    }

    /* Check if ECC has been corrupted */
    if (bitCount == 1) {
        return Hsiao_ERROR_ECC;
    }
    /* Otherwise, this is a multi-bit error */
    else {
        return Hsiao_ERROR_MULTIPLEBITS;
    }
}

/**
 * \brief Verifies 3-bytes hsiao codes for a data block whose size is multiple of
 * 256 word.Each 256-words block is verified between the given HSIAO code
 * generated by hardware and original HSIAO codes store has been previously stored.
 * Returns 0 if the data is correct, Hsiao_ERROR_SINGLEBIT if one or more
 * block(s) have had a single bit corrected, or either Hsiao_ERROR_ECC
 * or Hsiao_ERROR_MULTIPLEBITS.
 *
 * \param data  Data buffer to verify.
 * \param size  Size of the data in words.
 * \param originalCode  Original codes.
 * \param verifyCode  codes to be verified.
 */
static uint8_t SMC_ECC_Verify256x16bitHsiao(
    uint16_t *data,
    uint32_t size,
    const uint8_t *originalCode,
    const uint8_t *verifyCode
    )
{
    uint8_t correctionCode[3];
    uint32_t position = 0;
    uint8_t word;
    uint8_t bit;
    uint8_t error = 0;

    TRACE_DEBUG("SMC_ECC_Verify256x16bitHsiao()\n\r");
    while (position < size) {
        /* Xor both codes together */
        correctionCode[0] = verifyCode[0] ^ originalCode[0];
        correctionCode[1] = verifyCode[1] ^ originalCode[1];
        correctionCode[2] = verifyCode[2] ^ originalCode[2];
        TRACE_DEBUG("Correction code = %02X %02X %02X\n\r",
            correctionCode[0], correctionCode[1], correctionCode[2]);

        /* If all bytes are 0, there is no error */
        if ( correctionCode[0] || correctionCode[1] || correctionCode[2]) {
            /* If there is a single bit error, there are 11 bits set to 1 */
            if (ECC_CountBitsInCode(correctionCode) == 12) {
                /* Get word and bit indexes */
                word = (correctionCode[0] & 0xf0) >> 4;
                word |= (correctionCode[1] & 0x0f) << 4;
                bit = correctionCode[0] & 0x0f;

                /* Correct bit */
                TRACE_INFO("Correcting word #%d at bit %d\n\r", (int)(position + word), (int)bit);
                data[word] ^= (1 << bit);
                error = Hsiao_ERROR_SINGLEBIT;
            }
            /* Check if ECC has been corrupted */
            else if (ECC_CountBitsInCode(correctionCode) == 1) {
                return Hsiao_ERROR_ECC;
            }
            else {
                /* Otherwise, this is a multi-bit error */
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

/**
 * \brief Verifies hsiao codes for a data block. The block is verified between the given
 * HSIAO code generated by hardware and original HSIAO codes store has been
 * previously stored.
 *
 * \param data  Data buffer to verify.
 * \param size  Size of the data in words.
 * \param originalCode  Original codes.
 * \param verifyCode  codes to be verified.
 * \param dataPath 8bit/16bit data path.
 *
 * \return Returns 0 if the data is correct, Hsiao_ERROR_SINGLEBIT if one or more
 * block(s) have had a single bit corrected, or either Hsiao_ERROR_ECC
 * or Hsiao_ERROR_MULTIPLEBITS.
 */
uint8_t SMC_ECC_VerifyHsiao(
    uint8_t *data,
    uint32_t size,
    const uint8_t *originalCode,
    const uint8_t *verifyCode,
    uint8_t dataPath)
{
    uint8_t correctionType;
    uint8_t error = 0;

    correctionType = SMC_ECC_GetCorrectoinType(SMC);
    /* For 16-bit data path */
    if (dataPath == 16) {
        switch (correctionType){
            case SMC_ECC_MD_TYPCORREC_CPAGE:
                error = SMC_ECC_VerifyPageOf16bitHsiao((uint16_t*)data, originalCode, verifyCode);
                break;
            case SMC_ECC_MD_TYPCORREC_C256B:
                error= SMC_ECC_Verify256x16bitHsiao((uint16_t*)data, size / 2, originalCode, verifyCode);
                break;
            case SMC_ECC_MD_TYPCORREC_C512B :
                TRACE_WARNING("16-bit 512 per page correction not yet implement! \n\r");
                break;
        }
    }
    /* For 8-bit data path */
    else {
        switch (correctionType){
            case SMC_ECC_MD_TYPCORREC_CPAGE:
                error = SMC_ECC_VerifyPageOf8bitHsiao(data, originalCode, verifyCode);
                break;
            case SMC_ECC_MD_TYPCORREC_C256B:
                 error = SMC_ECC_Verify256x8bitHsiao(data, size, originalCode, verifyCode);
                 break;
            case SMC_ECC_MD_TYPCORREC_C512B:
                error = SMC_ECC_Verify512x8bitHsiao(data, size, originalCode, verifyCode);
                break;
        }
    }
    return error;
}

/**
 * \brief Get 32-bit ECC code for 16-bit data path NAND flash.
 * 32-bit ECC is generated in order to perform one bit correction
 * for a page in page 512/1024/2048/4096 for 16-bit words
 *
 * \param size  Data size in bytes.
 * \param code  Codes buffer.
 */
static void SMC_ECC_Get24bitPerPageEcc(uint32_t pageDataSize, uint8_t *code)
{
    uint32_t eccParity;
    uint32_t eccNparity;
    uint32_t ecc[16];

    pageDataSize = pageDataSize; /* stop warning */

    /* Get Parity value. */
    SMC_ECC_GetValue(SMC, ecc);

    /*  ----   P16384'P8192'P4096'P2048'  P1024'P512'P256' ---  4th. Ecc Byte to store */
    /*  P128'  P64'   P32'  P16'  P8'     P4'   P2'  P1'   ---  3rd. Ecc Byte to store */
    /*  ----   P16384 P8192 P4096 P2048   P1024 P512 P256  ---  2nd. Ecc Byte to store */
    /*  P128   P64    P32   P16   P8      P4    P2   P1    ---  1st. Ecc Byte to store */

    /* Invert codes (linux compatibility) */
    eccParity = ~(ecc[0]);
    eccNparity = ~(ecc[1]);
    TRACE_DEBUG("ecc Parity is 0x%08x, ecc Nparity is 0x%08x \n\r", (unsigned int)eccParity, (unsigned int)eccNparity);
    code[0] = eccParity & 0xff;
    code[1] = (eccParity >> 8 )& 0xff;
    code[2] = eccNparity & 0xff;
    code[3] = (eccNparity >> 8 )& 0xff;
}

/**
 * \brief Get 24-bit ECC code for 8-bit data path NAND flash.
 * 24-bit ECC is generated in order to perform one bit correction
 * for 256 byte in page 512/1024/2048/4096 for 8-bit words
 *
 * \param size  Data size in bytes.
 * \param code  Codes buffer.
 */
static void SMC_ECC_Get24bitPer256Ecc(uint32_t pageDataSize, uint8_t *code)
{
    uint8_t i;
    uint8_t numEcc;
    uint32_t eccParity;
    uint32_t ecc[16];

    SMC_ECC_GetValue(SMC, ecc);
    numEcc = pageDataSize / 256;

    /*  P2048' P1024' P512' P256' P128'   P64'  P32' P16'  ---  3rd. Ecc Byte to store */
    /*  P8'    P4'    P2'   P1'   P2048   P1024 P512 P256  ---  2nd. Ecc Byte to store */
    /*  P128   P64    P32   P16   P8      P4    P2   P1    ---  1st. Ecc Byte to store */
    for (i = 0; i < numEcc; i++) {
        /* Get Parity and NParity value. */
        eccParity = ecc[i];
        /* Invert codes (linux compatibility) */
        eccParity = ~eccParity;
        TRACE_DEBUG("ecc Parity%d is 0x%08x \n\r", (int)i, (unsigned int)eccParity);
        code[i * 3] = eccParity & 0xff;
        code[i * 3 + 1] = (eccParity >> 8) & 0xff;
        code[i * 3 + 2] = (eccParity >> 16) & 0xff;
    }
}

/**
 * \brief Get 24-bit ECC code for 8-bit data path NAND flash.
 * 24-bit ECC is generated in order to perform one bit correction
 * for 512 byte in page 512/1024/2048/4096 for 8-bit words
 *
 * \param size  Data size in bytes.
 * \param code  Codes buffer.
 */
static void SMC_ECC_Get24bitPer512Ecc(uint32_t pageDataSize, uint8_t *code)
{
    uint8_t i;
    uint8_t numEcc;
    uint32_t eccParity;
    uint32_t ecc[16];

    SMC_ECC_GetValue(SMC, ecc);
    numEcc = pageDataSize / 512;

    /*  P2048' P1024' P512' P256' P128'   P64'  P32' P16'  ---  3rd. Ecc Byte to store */
    /*  P8'    P4'    P2'   P1'   P2048   P1024 P512 P256  ---  2nd. Ecc Byte to store */
    /*  P128   P64    P32   P16   P8      P4    P2   P1    ---  1st. Ecc Byte to store */
    for (i = 0; i < numEcc; i++) {
        /* Get Parity and NParity value. */
        eccParity = ecc[i];
        /* Invert codes (linux compatibility) */
        eccParity = ~eccParity;
        TRACE_DEBUG("ecc Parity%d is 0x%08x \n\r", (int)i, (unsigned int)eccParity);
        code[i * 3] = eccParity & 0xff;
        code[i * 3 + 1] = (eccParity >> 8) & 0xff;
        code[i * 3 + 2] = (eccParity >> 16) & 0xff;
    }
}

/**
 * \breif Get 32-bit ECC code for 16-bit data path NAND flash.
 * 32-bit ECC is generated in order to perform one bit correction
 * for 256 word in page 512/1024/2048/4096 for 16-bit words
 *
 * \param size  Data size in bytes.
 * \param code  Codes buffer.
 */
static void SMC_ECC_Get32bitPer256Ecc(uint32_t pageDataSize, uint8_t *code)
{
    uint8_t i;
    uint8_t numEcc;
    uint32_t eccParity;
    uint32_t eccNparity;
    uint32_t ecc[16];

    SMC_ECC_GetValue(SMC, ecc);
    numEcc = pageDataSize / 256;

    /*  P2048' P1024' P512' P256' P128'   P64'  P32' P16'  ---  3rd. Ecc Byte to store */
    /*  P8'    P4'    P2'   P1'   P2048   P1024 P512 P256  ---  2nd. Ecc Byte to store */
    /*  P128   P64    P32   P16   P8      P4    P2   P1    ---  1st. Ecc Byte to store */
    for (i = 0; i < numEcc; i+= 2) {
        /* Get Parity value. */
        eccParity = ecc[i];
        /* Invert codes (linux compatibility) */
        eccParity = ~eccParity;
        /* Get NParity value. */
        eccNparity = ecc[i + 1];
        eccNparity = ~eccNparity;
        TRACE_DEBUG("ecc Parity%d is 0x%08x, ecc Nparity%d is 0x%08x \n\r", (int)i, (unsigned int)eccParity, (int)i, (unsigned int)eccNparity);
        code[i * 3] = eccParity & 0xff;
        code[i * 3 + 1] = ((eccParity >> 8) & 0x0f ) | ((eccNparity & 0x0f) << 4);
        code[i * 3 + 2] = (eccNparity >> 4) & 0xff;

        code[(i + 1) * 3] = (eccParity >> 16) & 0xff;
        code[(i + 1) * 3 + 1] = ((eccParity >> 24) & 0x0f ) | (((eccNparity >> 16)& 0x0f) << 4);
        code[(i + 1) * 3 + 2] =  (eccNparity >> 20) & 0xff;

    }
}

/**
 * \breif Get 32-bit ECC code for 16-bit data path NAND flash.
 * 32-bit ECC is generated in order to perform one bit correction
 * for a page in page 512/1024/2048/4096 for 16-bit words
 *
 * \param size  Data size in bytes.
 * \param code  Codes buffer.
 */
static void SMC_ECC_Get32bitPerPageEcc(uint32_t pageDataSize, uint8_t *code)
{
    uint32_t eccParity;
    uint32_t eccNparity;
    uint32_t ecc[16];

    pageDataSize = pageDataSize; /* stop warning */

    /* Get Parity value. */
    SMC_ECC_GetValue(SMC, ecc);

    /*  ----   P16384'P8192'P4096'P2048'  P1024'P512'P256' ---  4th. Ecc Byte to store */
    /*  P128'  P64'   P32'  P16'  P8'     P4'   P2'  P1'   ---  3rd. Ecc Byte to store */
    /*  ----   P16384 P8192 P4096 P2048   P1024 P512 P256  ---  2nd. Ecc Byte to store */
    /*  P128   P64    P32   P16   P8      P4    P2   P1    ---  1st. Ecc Byte to store */

    /* Invert codes (linux compatibility) */
    eccParity = ~(ecc[0]);
    eccNparity = ~(ecc[1]);
    TRACE_DEBUG("ecc Parity is 0x%08x, ecc Nparity is 0x%08x \n\r", (unsigned int)eccParity, (unsigned int)eccNparity);
    code[0] = eccParity & 0xff;
    code[1] = (eccParity >> 8 )& 0xff;
    code[2] = eccNparity & 0xff;
    code[3] = (eccNparity >> 8 )& 0xff;
}

/**
 * Get ECC code for 8bit/16-bit data path NAND flash by giving data path.
 * 24-bit or 32-bit ECC is generated in order to perform one bit correction
 * for a page in page 512/1024/2048/4096.
 *
 * \param size  Data size in bytes.
 * \param code  Codes buffer.
 * \param dataPath 8bit/16bit data path.
 */
void SMC_ECC_GetEccParity(uint32_t pageDataSize, uint8_t *code, uint8_t dataPath)
{
    uint8_t correctionType;

    correctionType = SMC_ECC_GetCorrectoinType(SMC);
    /* For 16-bit data path */
    if (dataPath == 16) {
        switch (correctionType){
            case SMC_ECC_MD_TYPCORREC_CPAGE:
                SMC_ECC_Get32bitPerPageEcc(pageDataSize, code);
                break;
            case SMC_ECC_MD_TYPCORREC_C256B:
                SMC_ECC_Get32bitPer256Ecc(pageDataSize, code);
                break;
            case SMC_ECC_MD_TYPCORREC_C512B:
                TRACE_WARNING("16 bit  512 byte correct not yet implement! \n\r");
                break;
        }
    }
    /* For 8-bit data path */
    else {
        switch (correctionType){
            case SMC_ECC_MD_TYPCORREC_CPAGE:
                SMC_ECC_Get24bitPerPageEcc(pageDataSize, code);
                break;
            case SMC_ECC_MD_TYPCORREC_C256B:
                 SMC_ECC_Get24bitPer256Ecc(pageDataSize, code);
                 break;
            case SMC_ECC_MD_TYPCORREC_C512B:
                SMC_ECC_Get24bitPer512Ecc(pageDataSize, code);
                break;
        }
    }
}

