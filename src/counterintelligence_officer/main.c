#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>
#include <sys/mman.h> 
#include <sys/stat.h>

#include "posix_semaphore.h"
#include "memory.h"
#include "counterintelligence_officer.h"

int main() {
    memory_t * memory;
    sem_t *sem;
    sem = open_semaphore("spy_simulation-sem");
    int shmd = shm_open("/spy_simulation", O_CREAT | O_RDWR, (mode_t)0600);
    if(shmd == -1) {
        perror("shmd failed");
    }
  

    P(sem);
    memory = mmap(NULL, sizeof(memory_t), PROT_READ | PROT_WRITE, MAP_SHARED, shmd,0);
    memory->counter_intelligence_officer_pid = getpid();
    munmap(memory, sizeof(memory_t));
    close(shmd);
    V(sem);

    while(1) {
        set_signal_handler();
        sem = open_semaphore("spy_simulation-sem");
        P(sem);
        shmd = shm_open("/spy_simulation", O_RDWR, 0666);
        memory = mmap(NULL, sizeof(memory_t), PROT_READ | PROT_WRITE, MAP_SHARED, shmd, 0);

        if(memory->counter_officer.has_target == 1){
            go_target(memory);
        }

        munmap(memory, sizeof(memory_t));
        close(shmd);
        V(sem);
    }
}
