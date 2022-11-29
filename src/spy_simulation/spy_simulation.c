#include "spy_simulation.h"
#include <stdio.h>
#include <stdlib.h>

city * make_conf() {
    city * cityPT = (city *) malloc(sizeof(city));

    cityPT->grid[3][3] = makeCell(CITY_HALL);

    cityPT->grid[0][1] = makeCell(COMPANY);
    cityPT->grid[0][3] = makeCell(COMPANY);
    cityPT->grid[0][6] = makeCell(COMPANY);
    cityPT->grid[3][4] = makeCell(COMPANY);
    cityPT->grid[4][2] = makeCell(COMPANY);
    cityPT->grid[5][2] = makeCell(COMPANY);
    cityPT->grid[5][6] = makeCell(COMPANY);
    cityPT->grid[6][1] = makeCell(COMPANY);

    cityPT->grid[1][0] = makeCell(HABITATION_BUILDING);
    cityPT->grid[1][5] = makeCell(HABITATION_BUILDING);
    cityPT->grid[2][1] = makeCell(HABITATION_BUILDING);
    cityPT->grid[2][3] = makeCell(HABITATION_BUILDING);
    cityPT->grid[2][6] = makeCell(HABITATION_BUILDING);
    cityPT->grid[4][1] = makeCell(HABITATION_BUILDING);
    cityPT->grid[4][6] = makeCell(HABITATION_BUILDING);
    cityPT->grid[5][4] = makeCell(HABITATION_BUILDING);
    cityPT->grid[6][0] = makeCell(HABITATION_BUILDING);
    cityPT->grid[6][4] = makeCell(HABITATION_BUILDING);
    cityPT->grid[6][6] = makeCell(HABITATION_BUILDING);

    cityPT->grid[1][2] = makeCell(SUPERMARKET);
    cityPT->grid[4][3] = makeCell(SUPERMARKET);

    cityPT->grid[0][0] = makeCell(EMPTY);
    cityPT->grid[0][2] = makeCell(EMPTY);
    cityPT->grid[0][4] = makeCell(EMPTY);
    cityPT->grid[0][5] = makeCell(EMPTY);
    cityPT->grid[1][1] = makeCell(EMPTY);
    cityPT->grid[1][3] = makeCell(EMPTY);
    cityPT->grid[1][4] = makeCell(EMPTY);
    cityPT->grid[1][6] = makeCell(EMPTY);
    cityPT->grid[2][0] = makeCell(EMPTY);
    cityPT->grid[2][2] = makeCell(EMPTY);
    cityPT->grid[2][4] = makeCell(EMPTY);
    cityPT->grid[2][5] = makeCell(EMPTY);
    cityPT->grid[3][0] = makeCell(EMPTY);
    cityPT->grid[3][1] = makeCell(EMPTY);
    cityPT->grid[3][2] = makeCell(EMPTY);
    cityPT->grid[3][5] = makeCell(EMPTY);
    cityPT->grid[3][6] = makeCell(EMPTY);
    cityPT->grid[4][0] = makeCell(EMPTY);
    cityPT->grid[4][4] = makeCell(EMPTY);
    cityPT->grid[4][5] = makeCell(EMPTY);
    cityPT->grid[5][0] = makeCell(EMPTY);
    cityPT->grid[5][1] = makeCell(EMPTY);
    cityPT->grid[5][3] = makeCell(EMPTY);
    cityPT->grid[5][5] = makeCell(EMPTY);
    cityPT->grid[6][2] = makeCell(EMPTY);
    cityPT->grid[6][3] = makeCell(EMPTY);
    cityPT->grid[6][5] = makeCell(EMPTY);


}

city * makeCity() {
    city * cityPT = (city *) malloc(sizeof(city));
    int i, j, cellAdded, x, y;

    cityPT->grid[3][3] = makeCell(CITY_HALL);

    for(i=0; i<NB_COMPANY; i++) {
        cellAdded = 0;
        while(!cellAdded) {
            x = rand()%GRID_HEIGHT;
            y = rand()%GRID_WIDTH;
            if(cityPT->grid[x][y] == NULL) {
                cityPT->grid[x][y] = makeCell(COMPANY);
                cellAdded = 1;
            }
        }
    }

    for(i=0; i<NB_SUPERMAKET; i++) {
        cellAdded = 0;
        while(!cellAdded) {
            x = rand()%GRID_HEIGHT;
            y = rand()%GRID_WIDTH;
            if(cityPT->grid[x][y] == NULL) {
                cityPT->grid[x][y] = makeCell(SUPERMARKET);
                cellAdded = 1;
            }
        }
    }

    for(i=0; i<NB_HABITATION_BUILDING; i++) {
        cellAdded = 0;
        while(!cellAdded) {
            x = rand()%GRID_HEIGHT;
            y = rand()%GRID_WIDTH;
            if(cityPT->grid[x][y] == NULL) {
                cityPT->grid[x][y] = makeCell(HABITATION_BUILDING);
                cellAdded = 1;
            }
        }
    }

    for(i=0; i<GRID_WIDTH; i++) {
        for(j=0; j<GRID_HEIGHT; j++) {
            if(cityPT->grid[i][j] == NULL) {
                cityPT->grid[i][j] = makeCell(EMPTY);
            }
        }
    }

    return cityPT;
}

cell * makeCell(int type) {
    cell * c = (cell *)malloc(sizeof(cell));
    c->type = type;
    switch(type) {
        case CITY_HALL : 
            c->max_capacity = CITY_HALL_MAX_CAPACITY;
        break;
        case COMPANY : 
            c->max_capacity = COMPANY_MAX_CAPACITY;
        break;
        case SUPERMARKET :
            c->max_capacity = SUPERMAKET_MAX_CAPACITY;
        break;
        case HABITATION_BUILDING :
            c->max_capacity = HABITATION_BUILDING_MAX_CAPACITY;
        break;
        default :
            c->max_capacity = EMPTY_MAX_CAPACITY;
    }
    return c;
}

void print_city(city * city) {
    int i, j;
    int letter[5] = {'H', 'F', 'S', 'B', 'O'};
    for(i=0; i<GRID_WIDTH; i++) {
        for(j=0; j<GRID_HEIGHT; j++) {
            printf("%c ", letter[city->grid[i][j]->type]);
        }
        printf("\n");
    }
}