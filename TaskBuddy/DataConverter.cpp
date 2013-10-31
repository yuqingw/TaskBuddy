#include "stdafx.h"
#include "DataConverter.h"

//This method converts System::String^ to standard string
std::string DataConverter::sysToStdString(System::String^ userEnteredInBox) {
	const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(userEnteredInBox)).ToPointer();
	std::string userEntered = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));

	return userEntered;
}

//This method converts standard string to System::String^
String^ DataConverter::stdToSysString(std::string toBePrinted) {
	return gcnew String(toBePrinted.c_str());
}

//This method converts integer to System::String^
String^ DataConverter::intToString(int number) {
	return Convert::ToString(number);
}

//This method converts the date structure to System::String^
String^ DataConverter::dateToString(TASK_DATE dayAdded) {
	String^ day = intToString(dayAdded.day);
	String^ month = intToString(dayAdded.month);
	String^ year = intToString(dayAdded.year);
	String^ taskDate = day + "/" + month + "/" + year;

	return taskDate;
}

//This method converts the time structure to System::String^
String^ DataConverter::timeToString(TIME timeAdded) {
	int standardHour = militaryToStandardTime(timeAdded.hour);
	String^ hour = intToString(standardHour);
	String^ minute = appendForeZeroToMinute(timeAdded.min);
	String^ dayStat = (checkDayStatus(timeAdded.hour)) ? "am" : "pm";
	String^ taskTime;
	
	/*if(hour == "0" && minute == "00") {
		taskTime = "";
	}else {
		taskTime = hour + ":" + minute + " " + dayStat;
	}*/
	setTaskTime(taskTime, hour, minute, dayStat);

	return taskTime;
}

//This method converts System::String^ to System::DateTime without time
DateTime DataConverter::sysStringToDateTime(String^ currentRowDate) {
	int firstSlashPosition = ZERO;
	int secondSlashPosition= ZERO;
	int monthLength = ZERO;
	bool isDayFound = false;
	bool isMonthFound = false;
	bool isYearFound = false;
	int day = ZERO;
	int month = ZERO;
	int year = ZERO;

	if(currentRowDate == "Today") {
		return DateTime::Today;
	}else {
		for(int i=0; i<currentRowDate->Length; i++) {
			if(!isDayFound && currentRowDate[i] == '/') {
				day = sysStringToInt(currentRowDate->Substring(ZERO, i));
				firstSlashPosition = i;
				isDayFound = true;
			}else if(!isMonthFound && currentRowDate[i] == '/') {
				monthLength = i - firstSlashPosition - 1;
				month = sysStringToInt(currentRowDate->Substring(++firstSlashPosition, monthLength));
				secondSlashPosition = i;
				isMonthFound = true;
			}
		}
		year = sysStringToInt(currentRowDate->Substring(++secondSlashPosition, YEAR_LENGTH));

		return DateTime(year, month, day);
	}
}

DateTime DataConverter::sysStringToDateTimeWithMinutes(String^ currentRowTime) {
	int firstSlashPosition = ZERO;
	int secondSlashPosition= ZERO;
	int monthLength = ZERO;
	bool isDayFound = false;
	bool isMonthFound = false;
	int day = DateTime::Today.Day;
	int month = DateTime::Today.Month;
	int year = DateTime::Today.Year;
	int hour = ZERO;
	int minutes = ZERO;

	for(int i=0; i<currentRowTime->Length; i++) {
		if(currentRowTime[i] == ':') {
			hour = sysStringToInt(currentRowTime->Substring(ZERO, i));
			minutes = sysStringToInt(currentRowTime->Substring(i+1, 2));
			break;
		}
	}
	hour = standardToMilitaryTime(currentRowTime, hour);

	return DateTime(year, month, day, hour, minutes, ZERO);
}

int DataConverter::sysStringToInt(String^ dayMonthYear) {
	return Convert::ToInt32(dayMonthYear);
}

int DataConverter::militaryToStandardTime(int hour) {
	if(hour > HALF_A_DAY) {
		hour -= HALF_A_DAY;
	}

	return hour;
}

int DataConverter::standardToMilitaryTime(String^ currentRowTime, int hour) {
	if(currentRowTime->Substring(currentRowTime->Length-2, 2) == "am" && (hour == HALF_A_DAY)) {
		hour = ZERO;
	}else if(currentRowTime->Substring(currentRowTime->Length-2, 2) == "pm" && (hour < HALF_A_DAY)) {
		hour += HALF_A_DAY;
	}

	return hour;
}

String^ DataConverter::appendForeZeroToMinute(int minute) {
	String^ min = intToString(minute);
	if(minute < DOUBLE_DIGIT) {
		min = "0" + min;
	}

	return min;
}

void DataConverter::setTaskTime(String^& taskTime, String^ hour, String^ minute, String^ dayStat) {
	if(hour == "0" && minute == "00") {
		taskTime = "";
	}else {
		taskTime = hour + ":" + minute + " " + dayStat;
	}

	return;
}

bool DataConverter::checkDayStatus(int hour) {
	return (hour <= HALF_A_DAY);
}