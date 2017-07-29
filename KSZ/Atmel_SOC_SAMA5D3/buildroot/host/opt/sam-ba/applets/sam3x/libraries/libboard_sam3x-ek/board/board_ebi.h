#ifndef _BOARD_EBI_
#define _BOARD_EBI_

/**
 * \file 
 * EBI
 * - \ref PIN_EBI_DATA_BUS
 * - \ref PIN_EBI_NRD
 * - \ref PIN_EBI_NWE
 * - \ref PIN_EBI_NCS0
 * - \ref PIN_EBI_PSRAM_ADDR_BUS
 * - \ref PIN_EBI_PSRAM_NBS
 * - \ref PIN_EBI_A1
 * - \ref PIN_EBI_NCS1
 * - \ref PIN_EBI_LCD_RS
 *
 */
 
// ----------------------------------------------------------------------------------------------------------
// EBI
// ----------------------------------------------------------------------------------------------------------
/** EBI Data Bus pins */
#define PIN_EBI_DATA_BUS            {0xFFFF << 2,    PIOC, ID_PIOC, PIO_PERIPH_A, PIO_PULLUP}
/** EBI NRD pin */
#define PIN_EBI_NRD                 {PIO_PA29B_NRD, PIOA, ID_PIOA, PIO_PERIPH_B, PIO_PULLUP}
/** EBI NWE pin */
#define PIN_EBI_NWE                 {PIO_PC18A_NWR0_NWE,  PIOC, ID_PIOC, PIO_PERIPH_A, PIO_PULLUP}
/** EBI NCS0 pin */
#define PIN_EBI_NCS0                {PIO_PA6B_NCS0, PIOA, ID_PIOA, PIO_PERIPH_B, PIO_PULLUP}
/** EBI NCS1 pin */
#define PIN_EBI_NCS1                {PIO_PA7B_NCS1, PIOA, ID_PIOA, PIO_PERIPH_B, PIO_PULLUP}
/** EBI NCS2 pin */
#define PIN_EBI_NCS2                {PIO_PB24B_NCS2, PIOB, ID_PIOB, PIO_PERIPH_B, PIO_PULLUP}
/** EBI pins for PSRAM address bus */
#define PIN_EBI_PSRAM_ADDR_BUS      {0x3f00fff, PIOC, ID_PIOC, PIO_PERIPH_A, PIO_PULLUP}
/** EBI pins for PSRAM NBS pins */
#define PIN_EBI_PSRAM_NBS           {1 << 7, PIOB, ID_PIOB, PIO_PERIPH_B, PIO_PULLUP}, \
                                    {1 << 15, PIOC, ID_PIOC, PIO_PERIPH_A, PIO_PULLUP}
/** EBI pin for LCD RS */
#define PIN_EBI_LCD_RS              {PIO_PC22, PIOC, ID_PIOC, PIO_PERIPH_A, PIO_PULLUP} /* LCD RS pin */



#endif /* _BOARD_EBI_ */
