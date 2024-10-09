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

  while (scanf ("%c", &c) == 1) {
    printf ("%c", c);
  }

  return (0);
}
