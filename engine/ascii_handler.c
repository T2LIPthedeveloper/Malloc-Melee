#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./ascii_handler.h"

int display_ascii_art(char *filename)
{
    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
    {
        return 1;
    }

    // read one character at a time and
    // display it to the output
    char ch;
    while ((ch = fgetc(fp)) != EOF)
        putchar(ch);

    // close the file
    fclose(fp);
    printf("\n");
    return 0;
}



