#include "high_yds.h"



int main(int argc, char **argv) {
    //解析命令行参数
    optionProcess op(argc, argv);
    if (!op.getParseStatus()) return 1;
    //根据命令行参数执行指令
    op.runOptions();

    if (op.isExit()) return 1;

    //读取配置信息
    Configuration conf;
    if (!conf.isValid()) return 1;
    //根据配置信息配置服务

    //进入主程序去创建子进程
    //然后执行主程序循环体

    return 0;
}