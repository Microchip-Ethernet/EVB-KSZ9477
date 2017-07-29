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

/*------------------------------------------------------------------------------ */
/*         Headers                                                               */
/*------------------------------------------------------------------------------ */

#include <board.h>
#include <libnandflash.h>
#include <libpmecc.h>

#include <assert.h>
#include <string.h>

/*------------------------------------------------------------------------------ */
/*         Internal definitions                                                  */
/*------------------------------------------------------------------------------ */

 /** Casts */
#define MODEL(ecc)  ((struct NandFlashModel *) ecc)
#define RAW(ecc)    ((struct RawNandFlash *) ecc)

/*------------------------------------------------------------------------------ */
/*         Local functions */
/*------------------------------------------------------------------------------ */
static uint8_t EccNandFlash_ReadPageWithHwEcc(
    const struct EccNandFlash *ecc,
    uint16_t block,
    uint16_t page,
    void *data,
    void *spare)
{
   /* To be implement here */
   RawNandFlash_ReadPage(RAW(ecc), block, page, data, 0);
   return 0; 
}

/**
 * \brief Reads the data and/or spare of a page of a nandflash chip, and verify that
 * the data is valid using the ECC information contained in the spare. If one
 * buffer pointer is 0, the corresponding area is not saved.
 * \param ecc  Pointer to an EccNandFlash instance.
 * \param block  Number of block to read from.
 * \param page  Number of page to read inside given block.
 * \param data  Data area buffer.
 * \param spare  Spare area buffer.
 * \return 0 if the data has been read and is valid; otherwise returns either
 * NandCommon_ERROR_CORRUPTEDDATA or ...
 */
static uint8_t EccNandFlash_ReadPageWithSoftwareEcc(
    const struct EccNandFlash *ecc,
    uint16_t block,
    uint16_t page,
    void *data,
    void *spare)
{
    uint8_t tmpSpare[NandCommon_MAXPAGESPARESIZE];
    uint8_t error;

    uint8_t tmpData[NandCommon_MAXPAGEDATASIZE];
    uint8_t hamming[NandCommon_MAXSPAREECCBYTES];

    uint16_t pageDataSize = NandFlashModel_GetPageDataSize(MODEL(ecc));
    uint8_t pageSpareSize = NandFlashModel_GetPageSpareSize(MODEL(ecc));

    /* Start by reading the spare data */
    error = RawNandFlash_ReadPage(RAW(ecc), block, page, 0, tmpSpare);
    if (error) {

        TRACE_ERROR("EccNandFlash_ReadPage: Failed to read page\n\r");
        return error;
    }

    /* Then reading the data */
    error = RawNandFlash_ReadPage(RAW(ecc), block, page, tmpData, 0);
    if (error) {

        TRACE_ERROR("EccNandFlash_ReadPage: Failed to read page\n\r");
        return error;
    }

    /* Retrieve ECC information from page and verify the data */
    NandSpareScheme_ReadEcc(NandFlashModel_GetScheme(MODEL(ecc)), tmpSpare, hamming);
    error = Hamming_Verify256x(tmpData, pageDataSize, hamming);
    if (error && (error != Hamming_ERROR_SINGLEBIT)) {

        TRACE_ERROR("EccNandFlash_ReadPage: at B%d.P%d Unrecoverable data\n\r",
                    block, page);
        return NandCommon_ERROR_CORRUPTEDDATA;
    }
    /* Copy data and/or spare into final buffers */
    if (data) {

        memcpy(data, tmpData, pageDataSize);
    }
    if (spare) {

        memcpy(spare, tmpSpare, pageSpareSize);
    }
    return 0;
}

/**
 * \brief Reads the data page of a nandflash chip, and verify that
 * the data is valid by PMECC module. If one
 * \param ecc  Pointer to an EccNandFlash instance.
 * \param block  Number of block to read from.
 * \param page  Number of page to read inside given block.
 * \param data  Data area buffer.
 * \return 0 if the data has been read and is valid; otherwise returns either
 * NandCommon_ERROR_CORRUPTEDDATA or ...
 */
 
