#include "stdafx.h"
#include "MarkCommand.h"

MarkCommand::MarkCommand(string input, vector<Task*> current) {

	taskInfo = input;
	currentTimedDisplay = current;
}

//Users are able to input more than 1 position for marking.
//If any of the input index is invalid then none of the tasks are marked
//and invalid message is returned.
DataFeedback MarkCommand::execute(Storage& container) {

	write.writeLogToFile("MarkCommand::execute","Enter");
	Task* markedTask;
	string charString;
	istringstream inputStream(taskInfo);

	while(inputStream >> charString) {

		if(consistsOfOnlyDigits(charString)) {

			int position;

			try {
				position = findPositionInList(currentTimedDisplay, charString);
			} catch (Exception positionExcpt) {

				for(int i=0; i<markedTasks.size(); i++) {
					markedTasks[i]->changeMark();
				}

				write.writeLogToFile("MarkCommand::execute","Exit");
				return positionExcpt.getFeedback();
			}

			markedTask = currentTimedDisplay[position];
			markedTask->changeMark();
			markedTasks.push_back(markedTask);

		} else {

			for(int pos=0; pos<markedTasks.size(); pos++) {
				markedTasks[pos]->changeMark();
			}

			DataFeedback dataToLogic(INVALID_POSITION);
			write.writeLogToFile("MarkCommand::execute","Exit");
			return dataToLogic;
		}
	}

	DataFeedback dataToLogic(MARK_SUCCESS, currentTimedDisplay, CHANGED_TIMED);
	write.writeLogToFile("MarkCommand::execute","Exit");
	return dataToLogic;
}

DataFeedback MarkCommand::undo(Storage& container) {

	write.writeLogToFile("MarkCommand::undo","Enter");

	for(int pos=0; pos<markedTasks.size(); pos++) {
		markedTasks[pos]->changeMark();
	}

	DataFeedback dataToLogic(UNDO_MARK, container.getAllTasks(), CHANGED_TIMED);
	write.writeLogToFile("MarkCommand::undo","Exit");
	return dataToLogic;
}

