#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "MainAux.h"
#include "Game.h"
#include "Solver.h"
#include "Parser.h"

int main(int argc, char *argv[]) {
    if (argc == 2) {
        srand((unsigned) atoi(argv[1]));
    } else {
        srand(5);
    }

    /* start playing... */
    START_GAME();
    return 0;
}
