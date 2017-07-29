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

/** \addtogroup flashd_module Flash Memory Interface
 * The flash driver manages the programming, erasing, locking and unlocking sequences
 * with dedicated commands.
 *
 * To implement flash programing operation, the user has to follow these few steps :
 * <ul>
 * <li>Configue flash wait states to initializes the flash. </li>
 * <li>Checks whether a region to be programmed is locked. </li>
 * <li>Unlocks the user region to be programmed if the region have locked before.</li>
 * <li>Erases the user page before program (optional).</li>
 * <li>Writes the user page from the page buffer.</li>
 * <li>Locks the region of programmed area if any.</li>
 * </ul>
 *
 * Writing 8-bit and 16-bit data is not allowed and may lead to unpredictable data corruption.
 * A check of this validity and padding for 32-bit alignment should be done in write algorithm.

 * Lock/unlock range associated with the user address range is automatically translated.
 *
 * This security bit can be enabled through the command "Set General Purpose NVM Bit 0".
 *
 * A 128-bit factory programmed unique ID could be read to serve several purposes.
 *
 * The driver accesses the flash memory by calling the lowlevel module provided in \ref efc_module.
 * For more accurate information, please look at the EEFC section of the Datasheet.
 *
 * Related files :\n
 * \ref flashd.c\n
 * \ref flashd.h.\n
 * \ref efc.c\n
 * \ref efc.h.\n
*/
/*@{*/
/*@}*/


/**
 * \file
 *
 * The flash driver provides the unified interface for flash program operations.
 *
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/
#include "chip.h"

#include <string.h>
#include <assert.h>

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

static uint32_t _adwPageBuffer[IFLASH_PAGE_SIZE/sizeof(uint32_t)] ;
static uint8_t* _aucPageBuffer = (uint8_t*)_adwPageBuffer;
static uint32_t _dwUseIAP = 1; /* Use IAP interface by default. */

/*----------------------------------------------------------------------------
 *        Local macros
 *----------------------------------------------------------------------------*/

#define min( a, b ) (((a) < (b)) ? (a) : (b))

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/


/**
 * \brief Computes the lock range associated with the given address range.
 *
 * \param dwStart  Start address of lock range.
 * \param dwEnd  End address of lock range.
 * \param pdwActualStart  Actual start address of lock range.
 * \param pdwActualEnd  Actual end address of lock range.
 */
static void ComputeLockRange( uint32_t dwStart, uint32_t dwEnd, uint32_t *pdwActualStart, uint32_t *pdwActualEnd )
{
    Efc* pStartEfc ;
    Efc* pEndEfc ;
    uint16_t wStartPage ;
    uint16_t wEndPage ;
    uint16_t wNumPagesInRegion ;
    uint16_t wActualStartPage ;
    uint16_t wActualEndPage ;

    /* If "dwEnd" is at the start address of a lock region, */
    /* It actually means the end address of previous lock region  */
    /* So, we do adjustment of "dwEnd" here. */
    if ((dwEnd != IFLASH0_ADDR) && ((dwEnd & (IFLASH_LOCK_REGION_SIZE-1)) == 0))
    {
        dwEnd -= 1;
    }

    /* Convert start and end address in page numbers */
    EFC_TranslateAddress( &pStartEfc, dwStart, &wStartPage, 0 ) ;
    EFC_TranslateAddress( &pEndEfc, dwEnd, &wEndPage, 0 ) ;

    /* Find out the first page of the first region to lock */
    wNumPagesInRegion = IFLASH_LOCK_REGION_SIZE / IFLASH_PAGE_SIZE;
    wActualStartPage = wStartPage - (wStartPage % wNumPagesInRegion) ;
    wActualEndPage = wEndPage ;
    if ( (wEndPage % wNumPagesInRegion) != (wNumPagesInRegion-1) )
    {
        wActualEndPage += wNumPagesInRegion - (wEndPage % wNumPagesInRegion) - 1;
    }

    /* Store actual page numbers */
    EFC_ComputeAddress( pStartEfc, wActualStartPage, 0, pdwActualStart ) ;
    EFC_ComputeAddress( pEndEfc, wActualEndPage, 0, pdwActualEnd ) ;
    TRACE_DEBUG( "Actual lock range is 0x%06X - 0x%06X\n\r",
        (unsigned int)(*pdwActualStart), (unsigned int)(*pdwActualEnd + IFLASH_PAGE_SIZE - 1) ) ;
}


