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
  case 4:
    trials = atoi(argv[3]);
    break;
  default:
    printf("Usage %s infile outfile trials\n", argv[0]);
    exit(1);
  }

  //Let's do some 2 file IO
  sprintf(command, "./reverse %s %s", argv[1], argv[2]);
  
  res = gettimeofday(&t1, NULL); assert(res==0);

  for(int i = 0; i < trials; i++)
  {
    system(command);
  }
  
  res = gettimeofday(&t2, NULL); assert(res==0);

  sum = nanosec(t2) - nanosec(t1);

  average = sum / trials;

  printf("Average time of execution (2 file reverse):  %10dns\n", sum);

  //Now let's look at 1 file IO
  sprintf(command, "./reverse2 %s", argv[2]);
  
  res = gettimeofday(&t1, NULL); assert(res==0);

  for(int i = 0; i < trials; i++)
  {
    system(command);
  }
  
  res = gettimeofday(&t2, NULL); assert(res==0);

  sum = nanosec(t2) - nanosec(t1);

  average = sum / trials;

  printf("Average time of execution (reverse inplace): %10dns\n", sum);
  
  return 0;
}
