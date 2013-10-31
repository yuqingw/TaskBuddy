#include "stdafx.h"
#include "Command.h"


Day Command::getCurrentDay() {

	time_t now = time(0);
	tm *ltm = localtime(&now);

	if(ltm->tm_wday == 0)
		return SUNDAY;
	
	if(ltm->tm_wday == 1)
		return MONDAY;
	
	if(ltm->tm_wday == 2)
		return TUESDAY;

	if(ltm->tm_wday == 3)
		return WEDNESDAY;

	if(ltm->tm_wday == 4)
		return THURSDAY;

	if(ltm->tm_wday == 5)
		return FRIDAY;

	if(ltm->tm_wday == 6)
		return SATURDAY;

}

int Command::getCurrentMonth() {

	time_t now = time(0);
	tm *ltm = localtime(&now);

	return ltm->tm_mon+1;

}

int Command::getCurrentDayOfMonth() {

	time_t now = time(0);
	tm *ltm = localtime(&now);

	return ltm->tm_mday;

}

int Command::getCurrentYear() {

	time_t now = time(0);
	tm *ltm = localtime(&now);

	return 1900 + ltm->tm_year;

}

void Command::shortenInput(string& input) {

	assert(input.size() != 0);

	if(input[POS_OF_1ST_CHAR] == SPACE) {
		while(input[POS_OF_1ST_CHAR] == SPACE) {
			input = input.substr(POS_OF_2ND_CHAR, input.size()-POS_OF_2ND_CHAR);
		}
	}

	while(input.size() != 0) {
		if(input[POS_OF_1ST_CHAR] == SPACE) {

			while(input[POS_OF_1ST_CHAR] == SPACE) {
				input = input.substr(POS_OF_2ND_CHAR, input.size()-POS_OF_2ND_CHAR);
				if(input.size() == 0) {
					break;
				}
			}
			break;

		} else {
			input = input.substr(POS_OF_2ND_CHAR, input.size()-POS_OF_2ND_CHAR);
		}
	}
}

//Finds an indication of a month in the input string.
Month Command::checkForMonth(string input) {

	assert(input.size() != 0);

	if(input == "january" || input == "jan") {
		return JANUARY;

	} else if(input == "february" || input == "feb") {
		return FEBRUARY;

	} else if(input == "march" || input == "mar") {
		return MARCH;

	} else if(input == "april" || input == "apr") {
		return APRIL;

	} else if(input == "may") {
		return MAY;

	} else if(input == "june" || input == "jun") {
		return JUNE;

	} else if(input == "july" || input == "jul") {
		return JULY;

	} else if(input == "august" || input == "aug") {
		return AUGUST;

	} else if(input == "september" || input == "sep") {
		return SEPTEMBER;

	} else if(input == "october" || input == "oct") {
		return OCTOBER;

	} else if(input == "november" || input == "nov") {
		return NOVEMBER;

	} else if(input == "december" || input == "dec") {
		return DECEMBER;

	} else {
		return NO_MONTH;
	}

}

//Finds an indication of a day of the week in the input string.
Day Command::checkForDay(string input) {

	assert(input.size() != 0);

	if(input == "sunday" || input == "sun") {
		return SUNDAY;

	} else if(input == "monday" || input == "mon") {
		return MONDAY;

	} else if(input == "tuesday" || input == "tue") {
		return TUESDAY;

	} else if(input == "wednesday" || input == "wed") {
		return WEDNESDAY;

	} else if(input == "thursday" || input == "thu") {
		return THURSDAY;

	} else if(input == "friday" || input == "fri") {
		return FRIDAY;

	} else if(input == "saturday" || input == "sat") {
		return SATURDAY;

	} else {

		return NO_DAY;
	}
}

//This method determines the number of days from the current day to the input day of week.
int Command::determineDaysToTask(Day dayOfTask) {

	Day currentDay = getCurrentDay();

	int currentDayNum = currentDay;
	int taskDayNum = dayOfTask;
	int daysToTask;
		
	if(taskDayNum >= currentDayNum) {
		daysToTask = taskDayNum - currentDayNum;
	} else {
		daysToTask = DAYS_IN_WEEK - currentDayNum + taskDayNum;
	}

	return daysToTask;
}

