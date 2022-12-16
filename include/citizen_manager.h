#ifndef CITIZEN_MANAGER_H
#define CITIZEN_MANAGER_H

#include "memory.h"

struct args_s {
  memory_t * memory;
  int citizen_index;
};
typedef struct args_s args_t;

int get_hour(memory_t *memory);
int get_minutes(memory_t *memory);
void get_next_cell(memory_t *memory, int citizen_index, int destination_row, int destination_column, int * next_row, int * next_column);
void *make_round(void * args);
#endif //CITIZEN_MANAGER_H
