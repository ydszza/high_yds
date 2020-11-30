#include "high_debug.h"

void Debug::printError(const char *error_msg) {
    if (!error_msg) return;
    perror(error_msg);
}

void Debug::printInfo(const char *info_msg) {
    if (!info_msg) return;
    printf("%s\n", info_msg);
}

