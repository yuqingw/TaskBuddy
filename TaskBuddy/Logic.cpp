#include "stdafx.h"
#include "Logic.h"


Logic::Logic() {
	isSearchDisplay = false;
	prevIsSearch = false;
	prevSearch = NULL;
	currentDisplay=taskBank.getTimedTasks();
	floatDisplay=taskBank.getFloatTasks();
}

Logic::~Logic() {

	delete prevSearch;
	prevSearch = NULL;
	
	for(int position = 0; position < prevCommands.size(); position++) {
		delete prevCommands[position].first;
		prevCommands[position].first = NULL;
		delete prevCommands[position].second;
		prevCommands[position].second = NULL;
	}

	for(int i=0; i <taskPointersForDeletion.size(); i++) {
		delete taskPointersForDeletion[i];
		taskPointersForDeletion[i] = NULL;
	}
}

void Logic::callStorageToLoad() {
	taskBank.loadToFile();
}

vector<Task*> Logic::getInitialTimedDisplay() {
	return currentDisplay;
}

vector<Task*> Logic::getInitialFloatDisplay() {
	return floatDisplay;
}
//This is the only method that the GUI calls whenever there is a user input.
//Obtains the proper commands from Parser class and executes the commands.
//Analyses the information received and determines the proper information to be returned to
//the GUI for display
//Information that needs to be determined include:
//	The vector of tasks to be displayed.
//	The position of tasks to be highlighted on the display if needed.
DataFeedback Logic::analyseInput(std::string input) {

	write.writeLogToFile("Logic::analyseInput","Enter");
	DataFeedback dataToGUI;
	DataFeedback deleteData;
	DataFeedback addData;
	DataFeedback searchData;
	COMMAND_SET commandExecutor;

	try {
		commandExecutor = CommandAnalyser.createCommandExecutor(input, currentDisplay, floatDisplay, prevCommands, prevSearch);
	} catch (Exception commandExcpt) {
		write.writeLogToFile("Logic::analyseInput","Exit");
		return commandExcpt.getFeedback();
	}

	if(isBackCommand(commandExecutor)) {

		isSearchDisplay = false;
		currentDisplay = taskBank.getAllTasks();
		DataFeedback mainPage(MAIN, taskBank.getAllTasks(), 1);
		dataToGUI = mainPage;

	} else if(isCommandsOtherThanUpdate(commandExecutor)) {
			
		dataToGUI = carryOutFirstCommand(commandExecutor, taskBank);

		//Code below handles cases regarding search display
		//i.e. whether commands lead to staying on the search page
		//or exiting the search page.
		if(isUnsuccessfulSearch(dataToGUI)) {
				
			write.writeLogToFile("Logic::analyseInput","Exit");
			prevTaskList = taskBank.getAllTasks();
			return dataToGUI;
		}

		if(isCommandsThatExitSearch(dataToGUI)) {
			isSearchDisplay = false;
		}

		if(isStayOnCurrentSearchPage(dataToGUI, isSearchDisplay)) {

			searchData = prevSearch->execute(taskBank);

			if(!dataToGUI.haveChangedFloat()) {
				dataToGUI.changeTaskList(searchData.getTaskList());
			}
		}
		
		int changedPosition;

		//Code below determines the type of action that was carried out
		//and determines the proper information to be returned to the GUI for display
		if(isAddTimedTask(dataToGUI)) {

			changedPosition = findChangedPositionForAdding(dataToGUI.getTaskList(), dataToGUI.getChangedTask());
			dataToGUI.setChangedPosition(changedPosition);
			currentDisplay = dataToGUI.getTaskList();

		} else if(isUndoDelForTimedTask(dataToGUI)) {

			changedPosition = findChangedPositionForAdding(dataToGUI.getTaskList(), dataToGUI.getChangedTask());
			dataToGUI.setChangedPosition(changedPosition);
			currentDisplay = dataToGUI.getTaskList();
			removePointerFromVector(dataToGUI.getChangedTask());

		} else if(isDelTimedTask(dataToGUI)) {

			changedPosition = findChangedPositionForDeleting(dataToGUI.getTaskList(), currentDisplay);
			dataToGUI.setChangedPosition(changedPosition);
			currentDisplay = dataToGUI.getTaskList();
			taskPointersForDeletion.push_back(dataToGUI.getChangedTask());

		} else if(isUndoAddForTimedTask(dataToGUI)) {

			changedPosition = findChangedPositionForDeleting(dataToGUI.getTaskList(), prevTaskList);
			dataToGUI.setMainList(prevTaskList);
			dataToGUI.setChangedPosition(changedPosition);
			currentDisplay = dataToGUI.getTaskList();
			taskPointersForDeletion.push_back(dataToGUI.getChangedTask());
			
		} else if(isSuccessfulSearch(dataToGUI)) {

			isSearchDisplay = true;
			delete prevSearch;
			prevSearch = commandExecutor.first;
			currentDisplay = dataToGUI.getTaskList();

		} else if(isMark(dataToGUI)) {

			prevTaskList = taskBank.getAllTasks();
			write.writeLogToFile("Logic::analyseInput","Exit");
			return dataToGUI;

		} else if(isUndoMark(dataToGUI)) {

			dataToGUI.changeTaskList(taskBank.getAllTasks());
			currentDisplay = dataToGUI.getTaskList();

		} else if(isAddingFloat(dataToGUI)) {

			changedPosition = findChangedPositionForAdding(dataToGUI.getTaskList(), dataToGUI.getChangedTask());
			dataToGUI.setChangedPosition(changedPosition);
			floatDisplay = dataToGUI.getTaskList();

		} else if(isDeletingFloat(dataToGUI)) {

			changedPosition = findChangedPositionForDeleting(dataToGUI.getTaskList(), floatDisplay);
			dataToGUI.setChangedPosition(changedPosition);
			floatDisplay = dataToGUI.getTaskList();

		} else {

			//remove invalid commands from vector of previous commands for purpose of undo-ing
			assert(!prevCommands.empty());
			delete prevCommands[prevCommands.size() - 1].first;
			delete prevCommands[prevCommands.size() - 1].second;
			prevCommands.pop_back();
		}

	} else {

		//Case for update command.
		deleteData = carryOutFirstCommand(commandExecutor, taskBank);

		if(isInvalidFirstCommand(deleteData)) {
			delete prevCommands[prevCommands.size() - 1].first;
			delete prevCommands[prevCommands.size() - 1].second;
			prevCommands.pop_back();
			write.writeLogToFile("Logic::analyseInput","Exit");
			return deleteData;
		}

		addData = carryOutSecondCommand(commandExecutor, taskBank);

		if(isInvalidSecondCommand(addData)) {
			//if second command is invalid, undo the first command which is already executed.
			commandExecutor.first->undo(taskBank);
			delete prevCommands[prevCommands.size() - 1].first;
			delete prevCommands[prevCommands.size() - 1].second;
			prevCommands.pop_back();
			write.writeLogToFile("Logic::analyseInput","Exit");
			return addData;
		}

		dataToGUI = addData;

		if(isUndoUpdate(dataToGUI)) {
			isSearchDisplay = false;
		}

		if(isSearchDisplay) {
			searchData = prevSearch->execute(taskBank);
			dataToGUI.changeTaskList(searchData.getTaskList());
		} else {
			dataToGUI.changeTaskList(addData.getTaskList());
		}

		int changedPosition;

		if(isUndoUpdate(dataToGUI)) {
			changedPosition = findChangedPositionForAdding(dataToGUI.getTaskList(), deleteData.getChangedTask());
			taskPointersForDeletion.push_back(addData.getChangedTask());
			removePointerFromVector(deleteData.getChangedTask());
		} else {
			changedPosition = findChangedPositionForAdding(dataToGUI.getTaskList(), dataToGUI.getChangedTask());
			taskPointersForDeletion.push_back(deleteData.getChangedTask());
		}

		dataToGUI.setChangedPosition(changedPosition);
		currentDisplay = dataToGUI.getTaskList();

		if(dataToGUI.getFeedback() == ADD_SUCCESS) {
			dataToGUI.setFeedback(UPD_SUCCESS);
		} else {
			dataToGUI.setFeedback(UNDO_UPD);
		}
	}	
		
	prevTaskList = taskBank.getAllTasks();
	write.writeLogToFile("Logic::analyseInput","Exit");
	return dataToGUI;
}

