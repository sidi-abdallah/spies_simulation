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

#define SPIES_NUMBER 3
#define ROUND_NB_BEFORE_STOLE 12

int * available_companies = (int *)calloc(MAX_COMPANIES, sizeof(int));

mailbox_t * get_pos_mailbox(void) {
    sem_t *sem; 
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
    sem = open_semaphore("sem_test-sem");
    P(sem);
    int shmd = shm_open("/share_memory__test",O_RDWR,0666);
    memory = mmap(NULL, sizeof(memory_t), PROT_READ | PROT_WRITE,MAP_SHARED, shmd,0);
    round = memory->count;
    munmap(memory, sizeof(memory_t));
    close(shmd);
    V(sem);    
    return count;
}

int  chosen_company_index(void) {
    int company_index = rand() % MAX_COMPANIES;
    mailbox_t * mailbox = get_pos_mailbox();
    company_t * company;
    while(available_companies[company_chosen]){
        company_index = rand() % MAX_COMPANIES;
        
        if(manhatten_distance(mailbox->row, mailbox->column, ))
    }
    available_companies[company_index] = 1;
    return company_index;
}

company_t * choose_company(void) {
    sem_t *sem; 
    company_t *company = (company_t *)malloc(sizeof(company_t));
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


void stole_information(memory_t *memory) {
    company_t *company = choose_company();
    int round = get_round();

    for(int i = 0; i < ROUND_NB_BEFORE_STOLE; i++){

    }

} 














int main(void) {

    pthread_t spies[SPIES_NUMBER];
    
    for(int i = 0; i < SPIES_NUMBER; i++) {
        pthread_create(&spies[i], NULL, spy_routine,NULL);

    }

    for(int i = 0; i < SPIES_NUMBER; i++) {
        pthread_join(spies[i], NULL);
    }
    return 0;
}

