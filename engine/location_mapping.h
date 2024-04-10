#ifndef LOCATION_MAPPING_HG
#define LOCATION_MAPPING_HG

#include "player.h"

#define MAX_LOCATIONS 30

/* include Location func pointer definition from player.h */
/* include player current location from player.h */

/* struct to hold key-value mappings with string to func pointer */
struct LocationEntry {
    char *location;
    Location func;
};

/* function declarations */
void init_location_mapping();
Location get_location(char *location_name);

#endif

