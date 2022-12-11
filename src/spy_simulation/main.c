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

    memory_t * memory;
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

    create_map(memory);
    create_mailbox(memory);
    create_characters(memory);

    set_signal_handler();
    while(1) {

    }
    
    munmap(memory, sizeof(memory_t));
    close(shmd);
    shm_unlink("/spy_simulation");
}