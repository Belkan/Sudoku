#include <stdio.h>
#include "Game.h"
#include "../minunit.h"
#include "../MainAux/MainAux.h"

int tests_run;

static char *verify_setSuccessful() {
    GameState *gameState = createGameState(SIZE);
    SET_STATUS status;
    status = set(gameState, 1, 2, 3);
    ASSERT_THAT(status == SUCCESS & gameState->board[1][2] == 3, "ERROR: verify_setSuccessful");
    return 0;
}

static char *verify_setIllegal() {
    GameState *gameState = createGameState(SIZE);
    SET_STATUS status;
    set(gameState, 1, 2, 3);
    status = set(gameState, 2, 2, 3);

    ASSERT_THAT (status == ILLEGAL_MOVE, "ERROR: verify_setIllegal");
    return 0;
    }


static char *verify_setFixed() {
    GameState *gameState = createGameState(9);
    SET_STATUS status;
    gameState->fixed[1][2] = true;
    status = set(gameState, 1, 2, 3);

    ASSERT_THAT(status == CELL_FIXED, "ERROR: verify_setFixed");
    return 0;
}

// TODO - add this when we finish Solver.
//void verify_gameOver() {
//
//}

static char * run_all_tests() {
    RUN_TEST(verify_setSuccessful);
    RUN_TEST(verify_setIllegal);
    RUN_TEST(verify_setFixed);
    return 0;
}

int GameUnitTest() {
    char *result = run_all_tests();
    if (result != 0) {
        printf("%s\n", result);
    }
    else {
        printf("All GameUnitTest tests passed\n");
        printf("Tests run: %d\n", tests_run);
    }
    return result != 0;
}




