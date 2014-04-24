#include "CLListenAgent.h"

//initial listen socket
CLStatus CLListenAgent::init(){
    listenFd = socket(AF_INET,SOCK_STREAM,0);
    if(listenFd < 0){
        CLLogger::writeLogMessage("CLListen::init socket error!\n",errno);
        return CLStatus(FAILED,errno);
    }

    if( bind( listenFd , (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0 ){
        CLLogger::writeLogMessage("CLListen::init bind error!\n ",errno);
        return CLStatus(FAILED,errno);
    }

    if( listen( listenFd, LISTEN_NUM) < 0 ){
        CLLogger::writeLogMessage( "CLListen::init listen error!\n",errno );
        return CLStatus( FAILED,errno );
    }
    
    return CLStatus( SUCCESSFUL,0 );
}

CLStatus CLListenAgent::receiveData(){
    socklen_t clientLen;
    int clientFd;

    clientFd = accept( listenFd, (struct sockaddr*)&clientAddr, &clientLen );
    if(clientFd < 0){
        CLLogger::writeLogMessage( "CLListen:: receiveData accept error!\n",errno );
        return CLStatus( FAILED,errno );
    }
    
    CLAgent *jobAgent = new CLJobAgent(clientFd);
    CLEpoll::getInstance() -> doEvent(jobAgent,clientFd,EPOLL_CTL_ADD,EPOLLIN);

    return CLStatus( SUCCESSFUL,0 );
}

CLStatus CLListenAgent::sendData(){
}

int CLListenAgent::getListenFd()const{
    return listenFd;
}
