#include <stdio.h>
#include <stdlib.h>
#include "listnode.h"

int findNthElement(struct listnode *head, int N);

int main()
{
  int nums[] = {8, 6, 7, 5, 3, 0, 9};
  ll* head = NULL;
  for (int i = 0; i < 7; i++)
  {
    push(&head, nums[i]);
  }
  printf("The list content is:\n");
  printList(head);
  printf("Element 0 is %d\n", findNthElement(head, 0));
  printf("Element 3 is %d\n", findNthElement(head, 3));
  printf("Element 6 is %d\n", findNthElement(head, 6));
}

int findNthElement(ll *head, int N)
{
  ll *curr = head;
  for (int i = 0; i < N; i++)
  {
    curr = curr -> next;
  }
  return curr -> val;
}
