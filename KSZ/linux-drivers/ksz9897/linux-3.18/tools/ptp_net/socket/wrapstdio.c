/* -----------------------------------------------------------------------------

    Modified from W. Richard Stevens's UNIX Network Programming to run under
    Windows
----------------------------------------------------------------------------- */

/*
 * Standard I/O wrapper functions.
 */

#include <stdio.h>
#include "error.h"


void
Fclose (
    FILE *fp )
{
    if ( fclose( fp ) != 0 )
        err_sys( "fclose error" );
}  /* FClose */


char *
Fgets (
    char *ptr,
    int  n,
    FILE *stream )
{
    char *rptr;

    if ( ( rptr = fgets( ptr, n, stream )) == NULL  &&  ferror( stream ) )
        err_sys( "fgets error" );
    return( rptr );
}  /* Fgets */


FILE *
Fopen (
    const char *filename,
    const char *mode )
{
    FILE *fp;

    if ( ( fp = fopen( filename, mode )) == NULL )
        err_sys( "fopen error" );
    return( fp );
}  /* Fopen */


void
Fputs (
    const char *ptr,
    FILE       *stream )
{
    if ( fputs( ptr, stream ) == EOF )
        err_sys( "fputs error" );
}  /* Fputs */
