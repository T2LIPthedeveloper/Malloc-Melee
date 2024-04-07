#include <stdio.h>
#include "../../engine/player.h"
#include "../../engine/choice.h"
#include "../../engine/util.h"
#include "../../engine/fight.h"
#include "../../engine/monster.h"
#include "../../engine/items.h"
#include "seventh_corridor.h"
#include "../floor_3/eighth_corridor.h"
#include "fireplace_room.h"
#include "../../engine/ascii_handler.h"

/* Finally, the last fight of the second floor. Time to make it as SOUL-CRUSHING AS POSSIBLE. */
void fireplace_room(struct Player *player)
{
    // Wanted to make an unbeatable mob. This is the best I could do. Yes, this is very Dark Souls-y.
    static struct Monster timid_dragon = {
        .name = "timid dragon",
        .health = 1000,
        .attack = 50,
        .defense = 10,
        .attack_description_count = 1,
        .attack_descriptions = { 
            "The timid dragon breathes fire at you (timidly)."
        },
        .defense_description_count = 1,
        .defense_descriptions = { "The timid dragon blocks with its wings out of fright." }
    };
    
    short timidDragonAlive = (timid_dragon.health > 0);
    if (!timidDragonAlive)
    {
        display_ascii_art("./assets/fireplace.txt");
    }
    else
    {
        display_ascii_art("./assets/dragon.txt");
    }
    
    printf("You're standing in a large room with a fireplace. Ah, the nice warmth.\n");
    printf("On the other side of the room lies a spiral staircase. Probably another floor to deal with.\n");
    
    if(timidDragonAlive)
    {
        printf("In front of you, a timid dragon stands, looking at you with fear in its eyes.\n");
        printf("It's a dragon, but it's not attacking you. It's just standing there, looking scared. \nBut it's ready to fight if it needs to.\n");
    }
    printf("\n");
    
    
    Choice choices[2] = {
        { 0, "Go back into the corridor." },
        { 1, (timidDragonAlive) ? "Fight the timid dragon." : "Go upstairs to the next floor." }
    };
    
    short result = choose(choices, 2);
    
    if(result == 0)
        player->current_location = &seventh_corridor;
    else
    {
        if(timidDragonAlive)
        {
            if(playerHasCollectable(player, BURNT_CIGAR))
            {
                clearScreen();
                
                //The monster is scared of the cigar as its father was a smoker (yes I know it's a bit silly, but it's a game after all)
                display_ascii_art("./assets/dragon.txt");
                printf("As you reach for your cigar, the dragon's eyes widen in fear.\n");
                printf("(This is a timid dragon, after all. It's scared of everything. But especially cigars as they remind it of other dragons.)\n");
                
                printf("The dragon flies up the chimney, blowing ash all over you. You're left standing there, cigar in hand.\n");
                promptToPressEnter("continue");
                timid_dragon.health = 0; // Completing the fight
            }
            else
            {
                //If you don't have the rune, you have to fight the dragon
                short fightResult = run_fighting(player, &timid_dragon);
                if(fightResult == 0)
                    player->current_location = NULL; 
                else
                {
                    printf("Huh. The dragon's not so tough after all. It's just a big scaredy-cat. A dead one now, though.\n");
                    promptToPressEnter("continue");
                }
            }
        }
        else
            player->current_location = &eighth_corridor;
    }
}