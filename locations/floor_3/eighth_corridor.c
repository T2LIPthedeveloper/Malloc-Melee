#include <stdio.h>
#include "../../engine/player.h"
#include "../../engine/choice.h"
#include "../floor_2/fireplace_room.h"
#include "final_corridor.h"
#include "eighth_corridor.h"

/* First corridor of the 3rd floor */
void eighth_corridor(struct Player *player)
{
    static short playerWasHere = 0;
    
    printf("You're standing in a corridor, with a staircase leading down to the floor below.\n");
    printf("The corridor turns left at the end yet again.\n");
    printf("On your left, a soldier is sat on the floor, looking bored.\n");
    
    if(!playerWasHere)
    {
        printf("As you approach the soldier, he looks up at you.\n");
        printf("\"Shucks,\" he says, \"I'm supposed to be guarding this corridor, but I'm so bored.\"\n");
        printf("\"I'm not even sure what I'm supposed to be guarding against.\"\n");
        playerWasHere = 1;
    }
    
    Choice choices[2] = {
        { 0, "Go back down the corridor, towards the staircase." },
        { 1, "Go down the corridor and turn left." }
    };
    
    short result = choose(choices, 2);
    
    if(result == 0)
        player->current_location = &fireplace_room;
    else
        player->current_location = &final_corridor;
}