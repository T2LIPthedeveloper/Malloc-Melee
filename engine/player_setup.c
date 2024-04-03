#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./player_setup.h"

// Function to initialize default parameters for the player
void setupPlayer(Player *player) {
    // Set default parameters for the player
    player->max_health = 100;
    player->health = 100;
    player->inventory = NULL; // Initialize inventory to NULL or empty
    player->weapon = NULL;    // Initialize weapon to NULL
    player->armour = NULL;    // Initialize armour to NULL
    player->curr_loc = NULL;  // Initialize current location to NULL

    // Set the player's name
    setName(player);
}

// Function to prompt the player to enter their name
void setName(Player *player) {
    printf("Enter your character's name: ");
    char name[100];
    scanf("%s", name);

    // Allocate memory for the player's name and copy the input name
    player->name = malloc(strlen(name) + 1);
    if (player->name == NULL) {
        printf("Memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
    strcpy(player->name, name);
}
