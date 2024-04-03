#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./save_system.h"
#include "./player.h"
#include "./items.h"

int save_game(struct Player *player)
{
    FILE *file = fopen("savegame.txt", "w");
    if(file == NULL)
    {
        printf("Error opening file: savegame.txt\n");
        return;
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
    
    fclose(file);
}

Player * load_game(char * filename)
{
    FILE *file = fopen(filename, "r");
    if(file == NULL)
    {
        printf("Error opening file: savegame.txt\n");
        return NULL;
    }

    /* Malloc for new player */
    struct Player * player = malloc(sizeof(struct Player));
    struct ValuedItem * weapon = malloc(sizeof(struct ValuedItem));
    struct ValuedItem * defense = malloc(sizeof(struct ValuedItem));
    
    char line[256];
    fgets(line, sizeof(line), file);
    line[strlen(line) - 1] = '\0'; // Remove newline character
    player->name = strdup(line);
    
    fgets(line, sizeof(line), file);
    player->max_health = atoi(line);
    
    fgets(line, sizeof(line), file);
    player->health = atoi(line);

    fgets(line, sizeof(line), file);
    *weapon->name = strdup(line);

    fgets(line, sizeof(line), file);
    *weapon->verb = strdup(line);

    fgets(line, sizeof(line), file);
    *weapon->value = atoi(line);

    fgets(line, sizeof(line), file);
    *defense->name = strdup(line);

    fgets(line, sizeof(line), file);
    *defense->verb = strdup(line);

    fgets(line, sizeof(line), file);
    *defense->value = atoi(line);

    player->weapon = *weapon;
    player->defense = *defense;
    
    for(int i = 0; i < player->collectable_count; i++)
    {
        fgets(line, sizeof(line), file);
        player->collectibles[i] = atoi(line);
    }
    
    fclose(file);

    return player;
}