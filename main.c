#include <stdio.h>
#include <stdlib.h>
#include "MainAux/MainAux.h"
#include "Game/Game.h"
#include "Solver/Solver.h"
#include "Parser/Parser.h"
#include "Game/GameUnitTest.h"
#include "MainAux/MainAuxUnitTest.h"
#include "minunit.h"
#include "Solver/SolverUnitTest.h"

int main(int argc, char *argv[]) {
    srand((unsigned) atoi(argv[1]));
//    MainAuxUnitTest();
//    tests_run = 0;
//    GameUnitTest();
//    tests_run = 0;
//    SolverUnitTest();
    START_GAME();
}
