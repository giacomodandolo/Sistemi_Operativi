#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *PrintHello (
  )
{
  pthread_t tid;

  sleep (2);
  tid = pthread_self ();
  fprintf (stdout, "Hello World: I'm a Thread!\n");
  fprintf (stdout, "Thread see thread id (TID, unsigned int?!) = %d\n",
    (unsigned int) tid);
   
  pthread_exit (NULL);
}

int main (
  int argc,
  char *argv[]
  )
{
  pthread_t tid;
  int rc;

  fprintf (stdout, "Creating 1 thread\n");
  rc = pthread_create (&tid, NULL, PrintHello, NULL);
  if (rc) {
    fprintf (stderr, "ERROR: Pthread_create() core %d\n", rc);
    exit(-1);
  }

  fprintf (stdout, "Main see thread id (TID, unsigned int?!)= %d\n",
    (unsigned int) tid);

  // Check this out: Enable one of the two
  if (argc > 1) {
    //exit (0);
    return (0);
  } else {
    pthread_exit (NULL);
  }
}
