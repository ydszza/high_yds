#ifndef __HIGH_POLL_MODULE_H_
#define __HIGH_POLL_MODULE_H_

#include <sys/poll.h>
#include <strings.h>
#include <time.h>
#include <vector>
#include "high_event_module.h"
#include "../debug/high_debug.h"


class highPollAction : public highEventAction {
public:
    highPollAction();
    virtual ~highPollAction();

    virtual bool addEvent(int fd, eventMode mode);
    virtual bool delEvent(int fd, eventMode mode);
    virtual bool changeEvent(int fd, eventMode mode);
    virtual bool processEvent(unsigned long timer);

private:
    std::vector<struct pollfd> events;
};

#endif // !__HIGH_POLL_MODULE_H_