#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <math.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/stat.h>
// #include <pthread.h>
#include <time.h>
#include "posix_semaphore.h"
#include "spy_simulation.h"
#include "functions.h"
#include "memory.h"
#include "cell.h"


int get_hour(memory_t *memory) {
    return ((int) floor((memory->count/6)))%24;
}

int get_minutes(memory_t *memory) {
    return (memory->count * 10)%60;
}

int manhattan_distance(int x1, int y1, int x2, int y2){
    return abs(x2 - x1) + abs(y2 - y1);
}

void get_next_cell(memory_t *memory, int destination_row, int destination_column, int * next_row, int * next_column) {
    int i, j, random_cell;
    int count_reachable_cells = 0;
    int reachable_cells_row[8];
    int reachable_cells_column [8];
    
    for(i = memory->case_officer.location_row - 1; i <= memory->case_officer.location_row + 1; i++) {
        for(j = memory->case_officer.location_column - 1; j <= memory->case_officer.location_column + 1; j++) {
            if(i >= 0 && i < MAX_ROWS && j >= 0 && j < MAX_COLUMNS) {
                if(manhattan_distance(i, j, destination_row, destination_column) < manhattan_distance(memory->case_officer.location_row, memory->case_officer.location_column, destination_row, destination_column)) {
                    reachable_cells_row[count_reachable_cells] = i;
                    reachable_cells_column[count_reachable_cells] = j;
                    count_reachable_cells += 1;
                }
            }
        }
    } 
    
    random_cell = rand()%count_reachable_cells;
    *next_row = reachable_cells_row[random_cell];
    *next_column = reachable_cells_column[random_cell];
}

void move_to_supermarket(memory_t * memory){
    int random_supermarket_index;
    do{
        random_supermarket_index = rand()%MAX_SUPERMARKETS;
    }while(memory->supermarkets[random_supermarket_index].affected_characters >= MAX_CHARACTERS_SUPERMARKET); // MAX_CHARACTERS_SUPERMARKET à modifier sur common.h

    // int random_supermarket_index = memory->case_officer.random_chosen_supermarket_index;
    // int case_office_location_row = memory->case_officer.location_row;
    // int case_officer_location_column = memory->case_officer.location_column
    int supermarket_visited = memory->case_officer.supermarket_visited;
    int supermarket_row = memory->supermarkets[random_supermarket_index].row;
    int supermarket_column = memory->supermarkets[random_supermarket_index].column;
    
    
    if(!supermarket_visited){
        get_next_cell(memory, memory->supermarkets[random_supermarket_index].row, memory->supermarkets[random_supermarket_index].column, &(memory->case_officer.location_row), &(memory->case_officer.location_column));
    }
    else if(memory->case_officer.location_row == supermarket_row && memory->case_officer.location_column == supermarket_column){
        supermarket_visited = 1;
    }   
}

void move_back_home(memory_t * memory){
    if(memory->case_officer.location_row == memory->case_officer.home_row && memory->case_officer.location_column == memory->case_officer.home_column){
        printf("case officer is already at home\n");
    }
    else{
        get_next_cell(memory, memory->case_officer.home_row, memory->case_officer.home_column, &(memory->case_officer.location_row), &(memory->case_officer.location_column));
    }
}

void move_to_mailbox(memory_t * memory){
    
}

void case_officer_routine(memory_t * memory){
    int hour = get_hour(memory);
    if(hour >= 17 && hour <= 19){
        if(memory->case_officer.supermarket_visited == 0){
            move_to_supermarket(memory);
        }
        else if(memory->case_officer.supermarket_visited == 1){
            move_back_home(memory);
        }
    }
}

int main(void){
    int shmd;
    sem_t *sem;
    memory_t *memory;

    srand(time(NULL));
    
    sem = open_semaphore("spy_simulation-sem");
    P(sem);
    shmd = shm_open("/spy_simulation", O_RDWR, 0666);
    memory = mmap(NULL, sizeof(memory_t), PROT_READ | PROT_WRITE, MAP_SHARED, shmd, 0);

    /*case officer information initialization*/
    memory->case_officer.supermarket_visited = 0;
    memory->case_officer.random_chosen_supermarket_index = -1;
    /*end case officer information initialization*/

    munmap(memory, sizeof(memory_t));
    close(shmd);
    V(sem);

    while(1){
        sem = open_semaphore("spy_simulation-sem");
        P(sem);
        shmd = shm_open("/spy_simulation", O_RDWR, 0666);
        memory = mmap(NULL, sizeof(memory_t), PROT_READ | PROT_WRITE, MAP_SHARED, shmd, 0);

        /*case officer information initialization*/
        memory->case_officer.supermarket_visited = 0;
        memory->case_officer.random_chosen_supermarket_index = -1;
        /*end case officer information initialization*/

        case_officer_routine(memory);

        
        munmap(memory, sizeof(memory_t));
        close(shmd);
        V(sem);
    }

}