#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>
#include <sys/mman.h> 
#include <sys/stat.h>

#include "spy_simulation.h"
#include "posix_semaphore.h"

int main(int argc, char **argv)
{
    srand(time(NULL));

    printf(".bin/spy_simulation\n");

    memory_t * memory;
    sem_t *sem;
    sem = create_and_open_semaphore("/spy_simulation-sem");
    destroy_semaphore(sem, "/spy_simulation-sem");
    sem = create_and_open_semaphore("/spy_simulation-sem");
    int shmd = shm_open("/spy_simulation", O_CREAT | O_RDWR, (mode_t)0600);
    if(shmd == -1) {
        perror("shmd failed");
    }
    if(ftruncate(shmd, sizeof(memory_t)) == -1) {
        perror("shmd truncate failed");
    }
    memory = mmap(NULL, sizeof(memory_t), PROT_READ | PROT_WRITE, MAP_SHARED, shmd,0);
    if (memory == MAP_FAILED) {
        perror("mmap failed");
        return -1;
    }
    P(sem);
    

    create_map(memory);
    create_mailbox(memory);
    create_characters(memory);
    memory->spy_simulation_pid = getpid();
    memory->count = 0;

    munmap(memory, sizeof(memory_t));
    close(shmd);
    V(sem);

    set_signal_handler();
    printf("READY\n");
    while(1) {

    }
}