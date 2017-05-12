#include <stdio.h>
#include <pthread.h>

typedef int semaphore;

pthread_mutex_t mutex;
pthread_cond_t cond;

void *thread_a();
void *thread_b();

void sem_init(semaphore *sem, int initial);
void sem_wait(semaphore *sem);
void sem_signal(semaphore *sem);

semaphore aArrived, bArrived;

int main()
{
  pthread_t a, b;

  //init semaphores
  sem_init(&aArrived, 0);
  sem_init(&bArrived, 0);
  
  pthread_create(&a, NULL, thread_a, NULL);
  pthread_create(&b, NULL, thread_b, NULL);
  pthread_join(a, NULL);
  pthread_join(b, NULL);
  
  return 0;
}

void *thread_a()
{
  printf("a1\n");
  sem_signal(&aArrived);
  sem_wait(&bArrived);
  printf("a2\n");
}

void *thread_b()
{
  printf("b1\n");
  sem_signal(&bArrived);
  sem_wait(&aArrived);
  printf("b2\n");
}

void sem_init(semaphore *sem, int initial)
{
  *sem = initial;
}

void sem_wait(semaphore *sem)
{
  pthread_mutex_lock(&mutex);
  while(*sem <= 0)
  {
    pthread_cond_wait(&cond, &mutex);
  }
  *sem = *sem - 1;
  pthread_mutex_unlock(&mutex);
}

void sem_signal(semaphore *sem)
{
  pthread_mutex_lock(&mutex);
  *sem = *sem + 1;
  pthread_mutex_unlock(&mutex);
  pthread_cond_signal(&cond);
}
