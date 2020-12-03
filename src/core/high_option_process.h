#ifndef __HIGH_OPTION_PROCESS_H
#define __HIGH_OPTION_PROCESS_H

#include <string>
#include <cstring>
#include "./../debug/high_debug.h"
#include "high_common.h"

class optionProcess {
public:
    optionProcess(int argc, char** argv);

    bool getParseStatus() const;
    bool runOptions();
    bool isExit() const;

private:
    bool _parseStatus;
    bool _isExit;
    std::string _cmd;
    std::string _arg;

    bool _showVersion;
    bool _showHelp;
    bool _showConfig;
    bool _testConfig;
    bool _quitMode;
    char* _prefix;
    char* _conf_file;
    char* _conf_param;
    char* _signal;
    bool _process;
};


#endif // !__HIGH_OPTION_PROCESS_H