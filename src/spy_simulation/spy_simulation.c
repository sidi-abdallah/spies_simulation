#include "spy_simulation.h"
#include <stdio.h>
#include <stdlib.h>

memory_t * create_memory() {
    memory_t * memory = (memory_t *) malloc(sizeof(memory_t));

    create_map(memory);
    create_mailbox(memory);
    // create_spies(memory.spies, &memory.mailbox, memory.residential_buildings);
    // create_citizens(memory.citizens, memory.residential_buildings, memory.companies, &memory.city_hall, memory.supermarkets);

    return memory;
}

void create_map(memory_t * memory) {
    int nb_companies = 0;
    int nb_residential_buildings = 0;
    int nb_supermakets = 0;

    memory->map.columns = MAX_COLUMNS;
    memory->map.rows = MAX_ROWS;

    create_map_cell(memory, WASTELAND, 0, 0, MAX_CHARACTERS_WASTELAND, &nb_companies, &nb_residential_buildings, &nb_supermakets);
    create_map_cell(memory, COMPANY, 0, 1, MAX_CHARACTERS_COMPANY, &nb_companies, &nb_residential_buildings, &nb_supermakets);
    create_map_cell(memory, WASTELAND, 0, 2, MAX_CHARACTERS_WASTELAND, &nb_companies, &nb_residential_buildings, &nb_supermakets);
    create_map_cell(memory, COMPANY, 0, 3, MAX_CHARACTERS_COMPANY, &nb_companies, &nb_residential_buildings, &nb_supermakets);
    create_map_cell(memory, WASTELAND, 0, 4, MAX_CHARACTERS_WASTELAND, &nb_companies, &nb_residential_buildings, &nb_supermakets);
    create_map_cell(memory, WASTELAND, 0, 5, MAX_CHARACTERS_WASTELAND, &nb_companies, &nb_residential_buildings, &nb_supermakets);
    create_map_cell(memory, COMPANY, 0, 6, MAX_CHARACTERS_COMPANY, &nb_companies, &nb_residential_buildings, &nb_supermakets);

    create_map_cell(memory, RESIDENTIAL_BUILDING, 1, 0, MAX_CHARACTERS_RESIDENTIAL_BUILDING, &nb_companies, &nb_residential_buildings, &nb_supermakets);
    create_map_cell(memory, WASTELAND, 1, 1, MAX_CHARACTERS_WASTELAND, &nb_companies, &nb_residential_buildings, &nb_supermakets);
    create_map_cell(memory, SUPERMARKET, 1, 2, MAX_CHARACTERS_SUPERMARKET, &nb_companies, &nb_residential_buildings, &nb_supermakets);
    create_map_cell(memory, WASTELAND, 1, 3, MAX_CHARACTERS_WASTELAND, &nb_companies, &nb_residential_buildings, &nb_supermakets);
    create_map_cell(memory, WASTELAND, 1, 4, MAX_CHARACTERS_WASTELAND, &nb_companies, &nb_residential_buildings, &nb_supermakets);
    create_map_cell(memory, RESIDENTIAL_BUILDING, 1, 5, MAX_CHARACTERS_RESIDENTIAL_BUILDING, &nb_companies, &nb_residential_buildings, &nb_supermakets);
    create_map_cell(memory, WASTELAND, 1, 6, MAX_CHARACTERS_WASTELAND, &nb_companies, &nb_residential_buildings, &nb_supermakets);
    
    create_map_cell(memory, WASTELAND, 2, 0, MAX_CHARACTERS_WASTELAND, &nb_companies, &nb_residential_buildings, &nb_supermakets);
    create_map_cell(memory, RESIDENTIAL_BUILDING, 2, 1, MAX_CHARACTERS_RESIDENTIAL_BUILDING, &nb_companies, &nb_residential_buildings, &nb_supermakets);
    create_map_cell(memory, WASTELAND, 2, 2, MAX_CHARACTERS_WASTELAND, &nb_companies, &nb_residential_buildings, &nb_supermakets);
    create_map_cell(memory, RESIDENTIAL_BUILDING, 2, 3, MAX_CHARACTERS_RESIDENTIAL_BUILDING, &nb_companies, &nb_residential_buildings, &nb_supermakets);
    create_map_cell(memory, WASTELAND, 2, 4, MAX_CHARACTERS_WASTELAND, &nb_companies, &nb_residential_buildings, &nb_supermakets);
    create_map_cell(memory, WASTELAND, 2, 5, MAX_CHARACTERS_WASTELAND, &nb_companies, &nb_residential_buildings, &nb_supermakets);
    create_map_cell(memory, RESIDENTIAL_BUILDING, 2, 6, MAX_CHARACTERS_RESIDENTIAL_BUILDING, &nb_companies, &nb_residential_buildings, &nb_supermakets);

    create_map_cell(memory, WASTELAND, 3, 0, MAX_CHARACTERS_WASTELAND, &nb_companies, &nb_residential_buildings, &nb_supermakets);
    create_map_cell(memory, WASTELAND, 3, 1, MAX_CHARACTERS_WASTELAND, &nb_companies, &nb_residential_buildings, &nb_supermakets);
    create_map_cell(memory, WASTELAND, 3, 2, MAX_CHARACTERS_WASTELAND, &nb_companies, &nb_residential_buildings, &nb_supermakets);
    create_map_cell(memory, CITY_HALL, 3, 3, MAX_CHARACTERS_CITY_HALL, &nb_companies, &nb_residential_buildings, &nb_supermakets);
    create_map_cell(memory, COMPANY, 3, 4, MAX_CHARACTERS_COMPANY, &nb_companies, &nb_residential_buildings, &nb_supermakets);
    create_map_cell(memory, WASTELAND, 3, 5, MAX_CHARACTERS_WASTELAND, &nb_companies, &nb_residential_buildings, &nb_supermakets);
    create_map_cell(memory, WASTELAND, 3, 6, MAX_CHARACTERS_WASTELAND, &nb_companies, &nb_residential_buildings, &nb_supermakets);

    create_map_cell(memory, WASTELAND, 4, 0, MAX_CHARACTERS_WASTELAND, &nb_companies, &nb_residential_buildings, &nb_supermakets);
    create_map_cell(memory, RESIDENTIAL_BUILDING, 4, 1, MAX_CHARACTERS_RESIDENTIAL_BUILDING, &nb_companies, &nb_residential_buildings, &nb_supermakets);
    create_map_cell(memory, COMPANY, 4, 2, MAX_CHARACTERS_COMPANY, &nb_companies, &nb_residential_buildings, &nb_supermakets);
    create_map_cell(memory, SUPERMARKET, 4, 3, MAX_CHARACTERS_SUPERMARKET, &nb_companies, &nb_residential_buildings, &nb_supermakets);
    create_map_cell(memory, WASTELAND, 4, 4, MAX_CHARACTERS_WASTELAND, &nb_companies, &nb_residential_buildings, &nb_supermakets);
    create_map_cell(memory, WASTELAND, 4, 5, MAX_CHARACTERS_WASTELAND, &nb_companies, &nb_residential_buildings, &nb_supermakets);
    create_map_cell(memory, RESIDENTIAL_BUILDING, 4, 6, MAX_CHARACTERS_RESIDENTIAL_BUILDING, &nb_companies, &nb_residential_buildings, &nb_supermakets);

    create_map_cell(memory, WASTELAND, 5, 0, MAX_CHARACTERS_WASTELAND, &nb_companies, &nb_residential_buildings, &nb_supermakets);
    create_map_cell(memory, WASTELAND, 5, 1, MAX_CHARACTERS_WASTELAND, &nb_companies, &nb_residential_buildings, &nb_supermakets);
    create_map_cell(memory, COMPANY, 5, 2, MAX_CHARACTERS_COMPANY, &nb_companies, &nb_residential_buildings, &nb_supermakets);
    create_map_cell(memory, WASTELAND, 5, 3, MAX_CHARACTERS_WASTELAND, &nb_companies, &nb_residential_buildings, &nb_supermakets);
    create_map_cell(memory, RESIDENTIAL_BUILDING, 5, 4, MAX_CHARACTERS_RESIDENTIAL_BUILDING, &nb_companies, &nb_residential_buildings, &nb_supermakets);
    create_map_cell(memory, WASTELAND, 5, 5, MAX_CHARACTERS_WASTELAND, &nb_companies, &nb_residential_buildings, &nb_supermakets);
    create_map_cell(memory, COMPANY, 5, 6, MAX_CHARACTERS_COMPANY, &nb_companies, &nb_residential_buildings, &nb_supermakets);

    create_map_cell(memory, RESIDENTIAL_BUILDING, 6, 0, MAX_CHARACTERS_RESIDENTIAL_BUILDING, &nb_companies, &nb_residential_buildings, &nb_supermakets);
    create_map_cell(memory, COMPANY, 6, 1, MAX_CHARACTERS_COMPANY, &nb_companies, &nb_residential_buildings, &nb_supermakets);
    create_map_cell(memory, WASTELAND, 6, 2, MAX_CHARACTERS_WASTELAND, &nb_companies, &nb_residential_buildings, &nb_supermakets);
    create_map_cell(memory, WASTELAND, 6, 3, MAX_CHARACTERS_WASTELAND, &nb_companies, &nb_residential_buildings, &nb_supermakets);
    create_map_cell(memory, RESIDENTIAL_BUILDING, 6, 4, MAX_CHARACTERS_RESIDENTIAL_BUILDING, &nb_companies, &nb_residential_buildings, &nb_supermakets);
    create_map_cell(memory, WASTELAND, 6, 5, MAX_CHARACTERS_WASTELAND, &nb_companies, &nb_residential_buildings, &nb_supermakets);
    create_map_cell(memory, RESIDENTIAL_BUILDING, 6, 6, MAX_CHARACTERS_RESIDENTIAL_BUILDING, &nb_companies, &nb_residential_buildings, &nb_supermakets);
}

