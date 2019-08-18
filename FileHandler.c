#include <stdlib.h>
#include <stdio.h>
#include "FileHandler.h"

const char * getFullPath (char *relativePath) {
    char *actualPath = malloc(PATH_MAX);
    char __attribute__((unused)) *ptr;

    /* Utility function generates full path from relative path. */
    ptr = realpath(relativePath, actualPath);

    return actualPath;
}
