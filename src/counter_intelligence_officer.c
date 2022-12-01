#include "counter_intelligence_officer.h"
#define CITY_HALL_X 4
#define CITY_HALL_Y 4

counter_officer * memory_alloc_counter_officer(){
    counter_officer * cio;
    cio = (counter_officer *)malloc(sizeof(counter_officer));
    cio->position = (position *)malloc(sizeof(position));
    cio->city_hall_pos = (position *)malloc(sizeof(position));
    cio->mailbox_pos = (position *)malloc(sizeof(position));
    retrun cio;
}

void init_counter_officer(counter_officer * cio){
    id = getpid();
    health = 10;
    cio->city_hall_pos->x = CITY_HALL_X;
    cio->city_hall_pos->y = CITY_HALL_Y;
    cio->position->x = CITY_HALL_X;
    cio->position->y = CITY_HALL_Y;
    cio->mailbox_pos->x = 0;
    cio->mailbox_pos->y = 0;
    return;
}

