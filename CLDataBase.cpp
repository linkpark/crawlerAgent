#include "CLDataBase.h"

CLDataBase::CLDataBase(const char *host,const char *username,
					const char *password,const char *database):
					hostName(host),userName(username),
					passWord(password),dataBase(database)
					{

	mysql_init(&mysqlObj);

}

CLDataBase::~CLDataBase(){
	mysql_close(&mysqlObj);
}

bool CLDataBase::mysqlConnect(){
	MYSQL *result;
 	result = mysql_real_connect(&mysqlObj,hostName.c_str(),userName.c_str(),
		passWord.c_str(),dataBase.c_str(),0,NULL,0);

	if(result == NULL){
		printf("dataBase connect error %s\n",mysql_error(&mysqlObj));
		return false;
	}
	else{
        mysql_character_set_name(&mysqlObj);
        
        return true;
    }
}

bool CLDataBase::mysqlQuery(char *query){
	int ret = 1;

	while(ret != 0){
		ret = mysql_query(&mysqlObj,query);

		//if the connect is lost then re connect
		if(CR_SERVER_LOST == mysql_errno(&mysqlObj) || CR_SERVER_GONE_ERROR == mysql_errno(&mysqlObj)){
			if(!mysqlConnect()){
				perror("mysql reconnect errror!\n");
				return false;
			}
			continue;
		}
		else if(ret != 0){
			printf("mysql query error! %d\n",mysql_errno(&mysqlObj));
			return false;
		}
	}
	return true;
}

bool CLDataBase:: mysqlSelect(char *query,MYSQL_RES **result){
	int ret = 1;	
	while(ret != 0){
		ret = mysql_query(&mysqlObj,query);

		//if the connect is lost then re connect
		if(CR_SERVER_LOST == mysql_errno(&mysqlObj) || CR_SERVER_GONE_ERROR == mysql_errno(&mysqlObj)){
			if(!mysqlConnect()){
				perror("mysql reconnect errror!\n");
				return false;
			}
			continue;
		}
		else if(ret != 0){
			printf("mysql query error! %d\n",mysql_errno(&mysqlObj));
			return false;
		}
	}
 	
	*result = mysql_use_result(&mysqlObj);
	if( (*result) == NULL){
		cout << mysql_errno(&mysqlObj) << endl;
		cout << mysql_error(&mysqlObj) << endl;
		return false;
	}

	else
		return true;
}



