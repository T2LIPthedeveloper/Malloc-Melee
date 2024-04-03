#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "./engine/player.h"
#include "./engine/util.h"
#include "./locations/floor_1/prison.h"
#include "./engine/save_system.h"

int main()
{
    srand(time(NULL));

    Player player;

    /* display main menu */
    displayMainMenu();
    
    /* get user input */
    int choice = getUserInput(1, 3);
    if (choice == 1) {
        /* Ask for player name first */
        printf("Enter your name: ");
        char name[50];
        fgets(name, 50, stdin);
        name[strlen(name) - 1] = '\0'; // Remove newline character
        player = createPlayer(name);
        player.current_location = &prisonCell1;
    } else if (choice == 2) {
        /* get name of player */
        char save[50];
        printf("Enter your save: ");
        fgets(save, 50, stdin);
        save[strlen(save) - 1] = '\0'; // Remove newline character
        player = *load_game(save);
    } else {
        return 0;
    }
    while(player.current_location != NULL) 
    {
        clearScreen();
        (*player.current_location)(&player);
    }
    
    printf("\n");
    promptToPressEnter("end the game");
    
    return 0;
}