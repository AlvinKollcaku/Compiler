/*
 * <Compiler>
 * Copyright (C) <2024> <Alvin Kollçaku>
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
#include <ctype.h>
#include <math.h>
#include "InfixHeader.h"


//12 + 3 * ( 22- 123 *2) + 14

#define POP_FROM_STACK true
#define DONT_POP_FROM_STACK false

//#define DEBUG

//infix to postfix------------------------------------------------
//char infix[],char postfix[] -> previous arguments
char *str;

void convertToPostfix(char *infix,char *postfix2[]) {
    StackNodePtr topPtr = (StackNodePtr) malloc(sizeof(StackNode));
    topPtr->data = '('; // pushing a '(' in the base of the stack
    topPtr->nextPtr = NULL;
    int tokenIndex = 0;
    char popValue;

    for (int i = 0; !(isEmpty(topPtr)); i++) {
            // If the current character is a digit
        //printf("Current %c\n",infix[i]);
            if (isdigit(infix[i])) {
                char number[20]; //max number of digits is 19
                int numIndex = 0;
                // Collecting the full number
                while ((isdigit(infix[i])||infix[i]=='.')&&numIndex<19) {
                    number[numIndex++] = infix[i++];
                }
                if(isdigit(infix[i])) //If next token is still a digit than we have crossed legth 20
                {
                    printf("ERROR:A number at line %d is longer than 19 characters",lastValidLine);
                    exit(1);
                }
                i--;
                number[numIndex] = '\0';
                //printf("Number : %s \n",number);
                if(strtod(number,NULL)>99999 ||strtod(number,NULL)<-99999)
                {
                    printf("Overflow error at line %d. %s is out of the range [-99999,99999]\n",lastValidLine,number);
                    exit(1);
                }
                postfix2[tokenIndex] = (char *) malloc(sizeof(char) * (strlen(number) + 1));
                strcpy(postfix2[tokenIndex++], number);
                //printf("Number in postfix %s\n",postfix2[tokenIndex-1]);
            }else if(isalpha(infix[i]))//This is for the compiler part to put the variables in
            {
                char stringBuilt[26];
                int index=0;
                while(isalpha(infix[i]))
                {
                   // printf("Is alpha : %c\n",infix[i]);
                    if(index>24)
                    {
                        printf("Infix expression has string larger than 25 chars\n");
                        exit(1);
                    }
                    stringBuilt[index++]=infix[i++];
                }
                i--; //It will be incremented at the next loop iteration

                stringBuilt[index]='\0';
                //printf("String putting in postfix[%d] is %s \n",tokenIndex,stringBuilt);
                postfix2[tokenIndex] = (char *) malloc(sizeof(char) * (strlen(stringBuilt) ));
                strcpy(postfix2[tokenIndex++],stringBuilt);
            }
                // If the current character is an operator
            else if (isOperator(infix[i])) {
                //printf("About to handle %c\n",infix[i]);
                if(infix[i]=='/' && infix[i+1]=='0')
                {
                    printf("Error: Possible attempt to divide by 0 at line number %d.\nPlease remove any redundant leading zeros\n",lastValidLine);
                    exit(1);
                }
                if(precedence(infix[i], topPtr->data))
                {
                    popValue=pop(&topPtr);//If topPtr->data has same or higher precedence we pop it

                    if(popValue!='(') //'(' are not present in postfix
                    {
                        postfix2[tokenIndex++]=charToString(popValue);
                    }
                }
                //printf("Pushing %c into the stack\n", infix[i]);
                push(&topPtr,infix[i]); //We pass in the address of topPtr to change where it's
                // pointing to
            }
            else if(infix[i]=='(')
            {
                push(&topPtr, '(');
            }
            else if(infix[i]==')')
            {
                while(topPtr->data!='(')
                {
                    popValue=pop(&topPtr);
                    postfix2[tokenIndex++]= charToString(popValue);
                }
                pop(&topPtr);// will call it one more time to remove '('

            }
            else if(infix[i]=='$') //we have reached the end of infix array
            {
                while(!isEmpty(topPtr)) //the remaining operators will be popped and put in postfix
                {
                    popValue=pop(&topPtr);
                    if(popValue!='(')
                    {
                        postfix2[tokenIndex++]= charToString(popValue);
                    }
                }
                break;
            }
       // printf("Next one is %c\n",infix[i]);
    }
}

bool isOperator(char  c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/' || c=='%' || c=='^');
}

bool precedence(char operator1, char operator2)
{
    //op1 is from infix array, op2 is in the stack
    //will determine if op2 should be popped from the stack
    //it will be popped only if it has same or higher precedence than op1
    //op1 will be put in the stack
    if(operator2=='(')
    {
        return false;
    }

    if(operator2=='^')//highest precedence
        return true;
    else if(operator1=='^')
        return false;

    if(operator1=='*'||operator1=='/'||operator1=='%')
    {
        if(operator2=='*'||operator2=='/'||operator2=='%') //same precedence
        {
            return true;//remove op2
        }
        else
        {
            return false;
        }
    }
    else
    {
        //printf("Returning true\n");
        return true;//op1 = + or - so op2 is same or higher precedence
    }
}

void push(StackNodePtr *topPtr, char value)
{
    StackNodePtr newNode=(StackNodePtr)malloc(sizeof(StackNode));

    if(newNode!=NULL)
    {
        newNode->data=value;
        newNode->nextPtr=*topPtr;
        *topPtr=newNode;
    }
    else
        printf("%c not inserted. No memory available.\n",value);
}

char pop(StackNodePtr *topPtr)
{
    char  popValue;
    StackNodePtr tmp=*topPtr;
    popValue=(*topPtr)->data;
    *topPtr=(*topPtr)->nextPtr;
    free(tmp);

    return popValue;
}

bool isEmpty(StackNodePtr topPtr)
{
    if(topPtr==NULL)
        return true;

    return false;
}

void printStack(StackNodePtr topPtr)
{
    if(topPtr==NULL)
        printf("Stack is empty.\n");
    else
    {
        printf("Stack is: \n");
        while(topPtr!=NULL)
        {
            printf("%c ",topPtr->data);
            topPtr=topPtr->nextPtr;
        }
    }
    puts("");
}

double evaluatePostfixExpression(char *expr[])
{
    StackNode2Ptr topPtr2=NULL;
    // Character end pointer  -> for strof which is used to convert a string to float
    char* pend;

    for(int i=0; strcmp(expr[i], "$") != 0; i++)
    {
        if(isOperator(*expr[i]))
        {
            //if we have an operator pop last 2 digits in stack to do the calculation
            double v1=pop2(&topPtr2);
            double v2=pop2(&topPtr2);

            double result=calculate(v1,v2,*expr[i]);

            //pushing result into stack
            push2(&topPtr2,result);
        }
        else
        {
            push2(&topPtr2,strtof(expr[i], &pend));
        }
    }
    return topPtr2->data;
}

double calculate(double op1, double op2, char Operator)
{
    //op2 is extracted second, so it occurs first in postfix
    switch(Operator)
    {
        case '+':
            return op2+op1;
        case '-':
            return op2-op1;
        case '*':
            return op2*op1;
        case '/':
            return op2/op1;
        case '%':
            return (int)op1%(int)op2; //TODO -> syntax analyser will check that %  is applied only to ints
        case '^':
            return pow(op1,op2);
        default:
            return 0;
    }
}

void push2(StackNode2Ptr *topPtr, double value)
{
    StackNode2Ptr newNode=(StackNode2Ptr)malloc(sizeof(StackNode2));

    if(newNode!=NULL)
    {
        newNode->data=value;
        newNode->nextPtr=*topPtr;
        *topPtr=newNode;
    }
    else
        printf("%.1lf not inserted. No memory available.\n",value);
}

double pop2(StackNode2Ptr *topPtr)
{
    double popValue=0;
    StackNode2Ptr tmp=*topPtr;
    popValue=(*topPtr)->data;
    *topPtr=(*topPtr)->nextPtr;
    free(tmp);

    return popValue;
}

bool isEmpty2(StackNode2Ptr topPtr)
{
    if(topPtr==NULL)
        return true;

    return false;
}

void printStack2(StackNode2Ptr topPtr)
{
    if(topPtr==NULL)
        printf("Stack is empty.\n");
    else
    {
        printf("Stack is: \n");
        while(topPtr!=NULL)
        {
            printf("%.0lf",topPtr->data);
            topPtr=topPtr->nextPtr;
        }
    }
    puts("");
}

char* charToString(char c) {
    // Allocate memory for the string (2 characters: the char and the null terminator)
    str = (char*)malloc(2 * sizeof(char));
    if (str != NULL) {
        str[0] = c; // Assign the character
        str[1] = '\0'; // Null-terminate the string
    }
    return str;
}

