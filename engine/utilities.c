#include <stdio.h>
#include <stdlib.h>

/* Get random string char from string array - useful for randomised choice picking during combat and stuff  */
const char * getRandStringFromArray(const char * array[], int size) {
    return array[rand() % size];
}

/* Prompt to press Enter, with parameter taken for action selected by the user */
void pressEnterToContinue(const char * action) {
    printf("\nPress Enter to %s!", action);
    int ch;
    while ((ch = getchar()) != '\n' && ch != '\r');

}

/* Screen clearing (independent of Linux and Windows) using system calls */
void clearScreen() {
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #elif defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #else
        /* Just add a crack ton of newlines 4 da memez */
        for (int i = 0; i < 100; i++) {
            printf("\n");
        }
    #endif
}