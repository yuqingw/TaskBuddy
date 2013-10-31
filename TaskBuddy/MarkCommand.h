//
//	NAME: class MarkCommand
//	DESCRIPTION: This class handles mark commands by the user.
//	Users are supposed to input index positions of the tasks shown on the display
//	to indicate the tasks they wish to mark/unmark.
//	Users are able to input more than one index position,separate by a space, to mark/unmark
//	multiple tasks at one time.
//

#ifndef MARKCOMMAND_H
#define MARKCOMMAND_H

#include <vector>
#include <string>
#include <ctime>
#include <sstream>
#include "Command.h"
#include "Log.h"

using namespace std;

class MarkCommand : public Command {

private:

	vector<Task*> currentTimedDisplay;
	vector<Task*> markedTasks;
	Log write;

public:

	MarkCommand(string input, vector<Task*> current);
	virtual DataFeedback execute(Storage& container);
	virtual DataFeedback undo(Storage& container);
};
#endif