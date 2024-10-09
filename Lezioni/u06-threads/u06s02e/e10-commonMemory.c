/*
 * With argc=1 the thread does not sleep
 * and it is faster than the main thread
 */

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int myglobal;

void *
thread_function (
  void *arg
  )
{
  int *argc = (int *) arg;
	
  int i, j;
  for (i=0; i<20; i++) {
    j = myglobal;
    j = j + 1;
    printf ("t");
    fflush (stdout);
    if (*argc > 1) sleep (1);
    myglobal = j;
  }
  printf ("(T:myglobal=%d)", myglobal);
  fflush (stdout);

  return NULL;
}

int
main (
  int argc,
  char ** argv
  )
{
  pthread_t mythread;
  int i;

  if (pthread_create (&mythread, NULL, thread_function, &argc)) {
    printf ("error creating thread.");
    abort ();
  }

  for (i=0; i<20; i++) {
    myglobal = myglobal + 1;
    printf ("m");
    fflush (stdout);
    sleep (1);
  }

  if (pthread_join (mythread, NULL)) {
    printf ("error joining thread.");
    abort ();
  }

  printf ("(M:myglobal=%d)", myglobal);
  fflush (stdout);
  printf ("\n");

  exit (0);
}
