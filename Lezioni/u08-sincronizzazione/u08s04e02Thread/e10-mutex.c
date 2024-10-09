/*
 *  mutex.c
 *
 *  Illustrates the use of mutex
 *  for mutual exclusion
 */
#include <pthread.h>
#include "errors.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *ME_thread (void *arg)
{
    int status;

    status = pthread_detach (pthread_self ());
    if (status != 0)
        err_abort (status, "Detach thread");
    for(;;) {
      status = pthread_mutex_lock (&mutex);
      if (status != 0) err_abort (status, "Lock mutex");
     
      printf("critical region of thread  %ld\n", pthread_self());

      status = pthread_mutex_unlock (&mutex);
      if (status != 0) err_abort (status, "Lock mutex"); 
      sleep(2);
//      sched_yield();    // rilascia volontariamente il processore
    }
    return NULL;
}

int main (int argc, char *argv[])
{
    int status;
 
    pthread_t thread;

    // setvbuf (stdout, NULL, _IONBF, 0);
    setbuf(stdout,0);           // no buffering for  stdout
 
    status = pthread_create (&thread, NULL, ME_thread, NULL);
    if (status != 0)
      err_abort (status, "Create print thread");

    status = pthread_create (&thread, NULL, ME_thread, NULL);
    if (status != 0)
      err_abort (status, "Create print thread");

    pthread_exit(NULL);
}
