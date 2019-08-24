#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "MainAux.h"
#include "Game.h"
#include "Solver.h"
#include "Parser.h"
#include "FileHandler.h"

int main(int argc, char *argv[]) {

    /* @TODO more rigorous tests */
    /* Testing functionality of saving boards. */
    GameState *gameState = createGameState(3, 3);

    set(gameState, 2, 2, 5);
    set(gameState, 1, 1, 2);
    set(gameState, 1, 2, 4);
    set(gameState, 2, 1, 6);
    setFixed(2, 2, true, gameState);

    printBoard(gameState, BOARD);

    printf("TEST 1\n");
    saveToFile("adar.txt", gameState);

    printf("TEST 2\n");
    saveToFile("omri.txt", gameState);

    printf("END OF TESTS\n");

    if (validLoadPath("cmake-build-debug/omri.txt")) {
        printf("omri.txt loaded successfully\n");
    }

    /* Testing functionality of loading boards */
    printf("TEST 1\n");
    gameState = loadEmptyBoard();
    printBoard(gameState, BOARD);

    /* TODO why doesn't this work? */
    printf("TEST 2\n");
    gameState = loadFromFile("cmake-build-debug/omri.txt");
    printBoard(gameState, BOARD);

    destroyGameState(gameState);

    printf("END OF TESTS\n");


    if (argc == 2) {
        srand((unsigned) atoi(argv[1]));
    } else {
        srand(5);
    }

    /* start playing... */
    /* START_GAME(3, 3, INITMODE); */


    return 0;
}
