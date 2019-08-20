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

/* Function to load up a saved game board and update our game state with it */
void loadFromFile (char *filePath, GameState *gameState) {
    char *rowSize = (char *)malloc(CHAR_MAX), *colSize = (char *)malloc(CHAR_MAX);
    int i = 0, k = 0, j = 0;
    char *currLine = "Read this from file";
    FILE *loadedGame;
    /* Test for validity of board */
    if (!validLoadPath(filePath)) {
        throw_loadPathError();
        return;
    }

    /* Make sure game status is either Edit or Solve */
    if (getStatus(gameState) == INIT) {
        throw_loadedInWrongModeError();
        return;
    }

    /* Load up the game */
    loadedGame = fopen(filePath, "r");

    /* Read first line of loaded game into board */
    fgets(currLine, CHAR_MAX, loadedGame);

    /* Read row size */
    for (i = 0; i < size_t2int(strlen(currLine)); i++) {
        if (isdigit(currLine[i])) {
            rowSize[k] = currLine[i];
            k++;
        }
        else if (k > 0) {
            break;
        }
    }
    if (!rowSize) {
        throw_rowSizeNotFoundError();
        return;
    }

    k = 0;
    /* Read column size */
    for (; i < size_t2int(strlen(currLine)); i++) {
        if (isdigit(currLine[i])) {
            colSize[k] = currLine[i];
            k++;
        }
        else if (k > 0) {
            break;
        }
    }
    if (!colSize) {
        throw_colSizeNotFoundError();
        return;
    }

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
