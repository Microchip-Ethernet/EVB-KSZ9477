#ifndef _IOFUNC_H
#define _IOFUNC_H


ssize_t readline ( SOCKET fd, void *vptr, size_t maxlen );
ssize_t Readline ( SOCKET fd, void *ptr, size_t maxlen );
ssize_t readn ( SOCKET fd, void *vptr, size_t maxlen );
ssize_t Readn ( SOCKET fd, void *ptr, size_t maxlen );
ssize_t writen ( SOCKET fd, const void *vptr, size_t n );
void Writen ( SOCKET fd, void *ptr, size_t nbytes );

#endif
