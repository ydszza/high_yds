#include "high_configure.h"

Configuration::Configuration() {
    //读取配置文件，解析配置
    std::ifstream confFile("../../configure", std::ios::in);
    if (!confFile.is_open()) {
        Debug::printInfo("configure file open failed");
        //std::cout << "failed" << std::endl;
        _isValid = false;
        return;
    }
    std::string conf;
    while (!confFile.eof()) {
        getline(confFile, conf);
        std::cout << conf << std::endl;
    }
    _isValid = true;
    confFile.close();
}

Configuration::~Configuration() {
    //
}

inline bool Configuration::isValid() const {
    return _isValid;
}

inline int Configuration::getPort() const {
    return _port;
}

// int main() {
//     Configuration configure;
//     return 0;
// }