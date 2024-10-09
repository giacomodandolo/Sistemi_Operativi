#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <semaphore.h>
#include <pthread.h>

#define L 100

struct threadData {
  pthread_t threadId;
  int id;
  FILE *fp;
  int line;
  int sum;
};

static void *readFile (void *);

sem_t sem;

int
main (
  int argc,
  char *argv[]
  )
{
  int i, nT, total, line;
  struct threadData *td;
  void *retval;
  FILE *fp;

  fprintf (stdout, "Command line: ");
  for (i=0; i<argc; i++) {
    fprintf (stdout, "%s ", argv[i]);
  }
  fprintf (stdout, "\n");

  nT = atoi (argv[1]);
  td = (struct threadData *) malloc (nT * sizeof (struct threadData));

  fp = fopen (argv[2], "r");
  if (fp==NULL) {
    fprintf (stderr, "Error Opening File.\n");
    exit (1);
  }

  sem_init (&sem, 0, 1);

  for (i=0; i<nT; i++) {
    td[i].id = i;
    td[i].fp = fp; // Same fp for all Threads
    td[i].line = 0;
    td[i].sum = 0;
    pthread_create (&(td[i].threadId), NULL, readFile, (void *) &td[i]);
  }

  total = 0;
  line = 0;
  for (i=0; i<nT; i++) {
    pthread_join (td[i].threadId, &retval);
    total += td[i].sum;
    line += td[i].line;
  }
  fprintf (stdout, "Total Sum: %d; #Line: %d\n", total, line);

  sem_destroy (&sem);
  fclose (fp);

  return (1);
}

static void *
readFile (
  void *arg
  )
{
  int n, retVal;

  struct threadData *td;

  td = (struct threadData *) arg;

  do {
    sem_wait (&sem);
    retVal = fscanf (td->fp, "%d", &n);
    sem_post (&sem);

    if (retVal!=EOF) {
      td->line++;
      td->sum += n;
      fprintf (stdout, "    Debug - Th: %d; Val: %d; Line: %d\n",
        td->id, n, td->line);
    }

    // Delay Threads ...
    sleep (1);
  } while (retVal!=EOF);

  fprintf (stdout, "  Thread: %d; Partial Sum: %d; #Line: %d\n",
    td->id, td->sum, td->line);

  pthread_exit ((void *) 1); 
}
