#ifndef CLJOBAGENT_H_
#define CLJOBAGENT_H_
#include "stadx.h"
#include "CLAgent.h"
#include "CLJsonHandler.h"
#include "Error.h"

const int BUFF_SIZE = 100;

class CLJobAgent:public CLAgent{
private:
    int jobFd;
    CLJsonHandler jsonHandler;

private:
    int readLine(char *buf, size_t maxlen);
    void reportToPortal( void );

public:
    CLJobAgent(int);
    virtual ~CLJobAgent();

public:
    CLStatus receiveData();
    CLStatus sendData();
};

#endif

