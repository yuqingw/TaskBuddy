#include "stdafx.h"
#include "DelCommand.h"


DelCommand::DelCommand(string input, vector<Task*> current, vector<Task*> floats) {

	deletedTask = NULL;
	taskInfo = input;
	undoFlag = true;
	currentTimedDisplay = current;
	currentFloatDisplay = floats;

}

DataFeedback DelCommand::execute(Storage& container) {

	write.writeLogToFile("DelCommand::execute","Enter");
	DataFeedback dataToLogic;
	vector<Task*> taskList;
	string charString;
	istringstream inputStream(taskInfo);

	inputStream >> charString;

	if(isChangeFloatTask(charString)) {

		inputStream >> charString;

		if(consistsOfOnlyDigits(charString)) {

			int position;

			try {
				position = findPositionInList(currentFloatDisplay, charString);
			} catch (Exception positionExcpt) {
				write.writeLogToFile("DelCommand::execute","Exit");
				return positionExcpt.getFeedback();
			}

			deletedTask = currentFloatDisplay[position];
			taskList  = container.delFloatTask(deletedTask);
			DataFeedback successFeedback(DEL_SUCCESS, taskList, deletedTask, CHANGED_FLOAT);
			write.writeLogToFile("DelCommand::execute","Exit");
			dataToLogic = successFeedback;
		}

	} else if(consistsOfOnlyDigits(charString)) {

		int position;

		try {
			position = findPositionInList(currentTimedDisplay, charString);
		} catch (Exception positionExcpt) {
			write.writeLogToFile("DelCommand::execute","Exit");
			return positionExcpt.getFeedback();
		}

		deletedTask = currentTimedDisplay[position];
		taskList  = container.delTimedTask(deletedTask);
		DataFeedback successFeedback(DEL_SUCCESS, taskList, deletedTask, 1);
		write.writeLogToFile("DelCommand::execute","Exit");
		dataToLogic = successFeedback;
		
	} else {

		DataFeedback failedFeedback(INVALID_POSITION);
		write.writeLogToFile("DelCommand::execute","Exit");
		dataToLogic = failedFeedback;
	}

	return dataToLogic;
}
	

DataFeedback DelCommand::undo(Storage& container) {

	write.writeLogToFile("DelCommand::undo","Enter");
	vector<Task*> taskList;

	if(isFloat(deletedTask)) {

		taskList = container.addFloatTask(deletedTask);
		DataFeedback logicFeedback(UNDO_DELETE, taskList, deletedTask, CHANGED_FLOAT);
		write.writeLogToFile("DelCommand::undo","Exit");
		return logicFeedback;

	} else {

		taskList = container.addTimedTask(deletedTask);
		DataFeedback logicFeedback(UNDO_DELETE, taskList, deletedTask, 1);
		write.writeLogToFile("DelCommand::undo","Exit");
		return logicFeedback;
	}
}

