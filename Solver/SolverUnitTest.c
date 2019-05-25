#include "../MainAux/MainAux.h"
#include "../minunit.h"
#include "SolverUnitTest.h"
#include "Solver.h"
#include <stdlib.h>
#include <stdio.h>

int tests_run;

static char * verify_genRandSolution() {
    GameState *gameState = createGameState(SIZE);
    generateRandomSolution(gameState);
    printBoard(gameState, SOLUTION);
    destroyGameState(gameState);
    return 0;
}

static char * run_all_tests() {
    RUN_TEST(verify_genRandSolution);
    return 0;
}

int SolverUnitTest() {
    char *result = run_all_tests();
    if (result != 0) {
        printf("%s\n", result);
    }
    else {
        printf("All Solver tests passed\n");
        printf("Tests run: %d\n", tests_run);

    }
    return result != 0;
}

