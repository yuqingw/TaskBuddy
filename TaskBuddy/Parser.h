//
//	NAME: class Parser
//	DESCRIPTION: This class analyses what the command from the input string is and returns
//	the respective Command class to the Logic class where it will be executed
//

#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include "AddCommand.h"
#include "DelCommand.h"
#include "MarkCommand.h"
#include "SearchCommand.h"
#include "Exception.h"
#include "Log.h"

using namespace std;

enum CommandType {
	ADD, DELETE, UPDATE, UNDO, EXIT, SORT, SEARCH, MARK, BACK, INVALID
};

//Structure to hold 2 commands.
//For all commands except update, only the first command will be initialised to point to a command.
//For update, the implementation involves deleting first then adding.
//Thus second command is used in the case of updating.
struct COMMAND_SET {

	Command* first;
	Command* second;
};

class Parser {
private:

	static const int SPACE = 32;
	static const int POS_OF_1ST_CHAR = 0;

	//String lengths of the various commands.
	static const int ADD_STRING_LENGTH = 3;
	static const int DELETE_STRING_LENGTH = 6;
	static const int SEARCH_STRING_LENGTH = 6;
	static const int UPDATE_STRING_LENGTH = 6;
	static const int MARK_STRING_LENGTH = 4;
	static const int BACK_STRING_LENGTH = 4;

	static const int MIN_LENGTH_AFTER_COMMAND_WORD = 2;

	Log write;
	CommandType determineCommandType(std::string& input);

	bool isAddCommand(string input);
	bool isDeleteCommand(string input);
	bool isUpdateCommand(string input);
	bool isSearchCommand(string input);
	bool isMarkCommand(string input);
	bool isBackCommand(string input);
	bool isUndoCommand(string input);
	bool isValidAfterCommandWord(int commandLength, string input);

public:

	COMMAND_SET createCommandExecutor(string input, 
		vector<Task*>& current, 
		vector<Task*>& floats, 
		vector<COMMAND_SET>& prevCommands, 
		Command*& prevSearch);

};

#endif