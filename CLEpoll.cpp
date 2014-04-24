#include "CLEpoll.h"

//initial single epollObj
CLEpoll* CLEpoll::epollObj = NULL;

CLEpoll::CLEpoll():
    epollFd(-1),epollEvents(NULL){
}

CLEpoll::~CLEpoll(){
    if(epollEvents != NULL){
        delete[] epollEvents;
        epollEvents = NULL;
    }
}

int CLEpoll::getEpollFd()const{
    return epollFd;
}

CLStatus CLEpoll::initialize(int eventSizeParam){
    eventSize = eventSizeParam;
    epollFd = epoll_create( eventSize );

    if(epollFd < 0){
        return CLStatus(FAILED,errno);
    }
    
    epollEvents = new epoll_event[eventSize];
    memset(epollEvents , 0 , sizeof(epoll_event)*eventSize);
    return CLStatus( SUCCESSFUL , errno );
}

CLStatus CLEpoll::doEvent(CLAgent *ptr,int fd,int op,unsigned int event){
    struct epoll_event ev;
    memset( &ev , 0 , sizeof( epoll_event ) );
    ev.events = event;
    ev.data.ptr = ptr;
    if( epoll_ctl(epollFd, op, fd, &ev) < 0)
        return CLStatus(FAILED,errno);
    
    return CLStatus( SUCCESSFUL , errno );
}

CLEpoll* CLEpoll::getInstance(){
    if(epollObj == NULL){
        epollObj = new CLEpoll();
        return epollObj;
    }

    else
        return epollObj;
}

void CLEpoll::run(){
    int ndfs = 0;
    CLAgent *agent = NULL;

    while( true ){
        ndfs = epoll_wait( epollFd, epollEvents, eventSize , EPOLL_TIME_OUT_LEN);
        if( ndfs < 0 ){
            if( EINTR == errno )
                continue;

            else{
                CLLogger::writeLogMessage("CLEpoll::epoll_wait error!\n",errno);
                exit(FAILED);
            }
        }
         
        for( int i = 0 ; i < ndfs ; i++ ){
            agent = static_cast< CLAgent* >( epollEvents[i].data.ptr );
            if( NULL == agent ){
                CLLogger::writeLogMessage("CLEpoll:agent == NULL!\n",FAILED);
                continue;
            }

            if(epollEvents[i].events & EPOLLOUT){
                if( !(agent -> sendData()).isSuccess() ){
                    CLLogger::writeLogMessage("CLEpoll:agent send error!\n",errno);
                }
            }

            if(epollEvents[i].events & EPOLLIN){
                if( !(agent -> receiveData()).isSuccess() ){
                    CLLogger::writeLogMessage("CLEpoll:agent recev error!\n",errno);
                }
            }
        }
    }
}

