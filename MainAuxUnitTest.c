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

void verify_getRandom() {
    int lower, upper, res;
    lower = 4;
    upper = INT_MAX;
    res = getRandom(lower, upper);
    printf("This should print an integer in [4, infinity]: %d\n", res);

    lower = 5;
    upper = 17;
    res = getRandom(lower, upper);
    printf("This should print an integer in [5,17]: %d\n", res);

    lower = 250;
    upper = 2796;
    res = getRandom(lower, upper);
    printf("This should print an integer in [250, 2796]: %d\n", res);

    lower = 2;
    upper = 3;
    res = getRandom(lower, upper);
    printf("This should print an integer in [2, 3]: %d\n", res);

}

void MainAuxUnitTest() {
    verify_printBoard();
    verify_getRandom();
}