/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Initializes the flash driver.
 *
 * \param dwMCk     Master clock frequency in Hz.
 * \param dwUseIAP  0: use EEFC controller interface, 1: use IAP interface.
 *                  dwUseIAP should be set to 1 when running out of flash.
 */

extern void FLASHD_Initialize( uint32_t dwMCk, uint32_t dwUseIAP )
{
    dwMCk = dwMCk; /* avoid warnings */

    EFC_DisableFrdyIt( EFC0 ) ;
    EFC_DisableFrdyIt( EFC1 ) ;

    _dwUseIAP = dwUseIAP ;
}

/**
 * \brief Erases the entire flash.
 *
 * \param address  Flash start address.
 * \return 0 if successful; otherwise returns an error code.
 */
extern uint32_t FLASHD_Erase( uint32_t dwAddress )
{
    Efc* pEfc ;
    uint16_t wPage ;
    uint16_t wOffset ;
    uint32_t dwError ;

    assert( (dwAddress >=IFLASH0_ADDR) || (dwAddress <= (IFLASH0_ADDR + IFLASH_SIZE)) ) ;

    /* Translate write address */
    EFC_TranslateAddress( &pEfc, dwAddress, &wPage, &wOffset ) ;
    dwError = EFC_PerformCommand( pEfc, EFC_FCMD_EA, 0, _dwUseIAP ) ;

    return dwError ;
}

/**
 * \brief Writes a data buffer in the internal flash.
 *
 * \note This function works in polling mode, and thus only returns when the
 * data has been effectively written.
 * \param address  Write address.
 * \param pBuffer  Data buffer.
 * \param size  Size of data buffer in bytes.
 * \return 0 if successful, otherwise returns an error code.
 */
extern uint32_t FLASHD_Write( uint32_t dwAddress, const void *pvBuffer, uint32_t dwSize )
{
    Efc* pEfc ;
    uint16_t page ;
    uint16_t offset ;
    uint32_t writeSize ;
    uint32_t pageAddress ;
    uint16_t padding ;
    uint32_t dwError ;
    uint32_t sizeTmp ;
    uint32_t *pAlignedDestination ;
    uint32_t *pAlignedSource ;
    uint32_t fwsBak0, fwsBak1;

    /* Set 6 WS for internal Flash writing (refer to errata) */
    fwsBak0 = ((EFC0->EEFC_FMR) & EEFC_FMR_FWS_Msk) >> EEFC_FMR_FWS_Pos;
    fwsBak1 = ((EFC1->EEFC_FMR) & EEFC_FMR_FWS_Msk) >> EEFC_FMR_FWS_Pos;
    EFC_SetWaitState(EFC0, 6);
    EFC_SetWaitState(EFC1, 6);

    uint32_t crossWrite = 0;
    void     *pvBufferRemain = 0;
    uint32_t dwSizeRemain = 0;

    assert( pvBuffer ) ;
    assert( dwAddress >= IFLASH0_ADDR ) ;
    assert( (dwAddress + dwSize) <= (IFLASH0_ADDR + IFLASH_SIZE) ) ;

    /* Check if the write operation will cross over flash0 and flash1 */
    if ( ((dwAddress + dwSize) <= (IFLASH0_ADDR + IFLASH_SIZE/2)) ||
         (dwAddress >= IFLASH1_ADDR) )
    {
        crossWrite = 0;
    }
    else
    {
        /* Save information for write operation on flash1 */
        crossWrite = 1;
        pvBufferRemain = (void *)((uint8_t *)pvBuffer + (IFLASH1_ADDR - dwAddress));
        dwSizeRemain = dwSize - (IFLASH1_ADDR - dwAddress);
        /* Adjust size for write operation on flash0 */
        dwSize = (IFLASH1_ADDR - dwAddress);
    }

fd_write:
    /* Translate write address */
    EFC_TranslateAddress( &pEfc, dwAddress, &page, &offset ) ;

    /* Write all pages */
    while ( dwSize > 0 )
    {
        /* Copy data in temporary buffer to avoid alignment problems */
        writeSize = min((uint32_t)IFLASH_PAGE_SIZE - offset, dwSize ) ;
        EFC_ComputeAddress(pEfc, page, 0, &pageAddress ) ;
        padding = IFLASH_PAGE_SIZE - offset - writeSize ;

        /* Pre-buffer data */
        memcpy( _aucPageBuffer, (void *) pageAddress, offset);

        /* Buffer data */
        memcpy( _aucPageBuffer + offset, pvBuffer, writeSize);

        /* Post-buffer data */
        memcpy( _aucPageBuffer + offset + writeSize, (void *) (pageAddress + offset + writeSize), padding);

        /* Write page
         * Writing 8-bit and 16-bit data is not allowed and may lead to unpredictable data corruption
         */
        pAlignedDestination = (uint32_t*)pageAddress ;
        pAlignedSource = (uint32_t*)_adwPageBuffer ;
        sizeTmp = IFLASH_PAGE_SIZE ;

        while ( sizeTmp >= 4 )
        {
            *pAlignedDestination++ = *pAlignedSource++;
            sizeTmp -= 4;
        }

        /* Send writing command */
        dwError = EFC_PerformCommand( pEfc, EFC_FCMD_EWP, page, _dwUseIAP ) ;
        if ( dwError )
        {
            /* Restore FWS settings */
            EFC_SetWaitState(EFC0, fwsBak0);
            EFC_SetWaitState(EFC1, fwsBak1);
            return dwError ;
        }

        /* Progression */
        dwAddress += IFLASH_PAGE_SIZE ;
        pvBuffer = (void *)((uint32_t) pvBuffer + writeSize) ;
        dwSize -= writeSize ;
        page++;
        offset = 0;
    }

    /* Check if there is a writing operation on flash1 */
    if (crossWrite == 1)
    {
        dwAddress = IFLASH1_ADDR;
        pvBuffer = pvBufferRemain;
        dwSize = dwSizeRemain;
        crossWrite = 0;
        goto fd_write;
    }

    /* Restore FWS settings */
    EFC_SetWaitState(EFC0, fwsBak0);
    EFC_SetWaitState(EFC1, fwsBak1);
    return 0 ;
}
/**
 * \brief Locks all the regions in the given address range. The actual lock range is
 * reported through two output parameters.
 *
 * \param start  Start address of lock range.
 * \param end    End address of lock range.
 * \param pActualStart  Start address of the actual lock range (optional).
 * \param pActualEnd  End address of the actual lock range (optional).
 * \return 0 if successful, otherwise returns an error code.
 */
