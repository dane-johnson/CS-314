#include <stdlib.h>
#include "treenode.h"

void insert(node **head, int val)
{
  if ( *head == NULL )
  {
    *head = (node*) malloc(sizeof(node*));
    (*head) -> right = NULL;
    (*head) -> left = NULL;
    (*head) -> val = val;
  }
  else
  {
    if( val >= (*head) -> val)
    {
      insert( &((*head) -> right), val);
    }
    else
    {
      insert( &((*head) -> left), val);
    }
  }
}
