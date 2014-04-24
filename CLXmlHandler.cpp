#include "CLXmlHandler.h"

CLXmlHandler::CLXmlHandler():doc(NULL){
}

CLXmlHandler::~CLXmlHandler(){
    if( NULL != doc ){
        xmlFreeDoc( doc );
    }
}

CLStatus CLXmlHandler::xmlFileLoad(const char* fileName){
    xmlNodePtr cur;
    doc = xmlReadFile(fileName,"utf-8",XML_PARSE_NOBLANKS);
    if( NULL == doc){
        CLLogger::writeLogMessage("CLXmlHandler::open xml file error!\n",errno);
        return CLStatus( FAILED , errno );
    }
    
    cur = xmlDocGetRootElement(doc);
    if(NULL == cur){
        CLLogger::writeLogMessage("CLXmlHandler::can't open root!\n",errno);
        return CLStatus( FAILED , errno);
    }
    
    cur = cur->xmlChildrenNode;
    while( NULL!= cur){
         xmlChar* xmlValue = xmlNodeGetContent( cur );

        string stringKey( (const char*)cur->name );
        string stringValue( (const char*)xmlValue );

        value[ stringKey ] = stringValue;
        cur = cur->next;

        //free xmlChar
        xmlFree(xmlValue);
    }

    return CLStatus( SUCCESSFUL,errno );
}

string& CLXmlHandler::getNodeValueByKey( string& key ){
        return value[ key ];
}

