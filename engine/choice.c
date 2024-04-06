#include <stdio.h>
#include "choice.h"

int choose(Choice choices[], int num_choices)
{
    static short choice_already_taken = 0;
    
    printf("You must choose.\n");
    
    if(!choice_already_taken)
    {
        printf("Type the number corresponding to your selection and press ENTER.\n");
        choice_already_taken = 1;
    }
    
    //Display choices
    for(int i = 0; i < num_choices; i++)
        printf("(%d) %s\n", i + 1, choices[i].optionStr);
    
    
    //Make selection (1, 2, 3, etc)
    //Print a prompt, then repeat till a valid selection is made
    int choice = 0;
    do
    {
        printf("> ");
        int scanResult = scanf("%d", &choice);
        
        // if player didn't enter a number, we need to flush out the buffer
        int c;
        while((c = getchar()) != '\n' && c != EOF);
        
    } while(choice < 1 || choice > num_choices);
    
    
    //Return selected function's index
    return choices[choice - 1].chosenSectionIndex;
}