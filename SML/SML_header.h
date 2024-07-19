/*
 * <Compiler>
 * Copyright (C) <2024> <Alvin Kollçaku>
 *
 * Author: Alvin Kollçaku
 * Contact: kollcakualvin@gmail.com
 * Year: 2024
 * Original repository of the project: https://github.com/AlvinKollcaku/Compiler
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
