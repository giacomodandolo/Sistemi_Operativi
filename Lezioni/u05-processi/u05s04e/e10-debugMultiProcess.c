/*
 * StQ 05.04.2011
 *
 * Demo: How to debug concurrent processes
 *
 *
 * 1 - inserire nel padre e nel figlio da debuggare una
 *     stampa del pid, una pause (per mandarlo in pausa in
 *     attesa di un segnale) e una linea specifica in cui
 *     incominciare il debug
 * 2 - compilare con opzione -g (no ottimizzazione)
 *     gcc -Wall -g -o <exe> <source> -lm
 * 3 - eseguire il pgrm nella prima finestra
 * 4 - eseguire gdb nella seconda finestra (in cui si debugga il
 *     padre). In tale debug effettuare:
 *     - file <exe>   per caricare la tabella dei simboli di quel programma
 *                    eseguibile
 *     - attach <pid> inserendo il pid del padre (che si vuole debuggare)
 *     - break <n>    con n = numero riga in cui si vuole incomiciare il debug
 *     - signal SIGUSR1 per svegliare il padre dalla sua pause
 * 5 - idem per il figli
 * 6 - padre e figlio si debuggano nelle due finestre
 *
 */

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>

void segnalePadre (int);
void segnaleFiglio (int);

int
child (
  int sec
  )
{
  fprintf(stdout,"CHILD%d: Inizio!\n", getpid());
  fprintf(stdout,"CHILD%d: Dormo!\n",getpid());
  sleep(sec);
  fprintf(stdout, "CHILD%d: Sono il figlio di %d. "
    "Non dormo ed ho finito!\n",getpid(),getppid());

  return 0;
}

int
father (
  )
{
  int status;
  fprintf(stdout, "PARENT: Sono il padre %d!\n", getpid());
  fprintf(stdout, "PARENT: Dormo!\n");
  sleep(1);
  fprintf(stdout, "PARENT: Ho smesso di dormire!\n");
  fprintf(stdout, "PARENT: Ho aspettato il figlio %d\n",wait(&status));
  fprintf(stdout, "PARENT: Ho finito!\n");

  return 0;
}

int
main (
  void
  )
{
  switch (fork()){
    case -1:
      fprintf (stderr, "Fork error.\n");
      return 1;
    case 0 :
      fprintf (stdout, "Figlio pid = %d\n", getpid());
      signal (SIGUSR1, segnaleFiglio);
      pause();
      fprintf (stdout, "Breakpoint line.\n");
      child(10);
      break;
    default:
      fprintf (stdout, "Padre pid = %d\n", getpid());
      signal(SIGUSR1, segnalePadre);
      pause();
      fprintf (stdout, "Breakpoint line.\n");
      father();
      break;
  }

  printf("Fine del processo %d\n",getpid());
  return 0;
}

void
segnaleFiglio (
  int signum
  )
{
  fprintf (stdout, "Figlio pid = %d\n", getpid());
}

void
segnalePadre (
  int signum
  )
{
  fprintf (stdout, "Padre pid = %d\n", getpid());
}
