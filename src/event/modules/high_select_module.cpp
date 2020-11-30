#include "high_select_module.h"

highSelectAction::highSelectAction() : highEventAction(std::string("select action")) {
    FD_ZERO(&_readFds);
    FD_ZERO(&_writeFds);
    _maxFd = -1;
}

highSelectAction::~highSelectAction() {

}

/**
 * select add event
*/
bool highSelectAction::addEvent(int fd, eventMode mode) {
    if (fd < 0) {
        Debug::printInfo("invaild fd");
        return false;
    }

    if (mode & EVENT_READ) FD_SET(fd, &_readFds);
    if (mode & EVENT_WRITE) FD_SET(fd, &_writeFds);

    if (fd > _maxFd) _maxFd = fd;

    return true;
}

/**
 * select delete event
*/
bool highSelectAction::delEvent(int fd, eventMode mode) {
    if (fd < 0) {
        Debug::printInfo("invaild fd");
        return false;
    }

    if (mode & EVENT_READ) FD_CLR(fd, &_readFds);
    if (mode & EVENT_WRITE) FD_CLR(fd, &_writeFds);

    if (fd > _maxFd) _maxFd = fd;

    return true;
}

/**
 * select change event
*/
bool highSelectAction::changeEvent(int fd, eventMode mode) {
    if (fd < 0) {
        Debug::printInfo("invaild fd");
        return false;
    }

    if (mode & EVENT_READ) delEvent(fd, EVENT_WRITE);
    if (mode & EVENT_WRITE) delEvent(fd, EVENT_READ);
    addEvent(fd, mode);

    return true;
}

/**
 * select wait event
*/
bool highSelectAction::processEvent(unsigned long timer) {
    struct timeval tv, *tp;
    if (timer != -1) {
        tv.tv_sec = (long) (timer / 1000);
        tv.tv_usec = (long) ((timer % 1000) * 1000);
        tp = &tv;
    } else {
        tp = NULL;
    }

    _workReadFds = _readFds;
    _workWriteFds = _writeFds;

    int ready = select(_maxFd+1, &_workReadFds, &_workWriteFds, NULL, tp);
    if (ready < 0) {
        Debug::printInfo("select failed");
        return false;
    }
    if (ready == 0) {
        Debug::printInfo("select() returned no event");
    }
    
    //有事件返回的情况
    for (int i = 0; i < events.size(); ++i) {
        //遍历保存的连接查找有读可写事件
        ev = events[i];
        c = ev->data;
        bool isFounded = false;

        //可写事件检测
        if (ev->write) {
            if (FD_ISSET(c->fd, &_writeFds)) {
                isFounded = true;
                Debug::printInfo("select write fd");
            }
        }
        //可读事件检测
        else if (ev->read) {
            if (FD_ISSET(c->fd, &_readFds)) {
                isFounded = true;
                Debug::printInfo("select read event");
            }
        }
        //检测到的处理
        if (isFounded) {
            ev->read = true;
            //添加回调方法在此
        }
    }

    return true;
}