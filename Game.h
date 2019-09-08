#ifndef SUDOKU_GAME_H
#define SUDOKU_GAME_H

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum game_mode {
    EDITMODE,
    SOLVEMODE,
    INITMODE
} GAME_MODE;

typedef struct GameState{
    int size;
    int rowsInBlock;
    int colsInBlock;
    int **board;
    bool **fixed;
    bool markErrors;
    GAME_MODE mode;
} GameState;

typedef enum set_status {
    SUCCESS,
    CELL_FIXED
} SET_STATUS;

/* Tries to set value in (row, col) in board, and returns the mode of the request */
SET_STATUS set(GameState *gameState, int row, int col, int value);

void setMarkErrors(GameState *gameState, bool val);

/* Validates if the current board is in a legal sudoku state. */
bool isBoardLegal(GameState *gameState);

/* Checks if this set is a legal set (assuming input is valid i.e. not fixed cell) */
bool isUserLegalMove(GameState *gameState, int row, int col, int value);

/* Checks if the board is full */
bool isUserBoardFull(GameState *gameState);

void checkFullBoard(GameState* gameState);

/* Returns number of empty cells in board */
int countBlanks(GameState *gameState);

/* Checks if placement is legal */
bool safeMove(int row, int col, int val, GameState* gameState);

/* Util subfunctions used for safeMove */
bool safeMoveRow(int row, int val, GameState* gameState);
bool safeMoveCol(int col, int val, GameState* gameState);
bool safeMoveBlock(int block, int val, GameState* gameState);
int findBlock(int row, int col, GameState* gameState);

/* Sets the amount of initial fixed cells for board */
void setFixedCellsRand(GameState *gameState, int fixed);

/* Util function to copy boards */
void copyFromBoardToBoard(GameState* gameStateFrom, GameState* gameStateTo);

/* Getters, setters and general util for GameState */
GameState *createGameState(int row, int col);
void destroyGameState(GameState *gameState);
void setCellValue (int row, int col, int value, GameState* gameState);
int getCellValue (int row, int col, GameState* gameState);
void setFixed (int row, int col, bool value, GameState* gameState);
bool isFixed (int row, int col, GameState* gameState);
int getSize (GameState* gameState);
int getRowsInBlock (GameState* gameState);
int getColsInBlock (GameState* gameState) ;
void setGameMode(GameState *gameState, GAME_MODE status);
GAME_MODE getGameMode(GameState *gameState);
void setMarkErrors(GameState *gameState, bool val);
bool getMarkErrors(GameState *gameState);

#endif
