#include "location_mapping.h"
#include "player.h"

/* Locations */
#include "../locations/floor_1/prison.h"
#include "../locations/floor_1/guards_mess.h"
#include "../locations/floor_1/fourth_corridor.h"
#include "../locations/floor_2/fifth_corridor.h"
#include "../locations/floor_2/dining_room.h"
#include "../locations/floor_3/final_corridor.h"

/* Generics */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static struct LocationEntry locationDict[] = {
    /* All saveable locations */
    {"first_cell", &firstCell},
    {"guards_mess", &guardsMess},
    {"fourth_corridor", &fourth_corridor},
    {"fifth_corridor", &fifth_corridor},
    {"dining_room", &dining_room},
    {"final_corridor", &final_corridor}

};

Location get_location(char *location_name) {
    for (int i = 0; i < MAX_LOCATIONS; i++) {
        if (strcmp(locationDict[i].location, location_name) == 0) {
            return locationDict[i].func;
        }
    }
    return NULL;
}