#include <stdio.h>

void function()
{
  char buf[0];
  int *ret = buf;
  //(*ret) += 8;
}

int main()
{
  int x;
  x = 0;
  function();
  x = 1;
  x = x + 1;
  printf("%d\n", x);
}
