/* -----------------------------------------------------------------------------

    Modified from W. Richard Stevens's UNIX Network Programming to run under
    Windows
----------------------------------------------------------------------------- */

/* This is from the BIND 4.9.4 release, modified to compile by itself */

/* Copyright (c) 1996 by Internet Software Consortium.
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND INTERNET SOFTWARE CONSORTIUM DISCLAIMS
 * ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL INTERNET SOFTWARE
 * CONSORTIUM BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 * PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS
 * ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
 * SOFTWARE.
 */

#include <stdio.h>
#include <string.h>
#include "wnp.h"


#define IN6ADDRSZ   16
#define INADDRSZ     4
#define INT16SZ      2

#ifdef __GNUC__
#ifndef AF_INET6
#define AF_INET6     8
#endif
#endif


/*
 * WARNING: Don't even consider trying to compile this on a system where
 * sizeof(int) < 4.  sizeof(int) > 4 is fine; all the world's not a VAX.
 */


/* const char *
 * inet_ntop4(src, dst, size)
 *  format an IPv4 address, more or less like inet_ntoa()
 * return:
 *  `dst' (as a const)
 * notes:
 *  (1) uses no statics
 *  (2) takes a u_char* not an in_addr as input
 * author:
 *  Paul Vixie, 1996.
 */
static const char *
inet_ntop4 (
    const uint8_t *src,
    char          *dst,
    size_t        size )
{
    static const char fmt[] = "%u.%u.%u.%u";

    char tmp[ sizeof "255.255.255.255" ];

    sprintf( tmp, fmt, src[ 0 ], src[ 1 ], src[ 2 ], src[ 3 ]);
    if ( strlen( tmp ) > size ) {

#ifndef __GNUC__
        WSASetLastError( WSAEFAULT );
#endif
        return( NULL );
    }
    strcpy( dst, tmp );
    return( dst );
}  /* inet_ntop4 */


/* const char *
 * inet_ntop6(src, dst, size)
 *  convert IPv6 binary address into presentation (printable) format
 * author:
 *  Paul Vixie, 1996.
 */
static const char *
inet_ntop6 (
    const uint8_t *src,
    char          *dst,
    size_t        size )
{
    /*
     * Note that int32_t and int16_t need only be "at least" large enough
     * to contain a value of the specified size.  On some systems, like
     * Crays, there is no such thing as an integer variable with 16 bits.
     * Keep this in mind if you think this function should have been coded
     * to use pointer overlays.  All the world's not a VAX.
     */
    char     tmp[ sizeof "ffff:ffff:ffff:ffff:ffff:ffff:255.255.255.255" ];
    char     *tp;
    uint32_t words[ IN6ADDRSZ / INT16SZ ];
    int      i;
    struct { int base, len; } best, cur;

    /*
     * Preprocess:
     *  Copy the input (bytewise) array into a wordwise array.
     *  Find the longest run of 0x00's in src[] for :: shorthanding.
     */
    memset( words, 0, sizeof words );
    for ( i = 0; i < IN6ADDRSZ; i++ )
        words[ i / 2 ] |= ( src[ i ] << (( 1 - ( i % 2 )) << 3 ));
    best.base = -1;
    cur.base = -1;
    best.len = 0;
    cur.len = 0;
    for ( i = 0; i < ( IN6ADDRSZ / INT16SZ ); i++ ) {
        if ( words[ i ] == 0 ) {
            if ( cur.base == -1 )
                cur.base = i, cur.len = 1;
            else
                cur.len++;
        }
        else {
            if ( cur.base != -1 ) {
                if ( best.base == -1  ||  cur.len > best.len )
                    best = cur;
                cur.base = -1;
            }
        }
    }
    if ( cur.base != -1 ) {
        if ( best.base == -1  ||  cur.len > best.len )
            best = cur;
    }
    if ( best.base != -1  &&  best.len < 2 )
        best.base = -1;

    /*
     * Format the result.
     */
    tp = tmp;
    for ( i = 0; i < ( IN6ADDRSZ / INT16SZ ); i++ ) {

        /* Are we inside the best run of 0x00's? */
        if ( best.base != -1  &&  i >= best.base  &&
                i < ( best.base + best.len ) ) {
            if ( i == best.base )
                *tp++ = ':';
            continue;
        }

        /* Are we following an initial run of 0x00s or any real hex? */
        if ( i != 0 )
            *tp++ = ':';

        /* Is this address an encapsulated IPv4? */
        if ( i == 6  &&  best.base == 0  &&
                ( best.len == 6  ||  ( best.len == 5  &&
                words[ 5 ] == 0xffff )) ) {
            if ( !inet_ntop4( src + 12, tp, sizeof tmp - ( tp - tmp )) )
                return( NULL );
            tp += strlen( tp );
            break;
        }
        sprintf( tp, "%x", words[ i ]);
        tp += strlen( tp );
    }

    /* Was it a trailing run of 0x00's? */
    if ( best.base != -1  &&  ( best.base + best.len ) ==
            ( IN6ADDRSZ / INT16SZ ) )
        *tp++ = ':';
    *tp++ = '\0';

    /*
     * Check for overflow, copy, and we're done.
     */
    if ( ( size_t )( tp - tmp ) > size ) {

#ifndef __GNUC__
        WSASetLastError( WSAEFAULT );
#endif
        return( NULL );
    }
    strcpy( dst, tmp );
    return( dst );
}  /* inet_ntop6 */