extern uint32_t FLASHD_Lock( uint32_t start, uint32_t end, uint32_t *pActualStart, uint32_t *pActualEnd )
{
    Efc *pEfc ;
    uint32_t actualStart, actualEnd ;
    uint16_t startPage, endPage ;
    uint32_t dwError ;
    uint16_t numPagesInRegion = IFLASH_LOCK_REGION_SIZE / IFLASH_PAGE_SIZE;

    uint32_t crossLock = 0;
    uint32_t endBak = end;

    /* Check if the lock operation will cross over flash0 and flash1 */
    if ( (start >= IFLASH1_ADDR) || (end <= IFLASH1_ADDR) )
    {
        crossLock = 0;
    }
    else
    {
        /* Save information for lock operation on flash1 */
        crossLock = 1;
        endBak = end;
        /* Adjust end address for lock operation on flash0 */
        end = (IFLASH1_ADDR - 1);
    }

fd_lock:
    /* Compute actual lock range and store it */
    ComputeLockRange( start, end, &actualStart, &actualEnd ) ;
    if ( pActualStart != NULL )
    {
        *pActualStart = actualStart ;
    }
    if ( pActualEnd != NULL )
    {
        *pActualEnd = actualEnd;
    }

    /* Compute page numbers */
    EFC_TranslateAddress( &pEfc, actualStart, &startPage, 0 ) ;
    EFC_TranslateAddress( 0, actualEnd, &endPage, 0 ) ;

    /* Lock all pages */
    while ( startPage < endPage )
    {
        dwError = EFC_PerformCommand( pEfc, EFC_FCMD_SLB, startPage, _dwUseIAP ) ;
        if ( dwError )
        {
            return dwError ;
        }
        startPage += numPagesInRegion;
    }

    /* Check if there is a lock operation on flash1 */
    if (crossLock == 1)
    {
        start = IFLASH1_ADDR;
        end = endBak;
        crossLock = 0;
        goto fd_lock;
    }

    return 0 ;
}

/**
 * \brief Unlocks all the regions in the given address range. The actual unlock range is
 * reported through two output parameters.
 * \param start  Start address of unlock range.
 * \param end  End address of unlock range.
 * \param pActualStart  Start address of the actual unlock range (optional).
 * \param pActualEnd  End address of the actual unlock range (optional).
 * \return 0 if successful, otherwise returns an error code.
 */
