#include <stdio.h>
#include <stdlib.h>

void swapPtrs(int**, int**);

int main()
{
  int a, b, *a_ptr, *b_ptr;
  a = 1;
  b = 2;
  a_ptr = &a;
  b_ptr = &b;
  printf("Before the swap:\n");
  printf("*a_ptr = %d\n", *a_ptr);
  printf("*b_ptr = %d\n", *b_ptr);
  swapPtrs(&a_ptr, &b_ptr);
  printf("After the swap:\n");
  printf("*a_ptr = %d\n", *a_ptr);
  printf("*b_ptr = %d\n", *b_ptr);
  return 0;
}

void swapPtrs(int** a, int** b)
{
  int* temp;
  temp = *a;
  *a = *b;
  *b = temp;
}
