#include <stdio.h>
#include <stdlib.h>
#include "../../engine/player.h"
#include "../../engine/util.h"
#include "../../engine/choice.h"
#include "../../engine/items.h"
#include "../../engine/monster.h"
#include "../../engine/fight.h"
#include "prison.h"
#include "guards_mess.h"
#include "first_corridor.h"
#include "../../engine/ascii_handler.h"


/* Win a prize, or lose and die */
void smoking_coin_flipper(struct Player *player)
{
    display_ascii_art("./assets/odd_man.txt");
    printf("You're in a small, dimly lit room. And you're not alone. For there sits an oddly cheerful man in a beanie, cheerily puffing on a cigarette.\n");
    printf("He looks up at you, and grins.\n\n");
    
    if(!playerHasCollectable(player, BURNT_CIGAR))
    {
        printf("\"Well lookie here... bet you're tired after all of that escapin'... care for a smoke?\"\n");
        printf("You politely refuse, though you're not sure why. You're not sure if your value system applies here.\n");
        printf("\"You see, I'm a blackjack player. Hell of a stressful game. But it's got the same chance as a coin flip, and I've got myself... a coin.\"\n");
        printf("If it lands on heads, congratulations! A great prize is yours. If not... you'll suffer a fate worse than anything you've encountered before.\n\n");
        
        printf("Care to play?\"\n\n");
        
        Choice choices[2] = {
            { 0, "I'm already stuck in this hole, why not try and make the most of it?" },
            { 1, "Not taking any chances. I just want to get out of here and leave." }
        };
        
        short result = choose(choices, 2);
        
        clearScreen();
        
        if(result == 0)
        {
            int isHeads = rand() % 2;
            if(isHeads)
            {
                display_ascii_art("./assets/odd_man.txt");
                printf("The coin lands on heads.\n");
                printf("\"Cheers!\" the man says. \"Go ahead and take your prize, you lucky bastard.\"\n");
                printf("The man hands you something long, thick... and awfully ashy. It's a burnt cigar, freshly stubbed. You look at it, then back at him as he lights up another.\n");
                printf("\"You didn't want a fresh one, so why not be of use? Hurry along now, you'll need that more than you think...\"\n");
                addCollectibleToPlayer(player, BURNT_CIGAR);
            }
            else
            {
                display_ascii_art("./assets/death.txt");
                printf("The coin lands on tails, and the lights go out. A faint smell of bitter almond crosses your nose.\n");
                printf("Suddenly, you feel death (It feels a lot like a bad cough).\n");
                printf("Your body drops to the ground, your soul fading along with it.\n");
                player->current_location = NULL;
                return;
            }
        }
        else {
            display_ascii_art("./assets/odd_man.txt");
            printf("\"Welp. Can't force you to if you don't want to. Drop by anytime...\" The man replies.\n");
        }            
    }
    else
        printf("\"Why are you here again? Don't you have anything better to do?\" The man says with a scowl.\n");
    
    
    printf("\n");
    promptToPressEnter("leave the room");
    player->current_location = &firstCorridor;
}



/* The corridor itself, with a zombie to fight */
void firstCorridor(struct Player *player)
{
    static struct Monster zombie = {
        .name = "zombie",
        .health = 25,
        .attack = 3,
        .defense = 1,
        .attack_description_count = 2,
        .attack_descriptions = { 
            "The zombie stabs at you with its flimsy dagger.", 
            "The zombie slashes at you with its flimsy dagger." 
        },
        .defense_description_count = 1,
        .defense_descriptions = { "The zombie blocks with its hands." }
    };
    
    int zombieIsAlive = (zombie.health > 0);

    if (zombieIsAlive) {
        display_ascii_art("./assets/zombie.txt");
    }
    else {
        display_ascii_art("./assets/hallway.txt");
    }
    printf("You're in a long corridor, with a door to your right.\n");
    printf((zombieIsAlive) ? "In front of you looms the shadow of... a human? \nYou wish, as the stench of rotting flesh enters your nostrils. It's a zombie.\n" : "And look! There's a door to another room right down here.\n");
    printf("\n");
    
    Choice choices[3] = {
        { 0, "Return to the prison." },
        { 1, "Check out what's in the door to your right." },
        { 2, (zombieIsAlive) ? "Fight the zombie." : "Walk down the long corridor and pass through the door." },
    };
    
    short result = choose(choices, 3);
    
    if(result == 0)
        player->current_location = &prisonCorridor;
    else if(result == 1)
        player->current_location = &smoking_coin_flipper;
    else
    {
        if(zombieIsAlive)
        {
            printf("\n");
            int fightResult = run_fighting(player, &zombie);
            if(fightResult == 0)
                player->current_location = NULL; 
            else
            {
                printf("\nYou pick up the zombie's flimsy dagger.\n\n");
                struct ValuedItem flimsyDagger = { "flimsy dagger", "slash", (short)10 };
                player->weapon = flimsyDagger;
                promptToPressEnter("continue");
                printf("\n");
            }
        }
        else
           player->current_location = &guardsMess; 
    }
}