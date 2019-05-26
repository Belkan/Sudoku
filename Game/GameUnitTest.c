#include <stdio.h>
#include "Game.h"
#include "../minunit.h"
#include "../MainAux/MainAux.h"

int tests_run;

static char *verify_setSuccessful() {
    GameState *gameState = createGameState(SIZE);
    SET_STATUS status;
    status = set(gameState, 1, 2, 3);
    ASSERT_THAT(status == SUCCESS && gameState->board[1][2] == 3, "ERROR: verify_setSuccessful");
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
    GameState *gameState = createGameState(SIZE);
    SET_STATUS status;
    gameState->fixed[1][2] = true;
    status = set(gameState, 1, 2, 3);

    ASSERT_THAT(status == CELL_FIXED, "ERROR: verify_setFixed");
    return 0;
}

static char * verify_countBlanks_ofEmptyBoard() {
    GameState *gameState = createGameState(SIZE);
    int blanks = countBlanks(gameState, BOARD);
    ASSERT_THAT(blanks == SIZE*SIZE,
            "ERROR: verify_countBlanks_ofEmptyBoard != SIZE*SIZE");

    return 0;
}

static char * verify_safeMove() {
    GameState *gameState = createGameState(SIZE);
    set(gameState, 5, 7, 3);
    ASSERT_THAT(
            safeMove(gameState->board,5,8,3,gameState->size) == false &&
            safeMove(gameState->board,5,4,3,gameState->size) == false &&
            safeMove(gameState->board,4,6,4,gameState->size) == true ,
            "ERROR: verify_safeMove, same row");
    ASSERT_THAT(
            safeMove(gameState->board,7,7,3,gameState->size) == false &&
            safeMove(gameState->board,4,7,3,gameState->size) == false &&
            safeMove(gameState->board,2,6,4,gameState->size) == true ,
            "ERROR: verify_safeMove, same col");
    ASSERT_THAT(
            safeMove(gameState->board,5,6,3,gameState->size) == false &&
            safeMove(gameState->board,3,8,3,gameState->size) == false &&
            safeMove(gameState->board,4,7,4,gameState->size) == true ,
            "ERROR: verify_safeMove, same box");

    return 0;

}

static char * run_all_tests() {
    RUN_TEST(verify_setSuccessful);
    RUN_TEST(verify_setIllegal);
    RUN_TEST(verify_setFixed);
    RUN_TEST(verify_countBlanks_ofEmptyBoard);
    RUN_TEST(verify_safeMove);
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