void create_map_cell(memory_t * memory, int type, int row, int column, int nb_of_characters, int * nb_companies, int * nb_residential_buildings, int * nb_supermakets) {
    memory->map.cells[row][column].type = type;
    memory->map.cells[row][column].row = row;
    memory->map.cells[row][column].column = column;
    memory->map.cells[row][column].nb_of_characters = nb_of_characters;

    switch(type) {
        case RESIDENTIAL_BUILDING :
            memory->residential_buildings[*nb_residential_buildings].row = row;
            memory->residential_buildings[*nb_residential_buildings].column = column;
            memory->residential_buildings[*nb_residential_buildings].affected_characters = 0;
            *nb_residential_buildings += 1;
        break;
        case CITY_HALL :
            memory->city_hall.row = row;
            memory->city_hall.column = column;
            memory->city_hall.affected_characters = 0;
        break;
        case COMPANY :
            memory->companies[*nb_companies].row = row;
            memory->companies[*nb_companies].column = column;
            memory->companies[*nb_companies].affected_characters = 0;
            *nb_companies += 1;
        break;
        case SUPERMARKET :
            memory->supermarkets[*nb_supermakets].row = row;
            memory->supermarkets[*nb_supermakets].column = column;
            memory->supermarkets[*nb_supermakets].affected_characters = 0;
            *nb_supermakets += 1;
        break;
    }
}

