#include "stdafx.h"
#include "AddCommand.h"

static const string ANTE_MERIDIAN = "am";
static const string POST_MERIDIAN = "pm";

//@author A0085504H
AddCommand::AddCommand(string info) {

	taskInfo = info;
	addedTask = NULL;
	undoFlag = true;
}

//This method analyses the user input string and creates the task to be added
//and adds it the Storage.
//Analyses for the name, date and time of the task which are handled by other methods.
//Returns information about the task added to Logic.
DataFeedback AddCommand::execute(Storage& container) {

	write.writeLogToFile("addCommand::execute","Enter");
	vector<Task*> taskList;
	string taskName;
	TASK_DATE taskDate;

	if(isChangeFloatTask(taskInfo)) {

		//remove "wl" from the string
		shortenInput(taskInfo);
		taskName = taskInfo;

		if(taskName.empty()) {

			DataFeedback logicFeedback(INVALID_NO_NAME);
			return logicFeedback;

		} else {

			addedTask = new Task(taskInfo);
			taskList = container.addFloatTask(addedTask);
			DataFeedback logicFeedback(ADD_SUCCESS, taskList, addedTask, CHANGED_FLOAT);
			write.writeLogToFile("addCommand::execute","Exit");
			return logicFeedback;
		}

	} else {

		taskInfo = toLowerCase(taskInfo);

		bool haveDate;
		bool haveDay;
		int dayPosition = findDayPosition(taskInfo);
		int datePosition = findDatePosition(taskInfo);

		haveDay = isPositionFound(dayPosition);
		haveDate = isPositionFound(datePosition);

		//If user inputs both a valid day of the week and date, 
		//the one that comes later in the input is taken as the task date indicator
		if(haveDay == true && haveDate == true) {
			if(dayPosition > datePosition) {
				haveDate = false;
			} else {
				haveDay = false;
			}
		}

		//Code below determines name and date of task
		if(haveDay == true) {

			try {
				taskName = determineName(taskInfo, dayPosition);
			} catch (Exception nameExcpt) {
				return nameExcpt.getFeedback();
			}

			taskDate = determineDateForDayFormat(taskInfo);

		} else if(haveDate == true) {

			try {
				taskName = determineName(taskInfo, datePosition);
			} catch (Exception nameExcpt) {
				return nameExcpt.getFeedback();
			}

			try {
				taskDate = determineDateForDateFormat(taskInfo);
			} catch (Exception dateExcpt) {
				return dateExcpt.getFeedback();
			}

			if(dateHasPassed(taskDate)) {
				DataFeedback invalidFeedback(INVALID_DATE_PASSED);
				return invalidFeedback;
			}

		} else {

			DataFeedback invalidFeedback(INVALID_DATE);
			return invalidFeedback;
		}

		//Code below determines task time and creates task
		string timeString;
		istringstream inputStream(taskInfo);
		inputStream >> timeString;

		if(taskInfo.find_first_of(HYPHEN) == NOT_FOUND) {

			TIME taskTime;

			try {
				taskTime = determineTaskTime(timeString, taskDate);
			} catch(Exception timeExcpt) {
				return timeExcpt.getFeedback();
			}

			if(inputStream >> timeString) {

				DataFeedback logicFeedback(INVALID_TIME_FORMAT);
				return logicFeedback;

			} else {

				addedTask = new DeadlineTask(taskName, taskDate, taskTime);
				taskList = container.addTimedTask(addedTask);
				DataFeedback logicFeedback(ADD_SUCCESS, taskList, addedTask, CHANGED_TIMED);
				write.writeLogToFile("addCommand::execute","Exit");
				return logicFeedback;
			}
		
		} else {

			TIME startTime;
			TIME endTime;
			int hyphenPos;

			try {
				hyphenPos = findHyphenPos(taskInfo);
			} catch(Exception excpt) {
				return excpt.getFeedback();
			}

			string startTimeString = taskInfo.substr(POS_OF_1ST_CHAR, hyphenPos);
			string endTimeString = taskInfo.substr(hyphenPos+1, taskInfo.size()-1);

			try {
				determineTaskDuration(startTime, endTime, startTimeString, endTimeString, taskDate);
			} catch(Exception timeExcpt) {
				return timeExcpt.getFeedback();
			}
	
			addedTask = new Event(taskName, taskDate, startTime, endTime);
			taskList = container.addTimedTask(addedTask);
			DataFeedback logicFeedback(ADD_SUCCESS, taskList, addedTask, CHANGED_TIMED);
			write.writeLogToFile("addCommand::execute","Exit");
			return logicFeedback;
		}
	}	
}

