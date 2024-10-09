#include <stdio.h>
#include <unistd.h>
#include "pthread.h"

int
main (
  void
  )
{
  pid_t pid;
  pthread_t tid;
 
  pid = getpid ();
  tid = pthread_self ();

  // Process Id: Non negative Integer
  // Thread Id : It is not an integer ... printing it out anyway

  printf("Process id     (PID) = %d\n",  pid);
  printf("Main thread id (TID) = %ld\n", tid);

  return (1);
}
