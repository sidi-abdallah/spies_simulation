#ifndef CHARACTER_H
#define CHARACTER_H

#include "common.h"
#include "cell.h"

/**
 * \brief A given time.
 */
struct time1_s {
    int hour;
    int minutes;
};

typedef struct time1_s time1_t;


enum character_type_e {
    CITIZEN,
    SPY,
    COUNTER_OFFICER,
    CASE_OFFICER
};

enum work_type_e {
    SUPERMARKET_WORK,
    CITY_HALL_WORK,
    COMPANY_WORK
};

typedef enum character_type_e character_type_t;
typedef enum work_type_e work_type_t;
typedef struct character_s character_t;
typedef struct citizen_s citizen_t;
typedef struct spie_s spie_t;
typedef struct case_officer_s case_officer_t;
typedef struct counter_officer_s counter_officer_t;

struct character_s {
    int id;      /*!< Id of the character. */
    int row;     /*!< Row of the location of the character. */
    int column;  /*!< Column of the location of the character. */
};

/**
 * \brief A citizen 
*/
struct citizen_s {
    int id;
    int health_points;
    int location_row;
    int location_column;
    int home_row;
    int home_column;
    int work_row;
    int work_column;
    work_type_t work;
    int shopping;
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
    int round_number_before_stole;
    int rand_time_for_stoling;  
    int rand_day_routine;
    int index_company_being_stolen;
    int shopping; 
    int stay_at_home;
    int stroll_in_city;
    int is_stolling;
    int hour;
    int random_supermarket;
    int * companies_stolen_yet;
    company_type_t message_importance;
    char stolen_message_content[MAX_LENGTH_OF_MESSAGE];
    int go_to_put_msg_in_mailbox;
};

struct case_officer_s {
    int id;
    int health_points;
    int location_row;
    int location_column;
    int home_row;
    int home_column;
    time1_t outing_mailbox_1;
    time1_t outing_mailbox_2;
    time1_t outing_supermarket;
    time1_t send_messages;
    int random_supermarket;
    int going_to_mailbox;
    int going_to_supermarket;
    int at_mailbox;
    int number_of_messages;
    char **messages;
};

struct counter_officer_s {
    int id;
    int health_points;
    int location_row;
    int location_column;
    int has_target;
    int target_index;
    int target_row;
    int target_column;
};

#endif /* CHARACTER_H */
