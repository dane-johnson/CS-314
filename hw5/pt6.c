#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define IN 0
#define OUT 1

typedef struct FileInfo
{
  char name[10];
  int noc;
  int now;
  int nol;
} FileInfo;

void initfileinfo(FileInfo*, const char*);
void parsefile(FileInfo*, FILE*);
void printfileinfo(FileInfo);
void addtosaved(FileInfo);
void printsaved();

int main(int argc, char *argv[])
{
  char *filename;
  FILE *fp;
  FileInfo curr;
  
  switch(argc)
  {
  case 2:
    filename = argv[1];
    fp = fopen(filename, "r");

    if(fp == NULL)
    {
      printf("File not found.\n");
      exit(1);
    }

    break;
  default:
    printf("Usage: %s filename\n", argv[0]);
    exit(2);
  }

  initfileinfo(&curr, filename);
  parsefile(&curr, fp);
  fclose(fp);

  addtosaved(curr);
  printsaved();
  
  return 0;
}

void initfileinfo(FileInfo *fi, const char *filename)
{
  strcpy(fi->name, filename);
  fi->noc = 0;
  fi->now = 0;
  fi->nol = 0;
}

void printfileinfo(FileInfo fi)
{
  printf(" %d %d %d %s\n", fi.nol, fi.now, fi.noc, fi.name);
}

void parsefile(FileInfo *fi, FILE *fp)
{
  int flip = OUT;
  char curr;

  curr = fgetc(fp);

  while(curr != EOF)
  {
    (fi->noc)++;
    switch(curr)
    {
    case ' ':
      if(flip == IN)
      {
	flip = OUT;
      }
      break;
    case '\n':
      (fi->nol)++;
      if(flip == IN)
      {
	flip = OUT;
      }
      break;
    default:
      if(flip == OUT)
      {
	(fi->now)++;
	flip = IN;
      }
    }

    curr = fgetc(fp);
  }
}

void addtosaved(FileInfo fi)
{
  FILE *fp;
  FileInfo *curr;

  curr = (FileInfo*)malloc(sizeof(FileInfo));

  //Open the file for binary read-write with appending
  fp = fopen("wc.saved", "a+b");

  //Check to be sure we haven't already added this file
  while(fread((void*) curr, sizeof(FileInfo), 1, fp))
  {
    if(strcmp(curr->name, fi.name) == 0)
    {
      fclose(fp);
      free(curr);
      return;
    }
  }
  
  //Add this file to saved
  fwrite((void*) &fi, sizeof(FileInfo), 1, fp);
  fclose(fp);
  free(curr);
}

void printsaved()
{
  FILE *fp;
  FileInfo *curr;
  int tol=0, tow=0, toc=0;

  curr = (FileInfo*)malloc(sizeof(FileInfo));
  fp = fopen("wc.saved", "rb");
  if(fp)
  {
    while(fread((void*)curr, sizeof(FileInfo), 1, fp))
    {
      printfileinfo(*curr);
      tol += curr->nol;
      tow += curr->now;
      toc += curr->noc;
    }
    fclose(fp);
  }
  printf(" %d %d %d\n", tol, tow, toc);
  free(curr);
}
      
