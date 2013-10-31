#include "stdafx.h"
#include "SearchCommand.h"


SearchCommand::SearchCommand(string info) {

	taskInfo = info;
	undoFlag = true;
}

DataFeedback SearchCommand::execute(Storage& container) {

	write.writeLogToFile("SearchCommand::execute","Enter");
	string subInfo = taskInfo;
	vector<Task*> taskList;
	DataFeedback dataToLogic;

	//If user wishes to search by day or date, these must be at the start of the input string
	if(findDayPosition(subInfo) == FIRST_POSITION) {

		Day searchedDay = checkForDay(subInfo);
		TASK_DATE searchedDate = determineDateForDayFormat(subInfo);
		write.writeLogToFile("SearchCommand::execute","Exit");
		taskList = container.searchByDate(searchedDate);

	} else if(findDatePosition(subInfo) == FIRST_POSITION) {

		TASK_DATE searchedDate;
		try {
			searchedDate = determineDateForDateFormat(subInfo);
		} catch(Exception excpt) {
			excpt.setFeedback(EMPTY_SEARCH);
			return excpt.getFeedback();
		}
		write.writeLogToFile("SearchCommand::execute","Exit");
		taskList = container.searchByDate(searchedDate);

	} else {

		string searchedName = subInfo;
		write.writeLogToFile("SearchCommand::execute","Exit");
		taskList = container.searchByName(searchedName);
	}

	if(taskList.empty()) {
		DataFeedback dataInfo(EMPTY_SEARCH);
		dataToLogic = dataInfo;
	} else {
		DataFeedback dataInfo(SEARCH_SUCCESS, taskList, CHANGED_TIMED);
		dataToLogic = dataInfo;
	}

	return dataToLogic;
}

DataFeedback SearchCommand::undo(Storage& container) {
	write.writeLogToFile("SearchCommand::undo","Enter");
	DataFeedback test(INVALID_COMMAND);
	write.writeLogToFile("SearchCommand::undo","Exit");
	return test;
}


