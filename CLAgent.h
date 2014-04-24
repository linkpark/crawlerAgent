#ifndef CLAGENT_H_
#define CLAGENT_H_
#include "stadx.h"
#include "CLLogger.h"

class CLAgent{
public:
    CLAgent(){}
    virtual ~CLAgent(){}

    virtual CLStatus receiveData() = 0;
    virtual CLStatus sendData() = 0;
};
#endif

