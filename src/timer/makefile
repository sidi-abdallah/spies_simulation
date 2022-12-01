CC = gcc
CFLAGS =  -lrt -lpthread
OBJSIEVE  = timer.o posix_semaphore.o
EXEC = main
SRC = src
INC = ../../include

all: $(EXEC) clean
.PHONY: clean

$(EXEC) : $(OBJSIEVE)
	$(CC) $^ -o $@ $(CFLAGS) -lm

timer.o : timer.c  timer.h
	$(CC) -c $< $(CFLAGS) 

posix_semaphore.o : posix_semaphore.c  posix_semaphore.h
	$(CC) -c $< $(CFLAGS) 

clean :
	rm -f *.o

