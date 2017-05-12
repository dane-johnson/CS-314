#include "fs.h"

void mapfs(int fd){
  if ((fs = mmap(NULL, FSSIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == NULL){
      perror("mmap failed");
      exit(EXIT_FAILURE);
  }
}


void unmapfs(){
  munmap(fs, FSSIZE);
}


void formatfs(){
  fs->superblock.freeblocks = NUM_BLOCKS;
  fs->superblock.freeinodes = NUM_INODES;
}


void loadfs(){

}


void lsfs(){
  int total, i;
  struct inode_t *curr;
  curr = fs->inodes;
  i = 0;
  total = fs->superblock.freeinodes;
  while(i < NUM_INODES && total < NUM_INODES)
  {
    if(curr->flags & FLAG_INUSE)
    {
      printf("%s\n", curr->name);
      total++;
    }
    curr += sizeof(struct inode_t);
    i++;
  }
}

void addfilefs(char* fname){
  struct inode_t *curr;
  FILE *fp;
  int nblocks;
  int *blocks;
  int size;
  int read;
  char buf[BLOCK_WIDTH];

  if(fs->superblock.freeinodes == 0)
  {
    printf("No free inodes.\n");
    exit(1);
  }

  curr = fs->inodes;
  while(curr->flags & FLAG_INUSE)
  {
    curr += sizeof(struct inode_t);
  }

  fp = fopen(fname, "r");
  if(!fp)
  {
    printf("File %s does not exist.\n", fname);
    exit(1);
  }

  fseek(fp, 0, SEEK_END);
  size = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  nblocks = size / BLOCK_WIDTH;
  if(size % BLOCK_WIDTH > 0)
  {
    nblocks++;
  }

  if(nblocks > fs->superblock.freeblocks)
  {
    printf("Not enough free blocks.\n");
    exit(1);
  }

  blocks = (int*)calloc(nblocks, BLOCK_WIDTH);
  for(int i = 0; i < nblocks; i++)
  {
    blocks[i] = balloc();
    read = fread(buf, sizeof(char), BLOCK_WIDTH, fp);
    memcpy(fs->blocks[blocks[i]].data, buf, read);
  }
  fclose(fp);

  curr->flags |= FLAG_INUSE;
  strcpy(curr->name, fname);
  memcpy(curr->blocks, blocks, nblocks * BLOCK_WIDTH);
  curr->nblocks = nblocks;
  (fs->superblock.freeinodes)--;
  fs->superblock.freeblocks -= nblocks;
}
  
  /* int *blocks; */
  /* char buf[BLOCK_WIDTH]; */
  /* fp = fopen(fname, "rb"); */
  /* if(!fp) */
  /* { */
  /*   printf("Error, file %s does not exist.\n", fname); */
  /*   exit(1); */
  /* } */
  /* if (fs->superblock.nfiles == NUM_INODES) */
  /* { */
  /*   printf("Error, file system is full.\n"); */
  /*   exit(1); */
  /* } */
  /* (fs->superblock.nfiles)++; */
  /* curr = fs->inodes; */
  /* while(curr->flags & FLAG_INUSE) */
  /* { */
  /*   curr += sizeof(struct inode_t); */
  /* } */
  /* curr->flags |= FLAG_INUSE; */
  /* strcpy(curr->name, fname); */
  /* fseek(fp, 0, SEEK_END); */
  /* size = ftell(fp); */
  /* fseek(fp, 0, SEEK_SET); */
  /* curr->nblocks = size / BLOCK_WIDTH; */
  /* if(size % BLOCK_WIDTH != 0) */
  /* { */
  /*   (curr->nblocks)++; */
  /* } */
  /* blocks = balloc(curr->nblocks); */
  /* memcpy(curr->blocks, blocks, sizeof(int) * curr->nblocks); */
  /* free(blocks); */
  /* for(int i = 0; i < curr->nblocks - 1; i++) */
  /* { */
  /*   fread(buf, sizeof(char), BLOCK_WIDTH, fp); */
  /*   memcpy(fs->blocks[curr->blocks[i]].data, buf, sizeof(char) * BLOCK_WIDTH); */
  /* } */
  /* fread(buf, sizeof(char), size % BLOCK_WIDTH, fp); */
  /* memcpy(fs->blocks[curr->blocks[curr->nblocks - 1]].data, buf, sizeof(char) * (size % BLOCK_WIDTH)); */
  /* fclose(fp); */


void removefilefs(char* fname){

}


void extractfilefs(char* fname){

}

int balloc()
{
  for(int i = 0; i < NUM_BLOCKS; i++)
  {
    for(int j = 0; j < 8; j++)
    {
      if((fs->fbl[i] & 0x1 << j) == 0)
      {
	fs->fbl[i] |= 0x1 << j;
	(fs->superblock.freeblocks)--;
	return i * 8 + j;
      }
    }
  }
  printf("Error, out of memory.\n");
  exit(1);
}
			
