SudokuMake = Game.c MainAux.c Parser.c Solver.c main.c
CC = gcc
FLAGS = -Wall -ansi -Wextra -Werror -pedantic-errors


sudokumake: 
	@$(info	Making file...)
	@$(CC) $(FLAGS) -o sudoku $(SudokuMake) -lm
	$(info Done!)

all:
	sudoku clean
