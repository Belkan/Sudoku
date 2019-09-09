#include <stdlib.h>
#include <stdio.h>
#include "GeneralUtils.h"
#include "MainAux.h"
#include "Solver.h"

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
