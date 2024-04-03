#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "./player.h"
#include "./util.h"
#include "./ascii_handler.h"
/* define main menu */
void displayMainMenu()
{
    clearScreen();
    display_ascii_art("../assets/main_logo.txt");

    /* main menu options:
    1. new game
    2. load game
    3. exit
    */

    printf("1. New Game\n");
    printf("2. Load Game\n");
    printf("3. Exit\n");
}