# ifndef PLAYER_H
# define PLAYER_H

typedef struct Player Player;

/* func pointer type for locations to be used in game for executing location-specific plays */
typedef void (*Location)(struct Player *);

/* Details typically found in a player */
struct Player {
    char * name;
    short max_health;
    short health;
    UsefulItem * inventory; /* Inventory of player, contains items that can be used in game */
    struct UsefulItem * weapon; /* Damage done by successful attack, has weapon name and attack amount */
    struct UsefulItem * armour; /* Damage absorbed by successful attack, has armour name and defence amount, plus chance of successful defense (to be confirmed) */
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