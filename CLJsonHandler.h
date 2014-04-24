#ifndef CLJSONHANDLER_H_
#define CLJSONHANDLER_H_
#include "stadx.h"
#include <json/json.h>
#include "CLLogger.h"

class CLJsonHandler{
private:
    Json::Reader reader;
    Json::Value value;

public:
    bool loadJsonString(char *); 
    string getValueByKey(const char* key);
};

#endif
