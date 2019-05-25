
#include <stdio.h>
#include "Game.h"
#include "../Solver/Solver.h"

/* tries to set value in (row, col) in board, and returns the status of the request */
SET_STATUS set(GameState *gameState, int row, int col, int value) {
    SET_STATUS Status;
    if (gameState->fixed[row][col]) {
        Status = CELL_FIXED;
        return Status;
    }
    if (!isUserLegalMove(gameState, row, col, value)) {
        Status = ILLEGAL_MOVE;
        return Status;
    }

    gameState->board[row][col] = value;
    if (isUserBoardFull(gameState)) {
        Status = GAME_OVER;
        return Status;
    }

    Status = SUCCESS;
    return Status;

}

void hint(GameState *gameState, int row, int col) {
    printf("Hint: set cell to %d\n", gameState->solution[row][col]);
}

// validates if board is solvable and updates the solution if so.
bool validate(GameState *gameState) {
    if (isSolvable(gameState)) {
        printf("Validation passed: board is solvable\n");
        return true;
    }
    printf("Validation failed: board is unsolvable\n");
    return false;
    }


/* checks if this set is a legal set (assuming input is valid) */
bool isUserLegalMove(GameState *gameState, int row, int col, int value) {
    if (safeMove(gameState->board, row, col, value, gameState->size)) {
        return true;
    }
    return false;
}

/* check if the board is full */
bool isUserBoardFull(GameState *gameState) {
    if (countBlanks(gameState, BOARD) == 0) {
        return true;
    }
    return false;
} /* EOF */

/* return number of empty cells in board */
int countBlanks(GameState *gameState, BOARD_TYPE type) {
    int row, col, count;
    int **board;
    switch(type){
        case BOARD:
            board = gameState->board;
            break;
        case SOLUTION:
            board = gameState->solution;
            break;
    }

    for (row = 0; row < gameState->size; row++) {
        for (col = 0; col < gameState->size; col++) {
            if (board[row][col] == 0) {
                count++;
            }
        }
    }
    return count;
} /* EOF */

/* checks if placement is legal */
bool safeMove(int **board, int row, int col, int val, int size) {
    int block = findBlock(row, col);

    return safeMoveRow(board, row, val, size) &&
           safeMoveCol(board, col, val, size) &&
           safeMoveBlock(board, block, val);
} /* EOF */

/* Util subfunctions used for safeMove */
bool safeMoveRow(int** board, int row, int val, int size) {
    int col;
    for (col = 0; col < size; col++) {
        if (board[row][col] == val)
            return false; /* val exists in row */
    }
    return true;
}

bool safeMoveCol(int** board, int col, int val, int size) {
    int row;

    for (row = 0; row < size; row++) {
        if (board[row][col] == val)
            return false; /* val exists in column */
    }
    return true;
}

/* TODO make this work for any size */
/// WORKS ONLY FOR SIZE 9
bool safeMoveBlock(int** board, int block, int val) {
    int fromRow, fromCol, toRow, toCol, i, j;

    switch (block) {
        case 0:
            fromRow = 0;
            fromCol = 0;
            toRow = BLOCK - 1;
            toCol = BLOCK - 1;
            break;
        case 1:
            fromRow = 0;
            fromCol = BLOCK;
            toRow = BLOCK - 1;
            toCol = 2 * BLOCK - 1;
            break;
        case 2:
            fromRow = 0;
            fromCol = 2 * BLOCK;
            toRow = BLOCK - 1;
            toCol = 3 * BLOCK - 1;
            break;
        case 3:
            fromRow = BLOCK;
            fromCol = 0;
            toRow = 2 * BLOCK - 1;
            toCol = BLOCK - 1;
            break;
        case 4:
            fromRow = BLOCK;
            fromCol = BLOCK;
            toRow = 2 * BLOCK - 1;
            toCol = 2 * BLOCK - 1;
            break;
        case 5:
            fromRow = BLOCK;
            fromCol = 2 * BLOCK;
            toRow = 2 * BLOCK - 1;
            toCol = 3 * BLOCK - 1;
            break;
        case 6:
            fromRow = 2 * BLOCK;
            fromCol = 0;
            toRow = 3 * BLOCK - 1;
            toCol = BLOCK - 1;
            break;
        case 7:
            fromRow = 2 * BLOCK;
            fromCol = BLOCK;
            toRow = 3 * BLOCK - 1;
            toCol = 2 * BLOCK - 1;
            break;
        case 8:
            fromRow = 2 * BLOCK;
            fromCol = 2 * BLOCK;
            toRow = 3 * BLOCK - 1;
            toCol = 3 * BLOCK - 1;
            break;
        default:
            printf("Error: safeMoveBlock has failed\n");
            fromRow = fromCol = toRow = toCol = 0;
            break;
    }

    for (i = fromRow; i <= toRow; i++) {
        for (j = fromCol; j <= toCol; j++) {
            if (board[i][j] == val) { /* val exists in block */
                return false;
            }
        }
    }
    return true;
} /* EOF */

void setFixedCellsRand(GameState *gameState, int fixed) {
    int row, col, counter;
    counter = 0;

    while (counter < fixed) {
        row = getRandom(0,8);
        col = getRandom(0,8);
        if (!gameState->fixed[row][col]) {
            gameState->fixed[row][col] = true;
            counter++;
        }
    }
    for (int i = 0; i < gameState->size; i++) {
        for (int j = 0; j < gameState->size; j++) {
            if (!gameState->fixed[i][j]) {
                gameState->board[i][j] = 0;
            }
        }
    }
}

void copyFromBoardToBoard(int** board1, int** board2, int size) {
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++) {
            board2[i][j] = board1[i][j];
        }
    }
}

int findBlock(int row, int col) {
    return ((row / 3)*3 + (col / 3));
} /* EOF */

