#include <stdio.h>
#include "../../engine/player.h"
#include "../../engine/choice.h"
#include "../../engine/fight.h"
#include "../../engine/monster.h"
#include "../../engine/util.h"
#include "third_corridor.h"
#include "../floor_2/fifth_corridor.h"
#include "fourth_corridor.h"
#include "../../engine/ascii_handler.h"

/* Part 3 of the guards' mess corridor. Got kind of lazy with this one, I admit. */
void fourth_corridor(struct Player *player)
{
    static struct Monster minotaur = {
        .name = "minotaur",
        .health = 80,
        .attack = 10,
        .defense = 5,
        .attack_description_count = 2,
        .attack_descriptions = { 
            "The minotaur slashes his claws at your face.", 
            "The minotaur charges towards you, arms wide open." 
        },
        .defense_description_count = 1,
        .defense_descriptions = { "The minotaur's tough skin protects him from your attack." }
    };
    
    short minotaurAlive = (minotaur.health > 0);
    if (!minotaurAlive)
    {
        display_ascii_art("./assets/hallway.txt");
    }
    else
    {
        display_ascii_art("./assets/minotaur.txt");
    }

    printf("You are standing in a corridor. How many corridors have you gone through at this point?\n");
    if(minotaurAlive)
    {
        printf("In front of you there is a minotaur, with the body of a wrestler and head of an angry bull.\n");
    }
    printf("All that stands between you and the next floor is a spiral staircase.\n\n");
    
    
    Choice choices[2] = {
        { 0, "Screw this. We're heading back to the guards\' mess." },
        { 1, (minotaurAlive) ? "Fight the minotaur." : "Walk up the spiral staircase." }
    };
    
    short result = choose(choices, 2);
    
    if(result == 0)
        player->current_location = &third_corridor;
    if(result == 1)
    {
        if(minotaurAlive)
        {
            printf("\n");
            short fightResult = run_fighting(player, &minotaur);
            if(fightResult == 0)
                player->current_location = NULL; 
            else
            {
                promptToPressEnter("continue");
                printf("\n");
            }
        }
        else
            player->current_location = &fifth_corridor;
    }
}