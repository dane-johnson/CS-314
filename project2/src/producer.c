#include "lab2-api.h"

typedef struct DB {
  //make sure this struct matches in all files
  char buffer[5];
  int bufferValCount;
} DB;

int main(int argc, char *argv[]) {
  int i;
  DB *db;
  char hw[10] = {'h','e','l','l','o','w','o','r','l','d'};
  uint32 handle;
  sem_t spage, sem1, sem2;
  lock_t lock;


  handle = dstrtol(argv[1], NULL, 10);
  spage = dstrtol(argv[2], NULL, 10);
  lock = dstrtol(argv[3], NULL, 10);
  sem1 = dstrtol( argv[4], NULL, 10);//blocks when buffer is full
  sem2 = dstrtol(argv[5], NULL, 10);//block when buffer is empty

  db = (DB*)shmat(handle);

 if(sem_signal(spage)) {
  Printf("Could not map virtual address to memory");
  exit();
 }
 for(i = 0; i < 10; i++) {
   lock_acquire(lock);

   Printf("\nproducer for loop\n");
   
   db->buffer[db->bufferValCount] = hw[i];//add char to buffer
   db->bufferValCount++;//up buffer count
   lock_release(lock);

   sem_signal(sem1);
   sem_wait(sem2);

 }

  return 0;
}



