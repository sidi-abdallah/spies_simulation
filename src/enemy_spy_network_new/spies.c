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
#include "posix_semaphore.h"
#include "spy_simulation.h"
#include "functions.h"
#include "memory.h"
#include "cell.h"

#define SPIES_NUMBER 3
#define ROUND_NB_BEFORE_STOLE 12
#define ADJACENT_CASES_NUMBER 8

//int * available_companies = calloc(MAX_COMPANIES, sizeof(int));
int available_companies[MAX_COMPANIES] = {0};

mailbox_t * get_pos_mailbox(void) {
    sem_t *sem; 
    memory_t * memory = malloc(sizeof(memory_t));
    mailbox_t *mailbox = (mailbox_t *)malloc(sizeof(mailbox_t));
    sem = open_semaphore("sem_test-sem");
    P(sem);
    int shmd = shm_open("/share_memory__test",O_RDWR,0666);
    memory = mmap(NULL, sizeof(memory_t), PROT_READ | PROT_WRITE,MAP_SHARED, shmd,0);
    *mailbox = memory->mailbox;
    munmap(memory, sizeof(memory_t));
    close(shmd);
    V(sem);    
    return mailbox;
}

int manhattan_distance(int x1, int y1, int x2, int y2) {
    return abs(x2 -x1) + abs(y2 -y1); 
}

int get_round(void) {
    sem_t *sem; 
    int round;
    memory_t * memory = malloc(sizeof(memory_t));
    sem = open_semaphore("sem_test-sem");
    P(sem);
    int shmd = shm_open("/share_memory__test",O_RDWR,0666);
    memory = mmap(NULL, sizeof(memory_t), PROT_READ | PROT_WRITE,MAP_SHARED, shmd,0);
    round = memory->count;
    munmap(memory, sizeof(memory_t));
    close(shmd);
    V(sem);    
    return round;
}

int  chosen_company_index(void) {
    int company_index = rand() % MAX_COMPANIES;
    company_t *company = (company_t *)malloc(sizeof(company_t));
    sem_t *sem; 
    memory_t * memory = malloc(sizeof(memory_t));
    mailbox_t * mailbox = get_pos_mailbox();
    while(available_companies[company_index]){
        company_index = rand() % MAX_COMPANIES;
        sem = open_semaphore("sem_test-sem");
        P(sem);
        int shmd = shm_open("/share_memory__test",O_RDWR,0666);
        memory = mmap(NULL, sizeof(memory_t), PROT_READ | PROT_WRITE,MAP_SHARED, shmd,0);
        *company = memory->companies[company_index];
        munmap(memory, sizeof(memory_t));
        close(shmd);
        V(sem);    
            
        if(manhattan_distance(mailbox->row, mailbox->column, company->row, company->column) <= 4) {
            available_companies[company_index] = 1;
            return company_index; 
        }
    }
    return -1; //ne va jamais arriver (eviter le warning)     
}

company_t * choose_company(void) {
    sem_t *sem; 
    company_t *company = (company_t *)malloc(sizeof(company_t));
    memory_t * memory = malloc(sizeof(memory_t));
    sem = open_semaphore("sem_test-sem");
    P(sem);
    int shmd = shm_open("/share_memory__test",O_RDWR,0666);
    memory = mmap(NULL, sizeof(memory_t), PROT_READ | PROT_WRITE,MAP_SHARED, shmd,0);
    *company = memory->companies[chosen_company_index()];
    munmap(memory, sizeof(memory_t));
    close(shmd);
    V(sem);    
    return company;
}

spie_t * get_spy(int spy_index) {
    sem_t *sem; 
    memory_t * memory = malloc(sizeof(memory_t));
    spie_t *spy = (spie_t *)malloc(sizeof(spie_t));
    sem = open_semaphore("sem_test-sem");
    P(sem);
    int shmd = shm_open("/share_memory__test",O_RDWR,0666);
    memory = mmap(NULL, sizeof(memory_t), PROT_READ | PROT_WRITE,MAP_SHARED, shmd,0);
    *spy = memory->spies[spy_index];
    munmap(memory, sizeof(memory_t));
    close(shmd);
    V(sem);    
    return spy;
}

double euclid_distance(int x1, int y1, int x2, int y2){
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

void change_pos_spie(int spy_index, int new_row, int new_column) {
    sem_t *sem; 
    sem = open_semaphore("sem_test-sem");
    memory_t * memory = malloc(sizeof(memory_t));
    P(sem);
    int shmd = shm_open("/share_memory__test",O_RDWR,0666);
    memory = mmap(NULL, sizeof(memory_t), PROT_READ | PROT_WRITE,MAP_SHARED, shmd,0);
    memory->spies[spy_index].location_row = new_row;
    memory->spies[spy_index].location_column = new_column;
    memory->memory_has_changed = 1;
    munmap(memory, sizeof(memory_t));
    close(shmd);
    V(sem);    

}

void move_spy(int row_direction, int column_direction, int spy_index){
    int valid_cells_x[3];
    int valid_cells_y[3];
    int counter = 0;
    spie_t *spy = get_spy(spy_index);
    int random_valid_cell;
    for(int i = -1; i <= 1; ++i){
        for(int j = -1; j <= 1; ++j) {
            if(i == 0 && j ==0){
                continue;
            }
            if(i >= 0 && i < MAX_ROWS && j >= 0 && j < MAX_COLUMNS) {

                if(euclid_distance(row_direction, column_direction, spy->location_row + i,  spy->location_column + j) < euclid_distance(row_direction, column_direction, spy->location_row,  spy->location_column)){
                    valid_cells_x[counter] = spy->location_row + i;
                    valid_cells_y[counter] = spy->location_column + j;
                    ++counter;
                }
            }
        }
    }
    random_valid_cell = rand() % 3;
    change_pos_spie(spy_index,valid_cells_x[random_valid_cell],valid_cells_y[random_valid_cell]);

}

int is_adjacent_to_company(company_t * company, spie_t * spy){
    return (abs(spy->location_row - company->row) <= 1 && abs(spy->location_column - company->column) <= 1) ? 1 : 0;
} 

// void tracking_before_stole(company_t *company, int spy_index) {
//     int counter = 0;

    
// }

void stole_information(int spy_index) {
    company_t *company = choose_company();
    int last_round = get_round();
    int current_round = get_round();
    spie_t * spy = get_spy(spy_index);

    while(!is_adjacent_to_company(company, spy)) {
        if(current_round == last_round + 1){
            move_spy(company->row, company->column, spy_index);
        }
        last_round = current_round; 
    }
    // while(current_round != last_round + ROUND_NB_B    memory_t * memory = malloc(sizeof(memory_t));

}

int main(void) {

    pthread_t spies[SPIES_NUMBER];
    stole_information(0);
    // for(int i = 0; i < SPIES_NUMBER; i++) {
    //     pthread_create(&spies[i], NULL, stole_information,(void *)(&i));

    // }

    // for(int i = 0; i < SPIES_NUMBER; i++) {
    //     pthread_join(spies[i], NULL);
    // }
    return 0;
}

