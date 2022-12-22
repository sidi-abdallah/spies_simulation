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

void get_next_cell(memory_t *memory, int spie_index, int destination_row, int destination_column, int * next_row, int * next_column) {
    int i, j, random_cell;
    int count_reachable_cells = 0;
    int reachable_cells_row[8];
    int reachable_cells_column [8];
    
    for(i = memory->spies[spie_index].location_row - 1; i <= memory->spies[spie_index].location_row + 1; i++) {
        for(j = memory->spies[spie_index].location_column - 1; j <= memory->spies[spie_index].location_column + 1; j++) {
            if(i >= 0 && i < MAX_ROWS && j >= 0 && j < MAX_COLUMNS) {
                if(i == destination_row && j == destination_column) {
                        *next_row = i;
                        *next_column = j;
                        return;
                }
                if(memory->map.cells[i][j].type == WASTELAND) {
                    if(manhattan_distance(i, j, destination_row, destination_column) < manhattan_distance(memory->spies[spie_index].location_row, memory->spies[spie_index].location_column, destination_row, destination_column)) {
                        reachable_cells_row[count_reachable_cells] = i;
                        reachable_cells_column[count_reachable_cells] = j;
                        count_reachable_cells += 1;
                    }
                }
            }
        }
    }

    if(count_reachable_cells == 0) {
        for(i = memory->spies[spie_index].location_row - 1; i <= memory->spies[spie_index].location_row + 1; i++) {
            for(j = memory->spies[spie_index].location_column - 1; j <= memory->spies[spie_index].location_column + 1; j++) {
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

void night_routine(memory_t *memory, int spie_index) {
    int company_row = 0, company_col = 0, next_row = 0, next_column = 0;

    if(memory->spies[spie_index].round_number_before_stole == 0) {
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
        if(next_row == company_row && next_column == company_col) {
            if(memory->spies[spie_index].round_number_before_stole < 12) {
                //printf("nombre de tours < 12 : %d\n", memory->spies[spie_index].round_number_before_stole);
                memory->spies[spie_index].round_number_before_stole++;
            }
            //  else if(round_number_before_stole == 12 || walking_to_put_fake_msg) {
            //     int decide_to_stole = rand()%100;
            //     if(decide_to_stole < 86) {
            //         strcpy(memory->spies[spie_index].stolen_message_content, memory->companies[index_company_being_stolen].information);
            //         int random_importance_msg = rand() % 100 + 1;
            //         if(random_importance_msg == 1){
            //             memory->spies[spie_index].message_importance = CRUTIAL;
            //         }
            //         else if(random_importance_msg > 1 && random_importance_msg <= 6){
            //             memory->spies[spie_index].message_importance = STRONG;
            //         }
            //         else if(random_importance_msg > 6 && random_importance_msg <= 20){
            //             memory->spies[spie_index].message_importance = MEDIUM;
            //         }
            //         else if(random_importance_msg > 20 && random_importance_msg <= 50){
            //             memory->spies[spie_index].message_importance = LOW;
            //         }
            //         else{
            //             memory->spies[spie_index].message_importance = VERY_LOW;
            //         }
            //     }
                
            //     else if(walking_to_put_fake_msg){
            //         get_next_cell(memory, spie_index, memory->mailbox.row, memory->mailbox.column, &next_row, &next_column);
            //         round_number_before_stole++;
            //     }
            //     else {
            //         get_next_cell(memory, spie_index, memory->mailbox.row, memory->mailbox.column, &next_row, &next_column);
            //         walking_to_put_fake_msg = 1;
            //         round_number_before_stole++;
            //     }
            // }
            else {
                //printf(" %d ont été effectué avant le vol\n", memory->spies[spie_index].round_number_before_stole);
                memory->spies[spie_index].round_number_before_stole = 0;
            }
        }
        else {
            memory->spies[spie_index].location_row = next_row;
            memory->spies[spie_index].location_column = next_column;
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
           // printf("spy new hour %d\n", hour);
           // printf(" TID : %ld\n", pthread_self());
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
                //printf("spie se promene\n");
                    //gestion de promenade ici (later).
            }
        }
        if(destination_row == memory->spies[spie_index].location_row && destination_col == memory->spies[spie_index].location_column) {
            next_row = destination_row;
            next_column = destination_col;
        }
        else {
            get_next_cell(memory, spie_index, destination_row, destination_col, &next_row, &next_column);
            //printf("spy change position (%d, %d) \n", next_row, next_column);

        }
        memory->spies[spie_index].location_row = next_row;
        memory->spies[spie_index].location_column = next_column;
        //printf("pos actual of %ld :(%d,%d)\n",pthread_self(), memory->spies[spie_index].location_row, memory->spies[spie_index].location_column);
}

void spie_routine(memory_t *memory, int spie_index) {
    int hour = get_hour(memory);
    //printf("%d\n",hour);

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
        if(hour >= 17 && hour < 20 && memory->spies[spie_index].rand_time_for_stoling <= 100) {
            night_routine(memory, spie_index);
        }
        if(hour >= 20 && hour <= 23 && memory->spies[spie_index].rand_time_for_stoling > 2 && memory->spies[spie_index].rand_time_for_stoling <= 12) {
            night_routine(memory, spie_index);
        }
        if(hour <= 0 && hour > 3 && memory->spies[spie_index].rand_time_for_stoling > 12 && memory->spies[spie_index].rand_time_for_stoling <= 86) {
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
        //printf("spie entre 8h et 17h\n");
        day_routine(memory, spie_index);
    }
}

void main_spy(int index) {
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
            spie_routine(memory, index);
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
    printf("%d:%d [%d,%d]=>[%d,%d] (H(%d,%d) M(%d,%d))\n",hour, minutes, location_row, location_column, next_row, next_column, memory->case_officer.home_row, memory->case_officer.home_column, memory->mailbox.row, memory->mailbox.column);
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

// // int * available_companies = calloc(MAX_COMPANIES, sizeof(int));
// int available_companies[MAX_COMPANIES] = {0};

// mailbox_t *get_pos_mailbox(void)
// {
//     sem_t *sem;
//     memory_t *memory = malloc(sizeof(memory_t));
//     mailbox_t *mailbox = (mailbox_t *)malloc(sizeof(mailbox_t));
//     sem = open_semaphore("spy_simulation-sem");
//     printf("get_pos_mailbox1\n");
//     P(sem);
//     printf("get_pos_mailbox2\n");
//     int shmd = shm_open("/spy_simulation", O_RDWR, 0666);
//     memory = mmap(NULL, sizeof(memory_t), PROT_READ | PROT_WRITE, MAP_SHARED, shmd, 0);
//     *mailbox = memory->mailbox;
//     munmap(memory, sizeof(memory_t));
//     close(shmd);
//     V(sem);
//     return mailbox;
// }



// int get_round(void)
// {
//     sem_t *sem;
//     int round;
//     int shmd;
//     memory_t *memory = malloc(sizeof(memory_t));
//     sem = open_semaphore("spy_simulation-sem");
//     P(sem);
//     printf("hello_get_round\n");
//     shmd = shm_open("/spy_simulation", O_RDWR, 0666);
//     memory = mmap(NULL, sizeof(memory_t), PROT_READ | PROT_WRITE, MAP_SHARED, shmd, 0);
//     round = memory->count;
//     munmap(memory, sizeof(memory_t));
//     close(shmd);
//     V(sem);
//     return round;
// }

// int chosen_company_index(void)
// {
//     int company_index = rand() % MAX_COMPANIES;
//     company_t *company = (company_t *)malloc(sizeof(company_t));
//     sem_t *sem;
//     memory_t *memory = malloc(sizeof(memory_t));
//     printf("chosen company index1\n");
//     mailbox_t *mailbox = get_pos_mailbox();
//     printf("chosen company index2\n");
//     while (available_companies[company_index])
//     {
//         company_index = rand() % MAX_COMPANIES;
//         sem = open_semaphore("spy_simulation-sem");
//         P(sem);
//         int shmd = shm_open("/spy_simulation", O_RDWR, 0666);
//         memory = mmap(NULL, sizeof(memory_t), PROT_READ | PROT_WRITE, MAP_SHARED, shmd, 0);
//         *company = memory->companies[company_index];
//         munmap(memory, sizeof(memory_t));
//         close(shmd);
//         V(sem);
//         printf("chosen company index\n");
//         if (manhattan_distance(mailbox->row, mailbox->column, company->row, company->column) <= 4)
//         {
//             available_companies[company_index] = 1;
//             return company_index;
//         }
//     }
//     return -1; // ne va jamais arriver (eviter le warning)
// }

// company_t *choose_company(void)
// {
//     sem_t *sem;
//     company_t *company = (company_t *)malloc(sizeof(company_t));
//     memory_t *memory = malloc(sizeof(memory_t));
//     sem = open_semaphore("spy_simulation-sem");
//     int index_company = chosen_company_index();
//     P(sem);
//     printf("in chose company1\n");
//     int shmd = shm_open("/spy_simulation", O_RDWR, 0666);
//     memory = mmap(NULL, sizeof(memory_t), PROT_READ | PROT_WRITE, MAP_SHARED, shmd, 0);
//     printf("in chose company2\n");
//     printf("%d\n", memory->companies[0].column);
//     *company = memory->companies[index_company];
//     printf("in chose company3\n");
//     munmap(memory, sizeof(memory_t));
//     close(shmd);
//     V(sem);
//     return company;
// }

// spie_t *get_spy(int spy_index)
// {
//     sem_t *sem;
//     memory_t *memory = malloc(sizeof(memory_t));
//     spie_t *spy = (spie_t *)malloc(sizeof(spie_t));
//     sem = open_semaphore("spy_simulation-sem");
//     P(sem);
//     int shmd = shm_open("/spy_simulation", O_RDWR, 0666);
//     memory = mmap(NULL, sizeof(memory_t), PROT_READ | PROT_WRITE, MAP_SHARED, shmd, 0);
//     *spy = memory->spies[spy_index];
//     munmap(memory, sizeof(memory_t));
//     close(shmd);
//     V(sem);
//     return spy;
// }

// // double euclid_distance(int x1, int y1, int x2, int y2){
// //     return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
// // }

// void change_pos_spie(int spy_index, int new_row, int new_column)
// {
//     sem_t *sem;
//     sem = open_semaphore("spy_simulation-sem");
//     memory_t *memory = malloc(sizeof(memory_t));
//     P(sem);
//     int shmd = shm_open("/spy_simulation", O_RDWR, 0666);
//     memory = mmap(NULL, sizeof(memory_t), PROT_READ | PROT_WRITE, MAP_SHARED, shmd, 0);
//     memory->spies[spy_index].memory->spies[spie_index].location_row = new_row;
//     memory->spies[spy_index].memory->spies[spie_index].location_column = new_column;
//     memory->memory_has_changed = 1;
//     munmap(memory, sizeof(memory_t));
//     close(shmd);
//     V(sem);
// }

// void move_spy(int row_direction, int column_direction, int spy_index)
// {
//     int valid_cells_x[3];
//     int valid_cells_y[3];
//     int counter = 0;
//     spie_t *spy = get_spy(spy_index);
//     int random_valid_cell;
//     for (int i = -1; i <= 1; ++i)
//     {
//         for (int j = -1; j <= 1; ++j)
//         {
//             // if(i == 0 && j ==0){
//             //     continue;
//             // }
//             // printf("he");
//             if (i >= 0 && i < MAX_ROWS && j >= 0 && j < MAX_COLUMNS && (i != 0 || j != 0))
//             {

//                 // if(manhatten_distance(row_direction, column_direction, spy->memory->spies[spie_index].location_row + i,  spy->memory->spies[spie_index].location_column + j) < manhattan_distance(row_direction, column_direction, spy->memory->spies[spie_index].location_row,  spy->memory->spies[spie_index].location_column)){
//                 if ((row_direction - spy->memory->spies[spie_index].location_row) > (row_direction - (spy->memory->spies[spie_index].location_row + i)) || (column_direction - spy->memory->spies[spie_index].location_column) > (column_direction - (spy->memory->spies[spie_index].location_column + j)))
//                 {
//                     valid_cells_x[counter] = spy->memory->spies[spie_index].location_row + i;
//                     valid_cells_y[counter] = spy->memory->spies[spie_index].location_column + j;
//                     ++counter;
//                 }
//             }
//         }
//     }
//     random_valid_cell = rand() % counter;
//     change_pos_spie(spy_index, valid_cells_x[random_valid_cell], valid_cells_y[random_valid_cell]);
// }

// int is_adjacent_to_company(company_t *company, spie_t *spy)
// {
//     return (abs(spy->memory->spies[spie_index].location_row - company->row) <= 1 && abs(spy->memory->spies[spie_index].location_column - company->column) <= 1) ? 1 : 0;
// }

// // void tracking_before_stole(company_t *company, int spy_index) {
// //     int counter = 0;

// // }

// void stole_information(int spy_index)
// {
//     printf("hello1\n");
//     company_t *company = choose_company();
//     printf("hello2\n");
//     int last_round = get_round();
//     printf("hello3\n");
//     int current_round = last_round;
//     printf("hello4\n");
//     //  while(!is_adjacent_to_company(company, spy)) {
//     printf("hello5\n");
//     //    if(current_round == last_round + 1){
//     printf("hello6\n");
//     move_spy(company->row, company->column, spy_index);
//     printf("hello7\n");
//     //  }
//     last_round = current_round;
// }
// // while(current_round != last_round + ROUND_NB_B    memory_t * memory = malloc(sizeof(memory_t));