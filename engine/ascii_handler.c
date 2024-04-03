#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./ascii_handler.h"

void display_ascii_art(char *filename)
{
    FILE *file = fopen(filename, "r");
    if(file == NULL)
    {
        printf("Error opening file: %s\n", filename);
        return;
    }
    
    char line[256];
    while(fgets(line, sizeof(line), file))
    {
        printf("%s", line);
    }
    
    fclose(file);
}



