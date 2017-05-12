#include "lab2-api.h"

typedef struct DB {
  //make sure this struct matches in all files
  char buffer[5];
  int bufferValCount;
} DB;

int main(int argc, char *argv[]) {
  int i;
  DB *db;
  char print;
  uint32 handle;
  sem_t spage, sem1, sem2;
  lock_t lock;


  handle = dstrtol(argv[1], NULL, 10);
  spage = dstrtol(argv[2], NULL, 10);
  lock = dstrtol(argv[3], NULL, 10);
  sem1 = dstrtol( argv[4], NULL, 10);//blocks when buffer is full
  sem2 = dstrtol(argv[5], NULL, 10);//block when buffer is empty

  db = (DB*)shmat(handle);

  //Took this out because we want to ensure that a producer starts first
  //  if(sem_signal(spage)) {
  // Printf("Could not map virtual address to memory");
  // exit();
  // }
while(db->bufferValCount != 0 || sem1 != 0 || sem2 != 5) {
  lock_acquire(lock);
  
  Printf("\nconsumer while loop\n");
  Printf("%c", db->buffer[db->bufferValCount-1]);//print a char
  db->buffer[db->bufferValCount-1] = NULL;//remove printed char from buffer
  db->bufferValCount--;//decrement the buffer count

  lock_release(lock);
  
  sem_signal(sem2);
  sem_wait(sem1);
  
  }

 Printf("\nconsumer done\n");
return 0;
}
