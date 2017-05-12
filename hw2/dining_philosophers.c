#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define N        5
#define LEFT     ( i + N - 1) % N
#define RIGHT    ( i + 1) % 1
#define THINKING 0
#define HUNGRY   1
#define EATING   2
#define MEALS    2

int state[N];

pthread_t threads[N];

sem_t mutex;
sem_t s[N];

void *philosopher(int*);
void take_forks(int);
void put_forks(int);
void test(int);
void think(int);
void eat(int);

int main()
{
  sem_init(&mutex, 0, 1);
  for(int i = 0; i < N; i++)
  {
    sem_init(s + i, 0, 1);
  }
  for(int i = 0; i < N; i++)
  {
    pthread_create(threads + i, NULL, philosopher, &i);
  }
  for(int i = 0; i < N; i++)
  {
    pthread_join(threads[i], NULL);
  }
  return 0;
}

void *philosopher(int *i)
{
  for(int j = 0; j < MEALS; j++)
  {
    think(*i);
    take_forks(*i);
    eat(*i);
    put_forks(*i);
  }

  pthread_exit(0);
}

void take_forks(int i)
{
  sem_wait(&mutex);
  state[i] = HUNGRY;
  test(i);
  sem_post(&mutex);
  sem_wait(s + i);
}

void put_forks(int i)
{
  sem_wait(&mutex);
  state[i] = THINKING;
  test(RIGHT);
  test(LEFT);
  sem_post(&mutex);
}

void test(int i)
{
  if(state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING)
  {
    state[i] = EATING;
    sem_post(s + i);
  }
}

void think(int i)
{
  printf("Philosopher %d: Hmm...\n", i);
}

void eat(int i)
{
  printf("Philosopher %d: Nom\n", i);
}
