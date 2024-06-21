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

int returns_SML_location_from_SymbolTable(char  Symbol)
{
    for(int i=0; i<=SymbolTableIndex; i++)
    {
        if(Symbol==SymbolTable[i].symbol)
            return SymbolTable[i].location;
    }
    return -1;
}
//Using another function since line numbers can be double digits and strings need to
//be used with atoi() --> atoi("A")=0 Problem!
int returns_LineNum_location_from_SymbolTable(char* Symbol)
{
    for(int i=0; i<=SymbolTableIndex; i++)
    {
        if(atoi(Symbol)==SymbolTable[i].symbol)
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
            printf("%d\t %c\t %d\n",SymbolTable[i].symbol,SymbolTable[i].type,SymbolTable[i].location);
        else
            printf("%c\t %c\t %d\n",SymbolTable[i].symbol,SymbolTable[i].type,SymbolTable[i].location);
    }
}

void printSML()
{
    puts("");
    puts("-----------------------------------");
    puts("Printing the SML program");

    for(int i=0; i<100; i++)
    {
        printf("%d\n",SML[i]);
        if(SML[i]==0)
            break;
    }

}

void printFlagsArray(int size)
{
    puts("Flags array");
    for(int i=1;i<=size;i++)
    {
        printf("%d ",flags[i]);
        if(i%5==0)
            puts("");
    }
}