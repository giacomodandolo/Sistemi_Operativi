/*
 *  Illustrates system call fork
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
  int i, n, *vet;
  int retValue;
  pid_t pid;
  n = atoi (argv[1]);
  vet = (int *) malloc (n * sizeof (int));
  if (vet==NULL) {
    fprintf (stderr, "Allocation Error.\n");
    exit (1);
  } 
  fprintf (stdout, "Input:\n");
  for (i=0; i<n; i++) {
    fprintf (stdout, "vet[%d]:", i);
    scanf ("%d", &vet[i]);
  }

  fprintf (stdout, "Output:\n");
  for (i=n-1; i>=0; i--) {
    fprintf (stdout, "vet[%d]:%d - ", i, vet[i]);
    pid = fork();
    if (pid>0) {
      pid = wait (&retValue);
      break;
    }
    fprintf (stdout, "Run PID=%d\n", getpid());
  }

  fprintf (stdout, "End PID=%d\n", getpid());

  exit (0);
}

