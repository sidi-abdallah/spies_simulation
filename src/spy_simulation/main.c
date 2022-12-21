#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>
#include <sys/mman.h> 
#include <sys/stat.h>

#include "spy_simulation.h"
#include "posix_semaphore.h"

int main(void)
{
    srand(time(NULL));

    memory_t * memory;
    sem_t *sem;
    sem = create_and_open_semaphore("/spy_simulation-sem");
    int shmd = shm_open("/spy_simulation", O_CREAT | O_RDWR, (mode_t)0600);
    if(shmd == -1) {
        perror("shmd failed");
    }
    if(ftruncate(shmd, sizeof(memory_t)) == -1) {
        perror("shmd truncate failed");
    }

    P(sem);
    memory = mmap(NULL, sizeof(memory_t), PROT_READ | PROT_WRITE, MAP_SHARED, shmd,0);
    create_map(memory);
    create_mailbox(memory);
    create_characters(memory);
    set_companies_informations(memory);
    memory->spy_simulation_pid = getpid();
    memory->count = 0;
    munmap(memory, sizeof(memory_t));
    close(shmd);
    V(sem);

    while(1) {
       // pause();
        set_signal_handler();
    }

}