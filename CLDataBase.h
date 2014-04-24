#ifndef CLDATABASE_H
#define CLDATABASE_H
#include "stadx.h"
#include <mysql/mysql.h>
#include <mysql/errmsg.h>
class CLDataBase{
	private:
		MYSQL mysqlObj;
		string userName;
		string passWord;
		string dataBase;
		string hostName;

	public:
		CLDataBase(const char *host,const char *username,
				const char *password,const char *database);
		~CLDataBase();

		bool mysqlConnect();
		bool mysqlQuery(char *query);
		bool mysqlSelect(char *query,MYSQL_RES **result);
};
#endif 
