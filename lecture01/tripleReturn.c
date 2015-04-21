
/**
 * @file tripleReturn.c 
 *
 * Fork 3 threads from main. 
 *
 *
 * The function `triple()` takes an argument: a pointer which will
 * be casted into an `int *`. I will gather the return value from the 
 * thread.
 */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

/* for getpid() */
#include <sys/types.h>
#include <unistd.h>


/**
 * @brief Simple multiplication function.
 *
 * I will fork the threads in a `for`-loop in the `main()`.
 *
 * @param arg pointer to an IO-like `struct`.
 *
 * @return Pointer to the address of the result. 
 */
    void *
hello ( void *arg ) {

    /* this pointer won't be freed at the end of this scope! */
    int *result = (int *) malloc( sizeof(int) );

    /* multiplication */
    *result = 3 * *( (int *) arg );

    /* return pointer to result*/
    return (void *) result;
}

    int
main () {

    size_t numThreads = 3;

    /* allocate threads */
    pthread_t *thread;
    thread = (pthread_t *) malloc( numThreads * sizeof( pthread_t ) );

    /* array for thread-function arguments */
    int *threadArg;
    threadArg = (int *) malloc( numThreads * sizeof( int ) );

    /* split new `pthread`s */
    for ( size_t t = 0; t < numThreads; ++ t ) {
        /*
         * I use `threadArg[]` to pass argument to functions in threads.
         * Otherwise I would get unexpected behaviour in the function since
         * the index is modified within the loop.
         */
        threadArg[t] = t;

        /* 
         * Here I am using pointer arithmetics: since thread is a pointer,
         * the address of the \f$i\f$-th item is passed to the function.
         */
        pthread_create ( thread + t, NULL, &hello, &threadArg[t] );
    }

    /* Join threads and gather results */
    int *output;
    for ( size_t t = 0; t < numThreads; ++ t ) {
        /* now I have to gather the results */
        pthread_join ( thread[t], (void **)  &output );

        /* print the result of `triple()` calls */
        printf( "Triple of %d is %d\n", threadArg[t],*output );

        /* XXX why? it's not allocated! */
        free( output );
    }

    free( thread );

    return 0;
}
