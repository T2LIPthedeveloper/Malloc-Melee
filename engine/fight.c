#include "player.h"
#include "monster.h"
#include "choice.h"
#include "util.h"
#include <stdlib.h>
#include <stdio.h>
#include "ascii_handler.h"

#define REC_ACT_COUNT 6

/* Allows us to enable the monster to remember the player's movements */
static short lastActions[REC_ACT_COUNT]; //-1 = not set

short tooManyActionRepeats(int currentAction)
{
    short broDoBeRepeating = 1;
    int lastAction = -1; // -1 = not set
    
    for(short i = 0; i < REC_ACT_COUNT; i++)
    {
        if(i > 0)
            lastActions[i-1] = lastActions[i];
        
        if(i == REC_ACT_COUNT - 1)
            lastActions[i] = currentAction;
        
        if(i > 0 && lastActions[i] != lastAction)
            broDoBeRepeating = 0;
        
        lastAction = lastActions[i];
    }
    
    return broDoBeRepeating;
}


void resetActionRecord()
{
    for(int i = 0; i < REC_ACT_COUNT; i++)
        lastActions[i] = -1;
}


/* Prints a description of a player's attack */
void printPlayerAttackDesc(struct Player *p) {
    printf("You %s the enemy with your %s.\n", p->weapon.verb, p->weapon.name);
}

/* Prints a description of a player's defense */
void printPlayerDefenseDesc(struct Player *p) {
    printf("You %s with your %s.\n", p->defense.verb, p->defense.name);
}

/* Prints a random attack description for a monster */
void printMonsterAttackDesc(struct Monster *m) {
    printf("%s\n", getRandomStringFromArray(m->attack_descriptions, m->attack_description_count));
}

/* Prints a random defense description for a monster */
void printMonsterDefenseDesc(struct Monster *m) {
    printf("%s\n", getRandomStringFromArray(m->defense_descriptions, m->defense_description_count));
}


void printHealthInfo(struct Player *player, struct Monster *monster)
{
    printf("Your health: %d - Enemy health: %d\n", player->health, monster->health);
}

/* 
    Determines if a defense is successful
    defenseValue - the defense value to check against
*/
int defenseSuccessful(int defenseValue)
{
    /*
    if the defense is 10 plus, then it will always be successful
    */
    return (rand() % 9) < defenseValue;
}


/* 
    Determines and handles the result of the player's/monster's choices 
    playerAction - 0 = attack; 1 = defend; 2 = dodge
    enemyDefends - treated as a boolean
    broDoBeRepeating - has the player's action been found to have been repeated too many times?
*/
void runCombatRound(int playerAction, int enemyDefends, int broDoBeRepeating, struct Player *player, struct Monster *monster)
{
    int pAttackVal = player->weapon.value;
    int pDefVal = player->defense.value;
    if(broDoBeRepeating)
    {
        pAttackVal /= 2;
        pDefVal /= 2;
    }
    
    if(playerAction == 0)
        printPlayerAttackDesc(player);
    else if(playerAction == 1)
        printPlayerDefenseDesc(player);
    
    if(enemyDefends)
        printMonsterDefenseDesc(monster);
    else
        printMonsterAttackDesc(monster);
    
    
    
    if(playerAction == 0) // Player attacks
    {
        if(enemyDefends)
        {
            int eDefSuccess = defenseSuccessful(monster->defense);
            printf((eDefSuccess) ? "Enemy defense was successful.\n" : "Enemy defense failed.\n");
            
            if(!eDefSuccess)
                monster->health -= pAttackVal;
        }
        else
        {
            printf("You both succeed with your attacks.\n");
            player->health -= monster->attack;
            monster->health -= pAttackVal;
        }
    }
    else if(playerAction == 1) // Player defends
    {
        if(enemyDefends)
            printf("You both succeed with your defense.\n");
        else
        {
            int pDefSuccess = defenseSuccessful(pDefVal);
            printf((pDefSuccess) ? "Your defense was successful.\n" : "Your defense failed.\n");
            
            if(!pDefSuccess)
                player->health -= monster->attack;
        }
    }
    else // Player dodges
    {
        int dodgeSucceeds = enemyDefends || (rand() % 2);
        
        if(!enemyDefends && !dodgeSucceeds)
            player->health -= monster->attack;
        
        printf((dodgeSucceeds) ? "You successfully dodge.\n" : "You fail to dodge.\n");
    }
}



/*
1 = player win
0 = player lose i.e monster win
*/
int run_fighting(struct Player *player, struct Monster *monster)
{
    resetActionRecord();
    
    Choice playerChoices[3] = {
        { 0, "Attack" },
        { 1, "Defend" },
        { 2, "Dodge" }
    };
    
    do
    {
        clearScreen();
        
        printHealthInfo(player, monster);
        
        // Determine actions
        int choice = choose(playerChoices, 3);
        short broDoBeRepeating = tooManyActionRepeats(choice);
        
        short enemyDefends;
        if(broDoBeRepeating)
        {
            enemyDefends = 0;
        }
        else
            enemyDefends = (rand() % 3) > 0;
        
        
        // Run round
        runCombatRound(choice, enemyDefends, broDoBeRepeating, player, monster);
        printf("\n");
        promptToPressEnter("continue");
        
        
        // End the fight?
        if (monster->health <= 0 && player->health > 0)
        {
            clearScreen();
            printf("You have defeated the %s.\n", monster->name);
            return 1;
        }
    }
    while(player->health > 0);
    
    clearScreen();
    display_ascii_art("./assets/death.txt");
    printf("You have been defeated by the %s.\n", monster->name);
    return 0;
}