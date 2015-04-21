
/**
 * @file tripleStructIO.c 
 *
 * Fork 3 threads from main. 
 *
 *
 * The function `triple()` takes an argument: a pointer to a `struct`.
 * The structue will be modified wihthin the function. This will
 * allow to get some return value without actually returning.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

/* for getpid() */
#include <sys/types.h>
#include <unistd.h>

/**
 * @brief Structure to operate upon from `triple()`.
 *
 * This will allow to "get" values from `triple()` without actually `return`ing.
 */
struct pthreadArgsIO {
    int in;
    int out;
};

/**
 * @brief Simple multiplication function.
 *
 * I will fork the threads in a `for`-loop in the `main()`.
 *
 * @param arg pointer to an IO-like `struct`.
 *
 * @return some `void *` invalid pointer.
 */
    void *
hello ( void *arg ) {
    
    /* auxiliary variable */
    struct pthreadArgsIO *tmp = ( struct pthreadArgsIO * ) arg;

    /* multiplication */
    tmp->out = 3 * tmp->in;

    /* return some invalid pointer */
    return NULL;
}

    int
main () {

    size_t numThreads = 3;

    /* allocate threads */
    pthread_t *thread;
    thread = (pthread_t *) malloc( numThreads * sizeof( pthread_t ) );

    /* array for thread-function arguments */
    struct pthreadArgsIO *threadArg;
    threadArg = (struct pthreadArgsIO *) malloc( numThreads * sizeof( struct pthreadArgsIO ) );

    /* split new `pthread`s */
    for ( size_t t = 0; t < numThreads; ++ t ) {
        /*
         * I use `threadArg[]` to pass argument to functions in threads.
         * Otherwise I would get unexpected behaviour in the function since
         * the index is modified within the loop.
         */
        threadArg[t].in = t;

        /* 
         * Here I am using pointer arithmetics: since thread is a pointer,
         * the address of the \f$i\f$-th item is passed to the function.
         */
        pthread_create ( thread + t, NULL, &hello, &threadArg[t] );
    }

    /* Join threads and print results */
    for ( size_t t = 0; t < numThreads; ++ t ) {
        pthread_join ( thread[t], NULL );

        /* print the result of `triple()` calls */
        printf( "Triple of %d is %d\n",
                threadArg[t].in,
                threadArg[t].out );
    }

    free( thread );

    return 0;
}
