#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 3
#define DETACH_T 1

void *BusyWork(void *p) {
   int i, n, *np;
   double result=0.0;
   long int li;
   
   np = (int *) p;
   n = *np;
   li = n;
   
   for (i=0; i<n; i++)  {
     result = result + (double)random();
   }

   printf("Thread (%d-%ld) result = %e\n", n, li, result);

   pthread_exit ((void *) li);
}

int main (
  int argc,
  char *argv[]
  )
{
  pthread_t thread[NUM_THREADS];
  pthread_attr_t attr;
  int v[NUM_THREADS], rc, t;
  void *status;
  long int li;

#if DETACH_T
  /* Initialize and set thread detached attribute */
  pthread_attr_init (&attr);
  pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_JOINABLE);
#endif

  for (t=0; t<NUM_THREADS; t++) {
    printf ("Creating thread %d\n", t);
    v[t] = t;
#if DETACH_T
    rc = pthread_create (&thread[t], &attr, BusyWork, (void *) &v[t]); 
#else
    rc = pthread_create (&thread[t], NULL, BusyWork, (void *) &v[t]); 
#endif
    if (rc) {
      printf("ERROR; return code from pthread_create() is %d\n", rc);
       exit(-1);
    }
  }

#if 0
  /* Free attribute */
  pthread_attr_destroy (&attr);
#endif

  /* Wait for the threads */
  for (t=0; t<NUM_THREADS; t++) {
    rc = pthread_join (thread[t], &status);
    if (rc) {
      printf("ERROR return code from pthread_join() is %d\n", rc);
      exit(-1);
    }
    li = (long int) status;
    printf("Completed join with thread %d status= %ld\n", t, li);
  }

  pthread_exit(NULL);
}

