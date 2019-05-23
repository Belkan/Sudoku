
#include <stdio.h>
#include "Game.h"

/* tries to set value in (row, col) in board, and returns the status of the request */
SET_STATUS set(GameState *gameState, int row, int col, int value) {
    SET_STATUS Status;
    if (isFixedCell(row, col, gameState)) {
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

void hint(GameState *gameState, int row, int col) {}

void validate(GameState *gameState) {}

void restart(GameState *gameState) {}

/* TODO: check if it's in the same box (currently only checks row and col */
/* checks if this set is a legal set (assuming input is valid) */
bool isUserLegalMove(GameState *gameState, int row, int col, int value) {
    if (safeMove(gameState, row, col, value, BOARD)) {
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

/* TODO make this function generic i.e. able to reference gameState->solution and gameState->board */
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
bool safeMove(GameState *gameState, int row, int col, int val, BOARD_TYPE type) {
    int block = findBlock(row, col);
    int** board;
    switch(type){
        case BOARD:
            board = gameState->board;
            break;
        case SOLUTION:
            board = gameState->solution;
            break;
    }
    return safeMoveRow(board, row, val, gameState->size) &&
           safeMoveCol(board, col, val, gameState->size) &&
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

int findBlock(int row, int col) {
    return ((row / 3)*3 + (col / 3));
} /* EOF */

/* generates a random solved board */
/* TODO see this actually generates a random board */
bool generateRandBoard(GameState *gameState, int row, int col) {
    int val, i, k, nextCol, nextRow;
    char possibleVals[8];
    if (countBlanks(gameState, 's') == 0) {
        return true; /* finished placement of all board */
    }

    /* get a random cell to recursively call */
    nextRow = getRandom(0, SIZE - 1);
    nextCol = getRandom(0, SIZE - 1);

    /* a value has already been placed in this location */
    if (gameState->solution[row][col] != 0) {
        return generateRandBoard(gameState, nextRow, nextCol);
    }

    k = 0;
    for (i = 1; i < 10; i++) {
        if (safeMove(gameState, row, col, i, 's')) {
            possibleVals[k] = i;
            k++;
        }
    }

    if (k == 0) {
        /* no legal moves available */
        return false;
    }

    /* choose random value out of possible values */
    i = getRandom(1, k);
    val = possibleVals[i];
    gameState->solution[row][col] = val;

    if (generateRandBoard(gameState, nextRow, nextCol)) {
        return true;
    } else {
        /* unsuccessful value chosen, reset it */
        gameState->solution[row][col] = 0;
    }
    return false;
} /* EOF */