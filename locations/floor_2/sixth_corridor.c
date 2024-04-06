#include <stdio.h>
#include "../../engine/player.h"
#include "../../engine/choice.h"
#include "../../engine/util.h"
#include "fifth_corridor.h"
#include "dining_room.h"
#include "sixth_corridor.h"

/* Heading towards the dining room now */
void sixth_corridor(struct Player *player)
{
    static short playerHasPotion = 0;
    
    printf("You're standing in a corridor.\n");
    printf("A door lies at the opposite end of it.\n");
    if(!playerHasPotion)
        printf("To your right, there's a table with a vial of something sweet-smelling. Seems like a potion.\n");
    printf("\n");
    
    
    Choice choices[3] = {
        { 0, "Head back towards the spiral staircase in the previous corridor." },
        { 1, "Continue towards the door at the opposite end of the corridor." },
        { 2, "Drink the vial of potion." } //Show it only if the option's available
    };
    
    short result = choose(choices, (playerHasPotion) ? 2 : 3);
    
    if(result == 0)
        player->current_location = &fifth_corridor;
    else if(result == 1)
        player->current_location = &dining_room;
    else
    {
        clearScreen();
        printf("As you gulp down the potion, you feel your strength returning after a long journey. Your health is fully restored.\n");
        promptToPressEnter("continue");
        player->health = player->max_health;
        playerHasPotion = 1;
    }
}