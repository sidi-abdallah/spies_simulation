#ifndef COUNTERINTELLIGENCE_OFFICER_H
#define COUNTERINTELLIGENCE_OFFICER_H

/**
 * \file counterintelligence_officer.h
 *
 * Defines functions used by the counterintelligence officer.
 */

#include "memory.h"

/**
 * @brief Define the signal handler.
*/
void set_signal_handler();

/**
 * @brief Handle the receive signal and call the function new_target if the signal is received by the suiveillance network.
*/
void signal_handler(int signum);

/**
 * @brief Read on the named pipe the new target.
*/
void new_target();

/**
 * @brief Make the officer routine if he has a target.
*/
void go_target(memory_t * memory);

void get_next_cell(memory_t * memory, int destination_row, int destination_column, int *next_row, int * next_column);

#endif //COUNTERINTELLIGENCE_OFFICER_H