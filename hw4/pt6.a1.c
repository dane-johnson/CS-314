#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
  if(argc < 2)
  {
    return -2;
  }
  int faults = atoi(argv[1]);
  
  FILE *fp = popen("getconf PAGESIZE", "r");
  if(!fp)
  {
    return -1;
  }
  int page_size;
  fscanf(fp, "%d", &page_size);
  pclose(fp);

  char *memory;
  memory = (char*) malloc( sizeof(char) * (page_size * faults + 1));

  for (int i = 0; i < faults; i++)
  {
    memory[i * page_size + 1] = 'D';
  }

  return 0;
}
