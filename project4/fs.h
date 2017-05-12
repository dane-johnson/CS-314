#ifndef __FS_H__
#define __FS_H__
#include <sys/mman.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FSSIZE 10000000
#define NUM_BLOCKS  200
#define BLOCK_WIDTH 512
#define NUM_INODES 100
#define BLOCKS_PER_INODE 100

#define FLAG_INUSE 0x1
#define FLAG_DIR   0x2

struct superblock_t {
  int freeinodes;
  int freeblocks;
};

struct inode_t {
  char name[256];
  char flags;
  int nblocks;
  int blocks[BLOCKS_PER_INODE];
};

struct block_t {
  char data[BLOCK_WIDTH];
};

struct fs_t {
  struct superblock_t superblock;
  char fbl[NUM_BLOCKS/8];
  struct inode_t inodes[NUM_INODES];
  struct block_t blocks[NUM_BLOCKS];
};

struct fs_t* fs;

void mapfs(int fd);
void unmapfs();
void formatfs();
void loadfs();
void lsfs();
void addfilefs(char* fname);
void removefilefs(char* fname);
void extractfilefs(char* fname);
int balloc();

#endif
