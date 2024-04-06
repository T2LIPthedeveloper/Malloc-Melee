#include <stdio.h>
#include "../../engine/player.h"
#include "../../engine/choice.h"
#include "../../engine/util.h"
#include "../../engine/items.h"
#include "dining_room.h"
#include "fireplace_room.h"
#include "seventh_corridor.h"

/* Corridor after the dining room... close to finishing the second floor */
void seventh_corridor(struct Player *player)
{
    static short playerHasShield = 0;
    
    printf("You're standing in a corridor, with armoured suits lined up along both walls.\n");
    printf("One of the suits has a moustache painted on its helmet.\n");
    printf("At the end of the corridor, you see a door.\n");
    
    Choice choices[3] = {
        { 0, "Go back to the dining room." },
        { 1, "Go towards the door at the end." },
        { 2, "There's something about that suit with the moustache that's SO alluring." }
    };
    
    short result = choose(choices, (playerHasShield) ? 2 : 3);
    
    if(result == 0)
        player->current_location = &dining_room;
    else if(result == 1)
        player->current_location = &fireplace_room;
    else
    {
        clearScreen();
        printf("You walk up to the suit with the moustache, and notice a shield leaning against it.\n");
        printf("It's a steel shield, with a dragon painted on it. It looks like it's seen some action.\n");
        
        struct ValuedItem dragon_shield = { "dragon shield", "block", (short)7 };
        player->defense = dragon_shield;
        
        playerHasShield = 1;
        promptToPressEnter("continue");
    }
}