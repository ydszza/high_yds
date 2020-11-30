#include "high_epoll_module.h"

highEpollAction::highEpollAction() : highEventAction(std::string("epoll action")) {
    _epollFd = epoll_create(1024);
    _events.resize(128);
}

highEpollAction::~highEpollAction() {
    close(_epollFd);
}

bool highEpollAction::addEvent(int fd, eventMode mode) {
    if (fd < 0) {
        Debug::printInfo("invalid fd");
        return false;
    }

    struct epoll_event ev;
    bzero(&ev, sizeof(ev));
    if (mode & EVENT_WRITE) ev.events |= EPOLLIN;
    if (mode & EVENT_READ) ev.events |= EPOLLOUT;
    ev.data.fd = fd;
    if (epoll_ctl(_epollFd, EPOLL_CTL_ADD, fd, &ev) < 0) {
        Debug::printError("epoll_ctl add");
        return false;
    }

    return true;
}

bool highEpollAction::delEvent(int fd, eventMode mode) {
    if (fd < 0) {
        Debug::printInfo("invalid fd");
        return false;
    }

    struct epoll_event ev;
    bzero(&ev, sizeof(ev));
    if (mode & EVENT_WRITE) ev.events |= EPOLLIN;
    if (mode & EVENT_READ) ev.events |= EPOLLOUT;
    ev.data.fd = fd;
    if (epoll_ctl(_epollFd, EPOLL_CTL_DEL, fd, &ev) < 0) {
        Debug::printError("epoll_ctl delete");
        return false;
    }

    return true;
}

bool highEpollAction::changeEvent(int fd, eventMode mode) {
    if (fd < 0) {
        Debug::printInfo("invalid fd");
        return false;
    }

    struct epoll_event ev;
    bzero(&ev, sizeof(ev));
    if (mode & EVENT_WRITE) ev.events |= EPOLLIN;
    if (mode & EVENT_READ) ev.events |= EPOLLOUT;
    ev.data.fd = fd;
    if (epoll_ctl(_epollFd, EPOLL_CTL_DEL, fd, &ev) < 0) {
        Debug::printError("epoll_ctl change");
        return false;
    }

    return true;
} 

bool highEpollAction::processEvent(unsigned long timer) {
    struct timeval tv, *tp;
    if (timer == -1) {
        tp = NULL; 
    } else {
        tv.tv_sec = (long) (timer / 1000);
        tv.tv_usec = (long) ((timer % 1000) * 1000);
        tp = &tv;
    }

    int ready = epoll_wait (_epollFd, &_events[0], _events.size(), timer);

    if (ready < 0) {
        Debug::printInfo("epoll failed");
        return false;
    }
    if (ready == 0) {
        Debug::printInfo("epoll returned no events");
        return false;
    }

    for (int i = 0; i < _events.size(); ++i) {
        bool isFounded = false;
        //可读事件
        if (_events[i].events & EPOLLIN) {
            isFounded = true;
            Debug::printInfo("epoll read events");
        }
        else if (_events[i].events & EPOLLOUT) {
            isFounded = true;
            Debug::printInfo("epoll write events");
        }
        if (isFounded) {
            //设置读写标志以及对应的回调函数
        }
    }
    return true;
}