#ifndef MESH_SURVEILLANCE_NETWORK
#define MESH_SURVEILLANCE_NETWORK

/**
 * \file mesh_surveillance_network.h
 *
 * Defines structures and functions used by the meshed surveillance network.
 */

#include "common.h"

typedef struct mesh_surveillance_network_s mesh_surveillance_network_t;

/**
 * \brief The meshed surveillance network.
 */
struct mesh_surveillance_network_s {
    int near_company[NUMBER_OF_CHARACTERS]; /*!< For each character, the successives number of round near a company. */
    int id_suspicious_character;            /*!< The id of the character suspicious. */
};

#endif //MESH_SURVEILLANCE_NETWORK
