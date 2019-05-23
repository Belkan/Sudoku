#include <stdio.h>
#include "MainAux/MainAux.h"
#include "Game/Game.h"
#include "Solver/Solver.h"
#include "Parser/Parser.h"
#include "Game/GameUnitTest.h"
#include "MainAux/MainAuxUnitTest.h"

int main() {
    GameState* gameState = createGameState(SIZE);
    MainAuxUnitTest();
    GameUnitTest();
}
