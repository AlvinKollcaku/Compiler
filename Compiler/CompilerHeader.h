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

#ifndef MINICOMPILERFINAL_COMPILERHEADER_H
#define MINICOMPILERFINAL_COMPILERHEADER_H

#include <stdbool.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 300 //max length of line in input file that contains the simple program

struct tableEntry
{
    char variable[30];//variable name or string literal
    double symbol;//constant or line num
    char type;//'C'=Numerical_Constant 'L'=line_number 'V'=Variable 'S'=String_Literal or StringVariable
    int location;//0 to 99 -> SMLs memory location associated with the symbol
    //char[20] command;
};

extern double SML[1000];// will hold the SML program
extern int SmlInstructionCounter;
extern int SmlVariableIndexCounter;
extern int flags[1000]; //flags array has the same size as SML because the index of the incomplete instruction
//in flags array will correspond to the index in SML array for the particular instruction

extern struct tableEntry SymbolTable[2000];
extern int SymbolTableIndex;
extern int lastValidLine;
extern bool isString;

typedef struct Postfix
{
    int address;
    struct Postfix * nextPtr;
}Postfix;

typedef struct Postfix * PostfixPtr;

//CompilerFunctions.c
void printSML();
bool isKeyword(char *str);
int returns_SML_location_from_SymbolTable(char *Symbol);
bool isValidVariable(char *var);
bool isConstant(const char* str);
void printSymbolTable();
int returns_LineNum_location_from_SymbolTable(char* Symbol);
int returns_LineNum_location_from_SymbolTable2(int Symbol); //this is for line numbers for the flags array
void printFlagsArray();
bool isVariableInSymbolTable(int address);
void completeInstructions();
void remove_newline(char *str);
void check_String_length(char * var);
void checkCounters();
bool isValidStringLiteral(char *var);
void writeArrayToFile(const char *filename, double *array, size_t size);

//Keywords.c
void inputKeyword(char *tokenPtr);
void conditionKeyword(char *tokenPtr);
void printKeyword(char *tokenPtr);
bool isConditionalOperator(char c);
void letKeyword(char *tokenPtr);
void gotoKeyword(char *tokenPtr);
void inputS(char *tokenPtr);
void newlineKeyword();
void letS(char *tokenPtr);

//KeywordHelper.c
void handleOperators(char Operators[],int Operands[],char * tokenPtr);
int evaluatePostfixExpression2(char *expr[]);
void pushPostfix(PostfixPtr *topPtr, int value);
int popPostfix(PostfixPtr *topPtr);
void reorganizeStack(int a1,int a2,char operator,PostfixPtr *topPtr);
void printPostfixStack(PostfixPtr topPtr);
int find_operator_position(const char *str);

//InfixFunctions.c -> in InfixToPostfix folder
bool isOperator(char  c);
void convertToPostfix(char *infix,char *postfix2[]);
char* charToString(char c);

//SML_functions.c -> in SML folder
void dump(double accumulator,int instructionCounter,int instructionRegister,
          int operationCode,int operand, double *memory);

void execute(double* accumulator,int* instructionCounter,int* instructionRegister,
             int* operationCode,int* operand, double *memory);

void load(double* memory,int instructionCounter);
int isInteger(double num);
void clear_input_buffer();

#endif //MINICOMPILERFINAL_COMPILERHEADER_H
