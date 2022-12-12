#include "timer.h"
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/types.h>
#include "monitor_common.h"
#include "monitor.h"
#include "memory.h"
#include <sys/ioctl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/stat.h>        /* Pour les constantes des modes */
#include <fcntl.h>  
#include <string.h>
#include "posix_semaphore.h"

int count = 0;

void handler(int signum) {
    sem_t *sem; 
    memory_t *memory = (memory_t *) malloc(sizeof(memory_t));
    switch (signum) {
        case SIGALRM:
            sem = open_semaphore("sem_test-sem");
            P(sem);
            int shmd = shm_open("/share_memory__test",O_RDWR,0666);
            memory = mmap(NULL, sizeof(memory_t), PROT_READ | PROT_WRITE,MAP_SHARED, shmd,0);
            memory->count++;
            memory->memory_has_changed = 1;
            munmap(memory, sizeof(memory_t));
            close(shmd);
            V(sem);
                break;
        case SIGTERM:
                printf("moi qui ai un pid = %d j'ai reussi un signal SIGTERM\n", getpid());
                count++;
                break;
         case SIGINT:
                exit(0);
        //     quit_nicely(NO_PARTICULAR_REASON);
        default:
            break;
    }
}

//Appel handler à l'aide d'une sigaction
void set_signals() {
    struct sigaction action;
    action.sa_handler = handler;
    action.sa_flags = 0;
    sigemptyset(&action.sa_mask);

    /* Set signal handlers */
     sigaction(SIGTERM, &action, NULL);
    sigaction(SIGALRM, &action, NULL);

    /*  Ignore SIGTSTP  */
    action.sa_handler = SIG_IGN;
    sigaction(SIGTSTP, &action, NULL);
    // action.sa_handler = SIG_IGN;
    // sigaction(SIGTSTP, &action, NULL);
}


 void set_pids_processes(void) {
    memory_t *memory = (memory_t *)malloc(sizeof(memory_t));
    int shmd = 0;
    sem_t *sem = open_semaphore("sem_test-sem");
    P(sem);
    shmd = shm_open("/share_memory__test",O_RDWR,0666);
    memory = mmap(NULL, sizeof(memory_t), PROT_READ | PROT_WRITE,MAP_SHARED, shmd,0);
    memory->pid_spy_simulation = getpid();
    printf("pid de spy simulation set: %d \n", memory->pid_spy_simulation);
    munmap(memory, sizeof(memory_t));
    close(shmd);
    V(sem);
} 

void create_sem_memory_for_test(void) {
    int shmd = shm_open("/share_memory__test",O_CREAT|O_RDWR,/*S_IRUSR|S_IWUSR*/0666);
    if(ftruncate(shmd, sizeof(memory_t)) == -1 ) {
        perror("can't create shared memory\n");
    }
    sem_t *sem = create_and_open_semaphore("sem_test-sem");
}

int main(void) {

    create_sem_memory_for_test();
    set_pids_processes();
     while(1) {
         set_signals();
     }
     return 0;
}