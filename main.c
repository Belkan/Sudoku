#include <stdio.h>
#include "MainAux.h"
#include "Game.h"
#include "Solver.h"
#include "Parser.h"
#include "GameUnitTest.h"

int main() {
    GameState* gameState = createGameState(9);
    printBoard(gameState);
    GameUnitTest();
}
