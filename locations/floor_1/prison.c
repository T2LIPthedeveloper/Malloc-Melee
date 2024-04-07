#include <stdio.h>
#include "../../engine/player.h"
#include "../../engine/util.h"
#include "../../engine/choice.h"
#include "../../engine/items.h"
#include "first_corridor.h"
#include "prison.h"
#include "../../engine/ascii_handler.h"
#include "../../engine/save_system.h"

/* The starting point of the game */
void firstCell(struct Player *player)
{
    static short fullDescRead = 0;
    char *simpleDesc = "The walls ooze with a clammy chill, and an unsettling scent lingers in the air, haunting every breath...";
    
    display_ascii_art("./assets/prison_cell_alt.txt");
    if(fullDescRead)
    {
        printf("%s\n\n", simpleDesc);
    }
    else
    {
        printf("Your eyes flutter open to a pitch-black dungeon, the air heavy with ancient whispers, \nand your mind devoid of memories like a forgotten specter in this sinister abyss.\n\n");
        printf("%s..\n\n", simpleDesc);
        printf("You realise... it's YOUR breath. You think to yourself, \"What the hell did I eat last night?\"\n\n");
        printf("The cell looms before you, its door ajar. You get a sudden rush of freedom, but dread what lies before you.\n\n");
        fullDescRead = 1;
    }
    
    Choice choices[3] = {
        { 0, "Leave the cell." },
        { 1, "Stay here and feel sorry for yourself." },
        {2, "Wait... maybe you want to save your state. Do you?"}
    };
    
    int result = choose(choices, 3);
    
    if(result == 2)
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
    else
    if(result == 0)
        player->current_location = &prisonCorridor;
}


/* Looking into the second prison cell -- The first of 2 lovers */
void secondCell(struct Player *player)
{
    display_ascii_art("./assets/prison_cell.txt");
    printf("In the musk and darkness of the cell, you can make out what appears to be the rotting bones of a prisoner... what used to be one, at least.\n");
    printf("The skeleton lies on its back, its skull tilting forward and slightly to the right, as if beckoning you to come closer.\n\n");
    promptToPressEnter("step back");
    player->current_location = &prisonCorridor;
}

/* Looking into the third prison cell -- The second of 2 lovers */
void thirdCell(struct Player *player)
{
    display_ascii_art("./assets/prison_cell.txt");
    printf("In the musk and darkness of the cell, you can make out what appears to be the rotting bones of a prisoner... what used to be one, at least.\n");
    printf("The skeleton is surprisingly erect, the eye sockets following your every gaze... are you sure it's just a skeleton?\n\n");
    promptToPressEnter("step back");
    player->current_location = &prisonCorridor;
}

/* The forth prison cell. */
void fourthCell(struct Player *player)
{
    display_ascii_art("./assets/prison_cell_alt.txt");
    printf("Zip. Nada. Nothing. Everywhere you look, you're met with the sordid emptiness and isolation of an average, poorly maintained prison cell.\n");
    if(!playerHasCollectable(player, KEY_RING))
    {
        printf("Huh, maybe it's not so empty after all. At least you got a key ring. Thanks, miserable cell!\n");
        addCollectibleToPlayer(player, KEY_RING);
    }
    
    printf("\n");
    promptToPressEnter("go back outside");
    player->current_location = &prisonCorridor;
}


/* The corridor outside the prison cells */
void prisonCorridor(struct Player *player)
{
    display_ascii_art("./assets/hallway.txt");
    printf("The corridor is dimly lit with the flickering light of a few torches, dangling precariously by their rusted iron mounts.\n");
    printf("And it looks like you're not alone in this den of imprisonment. There are three other miserable cells wasting away aside from yours.\n");
    printf("And would you look at that, the fourth's open. Huh.\n");
    printf("You look to your right and see a door. You ponder about where it may lead.\n\n");
    
    Choice choices[5] = {
        { 0, "Go back in your cell and feel sorry for yourself." },
        { 1, "Check out the 2nd cell." },
        { 2, "Check out the 3rd cell." },
        { 3, "Enter the 4th cell." },
        { 4, "Go through the door." }
    };
    
    short result = choose(choices, 5);
    
    if(result == 0)
        player->current_location = &firstCell;
    else if(result == 1)
        player->current_location = &secondCell;
    else if(result == 2)
        player->current_location = &thirdCell;
    else if(result == 3)
        player->current_location = &fourthCell;
    else
        player->current_location = &firstCorridor;
}