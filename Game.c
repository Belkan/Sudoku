
#include "Game.h"

/* tries to set value in (row, col) in board, and returns the status of the request */
enum status set (GameState gameState, int row, int col, int value) {
    enum status Status;
    if (isFixed(row, col, gameState)) {
        Status = Fixed;
        return Status;
    }
    if (isLegalMove(gameState, row, col, value)) {
        Status = Invalid;
        return Status;
    }

    set_in_board(gameState, row, col, value);
    Status = Success;
    return Status;

}
void hint (GameState gameState, int row, int col){}

void validate (GameState gameState){}

void restart (GameState gameState){}

bool isLegalMove(GameState gameState, int row, int col, int value){}

void set_in_board(GameState gameState, int row, int col, int value){}