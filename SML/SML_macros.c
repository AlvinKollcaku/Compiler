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

#define READ 10
#define WRITE 11
#define READ_STRING 12
#define WRITE_STRING 13

#define NEWLINE 14

#define LOAD 20
#define STORE 21

#define ADD 30
#define SUBTRACT 31
#define DIVIDE 32
#define MULTIPLY 33
#define REMAINDER 34
#define EXPONENTIATION 35

#define BRANCH 40
#define BRANCHNEG 41
#define BRANCHNEG_ZERO 42
#define BRANCHPOS 43
#define BRANCHPOS_ZERO 44
#define BRANCHZERO 45
#define BRANCHNOT_ZERO 46

#define HALT 49 //Putting it at 49 in case of new commands

typedef int make_iso_compilers_happy;
