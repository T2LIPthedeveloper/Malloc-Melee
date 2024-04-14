#include <stdlib.h>
#include <stdio.h>

/* random string from string array */
const char* getRandomStringFromArray(char *arr[], int count)
{
    return arr[rand() % count];
}

/* 
    wait for the user to press return 
    before continuing

    verb: the verb to display in the prompt
*/
void promptToPressEnter(char *verb)
{
    printf("Press enter to %s...", verb);
    int c;
    while((c = getchar()) != '\n' && c != '\r');
}

/* Clear the console screen, ready for the next screen */
void clearScreen()
{
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__) || defined(__MACH__) || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__)
        system("clear");
    #elif defined(_WIN32) || defined(_WIN64)
        system("cls");
    #else
        // Add a bunch of newlines if system calls aren't available
        for(int i = 0; i < 200; i++)
            printf("\n");
    #endif
}