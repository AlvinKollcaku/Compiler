#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "CompilerHeader.h"

void inputKeyword(char *tokenPtr)
{
    //Now we have to put the variable in the symbol table if it is not already
    tokenPtr=strtok(NULL," "); //1)Going to the variable/constant
    //printf("CurrentToken:%s\n",tokenPtr);
    //printf("CASE:INPUT --> Value returned from function %d \n",x);
    int location=returns_SML_location_from_SymbolTable(tokenPtr);
    if(location==-1)
    {
        if(isValidVariable(tokenPtr))
        {
            strcpy(SymbolTable[SymbolTableIndex].variable,tokenPtr);
            SymbolTable[SymbolTableIndex].type='V';
            SymbolTable[SymbolTableIndex++].location=SmlVariableIndexCounter--;
            location=SmlVariableIndexCounter+1;
        }
    }
    SML[SmlInstructionCounter++]=10000+location;
}

void conditionKeyword(char *tokenPtr)
{
    /*There are 6 forms the if statement can take x==y x<y x>y x<=y x>=y x!=y*/

    int Operands[2]={-1,-1};

    tokenPtr = strtok(NULL, "\0");

    //printf("Current token %s\n",tokenPtr);
    //!Since strtok() replaces the first occurrence of the delimiter (int this case " ") with \0
    //!we use that to get the expression part with the goto which we will use to split again

    // printf("Token %s\n",tokenPtr);
    //Now that we have the string we need to find the position of the operator/s to split it
    // there into a left and right part
    char *expression,*left, Operators[3], *right;

    //expression=(char *) malloc(200*sizeof(char));
    left=(char *) malloc(100*sizeof(char));
    right=(char *) malloc(100*sizeof(char));

    // Allocate memory for expression and gotoLine
    expression = (char *)malloc(200 * sizeof(char));
    if (expression == NULL) {
        printf("Memory allocation for expression failed.\n");
        exit(1);
    }

    char *gotoLine = (char *)malloc(10 * sizeof(char));
    if (gotoLine == NULL) {
        printf("Memory allocation for gotLine failed.\n");
        exit(1);
    }

    // Find the position of "goto"
    char *findGoto = strstr(tokenPtr, "goto");
    /*
     This function returns a pointer point to the first character of the found s2 in s1 otherwise a null pointer
     if s2 is not present in s1.If s2 points to an empty string, s1 is returned.
     */
    if (findGoto != NULL) {
        // Copy the part before "goto" to expression
        size_t expressionLength = findGoto - tokenPtr;
        strncpy(expression, tokenPtr, expressionLength);
        expression[expressionLength] = '\0';  // Null-terminate the string

        // Skip the "goto" and any leading spaces to get the goto line
        findGoto += 4; // Skip "goto"
        while (*findGoto == ' ') findGoto++; // Skip leading spaces
        strcpy(gotoLine, findGoto);
    } else {
        printf("No 'goto' found in the if statement in line number %d.\n",lastValidLine);
        expression[0] = '\0';  // Set to empty string
        gotoLine[0] = '\0';    // Set to empty string
        exit(1);
    }

    //printf("Expression = %s\n",expression);
    //printf("Goto line = %s\n",gotoLine);

    // Find the position of the operator
    int pos = find_operator_position(expression);
    if (pos == -1) {
        printf("Operator not found in line %d\n",lastValidLine);
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

    handleOperators(Operators,Operands,gotoLine);
}

void letKeyword(char *tokenPtr)
{
    //1) Put all symbols that are not in the symbol table
    tokenPtr=strtok(NULL,"=");
    int left_variable_location=returns_SML_location_from_SymbolTable(tokenPtr);
   //printf("Left variable %s with location %d\n",tokenPtr,left_variable_location);
    if(left_variable_location==-1 )
    {
        strcpy(SymbolTable[SymbolTableIndex].variable,tokenPtr);
        SymbolTable[SymbolTableIndex].type='V';
        SymbolTable[SymbolTableIndex++].location=SmlVariableIndexCounter--;
        left_variable_location=SmlVariableIndexCounter+1;
    }
    tokenPtr=strtok(NULL,"=");

   // printf("Right side %s \n",tokenPtr);
    strcat(tokenPtr,"$");

    char * postfix[200];
    for(int i=0;i<200;i++)
    {
        postfix[i]="$";
    }
    convertToPostfix(tokenPtr,postfix);
   // printf("Posftix finished\n");

    SML[SmlInstructionCounter++]=20000+evaluatePostfixExpression2(postfix);//loading the result in accumulator
    SML[SmlInstructionCounter++]=21000+left_variable_location;//Storing the result in our variable
}

void letS(char *tokenPtr)
{
    tokenPtr=strtok(NULL,"=");
    int left_variable_location=returns_SML_location_from_SymbolTable(tokenPtr);
    //printf("Left variable %s with location %d\n",tokenPtr,left_variable_location);
    if(left_variable_location==-1 )
    {
        strcpy(SymbolTable[SymbolTableIndex].variable,tokenPtr);
        SymbolTable[SymbolTableIndex].type='S';
        SymbolTable[SymbolTableIndex++].location=SmlVariableIndexCounter--;
        left_variable_location=SmlVariableIndexCounter+1;
    }
    tokenPtr=strtok(NULL,"=");

    remove_newline(tokenPtr);

    for(int i=0;i< strlen(tokenPtr);i++)
    {
        if(isspace(tokenPtr[i]))
            continue;

        if(tokenPtr[i]=='\"') //We are dealing with a string literal
        {
            char *noSpacesString=tokenPtr+i;
            if(isValidStringLiteral(noSpacesString))
            {
                strcpy(SymbolTable[SymbolTableIndex].variable,noSpacesString);
                SymbolTable[SymbolTableIndex].type='S';
                SymbolTable[SymbolTableIndex++].location=left_variable_location;

                size_t len = strlen(noSpacesString);
                //Now that we are dealing with a valid string we store it in memory in sequence


                SML[left_variable_location]=(len-2)*10000+(int)noSpacesString[1]; //skipping \"

                for(int i=2;i<len-1;i++) //also skipping the last \" with len-1
                {
                    SML[SmlVariableIndexCounter--]=(int)noSpacesString[i];
                }
            }else
            {
                printf("Invalid string literal in let statement at line %d\n",lastValidLine);
                exit(1);
            }
            return;
        }
    }
}
void printKeyword(char *tokenPtr)
{
    char *pend;
    tokenPtr=strtok(NULL," ");//going to the variable or constant to print

    //printf("Current token %s with length %llu\n",tokenPtr, strlen(tokenPtr));

    while(tokenPtr!=NULL)
    {
        remove_newline(tokenPtr);
        if(strcmp(tokenPtr,"NL")==0)
        {
            newlineKeyword();
            tokenPtr=strtok(NULL," ");
            continue;
        }
        int location=returns_SML_location_from_SymbolTable(tokenPtr);
        if(location==-1)
        {
            //printf("%s is not in symbol table\n",tokenPtr);
            if(isValidVariable(tokenPtr))
            {
                strcpy(SymbolTable[SymbolTableIndex].variable,tokenPtr);
                SymbolTable[SymbolTableIndex].type='V';
                SymbolTable[SymbolTableIndex++].location=SmlVariableIndexCounter--;
                location=SmlVariableIndexCounter+1;
                SML[SmlInstructionCounter++]=11000+location;
            }
            else if(isValidStringLiteral(tokenPtr))
            {
                strcpy(SymbolTable[SymbolTableIndex].variable,tokenPtr);
                SymbolTable[SymbolTableIndex].type='S';
                SymbolTable[SymbolTableIndex++].location=SmlVariableIndexCounter;
                location=SmlVariableIndexCounter;

                size_t len = strlen(tokenPtr);
                //Now that we are dealing with a valid string we store it in memory in sequence

                SML[SmlVariableIndexCounter--]=(len-2)*10000+(int)tokenPtr[1]; //skipping \"

                for(int i=2;i<len-1;i++) //also skipping the last \" with len-1
                {
                    SML[SmlVariableIndexCounter--]=(int)tokenPtr[i];
                }
                SML[SmlInstructionCounter++]=13000+location;
            }else //We put the constant in the symbol table and in the SML array
            {
                SymbolTable[SymbolTableIndex].symbol=atoi(tokenPtr);
                SymbolTable[SymbolTableIndex].type='C';
                SymbolTable[SymbolTableIndex++].location=SmlVariableIndexCounter;
                SML[SmlVariableIndexCounter--]=strtof(tokenPtr, &pend);
                location=SmlVariableIndexCounter+1;
                SML[SmlInstructionCounter++]=11000+location;
            }
        }else
        {
            if(isValidVariable(tokenPtr) || isConstant(tokenPtr))
            {
                if(!isString)
                {
                    SML[SmlInstructionCounter++]=11000+location;
                }
                else
                    SML[SmlInstructionCounter++]=13000+location; //String literal
                isString=false;
            }
            else //it is a string literal
                SML[SmlInstructionCounter++]=13000+location;
        }
        tokenPtr=strtok(NULL," ");
        //printf("Next one %s\n",tokenPtr);
    }
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
    tokenPtr=strtok(NULL," "); //1)Going to the variable
    //printf("CurrentToken:%s\n",tokenPtr);
    if(!isValidVariable(tokenPtr))
    {
        printf("The variable after input keyword should be max 25 characters and should only contain letters"
               "->%s is not correct at line number %d",tokenPtr,lastValidLine);
        exit(1);
    }

    //printf("CASE:INPUT --> Value returned from function %d \n",x);
    int line=returns_SML_location_from_SymbolTable(tokenPtr);
    if(line==-1) //not in symbol table -> we put it there
    {
        //printf("Putting it in the symbol table\n");
        strcpy(SymbolTable[SymbolTableIndex].variable,tokenPtr);
        SymbolTable[SymbolTableIndex].type='S';
        SymbolTable[SymbolTableIndex++].location=SmlVariableIndexCounter;

        //printf("Inputted: %c\n",SymbolTable[SymbolTableIndex-1]);

        SML[SmlInstructionCounter++]=12000+SmlVariableIndexCounter;
        SmlVariableIndexCounter-=10;
        //1000 + the location for the referenced variable(which is the next token)
    }
    else
    {
        //We use its location in the symbol table
        SML[SmlInstructionCounter++]=12000+line;
    }
}

void newlineKeyword()
{
    SML[SmlInstructionCounter++]=14000;
}


