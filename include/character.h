#ifndef CHARACTER_H
#define CHARACTER_H

#include "common.h"

enum character_type_e {
    CITIZEN,
    SPIE,
    COUNTER_OFFICER,
    CASE_OFFICER
};

enum job_type_e {
    SUPERMARKET_JOB,
    CITY_HALL_JOB,
    COMPANY_JOB
};

typedef enum job_type_e job_type_t;
typedef struct character_s character_t;
typedef struct citizen_s citizen_t;
typedef struct spie_s spie_t;
typedef struct case_officer_s case_officer_t;
typedef struct counter_officer_s counter_officer_t;

struct character_s {
    int id;
    int location_row;
    int location_column;
};

/**
 * \brief A citizen 
*/
struct citizen_s {
    int current_row;
    int current_column;
    int habitation_row;
    int habitation_column;
    int job_row;
    int job_column;
    int life_points;
    job_type_t job;
};

struct spie_s {
    int id;
    int health_points;
    int location_row;
    int location_column;
    int home_row;
    int home_column;
    int nb_of_stolen_companies;
    int has_license_to_kill;
    char stolen_message_content[MAX_LENGTH_OF_MESSAGE];
};

struct case_officer_s {
    int id;
    int health_points;
    int location_row;
    int location_column;
    int home_row;
    int home_column;
    int mailbox_row;
    int mailbox_column;
};

struct counter_officer_s {
    int current_row;
    int current_column;
    int habitation_row;
    int habitation_column;
    int life_points;
};

#endif /* CHARACTER_H */
