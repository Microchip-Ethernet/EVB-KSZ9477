/* ----------------------------------------------------------------------------
 *         SAM Software Package License 
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
 
/** \file */

 /*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/
#include <board.h>
#include <libpmecc.h>
 
/*------------------------------------------------------------------------------ */
/*         Variables                                                             */
/*------------------------------------------------------------------------------ */
/** Current initialized PmeccDescriptor instance*/
static PmeccDescriptor *pCurrentPmeccDescriptor = 0;
#if !defined (USE_PMECC_EMBEDDED_ALGO)
 /*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

 /**
 * \brief Build the pseudo syndromes table
 * \param pPmeccDescriptor Pointer to a PmeccDescriptor instance.
 * \param sector Targetted sector.
 */ 
 
static void GenSyn( PmeccDescriptor *pPmeccDescriptor, uint32_t sector )
{
    int16_t *pRemainer;
    uint32_t index;
    pRemainer = ( int16_t *) &( HSMC->HSMC_REM[sector] );

    for (index = 0; index < (uint32_t)pPmeccDescriptor->tt; index++) 
    {
        /* Fill odd syndromes */
        pPmeccDescriptor->partialSyn[1 + ( 2 * index )] = pRemainer[index];
    }
}

/**
 * \brief The substitute function evaluates the polynomial remainder, 
 * with different values of the field primitive elements.
 * \param pPmeccDescriptor Pointer to a PmeccDescriptor instance.
 */ 
static uint32_t substitute( PmeccDescriptor *pPmeccDescriptor )
{
    int32_t i, j;
    int16_t *si;
    int16_t *pPartialSyn = pPmeccDescriptor->partialSyn;
    int16_t *alpha_to = pPmeccDescriptor->alpha_to;
    int16_t *index_of = pPmeccDescriptor->index_of;


    /* si[] is a table that holds the current syndrome value, an element of that table belongs to the field.*/
    si = pPmeccDescriptor->si;

    for ( i = 1; i < 2 * NB_ERROR_MAX; i++ ) 
    {  
        si[i] = 0; 
    } 

    /* Computation 2t syndromes based on S(x) */
    /* Odd syndromes */
    for ( i = 1; i <= 2 * pPmeccDescriptor->tt - 1; i = i + 2 ) 
    {
        si[i] = 0; 
        for (j = 0; j < pPmeccDescriptor->mm; j++)  
        {
            if ( pPartialSyn[i] & ((uint16_t)0x1 << j) )
                si[i] = alpha_to[(i * j)] ^ si[i];
        }
    }
    /* Even syndrome = (Odd syndrome) ** 2 */
    for (i = 2; i <= 2 * pPmeccDescriptor->tt; i = i + 2 ) 
    {
        j = i / 2;
        if (si[j] == 0)
        {
            si[i] = 0;
        }
        else
        {
            si[i] = alpha_to[(2 * index_of[si[j]]) % pPmeccDescriptor->nn];
        }
    }
    return 0;
}

/**
 * \brief The substitute function finding the value of the error
 * location polynomial.
 * \param pPmeccDescriptor Pointer to a PmeccDescriptor instance.
 */ 
