
#include "FileHandler.h"
#include "Game.h"

void testFileHandler() {

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

    printf("TEST 2\n");
    gameState = loadFromFile("omri.txt");
    printBoard(gameState, BOARD);

    destroyGameState(gameState);

    printf("END OF TESTS\n");
}

void testJustLoad() {
    GameState *gameState = loadFromFile("omri.txt");
    destroyGameState(gameState);
}

void testSolutionCounter() {
    int result;
    GameState *myGame = createGameState(2, 1);
    printBoard(myGame, BOARD);

    result = solutionCounter(myGame);
    printf("returned: %d\n", result);
}
