#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

typedef struct gunk{
  char name[256];
  int size;
} gunk;

void listnames(const char*);
void addtoarchive(const char*, const char*);
void extractfromarchive(const char*, const char*);
void usage(const char*);

int main(int argc, char *argv[])
{
  switch(argc)
  {
  case 3:
    if (strcmp(argv[1], "-l") == 0)
    {
      listnames(strdup(argv[2]));
    }
    else
    {
      usage(strdup(argv[0]));
    }
    break;
  case 4:
    if (strcmp(argv[1], "-a") == 0)
    {
      addtoarchive(strdup(argv[2]), strdup(argv[3]));
    }
    else if (strcmp(argv[1], "-e") == 0)
    {
      extractfromarchive(strdup(argv[2]), strdup(argv[3]));
    }
    else
    {
      usage(strdup(argv[0]));
    }
    break;
  default:
    usage(strdup(argv[0]));
  }
}

void usage(const char *program)
{
  printf("Usage: %s [option] <archivename> [file]\n", program);
  exit(1);
}

void listnames(const char *archivename)
{
  FILE *ap;
  gunk g;
  
  ap = fopen(archivename, "rb");
  if(!ap)
  {
    printf("Archive %s does not exist.\n", archivename);
    exit(2);
  }
  while(fread((void*) &g, sizeof(gunk), 1, ap))
  {
    printf("%s\n", g.name);
    fseek(ap, sizeof(char) * g.size, SEEK_CUR);
  }
  fclose(ap);
}

void addtoarchive(const char *archivename, const char *filename)
{
  FILE *ap, *fp;
  gunk g;
  char *c;
  struct stat buf;

  lstat(filename, &buf);
  
  fp = fopen(filename, "rb");
  
  if(!fp)
  {
    printf("File %s does not exist.\n", filename);
    exit(3);
  }
  ap = fopen(archivename, "ab");

  strcpy(g.name, filename);
  g.size = buf.st_size;
  fwrite((void*) &g, sizeof(gunk), 1, ap);

  c = (char*)calloc(g.size, sizeof(char));
  fread((void*) c, sizeof(char), g.size, fp);
  fwrite((void*) c, sizeof(char), g.size, ap);
  free(c);

  fclose(ap);
  fclose(fp);
}

void extractfromarchive(const char *archivename, const char *filename)
{
  char found = 0;
  FILE *ap, *fp;
  gunk g;
  char *c;

  ap = fopen(archivename, "rb");

  if(!ap)
  {
    printf("Archive %s does not exist.\n", archivename);
    exit(2);
  }

  while(fread((void*)&g, sizeof(gunk), 1, ap))
  {
    if (strcmp(filename, g.name) == 0)
    {
      fp = fopen(filename, "wb");
      c = (char*)calloc(g.size, sizeof(char));
      fread((void*) c, sizeof(char), g.size, ap);
      fwrite((void*) c, sizeof(char), g.size, fp);
      free(c);
      found = 1;
      break;
    }
    fseek(ap, g.size * sizeof(char), SEEK_CUR);
  }

  if(!found)
  {
    printf("File %s not found in archive.\n", filename);
  }
}
