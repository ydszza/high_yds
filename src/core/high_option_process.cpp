#include "high_option_process.h"

optionProcess::optionProcess(int argc, char** argv) {
    for (int i = 1; i < argc; i++) {

        char *p = argv[i];

        if (*p++ != '-') {
            Debug::printInfo("Invalid option");
            _parseStatus = false;
            return;
        }

        while (*p) {
            switch (*p) {
                case '?':
                case 'h':
                    _showVersion = true;
                    _showHelp = true;
                    break;

                case 'v':
                    _showVersion = true;
                    break;

                case 'V':
                    _showVersion = true;
                    _showConfig = true;
                    break;

                case 't':
                    _testConfig = true;
                    break;
                
                case 'q':
                    _quitMode = true;
                    break;

                case 'p':
                    if (*p) {
                        _prefix = p;
                        goto next;
                    }

                    if (argv[++i]) {
                        _prefix = argv[i];
                    }

                    Debug::printInfo("option \"-p\" required directory name");
                    _parseStatus = false;
                    return ;

                case 'c':
                    if (*p) {
                        _conf_file = p;
                        goto next;
                    }

                    if (argv[++i]) {
                        _conf_file = argv[i];
                        goto next;
                    }
                    Debug::printInfo("option \"-c\" requires file name");
                    _parseStatus = false;
                    return ;

                case 'g':
                    if (*p) {
                        _conf_param = p;
                        goto next;
                    }

                    if (argv[++i]) {
                        _conf_param = argv[i];
                        goto next;
                    }
                    Debug::printInfo("option \"-g\" requires param");
                    _parseStatus = false;
                    return ;

                case 's':
                    if (*p) {
                        _signal = p;
                    } else {
                        Debug::printInfo("option \"-s\" requires pram");
                        _parseStatus = false;
                        return ;
                    }

                    if (strcmp(_signal,"stop") == 0 
                        || strcmp(_signal,"quit") == 0
                        || strcmp(_signal,"reopen") == 0
                        || strcmp(_signal,"reload") == 0) 
                    {
                        _process = true;
                        goto next;
                    }

                    Debug::printInfo("invalid option \"-s\" xxx");
                    _parseStatus = false;
                    return ;
                default:
                    Debug::printInfo("invalid option ");
            }
        }
        next:
            continue;
    }
    _parseStatus = true;

    if (_showVersion || _showHelp || _showConfig || _showConfig)
         _isExit = true;
    else 
        _isExit = false;
}

inline bool optionProcess::getParseStatus() const {
    return _parseStatus;
}

inline bool optionProcess::isExit() const {
    return _isExit;
}

bool optionProcess::runOptions() {
    //根据解析结果执行相应的命令
    if (_showVersion) Debug::printInfo("high_yds version: " HIGH_VERSION);

    if (_showHelp) 
        Debug::printInfo(
            "Usage: high_yds [-?hvVtq] [-s ssignal] [-c filename]"
            "[-p prefix] [-g directorives] \n\n"
            "Options:\n"
            " -?,-h Show this help message\n"
            "-v:            Show version and exit\n"
            "-V:            Show the version and configure options then exit\n"
            "-t:            test configurer and exit\n"
            "-q:            test suppress non-error messages "
                            "during configure testing\n"
            "-s signal:     send signal to a master process: "
                            "stop, quit, reopen, reload\n"
            "-p prefix:     set prefix path(default none)\n"
            "-c filename:   set configuration file (default: "...")\n"
            "-g directives: set global directives out of configuration "
                                   "file\n\n"
        );

       if (_showConfig) {
           Debug::printInfo("configure parameter: (暂时省略)...");
           //打印配置信息...
       }

       if (_testConfig) {
           //do sth and returned
           return 0;
       }
}