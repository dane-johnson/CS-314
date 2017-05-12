#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
  char c;
  char *memory;
  int i, page_size, fd, faults;
  
  if(argc < 2)
  {
    return -2;
  }
  faults = atoi(argv[1]);
  
  FILE *fp = popen("getconf PAGESIZE", "r");
  if(!fp)
  {
    return -1;
  }
  page_size;
  fscanf(fp, "%d", &page_size);
  pclose(fp);

  fd = open("/bin/emacs", O_RDONLY, 0);

  memory = (char*) mmap(NULL, sizeof(char) * (page_size * faults + 1), PROT_READ, MAP_SHARED, fd, 0);
  
  for (i = 0; i < faults; i++)
  {
    c = memory[i * page_size];
  }

  munmap(memory, sizeof(char) * (page_size * faults + 1));

  return 0;
}
