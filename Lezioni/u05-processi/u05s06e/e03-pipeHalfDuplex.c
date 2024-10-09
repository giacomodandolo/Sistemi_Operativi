/*
 *  Posso scrivere nelle due direzioni in un pipe (half-duplex)?
 *  Si alternativamente ...
 *  Se inserisco:
 *  - F sulla riga di comando il padre scrive delle F e il figlio le legge
 *  - C sulla riga di comando il figlio scrive delle C e il padre le legge
 *  - FC sulla riga di comando si alternano
 *  Faccio delle sleep per evitare R/W siano fatte della stesso processo
 *  in sequenza.
 *  Se tolgo i clico while(1) faccio solo un giro e il padre fa la wait per
 *  la exit del figlio.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int
main (
  int argc,
  char ** argv
  )
{
  int fd[2];
  char c;

  // no buffering
  setbuf (stdout, 0);

  // Create pipe
  pipe (fd);

  if (fork()!=0) {
    while (1) {
      if (strcmp (argv[1], "F")==0 || strcmp (argv[1], "FC")==0) {
        c = 'F';
        fprintf (stdout, "Father Write %c\n", c);
        write (fd[1], &c, 1);
      }
      sleep (2);
      if (strcmp (argv[1], "C")==0 || strcmp (argv[1], "FC")==0) {
        read (fd[0], &c, 1);
        fprintf (stdout, "Father Read %c\n", c);
      }
      sleep (2);
    }
    wait ((int *) 0);
  } else {
    while (1) {
      if (strcmp (argv[1], "F")==0 || strcmp (argv[1], "FC")==0) {
        read (fd[0], &c, 1);
        fprintf (stdout, "Child Read %c\n", c);
      }
      sleep (2);
      if (strcmp (argv[1], "C")==0 || strcmp (argv[1], "FC")==0) {
        c = 'C';
        fprintf (stdout, "Child Write %c\n", c);
        write (fd[1], &c, 1);
      }
      sleep (2);
    }
    exit (0);
  }

   return (0);
}
