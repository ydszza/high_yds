#ifndef __HIGH_DEBUG_
#define __HIGH_DEBUG_

#include <errno.h>
#include <iostream>
#include <string>

#define DEBUG_ON

#ifdef DEBUG_ON

class Debug {
public:
    static void printError(const char *error_msg);
    static void printInfo(const char *info_msg);
    static void printInfo(const std::string& info_msg);
};

#else


#endif // DEBUG

#endif // !__HIGH_DEBUG_
