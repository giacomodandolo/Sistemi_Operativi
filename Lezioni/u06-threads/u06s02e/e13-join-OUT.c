/* Creates two threads, 
   one printing 1000 "a"s, the other printing 1000 "b"s.
   Illustrates: thread creation,
                thread joining
                retcode and retvalue. 
*/

#include <stdio.h>
#include <unistd.h>
#include "pthread.h"

// global variable

int glo = 100;

static void *
process (void *arg)
{
  
  char *c = (char *) arg;	// cast the void argument to the real type
  
  int i;
  
  fprintf (stderr, "Starting thread %s, glo=%d\n", c, glo);
  for (i = 0; i < 1000; i++) 
    write (1, c, 1);
  return  c;
}

int
main (void)
{
  int retcode;
  pthread_t th_a, th_b;
  void *retval;
   
  retcode = pthread_create (&th_a, NULL, process, (void *) "a");
  if (retcode != 0)
    fprintf (stderr, "create a failed %d\n", retcode);
  retcode = pthread_create (&th_b, NULL, process, (void *) "b");
  if (retcode != 0)
    fprintf (stderr, "create b failed %d\n", retcode);
  retcode = pthread_join (th_a, &retval);
  
  fprintf(stderr, "retval : %c\n",   * (char *) retval);
  
  if (retcode != 0)
    fprintf (stderr, "join a failed %d\n", retcode);
  retcode = pthread_join (th_b, &retval);
  
  fprintf(stderr, "retval : %c\n",   * (char *) retval);
 
  if (retcode != 0)
    fprintf (stderr, "join b failed %d\n", retcode);
  return 0;
}
