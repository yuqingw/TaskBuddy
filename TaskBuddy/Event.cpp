#include "stdafx.h"
#include "Event.h"



//This class is inherited from Task class
//Object of this class is used as event task which has a duration besides the basic attributes of a task

Event::Event(std::string name, TASK_DATE date, TIME start, TIME end)
	:Task(name) {

		deadLine = date;
		startTime = start;
		endTime = end;
		mark = false;
		expired = false;
		today = false;
}

TASK_DATE Event::getDeadLine() {

	return deadLine;
}

TIME Event::getEndTime() {

	return endTime;
}

TIME Event::getStartTime() {


	return startTime;
}

bool Event::isExpired() {
	return expired;
}

void Event::indicateExpired() {
	expired = true;
}

bool Event::isMarked() {
	return mark;
}

void Event::changeMark() {

	mark = !mark;
}

bool Event::isToday() {
	return today;
}

void Event::indicateToday(bool indication) {
	today = indication;
}

