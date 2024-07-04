# Simple Language to Assembly Compiler ![💻 Compiler](https://github.com/AlvinKollcaku/Compiler/assets/142890850/def1d7a8-80ea-400d-a689-97aec3a09145)

## Table of Contents
1. [Introduction](#introduction)
2. [Features](#features)
3. [Language Keywords](#language-keywords)
4. [Scheme for the process](#scheme)
5. [Error Handling](#error-handling)
6. [Example Code](#example-code)
7. [Demo Program](#demo-program)

## Introduction
This Compiler turns the "Simple" but powerful language with 10 keywords into an assembly-like Simple Machine Language (SML). The project consists of three main parts:

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
   - Floating point numbers are allowed, and the range [-99999, 99999] must be respected.

3. **The Compiler**
   - Converts each instruction in the **Simple** language into **SML**.
   - The Simple language includes commands: `rem`, `input`, `inputS`, `let`, `letS`, `print`, `goto`, `if..goto`, and `end`.
   - Operators in Simple have the same precedence as in C, and parentheses can change the order of evaluation.

### Compiler Passes
1. **First Pass**
   - Constructs a symbol table with every line number, variable name, numerical constant, and string literal.
   - Produces the corresponding SML instruction for each Simple statement.
   - Performs **error checking** (Explained below).

2. **Second Pass**
   - Completes unfinished instructions and outputs the SML program to a file.
   - Example: Resolving `goto 60` if line 60 has not yet been reached in the first pass.
   - 
## Further Details
- For a complete explanation of operation codes, see `SML/SML.txt`.
- For an in-depth explanation of the compiler and the Simple language, see `Compiler/CompilerExplain.txt`.
  
## Features
- List of key features of the compiler
  - Converts simple language to the assembly like Simple machine language (SML)
  - Supports comments, string and numerical variable initialization, printing, conditional jumps, loops , subroutines (functions)
  - Strings occupy mulitple memory cells, where in each cell a char of the corresponding string is stored
    
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
  - `NL`: Newline
  - `end`: End of the program
    
## Scheme for the process
- Explanation of the process
![image](https://github.com/AlvinKollcaku/Compiler/assets/142890850/b5c260c0-e983-40ee-a309-8c2cd1a74eef)

## Error Handling
In each error case the line number where it occurred is shown.
1) The form of each statement is validated. The following error messages can be shown:
   Invalid keyword: ![carbon (1)](https://github.com/AlvinKollcaku/Compiler/assets/142890850/febdcc96-c1a1-4ae3-a70a-bc3278c90de4)
   Missing goto in if statement: ![carbon](https://github.com/AlvinKollcaku/Compiler/assets/142890850/d764709b-0706-46b1-8f6b-70a92e619131)
2) Line numbers should be >= 0 . The following error message will be shown:
   ![carbon (1)](https://github.com/AlvinKollcaku/Compiler/assets/142890850/977bd160-92a7-4951-8185-05c51b7152d7)
3) String literals should include no spaces and should each be writen in "" seperately. Example: "I am" and "I " "am" is wrong while "I" "am" is correct.They must be less than 11 chars since memory is very limited. Error message:
   ![carbon](https://github.com/AlvinKollcaku/Compiler/assets/142890850/d6accd13-a7c8-4dbe-a11e-35f71b66d73f)
4) Overflow errors:
   ![carbon (1)](https://github.com/AlvinKollcaku/Compiler/assets/142890850/1822e34c-e8e1-4544-99db-e8e466a73e17)
   If during calculations the range [-99999,99999] is exceeded that is reported at runtime:
   ![carbon](https://github.com/AlvinKollcaku/Compiler/assets/142890850/137c61dc-9a83-40f2-98ca-934f289c30b4)
5) Divide by 0 attempts:
   ![carbon (1)](https://github.com/AlvinKollcaku/Compiler/assets/142890850/5797205f-474d-4c51-9d43-889af7e04b54)
6) A variable must not exceed length of 25 chars and must include only letters:
   ![carbon](https://github.com/AlvinKollcaku/Compiler/assets/142890850/950c9ab2-a8e3-40db-919b-89b2b260e1ce)
   ![carbon](https://github.com/AlvinKollcaku/Compiler/assets/142890850/36183fe4-d868-4e82-af1d-ea58898993e0)
7)Numbers must not be longer than 19 characters
   ![carbon (1)](https://github.com/AlvinKollcaku/Compiler/assets/142890850/6f42e9c2-efcb-4ff4-a847-e006de4ee782)

- Logical errors will lead to undefined behaviour(e.g. using let instead of lets to initialze a string variable).

## Demo Program
- Some programs that I have written, which showcase the power of the Simple language can be found in the Programs folder. The one that uses all features is HighestGrade.txt.
- Here I will explain a much shorter program, just to give an idea how the conversion is done:
- 

