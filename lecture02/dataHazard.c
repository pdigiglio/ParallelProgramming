/**
 *
 *
 *           @name  dataHazard.c
 *          @brief  
 *
 *          Example usage:
 *          @code
 *          @endcode
 *
 *        @version  1.0
 *           @date  04/27/2015 (11:40:20 PM)
 *       @revision  none
 *       @compiler  gcc
 *
 *
 *         @author  P. Di Giglio (github.com/pdigiglio), <p.digiglio91@gmail.com>
 *        @company  
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>

#define SOME_HUGE_NUMBER 10000000


	void *
incrementUndefined ( void *p ) {

	/* 
	 * XXX this will directly access the variable itself!
	 * RACE CONDITION!
	 *
	 * This will result in an undefined behaviour due to the execution of threads!
	 */
	int *i = (int *) p;

	for ( unsigned int j = 0; j < SOME_HUGE_NUMBER; ++ j )
		( *i ) ++;

	return NULL;
}

	int
main () {

	pthread_t thread;
	int i = 0;

	/* split thread */
	pthread_create( &thread, NULL, &incrementUndefined, &i );

	for( int j = 0; j < SOME_HUGE_NUMBER; ++ j )
		i ++;

	pthread_join( thread, NULL );
	printf( "Value of i is %d\n", i );

	return 0;
}
