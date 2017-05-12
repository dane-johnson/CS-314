#include <stdio.h>
#include <stdlib.h>
#include "treenode.h"

void inorderPrint(struct treenode* head);

int main()
{
  node* head = NULL;

  insert(&head, 100);
  insert(&head, 75);
  insert(&head, 50);
  insert(&head, 125);
  insert(&head, 25);
  insert(&head, 150);

  inorderPrint(head);
  printf("\n");
  
  return 0;
}

void inorderPrint(node* head)
{
  if(head == NULL)
  {
    return;
  }
  else
  {
    inorderPrint(head -> left);
    printf("%d, ", head -> val);
    inorderPrint(head -> right);
  }
}