static uint32_t get_sigma( PmeccDescriptor *pPmeccDescriptor )
{
    uint32_t dmu_0_count;
    int32_t i, j, k;
    int16_t *lmu = pPmeccDescriptor->lmu;
    int16_t *si = pPmeccDescriptor->si;
    int16_t tt = pPmeccDescriptor->tt;

    /* mu          */
    int32_t mu[NB_ERROR_MAX+1];
    
    /* discrepancy */
    int32_t dmu[NB_ERROR_MAX+1];
    
    /* delta order   */
    int32_t delta[NB_ERROR_MAX+1];
    
    /* index of largest delta */
    int32_t ro;
    int32_t largest;
    int32_t diff; 

    dmu_0_count = 0;
    
    /*     First Row      */ 
    
    /* Mu */ 
    mu[0]  = -1; 
    /* Actually -1/2 */ 
    /* Sigma(x) set to 1 */ 

    for ( i = 0; i < (2 * NB_ERROR_MAX + 1 ); i++ ) 
        pPmeccDescriptor->smu[0][i] = 0; 

    pPmeccDescriptor->smu[0][0] = 1; 

    /* discrepancy set to 1 */ 
    dmu[0] = 1; 

    /* polynom order set to 0 */ 
    lmu[0] = 0; 

    /* delta set to -1 */ 
    delta[0]  = (mu[0] * 2 - lmu[0]) >> 1; 


    /*                     */ 
    /*     Second Row      */ 
    /*                     */ 
    
    /* Mu */ 
    mu[1]  = 0; 

    /* Sigma(x) set to 1 */ 
    for ( i = 0; i < (2 * NB_ERROR_MAX + 1); i++ )    
        pPmeccDescriptor->smu[1][i] = 0; 

    pPmeccDescriptor->smu[1][0] = 1; 

    /* discrepancy set to S1 */ 
    dmu[1] = si[1]; 

    /* polynom order set to 0 */ 
    lmu[1] = 0;
    

    /* delta set to 0 */ 
    delta[1]  = (mu[1] * 2 - lmu[1]) >> 1;

    /* Init the Sigma(x) last row */ 
    for ( i = 0; i < (2 * NB_ERROR_MAX + 1); i++ )    
        pPmeccDescriptor->smu[tt + 1][i] = 0;


    for ( i = 1; i <= tt; i++) 
    {   
        mu[i+1] = i << 1;
        /* Compute Sigma (Mu+1)             */
        /* And L(mu)                        */  
        /* check if discrepancy is set to 0 */  
        if ( dmu[i] == 0)  
        {
            dmu_0_count++;
            if (( tt - (lmu[i] >> 1) - 1) & 0x1)
            {
                if ( dmu_0_count == (uint32_t)(( tt - (lmu[i] >> 1) - 1) / 2) + 2 )
                {
                    for ( j = 0; j <= (lmu[i] >> 1 ) + 1; j++)
                    {    
                        pPmeccDescriptor->smu[tt+1][j] = pPmeccDescriptor->smu[i][j];   
                    }  
                    lmu[tt + 1] = lmu[i];
                    return 0;
                }
            }
            else
            {
                if ( dmu_0_count == (uint32_t)((tt - (lmu[i] >> 1) - 1) / 2) + 1 )
                {
                    for ( j = 0; j <= (lmu[i] >> 1) + 1; j++ )
                    {    
                        pPmeccDescriptor->smu[tt + 1][j] = pPmeccDescriptor->smu[i][j];   
                    }   
                    lmu[tt + 1] = lmu[i];
                    return 0;
                }
            }

            /* copy polynom */  
            for ( j = 0; j <= lmu[i] >> 1; j++)
            {    
                pPmeccDescriptor->smu[i + 1][j] = pPmeccDescriptor->smu[i][j];   
            }   

            /* copy previous polynom order to the next */
            lmu[i + 1] = lmu[i];  
        }
        else  
        {
            ro = 0;   
            largest = -1;   
            /* find largest delta with dmu != 0 */   
            for ( j = 0; j < i; j++)   
            {    
                if (dmu[j])    
                {     
                    if (delta[j] > largest)     
                    {      
                        largest = delta[j];      
                        ro = j;      
                    }     
                }    
            }
            
            /* compute difference */
            diff = (mu[i] - mu[ro]);
            
            /* Compute degree of the new smu polynomial */
            if ((lmu[i]>>1) > ((lmu[ro]>>1) + diff))
                lmu[i + 1] = lmu[i];
            else
                lmu[i + 1] = ((lmu[ro]>>1) + diff) * 2;

            /* Init smu[i+1] with 0 */
            for ( k = 0; k < (2 * NB_ERROR_MAX+1); k ++)
                pPmeccDescriptor->smu[i+1][k] = 0;

            /* Compute smu[i+1] */
            for ( k = 0; k <= lmu[ro]>>1; k ++)
                if ( pPmeccDescriptor->smu[ro][k] && dmu[i] )
                     pPmeccDescriptor->smu[i + 1][k + diff] = pPmeccDescriptor->alpha_to[( pPmeccDescriptor->index_of[dmu[i]] 
                                                    + ( pPmeccDescriptor->nn - pPmeccDescriptor->index_of[dmu[ro]] ) 
                                                    + pPmeccDescriptor->index_of[pPmeccDescriptor->smu[ro][k]]) % pPmeccDescriptor->nn];

            for ( k = 0; k <= lmu[i]>>1; k ++ )
                pPmeccDescriptor->smu[i+1][k] ^= pPmeccDescriptor->smu[i][k]; 

        } 

        /*************************************************/
        /*                                               */
        /*      End Compute Sigma (Mu+1)                 */
        /*      And L(mu)                                */ 
        /*************************************************/
        /* In either case compute delta */
        delta[i + 1]  = (mu[i + 1] * 2 - lmu[i + 1]) >> 1;

        /* Do not compute discrepancy for the last iteration */
        if (i < tt)
        {
            for ( k = 0 ; k <= (lmu[i + 1] >> 1); k++ )   
            {
                if (k == 0) 
                    dmu[i + 1] = si[2 * (i - 1) + 3];    
                /* check if one operand of the multiplier is null, its index is -1 */    
                else if ( pPmeccDescriptor->smu[i+1][k] && si[ 2 * ( i - 1 ) + 3 - k] )
                    dmu[i + 1] = pPmeccDescriptor->alpha_to[(pPmeccDescriptor->index_of[pPmeccDescriptor->smu[ i + 1 ][ k ]] 
                               + pPmeccDescriptor->index_of[si[ 2 * ( i - 1 ) + 3 - k]]) % pPmeccDescriptor->nn] ^ dmu[ i + 1]; 
            }
        }
    }
    return 0;
}


