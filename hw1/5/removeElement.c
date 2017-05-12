#include <stdlib.h>
#include <stdio.h>
#include "listnode.h"

void removeNthElement(struct listnode* head, int N);

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
  printf("Removing element 3\n");
  removeNthElement(head, 3);
  printf("The list content is now:\n");
  printList(head);
  //We got this edge-case working, let's show off
  printf("Removing element 0\n");
  removeNthElement(head, 0);
  printf("The list content is now:\n");
  printList(head);
}

void removeNthElement(ll *head, int N)
{
  ll *curr, *last;
  curr = head;
  last = NULL;

  //Edge-case, N = 0
  if (N == 0)
  {
    //Copy all data from next to head, delete next
    curr = head -> next;
    head -> val = curr -> val;
    head -> next = curr -> next;
    free(curr);
    return;
  }

  for(int i = 0; i < N; i++)
  {
    last = curr;
    curr = curr -> next;
  }

  last -> next = curr -> next;
  free(curr);
}
