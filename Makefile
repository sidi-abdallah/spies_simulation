CC=gcc
CFLAGS=-Wall -Wextra -pedantic -O2 -g

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

all: bin/main bin/spy_simulation bin/timer bin/monitor bin/citizen_manager bin/enemy_spy_network

bin/main : src/main.c
	$(CC) $^ -o $@ $(LDFLAGS)
	
# ----------------------------------------------------------------------------
# MONITOR
# ----------------------------------------------------------------------------
bin/monitor: src/monitor/main.o \
             src/monitor/monitor.o \
             src/monitor/monitor_common.o \
             src/common/logger.o \
			 src/common/posix_semaphore.o
	$(CC) $^ -o $@ $(LDFLAGS)

src/monitor/main.o: src/monitor/main.c include/monitor.h include/monitor_common.h
	$(CC) $(CPPFLAGS) $(CFLAGS) $< -o $@ -c

src/monitor/monitor.o: src/monitor/monitor.c include/monitor.h
	$(CC) $(CPPFLAGS) $(CFLAGS) $< -o $@ -c

src/monitor/monitor_common.o: src/monitor/monitor_common.c include/monitor_common.h
	$(CC) $(CPPFLAGS) $(CFLAGS) $< -o $@ -c


# ----------------------------------------------------------------------------
# SPY_SIMULATION
# ----------------------------------------------------------------------------
bin/spy_simulation : src/spy_simulation/main.o \
					 src/spy_simulation/spy_simulation.o \
					 src/common/posix_semaphore.o \
					 src/common/functions.o
	$(CC) $^ -o $@ $(LDFLAGS)

src/spy_simulation/main.o : src/spy_simulation/main.c include/spy_simulation.h
	$(CC) $(CPPFLAGS) $(CFLAGS) $< -o $@ -c

src/spy_simulation/spy_simulation.o : src/spy_simulation/spy_simulation.c include/spy_simulation.h
	$(CC) $(CPPFLAGS) $(CFLAGS) $< -o $@ -c

# ----------------------------------------------------------------------------
# TIMER
# ----------------------------------------------------------------------------
bin/timer : src/timer/main.o \
			src/timer/timer.o \
			src/common/posix_semaphore.o
	$(CC) $^ -o $@ $(LDFLAGS)

src/timer/main.o : src/timer/main.c include/timer.h
	$(CC) $(CPPFLAGS) $(CFLAGS) $< -o $@ -c

src/timer/timer.o : src/timer/timer.c include/timer.h
	$(CC) $(CPPFLAGS) $(CFLAGS) $< -o $@ -c


# ----------------------------------------------------------------------------
# ENEMY_SPY_NETWORK
# ----------------------------------------------------------------------------

bin/enemy_spy_network : src/enemy_spy_network/main.o \
						src/enemy_spy_network/enemy_spy_network.o \
						src/common/posix_semaphore.o \
						src/common/functions.o
	$(CC) $^ -o $@ $(LDFLAGS)

src/enemy_spy_network/main.o : src/enemy_spy_network/main.c include/enemy_spy_network.h
	$(CC) $(CPPFLAGS) $(CFLAGS) $< -o $@ -c
	
src/enemy_spy_network/enemy_spy_network.o : src/enemy_spy_network/enemy_spy_network.c include/enemy_spy_network.h
	$(CC) $(CPPFLAGS) $(CFLAGS) $< -o $@ -c

# ----------------------------------------------------------------------------
# CITIZEN_MANAGER
# ----------------------------------------------------------------------------
bin/citizen_manager : src/citizen_manager/main.o \
					  src/citizen_manager/citizen_manager.o \
					  src/common/posix_semaphore.o \
					  src/common/functions.o \
					  src/spy_simulation/spy_simulation.o
	$(CC) $^ -o $@ $(LDFLAGS)

src/citizen_manager/main.o : src/citizen_manager/main.c include/citizen_manager.h
	$(CC) $(CPPFLAGS) $(CFLAGS) $< -o $@ -c

src/citizen_manager/citizen_manager.o : src/citizen_manager/citizen_manager.c include/citizen_manager.h
	$(CC) $(CPPFLAGS) $(CFLAGS) $< -o $@ -c

# ----------------------------------------------------------------------------
# COMMON OBJECTS FILES
# ----------------------------------------------------------------------------

src/common/logger.o: src/common/logger.c include/logger.h
	$(CC) $(CPPFLAGS) $(CFLAGS) $< -o $@ -c

src/common/posix_semaphore.o : src/common/posix_semaphore.c include/posix_semaphore.h
	$(CC) $(CPPFLAGS) $(CFLAGS) $< -o $@ -c

src/common/functions.o : src/common/functions.c include/functions.h
	$(CC) $(CPPFLAGS) $(CFLAGS) $< -o $@ -c


# ----------------------------------------------------------------------------
# CLEANING
# ----------------------------------------------------------------------------
clean:
	rm -f src/monitor/*.o src/common/*.o src/spy_simulation/*.o src/citizen_manager/*.o src/timer/*.o

distclean: clean
	rm -f bin/* 

clean_sem :
	rm -f /dev/shm/*

