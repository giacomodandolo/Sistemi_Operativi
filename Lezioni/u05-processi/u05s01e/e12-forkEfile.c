#include <stdio.h>
#include <unistd.h>

#define NAME "in.txt"

int
main (
  )
{
  int pid, n;
  FILE *fp;

#if 0

  /*
   * Fork and then oper file
   * fp are independent
   */
   
  setbuf (stdout, 0);

  pid = fork();

  if (pid==0) {
    /* Child */
    fp = fopen (NAME, "r");
    while (fscanf (fp, "%d", &n) != EOF) {
      printf ("Child reading %d\n", n);
      sleep (1);
    }
    fclose (fp);
  } else {
    /* Father */
    fp = fopen (NAME, "r");
    while (fscanf (fp, "%d", &n) != EOF) {
      printf ("Father reading %d\n", n);
      //sleep (1);
    }
    fclose (fp);
  }

#else

  /*
   * Oper file and then fork
   * fp are dependent
   */

  setbuf (stdout, 0);

  fp = fopen (NAME, "r");

  pid = fork();

  if (pid==0) {
    /* Child */
    printf ("Child running ...\n");
    while (fscanf (fp, "%d", &n) != EOF) {
      printf ("Child reading %d\n", n);
      sleep (1);
    }
  } else {
    /* Father */
    printf ("Father running ...\n");
    while (fscanf (fp, "%d", &n) != EOF) {
      printf ("Father reading %d\n", n);
      sleep (1);
    }
  }

  fclose (fp);

#endif

  return (0);
}
