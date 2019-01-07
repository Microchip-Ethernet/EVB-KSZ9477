#ifndef _ERROR_H
#define _ERROR_H

/* -----------------------------------------------------------------------------

----------------------------------------------------------------------------- */


void SocketExit ( void );
void SocketInit ( int daemon );

void err_dump ( const char *fmt, ... );
void err_msg ( const char *fmt, ... );
void err_quit ( const char *fmt, ... );
void err_ret ( const char *fmt, ... );
void err_sys ( const char *fmt, ... );

int invalid_err(void);

#endif