void create_mailbox(memory_t * memory) {
    int random_building = rand()%MAX_RESIDENTIAL_BUILDING;
    memory->mailbox.row = memory->residential_buildings[random_building].row;
    memory->mailbox.column = memory->residential_buildings[random_building].column;
    memory->residential_buildings[random_building].affected_characters += 1;
}

void create_spies(spie_t spies[NUMBER_OF_SPIES], mailbox_t * mailbox, residential_building_t residential_buildings[MAX_RESIDENTIAL_BUILDING]) {
    int i;
    int spie_affected;
    int random_building;
    int licence_to_kill_affected = 0;

    for(i=0; i<NUMBER_OF_SPIES; i++) {
        spie_affected = 0;
        while(!spie_affected) {
            random_building = rand()%MAX_RESIDENTIAL_BUILDING;
            if(manhattan_distance(residential_buildings[random_building].row, residential_buildings[random_building].column, mailbox->row, mailbox->column) < 4 && residential_buildings[random_building].affected_characters < MAX_HABITATION_IN_RESIDENTIAL_BUILING) {
                if(!licence_to_kill_affected && rand()%2) {
                    spies[i].has_license_to_kill = 1;
                    licence_to_kill_affected = 1;
                }
                else {
                    spies[i].has_license_to_kill = 0;
                }
                spies[i].id = i;
                spies[i].health_points = MAX_LIFE_POINTS;
                spies[i].location_row = residential_buildings[random_building].row;
                spies[i].location_column = residential_buildings[random_building].column;
                spies[i].home_row = residential_buildings[random_building].row;
                spies[i].home_column = residential_buildings[random_building].column;
                spies[i].nb_of_stolen_companies = 0;
                residential_buildings[random_building].affected_characters += 1;
                spie_affected = 1;
            }
        }
    }
}

void create_spie(memory * memory, int id, int row, int column) {
    
}

void create_citizens(citizen_t citizens[NUMBER_OF_CITIZENS], residential_building_t residential_buildings[MAX_RESIDENTIAL_BUILDING], company_t companies[MAX_COMPANIES], city_hall_t * city_hall, supermarket_t supermarkets[MAX_SUPERMARKETS]) {
    int i;
    int character_habitation_affected;
    int character_job_affected;
    int random_building;
    int random_job;
    int random_supermarket;
    int random_company;
    
    for(i=0; i<NUMBER_OF_CITIZENS; i++) {
        character_habitation_affected = 0;
        character_job_affected = 0;
        while(!character_habitation_affected && !character_job_affected) {
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
            if(!character_job_affected) {
                random_job = rand()%MAX_JOBS_TYPES;
                switch(random_job) {
                    case SUPERMARKET_JOB :
                        random_supermarket = rand()%MAX_SUPERMARKETS;
                        if(supermarkets[random_supermarket].affected_characters < MAX_AFFECTED_SUPERMARKET) {
                            supermarkets[random_supermarket].affected_characters += 1;
                            citizens[i].job_row = supermarkets[random_supermarket].row;
                            citizens[i].job_column = supermarkets[random_supermarket].column;
                            character_job_affected = 1;
                        }
                    break;
                    case CITY_HALL_JOB :
                        if(city_hall->affected_characters < MAX_AFFECTED_CITY_HALL) {
                            city_hall->affected_characters += 1;
                            citizens[i].job_row = city_hall->row;
                            citizens[i].job_column = city_hall->column;
                            character_job_affected = 1;
                        }
                    break;
                    case COMPANY_JOB :
                        random_company = rand()%MAX_COMPANIES;
                        citizens[i].job_row = companies[random_company].row;
                        citizens[i].job_column = companies[random_company].column;
                        character_job_affected = 1;
                    break;
                }
            }
        }
    }
}

int manhattan_distance(int x1, int y1, int x2, int y2) {
    return abs(x2 - x1) + abs(y2 - y1);
}
