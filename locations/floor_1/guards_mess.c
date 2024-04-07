#include <stdio.h>
#include "../../engine/player.h"
#include "../../engine/util.h"
#include "../../engine/choice.h"
#include "../../engine/items.h"
#include "../../engine/monster.h"
#include "../../engine/fight.h"
#include "first_corridor.h"
#include "second_corridor.h"
#include "guards_mess.h"
#include "../../engine/save_system.h"
#include "../../engine/ascii_handler.h"


/* The armour in the antiques/trophy area of the mess hall */
void brokenChainmail(struct Player *player)
{
    display_ascii_art("./assets/knight.txt");
    printf("You look at the old, broken links of the chainmail.\n");
    
    static short playerHasShield = 0;
    
    if(!playerHasShield)
    {
        printf("The suit has no weapon, but it does have a shield.\n");
        printf("You take the flimsy shield.\n");
        
        struct ValuedItem flimsyShield = { "flimsy shield", "block", (short)5 };
        player->defense = flimsyShield;
        playerHasShield = 1;
    }
    
    printf("\n");
                
    promptToPressEnter("continue");
    player->current_location = &guardsMess;
}


/* Food left in the corner of the mess hall */
void staleCupNoodles(struct Player *player)
{
    int addedHealth = 70;
    int healthTotal = player->health + addedHealth;
    int updatedHealth = (healthTotal < player->max_health) ? healthTotal : player->max_health;
    display_ascii_art("./assets/cup_noodles.txt");
    printf("You sit down at the end of the table, and take a bit of the cold, hardening cup noodles.\n");
    printf("Though it tastes as bland as plaster, you do feel better.\n");
    if(player->health < updatedHealth)
        printf("Your health increases to %d.\n", updatedHealth);
    
    printf("\n");
    
    player->health = updatedHealth;
    
    promptToPressEnter("continue");
    player->current_location = &guardsMess;
}


/* A cafeteria for the prison guards */
void guardsMess(struct Player *player)
{
    static struct Monster boxer = {
        .name = "boxer",
        .health = 75,
        .attack = 7,
        .defense = 3,
        .attack_description_count = 2,
        .attack_descriptions = { 
            "Boxer swings his left arm at you, trying to cobble you.", 
            "Boxer charges at you fists-first." 
        },
        .defense_description_count = 1,
        .defense_descriptions = { "Boxer blocks with his sizeable forearms. You see a sly grin on his face." }
    };
    
    short boxerAlive = (boxer.health > 0);
    
    static short someoneAteTheFood = 0;
    
    display_ascii_art("./assets/mess.txt");
    printf("You're in a large, airy hall with a couple of tables. Looks like a cafeteria of some sort.\n");
    printf("To your left, a wall has shelves full of antiques and pictures of past guards. Oh, and some terribly worn-out chainmail.\n");
    printf("To your right, there is a door out of the hall.\n");
    if(!someoneAteTheFood)
        printf("In the corner, there is a cup with some stale noodles.\n");
    
    if(boxerAlive)
    {
        printf("\nIn front of you stands the largest boxer you've possibly seen.\n");
        printf("He's wearing obscure boxing shorts, its edges laced with spiky thorns. Can't imagine wearing those all day.\n");
        printf("He looks at you menacingly, waiting for you to make the first move with a smug look on his face.\n");
    }
    
    printf("\n");
    
    short optionCount = (boxerAlive) ? 2 : (5 - someoneAteTheFood);
    Choice choices[5] = {
        { 0, "Go back into the corridor that leads to the jail." },
        { 1, (boxerAlive) ? "Fight the menacing boxer." : "Leave through the door to your right." },
        { 2, "Amble across to the chainmail armour." },
        { 3, "Eat the stale cup noodles. They're not getting any fresher..." },
        { 4, "Just for a moment, you think to yourself... don't you have a state to save?"}
    };
    
    int result = choose(choices, optionCount);
    
    if(result == 0)
        player->current_location = &firstCorridor;
    else if(result == 1)
    {
        if(boxerAlive)
        {
            printf("\n");
            short fightResult = run_fighting(player, &boxer);
            if(fightResult == 0)
                player->current_location = NULL; 
            else
            {
                promptToPressEnter("continue");
                printf("\n");
            }
        }
        else
            player->current_location = &second_corridor;
    }
    else if(result == 2)
        player->current_location = &brokenChainmail;
    else if(result == 3)
        player->current_location = &staleCupNoodles;
    else
    {
        int save_result;
        save_result = save_game(player);
        if (save_result == 0)
        {
            printf("Game saved successfully.\n");
        }
        else
        {
            printf("Error saving game.\n");
        }
    }
}