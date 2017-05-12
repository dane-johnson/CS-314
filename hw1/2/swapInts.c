#include <stdio.h>
#include <stdlib.h>

void swapInts(int* a, int* b);

int main()
{
  int a, b;
  a = 1;
  b = 2;
  printf("Before Swap:\n");
  printf("a:%d\n", a);
  printf("b:%d\n", b);
  swapInts(&a, &b);
  printf("After Swap:\n");
  printf("a:%d\n", a);
  printf("b:%d\n", b);
  return 0;
}

void swapInts(int* a, int* b)
{
  *a ^= *b;
  *b ^= *a;
  *a ^= *b;
}
