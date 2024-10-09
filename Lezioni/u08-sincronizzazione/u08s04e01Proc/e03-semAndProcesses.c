/*
 *  StQ 01.12.2017
 *  Sem and Processes
 *  "Linux Threads does not currently support shared semaphores"
 *  !!!
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <pthread.h>

#define N 20

int main() {
  sem_t sem1, sem2;
  int i1, i2;

  setbuf (stdout, 0);

  sem_init (&sem1, 1, 1);
  sem_init (&sem2, 1, 0);

  if (fork()>0) {

    for (i1=0; i1<N; i1++) {
      sem_wait (&sem1);
      fprintf (stdout, "Father %d\n", i1);
      sem_post (&sem2);
    }

    wait ((int *) 0);
  } else{

    for (i2=0; i2<N; i2++) {
      sem_wait (&sem2);
      fprintf (stdout, "Child %d\n", i2);
      sem_post (&sem1);
    }

  }

  sem_destroy (&sem1);
  sem_destroy (&sem2);

  fprintf (stdout, "Bye\n");
  return 0;
}