DataFeedback AddCommand::undo(Storage& container) {

	write.writeLogToFile("addCommand::undo","Enter");
	vector<Task*> taskList;

	if(isFloat(addedTask)) {

		taskList = container.delFloatTask(addedTask);
		DataFeedback logicFeedback(UNDO_ADD, taskList, addedTask, CHANGED_FLOAT);
		write.writeLogToFile("addCommand::undo","Exit");
		return logicFeedback;

	} else {

		taskList = container.delTimedTask(addedTask);
		DataFeedback logicFeedback(UNDO_ADD, taskList, addedTask, CHANGED_TIMED);
		write.writeLogToFile("addCommand::undo","Exit");
		return logicFeedback;
	}
}

string AddCommand::toLowerCase(string input) {

	string lowCaseText = input;

	for(int i=0; i<lowCaseText.size(); i++)
		lowCaseText[i] = tolower(lowCaseText[i]);

	return lowCaseText;
}

//This method extracts the name of the task from the input string
//by using the position of the date indicator which is what comes after the task name in the input string
//Exception will be thrown if a name cannot be found.
string AddCommand::determineName(string& input, int pos) throw(Exception){
	
	assert(input.size() != 0);

	if(haveNoName(pos)) {
		throw Exception(INVALID_NO_NAME);
	}

	string name = "";
	string charString;
	istringstream inputStream(input);

	for(int currPos=1; currPos < pos; currPos++) {

		shortenInput(input);
		inputStream >> charString;
		name += charString;

		if(currPos != pos-1) {
			name += SPACE;
		}
	}

	return name;
}

bool AddCommand::haveNoName(int pos) {

	if(pos == 0 || pos == 1) {
		return true;
	} else {
		return false;
	}
}

TIME AddCommand::getCurrentTime() {

	TIME currentTime;
	time_t now = time(0);
	tm *ltm = localtime(&now);

	currentTime.min = ltm->tm_min;
	currentTime.hour = ltm->tm_hour;

	return currentTime;
}

//This method determines the time of the task from the input string.
//At this point, the name and date of the task has already been extracted from the input string.
//Exceptions are thrown if user did not input a valid time format or the time input is invalid.
//A time that has passed will also not be allowed and thrown as exception.
TIME AddCommand::determineTaskTime(string input, TASK_DATE date) throw(Exception) {

	int charPos = 0;
	int numDigitsInTime;
	TIME timeOfTask;

	if(input.empty()) {

		timeOfTask.hour = ELEVEN_PM;
		timeOfTask.min = LAST_MIN_IN_HOUR;

	} else {

		if(!isValidTimeFormat(input)) {
			throw Exception(INVALID_TIME_FORMAT);
		}

		numDigitsInTime = countDigits(input);

		try {
			calculateTime(input, numDigitsInTime, timeOfTask);
		} catch(Exception excpt) {
			throw excpt;
		}
	}
	
	if(timeHasPassed(timeOfTask, date)) {
		throw Exception(INVALID_DATE_PASSED);
	}

	return timeOfTask;
}

