#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

typedef struct Bin
{
  int no;
  int count;
  struct Bin *next;
} Bin;


void init(Bin *head);
void insert(Bin *head, int size, int bin_size);
void parsedir(Bin *head, DIR *dir, char *dirname, int bin_size);
void printbins(Bin head, int bin_size);

int main(int argc, char *argv[])
{
  DIR *root;
  char *dirname;
  int bin_size;
  Bin head;
  
  switch (argc)
  {
  case 3:
    bin_size = atoi(argv[2]);
    dirname = argv[1];
    root = opendir(dirname);
    
    if(root == NULL)
    {
      printf("Error locating directory.\n");
      exit(1);
    }
    
    break;
  default:
    printf("Usage: %s dir bin_size.\n", argv[0]);
    exit(2);
  }
  
  init(&head);

  parsedir(&head, root, dirname, bin_size);

  printbins(head, bin_size);

  return 0;
}

void insert(Bin *head, int size, int bin_size)
{
  int seek;
  Bin *curr, *next;

  seek = size / bin_size;
  if(seek == 0)
  {
    //It is in the first bin, edge case.
    (head->count)++;
  }
  else
  {
    curr = head;
    next = head->next;
    //While we're not at the end
    while(next != NULL)
    {
      if(next->no == seek)
      {
	//We've found the bin, increment
	(next->count)++;
	return;
      }
      else if(next->no > seek)
      {
	//The next bin is too large, we need to insert one in between
	Bin *new = (Bin*)malloc(sizeof(Bin));
	new->no = seek;
	new->count = 1;
	new->next = next;
	curr->next = new;
	return;
      }
      else
      {
	//Keep looking
	next = next->next;
	curr = curr->next;
      }
    }
    //We're at the end of the list, make a new bin
    Bin *new = (Bin*)malloc(sizeof(Bin));
    new->no = seek;
    new->count = 1;
    curr->next = new;
  }
}

void init(Bin *head)
{
  head->no = 0;
  head->count = 0;
  head->next = NULL;
}

void parsedir(Bin *head, DIR *dir, char *dirname, int bin_size)
{
  struct dirent *next;
  struct stat stats;
  char str[1024];

  if (dir == NULL) return;
  
  next = readdir(dir);
  while(next != NULL)
  {
    switch(next->d_type)
    {
    case DT_REG:
      sprintf(str, "%s/%s", dirname, next->d_name);
      lstat(str, &stats);
      insert(head, stats.st_size, bin_size);
      break;
    case DT_DIR:
      sprintf(str, "%s/%s", dirname, next->d_name);
      parsedir(head, opendir(str), str, bin_size);
      break;
    }

    next = readdir(dir);
  }
}

void printbins(Bin head, int bin_size)
{
  Bin *curr;
  int no = 0;
  
  printf("%d-%d:", 0, bin_size - 1);
  for(int i = 0; i < head.count; i++)
  {
    printf("*");
  }
  printf("\n");

  curr = head.next;
  
  while(curr != NULL)
  {
    //Fill in spaces for empty bins
    for(int i = no + 1; i < curr->no; i++)
    {
      printf("%d-%d:\n", i * bin_size, (i + 1) * bin_size - 1);
    }
    printf("%d-%d:", curr->no * bin_size, (curr->no + 1) * bin_size - 1);
    for(int i = 0; i < curr->count; i++)
    {
      printf("*");
    }
    printf("\n");
    no = curr->no;
    curr = curr->next;
  }
}
