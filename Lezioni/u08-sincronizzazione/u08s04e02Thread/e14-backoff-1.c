/*
 * backoff.c
 *
 * Demonstrate deadlock avoidance using "mutex backoff".
 */
#include <pthread.h>
#include <sched.h>
#include "errors.h"

#define ITERATIONS 10

/*
 * Initialize a static array of 3 mutexes.
 */
pthread_mutex_t mutex[3] = {
    PTHREAD_MUTEX_INITIALIZER,
    PTHREAD_MUTEX_INITIALIZER,
    PTHREAD_MUTEX_INITIALIZER
    };
    

/*
 * This is a thread start routine that locks all mutexes in
 * order, to ensure a conflict with lock_reverse, which does the
 * opposite.
 */
void *lock_forward (void *arg)
{
    int i, iterate, backoffs;
    int status;

    for (iterate = 0; iterate < ITERATIONS; iterate++) {
        backoffs = 0;
        status = pthread_mutex_lock (&mutex[0]);
        for (i = 1; i < 3; i++) {  
          status = pthread_mutex_trylock (&mutex[i]);
          if (status == EBUSY) {
            backoffs++;
            printf("forward locker backing off at %d\n",i);
            for (; i >= 0; i--) 
              status = pthread_mutex_unlock (&mutex[i]);
          }
          else
            printf(" forward locker got %d\n", i);
        }
        sleep (1);           
     }
        /*
         * Report that we got 'em, and unlock to try again.
         */
        printf (
            "lock forward got all locks, %d backoffs\n", backoffs);
        pthread_mutex_unlock (&mutex[2]);
        pthread_mutex_unlock (&mutex[1]);
        pthread_mutex_unlock (&mutex[0]);
        sleep (1);
  
    return NULL;
}

/*
 * This is a thread start routine that locks all mutexes in
 * reverse order, to ensure a conflict with lock_forward, which
 * does the opposite.
 */
void *lock_backward (void *arg)
{
    int i, iterate, backoffs;
    int status;

    for (iterate = 0; iterate < ITERATIONS; iterate++) {
        backoffs = 0;
        status = pthread_mutex_lock (&mutex[2]);
        for (i = 1; i >= 0; i--) {  
          status = pthread_mutex_trylock (&mutex[i]);
          if (status == EBUSY) {
            backoffs++;
            printf("backward locker backing off at %d\n",i);
            for (; i <3; i++) 
              status = pthread_mutex_unlock (&mutex[i]);
          }
          else
            printf(" backward locker got %d\n", i);
        }
        sleep (1);           
        }
        /*
         * Report that we got 'em, and unlock to try again.
         */
        printf (
            "lock forward got all locks, %d backoffs\n", backoffs);
        pthread_mutex_unlock (&mutex[2]);
        pthread_mutex_unlock (&mutex[1]);
        pthread_mutex_unlock (&mutex[0]);
        sleep (1);
  
    return NULL;
}

int main (int argc, char *argv[])
{
    pthread_t forward, backward;
    int status;

    /*
     * If the second argument is absent, or zero, the two
     * threads run "at speed." On some systems, especially
     * uniprocessors, one thread may complete before the other
     * has a chance to run, and you won't see a deadlock or
     * backoffs. In that case, try running with the argument set
     * to a positive number to cause the threads to call
     * sched_yield() at each lock; or, to make it even more
     * obvious, set to a negative number to cause the threads to
     * call sleep(1) instead.
     */
    if (argc > 2)
        yield_flag = atoi (argv[2]);
    status = pthread_create (
        &forward, NULL, lock_forward, NULL);
    if (status != 0)
        err_abort (status, "Create forward");
    status = pthread_create (
        &backward, NULL, lock_backward, NULL);
    if (status != 0)
        err_abort (status, "Create backward");  
    pthread_exit (NULL);
}
