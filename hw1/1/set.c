#include <stdio.h>
#include <stdlib.h>

void set(int* a, int val);

int main()
{
  int a, b, *a_ptr;
  a=1;
  printf("Before set:\n");
  printf("%d\n", a);
  printf("Setting a to %d\n", 5);
  set(&a, 5);
  printf("After set:\n");
  printf("%d\n", a);
  return 0;
}

void set(int* a, int val)
{
  *a = val;
}
