#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./engine/player.h"
#include "./engine/main_menu.h"
#include "./engine/player_setup.h"
#include "./engine/save_system.h"
#include "./engine/utilities.h"

int main() {
    Player player; // Initialize the player structure

    // Display the main menu and handle user input
    handleMainMenuInput(&player);

    return 0;

}

// Function to handle main menu input
void handleMainMenuInput(Player *player) {
    int choice;

    do {
        displayMainMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Loading game...\n");
                if (loadPlayerFromFile(player, "savefile.dat")) {
                    printf("Game loaded successfully!\n");
                    // Start the game with the loaded player
                    // startGame(player);
                } else {
                    printf("Failed to load the game.\n");
                }
                break;
            case 2:
                printf("Setting up a new game...\n");
                // Set up the player
                setupPlayer(player);
                printf("Player setup complete!\n");
                // Wait for user input before proceeding
                pressEnterToContinue("start the game");
                clearScreen();
                // Initialize the game with the new player
                // startGame(player);
                break;
            case 3:
                printf("Exiting the game...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);
}