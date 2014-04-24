#ifndef CLXMLHANDLER_H_
#define CLXMLHANDLER_H_
#include "stadx.h"
#include "CLLogger.h"
#include "Error.h"
#include <libxml/parser.h>
class CLXmlHandler{
private:
    xmlDocPtr doc;
    map< string, string > value;

public:
    CLXmlHandler();
    ~CLXmlHandler();

    CLStatus xmlFileLoad(const char* fileName);
    string& getNodeValueByKey(string& key);
};

#endif 
