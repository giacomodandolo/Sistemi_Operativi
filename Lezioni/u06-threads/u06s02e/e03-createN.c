#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_THREADS 5

void *PrintHello (
  void *threadid
  ) 
{
  long int tid;

  tid = (long int) threadid;
  sleep (2 * tid);
  printf ("Hello World! It's me, thread #%ld!\n", tid);

  pthread_exit(NULL);
}

int main (
  int argc,
  char *argv[]
  )
{
  pthread_t threads[NUM_THREADS];
  long int rc, t;

  for (t=0; t<NUM_THREADS; t++) {
    fprintf (stdout, "In main: creating thread %ld\n", t);
    rc = pthread_create (&threads[t], NULL, PrintHello, (void *) t);
    if (rc) {
      fprintf (stderr, "ERROR: pthread_create() code %ld\n", rc);
      exit(-1);
    }
  }
  sleep (15);

  pthread_exit (NULL);
}
