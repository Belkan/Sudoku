#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "MainAux.h"
#include "Game.h"
#include "Solver.h"
#include "Parser.h"
#include "FileHandler.h"
#include "UnitTester.h"

int main(int argc, char *argv[]) {

    if (argc == 2) {
        srand((unsigned) atoi(argv[1]));
    } else {
        srand(5);
    }

    /* start playing... */
     START_GAME();
    /* testFileHandler();*/
    return 0;
}
