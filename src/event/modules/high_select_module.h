#ifndef __HIGH_SELECT_MODULE_H_
#define __HIGH_SELECT_MODULE_H_

#include <sys/select.h>
#include <strings.h>
#include <time.h>
#include "high_event_module.h"
#include "../debug/high_debug.h"

class highSelectAction : public highEventAction {
public:
    highSelectAction();
    virtual ~highSelectAction();

    virtual bool addEvent(int fd, eventMode mode);
    virtual bool delEvent(int fd, eventMode mode);
    virtual bool changeEvent(int fd, eventMode mode);
    virtual bool processEvent(unsigned long timer);

private:
    fd_set _readFds;
    fd_set _workReadFds;
    fd_set _writeFds;
    fd_set _workWriteFds;
    int _maxFd;
};

#endif // !__HIGH_SELECT_MODULE_H_