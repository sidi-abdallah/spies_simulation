/*
 * A Facade design pattern.
 */
#ifndef FACADE_H
#define FACADE_H

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

#endif
