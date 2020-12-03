#ifndef __HIGH_CONFIGURE_H_
#define __HIGH_CONFIGURE_H_

#include <fstream>
#include <iostream>
#include "./../debug/high_debug.h"

class Configuration {
public:
    Configuration();
    ~Configuration();

    bool isValid() const;
    int getPort() const;

private:
    bool _isValid;
    int _port;
};

#endif // !__HIGH_CONFIGURE_H_