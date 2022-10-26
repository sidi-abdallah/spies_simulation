CC=gcc
CPPFLAGS=
CFLAGS=-Wall -Wextra -pedantic -g
EXEC= singleton factory facade observer state

.PHONY: all clean

all: $(EXEC)

singleton: singleton.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $^ -o $@

factory: factory.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $^ -o $@

facade: facade.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $^ -o $@

observer: observer.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $^ -o $@

state: state/main.c state/character.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $^ -o $@

clean:
	rm $(EXEC)
