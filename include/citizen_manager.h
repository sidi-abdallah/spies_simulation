#ifndef CITIZEN_MANAGER_H
#define CITIZEN_MANAGER_H

/**
 * \file citizen_manager.h
 *
 * Defines structures and functions used by the threads of each citizen.
 */

#include "memory.h"

/**
 * \brief The arguments of each thread.
 */
struct args_s {
  memory_t * memory; /*!< The shared memory. */
  int citizen_index; /*!< The index of the citizen's thread. */
};

typedef struct args_s args_t;

/**
 * \brief Calculate the next cell a citizen will go according to his final destination.
 */
void get_next_cell(memory_t *memory, int citizen_index, int destination_row, int destination_column, int * next_row, int * next_column);

/**
 * \brief Move the citizen to his next cell according to the hour of the day, his home, work, if he has to go to the supermarket...
 */
void *make_round(void * args);
#endif //CITIZEN_MANAGER_H
