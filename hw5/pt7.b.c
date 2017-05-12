#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  FILE *file;
  int i, j;
  char a, b;

  switch(argc)
  {
  case 2:
    file = fopen(argv[1], "r+b");

    if(!file)
    {
      printf("File does not exist.\n");
      exit(1);
    }

    break;
  default:
    printf("Usage: %s file", argv[0]);
    exit(2);
  }


  //Get the index of the first and last bytes
  i = 0;
  fseek(file, 0, SEEK_END);
  j = ftell(file) - 1;
  while(i < j)
  {
    //Move to the beginning
    fseek(file, i, SEEK_SET);
    //Read a byte from the beginning
    fread(&a, sizeof(char), 1, file);
    //Move to the end
    fseek(file, j, SEEK_SET);
    //Read a byte from the end
    fread(&b, sizeof(char), 1, file);
    //Write the beginning byte to the end
    fseek(file, j, SEEK_SET);
    fwrite(&a, sizeof(char), 1, file);
    //Move to the beginning
    fseek(file, i, SEEK_SET);
    //Write the end byte to the beginning
    fwrite(&b, sizeof(char), 1, file);
    //Increment and decrement the counters
    i++;
    j--;
  }

  fclose(file);

  return 0;
}
