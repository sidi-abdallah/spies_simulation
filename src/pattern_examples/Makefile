CC=gcc
CPPFLAGS=-I. -I./facade -I./factory -I./observer -I./state
CFLAGS=-Wall -Wextra -pedantic -g
EXEC=factory.bin facade.bin observer.bin state_character.bin

.PHONY: all clean

all: $(EXEC)

singleton.bin: singleton.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $^ -o $@

factory.bin: factory/main.c factory/factory.c logger.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $^ -o $@

facade.bin: facade/main.c facade/facade.c logger.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $^ -o $@

observer.bin: observer/main.c observer/observer.c logger.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $^ -o $@

state_character.bin: state/main.c state/character.c logger.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $^ -o $@

clean:
	rm $(EXEC)
