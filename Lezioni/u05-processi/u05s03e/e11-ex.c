#include <stdio.h>
#include <unistd.h>

int main(){
  int n;
  n=0;
  while (n<3 && fork()){
    if (!fork())
      execlp ("echo", "n++", "n", NULL);
    n++;
    printf ("%d\n", n);
  }
  return (1);
} 

#if 0
./p3
1
2
3
4
5
n
n
n
n
n
n

se metto n<2
1
2
n
n
#endif
