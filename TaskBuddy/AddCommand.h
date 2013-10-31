//	
//	NAME: class AddCommand
//	DESCRIPTION: This class handles adding tasks to the Storage.
//	It analyses and dissects the input string from the user in order to obtain 
//	the task information and creates the task accordingly.
//	It obtains the updated list of tasks after adding to the Storage and returns 
//	all the information to the Logic class including any invalidities.
//
#ifndef ADDCOMMAND_H
#define ADDCOMMAND_H

#include "Command.h"
#include "Exception.h"
#include "Log.h"

using namespace std;

class AddCommand : public Command {

private:

	static const int ELEVEN_PM = 23;
	static const int LAST_MIN_IN_HOUR = 59;
	static const int MAXIMUM_HOUR = 12;
	static const int TWELVE_HOURS = 12;
	static const int TWENTY_FOUR_HOURS = 24;

	static const int DOUBLE_DIGIT = 2;
	static const int SINGLE_DIGIT = 1;

	//Number of digits in our available time formats
	static const int FOUR_DIGIT_TIME = 4;
	static const int THREE_DIGIT_TIME = 3;
	static const int TWO_DIGIT_TIME = 2;
	static const int SINGLE_DIGIT_TIME = 1;

	//String lengths of all valid time inputs.
	//e.g. 1pm/1am
	static const int SINGLE_DIGIT_TIME_STRINGLEN = 3;
	//e.g. 10pm/10am
	static const int TWO_DIGIT_TIME_STRINGLEN = 4;
	//e.g. 130pm/130am
	static const int THREE_DIGIT_TIME_STRINGLEN = 5;
	//e.g. 1030am/1030pm
	static const int FOUR_DIGIT_TIME_STRINGLEN = 6;

	//String length of "am" and "pm".
	static const int MERIDIAN_STRINGLEN = 2;

	Task* addedTask;
	Log write;

	string toLowerCase(string input);
	bool isPositionFound(int position);
	string determineName(string& input, int pos);
	bool haveNoName(int pos);

	TIME getCurrentTime();
	TIME determineTaskTime(string input, TASK_DATE date);
	void calculateTime(string input, int numDigits, TIME& taskTime);

	bool isValidTimeFormat(string input);
	bool isSingleDigitTime(string input);
	bool isTwoDigitTime(string input);
	bool isThreeDigitTime(string input);
	bool isFourDigitTime(string input);
	bool isValidTime(TIME taskTime);

	int findHyphenPos(string input);

	void determineTaskDuration(
		TIME& start, 
		TIME& end, 
		string startString, 
		string endString, 
		TASK_DATE date);

	bool isValidDuration(TIME start, TIME end);

	bool timeHasPassed(TIME time, TASK_DATE date);
	bool isToday(TASK_DATE date);
	
public:

	AddCommand(string info);
	virtual DataFeedback execute(Storage& container);
	virtual DataFeedback undo(Storage& container);
	
};

#endif