#include "timer.h"
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/types.h>
//#include "monitor_common.h"
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
    switch (signum) {
        case SIGALRM:
                printf("moi qui ai un pid = %d j'ai reussi un signal SIGALRM\n", getpid());
        case SIGTERM:
                printf("moi qui ai un pid = %d j'ai reussi un signal SIGTERM\n", getpid());

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
    action.sa_handler = &handler;
    action.sa_flags = 0;
    sigemptyset(&action.sa_mask);

    /* Set signal handlers */
    sigaction(SIGTERM, &action, NULL);
    sigaction(SIGINT, &action, NULL);
    sigaction(SIGALRM, &action, NULL);

    /*  Ignore SIGTSTP  */
    action.sa_handler = SIG_IGN;
    sigaction(SIGTSTP, &action, NULL);
}


 void set_pids_processes(void) {
    struct Processes_Pids *processes_Pids = malloc(sizeof(struct Processes_Pids)); 
    sem_t *sem; 
    sem = open_semaphore("sem_test-sem");
    P(sem);
    int shmd = shm_open("/share_memory__test",O_RDWR,0666);
    processes_Pids = mmap(NULL, sizeof(struct Processes_Pids), PROT_READ | PROT_WRITE,MAP_SHARED, shmd,0);
    processes_Pids->pid_spy_simulation = getpid();
    printf("pid de spy simulation set: %d \n", processes_Pids->pid_spy_simulation);
    munmap(processes_Pids, sizeof(struct Processes_Pids));
    close(shmd);
    V(sem);
} 

void create_sem_memory_for_test(void) {
    int shmd = shm_open("/share_memory__test",O_CREAT|O_RDWR,S_IRUSR|S_IWUSR);
    if(ftruncate(shmd, sizeof(struct Processes_Pids)) == -1 ) 
        perror("can't create shared memory\n");

    sem_t *sem;
    sem = create_and_open_semaphore("sem_test-sem");
}

int main(void) {

    create_sem_memory_for_test();
    set_pids_processes();
    while(1) {
        set_signals();
    }
    return 0;
}