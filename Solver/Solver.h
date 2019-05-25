#ifndef SUDOKU_SOLVER_H
#define SUDOKU_SOLVER_H
#include <stdbool.h>
#include "../Game/Game.h"

/* generate new random board */
void generateRandomSolution(GameState *gameState);

int getNextRow(int size, int row, int col);

int getNextCol(int size, int col);


#endif //SUDOKU_SOLVER_H
