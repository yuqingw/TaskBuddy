//	
//	NAME: class Logic
//	DESCRIPTION: This class acts as a controller/director and has access to the Parser and Storage class.
//	It gets Parser to disseminate the info and return the command which it will execute on the Storage.
//	This class also saves the tasks that are currently being displayed on the GUI.
//	It determines all the proper information that the GUI requires for displaying after each command.
//

#ifndef LOGIC_H
#define LOGIC_H

#include <string>

#include "Parser.h"
#include "Storage.h"
#include "Exception.h"
#include "Log.h"

using namespace std;

class Logic {

private:

	Storage taskBank;
	Log write;
	Parser CommandAnalyser;
	vector<Task*> currentDisplay;
	vector<Task*> floatDisplay;
	vector<Task*> prevTaskList;
	vector<Task*> taskPointersForDeletion;
	vector<COMMAND_SET> prevCommands;
	Command* prevSearch;

	bool isSearchDisplay;
	bool prevIsSearch;

	DataFeedback carryOutFirstCommand(COMMAND_SET commands, Storage& container);
	DataFeedback carryOutSecondCommand(COMMAND_SET commands, Storage& container);

	bool isBackCommand(COMMAND_SET commands);
	bool isCommandsOtherThanUpdate(COMMAND_SET commands);
	bool isCommandsThatExitSearch(DataFeedback commandInfo);

	bool isUnsuccessfulSearch(DataFeedback commandInfo);
	bool isSuccessfulSearch(DataFeedback commandInfo);
	bool isStayOnCurrentSearchPage(DataFeedback commandInfo, bool isOnSearchPage);

	bool isAddTimedTask(DataFeedback commandInfo);
	bool isDelTimedTask(DataFeedback commandInfo);
	bool isUndoAddForTimedTask(DataFeedback commandInfo);
	bool isUndoDelForTimedTask(DataFeedback commandInfo);
	bool isAddingFloat(DataFeedback commandInfo);
	bool isDeletingFloat(DataFeedback commandInfo);
	bool isMark(DataFeedback commandInfo);
	bool isUndoMark(DataFeedback commandInfo);

	bool isInvalidFirstCommand(DataFeedback commandInfo);
	bool isInvalidSecondCommand(DataFeedback commandInfo);
	bool isUndoUpdate(DataFeedback commandInfo);

	void removePointerFromVector(Task* taskPointer);

public:
	
	Logic();
	~Logic();

	void callStorageToLoad();
	vector<Task*> getInitialTimedDisplay();
	vector<Task*> getInitialFloatDisplay();
	DataFeedback analyseInput(std::string input);
	int findChangedPositionForAdding(vector<Task*> newDisplay, Task* changedTask);
	int findChangedPositionForDeleting(vector<Task*> newDisplay, vector<Task*> oldDisplay);
	

};

#endif