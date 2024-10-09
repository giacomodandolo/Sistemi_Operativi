/*
 * Prova per verificare se:
 * - il figlio del figlio puo' svegliare il padre?!
 * - oppure ogni P attende solo i P figli e non i nipoti?!
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int
main (
  )
{
  pid_t pid, retPid;

  fprintf (stdout, "#Fa: PID=%d ... started\n", getpid());

  pid = fork();
  if (pid > 0) {

    // Father
    fprintf (stdout, "#Fb: PID=%d ... going to wait\n", getpid());
    //sleep (1);
    retPid = wait ((int *) 0);
    fprintf (stdout, "#Fc: PID=%d ... woken up, retPID=%d\n", getpid(), retPid);
    exit (0);

  } else {

    //Child
    pid = fork();
    if (pid > 0) {

      // Child
      fprintf (stdout, "  C1a: pid=%d ... going to sleep\n", getpid());
      // Force child to sleep, then is the father to wait first
      sleep (10);
      fprintf (stdout, "  C1a: pid=%d ... sleep ended going to wait\n", getpid());
      retPid = wait ((int *) 0);
      fprintf (stdout, "  C1b: PID=%d ... woken up, retPID=%d\n", getpid(), retPid);
      exit (0);

    } else {

      // Child of Child
      fprintf (stdout, "    C11a: PID=%d\n", getpid());
      sleep (1);
      fprintf (stdout, "    C11b: PID=%d ... going to exit\n", getpid());
      exit (0);

    }  
  }

  fprintf (stdout, "Never Reached\n");
  return (0);
}
