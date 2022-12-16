#ifndef SPY_SIMULATION_H
#define SPY_SIMULATION_H

#include "memory.h"
#include "common.h"
#include "cell.h"
#include "character.h"


memory_t * create_memory();

void create_map(memory_t * memory);
void create_map_cell(memory_t * memory, int type, int row, int column, int nb_of_characters, int * nb_companies, int * nb_residential_buildings, int * nb_supermakets);
void create_mailbox(memory_t * memory);
void create_spies(memory_t * memory);
void create_characters(memory_t * memory);
void create_character(memory_t * memory, int id, character_type_t type, int home_row, int home_column, int work_row, int work_column, work_type_t work, int * nb_citizens, int * nb_spies);

character_t * get_characters(memory_t * memory);
void mesh_surveillance_network(memory_t * memory, character_t characters[NUMBER_OF_CHARACTERS-1]);

void set_signal_handler();
void signal_handler(int signum);
void new_round();

#endif /* SPY_SIMULATION_H */
