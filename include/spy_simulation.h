#ifndef SPY_SIMULATION_H
#define SPY_SIMULATION_H

#define CITY_HALL_MAX_CAPACITY 20
#define COMPANY_MAX_CAPACITY 50
#define SUPERMAKET_MAX_CAPACITY 30
#define HABITATION_BUILDING_MAX_CAPACITY 15
#define EMPTY_MAX_CAPACITY 999

#define NB_COMPANY 8
#define NB_SUPERMAKET 2
#define NB_HABITATION_BUILDING 11

#define GRID_WIDTH 7
#define GRID_HEIGHT 7

typedef struct cell cell;
typedef struct city city;

typedef enum {CITY_HALL, COMPANY, SUPERMARKET, HABITATION_BUILDING, EMPTY}building_type;

struct cell {
    building_type type;
    int max_capacity;
};

struct city {
    cell * grid[7][7];
}; 

city * makeCity();
city * make_conf();
cell * makeCell(int type);
void print_city();

#endif //SPY_SIMULATION_H