#include "stdafx.h"
#include "DeadlineTask.h"

//This class is inherited from Task class
//Object of this class is used as deadline task which do not have a start time
//End time of a deadline task is 2359pm of the date indicated if user do not define a specific time
DeadlineTask::DeadlineTask(std::string name, TASK_DATE date, TIME time)
	:Task(name) {

		deadLine = date;
		endTime = time;
		mark = false;
		expired = false;
		today = false;
}

TASK_DATE DeadlineTask::getDeadLine() {

	return deadLine;
}

TIME DeadlineTask::getEndTime() {

	return endTime;
}

TIME DeadlineTask::getStartTime() {

	TIME invalidTime;

	invalidTime.hour = 0;
	invalidTime.min = 0;

	return invalidTime;
}

bool DeadlineTask::isExpired() {
	return expired;
}

void DeadlineTask::indicateExpired() {
	expired = true;
}

bool DeadlineTask::isMarked() {
	return mark;
}

void DeadlineTask::changeMark() {

	mark = !mark;
}

bool DeadlineTask::isToday() {
	return today;
}

void DeadlineTask::indicateToday(bool indication) {
	today = indication;
}

