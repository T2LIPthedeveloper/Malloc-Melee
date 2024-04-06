#include <stdio.h>
#include "../../engine/player.h"
#include "../../engine/choice.h"
#include "../../engine/util.h"
#include "../../engine/items.h"
#include "eighth_corridor.h"
#include "treasure_room.h"
#include "final_corridor.h"
#include "../../engine/save_system.h"

/* The text that appears when the player finishes the game */
void endGameText()
{
    printf("All of that fighting's got you feeling pretty tired.\n");
    printf("You manage to make it to the door, and push it open.\n");
    printf("You've managed to escape the grasp of that preposterous Chief.\n");
    printf("You get out, and escape the fortress as fast as you can.\n");
    printf("Hello again, freedom.\n");
    
    promptToPressEnter("finish the game");
}


/* The final corridor of the game */
void final_corridor(struct Player *player)
{
    static short triedToOpenDoorBefore = 0; // tried opening without the Malloc Mask
    
    printf("You're standing in a corridor, with a staircase leading down to the floor below.\n");
    printf("There is a door at the opposite end of the corridor.\n");
    printf("Halfway down the corridor, there is a large door on the left. Some big guy is sat next to it.\n");
    
    Choice options[4] = {
        { 0, "Go back down the corridor, towards the staircase." },
        { 1, "Go towards the door at the end of the corridor." },
        { 2, "Try and open the large door on the left." },
        { 3, "Save the game."}
    };
    
    short result = choose(options, 3);
    
    if(result == 0)
        player->current_location = &eighth_corridor;
    else if(result == 1)
        player->current_location = &treasureRoom;
    else if (result == 2)
    {
        clearScreen();
        
        if(playerHasCollectable(player, MALLOC_MASK)) //End game
        {
            clearScreen();
            endGameText();
            player->current_location = NULL;
        }
        else //Can't open the door
        {
            printf("You push against the door, but nothing happens.\n");
            if(!triedToOpenDoorBefore)
            {
                printf("The man sat next to the door looks up at you and speaks.\n");
                printf("\"You can try that all you like,\" he says, \"it isn't going to move.\"\n");
                printf("\"I don't know about you, but I'm not going to be able to open it. Need a hell lot more strength than that.\"\n");
                triedToOpenDoorBefore = 1;
            }
            
            promptToPressEnter("continue");
        }
    }
    else if (result == 3)
    {
        int saveResult;
        saveResult = saveGame(player);
        if(saveResult == 0)
            printf("Game saved successfully.\n");
        else
            printf("Error saving game.\n");
    }
}