#ifndef SAVE_SYSTEM_H
#define SAVE_SYSTEM_H

#include "./player.h"

// Function prototypes
int savePlayerToFile(const Player *player, const char *filename);

int loadPlayerFromFile(Player *player, const char *filename);

#endif
