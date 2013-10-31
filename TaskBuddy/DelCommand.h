//
//	NAME: class DelCommand
//	DESCRIPTION: This class handles delete commands by the user.
//	Users are supposed to input index positions of the tasks shown on the display
//	to indicate the tasks they wish delete.
//

#ifndef DELCOMMAND_H
#define DELCOMMAND_H

#include <vector>
#include <string>
#include <ctime>
#include <sstream>
#include "Command.h"
#include "Log.h"

using namespace std;

class DelCommand : public Command {

private:

	vector<Task*> currentTimedDisplay;
	vector<Task*> currentFloatDisplay;
	Task* deletedTask;
	Log write;

public:

	DelCommand(string input, vector<Task*> current, vector<Task*> floats);
	virtual DataFeedback execute(Storage& container);
	virtual DataFeedback undo(Storage& container);


};

#endif