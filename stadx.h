/*
 * =====================================================================================
 *
 *       Filename:  stadx.h
 *
 *    Description:  common head file
 *
 *        Version:  1.0
 *        Created:  10/20/13 21:25:07
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  (wj), 
 *        Company:  NDSL
 *
 * =====================================================================================
 */

#ifndef STADX_H
#define STADX_H
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <cstring>
#include <cstdio>

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/epoll.h>
#include <signal.h>
#define oops(m,n){perror(m);exit(n);}
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

using namespace std;

/*struct initialParameter{
	xmlChar* webServerIp;
	xmlChar* webServerPort;
	xmlChar* dbhost;
	xmlChar* dbuser;
	xmlChar* dbpasswd;
	xmlChar* dbname;
	xmlChar* crawlerId;
	xmlChar* localIp;	
};*/

#endif

