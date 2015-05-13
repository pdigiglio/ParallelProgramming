/**
 * @file schedulingOpenMP.c
 *
 */

#include <omp.h>

#include <unistd.h>
#include <string.h>

#include <stdio.h>
#include <stdlib.h>

char *coloredDigit[] = {
	"\e[1;30;1m0",
	"\e[1;31;1m1",
	"\e[1;32;1m2",
	"\e[1;33;1m3",
	"\e[1;34;1m4",
	"\e[1;35;1m5",
	"\e[1;36;1m6",
	"\e[1;37;1m7"
};

	int
main () {

	const unsigned int xSize = 80;
	const unsigned int ySize = 40;

	const size_t strLen = strlen( coloredDigit[0] );
	char *string2D = malloc( xSize * ySize * strLen + ySize );
	if ( string2D == NULL ) {
		fprintf( stderr, "string2D allocation failed\n" );
		exit( EXIT_FAILURE );
	}

#pragma omp parallel for schedule(runtime)
	for ( unsigned int i = 0; i < ySize; ++ i ) {
		for ( unsigned int j = 0; j < xSize; ++ j ) {
			memcpy( string2D + ( i * xSize * strLen + i ) + ( j * strLen),
					coloredDigit[ omp_get_thread_num() % omp_get_num_threads()],
					strLen );
		} 
	}
	
	unsigned int row;
	for ( unsigned int i = 0; i < ySize; ++ i ) {
		row = i * xSize * strLen + i;
		printf( "%s\n", string2D + row );
	}

	// reset color
	printf( "\033[0m" );

	return 0;
}

