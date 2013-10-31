#include "stdafx.h"
#include "Exception.h"


Exception::Exception(UserFeedback feedback) {
	excepData.setFeedback(feedback);
}

DataFeedback Exception::getFeedback() {
	return excepData;
}

void Exception::setFeedback(UserFeedback feedback) {
	excepData.setFeedback(feedback);
}