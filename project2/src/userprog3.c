#include "lab2-api.h"

int main(int argc, char* argv[])
{
  int number, i;
  int *count;
  uint32 handle;
  lock_t lock;
  sem_t spage;
  char handle_str[10], spage_str[10], lock_str[10];

  switch(argc)
  {
  case 2:
    number = dstrtol(argv[1], NULL, 10);
    Printf("Setting number = %d\n", number);
    break;
  default:
    Printf("Usage: ");
    Printf(argv[0]);
    Printf(" number\n");
    exit();
  }

  handle = shmget();
  count = (int *)shmat(handle);
  if(count == NULL)
  {
    Printf("Could not map the shared page to virtual address, exiting..\n");
    exit();
  }
  *count = 0;
  spage = sem_create(0);

  lock = lock_create();
  if(lock < 0)
  {
    Printf("Lock handle is bad, exiting...\n");
  }

  ditoa(handle, handle_str);
  ditoa(spage, spage_str);
  ditoa(lock, lock_str);

  for(i=0; i<number; i++)
  {
    process_create("userprog4.dlx.obj", handle_str, spage_str, lock_str, NULL);
  }

  sem_wait(spage);
  
  return 0;
}
