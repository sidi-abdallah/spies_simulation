#include "spy_simulation.h"
#include <stdio.h>
#include <stdlib.h>

city * makeCity() {
    city * cityPT = (city *) malloc(sizeof(city));
    int i, cellAdded, x, y;

    cityPT->grid[3][3] = makeCell(CITY_HALL);

    for(i=0; i<NB_COMPANY; i++) {
        cellAdded = 0;
        while(!cellAdded) {
            x = rand()%GRID_HEIGHT;
            y = rand()%GRID_WIDTH;
            if(1) {
                cityPT->grid[x][y] = makeCell(COMPANY);
            }
        }
    }

    for(i=0; i<NB_SUPERMAKET; i++) {
        cellAdded = 0;
        while(!cellAdded) {
            x = rand()%GRID_HEIGHT;
            y = rand()%GRID_WIDTH;
            if(1) {
                cityPT->grid[x][y] = makeCell(SUPERMARKET);
            }
        }
    }

    for(i=0; i<NB_HABITATION_BUILDING; i++) {
        cellAdded = 0;
        while(!cellAdded) {
            x = rand()%GRID_HEIGHT;
            y = rand()%GRID_WIDTH;
            if(1) {
                cityPT->grid[x][y] = makeCell(HABITATION_BUILDING);
            }
        }
    }
    return cityPT;
}

cell * makeCell(int type) {
    return NULL;
}