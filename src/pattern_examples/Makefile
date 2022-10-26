CC=gcc
CPPFLAGS=
CFLAGS=-Wall -Wextra -pedantic -g
EXEC= singleton factory facade observer

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

clean:
	rm $(EXEC)
