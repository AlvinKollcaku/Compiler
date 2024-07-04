# Simple Language to Assembly ![💻 Compiler](https://github.com/AlvinKollcaku/Compiler/assets/142890850/def1d7a8-80ea-400d-a689-97aec3a09145)

## Table of Contents
1. [Introduction](#introduction)
2. [Features](#features)
3. [Simple Language Keywords](#simple-language-keywords)
4. [Scheme for the process](#scheme-for-the-process)
5. [Error Handling](#error-handling)
6. [Demo Program](#demo-program)
7. [License](#license)


## Introduction
This Compiler turns the "Simple" but powerful language with 10 keywords into an assembly-like Simple Machine Language (SML). The project consists of three main parts:

1. **The Virtual Machine: Simpletron**
   - Simpletron is a virtual machine that runs programs written in SML.
   - It handles all information in terms of **words**, which are signed 5-digit decimal numbers (e.g., +10999).
   - Simpletron has a 1000-word memory, with each word referenced by locations 0 through 999.
   - Each SML instruction occupies one word of Simpletron's memory. The first two digits are the operation code, and the last three digits correspond to the memory location for the operation.
   - Example: `10999` means **READ** a value from the user and store it in location 999.
   - Numerical values occupy 1 cell in the memory
   - **Strings** occupy mulitple memory cells, where in each cell a char of the corresponding string is stored. In the cell where the first char is stored the length of the string is also stored.
   - There are 4 registers used in the language simulator:
   accumulator - special register in which information is put for Simpletron to use in calculations or examine it
   instructionCounter - will hold the current instruction number
   instructionRegister - will hold the current instruction (operationCode + operand)
   operationCode - will hold the first 2 digits of the instruction being executed
   operand - will hold the last 2 digits of the instruction being executed
   
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
     
## Further Details
- For a complete explanation of operation codes, see `SML/SML.txt`.
- For an in-depth explanation of the compiler and the Simple language, see `Compiler/CompilerExplain.txt`.
  
## Features
- List of key features of the compiler
  - Converts simple language to the assembly like Simple machine language (SML)
  - Supports comments, string and numerical variable initialization, printing, conditional jumps, loops , subroutines (functions)
    
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
   Invalid keyword: ![carbon](https://github.com/AlvinKollcaku/Compiler/assets/142890850/0bf16455-9e84-4cfb-9ae7-36505043b784)
   Missing goto in if statement: ![carbon](https://github.com/AlvinKollcaku/Compiler/assets/142890850/fd653578-57ed-4faa-bfb1-9538e3b9cadf)
2) Line numbers should be >= 0 . The following error message will be shown:
  ![carbon (1)](https://github.com/AlvinKollcaku/Compiler/assets/142890850/58d2ad86-3aa2-4957-aa0e-7f07ffbbb045)
3) String literals should include no spaces and should each be writen in "" seperately. Example: "I am" and "I " "am" is wrong while "I" "am" is correct.They must be less than 11 chars since memory is very limited. Error message:
   ![carbon](https://github.com/AlvinKollcaku/Compiler/assets/142890850/f8316f13-b7c9-4116-af93-0bae10bf4f54)
4) Overflow errors:
   ![carbon](https://github.com/AlvinKollcaku/Compiler/assets/142890850/f14809d2-579f-476f-b447-1d14a3f499c2)
   If during calculations the range [-99999,99999] is exceeded that is reported at runtime:
   ![carbon](https://github.com/AlvinKollcaku/Compiler/assets/142890850/9a82cc18-1ce7-46d7-89e3-375f7392ceed)
5) Divide by 0 attempts:
   ![carbon](https://github.com/AlvinKollcaku/Compiler/assets/142890850/af15e55e-5a30-449a-aeae-ea8c69f9e9f3)
6) A variable must not exceed length of 25 chars and must include only letters:
   ![carbon](https://github.com/AlvinKollcaku/Compiler/assets/142890850/6a91c61e-1fe0-4787-9b59-450349396370)
   ![carbon](https://github.com/AlvinKollcaku/Compiler/assets/142890850/95665f86-5aa3-4f61-8a8a-de21f24a6da6)
7)Numbers must not be longer than 19 characters
  ![carbon](https://github.com/AlvinKollcaku/Compiler/assets/142890850/d8d02447-7f0e-4321-bdf5-1bc6f29e667c)
8)If the Simple program is exceeds the 1000 word memory of SML an error will be thrown.
  ![carbon](https://github.com/AlvinKollcaku/Compiler/assets/142890850/2cff957f-f7d9-4fb7-9c78-fb8a45641d7c)

-Logical errors will lead to undefined behaviour(e.g. using let instead of lets to initialze a string variable).

## Demo Program

Some programs showcasing the power of the Simple language can be found in the Programs folder. For example, **HighestGrade.txt** demonstrates all features of the language. Below, I explain a shorter program to illustrate how execution works:

### Program: `Programs/EvenOrOdd.txt`
![carbon (1)](https://github.com/AlvinKollcaku/Compiler/assets/142890850/e8407b8e-d95a-4baa-a9ca-50858a2ae2e4)

### Symbol Table 

![carbon (1)](https://github.com/AlvinKollcaku/Compiler/assets/142890850/9605bfd5-4d5a-418d-93f6-5ec59b47d3a4)

This table organizes the symbols used in the program, categorizing them by their type (L for line number, S for string, V for variable, and C for constant) and their respective memory locations. Each entry corresponds to an element utilized in the Simple language program described earlier.

### Corresponding SML Program

![carbon](https://github.com/AlvinKollcaku/Compiler/assets/142890850/47557b8c-03eb-472a-b9c8-07d566dcfefe)

### Output  
![carbon](https://github.com/AlvinKollcaku/Compiler/assets/142890850/a7cbd24d-a2ff-4398-8d6c-d13629c9c12b)

### Registers and Memory
![carbon (1)](https://github.com/AlvinKollcaku/Compiler/assets/142890850/21fe246c-6bf4-4025-9adc-308ddfb74db7)

### Explanation

This program demonstrates basic flow control in the Program. Here's a breakdown of its functionality:

- **Printing Strings**: First line uses the `print` keyword to output multiple strings: "Enter", "a", "number", followed by a newline (NL).
                       In SML it corresponds to 4 instructions. 3 to print each string and one for the newline.
- **Input**: Line 1 uses the `input` keyword to prompt the user for a numerical input, which is stored in the variable `number`.
             Corresponds to 1 instruction in SML.
- **Conditional Branching**: Line 2 checks if the value stored in `number` is even (`number % 2 == 0`). If true, the program jumps to line 5; otherwise, it continues to line 3.
                             For SML first each side of the expression is turned into postfix. So the above expression becomes number 2 % == 0. Than the evaluation occurs.
                             We evaluate the left side by LOADING the value of number in accumulator, % the value in accumulator with 2 and storing the result in the next free spot.
                             Than we load this result in accumulator and subtract the right side value from it (Here: 0). If value in accumulaotr is 0 we branch, else we continue with
                             the next SML instruction.
- **Output Based on Condition**: 
  - If `number` is even, line 5 prints "Even".
  - If `number` is odd, line 3 prints "Odd".
- **End of Program**: Line 6 marks the end of the program execution.

The symbol table provides a structured view of all symbols used in the program, including line numbers, variables (`number`), constants (`2.00`, `0.00`), and string literals (`"Enter"`, `"Odd"`, `"Even"`). Each symbol is categorized by type and mapped to its corresponding memory location.

The corresponding SML program executes these operations in a simulated environment, reflecting the sequence of actions defined in the Simple language program.  

## License

This project is licensed under the GNU General Public License v3.0. You can redistribute it and/or modify it under the terms of the GPL-3.0 license.