//This method extracts the date of the task from the user input string in the case whereby the format
// of user input to indicate date of the task is through a day of the week, for e.g "friday".
// Example of input string : "friday" or "fri".
//Used by AddCommand and SearchCommand for analysis of date inputs.
TASK_DATE Command::determineDateForDayFormat(string& input) {

	assert(input.size() != 0);
	istringstream inputStream(input);
	string dayString;
	inputStream >> dayString;

	TASK_DATE dateOfTask;
	Day taskDay = checkForDay(dayString);
	int currentMonth = getCurrentMonth();
	int numDaysToTask = determineDaysToTask(taskDay);

	int dayOfMonth = getCurrentDayOfMonth();

	dateOfTask.day = dayOfMonth + numDaysToTask;
	dateOfTask.month = currentMonth;
	dateOfTask.year = getCurrentYear();
	
	adjustDateForOverflow(dateOfTask);

	shortenInput(input);

	return dateOfTask;
}

//This method adjusts the date for determining date through day of week format in the case of overflow
//since adding the number of days to the current day of month can lead to it being larger
//than the maximum number of days in the month
void Command::adjustDateForOverflow(TASK_DATE& taskDate) {

	if(getCurrentMonth() == FEBRUARY) {

		if(taskDate.month > NUM_DAYS_IN_FEB) {
			taskDate.day -= NUM_DAYS_IN_FEB;
			taskDate.month += 1;
		}

	} else if(getCurrentMonth() == APRIL || getCurrentMonth() == JUNE || getCurrentMonth() == SEPTEMBER || getCurrentMonth() == NOVEMBER) {

		if(taskDate.month > THIRTY_DAYS) {
			taskDate.day -= THIRTY_DAYS;
			taskDate.month += 1;
		}

	} else {

		if(taskDate.day > THIRTY_ONE_DAYS) {

			taskDate.day -= THIRTY_ONE_DAYS;

			if(getCurrentMonth() == DECEMBER) {
				taskDate.month -= (NUM_OF_MONTHS_IN_YEAR-1);
				taskDate.year += 1;
			} else {
				taskDate.month += 1;
			}
		}
	}
}

//This method extracts the date of the task from the user input string in the case whereby the format
// of user input to indicate date of the task is through day,month, year(year can be omitted for current year)
//for e.g "21 october", "21 october 2012".
//Used by AddCommand and SearchCommand for analysis of date inputs.
TASK_DATE Command::determineDateForDateFormat(string& input) throw(Exception) {

	assert(input.size() != 0);

	TASK_DATE dateOfTask;

	string subInput = input;
	istringstream inputStream(subInput);
	string charString;

	inputStream >> charString;
	dateOfTask.day = convertCharToDigits(charString);
	//remove the day from string.
	shortenInput(input);

	inputStream >> charString;
	dateOfTask.month = checkForMonth(charString);
	//remove the month from string.
	shortenInput(input);
	
	inputStream >> charString;
	if(haveYear(charString)) {
		dateOfTask.year = convertCharToDigits(charString);
		//remove year from string
		shortenInput(input);
	} else {
		dateOfTask.year = getCurrentYear();
	}

	if(!isValidDate(dateOfTask)) {
		throw Exception(INVALID_DATE);
	}

	/*if(dateHasPassed(dateOfTask)) {
		throw Exception(INVALID_DATE_PASSED);
	}*/

	return dateOfTask;
}

bool Command::isFloat(Task* task) {

	assert(task != NULL);

	if(task->getDeadLine().day == 0) {
		return true;
	} else {
		return false;
	}
}

//This method detects from user input if user wishes to edit float tasks.
//Used by AddCommand and DelCommand where alterations to float tasks are possible.
bool Command::isChangeFloatTask(string input) {

	string charString;
	istringstream inputStream(input);
	inputStream >> charString;

	if(charString == FLOAT_TASK) {
		return true;
	} else {
		return false;
	}
}

bool Command::isDigit(char character) {

	if(character >= ASCII_OF_0 & character <= ASCII_OF_9) {
		return true;
	} else {
		return false;
	}
} 

//This method checks if the string consists of a single or two digits 
// which are the possibilities for numbers representing day
bool Command::isDigitsForDay(string input) {

	if(input.size() == 2) {

		if(isDigit(input[POS_OF_1ST_CHAR]) & isDigit(input[POS_OF_2ND_CHAR])) {
			return true;
		} else {
			return false;
		}

	} else if(input.size() == 1) {

		if(isDigit(input[POS_OF_1ST_CHAR])) {
			return true;
		} else {
			return false;
		}

	} else {

		return false;
	}
}

//This method checks and finds the position of a day of the week in the string.
//returns -1 if not found.
//Used by AddCommand and SearchCommand where analysis of dates are required.
int Command::findDayPosition(string input) {

	assert(input.size() != 0);

	istringstream inputStringStream(input);
	string charString;
	int tempPosition = 1;
	int position = 0;

	while(inputStringStream >> charString) {

		if(checkForDay(charString) != NO_DAY) {
			position = tempPosition;
			tempPosition++;
		} else {
			tempPosition++;
		}
	}

	if(position == 0) {
		return NOT_FOUND;
	} else {
		return position;
	}
}

