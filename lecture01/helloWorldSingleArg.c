
/**
 * @file helloWorldSingleArg.c 
 *
 * Fork 3 threads from main. Now the function `hello()`
 * takes an requires an argument.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

/**
 * @brief Simple "`Hello world`" printer.
 *
 * I will fork the threads in a `for`-loop in the `main()`.
 *
 * @param index pointer to loop index which created the pthread
 *
 * @return some `void *` invalid pointer.
 */
    void *
hello ( void *index ) {
    printf( "Hello World from pthread %d!\n", *( (int *) index ) );
    
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

    /**
     * @attention You never know when a thread is exactly executed! In my case,
     * main thread prints before the other threads.
     *
     * Now it's interesting to see that the threads are not executed in order!
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
