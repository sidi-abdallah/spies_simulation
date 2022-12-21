/*
 * The License to Kill Project
 *
 * Copyright (C) 1995-2022 Alain Lebret <alain.lebret [at] ensicaen [dot] fr>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef MEMORY_H
#define MEMORY_H

#include "cell.h"
#include "character.h"
#include "common.h"
#include "mesh_surveillance_network.h"
#include <sys/types.h> 
#include <unistd.h>

/**
 * \file memory.h
 *
 * Defines structures and functions used to manipulate our shared memory.
 */

typedef struct map_s map_t;
typedef struct memory_s memory_t;

/**
 * \brief The city map.
 */
struct map_s {
    int columns;                         /*!< The number of columns of the city map. */
    int rows;                            /*!< The number of rows of the city map.*/
    cell_t cells[MAX_COLUMNS][MAX_ROWS]; /*!< Cells that constitute the city map. */
};

/**
 * \brief Shared memory used by all processes.
 */
struct memory_s {
    int memory_has_changed;    /*!< This flag is set to 1 when the memory has changed. */
    int simulation_has_ended;  /*!< This flag is set to the following values:
                                * - 0: has not ended;
                                * - 1: the spy network has fled. It wins!
                                * - 2: the counterintelligence officer has discovered the mailbox. He wins.
                                * - 3: the counterintelligence officer did not discover the mailbox. The spy network
                                *      wins!
                                */
    
    map_t map;                  /*!<Contains the map of the city. */

    city_hall_t city_hall;                                                   /*!< Structure of the city hall. */
    company_t companies[MAX_COMPANIES];                                      /*!< Structures of the companies. */
    residential_building_t residential_buildings[MAX_RESIDENTIAL_BUILDING];  /*!< Structures of the residental buildings. */
    supermarket_t supermarkets[MAX_SUPERMARKETS];                            /*!< Structures of the supermakets. */
    mailbox_t mailbox;                                                       /*!< Structure of the mailbox. */
    
    citizen_t citizens[NUMBER_OF_CITIZENS];  /*!< Structures of the citizens. */
    spie_t spies[NUMBER_OF_SPIES];           /*!< Structures of the spies. */
    counter_officer_t counter_officer;       /*!< Structure of the counter intelligence officer. */
    case_officer_t case_officer;             /*!< Structure of the case officer. */
    int citizens_at_home;                    /*!< Number of citizens at home. */
    int citizens_at_work;                    /*!< Number of citizens at work. */
    int citizens_walking;                    /*!< Number of citizens walking in the city. */

    mesh_surveillance_network_t mesh_surveillance_network;  /*!< Structure of the meshed suiveillance network. */

    pid_t spy_simulation_pid;                /*!< Pid of the spy_simulation process. */
    pid_t citzen_manager_pid;                /*!< Pid of the citzen_manager process. */
    pid_t counter_intelligence_officer_pid;  /*!< Pid of the counter_intelligence_officer process. */
    pid_t spies_pid[NUMBER_OF_SPIES];        /*!< Pids of the spies process. */
    pid_t case_officer_pid;                  /*!< Pid of the case_officer process. */
    
    int count;  /*!< Current round of the simulation. */
};

#endif /* MEMORY_H */
