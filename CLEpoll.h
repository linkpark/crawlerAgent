#include "stadx.h"
#ifndef CLEPOLL_H_
#define CLEPOLL_H_
#include "CLAgent.h"
#include "Error.h"
//using single pattern
const int EPOLL_TIME_OUT_LEN = -1;
class CLEpoll{
private:
    int epollFd;
    int eventSize;
    struct epoll_event *epollEvents;

    static CLEpoll* epollObj;

private:
    CLEpoll();
    CLEpoll(const CLEpoll&);
    CLEpoll& operator=(CLEpoll&);

    virtual ~CLEpoll();
 
public:   
    int getEpollFd()const;
    CLStatus initialize( int );
    CLStatus doEvent( CLAgent* ptr, int fd, int op, unsigned int event); 
    void run( void );

public:
    static CLEpoll* getInstance();
};

#endif
