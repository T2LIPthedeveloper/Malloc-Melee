#ifndef SAVE_SYSTEM_H
#define SAVE_SYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./player.h"
#include "./items.h"

/* load and save functions for player state */
Player * load_game(char *filename);
int save_game(struct Player *player, char * location);

#endif