/* char *
 * inet_ntop(af, src, dst, size)
 *  convert a network format address to presentation format.
 * return:
 *  pointer to presentation format address (`dst'), or NULL (see errno).
 * author:
 *  Paul Vixie, 1996.
 */
const char *
_inet_ntop (
    int        af,
    const void *src,
    char       *dst,
    size_t     size )
{
    switch ( af ) {
        case AF_INET:
            return( inet_ntop4( src, dst, size ));
        case AF_INET6:
            return( inet_ntop6( src, dst, size ));
        default:

#ifndef __GNUC__
            WSASetLastError( WSAEAFNOSUPPORT );
#endif
            return( NULL );
    }
    /* NOTREACHED */
}  /* inet_ntop */


const char *
Inet_ntop (
    int        family,
    const void *addrptr,
    char       *strptr,
    size_t     len )
{
    const char *ptr;

    /* check for old code */
    if ( strptr == NULL )
        err_quit( "NULL 3rd argument to inet_ntop" );
    if ( ( ptr = _inet_ntop( family, addrptr, strptr, len )) == NULL )
        err_sys( "inet_ntop error" );
    return( ptr );
}  /* Inet_ntop */

/* -------------------------------------------------------------------------- */

/* int
 * inet_pton4(src, dst)
 *  like inet_aton() but without all the hexadecimal and shorthand.
 * return:
 *  1 if `src' is a valid dotted quad, else 0.
 * notice:
 *  does not touch `dst' unless it's returning 1.
 * author:
 *  Paul Vixie, 1996.
 */
static int
inet_pton4 (
    const char *src,
    uint8_t    *dst )
{
    static const char digits[] = "0123456789";

    int     saw_digit;
    int     octets;
    int     ch;
    uint8_t tmp[ INADDRSZ ];
    uint8_t *tp;

    saw_digit = 0;
    octets = 0;
    *( tp = tmp ) = 0;
    while ( ( ch = *src++ ) != '\0' ) {
        const char *pch;

        if ( ( pch = strchr( digits, ch )) != NULL ) {
            uint32_t new_word = *tp * 10 + ( pch - digits );

            if ( new_word > 255 )
                return( 0 );
            *tp = ( uint8_t ) new_word;
            if ( !saw_digit ) {
                if ( ++octets > 4 )
                    return( 0 );
                saw_digit = 1;
            }
        }
        else if ( ch == '.'  &&  saw_digit ) {
            if ( octets == 4 )
                return( 0 );
            *++tp = 0;
            saw_digit = 0;
        }
        else
            return( 0 );
    }
    if ( octets < 4 )
        return( 0 );
    /* bcopy(tmp, dst, INADDRSZ); */
    memcpy( dst, tmp, INADDRSZ );
    return( 1 );
}  /* inet_pton4 */


/* int
 * inet_pton6(src, dst)
 *  convert presentation level address to network order binary form.
 * return:
 *  1 if `src' is a valid [RFC1884 2.2] address, else 0.
 * notice:
 *  (1) does not touch `dst' unless it's returning 1.
 *  (2) :: in a full address is silently ignored.
 * credit:
 *  inspired by Mark Andrews.
 * author:
 *  Paul Vixie, 1996.
 */
