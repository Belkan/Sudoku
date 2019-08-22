#include "FileHandler.h"

/* Function to check for validity of loading a file: returns true if file can be loaded */
bool validLoadPath (char *filePath) {
    FILE *file;
    /* File exists and can be loaded */
    if ((file = fopen(filePath, "r")) != NULL) {
        /* Close file prior to returning */
        fclose(file);
        return true;
    }
    return false;
}

GameState *loadEmptyBoard() {
    GameState *gameState = initializeGame(3, 3);
    return gameState;
}

/* Function to load up a saved game board and update our game state with it */
void loadFromFile (char *filePath, GameState *gameState) {
    char *str[MAX];
    char *token;
    char *rowSize = (char *)malloc(CHAR_MAX), *colSize = (char *)malloc(CHAR_MAX);
    int i = 0, k = 0, j = 0, idx = 0;
    char *currLine = "Read this from file";
    FILE *loadedGame;

    /* Test for validity of board */
    if (!validLoadPath(filePath)) {
        throw_loadPathError();
        return;
    }
    /* Make sure game status is either Edit or Solve */
    if (getStatus(gameState) == INITMODE) {
        throw_loadedInWrongModeError();
        return;
    }

    /* Load up the game */
    loadedGame = fopen(filePath, "r");

    /* Read first line of loaded game into board */
    fgets(currLine, CHAR_MAX, loadedGame);

    /* Break line using delimeter */
    str[0] = NULL, str[1] = NULL;
    token = strtok(currLine, " \t\r\n");
    while (token != 0){
        str[idx++] = token;
        token = strtok(0, " \t\r\n");
    }

    /* Read row & col sizes */
    rowSize = str[0];
    colSize = str[1];
    if (!rowSize) {
        throw_rowSizeNotFoundError();
        return;
    }
    if (!colSize) {
        throw_colSizeNotFoundError();
        return;
    }

    /* Get rid of old board to load up new one */
    destroyGameState(gameState);
    START_GAME(atoi(rowSize), atoi(colSize), EDITMODE);

    /* Read board */
    for (i = 0; i < atoi(rowSize); i++) {
        k = 0;
        /* Grab line to read */
        fgets(currLine, CHAR_MAX, loadedGame);

        /* Iterate over line's whitespaces */
        while (currLine[j] == ' ' || currLine[j] == '\t' || currLine[j] == '\r' || currLine[j] == '\n') {
            if (currLine[j] == '\n') {
                break;
            }
            j++;
        }

        /* Reached end of the line */
        if (currLine[j] == '\n') {
            continue;
        }

        /* Read digits to board */
        if (isdigit(currLine[j])) {
            gameState->board[i][k] = currLine[j];
        }
        k++;
        /* Read fixed cells to board */
        if (currLine[j] == '.') {
            gameState->fixed[i][k-1] = true;
        }
    }

    /* Close the game */
    fclose(loadedGame);

    /* Free resources */
    free(rowSize);
    free(colSize);

}
