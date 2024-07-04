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

#include <stdio.h>
#include <stdlib.h>
#include "SML_header.h"

int main2()
{
    printf("***          Welcome to the Simple Language           ***\n\n"
           "***Please enter your program one instruction ***\n"
           "***(or data word) at a time. I will type the ***\n"
           "***location number and a question mark (?).  ***\n"
           "***You then type the word for that location. ***\n"
           "***Type the sentinel -99999 to stop entering ***\n"
           "***your program.                             ***\n\n");

    double memory[1000]= {0}; //Indexes = location
    /*Each index holds an 4 digit instruction
    First 2 digits= operation code for example Read
    Last 2 digits= memory location for operand
    */

    double accumulator=0;
    int instructionCounter=0;
    int instructionRegister=0;
    int operationCode=0;
    int operand=0;

    //Loading phase
    load(memory,instructionCounter);

    printf("\n*** Program loading completed ***\n");
    printf("*** Program execution begins  ***\n\n");

    execute(&accumulator,&instructionCounter,&instructionRegister,
            &operationCode,&operand,memory);

    return 0;
}