/* The ROM code embeds the software used in the process of ECC detection/correction: 
function PMECC_CorrectionAlgo(). The user does not need to embed it in other software. */
#if defined (USE_PMECC_EMBEDDED_ALGO)
uint32_t (*PMECC_CorrectionAlgo)(Pmecc *, Pmerrloc *, PmeccDescriptor *, uint32_t, uint32_t);
#endif

static uint8_t EccNandFlash_ReadPageWithPmecc(
    const struct EccNandFlash *ecc,
    uint16_t block,
    uint16_t page,
    void *data )
{
    volatile uint32_t pmeccStatus;
    uint8_t error;
    uint16_t i;
    uint8_t tmpSpare[NandCommon_MAXPAGESPARESIZE];
    uint16_t pageSpareSize = NandFlashModel_GetPageSpareSize(MODEL(ecc));
//    uint32_t curEccStatus;
    PmeccDescriptor *pPmeccDescriptor;
    
    if ( !data ) return NandCommon_ERROR_ECC_NOT_COMPATIBLE;
    pPmeccDescriptor = PMECC_GetCurrentPmeccDescriptor();
    /* Start by reading the spare data */
    error = RawNandFlash_ReadPage(RAW(ecc), block, page, data, 0);
    if (error) {
        TRACE_ERROR("EccNandFlash_ReadPage: Failed to read page\n\r");
        return error;
    }
    pmeccStatus = SMC->SMC_PMECCISR;
    if(pmeccStatus) {
        //curEccStatus = pmeccStatus;
        /* Check if the spare area was erased */
        RawNandFlash_ReadPage(RAW(ecc), block, page, 0, tmpSpare);
        for ( i = 0 ; i < pageSpareSize; i++) {
            if(tmpSpare[i] != 0xff) {
                break;
            }
        }
        if (i == pageSpareSize) {
            pmeccStatus = 0;
        }
    }
    /* bit correction will be done directly in destination buffer. */
#if defined (USE_PMECC_EMBEDDED_ALGO)
    PMECC_CorrectionAlgo = (uint32_t (*)(Pmecc *, Pmerrloc *, PmeccDescriptor *, uint32_t, uint32_t)) 
                           *((uint32_t *) PMECC_CORRECTIONALGO_ROM_ADDRESS);
    
    if ( PMECC_CorrectionAlgo( PMECC, PMERRLOC, pPmeccDescriptor, pmeccStatus, (uint32_t) data) )
#else
    if ( PMECC_CorrectionAlgo( pPmeccDescriptor, pmeccStatus, (uint32_t) data) )
#endif
    {
         SMC->SMC_PMECCFG &= (~SMC_PMECCFG_AUTO);
         SMC->SMC_PMECCTRL = SMC_PMECCTRL_DISABLE;
         TRACE_ERROR("EccNandFlash_ReadPage: at B%d.P%d Unrecoverable data\n\r", block, page);
         return NandCommon_ERROR_CORRUPTEDDATA;
    }
    SMC->SMC_PMECCFG &= (~SMC_PMECCFG_AUTO);
    SMC->SMC_PMECCTRL = SMC_PMECCTRL_DISABLE;
    return 0;
}

static uint8_t EccNandFlash_WritePageWithHwEcc(
    const struct EccNandFlash *ecc,
    uint16_t block,
    uint16_t page,
    void *data,
    void *spare)
{
    uint8_t error;
    SMC->SMC_PMECCTRL = SMC_PMECCTRL_DISABLE;
    /* Perform write operation */
    error = RawNandFlash_WritePage(RAW(ecc), block, page, data, 0);
    if (error) {

        TRACE_ERROR("EccNandFlash_WritePage: Failed to write page\n\r");
        return error;
    }
    return 0;
}

