# ifndef PLAYER_H
# define PLAYER_H
#include "./items.h"

typedef struct Player Player;

/* func pointer type for locations to be used in game for executing location-specific plays */
typedef void (*Location)(struct Player *);

/* Details typically found in a player */
struct Player {
    char * name;
    short max_health;
    short health;
    short attack;
    short defence;
    UsefulItem * inventory; /* Inventory of player, contains items that can be used in game */
    short item_count; /* Number of items in inventory */
    struct UsefulItem * weapon; /* Weapon value = amount of damage done by successful attack */
    struct UsefulItem * armour; /* Defense value = amount of damage reduced by successful attack + chance of successful defense */
    Location curr_loc; /* Location of player in game */
};

/* Add item to inventory */
void addItemToInventory(Player * player, UsefulItem * item);

/* Remove item from inventory */
void removeItemFromInventory(Player * player, UsefulItem * item);

/* Does the player have the necessary item? */
int hasItem(Player * player, UsefulItem * item);

/* Create a player without the current location */
void createPlayer(Player * player, char * name);

#endif