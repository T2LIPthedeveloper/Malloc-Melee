#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./player.h"
#include "./items.h"

/* Add item to inventory */
void addItemToInventory(Player * player, UsefulItem * item) {
    /* malloc inventory */
    UsefulItem * temp = malloc ((player->item_count + 1) * sizeof(UsefulItem));
    if (temp == NULL) {
        printf("Memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
    /* copy inventory to temp */
    for (int i = 0; i < player->item_count; i++) {
        temp[i] = player->inventory[i];
    }
    /* free inventory */
    free(player->inventory);
    /* add item to inventory */
    temp[player->item_count] = *item;
    player->inventory = temp;
    player->item_count++;
}
/* Remove item from inventory */
void removeItemFromInventory(Player * player, UsefulItem * item) {
    /* malloc inventory */
    UsefulItem * temp = malloc ((player->item_count - 1) * sizeof(UsefulItem));
    if (temp == NULL) {
        printf("Memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
    /* copy inventory to temp */
    int j = 0;
    for (int i = 0; i < player->item_count; i++) {
        if (&player->inventory[i] != item) {
            temp[j] = player->inventory[i];
            j++;
        }
    }
    /* free inventory */
    free(player->inventory);
    /* remove item from inventory */
    player->inventory = temp;
    player->item_count--;
    if (player->item_count == 0) {
        player->inventory = NULL;
    }
    
}
/* Does the player have the necessary item? */
int hasItem(Player * player, UsefulItem * item) {
    for (int i = 0; i < player->item_count; i++) {
        if (&player->inventory[i] == item) {
            return 1;
        }
    }
    return 0;
}
/* Create a player without the current location */
void createPlayer(Player * player, char * name) {
    player->name = name;
    player->max_health = 100;
    player->health = 100;
    player->attack = 10;
    player->defence = 5;
    player->inventory = NULL;
    player->item_count = 0;
    player->weapon = NULL;
    player->armour = NULL;
    player->curr_loc = NULL;
}