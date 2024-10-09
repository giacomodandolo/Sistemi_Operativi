#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char ** argv){
  int n;
  char str[10];
  n = atoi (argv[1]);
  if (n>0) {
    printf ("%d\n", n);
    sprintf (str, "%s %d", argv[0], n-1);
    system (str);
  }
  printf("End.\n");
  return (1);
}

#if 0
./p2 3
3
2
1
End.
End.
End.
End.

./p2 4
4
3
2
1
End.
End.
End.
End.
End.
#endif
