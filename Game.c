
#include "Game.h"

/* tries to set value in (row, col) in board, and returns the status of the request */
enum status set (int board[9][9], int row, int col, int value) {
    enum status Status;
    if (isFixed(row, col, board)) {
        Status = Fixed;
        return Status;
    }
    if (isLegalMove(board, row, col, value)) {
        Status = Invalid;
        return Status;
    }

    Status = Success;
    return Status;

}
void hint (int board[9][9], int row, int col){}

void validate (int board[9][9]){}

void restart (int board[9][9]){}

bool isLegalMove(int board[9][9], int row, int col, int value){}

void set_in_board(int board[9][9], int row, int col, int value){}