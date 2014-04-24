#include "CLJsonHandler.h"

bool CLJsonHandler::loadJsonString(char *str){
    if( !reader.parse(str,value) ){
        CLLogger::writeLogMessage("CLJsonHandler:loadJsonString error!\n",errno);
        return false;
    }

    return true;
}

string CLJsonHandler::getValueByKey(const char* key){
    return value[key].asString();
}


