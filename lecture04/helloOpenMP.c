/**
 * @file helloOpenMP.c
 *
 */

#include <omp.h>
#include <stdio.h>

	int
main () {

#pragma omp parallel
	{
		printf( "Hi asshole from thread %u\n", omp_get_thread_num() );

		if ( omp_get_thread_num() == 0 )
			printf( "Number of threads is: %u\n", omp_get_num_threads() );
	}

	return 0;
}
