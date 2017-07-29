/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2013, Atmel Corporation
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

/*------------------------------------------------------------------------------
 *      Linker script for running in internal SRAM on the SAMA5D4
 *----------------------------------------------------------------------------*/

OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(entry)
SEARCH_DIR(.)

/* Memory Spaces Definitions */
MEMORY
{
/*  romcodesram (W!RX) : ORIGIN = 0x210000, LENGTH = 0x10000*/
    sram (W!RX) : ORIGIN = 0x200000, LENGTH = 0x10000 /* sram, 64K */
}


/* Section Definitions */ 
SECTIONS 
{ 
    .fixed0 : 
    { 
        . = ALIGN(4);
        _sfixed = .;
        KEEP(*(.textisp .textisp.*))
        *(.text .text.*) 
        *(.glue_7t) *(.glue_7)
        *(.CP15_*)
        *(.rodata .rodata* )
        
        *(.data .data.*);
        . = ALIGN(4);
        _efixed = .;  /* End of text section */
    } > sram

    . = ALIGN(4); 
    _etext = .;

    .relocate : AT (_etext)
    {
        . = ALIGN(4);
        _srelocate = .;
        . = ALIGN(4);
        _erelocate = .;
    } > sram

    /* .bss section which is used for uninitialized data */ 
    .bss (NOLOAD) :
    { 
       . = ALIGN(4);
        _sbss = . ;
        _szero = .;
        *(.bss .bss.*)
        . = ALIGN(4);
        _ebss = . ;
        _ezero = .;
    } > sram

    _sstack = 0x210000;
    . = ALIGN(4); 
    _end = . ; 
}
end = .;

