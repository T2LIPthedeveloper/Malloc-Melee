#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./main_menu.h"
#include "./save_system.h"
#include "./player_setup.h"
#include "./utilities.h"

// Function to display the main menu options
void displayMainMenu() {
    displayAsciiArt("./assets/main_logo.txt");
    printf("=== Main Menu ===\n");
    printf("1. Load Game\n");
    printf("2. New Game\n");
    printf("3. Quit\n");
}

// Function to display ASCII art from a file
void displayAsciiArt(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening ASCII art file: %s\n", filename);
        return;
    }

    char ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    fclose(file);
}