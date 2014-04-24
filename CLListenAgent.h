#ifndef CLLISTENAGENT_H_
#define CLLISTENAGENT_H_
#include "CLAgent.h"
#include "CLJobAgent.h"
#include "CLEpoll.h"

const int LISTEN_NUM = 1024;
class CLJobAgent;
class CLListenAgent:public CLAgent{
private:
    int listenFd;
    struct sockaddr_in serverAddr;
    struct sockaddr_in clientAddr;

public:
    CLListenAgent(int port):listenFd(-1){
        memset(&serverAddr,0,sizeof(struct sockaddr_in));
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
        serverAddr.sin_port = htons(port);
    }

    virtual ~CLListenAgent(){
        if(listenFd != -1){
            close(listenFd);
        }
    }

public:
    virtual CLStatus init(void);
    virtual CLStatus receiveData();
    virtual CLStatus sendData();
    int getListenFd()const;
};

#endif 
