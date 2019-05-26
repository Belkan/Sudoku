cmake_minimum_required(VERSION 3.13)
project(Sudoku C)

set(CMAKE_C_STANDARD 90)
set(GCC_COVERAGE_COMPILE_FLAGS "-fmessage-length=0 -ansi -Wall -Wextra -Werror -pedantic-errors")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )


add_executable(Sudoku main.c Game/Game.c Game/Game.h MainAux/MainAux.c MainAux/MainAux.h Parser/Parser.c Parser/Parser.h Solver/Solver.c Solver/Solver.h Solver/SolverUnitTest.c MainAux/MainAuxUnitTest.c Game/GameUnitTest.c Parser/ParserUnitTest.c Game/GameUnitTest.h MainAux/MainAuxUnitTest.h minunit.h Solver/SolverUnitTest.h)

