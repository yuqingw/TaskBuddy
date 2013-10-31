#include "stdafx.h"
#include "DataFeedback.h"

DataFeedback::DataFeedback() {
	
	messageToUser = NIL;
	changedTask = NULL;
	changedPos = NULL_POSITION;
	changedFloat = false;
	changedTimed = false;
}

DataFeedback::DataFeedback(UserFeedback feedback, vector<Task*> tasks, Task* task, int whatChanged) {

	messageToUser = feedback;
	listOfTasksForDisplay = tasks;
	changedTask = task;
	changedPos = NULL_POSITION;

	if(whatChanged == FLOAT_WAS_CHANGED) {
		changedFloat = true;
		changedTimed = false;
	} else {
		changedFloat = false;
		changedTimed = true;
	}
}

DataFeedback::DataFeedback(UserFeedback feedback, vector<Task*> tasks, int whatChanged) {

	messageToUser = feedback;
	listOfTasksForDisplay = tasks;
	changedTask = NULL;
	changedPos = NULL_POSITION;

	if(whatChanged == FLOAT_WAS_CHANGED) {
		changedFloat = true;
		changedTimed = false;
	} else {
		changedFloat = false;
		changedTimed = true;
	}
}

DataFeedback::DataFeedback(UserFeedback feedback) {

	messageToUser = feedback;
	changedTask = NULL;
	changedPos = NULL_POSITION;
	changedFloat = false;
	changedTimed = false;
}

bool DataFeedback::haveChangedFloat() {

	return changedFloat;
}

bool DataFeedback::haveChangedTimed() {
	
	return changedTimed;
}

int DataFeedback::getAddedPos() {

	return changedPos;
}

UserFeedback DataFeedback::getFeedback() {
	return messageToUser;
}

vector<Task*> DataFeedback::getTaskList() {

	return listOfTasksForDisplay;
}

vector<Task*> DataFeedback::getMainList() {

	return mainPageList;
}

Task* DataFeedback::getChangedTask() {

	return changedTask;
}

void DataFeedback::setFeedback(UserFeedback feedback) {

	messageToUser = feedback;
}

void DataFeedback::setChangedPosition(int position) {

	changedPos = position;
}

void DataFeedback::changeTaskList(vector<Task*> list) {

	listOfTasksForDisplay = list;
}

void DataFeedback::setMainList(vector<Task*> list) {

	mainPageList = list;
}