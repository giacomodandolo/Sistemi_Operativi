#include <stdio.h>
#include <stdlib.h>
#include "pthread.h"
#include "semaphore.h"

sem_t *me, *me1, *me2, *r, *w;
int nr = 0;
int nw = 0;

static void *
writer (void *a)
{
  int *i = (int *) a;

  sem_wait (me2);
  nw++;
  if (nw == 1)
    sem_wait (r);
  sem_post (me2);
  

  sem_wait (w);
  printf ("Thread n. %d writing\n", *i);
  sleep(5);
  sem_post (w);
  
  sem_wait (me2);
  nw--;
  if (nw == 0)
    sem_post (r);
  sem_post (me2);

  return NULL;
}


static void *
reader (void *a)
{
  int *i = (int *) a;

  sleep (2);
  sem_wait (me);
    sem_wait (r);
      sem_wait (me1);
        nr++;
        if (nr == 1)
          sem_wait (w);
      sem_post (me1);
    sem_post (r);
  sem_post (me);

  printf ("Thread n. %d reading\n", *i);
  sleep (1);
 
  sem_wait (me1);
  nr--;
  if (nr == 0)
    sem_post (w);
  sem_post (me1);

  return NULL;
}

int
main (void)
{
  pthread_t th_a, th_b;
  int i, *v;

  r = (sem_t *) malloc (sizeof (sem_t));
  w = (sem_t *) malloc (sizeof (sem_t));
  me = (sem_t *) malloc (sizeof (sem_t));
  me1 = (sem_t *) malloc (sizeof (sem_t));
  me2 = (sem_t *) malloc (sizeof (sem_t));
  sem_init (r, 0, 1);
  sem_init (w, 0, 1);
  sem_init (me, 0, 1);
  sem_init (me2, 0, 1);
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
    sleep(1);
    pthread_create (&th_b, NULL, writer, v);
  }

  pthread_exit (0);

}
