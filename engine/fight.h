#ifndef FIGHT_H
#define FIGHT_H
#include "monster.h"
#include "player.h"

/* Player fights monster, 1 if player wins and 0 if player loses */
int run_fighting(struct Player *player, struct Monster *monster);

#endif