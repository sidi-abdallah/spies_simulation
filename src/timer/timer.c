#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/types.h>
#include "monitor_common.h"
#include <sys/ioctl.h>
#include <memory.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/stat.h>        /* Pour les constantes des modes */
#include <fcntl.h>  
#include <string.h>
#include "posix_semaphore.h"
#include "memory.h"
#include "common.h"
#include "timer.h"


//créer un sémaphore et un mémoire partagé de test
void get_pids_processes(void) {
    memory_t *memory = malloc(sizeof(memory_t)); 
    sem_t *sem; 
    sem = open_semaphore("sem_test-sem");
            P(sem);
            int shmd = shm_open("/share_memory__test",O_RDWR,0666);
            memory = mmap(NULL, sizeof(memory_t), PROT_READ | PROT_WRITE,MAP_SHARED, shmd,0);
            printf("pid de spy_simulation got : %d \n", memory->spy_simulation_pid);
            munmap(memory, sizeof(memory_t));
            close(shmd);
            V(sem);
}

// Le pas de temps (200ms ici)
void set_timer(void) {
    struct itimerval it;

    /* Clear itimerval struct members */
    timerclear(&it.it_interval);
    timerclear(&it.it_value);

    /* Set timer */
    it.it_interval.tv_usec = TIME_STEP;
    it.it_value.tv_usec = TIME_STEP;
    setitimer(ITIMER_REAL, &it, NULL);
}

void sent_sig(void) {
    pid_t pid_spy_simulation;
    memory_t *memory = malloc(sizeof(memory_t)); 
    sem_t *sem; 
    
    int shmd = shm_open("/spy_simulation",O_RDWR,0666);
    memory = mmap(NULL, sizeof(memory_t), PROT_READ | PROT_WRITE,MAP_SHARED, shmd,0);
    
    sem = open_semaphore("/spy_simulation-sem");
    P(sem);
    pid_spy_simulation = memory->spy_simulation_pid;
    V(sem);

    munmap(memory, sizeof(memory_t));
    
    for(int round = 0; round < ROUND_NUMBER; round++) {
       //if(/*reseau dessocié*/0) kill(pid_spy_simulation, SIGTERM);
       /*else*/ 
       // printf("%d\n", round);
       kill(pid_spy_simulation, SIGALRM);
        usleep(DEFAULT_SPAN_ROUND);
        //set_timer();
    }
    kill(pid_spy_simulation, SIGKILL);
    //To DO other processus kill
    // kill(memory->pid_spy_simulation, SIGALRM);
    // kill(memory->pid_spy_simulation, SIGALRM);
    // kill(memory->pid_spy_simulation, SIGALRM);
}