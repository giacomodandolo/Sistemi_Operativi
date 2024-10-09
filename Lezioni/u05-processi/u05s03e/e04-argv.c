/*
 * Stampa argv
 * Uso con exec per vedere nome dell’eseguibile
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main (
  int argc,
  char **argv
  )
{
  int i;

  printf("argc = %d\n", argc);

  for (i=0; i<argc; i++) {
    fprintf (stdout,  "%s \n", argv[i]);
    sleep (2);
  }

  exit (0);
}
