#ifndef UTILITIES_H
#define UTILITIES_H

/* Get random string char from string array - useful for randomised choice picking during combat and stuff  */
const char * getRandStringFromArray(const char * array[], int size);

/* Prompt to press Enter, with parameter taken for action selected by the user */
void pressEnterToContinue(const char * action);

/* Screen clearing (independent of Linux and Windows) */
void clearScreen();

#endif