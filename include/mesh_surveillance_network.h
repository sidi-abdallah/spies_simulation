#ifndef MESH_SURVEILLANCE_NETWORK
#define MESH_SURVEILLANCE_NETWORK

#include "common.h"

typedef struct mesh_surveillance_network_s mesh_surveillance_network_t;

struct mesh_surveillance_network_s {
    int near_company[NUMBER_OF_CHARACTERS];
    int id_suspicious_character;
};

#endif //MESH_SURVEILLANCE_NETWORK