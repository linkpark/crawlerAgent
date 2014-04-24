#include "CLStatus.h"

CLStatus::CLStatus(long returnCodeParam, long errorCodeParam):
	constReturnCode(returnCode),constErrorCode(errorCode){
	
	returnCode = returnCodeParam;
	errorCode = errorCodeParam;
}

CLStatus::CLStatus(const CLStatus& s):
	constReturnCode(returnCode),constErrorCode(errorCode){
	returnCode = s.returnCode;
	errorCode = s.errorCode;
}

CLStatus::~CLStatus(){
}

bool CLStatus::isSuccess(){
	if(returnCode >= 0)
		return true;
	else
		return false;
}

