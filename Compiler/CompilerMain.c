#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<stdbool.h>
#include "CompilerHeader.h"
#include "C:\Users\alvin\OneDrive\Desktop\MiniCompilerFinal\InfixToPostfix\InfixHeader.h"

int SML[1000]={0};// will hold the SML program
 int SmlInstructionCounter=0;
 int SmlVariableIndexCounter=999; //TODO check if SMLInstrcutioncounter > SMLVairableIndexCounter -> raise "out of memory error"
 int flags[1000]; //flags array has the same size as SML because the index of the incomplete instruction
//in flags array will correspond to the index in SML array for the particular instruction

 struct tableEntry SymbolTable[2000];
 int SymbolTableIndex=0;

int main4()
{
    for(int i=0; i<1000; i++)
        /*goto(x) will store x since we do not have x in the symbol table yet
        x will be stored in same subscript as incomplete instruction line*/
    {
        flags[i]=-1; //flags[SmlInstructionCounter++]
    }

    //READING THE SIMPLE PROGRAM FROM THE FILE
    FILE * infile=NULL;
    infile=fopen("C:\\Users\\alvin\\OneDrive\\Desktop\\MiniCompilerFinal\\Compiler\\Simple.txt","r");
    if (infile == NULL)
    {
        perror("Unable to open the file");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    // Reading lines from the file until the end

    while (fgets(line, MAX_LINE_LENGTH, infile) != NULL)
    {
        //printf("Current line:%s\n",line);

        //fgets(line, MAX_LINE_LENGTH, infile) != NULL
        //while (fscanf(infile, "%s", line) != EOF) {
        //strtok(line, " "): This function splits the string line
        // into tokens using a space (" ") as the delimiter.
        char *tokenPtr = strtok(line," ");
        //strtok treats the newline char as a delimiter by default

        //printf("THe line:%s\n",line);
        //printf("THe token: %s\n",tokenPtr);

        bool LineNumber=true; //Will be turned to False after first token
        //Will process a single row
        while(tokenPtr!=NULL) //assuming everything is written in lowerCase
        {
            //printf("TOKEN: %s\n",tokenPtr);
            //Putting the line number first in the symbol table
            //TODO could also just check if a symbol is in the symbol table or not to input it
            //TODO Watch out for constants tho
            if(LineNumber)
            {
                SymbolTable[SymbolTableIndex].symbol=atoi(tokenPtr);
                SymbolTable[SymbolTableIndex].type='L';
                SymbolTable[SymbolTableIndex++].location=SmlInstructionCounter;//unchanged
                LineNumber=false;
            }
            else if(strcmp(tokenPtr,"rem")==0) //If the keyword is rem we ignore the line
                break;
            else if(isKeyword(tokenPtr))
            {
                //CASE 1: INPUT
                //TODO check if the argument is a variable
                if(strcmp(tokenPtr,"input")==0) //input= READ instruction in SML
                {
                    inputKeyword(tokenPtr);
                }
                else if(strcmp(tokenPtr,"if")==0)  //CASE 2: IF STATEMENT
                {
                    conditionKeyword(tokenPtr);
                    break;
                }else if(strcmp(tokenPtr,"let")==0)
                {
                    letKeyword(tokenPtr);
                    break;
                }
            }
            else
            {
                printf("DONT KNOW WHAT THE TOKEN IS");
                exit(0);
            }

            //printf("%s\n",tokenPtr);
            tokenPtr=strtok(NULL," "); //= continue to parse the string from where the last token was found
        }
    }

    fclose(infile);

    printSymbolTable(SymbolTable,SymbolTableIndex);
    printSML(SML);
    printFlagsArray(15);

    return 0;
}


/* TODO in the if case if x>y it is taken as single token-> Temp solution use spaces to seperate
a single tokenPtr-> check tokenPtr length!=1*/
/* TODO: Remove the arguments for most function when they are already global vars*/
/* TODO: With comparisons we can only have 2 operators -> fix
 * MAJOR TODO: Simple langauge only works with 1 char variables and constants
So x > 2+2 does not work*/