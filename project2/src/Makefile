#
# This is a makefile for the DLX OS projects.
#

CC = gcc-dlx
AS = dlxasm
CFLAGS = -mtraps -O3

#INCS = $(wildcard *.h)
#SRCS = $(wildcard *.c)
#OBJS = $(addsuffix .o, $(basename $(wildcard *.c))) \
#       $(addsuffix .o, $(basename $(wildcard *.s)))
INCS = dlxos.h traps.h filesys.h memory.h misc.h process.h queue.h \
       synch.h syscall.h share_memory.h
SRCS = filesys.c memory.c misc.c process.c queue.c synch.c traps.c sysproc.c 
OBJS = $(addsuffix .o, $(basename $(SRCS)))

all: os.dlx.obj userprog userprog2 userprog3 userprog4 run producer consumer

os.dlx.obj: os.dlx
	$(AS) -i _osinit -l os.lst os.dlx
	mv os.dlx.obj ../execs

os.dlx: $(OBJS) dlxos.o trap_random.o osend.o share_memory.o
	$(CC) -mtraps -O3 dlxos.o trap_random.o share_memory.o $(OBJS) osend.o -o os.dlx

share_memory.o:
	cp share_memory.api share_memory.o

osend.o: osend.s
	$(CC) -c osend.s

trap_random.o: trap_random.s
	$(CC) -c trap_random.s

dlxos.o: dlxos.s
	$(CC) -c dlxos.s

usertraps.o: usertraps.s
	$(CC) -c usertraps.s

userprog : userprog.o usertraps.o misc.o
	$(CC) -mtraps -O3 userprog.o usertraps.o misc.o -o userprog.dlx
	$(AS) -l userprog.lst userprog.dlx
	mv userprog.dlx.obj ../execs

userprog2 : userprog2.o usertraps.o misc.o
	$(CC) -mtraps -O3 userprog2.o usertraps.o misc.o -o userprog2.dlx
	$(AS) -l userprog2.lst userprog2.dlx
	mv userprog2.dlx.obj ../execs

userprog3 : userprog3.o usertraps.o misc.o
	$(CC) -mtraps -O3 userprog3.o usertraps.o misc.o -o userprog3.dlx
	$(AS) -l userprog3.lst userprog3.dlx
	mv userprog3.dlx.obj ../execs

userprog4 : userprog4.o usertraps.o misc.o
	$(CC) -mtraps -O3 userprog4.o usertraps.o misc.o -o userprog4.dlx
	$(AS) -l userprog4.lst userprog4.dlx
	mv userprog4.dlx.obj ../execs

run	 : run.o usertraps.o misc.o
	$(CC) -mtraps -O3 run.o usertraps.o misc.o -o run.dlx
	$(AS) -l run.lst run.dlx
	mv run.dlx.obj ../execs

producer : producer.o usertraps.o misc.o
	$(CC) -mtraps -O3 producer.o usertraps.o misc.o -o producer.dlx
	$(AS) -l producer.lst producer.dlx
	mv producer.dlx.obj ../execs

consumer : consumer.o usertraps.o misc.o
	$(CC) -mtraps -O3 consumer.o usertraps.o misc.o -o consumer.dlx
	$(AS) -l consumer.lst consumer.dlx
	mv consumer.dlx.obj ../execs


Makefile.depend: depend

depend: $(SRCS) $(INCS)
	$(CC) -MM $(SRCS) > Makefile.depend

clean:
	/bin/rm -f *.o *.dlx *.lst *.obj Makefile.depend vm

include Makefile.depend
