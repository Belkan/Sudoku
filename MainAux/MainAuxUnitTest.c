#include "MainAux.h"
#include "../minunit.h"
#include <stdlib.h>
#include <stdio.h>

int tests_run;

static char * verify_printBoard() {
    GameState *gameState = createGameState(SIZE);
    printBoard(gameState, BOARD);
    destroyGameState(gameState);
    return 0;
}

static char * verify_printSolution() {
    GameState *gameState = createGameState(SIZE);
    printBoard(gameState, SOLUTION);
    destroyGameState(gameState);
    return 0;

}

static char * verify_getRandom() {
    int lower, upper, res;
    lower = 4;
    upper = INT_MAX;
    res = getRandom(lower, upper);
    ASSERT_THAT(res >= 4 && res <= INT_MAX, "ERROR (verify_getRandom), int not in range (4,max)");

    lower = 5;
    upper = 17;
    res = getRandom(lower, upper);
    ASSERT_THAT(res >= 5 && res <= 17, "ERROR (verify_getRandom), int not in range (4,max)");

    lower = 2;
    upper = 3;
    res = getRandom(lower, upper);
    ASSERT_THAT(res >= 2 && res <= 3, "ERROR (verify_getRandom), int not in range (4,max)");
    return 0;
}

char * run_all_tests() {
    RUN_TEST(verify_getRandom);
    RUN_TEST(verify_printBoard);
    RUN_TEST(verify_printSolution);

    return 0;
}

int MainAuxUnitTest() {
    char *result = run_all_tests();
    if (result != 0) {
        printf("%s\n", result);
    }
    else {
        printf("All MainAuxUnitTest tests passed\n");
        printf("Tests run: %d\n", tests_run);

    }
    return result != 0;
}


