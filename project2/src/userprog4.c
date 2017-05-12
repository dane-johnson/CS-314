#include "lab2-api.h"

int main(int argc, char *argv[])
{
  int i;
  int *count;
  uint32 handle;
  sem_t spage;
  lock_t lock;

  if(argc!=4)
  {
    Printf("Usage: ");
    Printf(argv[0]);
    Printf(" handle_str spage_str lock_str\n");
    exit();
  }
  handle = dstrtol(argv[1], NULL, 10);
  spage = dstrtol(argv[2], NULL, 10);
  lock = dstrtol(argv[3], NULL, 10);

  count = (int*)shmat(handle);
  if (count == NULL)
  {
    Printf("Could not map the virtual address to the memory, exiting...\n");
    exit();
  }

  if (sem_signal(spage))
  {
    Printf("Bad semaphore spage... Exiting!\n");
    exit();
  }

  //If this goes well, should print 1 -> number in order

  
  lock_acquire(&lock); //Get the lock
  (*count)++;  //Increment the count
  Printf("%d\n", *count); //Print the count
  lock_release(&lock); //Release the lock

  return 0;
}
  
