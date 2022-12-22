#include "spy_simulation.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <signal.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/mman.h> 
#include <string.h>
#include <sys/stat.h>
#include "posix_semaphore.h"
#include "functions.h"
#include "mesh_surveillance_network.h"

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
    memory->mailbox.number_of_messages = 0;
    memory->mailbox.messages = NULL;
    memory->mailbox.occupied = 0;
    memory->mailbox.informations = (char **)malloc(sizeof(char*) * 20);
    for(int i = 0; i < 20; i++){
        memory->mailbox.informations[i] = (char*) malloc(sizeof(char) * MAX_LENGTH_OF_MESSAGE);
    }
    memory->mailbox.index_of_next_msg = 0;

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
            break;
        case SIGTERM:
            break;
         case SIGINT:
            exit(0);
        default:
            break;
    }
}

void mesh_surveillance_network(memory_t * memory) {
    int i, j, u, v, company_near, working, at_home;

    character_t *characters = get_characters(memory);

    for(i=0; i<NUMBER_OF_CHARACTERS-1; i++) {
        company_near = 0;
        working = 0;
        at_home = 0;

        for(j = 0; j<MAX_COMPANIES; j++) {
            if(characters[i].row == memory->companies[j].row && characters[i].column == memory->companies[j].column) {
                working = 1;
            }
        }
        for(j = 0; j<MAX_RESIDENTIAL_BUILDING; j++) {
            if(characters[i].row == memory->residential_buildings[j].row && characters[i].column == memory->residential_buildings[j].column) {
                at_home = 1;
            }
        }
        //If not working in a company
        if(!working && !at_home) {
            for(u=characters[i].row -1; u <= characters[i].row +1; u++) {
                for(v=characters[i].column -1; v <= characters[i].column +1; v++) {
                    if(u >= 0 && u < MAX_ROWS && v >= 0 && v < MAX_COLUMNS) {
                        for(j = 0; j<MAX_COMPANIES; j++) {
                            if(u == memory->companies[j].row && v == memory->companies[j].column) {
                                company_near = 1;
                            }
                        }
                    }
                }
            }
            //If character is near of a company
            if(company_near) {
                memory->mesh_surveillance_network.near_company[characters[i].id] += 1;
                //If he is near a company for 10 rounds, send a SIGALARM
                if(memory->mesh_surveillance_network.near_company[characters[i].id] >= NUMBER_SUSPICIOUS_ROUND) {
                    memory->mesh_surveillance_network.id_suspicious_character = characters[i].id;
                    int fd;
                    mkfifo("counterintellifence_officer", 0666);
                    fd = open("counterintellifence_officer", O_RDWR);
                    char buff[20];
                    sprintf(buff, "%d %d %d", characters[i].id, characters[i].row, characters[i].column);
                    if(write(fd, buff, strlen(buff)+1) != -1){
                        kill(memory->counter_intelligence_officer_pid, SIGALRM);
                    }
                    close(fd);
                }
            }
        }
    }
}

character_t * get_characters(memory_t * memory) {
    character_t * characters;
    characters = (character_t *)malloc(sizeof(character_t) * NUMBER_OF_CHARACTERS-1);
    int i;
    characters[0].row = memory->case_officer.location_row;
    characters[0].column = memory->case_officer.location_column;
    characters[0].id = memory->case_officer.id;
    for(i = 0; i < NUMBER_OF_SPIES; i++) {
        characters[i+1].row = memory->spies[i].location_row;
        characters[i+1].column = memory->spies[i].location_column;
        characters[i+1].id = memory->spies[i].id;
    }
    for(i = 0; i < NUMBER_OF_CITIZENS; i++) {
        characters[i+1+NUMBER_OF_SPIES].row = memory->citizens[i].location_row;
        characters[i+1+NUMBER_OF_SPIES].column = memory->citizens[i].location_column;
        characters[i+1+NUMBER_OF_SPIES].id = memory->citizens[i].id;
    } 
    return characters;
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
    mesh_surveillance_network(memory);

    munmap(memory, sizeof(memory_t));
    close(shmd);
    V(sem);
}

void set_companies_informations(memory_t * memory) {
    int i, j, random_importance;

    for(i=0; i<MAX_COMPANIES; i++) {
        random_importance = rand()%MAX_COMPANY_TYPES;
        memory->companies[i].type = random_importance;
        switch(random_importance) {
            case CRUTIAL : 
                if(memory->companies[i].affected_characters > COMPANY_CRUCIAL_EMPLOYEES) {
                    memory->companies[i].number_informations = COMPANY_CRUCIAL_GREATER_INFORMATIONS;
                }
                else {
                    memory->companies[i].number_informations = COMPANY_CRUCIAL_SMALLER_INFORMATIONS;
                }
            break;
            case STRONG : 
                if(memory->companies[i].affected_characters > COMPANY_STRONG_EMPLOYEES) {
                    memory->companies[i].number_informations = COMPANY_STRONG_GREATER_INFORMATIONS;
                }
                else {
                    memory->companies[i].number_informations = COMPANY_STRONG_SMALLER_INFORMATIONS;
                }
            break;
            case MEDIUM : 
                if(memory->companies[i].affected_characters > COMPANY_MEDIUM_EMPLOYEES) {
                    memory->companies[i].number_informations = COMPANY_MEDIUM_GREATER_INFORMATIONS;
                }
                else {
                    memory->companies[i].number_informations = COMPANY_MEDIUM_SMALLER_INFORMATIONS;
                }
            break;
            case LOW : 
                if(memory->companies[i].affected_characters > COMPANY_LOW_EMPLOYEES) {
                    memory->companies[i].number_informations = COMPANY_LOW_GREATER_INFORMATIONS;
                }
                else {
                    memory->companies[i].number_informations = COMPANY_LOW_SMALLER_INFORMATIONS;
                }
            break;
            case VERY_LOW : 
                if(memory->companies[i].affected_characters > COMPANY_VERY_LOW_EMPLOYEES) {
                    memory->companies[i].number_informations = COMPANY_VERY_LOW_GREATER_INFORMATIONS;
                }
                else {
                    memory->companies[i].number_informations = COMPANY_VERY_LOW_SMALLER_INFORMATIONS;
                }
            break;
        }
        if(memory->companies[i].number_informations > 0) {
            memory->companies[i].informations = (char **)malloc(memory->companies[i].number_informations*sizeof(char*));
            for(j = 0; j<memory->companies[i].number_informations; j++) {
                memory->companies[i].informations[j] = (char *)malloc(sizeof(char)*MAX_LENGTH_OF_MESSAGE);
                sprintf(memory->companies[i].informations[j], "Information n°%d de l'entreprise n°%d", j, i);
            }
        }
    }
}
