#include "high_debug.h"

void Debug::printError(const char *error_msg) {
    if (!error_msg) return;
    perror(error_msg);
}

void Debug::printInfo(const char *info_msg) {
    if (!info_msg) return;
    std::cout << info_msg << std::endl;
}

void Debug::printInfo(const std::string &info_msg) {
    std::cout << info_msg << std::endl;
}

