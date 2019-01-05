/*
 * pthreads wrapper functions.
 */

#include "wnp.h"
#include <errno.h>
#include <signal.h>
#include "wrapthread.h"


void Pthread_create (
    Ppthread_t            tid, 
    const pthread_attr_t* attr,
    void*                 ( *func )( void* ), 
    void*                 arg )
{
    int n;

    if ( ( n = pthread_create( tid, attr, func, arg )) == 0 )
        return;
    errno = n;
    err_sys( "pthread_create error" );
}  /* Pthread_create */


void Pthread_join ( 
    pthread_t tid, 
    void**    status )
{
    int n;

    if ( ( n = pthread_join( tid, status )) == 0 )
        return;
    errno = n;
    err_sys( "pthread_join error" );
}  /* Pthread_join */


void Pthread_detach (
    pthread_t tid )
{
    int n;

    if ( ( n = pthread_detach( tid )) == 0 )
        return;
    errno = n;
    err_sys( "pthread_detach error" );
}  /* Pthread_detach */


void Pthread_kill (
    pthread_t tid, 
    int       signo )
{
    int n;

    if ( ( n = pthread_kill( tid, signo )) == 0 )
        return;
    errno = n;
    err_sys( "pthread_kill error" );
}  /* Pthread_kill */


void Pthread_mutexattr_init (
    Ppthread_mutexattr_t attr )
{
    int n;

    if ( ( n = pthread_mutexattr_init( attr )) == 0 )
        return;
    errno = n;
    err_sys( "pthread_mutexattr_init error" );
}  /* Pthread_mutexattr_init */


#ifdef POSIX_THREAD_PROCESS_SHARED
void Pthread_mutexattr_setpshared (
    Ppthread_mutexattr_t attr, 
    int                  flag )
{
    int n;

    if ( ( n = pthread_mutexattr_setpshared( attr, flag )) == 0 )
        return;
    errno = n;
    err_sys( "pthread_mutexattr_setpshared error" );
}  /* Pthread_mutexattr_setshared */
#endif


void Pthread_mutex_init (
    Ppthread_mutex_t     mptr, 
    Ppthread_mutexattr_t attr )
{
    int n;

    if ( ( n = pthread_mutex_init( mptr, attr )) == 0 )
        return;
    errno = n;
    err_sys( "pthread_mutex_init error" );
}  /* Ptheread_mutex_init */


void Pthread_mutex_lock (
    Ppthread_mutex_t mptr )
{
    int n;

    if ( ( n = pthread_mutex_lock( mptr )) == 0 )
        return;
    errno = n;
    err_sys( "pthread_mutex_lock error" );
}  /* Pthread_mutex_lock */


void Pthread_mutex_unlock (
    Ppthread_mutex_t mptr )
{
    int n;

    if ( ( n = pthread_mutex_unlock( mptr )) == 0 )
        return;
    errno = n;
    err_sys( "pthread_mutex_unlock error" );
}  /* Pthread_mutex_unlock */


void Pthread_cond_broadcast (
    Ppthread_cond_t cptr )
{
    int n;

    if ( ( n = pthread_cond_broadcast( cptr )) == 0 )
        return;
    errno = n;
    err_sys( "pthread_cond_broadcast error" );
}  /* Pthread_cond_broadcast */


void Pthread_cond_signal (
    Ppthread_cond_t cptr )
{
    int n;

    if ( ( n = pthread_cond_signal( cptr )) == 0 )
        return;
    errno = n;
    err_sys( "pthread_cond_signal error" );
}  /* Pthread_cond_signal */


void Pthread_cond_wait (
    Ppthread_cond_t  cptr, 
    Ppthread_mutex_t mptr )
{
    int n;

    if ( ( n = pthread_cond_wait( cptr, mptr )) == 0 )
        return;
    errno = n;
    err_sys( "pthread_cond_wait error" );
}  /* Pthread_cond_wait */


void Pthread_cond_timedwait (
    Ppthread_cond_t        cptr, 
    Ppthread_mutex_t       mptr,
    const struct timespec* tsptr )
{
    int n;

    if ( ( n = pthread_cond_timedwait( cptr, mptr, tsptr )) == 0 )
        return;
    errno = n;
    err_sys( "pthread_cond_timedwait error" );
}  /* Pthread_cond_timedwait */


void Pthread_once (
    pthread_once_t* ptr, 
    void            ( *func )( void ))
{
    int n;

    if ( ( n = pthread_once( ptr, func )) == 0 )
        return;
    errno = n;
    err_sys( "pthread_once error" );
}  /* Pthread_once */


void Pthread_key_create (
    pthread_key_t* key, 
    void           ( *func )( void* ))
{
    int n;

    if ( ( n = pthread_key_create( key, func )) == 0 )
        return;
    errno = n;
    err_sys( "pthread_key_create error" );
}  /* Pthread_key_create */


void Pthread_setspecific (
    pthread_key_t key, 
    const void*   value )
{
    int n;

    if ( ( n = pthread_setspecific( key, value )) == 0 )
        return;
    errno = n;
    err_sys( "pthread_setspecific error" );
}  /* Pthread_setspecific */
