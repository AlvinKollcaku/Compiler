#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "CompilerHeader.h"

void inputKeyword(char *tokenPtr)
{
    //Now we have to put the variable in the symbol table if it is not already
    tokenPtr=strtok(NULL," "); //1)Going to the variable/constant
    //printf("CurrentToken:%s\n",tokenPtr);

    if(!isVariable(tokenPtr))
    {
        printf("The variable after input keyword should be a character instead of %s"
               "-> at line number %d",tokenPtr,lastValidLine);
        exit(1);
    }

    //printf("CASE:INPUT --> Value returned from function %d \n",x);
    int line=returns_SML_location_from_SymbolTable(tokenPtr);
    if(line==-1) //not in symbol table -> we put it there
    {
        //printf("Putting it in the symbol table\n");
        SymbolTable[SymbolTableIndex].symbol=*tokenPtr;
        SymbolTable[SymbolTableIndex].type='V';
        SymbolTable[SymbolTableIndex++].location=SmlVariableIndexCounter;

        //printf("Inputed: %c\n",SymbolTable[SymbolTableIndex-1]);

        SML[SmlInstructionCounter++]=10000+SmlVariableIndexCounter--;
        //1000 + the location for the referenced variable(which is the next token)
    }
    else
    {
        //We use its location in the symbol table
        SML[SmlInstructionCounter++]=10000+line;
    }
}

void conditionKeyword(char *tokenPtr)
{
    /*There are 6 forms the if statement can take x==y x<y x>y x<=y x>=y x!=y*/

    int Operands[2]={-1,-1};

    tokenPtr = strtok(NULL, "\0");
    //!Since strtok() replaces the first occurrence of the delimiter (int this case " ") with \0
    //!we use that to get the expression part with the goto which we will use to split again

    // printf("Token %s\n",tokenPtr);
    //Now that we have the string we need to find the position of the operator/s to split it
    // there into a left and right part
    char *expression,*left, Operators[3], *right;

    expression=(char *) malloc(200*sizeof(char));
    left=(char *) malloc(100*sizeof(char));
    right=(char *) malloc(100*sizeof(char));

    expression = strtok(tokenPtr,"goto");
    tokenPtr = strtok(NULL,"goto"); //will hold the line to goto

    // Find the position of the operator
    int pos = find_operator_position(expression);
    if (pos == -1) {
        printf("Operator not found!In Keywords.c/conditionKeyword() line 50\n");
        exit(1);
    }

    // Determine the length of the operator
    int op_length = (expression[pos] == '>' || expression[pos] == '<' || expression[pos] == '!' || expression[pos] == '=') && expression[pos + 1] == '=' ? 2 : 1;

    // Extract the left part, the operator, and the right part
    strncpy(left, expression, pos);
    left[pos] = '\0';
    strncpy(Operators, expression + pos, op_length);
    Operators[op_length] = '\0';
    strcpy(right, expression + pos + op_length);

    //printf("Left: %s\n", left);
    // printf("Operator: %s\n", Operators);
    // printf("Right: %s\n", right);

    char * postfix[100];
    for(int i=0;i<100;i++)
    {
        postfix[i]="$";
    }
    strcat(left,"$");
    strcat(right,"$");
    convertToPostfix(left,postfix);
    Operands[0]=evaluatePostfixExpression2(postfix);
    for(int i=0;i<100;i++)
    {
        postfix[i]="$";
    }
    strcat(right,"$");
    convertToPostfix(right,postfix);
    Operands[1]=evaluatePostfixExpression2(postfix);

    //printf("%d %c%c %d goto %s\n",Operands[0],Operators[0],Operators[1],Operands[1],tokenPtr);

    handleOperators(Operators,Operands,tokenPtr);
}

void letKeyword(char *tokenPtr)
{
    //1) Put all symbols that are not in the symbol table
    tokenPtr=strtok(NULL,"=");
    int left_variable_location=returns_SML_location_from_SymbolTable(tokenPtr);
    if(left_variable_location==-1)
    {
        SymbolTable[SymbolTableIndex].symbol=*tokenPtr;
        SymbolTable[SymbolTableIndex].type='V';
        SymbolTable[SymbolTableIndex++].location=SmlVariableIndexCounter--;
        left_variable_location=SmlVariableIndexCounter+1;
    }
    tokenPtr=strtok(NULL,"=");
    strcat(tokenPtr,"$");

    char * postfix[200];
    for(int i=0;i<200;i++)
    {
        postfix[i]="$";
    }
    convertToPostfix(tokenPtr,postfix);
    SML[SmlInstructionCounter++]=20000+evaluatePostfixExpression2(postfix);//loading the result in accumulator
    SML[SmlInstructionCounter++]=21000+left_variable_location;//Storing the result in our variable
}

void printKeyword(char *tokenPtr)
{
    tokenPtr=strtok(NULL," ");//going to the variable or constant to print
    char *string=(char *) malloc(300* sizeof(char));
    if(!isVariable(tokenPtr))
    {
        if(*tokenPtr=='\'')
        {
            while(*tokenPtr!='\'' && strlen(string)<300 && tokenPtr!=NULL)
            {
                printf("Current token: %s \n",tokenPtr);
                strcat(string, strcat(" ",tokenPtr));
            }
        }
    }
    printf("String %s: ",string);
    exit(1);
    int location=returns_SML_location_from_SymbolTable(tokenPtr);
    if(location==-1)
    {
        SymbolTable[SymbolTableIndex].symbol=*tokenPtr;

        if(isVariable(tokenPtr))
            SymbolTable[SymbolTableIndex].type='V';
        else
            SymbolTable[SymbolTableIndex].type='C';

        SymbolTable[SymbolTableIndex++].location=SmlVariableIndexCounter--;
        location=SmlVariableIndexCounter+1;
    }
    SML[SmlInstructionCounter++]=11000+location; //Write location
}

void gotoKeyword(char *tokenPtr)
{
    tokenPtr= strtok(NULL," ");
    int line=returns_LineNum_location_from_SymbolTable(tokenPtr);
    if(line==-1)
    {
        flags[SmlInstructionCounter] = atoi(tokenPtr);
        SML[SmlInstructionCounter++] = 40000;
    }else
        SML[SmlInstructionCounter]=40000 + line;
}

void inputS(char *tokenPtr)
{
    //Now we have to put the variable in the symbol table if it is not already
    tokenPtr=strtok(NULL," "); //1)Going to the variable/constant
    //printf("CurrentToken:%s\n",tokenPtr);

    if(!isVariable(tokenPtr))
    {
        printf("The variable after input keyword should be a character instead of %s"
               "-> at line number %d",tokenPtr,lastValidLine);
        exit(1);
    }

    //printf("CASE:INPUT --> Value returned from function %d \n",x);
    int line=returns_SML_location_from_SymbolTable(tokenPtr);
    if(line==-1) //not in symbol table -> we put it there
    {
        //printf("Putting it in the symbol table\n");
        SymbolTable[SymbolTableIndex].symbol=*tokenPtr;
        SymbolTable[SymbolTableIndex].type='V';
        SymbolTable[SymbolTableIndex++].location=SmlVariableIndexCounter;

        //printf("Inputed: %c\n",SymbolTable[SymbolTableIndex-1]);

        SML[SmlInstructionCounter++]=10000+SmlVariableIndexCounter--;
        //1000 + the location for the referenced variable(which is the next token)
    }
    else
    {
        //We use its location in the symbol table
        SML[SmlInstructionCounter++]=10000+line;
    }
}

void printS(char *tokenPtr)
{

}



