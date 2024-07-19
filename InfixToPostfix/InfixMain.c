/*
 * <Compiler>
 * Copyright (C) <2024> <Alvin Kollçaku>
 *
 * Author: Alvin Kollçaku
 * Contact: kollcakualvin@gmail.com
 * Year: 2024
 * Original repository of the project: https://github.com/AlvinKollcaku/Compiler
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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