/**
 * \brief Init the PMECC Error Location peripheral and start the error
 *        location processing
 * \param pPmeccDescriptor Pointer to a PmeccDescriptor instance.
 * \param SectorSizeInBits Size of the sector in bits.
 * \return Number of errors
 */ 
static int32_t ErrorLocation ( PmeccDescriptor *pPmeccDescriptor, uint32_t SectorSizeInBits )
{
    uint32_t alphax;
    uint32_t *pSigma;
    uint32_t errorNumber;
    uint32_t NbrOfRoots; 

    /* Disable PMECC Error Location IP */
    HSMC->HSMC_ELDIS |= 0xFFFFFFFF;
    errorNumber = 0;
    alphax = 0;

    pSigma = (uint32_t *) &(HSMC->HSMC_SIGMA0);
    
    for ( alphax = 0; alphax <= (uint32_t)(pPmeccDescriptor->lmu[pPmeccDescriptor->tt + 1] >> 1); alphax++) 
    {

        *pSigma++ = pPmeccDescriptor->smu[pPmeccDescriptor->tt + 1][alphax];
        errorNumber++;
    }

    HSMC->HSMC_ELCFG |= ((errorNumber - 1) << 16);
    /* Enable error location process */
    HSMC->HSMC_ELEN = SectorSizeInBits;     

    while ((HSMC->HSMC_ELISR & HSMC_ELISR_DONE) == 0);

    NbrOfRoots = (HSMC->HSMC_ELISR & HSMC_ELISR_ERR_CNT_Msk) >> 8;
    /* Number of roots == degree of smu hence <= tt */
    if (NbrOfRoots == (uint32_t)(pPmeccDescriptor->lmu[pPmeccDescriptor->tt + 1] >> 1))
        return (errorNumber - 1);
    
    /* Number of roots not match the degree of smu ==> unable to correct error */
    return -1;  
}

/**
 * \brief Correct errors indicated in the PMECCEL error location registers.
 * \param sectorBaseAddress Base address of the sector.
 * \param ExtraBytes Number of extra bytes of the sector.(encoded Spare Area, only for the last sector)
 * \param ErrorNbr Number of error to correct
 * \return Number of errors
 */ 
