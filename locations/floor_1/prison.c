#include <stdio.h>
#include "../../engine/player.h"
#include "../../engine/util.h"
#include "../../engine/choice.h"
#include "../../engine/items.h"
#include "corridor1.h"
#include "prison.h"
#include "../../engine/ascii_handler.h"
#include "../../engine/save_system.h"

/* The starting point of the game */
void prisonCell1(struct Player *player)
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
    
    Choice options[3] = {
        { 0, "Leave the cell." },
        { 1, "Stay here and feel sorry for yourself." },
        {2, "Wait... maybe you want to save your state. Do you?"}
    };
    
    int result = makeChoice(options, 3);
    
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
void prisonCell2(struct Player *player)
{
    display_ascii_art("./assets/prison_cell.txt");
    printf("You can see a skeleton in the cell.\n");
    printf("The skeleton is leant up against the wall to the right.\n\n");
    promptToPressEnter("step back");
    player->current_location = &prisonCorridor;
}

/* Looking into the third prison cell -- The second of 2 lovers */
void prisonCell3(struct Player *player)
{
    display_ascii_art("./assets/prison_cell.txt");
    printf("You can see a skeleton in the cell.\n");
    printf("The skeleton is leant up against the wall to the left.\n\n");
    promptToPressEnter("step back");
    player->current_location = &prisonCorridor;
}

/* The forth prison cell. */
void prisonCell4(struct Player *player)
{
    display_ascii_art("./assets/prison_cell_alt.txt");
    printf("You are standing in an empty prison cell.\n");
    if(!playerHasCollectable(player, KEYRING))
    {
        printf("There is a big ring of keys on the ground. You pick them up.\n");
        addCollectibleToPlayer(player, KEYRING);
    }
    
    printf("\n");
    promptToPressEnter("go back outside");
    player->current_location = &prisonCorridor;
}


/* The corridor outside the prison cells */
void prisonCorridor(struct Player *player)
{
    printf("You are standing in a corridor.\n");
    printf("There are torches mounted on the walls.\n");
    printf("There are 3 other cells next to yours. The door of the 4th cell is open.\n");
    printf("There is also a door on your right, that leads out of this room.\n\n");
    
    Choice options[5] = {
        { 0, "Go back in your cell and feel sorry for yourself." },
        { 1, "Look into the 2nd cell." },
        { 2, "Look into the 3rd cell." },
        { 3, "Go into the 4th cell." },
        { 4, "Leave the room." }
    };
    
    short result = makeChoice(options, 5);
    
    if(result == 0)
        player->current_location = &prisonCell1;
    else if(result == 1)
        player->current_location = &prisonCell2;
    else if(result == 2)
        player->current_location = &prisonCell3;
    else if(result == 3)
        player->current_location = &prisonCell4;
    else
        player->current_location = &corridor1;
}