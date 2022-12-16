#include "citizen_manager.h"

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "functions.h"

int get_hour(memory_t *memory) {
    return ((int) floor((memory->count/6)))%24;
}

int get_minutes(memory_t *memory) {
    return (memory->count * 10)%60;
}

void get_next_cell(memory_t *memory, int citizen_index, int destination_row, int destination_column, int * next_row, int * next_column) {
    int i, j, random_cell;
    int count_reachable_cells = 0;
    int reachable_cells_row[8];
    int reachable_cells_column [8];
    
    for(i = memory->citizens[citizen_index].location_row - 1; i <= memory->citizens[citizen_index].location_row + 1; i++) {
        for(j = memory->citizens[citizen_index].location_column - 1; j <= memory->citizens[citizen_index].location_column + 1; j++) {
            if(i >= 0 && i < MAX_ROWS && j >= 0 && j < MAX_COLUMNS) {
                if(manhattan_distance(i, j, destination_row, destination_column) < manhattan_distance(memory->citizens[citizen_index].location_row, memory->citizens[citizen_index].location_column, destination_row, destination_column)) {
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

void *make_round(void * args) {
    int next_row, next_column, destination_row, destination_column;

    args_t * arguments = (args_t *) args;
    memory_t * memory = arguments->memory;
    int citizen_index = arguments->citizen_index;

    int hour = get_hour(memory);
    int minutes = get_minutes(memory);
    int location_row = memory->citizens[citizen_index].location_row;
    int location_column = memory->citizens[citizen_index].location_column;
    int work_row = memory->citizens[citizen_index].work_row;
    int work_column = memory->citizens[citizen_index].work_column;
    int work = memory->citizens[citizen_index].work;
    int home_row = memory->citizens[citizen_index].home_row;
    int home_column = memory->citizens[citizen_index].home_column;
    int need_to_shop;

    if(hour == 0 && minutes == 0) {
        memory->citizens[citizen_index].shopping = rand()%4 == 1;
    }
    need_to_shop = memory->citizens[citizen_index].shopping;

    if(hour >= 8 && ((work != SUPERMARKET_WORK && hour < 17) || (work == SUPERMARKET_WORK && (hour < 19 || (hour == 19 && minutes < 30))))) {
        destination_row = work_row;
        destination_column = work_column;
    }
    else if(need_to_shop && (work != SUPERMARKET_WORK && hour > 17)) {
        int random_supermarket = rand()%MAX_SUPERMARKETS;
        destination_row = memory->supermarkets[random_supermarket].row;
        destination_column = memory->supermarkets[random_supermarket].column;
    }
    else {
        destination_row = home_row;
        destination_column = home_column;
    }
    if(destination_row == location_row && destination_column == location_column) {
        next_row = destination_row;
        next_column = destination_column;
    }
    else {
        get_next_cell(memory, citizen_index, destination_row, destination_column, &next_row, &next_column);
    }

    for(int i =0; i<MAX_SUPERMARKETS; i++) {
        if(next_row == memory->supermarkets[i].row && next_column == memory->supermarkets[i].column) {
            memory->citizens[citizen_index].shopping = 0;
        }
    }
    memory->citizens[citizen_index].location_row = next_row;
    memory->citizens[citizen_index].location_column = next_column;

    if(memory->citizens[citizen_index].location_row == memory->citizens[citizen_index].home_row && memory->citizens[citizen_index].location_column == memory->citizens[citizen_index].home_column) {
        memory->citizens_at_home += 1;
    }
    else if(memory->citizens[citizen_index].location_row == memory->citizens[citizen_index].work_row && memory->citizens[citizen_index].location_column == memory->citizens[citizen_index].work_column) {
        memory->citizens_at_work += 1;
    }
    else {
        memory->citizens_walking+= 1;
    }
    return NULL;
}