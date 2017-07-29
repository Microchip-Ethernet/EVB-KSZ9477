/* ----------------------------------------------------------------------------
 *         SAM Software Package License 
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

/** \file */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include <board.h>
#include <libnandflash.h>

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/
#define MAX_READ_STATUS_COUNT 100000

/** Not all 256 bytes are useful */
#define ONFI_PARAM_TABLE_SIZE 116

/** Flag to indicate ECC status */
uint8_t currentEcc = ECC_NO;
uint8_t isDropJss = 0;
uint16_t jffsTrimPage;

#define WRITE_NAND(d, adr) do{ *(volatile uint8_t *)((unsigned long)adr) = (uint8_t)d; } while(0)


/*------------------------------------------------------------------------------ */
/*         Variables                                                             */
/*------------------------------------------------------------------------------ */
/** Current initialized OnfiPageParam instance*/
static OnfiPageParam *pCurrentOnfiPageParam = 0;

/*----------------------------------------------------------------------------
 *        Internal functions
 *----------------------------------------------------------------------------*/
/**
 * \brief This function Reads the status register of the NAND device by 
 * issuing a 0x70 command.
 * \return  NAND_IO_RC_PASS     =0 : The function completes operation successfully.
            NAND_IO_RC_FAIL     =1 : The function does not complete operation successfully.
            NAND_IO_RC_TIMEOUT  =2 : The function times out before operation completes.
*/
static uint32_t _NandReadStatus(void)
{
    uint32_t nReadStatusCount;
    uint8_t ucStatus;

    /* Issue command */
    WRITE_NAND_COMMAND(NAND_CMD_STATUS, EBI_NF_ADDR);
    nReadStatusCount = 0;

    while (nReadStatusCount < MAX_READ_STATUS_COUNT) {
        /* Read status byte */
        ucStatus = READ_NAND(EBI_NF_ADDR);
        /* Check status */
        /* If status bit 6 = 1 device is ready */
        if ((ucStatus & STATUS_BIT_6) == STATUS_BIT_6) {
            if ((ucStatus & STATUS_BIT_0) == 0)  /* If status bit 0 = 0 the last operation was succesful */
                return NAND_IO_RC_PASS;
            else
                return NAND_IO_RC_FAIL;
        }
        nReadStatusCount++;
    }
    return NAND_IO_RC_TIMEOUT;
}

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/
/**
 * \brief This function read an the ONFI signature at address of 20h to detect
 * if the device is ONFI compatiable.
 * \return  0: ONFI not compliant or not supported.
            1: ONFI compliant
*/
uint8_t NandIsOnficompatible (void)
{
    uint8_t onfi_param_table[ONFI_PARAM_TABLE_SIZE];

    // Check if the Nandflash is ONFI compliant

    WRITE_NAND_COMMAND(NAND_CMD_READID, EBI_NF_ADDR);
    WRITE_NAND_ADDRESS(0x20, EBI_NF_ADDR);

    onfi_param_table[0] = READ_NAND(EBI_NF_ADDR);
    onfi_param_table[1] = READ_NAND(EBI_NF_ADDR);
    onfi_param_table[2] = READ_NAND(EBI_NF_ADDR);
    onfi_param_table[3] = READ_NAND(EBI_NF_ADDR);

    if ((onfi_param_table[0] == 'O') &&
        (onfi_param_table[1] == 'N') &&
        (onfi_param_table[2] == 'F') &&
        (onfi_param_table[3] == 'I')) {
        return 1;
    }
    else {
        return 0;
    }
}

