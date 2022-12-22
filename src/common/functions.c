#include "functions.h"
#include <stdio.h>
#include <stdlib.h>

#include "math.h"

int manhattan_distance(int x1, int y1, int x2, int y2) {
    return abs(x2 - x1) + abs(y2 - y1);
}

int get_hour(memory_t *memory) {
    return ((int) floor((memory->count/6)))%24;
}

int get_minutes(memory_t *memory) {
    return (memory->count * 10)%60;
}

time1_t create_time(int hour, int minutes) {
    time1_t res;
    res.hour = hour;
    res.minutes = minutes;
    return res;
}
