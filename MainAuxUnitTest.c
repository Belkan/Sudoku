#include "MainAux.h"
#include "Game.h"
#include <stdlib.h>
#include <stdio.h>

void verify_printBoard() {
    GameState *gameState = createGameState(SIZE);
    printf("this should print the empty board:\n");
    printBoard(gameState);
    set(gameState, 1, 1, 1);
    set(gameState, 5,4,18);
    set(gameState, 4,3,9);
    printf("this should print a board with some fixed cells\n");
    printBoard(gameState);
    destroyGameState(gameState);
}

void MainAuxUnitTest() {
    verify_printBoard();
}

