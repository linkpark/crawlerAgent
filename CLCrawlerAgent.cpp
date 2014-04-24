#include "CLCrawlerAgent.h"

CLCrawlerAgent::CLCrawlerAgent(string &id,string &ip,CLDataBase *baseObj):
    connectFd(-1),crawlerId(id),localIp(ip){
    memset( &webServerAddr, 0 , sizeof(webServerAddr) );
    taskTableHandler = new CLTaskTableHandler( baseObj );
}

CLCrawlerAgent::~CLCrawlerAgent(){
    if(connectFd > 0){
        close(connectFd);
    }

    delete taskTableHandler;
    cout <<"crawler agent has been delete" <<endl;
}

CLStatus CLCrawlerAgent::initial( string& ip, string& port ){
    int webServerPort = atoi( port.c_str() ); 
    char jsonBuf[MAXLINE];

    webServerAddr.sin_family = AF_INET;                             
    webServerAddr.sin_port = htons(webServerPort);
    if(inet_pton(AF_INET,ip.c_str(),&webServerAddr.sin_addr) < 0){
        CLLogger::writeLogMessage("CLCrawlerAgent: initial error inet_pton\n",errno);
        return CLStatus(FAILED,errno);
    }
    
    connectFd = socket(AF_INET,SOCK_STREAM,0);
    if(connectFd < 0){
        CLLogger::writeLogMessage("CLCrawlerAgent: initial error,socket error!\n",errno);
        return CLStatus(FAILED,errno);
    }

    if(connect(connectFd,(struct sockaddr*)&webServerAddr,sizeof(webServerAddr)) < 0){
        CLLogger::writeLogMessage("CLCrawlerAgent: initial error,connect error!\n",errno);
        return CLStatus(FAILED,errno);
    }
    
     memset(jsonBuf,'\0',MAXLINE);
     sprintf(jsonBuf,"{\"type\":\"CrawlerControlServerMsg\",\"crawlerConrolServerMsg\":{\"id\":%s,\"ip\":\"%s\"}}\n",crawlerId.c_str(),localIp.c_str());
    
     int r = write(connectFd , jsonBuf, strlen(jsonBuf)+1 );
     if( r < 0){
        CLLogger::writeLogMessage("CLCrawlerAgent: initial error, write error!\n",errno);
        return CLStatus(FAILED,errno);
     }

     return CLStatus(SUCCESSFUL,errno);
}

int CLCrawlerAgent::getConnectFd() const{
    return connectFd;
}

CLStatus CLCrawlerAgent::receiveData(){
    char serverJsonBuf[ MAXLINE ];  
    int r = read(connectFd, serverJsonBuf , MAXLINE);
    if(r < 0){
        if( EINTR == errno)
            return CLStatus(SUCCESSFUL,errno);
        else
            return CLStatus(FAILED,errno);
    }

    else if(r == 0){
        CLLogger::writeLogMessage("CLCrawelrAgent: receviveData,server close!\n",errno);
        delete this;

        cout << "server has closed" <<endl;
        return CLStatus(SUCCESSFUL,errno);
    }

    else{
        cout << serverJsonBuf<<endl;

        if( !jsonHandler.loadJsonString(serverJsonBuf) ){
            CLLogger::writeLogMessage("CLCrawlerAgent:jsonHandler error!",errno);
            return CLStatus(FAILED,errno);
        } 
    }
    
    runCrawlerJob( jsonHandler.getValueByKey("taskId") );

    return CLStatus(SUCCESSFUL,errno);
}   

CLStatus CLCrawlerAgent::sendData(){
    
}

void CLCrawlerAgent::runCrawlerJob(string id){
    //taskTableHandler->selectById(id);

    //cout << taskTableHandler->getEBussinessName() <<endl;
    //cout << taskTableHandler->getCreateTime() <<endl;
    
    runJdJob();
    if (signal( SIGCHLD, sigChildHandler) == SIG_ERR){
        perror("signal error\n");
    }
}

void CLCrawlerAgent::sigChildHandler(int sig){
    pid_t pid;
    int stat;

    while( (pid = waitpid(-1 , &stat, WNOHANG)) > 0){
        cout << "child " << pid << " terminated" <<endl;
    }
    return;
}

void CLCrawlerAgent::runJdJob(){
    if(fork() == 0){
//        system()
    }
}