/**
 * \brief This function retrieves the data structure that describes the target¡®s 
 * organization, features, timings and other behavioral parameters.
 * \param pOnfiPageParameter Pointer to a PmeccDescriptor instance.
 * \return  0: ONFI not compliant or not supported.
            1: ONFI compliant
*/
uint8_t NandGetOnfiPageParam (OnfiPageParam *pOnfiPageParameter)
{
    uint8_t i;
    uint8_t onfi_param_table[ONFI_PARAM_TABLE_SIZE];

    if (NandIsOnficompatible()) {
        pCurrentOnfiPageParam = pOnfiPageParameter;
        pOnfiPageParameter->onfiCompatiable = 1;
        for (i = 0; i < ONFI_PARAM_TABLE_SIZE; i++) {
            onfi_param_table[i] = 0xFF;
        }
        /* Perform Read Parameter Page command */
        WRITE_NAND_COMMAND(NAND_CMD_READ_PARAM_PAGE, EBI_NF_ADDR);
        WRITE_NAND_ADDRESS(0x0, EBI_NF_ADDR);

        /* Wait NF ready */
        _NandReadStatus();
        /* Re-enable data output mode required after Read Status command */
        WRITE_NAND_COMMAND(NAND_CMD_READ0, EBI_NF_ADDR);

        /* Read the parameter table */
        for (i = 0; i < ONFI_PARAM_TABLE_SIZE; i++) {
            onfi_param_table[i] = READ_NAND(EBI_NF_ADDR);
        }
        for (i = 0; i < ONFI_PARAM_TABLE_SIZE; i++) {
            if ( onfi_param_table[i] != 0xFF ) break;
        }
        if ( i == ONFI_PARAM_TABLE_SIZE) {
            pOnfiPageParameter->onfiCompatiable = 0;
            return 0;
        }
        
        /* JEDEC manufacturer ID */
        pOnfiPageParameter->manufacturerId = *(uint8_t *)(onfi_param_table + 64);
        TRACE_INFO("ONFI manufacturerId %x \n\r",pOnfiPageParameter->manufacturerId);
        /* Bus width */
        pOnfiPageParameter->onfiBusWidth = (*(uint8_t *)(onfi_param_table + 6)) & 0x01;
        /* Get number of data bytes per page (bytes 80-83 in the param table) */
        pOnfiPageParameter->onfiPageSize =  *(uint32_t *)(void*)(onfi_param_table + 80);
        TRACE_INFO("ONFI onfiPageSize %x \n\r", (unsigned int)pOnfiPageParameter->onfiPageSize);
        /* Get number of spare bytes per page (bytes 84-85 in the param table) */
        pOnfiPageParameter->onfiSpareSize =  *(uint16_t *)(void*)(onfi_param_table + 84);
         TRACE_INFO("ONFI onfiSpareSize %x \n\r",(unsigned int)pOnfiPageParameter->onfiSpareSize);
        /* Number of pages per block. */
        pOnfiPageParameter->onfiPagesPerBlock = *(uint32_t *)(void*)(onfi_param_table + 92);
        /* Number of blocks per logical unit (LUN). */
        pOnfiPageParameter->onfiBlocksPerLun = *(uint32_t *)(void*)(onfi_param_table + 96);
        /* Number of logical units. */
        pOnfiPageParameter->onfiLogicalUnits = *(uint8_t *)(onfi_param_table + 100);
        /* Number of bits of ECC correction */
        pOnfiPageParameter->onfiEccCorrectability = *(uint8_t *)(onfi_param_table + 112);
        TRACE_INFO("ONFI onfiEccCorrectability %x \n\r",pOnfiPageParameter->onfiEccCorrectability);
        /* Device model */
        pOnfiPageParameter->onfiDeviceModel= *(uint8_t *)(onfi_param_table + 49);
        return 1;
    }
    return 0;
}

/**
 * \brief This function check if the Nandflash has an embedded ECC controller.
 * \return  0: ONFI not compliant or internal ECC not supported.
            1: Internal ECC enabled.
*/
uint8_t NandEnableInternalEcc (void)
{
    OnfiPageParam *pOnfiPageParameter;
    pOnfiPageParameter = NandGetCurrentOnfiInstance();

    if (pOnfiPageParameter->onfiCompatiable == 1) {
        /* Check if the Nandflash has an embedded ECC controller
           Known memories with this feature :
           - Manufacturer ID = 2Ch (Micron)
           - Number of bits ECC = 04h (4-bit ECC means process 34nm)
           - device size = 1Gb or 2Gb or 4Gb (Number of data bytes per page * Number of pages per block * Number of blocks per unit)  */
        if ( ((pOnfiPageParameter->manufacturerId & NAND_MFR_MICRON) == NAND_MFR_MICRON) &&
              (pOnfiPageParameter->onfiEccCorrectability == 0x4) &&
              ((pOnfiPageParameter->onfiDeviceModel == '1')     //  1G,
               || (pOnfiPageParameter->onfiDeviceModel == '2')     //  2G
               || (pOnfiPageParameter->onfiDeviceModel == '4'))) { //  or 4G bits

            /* then activate the internal ECC controller */
            WRITE_NAND_COMMAND(NAND_CMD_SET_FEATURE, EBI_NF_ADDR);
            WRITE_NAND_ADDRESS(0x90, EBI_NF_ADDR);

            WRITE_NAND(0x08, EBI_NF_ADDR);
            WRITE_NAND(0x00, EBI_NF_ADDR);
            WRITE_NAND(0x00, EBI_NF_ADDR);
            WRITE_NAND(0x00, EBI_NF_ADDR);
            setSmcOpEccType(SMC_ECC_INTERNAL);
            return 1;
        }
    }
    return 0;
}


