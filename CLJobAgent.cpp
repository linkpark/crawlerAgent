#include "CLJobAgent.h"

CLJobAgent::CLJobAgent(int fd):jobFd(fd){
}

CLJobAgent::~CLJobAgent(){
    if(jobFd > 0)
        close(jobFd);
}

CLStatus CLJobAgent::receiveData(){
    int n;
    char buf[BUFF_SIZE];
    memset(buf,0,BUFF_SIZE);

    n = readLine(buf,BUFF_SIZE-1);
    if( n < 0){
        CLLogger::writeLogMessage("CLJobAgent::read error!=n",errno);
        return CLStatus(FAILED,errno);
    }

    if(n == 0){
        cout << "job has done";
        delete this;
        return CLStatus(SUCCESSFUL,0);
    }

    if( !jsonHandler.loadJsonString( buf ) ){
        CLLogger::writeLogMessage("CLJobAgent:jsonhadler load error!\n",errno);
        return CLStatus(FAILED,errno);
    }

    //向portal汇报任务状态
    reportToPortal();
    
    return CLStatus(SUCCESSFUL,0);
}

CLStatus CLJobAgent::sendData(){    
}

int CLJobAgent::readLine(char *buf, size_t maxlen){
    ssize_t n,i;
    char c;

    for( i = 1; i < maxlen ; i++){
        if( (n = read(jobFd,&c,1)) == 1 ){
            *buf++ = c;

            if(c == '\n')
                break;
        }else if(n == 0){
            *buf = 0;

            return (i - 1);
        }else{
            if(errno == EINTR){
                i--;
                continue;
            }

            return -1;
        }
    }

    return i;
}

void CLJobAgent::reportToPortal(){
    if (jsonHandler.getValueByKey("crawlerPercentage") != ""){
        cout << "report crawler job " <<endl;
        cout << "job percentage:" ;
        cout << jsonHandler.getValueByKey("crawlerPercentage") <<endl;
    }

    else if(jsonHandler.getValueByKey("storePercentage") != ""){
        cout << "report store job" << endl;
        cout << "job percentage:";
        cout << jsonHandler.getValueByKey("storePercentage") <<endl;
    }
    else{
        cout << "error report" << endl;
    }
}


