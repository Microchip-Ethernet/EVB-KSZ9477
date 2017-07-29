#ifndef _BOARD_NANDFLASH_
#define _BOARD_NANDFLASH_

/**
 * \file 
 * NandFlash
 * - \ref PIN_EBI_NANDOE
 * - \ref PIN_EBI_NANDWE
 * - \ref PIN_EBI_NANDCLE
 * - \ref PIN_EBI_NANDALE
 * - \ref PIN_EBI_NANDIO
 * - \ref BOARD_NF_CE_PIN
 * - \ref BOARD_NF_RB_PIN
 * - \ref PINS_NANDFLASH
 *
 */

// ----------------------------------------------------------------------------------------------------------
// NAND FLASH
// checked - tvd
// ----------------------------------------------------------------------------------------------------------
/** NandFlash pins definition: OE. */
#define PIN_EBI_NANDOE          {PIO_PC19A_NANDOE,  PIOC, ID_PIOC, PIO_PERIPH_A, PIO_PULLUP}
/** NandFlash pins definition: WE. */
#define PIN_EBI_NANDWE          {PIO_PC20A_NANDWE, PIOC, ID_PIOC, PIO_PERIPH_A, PIO_PULLUP}
/** NandFlash pins definition: CLE. */
#define PIN_EBI_NANDCLE         {PIO_PD9A_A22_NANDCLE, PIOD, ID_PIOD, PIO_PERIPH_A, PIO_PULLUP}
/** NandFlash pins definition: ALE. */
#define PIN_EBI_NANDALE         {PIO_PD8A_A21_NANDALE, PIOD, ID_PIOD, PIO_PERIPH_A, PIO_PULLUP}
/** NandFlash pins definition: DATA. */
#define PIN_EBI_NANDIO          {0x0000FFFF, PIOC, ID_PIOC, PIO_PERIPH_A, PIO_PULLUP}

#if defined(CHIP_NAND_CTRL)
/** NFC chip select ID definition */
#define BOARD_NF_CSID           NFCADDR_CMD_CSID_0
/** Nandflash chip enable pin definition. */
#define BOARD_NF_CE_PIN         {PIO_PA6B_NCS0, PIOA, ID_PIOA, PIO_PERIPH_B, PIO_PULLUP}
/** Nandflash ready/busy pin definition. */
#define BOARD_NF_RB_PIN         {PIO_PA2B_NANDRDY, PIOA, ID_PIOA, PIO_PERIPH_B, PIO_PULLUP}
#else
/** Nandflash chip enable pin definition. */
#define BOARD_NF_CE_PIN         {PIO_PA6B_NCS0, PIOA, ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT}
/** Nandflash ready/busy pin definition. */
#define BOARD_NF_RB_PIN         {PIO_PA2B_NANDRDY, PIOA, ID_PIOA, PIO_INPUT, PIO_PULLUP}
#endif

/** Nandflash controller peripheral pins definition. */
#define PINS_NANDFLASH          PIN_EBI_NANDIO, BOARD_NF_CE_PIN, BOARD_NF_RB_PIN, PIN_EBI_NANDOE, \
                                PIN_EBI_NANDWE, PIN_EBI_NANDCLE, PIN_EBI_NANDALE

/*
 * \addtopage sam3x_ek_mem
 * \section NandFlash
 * - \ref BOARD_NF_COMMAND_ADDR
 * - \ref BOARD_NF_ADDRESS_ADDR
 * - \ref BOARD_NF_DATA_ADDR
 *
 */

// ----------------------------------------------------------------------------------------------------------
// NAND FLASH
// ----------------------------------------------------------------------------------------------------------
/** Address for transferring command bytes to the nandflash. */
#define BOARD_NF_COMMAND_ADDR   0x60400000
/** Address for transferring address bytes to the nandflash. */
#define BOARD_NF_ADDRESS_ADDR   0x60200000
/** Address for transferring data bytes to the nandflash. */
#define BOARD_NF_DATA_ADDR      0x60000000


#endif /* _BOARD_NANDFLASH_ */
