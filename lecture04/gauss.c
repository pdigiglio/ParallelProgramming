/**
 * @file gauss.c
 *
 * @brief Sum up the first `N` natural numbers.
 */

#include <omp.h>

#include <stdlib.h>
#include <stdio.h>

#define N 10000000

/**
 * @brief Gauss' formula for sum of integer.
 *
 * I use this in order to prevent some overflow I may obtain in
 * evaluating \f$(N (N+1))/2\f$. In this case, assuming \f$N\f$ is
 * even, I evaluate \f$ (N/2)(N + 1)\f$ since it has smaller intermediate
 * results.
 */
	long long unsigned int
gaussSum ( unsigned long n ) {
	if ( n & 1 ) /* if n is odd */
		return n * ( ( n + 1 ) / 2 ); 
	else
		return ( n / 2 ) * ( n + 1 );

}
	int
main () {
	
	unsigned int *a = (unsigned int *) malloc( N * sizeof( unsigned int ) );
	for ( unsigned int j = 0; j < N; ++ j )
		a[j] = j + 1;

	long long unsigned int sum = 0;
	#pragma omp parallel for reduction ( +: sum )
	for ( unsigned int j = 0; j < N; ++ j ) {
//		printf( "Thread %u out of %u is processing index %u >> ", omp_get_thread_num(), omp_get_num_threads(), j );
		sum = sum + a[j];
//		printf( " sum = %u\n", sum );
	}

	printf( "Result according to openMP: %lu\n", sum );
	printf( "Result according to Gauss:  %lu\n", gaussSum( N ) );

	return 0;
}
