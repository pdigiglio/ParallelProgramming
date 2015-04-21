/**
 * @file helloWorld.c
 *
 */

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

    /* create a new thread */
    pthread_t thread;
    pthread_create ( &thread, NULL, &hello, NULL );

    printf( "Hello World from main!\n" );

    /**
     * @attention Joining threads is _important!_ If you don't do it you could have
     * the program terminated before threads forked by main are executed. Sometimes,
     * in this case, you get printed `Hello World from thread!` twice or not printed
     * at all.
     */
    pthread_join ( thread, NULL );

    return 0;
}
