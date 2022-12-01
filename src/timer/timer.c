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

// struct Processes_Pids {
//     pid_t pid;
//     int a;
//     int count;
// };

struct Processes_Pids {
     pid_t pid;
     int a;
     int pid_spy_simulation ;
 };


//créer un sémaphore et un mémoire partagé de test
void create_sem_memory_for_test(void) {
    int shmd = shm_open("/share_memory__test",O_CREAT|O_RDWR,S_IRUSR|S_IWUSR);
    if(ftruncate(shmd, sizeof(struct Processes_Pids)) == -1 ) 
        perror("can't create shared memory\n");

    sem_t *sem;
    sem = create_and_open_semaphore("sem_test-sem");
}


void get_pids_processes(void) {
    struct Processes_Pids *processes_Pids; //= calloc(2, sizeof(int));  
    sem_t *sem; 
    sem = open_semaphore("sem_test-sem");
        //P(sem);
            int shmd = shm_open("/share_memory__test",O_RDWR,0666);
            processes_Pids = mmap(NULL, sizeof(struct Processes_Pids), PROT_READ | PROT_WRITE,MAP_SHARED, shmd,0);
            printf("counter : %d \n", Processes_Pids->pid_spy_simulation);
            munmap(Processes_Pids, sizeof(struct Processes_Pids));
            close(shmd);
            //V(sem);
} 
//fonction exécutée à chque tour
void handler(int signum) {
    struct Processes_Pids *Processes_Pids = calloc(2, sizeof(int));  
    sem_t *sem; 

    switch (signum) {
        case SIGALRM:
            sem = open_semaphore("sem_test-sem");

            //P(sem);
            int shmd = shm_open("/share_memory__test",O_RDWR,0666);
            Processes_Pids = mmap(NULL, sizeof(struct Processes_Pids), PROT_READ | PROT_WRITE,MAP_SHARED, shmd,0);
            Processes_Pids->count++;
            printf("counter : %d \n", Processes_Pids->count);
            munmap(Processes_Pids, sizeof(struct Processes_Pids));
            close(shmd);
            //V(sem);
            alarm(1);
           // ualarm(TIME_STEP, 0);
        case SIGTERM:
        // case SIGINT:
        //     quit_nicely(NO_PARTICULAR_REASON);
        default:
            break;
    }
}

// Le pas de temps (200ms ici)
void set_timer(void)
{
    struct itimerval it;

    /* Clear itimerval struct members */
    timerclear(&it.it_interval);
    timerclear(&it.it_value);

    /* Set timer */
    it.it_interval.tv_usec = TIME_STEP;
    it.it_value.tv_usec = TIME_STEP;
    setitimer(ITIMER_REAL, &it, NULL);
}

//Appel handler à l'aide d'une sigaction
int set_signals()
{
    struct sigaction action;

    memset(&action, 0, sizeof(action));
    action.sa_handler = &handler;
   
    if(sigaction(SIGALRM, &action, NULL) == -1) {
        perror("erreur de passer à handler\n");
        return -1;
    }
    alarm(1);
    return 0;
    //ualarm(TIME_STEP, 0);
   // set_timer(); // attendre TIME_STEP avant d'envoyer un signal à handler
}

void sent_sig(void) {
    for(int round = 0; round < ROUND_NUMBER; round++) {
       // if(/*reseau dessocié*/0) handler(SIGTERM);
        /*else*/
        if(kill(processes_Pids->pid_spy_simulation, SIGALRM)==-1) {
            perror("can't sent sig!!\n");
        }
    }
    kill(processes_Pids->pid_spy_simulation, SIGTERM);
    //To DO other processus kill
    // kill(processes_Pids->pid_spy_simulation, SIGALRM);
    // kill(processes_Pids->pid_spy_simulation, SIGALRM);
    // kill(processes_Pids->pid_spy_simulation, SIGALRM);
}

int main(int argc, char * argv[]){
    int status;
    create_sem_memory_for_test();
    // int i = 0;
    // for(int round = 0; round < ROUND_NUMBER; round++) {
        if(fork()==0) {
            set_signals();
            // i++;
        }
       while(1);
        // else {
        //     wait(&status);
        //     printf("child exit code: %d\n", WEXITSTATUS(status));
        // }
    //while(i < ROUND_NUMBER);

       // else wait(0);
   // }    //sent_sig();
   // exit(EXIT_SUCCESS);
}
