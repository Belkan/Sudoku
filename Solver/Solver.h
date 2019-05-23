#ifndef SUDOKU_SOLVER_H
#define SUDOKU_SOLVER_H
#include <stdbool.h>
#include "../Game/Game.h"

/* generate new random board */
bool generateRandBoard(GameState *gameState, int row, int col);

#endif //SUDOKU_SOLVER_H