/**
 * \brief Writes the data and/or spare area of a nandflash page, after calculating an
 * ECC for the data area and storing it in the spare. If no data buffer is
 * provided, the ECC is read from the existing page spare. If no spare buffer
 * is provided, the spare area is still written with the ECC information
 * calculated on the data buffer.
 * \param ecc Pointer to an EccNandFlash instance.
 * \param block  Number of the block to write in.
 * \param page  Number of the page to write inside the given block.
 * \param data  Data area buffer, can be 0.
 * \param spare  Spare area buffer, can be 0.
 * \return 0 if successful; otherwise returns an error code.
 */
static uint8_t EccNandFlash_WritePageWithSoftwareEcc(
    const struct EccNandFlash *ecc,
    uint16_t block,
    uint16_t page,
    void *data,
    void *spare)
{
    uint8_t error;
    uint8_t tmpSpare[NandCommon_MAXPAGESPARESIZE];
    uint8_t hamming[NandCommon_MAXSPAREECCBYTES];
    uint16_t pageDataSize = NandFlashModel_GetPageDataSize(MODEL(ecc));
    uint16_t pageSpareSize = NandFlashModel_GetPageSpareSize(MODEL(ecc));

    /* Compute ECC on the new data, if provided */
    /* If not provided, hamming code set to 0xFFFF.. to keep existing bytes */
    memset(hamming, 0xFF, NandCommon_MAXSPAREECCBYTES);
    if ( data ) {

        /* Compute hamming code on data */
        Hamming_Compute256x(data, pageDataSize, hamming);
    }

    /* Store code in spare buffer (if no buffer provided, use a temp. one) */
    if ( !spare ) {
        spare = tmpSpare;
        memset(spare, 0xFF, pageSpareSize);
    }
    NandSpareScheme_WriteEcc(NandFlashModel_GetScheme(MODEL(ecc)), spare, hamming);

    /* Perform write operation */
    error = RawNandFlash_WritePage(RAW(ecc), block, page, data, spare);
    if ( error ) {
        TRACE_ERROR("EccNandFlash_WritePage: Failed to write page\n\r");
        return error;
    }
    return 0;
}

/**
 * \brief Writes the data area of a nandflash page, The PMECC module generates 
 * redundancy at encoding time. When a NAND write page operation is performed.
 * The redundancy is appended to the page and written in the spare area.
 * \param ecc Pointer to an EccNandFlash instance.
 * \param block  Number of the block to write in.
 * \param page  Number of the page to write inside the given block.
 * \param data  Data area buffer, can be 0.
 * \return 0 if successful; otherwise returns an error code.
 */
static uint8_t EccNandFlash_WritePageWithPmecc(
    const struct EccNandFlash *ecc,
    uint16_t block,
    uint16_t page,
    void *data )
{
    uint8_t error;
    /* Perform write operation */
    error = RawNandFlash_WritePage(RAW(ecc), block, page, data, 0);
    SMC->SMC_PMECCTRL = SMC_PMECCTRL_DISABLE;
    if (error) {

        TRACE_ERROR("EccNandFlash_WritePage: Failed to write page\n\r");
        return error;
    }
    return 0;
}

/*------------------------------------------------------------------------------ */
/*         Exported functions */
/*------------------------------------------------------------------------------ */

/**
 * \brief Initializes an EccNandFlash instance.
 * \param ecc  Pointer to an EccNandFlash instance.
 * \param model  Pointer to the underlying nand chip model. Can be 0.
 * \param commandAddress  Address at which commands are sent.
 * \param addressAddress  Address at which addresses are sent.
 * \param dataAddress  Address at which data is sent.
 * \param pinChipEnable  Pin controlling the CE signal of the NandFlash.
 * \param pinReadyBusy  Pin used to monitor the ready/busy signal of the Nand.
*/
uint8_t EccNandFlash_Initialize(
    struct EccNandFlash *ecc,
    const struct NandFlashModel *model,
    uint32_t commandAddress,
    uint32_t addressAddress,
    uint32_t dataAddress,
    const Pin pinChipEnable,
    const Pin pinReadyBusy)
{
    uint8_t rc;
    rc = RawNandFlash_Initialize(RAW(ecc),
                                 model,
                                 commandAddress,
                                 addressAddress,
                                 dataAddress,
                                 pinChipEnable,
                                 pinReadyBusy);
    return rc;
}

