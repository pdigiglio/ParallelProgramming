
/**
 * @file helloWorld3.c
 *
 * Fork 3 threads from main.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

/**
 * @brief Simple "`Hello world`" printer.
 *
 * @return some `void *` invalid pointer.
 */
    void *
hello () {
    printf( "Hello World from pthread!\n" );
    
    /* return some invalid pointer */
    return NULL;
}

    int
main () {

    size_t numThreads = 3;

    /* allocate threads */
    pthread_t *thread;
    thread = (pthread_t *) malloc( numThreads * sizeof( pthread_t ) );

    /* split new `pthread`s */
    for ( size_t t = 0; t < numThreads; ++ t ) {
        /* 
         * Here I am using pointer arithmetics: since thread is a pointer,
         * the address of the \f$i\f$-th item is passed to the function.
         */
        pthread_create ( thread + t, NULL, &hello, NULL );
    }

    /**
     * @attention You never know when a thread is exactly executed! In my case,
     * main thread prints before the other threads.
     */
    printf( "Hello World from main!\n" );

    /**
     * @attention Joining threads is _important!_ If you don't do it you could have
     * the program terminated before threads forked by main are executed. Sometimes,
     * in this case, you get printed `Hello World from thread!` twice or not printed
     * at all.
     */
    for ( size_t t = 0; t < numThreads; ++ t ) {
        pthread_join ( thread[t], NULL );
    }

    free( thread );

    return 0;
}