//This method checks and finds the position of a date in the string.
//returns -1 if not found.
//Used by AddCommand and SearchCommand where analysis of dates are required.
int Command::findDatePosition(string input) {

	assert(input.size() != 0);

	istringstream inputStringStream(input);
	string charString;
	string prevCharString;
	int tempPosition = 1;
	int position = 0;

	while(inputStringStream >> charString) {

		if(checkForMonth(charString) != NO_MONTH & isDigitsForDay(prevCharString)) {
			position = tempPosition;
			tempPosition++;
		} else {
			prevCharString = charString;
			tempPosition++;
		}
	}

	if(position == 0) {
		return NOT_FOUND;
	} else {
		return position-1;
	}
}

bool Command::isValidDayOfMonth(TASK_DATE date) {

	if(date.day == 0) {
		return false;

	} else if(date.month == FEBRUARY) {

		if(isLeapYear(date.year)) {
			if(date.day > NUM_DAYS_IN_LEAP_FEB) {
				return false;
			}
		} else {
			if(date.day > NUM_DAYS_IN_FEB) {
				return false;
			}
		}
			
	} else if(date.month == APRIL || date.month == JUNE || 
		date.month == SEPTEMBER || date.month == NOVEMBER) {

		if(date.day > THIRTY_DAYS) {
			return false;
		}

	} else {
		
		if(date.day > THIRTY_ONE_DAYS) {
			return false;
		}
	}
	
	return true;
}

bool Command::isLeapYear(int year) {

	if(year%LEAP_DIVISOR_FOUR == 0 && year%LEAP_DIVISOR_HUNDRED !=0) {
		return true;
	} else if(year%LEAP_DIVISOR_FOUR == 0 && year%LEAP_DIVISOR_HUNDRED == 0 && 
		year%LEAP_DIVISOR_FOUR_HUNDRED == 0) {
		return true;
	} else {
		return false;
	}
}

bool Command::isValidDate(TASK_DATE date) {

	if(!isValidDayOfMonth(date)) {
		return false;
	}

	return true;
}

//This method checks if user input position is not within range of the displayed list.
//Used by DelCommand and MarkCommand where input of index positions.
bool Command::isOutOfRange(vector<Task*> taskList, int position) {
	
	if(position == 0) {
		return true;
	} else if(position > taskList.size()) {
		return true;
	} else {
		return false;
	}
}

bool Command::haveYear(string input) {

	if(countDigits(input) == NUM_DIGITS_IN_YEAR && input.size() == NUM_DIGITS_IN_YEAR) {
		return true;
	} else {
		return false;
	}
}

bool Command::dateHasPassed(TASK_DATE date) {

	if(date.year < getCurrentYear()) {
		return true;

	} else if(date.year == getCurrentYear() && date.month < getCurrentMonth()) {
		return true;

	} else if(date.year == getCurrentYear() && date.month == getCurrentMonth() && date.day < getCurrentDayOfMonth()) {
		return true;

	} else {
		return false;
	}

}

//Converts user input index to the actual position in a vector list.
//Used by DelCommand and MarkCommand.
int Command::findPositionInList(vector<Task*> taskList, string input) throw (Exception) {

	int userEnteredPos = convertCharToDigits(input);

	if(isOutOfRange(taskList, userEnteredPos)) {
		throw Exception(INVALID_POSITION);
	}

	int vectorPosition = userEnteredPos - 1;
	return vectorPosition;

}

//Counts the number of the characters in the string that are digits
//from the start of the string until the end or until the character is no longer a digit
int Command::countDigits(string input) {

	assert(input.size() != 0);

	int digitCount = 0;

	for(int charPos=0; charPos<input.size(); charPos++) {
		if(isDigit(input[charPos])) {
			digitCount++;
		} else {
			break;
		}
	}

	return digitCount;
}

//Converts the value of characters representing digits to the actual value of the digits.
//Can only be used when the input string consists of only digit characters
int Command::convertCharToDigits(string input) {

	int charPos;
	int digit;
	int value = 0;
	int exponent = input.size() - 1;
	double base = BASE_POWER;

	for(charPos=0; charPos < input.size(); charPos++) {

		digit = input[charPos] - ASCII_OF_0;
		value += digit*pow(base, exponent);
		exponent--;
	}

	return value;
}

bool Command::consistsOfOnlyDigits(string input) {

	if(countDigits(input) == input.size()) {
		return true;
	} else {
		return false;
	}
}

//Checks if the command is flagged for undo-ing.
//True means undo cannot be called.
bool Command::isFlagged() {
	return undoFlag;
}

void Command::removeFlag() {
	undoFlag = false;
}