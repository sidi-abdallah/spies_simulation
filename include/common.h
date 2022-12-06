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
#ifndef COMMON_H
#define COMMON_H

/**
 * \file common.h
 *
 * Defines some constants and paths to interprocess mechanisms.
 */

/*
 * ---------------------------------------------------------------------------
 * Constants associated with the city map
  * ---------------------------------------------------------------------------
 */
#define MAX_COLUMNS                     7   /*!< Maximum number of columns for the city map. */
#define MAX_ROWS                        7   /*!< Maximum number of rows for the city map. */
#define MAX_COMPANIES                   8   /*!< Maximum number of companies for the city map*/
#define MAX_SUPERMARKETS                2   /*!< Maximum number of supermakets for the city map*/
#define MAX_RESIDENTIAL_BUILDING        11  /*!< Maximum number of habitation buildings for the city map*/

/*
 * ---------------------------------------------------------------------------
 * Constants associated with the cells
  * ---------------------------------------------------------------------------
 */
#define MAX_CHARACTERS_COMPANY                  0   /*!< Maximum number of characters in a company cell*/
#define MAX_CHARACTERS_CITY_HALL                0   /*!< Maximum number of characters in the city hall cell*/
#define MAX_CHARACTERS_RESIDENTIAL_BUILDING     0   /*!< Maximum number of characters in a residential building cell*/
#define MAX_CHARACTERS_SUPERMARKET              0   /*!< Maximum number of characters in a supermarket cell*/
#define MAX_CHARACTERS_WASTELAND                999 /*!< Maximum number of characters in a wasteland cell*/

/*
 * ---------------------------------------------------------------------------
 * Constants associated with the residential buildings
  * ---------------------------------------------------------------------------
 */
#define MAX_HABITATION_IN_RESIDENTIAL_BUILING   15  /*!< Maximum number of characters living in a residential building*/

/*
 * ---------------------------------------------------------------------------
 * Constants associated with the jobs
  * ---------------------------------------------------------------------------
 */
#define MAX_AFFECTED_CITY_HALL   15  /*!< Maximum number of characters living in a residential building*/
#define MAX_AFFECTED_SUPERMARKET   15  /*!< Maximum number of characters living in a residential building*/


/*
 * ---------------------------------------------------------------------------
 * Constants associated with the companies
  * ---------------------------------------------------------------------------
 */
#define MAX_COMPANY_TYPES                       5   /*!< Maximum number of types of a company*/

#define COMPANY_CRUCIAL_EMPLOYEES               30  /*!< Threshold number of employees for a crucial importance type company*/
#define COMPANY_STRONG_EMPLOYEES                30  /*!< Threshold number of employees for a strong importance type company*/
#define COMPANY_MEDIUM_EMPLOYEES                20  /*!< Threshold number of employees for a medium importance type company*/
#define COMPANY_LOW_EMPLOYEES                   10  /*!< Threshold number of employees for a low importance type company*/
#define COMPANY_VERY_LOW_EMPLOYEES              10  /*!< Threshold number of employees for a very low importance type company*/

#define COMPANY_CRUCIAL_GREATER_INFORMATIONS    2   /*!< Number of informations in a crucial importance type company if there are more than the threshold employees*/
#define COMPANY_CRUCIAL_SMALLER_INFORMATIONS    0   /*!< Number of informations in a crucial importance type company if there are less than the threshold employees*/
#define COMPANY_STRONG_GREATER_INFORMATIONS     5   /*!< Number of informations in a strong importance type company if there are more than the threshold employees*/
#define COMPANY_STRONG_SMALLER_INFORMATIONS     1   /*!< Number of informations in a strong importance type company if there are less than the threshold employees*/
#define COMPANY_MEDIUM_GREATER_INFORMATIONS     12  /*!< Number of informations in a medium importance type company if there are more than the threshold employees*/
#define COMPANY_MEDIUM_SMALLER_INFORMATIONS     7   /*!< Number of informations in a medium importance type company if there are less than the threshold employees*/
#define COMPANY_LOW_GREATER_INFORMATIONS        20  /*!< Number of informations in a low importance type company if there are more than the threshold employees*/
#define COMPANY_LOW_SMALLER_INFORMATIONS        11  /*!< Number of informations in a low importance type company if there are less than the threshold employees*/
#define COMPANY_VERY_LOW_GREATER_INFORMATIONS   30  /*!< Number of informations in a very low importance type company if there are more than the threshold employees*/
#define COMPANY_VERY_LOW_SMALLER_INFORMATIONS   17  /*!< Number of informations in a very low importance type company if there are less than the threshold employees*/

/*
 * ---------------------------------------------------------------------------
 * Constants associated with the characters
  * ---------------------------------------------------------------------------
 */
#define NUMBER_OF_CITIZENS 127 /*!< Number of normal citizens in the simulation*/
#define NUMBER_OF_SPIES    3   /*!< Number of spies in the simulation*/
#define MAX_LIFE_POINTS    10  /*!< Maximum number of life points for a character*/
#define MAX_JOBS_TYPES     3   /*!< Maximum number of types of jobs*/
/*
 * ---------------------------------------------------------------------------
 * Constants associated with the content of messages.
 * ---------------------------------------------------------------------------
 */

/** Maximum length of a message */
#define MAX_LENGTH_OF_MESSAGE 128

#define FAKE_MESSAGE  "FAKE"
#define EMPTY         "EMPTY"
#define STOLEN        "STOLEN"
#define NOT_FOUND     "NOT_FOUND"

#endif /* COMMON_H */
