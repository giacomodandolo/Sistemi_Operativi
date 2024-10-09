#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *PrintHello (
  )
{
  printf ("Hello World! I'm a thread!\n");
  sleep (2);
  fprintf (stdout, "Ending Thead\n");
  pthread_exit (NULL);
}

int main (
  int argc,
  char *argv[]
  )
{
  pthread_t tid;
  int rc;
  void *status;

  fprintf (stdout, "Creating 1 thread\n");
  rc = pthread_create (&tid, NULL, PrintHello, NULL);
  if (rc) {
    fprintf (stderr, "ERROR: pthread_create() core %d\n", rc);
    exit(-1);
  }

  if (argc > 1) {
    pthread_detach (tid);
  }

  sleep (1);
  rc = pthread_join (tid, &status);
  if (rc) {
    fprintf (stderr, "ERROR return code from pthread_join() is %d\n", rc);
    exit(-1);
  }

  fprintf (stdout, "Ending Main\n");
  pthread_exit (NULL);
}
