#ifndef SUDOKU_SOLVER_H
#define SUDOKU_SOLVER_H
#include <stdbool.h>
#include "../Game/Game.h"

typedef enum solution_type {
    DETERMINISTIC,
    RANDOM
} SOLUTION_TYPE ;
/* generate new random board */

bool isSolvableRecursion(GameState *gameState, int **solutionBoardCopy, int row, int col, SOLUTION_TYPE type);

bool isSolvable(GameState *gameState);

void generateRandomSolution(GameState *gameState);

int getNextRow(int size, int row, int col);

int getNextCol(int size, int col);


#endif //SUDOKU_SOLVER_H
