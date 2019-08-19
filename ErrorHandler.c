#include "ErrorHandler.h"

/* Error regarding loading files from text */
void throw_rowSizeNotFoundError() {
    printf("Error: row size not found while loading file! Please specify another file!\n");
}
void throw_colSizeNotFoundError() {
    printf("Error: column size not found while loading file! Please specify another file!\n");
}
void throw_loadedInWrongModeError() {
    printf("Error: files cannot be loaded in INIT mode!\n");
}
void throw_loadPathError() {
    printf("Error: incorrect file path given!\n");
}
