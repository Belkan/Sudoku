SudokuMake = Game.c MainAux.c Parser.c Solver.c main.c
CC = gcc


sudokumake: 
	$(info	Making file...)
	$(CC) -Wall -ansi -Wextra -Werror -pedantic-errors -o sudoku $(SudokuMake) -lm