/**
 * \brief Reads the data and/or spare of a page of a nandflash chip, and verify that
 * the data is valid using the ECC information contained in the spare. If one
 * buffer pointer is 0, the corresponding area is not saved.
 * \param ecc  Pointer to an EccNandFlash instance.
 * \param block  Number of block to read from.
 * \param page  Number of page to read inside given block.
 * \param data  Data area buffer.
 * \param spare  Spare area buffer.
 * \return 0 if the data has been read and is valid; otherwise returns either
 * NandCommon_ERROR_CORRUPTEDDATA or ...
 */
uint8_t EccNandFlash_ReadPage(
    const struct EccNandFlash *ecc,
    uint16_t block,
    uint16_t page,
    void *data,
    void *spare)
{
    uint8_t eccStatus;
    eccStatus = getSmcOpEccType();
    assert(data || spare);
    TRACE_DEBUG("EccNandFlash_WritePage(B#%d:P#%d)\n\r", block, page);
    if ((eccStatus == SMC_ECC_NOECC) || (eccStatus == SMC_ECC_INTERNAL)) {
        return RawNandFlash_ReadPage(RAW(ecc), block, page, data, spare);
    }
    if ((eccStatus == SMC_ECC_PMECC) && PMECC_GetCurrentPmeccDescriptor()){
        if (spare) return NandCommon_ERROR_ECC_NOT_COMPATIBLE;
       return EccNandFlash_ReadPageWithPmecc( ecc, block, page, data );
    }
    if (eccStatus == SMC_ECC_SOFTWARE){
        return EccNandFlash_ReadPageWithSoftwareEcc( ecc, block, page, data, spare );
    }
    if (eccStatus == SMC_ECC_HSIAO){
        return EccNandFlash_ReadPageWithHwEcc( ecc, block, page, data, spare);
    }
    return NandCommon_ERROR_ECC_NOT_COMPATIBLE;
}

/**
 * \brief Writes the data and/or spare area of a nandflash page, after calculating an
 * ECC for the data area and storing it in the spare. If no data buffer is
 * provided, the ECC is read from the existing page spare. If no spare buffer
 * is provided, the spare area is still written with the ECC information
 * calculated on the data buffer.
 * \param ecc Pointer to an EccNandFlash instance.
 * \param block  Number of the block to write in.
 * \param page  Number of the page to write inside the given block.
 * \param data  Data area buffer, can be 0.
 * \param spare  Spare area buffer, can be 0.
 * \return 0 if successful; otherwise returns an error code.
 */
uint8_t EccNandFlash_WritePage(
    const struct EccNandFlash *ecc,
    uint16_t block,
    uint16_t page,
    void *data,
    void *spare)
{
    uint8_t eccStatus;
    eccStatus = getSmcOpEccType();
    assert(data || spare);
    TRACE_DEBUG("EccNandFlash_WritePage(B#%d:P#%d)\n\r", block, page);
    if ((eccStatus == SMC_ECC_NOECC) || (eccStatus == SMC_ECC_INTERNAL)) {
        return RawNandFlash_WritePage(RAW(ecc), block, page, data, spare);
    }
    if ((eccStatus == SMC_ECC_PMECC) && PMECC_GetCurrentPmeccDescriptor()){
        if (spare) return NandCommon_ERROR_ECC_NOT_COMPATIBLE;
        return EccNandFlash_WritePageWithPmecc( ecc, block, page, data);
    }
    if (eccStatus == SMC_ECC_SOFTWARE){
        return EccNandFlash_WritePageWithSoftwareEcc( ecc, block, page, data, spare);
    }
    if (eccStatus == SMC_ECC_HSIAO){
        return EccNandFlash_WritePageWithHwEcc( ecc, block, page, data, spare);
    }
    return NandCommon_ERROR_ECC_NOT_COMPATIBLE;
}
