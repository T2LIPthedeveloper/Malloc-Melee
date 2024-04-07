#include <stdio.h>
#include "../../engine/player.h"
#include "../../engine/util.h"
#include "../../engine/choice.h"
#include "guards_mess.h"
#include "third_corridor.h"
#include "second_corridor.h"
#include "../../engine/ascii_handler.h"


/* The humour starts here */
void enamel_throne(struct Player *player)
{
    static short doorIsOpen = 0;
    
    display_ascii_art("./assets/toilet.txt");
    printf("You enter the room and immediately regret it. There's a talking toilet. \nWith every word it speaks comes the smell of sewage.\n");
    
    if(!doorIsOpen)
    {
        printf("It looks up haughtily, as nothing can pierce its uncorroded enamel bones.\n");
        printf("\"So, you must be the new prisoner.\" he says. \"Looks like the guards are getting pretty lax.\"\n\n");
        printf("You ask it where you are, and why you are here.\n");
        printf("\"You've found yourself in Chief Chunker's dungeons, my friend.\" the toilet explains. You inquire about Chief Chunker.\n");
        printf("\"The Chief's name is notorious across all the realms. You're here because you slighted him. And nobody slights Chief Chunker.\"\n");
        printf("You don't remember slighting a mosquito, let alone some Chief. The toilet continues its distasteful sermon:\n\n");
        printf("\"Next time you drink, just be careful whose uniform you soil.\"\n");
        printf("Oh no. That's what you can't remember.\n");
        
        doorIsOpen = 1;
    }
    else
    {
        printf("\"What, you think just because I'm a toilet I'm supposed to be USED? These ableist humans, I swear...\"\n");
    }
    
    printf("\n");
    promptToPressEnter("close the door");
    player->current_location = &second_corridor;
}


/* The corridor after the mess hall */
void second_corridor(struct Player *player)
{
    display_ascii_art("./assets/turning_hallway.txt");
    printf("You're in yet another corridor.\n");
    printf("There's a door to your right.\n");
    printf(" The corridor turns left, with a pretty sharp corner. Ominous sounds come from the depth of the darkness.\n\n");
    
    Choice choices[3] = {
        { 0, "Go back into the hall." },
        { 1, "Open the door on your right." },
        { 2, "Go down the corridor, and take that left corner." },
    };
    
    short result = choose(choices, 3);
    
    if(result == 0)
        player->current_location = &guardsMess;
    else if(result == 1)
        player->current_location = &enamel_throne;
    else
        player->current_location = &third_corridor;
}