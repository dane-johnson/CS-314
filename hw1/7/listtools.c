#include <stdio.h>
#include <stdlib.h>
#include "listnode.h"

void push(ll** head, int val)
{
  ll* temp = (ll*) malloc (sizeof(ll*));
  temp -> val = val;
  temp -> next = *head;
  if (*head != NULL)
  { 
    (*head) -> last = temp;
  }
  *head = temp;
}

void printList(ll *head)
{
  while(head != NULL)
  {
    printf("%d->", head -> val);
    head = head -> next;
  }
  printf("NULL\n");
}

