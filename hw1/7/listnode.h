#ifndef LISTNODE_H
#define LISTNODE_H
typedef struct listnode
{
  int val;
  struct listnode* next;
  struct listnode* last;
} ll;
#endif
