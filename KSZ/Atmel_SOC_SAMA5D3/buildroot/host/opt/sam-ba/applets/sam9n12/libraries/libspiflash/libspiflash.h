#ifndef _LIB_SPIFLASH_ 
#define _LIB_SPIFLASH_ 


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
 
#include "include/spi_dma.h"
#include "include/at25_spi.h"
#include "include/at25d.h"
#include "include/at45_spi.h"
#include "include/at45d.h"

#endif /* _LIB_SPIFLASH_ */
