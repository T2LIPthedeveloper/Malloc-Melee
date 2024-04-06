#include <stdio.h>
#include "../../engine/player.h"
#include "../../engine/choice.h"
#include "../../engine/util.h"
#include "../../engine/items.h"
#include "../../engine/monster.h"
#include "../../engine/fight.h"
#include "final_corridor.h"
#include "treasure_room.h"

/* The chest that contains the Olden Bling */
void treasureChest(struct Player *player)
{
    if(playerHasCollectable(player, MALLOC_MASK))
        printf("The chest is empty.\n");
    else
    {
        printf("You open the chest, and find that there is only one piece of treasure inside.\n");
        printf("It is a golden mask, with a large red gem in the centre.\n");
        printf("Then it hits you. This thing is the Malloc Mask!\n");
        printf("The sheer amount of memory it can allocate is staggering. Enough to make you feel invincible.\n\n Enough to (somehow) defeat the dreaded :(){ :|: & };:\n");
        addCollectibleToPlayer(player, MALLOC_MASK); //Don't ask me how infinite memory can defeat a fork bomb
    }
    
    promptToPressEnter("step back");
    player->current_location = &treasureRoom;
}


/* The treasure room */
void treasureRoom(struct Player *player)
{
    static struct Monster fortress_guard = {
        .name = "fortress guard",
        .health = 100,
        .attack = 13,
        .defense = 7,
        .attack_description_count = 1,
        .attack_descriptions = { 
            "The fortress guard swings his axe at you."
        },
        .defense_description_count = 1,
        .defense_descriptions = { "The fortress guard blocks with his shield." }
    };
    
    short guardAlive = (fortress_guard.health > 0);
    
    printf("You're standing in a room that is filled with treasure. Or at least, it would be if there was any.\n");
    printf("There are two large windows on the far wall, and a chest in the corner.\n");
    
    if(guardAlive)
    {
        printf("In the centre of the room, there stands a fortress guard.\n");
        printf("He is wearing a suit of armour, with a helmet that has a large red plume.\n");
        printf("He is holding a large axe, and looks like he's ready to fight.\n");
    }
    
    
    Choice options[2] = {
        { 0, "Go back out into the corridor." },
        { 1, (guardAlive) ? "Fight the fortress guard." : "Open the chest in the corner." }
    };
    
    short result = choose(options, 2);
    
    if(result == 0)
        player->current_location = &final_corridor;
    else
    {
        if(guardAlive)
        {
            clearScreen();
            short fightResult = runCombat(player, &fortress_guard);
            if(fightResult == 0)
                player->current_location = NULL; 
            else
            {
                printf("\n");
                promptToPressEnter("continue");
            }
        }
        else
        {
            player->current_location = &treasureChest;
        }
    }
}