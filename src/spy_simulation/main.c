#include "spy_simulation.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv)
{
    srand(time(NULL));
    city * city_simulation = makeCity();
    printf("CITY MADE\n");
    print_city(city_simulation);
}