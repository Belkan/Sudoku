#include <stdio.h>
#include "MainAux.h"
#include "Game.h"
#include "Solver.h"
#include "Parser.h"
#include "GameUnitTest.h"
#include "MainAuxUnitTest.h"

int main() {
    GameState* gameState = createGameState(SIZE);
    MainAuxUnitTest();
    GameUnitTest();
}
