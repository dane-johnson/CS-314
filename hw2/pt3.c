#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_THREADS 3

sem_t turnstile1, turnstile2, mutex;
int count = 0, cycles = 0;

int main()  {
  pthread_t thread1, thread2, thread3;
  void *f1();
  sem_init(&turnstile1, 0, 0);
  sem_init(&turnstile2, 0, 1);
  sem_init(&mutex, 0, 1);

  pthread_create(&thread1,NULL,f1,1);
  pthread_create(&thread2,NULL,f1,2);
  pthread_create(&thread3,NULL,f1,3);
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
  pthread_join(thread3, NULL);

  return 0;
}

void *f1(int x)
{
  while(cycles < NUM_THREADS)
  {
    //Rendezvous
    sem_wait(&mutex);
    count++;
    if(count == NUM_THREADS)
    {
      sem_wait(&turnstile2);
      sem_post(&turnstile1);
    }
    sem_post(&mutex);
    sem_wait(&turnstile1);


    //Critical point
    if(cycles + 1 == x)
    {
      printf("%d\n", x);
      cycles++;
    }
    
    sem_post(&turnstile1);
    //Rendezvous part 2
    sem_wait(&mutex);
    count--;
    if(count == 0)
    {
      sem_wait(&turnstile1);
      sem_post(&turnstile2);
    }
    sem_post(&mutex);
    sem_wait(&turnstile2);
    sem_post(&turnstile2);
  }
  pthread_exit(0);
}
