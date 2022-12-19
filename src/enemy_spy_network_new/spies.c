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
//#include "citizen_manager.h"
typedef struct args_spy {
    memory_t *memory;
    int spie_index;
} args_spy;

#define SPIES_NUMBER 3
#define ROUND_NB_BEFORE_STOLE 12
#define ADJACENT_CASES_NUMBER 8


int get_hour(memory_t *memory) {
    return ((int) floor((memory->count/6)))%24;
}

int get_minutes(memory_t *memory) {
    return (memory->count * 10)%60;
}

void get_next_cell(memory_t *memory, int spie_index, int destination_row, int destination_column, int * next_row, int * next_column) {
    int i, j, random_cell;
    int count_reachable_cells = 0;
    int reachable_cells_row[8];
    int reachable_cells_column [8];
    
    for(i = memory->spies[spie_index].location_row - 1; i <= memory->citizens[spie_index].location_row + 1; i++) {
        for(j = memory->spies[spie_index].location_column - 1; j <= memory->spies[spie_index].location_column + 1; j++) {
            if(i >= 0 && i < MAX_ROWS && j >= 0 && j < MAX_COLUMNS) {
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


void *spie_routine(void *args) {
    int company_row = 0, company_col = 0 , destination_row = 0, destination_col = 0,  next_row = 0, next_column = 0;

    args_spy * arguments = (args_spy *) args;
    memory_t * memory = arguments->memory;
    int spie_index = arguments->spie_index;
    int hour = get_hour(memory);
    int minutes = get_minutes(memory);
    int location_row = memory->spies[spie_index].location_row;
    int location_column = memory->spies[spie_index].location_column;
    int home_row = memory->spies[spie_index].home_row;
    int home_column = memory->spies[spie_index].home_column;
    int rand_time_for_stoling = memory->spies[spie_index].rand_time_for_stoling;
    int index_company_being_stolen = memory->spies[spie_index].index_company_being_stolen;
    int round_number_before_stole = memory->spies[spie_index].round_number_before_stole;
    int stroll_in_city = memory->spies[spie_index].stroll_in_city;
    int shopping = memory->spies[spie_index].shopping;
    int stay_at_home = memory->spies[spie_index].stay_at_home;
    int rand_day_routine = memory->spies[spie_index].rand_day_routine;
    int random_supermarket = memory->spies[spie_index].random_supermarket;
    //printf("%d\n",hour);

    if(hour==17) {
        rand_time_for_stoling  = (rand()%100) + 1;
    //    printf("c'est 17h 00\n");
    }
    //In the night between 17H and 8H
    printf("rand_time_for_stoling = %d\n", rand_time_for_stoling);
    if(hour >= 17 || hour < 8) {
        printf(" spie entre 17h et 8h\n");
        if(hour >= 17 && hour < 20 && rand_time_for_stoling <= 100) {
            if(round_number_before_stole == 0) {
                index_company_being_stolen  = rand()%MAX_COMPANIES;
                while(memory->spies[spie_index].companies_stolen_yet[index_company_being_stolen]) {
                    index_company_being_stolen  = rand()%MAX_COMPANIES;
                }
                memory->spies[spie_index].companies_stolen_yet[index_company_being_stolen] = 1;
                round_number_before_stole++;
                
            }
            else {
                company_row = memory->companies[index_company_being_stolen].row;
                company_col = memory->companies[index_company_being_stolen].column;
                get_next_cell(memory, spie_index, company_row, company_col, &next_row, &next_column);
                if(next_row == company_row && next_column == company_col) {
                    if(round_number_before_stole < 12) {
                        printf("nombre de tours < 12 : %d\n", round_number_before_stole);
                        round_number_before_stole++;
                    }
                    // else if(round_number_before_stole == 12) {
                    //     decide_to_stole = rand()%100;
                    //     if(decide_to_stole < 86) {

                    //     }
                    //     else {
                            
                    //     }
                    // }
                    else {
                        round_number_before_stole = 0;
                    }
                }
                else {
                    location_row = next_row;
                    location_column = next_column;
                }

            }
            
        }

        if(hour >= 20 && hour <= 23 && rand_time_for_stoling > 2 && rand_time_for_stoling <= 12) {

        }
        if(hour <= 0 && hour > 3 && rand_time_for_stoling > 12 && rand_time_for_stoling <= 86) {

        }
        if(hour >= 3 && hour < 5 && rand_time_for_stoling > 88 && rand_time_for_stoling <= 98) {

        }
        if(hour >= 5 && hour < 8 && rand_time_for_stoling > 98 ) {
        
        }
            

    //In the day between 8H and 17H
    } else {
        printf("spie entre 8h et 17h\n");
        if(hour == 8) rand_day_routine = rand()%100;
        if(memory->spies[spie_index].hour != hour ) {
            memory->spies[spie_index].hour = hour;
            printf("spy new hour %d\n", hour);
            printf(" TID : %ld\n", pthread_self());
            rand_day_routine = rand()%100;
            shopping = 0;
            stroll_in_city = 0;
            stay_at_home = 0;
        }
        else {
            if(rand_day_routine <= 30) {
                destination_row = home_row;
                destination_col = home_column;
                stay_at_home = 1;
                printf("spie chez lui\n");
                shopping = 0;
                stroll_in_city = 0;
            } 
            else if(rand_day_routine > 30 && rand_day_routine < 40) {
                if(shopping == 0) {
                    random_supermarket = rand()%MAX_SUPERMARKETS;
                }
                printf("spie supermarché\n");

                destination_row = memory->supermarkets[random_supermarket].row;
                destination_col = memory->supermarkets[random_supermarket].column;
                shopping = 1;
                stay_at_home = 0;
                stroll_in_city = 0;
            } else {
                printf("spie se promene\n");
                    //gestion de promenade ici (later).
            }
        }
        if(destination_row == location_row && destination_col == location_column) {
            next_row = destination_row;
            next_column = destination_col;
        }
        else {
            get_next_cell(memory, spie_index, destination_row, destination_col, &next_row, &next_column);
            printf("spy change position (%d, %d) \n", next_row, next_column);

        }
        location_row = next_row;
        location_column = next_column;
        printf("pos actual of %ld :(%d,%d)\n",pthread_self(), location_row, location_column);
    }

    //recuperation du contexte
    memory->spies[spie_index].location_row = location_row;
    memory->spies[spie_index].location_column = location_column;
    memory->spies[spie_index].rand_time_for_stoling = rand_time_for_stoling;
    memory->spies[spie_index].index_company_being_stolen = index_company_being_stolen;
    memory->spies[spie_index].round_number_before_stole = round_number_before_stole;
    memory->spies[spie_index].stroll_in_city = stroll_in_city;
    memory->spies[spie_index].shopping = shopping;
    memory->spies[spie_index].stay_at_home = stay_at_home;
    memory->spies[spie_index].rand_day_routine = rand_day_routine;
    memory->spies[spie_index].random_supermarket = random_supermarket;
    arguments->memory = memory;
    arguments->memory->memory_has_changed = 1;


    return NULL;
}




// int * available_companies = calloc(MAX_COMPANIES, sizeof(int));
int available_companies[MAX_COMPANIES] = {0};

mailbox_t *get_pos_mailbox(void)
{
    sem_t *sem;
    memory_t *memory = malloc(sizeof(memory_t));
    mailbox_t *mailbox = (mailbox_t *)malloc(sizeof(mailbox_t));
    sem = open_semaphore("spy_simulation-sem");
    printf("get_pos_mailbox1\n");
    P(sem);
    printf("get_pos_mailbox2\n");
    int shmd = shm_open("/spy_simulation", O_RDWR, 0666);
    memory = mmap(NULL, sizeof(memory_t), PROT_READ | PROT_WRITE, MAP_SHARED, shmd, 0);
    *mailbox = memory->mailbox;
    munmap(memory, sizeof(memory_t));
    close(shmd);
    V(sem);
    return mailbox;
}

int manhattan_distance(int x1, int y1, int x2, int y2)
{
    return abs(x2 - x1) + abs(y2 - y1);
}

int get_round(void)
{
    sem_t *sem;
    int round;
    int shmd;
    memory_t *memory = malloc(sizeof(memory_t));
    sem = open_semaphore("spy_simulation-sem");
    P(sem);
    printf("hello_get_round\n");
    shmd = shm_open("/spy_simulation", O_RDWR, 0666);
    memory = mmap(NULL, sizeof(memory_t), PROT_READ | PROT_WRITE, MAP_SHARED, shmd, 0);
    round = memory->count;
    munmap(memory, sizeof(memory_t));
    close(shmd);
    V(sem);
    return round;
}

int chosen_company_index(void)
{
    int company_index = rand() % MAX_COMPANIES;
    company_t *company = (company_t *)malloc(sizeof(company_t));
    sem_t *sem;
    memory_t *memory = malloc(sizeof(memory_t));
    printf("chosen company index1\n");
    mailbox_t *mailbox = get_pos_mailbox();
    printf("chosen company index2\n");
    while (available_companies[company_index])
    {
        company_index = rand() % MAX_COMPANIES;
        sem = open_semaphore("spy_simulation-sem");
        P(sem);
        int shmd = shm_open("/spy_simulation", O_RDWR, 0666);
        memory = mmap(NULL, sizeof(memory_t), PROT_READ | PROT_WRITE, MAP_SHARED, shmd, 0);
        *company = memory->companies[company_index];
        munmap(memory, sizeof(memory_t));
        close(shmd);
        V(sem);
        printf("chosen company index\n");
        if (manhattan_distance(mailbox->row, mailbox->column, company->row, company->column) <= 4)
        {
            available_companies[company_index] = 1;
            return company_index;
        }
    }
    return -1; // ne va jamais arriver (eviter le warning)
}

company_t *choose_company(void)
{
    sem_t *sem;
    company_t *company = (company_t *)malloc(sizeof(company_t));
    memory_t *memory = malloc(sizeof(memory_t));
    sem = open_semaphore("spy_simulation-sem");
    int index_company = chosen_company_index();
    P(sem);
    printf("in chose company1\n");
    int shmd = shm_open("/spy_simulation", O_RDWR, 0666);
    memory = mmap(NULL, sizeof(memory_t), PROT_READ | PROT_WRITE, MAP_SHARED, shmd, 0);
    printf("in chose company2\n");
    printf("%d\n", memory->companies[0].column);
    *company = memory->companies[index_company];
    printf("in chose company3\n");
    munmap(memory, sizeof(memory_t));
    close(shmd);
    V(sem);
    return company;
}

spie_t *get_spy(int spy_index)
{
    sem_t *sem;
    memory_t *memory = malloc(sizeof(memory_t));
    spie_t *spy = (spie_t *)malloc(sizeof(spie_t));
    sem = open_semaphore("spy_simulation-sem");
    P(sem);
    int shmd = shm_open("/spy_simulation", O_RDWR, 0666);
    memory = mmap(NULL, sizeof(memory_t), PROT_READ | PROT_WRITE, MAP_SHARED, shmd, 0);
    *spy = memory->spies[spy_index];
    munmap(memory, sizeof(memory_t));
    close(shmd);
    V(sem);
    return spy;
}

// double euclid_distance(int x1, int y1, int x2, int y2){
//     return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
// }

void change_pos_spie(int spy_index, int new_row, int new_column)
{
    sem_t *sem;
    sem = open_semaphore("spy_simulation-sem");
    memory_t *memory = malloc(sizeof(memory_t));
    P(sem);
    int shmd = shm_open("/spy_simulation", O_RDWR, 0666);
    memory = mmap(NULL, sizeof(memory_t), PROT_READ | PROT_WRITE, MAP_SHARED, shmd, 0);
    memory->spies[spy_index].location_row = new_row;
    memory->spies[spy_index].location_column = new_column;
    memory->memory_has_changed = 1;
    munmap(memory, sizeof(memory_t));
    close(shmd);
    V(sem);
}

void move_spy(int row_direction, int column_direction, int spy_index)
{
    int valid_cells_x[3];
    int valid_cells_y[3];
    int counter = 0;
    spie_t *spy = get_spy(spy_index);
    int random_valid_cell;
    for (int i = -1; i <= 1; ++i)
    {
        for (int j = -1; j <= 1; ++j)
        {
            // if(i == 0 && j ==0){
            //     continue;
            // }
            // printf("he");
            if (i >= 0 && i < MAX_ROWS && j >= 0 && j < MAX_COLUMNS && (i != 0 || j != 0))
            {

                // if(manhatten_distance(row_direction, column_direction, spy->location_row + i,  spy->location_column + j) < manhattan_distance(row_direction, column_direction, spy->location_row,  spy->location_column)){
                if ((row_direction - spy->location_row) > (row_direction - (spy->location_row + i)) || (column_direction - spy->location_column) > (column_direction - (spy->location_column + j)))
                {
                    valid_cells_x[counter] = spy->location_row + i;
                    valid_cells_y[counter] = spy->location_column + j;
                    ++counter;
                }
            }
        }
    }
    random_valid_cell = rand() % counter;
    change_pos_spie(spy_index, valid_cells_x[random_valid_cell], valid_cells_y[random_valid_cell]);
}

int is_adjacent_to_company(company_t *company, spie_t *spy)
{
    return (abs(spy->location_row - company->row) <= 1 && abs(spy->location_column - company->column) <= 1) ? 1 : 0;
}

// void tracking_before_stole(company_t *company, int spy_index) {
//     int counter = 0;

// }

void stole_information(int spy_index)
{
    printf("hello1\n");
    company_t *company = choose_company();
    printf("hello2\n");
    int last_round = get_round();
    printf("hello3\n");
    int current_round = last_round;
    printf("hello4\n");
    //  while(!is_adjacent_to_company(company, spy)) {
    printf("hello5\n");
    //    if(current_round == last_round + 1){
    printf("hello6\n");
    move_spy(company->row, company->column, spy_index);
    printf("hello7\n");
    //  }
    last_round = current_round;
}
// while(current_round != last_round + ROUND_NB_B    memory_t * memory = malloc(sizeof(memory_t));

int main(void)
{
    int shmd, i;
    sem_t *sem;
    pthread_t *t;
    memory_t *memory;
    args_spy *args;
    int count = 0;
    
    srand(time(NULL));
    
    sem = open_semaphore("spy_simulation-sem");
    P(sem);
    shmd = shm_open("/spy_simulation", O_RDWR, 0666);
    memory = mmap(NULL, sizeof(memory_t), PROT_READ | PROT_WRITE, MAP_SHARED, shmd, 0);
    for(int spie_index = 0; spie_index < SPIES_NUMBER; spie_index++) {
        memory->spies[spie_index].rand_time_for_stoling = 0;
        memory->spies[spie_index].round_number_before_stole = 0;
        memory->spies[spie_index].stroll_in_city = 0;
        memory->spies[spie_index].shopping = 0;
        memory->spies[spie_index].stay_at_home = 0;
        memory->spies[spie_index].rand_day_routine = 0;
        memory->spies[spie_index].random_supermarket = 0;
        memory->spies[spie_index].hour = get_hour(memory);
        memory->spies[spie_index].companies_stolen_yet = (int*)calloc(MAX_COMPANIES, sizeof(int));
    }
    munmap(memory, sizeof(memory_t));
    close(shmd);
    V(sem);


    while (1)
    {
        sem = open_semaphore("spy_simulation-sem");
        P(sem);
        shmd = shm_open("/spy_simulation", O_RDWR, 0666);
        memory = mmap(NULL, sizeof(memory_t), PROT_READ | PROT_WRITE, MAP_SHARED, shmd, 0);
        
        if (count != memory->count)
        {
            count = memory->count;
            t = (pthread_t *)malloc(sizeof(pthread_t) * SPIES_NUMBER);
            args = (args_spy *)malloc(sizeof(args_spy) * SPIES_NUMBER);
            for (i = 0; i < SPIES_NUMBER; i++)
            {
                args[i].spie_index = i;
                args[i].memory = memory;
            }

            for (i = 0; i < SPIES_NUMBER; i++)
            {
                pthread_create(&t[i], NULL, spie_routine, &args[i]);
            }

            for (i = 0; i < SPIES_NUMBER; i++)
            {
                pthread_join(t[i], NULL);
            }
        }
        munmap(memory, sizeof(memory_t));
        close(shmd);
        V(sem);
    }
    return 0;
}