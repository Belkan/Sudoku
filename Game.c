
#include <stdio.h>
#include "Game.h"
#include "MainAux.h"

/* TODO: Remove this entire thing by making the needed checks in ParserUtils or CommandExecutioner. */
/* Tries to set value in (row, col) in board, and returns the status of the request */
SET_STATUS set(GameState *gameState, int row, int col, int value) {
    SET_STATUS status = SUCCESS;
    if (getGameMode(gameState) == EDITMODE) {
        setCellValue(row, col, value, gameState);
        return status;
    }
    if (isFixed(row, col, gameState)) {
        status = CELL_FIXED;
        return status;
    }
    setCellValue(row, col, value, gameState);
    return status;
}

bool isBoardLegal(GameState *gameState) {
    int row, col;
    for (row = 0; row < getSize(gameState); row++) {
        for (col = 0; col < getSize(gameState); col++) {
            if (getCellValue(row, col, gameState) != 0 &&
                !isUserLegalMove(gameState, row, col, getCellValue(row, col, gameState))) {
                return false;

            }
        }
    }
    return true;
}


/* Checks if this set is a legal set  */
bool isUserLegalMove(GameState *gameState, int row, int col, int value) {
    int oldValue = getCellValue(row, col, gameState);
    setCellValue(row, col, 0, gameState);
    if (value == 0 || safeMove(row, col, value, gameState)) {
        setCellValue(row, col, oldValue, gameState);
        return true;
    }
    setCellValue(row, col, oldValue, gameState);
    return false;
}

/* Checks if the board is full */
bool isUserBoardFull(GameState *gameState) {
    if (countBlanks(gameState) == 0) {
        return true;
    }
    return false;
}

/* Returns number of empty cells in board */
int countBlanks(GameState *gameState) {
    int row, col, count = 0;

    for (row = 0; row < getSize(gameState); row++) {
        for (col = 0; col < getSize(gameState); col++) {
            if (getCellValue(row, col, gameState) == 0) {
                count++;
            }
        }
    }
    return count;
}

/* Checks if placement is legal */
bool safeMove(int row, int col, int val, GameState *gameState) {
    int block = findBlock(row, col, gameState);

    return safeMoveRow(row, val, gameState) &&
           safeMoveCol(col, val, gameState) &&
           safeMoveBlock(block, val, gameState) &&
           val > 0 && val <= gameState->size;
}

/* Util subfunctions used for safeMove */

bool safeMoveRow(int row, int val, GameState *gameState) {
    int col;
    for (col = 0; col < getSize(gameState); col++) {
        if (getCellValue(row, col, gameState) == val)
            return false; /* val exists in row */
    }
    return true;
}

bool safeMoveCol(int col, int val, GameState *gameState) {
    int row;

    for (row = 0; row < getSize(gameState); row++) {
        if (getCellValue(row, col, gameState) == val)
            return false; /* val exists in column */
    }
    return true;
}

bool safeMoveBlock(int block, int val, GameState *gameState) {
    int row, col;
    int fromRow = (block / getRowsInBlock(gameState)) * getRowsInBlock(gameState);
    int fromCol = (block % getRowsInBlock(gameState)) * getColsInBlock(gameState);
    for (row = fromRow; row < fromRow + getRowsInBlock(gameState); row++) {
        for (col = fromCol; col < fromCol + getColsInBlock(gameState); col++) {
            if (getCellValue(row, col, gameState) == val) { /* val exists in block */
                return false;
            }
        }
    }
    return true;
}

int findBlock(int row, int col, GameState *gameState) {
    int rows = getRowsInBlock(gameState);
    int cols = getColsInBlock(gameState);
    return (row / rows) * rows + (col / cols);
}

void checkFullBoard(GameState* gameState) {
    if (isUserBoardFull(gameState)) {
        if (isBoardLegal(gameState)) {
            printf("Congratulations! You successfully completed this puzzle!\n");
            setGameMode(gameState, INITMODE);
        } else {
            printf("Unfortunately, there is a mistake in your solution. You can still try to correct it!\n");
        }
    }
}

/* Getters, setters and general util for GameState */

GameState *createGameState(int rowsInBlock, int colsInBlock) {
    int i;
    GameState *gameState = malloc(sizeof(GameState));
    int size = rowsInBlock * colsInBlock;
    gameState->size = size;
    gameState->rowsInBlock = rowsInBlock;
    gameState->colsInBlock = colsInBlock;
    gameState->markErrors = false;
    gameState->mode = INITMODE;
    gameState->board = (int **) malloc(size * sizeof(int *));
    for (i = 0; i < size; i++) {
        gameState->board[i] = (int *) calloc(size, sizeof(int));
    }
    gameState->fixed = (bool **) malloc(size * sizeof(bool *));
    for (i = 0; i < size; i++) {
        gameState->fixed[i] = (bool *) calloc(size, sizeof(bool));
    }
    return gameState;
}

void destroyGameState(GameState *gameState) {
    destroyMatrix(gameState->board, gameState->size);
    destroyMatrix((int **) gameState->fixed, gameState->size);
    free(gameState);
}

void setCellValue(int row, int col, int value, GameState *gameState) {
    gameState->board[row][col] = value;
}

int getCellValue(int row, int col, GameState *gameState) {
    return gameState->board[row][col];
    }

void setFixed(int row, int col, bool value, GameState *gameState) {
    gameState->fixed[row][col] = value;
}

bool isFixed(int row, int col, GameState *gameState) {
    return gameState->fixed[row][col];
}

int getSize(GameState *gameState) {
    return gameState->size;
}

int getRowsInBlock(GameState *gameState) {
    return gameState->rowsInBlock;
}

void setMarkErrors(GameState *gameState, bool val) {
    gameState->markErrors = val;
}

int getColsInBlock(GameState *gameState) {
    return gameState->colsInBlock;
}

void setGameMode(GameState *gameState, GAME_MODE status) {
    gameState->mode = status;
}

GAME_MODE getGameMode(GameState *gameState) {
    return gameState->mode;
}
