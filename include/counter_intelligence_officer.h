#ifndef COUNTER_INTELLIGENCE_OFFICER_H
#define COUNTER_INTELLIGENCE_OFFICER_H
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

typedef struct position{
    int x;
    int y;
} position;

typedef struct counter_intelligence_officer {
    pid_t id; // Id of the officer
    int health;
    position * position;
    position * city_hall_pos;
    position * mailbox_pos;
    pid_t target; 
} counter_officer;

counter_officer * init_counter_officer();


#endif /*COUNTER_INTELLIGENCE_OFFICER_H*/