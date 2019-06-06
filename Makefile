SudokuMake = Game.c MainAux.c Parser.c Solver.c main.c


sudokumake: 
	$(info	Making file...)
	gcc -Wall -ansi -Wextra -Werror -pedantic-errors -o sudoku $(SudokuMake) -lm
