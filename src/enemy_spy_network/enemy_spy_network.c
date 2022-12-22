#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <math.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <pthread.h>
#include <time.h>
#include "posix_semaphore.h"
#include "spy_simulation.h"
#include "functions.h"
#include "memory.h"
#include "cell.h"
#include "enemy_spy_network.h"
#include "character.h"
#include <string.h>



void get_next_cell(memory_t *memory, int spie_index, int destination_row, int destination_column, int * next_row, int * next_column) {
    int i, j, random_cell;
    int count_reachable_cells = 0;
    int reachable_cells_row[8];
    int reachable_cells_column [8];
    
    for(i = memory->spies[spie_index].location_row - 1; i <= memory->spies[spie_index].location_row + 1; i++) {
        for(j = memory->spies[spie_index].location_column - 1; j <= memory->spies[spie_index].location_column + 1; j++) {
            if(i >= 0 && i < MAX_ROWS && j >= 0 && j < MAX_COLUMNS ) {
                if(manhattan_distance(i, j, destination_row, destination_column) < manhattan_distance(memory->spies[spie_index].location_row, memory->spies[spie_index].location_column, destination_row, destination_column)) {
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

int get_msg_from_company(memory_t *memory, int spie_index, int probability_of_success) {
    int next_row = 0, next_column = 0, decide_to_stole = rand()%100;
    int rand_index_of_stolen_msg = rand()%memory->companies[memory->spies[spie_index].index_company_being_stolen].number_informations;
    if(decide_to_stole < probability_of_success) {
        memory->spies[spie_index].location_row = next_row;
        memory->spies[spie_index].location_column = next_column;
        memory->spies[spie_index].nb_of_stolen_companies++;
      
        strcpy(memory->spies[spie_index].stolen_message_content, memory->companies[memory->spies[spie_index].index_company_being_stolen].informations[rand_index_of_stolen_msg]);
        int random_importance_msg = rand() % 100 + 1;
        if(random_importance_msg == 1){
            memory->spies[spie_index].message_importance = CRUTIAL;
        }
        else if(random_importance_msg > 1 && random_importance_msg <= 6){
            memory->spies[spie_index].message_importance = STRONG;
        }
        else if(random_importance_msg > 6 && random_importance_msg <= 20){
            memory->spies[spie_index].message_importance = MEDIUM;
        }
        else if(random_importance_msg > 20 && random_importance_msg <= 50){
            memory->spies[spie_index].message_importance = LOW;
        }
        else{
            memory->spies[spie_index].message_importance = VERY_LOW;
        }
        return 1;
    }
    return 0;
}


void night_routine(memory_t *memory, int spie_index) {
     switch(spie_index){
        
        case 1:
            usleep(4000);
            break;
        case 2:
            usleep(8000);
            break;
        default:
            break;
    }

    int company_row = 0, company_col = 0, next_row = 0, next_column = 0;

    if(memory->spies[spie_index].round_number_before_stole == 0 && ! memory->spies[spie_index].go_to_put_msg_in_mailbox) {
        memory->spies[spie_index].index_company_being_stolen  = rand()%MAX_COMPANIES;
        while(memory->spies[spie_index].companies_stolen_yet[memory->spies[spie_index].index_company_being_stolen]) {
            memory->spies[spie_index].index_company_being_stolen  = rand()%MAX_COMPANIES;
        }
        memory->spies[spie_index].companies_stolen_yet[memory->spies[spie_index].index_company_being_stolen] = 1;
        memory->spies[spie_index].round_number_before_stole++;
    
    }else {
        company_row = memory->companies[memory->spies[spie_index].index_company_being_stolen].row;
        company_col = memory->companies[memory->spies[spie_index].index_company_being_stolen].column;
        get_next_cell(memory, spie_index, company_row, company_col, &next_row, &next_column);
        if(memory->spies[spie_index].round_number_before_stole <= 12 && next_row == company_row && next_column == company_col) {
            if(memory->spies[spie_index].round_number_before_stole < 12) {
                memory->spies[spie_index].round_number_before_stole++;
            
            } else {
                if(!get_msg_from_company(memory, spie_index, 86)) {

                    get_next_cell(memory, spie_index, memory->mailbox.row, memory->mailbox.column, &next_row, &next_column);
                    if(next_row == memory->mailbox.row && next_column == memory->mailbox.column) {
            
                            memory->spies[spie_index].location_row = next_row;
                            memory->spies[spie_index].location_column = next_column;
                            strcpy(memory->mailbox.informations[memory->mailbox.index_of_next_msg], memory->spies[spie_index].stolen_message_content);
                            memory->spies[spie_index].go_to_put_msg_in_mailbox = 0;
                            memory->mailbox.index_of_next_msg++;
                    
                    }
                    else {
                        memory->spies[spie_index].go_to_put_msg_in_mailbox = 1;
                        memory->spies[spie_index].location_row = next_row;
                        memory->spies[spie_index].location_column = next_column;
                    }
                }
                else {  
                     memory->spies[spie_index].go_to_put_msg_in_mailbox = 1;
                }
                memory->spies[spie_index].round_number_before_stole++;
            }
        } else if(memory->spies[spie_index].go_to_put_msg_in_mailbox && memory->spies[spie_index].round_number_before_stole > 12){
     
            get_next_cell(memory, spie_index, memory->mailbox.row, memory->mailbox.column, &next_row, &next_column);
            if(next_row == memory->mailbox.row && next_column == memory->mailbox.column) {
                   memory->spies[spie_index].location_row = next_row;
                   memory->spies[spie_index].location_column = next_column;
                   strcpy(memory->mailbox.informations[memory->mailbox.index_of_next_msg], memory->spies[spie_index].stolen_message_content);
                   memory->spies[spie_index].go_to_put_msg_in_mailbox = 0;
                   memory->mailbox.index_of_next_msg++;
            }
            else {
                memory->spies[spie_index].location_row = next_row;
                memory->spies[spie_index].location_column = next_column;
            }
            memory->spies[spie_index].round_number_before_stole++;
            
        } else if(!memory->spies[spie_index].go_to_put_msg_in_mailbox && memory->spies[spie_index].round_number_before_stole > 12 && memory->spies[spie_index].round_number_before_stole < 19){
        
            get_next_cell(memory, spie_index, company_row, company_col, &next_row, &next_column);
            if(next_row == company_row && next_column == company_col) {
                memory->spies[spie_index].round_number_before_stole++;
                if(!get_msg_from_company(memory, spie_index, 90)) {
                    memory->spies[spie_index].round_number_before_stole = 0;
                }  
                else {
                    memory->spies[spie_index].go_to_put_msg_in_mailbox = 1;
                }
            }
            else {
                memory->spies[spie_index].location_row = next_row;
                memory->spies[spie_index].location_column = next_column;
                memory->spies[spie_index].round_number_before_stole++;
            }
        }
        else {
            if(memory->spies[spie_index].round_number_before_stole >=19)  {
                memory->spies[spie_index].round_number_before_stole = 0;
                memory->spies[spie_index].go_to_put_msg_in_mailbox = 0;

            }
            else {
                memory->spies[spie_index].location_row = next_row;
                memory->spies[spie_index].location_column = next_column;
                memory->spies[spie_index].round_number_before_stole++;
            }
        }
    }

}

void day_routine(memory_t *memory, int spie_index) {
    int destination_row = 0, destination_col = 0, next_row = 0, next_column = 0;
    int hour = get_hour(memory);
        if(hour == 8) {
            memory->spies[spie_index].rand_day_routine = rand()%100;
        }
        if(memory->spies[spie_index].hour != hour ) {
            memory->spies[spie_index].hour = hour;
            memory->spies[spie_index].rand_day_routine = rand()%100;
            memory->spies[spie_index].shopping = 0;
            memory->spies[spie_index].stroll_in_city = 0;
            memory->spies[spie_index].stay_at_home = 0;
        }
        else {
            if(memory->spies[spie_index].rand_day_routine <= 30) {
                destination_row = memory->spies[spie_index].home_row;
                destination_col = memory->spies[spie_index].home_column;
                memory->spies[spie_index].stay_at_home = 1;
             //   printf("spie chez lui\n");
                memory->spies[spie_index].shopping = 0;
                memory->spies[spie_index].stroll_in_city = 0;
            } 
            else if(memory->spies[spie_index].rand_day_routine > 30 && memory->spies[spie_index].rand_day_routine < 40) {
                if(memory->spies[spie_index].shopping == 0) {
                    memory->spies[spie_index].random_supermarket = rand()%MAX_SUPERMARKETS;
                }
               // printf("spie supermarché\n");

                destination_row = memory->supermarkets[memory->spies[spie_index].random_supermarket].row;
                destination_col = memory->supermarkets[memory->spies[spie_index].random_supermarket].column;
                memory->spies[spie_index].shopping = 1;
                memory->spies[spie_index].stay_at_home = 0;
                memory->spies[spie_index].stroll_in_city = 0;
            } else {
                destination_row = rand()%6;
                destination_col = rand()%6;
                memory->spies[spie_index].stroll_in_city = 1;
                memory->spies[spie_index].stay_at_home = 0;
                memory->spies[spie_index].shopping = 0;
            }
        }
        if(destination_row == memory->spies[spie_index].location_row && destination_col == memory->spies[spie_index].location_column) {
            next_row = destination_row;
            next_column = destination_col;
        }
        else {
            get_next_cell(memory, spie_index, destination_row, destination_col, &next_row, &next_column);

        }
        memory->spies[spie_index].location_row = next_row;
        memory->spies[spie_index].location_column = next_column;
}


void *spie_routine(void *args) {

    args_spy * arguments = (args_spy *) args;
    memory_t * memory = arguments->memory;
    int spie_index = arguments->spie_index;
    int hour = get_hour(memory);

    if(hour==17) {
        memory->spies[spie_index].rand_time_for_stoling  = (rand()%100) + 1;
    //    printf("c'est 17h 00\n");
    }
    //In the night between 17H and 8H
    //printf("memory->spies[spie_index].rand_time_for_stoling = %d\n", memory->spies[spie_index].rand_time_for_stoling);
    if(hour >= 17 || hour < 8) {
        memory->spies[spie_index].is_stolling = 1;
        memory->spies[spie_index].shopping = 0;
        memory->spies[spie_index].stroll_in_city = 0;
      //  printf(" spie entre 17h et 8h\n");
        if(hour >= 17 && hour < 20 && memory->spies[spie_index].rand_time_for_stoling <= 2) {
            night_routine(memory, spie_index);
        }
        if(hour >= 20 && hour <= 23 && memory->spies[spie_index].rand_time_for_stoling > 2 && memory->spies[spie_index].rand_time_for_stoling <= 12) {
            night_routine(memory, spie_index);
        }
        if(hour >= 0 && hour < 3 && memory->spies[spie_index].rand_time_for_stoling > 12 && memory->spies[spie_index].rand_time_for_stoling <= 86) {
            night_routine(memory, spie_index);
        }
        if(hour >= 3 && hour < 5 && memory->spies[spie_index].rand_time_for_stoling > 88 && memory->spies[spie_index].rand_time_for_stoling <= 98) {
            night_routine(memory, spie_index);
        }
        if(hour >= 5 && hour < 8 && memory->spies[spie_index].rand_time_for_stoling > 98 ) {
            night_routine(memory, spie_index);
        }
            

    //In the day between 8H and 17H
    } else {
        memory->spies[spie_index].is_stolling = 0;
        memory->spies[spie_index].round_number_before_stole = 0;
        memory->spies[spie_index].go_to_put_msg_in_mailbox = 0;
        day_routine(memory, spie_index);
    }

    //recuperation du contexteq
    
    arguments->memory = memory;
    arguments->memory->memory_has_changed = 1;


    return NULL;
}


void main_spy(int index) {
    int shmd;
    sem_t *sem;
    memory_t *memory;
    args_spy * args = malloc(sizeof(args_spy));
    args->spie_index = index;

    int count = 0;
    while(1) {
        sem = open_semaphore("spy_simulation-sem");
        P(sem);
        shmd = shm_open("/spy_simulation", O_RDWR, 0666);
        memory = mmap(NULL, sizeof(memory_t), PROT_READ | PROT_WRITE, MAP_SHARED, shmd, 0);
        args->memory = memory;
        if (count != memory->count) {
            spie_routine(args);
        }
        munmap(memory, sizeof(memory_t));
        close(shmd);
        V(sem);
    }
}

void main_case_officer() {
    int shmd;
    sem_t *sem;
    memory_t *memory;

    int count = 0;
    while(1) {
        sem = open_semaphore("spy_simulation-sem");
        P(sem);
        shmd = shm_open("/spy_simulation", O_RDWR, 0666);
        memory = mmap(NULL, sizeof(memory_t), PROT_READ | PROT_WRITE, MAP_SHARED, shmd, 0);

        if (count != memory->count) {
            count = memory->count;
            case_officer_routine(memory);
        }
        munmap(memory, sizeof(memory_t));
        close(shmd);
        V(sem);
    }
}

void case_officer_routine(memory_t * memory) {
    int hour = get_hour(memory);
    int minutes =get_minutes(memory);
    int next_row, next_column;

    if(hour == 0 && minutes == 0) { //Initialize times to go out
        memory->case_officer.outing_mailbox_1 = create_time((rand()%9)+8, (rand()%6)*10);
        memory->case_officer.outing_mailbox_2 = create_time((rand()%9)+8, (rand()%6)*10);
        while(abs(memory->case_officer.outing_mailbox_1.hour-memory->case_officer.outing_mailbox_2.hour) < 2) {
            memory->case_officer.outing_mailbox_2 = create_time((rand()%9)+8, (rand()%6)*10);
        }
        memory->case_officer.outing_supermarket = create_time((rand()%2)+17, (rand()%6)*10);
        memory->case_officer.send_messages = create_time((rand()%2)+22, (rand()%6)*10);
    }

    int hour_outing_mailbox1 = memory->case_officer.outing_mailbox_1.hour;
    int minutes_outing_mailbox1 = memory->case_officer.outing_mailbox_1.minutes;
    int hour_outing_mailbox2 = memory->case_officer.outing_mailbox_2.hour;
    int minutes_outing_mailbox2 = memory->case_officer.outing_mailbox_2.minutes;
    int hour_outing_supermarket = memory->case_officer.outing_supermarket.hour;
    int minutes_outing_supermarket = memory->case_officer.outing_supermarket.minutes;
    int random_supermarket = memory->case_officer.random_supermarket;

    int location_row = memory->case_officer.location_row;
    int location_column = memory->case_officer.location_column;
    int supermarket_row = memory->supermarkets[random_supermarket].row;
    int supermarket_column = memory->supermarkets[random_supermarket].column;

    if(hour >= 8 && hour < 17) {
        if((hour == hour_outing_mailbox1 && minutes == minutes_outing_mailbox1) || (hour == hour_outing_mailbox2 && minutes == minutes_outing_mailbox2)) { //Time to go to mailbox
            memory->case_officer.going_to_mailbox = 1;
        }
        if(memory->case_officer.going_to_mailbox == 1) { //Need to go to mailbox
            get_next_cell_case_officer(memory, memory->mailbox.row, memory->mailbox.column, &next_row, &next_column);
        }
        if(memory->case_officer.going_to_mailbox == 1 && memory->mailbox.occupied == 1) { //Mailbox occupied
            next_row = location_row; //Stay at the same cell
            next_column = location_column;
        }
        if(memory->case_officer.going_to_mailbox == 1 && location_row == memory->mailbox.row && location_column == memory->mailbox.column) { //At mailbox
            memory->case_officer.going_to_mailbox = 0;
            memory->case_officer.at_mailbox = 1;
            memory->mailbox.occupied = 1;
            case_officer_get_message(memory);
        } 
        if(memory->case_officer.going_to_mailbox == 0) { //Need to go home
            if(memory->case_officer.at_mailbox == 1){
                memory->mailbox.occupied = 0;
            }
            get_next_cell_case_officer(memory, memory->case_officer.home_row, memory->case_officer.home_column, &next_row, &next_column);
        }
    }
    else if(hour >= 17 && hour < 19) {
        if(hour == hour_outing_supermarket && minutes == minutes_outing_supermarket) {
            memory->case_officer.going_to_supermarket = 1;
        }
        if(memory->case_officer.going_to_supermarket == 1) { //Need to go to supermarket
            get_next_cell_case_officer(memory, supermarket_row, supermarket_column, &next_row, &next_column);
        }
        if(location_row == supermarket_row && location_column == supermarket_column) { //At supermarket
            memory->case_officer.going_to_supermarket = 0;
        }
        if(memory->case_officer.going_to_supermarket == 0) { //Been at supermarket, need to go home
            get_next_cell_case_officer(memory, memory->case_officer.home_row, memory->case_officer.home_column, &next_row, &next_column);
        }
    }
    else if(hour >= 22 && (hour < 23 || (hour == 23 && minutes <= 50))) {
        next_row = location_row;
        next_column = location_column;
        if(hour == memory->case_officer.send_messages.hour && minutes == memory->case_officer.send_messages.minutes){ //Time to send messages

        }
    }
    else {
        get_next_cell_case_officer(memory, memory->case_officer.home_row, memory->case_officer.home_column, &next_row, &next_column);
    }
    // printf("%d:%d [%d,%d]=>[%d,%d] (H(%d,%d) M(%d,%d))\n",hour, minutes, location_row, location_column, next_row, next_column, memory->case_officer.home_row, memory->case_officer.home_column, memory->mailbox.row, memory->mailbox.column);
    memory->case_officer.location_row = next_row;
    memory->case_officer.location_column = next_column;
}

void get_next_cell_case_officer(memory_t *memory, int destination_row, int destination_column, int * next_row, int * next_column) {
    int i, j, random_cell;
    int count_reachable_cells = 0;
    int reachable_cells_row[8];
    int reachable_cells_column [8];
    
    for(i = memory->case_officer.location_row - 1; i <= memory->case_officer.location_row + 1; i++) {
        for(j = memory->case_officer.location_column - 1; j <= memory->case_officer.location_column + 1; j++) {
            if(i >= 0 && i < MAX_ROWS && j >= 0 && j < MAX_COLUMNS) {
                if(i == destination_row && j == destination_column) {
                        *next_row = i;
                        *next_column = j;
                        return;
                }
                if(memory->map.cells[i][j].type == WASTELAND) {
                    if(manhattan_distance(i, j, destination_row, destination_column) < manhattan_distance(memory->case_officer.location_row, memory->case_officer.location_column, destination_row, destination_column)) {
                        reachable_cells_row[count_reachable_cells] = i;
                        reachable_cells_column[count_reachable_cells] = j;
                        count_reachable_cells += 1;
                    }
                }
            }
        }
    }

    if(count_reachable_cells == 0) {
        for(i = memory->case_officer.location_row - 1; i <= memory->case_officer.location_row + 1; i++) {
            for(j = memory->case_officer.location_column - 1; j <= memory->case_officer.location_column + 1; j++) {
                if(i >= 0 && i < MAX_ROWS && j >= 0 && j < MAX_COLUMNS && memory->map.cells[i][j].type == WASTELAND) {
                    *next_row = i;
                    *next_column = j;
                    return;
                }
            }
        } 
    } 
    else {
        random_cell = rand()%count_reachable_cells;
        *next_row = reachable_cells_row[random_cell];
        *next_column = reachable_cells_column[random_cell];
    }
}

void case_officer_get_message(memory_t *memory) {
    if(memory->mailbox.number_of_messages > 0) {
        for(int i=0; i<memory->mailbox.number_of_messages; i++) {
            ++memory->case_officer.number_of_messages;
            memory->case_officer.messages = realloc(memory->case_officer.messages, memory->case_officer.number_of_messages * sizeof(char*));
            memory->case_officer.messages[memory->case_officer.number_of_messages-1] = memory->mailbox.messages[i];
        }
        memory->mailbox.number_of_messages = 0;
        memory->mailbox.messages = NULL;
    }
}

