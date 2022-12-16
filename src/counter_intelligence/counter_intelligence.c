#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "../../include/counter_intelligence.h"




int get_hour(memory_t *memory) {
    return ((int) floor((memory->count/6)))%24;
}

int get_minutes(memory_t *memory) {
    return (memory->count * 10)%60;
}


bool is_citizen_in_cell( cell_t* cell,citizen_t citizen ){
    return ((cell->row == citizen.location_row) && (cell->column == citizen.location_column));
}

void update_detection(cell_t* cell, citizen_t citizen){
    if (is_citizen_in_cell(cell, citizen)){
        *(cell->detection->counter)++;
    }
    else { *(cell->detection->counter)= 0;}
    if (*(cell->detection->counter) > 5){
        cell->detection->expected_spy = true;
        *(cell->detection->counter) = 0; 
    }    
}


void detect_anomaly(memory_t *memory){
    for (int k = 0; k < MAX_COMPANIES; k++){
        company_t* company = &(memory->companies[k]);
        for (int i = -1; i = 1; i++){
            if ((company->row)+i < 0 || (company->row)+i > 6){ continue;}
            for (int j = -1; j=1; j++){
                if ((company->column)+j < 0 || (company->column)+j > 6){ continue;}
                cell_t* neighbour = &(memory->map.cells[(company->row)+i][(company->column)+j]);
                for (int i = 0; i < NUMBER_OF_CITIZENS; i++){
                    update_detection(neighbour, memory->citizens[i]);
                    }
                }
        }
    }
}




