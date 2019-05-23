#include <stdio.h>
#include "MainAux/MainAux.h"
#include "Game/Game.h"
#include "Solver/Solver.h"
#include "Parser/Parser.h"
#include "Game/GameUnitTest.h"
#include "MainAux/MainAuxUnitTest.h"
#include "minunit.h"

int main() {
    MainAuxUnitTest();
    tests_run = 0;
    GameUnitTest();

}
