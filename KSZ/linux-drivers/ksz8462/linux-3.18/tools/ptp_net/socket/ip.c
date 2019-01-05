#include "wnp.h"


u_short in_cksum (
    u_short* addr,
    int      len )
{
    int      nleft = len;
    int      sum = 0;
    u_short* w = addr;
    u_short  answer = 0;

    while ( nleft > 1 ) {
        sum += *w++;
        nleft -= 2;
    }

    if ( nleft == 1 ) {
        *( u_char* )( &answer ) = *( u_char* ) w;
        sum += answer;
    }

    sum = ( sum >> 16 ) + ( sum & 0xffff );
    sum += ( sum >> 16 );
    answer = ( u_short ) ~sum;
    return( answer );
}  // in_cksum


