#include <stdio.h>
#include <stdlib.h>
#include "listnode.h"

int findNthToLastElement(struct listnode* head, int N); 

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
  printf("The 3rd to last element is %d:", findNthToLastElement(head, 2));

  return 0;
}

int findNthToLastElement(ll *head, int N)
{
  int len;
  ll *curr;

  curr = head;
  len = 0;
  
  while (curr != NULL)
  {
    len++;
    curr = curr -> next;
  }

  for(int i = 1; i < len - N; i++)
  {
    head = head -> next;
  }

  return head -> val;
}
