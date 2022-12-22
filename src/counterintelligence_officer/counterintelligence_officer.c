#include "counterintelligence_officer.h"
#include "memory.h"
#include "posix_semaphore.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <signal.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/mman.h> 
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

void set_signal_handler() {
    struct sigaction action;
    action.sa_handler = signal_handler;
    action.sa_flags = 0;
    sigemptyset(&action.sa_mask);

    sigaction(SIGTERM, &action, NULL);

    sigaction(SIGALRM, &action, NULL);

    action.sa_handler = SIG_IGN;
    sigaction(SIGTSTP, &action, NULL);
}

void signal_handler(int signum) {
    switch (signum) {
        case SIGALRM:
            new_target();
            break;
        case SIGTERM:
            //printf("signal SIGTERM\n");
            break;
         case SIGINT:
            //printf("signal SIGINT\n");
            exit(0);
        default:
            break;
    }
}

void new_target() {
    int fd, index, row, column, shmd;
    sem_t* sem;
    memory_t *memory;
    
    fd = open("counterintellifence_officer", O_WRONLY);
    char buff[20];
    if(read(fd, buff, sizeof(buff)) == -1){
        return;
    }
    sscanf(buff, "%d %d %d", &index, &row, &column);
    close(fd);

    sem = open_semaphore("spy_simulation-sem");
    P(sem);
    shmd = shm_open("/spy_simulation", O_RDWR, 0666);
    memory = mmap(NULL, sizeof(memory_t), PROT_READ | PROT_WRITE, MAP_SHARED, shmd, 0);

    if(memory->counter_officer.has_target == 0) {
        memory->counter_officer.target_index = index;
        memory->counter_officer.target_row = row;
        memory->counter_officer.target_column = column;
        memory->counter_officer.has_target = 1;
    }
    munmap(memory, sizeof(memory_t));
    close(shmd);
    V(sem);
}

void go_target(memory_t * memory) {
    
}