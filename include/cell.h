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
#ifndef CELL_H
#define CELL_H

#include "common.h"
/**
 * \file cell.h
 *
 * Defines a cell within the grid map of the city. The cell may contains:
 * - Nothing (\e WASTELAND);
 * - A residential building (\e RESIDENTIAL_BUILDING);
 * - The City Hall (\e CITY_HALL);
 * - A company (\e COMPANY);
 * - SUPERMARKET (\e SUPERMARKET).
 */


/**
 * The type of cells within the city map.
 */
enum cell_type_e {
    WASTELAND,            /*!< An empty cell. */
    RESIDENTIAL_BUILDING, /*!< A cell that contains a residential building. */
    CITY_HALL,            /*!< A cell that contains the City Hall. */
    COMPANY,              /*!< A cell that contains a company. */
    SUPERMARKET           /*!< A cell that contains a supermarket. */
};

enum company_type_e {
    CRUTIAL,
    STRONG,
    MEDIUM,
    LOW,
    VERY_LOW
};

typedef enum cell_type_e cell_type_t;
typedef enum company_type_e company_type_t;
typedef struct cell_s cell_t;
typedef struct mailbox_s mailbox_t;
typedef struct company_s company_t;
typedef struct supermarket_s supermarket_t;
typedef struct city_hall_s city_hall_t;
typedef struct residential_building_s residential_building_t;

/**
 * \brief A cell within the map of the city.
 */
struct cell_s {
    int column;           /*!< Column of the cell. */
    int row;              /*!< Row of the cell. */
    cell_type_t type;     /*!< Type of the cell (@see \enum e_cell_type). */
    int nb_of_characters; /*!< Max. number of characters on the cell. */
};

struct residential_building_s {
    int column;
    int row;
    int affected_characters;
};

struct company_s {
    int row;
    int column;
    int affected_characters;
    int number_informations;
    char **informations;
    company_type_t type;
};

struct city_hall_s {
    int column;
    int row;
    int affected_characters;
};

struct supermarket_s {
    int column;
    int row;
    int affected_characters;
};

struct mailbox_s {
    int row;
    int column;
    /**
     * liste de messages
    */
};

#endif /* CELL_H */