//Used by all types of commands.
DataFeedback Logic::carryOutFirstCommand(COMMAND_SET commands, Storage& container) {

	DataFeedback executionData;

	if(commands.first->isFlagged()) {
		executionData = commands.first->execute(container);
	} else {
		executionData = commands.first->undo(container);
	}

	return executionData;
}

//Only used in the case of update command which is carried out using delete+add.
DataFeedback Logic::carryOutSecondCommand(COMMAND_SET commands, Storage& container) {

	DataFeedback executionData;

	if(commands.second->isFlagged()) {
		executionData = commands.second->execute(container);
	} else {
		executionData = commands.second->undo(container);
	}

	return executionData;
}

bool Logic::isBackCommand(COMMAND_SET commands) {

	if(commands.first == NULL) {
		return true;
	} else {
		return false;
	}
}

bool Logic::isUnsuccessfulSearch(DataFeedback commandInfo) {

	if(commandInfo.getFeedback() == EMPTY_SEARCH) {
		return true;
	} else {
		return false;
	}
}

bool Logic::isSuccessfulSearch(DataFeedback commandInfo) {

	if(commandInfo.getFeedback() == SEARCH_SUCCESS) {
		return true;
	} else {
		return false;
	}
}

//Used to check if User is currently on a search page and the is not doing another search.
bool Logic::isStayOnCurrentSearchPage(DataFeedback commandInfo, bool isOnSearchPage) {

	if(commandInfo.getFeedback() != SEARCH_SUCCESS && isOnSearchPage) {
		return true;
	} else {
		return false;
	}
}

