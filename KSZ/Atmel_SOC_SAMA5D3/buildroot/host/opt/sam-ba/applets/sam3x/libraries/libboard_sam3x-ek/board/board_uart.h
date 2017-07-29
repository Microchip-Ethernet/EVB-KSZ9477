#ifndef _BOARD_UART_
#define _BOARD_UART_

/**
 * \file
 * UART
 * - \ref PINS_UART
 *
 */
 
// ----------------------------------------------------------------------------------------------------------
// UART
// checked - tvd
// ----------------------------------------------------------------------------------------------------------
/** UART pins (UTXD0 and URXD0) definitions, PA8,9. */
#define PINS_UART  { PIO_PA8A_URXD|PIO_PA9A_UTXD, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}



#endif /* _BOARD_UART_ */