void AddCommand::calculateTime(string input, int numDigits, TIME& taskTime) throw(Exception) {

	int hourStringLength;
	int minStringLength;
	string hourString;
	string minString;

	if(numDigits == FOUR_DIGIT_TIME) {

		hourStringLength = DOUBLE_DIGIT;
		minStringLength = DOUBLE_DIGIT;
		hourString = input.substr(POS_OF_1ST_CHAR, hourStringLength);
		minString = input.substr(POS_OF_3RD_CHAR, minStringLength);
		taskTime.hour = convertCharToDigits(hourString);
		taskTime.min = convertCharToDigits(minString);

		if(!isValidTime(taskTime)) {
			throw Exception(INVALID_TIME);
		}

		if(input.substr(POS_OF_5TH_CHAR, MERIDIAN_STRINGLEN) == POST_MERIDIAN) {
			taskTime.hour += TWELVE_HOURS;
		}

	} else if(numDigits == THREE_DIGIT_TIME) {

		hourStringLength = SINGLE_DIGIT;
		minStringLength = DOUBLE_DIGIT;
		hourString = input.substr(POS_OF_1ST_CHAR, hourStringLength);
		minString = input.substr(POS_OF_2ND_CHAR, minStringLength);
		taskTime.hour = convertCharToDigits(hourString);
		taskTime.min  = convertCharToDigits(minString);
			
		if(!isValidTime(taskTime)) {
			throw Exception(INVALID_TIME);
		}

		if(input.substr(POS_OF_4TH_CHAR, MERIDIAN_STRINGLEN) == POST_MERIDIAN) {
			taskTime.hour += TWELVE_HOURS;
		}

	} else if(numDigits == TWO_DIGIT_TIME) {

		hourStringLength = DOUBLE_DIGIT;
		hourString = input.substr(POS_OF_1ST_CHAR, hourStringLength);
		taskTime.hour = convertCharToDigits(hourString);
		taskTime.min = 0;

		if(!isValidTime(taskTime)) {
			throw Exception(INVALID_TIME);
		}

		if(input.substr(POS_OF_3RD_CHAR, MERIDIAN_STRINGLEN) == POST_MERIDIAN) {
			taskTime.hour += TWELVE_HOURS;
		}

	} else {

		hourStringLength = SINGLE_DIGIT;
		hourString = input.substr(POS_OF_1ST_CHAR, hourStringLength);
		taskTime.hour = convertCharToDigits(hourString);
		taskTime.min = 0;

		if(!isValidTime(taskTime)) {
			throw Exception(INVALID_TIME);
		}

		if(input.substr(POS_OF_2ND_CHAR, MERIDIAN_STRINGLEN) == POST_MERIDIAN) {
			taskTime.hour += TWELVE_HOURS;
		}
	}	
}

//This method determines the starting time and ending time of the task in the case which the 
//user adds a task with a duration.
//Any invalid time/time format will be thrown as exceptions.
//A start time that is later than the end time will be also not be allowed and thrown.
void AddCommand::determineTaskDuration(
	TIME& start, 
	TIME& end, 
	string startString, 
	string endString, 
	TASK_DATE date) throw(Exception) {
	
	assert(startString.size() != 0);
	assert(endString.size() != 0);

	try{
		start = determineTaskTime(startString, date);
	}  catch(Exception except) {
		throw except;
	}
	
	try{
		end = determineTaskTime(endString, date);
	}  catch(Exception except) {
		throw except;
	}

	if(!isValidDuration(start, end)) {
		throw Exception(INVALID_DURATION);
	}

}

//This method determines the position of the hyphen, '-' character in the the time duration string e.g. "130pm-230pm"
//in the case which the user adds a task with duration.
//If the position is at the start or at the end, it will be be definitely invalid and thrown as an exception.
int AddCommand::findHyphenPos(string input) throw(Exception) {

	assert(input.size() != 0);

	int charPos = 0;

	while(input[charPos] != HYPHEN) {
		charPos++;
	}

	if(charPos == POS_OF_1ST_CHAR || charPos == input.size()-1) {
		throw Exception(INVALID_TIME_FORMAT);
	}

	return charPos;
}

//This method checks to see if user has input a valid time format
//Available formats are 1 to 4 digits with "am" or "pm"
//First digit cannot be 0.
//e.g. 1 digit: 1am/1pm
//     2 digits: 10am/10pm
//     3 digits: 130am/130pm
//     4 digits: 1030am/1030pm
bool AddCommand::isValidTimeFormat(string input) {

	assert(input.size() != 0);

	if(input[POS_OF_1ST_CHAR] == ASCII_OF_0) {

		return false;

	} else if(isSingleDigitTime(input)) {

		return true;	

	} else if(isTwoDigitTime(input)) {

		return true;
		
	} else if(isThreeDigitTime(input)) {
			
		return true;

	} else if(isFourDigitTime(input)) {

		return true;
		
	} else {

		return false;
	}
}

