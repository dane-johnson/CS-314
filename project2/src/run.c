#include "lab2-api.h"

typedef struct DB {
  char buffer[5];
  int bufferValCount;
} DB;

int main (int argc, char* argv[]) {
  uint32 handle;
  int i, num_p, num_c;
  DB *db;
  sem_t sem1, sem2, spage;
  lock_t lock;
  char handle_str[10], spage_str[10],  lock_str[10], sem1_str[10], sem2_str[10];
  db-> bufferValCount = 0;//initialize buffer counter to 0

  handle = shmget();//get handle to shared mem
  db = (DB*)shmat(handle);//get address of shared mem

  if(argc != 3)
  {
    exit();
  }

  num_p = dstrtol(argv[1],NULL,10);//get # of producers from args
  num_c = dstrtol(argv[2],NULL,10);//get # consumers from args
  // Printf("p:%d,c:%d",num_p, num_c);

  if(db == NULL) {
    Printf("Could not map shared page to a virtual page.");
    exit();
  }
 
  // for(i = 0; i < buffer_size; i++) {
  //  db->buffer[i] = shared_buffer[i];
  // }
  
  spage = sem_create(0);
  sem1 = sem_create(0);//^ when letter added, v when letter removed
  sem2 = sem_create(5);//v when letter added, ^ when letter removed
  lock = lock_create();
  
  ditoa(handle, handle_str);
  ditoa(spage, spage_str);
  ditoa(lock, lock_str);
  ditoa(sem1, sem1_str);
  ditoa(sem2, sem2_str);
  
  Printf("\nrun.c before procs are made\n");
  for(i = 0; i < num_p; i++){//make producer procs
    process_create("producer.dlx.obj", handle_str, spage_str, lock_str, sem1_str, sem2_str, NULL);
  }
  for(i = 0; i < num_c; i++) {//make consumer procs
    process_create("consumer.dlx.obj", handle_str, spage_str, lock_str, sem1_str, sem2_str, NULL);
  }
  Printf("\nrun.c after procs are made\n");
  sem_wait(spage);//wait for someone (a producer) to grab the page
  return 0;
}
