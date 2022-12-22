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


pid_t get_pids_processes(void) {
    memory_t *memory = malloc(sizeof(memory_t)); 
    pid_t spy_simulation_pid;
    sem_t *sem; 
    sem = open_semaphore("spy_simulation-sem");
    P(sem);
    int shmd = shm_open("/spy_simulation",O_RDWR,0666);
    memory = mmap(NULL, sizeof(memory_t), PROT_READ | PROT_WRITE,MAP_SHARED, shmd,0);
    spy_simulation_pid = memory->spy_simulation_pid;
    printf("pid de spy_simulation got : %d \n", memory->spy_simulation_pid);
    munmap(memory, sizeof(memory_t));
    close(shmd);
    V(sem);
    return spy_simulation_pid;
}

void sent_sig(void) {
    pid_t pid_spy_simulation;
    
    pid_spy_simulation = get_pids_processes();
    
    for(int round = 0; round < ROUND_NUMBER; round++) {
       //if(/*reseau dessocié*/0) kill(pid_spy_simulation, SIGTERM);
       /*else*/ 
       kill(pid_spy_simulation, SIGALRM);
       usleep(DEFAULT_SPAN_ROUND);
    }
    kill(pid_spy_simulation, SIGKILL);
    //To DO other processus kill
    // kill(memory->pid_spy_simulation, SIGALRM);
    // kill(memory->pid_spy_simulation, SIGALRM);
    // kill(memory->pid_spy_simulation, SIGALRM);
}