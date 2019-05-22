#include <stdio.h>
#include "MainAux.h"
#include "Game.h"
#include "Solver.h"
#include "Parser.h"
#include "GameUnitTest.h"

int main() {
    GameState* gameState = initializeGame(9);
//    printf("%d", gameState->board[0][0]);
    printBoard(gameState);
    GameUnitTest();
}
