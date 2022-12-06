#include "spy_simulation.h"
#include <stdio.h>
#include <stdlib.h>

memory_t create_memory() {
    memory_t memory;

    create_map(&(memory.map));
    create_residential_buildings(memory.residential_buildings);
    create_companies(memory.companies);
    create_mailbox(&memory.mailbox, memory.residential_buildings);
    create_spies(memory.spies, &memory.mailbox, memory.residential_buildings);
    create_citizens(memory.citizens, memory.residential_buildings, memory.companies, &memory.city_hall, memory.supermarkets);

    return memory;
}

void create_map(map_t * map) {
    map->columns = MAX_COLUMNS;
    map->rows = MAX_ROWS;

    create_map_cell(&map->cells[0][0], WASTELAND, 0, 0, MAX_CHARACTERS_WASTELAND);
    create_map_cell(&map->cells[0][1], COMPANY, 0, 1, MAX_CHARACTERS_COMPANY);
    create_map_cell(&map->cells[0][2], WASTELAND, 0, 2, MAX_CHARACTERS_WASTELAND);
    create_map_cell(&map->cells[0][3], COMPANY, 0, 3, MAX_CHARACTERS_COMPANY);
    create_map_cell(&map->cells[0][4], WASTELAND, 0, 4, MAX_CHARACTERS_WASTELAND);
    create_map_cell(&map->cells[0][5], WASTELAND, 0, 5, MAX_CHARACTERS_WASTELAND);
    create_map_cell(&map->cells[0][6], COMPANY, 0, 6, MAX_CHARACTERS_COMPANY);

    create_map_cell(&map->cells[1][0], RESIDENTIAL_BUILDING, 1, 0, MAX_CHARACTERS_RESIDENTIAL_BUILDING);
    create_map_cell(&map->cells[1][1], WASTELAND, 1, 1, MAX_CHARACTERS_WASTELAND);
    create_map_cell(&map->cells[1][2], SUPERMARKET, 1, 2, MAX_CHARACTERS_SUPERMARKET);
    create_map_cell(&map->cells[1][3], WASTELAND, 1, 3, MAX_CHARACTERS_WASTELAND);
    create_map_cell(&map->cells[1][4], WASTELAND, 1, 4, MAX_CHARACTERS_WASTELAND);
    create_map_cell(&map->cells[1][5], RESIDENTIAL_BUILDING, 1, 5, MAX_CHARACTERS_RESIDENTIAL_BUILDING);
    create_map_cell(&map->cells[1][6], WASTELAND, 1, 6, MAX_CHARACTERS_WASTELAND);
    
    create_map_cell(&map->cells[2][0], WASTELAND, 2, 0, MAX_CHARACTERS_WASTELAND);
    create_map_cell(&map->cells[2][1], RESIDENTIAL_BUILDING, 2, 1, MAX_CHARACTERS_RESIDENTIAL_BUILDING);
    create_map_cell(&map->cells[2][2], WASTELAND, 2, 2, MAX_CHARACTERS_WASTELAND);
    create_map_cell(&map->cells[2][3], RESIDENTIAL_BUILDING, 2, 3, MAX_CHARACTERS_RESIDENTIAL_BUILDING);
    create_map_cell(&map->cells[2][4], WASTELAND, 2, 4, MAX_CHARACTERS_WASTELAND);
    create_map_cell(&map->cells[2][5], WASTELAND, 2, 5, MAX_CHARACTERS_WASTELAND);
    create_map_cell(&map->cells[2][6], RESIDENTIAL_BUILDING, 2, 6, MAX_CHARACTERS_RESIDENTIAL_BUILDING);

    create_map_cell(&map->cells[3][0], WASTELAND, 3, 0, MAX_CHARACTERS_WASTELAND);
    create_map_cell(&map->cells[3][1], WASTELAND, 3, 1, MAX_CHARACTERS_WASTELAND);
    create_map_cell(&map->cells[3][2], WASTELAND, 3, 2, MAX_CHARACTERS_WASTELAND);
    create_map_cell(&map->cells[3][3], CITY_HALL, 3, 3, MAX_CHARACTERS_CITY_HALL);
    create_map_cell(&map->cells[3][4], COMPANY, 3, 4, MAX_CHARACTERS_COMPANY);
    create_map_cell(&map->cells[3][5], WASTELAND, 3, 5, MAX_CHARACTERS_WASTELAND);
    create_map_cell(&map->cells[3][6], WASTELAND, 3, 6, MAX_CHARACTERS_WASTELAND);

    create_map_cell(&map->cells[4][0], WASTELAND, 4, 0, MAX_CHARACTERS_WASTELAND);
    create_map_cell(&map->cells[4][1], RESIDENTIAL_BUILDING, 4, 1, MAX_CHARACTERS_RESIDENTIAL_BUILDING);
    create_map_cell(&map->cells[4][2], COMPANY, 4, 2, MAX_CHARACTERS_COMPANY);
    create_map_cell(&map->cells[4][3], SUPERMARKET, 4, 3, MAX_CHARACTERS_SUPERMARKET);
    create_map_cell(&map->cells[4][4], WASTELAND, 4, 4, MAX_CHARACTERS_WASTELAND);
    create_map_cell(&map->cells[4][5], WASTELAND, 4, 5, MAX_CHARACTERS_WASTELAND);
    create_map_cell(&map->cells[4][6], RESIDENTIAL_BUILDING, 4, 6, MAX_CHARACTERS_RESIDENTIAL_BUILDING);

    create_map_cell(&map->cells[5][0], WASTELAND, 5, 0, MAX_CHARACTERS_WASTELAND);
    create_map_cell(&map->cells[5][1], WASTELAND, 5, 1, MAX_CHARACTERS_WASTELAND);
    create_map_cell(&map->cells[5][2], COMPANY, 5, 2, MAX_CHARACTERS_COMPANY);
    create_map_cell(&map->cells[5][3], WASTELAND, 5, 3, MAX_CHARACTERS_WASTELAND);
    create_map_cell(&map->cells[5][4], RESIDENTIAL_BUILDING, 5, 4, MAX_CHARACTERS_RESIDENTIAL_BUILDING);
    create_map_cell(&map->cells[5][5], WASTELAND, 5, 5, MAX_CHARACTERS_WASTELAND);
    create_map_cell(&map->cells[5][6], COMPANY, 5, 6, MAX_CHARACTERS_COMPANY);

    create_map_cell(&map->cells[6][0], RESIDENTIAL_BUILDING, 6, 0, MAX_CHARACTERS_RESIDENTIAL_BUILDING);
    create_map_cell(&map->cells[6][1], COMPANY, 6, 1, MAX_CHARACTERS_COMPANY);
    create_map_cell(&map->cells[6][2], WASTELAND, 6, 2, MAX_CHARACTERS_WASTELAND);
    create_map_cell(&map->cells[6][3], WASTELAND, 6, 3, MAX_CHARACTERS_WASTELAND);
    create_map_cell(&map->cells[6][4], RESIDENTIAL_BUILDING, 6, 4, MAX_CHARACTERS_RESIDENTIAL_BUILDING);
    create_map_cell(&map->cells[6][5], WASTELAND, 6, 5, MAX_CHARACTERS_WASTELAND);
    create_map_cell(&map->cells[6][6], RESIDENTIAL_BUILDING, 6, 6, MAX_CHARACTERS_RESIDENTIAL_BUILDING);
}

