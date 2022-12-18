#include "spy_simulation.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <signal.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/mman.h> 
#include <sys/stat.h>
#include "posix_semaphore.h"
#include "functions.h"

memory_t * create_memory() {
    memory_t * memory = (memory_t *) malloc(sizeof(memory_t));
    create_map(memory);
    create_mailbox(memory);
    create_characters(memory);
    memory->count = 0;
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

void create_characters(memory_t * memory) {
    int nb_citizens = 0;
    int nb_spies = 0;
    int i;
    int character_created;
    int random_building;
    int random_work_type;
    int random_work_building;
    int j;

    for(i=0; i<NUMBER_OF_SPIES; i++) {
        character_created = 0;
        while(!character_created) {
            random_building = rand()%MAX_RESIDENTIAL_BUILDING;
            if(manhattan_distance(memory->residential_buildings[random_building].row, memory->residential_buildings[random_building].column, memory->mailbox.row, memory->mailbox.column) < 4 && memory->residential_buildings[random_building].affected_characters < MAX_HABITATION_IN_RESIDENTIAL_BUILING) {
                create_character(memory, i, SPY, memory->residential_buildings[random_building].row, memory->residential_buildings[random_building].column, 0, 0, 0, NULL, &nb_spies);
                memory->residential_buildings[random_building].affected_characters += 1;
                character_created = 1;
            }
        }
    }

    character_created = 0;
    while(!character_created) {
        random_building = rand()%MAX_RESIDENTIAL_BUILDING;
        if(manhattan_distance(memory->residential_buildings[random_building].row, memory->residential_buildings[random_building].column, memory->mailbox.row, memory->mailbox.column) < 4 && memory->residential_buildings[random_building].affected_characters < MAX_HABITATION_IN_RESIDENTIAL_BUILING) {
            create_character(memory, NUMBER_OF_SPIES, CASE_OFFICER, memory->residential_buildings[random_building].row, memory->residential_buildings[random_building].column, 0, 0, 0, NULL, &nb_spies);
            memory->residential_buildings[random_building].affected_characters += 1;
            character_created = 1;
        }
    }

    create_character(memory, NUMBER_OF_SPIES+1, COUNTER_OFFICER, 0, 0, memory->city_hall.row, memory->city_hall.column, 0, NULL, NULL);

    for(i=NUMBER_OF_SPIES+2; i<NUMBER_OF_CHARACTERS; i++) {
        int residential_ok = 0;
        int work_ok = 0;
        int work_row, work_column, home_row, home_column;
        while(!residential_ok) {
            random_building = rand()%MAX_RESIDENTIAL_BUILDING;
            if(memory->residential_buildings[random_building].affected_characters < MAX_HABITATION_IN_RESIDENTIAL_BUILING) {
                memory->residential_buildings[random_building].affected_characters += 1;
                home_row = memory->residential_buildings[random_building].row;
                home_column = memory->residential_buildings[random_building].column;
                residential_ok = 1;
            }
        }
        while(!work_ok) {
            random_work_type = rand()%MAX_JOBS_TYPES;
            switch(random_work_type) {
                case COMPANY_WORK :
                    random_work_building = random()%MAX_COMPANIES;
                    for(j = 0; j < MAX_COMPANIES; j++) {
                        if(memory->companies[j].affected_characters < 5) {
                            memory->companies[j].affected_characters += 1;
                            work_row = memory->companies[j].row;
                            work_column = memory->companies[j].column;
                            work_ok = 1;
                        }
                    }
                    if(!work_ok) {
                        memory->companies[random_work_building].affected_characters += 1;
                        work_row = memory->companies[random_work_building].row;
                        work_column = memory->companies[random_work_building].column;
                        work_ok = 1;
                    }
                break;
                case SUPERMARKET_WORK :
                    random_work_building = random()%MAX_SUPERMARKETS;
                    if(memory->supermarkets[random_work_building].affected_characters < MAX_AFFECTED_SUPERMARKET) {
                        memory->supermarkets[random_work_building].affected_characters += 1;
                        work_row = memory->supermarkets[random_work_building].row;
                        work_column = memory->supermarkets[random_work_building].column;
                        work_ok = 1;
                    }
                break;
                case CITY_HALL_WORK :
                    if(memory->city_hall.affected_characters < MAX_AFFECTED_CITY_HALL) {
                        memory->city_hall.affected_characters += 1;
                        work_row = memory->city_hall.row;
                        work_column = memory->city_hall.column;
                        work_ok = 1;
                    }
                break;
            }
        }
        create_character(memory, i, CITIZEN, home_row, home_column, work_row, work_column, random_work_type, &nb_citizens, NULL);
    }
}

void create_character(memory_t * memory, int id, character_type_t type, int home_row, int home_column, int work_row, int work_column, work_type_t work, int * nb_citizens, int * nb_spies) {
    switch (type)
    {
    case CITIZEN :
        memory->citizens[*nb_citizens].id = id;
        memory->citizens[*nb_citizens].location_row = home_row;
        memory->citizens[*nb_citizens].location_column = home_column;
        memory->citizens[*nb_citizens].home_row = home_row;
        memory->citizens[*nb_citizens].home_column = home_column;
        memory->citizens[*nb_citizens].work_row = work_row;
        memory->citizens[*nb_citizens].work_column = work_column;
        memory->citizens[*nb_citizens].work = work;
        memory->citizens[*nb_citizens].health_points = MAX_LIFE_POINTS;
        *nb_citizens += 1;
        break;
    case SPY:
        memory->spies[*nb_spies].id = id;
        memory->spies[*nb_spies].location_row = home_row;
        memory->spies[*nb_spies].location_column = home_column;
        memory->spies[*nb_spies].home_row = home_row;
        memory->spies[*nb_spies].home_column = home_column;
        memory->spies[*nb_spies].health_points = MAX_LIFE_POINTS;
        memory->spies[*nb_spies].nb_of_stolen_companies = 0;
        memory->spies[*nb_spies].has_license_to_kill = *nb_spies == 0 ? 1 : 0;
        *nb_spies += 1;
        break;
    case CASE_OFFICER:
        memory->case_officer.id = id;
        memory->case_officer.location_row = home_row;
        memory->case_officer.location_column = home_column;
        memory->case_officer.home_row = home_row;
        memory->case_officer.home_column = home_column;
        memory->case_officer.health_points = MAX_LIFE_POINTS;
        break;
    case COUNTER_OFFICER:
        memory->counter_officer.id = id;
        memory->counter_officer.location_row = work_row;
        memory->counter_officer.location_column = work_column;
        memory->counter_officer.health_points = MAX_LIFE_POINTS;
        break;
    }
}

void set_signal_handler() {
    struct sigaction action;
    action.sa_handler = signal_handler;
    action.sa_flags = 0;
    sigemptyset(&action.sa_mask);

    sigaction(SIGTERM, &action, NULL);

    sigaction(SIGALRM, &action, NULL);

    action.sa_handler = SIG_IGN;
    sigaction(SIGTSTP, &action, NULL);
}

void signal_handler(int signum) {
    switch (signum) {
        case SIGALRM:
            new_round();
           // printf("signal SIGALRM\n");
            break;
        case SIGTERM:
            //printf("signal SIGTERM\n");
            break;
         case SIGINT:
            //printf("signal SIGINT\n");
            exit(0);
        default:
            break;
    }
}

void new_round() {
    memory_t * memory;
    sem_t *sem;
    sem = open_semaphore("spy_simulation-sem");
    P(sem);
    int shmd = shm_open("/spy_simulation", O_CREAT | O_RDWR, (mode_t)0600);
    memory = mmap(NULL, sizeof(memory_t), PROT_READ | PROT_WRITE, MAP_SHARED, shmd,0);
    memory->count += 1;
    memory->memory_has_changed = 1;
    munmap(memory, sizeof(memory_t));
    close(shmd);
    V(sem);
}
