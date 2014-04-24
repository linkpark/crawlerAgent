#include "CLTaskTableHandler.h"

CLTaskTableHandler:: CLTaskTableHandler(CLDataBase *dataBaseObj)
		:dataBase(dataBaseObj){
}

bool CLTaskTableHandler:: selectById(string &idParam){
	char query[100];
	MYSQL_RES *result = NULL;
	MYSQL_ROW row;
	
	sprintf(query,"select * from task where id='%s';",idParam.c_str());
	printf("%s\n",query);

	if(!dataBase->mysqlSelect(query,&result))
		return false;
			
	row = mysql_fetch_row(result);
	
	id = row[0];
	entryUrl = row[1];
	eBussinessName = row[2];
	goodsCategoryName = row[3];
	pageNumber = row[4];
	state = row[5];
	createTime = row[6];
	finishTime = row[7];
	
	return true;	
}

bool CLTaskTableHandler:: setStateById(string &idParam,string &stateParam){
    
}

string CLTaskTableHandler:: getIdResult(){
	return id;
}

string CLTaskTableHandler:: getEntryUrlResult(){
	return entryUrl;
}

string CLTaskTableHandler:: getEBussinessName(){
	return eBussinessName;
}

string CLTaskTableHandler:: getGoodsCategoryName(){
	return goodsCategoryName;
}

string CLTaskTableHandler:: getPageNumber(){
	return pageNumber;
}

string CLTaskTableHandler:: getState(){
	return state;
}

string CLTaskTableHandler:: getCreateTime(){
	return createTime;
}

string CLTaskTableHandler:: getFinishTime(){
	return finishTime;
}

