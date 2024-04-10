#include <stdio.h>
#include "../../engine/player.h"
#include "../../engine/choice.h"
#include "../../engine/util.h"
#include "../../engine/fight.h"
#include "../../engine/monster.h"
#include "../../engine/items.h"
#include "sixth_corridor.h"
#include "seventh_corridor.h"
#include "dining_room.h"
#include "../../engine/save_system.h"
#include "../../engine/ascii_handler.h"


/* Banquet hall */
void dining_room(struct Player *player)
{
    static short turkeyEaten = 0;
    static short doorUnlocked = 0;
    
    static struct Monster rabid_turkey = {
        .name = "rabid turkey",
        .health = 100,
        .attack = 13,
        .defense = 5,
        .attack_description_count = 1,
        .attack_descriptions = { 
            "The turkey tries to peck at you."
        },
        .defense_description_count = 1,
        .defense_descriptions = { "The turkey blocks with its big gullet." }
    };
    
    short turkeyLiving = (rabid_turkey.health > 0);
    
    display_ascii_art("./assets/mess.txt");
    printf("You're currently in a big dining room. A huge table lies ahead, fit for a banquet.\n");
    printf("A door lies at the other end of the dining room. Who knows where it may go?\n");
    if(turkeyLiving)
    {
        printf("What's that? The turkey being served is alive. And rabid. Bad choice of fowl.\n");
        printf("Oh, and it's twice your size, foaming at the... beak? \n");
    }
    else if(!turkeyEaten)
        printf("The turkey lies in pieces atop the table. That foam? It was just seasoning.\n");
    
    printf("\n");
    
    
    
    Choice choices[4] = {
        { 0, "Head back towards the spiral staircase." },
        { 1, (turkeyLiving) ? "Fight that rabid turkey. Don't let it get too close." : "Go through the door." },
        { 2, "Eat the rabid turkey's remains." },
        { 3, "Good time to save, isn't it?"}
    };
    
    short result = choose(choices, (!turkeyLiving && !turkeyEaten) ? 4 : 3);
    
    if(result == 0)
        player->current_location = &sixth_corridor;
    else if(result == 1)
    {
        if(turkeyLiving)
        {
            short fightResult = run_fighting(player, &rabid_turkey);
            if(fightResult == 0)
                player->current_location = NULL; 
            else
            {
                promptToPressEnter("continue");
            }
        }
        else
        {
            if(playerHasCollectable(player, KEY_RING))
            {
                if(!doorUnlocked)
                {
                    clearScreen();
                    printf("You unlock the door with one of the keys you found in the prison.\n");
                    promptToPressEnter("continue");
                    doorUnlocked = 1;
                }
                
                player->current_location = &seventh_corridor;
            }
            else
            {
                clearScreen();
                printf("You try to open the door, but it's locked.\n");
                promptToPressEnter("continue");
            }
        }
    }
    else if(result == 2)
    {
        clearScreen();
        display_ascii_art("./assets/mess.txt");
        printf("You make a fire out of some wood, and cook the turkey's body parts scattered here and there.\n");
        printf("It may have been a rabid turkey, but it did max out your health. Worth the meal.\n");
        promptToPressEnter("continue");
        turkeyEaten = 1;
        player->health = player->max_health;
    }
    else if (result == 3)
    {
        int save_result;
        save_result = save_game(player, "dining_room");
        if (save_result == 0)
        {
            printf("Game saved successfully.\n");
        }
        else
        {
            printf("Failed to save game.\n");
        }
    }
}