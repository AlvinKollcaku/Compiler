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
#include <math.h>
#include "CompilerHeader.h"

void handleOperators(char Operators[],int Operands[],char * tokenPtr)
{
    SML[SmlInstructionCounter++]=20000+Operands[0]; //1)loading first operand in accumulator
    SML[SmlInstructionCounter++]=31000+Operands[1]; // first-second

    if(Operators[0]=='>')
    {
        //If the line number is not in symbol table we put it in the flags array in the corresponding index
        //as the unfinished SML instruction
        int line=returns_LineNum_location_from_SymbolTable(tokenPtr);
        if(line==-1)
        {
            flags[SmlInstructionCounter]=atoi(tokenPtr);
            if(Operators[1]=='=')
                SML[SmlInstructionCounter++]=44000; //Branch if accumulator is positive or 0
            else
                SML[SmlInstructionCounter++]=43000;
        }else
        {
            if(Operators[1]=='=')
                SML[SmlInstructionCounter++]=44000+line;//Branch if accumulator is positive or 0
            else
                SML[SmlInstructionCounter++]=43000+line;
        }
    }else if(Operators[0]=='<')
    {
        //We search for the line number in the symbol table
        int line=returns_LineNum_location_from_SymbolTable(tokenPtr);
        if(line==-1)
        {
            flags[SmlInstructionCounter]=atoi(tokenPtr);
            if(Operators[1]=='=')
                SML[SmlInstructionCounter++]=42000; //Branch if accumulator is negative or 0
            else
                SML[SmlInstructionCounter++]=41000;
        }else
        {
            if(Operators[1]=='=')
                SML[SmlInstructionCounter++]=42000+line;//Branch if accumulator is negative or 0
            else
                SML[SmlInstructionCounter++]=41000+line;
        }
    }else if(Operators[0]=='=' || Operators[0]=='!')
    {
        //The syntax analyser must have already checked that they are of valid form == != but we also check here
        if(Operators[1]!='=')
        {
            printf("Operator not of form == or !=");
            exit(1);
        }
        int line=returns_LineNum_location_from_SymbolTable(tokenPtr);
        if(line==-1)
        {
            flags[SmlInstructionCounter]=atoi(tokenPtr);
            if(Operators[0]=='=')
                SML[SmlInstructionCounter++]=45000; //Branch if accumulator is 0
            else
                SML[SmlInstructionCounter++]=46000;//Branch if accumulator is NOT 0
        }else
        {
            if(Operators[0]=='=')
                SML[SmlInstructionCounter++]=45000+line;//Branch if accumulator is negative or 0
            else
                SML[SmlInstructionCounter++]=46000+line;
        }
    }
}

int evaluatePostfixExpression2(char *expr[])
{
    PostfixPtr topPtr=NULL;
    char * pend;// Character end pointer  -> for strof

    for(int i=0; strcmp(expr[i],"$") != 0; i++)
    {
        if(isValidVariable(expr[i]))
        {
            //printf("%c is variable\n", *expr[i]);
            if(returns_SML_location_from_SymbolTable(expr[i])==-1)
            {
                strcpy(SymbolTable[SymbolTableIndex].variable, expr[i]);
                SymbolTable[SymbolTableIndex].type='V';
                SymbolTable[SymbolTableIndex++].location=SmlVariableIndexCounter--;
            }
            pushPostfix(&topPtr,returns_SML_location_from_SymbolTable(expr[i]));
        }else if(isOperator(*expr[i]))
        {
            //printf("%c is operator\n",*expr[i]);
            //if we have an operator pop last 2 digits in stack to do the calculation
            int v2=popPostfix(&topPtr); //second operator address
            int v1=popPostfix(&topPtr); //first operator address

           //printf("Now reorganizing the stack\n");
            reorganizeStack(v1,v2,*expr[i],&topPtr);
            //printf("Stack reorganized\n");
           // printPostfixStack(topPtr);
        }
        else //It is a constant -> put it into the symbol table if it's not there
            // and push the location in the stack
        {
            //printf("%lf is constant\n", strtof(expr[i], &pend));
            int resultLocation= returns_SML_location_from_SymbolTable(expr[i]);
            if(resultLocation==-1)
            {
                //printf("%s about to be put in symbol table %lf\n",expr[i],strtod(expr[i], &pend));
                SymbolTable[SymbolTableIndex].symbol=strtod(expr[i], &pend);
                SymbolTable[SymbolTableIndex].type='C';
                SymbolTable[SymbolTableIndex++].location=SmlVariableIndexCounter--;
                resultLocation=SmlVariableIndexCounter+1;
                //printf("%lf put in symbol table\n",SymbolTable[SymbolTableIndex-1].symbol);
                SML[SmlVariableIndexCounter+1]=strtod(expr[i], &pend);
            }
            pushPostfix(&topPtr,resultLocation);
        }
        //printf("Next -> Comparing %s with \"$\" %d \n",expr[i+1],strcmp(expr[i+1],"$"));
    }
    //printf("Value that is being returned %d\n",topPtr->address);
    return topPtr->address; //returning the address with the result
}

