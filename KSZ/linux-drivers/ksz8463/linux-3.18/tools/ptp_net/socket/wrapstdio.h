#ifndef _WRAPSTDIO_H
#define _WRAPSTDIO_H


#include <stdio.h>


void Fclose ( FILE *fp );
char * Fgets ( char *ptr, int n, FILE *stream );
FILE * Fopen ( const char *filename, const char *mode );
void Fputs ( const char *ptr, FILE *stream );

#endif
