#ifndef _LIB_NANDFLASH_ 
#define _LIB_NANDFLASH_ 


/* Define attribute */
#if defined   ( __CC_ARM   ) /* Keil µVision 4 */
    #define WEAK __attribute__ ((weak))
#elif defined ( __ICCARM__ ) /* IAR Ewarm 5.41+ */
    #define WEAK __weak
#elif defined (  __GNUC__  ) /* GCC CS3 2009q3-68 */
    #define WEAK __attribute__ ((weak))
#endif

/* Define NO_INIT attribute */
#if defined   ( __CC_ARM   )
    #define NO_INIT
#elif defined ( __ICCARM__ )
    #define NO_INIT __no_init
#elif defined (  __GNUC__  )
    #define NO_INIT
#endif

/*
 * drivers
 */
 
#include "include/SkipBlockNandFlash.h"
#include "include/RawNandFlash.h"
#include "include/NandSpareScheme.h"
#include "include/NandFlashModelList.h"
#include "include/NandFlashModel.h"
#include "include/NandCommon.h"
#include "include/EccNandFlash.h"
#include "include/NandFlashOnfi.h"
#include "include/NandFlashDma.h"
#endif /* _LIB_NANDFLASH_ */