static uint32_t ErrorCorrection( uint32_t sectorBaseAddress, uint32_t ExtraBytes, uint32_t ErrorNbr)
{
    uint32_t *pErrPos;
    uint32_t bytePos;
    uint32_t bitPos;
    uint32_t sectorSize;
    uint32_t eccSize;
    uint32_t eccEndAddr;

    pErrPos = (uint32_t *) (&(HSMC->HSMC_ERRLOC[0]));

    sectorSize = 512 * (((HSMC->HSMC_PMECCFG & HSMC_PMECCFG_SECTORSZ) >> 4) + 1);
    /* Get number of ECC bytes */
    eccEndAddr = HSMC->HSMC_PMECCEADDR;
    eccSize = (eccEndAddr - HSMC->HSMC_PMECCSADDR) + 1;

    while ( ErrorNbr )
    {
        bytePos = (*pErrPos - 1) / 8;
        bitPos = (*pErrPos - 1) % 8;

        if ( bytePos < (sectorSize + ExtraBytes))   /* If error is located in the data area(not in ECC) */
        {
            if ( bytePos < sectorSize + HSMC->HSMC_PMECCSADDR) /* If the error position is before ECC area */
            {
                printf("Correct error bit @[#Byte %u,Bit# %u]\n\r", (unsigned int)bytePos, (unsigned int)bitPos);
                if ( *(uint8_t*)(sectorBaseAddress + bytePos) & (1 << bitPos)) 
                    *(uint8_t*)(sectorBaseAddress + bytePos) &= (0xFF ^ (1 << bitPos));
                else
                    *(uint8_t*)(sectorBaseAddress + bytePos) |= (1 << bitPos);
            }
            else
            {
                if (*(uint8_t*)(sectorBaseAddress + bytePos + eccSize)& (1 << bitPos)) 
                    *(uint8_t*)(sectorBaseAddress + bytePos + eccSize) &= (0xFF ^ (1 << bitPos));
                else
                    *(uint8_t*)(sectorBaseAddress + bytePos + eccSize) |= (1 << bitPos);
            }    
        }
        pErrPos++;
        ErrorNbr--;
    }
    return 0;
}
#endif
/**
 * \brief Configure the PMECC peripheral
 * \param pPmeccDescriptor Pointer to a PmeccDescriptor instance.
 */ 
static void PMECC_Configure ( PmeccDescriptor *pPmeccDescriptor ) 
{
    /* Disable ECC module */
    HSMC->HSMC_PMECCTRL |= HSMC_PMECCTRL_DISABLE;

    /* Reset the ECC module */
    HSMC->HSMC_PMECCTRL = HSMC_PMECCTRL_RST;
    HSMC->HSMC_PMECCFG = pPmeccDescriptor->errBitNbrCapability |
                       pPmeccDescriptor->sectorSize |
                       pPmeccDescriptor->pageSize | 
                       pPmeccDescriptor->nandWR |
                       pPmeccDescriptor->spareEna |
                       pPmeccDescriptor->modeAuto;

    HSMC->HSMC_PMECCSAREA = pPmeccDescriptor->spareSize - 1;

    HSMC->HSMC_PMECCSADDR = pPmeccDescriptor->eccStartAddr;

    HSMC->HSMC_PMECCEADDR = pPmeccDescriptor->eccEndAddr - 1;

    /* Disable all interrupts */
    HSMC->HSMC_PMECCIDR = 0xFF;

    /* Enable ECC module */
    HSMC->HSMC_PMECCTRL |= HSMC_PMECCTRL_ENABLE;
}


/*----------------------------------------------------------------------------
 *        Export functions
 *----------------------------------------------------------------------------*/
/**
 * \brief Initialize the PMECC peripheral
 * \param pPmeccDescriptor Pointer to a PmeccDescriptor instance.
 * \param sectorSize 0 for 512, 1 for 1024.
 * \param eccErrorsPersector Coded value of ECC bit number correction(2,4,8,12,24).
 * \param pageDataSize Data area size in byte.
 * \param pageDataSize Spare area size in byte.
 * \param EccOffset offset of the first ecc byte in spare zone.
 * \param spareProtected 1: The spare area is protected with the last sector of data.
 *                       0: The spare area is skipped in read or write mode.
 * \return 0 if successful; otherwise returns 1.
 */ 

