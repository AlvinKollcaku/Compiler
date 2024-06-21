#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<stdbool.h>
#include "CompilerHeader.h"

void inputKeyword(char *tokenPtr)
{
    //Now we have to put the variable in the symbol table if it is not already
    tokenPtr=strtok(NULL," "); //1)Going to the varaible/constant
    //printf("CurrentToken:%s\n",tokenPtr);

    //printf("CASE:INPUT --> Value returned from function %d \n",x);
    int line=returns_SML_location_from_SymbolTable(*tokenPtr);
    if(line==-1) //not in symbol table -> we put it there
    {
        //printf("Putting it in the symbol table\n");
        SymbolTable[SymbolTableIndex].symbol=*tokenPtr;
        SymbolTable[SymbolTableIndex].type='V';
        SymbolTable[SymbolTableIndex++].location=SmlVariableIndexCounter;

        //printf("Inputed: %c\n",SymbolTable[SymbolTableIndex-1]);

        SML[SmlInstructionCounter++]=1000+SmlVariableIndexCounter--;
        //1000 + the location for the referenced variable(which is the next token)
    }
    else
    {
        //We use its location in the symbol table
        SML[SmlInstructionCounter++]=1000+line;
    }
}

void conditionKeyword(char *tokenPtr)
{
    /*There are 6 forms the if statement can take x==y x<y x>y x<=y x>=y x!=y*/

    char Operands[2]={'$','$'};//$ will be used to check for no input in an index
    char Operators[2]={'$','$'};

    tokenPtr=strtok(NULL," "); //1)Going to the next token which could be a V or C
    //TODO check if it is only a var or C
    Operands[0]=*tokenPtr;
    //printf("CASE:IF (FIRST OPERAND) --> Value returned from function %d %c\n",l1,*tokenPtr);

    if(returns_SML_location_from_SymbolTable(*tokenPtr)==-1)
    {
        SymbolTable[SymbolTableIndex].symbol=*tokenPtr;

        if(isKeyword(tokenPtr))
            SymbolTable[SymbolTableIndex].type='V';
        else
            SymbolTable[SymbolTableIndex].type='C';

        SymbolTable[SymbolTableIndex++].location=SmlVariableIndexCounter--;
    }
    //Now we check the if cases by getting the next token
    tokenPtr=strtok(NULL," ");

    if(strlen(tokenPtr)==1)
    {
        if(isConditionalOperator(tokenPtr[0]))
            Operators[0] = tokenPtr[0];
        else
        {
            printf("Not a valid operator: %c\n",*tokenPtr);
            exit(0);
        }
    }else
    {
        if(isConditionalOperator(tokenPtr[0])&& isConditionalOperator(tokenPtr[1])) {
            Operators[0] = tokenPtr[0];
            Operators[1] = tokenPtr[1];
        }
        else
        {
            printf("Not a valid operator: %c\n",*tokenPtr);
            exit(0);
        }
    }
    //printf("The operators are ready: %c %c \n",Operators[0],Operators[1]);
    tokenPtr=strtok(NULL," ");

    if(isVariable(tokenPtr)||isConstant(tokenPtr))//TODO only checks if single letter V or single digit C
    {
        //We input the second operand in the symbol table if is not already there
        int l2=returns_SML_location_from_SymbolTable(*tokenPtr);
        Operands[1]=*tokenPtr;

        if(l2==-1)
        {
            SymbolTable[SymbolTableIndex].symbol=*tokenPtr;
            if(isKeyword(tokenPtr))
                SymbolTable[SymbolTableIndex].type='V';
            else
                SymbolTable[SymbolTableIndex].type='C';
            SymbolTable[SymbolTableIndex++].location=SmlVariableIndexCounter--;
        }

       handleOperators(Operators,Operands,tokenPtr);

    }
    else
    {
        printf("The second operand should be a single letter variable or a constant");
        //Have to implement with goto and loop
        exit(0);
    }
}

void letKeyword(char *tokenPtr)
{
    //1) Put all symbols that are not in the symbol table
    tokenPtr=strtok(NULL," "); //left variable //TODO check that it is a variable->lexical analyser

    if(returns_SML_location_from_SymbolTable(*tokenPtr)==-1)
    {
        SymbolTable[SymbolTableIndex].symbol=*tokenPtr;
        SymbolTable[SymbolTableIndex].type='V';
        SymbolTable[SymbolTableIndex++].location=SmlVariableIndexCounter--;
    }
    tokenPtr=strtok(NULL," "); // getting the equal sign //TODO check it

    char *rightExpression[100];
    //2)Will store the right side of the expression in a string array
    for(int i=0;i<100;i++)
    {
        rightExpression[i]="$";
    }

    int index=0;
    while(tokenPtr!=NULL)
    {
        tokenPtr=strtok(NULL," "); //Passing the equal sign to get to the expression
        rightExpression[index++]=tokenPtr;
        if(index>=100)
        {
            printf("Right expression in more than 100 tokens");
            exit(1);
        }
    }

    char * postfix[100];
}

void handleOperators(char Operators[],char Operands[],char * tokenPtr)
{
    SML[SmlInstructionCounter++]=2000+ //1)loading first operand in accumulator
                                 returns_SML_location_from_SymbolTable(Operands[0]);
    SML[SmlInstructionCounter++]=3100+ //2)Substracting second operand
                                 returns_SML_location_from_SymbolTable(Operands[1]);

    //Now we deal with the goto part -> TODO check in syntax analyser if valid form
    tokenPtr=strtok(NULL," ");//->skipping goto
    tokenPtr= strtok(NULL,"");//-> line where we need to go to

        if(Operators[0]=='>')
        {
            //If the line number is not in symbol table we put it in the flags array in the corresponding index
            //as the unfinished SML instruction
            int line=returns_LineNum_location_from_SymbolTable(tokenPtr);
            if(line==-1)
            {
                flags[SmlInstructionCounter]=atoi(tokenPtr);
                if(Operators[1]=='=')
                    SML[SmlInstructionCounter++]=4400; //Branch if accumulator is positive or 0
                else
                    SML[SmlInstructionCounter++]=4300;
            }else
            {
                if(Operators[1]=='=')
                    SML[SmlInstructionCounter++]=4400+line;//Branch if accumulator is positive or 0
                else
                    SML[SmlInstructionCounter++]=4300+line;

            }
        }else if(Operators[0]=='<')
        {
            //We search for the line number in the symbol table
            int line=returns_LineNum_location_from_SymbolTable(tokenPtr);
            if(line==-1)
            {
                flags[SmlInstructionCounter]=atoi(tokenPtr);
                if(Operators[1]=='=')
                    SML[SmlInstructionCounter++]=4200; //Branch if accumulator is negative or 0
                else
                    SML[SmlInstructionCounter++]=4100;
            }else
            {
                if(Operators[1]=='=')
                    SML[SmlInstructionCounter++]=4200+line;//Branch if accumulator is negative or 0
                else
                    SML[SmlInstructionCounter++]=4100+line;

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
                    SML[SmlInstructionCounter++]=4500; //Branch if accumulator is 0
                else
                    SML[SmlInstructionCounter++]=4600;//Branch if accumulator is NOT 0
            }else
            {
                if(Operators[0]=='=')
                    SML[SmlInstructionCounter++]=4500+line;//Branch if accumulator is negative or 0
                else
                    SML[SmlInstructionCounter++]=4600+line;
            }
        }
}