static int
inet_pton6 (
    const char *src,
    uint8_t    *dst )
{
    static const char xdigits_l[] = "0123456789abcdef",
                      xdigits_u[] = "0123456789ABCDEF";

    uint8_t    tmp[ IN6ADDRSZ ];
    uint8_t    *tp;
    uint8_t    *endp;
    uint8_t    *colonp;
    const char *xdigits;
    const char *curtok;
    int        ch;
    int        saw_xdigit;
    uint32_t   val;

    memset(( tp = tmp ), 0, IN6ADDRSZ );
    endp = tp + IN6ADDRSZ;
    colonp = NULL;

    /* Leading :: requires some special handling. */
    if ( *src == ':' )
        if ( *++src != ':' )
            return( 0 );
    curtok = src;
    saw_xdigit = 0;
    val = 0;
    while ( ( ch = *src++ ) != '\0' ) {
        const char *pch;

        if ( ( pch = strchr(( xdigits = xdigits_l ), ch )) == NULL )
            pch = strchr(( xdigits = xdigits_u ), ch );
        if ( pch != NULL ) {
            val <<= 4;
            val |= ( pch - xdigits );
            if ( val > 0xffff )
                return( 0 );
            saw_xdigit = 1;
            continue;
        }
        if ( ch == ':' ) {
            curtok = src;
            if ( !saw_xdigit ) {
                if ( colonp )
                    return( 0 );
                colonp = tp;
                continue;
            }
            if ( tp + INT16SZ > endp )
                return( 0 );
            *tp++ = ( uint8_t )( val >> 8 );
            *tp++ = ( uint8_t ) val;
            saw_xdigit = 0;
            val = 0;
            continue;
        }
        if ( ch == '.'  &&  (( tp + INADDRSZ ) <= endp )  &&
                inet_pton4( curtok, tp ) > 0 ) {
            tp += INADDRSZ;
            saw_xdigit = 0;

            /* '\0' was seen by inet_pton4(). */
            break;
        }
        return( 0 );
    }
    if ( saw_xdigit ) {
        if ( tp + INT16SZ > endp )
            return( 0 );
        *tp++ = ( uint8_t )( val >> 8 );
        *tp++ = ( uint8_t ) val;
    }
    if ( colonp != NULL ) {
        /*
         * Since some memmove()'s erroneously fail to handle
         * overlapping regions, we'll do the shift by hand.
         */
        const int n = tp - colonp;
        int i;

        for ( i = 1; i <= n; i++ ) {
            endp[ - i ] = colonp[ n - i ];
            colonp[ n - i ] = 0;
        }
        tp = endp;
    }
    if ( tp != endp )
        return( 0 );
    /* bcopy(tmp, dst, IN6ADDRSZ); */
    memcpy( dst, tmp, IN6ADDRSZ );
    return( 1 );
}  /* inet_pton6 */


/* int
 * inet_pton(af, src, dst)
 *  convert from presentation format (which usually means ASCII printable)
 *  to network format (which is usually some kind of binary format).
 * return:
 *  1 if the address was valid for the specified address family
 *  0 if the address wasn't valid (`dst' is untouched in this case)
 *  -1 if some other error occurred (`dst' is untouched in this case, too)
 * author:
 *  Paul Vixie, 1996.
 */
int
_inet_pton (
    int        af,
    const char *src,
    void       *dst )
{
    switch ( af ) {
        case AF_INET:
            return( inet_pton4( src, dst ));
        case AF_INET6:
            return( inet_pton6( src, dst ));
        default:

#ifndef __GNUC__
            WSASetLastError( WSAEAFNOSUPPORT );
#endif
            return( -1 );
    }
    /* NOTREACHED */
}  /* inet_pton */


void
Inet_pton (
    int        family,
    const char *strptr,
    void       *addrptr )
{
    int n;

    if ( ( n = _inet_pton( family, strptr, addrptr )) < 0 )

        /* errno set */
        err_sys( "inet_pton error for %s", strptr );
    else if ( n == 0 )

        /* errno not set */
        err_quit( "inet_pton error for %s", strptr );
}  /* Inet_pton */