/**
 * \brief This function check if the Nandflash has an embedded ECC controller, and disable it.
 * \return  0: ONFI not compliant or internal ECC not supported.
            1: Internal ECC disabled.
*/
uint8_t NandDisableInternalEcc (void)
{
            /* then activate the internal ECC controller */
            WRITE_NAND_COMMAND(NAND_CMD_SET_FEATURE, EBI_NF_ADDR);
            WRITE_NAND_ADDRESS(0x90, EBI_NF_ADDR);

            WRITE_NAND(0x00, EBI_NF_ADDR);
            WRITE_NAND(0x00, EBI_NF_ADDR);
            WRITE_NAND(0x00, EBI_NF_ADDR);
            WRITE_NAND(0x00, EBI_NF_ADDR);
    return 0;
}
/**
 * \brief Detect Nand connection on EBI.
 * \return return TRUE if the chip is detected.  FALSE otherwise.
 */

uint8_t NandEbiDetect(void)
{
    uint32_t timer;
    uint8_t rc;
    uint8_t chip_found = 0;
    uint8_t ids[4];
    uint8_t i;
    
    /* Send Reset command */
    WRITE_NAND_COMMAND(NAND_CMD_RESET, EBI_NF_ADDR);
    /* If a Nandflash is connected, it should answer to a read status command */
    for (timer = 0; timer < 60; timer++) {
        rc = _NandReadStatus();
        if (rc == NAND_IO_RC_PASS) {
            WRITE_NAND_COMMAND(NAND_CMD_READID, EBI_NF_ADDR);
            WRITE_NAND_ADDRESS(0, EBI_NF_ADDR);
            ids[0] = READ_NAND(EBI_NF_ADDR);
            ids[1] = READ_NAND(EBI_NF_ADDR);
            ids[2] = READ_NAND(EBI_NF_ADDR);
            ids[3] = READ_NAND(EBI_NF_ADDR);
            for(i = 0; i< NandFlashModelList_SIZE ; i++) {
                if(nandFlashModelList[i].deviceId == ids[1]) {
                    chip_found = 1;
                    break;
                }
            }
            break;
        }
    }
    if (chip_found == 0) {
        if (NandIsOnficompatible()) {
            chip_found = 1;
            /* even if it is not in device list (it is maybe a new device, but it is ONFI campatible */
        }
    }
    return chip_found;
}

/**
 * \brief Set current trimffs status.
 */
void NandSetTrimffs (uint8_t enable)
{
    isDropJss = enable;
}

/**
 * \brief Set current trimffs status.
 */
uint8_t isNandTrimffs (void)
{
    return isDropJss;
}

/**
 * \brief Set current trimffs page.
 * \param page Start trim page.
 */
void NandSetTrimPage (uint16_t page)
{
    jffsTrimPage = page;
}

/**
 * \brief Get current trimffs page.
 * \param page Start trim page.
 */
uint16_t NandGetTrimPage (void)
{
    return jffsTrimPage;
}

/**
 * \brief Get current OnfiPageParam instance
 *
 * \return current OnfiPageParam instance.
 */ 

OnfiPageParam * NandGetCurrentOnfiInstance ( void )
{
    return  pCurrentOnfiPageParam;
}

