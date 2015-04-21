
/**
 * @file helloWorldManyArg.c 
 *
 * Fork 3 threads from main. Now the function `hello()`
 * takes an requires an argument: a pointer to a `struct` 
 * to pass more than argument.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

/* for getpid() */
#include <sys/types.h>
#include <unistd.h>

/**
 * @brief Structure to pass more than value to `hello()`.
 */
struct pthreadArgs {
    size_t threadID;
    size_t numThreads;
};

/**
 * @brief Simple "`Hello world`" printer.
 *
 * I will fork the threads in a `for`-loop in the `main()`.
 *
 * @param arg pointer to a `struct` to pass more than one argument.
 *
 * @return some `void *` invalid pointer.
 */
    void *
hello ( void *arg ) {
    /**
     * @attention If I split the `printf()` into multiple `printf()`s, I'll get
     * crap on the screan since other loops will interfer.
     */
//    printf( "Hello World from pthread %zd of %zd!\n",
//            ( (struct pthreadArgs *) arg )->threadID,
//            ( (struct pthreadArgs *) arg )->numThreads );
//
//    printf( "Here's some info:\n" );
//    printf( "\t > My PID\t%d\n", getpid() );
//    printf( "\t > My TID\t%d\n", (unsigned) pthread_self() );

    printf( "\nHello World from pthread %zd of %zd!\n"
            "Here's some info:\n"
            "\t > My PID\t%d\n"
            "\t > My TID\t%d\n",
            ( (struct pthreadArgs *) arg )->threadID,
            ( (struct pthreadArgs *) arg )->numThreads,
            getpid(), (unsigned) pthread_self() );
    
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
    struct pthreadArgs *threadArg;
    threadArg = (struct pthreadArgs *) malloc( numThreads * sizeof( struct pthreadArgs ) );

    /* split new `pthread`s */
    for ( size_t t = 0; t < numThreads; ++ t ) {
        /*
         * I use `threadArg[]` to pass argument to functions in threads.
         * Otherwise I would get unexpected behaviour in the function since
         * the index is modified within the loop.
         */
        threadArg[t].threadID = t;
        threadArg[t].numThreads = numThreads;

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
    printf( "\nHello World from main!\n" );

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
