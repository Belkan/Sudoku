#include "GeneralUtils.h"

bool cellInRange(int cell, int size) {
    if (cell > size) return false;
    return true;
}

/* Utility function to extract integer value from string, similar to Java.  */
int nextInt(int startIdx, char *string) {
    int res = string[startIdx] - '0';

    while (isdigit(string[++startIdx])) {
        res *= 10;
        res += (string[startIdx] - '0');
    }
    return res;
}
