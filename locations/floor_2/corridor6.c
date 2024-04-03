#include <stdio.h>
#include "../../engine/player.h"
#include "../../engine/choice.h"
#include "../../engine/util.h"
#include "corridor5.h"
#include "banquet_hall.h"
#include "corridor6.h"

/* The 2nd part of the corrdior that leads to the banquet hall */
void corridor6(struct Player *player)
{
    static short potionAlreadyTaken = 0;
    
    printf("You are standing in a corridor.\n");
    printf("At the other end of the corridor, there is a door.\n");
    if(!potionAlreadyTaken)
        printf("To your right, there is a potion on a table.\n");
    printf("\n");
    
    
    Choice options[3] = {
        { 0, "Go back down the corridor, towards the staircase." },
        { 1, "Continue down the corridor, and go through the door." },
        { 2, "Drink the potion." } //Don't include if potion already taken
    };
    
    short result = makeChoice(options, (potionAlreadyTaken) ? 2 : 3);
    
    if(result == 0)
        player->current_location = &corridor5;
    else if(result == 1)
        player->current_location = &banquetHall;
    else
    {
        clearScreen();
        printf("You drink the potion, and feel your health being fully restored.\n");
        promptToPressEnter("continue");
        player->health = player->max_health;
        potionAlreadyTaken = 1;
    }
}