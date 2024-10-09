/*
 * Illustrates the use of shell (!!!) pipes
 * Example: ls | try-pipe 
 */

#include <stdio.h>
#include <stdlib.h>

int
main (
  )
{
  char c;

  setbuf (stdout, 0);
  setbuf (stderr, 0);

  while (scanf ("%c", &c) == 1) {
    fprintf (stdout, "stdout:%c\n", c);
    fprintf (stderr, "stderr:%c\n", c);
  }

  return (0);
}
