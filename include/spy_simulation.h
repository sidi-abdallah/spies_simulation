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

void create_spies(spie_t spies[NUMBER_OF_SPIES], mailbox_t * mailbox, residential_building_t residential_buildings[MAX_RESIDENTIAL_BUILDING]);
void create_citizens(citizen_t citizens[NUMBER_OF_CITIZENS], residential_building_t residential_buildings[MAX_RESIDENTIAL_BUILDING], company_t companies[MAX_COMPANIES], city_hall_t * city_hall, supermarket_t supermarkets[MAX_SUPERMARKETS]);

int manhattan_distance(int x1, int y1, int x2, int y2);

#endif /* SPY_SIMULATION_H */