uint8_t PMECC_Initialize( PmeccDescriptor *pPmeccDescriptor, 
                          uint8_t sectorSize ,
                          uint8_t eccErrorsPersector,
                          uint32_t pageDataSize,
                          uint32_t pageSpareSize,
                          uint16_t EccOffset,
                          uint8_t spareProtected)
{
    uint8_t nbSectorsPerPage = 0;
    pCurrentPmeccDescriptor = pPmeccDescriptor;
    if (eccErrorsPersector == 0xFF)
    {
        /* ONFI 2.2 : a value of 0xff indaicate we must apply a correction on sector > 512 bytes,
           so we set at the maximum allowed by PMECC 24 bits on 1024 sectors. */
        eccErrorsPersector = 24;
        sectorSize = 1;   /* 1 for 1024 bytes per sector */
    }
    /* Number of Sectors in one Page */
    switch ( sectorSize ) {
        /* 512 bytes per sector */
        case 0: 
            pPmeccDescriptor->sectorSize = (0 << 4);
            nbSectorsPerPage = pageDataSize / 512;
            pPmeccDescriptor->mm = 13;
#if defined ( GALOIS_TABLE_512_ROM_MAPPING ) && defined (GALOIS_TABLE_IN_ROM)
            pPmeccDescriptor->alpha_to = (int16_t *) &(pmecc_gf_512[PMECC_GF_SIZEOF_512]);
            pPmeccDescriptor->index_of = (int16_t *) &(pmecc_gf_512[0]);
#else
            pPmeccDescriptor->alpha_to = (int16_t *) &(pmecc_gf_512[PMECC_GF_ALPHA_TO]);
            pPmeccDescriptor->index_of = (int16_t *) &(pmecc_gf_512[PMECC_GF_INDEX_OF]);
#endif
            break;
        /* 1024 bytes per sector */
        case 1: 
            pPmeccDescriptor->sectorSize = HSMC_PMECCFG_SECTORSZ;
            nbSectorsPerPage = pageDataSize / 1024;
            pPmeccDescriptor->mm = 14;
#if defined ( GALOIS_TABLE_1024_ROM_MAPPING ) && defined (GALOIS_TABLE_IN_ROM)
            pPmeccDescriptor->alpha_to = (int16_t *) &(pmecc_gf_1024[PMECC_GF_SIZEOF_1024]);
            pPmeccDescriptor->index_of = (int16_t *) &(pmecc_gf_1024[0]);
#else
            pPmeccDescriptor->alpha_to = (int16_t *) &(pmecc_gf_1024[PMECC_GF_ALPHA_TO]);
            pPmeccDescriptor->index_of = (int16_t *) &(pmecc_gf_1024[PMECC_GF_INDEX_OF]);
#endif
            break;
    }
    switch ( nbSectorsPerPage )
    {
        case 1:
            pPmeccDescriptor->pageSize = HSMC_PMECCFG_PAGESIZE_PAGESIZE_1SEC;
            break;
        case 2:
            pPmeccDescriptor->pageSize = HSMC_PMECCFG_PAGESIZE_PAGESIZE_2SEC;
            break;
        case 4:
            pPmeccDescriptor->pageSize = HSMC_PMECCFG_PAGESIZE_PAGESIZE_4SEC;
            break;
        case 8:
            pPmeccDescriptor->pageSize = HSMC_PMECCFG_PAGESIZE_PAGESIZE_8SEC;
            break;
        default :
            pPmeccDescriptor->pageSize = HSMC_PMECCFG_PAGESIZE_PAGESIZE_1SEC;
            break;
    }
    pPmeccDescriptor->nn = (1 << pPmeccDescriptor->mm) - 1;
    /* Coded value of ECC bit number correction (0 (2 bits), 1 (4 bits), 2 (8 bits), 3 (12 bits), 4 (24 bits), 5 (NU)) */
    switch ( eccErrorsPersector ) 
    {
            case 2:
                pPmeccDescriptor->errBitNbrCapability = HSMC_PMECCFG_BCH_ERR_BCH_ERR2;
                break;
            case 4:
                pPmeccDescriptor->errBitNbrCapability = HSMC_PMECCFG_BCH_ERR_BCH_ERR4;
                break;
            case 8:
                pPmeccDescriptor->errBitNbrCapability = HSMC_PMECCFG_BCH_ERR_BCH_ERR8;
                break;
            case 12:
                pPmeccDescriptor->errBitNbrCapability = HSMC_PMECCFG_BCH_ERR_BCH_ERR12;
                break;
            case 24:
                pPmeccDescriptor->errBitNbrCapability = HSMC_PMECCFG_BCH_ERR_BCH_ERR24;
                break;
            default:
                pPmeccDescriptor->errBitNbrCapability = HSMC_PMECCFG_BCH_ERR_BCH_ERR2;
                eccErrorsPersector = 2;
                break;
        }

    /* Real value of ECC bit number correction (2, 4, 8, 12, 24) */
    pPmeccDescriptor->tt = eccErrorsPersector;
    if ((( pPmeccDescriptor->mm * eccErrorsPersector ) % 8 ) == 0)
    {
        pPmeccDescriptor->eccSizeByte = ((pPmeccDescriptor->mm * eccErrorsPersector ) / 8) * nbSectorsPerPage;
    }
    else 
    {
        pPmeccDescriptor->eccSizeByte = (((pPmeccDescriptor->mm * eccErrorsPersector ) / 8 ) + 1 ) * nbSectorsPerPage;
    }
    if (EccOffset <= 2)
    {
        pPmeccDescriptor->eccStartAddr = PMECC_ECC_DEFAULT_START_ADDR;
    }
    else {
        pPmeccDescriptor->eccStartAddr = EccOffset;
    }
    pPmeccDescriptor->eccEndAddr = pPmeccDescriptor->eccStartAddr + pPmeccDescriptor->eccSizeByte;
    if (pPmeccDescriptor->eccEndAddr > pageSpareSize)
    {
        return 1;
    }
    pPmeccDescriptor->spareSize = pPmeccDescriptor->eccEndAddr;

    //pPmeccDescriptor->nandWR = PMECC_CFG_NANDWR;  /* NAND write access */
    pPmeccDescriptor->nandWR = 0;  /* NAND Read access */
    if (spareProtected )
    {
        pPmeccDescriptor->spareEna = HSMC_PMECCFG_SPAREEN;
    }
    else 
    {
        pPmeccDescriptor->spareEna = 0;
    }
    /* PMECC_CFG_AUTO indicates that the spare is error protected. In this case, the ECC computation takes into account the whole spare area
    minus the ECC area in the ECC computation operation */
    pPmeccDescriptor->modeAuto = 0; 
    pPmeccDescriptor->clkCtrl = 2; /* At 133 Mhz, this field must be programmed with 2,
    indicating that the setup time is 3 clock cycles.*/
    pPmeccDescriptor->interrupt = 0;
    PMECC_Configure ( pPmeccDescriptor );
    return 0;
}

