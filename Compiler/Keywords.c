#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<stdbool.h>
#include <math.h>
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
    tokenPtr=strtok(NULL,"="); //variable part //TODO check that it is a variable->lexical analyser
    int left_variable_location=returns_SML_location_from_SymbolTable(*tokenPtr);
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
    evaluatePostfixExpression2(postfix);

    puts("Postfix:");
    for(int i=0; strcmp(postfix[i],"$")!=0;i++)
    {
        printf("%s ",postfix[i]);
    }
    puts("");
}

void handleOperators(char Operators[],char Operands[],char * tokenPtr)
{
    SML[SmlInstructionCounter++]=20000+ //1)loading first operand in accumulator
                                 returns_SML_location_from_SymbolTable(Operands[0]);
    SML[SmlInstructionCounter++]=31000+ //2)Substracting second operand
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

void evaluatePostfixExpression2(char *expr[])
{
    PostfixPtr topPtr=NULL;
    char * pend;// Character end pointer  -> for strof

    for(int i=0; strcmp(expr[i], "$") != 0; i++)
    {
        if(isVariable(expr[i]))
        {
            printf("%c is variable\n", *expr[i]);
            if(returns_SML_location_from_SymbolTable(*expr[i])==-1)
            {
                SymbolTable[SymbolTableIndex].symbol=(char)*expr[i];
                SymbolTable[SymbolTableIndex].type='V';
                SymbolTable[SymbolTableIndex++].location=SmlVariableIndexCounter--;
            }
            pushPostfix(&topPtr,returns_SML_location_from_SymbolTable(*expr[i]));
        }else if(isOperator(*expr[i]))
        {
            printf("%c is operator\n",*expr[i]);
            //if we have an operator pop last 2 digits in stack to do the calculation
            int v2=popPostfix(&topPtr); //second operator address
            int v1=popPostfix(&topPtr); //first operator address

            reorganizeStack(v1,v2,*expr[i], isVariableInSymbolTable(v1)&& isVariableInSymbolTable(v2));
        }
        else //It is a constant -> put it into the symbol table if its not there
        // and push the location in the stack
        {
            printf("%lf is constant\n", strtof(expr[i], &pend));
            int resultLocation= returns_Constant_location_from_SymbolTable(expr[i]);
            if(resultLocation==-1)
            {
                SymbolTable[SymbolTableIndex].symbol=strtof(expr[i], &pend);
                SymbolTable[SymbolTableIndex].type='C';
                SymbolTable[SymbolTableIndex++].location=SmlVariableIndexCounter--;
                resultLocation=SmlVariableIndexCounter+1;
                SML[SmlVariableIndexCounter+1]=strtof(expr[i], &pend);
            }
            pushPostfix(&topPtr,resultLocation);
        }
    }
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

void reorganizeStack(int a1,int a2,char operator,bool isVariableIncluded)
{
    /*
     1)Put the load and add/sub.. operations in SML
     2)Put the result of SML[a1] operator SML[a2] into the symbol table as new constant with
     a location in the SML array (resultLocation)
     3)STORE resultLocation
     */
    switch(operator)
    {
        double result=0;
        char str[50];
        int resultLocation;
        case '+':
            SML[SmlInstructionCounter++]=20000+a1; //LOAD a1
            SML[SmlInstructionCounter++]=30000+a2;//ADD a2 ->Now the result is in the accumulator

            if(isVariableIncluded)//the result will be stored in the next free spot
            {
                SML[SmlInstructionCounter++]=21000+SmlVariableIndexCounter;
                SmlVariableIndexCounter--;
            }else
            {
                result=SML[a1]+SML[a2];
                snprintf(str, sizeof(str), "%f", result);//turns float to string
                resultLocation= returns_Constant_location_from_SymbolTable(str);
                if(resultLocation==-1)
                {
                    SymbolTable[SymbolTableIndex].symbol=result;
                    SymbolTable[SymbolTableIndex].type='C';
                    SymbolTable[SymbolTableIndex++].location=SmlVariableIndexCounter--;
                    resultLocation=SmlVariableIndexCounter+1;
                }
                SML[SmlInstructionCounter++]=21000+resultLocation; //Store in the next free spot
            }
            break;
        case '-':
            SML[SmlInstructionCounter++]=20000+a1; //LOAD a1
            SML[SmlInstructionCounter++]=31000+a2;//SUBTRACT a2
            if(isVariableIncluded)//the result will be stored in the next free spot
            {
                SML[SmlInstructionCounter++]=21000+SmlVariableIndexCounter;
                SmlVariableIndexCounter--;
            }else
            {
                result=SML[a1]-SML[a2];
                snprintf(str, sizeof(str), "%f", result);//turns float to string
                resultLocation= returns_Constant_location_from_SymbolTable(str);
                if(resultLocation==-1)
                {
                    SymbolTable[SymbolTableIndex].symbol=result;
                    SymbolTable[SymbolTableIndex].type='C';
                    SymbolTable[SymbolTableIndex++].location=SmlVariableIndexCounter--;
                    resultLocation=SmlVariableIndexCounter+1;
                }
                SML[SmlInstructionCounter++]=21000+resultLocation; //Store in the next free spot
            }
            break;
        case '*':
            SML[SmlInstructionCounter++]=20000+a1; //LOAD a1
            SML[SmlInstructionCounter++]=33000+a2;//MULTIPLY a2
            if(isVariableIncluded)//the result will be stored in the next free spot
            {
                SML[SmlInstructionCounter++]=21000+SmlVariableIndexCounter;
                SmlVariableIndexCounter--;
            }else
            {
                result=SML[a1]*SML[a2];
                snprintf(str, sizeof(str), "%f", result);//turns float to string
                resultLocation= returns_Constant_location_from_SymbolTable(str);
                if(resultLocation==-1)
                {
                    SymbolTable[SymbolTableIndex].symbol=result;
                    SymbolTable[SymbolTableIndex].type='C';
                    SymbolTable[SymbolTableIndex++].location=SmlVariableIndexCounter--;
                    resultLocation=SmlVariableIndexCounter+1;
                }
                SML[SmlInstructionCounter++]=21000+resultLocation; //Store in the next free spot
            }
            break;
        case '/':
            SML[SmlInstructionCounter++]=20000+a1; //LOAD a1
            SML[SmlInstructionCounter++]=32000+a2;//DIV a2
            if(isVariableIncluded)//the result will be stored in the next free spot
            {
                SML[SmlInstructionCounter++]=21000+SmlVariableIndexCounter;
                SmlVariableIndexCounter--;
            }else
            {
                result=SML[a1]/SML[a2];
                snprintf(str, sizeof(str), "%f", result);//turns float to string
                resultLocation= returns_Constant_location_from_SymbolTable(str);
                if(resultLocation==-1)
                {
                    SymbolTable[SymbolTableIndex].symbol=result;
                    SymbolTable[SymbolTableIndex].type='C';
                    SymbolTable[SymbolTableIndex++].location=SmlVariableIndexCounter--;
                    resultLocation=SmlVariableIndexCounter+1;
                }
                SML[SmlInstructionCounter++]=21000+resultLocation; //Store in the next free spot
            }
            break;
        case '%':
            SML[SmlInstructionCounter++]=20000+a1; //LOAD a1
            SML[SmlInstructionCounter++]=34000+a2;//REMAINDER a2

            if(isVariableIncluded)//the result will be stored in the next free spot
            {
                SML[SmlInstructionCounter++]=21000+SmlVariableIndexCounter;
                SmlVariableIndexCounter--;
            }else
            {
                result=(int)SML[a1]%(int)SML[a2];
                snprintf(str, sizeof(str), "%f", result);//turns float to string
                resultLocation= returns_Constant_location_from_SymbolTable(str);
                if(resultLocation==-1)
                {
                    SymbolTable[SymbolTableIndex].symbol=result;
                    SymbolTable[SymbolTableIndex].type='C';
                    SymbolTable[SymbolTableIndex++].location=SmlVariableIndexCounter--;
                    resultLocation=SmlVariableIndexCounter+1;
                }
                SML[SmlInstructionCounter++]=21000+resultLocation; //Store in the next free spot
            }
            break;
        case '^':
            SML[SmlInstructionCounter++]=20000+a1; //LOAD a1
            SML[SmlInstructionCounter++]=35000+a2;//EXPONENTIATION a2

            if(isVariableIncluded)//the result will be stored in the next free spot
            {
                SML[SmlInstructionCounter++]=21000+SmlVariableIndexCounter;
                SmlVariableIndexCounter--;
            }else
            {
                result=pow(SML[a1],SML[a2]);
                snprintf(str, sizeof(str), "%f", result);//turns float to string
                resultLocation= returns_Constant_location_from_SymbolTable(str);
                if(resultLocation==-1)
                {
                    SymbolTable[SymbolTableIndex].symbol=result;
                    SymbolTable[SymbolTableIndex].type='C';
                    SymbolTable[SymbolTableIndex++].location=SmlVariableIndexCounter--;
                    resultLocation=SmlVariableIndexCounter+1;
                }
                SML[SmlInstructionCounter++]=21000+resultLocation; //Store in the next free spot
            }
            break;
        default:
            printf("Not valid operator");
            exit(1);
    }
}