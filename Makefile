CC=gcc
CFLAGS=-Wall -Wextra -pedantic -O2 -g
CC = gcc
CFLAGS =  -lrt -lpthread
OBJSIEVE_TIMER  = src/timer/timer.o src/common/posix_semaphore.o
OBJSIEVE_TIMER_TEST  = src/timer/timer_test.o src/common/posix_semaphore.o
TIMER = timer
TIMER_TEST = timer_test
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

all: bin/monitor $(TIMER) $(TIMER_TEST)

# ----------------------------------------------------------------------------
# MONITOR
# ----------------------------------------------------------------------------
bin/monitor: src/monitor/main.o \
             src/monitor/monitor.o \
             src/monitor/monitor_common.o \
             src/common/logger.o \
			 src/common/posix_semaphore.o
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
$(TIMER) : $(OBJSIEVE_TIMER)
	$(CC) $^ -o $@ $(CFLAGS) -lm

$(TIMER_TEST) : $(OBJSIEVE_TIMER_TEST)
	$(CC) $^ -o $@ $(CFLAGS) -lm

src/timer/timer.o : src/timer/timer.c  include/memory.h
	$(CC) -I./include -lrt -lpthread $< -o $@ -c

src/timer/timer_test.o : src/timer/timer_test.c  include/memory.h
	$(CC) -I./include -lrt -lpthread $< -o $@ -c

src/common/posix_semaphore.o : src/common/posix_semaphore.c  include/posix_semaphore.h
	$(CC) -I./include -lrt -lpthread $< -o $@ -c



# ----------------------------------------------------------------------------
# CLEANING
# ----------------------------------------------------------------------------
clean:
	rm src/monitor/*.o src/common/*.o src/timer/*.o

distclean: clean
	rm bin/monitor

