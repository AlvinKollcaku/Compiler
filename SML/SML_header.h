#ifndef MINICOMPILERFINAL_SML_HEADER_H
#define MINICOMPILERFINAL_SML_HEADER_H
#define CUSTOM_TAB "         "
#include <stdbool.h>

extern int SmlInstructionCounter;
extern int SymbolTableIndex;

void dump(double accumulator,int instructionCounter,int instructionRegister,
          int operationCode,int operand, double *memory);

void execute(double* accumulator,int* instructionCounter,int* instructionRegister,
             int* operationCode,int* operand, double *memory);

void load(double* memory,int instructionCounter);
int isInteger(double num);
bool is_valid_float(const char *str);
void clear_input_buffer();

#endif //MINICOMPILERFINAL_SML_HEADER_H
