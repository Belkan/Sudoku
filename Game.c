
#include "Game.h"

/* tries to set value in (row, col) in board, and returns the status of the request */
SET_STATUS set (GameState *gameState, int row, int col, int value) {
    SET_STATUS Status;
    if (isFixed(row, col, gameState)) {
        Status = CELL_FIXED;
        return Status;
    }
    if (isLegalMove(gameState, row, col, value)) {
        Status = ILLEGAL_MOVE;
        return Status;
    }

    gameState->board[row][col] = value;
    if (fullBoard(gameState)){
        Status = GAME_OVER;
        return Status;
    }

    Status = SUCCESS;
    return Status;

}
void hint (GameState *gameState, int row, int col){}

void validate (GameState *gameState){}

void restart (GameState *gameState){}

/* TODO: check if it's in the same box (currently only checks row and col */
/* checks if this set is a legal set (assuming input is valid) */
bool isLegalMove(GameState *gameState, int row, int col, int value){
    int i;
    for (i = 0; i < 9; i++){
        if (gameState->board[i][col] == value || gameState->board[row][i] == value) {
            return false;
        }
    }
}

/* check if the board is full */
bool fullBoard(GameState *gameState){
    int i, j;
    for (i = 0; i < 9; i++){
        for (j = 0; j < 9; j++){
            if (gameState->board[i][j] == 0) {
                return false;
            }
        }
    }
    return true;
}