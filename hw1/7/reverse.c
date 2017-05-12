#include <stdio.h>
#include <stdlib.h>
#include "listnode.h"

void reverse(struct listnode** head);

int main()
{
  int nums[] = {8, 6, 7, 5, 3, 0, 9};
  ll* head = NULL;

  for (int i = 0; i < 7; i++)
  {
    push(&head, nums[i]);
  }

  printf("The list content is: \n");
  printList(head);
  reverse(&head);
  printf("The list content in reverse is: \n");
  printList(head);
  
  return 0;
}

void reverse(ll ** head)
{
  ll *curr;
  curr = *head;

  do
  {
    ll * temp;

    temp = curr -> next;
    curr -> next = curr -> last;
    curr -> last = temp;

    curr = temp;
  }
  while(curr != NULL);

  while((*head) -> last != NULL)
  {
    (*head) = (*head) -> last;
  }
}
