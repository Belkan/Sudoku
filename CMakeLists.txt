cmake_minimum_required(VERSION 3.13)
project(Sudoku C)

set(CMAKE_C_STANDARD 99)

add_executable(Sudoku main.c Game.c Game.h MainAux.c MainAux.h Parser.c Parser.h Solver.c Solver.h SolverUnitTest.c MainAuxUnitTest.c GameUnitTest.c ParserUnitTest.c)