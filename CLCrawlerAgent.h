#ifndef CLCRAWLERAGENT_H_
#define CLCRAWLERAGENT_H_
#include "CLAgent.h"
#include "CLEpoll.h"
#include "CLJsonHandler.h"
#include "CLTaskTableHandler.h"

const int MAXLINE = 100;
class CLCrawlerAgent:public CLAgent{
private:
    int connectFd;
    struct sockaddr_in webServerAddr;

    string crawlerId;
    string localIp;

    CLJsonHandler jsonHandler;
    CLTaskTableHandler *taskTableHandler;

public:
    CLCrawlerAgent(string&, string&, CLDataBase *baseObj);
    virtual ~CLCrawlerAgent();
    static void sigChildHandler( int );
    void runJdJob();

public:
    int getConnectFd() const;
    CLStatus initial(string& ip, string& port);
    CLStatus receiveData();
    CLStatus sendData();
    void runCrawlerJob( string );

};

#endif
