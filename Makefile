CC=gcc
CFLAGS=-Wall -Wextra -pedantic -O2 -g
CC = gcc
CFLAGS =  -lrt -lpthread
OBJSIEVE1  = timer.o posix_semaphore.o
OBJSIEVE2  = timer_test.o posix_semaphore.o
EXEC1 = timer
EXEC2 = timer_test
SRC = src
INC = ../../include

# all: $(EXEC1) $(EXEC2) clean
# .PHONY: clean




# Compilation under MacOS X or Linux
UNAME=$(shell uname -s)
ifeq ($(UNAME),Darwin)
    CPPFLAGS=-D_REENTRANT -I./include -I/usr/local/Cellar/ncurses/6.3/include
    LDFLAGS=-L/usr/local/Cellar/ncurses/6.3/lib -lncurses -lpthread -lm
endif
ifeq ($(UNAME),Linux)
    CPPFLAGS=-D_REENTRANT -I./include
    LDFLAGS=-lncurses -lpthread -lrt -lm
endif

.PHONY: all clean distclean

all: bin/monitor $(EXEC1) $(EXEC2)

# ----------------------------------------------------------------------------
# MONITOR
# ----------------------------------------------------------------------------
bin/monitor: src/monitor/main.o \
             src/monitor/monitor.o \
             src/monitor/monitor_common.o \
             src/common/logger.o \
			 posix_semaphore.o
	$(CC) $^ -o $@ $(LDFLAGS)

src/monitor/main.o: src/monitor/main.c include/monitor.h include/monitor_common.h include/posix_semaphore.h
	$(CC) $(CPPFLAGS) $(CFLAGS) $< -o $@ -c

src/monitor/monitor.o: src/monitor/monitor.c include/monitor.h
	$(CC) $(CPPFLAGS) $(CFLAGS) $< -o $@ -c

src/monitor/monitor_common.o: src/monitor/monitor_common.c include/monitor_common.h
	$(CC) $(CPPFLAGS) $(CFLAGS) $< -o $@ -c


# ----------------------------------------------------------------------------
# COMMON OBJECTS FILES
# ----------------------------------------------------------------------------

src/common/logger.o: src/common/logger.c include/logger.h
	$(CC) $(CPPFLAGS) $(CFLAGS) $< -o $@ -c

# ----------------------------------------------------------------------------
# TIMER FILES
# ----------------------------------------------------------------------------
$(EXEC1) : $(OBJSIEVE1)
	$(CC) $^ -o $@ $(CFLAGS) -lm

$(EXEC2) : $(OBJSIEVE2)
	$(CC) $^ -o $@ $(CFLAGS) -lm

timer.o : src/monitor/timer.c  include/memory.h
	$(CC) -c $< $(CFLAGS) -I./include

timer_test.o : src/monitor/timer_test.c  include/memory.h
	$(CC) -c $< $(CFLAGS) -I./include

posix_semaphore.o : src/monitor/posix_semaphore.c  include/posix_semaphore.h
	$(CC) -c $< $(CFLAGS) -I./include



# ----------------------------------------------------------------------------
# CLEANING
# ----------------------------------------------------------------------------
clean:
	rm src/monitor/*.o src/common/*.o

distclean: clean
	rm bin/monitor

