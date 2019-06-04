#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "MainAux.h"
#include "Game.h"
#include "Solver.h"
#include "Parser.h"
#include "GameUnitTest.h"
#include "MainAuxUnitTest.h"
#include "minunit.h"
#include "SolverUnitTest.h"

int main(int argc, char *argv[]) {
    assert(argc == 2);
    srand((unsigned) atoi(argv[1]));
/*    MainAuxUnitTest();
    tests_run = 0;
    GameUnitTest();
    tests_run = 0;
    SolverUnitTest();*/
    START_GAME();
    return 0;
}
