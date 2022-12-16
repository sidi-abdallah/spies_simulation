#ifndef COUNTER_INTELLIGENCE_H
#define COUNTER_INTELLIGENCE_H

#include "memory.h"
#include "cell.h"
#include "character.h"


struct detection_material_s {
    bool expected_spy;
    int* counter;
};

bool is_citizen_in_cell( cell_t* cell,citizen_t citizen );
void update_detection(cell_t* cell, citizen_t citizen);
void detect_anomaly(memory_t *memory);


#endif // COUNTER_INTELLIGENCE_H