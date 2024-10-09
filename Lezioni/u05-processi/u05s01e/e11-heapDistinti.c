/*
 * Father and child have two separate heaps?
 *
 * Each page that is allocated for the process (be it
 * a virtual memory page that has the stack on it or the heap)
 * is copied for the forked process to be able to access it.
 * Actually, it is not copied right at the start, it is set to
 * Copy-on-Write, meaning once one of the processes (parent or
 * child) try to modify a page it is copied so that they will
 * not harm one-another, and still have all the data from the
 * point of fork() accessible to them.
 * For example, the code pages, those the actual executable
 * was mapped to in memory, are usually read-only and thus are
 * reused among all the forked processes - they will not be copied
 * again, since no one writes there, only read, and so copy-on-write
 * will never be needed.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <ctype.h>
#include <string.h>

#define MAXBUF 1024
#define NUMCHILD 2

int main(int argc, char *argv[]){
  pid_t pid;
  char *common;
  
  /*Vorrei che la cella puntata da common
    venisse condivisa tra padre e figlio*/
  common = (char *) malloc (sizeof (char));
  *common = 'M';
  
  fprintf(stdout, "Caller  : mypid=%d\t *(common):%c\t common:%ld\n",
    getpid(), *common, (long int) common);
  fflush (stdout);

  pid=fork();
  if (pid == 0) {
    fprintf(stdout, "Child 1 : mypid=%d\t *(common):%c\t common:%ld\n",
      getpid(), *common, (long int) common);
    *common = 'C';
    fprintf(stdout, "Child 2 : mypid=%d\t *(common):%c\t common:%ld\n",
      getpid(), *common, (long int) common);
    fflush (stdout);
    exit (0);
  } else {
    /*Con questa sleep spero che la stampa seguente
    venga fatta in seguito alla scrittura del valore 5 su *(common) */
    sleep(2);
    fprintf(stdout, "Father 1: mypid=%d\t *(common):%c\t common:%ld\n",
      getpid(), *common, (long int) common);
    fflush (stdout);
    *common = 'F';
    fprintf(stdout, "Father 2: mypid=%d\t *(common):%c\t common:%ld\n",
      getpid(), *common, (long int) common);
    fflush (stdout);
  }

  return 0;
}
