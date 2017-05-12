#include <stdio.h>
#include <stdlib.h>

int rightRot(int x, int n);

int main()
{
  int x;
  x = 0xdeadbeef;

  printf("Before rot:\n");
  printf("x: %d %x\n", x, x);

  x = rightRot(x, 16);

  printf("After rot:\n");
  printf("x: %d %x\n", x, x);
  
  return 0;
}

int rightRot(int x, int n)
{
  unsigned int a;
  a = (unsigned int) x;
  int np = (sizeof(int) * 8) - n;
  unsigned int movedBits = (a << np);
  return ((a >> n) | movedBits);
}
