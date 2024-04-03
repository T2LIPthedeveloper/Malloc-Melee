#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./save_system.h"

// Function to save player details to a file
int savePlayerToFile(const Player *player, const char *filename) {
    char filepath[100]; // Adjust size as needed
    sprintf(filepath, "saves/%s", filename); // Append "saves/" to the filename

    FILE *file = fopen(filepath, "wb"); // Open the file for writing in binary mode
    
    if (file == NULL) {
        perror("Error opening file");
        return 0; // Return 0 to indicate failure
    }
    
    // Write player details to the file
    fwrite(player, sizeof(Player), 1, file);

    // Close the file
    fclose(file);

    return 1; // Return 1 to indicate success
}

// Function to load player details from a file
int loadPlayerFromFile(Player *player, const char *filename) {
    char filepath[100]; // Adjust size as needed
    sprintf(filepath, "saves/%s", filename); // Append "saves/" to the filename

    FILE *file = fopen(filepath, "rb"); // Open the file for reading in binary mode
    
    if (file == NULL) {
        perror("Error opening file");
        return 0; // Return 0 to indicate failure
    }
    
    // Read player details from the file
    fread(player, sizeof(Player), 1, file);

    // Close the file
    fclose(file);

    return 1; // Return 1 to indicate success
}
