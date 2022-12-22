#ifndef ENEMY_SPY_NETWORK_H
#define ENEMY_SPY_NETWORK_H

/**
 * \file enemy_spy_network.h
 *
 * Defines functions used by the spy network.
 */

#define SPIES_NUMBER 3
#define ROUND_NB_BEFORE_STOLE 12
#define ADJACENT_CASES_NUMBER 8

typedef struct args_spy {
    memory_t *memory;
    int spie_index;
} args_spy;

/**
 * @brief Calculate the next cell for a given spy according to his current location and his destination.
*/
void get_next_cell(memory_t *memory, int spie_index, int destination_row, int destination_column, int * next_row, int * next_column);

/**
 * @brief Perform the day routine of a given spy.
*/
void day_routine(memory_t *memory, int spie_index);

/**
 * @brief Perform the night routine of a given spy.
*/
void night_routine(memory_t *memory, int spie_index);

/**
 * @brief Perform the routine of a given spy.
*/
void * spie_routine(void *args);

/**
 * @brief Perform the main process for a given spy.
*/
void main_spy(int index);

/**
 * @brief Perform the main process for the case officer.
*/
void main_case_officer();

/**
 * @brief Perform the routine of the case officer.
*/
void case_officer_routine(memory_t * memory);

/**
 * @brief Calculate the next cell for the case officer according to his current location and his destination.
*/
void get_next_cell_case_officer(memory_t *memory, int destination_row, int destination_column, int * next_row, int * next_column);

/**
 * @brief Collect all the messages of the mailbox for the case officer.
*/
void case_officer_get_message(memory_t *memory);

#endif //ENEMY_SPY_NETWORK_H