/**
 * \brief This fuction is able to build Galois Field.
 * \param mm degree of the remainders.
 * \param index_of Pointer to a buffer for index_of table.
 * \param alpha_to Pointer to a buffer for alpha_to table.
 */ 
void build_gf( uint32_t mm, int16_t* index_of, int16_t* alpha_to )
{
    uint32_t i;
    uint32_t mask;
    uint32_t nn;
    uint32_t p[15];

    nn = (1 << mm) - 1;
    /* set default value */
    for (i = 1; i < mm; i++)
        p[i] = 0;

    /*  1 + X^mm */
    p[0]  = 1;
    p[mm] = 1;

    /*  others  */
    if (mm == 3)
        p[1] = 1;
    else if (mm == 4)
        p[1] = 1;
    else if (mm == 5)
        p[2] = 1;
    else if (mm == 6)
        p[1] = 1;
    else if (mm == 7)
        p[3] = 1;
    else if (mm == 8)
        p[2] = p[3] = p[4] = 1;
    else if (mm == 9)
        p[4] = 1;
    else if (mm == 10)
        p[3] = 1;
    else if (mm == 11)
        p[2] = 1;
    else if (mm == 12)
        p[1] = p[4] = p[6] = 1;
    else if (mm == 13)
        p[1] = p[3] = p[4] = 1;
    else if (mm == 14)
        p[1] = p[6] = p[10] = 1;
    else if (mm == 15)
        p[1] = 1;

    /*-- First of All */
    /*-- build alpha ^ mm it will help to generate the field (primitiv) */
    alpha_to[mm] = 0;
    for (i = 0; i < mm; i++)
        if (p[i])
            alpha_to[mm] |= 1 << i;
     
    /* Secondly */
    /* Build elements from 0 to mm - 1 */
    /* very easy because degree is less than mm so it is */
    /* just a logical shift ! (only the remainder) */
    mask = 1;
    for (i = 0; i < mm; i++)
    {
        alpha_to[i] = mask;
        index_of[alpha_to[i]] = i;
        mask <<= 1;
    }

    index_of[alpha_to[mm]] = mm ;

    /* use a mask to select the MSB bit of the */
    /* LFSR ! */
    mask >>= 1; /* previous value moust be decremented */

    /* then finish the building */
    for (i = mm + 1; i <= nn; i++)
    {
        /* check if the msb bit of the lfsr is set */
        if (alpha_to[i-1] & mask)
            /* feedback loop is set */
            alpha_to[i] = alpha_to[mm] ^ ((alpha_to[i-1] ^ mask) << 1);
        else
            /*  only shift is enabled */
            alpha_to[i] = alpha_to[i-1] << 1;
        /*  lookup table */
        //index_of[alpha_to[i]] = i ;
        index_of[alpha_to[i]] = i%nn ;      //!!!!!!!!!!!!Pst modif
    }
    /* of course index of 0 is undefined in a multiplicative field */
    index_of[0] = -1;
}

