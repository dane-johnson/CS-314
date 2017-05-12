#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <assert.h>

long nanosec(struct timeval t)
{
  return ((t.tv_sec * 1000000 + t.tv_usec) * 1000);
}

int main(int argc, char *argv[])
{
  int res, trials;
  long sum, average;
  struct timeval t1, t2;
  char command[10];

  switch(argc)
  {
  case 2:
    trials = atoi(argv[1]);
    break;
  default:
    printf("Usage %s trials\n", argv[0]);
    exit(1);
  }

  //Let's look at some minor page faults
  sprintf(command, "./a1 %d", trials);
  
  res = gettimeofday(&t1, NULL); assert(res==0);
  
  system(command);
  
  res = gettimeofday(&t2, NULL); assert(res==0);

  sum = nanosec(t2) - nanosec(t1);

  average = sum / trials;

  printf("Average time of execution (minor page faults): %dns\n", sum);

  //Now let's look at some major page faults
  sprintf(command, "./a2 %d", trials);
  
  res = gettimeofday(&t1, NULL); assert(res==0);
  
  system(command);
  
  res = gettimeofday(&t2, NULL); assert(res==0);

  sum = nanosec(t2) - nanosec(t1);

  average = sum / trials;

  printf("Average time of execution (major page faults): %dns\n", sum);
  
  return 0;
}
