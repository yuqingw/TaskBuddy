//	
//	NAME: class Exception
//	DESCRIPTION: This class holds the information that is in the form of
//	of DataFeedback class which is thrown for exception handling.
//	


#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "DataFeedback.h"

class Exception {

private:
	DataFeedback excepData;

public:

	Exception(UserFeedback feedback);

	DataFeedback getFeedback();
	void setFeedback(UserFeedback feedback);
};
#endif