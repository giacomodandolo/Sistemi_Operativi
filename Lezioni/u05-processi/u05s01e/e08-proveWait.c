#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int
main (int argc, char ** argv) {
  int rv;

  if (fork()) {
    // F aspetta un figlio
    printf ("\nFather (%d) 1\n", getpid()); fflush (stdout);
    wait (&rv);
    // Aspetta altri figli che non esistono, quindi le
    // wait non sono bloccanti e F va avanti se passa la prima
    printf ("\nFather (%d) 2\n", getpid()); fflush (stdout);
    wait (&rv);
    printf ("\nFather (%d) 3\n", getpid()); fflush (stdout);
    wait (&rv);
    printf ("\nFather (%d) 4\n", getpid()); fflush (stdout);
    wait (&rv);
    printf ("\nFather (%d) 5\n", getpid()); fflush (stdout);
  } else {
    if (fork ()) {
      // Figlio che e' atteso dal padre
      printf ("  S (%d) 1\n", getpid()); fflush (stdout);
      // Se sleep a lungo
      // SS fa exit e diventa zombie
      // F continua ad aspettare
      // sino a quando S fa wait e libera tutti
      //sleep (20);
      // Infatti se S va in pause F aspetta e SS e' zombie per sempre
      // se poi faccio un kill esterno a S tutti e tre terminano
      pause ();
      wait (&rv);
      printf ("  S (%d) 2\n", getpid()); fflush (stdout);
      exit (0);
    } else {
      // Figlio del figlio dorme e exit
      printf ("    SS (%d) 1\n", getpid()); fflush (stdout);
      sleep (5);
      printf ("    SS (%d) 2\n", getpid()); fflush (stdout);
      exit (0);
    }
  }

}
