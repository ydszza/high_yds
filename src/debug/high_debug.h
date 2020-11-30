#ifndef __HIGH_DEBUG_
#define __HIGH_DEBUG_

#include <errno.h>
#include <stdio.h>

#define DEBUG_ON

#ifdef DEBUG_ON

class Debug {
public:
    static void printError(const char *error_msg);
    static void printInfo(const char *info_msg);
};

#else


#endif // DEBUG

#endif // !__HIGH_DEBUG_
