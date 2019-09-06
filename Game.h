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
    int **solution;
    bool **fixed;
    bool markErrors;
    GAME_MODE mode;
} GameState;

typedef enum set_status {
    SUCCESS,
    CELL_FIXED
} SET_STATUS;

typedef enum board_type {
    BOARD,
    SOLUTION
} BOARD_TYPE;

/* Tries to set value in (row, col) in board, and returns the mode of the request */
SET_STATUS set(GameState *gameState, int row, int col, int value);

void setMarkErrors(GameState *gameState, bool val);

/* Gives user hint for next move */
void hint(GameState *gameState, int row, int col);

/* Validates if board is solvable and updates the solution if so. */
bool validate(GameState *gameState);

/* Validates if the current board is in a legal sudoku state. */
bool isBoardLegal(GameState *gameState);

/* Checks if this set is a legal set (assuming input is valid i.e. not fixed cell) */
bool isUserLegalMove(GameState *gameState, int row, int col, int value);

/* Checks if the board is full */
bool isUserBoardFull(GameState *gameState);

void checkFullBoard(GameState* gameState);

/* Returns number of empty cells in board */
int countBlanks(GameState *gameState,  BOARD_TYPE type);

/* Checks if placement is legal */
bool safeMove(int row, int col, int val, GameState* gameState, BOARD_TYPE type);

/* Util subfunctions used for safeMove */
bool safeMoveRow(int row, int val, GameState* gameState, BOARD_TYPE type);
bool safeMoveCol(int col, int val, GameState* gameState, BOARD_TYPE type);
bool safeMoveBlock(int block, int val, GameState* gameState, BOARD_TYPE type);
int findBlock(int row, int col, GameState* gameState);

/* Sets the amount of initial fixed cells for board */
void setFixedCellsRand(GameState *gameState, int fixed);

/* Util function to copy boards */
void copyFromBoardToBoard(GameState* gameStateFrom, BOARD_TYPE fromType, GameState* gameStateTo, BOARD_TYPE toType);

/* Getters, setters and general util for GameState */
GameState *createGameState(int row, int col);
void destroyGameState(GameState *gameState);
void setCellValue (int row, int col, int value, GameState* gameState, BOARD_TYPE type);
int getCellValue (int row, int col, GameState* gameState, BOARD_TYPE type);
void setFixed (int row, int col, bool value, GameState* gameState);
bool isFixed (int row, int col, GameState* gameState);
int getSize (GameState* gameState);
int getRowsInBlock (GameState* gameState);
int getColsInBlock (GameState* gameState) ;
void setGameMode(GameState *gameState, GAME_MODE status);
GAME_MODE getGameMode(GameState *gameState);
#endif
