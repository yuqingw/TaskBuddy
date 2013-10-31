#include "stdafx.h"
#include "Task.h"


//This class is the parent class for DeadlineTask and Event
//Have the basic attributes of a typical task eg Name, Deadline, isMark etc
//Object of this class is used as a floating task without a deadline and start/end time

Task::Task(std::string name) {

	taskName = name;

}

std::string Task::getName() {

	return taskName;
}

TASK_DATE Task::getDeadLine() {

	TASK_DATE invalidDate;

	invalidDate.day=0;
	invalidDate.month=0;
	invalidDate.year=0;

	return invalidDate;
}

TIME Task::getEndTime() {

	TIME invalidTime;
	invalidTime.hour=0;
	invalidTime.min=0;
	return invalidTime;
}

TIME Task::getStartTime() {

	TIME invalidTime;
	invalidTime.hour=0;
	invalidTime.min=0;
	return invalidTime;

}

bool Task::isExpired() {
	return false;
}

void Task::indicateExpired() {
	return;
}

bool Task::isMarked() {
	return false;
}

void Task::changeMark() {
	return;
}

bool Task::isToday() {
	return false;
}

void Task::indicateToday(bool indication) {
	return;
}

