#include <stdio.h>
#include <stdlib.h>
#include "pthread.h"
#include "semaphore.h"

sem_t *me, *me1, *w;
int nr = 0;

static void *
writer (void *a)
{
  int *i = (int *) a;

  sem_wait (me1);
  sem_wait (w);
  printf ("Thread n. %d writing\n", *i);
  sleep(15);
  sem_post (w);
  sem_post (me1);

  return NULL;
}


static void *
reader (void *a)
{
  int *i = (int *) a;

  sleep (1);
  sem_wait (me);
  nr++;
  if (nr == 1)
    sem_wait (w);
  sem_post (me);

  printf ("Thread n. %d reading\n", *i);
  sleep (1);
 
  sem_wait (me);
  nr--;
  if (nr == 0)
    sem_post (w);
  sem_post (me);

  return NULL;
}

int
main (void)
{
  pthread_t th_a, th_b;
  int i, *v;

  w = (sem_t *) malloc (sizeof (sem_t));
  me = (sem_t *) malloc (sizeof (sem_t));
  me1 = (sem_t *) malloc (sizeof (sem_t));
  sem_init (w, 0, 1);
  sem_init (me, 0, 1);
  sem_init (me1, 0, 1);

  setbuf(stdout,0);

  /* Create the threads */

  for (i = 0; i < 10; i++) {
    v = (int *) malloc (sizeof (int));
    *v = i;
    pthread_create (&th_a, NULL, reader, v);
  }

  for (i = 0; i < 10; i++) {
    v = (int *) malloc (sizeof (int));
    *v = i;
    pthread_create (&th_b, NULL, writer, v);
  }

  pthread_exit (0);

}
