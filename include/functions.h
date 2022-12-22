#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "memory.h"

/**
 * \brief Calculate the manhattan distance between two cells.
 */
int manhattan_distance(int x1, int y1, int x2, int y2);

/**
 * \brief Calculate the current hour according to the number of rounds done.
 */
int get_hour(memory_t *memory);

/**
 * \brief Calculate the current minutes in the current hour according to the number of rounds done.
 */
int get_minutes(memory_t *memory);

time1_t create_time(int hour, int minutes);

#endif //FUNCTIONS_H
