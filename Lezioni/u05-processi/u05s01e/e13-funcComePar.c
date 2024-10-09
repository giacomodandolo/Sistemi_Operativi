#include <stdio.h>

int add1 (int, int);
int add2 (int, int);
int mul (int, int);
void f (int, int, int (*)(int, int));
 
int
main (
  )
{
  f (10, 20, add1);
  f (20, 30, add2);
  f (10, 30, mul);

  return (0);

}

int add1 (
  int a,
  int b
  )
{
  printf ("Add1: %d+%d=%d\n", a, b, a+b);
  return (a+b);
}

int add2 (
  int a,
  int b
  )
{
  printf ("Add2: %d+%d=%d\n", a, b, a+b);
  return (a+b);
}

int mul (
  int a,
  int b
  )
{
  printf ("Mul : %d*%d=%d\n", a, b, a*b);
  return (a*b);
}

void
f (
  int a,
  int b,
  int (*add)(int, int)
  )
{
  printf ("Chiamo add1/add2/mul: %d+%d=%d\n", a, b, add (a, b));
  return;
}
