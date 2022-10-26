/*
 * A Facade design pattern.
 */
#include <stdio.h>
#include <stdlib.h>

/*
 * The facade pattern knows the objects to which the requests of a client are
 * addressed. The facade transmits the various requests from the client to the
 * objects, then returns their responses to the client.
 */
typedef struct facade_s facade_t;
typedef struct memory_s memory_t;

struct facade_s {
    memory_t *memory;
    void (*get_and_display)(facade_t *, int);
};

struct memory_s {
    /*
     * Many fields such as integer values...
     */
    int fields[3];

    int (*get_int_value)(memory_t *memory, int index);
};

memory_t * new_memory(int (*get_int_value)(memory_t *, int));
facade_t * new_facade(memory_t *memory);
void facade_get_and_display(facade_t *facade, int index);
int memory_get_int_value(memory_t *memory, int index);

int main(void)
{
    memory_t *memory;
    facade_t *facade;

    memory = new_memory(memory_get_int_value);
    facade = new_facade(memory);
    facade->get_and_display(facade, 0);
    facade->get_and_display(facade, 1);
    facade->get_and_display(facade, 2);

    exit(EXIT_SUCCESS);
}

memory_t * new_memory(int (*get_int_value)(memory_t *, int))
{
    memory_t *memory;

    /* Should be a call to mmap() rather than malloc() / It is just for testing convenience. */
    memory = (memory_t *) malloc(sizeof(memory_t));
    memory->fields[0] = 5;
    memory->fields[1] = 7;
    memory->fields[2] = 3;
    memory->get_int_value = memory_get_int_value;

    return memory;
}

facade_t *new_facade(memory_t *memory)
{
    facade_t *facade;

    facade = (facade_t *) malloc(sizeof(facade_t));
    facade->memory = memory;
    facade->get_and_display = facade_get_and_display;

    return facade;
}

void facade_get_and_display(facade_t *facade, int index)
{
    int result;

    result = facade->memory->get_int_value(facade->memory, index);
    printf("%d\n", result);
}

int memory_get_int_value(memory_t *memory, int index)
{
    return memory->fields[index];
}
