cmake_minimum_required(VERSION 3.13)
project(Sudoku C)

set(CMAKE_C_STANDARD 99)

add_executable(Sudoku main.c Game/Game.c Game/Game.h MainAux/MainAux.c MainAux/MainAux.h Parser/Parser.c Parser/Parser.h Solver/Solver.c Solver/Solver.h Solver/SolverUnitTest.c MainAux/MainAuxUnitTest.c Game/GameUnitTest.c Parser/ParserUnitTest.c Game/GameUnitTest.h MainAux/MainAuxUnitTest.h minunit.h Solver/SolverUnitTest.h)