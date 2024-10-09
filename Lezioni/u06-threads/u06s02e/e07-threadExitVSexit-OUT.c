#include <pthread.h>
#include "errors.h"

int one=1, two=2;
   
static void *
print_thread (
  void *arg
  )
{
  int *t = (int *) arg;
  int status, i;

  // parent is not joining 
  status = pthread_detach (pthread_self ());

  if (status != 0)
    err_abort (status, "Detach thread");
    
  for (i=0; i<5; i++) {
    sleep (1);
    system ("date");
    printf ("Active thread: %d  i : %d\n", *t, i);
    printf ("Global Variables %d, %d\n", one, two);
  }

// exit(0);
  return NULL;
}


int main (
  int argc,
  char *argv[]
) {
   int status;
   pthread_t thread;

   status = pthread_create (&thread, NULL, print_thread, &one);
   if (status != 0)
     err_abort (status, "Create print thread 1");
  
   status = pthread_create (&thread, NULL, print_thread, &two);
   if (status != 0) {
     err_abort (status, "Create print thread 2");
   }

   if (argc > 1) {
      sleep(4);
      pthread_exit (NULL);
      // ends the main thread, but the two created threads continue running
   }  else {
     sleep(3);
     // after 3 seconds ends all threads
     exit(0);
   }
}