extern uint32_t FLASHD_Unlock( uint32_t start, uint32_t end, uint32_t *pActualStart, uint32_t *pActualEnd )
{
    Efc* pEfc ;
    uint32_t actualStart, actualEnd ;
    uint16_t startPage, endPage ;
    uint32_t dwError ;
    uint16_t numPagesInRegion = IFLASH_LOCK_REGION_SIZE / IFLASH_PAGE_SIZE;

    uint32_t crossUnlock = 0;
    uint32_t endBak = end;

    /* Check if the unlock operation will cross over flash0 and flash1 */
    if ( (start >= IFLASH1_ADDR) || (end <= IFLASH1_ADDR) )
    {
        crossUnlock = 0;
    }
    else
    {
        /* Save information for unlock operation on flash1 */
        crossUnlock = 1;
        endBak = end;
        /* Adjust end address for unlock operation on flash0 */
        end = (IFLASH1_ADDR - 1);
    }

fd_unlock:
    /* Compute actual unlock range and store it */
    ComputeLockRange(start, end, &actualStart, &actualEnd);
    if ( pActualStart != NULL )
    {
        *pActualStart = actualStart ;
    }
    if ( pActualEnd != NULL )
    {
        *pActualEnd = actualEnd ;
    }

    /* Compute page numbers */
    EFC_TranslateAddress( &pEfc, actualStart, &startPage, 0 ) ;
    EFC_TranslateAddress( 0, actualEnd, &endPage, 0 ) ;

    /* Unlock all pages */
    while ( startPage < endPage )
    {
        dwError = EFC_PerformCommand( pEfc, EFC_FCMD_CLB, startPage, _dwUseIAP ) ;
        if ( dwError )
        {
            return dwError ;
        }
        startPage += numPagesInRegion ;
    }

    /* Check if there is a unlock operation on flash1 */
    if (crossUnlock == 1)
    {
        start = IFLASH1_ADDR;
        end = endBak;
        crossUnlock = 0;
        goto fd_unlock;
    }

    return 0 ;
}

/**
 * \brief Returns the number of locked regions inside the given address range.
 *
 * \param start  Start address of range
 * \param end    End address of range.
 */
extern uint32_t FLASHD_IsLocked( uint32_t start, uint32_t end )
{
    Efc *pEfc ;
    uint16_t startPage, endPage ;
    uint8_t startRegion, endRegion ;
    uint32_t numPagesInRegion ;
    uint32_t status ;
    uint32_t dwError ;
    uint32_t numLockedRegions = 0 ;

    assert( end >= start ) ;
    assert( (start >=IFLASH0_ADDR) && (end <= IFLASH0_ADDR + IFLASH_SIZE) ) ;

    uint32_t crossLockCheck = 0;
    uint32_t endBak = end;

    /* Check if the lock check space will cross over flash0 and flash1 */
    if ( (start >= IFLASH1_ADDR) || (end <= IFLASH1_ADDR) )
    {
        crossLockCheck = 0;
    }
    else
    {
        /* Save information for lock check on flash1 */
        crossLockCheck = 1;
        endBak = end;
        /* Adjust end address for lock check on flash0 */
        end = (IFLASH1_ADDR - 1);
    }

fd_lock_check:
    /* Compute page numbers */
    EFC_TranslateAddress( &pEfc, start, &startPage, 0 ) ;
    EFC_TranslateAddress( 0, end, &endPage, 0 ) ;

    /* Compute region numbers */
    numPagesInRegion = IFLASH_LOCK_REGION_SIZE / IFLASH_PAGE_SIZE ;
    startRegion = startPage / numPagesInRegion ;
    endRegion = endPage / numPagesInRegion ;
    if ((endPage % numPagesInRegion) != 0)
    {
        endRegion++ ;
    }

    /* Retrieve lock status */
    dwError = EFC_PerformCommand( pEfc, EFC_FCMD_GLB, 0, _dwUseIAP ) ;

    if( dwError )
    {
        TRACE_ERROR("EFC_PerformCommand error %u\n\r", (unsigned int)dwError);
        /* Wait for watchdog expire or froze the program */
        while (1);
    }

    status = EFC_GetResult( pEfc ) ;

    /* Check status of each involved region */
    while ( startRegion < endRegion )
    {
        if ( (status & (1 << startRegion)) != 0 )
        {
            numLockedRegions++ ;
        }
        startRegion++ ;
    }

    /* Check if there is a lock check on flash1 */
    if (crossLockCheck == 1)
    {
        start = IFLASH1_ADDR;
        end = endBak;
        crossLockCheck = 0;
        goto fd_lock_check;
    }

    return numLockedRegions ;
}

