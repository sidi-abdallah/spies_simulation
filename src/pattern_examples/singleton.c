/*
 * A Singleton design pattern.
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct singleton_s singleton_t;
struct singleton_s {
    int id;

    int (*get_instance)(struct singleton_s *self);
    void (*operation)(struct singleton_s *self);
};

static void singleton_operation(singleton_t *this);
static int singleton_get_instance(singleton_t *this);
static singleton_t * new_singleton(void);
singleton_t *singleton_instance(void);

int main(void)
{
    singleton_t *first_instance;
    singleton_t *second_instance;

    first_instance = singleton_instance();
    first_instance->operation(first_instance);

    second_instance = singleton_instance();
    second_instance->operation(second_instance);

    exit(EXIT_SUCCESS);
}

static void singleton_operation(singleton_t *this)
{
    printf("Singleton %d: operation\n", this->get_instance(this));
}

static int singleton_get_instance(singleton_t *this) {
    return this->id;
}

static singleton_t * new_singleton(void)
{
    static int id;
    singleton_t *singleton;

    singleton = (singleton_t *) malloc(sizeof(singleton_t));
    id++;
    singleton->id = id;
    singleton->get_instance = singleton_get_instance;
    singleton->operation   = singleton_operation;

    return singleton;
}

singleton_t *singleton_instance(void)
{
    static singleton_t *instance;

    if (instance == 0) {
        instance = new_singleton();
    }

    return instance;
}