void create_residential_buildings(residential_building_t residential_buildings[MAX_RESIDENTIAL_BUILDING]) {
    residential_buildings[0].row = 1;
    residential_buildings[0].column = 0;
    residential_buildings[0].affected_characters = 0;

    residential_buildings[1].row = 1;
    residential_buildings[1].column = 5;
    residential_buildings[1].affected_characters = 0;

    residential_buildings[2].row = 2;
    residential_buildings[2].column = 1;
    residential_buildings[2].affected_characters = 0;

    residential_buildings[3].row = 2;
    residential_buildings[3].column = 3;
    residential_buildings[3].affected_characters = 0;

    residential_buildings[4].row = 2;
    residential_buildings[4].column = 6;
    residential_buildings[4].affected_characters = 0;

    residential_buildings[5].row = 4;
    residential_buildings[5].column = 1;
    residential_buildings[5].affected_characters = 0;

    residential_buildings[6].row = 4;
    residential_buildings[6].column = 6;
    residential_buildings[6].affected_characters = 0;

    residential_buildings[7].row = 5;
    residential_buildings[7].column = 4;
    residential_buildings[7].affected_characters = 0;

    residential_buildings[8].row = 6;
    residential_buildings[8].column = 0;
    residential_buildings[8].affected_characters = 0;

    residential_buildings[9].row = 6;
    residential_buildings[9].column = 4;
    residential_buildings[9].affected_characters = 0;

    residential_buildings[10].row = 6;
    residential_buildings[10].column = 6;
    residential_buildings[10].affected_characters = 0;
}

