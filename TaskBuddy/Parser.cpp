#include "stdafx.h"
#include "Parser.h"


//This method extracts out and determines the command word of the user input,
//leaving the execution information in the input string.
//Returns invalid when no command word is found.
//Throws exception when there is no further information other than command word.
CommandType Parser::determineCommandType(std::string& input) throw (Exception) {

	write.writeLogToFile("Parser::determineCommandType","Enter");

	if(isAddCommand(input)) {

		if(!isValidAfterCommandWord(ADD_STRING_LENGTH, input)) {
			throw Exception(INVALID_COMMAND);
		}

		int posOfInfo = ADD_STRING_LENGTH + 1;
		input = input.substr(posOfInfo, input.size()-posOfInfo);
		write.writeLogToFile("Parser::determineCommandType","Exit");

		return ADD;

	} else if(isDeleteCommand(input)) {

		if(!isValidAfterCommandWord(DELETE_STRING_LENGTH, input)) {
			throw Exception(INVALID_COMMAND);
		}

		int posOfInfo = DELETE_STRING_LENGTH + 1;
		input = input.substr(posOfInfo, input.size()-posOfInfo);

		write.writeLogToFile("Parser::determineCommandType","Exit");

		return DELETE;

	} else if(isSearchCommand(input)) {

		if(!isValidAfterCommandWord(SEARCH_STRING_LENGTH, input)) {
			throw Exception(INVALID_COMMAND);
		}

		int posOfInfo = SEARCH_STRING_LENGTH + 1;
		input = input.substr(posOfInfo, input.size()-posOfInfo);
		write.writeLogToFile("Parser::determineCommandType","Exit");

		return SEARCH;

	} else if(isUpdateCommand(input)) {

		if(!isValidAfterCommandWord(UPDATE_STRING_LENGTH, input)) {
			throw Exception(INVALID_COMMAND);
		}

		int posOfInfo = UPDATE_STRING_LENGTH + 1;
		input = input.substr(posOfInfo, input.size()-posOfInfo);
		write.writeLogToFile("Parser::determineCommandType","Exit");
		return UPDATE;

	} else if(isMarkCommand(input)) {

		if(!isValidAfterCommandWord(MARK_STRING_LENGTH, input)) {
			throw Exception(INVALID_COMMAND);
		}

		int posOfInfo = MARK_STRING_LENGTH + 1;

		input = input.substr(posOfInfo, input.size()-posOfInfo);
		write.writeLogToFile("Parser::determineCommandType","Exit");
		return MARK;

	} else if(isBackCommand(input)) {

		write.writeLogToFile("Parser::determineCommandType","Exit");
		return BACK;

	} else if(isUndoCommand(input)) {

		write.writeLogToFile("Parser::determineCommandType","Exit");
		return UNDO;

	} else {
		write.writeLogToFile("Parser::determineCommandType","Exit");
		return INVALID;
	}
}

//This method creates the proper commands based on the the user input command
//and returns them to the Logic class.
COMMAND_SET Parser::createCommandExecutor(
	string input, 
	vector<Task*>& current, 
	vector<Task*>& floats, 
	vector<COMMAND_SET>& prevCommands,
	Command*& prevSearch) throw(Exception) {

	write.writeLogToFile("Parser::createCommandExecutor","Enter");
	CommandType command;
	COMMAND_SET commandList;

	try {
		command = determineCommandType(input);
	} catch (Exception excpt) {
		throw excpt;
	}

	if(command == ADD) {

		Command* baseCommand = new AddCommand(input);
		commandList.first = baseCommand;
		commandList.second = NULL;
		prevCommands.push_back(commandList);
		write.writeLogToFile("Parser::createCommandExecutor","Exit");
		return commandList;

	} else if(command == DELETE) {

		Command* baseCommand = new DelCommand(input, current, floats);
		commandList.first = baseCommand;
		commandList.second = NULL;
		prevCommands.push_back(commandList);
		write.writeLogToFile("Parser::createCommandExecutor","Exit");
		return commandList;

	} else if(command == SEARCH) {

		Command* baseCommand = new SearchCommand(input);
		commandList.first = baseCommand;
		commandList.second = NULL;
		write.writeLogToFile("Parser::createCommandExecutor","Exit");
		return commandList;

	} else if(command == MARK) {

		Command* baseCommand = new MarkCommand(input, current);
		commandList.first = baseCommand;
		commandList.second = NULL;
		prevCommands.push_back(commandList);
		write.writeLogToFile("Parser::createCommandExecutor","Exit");
		return commandList;

	} else if(command == UNDO) {

		if(prevCommands.empty()) {
			throw Exception(INVALID_NO_COMMAND);
		}

		commandList = prevCommands[prevCommands.size() - 1];
		commandList.first->removeFlag();

		if(commandList.second != NULL) {
			commandList.second->removeFlag();
		}

		prevCommands.pop_back();
		write.writeLogToFile("Parser::createCommandExecutor","Exit");
		return commandList;

	} else if(command == UPDATE) {

		string charString;
		istringstream inputStream(input);
		inputStream >> charString;

		string delString = charString;
		string addString = "";

		if(inputStream >> charString) {
			addString += charString;
			addString += SPACE;

			while(inputStream >> charString) {
				addString += charString;
				addString += SPACE;
			}

			addString = addString.substr(POS_OF_1ST_CHAR, addString.size()-1);
			commandList.first = new DelCommand(delString, current, floats);
			commandList.second = new AddCommand(addString);
			prevCommands.push_back(commandList);

		} else {
			throw Exception(INVALID_COMMAND);
		}

		write.writeLogToFile("Parser::createCommandExecutor","Exit");
		return commandList;

	} else if(command == BACK) {

		//No commands to be created, tells Logic about returning to main page.
		commandList.first = NULL;
		commandList.second = NULL;
		write.writeLogToFile("Parser::createCommandExecutor","Exit");
		return commandList;

	} else {

		throw Exception(INVALID_COMMAND);
	}
}


bool Parser::isAddCommand(string input) {

	if(input.substr(POS_OF_1ST_CHAR, ADD_STRING_LENGTH) == "add") {
		return true;
	} else {
		return false;
	}
}

bool Parser::isDeleteCommand(string input) {

	if(input.substr(POS_OF_1ST_CHAR, DELETE_STRING_LENGTH) == "delete") {
		return true;
	} else {
		return false;
	}
}

bool Parser::isUpdateCommand(string input) {

	if(input.substr(POS_OF_1ST_CHAR, UPDATE_STRING_LENGTH) == "update") {
		return true;
	} else {
		return false;
	}
}

bool Parser::isSearchCommand(string input) {

	if(input.substr(POS_OF_1ST_CHAR, SEARCH_STRING_LENGTH) == "search") {
		return true;
	} else {
		return false;
	}
}

bool Parser::isMarkCommand(string input) {

	if(input.substr(POS_OF_1ST_CHAR, MARK_STRING_LENGTH) == "mark") {
		return true;
	} else {
		return false;
	}
}

bool Parser::isBackCommand(string input) {

	if(input.substr(POS_OF_1ST_CHAR, BACK_STRING_LENGTH) == "back") {
		return true;
	} else {
		return false;
	}
}

bool Parser::isUndoCommand(string input) {

	if(input == "undo") {
		return true;
	} else {
		return false;
	}
}

//This method checks for the existence of more information after the command word.
bool Parser::isValidAfterCommandWord(int commandLength, string input) {

	string charString;
	istringstream inputStream(input);
	inputStream >> charString;

	if(inputStream >> charString) {
		return true;
	} else {
		return false;
	}

}

