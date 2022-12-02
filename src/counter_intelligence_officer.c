#include "../include/counter_intelligence_officer.h"

position * company_targetted_memory; // List to memorize the company position that the person was in its peripherals (every round)
int * same_cell_counter; // A counter of how many rounds every person stay in the same cell (for every person)

list_of_people = (person *)malloc((NB_PEOPLE - 1) * sizeof(person)); // mines 1 because we want people information except counter intelligence officer ones
same_cell_counter = (int *)calloc(NB_PEOPLE - 1, sizeof(int)); // All initialized to zero
    

counter_officer * memory_alloc_counter_officer(){
    counter_officer * cio;
    cio = (counter_officer *)malloc(sizeof(counter_officer));
    cio->position = (position *)malloc(sizeof(position));
    cio->city_hall_pos = (position *)malloc(sizeof(position));
    cio->mailbox_pos = (position *)malloc(sizeof(position));
    retrun cio;
}

void init_counter_officer(counter_officer * cio){
    id = getpid();
    health = 10;
    cio->city_hall_pos->x = CITY_HALL_X;
    cio->city_hall_pos->y = CITY_HALL_Y;
    cio->position->x = CITY_HALL_X;
    cio->position->y = CITY_HALL_Y;
    cio->mailbox_pos->x = 0;
    cio->mailbox_pos->y = 0;
    return;
}


/**
*@brief Load people list and control lists that will be used to discover if there is any spy
*/
void people_surveillance(city * city){
    int fd;
    int i, j, p;
    // position * company_targetted_memory; // List to memorize the company position that the person was in its peripherals (every round)
    // int * same_cell_counter; // A counter of how many rounds every person stay in the same cell (for every person)  
    person * list_of_people; // citizen is a structure to be implemented
    
    company_targetted_memory = (person *)malloc((NB_PEOPLE - 1) * sizeof(position)); 
    // list_of_people = (person *)malloc((NB_PEOPLE - 1) * sizeof(person)); // mines 1 because we want people information except counter intelligence officer ones
    // same_cell_counter = (int *)calloc(NB_PEOPLE - 1, sizeof(int)); // All initialized to zero
    
    fd = shm_open("/shared_memory", O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP); // substitute "/shared_memory" by the name of shared memory
    if(fd == -1){
        log_error("shm_open() problem");
        return NULL;
    }

    list_of_people = mmap(NULL, sizeof(list_of_people), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (list_of_people == MAP_FAILED) {
        log_error("mmap() problem!");
        return NULL;
    }

    for( p = 0; p < NB_PEOPLE - 1; ++p){
        int location_x = list_of_people[i]->location->x;
        int location_y = list_of_people[i]->location->y;
        if(location_x > GRID_WIDTH || location_x < 1){
            perror("location_x out of bound\n");
            exit(EXIT_FAILURE);
        }
        if(location_y > GRID_HEIGHT || location_y < 1){
            perror("location_y out of bound\n");
            exit(EXIT_FAILURE);
        }
        for( i = -1; i <= 1; ++i){
            for( j = -1; j <= 1; ++j){
                if(i == 0 && j == 0){
                    continue;
                }
                if(city->grid[location_x + i][location_y + j].type == COMPANY){
                    if(company_targetted_memory[p]->x == location_x + i && company_targetted_memory[p]->y == location_y + j){
                        same_cell_counter[p]++;
                    }
                    else {
                        company_targetted_memory[p]->x = location_x + i;
                        company_targetted_memory[p]->y = location_y + j;
                        same_cell_counter[p] = 0;
                    }
                }
                
            }
        }
    }
}

/**
*@brief returns the index of a suspect in the people list
*/
int there_is_suspect(){
    for(int p = 0; p < NB_PEOPLE - 1; ++p){
        if(same_cell_counter[p] >= NB_ROUNDS_SUSPECT){
            return p;
        }
    }
}

/**
*@brief After finding the index of suspect by the "there_is_suspect", this function returns the company targetted
*/
position * company_targetted_by_suspect(int suspect_index){
    return company_targetted_memory[suspect_index];
}


/* I need now to implement a function which move the counter intelligence officer to the targetted company */

