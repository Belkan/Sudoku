
#include <stdio.h>
#include <math.h>
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

/* validates if board is solvable and updates the solution if so. */
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
    if (value == 0 || safeMove(gameState->board, row, col, value, gameState->size)) {
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
    int row, col, count = 0;
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
}

/* checks if placement is legal */
bool safeMove(int **board, int row, int col, int val, int size) {
    int block = findBlock(row, col);

    return safeMoveRow(board, row, val, size) &&
           safeMoveCol(board, col, val, size) &&
           safeMoveBlock(board, block, val, size);
}

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

bool safeMoveBlock(int** board, int block, int val, int size) {
    int blockSize = (int)sqrt(size), i, j;
    int fromRow = (block / blockSize) * blockSize;
    int fromCol = (block % blockSize) * blockSize;
    for (i = fromRow; i <= fromRow + 2; i++) {
        for (j = fromCol; j <= fromCol + 2; j++) {
            if (board[i][j] == val) { /* val exists in block */
                return false;
            }
        }
    }
    return true;
}

void setFixedCellsRand(GameState *gameState, int fixed) {
    int row, col, counter, i, j;
    counter = 0;

    while (counter < fixed) {
        row = getRandom(0,8);
        col = getRandom(0,8);
        if (!gameState->fixed[row][col]) {
            gameState->fixed[row][col] = true;
            counter++;
        }
    }
    for (i = 0; i < gameState->size; i++) {
        for (j = 0; j < gameState->size; j++) {
            if (!gameState->fixed[i][j]) {
                gameState->board[i][j] = 0;
            }
        }
    }
}

void copyFromBoardToBoard(int** board1, int** board2, int size) {
    int i, j;
    for (i = 0; i < size; i++){
        for (j = 0; j < size; j++) {
            board2[i][j] = board1[i][j];
        }
    }
}

int findBlock(int row, int col) {
    return ((row / 3)*3 + (col / 3));
}

void setHandler (SET_STATUS status, GameState *gameState) {
    switch (status) {
        case (SUCCESS):
            printBoard(gameState, BOARD);
            break;
        case (ILLEGAL_MOVE):
            printf("Error: value is invalid\n");
            break;
        case (CELL_FIXED):
            printf("Error: cell is fixed\n");
            break;
        case (GAME_OVER):
            printf("Puzzle solved successfully\n");
            break;
        default:
            break;
    }
}
