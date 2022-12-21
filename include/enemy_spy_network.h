#ifndef ENEMY_SPY_NETWORK_H
#define ENEMY_SPY_NETWORK_H

//#include "citizen_manager.h"
typedef struct args_spy {
    memory_t *memory;
    int spie_index;
} args_spy;

#define SPIES_NUMBER 3
#define ROUND_NB_BEFORE_STOLE 12
#define ADJACENT_CASES_NUMBER 8

void get_next_cell(memory_t *memory, int spie_index, int destination_row, int destination_column, int * next_row, int * next_column);

void day_routine(memory_t *memory, int spie_index);

void spie_routine(memory_t *memory, int spie_index);

void main_spy(int index);

#endif //ENEMY_SPY_NETWORK_H