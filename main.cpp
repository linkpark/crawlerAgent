#include "CLXmlHandler.h"
#include "CLCrawlerAgent.h"
#include "CLEpoll.h"
#include "CLDataBase.h"
#include "Error.h"
#include "CLListenAgent.h"

int main(){
    CLXmlHandler xmlHandler;
    xmlHandler.xmlFileLoad("AgentConf.xml");
    CLDataBase *dataBase;

    string webServerIp("webServerIp");
    string webServerPort("webServerPort");
    string crawlerId("crawlerId");
    string localIp("localIp");
    string dbhost("dbhost");
    string dbuser("dbuser");
    string dbpasswd("dbpasswd");
    string dbname("dbname");
    string listenPort("listenPort");

    CLEpoll::getInstance()->initialize(256);
    dataBase = new CLDataBase(
                xmlHandler.getNodeValueByKey(dbhost).c_str(),
                xmlHandler.getNodeValueByKey(dbuser).c_str(),
                xmlHandler.getNodeValueByKey(dbpasswd).c_str(),
                xmlHandler.getNodeValueByKey(dbname).c_str()
            );
    if(!dataBase->mysqlConnect()){
        cout << "connect mysql error!" <<endl;
        return FAILED;
    }

    cout << "connect dataBase successful" <<endl;

    CLCrawlerAgent *crawler = new CLCrawlerAgent(
            xmlHandler.getNodeValueByKey(crawlerId),
            xmlHandler.getNodeValueByKey(localIp),
            dataBase
            );

    //初始化任务监听接口
    int port = atoi( xmlHandler.getNodeValueByKey(listenPort).c_str() );
    CLListenAgent *listenAgent = new CLListenAgent(port);
    listenAgent->init();
    CLEpoll::getInstance()->doEvent(listenAgent,
            listenAgent->getListenFd(),
            EPOLL_CTL_ADD,
            EPOLLIN);
    cout << "listen successful" <<endl;
    //初始化爬虫处理接口
    CLStatus s = crawler->initial(
            xmlHandler.getNodeValueByKey(webServerIp),
            xmlHandler.getNodeValueByKey(webServerPort));

    if(!s.isSuccess()){
        cout << "connect webServer error!" << endl;
    }

    cout << "connect webServer successful" <<endl;
    CLEpoll::getInstance()->doEvent( crawler,
            crawler->getConnectFd(),
            EPOLL_CTL_ADD,
            EPOLLIN);

    CLEpoll::getInstance()->run();
    
    return 0;
}

