#ifndef COUNTER_INTELLIGENCE_OFFICER_H
#define COUNTER_INTELLIGENCE_OFFICER_H
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include "cell.h"
#include <sys/stat.h>
#include <math.h>

#define CITY_HALL_X 4
#define CITY_HALL_Y 4
#define GRID_WIDTH 7
#define GRID_HEIGHT 7
#define NB_ROUNDS_SUSPECT 12 // if a person in the city stay in peripherals of a company for more than 12 rounds, 
                             // then hi is a suspect

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

typedef struct person{
    position * location;
} person;

typedef struct city {
    cell * grid[7][7];
    person * person; // structure which describe every citizen (to be implemented)
} city; 




counter_officer * memory_alloc_counter_officer();
void init_counter_officer(counter_officer *);
void people_surveillance(city *);
int there_is_suspect();
position * company_targetted_by_suspect(int);









#endif /*COUNTER_INTELLIGENCE_OFFICER_H*/