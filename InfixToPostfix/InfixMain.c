#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<stdbool.h>
#include "InfixHeader.h"

//#define DEBUG

int main12()
{
    //infix to postfix----------------------------------------
    char *expression=(char *)malloc(sizeof(char)*200);
    gets(expression); //First we read the expression that the user enters

    //strlen will return the actual length of the expression (not the 200 occupied spaces)
    char *infix=(char *)malloc(sizeof(char)*strlen(expression)+2);
    strcpy(infix,expression);

    free(expression);

    strcat(infix,"$"); //appending a $ in end of infix array
    
    char * postfix[100]; //will hold the tokens

    for(int i=0;i<100;i++)
    {
        postfix[i]="$";
    }

#ifdef DEBUG
    printf("infix array: %s\n\n",infix);
#endif // DEBUG

    convertToPostfix(infix,postfix);
#ifdef DEBUG
    printf("Postfix array:\n\n");
#endif // DEBUG
    
    //----------------------------------------------------------

    //Postfix evaluation
    puts("Postfix array:");
    for(int i=0;strcmp(postfix[i],"$")!=0;i++)
        printf("%s ",postfix[i]);

    puts("");
   printf("Result: %.2f",evaluatePostfixExpression(postfix));

   free(infix);

    return 0;
}
