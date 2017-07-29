#ifndef _LIB_NORFLASH_ 
#define _LIB_NORFLASH_ 


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
 
#include "include/NorFlashCFI.h"
#include "include/NorFlashApi.h"
#include "include/NorFlashCommon.h"
#include "include/NorFlashAmd.h"
#include "include/NorFlashIntel.h"
#endif /* _LIB_NORFLASH_ */
