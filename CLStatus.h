#ifndef CLSTATUS_H_
#define CLSTATUS_H_
#include "stadx.h"
class CLStatus{
	private:
		long returnCode;
		long errorCode;

	public:
		CLStatus(long returnCodeParam , long errorCodeParam);
		CLStatus(const CLStatus &s);
		virtual ~CLStatus();

		const long& constReturnCode;
		const long& constErrorCode;		                           
	public:
		bool isSuccess();
};

#endif

