#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
  char c;
  int n, fd[2];
  pid_t p;

  setbuf (stdout, 0);
  
  pipe(fd);
  fprintf (stdout, "Reading from %d, writing to %d\n", fd[0], fd[1]);

  p = fork();

  if (p > 0) {
    // Parent
    close (fd[0]);
    write (fd[1], "Hi Child!", 9);
    close (fd[1]);
    wait (NULL);
    fprintf (stdout, " - Parent ends\n");
  } else {
    // Child
    close (fd[1]);
    while ((n = read (fd[0], &c, sizeof (char))) > 0) {
      fprintf (stdout, "%c", c);
    }
    fprintf (stdout, " - Child ends\n");
  }
  
  return 0;
}
