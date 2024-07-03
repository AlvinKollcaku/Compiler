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
This Compiler turns the "Simple" but powerful language with 9 keywords into an assembly-like Simple Machine Language (SML). The project consists of three main parts:

1. **The Virtual Machine: Simpletron (SML folder)**
   - Simpletron is a virtual machine that runs programs written in SML.
   - It handles all information in terms of **words**, which are signed 5-digit decimal numbers (e.g., +10999).
   - Simpletron has a 1000-word memory, with each word referenced by locations 0 through 999.
   - Each SML instruction occupies one word of Simpletron's memory. The first two digits are the operation code, and the last three digits correspond to the memory location for the operation.
   - Example: `10999` means **READ** a value from the user and store it in location 999.
   - For detailed operation codes, see `SML/SML.txt`.

2. **Infix to Postfix Converter**
   - Converts complex infix expressions (e.g., `2+3`) into postfix (e.g., `2 3 +`) to be evaluated in SML.
   - Postfix expressions are converted to SML instructions using a stack-based evaluation.
   - Operators supported: `+`, `-`, `/`, `*`, `%`, `^`.
   - Example conversion: `2.3 + 22 * (2^2 % 3) * 22.75` becomes `2.3 22 2 2 ^ 3 % * 22.75 * +`.
   - Floating point numbers are allowed, and the range [-99999, 99999] is respected.

3. **The Compiler**
   - Converts each instruction in the **Simple** language into **SML**.
   - The Simple language includes commands: `rem`, `input`, `inputS`, `let`, `letS`, `print`, `goto`, `if..goto`, and `end`.
   - Operators in Simple have the same precedence as in C, and parentheses can change the order of evaluation.

### Compiler Passes
1. **First Pass**
   - Constructs a symbol table with every line number, variable name, numerical constant, and string literal.
   - Produces the corresponding SML instruction for each Simple statement.
   - Performs **error checking**.

2. **Second Pass**
   - Completes unfinished instructions and outputs the SML program to a file.
   - Example: Resolving `goto 60` if line 60 has not yet been reached in the first pass.

### Error Handling
The compiler handles various error cases, which are detailed in a separate section (to be included as necessary).

## Further Details
- For a complete explanation of operation codes, see `SML/SML.txt`.
- For an in-depth explanation of the compiler and the Simple language commands, see `Compiler/CompilerExplain.txt`.
   
![image](https://github.com/AlvinKollcaku/Compiler/assets/142890850/b5c260c0-e983-40ee-a309-8c2cd1a74eef)

## Features
- List of key features of the compiler
  - Converts simple language to the assembly like Simple machine language (SML)
  - Supports comments, string and numerical variable initialization, printing, conditional jumps, loops , subroutines (functions)

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

## Simple Language Keywords
- Detailed description of each keyword
  - `rem`: Comment
  - `input`: numerial input
  - `inputS`: String input
  - `letS`: String variable initialization
  - `let`: Numerical variable initialization
  - `print`: Print variables, string literals, and numerical constants
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