//This method determines the position of the task in the vector after it is added.
//This is used in the case of an add command or undo-delete command.
int Logic::findChangedPositionForAdding(vector<Task*> newDisplay, Task* changedTask) {

	int changedPos;

	for(changedPos=0; changedPos < newDisplay.size(); changedPos++) {

		if(newDisplay[changedPos] == changedTask) {
			break;
		}
	}

	return changedPos;
}

//This method determines the position of the task in the vector before it was deleted
//This is used in the case of a delete command or undo-add command.
int Logic::findChangedPositionForDeleting(vector<Task*> newDisplay, vector<Task*> oldDisplay) {

	int changedPos = 0;

	while(changedPos < newDisplay.size() && changedPos < oldDisplay.size()) {

		if(oldDisplay[changedPos] != newDisplay[changedPos]) {
			break;
		}

		changedPos++;
	}

	return changedPos;
}


bool Logic::isCommandsOtherThanUpdate(COMMAND_SET commands) {

	if(commands.second == NULL) {
		return true;
	} else {
		return false;
	}
}

//Commands that lead to exiting search page including add and undo commands.
bool Logic::isCommandsThatExitSearch(DataFeedback commandInfo) {

	if(isAddTimedTask(commandInfo) || isUndoAddForTimedTask(commandInfo) || isUndoDelForTimedTask(commandInfo) || isUndoMark(commandInfo)) {
		return true;
	} else {
		return false;
	}

}

bool Logic::isAddTimedTask(DataFeedback commandInfo) {

	if(commandInfo.getFeedback() == ADD_SUCCESS &&  commandInfo.haveChangedTimed() == true) {
		return true;
	} else {
		return false;
	}
}

bool Logic::isDelTimedTask(DataFeedback commandInfo) {

	if(commandInfo.getFeedback() == DEL_SUCCESS &&  commandInfo.haveChangedTimed() == true) {
		return true;
	} else {
		return false;
	}
}

bool Logic::isUndoAddForTimedTask(DataFeedback commandInfo) {

	if(commandInfo.getFeedback() == UNDO_ADD &&  commandInfo.haveChangedTimed() == true) {
		return true;
	} else {
		return false;
	}
}

bool Logic::isUndoDelForTimedTask(DataFeedback commandInfo) {

	if(commandInfo.getFeedback() == UNDO_DELETE &&  commandInfo.haveChangedTimed() == true) {
		return true;
	} else {
		return false;
	}
}

bool Logic::isAddingFloat(DataFeedback commandInfo) {

	if((commandInfo.getFeedback() == ADD_SUCCESS &&  commandInfo.haveChangedFloat() == true) || 
		(commandInfo.getFeedback() == UNDO_DELETE && commandInfo.haveChangedFloat() == true)) {

		return true;

	} else {

		return false;
	}
}

bool Logic::isDeletingFloat(DataFeedback commandInfo) {

	if((commandInfo.getFeedback() == DEL_SUCCESS &&  commandInfo.haveChangedFloat() == true) || 
		(commandInfo.getFeedback() == UNDO_ADD && commandInfo.haveChangedFloat() == true)) {

		return true;

	} else {

		return false;
	}
}

bool Logic::isMark(DataFeedback commandInfo) {

	if(commandInfo.getFeedback() == MARK_SUCCESS &&  commandInfo.haveChangedTimed() == true) {
		return true;
	} else {
		return false;
	}
}

bool Logic::isUndoMark(DataFeedback commandInfo) {

	if(commandInfo.getFeedback() == UNDO_MARK &&  commandInfo.haveChangedTimed() == true) {
		return true;
	} else {
		return false;
	}
}

bool Logic::isInvalidFirstCommand(DataFeedback commandInfo) {

	if(commandInfo.getFeedback() != DEL_SUCCESS && commandInfo.getFeedback() != UNDO_DELETE) {
		return true;
	} else {
		return false;
	}
}

bool Logic::isInvalidSecondCommand(DataFeedback commandInfo) {

	if(commandInfo.getFeedback() != ADD_SUCCESS && commandInfo.getFeedback() != UNDO_ADD) {
		return true;
	} else {
		return false;
	}
}

bool Logic::isUndoUpdate(DataFeedback commandInfo) {

	if(commandInfo.getFeedback() == UNDO_ADD) {
		return true;
	} else {
		return false;
	}
}

void Logic::removePointerFromVector(Task* taskPointer) {

	for(int pos=0; pos<taskPointersForDeletion.size(); pos++) {
		if(taskPointer == taskPointersForDeletion[pos]) {
			taskPointersForDeletion.erase(taskPointersForDeletion.begin()+pos);
		}
	}
}

