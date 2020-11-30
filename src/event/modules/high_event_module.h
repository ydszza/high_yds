#ifndef __HIGH_EVENT_MODULE_H_
#define __HIGH_EVENT_MODULE_H_

#include <string>


enum eventMode{
    EVENT_READ = 0x1,
    EVENT_WRITE = 0x2
};



class highEventAction {
public:
    highEventAction(const std::string& name) : _actionName(name) {}
    virtual ~highEventAction();

    virtual bool addEvent(int fd, eventMode mode) = 0;
    virtual bool delEvent(int fd, eventMode mode) = 0;
    virtual bool changeEvent(int fd, eventMode mode) = 0;
    virtual bool processEvent(unsigned long timer) = 0;
private:
    std::string _actionName;
};

#endif // !__HIGH_EVENT_MODULE_H_