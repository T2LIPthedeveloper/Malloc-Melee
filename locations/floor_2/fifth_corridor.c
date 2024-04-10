#include <stdio.h>
#include "../../engine/player.h"
#include "../../engine/items.h"
#include "../../engine/choice.h"
#include "../../engine/util.h"
#include "../floor_1/fourth_corridor.h"
#include "sixth_corridor.h"
#include "fifth_corridor.h"
#include "../../engine/save_system.h"
#include "../../engine/ascii_handler.h"

/* Beginning of the 2nd floor */
void fifth_corridor(struct Player *player)
{
    static short playerHasSword = 0;
    
    display_ascii_art("./assets/turning_hallway.txt");
    printf("You're currently standing in a corridor.\n");
    printf("To your right, a soldier sleeps peacefully, his snores drowning the eerie whistle of air coming from the staircase.\n");
    printf("The corridor goes straight and turns sharply left.\n\n");
    
    Choice choices[4] = {
        { 0, "Go back downstairs through the spiral staircase." },
        { 1, "Move down the corridor." },
        { 2, "Steal the soldier's sword. He doesn't need to fight demons in his sleep." }, // Only if the player doesn't already have it
        { 3, "Been a while since you\'ve saved your game, huh?"}
    };
    
    short result = choose(choices, (playerHasSword) ? 3 : 4);
    
    if(result == 0)
        player->current_location = &fourth_corridor;
    else if(result == 1)
        player->current_location = &sixth_corridor;
    else if (result == 2 && !playerHasSword)
    {
        printf("You carefully take the broadsword from the soldier's grasp, being careful not to trigger his evidently sharp reflexes.\n");
        
        struct ValuedItem broadsword = { "broadsword", "slash", (short)15 };
        player->weapon = broadsword;
        playerHasSword = 1;
        
        promptToPressEnter("continue");
    }
    else if (result == 3)
    {
        int saveResult;
        saveResult = save_game(player, "fifth_corridor");
        if (saveResult == 0)
        {
            printf("Game saved successfully.\n");
        }
        else
        {
            printf("Failed to save game.\n");
        }
    }
}