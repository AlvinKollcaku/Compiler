#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<stdbool.h>
#include "CompilerHeader.h"

bool isKeyword(char *str)
{
    return (strcmp(str,"input")==0||strcmp(str,"if")==0||strcmp(str,"let")==0||
            strcmp(str,"goto")==0||strcmp(str,"print")==0||strcmp(str,"end")==0);
}

bool isVariable(char *var)
{
    return *var>=97 && *var<=122;
}

bool isConstant(const char* str) {
    if (str == NULL || strlen(str) == 0) {
        return false;
    }
    for (size_t i = 0; i < strlen(str); i++) {
        if (!isdigit((unsigned char)str[i])) {
            return false;
        }
    }
    return true;
}

bool isConditionalOperator(char c)
{
    return c=='='||c=='>'||c=='<'||c=='!';
}

int returns_SML_location_from_SymbolTable(char Symbol) //this is for variables
{
    for(int i=0; i<SymbolTableIndex; i++)
    {
        if(Symbol==(char)SymbolTable[i].symbol)
            return SymbolTable[i].location;
    }
    return -1;
}
//Using another function since line numbers can be double digits and strings need to
//be used with atoi() --> atoi("A")=0 Problem!
int returns_LineNum_location_from_SymbolTable(char* Symbol) //this is for line numbers
{
    for(int i=0; i<SymbolTableIndex; i++)
    {
        if(atoi(Symbol)==(int)SymbolTable[i].symbol && SymbolTable[i].type=='L')
            return SymbolTable[i].location;
    }
    return -1;
}

int returns_Constant_location_from_SymbolTable(char * constant)
{
    for(int i=0; i<SymbolTableIndex; i++)
    {
        if(atoi(constant)==SymbolTable[i].symbol && SymbolTable[i].type=='C')
            return SymbolTable[i].location;
    }
    return -1;
}

void printSymbolTable()
{
    // printf("SymbolTableIndex: %d\n",SymbolTableIndex);
    printf("Symbol \t Type \t Location\n");
    for(int i=0; i<SymbolTableIndex; i++)
    {
        if(SymbolTable[i].type=='L')
            printf("%.0lf\t %c\t %d\n",SymbolTable[i].symbol,SymbolTable[i].type,SymbolTable[i].location);
        else if(SymbolTable[i].type=='V')
            printf("%c\t %c\t %d\n",(char)SymbolTable[i].symbol,SymbolTable[i].type,SymbolTable[i].location);
        else
            printf("%.2lf\t %c\t %d\n",SymbolTable[i].symbol,SymbolTable[i].type,SymbolTable[i].location);

    }
}

void printSML()
{
    puts("");
    puts("-----------------------------------");
    puts("Printing the SML program");

    for(int i=0; i<SymbolTableIndex; i++)
    {
        if(SML[i]==0)
            break;
        printf("%.0lf\n",SML[i]);
    }
    printf("Variables and constants\n");
    for(int i=SmlVariableIndexCounter+1;i<1000;i++)
    {
        printf("%.1lf\n",SML[i]);
    }
}

void printFlagsArray()
{
    puts("Flags array");
    for(int i=1;i<=SymbolTableIndex;i++)
    {
        printf("%d ",flags[i]);
        if(i%10==0)
            puts("");
    }
}

bool isVariableInSymbolTable(int address)
{
    for(int i=0;i<SymbolTableIndex;i++)
    {
        if(SymbolTable[i].location==address)
            return true;
    }
    return false;
}