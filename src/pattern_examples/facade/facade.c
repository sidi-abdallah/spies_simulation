/*
 * A Facade design pattern.
 */
#include <stdio.h>
#include <stdlib.h>

#include "facade.h"
#include "logger.h"

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
    printf(">> %d\n", result);
}

int memory_get_int_value(memory_t *memory, int index)
{
    return memory->fields[index];
}
