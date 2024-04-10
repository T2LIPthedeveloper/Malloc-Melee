#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./save_system.h"
#include "./player.h"
#include "./items.h"
#include "./location_mapping.h"

int save_game(struct Player *player, char * location)
{
    /* path to player save: ../../saves/{player_name}.txt */
    char *filepath = "./saves/";
    char *filetype = ".txt";
    char fullpath[256];
    strcpy(fullpath, filepath);
    strcat(fullpath, player->name);
    strcat(fullpath, filetype);


    FILE *file = fopen(fullpath, "w");
    if(file == NULL)
    {
        printf("Error opening file: %s\n", fullpath);
        return 1;
    }
    
    fprintf(file, "%s\n", player->name);
    fprintf(file, "%d\n", player->max_health);
    fprintf(file, "%d\n", player->health);
    fprintf(file, "%s\n", player->weapon.name);
    fprintf(file, "%s\n", player->weapon.verb);
    fprintf(file, "%d\n", player->weapon.value);
    fprintf(file, "%s\n", player->defense.name);
    fprintf(file, "%s\n", player->defense.verb);
    fprintf(file, "%d\n", player->defense.value);
    fprintf(file, "%d\n", player->collectable_count);
    for(int i = 0; i < player->collectable_count; i++)
    {
        fprintf(file, "%d\n", player->collectibles[i]);
    }
    fprintf(file, "%s\n", location); /* Current location of player */
    fclose(file);
    return 0;
}

Player *load_game(char *filename)
{
    char *filepath = "./saves/";
    char *filetype = ".txt";
    char fullpath[256];
    strcpy(fullpath, filepath);
    strcat(fullpath, filename);
    strcat(fullpath, filetype);

    FILE *file = fopen(fullpath, "r");
    if (file == NULL)
    {
        printf("Error opening save file.\n");
        printf("File path attempted: %s\n", fullpath);
        return NULL;
    }

    struct Player *player = malloc(sizeof(struct Player));
    struct ValuedItem *weapon = malloc(sizeof(struct ValuedItem));
    struct ValuedItem *defense = malloc(sizeof(struct ValuedItem));

    char line[256];
    fgets(line, sizeof(line), file);
    line[strlen(line) - 1] = '\0'; // Remove newline character
    player->name = strdup(line);

    fgets(line, sizeof(line), file);
    player->max_health = atoi(line);

    fgets(line, sizeof(line), file);
    player->health = atoi(line);

    fgets(line, sizeof(line), file);
    weapon->name = strdup(line);

    fgets(line, sizeof(line), file);
    weapon->verb = strdup(line);

    fgets(line, sizeof(line), file);
    weapon->value = atoi(line);

    fgets(line, sizeof(line), file);
    defense->name = strdup(line);

    fgets(line, sizeof(line), file);
    defense->verb = strdup(line);

    fgets(line, sizeof(line), file);
    defense->value = atoi(line);

    player->weapon = *weapon;
    player->defense = *defense;

    fgets(line, sizeof(line), file);
    player->collectable_count = atoi(line);
    for (int i = 0; i < player->collectable_count; i++)
    {
        fgets(line, sizeof(line), file);
        player->collectibles[i] = atoi(line);
    }

    if (fgets(line, sizeof(line), file) != NULL) {
        line[strlen(line) - 1] = '\0'; // Remove newline character
        player->current_location = get_location(line);
    } else {
        printf("Error reading current location.\n");
        fclose(file);
        free(player->name);
        free(player);
        free(weapon->name);
        free(weapon->verb);
        free(weapon);
        free(defense->name);
        free(defense->verb);
        free(defense);
        return NULL;
    }

    fclose(file); // Close the file

    // Free allocated memory for weapon and defense
    free(weapon->name);
    free(weapon->verb);
    free(weapon);
    free(defense->name);
    free(defense->verb);
    free(defense);

    return player;
}
