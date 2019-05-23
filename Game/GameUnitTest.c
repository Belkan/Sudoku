#include <stdio.h>
#include "Game.h"
#include "../MainAux/MainAux.h"



void verify_setSuccessful(){
    GameState* gameState = createGameState(SIZE);
    SET_STATUS status;
    status = set(gameState, 1, 2, 3);

    if (status != SUCCESS || gameState->board[1][2] != 3) {
        printf("ERROR: verify_setSuccessful\n");
    }
}

void verify_setIllegal() {
    GameState* gameState = createGameState(SIZE);
    SET_STATUS status;
    set(gameState, 1, 2, 3);
    status = set(gameState, 2, 2, 3);

    if (status != ILLEGAL_MOVE) {
        printf("ERROR: verify_setIllegal\n");
    }
}

void verify_setFixed() {
    GameState* gameState = createGameState(9);
    SET_STATUS status;
    gameState->fixed[1][2] = true;
    status = set(gameState, 1, 2, 3);

    if (status != CELL_FIXED){
        printf("ERROR: verify_setFixed\n");
    }
}

// TODO - add this when we finish Solver.
//void verify_gameOver() {
//
//}

void GameUnitTest() {
    verify_setSuccessful();
    verify_setIllegal();
    verify_setFixed();
}



