
/**
* \file
*
* Implementation of low level library.
*
*/

#if defined __ICCARM__ /* IAR Ewarm 5.41+ */

#include "board.h"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <yfuns.h>

extern __weak size_t __write( int handle, const unsigned char *buf, size_t bufSize )
{
    size_t nChars = 0 ;

    /* Check for the command to flush all handles */
    if ( handle == -1 )
    {
        return 0 ;
    }

    /* Check for stdout and stderr (only necessary if FILE descriptors are enabled.) */
    if ( handle != 1 && handle != 2 )
    {
        /* remove warnings */
        return 0xfffffff ;
    }

    for ( /* Empty */ ; bufSize > 0 ; --bufSize )
    {
        UART_PutChar( *buf ) ;
        ++buf ;
        ++nChars ;
    }

    return nChars ;
}


extern __weak size_t __read( int handle, unsigned char *buf, size_t bufSize )
{
  size_t nChars = 0 ;

  /* Check for stdin (only necessary if FILE descriptors are enabled) */
  if ( handle != 0 )
  {
    /* remove warnings */
    return 0xfffffff ;
  }

  for ( /*Empty*/; bufSize > 0 ; --bufSize )
  {
    unsigned char c = UART_GetChar() ;

    if ( c == 0 )
    {
      break ;
    }
    *buf++ = c ;
    ++nChars ;
  }

  return nChars ;
}

/**
 * \brief Outputs a character on the UART.
 *
 * \param c  Character to output.
 *
 * \return The character that was output.
 */
extern __weak signed int putchar( signed int c )
{
    UART_PutChar( c ) ;

    return c ;
}
#endif // defined __ICCARM__
