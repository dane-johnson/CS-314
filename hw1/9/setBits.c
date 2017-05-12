#include <stdio.h>
#include <stdlib.h>

int setBits(int x, int p, int n, int y);

int main()
{
  int x, y, z;
  x = 0xdeaddead;
  y = 0xbeefbeef;

  printf("Before set:\n");
  printf("x: %d %x\n", x, x);
  printf("y: %d %x\n", y, y);

  z = setBits(x, 16, 16, y);

  printf("After set:\n");
  printf("z: %d %x\n", z, z);
  
  return 0;
}

int setBits(int x, int p, int n, int y)
{
  unsigned int a, b;
  a = (unsigned int) x;
  b = (unsigned int) y;
  int np = ((sizeof(unsigned int) * 8) - n);
  unsigned int yBits = ((0xffffffff >> np) & b) << p;
  unsigned int xBits = (~((0xffffffff >> np) << p)) & a;
  return (xBits | yBits);
}