/**
 * \brief Check if the given GPNVM bit is set or not.
 *
 * \param gpnvm  GPNVM bit index.
 * \returns 1 if the given GPNVM bit is currently set; otherwise returns 0.
 */
extern uint32_t FLASHD_IsGPNVMSet( uint8_t ucGPNVM )
{
    uint32_t dwError ;
    uint32_t dwStatus ;

    assert( ucGPNVM < 3 ) ;

    /* Get GPNVMs status */
    dwError = EFC_PerformCommand( EFC0, EFC_FCMD_GFB, 0, _dwUseIAP ) ;

    if( dwError )
    {
        TRACE_ERROR("EFC_PerformCommand error %u\n\r", (unsigned int)dwError);

        /* Wait for watchdog expire or froze the program */
        while (1);
    }

    dwStatus = EFC_GetResult( EFC0 ) ;

    /* Check if GPNVM is set */
    if ( (dwStatus & (1 << ucGPNVM)) != 0 )
    {
        return 1 ;
    }
    else
    {
        return 0 ;
    }
}

/**
 * \brief Sets the selected GPNVM bit.
 *
 * \param gpnvm  GPNVM bit index.
 * \returns 0 if successful; otherwise returns an error code.
 */
extern uint32_t FLASHD_SetGPNVM( uint8_t ucGPNVM )
{
    assert( ucGPNVM < 3 ) ;

    if ( !FLASHD_IsGPNVMSet( ucGPNVM ) )
    {
        return EFC_PerformCommand( EFC0, EFC_FCMD_SFB, ucGPNVM, _dwUseIAP ) ;
    }
    else
    {
        return 0 ;
    }
}

/**
 * \brief Clears the selected GPNVM bit.
 *
 * \param gpnvm  GPNVM bit index.
 * \returns 0 if successful; otherwise returns an error code.
 */
extern uint32_t FLASHD_ClearGPNVM( uint8_t ucGPNVM )
{
    assert( ucGPNVM < 3 ) ;

    if ( FLASHD_IsGPNVMSet( ucGPNVM ) )
    {
        return EFC_PerformCommand( EFC0, EFC_FCMD_CFB, ucGPNVM, _dwUseIAP ) ;
    }
    else
    {
        return 0 ;
    }
}

/**
 * \brief Read the unique ID.
 *
 * \param pdwUniqueID pointer on a 4bytes char containing the unique ID value.
 * \returns 0 if successful; otherwise returns an error code.
 */
#ifdef __ICCARM__
  __ramfunc
#else
  __attribute__ ((section (".ramfunc")))
#endif
uint32_t FLASHD_ReadUniqueID( uint32_t* pdwUniqueID )
{
    uint32_t status ;

    if (pdwUniqueID == NULL) {
        return 1;
    }

    pdwUniqueID[0] = 0 ;
    pdwUniqueID[1] = 0 ;
    pdwUniqueID[2] = 0 ;
    pdwUniqueID[3] = 0 ;

    /* Send the Start Read unique Identifier command (STUI) by writing the Flash
       Command Register with the STUI command.*/
    EFC0->EEFC_FCR = (0x5A << 24) | EFC_FCMD_STUI;

    /* When the Unique Identifier is ready to be read, the FRDY bit in the Flash
       Programming Status Register (EEFC_FSR) falls. */
    do
    {
        status = EFC0->EEFC_FSR ;
    } while ( (status & EEFC_FSR_FRDY) == EEFC_FSR_FRDY ) ;

    /* The Unique Identifier is located in the first 128 bits of the Flash
       memory mapping.*/
    pdwUniqueID[0] = *(uint32_t *)IFLASH0_ADDR;
    pdwUniqueID[1] = *(uint32_t *)(IFLASH0_ADDR + 4);
    pdwUniqueID[2] = *(uint32_t *)(IFLASH0_ADDR + 8);
    pdwUniqueID[3] = *(uint32_t *)(IFLASH0_ADDR + 12);

    /* To stop the Unique Identifier mode, the user needs to send the Stop Read
       unique Identifier command (SPUI) by writing the Flash Command Register
       with the SPUI command. */
    EFC0->EEFC_FCR = (0x5A << 24) | EFC_FCMD_SPUI ;

    /* When the Stop read Unique Unique Identifier command (SPUI) has been
       performed, the FRDY bit in the Flash Programming Status Register (EEFC_FSR)
       rises. */
    do
    {
        status = EFC0->EEFC_FSR ;
    } while ( (status & EEFC_FSR_FRDY) != EEFC_FSR_FRDY ) ;

    return 0;
}

