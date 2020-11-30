#include "high_poll_module.h"

highPollAction::highPollAction() : highEventAction(std::string("poll action")) {

}

highPollAction::~highPollAction() {

}

bool highPollAction::addEvent(int fd, eventMode mode) {
    if (fd < 0) {
        Debug::printInfo("invalid fd");
        return false;
    }

    struct pollfd ev;
    bzero(&ev, sizeof(ev));
    ev.fd = fd;
    if (mode & EVENT_READ) ev.events | POLLRDNORM;
    if (mode & EVENT_WRITE) ev.events | POLLWRNORM;
    events.push_back(ev);

    return true;
}

bool highPollAction::delEvent(int fd, eventMode mode = EVENT_WRITE) {
    if (fd < 0) {
        Debug::printInfo("invalid fd");
        return false;
    }

    for (int i = 0; i < events.size(); ++i) {
        if (events[i].fd == fd) {
            std::swap(events[i], events[events.size()-1]);
            events.pop_back();
            return true;
        }
    }

    Debug::printInfo("not found fd");
    return false;
}

bool highPollAction::changeEvent(int fd, eventMode mode) {
    if (fd < 0) {
        Debug::printInfo("invalid fd");
        return false;
    }

    int i;
    for (i = 0; i < events.size(); ++i) {
        if (events[i].fd == fd) break;
    }
    if (i == events.size()) {
        Debug::printInfo("not find fd");
        return false;
    }

    if (mode & EVENT_READ) {
        events[i].events &= ~POLLWRNORM;
        events[i].events |= POLLRDNORM;
    }
    if (mode & EVENT_WRITE) {
        events[i].events &= ~POLLRDNORM;
        events[i].events |= POLLWRNORM;
    }

    return true;
}

bool highPollAction::processEvent(unsigned long timer) {
    struct timeval tv, *tp;
    if (timer == -1) {
        tp = NULL; 
    } else {
        tv.tv_sec = (long) (timer / 1000);
        tv.tv_usec = (long) ((timer % 1000) * 1000);
        tp = &tv;
    }

    int nready = poll(&events[0], events.size(), timer);
    if (nready < 0) {
        Debug::printInfo("poll failed");
        return false;
    }
    if (nready == 0) {
        Debug::printInfo("poll returnd no events");
        return false;
    }

    for (int i = 0; i < events.size(); ++i) {
        auto revent = events[i].revents;
        bool isFounded = false;
        //读事件
        if (revent & events[i].events & POLLRDNORM) {
            isFounded = true;
            Debug::printInfo("poll read event");
        }
        else if (revent & events[i].events & POLLWRNORM) {
            isFounded = true;
            Debug::printInfo("poll write event");
        }
        if (isFounded) {
            //设置读写事件标志位并且设置回调函数
        }
    }
    return true;
}