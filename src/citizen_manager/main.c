#include "citizen_manager.h"
#include "posix_semaphore.h"
#include "memory.h"

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/mman.h> 
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <assert.h>

#include "spy_simulation.h"

int main() {
    srand(time(NULL));

    memory_t *memory;
    memory = malloc(sizeof(memory_t));
    sem_t *sem; 
    int shmd;
    int i;
    int count = 0;
    pthread_t *t;
    args_t *args;

    sem = open_semaphore("spy_simulation-sem");
    
       
    P(sem);
    shmd = shm_open("/spy_simulation",O_RDWR,0666);
    memory = mmap(NULL, sizeof(memory_t), PROT_READ | PROT_WRITE,MAP_SHARED, shmd,0);
    memory->citizens_at_home = NUMBER_OF_CITIZENS;
    memory->citizens_at_work = 0;
    memory->citizens_walking = 0;
    munmap(memory, sizeof(memory_t));
    close(shmd);
    V(sem);
    while (1) {
        sem = open_semaphore("spy_simulation-sem");
        P(sem);
        shmd = shm_open("/spy_simulation",O_RDWR,0666);
        memory = mmap(NULL, sizeof(memory_t), PROT_READ | PROT_WRITE,MAP_SHARED, shmd,0);
       
        if (memory->count != count) {
            count = memory->count;
            t = (pthread_t *) malloc(sizeof(pthread_t) * NUMBER_OF_CITIZENS);
            args = (args_t *) malloc(sizeof(args_t) * NUMBER_OF_CITIZENS);
            for(i=0; i<NUMBER_OF_CITIZENS; i++) {
                args[i].citizen_index = i;
                args[i].memory = memory;
            }

            for(i=0; i<NUMBER_OF_CITIZENS; i++) {
                pthread_create(&t[i], NULL, make_round, &args[i]);
            }

            for(i=0; i<NUMBER_OF_CITIZENS; i++) {
                pthread_join(t[i], NULL);
            }
        }
        munmap(memory, sizeof(memory_t));
        close(shmd);
        V(sem);
    }
}
