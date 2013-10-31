//This class converts between managed variables to unmanaged variables for manipulation 
//by the logic class.
//Conversion from different format is available.

#ifndef DATACONVERTER_H
#define DATACONVERTER_H

#include <msclr/marshal_cppstd.h>
#include <string>
#include "Task.h"

using namespace System;
using namespace Runtime::InteropServices;
using namespace std;

class DataConverter {
private:
	static const int ZERO = 0;
	static const int YEAR_LENGTH = 4;
	static const int DOUBLE_DIGIT = 10;
	static const int HALF_A_DAY = 12;
	static const int FULL_DAY = 24;

public:
	std::string sysToStdString(System::String^ userEnteredInBox);
	String^ stdToSysString(std::string toBePrinted);
	String^ intToString(int number);
	String^ dateToString(TASK_DATE dayAdded);
	String^ timeToString(TIME timeAdded);
	DateTime sysStringToDateTime(String^ currentRowDate);
	DateTime sysStringToDateTimeWithMinutes(String^ currentRowTime);
	int sysStringToInt(String^ dayMonthYear);
	int militaryToStandardTime(int hour);
	int standardToMilitaryTime(String^ currentRowTime, int hour);

private:
	String^ appendForeZeroToMinute(int minute);
	bool checkDayStatus(int hour);
	void setTaskTime(String^& taskTime, String^ hour, String^ minute, String^ dayStat);
};

#endif