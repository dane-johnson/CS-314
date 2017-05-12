#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[])
{
  FILE *infile, *outfile;
  int i = 0;
  char c;
  
  switch(argc)
  {
  case 3:
    infile = fopen(argv[1], "rb");
    outfile = fopen(argv[2], "wb");

    if(!infile || !outfile)
    {
      printf("File does not exist.\n");
      exit(1);
    }

    break;
  default:
    printf("Usage: %s infile outfile\n", argv[0]);
    exit(2);
  }

  while(!fseek(infile, --i, SEEK_END))
  {
    //Return pointer to beginning
    fread((void*)&c, sizeof(char), 1, infile);
    fwrite((void*)&c, sizeof(char), 1, outfile);
  }

  fclose(infile);
  fclose(outfile);
}
      
