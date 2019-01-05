#ifndef	_wrap_thread_h
#define	_wrap_thread_h


#include <pthread.h>


typedef pthread_t*           Ppthread_t;
typedef pthread_cond_t*      Ppthread_cond_t;
typedef pthread_mutex_t*     Ppthread_mutex_t;
typedef pthread_mutexattr_t* Ppthread_mutexattr_t;


void Pthread_create ( Ppthread_t, const pthread_attr_t*,
    void *(*)( void* ), void* );
void Pthread_join ( pthread_t, void ** );
void Pthread_detach ( pthread_t );
void Pthread_kill ( pthread_t, int );

void Pthread_mutexattr_init ( Ppthread_mutexattr_t );
void Pthread_mutexattr_setpshared ( Ppthread_mutexattr_t, int );
void Pthread_mutex_init ( Ppthread_mutex_t, Ppthread_mutexattr_t );
void Pthread_mutex_lock ( Ppthread_mutex_t );
void Pthread_mutex_unlock ( Ppthread_mutex_t );

void Pthread_cond_broadcast ( Ppthread_cond_t );
void Pthread_cond_signal ( Ppthread_cond_t );
void Pthread_cond_wait ( Ppthread_cond_t, Ppthread_mutex_t );
void Pthread_cond_timedwait ( Ppthread_cond_t, Ppthread_mutex_t,
    const struct timespec* );

void Pthread_key_create ( pthread_key_t*, void (*)( void* ));
void Pthread_setspecific ( pthread_key_t, const void* );
void Pthread_once ( pthread_once_t*, void (*)( void ));

#endif