void create_companies(company_t companies[MAX_COMPANIES]) {
    int i;
    int company_type;

    companies[0].row = 0;
    companies[0].column = 1;

    companies[1].row = 0;
    companies[1].column = 3;

    companies[2].row = 0;
    companies[2].column = 6;

    companies[3].row = 3;
    companies[3].column = 4;

    companies[4].row = 4;
    companies[4].column = 2;

    companies[5].row = 5;
    companies[5].column = 2;

    companies[6].row = 5;
    companies[6].column = 6;

    companies[7].row = 6;
    companies[7].column = 1;

    for(i=0; i<MAX_COMPANIES; i++) {
        company_type = rand()%MAX_COMPANY_TYPES;
        companies[i].type = company_type;
    }
}

void display_map(map_t * map) {
    int i, j;
    int letter[5] = {'W', 'R', 'H', 'C', 'S'};
    for(i=0; i<map->rows; i++) {
        for(j=0; j<map->columns; j++) {
            printf("%c ", letter[map->cells[i][j].type]);
        }
        printf("\n");
    }
}

void create_map_cell(cell_t * cell, int type, int row, int column, int nb_of_characters) {
    cell->type = type;
    cell->row = row;
    cell->column = column;
    cell->nb_of_characters = nb_of_characters;
}

void create_mailbox(mailbox_t * mailbox, residential_building_t residential_buildings[MAX_RESIDENTIAL_BUILDING]) {
    int random_building = rand()%MAX_RESIDENTIAL_BUILDING;
    mailbox->row = residential_buildings[random_building].row;
    mailbox->column = residential_buildings[random_building].column;
    residential_buildings[random_building].affected_characters += 1;
}

void create_spies(spie_t spies[NUMBER_OF_SPIES], mailbox_t * mailbox, residential_building_t residential_buildings[MAX_RESIDENTIAL_BUILDING]) {
    int i;
    int spie_affected;
    int random_building;

    for(i=0; i<NUMBER_OF_SPIES; i++) {
        spie_affected = 0;
        while(!spie_affected) {
            random_building = rand()%MAX_RESIDENTIAL_BUILDING;
            if(manhattan_distance(residential_buildings[random_building].row, residential_buildings[random_building].column, mailbox->row, mailbox->column) < 4 && residential_buildings[random_building].affected_characters < MAX_HABITATION_IN_RESIDENTIAL_BUILING) {
                spies[i].habitation_row = residential_buildings[random_building].row;
                spies[i].habitation_column = residential_buildings[random_building].column;
                spies[i].current_row = residential_buildings[random_building].row;
                spies[i].current_row = residential_buildings[random_building].column;
                spies[i].life_points = MAX_LIFE_POINTS;
                residential_buildings[random_building].affected_characters += 1;
                spie_affected = 1;
            }
        }
    }
}

void create_citizens(citizen_t citizens[NUMBER_OF_CITIZENS], residential_building_t residential_buildings[MAX_RESIDENTIAL_BUILDING], company_type_t companies[MAX_COMPANIES], city_hall_t * city_hall, supermarket_t supermarkets[MAX_SUPERMARKETS]) {
    int i;
    int character_habitation_affected;
    int random_building;
    
    for(i=0; i<NUMBER_OF_CITIZENS; i++) {
        character_habitation_affected = 0;
        while(!character_habitation_affected) {
            if(!character_habitation_affected) {
                random_building = rand()%MAX_RESIDENTIAL_BUILDING;
                if(residential_buildings[random_building].affected_characters < MAX_HABITATION_IN_RESIDENTIAL_BUILING) {
                    residential_buildings[random_building].affected_characters += 1;
                    citizens[i].habitation_row = residential_buildings[random_building].row;
                    citizens[i].habitation_column = residential_buildings[random_building].column;
                    citizens[i].current_row = residential_buildings[random_building].row;
                    citizens[i].current_column = residential_buildings[random_building].column;
                    citizens[i].life_points = MAX_LIFE_POINTS;
                    // printf("Citizen n°%d affected to [%d,%d]\n", i, residential_buildings[random_building].row, residential_buildings[random_building].column);
                    character_habitation_affected = 1;
                }
            }
        }
    }
}

int manhattan_distance(int x1, int y1, int x2, int y2) {
    return abs(x2 - x1) + abs(y2 - y1);
}
