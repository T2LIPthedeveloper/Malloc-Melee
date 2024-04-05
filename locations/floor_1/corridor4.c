#include <stdio.h>
#include "../../engine/player.h"
#include "../../engine/choice.h"
#include "../../engine/fight.h"
#include "../../engine/monster.h"
#include "../../engine/util.h"
#include "corridor3.h"
#include "../floor_2/corridor5.h"
#include "corridor4.h"

/* The third part of the corridor after the mess hall */
void corridor4(struct Player *player)
{
    static struct Monster shearMan = {
        .name = "shear-man",
        .health = 80,
        .attack = 10,
        .defense = 5,
        .attack_description_count = 2,
        .attack_descriptions = { 
            "Shear-man snaps his shears at you.", 
            "Shear-man slashes at you with his open shears." 
        },
        .defense_description_count = 1,
        .defense_descriptions = { "Shear-man blocks with his shears." }
    };
    
    short shearManIsAlive = (shearMan.health > 0);
    
    printf("You are standing in a corridor.\n");
    if(shearManIsAlive)
    {
        printf("In front of you there is a strange man, with small antlers and a white tail.\n");
        printf("Instead of hands, the man has large shears at the ends of his arms.\n");
    }
    printf("At the other end of the corridor, there is a spiral staircase, leading up to the next floor.\n\n");
    
    
    Choice options[2] = {
        { 0, "Head back towards the hall." },
        { 1, (shearManIsAlive) ? "Fight the man." : "Go up the staircase." }
    };
    
    short result = makeChoice(options, 2);
    
    if(result == 0)
        player->current_location = &corridor3;
    if(result == 1)
    {
        if(shearManIsAlive)
        {
            printf("\n");
            short fightResult = runCombat(player, &shearMan);
            if(fightResult == 0)
                player->current_location = NULL; 
            else
            {
                promptToPressEnter("continue");
                printf("\n");
            }
        }
        else
            player->current_location = &corridor5;
    }
}