//
//	NAME: class SearchCommand
//	DESCRIPTION: This class handles search commands by the user.
//	User is able to search by name or date.
//	Checks for existence of day of week or specific date in input string first.
//	If date indicator not found then searches by name.
//

#ifndef SEARCHCOMMAND_H
#define SEARCHCOMMAND_H

#include <vector>
#include <string>
#include <ctime>
#include <sstream>
#include "Command.h"
#include "Log.h"

using namespace std;

class SearchCommand : public Command {
private:

	static const int FIRST_POSITION = 1;
	Log write;

public:

	SearchCommand(string info);
	virtual DataFeedback execute(Storage& container);
	virtual DataFeedback undo(Storage& container);
};
#endif
