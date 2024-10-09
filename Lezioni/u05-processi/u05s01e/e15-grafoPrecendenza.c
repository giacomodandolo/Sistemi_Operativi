/* 
UNIX-process-synchronization.c
Illustrates:
	system call fork - wait
	and process state waiting
*/

#include <sys/types.h>
#include <sys/wait.h>

int num_arg;		// read-only global variable

main(int argc, char ** argv)
{
  pid_t           childpid;

  num_arg = argc;

  printf("parent - S1 - pid = %d\n", getpid());
  if ((childpid = fork()) == -1)
    perror("can't fork\n");
  if (childpid == 0) {
    printf("child: child pid = %d, parent pid = %d\n",
	   getpid(), getppid());
    P34();
    exit(0);
  } 
  else {
    if(num_arg > 1) sleep(15);		// precedence to child process
    printf("parent - S2 - pid = %d\n", getpid());
    printf("parent: child pid= %d, parent pid = %d\n",
	   childpid, getpid());
    printf("wait - P34 - \n");
    while (wait((int *) 0) != childpid);	/* wait for child */

    printf("parent - S5 - pid = %d\n", getpid());
    exit(0);
  }

}

P34()
{
  pid_t           pid4;

  printf("fork - P34 - \n");
  if ((pid4 = fork()) == -1)
    perror("can't fork\n");
  if (pid4 == 0) {
    printf("- S4 - pid = %d, parent pid = %d\n",
	   getpid(), getppid());
    exit(0);
  } else {
    if(num_arg > 1) sleep(15);		// precedence to child process
    printf("- S3 - pid = %d, parent pid = %d\n",
	   getpid(), getppid());
    while (wait((int *) 0) != pid4)	/* wait for child */
      ;
    printf("end of - P34 - \n");
    exit(0);
  }
}
