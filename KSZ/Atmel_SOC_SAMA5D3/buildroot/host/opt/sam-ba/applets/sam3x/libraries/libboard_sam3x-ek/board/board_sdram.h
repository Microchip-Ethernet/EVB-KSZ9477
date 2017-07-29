#ifndef _BOARD_SDRAM_
#define _BOARD_SDRAM_

/**
 * \file
 * \section SDRAM
 * - \ref BOARD_SDRAM_SIZE
 * - \ref PIN_SDRAM
 * - \ref BOARD_SDRAM_BUSWIDTH
 *
 */

// ----------------------------------------------------------------------------------------------------------
// SDRAM
// ----------------------------------------------------------------------------------------------------------
/**  Board SDRAM size for MT48LC16M16A2 */
#define BOARD_SDRAM_SIZE        (32*1024*1024)  // 32 MB

/**  List of all SDRAM pins definitions */
#define PIO_SDRAM_SDCKE PIO_PD13
#define PIO_SDRAM_SDCS PIO_PD12
#define PIO_SDRAM_RAS PIO_PD15
#define PIO_SDRAM_CAS PIO_PD16
#define PIO_SDRAM_BA0 PIO_PD6
#define PIO_SDRAM_BA1 PIO_PD7
#define PIO_SDRAM_SDWE PIO_PD14
#define PIO_SDRAM_NBS0 PIO_PC21
#define PIO_SDRAM_NBS1 PIO_PD10
#define PIO_SDRAM_DATA (0xffff << 2)    //PIO_PC2--PIO_PC17
#define PIO_SDRAM_SDA0_A7 (0xff << 23)    //PIO_PC23--PIO_PC30
#define PIO_SDRAM_SDA8 PIO_PD22
#define PIO_SDRAM_SDA9 PIO_PD23
#define PIO_SDRAM_SDA11 PIO_PD25
#define PIO_SDRAM_SDA12 PIO_PD4
#define PIO_SDRAM_SDA10 PIO_PD11

/**  List of all SDRAM pins definitions */
#define PINS_SDRAM_PIOC              { PIO_SDRAM_DATA | PIO_SDRAM_NBS0 | PIO_SDRAM_SDA0_A7, \
                                      PIOC, ID_PIOC, PIO_PERIPH_A, PIO_PULLUP }

#define PINS_SDRAM_PIOD              { PIO_SDRAM_SDCKE | PIO_SDRAM_SDCS | \
                                       PIO_SDRAM_RAS | PIO_SDRAM_CAS | \
                                       PIO_SDRAM_BA0 | PIO_SDRAM_BA1 | \
                                       PIO_SDRAM_SDWE | PIO_SDRAM_NBS1 | \
                                       PIO_SDRAM_SDA10 | \
                                       PIO_SDRAM_SDA8 | PIO_SDRAM_SDA9 | \
                                       PIO_SDRAM_SDA11 | PIO_SDRAM_SDA12, \
                                       PIOD, ID_PIOD, PIO_PERIPH_A, PIO_PULLUP }

/* PIO18 is used as SDRAM Enable on EK-REVB board */
#define PINS_SDRAM_EN     { (1<<18), PIOD, ID_PIOD, PIO_OUTPUT_1, PIO_DEFAULT }

#define PINS_SDRAM        PINS_SDRAM_PIOC,PINS_SDRAM_PIOD,PINS_SDRAM_EN

/**  SDRAM bus width */
#define BOARD_SDRAM_BUSWIDTH    16

/* SDRAMC clock speed */
#define SDRAMC_CLK (BOARD_MCK)

#endif /* _BOARD_SDRAM_ */
