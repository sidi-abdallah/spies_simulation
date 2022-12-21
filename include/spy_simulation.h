#ifndef SPY_SIMULATION_H
#define SPY_SIMULATION_H

/**
 * \file spy_simulation.h
 *
 * Defines functions used to create the simulation.
 */

#include "memory.h"
#include "common.h"
#include "cell.h"
#include "character.h"

/**
 * \brief Create the map of the map according to configuration given in the subject.
 */
void create_map(memory_t * memory);

/**
 * \brief Create one cell of the map according to its type.
 */
void create_map_cell(memory_t * memory, int type, int row, int column, int nb_of_characters, int * nb_companies, int * nb_residential_buildings, int * nb_supermakets);

/**
 * \brief Create the mailbox of the simulation.
 */
void create_mailbox(memory_t * memory);

/**
 * \brief Create all the characters of the simulation (citizens, spies, counter officer).
 */
void create_characters(memory_t * memory);

/**
 * \brief Create one character according to of his type, his home and his work.
 */
void create_character(memory_t * memory, int id, character_type_t type, int home_row, int home_column, int work_row, int work_column, work_type_t work, int * nb_citizens, int * nb_spies);

/**
 * \brief Return the list of all the characters of the simulation.
 */
character_t * get_characters(memory_t * memory);

/**
 * \brief Manage the meshed surveillance network in order to find spies.
 */
void mesh_surveillance_network(memory_t * memory);

/**
 * \brief Set the handler of the signals.
 */
void set_signal_handler();

/**
 * \brief Handle the signals for a new round or the end of the simulation.
 */
void signal_handler(int signum);

/**
 * \brief Manage a new round.
 */
void new_round();

/**
* Set informations for each companies according to the number of citizins working in the company. 
*/
void set_companies_informations(memory_t * memory);

#endif /* SPY_SIMULATION_H */
