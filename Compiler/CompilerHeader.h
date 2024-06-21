//
// Created by alvin on 12.06.2024.
//

#ifndef MINICOMPILERFINAL_COMPILERHEADER_H
#define MINICOMPILERFINAL_COMPILERHEADER_H

#include <stdbool.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 200 //max length of line in input file that contains the simple program

struct tableEntry
{
    int symbol;//ASCII value of var, constant or line num
    char type;//'C'=constant 'V'=variable 'L'=line number
    int location;//0 to 99 -> Simpletrons memory location associated with the symbol
    //char[20] command;
};

extern int SML[1000];// will hold the SML program
extern int SmlInstructionCounter;
extern int SmlVariableIndexCounter; //TODO check if SMLInstrcutioncounter > SMLVairableIndexCounter -> raise "out of memory error"
extern int flags[1000]; //flags array has the same size as SML because the index of the incomplete instruction
//in flags array will correspond to the index in SML array for the particular instruction

extern struct tableEntry SymbolTable[2000];
extern int SymbolTableIndex;

void printSML();
bool isKeyword(char *str);
int returns_SML_location_from_SymbolTable(char Symbol);
bool isVariable(char *var);
bool isKeyword(char *str);
bool isConstant(const char* str);
void inputKeyword(char *tokenPtr);
void conditionKeyword(char *tokenPtr);
bool isConditionalOperator(char c);
void printSymbolTable();
int returns_LineNum_location_from_SymbolTable(char* Symbol);
void printFlagsArray(int size);
void letKeyword(char *tokenPtr);
void handleOperators(char Operators[],char Operands[],char * tokenPtr);
void convertToPostfix(char *infix,char *postfix2[]);

#endif //MINICOMPILERFINAL_COMPILERHEADER_H
