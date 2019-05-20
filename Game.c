
#include "Game.h"

/* tries to set value in (row, col) in board, and returns the status of the request */
enum status set (GameState *gameState, int row, int col, int value) {
    enum status Status;
    if (isFixed(row, col, gameState)) {
        Status = Fixed;
        return Status;
    }
    if (isLegalMove(gameState, row, col, value)) {
        Status = Invalid;
        return Status;
    }

    gameState->board[row][col] = value;
    Status = Success;
    return Status;

}
void hint (GameState *gameState, int row, int col){}

void validate (GameState *gameState){}

void restart (GameState *gameState){}

/* TODO: check if it's in the same box (currently only checks row and col */
bool isLegalMove(GameState *gameState, int row, int col, int value){
    int i;
    for (i = 0; i < 9; i++){
        if (gameState->board[i][col] == value || gameState->board[row][i] == value) {
            return false;
        }
    }
}
