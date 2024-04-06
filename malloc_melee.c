#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "./engine/player.h"
#include "./engine/util.h"
#include "./locations/floor_1/prison.h"
#include "./engine/save_system.h"
#include "./engine/main_menu.h"
#include "./engine/choice.h"

int main()
{
    srand(time(NULL));

    Player player;

    /* display main menu */
    display_main_menu();
    
    /* get user input */
    Choice options[3] = {
        { 1, "New Game" },
        { 2, "Load Game" },
        { 3, "Exit" }
    };

    short choice = choose(options, 3);

    if (choice == 1) {
        /* Ask for player name first */
        printf("Enter your name: ");
        char name[50];
        fgets(name, 50, stdin);
        name[strlen(name) - 1] = '\0'; // Remove newline character
        player = createPlayer(name);
        player.current_location = &firstCell;
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