#if !defined (USE_PMECC_EMBEDDED_ALGO)
/**
 * \brief Launch error detection functions and correct corrupted bits.
 * \param pPmeccDescriptor Pointer to a PmeccDescriptor instance.
 * \param pmeccStatus Value of the PMECC status register.
 * \param pageBuffer Base address of the buffer containing the page to be corrected.
 * \param ErrorNbr Number of error to correct
 * \return 0 if all errors have been corrected, 1 if too many errors detected
 */ 
uint32_t PMECC_CorrectionAlgo( PmeccDescriptor *pPmeccDescriptor,
                               uint32_t pmeccStatus,
                               uint32_t pageBuffer)
{
    uint32_t sectorNumber = 0;
    uint32_t sectorBaseAddress;
    volatile int32_t errorNbr;
    
    /* Set the sector size (512 or 1024 bytes) */

    HSMC->HSMC_ELCFG = (pPmeccDescriptor->sectorSize >> 4 );

    while ( sectorNumber < (uint32_t)((1 << ((HSMC->HSMC_PMECCFG & HSMC_PMECCFG_PAGESIZE_Msk) >> 8)))) {

        errorNbr = 0;
        if ( pmeccStatus & 0x1 ) {

            sectorBaseAddress = pageBuffer + (sectorNumber * ((pPmeccDescriptor->sectorSize >> 4) + 1) * 512);

            GenSyn( pPmeccDescriptor, sectorNumber );

            substitute( pPmeccDescriptor );

            get_sigma( pPmeccDescriptor );
            errorNbr = ErrorLocation( pPmeccDescriptor, 
                       (((pPmeccDescriptor->sectorSize >> 4) + 1) * 512 * 8) 
                       + (pPmeccDescriptor->tt * (13 + (pPmeccDescriptor->sectorSize >> 4))));  /* number of bits of the sector + ecc */

            if (errorNbr == -1) {
                return 1;
            }
            else 
            {
                ErrorCorrection( sectorBaseAddress, 0, errorNbr );       /* Extra byte is 0 */
            }
        }
        sectorNumber++;
        pmeccStatus = pmeccStatus >> 1;
    }
        
    return 0;
}
#endif

/**
 * \brief Get current PmeccDescriptor
 *
 * \return current PmeccDescriptor.
 */ 

PmeccDescriptor * PMECC_GetCurrentPmeccDescriptor ( void )
{
    return  pCurrentPmeccDescriptor;
}

/**
 * \brief Disable pmecc.
 *
 */ 
void PMECC_Disable( void )
{
    /* Disable ECC module */
    HSMC->HSMC_PMECCTRL |= HSMC_PMECCTRL_DISABLE;
    pCurrentPmeccDescriptor = 0;
}
