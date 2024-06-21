cmake_minimum_required(VERSION 3.28)
project(MiniCompilerFinal C)

set(CMAKE_C_STANDARD 17)

add_executable(MiniCompilerFinal
        SML/SML_main.c
        SML/SML_header.h
        SML/SML_macros.c
        SML/SML_functions.c
        InfixToPostfix/InfixMain.c
        InfixToPostfix/InfixFunctions.c
        InfixToPostfix/InfixHeader.h
        Compiler/CompilerFunctions.c
        Compiler/CompilerHeader.h
        Compiler/CompilerMain.c
        Compiler/Keywords.c
)
