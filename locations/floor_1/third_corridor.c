#include <stdio.h>
#include "../../engine/player.h"
#include "../../engine/util.h"
#include "../../engine/choice.h"
#include "second_corridor.h"
#include "fourth_corridor.h"
#include "third_corridor.h"


/* Tough luck mate. Why did you have to take the easy way out? */
void departingExistence(struct Player *player)
{
    static short doorOpenedBefore = 0;
    
    printf("As you open the door, you see a sign on a wall that reads: \"FROM EXISTENCE\". You feel your ankle tug on a wire of some sort.\n");
    
    if(!doorOpenedBefore)
    {
        printf("A massive salvo of arrows points towards you, with a spring behind it connected to the wire.\n");
        printf("The arrows, triggered by the spring, fire at you. They all hit their mark.\n\n");
        
        player->health = player->health / 10;
        
        if(player->health == 0)
        {
            printf("You die from blood loss. Tough luck.\n");
            player->current_location = NULL;
            return;
        }
        else
        {
            printf("You pluck out all of the bloody arrows and snap the wire. That was close. Your health is now %d.\n", player->health);
            doorOpenedBefore = 1;
        }
    }
    else
        printf("A pile of bloody arrows lies on the floor, along with some loose wire.\n");
    
    printf("\n");
    promptToPressEnter("close the door");
    player->current_location = &third_corridor;
}

/* Another hallway after the guards' mess */
void third_corridor(struct Player *player)
{
    printf("You're standing in a corridor. Lots of them, I know.\n");
    printf("A door on your left has a wooden sign, marked \"DEPARTURE\".\n");
    printf("At the other end, the corridor turns left.\n\n");
    
    Choice choices[3] = {
        { 0, "Head back towards the guards' mess." },
        { 1, "Open the door marked \"DEPARTURE\". Might be your way out." },
        { 2, "Go down the corridor and turn left at the corner." },
    };
    
    short result = choose(choices, 3);
    
    if(result == 0)
        player->current_location = &second_corridor;
    else if(result == 1)
        player->current_location = &departingExistence;
    else
        player->current_location = &fourth_corridor;
}