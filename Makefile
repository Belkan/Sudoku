SudokuMake: Game.c MainAux.c Parser.c Solver.c
	gcc -Wall -ansi -Wextra -Werror -pedantic-errors -o Sudoku Game.c MainAux.c Parser.c Solver.c main.c -lm


