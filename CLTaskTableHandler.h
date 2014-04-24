#ifndef CLTASKTABLEHANDLER_H
#define CLTASKTABLEHANDLER_H
#include "CLDataBase.h"

class CLTaskTableHandler{
private:
	string id;
	string entryUrl;
	string eBussinessName;
	string goodsCategoryName;
	string pageNumber;
	string state;
	string createTime;
	string finishTime;

	CLDataBase *dataBase;

public:
	CLTaskTableHandler(CLDataBase *dataBaseObj);
	bool selectById(string &idParam);
	bool updateStateById(string &idParam,string &stateParam);

public:
	//a series of get and set function;
	string getIdResult();
	string getEntryUrlResult();
	string getEBussinessName();
	string getGoodsCategoryName();
	string getPageNumber();
	string getState();
	string getCreateTime();
	string getFinishTime();

	bool setStateById(string& , string&);
};

#endif
