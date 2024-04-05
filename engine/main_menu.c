#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include "./player.h"
#include "./util.h"
#include "./ascii_handler.h"
/* define main menu */
void display_main_menu()
{
    int continue_game;
    clearScreen();
    continue_game = display_ascii_art("./assets/main_logo.txt");
    printf("A game by Atul Parida and Jignesh Motwani for 50.051 Programming Language Concepts.\n\n");
    if (continue_game == 1)
    {
        /* print current working directory */
        printf("Current working directory: %s", getcwd(NULL, 0));
        printf("Error: could not open file main_logo.txt");
        printf("\n");
    }
    /* main menu options:
    1. new game
    2. load game
    3. exit
    */
}