#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <math.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <pthread.h>
#include <time.h>
#include "posix_semaphore.h"
#include "spy_simulation.h"
#include "functions.h"
#include "memory.h"
#include "cell.h"
#include "enemy_spy_network.h"

int main(void) {
    int shmd;
    sem_t *sem;
    memory_t *memory;
    
    srand(time(NULL));

    sem = open_semaphore("spy_simulation-sem");
    P(sem);
    shmd = shm_open("/spy_simulation", O_RDWR, 0666);
    memory = mmap(NULL, sizeof(memory_t), PROT_READ | PROT_WRITE, MAP_SHARED, shmd, 0);

    //Initialize spies
    for(int spie_index = 0; spie_index < SPIES_NUMBER; spie_index++) {
        memory->spies[spie_index].rand_time_for_stoling = 0;
        memory->spies[spie_index].round_number_before_stole = 0;
        memory->spies[spie_index].stroll_in_city = 0;
        memory->spies[spie_index].shopping = 0;
        memory->spies[spie_index].stay_at_home = 0;
        memory->spies[spie_index].rand_day_routine = 0;
        memory->spies[spie_index].random_supermarket = 0;
        memory->spies[spie_index].walking_to_put_fake_msg = 0;
        memory->spies[spie_index].hour = get_hour(memory);
        memory->spies[spie_index].companies_stolen_yet = (int*)calloc(MAX_COMPANIES, sizeof(int));
    }
    //Initialize case_officer
    memory->case_officer.outing_mailbox_1 = create_time(8,0);
    memory->case_officer.outing_mailbox_2 = create_time(12,0);
    memory->case_officer.outing_supermarket = create_time(17,0);
    memory->case_officer.send_messages = create_time(22,0);
    memory->case_officer.random_supermarket = 0;
    memory->case_officer.going_to_mailbox = 0;
    memory->case_officer.going_to_supermarket = 0;

    munmap(memory, sizeof(memory_t));
    close(shmd);
    V(sem);


    sem = open_semaphore("spy_simulation-sem");
    P(sem);
    shmd = shm_open("/spy_simulation", O_RDWR, 0666);
    memory = mmap(NULL, sizeof(memory_t), PROT_READ | PROT_WRITE, MAP_SHARED, shmd, 0);
    
    if(fork() == 0) {
        if(fork() == 0) {
            if(fork() == 0) {
                memory->case_officer_pid = getpid();
                munmap(memory, sizeof(memory_t));
                close(shmd);
                V(sem);
                main_case_officer();
            }
            else {
                memory->spies_pid[2] = getpid();
                munmap(memory, sizeof(memory_t));
                close(shmd);
                V(sem);
                main_spy(2);
                wait(NULL);
            }
        }
        else {
            memory->spies_pid[1] = getpid();
            munmap(memory, sizeof(memory_t));
            close(shmd);
            V(sem);
            main_spy(1); 
            wait(NULL);
        }
    }
    else {
        memory->spies_pid[0] = getpid();
        munmap(memory, sizeof(memory_t));
        close(shmd);
        V(sem);
        main_spy(0);
        wait(NULL);
    }

    // while (1)
    // {
    //     sem = open_semaphore("spy_simulation-sem");
    //     P(sem);
    //     shmd = shm_open("/spy_simulation", O_RDWR, 0666);
    //     memory = mmap(NULL, sizeof(memory_t), PROT_READ | PROT_WRITE, MAP_SHARED, shmd, 0);
        
    //     if (count != memory->count)
    //     {
    //         count = memory->count;
    //         t = (pthread_t *)malloc(sizeof(pthread_t) * SPIES_NUMBER);
    //         args = (args_spy *)malloc(sizeof(args_spy) * SPIES_NUMBER);
    //         for (i = 0; i < SPIES_NUMBER; i++)
    //         {
    //             args[i].spie_index = i;
    //             args[i].memory = memory;
    //         }

    //         for (i = 0; i < SPIES_NUMBER; i++)
    //         {
    //             pthread_create(&t[i], NULL, spie_routine, &args[i]);
    //         }

    //         for (i = 0; i < SPIES_NUMBER; i++)
    //         {
    //             pthread_join(t[i], NULL);
    //         }
    //     }
    //     munmap(memory, sizeof(memory_t));
    //     close(shmd);
    //     V(sem);
    // }
    return 0;
}