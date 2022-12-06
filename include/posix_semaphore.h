#ifndef __SEM_H
#define __SEM_H
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <semaphore.h>
#include <stddef.h>
#include <sys/stat.h>

struct maChaine{
    pid_t pid;
    int a;
    char chaine1[256];
    char chaine2[256];
    char  chaine3[256];
};

typedef sem_t semaphore_t;


void handle_fatal_error(const char *message);

semaphore_t *create_and_open_semaphore(char *name);

semaphore_t *open_semaphore(char *name);

void destroy_semaphore(semaphore_t *sem, char *name);

void P(semaphore_t *sem);

void V(semaphore_t *sem);



#endif