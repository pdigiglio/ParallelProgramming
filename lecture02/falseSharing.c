/**
 *
 *
 *           @name  falseSharing.c
 *          @brief  
 *
 *          Example usage:
 *          @code
 *          @endcode
 *
 *        @version  1.0
 *           @date  04/27/2015 (10:22:39 PM)
 *       @revision  none
 *       @compiler  gcc
 *
 *
 *         @author  P. Di Giglio (github.com/pdigiglio), <p.digiglio91@gmail.com>
 *        @company  
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/**
 * @def N_THREADS
 *
 * Number of threads.
 */
#define N_THREADS 2

/**
 * @def NUM
 */
#define SOME_HUGE_HUMBER 100000000

/**
 * @brief Structure for passing arguments.
 *
 * @attention There is a very nice trick!
 *
 * If `pthreadArgs` is too small, when allocating
 * it with `malloc()`, it's allocated subsequently. In this case, each `struct` shares a 
 * cache line with other data which are being modified by other threads: _the cache
 * fetching protocol forces the cache line to be reloaded!_
 *
 * That's why I added a dummy `char[64]` array: in order not to have shared cache line
 * for different records.
 */
typedef struct {
	unsigned int num;
	unsigned int i;

	// comment this to to see the performance difference
	unsigned char fill[64];
} pthreadArgs;

/**
 * @brief Just runs over one of parameters.
 */
	void *
increment ( void *pars ) {
	/* cast into the right type */
	pthreadArgs *p = (pthreadArgs *) pars;

	for ( int j = 0; j < p->num; ++ j ) {
		/* XXX directly increment the variable */
		p->i ++;
	}

	return NULL;
}

	int
main () {

	//----------------------------------------------------------------------------------
	//
	// ALLOCATE MEMORY
	//

	/* allocate pthreads */
	pthread_t *pthread = (pthread_t *) malloc( N_THREADS * sizeof( pthread_t ) );
	if ( ! pthread ) {
		fprintf( stderr, "pthread allocation failed!\n" );
		exit ( EXIT_FAILURE );
	}

	/* argument for function */
	pthreadArgs *args = (pthreadArgs *) malloc( N_THREADS * sizeof( pthreadArgs ) );
	if( ! args ) {
		fprintf( stderr, "pthreadArgs allocation failed!\n" );
		exit ( EXIT_FAILURE );
	}

	//
	//-----------------------------------------------------------------------------------
	
	for ( unsigned int j = 0; j < N_THREADS; ++ j ) {
		/* initialize counter to 0 */
		args[j].i   = 0;
		
		/* pthreads will have a different workload */
		args[j].num = ( j + 1 ) * SOME_HUGE_HUMBER;

		/* launch thread */
		pthread_create ( pthread + j, NULL, &increment, args + j );
	}

	/* join threads */
	for ( unsigned int j = 0; j < N_THREADS; ++ j ) {
		pthread_join( pthread[j], NULL );
		printf( "Value for thread %u is %u!\n", j, args[j].i );
	}

	free( pthread );
	free( args );

	return 0;
}
