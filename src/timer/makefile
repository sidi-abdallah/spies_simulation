CC = gcc
CFLAGS =  -lrt -lpthread
OBJSIEVE1  = timer.o posix_semaphore.o
OBJSIEVE2  = timer_test.o posix_semaphore.o
EXEC1 = timer
EXEC2 = timer_test
SRC = src
INC = ../../include

all: $(EXEC1) $(EXEC2) clean
.PHONY: clean

$(EXEC1) : $(OBJSIEVE1)
	$(CC) $^ -o $@ $(CFLAGS) -lm

$(EXEC2) : $(OBJSIEVE2)
	$(CC) $^ -o $@ $(CFLAGS) -lm

timer.o : timer.c  timer.h
	$(CC) -c $< $(CFLAGS) 

timer_test.o : timer_test.c  timer.h
	$(CC) -c $< $(CFLAGS) 

posix_semaphore.o : posix_semaphore.c  posix_semaphore.h
	$(CC) -c $< $(CFLAGS) 

clean :
	rm -f *.o

