#ifndef __HIGH_EPOLL_MODULE_H
#define __HIGH_EPOLL_MODULE_H

#include <sys/epoll.h>
#include <strings.h>
#include <time.h>
#include <unistd.h>
#include <vector>
#include "high_event_module.h"
#include "../debug/high_debug.h"


class highEpollAction : public highEventAction {
public:
    highEpollAction();
    virtual ~highEpollAction();

    virtual bool addEvent(int fd, eventMode mode);
    virtual bool delEvent(int fd, eventMode mode);
    virtual bool changeEvent(int fd, eventMode mode);
    virtual bool processEvent(unsigned long timer);

private:
    int _epollFd;
    std::vector<struct epoll_event> _events;
};

#endif // !__HIGH_EPOLL_MODULE_H