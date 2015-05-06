/**
 * @file conditionVariable.c
 *
 * @brief
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <pthread.h>

// for struct timespec
#include <time.h>

// for sleep()
#include <unistd.h>

// for ETIMEDOUT
#include <errno.h>

typedef struct {
	pthread_mutex_t mutex;
	pthread_cond_t  cond;
	bool            value;
} my_struct_t;

my_struct_t data = {
	PTHREAD_MUTEX_INITIALIZER,
	PTHREAD_COND_INITIALIZER,
	false
};

const double hibernation = 1.;

	void *
wait_thread( void * p ) {

	sleep( hibernation );

	// lock
	pthread_mutex_lock( &( data.mutex ) );
	// change value
	data.value = true;
	// send signal
	pthread_cond_signal( &(data.cond) );
	// unlock
	pthread_mutex_unlock( &( data.mutex ) );

	return NULL;
}

	int
main () {

	pthread_t thread;
	struct timespec timeout;
	pthread_create( &thread, NULL, &wait_thread, NULL );

	double shift = 2;
	timeout.tv_sec = time(NULL) + shift;

	// lock before checking for value 
	pthread_mutex_lock( &( data.mutex ) );

	while ( ! data.value ) {
		// this while-loop will run at most for `shift` seconds
		if ( pthread_cond_timedwait( &( data.cond ), &( data.mutex ), &timeout ) == ETIMEDOUT ) {
			fprintf( stderr, "Condition wait timed out!\n" );
			break;
		}
	}

	if( data.value ) {
		fprintf( stderr, "Condition was signaled!\n" );
	}

	// unlock mutex
	pthread_mutex_unlock( &( data.mutex ) );

	// join threads
	pthread_join ( thread, NULL );

	return 0;
}