bool AddCommand::isSingleDigitTime(string input) {

	if((input.size() == SINGLE_DIGIT_TIME_STRINGLEN) && 
	   (countDigits(input) == SINGLE_DIGIT_TIME) && 
	   (input.substr(POS_OF_2ND_CHAR, MERIDIAN_STRINGLEN) == ANTE_MERIDIAN) || 
	   (input.size() == SINGLE_DIGIT_TIME_STRINGLEN) && 
	   (countDigits(input) == SINGLE_DIGIT_TIME) && 
	   (input.substr(POS_OF_2ND_CHAR, MERIDIAN_STRINGLEN) == POST_MERIDIAN)) {

		return true;
	} else {
		return false;
	}
}

bool AddCommand::isTwoDigitTime(string input) {

	if(input.size() == TWO_DIGIT_TIME_STRINGLEN && 
		countDigits(input) == TWO_DIGIT_TIME && 
		input.substr(POS_OF_3RD_CHAR, MERIDIAN_STRINGLEN) == ANTE_MERIDIAN ||
		input.size() == TWO_DIGIT_TIME_STRINGLEN &&
		countDigits(input) == TWO_DIGIT_TIME && 
		input.substr(POS_OF_3RD_CHAR, MERIDIAN_STRINGLEN) == POST_MERIDIAN) {

		return true;

	} else {
		return false;
	}
}

bool AddCommand::isThreeDigitTime(string input) {

	if(input.size() == THREE_DIGIT_TIME_STRINGLEN && 
		countDigits(input) == THREE_DIGIT_TIME && 
		input.substr(POS_OF_4TH_CHAR, MERIDIAN_STRINGLEN) == ANTE_MERIDIAN ||
		input.size() == THREE_DIGIT_TIME_STRINGLEN &&
		countDigits(input) == THREE_DIGIT_TIME && 
		input.substr(POS_OF_4TH_CHAR, MERIDIAN_STRINGLEN) == POST_MERIDIAN) {

		return true;

	} else {
		return false;
	}
}

bool AddCommand::isFourDigitTime(string input) {

	if(input.size() == FOUR_DIGIT_TIME_STRINGLEN && 
		countDigits(input) == FOUR_DIGIT_TIME && 
		input.substr(POS_OF_5TH_CHAR, MERIDIAN_STRINGLEN) == ANTE_MERIDIAN ||
		input.size() == FOUR_DIGIT_TIME_STRINGLEN && 
		countDigits(input) == FOUR_DIGIT_TIME && 
		input.substr(POS_OF_5TH_CHAR, MERIDIAN_STRINGLEN) == POST_MERIDIAN) {

		return true;

	} else {
		return false;
	}
}

//User input hour cannot be greater than 12 since time format is am/pm
//Minutes cannot be greater than 59
bool AddCommand::isValidTime(TIME taskTime) {

	if(taskTime.hour == 0 || taskTime.hour > MAXIMUM_HOUR || taskTime.min > LAST_MIN_IN_HOUR) {
		return false;

	} else {
		return true;
	}
}

//Checks if start time is earlier than end time.
bool AddCommand::isValidDuration(TIME start, TIME end) {

	int startHour = start.hour;
	int endHour = end.hour;

	if(startHour == TWELVE_HOURS || startHour == TWENTY_FOUR_HOURS) {
		startHour -= TWELVE_HOURS;
	}

	if(endHour == TWELVE_HOURS || endHour == TWENTY_FOUR_HOURS) {
		endHour -= TWELVE_HOURS;
	}

	if(startHour > endHour) {
		return false;
	} else if(start.hour == end.hour && start.min >= end.min) {
		return false;
	} else {
		return true;
	}

}

bool AddCommand::isPositionFound(int position) {
	return (position == NOT_FOUND ? false : true);
}

bool AddCommand::timeHasPassed(TIME time, TASK_DATE date) {

	int hour = time.hour;
	if(hour == TWENTY_FOUR_HOURS || hour == TWELVE_HOURS) {
		hour-= TWELVE_HOURS;
	}

	if(isToday(date)) {

		if(hour < getCurrentTime().hour) {
			return true;
		} else if(hour == getCurrentTime().hour && time.min < getCurrentTime().min) {
			return true;
		}
	}

	return false;
}

bool AddCommand::isToday(TASK_DATE date) {

	if(date.day == getCurrentDayOfMonth() && date.month == getCurrentMonth() && date.year == getCurrentYear()) {
		return true;
	} else {
		return false;
	}
}
