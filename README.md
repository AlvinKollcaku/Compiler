# Simple Language to Assembly Compiler 

## Table of Contents
1. [Introduction](#introduction)
2. [Features](#features)
3. [Installation](#installation)
4. [Usage](#usage)
5. [Language Keywords](#language-keywords)
6. [Example Code](#example-code)
7. [Demo Program](#demo-program)

## Introduction
This Compiler turns the "Simple" but powerful language with 9 keywords into an assembly like Simple Machine Language (SML). The project consists of 3 parts:
1) The SML language
     The simple language contains:
-Accumulator -> a special register in which info is put before Simple language uses it
                in calculations or examines it

-A word -> 4 digit signed decimal number
-A word=SimpleLanguage Instruction
        First 2 digits = operation code -> specify operation to be performed
        Last 2 digits = operand -> Memory location to do the operation on
-------------------------------------------------------------------------------------
Operation Code  -> Meaning

Input/Output
READ 10 -> Read a word(representing a value) from keyboard into specific memory location
WRITE 11 -> Write a word from a specific location in memory to the screen

Load/Store operations
LOAD 20 -> Load a word from a specific location in memory into the accumulator
STORE 21 -> Store a word from the accumulator into a specific location in memory

Arithmetic operations
ADD 30 -> Add a word from a specific location in memory to the word in the accumulator
            (the result is left in the accumulator)
SUBTRACT 30 -> SUBTRACT a word from a specific location in memory to the word in the accumulator
            (the result is left in the accumulator)
DIVIDE 30 -> DIVIDE a word from a specific location in memory to the word in the accumulator
            (the result is left in the accumulator)
MULTIPLY 30 -> MULTIPLY a word from a specific location in memory to the word in the accumulator
            (the result is left in the accumulator)

Transfer-of-control operations:
BRANCH 40 -> Branch to a specific location in memory
BRANCHNEG 41 -> Branch to a specific location in memory if the accumulator is negative
BRANCHZERO 42 -> Branch to a specific location in memory if the accumulator is zero
HALT 43 -> Halt the program

------------------------------------------------------------------------------------
There are 4 registers used in the language simulator
accumulator
instructionCounter - will hold the current instruction number
instructionRegister - will hold the current instruction (operationCode + operand)
operationCode - will hold the first 2 digits of the instruction being executed
operand - will hold the last 2 digits of the instruction being executed

1)Before running SML program we load it into memory

3) The infixToPostfix Converter
    -The job of this program is to convert arbitrarily complex infix expression like 2+3*(4-2) into postfix 2 3 4 2-*+. This is done because everything in the Simple lanugage has to be converted into SML. The infix expression can't be converted to SML directly, but the postfix one can. So the above expression will be evaluated with SML via the following commands after each of the constants have been put in the memory.
5) The compiler
6) 

## Features
- List of key features of the compiler
  - Converts simple language to assembly
  - Supports comments, string and numerical variable initialization, printing, conditional jumps, and more

## Installation
- Prerequisites
- Steps to install the compiler
  - Cloning the repository
  - Building the compiler
  - Installing dependencies

## Usage
- How to run the compiler
- Command-line options
- Input and output file formats

## Language Keywords
- Detailed description of each keyword
  - `rem`: Comment
  - `letS`: String initialization
  - `let`: Numerical variable initialization
  - `print`: Print variables, string literals, and constants
  - `if expression goto`: Conditional jump
  - `goto`: Unconditional jump
  - `end`: End of the program

## Example Code
- Sample code snippets
- Explanation of the example code
- Expected output after compilation

## Demo Program
- Overview of the demo game
- Code of the demo game
- How to run the demo game
- Screenshots or videos (if applicable)

