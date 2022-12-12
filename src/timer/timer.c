#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/types.h>
#include "monitor_common.h"
#include <sys/ioctl.h>
#include "memory.h"
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/stat.h>        /* Pour les constantes des modes */
#include <fcntl.h>  
#include <string.h>
#include "posix_semaphore.h"

int get_pids_processes(memory_t *memory) {
    int pid_spy_simulation;  
    sem_t *sem; 
    sem = open_semaphore("sem_test-sem");
    P(sem);
    int shmd = shm_open("/share_memory__test",O_RDWR,0666);
    memory = mmap(NULL, sizeof(memory_t), PROT_READ | PROT_WRITE,MAP_SHARED, shmd,0);
    pid_spy_simulation = memory->pid_spy_simulation;
    printf("pid de spy_simulation got : %d \n", memory->pid_spy_simulation);
    munmap(memory, sizeof(memory_t));
    close(shmd);
    V(sem);
    return pid_spy_simulation;
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
    memory_t *memory = (memory_t *)malloc(sizeof(memory_t)); 
    pid_spy_simulation = get_pids_processes(memory);
   
    for(int round = 0; round < ROUND_NUMBER; round++) {
       //if(/*reseau dessocié*/0) kill(pid_spy_simulation, SIGTERM);
       /*else*/ 
       kill(pid_spy_simulation, SIGALRM);
       usleep(TIME_STEP);
    }
    kill(pid_spy_simulation, SIGKILL);
    //To DO other processus kill
    // kill(memory->pid_spy_simulation, SIGALRM);
    // kill(memory->pid_spy_simulation, SIGALRM);
    // kill(memory->pid_spy_simulation, SIGALRM);
}

int main(int argc, char * argv[]){
    sent_sig();
    return 0;
}
