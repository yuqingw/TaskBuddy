//
//	NAME: class Command
//	DESCRIPTION: This is an abstract class for all the different types of user commands,
//	including AddCommand, DelCommand, SearchCommand and MarkCommand.
//	It has protected methods and constant variables which are used by
//	more than one command class.
//
#ifndef COMMAND_H
#define COMMAND_H

#include <vector>
#include <string>
#include <ctime>
#include <sstream>
#include <assert.h>
#include <math.h>
#include "Storage.h"
#include "DataFeedback.h"
#include "Exception.h"

enum Day {
	NO_DAY, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY
};

enum Month {
	NO_MONTH, JANUARY, FEBRUARY, MARCH, APRIL, MAY, JUNE, JULY, AUGUST, SEPTEMBER, OCTOBER, NOVEMBER, DECEMBER
};

static const string FLOAT_TASK = "wl";

class Command {
protected:

	string taskInfo;
	bool undoFlag;

	static const int DAYS_IN_WEEK = 7;

	//Ascii value of char space.
	static const int SPACE = 32;
	//Ascii value of char hyphen.
	static const int HYPHEN = 45;
	static const int NOT_FOUND = -1;

	//Positions of characters in a string.
	static const int POS_OF_1ST_CHAR = 0;
	static const int POS_OF_2ND_CHAR = 1;
	static const int POS_OF_3RD_CHAR = 2;
	static const int POS_OF_4TH_CHAR = 3;
	static const int POS_OF_5TH_CHAR = 4;

	//Ascii values of various digits
	static const int ASCII_OF_0 = 48;
	static const int ASCII_OF_1 = 49;
	static const int ASCII_OF_9 = 57;

	//Year has four digits
	static const int NUM_DIGITS_IN_YEAR = 4;

	static const int LEAP_DIVISOR_FOUR = 4;
	static const int LEAP_DIVISOR_HUNDRED = 100;
	static const int LEAP_DIVISOR_FOUR_HUNDRED = 400;

	static const int BASE_POWER = 10;

	//Numerical indications of whether float tasks or tasks that have time have changed
	static const int CHANGED_FLOAT = 0;
	static const int CHANGED_TIMED = 1;

	static const int NUM_OF_MONTHS_IN_YEAR = 12;
	static const int NUM_DAYS_IN_FEB = 28;
	static const int NUM_DAYS_IN_LEAP_FEB = 29;

	//Number of days in months june,april, september and november
	static const int THIRTY_DAYS = 30;
	//Number of days in months january, march, march, july, august, october and december;
	static const int THIRTY_ONE_DAYS = 31;

	Day getCurrentDay();
	int getCurrentMonth();
	int getCurrentDayOfMonth();
	int getCurrentYear();

	void shortenInput(string& input);

	Month checkForMonth(string input);
	Day checkForDay(string input);

	int determineDaysToTask(Day dayOfTask);

	TASK_DATE determineDateForDayFormat(string& input);
	void adjustDateForOverflow(TASK_DATE& taskDate);

	TASK_DATE determineDateForDateFormat(string& input);

	bool isFloat(Task* task);
	bool isChangeFloatTask(string input);

	bool isDigit(char character);
	bool isDigitsForDay(string input);

	bool isValidDayOfMonth(TASK_DATE date);
	bool isLeapYear(int year);
	bool isValidDate(TASK_DATE date);

	bool isOutOfRange(vector<Task*> taskList, int position);

	bool haveYear(string input);
	bool dateHasPassed(TASK_DATE date);

	int findDayPosition(string input);
	int findDatePosition(string input);

	int findPositionInList(vector<Task*> taskList, string input);

	int countDigits(string input);
	int convertCharToDigits(string input);

	bool consistsOfOnlyDigits(string input);

public: 

	virtual DataFeedback execute(Storage& container) = 0;
	virtual DataFeedback undo(Storage& container) = 0;

	bool isFlagged();
	void removeFlag();
};

#endif