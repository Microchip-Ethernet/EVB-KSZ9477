#ifndef _LIB_ATSAM3S_
#define _LIB_ATSAM3S_

/*
 * Peripherals registers definitions
 */
#include <include/SAM3S.h>


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
 * Core
 */

/*
 * Peripherals
 */
#include <include/efc.h>
#include <include/flashd.h>
#include <include/pio.h>
#include <include/pmc.h>
#include <include/usart.h>


#include <include/trace.h>
#include <include/wdt.h>

#endif /* _LIB_ATSAM3S_ */