void pushPostfix(PostfixPtr *topPtr, int value)
{
    PostfixPtr newNode=(PostfixPtr)malloc(sizeof(Postfix));

    if(newNode!=NULL)
    {
        newNode->address=value;
        newNode->nextPtr=*topPtr;
        *topPtr=newNode;
    }
    else
        printf("%d not inserted. No memory available.\n",value);
}

int popPostfix(PostfixPtr *topPtr)
{
    PostfixPtr tmp=*topPtr;
    int popValue=(*topPtr)->address;
    *topPtr=(*topPtr)->nextPtr;
    free(tmp);

    return popValue;
}

void reorganizeStack(int a1,int a2,char operator,PostfixPtr* topPtr)
{
    /*
     1)Put the load and add/sub.. operations in SML
     2)Put the result of SML[a1] operator SML[a2] into the symbol table as new constant with
     a location in the SML array (resultLocation)
     3)STORE resultLocation
     */
    switch(operator)
    {
        case '+':
            SML[SmlInstructionCounter++]=20000+a1; //LOAD a1
            SML[SmlInstructionCounter++]=30000+a2;//ADD a2 ->Now the result is in the accumulator

            SML[SmlInstructionCounter++]=21000+SmlVariableIndexCounter; //Result will be stored in the next free spot
            pushPostfix(topPtr,SmlVariableIndexCounter);//Pushing the address with the result into the stack
            SmlVariableIndexCounter--;
            break;
        case '-':
            SML[SmlInstructionCounter++]=20000+a1; //LOAD a1
            SML[SmlInstructionCounter++]=31000+a2;//SUBTRACT a2
            SML[SmlInstructionCounter++]=21000+SmlVariableIndexCounter; //Result will be stored in the next free spot
            pushPostfix(topPtr,SmlVariableIndexCounter);//Pushing the address with the result into the stack
            SmlVariableIndexCounter--;
            break;
        case '*':
            SML[SmlInstructionCounter++]=20000+a1; //LOAD a1
            SML[SmlInstructionCounter++]=33000+a2;//MULTIPLY a2
            SML[SmlInstructionCounter++]=21000+SmlVariableIndexCounter; //Result will be stored in the next free spot
            pushPostfix(topPtr,SmlVariableIndexCounter);//Pushing the address with the result into the stack
            SmlVariableIndexCounter--;
            break;
        case '/':
            SML[SmlInstructionCounter++]=20000+a1; //LOAD a1
            SML[SmlInstructionCounter++]=32000+a2;//DIV a2
            SML[SmlInstructionCounter++]=21000+SmlVariableIndexCounter; //Result will be stored in the next free spot
            pushPostfix(topPtr,SmlVariableIndexCounter);//Pushing the address with the result into the stack
            SmlVariableIndexCounter--;
            break;
        case '%':
            SML[SmlInstructionCounter++]=20000+a1; //LOAD a1
            SML[SmlInstructionCounter++]=34000+a2;//REMAINDER a2

            SML[SmlInstructionCounter++]=21000+SmlVariableIndexCounter; //Result will be stored in the next free spot
            pushPostfix(topPtr,SmlVariableIndexCounter);//Pushing the address with the result into the stack
            SmlVariableIndexCounter--;
            break;
        case '^':
            SML[SmlInstructionCounter++]=20000+a1; //LOAD a1
            SML[SmlInstructionCounter++]=35000+a2;//EXPONENTIATION a2

            SML[SmlInstructionCounter++]=21000+SmlVariableIndexCounter; //Result will be stored in the next free spot
            pushPostfix(topPtr,SmlVariableIndexCounter);//Pushing the address with the result into the stack
            SmlVariableIndexCounter--;
            break;
        default:
            printf("Not valid operator");
            exit(1);
    }
}

void printPostfixStack(PostfixPtr topPtr)
{
    if(topPtr==NULL)
        printf("Stack is empty.\n");
    else
    {
        printf("Stack is: \n");
        while(topPtr!=NULL)
        {
            printf("%d ",topPtr->address);
            topPtr=topPtr->nextPtr;
        }
    }
    puts("");
}

int find_operator_position(const char *str) {
    const char *operators[] = {">=", "<=", "==", "!=", ">", "<"};
    for (int i = 0; i < 6; ++i) {
        char *pos = strstr(str, operators[i]); //to find the first occurrence of a substring within a larger string
        //find operators[i] in str or return null
        if (pos != NULL) {
            return pos - str;//Since elements in an array are stored in seq we subtract the operators address
            //with the beginning of the string to get the number of elements before the operator
        }
    }
    return -1;
}

